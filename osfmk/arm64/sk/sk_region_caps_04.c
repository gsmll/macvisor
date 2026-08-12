/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 04: 0x8ec20-0x100000 caps region (0x8ec20 - 0x92698). */

#include <stdint.h>
#include <stddef.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Shared cL4 helpers OUTSIDE this slice (declared extern with a one-line
 * note; bodies reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */
/* FUN_0036b118 — release/restore a lock around the DAT_00657778 buffer
 * object (mirror of FUN_0036b270). Called both with and without the
 * buffer pointer. */
extern void cl4_buf_release(unsigned long buf);
/* FUN_0036b6ac — release/lock teardown for the same buffer context. */
extern void cl4_buf_release_fast(void);
/* FUN_0036b270 — acquire/lock the DAT_00657778 buffer object. */
extern unsigned long cl4_buf_acquire(unsigned long buf);
/* FUN_0036b6ac / FUN_003a261c — predicate/condition check on the buffer
 * state (returns nonzero to steer an obfuscation branch). */
extern int cl4_buf_cond(unsigned long buf);
/* FUN_00324bf0 — helper consulted while resolving the buffer's backing
 * object (returns a word used as a lookup key). */
extern unsigned long cl4_buf_key(int a);
/* FUN_00362acc — resolve the buffer backing object given (buffer, key). */
extern long cl4_buf_resolve(unsigned long buf, unsigned long key);
/* FUN_0006f6b4 — fallback buffer-backing-object resolver. */
extern long cl4_buf_resolve_fallback(void);
/* FUN_0036a20c — tear down a stack-local buffer frame. */
extern void cl4_buf_frame_teardown(unsigned long *frame);
/* FUN_00002828 — initialise a stack buffer frame from *ptr. */
extern void cl4_buf_frame_init(long *ptr, unsigned long *frame);
/* FUN_0008110c — fill a stack buffer frame from the given word. */
extern void cl4_buf_frame_fill(unsigned long *word, unsigned long *frame);
/* FUN_001032b8 — fetch current thread / operation result word. */
extern unsigned long cl4_result_fetch(void);
/* FUN_0010319c — advance/derive a result word from the given operand. */
extern unsigned long cl4_result_advance(unsigned long operand);
/* FUN_0011d7e8 — stack canary check failure (noreturn). */
extern void cl4_stack_canary_fail(void) __attribute__((noreturn));
/* FUN_001ae20c — register a deferred cleanup callback (fn, frame, buf). */
extern void cl4_defer_cleanup(void *fn, unsigned long *frame, unsigned long buf);
/* FUN_0036b118 — used above. */

/* Global: the obfuscation/deobfuscation working buffer. DAT_00657778
 * (16-byte object header) with its data payload at DAT_00657798. */
extern unsigned char cl4_obf_buffer[];   /* DAT_00657778 */
/* Global: 16-byte cursor/PRNG state pair. _DAT_004c08a0 / _DAT_004c08a8. */
extern unsigned long cl4_obf_cursor[2];

/* ------------------------------------------------------------------ *
 * In-slice function prototypes.
 * ------------------------------------------------------------------ */
static unsigned long cl4_prng_next(void);

/* FUN_0008ec20 @ 0x0008ec20   (est. cl4_prng_next)
 * Ghidra: undefined8 FUN_0008ec20(void)
 * Advances the cL4 obfuscation pseudo-random generator state (a two-word
 * xorshift-style LFSR living at the context pointer +0x10/+0x18) and
 * returns a derived 64-bit word. The low byte of the result is used by
 * callers to fill the deobfuscation buffer. Renders opaque-predicate
 * branches (which read a constant field at ctx+0x20) as the original
 * checks; the branch is never taken in normal operation.
 * Confidence: medium
 * Notes: decompiler shows opaque predicates via *(*(ctx+0x20)+0x10)==0;
 *   SoftwareBreakpoint(1,0x8ed24) marks a noreturn trap on canary failure. */
static unsigned long cl4_prng_next(void)
{
    /* PRNG state words (global context held across calls). */
    unsigned long s0, s1, mixed, local;
    unsigned long canary = 0xd37adfb44bfffed6;   /* stack canary */

    cl4_buf_frame_init(ctx_global + 0x20, frame_a);
    if (*(long *)(*(long *)(ctx_global + 0x20) + 0x10) == 0) {
        s0 = ctx_prng_state[0];
        local = ctx_prng_state[1] + s0;
        mixed = ctx_prng_state[1] ^ s0;
        ctx_prng_state[0] = ror(s0, 9) ^ (mixed << 14) ^ mixed;
        ctx_prng_state[1] = ror(mixed, 28);
        cl4_branch_guard();
        cl4_buf_frame_fill(&local, frame_b);
        cl4_buf_frame_teardown(frame_b);
    }
    cl4_branch_guard();
    if (*(long *)(*(long *)(ctx_global + 0x20) + 0x10) == 0) {
        cl4_buf_frame_teardown(frame_b);
        cl4_trap(1, 0x8ed24);                     /* noreturn */
    }
    unsigned long result = cl4_result_fetch();
    if (((unsigned)result & 0xff00) == 0x100) {
        result = cl4_result_advance(*(long *)(*(long *)(ctx_global + 0x20) + 0x10) - 1);
    }
    cl4_buf_frame_teardown(frame_b);
    if (canary != 0xd37adfb44bfffed6) cl4_stack_canary_fail();
    return result;
}
