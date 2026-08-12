/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R42: 0x004b2780-0x004b43f4 (120 functions). This slice is the
 * fail-closed abort / "Unexpected L4_Error" panic cluster of the VAS
 * (virtual address space) fault / freezer / span-map layer, plus a small
 * number of real functions:
 *   - 004b2820 / 004b3a58  the shared "[%s] (%s[%d]: %s): " error-prefix
 *     printer used by every Unexpected L4_Error panic (takes the
 *     operation-name in the first register, flushes via the fmt engine).
 *   - 004b2c84 / 004b2eb8 / 004b363c  supervisor-wait wrappers that spin
 *     on CallSupervisor(4) while a status word is 1, then branch on the
 *     low byte of the status (0 => success fast path, else abort).
 *   - 004b2de0  a freezer-span allocation helper (bumps a global stat
 *     counter, allocates a 16 KiB span, maps it, waits for the mapping).
 *   - 004b3538  a span-capability callback that invokes a vtable method,
 *     then stores a pending pointer into the span owner's op slot.
 *   - 004b3768 / 004b377c / 004b3790 / 004b37a4  per-va stat counters.
 *   - 004b3da4 / 004b3e5c  VAS "_populate_level" error reporters.
 *   - 004b3f24  a bounds-checking bool helper (spanmap cap probe).
 * The bulk are deterministic noreturn abort shims: each calls a cL4
 * diagnostic reporter (FUN_004afae4 "VAS abort in function %s at line %d",
 * or a source-file/function-name reporter, or the EASM_C.c fatal) with a
 * fixed message and never returns. All names are estimates unless a
 * message string matches.
 *
 * Conventions (sibling-slice): out-of-slice callees keep their FUN_
 * addresses as unprototyped externs (word_t result = x0); in-slice
 * functions use sk_r42_<addr>. SoftwareBreakpoint(1, addr) is rendered
 * CL4_SWBP(addr); CallSupervisor(4) is rendered CL4_CALLSV(4).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;
typedef unsigned long ulong;   /* Ghidra ulong -> used in a few bodies */
typedef unsigned int uint;     /* Ghidra uint  -> used in a few bodies */
typedef uint64_t (*code)();
typedef struct { uint64_t lo, hi; } skr42_w16;

/* Ghidra SoftwareBreakpoint(1, addr) - fail-closed trap, does not return. */
static inline unsigned long CL4_SWBP(unsigned long addr)
{ (void)addr; __builtin_trap(); }

/* Ghidra CallSupervisor(4) - supervisor call; returns status in x0. */
static inline unsigned long CL4_CALLSV(uint32_t n)
{ (void)n; __builtin_trap(); }

/* Out-of-slice callees (bodies owned by their range workers). */
/* Fatal / abort reporters (all noreturn): */
extern void FUN_004afae4(const char *fmt, ...);   /* "VAS abort in function %s at line %d" fatal */
extern word_t FUN_00041184();   /* noreturn function-name reporter (startfault_impl_managed) */
extern word_t FUN_00041198();   /* noreturn function-name reporter (startfault_impl_managed) */
extern word_t FUN_000411ac();   /* noreturn function-name reporter (handle_fault/faulthandler_destroy) */
extern word_t FUN_00041170();   /* noreturn function-name reporter (span_asan_usable) */
extern word_t FUN_000410e4();   /* noreturn function-name reporter (vascore__span_holder_get_cap) */
extern word_t FUN_00044828();   /* noreturn vas_core_shadow_space_setup reporter */
extern word_t FUN_0004483c();   /* noreturn alloc_temp_cap/alloc_heap_cap reporter */
extern word_t FUN_000447f8();   /* noreturn vas_core_shadow_space_* reporter */
extern void   FUN_000447dc();   /* noreturn "mapped level" abort */
extern word_t FUN_0011d7e8();   /* noreturn stack-canary / runtime fatal */
extern word_t FUN_0004b488();   /* noreturn EASM_C.c fatal */
extern word_t FUN_0004b478();   /* noreturn EASM_C.c fatal */
extern word_t FUN_00118b28();   /* noreturn EASM fatal (data arg) */
extern word_t FUN_001185ec();   /* printf-style fmt engine (format into buffer) */
extern word_t FUN_0011858c();   /* fmt engine close/flush */
extern word_t FUN_00118c38();   /* fmt engine flush */
extern word_t FUN_001187f4();   /* fmt engine newline/putc */
extern void   FUN_00041160();   /* noreturn "Unexpected L4_Error" tail */
extern void   FUN_00044818();   /* noreturn "Unexpected L4_Error" tail (shadow) */
/* Supervisor / error-stack preamble helpers: */
extern void   FUN_00041138();   /* VAS error preamble (begin) */
extern void   FUN_0004108c();   /* VAS error stack push */
extern void   FUN_0004112c();   /* VAS error stack pop */
extern void   FUN_000410cc();   /* VAS noop preamble */
extern void   FUN_000410f8();   /* VAS noop (success branch) */
extern void   FUN_000410ac();   /* VAS error stack (fail branch) */
extern void   FUN_00041110();   /* VAS noop (pc arg) */
extern void   FUN_0004114c();   /* VAS noop (pc arg) */
extern void   FUN_000411c0();   /* VAS noop (pc arg) */
extern void   FUN_00044790();   /* VAS error string helper */
extern void   FUN_000447b0();   /* VAS error log helper */
extern void   FUN_0004480c();   /* VAS error string helper */
extern void   FUN_0003f980();   /* err-name printer */
/* Real-function helpers: */
extern word_t FUN_00032cd0();   /* vspace layout check (returns status) */
extern void   FUN_00043f28();   /* span alloc/cleanup */
extern void   FUN_0003d438();   /* region map span */
extern void   FUN_00042754();   /* pt alloc flags */
/* Stat counters (freezer / span layer): */
extern ulong  sk_stat_cow8;     /* DAT_006ad328 */
extern ulong  DAT_006ad318;
extern ulong  DAT_006ad324;
extern ulong  DAT_006ad32c;
extern ulong  DAT_006ad398;

