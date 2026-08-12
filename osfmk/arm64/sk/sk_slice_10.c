/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 10: 0x55454-0x5ac2c — the syscall/service-interface dispatch layer.
 *
 * This region implements the cL4 syscall-class dispatch machinery:
 *   - a lazily-initialised singleton "service table" object (global 0x6b04b0)
 *     looked up in a per-thread registry (FUN_0005baac) of registered objects
 *     keyed by two ints;
 *   - a family of virtual-dispatch thunks (FUN_000549ac() + vtable offset) that
 *     forward calls and field reads onto the singleton's method table;
 *   - per-class descriptor builders that fill a syscall-class descriptor table
 *     (id, version fields 0x1601/0x1701, method pointers, two data tables,
 *     a dispatch code pointer) for class ids 1, 2, 0x100000001..0x900000001;
 *   - SVC-0 entry wrappers that marshal arguments into the per-thread
 *     tpidrro_el0 syscall buffer, set a syscall selector in w1, issue `svc 0`,
 *     and retry while the kernel returns 1;
 *   - runflags / sec_transition capability-gate helpers (FUN_0005ab94,
 *     FUN_0005ac2c).
 * All names are estimates unless string/header matched; most are structural.
 * The class name string is "Redacted" (Apple strips service identifiers). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

#define CL4_FATAL() __builtin_trap()

/* ================================================================== *
 * Shared kernel dependencies (declared extern; bodies owned by other
 * range workers — out of slice).
 * ================================================================== */

/* FUN_000549ac: return the singleton service-table object at global
 * 0x6b04b0, lazily populating it via the per-thread object registry. */
extern word_t FUN_000549ac(void);
/* FUN_0005acac(ptr, a, b): if *ptr==0, look up the registered object keyed
 * by (a,b) in the per-thread registry and cache it at *ptr. */
extern word_t FUN_0005acac(word_t *ptr, int a, int b);
/* FUN_0005baac(a, b): walk the per-thread registry linked list and return
 * the registered object whose keys match (a,b). */
extern word_t FUN_0005baac(int a, int b);
/* FUN_0006562c(name, &val): symbol/name lookup helper (string -> value). */
extern long FUN_0006562c(const char *name, word_t *val);
/* FUN_00060524: read tpidr_el0+8 (per-thread current field). */
extern word_t FUN_00060524(void);
/* FUN_0005b190(msg, arg): noreturn fatal/panic with message. */
extern void FUN_0005b190(word_t msg, word_t arg);
/* FUN_00054610: singleton table variant getter (global 0x6b04a8). */
extern word_t FUN_00054610(void);
/* FUN_00053568(sel): boot/runflag gate check (tail-called with selector). */
extern word_t FUN_00053568(word_t sel);
/* FUN_0005ab94: xrt runflags capability check (in-slice, below). */
/* thunk_FUN_00114e50: string/byte compare (sym vs DAT_005cf0f4). */
extern word_t thunk_FUN_00114e50(word_t sym, void *cmp, word_t val);
extern unsigned char _DAT_005cf0f4[];   /* comparison data for sec_transition */

/* The singleton method table: methods live at byte offsets 0x60..0x1a0,
 * data tables at 0x180/0x188 (length byte at 0x178), scalar fields at
 * 0xd0/0xf1/0x14a/0x1b0/0x1b8. Modelled as a word_t-typed table so the
 * dispatch thunks can forward at the exact offsets Ghidra shows. */


/* FUN_00055454 @ 0x00055454  (est. sk_svc_dispatch_60)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x60 (slot 12), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_60(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0x60))(a1);
}

/* FUN_00055488 @ 0x00055488  (est. sk_svc_dispatch_68)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x68 (slot 13), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_68(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0x68))(a1);
}

/* FUN_000554bc @ 0x000554bc  (est. sk_svc_dispatch_70)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x70 (slot 14), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_70(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0x70))(a1);
}

/* FUN_000554f0 @ 0x000554f0  (est. sk_svc_dispatch_78)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x78 (slot 15), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_78(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0x78))(a1);
}

/* FUN_00055524 @ 0x00055524  (est. sk_svc_dispatch_80)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x80 (slot 16), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_80(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0x80))(a1);
}

/* FUN_00055558 @ 0x00055558  (est. sk_svc_dispatch_88)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x88 (slot 17), passing
 * through 4 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_88(word_t a1, word_t a2, word_t a3, word_t a4)
{
    (*(word_t (**)(word_t a1, word_t a2, word_t a3, word_t a4))(FUN_000549ac() + 0x88))(a1, a2, a3, a4);
}

/* FUN_000555ac @ 0x000555ac  (est. sk_svc_dispatch_90)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x90 (slot 18), passing
 * through 3 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_90(word_t a1, word_t a2, word_t a3)
{
    (*(word_t (**)(word_t a1, word_t a2, word_t a3))(FUN_000549ac() + 0x90))(a1, a2, a3);
}

/* FUN_000555f8 @ 0x000555f8  (est. sk_svc_dispatch_98)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x98 (slot 19), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_98(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0x98))(a1);
}

/* FUN_0005562c @ 0x0005562c  (est. sk_svc_dispatch_b0)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0xb0 (slot 22), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_b0(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0xb0))(a1);
}

/* FUN_00055660 @ 0x00055660  (est. sk_svc_dispatch_b8)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0xb8 (slot 23), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_b8(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0xb8))(a1);
}

/* FUN_00055694 @ 0x00055694  (est. sk_svc_dispatch_c0)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0xc0 (slot 24), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_c0(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0xc0))(a1);
}

/* FUN_000556c8 @ 0x000556c8  (est. sk_svc_get_d0)
 * Read the 8-bit scalar field at method-table offset 0xd0 of the
 * singleton service table.
 * Confidence: high (structural) */
static word_t sk_svc_get_d0(void)
{
    return *(word_t *)(FUN_000549ac() + 0xd0);
}

