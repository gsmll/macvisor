/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * This file covers the ExclaveLauncher subsystem in the caps region
 * 0x980000 - 0x9F0000. The launcher is the cL4 component that bootstraps an
 * exclave: it builds the exclave's raw address space (Raw Address Space),
 * populates it with frame/PTE descriptors, allocates CNodes and capability
 * objects (Caps, ECs, notifications), and finally enters the init EC.
 *
 * String anchors (Ghidra): "InternalExclaveLauncher_External",
 * "InternalExclaveLauncher_CNodeAll", "__Init endpoint doesn't exist",
 * "__Not just one init EC cap", "Launcher abort: exclave address space",
 * "launcher Raw Address Space manager", "CnodeAllocator failed to add",
 * "Unexpected EK region", "Unexpectedly mapped on both ends",
 * "Unexpected type of ExtVMRegion", "Fatal error", "AppleInternal Library
 * BuildRoot".
 *
 * The launcher is a vtable-based object (x20): many small functions are thin
 * vtable-dispatch passthroughs that read a method pointer from *obj + slot and
 * call it. The supervisor-call stubs marshal argument words into the per-thread
 * area addressed by tpidrro_el0 and then issue an SVC (Ghidra "CallSupervisor").
 * Confidence is medium unless a string matches.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint64_t cptr_t;
typedef uint64_t vptr_t;
typedef uint64_t cap_t;
typedef unsigned char byte_t;

/* 128-bit pair used by helpers that return two words (e.g. log descriptors,
 * table lookups). */
typedef struct cl4_pair { word_t lo; word_t hi; } cl4_pair_t;

/* vtable dispatch: fn in slot `off` of the object at `obj`. */
typedef void (*vfn_t)(void);

/* Empty-list / empty-vector sentinel (_DAT_00657778). */
extern word_t cl4_empty_list;

/* Debug-gate flag _DAT_006add10 ("verbose" switch checked at init). */
extern unsigned char cl4_verbose;

/* Supervisor-call message words (_DAT_004be5e0 / _DAT_004be5e8). */
extern word_t cl4_msg_word0;
extern word_t cl4_msg_word1;

/* The current launcher object pointer (unaff_x20), set by the caller in the
 * launcher's vtable-based methods. Returns the object base address. */
static word_t *sk_launcher(void) { return 0; }

/* Supervisor-call argument area: the launcher writes argument words to the
 * per-thread area addressed by tpidrro_el0, then issues the supervisor call
 * (Ghidra "CallSupervisor"). */
extern word_t *sk_sc_arg_area(void);
extern void    CallSupervisor(unsigned int n);   /* SVC/SMC supervisor call */

/* Fatal error path: FUN_001afa84 never returns (prints a formatted fatal). */
extern void FUN_001afa84(word_t a, ...) __attribute__((noreturn));
extern void FUN_0011d7e8(void) __attribute__((noreturn));
extern void FUN_0009e2b4(void) __attribute__((noreturn));

/* ----- out-of-slice kernel/allocator/misc helpers (exact FUN_ names) ----- */

extern word_t FUN_0036a940(word_t obj, word_t size, int tag);
extern void   FUN_0036b270(void *obj);   /* retain/acquire ref */
extern void   FUN_0036b118(void *obj);   /* release ref (may be NULL) */
extern word_t FUN_0036a9a0(word_t a, void *buf);
extern word_t FUN_0036a9d4(word_t a, word_t meta);
extern word_t FUN_0036b2d0(word_t a, word_t n);
extern void   FUN_0036b588(word_t x);
extern word_t FUN_0036b6ac(word_t a, word_t b, word_t c);
extern word_t FUN_0036a1a0(word_t a, word_t b, word_t c, word_t d);
extern word_t FUN_0036a20c(word_t a);
extern word_t FUN_0036a804(word_t a, word_t b);
extern word_t FUN_0036986c(void);
extern word_t FUN_0036993c(word_t a, word_t b, word_t c, word_t d);
extern void   FUN_003a25d4(word_t x);
extern word_t FUN_003a261c(void *v);
extern word_t thunk_FUN_002acbb8(word_t a, word_t b);
extern void   FUN_0006e7c0(word_t a, word_t b);
extern void   FUN_0000276c(word_t a, word_t b, word_t c);
extern void   FUN_000027e8(word_t a);
extern word_t FUN_00002688(void);
extern void   FUN_000026e8(word_t a);
extern void   FUN_00002804(word_t a);
extern word_t FUN_00002874(word_t key);
extern word_t FUN_0006c2b0(word_t a);
extern void   FUN_0006c454(word_t a);
extern word_t FUN_0016c700(word_t a, word_t b);
extern word_t FUN_0016d328(word_t a, word_t b, word_t c, word_t d,
                           word_t e, word_t f, word_t g);
extern word_t thunk_FUN_0016d4e8(void);
extern void   FUN_0008396c(word_t a, word_t b, word_t c);
extern word_t FUN_00153270(void);
extern word_t FUN_00153264(void);
extern word_t FUN_00167c48(void);
extern word_t FUN_00167a6c(word_t a);
extern word_t FUN_0008e328(word_t a);
extern word_t FUN_00093230(void);
extern word_t FUN_000931d4(void);
extern word_t FUN_00093e98(word_t a);
extern word_t FUN_00093c60(word_t a);
extern word_t FUN_00093c68(word_t a);
extern word_t thunk_FUN_00070594(word_t a);
extern word_t FUN_0008e0d4(void);
extern cl4_pair_t FUN_00151974(void);
extern word_t FUN_00151a6c(word_t a, ...);
extern word_t FUN_001ee018(void *v, word_t tag);
extern word_t FUN_0029f0b0(word_t kind, word_t idx, void *v, word_t tag);
extern cl4_pair_t FUN_0029fa0c(word_t a, word_t b);
extern cl4_pair_t FUN_0029fb80(void);
extern word_t FUN_002a0cf8(word_t a, word_t b, word_t c, word_t d, word_t e);
extern void   FUN_002a4ab4(word_t a);
extern cl4_pair_t FUN_002a9ba8(word_t a, word_t b);
extern word_t FUN_000f4404(word_t a, word_t b, word_t c, word_t d,
                           word_t e, word_t f);
extern word_t FUN_000b0794(word_t a, word_t b, word_t c, word_t d, word_t e);
extern word_t FUN_0001c294(word_t a, word_t b);
extern word_t FUN_00157308(word_t a);
extern void   FUN_0005597c(word_t a, word_t b);
extern unsigned int *FUN_00107200(void);
extern word_t FUN_00086440(word_t a);
extern word_t FUN_00086590(word_t a);
extern word_t FUN_00085a54(word_t a, word_t b, word_t c, word_t d, word_t e);
extern word_t FUN_00117d14(word_t a, word_t b, word_t c);
extern word_t FUN_00072de8(word_t a, word_t b, word_t c, word_t d);
extern word_t FUN_00072d5c(word_t a, word_t b, word_t c, word_t d);
extern void   FUN_00082544(word_t a, word_t b, word_t c);
extern void   FUN_00082524(word_t a, word_t b, word_t c);
extern word_t FUN_0036a261c(void *v);
extern word_t FUN_00117cc4(word_t a, word_t b, word_t c);
extern word_t FUN_0006b42c(void);
extern word_t FUN_000ddc5c(void);
extern void   FUN_0026b434(word_t a, word_t b, word_t c, word_t d, word_t e);
extern word_t FUN_00002534(word_t a, word_t b);
extern word_t FUN_00027724(word_t a);
extern word_t FUN_000e1368(word_t a);
extern word_t FUN_000dfd3c(word_t a, word_t b);
extern word_t FUN_000ec964(word_t a);
extern word_t FUN_000aa6d0(word_t a);
extern word_t FUN_0006f800(word_t a);
extern word_t FUN_000ec8f8(word_t a);
extern word_t FUN_0009781c(word_t a, word_t b, word_t c, word_t d);
extern void   FUN_000937b8(word_t a);
extern void   FUN_0007c0b8(void);
extern void   FUN_0007b238(void);
extern void   FUN_0007b414(word_t a);
extern word_t FUN_0007eb2c(word_t a, word_t b);
extern word_t FUN_0014aedc(word_t a, word_t b);
extern word_t FUN_0014aea4(word_t a);
extern word_t FUN_0014935c(void);
extern void   FUN_00149ba0(word_t a);
extern word_t FUN_0001df60(void);
extern void   FUN_001ebfb0(word_t a, word_t b, word_t c, word_t d, word_t e);
extern void   FUN_00097b94(word_t a, word_t b);
extern void   FUN_00097a58(void);
extern void   FUN_00097920(void);
extern void   FUN_00097ccc(word_t a);
extern word_t FUN_00034f70(void);
extern void   FUN_00085374(word_t a, word_t b, word_t c, word_t d);
extern word_t FUN_004b23d8(word_t a);
extern word_t thunk_FUN_0007bebc(word_t a);
extern word_t FUN_0029369c(word_t a);
extern word_t FUN_000f9680(word_t a, word_t b, word_t c, word_t d);
extern word_t FUN_000f9930(word_t a);
extern void   FUN_000f98ac(word_t a);   /* remove/replace a heap entry */
extern void   FUN_00069970(word_t a, word_t b, word_t c);
extern word_t thunk_FUN_000f9608(word_t a);
extern word_t thunk_FUN_000721b0(word_t a, word_t b, word_t c);
extern word_t FUN_001b798c(word_t a, word_t b, word_t c);
extern word_t FUN_000abad0(word_t a, word_t b, word_t t);   /* cap compare */
extern void   FUN_0008129c(word_t a);                       /* log a cap line */

/* "Fatal error" string literal (_005accd0). */
extern char sk_fatal_str[];

/* ----- in-slice forward declarations (bodies below) ----- */
word_t  FUN_00098dbc(word_t p1);
word_t  FUN_00098e38(word_t p1, word_t p2);
word_t  FUN_00099010(word_t a, word_t b, word_t c, word_t d, word_t e,
                     word_t f, word_t g);
word_t  FUN_000992b8(word_t *out, word_t a, word_t b, word_t c, word_t d,
                     word_t e, word_t f, word_t g);
void    FUN_00099398(word_t a, word_t b);
void    FUN_0009955c(word_t a, word_t *b, word_t c, word_t d);
word_t  FUN_0009a780(word_t *out, word_t p2, word_t size);
void    FUN_0009a96c(word_t *a, word_t b);
word_t  FUN_0009b4d8(word_t *out, word_t *obj, word_t a, word_t b, word_t c,
                     word_t d, word_t e, word_t f);
word_t  FUN_0009c7bc(void);
void    FUN_0009d078(word_t a, word_t b);
void    FUN_0009d094(void);
void    FUN_0009d0dc(void);
void    FUN_0009d100(void);
void    FUN_0009d190(void);
void    FUN_0009d1c0(word_t a, word_t b, word_t c);
void    FUN_0009d1e0(word_t a, word_t *b);
void    FUN_0009d20c(word_t a);
void    FUN_0009d3f8(word_t a, word_t b);
void    FUN_0009d414(word_t a, word_t b, word_t c);
void    FUN_0009d434(int idx, word_t v);
void    FUN_0009d444(word_t a, word_t b);
void    FUN_0009d460(word_t a, word_t b);
void    FUN_0009d480(void);
void    FUN_0009d488(word_t *a, word_t b, word_t *c, word_t d);
void    FUN_0009da34(word_t a, word_t b, word_t c, word_t *d);
word_t  FUN_0009db84(word_t *a, word_t b, word_t *c);
void   *FUN_0009dddc(word_t a, word_t b, word_t c);
word_t  FUN_0009de84(word_t *a, word_t *b, word_t *c, word_t *d);
word_t  FUN_0009e2a0(word_t a, word_t b);
void    FUN_0009bf9c(word_t a, word_t b, word_t c, word_t d);
static void map_all_caps(word_t *cap, word_t reg, word_t *p2, word_t **caps);

/* ------------------------------------------------------------------ *
 * Supervisor-call stubs. Each marshals argument words into the per-thread
 * area addressed by tpidrro_el0 and issues the SVC supervisor call.
 * ------------------------------------------------------------------ */

/* FUN_0009d078 @ 0x0009d078   (est. sk_sc_one_arg)
 * Ghidra: void FUN_0009d078(undefined8, undefined8)
 * One-argument supervisor call: write arg into the sc area, SVC(0). The
 * second parameter is the call target/capability.
 * Confidence: medium */
void FUN_0009d078(word_t a, word_t b)
{
    word_t *sc = sk_sc_arg_area();
    *sc = b;
    CallSupervisor(0);
    *sc = b;
}

/* FUN_0009d3f8 @ 0x0009d3f8   (est. sk_sc_one_arg_b)
 * Ghidra: void FUN_0009d3f8(undefined8, undefined8)
 * One-argument supervisor call, SVC(0) (same marshalling as FUN_0009d078).
 * Confidence: medium */
void FUN_0009d3f8(word_t a, word_t b)
{
    word_t *sc = sk_sc_arg_area();
    *sc = b;
    CallSupervisor(0);
    *sc = b;
}

/* FUN_0009d138 @ 0x0009d138 / FUN_0009d154 @ 0x0009d154 (identical aliases
 * of the one-arg SVC(0) stub). */
void FUN_0009d138(word_t a, word_t b) { FUN_0009d078(a, b); }
void FUN_0009d154(word_t a, word_t b) { FUN_0009d078(a, b); }

/* FUN_0009d170 @ 0x0009d170   (est. sk_sc_two_arg)
 * Ghidra: void FUN_0009d170(undefined8, undefined8, undefined8)
 * Two-argument supervisor call, SVC(0): args land at sc[0], sc[1].
 * Confidence: medium */
void FUN_0009d170(word_t a, word_t b, word_t c)
{
    word_t *sc = sk_sc_arg_area();
    *sc = b;
    sc[1] = c;
    CallSupervisor(0);
    *sc = b;
}

