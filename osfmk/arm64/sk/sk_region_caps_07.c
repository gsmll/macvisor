/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 07: 0x9e2b4-0xa3864 caps region.
 *
 * Region characterisation: mostly the TimeTrace performance-trace subsystem
 * (timespan records, root trace, buffer growth), MACH-O segment/DART loading
 * (__TEXT/__DATA/__MACHO__DART segment walk, bundle segment compression), and
 * CSpace / capability-table lookup + accessor helpers. Many bodies read their
 * context from callee-saved registers (x20 = "self", x21 = status) set up by
 * the caller; those are surfaced as explicit parameters with a note.
 */

#include <stdint.h>
#include <stddef.h>

#include "sk_internal.h"

/* =====================================================================
 * Out-of-slice microkernel primitives (declared extern; names = Ghidra).
 * These live outside 0x9e2b4-0xa3864 and are referenced by this region.
 * Variadic forms are used where the decompile shows varying arity.
 * ===================================================================== */

extern word_t FUN_0036a940(word_t _a, ...);      /* object allocator (zone/metadata) */
extern word_t FUN_0036b118(word_t _a, ...);      /* release/refdrop, returns obj */
extern word_t FUN_0036b270(word_t _a, ...);      /* retain/refhold */
extern void  FUN_0036b6ac(word_t _a, ...); /* object finalize/destruct */
extern void  FUN_0036b6f4(void);      /* error/abort cleanup path */
extern word_t FUN_0036a9a0(word_t _a, ...);      /* object create from metadata */
extern void  FUN_0036a1a0(word_t _a, ...);       /* object attribute set */
extern void  FUN_0036a20c(word_t _a, ...);       /* object attribute clear/commit */
extern void  FUN_003a25d4(word_t);    /* trace/log emit (word + tag) */
extern word_t FUN_003a261c(word_t _a, ...);       /* trace helper */
extern void  thunk_FUN_002acbb8(word_t _a, ...); /* trace format emit */
extern void  FUN_002a4ab4(word_t);    /* trace section begin */
extern word_t FUN_00027724(word_t _a, ...);      /* type/method lookup -> fn ptr */
extern word_t FUN_00002534(word_t _a, ...);      /* metadata lookup -> object hdr */
extern void  FUN_0026b434(word_t _a, ...);       /* object setup */
extern void  FUN_0036b588(word_t);    /* object publish */
extern word_t FUN_00002688(void);     /* object id/counter */
extern void  FUN_000026e8(word_t);    /* object init */
extern void  FUN_000027e8(void);      /* object context */
extern void  FUN_00002818(void);      /* trace abort path */
extern void  FUN_00002828(word_t _a, ...);       /* attribute snapshot */
extern void  FUN_00002874(word_t _a, ...);       /* attribute/string emit */
extern void  FUN_001afa84(word_t _a, ...);       /* Noreturn fatal/panic sink */
extern void  FUN_000fdb98(word_t);    /* object dispose */
extern word_t FUN_0006a4c0(word_t _a, ...);      /* object method bind */
extern word_t FUN_0006cf50(word_t _a, ...);      /* region/segment handle lookup */
extern word_t FUN_0006d0b8(word_t _a, ...);      /* address -> token */
extern void  FUN_00084824(word_t _a, ...);       /* region record append */
extern word_t FUN_00092c00(word_t _a, ...);      /* counter/state */
extern word_t FUN_000e4078(word_t _a, ...);      /* stream/sink alloc */
extern word_t FUN_00117cc4(word_t _a, ...);      /* memcpy */
extern word_t FUN_001051e0(word_t _a, ...);      /* uuid/metadata copy */
extern word_t FUN_000739d8(word_t _a, ...);      /* vector grow/realloc */
extern word_t FUN_001ee018(word_t _a, ...);      /* buffer length lookup */
extern void  FUN_002cb61c(word_t _a, ...);       /* buffer copy */
extern void  FUN_002a4468(word_t _a, ...);       /* buffer write */
extern word_t FUN_001ed960(word_t _a, ...);      /* timestamp/clock read */
extern word_t FUN_001003e8(word_t _a, ...);      /* state guard */
extern word_t FUN_000ff728(word_t _a, ...);      /* register callback */
extern void  FUN_0006e7c0(word_t _a, ...);       /* object init */
extern word_t FUN_00077070(word_t _a, ...);      /* object bind */
extern void  FUN_000fce3c(word_t _a, ...);       /* deferred call */
extern word_t FUN_0036b2d0(word_t _a, ...);      /* list insert */
extern word_t FUN_0007b250(word_t _a, ...);      /* queue/notify */
extern word_t FUN_0007b42c(word_t _a, ...);      /* queue count */
extern word_t FUN_0006bb8c(void);     /* perf counter 1 */
extern word_t FUN_0006bb98(void);     /* perf counter 2 */
extern word_t FUN_0006bba4(void);     /* perf counter 3 */
extern word_t FUN_000867a8(word_t _a, ...);      /* object attr read */
extern void  FUN_0008e3b0(word_t _a, ...);       /* object attr reset */
extern word_t FUN_00107224(void);     /* flag register read */
extern word_t FUN_00107200(void);
extern word_t FUN_001071f4(void);
extern word_t FUN_0010720c(void);
extern word_t FUN_0013f738(void);     /* flag register read */
extern word_t FUN_0013f720(void);
extern word_t FUN_0013f72c(void);
extern word_t FUN_0001a1c8(word_t _a, ...);      /* flag mask helper */
extern word_t FUN_00141e64(void);     /* capability flag test */
extern word_t FUN_00141d44(void);
extern word_t FUN_00141b14(void);
extern word_t FUN_001420a4(void);
extern word_t FUN_0013bf20(word_t _a, ...);      /* capability resolve */
extern word_t FUN_001fac04(word_t _a, ...);      /* array alloc */
extern word_t FUN_0006a374(word_t _a, ...);      /* vector ensure */
extern word_t FUN_00082524(word_t _a, ...);      /* region ensure */
extern word_t FUN_00082584(word_t _a, ...);      /* region ensure (variant) */
extern word_t FUN_00076fc0(void);     /* obj context */
extern word_t FUN_001bc440(word_t _a, ...);      /* object create */
extern word_t FUN_0006f768(word_t _a, ...);      /* trace abort with string */
extern word_t FUN_0010b6bc(word_t _a, ...);      /* container init */
extern word_t FUN_0010b560(word_t _a, ...);      /* container attr read */
extern word_t FUN_0010b824(word_t _a, ...);      /* container attr read 2 */
extern word_t FUN_00106958(word_t _a, ...);      /* container append */
extern word_t FUN_001404d0(word_t _a, ...);      /* stream alloc */
extern word_t FUN_001404e0(word_t _a, ...);
extern word_t FUN_001401c0(word_t _a, ...);      /* stream write */
extern word_t FUN_00106c88(word_t _a, ...);      /* stream hdr */
extern word_t FUN_0022d2f4(word_t _a, ...);      /* stream build */
extern word_t FUN_00365b6c(word_t _a, ...);      /* container lookup */
extern word_t FUN_000839f8(word_t _a, ...);      /* iterator step */
extern word_t FUN_00377824(word_t _a, ...);      /* iterator metadata */
extern word_t FUN_00377bec(word_t _a, ...);      /* iterator create */
extern word_t FUN_00310d68(word_t _a, ...);      /* iterator alloc */
extern word_t FUN_00310d80(word_t _a, ...);
extern word_t FUN_0019e410(word_t _a, ...);      /* stream finalize */
extern word_t FUN_0019e538(word_t _a, ...);
extern word_t FUN_0019e578(word_t _a, ...);
extern word_t FUN_00268540(word_t _a, ...);      /* thread/context lookup */
extern word_t FUN_001d1d54(word_t _a, ...);      /* (thunk) finish */
extern word_t FUN_000d1d54(word_t _a, ...);      /* finish/enum tail */
extern word_t FUN_0001a448(word_t _a, ...);      /* thunk register pair */
extern word_t FUN_0039a128(void);     /* boot/init hook */
extern word_t FUN_000a6fc8(word_t _a, ...);      /* (out of slice) cap lookup */
extern word_t FUN_000a6fd4(word_t _a, ...);
extern void  FUN_000a6e40(word_t _a, ...);
extern void  FUN_000a6ee4(word_t _a, ...);
extern void  FUN_000a6e70(word_t _a, ...);
extern void  FUN_000a6e80(word_t _a, ...);
extern void  FUN_000a6e50(word_t _a, ...);
extern word_t FUN_000a6e20(word_t _a, ...);
extern void  FUN_000a6d08(word_t _a, ...);
extern void  FUN_000a6d44(word_t _a, ...);
extern void  FUN_000a6d58(word_t _a, ...);
extern void  FUN_000a6d70(word_t _a, ...);
extern void  FUN_000a6d88(word_t _a, ...);
extern void  FUN_000a6dac(word_t _a, ...);
extern void  FUN_000a6ddc(word_t _a, ...);
extern void  FUN_000a6ecc(word_t _a, ...);
extern void  FUN_000a6f08(word_t _a, ...);
extern void  FUN_000a6f20(word_t _a, ...);
extern void  FUN_000a6f38(word_t _a, ...);
extern void  FUN_000a6f50(word_t _a, ...);
extern word_t FUN_000a6f68(word_t _a, ...);
extern void  FUN_000a6f74(word_t _a, ...);
extern void  FUN_000a6f88(word_t _a, ...);
extern void  FUN_000a6fbc(word_t _a, ...);
extern void  FUN_000a6fb0(word_t _a, ...);
extern void  FUN_000a6840(word_t _a, ...);
extern word_t FUN_000a6894(word_t _a, ...);
extern word_t FUN_000a68c4(word_t _a, ...);
extern word_t FUN_000a68f4(word_t _a, ...);
extern word_t FUN_000a649c(word_t _a, ...);
extern word_t FUN_000a6b64(word_t _a, ...);
extern word_t FUN_000a6b94(word_t _a, ...);
extern word_t FUN_000a6bb8(word_t _a, ...);
extern word_t FUN_000a6be8(word_t _a, ...);
extern word_t FUN_000a6c18(word_t _a, ...);
extern void  FUN_000a63f0(word_t _a, ...);      /* cap record decode */
extern void  FUN_000a6444(word_t _a, ...);      /* cap record free */
extern void  FUN_000a6e08(word_t _a, ...);      /* boot-arg emit */
extern void  FUN_000a6e14(word_t _a, ...);
extern word_t FUN_0006ae9c(word_t _a, ...);     /* cap table find */
extern word_t FUN_0006f6b4(word_t _a, ...);     /* thunk */
extern word_t FUN_00072664(word_t _a, ...);      /* (thunk) cap slot get */
extern void  FUN_00072570(word_t _a, ...);
extern word_t FUN_00118328(word_t _a, ...);     /* state check */
extern void  FUN_00294bdc(word_t _a, ...);      /* panic log */
extern word_t FUN_00034f70(void);    /* page alloc */
extern word_t FUN_0006d0b8(word_t _a, ...);
extern void  FUN_00151a6c(word_t _a, ...);      /* exception log */
extern word_t FUN_00151974(void);
extern word_t FUN_0009461c(void);               /* exception/log flush */
extern word_t FUN_00083a78(word_t _a, ...);     /* record -> string */
extern word_t FUN_001dd77c(word_t _a, ...);     /* FFO list helper */
extern word_t FUN_001dd858(word_t _a, ...);     /* FFO list count */
extern word_t FUN_002a0cf8(word_t _a, ...);     /* range compare */
extern word_t FUN_000e2a34(void);               /* trace section */
extern word_t FUN_000a5da0(word_t _a, ...);     /* table mapper */
extern word_t FUN_000a6104(word_t _a, ...);     /* list mapper */
extern word_t FUN_000a6b2c(word_t _a, ...);     /* stream callback */
extern word_t FUN_000a64d8(word_t _a, ...);     /* stream callback */
extern word_t FUN_001fac04(word_t _a, ...);     /* array alloc */
extern word_t FUN_001004b8(word_t _a, ...);     /* exception trace */
extern word_t FUN_001404e0(word_t _a, ...);     /* stream alloc */
extern word_t FUN_001401c0(word_t _a, ...);     /* stream write */
extern word_t FUN_0022d2f4(word_t _a, ...);     /* stream build */
extern word_t FUN_00365b6c(word_t _a, ...);     /* container lookup */
extern word_t FUN_00310d80(word_t _a, ...);     /* stream hdr */
extern word_t FUN_000a5d40(word_t _a, ...);     /* __DATA size */
extern word_t FUN_000a5d70(word_t _a, ...);     /* __TEXT size */
extern void  FUN_00141960(void);

/* Supervisor call entry (secure monitor boundary; the TPIDRRO_EL0 handshake). */
extern void CallSupervisor(uint32_t code);

/* Forward declarations for in-slice functions (defined below). */
void FUN_0009e2b4(word_t fault_obj);
void FUN_0009e2e8(word_t *out, word_t *self);
word_t FUN_0009e2f4(word_t msg_obj, long *target, word_t *self, word_t status);
word_t FUN_0009e440(word_t *_hi, word_t *_lo);
void FUN_0009e508(void);
void FUN_0009e52c(word_t *out, word_t *self);
word_t FUN_0009e550(word_t a, word_t b, word_t *self, word_t status);
void FUN_0009e5a8(word_t obj, word_t param_2, word_t *self, word_t status);
void FUN_0009e7c4(word_t msg_obj, word_t cap);
void FUN_0009e83c(word_t *out, word_t param_2, word_t *self, word_t status);
word_t FUN_0009e8d0(word_t *_hi);
void FUN_0009e8ec(word_t *out, word_t p, word_t *self, word_t status);
void FUN_0009e8f0(word_t *out, word_t p, word_t *self, word_t status);
word_t FUN_0009e904(void);
word_t FUN_0009e908(void);
word_t FUN_0009e92c(word_t msg);
word_t FUN_0009e98c(word_t msg, word_t *extra);
void FUN_0009e9f4(word_t *self);
void FUN_0009e9f8(word_t *self);
long FUN_0009ea60(word_t desc);
void FUN_0009ea90(word_t param_1, word_t param_2);
void FUN_0009eab4(word_t *out, word_t *self);
word_t FUN_0009ead0(word_t msg_obj, long *target, word_t *self, word_t status);
void FUN_0009ec1c(word_t *out, word_t *self);
word_t FUN_0009ec40(word_t a, word_t b, word_t c, word_t d, word_t *self, word_t status);
void FUN_0009ecb0(word_t obj, word_t param_2, uint16_t param_3, word_t param_4,
                  word_t *self, word_t status);
void FUN_0009edd4(word_t *out, word_t param_2, word_t *self, word_t status);
word_t FUN_0009ee68(word_t *_hi);
void FUN_0009ee84(word_t *self);
void FUN_0009ee88(word_t *self);
void FUN_0009eeb0(word_t *out, word_t p, word_t *self, word_t status);
void FUN_0009eeb4(word_t *out, word_t p, word_t *self, word_t status);
word_t FUN_0009eec8(void);
word_t FUN_0009eecc(void);
void FUN_0009eef0(word_t param_1, word_t param_2);
word_t FUN_0009ef4c(word_t *_hi);
void FUN_0009ef5c(word_t *self);
word_t FUN_0009ef9c(word_t *self);
void * FUN_0009efd4(void);
void FUN_0009f00c(void);
void FUN_0009f05c(word_t new_root);
word_t FUN_0009f0bc(word_t param_1, word_t *_hi);
word_t FUN_0009f124(word_t *self);
void FUN_0009f150(word_t val, word_t *self);
word_t FUN_0009f190(word_t *_hi, word_t *self);
void FUN_0009f1c0(word_t *self);
void FUN_0009f200(long depth, word_t *self);
word_t FUN_0009f5cc(word_t *self);
void FUN_0009f6cc(long dest, long src, word_t param_3, word_t param_4);
word_t FUN_0009f728(word_t *self);
void FUN_0009f7b0(word_t *self);
void FUN_0009f7b4(word_t *self);
void FUN_0009f7d4(word_t *self);
word_t FUN_0009f834(word_t *_hi);
word_t FUN_0009f844(word_t *self);
void FUN_0009f88c(word_t *out, word_t id_lo, word_t id_hi, word_t *self);
void FUN_0009fbf8(word_t *rec, word_t *self);
void FUN_0009fd6c(word_t *self);
void FUN_0009fe78(word_t *dst, long src_end, word_t *self);
word_t FUN_0009ff20(word_t param_1, word_t p2, word_t p3, word_t p4);
void FUN_000a00c4(word_t *self);
void FUN_000a00ec(word_t *self);
void FUN_000a00f0(word_t *self);
void FUN_000a01c8(word_t param_1, word_t *self);
void FUN_000a01cc(word_t param_1, word_t *self);
word_t FUN_000a01e8(word_t *_hi);
word_t FUN_000a0208(word_t _a, ...);
void FUN_000a021c(void);
word_t FUN_000a022c(word_t param_1, word_t cnode);
void FUN_000a0278(word_t param_1, word_t cnode);
word_t FUN_000a02cc(word_t param_1, word_t param_2, word_t cnode, word_t *_hi);
void FUN_000a0368(word_t param_1, word_t cnode);
word_t FUN_000a03d8(word_t param_1, word_t cnode);
word_t FUN_000a0420(word_t param_1, word_t cnode);
void FUN_000a046c(word_t param_1, word_t cnode);
void FUN_000a04bc(word_t *out, word_t param_2, word_t cnode);
void FUN_000a0524(word_t param_1, word_t cnode);
word_t FUN_000a056c(word_t param_1, word_t cnode);
void FUN_000a05c0(word_t *out, word_t param_2, word_t cnode);
void FUN_000a0650(word_t *out, word_t param_2, word_t cnode);
void * FUN_000a06cc(word_t param_1);
word_t FUN_000a0c8c(word_t cb, word_t param_2, word_t param_3, word_t param_4,
                  word_t param_5, word_t param_6, word_t param_7, word_t param_8,
                  word_t status);