/* FUN_000556e4 @ 0x000556e4  (est. sk_svc_dispatch_d8)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0xd8 (slot 27), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_d8(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0xd8))(a1);
}

/* FUN_00055718 @ 0x00055718  (est. sk_svc_dispatch_e0)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0xe0 (slot 28), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_e0(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0xe0))(a1);
}

/* FUN_0005574c @ 0x0005574c  (est. sk_svc_dispatch_e8)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0xe8 (slot 29), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_e8(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0xe8))(a1);
}

/* FUN_00055780 @ 0x00055780  (est. sk_svc_get_f1)
 * Read the 8-bit scalar field at method-table offset 0xf1 of the
 * singleton service table.
 * Confidence: high (structural) */
static unsigned char sk_svc_get_f1(void)
{
    return *(unsigned char *)(FUN_000549ac() + 0xf1);
}

/* FUN_0005579c @ 0x0005579c  (est. sk_svc_dispatch_f8)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0xf8 (slot 31), passing
 * through 3 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_f8(word_t a1, word_t a2, word_t a3)
{
    (*(word_t (**)(word_t a1, word_t a2, word_t a3))(FUN_000549ac() + 0xf8))(a1, a2, a3);
}

/* FUN_000557e8 @ 0x000557e8  (est. sk_svc_dispatch_100)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x100 (slot 32), passing
 * through 2 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_100(word_t a1, word_t a2)
{
    (*(word_t (**)(word_t a1, word_t a2))(FUN_000549ac() + 0x100))(a1, a2);
}

/* FUN_00055824 @ 0x00055824  (est. sk_svc_dispatch_108)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x108 (slot 33), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_108(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0x108))(a1);
}

/* FUN_00055858 @ 0x00055858  (est. sk_svc_get_14a)
 * Read the 8-bit scalar field at method-table offset 0x14a of the
 * singleton service table.
 * Confidence: high (structural) */
static unsigned char sk_svc_get_14a(void)
{
    return *(unsigned char *)(FUN_000549ac() + 0x14a);
}

/* FUN_00055874 @ 0x00055874  (est. sk_svc_dispatch_150)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x150 (slot 42), passing
 * through 3 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_150(word_t a1, word_t a2, word_t a3)
{
    (*(word_t (**)(word_t a1, word_t a2, word_t a3))(FUN_000549ac() + 0x150))(a1, a2, a3);
}

/* FUN_000558c0 @ 0x000558c0  (est. sk_svc_dispatch_158)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x158 (slot 43), passing
 * through 3 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_158(word_t a1, word_t a2, word_t a3)
{
    (*(word_t (**)(word_t a1, word_t a2, word_t a3))(FUN_000549ac() + 0x158))(a1, a2, a3);
}

/* FUN_0005590c @ 0x0005590c  (est. sk_svc_dispatch_160)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x160 (slot 44), passing
 * through 2 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_160(word_t a1, word_t a2)
{
    (*(word_t (**)(word_t a1, word_t a2))(FUN_000549ac() + 0x160))(a1, a2);
}

/* FUN_00055948 @ 0x00055948  (est. sk_svc_dispatch_168)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x168 (slot 45), passing
 * through 1 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_168(word_t a1)
{
    (*(word_t (**)(word_t a1))(FUN_000549ac() + 0x168))(a1);
}

/* FUN_0005597c @ 0x0005597c  (est. sk_svc_dispatch_170)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x170 (slot 46), passing
 * through 2 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_170(word_t a1, word_t a2)
{
    (*(word_t (**)(word_t a1, word_t a2))(FUN_000549ac() + 0x170))(a1, a2);
}

/* FUN_000559b8 @ 0x000559b8  (est. sk_svc_table_get_180)
 * Indexed getter into one of the singleton's two method-name/data tables
 * (base pointer at offset 0x180, element count byte at 0x178). Returns
 * table[index] as a word, or 0 if the index is negative or past the count.
 * The pointer-overflow / range check is guarded by Software Breakpoint
 * 0x5519 (decompiler artifact kept faithfully).
 * Confidence: high (structural) */
static word_t sk_svc_table_get_180(unsigned int param_1)
{
    word_t base;
    word_t tab;
    word_t *entry;
    if ((int)param_1 < 0 || *(unsigned char *)(FUN_000549ac() + 0x178) <= param_1)
        return 0;
    base = FUN_000549ac();
    tab = *(word_t *)(base + 0x180);
    entry = (word_t *)tab + param_1;
    if ((word_t)entry < tab ||
        tab + *(unsigned char *)(base + 0x178) < (word_t)(entry + 1) ||
        (word_t)(entry + 1) < (word_t)entry)
        CL4_FATAL();   /* Software Breakpoint 0x5519 */
    return *entry;
}

/* FUN_00055a24 @ 0x00055a24  (est. sk_svc_table_get_188)
 * Indexed getter into one of the singleton's two method-name/data tables
 * (base pointer at offset 0x188, element count byte at 0x178). Returns
 * table[index] as a word, or 0 if the index is negative or past the count.
 * The pointer-overflow / range check is guarded by Software Breakpoint
 * 0x5519 (decompiler artifact kept faithfully).
 * Confidence: high (structural) */
static word_t sk_svc_table_get_188(unsigned int param_1)
{
    word_t base;
    word_t tab;
    word_t *entry;
    if ((int)param_1 < 0 || *(unsigned char *)(FUN_000549ac() + 0x178) <= param_1)
        return 0;
    base = FUN_000549ac();
    tab = *(word_t *)(base + 0x188);
    entry = (word_t *)tab + param_1;
    if ((word_t)entry < tab ||
        tab + *(unsigned char *)(base + 0x178) < (word_t)(entry + 1) ||
        (word_t)(entry + 1) < (word_t)entry)
        CL4_FATAL();   /* Software Breakpoint 0x5519 */
    return *entry;
}

/* FUN_00055a90 @ 0x00055a90  (est. sk_svc_table_get_190)
 * Indexed getter into one of the singleton's two method-name/data tables
 * (base pointer at offset 0x190, element count byte at 0x178). Returns
 * table[index] as a word, or 0 if the index is negative or past the count.
 * The pointer-overflow / range check is guarded by Software Breakpoint
 * 0x5519 (decompiler artifact kept faithfully).
 * Confidence: high (structural) */
