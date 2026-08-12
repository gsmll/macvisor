/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 19: 0xe7974-0xec044 caps region. */

#include <stdint.h>
#include <stddef.h>

#include "sk_internal.h"
#include <string.h>

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */
extern void FUN_000e7874();          /* out of slice; caps setup thunk chain */
extern uint64_t FUN_0036a940();      /* out of slice; returns a saved value */
extern void FUN_000e7d20(); /* in slice, 0xe7d20 */
extern void FUN_0006de38(); /* out of slice */
extern cl4_result_t FUN_00151974();  /* out of slice; {status,extra} pair */
extern void FUN_00151a6c(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t,
                         uint64_t, uint64_t, uint64_t); /* out of slice; panic/printer */
extern void FUN_0036b270();  /* out of slice; per-cpu/context acquire */
extern void FUN_0036b118(); /* out of slice; ref release */
extern void FUN_0036b6f4();  /* out of slice; error path */
extern void FUN_000fdb98(); /* out of slice; immediate completion */
extern void FUN_000ffba8();  /* out of slice; deferred completion */
/* --- capability/exception machinery (out of slice unless noted) --- */
extern uint64_t FUN_00027724();         /* out of slice; handler table lookup */
extern void thunk_FUN_002acbb8();           /* out of slice; IPC state transition */
extern uint64_t FUN_003a25d4();             /* out of slice; message-register block */
extern uint64_t FUN_0036a940();             /* out of slice; state query */
extern void FUN_002a4ab4();             /* out of slice; allocate tag block */
extern uint64_t FUN_001003e8();         /* out of slice; op register */
extern uint64_t FUN_000ff728();       /* out of slice */
extern void FUN_0006e7c0();  /* out of slice; capture frame */
extern void FUN_0009e98c();  /* out of slice; decode frame */
extern void FUN_0009e92c();             /* out of slice */
extern void FUN_000026e8();             /* out of slice */
extern void FUN_001004b8();                 /* out of slice */
extern void FUN_00077070(); /* out of slice */
extern uint64_t FUN_001000b8();             /* out of slice */
extern uint64_t (*DAT_006585a0)();              /* out of slice; indirect dispatch */
extern uint64_t (*DAT_006585c0)();              /* out of slice; indirect dispatch */
extern uint64_t FUN_000fd7b0();         /* out of slice; queue callback */
extern void FUN_000fc1cc();                 /* out of slice */
extern void FUN_000fce3c(uint64_t, uint64_t *, uint64_t, uint64_t, uint64_t,
                         uint64_t, uint64_t, uint64_t, uint64_t, uint64_t,
                         uint64_t);             /* out of slice; register handler */
extern uint64_t FUN_000e8248;                   /* in slice, 0xe8248 */
extern void FUN_0006a4c0();   /* out of slice */
extern uint64_t FUN_0009ea60();         /* out of slice; op->handler map */
extern void FUN_0009d1c0(); /* out of slice; forward result */
extern uint64_t FUN_0006f180();             /* out of slice */
extern void FUN_00205844(); /* out of slice */
extern void FUN_000fc644(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t,
                         uint64_t, uint64_t, uint64_t, uint64_t, uint64_t,
                         uint64_t, uint64_t);   /* out of slice; report */
extern uint64_t FUN_00053484();             /* out of slice; kernel state query */
extern uint64_t *FUN_0036993c(); /* out of slice */
extern void FUN_0036986c();                 /* out of slice; signal completion */
extern uint64_t FUN_000fd294(); /* out of slice; resolve record */
extern uint64_t FUN_00377824(); /* out of slice */
extern void FUN_0007c028();                 /* out of slice */
extern uint64_t FUN_001a0414();    /* out of slice; alloc */
extern void FUN_001a1854();   /* out of slice */
extern void FUN_001a5b90(); /* out of slice */
extern uint64_t FUN_00310d34();    /* out of slice */
extern uint64_t FUN_000eaf7c();         /* in slice, 0xeaf7c */
extern void FUN_0036b118();             /* out of slice; ref release */
extern uint64_t thunk_FUN_0036b270();           /* out of slice; ref acquire */
extern uint64_t FUN_000eb184(); /* in slice, 0xeb184 */
extern uint64_t FUN_003722e4(); /* out of slice */
extern uint64_t FUN_001f0130(); /* out of slice */
extern void FUN_000ec02c();                 /* in slice, 0xec02c */
extern void FUN_000ebed8();                 /* in slice, 0xebed8 */
extern void thunk_FUN_001ef804(); /* out of slice */
extern uint64_t FUN_000ebf54();             /* in slice, 0xebf54 */
extern void FUN_000ebf6c();                 /* in slice, 0xebf6c */
extern uint64_t FUN_0031a29c(); /* out of slice */
extern void FUN_000ebfbc();                 /* in slice, 0xebfbc */
extern void FUN_001cf6f4();                 /* out of slice */
extern void FUN_000db8e0();                 /* out of slice */
extern void FUN_000ebf3c();                 /* in slice, 0xebf3c */
extern void FUN_000ebf98();             /* in slice, 0xebf98 */
extern void FUN_000ec018();                 /* in slice, 0xec018 */
extern void FUN_000ebef0();                 /* in slice, 0xebef0 */
extern uint64_t FUN_000dbd8c();             /* out of slice */
extern void FUN_000ec038();                 /* in slice, 0xec038 */
extern void FUN_000aa3ac();                 /* out of slice */
extern void FUN_000ebf80();                 /* in slice, 0xebf80 */
extern void FUN_000ec004();                 /* in slice, 0xec004 */
extern uint64_t FUN_003a261c();         /* out of slice */
extern uint64_t FUN_000731dc(); /* out of slice; table grow */
extern uint64_t FUN_00073268(); /* out of slice; table grow */
extern void FUN_000ec044();                 /* in slice, 0xec044 */
extern uint64_t FUN_0031b614(); /* out of slice */
extern void FUN_00284f5c(); /* out of slice */
extern uint64_t FUN_00310d68(); /* out of slice */
extern uint64_t FUN_001a03fc(); /* out of slice */
extern void FUN_000ebf0c();                 /* in slice, 0xebf0c */
extern uint64_t FUN_0001a1c8(); /* out of slice */
extern void thunk_FUN_001fca54(); /* out of slice */
extern void FUN_001f6b30(); /* out of slice */
extern uint64_t FUN_001f7d28(); /* out of slice */
extern uint64_t FUN_001f0bb4(); /* out of slice */
extern void FUN_000eb19c(); /* in slice, 0xeb19c */
extern void FUN_000db870();             /* out of slice */
extern void FUN_000db888();             /* out of slice */
extern uint64_t FUN_00286e40(); /* out of slice */
extern uint64_t FUN_000ebf24();                 /* in slice, 0xebf24 */
extern uint64_t FUN_00376820(); /* out of slice */
extern void FUN_001d80e0(); /* out of slice */
extern uint64_t FUN_002871b4(); /* out of slice */
extern void FUN_000ebfcc();                 /* in slice, 0xebfcc */
extern void FUN_000ebff4();                 /* in slice, 0xebff4 */
extern uint64_t FUN_000ebfe8();             /* in slice, 0xebfe8 */
extern void thunk_FUN_00200b38(); /* out of slice */
extern void FUN_0031b760(); /* out of slice */
extern void FUN_00200bd0();           /* out of slice */
extern uint64_t FUN_0031b778(); /* out of slice */
extern void FUN_00200bf4(); /* out of slice */
extern void FUN_000eb2f4();           /* in slice, 0xeb2f4 */
extern void FUN_000eb2d8();   /* in slice, 0xeb2d8 */
extern uint64_t FUN_00002534(); /* out of slice */
extern uint64_t FUN_0036a9a0(); /* out of slice */
extern void FUN_0026b434(); /* out of slice */
extern void FUN_0036b588();             /* out of slice */
extern uint64_t FUN_00002688();             /* out of slice */
extern void FUN_0036b6ac(); /* out of slice */
extern uint64_t FUN_000ebd10(); /* in slice, 0xebd10 */
extern uint64_t FUN_000262fc(); /* out of slice; register-carry, variadic */
extern void FUN_000ebfac();                 /* in slice, 0xebfac */
extern uint64_t FUN_00377bec(); /* out of slice */
extern void FUN_000eb238();                 /* in slice, 0xeb238 */
extern void FUN_000eb268();                 /* in slice, 0xeb268 */
extern void FUN_000eb2a8();             /* in slice, 0xeb2a8 */
extern void FUN_000eb288();                 /* in slice, 0xeb288 */
extern uint64_t FUN_000eafac();         /* in slice, 0xeafac */
extern void SoftwareBreakpoint();       /* cL4 trap primitive */
extern void FUN_0036b6f4();                 /* out of slice; error path */
extern uint64_t FUN_000e7ad8();             /* in slice, 0xe7ad8 */
extern void FUN_000e8528();             /* in slice, 0xe8528 */
extern void FUN_000e8020(); /* in slice, 0xe8020 */
extern void FUN_000e80cc();   /* in slice, 0xe80cc */
extern uint64_t FUN_000e82d0();                 /* in slice, 0xe82d0 */
extern void FUN_000e7f98(); /* in slice, 0xe7f98 */
extern void FUN_000e89c8();             /* in slice, 0xe89c8 */
extern uint64_t FUN_000e8d78(uint64_t, uint64_t, uint64_t, uint8_t *,
                             uint64_t, uint64_t); /* in slice, 0xe8d78 */
extern uint64_t FUN_000e8268();  /* in slice, 0xe8268; panic diag trampoline */
extern void FUN_000e81dc();      /* in slice, 0xe81dc; install callback */
extern uint64_t FUN_000e88f4(uint64_t); /* in slice, 0xe88f4; table resolve */
extern void thunk_FUN_001dc298(); /* out of slice */
extern void FUN_000ea1bc();       /* in slice, 0xea1bc */
extern void FUN_000eb218();       /* in slice, 0xeb218 */
extern void FUN_000eb268();       /* in slice, 0xeb268 */
extern void FUN_000eb288();       /* in slice, 0xeb288 */
extern void FUN_000eb2a8();       /* in slice, 0xeb2a8 */
extern void FUN_000eb2d8();       /* in slice, 0xeb2d8 */
extern void FUN_000eb2f4();       /* in slice, 0xeb2f4 */
extern void FUN_000eb19c();       /* in slice, 0xeb19c */
extern void FUN_000eb238();       /* in slice, 0xeb238 */
extern void FUN_000ebed8();       /* in slice, 0xebed8 */
extern void FUN_000ebf0c();       /* in slice, 0xebf0c */
extern void FUN_000ebf3c();       /* in slice, 0xebf3c */
extern void FUN_000ebf6c();       /* in slice, 0xebf6c */
extern void FUN_000ebf80();       /* in slice, 0xebf80 */
extern void FUN_000ebf98();       /* in slice, 0xebf98 */
extern void FUN_000ebfac();       /* in slice, 0xebfac */
extern void FUN_000ebfbc();       /* in slice, 0xebfbc */
extern void FUN_000ebfcc();       /* in slice, 0xebfcc */
extern void FUN_000ebff4();       /* in slice, 0xebff4 */
extern void FUN_000ec004();       /* in slice, 0xec004 */
extern void FUN_000ec018();       /* in slice, 0xec018 */
extern void FUN_000ec02c();       /* in slice, 0xec02c */
extern void FUN_000ec038();       /* in slice, 0xec038 */
extern void FUN_000ec044();       /* in slice, 0xec044 */

/* --- additional out-of-slice helpers used by the 0xea* / 0xeb* decoders --- */
extern uint64_t FUN_00019850();   /* out of slice; list head */
extern uint64_t thunk_FUN_0001612c(); /* out of slice; list advance */
extern void FUN_0019ea20();       /* out of slice; extract entry */
extern void FUN_0019e924();       /* out of slice; advance */
extern uint64_t FUN_000267d4();   /* out of slice; validate */
extern uint64_t FUN_00019aac();   /* out of slice */
extern uint64_t FUN_0065a550();   /* out of slice; handler */
extern uint64_t FUN_0001fe3c();   /* out of slice; message header */
extern uint64_t FUN_000ebd54();       /* in slice, 0xebd54 */
extern uint64_t FUN_000ebd84();       /* in slice, 0xebd84 */
extern uint64_t FUN_000ebcbc();       /* in slice, 0xebcbc */
extern cl4_result_t FUN_00377dcc();   /* out of slice */
extern uint64_t FUN_00023c78();       /* out of slice; list header validate */
extern void FUN_000ebcec();       /* in slice, 0xebcec */

/* --- additional out-of-slice message/cap helpers --- */
extern uint64_t thunk_FUN_0001a1c8(); /* out of slice; message builder */
extern uint64_t FUN_0001b620();   /* out of slice; message op */
extern void FUN_0001ac14();       /* out of slice; install callback */
extern void FUN_00025704();       /* out of slice */
extern uint64_t FUN_0001ab94();   /* out of slice; header builder */
extern uint64_t FUN_0001b360();   /* out of slice; header builder */
extern void FUN_0001a72c();       /* out of slice; word decoder */
extern uint64_t FUN_0001a47c();   /* out of slice; message alloc */
extern uint64_t FUN_000e8978();       /* in slice, 0xe8978 */
extern void FUN_000eafdc();       /* in slice, 0xeafdc */


/* --- sort/range helper externs --- */
extern uint64_t FUN_000f9930();   /* out of slice; table deref */
extern uint64_t FUN_000f9680();   /* out of slice; table grow */
extern uint64_t FUN_000f958c();   /* out of slice; table alloc */
extern void FUN_00117d14();       /* out of slice; memmove */
extern int64_t FUN_0029369c();    /* out of slice; capacity measure */
extern uint64_t FUN_0007be8c();   /* out of slice; table normalize */
extern void FUN_000eba8c();       /* in slice, 0xeba8c */
extern void FUN_000eb79c();       /* in slice, 0xeb79c */
extern void FUN_000ebb34();       /* in slice, 0xebb34 */


/* --- remaining in/out of slice dispatch externs --- */
extern void FUN_000eac74();   /* in slice, 0xeac74 */
extern void FUN_000ea2f8();   /* in slice, 0xea2f8 */
extern void FUN_000ea5c8();   /* in slice, 0xea5c8 */
extern void FUN_000ea694();   /* in slice, 0xea694 */
extern uint64_t FUN_00021480(); /* out of slice; table base */
extern void FUN_000db8f8();   /* out of slice; copy completion */
extern cl4_result_t FUN_00374104(); /* out of slice; typed alloc */


extern void FUN_000eb82c();   /* in slice, 0xeb82c */
extern void FUN_000eb3ac();   /* in slice, 0xeb3ac */

/* --- final out/other slice externs --- */
extern void FUN_00072044();     /* out of slice; copy run */
extern uint64_t thunk_FUN_0036f974(); /* out of slice; register query */
extern void FUN_0035cf24();     /* out of slice; register store */
extern uint64_t FUN_00027614(); /* out of slice; object resolve */
extern void FUN_000ea4dc();     /* in slice, 0xea4dc */

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

/* FUN_000e7cfc @ 0x000e7cfc   (est. cl4_caps_op_stateful_wrap)
 * Ghidra: void FUN_000e7cfc(void)
 * Tail thunk to FUN_000e7c34 (0xe7c34), the stateful capability operation.
 * Confidence: high
 * Notes: single tail call. */
void cl4_caps_op_stateful_wrap(void)
{
    cl4_caps_op_stateful();  /* 0xe7c34 */
}

/* FUN_000e7d20 @ 0x000e7d20   (est. cl4_exception_setup)
 * Ghidra: void FUN_000e7d20(undefined8 p1, undefined8 p2)
 * Exception/syscall setup path. Captures the current fault frame into a
 * stack buffer (FUN_0006e7c0), queries the operation register
 * (FUN_001003e8(0)), and fetches the exception record (FUN_0036a940 +
 * FUN_000ff728). On the happy path (companion reg unaff_x21==0) it stores
 * the record into the context (x20+0x10), decodes the secondary frame
 * (FUN_0009e98c) and, depending on the local status (local_98), either
 * completes immediately or defers via a queued callback (FUN_000fd7b0 with
 * FUN_000e81dc). Panic diagnostics use FUN_000e8268 with the BuildRoot
 * source string (0x5c4870). References are released on both branches.
 * Confidence: low
 * Notes: unaff_x20/x21 caller-preserved context registers; several
 * unreachable blocks removed by decompiler. */
void cl4_exception_setup(uint64_t p1, uint64_t p2)
{
    uint8_t frame_a[24];
    uint8_t frame_b[40];
    uint64_t ctx = 0;      /* unaff_x20 */
    uint64_t ctx_flag = 0; /* unaff_x21 */
    uint64_t rec, u;
    uint64_t local_status;

    FUN_0006e7c0(p1, frame_b);  /* out of slice; capture fault frame */
    rec = FUN_001003e8(0);      /* out of slice; op/exception register */
    u = FUN_0036a940(rec, 0x52, 7);  /* out of slice */
    rec = FUN_000ff728(6, frame_b);  /* out of slice; fetch exception record */
    if (ctx_flag == 0) {
        *(uint64_t *)(ctx + 0x10) = rec;
        FUN_0009e98c(p2, frame_a);  /* out of slice; decode secondary frame */
        if (local_status == 0) {
            FUN_0009e92c(frame_a);  /* out of slice */
            FUN_0036b270();         /* out of slice */
            FUN_000e8268(0xd000000000000028ULL, 0x80000000005c1900ULL,
                         (uint64_t)0x5c4870 /* BuildRoot path */);  /* panic */
            FUN_001004b8();         /* out of slice */
            FUN_0009e92c(p2);       /* out of slice */
            FUN_000026e8(p1);       /* out of slice */
        } else {
            FUN_00077070(frame_a, frame_b);  /* out of slice */
            FUN_001000b8(0);        /* out of slice */
            (*DAT_006585a0)();      /* out of slice; indirect dispatch */
            u = FUN_000fd7b0(FUN_000e81dc);  /* out of slice; queue callback */
            FUN_0036b270();
            FUN_0036b270(u);
            FUN_000e8268(0xd00000000000001fULL, 0x80000000005c1a90ULL,
                         (uint64_t)0x5c4870);  /* panic */
            FUN_000fc1cc();         /* out of slice */
            FUN_0036b118(u);        /* out of slice; ref release */
            FUN_0009e92c(p2);
            FUN_000026e8(p1);
            FUN_000026e8(frame_b);
        }
        FUN_0036b118(*(uint64_t *)(ctx + 0x10));  /* ref release */
    } else {
        FUN_0009e92c(p2);
        FUN_000026e8(p1);
    }
    FUN_0036b6f4();  /* out of slice */
}

