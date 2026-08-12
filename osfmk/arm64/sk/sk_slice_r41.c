/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice: 0x004b10c0-0x004b2748 (SKR41) — a dense run of tiny noreturn
 * trap/abort stubs. 0x4b10c0-0x4b1a50 are Tightbeam-codec and Swift-runtime
 * fatal-error trap thunks: each prints a TB_FATAL / fatal message via a helper
 * then executes a `brk` (SoftwareBreakpoint) whose handler resumes the monitor.
 * 0x4b1a74-0x4b270c are VAS (virtual-address-space) abort stubs that panic via
 * FUN_004afae4 ("VAS abort in function '%s' at line %d") for assertion and
 * invariant violations across the VAS / heap / siptable layers. Interspersed:
 * 0x4b1c84 prints an "unable to map read only" message then returns; 0x4b1d40
 * dumps a bitmap then aborts; 0x4b20e8 is a security-assertion failure; and
 * 0x4b23d8 is a real page-range release routine (bitmap clear + refcount dec +
 * transaction commit) that is the only non-trivial body in the slice. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as Ghidra pseudo-ops).
 * ------------------------------------------------------------------ */

/* SoftwareBreakpoint(imm, cont): `brk #imm`. The Ghidra pseudo-op's second
 * operand is the address the trap handler resumes at (a monitor continuation,
 * unreachable from here because the brk is fatal). */
#define SK_BRK(imm)                                                          \
    do { __asm__ volatile("brk #" #imm); __builtin_unreachable(); } while (0)

/* CallSupervisor(n): `svc #n` supervisor call. */
#define CALL_SUPERVISOR(n)                                                   \
    do { __asm__ volatile("svc #" #n); } while (0)

/* 16-byte word pair returned in x0:x1 (aarch64e ABI). lo lands in x0. */
typedef struct {
    uint64_t lo;   /* x0 */
    uint64_t hi;   /* x1 */
} cl4_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-range helpers called from this slice (extern with one-line note;
 * bodies reconstructed by the range workers that own them). Ground truth
 * FUN_ address in comment. */
extern void FUN_00019800(uint64_t);  /* TB_FATAL: size-0-buffer fatal printer (dat@005ac851) */
extern void FUN_00019810(uint64_t);  /* TB_FATAL: "TB: size 0 buffer duri..." printer */
extern void FUN_00019820(uint64_t);  /* TB_FATAL printer (dat@005ac6d1) */
extern void FUN_00019830(uint64_t);  /* TB_FATAL: overflow during de... printer */
extern void FUN_00019840(uint64_t);  /* TB_FATAL: overflow during en... printer */
extern void FUN_00015e2c(uint64_t);  /* TB_FATAL: overflow detected when... printer */
extern void FUN_000179d8(uint64_t);  /* TB_FATAL: overflow detected when... printer (alt) */
extern void FUN_004afae4(uint64_t) __attribute__((noreturn));  /* vas_abort: printf-style VAS panic via FUN_0005b1b0 */
extern void FUN_00032e1c(uint64_t) __attribute__((noreturn));  /* vas_abort wrapper: "VAS abort in function '%s' at line..." */
extern void FUN_00032e30(uint64_t) __attribute__((noreturn));  /* vas_abort wrapper (alt line) */
extern void FUN_00034874(uint64_t) __attribute__((noreturn));  /* vas_abort wrapper (alt line) */
extern void FUN_001150e0(uint64_t) __attribute__((noreturn));  /* security-assertion failure handler ("Security assertion failed: %s, %f") */
extern void FUN_00118b28(uint64_t);  /* printf core (tag 0xb4000769f84206c9) */
extern void FUN_00118c28(uint64_t);  /* putchar via FUN_001187f4 */
extern void FUN_00118c38(uint64_t, uint64_t, uint64_t);  /* printf (tag, fmt, va) -> FUN_001158cc */
extern void FUN_001185ec(uint64_t, uint64_t);  /* printf (fmt, arg1) */
extern void FUN_001187f4(uint64_t, uint64_t);  /* formatted char output (ch, tag) */
extern long  *FUN_0005acac(uint64_t, uint64_t, uint64_t);  /* global-struct accessor (0x6af188) */
extern cl4_pair_t FUN_00034bd8(uint64_t);  /* load 16-byte pair @ arg */
extern void    FUN_00034d5c(uint64_t, uint64_t, uint64_t);  /* commit transaction @ arg */
extern uint64_t *FUN_00035418(uint64_t);  /* region lookup by tag */

/* ================================================================== *
 * Trap / abort stubs (address order)
 * ================================================================== */

/* FUN_004b10c0 @ 0x004b10c0   (est. sk_tb_fatal_trap_004b10c0)
 * Ghidra: void FUN_004b10c0(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b10e4) */
void sk_tb_fatal_trap_004b10c0(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b10e4) */
}

/* FUN_004b10e4 @ 0x004b10e4   (est. sk_tb_fatal_trap_004b10e4)
 * Ghidra: void FUN_004b10e4(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b1108) */
void sk_tb_fatal_trap_004b10e4(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1108) */
}

/* FUN_004b1108 @ 0x004b1108   (est. sk_tb_fatal_trap_004b1108)
 * Ghidra: void FUN_004b1108(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b112c) */
void sk_tb_fatal_trap_004b1108(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b112c) */
}

/* FUN_004b112c @ 0x004b112c   (est. sk_tb_fatal_trap_004b112c)
 * Ghidra: void FUN_004b112c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b1150) */
void sk_tb_fatal_trap_004b112c(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1150) */
}

/* FUN_004b1150 @ 0x004b1150   (est. sk_tb_fatal_trap_004b1150)
 * Ghidra: void FUN_004b1150(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019820, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019820; SoftwareBreakpoint(1,0x4b1174) */
void sk_tb_fatal_trap_004b1150(void)
{
    FUN_00019820(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1174) */
}

/* FUN_004b1174 @ 0x004b1174   (est. sk_tb_fatal_trap_004b1174)
 * Ghidra: void FUN_004b1174(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019840, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019840; SoftwareBreakpoint(1,0x4b1198) */