void * FUN_000a12e0(word_t param_1);
word_t FUN_000a1558(word_t param_1, word_t param_2, word_t cnode, word_t *_hi);
void FUN_000a1630(word_t *out, word_t param_2, word_t param_3, word_t cnode);
void FUN_000a16ec(word_t *out, word_t *cnode);
void FUN_000a17f4(word_t param_1, word_t param_2, word_t cnode);
void FUN_000a17f8(word_t param_1, word_t param_2, word_t cnode);
word_t FUN_000a18c4(word_t param_1);
long FUN_000a1990(word_t status);
word_t FUN_000a1ad4(word_t param_1);
int FUN_000a1b20(word_t *param_1);
word_t FUN_000a1b3c(word_t *_hi);
word_t FUN_000a1bd8(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                    word_t param_5, word_t param_6, word_t param_7, word_t *_hi);
long FUN_000a2094(word_t param_1, word_t param_2, word_t param_3);
long FUN_000a221c(word_t param_1, word_t param_2, word_t param_3);
void FUN_000a240c(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                  word_t param_5, word_t param_6, word_t param_7, word_t param_8);
word_t FUN_000a2820(word_t a, word_t b, word_t c, word_t d, word_t *self);
long FUN_000a2888(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                  word_t *self);
void FUN_000a2bfc(word_t param_1);
word_t FUN_000a2c24(word_t param_1, word_t param_2, word_t param_3, word_t cb);
void FUN_000a2cd8(word_t *self);
void FUN_000a2d70(word_t *param_1, word_t *param_2);
void FUN_000a2fe8(word_t *self);
void FUN_000a3018(word_t *self);
void FUN_000a301c(word_t *self);
void FUN_000a3040(word_t *self);
uint32_t FUN_000a30b0(uint32_t param_1);
void FUN_000a3168(word_t *a, word_t *b);
word_t FUN_000a31b0(word_t *_hi, word_t *self);
void FUN_000a31e0(word_t param_1, word_t param_2, word_t *self);
word_t FUN_000a3220(word_t *_hi, word_t *self);
word_t FUN_000a325c(word_t *self);
void FUN_000a328c(word_t val, word_t *self);
word_t FUN_000a32c0(word_t param_1, word_t *_hi, word_t *self);
word_t FUN_000a3310(word_t *self);
void FUN_000a33c0(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f, word_t *self, word_t status);
void FUN_000a3444(word_t *param_1, word_t param_2, word_t param_3, word_t param_4,
                  word_t *self, word_t status);
void FUN_000a35d0(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                  word_t param_5, word_t param_6, word_t *self, word_t status);
void FUN_000a3864(word_t *out, word_t param_2, word_t param_3, word_t param_4,
                  word_t param_5, word_t param_6, word_t status);


/* Globals referenced from this region (Ghidra DAT_* symbols). */
extern word_t _DAT_006ad9c8;
extern word_t _DAT_00657778;
extern word_t _DAT_00657788;
extern word_t _DAT_00657790;
extern word_t _DAT_00657798[];
extern word_t _DAT_006577a0[];

/* Register/meta constants (symbol addresses from Ghidra). */
#define FUN_0064fe58 ((word_t)0x64fe58)
#define thunk_FUN_0036b270 FUN_0036b270
#define thunk_FUN_00072664 FUN_00072664
#define thunk_FUN_0001a448 FUN_0001a448

static inline word_t LZCOUNT_64(word_t v){ return v ? (word_t)__builtin_clzll(v) : 64; }

/* =====================================================================
 * 0x0009e2b4
 * ===================================================================== */

/* FUN_0009e2b4 @ 0x0009e2b4   (est. sk_fault_caps_generic)
 * Ghidra: void FUN_0009e2b4(undefined8 param_1)
 * Forwards a capability-object fault to the shared noreturn fatal path with
 * fault class 0xb and severity 2. Never returns.
 * Confidence: low
 * Notes: noreturn delegate to FUN_001afa84(param_1, 0xb, 2). */
void FUN_0009e2b4(word_t fault_obj)
{
    FUN_001afa84(fault_obj, 0xb, 2);
}

/* FUN_0009e2e8 @ 0x0009e2e8   (est. sk_caps_read_self_word)
 * Ghidra: void FUN_0009e2e8(undefined8 *param_1)
 * Reads a single word at self+0x20 (self held in callee-saved x20) into *out.
 * A trivial context accessor; body is register-faithful.
 * Confidence: low
 * Notes: *(x20+0x20) -> *out; x20 = self context. */
void FUN_0009e2e8(word_t *out, word_t *self)
{
    *out = *(word_t *)((uintptr_t)self + 0x20);
}

/* FUN_0009e2f4 @ 0x0009e2f4   (est. sk_caps_dispatch_recv)
 * Ghidra: void FUN_0009e2f4(undefined8 param_1,long *param_2)
 * Stores the message/capability object into self+0x10, invokes the callee's
 * method slot +0x1b8 with 2 arguments, and copies the returned 9-word message
 * record into self+0x18..0x49 on success (x21==0). On failure releases all
 * held objects and runs the abort path.
 * Confidence: low
 * Notes: reads *( *param_2 + 0x1b8 ); GENTER-like dispatch via vtable. */
word_t FUN_0009e2f4(word_t msg_obj, long *target, word_t *self, word_t status)
{
    word_t obj;
    word_t rec[9];
    word_t m0, m1, m2, m3, m4;
    word_t hi, lo;

    *(word_t *)((uintptr_t)self + 0x10) = msg_obj;
    /* method +0x1b8 on the target object performs the receive. */
    ((word_t (*)(word_t *, word_t, word_t, word_t, word_t, word_t))
        *(word_t *)(*(word_t *)target + 0x1b8))((word_t *)&rec[0], 2, 0, 0, 0, 0);
    if (status == 0) {
        *(word_t *)((uintptr_t)self + 0x18) = rec[0];
        *(word_t *)((uintptr_t)self + 0x20) = rec[1];
        *(word_t *)((uintptr_t)self + 0x28) = rec[2];
        *(word_t *)((uintptr_t)self + 0x30) = rec[3];
        *(word_t *)((uintptr_t)self + 0x38) = rec[4];
        /* 7- and 8-byte packed tail at +0x40/+0x41..0x49 */
        *(word_t *)((uintptr_t)self + 0x40) = rec[5];
        *(word_t *)((uintptr_t)self + 0x48) = rec[6];
        m0 = *(word_t *)(*(word_t *)((uintptr_t)self + 0x10) + 0x10);
        FUN_0036b270(m0);
        FUN_000fdb98((word_t)&rec[0]);
        FUN_0036b118(m0);
        FUN_0036b118(msg_obj);
        FUN_0036b118((word_t)target);
    } else {
        FUN_0036b118(msg_obj);
        FUN_0036b118((word_t)target);
        FUN_0036b118(*(word_t *)((uintptr_t)self + 0x10));
        FUN_0036b6f4();
    }
    return 0;
}

/* FUN_0009e440 @ 0x0009e440   (est. sk_init_caps_bitmap)
 * Ghidra: undefined1 [16] FUN_0009e440(void)
 * Initialises the capability bitmap/zone machinery and returns a 128-bit
 * (tag,ptr) capability object descriptor {0xd00000000000003a,
 * 0x80000000005c18c0}.
 * Confidence: low
 * Notes: runs init 0x1d, sets mask 0xe0.., returns packed object pair. */
word_t FUN_0009e440(word_t *_hi, word_t *_lo)
{
    word_t m;
    FUN_002a4ab4(0x1d);
    FUN_003a25d4((word_t)0xe000000000000000);
    ((word_t (*)(word_t, word_t))FUN_00027724(0x671df8))(0x677830, 0x671df8);
    thunk_FUN_002acbb8(0);
    FUN_003a25d4((word_t)0xe000000000000000);
    thunk_FUN_002acbb8(0x29, 0xe100000000000000);
    if (_hi) *_hi = (word_t)0x80000000005c18c0;
    if (_lo) *_lo = (word_t)0xd00000000000003a;
    (void)m;
    return (word_t)0xd00000000000003a;
}

/* FUN_0009e508 @ 0x0009e508   (est. sk_init_caps_bitmap_wrap)
 * Ghidra: void FUN_0009e508(void)
 * Wrapper that invokes FUN_0009e440() (capability bitmap init) and returns.
 * Confidence: low
 * Notes: thin forwarding stub. */
void FUN_0009e508(void)
{
    FUN_0009e440(0, 0);
}

/* FUN_0009e52c @ 0x0009e52c   (est. sk_caps_read_self_word_wrap)
 * Ghidra: void FUN_0009e52c(void)
 * Wrapper that forwards to FUN_0009e2e8() (self word read).
 * Confidence: low
 * Notes: thin forwarding stub. */
void FUN_0009e52c(word_t *out, word_t *self)
{
    FUN_0009e2e8(out, self);
}

/* FUN_0009e550 @ 0x0009e550   (est. sk_caps_flush_wrap)
 * Ghidra: undefined8 FUN_0009e550(undefined8 param_1,undefined8 param_2)
 * Saves the allocator/trace state, runs FUN_0009e5a8 (capability flush), and
 * returns the saved state word.
 * Confidence: low
 * Notes: forwarding wrapper. */
word_t FUN_0009e550(word_t a, word_t b, word_t *self, word_t status)
{
    word_t saved = FUN_0036a940(0);
    FUN_0009e5a8(a, b, self, status);
    return saved;
}

/* FUN_0009e5a8 @ 0x0009e5a8   (est. sk_caps_flush)
 * Ghidra: void FUN_0009e5a8(undefined1 *param_1,undefined8 param_2)
 * Initialises the object, enters a guarded section, installs a callback
 * (6), and on success (x21==0) builds a timespan via FUN_0009e98c and, if a
 * pre-allocator flag is clear, emits the "init physAllocator exceptionHand"
 * trace record and invokes FUN_00077070 / deferred FUN_0009e9f4; otherwise it
 * reports the pre-init state and tears down. On failure releases and aborts.
 * Confidence: low
 * Notes: uses thunk_FUN_002acbb8/003a25d4 trace pairs with build-root string. */
void FUN_0009e5a8(word_t obj, word_t param_2, word_t *self, word_t status)
{
    word_t u;
    word_t guard;
    word_t rec[2];

    FUN_0006e7c0((word_t)obj, (word_t)&rec);
    guard = FUN_001003e8(0);
    FUN_0036a940(guard, 0x52, 7);
    u = FUN_000ff728(6, &rec);
    if (status == 0) {
        *(word_t *)((uintptr_t)self + 0x10) = u;
        FUN_0009e98c(param_2, (word_t*)&rec);
        if (*(long *)&rec == 0) {
            FUN_0009e92c((word_t)&rec);
            FUN_0036b270(0);
            FUN_001004b8((word_t)0xd000000000000028,
                         (word_t)0x80000000005c1900,
                         (word_t)0x5c1950, 0x125, 2, (word_t)0x5c1a80, 0x2b, 2);
            FUN_0009e92c(param_2);
        } else {
            FUN_00077070((word_t)&rec, (word_t)&guard);
            FUN_000fce3c((word_t)FUN_0009e9f4, (word_t)&guard, (word_t)0xd00000000000001f,
                         (word_t)0x80000000005c1a90, (word_t)0x5c1950, 0x125, 2,
                         (word_t)0x5c1a80, 0x2b, 2, 0x33);
            FUN_0009e92c(param_2);
            FUN_000026e8((word_t)obj);
            obj = (word_t)&guard;
        }
        FUN_000026e8((word_t)obj);
    } else {
        FUN_0009e92c(param_2);
        FUN_000026e8((word_t)obj);
        FUN_0036b6f4();
    }
}

/* FUN_0009e7c4 @ 0x0009e7c4   (est. sk_caps_dispatch_tail)
 * Ghidra: void FUN_0009e7c4(long param_1,long param_2)
 * Reads the handler id from the message object, resolves the IPC buffer
 * address of a capability, dispatches to the resolved handler, and performs
 * the supervisor-call tail via FUN_0009ea90.
 * Confidence: low
 * Notes: FUN_0009ea60 resolves an IPC buffer/object, FUN_0009ea90 = supervisor. */
void FUN_0009e7c4(word_t msg_obj, word_t cap)
{
    word_t handler = *(word_t *)(*(word_t *)(msg_obj + 0x10) + 0x48);
    word_t buf = *(word_t *)(cap + 0x18);
    word_t v = *(word_t *)(cap + 0x20);
    FUN_0006a4c0((word_t)cap, buf);
    ((word_t (*)(word_t, word_t))FUN_0009ea60(v))(buf, v);
    FUN_0009ea90(handler, buf);
}

/* FUN_0009e83c @ 0x0009e83c   (est. sk_endpoint_new)
 * Ghidra: void FUN_0009e83c(undefined8 *param_1,undefined8 param_2)
 * Allocates an endpoint object at 0x64fd10, enters dispatch (FUN_0009e2f4) and,
 * on success (x21==0), writes the endpoint class/size metadata into the caller
 * record and stores the created object at param_1[0].
 * Confidence: low
 * Notes: object metadata 0x64fd10 / 0x6604e0; calls FUN_0009e2f4. */
void FUN_0009e83c(word_t *out, word_t param_2, word_t *self, word_t status)
{
    word_t obj = FUN_0036a940(0x64fd10, 0x51, 7);
    FUN_0036b270(0);
    FUN_0036b270(param_2);
    obj = FUN_0009e2f4(0, 0, self, status);
    if (status == 0) {
        out[3] = 0x64fd10;
        out[4] = 0x6604e0;
        out[0] = obj;
    }
}

/* FUN_0009e8d0 @ 0x0009e8d0   (est. sk_cap_descriptor_a)
 * Ghidra: undefined1 [16] FUN_0009e8d0(void)
 * Returns the packed capability descriptor {0xd000000000000022,
 * 0x80000000004c1540}.
 * Confidence: low
 * Notes: constant 128-bit capability tag/ptr pair. */
word_t FUN_0009e8d0(word_t *_hi)
{
    if (_hi) *_hi = (word_t)0x80000000004c1540;
    return (word_t)0xd000000000000022;
}

/* FUN_0009e8ec @ 0x0009e8ec   (est. sk_endpoint_new_a)
 * Ghidra: void FUN_0009e8ec(void)
 * Wrapper forwarding to FUN_0009e83c (endpoint creation).
 * Confidence: low */
void FUN_0009e8ec(word_t *out, word_t p, word_t *self, word_t status)
{
    FUN_0009e83c(out, p, self, status);
}

/* FUN_0009e8f0 @ 0x0009e8f0   (est. sk_endpoint_new_b)
 * Ghidra: void FUN_0009e8f0(void)
 * Wrapper forwarding to FUN_0009e83c (endpoint creation).
 * Confidence: low */
void FUN_0009e8f0(word_t *out, word_t p, word_t *self, word_t status)
{
    FUN_0009e83c(out, p, self, status);
}

/* FUN_0009e904 @ 0x0009e904   (est. sk_cap_descriptor_tag_a)
 * Ghidra: undefined8 FUN_0009e904(void)
 * Returns the tag word of the constant capability descriptor (0xd000...22).
 * Confidence: low */
word_t FUN_0009e904(void)
{
    FUN_0009e8d0(0);
    return (word_t)0xd000000000000022;
}

/* FUN_0009e908 @ 0x0009e908   (est. sk_cap_descriptor_tag_b)
 * Ghidra: undefined8 FUN_0009e908(void)
 * Returns the tag word of the constant capability descriptor (0xd000...22).
 * Confidence: low */
word_t FUN_0009e908(void)
{
    FUN_0009e8d0(0);
    return (word_t)0xd000000000000022;
}

/* FUN_0009e92c @ 0x0009e92c   (est. sk_msg_dispose)
 * Ghidra: undefined8 FUN_0009e92c(undefined8 param_1)
 * Looks up the message type metadata and invokes the type's +8 dispose method
 * on the message, returning the message unchanged.
 * Confidence: low
 * Notes: metadata pair 0x64c050/0x4c1550; method slot (hdr-8)+8. */
word_t FUN_0009e92c(word_t msg)
{
    word_t hdr = FUN_00002534((word_t)0x64c050, (word_t)0x4c1550);
    (*(word_t (**)(word_t, word_t))((*(word_t *)(hdr + -8)) + 8))(msg, hdr);
    return msg;
}

/* FUN_0009e98c @ 0x0009e98c   (est. sk_msg_build)
 * Ghidra: undefined8 FUN_0009e98c(undefined8 param_1,undefined8 param_2)
 * Looks up the message type metadata and invokes the type's +0x10 build
 * method (param_2, param_1, hdr), returning param_2.
 * Confidence: low
 * Notes: metadata pair 0x64c050/0x4c1550; method slot (hdr-8)+0x10. */
word_t FUN_0009e98c(word_t msg, word_t *extra)
{
    word_t hdr = FUN_00002534((word_t)0x64c050, (word_t)0x4c1550);
    (*(word_t (**)(word_t, word_t, word_t))((*(word_t *)(hdr + -8)) + 0x10))
        ((word_t)extra, msg, hdr);
    return (word_t)extra;
}

/* FUN_0009e9f4 @ 0x0009e9f4   (est. sk_caps_deferred_dispatch)
 * Ghidra: void FUN_0009e9f4(void)
 * Deferred handler: forwards (self+0x10, self+0x18) to FUN_0009e7c4 (dispatch
 * tail). x20 = self.
 * Confidence: low */
void FUN_0009e9f4(word_t *self)
{
    FUN_0009e7c4(*(word_t *)((uintptr_t)self + 0x10),
                 *(word_t *)((uintptr_t)self + 0x18));
}

/* FUN_0009e9f8 @ 0x0009e9f8   (est. sk_caps_deferred_dispatch_b)
 * Ghidra: void FUN_0009e9f8(void)
 * Identical deferred handler forwarding to FUN_0009e7c4.
 * Confidence: low */
