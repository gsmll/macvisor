/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice SK02: 0x157dc-0x1a1dc — the transport-buffer / tb_message layer: the
 * message state machine (encoding vs decoding), the transport-buffer
 * (tb_transport) put/get primitives for u8/u16/u32/u64/f32/f64 and byte
 * buffers, transport-buffer allocation/mapping/copy-in/copy-out, capability
 * (capref) transport records, and the f32/f64 encode/decode entries.
 *
 * Terminology used here (all estimates):
 *   tb_message   - a message envelope: state @ +0x00, kind/type @ +0x04,
 *                  transport ptr @ +0x50, and a small slot array @ +0x28.
 *   tb_transport - the buffer descriptor (base@0, @8, pos@0x10, size@0x18,
 *                  @0x20, flags@0x28). Reached via *(message+0x50) (tb_get).
 *   state codes: 1 = encoding (write), 4 = decoding (read), 5 = released,
 *                 2 = completed. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* cL4 trap primitive: SoftwareBreakpoint(kind, pc) in the decompile. */
#define SoftwareBreakpoint(code, addr)  __builtin_trap()
#define CallSupervisor(n)  __asm__ volatile("hvc #0" ::: "memory")

/* dword = 4-byte word (used by the decompile-typed put/get wrappers). */
typedef uint32_t dword;

/* English-first aliases for the body helpers (bodies use these names). */
#define sk_heap_calloc(count, size, tag)   FUN_00010244((unsigned long)(count), (unsigned long)(size), (unsigned long)(tag))
#define sk_heap_realloc(p, n, tag)         FUN_000102f4((unsigned long)(p), (unsigned long)(n), (unsigned long)(tag))
#define sk_memcpy(d, s, n)                 FUN_00117cc4((unsigned long)(d), (unsigned long)(s), (unsigned long)(n))
#define sk_puts(s)                         FUN_00118b28((const char *)(s))
#define sk_phys_alloc(size)                FUN_00034f70()
#define sk_stack_chk()                     FUN_0011d7e8()
#define sk_boot_object_get(type)           FUN_00034a2c()
#define sk_fault_alloc_panic()             FUN_004b0498()
#define sk_fault_alloc()                   FUN_004b0068()
#define sk_va_align(v)                     FUN_000132d4((unsigned long)(v))
#define sk_va_align2(v, n)                 FUN_000132e0((unsigned long)(v), (unsigned long)(n))

/* arm64 TPIDRRO_EL0 (user read-only thread pointer). */
extern unsigned long tpidrro_el0;

/* ---- Shared cross-slice helpers (bodies owned by other slices; FUN_ address
 *      is ground truth). All declared variadic returning a word so they can be
 *      used both as value-producing calls and as void statements; the return
 *      is meaningful only where the original reads it. ---- */
extern unsigned long FUN_00010244(unsigned long count, unsigned long size, unsigned long tag);
extern unsigned long FUN_000102f4(unsigned long p, unsigned long nsize, unsigned long tag);
extern unsigned long FUN_00117cc4(unsigned long d, unsigned long s, unsigned long n);
extern unsigned long thunk_FUN_00114330(unsigned long d, unsigned long s, unsigned long n);
extern unsigned long FUN_00114330(unsigned long d, unsigned long s, unsigned long n);
extern unsigned long FUN_00118b28(const char *s);
extern void FUN_0011d7e8(unsigned long a, ...) __attribute__((noreturn));
extern unsigned long FUN_00034f70(void);
extern unsigned long FUN_00034a2c(void);
extern void FUN_00054354(void) __attribute__((noreturn));
extern void *thunk_FUN_00012568(void *p);
extern unsigned long thunk_FUN_00012568_2(void *p);
extern unsigned long thunk_FUN_00061638(void);
extern unsigned long FUN_00061638(void);
extern unsigned long FUN_00060524(unsigned long a, ...);
extern unsigned long FUN_000636a4(unsigned long a, unsigned long b);
extern unsigned long FUN_000639a0(unsigned long a, void *b);
extern unsigned long FUN_00062c2c(unsigned long a, unsigned long b, unsigned long c);
extern unsigned long FUN_0006290c(unsigned long a, unsigned long b, unsigned long c);
extern unsigned long FUN_00013260(void);
extern unsigned long FUN_000132d4(unsigned long v);
extern unsigned long FUN_000132e0(void *v, unsigned long n);
extern unsigned long FUN_0005ee58(unsigned long a, unsigned long b, unsigned long c, unsigned long d);
extern unsigned long FUN_0005ee50(unsigned long a);
extern unsigned long FUN_0005ee48(unsigned long a);
extern unsigned long FUN_0005ee40(unsigned long a);
extern unsigned long FUN_0005edac(unsigned long i, unsigned long v);
extern unsigned long FUN_0005eb78(unsigned long d, unsigned long n, int c);
extern unsigned long FUN_0036b270(unsigned long x);
extern void FUN_003a25d4(unsigned long x);
extern unsigned long FUN_002b24b8(unsigned long a, unsigned long b);
extern unsigned long FUN_002a9ba8(unsigned long a, unsigned long b);
extern unsigned long FUN_00376038(unsigned long a, unsigned long b);
extern unsigned long FUN_0001a2f4(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long e);
extern unsigned long FUN_0001d4a0(unsigned long a, unsigned long b);

/* Object/cap registry helpers. */
extern unsigned long FUN_00015108(unsigned long a, unsigned long b, unsigned long v, unsigned long tag);
extern void FUN_000151c8(unsigned long a, unsigned long b);
extern unsigned long FUN_00015264(unsigned long a, unsigned long b);
extern unsigned long FUN_00014470(unsigned long a);
extern unsigned long FUN_00014478(unsigned long a, int b);
extern unsigned long FUN_000145bc(unsigned long a, unsigned long b);
extern unsigned long thunk_FUN_00014510(unsigned long a, unsigned long b);
extern unsigned long FUN_00014578(unsigned long a);
extern void FUN_000153ec(unsigned long a);
extern unsigned long FUN_0001483c(unsigned long a);
extern void FUN_000147e0(unsigned long a);
extern unsigned long FUN_00014c18(unsigned long a, unsigned long v);
extern unsigned long FUN_0001505c(void);
extern unsigned long FUN_00015440(unsigned long a);
extern unsigned long FUN_00015450(unsigned long a);
extern unsigned long FUN_00015468(unsigned long a, unsigned long b, unsigned long *c);
extern unsigned long FUN_0001485c(unsigned long a, unsigned long b, unsigned long *c, unsigned long d);
extern unsigned long FUN_00014bd4(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long e);
extern unsigned long FUN_00014bd0(unsigned long a, unsigned long b, unsigned long c, unsigned long *d, unsigned long e);
extern unsigned long FUN_00014ce0(unsigned long a, unsigned long b, unsigned long c, unsigned long d, int e);
extern unsigned long FUN_00014db8(unsigned long a, unsigned long b, int c, unsigned long d, unsigned long e);
extern unsigned long FUN_00014f90(unsigned long a, unsigned long b, unsigned long c, int d);
extern unsigned long FUN_00015630(unsigned long a, unsigned long b);
extern unsigned long FUN_00015670(unsigned long a, unsigned long b, int c, unsigned long d);
extern unsigned long FUN_000156b8(unsigned long a, ...);
extern unsigned long FUN_000156e0(unsigned long a, ...);
extern unsigned long FUN_000155e8(unsigned long a, unsigned long b, int c, unsigned long d);
extern unsigned long FUN_00015548(unsigned long a, unsigned long b);
extern unsigned long FUN_0001574c(unsigned long a, unsigned long b);
extern unsigned long FUN_0004b520(unsigned long a);
extern void FUN_0004b664(unsigned long a);
extern unsigned long FUN_0004b710(unsigned long a, unsigned long b, int c);

/* ---- Ringminus1 fault/panic helper routines (FUN_004b0xxx) ---- */
extern void FUN_004b0498(void) __attribute__((noreturn));
extern void FUN_004b0068(void) __attribute__((noreturn));
extern unsigned long FUN_004b0570(void);
extern unsigned long FUN_004b05a0(void);
extern unsigned long FUN_004b05e8(void);
extern unsigned long FUN_004b05c4(void);
extern unsigned long FUN_004b060c(void);
extern unsigned long FUN_004b063c(void);
extern unsigned long FUN_004b066c(void);
extern unsigned long FUN_004b0690(void);
extern void FUN_004b06c0(void) __attribute__((noreturn));
extern unsigned long FUN_004b06e4(void);
extern unsigned long FUN_004b0714(void);
extern void FUN_004b0744(unsigned long p);
extern unsigned long FUN_004b07c0(void);
extern unsigned long FUN_004b07f0(void);
extern unsigned long FUN_004b0080(void);
extern unsigned long FUN_004b0244(void);
extern unsigned long FUN_004b0558(unsigned long k);
extern void FUN_004b0820(void);
extern unsigned long FUN_004b0850(void);
extern unsigned long FUN_004b0874(void);
extern unsigned long FUN_004b0898(void);
extern unsigned long FUN_004b08bc(void);
extern unsigned long FUN_004b08e0(void);
extern unsigned long FUN_004b0904(void);
extern unsigned long FUN_004b0934(void);
extern unsigned long FUN_004b0964(void);
extern unsigned long FUN_004b0988(void);
extern unsigned long FUN_004b09b8(void);
extern unsigned long FUN_004b09e8(void);
extern unsigned long FUN_004b0a18(void);
extern unsigned long FUN_004b0a3c(void);
extern unsigned long FUN_004b0a6c(void);
extern unsigned long FUN_004b0a90(void);
extern unsigned long FUN_004b0ac0(void);
extern unsigned long FUN_004b0ae4(void);
extern unsigned long FUN_004b0b14(void);
extern unsigned long FUN_004b0b44(void);
extern unsigned long FUN_004b0b74(void);
extern unsigned long FUN_004b0b98(unsigned long a, unsigned long b);
extern unsigned long FUN_004b0bbc(void);
extern unsigned long FUN_004b0be0(unsigned long a, unsigned long b);
extern unsigned long FUN_004b0c04(void);
extern unsigned long FUN_004b0c28(void);
extern unsigned long FUN_004b0c4c(void);
extern unsigned long FUN_004b0c7c(void);
extern unsigned long FUN_004b0cac(void);
extern unsigned long FUN_004b0cdc(void);
extern unsigned long FUN_004b0d0c(void);
extern unsigned long FUN_004b0d3c(void);
extern unsigned long FUN_004b0d60(void);
extern unsigned long FUN_004b0d84(void);
extern unsigned long FUN_004b0da8(void);
extern unsigned long FUN_004b0dcc(void);
extern unsigned long FUN_004b0df0(void);
extern unsigned long FUN_004b0e14(void);
extern unsigned long FUN_004b0e38(void);
extern unsigned long FUN_004b0e5c(void);
extern unsigned long FUN_004b0e80(void);
extern unsigned long FUN_004b0ea4(void);
extern unsigned long FUN_004b0eec(void);
extern unsigned long FUN_004b0f10(void);
extern unsigned long FUN_004b0ec8(void);
extern unsigned long FUN_004b0f34(void);
extern unsigned long FUN_004b0f58(void);
extern unsigned long FUN_004b0f7c(void);
extern unsigned long FUN_004b0fa0(void);
extern unsigned long FUN_004b0fc4(void);
extern unsigned long FUN_004b0fe8(void);
extern unsigned long FUN_004b100c(void);
extern unsigned long FUN_004b1030(void);
extern unsigned long FUN_004b1054(void);
extern unsigned long FUN_004b1078(void);
extern unsigned long FUN_004b109c(void);
extern unsigned long FUN_004b10c0(void);
extern unsigned long FUN_004b10e4(void);
extern unsigned long FUN_004b1108(void);
extern unsigned long FUN_004b112c(void);
extern unsigned long FUN_004b1150(void);
extern unsigned long FUN_004b1174(void);
extern unsigned long FUN_004b1198(void);
extern unsigned long FUN_004b11bc(void);
extern unsigned long FUN_004b11e0(void);
extern unsigned long FUN_004b1204(void);
extern unsigned long FUN_004b1228(void);
extern unsigned long FUN_004b124c(void);
extern unsigned long FUN_004b1270(void);
extern unsigned long FUN_004b1294(void);
extern unsigned long FUN_004b12b8(void);
extern unsigned long FUN_004b12dc(void);
extern unsigned long FUN_004b1300(void);
extern unsigned long FUN_004b1324(void);
extern unsigned long FUN_004b1348(void);
extern unsigned long FUN_004b136c(void);
extern unsigned long FUN_004b1390(void);
extern unsigned long FUN_004b13b4(void);
extern unsigned long FUN_004b13d8(void);
extern unsigned long FUN_004b13fc(void);
extern unsigned long FUN_004b1420(void);
extern unsigned long FUN_004b1444(void);
extern unsigned long FUN_004b1468(void);
extern unsigned long FUN_004b148c(void);
extern unsigned long FUN_004b14b0(void);
extern unsigned long FUN_004b14d4(void);
extern unsigned long FUN_004b14f8(void);
extern unsigned long FUN_004b151c(void);
extern unsigned long FUN_004b1540(void);
extern unsigned long FUN_004b1564(void);
extern unsigned long FUN_004b1588(void);
extern unsigned long FUN_004b15ac(void);
extern unsigned long FUN_004b15d0(void);
extern unsigned long FUN_004b15f4(void);
extern unsigned long FUN_004b1618(void);
extern unsigned long FUN_004b163c(void);
extern unsigned long FUN_004b1660(void);
extern unsigned long FUN_004b1684(void);
extern unsigned long FUN_004b16a8(void);
extern unsigned long FUN_004b16cc(void);
extern unsigned long FUN_004b16f0(void);
extern unsigned long FUN_004b1714(void);
extern unsigned long FUN_004b1738(void);
extern unsigned long FUN_004b175c(void);
extern unsigned long FUN_004b1780(void);
extern unsigned long FUN_004b17a4(void);
extern unsigned long FUN_004b17c8(void);
extern unsigned long FUN_004b17ec(void);
extern unsigned long FUN_004b1810(void);
extern unsigned long FUN_004b1834(void);
extern unsigned long FUN_004b1858(void);
extern unsigned long FUN_004b187c(void);
extern unsigned long FUN_004b18a0(void);
extern unsigned long FUN_004b18c4(void);
extern unsigned long FUN_004b18e8(void);
extern unsigned long FUN_004b190c(void);
extern unsigned long FUN_004b1930(void);
extern unsigned long FUN_004b1954(void);
extern unsigned long FUN_004b1978(void);
extern unsigned long FUN_004b199c(void);
extern unsigned long FUN_004b19c0(void);
extern unsigned long FUN_004b19e4(void);
extern unsigned long FUN_004b1a08(void);
extern unsigned long FUN_004b1a2c(void);
extern unsigned long FUN_004b1a50(void);
extern unsigned long FUN_004b23d8(unsigned long a, unsigned long b);

/* ---- This slice's own functions (forward declarations so cross-calls work) ----
 * Each has its full body later; only a few are cross-called. */
unsigned long *tb_acquire_buffer(unsigned long m, unsigned long m2);
void tb_transport_copy_obj(unsigned long obj, unsigned long m);
unsigned long tb_channel_create(unsigned long kind);
unsigned long tb_transport_recv(unsigned long m, unsigned int *state, unsigned long **out, unsigned long *flags);
unsigned long tb_transport_write(unsigned long m, unsigned long off, unsigned long count, unsigned long *out, unsigned long *flags);
unsigned long tb_transport_write_variant(unsigned long m, unsigned long msg2, unsigned long count, unsigned long *out, unsigned long *flags);
unsigned long tb_transport_append_cap(unsigned long reg, unsigned long m, unsigned long *out, unsigned long kind);
unsigned long tb_transport_read(unsigned long reg, unsigned long m, unsigned long obj, unsigned long kind, unsigned long count);
void tb_message_receive(unsigned long reg, void *data, unsigned long *t);
unsigned long tb_message_decode(unsigned long *src, unsigned long expect, unsigned long **out);
void tb_message_commit(unsigned long reg, unsigned long m, unsigned long obj, unsigned long *out);
void tb_msg_capref_handler(unsigned long rec, unsigned long cb, unsigned int *msg);
unsigned char *tb_capref_create(unsigned long a, unsigned long b, unsigned long flags, unsigned long cb);
unsigned long tb_capref_create2(unsigned long a, unsigned long b, unsigned long type, unsigned long cb);
unsigned long tb_get_transport(unsigned long m);
unsigned long tb_transport_end(unsigned long m);
unsigned long tb_get_18(unsigned long m);
void tb_set_18(unsigned long m, unsigned long v);
void tb_set_id(unsigned long m, unsigned long v);
void tb_set_kind8(unsigned long m, unsigned long v);
bool tb_cmp_kind8(unsigned long m, unsigned long v);
unsigned long tb_get_10(unsigned long m);
unsigned long tb_get_48(unsigned long m);
unsigned long tb_slot_get(unsigned long m, long i);
unsigned long tb_slot_push(unsigned long m, unsigned long v);
unsigned long tb_slot_pop(unsigned long m, unsigned long *out);
bool tb_transport_flags_test(unsigned long m, unsigned short mask);
void tb_transport_set_pos(unsigned long m, unsigned long pos);
void tb_transport_copy(unsigned long m, unsigned long dst, unsigned long len);
void tb_transport_start_copy(unsigned long m, unsigned long *start, unsigned long *delta, unsigned long cb);
void tb_transport_copy_region(unsigned long m, unsigned long off, unsigned long len, unsigned long cb);
void tb_claim_buffer(unsigned long size);
void tb_message_reset(unsigned int *m);
void tb_message_set_state(unsigned int *m, unsigned int state);
void tb_message_set_kind(unsigned long m, unsigned char kind);
unsigned long tb_message_init(unsigned int *m, unsigned long transport, unsigned char kind);
void tb_message_set_transport(unsigned long m, unsigned long transport);
void tb_message_state_transition(unsigned int *m);
void tb_message_release(unsigned int *m);
unsigned int *tb_message_for_type(unsigned int *m, unsigned long kind);
unsigned int tb_message_state(unsigned int *m);
unsigned char tb_message_kind(unsigned long m);
unsigned long tb_ok(void);
void tb_transport_alloc_buf(unsigned long m, unsigned long v);
unsigned long tb_transport_create_virt(unsigned long *p, unsigned long *out);
unsigned long tb_transport_create_phys(unsigned long *p);
unsigned long tb_transport_get_or_alloc(unsigned long p);
unsigned long tb_transport_get_or_alloc_b(unsigned long m);
unsigned long tb_transport_alloc(unsigned long *out, unsigned long v);
unsigned long tb_alloc_buffer(unsigned long size, unsigned long kind, unsigned long *out);
#define FUN_00016af0 tb_alloc_buffer
#define FUN_00017a88 tb_capref_create
#define FUN_00017a08 tb_capref_create2
#define FUN_00017c14 tb_msg_capref_handler
#define FUN_0001a11c tb_list_test
#define FUN_0001a138 tb_sorted_lookup
#define FUN_00019490 tb_msg_encode_f32
#define FUN_00019588 tb_msg_decode_f32
#define FUN_00019670 tb_msg_encode_f64
#define FUN_00019768 tb_msg_decode_f64
#define FUN_0001a0d0 tb_slot_set_if_empty
unsigned long tb_resize_buffer(unsigned long *t, unsigned long kind, unsigned long size);
unsigned long tb_f32_size(void);
void tb_msg_encode_f32_chk(void);
unsigned long tb_msg_encode_f32(unsigned int v, int *m);
void tb_msg_decode_f32_chk(void);
unsigned int tb_msg_decode_f32(int *m, unsigned int *out);
unsigned long tb_f64_size(void);
void tb_msg_encode_f64_chk(void);
unsigned long tb_msg_encode_f64(unsigned long v, int *m);
void tb_msg_decode_f64_chk(void);
unsigned long tb_msg_decode_f64(int *m, unsigned long *out);
unsigned long tb_zero(void);
unsigned long long tb_zero128(void);
void tb_register(unsigned long v);
long tb_emit_tag(long *out, long *src);
void tb_slot_set_if_empty(unsigned long v, long *slot, unsigned long cb);
unsigned int tb_list_test(unsigned long h, unsigned long v);
bool tb_sorted_lookup(unsigned long rec, unsigned long key);
void tb_nop(void);
unsigned long tb_identity(unsigned long a, unsigned long b);
unsigned long tb_va_cap_resolve(unsigned long a, unsigned long b, unsigned long addr, unsigned long flags);

/* Global data referenced by the slice. */
extern unsigned long _DAT_004bb180;
extern unsigned long _DAT_004bb190;
extern unsigned long _DAT_004bb1a0;
extern unsigned long _DAT_004bb198;
extern unsigned long _DAT_004bb1a8;
extern void (*DAT_00657fa0)(void);
extern unsigned long _DAT_004bb1b0;
extern unsigned long _DAT_0064c098;
extern unsigned long _LAB_006593e8;

/* String constant addresses (Ghidra s_/DAT_ names, as addresses). */
#define TB_ASSERT_SELF_STATE     ((const char *)0x5abb59)
#define TB_ASSERT_START_LT_MSG   ((const char *)0x5abd19)
#define TB_ASSERT_END_TRANSPORT  ((const char *)0x5abd8e)
#define TB_FATAL_OVERFLOW_ENC    ((const char *)0x5abd5d)
#define TB_FATAL_OVERFLOW_DEC    ((const char *)0x5aae93)
#define TB_ASSERT_DISP           ((const char *)0x5abbac)
#define TB_MESSAGE_C             ((const char *)0x5abb9f)
#define TB_ASSERT_ACCUM_TOTAL    ((const char *)0x5abf4e)
#define TB_FATAL_COPYIN          ((const char *)0x5ac03b)
#define TB_FATAL_ENC_F32         ((const char *)0x5ac8f6)
#define TB_FATAL_DEC_F32         ((const char *)0x5ac926)
#define TB_FATAL_ENC_F64         ((const char *)0x5ac956)
#define TB_FATAL_DEC_F64         ((const char *)0x5ac986)
#define TB_FATAL_SIZE0           ((const char *)0x5ac891)
#define TB_FATAL_OVFL_DEC        ((const char *)0x5ac8c6)
#define TB_FATAL_OVFL_ENC        ((const char *)0x5ac821)
#define DAT_5aacf2               ((const char *)0x5aacf2)
#define DAT_5aae47               ((const char *)0x5aae47)
#define DAT_5ac18d               ((const char *)0x5ac18d)
#define DAT_5ac851               ((const char *)0x5ac851)
#define DAT_5ac6d1               ((const char *)0x5ac6d1)
#define TB_ASSERT_IN_MSG_STATE   ((const char *)0x5ac3ef)

/* ------------------------------------------------------------------ *
 * tb_message / tb_transport core accessors and state machine
 * ------------------------------------------------------------------ */

/* FUN_000157dc @ 0x000157dc   (est. tb_claim_buffer)
 * Ghidra: void FUN_000157dc(long param_1)
 * Allocates a transport buffer of `size` bytes (tag 0x100004077774924) and
 * returns after checking the result is nonzero and non-wrapping. On alloc
 * failure it faults (FUN_004b0498); on a size/result overflow it traps.
 * Confidence: medium | Notes: alloc tag shared with tb_alloc_buffer. */
void tb_claim_buffer(unsigned long size)
{
    unsigned long p = sk_heap_calloc(size, 1, (void *)0x100004077774924);  /* FUN_00010244 */
    if (p <= p + size) {
        if (p == 0) {
            sk_fault_alloc_panic();  /* FUN_004b0498, noreturn */
        }
        if (size != 0) {
            return;
        }
    }
    SoftwareBreakpoint(0x5519, 0x1582c);
}

/* FUN_00015834 @ 0x00015834   (est. tb_message_reset)
 * Ghidra: void FUN_00015834(undefined4 *param_1)
 * Zeroes a tb_message envelope: state=0, kind=0, clears the slot fields, sets
 * the id (@+0x40) to ~0, and resets the transport pointer/region fields.
 * Confidence: high */
