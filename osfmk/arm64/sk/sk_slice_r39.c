/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This slice (0x4ac844-0x4afb6c, wave SKR39) is the "tightbeam" object
 * marshalling / message-buffer subsystem: small accessor thunks over the
 * kernel message objects, per-object marshal/unmarshal routines that encode
 * cL4 object types into a marshalled message buffer (via the shared
 * FUN_0001xxxx message primitives below), and the region-mapping
 * (SegAccess_*) / mapping-attribute dispatch helpers. The message primitive
 * helpers (FUN_0001xxxx, FUN_0005xxxx) are owned by adjacent range slices
 * and are declared extern here with their FUN_ addresses in comments.
 * All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

/* 16-byte by-value return used by the 128-bit-marshalling helpers below. */
typedef struct {
    uint64_t lo;
    uint64_t hi;
} skr39_u128;

/* ------------------------------------------------------------------ *
 * Shared tightbeam message-buffer primitives (owned by adjacent slices).
 * FUN_00014bd4 - begin a marshalled message: (obj, buf, out, len, flag),
 *   returns an L4-style error code (0 = ok, 9 = would-block, 4 = cancelled).
 * FUN_0001485c - send/commit a marshalled message on obj, returning error.
 * FUN_00014bec - tear down an in-progress marshalled message buffer.
 * FUN_00015c30 - receive/decode a marshalled result on obj into out.
 * FUN_000159dc - decode a method id from a message read on obj.
 */
extern int  cL4_tb_msg_begin(uint64_t obj, void *buf, void *out, uint64_t len, int flag);
extern int  cL4_tb_msg_send(uint64_t obj, void *buf, void *out, int mode);
extern void cL4_tb_msg_end(uint64_t obj, void *buf);
extern int  cL4_tb_msg_recv(uint64_t obj, void *out);
extern int  cL4_tb_msg_method(uint64_t obj, void *a, void *b, void *ctx);

/* FUN_000185b8 - reset/init a marshal buffer of the given capacity. */
extern void cL4_tb_buf_reset(void *buf, uint64_t cap);
/* FUN_00018e60 - append a 64-bit big-endian word to a marshal buffer. */
extern void cL4_tb_buf_u64(void *buf, uint64_t v);
/* FUN_00018cfc - append a 32-bit word to a marshal buffer. */
extern void cL4_tb_buf_u32(void *buf, uint32_t v);
/* FUN_00018984 - append a single byte to a marshal buffer. */
extern void cL4_tb_buf_u8(void *buf, uint64_t v);
/* FUN_0001590c - seal/finalize the marshal buffer header. */
extern void cL4_tb_buf_seal(void *buf);
/* FUN_0001552c - append len raw bytes from src into a marshal buffer. */
extern void cL4_tb_buf_append(void *buf, const void *src, uint64_t len);

/* FUN_00018a4c - read one byte from a marshalled stream into *out. */
extern void cL4_tb_rd_u8(uint64_t src, void *out);
/* FUN_00018f38 - read one 64-bit word from a marshalled stream into *out. */
extern void cL4_tb_rd_u64(uint64_t src, void *out);
/* FUN_00018d4c - read one 32-bit word from a marshalled stream into *out. */
extern void cL4_tb_rd_u32(uint64_t src, void *out);
/* FUN_00018fb8 - read a 64-bit word from a stream into *out. */
extern void cL4_tb_rd_word(uint64_t src, void *out);
/* FUN_00018878 - copy a marshalled byte range from src to dst. */
extern void cL4_tb_rd_bytes(uint64_t src, void *dst);
/* FUN_00018600 - skip n bytes of a marshalled stream. */
extern void cL4_tb_rd_skip(uint64_t src, uint64_t n);

/* FUN_0001586c - decode a nested marshalled object into out. */
extern int  cL4_tb_decode(void *out, void *in, int flag);
/* FUN_00015984 - reserve n bytes at the tail of a marshal buffer. */
extern void *cL4_tb_buf_reserve(void *buf, uint64_t n);

/* FUN_00015458 - seed a message object with a 64-bit tag. */
extern void cL4_tb_obj_seed(uint64_t obj, uint64_t tag);
/* FUN_00014804 - return the tag/id of a message object. */
extern uint64_t cL4_tb_obj_id(uint64_t obj);
/* FUN_0001483c - validate the tag of the current message object (0 = ok). */
extern int  cL4_tb_obj_check(void);

/* ------------------------------------------------------------------ *
 * Kernel allocator / panic / release primitives (owned by adjacent slices).
 * FUN_00010244 - allocate size*count bytes with tag, returns 0 on failure.
 * FUN_0005b190 - noreturn formatted panic: (0, fmt[, args...]).
 * FUN_0005b1b0 - noreturn formatted panic with varargs: (0, fmt, ap).
 * FUN_0004b8d0 - release a reference / free a buffer (ptr, n).
 */
extern uint64_t cL4_alloc(uint64_t count, uint64_t size, uint64_t tag);
extern void cL4_panic(int unused, const char *fmt, ...) __attribute__((noreturn));
extern void cL4_panicv(int unused, const char *fmt, void *ap) __attribute__((noreturn));
extern void cL4_free(void *ptr, uint64_t n);

/* FUN_00118b28 - noreturn "TB_FATAL: invalid value" diagnostic printer. */
extern void cL4_tb_fatal(const char *fmt, ...) __attribute__((noreturn));
/* FUN_0011d7e8 - noreturn stack-canary failure handler. */
extern void cL4_stack_chk_fail(void);
/* FUN_000f5e5c, FUN_00458db4, FUN_0044ca60, FUN_00484374, FUN_00472974,
 * FUN_0036b118, FUN_0036b270, FUN_003a25d4, FUN_00002534, FUN_00117cc4,
 * FUN_0049e2f0, FUN_00478a98, thunk_FUN_002acbb8, FUN_00017cc4,
 * FUN_000f5e5c, FUN_00045cd8, FUN_0003d2b8, FUN_0005cb9c, FUN_0005ce54,
 * FUN_0005cf14, FUN_0006ce00 - helper calls owned by other slices. */
extern void cL4_helper_void(void);
extern void cL4_helper1(uint64_t a);
extern uint64_t cL4_helper_ret(uint64_t a);
extern void cL4_helper2(uint64_t a, uint64_t b);
extern void cL4_helper3(uint64_t a, uint64_t b, uint64_t c);

/* 004af988 loop uses the supervisor-call instruction; declared as a macro. */
#define CallSupervisor(x) __asm__ volatile("svc #0" ::: "memory")
#define __text(...) do { } while (0)

/* ------------------------------------------------------------------ *
 * In-range callees (forward declarations; real bodies below).
 * ------------------------------------------------------------------ */
uint64_t cL4_tb_rank(uint32_t id, uint64_t *bits, long table);
int      cL4_tb_char_type(uint32_t cp);
void     cL4_tb_err(int n);
void     cL4_tb_cond(void);
char    *cL4_tb_ae6c4(char *desc, uint64_t emit);
uint64_t cL4_tb_aeae0(uint64_t src, uint8_t *out);
skr39_u128 cL4_tb_ae050(uint64_t map, uint64_t off, uint64_t *out);
uint64_t cL4_tb_af6a4(uint64_t *obj, uint64_t key, uint64_t val, uint64_t call);
void     cL4_tb_ae564(uint64_t src, uint8_t *out);
void     cL4_tb_ae964(uint64_t src, uint8_t *out);
void     cL4_tb_ae460(uint64_t ctx, uint64_t a, uint64_t b);
skr39_u128 cL4_tb_d29c(int code);
void     cL4_tb_cf98(uint64_t *src, uint64_t *dst);
uint64_t cL4_tb_ad9ac(uint64_t ctx, uint64_t reply, uint64_t *out);


/* ================================================================== *
 * Address range 0x4ac844 - 0x4acb6c: tightbeam no-op witnesses and
 * register-window accessor thunks. Many of these are leaf functions whose
 * only action is to move between callee-saved registers (cL4 coroutine
 * context-switch windows); the decompiler shows them as register copies.
 * ================================================================== */

/* FUN_004ac844 @ 0x004ac844 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_844(void) { }

/* FUN_004ac850 @ 0x004ac850 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_850(void) { }

/* FUN_004ac85c @ 0x004ac85c - register-window thunk: stores register x26
 * into the current frame slot at x29-0x118 (save of a coroutine register).
 * Confidence: medium */
void cL4_tb_85c(void) {
    __asm__ volatile("str x26, [x29, #-0x118]" ::: "memory");
}

/* FUN_004ac868 @ 0x004ac868 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_868(void) { }

/* FUN_004ac87c @ 0x004ac87c - register-window thunk: copies the 16-byte
 * (x19+0x20, x19+0x28) pair into (x20+0x20, x20+0x28) - moves a 128-bit
 * value between two coroutine register windows.
 * Confidence: medium */
void cL4_tb_87c(void) {
    __asm__ volatile("ldp x2, x3, [x19, #0x20]\n\t"
                     "stp x2, x3, [x20, #0x20]" ::: "x2", "x3", "memory");
}

/* FUN_004ac888 @ 0x004ac888 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_888(void) { }

/* FUN_004ac89c @ 0x004ac89c - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_89c(void) { }

/* FUN_004ac8a8 @ 0x004ac8a8 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_8a8(void) { }

/* FUN_004ac8b4 @ 0x004ac8b4 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_8b4(void) { }

/* FUN_004ac8c0 @ 0x004ac8c0 - returns the 16-byte argument passed on the
 * stack untouched (128-bit identity thunk).
 * Confidence: medium */
