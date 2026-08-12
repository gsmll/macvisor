/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 *
 * SK185 slice (0x00405b0c-0x00406e18): a cluster of the Swift `_Concurrency`
 * module (AsyncStream / AsyncThrowingStream machinery). Ground-truth strings
 * that anchor the region:
 *   0x005ce250 "Assertion failed", 0x005ce2d0 "Precondition failed",
 *   0x005accd0 "Fatal error",
 *   0x005dc1d0 "_Concurrency/AsyncStream.swift",       (line 0x1e = 30)
 *   0x005dbfb0 "_Concurrency/SourceCompatibility.swift", (line 0x2b = 43)
 *   0x005dc1f0 "_Concurrency/AsyncThrowingStream.swift", (line 0x26 = 38)
 *   metadata descriptors DAT_005a1500 / DAT_005a151c / DAT_004edd94.
 *
 * The region is almost entirely tiny Swift witness/thunk code:
 *   - no-op stubs and thin wrappers over shared `_Concurrency` helpers,
 *   - closure-context constructors that build a two-word result and stamp a
 *     partial-apply thunk pointer into out+8,
 *   - `{ptr,len}` Swift String-literal builders for the standard runtime
 *     failure messages, and
 *   - noreturn fatal-error thunks (FUN_001afa84) that point at AsyncStream /
 *     AsyncThrowingStream / SourceCompatibility sources.
 *
 * Swift ABI: the caller preserves a class/closure context ("self") in the
 * callee-saved register x20/x22; field reads/writes are against that
 * register. Here the register context is rendered as a leading `self`
 * parameter and the offsets are byte offsets into it. Functions that write a
 * partial-apply thunk address into out+8 (in_x16 or a LAB_/FUN_ label)
 * receive that address as an explicit parameter. Confidence is medium where
 * a _Concurrency string anchors the identity, otherwise low.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;

/* Two-word Swift ABI return (values returned in x0/x1). */
typedef struct { word_t lo; word_t hi; } sk185_pair_t;

/* Swift String literal `{pointer, length}` (also a two-word return). */
typedef struct { const char *ptr; word_t len; } sk185_str_t;

/* Field access at a byte offset into the register-preserved context. */
#define SK185_FIELD(self, off) (*(word_t *)((uint8_t *)(self) + (off)))

#define SK185_TRAP() __builtin_trap()   /* SoftwareBreakpoint(1,<addr>) path */

/* ------------------------------------------------------------------ *
 * Shared `_Concurrency` / Swift-runtime externs (ground truth FUN_
 * addresses). Variadic because the Swift ABI tail-merges arguments into
 * preserved registers that Ghidra renders with varying arity; bodies call
 * them with the counts shown in each decompile.
 * ------------------------------------------------------------------ */

extern word_t sk_swift_release(word_t, ...);                 /* FUN_0036b118 */
extern word_t sk_swift_retain(word_t, ...);                  /* FUN_0036b270 */
extern word_t sk_str_convert(word_t, ...);                   /* FUN_00377824 */
extern word_t sk_str_convert2(word_t, ...);                  /* FUN_00377bec */
extern word_t sk_desc_deref_release(word_t, ...);            /* FUN_00377dcc */
extern word_t sk_vt_dispatch38(word_t, ...);                 /* FUN_000839d8 */
extern word_t sk_vt_dispatch30(word_t, ...);                 /* FUN_000839f8 */
extern word_t sk_collection_initialize_buffer(word_t, ...);  /* FUN_00235488 */
extern word_t sk_swift_collection_count(word_t, ...);        /* FUN_0025177c */
extern word_t sk_syscall_args_1_2(word_t, ...);              /* FUN_003513b4 */
extern word_t sk_exclave_extent_c(word_t, ...);              /* FUN_000a649c */
extern word_t sk_cL4_noop_7(word_t, ...);                    /* FUN_000a6e14 */
extern void   sk_assert_fatal(word_t, ...) __attribute__((noreturn)); /* FUN_001afa84 */
extern void   sk_boot_fatal(void) __attribute__((noreturn)); /* FUN_0011d7e8 */

/* Region-local `_Concurrency` helpers (bodies reconstructed by other
 * workers / not part of this slice). FUN_ address is ground truth. */
extern word_t sk185_helper_3fa478(word_t, ...);   /* FUN_003fa478 */
extern word_t sk185_helper_3fa168(word_t, ...);   /* FUN_003fa168 */
extern word_t sk185_helper_3f9e34(word_t, ...);   /* FUN_003f9e34 */
extern word_t sk185_helper_3f9f4c(word_t, ...);   /* FUN_003f9f4c */
extern word_t sk185_helper_3f6668(word_t, ...);   /* FUN_003f6668 */
extern word_t sk185_helper_3f9cec(word_t, ...);   /* FUN_003f9cec */
extern word_t sk185_helper_3f7d48(word_t, ...);   /* FUN_003f7d48 */
extern word_t sk185_helper_3f4210(word_t, ...);   /* FUN_003f4210 */
extern word_t sk185_helper_3f5c00(word_t, ...);   /* FUN_003f5c00 */
extern word_t sk185_helper_3f6560(word_t, ...);   /* FUN_003f6560 */
extern word_t sk185_helper_3f6174(word_t, ...);   /* FUN_003f6174 */
extern word_t sk185_helper_3504d0(word_t, ...);   /* FUN_003504d0 */
extern word_t sk185_helper_350500(word_t, ...);   /* FUN_00350500 */
extern word_t sk185_helper_35050c(word_t, ...);   /* FUN_0035050c */
extern word_t sk185_helper_350bfc(word_t, ...);   /* FUN_00350bfc */
extern word_t sk185_helper_35860c(word_t, ...);   /* FUN_0035860c */
extern word_t sk185_helper_3d4658(word_t, ...);   /* FUN_003d4658 */
extern word_t sk185_helper_3ef9b0(word_t, ...);   /* FUN_003ef9b0 */
extern word_t sk185_helper_3fcc1c(word_t, ...);   /* FUN_003fcc1c */
extern word_t sk185_helper_3fc2c0(word_t, ...);   /* FUN_003fc2c0 */
extern word_t sk185_helper_3fbcd4(word_t, ...);   /* FUN_003fbcd4 */
extern word_t sk185_helper_404c60(word_t, ...);   /* FUN_00404c60 */
extern word_t sk185_helper_404d84(word_t, ...);   /* FUN_00404d84 */
extern word_t sk185_helper_405830(word_t, ...);   /* FUN_00405830 */
extern word_t sk185_helper_4070cc(word_t, ...);   /* FUN_004070cc */
extern word_t sk185_helper_407f18(word_t, ...);   /* FUN_00407f18 */
extern word_t sk185_helper_407f24(word_t, ...);   /* FUN_00407f24 */
extern word_t sk185_helper_408238(word_t, ...);   /* FUN_00408238 */
extern word_t sk185_helper_4082d4(word_t, ...);   /* FUN_004082d4 */
extern word_t sk185_helper_408db8(word_t, ...);   /* FUN_00408db8 */
extern word_t sk185_helper_40bd24(word_t, ...);   /* FUN_0040bd24 */
extern word_t sk185_helper_3fc9d0(word_t, ...);   /* FUN_003fc9d0 */

/* ------------------------------------------------------------------ *
 * Dispatch thunks: forward (arg1,arg2, context fields, ...) into a shared
 * `_Concurrency` helper. Context fields are byte offsets into self.
 * ------------------------------------------------------------------ */