void sk_tb_fatal_trap_004b1174(void)
{
    FUN_00019840(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1198) */
}

/* FUN_004b1198 @ 0x004b1198   (est. sk_tb_fatal_trap_004b1198)
 * Ghidra: void FUN_004b1198(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b11bc) */
void sk_tb_fatal_trap_004b1198(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b11bc) */
}

/* FUN_004b11bc @ 0x004b11bc   (est. sk_tb_fatal_trap_004b11bc)
 * Ghidra: void FUN_004b11bc(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b11e0) */
void sk_tb_fatal_trap_004b11bc(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b11e0) */
}

/* FUN_004b11e0 @ 0x004b11e0   (est. sk_tb_fatal_trap_004b11e0)
 * Ghidra: void FUN_004b11e0(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b1204) */
void sk_tb_fatal_trap_004b11e0(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1204) */
}

/* FUN_004b1204 @ 0x004b1204   (est. sk_tb_fatal_trap_004b1204)
 * Ghidra: void FUN_004b1204(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b1228) */
void sk_tb_fatal_trap_004b1204(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1228) */
}

/* FUN_004b1228 @ 0x004b1228   (est. sk_tb_fatal_trap_004b1228)
 * Ghidra: void FUN_004b1228(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b124c) */
void sk_tb_fatal_trap_004b1228(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b124c) */
}

/* FUN_004b124c @ 0x004b124c   (est. sk_tb_fatal_trap_004b124c)
 * Ghidra: void FUN_004b124c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019820, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019820; SoftwareBreakpoint(1,0x4b1270) */
void sk_tb_fatal_trap_004b124c(void)
{
    FUN_00019820(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1270) */
}

/* FUN_004b1270 @ 0x004b1270   (est. sk_tb_fatal_trap_004b1270)
 * Ghidra: void FUN_004b1270(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019840, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019840; SoftwareBreakpoint(1,0x4b1294) */
void sk_tb_fatal_trap_004b1270(void)
{
    FUN_00019840(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1294) */
}

/* FUN_004b1294 @ 0x004b1294   (est. sk_tb_fatal_trap_004b1294)
 * Ghidra: void FUN_004b1294(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b12b8) */
void sk_tb_fatal_trap_004b1294(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b12b8) */
}

/* FUN_004b12b8 @ 0x004b12b8   (est. sk_tb_fatal_trap_004b12b8)
 * Ghidra: void FUN_004b12b8(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b12dc) */
void sk_tb_fatal_trap_004b12b8(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b12dc) */
}

/* FUN_004b12dc @ 0x004b12dc   (est. sk_tb_fatal_trap_004b12dc)
 * Ghidra: void FUN_004b12dc(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b1300) */
void sk_tb_fatal_trap_004b12dc(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1300) */
}

/* FUN_004b1300 @ 0x004b1300   (est. sk_tb_fatal_trap_004b1300)
 * Ghidra: void FUN_004b1300(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b1324) */
void sk_tb_fatal_trap_004b1300(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1324) */
}

/* FUN_004b1324 @ 0x004b1324   (est. sk_tb_fatal_trap_004b1324)
 * Ghidra: void FUN_004b1324(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b1348) */
void sk_tb_fatal_trap_004b1324(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1348) */
}

/* FUN_004b1348 @ 0x004b1348   (est. sk_tb_fatal_trap_004b1348)
 * Ghidra: void FUN_004b1348(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019820, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019820; SoftwareBreakpoint(1,0x4b136c) */
void sk_tb_fatal_trap_004b1348(void)
{
    FUN_00019820(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b136c) */
}

/* FUN_004b136c @ 0x004b136c   (est. sk_tb_fatal_trap_004b136c)
 * Ghidra: void FUN_004b136c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019840, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019840; SoftwareBreakpoint(1,0x4b1390) */
void sk_tb_fatal_trap_004b136c(void)
{
    FUN_00019840(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1390) */
}

/* FUN_004b1390 @ 0x004b1390   (est. sk_tb_fatal_trap_004b1390)
 * Ghidra: void FUN_004b1390(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b13b4) */
void sk_tb_fatal_trap_004b1390(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b13b4) */
}

/* FUN_004b13b4 @ 0x004b13b4   (est. sk_tb_fatal_trap_004b13b4)
 * Ghidra: void FUN_004b13b4(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b13d8) */
void sk_tb_fatal_trap_004b13b4(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b13d8) */
}

/* FUN_004b13d8 @ 0x004b13d8   (est. sk_tb_fatal_trap_004b13d8)
 * Ghidra: void FUN_004b13d8(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_000179d8, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_000179d8; SoftwareBreakpoint(1,0x4b13fc) */
void sk_tb_fatal_trap_004b13d8(void)
{
    FUN_000179d8(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b13fc) */
}

/* FUN_004b13fc @ 0x004b13fc   (est. sk_tb_fatal_trap_004b13fc)
 * Ghidra: void FUN_004b13fc(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b1420) */
void sk_tb_fatal_trap_004b13fc(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1420) */
}

/* FUN_004b1420 @ 0x004b1420   (est. sk_tb_fatal_trap_004b1420)
 * Ghidra: void FUN_004b1420(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b1444) */
void sk_tb_fatal_trap_004b1420(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1444) */
}

/* FUN_004b1444 @ 0x004b1444   (est. sk_tb_fatal_trap_004b1444)
 * Ghidra: void FUN_004b1444(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b1468) */
void sk_tb_fatal_trap_004b1444(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1468) */
}

/* FUN_004b1468 @ 0x004b1468   (est. sk_tb_fatal_trap_004b1468)
 * Ghidra: void FUN_004b1468(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b148c) */
void sk_tb_fatal_trap_004b1468(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b148c) */
}

/* FUN_004b148c @ 0x004b148c   (est. sk_tb_fatal_trap_004b148c)
 * Ghidra: void FUN_004b148c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019820, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019820; SoftwareBreakpoint(1,0x4b14b0) */
void sk_tb_fatal_trap_004b148c(void)
{
    FUN_00019820(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b14b0) */
}