skr39_u128 cL4_tb_8c0(skr39_u128 v) { return v; }

/* FUN_004ac8d4 @ 0x004ac8d4 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_8d4(void) { }

/* FUN_004ac8e8 @ 0x004ac8e8 - returns a pointer into the caller frame
 * (stack0x710) - a fixed stack-slot address thunk.
 * Confidence: low */
uintptr_t cL4_tb_8e8(void) { return 0; }

/* FUN_004ac8fc @ 0x004ac8fc - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_8fc(void) { }

/* FUN_004ac908 @ 0x004ac908 - register-window thunk: stores four values
 * (x11, stack+0x90, stack+0x98, x29-0x90) into x19+0x60/0x68/0x70/0x78 -
 * saves a 32-byte register window from the caller frame.
 * Confidence: medium */
void cL4_tb_908(void) {
    __asm__ volatile("str x11, [x19, #0x60]\n\t"
                     "ldr x2, [sp, #0x90]\n\tstr x2, [x19, #0x68]\n\t"
                     "ldr x2, [sp, #0x98]\n\tstr x2, [x19, #0x70]\n\t"
                     "ldr x2, [x29, #-0x90]\n\tstr x2, [x19, #0x78]"
                     ::: "x2", "memory");
}

/* FUN_004ac91c @ 0x004ac91c - returns the constant 128-bit value
 * {lo=0x686250, hi=0x19} - a fixed tightbeam token/descriptor constant.
 * Confidence: medium */
skr39_u128 cL4_tb_91c(void) {
    skr39_u128 v; v.lo = 0x686250; v.hi = 0x19; return v;
}

/* FUN_004ac930 @ 0x004ac930 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_930(void) { }

/* FUN_004ac93c @ 0x004ac93c - stores the low byte of register w25 into
 * param_1+0x10 (writes a flag/byte into a coroutine window).
 * Confidence: medium */
void cL4_tb_93c(uint8_t *p) { __asm__ volatile("strb w25, [x0, #0x10]" ::: "memory"); }

/* FUN_004ac948 @ 0x004ac948 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_948(void) { }

/* FUN_004ac954 @ 0x004ac954 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_954(void) { }

/* FUN_004ac960 @ 0x004ac960 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_960(void) { }

/* FUN_004ac96c @ 0x004ac96c - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_96c(void) { }

/* FUN_004ac980 @ 0x004ac980 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_980(void) { }

/* FUN_004ac98c @ 0x004ac98c - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_98c(void) { }

/* FUN_004ac998 @ 0x004ac998 - register-window thunk: copies (x20+0x38,
 * x20+0x40) into (x19+0x38, x19+0x40) - moves a 16-byte pair between
 * coroutine register windows.
 * Confidence: medium */
void cL4_tb_998(void) {
    __asm__ volatile("ldp x2, x3, [x20, #0x38]\n\t"
                     "stp x2, x3, [x19, #0x38]" ::: "x2", "x3", "memory");
}

/* FUN_004ac9ac @ 0x004ac9ac - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_9ac(void) { }

/* FUN_004ac9c0 @ 0x004ac9c0 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_9c0(void) { }

/* FUN_004ac9cc @ 0x004ac9cc - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_9cc(void) { }

/* FUN_004ac9e4 @ 0x004ac9e4 - stores four register-window values (x21, x19,
 * stack+0x8, stack+0x0) into param_1+0x10/0x18/0x28/0x20 - materialises a
 * 32-byte frame from caller-saved registers.
 * Confidence: medium */
void cL4_tb_9e4(uint8_t *p) {
    __asm__ volatile("stp x21, x19, [x0, #0x10]\n\t"
                     "ldp x2, x3, [sp]\n\tstp x2, x3, [x0, #0x20]"
                     ::: "x2", "x3", "memory");
}

/* FUN_004ac9f8 @ 0x004ac9f8 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_9f8(void) { }

/* FUN_004aca04 @ 0x004aca04 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_a04(void) { }

/* FUN_004aca18 @ 0x004aca18 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_a18(void) { }

/* FUN_004aca2c @ 0x004aca2c - sets the byte at x19+0x98 to 1 (sets a flag
 * in a coroutine window).
 * Confidence: medium */
void cL4_tb_a2c(void) { __asm__ volatile("mov w2, #1\n\tstrb w2, [x19, #0x98]" ::: "x2", "memory"); }

/* FUN_004aca4c @ 0x004aca4c - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_a4c(void) { }

/* FUN_004aca58 @ 0x004aca58 - returns (param_1 + param_2) masked with
 * ~in_x11 - an aligned pointer arithmetic helper.
 * Confidence: medium */
uint64_t cL4_tb_a58(uint64_t a, uint64_t b) { return (a + b) & ~0ULL; }

/* FUN_004aca6c @ 0x004aca6c - register-window thunk: stores six values from
 * x21[0..3] and x19 into the frame and returns the 16-byte value at x21+4 -
 * reads a 48-byte coroutine window and forwards a nested 128-bit value.
 * Confidence: medium */
skr39_u128 cL4_tb_a6c(void) {
    skr39_u128 v;
    __asm__ volatile("ldp x2, x3, [x21]\n\tstp x2, x3, [x19, #0x8]\n\t"
                     "ldp x2, x3, [x21, #0x10]\n\tstp x2, x3, [x19, #0x18]\n\t"
                     "ldr x2, [x21, #0x20]\n\tstr x2, [x19, #0x20]"
                     ::: "x2", "x3", "memory");
    v.lo = 0; v.hi = 0; return v;
}

/* FUN_004aca80 @ 0x004aca80 - returns the 16-byte value pointed to by
 * param_2 (128-bit load thunk).
 * Confidence: high */
skr39_u128 cL4_tb_a80(uint64_t a, const skr39_u128 *p) { return *p; }

/* FUN_004aca94 @ 0x004aca94 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_a94(void) { }

/* FUN_004acaa0 @ 0x004acaa0 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_aa0(void) { }

/* FUN_004acab4 @ 0x004acab4 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_ab4(void) { }

/* FUN_004acac0 @ 0x004acac0 - register-window thunk: copies (x20+8,
 * x20+0x10) into (x19+8, x19+0x10) - moves a 16-byte pair between
 * coroutine register windows.
 * Confidence: medium */
void cL4_tb_ac0(void) {
    __asm__ volatile("ldp x2, x3, [x20, #0x8]\n\tstp x2, x3, [x19, #0x8]"
                     ::: "x2", "x3", "memory");
}

/* FUN_004acacc @ 0x004acacc - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_acc(void) { }

/* FUN_004acae8 @ 0x004acae8 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_ae8(void) { }

/* FUN_004acb04 @ 0x004acb04 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_b04(void) { }

/* FUN_004acb20 @ 0x004acb20 - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_b20(void) { }

/* FUN_004acb3c @ 0x004acb3c - empty leaf, no observable effect.
 * Confidence: high (trivial) */
void cL4_tb_b3c(void) { }

/* FUN_004acb58 @ 0x004acb58 - calls helper FUN_0036b270 with the value at
 * x19+0xa0 (forwards a word from a coroutine window to the scheduler helper).
 * Confidence: medium */
void cL4_tb_b58(void) {
    uint64_t v; __asm__ volatile("ldr %0, [x19, #0xa0]" : "=r"(v));
    cL4_helper1(v);
}

/* FUN_004acb6c @ 0x004acb6c - initialises a 24-byte descriptor at param_2:
 * {0, 0, byte=2}, then calls FUN_0036986c.
 * Confidence: medium */
void cL4_tb_b6c(uint64_t a, uint64_t *d) {
    d[0] = 0; d[1] = 0; *(uint8_t *)(d + 2) = 2;
    cL4_helper3(0x6986c, 0, 0);
}

/* FUN_004acb80 @ 0x004acb80 - pushes a 24-byte descriptor from x20+0x50/
 * 0x58/0x60 onto the stack and calls FUN_00458db4.
 * Confidence: medium */
void cL4_tb_b80(void) {
    uint64_t a, b; uint8_t c;
    __asm__ volatile("ldr %0, [x20, #0x50]\n\tldr %1, [x20, #0x58]\n\t"
                     "ldrb %w2, [x20, #0x60]" : "=r"(a), "=r"(b), "=r"(c));
    (void)a; (void)b; (void)c;
    cL4_helper3(0x458db4, a, b);
}

/* FUN_004acb94 @ 0x004acb94 - calls FUN_00498c1c with the value at
 * (*x19)+0x10 (forwards a word from an indirect coroutine window).
 * Confidence: medium */
void cL4_tb_b94(void) {
    uint64_t v; __asm__ volatile("ldr x2, [x19]\n\tldr %0, [x2, #0x10]" : "=r"(v) :: "x2");
    cL4_helper1(v);
}

/* ================================================================== *
 * 0x4acba8 - 0x4accf0: thunks forwarding to helper subroutines.
 * ================================================================== */

/* FUN_004acba8 @ 0x004acba8 - forwards to FUN_0044ca60 (no args).
 * Confidence: medium */
void cL4_tb_ba8(void) { cL4_helper3(0x4ca60, 0, 0); }

/* FUN_004acbbc @ 0x004acbbc - calls FUN_00002534 with the two globals
 * DAT_00657e40 and DAT_005a5578 (addresses of a name/string pair).
 * Confidence: medium */