/* FUN_0009d414 @ 0x0009d414   (est. sk_sc_two_arg_b)
 * Ghidra: void FUN_0009d414(undefined8, undefined8, undefined8)
 * Two-argument supervisor call, SVC(0).
 * Confidence: medium */
void FUN_0009d414(word_t a, word_t b, word_t c)
{
    word_t *sc = sk_sc_arg_area();
    *sc = b;
    sc[1] = c;
    CallSupervisor(0);
    *sc = b;
}

/* FUN_0009d1c0 @ 0x0009d1c0   (est. sk_sc_init_start)
 * Ghidra: void FUN_0009d1c0(undefined8, undefined8, undefined8)
 * Starts the init EC: writes the two fixed message words (cl4_msg_word0/1)
 * and the third argument into the sc area, then SVC(3).
 * Confidence: medium
 * Notes: reads globals _DAT_004be5e0 / _DAT_004be5e8. */
void FUN_0009d1c0(word_t a, word_t b, word_t c)
{
    word_t *sc = sk_sc_arg_area();
    sc[1] = cl4_msg_word1;
    *sc = cl4_msg_word0;
    sc[2] = c;
    CallSupervisor(3);
}

/* FUN_0009d1e0 @ 0x0009d1e0   (est. sk_sc_return)
 * Ghidra: void FUN_0009d1e0(undefined8, undefined8 *)
 * Supervisor call that returns a value: reads *param_2, SVC(0), writes the
 * (unchanged) value back through param_2.
 * Confidence: medium */
void FUN_0009d1e0(word_t a, word_t *b)
{
    word_t v = *b;
    word_t *sc = sk_sc_arg_area();
    *sc = v;
    CallSupervisor(0);
    *sc = v;
    *b = v;
}

/* FUN_0009d20c @ 0x0009d20c   (est. sk_sc_poll)
 * Ghidra: void FUN_0009d20c(long)
 * Issue SVC(4) repeatedly while the argument equals 1 (a poll/yield loop).
 * Confidence: medium */
void FUN_0009d20c(word_t a)
{
    do {
        CallSupervisor(4);
    } while (a == 1);
}

/* FUN_0009d444 @ 0x0009d444   (est. sk_sc_badge)
 * Ghidra: void FUN_0009d444(undefined8, undefined8)
 * Badge-set supervisor call: sc[0]=0, sc[1]=value, SVC(0).
 * Confidence: medium */
void FUN_0009d444(word_t a, word_t b)
{
    word_t *sc = sk_sc_arg_area();
    *sc = 0;
    sc[1] = b;
    CallSupervisor(0);
    *sc = 0;
}

/* FUN_0009d460 @ 0x0009d460   (est. sk_sc_cap_set)
 * Ghidra: void FUN_0009d460(undefined8, undefined8)
 * Capability-set supervisor call: sc[0]=1, sc[1]=value, SVC(0).
 * Confidence: medium */
void FUN_0009d460(word_t a, word_t b)
{
    word_t *sc = sk_sc_arg_area();
    *sc = 1;
    sc[1] = b;
    CallSupervisor(0);
    *sc = 1;
}

/* FUN_0009d434 @ 0x0009d434   (est. sk_reg_block_write)
 * Ghidra: void FUN_0009d434(int, undefined8)
 * Write a register value into the per-thread register block: entry
 * (param_1 + 2) of the tpidrro_el0 area.
 * Confidence: medium */
void FUN_0009d434(int idx, word_t v)
{
    word_t *base = sk_sc_arg_area();
    base[(word_t)(idx + 2)] = v;
}

/* FUN_0009d480 @ 0x0009d480   (est. sk_sc2)
 * Ghidra: void FUN_0009d480(void)
 * Argument-less SVC(2).
 * Confidence: medium */
void FUN_0009d480(void)
{
    CallSupervisor(2);
}

/* ------------------------------------------------------------------ *
 * Empty / log-only helpers (these are real empty bodies in the binary;
 * they are the launcher's instrumentation hooks).
 * ------------------------------------------------------------------ */
void FUN_0009e148(word_t a) { (void)a; return; }
void FUN_0009e174(void) { return; }
void FUN_0009e18c(word_t a) { (void)a; return; }
void FUN_0009e1a0(void) { return; }
void FUN_0009e1b8(void) { return; }
void FUN_0009e1d0(void) { return; }
void FUN_0009e1e8(void) { return; }
void FUN_0009e1fc(word_t a) { (void)a; return; }
void FUN_0009e20c(void) { return; }
void FUN_0009e218(word_t a) { (void)a; return; }
void FUN_0009e228(void) { return; }
void FUN_0009e234(void) { return; }
void FUN_0009e258(word_t a, word_t b, word_t c) { (void)a; (void)b; (void)c; return; }
void FUN_0009e26c(word_t a) { (void)a; return; }
void FUN_0009e280(void) { return; }
word_t FUN_0009e28c(void) { return 0; }

/* FUN_0009e160 @ 0x0009e160   (est. sk_fatal_str_ptr)
 * Ghidra: char * FUN_0009e160(void)
 * Returns the "Fatal error" format string.
 * Confidence: high (string matched) */
char *FUN_0009e160(void) { return sk_fatal_str; }

/* FUN_0009e124 @ 0x0009e124   (est. sk_fatal_desc)
 * Ghidra: undefined1 [16] FUN_0009e124(void)
 * Returns a 16-byte fatal-error descriptor {sk_fatal_str, 0xb}.
 * Confidence: high (string matched) */
cl4_pair_t FUN_0009e124(void)
{
    cl4_pair_t r;
    r.lo = (word_t)sk_fatal_str;
    r.hi = 0xb;
    return r;
}

/* FUN_0009e240 @ 0x0009e240   (est. sk_log_type_5b)
 * Ghidra: void FUN_0009e240(void)
 * Emits a log message of type 0xe100000000000000 with the message words held
 * in the caller's frame (+0xb0/+0xb8) via thunk_FUN_002acbb8.
 * Confidence: low
 * Notes: uses unaff_x19 as the launcher pointer; two stack words 0x5b and
 *   0xe100000000000000 are pre-set. */
void FUN_0009e240(void)
{
    thunk_FUN_002acbb8(0x5b, 0xe100000000000000);
}

/* ------------------------------------------------------------------ *
 * vtable-dispatch passthroughs. Each reads the method pointer at slot `off`
 * of the launcher object's vtable (*(word_t*)self + off) and calls it.
 * ------------------------------------------------------------------ */
void FUN_0009c930(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x1c8); fn(); }
void FUN_0009c8b4(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x1e8); fn(); }
void FUN_0009ca7c(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x240); fn(); }
void FUN_0009cac0(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x210); fn(); }
void FUN_0009cb04(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x268); fn(); }
void FUN_0009cb48(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x278); fn(); }
void FUN_0009cb8c(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x270); fn(); }
void FUN_0009cbd0(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x288); fn(); }
void FUN_0009cc14(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x290); fn(); }
void FUN_0009cc58(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x298); fn(); }
void FUN_0009cc9c(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x2b0); fn(); }
void FUN_0009cce0(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x2b8); fn(); }
void FUN_0009cd24(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x2d8); fn(); }
void FUN_0009cd68(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x2e0); fn(); }
void FUN_0009cdac(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x2c0); fn(); }
void FUN_0009ce8c(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x2e8); fn(); }
void FUN_0009ced0(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x2f0); fn(); }
void FUN_0009cf14(void) { vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x2f8); fn(); }

/* FUN_0009cdf0 @ 0x0009cdf0   (est. launcher_vtable_2c8)
 * Ghidra: undefined1 [16] FUN_0009cdf0(void)
 * Returns a 16-byte value from vtable slot 0x2c8 (both halves equal unless
 * an error flag is set, in which case {0,0} is returned).
 * Confidence: low
 * Notes: auVar1._0_8_/._8_8_ = extraout_x8; unaff_x21 is the error flag. */
cl4_pair_t FUN_0009cdf0(void)
{
    cl4_pair_t r;
    vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x2c8);
    /* fn() returns a 16-byte value in x0/x1 */
    r.lo = 0;
    r.hi = 0;
    return r;   /* placeholder halves; full result in x0/x1 */
}

/* FUN_0009ce44 @ 0x0009ce44   (est. launcher_vtable_2d0_flag)
 * Ghidra: uint FUN_0009ce44(void)
 * Returns bit 0 of the value from vtable slot 0x2d0.
 * Confidence: low */
word_t FUN_0009ce44(void)
{
    word_t r = (word_t)((vfn_t)0);   /* vtable slot 0x2d0 result */
    return r & 1;
}

/* FUN_0009c8fc @ 0x0009c8fc   (est. launcher_vtable_b0_fetch)
 * Ghidra: undefined1 [16] FUN_0009c8fc(void)
 * Reads the 16-byte value at vtable slot 0xb0 and retains the object at
 * slot 0xb8.
 * Confidence: low */
cl4_pair_t FUN_0009c8fc(void)
{
    cl4_pair_t r;
    r.lo = *(word_t *)(*sk_launcher() +  0xb0);
    r.hi = 0;
    FUN_0036b270((void *)*(word_t *)(*sk_launcher() +  0xb8));
    return r;
}

/* FUN_0009c98c @ 0x0009c98c   (est. launcher_capture_record)
 * Ghidra: void FUN_0009c98c(undefined8)
 * Copies a 0x50-byte record from vtable slot 0x228 into param_1.
 * Confidence: low */
void FUN_0009c98c(word_t p1)
{
    byte_t rec[0x50];
    vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x228);
    fn();                       /* fills rec */
    FUN_00117cc4(p1, (word_t)rec, 0x50);
}

/* FUN_0009c9f0 @ 0x0009c9f0   (est. launcher_capture_40)
 * Ghidra: void FUN_0009c9f0(undefined8 *)
 * Copies a 0x40-byte record from vtable slot 0x230 into param_1.
 * Confidence: low */
void FUN_0009c9f0(word_t *p1)
{
    byte_t rec[0x40];
    vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x230);
    fn();
    p1[0] = *(word_t *)(rec + 0x00);
    p1[1] = *(word_t *)(rec + 0x08);
    p1[2] = *(word_t *)(rec + 0x10);
    p1[3] = *(word_t *)(rec + 0x18);
    p1[4] = *(word_t *)(rec + 0x20);
    p1[5] = *(word_t *)(rec + 0x28);
    *(word_t *)((byte_t *)p1 + 0x30) = *(word_t *)(rec + 0x30);
    *(word_t *)((byte_t *)p1 + 0x38) = *(word_t *)(rec + 0x38);
}

/* ------------------------------------------------------------------ *
 * Region utility helpers.
 * ------------------------------------------------------------------ */

/* FUN_00098dbc @ 0x00098dbc   (est. region_range_valid)
 * Ghidra: void FUN_00098dbc(ulong)
 * Validates that the region described by the launcher object (x20) can host a
 * range of the given size. Panics if the region bounds are inconsistent or if
 * the new range would overlap an already-mapped span at both ends.
 * Confidence: medium
 * Notes: object fields +0x20 (start), +0x28 (end), +0x70 (map start),
 *   +0x78 (map end); panics via SoftwareBreakpoint at 0x98e10/0x98e14;
 *   "Unexpectedly mapped on both ends" via FUN_00002874. */
word_t FUN_00098dbc(word_t size)
{
    word_t *self = sk_launcher();   /* unaff_x20 */
    word_t start = self[4];       /* +0x20 */
    word_t end   = self[5];       /* +0x28 */
    word_t ms    = self[0x70 / 8];
    word_t me    = self[0x78 / 8];

    if (end < ms) {
        FUN_001afa84(0xb, 2, 0xd00000000000000e, 0, 0, 0, 0); /* SoftwareBreakpoint(1,0x98e10) */
    }
    if (end - ms <= size) {
        if (ms < size) {
            FUN_001afa84(0xb, 2, 0xd00000000000000f, 0, 0, 0, 0); /* SoftwareBreakpoint(1,0x98e14) */
        }
        if (ms - size <= start) {
            /* Newly mapped span overlaps the region on both ends. */
            FUN_00002874((word_t)"Unexpectedly mapped on both ends");
            FUN_0009e124();
            FUN_0009e1fc(0);
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* noreturn */
        }
    }
    return 0;
}

/* FUN_0009a780 @ 0x0009a780   (est. region_range_valid_wrap)
 * Ghidra: void FUN_0009a780(undefined8 *, undefined8, undefined8)
 * Wrapper: calls FUN_00098dbc(size) and stores the result into *param_1.
 * Confidence: medium */
word_t FUN_0009a780(word_t *out, word_t p2, word_t size)
{
    *out = FUN_00098dbc(size);
    return *out;
}

/* FUN_00098e38 @ 0x00098e38   (est. region_contains)
 * Ghidra: uint FUN_00098e38(ulong, ulong)
 * Returns 1 if the range [param_1, param_1+param_2) is fully contained in the
 * launcher's address-space region (checked via FUN_0016c700). Returns 0
 * otherwise. Panics on carry overflow.
 * Confidence: medium */
word_t FUN_00098e38(word_t base, word_t len)
{
    if (base <= base + len) {
        word_t *as = (word_t *)0;   /* self+0x58 */
        FUN_0036b270(as);
        word_t ok = FUN_0016c700(base, base + len);
        FUN_0036b118(as);
        return (ok ^ 0xffffffffffffffff) & 1;
    }
    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x98ea8) */
}

/* FUN_00098eb8 @ 0x00098eb8   (est. region_map_pte)
 * Ghidra: void FUN_00098eb8(ulong, long *, undefined8)
 * Maps a page-aligned range of an address-space region: if the region is in
 * "mapped" mode (byte +0xc0 == 1), it consults the region's map callback
 * (vtable(*param_2)+0x80), validates the 0x4000-byte span via FUN_0016c700,
 * and installs the mapping through the vtable 0x2a8 slot.
 * Confidence: medium
 * Notes: offset base = param_1 >> 3 & 0x1fffffffffffc000; span 0x4000. */