/* FUN_004b14b0 @ 0x004b14b0   (est. sk_tb_fatal_trap_004b14b0)
 * Ghidra: void FUN_004b14b0(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019840, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019840; SoftwareBreakpoint(1,0x4b14d4) */
void sk_tb_fatal_trap_004b14b0(void)
{
    FUN_00019840(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b14d4) */
}

/* FUN_004b14d4 @ 0x004b14d4   (est. sk_tb_fatal_trap_004b14d4)
 * Ghidra: void FUN_004b14d4(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b14f8) */
void sk_tb_fatal_trap_004b14d4(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b14f8) */
}

/* FUN_004b14f8 @ 0x004b14f8   (est. sk_tb_fatal_trap_004b14f8)
 * Ghidra: void FUN_004b14f8(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b151c) */
void sk_tb_fatal_trap_004b14f8(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b151c) */
}

/* FUN_004b151c @ 0x004b151c   (est. sk_tb_fatal_trap_004b151c)
 * Ghidra: void FUN_004b151c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b1540) */
void sk_tb_fatal_trap_004b151c(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1540) */
}

/* FUN_004b1540 @ 0x004b1540   (est. sk_tb_fatal_trap_004b1540)
 * Ghidra: void FUN_004b1540(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b1564) */
void sk_tb_fatal_trap_004b1540(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1564) */
}

/* FUN_004b1564 @ 0x004b1564   (est. sk_tb_fatal_trap_004b1564)
 * Ghidra: void FUN_004b1564(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b1588) */
void sk_tb_fatal_trap_004b1564(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1588) */
}

/* FUN_004b1588 @ 0x004b1588   (est. sk_tb_fatal_trap_004b1588)
 * Ghidra: void FUN_004b1588(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019820, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019820; SoftwareBreakpoint(1,0x4b15ac) */
void sk_tb_fatal_trap_004b1588(void)
{
    FUN_00019820(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b15ac) */
}

/* FUN_004b15ac @ 0x004b15ac   (est. sk_tb_fatal_trap_004b15ac)
 * Ghidra: void FUN_004b15ac(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019840, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019840; SoftwareBreakpoint(1,0x4b15d0) */
void sk_tb_fatal_trap_004b15ac(void)
{
    FUN_00019840(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b15d0) */
}

/* FUN_004b15d0 @ 0x004b15d0   (est. sk_tb_fatal_trap_004b15d0)
 * Ghidra: void FUN_004b15d0(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b15f4) */
void sk_tb_fatal_trap_004b15d0(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b15f4) */
}

/* FUN_004b15f4 @ 0x004b15f4   (est. sk_tb_fatal_trap_004b15f4)
 * Ghidra: void FUN_004b15f4(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b1618) */
void sk_tb_fatal_trap_004b15f4(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1618) */
}

/* FUN_004b1618 @ 0x004b1618   (est. sk_tb_fatal_trap_004b1618)
 * Ghidra: void FUN_004b1618(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b163c) */
void sk_tb_fatal_trap_004b1618(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b163c) */
}

/* FUN_004b163c @ 0x004b163c   (est. sk_tb_fatal_trap_004b163c)
 * Ghidra: void FUN_004b163c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b1660) */
void sk_tb_fatal_trap_004b163c(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1660) */
}

/* FUN_004b1660 @ 0x004b1660   (est. sk_tb_fatal_trap_004b1660)
 * Ghidra: void FUN_004b1660(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b1684) */
void sk_tb_fatal_trap_004b1660(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1684) */
}

/* FUN_004b1684 @ 0x004b1684   (est. sk_tb_fatal_trap_004b1684)
 * Ghidra: void FUN_004b1684(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019820, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019820; SoftwareBreakpoint(1,0x4b16a8) */
void sk_tb_fatal_trap_004b1684(void)
{
    FUN_00019820(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b16a8) */
}

/* FUN_004b16a8 @ 0x004b16a8   (est. sk_tb_fatal_trap_004b16a8)
 * Ghidra: void FUN_004b16a8(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019840, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019840; SoftwareBreakpoint(1,0x4b16cc) */
void sk_tb_fatal_trap_004b16a8(void)
{
    FUN_00019840(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b16cc) */
}

/* FUN_004b16cc @ 0x004b16cc   (est. sk_tb_fatal_trap_004b16cc)
 * Ghidra: void FUN_004b16cc(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b16f0) */
void sk_tb_fatal_trap_004b16cc(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b16f0) */
}

/* FUN_004b16f0 @ 0x004b16f0   (est. sk_tb_fatal_trap_004b16f0)
 * Ghidra: void FUN_004b16f0(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b1714) */
void sk_tb_fatal_trap_004b16f0(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1714) */
}

/* FUN_004b1714 @ 0x004b1714   (est. sk_tb_fatal_trap_004b1714)
 * Ghidra: void FUN_004b1714(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b1738) */
void sk_tb_fatal_trap_004b1714(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1738) */
}

/* FUN_004b1738 @ 0x004b1738   (est. sk_tb_fatal_trap_004b1738)
 * Ghidra: void FUN_004b1738(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b175c) */
void sk_tb_fatal_trap_004b1738(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b175c) */
}

/* FUN_004b175c @ 0x004b175c   (est. sk_tb_fatal_trap_004b175c)
 * Ghidra: void FUN_004b175c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b1780) */
void sk_tb_fatal_trap_004b175c(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1780) */
}

/* FUN_004b1780 @ 0x004b1780   (est. sk_tb_fatal_trap_004b1780)
 * Ghidra: void FUN_004b1780(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019820, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019820; SoftwareBreakpoint(1,0x4b17a4) */
void sk_tb_fatal_trap_004b1780(void)
{
    FUN_00019820(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b17a4) */
}

/* FUN_004b17a4 @ 0x004b17a4   (est. sk_tb_fatal_trap_004b17a4)
 * Ghidra: void FUN_004b17a4(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019840, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019840; SoftwareBreakpoint(1,0x4b17c8) */