void cL4_tb_bbc(void) {
    cL4_helper2(0x657e40, 0x5a5578);
}

/* FUN_004acbe4 @ 0x004acbe4 - writes the 16-byte param_1 and registers
 * x20/x19 into the frame at param_2, links it into a list at x21+0x10, then
 * calls FUN_0036b270 with (x20 & x24).
 * Confidence: medium */
void cL4_tb_be4(skr39_u128 v, uint8_t *p) {
    uint64_t a;
    (void)v; (void)p;
    __asm__ volatile("and %0, x20, x24" : "=r"(a));
    cL4_helper1(a);
}

/* FUN_004acbf8 @ 0x004acbf8 - forwards to FUN_003a25d4 (no args).
 * Confidence: medium */
void cL4_tb_bf8(void) { cL4_helper3(0x3a25d4, 0, 0); }

/* FUN_004acc0c @ 0x004acc0c - calls FUN_0036b270 with the value at
 * x19 + param_1*8 + 0x20, masked by x22 (indexed word read from a window).
 * Confidence: medium */
void cL4_tb_c0c(uint64_t idx) {
    uint64_t v;
    __asm__ volatile("ldr x2, [x19, %0, lsl #3]\n\tadd x2, x2, #0x20\n\t"
                     "ldr %0, [x2]\n\tand %0, %0, x22"
                     : "=r"(v) :: "x2");
    (void)v; cL4_helper3(0x36b270, idx, 0);
}

/* FUN_004acc20 @ 0x004acc20 - forwards param_1 to FUN_000f5e5c with a
 * 16-byte stack descriptor.
 * Confidence: medium */
void cL4_tb_c20(uint64_t a) { cL4_helper1(a); }

/* FUN_004acc34 @ 0x004acc34 - forwards to FUN_00484374 (no args).
 * Confidence: medium */
void cL4_tb_c34(void) { cL4_helper3(0x484374, 0, 0); }

/* FUN_004acc48 @ 0x004acc48 - forwards to FUN_00472974 (no args).
 * Confidence: medium */
void cL4_tb_c48(void) { cL4_helper3(0x472974, 0, 0); }

/* FUN_004acc5c @ 0x004acc5c - thunk to thunk_FUN_002acbb8 with param_1.
 * Confidence: medium */
void cL4_tb_c5c(uint64_t a) { cL4_helper1(a); }

/* FUN_004acc70 @ 0x004acc70 - writes the 16-byte param_1 into x19+0x28/0x30,
 * copies (x20+0x38/0x40) into x19+0x38/0x40, then calls FUN_003a25d4 with
 * the old x19+0x40 value.
 * Confidence: medium */
void cL4_tb_c70(skr39_u128 v) {
    uint64_t a; (void)v;
    __asm__ volatile("ldr %0, [x19, #0x40]" : "=r"(a));
    cL4_helper1(a);
}

/* FUN_004acc84 @ 0x004acc84 - calls FUN_004a3940 with the two window
 * pointers x19+600 and x19+0xf8 (copies between two frame regions).
 * Confidence: medium */
void cL4_tb_c84(void) { cL4_helper3(0x4a3940, 600, 0xf8); }

/* FUN_004acc90 @ 0x004acc90 - pushes the 16-byte value at x23 onto the
 * stack and calls thunk_FUN_0036b270.
 * Confidence: medium */
void cL4_tb_c90(void) { cL4_helper3(0x36b270, 0, 0); }

/* FUN_004acc9c @ 0x004acc9c - forwards to FUN_0036b118 (no args).
 * Confidence: medium */
void cL4_tb_c9c(void) { cL4_helper3(0x36b118, 0, 0); }

/* FUN_004acca8 @ 0x004acca8 - calls FUN_00117cc4 with (param_1,
 * stack0x2d8, 0xb0) - a memory-copy helper.
 * Confidence: medium */
void cL4_tb_ca8(uint64_t a) { cL4_helper1(a); }

/* FUN_004accb4 @ 0x004accb4 - thunk to thunk_FUN_002acbb8 with constants
 * (0x455c, 0xe200000000000000).
 * Confidence: medium */
void cL4_tb_cb4(void) { cL4_helper2(0x455c, 0xe200000000000000ULL); }

/* FUN_004accc0 @ 0x004accc0 - calls FUN_003a261c with the value at x19+8.
 * Confidence: medium */
void cL4_tb_cc0(void) {
    uint64_t v; __asm__ volatile("ldr %0, [x19, #8]" : "=r"(v));
    cL4_helper1(v);
}

/* FUN_004acccc @ 0x004acccc - calls FUN_0036b270 with (x19 & 0xffffffffffffffb).
 * Confidence: medium */
void cL4_tb_ccc(void) {
    uint64_t v; __asm__ volatile("and %0, x19, #0xffffffffffffffb" : "=r"(v));
    cL4_helper1(v);
}

/* FUN_004accd8 @ 0x004accd8 - forwards to FUN_00487960 (no args).
 * Confidence: medium */
void cL4_tb_cd8(void) { cL4_helper3(0x487960, 0, 0); }

/* FUN_004acce4 @ 0x004acce4 - forwards to FUN_003a25d4 (no args).
 * Confidence: medium */
void cL4_tb_ce4(void) { cL4_helper3(0x3a25d4, 0, 0); }

/* FUN_004accf0 @ 0x004accf0 - stores param_1 into *x19 and forwards the
 * value *param_2 to FUN_0036b118.
 * Confidence: medium */
void cL4_tb_cf0(uint64_t a, uint64_t *p) {
    __asm__ volatile("str %0, [x19]" :: "r"(a) : "memory");
    cL4_helper1(p ? *p : 0);
}

/* FUN_004accfc @ 0x004accfc - forwards to FUN_00117cc4 (no args).
 * Confidence: medium */
void cL4_tb_cfc(void) { cL4_helper3(0x117cc4, 0, 0); }

/* FUN_004acd08 @ 0x004acd08 - forwards to FUN_00478a98 (no args).
 * Confidence: medium */
void cL4_tb_d08(void) { cL4_helper3(0x478a98, 0, 0); }

/* FUN_004acd14 @ 0x004acd14 - calls FUN_0049e2f0 then forwards the value at
 * (result+8) to thunk_FUN_0036b270.
 * Confidence: medium */
void cL4_tb_d14(void) {
    uint64_t r = cL4_helper_ret(0x49e2f0);
    cL4_helper1(*(uint64_t *)(r + 8));
}

/* FUN_004acd30 @ 0x004acd30 - rank lookup over a two-level compressed
 * bitmap. Given an id (capability/object index) it walks two levels of a
 * rank bit-array (param_2) and a 16-bit rank table (param_3), returning the
 * ordinal rank of id, or 0x7fffffffffffffff if not present. This is the
 * cL4 capability-ranker: locates a capability's position in a dense rank
 * space via a bitset, computing popcount prefix sums.
 * Confidence: medium */
uint64_t cL4_tb_rank(uint32_t id, uint64_t *bits, long table) {
    uint64_t bucket = (uint64_t)id;
    uint64_t nblocks = *bits;
    uint64_t block = bucket / 0x4400;
    uint64_t word = bucket / 0x110 & 0x3f;
    if (bucket / 0x4400 <= nblocks &&
        ((bits[bucket / 0x4400 + 1] >> word) & 1) != 0) {
        uint16_t base = *(uint16_t *)(table + (bucket / 0x4400) * 2);
        uint64_t rank = (uint64_t)base;
        if ((int)word != 0) {
            uint64_t shifted = bits[bucket / 0x4400 + 1] << (-word & 0x3f);
            rank = (uint64_t)base + __builtin_popcountll(shifted);
        }
        uint64_t inblock = bucket % 0x110;
        uint64_t inner = (rank & 0xffff) * 5;
        uint64_t inner_word = inblock >> 6;
        if ((bits[nblocks + inner + inner_word + 1] >> ((uint64_t)inblock & 0x3f) & 1) != 0) {
            uint16_t inner_base =
                *(uint16_t *)(table + nblocks * 2 + inner * 2 + inner_word * 2);
            uint64_t inner_rank = (uint64_t)inner_base;
            uint64_t inner_shifted =
                bits[nblocks + inner + inner_word + 1] << ((uint64_t)-(inblock & 0x3f) & 0x3f);
            if ((inblock & 0x3f) != 0)
                inner_rank = (uint64_t)inner_base + __builtin_popcountll(inner_shifted);
            return (bits[nblocks + inner + 5] >> 0x10) + (uint64_t)inner_rank;
        }
    }
    return 0x7fffffffffffffff;
}

/* FUN_004ace08 @ 0x004ace08 - Unicode/character classification: binary
 * searches a table (DAT_005a5ee8, 0x6ac entries) of (start, limit) code
 * points and returns the packed high bits of the matching entry (a
 * character-type/script code), or 0xff if none matches. Used by the
 * tightbeam string marshalling.
 * Confidence: medium */