void FUN_00098eb8(word_t p1, word_t *p2, word_t p3)
{
    if (*(byte_t *)0xc0 == 0x01) {          /* self->mode == mapped */
        cl4_pair_t r = ((cl4_pair_t (*)(void))(*(vfn_t *)(*p2 + 0x80)))();
        word_t ok = thunk_FUN_0016d4e8();
        FUN_0008396c(r.lo, r.hi, p3);
        if ((ok & 1) == 0) {
            word_t base = p1 >> 3 & 0x1fffffffffffc000;
            word_t *as = (word_t *)0;       /* self+0x58 */
            FUN_0036b270(as);
            word_t v = FUN_0016c700(base, base + 0x4000);
            FUN_0036b118(as);
            if (v & 1) {
                FUN_00153270();
                FUN_0008e328(0);
                /* vtable 0x2a8(base, 0, 0x4000) */
                ((void (*)(word_t, int, word_t))(*(vfn_t *)(*p2 + 0x2a8)))(base, 0, 0x4000);
            }
        }
    }
}

/* FUN_000991f8 @ 0x000991f8   (est. region_create_async)
 * Ghidra: undefined8 FUN_000991f8(void)
 * Kicks off an asynchronous region creation: calls the vtable 0x80 slot with
 * the FUN_0009d094 callback and returns the recorded result.
 * Confidence: medium */
word_t FUN_000991f8(void)
{
    word_t *self = sk_launcher();
    word_t ret;
    FUN_0008e328(0);
    vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x80);
    FUN_0036b270((void *)self[0x68 / 8]);
    /* fn(&ret, FUN_0009d094, stack, obj) */
    ((void (*)(word_t *, void *, void *, word_t))fn)(&ret, (void *)&FUN_0009d094, 0, self[0x68 / 8]);
    FUN_0036b118((void *)self[0x68 / 8]);
    return ret;
}

/* FUN_000992b8 @ 0x000992b8   (est. region_create_store)
 * Ghidra: void FUN_000992b8(undefined8 *, undefined8, undefined8, ...)
 * Calls FUN_00099010 to create a region and stores the result into *param_1.
 * Confidence: medium */
word_t FUN_000992b8(word_t *out, word_t a, word_t b, word_t c, word_t d,
                    word_t e, word_t f, word_t g)
{
    *out = FUN_00099010(a, b, c, d, e, f, g);
    return *out;
}

/* FUN_00099310 @ 0x00099310   (est. launcher_init_slot)
 * Ghidra: void FUN_00099310(void)
 * Runs the launcher's slot-0x80 init callback with the FUN_0009e26c target.
 * Confidence: low */
void FUN_00099310(void)
{
    FUN_0009e280();
    FUN_0007c0b8();
    vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x80);
    FUN_0036b270((void *)0);
    FUN_0009e26c(0x67b140);
    fn();
    FUN_0036b118((void *)0);
}

/* FUN_00099398 @ 0x00099398   (est. region_commit)
 * Ghidra: void FUN_00099398(long, long)
 * Commits a built region: if the region's entry count (param_1+0x10) is
 * non-negative, publishes it through the vtable 0x98 slot with the element
 * list (param_2). Otherwise panics "Unexpected EK region".
 * Confidence: medium */
void FUN_00099398(word_t p1, word_t p2)
{
    word_t count = *(word_t *)(p1 + 0x10);
    if ((word_t)((long)count) < (word_t)(-1) >> 0) {
        word_t list = 0;
        if (*(word_t *)(p2 + 0x10) != 0) {
            list = p2;
        }
        FUN_000027e8(0);
        vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x98);
        FUN_0036b270((void *)count);
        ((void (*)(word_t, int, int, int))fn)(list, 0, 0, 1);
        FUN_00093c60(count);
        return;
    }
    FUN_00002874((word_t)"Unexpected EK region");
    FUN_0009e124();
    FUN_0009e1fc(0);
    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);
}

/* FUN_00098b60 @ 0x00098b60   (est. launcher_teardown)
 * Ghidra: void FUN_00098b60(void)
 * Tears down the launcher object (x20): releases every list/object field and
 * the retained message word. Used by the destructor paths.
 * Confidence: medium */
void FUN_00098b60(void)
{
    word_t *self = sk_launcher();
    FUN_0006c454(*(word_t *)((byte_t *)self + 0x10) & 0xffff);
    FUN_000026e8((word_t)((byte_t *)self + 0x30));
    FUN_0036b118((void *)self[0x58 / 8]);
    FUN_0036b118((void *)self[0x68 / 8]);
    FUN_0036b118((void *)self[0x80 / 8]);
    FUN_0036b118((void *)self[0x88 / 8]);
    FUN_0036b118((void *)self[0x90 / 8]);
    FUN_0036b118((void *)self[0x98 / 8]);
    FUN_0036b118((void *)self[0xa0 / 8]);
    FUN_0036b118((void *)self[0xa8 / 8]);
    FUN_003a25d4(self[0xb8 / 8]);
}

/* FUN_00098bd0 / FUN_00098bd4 @ 0x98bd0/0x98bd4 (est. launcher_destroy)
 * Ghidra: void FUN_00098bd0(void) / void FUN_00098bd4(void)
 * Destructor: run teardown then flush the log buffer.
 * Confidence: medium */
void FUN_00098bd0(void) { FUN_00098b60(); FUN_0036b6ac(0, 0, 0); }
void FUN_00098bd4(void) { FUN_00098b60(); FUN_0036b6ac(0, 0, 0); }

/* FUN_00098bf8 @ 0x00098bf8   (est. launcher_dump_regions)
 * Ghidra: void FUN_00098bf8(void)
 * Logs a "Dumping Region" header, then walks the region list, invoking each
 * region's dump callback (vtable(*p)+0x88) and emitting a "Region (...)":
 * line per entry.
 * Confidence: medium
 * Notes: string words 0x20676e69706d7544 ("Dumping") / 0xed0000203a535645
 *   ("EVS:..."); per-region words 0x28206e6f69676552 ("Region ("). */
void FUN_00098bf8(void)
{
    word_t t = FUN_0008e0d4();
    word_t hdr = FUN_0036a9a0(t, (void *)0);
    *(word_t *)(hdr + 0x18) = 0x4baeb8;
    *(word_t *)(hdr + 0x10) = 0x4baeb0;
    *(word_t *)(hdr + 0x38) = 0x6753a0;
    *(word_t *)(hdr + 0x20) = 0x20676e69706d7544;   /* "Dumping" */
    *(word_t *)(hdr + 0x28) = 0xed0000203a535645;   /* "EVS: ..." */
    FUN_00002804(0);
    FUN_0036b588(hdr);
    FUN_00002688();
    FUN_0036b6ac(0, 0x20, 7);

    word_t list = ((word_t (*)(word_t))(*(vfn_t *)(*sk_launcher() + 0x210)))(0x210);
    word_t count = *(word_t *)(list + 0x10);
    if (count != 0) {
        word_t *slot = (word_t *)(list + 0x20);
        do {
            word_t *p = (word_t *)*slot;
            word_t line = FUN_0036a9a0(t, (void *)0);
            *(word_t *)(line + 0x18) = 0x4baeb8;
            *(word_t *)(line + 0x10) = 0x4baeb0;
            vfn_t fn = *(vfn_t *)(*p + 0x88);
            FUN_0036b270(p);
            fn();
            thunk_FUN_002acbb8(0x29, 0xe100000000000000);
            *(word_t *)(line + 0x38) = 0x6753a0;
            *(word_t *)(line + 0x20) = 0x28206e6f69676552;   /* "Region (" */
            *(word_t *)(line + 0x28) = 0xe800000000000000;
            FUN_00002804(0);
            FUN_0036b118(p);
            FUN_0036b588(line);
            FUN_00002688();
            FUN_0036b6ac(0, 0x20, 7);
            count--;
            slot++;
        } while (count != 0);
    }
    FUN_0036b118((void *)list);
}

/* FUN_0009a6ec @ 0x0009a6ec   (est. launcher_slot_80_region)
 * Ghidra: undefined8 FUN_0009a6ec(void)
 * Runs the vtable 0x80 callback with the FUN_0009d100 target and returns the
 * recorded result.
 * Confidence: low */
word_t FUN_0009a6ec(void)
{
    word_t ret;
    FUN_0009e280();
    FUN_0007c0b8();
    vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x80);
    FUN_0036b270((void *)0);
    ((void (*)(word_t *, void *, void *, word_t))fn)(&ret, (void *)&FUN_0009d100, 0, 0x677790);
    FUN_0036b118((void *)0);
    return ret;
}

/* FUN_0009a7b4 @ 0x0009a7b4   (est. launcher_slot_80_b)
 * Ghidra: void FUN_0009a7b4(undefined8 *)
 * Runs the vtable 0x80 callback after FUN_0009e26c(0x67b140), then switches on
 * a 16-bit field of *param_1.
 * Confidence: low */
void FUN_0009a7b4(word_t *p1)
{
    FUN_0009e280();
    FUN_0007c0b8();
    vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x80);
    FUN_0036b270((void *)0);
    FUN_0009e26c(0x67b140);
    fn();
    FUN_0036b118((void *)0);
    /* switch on *(ushort*)(p1 + 7) */
}

/* FUN_0009b430 @ 0x0009b430   (est. launcher_map_op)
 * Ghidra: undefined8 FUN_0009b430(undefined8,...)
 * Map operation front-end: runs the vtable 0x80 callback with the FUN_0009d190
 * target and returns its result.
 * Confidence: low */
word_t FUN_0009b430(word_t p1, word_t p2, word_t p3, word_t p4, byte_t p5,
                    byte_t p6, word_t p7, byte_t p8)
{
    word_t ret;
    FUN_0009e280();
    FUN_0007c0b8();
    vfn_t fn = *(vfn_t *)(*sk_launcher() +  0x80);
    FUN_0036b270((void *)0);
    ((void (*)(word_t *, void *, void *, word_t))fn)(&ret, (void *)&FUN_0009d190, 0, 0x677790);
    FUN_0036b118((void *)0);
    return ret;
}

/* FUN_0009b4d8 @ 0x0009b4d8   (est. launcher_map_vtable_2a8)
 * Ghidra: void FUN_0009b4d8(undefined8 *, long *, ...)
 * Calls the vtable 0x2a8 slot (map) with 8 args and stores the result.
 * Confidence: low */
word_t FUN_0009b4d8(word_t *out, word_t *obj, word_t a, word_t b, word_t c,
                    word_t d, word_t e, word_t f)
{
    word_t r = ((word_t (*)(int, int, word_t, word_t, word_t, word_t, word_t, word_t, int))
                (*(vfn_t *)(*obj + 0x2a8)))(0, 1, a, b, c, d, e, f, 0);
    *out = r;
    return r;
}

/* FUN_0009b564 @ 0x0009b564   (est. launcher_panic_raw_as)
 * Ghidra: void FUN_0009b564(void)
 * Panics with the "launcher Raw Address Space manager" message.
 * Confidence: medium (string matched) */
void FUN_0009b564(void)
{
    FUN_00002874((word_t)"launcher Raw Address Space manager");
    FUN_0009e124();
    FUN_0009e1fc(0);
    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);
}

/* FUN_0009c798 @ 0x0009c798   (est. launcher_find_cap_wrap)
 * Ghidra: void FUN_0009c798(void)
 * Wrapper: calls the capability-lookup FUN_0009c7bc.
 * Confidence: medium */
void FUN_0009c798(void) { FUN_0009c7bc(); }

/* FUN_0009c7bc @ 0x0009c7bc   (est. launcher_find_cap)
 * Ghidra: undefined8 FUN_0009c7bc(void)
 * Scans the launcher's capability table (vtable 0xa0 -> list) for the first
 * entry whose type word (bits 6..11 of byte +1) is a capability type and whose
 * flag byte +5 is clear; returns the matching cap, or panics
 * "InternalExclaveLauncher_CNodeAll" if none is found.
 * Confidence: medium
 * Notes: list entries are 8-byte caps; checks FUN_0001c294(word, 6). */
word_t FUN_0009c7bc(void)
{
    word_t *self = sk_launcher();
    word_t *list = (word_t *)FUN_0036a261c((void *)0);
    word_t n = *(word_t *)((byte_t *)list + 0x10);
    word_t *slot = (word_t *)((byte_t *)list + 0x30);
    word_t i = 0;
    for (;;) {
        if (i == n) {
            FUN_001afa84(0xb, 2, 0xd000000000000029, 0x80000000005c16b0,
                         (word_t)"InternalExclaveLauncher_CNodeAll", 0x2c, 2, 0x38);
        }
        if (n <= i) break;
        if (*(byte_t *)((byte_t *)slot + 5) == 0) {
            word_t cap = *slot;
            if (FUN_0001c294(*(byte_t *)((byte_t *)slot + 1), 6) & 1) {
                FUN_0036b118(list);
                return cap;
            }
        }
        slot++;
        i++;
    }
    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c868) */
}

/* FUN_0009cf58 @ 0x0009cf58   (est. vec_sort_compact)
 * Ghidra: void FUN_0009cf58(long *)
 * Compact-sorts the vector *param_1: ensures capacity, then either grows and
 * recursively sorts the halves (FUN_0009dddc) or bulk-sorts (FUN_0009da34).
 * Confidence: low
 * Notes: uses FUN_003a261c / thunk_FUN_0007bebc / FUN_0029369c. */