void tb_message_reset(unsigned int *m)
{
    m[0] = 0;
    ((unsigned char *)m)[4] = 0;
    ((unsigned long *)m)[1] = 0;     /* +0x08 */
    ((unsigned long *)m)[2] = 0;     /* +0x10 */
    ((unsigned long *)m)[3] = 0;     /* +0x18 */
    ((unsigned long *)m)[4] = ~0ull; /* +0x20 */
    ((unsigned long *)m)[6] = 0;     /* +0x30 */
    ((unsigned long *)m)[5] = 0;     /* +0x28 */
    ((unsigned long *)m)[8] = 0;     /* +0x40 */
    ((unsigned long *)m)[7] = 0;     /* +0x38 */
    ((unsigned long *)m)[9] = 0;     /* +0x48 */
    ((unsigned long *)m)[10] = 0;    /* +0x50 transport ptr */
}

/* FUN_0001585c @ 0x0001585c   (est. tb_message_set_state)
 * Ghidra: void tb_message_set_state(undefined4 *param_1, undefined4 param_2)
 * Stores `state` into the message's state field (+0x00). */
void tb_message_set_state(unsigned int *m, unsigned int state)
{
    m[0] = state;
}

/* FUN_00015864 @ 0x00015864   (est. tb_message_set_kind)
 * Ghidra: void FUN_00015864(long param_1, undefined1 param_2)
 * Stores the message kind/type byte at +0x04. */
void tb_message_set_kind(unsigned long m, unsigned char kind)
{
    *(unsigned char *)(m + 4) = kind;
}

/* FUN_0001586c @ 0x0001586c   (est. tb_message_init)
 * Ghidra: undefined8 tb_message_init(int *param_1, undefined8 param_2, undefined1 param_3)
 * Initializes a tb_message for encoding: asserts state==0, sets state=1,
 * kind=param_3, clears +0x08/+0x0c, links the transport buffer (param_2) at
 * +0x50, sets the two id fields to ~0, and clears the slot array at +0x28
 * (4 entries of 2 words) plus the +0x50 slot. Returns 0.
 * Confidence: high | Notes: TB_ASSERT via FUN_00118b28 + SoftwareBreakpoint. */
unsigned long tb_message_init(unsigned int *m, unsigned long transport, unsigned char kind)
{
    if (m[0] != 0) {
        sk_puts(TB_ASSERT_SELF_STATE);  /* FUN_00118b28, s_...005abb59 */
        SoftwareBreakpoint(1, 0x15904);
    }
    m[0] = 1;
    ((unsigned char *)m)[4] = kind;
    m[2] = 0;                         /* +0x08 */
    m[3] = 0;                         /* +0x0c */
    *(unsigned long *)((unsigned long)m + 0x50) = transport;
    unsigned long *s = (unsigned long *)((unsigned char *)m + 0x48);
    long i = 4;
    m[8] = ~0ull;                     /* +0x20 */
    m[9] = ~0ull;                     /* +0x24 */
    unsigned long *p = (unsigned long *)((unsigned char *)m + 0x28);
    do {
        if (s < p + 2 || p + 2 < p) {
            SoftwareBreakpoint(0x5519, 0x158e0);
        }
        p[0] = 0;
        p[1] = 0;
        i = i - 1;
        p = p + 2;
    } while (i != 0);
    s[0] = 0;
    s[1] = 0;
    return 0;
}

/* FUN_00015904 @ 0x00015904   (est. tb_message_set_transport)
 * Ghidra: void tb_message_set_transport(long param_1, undefined8 param_2)
 * Stores the transport pointer at message+0x50. */
void tb_message_set_transport(unsigned long m, unsigned long transport)
{
    *(unsigned long *)(m + 0x50) = transport;
}

/* FUN_0001590c @ 0x0001590c   (est. tb_message_state_transition)
 * Ghidra: void tb_message_state_transition(int *param_1)
 * Advances the message state machine. For kind 1: from state 1 or 4 -> state 2
 * (complete). For kind 2: state 3/4 are terminal; state 1 -> state 2. For
 * other kinds, any reach here -> state 2. Otherwise faults (invalid state).
 * Confidence: medium | Notes: TB state codes: 1=encode, 4=decode, 2=done. */
void tb_message_state_transition(unsigned int *m)
{
    char kind = (char)m[1];
    if (kind == 1) {
        if (m[0] == 1 || m[0] == 4) goto done;
    } else if (kind == 2) {
        if ((unsigned int)(m[0] - 3U) < 2) {
            return;
        }
        if (m[0] == 1) goto done;
    } else if (kind != 0) {
done:
        m[0] = 2;
        return;
    }
    SoftwareBreakpoint(1, 0x15928);
}

/* FUN_00015964 @ 0x00015964   (est. tb_message_release)
 * Ghidra: void FUN_00015964(undefined4 *param_1)
 * Releases a message: clears kind, transport region/slot fields, resets id to
 * ~0, clears +0x50 transport, and sets state=5 (released).
 * Confidence: high */
void tb_message_release(unsigned int *m)
{
    ((unsigned char *)m)[4] = 0;
    ((unsigned long *)m)[1] = 0;      /* +0x08 */
    ((unsigned long *)m)[4] = ~0ull;  /* +0x20 */
    ((unsigned long *)m)[10] = 0;     /* +0x50 */
    m[0] = 5;
}

/* FUN_00015984 @ 0x00015984   (est. tb_message_for_type)
 * Ghidra: undefined4 * tb_message_for_type(undefined4 *param_1, undefined8 param_2)
 * For kind values 1 or 2, initializes `m` as a decode message (state=4,
 * kind=param_2) and returns it. For any other kind, resolves a cached
 * transport via FUN_004b0558 and returns its +0x50 transport pointer.
 * Confidence: medium | Notes: kind bytes map to a transport object table. */
unsigned int *tb_message_for_type(unsigned int *m, unsigned long kind)
{
    if ((((unsigned int)kind - 1U) & 0xff) < 2) {
        m[0] = 4;
        ((char *)m)[4] = (char)kind;
        return m;
    }
    unsigned long t = (unsigned long)FUN_004b0558(kind);
    return *(unsigned int **)(t + 0x50);
}

/* FUN_000159b8 @ 0x000159b8   (est. tb_get_transport)
 * Ghidra: undefined8 tb_get_transport(long param_1)
 * Returns the transport-buffer descriptor pointer stored at +0x50. */
unsigned long tb_get_transport(unsigned long m)
{
    return *(unsigned long *)(m + 0x50);
}

/* FUN_000159c0 @ 0x000159c0   (est. tb_message_state)
 * Ghidra: undefined4 FUN_000159c0(undefined4 *param_1)
 * Returns the message's current state (+0x00). */
unsigned int tb_message_state(unsigned int *m)
{
    return m[0];
}

/* FUN_000159c8 @ 0x000159c8   (est. tb_message_kind)
 * Ghidra: undefined1 FUN_000159c8(long param_1)
 * Returns the message kind/type byte at +0x04. */
unsigned char tb_message_kind(unsigned long m)
{
    return *(unsigned char *)(m + 4);
}

/* FUN_000159d0 @ 0x000159d0   (est. tb_transport_end)
 * Ghidra: undefined8 tb_transport_end(long param_1)
 * Returns the transport descriptor's end/limit field (+0x18) — the total
 * capacity in bytes. */
unsigned long tb_transport_end(unsigned long m)
{
    return *(unsigned long *)(*(unsigned long *)(m + 0x50) + 0x18);
}

/* FUN_000159dc @ 0x000159dc   (est. tb_transport_start_copy)
 * Ghidra: void FUN_000159dc(long param_1, ulong *param_2, long *param_3, long param_4)
 * Begins an outbound transport-buffer copy. Records the transport's base
 * (+0x10 field) into *param_2, then via a vtable call (param_4+0x10) queries
 * the current end-of-data; stores the delta (end - start) into *param_3.
 * If data remains, allocates a transport region via FUN_004b0570, validates
 * bounds with TB_ASSERT checks, and issues the write through the same vtable
 * entry. Falls to FUN_0011d7e8 on stack-corruption/error.
 * Confidence: low | Notes: transport descriptor vtable at param_4+0x10;
 *   canary 0xd2c8502b44bfffed6. */
void tb_transport_start_copy(unsigned long m, unsigned long *start,
                             unsigned long *delta, unsigned long cb)
{
    *start = *(unsigned long *)(*(unsigned long *)(m + 0x50) + 0x10);
    (**(unsigned long (**)(unsigned long))(cb + 0x10))(cb);
    unsigned long end = *(unsigned long *)(*(unsigned long *)(m + 0x50) + 0x10);
    unsigned long s = *start;
    *delta = end - s;
    if (s <= end) {
        return;
    }
    unsigned long acc[3];
    unsigned long region[11];
    unsigned long reg[16];
    long canary = -0x2c8502b44bfffed6;
    unsigned long *t = *(unsigned long **)((unsigned long)FUN_004b0570() + 0x50);
    unsigned long limit = t[3];
    if (limit < s) {
        sk_puts(TB_ASSERT_START_LT_MSG);  /* FUN_00118b28, s_...005abd19 */
    } else {
        if (s + *delta < s) {
            FUN_004b05a0();
        } else if (s + *delta <= limit) {
            unsigned long base = *(unsigned long *)t[0];
            acc[0] = base + s;
            if ((unsigned long *)(limit - s) < (unsigned long *)*delta ||
                base + limit < acc[0] || acc[0] < base) {
                SoftwareBreakpoint(0x5519, 0x15aa8);
            }
            acc[1] = 0;
            acc[2] = 0;
            /* Build a small region descriptor and dispatch the write. */
            unsigned int hdr[2];
            unsigned long args[14];
            hdr[0] = 4;                    /* disposition = TB_MES_... */
            ((unsigned char *)hdr)[4] = 2;
            args[0] = 0;
            args[1] = *(unsigned long *)((unsigned long)FUN_004b0570() + 0x10);
            args[2] = 0;
            args[3] = *(unsigned long *)((unsigned long)FUN_004b0570() + 0x20);
            args[4] = 0;
            args[5] = 0;
            args[6] = 0;
            args[7] = (unsigned long)acc;
            args[8] = 0;
            args[9] = *delta;
            (**(unsigned long (**)(unsigned long, void *))(cb + 0x10))(cb, &args);
            if (canary == -0x2c8502b44bfffed6) {
                return;
            }
            FUN_0011d7e8(0);  /* noreturn */
        }
        sk_puts(TB_ASSERT_END_TRANSPORT);  /* s_...005abd8e */
    }
    FUN_00118b28(0);
    SoftwareBreakpoint(1, 0x15b80);
}

/* FUN_00015a44 @ 0x00015a44   (est. tb_transport_copy_region)
 * Ghidra: void FUN_00015a44(long param_1, ulong param_2, ulong param_3, long param_4)
 * Copies a transport-buffer region starting at offset `off` of `len` bytes
 * through the callback `cb` vtable. Validates off/len against the transport
 * limits (TB_ASSERT start<transport, end<transport) and issues the write.
 * Confidence: low | Notes: variant of tb_transport_start_copy with explicit
 *   offset/len; canary 0xd2c8502b44bfffed6. */
void tb_transport_copy_region(unsigned long m, unsigned long off,
                              unsigned long len, unsigned long cb)
{
    unsigned long acc[4];
    unsigned long args[15];
    long canary = -0x2c8502b44bfffed6;
    unsigned long *t = *(unsigned long **)(m + 0x50);
    unsigned long limit = t[3];
    if (limit < off) {
        sk_puts(TB_ASSERT_START_LT_MSG);
    } else {
        if (off + len < off) {
            FUN_004b05a0();
        } else if (off + len <= limit) {
            unsigned long base = *(unsigned long *)t[0];
            acc[0] = base + off;
            if ((limit - off < len || base + limit < acc[0]) || acc[0] < base) {
                SoftwareBreakpoint(0x5519, 0x15aa8);
            }
            acc[1] = 0;
            acc[2] = 0;
            acc[3] = len;
            unsigned int hdr[2];
            hdr[0] = 4;
            ((unsigned char *)hdr)[4] = 2;
            args[0] = 0;
            args[1] = *(unsigned long *)(m + 0x10);
            args[2] = 0;
            args[3] = *(unsigned long *)(m + 0x20);
            args[4] = 0;
            args[5] = 0;
            args[6] = 0;
            args[7] = (unsigned long)acc;
            args[8] = 0;
            (**(unsigned long (**)(unsigned long, void *))(cb + 0x10))(cb, &args);
            if (canary == -0x2c8502b44bfffed6) {
                return;
            }
            FUN_0011d7e8(0);
        }
        sk_puts(TB_ASSERT_END_TRANSPORT);
    }
    FUN_00118b28(0);
    SoftwareBreakpoint(1, 0x15b80);
}

/* FUN_00015b84 @ 0x00015b84   (est. tb_set_id)
 * Ghidra: void tb_set_id(long param_1, undefined8 param_2)
 * Stores a word at +0x10. */
void tb_set_id(unsigned long m, unsigned long v)
{
    *(unsigned long *)(m + 0x10) = v;
}

/* FUN_00015b8c @ 0x00015b8c   (est. tb_set_kind8)
 * Ghidra: void FUN_00015b8c(long param_1, undefined8 param_2)
 * Stores a word at +0x08. */
void tb_set_kind8(unsigned long m, unsigned long v)
{
    *(unsigned long *)(m + 8) = v;
}

/* FUN_00015b94 @ 0x00015b94   (est. tb_cmp_kind8)
 * Ghidra: bool FUN_00015b94(long param_1, long param_2)
 * Returns whether the word at +0x08 equals `v`. */
bool tb_cmp_kind8(unsigned long m, unsigned long v)
{
    return *(unsigned long *)(m + 8) == v;
}

/* FUN_00015ba4 @ 0x00015ba4   (est. tb_get_18)
 * Ghidra: undefined8 tb_get_18(long param_1)
 * Returns the word at +0x18 (the message's object/type id). */
unsigned long tb_get_18(unsigned long m)
{
    return *(unsigned long *)(m + 0x18);
}

/* FUN_00015bac @ 0x00015bac   (est. tb_set_18)
 * Ghidra: void tb_set_18(long param_1, undefined8 param_2)
 * Stores a word at +0x18. */
void tb_set_18(unsigned long m, unsigned long v)
{
    *(unsigned long *)(m + 0x18) = v;
}

/* FUN_00015bb4 @ 0x00015bb4   (est. tb_get_48)
 * Ghidra: undefined8 FUN_00015bb4(long param_1)
 * Returns the word at +0x48 (slot array high bound). */
unsigned long tb_get_48(unsigned long m)
{
    return *(unsigned long *)(m + 0x48);
}

/* FUN_00015bbc @ 0x00015bbc   (est. tb_slot_get)
 * Ghidra: undefined8 FUN_00015bbc(long param_1, long param_2)
 * Returns slot `i` of the message slot array at +0x28, bounds-checked against
 * the array end at +0x48. Traps if out of range.
 * Confidence: medium */
unsigned long tb_slot_get(unsigned long m, long i)
{
    unsigned long *p = (unsigned long *)(m + 0x28) + i;
    unsigned long *base = (unsigned long *)(m + 0x28);
    unsigned long *end = (unsigned long *)(m + 0x48);
    if (base <= p && p + 1 <= end && p <= p + 1) {
        return *p;
    }
    SoftwareBreakpoint(0x5519, 0x15be8);
}

/* FUN_00015be8 @ 0x00015be8   (est. tb_slot_push)
 * Ghidra: undefined8 FUN_00015be8(long param_1, ulong param_2)
 * Appends `v` to the message slot array (+0x28, capacity 4 words, high bound
 * at +0x48). Returns 0 on success or 6 when the array is full.
 * Confidence: medium */
unsigned long tb_slot_push(unsigned long m, unsigned long v)
{
    unsigned long *end = (unsigned long *)(m + 0x48);
    unsigned long n = *end;
    if (3 < n) {
        return 6;
    }
    unsigned long off = m + n * 8;
    unsigned long *p = (unsigned long *)(off + 0x28);
    unsigned long *p2 = (unsigned long *)(off + 0x30);
    if (p2 <= end && p <= p2) {
        *p = v;
        *end = n + 1;
        return 0;
    }
    SoftwareBreakpoint(0x5519, 0x15c30);
}

/* FUN_00015c30 @ 0x00015c30   (est. tb_slot_pop)
 * Ghidra: undefined8 FUN_00015c30(long param_1, long *param_2)
 * Pops the first slot from the message slot array into *param_2, shifting the
 * remaining slots left. Returns 0 on success or 7 when empty.
 * Confidence: medium */
unsigned long tb_slot_pop(unsigned long m, unsigned long *out)
{
    unsigned long *end = (unsigned long *)(m + 0x48);
    unsigned long n = *end;
    if (n == 0) {
        return 7;
    }
    unsigned long *base = (unsigned long *)(m + 0x28);
    *out = *base;
    unsigned long *p = base;
    for (unsigned long i = n - 1; i != 0; i = i - 1) {
        unsigned long *nxt = p + 1;
        unsigned long *nn = p + 2;
        if ((((nxt < base || end < nn) || nn < nxt) || nxt <= p) &&
            (((nxt < base || end < nn) || nn < nxt) || p != nxt))
            goto bad;
        *p = p[1];
        p = p + 1;
    }
    p = base + n;
    unsigned long *last = p - 1;
    if ((base <= last && p <= end) && last <= p) {
        *last = 0;
        *end = n - 1;
        return 0;
    }
bad:
    SoftwareBreakpoint(0x5519, 0x15cbc);
}

/* FUN_00015cbc @ 0x00015cbc   (est. tb_transport_flags_test)
 * Ghidra: bool tb_transport_flags_test(long param_1, ushort param_2)
 * Returns whether any bit in `mask` is set in the transport descriptor's flag
 * word at +0x2a. */
bool tb_transport_flags_test(unsigned long m, unsigned short mask)
{
    return (*(unsigned short *)(*(unsigned long *)(m + 0x50) + 0x2a) & mask) != 0;
}

/* FUN_00015cd0 @ 0x00015cd0   (est. tb_transport_set_pos)
 * Ghidra: void tb_transport_set_pos(long param_1, undefined8 param_2)
 * Sets the transport descriptor's position field at +0x10. */
void tb_transport_set_pos(unsigned long m, unsigned long pos)
{
    *(unsigned long *)(*(unsigned long *)(m + 0x50) + 0x10) = pos;
}

/* FUN_00015cdc @ 0x00015cdc   (est. tb_ok)
 * Ghidra: undefined8 FUN_00015cdc(void)
 * Returns 0 (success). */
unsigned long tb_ok(void)
{
    return 0;
}

/* FUN_00015ce4 @ 0x00015ce4   (est. tb_transport_copy)
 * Ghidra: void FUN_00015ce4(long param_1, long param_2, ulong param_3)
 * Copies `len` bytes between two transport buffers (src at param_1+0x50, dst
 * at param_2+0x50). Validates both ranges, copies via FUN_00117cc4, and
 * advances both positions. Traps on overflow or out-of-range.
 * Confidence: low | Notes: TB_ASSERT src_end/dst_end banners. */
void tb_transport_copy(unsigned long m, unsigned long dst, unsigned long len)
{
    unsigned long *src = *(unsigned long **)(m + 0x50);
    unsigned long spos = src[2];
    if (spos + len < spos) {
        FUN_004b05e8();
    } else {
        unsigned long slimit = src[3];
        if (spos + len <= slimit) {
            unsigned long *dstt = *(unsigned long **)(dst + 0x50);
            unsigned long dpos = dstt[2];
            if (dpos + len < dpos) {
                FUN_004b05c4();
            } else {
                unsigned long dlimit = dstt[3];
                if (dpos + len <= dlimit) {
                    unsigned long dbase = *dstt;
                    unsigned long daddr = dbase + dpos;
                    unsigned long sbase = *src;
                    unsigned long saddr = sbase + spos;
                    bool a = saddr <= sbase + slimit;
                    bool b = daddr < dbase + dlimit;
                    bool c = daddr == dbase + dlimit;
                    bool ok = ((((a && sbase <= saddr) && len <= slimit - spos) &&
                                (b || c)) && dbase < daddr) &&
                               (len < dlimit - dpos || len == dlimit - dpos);
                    if (ok) {
                        FUN_00117cc4(daddr, saddr, len);
                        src[2] = src[2] + len;
                        dstt[2] = dstt[2] + len;
                        return;
                    }
                    SoftwareBreakpoint(0x5519, 0x15d78);
                }
            }
            sk_puts(TB_ASSERT_END_TRANSPORT);  /* s_...005abe0a dst_end */
            goto fatal;
        }
    }
    sk_puts(TB_ASSERT_START_LT_MSG);  /* s_...005abdcf src_end */
fatal:
    FUN_00118b28(0);
    SoftwareBreakpoint(1, 0x15e08);
}

/* FUN_00015e08 @ 0x00015e08   (est. tb_fatal_disposition)
 * Ghidra: void FUN_00015e08(ulong param_1)
 * Emits a TB_ASSERT "disposition == TB_MES..." banner with a stack trace tag
 * (kind 0x9a, "tb_message_c") and traps.
 * Confidence: medium */
void tb_fatal_disposition(unsigned long v)
{
    unsigned long tag = 0x9a;
    unsigned long val = v & 0xff;
    const char *cls = TB_MESSAGE_C;   /* s_tb_message_c_005abb9f */
    FUN_00118b28(TB_ASSERT_DISP);     /* s_...005abbac */
}

/* FUN_00015e2c @ 0x00015e2c   (est. tb_fatal_overflow)
 * Ghidra: void FUN_00015e2c(undefined8 param_1)
 * Emits the TB_FATAL "overflow detected when ..." banner and returns.
 * Confidence: medium */
void tb_fatal_overflow(unsigned long v)
{
    FUN_00118b28(TB_FATAL_OVERFLOW_ENC);  /* s_...005abd5d */
}

/* FUN_00015e3c @ 0x00015e3c   (est. tb_copyin_size)
 * Ghidra: void tb_copyin_size(undefined8 param_1, undefined8 *param_2)
 * Validates a copyin of *param_2 bytes (FUN_00015108 with tag 0x659088). On
 * failure releases the referenced objects (FUN_004b060c then release of the
 * +0x18 cap and the record via thunk_FUN_00012568).
 * Confidence: low | Notes: tag 0x659088; release tail. */
void tb_copyin_size(unsigned long m, unsigned long *rec)
{
    unsigned long r = FUN_00015108(m, *rec, (unsigned long)rec, 0x659088);
    if ((r & 1) != 0) {
        return;
    }
    FUN_004b060c();
    thunk_FUN_00012568((void *)*(unsigned long *)((unsigned long)0 + 0x18));
    thunk_FUN_00012568((void *)0);
}

/* FUN_00015e9c @ 0x00015e9c   (est. tb_acquire_buffer)
 * Ghidra: ulong * FUN_00015e9c(undefined8 param_1, long param_2)
 * Acquires (or grows) the transport buffer for `m`, appending the source
 * transport's data. Returns a new transport record, or 0. Handles the
 * accumulate/copy of the source, plus optional notification-record setup when
 * the source flags bit 1 is set. Falls to TB_ASSERT "accumulator->total_si..."
 * on overflow.
 * Confidence: low | Notes: heavy alloc/copy; tags 0x1010040313bcfeb,
 *   0x100004077774924, 0xa8ccd261, 0x1090040b6685729. */