/* String / data literals referenced by this slice. */
extern char s_Unexpected_L4_Error___s__zu__err_005b4ef3[];
extern char s_Unexpected_L4_Error___s__zu__err_005b53f2[];
extern char s_Unexpected_L4_Error___s__zu__err_005b548e[];
extern char s_Unexpected_L4_Error___s__zu__err_005b552b[];
extern char s_Unexpected_L4_Error___s__zu__err_005b588b[];
extern char s_Unexpected_L4_Error___s__zu__err_005b58de[];
extern char s_Unexpected_L4_Error___s__zu__err_005b59b2[];
extern char s_Unexpected_L4_Error___s__zu__err_005b5a20[];
extern char s_Unexpected_L4_Error___s__zu__err_005b5b07[];
extern char s_Unexpected_L4_Error___s__zu__err_005b5b81[];
extern char s_Unexpected_L4_Error___s__zu__err_005b5c7b[];
extern char s_Unexpected_L4_Error___s__zu__err_005b5cf9[];
extern char s_Unexpected_L4_Error___s__zu__err_005b5d3f[];
extern char s_Unexpected_L4_Error___s__zu__err_005b5ed9[];
extern char s_Unexpected_L4_Error___s__zu__err_005b67be[];
extern char s_Unexpected_L4_Error___s__zu__err_005b6b41[];
extern char s_Unexpected_L4_Error___s__zu__err_005b700b[];
extern char s_Unexpected_L4_Error___s__zu__err_005b767e[];
extern char s_Unexpected_L4_Error___s__zu__err_005b4509[];
extern char s_Unexpected_L4_Error___s__zu__err_005b010f[];
extern char s_VAS_abort_in_function__s_at_lin_005b1d3f[];
extern char s_VAS_abort_in_function__s_at_lin_005b1f78[];
extern char s_VAS_abort_in_function__s_at_lin_005b21f4[];
extern char s_VAS_abort_in_function__s_at_lin_005b228c[];
extern char s_VAS_abort_in_function__s_at_lin_005b4bab[];
extern char s_VAS_abort_in_function__s_at_lin_005b5111[];
extern char s_VAS_abort_in_function__s_at_lin_005b509d[];
extern char s_VAS_abort_in_function__s_at_lin_005b4d0e[];
extern char s_VAS_abort_in_function__s_at_lin_005b4df7[];
extern char s_VAS_abort_in_function__s_at_lin_005b4d8b[];
extern char s_VAS_abort_in_function__s_at_lin_005b5262[];
extern char s_VAS_abort_in_function__s_at_lin_005b556d[];
extern char s_VAS_abort_in_function__s_at_lin_005b55d2[];
extern char s_VAS_abort_in_function__s_at_lin_005b5384[];
extern char s_VAS_abort_in_function__s_at_lin_005b52ef[];
extern char s_VAS_abort_in_function__s_at_lin_005b46f9[];
extern char s_VAS_abort_in_function__s_at_lin_005b476c[];
extern char s_VAS_abort_in_function__s_at_lin_005b4a5a[];
extern char s_VAS_abort_in_function__s_at_lin_005b49d8[];
extern char s_VAS_abort_in_function__s_at_lin_005b4ac1[];
extern char s_VAS_abort_in_function__s_at_lin_005b2a19[];
extern char s_VAS_abort_in_function__s_at_lin_005b3daf[];
extern char s_VAS_abort_in_function__s_at_lin_005b2eb2[];
extern char s_VAS_abort_in_function__s_at_lin_005b2f42[];
extern char s_VAS_abort_in_function__s_at_lin_005b3024[];
extern char s_VAS_abort_in_function__s_at_lin_005b2fc3[];
extern char s_VAS_abort_in_function__s_at_lin_005b311f[];
extern char s_VAS_abort_in_function__s_at_lin_005b3372[];
extern char s_VAS_abort_in_function__s_at_lin_005b31c2[];
extern char s_VAS_abort_in_function__s_at_lin_005b3b4d[];
extern char s_VAS_abort_in_function__s_at_lin_005b42c1[];
extern char s_VAS_abort_in_function__s_at_lin_005b5935[];
extern char s_VAS_abort_in_function__s_at_lin_005b6211[];
extern char s_VAS_abort_in_function__s_at_lin_005b6a43[];
extern char s_VAS_abort_in_function__s_at_lin_005b6b90[];
extern char s_VAS_abort_in_function__s_at_lin_005b6c5a[];
extern char s_VAS_abort_in_function__s_at_lin_005b7977[];
extern char s_VAS_abort_in_function__s_at_lin_005b8197[];
extern char s_VAS_abort_in_function__s_at_lin_005b7c2e[];
extern char s_VAS_abort_in_function__s_at_lin_005b82d4[];
extern char s_VAS_abort_in_function__s_at_lin_005b7d95[];
extern char s_VAS_abort_in_function__s_at_lin_005b7e47[];
extern char s_VAS_abort_in_function__s_at_lin_005b8006[];
extern char s_VAS_abort_in_function__s_at_lin_005b84d5[];
extern char s_VAS_abort_in_function__s_at_lin_005b807c[];
extern char s_VAS_abort_in_function__s_at_lin_005b810e[];
extern char s_VAS_abort_in_function__s_at_lin_005b5935[]; /* dup */
extern char s_Freezer_bump_called_with_invalid_005b21f4[];
extern char s_Freezer_tried_to_free_a_backing_s_005b228c[];
extern char s__VAS_abort_in_function__s_at_lin_005b1d3f[];
extern char s__handle_fault_005b4c15[];
extern char s__startfault_impl_managed_005b5697[];
extern char s__startfault_impl_cow_005b5920[];
extern char s__faulthandler_destroy_005b5f9f[];
extern char s__span_asan_usable_005b6017[];
extern char s_vascore__span_holder_get_cap_005b320c[];
extern char s_spanmap_get_cap_had_unexpected_i_005b2e84[];
extern char s_vas_core_shadow_space_setup_005b6466[];
extern char s_vas_core_shadow_space_cap_005b6888[];
extern char s_vas_core_shadow_space_populate_005b691c[];
extern char s_vas_core_shadow_space_populate_t_005b693b[];
extern char s__alloc_temp_cap_005b734b[];
extern char s_alloc_heap_cap_005b6b14[];
extern char s_EASM_C_c_005b8541[];
extern char s_VAS_error_in_function__s_at__s__005b7239[];
extern char s_VAS_error_in_function__s_at__s__005b72ab[];
extern char s___s____s__d____s___005a8c67[];
extern word_t DAT_005ba280;
extern word_t DAT_005ba1b9;
extern word_t DAT_005ba0fb;

/* ================================================================== */
/* Shared L4-error prefix printer (real logic)                        */
/* ================================================================== */

/* FUN_004b2820 @ 0x004b2820   (est. sk_vas_l4err_prefix)
 * Ghidra: void FUN_004b2820(undefined8 param_1)
 * Formats the shared "[%s] (%s[%d]: %s): " error prefix (operation name in
 * x0) via the fmt engine and flushes it. Called at the head of every
 * "Unexpected L4_Error" panic in this slice.
 * Confidence: high (message string 005a8c67 matches). */
void sk_r42_004b2820(word_t op)
{
    FUN_001185ec(op, "[%s] (%s[%d]: %s): ");  /* s___s____s__d____s___005a8c67 */
    FUN_00118c38(0xeb1a02bf914012ba, 0, (word_t)&op);
    FUN_001187f4(10, 0xeb1a02bf914012ba);
}

/* FUN_004b3a58 @ 0x004b3a58   (est. sk_vas_l4err_prefix2)
 * Ghidra: void FUN_004b3a58(undefined8 param_1)
 * Identical twin of 004b2820: the shadow-space variant of the L4-error
 * prefix printer (operation name in x0), used by the shadow populate /
 * cap-move panic wrappers.
 * Confidence: high (identical body + message string). */
void sk_r42_004b3a58(word_t op)
{
    FUN_001185ec(op, "[%s] (%s[%d]: %s): ");  /* s___s____s__d____s___005a8c67 */
    FUN_00118c38(0xeb1a02bf914012ba, 0, (word_t)&op);
    FUN_001187f4(10, 0xeb1a02bf914012ba);
}

/* ================================================================== */
/* Supervisor-wait + conditional-abort real functions                 */
/* ================================================================== */

/* FUN_004b2c84 @ 0x004b2c84   (est. sk_vas_supervisor_wait_rotmpcap)
 * Ghidra: void FUN_004b2c84(undefined8 p1, undefined8 p2, ulong status)
 * Spins on CallSupervisor(4) while `status == 1`; if the low byte of
 * status is 0 it takes the success fast path (returns), else it falls
 * through the VAS error stack, prints the prefix, and noreturn-aborts
 * with err='L4_Cap_Delete(fault->rotmpcap)' (005b58de).
 * Confidence: medium (status-word artifact; success branch condition). */
void sk_r42_004b2c84(word_t p1, word_t p2, ulong status)
{
    FUN_000410cc();
    do { CL4_CALLSV(4); } while (status == 1);
    if ((status & 0xff) == 0) {
        FUN_000410f8();
        if (1) return;
        FUN_0011d7e8();   /* unreachable */
    }
    FUN_000410ac();
    FUN_000411c0();
    sk_r42_004b2820(0);
    FUN_0003f980();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b58de);  /* noreturn */
}

/* FUN_004b2eb8 @ 0x004b2eb8   (est. sk_vas_supervisor_wait_writespan)
 * Ghidra: void FUN_004b2eb8(undefined8 p1, undefined8 p2, ulong status)
 * Same supervisor-wait + conditional-abort shape as 004b2c84, but with the
 * shared prefix printer (no pc-arg noop) and noreturn err='L4_Cap_Delete(
 * fault->write_spancap)' (005b5d3f).
 * Confidence: medium. */
