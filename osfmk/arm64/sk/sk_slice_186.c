/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 186: 0x406e34-0x407830 — a block of Swift Concurrency runtime
 * accessors and thunks.
 *
 * This region is the tail of the linked-in Swift `_Concurrency` runtime:
 * small leaf functions that read/write fields of a receiver object (Swift
 * register ABI: `self` in a callee-saved register, rendered by Ghidra as
 * `unaff_x22`), property getters/setters on the task/executor records,
 * no-op `ret`-only stubs, and a few fatal-error / unimplemented-executor
 * traps. Several functions store an incoming register value (rendered as
 * `in_x16` / `in_w8`) into the high word of an out-parameter or return a
 * 16-byte value pair in {lo, hi}.
 *
 * Names use seL4/cL4 vocabulary; all are estimates (Swift ABI, so
 * confidence is low unless the string/address matched). Ghidra FUN_
 * identifiers are retained as the C symbol names (matching the manifest
 * ghidra_name); the estimated meaning lives in the header comment.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* 128-bit value used for Ghidra's `undefined1[16]` returns (lo = bytes 0-7,
 * hi = bytes 8-15). */
typedef struct { uint64_t lo; uint64_t hi; } sk_u128_t;

/* Fatal path: Ghidra renders the "Fatal error" trap as a call to the
 * Swift runtime fatal printer FUN_001afa84. */
#define SK_SWIFT_FATAL() __builtin_trap()

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift helpers referenced by this slice (FUN_ address
 * in the comment; bodies reconstructed by the sibling SK range workers
 * that own them). Signatures reflect the observed register usage.
 * ------------------------------------------------------------------ */
extern void      FUN_003fcc4c(void);      /* concurrency job prologue */
extern void      FUN_00377dcc(uint64_t);  /* task-state transition */
extern void      FUN_001afa84(const char *msg, uint64_t, uint64_t, uint64_t,
                              uint64_t, const char *, uint64_t, uint64_t)
                              __attribute__((noreturn)); /* Swift "Fatal error" */
extern void      FUN_000839d8(uint64_t a, ...);  /* vtable+0x38 indirect dispatch */
extern void      FUN_0040bd24(void);      /* concurrency cleanup/epilogue */
extern void      FUN_00377824(uint64_t a, ...);  /* runtime gate / notify */
extern uint64_t  FUN_000a649c(uint64_t);  /* Swift heap-buffer end projection */
extern void      FUN_0036993c(void);      /* dict/runtime arena cleanup */
extern void      FUN_000839f8(uint64_t a, uint64_t b, uint64_t c); /* vtable+0x30 dispatch */
extern void      FUN_003f637c(void);      /* concurrency deinit helper */
extern void      FUN_0040d098(void);      /* concurrency finalize */
extern void      FUN_003d4658(void);      /* runtime cleanup */
extern void      FUN_0036986c(void);      /* runtime cleanup / release */
extern void      FUN_0036b270(uint64_t);  /* cL4 ref retain (returns obj) */
extern void      FUN_003fc90c(void);      /* witness/closure fn (used as data) */

/* Data / string references (Ghidra names retained; addresses in comments). */
extern const char s_fatal_error[];        /* "Fatal error" s_Fatal_error_005accd0 @ 0x005accd0 */
extern const char s_conc_unimpl_exec[];   /* "Concurrency.UnimplementedExecutor…" @ 0x005dc2b0 */
extern void *DAT_005a14dc;                /* static singleton object @ 0x005a14dc */
extern void *DAT_004edcec;                /* static singleton object @ 0x004edcec */
extern void *DAT_006c0b78;                /* static singleton object @ 0x006c0b78 */

/* Code labels used as values (function pointers stored into fields). */
extern void LAB_003d88e8(void);           /* witness/closure fn @ 0x003d88e8 */
extern void LAB_003df658(void);           /* witness/closure fn @ 0x003df658 */
extern void LAB_003d55b4(void);           /* witness/closure fn @ 0x003d55b4 */
extern void LAB_003deec8(void);           /* witness/closure fn @ 0x003deec8 */

/*--------------------------------------------------------------------*/
/* FUN_00406e34 @ 0x00406e34   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406e34(void)
 * A `ret`-only stub: no state is read or written. Present in the
 * Concurrency vtable as an empty method implementation.
 * Confidence: low */