static word_t sk_svc_table_get_190(unsigned int param_1)
{
    word_t base;
    word_t tab;
    word_t *entry;
    if ((int)param_1 < 0 || *(unsigned char *)(FUN_000549ac() + 0x178) <= param_1)
        return 0;
    base = FUN_000549ac();
    tab = *(word_t *)(base + 0x190);
    entry = (word_t *)tab + param_1;
    if ((word_t)entry < tab ||
        tab + *(unsigned char *)(base + 0x178) < (word_t)(entry + 1) ||
        (word_t)(entry + 1) < (word_t)entry)
        CL4_FATAL();   /* Software Breakpoint 0x5519 */
    return *entry;
}

/* FUN_00055afc @ 0x00055afc  (est. sk_svc_dispatch_198)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x198 (slot 51), passing
 * through 0 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_198()
{
    (*(word_t (**)())(FUN_000549ac() + 0x198))();
}

/* FUN_00055b20 @ 0x00055b20  (est. sk_svc_dispatch_1a0)
 * Virtual-dispatch thunk: forward the call through the singleton service
 * table's method pointer at byte offset 0x1a0 (slot 52), passing
 * through 0 argument(s) unchanged.
 * Confidence: high (structural) */
static void sk_svc_dispatch_1a0()
{
    (*(word_t (**)())(FUN_000549ac() + 0x1a0))();
}

/* FUN_00055b44 @ 0x00055b44  (est. sk_svc_get_1b0)
 * Read the 8-bit scalar field at method-table offset 0x1b0 of the
 * singleton service table.
 * Confidence: high (structural) */
static word_t sk_svc_get_1b0(void)
{
    return *(word_t *)(FUN_000549ac() + 0x1b0);
}

/* FUN_00055b60 @ 0x00055b60  (est. sk_svc_get_1b8)
 * Read the 8-bit scalar field at method-table offset 0x1b8 of the
 * singleton service table.
 * Confidence: high (structural) */
static unsigned char sk_svc_get_1b8(void)
{
    return *(unsigned char *)(FUN_000549ac() + 0x1b8);
}
/* ================================================================== *
 * SVC-0 syscall entry wrappers.
 *
 * Each wrapper issues `svc 0` (the cL4 syscall trap) with a selector
 * placed in w1. Arguments beyond the first are marshalled into the
 * per-thread tpidrro_el0 syscall buffer (offsets 0, 8, 0x10) before the
 * trap and the first buffer slot is restored afterwards. The kernel
 * returns 1 to request a retry, so the wrapper loops while x0 == 1.
 * (Ghidra models the svc return as the incoming param_1 in the loop
 * condition; the disassembly shows `cmp x0,#1; b.eq` — the loop is on
 * the svc RETURN value, which the disasm confirms.)
 * ================================================================== */


/* FUN_00055ee0 @ 0x00055ee0  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_00056004 @ 0x00056004  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056034 @ 0x00056034  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056064 @ 0x00056064  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000565c4 @ 0x000565c4  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_000566e8 @ 0x000566e8  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056718 @ 0x00056718  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056748 @ 0x00056748  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056778 @ 0x00056778  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000567a8 @ 0x000567a8  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000567d8 @ 0x000567d8  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056d3c @ 0x00056d3c  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_00056e60 @ 0x00056e60  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056e90 @ 0x00056e90  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056ec0 @ 0x00056ec0  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056ef0 @ 0x00056ef0  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056f20 @ 0x00056f20  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00056f50 @ 0x00056f50  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000574c0 @ 0x000574c0  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_000575e4 @ 0x000575e4  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00057614 @ 0x00057614  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00057644 @ 0x00057644  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00057674 @ 0x00057674  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000576a4 @ 0x000576a4  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000576d4 @ 0x000576d4  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00057c44 @ 0x00057c44  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_00057d68 @ 0x00057d68  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00057d98 @ 0x00057d98  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00057dc8 @ 0x00057dc8  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00057df8 @ 0x00057df8  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00057e28 @ 0x00057e28  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00057e58 @ 0x00057e58  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000583c4 @ 0x000583c4  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_000584e8 @ 0x000584e8  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00058518 @ 0x00058518  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00058548 @ 0x00058548  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00058578 @ 0x00058578  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000585a8 @ 0x000585a8  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000585d8 @ 0x000585d8  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00058b44 @ 0x00058b44  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_00058c68 @ 0x00058c68  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00058c98 @ 0x00058c98  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00058cc8 @ 0x00058cc8  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00058cf8 @ 0x00058cf8  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00058d28 @ 0x00058d28  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00058d58 @ 0x00058d58  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000592c4 @ 0x000592c4  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_000593e8 @ 0x000593e8  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00059418 @ 0x00059418  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00059448 @ 0x00059448  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00059478 @ 0x00059478  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000594a8 @ 0x000594a8  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_000594d8 @ 0x000594d8  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00059a44 @ 0x00059a44  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_00059b68 @ 0x00059b68  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00059b98 @ 0x00059b98  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00059bc8 @ 0x00059bc8  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00059bf8 @ 0x00059bf8  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00059c28 @ 0x00059c28  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_00059c58 @ 0x00059c58  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005a1c4 @ 0x0005a1c4  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_0005a2e8 @ 0x0005a2e8  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005a318 @ 0x0005a318  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005a348 @ 0x0005a348  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005a378 @ 0x0005a378  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005a3a8 @ 0x0005a3a8  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005a3d8 @ 0x0005a3d8  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005a940 @ 0x0005a940  (est. sk_svc_2_marsh4)
 * Syscall wrapper (selector 2): marshals four register args — the
 * first stays in x0, the next three (param_2..param_4) are written into the
 * per-thread syscall buffer at tpidrro_el0[0..2] — issues `svc 0`, then
 * restores buffer slot 0.
 * Confidence: high (structural) */