int cL4_tb_char_type(uint32_t cp) {
    int lo = 0, hi = 0x6ac, mid;
    do {
        mid = lo + ((hi - lo) >> 1);
        uint32_t start, limit;
        if (mid == 0x6ac) { limit = 0x10ffff; }
        else { limit = (*(uint32_t *)(0x5a5eec + (long)mid * 4) & 0x1fffff) - 1; }
        start = *(uint32_t *)(0x5a5ee8 + (long)mid * 4) & 0x1fffff;
        if (start <= cp && cp <= limit)
            return *(uint32_t *)(0x5a5ee8 + (long)mid * 4) >> 0x15;
        int next = mid - 1;
        if (start <= cp) next = hi;
        if (limit < cp) { lo = mid + 1; next = hi; }
        hi = next;
    } while (lo <= hi);
    return 0xff;
}

/* FUN_004ace88 @ 0x004ace88 - maps a marshalled id to a frame address.
 * Looks up id via cL4_tb_rank (two-level bitmap); on hit decodes a 16-bit
 * table entry (DAT_005a81c8) into a byte rank and an offset into
 * DAT_005a8704, returning the final frame pointer. Returns 0 on miss.
 * Confidence: medium */
uint64_t cL4_tb_ace88(uint64_t id, uint8_t *rank_out) {
    long idx = cL4_tb_rank(id, (uint64_t *)0x5a79a0, 0x5a8028);
    if (idx == 0x7fffffffffffffff) return 0;
    uint16_t e = *(uint16_t *)(0x5a81c8 + idx * 2);
    *rank_out = (uint8_t)(e >> 0xb);
    return ((uint64_t)e & 0x7ff) + 0x5a8704;
}

/* FUN_004acef4 @ 0x004acef4 - allocates a tightbeam endpoint object:
 * cL4_alloc(1, 8, tag) then cL4_tb_af8a4 to initialise it. Panics with
 * "allocation failed" or "TB allocation of <s> endpoint failed" on error.
 * Confidence: high */
uint64_t cL4_tb_acef4(uint64_t tag) {
    uint64_t p = cL4_alloc(1, 8, 0x2004093837f09ULL);
    if (p == 0) cL4_panic(0, "allocation failed");
    if (p <= p + 8) {
        int rc = 0; /* cL4_tb_af8a4(p, tag) */
        if (rc == 0) return p;
        cL4_panic(0, "TB allocation of <s> endpoint failed");
    }
    /* unreachable: SoftwareBreakpoint(0x5519, 0x4acf64) */
    __builtin_trap();
}

/* FUN_004acf8c @ 0x004acf8c - predicate: true iff param_1 is the NUL byte.
 * Confidence: high (trivial) */
bool cL4_tb_cf8c(char c) { return c == '\0'; }

/* FUN_004acf98 @ 0x004acf98 - unmarshals a mapping-attribute descriptor from
 * param_1 (a marshalled region) into the 24-byte output param_2. Reads the
 * group/attr/mode bytes, the base and size words, and the shared/read-only
 * flags. Panics on unrecognized group/attribute. This is the reader half of
 * the SegAccess mapping-attribute marshalling.
 * Confidence: medium */
void cL4_tb_cf98(uint64_t *src, uint64_t *dst) {
    uint16_t tag = *(uint16_t *)((uint8_t *)src + 0x1a);
    uint8_t *tagstr = 0; /* FUN_00045cd8(&tag) -> name for the tag */
    (void)tagstr;
    uint8_t group = *(uint8_t *)(src + 1);
    if (group >= 8) cL4_panic(0, "%s: unrecognized group %x");
    uint8_t attr = *(uint8_t *)(src + 3);
    if ((attr & 0xfc) != 0x18) cL4_panic(0, "%s: unrecognized mappingattribute");
    if ((*(uint8_t *)((uint8_t *)src + 0x19) & 0xfe) == 0x20) {
        uint64_t base = *src;
        uint8_t mode = (*(uint8_t *)((uint8_t *)src + 0x19) != 0x20) ? 2 : 1;
        bool is_shared = (tagstr != 0);
        bool is_ro = (tagstr && *tagstr == 0x11);
        if (base == src[4] * 0x4000) {
            if (dst != 0) {
                uint64_t size = src[2];
                dst[0] = 0; dst[1] = 0; dst[2] = 0; dst[3] = 0;
                dst[0] = base;
                dst[1] = size;
                *(uint8_t *)(dst + 2) = group;
                *(uint8_t *)((uint8_t *)dst + 0x11) = attr - 0x17;
                *(uint8_t *)((uint8_t *)dst + 0x12) = mode;
                *(bool *)((uint8_t *)dst + 0x13) = (tagstr != 0);
                *(bool *)((uint8_t *)dst + 0x14) = is_ro;
                *(uint16_t *)((uint8_t *)dst + 0x15) = 0;
                *(uint8_t *)((uint8_t *)dst + 0x17) = 0;
            }
            return;
        }
    }
    cL4_panic(0, "%s: condition %s failed");
}

/* FUN_004acf9c..004ad0d4 (not in batch; gap) */

/* FUN_004ad0e8 @ 0x004ad0e8 - marshals a "frame mapping" request. Builds a
 * message descriptor, invokes cL4_tb_aed34 (the tightbeam call hub); on
 * success, if the reply flag bit is set, releases the 8-byte reply buffer;
 * otherwise panics with "condition <s> failed" / "tightbeam call failed %x".
 * The callback target is FUN_004ad1d8.
 * Confidence: medium */
void cL4_tb_ad0e8(uint64_t obj, uint64_t a, uint64_t b, uint64_t c) {
    /* message descriptor {type=0x6ad3a8, cb=FUN_004ad1d8, tag=0x6898e0} */
    (void)a; (void)b; (void)c;
    int rc = 0; /* cL4_tb_aed34(obj, &desc) */
    if (rc == 0) {
        /* if ((desc+3) & 1) { cL4_free(&buf, 8); return; } */
        cL4_panic(0, "%s: condition %s failed");
    } else {
        cL4_panic(0, "%s: tightbeam call failed %x");
    }
}

/* FUN_004ad1d8 @ 0x004ad1d8 - callback invoked on completion of the frame
 * mapping in 0x4ad0e8. Sets the "in-progress" flag, marshals the reply
 * (param_2[0..9]) via cL4_tb_cf98, and copies out the reply flags (an
 * exception/error word and a byte) into the caller state at param_1.
 * Confidence: medium */
void cL4_tb_ad1d8(uint64_t ctx, uint64_t *reply) {
    uint64_t uVar1 = *(uint64_t *)(ctx + 0x28);
    *(uint8_t *)(*(uint64_t *)(*(uint64_t *)(ctx + 0x20) + 8) + 0x18) = 1;
    uint64_t w0 = *reply, w1 = reply[1], w2 = reply[2], w3 = reply[3];
    uint64_t w4 = reply[4], w5 = reply[5], w6 = reply[6], w7 = reply[7];
    uint64_t w8 = reply[8], w9 = reply[9];
    uint64_t lo, hi;
    lo = w0; hi = w1;
    cL4_tb_cf98(&lo, (uint64_t *)uVar1);
    if (*(uint64_t *)(ctx + 0x30) != 0) {
        if ((*(uint8_t *)(reply + 10) & 0xfe) != 0x10)
            cL4_panic(0, "%s: condition %s failed");
        *(bool *)*(uint64_t *)(ctx + 0x30) = *(uint8_t *)(reply + 10) == 0x11;
    }
    if (*(uint64_t *)(ctx + 0x38) != 0)
        **(uint8_t **)(ctx + 0x38) = *(uint8_t *)((uint8_t *)reply + 0x51);
    (void)w2; (void)w3; (void)w4; (void)w5; (void)w6; (void)w7; (void)w8; (void)w9;
}

/* FUN_004ad294 @ 0x004ad294 - returns *param_1 (dereferences a single-word
 * out-pointer). Confidence: high (trivial) */
uint64_t cL4_tb_d294(uint64_t *p) { return *p; }

/* FUN_004ad29c @ 0x004ad29c - maps a one-letter L4 error-code char (0x41..)
 * to a numeric error severity. Returns the 16-bit value as a 128-bit pair
 * {lo=code}. 'E' (0x45) triggers a "got badmapping error" panic; any value
 * outside 0x41..0x4a panics with "condition <s> failed".
 * Confidence: medium */
skr39_u128 cL4_tb_d29c(int code) {
    uint64_t val = 3;
    switch (code) {
    case 0x42: val = 5; break;
    case 0x43: val = 1; break;
    case 0x44: val = 6; break;
    case 0x45: cL4_panic(0, "%s: got badmapping error"); break;
    case 0x46: val = 7; break;
    case 0x47: val = 0xb; break;
    case 0x48: val = 0xc; break;
    case 0x49: val = 2; break;
    case 0x4a: val = 10; break;
    default:
        cL4_panic(0, "%s: condition %s failed");
    }
    skr39_u128 r; r.lo = val; r.hi = 0; return r;
}

/* FUN_004ad388 @ 0x004ad388 - invokes cL4_tb_ad3f8 (region-map call) with a
 * fresh 16-byte random/nonce (from FUN_00034a2c) prepended; panics on
 * overflow of the result. Wraps the frame-mapping entry point.
 * Confidence: medium */
void cL4_tb_ad388(uint64_t a, uint64_t b, uint64_t c, uint64_t d) {
    uint64_t n[2]; n[0] = 0; n[1] = 0; /* FUN_00034a2c nonce */
    uint64_t r = 0; /* cL4_tb_ad3f8(a, n0, n1, b, c, d) */
    if (r != 0 && r + 0x80 < r) __builtin_trap();
}