void FUN_0009e9f8(word_t *self)
{
    FUN_0009e7c4(*(word_t *)((uintptr_t)self + 0x10),
                 *(word_t *)((uintptr_t)self + 0x18));
}

/* FUN_0009ea60 @ 0x0009ea60   (est. sk_ipcbuf_resolve)
 * Ghidra: long FUN_0009ea60(ulong param_1)
 * Resolves an IPC-buffer descriptor to its target address: if bit0 set, follows
 * the pointer at (desc & ~1); returns base+4 plus the signed offset stored at
 * base+4 (a relocatable image/segment reference).
 * Confidence: medium
 * Notes: classic seL4 object-image relocation resolution. */
long FUN_0009ea60(word_t desc)
{
    word_t base;
    if ((desc & 1) != 0)
        base = *(word_t *)(desc & (word_t)~1ull);
    else
        base = desc;
    return (long)(base + 4) + (long)*(int *)(base + 4);
}

/* FUN_0009ea90 @ 0x0009ea90   (est. sk_supervisor_call)
 * Ghidra: void FUN_0009ea90(undefined8 param_1,undefined8 param_2)
 * Writes param_2 into the read-only thread id register (TPIDRRO_EL0), issues
 * supervisor call 0 (secure-monitor boundary), then re-writes the value. The
 * TPIDRRO handshake carries the call argument to the monitor.
 * Confidence: medium
 * Notes: CallSupervisor(0); TPIDRRO_EL0 written before and after. */
void FUN_0009ea90(word_t param_1, word_t param_2)
{
    word_t *tpidrro = (word_t *)0x0;
    (void)param_1;
    (void)tpidrro;
    /* TPIDRRO_EL0 write of param_2, supervisor call, rewrite (as decompiled). */
    CallSupervisor(0);
}

/* FUN_0009eab4 @ 0x0009eab4   (est. sk_caps_read_triplet)
 * Ghidra: void FUN_0009eab4(undefined8 *param_1)
 * Reads a 3-field (addr, word16, word8) triplet out of self+0x20 and the
 * message object at +0x10 into the caller record.
 * Confidence: low
 * Notes: x20 = self. */
void FUN_0009eab4(word_t *out, word_t *self)
{
    out[0] = *(word_t *)((uintptr_t)self + 0x20);
    out[1] = *(word_t *)(*(word_t *)((uintptr_t)self + 0x10) + 0x18);
    *(word_t *)((uintptr_t)out + 0x10) =
        (word_t)*(uint16_t *)(*(word_t *)((uintptr_t)self + 0x10) + 0x20);
}

/* FUN_0009ead0 @ 0x0009ead0   (est. sk_caps_dispatch_recv1)
 * Ghidra: void FUN_0009ead0(undefined8 param_1,long *param_2)
 * Same shape as FUN_0009e2f4 but receives with argument count 1: stores the
 * object into self+0x10, calls method +0x1b8 with 1 argument, and copies the
 * 9-word record into self on success; on failure releases and aborts.
 * Confidence: low */
word_t FUN_0009ead0(word_t msg_obj, long *target, word_t *self, word_t status)
{
    word_t rec[9];

    *(word_t *)((uintptr_t)self + 0x10) = msg_obj;
    ((word_t (*)(word_t *, word_t, word_t, word_t, word_t, word_t))
        *(word_t *)(*(word_t *)target + 0x1b8))((word_t *)&rec[0], 1, 0, 0, 0, 0);
    if (status == 0) {
        *(word_t *)((uintptr_t)self + 0x18) = rec[0];
        *(word_t *)((uintptr_t)self + 0x20) = rec[1];
        *(word_t *)((uintptr_t)self + 0x28) = rec[2];
        *(word_t *)((uintptr_t)self + 0x30) = rec[3];
        *(word_t *)((uintptr_t)self + 0x38) = rec[4];
        *(word_t *)((uintptr_t)self + 0x40) = rec[5];
        *(word_t *)((uintptr_t)self + 0x48) = rec[6];
        FUN_0036b270(*(word_t *)(*(word_t *)((uintptr_t)self + 0x10) + 0x10));
        FUN_000fdb98((word_t)&rec[0]);
        FUN_0036b118(*(word_t *)(*(word_t *)((uintptr_t)self + 0x10) + 0x10));
        FUN_0036b118(msg_obj);
        FUN_0036b118((word_t)target);
    } else {
        FUN_0036b118(msg_obj);
        FUN_0036b118((word_t)target);
        FUN_0036b118(*(word_t *)((uintptr_t)self + 0x10));
        FUN_0036b6f4();
    }
    return 0;
}

/* FUN_0009ec1c @ 0x0009ec1c   (est. sk_caps_read_triplet_wrap)
 * Ghidra: void FUN_0009ec1c(void)
 * Wrapper forwarding to FUN_0009eab4 (triplet read).
 * Confidence: low */
void FUN_0009ec1c(word_t *out, word_t *self)
{
    FUN_0009eab4(out, self);
}

/* FUN_0009ec40 @ 0x0009ec40   (est. sk_endpoint_bind_wrap)
 * Ghidra: undefined8 FUN_0009ec40(undefined8 param_1,(word_t _a, ...)
 * Saves allocator state, runs FUN_0009ecb0 (endpoint bind), returns saved state.
 * Confidence: low */
word_t FUN_0009ec40(word_t a, word_t b, word_t c, word_t d, word_t *self, word_t status)
{
    word_t saved = FUN_0036a940(0);
    FUN_0009ecb0(a, b, c, d, self, status);
    return saved;
}

/* FUN_0009ecb0 @ 0x0009ecb0   (est. sk_endpoint_bind)
 * Ghidra: void FUN_0009ecb0(undefined8 param_1,undefined8 param_2,undefined2 param_3,(word_t _a, ...)
 * Initialises the object, enters a guarded section, installs an 8-count
 * callback, and on success (x21==0) stores the created endpoint object at
 * self+0x10, binds param_2/param_3 into self+0x18/0x20, and emits an exception
 * trace record; on failure releases and aborts.
 * Confidence: low
 * Notes: build-root string 0x5c1ad0. */
void FUN_0009ecb0(word_t obj, word_t param_2, uint16_t param_3, word_t param_4,
                  word_t *self, word_t status)
{
    word_t u;
    word_t l;
    word_t guard;
    word_t rec[2];

    FUN_0006e7c0((word_t)obj, (word_t)&rec);
    u = FUN_001003e8(0);
    FUN_0036a940(u, 0x52, 7);
    l = FUN_000ff728(8, &rec);
    if (status == 0) {
        *(word_t *)((uintptr_t)self + 0x10) = l;
        FUN_0009eef0(*(word_t *)(l + 0x48), param_4);
        guard = FUN_00151974();
        FUN_00151a6c((word_t)&guard, 0, (word_t)0x5c1ad0, 0x125, 2, 0x2b,
                     (word_t)0, (word_t)0);
        FUN_000026e8((word_t)obj);
        *(word_t *)((uintptr_t)self + 0x18) = param_2;
        *(word_t *)((uintptr_t)self + 0x20) = param_3;
    } else {
        FUN_000026e8((word_t)obj);
        FUN_0036b6f4();
    }
}

/* FUN_0009edd4 @ 0x0009edd4   (est. sk_notification_new)
 * Ghidra: void FUN_0009edd4(undefined8 *param_1,undefined8 param_2)
 * Allocates a notification object at 0x64fde8, runs dispatch (FUN_0009ead0) and
 * on success stores the created object and metadata into the caller record.
 * Confidence: low
 * Notes: object metadata 0x64fde8 / 0x660558. */
void FUN_0009edd4(word_t *out, word_t param_2, word_t *self, word_t status)
{
    word_t obj = FUN_0036a940(0x64fde8, 0x51, 7);
    FUN_0036b270(0);
    FUN_0036b270(param_2);
    obj = FUN_0009ead0(0, 0, self, status);
    if (status == 0) {
        out[3] = 0x64fde8;
        out[4] = 0x660558;
        out[0] = obj;
    }
}

/* FUN_0009ee68 @ 0x0009ee68   (est. sk_notif_descriptor)
 * Ghidra: undefined1 [16] FUN_0009ee68(void)
 * Returns packed notification descriptor {0xd000000000000022,
 * 0x80000000004c1610}.
 * Confidence: low */
word_t FUN_0009ee68(word_t *_hi)
{
    if (_hi) *_hi = (word_t)0x80000000004c1610;
    return (word_t)0xd000000000000022;
}

/* FUN_0009ee84 @ 0x0009ee84   (est. sk_notif_release)
 * Ghidra: void FUN_0009ee84(void)
 * Releases the notification object at self+0x10 and runs finalize (0x(word_t _a, ...).
 * x20 = self.
 * Confidence: low */
void FUN_0009ee84(word_t *self)
{
    FUN_0036b118(*(word_t *)((uintptr_t)self + 0x10));
    FUN_0036b6ac(0);
}

/* FUN_0009ee88 @ 0x0009ee88   (est. sk_notif_release_b)
 * Ghidra: void FUN_0009ee88(void)
 * Releases the notification object at self+0x10 and finalizes.
 * Confidence: low */
void FUN_0009ee88(word_t *self)
{
    FUN_0036b118(*(word_t *)((uintptr_t)self + 0x10));
    FUN_0036b6ac(0);
}

/* FUN_0009eeb0 @ 0x0009eeb0   (est. sk_notification_new_a)
 * Ghidra: void FUN_0009eeb0(void)
 * Wrapper forwarding to FUN_0009edd4.
 * Confidence: low */
void FUN_0009eeb0(word_t *out, word_t p, word_t *self, word_t status)
{
    FUN_0009edd4(out, p, self, status);
}

/* FUN_0009eeb4 @ 0x0009eeb4   (est. sk_notification_new_b)
 * Ghidra: void FUN_0009eeb4(void)
 * Wrapper forwarding to FUN_0009edd4.
 * Confidence: low */
void FUN_0009eeb4(word_t *out, word_t p, word_t *self, word_t status)
{
    FUN_0009edd4(out, p, self, status);
}

/* FUN_0009eec8 @ 0x0009eec8   (est. sk_notif_descriptor_tag_a)
 * Ghidra: undefined8 FUN_0009eec8(void)
 * Returns the tag word of the notification descriptor (0xd0...22).
 * Confidence: low */
word_t FUN_0009eec8(void)
{
    FUN_0009ee68(0);
    return (word_t)0xd000000000000022;
}

/* FUN_0009eecc @ 0x0009eecc   (est. sk_notif_descriptor_tag_b)
 * Ghidra: undefined8 FUN_0009eecc(void)
 * Returns the tag word of the notification descriptor (0xd0...22).
 * Confidence: low */
word_t FUN_0009eecc(void)
{
    FUN_0009ee68(0);
    return (word_t)0xd000000000000022;
}

/* FUN_0009eef0 @ 0x0009eef0   (est. sk_supervisor_call_b)
 * Ghidra: void FUN_0009eef0(undefined8 param_1,undefined8 param_2)
 * Same TPIDRRO_EL0 handshake supervisor call as FUN_0009ea90 (CallSupervisor 0).
 * Confidence: medium */
void FUN_0009eef0(word_t param_1, word_t param_2)
{
    (void)param_1; (void)param_2;
    CallSupervisor(0);
}

/* FUN_0009ef4c @ 0x0009ef4c   (est. sk_trace_desc)
 * Ghidra: undefined1 [16] FUN_0009ef4c(void)
 * Returns the zero-extended descriptor word 0x64fd78.
 * Confidence: low */
word_t FUN_0009ef4c(word_t *_hi)
{
    if (_hi) *_hi = 0;
    return (word_t)0x64fd78;
}

/* FUN_0009ef5c @ 0x0009ef5c   (est. sk_trace_root_alloc)
 * Ghidra: void FUN_0009ef5c(void)
 * Allocates the trace-root object (metadata 0x64fe58, zone 0x28), runs
 * FUN_0009f7d4 (root-trace init), and stashes the object in global 0x6ad9c8.
 * Confidence: low
 * Notes: writes _DAT_006ad9c8. */
void FUN_0009ef5c(word_t *self)
{
    word_t obj = FUN_0036a940(FUN_0064fe58, 0x28, 7);
    FUN_0009f7d4(self);
    _DAT_006ad9c8 = obj;
}

/* FUN_0009ef9c @ 0x0009ef9c   (est. sk_trace_root_alloc_wrap)
 * Ghidra: undefined8 FUN_0009ef9c(void)
 * Saves allocator state, runs FUN_0009f7d4 (root-trace init), returns saved.
 * Confidence: low */
word_t FUN_0009ef9c(word_t *self)
{
    word_t saved = FUN_0036a940(0);
    FUN_0009f7d4(self);
    return saved;
}

/* FUN_0009efd4 @ 0x0009efd4   (est. sk_trace_root_get)
 * Ghidra: undefined1 * FUN_0009efd4(void)
 * Ensures the trace root exists (FUN_000a021c); if not yet initialised, runs
 * FUN_000a01e8 + FUN_0039a128 (boot hook); returns &DAT_006ad9c8.
 * Confidence: low */
void *FUN_0009efd4(void)
{
    FUN_000a021c();
    FUN_000a01e8(0);
    FUN_0039a128();
    return (void*)&_DAT_006ad9c8;
}

/* FUN_0009f00c @ 0x0009f00c   (est. sk_trace_root_get_hold)
 * Ghidra: void FUN_0009f00c(void)
 * Ensures the trace root, snapshots the root object (FUN_00002828) into a local
 * record, and retains it via FUN_0036b270.
 * Confidence: low */
void FUN_0009f00c(void)
{
    word_t rec[3];
    FUN_000a021c();
    FUN_000a01e8(0);
    FUN_0039a128();
    FUN_00002828((word_t)&_DAT_006ad9c8, rec);
    FUN_0036b270(_DAT_006ad9c8);
}

/* FUN_0009f05c @ 0x0009f05c   (est. sk_trace_root_set)
 * Ghidra: void FUN_0009f05c(undefined8 param_1)
 * Replaces the global trace root: snapshots it, sets the new value (attribute
 * kind 1), releases the old root.
 * Confidence: low */
void FUN_0009f05c(word_t new_root)
{
    word_t rec[3];
    word_t old;
    FUN_000a021c();
    FUN_000a01e8(0);
    FUN_0039a128();
    FUN_0036a1a0((word_t)&_DAT_006ad9c8, rec, 1, 0);
    old = _DAT_006ad9c8;
    _DAT_006ad9c8 = new_root;
    FUN_0036b118(old);
}

/* FUN_0009f0bc @ 0x0009f0bc   (est. sk_trace_root_bind)
 * Ghidra: undefined1 [16] FUN_0009f0bc(undefined8 param_1)
 * Binds the trace root to attribute kind 0x21 and returns the pair
 * {0x6f910, &DAT_006ad9c8}.
 * Confidence: low */
word_t FUN_0009f0bc(word_t param_1, word_t *_hi)
{
    FUN_000a021c();
    FUN_000a01e8(0);
    FUN_0039a128();
    FUN_0036a1a0((word_t)&_DAT_006ad9c8, param_1, 0x21, 0);
    if (_hi) *_hi = (word_t)&_DAT_006ad9c8;
    return (word_t)0x6f910;
}

/* FUN_0009f124 @ 0x0009f124   (est. sk_trace_root_flag_get)
 * Ghidra: undefined1 FUN_0009f124(void)
 * Snapshots attribute kind at self+0x10 and returns its low byte.
 * Confidence: low */
word_t FUN_0009f124(word_t *self)
{
    word_t rec[3];
    FUN_00002828((word_t)((word_t*)self + 0x10), rec);
    return *(word_t *)((uintptr_t)self + 0x10);
}

/* FUN_0009f150 @ 0x0009f150   (est. sk_trace_root_flag_set)
 * Ghidra: void FUN_0009f150(undefined1 param_1)
 * Sets the attribute at self+0x10 (kind 1) to the given byte.
 * Confidence: low */
void FUN_0009f150(word_t val, word_t *self)
{
    word_t rec[3];
    FUN_0036a1a0((word_t)((word_t*)self + 0x10), rec, 1, 0);
    *(word_t *)((uintptr_t)self + 0x10) = val;
}

/* FUN_0009f190 @ 0x0009f190   (est. sk_trace_snapshot16)
 * Ghidra: undefined1 [16] FUN_0009f190(void)
 * Copies the 16-byte record at self+8 and retains the object at self+0x10;
 * returns the record.
 * Confidence: low */
word_t FUN_0009f190(word_t *_hi, word_t *self)
{
    word_t rec[2];
    rec[0] = *(word_t *)((uintptr_t)self + 8);
    rec[1] = *(word_t *)((uintptr_t)self + 0x10);
    thunk_FUN_0036b270(*(word_t *)((uintptr_t)self + 0x10));
    if (_hi) *_hi = rec[1];
    return rec[0];
}

/* FUN_0009f1c0 @ 0x0009f1c0   (est. sk_trace_method_dispatch)
 * Ghidra: void FUN_0009f1c0(void)
 * Invokes method slot +0xb0 on the object at self+0x20 (vtable dispatch).
 * Confidence: low */
void FUN_0009f1c0(word_t *self)
{
    word_t obj = *(word_t *)((uintptr_t)self + 0x20);
    (*(void (**)(void))((*(word_t *)obj) + 0xb0))();
}

/* FUN_0009f200 @ 0x0009f200   (est. sk_trace_root_dump)
 * Ghidra: void FUN_0009f200(long param_1)
 * Recursively dumps the trace-root's nested ring of timespan records to the
 * trace log. Emits timestamped strings ("bump smaps"/"scoll a"/"free"/"timit",
 * decoded from the byte-swapped immediates) for each of the 5 packed fields at
 * self+0x20..0x40, then appends an "SZ"/"FFO" descriptor, and recurses over the
 * child spans stored in the per-node array at +0x50. Overflow/underflow of the
 * recursion count traps via SoftwareBreakpoint(1).
 * Confidence: low
 * Notes: heavy trace/format emission; uses thunk_FUN_002acbb8 + FUN_003a25d4. */