static void sk_svc_2_marsh4(word_t param_1, word_t param_2,
                                word_t param_3, word_t param_4)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    buf[1] = param_3;
    buf[2] = param_4;
    CallSupervisor(0);   /* svc 0, selector 2 in w1 */
    buf[0] = param_2;
}

/* FUN_0005aa64 @ 0x0005aa64  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005aa94 @ 0x0005aa94  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005aac4 @ 0x0005aac4  (est. sk_svc_1_marsh1)
 * Syscall wrapper (selector 1): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005aaf4 @ 0x0005aaf4  (est. sk_svc_3_marsh1)
 * Syscall wrapper (selector 3): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_3_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 3 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005ab24 @ 0x0005ab24  (est. sk_svc_5_marsh1)
 * Syscall wrapper (selector 5): saves buffer slot 0, issues `svc 0`,
 * restores slot 0, and retries while the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_5_marsh1(word_t param_1)
{
    word_t *buf = (word_t *)tpidrro_el0;
    word_t saved = buf[0];
    do {
        CallSupervisor(0);   /* svc 0, selector 5 in w1 */
        buf[0] = saved;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}

/* FUN_0005ab54 @ 0x0005ab54  (est. sk_svc_1_marsh2)
 * Syscall wrapper (selector 1): writes param_2 into the per-thread
 * syscall buffer slot 0, issues `svc 0`, restores slot 0, and retries while
 * the kernel returns 1.
 * Confidence: high (structural) */
static void sk_svc_1_marsh2(word_t param_1, word_t param_2)
{
    word_t *buf = (word_t *)tpidrro_el0;
    buf[0] = param_2;
    do {
        CallSupervisor(0);   /* svc 0, selector 1 in w1 */
        buf[0] = param_2;
    } while (param_1 == 1);   /* retry while svc returns 1 */
}
/* ================================================================== *
 * Per-class syscall descriptor builders.
 *
 * Each builder, given a class id in param_1 and a pointer to a descriptor
 * struct in param_2, fills the descriptor when param_1 matches the class
 * id, and returns whether it matched. The descriptor carries:
 *   +0x08 id, +0x10 name (all "Redacted" — Apple strips identifiers),
 *   +0x18/+0x1c/+0x20 config, +0x28..+0x170 method pointers (either
 *     inline LAB_ stubs embedded in this builder or SVC wrappers),
 *   +0xf0/+0x149 version fields (0x1601 / 0x1701), +0x178 data-table
 *     element count, +0x180/+0x188 the two data tables, +0x190 a dispatch
 *     code pointer, +0x1a8/+0x1b0/+0x1b8 tail config.
 * ================================================================== */