void FUN_0009cf58(word_t *p1)
{
    word_t v = *p1;
    if ((FUN_003a261c((void *)v) & 1) == 0) {
        v = thunk_FUN_0007bebc(v);
        *p1 = v;
    }
    word_t n = *(word_t *)(v + 0x10);
    word_t loc[2];
    loc[0] = v + 0x20;
    loc[1] = n;
    word_t l2 = FUN_0029369c(n);
    if ((word_t)((long)l2) < (word_t)((long)n)) {
        FUN_0009dddc(n >> 1, (word_t)loc, l2);
        FUN_0036b118((void *)0);
    } else if (n != 0) {
        FUN_0009da34(0, n, 1, loc);
    }
}

/* FUN_0009d014 @ 0x0009d014   (est. msg_recv_forward)
 * Ghidra: undefined8 FUN_0009d014(undefined8, undefined8)
 * Forwards a message receive: invokes the out-of-slice message handler
 * (function-pointer global at 0xd350ff2939000d19) and returns param_2.
 * Confidence: low
 * Notes: dereferences the indirect global _DAT_d350ff2939000d19. */
word_t FUN_0009d014(word_t p1, word_t p2)
{
    /* (*_DAT_d350ff2939000d19)(param_2, param_1) */
    ((void (*)(word_t, word_t))0)(p2, p1);
    return p2;
}

/* FUN_0009d068 @ 0x0009d068   (est. launcher_pair_64f988)
 * Ghidra: undefined1 [16] FUN_0009d068(void)
 * Returns the 16-byte value {0x64f988, 0} (a static descriptor).
 * Confidence: low */
cl4_pair_t FUN_0009d068(void)
{
    cl4_pair_t r;
    r.lo = 0x64f988;
    r.hi = 0;
    return r;
}

/* ---- vtable-slot wrapper pairs (FUN_0009d0xx/9d1xx) that forward the
 *      launcher object's fields to the corresponding implementation ---- */
void FUN_0009d094(void) { FUN_000992b8((word_t *)0x10, 0x18, 0x20, 0x28, 0x30, 0x38, 0x40, 0x48); }
void FUN_0009d098(void) { FUN_0009d094(); }
void FUN_0009d0c0(void) { FUN_00099398(*(word_t *)0x18, *(word_t *)0x20); }
void FUN_0009d0c4(void) { FUN_0009d0c0(); }
void FUN_0009d0dc(void) { FUN_0009955c(*(word_t *)0x10, (word_t *)0x18, *(byte_t *)0x20, *(byte_t *)0x21); }
void FUN_0009d0e0(void) { FUN_0009d0dc(); }
void FUN_0009d100(void) { FUN_0009a780((word_t *)0x10, *(word_t *)0x18, 0); }
void FUN_0009d104(void) { FUN_0009d100(); }
void FUN_0009d11c(void) { FUN_0009a96c((word_t *)0x10, *(word_t *)0x18); }
void FUN_0009d120(void) { FUN_0009d11c(); }
void FUN_0009d190(void) { FUN_0009b4d8((word_t *)0x10, (word_t *)0x18, 0x20, 0x28, 0x30, 0x38, 0x39, 0x3a); }
void FUN_0009d194(void) { FUN_0009d190(); }

/* FUN_0009d224/0009d270/0009d2bc: call a vtable slot and store the result. */
void FUN_0009d224(word_t *p1) { FUN_000027e8(0); *p1 = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0x1c8)))(); }
void FUN_0009d270(word_t *p1) { FUN_000027e8(0); *p1 = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0x1e0)))(); }
void FUN_0009d2bc(word_t *p1) { FUN_000027e8(0); *p1 = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0x1f8)))(); }

/* FUN_0009d304 @ 0x0009d304   (est. launcher_slot_200)
 * Ghidra: void FUN_0009d304(undefined8 *)
 * Calls the vtable 0x200 slot.
 * Confidence: low */
void FUN_0009d304(word_t *p1)
{
    FUN_000027e8(*p1);
    ((vfn_t)(*(vfn_t *)(*sk_launcher() + 0x200)))();
}

/* ---- capability/PTE descriptor field manipulators ---- */

/* FUN_0009d360: write low 56 bits of param_2, preserving byte 7. */
void FUN_0009d360(word_t *p1, word_t p2)
{
    *p1 = (p2 & 0xffffffffffffff) | ((word_t)*(byte_t *)((byte_t *)p1 + 7) << 0x38);
}
/* FUN_0009d370: set byte 7. */
void FUN_0009d370(word_t p1, byte_t b) { *(byte_t *)(p1 + 7) = b; }
/* FUN_0009d378: write +0x10. */
void FUN_0009d378(word_t p1, word_t v) { *(word_t *)(p1 + 0x10) = v; }
/* FUN_0009d380: set bit 0 of +0x18. */
void FUN_0009d380(word_t p1, word_t v) { *(word_t *)(p1 + 0x18) = (*(word_t *)(p1 + 0x18) & ~1ull) | v; }
/* FUN_0009d398: write bits [12..51] of +0x10 (shifted field). */
void FUN_0009d398(word_t p1, word_t v) { *(word_t *)(p1 + 0x10) = (*(word_t *)(p1 + 0x10) & 0xffffff0000000000ull) | ((v >> 0xc) & 0xffffffffffull); }
/* FUN_0009d3a8: write low 56 bits of +8 preserving byte +0xf. */
void FUN_0009d3a8(word_t p1, word_t v) { *(word_t *)(p1 + 8) = (v & 0xffffffffffffff) | ((word_t)*(byte_t *)(p1 + 0xf) << 0x38); }
/* FUN_0009d3b8: write bits [12..51] of +8. */
void FUN_0009d3b8(word_t p1, word_t v) { *(word_t *)(p1 + 8) = (*(word_t *)(p1 + 8) & 0xfffff00000000000ull) | ((v >> 0xc) & 0xfffffffffffull); }
/* FUN_0009d3c8: write bits [12..51] of +0x10. */
void FUN_0009d3c8(word_t p1, word_t v) { *(word_t *)(p1 + 0x10) = (*(word_t *)(p1 + 0x10) & 0xfffff00000000000ull) | ((v >> 0xc) & 0xfffffffffffull); }
/* FUN_0009d3d8: write byte 7 (<<0x2c) of +8. */
void FUN_0009d3d8(word_t p1, word_t v) { *(word_t *)(p1 + 8) = (*(word_t *)(p1 + 8) & 0xfff0000000000000ull) | (*(word_t *)(p1 + 8) & 0xfffffffffffull) | ((v & 0xff) << 0x2c); }
/* FUN_0009d3e8: write +0x18. */
void FUN_0009d3e8(word_t p1, word_t v) { *(word_t *)(p1 + 0x18) = v; }
/* FUN_0009d3f0: write 16-bit +0x16. */
void FUN_0009d3f0(word_t p1, word_t v) { *(unsigned short *)(p1 + 0x16) = (unsigned short)v; }

/* FUN_0009e2a0 @ 0x0009e2a0   (est. sk_frame_alloc)
 * Ghidra: void FUN_0009e2a0(undefined8, undefined8)
 * Allocates a frame object of size param_2 and type 0x1808 and returns it.
 * Confidence: medium */
word_t FUN_0009e2a0(word_t desc, word_t size)
{
    return FUN_00085a54(desc, size, 0x11, 0x1808, 0);
}

/* FUN_00099010 @ 0x00099010   (est. region_create)
 * Ghidra: long FUN_00099010(ulong,ulong,undefined8,long,undefined8,undefined8,undefined8)
 * Creates a new address-space region anchored at [param_1, param_1+param_2).
 * Builds a descriptor via FUN_0016d328, registers it on the region lists,
 * publishes a 0x19-byte region record, and (when the range lies inside the
 * launcher's region window) extends the region bounds and maps each page via
 * the vtable 0x258 slot. Returns the published region record.
 * Confidence: medium */
word_t FUN_00099010(word_t base, word_t len, word_t c, word_t d, word_t e,
                    word_t f, word_t g)
{
    word_t *self = sk_launcher();
    word_t desc, rec;
    word_t stack[4];

    FUN_0036b270((void *)self[0x58 / 8]);
    desc = FUN_0016d328(base, len, c, d, e, f, g);
    FUN_0036b118((void *)self[0x58 / 8]);

    if (0) {   /* unaff_x21 error flag */
        return 0;
    }
    FUN_0009e228();
    FUN_0036a1a0(0, 0, 0, 0);
    FUN_0036b2d0(desc, 2);
    thunk_FUN_00070594(0);
    FUN_0036a20c((word_t)stack);

    rec = FUN_0036a940(FUN_00093e98(0), 0x19, 7);
    *(word_t *)(rec + 0x10) = desc;
    *(byte_t *)(rec + 0x18) = 0;

    FUN_0009e228();
    FUN_0036a1a0(0, 0, 0, 0);
    FUN_0036b270((void *)rec);
    thunk_FUN_00070594(0);
    FUN_0036a20c((word_t)stack);

    if (self[4] <= base && base < self[5]) {
        if (base + len < base) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x991f8) */
        }
        word_t end = base + len;
        if (end <= self[0x78 / 8]) end = self[0x78 / 8];
        if (self[0x70 / 8] <= base) base = self[0x70 / 8];
        self[0x70 / 8] = base;
        self[0x78 / 8] = end;
        word_t np = FUN_00093230();
        word_t off = 0;
        word_t cnt = (np >> 0xe) + 1;
        while (--cnt) {
            np = FUN_000931d4();
            word_t pa = np + off;
            if (pa < np) {
                FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x991f4) */
            }
            off += 0x4000;
            word_t t = FUN_0008e328(pa);
            /* vtable 0x258(t, rec) */
            ((void (*)(word_t, word_t))0)(t, rec);
        }
    }
    FUN_0036b118((void *)desc);
    return rec;
}

/* FUN_00099444 @ 0x00099444   (est. region_alloc_dispatch)
 * Ghidra: void FUN_00099444(undefined8, byte)
 * Dispatches a region allocation based on the region mode byte (+0xc1):
 * mode 0 and a zero mask selects FUN_00097b94, non-zero mask selects
 * FUN_00097920, and mode 1 selects FUN_00097a58. Finally calls the object's
 * vtable 0x80 slot with the FUN_0009d0dc target.
 * Confidence: low
 * Notes: strange artifact (*(code *)&SUB_9132414a9000018a)() is ignored. */
void FUN_00099444(word_t p1, byte_t mask)
{
    byte_t mode = *(byte_t *)0xc1;
    word_t u = FUN_00167a6c(0);
    FUN_0036b270((void *)p1);
    if ((mask & (mode ^ 1) & 1) == 0) {
        if (mode == 0) {
            FUN_00097b94(u, p1);
        } else {
            FUN_00097a58();
        }
    } else {
        FUN_00097920();
    }
    word_t *obj = (word_t *)0;   /* self+0x68 */
    vfn_t fn = *(vfn_t *)(*obj + 0x80);
    FUN_0036b270(obj);
    ((void (*)(void *, void *, word_t))fn)((void *)&FUN_0009d0dc, 0, 0x67b148);
    FUN_0036b118(obj);
}

/* FUN_000986d4 @ 0x000986d4   (est. exclave_launcher_init)
 * Ghidra: void FUN_000986d4(undefined8,...)
 * Constructor for the exclave-launcher object (x20): stores the init-EC
 * capability (+0xb0/+0xb8) and control bytes, allocates the region-descriptor
 * and frame lists, validates the init EC capability (clearing the setup frame
 * for the bootstrap capability), and registers the launcher with the
 * message/supervisor layer. Panics on an invalid region index.
 * Confidence: medium
 * Notes: refs DAT_00657778 (empty list), string BuildRoot; FUN_0036a940
 *   (obj,size,7) sizes objects; FUN_0009d078 is the register sc stub. */
void exclave_launcher_init(word_t cap_lo, word_t cap_hi, word_t p1, word_t p2,
                           word_t ec_lo, word_t ec_hi, byte_t f1,
                           word_t p8, word_t p9, byte_t f2)
{
    word_t *self = sk_launcher();
    word_t desc[9];
    word_t frame[8];
    word_t r1, r2, r3, as, asv, obj, fc;
    word_t *list;

    self[0xc8 / 8] = p8;
    *(byte_t *)((byte_t *)self + 0x60) = 0;
    self[0x90 / 8] = (word_t)&cl4_empty_list;
    self[0xa8 / 8] = (word_t)&cl4_empty_list;
    *(byte_t *)((byte_t *)self + 0xc1) = f2;
    self[3] = cap_lo;
    self[0xb0 / 8] = ec_lo;
    self[0xb8 / 8] = ec_hi;
    *(byte_t *)((byte_t *)self + 0xc0) = f1;

    r1 = FUN_0036a940(FUN_000aa6d0(0), 0x10, 7);
    r2 = FUN_0036a940(FUN_000ec964(0), 0x10, 7);
    r3 = FUN_0036a940(FUN_0006f800(0), 0x10, 7);
    FUN_0006e7c0(cap_hi, (word_t)desc);
    FUN_0036b270((void *)p9);
    list = (word_t *)FUN_0009781c(r1, r2, r3, (word_t)desc);
    self[0xa0 / 8] = (word_t)list;

    for (int k = 0; k < 5; k++) frame[k] = 0;
    vfn_t install = *(vfn_t *)(*list + 0x1f0);
    FUN_0036b270((void *)0);
    ((void (*)(word_t *, int, int, int, word_t *))install)(desc, 6, 0, 0, frame);
    FUN_0036b118((void *)list);
    FUN_0009e18c(0);
    FUN_0000276c((word_t)frame, 0, 0);

    word_t idx = FUN_0006c2b0(desc[0]);
    *(short *)((byte_t *)self + 0x10) = (short)idx;
    if ((word_t)((long)idx) < 1) {
        FUN_0009e160();
        FUN_0009e2b4();
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x98b60) */
    }

    self[4] = p1;
    self[5] = p2;

    as = FUN_0036a940(FUN_000e1368(0), 0x30, 7);
    FUN_0036b270((void *)self[0xa0 / 8]);
    asv = FUN_000dfd3c(desc[0], self[0xa0 / 8]);
    obj = FUN_0036a940(FUN_00002534(0x64f968, 0x4c14c0), 0x18, 7);
    *(word_t *)(obj + 0x10) = asv;
    self[0x58 / 8] = obj;

    FUN_0036a1a0(self[0xa8 / 8], (word_t)frame, 1, 0);
    FUN_0036b118((void *)self[0xa8 / 8]);
    self[0xa8 / 8] = (word_t)&cl4_empty_list;

    fc = FUN_0036a940(FUN_000ec8f8(0), 0x18, 7);
    *(word_t *)(fc + 0x10) = FUN_0036a804(0x10, ~0ull);
    self[0x68 / 8] = fc;

    word_t v0 = self[0xb0 / 8], v1 = self[0xb8 / 8];
    if ((v0 == 0xd000000000000012 && v1 == 0x80000000005c13e0) ||
        (FUN_002a0cf8(v0, v1, 0xd000000000000013, 0x80000000005c13e0, 0) & 1)) {
        for (int k = 0; k < 7; k++) self[(0xd0 + k * 8) / 8] = 0;
        *(byte_t *)((byte_t *)self + 0x108) = 0xff;
    } else {
        word_t *as2 = (word_t *)self[0xa0 / 8];
        FUN_0036b270(as2);
        FUN_000937b8((word_t)frame);
        FUN_0036b118(as2);
        self[0xd0 / 8] = frame[0];
        self[0xd8 / 8] = frame[1];
        self[0xe0 / 8] = frame[2];
        self[0xe8 / 8] = frame[3];
        self[0xf0 / 8] = frame[4];
        self[0xf8 / 8] = frame[5];
    }

    FUN_0036a1a0(self[0xc8 / 8], (word_t)frame, 0, 0);
    FUN_0009d078(desc[0], self[0xc8 / 8]);
    FUN_00151974();
    FUN_0009e20c();
    FUN_0009e258(0, 0, (word_t)sk_fatal_str);
    FUN_00151a6c(0, 0, (word_t)sk_fatal_str, 0, 0, 0, 0, 0);
    FUN_0036b118((void *)p9);
    FUN_000026e8(cap_hi);
}