/* FUN_000e7f98 @ 0x000e7f98   (est. cl4_exception_handler_install)
 * Ghidra: void FUN_000e7f98(undefined8 p1, undefined8 p2, undefined8 p3)
 * Installs an exception handler. Records p2/p1/p3 into a stack frame, then
 * registers FUN_000e8248 as the callback through FUN_000fce3c with the
 * panic diagnostic (status 0xd000000000000017, addr 0x80000000005c08d0,
 * BuildRoot path 0x5c4870, line 0x11f, verbosity 2) and the message string
 * "init_physAllocator_exceptionHand..." (0x5c49d0, 0x30, 2, 0x36).
 * Confidence: low
 * Notes: FUN_000fce3c is the handler-registration/panic printer. */
void cl4_exception_handler_install(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t args[4];
    args[0] = p2;
    args[1] = p1;
    args[2] = p3;
    FUN_000fce3c(FUN_000e8248, args, 0xd000000000000017ULL,
                 0x80000000005c08d0ULL, (uint64_t)0x5c4870 /* BuildRoot */,
                 0x11f, 2, (uint64_t)0x5c49d0 /* "init_physAllocator_exceptionHand..." */,
                 0x30, 2, 0x36);  /* out of slice; register handler + panic diag */
}

/* FUN_000e8020 @ 0x000e8020   (est. cl4_exception_dispatch_op)
 * Ghidra: void FUN_000e8020(long p1, undefined8 p2, undefined8 p3)
 * Dispatches a capability operation. Reads the operation id (p1+0x18) and
 * the associated object (p1+0x20), releases/validates p1 via FUN_0006a4c0,
 * resolves the per-id handler through FUN_0009ea60, invokes it with the
 * op id and object, then forwards the result through FUN_0009d1c0(p2,p3).
 * Confidence: low
 * Notes: FUN_0009ea60 maps an op id to a handler function pointer. */
void cl4_exception_dispatch_op(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t opid = *(uint64_t *)(p1 + 0x18);
    uint64_t obj = *(uint64_t *)(p1 + 0x20);
    uint64_t (*handler)(uint64_t, uint64_t);

    FUN_0006a4c0(p1, opid);  /* out of slice */
    handler = (uint64_t (*)(uint64_t, uint64_t))FUN_0009ea60(obj);  /* out of slice */
    opid = handler(opid, obj);
    FUN_0009d1c0(opid, p2, p3);  /* out of slice; forward result */
}

/* FUN_000e8094 @ 0x000e8094   (est. cl4_exception_dispatch_op_wrap)
 * Ghidra: void FUN_000e8094(undefined8 p1)
 * Tail thunk to FUN_000e80cc(p1, 1): dispatches the capability operation
 * with the "shared/checked" flag set.
 * Confidence: medium
 * Notes: single tail call to 0xe80cc with constant 1. */
void cl4_exception_dispatch_op_wrap(uint64_t p1)
{
    FUN_000e80cc(p1, 1);  /* 0xe80cc */
}

/* FUN_000e80b0 @ 0x000e80b0   (est. cl4_exception_dispatch_unchecked)
 * Ghidra: void FUN_000e80b0(undefined8 p1)
 * Tail thunk to FUN_000e80cc(p1, 0): dispatches with the "unchecked" flag
 * (0), i.e. the exception came in on an unchecked/unshared path.
 * Confidence: medium
 * Notes: single tail call to 0xe80cc with constant 0. */
void cl4_exception_dispatch_unchecked(uint64_t p1)
{
    FUN_000e80cc(p1, 0);  /* 0xe80cc */
}

/* FUN_000e80cc @ 0x000e80cc   (est. cl4_exception_dispatch)
 * Ghidra: void FUN_000e80cc(undefined8 *p1, undefined8 p2)
 * Core exception dispatcher. Acquires the exception context for the
 * LAB_00651c08 state label (FUN_0036a940/FUN_0036b270), runs the async-op
 * setup FUN_000e7ad8, and, on the happy path (companion reg unaff_x21==0),
 * records the dispatch into p1: p1[3]=0x651c08, p1[4]=0x661df8 (handler
 * table), *p1=result. p2 selects the checked/unchecked variant.
 * Confidence: low
 * Notes: unaff_x21 caller-preserved context register; LAB_00651c08 is a
 * dispatch state label. */
void cl4_exception_dispatch(uint64_t *p1, uint64_t p2)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t result;

    FUN_0036a940(0x651c08, 0x51, 7);  /* out of slice */
    FUN_0036b270();                        /* out of slice */
    FUN_0036b270(p2);                      /* out of slice */
    result = FUN_000e7ad8();               /* 0xe7ad8 */
    if (ctx_flag == 0) {
        p1[3] = (uint64_t)0x651c08;
        p1[4] = 0x661df8;   /* handler table */
        p1[0] = result;
    }
}

/* FUN_000e8168 @ 0x000e8168   (est. cl4_exc_err_unknown_op)
 * Ghidra: undefined1[16] FUN_000e8168(void)
 * Returns a fixed capability-operation error code: {lo=0xd<<60|0x1c,
 * hi=0x80000000004c31b0}. Represents an unknown/invalid operation error
 * result returned to the caller.
 * Confidence: medium
 * Notes: constant-only return; shared by several error-reporting thunks. */
cl4_result_t cl4_exc_err_unknown_op(void)
{
    cl4_result_t r;
    r.hi = 0x80000000004c31b0ULL;
    r.lo = 0xd00000000000001cULL;
    return r;
}

/* FUN_000e8184 / FUN_000e8188 @ 0xe8184 / 0xe8188  (est. cl4_exc_err_dispatch_a/b)
 * Ghidra: void FUN_000e8184(void) / void FUN_000e8188(void)
 * Tail thunks to FUN_000e8094(): both report the current operation error
 * through the shared checked dispatcher (0xe8094). The two entry points
 * represent distinct error sources reaching the same handler.
 * Confidence: medium
 * Notes: single tail call each to 0xe8094. */
void cl4_exc_err_dispatch_a(void)
{
    cl4_exception_dispatch_op_wrap(0);  /* 0xe8094 */
}
void cl4_exc_err_dispatch_b(void)
{
    cl4_exception_dispatch_op_wrap(0);  /* 0xe8094 */
}

/* FUN_000e819c / FUN_000e81a0 @ 0xe819c / 0xe81a0  (est. cl4_exc_err_unchecked_a/b)
 * Ghidra: void FUN_000e819c(void) / void FUN_000e81a0(void)
 * Tail thunks to FUN_000e80b0(): report the current operation error through
 * the unchecked dispatcher (0xe80b0). Two entry points for distinct error
 * sources.
 * Confidence: medium
 * Notes: single tail call each to 0xe80b0. */
void cl4_exc_err_unchecked_a(void)
{
    cl4_exception_dispatch_unchecked(0);  /* 0xe80b0 */
}
void cl4_exc_err_unchecked_b(void)
{
    cl4_exception_dispatch_unchecked(0);  /* 0xe80b0 */
}

/* FUN_000e81b4 / FUN_000e81b8 @ 0xe81b4 / 0xe81b8  (est. cl4_exc_err_status_a/b)
 * Ghidra: undefined8 FUN_000e81b4(void) / undefined8 FUN_000e81b8(void)
 * Both call FUN_000e8168 (report unknown-op error) and return the error
 * status word 0xd00000000000001c as the function result.
 * Confidence: medium
 * Notes: return value is the .lo of the cl4_result produced by 0xe8168. */
uint64_t cl4_exc_err_status_a(void)
{
    cl4_exc_err_unknown_op();  /* 0xe8168 */
    return 0xd00000000000001cULL;
}
uint64_t cl4_exc_err_status_b(void)
{
    cl4_exc_err_unknown_op();  /* 0xe8168 */
    return 0xd00000000000001cULL;
}

/* FUN_000e81dc / FUN_000e81e0 @ 0xe81dc / 0xe81e0  (est. cl4_exc_install_cb_a/b)
 * Ghidra: void FUN_000e81dc(undefined8 p1) / void FUN_000e81e0(undefined8 p1)
 * Exception-handler callbacks: forward p1 plus the two context fields
 * (x20+0x10, x20+0x18) to the handler-install routine FUN_000e7f98. Two
 * entry points for distinct install sites.
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register. */
void cl4_exc_install_cb_a(uint64_t p1)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000e7f98(p1, *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18));  /* 0xe7f98 */
}
void cl4_exc_install_cb_b(uint64_t p1)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000e7f98(p1, *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18));  /* 0xe7f98 */
}

/* FUN_000e81f8 @ 0x000e81f8   (est. cl4_const_0x651c08)
 * Ghidra: undefined1[16] FUN_000e81f8(void)
 * Returns the constant 0x651c08 zero-extended to a word pair (lo=0x651c08,
 * hi=0). This is the address of the LAB_00651c08 dispatch state label used
 * by the exception dispatcher.
 * Confidence: medium
 * Notes: ZEXT816(0x651c08); matches 0x651c08 used at 0xe80cc. */
cl4_result_t cl4_const_0x651c08(void)
{
    cl4_result_t r;
    r.lo = 0x651c08;
    r.hi = 0;
    return r;
}

/* FUN_000e8268 @ 0x000e8268   (est. cl4_exc_panic_diag)
 * Ghidra: undefined FUN_000e8268(void)
 * Exception-diagnostic panic trampoline. The decompiler collapses the body
 * to `void(void){return;}` but the disassembly (0xe8268-0xe827f) shows it
 * loading the fixed panic-call constants w3=0x11f (line), w4=2 (verbosity),
 * w6=0x30, w7=2, copying x21=x23 (carrying the panic/return context), and
 * returning via ret. It is invoked from every exception-handler site with
 * (status, addr, BuildRoot-string) in args 0-2 and emits the diagnostic
 * through the caller continuation state carried in x23.
 * Confidence: low
 * Notes: false no-op decompile; body reconstructed from disassembly. */
void cl4_exc_panic_diag(void)
{
    /* w3=0x11f, w4=2, w6=0x30, w7=2 loaded as panic-call constants;
     * x21=x23 carries the caller continuation/return context. Actual
     * diagnostic emission happens through x23 after `ret`. */
    __asm__ volatile("" ::: "memory");
}

/* FUN_000e8238 @ 0x000e8238   (est. cl4_const_0x651ba0)
 * Ghidra: undefined1[16] FUN_000e8238(void)
 * Returns the constant 0x651ba0 zero-extended to a word pair (lo=0x651ba0,
 * hi=0). A fixed dispatch/data address.
 * Confidence: low
 * Notes: ZEXT816(0x651ba0). */
cl4_result_t cl4_const_0x651ba0(void)
{
    cl4_result_t r;
    r.lo = 0x651ba0;
    r.hi = 0;
    return r;
}

/* FUN_000e8248 / FUN_000e824c @ 0xe8248 / 0xe824c  (est. cl4_exc_dispatch_ctx_a/b)
 * Ghidra: void FUN_000e8248(void) / void FUN_000e824c(void)
 * Context-driven exception dispatchers: forward the three context fields
 * (x20+0x10, x20+0x18, x20+0x20) to FUN_000e8020 (the capability op
 * dispatcher). Two entry points for distinct call sites.
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register. */
void cl4_exc_dispatch_ctx_a(void)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000e8020(*(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20));  /* 0xe8020 */
}
void cl4_exc_dispatch_ctx_b(void)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000e8020(*(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18),
                 *(uint64_t *)(ctx + 0x20));  /* 0xe8020 */
}

/* FUN_000e8280 @ 0x000e8280   (est. cl4_exc_pre_dispatch)
 * Ghidra: undefined8 FUN_000e8280(undefined8 p1)
 * Saves the value from out-of-slice FUN_0036a940, forwards p1 to
 * FUN_000e8528 (0xe8528, the dispatch entry), and returns the saved value.
 * Confidence: low
 * Notes: FUN_0036a940 result preserved across the 0xe8528 call and returned. */
uint64_t cl4_exc_pre_dispatch(uint64_t p1)
{
    uint64_t saved = FUN_0036a940();  /* out of slice */
    FUN_000e8528(p1);                 /* in slice, 0xe8528 */
    return saved;
}

/* FUN_000e82d0 @ 0x000e82d0   (est. cl4_caps_async_op_setup_v10)
 * Ghidra: void FUN_000e82d0(undefined8 p1, long *p2)
 * Variant of the async capability-op setup (cf. 0xe7ad8) using op kind 10.
 * Stores p1 into the context (x20+0x10), invokes the method at *p2+0x1b8
 * with a 16-byte result buffer, and on the happy path (unaff_x21==0)
 * commits the result into the context (offsets 0x18..0x49), then calls the
 * completion method at *(**ctx+0x10)+0x70 on the captured object before
 * releasing references.
 * Confidence: low
 * Notes: fallback pattern; one unreachable block at 0xe83f8 removed. */
void cl4_caps_async_op_setup_v10(uint64_t p1, uint64_t *p2)
{
    uint8_t result_buf[16];
    uint64_t ctx = 0;      /* unaff_x20 */
    uint64_t ctx_flag = 0; /* unaff_x21 */
    void (*op)(uint8_t *, int, int, int, int, int);
    uint64_t *obj;
    void (*done)(uint8_t *);

    *(uint64_t *)(ctx + 0x10) = p1;
    op = *(void (**)(uint8_t *, int, int, int, int, int))(*p2 + 0x1b8);
    FUN_0036b270();  /* out of slice */
    op(result_buf, 10, 0, 0, 0, 0);
    if (ctx_flag == 0) {
        *(uint64_t *)(ctx + 0x20) = *(uint64_t *)(result_buf + 8);
        *(uint64_t *)(ctx + 0x18) = *(uint64_t *)(result_buf + 0);
        *(uint64_t *)(ctx + 0x30) = *(uint64_t *)(result_buf + 0x18);
        *(uint64_t *)(ctx + 0x28) = *(uint64_t *)(result_buf + 0x10);
        *(uint64_t *)(ctx + 0x40) = *(uint64_t *)(result_buf + 0x28);
        *(uint64_t *)(ctx + 0x38) = *(uint64_t *)(result_buf + 0x20);
        *(uint64_t *)(ctx + 0x49) = *(uint64_t *)(result_buf + 0x37);
        *(uint64_t *)(ctx + 0x41) = *(uint64_t *)(result_buf + 0x30);
        obj = *(uint64_t **)(*(uint64_t *)(ctx + 0x10) + 0x10);
        done = *(void (**)(uint8_t *))(*obj + 0x70);
        FUN_0036b270(obj);  /* out of slice */
        done(result_buf);
        FUN_0036b118(obj);  /* out of slice; ref release */
        FUN_0036b118(p1);
        FUN_0036b118(p2);
    } else {
        FUN_0036b118(p1);
        FUN_0036b118(p2);
        FUN_0036b118(*(uint64_t *)(ctx + 0x10));
        FUN_0036b6f4();  /* out of slice; error path */
    }
}

/* FUN_000e843c @ 0x000e843c   (est. cl4_caps_op_stateful_hibr)
 * Ghidra: undefined1[16] FUN_000e843c(void)
 * Stateful capability operation (hibernation variant). Same skeleton as
 * 0xe7c34: alloc tag-0x1d, consult MR block (0xe0... prefix), run the
 * 0x671df8-table handler, two IPC state transitions, returning the packed
 * {status=0xd<<60|0x28, addr=0x80000000005c49f0}.
 * Confidence: low
 * Notes: mirrors 0xe7c34/0xe7874 state-machine pattern. */
cl4_result_t cl4_caps_op_stateful_hibr(void)
{
    void (*handler)(uint64_t, uint64_t);
    uint64_t h, carry = 0;

    FUN_002a4ab4(0x1d);  /* out of slice */
    h = FUN_003a25d4(0xe000000000000000ULL);  /* out of slice; MR block */
    handler = (void (*)(uint64_t, uint64_t))FUN_00027724(0x671df8);  /* out of slice */
    handler(0x677830, 0x671df8);
    thunk_FUN_002acbb8();  /* out of slice; IPC transition */
    h = FUN_003a25d4(carry);  /* out of slice */
    thunk_FUN_002acbb8(0x29, 0xe100000000000000ULL);  /* out of slice */
    cl4_result_t r;
    r.hi = 0x80000000005c49f0ULL;
    r.lo = 0xd000000000000028ULL;
    return r;
}

/* FUN_000e8504 @ 0x000e8504   (est. cl4_caps_op_stateful_hibr_wrap)
 * Ghidra: void FUN_000e8504(void)
 * Tail thunk to FUN_000e843c.
 * Confidence: high
 * Notes: single tail call. */
void cl4_caps_op_stateful_hibr_wrap(void)
{
    cl4_caps_op_stateful_hibr();  /* 0xe843c */
}

/* FUN_000e8528 @ 0x000e8528   (est. cl4_exception_dispatch_check)
 * Ghidra: void FUN_000e8528(ulong p1)
 * Exception dispatch with mode selection. Queries the kernel state via
 * FUN_00053484(0). If absent, records a fixed error result
 * {0xd000000000000023, 0x80000000005c4a20} through FUN_0036993c and signals
 * completion (FUN_0036986c). Otherwise selects mode 3 (or 4 when p1 bit 0
 * set) and resolves the target record via FUN_000fd294 after FUN_001000b8;
 * on the happy path (unaff_x21==0) the resolved value is stored into the
 * context (x20+0x10).
 * Confidence: low
 * Notes: unaff_x20/x21 caller-preserved context registers. */