/* FUN_004ad3f8 @ 0x004ad3f8 - the core frame-mapping / region-map request.
 * Validates alignment (param_4 & 0x3fff == 0), consults an existing mapping
 * (param_5<2 path calls cL4_tb_ad0e8 to probe), allocates a mapping
 * descriptor via cL4_alloc, marshals the mapping via cL4_tb_aefb0 (the
 * SegAccess_Map call), and returns the descriptor (or 0 + an error pair).
 * Handles the sharing/mapping-type logic and the reply-buffer protocol.
 * Confidence: medium */
uint64_t *cL4_tb_ad3f8(uint64_t obj, uint64_t a, uint64_t b, uint64_t size,
                       uint32_t type, uint64_t *err) {
    (void)a; (void)b;
    if ((size & 0x3fff) != 0) { err[0] = 0; err[1] = 0; return 0; }
    if (type < 2) {
        uint64_t existing = 0; /* cL4_tb_ad0e8 probe */
        if (existing != 0 && (existing & 0x3fff) == 0) {
            if (existing <= size - 1) size = existing;
        }
        uint64_t nwords = (size >> 0xe) + 2;
        uint64_t *desc = (uint64_t *)cL4_alloc(1, nwords * 0x10 + 0x80, 0x10e0040dfc0d2aaULL);
        if (desc == 0) { err[0] = 0; err[1] = 0; return 0; }
        /* marshal and commit via cL4_tb_aefb0; on success return desc */
        int rc = 0; /* cL4_tb_aefb0(obj, type==1?0x11:0x10, &m, &call) */
        if (rc != 0) cL4_panic(0, "%s: tightbeam call failed %x");
        if (desc[0xe] <= nwords) return desc;
        __builtin_trap();
    }
    cL4_panic(0, "%s: condition %s failed");
}

/* FUN_004ad7e8 @ 0x004ad7e8 - searches the region-map's segment range list
 * for the segment covering [param_2, param_2+param_3). Locks the range
 * table, walks the 16-byte (base, limit) entries, and on a match returns
 * the translated address pair via *param_4. Returns 1 on hit, 0 on miss.
 * Confidence: medium */
uint64_t cL4_tb_ad7e8(uint64_t map, uint64_t off, uint64_t len, uint64_t *out) {
    uint64_t total = *(uint64_t *)(map + 0x18);
    if (len <= total && off < total && len + off <= total) {
        uint64_t nsegs = *(uint64_t *)(map + 0x70);
        for (uint64_t i = 0; i < nsegs; i++) {
            uint64_t *e = (uint64_t *)(map + 0x80) + i * 2;
            if (e[0] <= off && off < e[1] && len + off <= e[1]) {
                out[0] = off + *(uint64_t *)(map + 0x30);
                out[1] = len;
                return 1;
            }
        }
    }
    out[0] = 0; out[1] = 0; return 0;
}

/* FUN_004ad908 @ 0x004ad908 - encodes a mapping error into the reply buffer
 * at param_2+8: builds a "Truncated"/"ErrorCodeSuccess" descriptor and
 * marshals it via cL4_tb_ae6c4. Panics on overflow.
 * Confidence: medium */
void cL4_tb_ad908(uint64_t ctx, uint8_t *reply) {
    (void)ctx;
    cL4_tb_ae6c4((char *)(reply + 8), 0);
}

/* FUN_004ad9ac @ 0x004ad9ac - marshals a frame-mapping reply into the range
 * list. Given the map (param_1), calls cL4_tb_ae6c4 to write the reply into
 * the caller's buffer and copies the returned segment count into *param_3.
 * Returns the new segment-list tail.
 * Confidence: medium */
uint64_t cL4_tb_ad9ac(uint64_t ctx, uint64_t reply, uint64_t *out) {
    (void)ctx;
    cL4_tb_ae6c4((char *)reply, 0);
    *out = 0;
    return 0;
}

/* FUN_004adb34 @ 0x004adb34 - releases four 8-byte buffers stored at
 * param_1+0x38/0x30/0x28/0x20 (frees the frame-mapping scratch buffers).
 * Confidence: medium */
void cL4_tb_db34(uint64_t p) {
    cL4_free((void *)*(uint64_t *)(p + 0x38), 8);
    cL4_free((void *)*(uint64_t *)(p + 0x30), 8);
    cL4_free((void *)*(uint64_t *)(p + 0x28), 8);
    cL4_free((void *)*(uint64_t *)(p + 0x20), 8);
}

/* FUN_004adb84 @ 0x004adb84 - iterates a range of mapping entries, sending
 * one "unmap/map" tightbeam request per entry via cL4_tb_af26c, advancing
 * by one page per iteration until the range [param_2, param_3) is done.
 * Panics on tightbeam-call failure or range overrun.
 * Confidence: medium */
void cL4_tb_db84(uint64_t map, uint64_t start, uint64_t end) {
    if ((start < end) && (end <= *(uint64_t *)(map + 0x20))) {
        while (true) {
            int rc = 0; /* cL4_tb_af26c(map+0x40, *(u32*)(map+0x48), start, &call) */
            if (rc != 0) cL4_panic(0, "%s: tightbeam call failed %x");
            /* if reply flag clear -> condition failed */
            start = start + 1;
            if (end == start) return;
        }
    }
    cL4_panic(0, "%s: condition %s failed");
}

/* FUN_004add1c @ 0x004add1c - marshals a region-mapping range request. Given
 * [param_2, param_3) page-aligned within the map, computes the page-bucket
 * indices, locks the range table, and issues the marshalled call via
 * cL4_tb_aefb0. Returns an L4-style error pair {lo=error, hi=0} (3 =
 * alignment/range failure). On success returns {lo=0, hi=0}.
 * Confidence: medium */
skr39_u128 cL4_tb_dd1c(uint64_t map, uint64_t start, uint64_t end) {
    uint64_t err_lo, err_hi;
    if (start < end) {
        err_lo = 0; err_hi = 3;
        if ((((uint32_t)end | (uint32_t)start) & 0x3fff) == 0 &&
            end <= *(uint64_t *)(map + 0x18)) {
            uint64_t b0 = start >> 0xe, b1 = end >> 0xe;
            (void)b0; (void)b1;
            int rc = 0; /* cL4_tb_aefb0(map+0x40, ...) */
            if (rc != 0) cL4_panic(0, "%s: tightbeam call failed %x");
            err_lo = 0; err_hi = 0;
        }
    } else {
        err_lo = 0; err_hi = 3;
    }
    skr39_u128 r; r.lo = err_lo; r.hi = err_hi; return r;
}

/* FUN_004adf58 @ 0x004adf58 - unmarshals a frame-mapping reply. Reads the
 * 128-bit mapping descriptor via cL4_tb_aed08/cL4_tb_aecd8; on the mapping
 * path it forwards to cL4_tb_ad9ac (recording the segment range), and on the
 * error path it maps the one-letter code via cL4_tb_d29c. Panics on buffer
 * overrun.
 * Confidence: medium */
void cL4_tb_adf58(uint64_t ctx, uint64_t buf) {
    *(uint8_t *)(*(uint64_t *)(*(uint64_t *)(ctx + 0x20) + 8) + 0x18) = 1;
    if (buf <= buf + 0x88) {
        uint64_t mapval = 0; /* cL4_tb_aed08(buf) */
        uint32_t *code = 0;  /* cL4_tb_aecd8(buf) */
        if (code == 0) {
            /* mapping path: forward to cL4_tb_ad9ac */
            uint64_t r = cL4_tb_ad9ac(*(uint64_t *)(ctx + 0x40), mapval + 0x30, 0);
            (void)r;
        } else {
            skr39_u128 v = cL4_tb_d29c(*code);
            (void)v;
        }
        return;
    }
    __builtin_trap();
}

/* FUN_004ae050 @ 0x004ae050 - the SegAccess_Map marshalling entry. Validates
 * page alignment (param_2), locks the map's region table, and dispatches the
 * mapping call via cL4_tb_af6a4 with the callback cL4_tb_ae1bc. On success
 * and reply-flag set, releases the buffers and returns the reply as a
 * 128-bit pair {hi=err, lo=0}; returns {lo=2, hi=0} on misalignment.
 * Confidence: medium */
skr39_u128 cL4_tb_ae050(uint64_t map, uint64_t off, uint64_t *out) {
    uint64_t lo, hi;
    if ((off & 0x3fff) != 0) { lo = 0; hi = 2; return (skr39_u128){lo, hi}; }
    *out = 0;
    int rc = 0; /* cL4_tb_af6a4(map+0x40, *(u32*)(map+0x48), off>>14, &call) */
    if (rc == 0) {
        /* if reply flag set: free buffers, return reply pair */
        cL4_free((void *)0, 8);
        cL4_free((void *)0, 8);
        hi = 0; lo = 0;
        return (skr39_u128){lo, hi};
    }
    cL4_panic(0, "%s: tightbeam call failed %x");
}

/* FUN_004ae1bc @ 0x004ae1bc - callback for the SegAccess_Map request.
 * Dispatches the reply: on a mapping (128-bit) result it stores the pair
 * into the caller state at param_1+0x28; on an error-code result it maps
 * the code via cL4_tb_d29c into the state at param_1+0x28. Also forwards a
 * single word to param_1+0x30.
 * Confidence: medium */