unsigned long *tb_acquire_buffer(unsigned long m, unsigned long m2)
{
    unsigned long *dst = (unsigned long *)tb_get_transport(m2);
    unsigned long *acc = (unsigned long *)FUN_00015264(m, *(unsigned long *)(m2 + 0x18));
    unsigned long *cap;
    if (acc == 0) {
        acc = (unsigned long *)sk_heap_calloc(1, 0x20, (void *)0x1010040313bcfeb);  /* FUN_00010244 */
        if (acc == 0) {
            FUN_004b066c();
            FUN_004b0714();
        } else {
            *acc = *(unsigned long *)(m2 + 0x18);
            if ((long)dst[3] < 0) { FUN_004b0714(); }
            unsigned long n = dst[3] * 2;
            unsigned long p = FUN_00010244(n, 1, 0x100004077774924);
            if (p + n < p) { FUN_004b0714(); }
            if (p != 0) {
                acc[2] = n;
                acc[3] = p;
                tb_copyin_size(m, acc);
            } else {
                FUN_004b06c0();
            }
        }
    } else {
        unsigned long t = tb_get_transport(m2);
        unsigned long cur = acc[1];
        unsigned long need = cur + *(unsigned long *)(t + 0x18);
        if (cur + *(unsigned long *)(t + 0x18) < cur) {
            FUN_004b06e4();
            FUN_004b0690();
            FUN_00118b28(TB_ASSERT_ACCUM_TOTAL);
            SoftwareBreakpoint(1, 0x16104);
        }
        unsigned long cap = acc[2];
        if (cap < need) {
            unsigned long np = FUN_000102f4(acc[3], need, 0xa8ccd261);
            if (np + need < np) { FUN_004b0714(); }
            if (np == 0) {
                FUN_004b06c0();
                FUN_004b066c();
                FUN_004b0714();
            }
            acc[2] = need;
            acc[3] = np;
            cur = acc[1];
            cap = need;
        }
        unsigned long srclen = dst[3];
        if (cur + srclen < cur) { FUN_004b06e4(); }
        if (cap < cur + srclen) { FUN_004b0690(); }
        unsigned long buf = acc[3];
        unsigned long d = buf + cur;
        if ((buf + cap < d || d < buf) || cap - cur < srclen ||
            FUN_00117cc4(d, *dst, srclen), d + srclen < d) {
            SoftwareBreakpoint(0x5519, 0x1600c);
        }
        acc[1] = acc[1] + dst[3];
        if ((*(unsigned char *)((unsigned long)dst + 0x2a) >> 1 & 1) == 0) {
            return 0;
        }
        unsigned long *rec = (unsigned long *)FUN_00010244(1, 0x68, 0x1090040b6685729);
        if (rec != 0) {
            int r = FUN_00014c18((unsigned long)rec, acc[1]);
            if (r == 0) {
                unsigned long n = acc[1];
                if (n <= (unsigned long)acc[2] && n <= rec[3]) {
                    unsigned long base = *rec;
                    FUN_00117cc4(base, acc[3], n);
                    if (base <= base + n) {
                        FUN_000151c8(m, *acc);
                        return rec;
                    }
                }
                SoftwareBreakpoint(0x5519, 0x16008);
            }
            FUN_004b063c();
        }
        FUN_004b066c();
        FUN_004b063c();
        unsigned long *r2 = (unsigned long *)FUN_00118b28(DAT_5aacf2);
        return r2;
    }
    FUN_004b066c();
    FUN_004b063c();
    unsigned long *r3 = (unsigned long *)FUN_00118b28(DAT_5aacf2);
    return r3;
}

/* FUN_0001611c @ 0x0001611c   (est. tb_panic_msg)
 * Ghidra: void FUN_0001611c(undefined8 param_1)
 * Emits the buffer-error banner (DAT_005aacf2). */
void tb_panic_msg(unsigned long v)
{
    FUN_00118b28(DAT_5aacf2);
}

/* FUN_0001612c @ 0x0001612c   (est. tb_get_10)
 * Ghidra: undefined8 tb_get_10(long param_1)
 * Returns the word at +0x10. */
unsigned long tb_get_10(unsigned long m)
{
    return *(unsigned long *)(m + 0x10);
}

/* FUN_00016134 @ 0x00016134   (est. tb_transport_get_or_alloc)
 * Ghidra: undefined8 tb_transport_get_or_alloc(undefined8 *param_1)
 * Returns the current transport's base if it exists; otherwise allocates a
 * fresh 0x20-byte transport record (tag 0x108004047936fdf), registers it, and
 * returns it (cleaning up on registration failure).
 * Confidence: low | Notes: alloc tag 0x108004047936fdf. */
unsigned long tb_transport_get_or_alloc(unsigned long p)
{
    if ((*(unsigned char *)(p + 0x18) & 1) != 0) {
        return *(unsigned long *)p;
    }
    unsigned long t = (unsigned long)FUN_004b07c0();
    if ((*(unsigned char *)(t + 0x18) & 1) != 0) {
        return *(unsigned long *)(t + 8);
    }
    unsigned long *rec = (unsigned long *)FUN_00010244(1, 0x20, 0x108004047936fdf);
    if (rec == 0) {
        FUN_004b0068();
    }
    *(unsigned long *)((unsigned long)rec + 0x10) = 0;
    *(unsigned char *)((unsigned long)rec + 0x18) = 0;
    if (rec <= rec + 0x20) {
        FUN_004b07f0();  /* stores rec into the current-transport slot */
        unsigned long r = tb_transport_create_virt(rec, 0);
        if ((int)r != 0) {
            FUN_004b0744((unsigned long)rec);
        }
        return r;
    }
    SoftwareBreakpoint(0x5519, 0x16204);
}

/* FUN_00016154 @ 0x00016154   (est. tb_transport_get_or_alloc_b)
 * Ghidra: undefined8 tb_transport_get_or_alloc_b(long param_1)
 * Same as tb_transport_get_or_alloc but keyed off the existing record at
 * param_1+0x18. */
unsigned long tb_transport_get_or_alloc_b(unsigned long m)
{
    if ((*(unsigned char *)(m + 0x18) & 1) != 0) {
        return *(unsigned long *)(m + 8);
    }
    unsigned long *rec = (unsigned long *)FUN_00010244(1, 0x20, 0x108004047936fdf);
    if (rec != 0) {
        *(unsigned long *)((unsigned long)rec + 0x10) = 0;
        *(unsigned char *)((unsigned long)rec + 0x18) = 0;
        if (rec <= rec + 0x20) {
            FUN_004b07f0();
            unsigned long r = tb_transport_create_virt(rec, 0);
            if ((int)r != 0) {
                FUN_004b0744((unsigned long)rec);
            }
            return r;
        }
        SoftwareBreakpoint(0x5519, 0x16204);
    }
    FUN_004b0068();
}

/* FUN_00016174 @ 0x00016174   (est. tb_transport_alloc)
 * Ghidra: undefined8 tb_transport_alloc(ulong *param_1, undefined8 param_2)
 * Allocates a fresh 0x20-byte transport record, links value `v` at +0x10,
 * stores it in *param_1, registers it, and returns the registration result.
 * Confidence: medium | Notes: alloc tag 0x108004047936fdf. */
unsigned long tb_transport_alloc(unsigned long *out, unsigned long v)
{
    unsigned long *rec = (unsigned long *)FUN_00010244(1, 0x20, 0x108004047936fdf);
    if (rec == 0) {
        FUN_004b0068();
    }
    *(unsigned long *)((unsigned long)rec + 0x10) = v;
    *(unsigned char *)((unsigned long)rec + 0x18) = 0;
    if (rec <= rec + 0x20) {
        *out = (unsigned long)rec;
        unsigned long r = tb_transport_create_virt(rec, 0);
        if ((int)r != 0) {
            FUN_004b0744((unsigned long)rec);
        }
        return r;
    }
    SoftwareBreakpoint(0x5519, 0x16204);
}

/* FUN_00016208 @ 0x00016208   (est. tb_transport_create_virt)
 * Ghidra: undefined8 tb_transport_create_virt(ulong *param_1, ulong *param_2)
 * Creates a virtual-address transport buffer of param_1[2] bytes (tag
 * 0x100004077774924) by invoking a boot-object method (FUN_00034a2c +0x30) to
 * map it. On success sets param_1[3] flag, stores the base and a 0x4000 size
 * marker, and (if param_2 given) stores the base. Returns 0 or 0xd on failure.
 * Confidence: medium | Notes: vtable method at obj+0x30; panic FUN_00054354. */
unsigned long tb_transport_create_virt(unsigned long *p, unsigned long *out)
{
    if ((p[3] & 1) == 0) {
        unsigned long req[2];
        unsigned long op[2];
        unsigned char kind = 0x11;
        unsigned long tag = _DAT_004bb198;
        unsigned long loc = _DAT_004bb190;
        unsigned long obj = (unsigned long)FUN_00034a2c();
        unsigned char ok = (**(unsigned char (***)(unsigned long, unsigned long, void *, void *, unsigned long, unsigned long))(obj + 0x30))
            (*(unsigned long *)obj, 0x1808, &kind, &req, 0, 0);
        if (ok == 0) {
            unsigned long base = 0;
            if (req[1] == 0) {
                FUN_00054354();
            }
            (**(unsigned long (**)(unsigned long, void *))(req[1] + 8))(req[0], &op);
            unsigned long b = op[0];
            unsigned char ok2 = (**(unsigned char (**)(unsigned long, unsigned long, unsigned long))(req[1] + 0x28))(req[0], 0, p[2]);
            if (ok2 == 0) {
                if ((b != 0) && (b + loc <= b)) {
                    SoftwareBreakpoint(0x5519, 0x16318);
                }
                *(unsigned char *)(p + 3) = 1;
                *p = b;
                p[1] = 0x4000;
                if (out == 0) {
                    return 0;
                }
                *out = b;
                return 0;
            }
        }
    }
    return 0xd;
}

/* FUN_00016318 @ 0x00016318   (est. tb_transport_create_phys)
 * Ghidra: undefined8 tb_transport_create_phys(ulong *param_1)
 * Creates a physically-backed transport buffer: maps a physical page via the
 * boot object, allocates a 0x20 transport record, and stores base/size/marker.
 * Returns 0 or 0xd.
 * Confidence: medium | Notes: boot methods at +0x30 and +0x40; phys alloc
 *   FUN_00034f70. */
unsigned long tb_transport_create_phys(unsigned long *p)
{
    unsigned long req[2];
    unsigned long *op = 0;
    unsigned char kind = 0x11;
    unsigned long tag = _DAT_004bb198;
    unsigned long loc = _DAT_004bb190;
    unsigned long obj = (unsigned long)FUN_00034a2c();
    unsigned char ok = (**(unsigned char (***)(unsigned long, unsigned long, void *, void *, unsigned long, unsigned long))(obj + 0x30))
        (*(unsigned long *)obj, 0x28, &kind, &req, 0, 0);
    if (ok == 0) {
        unsigned long base = 0;
        if (op == 0) {
            FUN_00054354();
        }
        (*(unsigned long (**)(unsigned long, void *))op[1])(req[0], &base);
        unsigned long b = *(unsigned long *)&base;
        unsigned long phys = FUN_00034f70();
        obj = (unsigned long)FUN_00034a2c();
        unsigned char ok2 = (**(unsigned char (***)(unsigned long, unsigned long, unsigned long, unsigned long))(obj + 0x40))
            (*(unsigned long *)obj, b, 1, phys);
        if (ok2 == 0) {
            unsigned long *rec = (unsigned long *)FUN_00010244(1, 0x20, 0x108004047936fdf);
            if (rec == 0) {
                FUN_004b0068();
            }
            *rec = b;
            rec[1] = 0x4000;
            rec[2] = phys;
            *(unsigned char *)(rec + 3) = 1;
            if (rec <= rec + 4) {
                *p = (unsigned long)rec;
                return 0;
            }
            SoftwareBreakpoint(0x5519, 0x16450);
        }
        (*(unsigned long (**)(unsigned long))op[0])(req[0]);
    }
    return 0xd;
}

/* FUN_00016458 @ 0x00016458   (est. tb_channel_create)
 * Ghidra: long FUN_00016458(undefined8 param_1)
 * Allocates a tb_channel (0x118 bytes, tag 0x10e0040f252f50e) with an embedded
 * transport record (0x70 bytes, tag 0x10a0040464bf099), initializing the
 * transport (FUN_00015440/FUN_00015450) and its object id (FUN_0001505c).
 * Returns the channel pointer.
 * Confidence: medium | Notes: object type tag 0x6590a8; aux-flag bit2 check. */
unsigned long tb_channel_create(unsigned long kind)
{
    unsigned long ch = FUN_00010244(1, 0x118, 0x10e0040f252f50e);
    if (ch == 0) {
        FUN_004b0068();
    }
    unsigned long *rec = (unsigned long *)FUN_00010244(1, 0x70, 0x10a0040464bf099);
    if (rec != 0) {
        *(unsigned long **)(ch + 0x80) = rec;
        *(unsigned long *)(ch + 0x60) = 0x6590a8;
        unsigned long v = FUN_00015440(kind);
        *rec = v;
        unsigned long flag = FUN_00015450(kind);
        if ((flag >> 2 & 1) != 0) {
            *(unsigned char *)(rec + 0xc) = 1;
        }
        unsigned long id = FUN_0001505c();
        rec[0xd] = id;
        return ch;
    }
    FUN_004b0068();
}

/* FUN_0001650c @ 0x0001650c   (est. tb_transport_recv)
 * Ghidra: undefined8 FUN_0001650c(long param_1, int *param_2, undefined8 *param_3, ulong *param_4)
 * Receives data into the transport buffer of `m` (state 3 path). Copies the
 * source transport into a fresh/destination transport, handling chunked
 * copy-in via FUN_00016d78/00016e1c, notification records (FUN_00016174), and
 * final state transitions. Returns an error code (0 on success).
 * Confidence: low | Notes: large function; source transport via +0x80;
 *   CallSupervisor(1)/(4); flags in param_4. */
unsigned long tb_transport_recv(unsigned long m, unsigned int *state,
                                unsigned long **out, unsigned long *flags)
{
    unsigned long *rec = 0;
    if (*state == 3) {
        unsigned long ch = *(unsigned long *)(m + 0x80);
        unsigned long *dst = (unsigned long *)tb_get_transport((unsigned long)state);
        if (*(unsigned long *)(dst + 0x18) < 0x191) {
            unsigned long *src = (unsigned long *)tb_get_transport((unsigned long)state);
            unsigned long ph = ((unsigned long)flags >> 1 & 1) ? FUN_00034f70() : 0;
            unsigned short f = *(unsigned short *)((unsigned long)src + 0x2a);
            unsigned long l = FUN_000132d4(src[3]);
            unsigned long l2 = FUN_000132e0((void *)*src, src[3]);
            if (l == l2) {
                if (ph != 0) {
                    FUN_0005edac(0, ph);
                }
                unsigned long nr = FUN_0005ee58(l, 0, f, 0);
                unsigned long r = FUN_000639a0(ch, &nr);
                if (r == 0) {
                    tb_transport_copy_obj(nr, (unsigned long)state);
                    unsigned long r2 = FUN_0005ee40(nr);
                    if (r2 != 0) {
                        tb_transport_alloc(&rec, ph);
                    }
                }
                if (((unsigned long)flags & 2) != 0) goto next;
                goto finish;
            }
            goto err;
        }
        unsigned char one = 1;
        unsigned long l = FUN_000132d4(1);
        unsigned long *ph = (unsigned long *)FUN_00034f70();
        FUN_0005edac(0, (unsigned long)ph);
        unsigned long l2 = FUN_000132e0(&one, 1);
        if (l2 == l) {
            unsigned long nr = FUN_0005ee58(l, 0, 0x20, 0);
            unsigned long r = FUN_000639a0(ch, &nr);
            if (r == 0) {
                while (r = FUN_0005ee40(nr), r != 0) {
                    unsigned long cur = tpidrro_el0;
                    unsigned long cnt = *(unsigned long *)(cur + 0x1e0);
                    FUN_0005edac(0, 0);
                    if (cnt == 0) break;
                    unsigned long *ph2 = (unsigned long *)FUN_00034f70();
                    if (ph2 == 0) goto errb;
                    CallSupervisor(1);
                    if ((cnt & 0xff) != 0) goto errc;
                    FUN_004b23d8((unsigned long)ph, (unsigned long)ph2);
                    unsigned long *rec2 = 0;
                    int r3 = tb_transport_alloc(&rec2, (unsigned long)ph2);
                    unsigned long *recp = rec2;
                    if (r3 != 0) goto finish2;
                    rec = rec2;
                    unsigned long *src = (unsigned long *)tb_get_transport((unsigned long)state);
                    unsigned short f2 = *(unsigned short *)((unsigned long)src + 0x2a);
                    unsigned long srclen = src[3];
                    unsigned long cap = tb_transport_get_or_alloc_b((unsigned long)recp);
                    unsigned long n = srclen;
                    if (cap <= srclen) n = cap;
                    if ((src[3] < n) ||
                        (FUN_00117cc4(*recp, *src, n), (unsigned long)recp[0] + n < (unsigned long)recp[0])) {
                        SoftwareBreakpoint(0x5519, 0x16a1c);
                    }
                    tb_transport_set_pos((unsigned long)state, n);
                    unsigned long sz16 = FUN_000132d4(0x18);
                    unsigned long sz16b = FUN_000132e0(&nr, 0x18);
                    if (sz16 != sz16b) goto erre;
                    unsigned long *rec3 = (unsigned long *)FUN_0005ee58(sz16, 0, f2 | 0x20, 0);
                    unsigned long r4 = FUN_000639a0(ch, &rec3);
                    if (r4 == 0) {
                        srclen = srclen - n;
                        do {
                            if (srclen == 0) {
                                tb_transport_copy_obj((unsigned long)rec3, (unsigned long)state);
                                break;
                            }
                            unsigned long n2 = srclen;
                            if (cap <= srclen) n2 = cap;
                            unsigned long saddr = (unsigned long)recp[0];
                            unsigned long dpos = (unsigned long)src[2];
                            if ((src[3] - src[2] < n2) ||
                                (FUN_00117cc4(saddr, *src + dpos, n2), saddr + n2 < saddr)) {
                                SoftwareBreakpoint(0x5519, 0x16a1c);
                            }
                            tb_transport_set_pos((unsigned long)state, src[2] + n2);
                            unsigned long sz16c = FUN_000132d4(0x18);
                            unsigned long sz16d = FUN_000132e0(&nr, 0x18);
                            if (sz16c != sz16d) goto errf;
                            srclen = srclen - n2;
                            rec3 = (unsigned long *)FUN_0005ee58(sz16c, 0, f2 | 0x20, 0);
                            r4 = FUN_000639a0(ch, &rec3);
                        } while (r4 == 0);
                    }
                    if (((unsigned long)flags & 2) == 0) goto finish;
next:
                    if (out == 0) {
                        FUN_004b0744((unsigned long)rec);
                        return 4;
                    }
                    int hb = tb_transport_flags_test((unsigned long)state, 0x20);
                    if (hb == 0) {
                        tb_transport_set_pos((unsigned long)state, 0);
                        tb_message_set_state(state, 4);
                        *out = (unsigned long *)state;
                        goto finish;
                    }
                    unsigned long *src2 = (unsigned long *)tb_get_transport((unsigned long)state);
                    unsigned long msgend = tb_transport_end((unsigned long)state);
                    if (msgend < 0x10) goto errg;
                    unsigned long *data = (unsigned long *)*src2;
                    unsigned long *tail = (unsigned long *)data[1];
                    unsigned long *head = (unsigned long *)*data;
                    unsigned long *rec4 = tail;
                    unsigned long *tail2 = 0;
                    tb_resize_buffer(src2, 0, (unsigned long)head);
                    tb_message_set_state(state, 1);
                    tb_message_receive((unsigned long)rec, (void *)tail, src2);
                    unsigned long diff = (unsigned long)head - (unsigned long)tail;
                    if (head < tail) goto errh;
                    do {
                        if (diff == 0) {
                            unsigned char three = 3;
                            unsigned long l3 = FUN_000132d4(1);
                            unsigned long l4 = FUN_000132e0(&three, 1);
                            if (l4 != l3) goto erri;
                            unsigned long nr4 = FUN_0005ee58(l3, 0, 0x20, 0);
                            FUN_000639a0(ch, &nr4);
                            goto finish2;
                        }
                        int r5 = tb_message_decode((unsigned long *)ch, (unsigned long)head, &rec4);
                        tail2 = rec4;
                        if (r5 != 0) {
                            FUN_004b0744((unsigned long)rec);
                            goto finish2;
                        }
                        tb_message_receive((unsigned long)rec, (void *)rec4, src2);
                        if (tail2 == 0) goto outnull;
                        diff = diff - (unsigned long)tail2;
                    } while (tail2 <= diff);
                    FUN_004b0934();
                }
            }
            goto top_done;
        }
    } else {
        FUN_004b0820();
    }
    FUN_004b0874();
err:    FUN_004b0850();
errg:   FUN_004b0904();
errh:   FUN_004b0988();
errb:   FUN_004b09b8();
errc:   FUN_004b0898();
erri:   FUN_004b0964();
erre:   FUN_004b08bc();
errf:   FUN_004b08e0();
    return 0;
top_done:
    return 0xd;
finish:
    if (rec == 0) return 0;
    FUN_004b0744((unsigned long)rec);
    return 0;
finish2:
    return 0;
outnull:
    FUN_004b0744((unsigned long)rec);
    return 4;
}

/* FUN_00016a5c @ 0x00016a5c   (est. tb_channel_flush)
 * Ghidra: undefined8 FUN_00016a5c(long param_1)
 * Flushes a tb_channel's transport: if the aux flag bit is set, performs a
 * broadcast notification (FUN_0006290c with FUN_00013260); then invokes a
 * syscall (FUN_00062c2c) against the channel's +0x80 record. Returns 0.
 * Confidence: low | Notes: channel at +0x80; object id tag 0x16fa0. */
unsigned long tb_channel_flush(unsigned long ch)
{
    unsigned long *rec = *(unsigned long **)(ch + 0x80);
    if (*(char *)(rec + 0xc) == 1) {
        FUN_0006290c(0, (unsigned long)FUN_00013260, 0);
    }
    unsigned long arg[2];
    arg[0] = 0x16fa0;
    arg[1] = _DAT_004bb1a8;
    unsigned long op = _DAT_004bb1a0;
    arg[0] = 4;
    *(unsigned long *)((unsigned char *)arg + 8) = ch;
    FUN_00062c2c((unsigned long)(rec + 2), *rec, (unsigned long)&arg);
    return 0;
}

/* FUN_00016af0 @ 0x00016af0   (est. tb_alloc_buffer)
 * Ghidra: undefined8 FUN_00016af0(ulong param_1, undefined8 param_2, ulong *param_3)
 * Allocates a transport buffer of `size` bytes (tag 0x100004077774924) and
 * initializes the descriptor at param_3 (base, size, flags). Returns 0 on
 * success, or the previous release result when the allocation fails (with the
 * descriptor reset to a released 0x100-marker state).
 * Confidence: high | Notes: alloc tag 0x100004077774924. */
unsigned long tb_alloc_buffer(unsigned long size, unsigned long kind, unsigned long *out)
{
    unsigned long p = FUN_00010244(size, 1, 0x100004077774924);
    if (p + size < p) {
        SoftwareBreakpoint(0x5519, 0x16b5c);
    }
    if (p != 0) {
        out[6] = 0;
        *out = p;
        *(unsigned char *)(out + 1) = 0;
        out[2] = 0;
        out[3] = size;
        out[4] = 0;
        *(unsigned int *)(out + 5) = 0;
        return 0;
    }
    unsigned long *t = (unsigned long *)FUN_004b0080();
    unsigned long r = (unsigned long)thunk_FUN_00012568((void *)*t);
    *t = 0;
    t[3] = 0;
    t[4] = 0;
    t[2] = 0;
    t[6] = 0;
    *(unsigned char *)(t + 1) = 0;
    *(unsigned int *)(t + 5) = 0x100;
    return r;
}

/* FUN_00016ba4 @ 0x00016ba4   (est. tb_resize_buffer)
 * Ghidra: undefined8 FUN_00016ba4(ulong *param_1, undefined8 param_2, ulong param_3)
 * Resizes the transport descriptor param_1 to `size` bytes (tag 0x360b8758),
 * updating its base pointer and capacity. Returns 0 on success, 1 on alloc
 * failure (descriptor left intact).
 * Confidence: high | Notes: realloc tag 0x360b8758. */
unsigned long tb_resize_buffer(unsigned long *t, unsigned long kind, unsigned long size)
{
    if (size != t[3]) {
        unsigned long p = FUN_000102f4(*t, size, 0x360b8758);
        if (p + size < p) {
            SoftwareBreakpoint(0x5519, 0x16c0c);
        }
        if (p == 0) {
            FUN_004b0080();
            return 1;
        }
        *t = p;
        t[3] = size;
    }
    t[2] = 0;
    return 0;
}