/* FUN_00405b0c @ 0x00405b0c   (est. sk185_dispatch_3fa478)
 * Ghidra: void FUN_00405b0c(undefined8, undefined8)
 * Forwards (param_1,param_2) plus self fields 0x28,0x30,0x38,0x10,0x18,0x20
 * into the shared helper FUN_003fa478. No side effects beyond the call.
 * Confidence: low (thin `_Concurrency` dispatch thunk). */
void sk185_dispatch_3fa478(word_t *self, word_t param_1, word_t param_2)
{
    sk185_helper_3fa478(param_1, param_2, SK185_FIELD(self, 0x28),
                        SK185_FIELD(self, 0x30), SK185_FIELD(self, 0x38),
                        SK185_FIELD(self, 0x10), SK185_FIELD(self, 0x18),
                        SK185_FIELD(self, 0x20));
}

/* FUN_00405b40 @ 0x00405b40   (est. sk185_dispatch_3fa168)
 * Ghidra: void FUN_00405b40(undefined8, undefined8)
 * Forwards (param_1,param_2) plus self fields 0x18,0x20,0x28,0x10 into
 * FUN_003fa168. Confidence: low (thin `_Concurrency` dispatch thunk). */
void sk185_dispatch_3fa168(word_t *self, word_t param_1, word_t param_2)
{
    sk185_helper_3fa168(param_1, param_2, SK185_FIELD(self, 0x18),
                        SK185_FIELD(self, 0x20), SK185_FIELD(self, 0x28),
                        SK185_FIELD(self, 0x10));
}

/* FUN_00405b70 @ 0x00405b70   (est. sk185_dispatch_3f9e34)
 * Ghidra: void FUN_00405b70(undefined8, undefined8)
 * Forwards (param_1,param_2) plus self fields 0x28,0x10,0x18,0x20 into
 * FUN_003f9e34. Confidence: low (thin `_Concurrency` dispatch thunk). */
void sk185_dispatch_3f9e34(word_t *self, word_t param_1, word_t param_2)
{
    sk185_helper_3f9e34(param_1, param_2, SK185_FIELD(self, 0x28),
                        SK185_FIELD(self, 0x10), SK185_FIELD(self, 0x18),
                        SK185_FIELD(self, 0x20));
}

/* FUN_00405b74 @ 0x00405b74   (est. sk185_dispatch_3f9e34_b)
 * Ghidra: void FUN_00405b74(undefined8, undefined8)
 * Identical body to FUN_00405b70 (duplicate witness thunk): forwards
 * (param_1,param_2) plus self fields 0x28,0x10,0x18,0x20 into FUN_003f9e34.
 * Confidence: low. */
void sk185_dispatch_3f9e34_b(word_t *self, word_t param_1, word_t param_2)
{
    sk185_helper_3f9e34(param_1, param_2, SK185_FIELD(self, 0x28),
                        SK185_FIELD(self, 0x10), SK185_FIELD(self, 0x18),
                        SK185_FIELD(self, 0x20));
}

/* FUN_00405b90 @ 0x00405b90   (est. sk185_dispatch_3f9f4c)
 * Ghidra: void FUN_00405b90(undefined8, undefined8)
 * Forwards (param_1,param_2) plus self fields 0x28,0x10,0x18,0x20 into
 * FUN_003f9f4c. Confidence: low (thin `_Concurrency` dispatch thunk). */
void sk185_dispatch_3f9f4c(word_t *self, word_t param_1, word_t param_2)
{
    sk185_helper_3f9f4c(param_1, param_2, SK185_FIELD(self, 0x28),
                        SK185_FIELD(self, 0x10), SK185_FIELD(self, 0x18),
                        SK185_FIELD(self, 0x20));
}

/* FUN_00405bc0 @ 0x00405bc0   (est. sk185_bc0_bump)
 * Ghidra: void FUN_00405bc0(long)
 * Complex init/iteration step: runs a sequence of `_Concurrency` helpers
 * (FUN_00350bfc/FUN_003f6560/FUN_003513b4/FUN_003f6174/FUN_0035050c/
 * FUN_00405830/FUN_00407f24), builds a demangled witness string via
 * FUN_00377824/FUN_000a6e14/FUN_00377bec against descriptor DAT_00611b24,
 * then adds FUN_003f4210()'s result to param_1+8, trapping (SoftwareBreakpoint
 * 1, 0x405ca0) on signed-carry overflow of the add.
 * Confidence: medium (_Concurrency string/descriptor refs). */
void sk185_bc0_bump(uint8_t *self, word_t param_1)
{
    word_t u1 = SK185_FIELD(self, 0x18);
    word_t u3 = SK185_FIELD(self, 0x20);
    word_t u5 = SK185_FIELD(self, 0x30);

    sk185_helper_350bfc(SK185_FIELD(self, 0x28), param_1);
    sk185_helper_3f6560();
    sk_syscall_args_1_2((void *)0, param_1);   /* FUN_003513b4, local buffer elided */
    sk185_helper_3f6174();
    sk185_helper_35050c();
    sk185_helper_405830();
    sk185_helper_407f24();
    u3 = sk_str_convert(0, u3, u1, (word_t)0x611b24);   /* DAT_00611b24 descriptor */
    sk185_helper_407f18();
    u3 = sk_cL4_noop_7();                       /* FUN_000a6e14 (returns 16 bytes) */
    sk_str_convert2(u3, 0, u3, (word_t)0x611b24);   /* FUN_00377bec, DAT_00611b24 */
    sk_syscall_args_1_2((void *)0, u5);
    {
        long cur = *(long *)((uint8_t *)param_1 + 8);
        word_t addv = sk185_helper_3f4210();
        word_t sum = (word_t)cur + addv;
        if (sum >= (word_t)cur) {   /* !SCARRY8: no carry-out of the add */
            *(long *)((uint8_t *)param_1 + 8) = (long)sum;
            return;
        }
    }
    SK185_TRAP();   /* SoftwareBreakpoint(1,0x405ca0) — overflow, does not return */
}

/* FUN_00405ca0 @ 0x00405ca0   (est. sk185_dispatch_3f6668)
 * Ghidra: void FUN_00405ca0(undefined8, undefined8, undefined8, undefined8)
 * Forwards self fields 0x28,0x30 plus (param_3,param_4,param_1->0x10 field...)
 * into FUN_003f6668, after a no-op FUN_00408238(). Confidence: low. */
void sk185_dispatch_3f6668(word_t *self, word_t param_1, word_t param_2,
                           word_t param_3, word_t param_4)
{
    sk185_helper_408238();
    sk185_helper_3f6668(SK185_FIELD(self, 0x28), SK185_FIELD(self, 0x30),
                        param_3, param_4, SK185_FIELD(self, 0x10));
}

/* FUN_00405cd4 @ 0x00405cd4   (est. sk185_cd4_fill)
 * Ghidra: void FUN_00405cd4(long, undefined8)
 * If param_1+0x10 is zero, runs a bounded fill: when self+0x18 count is
 * positive, calls FUN_00350500/FUN_003f5c00/FUN_00235488 and records the
 * count at param_1+8. Otherwise raises the "Assertion failed" runtime
 * failure (FUN_001afa84). Confidence: medium (_Concurrency runtime-failure
 * path, FUN_00235488 = sk_collection_initialize_buffer). */