void FUN_0009f200(long depth, word_t *self)
{
    word_t span = *(word_t *)((uintptr_t)self + 0x20);
    word_t auVar9[2];
    word_t rec[2];
    word_t lVar4, uVar3;
    word_t *node;
    long count;

    auVar9[0] = FUN_001ed960(0x2020, (word_t)0xe200000000000000);
    uVar3 = FUN_00002534((word_t)0x64c040, (word_t)0x4bbf40);
    lVar4 = FUN_0036a9a0(uVar3, (word_t*)&rec);
    *(word_t *)(lVar4 + 0x18) = *(word_t *)0x4baeb8;
    *(word_t *)(lVar4 + 0x10) = *(word_t *)0x4baeb0;
    thunk_FUN_002acbb8(*(word_t *)((uintptr_t)self + 0x10),
                       *(word_t *)((uintptr_t)self + 0x18));
    thunk_FUN_002acbb8(0x203a, (word_t)0xe200000000000000);
    /* span / 1e6 (us) formatting + "bump smaps" string emission */
    ((word_t (*)(word_t, word_t))FUN_00027724(0x671848))(0x677790, 0x671848);
    thunk_FUN_002acbb8(0);
    thunk_FUN_002acbb8(0x2f2073706d756220, (word_t)0xe900000000000020);
    FUN_003a25d4(*(word_t *)((uintptr_t)self + 0x30));
    thunk_FUN_002acbb8(0x2073636f6c6c6120, (word_t)0xea0000000000202f);
    FUN_003a25d4(*(word_t *)((uintptr_t)self + 0x38));
    thunk_FUN_002acbb8(0x2f20736565726620, (word_t)0xe900000000000020);
    FUN_003a25d4(*(word_t *)((uintptr_t)self + 0x40));
    ((word_t (*)(word_t, word_t))FUN_00027724(0x6720e0))(0x677880, 0x6720e0);
    thunk_FUN_002acbb8(0x73656d697420, (word_t)0xe600000000000000);
    FUN_003a25d4(*(word_t *)((uintptr_t)self + 0x28));

    *(word_t *)(lVar4 + 0x38) = 0x6753a0;
    *(word_t *)(lVar4 + 0x20) = auVar9[0];
    FUN_0026b434(lVar4, 0x20, (word_t)0xe100000000000000, 10,
                 (word_t)0xe100000000000000);
    FUN_0036b588(lVar4);
    uVar3 = FUN_00002688();
    FUN_0036b6ac(uVar3, 0x20, 7);
    FUN_0036a1a0((word_t)((word_t*)self + 0x50), &rec, 0, 0);

    node = *(word_t **)((uintptr_t)self + 0x50);
    count = *(long *)((uintptr_t)node + 0x10);
    if (count != 0) {
        word_t off;
        if (depth + 1 < 0) return;          /* overflow trap path */
        FUN_0036b270((word_t)node);
        for (off = 0x30; count != 0; off += 0x18, count--) {
            FUN_0036b270(*(word_t *)((uintptr_t)node + off));
            FUN_0009f200(depth + 1, self);
            FUN_0036b118(*(word_t *)((uintptr_t)node + off));
        }
        FUN_0036b118((word_t)node);
    }
}

/* FUN_0009f5cc @ 0x0009f5cc   (est. sk_trace_record_begin)
 * Ghidra: void FUN_0009f5cc(void)
 * Selects a trace record for the current span: if the "spans-enabled" and
 * "sweep" flags in self+0x10/0x18 are set appropriately, forwards to
 * FUN_0009f6cc (record alloc); otherwise writes the record into the buffer at
 * 0x67b148 via FUN_002a4468. This is the TimeTrace span-begin fast path.
 * Confidence: medium
 * Notes: bit tests at (u>>0x3c&1),(u>>0x3d&1). */
word_t FUN_0009f5cc(word_t *self)
{
    word_t span = *(word_t *)((uintptr_t)self + 0x10);
    word_t flags = *(word_t *)((uintptr_t)self + 0x18);
    word_t rec[2];

    if (((flags >> 0x3c) & 1) == 0) {
        if (((flags >> 0x3d) & 1) != 0) {
            FUN_0009f6cc((word_t)&span, 0, 0, 0);
            return 0;
        }
        if (((span >> 0x3c) & 1) != 0) {
            FUN_0009f6cc(((word_t)(flags & 0xfffffffffffffff)) + 0x20, 0, 0, 0);
            return 0;
        }
    }
    FUN_002a4468((word_t)FUN_000a01c8, (word_t)&rec, span, flags, (word_t)0x67b148);
    return 0;
}

/* FUN_0009f6cc @ 0x0009f6cc   (est. sk_trace_record_alloc)
 * Ghidra: void FUN_0009f6cc(long param_1,(word_t _a, ...)
 * Computes the length of the destination trace buffer (FUN_001ee018 from
 * param_2+0x10/0x18) and, if positive, copies param_1..param_1+len into it via
 * FUN_002cb61c; otherwise traps (SoftwareBreakpoint 1).
 * Confidence: medium
 * Notes: buffer bounds check then copy. */
void FUN_0009f6cc(long dest, long src, word_t param_3, word_t param_4)
{
    long len = FUN_001ee018(*(word_t *)(src + 0x10), *(word_t *)(src + 0x18));
    if (len >= 0) {
        FUN_002cb61c(dest, dest + len, param_3, param_4);
        return;
    }
    /* trap: SoftwareBreakpoint(1, 0x9f728) */
}

/* FUN_0009f728 @ 0x0009f728   (est. sk_trace_ring_teardown)
 * Ghidra: void FUN_0009f728(void)
 * Releases the trace ring: emits the flags, drops the sink object at self+0x50,
 * then walks the linked list at self+0x48 releasing each span and unlinking
 * (FUN_0036b2d0) until the list terminator is reached.
 * Confidence: medium
 * Notes: linked-list walk with release; x20 = self. */
word_t FUN_0009f728(word_t *self)
{
    word_t l;
    FUN_003a25d4(*(word_t *)((uintptr_t)self + 0x18));
    FUN_0036b118(*(word_t *)((uintptr_t)self + 0x50));
    l = *(word_t *)((uintptr_t)self + 0x48);
    *(word_t *)((uintptr_t)self + 0x48) = 0;
    FUN_0036b270(l);
    while (l != 0) {
        word_t next;
        FUN_0036b118(l);
        if (FUN_003a261c(l) == 0) break;
        next = *(word_t *)(l + 0x48);
        FUN_0036b2d0(next, 2);
        FUN_0036b118(l);
        l = next;
    }
    FUN_0036b118(l);
    return 0;
}

/* FUN_0009f7b0 @ 0x0009f7b0   (est. sk_trace_ring_teardown_a)
 * Ghidra: void FUN_0009f7b0(void)
 * Runs FUN_0009f728 then finalizes the ring object (size 0x58).
 * Confidence: low */
void FUN_0009f7b0(word_t *self)
{
    word_t u = FUN_0009f728(self);
    FUN_0036b6ac(u, 0x58, 7);
}

/* FUN_0009f7b4 @ 0x0009f7b4   (est. sk_trace_ring_teardown_b)
 * Ghidra: void FUN_0009f7b4(void)
 * Runs FUN_0009f728 then finalizes the ring object (size 0x58).
 * Confidence: low */
void FUN_0009f7b4(word_t *self)
{
    word_t u = FUN_0009f728(self);
    FUN_0036b6ac(u, 0x58, 7);
}

/* FUN_0009f7d4 @ 0x0009f7d4   (est. sk_trace_root_init)
 * Ghidra: void FUN_0009f7d4(void)
 * Initialises the trace-root object at self: clears the flag at +0x10, allocates
 * a 0x58-byte ring object (FUN_0009f834 descriptor), zeroes its +0x20..0x48
 * counters, seeds +0x50 with the DAT_00657778 node metadata and the "rooT"
 * magic at +0x10, links +0x18/+0x20 to it, and retains it.
 * Confidence: medium
 * Notes: writes magic 0x746f6f72 ("root" byte-swapped) at +0x10. */
void FUN_0009f7d4(word_t *self)
{
    word_t ring;
    *(word_t *)((uintptr_t)self + 0x10) = 0;
    ring = FUN_0036a940(FUN_0009f834(0), 0x58, 7);
    *(word_t *)(ring + 0x28) = 0;
    *(word_t *)(ring + 0x20) = 0;
    *(word_t *)(ring + 0x38) = 0;
    *(word_t *)(ring + 0x30) = 0;
    *(word_t *)(ring + 0x48) = 0;
    *(word_t *)(ring + 0x40) = 0;
    *(word_t *)(ring + 0x50) = (word_t)&_DAT_00657778;
    *(word_t *)(ring + 0x10) = 0x746f6f72;
    *(word_t *)(ring + 0x18) = (word_t)0xe400000000000000;
    *(word_t *)((uintptr_t)self + 0x18) = ring;
    *(word_t *)((uintptr_t)self + 0x20) = ring;
    FUN_0036b270(0);
}

/* FUN_0009f834 @ 0x0009f834   (est. sk_trace_ring_meta)
 * Ghidra: undefined1 [16] FUN_0009f834(void)
 * Returns the ring metadata descriptor word 0x64ff40.
 * Confidence: low */
word_t FUN_0009f834(word_t *_hi)
{
    if (_hi) *_hi = 0;
    return (word_t)0x64ff40;
}

/* FUN_0009f844 @ 0x0009f844   (est. sk_trace_enabled)
 * Ghidra: undefined8 FUN_0009f844(void)
 * Calls method +0x50 on the self object (x20); if the returned flag has bit0
 * set, returns FUN_00118328(1), else 0. Tests whether tracing is enabled.
 * Confidence: medium
 * Notes: vtable method +0x50; result gated by FUN_00118328. */
word_t FUN_0009f844(word_t *self)
{
    word_t r = (*(word_t (**)(void))(*((word_t **)self) + 0x50))();
    if ((r & 1) != 0)
        return FUN_00118328(1);
    return 0;
}

/* FUN_0009f88c @ 0x0009f88c   (est. sk_timespan_begin)
 * Ghidra: void FUN_0009f88c(undefined8 *param_1,long param_2,long param_3)
 * Begins a named timespan: validates that the current thread's span nesting
 * (self+0x20) is not deeper than 0x18, then looks up (param_2,param_3) in the
 * thread's span table; if absent, allocates a new 0x58-byte timespan record,
 * links it, and stores the resulting node at self+0x20. On any inconsistency it
 * emits a "byt e. is " error and panics. Outputs an 8-word result record.
 * Confidence: medium
 * Notes: huge body; string refs "byt e. is " / timespan code; FUN_0009f834 ring
 *   metadata; SoftwareBreakpoint traps on overflow. */
void FUN_0009f88c(word_t *out, word_t id_lo, word_t id_hi, word_t *self)
{
    word_t *tab;
    word_t rec0[3];
    long count, n;
    word_t lVar6;
    word_t thread;

    thread = FUN_00268540(0);
    if (0x18 < *(word_t *)(thread + 0x10)) {
        /* "byt e. is " — nesting overflow error path then panic */
        FUN_001afa84(FUN_000a0208(0), 0xb, 2);
    }
    tab = *(word_t **)((uintptr_t)self + 0x20);
    FUN_00002828((word_t)((word_t*)tab + 0x50), (word_t)&n);
    count = *(long *)(*(word_t *)((uintptr_t)tab + 0x50) + 0x10);
    while (count > 0) {
        word_t *ent = (word_t *)(*(word_t *)((uintptr_t)tab + 0x50) + 0x20 +
                                 (count-1) * 0x18);
        if (ent[2] == id_lo && ent[3] == id_hi) {
            lVar6 = ent[0];
            FUN_0036b2d0(lVar6, 2);
            goto found;
        }
        count--;
    }
    {
        word_t ring = FUN_0036a940(FUN_0009f834(0), 0x58, 7);
        word_t *owner;
        *(word_t *)(ring + 0x28) = 0;
        *(word_t *)(ring + 0x20) = 0;
        *(word_t *)(ring + 0x38) = 0;
        *(word_t *)(ring + 0x30) = 0;
        *(word_t *)(ring + 0x10) = id_lo;
        *(word_t *)(ring + 0x18) = id_hi;
        owner = *(word_t **)((uintptr_t)self + 0x20);
        *(word_t *)(ring + 0x40) = 0;
        *(word_t *)(ring + 0x48) = (word_t)owner;
        *(word_t *)(ring + 0x50) = (word_t)&_DAT_00657778;
        FUN_0036b2d0(ring, 2);
        thunk_FUN_0036b270(id_hi);
        FUN_0036b270((word_t)owner);
        FUN_0036a1a0((word_t)((word_t*)owner + 0x50), (word_t)&rec0, 0x21, 0);
        thunk_FUN_0036b270(id_hi);
        FUN_0036b270((word_t)owner);
        FUN_0007b250(0);
        {
            word_t nodec = *(word_t *)(*(word_t *)((word_t)owner + 0x50) + 0x10);
            FUN_0007b42c(nodec);
            n = *(word_t *)((word_t)owner + 0x50);
            *(word_t *)(n + 0x10) = nodec + 1;
            n = n + nodec * 0x18;
            *(word_t *)(n + 0x20) = id_lo;
            *(word_t *)(n + 0x28) = id_hi;
            *(word_t *)(n + 0x30) = ring;
            *(word_t *)((word_t)owner + 0x50) = n;
        }
        FUN_0036a20c((word_t)&rec0);
        FUN_0036b118((word_t)owner);
        lVar6 = ring;
    }
found:
    {
        word_t old = *(word_t *)((uintptr_t)self + 0x20);
        *(word_t *)((uintptr_t)self + 0x20) = lVar6;
        FUN_0036b270(lVar6);
        FUN_0036b118(old);
    }
    out[0] = FUN_0009f844(self);
    thunk_FUN_0036b270(id_hi);
    out[1] = FUN_0006bb8c();
    out[2] = FUN_0006bb98();
    out[3] = FUN_0006bba4();
    FUN_0036b118(lVar6);
    out[4] = id_lo;
    out[5] = id_hi;
    out[6] = lVar6;
    out[7] = (word_t)self;
    FUN_0036b270(0);
}

/* FUN_0009fbf8 @ 0x0009fbf8   (est. sk_timespan_end)
 * Ghidra: void FUN_0009fbf8(ulong *param_1)
 * Ends a timespan begun by FUN_0009f88c. Validates that the record's span
 * (param_1[3]) is the current span, accumulates elapsed counters (wall,
 * cycles, counters 1-3) into the span, bumps the span depth, and pops to the
 * parent span if one exists; otherwise it reports "Timespan name must be <"
 * or "Ended a span that isn't" and panics.
 * Confidence: medium
 * Notes: perf counters via FUN_0006bb8c/98/a4; overflow traps at 0x9fce8+;
 *   strings 0x5c1c30/0x5c1c50. Noreturn on failure. */
void FUN_0009fbf8(word_t *rec, word_t *self)
{
    word_t span, u2, cur;
    word_t n;

    (void)FUN_0009f844(self);
    span = rec[3];
    if (span == *(word_t *)((uintptr_t)self + 0x20)) {
        n = 0;
        if (rec[0] <= (word_t)FUN_0009f844(self))
            n = (word_t)FUN_0009f844(self) - rec[0];
        *(word_t *)(span + 0x20) += n;      /* span wall time */
        *(word_t *)(span + 0x28) += 1;      /* span depth/count */
        u2 = FUN_0006bb8c() - rec[5];
        *(word_t *)(span + 0x30) += u2;     /* counter 1 */
        u2 = FUN_0006bb98() - rec[6];
        *(word_t *)(span + 0x38) += u2;     /* counter 2 */
        u2 = FUN_0006bba4() - rec[7];
        *(word_t *)(span + 0x40) += u2;     /* counter 3 */
        if (*(word_t *)(span + 0x48) != 0) {
            /* pop to parent span */
            cur = *(word_t *)((uintptr_t)self + 0x20);
            *(word_t *)((uintptr_t)self + 0x20) = *(word_t *)(span + 0x48);
            FUN_0036b270(0);
            FUN_0036b118(cur);
            return;
        }
        FUN_000a0208((word_t)0x5c1c50 + 0x10);   /* "Ended a span that isn't..." */
        FUN_00002818();
    } else {
        FUN_000a0208((word_t)0x5c1c30);          /* "Timespan name must be <..." */
        FUN_00002818();
    }
    FUN_001afa84(0);
}

/* FUN_0009fd6c @ 0x0009fd6c   (est. sk_trace_root_end)
 * Ghidra: void FUN_0009fd6c(void)
 * Ends the root trace: builds a "Timing report" object, and if the trace ring
 * at self+0x18 still matches self+0x20 (empty ring) it dumps the whole root
 * via FUN_0009f200(0); otherwise reports "Ended the root trace" and panics.
 * Confidence: medium
 * Notes: string "Timing report:" 0x6753a0 / 0x7220676e696d6954. */
void FUN_0009fd6c(word_t *self)
{
    word_t lVar2, uVar1;
    word_t rec[8];

    uVar1 = FUN_00002534((word_t)0x64c040, (word_t)0x4bbf40);
    lVar2 = FUN_0036a9a0(uVar1, (word_t*)&rec);
    *(word_t *)(lVar2 + 0x18) = *(word_t *)0x4baeb8;
    *(word_t *)(lVar2 + 0x10) = *(word_t *)0x4baeb0;
    *(word_t *)(lVar2 + 0x38) = 0x6753a0;
    *(word_t *)(lVar2 + 0x20) = 0x7220676e696d6954;
    *(word_t *)(lVar2 + 0x28) = 0xee003a74726f7065;
    FUN_0026b434(lVar2, 0x20, (word_t)0xe100000000000000, 10,
                 (word_t)0xe100000000000000);
    FUN_0036b588(lVar2);
    uVar1 = FUN_00002688();
    FUN_0036b6ac(uVar1, 0x20, 7);
    lVar2 = *(word_t *)((uintptr_t)self + 0x18);
    if (*(word_t *)((uintptr_t)self + 0x20) == lVar2) {
        FUN_0036b270(lVar2);
        FUN_0009f200(0, self);
        FUN_0036b118(lVar2);
        return;
    }
    FUN_000a0208((word_t)0x5c1c80 + 0x10);   /* "Ended the root trace..." */
    FUN_00002818();
    FUN_001afa84(0);
}