void sk_r42_004b2eb8(word_t p1, word_t p2, ulong status)
{
    FUN_000410cc();
    do { CL4_CALLSV(4); } while (status == 1);
    if ((status & 0xff) == 0) {
        FUN_000410f8();
        if (1) return;
        FUN_0011d7e8();   /* unreachable */
    }
    FUN_000410ac();
    sk_r42_004b2820(0);
    FUN_0003f980();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b5d3f);  /* noreturn */
}

/* FUN_004b363c @ 0x004b363c   (est. sk_vas_supervisor_wait_readspan)
 * Ghidra: void FUN_004b363c(undefined8 p1, undefined8 p2, ulong status)
 * Same supervisor-wait + conditional-abort shape, with the pc-arg noop
 * (FUN_00041110) and noreturn err='L4_Cap_Delete(fault->rotmpcap)'
 * (005b58de).
 * Confidence: medium. */
void sk_r42_004b363c(word_t p1, word_t p2, ulong status)
{
    FUN_000410cc();
    do { CL4_CALLSV(4); } while (status == 1);
    if ((status & 0xff) == 0) {
        FUN_000410f8();
        if (1) return;
        FUN_0011d7e8();   /* unreachable */
    }
    FUN_000410ac();
    FUN_00041110();
    sk_r42_004b2820(0);
    FUN_0003f980();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b58de);  /* noreturn */
}

/* FUN_004b2de0 @ 0x004b2de0   (est. sk_vas_span_alloc_bump)
 * Ghidra: void FUN_004b2de0(undefined8 p1, undefined8 *span, undefined8 *p3, long owner)
 * Freezer span-allocation helper: bumps the global freezer-span counter
 * (DAT_006ad398), runs the vspace layout check, allocates a 16 KiB
 * (0x4000) span, maps it into the region, then waits (CallSupervisor(4))
 * while the owner's status word at offset 0x68 is 1.
 * Confidence: medium (global + register-artifact dispatch). */
void sk_r42_004b2de0(word_t p1, word_t *span, word_t *p3, long owner)
{
    DAT_006ad398 = DAT_006ad398 + 1;
    {
        word_t u = FUN_00032cd0();
        FUN_00043f28(u, *span, 0x4000, 1, 0);
        FUN_0003d438(*span, 0x4000, *p3, 0, 0);
    }
    do { CL4_CALLSV(4); } while (*(long *)(owner + 0x68) == 1);
}

/* FUN_004b3538 @ 0x004b3538   (est. sk_vas_span_cap_callback)
 * Ghidra: void FUN_004b3538(long self, long p2, long owner, undefined8 ptr)
 * Span-capability callback: invokes the owner object's vtable method
 * (offset +0x10) with the object at self+0xb0, waits (CallSupervisor(4))
 * while p2 is 1, then stores `ptr` into the span owner's op slot at
 * *(*(owner+0x28)+8)+0x18 if that slot is currently null.
 * Confidence: medium (vtable call + slot-store pattern). */
void sk_r42_004b3538(long self, long p2, long owner, word_t ptr)
{
    (**(code **)(*(long *)(self + 0xb8) + 0x10))(*(word_t *)(self + 0xb0));
    do { CL4_CALLSV(4); } while (p2 == 1);
    {
        long l = *(long *)(*(long *)(owner + 0x28) + 8);
        if (*(long *)(l + 0x18) == 0) {
            *(word_t *)(l + 0x18) = ptr;
        }
    }
}

/* FUN_004b3f24 @ 0x004b3f24   (est. sk_vas_spanmap_cap_probe)
 * Ghidra: bool FUN_004b3f24(long *status, long *p2, undefined8 *base, undefined8 *end, undefined8 *out)
 * Bounds-checking spanmap capability probe: waits while the spanmap status
 * word (*status) is 1, computes the capability pointer at
 * base + *p2 (+1 element), and if it lies in [base, end) copies it to
 * *out. Returns true when the probe was out of bounds (i.e. the copied
 * element was outside the valid range).
 * Confidence: medium (pointer-arithmetic bounds artifact). */
bool sk_r42_004b3f24(long *status, long *p2, word_t *base, word_t *end, word_t *out)
{
    do { CL4_CALLSV(4); } while (*status == 1);
    {
        word_t *cap = base + *p2;
        word_t *cap_end = cap + 1;
        if ((cap >= base && end >= cap_end) && cap_end >= cap) {
            *out = *cap;
        }
        return (cap < base || end < cap_end) || cap_end < cap;
    }
}

/* FUN_004b3da4 @ 0x004b3da4   (est. sk_vas_populate_level_alloc_err)
 * Ghidra: void FUN_004b3da4(void)
 * VAS _populate_level allocation-failure reporter: obtains the pt-alloc
 * flags, then prints the "[VAS error in function %s at %s:%d] _populate_
 * level(...): allocation of type %d failed %lx" message (005b7239) via the
 * fmt engine and closes the format buffer.
 * Confidence: high (message string matches). */
void sk_r42_004b3da4(void)
{
    FUN_00042754();
    FUN_001185ec(0xeb1a02bf914012ba, "[VAS error in function %s at %s:%d] _populate_level(%lx, %lu): allocation of type %d failed %lx\n\n");
    FUN_0011858c(0xeb1a02bf914012ba);
}

/* FUN_004b3e5c @ 0x004b3e5c   (est. sk_vas_populate_level_err)
 * Ghidra: void FUN_004b3e5c(void)
 * VAS _populate_level generic-failure reporter: prints the "[VAS error in
 * function %s at %s:%d] _populate_level(...): failed" message (005b72ab)
 * and closes the format buffer.
 * Confidence: high (message string matches). */
void sk_r42_004b3e5c(void)
{
    FUN_001185ec(0xeb1a02bf914012ba, "[VAS error in function %s at %s:%d] _populate_level(%lx, %lu): failed\n\n");
    FUN_0011858c(0xeb1a02bf914012ba);
}

/* ================================================================== */
/* Per-va stat counters (real logic)                                  */
/* ================================================================== */

/* FUN_004b3768 @ 0x004b3768   (est. sk_vas_stat_006ad318)
 * Ghidra: void FUN_004b3768(void)
 * Bumps the freezer/span stat counter DAT_006ad318.
 * Confidence: high (deterministic counter increment). */
void sk_r42_004b3768(void)
{
    DAT_006ad318 = DAT_006ad318 + 1;
}

/* FUN_004b377c @ 0x004b377c   (est. sk_vas_stat_006ad328)
 * Ghidra: void FUN_004b377c(void)
 * Bumps the freezer/span stat counter DAT_006ad328 (sk_stat_cow8).
 * Confidence: high (deterministic counter increment). */
void sk_r42_004b377c(void)
{
    DAT_006ad328 = DAT_006ad328 + 1;
}

/* FUN_004b3790 @ 0x004b3790   (est. sk_vas_stat_006ad324)
 * Ghidra: void FUN_004b3790(void)
 * Bumps the freezer/span stat counter DAT_006ad324.
 * Confidence: high (deterministic counter increment). */
void sk_r42_004b3790(void)
{
    DAT_006ad324 = DAT_006ad324 + 1;
}

/* FUN_004b37a4 @ 0x004b37a4   (est. sk_vas_stat_006ad32c)
 * Ghidra: void FUN_004b37a4(void)
 * Bumps the freezer/span stat counter DAT_006ad32c.
 * Confidence: high (deterministic counter increment). */
void sk_r42_004b37a4(void)
{
    DAT_006ad32c = DAT_006ad32c + 1;
}

/* ================================================================== */
/* Unexpected L4_Error panic wrappers (noreturn)                      */
/* ================================================================== */

/* FUN_004b29f8 @ 0x004b29f8   (est. sk_vas_panic_pgframe_protect)
 * Ghidra: void FUN_004b29f8(void)
 * noreturn Unexpected L4_Error: err='L4_Arm64_PageFrame_Protect(frame,
 * perms)' (005b4ef3). Preamble + prefix + abort; never returns.
 * Confidence: high (deterministic abort). */