void sk185_cd4_fill(word_t *self, uint8_t *param_1, word_t param_2)
{
    if (*(long *)(param_1 + 0x10) == 0) {
        long count = (long)SK185_FIELD(self, 0x18);
        if (0 < count) {
            word_t v10 = SK185_FIELD(self, 0x10);
            word_t v20 = SK185_FIELD(self, 0x20);
            sk185_helper_350500((word_t)param_1, param_2, param_2);
            word_t got = sk185_helper_3f5c00();
            sk_collection_initialize_buffer(v20, count, got, v10);   /* FUN_00235488 */
        }
        *(long *)(param_1 + 8) = count;
        return;
    }
    sk185_helper_4070cc();
    sk185_str_assertion_failed_c();      /* FUN_004063f4 builds "Assertion failed" string */
    sk_assert_fatal();                   /* FUN_001afa84 — does not return */
}

/* FUN_00405d70 @ 0x00405d70   (est. sk185_d70_clear)
 * Ghidra: void FUN_00405d70(void)
 * Runs two shared helpers (FUN_0035860c/FUN_0025177c), zeroes self+8 and
 * self+0x10, then calls FUN_004082d4. Confidence: low. */
void sk185_d70_clear(uint8_t *self)
{
    sk185_helper_35860c();
    sk_swift_collection_count();         /* FUN_0025177c */
    SK185_FIELD(self, 8) = 0;
    SK185_FIELD(self, 0x10) = 0;
    sk185_helper_4082d4();
}

/* FUN_00405da8 @ 0x00405da8   (est. sk185_dispatch_3f9cec)
 * Ghidra: void FUN_00405da8(undefined8, undefined8)
 * Forwards (param_1,param_2) plus self fields 0x28,0x30,0x10,0x18,0x20 into
 * FUN_003f9cec. Confidence: low (thin `_Concurrency` dispatch thunk). */
void sk185_dispatch_3f9cec(word_t *self, word_t param_1, word_t param_2)
{
    sk185_helper_3f9cec(param_1, param_2, SK185_FIELD(self, 0x28),
                        SK185_FIELD(self, 0x30), SK185_FIELD(self, 0x10),
                        SK185_FIELD(self, 0x18), SK185_FIELD(self, 0x20));
}

/* FUN_00405dac @ 0x00405dac   (est. sk185_dispatch_3f9cec_b)
 * Ghidra: void FUN_00405dac(undefined8, undefined8)
 * Duplicate of FUN_00405da8 (witness clone): forwards (param_1,param_2) plus
 * self fields 0x28,0x30,0x10,0x18,0x20 into FUN_003f9cec. Confidence: low. */
void sk185_dispatch_3f9cec_b(word_t *self, word_t param_1, word_t param_2)
{
    sk185_helper_3f9cec(param_1, param_2, SK185_FIELD(self, 0x28),
                        SK185_FIELD(self, 0x30), SK185_FIELD(self, 0x10),
                        SK185_FIELD(self, 0x18), SK185_FIELD(self, 0x20));
}

/* FUN_00405dcc @ 0x00405dcc   (est. sk185_dispatch_3f7d48)
 * Ghidra: void FUN_00405dcc(undefined8, undefined8)
 * Forwards (param_1,param_2) plus self fields 0x28,0x30,0x10 into
 * FUN_003f7d48. Confidence: low (thin `_Concurrency` dispatch thunk). */
void sk185_dispatch_3f7d48(word_t *self, word_t param_1, word_t param_2)
{
    sk185_helper_3f7d48(param_1, param_2, SK185_FIELD(self, 0x28),
                        SK185_FIELD(self, 0x30), SK185_FIELD(self, 0x10));
}

/* FUN_00405dfc @ 0x00405dfc   (est. sk185_dfC_vcall)
 * Ghidra: void FUN_00405dfc(undefined8 *, ulong)
 * Indirect call through a method-table slot: if param_1 is non-null, loads
 * the vtable function pointer FUN_003d4658(param_2 & ~3) and calls it with
 * (param_1[0], param_2 & ~3). The &~3 masks the low tag bits of the method
 * pointer. Confidence: medium (Swift vtable dispatch pattern). */
void sk185_dfC_vcall(word_t *param_1, word_t param_2)
{
    if (param_1 != 0) {
        word_t slot = param_1[0];
        word_t masked = param_2 & 0xfffffffffffffffcULL;
        ((void (*)(word_t, word_t))(sk185_helper_3d4658(masked)))(slot, masked);
    }
}

/* FUN_00405e80 @ 0x00405e80   (est. sk185_e80_copy3)
 * Ghidra: undefined8 * FUN_00405e80(undefined8 *, undefined8 *)
 * Copies the three-word block param_2[0..2] into param_1[0..2], retains the
 * copied value (FUN_0036b270), and returns param_1. Swift value copy with
 * retain. Confidence: low. */
word_t *sk185_e80_copy3(word_t *param_1, word_t *param_2)
{
    param_1[0] = param_2[0];
    param_1[1] = param_2[1];
    param_1[2] = param_2[2];
    sk_swift_retain();                   /* FUN_0036b270 */
    return param_1;
}

/* FUN_00405eb8 @ 0x00405eb8   (est. sk185_eb8_move_retain)
 * Ghidra: void FUN_00405eb8(void)
 * Moves a three-word value into the self block: after FUN_003504d0(),
 * releases the old self[0] and retains the incoming value, then copies self
 * fields from self+0x19/x19+8/+0x10. Swift retain/release (FUN_0036b270 /
 * FUN_0036b118). Confidence: low. */
void sk185_eb8_move_retain(word_t *self, uint8_t *src)
{
    sk185_helper_3504d0();
    word_t old = self[0];
    self[0] = 0;                        /* extraout_x1 → incoming value (see note) */
    sk_swift_retain();                  /* FUN_0036b270 */
    sk_swift_release(old);              /* FUN_0036b118 */
    self[1] = *(word_t *)(src + 8);
    self[2] = *(word_t *)(src + 0x10);
}

/* FUN_00405f0c @ 0x00405f0c   (est. sk185_f0c_move_retain)
 * Ghidra: void FUN_00405f0c(void)
 * Variant of FUN_00405eb8: fetches a two-word value from FUN_003504d0(),
 * releases the old self[0] and stores the new value, then copies self fields
 * from x19+8/+0x10. Confidence: low. */
void sk185_f0c_move_retain(word_t *self, uint8_t *src)
{
    sk185_pair_t v = { 0, 0 };
    v = (sk185_pair_t){ sk185_helper_3504d0(), 0 };
    word_t old = v.lo;
    self[0] = v.hi;
    sk_swift_release(old);              /* FUN_0036b118 */
    word_t n = *(word_t *)(src + 8);
    self[2] = *(word_t *)(src + 0x10);
    self[1] = n;
}

/* FUN_00405fb4 @ 0x00405fb4   (est. sk185_fb4_helper)
 * Ghidra: void FUN_00405fb4(void)
 * Thin wrapper: calls FUN_00404c60. Confidence: low. */
void sk185_fb4_helper(void)
{
    sk185_helper_404c60();
}

/* FUN_00405fb8 @ 0x00405fb8   (est. sk185_fb8_helper)
 * Ghidra: void FUN_00405fb8(void)
 * Thin wrapper: calls FUN_00404c60 (duplicate witness thunk). Confidence: low. */
void sk185_fb8_helper(void)
{
    sk185_helper_404c60();
}

/* FUN_00406064 @ 0x00406064   (est. sk185_06064_guard)
 * Ghidra: void FUN_00406064(void)
 * Calls the no-op FUN_004068cc, then (ZR is set by the void callee) calls
 * FUN_003fbcd4; the otherwise-taken fatal path (FUN_0011d7e8) is dead.
 * Confidence: low. */