void sk_tb_fatal_trap_004b17a4(void)
{
    FUN_00019840(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b17c8) */
}

/* FUN_004b17c8 @ 0x004b17c8   (est. sk_tb_fatal_trap_004b17c8)
 * Ghidra: void FUN_004b17c8(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b17ec) */
void sk_tb_fatal_trap_004b17c8(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b17ec) */
}

/* FUN_004b17ec @ 0x004b17ec   (est. sk_tb_fatal_trap_004b17ec)
 * Ghidra: void FUN_004b17ec(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b1810) */
void sk_tb_fatal_trap_004b17ec(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1810) */
}

/* FUN_004b1810 @ 0x004b1810   (est. sk_tb_fatal_trap_004b1810)
 * Ghidra: void FUN_004b1810(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b1834) */
void sk_tb_fatal_trap_004b1810(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1834) */
}

/* FUN_004b1834 @ 0x004b1834   (est. sk_tb_fatal_trap_004b1834)
 * Ghidra: void FUN_004b1834(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b1858) */
void sk_tb_fatal_trap_004b1834(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1858) */
}

/* FUN_004b1858 @ 0x004b1858   (est. sk_tb_fatal_trap_004b1858)
 * Ghidra: void FUN_004b1858(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b187c) */
void sk_tb_fatal_trap_004b1858(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b187c) */
}

/* FUN_004b187c @ 0x004b187c   (est. sk_tb_fatal_trap_004b187c)
 * Ghidra: void FUN_004b187c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019820, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019820; SoftwareBreakpoint(1,0x4b18a0) */
void sk_tb_fatal_trap_004b187c(void)
{
    FUN_00019820(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b18a0) */
}

/* FUN_004b18a0 @ 0x004b18a0   (est. sk_tb_fatal_trap_004b18a0)
 * Ghidra: void FUN_004b18a0(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019840, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019840; SoftwareBreakpoint(1,0x4b18c4) */
void sk_tb_fatal_trap_004b18a0(void)
{
    FUN_00019840(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b18c4) */
}

/* FUN_004b18c4 @ 0x004b18c4   (est. sk_tb_fatal_trap_004b18c4)
 * Ghidra: void FUN_004b18c4(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b18e8) */
void sk_tb_fatal_trap_004b18c4(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b18e8) */
}

/* FUN_004b18e8 @ 0x004b18e8   (est. sk_tb_fatal_trap_004b18e8)
 * Ghidra: void FUN_004b18e8(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b190c) */
void sk_tb_fatal_trap_004b18e8(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b190c) */
}

/* FUN_004b190c @ 0x004b190c   (est. sk_tb_fatal_trap_004b190c)
 * Ghidra: void FUN_004b190c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b1930) */
void sk_tb_fatal_trap_004b190c(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1930) */
}

/* FUN_004b1930 @ 0x004b1930   (est. sk_tb_fatal_trap_004b1930)
 * Ghidra: void FUN_004b1930(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b1954) */
void sk_tb_fatal_trap_004b1930(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1954) */
}

/* FUN_004b1954 @ 0x004b1954   (est. sk_tb_fatal_trap_004b1954)
 * Ghidra: void FUN_004b1954(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b1978) */
void sk_tb_fatal_trap_004b1954(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1978) */
}

/* FUN_004b1978 @ 0x004b1978   (est. sk_tb_fatal_trap_004b1978)
 * Ghidra: void FUN_004b1978(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019820, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019820; SoftwareBreakpoint(1,0x4b199c) */
void sk_tb_fatal_trap_004b1978(void)
{
    FUN_00019820(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b199c) */
}

/* FUN_004b199c @ 0x004b199c   (est. sk_tb_fatal_trap_004b199c)
 * Ghidra: void FUN_004b199c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019840, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019840; SoftwareBreakpoint(1,0x4b19c0) */
void sk_tb_fatal_trap_004b199c(void)
{
    FUN_00019840(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b19c0) */
}

/* FUN_004b19c0 @ 0x004b19c0   (est. sk_tb_fatal_trap_004b19c0)
 * Ghidra: void FUN_004b19c0(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b19e4) */
void sk_tb_fatal_trap_004b19c0(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b19e4) */
}

/* FUN_004b19e4 @ 0x004b19e4   (est. sk_tb_fatal_trap_004b19e4)
 * Ghidra: void FUN_004b19e4(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "tb_codec.c" via the
 * TB_FATAL printer FUN_00019800, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac712; helper FUN_00019800; SoftwareBreakpoint(1,0x4b1a08) */
void sk_tb_fatal_trap_004b19e4(void)
{
    FUN_00019800(0x005ac712u);   /* TB_FATAL printer; source "tb_codec.c" @0x005ac712 */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1a08) */
}

/* FUN_004b1a08 @ 0x004b1a08   (est. sk_tb_fatal_trap_004b1a08)
 * Ghidra: void FUN_004b1a08(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019830, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019830; SoftwareBreakpoint(1,0x4b1a2c) */
void sk_tb_fatal_trap_004b1a08(void)
{
    FUN_00019830(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1a2c) */
}

/* FUN_004b1a2c @ 0x004b1a2c   (est. sk_tb_fatal_trap_004b1a2c)
 * Ghidra: void FUN_004b1a2c(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00015e2c, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00015e2c; SoftwareBreakpoint(1,0x4b1a50) */
void sk_tb_fatal_trap_004b1a2c(void)
{
    FUN_00015e2c(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1a50) */
}

/* FUN_004b1a50 @ 0x004b1a50   (est. sk_tb_fatal_trap_004b1a50)
 * Ghidra: void FUN_004b1a50(void)
 * Tightbeam (TB) codec / Swift-runtime fatal-error trap thunk: reports
 * a fatal condition attributed to source "/AppleInternal/Library/BuildRoot/..." source path via the
 * TB_FATAL printer FUN_00019810, then executes `brk` and never returns.
 * Confidence: high
 * Notes: file string @0x005ac71d; helper FUN_00019810; SoftwareBreakpoint(1,0x4b1a74) */