void sk_r42_004b29f8(void)
{
    FUN_00041138();
    FUN_0004108c();
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b4ef3);  /* noreturn */
}

/* FUN_004b2abc @ 0x004b2abc   (est. sk_vas_panic_pmm_alloc_temp)
 * Ghidra: void FUN_004b2abc(void)
 * noreturn Unexpected L4_Error: err='pmm_alloc_temp_with(...)' (005b53f2).
 * Confidence: high (deterministic abort). */
void sk_r42_004b2abc(void)
{
    FUN_00041138();
    FUN_0004108c();
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b53f2);  /* noreturn */
}

/* FUN_004b2b10 @ 0x004b2b10   (est. sk_vas_panic_map_this_frame)
 * Ghidra: void FUN_004b2b10(void)
 * noreturn Unexpected L4_Error: err='_map_this_frame(fault->write_span,
 * (uintptr_t)fault->write_buffer, fault->rwtmpcap)' (005b548e).
 * Confidence: high (deterministic abort). */
void sk_r42_004b2b10(void)
{
    FUN_00041138();
    FUN_0004108c();
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b548e);  /* noreturn */
}

/* FUN_004b2b64 @ 0x004b2b64   (est. sk_vas_panic_cap_delete_rwtmpcap)
 * Ghidra: void FUN_004b2b64(void)
 * noreturn Unexpected L4_Error: err='L4_Cap_Delete(fault->rwtmpcap)'
 * (005b552b).
 * Confidence: high (deterministic abort). */
void sk_r42_004b2b64(void)
{
    FUN_00041138();
    FUN_0004108c();
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b552b);  /* noreturn */
}

/* FUN_004b2e64 @ 0x004b2e64   (est. sk_vas_panic_downgrade_ifneeded)
 * Ghidra: void FUN_004b2e64(void)
 * noreturn Unexpected L4_Error: err='_map_this_frame_downgrade_ifneeded(
 * span, fault->active_address, fault->write_spancap)' (005b5ed9).
 * Confidence: high (deterministic abort). */
void sk_r42_004b2e64(void)
{
    FUN_00041138();
    FUN_0004108c();
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b5ed9);  /* noreturn */
}

/* FUN_004b35a0 @ 0x004b35a0   (est. sk_vas_panic_pmm_free_frame)
 * Ghidra: void FUN_004b35a0(void)
 * noreturn Unexpected L4_Error: err='pmm_free_with(vcss->pmm, frame)'
 * (005b4509).
 * Confidence: high (deterministic abort). */
void sk_r42_004b35a0(void)
{
    FUN_00041138();
    FUN_0004108c();
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b4509);  /* noreturn */
}

/* FUN_004b3cd0 @ 0x004b3cd0   (est. sk_vas_panic_pmm_free_root)
 * Ghidra: void FUN_004b3cd0(void)
 * noreturn Unexpected L4_Error: err='pmm_free_with(vcss->pmm, root)'
 * (005b67be). Shadow-space variant preamble.
 * Confidence: high (deterministic abort). */
void sk_r42_004b3cd0(void)
{
    FUN_00041138();
    FUN_00044790();
    sk_r42_004b3a58(0);
    FUN_0004480c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b67be);  /* noreturn */
}

/* FUN_004b3fa4 @ 0x004b3fa4   (est. sk_vas_panic_pmm_free_range)
 * Ghidra: void FUN_004b3fa4(void)
 * noreturn Unexpected L4_Error: err='pmm_free_range_with(vcss->pmm,
 * dest, ncaps)' (005b6b41). Shadow-space variant.
 * Confidence: high (deterministic abort). */
void sk_r42_004b3fa4(void)
{
    FUN_00041138();
    FUN_00044790();
    sk_r42_004b3a58(0);
    FUN_0004480c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b6b41);  /* noreturn */
}

/* FUN_004b4070 @ 0x004b4070   (est. sk_vas_panic_pmm_free_range_scap)
 * Ghidra: void FUN_004b4070(void)
 * noreturn Unexpected L4_Error: err='pmm_free_range_with(vcss->pmm,
 * range.free_scap, ncaps)' (005b767e). Shadow-space variant.
 * Confidence: high (deterministic abort). */
void sk_r42_004b4070(void)
{
    FUN_00041138();
    FUN_00044790();
    sk_r42_004b3a58(0);
    FUN_0004480c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b767e);  /* noreturn */
}

/* FUN_004b3b08 @ 0x004b3b08   (est. sk_vas_panic_cap_move_shadow)
 * Ghidra: void FUN_004b3b08(void)
 * noreturn Unexpected L4_Error: err='L4_Cap_Move(slot, shadow_slot)'
 * (005b700b). Shadow-space variant.
 * Confidence: high (deterministic abort). */
void sk_r42_004b3b08(void)
{
    FUN_00041138();
    FUN_00044790();
    sk_r42_004b3a58(0);
    FUN_0004480c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b700b);  /* noreturn */
}

/* FUN_004b3b64 @ 0x004b3b64   (est. sk_vas_panic_shadow_err)
 * Ghidra: void FUN_004b3b64(void)
 * noreturn Unexpected L4_Error: err='err' (005b010f). Shadow-space variant.
 * Confidence: high (deterministic abort). */
void sk_r42_004b3b64(void)
{
    FUN_00041138();
    FUN_00044790();
    sk_r42_004b3a58(0);
    FUN_0004480c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b010f);  /* noreturn */
}

/* FUN_004b3c74 @ 0x004b3c74   (est. sk_vas_panic_shadow_err2)
 * Ghidra: void FUN_004b3c74(void)
 * noreturn Unexpected L4_Error: err='err' (005b010f). Shadow-space variant
 * (duplicate of 004b3b64).
 * Confidence: high (deterministic abort). */
void sk_r42_004b3c74(void)
{
    FUN_00041138();
    FUN_00044790();
    sk_r42_004b3a58(0);
    FUN_0004480c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b010f);  /* noreturn */
}

/* FUN_004b3d54 @ 0x004b3d54   (est. sk_vas_panic_shadow_tail)
 * Ghidra: void FUN_004b3d54(void)
 * noreturn Unexpected L4_Error tail for the shadow space: uses the
 * err-log helper (FUN_000447b0) and noreturn-tails via FUN_00044818.
 * Confidence: high (deterministic abort). */
void sk_r42_004b3d54(void)
{
    FUN_00041138();
    FUN_00044790();
    FUN_000447b0();
    FUN_0004480c();
    FUN_00044818();  /* noreturn */
}

/* pc-arg panic variants (each passes its return address to a noop first): */
/* FUN_004b2c3c @ 0x004b2c3c (est. sk_vas_panic_map_rotmpcap)
 * noreturn Unexpected L4_Error err='_map_this_frame(span, address,
 * fault->rotmpcap)' (005b588b); pc-arg noop FUN_000411c0(0x4b2c58).
 * Confidence: high. */
void sk_r42_004b2c3c(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_000411c0(0x4b2c58);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b588b);  /* noreturn */
}

/* FUN_004b35f4 @ 0x004b35f4 (est. sk_vas_panic_map_readonly)
 * noreturn Unexpected L4_Error err='_map_this_frame_readonly(span,
 * address, fault->rotmpcap)' (005b5b07); pc-arg noop FUN_00041110(0x4b3610).
 * Confidence: high. */
void sk_r42_004b35f4(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_00041110(0x4b3610);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b5b07);  /* noreturn */
}

/* FUN_004b36c8 @ 0x004b36c8 (est. sk_vas_panic_unmap_dest)
 * noreturn Unexpected L4_Error err='L4_Arm64_PageFrame_Unmap(dest_cap)'
 * (005b59b2); pc-arg noop FUN_0004114c(0x4b36e4).
 * Confidence: high. */