void sk185_06064_guard(void)
{
    sk185_noop_4068cc();
    /* (bool)in_ZR is set: FUN_004068cc returns void */
    sk185_helper_3fbcd4();
}

/* FUN_00406090 @ 0x00406090   (est. sk185_06090_guard)
 * Ghidra: void FUN_00406090(void)
 * Calls the no-op FUN_004068cc, then (ZR set) calls FUN_003fc2c0; fatal path
 * (FUN_0011d7e8) is dead. Confidence: low. */
void sk185_06090_guard(void)
{
    sk185_noop_4068cc();
    /* (bool)in_ZR is set: FUN_004068cc returns void */
    sk185_helper_3fc2c0();
}

/* FUN_0040621c @ 0x0040621c   (est. sk185_0621c_helper)
 * Ghidra: void FUN_0040621c(void)
 * Thin wrapper: calls FUN_00404d84. Confidence: low. */
void sk185_0621c_helper(void)
{
    sk185_helper_404d84();
}

/* FUN_00406220 @ 0x00406220   (est. sk185_06220_helper)
 * Ghidra: void FUN_00406220(void)
 * Thin wrapper: calls FUN_00404d84 (duplicate witness thunk). Confidence: low. */
void sk185_06220_helper(void)
{
    sk185_helper_404d84();
}

/* ------------------------------------------------------------------ *
 * No-op stubs. Each is a `return;` in the decompile (Swift runtime
 * placeholder / protocol-witness stub). All confidence: low.
 * ------------------------------------------------------------------ */

/* FUN_00406268 @ 0x00406268   (est. sk185_noop_406268) */
void sk185_noop_406268(void) { }

/* FUN_00406288 @ 0x00406288   (est. sk185_noop_406288) */
void sk185_noop_406288(void) { }

/* FUN_004062a8 @ 0x004062a8   (est. sk185_noop_4062a8) */
void sk185_noop_4062a8(void) { }

/* FUN_004062c8 @ 0x004062c8   (est. sk185_noop_4062c8) */
void sk185_noop_4062c8(void) { }

/* FUN_004062e8 @ 0x004062e8   (est. sk185_noop_4062e8) */
void sk185_noop_4062e8(void) { }

/* FUN_00406374 @ 0x00406374   (est. sk185_noop_406374) */
void sk185_noop_406374(void) { }

/* FUN_00406394 @ 0x00406394   (est. sk185_noop_406394) */
void sk185_noop_406394(void) { }

/* FUN_004064f8 @ 0x004064f8   (est. sk185_noop_4064f8) */
void sk185_noop_4064f8(void) { }

/* FUN_00406518 @ 0x00406518   (est. sk185_noop_406518) */
void sk185_noop_406518(void) { }

/* FUN_00406574 @ 0x00406574   (est. sk185_noop_406574) */
void sk185_noop_406574(void) { }

/* FUN_004065c8 @ 0x004065c8   (est. sk185_noop_4065c8) */
void sk185_noop_4065c8(void) { }

/* FUN_004065e8 @ 0x004065e8   (est. sk185_noop_4065e8) */
void sk185_noop_4065e8(void) { }

/* FUN_0040668c @ 0x0040668c   (est. sk185_noop_40668c) */
void sk185_noop_40668c(void) { }

/* FUN_00406734 @ 0x00406734   (est. sk185_noop_406734) */
void sk185_noop_406734(void) { }

/* FUN_0040676c @ 0x0040676c   (est. sk185_noop_40676c) */
void sk185_noop_40676c(void) { }

/* FUN_0040678c @ 0x0040678c   (est. sk185_noop_40678c) */
void sk185_noop_40678c(void) { }

/* FUN_0040679c @ 0x0040679c   (est. sk185_noop_40679c) */
void sk185_noop_40679c(void) { }

/* FUN_004067b8 @ 0x004067b8   (est. sk185_noop_4067b8) */
void sk185_noop_4067b8(void) { }

/* FUN_0040683c @ 0x0040683c   (est. sk185_noop_40683c) */
void sk185_noop_40683c(void) { }

/* FUN_00406894 @ 0x00406894   (est. sk185_noop_406894) */
void sk185_noop_406894(void) { }

/* FUN_004068bc @ 0x004068bc   (est. sk185_noop_4068bc) */
void sk185_noop_4068bc(void) { }

/* FUN_004068cc @ 0x004068cc   (est. sk185_noop_4068cc)
 * No-op; called by FUN_00406064 / FUN_00406090 as a guard probe. */
void sk185_noop_4068cc(void) { }

/* FUN_0040691c @ 0x0040691c   (est. sk185_noop_40691c) */
void sk185_noop_40691c(void) { }

/* FUN_0040692c @ 0x0040692c   (est. sk185_noop_40692c) */
void sk185_noop_40692c(void) { }

/* FUN_0040695c @ 0x0040695c   (est. sk185_noop_40695c) */
void sk185_noop_40695c(void) { }

/* FUN_0040697c @ 0x0040697c   (est. sk185_noop_40697c) */
void sk185_noop_40697c(void) { }

/* FUN_0040698c @ 0x0040698c   (est. sk185_noop_40698c) */
void sk185_noop_40698c(void) { }

/* FUN_004069d8 @ 0x004069d8   (est. sk185_noop_4069d8) */
void sk185_noop_4069d8(void) { }

/* FUN_004069ec @ 0x004069ec   (est. sk185_noop_4069ec) */
void sk185_noop_4069ec(void) { }

/* FUN_00406a10 @ 0x00406a10   (est. sk185_noop_406a10) */
void sk185_noop_406a10(void) { }

/* FUN_00406a94 @ 0x00406a94   (est. sk185_noop_406a94) */
void sk185_noop_406a94(void) { }

/* FUN_00406ab4 @ 0x00406ab4   (est. sk185_noop_406ab4) */
void sk185_noop_406ab4(void) { }

/* FUN_00406bc4 @ 0x00406bc4   (est. sk185_noop_406bc4) */
void sk185_noop_406bc4(void) { }

/* FUN_00406bd4 @ 0x00406bd4   (est. sk185_noop_406bd4) */
void sk185_noop_406bd4(void) { }

/* FUN_00406c08 @ 0x00406c08   (est. sk185_noop_406c08) */
void sk185_noop_406c08(void) { }

/* FUN_00406ce0 @ 0x00406ce0   (est. sk185_noop_406ce0) */
void sk185_noop_406ce0(void) { }

/* FUN_00406d60 @ 0x00406d60   (est. sk185_noop_406d60) */
void sk185_noop_406d60(void) { }

/* FUN_00406d70 @ 0x00406d70   (est. sk185_noop_406d70) */
void sk185_noop_406d70(void) { }

/* FUN_00406d80 @ 0x00406d80   (est. sk185_noop_406d80) */
void sk185_noop_406d80(void) { }

/* FUN_00406da8 @ 0x00406da8   (est. sk185_noop_406da8) */
void sk185_noop_406da8(void) { }

/* FUN_00406de8 @ 0x00406de8   (est. sk185_noop_406de8) */
void sk185_noop_406de8(void) { }

/* ------------------------------------------------------------------ *
 * Constant / metadata returners.
 * ------------------------------------------------------------------ */

/* FUN_004063b4 @ 0x004063b4   (est. sk185_zero)
 * Ghidra: undefined8 FUN_004063b4(void)
 * Returns 0. Confidence: low. */
word_t sk185_zero(void)
{
    return 0;
}

/* FUN_0040654c @ 0x0040654c   (est. sk185_zero_b)
 * Ghidra: undefined8 FUN_0040654c(void)
 * Returns 0. Confidence: low. */
