/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0x39fcc4-0x3a68a4) is a cL4 kernel-object dispatch layer: the
 * bodies are selector-based dispatchers (the first word of the object selects
 * a handler), plumbing between the capability/object stores at 0x67b0a8 /
 * 0x67c068 / 0x67c0d0 / 0x67c1c8 / 0x67c230, and small object/service helpers.
 * All names are estimates unless string-matched. */
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1).
 * Model it as a struct so callers can carry both halves. */
typedef struct { unsigned long lo, hi; } cL4_w16_t;

/* SoftwareBreakpoint(1, addr) fail-closed trap (brk #1). */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* ------------------------------------------------------------------ *
 * Extern declarations for callees outside this region and forward
 * declarations for in-region callees. Populated as functions are
 * transcribed.
 * ------------------------------------------------------------------ */