void sk_tb_fatal_trap_004b1a50(void)
{
    FUN_00019810(0x005ac71du);   /* TB_FATAL printer; source "/AppleInternal/Library/BuildRoot/..." source path @0x005ac71d */
    SK_BRK(1);            /* SoftwareBreakpoint(1, 0x4b1a74) */
}

/* FUN_004b1a74 @ 0x004b1a74   (est. sk_vas_abort_trap_004b1a74)
 * Ghidra: void FUN_004b1a74(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter "VAS abort in function '%s' at line %d", aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005ae53e */
void sk_vas_abort_trap_004b1a74(void)
{
    FUN_004afae4(0x005ae53eu);  /* VAS abort: "VAS abort in function '%s' at line %d" @0x005ae53e */
}

/* FUN_004b1aac @ 0x004b1aac   (est. sk_vas_abort_trap_004b1aac)
 * Ghidra: void FUN_004b1aac(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005ad352, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005ad352 */
void sk_vas_abort_trap_004b1aac(void)
{
    FUN_004afae4(0x005ad352u);  /* VAS abort: 005ad352 @0x005ad352 */
}

/* FUN_004b1ae8 @ 0x004b1ae8   (est. sk_vas_abort_trap_004b1ae8)
 * Ghidra: void FUN_004b1ae8(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005ae833, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005ae833 */
void sk_vas_abort_trap_004b1ae8(void)
{
    FUN_004afae4(0x005ae833u);  /* VAS abort: 005ae833 @0x005ae833 */
}

/* FUN_004b1b24 @ 0x004b1b24   (est. sk_vas_abort_trap_004b1b24)
 * Ghidra: void FUN_004b1b24(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005ae676, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005ae676 */
void sk_vas_abort_trap_004b1b24(void)
{
    FUN_004afae4(0x005ae676u);  /* VAS abort: 005ae676 @0x005ae676 */
}

/* FUN_004b1b60 @ 0x004b1b60   (est. sk_vas_abort_trap_004b1b60)
 * Ghidra: void FUN_004b1b60(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005ae97f, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005ae97f */
void sk_vas_abort_trap_004b1b60(void)
{
    FUN_004afae4(0x005ae97fu);  /* VAS abort: 005ae97f @0x005ae97f */
}

/* FUN_004b1b9c @ 0x004b1b9c   (est. sk_vas_abort_trap_004b1b9c)
 * Ghidra: void FUN_004b1b9c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005aeae4, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005aeae4 */
void sk_vas_abort_trap_004b1b9c(void)
{
    FUN_004afae4(0x005aeae4u);  /* VAS abort: 005aeae4 @0x005aeae4 */
}

/* FUN_004b1bd8 @ 0x004b1bd8   (est. sk_vas_abort_trap_004b1bd8)
 * Ghidra: void FUN_004b1bd8(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005aea4f, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005aea4f */
void sk_vas_abort_trap_004b1bd8(void)
{
    FUN_004afae4(0x005aea4fu);  /* VAS abort: 005aea4f @0x005aea4f */
}

/* FUN_004b1c10 @ 0x004b1c10   (est. sk_vas_abort_trap_004b1c10)
 * Ghidra: void FUN_004b1c10(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005aebd3, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005aebd3 */
void sk_vas_abort_trap_004b1c10(void)
{
    FUN_004afae4(0x005aebd3u);  /* VAS abort: 005aebd3 @0x005aebd3 */
}

/* FUN_004b1c4c @ 0x004b1c4c   (est. sk_vas_abort_trap_004b1c4c)
 * Ghidra: void FUN_004b1c4c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005ae29a, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005ae29a */
void sk_vas_abort_trap_004b1c4c(void)
{
    FUN_004afae4(0x005ae29au);  /* VAS abort: 005ae29a @0x005ae29a */
}

/* FUN_004b1c84 @ 0x004b1c84   (est. sk_vas_report_unmap_readonly)
 * Ghidra: void FUN_004b1c84(undefined8 param_1)
 * Reports an 'unable to map read only' error for the given object/region through the printf helpers, then returns normally (does not trap).
 * Confidence: medium
 * Notes: Ghidra: void FUN_004b1c84(undefined8 param_1); printf trio via FUN_001185ec / FUN_00118c38 / FUN_001187f4; tag 0xeb1a02bf914012ba; returns */
void sk_vas_report_unmap_readonly(uint64_t what)
{
    FUN_001185ec(what, 0x005a8c67u);                  /* print "[%s] (%s[%d]: %s)" */
    FUN_00118c38(0xeb1a02bf914012bau, 0x005b00bfu, 0);/* print "%s(%zu): unable to map read only" */
    FUN_001187f4(10, 0xeb1a02bf914012bau);            /* print '\n' */
    /* returns to caller (not a trap) */
}

/* FUN_004b1d08 @ 0x004b1d08   (est. sk_vas_abort_trap_004b1d08)
 * Ghidra: void FUN_004b1d08(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005aecbb, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005aecbb */
void sk_vas_abort_trap_004b1d08(void)
{
    FUN_004afae4(0x005aecbbu);  /* VAS abort: 005aecbb @0x005aecbb */
}

/* FUN_004b1d40 @ 0x004b1d40   (est. sk_vas_abort_bitmap_dump)
 * Ghidra: void FUN_004b1d40(byte *param_1)
 * Diagnostic abort: prints a 'bitmaps:' header followed by one ' %#zx' per entry in the bitmap count, a newline, then panics via the VAS abort formatter (noreturn).
 * Confidence: high
 * Notes: Ghidra: void FUN_004b1d40(byte *param_1); prints 'bitmaps:' then ' %#zx' *count entries then newline then vas_abort @0x005aee98 */
void sk_vas_abort_bitmap_dump(uint8_t *count)
{
    FUN_00118b28(0x005aee89u);        /* print "bitmaps:" */
    if (*count != 0) {
        uint64_t i = 0;
        do {
            FUN_00118b28(0x005aee92u);/* print " %#zx" (one entry) */
            i = i + 1;
        } while (i < *count);
    }
    FUN_00118c28(10);                 /* print '\n' */
    FUN_004afae4(0x005aee98u);        /* [VAS abort ...] noreturn */
}

