/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses in
 * the cl4_kernel.raw program. All names are estimates unless string/header
 * matched.
 * Slice R03: 0x3a6c28-0x3ba390.
 * This slice is the tagged-value stream serializer/deserializer: a
 * Tightbeam-style compact-data subsystem that turns a byte stream (read
 * through a stream-context at +0x38 data / +0x40 end / +0x48 pos) into a
 * tree of tagged value nodes, and back. Every node is a small block: [0] data
 * pointer, [1] count/value word, [2] = 16-bit tag at +0x10, [3] = a one-byte
 * sub-type/flags at +0x12. A per-context value stack (array at +0x58, count at
 * +0x60) is used to build/consume nested values. Register-argument functions
 * (x20 "self", x21 "flag") model those args as explicit leading parameters;
 * Ghidra's unaff_x20/x21 are noted in comments. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* A tagged value node: [0]=data/child pointer, [1]=count/value word,
 * [2]=16-bit tag at +0x10, byte at +0x12 = sub-type/flags. */
typedef uint64_t sk_node;

/* Stream context (param_1 of the reader/writer entry points):
 *   +0x38 data base, +0x40 end, +0x48 position,
 *   +0x58 value-stack array, +0x60 value-stack count. */