word_t sk185_zero_b(void)
{
    return 0;
}

/* FUN_00406560 @ 0x00406560   (est. sk185_ff)
 * Ghidra: undefined8 FUN_00406560(void)
 * Returns 0xff. Confidence: low. */
word_t sk185_ff(void)
{
    return 0xff;
}

/* FUN_004069c4 @ 0x004069c4   (est. sk185_ff_b)
 * Ghidra: undefined8 FUN_004069c4(void)
 * Returns 0xff. Confidence: low. */
word_t sk185_ff_b(void)
{
    return 0xff;
}

/* FUN_00406cb0 @ 0x00406cb0   (est. sk185_identity_arg2)
 * Ghidra: undefined8 FUN_00406cb0(undefined8, undefined8)
 * Identity on the second argument; returns param_2. Confidence: low. */
word_t sk185_identity_arg2(word_t param_1, word_t param_2)
{
    (void)param_1;
    return param_2;
}

/* FUN_00406478 @ 0x00406478   (est. sk185_meta_5a1500)
 * Ghidra: undefined * FUN_00406478(void)
 * Returns the `_Concurrency` type-metadata descriptor at DAT_005a1500.
 * Confidence: low. */
void *sk185_meta_5a1500(void)
{
    return (void *)0x5a1500;   /* DAT_005a1500 (Swift type metadata) */
}

/* FUN_004066a4 @ 0x004066a4   (est. sk185_meta_4edd94)
 * Ghidra: undefined * FUN_004066a4(void)
 * Returns the type descriptor at DAT_004edd94. Confidence: low. */
void *sk185_meta_4edd94(void)
{
    return (void *)0x4edd94;   /* DAT_004edd94 (Swift type metadata) */
}

/* FUN_00406d90 @ 0x00406d90   (est. sk185_meta_5a151c)
 * Ghidra: undefined * FUN_00406d90(void)
 * Returns the `_Concurrency` type-metadata descriptor at DAT_005a151c.
 * Confidence: low. */
void *sk185_meta_5a151c(void)
{
    return (void *)0x5a151c;   /* DAT_005a151c (Swift type metadata) */
}

/* ------------------------------------------------------------------ *
 * Swift String-literal builders (return {ptr,len} in x0/x1).
 * ------------------------------------------------------------------ */

/* FUN_00406310 @ 0x00406310   (est. sk185_str_assertion_failed_a)
 * Ghidra: undefined1 [16] FUN_00406310(void)
 * Returns the Swift string {"Assertion failed", 0x10}. Confidence: high
 * (string s_Assertion_failed_005ce250 at 0x5ce250). */
sk185_str_t sk185_str_assertion_failed_a(void)
{
    sk185_str_t s = { "Assertion failed", 0x10 };
    return s;
}

/* FUN_0040633c @ 0x0040633c   (est. sk185_str_assertion_failed_b)
 * Ghidra: undefined1 [16] FUN_0040633c(void)
 * Returns the Swift string {"Assertion failed", 0x10} (duplicate builder).
 * Confidence: high (string s_Assertion_failed_005ce250). */
sk185_str_t sk185_str_assertion_failed_b(void)
{
    sk185_str_t s = { "Assertion failed", 0x10 };
    return s;
}

/* FUN_004063f4 @ 0x004063f4   (est. sk185_str_assertion_failed_c)
 * Ghidra: undefined1 [16] FUN_004063f4(void)
 * Returns the Swift string {"Assertion failed", 0x10}; called by
 * FUN_00405cd4 to feed the runtime failure. Confidence: high (string
 * s_Assertion_failed_005ce250). */
sk185_str_t sk185_str_assertion_failed_c(void)
{
    sk185_str_t s = { "Assertion failed", 0x10 };
    return s;
}

/* FUN_004063d0 @ 0x004063d0   (est. sk185_str_precondition_failed)
 * Ghidra: undefined1 [16] FUN_004063d0(void)
 * Returns the Swift string {"Precondition failed", 0x13}. Confidence: high
 * (string s_Precondition_failed_005ce2d0 at 0x5ce2d0). */
sk185_str_t sk185_str_precondition_failed(void)
{
    sk185_str_t s = { "Precondition failed", 0x13 };
    return s;
}

/* C-string (char*) returners. */

/* FUN_00406678 @ 0x00406678   (est. sk185_cstr_precondition_failed)
 * Ghidra: char * FUN_00406678(void)
 * Returns the C string "Precondition failed" (0x5ce2d0). Confidence: high. */
const char *sk185_cstr_precondition_failed(void)
{
    return "Precondition failed";   /* s_Precondition_failed_005ce2d0 */
}

/* FUN_0040677c @ 0x0040677c   (est. sk185_cstr_assertion_failed)
 * Ghidra: char * FUN_0040677c(void)
 * Returns the C string "Assertion failed" (0x5ce250). Confidence: high. */
const char *sk185_cstr_assertion_failed(void)
{
    return "Assertion failed";   /* s_Assertion_failed_005ce250 */
}

/* FUN_00406aa4 @ 0x00406aa4   (est. sk185_cstr_precondition_failed_b)
 * Ghidra: char * FUN_00406aa4(void)
 * Returns the C string "Precondition failed" (0x5ce2d0) (duplicate builder).
 * Confidence: high. */
const char *sk185_cstr_precondition_failed_b(void)
{
    return "Precondition failed";   /* s_Precondition_failed_005ce2d0 */
}

/* ------------------------------------------------------------------ *
 * Fatal-error thunks (noreturn; raise a `_Concurrency` runtime failure with
 * a specific source file/line via FUN_001afa84).
 * ------------------------------------------------------------------ */

/* FUN_00406444 @ 0x00406444   (est. sk185_fatal_asyncstream)
 * Ghidra: void FUN_00406444(ulong)
 * Raises "Fatal error" for AsyncStream: FUN_001afa84("Fatal error", 0xb, 2,
 * 0xd00000000000002f, param_1 | 0x8000000000000000,
 * "_Concurrency/AsyncStream.swift", 0x1e=30, 2). Noreturn.
 * Confidence: medium (AsyncStream.swift:30 string anchor). */
void sk185_fatal_asyncstream(word_t param_1)
{
    sk_assert_fatal((word_t)"Fatal error", 0xb, 2, 0xd00000000000002fULL,
                    param_1 | 0x8000000000000000ULL,
                    (word_t)"_Concurrency/AsyncStream.swift", 0x1e, 2);
}

/* FUN_00406490 @ 0x00406490   (est. sk185_fatal_sourcecompat)
 * Ghidra: void FUN_00406490(ulong)
 * Raises "Fatal error" for the source-compatibility layer:
 * FUN_001afa84("Fatal error", 0xb, 2, 0xd00000000000002f,
 * param_1 | 0x8000000000000000, "_Concurrency/SourceCompatibility.swift",
 * 0x2b=43, 2). Noreturn.
 * Confidence: medium (SourceCompatibility.swift:43 string anchor). */
void sk185_fatal_sourcecompat(word_t param_1)
{
    sk_assert_fatal((word_t)"Fatal error", 0xb, 2, 0xd00000000000002fULL,
                    param_1 | 0x8000000000000000ULL,
                    (word_t)"_Concurrency/SourceCompatibility.swift", 0x2b, 2);
}

/* FUN_004064c4 @ 0x004064c4   (est. sk185_fatal_asynthrowingstream)
 * Ghidra: void FUN_004064c4(ulong)
 * Raises "Fatal error" for AsyncThrowingStream: FUN_001afa84("Fatal error",
 * 0xb, 2, 0xd00000000000002f, param_1 | 0x8000000000000000,
 * "_Concurrency/AsyncThrowingStream.swift", 0x26=38, 2). Noreturn.
 * Confidence: medium (AsyncThrowingStream.swift:38 string anchor). */