/* FUN_0009fe78 @ 0x0009fe78   (est. sk_trace_entries_copy)
 * Ghidra: void FUN_0009fe78(undefined8 *param_1,long param_2)
 * Copies up to (param_2-param_1)/0x20 trace entries from the global trace
 * buffer (FUN_0009ff20) into the caller array, honouring the source's capacity.
 * Confidence: medium
 * Notes: element stride 0x20 (4 words). */
void FUN_0009fe78(word_t *dst, long src_end, word_t *self)
{
    word_t *srcbuf;
    word_t u6, u8, u10, u11;
    long cap, i, j;

    if (dst == 0) dst = 0;
    cap = 0;
    if (dst != 0)
        cap = (long)(src_end - (long)dst) >> 5;
    FUN_0036b270(*(word_t *)((uintptr_t)self + 0x18));
    srcbuf = (word_t*)FUN_0009ff20(0,0,0,0);
    FUN_0036b118(*(word_t *)((uintptr_t)self + 0x18));
    u6 = *(word_t *)((word_t)srcbuf + 0x10);
    for (i = 0, j = 0x20; u6 != (word_t)i; i++) {
        if (*(word_t *)((word_t)srcbuf + 0x10) <= (word_t)i) break; /* bounds */
        if (cap == i) break;
        u8 = *(word_t *)((word_t)srcbuf + j);
        u11 = *(word_t *)((word_t)srcbuf + j + 0x18);
        u10 = *(word_t *)((word_t)srcbuf + j + 0x10);
        dst[i*4+0] = u8;
        dst[i*4+1] = *(word_t *)((word_t)srcbuf + j + 8);
        dst[i*4+2] = u10;
        dst[i*4+3] = u11;
        j += 0x20;
    }
    FUN_0036b118((word_t)srcbuf);
}

/* FUN_0009ff20 @ 0x0009ff20   (est. sk_trace_buffer_get)
 * Ghidra: long FUN_0009ff20(long param_1,(word_t _a, ...)
 * Returns the global trace-entry buffer, merging child span buffers from the
 * per-node arrays. Allocates (or grows, via FUN_000739d8) a 0x40-byte buffer
 * object, then concatenates the entries stored in each child node's +0x50
 * array (stride 0x18) into it.
 * Confidence: medium
 * Notes: recursive merge; capacity double via u>>1 checks; bounds traps. */
word_t FUN_0009ff20(word_t param_1, word_t p2, word_t p3, word_t p4)
{
    word_t uVar3;
    word_t buf;
    word_t *node;
    long count, i;

    uVar3 = FUN_00002534((word_t)0x64e850, (word_t)0x4c06a8);
    buf = FUN_0036a940(uVar3, 0x40);
    *(word_t *)(buf + 0x18) = *(word_t *)0x4baeb8;
    *(word_t *)(buf + 0x10) = *(word_t *)0x4baeb0;
    *(word_t *)(buf + 0x20) = FUN_0009f5cc(0);
    *(word_t *)(buf + 0x30) = 7;
    *(word_t *)(buf + 0x38) = p4;
    FUN_00002828(param_1 + 0x50, (word_t*)&uVar3);
    node = *(word_t **)(param_1 + 0x50);
    count = *(long *)((word_t)node + 0x10);
    if (count != 0) {
        word_t off;
        FUN_0036b270((word_t)node);
        for (off = 0x30; count != 0; off += 0x18, count--) {
            word_t child, cc, added;
            FUN_0036b270(*(word_t *)((word_t)node + off));
            child = FUN_0009ff20(0,0,0,0);
            added = *(word_t *)(child + 0x10);
            {
                word_t cur = *(word_t *)(buf + 0x10);
                word_t need = cur + added;
                word_t cap = *(word_t *)(buf + 0x18) >> 1;
                if (cap < need) {
                    word_t newcap = need;
                    if (cur > need) newcap = cur;
                    buf = FUN_000739d8(1, newcap, 1, buf);
                    cap = *(word_t *)(buf + 0x18) >> 1;
                }
                /* append child entries */
                FUN_00117cc4(buf + cur * 0x20 + 0x20, child + 0x20, added << 5);
                if (added != 0)
                    *(word_t *)(buf + 0x10) = cur + added;
            }
            FUN_0036b118(child);
            FUN_0036b118(*(word_t *)((word_t)node + off));
        }
        FUN_0036b118((word_t)node);
    }
    return buf;
}

/* FUN_000a00c4 @ 0x000a00c4   (est. sk_trace_obj_release)
 * Ghidra: void FUN_000a00c4(void)
 * Releases the two object references held at self+0x18 and self+0x20.
 * Confidence: low */
void FUN_000a00c4(word_t *self)
{
    FUN_0036b118(*(word_t *)((uintptr_t)self + 0x18));
    FUN_0036b118(*(word_t *)((uintptr_t)self + 0x20));
}

/* FUN_000a00ec @ 0x000a00ec   (est. sk_trace_obj_destroy_a)
 * Ghidra: void FUN_000a00ec(void)
 * Releases the trace object's refs then finalizes the object.
 * Confidence: low */
void FUN_000a00ec(word_t *self)
{
    FUN_000a00c4(self);
    FUN_0036b6ac(0);
}

/* FUN_000a00f0 @ 0x000a00f0   (est. sk_trace_obj_destroy_b)
 * Ghidra: void FUN_000a00f0(void)
 * Releases the trace object's refs then finalizes the object.
 * Confidence: low */
void FUN_000a00f0(word_t *self)
{
    FUN_000a00c4(self);
    FUN_0036b6ac(0);
}

/* FUN_000a01c8 @ 0x000a01c8   (est. sk_trace_record_emit)
 * Ghidra: void FUN_000a01c8(undefined8 param_1)
 * Emits a trace record by forwarding (param_1, self+0x10/0x18/0x20) to
 * FUN_0009f6cc.
 * Confidence: low */
void FUN_000a01c8(word_t param_1, word_t *self)
{
    FUN_0009f6cc(param_1, *(word_t *)((uintptr_t)self + 0x10),
                 *(word_t *)((uintptr_t)self + 0x18),
                 *(word_t *)((uintptr_t)self + 0x20));
}

/* FUN_000a01cc @ 0x000a01cc   (est. sk_trace_record_emit_b)
 * Ghidra: void FUN_000a01cc(undefined8 param_1)
 * Emits a trace record via FUN_0009f6cc (duplicate of 0xa01c8).
 * Confidence: low */
void FUN_000a01cc(word_t param_1, word_t *self)
{
    FUN_0009f6cc(param_1, *(word_t *)((uintptr_t)self + 0x10),
                 *(word_t *)((uintptr_t)self + 0x18),
                 *(word_t *)((uintptr_t)self + 0x20));
}

/* FUN_000a01e8 @ 0x000a01e8   (est. sk_trace_boot_hook_pair)
 * Ghidra: undefined1 [16] FUN_000a01e8(void)
 * Returns the boot hook pair {0x64fe38, FUN_0009ef5c} (init fn + arg).
 * Confidence: medium */
word_t FUN_000a01e8(word_t *_hi)
{
    if (_hi) *_hi = (word_t)FUN_0009ef5c;
    return (word_t)0x64fe38;
}

/* FUN_000a0208 @ 0x000a0208   (est. sk_fatal_string)
 * Ghidra: char * FUN_000a0208(void)
 * Returns the address of the "Fatal error" string.
 * Confidence: high
 * Notes: s_Fatal_error_005accd0. */
word_t FUN_000a0208(word_t _a, ...)
{
    return (word_t)0x5accd0;
}

/* FUN_000a021c @ 0x000a021c   (est. sk_trace_present_check)
 * Ghidra: void FUN_000a021c(void)
 * Empty guard/check helper (no-op body as decompiled).
 * Confidence: low */
void FUN_000a021c(void)
{
    return;
}

/* =====================================================================
 * CSpace / capability-table lookup + accessor family (0xa022c-0xa0650).
 * These check whether the caller's CNode (param_2+0x10) is non-empty, locate a
 * slot via the thunked FUN_00072664 cap-table find, and copy/return the slot.
 * On a missing cap they run the no-cap error helpers (FUN_000a6ee4/6e40) and
 * always tail into FUN_0009461c (exception/log flush).
 * ===================================================================== */

/* FUN_000a022c @ 0x000a022c   (est. sk_cap_get_word)
 * Ghidra: undefined8 FUN_000a022c(undefined8 param_1,long param_2)
 * If the CNode at param_2 has a non-empty slot, finds the slot (thunk
 * FUN_00072664); on hit retains and returns the slot's word; else returns 0.
 * Confidence: low */
word_t FUN_000a022c(word_t param_1, word_t cnode)
{
    if (*(word_t *)(cnode + 0x10) != 0) {
        FUN_00072570(0);
        if ((/*flag*/ 0) & 1) {
            FUN_000a6fc8(0);
            return FUN_0036b270(0);
        }
        return 0;
    }
    return 0;
}

/* FUN_000a0278 @ 0x000a0278   (est. sk_cap_get_slot)
 * Ghidra: void FUN_000a0278(undefined8 param_1,long param_2)
 * Finds the cap slot in cnode; on hit retains the slot object at
 * (cnode+0x38)+idx*0x10+8; else runs the no-cap helper; always flushes.
 * Confidence: low */
void FUN_000a0278(word_t param_1, word_t cnode)
{
    word_t r[3];
    if (*(word_t *)(cnode + 0x10) != 0) {
        r[0] = thunk_FUN_00072664(0);
        if ((r[2] & 1) != 0) {
            FUN_0036b270(*(word_t *)(*(word_t *)(cnode + 0x38) +
                                     r[0] * 0x10 + 8));
            goto done;
        }
    }
    FUN_000a6ee4(0);
done:
    FUN_0009461c();
}

/* FUN_000a02cc @ 0x000a02cc   (est. sk_cap_copy16)
 * Ghidra: undefined1 [16] FUN_000a02cc(word_t _a, ...)
 * If the CNode has a slot, resolves it via FUN_0006ae9c; on hit copies the
 * 16-byte slot and retains it, returning the pair {obj, extra}; else returns 0.
 * Confidence: low */
word_t FUN_000a02cc(word_t param_1, word_t param_2, word_t cnode, word_t *_hi)
{
    word_t r[2];
    if (*(word_t *)(cnode + 0x10) == 0) {
        FUN_000a6e40(0);
        if (_hi) *_hi = 0;
        return 0;
    }
    thunk_FUN_0036b270(cnode);
    if ((FUN_0006ae9c(param_1, param_2) & 1) == 0) {
        FUN_000a6e40(0);
        if (_hi) *_hi = 0;
        return 0;
    }
    FUN_000a6fd4(0);
    r[0] = FUN_0036b270(0);
    if (_hi) *_hi = r[1];
    FUN_003a25d4(cnode);
    return r[0];
}

/* FUN_000a0368 @ 0x000a0368   (est. sk_cap_put_slot)
 * Ghidra: void FUN_000a0368(undefined8 param_1,long param_2)
 * If the CNode has a slot and the find succeeds, retains the slot's +8 and
 * +0x18 words; else runs the no-cap helper; flushes.
 * Confidence: low */
void FUN_000a0368(word_t param_1, word_t cnode)
{
    if ((*(word_t *)(cnode + 0x10) == 0) || (thunk_FUN_00072664(0), (0 & 1) == 0)) {
        FUN_000a6ee4(0);
    } else {
        FUN_000a6fd4(0);
        thunk_FUN_0036b270(*(word_t *)((word_t)FUN_0036b270(0) + 8));
        FUN_0036b270(0);
    }
    FUN_0009461c();
}

/* FUN_000a03d8 @ 0x000a03d8   (est. sk_cap_get_word2)
 * Ghidra: undefined8 FUN_000a03d8(undefined8 param_1,long param_2)
 * Like 0xa022c: find slot, on hit return its word via FUN_000a6fc8, else 0.
 * Confidence: low */
word_t FUN_000a03d8(word_t param_1, word_t cnode)
{
    if (*(word_t *)(cnode + 0x10) != 0) {
        thunk_FUN_00072664(0);
        if ((0 & 1) == 0)
            return 0;
        return FUN_000a6fc8(0);
    }
    return 0;
}

/* FUN_000a0420 @ 0x000a0420   (est. sk_cap_get_word3)
 * Ghidra: undefined8 FUN_000a0420(undefined8 param_1,long param_2)
 * Find slot; on hit retain and return the slot word, else 0.
 * Confidence: low */
word_t FUN_000a0420(word_t param_1, word_t cnode)
{
    if (*(word_t *)(cnode + 0x10) != 0) {
        thunk_FUN_00072664(0);
        if ((0 & 1) == 0)
            return 0;
        FUN_000a6fc8(0);
        return FUN_0036b270(0);
    }
    return 0;
}

/* FUN_000a046c @ 0x000a046c   (est. sk_cap_put_word)
 * Ghidra: void FUN_000a046c(undefined8 param_1,long param_2)
 * If the CNode slot is found, writes the slot (FUN_000a6e70) and retains;
 * else runs the no-cap helper; flushes.
 * Confidence: low */
void FUN_000a046c(word_t param_1, word_t cnode)
{
    if (*(word_t *)(cnode + 0x10) != 0) {
        thunk_FUN_00072664(0);
        if ((0 & 1) != 0) {
            FUN_000a6e70(0);
            FUN_0036b270(0);
            FUN_0036b270(cnode);
            goto done;
        }
    }
    FUN_000a6ee4(0);
done:
    FUN_0009461c();
}

/* FUN_000a04bc @ 0x000a04bc   (est. sk_cap_get_record)
 * Ghidra: void FUN_000a04bc(undefined8 *param_1,undefined8 param_2,long param_3)
 * If the CNode slot is found, copies the 0x70-byte record at (cnode+0x38)+idx*0x70
 * into param_1 (via FUN_000a6840); else zeroes the 13-word output record.
 * Confidence: medium */
void FUN_000a04bc(word_t *out, word_t param_2, word_t cnode)
{
    word_t r[3];
    if ((*(word_t *)(cnode + 0x10) != 0) &&
        (r[0] = thunk_FUN_00072664(0), (r[2] & 1) != 0)) {
        FUN_000a6840(*(word_t *)(cnode + 0x38) + r[0] * 0x70, (word_t*)out);
        return;
    }
    /* zero 13 words (104 bytes) */
    for (int i = 0; i < 13; i++) ((word_t*)out)[i] = 0;
}

/* FUN_000a0524 @ 0x000a0524   (est. sk_cap_put_word2)
 * Ghidra: void FUN_000a0524(undefined8 param_1,long param_2)
 * If the CNode slot is found, write slot + retain; else no-cap helper; flush.
 * Confidence: low */
void FUN_000a0524(word_t param_1, word_t cnode)
{
    if (*(word_t *)(cnode + 0x10) != 0) {
        thunk_FUN_00072664(0);
        if ((0 & 1) != 0) {
            FUN_000a6e70(0);
            thunk_FUN_0036b270(cnode);
            goto done;
        }
    }
    FUN_000a6ee4(0);
done:
    FUN_0009461c();
}

/* FUN_000a056c @ 0x000a056c   (est. sk_cap_get_word4)
 * Ghidra: undefined8 FUN_000a056c(undefined8 param_1,long param_2)
 * Find slot; on hit return FUN_000a6fc8(idx, 0), else 0.
 * Confidence: low */
word_t FUN_000a056c(word_t param_1, word_t cnode)
{
    word_t r[3];
    if (*(word_t *)(cnode + 0x10) != 0) {
        r[0] = thunk_FUN_00072664(0);
        if ((r[2] & 1) == 0)
            return 0;
        return FUN_000a6fc8(r[0], 0);
    }
    return 0;
}

/* FUN_000a05c0 @ 0x000a05c0   (est. sk_cap_get_rec6)
 * Ghidra: void FUN_000a05c0(undefined8 *param_1,undefined8 param_2,long param_3)
 * If the CNode slot is found, copies the 6-word + 1-byte record at
 * (cnode+0x38)+idx*0x30 into param_1; else writes zeros.
 * Confidence: low */
void FUN_000a05c0(word_t *out, word_t param_2, word_t cnode)
{
    word_t r[3];
    word_t v0, v1, v2, v3, v4;
    word_t b;

    if ((*(word_t *)(cnode + 0x10) != 0) &&
        (r[0] = thunk_FUN_00072664(0), (r[2] & 1) != 0)) {
        word_t *p = (word_t *)(*(word_t *)(cnode + 0x38) + r[0] * 0x30);
        v0 = p[0]; v1 = p[1]; v2 = p[2]; v3 = p[3]; v4 = p[4];
        b = *(word_t *)((word_t)p + 0x28);
        FUN_0036b270(p[3]);
    } else {
        v0 = v1 = v2 = v3 = v4 = 0; b = 0;
    }
    out[0] = v0; out[1] = v1; out[2] = v2; out[3] = 0; out[4] = v4;
    *(word_t *)((word_t)out + 0x28) = b;
}

/* FUN_000a0650 @ 0x000a0650   (est. sk_cap_get_rec5)
 * Ghidra: void FUN_000a0650(undefined8 *param_1,undefined8 param_2,long param_3)
 * If the CNode slot is found, copies the 5-field record at (cnode+0x38)+idx*0x28
 * into param_1; else writes zeros.
 * Confidence: low */