/* FUN_00055b7c @ 0x00055b7c  (est. sk_svc_class_2_build)
 * Build the syscall-class descriptor for class id 2: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 2.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_2_build(word_t param_1, word_t param_2)
{
    if (param_1 == 2) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x28)) = &LAB_00055e24;
    *((word_t *)(param_2 + 0xa8)) = &LAB_00055e44;
    *((word_t *)(param_2 + 0xb0)) = &LAB_00055e4c;
    *((word_t *)(param_2 + 0xb8)) = &LAB_00055e54;
    *((word_t *)(param_2 + 0xc0)) = &LAB_00055e5c;
    *((word_t *)(param_2 + 0xd8)) = &LAB_00055e64;
    *((word_t *)(param_2 + 0xe0)) = &LAB_00055e6c;
    *((word_t *)(param_2 + 0xe8)) = &LAB_00055e74;
    *((word_t *)(param_2 + 0xf8)) = &LAB_00055e7c;
    *((word_t *)(param_2 + 0x100)) = &LAB_00055e9c;
    *((word_t *)(param_2 + 0x108)) = &LAB_00055eb8;
    *((word_t *)(param_2 + 0x110)) = &LAB_00055ed0;
    *((word_t *)(param_2 + 0x118)) = &LAB_00055ed8;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_00055f0c;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_00055f28;
    *((word_t *)(param_2 + 0x158)) = &LAB_00055f48;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_00055f68;
    *((word_t *)(param_2 + 0x170)) = &LAB_00055fb0;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bcd10  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bcdd8  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_00055ff0;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_00055ff8;
    }
    return param_1 == 2;
}

/* FUN_00056098 @ 0x00056098  (est. sk_svc_class_1_build)
 * Build the syscall-class descriptor for class id 1: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 1.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_1_build(word_t param_1, word_t param_2)
{
    if (param_1 == 1) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_00056410;
    *((word_t *)(param_2 + 0x48)) = &LAB_00056428;
    *((word_t *)(param_2 + 0x50)) = &LAB_00056440;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_0005645c;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_00056474;
    *((word_t *)(param_2 + 0x78)) = &LAB_000564ac;
    *((word_t *)(param_2 + 0x80)) = &LAB_000564c4;
    *((word_t *)(param_2 + 0x88)) = &LAB_000564dc;
    *((word_t *)(param_2 + 0x90)) = &LAB_00056504;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_00056528;
    *((word_t *)(param_2 + 0xb0)) = &LAB_00056530;
    *((word_t *)(param_2 + 0xb8)) = &LAB_00056538;
    *((word_t *)(param_2 + 0xc0)) = &LAB_00056540;
    *((word_t *)(param_2 + 0xd8)) = &LAB_00056548;
    *((word_t *)(param_2 + 0xe0)) = &LAB_00056550;
    *((word_t *)(param_2 + 0xe8)) = &LAB_00056558;
    *((word_t *)(param_2 + 0xf8)) = &LAB_00056560;
    *((word_t *)(param_2 + 0x100)) = &LAB_00056580;
    *((word_t *)(param_2 + 0x108)) = &LAB_0005659c;
    *((word_t *)(param_2 + 0x110)) = &LAB_000565b4;
    *((word_t *)(param_2 + 0x118)) = &LAB_000565bc;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_000565f0;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_0005660c;
    *((word_t *)(param_2 + 0x158)) = &LAB_0005662c;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_0005664c;
    *((word_t *)(param_2 + 0x170)) = &LAB_00056694;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bcea0  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bcf70  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_000566d4;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_000566dc;
    }
    return param_1 == 1;
}

/* FUN_0005680c @ 0x0005680c  (est. sk_svc_class_0x100000001_build)
 * Build the syscall-class descriptor for class id 0x100000001: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 0x100000001.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_0x100000001_build(word_t param_1, word_t param_2)
{
    if (param_1 == 0x100000001) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_00056b88;
    *((word_t *)(param_2 + 0x48)) = &LAB_00056ba0;
    *((word_t *)(param_2 + 0x50)) = &LAB_00056bb8;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_00056bd4;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_00056bec;
    *((word_t *)(param_2 + 0x78)) = &LAB_00056c24;
    *((word_t *)(param_2 + 0x80)) = &LAB_00056c3c;
    *((word_t *)(param_2 + 0x88)) = &LAB_00056c54;
    *((word_t *)(param_2 + 0x90)) = &LAB_00056c7c;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_00056ca0;
    *((word_t *)(param_2 + 0xb0)) = &LAB_00056ca8;
    *((word_t *)(param_2 + 0xb8)) = &LAB_00056cb0;
    *((word_t *)(param_2 + 0xc0)) = &LAB_00056cb8;
    *((word_t *)(param_2 + 0xd8)) = &LAB_00056cc0;
    *((word_t *)(param_2 + 0xe0)) = &LAB_00056cc8;
    *((word_t *)(param_2 + 0xe8)) = &LAB_00056cd0;
    *((word_t *)(param_2 + 0xf8)) = &LAB_00056cd8;
    *((word_t *)(param_2 + 0x100)) = &LAB_00056cf8;
    *((word_t *)(param_2 + 0x108)) = &LAB_00056d14;
    *((word_t *)(param_2 + 0x110)) = &LAB_00056d2c;
    *((word_t *)(param_2 + 0x118)) = &LAB_00056d34;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_00056d68;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_00056d84;
    *((word_t *)(param_2 + 0x158)) = &LAB_00056da4;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_00056dc4;
    *((word_t *)(param_2 + 0x170)) = &LAB_00056e0c;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bd040  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bd110  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_00056e4c;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_00056e54;
    }
    return param_1 == 0x100000001;
}

/* FUN_00056f84 @ 0x00056f84  (est. sk_svc_class_0x200000001_build)
 * Build the syscall-class descriptor for class id 0x200000001: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 0x200000001.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_0x200000001_build(word_t param_1, word_t param_2)
{
    if (param_1 == 0x200000001) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_0005730c;
    *((word_t *)(param_2 + 0x48)) = &LAB_00057324;
    *((word_t *)(param_2 + 0x50)) = &LAB_0005733c;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_00057358;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_00057370;
    *((word_t *)(param_2 + 0x78)) = &LAB_000573a8;
    *((word_t *)(param_2 + 0x80)) = &LAB_000573c0;
    *((word_t *)(param_2 + 0x88)) = &LAB_000573d8;
    *((word_t *)(param_2 + 0x90)) = &LAB_00057400;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_00057424;
    *((word_t *)(param_2 + 0xb0)) = &LAB_0005742c;
    *((word_t *)(param_2 + 0xb8)) = &LAB_00057434;
    *((word_t *)(param_2 + 0xc0)) = &LAB_0005743c;
    *((word_t *)(param_2 + 0xd8)) = &LAB_00057444;
    *((word_t *)(param_2 + 0xe0)) = &LAB_0005744c;
    *((word_t *)(param_2 + 0xe8)) = &LAB_00057454;
    *((word_t *)(param_2 + 0xf8)) = &LAB_0005745c;
    *((word_t *)(param_2 + 0x100)) = &LAB_0005747c;
    *((word_t *)(param_2 + 0x108)) = &LAB_00057498;
    *((word_t *)(param_2 + 0x110)) = &LAB_000574b0;
    *((word_t *)(param_2 + 0x118)) = &LAB_000574b8;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_000574ec;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_00057508;
    *((word_t *)(param_2 + 0x158)) = &LAB_00057528;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_00057548;
    *((word_t *)(param_2 + 0x170)) = &LAB_00057590;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bd1e0  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bd2b0  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_000575d0;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_000575d8;
    }
    return param_1 == 0x200000001;
}

/* FUN_00057708 @ 0x00057708  (est. sk_svc_class_0x300000001_build)
 * Build the syscall-class descriptor for class id 0x300000001: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 0x300000001.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_0x300000001_build(word_t param_1, word_t param_2)
{
    if (param_1 == 0x300000001) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_00057a90;
    *((word_t *)(param_2 + 0x48)) = &LAB_00057aa8;
    *((word_t *)(param_2 + 0x50)) = &LAB_00057ac0;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_00057adc;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_00057af4;
    *((word_t *)(param_2 + 0x78)) = &LAB_00057b2c;
    *((word_t *)(param_2 + 0x80)) = &LAB_00057b44;
    *((word_t *)(param_2 + 0x88)) = &LAB_00057b5c;
    *((word_t *)(param_2 + 0x90)) = &LAB_00057b84;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_00057ba8;
    *((word_t *)(param_2 + 0xb0)) = &LAB_00057bb0;
    *((word_t *)(param_2 + 0xb8)) = &LAB_00057bb8;
    *((word_t *)(param_2 + 0xc0)) = &LAB_00057bc0;
    *((word_t *)(param_2 + 0xd8)) = &LAB_00057bc8;
    *((word_t *)(param_2 + 0xe0)) = &LAB_00057bd0;
    *((word_t *)(param_2 + 0xe8)) = &LAB_00057bd8;
    *((word_t *)(param_2 + 0xf8)) = &LAB_00057be0;
    *((word_t *)(param_2 + 0x100)) = &LAB_00057c00;
    *((word_t *)(param_2 + 0x108)) = &LAB_00057c1c;
    *((word_t *)(param_2 + 0x110)) = &LAB_00057c34;
    *((word_t *)(param_2 + 0x118)) = &LAB_00057c3c;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_00057c70;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_00057c8c;
    *((word_t *)(param_2 + 0x158)) = &LAB_00057cac;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_00057ccc;
    *((word_t *)(param_2 + 0x170)) = &LAB_00057d14;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bd380  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bd450  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_00057d54;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_00057d5c;
    }
    return param_1 == 0x300000001;
}

/* FUN_00057e8c @ 0x00057e8c  (est. sk_svc_class_0x400000001_build)
 * Build the syscall-class descriptor for class id 0x400000001: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 0x400000001.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_0x400000001_build(word_t param_1, word_t param_2)
{
    if (param_1 == 0x400000001) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_00058210;
    *((word_t *)(param_2 + 0x48)) = &LAB_00058228;
    *((word_t *)(param_2 + 0x50)) = &LAB_00058240;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_0005825c;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_00058274;
    *((word_t *)(param_2 + 0x78)) = &LAB_000582ac;
    *((word_t *)(param_2 + 0x80)) = &LAB_000582c4;
    *((word_t *)(param_2 + 0x88)) = &LAB_000582dc;
    *((word_t *)(param_2 + 0x90)) = &LAB_00058304;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_00058328;
    *((word_t *)(param_2 + 0xb0)) = &LAB_00058330;
    *((word_t *)(param_2 + 0xb8)) = &LAB_00058338;
    *((word_t *)(param_2 + 0xc0)) = &LAB_00058340;
    *((word_t *)(param_2 + 0xd8)) = &LAB_00058348;
    *((word_t *)(param_2 + 0xe0)) = &LAB_00058350;
    *((word_t *)(param_2 + 0xe8)) = &LAB_00058358;
    *((word_t *)(param_2 + 0xf8)) = &LAB_00058360;
    *((word_t *)(param_2 + 0x100)) = &LAB_00058380;
    *((word_t *)(param_2 + 0x108)) = &LAB_0005839c;
    *((word_t *)(param_2 + 0x110)) = &LAB_000583b4;
    *((word_t *)(param_2 + 0x118)) = &LAB_000583bc;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_000583f0;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_0005840c;
    *((word_t *)(param_2 + 0x158)) = &LAB_0005842c;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_0005844c;
    *((word_t *)(param_2 + 0x170)) = &LAB_00058494;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bd520  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bd5f0  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_000584d4;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_000584dc;
    }
    return param_1 == 0x400000001;
}

/* FUN_0005860c @ 0x0005860c  (est. sk_svc_class_0x500000001_build)
 * Build the syscall-class descriptor for class id 0x500000001: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 0x500000001.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_0x500000001_build(word_t param_1, word_t param_2)
{
    if (param_1 == 0x500000001) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_00058990;
    *((word_t *)(param_2 + 0x48)) = &LAB_000589a8;
    *((word_t *)(param_2 + 0x50)) = &LAB_000589c0;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_000589dc;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_000589f4;
    *((word_t *)(param_2 + 0x78)) = &LAB_00058a2c;
    *((word_t *)(param_2 + 0x80)) = &LAB_00058a44;
    *((word_t *)(param_2 + 0x88)) = &LAB_00058a5c;
    *((word_t *)(param_2 + 0x90)) = &LAB_00058a84;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_00058aa8;
    *((word_t *)(param_2 + 0xb0)) = &LAB_00058ab0;
    *((word_t *)(param_2 + 0xb8)) = &LAB_00058ab8;
    *((word_t *)(param_2 + 0xc0)) = &LAB_00058ac0;
    *((word_t *)(param_2 + 0xd8)) = &LAB_00058ac8;
    *((word_t *)(param_2 + 0xe0)) = &LAB_00058ad0;
    *((word_t *)(param_2 + 0xe8)) = &LAB_00058ad8;
    *((word_t *)(param_2 + 0xf8)) = &LAB_00058ae0;
    *((word_t *)(param_2 + 0x100)) = &LAB_00058b00;
    *((word_t *)(param_2 + 0x108)) = &LAB_00058b1c;
    *((word_t *)(param_2 + 0x110)) = &LAB_00058b34;
    *((word_t *)(param_2 + 0x118)) = &LAB_00058b3c;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_00058b70;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_00058b8c;
    *((word_t *)(param_2 + 0x158)) = &LAB_00058bac;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_00058bcc;
    *((word_t *)(param_2 + 0x170)) = &LAB_00058c14;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bd6c0  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bd790  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_00058c54;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_00058c5c;
    }
    return param_1 == 0x500000001;
}

/* FUN_00058d8c @ 0x00058d8c  (est. sk_svc_class_0x600000001_build)
 * Build the syscall-class descriptor for class id 0x600000001: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 0x600000001.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_0x600000001_build(word_t param_1, word_t param_2)
{
    if (param_1 == 0x600000001) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_00059110;
    *((word_t *)(param_2 + 0x48)) = &LAB_00059128;
    *((word_t *)(param_2 + 0x50)) = &LAB_00059140;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_0005915c;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_00059174;
    *((word_t *)(param_2 + 0x78)) = &LAB_000591ac;
    *((word_t *)(param_2 + 0x80)) = &LAB_000591c4;
    *((word_t *)(param_2 + 0x88)) = &LAB_000591dc;
    *((word_t *)(param_2 + 0x90)) = &LAB_00059204;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_00059228;
    *((word_t *)(param_2 + 0xb0)) = &LAB_00059230;
    *((word_t *)(param_2 + 0xb8)) = &LAB_00059238;
    *((word_t *)(param_2 + 0xc0)) = &LAB_00059240;
    *((word_t *)(param_2 + 0xd8)) = &LAB_00059248;
    *((word_t *)(param_2 + 0xe0)) = &LAB_00059250;
    *((word_t *)(param_2 + 0xe8)) = &LAB_00059258;
    *((word_t *)(param_2 + 0xf8)) = &LAB_00059260;
    *((word_t *)(param_2 + 0x100)) = &LAB_00059280;
    *((word_t *)(param_2 + 0x108)) = &LAB_0005929c;
    *((word_t *)(param_2 + 0x110)) = &LAB_000592b4;
    *((word_t *)(param_2 + 0x118)) = &LAB_000592bc;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_000592f0;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_0005930c;
    *((word_t *)(param_2 + 0x158)) = &LAB_0005932c;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_0005934c;
    *((word_t *)(param_2 + 0x170)) = &LAB_00059394;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bd860  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bd930  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_000593d4;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_000593dc;
    }
    return param_1 == 0x600000001;
}

/* FUN_0005950c @ 0x0005950c  (est. sk_svc_class_0x700000001_build)
 * Build the syscall-class descriptor for class id 0x700000001: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 0x700000001.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_0x700000001_build(word_t param_1, word_t param_2)
{
    if (param_1 == 0x700000001) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_00059890;
    *((word_t *)(param_2 + 0x48)) = &LAB_000598a8;
    *((word_t *)(param_2 + 0x50)) = &LAB_000598c0;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_000598dc;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_000598f4;
    *((word_t *)(param_2 + 0x78)) = &LAB_0005992c;
    *((word_t *)(param_2 + 0x80)) = &LAB_00059944;
    *((word_t *)(param_2 + 0x88)) = &LAB_0005995c;
    *((word_t *)(param_2 + 0x90)) = &LAB_00059984;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_000599a8;
    *((word_t *)(param_2 + 0xb0)) = &LAB_000599b0;
    *((word_t *)(param_2 + 0xb8)) = &LAB_000599b8;
    *((word_t *)(param_2 + 0xc0)) = &LAB_000599c0;
    *((word_t *)(param_2 + 0xd8)) = &LAB_000599c8;
    *((word_t *)(param_2 + 0xe0)) = &LAB_000599d0;
    *((word_t *)(param_2 + 0xe8)) = &LAB_000599d8;
    *((word_t *)(param_2 + 0xf8)) = &LAB_000599e0;
    *((word_t *)(param_2 + 0x100)) = &LAB_00059a00;
    *((word_t *)(param_2 + 0x108)) = &LAB_00059a1c;
    *((word_t *)(param_2 + 0x110)) = &LAB_00059a34;
    *((word_t *)(param_2 + 0x118)) = &LAB_00059a3c;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_00059a70;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_00059a8c;
    *((word_t *)(param_2 + 0x158)) = &LAB_00059aac;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_00059acc;
    *((word_t *)(param_2 + 0x170)) = &LAB_00059b14;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bda00  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bdad0  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_00059b54;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_00059b5c;
    }
    return param_1 == 0x700000001;
}

/* FUN_00059c8c @ 0x00059c8c  (est. sk_svc_class_0x800000001_build)
 * Build the syscall-class descriptor for class id 0x800000001: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 0x800000001.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_0x800000001_build(word_t param_1, word_t param_2)
{
    if (param_1 == 0x800000001) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_0005a010;
    *((word_t *)(param_2 + 0x48)) = &LAB_0005a028;
    *((word_t *)(param_2 + 0x50)) = &LAB_0005a040;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_0005a05c;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_0005a074;
    *((word_t *)(param_2 + 0x78)) = &LAB_0005a0ac;
    *((word_t *)(param_2 + 0x80)) = &LAB_0005a0c4;
    *((word_t *)(param_2 + 0x88)) = &LAB_0005a0dc;
    *((word_t *)(param_2 + 0x90)) = &LAB_0005a104;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_0005a128;
    *((word_t *)(param_2 + 0xb0)) = &LAB_0005a130;
    *((word_t *)(param_2 + 0xb8)) = &LAB_0005a138;
    *((word_t *)(param_2 + 0xc0)) = &LAB_0005a140;
    *((word_t *)(param_2 + 0xd8)) = &LAB_0005a148;
    *((word_t *)(param_2 + 0xe0)) = &LAB_0005a150;
    *((word_t *)(param_2 + 0xe8)) = &LAB_0005a158;
    *((word_t *)(param_2 + 0xf8)) = &LAB_0005a160;
    *((word_t *)(param_2 + 0x100)) = &LAB_0005a180;
    *((word_t *)(param_2 + 0x108)) = &LAB_0005a19c;
    *((word_t *)(param_2 + 0x110)) = &LAB_0005a1b4;
    *((word_t *)(param_2 + 0x118)) = &LAB_0005a1bc;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_0005a1f0;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_0005a20c;
    *((word_t *)(param_2 + 0x158)) = &LAB_0005a22c;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_0005a24c;
    *((word_t *)(param_2 + 0x170)) = &LAB_0005a294;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bdba0  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bdc70  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_0005a2d4;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_0005a2dc;
    }
    return param_1 == 0x800000001;
}

/* FUN_0005a40c @ 0x0005a40c  (est. sk_svc_class_0x900000001_build)
 * Build the syscall-class descriptor for class id 0x900000001: fills the
 * descriptor at param_2 with the class id, the (redacted) name, the
 * method-pointer table (inline stubs + SVC wrappers), version fields,
 * the two data tables and the dispatch code pointer, then returns whether
 * param_1 == 0x900000001.
 * Confidence: medium (structural; LAB_ inline stub targets and DAT_ tables
 *   are opaque addresses, and the class name is redacted) */