void cl4_exception_dispatch_check(uint64_t p1)
{
    uint64_t ctx = 0;      /* unaff_x20 */
    uint64_t ctx_flag = 0; /* unaff_x21 */
    uint64_t *err;
    uint64_t l, u2, u3;

    l = FUN_00053484(0);  /* out of slice; kernel state query */
    if (l == 0) {
        err = FUN_0036993c(0x662d28, 0x662a78, 0, 0);  /* out of slice */
        err[0] = 0xd000000000000023ULL;
        err[1] = 0x80000000005c4a20ULL;
        *(uint8_t *)((uint64_t)err + 16) = 1;
        FUN_0036986c();  /* out of slice; signal completion */
    } else {
        u3 = 3;
        if ((p1 & 1) != 0) {
            u3 = 4;
        }
        u2 = FUN_001000b8(0);  /* out of slice */
        u3 = FUN_000fd294(u2, l, u3);  /* out of slice; resolve record */
        if (ctx_flag == 0) {
            *(uint64_t *)(ctx + 0x10) = u3;
            return;
        }
    }
    FUN_0036b6f4();  /* out of slice */
}

/* FUN_000e8620 @ 0x000e8620   (est. cl4_exc_hibernation_init)
 * Ghidra: void FUN_000e8620(undefined8 p1, undefined8 p2, undefined8 p3)
 * Hibernation-init exception handler. Builds a message frame (local_50=0,
 * status prefix 0xe0...), allocates a tag-0x2f block, performs an IPC state
 * transition {0xd<<60|0x2d, 0x80000000005c4a50}, sets up p3 as a message,
 * and drives the init through FUN_0006f180/FUN_00205844 then reports via
 * FUN_000fc644 with the "init_hibernation_..." string (0x5c4bc0), BuildRoot
 * path (0x5c4aa0), line 0x113, and forwarded p2/p1/p3 arguments.
 * Confidence: low
 * Notes: FUN_000fc644 is the init/report printer; string refs at 0x5c4aa0
 * and 0x5c4bc0. */
void cl4_exc_hibernation_init(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t frame = 0;
    uint64_t status = 0xe000000000000000ULL;
    uint64_t msg = p3;
    uint64_t v;

    FUN_002a4ab4(0x2f);  /* out of slice; alloc tag-0x2f */
    thunk_FUN_002acbb8(0xd00000000000002dULL, 0x80000000005c4a50ULL);  /* IPC transition */
    v = FUN_0006f180(0);  /* out of slice */
    FUN_00205844(&msg, &frame, v, 0x6756a8, 0x66e1b8);  /* out of slice */
    v = status;
    FUN_000fc644(frame, status, (uint64_t)0x5c4aa0 /* BuildRoot */, 0x113, 2,
                 (uint64_t)0x5c4bc0 /* "init_hibernation_..." */, 0x12, 2, 0x34,
                 p2, p1, p3);  /* out of slice; report */
    FUN_003a25d4(v);  /* out of slice */
}

/* FUN_000e8724 @ 0x000e8724   (est. cl4_exception_dispatch_alt)
 * Ghidra: void FUN_000e8724(undefined8 *p1, undefined8 p2)
 * Alternate exception dispatcher (cf. 0xe80cc) using the 0x651cd0 state
 * label and the async-op setup 0xe82d0. On the happy path (unaff_x21==0)
 * records p1[3]=0x651cd0, p1[4]=0x661e68 (handler table), *p1=result.
 * Confidence: low
 * Notes: unaff_x21 caller-preserved context register. */
void cl4_exception_dispatch_alt(uint64_t *p1, uint64_t p2)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t result;

    FUN_0036a940(0x651cd0, 0x51, 7);  /* out of slice */
    FUN_0036b270();  /* out of slice */
    FUN_0036b270(p2);
    result = FUN_000e82d0();  /* 0xe82d0 */
    if (ctx_flag == 0) {
        p1[3] = 0x651cd0;
        p1[4] = 0x661e68;   /* handler table */
        p1[0] = result;
    }
}

/* FUN_000e87b8 @ 0x000e87b8   (est. cl4_exc_err_cap_not_found)
 * Ghidra: undefined1[16] FUN_000e87b8(void)
 * Returns a fixed capability error result: {lo=0xd<<60|0x10,
 * hi=0x80000000004c32a0}. Indicates a capability-not-found style error.
 * Confidence: medium
 * Notes: constant-only return. */
cl4_result_t cl4_exc_err_cap_not_found(void)
{
    cl4_result_t r;
    r.hi = 0x80000000004c32a0ULL;
    r.lo = 0xd000000000000010ULL;
    return r;
}

/* FUN_000e87d4 / FUN_000e87d8 @ 0xe87d4 / 0xe87d8  (est. cl4_exc_dispatch_alt_a/b)
 * Ghidra: void FUN_000e87d4(void) / void FUN_000e87d8(void)
 * Tail thunks to FUN_000e8724 (alternate exception dispatcher). Two entry
 * points for distinct call sites.
 * Confidence: medium
 * Notes: single tail call each to 0xe8724. */
void cl4_exc_dispatch_alt_a(void)
{
    cl4_exception_dispatch_alt(0, 0);  /* 0xe8724 */
}
void cl4_exc_dispatch_alt_b(void)
{
    cl4_exception_dispatch_alt(0, 0);  /* 0xe8724 */
}

/* FUN_000e87ec / FUN_000e87f0 @ 0xe87ec / 0xe87f0  (est. cl4_exc_err_capnf_status_a/b)
 * Ghidra: undefined8 FUN_000e87ec(void) / undefined8 FUN_000e87f0(void)
 * Both call FUN_000e87b8 (capability-not-found error report) and return the
 * error status word 0xd000000000000010 as the result.
 * Confidence: medium
 * Notes: return value is the .lo of the cl4_result from 0xe87b8. */
uint64_t cl4_exc_err_capnf_status_a(void)
{
    cl4_exc_err_cap_not_found();  /* 0xe87b8 */
    return 0xd000000000000010ULL;
}
uint64_t cl4_exc_err_capnf_status_b(void)
{
    cl4_exc_err_cap_not_found();  /* 0xe87b8 */
    return 0xd000000000000010ULL;
}

/* FUN_000e884c @ 0x000e884c   (est. cl4_const_0x651c70)
 * Ghidra: undefined1[16] FUN_000e884c(void)
 * Returns the constant 0x651c70 zero-extended to a word pair. A fixed
 * dispatch/data address.
 * Confidence: low
 * Notes: ZEXT816(0x651c70). */
cl4_result_t cl4_const_0x651c70(void)
{
    cl4_result_t r;
    r.lo = 0x651c70;
    r.hi = 0;
    return r;
}

/* FUN_000e8874 @ 0x000e8874   (est. cl4_exc_cap_op_dispatch)
 * Ghidra: void FUN_000e8874(void)
 * Dispatches a capability operation from the current context: reads the
 * object (*unaff_x20), takes the operation id at obj+0x40, resolves the
 * handler via FUN_000e88f4, and invokes it with (obj+0x38, opid).
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register. */
void cl4_exc_cap_op_dispatch(void)
{
    uint64_t *ctx = 0;  /* unaff_x20 */
    uint64_t obj = *ctx;
    uint64_t opid = *(uint64_t *)(obj + 0x40);
    void (*handler)(uint64_t, uint64_t);

    handler = (void (*)(uint64_t, uint64_t))FUN_000e88f4(opid);  /* 0xe88f4 */
    handler(*(uint64_t *)(obj + 0x38), opid);
}

/* FUN_000e88f4 @ 0x000e88f4   (est. cl4_table_entry_resolve)
 * Ghidra: long FUN_000e88f4(ulong p1)
 * Resolves a table entry pointer. If the low bit of p1 is set, dereferences
 * p1&~1 (a pointer to the table base). Returns base+0x28 plus the signed
 * 32-bit length/offset field at base+0x28 — i.e. the first element address
 * of a variable-size entry table.
 * Confidence: low
 * Notes: classic seL4-style offset-encoded table; the (int) at +0x28 is a
 * byte length used to skip to the first entry. */
uint64_t cl4_table_entry_resolve(uint64_t p1)
{
    if ((p1 & 1) != 0) {
        p1 = *(uint64_t *)(p1 & 0xfffffffffffffffeULL);
    }
    return (p1 + 0x28) + (int64_t)*(int32_t *)(p1 + 0x28);
}

/* FUN_000e8978 @ 0x000e8978   (est. cl4_exc_pre_dispatch_2)
 * Ghidra: undefined8 FUN_000e8978(undefined8 p1)
 * Saves the value from out-of-slice FUN_0036a940, forwards p1 to
 * FUN_000e89c8 (0xe89c8, the argument-table walk), and returns the saved
 * value.
 * Confidence: low
 * Notes: FUN_0036a940 result preserved across the 0xe89c8 call. */
uint64_t cl4_exc_pre_dispatch_2(uint64_t p1)
{
    uint64_t saved = FUN_0036a940();  /* out of slice */
    FUN_000e89c8(p1);                 /* in slice, 0xe89c8 */
    return saved;
}

/* FUN_000ea114 @ 0x000ea114   (est. cl4_exc_cap_op_dispatch_4arg)
 * Ghidra: void FUN_000ea114(undefined8 p1, undefined8 p2)
 * Dispatches a 4-argument capability operation: reads the object (*x20),
 * takes the operation id at obj+0x40, resolves the handler via
 * FUN_000eafac, and invokes it with (p1, p2, obj+0x38, opid).
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register. */
void cl4_exc_cap_op_dispatch_4arg(uint64_t p1, uint64_t p2)
{
    uint64_t *ctx = 0;  /* unaff_x20 */
    uint64_t obj = *ctx;
    uint64_t opid = *(uint64_t *)(obj + 0x40);
    void (*handler)(uint64_t, uint64_t, uint64_t, uint64_t);

    handler = (void (*)(uint64_t, uint64_t, uint64_t, uint64_t))FUN_000eafac(opid);  /* 0xeafac */
    handler(p1, p2, *(uint64_t *)(obj + 0x38), opid);
}

/* FUN_000e89c8 @ 0x000e89c8   (est. cl4_caps_arg_table_walk)
 * Ghidra: long * FUN_000e89c8(long param_1)
 * Walks a capability-operation argument table at param_1+0x40 (records of 5
 * words; count at param_1+0x10) and processes each record through
 * FUN_000e8d78. Acquires references on each record's fields, drives the
 * message/state machinery (thunk_FUN_0036b270 / FUN_003a25d4), and advances
 * the stack allocation via the callback table (extraout_x16+0x10/+8). When
 * all records are consumed it releases the arg table, resolves the handler
 * via FUN_000eaf7c and invokes it with the collected arguments, then
 * dispatches the continuation at (local_c8+0x20). On a mid-walk failure
 * (unaff_x21!=0) it releases and falls to the error path. Hitting the loop
 * bound with an unconsumed record traps (SoftwareBreakpoint at 0xe8d78).
 * Confidence: low
 * Notes: large control-flow; DAT_006585c0 is an indirect dispatch/call
 * helper; several stack pointers derived from register carries. */
uint64_t *cl4_caps_arg_table_walk(uint64_t param_1)
{
    uint64_t *ctx = 0;  /* unaff_x20 */
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t obj = *ctx;
    uint64_t tcb = *(uint64_t *)(obj + 0x38);
    uint64_t tcb_hdr = *(uint64_t *)(tcb - 8);
    void (*disp)(void);  /* DAT_006585c0 */
    uint64_t u13, u5, u6, u2, u7, u1, u11, v;
    uint64_t u15 = 0;
    uint64_t count = *(uint64_t *)(param_1 + 0x10);
    uint64_t *rec = (uint64_t *)(param_1 + 0x40);
    uint64_t stack_a, stack_b;

    (*DAT_006585c0)();  /* out of slice; indirect dispatch */
    u13 = *(uint64_t *)(/* extraout_x8 */ 0 + 0x40);
    u5 = FUN_00377824(0, u13, tcb, 0x0, 0x0);  /* out of slice */
    FUN_0007c028(u5, u5);  /* out of slice */
    (*DAT_006585c0)(*(uint64_t *)(/* extraout_x8_00 */ 0 + 0x40));
    stack_a = /* ... */ 0;
    (*DAT_006585c0)();
    stack_b = stack_a;  /* - extraout_x12_00 */
    u5 = FUN_001a0414(0);  /* out of slice; alloc */
    u13 = FUN_00377824(0, u13, tcb, 0x0, 0x0);  /* out of slice */
    uint64_t local_68 = FUN_001a0414(0);  /* out of slice; alloc */
    for (;;) {
        if (count == u15) {
            FUN_0036b118(param_1);  /* out of slice; ref release */
            void (*h)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
            h = (void (*)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))FUN_000eaf7c(u13);
            h(/* local_d0 */ 0, u5, local_68, tcb, u13);
            (**(void (**)(uint64_t, uint64_t, uint64_t))(tcb_hdr + 0x20))(
                (uint64_t)ctx + *(uint64_t *)(*ctx + 0x48), /* puVar3 */ 0, tcb);
            return ctx;
        }
        if (*(uint64_t *)(param_1 + 0x10) <= u15) break;
        u7 = rec[-2];
        u1 = rec[-1];
        u11 = rec[0];
        u6 = rec[-4];
        u2 = rec[-3];
        thunk_FUN_0036b270(u2);  /* out of slice; ref acquire */
        FUN_0036b270(u7);
        FUN_0036b270(u1);
        u6 = FUN_000e8d78(stack_b, u6, u2, (uint8_t *)u7, u1, u11);  /* 0xe8d78 */
        FUN_003a25d4(u2);  /* out of slice; MR block */
        FUN_0036b118(u7);  /* ref release */
        FUN_0036b118(u1);
        if (ctx_flag != 0) {
            FUN_0036b118(param_1);
            FUN_0036b118(local_68);
            FUN_0036b118(u5);
            FUN_0036b6f4(ctx, tcb, *(uint32_t *)(*ctx + 0x18),
                         *(uint16_t *)(*ctx + 0x1c));  /* out of slice; error path */
            return ctx;
        }
        u15 = u15 + 1;
        (**(void (**)(uint64_t, uint64_t, uint64_t))(/* extraout_x16 */ 0 + 0x10))(
            stack_a, stack_b, /* extraout_x1 */ 0);
        v = FUN_00310d34(0, /* extraout_x1 */ 0);  /* out of slice */
        FUN_001a1854(stack_a, v);  /* out of slice */
        FUN_001a5b90(&local_68, u6, u13);  /* out of slice */
        FUN_0036b118(u6);
        (**(void (**)(uint64_t, uint64_t))(/* extraout_x16 */ 0 + 8))(stack_b, /* extraout_x1 */ 0);
        rec = rec + 5;
    }
    /* Does not return: trap on stale table state. */
    SoftwareBreakpoint(1, 0xe8d78);
}

/* FUN_000e8d78 @ 0x000e8d78   (est. cl4_caps_arg_decode)
 * Ghidra: undefined1 * FUN_000e8d78(undefined8 p1, undefined8 p2,
 *            undefined8 p3, undefined1 *p4, ulong p5, undefined8 p6)
 * Decodes a capability-operation argument list and builds the resulting
 * IPC message. p5 is a capability-pointer list (count at p5+0x10, entries
 * at p5+0x20). For each capability pointer it reads the type byte (+0x20)
 * and 16-byte header; entries with the sign bit set are validated as
 * duplicate-argument / array-element kinds (panics on "Encountered
 * duplicate argument..." 0x5c3980, "array element at index..." 0x5c3920,
 * "argument in position..." 0x5c38e0), growing the argument table
 * (FUN_000731dc/FUN_00073268) as needed. It then assembles the message
 * through seL4 helpers (FUN_0031b614, FUN_00284f5c, FUN_001fca54,
 * FUN_001f6b30), walks the argument bitmap (LZCOUNT bitscan) filling a
 * slot table, and dispatches through a registered callback
 * (FUN_00286e40/FUN_002871b4) or emits a diagnostic error. A secondary
 * argument list (p4) is validated and folded in. Traps (SoftwareBreakpoint)
 * fire on malformed state (0xea098, 0xe9e34, 0xea0fc, 0xea100, 0xea104,
 * 0xea108, 0xea114).
 * Confidence: low
 * Notes: fallback reconstruction — the decompiler's register-carry
 * artifacts (extraout_x* / unaff_x20/x21 / DAT_006585c0 indirect dispatch)
 * prevent exact value propagation; logic kept structurally faithful with
 * carries noted in comments. */