/* FUN_00016c24 @ 0x00016c24   (est. tb_transport_copy_obj)
 * Ghidra: void tb_transport_copy_obj(undefined8 param_1, undefined8 param_2)
 * Copies the transport object `obj` (param_1) into the transport buffer of
 * `m` (param_2): reads the object size (FUN_0005ee50), stack-copies its bytes
 * (FUN_0005eb78), copies the object's flag word into the transport descriptor,
 * sets message kind=2, records the current cpu/thread id, and resizes the
 * buffer to fit. Traps on overflow.
 * Confidence: low | Notes: uses DAT_00657fa0 (stack switch) + FUN_0005eb78;
 *   canary 0xd2c8502b44bfffed6. */
void tb_transport_copy_obj(unsigned long obj, unsigned long m)
{
    long canary = -0x2c8502b44bfffed6;
    unsigned long *t = (unsigned long *)tb_get_transport(m);
    unsigned long n = FUN_0005ee50(obj);
    if (n >> 0x3d == 0) {
        unsigned long bytes = n * 8;
        (*DAT_00657fa0)();
        unsigned char stackbuf[((0) & ~0xf)];
        unsigned char *buf = stackbuf - (bytes + 0xf & 0xfffffffffffffff0);
        thunk_FUN_00114330((unsigned long)buf, (unsigned long)buf, bytes);
        if (buf + bytes < buf) goto trap;
        unsigned long got = FUN_0005eb78((unsigned long)buf, bytes, 0);
        if (n == got) {
            unsigned short f = FUN_0005ee48(obj);
            *(unsigned short *)((unsigned long)t + 0x2a) = f;
            tb_message_for_type((unsigned int *)m, 2);
            FUN_00060524(0);
            unsigned long th = thunk_FUN_00061638();
            tb_set_18(m, th);
            FUN_0005edac(0, 0);
            tb_resize_buffer(t, 0, bytes);
            if (t[3] <= bytes && bytes - t[3] != 0) {
trap:
                SoftwareBreakpoint(0x5519, 0x16d6c);
            }
            unsigned long base = *t;
            FUN_00117cc4(base, (unsigned long)buf, bytes);
            if (base + bytes < base) goto trap;
            if (canary == -0x2c8502b44bfffed6) {
                return;
            }
            FUN_0011d7e8(0);
        }
    } else {
        FUN_004b0a18();
    }
    FUN_004b09e8();
    FUN_0011d7e8(0);
}

/* FUN_00016d78 @ 0x00016d78   (est. tb_message_receive)
 * Ghidra: void tb_message_receive(undefined8 param_1, undefined8 *param_2, ulong *param_3)
 * The transport-buffer message receive core. Appends `param_2` bytes of
 * inbound data to the transport descriptor param_3; when the append crosses
 * the buffer limit it materializes the pending tb_message from the source
 * buffer (FUN_0005eb78 + stack copy), initializes a fresh message (kind via
 * FUN_0001586c, state 4), and dispatches on the message kind byte:
 *   1 -> allocate a new physical transport + CallSupervisor(2)
 *   2 -> copy into an existing transport cap
 *   3 -> release the referenced object (FUN_000151c8)
 *   4 -> copy into a transport-buffer cap (with growth)
 * Falls to FUN_0011d7e8 on error. Huge; decompiler "type propagation not
 * settling" warning. The plVar5[-N] stores are the compiler zero-initializing
 * a large stack message/region struct, represented here as a named block.
 * Confidence: low | Notes: tags 0x100004077774924, 0x103004032233d17,
 *   0x1090040b6685729; CallSupervisor(2); canary 0xd2c8502b44bfffed6. */
void tb_message_receive(unsigned long reg, void *data, unsigned long *t)
{
    unsigned long cur = tb_transport_get_or_alloc(0);
    unsigned long base = *t;
    unsigned long end = base + t[3];
    unsigned long pos = base + t[2];
    if (((cur + (unsigned long)data < cur) || end < pos) || pos < base ||
        t[3] - t[2] < (unsigned long)data ||
        FUN_00117cc4(pos, cur, (unsigned long)data), pos + (unsigned long)data < pos) {
        SoftwareBreakpoint(0x5519, 0x16dc8);
    }
    unsigned long p = t[2];
    t[2] = p + (unsigned long)data;
    if (p + (unsigned long)data <= t[3]) {
        thunk_FUN_00114330((unsigned long)cur, (unsigned long)data, (unsigned long)data);
        return;
    }
    /* ---- materialize the message from the source buffer ---- */
    unsigned long msg = (unsigned long)FUN_004b0a3c();
    unsigned long srcbuf = *(unsigned long *)msg;
    unsigned long out = 0;
    long canary = -0x2c8502b44bfffed6;
    unsigned char one = 2;
    unsigned long l1 = FUN_000132d4(1);
    unsigned long l2 = FUN_000132e0(&one, 1);
    if (l2 != l1) {
        unsigned long r = FUN_004b0a6c();
        goto chk;
    }
    unsigned long nr = 0x20;
    unsigned long buf = FUN_0005ee58(l1, 0, 0x20, 0);
    unsigned long r = FUN_000639a0((unsigned long)msg, &buf);
    if (r != 0) {
        unsigned long r2 = 1;
chk:
        if (canary == -0x2c8502b44bfffed6) {
            return;
        }
        FUN_0011d7e8(r2);
    }
    unsigned long n = FUN_0005ee50(buf);
    unsigned long bytes = 0;
    unsigned char *sbuf = 0;
    if (n >> 0x3d == 0) {
        bytes = n * 8;
        (*DAT_00657fa0)();
        sbuf = (unsigned char *)((unsigned long)&srcbuf - (bytes + 0xf & 0xfffffffffffffff0));
        thunk_FUN_00114330((unsigned long)sbuf, (unsigned long)sbuf, bytes);
        unsigned long got = FUN_0005eb78((unsigned long)sbuf, bytes, 0);
        if (n == got) {
            if (0xf < bytes) {
                if (*(unsigned long *)sbuf == *(unsigned long *)(msg + 8)) {
                    out = *(unsigned long *)(sbuf + 8);
                    goto found;
                }
            }
            out = 4;
            goto found;
        }
    } else {
        FUN_004b0ac0();
    }
    /* ---- fresh message setup (zero-initialized region struct) ---- */
    unsigned long msg2 = (unsigned long)FUN_004b0a90();
    unsigned char kindb;
    unsigned char f8;
    unsigned long *mt;
    unsigned long mbuf;
    /* A large stack region is zero-initialized here (the plVar5[-N]=0 block). */
    unsigned char zbuf[0x68] = {0};
    if (bytes <= 0x1b8) {
        unsigned long got2 = FUN_0005eb78((unsigned long)sbuf, bytes, 0);
        if (n == got2) {
            unsigned long fl = FUN_0005ee48(*(unsigned long *)(msg2 + 8));
            FUN_00060524(0);
            unsigned long tid = thunk_FUN_00061638();
            unsigned long v = tid;
            if ((fl >> 5 & 1) == 0) {
                if (bytes == 0 ||
                    FUN_00016af0(bytes, tid, (unsigned long *)&zbuf[0x10]) != 0) {
                    goto trap_1710c;
                }
                unsigned long b = *(unsigned long *)&zbuf[0x10];
                FUN_00117cc4(b, (unsigned long)sbuf, bytes);
                if (b + bytes < b) goto trap_1710c;
                *(unsigned short *)&zbuf[0x50] = (unsigned short)fl;
                int ir = tb_message_init((unsigned int *)&zbuf[0x40], b, 1);
                if (ir != 0) {
                    unsigned long e = FUN_0005ee58(0, 0, 0, 0);
                    goto done_e;
                }
                tb_message_set_state(&zbuf[0x40], 4);
                tb_set_id((unsigned long)&zbuf[0x40], 0);
                tb_set_18((unsigned long)&zbuf[0x40], v);
                unsigned long nb = 0;
                ir = FUN_00015468((unsigned long)msg2, (unsigned long)&zbuf[0x40], &nb);
                if (ir == 0) {
                    unsigned long rec = nb;
                    if (rec != 0) {
                        goto build;
                    }
                    thunk_FUN_00012568((void *)*(unsigned long *)&zbuf[0x10]);
                } else {
                    unsigned long e = FUN_0005ee58(0, 0, 0, 0);
                    nb = e;
                    goto post;
                }
            } else {
                unsigned char kb = *sbuf;
                if (2 < kb) {
                    if (kb == 3) {
                        FUN_000151c8(*(unsigned long *)(*(unsigned long *)((unsigned long)msg2 + 0x80) + 0x68), v);
                    } else if (kb == 4) {
                        if (0x17 < bytes) {
                            unsigned long cap = *(unsigned long *)(*(unsigned long *)((unsigned long)msg2 + 0x80) + 0x68);
                            unsigned long *cr = (unsigned long *)FUN_00015264(cap, v);
                            if (cr != 0 && *(char *)(cr + 8) == 1 && *(unsigned long *)(cr + 0x10) != 0) {
                                unsigned long cbase = tb_transport_get_or_alloc(0);
                                unsigned long *cp = (unsigned long *)(cr + 0x18);
                                unsigned long size = *cp;
                                if (size == 0) {
                                    size = FUN_00010244(*(unsigned long *)&zbuf[0x10], 1, 0x100004077774924);
                                    if (size + *(unsigned long *)&zbuf[0x10] < size) goto trap_1710c;
                                    if (size == 0) goto oom;
                                    *(unsigned long *)(cr + 0x18) = size;
                                    *(unsigned long *)(cr + 0x20) = *(unsigned long *)&zbuf[0x10];
                                    *(unsigned long *)(cr + 0x28) = 0;
                                }
                                unsigned long fill = *(unsigned long *)(cr + 0x28);
                                if (fill + bytes <= *(unsigned long *)(cr + 0x20)) {
                                    unsigned long dst = size + fill;
                                    if ((cbase + bytes < cbase) ||
                                        (dst < size || *(unsigned long *)(cr + 0x20) + size < dst) ||
                                        (*(unsigned long *)(cr + 0x20) - fill < bytes ||
                                         FUN_00117cc4(dst, cbase, bytes), dst + bytes < dst)) {
trap_1710c:
                                        SoftwareBreakpoint(0x5519, 0x17110);
                                    }
                                    *(unsigned long *)(cr + 0x28) = fill + bytes;
                                    thunk_FUN_00114330((unsigned long)cbase, (unsigned long)cbase, bytes);
                                    if (*(unsigned long *)(cr + 0x20) == *(unsigned long *)(cr + 0x28)) {
                                        unsigned long nb2 = 0;
                                        /* region struct zeroed + rebuilt */
                                        *(unsigned long *)&zbuf[0x10] = size;
                                        *(unsigned long *)&zbuf[0x38] = *(unsigned long *)(cr + 0x20);
                                        *(unsigned short *)&zbuf[0x50] = (unsigned short)fl;
                                        tb_message_init((unsigned int *)&zbuf[0x40], *(unsigned long *)&zbuf[0x10], 1);
                                        tb_set_18((unsigned long)&zbuf[0x40], v);
                                        tb_set_id((unsigned long)&zbuf[0x40], 0);
                                        tb_message_set_state(&zbuf[0x40], 4);
                                        *cp = 0;
                                        *(unsigned long *)(cr + 0x20) = 0;
                                        unsigned long nb3 = 0;
                                        int ir2 = FUN_00015468((unsigned long)msg2, (unsigned long)&zbuf[0x40], &nb3);
                                        if (ir2 != 0) goto tail;
                                        unsigned long rec = nb3;
                                        goto build;
                                    }
                                    out = 0;
                                }
                            }
                        }
                        FUN_0005ee58(0, 0, 0, 0);
                    }
                    out = 0;
                } else if (kb == 1) {
                    unsigned long *cp = 0;
                    int ir = tb_transport_create_phys(&cp);
                    if (ir == 0) {
                        unsigned long rec = (unsigned long)cp;
                        unsigned long *nr = (unsigned long *)FUN_00010244(1, 0x30, 0x103004032233d17);
                        if (nr == 0) FUN_004b0068();
                        *(unsigned char *)(nr + 1) = 1;
                        *nr = v;
                        nr[2] = rec;
                        FUN_00015108(*(unsigned long *)(*(unsigned long *)((unsigned long)msg2 + 0x80) + 0x68), v, (unsigned long)nr, 0x659128);
                        unsigned long id = tb_get_10(*(unsigned long *)&zbuf[0x10]);
                        unsigned long pa = FUN_00034f70();
                        CallSupervisor(2);
                        unsigned long r = FUN_00060524(id, pa);
                        r = FUN_000636a4(r, 0);
                        CallSupervisor(1);
                        if ((pa & 0xff) == 0) {
                            FUN_004b23d8(pa, 0);
                            unsigned long e = FUN_0005ee58(0, 1, 0x20, 0);
                            out = 0;
                            goto done_e;
                        }
                        FUN_004b0b98(pa, r);
                    }
                    out = 0;
                } else if (kb == 2) {
                    unsigned long cap = *(unsigned long *)(*(unsigned long *)((unsigned long)msg2 + 0x80) + 0x68);
                    unsigned long *cr = (unsigned long *)FUN_00015264(cap, v);
                    if (cr == 0 || *(char *)(cr + 8) != 2) goto nofill;
                    unsigned long room = *(unsigned long *)(cr + 0x20) - *(unsigned long *)(cr + 0x28);
                    unsigned long cbase = tb_transport_get_or_alloc_b(*(unsigned long *)(cr + 0x10));
                    if (cbase <= room) room = cbase;
                    unsigned long end2 = *(unsigned long *)(cr + 0x20);
                    unsigned long fill = *(unsigned long *)(cr + 0x28);
                    if (end2 < fill + room) {
                        room = 0;
                    } else {
                        if (end2 - fill < room) goto trap_1710c;
                        unsigned long size = *(unsigned long *)(cr + 0x18);
                        unsigned long dst = size + fill;
                        unsigned long b2 = **(unsigned long **)(cr + 0x10);
                        if ((size + end2 < dst) || (dst < size) ||
                            FUN_00117cc4(b2, dst, room), b2 + room < b2) goto trap_1710c;
                        *(unsigned long *)(cr + 0x28) = fill + room;
                    }
                    *(unsigned long *)&zbuf[0x10] = end2;
                    *(unsigned long *)&zbuf[0x18] = room;
                    if (FUN_000132e0(&zbuf[0x10], 0x10) != FUN_000132d4(0x10)) goto tail;
                    out = 0x20;
                }
            }
        }
    } else {
        FUN_004b0bbc();
        FUN_004b0ae4();
    }
    FUN_004b0b14();
    goto done;
found:
    if (canary == -0x2c8502b44bfffed6) {
        return;
    }
    FUN_0011d7e8(out);
done:
    FUN_0011d7e8(out);
oom:    FUN_004b0080();
    goto done;
nofill:
    FUN_0005ee58(0, 0, 0, 0);
    out = 0;
    goto done;
build:
    /* dispatch to the shared message-build/commit tail (FUN_000176a4); the
     * commit writes its result into the out slot. */
    tb_message_commit((unsigned long)msg2, (unsigned long)&zbuf[0x40], 0, &buf);
    goto done;
done_e:
    out = 0;
    goto done;
post:
    goto done;
tail:
    FUN_004b0b44();
    return;
}

/* FUN_00016a5c @ 0x00016a5c   (est. tb_channel_flush)
 * Ghidra: void tb_message_decode(long *param_1, long param_2, undefined8 *param_3)
 * Decode variant of tb_message_receive. Reads the transport object at param_1
 * (kind check via FUN_000132d4/132e0), materializes the inbound message bytes
 * (FUN_0005eb78 + stack copy), and compares the first word against the
 * expected magic `param_2`; on match stores the message payload at *param_3
 * and returns 0. Otherwise it builds a fresh message and dispatches on the
 * kind byte exactly like tb_message_receive (kinds 1/2/3/4).
 * Confidence: low | Notes: twin of 16d78; same helpers/tags; canary
 *   0xd2c8502b44bfffed6. */
unsigned long tb_message_decode(unsigned long *src, unsigned long expect, unsigned long **out)
{
    unsigned long msg = (unsigned long)src;
    unsigned long got;
    long canary = -0x2c8502b44bfffed6;
    unsigned char one = 2;
    unsigned long l1 = FUN_000132d4(1);
    unsigned long l2 = FUN_000132e0(&one, 1);
    if (l2 != l1) {
        unsigned long r = FUN_004b0a6c();
        goto chk;
    }
    unsigned long nr = 0x20;
    unsigned long buf = FUN_0005ee58(l1, 0, 0x20, 0);
    unsigned long ir = 0;
    unsigned long r = FUN_000639a0((unsigned long)msg, &buf);
    if (r != 0) {
        unsigned long r2 = 1;
chk:
        if (canary == -0x2c8502b44bfffed6) {
            return 0;
        }
        FUN_0011d7e8(r2);
    }
    unsigned long n = FUN_0005ee50(buf);
    unsigned long bytes = 0;
    unsigned char *sbuf = 0;
    if (n >> 0x3d == 0) {
        bytes = n * 8;
        (*DAT_00657fa0)();
        sbuf = (unsigned char *)((unsigned long)msg - (bytes + 0xf & 0xfffffffffffffff0));
        thunk_FUN_00114330((unsigned long)sbuf, (unsigned long)sbuf, bytes);
        unsigned long got2 = FUN_0005eb78((unsigned long)sbuf, bytes, 0);
        if (n == got2) {
            if (0xf < bytes) {
                if (*(unsigned long *)sbuf == expect) {
                    *out = (unsigned long *)(*(unsigned long *)(sbuf + 8));
                    goto found;
                }
            }
            *out = (unsigned long *)(4);
            goto found;
        }
    } else {
        FUN_004b0ac0();
    }
    /* ---- fresh message build + kind dispatch (same as tb_message_receive) ---- */
    unsigned long msg2 = (unsigned long)FUN_004b0a90();
    unsigned char kindb;
    unsigned long v;
    unsigned long *mt;
    unsigned char zbuf[0x68] = {0};
    if (bytes <= 0x1b8) {
        unsigned long got3 = FUN_0005eb78((unsigned long)sbuf, bytes, 0);
        if (n == got3) {
            unsigned long fl = FUN_0005ee48(*(unsigned long *)(msg2 + 8));
            FUN_00060524(0);
            unsigned long tid = thunk_FUN_00061638();
            v = tid;
            if ((fl >> 5 & 1) == 0) {
                if (bytes == 0 || FUN_00016af0(bytes, tid, (unsigned long *)&zbuf[0x10]) != 0)
                    goto trap_1710c;
                unsigned long b = *(unsigned long *)&zbuf[0x10];
                FUN_00117cc4(b, (unsigned long)sbuf, bytes);
                if (b + bytes < b) goto trap_1710c;
                *(unsigned short *)&zbuf[0x50] = (unsigned short)fl;
                int ir = tb_message_init((unsigned int *)&zbuf[0x40], b, 1);
                if (ir != 0) {
                    unsigned long e = FUN_0005ee58(0, 0, 0, 0);
                    goto done_e;
                }
                tb_message_set_state(&zbuf[0x40], 4);
                tb_set_id((unsigned long)&zbuf[0x40], 0);
                tb_set_18((unsigned long)&zbuf[0x40], v);
                unsigned long nb = 0;
                ir = FUN_00015468((unsigned long)msg2, (unsigned long)&zbuf[0x40], &nb);
                if (ir == 0) {
                    unsigned long rec = nb;
                    if (rec != 0) goto build;
                    thunk_FUN_00012568((void *)*(unsigned long *)&zbuf[0x10]);
                } else {
                    unsigned long e = FUN_0005ee58(0, 0, 0, 0);
                    nb = e;
                    goto post;
                }
            } else {
                unsigned char kb = *sbuf;
                if (2 < kb) {
                    if (kb == 3) {
                        FUN_000151c8(*(unsigned long *)(*(unsigned long *)((unsigned long)msg2 + 0x80) + 0x68), v);
                    } else if (kb == 4) {
                        if (0x17 < bytes) {
                            unsigned long cap = *(unsigned long *)(*(unsigned long *)((unsigned long)msg2 + 0x80) + 0x68);
                            unsigned long *cr = (unsigned long *)FUN_00015264(cap, v);
                            if (cr != 0 && *(char *)(cr + 8) == 1 && *(unsigned long *)(cr + 0x10) != 0) {
                                unsigned long cbase = tb_transport_get_or_alloc(0);
                                unsigned long *cp = (unsigned long *)(cr + 0x18);
                                unsigned long size = *cp;
                                if (size == 0) {
                                    size = FUN_00010244(*(unsigned long *)&zbuf[0x10], 1, 0x100004077774924);
                                    if (size + *(unsigned long *)&zbuf[0x10] < size) goto trap_1710c;
                                    if (size == 0) goto oom;
                                    *(unsigned long *)(cr + 0x18) = size;
                                    *(unsigned long *)(cr + 0x20) = *(unsigned long *)&zbuf[0x10];
                                    *(unsigned long *)(cr + 0x28) = 0;
                                }
                                unsigned long fill = *(unsigned long *)(cr + 0x28);
                                if (fill + bytes <= *(unsigned long *)(cr + 0x20)) {
                                    unsigned long dst = size + fill;
                                    if ((cbase + bytes < cbase) ||
                                        (dst < size || *(unsigned long *)(cr + 0x20) + size < dst) ||
                                        (*(unsigned long *)(cr + 0x20) - fill < bytes ||
                                         FUN_00117cc4(dst, cbase, bytes), dst + bytes < dst)) {
trap_1710c:
                                        SoftwareBreakpoint(0x5519, 0x17110);
                                    }
                                    *(unsigned long *)(cr + 0x28) = fill + bytes;
                                    thunk_FUN_00114330((unsigned long)cbase, (unsigned long)cbase, bytes);
                                    if (*(unsigned long *)(cr + 0x20) == *(unsigned long *)(cr + 0x28)) {
                                        *(unsigned long *)&zbuf[0x10] = size;
                                        *(unsigned long *)&zbuf[0x38] = *(unsigned long *)(cr + 0x20);
                                        *(unsigned short *)&zbuf[0x50] = (unsigned short)fl;
                                        tb_message_init((unsigned int *)&zbuf[0x40], *(unsigned long *)&zbuf[0x10], 1);
                                        tb_set_18((unsigned long)&zbuf[0x40], v);
                                        tb_set_id((unsigned long)&zbuf[0x40], 0);
                                        tb_message_set_state(&zbuf[0x40], 4);
                                        *cp = 0;
                                        *(unsigned long *)(cr + 0x20) = 0;
                                        unsigned long nb2 = 0;
                                        int ir2 = FUN_00015468((unsigned long)msg2, (unsigned long)&zbuf[0x40], &nb2);
                                        if (ir2 != 0) goto tail;
                                        unsigned long rec = nb2;
                                        goto build;
                                    }
                                    *out = (unsigned long *)(0);
                                }
                            }
                        }
                        FUN_0005ee58(0, 0, 0, 0);
                    }
                    *out = (unsigned long *)(0);
                } else if (kb == 1) {
                    unsigned long *cp = 0;
                    int ir = tb_transport_create_phys(&cp);
                    if (ir == 0) {
                        unsigned long rec = (unsigned long)cp;
                        unsigned long *nr = (unsigned long *)FUN_00010244(1, 0x30, 0x103004032233d17);
                        if (nr == 0) FUN_004b0068();
                        *(unsigned char *)(nr + 1) = 1;
                        *nr = v;
                        nr[2] = rec;
                        FUN_00015108(*(unsigned long *)(*(unsigned long *)((unsigned long)msg2 + 0x80) + 0x68), v, (unsigned long)nr, 0x659128);
                        unsigned long id = tb_get_10(*(unsigned long *)&zbuf[0x10]);
                        unsigned long pa = FUN_00034f70();
                        CallSupervisor(2);
                        unsigned long r = FUN_00060524(id, pa);
                        r = FUN_000636a4(r, 0);
                        CallSupervisor(1);
                        if ((pa & 0xff) == 0) {
                            FUN_004b23d8(pa, 0);
                            unsigned long e = FUN_0005ee58(0, 1, 0x20, 0);
                            *out = (unsigned long *)(0);
                            goto done_e;
                        }
                        FUN_004b0b98(pa, r);
                    }
                    *out = (unsigned long *)(0);
                } else if (kb == 2) {
                    unsigned long cap = *(unsigned long *)(*(unsigned long *)((unsigned long)msg2 + 0x80) + 0x68);
                    unsigned long *cr = (unsigned long *)FUN_00015264(cap, v);
                    if (cr == 0 || *(char *)(cr + 8) != 2) goto nofill;
                    unsigned long room = *(unsigned long *)(cr + 0x20) - *(unsigned long *)(cr + 0x28);
                    unsigned long cbase = tb_transport_get_or_alloc_b(*(unsigned long *)(cr + 0x10));
                    if (cbase <= room) room = cbase;
                    unsigned long end2 = *(unsigned long *)(cr + 0x20);
                    unsigned long fill = *(unsigned long *)(cr + 0x28);
                    if (end2 < fill + room) {
                        room = 0;
                    } else {
                        if (end2 - fill < room) goto trap_1710c;
                        unsigned long size = *(unsigned long *)(cr + 0x18);
                        unsigned long dst = size + fill;
                        unsigned long b2 = **(unsigned long **)(cr + 0x10);
                        if ((size + end2 < dst) || (dst < size) ||
                            FUN_00117cc4(b2, dst, room), b2 + room < b2) goto trap_1710c;
                        *(unsigned long *)(cr + 0x28) = fill + room;
                    }
                    *(unsigned long *)&zbuf[0x10] = end2;
                    *(unsigned long *)&zbuf[0x18] = room;
                    if (FUN_000132e0(&zbuf[0x10], 0x10) != FUN_000132d4(0x10)) goto tail;
                    *out = (unsigned long *)(0x20);
                }
            }
        }
    } else {
        FUN_004b0bbc();
        FUN_004b0ae4();
    }
    FUN_004b0b14();
    goto done;
found:
    if (canary == -0x2c8502b44bfffed6) {
        return 0;
    }
    return 0;
done:
    return 0;
oom:    FUN_004b0080();
    goto done;
nofill:
    FUN_0005ee58(0, 0, 0, 0);
    *out = (unsigned long *)(0);
    goto done;
build:
    tb_message_commit((unsigned long)msg2, (unsigned long)&zbuf[0x40], 0, out);
    goto post;
post:
    goto done;
done_e:
    goto done;
tail:
    FUN_004b0b44();
    return 0;
}