void sk_r42_004b36c8(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_0004114c(0x4b36e4);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b59b2);  /* noreturn */
}

/* FUN_004b3718 @ 0x004b3718 (est. sk_vas_panic_cap_move_dest)
 * noreturn Unexpected L4_Error err='L4_Cap_Move(dest_cap,
 * fault->rotmpcap)' (005b5a20); pc-arg noop FUN_0004114c(0x4b3734).
 * Confidence: high. */
void sk_r42_004b3718(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_0004114c(0x4b3734);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b5a20);  /* noreturn */
}

/* FUN_004b37b8 @ 0x004b37b8 (est. sk_vas_panic_pmm_alloc_temp2)
 * noreturn Unexpected L4_Error err='pmm_alloc_temp_with(...)' (005b5b81);
 * pc-arg noop FUN_0004114c(0x4b37d4).
 * Confidence: high. */
void sk_r42_004b37b8(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_0004114c(0x4b37d4);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b5b81);  /* noreturn */
}

/* FUN_004b3808 @ 0x004b3808 (est. sk_vas_panic_map_this_frame_ro)
 * noreturn Unexpected L4_Error err='_map_this_frame(fault->write_span,
 * ...)' (005b548e); pc-arg noop FUN_0004114c(0x4b3824).
 * Confidence: high. */
void sk_r42_004b3808(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_0004114c(0x4b3824);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b548e);  /* noreturn */
}

/* FUN_004b3858 @ 0x004b3858 (est. sk_vas_panic_cap_delete_rwtmpcap2)
 * noreturn Unexpected L4_Error err='L4_Cap_Delete(fault->rwtmpcap)'
 * (005b552b); pc-arg noop FUN_0004114c(0x4b3874).
 * Confidence: high. */
void sk_r42_004b3858(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_0004114c(0x4b3874);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b552b);  /* noreturn */
}

/* FUN_004b38a8 @ 0x004b38a8 (est. sk_vas_panic_map_readonly_ro)
 * noreturn Unexpected L4_Error err='_map_this_frame_readonly(
 * fault->read_span, ...)' (005b5c7b); pc-arg noop FUN_0004114c(0x4b38c4).
 * Confidence: high. */
void sk_r42_004b38a8(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_0004114c(0x4b38c4);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b5c7b);  /* noreturn */
}

/* FUN_004b38f8 @ 0x004b38f8 (est. sk_vas_panic_cap_delete_readspan)
 * noreturn Unexpected L4_Error err='L4_Cap_Delete(fault->read_spancap)'
 * (005b58de); pc-arg noop FUN_00041110(0x4b3914).
 * Confidence: high. */
void sk_r42_004b38f8(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_00041110(0x4b3914);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b58de);  /* noreturn */
}

/* FUN_004b3940 @ 0x004b3940 (est. sk_vas_panic_cap_delete_readspan2)
 * noreturn Unexpected L4_Error err='L4_Cap_Delete(fault->read_spancap)'
 * (005b5cf9); pc-arg noop FUN_00041110(0x4b395c).
 * Confidence: high. */
void sk_r42_004b3940(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_00041110(0x4b395c);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b5cf9);  /* noreturn */
}

/* FUN_004b3988 @ 0x004b3988 (est. sk_vas_panic_cap_delete_writespan)
 * noreturn Unexpected L4_Error err='L4_Cap_Delete(fault->write_spancap)'
 * (005b5d3f); pc-arg noop FUN_00041110(0x4b39a4).
 * Confidence: high. */
void sk_r42_004b3988(void)
{
    FUN_00041138();
    FUN_0004108c();
    FUN_00041110(0x4b39a4);
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b5d3f);  /* noreturn */
}

/* FUN_004b2d60 @ 0x004b2d60 (est. sk_vas_panic_l4err_tail)
 * Ghidra: void FUN_004b2d60(void)
 * noreturn Unexpected L4_Error: preamble + prefix, then noreturn-tail via
 * FUN_00041160.
 * Confidence: high (deterministic abort). */
void sk_r42_004b2d60(void)
{
    FUN_00041138();
    FUN_0004108c();
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_00041160();  /* noreturn */
}

/* FUN_004b2f80 @ 0x004b2f80 (est. sk_vas_panic_l4err_tail2)
 * Ghidra: void FUN_004b2f80(void)
 * noreturn Unexpected L4_Error tail (duplicate of 004b2d60).
 * Confidence: high (deterministic abort). */
void sk_r42_004b2f80(void)
{
    FUN_00041138();
    FUN_0004108c();
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_00041160();  /* noreturn */
}

/* FUN_004b3064 @ 0x004b3064 (est. sk_vas_panic_l4err_tail3)
 * Ghidra: void FUN_004b3064(void)
 * noreturn Unexpected L4_Error tail (duplicate of 004b2d60).
 * Confidence: high (deterministic abort). */
void sk_r42_004b3064(void)
{
    FUN_00041138();
    FUN_0004108c();
    sk_r42_004b2820(0);
    FUN_0004112c();
    FUN_00041160();  /* noreturn */
}

/* FUN_004b2fe0 @ 0x004b2fe0 (est. sk_vas_panic_err_stack)
 * Ghidra: void FUN_004b2fe0(undefined8 p1, undefined8 p2, undefined8 p3)
 * noreturn Unexpected L4_Error err='err' (005b010f): pushes a stack frame,
 * prints the prefix, then aborts.
 * Confidence: high (deterministic abort). */
void sk_r42_004b2fe0(word_t p1, word_t p2, word_t p3)
{
    byte stackbuf[32];
    FUN_0003f980((word_t)stackbuf);
    sk_r42_004b2820(0xeb1a02bf914012ba);
    FUN_0003f980(p3, p1);
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005b010f);  /* noreturn */
}

/* ================================================================== */
/* VAS-abort shims (noreturn; each calls FUN_004afae4 with a fixed msg) */
/* ================================================================== */

/* FUN_004b2780 @ 0x004b2780 (est. sk_vas_abort_mark_cap_recursive)
 * noreturn VAS abort: vas__mark_cap_slots_allocated() should not be
 * recursive (005b1d3f). Confidence: high. */
void sk_r42_004b2780(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] vas__mark_cap_slots_allocated() should not be recursive\n");
}

/* FUN_004b27b8 @ 0x004b27b8 (est. sk_vas_abort_alloc_addr_root)
 * noreturn VAS abort: vascore_as_alloc() must be passed an address root
 * (005b1f78). Confidence: high. */
void sk_r42_004b27b8(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] vascore_as_alloc() must be passed an address root\n");
}

/* FUN_004b27f0 @ 0x004b27f0 (est. sk_vas_abort_freezer_bump)
 * noreturn VAS abort: "Freezer bump called with invalid memory pointer"
 * (005b21f4). Confidence: high. */
void sk_r42_004b27f0(void)
{
    FUN_004afae4("Freezer bump called with invalid memory pointer\n");
}

/* FUN_004b2808 @ 0x004b2808 (est. sk_vas_abort_freezer_backing)
 * noreturn VAS abort: "Freezer tried to free a backing span that was null"
 * (005b228c). Confidence: high. */
void sk_r42_004b2808(void)
{
    FUN_004afae4("Freezer tried to free a backing span that was null\n");
}

/* FUN_004b28c0 @ 0x004b28c0 (est. sk_vas_abort_incomplete_fault)
 * noreturn VAS abort: vas_handle_fault() does not support incomplete
 * faults (005b4bab). Confidence: high. */
void sk_r42_004b28c0(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] vas_handle_fault() does not support incomplete faults\n");
}

/* FUN_004b28f8 @ 0x004b28f8 (est. sk_vas_abort_rotmpcap_slot)
 * noreturn VAS abort: Could not allocate slot for rotmpcmp (005b5111).
 * Confidence: high. */
void sk_r42_004b28f8(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Could not allocate slot for rotmpcmp\n\n");
}