uint8_t *cl4_caps_arg_decode(uint64_t p1, uint64_t p2, uint64_t p3,
                             uint8_t *p4, uint64_t p5, uint64_t p6)
{
    uint64_t ctx = 0;         /* unaff_x20 */
    uint64_t ctx_flag = 0;    /* unaff_x21 */
    uint64_t u28, u23, u14, u15, u13, u17, u34, u33, u22;
    uint64_t uVar6, uVar7, uVar11, u20, uVar20, uVar21;
    uint64_t l24, l31, l18, l19, lVar13;
    uint8_t  *pu16;           /* current table */
    uint64_t  count, slot;
    uint8_t   t16[16], hdr[16];
    void (*disp)(void);       /* DAT_006585c0 */
    uint64_t slot_148 = 0, slot_90 = 0, slot_e8 = 0, slot_e0 = 0;
    uint64_t slot_d8 = 0, slot_d0 = 0;
    uint64_t auStack_b8 = 0, auStack_220 = 0, auStack_240 = 0;
    uint64_t auStack_260 = 0, auStack_128 = 0;

    u28 = *(uint64_t *)(ctx + 0x40);
    u23 = *(uint64_t *)(ctx + 0x38);
    /* local_1e0 = FUN_00377824(0, u28, u23, 0x0, 0x0) */
    FUN_0007c028();  /* out of slice */
    disp();          /* DAT_006585c0 indirect dispatch */
    pu16 = (uint8_t *)0x657778;  /* 0x0 */
    lVar13 = FUN_000eb184(0xff, u23, u28);  /* 0xeb184 */
    u14 = FUN_003722e4(0, 0x677830, lVar13, 0, 0);  /* out of slice */
    u14 = FUN_001a0414(0, u14);  /* out of slice */
    u14 = FUN_001f0130(u14, 0x677830, lVar13, 0x671e68);  /* out of slice */
    count = *(uint64_t *)(p5 + 0x10);
    u14 = u14;  /* local_c0 */
    if (count == 0) {
        FUN_000ec02c();  /* in slice; iterator init */
    } else {
        FUN_000ec02c();
        {
            uint64_t *iter = (uint64_t *)(p5 + 0x20);
            do {
                uint8_t *ep = (uint8_t *)*iter;
                uint32_t type;
                if ((int64_t)ep < 0) {
                    /* sign bit set: tagged capability */
                    uint8_t *base = ep + 0x10;   /* & 0x7fff... +0x10 */
                    memcpy(t16, base, 16);
                    type = *(uint8_t *)(((uint64_t)ep & 0x7fffffffffffffffULL) + 0x20);
                    FUN_0036b270();  /* out of slice; ref acquire */
                    if ((int8_t)type < 0) goto decode_tagged;
decode_type:
                    /* uVar12 = (type & 0x7f) == 1 */
                    if ((type & 0x7f) == 1) {
                        FUN_000ebed8();  /* in slice */
                        /* auVar36 = FUN_000ebf6c() */
                        thunk_FUN_001ef804(/* auVar36[0] */ 0, /* auVar36[1] */ 0,
                                           0x677830, p5);  /* out of slice */
                        FUN_000ebf54();  /* in slice */
                        if ((type & 0x7f) == 1) {
                            /* duplicate-argument handling */
                            FUN_000ebed8();
                            l24 = FUN_0031a29c(0, 0x677830, p5, 0);  /* out of slice */
                            FUN_000ebfbc();  /* in slice */
                            FUN_001cf6f4();  /* out of slice */
                            goto next_entry;
                        }
                        FUN_000db8e0();  /* out of slice */
                        FUN_000ebf3c();  /* in slice */
                        FUN_002a4ab4(0x2d);  /* out of slice; alloc */
                        FUN_003a25d4(/* local_140 */ 0);  /* out of slice; MR block */
                        FUN_000ebf98((uint64_t)0x5c3980 /* "Encountered duplicate argument a..." */);
                        FUN_000ec018();  /* in slice */
                        FUN_000ebef0();  /* in slice */
                        FUN_00027724(/* extraout_x16_04 */ 0);  /* out of slice */
                        u28 = FUN_000dbd8c();  /* out of slice */
                        /* (*extraout_x8_04)(u28, t16[0]) */
                        thunk_FUN_002acbb8();  /* out of slice; IPC transition */
                        FUN_003a25d4(/* extraout_x1_02 */ 0);  /* out of slice */
                        FUN_000ec038();  /* in slice */
                        FUN_000aa3ac();  /* out of slice */
                        FUN_000ebf80();  /* in slice */
                    } else {
                        FUN_000ebed8();
                        /* auVar36 = FUN_000ebf6c() */
                        thunk_FUN_001ef804(0, 0, 0x677830, p5);
                        FUN_000ebf54();
                        if ((type & 0x7f) == 1) {
                            FUN_000ebed8();
                            /* auVar36 = FUN_0031a29c(0,0x677830,p5,extraout_x16_01) */
                            FUN_000ebfbc();
                            FUN_001cf6f4();
                        } else {
                            FUN_000db8e0();
                        }
                        FUN_000ebed8();
                        /* auVar36 = FUN_000ebf6c() */
                        thunk_FUN_001ef804(0, 0, 0x677830, p5);
                        u15 = FUN_000ebf54();
                        if ((type & 0x7f) != 1) {
                            if ((u15 >> 0x3e & 1) != 0) {
                                /* array element: grow table */
                                u15 = u15 & 0xbfffffffffffffffULL;
                                FUN_0036b270((uint64_t)ep & 0x7fffffffffffffffULL);
                                u33 = FUN_003a261c(u15);  /* out of slice */
                                if ((u33 & 1) == 0) {
                                    u15 = FUN_000731dc(0, *(uint64_t *)(u15 + 0x10) + 1, 1, u15);
                                }
                                p5 = *(uint64_t *)(u15 + 0x10);
                                if (*(uint64_t *)(u15 + 0x18) >> 1 <= p5) {
                                    FUN_000ec004();  /* in slice */
                                    u15 = FUN_000731dc();
                                }
                                *(uint64_t *)(u15 + 0x10) = p5 + 1;
                                l24 = u15 + p5 * 0x10;
                                *(uint64_t *)(l24 + 0x20) = /* t16[1] */ 0;
                                *(uint64_t *)(l24 + 0x28) = (uint64_t)ep;
                                /* local_148 = u15 | 0x4000000000000000 */
                                FUN_000ebed8();
                                /* auVar35 = FUN_000ec02c(0,0x677830) */
                                l24 = FUN_0031a29c(0, 0, p5);  /* out of slice */
                                FUN_0036b270(u15);
                                FUN_000ebfbc();
                                FUN_001cf6f4();
                                FUN_0036b118(u15);  /* ref release */
                                FUN_0036b118((uint64_t)ep & 0x7fffffffffffffffULL);
                                goto next_entry;
                            }
                            FUN_000db8e0();
                        }
                        FUN_000ebf3c();
                        FUN_002a4ab4(0x3a);  /* out of slice; alloc */
                        FUN_000ec044();  /* in slice */
                        /* local_148 = extraout_x8_05 */
                        thunk_FUN_002acbb8(0xd000000000000038ULL, 0x80000000005c3880ULL);
                        FUN_000ebef0();
                        FUN_00027724(/* extraout_x16_05 */ 0);
                        u28 = FUN_000dbd8c();
                        /* (*extraout_x8_06)(u28, t16[0]) */
                        thunk_FUN_002acbb8();
                        FUN_003a25d4(/* extraout_x1_03 */ 0);
                        FUN_000ec038();
                        FUN_000aa3ac();
                        FUN_000ebf80();
                    }
                    FUN_003a25d4(u14);
                    FUN_0036b118((uint64_t)pu16);  /* ref release */
                    ctx = (uint64_t)ep & 0x7fffffffffffffffULL;
                    goto exit_path;
                }
                /* untagged entry */
                FUN_0036b270((uint64_t)ep);
                /* auVar35 = FUN_000a981c(); Var5 = auVar35.low9 */
                type = (uint32_t)l24;
                if ((type >> 7 & 1) != 0) goto decode_tagged;
decode_tagged:
                if (/* Var5 >> 0x3a */ 0 != 0) {
                    SoftwareBreakpoint(1, 0xea098);  /* trap */
                }
                u15 = FUN_003a261c(pu16);  /* out of slice */
                if ((u15 & 1) == 0) {
                    pu16 = (uint8_t *)FUN_00073268(0, *(uint64_t *)(pu16 + 0x10) + 1, 1, pu16);
                }
                p5 = *(uint64_t *)(pu16 + 0x10);
                if (*(uint64_t *)(pu16 + 0x18) >> 1 <= p5) {
                    FUN_000ec004();
                    pu16 = (uint8_t *)FUN_00073268();
                }
                FUN_0036b118((uint64_t)ep & 0x7fffffffffffffffULL);
                *(uint64_t *)(pu16 + 0x10) = p5 + 1;
                *(uint64_t *)(pu16 + p5 * 0x18 + 0x20) = /* Var5 */ 0 << 6;
                *(uint64_t *)(pu16 + p5 * 0x18 + 0x28) = p6;
                pu16[p5 * 0x18 + 0x30] = (uint8_t)(/* Var5>>0x40 */ 0 & 1);
                FUN_000ec02c();
next_entry:
                count--;
                u14 = u14;
                iter++;
            } while (count != 0);
        }
    }
    /* message assembly */
    /* local_e8 = 0x7000000000000007 (message tag) */
    u15 = thunk_FUN_0036b270(u14, 0x677830, p5, 0x671e68);  /* out of slice */
    /* local_d0 = u15 */
    u17 = FUN_0031b614(0, 0x677830, p5, 0x671e68);  /* out of slice */
    thunk_FUN_0036b270(u14);
    FUN_00284f5c(&slot_148, u17, 0x66bb20, 0x671e50);  /* out of slice */
    FUN_003a25d4(u15);
    /* lVar31 = (char)local_140 == 1 ? 0 : (extraout_x8_01 + 1, with
     * overflow traps 0xea104/0xea100) */
    l18 = FUN_00310d68(0, p5);  /* out of slice */
    /* local_c8 = FUN_001a03fc(&local_e8, lVar31, l18) */
    FUN_000ebf0c();  /* in slice */
    u17 = FUN_0001a1c8(u14, 0x677830, p5, /* extraout_x16_02 */ 0);  /* out of slice */
    thunk_FUN_001fca54(auStack_b8, u17, 0x677830, p5, l31);  /* out of slice */
    FUN_001f6b30(&slot_90, auStack_b8, 0x677830, p5, l31);  /* out of slice */
    /* bitmap walk: for each set bit (LZCOUNT bitscan) fill slot table */
    u15 = /* local_70 */ 0;
    l24 = /* lStack_78 */ 0;
    for (;;) {
        for (; u15 != 0; u15 = u15 - 1 & u15) {
            u33 = /* LZCOUNT bitswap of u15 | l24<<6 */ 0;
            FUN_000ebf0c();
            l19 = FUN_001f7d28(/* local_90 */ 0, 0x677830, lVar13, /* extraout_x16_03 */ 0);
            l19 = *(uint64_t *)(l19 + u33 * 8);
            l31 = FUN_001f0bb4(/* local_90 */ 0, 0x677830, lVar13, l31);
            if (l19 < 0) {
                SoftwareBreakpoint(1, 0xea0fc);  /* trap */
            }
            u34 = *(uint64_t *)(l31 + u33 * 8);
            FUN_000db870(u34);  /* out of slice */
            FUN_000db870(u34);
            FUN_00310d34(0, l18);  /* out of slice */
            thunk_FUN_001dc298();  /* out of slice */
            l31 = /* local_c8 */ 0;
            FUN_000eb19c(l19, /* local_c8 */ 0, l18);  /* 0xeb19c */
            u33 = *(uint8_t *)(*(uint64_t *)(l18 - 8) + 0x50);
            /* swap slot table entries */
            u17 = *(uint64_t *)(l31 + (u33 + 0x20 & (u33 ^ 0xffffffffffffffffULL)) + l19 * 8);
            *(uint64_t *)(l31 + (u33 + 0x20 & (u33 ^ 0xffffffffffffffffULL)) + l19 * 8) = u34;
            FUN_000db8e0(u17);
            FUN_000db888(u34);
        }
        l24 = l24 + 1;
        if (/* SCARRY */ 0) {
            SoftwareBreakpoint(1, 0xe9e34);  /* trap */
        }
        if (/* local_80 + 0x40 >> 6 */ 0 <= l24) break;
        u15 = *(uint64_t *)(/* lStack_88 */ 0 + l24 * 8);
    }
    FUN_0036b118(/* local_90 */ 0);  /* ref release */
    disp();
    /* auStack_210[lVar4] = u23; auStack_210[lVar4+8] = u28 */
    u17 = FUN_00310d34(0, l18);
    u15 = FUN_00286e40(0x0, auStack_220, u17, 0x66acf0);  /* out of slice */
    if ((u15 & 1) == 0) {
        /* dispatch failure: build "argument in position..." error message */
        disp();
        u14 = FUN_000ebf24();  /* in slice */
        u14 = FUN_00376820(u14, u17);  /* out of slice */
        FUN_001d80e0(&slot_148, 0x0, auStack_220, u17, u14);
        if ((char)/* local_140 */ 0 == '\x01') {
            SoftwareBreakpoint(1, 0xea108);  /* trap */
        }
        FUN_000ec038();
        FUN_000ebf3c();
        FUN_002a4ab4(0x2a);  /* out of slice; alloc */
        FUN_003a25d4(/* local_140 */ 0);
        FUN_000ebf98((uint64_t)0x5c38e0 /* "argument in position..." */);
        FUN_000ec018();
        /* local_e8 = auStack_200 */
        /* pcVar10 = FUN_00027724(0x6720e0); (*pcVar10)(0x677880, 0x6720e0) */
        thunk_FUN_002acbb8();
        FUN_003a25d4(/* extraout_x1 */ 0);
        FUN_000ebfcc();  /* in slice */
        FUN_000ec038();
        ctx = /* local_140 */ 0;
        FUN_000aa3ac();
        FUN_000ebf80();
        FUN_000ebff4();  /* in slice */
        pu16 = (uint8_t *)FUN_000ebfe8();  /* in slice */
        p4 = /* extraout_x1 */ 0;
    } else {
        disp();
        /* u15 = FUN_002871b4(FUN_000eb1e8, auStack_220, u17, lVar13, 0x66acf0) */
        /* local_d8 = u15; local_d0 = u15 */
        u17 = FUN_00310d34(0, lVar13);
        thunk_FUN_00200b38(&slot_e8, u17, 0x66acf0);  /* out of slice */
        FUN_0031b760(0, u17, 0x66acf0);  /* out of slice */
        FUN_00200bd0(&slot_148);  /* out of slice */
        u34 = FUN_0031b778(0, u17, 0x66acf0);  /* out of slice */
        while (FUN_00200bf4(&slot_e8, u34), /* local_e0 */
               (/* local_e0 ^ 0xffffffffffffffff & 0x7000000000000007 */ 0) != 0) {
            if (/* local_e0 >> 0x3e & 1 */ 0) {
                /* iterate the pending array; validate indices; on a hole
                 * emit "array element at index..." error (0x5c3920) and
                 * return the completed error message */
                SoftwareBreakpoint(1, 0xea114);  /* possible trap */
                /* ... */
            }
            FUN_000eb2d8(/* puVar6 */ 0, /* puVar9 */ 0);  /* 0xeb2d8 */
        }
        FUN_0036b118(/* local_148 */ 0);
        u34 = /* uRam@0x4baeb8 */ 0;
        u17 = /* _DAT_004baeb0 */ 0;
        l31 = *(uint64_t *)(p4 + 0x10);
        if (l31 != 0) {
            uint64_t *p32 = (uint64_t *)(p4 + 0x38);
            do {
                u15 = p32[-2];
                if (*(uint64_t *)(u15 + 0x10) == 0) {
                    if (/* DAT_006add10 */ 0 == '\x01') {
                        /* build an error message for a pending reference:
                         * FUN_00002534, FUN_0036a9a0, alloc 0x3c,
                         * thunk_FUN_002acbb8(0xd<<60|0x10, 0x80000000005c3920),
                         * FUN_00205844, state transitions, FUN_0026b434,
                         * FUN_0036b588, FUN_00002688, FUN_0036b6ac */
                        u22 = /* *p32 */ 0;
                        FUN_002a4ab4(0x3c);  /* out of slice; alloc */
                        FUN_000ec044();
                        thunk_FUN_002acbb8(0xd000000000000010ULL, 0x80000000005c3920ULL);
                        FUN_00205844(&slot_148, &slot_e8,
                                     0x65f878, 0x6756a8, 0x66e1b8);  /* out of slice */
                        thunk_FUN_002acbb8(0x706d6f6320666f20ULL, 0xee0020746e656e6fULL);
                        thunk_FUN_002acbb8(p2, p3);
                        thunk_FUN_002acbb8(0xd00000000000001aULL, 0x80000000005c3940ULL);
                        /* *(l24+0x38)=0x6753a0; *(l24+0x20)=local_e8; *(l24+0x28)=local_e0 */
                        FUN_0026b434(l24, 0x20, 0xe100000000000000ULL, 10,
                                     0xe100000000000000ULL);  /* out of slice */
                        FUN_0036b588(l24);  /* out of slice */
                        u20 = FUN_00002688();  /* out of slice */
                        FUN_0036b6ac(u20, 0x20, 7);  /* out of slice */
                        FUN_003a25d4(u22);
                        FUN_0036b118(u15);  /* ref release */
                    } else {
                        thunk_FUN_0036b270(p3);
                    }
                    FUN_003a25d4(p3);
                }
                p32 = p32 + 4;
                l31--;
                u15 = /* local_d0 */ 0;
            } while (l31 != 0);
        }
        /* local_148 = 0 */
        FUN_000ea1bc(&slot_148, u15, 0x65a898, 0x65a7d0);  /* 0xea1bc */
        if (ctx_flag == 0) {
            FUN_000ec044();
            /* build and dispatch the final message through the registered
             * handler chain (FUN_00002534 / FUN_00377824 / FUN_000262fc /
             * FUN_00377bec / FUN_000eb238 / FUN_000eb2a8), then invoke the
             * completion at (local_1d8+0x20). */
            u17 = FUN_00002534(0x64e1e8, 0x0);  /* out of slice */
            u34 = FUN_00377824(0, u28, u23, 0x0, 0x0);
            u20 = FUN_00002534(0x0, 0x0);
            u22 = FUN_000ebd10(0x651da0, 0x64e1e8, 0x0);  /* 0xebd10 */
            u17 = FUN_000262fc(FUN_000eb218, auStack_220, u17, u34, u20, u22,
                               0x66c1c8, &slot_d8);  /* out of slice */
            FUN_000ebfac();  /* in slice */
            u34 = /* local_1e0 */ 0;
            u22 = FUN_00377bec(u28, u23, /* local_1e0 */ 0, 0x0, 0x0);
            /* pcVar10 = FUN_000eb238(); thunk_FUN_0036b270(p3);
             * (*pcVar10)(local_1d0, p2, p3, extraout_x8_08, u17, u34, u22) */
            disp();
            u17 = /* local_1f0 */ 0;
            u17 = FUN_00002534(0x651da8, 0x0);
            u28 = FUN_00377824(0, u28, u23, 0x0, 0x0);
            u23 = FUN_000ebd10(0x651db0, 0x651da8, 0x0);
            u33 = FUN_000262fc(FUN_000eb268, auStack_240, u17, u28, 0x674330,
                               u23, 0x66d208);
            FUN_000ebfac();
            disp();
            /* pcVar10 = FUN_000eb2a8(u22);
             * (*pcVar10)(FUN_000eb288, auStack_260, u20, 0x66c1c8, &local_e8,
             *             u34, u22) */
            l31 = /* local_c8 */ 0;
            FUN_000ebfe8();
            FUN_0036b118();
            FUN_0036b118(l31);
            (**(void (**)(uint64_t, uint64_t, uint64_t))(/* local_1d8 */ 0 + 0x20))(
                /* local_1f8 */ 0, /* puVar29 */ 0, u34);
            u15 = /* local_d0 */ 0;
            FUN_003a25d4(u14);
            FUN_0036b118(u15);
            return (uint8_t *)u33;
        }
        FUN_000ebff4();
        FUN_0036b118(u15);
    }
    FUN_0036b118((uint64_t)pu16);
    /* puVar29 = p4 */
exit_path:
    FUN_0036b118(ctx);
    return p4;
}