static bool sk_svc_class_0x900000001_build(word_t param_1, word_t param_2)
{
    if (param_1 == 0x900000001) {
    *((word_t *)(param_2 + 0x10)) = "Redacted";
    *((word_t *)(param_2 + 0x40)) = &LAB_0005a78c;
    *((word_t *)(param_2 + 0x48)) = &LAB_0005a7a4;
    *((word_t *)(param_2 + 0x50)) = &LAB_0005a7bc;
    *((word_t *)(param_2 + 0x58)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0x60)) = &LAB_0005a7d8;
    *((word_t *)(param_2 + 0x68)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x70)) = &LAB_0005a7f0;
    *((word_t *)(param_2 + 0x78)) = &LAB_0005a828;
    *((word_t *)(param_2 + 0x80)) = &LAB_0005a840;
    *((word_t *)(param_2 + 0x88)) = &LAB_0005a858;
    *((word_t *)(param_2 + 0x90)) = &LAB_0005a880;
    *((word_t *)(param_2 + 0x98)) = (word_t)sk_svc_1_marsh1;
    *((word_t *)(param_2 + 0xa8)) = &LAB_0005a8a4;
    *((word_t *)(param_2 + 0xb0)) = &LAB_0005a8ac;
    *((word_t *)(param_2 + 0xb8)) = &LAB_0005a8b4;
    *((word_t *)(param_2 + 0xc0)) = &LAB_0005a8bc;
    *((word_t *)(param_2 + 0xd8)) = &LAB_0005a8c4;
    *((word_t *)(param_2 + 0xe0)) = &LAB_0005a8cc;
    *((word_t *)(param_2 + 0xe8)) = &LAB_0005a8d4;
    *((word_t *)(param_2 + 0xf8)) = &LAB_0005a8dc;
    *((word_t *)(param_2 + 0x100)) = &LAB_0005a8fc;
    *((word_t *)(param_2 + 0x108)) = &LAB_0005a918;
    *((word_t *)(param_2 + 0x110)) = &LAB_0005a930;
    *((word_t *)(param_2 + 0x118)) = &LAB_0005a938;
    *((word_t *)(param_2 + 0x120)) = (word_t)sk_svc_2_marsh4;
    *((word_t *)(param_2 + 0x128)) = (word_t)sk_svc_3_marsh1;
    *((word_t *)(param_2 + 0x130)) = &LAB_0005a96c;
    *((word_t *)(param_2 + 0x138)) = (word_t)sk_svc_5_marsh1;
    *((word_t *)(param_2 + 0x150)) = &LAB_0005a988;
    *((word_t *)(param_2 + 0x158)) = &LAB_0005a9a8;
    *((word_t *)(param_2 + 0x160)) = (word_t)sk_svc_1_marsh2;
    *((word_t *)(param_2 + 0x168)) = &LAB_0005a9c8;
    *((word_t *)(param_2 + 0x170)) = &LAB_0005aa10;
    *((word_t *)(param_2 + 0x180)) = (word_t)0x004bdd40  /* data table */;
    *((word_t *)(param_2 + 0x188)) = (word_t)0x004bde10  /* data table */;
    *((word_t *)(param_2 + 0x198)) = &LAB_0005aa50;
    *((word_t *)(param_2 + 0x1a0)) = &LAB_0005aa58;
    }
    return param_1 == 0x900000001;
}
/* ================================================================== *
 * Runflags / sec-transition capability gates and the singleton
 * initialisation helper for this slice.
 * ================================================================== */

