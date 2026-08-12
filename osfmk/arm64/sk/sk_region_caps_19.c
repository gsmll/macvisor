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