/* FUN_000ea1bc @ 0x000ea1bc   (est. cl4_caps_list_validate)
 * Ghidra: void FUN_000ea1bc(undefined8 p1, undefined8 p2, undefined8 p3,
 *            undefined8 p4)
 * Validates each capability in the list p2 (helper FUN_00019850 /
 * thunk_FUN_0001612c), extracting entries via FUN_0019ea20 and advancing via
 * FUN_0019e924, and checking each with FUN_000267d4 (p3/p4 context). On
 * success the entry is released (FUN_000db888). On a failed entry
 * (unaff_x21!=0) it records the error through FUN_0036993c with the
 * FUN_0065a550 handler and returns.
 * Confidence: low
 * Notes: unaff_x20/x21 caller-preserved context registers; DAT_004c3658
 * referenced at the validation call. */
void cl4_caps_list_validate(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t ctx = 0;       /* unaff_x20 */
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t u4, u1, u3;
    uint64_t cur, nxt;

    u4 = FUN_000eb184(0, *(uint64_t *)(ctx + 0x38), *(uint64_t *)(ctx + 0x40));  /* 0xeb184 */
    cur = FUN_00019850(p2, u4);  /* out of slice */
    for (;;) {
        nxt = thunk_FUN_0001612c(p2, u4);  /* out of slice */
        if (cur == nxt) {
            return;
        }
        FUN_0019ea20(&u1, cur, p2, u4);  /* out of slice; extract entry */
        u1 = u1;  /* local_60 */
        FUN_0019e924(&cur, p2, u4);  /* out of slice; advance */
        u3 = FUN_000267d4(&u1, p3, u4, p4, 0x4c3658);  /* out of slice; validate */
        if (ctx_flag != 0) break;
        FUN_000db888(u1);  /* out of slice; release entry */
    }
    u4 = FUN_00019aac(0);  /* out of slice */
    FUN_0036993c(u4, FUN_0065a550, 0, 0);  /* out of slice; record error */
    /* *extraout_x1 = u3; */
    FUN_000db888(u1);
}

/* FUN_000ea2f8 @ 0x000ea2f8   (est. cl4_caps_op_dispatch_8)
 * Ghidra: void FUN_000ea2f8(undefined8 p1, undefined8 *p2, undefined8 p3,
 *            undefined8 p4, undefined8 *p5)
 * Dispatches an 8-argument capability operation. Reads the message header
 * (p2[2], p2[3]) and kind (FUN_0001fe3c(*p2)), builds the operation context
 * via FUN_00377824/FUN_00002534/FUN_000262fc (callback FUN_000ebcec), then
 * invokes the handler from FUN_000ebd54 with the assembled argument vector.
 * On the failure path (unaff_x21!=0) it publishes the pending state through
 * the MR block and stores it into *p5.
 * Confidence: low
 * Notes: unaff_x21 caller-preserved context register. */
void cl4_caps_op_dispatch_8(uint64_t p1, uint64_t *p2, uint64_t p3, uint64_t p4,
                            uint64_t *p5)
{
    uint64_t u1, u2, u3, u4, u5, u6;
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint8_t  hdr[12];
    uint64_t local_58_res = 0;
    void (*handler)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t,
                    uint64_t, uint64_t, uint64_t);

    u1 = p2[2];
    u2 = p2[3];
    memcpy(hdr, (void *)FUN_0001fe3c(*p2), 12);  /* out of slice; header */
    u3 = FUN_00377824(0, p4, p3, 0x0, 0x0);  /* out of slice */
    thunk_FUN_0036b270(u2);  /* out of slice; ref acquire */
    u4 = FUN_00002534(0x0, 0x0);  /* out of slice */
    u5 = FUN_00002534(0x0, 0x0);  /* out of slice */
    u6 = FUN_000ebd10(0x651db8, 0x0, 0x0);  /* 0xebd10 */
    u3 = FUN_000262fc(FUN_000ebcec, /* auStack_90 */ 0, u4, u3, u5, u6, 0x66c1c8,
                      &local_58_res);  /* out of slice */
    if (ctx_flag == 0) {
        u4 = FUN_00377824(0, p4, p3, 0x0, 0x0);
        u5 = FUN_00377bec(p4, p3, u4, 0x0, 0x0);  /* out of slice */
        handler = (void (*)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t,
                            uint64_t, uint64_t, uint64_t))FUN_000ebd54();  /* 0xebd54 */
        handler(p1, hdr[0] & 0xffffffff00ffffffULL, /* hdr[8..] */ 0,
                u1, u2, u3, u4, u5);
    } else {
        FUN_003a25d4(u2);  /* out of slice; MR block */
        p5[0] = /* local_58 */ 0;
    }
}

/* FUN_000ea4dc @ 0x000ea4dc   (est. cl4_caps_op_dispatch_5)
 * Ghidra: void FUN_000ea4dc(undefined8 p1, undefined8 *p2, undefined8 p3,
 *            undefined8 p4, undefined8 p5, long *p6)
 * Dispatches a 5-argument capability operation. Reads the message words
 * (*p2, p2[1]), builds the operation context (FUN_00377824/FUN_00377bec),
 * acquires a reference on the object, and invokes the handler from
 * FUN_000ebd84 with the argument vector. On failure (unaff_x21!=0) records
 * the error into *p6.
 * Confidence: low
 * Notes: unaff_x21 caller-preserved context register. */
void cl4_caps_op_dispatch_5(uint64_t p1, uint64_t *p2, uint64_t p3, uint64_t p4,
                            uint64_t p5, uint64_t *p6)
{
    uint64_t u1, u2, u3, u4;
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    void (*handler)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

    u1 = *p2;
    u2 = p2[1];
    u3 = FUN_00377824(0xff, p5, p4, 0x0, 0x0);
    u4 = FUN_00377bec(p5, p4, u3, 0x0, 0x0);
    handler = (void (*)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t))FUN_000ebd84();  /* 0xebd84 */
    thunk_FUN_0036b270(u2);  /* ref acquire */
    { cl4_result_t _r = FUN_00377dcc(0, u3); u3 = _r.lo; }  /* out of slice */
    handler(p1, u1, u2, u3, u4);
    if (ctx_flag != 0) {
        p6[0] = ctx_flag;
    }
}

/* FUN_000ea5c8 @ 0x000ea5c8   (est. cl4_caps_op_dispatch_6)
 * Ghidra: void FUN_000ea5c8(undefined8 p1, undefined8 *p2, undefined8 p3,
 *            undefined8 p4)
 * Dispatches a 6-argument capability operation. Reads the message words
 * (*p2, p2[1]) and an options byte (p2+2), builds the operation context,
 * and invokes the handler from FUN_000ebcbc.
 * Confidence: low
 * Notes: single dispatch path, no error branch. */
void cl4_caps_op_dispatch_6(uint64_t p1, uint64_t *p2, uint64_t p3, uint64_t p4)
{
    uint64_t u1, u2, u4, u5;
    uint8_t  u3;
    void (*handler)(uint64_t, uint64_t, uint64_t, uint8_t, uint64_t, uint64_t);

    u1 = *p2;
    u2 = p2[1];
    u3 = *(uint8_t *)(p2 + 2);
    u4 = FUN_00377824(0, p4, p3, 0x0, 0x0);
    u5 = FUN_00377bec(p4, p3, u4, 0x0, 0x0);
    handler = (void (*)(uint64_t, uint64_t, uint64_t, uint8_t, uint64_t, uint64_t))FUN_000ebcbc();  /* 0xebcbc */
    handler(p1, u1, u2, u3, u4, u5);
}

/* FUN_000ea694 @ 0x000ea694   (est. cl4_caps_op_validate_ctx)
 * Ghidra: void FUN_000ea694(undefined8 p1, long p2, undefined8 *p3, long *p4)
 * Validates a capability operation against the object p2. Builds two layers
 * of operation context (FUN_00377824/FUN_00377bec over p2+0x38/+0x40), then
 * runs the list validation FUN_000ea1bc over *p3. On failure (unaff_x21!=0)
 * records the error into *p4.
 * Confidence: low
 * Notes: unaff_x21 caller-preserved context register. */
void cl4_caps_op_validate_ctx(uint64_t p1, uint64_t p2, uint64_t *p3, uint64_t *p4)
{
    uint64_t u1, u2, u3, u4;
    uint64_t ctx_flag = 0;  /* unaff_x21 */

    u4 = *p3;
    u2 = *(uint64_t *)(p2 + 0x38);
    u3 = *(uint64_t *)(p2 + 0x40);
    u1 = FUN_00377824(0xff, u3, u2, 0x0, 0x0);
    u2 = FUN_00377bec(u3, u2, u1, 0x0, 0x0);
    u3 = FUN_00377824(0, u2, u1, 0x0, 0x0);
    u2 = FUN_00377bec(u2, u1, u3, 0x0, 0x0);
    FUN_0036b270(u4);  /* ref acquire */
    cl4_caps_list_validate(p1, u4, u3, u2);  /* 0xea1bc */
    FUN_0036b118(u4);  /* ref release */
    if (ctx_flag != 0) {
        p4[0] = ctx_flag;
    }
}

/* FUN_000ea7b4 @ 0x000ea7b4   (est. cl4_caps_op_prepare)
 * Ghidra: undefined8 FUN_000ea7b4(undefined8 p1)
 * Prepares a capability operation: builds a {p1, 0} frame, resolves the
 * table via FUN_000eb184, and validates it with FUN_000267d4. Returns the
 * local status word (0).
 * Confidence: low
 * Notes: one unreachable block at 0xea838 removed. */
uint64_t cl4_caps_op_prepare(uint64_t p1)
{
    uint64_t status = 0;
    uint64_t frame0 = p1;
    uint64_t v = FUN_000eb184(0);  /* 0xeb184 */
    FUN_000267d4(&frame0, 0x65a898, v, 0x65a7d0, 0x4c3658);  /* out of slice; validate */
    return status;
}

/* FUN_000ea884 @ 0x000ea884   (est. cl4_caps_validate_cap_list)
 * Ghidra: undefined8 FUN_000ea884(undefined8 p1, ulong p2, undefined8 p3,
 *            undefined8 p4, undefined8 p5, undefined8 p6)
 * Validates a capability argument. If p2's bit 0x3e is clear, it validates
 * the single capability word via FUN_000267d4. Otherwise p2 points to a
 * mapped capability list (count at +0x10, entries at +0x28): each entry is
 * validated in turn (acquire/release its low tag bit). The result (the
 * last-validated word) is carried out via the unaff_x26 register path.
 * Confidence: low
 * Notes: unaff_x21/x26 caller-preserved registers; FUN_00023c78 validates
 * the list header. */
uint64_t cl4_caps_validate_cap_list(uint64_t p1, uint64_t p2, uint64_t p3,
                                    uint64_t p4, uint64_t p5, uint64_t p6)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t carry = 0;     /* unaff_x26 */
    uint64_t result = 0;
    uint64_t count;
    uint64_t *ent;

    if ((p2 >> 0x3e & 1) == 0) {
        result = p2;
        result = FUN_000267d4(&result, p4, 0x662bc0, p6, 0x6629d8);  /* validate */
        if (ctx_flag != 0) {
            carry = result;
        }
    } else {
        count = *(uint64_t *)((p2 & 0xbfffffffffffffffULL) + 0x10);
        void (*h)(uint64_t, uint64_t, uint64_t) =
            (void (*)(uint64_t, uint64_t, uint64_t))FUN_00023c78(p6);  /* out of slice */
        h(count, p4, p6);
        ent = (uint64_t *)((p2 & 0xbfffffffffffffffULL) + 0x28);
        for (; count != 0; count--) {
            uint64_t cap = *ent;
            result = cap;
            FUN_0036b270(cap & 0x7fffffffffffffffULL);  /* ref acquire */
            result = FUN_000267d4(&result, p4, 0x662bc0, p6, 0x6629d8);  /* validate */
            FUN_0036b118(cap & 0x7fffffffffffffffULL);  /* ref release */
            if (ctx_flag != 0) goto done;
            ent += 2;
            carry = result;
        }
    }
done:
    return carry;
}

/* FUN_000ea9c8 @ 0x000ea9c8   (est. cl4_caps_op_check)
 * Ghidra: undefined4 FUN_000ea9c8(undefined8 p1, undefined8 p2, undefined8 p3,
 *            long p4)
 * Runs the capability validation FUN_000ea884 over the object p4 fields and
 * returns 1 on success (unaff_x21==0) or the validation result otherwise.
 * Confidence: low
 * Notes: unaff_x20/x21 caller-preserved context registers. */
uint32_t cl4_caps_op_check(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t *ctx = 0;  /* unaff_x20 */
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint32_t r;

    r = (uint32_t)cl4_caps_validate_cap_list(p1, *ctx, *(uint64_t *)(p4 + 0x10),
                                             p2, *(uint64_t *)(p4 + 0x18), p3);  /* 0xea884 */
    if (ctx_flag == 0) {
        r = 1;
    }
    return r;
}

/* FUN_000ea9cc @ 0x000ea9cc   (est. cl4_caps_op_check_b)
 * Ghidra: undefined4 FUN_000ea9cc(undefined8 p1, undefined8 p2, undefined8 p3,
 *            long p4)
 * Duplicate of 0xea9c8: runs FUN_000ea884 over the object p4 fields and
 * returns 1 on success (unaff_x21==0) or the validation result.
 * Confidence: low
 * Notes: twin entry point to 0xea9c8. */
uint32_t cl4_caps_op_check_b(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t *ctx = 0;  /* unaff_x20 */
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint32_t r;

    r = (uint32_t)cl4_caps_validate_cap_list(p1, *ctx, *(uint64_t *)(p4 + 0x10),
                                             p2, *(uint64_t *)(p4 + 0x18), p3);
    if (ctx_flag == 0) {
        r = 1;
    }
    return r;
}

/* FUN_000eaa04 @ 0x000eaa04   (est. cl4_exc_dispatch_continuation)
 * Ghidra: void FUN_000eaa04(void)
 * Invokes the dispatch continuation for the current exception context: the
 * function pointer at (*(*x20+0x38)-8)+8 is called with the argument slot
 * x20+*(*x20+0x48).
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register; indirect call. */
void cl4_exc_dispatch_continuation(void)
{
    uint64_t *ctx = 0;  /* unaff_x20 */
    void (**cont)(uint64_t) = (void (**)(uint64_t))(
        (*(uint64_t *)(*(uint64_t *)(*ctx + 0x38) - 8)) + 8);
    (*cont)((uint64_t)ctx + *(uint64_t *)(*ctx + 0x48));
}

/* FUN_000eaa6c / FUN_000eaa70 @ 0xeaa6c / 0xeaa70  (est. cl4_exc_dispatch_tail_a/b)
 * Ghidra: void FUN_000eaa6c(void) / void FUN_000eaa70(void)
 * Run the dispatch continuation (0xeaa04) then the out-of-slice cleanup
 * FUN_0036b6ac(). Two entry points for distinct call sites.
 * Confidence: low
 * Notes: FUN_0036b6ac is the trailing state-cleanup helper. */
void cl4_exc_dispatch_tail_a(void)
{
    cl4_exc_dispatch_continuation();  /* 0xeaa04 */
    FUN_0036b6ac();  /* out of slice */
}
void cl4_exc_dispatch_tail_b(void)
{
    cl4_exc_dispatch_continuation();  /* 0xeaa04 */
    FUN_0036b6ac();  /* out of slice */
}

/* FUN_000eaaa4 @ 0x000eaaa4   (est. cl4_exc_op_prepare_store)
 * Ghidra: void FUN_000eaaa4(undefined8 *p1)
 * Stores the result of FUN_000e8978 (0xe8978) into *p1 on the happy path
 * (unaff_x21==0).
 * Confidence: low
 * Notes: unaff_x21 caller-preserved context register. */
void cl4_exc_op_prepare_store(uint64_t *p1)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t v = FUN_000e8978();  /* 0xe8978 */
    if (ctx_flag == 0) {
        p1[0] = v;
    }
}

/* FUN_000eaad0 @ 0x000eaad0   (est. cl4_exc_cap_op_dispatch_wrap)
 * Ghidra: void FUN_000eaad0(void)
 * Tail thunk to FUN_000e8874 (0xe8874, capability op dispatch).
 * Confidence: high
 * Notes: single tail call. */
void cl4_exc_cap_op_dispatch_wrap(void)
{
    cl4_exc_cap_op_dispatch();  /* 0xe8874 */
}

/* FUN_000eaaf4 @ 0x000eaaf4   (est. cl4_exc_cap_op_dispatch_4arg_wrap)
 * Ghidra: void FUN_000eaaf4(void)
 * Tail thunk to FUN_000ea114 (0xea114, 4-argument capability op dispatch).
 * Confidence: high
 * Notes: single tail call. */
void cl4_exc_cap_op_dispatch_4arg_wrap(void)
{
    cl4_exc_cap_op_dispatch_4arg(0, 0);  /* 0xea114 */
}

/* FUN_000eab18 @ 0x000eab18   (est. cl4_exc_msg_build)
 * Ghidra: void FUN_000eab18(undefined1 (*p1)[16])
 * Builds a 16-byte message/header word from thunk_FUN_0001a1c8() and stores
 * it into *p1.
 * Confidence: low
 * Notes: thunk_FUN_0001a1c8 is the out-of-slice message builder. */
void cl4_exc_msg_build(uint8_t (*p1)[16])
{
    uint8_t w[16];
    memcpy(w, (void *)thunk_FUN_0001a1c8(), 16);  /* out of slice */
    memcpy(p1, w, 16);
}

/* FUN_000eab48 @ 0x000eab48   (est. cl4_exc_msg_op)
 * Ghidra: void FUN_000eab48(undefined8 p1, undefined8 p2)
 * Performs a message operation via FUN_0001b620 over the context
 * (*x20, x20[1]). On failure (unaff_x21!=0) it records an error through
 * FUN_0036993c with the DAT_00659b58/0x6598d8 handlers.
 * Confidence: low
 * Notes: unaff_x20/x21 caller-preserved context registers. */