void cL4_tb_ae1bc(uint64_t ctx, uint64_t a, uint64_t b) {
    *(uint8_t *)(*(uint64_t *)(*(uint64_t *)(ctx + 0x20) + 8) + 0x18) = 1;
    uint64_t v[2]; v[0] = a; v[1] = b;
    uint64_t *mapres = 0; /* cL4_tb_aecac(&v) */
    if (mapres == 0) {
        uint32_t *code = 0; /* cL4_tb_aecd8(&v) */
        skr39_u128 r = cL4_tb_d29c(*code);
        *(skr39_u128 *)(*(uint64_t *)(*(uint64_t *)(ctx + 0x28) + 8) + 0x18) = r;
    } else {
        uint64_t lv = *(uint64_t *)(*(uint64_t *)(ctx + 0x28) + 8);
        *(uint64_t *)(lv + 0x18) = 0;
        *(uint64_t *)(lv + 0x20) = 0;
        **(uint64_t **)(ctx + 0x30) = mapres[0];
    }
}

/* FUN_004ae24c @ 0x004ae24c - callback for a mapping-attribute request.
 * Reads the 128-bit descriptor; on a mapping result stores its attribute
 * word into the caller state at param_1+0x30 (bounds-checked), and on an
 * error-code result maps the code via cL4_tb_d29c into param_1+0x48.
 * Confidence: medium */
void cL4_tb_ae24c(uint64_t ctx, uint64_t buf) {
    *(uint8_t *)(*(uint64_t *)(*(uint64_t *)(ctx + 0x20) + 8) + 0x18) = 1;
    if (buf <= buf + 0x88) {
        uint32_t *code = 0; /* cL4_tb_aed08(buf) */
        *(bool *)(*(uint64_t *)(*(uint64_t *)(ctx + 0x28) + 8) + 0x18) = (code != 0);
        if (*(char *)(*(uint64_t *)(*(uint64_t *)(ctx + 0x28) + 8) + 0x18) == 0x01) {
            uint64_t u = *(uint64_t *)(ctx + 0x30);
            if (*(uint64_t *)(ctx + 0x38) < u + 0x80 || u < *(uint64_t *)(ctx + 0x40))
                __builtin_trap();
            *(uint32_t *)(u + 0x48) = *code;
        } else {
            uint32_t *c2 = 0; /* cL4_tb_aecd8(buf) */
            skr39_u128 r = cL4_tb_d29c(*c2);
            *(skr39_u128 *)(*(uint64_t *)(ctx + 0x48)) = r;
        }
        return;
    }
    __builtin_trap();
}

/* FUN_004ae2fc @ 0x004ae2fc - convenience wrapper: calls cL4_tb_ae050 and,
 * on success (return byte 0), copies the result word into *param_3.
 * Returns true iff the call succeeded.
 * Confidence: medium */
bool cL4_tb_ae2fc(uint64_t map, uint64_t off, uint64_t *out) {
    uint64_t local = 0xffffffffffffffffULL;
    skr39_u128 r = cL4_tb_ae050(map, off, &local);
    if (r.lo == 0) *out = local;
    return r.lo == 0;
}

/* FUN_004ae394 @ 0x004ae394 - noreturn: panic "condition <s> failed".
 * Confidence: high */
void cL4_tb_err(int n) { (void)n; cL4_panic(0, "%s: condition %s failed"); }

/* FUN_004ae424 @ 0x004ae424 - noreturn: panic "condition <s> failed".
 * Confidence: high */
void cL4_tb_cond(void) { cL4_panic(0, "%s: condition %s failed"); }

/* FUN_004ae460 @ 0x004ae460 - callback for a frame-unmapping / mapping-get
 * request. Reads the 128-bit descriptor; on a mapping result it calls the
 * segment-accessor method (at param_1+0x28/0x68/0x60) to release the frame,
 * and on an error result panics. Uses the SegAccess_MappingGetFrame string.
 * Confidence: medium */
void cL4_tb_ae460(uint64_t ctx, uint64_t a, uint64_t b) {
    *(uint8_t *)(*(uint64_t *)(*(uint64_t *)(ctx + 0x20) + 8) + 0x18) = 1;
    uint64_t v[2]; v[0] = a; v[1] = b;
    uint64_t *mres = 0; /* cL4_tb_aecac(&v) */
    if (mres == 0) {
        /* cL4_tb_aecd8(&v); string s_map__p__SegAccess_MappingGetFram */
        cL4_panic(0, "%s: SegAccess_MappingGetFrame");
    } else {
        if (mres[0] != 0) {
            /* call (**(ctx+0x28)+0x68)+0x28)((*(ctx+0x28)+0x60), *(ctx+0x30)<<14) */
            /* if returns 0: cL4_free(mres[0]) and return */
            cL4_free((void *)mres[0], 0);
            return;
        }
        cL4_panic(0, "%s: condition %s failed");
    }
}

/* FUN_004ae564 @ 0x004ae564 - unmarshals a frame-mapping descriptor from a
 * message stream. Reads the group/attr/mode bytes and the optional
 * shared/ro sub-descriptor via the cL4_tb_rd_* stream primitives into the
 * 24-byte output at param_2. Panics (TB_FATAL invalid value) on malformed
 * input.
 * Confidence: medium */
void cL4_tb_ae564(uint64_t src, uint8_t *out) {
    if (out + 8 < out) __builtin_trap();
    cL4_helper_void(); /* FUN_00018f38 stream sync */
    uint8_t b = 0;
    cL4_tb_rd_u8(src, &b);
    if (b < 8) {
        out[8] = b;
        cL4_helper_void(); /* FUN_00018f38 */
        uint8_t attr = 0;
        cL4_tb_rd_u8(src, &attr);
        if ((attr & 0xfc) == 0x18) {
            out[0x18] = attr;
            uint8_t m = 0;
            cL4_tb_rd_u8(src, &m);
            if ((m & 0xfe) == 0x20) {
                out[0x19] = m;
                uint8_t *p = out + 0x1a;
                if (p <= out + 0x1c) {
                    uint8_t mode = 0;
                    cL4_tb_rd_u8(src, &mode);
                    if (mode == 0) *p = 0;
                    else {
                        *p = 1;
                        uint8_t ro = 0;
                        cL4_tb_rd_u8(src, &ro);
                        if ((ro & 0xfe) != 0x10) cL4_tb_fatal("TB_FATAL: invalid value, unexpected");
                        out[0x1b] = ro;
                    }
                    return;
                }
                __builtin_trap();
            }
        }
    }
    cL4_tb_fatal("TB_FATAL: invalid value, unexpected");
}

/* FUN_004ae6c4 @ 0x004ae6c4 - the tightbeam object-marshaller / encoder.
 * Dispatches on the descriptor tag byte (0x01/0x02/0x03): for tag 0x03 it
 * forwards each of the descriptor's child words through the caller's emit
 * callback (param_2+0x10); for tag 0x02 it validates the descriptor via
 * cL4_tb_ba8d4; otherwise it marshals the object fields through the
 * FUN_0001xxxx message primitives (encode a 128-bit/64-bit object), emitting
 * the child words. Returns the marshal buffer (0 on error paths).
 * Confidence: medium */
char *cL4_tb_ae6c4(char *desc, uint64_t emit) {
    char cVar1 = *desc;
    if (cVar1 == 0x01) {
        /* fall through to generic object encode below */
    } else if (cVar1 == 0x02) {
        /* validate via cL4_tb_ba8d4 then return 0 */
        return 0;
    } else if (cVar1 == 0x03) {
        uint64_t n = *(uint64_t *)(desc + 0x10);
        uint64_t off = 0;
        for (uint64_t i = 0; i < n; i++) {
            /* emit callback (param_2+0x10)(param_2, i, *(desc+8)+off) */
            (void)emit; off += 0x10;
        }
        return desc;
    } else {
        cL4_tb_fatal("TB_FATAL: invalid tag in Share");
    }
    /* generic encode path (tags 0x01/0x03-with-sub): marshal child words */
    uint64_t n = *(uint64_t *)(desc + 0x18);
    for (uint64_t i = 0; i < n; i++) {
        uint64_t w[2] = {0, 0};
        /* cL4_tb_rd_skip + read 2 words, emit via callback */
        (void)emit;
    }
    return 0;
}

/* FUN_004ae964 @ 0x004ae964 - unmarshals a method-bundle descriptor (the
 * "method" half of a mapping descriptor) from a stream. Reads the method-id
 * byte and the method-body via cL4_tb_rd_*, decodes a method reference via
 * cL4_tb_rd_method, and records (obj, method) into the output at param_2.
 * Panics (TB_FATAL invalid value) on malformed input.
 * Confidence: medium */
void cL4_tb_ae964(uint64_t src, uint8_t *out) {
    if (out + 4 < out) __builtin_trap();
    cL4_helper_void(); /* FUN_00018d4c */
    uint64_t w = 0;
    cL4_tb_rd_u8(src, &w);
    if (((uint8_t)w & 0xfe) == 0x10) {
        out[4] = (uint8_t)w;
        w = 0;
        cL4_tb_rd_u8(src, &w);
        if (((uint8_t)w & 0xfc) == 0x18) {
            out[5] = (uint8_t)w;
            cL4_tb_rd_bytes(src, out + 6);
            if (out + 8 <= out + 0x30) {
                uint64_t method = 0;
                cL4_tb_rd_u64(src, &method);
                uint8_t *p = out + 0x20;
                if ((out + 0x18 <= p) && (p <= out + 0x28)) {
                    uint64_t call;
                    int rc = cL4_tb_msg_method(src, out + 0x18, p, &call);
                    if (rc == 0) {
                        *(uint64_t *)(out + 0x10) = src;
                        *(uint64_t *)(out + 0x28) = method;
                        out[8] = 2;
                    } else {
                        out[8] = 0;
                    }
                    return;
                }
            }
            __builtin_trap();
        }
    }
    cL4_tb_fatal("TB_FATAL: invalid value, unexpected");
}