void sk185_fatal_asynthrowingstream(word_t param_1)
{
    sk_assert_fatal((word_t)"Fatal error", 0xb, 2, 0xd00000000000002fULL,
                    param_1 | 0x8000000000000000ULL,
                    (word_t)"_Concurrency/AsyncThrowingStream.swift", 0x26, 2);
}

/* ------------------------------------------------------------------ *
 * Wrappers over shared helpers / runtime functions.
 * ------------------------------------------------------------------ */

/* FUN_00406420 @ 0x00406420   (est. sk185_06420_vtdispatch30)
 * Ghidra: void FUN_00406420(void)
 * Thin wrapper: calls FUN_000839f8 (sk_vt_dispatch30). Confidence: low. */
void sk185_06420_vtdispatch30(void)
{
    sk_vt_dispatch30();
}

/* FUN_0040652c @ 0x0040652c   (est. sk185_0652c_str)
 * Ghidra: void FUN_0040652c(void)
 * Calls FUN_00377824 (sk_str_convert) with 0xff. Confidence: low. */
void sk185_0652c_str(void)
{
    sk_str_convert(0xff);
}

/* FUN_00406590 @ 0x00406590   (est. sk185_06590_helper)
 * Ghidra: void FUN_00406590(void)
 * Calls FUN_003d4658 (vtable-slot resolver). Confidence: low. */
void sk185_06590_helper(void)
{
    sk185_helper_3d4658();
}

/* FUN_00406608 @ 0x00406608   (est. sk185_06608_str2)
 * Ghidra: void FUN_00406608(void)
 * Calls FUN_00377bec (sk_str_convert2). Confidence: low. */
void sk185_06608_str2(void)
{
    sk_str_convert2();
}

/* FUN_004067cc @ 0x004067cc   (est. sk185_067cc_extent)
 * Ghidra: void FUN_004067cc(void)
 * Calls FUN_000a649c (sk_exclave_extent_c). Confidence: low. */
void sk185_067cc_extent(void)
{
    sk_exclave_extent_c();
}

/* FUN_004067f8 @ 0x004067f8   (est. sk185_067f8_str2)
 * Ghidra: void FUN_004067f8(void)
 * Calls FUN_00377bec (sk_str_convert2) (duplicate wrapper). Confidence: low. */
void sk185_067f8_str2(void)
{
    sk_str_convert2();
}

/* FUN_00406830 @ 0x00406830   (est. sk185_06830_helper)
 * Ghidra: void FUN_00406830(undefined8)
 * Calls FUN_00408db8(param_1, 0, 0). Confidence: low. */
void sk185_06830_helper(word_t param_1)
{
    sk185_helper_408db8(param_1, 0, 0);
}

/* FUN_0040684c @ 0x0040684c   (est. sk185_0684c_str)
 * Ghidra: void FUN_0040684c(void)
 * Calls FUN_00377824 (sk_str_convert) with 0. Confidence: low. */
void sk185_0684c_str(void)
{
    sk_str_convert(0);
}

/* FUN_0040686c @ 0x0040686c   (est. sk185_0686c_vtdispatch)
 * Ghidra: void FUN_0040686c(void)
 * Dispatches through self field 0x10 via sk_vt_dispatch38(self+0x10, 1, 1),
 * then calls FUN_0040bd24. Confidence: low. */
void sk185_0686c_vtdispatch(uint8_t *self)
{
    sk_vt_dispatch38(SK185_FIELD(self, 0x10), 1, 1);
    sk185_helper_40bd24();
}

/* FUN_004068a4 @ 0x004068a4   (est. sk185_068a4_str)
 * Ghidra: void FUN_004068a4(undefined8, undefined8, undefined8)
 * Calls FUN_00377824(0, param_2, param_3, &DAT_00614a5c, &LAB_00614a6c) —
 * demangles/renders a value against the descriptor pair. Confidence: low. */
void sk185_068a4_str(word_t param_1, word_t param_2, word_t param_3)
{
    (void)param_1;
    sk_str_convert(0, param_2, param_3, (word_t)0x614a5c, (word_t)0x614a6c);
}

/* FUN_004068f4 @ 0x004068f4   (est. sk185_068f4_release)
 * Ghidra: void FUN_004068f4(void)
 * Calls FUN_003fcc1c then releases a descriptor via FUN_00377dcc(0)
 * (sk_desc_deref_release). Confidence: low. */
void sk185_068f4_release(void)
{
    sk185_helper_3fcc1c();
    sk_desc_deref_release(0);
}

/* FUN_00406be4 @ 0x00406be4   (est. sk185_06be4_vtdispatch30)
 * Ghidra: void FUN_00406be4(void)
 * Thin wrapper: calls FUN_000839f8 (sk_vt_dispatch30) (duplicate). Confidence: low. */
void sk185_06be4_vtdispatch30(void)
{
    sk_vt_dispatch30();
}

/* FUN_00406c5c @ 0x00406c5c   (est. sk185_06c5c_vtdispatch)
 * Ghidra: void FUN_00406c5c(undefined8)
 * Dispatches via sk_vt_dispatch38(param_1, 1, 1), then calls FUN_0040bd24.
 * Confidence: low. */
void sk185_06c5c_vtdispatch(word_t param_1)
{
    sk_vt_dispatch38(param_1, 1, 1);
    sk185_helper_40bd24();
}

/* FUN_00406cf0 @ 0x00406cf0   (est. sk185_06cf0_vtdispatch)
 * Ghidra: void FUN_00406cf0(void)
 * Dispatches through self field 0x10 via sk_vt_dispatch38(self+0x10, 0, 1),
 * then calls FUN_0040bd24. Confidence: low. */
void sk185_06cf0_vtdispatch(uint8_t *self)
{
    sk_vt_dispatch38(SK185_FIELD(self, 0x10), 0, 1);
    sk185_helper_40bd24();
}

/* FUN_00406db8 @ 0x00406db8   (est. sk185_06db8_vtdispatch30)
 * Ghidra: void FUN_00406db8(void)
 * Dispatches via sk_vt_dispatch30(self+0x50, 1, self+0x38). Confidence: low. */
void sk185_06db8_vtdispatch30(uint8_t *self)
{
    sk_vt_dispatch30(SK185_FIELD(self, 0x50), 1, SK185_FIELD(self, 0x38));
}

/* FUN_00406dd0 @ 0x00406dd0   (est. sk185_06dd0_str)
 * Ghidra: void FUN_00406dd0(void)
 * Calls FUN_00377824 (sk_str_convert) with 0xff (duplicate). Confidence: low. */
void sk185_06dd0_str(void)
{
    sk_str_convert(0xff);
}

/* FUN_00406748 @ 0x00406748   (est. sk185_06748_str)
 * Ghidra: void FUN_00406748(undefined8, undefined8, long)
 * Calls FUN_00377824(0, param_3+0x18, param_3+0x10, &DAT_00614a5c,
 * &LAB_00614a6c) — renders a two-word value from param_3. Confidence: low. */
void sk185_06748_str(word_t param_1, word_t param_2, uint8_t *param_3)
{
    (void)param_1; (void)param_2;
    sk_str_convert(0, *(word_t *)(param_3 + 0x18), *(word_t *)(param_3 + 0x10),
                   (word_t)0x614a5c, (word_t)0x614a6c);
}