/* FUN_000176a4 @ 0x000176a4   (est. tb_message_commit)
 * Ghidra: void tb_message_commit(long param_1, undefined8 param_2, undefined8 param_3, undefined8 *param_4)
 * Commits a received message to its destination transport. For a source
 * transport <0x191 bytes it releases the source cap and copies the payload
 * into a fresh buffer (FUN_000132e0) sized by the message; otherwise it
 * either creates a new transport (FUN_00016318) for the message kind or
 * reuses the destination cap (FUN_00015264), then writes the message into the
 * destination via FUN_0005ee58 and stores the resulting object at *param_4.
 * Returns via *param_4; falls to FUN_0011d7e8 on error.
 * Confidence: low | Notes: kind codes 1/2; tags 0x103004032233d17,
 *   0x659128; CallSupervisor(2); canary 0xd2c8502b44bfffed6. */
void tb_message_commit(unsigned long reg, unsigned long m, unsigned long obj, unsigned long *out)
{
    long canary = -0x2c8502b44bfffed6;
    unsigned long *t = (unsigned long *)tb_get_transport(m);
    unsigned long srclen = t[3];
    unsigned long oid = tb_get_18(obj);
    unsigned long *cr = (unsigned long *)FUN_00015264(*(unsigned long *)(*(unsigned long *)(reg + 0x80) + 0x68), oid);
    unsigned long result;
    if (srclen < 0x191) {
        if (cr != 0) {
            FUN_000151c8(*(unsigned long *)(*(unsigned long *)(reg + 0x80) + 0x68), *cr);
        }
        unsigned long len = t[3];
        (*DAT_00657fa0)();
        unsigned char *sbuf = (unsigned char *)((unsigned long)&srclen - (len + 0xf & 0xfffffffffffffff0));
        if ((unsigned long)sbuf + len < (unsigned long)sbuf) {
trap_17848:
            SoftwareBreakpoint(0x5519, 0x1784c);
        }
        unsigned long base = *t;
        FUN_00117cc4((unsigned long)sbuf, base, len);
        unsigned short f = *(unsigned short *)((unsigned long)t + 0x2a);
        thunk_FUN_00012568((void *)base);
        *t = 0;
        t[3] = 0;
        t[4] = 0;
        t[2] = 0;
        t[6] = 0;
        *(unsigned char *)(t + 1) = 0;
        *(unsigned int *)(t + 5) = 0x100;
        unsigned long l1 = FUN_000132d4(len);
        unsigned long l2 = FUN_000132e0(sbuf, len);
        if (l2 != l1) {
            FUN_004b0c28();
            FUN_004b0c04();
            FUN_004b0068();
        }
        result = 0;
    } else {
        unsigned long local_70 = 0;
        unsigned long buf;
        if (cr == 0) {
            unsigned long *cp = &local_70;
            int ir = tb_transport_create_phys(&cp);
            buf = local_70;
            if (ir != 0) {
                result = 0xd;
                goto ret;
            }
            unsigned long srclen2 = t[3];
            unsigned long sbase = *t;
            unsigned long oid2 = tb_get_18(obj);
            unsigned long *nr = (unsigned long *)FUN_00010244(1, 0x30, 0x103004032233d17);
            if (nr == 0) goto trap_179c0;
            nr[3] = sbase;
            nr[4] = srclen2;
            *(unsigned char *)(nr + 1) = 2;
            *nr = oid2;
            nr[2] = buf;
            FUN_00015108(*(unsigned long *)(*(unsigned long *)(reg + 0x80) + 0x68), oid2, (unsigned long)nr, 0x659128);
            unsigned long id = tb_get_10(local_70);
            unsigned long pa = FUN_00034f70();
            CallSupervisor(2);
            unsigned long r = FUN_00060524(id, pa);
            r = FUN_000636a4(r, 0);
            CallSupervisor(1);
            if ((pa & 0xff) != 0) {
                FUN_004b0be0(pa, r);
                FUN_00118b28(TB_FATAL_COPYIN);
                return;
            }
            FUN_004b23d8(pa, 0);
        } else {
            unsigned long l = tb_transport_get_or_alloc_b(cr[2]);
            if ((unsigned long)(cr[3] + l) < (unsigned long)cr[3]) goto trap_17848;
            thunk_FUN_00114330(0, 0, 0);
            *(unsigned char *)(cr + 1) = 2;
            cr[5] = 0;
            local_70 = cr[2];
            buf = (unsigned long)cr;
        }
        unsigned long ccap = tb_transport_get_or_alloc_b(local_70);
        unsigned long len = t[3];
        unsigned long n = len;
        if (ccap <= len) n = ccap;
        buf = buf;  /* dest cap record */
        *(unsigned long *)(buf + 0x28) += n;
        unsigned long base = tb_transport_get_or_alloc(local_70);
        if ((t[3] < n || base + n < base) ||
            FUN_00117cc4(base, *t, n), base + n < base) goto trap_17848;
        unsigned long dbuf[2];
        dbuf[0] = len;
        dbuf[1] = n;
        if (FUN_000132e0(&dbuf, 0x10) != FUN_000132d4(0x10)) {
            FUN_004b0c28();
            FUN_004b0c04();
            FUN_004b0068();
        }
        result = (cr == 0) ? 1 : 0;
        unsigned long f = 0x20;
    }
    unsigned long r2 = FUN_0005ee58(0, 0, 0, 0);
    *out = r2;
ret:
    if (canary == -0x2c8502b44bfffed6) {
        return;
    }
    FUN_0011d7e8(result);
trap_179c0:
    FUN_004b0068();
}

/* ---- TB_FATAL banner helpers (each prints its message) ---- */
/* FUN_000179c8 @ 0x000179c8  (est. tb_fatal_copyin_size)  prints TB_FATAL: Copyin size did not match. */
void tb_fatal_copyin_size(unsigned long v) { FUN_00118b28(TB_FATAL_COPYIN); }
/* FUN_000179d8 @ 0x000179d8  (est. tb_fatal_overflow_dec)  prints TB_FATAL overflow during decode. */
void tb_fatal_overflow_dec(unsigned long v) { FUN_00118b28(TB_FATAL_OVERFLOW_DEC); }
/* FUN_000179e8 @ 0x000179e8  (est. tb_fatal_buf)          prints DAT_005aae47. */
void tb_fatal_buf(unsigned long v) { FUN_00118b28(DAT_5aae47); }
/* FUN_000179f8 @ 0x000179f8  (est. tb_fatal_buf2)         prints DAT_005ac18d. */
void tb_fatal_buf2(unsigned long v) { FUN_00118b28(DAT_5ac18d); }

/* FUN_00017a08 @ 0x00017a08   (est. tb_capref_create2)
 * Ghidra: undefined8 FUN_00017a08(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Builds a capability reference from two capability handles (retained via
 * FUN_00014478), attaches a type, then releases the two input handles.
 * Returns the created capref.
 * Confidence: medium */
unsigned long tb_capref_create2(unsigned long a, unsigned long b, unsigned long type, unsigned long cb)
{
    unsigned long h1 = FUN_00014478(a, 1);
    unsigned long h2 = FUN_00014478(b, 0);
    unsigned long cr = (unsigned long)tb_capref_create(h1, h2, type, cb);
    FUN_000153ec(a);
    FUN_000153ec(b);
    return cr;
}

/* FUN_00017a88 @ 0x00017a88   (est. tb_capref_create)
 * Ghidra: undefined1 * FUN_00017a88(undefined8 param_1, undefined8 param_2, ulong param_3, undefined8 param_4)
 * Allocates a 0x20-byte capability-ref record (tag 0x10a0040b1493d95), stores
 * a flag when param_3 bit0 set, binds two capability handles (FUN_000145bc /
 * thunk_FUN_00014510), the object id (FUN_0004b520), and a release callback
 * (FUN_00017c14). Returns the record. Recurses on allocation failure.
 * Confidence: medium | Notes: object id tag 0x659148. */
unsigned char *tb_capref_create(unsigned long a, unsigned long b, unsigned long flags, unsigned long cb)
{
    unsigned long tag = 0x10a0040b1493d95;
    unsigned char *rec = (unsigned char *)FUN_00010244(1, 0x20, 0x10a0040b1493d95);
    if (rec == 0) {
        unsigned long *r = (unsigned long *)FUN_004b0244();
        rec = tb_capref_create(r[0], r[1], 0, tag);
        return rec;
    }
    if ((flags & 1) != 0) {
        *rec = 1;
    }
    unsigned long obj = FUN_0004b520(cb);
    unsigned long args[6];
    args[0] = 0x6ad3a8;
    args[1] = _DAT_004bb180;
    args[2] = (unsigned long)FUN_00017c14;
    args[3] = 0x659148;
    args[4] = obj;
    args[5] = 0;
    unsigned long v = FUN_000145bc(a, (unsigned long)&args);
    *(unsigned long *)(rec + 8) = v;
    v = (unsigned long)thunk_FUN_00014510(b, 0);
    *(unsigned long *)(rec + 0x10) = v;
    *(unsigned long *)(rec + 0x18) = obj;
    if ((unsigned char *)rec <= rec + 0x20) {
        return rec;
    }
    SoftwareBreakpoint(0x5519, 0x17b78);
}

/* FUN_00017b7c @ 0x00017b7c   (est. tb_capref_bind)
 * Ghidra: void FUN_00017b7c(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Binds two caps into a capref with no extra flags. */
void tb_capref_bind(unsigned long a, unsigned long b, unsigned long cb)
{
    FUN_00017a88(a, b, 0, cb);
}

/* FUN_00017b88 @ 0x00017b88   (est. tb_capref_bind2)
 * Ghidra: void FUN_00017b88(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Binds and retains two caps into a capref. */
void tb_capref_bind2(unsigned long a, unsigned long b, unsigned long cb)
{
    FUN_00017a08(a, b, 0, cb);
}

/* FUN_00017b94 @ 0x00017b94   (est. tb_capref_release)
 * Ghidra: void FUN_00017b94(long param_1)
 * Releases a capref: drops the second cap (FUN_0001483c check) and destroys
 * the first cap (FUN_000147e0). */
void tb_capref_release(unsigned long cr)
{
    int r = FUN_0001483c(*(unsigned long *)(cr + 0x10));
    if (r != 0) {
        return;
    }
    FUN_000147e0(*(unsigned long *)(cr + 8));
}

/* FUN_00017bd4 @ 0x00017bd4   (est. tb_capref_destroy)
 * Ghidra: void FUN_00017bd4(long param_1)
 * Destroys a capref: releases the object (FUN_0004b664), the two cap handles
 * (FUN_00014578), and the record itself (thunk_FUN_00012568). */
void tb_capref_destroy(unsigned long cr)
{
    FUN_0004b664(*(unsigned long *)(cr + 0x18));
    FUN_00014578(*(unsigned long *)(cr + 8));
    FUN_00014578(*(unsigned long *)(cr + 0x10));
    thunk_FUN_00012568((void *)cr);
}

/* FUN_00017c14 @ 0x00017c14   (est. tb_msg_capref_handler)
 * Ghidra: void FUN_00017c14(long param_1, undefined8 param_2, int *param_3)
 * The capref message handler (bound as FUN_00017a88's release callback).
 * Validates the inbound message region, marshals the payload into a message
 * (FUN_00014bd4), checks the message kind, copies capability slots, and
 * forwards the request via the transport callback. On success returns 0.
 * Confidence: low | Notes: TB_ASSERT in_msg->state; transport vtable at
 *   +0x10; kind codes 0/2; helper FUN_0001485c/FUN_00014f90/FUN_0001574c. */
void tb_msg_capref_handler(unsigned long rec, unsigned long cb, unsigned int *msg)
{
    long canary = -0x2c8502b44bfffed6;
    unsigned char *data = *(unsigned char **)(rec + 0x28);
    if (data != 0 &&
        (data + 0x20 < data || *(unsigned char **)(rec + 0x30) < data + 0x20 ||
         data < *(unsigned char **)(rec + 0x38))) {
        SoftwareBreakpoint(0x5519, 0x17e4c);
    }
    unsigned long vtable = *(unsigned long *)(rec + 0x20);
    int r = (**(unsigned int (***)(unsigned long, unsigned char *, unsigned int *, int))(vtable + 0x10))(vtable, data, msg, 1);
    if (r == 0) {
        tb_message_state_transition(msg);
        return;
    }
    unsigned long *t = (unsigned long *)tb_get_transport((unsigned long)msg);
    *(unsigned long *)(t + 0x10) = *(unsigned long *)(t + 0x18);
    unsigned long u = FUN_00014470(*(unsigned long *)(data + 0x10));
    unsigned long region[14] = {0};
    unsigned long out[5] = {0};
    unsigned long v2 = *(unsigned long *)(data + 0x10);
    unsigned long end = tb_transport_end((unsigned long)msg);
    FUN_00014bd4(v2, (unsigned long)&out, (unsigned long)region, end, 0);
    if (msg[0] != 4) {
        FUN_00118b28(TB_ASSERT_IN_MSG_STATE);
        SoftwareBreakpoint(1, 0x17e74);
    }
    unsigned long v3 = *(unsigned long *)(data + 0x10);
    unsigned char kind = *data;
    unsigned long *tm = (unsigned long *)tb_get_transport((unsigned long)msg);
    unsigned long *rm = (unsigned long *)tb_get_transport((unsigned long)&out);
    if (*(unsigned long *)(tm + 0x18) != *(unsigned long *)(rm + 0x18)) {
        unsigned long *bad = (unsigned long *)FUN_004b0c4c();
        FUN_0004b710(bad[0] + 0x20, *(unsigned long *)(bad[1] + 0x20), 7);
        return;
    }
    FUN_0001574c((unsigned long)rm, (unsigned long)tm);
    tb_message_state_transition(&out);
    unsigned long which = 0;
    if (kind == 0) which = 2;
    int r2 = FUN_0001485c(v3, (unsigned long)&out, &region[0], which);
    if (r2 == 0) {
        if ((*data & 1) == 0 &&
            (r2 = (**(unsigned int (***)(unsigned long, unsigned char *, unsigned long, int))(vtable + 0x10))(vtable, data, region[0], 0), r2 != 0)) {
            unsigned long e2 = tb_transport_end((unsigned long)&out);
            FUN_00014f90(*(unsigned long *)(data + 8), (unsigned long)msg, e2, 0);
            unsigned long *tm2 = (unsigned long *)tb_get_transport((unsigned long)msg);
            FUN_0001574c((unsigned long)tm2, (unsigned long)region);
            *(unsigned long *)(tm2 + 0x10) = *(unsigned long *)(tm2 + 0x18);
            tb_message_state_transition(msg);
        }
        u = FUN_00014470(*(unsigned long *)(data + 0x10));
        msg = 0;
    } else {
        msg = 0;
        if (region[0] == 0) return;
    }
    FUN_00015630(u, (unsigned long)region);
    if (canary == -0x2c8502b44bfffed6) {
        return;
    }
    FUN_0011d7e8((unsigned long)msg);
}

/* FUN_00017e94 @ 0x00017e94   (est. tb_transport_write)
 * Ghidra: ulong FUN_00017e94(long param_1, ulong param_2, ulong param_3, ulong *param_4, ulong *param_5)
 * Writes `count` (param_3) bytes from the source transport into the
 * destination transport of `m` (param_1). Chunked copy loop with per-chunk
 * message append (FUN_00015670), region commit (FUN_00014bd0), and capref
 * propagation (FUN_00015548). On completion frees the scratch object and
 * stores the resulting transport at *param_4. Returns an error code.
 * Confidence: low | Notes: tags 0x1090040b6685729, 0x1010040ba4d407c,
 *   0x100004077774924; kind flags; scratch object FUN_00010244(0x68). */
unsigned long tb_transport_write(unsigned long m, unsigned long off, unsigned long count,
                                 unsigned long *out, unsigned long *flags)
{
    if (*(unsigned long *)(m + 0x60) != 0) {
        if (*(unsigned long *)(*(unsigned long *)(m + 0x60) + 0x38) == 0) {
            return 0;
        }
        return (FUN_000156e0(0) < off) ? 1 : 0;
    }
    unsigned long *scratch = (unsigned long *)FUN_004b0c7c();
    unsigned long msg = scratch[1];
    int r = FUN_000156b8(msg);
    if (r == 0) {
        return 1;
    }
    unsigned long step = FUN_000156e0(msg);
    unsigned long *t = (unsigned long *)tb_get_transport((unsigned long)msg);
    unsigned long total = t[3];
    unsigned long last = 0;
    unsigned long *scr = (unsigned long *)FUN_00010244(1, 0x68, 0x1090040b6685729);
    if (scr == 0) {
        FUN_004b0068();
    }
    unsigned long *capout = 0;
    unsigned long *cap = scr;
    unsigned long r2 = FUN_000155e8(msg, step, 0, (unsigned long)scr);
    if ((int)r2 == 0) {
        unsigned long base = scratch[0];
        if (total != 0) {
            unsigned long done = 0;
            unsigned long *flag5 = (unsigned long *)((unsigned long)flags & 0xfffffffffffffffd);
            unsigned long *flag6 = flags;
            do {
                unsigned long chunk = done + step;
                if (done + step < done) {
                    /* overflow: re-materialize and continue from the last chunk */
                    unsigned long *sc2 = (unsigned long *)FUN_004b0cac();
                    unsigned long m2 = sc2[1];
                    unsigned long v = FUN_00014470((unsigned long)cap);
                    int r3 = FUN_000156b8(0);
                    if (r3 == 0) {
                        return 5;
                    }
                    unsigned long *t2 = (unsigned long *)tb_get_transport(m2);
                    if ((*(unsigned char *)(t2 + 5) & 1) == 0) {
                        FUN_004b0cdc();
                    } else {
                        unsigned long oid = *(unsigned long *)(m2 + 0x18);
                        unsigned long *nr = (unsigned long *)FUN_00010244(1, 0x20, 0x1010040ba4d407c);
                        if (nr != 0) {
                            unsigned long n = t2[3];
                            unsigned long p = FUN_00010244(n, 1, 0x100004077774924);
                            if (p <= p + n) {
                                if (p == 0) {
                                    FUN_004b0498();
                                }
                                if (n <= (unsigned long)t2[3]) {
                                    FUN_00117cc4(p, *t2, n);
                                    nr[2] = n;
                                    nr[3] = 0;
                                    *nr = oid;
                                    nr[1] = p;
                                    if (nr < nr + 4) {
                                        FUN_00015108(sc2[0], oid, (unsigned long)nr, 0x659198);
                                        unsigned long st2 = FUN_000156e0(v);
                                        unsigned long rc = FUN_00014db8((unsigned long)cap, (unsigned long)m2, 1, st2, 0);
                                        if ((int)rc != 0) {
                                            return rc;
                                        }
                                        unsigned long *t3 = (unsigned long *)tb_get_transport(m2);
                                        if (st2 <= (unsigned long)nr[2]) {
                                            unsigned long b2 = *t3;
                                            unsigned long dpos = b2 + t3[4];
                                            if (((dpos <= b2 + t3[3]) && (b2 <= dpos)) &&
                                                (st2 <= t3[3] - t3[4]) &&
                                                (FUN_00117cc4(dpos, nr[1], st2), dpos <= dpos + st2)) {
                                                t3[2] = t3[2] + st2;
                                                nr[3] = nr[3] + st2;
                                                *(unsigned short *)((unsigned long)t3 + 0x2a) |= 1;
                                                *capout = m2;
                                                tb_message_state_transition((unsigned int *)m2);
                                                return 0;
                                            }
                                        }
                                    }
                                }
                            }
                            SoftwareBreakpoint(0x5519, 0x18368);
                        }
                    }
                    FUN_004b0068();
                }
                unsigned long n = step;
                if (total <= chunk) n = total - done;
                unsigned long r4 = FUN_00015670(msg, (unsigned long)scr, 0, n);
                if ((int)r4 != 0) {
                    FUN_00015630(msg, (unsigned long)scr);
                    goto free_scr;
                }
                unsigned long b3 = *t;
                unsigned long daddr = b3 + t[4] + done;
                if (b3 + t[3] < daddr || daddr < b3) {
                    SoftwareBreakpoint(0x5519, 0x1816c);
                }
                unsigned long sb = *scr;
                unsigned long spos = sb + scr[4];
                unsigned long sbase = sb + scr[3];
                unsigned long sroom = scr[3] - scr[4];
                bool full = t[3] - (t[4] + done) < n;
                if ((full || sbase < spos) || sroom <= n ||
                    (FUN_00117cc4(spos, daddr, n), spos + n < spos)) {
                    SoftwareBreakpoint(0x5519, 0x1816c);
                }
                unsigned long **pp = &flag5;
                if (total <= chunk) pp = &flag6;
                capout = *pp;
                unsigned short kind = 3;
                if (total > chunk) kind = 1;
                *(unsigned short *)((unsigned long)scr + 0x2a) = kind;
                tb_message_set_transport((unsigned long)msg, (unsigned long)scr);
                FUN_00014bd0(base, msg, msg, &last, (unsigned long)capout);
                if (chunk < total) {
                    capout = 0;
                    cap = flag5;
                } else {
                    capout = &last;
                    cap = flag6;
                }
                unsigned long r5 = FUN_00015548(msg, msg);
                if ((int)r5 != 0) {
                    FUN_00015630(msg, (unsigned long)scr);
                    thunk_FUN_00012568((void *)scr);
                    tb_message_set_transport((unsigned long)msg, (unsigned long)t);
                    return r5;
                }
                if (last != 0) {
                    if (chunk < total) {
                        FUN_00015630(msg, (unsigned long)scr);
                        thunk_FUN_00012568((void *)scr);
                        tb_message_set_transport((unsigned long)last, (unsigned long)t);
                        return 4;
                    }
                    unsigned long b4 = tb_get_transport(0);
                    cap = *(unsigned long **)(b4 + 0x18);
                    capout = t;
                    unsigned long r6 = FUN_00014ce0(base, msg, (unsigned long)t, (unsigned long)cap, 0);
                    if ((int)r6 != 0) {
                        FUN_00015630(msg, (unsigned long)scr);
                        thunk_FUN_00012568((void *)scr);
                        return r6;
                    }
                    FUN_0001574c((unsigned long)t, b4);
                }
                tb_message_set_transport((unsigned long)msg, (unsigned long)t);
                done = n + done;
            } while (done < total);
        }
        FUN_00015630(msg, (unsigned long)scr);
        thunk_FUN_00012568((void *)scr);
        if (out != 0 && last != 0) {
            *out = msg;
        }
        tb_message_set_transport((unsigned long)msg, (unsigned long)t);
        return 0;
    } else {
free_scr:
        thunk_FUN_00012568((void *)scr);
    }
    return r2;
}