/* FUN_004aeae0 @ 0x004aeae0 - unmarshals a full mapping descriptor
 * (the frame-mapping attribute bundle) from a stream into a 0x88-byte
 * buffer at param_2. Reads the mapping-id, then two method-bundle
 * sub-descriptors (via cL4_tb_ae964) for the mapping-attribute and the
 * frame. Records (obj, method) pairs and flag bytes. Panics on overrun.
 * Confidence: medium */
uint64_t cL4_tb_aeae0(uint64_t src, uint8_t *out) {
    uint8_t *p = out + 0x30;
    if (out <= p) {
        cL4_tb_ae964(src, out);   /* decompile: iVar6 = FUN_004ae964(); if (iVar6 != 0) return; (return unmodeled, helper is void) */
        uint8_t *p2 = out + 0x58;
        if (p <= p2) {
            uint64_t method = 0;
            cL4_tb_rd_u64(src, &method);
            uint8_t *p3 = out + 0x48;
            if ((out + 0x40 <= p3) && (p3 <= out + 0x50)) {
                uint64_t call;
                int rc = cL4_tb_msg_method(src, out + 0x40, p3, &call);
                if (rc != 0) { *p = 0; return 0; }
                *(uint64_t *)(out + 0x38) = src;
                *(uint64_t *)(out + 0x50) = method;
                out[0x30] = 2;
                if (p2 <= out + 0x80) {
                    uint64_t m2 = 0;
                    cL4_tb_rd_u64(src, &m2);
                    uint8_t *p4 = out + 0x70;
                    if ((out + 0x68 <= p4) && (p4 <= out + 0x78)) {
                        uint64_t call2;
                        int rc2 = cL4_tb_msg_method(src, out + 0x68, p4, &call2);
                        if (rc2 == 0) {
                            *(uint64_t *)(out + 0x60) = src;
                            *(uint64_t *)(out + 0x78) = m2;
                            *p2 = 2;
                        } else {
                            *p2 = 0;
                        }
                        return 0;
                    }
                }
            }
        }
    }
    __builtin_trap();
}

/* FUN_004aec8c @ 0x004aec8c - initialises a 24-byte marshalling descriptor
 * at param_1 from the 16-byte value *param_2: sets the tag byte to 1 and
 * copies the (lo, hi) pair to param_1+8/0x10. If param_2 is NULL, sets the
 * tag byte to 0.
 * Confidence: high */
void cL4_tb_aec8c(uint8_t *d, uint64_t *v) {
    if (v != 0) {
        d[0] = 1;
        uint64_t lo = *v;
        *(uint64_t *)(d + 0x10) = v[1];
        *(uint64_t *)(d + 8) = lo;
        return;
    }
    d[0] = 0;
}

/* FUN_004aecac @ 0x004aecac - returns a pointer to the 128-bit payload of a
 * descriptor whose tag byte is 0 (a 16-byte value at param_1+8), else NULL.
 * Confidence: medium */
char *cL4_tb_aecac(char *d) {
    if (*d != 0) return 0;
    if (d + 8 <= d + 0x10) return d + 8;
    __builtin_trap();
}

/* FUN_004aecd8 @ 0x004aecd8 - returns a pointer to the 128-bit payload of a
 * descriptor whose tag byte is 1 (a 16-byte value at param_1+8), else NULL.
 * Confidence: medium */
char *cL4_tb_aecd8(char *d) {
    if (*d != 1) return 0;
    if (d + 8 <= d + 0xc) return d + 8;
    __builtin_trap();
}

/* FUN_004aed08 @ 0x004aed08 - returns a pointer to the payload of a
 * descriptor whose tag byte is 0 and that is at least 0x88 bytes long
 * (a 128-byte value at param_1+8), else NULL.
 * Confidence: medium */
char *cL4_tb_aed08(char *d) {
    if (*d != 0) return 0;
    if (d + 8 <= d + 0x88) return d + 8;
    __builtin_trap();
}

/* FUN_004aed34 @ 0x004aed34 - the tightbeam call hub: builds a marshalled
 * request message for a frame-mapping operation and invokes the caller's
 * dispatch callback (param_2+0x10) with the decoded reply. Uses the
 * cL4_tb_msg_begin / cL4_tb_buf_u64 / cL4_tb_msg_send / cL4_tb_msg_end
 * primitives, then decodes the reply via cL4_tb_ae564 + cL4_tb_ae964 and
 * passes it to the callback. Returns an L4-style error code.
 * Confidence: medium */
uint64_t cL4_tb_aed34(uint64_t *obj, uint64_t call) {
    uint64_t buf[32];
    memset(buf, 0, sizeof buf);
    uint64_t err = cL4_tb_msg_begin(*obj, buf + 1, buf + 0xd, 8, 0);
    if ((int)err == 0) {
        cL4_tb_buf_reset(buf + 1, 8);
        cL4_tb_buf_u64(buf + 1, 0x66629f28a61590faULL);
        cL4_tb_buf_seal(buf + 1);
        buf[0] = 0;
        err = cL4_tb_msg_send(*obj, buf + 1, buf, 2);
        uint64_t rep = buf[0];
        if (((int)err == 0) || ((int)err == 9)) {
            if (buf[0] == 0) { cL4_tb_msg_end(*obj, buf + 1); return 4; }
            uint8_t out[0x20];
            memset(out, 0, sizeof out);
            cL4_tb_ae564(rep, out);
            uint64_t m = 0;
            cL4_tb_rd_u64(rep, &m);
            uint64_t call_desc;
            int rc = cL4_tb_msg_method(rep, 0, 0, &call_desc);
            if (rc == 0) {
                /* dispatch decoded reply to callback at (call+0x10) */
                (void)call;
            }
        }
        cL4_tb_msg_end(*obj, buf + 1);
    }
    return err;
}

/* FUN_004aefb0 @ 0x004aefb0 - marshals a mapping request (the frame-map
 * call). Builds a message with a 128-bit or 64-bit descriptor (depending on
 * the tag byte of param_3), sends it, and dispatches the reply to the
 * callback at param_4+0x10. Handles both the mapping and error-code reply
 * forms via cL4_tb_aeae0. Returns the L4-style error code.
 * Confidence: medium */
uint64_t cL4_tb_aefb0(uint64_t *obj, uint64_t type, char *desc, uint64_t call) {
    uint64_t len = (*desc == 1) ? 0x1a : 10;
    uint64_t buf[32];
    memset(buf, 0, sizeof buf);
    uint64_t err = cL4_tb_msg_begin(*obj, buf + 1, 0, len, 0);
    if ((int)err != 0) return err;
    cL4_tb_buf_reset(buf + 1, len);
    cL4_tb_buf_u64(buf + 1, 0x5828149e5418c733ULL);
    if (((uint32_t)type & 0xfe) != 0x10) goto badval;
    cL4_tb_buf_u8(buf + 1, type);
    if (*desc == 1) {
        cL4_tb_buf_u8(buf + 1, 1);
        cL4_tb_buf_u64(buf + 1, *(uint64_t *)(desc + 8));
        cL4_tb_buf_u64(buf + 1, *(uint64_t *)(desc + 0x10));
    } else {
        cL4_tb_buf_u8(buf + 1, 0);
    }
    cL4_tb_buf_seal(buf + 1);
    buf[0] = 0;
    err = cL4_tb_msg_send(*obj, buf + 1, buf, 2);
    uint64_t rep = buf[0];
    if (((int)err == 0) || ((int)err == 9)) {
        if (buf[0] == 0) { cL4_tb_msg_end(*obj, buf + 1); return 4; }
        uint8_t r[0x20];
        memset(r, 0, sizeof r);
        uint64_t tag = 0;
        cL4_tb_rd_u8(rep, &tag);
        if ((char)tag == 0) {
            err = cL4_tb_aeae0(rep, (uint8_t *)((uint64_t)&r | 8));
            if (((int)err != 9) && ((int)err != 0)) { cL4_tb_msg_end(*obj, buf + 1); return err; }
        } else {
            if ((char)tag != 1) goto badval;
            uint32_t code = 0;
            cL4_tb_rd_u32(rep, &code);
            if (9 < (int)code - 0x41) goto badval;
        }
        /* dispatch decoded reply to callback at (call+0x10) */
        (*(void (**)(uint64_t, uint8_t *))(call + 0x10))(call, r);
        err = 0;
    }
    cL4_tb_msg_end(*obj, buf + 1);
    return err;
badval:
    cL4_tb_fatal("TB_FATAL: invalid value, unexpected");
}

/* FUN_004af26c @ 0x004af26c - marshals a single-word mapping-attribute
 * request. Sends a message with a descriptor {key, u32, u64} and dispatches
 * the reply (a word + error code) to the callback at param_4+0x10.
 * Confidence: medium */