void FUN_000a0650(word_t *out, word_t param_2, word_t cnode)
{
    word_t r[3];
    word_t v1, v2, v3, v4, v0;

    if ((*(word_t *)(cnode + 0x10) != 0) &&
        (r[0] = thunk_FUN_00072664(0), (r[2] & 1) != 0)) {
        word_t *p = (word_t *)(*(word_t *)(cnode + 0x38) + r[0] * 0x28);
        v1 = p[1];
        v2 = *(word_t *)((word_t)p + 0x10);
        v3 = p[3]; v4 = p[4];
        v0 = FUN_0036b270(*p);
    } else {
        v1 = v0 = 0;
        FUN_000a6e40(0);
        v2 = v3 = v4 = 0;
    }
    out[0] = v0; out[1] = v1; out[2] = v2; out[3] = v3; out[4] = v4;
}

/* FUN_000a06cc @ 0x000a06cc   (est. sk_dart_sync_collect)
 * Ghidra: undefined * FUN_000a06cc(undefined8 param_1)
 * Walks the DART/segment device table and builds a 0x40-byte-per-entry
 * collection (array of {result, span, span2, span3, flags, uuid, pad}).
 * For each device found it queries its +0x70 method, formats a trace record
 * via FUN_000a0c8c, appends the 0x40-byte entry (growing the array), and stops
 * when the iterator is exhausted. Returns the collected array.
 * Confidence: low
 * Notes: big dispatch loop; SUB_dac10230d294a3f1 alloca; FUN_000a6894/68c4/68f4
 *   are device-table iteration helpers; DAT_00657798 node metadata. */
void *FUN_000a06cc(word_t param_1)
{
    word_t *node = _DAT_00657798;
    word_t it;
    word_t rec[3];
    long extra_x8;
    word_t lVar8, lVar14, lVar7, lVar3, lVar4, uVar9;
    word_t *out;
    word_t uVar1, uVar12;
    word_t *puVar13;

    (void)param_1; (void)extra_x8; (void)rec;
    /* Decompiled body iterates an object/segment table via FUN_000a6894..68f4,
     * calling each device's +0x70 accessor, formatting via FUN_000a0c8c, and
     * appending 0x40-byte records to the returned array (node). Structure
     * mirrors the second loop; the alloca/SUB_* register dance is elided. */
    it = FUN_00377bec(0, 0, 0, (word_t)0x611b24, (word_t)0x611b2c);
    for (;;) {
        word_t *dev;
        (*(word_t (**)(word_t *))((word_t)FUN_000a68f4(it)))(rec);
        dev = (word_t*)rec[0];
        if (dev == 0) break;
        (*(word_t (**)(word_t *))(*((word_t**)dev) + 0x70))(rec);
        uVar9 = FUN_000e4078(0);
        uVar9 = FUN_000a0c8c((word_t)FUN_000a6b2c, 0, rec[1], uVar9, 0x674330, rec[2],
                             0x66d208, 0, 0);
        FUN_000026e8((word_t)rec);
        lVar8 = dev[2]; lVar14 = dev[3]; lVar7 = dev[5]; lVar3 = dev[6];
        lVar4 = dev[4];
        thunk_FUN_0036b270(lVar14);
        /* append 0x40-byte entry to node */
        puVar13 = node;
        uVar1 = *(word_t *)((word_t)node + 0x10);
        if (*(word_t *)((word_t)node + 0x18) >> 1 <= uVar1)
            FUN_0006a374(1, uVar1 + 1, 1);
        node = puVar13;
        *(word_t *)((word_t)node + 0x10) = uVar1 + 1;
        *(word_t *)((word_t)node + uVar1 * 0x40 + 0x20) = uVar9;
        *(word_t *)((word_t)node + uVar1 * 0x40 + 0x28) = lVar8;
        *(word_t *)((word_t)node + uVar1 * 0x40 + 0x30) = lVar14;
        *(word_t *)((word_t)node + uVar1 * 0x40 + 0x38) = lVar7;
        *(word_t *)((word_t)node + uVar1 * 0x40 + 0x40) = (char)lVar4;
        FUN_0036b118((word_t)dev);
    }
    return node;
}

/* FUN_000a0c8c @ 0x000a0c8c   (est. sk_stream_for_each)
 * Ghidra: void FUN_000a0c8c(code *param_1,(word_t _a, ...)
 * Generic iterator that walks the container (param_3/param_6) and invokes the
 * callback param_1 (e.g. FUN_000a6b2c / FUN_000a64d8) on each element, writing
 * each element into the sink; on x21!=0 (early stop) it unwinds and returns.
 * Confidence: low
 * Notes: iterator metadata pair 0x611b24/0x611b34/0x611b3c; SUB_* alloca. */
word_t FUN_000a0c8c(word_t cb, word_t param_2, word_t param_3, word_t param_4,
                  word_t param_5, word_t param_6, word_t param_7, word_t param_8,
                  word_t status)
{
    word_t it = FUN_00377824(0, param_6, param_3, (word_t)0x611b24, (word_t)0x611b34);
    word_t it2 = FUN_00377824(0, param_6, param_3, (word_t)0x611b24, (word_t)0x611b3c);
    word_t sink = FUN_00310d80(0, param_4);
    word_t elem[3];
    (void)it2; (void)sink;
    for (;;) {
        word_t r;
        (*(word_t (**)(word_t *))FUN_000a68f4(param_6))(elem);
        if (elem[0] == 0) break;
        (*(word_t (**)(word_t *))(*((word_t**)elem[0]) + 0x70))(elem);
        if (status != 0) break;
        FUN_0006a4c0((word_t)elem, elem[1]);
        r = FUN_000e4078(0);
        ((word_t (*)(word_t, word_t, word_t, word_t, word_t, word_t))cb)
            (elem[1], 0, r, 0x674330, elem[2], 0x66d208);
        FUN_000026e8((word_t)elem);
        FUN_0036b118(elem[0]);
    }
    FUN_0036b118(cb);
    return 0;
}

/* FUN_000a12e0 @ 0x000a12e0   (est. sk_cap_table_enumerate)
 * Ghidra: undefined * FUN_000a12e0(long param_1)
 * Enumerates the capability table described by param_1: for each of the
 * lVar15 = *(param_1+0x10) set capabilities, locates the set bit in the bitmap
 * at param_1+0x40, decodes the 0x40-byte slot via FUN_000a63f0, and appends the
 * {tag,word} pair to the output array (node, DAT_00657778). On inconsistency it
 * traps. Returns the output array.
 * Confidence: medium
 * Notes: bitmap walk with LZCOUNT; slot stride 0x40; output stride 0x10. */
void *FUN_000a12e0(word_t param_1)
{
    word_t count = *(word_t *)(param_1 + 0x10);
    word_t *node = &_DAT_00657778;
    word_t slot[6];
    word_t out[2];
    word_t i;

    if (count != 0) {
        word_t cur = 0;
        FUN_0006a374(0, count, 0);
        for (i = 0; i != count; i++) {
            word_t idx = cur;
            word_t slotp;
            word_t bit, word, mask;
            bit = idx >> 6;
            mask = (word_t)1 << (idx & 0x3f);
            if ((*(word_t *)(param_1 + 0x40 + bit * 8) & mask) == 0) break;
            slotp = *(word_t *)(param_1 + 0x38) + idx * 0x40;
            slot[0] = *(word_t *)(slotp + 0);
            slot[1] = *(word_t *)(slotp + 8);
            slot[2] = *(word_t *)(slotp + 0x10);
            slot[3] = *(word_t *)(slotp + 0x18);
            slot[4] = *(word_t *)(slotp + 0x20);
            slot[5] = *(word_t *)(slotp + 0x28);
            FUN_000a63f0((word_t)slot, (word_t)(word_t*)out);
            FUN_000a2d70((word_t*)&slot[0], &slot[0]);
            FUN_000a6444((word_t)slot);
            /* append {out[0],out[1]} to node */
            {
                word_t u = *(word_t *)((word_t)node + 0x10);
                if (*(word_t *)((word_t)node + 0x18) >> 1 <= u)
                    FUN_0006a374(1, u + 1, 1);
                *(word_t *)((word_t)node + 0x10) = u + 1;
                *(word_t *)((word_t)node + u * 0x10 + 0x20) = out[0];
                *(word_t *)((word_t)node + u * 0x10 + 0x28) = out[1];
            }
            /* advance to next set bit */
            word = *(word_t *)(param_1 + 0x40 + bit * 8) & ~(mask << 1);
            cur = bit * 64 + LZCOUNT_64(word);
        }
        FUN_000d1d54(param_1, cur);
    }
    return node;
}

/* FUN_000a1558 @ 0x000a1558   (est. sk_cap_get16)
 * Ghidra: undefined1 [16] FUN_000a1558(undefined8 param_1,undefined8 param_2)
 * If the CNode at in_x6 has 0 slots -> no-cap error helpers then panic; if
 * exactly 1 -> return {+0x20, +0x28} pair; else -> resolve via FUN_000a6e80/
 * FUN_000a6fb0 then panic.
 * Confidence: low
 * Notes: in_x6 = CNode; noreturn on mismatch. */
word_t FUN_000a1558(word_t param_1, word_t param_2, word_t cnode, word_t *_hi)
{
    word_t v1, v2;
    if (*(word_t *)(cnode + 0x10) == 0) {
        FUN_000a6e20(param_2);
        thunk_FUN_0036b270(0);
        FUN_000a6d08(0);
        thunk_FUN_002acbb8(0);
        FUN_000a6fbc(0);
        FUN_000a6d44(0);
        FUN_000a6e50(0);
    } else {
        v1 = *(word_t *)(cnode + 0x28);
        if (*(word_t *)(cnode + 0x10) == 1) {
            v2 = *(word_t *)(cnode + 0x20);
            thunk_FUN_0036b270(v1);
            if (_hi) *_hi = v1;
            return v2;
        }
        FUN_000a6e80(0);
        v1 = thunk_FUN_0036b270(v1);
        FUN_000a6fb0(v1, (word_t)0x80000000005c1f60);
        thunk_FUN_002acbb8(0);
        FUN_000a6fbc(0);
        FUN_000a6d44(0);
    }
    FUN_001afa84(0);
    return 0;
}

/* FUN_000a1630 @ 0x000a1630   (est. sk_cap_get_rec7)
 * Ghidra: void FUN_000a1630(undefined8 *param_1,(word_t _a, ...)
 * If the CNode at in_x6 has exactly 1 slot, copies the 7-word record
 * (+0x20..+0x50) into param_1; else runs the no-cap/error helpers and panics.
 * Confidence: low */
void FUN_000a1630(word_t *out, word_t param_2, word_t param_3, word_t cnode)
{
    if (*(word_t *)(cnode + 0x10) == 1) {
        out[0] = *(word_t *)(cnode + 0x20);
        out[1] = *(word_t *)(cnode + 0x28);
        out[2] = *(word_t *)(cnode + 0x30);
        out[3] = *(word_t *)(cnode + 0x38);
        out[4] = *(word_t *)(cnode + 0x40);
        out[5] = *(word_t *)(cnode + 0x48);
        *(word_t *)((word_t)out + 0x30) = *(word_t *)(cnode + 0x50);
        return;
    }
    if (*(word_t *)(cnode + 0x10) == 0)
        thunk_FUN_0036b270(param_3), FUN_000a6d08(0);
    else {
        thunk_FUN_0036b270(param_3);
        FUN_000a6fb0(param_2, (word_t)0x80000000005c1f60);
    }
    thunk_FUN_002acbb8(0);
    FUN_000a6d44(0);
    FUN_001afa84(0);
}

/* FUN_000a16ec @ 0x000a16ec   (est. sk_cap_copy_cstr)
 * Ghidra: void FUN_000a16ec(void)
 * If the CNode at in_x6 is empty -> error helpers then panic; else copies the
 * 0x42-byte slot record, and if the count is 1 converts it via FUN_00083a78
 * (string) and returns; otherwise resolves and panics.
 * Confidence: low */
void FUN_000a16ec(word_t *out, word_t *cnode)
{
    word_t r[3];
    word_t l = *(word_t *)(cnode + 0x10);
    r[0] = FUN_000a6e20(0);
    if (l == 0) {
        thunk_FUN_0036b270(r[1]);
        FUN_000a6d08(0);
        thunk_FUN_002acbb8(0);
    } else {
        FUN_00117cc4((word_t)out, (word_t)((word_t*)cnode + 0x20), 0x42);
        if (l == 1) {
            FUN_00117cc4((word_t)(word_t*)&r, (word_t)((word_t*)cnode + 0x20), 0x42);
            FUN_00083a78((word_t)out, (word_t)&r);
            return;
        }
        thunk_FUN_0036b270(r[1]);
        FUN_000a6fb0(FUN_00083a78((word_t)out, (word_t)&r),
                     (word_t)0x80000000005c1f60);
        thunk_FUN_002acbb8(0);
    }
    FUN_000a6d44(0);
    FUN_000a6e50(0);
    FUN_001afa84(0);
}

/* FUN_000a17f4 @ 0x000a17f4   (est. sk_cap_release16) [thunk]
 * Ghidra: void thunk_FUN_000a17f8(word_t _a, ...)
 * Thunk that shares the body of FUN_000a17f8 (capability release helper).
 * Confidence: low */
void FUN_000a17f4(word_t param_1, word_t param_2, word_t cnode)
{
    FUN_000a17f8(param_1, param_2, cnode);
}

/* FUN_000a17f8 @ 0x000a17f8   (est. sk_cap_release16)
 * Ghidra: void FUN_000a17f8(undefined8 param_1,undefined8 param_2)
 * Releases a capability from the CNode at in_x6: empty -> error helpers +
 * panic; one slot -> release the +0x20 word and return; else -> resolve and
 * panic.
 * Confidence: low */
void FUN_000a17f8(word_t param_1, word_t param_2, word_t cnode)
{
    word_t v;
    if (*(word_t *)(cnode + 0x10) == 0) {
        FUN_000a6e20(param_2);
        thunk_FUN_0036b270(0);
        FUN_000a6d08(0);
        thunk_FUN_002acbb8(0);
        FUN_000a6fbc(0);
        FUN_000a6d44(0);
        FUN_000a6e50(0);
    } else {
        v = *(word_t *)(cnode + 0x20);
        if (*(word_t *)(cnode + 0x10) == 1) {
            FUN_0036b270(v);
            return;
        }
        FUN_000a6e80(0);
        v = FUN_0036b270(v);
        FUN_000a6fb0(v, (word_t)0x80000000005c1f60);
        thunk_FUN_002acbb8(0);
        FUN_000a6fbc(0);
        FUN_000a6d44(0);
    }
    FUN_001afa84(0);
}

/* FUN_000a18c4 @ 0x000a18c4   (est. sk_cap_slot_attr)
 * Ghidra: undefined1 FUN_000a18c4(undefined8 param_1)
 * Looks up the capability slot via FUN_000a6f88/FUN_00365b6c; on success
 * returns the byte at slot+0x20 (attribute flag), else 0.
 * Confidence: low */
word_t FUN_000a18c4(word_t param_1)
{
    word_t slot;
    word_t st;
    FUN_000a6f88(0);
    st = FUN_00365b6c((word_t)&slot, 0, param_1, FUN_001404d0(0), 6);
    if (st == 0)
        return 0;
    FUN_0036b118(0);
    return *(word_t *)(slot + 0x20);
}

/* FUN_000a1990 @ 0x000a1990   (est. sk_text_segment_load)
 * Ghidra: long FUN_000a1990(void)
 * Loads the __TEXT segment: initialises the container, and if the container
 * status is not the sentinel, parses the load command; if the flag byte
 * (local_230) is not 1 it locates the __TEXT command (magic 0x545845545f5f),
 * and if the text-segment flag (local_180) is not set reports "Missing text
 * segment" and panics. Returns the text size (local_240 + local_1b0).
 * Confidence: low
 * Notes: __TEXT magic 0x545845545f5f; string 0x5c1d10. */
long FUN_000a1990(word_t status)
{
    word_t a[2];
    word_t local_240, local_1b0;
    char local_230, local_180;
    FUN_0010b6bc((word_t)a);
    if (status == 0) {
        FUN_00117cc4((word_t)a, (word_t)a, 0x145);
        if (FUN_000a1b20((word_t*)a) != 1)
            return 0;
    } else {
        FUN_0036b118(0);
    }
    FUN_0010b560((word_t)a);
    if (local_230 == 1) {
        return 0;
    }
    FUN_0010b824((word_t)a);
    FUN_00106958((word_t)a, (word_t)0x545845545f5f, (word_t)0xe600000000000000);
    FUN_000a1ad4((word_t)a);
    if (local_180 == 1) {
        FUN_00002874((word_t)0x5c1d10);   /* "Missing text segment" */
        FUN_000a6d58(0);
        FUN_0006f768(0);
        FUN_001afa84(0);
    }
    return (long)(local_240 + local_1b0);
}

/* FUN_000a1ad4 @ 0x000a1ad4   (est. sk_seg_activate)
 * Ghidra: undefined8 FUN_000a1ad4(undefined8 param_1)
 * Activates the segment by invoking the stored method at _DAT_910083ffa9417c05
 * and returns param_1 unchanged.
 * Confidence: low
 * Notes: indirect call via global function pointer (relocated). */
word_t FUN_000a1ad4(word_t param_1)
{
    (*(void (**)(void))(*(word_t *)0x910083ffa9417c05))();
    return param_1;
}

/* FUN_000a1b20 @ 0x000a1b20   (est. sk_seg_present)
 * Ghidra: int FUN_000a1b20(int *param_1)
 * If the presence flag byte at param_1[0x51] is nonzero, returns *param_1 + 1
 * (a count + presence sentinel), else 0.
 * Confidence: low */
int FUN_000a1b20(word_t *param_1)
{
    if (*(char *)((word_t)param_1 + 0x144) != 0)
        return (int)param_1[0] + 1;
    return 0;
}

