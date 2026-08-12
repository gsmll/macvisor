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
extern void cL4_panic(int unused, const char *fmt, ...);
extern void cL4_panicv(int unused, const char *fmt, void *ap);
extern void cL4_free(void *ptr, uint64_t n);

/* FUN_00118b28 - noreturn "TB_FATAL: invalid value" diagnostic printer. */
extern void cL4_tb_fatal(const char *fmt, ...);
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