/* FUN_0005ab88 @ 0x5ab88  (est. sk_runflag_gate)
 * Invoke the boot/runflag gate check FUN_00053568 with selector 1.
 * Confidence: medium (thin wrapper; callee out of slice) */
static void sk_runflag_gate(word_t param_1)
{
    FUN_00053568(1);
}

/* FUN_0005ab94 @ 0x5ab94  (est. sk_xrt_runflags_check)
 * Check the cL4 `xrt__runflags` capability for the runflag bit selected by
 * param_2 within the runflags word at offset param_1. Looks up the
 * "xrt__runflags" symbol (FUN_0006562c); if absent returns 0; if the runflags
 * word is shorter than param_1, panics with "xrt runflag metadata not long
 * enough" (noreturn); otherwise returns 1 if the bit is set, 2 if clear.
 * A pointer-overflow check on the runflags buffer is guarded by Software
 * Breakpoint 0x5519.
 * Confidence: medium (string-matched "xrt__runflags" / "xrt runflag
 *   metadata not long enough") */
static unsigned int sk_xrt_runflags_check(unsigned long param_1, unsigned int param_2)
{
    word_t symval = 0;
    long sym = FUN_0006562c("xrt__runflags", &symval);
    if (sym == 0)
        return 0;
    if (symval < (param_1 & 0xffffffff)) {
        FUN_0005b190(FUN_00060524(), (word_t)"xrt runflag metadata not long enough");
        /* noreturn */
    }
    {
        char *p = (char *)(sym + (param_1 & 0xffffffff));
        if ((char *)(sym + symval) <= p)
            CL4_FATAL();   /* Software Breakpoint 0x5519 @ 0x5ac1c */
        return ((unsigned int)*p >> (param_2 & 0x1f) & 1) == 0 ? 2 : 1;
    }
}