/* FUN_00017edc @ 0x00017edc   (est. tb_transport_write_variant)
 * Ghidra: undefined8 FUN_00017edc(undefined8 param_1, undefined8 param_2, ulong param_3, ulong *param_4, ulong *param_5)
 * Variant of tb_transport_write taking the message object directly (param_2)
 * rather than a channel; otherwise identical chunked write loop.
 * Confidence: low | Notes: same tags/helpers as 17e94. */
unsigned long tb_transport_write_variant(unsigned long m, unsigned long msg2, unsigned long count,
                                         unsigned long *out, unsigned long *flags)
{
    int r = FUN_000156b8(msg2);
    if (r == 0) {
        return 1;
    }
    unsigned long step = FUN_000156e0(msg2);
    unsigned long *t = (unsigned long *)tb_get_transport((unsigned long)msg2);
    unsigned long total = t[3];
    unsigned long last = 0;
    unsigned long *scr = (unsigned long *)FUN_00010244(1, 0x68, 0x1090040b6685729);
    if (scr == 0) {
        FUN_004b0068();
    }
    unsigned long *capout = 0;
    unsigned long *cap = scr;
    unsigned long r2 = FUN_000155e8(msg2, step, 0, (unsigned long)scr);
    if ((int)r2 == 0) {
        unsigned long base = m;
        if (total != 0) {
            unsigned long done = 0;
            unsigned long *flag5 = (unsigned long *)((unsigned long)flags & 0xfffffffffffffffd);
            unsigned long *flag6 = flags;
            do {
                unsigned long chunk = done + step;
                if (done + step < done) {
                    unsigned long *sc2 = (unsigned long *)FUN_004b0cac();
                    unsigned long m2 = sc2[1];
                    unsigned long v = FUN_00014470((unsigned long)cap);
                    int r3 = FUN_000156b8(0);
                    if (r3 == 0) {
                        return 5;
                    }
                    unsigned long *t2 = (unsigned long *)tb_get_transport(m2);
                    if ((*(unsigned char *)(t2 + 5) & 1) == 0) {
                        FUN_004b0cdc();
                    } else {
                        unsigned long oid = *(unsigned long *)(m2 + 0x18);
                        unsigned long *nr = (unsigned long *)FUN_00010244(1, 0x20, 0x1010040ba4d407c);
                        if (nr != 0) {
                            unsigned long n = t2[3];
                            unsigned long p = FUN_00010244(n, 1, 0x100004077774924);
                            if (p <= p + n) {
                                if (p == 0) {
                                    FUN_004b0498();
                                }
                                if (n <= (unsigned long)t2[3]) {
                                    FUN_00117cc4(p, *t2, n);
                                    nr[2] = n;
                                    nr[3] = 0;
                                    *nr = oid;
                                    nr[1] = p;
                                    if (nr < nr + 4) {
                                        FUN_00015108(sc2[0], oid, (unsigned long)nr, 0x659198);
                                        unsigned long st2 = FUN_000156e0(v);
                                        unsigned long rc = FUN_00014db8((unsigned long)cap, (unsigned long)m2, 1, st2, 0);
                                        if ((int)rc != 0) {
                                            return rc;
                                        }
                                        unsigned long *t3 = (unsigned long *)tb_get_transport(m2);
                                        if (st2 <= (unsigned long)nr[2]) {
                                            unsigned long b2 = *t3;
                                            unsigned long dpos = b2 + t3[4];
                                            if (((dpos <= b2 + t3[3]) && (b2 <= dpos)) &&
                                                (st2 <= t3[3] - t3[4]) &&
                                                (FUN_00117cc4(dpos, nr[1], st2), dpos <= dpos + st2)) {
                                                t3[2] = t3[2] + st2;
                                                nr[3] = nr[3] + st2;
                                                *(unsigned short *)((unsigned long)t3 + 0x2a) |= 1;
                                                *capout = m2;
                                                tb_message_state_transition((unsigned int *)m2);
                                                return 0;
                                            }
                                        }
                                    }
                                }
                            }
                            SoftwareBreakpoint(0x5519, 0x18368);
                        }
                    }
                    FUN_004b0068();
                }
                unsigned long n = step;
                if (total <= chunk) n = total - done;
                unsigned long r4 = FUN_00015670(msg2, (unsigned long)scr, 0, n);
                if ((int)r4 != 0) {
                    FUN_00015630(msg2, (unsigned long)scr);
                    goto free_scr;
                }
                unsigned long b3 = *t;
                unsigned long daddr = b3 + t[4] + done;
                if (b3 + t[3] < daddr || daddr < b3) {
                    SoftwareBreakpoint(0x5519, 0x1816c);
                }
                unsigned long sb = *scr;
                unsigned long spos = sb + scr[4];
                unsigned long sbase = sb + scr[3];
                unsigned long sroom = scr[3] - scr[4];
                bool full = t[3] - (t[4] + done) < n;
                if ((full || sbase < spos) || sroom <= n ||
                    (FUN_00117cc4(spos, daddr, n), spos + n < spos)) {
                    SoftwareBreakpoint(0x5519, 0x1816c);
                }
                unsigned long **pp = &flag5;
                if (total <= chunk) pp = &flag6;
                capout = *pp;
                unsigned short kind = 3;
                if (total > chunk) kind = 1;
                *(unsigned short *)((unsigned long)scr + 0x2a) = kind;
                tb_message_set_transport((unsigned long)msg2, (unsigned long)scr);
                FUN_00014bd0(base, msg2, msg2, &last, (unsigned long)capout);
                if (chunk < total) {
                    capout = 0;
                    cap = flag5;
                } else {
                    capout = &last;
                    cap = flag6;
                }
                unsigned long r5 = FUN_00015548(msg2, msg2);
                if ((int)r5 != 0) {
                    FUN_00015630(msg2, (unsigned long)scr);
                    thunk_FUN_00012568((void *)scr);
                    tb_message_set_transport((unsigned long)msg2, (unsigned long)t);
                    return r5;
                }
                if (last != 0) {
                    if (chunk < total) {
                        FUN_00015630(msg2, (unsigned long)scr);
                        thunk_FUN_00012568((void *)scr);
                        tb_message_set_transport((unsigned long)last, (unsigned long)t);
                        return 4;
                    }
                    unsigned long b4 = tb_get_transport(0);
                    cap = *(unsigned long **)(b4 + 0x18);
                    capout = t;
                    unsigned long r6 = FUN_00014ce0(base, msg2, (unsigned long)t, (unsigned long)cap, 0);
                    if ((int)r6 != 0) {
                        FUN_00015630(msg2, (unsigned long)scr);
                        thunk_FUN_00012568((void *)scr);
                        return r6;
                    }
                    FUN_0001574c((unsigned long)t, b4);
                }
                tb_message_set_transport((unsigned long)msg2, (unsigned long)t);
                done = n + done;
            } while (done < total);
        }
        FUN_00015630(msg2, (unsigned long)scr);
        thunk_FUN_00012568((void *)scr);
        if (out != 0 && last != 0) {
            *out = msg2;
        }
        tb_message_set_transport((unsigned long)msg2, (unsigned long)t);
        return 0;
    } else {
free_scr:
        thunk_FUN_00012568((void *)scr);
    }
    return r2;
}

/* FUN_000181f4 @ 0x000181f4   (est. tb_transport_append_cap)
 * Ghidra: undefined8 FUN_000181f4(undefined8 param_1, long param_2, long *param_3, undefined8 param_4)
 * Appends a capability to a transport message: retains the cap (FUN_00015108),
 * grows the destination, and links the capref. Returns 0 on success.
 * Confidence: low | Notes: tags 0x1010040ba4d407c, 0x100004077774924,
 *   0x659198. */
unsigned long tb_transport_append_cap(unsigned long reg, unsigned long m, unsigned long *out, unsigned long kind)
{
    unsigned long v = FUN_00014470(kind);
    int r = FUN_000156b8(0);
    if (r == 0) {
        return 5;
    }
    unsigned long *t = (unsigned long *)tb_get_transport(m);
    if ((*(unsigned char *)(t + 5) & 1) == 0) {
        FUN_004b0cdc();
    } else {
        unsigned long oid = *(unsigned long *)(m + 0x18);
        unsigned long *nr = (unsigned long *)FUN_00010244(1, 0x20, 0x1010040ba4d407c);
        if (nr != 0) {
            unsigned long n = t[3];
            unsigned long p = FUN_00010244(n, 1, 0x100004077774924);
            if (p <= p + n) {
                if (p == 0) {
                    FUN_004b0498();
                }
                if (n <= (unsigned long)t[3]) {
                    FUN_00117cc4(p, *t, n);
                    nr[2] = n;
                    nr[3] = 0;
                    *nr = oid;
                    nr[1] = p;
                    if (nr < nr + 4) {
                        FUN_00015108(reg, oid, (unsigned long)nr, 0x659198);
                        unsigned long st = FUN_000156e0(v);
                        unsigned long rc = FUN_00014db8(kind, m, 1, st, 0);
                        if ((int)rc != 0) {
                            return rc;
                        }
                        unsigned long *t2 = (unsigned long *)tb_get_transport(m);
                        if (st <= (unsigned long)nr[2]) {
                            unsigned long b = *t2;
                            unsigned long dpos = b + t2[4];
                            if (((dpos <= b + t2[3]) && (b <= dpos)) &&
                                (st <= t2[3] - t2[4]) &&
                                (FUN_00117cc4(dpos, nr[1], st), dpos <= dpos + st)) {
                                t2[2] = t2[2] + st;
                                nr[3] = nr[3] + st;
                                *(unsigned short *)((unsigned long)t2 + 0x2a) |= 1;
                                *out = m;
                                tb_message_state_transition((unsigned int *)m);
                                return 0;
                            }
                        }
                    }
                }
            }
            SoftwareBreakpoint(0x5519, 0x18368);
        }
    }
    FUN_004b0068();
}

/* FUN_000183f0 @ 0x000183f0   (est. tb_transport_read)
 * Ghidra: undefined8 FUN_000183f0(undefined8 param_1, undefined8 param_2, long param_3, undefined8 param_4, undefined8 param_5)
 * Reads `count` bytes from a transport message into a destination object:
 * looks up the object (FUN_00015264), appends via FUN_00014db8, and advances
 * the position. Returns 0 on success; 0xf (not found), 2 (final), or error.
 * Confidence: low | Notes: kind flags 1/3. */
unsigned long tb_transport_read(unsigned long reg, unsigned long m, unsigned long obj,
                                unsigned long kind, unsigned long count)
{
    unsigned long *t = (unsigned long *)tb_get_transport(obj);
    if ((*(unsigned char *)(t + 0x28) & 1) == 0) {
        unsigned long *cr = (unsigned long *)FUN_00015264(reg, *(unsigned long *)(obj + 0x18));
        if (cr == 0) {
            return 0xf;
        }
        unsigned long avail = FUN_000156e0(count);
        unsigned long cur = *(unsigned long *)(cr + 0x18);
        unsigned long end = cur + avail;
        if (cur + avail < cur) {
            FUN_004b0d0c();
            thunk_FUN_00012568((void *)*(unsigned long *)(0 + 8));
            return (unsigned long)thunk_FUN_00012568((void *)0);
        }
        unsigned long cap = *(unsigned long *)(cr + 0x10);
        if (cap <= end) {
            avail = cap - cur;
        }
        unsigned long r = FUN_00014db8(m, obj, 1, avail, 0);
        if ((int)r == 0) {
            unsigned long *t2 = (unsigned long *)tb_get_transport(obj);
            unsigned short kind2 = 3;
            if (end < cap) kind2 = 1;
            *(unsigned short *)((unsigned long)t2 + 0x2a) = kind2;
            unsigned long src = *(unsigned long *)(cr + 8) + *(unsigned long *)(cr + 0x18);
            if (src <= src + avail && avail <= t2[3]) {
                unsigned long b = *t2;
                FUN_00117cc4(b, src, avail);
                if (b <= b + avail) {
                    *(unsigned long *)(cr + 0x18) += avail;
                    tb_message_state_transition((unsigned int *)obj);
                    if (cap <= end) {
                        FUN_000151c8(reg, *(unsigned long *)(obj + 0x18));
                    }
                    return 0;
                }
            }
            SoftwareBreakpoint(0x5519, 0x184c4);
        }
    } else {
        return 2;
    }
    return r;
}

/* FUN_00018560 @ 0x00018560   (est. tb_flags_check_all)
 * Ghidra: ulong FUN_00018560(undefined8 *param_1, long param_2, undefined8 param_3)
 * Iterates `count` transport handles; returns nonzero (set bit) if any handle
 * reports the given flag (FUN_0001a11c). Returns 1 when the list is empty.
 * Confidence: medium */
unsigned long tb_flags_check_all(unsigned long *list, long count, unsigned long flag)
{
    unsigned long r = 1;
    if (list != 0) {
        do {
            if (count == 0) {
                return r;
            }
            count = count - 1;
            r = FUN_0001a11c(*list, flag);
            list = list + 1;
        } while ((r & 1) == 0);
    }
    return r;
}

/* FUN_000185b8 @ 0x000185b8   (est. tb_put_region)
 * Ghidra: int * FUN_000185b8(int *param_1, ulong param_2, ulong param_3)
 * Writes `len` bytes (param_3) of source data `src` (param_2) into the
 * transport buffer of a state-1 (encoding) message, growing/selecting an
 * alternate buffer if needed. Returns the chosen transport buffer pointer.
 * Traps on overflow.
 * Confidence: medium | Notes: message kinds 1 and 4; several fallback
 *   allocation helpers (FUN_004b0d3c/0d60/0dcc/0e5c). */
int *tb_put_region(int *m, unsigned long src, unsigned long len)
{
    if (m[0] == 1) {
        unsigned long pos = *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10);
        if (pos + len < pos) goto of;
        if (pos + len <= *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x18)) {
            return m;
        }
    } else {
        FUN_004b0d3c();
of:     FUN_004b0d84();
    }
    unsigned long *alt = (unsigned long *)FUN_004b0d60();
    int *m2 = (int *)alt[0];
    if (m2[0] == 4) {
        unsigned long cap = *(unsigned long *)(*(unsigned long *)(m2 + 0x14) + 0x18);
        if (cap == 0) goto nz;
        unsigned long pos = *(unsigned long *)(*(unsigned long *)(m2 + 0x14) + 0x10);
        if (pos + alt[1] < pos) goto ov;
        if (pos + alt[1] <= cap) {
            return m2;
        }
    } else {
        FUN_004b0da8();
nz:     FUN_004b0e14();
ov:     FUN_004b0df0();
    }
    unsigned long *alt2 = (unsigned long *)FUN_004b0dcc();
    int *m3 = (int *)alt2[0];
    if (m3[0] == 1) {
        unsigned long *t = *(unsigned long **)(m3 + 0x14);
        unsigned long pos = t[2];
        if (pos + len < pos) SoftwareBreakpoint(0x5519, 0x0);
        unsigned long cap = t[3];
        if (pos + len <= cap) {
            unsigned long base = *t;
            unsigned long d = base + pos;
            if ((d <= base + cap && base <= d) && len <= cap - pos &&
                FUN_00117cc4(d, alt2[1], len), d <= d + len) {
                *(unsigned long *)(*(unsigned long *)(m3 + 0x14) + 0x10) += len;
                return (int *)d;
            }
            SoftwareBreakpoint(0x5519, 0x186b8);
        }
    } else {
        FUN_004b0e38();
ov2:    FUN_004b0e80();
    }
    unsigned long *alt3 = (unsigned long *)FUN_004b0e5c();
    unsigned long d3 = alt3[1];
    if (alt3[0] == 4) {
        unsigned long *t = *(unsigned long **)(alt3[0] + 0x14);
        unsigned long cap = t[3];
        if (cap == 0) goto nz2;
        unsigned long pos = t[2];
        if (pos + len < pos) SoftwareBreakpoint(0x5519, 0x0);
        if (pos + len <= cap) {
            unsigned long base = *t;
            t[2] = pos + len;
            unsigned long d = base + pos;
            if ((d <= base + cap && base <= d) && len <= cap - pos &&
                FUN_00117cc4(d3, d, len), d3 <= d3 + len) {
                return (int *)d3;
            }
            SoftwareBreakpoint(0x5519, 0x18768);
        }
        goto nz3;
    } else {
        FUN_004b0ea4();
nz2:    FUN_004b0f10();
    }
    FUN_004b0eec();
nz3:
    FUN_004b0ec8();
    return (int *)((unsigned long)&((char *)0)[0] + 1);
}

/* FUN_00018600 @ 0x00018600   (est. tb_get_region)
 * Ghidra: int * FUN_00018600(int *param_1, ulong param_2, ulong param_3)
 * Reads `len` bytes from a state-4 (decoding) message transport into the
 * destination `dst` (param_2), selecting the right buffer. Returns the
 * destination pointer. Traps on overflow.
 * Confidence: medium | Notes: twin of tb_put_region with kind 4 first. */
int *tb_get_region(int *m, unsigned long dst, unsigned long len)
{
    if (m[0] == 4) {
        unsigned long cap = *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x18);
        if (cap == 0) goto nz;
        unsigned long pos = *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10);
        if (pos + dst < pos) goto ov;
        if (pos + dst <= cap) {
            return m;
        }
    } else {
        FUN_004b0da8();
nz:     FUN_004b0e14();
ov:     FUN_004b0df0();
    }
    unsigned long *alt = (unsigned long *)FUN_004b0dcc();
    int *m2 = (int *)alt[0];
    if (m2[0] == 1) {
        unsigned long *t = *(unsigned long **)(m2 + 0x14);
        unsigned long pos = t[2];
        if (pos + len < pos) SoftwareBreakpoint(0x5519, 0x0);
        unsigned long cap = t[3];
        if (pos + len <= cap) {
            unsigned long base = *t;
            unsigned long d = base + pos;
            if ((d <= base + cap && base <= d) && len <= cap - pos &&
                FUN_00117cc4(d, alt[1], len), d <= d + len) {
                *(unsigned long *)(*(unsigned long *)(m2 + 0x14) + 0x10) += len;
                return (int *)d;
            }
            SoftwareBreakpoint(0x5519, 0x186b8);
        }
    } else {
        FUN_004b0e38();
ov2:    FUN_004b0e80();
    }
    unsigned long *alt2 = (unsigned long *)FUN_004b0e5c();
    unsigned long d2 = alt2[1];
    if (alt2[0] == 4) {
        unsigned long *t = *(unsigned long **)(alt2[0] + 0x14);
        unsigned long cap = t[3];
        if (cap == 0) goto nz2;
        unsigned long pos = t[2];
        if (pos + len < pos) SoftwareBreakpoint(0x5519, 0x0);
        if (pos + len <= cap) {
            unsigned long base = *t;
            t[2] = pos + len;
            unsigned long d = base + pos;
            if ((d <= base + cap && base <= d) && len <= cap - pos &&
                FUN_00117cc4(d2, d, len), d2 <= d2 + len) {
                return (int *)d2;
            }
            SoftwareBreakpoint(0x5519, 0x18768);
        }
        goto nz3;
    } else {
        FUN_004b0ea4();
nz2:    FUN_004b0f10();
    }
    FUN_004b0eec();
nz3:
    FUN_004b0ec8();
    return (int *)((unsigned long)&((char *)0)[0] + 1);
}

/* FUN_00018650 @ 0x00018650   (est. tb_put_region_va)
 * Ghidra: undefined8 FUN_00018650(int *param_1, undefined8 param_2, ulong param_3)
 * Writes `len` bytes from source `src` into a state-1 message transport,
 * returning the destination address. Traps on overflow.
 * Confidence: medium | Notes: simplified tb_put_region (kind 1 then 4). */
unsigned long tb_put_region_va(int *m, unsigned long src, unsigned long len)
{
    if (m[0] == 1) {
        unsigned long *t = *(unsigned long **)(m + 0x14);
        unsigned long pos = t[2];
        if (pos + len < pos) goto ov;
        unsigned long cap = t[3];
        if (pos + len <= cap) {
            unsigned long base = *t;
            unsigned long d = base + pos;
            if ((d <= base + cap && base <= d) && len <= cap - pos &&
                FUN_00117cc4(d, src, len), d <= d + len) {
                *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += len;
                return d;
            }
            SoftwareBreakpoint(0x5519, 0x186b8);
        }
    } else {
        FUN_004b0e38();
ov:     FUN_004b0e80();
    }
    unsigned long *alt = (unsigned long *)FUN_004b0e5c();
    unsigned long d2 = alt[1];
    if (alt[0] == 4) {
        unsigned long *t = *(unsigned long **)(alt[0] + 0x14);
        unsigned long cap = t[3];
        if (cap == 0) goto nz;
        unsigned long pos = t[2];
        if (pos + len < pos) SoftwareBreakpoint(0x5519, 0x0);
        if (pos + len <= cap) {
            unsigned long base = *t;
            t[2] = pos + len;
            unsigned long d = base + pos;
            if ((d <= base + cap && base <= d) && len <= cap - pos &&
                FUN_00117cc4(d2, d, len), d2 <= d2 + len) {
                return d2;
            }
            SoftwareBreakpoint(0x5519, 0x18768);
        }
        goto nz2;
    } else {
        FUN_004b0ea4();
nz:     FUN_004b0f10();
    }
    FUN_004b0eec();
nz2:
    FUN_004b0ec8();
    return 1;
}

/* FUN_0001879c @ 0x0001879c   (est. tb_ok1)
 * Ghidra: undefined8 FUN_0001879c(void)
 * Returns 1 (a "ready/available" sentinel). */
unsigned long tb_ok1(void)
{
    return 1;
}

/* ---- u8 put/get primitives ---- */

/* FUN_000187a4 @ 0x000187a4   (est. tb_put_u8)
 * Ghidra: void FUN_000187a4(int *param_1, undefined1 param_2)
 * Writes a byte into a state-1 (encoding) transport, advancing the position.
 * Falls back to the current transport via FUN_004b0f34. Traps on overflow.
 * Confidence: medium */
void tb_put_u8(int *m, unsigned char v)
{
    unsigned char *d;
    unsigned long pos;
    unsigned long cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (pos != ~0ull) {
            cap = t[3];
            if (pos + 1 <= cap) {
                d = (unsigned char *)*t + pos;
                if ((d <= (unsigned char *)*t + cap && (unsigned char *)*t <= d) &&
                    cap != pos && (*d = v, d <= d + 1)) {
                    *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 1;
                    return;
                }
                SoftwareBreakpoint(0x5519, 0x187f8);
            }
            goto fallback;
        }
    } else {
        FUN_004b0f34();
    }
    FUN_004b0f7c();
fallback:
    unsigned long cur = (unsigned long)FUN_004b0f58();
    t = *(unsigned long **)(cur + 0x50);
    d = (unsigned char *)*t + t[2];
    if ((t[3] != t[2] && d <= (unsigned char *)*t + t[3]) && (unsigned char *)*t <= d &&
        (*d = v, d <= d + 1)) {
        *(unsigned long *)(*(unsigned long *)(cur + 0x50) + 0x10) += 1;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x18854);
}

/* FUN_0001882c @ 0x0001882c   (est. tb_put_u8_cur)
 * Ghidra: void FUN_0001882c(long param_1, undefined1 param_2)
 * Writes a byte into the transport of message `m` (+0x50) directly.
 * Confidence: medium */
