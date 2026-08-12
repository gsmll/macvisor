/* sk_internal.h — shared base types for the cL4 Secure Kernel (GL1) recreation.
 * Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses in the cl4_kernel.raw program.
 * Names use seL4/cL4 vocabulary; all are estimates unless string/header matched.
 * This header holds only scalar/word primitives and small structs shared across
 * the vspace/MMU layer; per-function detail lives in the region .c files. */

#ifndef _SK_INTERNAL_H_
#define _SK_INTERNAL_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* cL4/seL4 word — the kernel's fundamental word size (arm64e: 64-bit). */
typedef uint64_t word_t;
typedef uint64_t cptr_t;   /* capability pointer */
typedef uint64_t vptr_t;   /* virtual address */
typedef uint64_t pptr_t;   /* physical address */
typedef uint64_t cap_t;    /* capability word */
typedef uint64_t tcb_t;    /* thread-control-block word */
typedef uint32_t seL4_Word;

/* Result of a cL4 operation: error code in lo, status/details in hi.
 * The binary packs the classic seL4 exception/error into the return pair. */
typedef struct cl4_result {
    uint64_t lo;
    uint64_t hi;
} cl4_result_t;

/* Empty/undefined capability marker. */
#define CL4_CAP_NULL 0ull

/* Canonical memory attributes (seL4 ARMv8 MTE/SH bits), 4-bit field. */
#define CL4_MEMATTR_DEVICE_nGnRnE  0x0u
#define CL4_MEMATTR_NORMAL         0x4u

#endif /* _SK_INTERNAL_H_ */