/* FUN_004b1de4 @ 0x004b1de4   (est. sk_vas_abort_trap_004b1de4)
 * Ghidra: void FUN_004b1de4(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005af609, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005af609 */
void sk_vas_abort_trap_004b1de4(void)
{
    FUN_004afae4(0x005af609u);  /* VAS abort: 005af609 @0x005af609 */
}

/* FUN_004b1e1c @ 0x004b1e1c   (est. sk_vas_abort_trap_004b1e1c)
 * Ghidra: void FUN_004b1e1c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005af86a, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005af86a */
void sk_vas_abort_trap_004b1e1c(void)
{
    FUN_004afae4(0x005af86au);  /* VAS abort: 005af86a @0x005af86a */
}

/* FUN_004b1e58 @ 0x004b1e58   (est. sk_vas_abort_trap_004b1e58)
 * Ghidra: void FUN_004b1e58(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005af7e0, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005af7e0 */
void sk_vas_abort_trap_004b1e58(void)
{
    FUN_004afae4(0x005af7e0u);  /* VAS abort: 005af7e0 @0x005af7e0 */
}

/* FUN_004b1e90 @ 0x004b1e90   (est. sk_vas_abort_trap_004b1e90)
 * Ghidra: void FUN_004b1e90(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005af9c5, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005af9c5 */
void sk_vas_abort_trap_004b1e90(void)
{
    FUN_004afae4(0x005af9c5u);  /* VAS abort: 005af9c5 @0x005af9c5 */
}

/* FUN_004b1ec8 @ 0x004b1ec8   (est. sk_vas_abort_trap_004b1ec8)
 * Ghidra: void FUN_004b1ec8(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005af6f9, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005af6f9 */
void sk_vas_abort_trap_004b1ec8(void)
{
    FUN_004afae4(0x005af6f9u);  /* VAS abort: 005af6f9 @0x005af6f9 */
}

/* FUN_004b1f04 @ 0x004b1f04   (est. sk_vas_abort_trap_004b1f04)
 * Ghidra: void FUN_004b1f04(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005af699, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005af699 */
void sk_vas_abort_trap_004b1f04(void)
{
    FUN_004afae4(0x005af699u);  /* VAS abort: 005af699 @0x005af699 */
}

/* FUN_004b1f3c @ 0x004b1f3c   (est. sk_vas_abort_trap_004b1f3c)
 * Ghidra: void FUN_004b1f3c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005aef6a, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005aef6a */
void sk_vas_abort_trap_004b1f3c(void)
{
    FUN_004afae4(0x005aef6au);  /* VAS abort: 005aef6a @0x005aef6a */
}

/* FUN_004b1f74 @ 0x004b1f74   (est. sk_vas_abort_trap_004b1f74)
 * Ghidra: void FUN_004b1f74(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005af1c3, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005af1c3 */
void sk_vas_abort_trap_004b1f74(void)
{
    FUN_004afae4(0x005af1c3u);  /* VAS abort: 005af1c3 @0x005af1c3 */
}

/* FUN_004b1fac @ 0x004b1fac   (est. sk_vas_abort_trap_004b1fac)
 * Ghidra: void FUN_004b1fac(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter "vascore::get_inspace_segmentinfo", aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_00032e30; string @0x005af2f8 */
void sk_vas_abort_trap_004b1fac(void)
{
    FUN_00032e30(0x005af2f8u);  /* VAS abort: "vascore::get_inspace_segmentinfo" @0x005af2f8 */
}

/* FUN_004b1fd4 @ 0x004b1fd4   (est. sk_vas_abort_trap_004b1fd4)
 * Ghidra: void FUN_004b1fd4(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005af3fc, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005af3fc */
void sk_vas_abort_trap_004b1fd4(void)
{
    FUN_004afae4(0x005af3fcu);  /* VAS abort: 005af3fc @0x005af3fc */
}

/* FUN_004b200c @ 0x004b200c   (est. sk_vas_abort_trap_004b200c)
 * Ghidra: void FUN_004b200c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter "vascore::get_inspace_segmentinfo", aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_00032e30; string @0x005af2f8 */
void sk_vas_abort_trap_004b200c(void)
{
    FUN_00032e30(0x005af2f8u);  /* VAS abort: "vascore::get_inspace_segmentinfo" @0x005af2f8 */
}

/* FUN_004b2034 @ 0x004b2034   (est. sk_vas_abort_trap_004b2034)
 * Ghidra: void FUN_004b2034(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter "vascore::get_inspace_segmentinfo", aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_00032e1c; string @0x005af2f8 */
void sk_vas_abort_trap_004b2034(void)
{
    FUN_00032e1c(0x005af2f8u);  /* VAS abort: "vascore::get_inspace_segmentinfo" @0x005af2f8 */
}

/* FUN_004b205c @ 0x004b205c   (est. sk_vas_abort_trap_004b205c)
 * Ghidra: void FUN_004b205c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter "vas_core::siptable_map_entry", aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_00032e1c; string @0x005afbf4 */
void sk_vas_abort_trap_004b205c(void)
{
    FUN_00032e1c(0x005afbf4u);  /* VAS abort: "vas_core::siptable_map_entry" @0x005afbf4 */
}

/* FUN_004b2084 @ 0x004b2084   (est. sk_vas_abort_trap_004b2084)
 * Ghidra: void FUN_004b2084(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter "vas_core::siptable_map", aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_00032e1c; string @0x005afa40 */
void sk_vas_abort_trap_004b2084(void)
{
    FUN_00032e1c(0x005afa40u);  /* VAS abort: "vas_core::siptable_map" @0x005afa40 */
}

/* FUN_004b20ac @ 0x004b20ac   (est. sk_vas_abort_trap_004b20ac)
 * Ghidra: void FUN_004b20ac(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005af512, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005af512 */
void sk_vas_abort_trap_004b20ac(void)
{
    FUN_004afae4(0x005af512u);  /* VAS abort: 005af512 @0x005af512 */
}