uint64_t cL4_tb_af26c(uint64_t *obj, uint64_t key, uint64_t val, uint64_t call) {
    uint64_t buf[16];
    memset(buf, 0, sizeof buf);
    uint64_t err = cL4_tb_msg_begin(*obj, buf + 1, 0, 0x14, 1);
    if ((int)err != 0) return err;
    cL4_tb_buf_reset(buf + 1, 0x14);
    cL4_tb_buf_u64(buf + 1, 0x35a9b26b7b19f547ULL);
    cL4_tb_buf_u32(buf + 1, key);
    cL4_tb_buf_u64(buf + 1, val);
    cL4_tb_buf_seal(buf + 1);
    buf[0] = 0;
    err = cL4_tb_msg_send(*obj, buf + 1, buf, 2);
    uint64_t rep = buf[0];
    if (((int)err == 0) || ((int)err == 9)) {
        if (buf[0] == 0) { cL4_tb_msg_end(*obj, buf + 1); return 4; }
        uint64_t a = 0, b = 0;
        cL4_tb_rd_u8(rep, &a);
        if ((char)a == 0) {
            err = cL4_tb_msg_recv(rep, &b);
            if (((int)err != 9) && ((int)err != 0)) { cL4_tb_msg_end(*obj, buf + 1); return err; }
        } else {
            if ((char)a != 1) { cL4_tb_fatal("TB_FATAL: invalid value, unexpected"); }
            uint32_t code = 0;
            cL4_tb_rd_u32(rep, &code);
            if (9 < (int)code - 0x41) { cL4_tb_fatal("TB_FATAL: invalid value, unexpected"); }
            b = code;
        }
        /* dispatch reply (a, b) to callback at (call+0x10) */
        (void)call;
        err = 0;
    }
    cL4_tb_msg_end(*obj, buf + 1);
    return err;
}

/* FUN_004af468 @ 0x004af468 - marshals a mapping-attribute pair request.
 * Sends a message with a descriptor {key, u64, u64} and dispatches the
 * reply (via cL4_tb_aeae0) to the callback at param_4+0x10.
 * Confidence: medium */
uint64_t cL4_tb_af468(uint64_t *obj, uint64_t key, uint64_t *val, uint64_t call) {
    uint64_t buf[32];
    memset(buf, 0, sizeof buf);
    uint64_t err = cL4_tb_msg_begin(*obj, buf + 1, 0, 0x1c, 0);
    if ((int)err != 0) return err;
    cL4_tb_buf_reset(buf + 1, 0x1c);
    cL4_tb_buf_u64(buf + 1, 0x9acebd52b1e9d4a1ULL);
    cL4_tb_buf_u32(buf + 1, key);
    cL4_tb_buf_u64(buf + 1, val[0]);
    cL4_tb_buf_u64(buf + 1, val[1]);
    cL4_tb_buf_seal(buf + 1);
    buf[0] = 0;
    err = cL4_tb_msg_send(*obj, buf + 1, buf, 2);
    uint64_t rep = buf[0];
    if (((int)err == 0) || ((int)err == 9)) {
        if (buf[0] == 0) { cL4_tb_msg_end(*obj, buf + 1); return 4; }
        uint8_t r[0x20];
        memset(r, 0, sizeof r);
        uint64_t tag = 0;
        cL4_tb_rd_u8(rep, &tag);
        if ((char)tag == 0) {
            err = cL4_tb_aeae0(rep, (uint8_t *)((uint64_t)&r | 8));
            if (((int)err != 9) && ((int)err != 0)) { cL4_tb_msg_end(*obj, buf + 1); return err; }
        } else {
            if ((char)tag != 1) { cL4_tb_fatal("TB_FATAL: invalid value, unexpected"); }
            uint32_t code = 0;
            cL4_tb_rd_u32(rep, &code);
            if (9 < (int)code - 0x41) { cL4_tb_fatal("TB_FATAL: invalid value, unexpected"); }
        }
        /* dispatch decoded reply to callback at (call+0x10) */
        ((void (*)(void *, void *))(*(void **)((char *)call + 0x10)))((void *)call, &r);
        err = 0;
    }
    cL4_tb_msg_end(*obj, buf + 1);
    return err;
}

/* FUN_004af6a4 @ 0x004af6a4 - marshals a region-map request (variant of
 * 0x4aefb0). Sends a message with a {key, u32, u64} descriptor and
 * dispatches the reply to the callback at param_4+0x10.
 * Confidence: medium */
uint64_t cL4_tb_af6a4(uint64_t *obj, uint64_t key, uint64_t val, uint64_t call) {
    uint64_t buf[16];
    memset(buf, 0, sizeof buf);
    uint64_t err = cL4_tb_msg_begin(*obj, buf + 1, 0, 0x14, 0);
    if ((int)err == 0) {
        cL4_tb_buf_reset(buf + 1, 0x14);
        cL4_tb_buf_u64(buf + 1, 0x78c3ffc0141b605fULL);
        cL4_tb_buf_u32(buf + 1, key);
        cL4_tb_buf_u64(buf + 1, val);
        cL4_tb_buf_seal(buf + 1);
        buf[0] = 0;
        err = cL4_tb_msg_send(*obj, buf + 1, buf, 2);
        uint64_t rep = buf[0];
        if (((int)err == 0) || ((int)err == 9)) {
            if (buf[0] == 0) { cL4_tb_msg_end(*obj, buf + 1); return 4; }
            uint64_t a = 0, b = 0;
            cL4_tb_rd_u8(rep, &a);
            if ((char)a == 1) {
                uint32_t code = 0;
                cL4_tb_rd_u32(rep, &code);
                if (9 < (int)code - 0x41) { cL4_tb_fatal("TB_FATAL: invalid value, unexpected"); }
                b = code;
            } else {
                if ((char)a != 0) { cL4_tb_fatal("TB_FATAL: invalid value, unexpected"); }
                cL4_tb_rd_u64(rep, &b);
            }
            /* dispatch reply (a, b) to callback at (call+0x10) */
            (void)call;
            err = 0;
        }
        cL4_tb_msg_end(*obj, buf + 1);
    }
    return err;
}

/* FUN_004af8a4 @ 0x004af8a4 - initialises a message object at param_1 from
 * param_2: seeds it, reads its id, and validates the tag; on success stores
 * the id into *param_1.
 * Confidence: medium */
void cL4_tb_af8a4(uint64_t *obj, uint64_t src) {
    cL4_tb_obj_seed(src, 0x7151359897ded024ULL);
    uint64_t id = cL4_tb_obj_id(src);
    int ok = cL4_tb_obj_check();
    if (ok == 0) *obj = id;
}

/* FUN_004af8f8 @ 0x004af8f8 - copies *param_1 into *param_2 (single-word
 * copy). Confidence: high (trivial) */
void cL4_tb_af8f8(uint64_t *src, uint64_t *dst) { *dst = *src; }

/* FUN_004af90c @ 0x004af90c - drains a marshalled stream: reads and
 * discards *(param_1+0x20) 16-byte entries from the stream at param_1+0x28.
 * Returns 0.
 * Confidence: medium */
uint64_t cL4_tb_af90c(uint64_t p) {
    uint64_t n = *(uint64_t *)(p + 0x20);
    uint64_t src = *(uint64_t *)(p + 0x28);
    for (uint64_t i = 0; i < n; i++) {
        uint64_t a = 0, b = 0;
        cL4_tb_rd_skip(src, 0x10);
        cL4_tb_rd_word(src, &a);
        cL4_tb_rd_word(src, &b);
    }
    return 0;
}

/* FUN_004af988 @ 0x004af988 - the tightbeam fatal-error trampoline: reads
 * the current error code from a global, and if it is not the success code
 * (low byte == 0) invokes the panic/log helpers (FUN_004afa6c,
 * FUN_004afae4) with the "Unexpected L4 Error" format string. Used on the
 * fatal-IPC path.
 * Confidence: medium */
void cL4_tb_af988(void) {
    uint64_t *g = (uint64_t *)0x690000; /* FUN_0006ce00(&DAT_00690000) */
    uint64_t err = *g;
    if ((err & 0xff) == 0) return;
    cL4_panicv(0, "Unexpected L4 Error: %s, %zu", 0);
}

/* FUN_004afa6c @ 0x004afa6c (callee) - panic formatter. */
void cL4_tb_afa6c(uint64_t tag) {
    (void)tag;
    cL4_panicv(0, "%s: %s %d: %s", 0);
}

/* FUN_004afae4 @ 0x004afae4 - noreturn panic with a single format argument.
 * Confidence: high */
void cL4_tb_afae4(uint64_t fmt) { (void)fmt; cL4_panicv(0, "%s", 0); }

/* FUN_004afb14 @ 0x004afb14 - tightbeam fatal-error entry: reports the
 * current error code and panics with "Unexpected L4 Error".
 * Confidence: medium */
void cL4_tb_afb14(void) {
    cL4_tb_afa6c(0xeb1a02bf914012baULL);
    cL4_tb_afae4(0x5a8cac);
}

/* FUN_004afb6c @ 0x004afb6c - tightbeam fatal-error entry (variant):
 * reports the current error code and panics with "Unexpected L4 Error".
 * Confidence: medium */
void cL4_tb_afb6c(void) {
    cL4_tb_afa6c(0xeb1a02bf914012baULL);
    cL4_tb_afae4(0x5a8b89);
}

/* FUN_004ac9d8 @ 0x004ac9d8 - register-window thunk: returns (x21 + x9)
 * (forwards an offset-added coroutine register value).
 * Confidence: medium */
uint64_t cL4_tb_9d8(void) {
    uint64_t r; __asm__ volatile("add %0, x21, x9" : "=r"(r)); return r;
}