/* FUN_00406814 @ 0x00406814   (est. sk185_06814_str)
 * Ghidra: void FUN_00406814(undefined8, undefined8, long)
 * Duplicate of FUN_00406748: FUN_00377824(0, param_3+0x18, param_3+0x10,
 * &DAT_00614a5c, &LAB_00614a6c). Confidence: low. */
void sk185_06814_str(word_t param_1, word_t param_2, uint8_t *param_3)
{
    (void)param_1; (void)param_2;
    sk_str_convert(0, *(word_t *)(param_3 + 0x18), *(word_t *)(param_3 + 0x10),
                   (word_t)0x614a5c, (word_t)0x614a6c);
}

/* ------------------------------------------------------------------ *
 * Self-field accessors (return a single context field).
 * ------------------------------------------------------------------ */

/* FUN_00406624 @ 0x00406624   (est. sk185_field_0x10_a)
 * Ghidra: undefined8 FUN_00406624(void)
 * Returns self field at byte offset 0x10. Confidence: low. */
word_t sk185_field_0x10_a(uint8_t *self)
{
    return SK185_FIELD(self, 0x10);
}

/* FUN_004066bc @ 0x004066bc   (est. sk185_field_0x10_b)
 * Ghidra: undefined8 FUN_004066bc(void)
 * Returns self field at byte offset 0x10. Confidence: low. */
word_t sk185_field_0x10_b(uint8_t *self)
{
    return SK185_FIELD(self, 0x10);
}

/* FUN_004069b0 @ 0x004069b0   (est. sk185_field_0x10_c)
 * Ghidra: undefined8 FUN_004069b0(void)
 * Returns self field at byte offset 0x10. Confidence: low. */
word_t sk185_field_0x10_c(uint8_t *self)
{
    return SK185_FIELD(self, 0x10);
}

/* FUN_00406dfc @ 0x00406dfc   (est. sk185_field_0x108)
 * Ghidra: undefined8 FUN_00406dfc(void)
 * Returns self field at byte offset 0x108. Confidence: low. */
word_t sk185_field_0x108(uint8_t *self)
{
    return SK185_FIELD(self, 0x108);
}

/* ------------------------------------------------------------------ *
 * Self-field store helpers (write arguments into context fields).
 * ------------------------------------------------------------------ */

/* FUN_00406c80 @ 0x00406c80   (est. sk185_store_4)
 * Ghidra: void FUN_00406c80(undefined8, undefined8, undefined8, undefined8)
 * Stores param_1→0x10, param_2→0x18, param_3→0x20, param_4→0x28 of self.
 * Confidence: low. */
void sk185_store_4(uint8_t *self, word_t param_1, word_t param_2,
                   word_t param_3, word_t param_4)
{
    SK185_FIELD(self, 0x20) = param_3;
    SK185_FIELD(self, 0x28) = param_4;
    SK185_FIELD(self, 0x10) = param_1;
    SK185_FIELD(self, 0x18) = param_2;
}

/* FUN_00406cc8 @ 0x00406cc8   (est. sk185_store_6)
 * Ghidra: void FUN_00406cc8(undefined8, undefined8, undefined8, undefined8,
 *                           undefined8)
 * Stores param_1→0x10, param_2→0x18, param_3→0x20, param_4→0x28, self(x20)→
 * 0x30, param_5→0x38 of self. Confidence: low. */
void sk185_store_6(uint8_t *self, word_t ctx, word_t param_1, word_t param_2,
                   word_t param_3, word_t param_4, word_t param_5)
{
    SK185_FIELD(self, 0x30) = ctx;      /* unaff_x20 preserved context */
    SK185_FIELD(self, 0x38) = param_5;
    SK185_FIELD(self, 0x20) = param_3;
    SK185_FIELD(self, 0x28) = param_4;
    SK185_FIELD(self, 0x10) = param_1;
    SK185_FIELD(self, 0x18) = param_2;
}

/* FUN_00406c1c @ 0x00406c1c   (est. sk185_store_6_b)
 * Ghidra: void FUN_00406c1c(undefined8, undefined8, undefined8, long)
 * Stores param_1→0x10, param_2→0x18, param_3→0x20, param_4→0x28, self(x20)→
 * 0x30, and param_4+0x18→0x38 of self. Confidence: low. */
void sk185_store_6_b(uint8_t *self, word_t ctx, word_t param_1, word_t param_2,
                     word_t param_3, uint8_t *param_4)
{
    SK185_FIELD(self, 0x28) = (word_t)param_4;
    SK185_FIELD(self, 0x30) = ctx;      /* unaff_x20 preserved context */
    SK185_FIELD(self, 0x18) = param_2;
    SK185_FIELD(self, 0x20) = param_3;
    SK185_FIELD(self, 0x10) = param_1;
    SK185_FIELD(self, 0x38) = *(word_t *)(param_4 + 0x18);
}

/* FUN_00406704 @ 0x00406704   (est. sk185_06704_setup)
 * Ghidra: void FUN_00406704(undefined8, long)
 * Stores param_1→0x10, param_2→0x18, self(x20)→0x20, param_2+0x18→0x28 and
 * param_2+0x10→0x30 of self, then calls FUN_00377824(0xff, ...) with the two
 * captured words and descriptor pair &DAT_00614a5c/&DAT_00614a74.
 * Confidence: low. */
void sk185_06704_setup(uint8_t *self, word_t ctx, word_t param_1, uint8_t *param_2)
{
    SK185_FIELD(self, 0x18) = (word_t)param_2;
    SK185_FIELD(self, 0x20) = ctx;      /* unaff_x20 preserved context */
    SK185_FIELD(self, 0x10) = param_1;
    word_t v2 = *(word_t *)(param_2 + 0x18);
    SK185_FIELD(self, 0x28) = v2;
    word_t v1 = *(word_t *)(param_2 + 0x10);
    SK185_FIELD(self, 0x30) = v1;
    sk_str_convert(0xff, v2, v1, (word_t)0x614a5c, (word_t)0x614a74);
}

/* ------------------------------------------------------------------ *
 * Closure-context constructors: write a partial-apply thunk pointer into
 * out+8 and return a two-word value {fieldA, fieldB} in x0/x1.
 * ------------------------------------------------------------------ */

/* FUN_00406944 @ 0x00406944   (est. sk185_ctx_x16_a)
 * Ghidra: undefined1 [16] FUN_00406944(long)
 * Stores the incoming partial-apply thunk (in_x16) into param_1+8 and returns
 * {self+0x50, self+0x68}. Confidence: low. */
sk185_pair_t sk185_ctx_x16_a(uint8_t *self, uint8_t *param_1, word_t thunk)
{
    *(word_t *)(param_1 + 8) = thunk;   /* in_x16: partial-apply thunk address */
    sk185_pair_t r = { SK185_FIELD(self, 0x50), SK185_FIELD(self, 0x68) };
    return r;
}

/* FUN_00406c98 @ 0x00406c98   (est. sk185_ctx_x16_b)
 * Ghidra: undefined1 [16] FUN_00406c98(long)
 * Stores the incoming partial-apply thunk (in_x16) into param_1+8 and returns
 * {self+0x48, self+0x10}. Confidence: low. */
sk185_pair_t sk185_ctx_x16_b(uint8_t *self, uint8_t *param_1, word_t thunk)
{
    *(word_t *)(param_1 + 8) = thunk;   /* in_x16: partial-apply thunk address */
    sk185_pair_t r = { SK185_FIELD(self, 0x48), SK185_FIELD(self, 0x10) };
    return r;
}