/* FUN_0005ac2c @ 0x5ac2c  (est. sk_sec_transition_allowed)
 * Decide whether the current context may perform a secure (Sec) transition.
 * Returns 1 when allowed, 0 otherwise. Requires the singleton flag byte
 * (offset 0x1b8) to be non-zero, and the byte at FUN_00054610() to have bit
 * 0 clear (i.e. not already in a transition). It then looks up the
 * "sec_transition" symbol; if missing or its stored value equals
 * DAT_005cf0f4 it clears the "xrt__runflags" bit via sk_xrt_runflags_check
 * (2,1) and returns (that result == 1). Otherwise it returns 1.
 * Confidence: medium (string-matched "sec_transition"; DAT_005cf0f4
 *   comparison via thunk_FUN_00114e50 is a string/byte compare) */
static unsigned long sk_sec_transition_allowed(void)
{
    unsigned long r;
    r = sk_svc_get_1b8();
    if ((int)r != 0) {
        unsigned char *pb = (unsigned char *)FUN_00054610();
        if ((*pb & 1) == 0) {
            word_t val = 0;
            long sym = FUN_0006562c("sec_transition", &val);
            if (sym == 0 || (word_t)thunk_FUN_00114e50(sym, &DAT_005cf0f4, val) == 0) {
                r = (unsigned long)(sk_xrt_runflags_check(2, 1) == 1);
            } else {
                r = 1;
            }
        } else {
            r = 0;
        }
    }
    return r;
}
