/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 07: 0x9e2b4-0xa3864 caps region. */

#include <stdint.h>
#include <stddef.h>

#include "sk_internal.h"

/* Out-of-slice kernel/microkernel dependencies (one-line notes). */
extern void FUN_001afa84(word_t arg, word_t code, word_t extra); /* out of slice: noreturn fault/panic path */
extern void FUN_0036b270(void);                                  /* out of slice: context mgmt */
extern void FUN_0036b118(void *p);                               /* out of slice: release/refdrop */
extern void FUN_0036b6f4(void);                                  /* out of slice: error path */
extern void FUN_000fdb98(void *p);                               /* out of slice: object dispose */
extern void FUN_002a4ab4(word_t v);                              /* out of slice: init/mask */
extern void FUN_003a25d4(word_t v);                              /* out of slice: set mask */
extern word_t FUN_00027724(word_t v);                            /* out of slice: returns fn ptr */
extern void thunk_FUN_002acbb8(void);                            /* out of slice: thunk */
extern void FUN_0006a4c0(void *p, word_t v);                     /* out of slice: bind */
extern void FUN_0009ea90(word_t a, word_t b);                    /* out of slice (sibling): dispatch tail */

/* FUN_0009e2b4 @ 0x0009e2b4   (est. sk_caps_error_0xb)
 * Ghidra: void FUN_0009e2b4(undefined8 param_1)
 * Enters the shared fault/exception path with fault code 0xb and extra 2.
 * No return: the kernel terminates or panics the calling thread.
 * Confidence: low
 * Notes: noreturn; delegates directly to FUN_001afa84. */
void FUN_0009e2b4(word_t param_1)
{
    /* The opcode 0xb + argument 2 identify a capability/object error class;
     * this stub simply forwards to the shared fatal-error sink. */
    FUN_001afa84(param_1, 0xb, 2);
    /* unreachable: FUN_001afa84 is noreturn */
}

/* FUN_0009e2e8 @ 0x0009e2e8   (est. sk_caps_get_word)
 * Ghidra: void FUN_0009e2e8(undefined8 *param_1)
 * Copies a single word from the thread/context record held in callee-saved x20
 * (offset 0x20) out to the caller's slot. A thin accessor.
 * Confidence: low
 * Notes: reads *(x20 + 0x20); x20 is a preserved register naming the context. */
void FUN_0009e2e8(word_t *out)
{
    /* out = context->field_20; the context base lives in callee-saved x20. */
    *out = 0; /* placeholder — context base in x20 unavailable to C */
}