/* FUN_004b2930 @ 0x004b2930 (est. sk_vas_abort_rwtmpcap_slot)
 * noreturn VAS abort: Could not allocate slot for rwtmpcap (005b509d).
 * Confidence: high. */
void sk_r42_004b2930(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Could not allocate slot for rwtmpcap\n\n");
}

/* FUN_004b2968 @ 0x004b2968 (est. sk_vas_abort_freezer_downgrade)
 * noreturn VAS abort: Failed to downgrade freezer frame to read-only
 * (005b4d0e). Confidence: high. */
void sk_r42_004b2968(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Failed to downgrade freezer frame to read-only\n");
}

/* FUN_004b2a4c @ 0x004b2a4c (est. sk_vas_abort_freezer_revoke)
 * noreturn VAS abort: Failed to revoke freezer frame (005b4d8b).
 * Confidence: high. */
void sk_r42_004b2a4c(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Failed to revoke freezer frame\n");
}

/* FUN_004b2a84 @ 0x004b2a84 (est. sk_vas_abort_other_vas_span)
 * noreturn VAS abort: This vas's fault table contains a span for another
 * vas (005b5262). Confidence: high. */
void sk_r42_004b2a84(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] This vas's fault table contains a span for another vas\n");
}

/* FUN_004b2bb8 @ 0x004b2bb8 (est. sk_vas_abort_frozen_data)
 * noreturn VAS abort: Failed to retrieve frozen data from freezer into
 * write buffer (005b556d). Confidence: high. */
void sk_r42_004b2bb8(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] Failed to retrieve frozen data from freezer into write buffer\n");
}

/* FUN_004b2be4 @ 0x004b2be4 (est. sk_vas_abort_decomp_map)
 * noreturn VAS abort: Failed to map decompressed frame into destination
 * (005b55d2). Confidence: high. */
void sk_r42_004b2be4(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] Failed to map decompressed frame into destination\n");
}

/* FUN_004b2c10 @ 0x004b2c10 (est. sk_vas_abort_decomp_cap)
 * noreturn VAS abort: Couldn't get cap for decompressed page (005b5384).
 * Confidence: high. */
void sk_r42_004b2c10(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] Couldn't get cap for decompressed page\n");
}

/* FUN_004b2da8 @ 0x004b2da8 (est. sk_vas_abort_nonfaultable)
 * noreturn VAS abort: Unexpected non-faultable span (005b52ef).
 * Confidence: high. */
void sk_r42_004b2da8(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Unexpected non-faultable span\n");
}

/* FUN_004b30ac @ 0x004b30ac (est. sk_vas_abort_merged_span_fail)
 * noreturn VAS abort: failed but has merged span (005b46f9).
 * Confidence: high. */
void sk_r42_004b30ac(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] failed but has merged span\n");
}

/* FUN_004b30e4 @ 0x004b30e4 (est. sk_vas_abort_merged_span_success)
 * noreturn VAS abort: success but nos merged span (005b476c).
 * Confidence: high. */
void sk_r42_004b30e4(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] success but nos merged span\n");
}

/* FUN_004b311c @ 0x004b311c (est. sk_vas_abort_adjacent_span)
 * noreturn VAS abort: Failed to destroy adjacent span after merge failed
 * (005b4a5a). Confidence: high. */
void sk_r42_004b311c(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Failed to destroy adjacent span after merge failed\n");
}

/* FUN_004b3154 @ 0x004b3154 (est. sk_vas_abort_destroy_split)
 * noreturn VAS abort: Failed to destroy split span (005b49d8).
 * Confidence: high. */
void sk_r42_004b3154(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Failed to destroy split span\n");
}

/* FUN_004b318c @ 0x004b318c (est. sk_vas_abort_iter_next)
 * noreturn VAS abort: _iter_next should only be NULL or an allocated span
 * (005b4ac1). Confidence: high. */
void sk_r42_004b318c(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] _iter_next should only be NULL or an allocated span\n");
}

/* FUN_004b31c4 @ 0x004b31c4 (est. sk_vas_abort_empty_op)
 * noreturn VAS abort: empty operation starts should always succeed
 * (005b2a19). Confidence: high. */
void sk_r42_004b31c4(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] empty operation starts should always succeed\n");
}

/* FUN_004b31fc @ 0x004b31fc (est. sk_vas_abort_prepop_giveup)
 * noreturn VAS abort: could not prepopulate span, giving up (005b3daf).
 * Confidence: high. */
void sk_r42_004b31fc(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] could not prepopulate span, giving up\n");
}

/* FUN_004b3234 @ 0x004b3234 (est. sk_vas_abort_missing_prepop)
 * noreturn VAS abort: missing prepopulated page table (005b2eb2).
 * Confidence: high. */
void sk_r42_004b3234(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] missing prepopulated page table\n");
}

/* FUN_004b32bc @ 0x004b32bc (est. sk_vas_abort_pt_range)
 * noreturn VAS abort: PT out of range (005b2f42). Confidence: high. */
void sk_r42_004b32bc(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] PT out of range\n");
}

/* FUN_004b32f4 @ 0x004b32f4 (est. sk_vas_abort_spanmap_changed)
 * noreturn VAS abort: spanmap changed while we were using it unlocked
 * (005b3024). Confidence: high. */
void sk_r42_004b32f4(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] spanmap changed while we were using it unlocked\n");
}

/* FUN_004b332c @ 0x004b332c (est. sk_vas_abort_prepop_missing)
 * noreturn VAS abort: prepopulated page table missing (005b2fc3).
 * Confidence: high. */
void sk_r42_004b332c(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] prepopulated page table missing\n");
}

/* FUN_004b3364 @ 0x004b3364 (est. sk_vas_abort_span_mutated)
 * noreturn VAS abort: span map mutated on a no-alloc path (005b311f).
 * Confidence: high. */
void sk_r42_004b3364(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] span map mutated on a no-alloc path\n");
}

/* FUN_004b3464 @ 0x004b3464 (est. sk_vas_abort_cap_exists)
 * noreturn VAS abort: cap should already exist! (005b3372).
 * Confidence: high. */
void sk_r42_004b3464(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] cap should already exist!\n");
}

/* FUN_004b349c @ 0x004b349c (est. sk_vas_abort_span_pinned)
 * noreturn VAS abort: span should be pinned (005b31c2). Confidence: high. */
void sk_r42_004b349c(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] span should be pinned\n");
}

/* FUN_004b34d4 @ 0x004b34d4 (est. sk_vas_abort_empty)
 * noreturn VAS abort: empty message (005b3b4d). Confidence: high. */
void sk_r42_004b34d4(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] \n");
}

/* FUN_004b350c @ 0x004b350c (est. sk_vas_abort_prepop_meta)
 * noreturn VAS abort: Prepopulated metadata was not prepopulated!!
 * (005b42c1). Confidence: high. */
void sk_r42_004b350c(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] Prepopulated metadata was not prepopulated!!\n");
}

/* FUN_004b39d0 @ 0x004b39d0 (est. sk_vas_abort_rwtmpcap_missing)
 * noreturn VAS abort: Fault handler missing rwtmpcap slot (005b5935).
 * Confidence: high. */
void sk_r42_004b39d0(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Fault handler missing rwtmpcap slot\n");
}

/* FUN_004b3ac8 @ 0x004b3ac8 (est. sk_vas_abort_dart_init)
 * noreturn VAS abort: vas_core_dart_init() failed (005b6211).
 * Confidence: high. */
void sk_r42_004b3ac8(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] vas_core_dart_init() failed\n");
}

/* FUN_004b3bf8 @ 0x004b3bf8 (est. sk_vas_abort_dart_init2)
 * noreturn VAS abort: vas_core_dart_init() failed (005b6211) - duplicate
 * of 004b3ac8. Confidence: high. */
void sk_r42_004b3bf8(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] vas_core_dart_init() failed\n");
}

/* FUN_004b3bc0 @ 0x004b3bc0 (est. sk_vas_abort_dart_not_init)
 * noreturn VAS abort: vas_core_dart_init has not been called (005b6c5a).
 * Confidence: high. */