/* FUN_000a1b3c @ 0x000a1b3c   (est. sk_ffo_sz_pair)
 * Ghidra: undefined1 [16] FUN_000a1b3c(void)
 * Returns the {SZ, FFO} descriptor pair for the current segment context.
 * Confidence: low
 * Notes: emits "FFO"/"SZ" trace tags. */
word_t FUN_000a1b3c(word_t *_hi)
{
    word_t lo, hi;
    FUN_000a6ecc(0);
    thunk_FUN_002acbb8(0);
    hi = thunk_FUN_0036b270(0);
    thunk_FUN_002acbb8(0x46464f, (word_t)0xe300000000000000);   /* "FFO" */
    thunk_FUN_0036b270(hi);
    thunk_FUN_002acbb8(0x5a53, (word_t)0xe200000000000000);     /* "SZ" */
    FUN_003a25d4(hi);
    lo = thunk_FUN_0036b270(0);
    if (_hi) *_hi = hi;
    return lo;
}

/* FUN_000a1bd8 @ 0x000a1bd8   (est. sk_seg_build)
 * Ghidra: undefined1 [16] FUN_000a1bd8(word_t _a, ...)
 * Builds a segment by walking the device table (param_1), collecting the
 * __MACHO__DART entries, resolving the __TEXT (0x545845545f5f) or __DATA
 * (0x415441445f5f) segment sizes via FUN_000a2094/5d70/5d40, and returning the
 * {size, offset} pair. On any inconsistency it traps.
 * Confidence: low
 * Notes: magic words __MACHO__DART 0x4f4843414d5f5f, __TEXT, __DATA; device
 *   table iteration via param_1 vtable +0x70/+0x78/+0x88/+0x90. */
word_t FUN_000a1bd8(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                    word_t param_5, word_t param_6, word_t param_7, word_t *_hi)
{
    word_t lVar6, uVar9, uVar8, uVar10, uVar11;
    word_t uVar2, uVar3, uVar4;
    word_t *list;
    long count, i;

    lVar6 = (*(word_t (**)(void))(*((word_t**)param_1) + 0x70))();
    if (lVar6 == 0) {
        lVar6 = (*(word_t (**)(void))(*((word_t**)param_1) + 0x88))();
        count = *(long *)((word_t)FUN_000a6f68(0) + 0x10);
        /* collect DART entries whose +0x78 method returns the DART magic */
        for (i = 0; i != count; i++) {
            word_t *pl = *(word_t **)(lVar6 + i * 8 + 0x20);
            word_t m = (*(word_t (**)(void))(*((word_t**)pl) + 0x78))();
            FUN_0036b270((word_t)pl);
            if (m == (word_t)0x11000529b94c7909) {
                /* record pl in the FFO list (DAT_006ad9c8 context) */
                FUN_001dd77c(0);
                {
                    word_t head = *(word_t *)((word_t)FUN_0036b270(0) + 0x10);
                    FUN_001dd858(head);
                    *(word_t *)((word_t)FUN_0036b270(0) + 0x10) = head + 1;
                    *(word_t *)((word_t)FUN_0036b270(0) + head * 8 + 0x20) = (word_t)pl;
                }
            } else {
                FUN_0036b118((word_t)pl);
            }
        }
        FUN_0036b118(lVar6);
        uVar11 = *(word_t *)((word_t)FUN_0036b270(0) + 0x20);
        FUN_0036b270(uVar11);
        FUN_0036b118(FUN_0036b270(0));
        (*(void (**)(word_t))(*((word_t**)param_1) + 0x78))(uVar11);
    } else {
        FUN_0036b118(0);
    }
    /* resolve segment size via the second table (param_2 vtable +0x90) */
    uVar9 = (*(word_t (**)(void))(*((word_t**)param_2) + 0x90))();
    if (*(word_t *)(uVar9 + 0x10) != 0) {
        if ((FUN_0006ae9c(0,0) & 1) != 0) {
            uVar11 = *(word_t *)(*(word_t *)(uVar9 + 0x38) + 0);
            uVar3 = *(word_t *)(*(word_t *)(uVar9 + 0x38) + 8);
            uVar2 = *(word_t *)(*(word_t *)(uVar9 + 0x38) + 0x10);
            uVar4 = *(word_t *)(*(word_t *)(uVar9 + 0x38) + 0x18);
            FUN_0036b270(uVar11);
            uVar8 = FUN_0013bf20(uVar11, uVar3, uVar2, uVar4);
            FUN_0036b118(uVar11);
            if ((long)uVar8 < 0) return 0;
            if ((param_3 == (word_t)0x545845545f5f &&
                 param_4 == (word_t)(-0x1a00000000000000)) ||
                (FUN_002a0cf8(0x545845545f5f, (word_t)0xe600000000000000,
                              param_3, param_4, 0) & 1) != 0) {
                uVar10 = FUN_000a2094(lVar6, param_3, param_4);
            } else {
                uVar10 = FUN_000a2094(lVar6, (word_t)0x415441445f5f,
                                      (word_t)0xe600000000000000);
            }
            FUN_0036b118(lVar6);
            if (_hi) *_hi = uVar8;
            return uVar10 + (uVar8 - uVar10);
        }
    }
    FUN_003a25d4(uVar9);
    return 0;
}

/* FUN_000a2094 @ 0x000a2094   (est. sk_macho_dart_size)
 * Ghidra: long FUN_000a2094(long *param_1,undefined8 param_2,undefined8 param_3)
 * Looks up the __MACHO__DART (0x4f4843414d5f5f) entry in the device table and
 * returns its resolved size via FUN_0013bf20; else traps.
 * Confidence: low */
long FUN_000a2094(word_t param_1, word_t param_2, word_t param_3)
{
    word_t l;
    word_t r[3];
    word_t v0, v1, v2, v3;
    thunk_FUN_002acbb8(param_2, param_3);
    thunk_FUN_0036b270((word_t)0xe700000000000000);
    thunk_FUN_002acbb8(0x46464f, (word_t)0xe300000000000000);   /* "FFO" */
    FUN_003a25d4((word_t)0xe700000000000000);
    l = (*(word_t (**)(void))(*((word_t**)param_1) + 0x90))();
    if (*(word_t *)(l + 0x10) != 0 &&
        (r[0] = FUN_0006ae9c(0x4f4843414d5f5f, (word_t)0xe700000000000000),
         (r[2] & 1) != 0)) {
        word_t *p = (word_t *)(*(word_t *)(l + 0x38) + r[0] * 0x20);
        v0 = p[0]; v1 = p[1]; v2 = p[2]; v3 = p[3];
        FUN_0036b270(v0);
        l = FUN_0013bf20(v0, v1, v2, v3);
        FUN_0036b118(v0);
        return (long)l;
    }
    FUN_003a25d4((word_t)0xe700000000000000);
    FUN_003a25d4(l);
    return 0;
}

/* FUN_000a221c @ 0x000a221c   (est. sk_macho_sz_size)
 * Ghidra: long FUN_000a221c(long *param_1,undefined8 param_2,undefined8 param_3)
 * Resolves the __MACHO__DART "SZ" entry size in the device table (analogous to
 * 0xa2094 but tagged "SZ"), returning it via FUN_0013bf20; else traps.
 * Confidence: low */
long FUN_000a221c(word_t param_1, word_t param_2, word_t param_3)
{
    word_t l;
    word_t r[3];
    word_t v0, v1, v2, v3;
    thunk_FUN_002acbb8(param_2, param_3);
    thunk_FUN_0036b270((word_t)0xe700000000000000);
    thunk_FUN_002acbb8(0x5a53, (word_t)0xe200000000000000);     /* "SZ" */
    FUN_003a25d4((word_t)0xe700000000000000);
    l = (*(word_t (**)(void))(*((word_t**)param_1) + 0x90))();
    thunk_FUN_0036b270((word_t)0xe700000000000000);
    if (*(word_t *)(l + 0x10) != 0 &&
        (r[0] = FUN_0006ae9c(0x4f4843414d5f5f, (word_t)0xe700000000000000),
         (r[2] & 1) != 0)) {
        word_t *p = (word_t *)(*(word_t *)(l + 0x38) + r[0] * 0x20);
        v0 = p[0]; v1 = p[1]; v2 = p[2]; v3 = p[3];
        FUN_0036b270(v0);
        l = FUN_0013bf20(v0, v1, v2, v3);
        FUN_003a25d4((word_t)0xe700000000000000);
        FUN_0036b118(v0);
        return (long)l;
    }
    FUN_003a25d4(l);
    FUN_003a25d4((word_t)0xe700000000000000);
    return 0;
}

/* FUN_000a240c @ 0x000a240c   (est. sk_bundle_seg_commit)
 * Ghidra: void FUN_000a240c(word_t _a, ...)
 * Commits a compressed bundle segment: computes the segment size from
 * FUN_000a1bd8 and FUN_000a221c, rounds it to 0x4000-page granularity, maps
 * each page via FUN_0006d0b8/FUN_00034f70/FUN_00084824, then builds a paging
 * object via FUN_00106c88/FUN_0022d2f4/FUN_001401c0. On allocation failure it
 * reports "handleSegment bundle comp segCom..." and panics.
 * Confidence: low
 * Notes: string 0x5c20e0; page size 0x4000; page alloc FUN_00034f70. */
void FUN_000a240c(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                  word_t param_5, word_t param_6, word_t param_7, word_t param_8)
{
    word_t u4 = FUN_000a1bd8(param_1, param_2, param_4, param_5, param_6,
                             param_7, param_8, 0);
    word_t u5 = FUN_000a221c(param_2, param_4, param_5);
    word_t seg = FUN_0006cf50(u4);
    word_t state, u7, u1;
    word_t pages, i;
    word_t sink;
    word_t au[2];

    if (seg == 0) {
        FUN_0006f768((word_t)0x5accd0);
        FUN_001afa84(0);
    }
    state = FUN_00092c00(0);
    /* number of 0x4000 pages covering u5 */
    pages = 0;
    {
        word_t covered = 0;
        while (covered < u5) {
            pages++;
            if (covered > (word_t)0xffffffffffffbfff) covered = (word_t)-1;
            else covered += 0x4000;
        }
    }
    sink = FUN_000a6f68(0);
    FUN_00082524(0, pages, 0);
    if (u5 != 0) {
        word_t off = 0;
        for (i = 0; i != pages; i++) {
            word_t end = off + 0x4000;
            if (off > (word_t)0xffffffffffffbfff) end = (word_t)-1;
            u7 = FUN_0006d0b8(u4 + off);
            if (FUN_00034f70() == 0) goto fail;
            FUN_00084824(seg, u7, FUN_00034f70());
            /* append page record to sink */
            {
                word_t u = *(word_t *)(sink + 0x10);
                if (*(word_t *)(sink + 0x18) >> 1 <= u) FUN_000a6f20(0);
                *(word_t *)(sink + 0x10) = u + 1;
                *(word_t *)(sink + u * 8 + 0x20) = FUN_00034f70();
            }
            off = end;
            if (end >= u5) break;
        }
    }
    u7 = *(word_t *)(param_3 + 0x18);
    u1 = *(word_t *)(param_3 + 0x20);
    au[0] = FUN_00106c88(0);
    au[1] = FUN_0022d2f4(au[0], 0x6753a0, 0x66e240, 0x66e0d8);
    state = FUN_001404e0(0);
    state = FUN_0036a940(state, 0x48, 7);
    FUN_001401c0(u7, u1, state, sink, au[0], au[1], state);
    return;
fail:
    FUN_002a4ab4(0x1e);
    FUN_003a25d4((word_t)0xe000000000000000);
    FUN_000a6f74(0);
    FUN_00294bdc((word_t)0x5c20e0, 0x30, 2);
    thunk_FUN_002acbb8(0);
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(0x203a20, (word_t)0xe300000000000000);
    FUN_000a6d70(0);
    FUN_0006f768((word_t)0x5accd0);
    FUN_001afa84(0);
}

/* FUN_000a2820 @ 0x000a2820   (est. sk_cap_table_build_wrap)
 * Ghidra: undefined8 FUN_000a2820(word_t _a, ...)
 * Saves allocator state, runs FUN_000a2888 (capability table build), returns
 * the saved state.
 * Confidence: low */
word_t FUN_000a2820(word_t a, word_t b, word_t c, word_t d, word_t *self)
{
    word_t saved = FUN_0036a940(0);
    FUN_000a2888(a, b, c, d, self);
    return saved;
}

/* FUN_000a2888 @ 0x000a2888   (est. sk_cap_table_build)
 * Ghidra: long FUN_000a2888(long param_1,(word_t _a, ...)
 * Builds a capability table object from the input capability set param_1:
 * copies each 0x50-byte slot record into a staging array, then re-derives the
 * table (FUN_000a2c24), and finally re-encodes the slot records via
 * FUN_000a63f0 into a second table; the completed object (self+0x10..0x38,
 * with flag param_4&1 at +0x28) is returned. Complex bitmap/record shuffling.
 * Confidence: low
 * Notes: slot stride 0x50 for staging and 0x40 for the source; big loops. */
long FUN_000a2888(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                  word_t *self)
{
    word_t count = *(word_t *)(param_1 + 0x10);
    word_t *stage = &_DAT_00657778;
    word_t lVar6, uVar2, uVar3;
    word_t slot[8];
    word_t i;

    if (count != 0) {
        word_t *src = (word_t *)(param_1 + 0x20);
        FUN_00082584(0, count, 0);
        for (i = count; i != 0; i--) {
            /* copy 8-word (0x50-byte) slot */
            slot[0] = src[0]; slot[1] = src[1]; slot[2] = src[2];
            slot[3] = src[3]; slot[4] = src[4]; slot[5] = src[5];
            slot[6] = src[6]; slot[7] = src[7];
            FUN_000a63f0((word_t)slot, (word_t)(word_t*)&stage);
            {
                word_t u = *(word_t *)((word_t)stage + 0x10);
                if (*(word_t *)((word_t)stage + 0x18) >> 1 <= u)
                    FUN_00082584(1, u + 1, 1);
                *(word_t *)((word_t)stage + 0x10) = u + 1;
                *(word_t *)((word_t)stage + u * 0x50 + 0x20) = slot[1];
                *(word_t *)((word_t)stage + u * 0x50 + 0x28) = slot[2];
                *(word_t *)((word_t)stage + u * 0x50 + 0x30) = slot[0];
                *(word_t *)((word_t)stage + u * 0x50 + 0x38) = slot[3];
                *(word_t *)((word_t)stage + u * 0x50 + 0x40) = slot[4];
                *(word_t *)((word_t)stage + u * 0x50 + 0x48) = slot[5];
                *(word_t *)((word_t)stage + u * 0x50 + 0x50) = slot[6];
                *(word_t *)((word_t)stage + u * 0x50 + 0x58) = slot[7];
            }
            src += 8;
        }
    }
    uVar2 = FUN_000a2c24((word_t)stage, (word_t)0x6502b0, (word_t)0x4c1928,
                         (word_t)FUN_000a5da0);
    *(word_t *)((uintptr_t)self + 0x10) = uVar2;
    /* re-encode pass (second loop): decode + encode each slot */
    lVar6 = *(word_t *)(param_1 + 0x10);
    *(word_t *)((uintptr_t)self + 0x18) = (word_t)stage;
    FUN_000a6ddc(0);
    for (i = 0; i != lVar6; i++) {
        word_t rec[2];
        rec[0] = thunk_FUN_0001a448(0, 0);
        if ((FUN_00141e64() & 1) != 0) {
            FUN_003a25d4(rec[0]);
            FUN_000a6444((word_t)slot);
            continue;
        }
        FUN_000a6e14(0);
        if ((FUN_00141d44() & 1) != 0) { FUN_003a25d4(rec[0]); FUN_000a6444((word_t)slot); continue; }
        FUN_000a6e14(0);
        if ((FUN_00141b14() & 1) != 0) { FUN_003a25d4(rec[0]); FUN_000a6444((word_t)slot); continue; }
        FUN_000a6e14(0);
        FUN_003a25d4(rec[0]);
        FUN_000a6444((word_t)slot);
    }
    *(word_t *)((uintptr_t)self + 0x20) = (word_t)stage;
    *(word_t *)((uintptr_t)self + 0x30) = param_2;
    *(word_t *)((uintptr_t)self + 0x38) = param_3;
    *(word_t *)((uintptr_t)self + 0x28) = param_4 & 1;
    FUN_0036b118(param_1);
    return (long)self;
}

/* FUN_000a2bfc @ 0x000a2bfc   (est. sk_cap_list_build)
 * Ghidra: void FUN_000a2bfc(undefined8 param_1)
 * Builds a capability list via FUN_000a2c24 with the FUN_000a6104 mapper.
 * Confidence: low */
void FUN_000a2bfc(word_t param_1)
{
    FUN_000a2c24(param_1, (word_t)0x650288, (word_t)0x4c1900, (word_t)FUN_000a6104);
}

/* FUN_000a2c24 @ 0x000a2c24   (est. sk_array_build)
 * Ghidra: undefined8 * FUN_000a2c24(long param_1,(word_t _a, ...)
 * Allocates an array of lVar2 = *(param_1+0x10) elements (metadata
 * param_2/param_3) and invokes the mapper callback param_4 on each element.
 * Returns the array.
 * Confidence: low
 * Notes: empty count -> DAT_00657798 sentinel. */
word_t FUN_000a2c24(word_t param_1, word_t param_2, word_t param_3, word_t cb)
{
    word_t l;
    word_t arr;
    l = *(word_t *)(param_1 + 0x10);
    if (l == 0)
        arr = (word_t)&_DAT_00657798;
    else
        arr = FUN_001fac04(l, FUN_00002534(param_2, param_3));
    FUN_0036b270(param_1);
    ((word_t (*)(word_t, word_t, word_t *))cb)(FUN_0036b270(param_1), 1, &arr);
    FUN_0036b118(cb);
    return arr;
}