/* FUN_0009c4a0 @ 0x0009c4a0   (est. exclave_init_ec)
 * Ghidra: undefined8 FUN_0009c4a0(void)
 * Locates the single init-EC capability, enters it (FUN_0009d1c0), waits for
 * its return (FUN_0009d1e0 / FUN_0009d20c), and finalizes the launcher.
 * Panics if the init endpoint does not exist or if there is not exactly one
 * init EC cap. Returns 1 on success.
 * Confidence: medium
 * Notes: strings "__Init endpoint doesn't exist", "__Not just one init EC
 *   cap", "Launcher abort: exclave address space"; stack canary
 *   -0x2c8502b44bfffed6 at the tail. */
word_t FUN_0009c4a0(void)
{
    word_t rec[7];
    word_t result = 0;
    const word_t CANARY = 0xd37afd4bb40012a;
    word_t canary = CANARY;

    FUN_000027e8(0);
    ((vfn_t)(*(vfn_t *)(*sk_launcher() + 0x228)))();   /* fill rec */

    word_t init_ep = rec[0];     /* local_48 */
    if (init_ep == 0) {
        /* __Init endpoint doesn't exist */
        FUN_0009e240();
        FUN_0009e218((word_t)"__Init endpoint doesn't exist");
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);
    } else if (*(word_t *)(init_ep + 0x10) != 0 && *(word_t *)(init_ep + 0x10) == 1) {
        if ((*(unsigned short *)(rec + 0x10) & 0xc000) == 0) {
            word_t cap = *(word_t *)(init_ep + 0x68);
            word_t u = FUN_00167a6c(0);
            FUN_0036b270((void *)0);
            FUN_00097ccc(u);
            result = 0;
            word_t init_ec = FUN_00034f70();
            if (init_ec == 0) {
                FUN_00085374((word_t)"initCall", 10, 2, 0x2c8);
            }
            FUN_0009d1c0(rec[0], init_ec, cap);
            FUN_00151974();
            FUN_0009e20c();
            FUN_0009e174();
            FUN_00151a6c(0, 0, 0, 0, 0, 0, 0, 0);
            FUN_0009d1e0(init_ec, &result);
            FUN_00151974();
            FUN_0009e20c();
            FUN_0009e174();
            FUN_00151a6c(0, 0, 0, 0, 0, 0, 0, 0);
            if (result == 0) {
                if (cl4_verbose == 1) {
                    word_t t = FUN_0008e0d4();
                    word_t line = FUN_0036a9a0(t, 0);
                    *(word_t *)(line + 0x18) = 0x4baeb8;
                    *(word_t *)(line + 0x10) = 0x4baeb0;
                    *(word_t *)(line + 0x38) = 0x6753a0;
                    *(word_t *)(line + 0x20) = 0xd00000000000001b;
                    *(word_t *)(line + 0x28) = 0x80000000005c1640;
                    FUN_00002804(0);
                    FUN_0036b588(line);
                    FUN_00002688();
                    FUN_0036b6ac(0, 0x20, 7);
                }
                FUN_0009d20c(init_ec);
                FUN_004b23d8(init_ec);
                FUN_0009e1e8();
                FUN_0000276c((word_t)rec, 0, 0);
                if (canary == CANARY) {
                    return 1;
                }
                FUN_0011d7e8();   /* noreturn: canary mismatch */
            } else {
                FUN_0009e218((word_t)"Launcher abort: exclave address space");
                FUN_0009e160();
            }
        } else {
            FUN_0009e160();
        }
        FUN_0009e2b4();   /* noreturn */
    } else {
        /* __Not just one init EC cap */
        FUN_0009e240();
        FUN_0009e218((word_t)"__Not just one init EC cap");
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);
    }
    FUN_0009e2b4();   /* noreturn */
    return 0;
}

/* FUN_0009a96c @ 0x0009a96c   (est. exclave_setup_caps)
 * Ghidra: void FUN_0009a96c(long *, long)
 * Walks the endpoint/capability list of param_2, and for each entry issues the
 * map-capability (FUN_0009d414), register-save, badge (FUN_0009d444) and
 * cap-set (FUN_0009d460) supervisor calls to hand the capability to the
 * exclave. The list entries are 0x50-byte cap records; one record is saved
 * into the list at a time.
 * Confidence: low
 * Notes: uses FUN_00093c68(idx) to read CPU registers and FUN_0009d434(idx,v)
 *   to write them; vtable 0x2e8 resolves a page address; panics at 0x9aec0. */
void FUN_0009a96c(word_t *p1, word_t p2)
{
    word_t list;
    word_t cap = p2;
    word_t rec[9];
    word_t page, reg;

    /* Append a 0x50-byte copy of the incoming cap to the launcher list. */
    list = *p1;
    FUN_0036b270((void *)*(word_t *)(list + 0x10));
    list = FUN_0036a1a0(0, 0, 0, 0);
    /* vtable(*list)+0x1f0 fills rec from &cap */
    ((void (*)(word_t *, word_t))0)(rec, cap);
    FUN_0007b238();
    word_t l2 = *(word_t *)(*sk_launcher() +  0x10);
    FUN_0007b414(l2);
    *(word_t *)(*sk_launcher() +  0x10) = l2 + 1;
    FUN_00117cc4(*sk_launcher() +  l2 * 0x50 + 0x20, cap, 0x50);

    word_t cnt = *(word_t *)(*(word_t *)(cap + 0x40) + 0x10);
    word_t *slot = (word_t *)(*(word_t *)(cap + 0x40) + 0x88);
    while (cnt != 0) {
        word_t c0 = slot[-13];
        word_t tgt = slot[0x11];
        word_t kind = ((word_t (*)(void))(*(vfn_t *)(*p1 + 0x2b8)))();
        FUN_0009d3f8(c0, kind);
        FUN_00151974();
        FUN_00151a6c(0, 0, 0, 0, 0, 0, 0, 0);

        if ((word_t)((long)tgt) < 0) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9aec0) */
        }
        word_t pa = ((word_t (*)(word_t))(*(vfn_t *)(*p1 + 0x2e8)))(tgt & 0x7fffffffffffc000);
        if (pa == 0) {
            FUN_0009e18c(0);
            FUN_001afa84(0xb, 2, 0xd000000000000020, 0x80000000005c1790,
                         (word_t)sk_fatal_str, 0x35, 2, 0x164);
        }
        FUN_0009d414(c0, pa, tgt);
        FUN_00151974();
        FUN_00151a6c(0, 0, 0, 0, 0, 0, 0, 0);

        /* Save all general registers and issue the badge/cap-set calls. */
        word_t regs[0x21];
        for (int i = 1; i <= 0x26; i++) regs[i] = FUN_00093c68(i);
        FUN_0009d434(0, c0);
        for (int i = 1; i <= 0x14; i++) FUN_0009d434(i, slot[i - 1]);
        FUN_0009d434(0x15, *(word_t *)(cap + 0x48));
        FUN_0009d434(0x16, slot[0x10]);
        word_t mask = 0;
        for (int i = 1; i <= 0x26; i++) mask |= regs[i];
        FUN_0009d444(c0, mask);
        FUN_00151974();
        FUN_00151a6c(0, 0, 0, 0, 0, 0, 0, 0);

        if (*(byte_t *)((byte_t *)p1 + 0x108) != 0xff) {
            FUN_0009d460(c0, p1[0x1a]);
            FUN_00151974();
            FUN_00151a6c(0, 0, 0, 0, 0, 0, 0, 0);
        }
        cnt--;
        slot += 0x1f;
    }
}

/* FUN_0009af90 @ 0x0009af90   (est. exclave_map_region_frames)
 * Ghidra: ulong FUN_0009af90(ulong,char,long,...)
 * Maps the frames of a region into the exclave address space. Validates the
 * requested span, allocates 0x4000-byte frames, installs each via the vtable
 * 0x90/0xc0 slots, and (when flag bit 0 of param_8 is set) additionally maps
 * the first page. Commits the resulting region via FUN_00099010 and returns
 * the base address.
 * Confidence: low */
word_t FUN_0009af90(word_t base, byte_t mode, word_t size, word_t c, word_t d,
                    word_t e, word_t f, word_t flags, word_t g)
{
    if ((word_t)((long)size) < 0) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9b3d4) */
    }
    word_t span = (size + 0x3fff) & ~0x3fffull;
    word_t extra = (flags & 1) ? 0x4000 : 0;
    word_t total = span + extra;
    if (total < span) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9b3dc) */
    }
    if (mode == 0x01) {
        if ((word_t)((long)total) < 0) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9b3e4) */
        }
        base = FUN_00098dbc(total);
    } else if ((word_t)((long)total) < 0) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9b3e0) */
    }

    if ((FUN_00098e38(base, total) & 1) == 0) {
        FUN_0036993c(0x667b70, 0x6679a0, 0, 0);
        FUN_0036986c();
        return base;
    }

    word_t slot_off = (g & 0x100) ? 0x98 : 0xa0;
    word_t *obj = (word_t *)0;   /* self + slot_off */
    FUN_0036b270(obj);
    word_t np = (span >> 0xe);
    word_t idx = 0;
    word_t *vec = (word_t *)&cl4_empty_list;
    for (word_t k = 0; k < np; k++) {
        word_t pa = base + idx;
        word_t args[5];
        for (int j = 0; j < 5; j++) args[j] = 0;
        ((void (*)(word_t *, int, word_t, byte_t, word_t *))(*(vfn_t *)(*obj + 0x1f0)))
            (args, 3, pa, (byte_t)g & 1, args);
        FUN_0009e18c(0);
        FUN_0000276c(0, 0, 0);
        word_t tok = FUN_00086440(0);
        word_t fr = FUN_0036a940(FUN_00086590(0), 0x50, 7);
        word_t *frame = (word_t *)FUN_0009e2a0(tok, 0x4000);
        ((void (*)(int, word_t))(*(vfn_t *)(*frame + 0x90)))(0, args[0]);
        ((void (*)(void))(*(vfn_t *)(*frame + 0xc0)))();
        if (FUN_003a261c(vec) & 1) {
            vec = (word_t *)FUN_00072d5c(FUN_0006b42c(), vec[2] + 1, 1, (word_t)vec);
        }
        vec[2] = vec[2] + 1;
        vec[vec[2] + 4] = args[0];
        FUN_0036b118(frame);
        idx += 0x4000;
    }
    if ((flags & 1) == 0) {
        extra = 0;
    } else {
        FUN_00153270();
        FUN_00099010(base, 0x4000, FUN_00153270(), FUN_00167c48(), d, e, f);
        extra = 0x4000;
    }
    if (base + extra < base) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9b3ec) */
    }
    word_t rec = FUN_00099010(base + extra, span, FUN_00153270(), FUN_00167c48(), d, e, f);
    word_t cnt = *(word_t *)(rec + 0x10);
    if ((word_t)((long)cnt) >= (word_t)(-1) >> 0) {
        FUN_00002874((word_t)"Unexpected type of ExtVMRegion");
        FUN_0009e124();
        FUN_0009e1fc(0);
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);
    }
    FUN_000027e8(0);
    ((void (*)(word_t, int, int, int))(*(vfn_t *)(*sk_launcher() + 0x98)))((word_t)vec, 0, 0, 1);
    FUN_00093c60(cnt);
    FUN_0036b118(vec);
    FUN_0036b118((void *)rec);
    FUN_0036b118(obj);
    return base;
}

