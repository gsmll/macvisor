/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 19: 0xe7974-0xec044 caps region. */

#include <stdint.h>
#include <stddef.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */
extern void FUN_000e7874(void);          /* out of slice; caps setup thunk chain */
extern uint64_t FUN_0036a940(void);      /* out of slice; returns a saved value */
extern void FUN_000e7d20(uint64_t, uint64_t, uint64_t); /* in slice, 0xe7d20 */
extern void FUN_0006de38(uint64_t, uint64_t, uint64_t); /* out of slice */
extern cl4_result_t FUN_00151974(void);  /* out of slice; {status,extra} pair */
extern void FUN_00151a6c(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t,
                         uint64_t, uint64_t, uint64_t); /* out of slice; panic/printer */
extern void FUN_0036b270(void);  /* out of slice; per-cpu/context acquire */
extern void FUN_0036b118(uint64_t); /* out of slice; ref release */
extern void FUN_0036b6f4(void);  /* out of slice; error path */
extern void FUN_000fdb98(uint8_t *); /* out of slice; immediate completion */
extern void FUN_000ffba8(void);  /* out of slice; deferred completion */

/* FUN_000e7974 @ 0x000e7974   (est. cl4_caps_region_thunk)
 * Ghidra: undefined FUN_000e7974(void)
 * Tail thunk: forwards directly to FUN_000e7874 (out of slice), a complex
 * capability/state setup routine that allocates a tag-0x18 block
 * (FUN_002a4ab4), consults the message register block (FUN_003a25d4), runs a
 * handler via function pointer from a table (FUN_00027724 @ 0x671848), then
 * performs IPC state transitions (thunk_FUN_002acbb8). Returns a packed
 * {status=0xd<<60|0x15, addr=0x80000000005c4830} value.
 * Confidence: low
 * Notes: body is a single tail call to out-of-slice FUN_000e7874. */
void cl4_caps_region_thunk_000e7974(void)
{
    FUN_000e7874();  /* out of slice */
}

/* FUN_000e79d8 @ 0x000e79d8   (est. cl4_const_0x651ad0)
 * Ghidra: undefined1[16] FUN_000e79d8(void)
 * Returns the constant 0x651ad0 zero-extended to a 16-byte word pair
 * (lo=0x651ad0, hi=0). Likely returns a fixed data/object address used as an
 * IPC/capability argument.
 * Confidence: low
 * Notes: pure constant return; ZEXT816(0x651ad0). */
cl4_result_t cl4_const_0x651ad0(void)
{
    cl4_result_t r;
    r.lo = 0x651ad0;
    r.hi = 0;
    return r;
}

/* FUN_000e79e8 @ 0x000e79e8   (est. cl4_noop)
 * Ghidra: void FUN_000e79e8(void)
 * Empty function that performs no operation and returns void.
 * Confidence: high
 * Notes: empty body; referenced by the 0xe7874 setup path. */
void cl4_noop(void)
{
}

/* FUN_000e79fc @ 0x000e79fc   (est. cl4_caps_dispatch_pre)
 * Ghidra: undefined8 FUN_000e79fc(undefined8 p1, undefined8 p2, undefined8 p3)
 * Saves the value returned by the out-of-slice helper FUN_0036a940, then
 * dispatches to the in-slice function FUN_000e7d20 (0xe7d20) with the three
 * forwarded arguments, and returns the earlier saved value.
 * Confidence: low
 * Notes: FUN_0036a940 (out of slice) result is preserved across the
 * FUN_000e7d20 call and returned. */
uint64_t cl4_caps_dispatch_pre(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t saved = FUN_0036a940();  /* out of slice */
    FUN_000e7d20(p1, p2, p3);         /* in slice, 0xe7d20 */
    return saved;
}

/* FUN_000e7a64 @ 0x000e7a64   (est. cl4_caps_panic_assert)
 * Ghidra: void FUN_000e7a64(undefined8 p1, undefined8 p2)
 * Fetches a field at *(x20+0x10)+0x48 (the current thread/object context),
 * passes it with p1/p2 to out-of-slice FUN_0006de38, then calls the panic
 * handler FUN_00151a6c with the source label "AppleInternal/Library/
 * BuildRoot/..." (0x5c4870), line 0x11f, verbosity 2, code 0x4f, and the
 * 16-byte value from FUN_00151974 as arguments. This is an assertion-failure
 * panic path in the caps region.
 * Confidence: low
 * Notes: FUN_00151a6c is the panic/printer; FUN_00151974 supplies a
 * {status,extra} pair; string at 0x5c4870 is a BuildRoot path. */
void cl4_caps_panic_assert(uint64_t p1, uint64_t p2)
{
    /* unaff_x20 is the caller-preserved context register; the object context
     * is read from *(ctx+0x10)+0x48. */
    uint64_t ctx_reg = 0;  /* unaff_x20 carried in from caller */
    uint64_t ctx = *(uint64_t *)(*(uint64_t *)(ctx_reg + 0x10) + 0x48);
    FUN_0006de38(ctx, p1, p2);  /* out of slice */
    cl4_result_t pair = FUN_00151974();  /* out of slice */
    /* LAB_000f648c: code address passed to panic; 0x5c4870 is the BuildRoot
     * source-path string; 0x11f is the line number, 0x4f the panic code. */
    FUN_00151a6c(0 /* LAB_000f648c */, 0,
                 (uint64_t)0x5c4870 /* "AppleInternal/Library/BuildRoot/..." */,
                 0x11f, 2, 0x4f, pair.lo, pair.hi);  /* panic */
}