void cl4_exc_msg_op(uint64_t p1, uint64_t p2)
{
    uint64_t *ctx = 0;  /* unaff_x20 */
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t v = FUN_0001b620(p1, p2, *ctx, ctx[1]);  /* out of slice */
    if (ctx_flag != 0) {
        FUN_0036993c(0x659b58, 0x6598d8, 0, 0);  /* out of slice */
        /* *extraout_x1 = v; */
    }
}

/* FUN_000eaba4 @ 0x000eaba4   (est. cl4_exc_op_register)
 * Ghidra: void FUN_000eaba4(undefined8 p1, undefined8 p2, undefined8 p3,
 *            undefined8 p4, undefined8 p5)
 * Registers an exception operation. Captures the current context through the
 * indirect dispatch (*DAT_006585c0), stores p3/p4 into the frame, and
 * installs FUN_000eafdc as the completion callback via FUN_0001ac14. On the
 * failure path (unaff_x21!=0) invokes the continuation at
 * (extraout_x16+0x20) with p5 and the stack frame.
 * Confidence: low
 * Notes: unaff_x21/x8/x16 caller-preserved registers; DAT_006585c0 indirect
 * dispatch. */
void cl4_exc_op_register(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                         uint64_t p5)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint8_t frame[16];
    uint64_t v = p3;

    FUN_0007c028();  /* out of slice */
    /* local_40 = (*DAT_006585c0)(*(extraout_x8+0x40)) */
    v = v;  /* local_50 */
    FUN_0001ac14(FUN_000eafdc, frame);  /* out of slice; install callback */
    if (ctx_flag != 0) {
        (**(void (**)(uint64_t, uint8_t *, uint64_t))(/* extraout_x16 */ 0 + 0x20))(
            p5, frame, p3);
    }
}

/* FUN_000eac74 @ 0x000eac74   (est. cl4_exc_cap_acquire_state)
 * Ghidra: void FUN_000eac74(undefined8 p1, undefined8 p2, undefined8 p3,
 *            long p4, undefined8 p5, undefined8 p6)
 * Acquires capability-operation state. Reads the object header (param_4-8),
 * captures the message fields through the indirect dispatch (*DAT_006585c0)
 * (word pairs at +8/+0x10 and +0x18/+0x20, plus carried x14/x15 bytes),
 * then runs the captured-state handler (*extraout_x8). On the happy path
 * (unaff_x21==0) it repacks the state into local_c0..local_90 and calls
 * FUN_00025704; otherwise it invokes the continuation at (lVar2+0x20) with
 * p6 and repacks into local_80..local_50 before FUN_00025704.
 * Confidence: low
 * Notes: extensive register-carry (extraout_x8/x12/w13/x14/w15); DAT_006585c0
 * indirect dispatch. */
void cl4_exc_cap_acquire_state(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                               uint64_t p5, uint64_t p6)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t hdr = *(uint64_t *)(p4 - 8);
    uint64_t l1 = (*DAT_006585c0)(p2);  /* out of slice; indirect dispatch */
    uint8_t  flag = 0;  /* extraout_w13 & 1 */
    uint64_t w08, w10, w18, w20, carry14;
    uint8_t  carry15;
    void (*cap)(uint8_t *, uint8_t *);

    w10 = *(uint64_t *)(l1 + 0x10);
    w08 = *(uint64_t *)(l1 + 8);
    w20 = *(uint64_t *)(l1 + 0x20);
    w18 = *(uint64_t *)(l1 + 0x18);
    carry14 = 0;  /* extraout_x14 */
    carry15 = 0;  /* extraout_w15 */
    cap = (void (*)(uint8_t *, uint8_t *))(/* extraout_x8 */ 0);
    cap(&flag, /* stack */ 0);
    if (ctx_flag == 0) {
        /* repack: local_c0=CONCAT71(uStack_f7,flag); uStack_b8=w08;
         * uStack_a8=w18; uStack_b0=w10; uStack_98=carry14;
         * local_a0=w20; local_90=carry15 */
        FUN_00025704();  /* out of slice */
    } else {
        (**(void (**)(uint64_t, uint8_t *, uint64_t))(hdr + 0x20))(p6, /* stack */ 0, p4);
        /* repack into local_80..local_50 */
        FUN_00025704();  /* out of slice */
    }
}

/* FUN_000eadc0 @ 0x000eadc0   (est. cl4_exc_msg_store2)
 * Ghidra: void FUN_000eadc0(undefined1 (*p1)[16], undefined8 p2, undefined8 p3,
 *            undefined8 p4, undefined8 p5)
 * Builds a message header from FUN_0001ab94() into *p1 and stores p4/p5
 * into the message payload at param_1[1].
 * Confidence: low
 * Notes: FUN_0001ab94 is the out-of-slice header builder. */
void cl4_exc_msg_store2(uint8_t (*p1)[16], uint64_t p2, uint64_t p3,
                        uint64_t p4, uint64_t p5)
{
    uint8_t w[16];
    memcpy(w, (void *)FUN_0001ab94(), 16);  /* out of slice */
    memcpy(p1, w, 16);
    *(uint64_t *)(p1[1] + 0) = p4;
    *(uint64_t *)(p1[1] + 8) = p5;
}

/* FUN_000eadec @ 0x000eadec   (est. cl4_exc_op_dispatch_cb)
 * Ghidra: void FUN_000eadec(undefined8 p1, undefined8 p2, long p3,
 *            undefined8 p4, undefined8 p5)
 * Dispatches an exception operation callback: reads the object header
 * (param_3-8), captures its +0x40 field via the indirect dispatch, runs the
 * operation registration 0xeaba4, and on failure (unaff_x21!=0) invokes the
 * continuation at (lVar1+0x20) with p5 and the stack.
 * Confidence: low
 * Notes: unaff_x21/x8 caller-preserved registers. */
void cl4_exc_op_dispatch_cb(uint64_t p1, uint64_t p2, uint64_t p3,
                            uint64_t p4, uint64_t p5)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t hdr = *(uint64_t *)(p3 - 8);
    (*DAT_006585c0)(*(uint64_t *)(hdr + 0x40));  /* indirect dispatch */
    cl4_exc_op_register(0, 0, 0, 0, 0);  /* 0xeaba4 */
    if (ctx_flag != 0) {
        (**(void (**)(uint64_t, uint8_t *, uint64_t))(hdr + 0x20))(p5, /* stack */ 0, p3);
    }
}

/* FUN_000eaea0 @ 0x000eaea0   (est. cl4_exc_msg_store_flag)
 * Ghidra: void FUN_000eaea0(undefined1 (*p1)[16], undefined8 p2, undefined8 p3,
 *            byte p4)
 * Builds a message header from FUN_0001b360() into *p1 and stores the
 * single-bit flag p4&1 into the payload byte param_1[1][0].
 * Confidence: low
 * Notes: FUN_0001b360 is the out-of-slice header builder. */
void cl4_exc_msg_store_flag(uint8_t (*p1)[16], uint64_t p2, uint64_t p3, uint8_t p4)
{
    uint8_t w[16];
    memcpy(w, (void *)FUN_0001b360(), 16);  /* out of slice */
    memcpy(p1, w, 16);
    p1[1][0] = p4 & 1;
}

/* FUN_000eaed0 @ 0x000eaed0   (est. cl4_exc_msg_decode_words)
 * Ghidra: void FUN_000eaed0(undefined8 *p1, ulong p2)
 * Decodes a message word into five fields via FUN_0001a72c (masked with
 * 0xffffffff00ffffff) and copies the result words into p1[0..4].
 * Confidence: low
 * Notes: FUN_0001a72c is the out-of-slice word decoder. */
void cl4_exc_msg_decode_words(uint64_t *p1, uint64_t p2)
{
    uint64_t f[5];
    FUN_0001a72c(&f[0], p2 & 0xffffffff00ffffffULL);  /* out of slice */
    p1[1] = f[1];
    p1[0] = f[0];
    p1[3] = f[3];
    p1[2] = f[2];
    p1[4] = f[4];
}

/* FUN_000eaf18 @ 0x000eaf18   (est. cl4_exc_msg_alloc)
 * Ghidra: void FUN_000eaf18(undefined1 (*p1)[16])
 * Allocates a message via FUN_0001a47c() into *p1 on the happy path
 * (unaff_x21==0); otherwise records an error through FUN_0036993c and
 * returns the message word.
 * Confidence: low
 * Notes: unaff_x21 caller-preserved context register. */
void cl4_exc_msg_alloc(uint8_t (*p1)[16])
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint8_t w[16];
    memcpy(w, (void *)FUN_0001a47c(), 16);  /* out of slice */
    if (ctx_flag == 0) {
        memcpy(p1, w, 16);
    } else {
        FUN_0036993c(0x659b58, 0x6598d8, 0, 0);  /* out of slice */
        /* *extraout_x1 = w[0]; */
    }
}

/* FUN_000eaf7c @ 0x000eaf7c   (est. cl4_table_entry_resolve_24)
 * Ghidra: long FUN_000eaf7c(ulong p1)
 * Table entry resolve (cf. 0xe88f4) using offset 0x24: dereferences p1&~1
 * if the tag bit is set, returns (base+0x24)+(int)*(base+0x24).
 * Confidence: low
 * Notes: offset-encoded entry table; first-entry address. */
uint64_t cl4_table_entry_resolve_24(uint64_t p1)
{
    if ((p1 & 1) != 0) {
        p1 = *(uint64_t *)(p1 & 0xfffffffffffffffeULL);
    }
    return (p1 + 0x24) + (int64_t)*(int32_t *)(p1 + 0x24);
}

/* FUN_000eafac @ 0x000eafac   (est. cl4_table_entry_resolve_2c)
 * Ghidra: long FUN_000eafac(ulong p1)
 * Table entry resolve (cf. 0xe88f4) using offset 0x2c: dereferences p1&~1
 * if the tag bit is set, returns (base+0x2c)+(int)*(base+0x2c).
 * Confidence: low
 * Notes: offset-encoded entry table; first-entry address. */
uint64_t cl4_table_entry_resolve_2c(uint64_t p1)
{
    if ((p1 & 1) != 0) {
        p1 = *(uint64_t *)(p1 & 0xfffffffffffffffeULL);
    }
    return (p1 + 0x2c) + (int64_t)*(int32_t *)(p1 + 0x2c);
}

/* FUN_000eafdc / FUN_000eafe0 @ 0xeafdc / 0xeafe0  (est. cl4_exc_cap_acq_cb_a/b)
 * Ghidra: void FUN_000eafdc(undefined8 p1, undefined8 p2) /
 *         void FUN_000eafe0(undefined8 p1, undefined8 p2)
 * Capability-acquire callbacks: forward p1/p2 plus the four context fields
 * (x20+0x20, +0x28, +0x10, +0x18) to FUN_000eac74 (0xeac74). Two entry
 * points for distinct call sites.
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register. */
void cl4_exc_cap_acq_cb_a(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000eac74(p1, *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18), p2);
}
void cl4_exc_cap_acq_cb_b(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000eac74(p1, *(uint64_t *)(ctx + 0x20), *(uint64_t *)(ctx + 0x28),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18), p2);
}

/* FUN_000eb0ec @ 0x000eb0ec   (est. cl4_caps_alloc_typed)
 * Ghidra: undefined1[16] FUN_000eb0ec(long p1)
 * Allocates a typed capability. Resolves the object type table via
 * FUN_00377dcc and, if its size word is below 0x40, grows the allocation
 * window (local_28 = *(base-8)+0x40) and invokes FUN_00374104 to allocate;
 * returns 0 if that fails. If the size is >= 0x40 it returns the existing
 * base with size 0x3f.
 * Confidence: low
 * Notes: returns a {base,size} pair; FUN_00374104 is the allocation op. */
cl4_result_t cl4_caps_alloc_typed(uint64_t p1)
{
    cl4_result_t r1 = FUN_00377dcc(0x13f, *(uint64_t *)(p1 + 0x38));  /* out of slice */
    cl4_result_t r2;
    if (r1.hi < 0x40) {
        uint64_t win = *(uint64_t *)(r1.lo - 8) + 0x40;
        r2 = FUN_00374104(p1, 0, 1, &win, p1 + 0x48);  /* out of slice; alloc */
        if (r2.lo == 0) {
            r2.lo = 0;
            r2.hi = 0;
        }
    } else {
        r2.hi = 0x3f;
        r2.lo = r1.lo;
    }
    return r2;
}

/* FUN_000eb184 @ 0x000eb184   (est. cl4_caps_table_base)
 * Ghidra: void FUN_000eb184(void)
 * Tail thunk to FUN_00021480 (out of slice), the capability table base
 * resolver.
 * Confidence: low
 * Notes: single tail call to out-of-slice FUN_00021480. */
void cl4_caps_table_base(void)
{
    FUN_00021480();  /* out of slice */
}

/* FUN_000eb19c @ 0x000eb19c   (est. cl4_caps_bounds_check)
 * Ghidra: void FUN_000eb19c(ulong p1, long p2)
 * Bounds check for a capability table index: p1 is negative or >=
 * *(p2+0x10) (the table length) → traps via SoftwareBreakpoint
 * (0xeb1b4 / 0xeb1b8). Otherwise returns silently.
 * Confidence: low
 * Notes: array-bounds trap; does not return on overflow. */
void cl4_caps_bounds_check(uint64_t p1, uint64_t p2)
{
    if ((int64_t)p1 < 0) {
        SoftwareBreakpoint(1, 0xeb1b4);  /* trap */
    }
    if (p1 < *(uint64_t *)(p2 + 0x10)) {
        return;
    }
    SoftwareBreakpoint(1, 0xeb1b8);  /* trap */
}

/* FUN_000eb1e8 @ 0x000eb1e8   (est. cl4_caps_copy_word)
 * Ghidra: void FUN_000eb1e8(undefined8 *p1, undefined8 *p2)
 * Copies *p2 into *p1 and runs the out-of-slice continuation FUN_000db8f8.
 * Confidence: low
 * Notes: FUN_000db8f8 is the copy-completion helper. */
void cl4_caps_copy_word(uint64_t *p1, uint64_t *p2)
{
    *p1 = *p2;
    FUN_000db8f8();  /* out of slice */
}

/* FUN_000eb218 / FUN_000eb21c @ 0xeb218 / 0xeb21c  (est. cl4_caps_disp8_cb_a/b)
 * Ghidra: void FUN_000eb218(undefined8 p1, undefined8 p2) /
 *         void FUN_000eb21c(undefined8 p1, undefined8 p2)
 * Forward p1/p2 plus the context fields (x20+0x10, x20+0x18) to the
 * 8-argument op dispatcher 0xea2f8. Two entry points for distinct sites.
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register. */
void cl4_caps_disp8_cb_a(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000ea2f8(p1, (uint64_t *)*(uint64_t *)(ctx + 0x10),
                 *(uint64_t *)(ctx + 0x18), p2);
}
void cl4_caps_disp8_cb_b(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000ea2f8(p1, (uint64_t *)*(uint64_t *)(ctx + 0x10),
                 *(uint64_t *)(ctx + 0x18), p2);
}

/* FUN_000eb238 @ 0x000eb238   (est. cl4_table_entry_resolve_14)
 * Ghidra: long FUN_000eb238(ulong p1)
 * Table entry resolve (cf. 0xe88f4) using offset 0x14.
 * Confidence: low
 * Notes: offset-encoded entry table; first-entry address. */
uint64_t cl4_table_entry_resolve_14(uint64_t p1)
{
    if ((p1 & 1) != 0) {
        p1 = *(uint64_t *)(p1 & 0xfffffffffffffffeULL);
    }
    return (p1 + 0x14) + (int64_t)*(int32_t *)(p1 + 0x14);
}

/* FUN_000eb268 / FUN_000eb26c @ 0xeb268 / 0xeb26c  (est. cl4_caps_disp6_cb_a/b)
 * Ghidra: void FUN_000eb268(undefined8 p1, undefined8 p2) /
 *         void FUN_000eb26c(undefined8 p1, undefined8 p2)
 * Forward p1/p2 plus the context fields (x20+0x10, x20+0x18) to the
 * 6-argument op dispatcher 0xea5c8. Two entry points.
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register. */
void cl4_caps_disp6_cb_a(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000ea5c8(p1, (uint64_t *)*(uint64_t *)(ctx + 0x10),
                 *(uint64_t *)(ctx + 0x18), p2);
}
void cl4_caps_disp6_cb_b(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000ea5c8(p1, (uint64_t *)*(uint64_t *)(ctx + 0x10),
                 *(uint64_t *)(ctx + 0x18), p2);
}

/* FUN_000eb288 / FUN_000eb28c @ 0xeb288 / 0xeb28c  (est. cl4_caps_val_ctx_cb_a/b)
 * Ghidra: void FUN_000eb288(undefined8 p1, undefined8 p2) /
 *         void FUN_000eb28c(undefined8 p1, undefined8 p2)
 * Forward p1/p2 plus the context fields (x20+0x10, x20+0x18) to the context
 * validator 0xea694. Two entry points.
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register. */
void cl4_caps_val_ctx_cb_a(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000ea694(p1, *(uint64_t *)(ctx + 0x10),
                 (uint64_t *)*(uint64_t *)(ctx + 0x18), (uint64_t *)p2);
}
void cl4_caps_val_ctx_cb_b(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000ea694(p1, *(uint64_t *)(ctx + 0x10),
                 (uint64_t *)*(uint64_t *)(ctx + 0x18), (uint64_t *)p2);
}

/* FUN_000eb2a8 @ 0x000eb2a8   (est. cl4_table_entry_resolve_18)
 * Ghidra: long FUN_000eb2a8(ulong p1)
 * Table entry resolve (cf. 0xe88f4) using offset 0x18.
 * Confidence: low
 * Notes: offset-encoded entry table; first-entry address. */
uint64_t cl4_table_entry_resolve_18(uint64_t p1)
{
    if ((p1 & 1) != 0) {
        p1 = *(uint64_t *)(p1 & 0xfffffffffffffffeULL);
    }
    return (p1 + 0x18) + (int64_t)*(int32_t *)(p1 + 0x18);
}