void FUN_00406e34(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406e48 @ 0x00406e48   (est. sk_conc_state_isnot_running)
 * Ghidra: bool FUN_00406e48(void)
 * Returns whether the 32-bit state word at self+0xb0 is not equal to 1
 * (i.e. the object is not in "running" state). A boolean predicate on
 * the receiver's status field.
 * Confidence: low
 * Notes: unaff_x22 = receiver (`self`), Swift register ABI. */
bool FUN_00406e48(void *self)
{
    return *(int *)((char *)self + 0xb0) != 1;
}

/*--------------------------------------------------------------------*/
/* FUN_00406e64 @ 0x00406e64   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406e64(void)
 * A `ret`-only stub (empty method implementation).
 * Confidence: low */
void FUN_00406e64(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406e78 @ 0x00406e78   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406e78(void)
 * A `ret`-only stub (empty method implementation).
 * Confidence: low */
void FUN_00406e78(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406e8c @ 0x00406e8c   (est. sk_conc_job_finish)
 * Ghidra: void FUN_00406e8c(void)
 * Runs the concurrency job prologue then transitions the task state to 0.
 * The two-call sequence is the tail of a task/job completion path.
 * Confidence: low */
void FUN_00406e8c(void)
{
    FUN_003fcc4c();
    FUN_00377dcc(0);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406eb0 @ 0x00406eb0   (est. sk_conc_unimplemented_executor_fatal)
 * Ghidra: void FUN_00406eb0(ulong param_1)
 * Trap path for an unimplemented Concurrency executor: raises a Swift
 * "Fatal error" with a tagged message referencing the
 * "Concurrency.UnimplementedExecutor" diagnostic string and the supplied
 * parameter (OR-ed with the 0x8000000000000000 tag bit). Never returns.
 * Confidence: high (string match)
 * Notes: s__Concurrency_UnimplementedExecut_005dc2b0; noreturn. */
void FUN_00406eb0(uint64_t param_1)
{
    FUN_001afa84(s_fatal_error, 0xb, 2, 0xd00000000000002a,
                 param_1 | 0x8000000000000000ull,
                 s_conc_unimpl_exec, 0x28, 2);
}

/*--------------------------------------------------------------------*/
/* FUN_00406ee4 @ 0x00406ee4   (est. sk_conc_accessor_epilogue)
 * Ghidra: void FUN_00406ee4(undefined8 param_1)
 * Dispatches via the vtable method at +0x38 (passing param_1, 0, 1) and
 * then runs the concurrency epilogue/cleanup.
 * Confidence: low */
void FUN_00406ee4(uint64_t param_1)
{
    FUN_000839d8(param_1, 0, 1);
    FUN_0040bd24();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406f08 @ 0x00406f08   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406f08(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00406f08(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406f18 @ 0x00406f18   (est. sk_conc_disptach_self_10)
 * Ghidra: void FUN_00406f18(void)
 * Reads the receiver's context words (self+0x10, self+0x38) and performs a
 * vtable +0x38 dispatch with those as the first and fourth arguments.
 * Confidence: low */
void FUN_00406f18(void *self)
{
    FUN_000839d8(*(uint64_t *)((char *)self + 0x10), 1, 1,
                 *(uint64_t *)((char *)self + 0x38));
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406f2c @ 0x00406f2c   (est. sk_conc_pair_get_10)
 * Ghidra: undefined1 [16] FUN_00406f2c(void)
 * Returns the 16-byte value stored at receiver offset +0x10 as a {lo,hi}
 * pair.
 * Confidence: low */
sk_u128_t FUN_00406f2c(void *self)
{
    return *(sk_u128_t *)((char *)self + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_00406f40 @ 0x00406f40   (est. sk_conc_record_set)
 * Ghidra: void FUN_00406f40(undefined8 param_1..param_5)
 * Writes five word arguments plus the x20-captured value into the
 * receiver record at offsets 0x10/0x18/0x20/0x28/0x30/0x38. A
 * multi-field initializer for a task/job record.
 * Confidence: low */
void FUN_00406f40(uint64_t param_1, uint64_t param_2, uint64_t param_3,
                  uint64_t param_4, uint64_t param_5, uint64_t x20, void *self)
{
    *(uint64_t *)((char *)self + 0x30) = x20;
    *(uint64_t *)((char *)self + 0x38) = param_5;
    *(uint64_t *)((char *)self + 0x20) = param_3;
    *(uint64_t *)((char *)self + 0x28) = param_4;
    *(uint64_t *)((char *)self + 0x10) = param_1;
    *(uint64_t *)((char *)self + 0x18) = param_2;
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406f50 @ 0x00406f50   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406f50(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00406f50(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406f60 @ 0x00406f60   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406f60(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00406f60(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406f74 @ 0x00406f74   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406f74(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00406f74(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406f84 @ 0x00406f84   (est. sk_conc_pair_get_58_90)
 * Ghidra: undefined1 [16] FUN_00406f84(long param_1)
 * Writes the incoming register value `in_x16` into out-param_1+8, then
 * returns the {self+0x58, self+0x90} pair. A 16-byte getter that also
 * preserves a secondary register value.
 * Confidence: low */
sk_u128_t FUN_00406f84(uint64_t *param_1, uint64_t x16, void *self)
{
    *(uint64_t *)((char *)param_1 + 8) = x16;
    return (sk_u128_t){ .lo = *(uint64_t *)((char *)self + 0x58),
                        .hi = *(uint64_t *)((char *)self + 0x90) };
}

/*--------------------------------------------------------------------*/
/* FUN_00406fb0 @ 0x00406fb0   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406fb0(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00406fb0(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406fc0 @ 0x00406fc0   (est. sk_conc_identity_3rd)
 * Ghidra: undefined8 FUN_00406fc0(undefined8 param_1, undefined8 param_2,
 *                                 undefined8 param_3)
 * Identity on the third argument: returns param_3 unchanged.
 * Confidence: low */
uint64_t FUN_00406fc0(uint64_t param_1, uint64_t param_2, uint64_t param_3)
{
    (void)param_1;
    (void)param_2;
    return param_3;
}

/*--------------------------------------------------------------------*/
/* FUN_00406fd4 @ 0x00406fd4   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406fd4(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00406fd4(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406fe0 @ 0x00406fe0   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00406fe0(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00406fe0(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00406fec @ 0x00406fec   (est. sk_conc_runtime_gate_full)
 * Ghidra: void FUN_00406fec(void)
 * Invokes the runtime gate with a full (0xff) marker argument.
 * Confidence: low */
void FUN_00406fec(void)
{
    FUN_00377824(0xff);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407000 @ 0x00407000   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407000(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407000(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0040700c @ 0x0040700c   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_0040700c(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_0040700c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407018 @ 0x00407018   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407018(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407018(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407024 @ 0x00407024   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407024(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407024(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407030 @ 0x00407030   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407030(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407030(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407048 @ 0x00407048   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407048(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407048(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407060 @ 0x00407060   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407060(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407060(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407070 @ 0x00407070   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407070(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407070(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407080 @ 0x00407080   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407080(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407080(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407090 @ 0x00407090   (est. sk_conc_const_zero)
 * Ghidra: undefined8 FUN_00407090(void)
 * Returns the constant 0.
 * Confidence: low */
uint64_t FUN_00407090(void)
{
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_004070a0 @ 0x004070a0   (est. sk_conc_accessor_epilogue)
 * Ghidra: void FUN_004070a0(undefined8 param_1, undefined8 param_2)
 * Dispatches via vtable +0x38 with (param_1, param_2, 1), then runs the
 * concurrency epilogue/cleanup.
 * Confidence: low */
void FUN_004070a0(uint64_t param_1, uint64_t param_2)
{
    FUN_000839d8(param_1, param_2, 1);
    FUN_0040bd24();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004070c0 @ 0x004070c0   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004070c0(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004070c0(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004070cc @ 0x004070cc   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004070cc(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004070cc(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004070d8 @ 0x004070d8   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004070d8(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004070d8(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004070e4 @ 0x004070e4   (est. sk_conc_buf_end_accessor)
 * Ghidra: void FUN_004070e4(void)
 * Computes (and discards) the end of a Swift heap buffer via the
 * buffer-end projection helper. A trivial accessor thunk.
 * Confidence: low */
void FUN_004070e4(void)
{
    FUN_000a649c(0);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407100 @ 0x00407100   (est. sk_conc_buf_end_accessor)
 * Ghidra: void FUN_00407100(void)
 * Same buffer-end projection accessor as FUN_004070e4 (discards result).
 * Confidence: low */
void FUN_00407100(void)
{
    FUN_000a649c(0);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0040711c @ 0x0040711c   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_0040711c(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_0040711c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407128 @ 0x00407128   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407128(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407128(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407134 @ 0x00407134   (est. sk_conc_fatal_error_pair)
 * Ghidra: undefined1 [16] FUN_00407134(void)
 * Builds the {lo, hi} pair {&"Fatal error", 0xb} — the Swift runtime's
 * generic fatal-error value (message pointer + message length 0xb).
 * Confidence: medium (string ref) */
sk_u128_t FUN_00407134(void)
{
    return (sk_u128_t){ .lo = (uint64_t)s_fatal_error, .hi = 0xb };
}

/*--------------------------------------------------------------------*/
/* FUN_00407158 @ 0x00407158   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407158(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407158(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407164 @ 0x00407164   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407164(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407164(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407170 @ 0x00407170   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407170(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407170(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407180 @ 0x00407180   (est. sk_conc_record_collect)
 * Ghidra: void FUN_00407180(void)
 * Loads six context words from the receiver (offsets 0x48/0x50/0x58/
 * 0x80/0xa0/0xb0) onto the stack in preparation for the concurrency
 * epilogue FUN_0040bd24. A context-capture thunk.
 * Confidence: low */
void FUN_00407180(void *self)
{
    uint64_t w_b0 = *(uint64_t *)((char *)self + 0xb0);
    uint64_t w_a0 = *(uint64_t *)((char *)self + 0xa0);
    uint64_t w_80 = *(uint64_t *)((char *)self + 0x80);
    uint64_t w_50 = *(uint64_t *)((char *)self + 0x50);
    uint64_t w_58 = *(uint64_t *)((char *)self + 0x58);
    uint64_t w_48 = *(uint64_t *)((char *)self + 0x48);
    (void)w_b0;
    (void)w_a0;
    (void)w_80;
    (void)w_50;
    (void)w_58;
    (void)w_48;
    FUN_0040bd24();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004071a4 @ 0x004071a4   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004071a4(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004071a4(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004071c0 @ 0x004071c0   (est. sk_conc_field_get_10)
 * Ghidra: undefined8 FUN_004071c0(long param_1)
 * Writes the incoming register value `in_x16` into out-param_1+8, then
 * returns the word at self+0x10. A property getter preserving the
 * secondary register.
 * Confidence: low */
uint64_t FUN_004071c0(uint64_t *param_1, uint64_t x16, void *self)
{
    *(uint64_t *)((char *)param_1 + 8) = x16;
    return *(uint64_t *)((char *)self + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_004071d0 @ 0x004071d0   (est. sk_conc_pair_get_38)
 * Ghidra: undefined1 [16] FUN_004071d0(long param_1)
 * Writes `in_x16` into out-param_1+8 and returns the {self+0x38, 0} pair.
 * Confidence: low */
sk_u128_t FUN_004071d0(uint64_t *param_1, uint64_t x16, void *self)
{
    *(uint64_t *)((char *)param_1 + 8) = x16;
    return (sk_u128_t){ .lo = *(uint64_t *)((char *)self + 0x38), .hi = 0 };
}

/*--------------------------------------------------------------------*/
/* FUN_00407200 @ 0x00407200   (est. sk_conc_copy3_words)
 * Ghidra: void FUN_00407200(undefined8 *param_1)
 * Copies three words (2 full words + 1 byte) from param_1 to the
 * destination pointer carried in x9.
 * Confidence: low */
void FUN_00407200(uint64_t *param_1, uint64_t *dst)
{
    uint64_t uVar1 = param_1[0];
    dst[1] = param_1[1];
    dst[0] = uVar1;
    *(uint8_t *)(dst + 2) = *(uint8_t *)(param_1 + 2);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407214 @ 0x00407214   (est. sk_conc_link_record)
 * Ghidra: void FUN_00407214(undefined8 param_1, long param_2)
 * Writes param_1/param_2 and the x20-captured value into the receiver
 * record (offsets 0x10/0x18/0x20), and copies the word at param_2+0x18
 * into self+0x28. A record-linking initializer.
 * Confidence: low */
void FUN_00407214(uint64_t param_1, void *param_2, uint64_t x20, void *self)
{
    *(void **)((char *)self + 0x18) = param_2;
    *(uint64_t *)((char *)self + 0x20) = x20;
    *(uint64_t *)((char *)self + 0x10) = param_1;
    *(uint64_t *)((char *)self + 0x28) = *(uint64_t *)((char *)param_2 + 0x18);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407228 @ 0x00407228   (est. sk_conc_field_get_158)
 * Ghidra: undefined8 FUN_00407228(void)
 * Returns the word at receiver offset +0x158.
 * Confidence: low */
uint64_t FUN_00407228(void *self)
{
    return *(uint64_t *)((char *)self + 0x158);
}

/*--------------------------------------------------------------------*/
/* FUN_0040723c @ 0x0040723c   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_0040723c(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_0040723c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407248 @ 0x00407248   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407248(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407248(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407254 @ 0x00407254   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407254(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407254(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407260 @ 0x00407260   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407260(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407260(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407280 @ 0x00407280   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407280(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407280(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004072a0 @ 0x004072a0   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004072a0(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004072a0(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004072c0 @ 0x004072c0   (est. sk_conc_const_ff)
 * Ghidra: undefined8 FUN_004072c0(void)
 * Returns the constant 0xff.
 * Confidence: low */
uint64_t FUN_004072c0(void)
{
    return 0xff;
}

/*--------------------------------------------------------------------*/
/* FUN_004072cc @ 0x004072cc   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004072cc(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004072cc(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004072e8 @ 0x004072e8   (est. sk_conc_runtime_gate_record)
 * Ghidra: void FUN_004072e8(void)
 * Invokes the runtime gate with marker 0 and the two context words from
 * the receiver (offsets 0x28 and 0x18).
 * Confidence: low */
void FUN_004072e8(void *self)
{
    FUN_00377824(0, *(uint64_t *)((char *)self + 0x28),
                 *(uint64_t *)((char *)self + 0x18));
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407300 @ 0x00407300   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407300(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407300(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407318 @ 0x00407318   (est. sk_conc_finalize)
 * Ghidra: void FUN_00407318(void)
 * Runs the concurrency finalizer.
 * Confidence: low */
void FUN_00407318(void)
{
    FUN_0040d098();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407324 @ 0x00407324   (est. sk_conc_global_singleton)
 * Ghidra: undefined * FUN_00407324(void)
 * Returns a pointer to the static singleton object DAT_004edcec.
 * Confidence: low */
void *FUN_00407324(void)
{
    return &DAT_004edcec;
}

/*--------------------------------------------------------------------*/
/* FUN_0040733c @ 0x0040733c   (est. sk_conc_pair_get_68_90)
 * Ghidra: undefined1 [16] FUN_0040733c(long param_1)
 * Stores the closure/witness pointer LAB_003df658 into out-param_1+8 and
 * returns the {self+0x68, self+0x90} pair.
 * Confidence: low */
sk_u128_t FUN_0040733c(void **param_1, void *self)
{
    *((void **)((char *)param_1 + 8)) = (void *)LAB_003df658;
    return (sk_u128_t){ .lo = *(uint64_t *)((char *)self + 0x68),
                        .hi = *(uint64_t *)((char *)self + 0x90) };
}

/*--------------------------------------------------------------------*/
/* FUN_00407374 @ 0x00407374   (est. sk_conc_cleanup)
 * Ghidra: void FUN_00407374(void)
 * Runs the runtime cleanup helper.
 * Confidence: low */
void FUN_00407374(void)
{
    FUN_003d4658();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0040738c @ 0x0040738c   (est. sk_conc_field_get_10)
 * Ghidra: undefined8 FUN_0040738c(void)
 * Returns the word at receiver offset +0x10.
 * Confidence: low */
uint64_t FUN_0040738c(void *self)
{
    return *(uint64_t *)((char *)self + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_00407398 @ 0x00407398   (est. sk_conc_field_get_70)
 * Ghidra: undefined8 FUN_00407398(long param_1)
 * Stores the closure/witness pointer LAB_003d55b4 into out-param_1+8 and
 * returns the word at self+0x70.
 * Confidence: low */
uint64_t FUN_00407398(void **param_1, void *self)
{
    *((void **)((char *)param_1 + 8)) = (void *)LAB_003d55b4;
    return *(uint64_t *)((char *)self + 0x70);
}

/*--------------------------------------------------------------------*/
/* FUN_004073cc @ 0x004073cc   (est. sk_conc_field_get_40)
 * Ghidra: undefined8 FUN_004073cc(long param_1)
 * Stores the closure/witness pointer LAB_003d88e8 into out-param_1+8 and
 * returns the word at self+0x40.
 * Confidence: low */
uint64_t FUN_004073cc(void **param_1, void *self)
{
    *((void **)((char *)param_1 + 8)) = (void *)LAB_003d88e8;
    return *(uint64_t *)((char *)self + 0x40);
}

/*--------------------------------------------------------------------*/
/* FUN_00407400 @ 0x00407400   (est. sk_conc_pair_get_78_a0)
 * Ghidra: undefined1 [16] FUN_00407400(long param_1)
 * Stores the closure/witness pointer LAB_003deec8 into out-param_1+8 and
 * returns the {self+0x78, self+0xa0} pair.
 * Confidence: low */
sk_u128_t FUN_00407400(void **param_1, void *self)
{
    *((void **)((char *)param_1 + 8)) = (void *)LAB_003deec8;
    return (sk_u128_t){ .lo = *(uint64_t *)((char *)self + 0x78),
                        .hi = *(uint64_t *)((char *)self + 0xa0) };
}

/*--------------------------------------------------------------------*/
/* FUN_00407434 @ 0x00407434   (est. sk_conc_field_nil)
 * Ghidra: void FUN_00407434(long param_1)
 * Clears the word at out-param_1+8 to 0 (stores nil into a field slot).
 * Confidence: low */
void FUN_00407434(uint64_t *param_1)
{
    *(uint64_t *)((char *)param_1 + 8) = 0;
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407444 @ 0x00407444   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407444(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407444(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407450 @ 0x00407450   (est. sk_conc_pair_shift)
 * Ghidra: undefined1 [16] FUN_00407450(void)
 * Builds the {lo=0, hi=in_x3} pair: the x3 register value is shifted into
 * the high word of a 128-bit result (Ghidra renders the <<0x40 shift).
 * Confidence: low */
sk_u128_t FUN_00407450(uint64_t x3)
{
    return (sk_u128_t){ .lo = 0, .hi = x3 };
}

/*--------------------------------------------------------------------*/
/* FUN_00407460 @ 0x00407460   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407460(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407460(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407478 @ 0x00407478   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407478(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407478(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407484 @ 0x00407484   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407484(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407484(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0040749c @ 0x0040749c   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_0040749c(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_0040749c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004074b4 @ 0x004074b4   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004074b4(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004074b4(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004074c4 @ 0x004074c4   (est. sk_conc_field_get_50)
 * Ghidra: undefined8 FUN_004074c4(long param_1)
 * Writes `in_x16` into out-param_1+8 and returns the word at self+0x50.
 * Confidence: low */
uint64_t FUN_004074c4(uint64_t *param_1, uint64_t x16, void *self)
{
    *(uint64_t *)((char *)param_1 + 8) = x16;
    return *(uint64_t *)((char *)self + 0x50);
}

/*--------------------------------------------------------------------*/
/* FUN_004074d4 @ 0x004074d4   (est. sk_conc_arena_cleanup)
 * Ghidra: void FUN_004074d4(void)
 * Runs the dict/runtime arena cleanup helper (result discarded).
 * Confidence: low */
void FUN_004074d4(void)
{
    FUN_0036993c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004074e8 @ 0x004074e8   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004074e8(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004074e8(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407504 @ 0x00407504   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407504(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407504(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407520 @ 0x00407520   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407520(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407520(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0040752c @ 0x0040752c   (est. sk_conc_record_set)
 * Ghidra: void FUN_0040752c(undefined8 param_1..param_4)
 * Writes four word arguments plus the x20-captured value into the receiver
 * record at offsets 0x10/0x18/0x20/0x28/0x30. A record initializer.
 * Confidence: low */
void FUN_0040752c(uint64_t param_1, uint64_t param_2, uint64_t param_3,
                  uint64_t param_4, uint64_t x20, void *self)
{
    *(uint64_t *)((char *)self + 0x28) = param_4;
    *(uint64_t *)((char *)self + 0x30) = x20;
    *(uint64_t *)((char *)self + 0x18) = param_2;
    *(uint64_t *)((char *)self + 0x20) = param_3;
    *(uint64_t *)((char *)self + 0x10) = param_1;
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0040753c @ 0x0040753c   (est. sk_conc_deinit)
 * Ghidra: void FUN_0040753c(void)
 * Runs the concurrency deinit helper.
 * Confidence: low */
void FUN_0040753c(void)
{
    FUN_003f637c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0040754c @ 0x0040754c   (est. sk_conc_deinit)
 * Ghidra: void FUN_0040754c(void)
 * Runs the concurrency deinit helper (same as FUN_0040753c).
 * Confidence: low */
void FUN_0040754c(void)
{
    FUN_003f637c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0040755c @ 0x0040755c   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_0040755c(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_0040755c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407568 @ 0x00407568   (est. sk_conc_pair_global_closure)
 * Ghidra: undefined1 [16] FUN_00407568(void)
 * Returns the {lo=&DAT_006c0b78, hi=(func)FUN_003fc90c} pair — a static
 * global object paired with its closure/witness function.
 * Confidence: low */
sk_u128_t FUN_00407568(void)
{
    return (sk_u128_t){ .lo = (uint64_t)&DAT_006c0b78,
                        .hi = (uint64_t)(void *)FUN_003fc90c };
}

/*--------------------------------------------------------------------*/
/* FUN_00407588 @ 0x00407588   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407588(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407588(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407594 @ 0x00407594   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407594(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407594(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004075a4 @ 0x004075a4   (est. sk_conc_accessor_epilogue)
 * Ghidra: void FUN_004075a4(undefined8 param_1, undefined8 param_2)
 * Dispatches via vtable +0x38 with (param_1, param_2, 1), then runs the
 * concurrency epilogue/cleanup. Same shape as FUN_004070a0.
 * Confidence: low */
void FUN_004075a4(uint64_t param_1, uint64_t param_2)
{
    FUN_000839d8(param_1, param_2, 1);
    FUN_0040bd24();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004075c4 @ 0x004075c4   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004075c4(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004075c4(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004075d0 @ 0x004075d0   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004075d0(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004075d0(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004075ec @ 0x004075ec   (est. sk_conc_global_singleton)
 * Ghidra: undefined * FUN_004075ec(void)
 * Returns a pointer to the static singleton object DAT_005a14dc.
 * Confidence: low */
void *FUN_004075ec(void)
{
    return &DAT_005a14dc;
}

/*--------------------------------------------------------------------*/
/* FUN_00407604 @ 0x00407604   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407604(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407604(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407610 @ 0x00407610   (est. sk_conc_field_get_10)
 * Ghidra: undefined8 FUN_00407610(void)
 * Returns the word at receiver offset +0x10.
 * Confidence: low */
uint64_t FUN_00407610(void *self)
{
    return *(uint64_t *)((char *)self + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_0040761c @ 0x0040761c   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_0040761c(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_0040761c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407628 @ 0x00407628   (est. sk_conc_set_flag_byte)
 * Ghidra: void FUN_00407628(long param_1)
 * Writes the byte 1 into the buffer pointed to by self+0x20 at offset
 * param_1, then runs the runtime cleanup/release helper. Sets a flag byte
 * in a heap buffer.
 * Confidence: low */
void FUN_00407628(long param_1, void *self)
{
    *(uint8_t *)(*(long *)((char *)self + 0x20) + param_1) = 1;
    FUN_0036986c();
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407638 @ 0x00407638   (est. sk_conc_flag_copy_gate)
 * Ghidra: void FUN_00407638(undefined1 *param_1, undefined1 *param_2,
 *                           long param_3)
 * Copies one byte from param_2 to param_1, then invokes the runtime gate
 * with marker 0 and the two words from param_3 (offsets 0x18 and 0x10).
 * Confidence: low */
void FUN_00407638(uint8_t *param_1, uint8_t *param_2, void *param_3)
{
    *param_1 = *param_2;
    FUN_00377824(0, *(uint64_t *)((char *)param_3 + 0x18),
                 *(uint64_t *)((char *)param_3 + 0x10));
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_0040764c @ 0x0040764c   (est. sk_conc_dispatch_ret_slot)
 * Ghidra: undefined8 FUN_0040764c(void)
 * Performs a vtable dispatch (no arguments captured) and returns the
 * value that entered in the stack slot at +0x20 (in_stack_00000020).
 * Confidence: low */
uint64_t FUN_0040764c(uint64_t in_stack_20)
{
    FUN_000839d8(0);
    return in_stack_20;
}

/*--------------------------------------------------------------------*/
/* FUN_00407670 @ 0x00407670   (est. sk_conc_field_get_10)
 * Ghidra: undefined8 FUN_00407670(void)
 * Returns the word at receiver offset +0x10.
 * Confidence: low */
uint64_t FUN_00407670(void *self)
{
    return *(uint64_t *)((char *)self + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_0040767c @ 0x0040767c   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_0040767c(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_0040767c(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004076a8 @ 0x004076a8   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004076a8(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004076a8(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004076c4 @ 0x004076c4   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004076c4(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004076c4(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004076d8 @ 0x004076d8   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004076d8(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004076d8(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407700 @ 0x00407700   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407700(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407700(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407710 @ 0x00407710   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407710(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407710(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407720 @ 0x00407720   (est. sk_conc_field_get_38)
 * Ghidra: undefined8 FUN_00407720(void)
 * Returns the word at receiver offset +0x38.
 * Confidence: low */
uint64_t FUN_00407720(void *self)
{
    return *(uint64_t *)((char *)self + 0x38);
}

/*--------------------------------------------------------------------*/
/* FUN_00407740 @ 0x00407740   (est. sk_conc_field_get_50)
 * Ghidra: undefined8 FUN_00407740(void)
 * Returns the word at receiver offset +0x50.
 * Confidence: low */
uint64_t FUN_00407740(void *self)
{
    return *(uint64_t *)((char *)self + 0x50);
}

/*--------------------------------------------------------------------*/
/* FUN_0040774c @ 0x0040774c   (est. sk_conc_pair_copy_retain)
 * Ghidra: void FUN_0040774c(ulong param_1)
 * Clears the low 3 bits of param_1, copies its two words into the
 * destination pointer carried in x21, then retains the (second-word)
 * reference via FUN_0036b270. A copy-with-retain of a tagged pair.
 * Confidence: low */
void FUN_0040774c(uint64_t param_1, uint64_t *dst)
{
    uint64_t *src = (uint64_t *)(param_1 & 0xfffffffffffffff8ull);
    uint64_t uVar1 = src[1];
    uint64_t uVar3 = src[0];
    dst[1] = src[1];
    dst[0] = uVar3;
    FUN_0036b270(uVar1);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407764 @ 0x00407764   (est. sk_conc_addr_sum)
 * Ghidra: long FUN_00407764(void)
 * Returns the sum of the two register-captured values x26 + x23 (pointer
 * arithmetic in the caller's frame).
 * Confidence: low */
long FUN_00407764(long x26, long x23)
{
    return x26 + x23;
}

/*--------------------------------------------------------------------*/
/* FUN_00407774 @ 0x00407774   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407774(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407774(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407784 @ 0x00407784   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407784(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407784(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407790 @ 0x00407790   (est. sk_conc_record_store)
 * Ghidra: void FUN_00407790(undefined1 param_1 [16], undefined8 param_2,
 *                           undefined8 param_3)
 * Stores param_2/param_3, the two words of the 16-byte param_1, and the
 * byte in w8 into the 5-word array pointed to by x19.
 * Confidence: low */
void FUN_00407790(sk_u128_t param_1, uint64_t param_2, uint64_t param_3,
                  uint8_t w8, uint64_t *dst)
{
    dst[0] = param_2;
    dst[1] = param_3;
    dst[3] = param_1.hi;
    dst[2] = param_1.lo;
    *(uint8_t *)(dst + 4) = w8;
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004077a0 @ 0x004077a0   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004077a0(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004077a0(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004077b0 @ 0x004077b0   (est. sk_conc_dispatch_30)
 * Ghidra: void FUN_004077b0(void)
 * Performs an indirect vtable dispatch at +0x30 (no captured arguments).
 * Confidence: low */
void FUN_004077b0(void)
{
    FUN_000839f8(0, 0, 0);
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004077cc @ 0x004077cc   (est. sk_conc_field_get_10)
 * Ghidra: undefined8 FUN_004077cc(void)
 * Returns the word at receiver offset +0x10.
 * Confidence: low */
uint64_t FUN_004077cc(void *self)
{
    return *(uint64_t *)((char *)self + 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_004077dc @ 0x004077dc   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004077dc(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004077dc(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_004077ec @ 0x004077ec   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_004077ec(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_004077ec(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407800 @ 0x00407800   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407800(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407800(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407814 @ 0x00407814   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407814(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407814(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407824 @ 0x00407824   (est. sk_conc_noop_thunk)
 * Ghidra: void FUN_00407824(void)
 * A `ret`-only stub.
 * Confidence: low */
void FUN_00407824(void)
{
    return;
}

/*--------------------------------------------------------------------*/
/* FUN_00407830 @ 0x00407830   (est. sk_conc_field_get_78)
 * Ghidra: undefined8 FUN_00407830(long param_1)
 * Writes `in_x16` into out-param_1+8 and returns the word at self+0x78.
 * Confidence: low */
uint64_t FUN_00407830(uint64_t *param_1, uint64_t x16, void *self)
{
    *(uint64_t *)((char *)param_1 + 8) = x16;
    return *(uint64_t *)((char *)self + 0x78);
}