/* FUN_000e7ad8 @ 0x000e7ad8   (est. cl4_caps_async_op_setup)
 * Ghidra: undefined FUN_000e7ad8(undefined8 param_1, long *param_2, ulong param_3)
 * Sets up an asynchronous capability operation. Stores the object pointer
 * param_1 into the caller context (x20) at +0x10, then invokes a method
 * obtained from *param_2+0x1b8 (an operation/dispatch table) with a
 * 16-byte result buffer (&local_90, kind 2). If the companion register
 * (unaff_x21) is clear, the returned {lo,hi,...} is committed into the
 * context struct (offsets 0x18..0x49), and then either FUN_000fdb98 (immediate
 * completion) or FUN_000ffba8 (deferred) runs depending on param_3 bit 0.
 * Reference counts are released on all exit paths.
 * Confidence: low
 * Notes: fallback via analyze_function_complete (decompile timed out);
 * unreachable block at 0xe7c00 removed by decompiler; unaff_x20/x21 are
 * caller-preserved context registers. */
void cl4_caps_async_op_setup(uint64_t param_1, uint64_t *param_2, uint64_t param_3)
{
    uint8_t result_buf[16];
    uint64_t ctx = 0;   /* unaff_x20 context register from caller */
    uint64_t ctx_flag = 0; /* unaff_x21 companion register from caller */
    void (*op)(uint8_t *, int, int, int, int, int);

    *(uint64_t *)(ctx + 0x10) = param_1;
    op = *(void (**)(uint8_t *, int, int, int, int, int))(*param_2 + 0x1b8);
    FUN_0036b270();  /* out of slice; per-cpu/context acquire */
    op(result_buf, 2, 0, 0, 0, 0);
    if (ctx_flag == 0) {
        *(uint64_t *)(ctx + 0x20) = *(uint64_t *)(result_buf + 8);
        *(uint64_t *)(ctx + 0x18) = *(uint64_t *)(result_buf + 0);
        *(uint64_t *)(ctx + 0x30) = *(uint64_t *)(result_buf + 0x18);
        *(uint64_t *)(ctx + 0x28) = *(uint64_t *)(result_buf + 0x10);
        *(uint64_t *)(ctx + 0x40) = *(uint64_t *)(result_buf + 0x28);
        *(uint64_t *)(ctx + 0x38) = *(uint64_t *)(result_buf + 0x20);
        *(uint64_t *)(ctx + 0x49) = *(uint64_t *)(result_buf + 0x37);
        *(uint64_t *)(ctx + 0x41) = *(uint64_t *)(result_buf + 0x30);
        uint64_t u = *(uint64_t *)(*(uint64_t *)(ctx + 0x10) + 0x10);
        FUN_0036b270(u);  /* out of slice */
        if ((param_3 & 1) == 0) {
            FUN_000fdb98(result_buf);  /* out of slice; immediate completion */
        } else {
            FUN_000ffba8();            /* out of slice; deferred completion */
        }
        FUN_0036b118(u);       /* out of slice; ref release */
        FUN_0036b118(param_2);
        FUN_0036b118(param_1);
    } else {
        FUN_0036b118(param_1);
        FUN_0036b118(param_2);
        FUN_0036b118(*(uint64_t *)(ctx + 0x10));
        FUN_0036b6f4();  /* out of slice; error path */
    }
}

/* FUN_000e7c34 @ 0x000e7c34   (est. cl4_caps_op_stateful)
 * Ghidra: undefined1[16] FUN_000e7c34(void)
 * Stateful capability operation. Allocates a tag-0x1d block
 * (FUN_002a4ab4), consults the message-register block with the 0xe0...
 * status prefix (FUN_003a25d4), runs a handler selected from the
 * 0x671df8 table via FUN_00027724, then performs two IPC message-state
 * transitions (thunk_FUN_002acbb8 with 0x29/0xe1... codes). Returns the
 * packed {status=0xd<<60|0x34, addr=0x80000000005c4970}.
 * Confidence: low
 * Notes: mirrors the 0xe7874 setup/state-machine pattern. */
cl4_result_t cl4_caps_op_stateful(void)
{
    uint64_t h;
    void (*handler)(uint64_t, uint64_t);

    FUN_002a4ab4(0x1d);  /* out of slice; allocate tag-0x1d block */
    h = FUN_003a25d4(0xe000000000000000ULL);  /* out of slice; MR block */
    handler = (void (*)(uint64_t, uint64_t))FUN_00027724(0x671df8);  /* out of slice */
    handler(0x677830, 0x671df8);
    thunk_FUN_002acbb8();               /* out of slice; IPC state transition */
    /* extraout_x1: leftover x1 from the handler call fed back into the
     * message-register helper. */
    uint64_t carry = 0;  /* extraout_x1 */
    h = FUN_003a25d4(carry);            /* out of slice; MR block */
    thunk_FUN_002acbb8(0x29, 0xe100000000000000ULL);  /* out of slice */
    cl4_result_t r;
    r.hi = 0x80000000005c4970ULL;
    r.lo = 0xd000000000000034ULL;
    return r;
}