/* FUN_000a2cd8 @ 0x000a2cd8   (est. sk_cap_table_dump)
 * Ghidra: void FUN_000a2cd8(void)
 * Retains the table at self+0x10, enumerates it via FUN_000a12e0, releases,
 * and emits a "MACHO" trace record via FUN_001bc440/FUN_00076fc0, then flushes.
 * Confidence: low */
void FUN_000a2cd8(word_t *self)
{
    word_t u3, u2, u1;
    u3 = *(word_t *)((uintptr_t)self + 0x10);
    thunk_FUN_0036b270(u3);
    u1 = (word_t)FUN_000a12e0(0);
    FUN_003a25d4(u3);
    u3 = FUN_00002534((word_t)0x64e030, (word_t)0x4be900);
    u2 = FUN_00076fc0();
    FUN_001bc440(0, (word_t)0xe000000000000000, u3, u2);
    FUN_0036b118(u1);
    FUN_0009461c();
}

/* FUN_000a2d70 @ 0x000a2d70   (est. sk_macho_dump)
 * Ghidra: void FUN_000a2d70(undefined8 *param_1,long *param_2)
 * Dumps the MACH-O object graph: for each object in the list at (*param_2)+0x10
 * it invokes the object's +0x90 method and emits a "SEG: " trace record, then
 * emits a final "MACHO: " descriptor. Returns via param_1.
 * Confidence: low
 * Notes: DAT_00657788/90/98 global trace entry counters; "SEG:"/"MACHO:". */
void FUN_000a2d70(word_t *param_1, word_t *param_2)
{
    word_t obj = *param_2;
    word_t count;
    word_t i;
    word_t au[2];

    FUN_000e2a34();
    thunk_FUN_002acbb8(0);
    FUN_003a25d4(0);
    thunk_FUN_002acbb8(10, (word_t)0xe100000000000000);
    count = *(word_t *)(obj + 0x10);
    if (count != 0) {
        FUN_0006a374(0, count, 0);
        for (i = 0; i != count; i++) {
            word_t *pl = *(word_t **)(obj + 0x20 + i * 8);
            (*(void (**)(void))(*((word_t**)pl) + 0x90))();
            FUN_0036b270((word_t)pl);
            thunk_FUN_002acbb8(0);
            FUN_003a25d4(0);
            thunk_FUN_002acbb8(10, (word_t)0xe100000000000000);
            FUN_0036b118((word_t)pl);
            /* append "SEG:\n" trace tag to global entry table */
            {
                word_t u2 = _DAT_00657788;
                if (_DAT_00657790 >> 1 <= _DAT_00657788)
                    FUN_0006a374(1, _DAT_00657788 + 1, 1);
                _DAT_00657788 = _DAT_00657788 + 1;
                _DAT_00657798[u2*2] = 0x203a47455309;
                _DAT_006577a0[u2*2] = (word_t)0xe600000000000000;
            }
        }
    }
    au[0] = FUN_00002534((word_t)0x64e030, (word_t)0x4be900);
    au[1] = FUN_00076fc0();
    thunk_FUN_0036b270((word_t)0xe800000000000000);
    thunk_FUN_002acbb8(FUN_001bc440(0, (word_t)0xe000000000000000, au[0], au[1]),
                       (word_t)0);
    FUN_003a25d4((word_t)0xe800000000000000);
    FUN_0036b118((word_t)&_DAT_00657778);
    FUN_003a25d4((word_t)0xe800000000000000);
    thunk_FUN_0036b270((word_t)0xe800000000000000);
    thunk_FUN_002acbb8(10, (word_t)0xe100000000000000);
    FUN_003a25d4((word_t)0xe800000000000000);
    param_1[0] = 0x203a204f4843414d;   /* "MACHO: " */
    param_1[1] = (word_t)0xe800000000000000;
}

/* FUN_000a2fe8 @ 0x000a2fe8   (est. sk_trace_rec_release)
 * Ghidra: void FUN_000a2fe8(void)
 * Emits the trace tag at self+0x10 and releases the objects at self+0x18/0x20.
 * Confidence: low */
void FUN_000a2fe8(word_t *self)
{
    FUN_003a25d4(*(word_t *)((uintptr_t)self + 0x10));
    FUN_0036b118(*(word_t *)((uintptr_t)self + 0x18));
    FUN_0036b118(*(word_t *)((uintptr_t)self + 0x20));
}

/* FUN_000a3018 @ 0x000a3018   (est. sk_trace_rec_destroy_a)
 * Ghidra: void FUN_000a3018(void)
 * Releases trace record refs then finalizes.
 * Confidence: low */
void FUN_000a3018(word_t *self)
{
    FUN_000a2fe8(self);
    FUN_0036b6ac(0);
}

/* FUN_000a301c @ 0x000a301c   (est. sk_trace_rec_destroy_b)
 * Ghidra: void FUN_000a301c(void)
 * Releases trace record refs then finalizes.
 * Confidence: low */
void FUN_000a301c(word_t *self)
{
    FUN_000a2fe8(self);
    FUN_0036b6ac(0);
}

/* FUN_000a3040 @ 0x000a3040   (est. sk_obj_method_dispatch)
 * Ghidra: void FUN_000a3040(void)
 * Invokes vtable method +0x68 on the object at *self (x20).
 * Confidence: low */
void FUN_000a3040(word_t *self)
{
    (*(void (**)(void))((*(word_t *)*((word_t **)self)) + 0x68))();
}

/* FUN_000a30b0 @ 0x000a30b0   (est. sk_feature_flags)
 * Ghidra: uint FUN_000a30b0(uint param_1)
 * Reads three feature-flag registers and ORs them into a result when the
 * corresponding selector flag matches param_1. Returns the combined flag word.
 * Confidence: medium
 * Notes: FUN_00107224/200/1f4/20c and FUN_0013f738/720/72c flag regs. */
uint32_t FUN_000a30b0(uint32_t param_1)
{
    uint32_t res = *(uint32_t *)FUN_00107224();
    char c, c2;
    uint32_t m;
    c = *(char *)FUN_0013f738();
    m = FUN_0001a1c8(c);
    if (c == (char)FUN_0001a1c8(m & param_1))
        res |= *(uint32_t *)FUN_00107200();
    c = *(char *)FUN_0013f720();
    m = FUN_0001a1c8(c);
    if (c == (char)FUN_0001a1c8(m & param_1))
        res |= *(uint32_t *)FUN_001071f4();
    c = *(char *)FUN_0013f72c();
    m = FUN_0001a1c8(c);
    if (c == (char)FUN_0001a1c8(m & param_1))
        res |= *(uint32_t *)FUN_0010720c();
    return res;
}

/* FUN_000a3168 @ 0x000a3168   (est. sk_obj_call70)
 * Ghidra: void FUN_000a3168(undefined8 *param_1,undefined8 *param_2)
 * Invokes vtable method +0x70 on *param_2 with (*param_1, param_1[1]).
 * Confidence: low */
void FUN_000a3168(word_t *a, word_t *b)
{
    (*(void (**)(word_t, word_t))(*((word_t**)b[0]) + 0x70))(a[0], a[1]);
}

/* FUN_000a31b0 @ 0x000a31b0   (est. sk_attr16_get)
 * Ghidra: undefined1 [16] FUN_000a31b0(void)
 * Reads the 16-byte attribute at self+0x18 (FUN_000867a8) and returns it.
 * Confidence: low */
word_t FUN_000a31b0(word_t *_hi, word_t *self)
{
    word_t rec[3];
    FUN_000867a8((word_t)((word_t*)self + 0x18), rec);
    FUN_0036a1a0(0);
    if (_hi) *_hi = *(word_t *)((uintptr_t)self + 0x18 + 8);
    return *(word_t *)((uintptr_t)self + 0x18);
}

/* FUN_000a31e0 @ 0x000a31e0   (est. sk_attr16_set)
 * Ghidra: void FUN_000a31e0(undefined8 param_1,undefined8 param_2)
 * Writes the 16-byte value (param_1,param_2) into the attribute at self+0x18.
 * Confidence: low */
void FUN_000a31e0(word_t param_1, word_t param_2, word_t *self)
{
    FUN_0008e3b0((word_t)((word_t*)self + 0x18));
    *(word_t *)((uintptr_t)self + 0x18) = param_1;
    *(word_t *)((uintptr_t)self + 0x20) = param_2;
}

/* FUN_000a3220 @ 0x000a3220   (est. sk_attr16_bind)
 * Ghidra: undefined1 [16] FUN_000a3220(void)
 * Returns the pair {0x7bf58, &self+0x18} describing the 16-byte attribute.
 * Confidence: low */
word_t FUN_000a3220(word_t *_hi, word_t *self)
{
    FUN_000a6f08(0);
    if (_hi) *_hi = (word_t)((uintptr_t)self + 0x18);
    return (word_t)0x7bf58;
}

/* FUN_000a325c @ 0x000a325c   (est. sk_attr_byte_get)
 * Ghidra: undefined1 FUN_000a325c(void)
 * Reads the byte attribute at self+0x28 and returns it.
 * Confidence: low */
word_t FUN_000a325c(word_t *self)
{
    word_t rec[3];
    FUN_000867a8((word_t)((word_t*)self + 0x28), rec);
    FUN_0036a1a0(0);
    return *(word_t *)((uintptr_t)self + 0x28);
}

/* FUN_000a328c @ 0x000a328c   (est. sk_attr_byte_set)
 * Ghidra: void FUN_000a328c(undefined1 param_1)
 * Writes the byte value into the attribute at self+0x28.
 * Confidence: low */
void FUN_000a328c(word_t val, word_t *self)
{
    FUN_0008e3b0((word_t)((word_t*)self + 0x28));
    *(word_t *)((uintptr_t)self + 0x28) = val;
}

/* FUN_000a32c0 @ 0x000a32c0   (est. sk_attr_byte_bind)
 * Ghidra: undefined1 [16] FUN_000a32c0(undefined8 param_1)
 * Binds the byte attribute (kind 0x21) and returns {0x7bf58, &self+0x28}.
 * Confidence: low */
word_t FUN_000a32c0(word_t param_1, word_t *_hi, word_t *self)
{
    FUN_0036a1a0((word_t)((word_t*)self + 0x28), param_1, 0x21, 0);
    if (_hi) *_hi = (word_t)((uintptr_t)self + 0x28);
    return (word_t)0x7bf58;
}

/* FUN_000a3310 @ 0x000a3310   (est. sk_cap_table_build_ctl)
 * Ghidra: undefined8 FUN_000a3310(void)
 * Builds a capability table for the object at self+0x10: queries vtable +0x68
 * (span) and +0x80 (flag), then calls FUN_000a2888 with the flag. Returns the
 * allocator state.
 * Confidence: low */
word_t FUN_000a3310(word_t *self)
{
    word_t u3 = *(word_t *)((uintptr_t)self + 0x10);
    word_t span[2];
    word_t flag;
    word_t saved;
    FUN_000027e8();
    span[0] = (*(word_t (**)(void))(FUN_0036b270(0) + 0x68))();
    FUN_0036b270(u3);
    FUN_000027e8();
    flag = (*(word_t (**)(void))(FUN_0036b270(0) + 0x80))();
    saved = FUN_0036a940((word_t)0x650090, 0x40, 7);
    FUN_000a2888(u3, span[0], span[1], flag & 1, self);
    return saved;
}

/* FUN_000a33c0 @ 0x000a33c0   (est. sk_cap_table_load_wrap)
 * Ghidra: void FUN_000a33c0(word_t _a, ...)
 * Saves allocator state and runs FUN_000a35d0 (capability table load).
 * Confidence: low */
void FUN_000a33c0(word_t a, word_t b, word_t c, word_t d, word_t e, word_t f, word_t *self, word_t status)
{
    FUN_0036a940(0);
    FUN_000a35d0(a, b, c, d, e, f, self, status);
}

/* FUN_000a3444 @ 0x000a3444   (est. sk_cap_table_replace)
 * Ghidra: void FUN_000a3444(long *param_1,undefined8 param_2,(word_t _a, ...)
 * Replaces the capability table at self+0x10: invokes the source object's
 * +0x48 collector (FUN_000a06cc), releases the old table, and installs the new
 * one, recording the flag param_4&1 at +0x28.
 * Confidence: low
 * Notes: metadata pair 0x650298/0x4c1910; x21 status. */
void FUN_000a3444(word_t *param_1, word_t param_2, word_t param_3, word_t param_4,
                  word_t *self, word_t status)
{
    word_t lVar1;
    word_t stack;
    word_t u2;

    lVar1 = FUN_00002534((word_t)0x650298, (word_t)0x4c1910);
    (void)lVar1;
    *(word_t *)((uintptr_t)self + 0x10) = (word_t)&_DAT_00657778;
    *(word_t *)((uintptr_t)self + 0x18) = param_2;
    *(word_t *)((uintptr_t)self + 0x20) = param_3;
    (*(void (**)(word_t *))(*((word_t**)param_1) + 0x48))(&stack);
    u2 = (word_t)FUN_000a06cc(stack);
    if (status == 0) {
        FUN_0036b118((word_t)param_1);
        {
            word_t old = *(word_t *)((uintptr_t)self + 0x10);
            *(word_t *)((uintptr_t)self + 0x10) = u2;
            FUN_0036b118(old);
        }
        *(word_t *)((uintptr_t)self + 0x28) = param_4 & 1;
    } else {
        FUN_0036b118((word_t)param_1);
        FUN_0036b118(*(word_t *)((uintptr_t)self + 0x10));
        FUN_0036b6f4();
    }
}

/* FUN_000a35d0 @ 0x000a35d0   (est. sk_cap_table_load)
 * Ghidra: void FUN_000a35d0(word_t _a, ...)
 * Loads a capability table from the source (param_5/param_6): initialises the
 * iterator, stores the object/span into self+0x10/0x18/0x20, runs the stream
 * builder FUN_000a0c8c with callback FUN_000a64d8, and installs the result at
 * self+0x10. On x21!=0 releases and aborts.
 * Confidence: low
 * Notes: iterator metadata 0x608644; map FUN_000a649c; callback FUN_000a64d8. */
void FUN_000a35d0(word_t param_1, word_t param_2, word_t param_3, word_t param_4,
                  word_t param_5, word_t param_6, word_t *self, word_t status)
{
    word_t it = FUN_00377824(0, param_6, param_5, (word_t)0x608644, (word_t)0x608664);
    word_t stack;
    word_t u4, u5, u2;

    FUN_000a6f88(0);
    FUN_000a6f68(0);
    *(word_t *)((uintptr_t)self + 0x10) = FUN_0036b270(0);
    *(word_t *)((uintptr_t)self + 0x18) = param_2;
    *(word_t *)((uintptr_t)self + 0x20) = param_3;
    ((word_t (*)(word_t, word_t, word_t))FUN_000a649c(param_6))((word_t)&stack, param_5, param_6);
    if (status == 0) {
        u4 = FUN_00002534((word_t)0x64c260, (word_t)0x4bbc30);
        u5 = FUN_00377bec(param_6, param_5, it, (word_t)0x608644, (word_t)0x608654);
        u4 = FUN_000a0c8c((word_t)FUN_000a64d8, (word_t)&stack, it, (word_t)0x6619c0, u4, u5,
                          (word_t)0x66c1c8, 0, 0);
        (*(void (**)(word_t, word_t))(*(word_t *)(param_5 + -8) + 8))(param_1, param_5);
        (*(void (**)(word_t, word_t))(*(word_t *)(FUN_0036b270(0) + 8) + 0))((word_t)&stack, it);
        u2 = *(word_t *)((uintptr_t)self + 0x10);
        *(word_t *)((uintptr_t)self + 0x10) = u4;
        FUN_0036b118(u2);
        *(word_t *)((uintptr_t)self + 0x28) = (word_t)param_4 & 1;
    } else {
        (*(void (**)(word_t, word_t))(*(word_t *)(param_5 + -8) + 8))(param_1, param_5);
        FUN_0036b118(*(word_t *)((uintptr_t)self + 0x10));
        FUN_0036b6f4();
    }
}

/* FUN_000a3864 @ 0x000a3864   (est. sk_cap_table_read)
 * Ghidra: void FUN_000a3864(word_t _a, ...)
 * Reads a capability-table record: invokes the source method FUN_000a6b64,
 * runs the stream builder FUN_000a0c8c with callback FUN_000a6b94, queries the
 * record's sub-fields (FUN_000a6bb8/6be8/6c18, FUN_000a18c4) and a uuid, and
 * writes the 7-field output record into param_1.
 * Confidence: low
 * Notes: callback FUN_000a6b94; uuid FUN_001051e0. */
void FUN_000a3864(word_t *out, word_t param_2, word_t param_3, word_t param_4,
                  word_t param_5, word_t param_6, word_t status)
{
    word_t st;
    word_t u3, u4, u5;
    word_t rec[3];
    word_t au[2];

    ((word_t (*)(word_t, word_t, word_t))FUN_000a6b64(param_6))((word_t)&st, param_4, param_6);
    if (status == 0) {
        FUN_0006a4c0((word_t)&st, st);
        u3 = FUN_000e4078(0);
        u3 = FUN_000a0c8c((word_t)FUN_000a6b94, (word_t)&rec, st, u3, (word_t)0x674330,
                          FUN_0036b270(0), (word_t)0x66d208, 0, 0);
        FUN_000026e8((word_t)&st);
        u4 = (*(word_t (**)(word_t, word_t))FUN_000a6bb8(param_6))(param_4, param_6);
        u5 = (*(word_t (**)(word_t, word_t))FUN_000a6be8(param_6))(param_4, param_6);
        au[0] = FUN_000a18c4(param_4);
        au[1] = FUN_001051e0(0);
        FUN_0036b118(FUN_000a6c18(param_6));
        out[0] = u3;
        out[1] = FUN_0036b270(0);
        out[2] = FUN_0036b270(0);
        out[3] = u4;
        *(word_t *)((word_t)out + 0x20) = au[0] & 1;
        *(word_t *)((word_t)out + 0x28) = au[1];
        *(word_t *)((word_t)out + 0x38) = 0;
    }
}