void tb_put_u8_cur(unsigned long m, unsigned char v)
{
    unsigned long *t = *(unsigned long **)(m + 0x50);
    unsigned char *d = (unsigned char *)*t + t[2];
    if ((t[3] != t[2] && d <= (unsigned char *)*t + t[3]) && (unsigned char *)*t <= d &&
        (*d = v, d <= d + 1)) {
        *(unsigned long *)(*(unsigned long *)(m + 0x50) + 0x10) += 1;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x18854);
}

/* FUN_00018878 @ 0x00018878   (est. tb_get_u8)
 * Ghidra: int * FUN_00018878(int *param_1, undefined1 *param_2)
 * Reads a byte from a state-4 (decoding) transport into *param_2, advancing
 * the position. Falls back to the current transport. Returns the buffer.
 * Confidence: medium */
int *tb_get_u8(int *m, unsigned char *out)
{
    unsigned char *d;
    unsigned long pos;
    unsigned long cap;
    unsigned long *t;
    if (m[0] == 4) {
        t = *(unsigned long **)(m + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos != ~0ull) {
            if (pos + 1 <= cap) {
                t[2] = pos + 1;
                d = (unsigned char *)*t + pos;
                if ((unsigned char *)*t + cap < d || d < (unsigned char *)*t || cap == pos) {
                    SoftwareBreakpoint(0x5519, 0x188d4);
                }
                *out = *d;
                return m;
            }
            goto fb;
        }
    } else {
        FUN_004b0fa0();
nz:     FUN_004b100c();
    }
    FUN_004b0fe8();
fb:
    FUN_004b0fc4();
    return (int *)((unsigned long)&((char *)0)[0] + 1);
}

/* FUN_000188fc @ 0x000188fc   (est. tb_put_u8b)
 * Ghidra: void FUN_000188fc(int *param_1, undefined1 param_2)
 * Same as tb_put_u8 (state-1 write with current-transport fallback).
 * Confidence: medium */
void tb_put_u8b(int *m, unsigned char v)
{
    unsigned char *d;
    unsigned long pos;
    unsigned long cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (pos != ~0ull) {
            cap = t[3];
            if (pos + 1 <= cap) {
                d = (unsigned char *)*t + pos;
                if ((d <= (unsigned char *)*t + cap && (unsigned char *)*t <= d) &&
                    cap != pos && (*d = v, d <= d + 1)) {
                    *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 1;
                    return;
                }
                SoftwareBreakpoint(0x5519, 0x18950);
            }
            goto fb;
        }
    } else {
        FUN_004b1030();
    }
    FUN_004b1078();
fb:
    unsigned long cur = (unsigned long)FUN_004b1054();
    t = *(unsigned long **)(cur + 0x50);
    d = (unsigned char *)*t + t[2];
    if ((t[3] != t[2] && d <= (unsigned char *)*t + t[3]) && (unsigned char *)*t <= d &&
        (*d = v, d <= d + 1)) {
        *(unsigned long *)(*(unsigned long *)(cur + 0x50) + 0x10) += 1;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x189ac);
}

/* FUN_00018984 @ 0x00018984   (est. tb_put_u8_curb)
 * Ghidra: void FUN_00018984(long param_1, undefined1 param_2)
 * Writes a byte into the transport of message `m` directly.
 * Confidence: medium */
void tb_put_u8_curb(unsigned long m, unsigned char v)
{
    unsigned long *t = *(unsigned long **)(m + 0x50);
    unsigned char *d = (unsigned char *)*t + t[2];
    if ((t[3] != t[2] && d <= (unsigned char *)*t + t[3]) && (unsigned char *)*t <= d &&
        (*d = v, d <= d + 1)) {
        *(unsigned long *)(*(unsigned long *)(m + 0x50) + 0x10) += 1;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x189ac);
}

/* FUN_000189d0 @ 0x000189d0   (est. tb_put_bytes)
 * Ghidra: void FUN_000189d0(long param_1, undefined8 param_2, ulong param_3)
 * Writes `len` bytes from `src` into the transport of message `m` (+0x50),
 * advancing the position. Falls back to the current transport if the direct
 * append would overflow. Traps on overflow.
 * Confidence: medium */
void tb_put_bytes(unsigned long m, unsigned long src, unsigned long len)
{
    unsigned long *t = *(unsigned long **)(m + 0x50);
    unsigned long pos = t[2];
    if (pos + len < pos) {
        goto alt;
    }
    unsigned long base = *t;
    t[2] = pos + len;
    unsigned long d = base + pos;
    if ((d <= base + t[3] && base <= d) && len <= t[3] - pos &&
        FUN_00117cc4(d, src, len), d <= d + len) {
        return;
    }
    SoftwareBreakpoint(0x5519, 0x18a24);
alt:
    unsigned long *cur = (unsigned long *)FUN_004b109c();
    if (cur[0] == 4) {
        unsigned long *t2 = *(unsigned long **)(cur[0] + 0x14);
        unsigned long cap = t2[3];
        if (cap == 0) goto nz;
        unsigned long pos2 = t2[2];
        if (pos2 != ~0ull) {
            if (pos2 + 1 <= cap) {
                unsigned char *d2 = (unsigned char *)*t2 + pos2;
                t2[2] = pos2 + 1;
                if ((unsigned char *)*t2 + cap < d2 || d2 < (unsigned char *)*t2 || cap == pos2) {
                    SoftwareBreakpoint(0x5519, 0x18aa8);
                }
                *(unsigned char *)(cur[1]) = *d2;
                return;
            }
            goto fb;
        }
    } else {
        FUN_004b10c0();
nz:     FUN_004b112c();
    }
    FUN_004b1108();
fb:
    unsigned long cur2 = (unsigned long)FUN_004b10e4();
    unsigned long *t3 = *(unsigned long **)(cur2 + 0x50);
    unsigned long pos3 = t3[2];
    unsigned char *d3 = (unsigned char *)*t3 + pos3;
    t3[2] = pos3 + 1;
    if ((t3[3] == pos3 || (unsigned char *)*t3 + t3[3] < d3) || d3 < (unsigned char *)*t3) {
        SoftwareBreakpoint(0x5519, 0x18af8);
    }
    *(unsigned char *)(cur[1]) = *d3;
}

/* FUN_00018a4c @ 0x00018a4c   (est. tb_get_u8b)
 * Ghidra: void FUN_00018a4c(int *param_1, undefined1 *param_2)
 * Reads a byte from a state-4 transport into *param_2 (with current-transport
 * fallback). Traps on overflow.
 * Confidence: medium */
void tb_get_u8b(int *m, unsigned char *out)
{
    unsigned char *d;
    unsigned long pos;
    unsigned long cap;
    unsigned long *t;
    if (m[0] == 4) {
        t = *(unsigned long **)(m + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos != ~0ull) {
            if (pos + 1 <= cap) {
                d = (unsigned char *)*t + pos;
                t[2] = pos + 1;
                if ((unsigned char *)*t + cap < d || d < (unsigned char *)*t || cap == pos) {
                    SoftwareBreakpoint(0x5519, 0x18aa8);
                }
                *out = *d;
                return;
            }
            goto fb;
        }
    } else {
        FUN_004b10c0();
nz:     FUN_004b112c();
    }
    FUN_004b1108();
fb:
    unsigned long cur = (unsigned long)FUN_004b10e4();
    t = *(unsigned long **)(cur + 0x50);
    pos = t[2];
    d = (unsigned char *)*t + pos;
    t[2] = pos + 1;
    if ((t[3] == pos || (unsigned char *)*t + t[3] < d) || d < (unsigned char *)*t) {
        SoftwareBreakpoint(0x5519, 0x18af8);
    }
    *out = *d;
}

/* FUN_00018ac8 @ 0x00018ac8   (est. tb_get_u8_cur)
 * Ghidra: void FUN_00018ac8(long param_1, undefined1 *param_2)
 * Reads a byte from the transport of message `m` directly into *param_2.
 * Confidence: medium */
void tb_get_u8_cur(unsigned long m, unsigned char *out)
{
    unsigned long *t = *(unsigned long **)(m + 0x50);
    unsigned long pos = t[2];
    unsigned char *d = (unsigned char *)*t + pos;
    t[2] = pos + 1;
    if ((t[3] == pos || (unsigned char *)*t + t[3] < d) || d < (unsigned char *)*t) {
        SoftwareBreakpoint(0x5519, 0x18af8);
    }
    *out = *d;
}

/* ---- u16 put/get ---- */

/* FUN_00018b0c @ 0x00018b0c   (est. tb_put_u16)
 * Ghidra: void FUN_00018b0c(int *param_1, undefined2 param_2)
 * Writes a u16 into a state-1 transport (fallback to current). Traps.
 * Confidence: medium */
void tb_put_u16(int *m, unsigned short v)
{
    unsigned short *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (pos < ~0ull - 1) {
            cap = t[3];
            if (pos + 2 <= cap) {
                d = (unsigned short *)((unsigned long)*t + pos);
                if ((d <= (unsigned short *)((unsigned long)*t + cap) && (unsigned short *)*t <= d) &&
                    1 < cap - pos && (*d = v, d <= d + 1)) {
                    *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 2;
                    return;
                }
                SoftwareBreakpoint(0x5519, 0x18b64);
            }
            goto fb;
        }
    } else {
        FUN_004b1150();
    }
    FUN_004b1198();
fb:
    unsigned long cur = (unsigned long)FUN_004b1174();
    t = *(unsigned long **)(cur + 0x50);
    d = (unsigned short *)((unsigned long)*t + t[2]);
    if ((1 < (unsigned long)(t[3] - t[2]) && d <= (unsigned short *)((unsigned long)*t + t[3])) &&
        (unsigned short *)*t <= d) {
        *d = v;
        *(unsigned long *)(cur + 0x50 + 0x10) = *(unsigned long *)(*(unsigned long *)(cur + 0x50) + 0x10) + 2;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x18bc4);
}

/* FUN_00018b98 @ 0x00018b98   (est. tb_put_u16_cur)
 * Ghidra: void FUN_00018b98(long param_1, undefined2 param_2)
 * Writes a u16 into the transport of message `m` directly. */
void tb_put_u16_cur(unsigned long m, unsigned short v)
{
    unsigned long *t = *(unsigned long **)(m + 0x50);
    unsigned short *d = (unsigned short *)((unsigned long)*t + t[2]);
    if ((1 < (unsigned long)(t[3] - t[2]) && d <= (unsigned short *)((unsigned long)*t + t[3])) &&
        (unsigned short *)*t <= d) {
        *d = v;
        *(unsigned long *)(*(unsigned long *)(m + 0x50) + 0x10) += 2;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x18bc4);
}

/* FUN_00018be8 @ 0x00018be8   (est. tb_get_u16)
 * Ghidra: dword * FUN_00018be8(dword *param_1, undefined2 *param_2)
 * Reads a u16 from a state-4 transport into *param_2 (fallback to current).
 * Traps. Returns the buffer. */
dword *tb_get_u16(dword *m, unsigned short *out)
{
    unsigned short *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 4) {
        t = *(unsigned long **)(m + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 1) {
            if (pos + 2 <= cap) {
                d = (unsigned short *)((unsigned long)*t + pos);
                t[2] = pos + 2;
                if ((unsigned short *)((unsigned long)*t + cap) < d || d < (unsigned short *)*t || cap - pos < 2) {
                    SoftwareBreakpoint(0x5519, 0x18c48);
                }
                *out = *d;
                return m;
            }
            goto fb;
        }
    } else {
        FUN_004b11bc();
nz:     FUN_004b1228();
    }
    FUN_004b1204();
fb:
    FUN_004b11e0();
    return &((dword *)0)[0];
}

/* ---- u32 put/get ---- */

/* FUN_00018c70 @ 0x00018c70   (est. tb_put_u32)
 * Ghidra: void FUN_00018c70(int *param_1, undefined4 param_2)
 * Writes a u32 into a state-1 transport (fallback to current). Traps. */
void tb_put_u32(int *m, unsigned int v)
{
    unsigned int *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (pos < ~0ull - 3) {
            cap = t[3];
            if (pos + 4 <= cap) {
                d = (unsigned int *)((unsigned long)*t + pos);
                if ((d <= (unsigned int *)((unsigned long)*t + cap) && (unsigned int *)*t <= d) &&
                    3 < cap - pos && (*d = v, d <= d + 1)) {
                    *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 4;
                    return;
                }
                SoftwareBreakpoint(0x5519, 0x18cc8);
            }
            goto fb;
        }
    } else {
        FUN_004b124c();
    }
    FUN_004b1294();
fb:
    unsigned long cur = (unsigned long)FUN_004b1270();
    t = *(unsigned long **)(cur + 0x50);
    d = (unsigned int *)((unsigned long)*t + t[2]);
    if ((3 < (unsigned long)(t[3] - t[2]) && d <= (unsigned int *)((unsigned long)*t + t[3])) &&
        (unsigned int *)*t <= d) {
        *d = v;
        *(unsigned long *)(cur + 0x50 + 0x10) += 4;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x18d28);
}

/* FUN_00018cfc @ 0x00018cfc   (est. tb_put_u32_cur) */
void tb_put_u32_cur(unsigned long m, unsigned int v)
{
    unsigned long *t = *(unsigned long **)(m + 0x50);
    unsigned int *d = (unsigned int *)((unsigned long)*t + t[2]);
    if ((3 < (unsigned long)(t[3] - t[2]) && d <= (unsigned int *)((unsigned long)*t + t[3])) &&
        (unsigned int *)*t <= d) {
        *d = v;
        *(unsigned long *)(*(unsigned long *)(m + 0x50) + 0x10) += 4;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x18d28);
}

/* FUN_00018d4c @ 0x00018d4c   (est. tb_get_u32) */
dword *tb_get_u32(dword *m, unsigned int *out)
{
    unsigned int *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 4) {
        t = *(unsigned long **)(m + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 3) {
            if (pos + 4 <= cap) {
                d = (unsigned int *)((unsigned long)*t + pos);
                t[2] = pos + 4;
                if ((unsigned int *)((unsigned long)*t + cap) < d || d < (unsigned int *)*t || cap - pos < 4) {
                    SoftwareBreakpoint(0x5519, 0x18dac);
                }
                *out = *d;
                return m;
            }
            goto fb;
        }
    } else {
        FUN_004b12b8();
nz:     FUN_004b1324();
    }
    FUN_004b1300();
fb:
    FUN_004b12dc();
    return &((dword *)0)[0];
}

/* ---- u64 put/get ---- */

/* FUN_00018dd4 @ 0x00018dd4   (est. tb_put_u64)
 * Ghidra: void FUN_00018dd4(int *param_1, undefined8 param_2)
 * Writes a u64 into a state-1 transport (fallback to current). Traps. */
void tb_put_u64(int *m, unsigned long v)
{
    unsigned long *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (pos < ~0ull - 7) {
            cap = t[3];
            if (pos + 8 <= cap) {
                d = (unsigned long *)((unsigned long)*t + pos);
                if ((d <= (unsigned long *)((unsigned long)*t + cap) && (unsigned long *)*t <= d) &&
                    7 < cap - pos && (*d = v, d <= d + 1)) {
                    *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 8;
                    return;
                }
                SoftwareBreakpoint(0x5519, 0x18e2c);
            }
            goto fb;
        }
    } else {
        FUN_004b1348();
    }
    FUN_004b1390();
fb:
    unsigned long cur = (unsigned long)FUN_004b136c();
    t = *(unsigned long **)(cur + 0x50);
    d = (unsigned long *)((unsigned long)*t + t[2]);
    if ((7 < (unsigned long)(t[3] - t[2]) && d <= (unsigned long *)((unsigned long)*t + t[3])) &&
        (unsigned long *)*t <= d) {
        *d = v;
        *(unsigned long *)(cur + 0x50 + 0x10) += 8;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x18e8c);
}

/* FUN_00018e60 @ 0x00018e60   (est. tb_put_u64_cur) */
void tb_put_u64_cur(unsigned long m, unsigned long v)
{
    unsigned long *t = *(unsigned long **)(m + 0x50);
    unsigned long *d = (unsigned long *)((unsigned long)*t + t[2]);
    if ((7 < (unsigned long)(t[3] - t[2]) && d <= (unsigned long *)((unsigned long)*t + t[3])) &&
        (unsigned long *)*t <= d) {
        *d = v;
        *(unsigned long *)(*(unsigned long *)(m + 0x50) + 0x10) += 8;
        return;
    }
    SoftwareBreakpoint(0x5519, 0x18e8c);
}

/* FUN_00018eb0 @ 0x00018eb0   (est. tb_put_words)
 * Ghidra: void FUN_00018eb0(long param_1, undefined8 param_2, ulong param_3)
 * Writes `n` words (param_3*8 bytes) from `src` into the transport of `m`,
 * with current-transport fallback when full. Traps on overflow. */
void tb_put_words(unsigned long m, unsigned long src, unsigned long n)
{
    if (n >> 0x3d == 0) {
        unsigned long bytes = n * 8;
        unsigned long *t = *(unsigned long **)(m + 0x50);
        unsigned long pos = t[2];
        if (pos + bytes < pos) goto alt;
        unsigned long base = *t;
        t[2] = pos + bytes;
        unsigned long d = base + pos;
        if ((d <= base + t[3] && base <= d) && bytes <= t[3] - pos &&
            FUN_00117cc4(d, src, bytes), d <= d + bytes) {
            return;
        }
        SoftwareBreakpoint(0x5519, 0x18f0c);
    } else {
        FUN_004b13d8();
    }
alt:
    unsigned long *cur = (unsigned long *)FUN_004b13b4();
    if (cur[0] == 4) {
        unsigned long *t2 = *(unsigned long **)(cur[0] + 0x14);
        unsigned long cap = t2[3];
        if (cap == 0) goto nz;
        unsigned long pos = t2[2];
        if (pos < ~0ull - 7) {
            if (pos + 8 <= cap) {
                unsigned long *d2 = (unsigned long *)((unsigned long)*t2 + pos);
                t2[2] = pos + 8;
                if ((unsigned long *)((unsigned long)*t2 + cap) < d2 || d2 < (unsigned long *)*t2 || cap - pos < 8) {
                    SoftwareBreakpoint(0x5519, 0x18f98);
                }
                *(unsigned long *)(cur[1]) = *d2;
                return;
            }
            goto fb;
        }
    } else {
        FUN_004b13fc();
nz:     FUN_004b1468();
    }
    FUN_004b1444();
fb:
    unsigned long cur2 = (unsigned long)FUN_004b1420();
    unsigned long *t3 = *(unsigned long **)(cur2 + 0x50);
    unsigned long pos = t3[2];
    unsigned long *d3 = (unsigned long *)((unsigned long)*t3 + pos);
    t3[2] = pos + 8;
    if ((unsigned long)(t3[3] - pos) < 8 || (unsigned long *)((unsigned long)*t3 + t3[3]) < d3 ||
        d3 < (unsigned long *)*t3) {
        SoftwareBreakpoint(0x5519, 0x18fec);
    }
    *(unsigned long *)(cur[1]) = *d3;
}

/* FUN_00018f38 @ 0x00018f38   (est. tb_get_words) */
void tb_get_words(int *m, unsigned long *out)
{
    unsigned long *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 4) {
        t = *(unsigned long **)(m + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 7) {
            if (pos + 8 <= cap) {
                d = (unsigned long *)((unsigned long)*t + pos);
                t[2] = pos + 8;
                if ((unsigned long *)((unsigned long)*t + cap) < d || d < (unsigned long *)*t || cap - pos < 8) {
                    SoftwareBreakpoint(0x5519, 0x18f98);
                }
                *out = *d;
                return;
            }
            goto fb;
        }
    } else {
        FUN_004b13fc();
nz:     FUN_004b1468();
    }
    FUN_004b1444();
fb:
    unsigned long cur = (unsigned long)FUN_004b1420();
    t = *(unsigned long **)(cur + 0x50);
    pos = t[2];
    d = (unsigned long *)((unsigned long)*t + pos);
    t[2] = pos + 8;
    if ((unsigned long)(t[3] - pos) < 8 || (unsigned long *)((unsigned long)*t + t[3]) < d ||
        d < (unsigned long *)*t) {
        SoftwareBreakpoint(0x5519, 0x18fec);
    }
    *out = *d;
}

/* FUN_00018fb8 @ 0x00018fb8   (est. tb_get_words_cur) */
void tb_get_words_cur(unsigned long m, unsigned long *out)
{
    unsigned long *t = *(unsigned long **)(m + 0x50);
    unsigned long pos = t[2];
    unsigned long *d = (unsigned long *)((unsigned long)*t + pos);
    t[2] = pos + 8;
    if ((unsigned long)(t[3] - pos) < 8 || (unsigned long *)((unsigned long)*t + t[3]) < d ||
        d < (unsigned long *)*t) {
        SoftwareBreakpoint(0x5519, 0x18fec);
    }
    *out = *d;
}

/* ---- pointer-returning put/get primitives ---- */

/* FUN_00019000 @ 0x00019000   (est. tb_put_u8p)
 * Ghidra: int * FUN_00019000(int *param_1, undefined1 param_2)
 * Writes a byte into a state-1 transport and returns the buffer, or reads from
 * a state-4 buffer and returns that buffer (matching the 18xxx u8 pair with a
 * pointer return). Traps on overflow. */
int *tb_put_u8p(int *m, unsigned char v)
{
    unsigned char *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (~0ull - 1 < pos) goto over;
        cap = t[3];
        if (pos + 1 <= cap) {
            d = (unsigned char *)*t + pos;
            if ((d <= (unsigned char *)*t + cap && (unsigned char *)*t <= d) &&
                cap != pos && (*d = v, d <= d + 1)) {
                *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 1;
                return m;
            }
            SoftwareBreakpoint(0x5519, 0x19054);
        }
    } else {
        FUN_004b148c();
over:   FUN_004b14d4();
    }
    int *m2 = (int *)FUN_004b14b0();
    if (m2[0] == 4) {
        t = *(unsigned long **)(m2 + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos != ~0ull) {
            if (pos + 1 <= cap) {
                d = (unsigned char *)*t + pos;
                t[2] = pos + 1;
                if ((unsigned char *)*t + cap < d || d < (unsigned char *)*t || cap == pos) {
                    SoftwareBreakpoint(0x5519, 0x190e4);
                }
                *(unsigned char *)&v = *d;
                return m2;
            }
            goto fb;
        }
    } else {
        FUN_004b14f8();
nz:     FUN_004b1564();
    }
    FUN_004b1540();
fb:
    FUN_004b151c();
    return (int *)((unsigned long)&((char *)0)[0] + 2);
}

/* FUN_0001910c @ 0x0001910c   (est. tb_put_u16p) */
dword *tb_put_u16p(dword *m, unsigned short v)
{
    unsigned short *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (~0ull - 1 < pos) goto over;
        cap = t[3];
        if (pos + 2 <= cap) {
            d = (unsigned short *)((unsigned long)*t + pos);
            if ((d <= (unsigned short *)((unsigned long)*t + cap) && (unsigned short *)*t <= d) &&
                1 < cap - pos && (*d = v, d <= d + 1)) {
                *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 2;
                return m;
            }
            SoftwareBreakpoint(0x5519, 0x19164);
        }
    } else {
        FUN_004b1588();
over:   FUN_004b15d0();
    }
    dword *m2 = (dword *)FUN_004b15ac();
    if (m2[0] == 4) {
        t = *(unsigned long **)(m2 + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 1) {
            if (pos + 2 <= cap) {
                d = (unsigned short *)((unsigned long)*t + pos);
                t[2] = pos + 2;
                if ((unsigned short *)((unsigned long)*t + cap) < d || d < (unsigned short *)*t || cap - pos < 2) {
                    SoftwareBreakpoint(0x5519, 0x191f8);
                }
                *(unsigned short *)&v = *d;
                return m2;
            }
            goto fb;
        }
    } else {
        FUN_004b15f4();
nz:     FUN_004b1660();
    }
    FUN_004b163c();
fb:
    FUN_004b1618();
    return &((dword *)0)[0];
}