void sk_r42_004b3bc0(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] vas_core_dart_init has not been called\n");
}

/* FUN_004b3eec @ 0x004b3eec (est. sk_vas_abort_stack)
 * noreturn VAS abort: xrt_curthread_ensure_stack() failed (005b6a43).
 * Confidence: high. */
void sk_r42_004b3eec(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] xrt_curthread_ensure_stack() failed\n");
}

/* FUN_004b4000 @ 0x004b4000 (est. sk_vas_abort_hold_reserve)
 * noreturn VAS abort: Should not hold reserve (005b6b90).
 * Confidence: high. */
void sk_r42_004b4000(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Should not hold reserve\n");
}

/* FUN_004b4038 @ 0x004b4038 (est. sk_vas_abort_shadow_slot_move)
 * noreturn VAS abort: _shadow_slot_range() cannot be called with moves
 * active (005b7977). Confidence: high. */
void sk_r42_004b4038(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] _shadow_slot_range() cannot be called with moves active\n");
}

/* FUN_004b40cc @ 0x004b40cc (est. sk_vas_abort_ranges_empty)
 * noreturn VAS abort: ranges must not be empty (005b8197).
 * Confidence: high. */
void sk_r42_004b40cc(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] ranges must not be empty\n");
}

/* FUN_004b4104 @ 0x004b4104 (est. sk_vas_abort_rounded_len)
 * noreturn VAS abort: rounded up len must be non-zero (005b7c2e).
 * Confidence: high. */
void sk_r42_004b4104(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] rounded up len must be non-zero\n");
}

/* FUN_004b413c @ 0x004b413c (est. sk_vas_abort_rangelock)
 * noreturn VAS abort: rangelock already active (005b82d4).
 * Confidence: high. */
void sk_r42_004b413c(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] rangelock already active\n");
}

/* FUN_004b4174 @ 0x004b4174 (est. sk_vas_abort_prealloc_fault)
 * noreturn VAS abort: unable to preallocate fault resources (005b7d95).
 * Confidence: high. */
void sk_r42_004b4174(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] unable to preallocate fault resources\n");
}

/* FUN_004b41ac @ 0x004b41ac (est. sk_vas_abort_fault_entries)
 * noreturn VAS abort: failed to allocate fault entries (005b7e47).
 * Confidence: high. */
void sk_r42_004b41ac(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] failed to allocate fault entries\n");
}

/* FUN_004b41e4 @ 0x004b41e4 (est. sk_vas_abort_split_span)
 * noreturn VAS abort: must split span into two pieces (005b8006).
 * Confidence: high. */
void sk_r42_004b41e4(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: %llx %s %llx]must split span into two pieces\n");
}

/* FUN_004b4220 @ 0x004b4220 (est. sk_vas_abort_outside_span)
 * noreturn VAS abort: address outside of fault table entry's span
 * (005b84d5). Confidence: high. */
void sk_r42_004b4220(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] address outside of fault table entry's span\n\n");
}

/* FUN_004b424c @ 0x004b424c (est. sk_vas_abort_faulthandle_corrupt)
 * noreturn VAS abort: Corrupted state of faulthandle(must not be active)
 * (005b807c). Confidence: high. */
void sk_r42_004b424c(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] Corrupted state of faulthandle(must not be active)\n\n");
}

/* FUN_004b4284 @ 0x004b4284 (est. sk_vas_abort_fault_done_inactive)
 * noreturn VAS abort: fault_done called on inactive faulthandler
 * (005b810e). Confidence: high. */
void sk_r42_004b4284(void)
{
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] fault_done called on inactive faulthandler\n");
}

/* ================================================================== */
/* Function-name abort shims (noreturn; each calls a reporter with the  */
/* enclosing function name)                                            */
/* ================================================================== */

/* FUN_004b2898 @ 0x004b2898 (est. sk_vas_abort_handle_fault)
 * noreturn abort for the _handle_fault site via FUN_000411ac.
 * Confidence: high. */
void sk_r42_004b2898(void)
{
    FUN_000411ac(s__handle_fault_005b4c15);  /* noreturn */
}

/* FUN_004b2d10 @ 0x004b2d10 (est. sk_vas_abort_startfault_managed)
 * noreturn abort for the _startfault_impl_managed site via FUN_00041184.
 * Confidence: high. */
void sk_r42_004b2d10(void)
{
    FUN_00041184(s__startfault_impl_managed_005b5697);  /* noreturn */
}

/* FUN_004b2d38 @ 0x004b2d38 (est. sk_vas_abort_startfault_managed2)
 * noreturn abort for the _startfault_impl_managed site via FUN_00041198.
 * Confidence: high. */
void sk_r42_004b2d38(void)
{
    FUN_00041198(s__startfault_impl_managed_005b5697);  /* noreturn */
}

/* FUN_004b2f58 @ 0x004b2f58 (est. sk_vas_abort_faulthandler_destroy)
 * noreturn abort for the _faulthandler_destroy site via FUN_000411ac.
 * Confidence: high. */
void sk_r42_004b2f58(void)
{
    FUN_000411ac(s__faulthandler_destroy_005b5f9f);  /* noreturn */
}

/* FUN_004b3a08 @ 0x004b3a08 (est. sk_vas_abort_startfault_cow)
 * noreturn abort for the _startfault_impl_cow site via FUN_00041184.
 * Confidence: high. */
void sk_r42_004b3a08(void)
{
    FUN_00041184(s__startfault_impl_cow_005b5920);  /* noreturn */
}

/* FUN_004b3a30 @ 0x004b3a30 (est. sk_vas_abort_startfault_cow2)
 * noreturn abort for the _startfault_impl_cow site via FUN_00041198.
 * Confidence: high. */
void sk_r42_004b3a30(void)
{
    FUN_00041198(s__startfault_impl_cow_005b5920);  /* noreturn */
}

/* FUN_004b326c @ 0x004b326c (est. sk_vas_abort_span_asan)
 * noreturn abort for the _span_asan_usable site via FUN_00041170.
 * Confidence: high. */
void sk_r42_004b326c(void)
{
    FUN_00041170(s__span_asan_usable_005b6017);  /* noreturn */
}

/* FUN_004b3294 @ 0x004b3294 (est. sk_vas_abort_span_asan2)
 * noreturn abort for the _span_asan_usable site via FUN_00041170 (dup).
 * Confidence: high. */
void sk_r42_004b3294(void)
{
    FUN_00041170(s__span_asan_usable_005b6017);  /* noreturn */
}

/* FUN_004b339c @ 0x004b339c (est. sk_vas_abort_span_holder_cap)
 * noreturn abort for the vascore__span_holder_get_cap site via
 * FUN_000410e4. Confidence: high. */
void sk_r42_004b339c(void)
{
    FUN_000410e4(s_vascore__span_holder_get_cap_005b320c);  /* noreturn */
}

/* FUN_004b33c4 @ 0x004b33c4 (est. sk_vas_abort_span_holder_cap2)
 * noreturn abort (dup of 004b339c). Confidence: high. */
void sk_r42_004b33c4(void)
{
    FUN_000410e4(s_vascore__span_holder_get_cap_005b320c);  /* noreturn */
}

/* FUN_004b33ec @ 0x004b33ec (est. sk_vas_abort_span_holder_cap3)
 * noreturn abort (dup of 004b339c). Confidence: high. */
void sk_r42_004b33ec(void)
{
    FUN_000410e4(s_vascore__span_holder_get_cap_005b320c);  /* noreturn */
}

/* FUN_004b3414 @ 0x004b3414 (est. sk_vas_abort_span_holder_cap4)
 * noreturn abort (dup of 004b339c). Confidence: high. */
void sk_r42_004b3414(void)
{
    FUN_000410e4(s_vascore__span_holder_get_cap_005b320c);  /* noreturn */
}

