#ifndef _ARM64_SPTM_INTERNAL_H_
#define _ARM64_SPTM_INTERNAL_H_
/*
 * Recreated from sptm.t8142.release.im4p (SPTM, arm64e) — the Secure Page
 * Table Monitor (GL2). Shared types. Ground truth: Ghidra FUN_ names +
 * addresses; public API names from docs/sptm/headers/sptm_common.h.
 */
#include <stdint.h>

/* GENTER (0x00201420) / GEXIT (0x00201400) — Apple-proprietary guarded-level
 * transitions. Rendered as opaque calls; the selector in x16 selects the
 * dispatch endpoint (SPTM_LOAD_DISPATCH_ID). */
#define GENTER() __asm__ volatile(".long 0x00201420" ::: "memory")
#define GEXIT()  __asm__ volatile(".long 0x00201400" ::: "memory")

typedef uint64_t sptm_paddr_t;
typedef uint64_t sptm_vaddr_t;
typedef uint32_t sptm_domain_t;
typedef uint32_t sptm_dispatch_table_id_t;
typedef uint32_t sptm_dispatch_endpoint_id_t;

/* sptm_call_regs_t — the argument/return register block passed across the
 * guarded-level call (from sptm_common.h). */
typedef struct sptm_call_regs {
    uint64_t x0, x1, x2, x3, x4, x5, x6, x7;
    uint64_t x8;
} sptm_call_regs_t;

#endif