/* FUN_000eb2d8 @ 0x000eb2d8   (est. cl4_caps_release_if_tagged)
 * Ghidra: void FUN_000eb2d8(undefined8 p1, ulong p2)
 * If p2 has any of the tag bits in 0x7000000000000007 set (i.e.
 * (p2^~0)&0x7000000000000007 != 0), releases the reference via
 * FUN_000db888; otherwise no-op.
 * Confidence: low
 * Notes: tag-bit mask check before release. */
void cl4_caps_release_if_tagged(uint64_t p1, uint64_t p2)
{
    if (((p2 ^ 0xffffffffffffffffULL) & 0x7000000000000007ULL) == 0) {
        return;
    }
    FUN_000db888(p2);  /* out of slice; release */
}

/* FUN_000eb2f4 @ 0x000eb2f4   (est. cl4_caps_grow_table)
 * Ghidra: void FUN_000eb2f4(long *p1)
 * Grows / rebalances the array *p1: reads its count (FUN_003a261c or
 * FUN_0007be8c), and if the free/used measure from FUN_0029369c indicates
 * spare capacity it compacts via FUN_000eba8c (releasing the old backing
 * store), otherwise (non-empty) allocates a new slot via FUN_000eb79c.
 * Writes the possibly-relocated table back into *p1.
 * Confidence: low
 * Notes: unaff_x21 caller-preserved context register; grow/shrink helper. */
void cl4_caps_grow_table(uint64_t *p1)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t t = *p1;
    uint64_t v = FUN_003a261c(t);  /* out of slice */
    if ((v & 1) == 0) {
        t = FUN_0007be8c(t);  /* out of slice */
    }
    v = *(uint64_t *)(t + 0x10);
    uint64_t slot = t + 0x20;
    uint64_t count = v;
    int64_t m = FUN_0029369c(v);  /* out of slice */
    if (m < (int64_t)v) {
        FUN_000eba8c(v >> 1, &slot, (uint64_t)m);  /* 0xeba8c; compact */
        if (ctx_flag == 0) {
            FUN_0036b118();  /* out of slice; release */
        }
    } else if (v != 0) {
        FUN_000eb79c(0, v, 1, &slot);  /* 0xeb79c; grow */
    }
    *p1 = t;
}

/* FUN_000eb3ac @ 0x000eb3ac   (est. cl4_caps_sort_records)
 * Ghidra: void FUN_000eb3ac(long *p1, undefined8 p2, long *p3, long p4)
 * Sorts an array of 2-word capability records (*p3, count at p3[1]) and
 * records the resulting sorted ranges into the growable table *p1.
 * Implements a partition/merge (insertion + block swap) over the records,
 * keyed by the pair words, with param_4 as a merge-granule threshold.
 * Every out-of-range or overflow condition traps (SoftwareBreakpoint at
 * 0xeb71c..0xeb798). Records produced ranges {start,end} into *p1 and, when
 * *p1 is exhausted, re-sorts via FUN_000eb82c/FUN_000ebb34.
 * Confidence: low
 * Notes: large comparison-sort with pervasive bounds traps; unaff_x21 is the
 * loop-completion context register; &DAT_00657778 is the empty-table base. */
void cl4_caps_sort_records(uint64_t *p1, uint64_t p2, uint64_t *p3, uint64_t p4)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t tbl = 0x657778;  /* &DAT_00657778 */
    uint64_t cur = 0;
    uint64_t cap = 0;

    do {
        cap = tbl;
        uint64_t count = p3[1];
        if ((int64_t)count <= (int64_t)cur) {
            /* table drain path */
            uint64_t t = *p1;
            if (t == 0) {
                SoftwareBreakpoint(1, 0xeb79c);  /* trap */
            }
            cur = FUN_003a261c(tbl);  /* out of slice */
            if ((cur & 1) == 0) {
                cap = FUN_000f9930(cap);  /* out of slice */
            }
            cur = *(uint64_t *)(cap + 0x10);
            /* re-sort from table tail */
            goto drain_table;
        }
        /* partition pass over records [cur..count) */
        uint64_t hi = cur + 1;
        if ((int64_t)hi < (int64_t)count) {
            if ((int64_t)cur < -1) {
                SoftwareBreakpoint(1, 0xeb76c);  /* trap */
            }
            uint64_t *arr = (uint64_t *)*p3;
            uint64_t a = *(uint64_t *)(arr + hi * 2);      /* keyA */
            uint64_t a0 = *(uint64_t *)(arr + cur * 2);    /* keyCur */
            uint64_t x = a, b = hi;
            uint64_t w = cur + 2;
            /* insertion partition scan */
            for (;;) {
                uint64_t wc = w;
                uint64_t nx = b + 1;
                if (/* SCARRY8 */ 0) {
                    SoftwareBreakpoint(1, 0xeb75c);  /* trap */
                }
                hi = count;
                if ((int64_t)count <= (int64_t)nx) break;
                hi = *(uint64_t *)(arr + nx * 2);
                bool ord = x <= hi;
                b = b + 1;
                x = hi;
                w = wc + 1;
                hi = nx;
                if (a < a0 != ord) break;
            }
            if (a < a0) {
                /* swap block [cur, hi) with [w, ...) */
                if ((int64_t)hi < (int64_t)cur) {
                    SoftwareBreakpoint(1, 0xeb788);  /* trap */
                }
                if ((int64_t)cur < (int64_t)hi) {
                    uint64_t lim = (w <= count) ? w : count;
                    uint64_t *dst = (uint64_t *)(arr + cur * 2);
                    uint64_t l = cur, r = hi;
                    uint64_t *src = (uint64_t *)(arr + lim * 2);
                    for (;;) {
                        uint64_t *sp = src - 2;
                        uint64_t rm = r - 1;
                        if (l != rm) {
                            if (((int64_t)count < (int64_t)r || (int64_t)count <= (int64_t)l) ||
                                ((int64_t)(l | rm) < 0)) {
                                SoftwareBreakpoint(1, 0xeb764);  /* trap */
                            }
                            if (arr == 0) {
                                SoftwareBreakpoint(1, 0xeb790);  /* trap */
                            }
                            uint64_t d1 = dst[1], d0 = dst[0], s0 = *sp;
                            dst[1] = src[-1];
                            dst[0] = s0;
                            src[-1] = d1;
                            *sp = d0;
                        }
                        l = l + 1;
                        dst += 2;
                        r = rm;
                        src = sp;
                        if ((int64_t)l >= (int64_t)rm) break;
                    }
                    count = p3[1];
                }
            }
        }
        uint64_t e = hi;
        if ((int64_t)hi < (int64_t)count) {
            if (/* SBORROW8 */ 0) {
                SoftwareBreakpoint(1, 0xeb770);  /* trap */
            }
            if ((int64_t)(hi - cur) < (int64_t)p4) {
                if (/* SCARRY8 */ 0) {
                    SoftwareBreakpoint(1, 0xeb780);  /* trap */
                }
                uint64_t lim = cur + p4;
                if ((int64_t)count <= (int64_t)(cur + p4)) {
                    lim = count;
                }
                if ((int64_t)lim < (int64_t)cur) {
                    SoftwareBreakpoint(1, 0xeb784);  /* trap */
                }
                if (hi != lim) {
                    /* insertion sort the run [hi, lim) */
                    uint64_t *arr = (uint64_t *)*p3;
                    uint64_t *wp = (uint64_t *)(arr + hi * 2);
                    uint64_t w = hi;
                    uint64_t *ws = wp;
                    do {
                        uint64_t r = hi - 1;
                        if (/* SBORROW8 */ 0) {
                            SoftwareBreakpoint(1, 0xeb71c);  /* trap */
                        }
                        if ((int64_t)hi < 0 || (int64_t)count <= (int64_t)w) {
                            SoftwareBreakpoint(1, 0xeb720);  /* trap */
                        }
                        if ((int64_t)r < 0 || (int64_t)count <= (int64_t)r) {
                            SoftwareBreakpoint(1, 0xeb724);  /* trap */
                        }
                        hi = *wp;
                        uint64_t *prev = (uint64_t *)(arr + r * 2);
                        if (hi < *prev) {
                            if (arr == 0) {
                                SoftwareBreakpoint(1, 0xeb78c);  /* trap */
                            }
                            uint64_t x1 = wp[1], p0 = *prev;
                            wp[1] = prev[1];
                            wp[0] = p0;
                            *prev = hi;
                            prev[1] = x1;
                            wp -= 2;
                            hi = r;
                            if (r != cur) continue;
                        }
                        if (/* SCARRY8 */ 0) {
                            SoftwareBreakpoint(1, 0xeb760);  /* trap */
                        }
                        hi = w + 1;
                        wp = ws + 2;
                        uint64_t r2 = lim;
                        w = hi;
                        ws = wp;
                    } while (hi != lim);
                }
            }
        }
        if ((int64_t)e < (int64_t)cur) {
            SoftwareBreakpoint(1, 0xeb768);  /* trap */
        }
        /* append {cur, e} range to *tbl */
        uint64_t c2 = FUN_003a261c(tbl);
        if ((c2 & 1) == 0) {
            cap = FUN_000f9680(0, *(uint64_t *)(cap + 0x10) + 1, 1, cap);  /* out of slice */
        }
        c2 = *(uint64_t *)(cap + 0x10);
        if (*(uint64_t *)(cap + 0x18) >> 1 <= c2) {
            cap = FUN_000f9680(1 < *(uint64_t *)(cap + 0x18), c2 + 1, 1, cap);
        }
        *(uint64_t *)(cap + 0x10) = c2 + 1;
        *(uint64_t *)(cap + c2 * 0x10 + 0x20) = cur;
        *(uint64_t *)(cap + c2 * 0x10 + 0x28) = e;
        tbl = cap;
        if (*p1 == 0) {
            SoftwareBreakpoint(1, 0xeb794);  /* trap */
        }
        FUN_000eb82c(&tbl, *p1, p3);  /* 0xeb82c; merge ranges */
        cap = tbl;
        cur = e;
    } while (ctx_flag == 0);

    FUN_0036b118(cap);  /* out of slice; release */
    return;

drain_table:
    if (cur < 2) {
        FUN_0036b118(cap);
        return;
    }
    uint64_t *arr = (uint64_t *)*p3;
    if (arr == 0) {
        SoftwareBreakpoint(1, 0xeb798);  /* trap */
    }
    uint64_t *e3 = (uint64_t *)(cap + cur * 0x10);
    uint64_t l23 = *e3;
    uint64_t *rng = (uint64_t *)(cap + cur * 2);
    uint64_t g = rng[1];
    FUN_000ebb34(arr + l23 * 2, arr + *rng * 2, arr + g * 2, *p1);  /* 0xebb34 */
    if (ctx_flag != 0) {
        FUN_0036b118(cap);
        return;
    }
    if ((int64_t)g < (int64_t)l23) {
        SoftwareBreakpoint(1, 0xeb774);  /* trap */
    }
    uint64_t total = *(uint64_t *)(cap + 0x10);
    if (total <= cur - 2) {
        SoftwareBreakpoint(1, 0xeb778);  /* trap */
    }
    e3[0] = l23;
    e3[1] = g;
    uint64_t rem = total - cur;
    if (total < cur) {
        SoftwareBreakpoint(1, 0xeb77c);  /* trap */
    }
    cur = total - 1;
    FUN_00117d14((uint64_t *)(cap + cur * 2), (uint64_t *)(cap + (cur + 2) * 2), rem * 0x10);  /* out of slice; memmove */
    *(uint64_t *)(cap + 0x10) = cur;
    goto drain_table;
}

/* FUN_000eb79c @ 0x000eb79c   (est. cl4_caps_partition_insert)
 * Ghidra: void FUN_000eb79c(long p1, long p2, long p3, long *p4)
 * Insertion partition of the 2-word records in *p4 over [p3, p2): scans
 * records downward, swapping each into place while its key is smaller than
 * its predecessor. Bounds traps at 0xeb820..0xeb82c.
 * Confidence: low
 * Notes: comparison-sort primitive; swapped as 2-word pairs. */
void cl4_caps_partition_insert(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t *p4)
{
    uint64_t base;
    uint64_t *wp, *ws;
    uint64_t w = p3;

    if (p3 == p2) {
        return;
    }
    base = *p4;
    uint64_t count = p4[1];
    wp = (uint64_t *)(base + p3 * 0x10);
    ws = wp;
    for (;;) {
        uint64_t r = p3 - 1;
        if (/* SBORROW8 */ 0) {
            SoftwareBreakpoint(1, 0xeb820);  /* trap */
        }
        if (p3 < 0 || count <= w) {
            SoftwareBreakpoint(1, 0xeb824);  /* trap */
        }
        if (r < 0 || count <= r) {
            SoftwareBreakpoint(1, 0xeb828);  /* trap */
        }
        uint64_t key = *wp;
        uint64_t *prev = (uint64_t *)(base + r * 0x10);
        if (key < *prev) {
            if (base == 0) {
                SoftwareBreakpoint(1, 0xeb82c);  /* trap */
            }
            uint64_t x1 = wp[1], p0 = *prev;
            wp[1] = prev[1];
            wp[0] = p0;
            *prev = key;
            prev[1] = x1;
            wp -= 2;
            p3 = r;
            if (r == p1) continue;
        }
        p3 = w + 1;
        wp = ws + 2;
        ws = wp;
        w = p3;
        if (p3 == p2) return;
    }
}

/* FUN_000eb82c @ 0x000eb82c   (est. cl4_caps_ranges_merge)
 * Ghidra: undefined8 FUN_000eb82c(long *p1, undefined8 p2, long *p3)
 * Merges the sorted-range table *p1 (2-word {start,end} records, count at
 * +0x10) against the record array *p3. Re-balances adjacent ranges whose
 * combined span is smaller than a neighbour (sum-of-deltas comparisons) and
 * calls FUN_000ebb34 to merge overlapping ranges, shrinking the table with
 * a memmove (FUN_00117d14). Returns 1 on success. Bounds traps at
 * 0xeba44..0xeba8c.
 * Confidence: low
 * Notes: unaff_x21 is the completion context register. */
uint64_t cl4_caps_ranges_merge(uint64_t *p1, uint64_t p2, uint64_t *p3)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint64_t t = *p1;

    if (*(uint64_t *)(t + 0x10) <= 1) {
        return 1;
    }
    uint64_t v = FUN_003a261c(t);
    if ((v & 1) == 0) {
        t = FUN_000f9930(t);  /* out of slice */
    }
    *p1 = t;
    uint64_t base = t + 0x20;
    uint64_t n = *(uint64_t *)(t + 0x10);
    for (;;) {
        uint64_t m = n - 1;
        uint64_t *cur = (uint64_t *)(t + n * 0x10);
        uint64_t *prev = (uint64_t *)(base + m * 0x10);
        uint64_t dA = 0;
        if (n < 4) {
            if (n == 3) {
                /* compare first two ranges */
                bool b = (int64_t)*(uint64_t *)(t + 0x28) < (int64_t)*(uint64_t *)(t + 0x20);
                dA = *(uint64_t *)(t + 0x28) - *(uint64_t *)(t + 0x20);
                goto cmp;
            }
            if (n < 2) {
                SoftwareBreakpoint(1, 0xeba64);  /* trap */
            }
            uint64_t d = cur[1] - cur[0];
            if (/* borrow */ 0) {
                SoftwareBreakpoint(1, 0xeba70);  /* trap */
            }
            if (/* prev borrow */ 0) {
                SoftwareBreakpoint(1, 0xeba78);  /* trap */
            }
            if (prev[1] - prev[0] < d) break;
            n = m;
            continue;
        } else {
            uint64_t e = base + n * 0x10;
            dA = *(uint64_t *)(e - 0x38) - *(uint64_t *)(e - 0x40);
            uint64_t dB = *(uint64_t *)(e - 0x28) - *(uint64_t *)(e - 0x30);
            uint64_t dC = cur[1] - cur[0];
            if (dA + dC < *(uint64_t *)(e - 0x38) - *(uint64_t *)(e - 0x40)) {
                goto cmp;
            }
            /* else */
            if (/* prev borrow */ 0) {
                SoftwareBreakpoint(1, 0xeba80);  /* trap */
            }
            n = n - 2;
            if (prev[1] - prev[0] <= dA) {
                n = m;
            }
            continue;
        }
cmp:
        /* merge ranges at indices m and n */
        if (/* borrow */ 0) {
            SoftwareBreakpoint(1, 0xeba5c);  /* trap */
        }
        uint64_t d1 = cur[1] - cur[0];
        uint64_t d2 = prev[1] - prev[0];
        if (/* SCARRY8 */ 0) {
            SoftwareBreakpoint(1, 0xeba7c);  /* trap */
        }
        if (d1 + d2 < dA) {
            /* n = m path */
            uint64_t x = prev[1] - prev[0];
            if (/* borrow */ 0) {
                SoftwareBreakpoint(1, 0xeba68);  /* trap */
            }
            uint64_t y = cur[1] - cur[0];
            if (/* SCARRY8 */ 0) {
                SoftwareBreakpoint(1, 0xeba74);  /* trap */
            }
            if (x + y < dA) {
                if (/* borrow */ 0) {
                    SoftwareBreakpoint(1, 0xeba70);  /* trap */
                }
                if (cur[1] - cur[0] < x) { /* not reached */ }
                n = m;
                continue;
            }
        }
        /* merge ranges m,n via FUN_000ebb34 */
        if (n <= m) {
            SoftwareBreakpoint(1, 0xeba44);  /* trap */
        }
        uint64_t *arr = (uint64_t *)*p3;
        if (arr == 0) {
            *p1 = t;
            SoftwareBreakpoint(1, 0xeba8c);  /* trap */
        }
        uint64_t *pm = (uint64_t *)(base + m * 0x10);
        uint64_t lm = *pm;
        uint64_t *pn = (uint64_t *)(base + n * 0x10);
        uint64_t ln = pn[1];
        FUN_000ebb34(arr + lm * 2, arr + *pn * 2, arr + ln * 2, p2);  /* 0xebb34 */
        if (ctx_flag != 0) break;
        if (ln < lm) {
            SoftwareBreakpoint(1, 0xeba48);  /* trap */
        }
        if (*(uint64_t *)(t + 0x10) <= m) {
            SoftwareBreakpoint(1, 0xeba4c);  /* trap */
        }
        pm[0] = lm;
        pm[1] = ln;
        uint64_t total = *(uint64_t *)(t + 0x10);
        if (total <= n) {
            SoftwareBreakpoint(1, 0xeba50);  /* trap */
        }
        n = total - 1;
        FUN_00117d14((uint64_t *)(base + n * 0x10), (uint64_t *)(base + (n + 2) * 0x10),
                     (n - n) * 0x10);  /* out of slice; memmove */
        *(uint64_t *)(t + 0x10) = n;
        n = n; /* use last */
        if (!(2 < m)) break;
    }
    *p1 = t;
    return 1;
}