/* FUN_00406e18 @ 0x00406e18   (est. sk185_ctx_x16_c)
 * Ghidra: undefined1 [16] FUN_00406e18(long)
 * Stores the incoming partial-apply thunk (in_x16) into param_1+8 and returns
 * {self+0x58, self+0x70}. Confidence: low. */
sk185_pair_t sk185_ctx_x16_c(uint8_t *self, uint8_t *param_1, word_t thunk)
{
    *(word_t *)(param_1 + 8) = thunk;   /* in_x16: partial-apply thunk address */
    sk185_pair_t r = { SK185_FIELD(self, 0x58), SK185_FIELD(self, 0x70) };
    return r;
}

/* FUN_00406a24 @ 0x00406a24   (est. sk185_ctx_3e8918)
 * Ghidra: undefined1 [16] FUN_00406a24(long)
 * Stamps the partial-apply thunk at LAB_003e8918 into param_1+8 and returns
 * {self+0xe0, self+0x18}. Confidence: low. */
sk185_pair_t sk185_ctx_3e8918(uint8_t *self, uint8_t *param_1)
{
    *(void **)(param_1 + 8) = (void *)0x3e8918;   /* LAB_003e8918 */
    sk185_pair_t r = { SK185_FIELD(self, 0xe0), SK185_FIELD(self, 0x18) };
    return r;
}

/* FUN_00406a5c @ 0x00406a5c   (est. sk185_ctx_3dadc0)
 * Ghidra: undefined1 [16] FUN_00406a5c(long)
 * Stamps the partial-apply thunk at LAB_003dadc0 into param_1+8 and returns
 * {self+0x108, self+0x18}. Confidence: low. */
sk185_pair_t sk185_ctx_3dadc0(uint8_t *self, uint8_t *param_1)
{
    *(void **)(param_1 + 8) = (void *)0x3dadc0;   /* LAB_003dadc0 */
    sk185_pair_t r = { SK185_FIELD(self, 0x108), SK185_FIELD(self, 0x18) };
    return r;
}

/* FUN_00406ac4 @ 0x00406ac4   (est. sk185_ctx_3e7424)
 * Ghidra: undefined1 [16] FUN_00406ac4(long)
 * Stamps the partial-apply thunk at LAB_003e7424 into param_1+8 and returns
 * {self+0xb8, self+0xd8}. Confidence: low. */
sk185_pair_t sk185_ctx_3e7424(uint8_t *self, uint8_t *param_1)
{
    *(void **)(param_1 + 8) = (void *)0x3e7424;   /* LAB_003e7424 */
    sk185_pair_t r = { SK185_FIELD(self, 0xb8), SK185_FIELD(self, 0xd8) };
    return r;
}

/* FUN_00406af4 @ 0x00406af4   (est. sk185_ctx_3ef9b0)
 * Ghidra: undefined1 [16] FUN_00406af4(long)
 * Stamps the partial-apply thunk FUN_003ef9b0 into param_1+8 and returns
 * {self+0x48, self+0x10}. Confidence: low. */
sk185_pair_t sk185_ctx_3ef9b0(uint8_t *self, uint8_t *param_1)
{
    *(void **)(param_1 + 8) = (void *)sk185_helper_3ef9b0;   /* FUN_003ef9b0 */
    sk185_pair_t r = { SK185_FIELD(self, 0x48), SK185_FIELD(self, 0x10) };
    return r;
}

/* FUN_00406b24 @ 0x00406b24   (est. sk185_ctx_3d9abc)
 * Ghidra: undefined1 [16] FUN_00406b24(long)
 * Stamps the partial-apply thunk at LAB_003d9abc into param_1+8 and returns
 * {self+0xa0, self+0xc0}. Confidence: low. */
sk185_pair_t sk185_ctx_3d9abc(uint8_t *self, uint8_t *param_1)
{
    *(void **)(param_1 + 8) = (void *)0x3d9abc;   /* LAB_003d9abc */
    sk185_pair_t r = { SK185_FIELD(self, 0xa0), SK185_FIELD(self, 0xc0) };
    return r;
}

/* FUN_00406b54 @ 0x00406b54   (est. sk185_ctx_3e77d0)
 * Ghidra: undefined8 FUN_00406b54(long)
 * Stamps the partial-apply thunk at LAB_003e77d0 into param_1+8 and returns
 * self field 0x78. Confidence: low. */
word_t sk185_ctx_3e77d0(uint8_t *self, uint8_t *param_1)
{
    *(void **)(param_1 + 8) = (void *)0x3e77d0;   /* LAB_003e77d0 */
    return SK185_FIELD(self, 0x78);
}

/* FUN_00406b84 @ 0x00406b84   (est. sk185_ctx_3d9e50)
 * Ghidra: undefined8 FUN_00406b84(long)
 * Stamps the partial-apply thunk at LAB_003d9e50 into param_1+8 and returns
 * self field 0x60. Confidence: low. */
word_t sk185_ctx_3d9e50(uint8_t *self, uint8_t *param_1)
{
    *(void **)(param_1 + 8) = (void *)0x3d9e50;   /* LAB_003d9e50 */
    return SK185_FIELD(self, 0x60);
}

/* FUN_00406c3c @ 0x00406c3c   (est. sk185_ctx_3fc9d0)
 * Ghidra: undefined1 [16] FUN_00406c3c(void)
 * Returns {&DAT_006c0b50, FUN_003fc9d0}: a descriptor/function pair.
 * Confidence: low. */
sk185_pair_t sk185_ctx_3fc9d0(void)
{
    sk185_pair_t r = { (word_t)0x6c0b50, (word_t)sk185_helper_3fc9d0 };
    return r;
}

/* FUN_00406bb4 @ 0x00406bb4   (est. sk185_ctx_pair)
 * Ghidra: undefined1 [16] FUN_00406bb4(undefined8)
 * Returns {param_1, in_stack_0x8} (a two-word value assembled from the first
 * argument and the value spilled to the stack at sp+8). Confidence: low. */
sk185_pair_t sk185_ctx_pair(word_t param_1, word_t stack8)
{
    sk185_pair_t r = { param_1, stack8 };   /* in_stack_00000008 */
    return r;
}

/* FUN_00406d18 @ 0x00406d18   (est. sk185_06d18_collect)
 * Ghidra: void FUN_00406d18(void)
 * Loads ten words from self fields (0xf8,0xf0,0xd8,0xd0,0xb0,0xa8,0x90,0x88,
 * 0x70,0x48) into local slots, then calls FUN_0040bd24(self+0x178). The
 * locals are read by the (out-of-slice) callee; rendered faithfully as a
 * stack spilling of the captured fields. Confidence: low. */
void sk185_06d18_collect(uint8_t *self)
{
    word_t s0 = SK185_FIELD(self, 0xf8);
    word_t s1 = SK185_FIELD(self, 0xf0);
    word_t s2 = SK185_FIELD(self, 0xd8);
    word_t s3 = SK185_FIELD(self, 0xd0);
    word_t s4 = SK185_FIELD(self, 0xb0);
    word_t s5 = SK185_FIELD(self, 0xa8);
    word_t s6 = SK185_FIELD(self, 0x90);
    word_t s7 = SK185_FIELD(self, 0x88);
    word_t s8 = SK185_FIELD(self, 0x70);
    word_t s9 = SK185_FIELD(self, 0x48);
    (void)s0; (void)s1; (void)s2; (void)s3; (void)s4;
    (void)s5; (void)s6; (void)s7; (void)s8; (void)s9;
    sk185_helper_40bd24(SK185_FIELD(self, 0x178));
}