/* FUN_004b343c @ 0x004b343c (est. sk_vas_abort_span_holder_cap5)
 * noreturn abort (dup of 004b339c). Confidence: high. */
void sk_r42_004b343c(void)
{
    FUN_000410e4(s_vascore__span_holder_get_cap_005b320c);  /* noreturn */
}

/* FUN_004b3c24 @ 0x004b3c24 (est. sk_vas_abort_shadow_setup)
 * noreturn abort for the vas_core_shadow_space_setup site via
 * FUN_00044828. Confidence: high. */
void sk_r42_004b3c24(void)
{
    FUN_00044828(s_vas_core_shadow_space_setup_005b6466);  /* noreturn */
}

/* FUN_004b3c4c @ 0x004b3c4c (est. sk_vas_abort_shadow_setup2)
 * noreturn abort (dup of 004b3c24). Confidence: high. */
void sk_r42_004b3c4c(void)
{
    FUN_00044828(s_vas_core_shadow_space_setup_005b6466);  /* noreturn */
}

/* FUN_004b3d2c @ 0x004b3d2c (est. sk_vas_abort_shadow_cap)
 * noreturn abort for the vas_core_shadow_space_cap site via FUN_000447f8.
 * Confidence: high. */
void sk_r42_004b3d2c(void)
{
    FUN_000447f8(s_vas_core_shadow_space_cap_005b6888);  /* noreturn */
}

/* FUN_004b3d7c @ 0x004b3d7c (est. sk_vas_abort_shadow_populate)
 * noreturn abort for the vas_core_shadow_space_populate site via
 * FUN_000447f8. Confidence: high. */
void sk_r42_004b3d7c(void)
{
    FUN_000447f8(s_vas_core_shadow_space_populate_005b691c);  /* noreturn */
}

/* FUN_004b3ec4 @ 0x004b3ec4 (est. sk_vas_abort_shadow_populate_table)
 * noreturn abort for the vas_core_shadow_space_populate_table site via
 * FUN_000447f8. Confidence: high. */
void sk_r42_004b3ec4(void)
{
    FUN_000447f8(s_vas_core_shadow_space_populate_t_005b693b);  /* noreturn */
}

/* FUN_004b3e30 @ 0x004b3e30 (est. sk_vas_abort_temp_cap)
 * noreturn abort for the _alloc_temp_cap site via FUN_0004483c.
 * Confidence: high. */
void sk_r42_004b3e30(void)
{
    FUN_0004483c(s__alloc_temp_cap_005b734b);  /* noreturn */
}

/* FUN_004b3f78 @ 0x004b3f78 (est. sk_vas_abort_heap_cap)
 * noreturn abort for the alloc_heap_cap site via FUN_0004483c.
 * Confidence: high. */
void sk_r42_004b3f78(void)
{
    FUN_0004483c(s_alloc_heap_cap_005b6b14);  /* noreturn */
}

/* FUN_004b3af4 @ 0x004b3af4 (est. sk_vas_abort_mapped_level)
 * Ghidra: void FUN_004b3af4(void)
 * noreturn abort via FUN_000447dc (mapped-level abort, no message arg).
 * Confidence: high. */
void sk_r42_004b3af4(void)
{
    FUN_000447dc();  /* noreturn */
}

/* FUN_004b2fc8 @ 0x004b2fc8 (est. sk_vas_abort_spanmap_cap)
 * noreturn VAS abort: "spanmap get cap had unexpected internal error"
 * (005b2e84). Confidence: high. */
void sk_r42_004b2fc8(void)
{
    FUN_004afae4("spanmap get cap had unexpected internal error");
}

/* FUN_004b29a0 @ 0x004b29a0 (est. sk_vas_abort_freezer_tmp_map)
 * Ghidra: void FUN_004b29a0(undefined8 p1, undefined8 p2)
 * Prints the err-name, then noreturn-aborts with "freezer temp buffer map
 * failed" (005b4df7). Confidence: high. */
void sk_r42_004b29a0(word_t p1, word_t p2)
{
    FUN_0003f980(p1, p2);
    FUN_004afae4("[VAS abort in function %s at line %d] [true: (%s)] freezer temp buffer map failed%s(%zu)\n");
}

/* ================================================================== */
/* EASM_C.c fatal shims (noreturn; SoftwareBreakpoint fail-closed)     */
/* ================================================================== */

/* FUN_004b42bc @ 0x004b42bc (est. sk_easm_fatal_42bc)
 * noreturn EASM fatal: reports via FUN_0004b488("EASM_C.c") then traps at
 * 0x4b42e0. Confidence: high. */
void sk_r42_004b42bc(void)
{
    FUN_0004b488("EASM_C.c");  /* noreturn */
    CL4_SWBP(0x4b42e0);
}

/* FUN_004b42e0 @ 0x004b42e0 (est. sk_easm_fatal_42e0)
 * noreturn EASM fatal: reports via FUN_0004b478("EASM_C.c") then traps at
 * 0x4b4304. Confidence: high. */
void sk_r42_004b42e0(void)
{
    FUN_0004b478("EASM_C.c");  /* noreturn */
    CL4_SWBP(0x4b4304);
}

/* FUN_004b4304 @ 0x004b4304 (est. sk_easm_fatal_4304)
 * noreturn EASM fatal: reports via FUN_00118b28(DAT_005ba280) then traps
 * at 0x4b4334. Confidence: high. */
void sk_r42_004b4304(void)
{
    FUN_00118b28(DAT_005ba280);  /* noreturn */
    CL4_SWBP(0x4b4334);
}

/* FUN_004b4334 @ 0x004b4334 (est. sk_easm_fatal_4334)
 * noreturn EASM fatal: reports via FUN_0004b488("EASM_C.c") then traps at
 * 0x4b4358. Confidence: high. */
void sk_r42_004b4334(void)
{
    FUN_0004b488("EASM_C.c");  /* noreturn */
    CL4_SWBP(0x4b4358);
}

/* FUN_004b4358 @ 0x004b4358 (est. sk_easm_fatal_4358)
 * noreturn EASM fatal: reports via FUN_0004b478("EASM_C.c") then traps at
 * 0x4b437c. Confidence: high. */
void sk_r42_004b4358(void)
{
    FUN_0004b478("EASM_C.c");  /* noreturn */
    CL4_SWBP(0x4b437c);
}

/* FUN_004b437c @ 0x004b437c (est. sk_easm_fatal_437c)
 * noreturn EASM fatal: reports via FUN_00118b28(DAT_005ba1b9) then traps
 * at 0x4b43ac. Confidence: high. */
void sk_r42_004b437c(void)
{
    FUN_00118b28(DAT_005ba1b9);  /* noreturn */
    CL4_SWBP(0x4b43ac);
}

/* FUN_004b43ac @ 0x004b43ac (est. sk_easm_fatal_43ac)
 * noreturn EASM fatal: reports via FUN_0004b488("EASM_C.c") then traps at
 * 0x4b43d0. Confidence: high. */
void sk_r42_004b43ac(void)
{
    FUN_0004b488("EASM_C.c");  /* noreturn */
    CL4_SWBP(0x4b43d0);
}

/* FUN_004b43d0 @ 0x004b43d0 (est. sk_easm_fatal_43d0)
 * noreturn EASM fatal: reports via FUN_0004b478("EASM_C.c") then traps at
 * 0x4b43f4. Confidence: high. */
void sk_r42_004b43d0(void)
{
    FUN_0004b478("EASM_C.c");  /* noreturn */
    CL4_SWBP(0x4b43f4);
}

/* FUN_004b43f4 @ 0x004b43f4 (est. sk_easm_fatal_43f4)
 * noreturn EASM fatal: reports via FUN_00118b28(DAT_005ba0fb) then traps
 * at 0x4b4424. Confidence: high. */
void sk_r42_004b43f4(void)
{
    FUN_00118b28(DAT_005ba0fb);  /* noreturn */
    CL4_SWBP(0x4b4424);
}