/* FUN_004b20e8 @ 0x004b20e8   (est. sk_security_assert_fail)
 * Ghidra: void FUN_004b20e8(void)
 * Security-assertion failure handler: raises 'Security assertion failed:'
 * via FUN_001150e0 and does not return.
 * Confidence: high
 * Notes: string @0x005a8b30; helper FUN_001150e0 (noreturn) */
void sk_security_assert_fail(void)
{
    FUN_001150e0(0x005a8b30u);  /* security assertion failed msg @0x005a8b30 */
}

/* FUN_004b2128 @ 0x004b2128   (est. sk_vas_abort_trap_004b2128)
 * Ghidra: void FUN_004b2128(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter "vas_core_heap_init", aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_00034874; string @0x005b03ad */
void sk_vas_abort_trap_004b2128(void)
{
    FUN_00034874(0x005b03adu);  /* VAS abort: "vas_core_heap_init" @0x005b03ad */
}

/* FUN_004b2150 @ 0x004b2150   (est. sk_vas_abort_trap_004b2150)
 * Ghidra: void FUN_004b2150(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b0b4b, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b0b4b */
void sk_vas_abort_trap_004b2150(void)
{
    FUN_004afae4(0x005b0b4bu);  /* VAS abort: 005b0b4b @0x005b0b4b */
}

/* FUN_004b2188 @ 0x004b2188   (est. sk_vas_abort_trap_004b2188)
 * Ghidra: void FUN_004b2188(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b0aec, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b0aec */
void sk_vas_abort_trap_004b2188(void)
{
    FUN_004afae4(0x005b0aecu);  /* VAS abort: 005b0aec @0x005b0aec */
}

/* FUN_004b21c4 @ 0x004b21c4   (est. sk_vas_abort_trap_004b21c4)
 * Ghidra: void FUN_004b21c4(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter "_ensure_watermark", aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_00034874; string @0x005b095b */
void sk_vas_abort_trap_004b21c4(void)
{
    FUN_00034874(0x005b095bu);  /* VAS abort: "_ensure_watermark" @0x005b095b */
}

/* FUN_004b21ec @ 0x004b21ec   (est. sk_vas_abort_trap_004b21ec)
 * Ghidra: void FUN_004b21ec(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b0a38, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b0a38 */
void sk_vas_abort_trap_004b21ec(void)
{
    FUN_004afae4(0x005b0a38u);  /* VAS abort: 005b0a38 @0x005b0a38 */
}

/* FUN_004b2224 @ 0x004b2224   (est. sk_vas_abort_trap_004b2224)
 * Ghidra: void FUN_004b2224(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b098f, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b098f */
void sk_vas_abort_trap_004b2224(void)
{
    FUN_004afae4(0x005b098fu);  /* VAS abort: 005b098f @0x005b098f */
}

/* FUN_004b225c @ 0x004b225c   (est. sk_vas_abort_trap_004b225c)
 * Ghidra: void FUN_004b225c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b03cf, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b03cf */
void sk_vas_abort_trap_004b225c(void)
{
    FUN_004afae4(0x005b03cfu);  /* VAS abort: 005b03cf @0x005b03cf */
}

/* FUN_004b2294 @ 0x004b2294   (est. sk_vas_abort_trap_004b2294)
 * Ghidra: void FUN_004b2294(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b0789, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b0789 */
void sk_vas_abort_trap_004b2294(void)
{
    FUN_004afae4(0x005b0789u);  /* VAS abort: 005b0789 @0x005b0789 */
}

/* FUN_004b22cc @ 0x004b22cc   (est. sk_vas_abort_trap_004b22cc)
 * Ghidra: void FUN_004b22cc(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005aecbb, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005aecbb */
void sk_vas_abort_trap_004b22cc(void)
{
    FUN_004afae4(0x005aecbbu);  /* VAS abort: 005aecbb @0x005aecbb */
}

/* FUN_004b2304 @ 0x004b2304   (est. sk_vas_abort_trap_004b2304)
 * Ghidra: void FUN_004b2304(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b053f, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b053f */
void sk_vas_abort_trap_004b2304(void)
{
    FUN_004afae4(0x005b053fu);  /* VAS abort: 005b053f @0x005b053f */
}

/* FUN_004b233c @ 0x004b233c   (est. sk_vas_abort_trap_004b233c)
 * Ghidra: void FUN_004b233c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b05c9, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b05c9 */
void sk_vas_abort_trap_004b233c(void)
{
    FUN_004afae4(0x005b05c9u);  /* VAS abort: 005b05c9 @0x005b05c9 */
}

/* FUN_004b2368 @ 0x004b2368   (est. sk_vas_abort_trap_004b2368)
 * Ghidra: void FUN_004b2368(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b0baf, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b0baf */
void sk_vas_abort_trap_004b2368(void)
{
    FUN_004afae4(0x005b0bafu);  /* VAS abort: 005b0baf @0x005b0baf */
}

/* FUN_004b23a0 @ 0x004b23a0   (est. sk_vas_abort_trap_004b23a0)
 * Ghidra: void FUN_004b23a0(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b0d16, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b0d16 */
void sk_vas_abort_trap_004b23a0(void)
{
    FUN_004afae4(0x005b0d16u);  /* VAS abort: 005b0d16 @0x005b0d16 */
}

/* FUN_004b23d8 @ 0x004b23d8   (est. sk_vas_page_release)
 * Ghidra: void FUN_004b23d8(long param_1)
 * VAS page-release routine. Given a 12-bit page tag, it looks up the owning region, clears the page's present bit in the region bitmap, decrements the region refcount (frees the region into a global freelist when it drops past the 0xff reserve threshold), and commits the surrounding transaction. Crashes via [VAS abort] on invariant violations.
 * Confidence: medium
 * Notes: Ghidra: void FUN_004b23d8(long param_1); CallSupervisor(4) loop; FUN_0005acac(0x6af188,4,8); FUN_00034bd8; FUN_00035418 lookup; bitmap at reg+ (off>>12); refcount dec; FUN_00034d5c commit; SoftwareBreakpoint(0x5519,0x4b24f0) on overflow */