/* FUN_00019220 @ 0x00019220   (est. tb_put_u32p) */
dword *tb_put_u32p(dword *m, unsigned int v)
{
    unsigned int *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (~0ull - 3 < pos) goto over;
        cap = t[3];
        if (pos + 4 <= cap) {
            d = (unsigned int *)((unsigned long)*t + pos);
            if ((d <= (unsigned int *)((unsigned long)*t + cap) && (unsigned int *)*t <= d) &&
                3 < cap - pos && (*d = v, d <= d + 1)) {
                *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 4;
                return m;
            }
            SoftwareBreakpoint(0x5519, 0x19278);
        }
    } else {
        FUN_004b1684();
over:   FUN_004b16cc();
    }
    dword *m2 = (dword *)FUN_004b16a8();
    if (m2[0] == 4) {
        t = *(unsigned long **)(m2 + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 3) {
            if (pos + 4 <= cap) {
                d = (unsigned int *)((unsigned long)*t + pos);
                t[2] = pos + 4;
                if ((unsigned int *)((unsigned long)*t + cap) < d || d < (unsigned int *)*t || cap - pos < 4) {
                    SoftwareBreakpoint(0x5519, 0x1930c);
                }
                *(unsigned int *)&v = *d;
                return m2;
            }
            goto fb;
        }
    } else {
        FUN_004b16f0();
nz:     FUN_004b175c();
    }
    FUN_004b1738();
fb:
    FUN_004b1714();
    return &((dword *)0)[0];
}

/* FUN_00019224 @ 0x00019224   (est. tb_put_u32p_b) — identical to 19220 */
dword *tb_put_u32p_b(dword *m, unsigned int v)
{
    unsigned int *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (~0ull - 3 < pos) goto over;
        cap = t[3];
        if (pos + 4 <= cap) {
            d = (unsigned int *)((unsigned long)*t + pos);
            if ((d <= (unsigned int *)((unsigned long)*t + cap) && (unsigned int *)*t <= d) &&
                3 < cap - pos && (*d = v, d <= d + 1)) {
                *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 4;
                return m;
            }
            SoftwareBreakpoint(0x5519, 0x19278);
        }
    } else {
        FUN_004b1684();
over:   FUN_004b16cc();
    }
    dword *m2 = (dword *)FUN_004b16a8();
    if (m2[0] == 4) {
        t = *(unsigned long **)(m2 + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 3) {
            if (pos + 4 <= cap) {
                d = (unsigned int *)((unsigned long)*t + pos);
                t[2] = pos + 4;
                if ((unsigned int *)((unsigned long)*t + cap) < d || d < (unsigned int *)*t || cap - pos < 4) {
                    SoftwareBreakpoint(0x5519, 0x1930c);
                }
                *(unsigned int *)&v = *d;
                return m2;
            }
            goto fb;
        }
    } else {
        FUN_004b16f0();
nz:     FUN_004b175c();
    }
    FUN_004b1738();
fb:
    FUN_004b1714();
    return &((dword *)0)[0];
}

/* FUN_000192b0 @ 0x000192b0   (est. tb_get_u32p) */
dword *tb_get_u32p(dword *m, unsigned int *out)
{
    unsigned int *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 4) {
        t = *(unsigned long **)(m + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 3) {
            if (pos + 4 <= cap) {
                d = (unsigned int *)((unsigned long)*t + pos);
                t[2] = pos + 4;
                if ((unsigned int *)((unsigned long)*t + cap) < d || d < (unsigned int *)*t || cap - pos < 4) {
                    SoftwareBreakpoint(0x5519, 0x1930c);
                }
                *out = *d;
                return m;
            }
            goto fb;
        }
    } else {
        FUN_004b16f0();
nz:     FUN_004b175c();
    }
    FUN_004b1738();
fb:
    FUN_004b1714();
    return &((dword *)0)[0];
}

/* FUN_00019334 @ 0x00019334   (est. tb_put_u64p) */
dword *tb_put_u64p(dword *m, unsigned long v)
{
    unsigned long *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (~0ull - 7 < pos) goto over;
        cap = t[3];
        if (pos + 8 <= cap) {
            d = (unsigned long *)((unsigned long)*t + pos);
            if ((d <= (unsigned long *)((unsigned long)*t + cap) && (unsigned long *)*t <= d) &&
                7 < cap - pos && (*d = v, d <= d + 1)) {
                *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 8;
                return m;
            }
            SoftwareBreakpoint(0x5519, 0x1938c);
        }
    } else {
        FUN_004b1780();
over:   FUN_004b17c8();
    }
    unsigned long *alt = (unsigned long *)FUN_004b17a4();
    dword *m2 = (dword *)alt[0];
    if (m2[0] == 4) {
        t = *(unsigned long **)(m2 + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 7) {
            if (pos + 8 <= cap) {
                d = (unsigned long *)((unsigned long)*t + pos);
                t[2] = pos + 8;
                if ((unsigned long *)((unsigned long)*t + cap) < d || d < (unsigned long *)*t || cap - pos < 8) {
                    SoftwareBreakpoint(0x5519, 0x19420);
                }
                *(unsigned long *)&v = *d;
                return m2;
            }
            goto fb;
        }
    } else {
        FUN_004b17ec();
nz:     FUN_004b1858();
    }
    FUN_004b1834();
fb:
    FUN_004b1810();
    return &((dword *)0)[0];
}

/* FUN_00019338 @ 0x00019338   (est. tb_put_u64p_b) — identical to 19334 */
dword *tb_put_u64p_b(dword *m, unsigned long v)
{
    unsigned long *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 1) {
        t = *(unsigned long **)(m + 0x14);
        pos = t[2];
        if (~0ull - 7 < pos) goto over;
        cap = t[3];
        if (pos + 8 <= cap) {
            d = (unsigned long *)((unsigned long)*t + pos);
            if ((d <= (unsigned long *)((unsigned long)*t + cap) && (unsigned long *)*t <= d) &&
                7 < cap - pos && (*d = v, d <= d + 1)) {
                *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 8;
                return m;
            }
            SoftwareBreakpoint(0x5519, 0x1938c);
        }
    } else {
        FUN_004b1780();
over:   FUN_004b17c8();
    }
    unsigned long *alt = (unsigned long *)FUN_004b17a4();
    dword *m2 = (dword *)alt[0];
    if (m2[0] == 4) {
        t = *(unsigned long **)(m2 + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 7) {
            if (pos + 8 <= cap) {
                d = (unsigned long *)((unsigned long)*t + pos);
                t[2] = pos + 8;
                if ((unsigned long *)((unsigned long)*t + cap) < d || d < (unsigned long *)*t || cap - pos < 8) {
                    SoftwareBreakpoint(0x5519, 0x19420);
                }
                *(unsigned long *)&v = *d;
                return m2;
            }
            goto fb;
        }
    } else {
        FUN_004b17ec();
nz:     FUN_004b1858();
    }
    FUN_004b1834();
fb:
    FUN_004b1810();
    return &((dword *)0)[0];
}

/* FUN_000193c4 @ 0x000193c4   (est. tb_get_u64p) */
dword *tb_get_u64p(dword *m, unsigned long *out)
{
    unsigned long *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 4) {
        t = *(unsigned long **)(m + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 7) {
            if (pos + 8 <= cap) {
                d = (unsigned long *)((unsigned long)*t + pos);
                t[2] = pos + 8;
                if ((unsigned long *)((unsigned long)*t + cap) < d || d < (unsigned long *)*t || cap - pos < 8) {
                    SoftwareBreakpoint(0x5519, 0x19420);
                }
                *out = *d;
                return m;
            }
            goto fb;
        }
    } else {
        FUN_004b17ec();
nz:     FUN_004b1858();
    }
    FUN_004b1834();
fb:
    FUN_004b1810();
    return &((dword *)0)[0];
}

/* ---- f32 encode/decode ---- */

/* FUN_00019440 @ 0x00019440   (est. tb_f32_size)
 * Ghidra: undefined8 FUN_00019440(void)
 * Returns the f32 encoded size: 4 bytes. */
unsigned long tb_f32_size(void)
{
    return 4;
}

/* FUN_00019448 @ 0x00019448   (est. tb_msg_encode_f32_chk)
 * Ghidra: void FUN_00019448(void)
 * Encodes the current f32 via FUN_00019490 and faults on error
 * (TB_FATAL tb_message_encode_f32). */
void tb_msg_encode_f32_chk(void)
{
    int r = FUN_00019490();
    if (r == 0) {
        return;
    }
    FUN_00118b28(TB_FATAL_ENC_F32);
    SoftwareBreakpoint(1, 0x19490);
}

/* FUN_00019490 @ 0x00019490   (est. tb_msg_encode_f32)
 * Ghidra: undefined8 FUN_00019490(uint param_1, int *param_2)
 * Encodes an IEEE-754 f32 (bit pattern `v`) into a state-1 transport,
 * advancing the position. Returns 0, or 6 if the value is a NaN/inf payload
 * (|exp| >= 0x7f800000). Falls to the decode fault on bad state.
 * Confidence: high | Notes: NaN check: (v & 0x7fffffff) > 0x7f7fffff -> 6. */
unsigned long tb_msg_encode_f32(unsigned int v, int *m)
{
    if (0x7f7fffff < (v & 0x7fffffff)) {
        return 6;
    }
    if (m[0] == 1) {
        unsigned long *t = *(unsigned long **)(m + 0x14);
        unsigned long pos = t[2];
        if (pos < ~0ull - 3) {
            unsigned long cap = t[3];
            if (pos + 4 <= cap) {
                unsigned int *d = (unsigned int *)((unsigned long)*t + pos);
                if ((d <= (unsigned int *)((unsigned long)*t + cap) && (unsigned int *)*t <= d) &&
                    3 < cap - pos && (*d = v, d <= d + 1)) {
                    *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 4;
                    return 0;
                }
                SoftwareBreakpoint(0x5519, 0x19504);
            }
            goto bad;
        }
    } else {
        FUN_004b187c();
    }
    FUN_004b18c4();
bad:
    FUN_004b18a0();
    unsigned long r = FUN_00019588();
    if ((int)r != 0) {
        FUN_00118b28(TB_FATAL_DEC_F32);
        SoftwareBreakpoint(1, 0x19588);
    }
    return r;
}

/* FUN_00019540 @ 0x00019540   (est. tb_msg_decode_f32_chk)
 * Ghidra: void FUN_00019540(void)
 * Decodes the current f32 via FUN_00019588 and faults on error
 * (TB_FATAL tb_message_decode_f32). */
void tb_msg_decode_f32_chk(void)
{
    int r = FUN_00019588();
    if (r == 0) {
        return;
    }
    FUN_00118b28(TB_FATAL_DEC_F32);
    SoftwareBreakpoint(1, 0x19588);
}

/* FUN_00019588 @ 0x00019588   (est. tb_msg_decode_f32)
 * Ghidra: undefined4 FUN_00019588(int *param_1, uint *param_2)
 * Decodes an IEEE-754 f32 from a state-4 transport into *param_2. Returns 0,
 * or 7 if the value is a NaN/inf payload, or 8 when no data remains.
 * Confidence: high */
unsigned int tb_msg_decode_f32(int *m, unsigned int *out)
{
    unsigned int *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 4) {
        t = *(unsigned long **)(m + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 3) {
            if (pos + 4 <= cap) {
                d = (unsigned int *)((unsigned long)*t + pos);
                t[2] = pos + 4;
                if ((unsigned int *)((unsigned long)*t + cap) < d || d < (unsigned int *)*t || cap - pos < 4) {
                    SoftwareBreakpoint(0x5519, 0x195e8);
                }
                unsigned int v = *d;
                *out = v;
                unsigned int r = 0;
                if (0x7f7fffff < (v & 0x7fffffff)) {
                    r = 7;
                }
                return r;
            }
            goto nz3;
        }
    } else {
        FUN_004b18e8();
nz:     FUN_004b1954();
    }
    FUN_004b1930();
nz3:
    FUN_004b190c();
    return 8;
}

/* FUN_00019620 @ 0x00019620   (est. tb_f64_size)
 * Ghidra: undefined8 FUN_00019620(void)
 * Returns the f64 encoded size: 8 bytes. */
unsigned long tb_f64_size(void)
{
    return 8;
}

/* FUN_00019628 @ 0x00019628   (est. tb_msg_encode_f64_chk)
 * Ghidra: void FUN_00019628(void)
 * Encodes the current f64 via FUN_00019670 and faults on error
 * (TB_FATAL tb_message_encode_f64). */
void tb_msg_encode_f64_chk(void)
{
    int r = FUN_00019670();
    if (r == 0) {
        return;
    }
    FUN_00118b28(TB_FATAL_ENC_F64);
    SoftwareBreakpoint(1, 0x19670);
}

/* FUN_00019670 @ 0x00019670   (est. tb_msg_encode_f64)
 * Ghidra: undefined8 FUN_00019670(ulong param_1, int *param_2)
 * Encodes an IEEE-754 f64 (bit pattern `v`) into a state-1 transport.
 * Returns 0, or 6 for NaN/inf payloads. Falls to decode fault on bad state.
 * Confidence: high | Notes: NaN check: (v & 0x7fffffffffffffff) >
 *   0x7fefffffffffffff -> 6. */
unsigned long tb_msg_encode_f64(unsigned long v, int *m)
{
    if (0x7fefffffffffffff < (v & 0x7fffffffffffffff)) {
        return 6;
    }
    if (m[0] == 1) {
        unsigned long *t = *(unsigned long **)(m + 0x14);
        unsigned long pos = t[2];
        if (pos < ~0ull - 7) {
            unsigned long cap = t[3];
            if (pos + 8 <= cap) {
                unsigned long *d = (unsigned long *)((unsigned long)*t + pos);
                if ((d <= (unsigned long *)((unsigned long)*t + cap) && (unsigned long *)*t <= d) &&
                    7 < cap - pos && (*d = v, d <= d + 1)) {
                    *(unsigned long *)(*(unsigned long *)(m + 0x14) + 0x10) += 8;
                    return 0;
                }
                SoftwareBreakpoint(0x5519, 0x196e4);
            }
            goto bad;
        }
    } else {
        FUN_004b1978();
    }
    FUN_004b19c0();
bad:
    FUN_004b199c();
    unsigned long r = FUN_00019768();
    if ((int)r != 0) {
        FUN_00118b28(TB_FATAL_DEC_F64);
        SoftwareBreakpoint(1, 0x19768);
    }
    return r;
}

/* FUN_00019720 @ 0x00019720   (est. tb_msg_decode_f64_chk)
 * Ghidra: void FUN_00019720(void)
 * Decodes the current f64 via FUN_00019768 and faults on error
 * (TB_FATAL tb_message_decode_f64). */
void tb_msg_decode_f64_chk(void)
{
    int r = FUN_00019768();
    if (r == 0) {
        return;
    }
    FUN_00118b28(TB_FATAL_DEC_F64);
    SoftwareBreakpoint(1, 0x19768);
}

/* FUN_00019768 @ 0x00019768   (est. tb_msg_decode_f64)
 * Ghidra: ulong FUN_00019768(int *param_1, ulong *param_2)
 * Decodes an IEEE-754 f64 from a state-4 transport into *param_2. Returns 0,
 * or 7 for NaN/inf payloads, or the buffer-error banner (DAT_005ac851) when
 * no data remains.
 * Confidence: high */
unsigned long tb_msg_decode_f64(int *m, unsigned long *out)
{
    unsigned long *d;
    unsigned long pos, cap;
    unsigned long *t;
    if (m[0] == 4) {
        t = *(unsigned long **)(m + 0x14);
        cap = t[3];
        if (cap == 0) goto nz;
        pos = t[2];
        if (pos < ~0ull - 7) {
            if (pos + 8 <= cap) {
                d = (unsigned long *)((unsigned long)*t + pos);
                t[2] = pos + 8;
                if ((unsigned long *)((unsigned long)*t + cap) < d || d < (unsigned long *)*t || cap - pos < 8) {
                    SoftwareBreakpoint(0x5519, 0x197c8);
                }
                unsigned long v = *d;
                *out = v;
                unsigned long r = 0;
                if (0x7fefffffffffffff < (v & 0x7fffffffffffffff)) {
                    r = 7;
                }
                return r;
            }
            goto nz3;
        }
    } else {
        FUN_004b19e4();
nz:     FUN_004b1a50();
    }
    FUN_004b1a2c();
nz3:
    FUN_004b1a08();
    return (unsigned long)FUN_00118b28(DAT_5ac851);
}

/* ---- small banner/identity helpers ---- */

/* FUN_00019800 @ 0x00019800   (est. tb_fatal_buf3)  prints DAT_005ac851. */
void tb_fatal_buf3(unsigned long v) { FUN_00118b28(DAT_5ac851); }
/* FUN_00019810 @ 0x00019810   (est. tb_fatal_size0)  prints TB size-0 buffer during... */
void tb_fatal_size0(unsigned long v) { FUN_00118b28(TB_FATAL_SIZE0); }
/* FUN_00019820 @ 0x00019820   (est. tb_fatal_buf4)  prints DAT_005ac6d1. */
void tb_fatal_buf4(unsigned long v) { FUN_00118b28(DAT_5ac6d1); }
/* FUN_00019830 @ 0x00019830   (est. tb_fatal_ovfl_dec2)  prints TB overflow during decode. */
void tb_fatal_ovfl_dec2(unsigned long v) { FUN_00118b28(TB_FATAL_OVFL_DEC); }
/* FUN_00019840 @ 0x00019840   (est. tb_fatal_ovfl_enc2)  prints TB overflow during encode. */
void tb_fatal_ovfl_enc2(unsigned long v) { FUN_00118b28(TB_FATAL_OVFL_ENC); }

/* FUN_00019850 @ 0x00019850   (est. tb_zero)
 * Ghidra: undefined8 FUN_00019850(void)
 * Returns 0. */
unsigned long tb_zero(void) { return 0; }

/* FUN_00019858 @ 0x00019858   (est. tb_zero128)
 * Ghidra: undefined1 [16] FUN_00019858(void)
 * Returns a 128-bit zero. */
unsigned long long tb_zero128(void)
{
    return 0;
}

/* FUN_00019aac @ 0x00019aac   (est. tb_register)
 * Ghidra: void FUN_00019aac(undefined8 param_1)
 * Registers a transport object (param_1) into the global slot (DAT_0064c098)
 * via FUN_0001a0d0 with a stored callback (LAB_006593e8).
 * Confidence: low */
void tb_register(unsigned long v)
{
    FUN_0001a0d0(v, &_DAT_0064c098, &_LAB_006593e8);
}

/* FUN_00019d40 @ 0x00019d40   (est. tb_emit_tag)
 * Ghidra: long FUN_00019d40(long *param_1, long *param_2)
 * Stores the word *param_2 into *param_1, emits it via FUN_0036b270, and
 * returns param_2 + 0x10 (advancing the tag cursor by 16 bytes).
 * Confidence: low | Notes: FUN_0036b270 = tag emitter. */
long tb_emit_tag(long *out, long *src)
{
    long v = *src;
    *out = v;
    FUN_0036b270(v);
    return (long)src + 0x10;
}

/* FUN_0001a0d0 @ 0x0001a0d0   (est. tb_slot_set_if_empty)
 * Ghidra: void FUN_0001a0d0(undefined8 param_1, long *param_2, undefined8 param_3)
 * If *param_2 is zero, invokes FUN_00376038(param_1, param_3); when the result
 * high word is zero, stores the low word into *param_2.
 * Confidence: low | Notes: FUN_00376038 = object resolver. */
void tb_slot_set_if_empty(unsigned long v, long *slot, unsigned long cb)
{
    if (*slot != 0) {
        return;
    }
    unsigned long long r = FUN_00376038(v, cb);
    if (r >> 64 == 0) {
        *slot = (long)(unsigned int)r;
    }
}

/* FUN_0001a11c @ 0x0001a11c   (est. tb_list_test)
 * Ghidra: uint FUN_0001a11c(void)
 * Returns bit 0 of FUN_0001a138() — the "in list" predicate result.
 * Confidence: medium */
unsigned int tb_list_test(unsigned long h, unsigned long v)
{
    unsigned int r = tb_sorted_lookup(h, v);
    return r & 1;
}

/* FUN_0001a138 @ 0x0001a138   (est. tb_sorted_lookup)
 * Ghidra: bool FUN_0001a138(long param_1, ulong param_2)
 * Binary-search `key` in the sorted word array at param_1 (count at +0x08,
 * base at +0x10). Returns whether `key` is present. Traps on out-of-range
 * indices. param_1==0 -> true (empty/absent means present).
 * Confidence: medium */
bool tb_sorted_lookup(unsigned long rec, unsigned long key)
{
    bool found;
    if (rec == 0) {
        found = true;
    } else {
        if (*(unsigned long *)(rec + 0x10) == 0) {
            return false;
        }
        long count = *(long *)(rec + 8);
        if (count < 0) {
            SoftwareBreakpoint(1, 0x1a1c8);
        }
        long lo = 0;
        long hi = count - 1;
        long mid = hi / 2;
        while ((found = lo <= mid && mid <= hi), lo <= mid && mid <= hi) {
            if (count <= mid) {
                SoftwareBreakpoint(1, 0x1a1c4);
            }
            unsigned long v = *(unsigned long *)(*(unsigned long *)(rec + 0x10) + mid * 8);
            if (v == key) {
                return found;
            }
            if (key < v) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
            long step = (hi - lo) / 2;
            mid = lo + step;
            if (lo + step < lo) {
                SoftwareBreakpoint(1, 0x1a1c0);
            }
        }
    }
    return found;
}

/* FUN_0001a1c8 @ 0x0001a1c8   (est. tb_nop)
 * Ghidra: void FUN_0001a1c8(void)
 * No-op. */
void tb_nop(void)
{
}

/* FUN_0001a1cc @ 0x0001a1cc   (est. tb_identity)
 * Ghidra: undefined8 FUN_0001a1cc(undefined8 param_1, undefined8 param_2)
 * Returns param_2 (identity on the second argument). */
unsigned long tb_identity(unsigned long a, unsigned long b)
{
    return b;
}

/* FUN_0001a1dc @ 0x0001a1dc   (est. tb_va_cap_resolve)
 * Ghidra: ulong FUN_0001a1dc(undefined8 param_1, undefined8 param_2, ulong param_3, ulong param_4)
 * Resolves a virtual-address/capability pair (addr param_3, flags param_4)
 * into a transport object. For the "tagged" form (param_4 bit 0x10) extracts
 * the index field; for the "extended" form invokes FUN_002b24b8 and
 * FUN_0001d4a0, then dispatches on the kind bits through FUN_0001a2f4. Returns
 * the resolved index/cap.
 * Confidence: low | Notes: FUN_0001a2f4 dispatcher; FUN_003a25d4 release. */
unsigned long tb_va_cap_resolve(unsigned long a, unsigned long b, unsigned long addr, unsigned long flags)
{
    unsigned long idx;
    unsigned long long p = ((unsigned long long)flags << 32) | addr;
    if ((flags >> 0x3c & 1) == 0) {
        idx = addr & 0xffffffffffff;
        if ((flags & 0x2000000000000000) != 0) {
            idx = flags >> 0x38 & 0xf;
        }
        FUN_0036b270(flags);
    } else {
        idx = (unsigned long)FUN_002b24b8(addr, flags);
        FUN_0036b270(flags);
        p = FUN_0001d4a0(addr, flags);
        FUN_003a25d4(flags);
    }
    unsigned long lo = (unsigned long)(unsigned int)p;
    unsigned long hi = (unsigned long)(unsigned long long)p >> 32;
    if ((hi >> 0x3d & 1) == 0) {
        unsigned long long q;
        if ((lo >> 0x3c & 1) == 0) {
            q = FUN_002a9ba8(lo, hi);
        } else {
            q = ((unsigned long long)((hi & 0xfffffffffffffff) + 0x20) << 32) |
                (lo & 0xffffffffffff);
        }
        FUN_0001a2f4((void *)(unsigned int)q, q >> 32, a, b, idx);
    } else {
        FUN_0001a2f4(&lo, hi >> 0x38 & 0xf, a, b, idx);
    }
    FUN_003a25d4(hi);
    return idx;
}