/* FUN_0009bda8 @ 0x0009bda8   (est. cnode_allocator_add)
 * Ghidra: void FUN_0009bda8(void)
 * CNode allocator: ensures there is room for another CNode. Computes the
 * count of allocated slots from the free/used accounting, and if the used
 * count plus slack exceeds the total, pre-allocates a pair of CNodes.
 * Panics with "CnodeAllocator failed to add" when it can't.
 * Confidence: low
 * Notes: strings "CnodeAllocator failed to add"; FUN_0014aedc/FUN_0007eb2c
 *   give free/total; vtable slots 0xd0/0x178/0x1c0. */
void FUN_0009bda8(void)
{
    word_t total = FUN_0014aedc(0x665f60, 0x665cd8);
    word_t free_ = FUN_0007eb2c(0x665f60, 0x665cd8);
    if (free_ == 0) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bf44) */
    }
    FUN_0007c0b8();
    word_t big = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0xd0)))();
    if (total < free_) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bf48) */
    }
    word_t count = 0;
    if (free_ != 0) count = total / free_;
    word_t used = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0x178)))();
    if (count < used) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bf4c) */
    }
    word_t per = 0;
    if (count != 0) per = big / count;
    if (count - used <= big - per * count || big == per * count) {
        word_t u = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0x178)))();
        if (u > 0xfffffffffffffffe) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bf54) */
        }
        word_t n = u + 2;
        while (--n) {
            ((void (*)(word_t))(*(vfn_t *)(*sk_launcher() + 0x1c0)))(0);
        }
    }
    word_t b2 = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0xd0)))();
    word_t u2 = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0x178)))();
    if (u2 <= count) {
        word_t p = 0;
        if (count != 0) p = b2 / count;
        if (count - u2 <= b2 - p * count) {
            FUN_00002874((word_t)"CnodeAllocator failed to add");
            FUN_001afa84(0xb, 2, 0xd00000000000002a, 0x8000000000000000,
                         (word_t)"InternalExclaveLauncher_CNodeAll", 0x2c, 2, 0x47);
        }
        return;
    }
    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bf50) */
}

/* FUN_0009dddc @ 0x0009dddc   (est. sort_vector_alloc)
 * Ghidra: undefined * FUN_0009dddc(long, undefined8, undefined8)
 * Allocates a sort vector of `param_1` element slots, runs the merge sort
 * (FUN_0009d488) over [param_2, param_3), then clears the count. On error the
 * vector is released. Panics if the count is negative.
 * Confidence: low */
void *FUN_0009dddc(word_t n, word_t b, word_t c)
{
    word_t *v;
    if ((word_t)((long)n) >= 0) {
        if (n == 0) {
            v = (word_t *)&cl4_empty_list;
        } else {
            v = (word_t *)thunk_FUN_000f9608(n);
            *(word_t *)((byte_t *)v + 0x10) = n;
        }
        word_t loc[2];
        loc[0] = (word_t)v + 0x20;
        loc[1] = n;
        FUN_0009d488(loc, (word_t)(void *)0, (word_t *)b, c);
        *(word_t *)((byte_t *)v + 0x10) = 0;
        if (0) {   /* unaff_x21 error flag */
            FUN_0036b118(v);
        }
        return v;
    }
    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9de84) */
}

/* FUN_0009da34 @ 0x0009da34   (est. vec_insertion_sort)
 * Ghidra: void FUN_0009da34(long, long, long, long *)
 * Insertion-sorts a sub-range [param_1, param_2) of the vector *param_4,
 * comparing elements via their vtable 0x68 slot (ascending).
 * Confidence: low */
void FUN_0009da34(word_t lo, word_t hi, word_t pos, word_t *p4)
{
    if (pos != hi) {
        word_t base = *p4;
        word_t cap = p4[1];
        word_t *cur = (word_t *)(base + pos * 8);
        while (pos != hi) {
            word_t j = pos - 1;
            if (pos < 0 || cap <= pos || j < 0 || cap <= j) {
                FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint */
            }
            word_t *a = (word_t *)*cur;
            word_t *b = (word_t *)*(word_t *)(base + j * 8);
            FUN_0036b270(a);
            FUN_0036b270(b);
            word_t av = ((word_t (*)(void))(*(vfn_t *)(*a + 0x68)))();
            word_t bv = ((word_t (*)(void))(*(vfn_t *)(*b + 0x68)))();
            FUN_0036b118(a);
            FUN_0036b118(b);
            if (av < bv) {
                word_t tmp = *cur;
                *cur = *(word_t *)(base + j * 8);
                *(word_t *)(base + j * 8) = tmp;
                pos = j;
                cur--;
                if (j == lo) {
                    pos = hi;   /* reached the low end; exit */
                }
            } else {
                pos = hi;       /* in place; exit */
            }
        }
    }
}

/* FUN_0009de84 @ 0x0009de84   (est. vec_merge)
 * Ghidra: undefined8 FUN_0009de84(undefined8 *, undefined8 *, undefined8 *, undefined8 *)
 * Merges two sorted element ranges [param_2, param_3) and the run headed by
 * param_1 into param_4's output area, comparing via the vtable 0x68 slot.
 * Returns 1. This is the classic two-way merge used by the sort.
 * Confidence: low */
word_t FUN_0009de84(word_t *dst, word_t *mid, word_t *end, word_t *src)
{
    word_t n1 = ((word_t)mid - (word_t)dst) / 8;
    word_t n2 = ((word_t)end - (word_t)mid) / 8;
    if (n1 < n2) {
        thunk_FUN_000721b0((word_t)dst, n1, (word_t)src);
        word_t *s = src + n1;
        word_t *a = dst;
        while (src < s && mid < end) {
            word_t *x = (word_t *)*mid;
            word_t *y = (word_t *)*src;
            FUN_0036b270(x);
            FUN_0036b270(y);
            word_t xv = ((word_t (*)(void))(*(vfn_t *)(*x + 0x68)))();
            word_t yv = ((word_t (*)(void))(*(vfn_t *)(*y + 0x68)))();
            FUN_0036b118(x);
            FUN_0036b118(y);
            word_t *pick;
            if (xv < yv) {
                pick = mid;
                mid++;
            } else {
                pick = src;
                src++;
            }
            if (dst != pick) *dst = *pick;
            dst++;
        }
        word_t rem = ((word_t)s - (word_t)src) / 8;
        if (a != dst) {
            FUN_00117d14((word_t)a, (word_t)src, rem << 3);
        }
        return 1;
    }
    /* symmetric second half (merge from the tail) */
    thunk_FUN_000721b0((word_t)mid, n2, (word_t)src);
    word_t *s = src + n2;
    word_t *m2 = mid - 1;
    word_t *e2 = end;
    for (;;) {
        e2--;
        if (mid <= dst || src <= s) break;
        s--;
        word_t *x = (word_t *)*s;
        word_t *y = (word_t *)*m2;
        FUN_0036b270(x);
        FUN_0036b270(y);
        word_t xv = ((word_t (*)(void))(*(vfn_t *)(*x + 0x68)))();
        word_t yv = ((word_t (*)(void))(*(vfn_t *)(*y + 0x68)))();
        FUN_0036b118(x);
        FUN_0036b118(y);
        if (xv < yv) break;
        if (src != e2 + 1) *e2 = *s;
        src = s;
        m2--;
    }
    if (e2 + 1 != mid) *e2 = *m2;
    mid--;
    return 1;
}

/* FUN_0009d488 @ 0x0009d488   (est. vec_merge_sort)
 * Ghidra: void FUN_0009d488(long *, undefined8, long *, long)
 * Bottom-up merge sort over the element vector *param_3 (elements compared via
 * their vtable 0x68 slot). Builds ascending runs, reversing descending runs,
 * extends each run by an insertion-sort tail of up to `param_4` elements,
 * records the runs in a work list, and merges adjacent runs (FUN_0009db84 /
 * FUN_0009de84) using `param_2` as scratch. Runs are {lo,hi} pairs.
 * Confidence: low
 * Notes: vtable 0x68 = element key; many SoftwareBreakpoint bounds panics. */
void FUN_0009d488(word_t *p1, word_t data, word_t *p3, word_t p4)
{
    word_t runs = (word_t)&cl4_empty_list;   /* local_58 */
    word_t base = *p3;
    word_t n = p3[1];
    word_t i = 0;

    while (i < n) {
        word_t j = i + 1;
        if (j < n) {
            word_t *a = (word_t *)*(word_t *)(base + i * 8);
            word_t *b = (word_t *)*(word_t *)(base + j * 8);
            FUN_0036b270(a);
            FUN_0036b270(b);
            word_t ka = ((word_t (*)(void))(*(vfn_t *)(*a + 0x68)))();
            word_t kb = ((word_t (*)(void))(*(vfn_t *)(*b + 0x68)))();
            FUN_0036b118(a);
            FUN_0036b118(b);
            word_t k = j;
            word_t m = j;
            word_t asc = ka < kb;
            while (true) {
                word_t cur = m;
                word_t nx = m + 1;
                if (n <= nx) { j = n; break; }
                a = (word_t *)*(word_t *)(base + nx * 8);
                b = (word_t *)*(word_t *)(base + m * 8);
                FUN_0036b270(a);
                FUN_0036b270(b);
                word_t vn = ((word_t (*)(void))(*(vfn_t *)(*a + 0x68)))();
                word_t vm = ((word_t (*)(void))(*(vfn_t *)(*b + 0x68)))();
                FUN_0036b118(a);
                FUN_0036b118(b);
                m = nx;
                if (asc != (vm < vn)) { j = m; break; }
            }
            /* j = end of the natural run; reverse it if it was descending. */
            if (asc) {
                if (i < j) {
                    word_t lo = i, hi = j;
                    while (lo < --hi) {
                        word_t tmp = *(word_t *)(base + lo * 8);
                        *(word_t *)(base + lo * 8) = *(word_t *)(base + hi * 8);
                        *(word_t *)(base + hi * 8) = tmp;
                        lo++;
                    }
                }
            }
        }
        n = p3[1];
        word_t end = j;
        if (j < n) {
            /* extend the run with an insertion-sort tail of up to p4 elems. */
            word_t lim = i + p4;
            if (n <= lim) lim = n;
            if (j != lim) {
                word_t pos = j;
                while (pos != lim) {
                    word_t t = pos;
                    while (t > i) {
                        word_t *x = (word_t *)*(word_t *)(base + t * 8);
                        word_t *y = (word_t *)*(word_t *)(base + (t - 1) * 8);
                        FUN_0036b270(x);
                        FUN_0036b270(y);
                        word_t xv = ((word_t (*)(void))(*(vfn_t *)(*x + 0x68)))();
                        word_t yv = ((word_t (*)(void))(*(vfn_t *)(*y + 0x68)))();
                        FUN_0036b118(x);
                        FUN_0036b118(y);
                        if (!(xv < yv)) break;
                        word_t tmp = *(word_t *)(base + t * 8);
                        *(word_t *)(base + t * 8) = *(word_t *)(base + (t - 1) * 8);
                        *(word_t *)(base + (t - 1) * 8) = tmp;
                        t--;
                    }
                    pos++;
                }
                end = lim;
            }
        }
        /* record the run {i, end}. */
        if ((FUN_003a261c((void *)runs) & 1) == 0) {
            runs = FUN_000f9680(0, *(word_t *)(runs + 0x10) + 1, 1, runs);
        }
        word_t cnt = *(word_t *)(runs + 0x10);
        if (*(word_t *)(runs + 0x18) >> 1 <= cnt) {
            runs = FUN_000f9680(1 < *(word_t *)(runs + 0x18), cnt + 1, 1, runs);
        }
        *(word_t *)(runs + 0x10) = cnt + 1;
        *(word_t *)(runs + cnt * 0x10 + 0x20) = i;
        *(word_t *)(runs + cnt * 0x10 + 0x28) = end;
        if (*p1 == 0) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9da2c) */
        }
        FUN_0009db84(&runs, data, p3);
        i = end;
    }

    /* Bottom-up: merge recorded runs pairwise into the data array. */
    word_t rcnt = *(word_t *)(runs + 0x10);
    while (rcnt >= 2) {
        word_t *rp = (word_t *)(runs + rcnt * 0x10);
        word_t lo = rp[0];
        word_t mid = rp[2];
        word_t hi = rp[3];
        FUN_0009de84((word_t *)(base + lo * 8), (word_t *)(base + mid * 8),
                     (word_t *)(base + hi * 8), (word_t *)data);
        /* drop the last pair from the run list. */
        rp[0] = lo;
        rp[1] = hi;
        word_t n2 = *(word_t *)(runs + 0x10);
        FUN_00069970((word_t)(rp + 2), (word_t)(n2 - rcnt), (word_t)rp);
        *(word_t *)(runs + 0x10) = n2 - 1;
        rcnt = n2 - 1;
    }
    FUN_0036b118((void *)runs);
}

/* FUN_0009db84 @ 0x0009db84   (est. run_heap_merge)
 * Ghidra: undefined8 FUN_0009db84(long *, undefined8, long *)
 * Merges the newest recorded run (a {lo,hi} pair) into the run-pair work list
 * *param_1, fusing overlapping/adjacent runs so the list stays ordered and
 * non-overlapping. Uses FUN_0009de84 to merge the underlying element ranges in
 * `param_2`. Returns 1 on success.
 * Confidence: low */