void sk_vas_page_release(uint64_t tag)
{
    /* Spin: while the caller supplied tag == 1, re-issue the supervisor call.
     * (Transcribed faithfully; likely a drain/retry for a pending refcount.) */
    do { CALL_SUPERVISOR(4); } while (tag == 1);

    /* Fetch the global VAS structure (key 0x6af188, 4 elems of 8). */
    long *glob = FUN_0005acac(0x6af188, 4, 8);
    /* Open a 16-byte transaction on glob[0]->+0x10 (lo bit = in-flight marker). */
    cl4_pair_t txn = FUN_00034bd8(*(uint64_t *)(*glob + 0x10));
    if ((txn.lo & 1) != 0) {
        FUN_004afae4(0x005b18beu);      /* [VAS abort ...] txn already in flight */
    }

    /* Look up the region owning `tag`. */
    uint64_t *reg = FUN_00035418(tag);
    if (reg == NULL) {
        glob[7] = (long)tag;            /* untracked: record the tag as pending */
    } else {
        uint64_t off = tag - reg[5];    /* offset of tag from region base */
        if (0x3fff < off) {
            FUN_004afae4(0x005b1937u);  /* [VAS abort ...] offset past region bound */
        }
        uint64_t *count = reg + 4;          /* 16-bit refcount word */
        uint64_t *bitmap = reg + (off >> 12); /* page-slot bitmap word */
        if ((bitmap < reg || count < bitmap + 1) || bitmap + 1 < bitmap) {
            SK_BRK(0x5519);             /* SoftwareBreakpoint(0x5519, 0x4b24f0) */
        }
        uint64_t bit = (uint64_t)1 << ((off >> 6) & 0x3f);
        if ((*bitmap & bit) == 0) {
            FUN_004afae4(0x005b199du);  /* [VAS abort ...] page not marked present */
        }
        *bitmap = *bitmap & ~bit;       /* clear the present bit */
        uint64_t rc = *count;
        if (0xff < (uint16_t)rc) {      /* refcount about to drop below reserve: */
            reg[6] = (uint64_t)glob[6]; /* link reg into the freelist head glob[6] */
            if (reg + 9 < reg) {
                SK_BRK(0x5519);         /* SoftwareBreakpoint(0x5519, 0x4b24f0) */
            }
            glob[6] = (long)reg;
        }
        *(uint16_t *)count = (uint16_t)rc - 1;   /* decrement refcount */
    }
    FUN_00034d5c(*(uint64_t *)(*glob + 0x10), txn.lo, txn.hi);   /* commit txn */
}

/* FUN_004b2584 @ 0x004b2584   (est. sk_vas_abort_trap_004b2584)
 * Ghidra: void FUN_004b2584(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b1dab, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b1dab */
void sk_vas_abort_trap_004b2584(void)
{
    FUN_004afae4(0x005b1dabu);  /* VAS abort: 005b1dab @0x005b1dab */
}

/* FUN_004b25bc @ 0x004b25bc   (est. sk_vas_abort_trap_004b25bc)
 * Ghidra: void FUN_004b25bc(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b0ee4, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b0ee4 */
void sk_vas_abort_trap_004b25bc(void)
{
    FUN_004afae4(0x005b0ee4u);  /* VAS abort: 005b0ee4 @0x005b0ee4 */
}

/* FUN_004b25f4 @ 0x004b25f4   (est. sk_vas_abort_trap_004b25f4)
 * Ghidra: void FUN_004b25f4(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b0f56, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b0f56 */
void sk_vas_abort_trap_004b25f4(void)
{
    FUN_004afae4(0x005b0f56u);  /* VAS abort: 005b0f56 @0x005b0f56 */
}

/* FUN_004b262c @ 0x004b262c   (est. sk_vas_abort_trap_004b262c)
 * Ghidra: void FUN_004b262c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b1130, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b1130 */
void sk_vas_abort_trap_004b262c(void)
{
    FUN_004afae4(0x005b1130u);  /* VAS abort: 005b1130 @0x005b1130 */
}

/* FUN_004b2664 @ 0x004b2664   (est. sk_vas_abort_trap_004b2664)
 * Ghidra: void FUN_004b2664(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b10be, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b10be */
void sk_vas_abort_trap_004b2664(void)
{
    FUN_004afae4(0x005b10beu);  /* VAS abort: 005b10be @0x005b10be */
}

/* FUN_004b269c @ 0x004b269c   (est. sk_vas_abort_trap_004b269c)
 * Ghidra: void FUN_004b269c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b1052, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b1052 */
void sk_vas_abort_trap_004b269c(void)
{
    FUN_004afae4(0x005b1052u);  /* VAS abort: 005b1052 @0x005b1052 */
}

/* FUN_004b26d4 @ 0x004b26d4   (est. sk_vas_abort_trap_004b26d4)
 * Ghidra: void FUN_004b26d4(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b127f, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b127f */
void sk_vas_abort_trap_004b26d4(void)
{
    FUN_004afae4(0x005b127fu);  /* VAS abort: 005b127f @0x005b127f */
}

/* FUN_004b270c @ 0x004b270c   (est. sk_vas_abort_trap_004b270c)
 * Ghidra: void FUN_004b270c(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter 005b1b40, aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b1b40 */
void sk_vas_abort_trap_004b270c(void)
{
    FUN_004afae4(0x005b1b40u);  /* VAS abort: 005b1b40 @0x005b1b40 */
}


/* FUN_004b2748 @ 0x004b2748   (est. sk_vas_abort_trap_004b2748)
 * Ghidra: void FUN_004b2748(void)
 * VAS abort stub: panics (does not return) with the VAS abort
 * formatter "VAS abort in function '%s' at line %d", aborting the Secure Kernel.
 * Confidence: high
 * Notes: helper FUN_004afae4; string @0x005b1ade */
void sk_vas_abort_trap_004b2748(void)
{
    FUN_004afae4(0x005b1adeu);  /* VAS abort: "VAS abort in function '%s' at line %d" @0x005b1ade */
}