/* FUN_000eba8c @ 0x000eba8c   (est. cl4_caps_sort_alloc)
 * Ghidra: undefined * FUN_000eba8c(long p1, undefined8 p2, undefined8 p3)
 * Allocates a fresh range table of p1 2-word entries and sorts them via
 * FUN_000eb3ac. Returns the new table (or &DAT_00657778 when empty), with
 * count reset to 0. On a negative p1 it traps (0xebb34).
 * Confidence: low
 * Notes: unaff_x21 is the completion context register; FUN_000f958c is the
 * table allocator. */
uint8_t *cl4_caps_sort_alloc(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t ctx_flag = 0;  /* unaff_x21 */
    uint8_t *t;
    uint64_t local_50;
    uint64_t lStack_48;

    if (p1 < 0) {
        SoftwareBreakpoint(1, 0xebb34);  /* trap */
    }
    if (p1 == 0) {
        t = (uint8_t *)0x657778;  /* &DAT_00657778 */
    } else {
        t = (uint8_t *)FUN_000f958c(p1);  /* out of slice; alloc */
        *(uint64_t *)(t + 0x10) = p1;
    }
    local_50 = (uint64_t)t + 0x20;
    lStack_48 = p1;
    FUN_000eb3ac(&local_50, /* auStack_38 */ 0, (uint64_t *)p2, p3);  /* 0xeb3ac; sort */
    *(uint64_t *)(t + 0x10) = 0;
    if (ctx_flag != 0) {
        FUN_0036b118((uint64_t)t);  /* out of slice; release */
    }
    return t;
}

/* FUN_000ebb34 @ 0x000ebb34   (est. cl4_caps_merge_runs)
 * Ghidra: undefined8 FUN_000ebb34(ulong *p1, ulong *p2, ulong *p3, ulong *p4)
 * Merges two adjacent sorted runs of 2-word records: run A [p1,p2) and run
 * B [p2,p3), producing a merged run via the scratch buffer p4. Runs
 * FUN_00072044 (out of slice) on the shorter run, then interleaves records
 * by key, copying survivors with a memmove (FUN_00117d14). Returns 1.
 * Bounds trap at 0xebcbc on an overrun.
 * Confidence: low
 * Notes: standard 2-way merge; param_4 is a scratch region. */
uint64_t cl4_caps_merge_runs(uint64_t *p1, uint64_t *p2, uint64_t *p3, uint64_t *p4)
{
    int64_t n1 = ((int64_t)p2 - (int64_t)p1) / 0x10;
    int64_t n2 = ((int64_t)p3 - (int64_t)p2) / 0x10;
    uint64_t *dst, *src, *pa, *pb;
    uint64_t *ps;

    if (n1 < n2) {
        FUN_00072044(p1, n1, p4);  /* out of slice; copy run A to scratch */
        pa = p4 + n1 * 2;
        dst = p1;
        while (p4 < pa && p2 < p3) {
            if (*p2 < *p4) {
                pa = p4;
                src = p2;
                p2 += 2;
            } else {
                pa = p4 + 2;
                src = p4;
            }
            p4 = pa;
            if (dst != src) {
                uint64_t k = *src;
                dst[1] = src[1];
                dst[0] = k;
            }
            dst += 2;
        }
        if ((int64_t)pa - (int64_t)p4 < -0xf) {
            SoftwareBreakpoint(1, 0xebcbc);  /* trap */
        }
        int64_t rem = ((int64_t)pa - (int64_t)p4) / 0x10;
        if (dst != p4 || p4 + rem * 2 <= dst) {
            FUN_00117d14(dst, p4, rem << 4);  /* out of slice; memmove */
        }
        return 1;
    }
    /* symmetric merge with runs reversed */
    FUN_00072044(p2, n2, p4);
    pa = p4 + n2 * 2;
    for (;;) {
        dst = p2;
        p2 = dst - 2;
        pb = pa;
        for (;;) {
            ps = p3;
            pa = pb;
            p3 = ps - 2;
            if (dst <= p1 || pb <= p4) goto finish;
            pb = pb - 2;
            if (*pb < *p2) break;
            if (pb != ps) {
                uint64_t k = *pb;
                ps[-1] = pb[-1];
                *p3 = k;
            }
        }
        if (ps != dst) {
            uint64_t k = *p2;
            ps[-1] = dst[-1];
            *p3 = k;
        }
    }
finish:
    if ((int64_t)pa - (int64_t)p4 < -0xf) {
        SoftwareBreakpoint(1, 0xebcbc);  /* trap */
    }
    int64_t rem = ((int64_t)pa - (int64_t)p4) / 0x10;
    if (dst != p4 || p4 + rem * 2 <= dst) {
        FUN_00117d14(dst, p4, rem << 4);  /* out of slice; memmove */
    }
    return 1;
}

/* FUN_000ebcbc @ 0x000ebcbc   (est. cl4_table_entry_resolve_4)
 * Ghidra: long FUN_000ebcbc(ulong p1)
 * Table entry resolve (cf. 0xe88f4) using offset 4.
 * Confidence: low
 * Notes: offset-encoded entry table; first-entry address. */
uint64_t cl4_table_entry_resolve_4(uint64_t p1)
{
    if ((p1 & 1) != 0) {
        p1 = *(uint64_t *)(p1 & 0xfffffffffffffffeULL);
    }
    return (p1 + 4) + (int64_t)*(int32_t *)(p1 + 4);
}

/* FUN_000ebcec / FUN_000ebcf0 @ 0xebcec / 0xebcf0  (est. cl4_caps_disp5_cb_a/b)
 * Ghidra: void FUN_000ebcec(undefined8 p1, undefined8 p2) /
 *         void FUN_000ebcf0(undefined8 p1, undefined8 p2)
 * Forward p1/p2 plus the context fields (x20+0x20, +0x10, +0x18) to the
 * 5-argument op dispatcher 0xea4dc. Two entry points.
 * Confidence: low
 * Notes: unaff_x20 caller-preserved context register. */
void cl4_caps_disp5_cb_a(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000ea4dc(p1, (uint64_t *)*(uint64_t *)(ctx + 0x20),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18), p2);
}
void cl4_caps_disp5_cb_b(uint64_t p1, uint64_t p2)
{
    uint64_t ctx = 0;  /* unaff_x20 */
    FUN_000ea4dc(p1, (uint64_t *)*(uint64_t *)(ctx + 0x20),
                 *(uint64_t *)(ctx + 0x10), *(uint64_t *)(ctx + 0x18), p2);
}

/* FUN_000ebd10 @ 0x000ebd10   (est. cl4_caps_obj_lazy_init)
 * Ghidra: void FUN_000ebd10(long *p1, undefined8 p2, undefined8 p3)
 * Lazily initializes the object at *p1. If *p1 is still null, it resolves
 * the object type/name via FUN_00027614(p2,p3), registers it through
 * FUN_000ebf24, and materializes the object handle with FUN_00376820,
 * storing it into *p1.
 * Confidence: low
 * Notes: single-shot lazy init guarded by *p1==0. */
void cl4_caps_obj_lazy_init(uint64_t *p1, uint64_t p2, uint64_t p3)
{
    if (*p1 == 0) {
        uint64_t v = FUN_00027614(p2, p3);  /* out of slice; resolve */
        FUN_000ebf24(v, v);  /* 0xebf24 */
        uint64_t h = FUN_00376820();  /* out of slice; materialize */
        *p1 = h;
    }
}

/* FUN_000ebd54 @ 0x000ebd54   (est. cl4_table_entry_resolve_c)
 * Ghidra: long FUN_000ebd54(ulong p1)
 * Table entry resolve (cf. 0xe88f4) using offset 0xc.
 * Confidence: low
 * Notes: offset-encoded entry table; first-entry address. */
uint64_t cl4_table_entry_resolve_c(uint64_t p1)
{
    if ((p1 & 1) != 0) {
        p1 = *(uint64_t *)(p1 & 0xfffffffffffffffeULL);
    }
    return (p1 + 0xc) + (int64_t)*(int32_t *)(p1 + 0xc);
}

/* FUN_000ebd84 @ 0x000ebd84   (est. cl4_table_entry_resolve_4b)
 * Ghidra: long FUN_000ebd84(ulong p1)
 * Table entry resolve (cf. 0xebcbc) using offset 4; twin of 0xebcbc.
 * Confidence: low
 * Notes: offset-encoded entry table; first-entry address. */
uint64_t cl4_table_entry_resolve_4b(uint64_t p1)
{
    if ((p1 & 1) != 0) {
        p1 = *(uint64_t *)(p1 & 0xfffffffffffffffeULL);
    }
    return (p1 + 4) + (int64_t)*(int32_t *)(p1 + 4);
}

/* FUN_000ebdb4 @ 0x000ebdb4   (est. cl4_caps_query_register)
 * Ghidra: undefined8 FUN_000ebdb4(void)
 * Queries a capability register: calls thunk_FUN_0036f974 for the value and
 * registers it with FUN_0035cf24 against DAT_004c3568; returns the value.
 * Confidence: low
 * Notes: thunk_FUN_0036f974 / FUN_0035cf24 are out of slice. */
uint64_t cl4_caps_query_register(void)
{
    uint64_t v = thunk_FUN_0036f974();  /* out of slice */
    FUN_0035cf24(0x4c3568, v);  /* out of slice */
    return v;
}

/* FUN_000ebed8 / FUN_000ebef0 @ 0xebed8 / 0xebef0  (est. cl4_frame_store_ctx_a/b)
 * Ghidra: void FUN_000ebed8(void) / void FUN_000ebef0(void)
 * Store the caller-preserved x23 register into the caller's frame slot at
 * x29-0xd8. Used as a context-marker in the arg-decode state machine.
 * Confidence: low
 * Notes: unaff_x23/x29 are caller-preserved registers; the frame slot is
 * accessed via the frame pointer x29. */
void cl4_frame_store_ctx_a(void)
{
    uint64_t *frame = 0;  /* unaff_x29 frame base */
    uint64_t x23 = 0;     /* unaff_x23 */
    *(uint64_t *)((uint64_t)frame - 0xd8) = x23;
}
void cl4_frame_store_ctx_b(void)
{
    uint64_t *frame = 0;  /* unaff_x29 */
    uint64_t x23 = 0;     /* unaff_x23 */
    *(uint64_t *)((uint64_t)frame - 0xd8) = x23;
}

/* FUN_000ebf0c @ 0x000ebf0c   (est. cl4_noop_b)
 * Ghidra: void FUN_000ebf0c(void)
 * No-op. Marked as a state-machine step in the arg-decode path.
 * Confidence: high
 * Notes: empty body. */
void cl4_noop_b(void)
{
}

/* FUN_000ebf24 @ 0x000ebf24   (est. cl4_const_0x4e8268)
 * Ghidra: undefined * FUN_000ebf24(void)
 * Returns the fixed data address &DAT_004e8268 (a capability table / state
 * descriptor).
 * Confidence: medium
 * Notes: constant-only return. */
uint8_t *cl4_const_0x4e8268(void)
{
    return (uint8_t *)0x4e8268;
}

/* FUN_000ebf3c @ 0x000ebf3c   (est. cl4_frame_zero_state)
 * Ghidra: void FUN_000ebf3c(void)
 * Clears the caller frame's message-state slots at x29-0x138 (0) and
 * x29-0x130 (0xe000000000000000 status prefix).
 * Confidence: low
 * Notes: unaff_x29 frame base register. */
void cl4_frame_zero_state(void)
{
    uint64_t *frame = 0;  /* unaff_x29 */
    *(uint64_t *)((uint64_t)frame - 0x138) = 0;
    *(uint64_t *)((uint64_t)frame - 0x130) = 0xe000000000000000ULL;
}

/* FUN_000ebf54 @ 0x000ebf54   (est. cl4_frame_read_state)
 * Ghidra: undefined8 FUN_000ebf54(void)
 * Returns the message-state word at x29-0x138.
 * Confidence: low
 * Notes: unaff_x29 frame base register. */
uint64_t cl4_frame_read_state(void)
{
    uint64_t *frame = 0;  /* unaff_x29 */
    return *(uint64_t *)((uint64_t)frame - 0x138);
}

/* FUN_000ebf6c @ 0x000ebf6c   (est. cl4_frame_msg_ptr)
 * Ghidra: long FUN_000ebf6c(void)
 * Returns the message-pointer slot address x29-0xd8.
 * Confidence: low
 * Notes: unaff_x29 frame base register. */
uint64_t cl4_frame_msg_ptr(void)
{
    uint64_t *frame = 0;  /* unaff_x29 */
    return (uint64_t)frame - 0xd8;
}

/* FUN_000ebf80 @ 0x000ebf80   (est. cl4_frame_publish_msg)
 * Ghidra: void FUN_000ebf80(undefined8 p1, undefined8 *p2)
 * Publishes a completed message into *p2: stores the caller-preserved x19
 * and x20 registers as the first two words, marks the type byte (p2+2)=3,
 * and signals completion (FUN_0036986c).
 * Confidence: low
 * Notes: unaff_x19/x20 caller-preserved registers; FUN_0036986c signals
 * completion. */
void cl4_frame_publish_msg(uint64_t p1, uint64_t *p2)
{
    uint64_t x19 = 0;  /* unaff_x19 */
    uint64_t x20 = 0;  /* unaff_x20 */
    p2[0] = x19;
    p2[1] = x20;
    *(uint8_t *)(p2 + 2) = 3;
    FUN_0036986c();  /* out of slice; signal completion */
}

/* FUN_000ebf98 @ 0x000ebf98   (est. cl4_noop_c)
 * Ghidra: void FUN_000ebf98(void)
 * No-op. Called with a diagnostic string in the arg-decode error path.
 * Confidence: high
 * Notes: empty body; arg is a message string address. */
void cl4_noop_c(void)
{
}

/* FUN_000ebfac @ 0x000ebfac   (est. cl4_noop_d)
 * Ghidra: void FUN_000ebfac(void)
 * No-op.
 * Confidence: high
 * Notes: empty body. */
void cl4_noop_d(void)
{
}

/* FUN_000ebfbc @ 0x000ebfbc   (est. cl4_frame_state_pair)
 * Ghidra: undefined1[16] FUN_000ebfbc(void)
 * Returns the pair {x29-0x138, x29-0xd8} (the message-state and
 * message-pointer frame slots).
 * Confidence: low
 * Notes: unaff_x29 frame base register. */
cl4_result_t cl4_frame_state_pair(void)
{
    cl4_result_t r;
    uint64_t *frame = 0;  /* unaff_x29 */
    r.lo = (uint64_t)frame - 0x138;
    r.hi = (uint64_t)frame - 0xd8;
    return r;
}

/* FUN_000ebfcc @ 0x000ebfcc   (est. cl4_frame_state_transition)
 * Ghidra: void FUN_000ebfcc(void)
 * Performs an IPC state transition {status=0xd<<60|0x13,
 * addr=0x80000000005c38e0} via thunk_FUN_002acbb8.
 * Confidence: low
 * Notes: thunk_FUN_002acbb8 is the out-of-slice transition helper. */
void cl4_frame_state_transition(void)
{
    thunk_FUN_002acbb8(0xd000000000000013ULL, 0x80000000005c38e0ULL);
}

/* FUN_000ebfe8 @ 0x000ebfe8   (est. cl4_frame_read_extra)
 * Ghidra: undefined8 FUN_000ebfe8(void)
 * Returns the caller frame word at x29-0x190 (-400).
 * Confidence: low
 * Notes: unaff_x29 frame base register. */
uint64_t cl4_frame_read_extra(void)
{
    uint64_t *frame = 0;  /* unaff_x29 */
    return *(uint64_t *)((uint64_t)frame - 400);
}

/* FUN_000ebff4 @ 0x000ebff4   (est. cl4_frame_flush_state)
 * Ghidra: void FUN_000ebff4(void)
 * Flushes the frame word at x29-0x198 through the message-register helper
 * FUN_003a25d4.
 * Confidence: low
 * Notes: unaff_x29 frame base register. */
void cl4_frame_flush_state(void)
{
    uint64_t *frame = 0;  /* unaff_x29 */
    FUN_003a25d4(*(uint64_t *)((uint64_t)frame - 0x198));  /* out of slice */
}

/* FUN_000ec004 @ 0x000ec004   (est. cl4_caps_grow_needed)
 * Ghidra: bool FUN_000ec004(ulong p1)
 * Returns whether the table/array needs growing: p1 > 1.
 * Confidence: high
 * Notes: trivial predicate. */
bool cl4_caps_grow_needed(uint64_t p1)
{
    return p1 > 1;
}

/* FUN_000ec018 @ 0x000ec018   (est. cl4_frame_write_state)
 * Ghidra: void FUN_000ec018(undefined8 p1)
 * Writes the caller frame message-state slots: x29-0x138 = in_x9 (carried
 * x9 register), x29-0x130 = p1.
 * Confidence: low
 * Notes: unaff_x29 frame base register; in_x9 is a carried register. */
void cl4_frame_write_state(uint64_t p1)
{
    uint64_t *frame = 0;  /* unaff_x29 */
    uint64_t x9 = 0;      /* in_x9 */
    *(uint64_t *)((uint64_t)frame - 0x138) = x9;
    *(uint64_t *)((uint64_t)frame - 0x130) = p1;
}

/* FUN_000ec02c / FUN_000ec038 / FUN_000ec044 @ 0xec02c/0xec038/0xec044
 * (est. cl4_noop_e/f/g)
 * Ghidra: void FUN_000ec02c(void) / void FUN_000ec038(void) /
 *         void FUN_000ec044(void)
 * No-ops used as iterator/state-machine markers in the arg-decode path.
 * Confidence: high
 * Notes: empty bodies. */
void cl4_noop_e(void)
{
}
void cl4_noop_f(void)
{
}
void cl4_noop_g(void)
{
}