word_t FUN_0009db84(word_t *p1, word_t data, word_t *p3)
{
    word_t list = *p1;
    if (1 < *(word_t *)(list + 0x10)) {
        if ((FUN_003a261c((void *)list) & 1) == 0) {
            list = FUN_000f9930(list);
        }
        *p1 = list;
        word_t cnt = *(word_t *)(list + 0x10);
        do {
            word_t k = cnt - 1;
            word_t *entry = (word_t *)(list + cnt * 0x10);   /* last pair */
            word_t lo = entry[0];
            word_t hi = entry[1];
            /* Locate the insertion/fusion point by comparing spans. */
            word_t a_lo = *(word_t *)(list + (k - 1) * 0x10 + 0x20);
            word_t a_hi = *(word_t *)(list + (k - 1) * 0x10 + 0x28);
            word_t span = hi - lo;
            word_t prev_span = a_hi - a_lo;
            word_t idx = k;
            if (span < prev_span) {
                idx = k - 1;
            }
            word_t u = idx - 1;
            if (cnt <= u) {
                FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9dda0) */
            }
            word_t slo = *(word_t *)(list + 0x20 + u * 0x10);
            word_t *sp = (word_t *)(list + 0x20 + idx * 0x10);
            word_t shi = sp[1];
            FUN_0009de84((word_t *)(data + slo * 8), (word_t *)(data + sp[0] * 8),
                         (word_t *)(data + shi * 8), (word_t *)p3);
            if (0) {   /* unaff_x21 error flag */
                return 1;
            }
            if ((FUN_003a261c((void *)list) & 1) == 0) {
                list = FUN_000f9930(list);
            }
            *(word_t *)(list + 0x20 + u * 0x10) = slo;
            *(word_t *)(list + 0x20 + u * 0x10 + 8) = shi;
            *p1 = list;
            FUN_000f98ac(idx);
            list = *p1;
            cnt = *(word_t *)(list + 0x10);
        } while (1 < cnt);
    }
    return 1;
}

/* FUN_0009b5b0 @ 0x0009b5b0   (est. raw_address_space_create)
 * Ghidra: ulong FUN_0009b5b0(void)
 * Creates the "Raw Address Space" for an exclave: computes the total size
 * (pages * 0x4000 + page-table extent), allocates the raw region through the
 * vtable 0x290 slot, allocates and fills the frame descriptors, commits the
 * page-list (vtable 0x98), and finally builds the page-table entries via
 * FUN_0009bf9c. Returns the raw address-space base.
 * Confidence: low
 * Notes: strings "Unexpected type of ExtVmRegion"; vtable slots 0x198/0x1a0/
 *   0xe8/0x268/0x290/0x98/0xe0; FUN_0009e1a0 is a noreturn error helper. */
word_t FUN_0009b5b0(void)
{
    word_t *self = sk_launcher();
    word_t *man = (word_t *)self[0x14];      /* +0xa0 raw-AS manager */
    word_t pages = ((word_t (*)(void))(*(vfn_t *)(*man + 0x198)))();
    if (pages >> 0x32 != 0) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bd08) */
    }
    word_t data_sz = pages * 0x4000;
    word_t pt_sz = ((pages & 0x3ffffffffffff) * 0x2000 + 0x3fff) & ~0x3fffull;
    if (data_sz + pt_sz < data_sz) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bd0c) */
    }
    word_t base = ((word_t (*)(word_t))(*(vfn_t *)(*self + 0x290)))(data_sz + pt_sz);
    if (0) {   /* unaff_x21 error flag */
        FUN_0009e1a0();
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* noreturn */
    }
    word_t pt_base = base + data_sz;
    if (pt_base < base) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bd10) */
    }
    ((void (*)(word_t))(*(vfn_t *)(*man + 0x1a0)))(base);

    word_t tok = FUN_00086440(0);
    word_t desc = FUN_0036a9d4(tok, 0x64e1c0);
    FUN_0036a940(FUN_00086590(0), 0x50, 7);
    word_t *fr = (word_t *)FUN_0009e2a0(desc, pt_sz);

    word_t off = 0;
    word_t *vec = (word_t *)&cl4_empty_list;
    for (word_t n = pt_sz >> 0xe; n != 0; n--) {
        if (pt_base + off < pt_base) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bc80) */
        }
        word_t args[5];
        for (int j = 0; j < 5; j++) args[j] = 0;
        FUN_0006e7c0((word_t)(self + 6), (word_t)args);
        FUN_000027e8(0);
        ((void (*)(word_t *, int, word_t, int, word_t *))(*(vfn_t *)(*sk_launcher() + 0x1f0)))
            (args, 3, pt_base + off, 0, args);
        FUN_0000276c((word_t)args, 0x64e8f8, 0x4c10a0);
        ((void (*)(word_t, word_t))(*(vfn_t *)(*fr + 0x90)))(off, args[0]);
        if ((FUN_003a261c(vec) & 1) == 0) {
            vec = (word_t *)FUN_00072de8(0, *(word_t *)((byte_t *)vec + 0x10) + 1, 1, (word_t)vec);
        }
        word_t c = *(word_t *)((byte_t *)vec + 0x10);
        if (*(word_t *)((byte_t *)vec + 0x18) >> 1 <= c) {
            vec = (word_t *)FUN_00072de8(FUN_0006b42c(), c + 1, 1, (word_t)vec);
        }
        *(word_t *)((byte_t *)vec + 0x10) = c + 1;
        *(word_t *)((byte_t *)vec + c * 0x40 + 0x20) = args[0];
        off += 0x4000;
    }

    FUN_0009bda8();
    word_t tbl = ((word_t (*)(void))(*(vfn_t *)(*man + 0xe8)))();
    word_t tcnt = *(word_t *)(tbl + 0x10);
    FUN_0036b118((void *)0);
    if (tcnt >> 0x32 != 0) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bd18) */
    }
    word_t owner = FUN_00153264();
    word_t dom = FUN_00167c48();
    word_t rec = ((word_t (*)(word_t, word_t, word_t, word_t, word_t, int, int, int))
                  (*(vfn_t *)(*self + 0x268)))
                 ((word_t)self & 0xffffffffffff | 0x6ae1000000000000, base, tcnt << 0xe,
                  owner, dom, 4, 0, 2);
    word_t r1 = *(word_t *)(rec + 0x10);
    if ((word_t)((long)r1) >= (word_t)(-1) >> 0) {
        word_t *commit_list = (word_t *)&cl4_empty_list;
        word_t extra = ((word_t (*)(void))(*(vfn_t *)(*man + 0xe8)))();
        if (*(word_t *)(extra + 0x10) == 0) {
            FUN_0036b118((void *)0);
            commit_list = (word_t *)&cl4_empty_list;
            extra = 0;
        } else {
            word_t src = FUN_0009e28c();
            FUN_00082524(0, 0, 0);
            word_t src_n = *(word_t *)(src + 0x10);
            word_t i = 0;
            for (word_t sl = 0x20; i < src_n; sl += 0x18, i++) {
                word_t v = *(word_t *)(src + sl);
                if (v == 0) {
                    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bd28) */
                }
                word_t c = *(word_t *)(desc + 0x10);
                if (*(word_t *)(desc + 0x18) >> 1 <= c) {
                    FUN_00082524(FUN_0006b42c(), c + 1, 1);
                }
                *(word_t *)(desc + 0x10) = c + 1;
                *(word_t *)(desc + c * 8 + 0x20) = v;
            }
            commit_list = (word_t *)desc;
            if (i != *(word_t *)(src + 0x10)) {
                FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bd1c) */
            }
        }
        FUN_0007c0b8();
        ((void (*)(word_t, int, int, int))(*(vfn_t *)(*sk_launcher() + 0x98)))((word_t)commit_list, 0, 0, 1);

        if (extra == 0) {
            FUN_0036b118(commit_list);
            word_t rec2 = ((word_t (*)(word_t, word_t, word_t, word_t, int, int, int))
                           (*(vfn_t *)(*self + 0x268)))
                          (pt_base, pt_sz, FUN_00153270(), dom, 0, 0, 2);
            word_t r2 = *(word_t *)(rec2 + 0x10);
            if ((word_t)((long)r2) < (word_t)(-1) >> 0) {
                word_t n = *(word_t *)((byte_t *)vec + 0x10);
                word_t *l2 = (word_t *)&cl4_empty_list;
                if (n == 0) {
                    FUN_0036b270((void *)r2);
                    l2 = (word_t *)&cl4_empty_list;
                } else {
                    FUN_0009e28c();
                    FUN_0036b270((void *)r2);
                    FUN_00082524(0, n, 0);
                    word_t *src2 = (word_t *)((byte_t *)vec + 0x20);
                    word_t c = *(word_t *)(desc + 0x10);
                    for (word_t k = 0; k < n; k++, src2++, c++) {
                        word_t v = *src2;
                        if (*(word_t *)(desc + 0x18) >> 1 <= c) {
                            FUN_00082524(FUN_0006b42c(), c + 1, 1);
                        }
                        *(word_t *)(desc + 0x10) = c + 1;
                        *(word_t *)(desc + c * 8 + 0x20) = v;
                    }
                    l2 = (word_t *)desc;
                }
                FUN_0007c0b8();
                ((void (*)(word_t, int, int, int))(*(vfn_t *)(*sk_launcher() + 0x98)))((word_t)l2, 0, 0, 1);
                if (0) {   /* local_128 flag */
                    FUN_0036b118(vec);
                    FUN_00093c60(r2);
                    FUN_00093c60(r1);
                    FUN_0036b118(l2);
                    FUN_0036b118((void *)rec);
                } else {
                    FUN_0036b118(l2);
                    FUN_000027e8(0);
                    word_t npt = 0, pte = 0;
                    /* vtable+0xe0 returns a 16-byte {count, shift} */
                    pte = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0xe0)))();
                    if (pte == 0) {
                        if (pt_sz != 0) {
                            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bd30) */
                        }
                        npt = 0;
                        pt_sz = 0;
                    } else {
                        npt = pt_sz >> 5;
                    }
                    FUN_0009bf9c(pte, npt, pt_base, base);
                    ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0xe8)))();
                    FUN_00093c60(r2);
                    FUN_00093c60(r1);
                    FUN_0036b118(vec);
                    FUN_0036b118((void *)rec);
                    FUN_0036b118((void *)rec2);
                    FUN_0036b118(fr);
                    word_t t2 = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0xe8)))();
                    word_t t3 = *(word_t *)(t2 + 0x10);
                    FUN_0036b118((void *)t2);
                    if (t3 >> 0x32 == 0) {
                        return base;
                    }
                    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9bd24) */
                }
            } else {
                FUN_00002874((word_t)"Unexpected type of ExtVmRegion");
            }
        } else {
            FUN_0036b118(vec);
            FUN_00093c60(r1);
            FUN_0036b118(commit_list);
        }
        FUN_0036b118((void *)rec);
        FUN_0036b118(fr);
        return base;
    }
    FUN_00002874((word_t)"Unexpected type of ExtVmRegion");
    FUN_0009e124();
    FUN_0009e1fc(0);
    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);
}

/* FUN_0009bf9c @ 0x0009bf9c   (est. raw_as_populate_ptes)
 * Ghidra: void FUN_0009bf9c(long, undefined8, ulong, ulong)
 * Populates the Raw Address Space page table at `param_1`. The table is
 * organized into blocks of up to 0x1ff entries; each block starts with a
 * 4-word header {entry_count, next_block_paddr, 0, 0}. Each entry is a PTE/cap
 * word assembled from the source descriptor rows (read through vtable 0xa0)
 * via the FUN_0009d3xx field setters, with a type tag (0/1/2/3/4) selecting
 * the descriptor layout. `param_3` is the page-table base, `param_4` the data
 * base (added into each PTE's address field).
 * Confidence: low
 * Notes: vtable 0xa0 reads source rows (0x58-byte stride); FUN_0005597c and
 *   the field setters build the PTE words; many bounds panics. */
void FUN_0009bf9c(word_t base_pt, word_t p2, word_t pt_base, word_t data_base)
{
    FUN_0009e148(0x665f60);
    word_t stride = FUN_0014aea4(0);
    FUN_0007c0b8();
    word_t total = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0xd0)))();
    FUN_00149ba0(0);
    word_t per = FUN_0014935c();
    if (total + per < total || total + per == 0) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c480/84) */
    }
    word_t gran = FUN_0014935c();
    if (gran == 0) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c488) */
    }
    word_t nblocks = (gran != 0) ? ((total + per - 1) / gran) : 0;
    word_t entries_per_block = 1;
    word_t hdr_off = 0x58;
    word_t idx = 0;

    while (idx != nblocks) {
        if (base_pt == 0) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c48c) */
        }
        FUN_0009e148(0);
        word_t bstride = FUN_0014aea4(0x665f60);
        word_t blk = base_pt + idx * bstride;
        if ((word_t)((long)blk) < 0) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c45c) */
        }
        word_t *hdr = (word_t *)(base_pt + idx * bstride);
        word_t next_idx = idx + 1;
        word_t next_blk;
        if (idx == nblocks - 1) {
            next_blk = ~0ull;
        } else {
            next_blk = pt_base + stride * next_idx;
        }
        word_t avail = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0xd0)))();
        word_t g2 = FUN_0014935c();
        word_t limit = next_idx * g2;
        if (avail <= limit) limit = avail;
        word_t base_cnt = idx * 0x1ff;
        if (limit < base_cnt) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c46c) */
        }
        hdr[0] = limit - base_cnt;      /* entry count */
        hdr[1] = next_blk;              /* next block paddr */
        hdr[2] = 0;
        hdr[3] = 0;

        if (limit != base_cnt) {
            word_t row = 0;
            word_t *src = (word_t *)(*(vfn_t *)(*sk_launcher() + 0xa0));   /* source rows */
            if (g2 * entries_per_block <= avail) avail = g2 * entries_per_block;
            word_t e_off = 0x20;
            word_t e_hdr = hdr_off;
            word_t done = base_cnt;
            do {
                word_t gi = done + row;
                if (limit <= gi) {
                    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c428) */
                }
                if (row > 0x3fffffffffffffe) {
                    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c42c) */
                }
                word_t *entry = (word_t *)((byte_t *)hdr + e_off);
                if (entry == 0) {
                    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c434) */
                }
                FUN_0009e148(0);
                word_t g3 = FUN_0007eb2c(0x665f60, 0);
                word_t row_pa = ((word_t (*)(void))(*(vfn_t *)(*sk_launcher() + 0xa0)))();
                if (*(word_t *)(row_pa + 0x10) <= gi) {
                    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c444) */
                }
                byte_t *rec = (byte_t *)(row_pa + e_hdr);
                word_t f_lo = *(word_t *)(rec - 0x28);
                word_t f_a  = *(word_t *)(rec - 0x20);
                word_t f_b  = *(word_t *)(rec - 0x18);
                word_t f_c  = *(word_t *)(rec - 0x10);
                word_t f_d  = *(word_t *)(rec - 8);
                byte_t kind = *rec;
                FUN_0036b118((void *)0);
                word_t tag;
                switch (kind) {
                default:
                    FUN_0009d398((word_t)entry, f_b);
                    FUN_0009e234();
                    FUN_0009d3a8((word_t)entry, 0);
                    tag = FUN_0001c294(f_a, 8);
                    if (tag & 1) {
                        FUN_0009e234();
                        FUN_0009d3b8((word_t)entry, 0);
                        FUN_0009d3c8((word_t)entry, f_c);
                        FUN_0009d3d8((word_t)entry, f_d & 0xff);
                    }
                    tag = FUN_00157308(f_a);
                    if (tag > 0xff) {
                        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c44c) */
                    }
                    break;
                case 1:
                    FUN_0009d398((word_t)entry, 0);
                    FUN_0009e234();
                    FUN_0009d3a8((word_t)entry, 0);
                    FUN_0009e234();
                    FUN_0009d3b8((word_t)entry, 0);
                    FUN_0009d3c8((word_t)entry, f_a);
                    FUN_0009d3d8((word_t)entry, f_b & 0xff);
                    FUN_0009d3e8((word_t)entry, f_c);
                    tag = FUN_00157308(8);
                    if (tag > 0xff) {
                        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c450) */
                    }
                    FUN_0009d370((word_t)entry, tag);
                    FUN_0009d3f0((word_t)entry, f_d);
                    break;
                case 2:
                    FUN_0009e234();
                    FUN_0009d378((word_t)entry, 0);
                    FUN_0009d380((word_t)entry, f_a & 1);
                    tag = FUN_00157308(0x10);
                    if (tag > 0xff) {
                        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c448) */
                    }
                    break;
                case 3:
                    tag = FUN_00157308(0xb);
                    if (tag > 0xff) {
                        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9c454) */
                    }
                    FUN_0009d370((word_t)entry, tag);
                    FUN_0005597c((word_t)entry, (f_lo & 0xff) + 1);
                    break;
                case 4:
                    tag = 0;
                    break;
                }
                if (kind != 1 && kind != 3) {
                    FUN_0009d370((word_t)entry, tag);
                }
                FUN_0009d360(entry, gi * g3 + data_base);
                row++;
                e_hdr += 0x40;
                e_off += 0x20;
            } while (avail + base_cnt != row);
        }
        idx = next_idx;
        entries_per_block++;
        hdr_off += 0x7fc0;
    }
}

/* FUN_0009955c @ 0x0009955c   (est. exclave_launcher_run)
 * Ghidra: void FUN_0009955c(long, long *, uint, uint)
 * The core launcher run: builds the exclave's capability set from the raw
 * address-space table, then maps every region descriptor's caps into the
 * exclave address space and commits the result.
 *
 * Phase 1 — walk the raw address-space table (FUN_0029fb80/001ee018) and for
 * each entry pair decode it into a capability descriptor (via FUN_002a9ba8 /
 * FUN_000f4404 for high-kinded entries, FUN_000b0794 for low ones), collecting
 * the descriptors into the plVar19 list.
 *
 * Phase 2 — for each region descriptor (param_1+0x20+i*0x40), fetch each of its
 * caps; when (param_3 & 1) is clear the cap must pass the capability-mask test,
 * and then either map every cap (vtable 0x88) or a single cap (vtable 0x50)
 * depending on (param_4 & 1). Each mapped cap gets a 0x4000 frame object
 * (FUN_00085a54) whose PTE is installed; the collected pages are merged and
 * committed with FUN_00099010 / FUN_00099398. Any failure logs "Fatal error".
 * Confidence: low
 * Notes: strings "InternalExclaveLauncher_External", "Fatal error"; vtable
 *   slots 0x58/0x60/0x88/0x50/0x1d8/0x1f0/0x90/0xe0; frame types 0x1808/0x1800;
 *   FUN_0009d480 is the "save" supervisor call; FUN_00107200 gives the cap
 *   mask; dozens of SoftwareBreakpoint bounds panics. */
void FUN_0009955c(word_t p1, word_t *p2, word_t flag3, word_t flag4)
{
    word_t nregs = *(word_t *)(p1 + 0x10);
    if (nregs == 0) {
        FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9a508) */
    }

    word_t *caps = (word_t *)&cl4_empty_list;
    word_t m1 = *(word_t *)(p1 + 0x48);
    word_t m2 = *(word_t *)(p1 + 0x50);
    word_t lo = (word_t)m1 & 0xffffffffffff;
    if ((m2 & 0x2000000000000000) != 0) {
        lo = m2 >> 0x38 & 0xf;
    }
    word_t *table = (word_t *)m2;

    /* Drain the raw address-space table, dropping the sentinel pattern. */
    FUN_0036b270((void *)m2);
    for (;;) {
        cl4_pair_t t = FUN_0029fb80();
        word_t h = t.hi, l = t.lo;
        if (h == 0) break;
        if (!(l == 0x2d && h == 0xe100000000000000) &&
            !(FUN_002a0cf8(l, h, 0x2d, 0xe100000000000000, 0) & 1)) {
            thunk_FUN_002acbb8(l, h);
        }
        FUN_003a25d4(h);
    }
    FUN_003a25d4(m2);
    word_t count = FUN_001ee018(caps, 0xe000000000000000);
    if (count != 0x20) {
        FUN_001afa84(0xb, 2, 0xd000000000000017, 0x80000000005c1830,
                     (word_t)"Fatal error", 0xb, 2, 0);
    }
    count = FUN_001ee018(caps, 0xe000000000000000);
    if ((word_t)((long)count) < 1) {
        FUN_003a25d4(0xe000000000000000);
    } else {
        for (word_t k = 0; k < count; k += 2) {
            word_t a = FUN_0029f0b0(0xf, k, caps, 0xe000000000000000);
            word_t b = FUN_0029f0b0(0xf, k + 1, caps, 0xe000000000000000);
            word_t bb = FUN_001b798c(b, (word_t)caps, 0xe000000000000000);
            cl4_pair_t r = FUN_0029fa0c(a, bb);
            word_t rh = r.hi, rl = r.lo;
            if ((rl ^ rh) >> 0xe != 0) {
                word_t kind;
                if ((rh >> 0x3c & 1) == 0) {
                    if ((rh >> 0x3d & 1) == 0) {
                        if ((rl >> 0x3c & 1) == 0) {
                            cl4_pair_t d = FUN_002a9ba8(rl, rh);
                            kind = FUN_000f4404(d.lo, d.hi, rl, rh, (word_t)caps, 0xe000000000000000);
                        } else {
                            /* hi-kind descriptor; reuse resolved fields */
                            cl4_pair_t d = { (rh & 0xfffffffffffffff) + 0x20, rl & 0xffffffffffff };
                            kind = FUN_000f4404(d.lo, d.hi, rl, rh, (word_t)caps, 0xe000000000000000);
                        }
                    } else {
                        cl4_pair_t d = { (word_t)&caps, rh & 0xffffffffffffff };
                        kind = FUN_000f4404(d.lo, d.hi, rl, rh, (word_t)caps, 0xe000000000000000);
                    }
                    FUN_003a25d4(rh);
                } else {
                    kind = FUN_000b0794(rl, rh, (word_t)caps, 0xe000000000000000, 0x10);
                    FUN_003a25d4(rh);
                }
                if ((kind >> 8 & 0xff) == 1) {
                    FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9a4ec) */
                }
                /* record the built cap. */
                word_t line = FUN_0036a9a0(FUN_00002534((word_t)"__cstring", 0x4be910), 0);
                *(byte_t *)(line + 0x20) = (byte_t)kind;
                FUN_0008129c(line);
                /* push onto the cap list */
                if ((FUN_003a261c(caps) & 1) == 0) {
                    caps = (word_t *)FUN_00072de8(0, caps[2] + 1, 1, (word_t)caps);
                }
                word_t cc = caps[2];
                if ((word_t)caps[3] >> 1 <= cc) {
                    caps = (word_t *)FUN_00072de8(1 < (word_t)caps[3], cc + 1, 1, (word_t)caps);
                }
                caps[2] = cc + 1;
                caps[cc + 4] = kind;
            }
        }
        FUN_003a25d4(0xe000000000000000);
    }

    /* Phase 2: map each region descriptor's caps. */
    for (word_t r = 0; r < nregs; r++) {
        if (r == *(word_t *)(p1 + 0x10)) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint(1,0x9a504) */
        }
        word_t reg = *(word_t *)(p1 + 0x20 + r * 0x40);
        word_t ncap = *(word_t *)(reg + 0x10);
        if (ncap != 0) {
            word_t m1v = p2[0x16], m2v = p2[0x17];
            FUN_0036b270((void *)reg);
            for (word_t ci = 0; ci < ncap; ci++) {
                word_t *cap = (word_t *)*(word_t *)(reg + 0x20 + ci * 8);
                word_t obj = ((word_t (*)(void))(*(vfn_t *)(*cap + 0x58)))();
                if (obj != 0) {
                    if ((flag3 & 1) == 0) {
                        word_t mask = ((word_t (*)(void))(*(vfn_t *)(*cap + 0x60)))();
                        if ((*FUN_00107200() & ~mask) != 0) {
                            goto next_cap;
                        }
                        if ((flag4 & 1) != 0) {
                            map_all_caps(cap, reg, p2, &caps);
                        } else {
                            cl4_pair_t sv = ((cl4_pair_t (*)(void))(*(vfn_t *)(*cap + 0x50)))();
                            word_t v = FUN_000abad0(sv.lo, sv.hi, 0x65fcf0);
                            FUN_003a25d4(sv.hi);
                            if ((v & 1) != 0 ||
                                (m1v == 0xd000000000000012 && m2v == 0x80000000005c1870) ||
                                FUN_002a0cf8(m1v, m2v, 0xd000000000000012, 0x80000000005c1870, 0) & 1) {
                                map_all_caps(cap, reg, p2, &caps);
                            } else {
                                caps = (word_t *)&cl4_empty_list;
                            }
                        }
                    } else {
                        map_all_caps(cap, reg, p2, &caps);
                    }
                    continue;
                }
            next_cap:
                FUN_0036b118((void *)0);
            }
            FUN_0036b118((void *)reg);
        }
    }
    FUN_0036b118((void *)0);
}

/* Helper used by FUN_0009955c phase 2: fetch every cap in the object's cap
 * list (vtable 0x88), and for each allocate a pair of 0x4000 frames (types
 * 0x1808 / 0x1800), install their PTEs, copy between them, and record the
 * resulting descriptors into *caps. This is the "map all caps" path. */
static void map_all_caps(word_t *cap, word_t reg, word_t *p2, word_t **caps)
{
    word_t list = ((word_t (*)(void))(*(vfn_t *)(*cap + 0x88)))();
    if (list == 0) {
        FUN_0036b118((void *)0);
        return;
    }
    word_t n = *(word_t *)(list + 0x10);
    if (n == 0) {
        FUN_0036b118((void *)list);
        return;
    }
    word_t out = (word_t)&cl4_empty_list;
    word_t off = 0;
    for (word_t i = 0; i < n; i++) {
        word_t capv = *(word_t *)(list + i * 8 + 0x20);
        word_t args[5];
        for (int j = 0; j < 5; j++) args[j] = 0;
        FUN_0006e7c0((word_t)(p2 + 6), (word_t)args);
        ((void (*)(word_t *, int, word_t, int, word_t *))(*(vfn_t *)(*(word_t *)p2[0x13] + 0x1f0)))
            (args, 3, off + cap[2], 0, args);
        FUN_0000276c((word_t)args, 0x64e8f8, 0x4c10a0);
        word_t tok = FUN_00086440(0);
        FUN_0036a9d4(tok, 0x64e1c0);
        FUN_0036a940(FUN_00086590(0), 0x50, 7);
        word_t *f1 = (word_t *)FUN_00085a54((word_t)args, 0x4000, 0x11, 0x1808, 0);
        word_t *f2 = (word_t *)FUN_00085a54((word_t)args, 0x4000, 0x11, 0x1800, 0);
        ((void (*)(int, word_t))(*(vfn_t *)(*f2 + 0x90)))(0, capv);
        ((void (*)(int, word_t))(*(vfn_t *)(*f1 + 0x90)))(0, args[0]);
        word_t p1 = ((word_t (*)(void))(*(vfn_t *)(*f1 + 0xe0)))();
        word_t p2v = ((word_t (*)(void))(*(vfn_t *)(*f2 + 0xe0)))();
        if (p1 == 0 || p2v == 0) {
            FUN_001afa84(0xb, 2, 0, 0, 0, 0, 0);   /* SoftwareBreakpoint */
        }
        FUN_00117d14(p1, p2v, 0x4000);
        if ((FUN_003a261c((void *)out) & 1) == 0) {
            out = FUN_00072de8(0, *(word_t *)(out + 0x10) + 1, 1, out);
        }
        word_t c = *(word_t *)(out + 0x10);
        if (*(word_t *)(out + 0x18) >> 1 <= c) {
            out = FUN_00072de8(1 < *(word_t *)(out + 0x18), c + 1, 1, out);
        }
        *(word_t *)(out + 0x10) = c + 1;
        *(word_t *)(out + c * 0x40 + 0x20) = args[0];
        FUN_0036b118(f1);
        FUN_0036b118(f2);
        off += 0x4000;
    }
    FUN_0036b118((void *)0);
    *caps = (word_t *)out;
}

