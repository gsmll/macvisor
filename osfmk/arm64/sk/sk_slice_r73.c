/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R73: 0x685cd8-0x687b48 — the tail of the kernel image, resident in
 * the __DATA segment. It is the cL4 runtime fatal/assert machinery: a dense
 * table of noreturn abort handlers (one per panic message address), the
 * lock-protected assertion-failure abort sequences, the trace/fault-record
 * helpers (cL4_trace_*), the syscall-result error handlers (each runs the
 * seL4 supervisor call in a retry loop, then panics on a bad error code),
 * a few per-CPU counter increments, and assorted real-logic helpers
 * (frame-bitmap free, bounds-checked copy, vtable dispatch, object lookup).
 * All names are estimates unless string/header-matched.
 *
 * NOTE: the panic-message addresses (0x6a8xxx-0x6b1xxx) point into the
 * __DATA segment tail that lies BEYOND the on-disk file / Ghidra ram block
 * (ram ends at 0x69dfcf; file is 0x69e450 bytes). The string text at those
 * addresses is therefore not recoverable from this payload; the addresses are
 * kept verbatim as comments so a full-image load can resolve them later.
 *
 * Calling-convention note: several helper callees are tiny no-op / register
 * shims (FUN_0065f454, FUN_006765e4, FUN_006765fc, FUN_00676614, FUN_0067663c,
 * FUN_006766b0 — each is `return;` with hidden unaff-register side effects)
 * or one-line error-code fillers (FUN_00674e98, FUN_006765a4, FUN_006765c4,
 * FUN_00676630). They appear between the abort-sequence cleanup calls and the
 * final fatal() and are transcribed faithfully.
 */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;

/* seL4/cL4 supervisor call (SVC/BRK trap), imm 4 = seL4_SysCall. The
 * decompiler renders it as CallSupervisor(4). In the retry loops below the
 * call is issued and the loop re-tests a "would-block / needs-retry" flag
 * (== 1) before re-issuing. */
#define CL4_SYSCALL()  __asm__ volatile("svc #4" ::: "memory")

/* noreturn software-breakpoint trap used by the kernel on internal faults. */
#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations (extern; bodies reconstructed by the
 * range worker that owns them). Signatures reflect observed register use.
 * ------------------------------------------------------------------ */

/* FUN_006833d4 — the central fatal(): FUN_0065c310(0, msg, &frame).
 * noreturn; formats+prints the message and halts. */
extern void cL4_fatal(word_t msg) __attribute__((noreturn));

/* noreturn panic wrappers that forward a caller-supplied argument through a
 * fixed format string (address noted), then fall into cL4_fatal(). */
extern void cL4_fatal_ctx1(word_t arg) __attribute__((noreturn)); /* fmt 0x6a8cdf */
extern void cL4_fatal_ctx2(word_t arg) __attribute__((noreturn)); /* fmt 0x6a9997 */
extern void cL4_fatal_fmt_76660(word_t arg) __attribute__((noreturn)); /* fmt 0x6aee2a */
extern void cL4_fatal_fmt_76674(word_t arg) __attribute__((noreturn)); /* fmt 0x6ae527 */
extern void cL4_fatal_fmt_76688(word_t arg) __attribute__((noreturn)); /* fmt 0x6ae492 */
extern void cL4_fatal_fmt_7669c(word_t arg) __attribute__((noreturn)); /* fmt 0x6ada99 */
extern void cL4_fatal_76650(void) __attribute__((noreturn));   /* msg 0x6a71a1 */
extern void cL4_fatal_79394(void) __attribute__((noreturn));   /* msg 0x6afd4f */
extern void cL4_fatal_793b0(word_t arg) __attribute__((noreturn)); /* msg 0x6af394 */
extern void cL4_fatal_793e0(word_t arg) __attribute__((noreturn)); /* msg 0x6af60f */
extern void cL4_fatal_793d0(void) __attribute__((noreturn));   /* msg 0x6af912 */

/* L4 error-code machinery (s_L4_ErrorCode* string table @0x68a598).
 * FUN_00674e98(buf, code) fills a small error descriptor from the code byte. */
extern void cL4_ec_fill(word_t *buf, word_t code);            /* FUN_00674e98 */
extern void cL4_ec_fill_a(void);   /* FUN_006765a4: cL4_ec_fill(&stack) */
extern void cL4_ec_fill_b(void);   /* FUN_00676630: cL4_ec_fill() */
extern void cL4_ec_fill_c(void);   /* FUN_006765c4: cL4_ec_fill(&stack) */

/* No-op / register-shim helpers (each `return;`, hidden register side
 * effects); appear in the abort sequences as cleanup calls. */
extern void cL4_noop_65f454(void);  /* FUN_0065f454 */
extern void cL4_noop_765e4(void);   /* FUN_006765e4 */
extern void cL4_noop_765fc(void);   /* FUN_006765fc */
extern void cL4_noop_76614(void);   /* FUN_00676614 */
extern void cL4_noop_7663c(void);   /* FUN_0067663c */
extern void cL4_noop_766b0(void);   /* FUN_006766b0 */

/* Syscall/diagnostic validator — FUN_0067f660(p1,p2,p3). Rejects unknown
 * syscall selectors (returns 0xfffffff9 = -7) and, on a permitted one, runs
 * the diagnostic core FUN_0067f9a0. In the abort paths the decompiler drops
 * the arguments and treats the call as noreturn. */
extern word_t cL4_syscall_validate(word_t a, word_t b, word_t c); /* FUN_0067f660 */

/* Trace / fault-record helpers. FUN_0067d1f0(a,b) records event b for object
 * a via FUN_0067d83c(a,b,&stack) [→ FUN_0067b774], then checks the global
 * fault counter _DAT_006b5ed0: if it moved, it aborts via cL4_syscall_validate.
 * FUN_0067d3f8(n,obj) flushes the trace queue. */
extern void cL4_trace_fault(word_t a, word_t b);   /* FUN_0067d1f0 */
extern void cL4_trace_rec(word_t a, word_t b, word_t c); /* FUN_0067d83c */
extern void cL4_trace_flush(word_t n, word_t obj); /* FUN_0067d3f8 */

/* Object/capability lookup+release — FUN_0067d190(obj). Returns -1 and
 * records error 0x2d when the object is null; otherwise lookups/refs it. */
extern word_t cL4_obj_lookup(word_t obj);          /* FUN_0067d190 */

/* Capability/page-table type classifier — FUN_006775c0(a,b). Switches on a
 * type byte at a+0x98 (0/1/2) and reads a table byte; panics on invalid type. */
extern word_t cL4_type_classify(word_t a, word_t b); /* FUN_006775c0 */

/* Generic "check" helpers FUN_00679348 / FUN_006793c4 / FUN_00679368 —
 * call FUN_006774ac(&stack)/()/(); used in the 793xx abort sequences. */
extern void cL4_check_79348(void); /* FUN_00679348 */
extern void cL4_check_793c4(void); /* FUN_006793c4 */
extern void cL4_check_79368(void); /* FUN_00679368 */

/* Frame-bitmap / alloc helpers used by cL4_frame_bitmap_free (FUN_006860f4). */
extern void *cL4_ks_get_tls(word_t size, word_t align, word_t tag); /* FUN_0065be08 */
extern word_t cL4_state_flags(word_t p);           /* FUN_0066a9bc (16-byte ret) */
extern word_t cL4_frame_lookup(word_t idx);        /* FUN_0066b1fc */
extern void  cL4_state_restore(word_t p, word_t a, word_t b); /* FUN_0066ab40 */

/* Helpers used by cL4_map_flush (FUN_00686a8c). */
extern word_t cL4_ctx_new(void);                   /* FUN_00668c78 */
extern void  cL4_ctx_map(word_t ctx, word_t base, word_t size, word_t n, word_t f); /* FUN_00678ae0 */
extern void  cL4_ctx_copy(word_t src, word_t size, word_t dst, word_t a, word_t b); /* FUN_00672f64 */

/* The seL4 supervisor call returns a result; these are issued as
 * "CallSupervisor(4)" in the retry loops. */
static inline void cL4_supervisor_call(void) { CL4_SYSCALL(); }

/* ------------------------------------------------------------------ *
 * Global counters (dat region) read/written by the counter increments and
 * the map-flush helper. _DAT_007001xx are the inc targets; _DAT_006b4368 is
 * the current-thread / current-context pointer used by trace helpers.
 * ------------------------------------------------------------------ */
extern volatile word_t cL4_counter_1c8;  /* _DAT_007001c8 */
extern volatile word_t cL4_counter_1d8;  /* _DAT_007001d8 */
extern volatile word_t cL4_counter_1d4;  /* _DAT_007001d4 */
extern volatile word_t cL4_counter_1dc;  /* _DAT_007001dc */
extern volatile word_t cL4_counter_0248; /* _DAT_00700248 */
extern word_t cL4_current_ctx;           /* _DAT_006b4368 */
extern word_t cL4_trace_fault_counter;   /* _DAT_006b5ed0 */

/* ================================================================== *
 *  Pure fatal/abort thunks (Category A) — each is a noreturn handler
 *  that calls cL4_fatal with its own message-string address.
 * ================================================================== */

/* FUN_00685cd8 @ 0x685cd8   (est. cL4_fatal_685cd8)
 * Noreturn abort handler; panics with the message string at 0x6a9122.
 * Confidence: high (uniform table thunk) */
static void cL4_fatal_685cd8(void) { cL4_fatal(0x6a9122); /* msg @0x6a9122 */ }

/* FUN_00685d10 @ 0x685d10   (est. cL4_fatal_685d10) — panic msg @0x6a8e53. */
static void cL4_fatal_685d10(void) { cL4_fatal(0x6a8e53); }

/* FUN_00685d4c @ 0x685d4c   (est. cL4_fatal_685d4c) — panic msg @0x6a8df3. */
static void cL4_fatal_685d4c(void) { cL4_fatal(0x6a8df3); }

/* FUN_00685d84 @ 0x685d84   (est. cL4_fatal_685d84) — panic msg @0x6a899c. */
static void cL4_fatal_685d84(void) { cL4_fatal(0x6a899c); }

/* FUN_00685dbc @ 0x685dbc   (est. cL4_fatal_685dbc) — panic msg @0x6a8bf5. */
static void cL4_fatal_685dbc(void) { cL4_fatal(0x6a8bf5); }

/* FUN_00685df4 @ 0x685df4   (est. cL4_fatal_ctx_685df4)
 * Noreturn; forwards arg 0x6a9351 through the fixed-format wrapper
 * cL4_fatal_ctx1 (fmt @0x6a8cdf). Confidence: high */
static void cL4_fatal_685df4(void) { cL4_fatal_ctx1(0x6a9351); }

/* FUN_00685e1c @ 0x685e1c   (est. cL4_fatal_ctx_685e1c) — ctx1 arg 0x6a919d. */
static void cL4_fatal_685e1c(void) { cL4_fatal_ctx1(0x6a919d); }

/* FUN_00685e44 @ 0x685e44   (est. cL4_fatal_ctx_685e44) — ctx2 arg 0x6a99f2. */
static void cL4_fatal_685e44(void) { cL4_fatal_ctx2(0x6a99f2); }

/* FUN_00685e6c @ 0x685e6c   (est. cL4_fatal_685e6c) — panic msg @0x6aa190. */
static void cL4_fatal_685e6c(void) { cL4_fatal(0x6aa190); }

/* FUN_00685ea4 @ 0x685ea4   (est. cL4_fatal_685ea4) — panic msg @0x6aa131. */
static void cL4_fatal_685ea4(void) { cL4_fatal(0x6aa131); }

/* FUN_00685ee0 @ 0x685ee0   (est. cL4_fatal_ctx_685ee0) — ctx2 arg 0x6a9fa0. */
static void cL4_fatal_685ee0(void) { cL4_fatal_ctx2(0x6a9fa0); }

/* FUN_00685f08 @ 0x685f08   (est. cL4_fatal_685f08) — panic msg @0x6aa07d. */
static void cL4_fatal_685f08(void) { cL4_fatal(0x6aa07d); }

/* FUN_00685f40 @ 0x685f40   (est. cL4_fatal_685f40) — panic msg @0x6a9fd4. */
static void cL4_fatal_685f40(void) { cL4_fatal(0x6a9fd4); }

/* FUN_00685f78 @ 0x685f78   (est. cL4_fatal_685f78) — panic msg @0x6a9a14. */
static void cL4_fatal_685f78(void) { cL4_fatal(0x6a9a14); }

/* FUN_00685fb0 @ 0x685fb0   (est. cL4_fatal_685fb0) — panic msg @0x6a9dce. */
static void cL4_fatal_685fb0(void) { cL4_fatal(0x6a9dce); }

/* FUN_00685fe8 @ 0x685fe8   (est. cL4_fatal_685fe8) — panic msg @0x6a86ea. */
static void cL4_fatal_685fe8(void) { cL4_fatal(0x6a86ea); }

/* FUN_00686020 @ 0x686020   (est. cL4_fatal_686020) — panic msg @0x6a9b84. */
static void cL4_fatal_686020(void) { cL4_fatal(0x6a9b84); }

/* FUN_00686058 @ 0x686058   (est. cL4_fatal_686058) — panic msg @0x6a9c0e. */
static void cL4_fatal_686058(void) { cL4_fatal(0x6a9c0e); }

/* FUN_00686084 @ 0x686084   (est. cL4_fatal_686084) — panic msg @0x6aa1f4. */
static void cL4_fatal_686084(void) { cL4_fatal(0x6aa1f4); }

/* FUN_006860bc @ 0x6860bc   (est. cL4_fatal_6860bc) — panic msg @0x6aa35b. */
static void cL4_fatal_6860bc(void) { cL4_fatal(0x6aa35b); }

/* ================================================================== *
 *  Real-logic helpers.
 * ================================================================== */

/* FUN_006860f4 @ 0x6860f4   (est. cL4_frame_bitmap_free)
 * Releases a frame described by param_1 from the kernel's per-frame bitmap.
 * Runs the supervisor call in a retry loop (while param_1==1), looks up the
 * frame's bitmap entry, clears the owning bit, and decrements the refcount;
 * validates indices/overlap and panics on corruption. Returns via
 * cL4_state_restore of the saved flags.
 * Confidence: medium (register names inferred)
 * Notes: helper callees FUN_0065be08(0x6fea48,4,8), FUN_0066a9bc, FUN_0066b1fc,
 *   FUN_0066ab40; panics @0x6aadee/0x6aae67/0x6aaecd; SWBP 0x5519 @0x68620c. */
static void cL4_frame_bitmap_free(word_t idx)
{
    word_t *entry, *bitmap;
    void *state;
    word_t *tls;
    word_t flags[2];
    word_t diff;

    do {
        cL4_supervisor_call();
    } while (idx == 1);                       /* retry while preempted */

    /* Fetch the kernel TLS/bitmap state object (tag 4, 8-byte entries). */
    tls = (word_t *)cL4_ks_get_tls(0x6fea48, 4, 8);
    state = (void *)cL4_state_flags(*(word_t *)(*tls + 0x10));
    if (((word_t)state & 1) != 0) {           /* invalid state flag */
        cL4_fatal(0x6aadee);
    }

    bitmap = (word_t *)cL4_frame_lookup(idx);
    if (bitmap == (word_t *)0x0) {
        tls[7] = idx;                          /* record the freed index */
    } else {
        diff = idx - bitmap[5];
        if (0x3fff < diff) {                   /* index out of bitmap range */
            cL4_fatal(0x6aae67);
        }
        entry = bitmap + 4;
        bitmap = bitmap + (diff >> 0xc);       /* bitmap word for this frame */
        /* Overflow / out-of-order guards (decompiler's overlap check). */
        if ((bitmap < (word_t *)entry - 4) || (entry < bitmap + 1)) {
            CL4_SW_BP(0x68620c);
        }
        {
            word_t bit = 1UL << (diff >> 6 & 0x3f);
            if ((*bitmap & bit) == 0) {        /* frame not marked owned */
                cL4_fatal(0x6aaecd);
            }
            *bitmap &= ~bit;                   /* clear the owned bit */
        }
        if (0xff < (word_t)*(unsigned short *)entry) {
            bitmap[6] = tls[6];
            tls[6] = (word_t)bitmap;           /* push onto free list */
        }
        *(unsigned short *)entry = (unsigned short)((word_t)*(unsigned short *)entry - 1);
    }
    cL4_state_restore(*(word_t *)(*tls + 0x10), flags[0], flags[1]);
}

/* FUN_006862a0 @ 0x6862a0   (est. cL4_fatal_6862a0) — panic msg @0x6ab2db. */
static void cL4_fatal_6862a0(void) { cL4_fatal(0x6ab2db); }

/* FUN_006862d8 @ 0x6862d8   (est. cL4_fatal_6862d8) — panic msg @0x6aa529. */
static void cL4_fatal_6862d8(void) { cL4_fatal(0x6aa529); }

/* FUN_00686310 @ 0x686310   (est. cL4_fatal_686310) — panic msg @0x6aa59b. */
static void cL4_fatal_686310(void) { cL4_fatal(0x6aa59b); }

/* FUN_00686348 @ 0x686348   (est. cL4_fatal_686348) — panic msg @0x6aa775. */
static void cL4_fatal_686348(void) { cL4_fatal(0x6aa775); }

/* FUN_00686380 @ 0x686380   (est. cL4_fatal_686380) — panic msg @0x6aa703. */
static void cL4_fatal_686380(void) { cL4_fatal(0x6aa703); }

/* FUN_006863b8 @ 0x6863b8   (est. cL4_fatal_6863b8) — panic msg @0x6aa697. */
static void cL4_fatal_6863b8(void) { cL4_fatal(0x6aa697); }

/* FUN_006863f0 @ 0x6863f0   (est. cL4_fatal_6863f0) — panic msg @0x6ab070. */
static void cL4_fatal_6863f0(void) { cL4_fatal(0x6ab070); }

/* FUN_0068642c @ 0x68642c   (est. cL4_fatal_68642c) — panic msg @0x6ab00e. */
static void cL4_fatal_68642c(void) { cL4_fatal(0x6ab00e); }

/* FUN_00686464 @ 0x686464   (est. cL4_fatal_686464) — panic msg @0x6ab26f. */
static void cL4_fatal_686464(void) { cL4_fatal(0x6ab26f); }

/* FUN_0068649c @ 0x68649c   (est. cL4_fatal_68649c) — panic msg @0x6ab5f5. */
static void cL4_fatal_68649c(void) { cL4_fatal(0x6ab5f5); }

/* FUN_006864b4 @ 0x6864b4   (est. cL4_fatal_6864b4) — panic msg @0x6ab68d. */
static void cL4_fatal_6864b4(void) { cL4_fatal(0x6ab68d); }

/* FUN_006864cc @ 0x6864cc   (est. cL4_trace_fault_record)
 * Records a trace/fault event for the current context: calls cL4_trace_fault
 * (which panics if the global fault counter moved), then appends a raw record
 * (cL4_trace_rec) and flushes the trace queue (cL4_trace_flush(10, ctx)).
 * param_1 = event tag. Confidence: high (matches FUN_006874b4 byte-for-byte)
 * Notes: event string @0x6a53b8; ctx from _DAT_006b4368. */
static void cL4_trace_fault_record(word_t tag)
{
    cL4_trace_fault(tag, 0x6a53b8);
    cL4_trace_rec(cL4_current_ctx, 0, (word_t)&tag);
    cL4_trace_flush(10, cL4_current_ctx);
}

/* FUN_00686544 @ 0x686544   (est. cL4_fatal_fmt_686544)
 * Noreturn; forwards arg 0x6ada7c through cL4_fatal_fmt_7669c (fmt @0x6ada99). */
static void cL4_fatal_686544(void) { cL4_fatal_fmt_7669c(0x6ada7c); }

/* FUN_0068656c @ 0x68656c   (est. cL4_fatal_68656c) — panic msg @0x6ada12. */
static void cL4_fatal_68656c(void) { cL4_fatal(0x6ada12); }

/* FUN_006865a4 @ 0x6865a4   (est. cL4_fatal_6865a4) — panic msg @&DAT_006adf78. */
static void cL4_fatal_6865a4(void) { cL4_fatal(0x6adf78); }

/* FUN_006865dc @ 0x6865dc   (est. cL4_fatal_6865dc) — panic msg @0x6adf04. */
static void cL4_fatal_6865dc(void) { cL4_fatal(0x6adf04); }

/* FUN_00686614 @ 0x686614   (est. cL4_fatal_686614) — panic msg @0x6adb75. */
static void cL4_fatal_686614(void) { cL4_fatal(0x6adb75); }

/* FUN_0068664c @ 0x68664c   (est. cL4_ec_fatal_68664c)
 * Fills an error descriptor (cL4_ec_fill(param_1, param_2)) then panics
 * with the message at 0x6adc5e. Noreturn. Confidence: high */
static void cL4_ec_fatal_68664c(word_t p1, word_t p2)
{
    cL4_ec_fill((word_t *)p1, p2);
    cL4_fatal(0x6adc5e);
}

/* FUN_006866a4 @ 0x6866a4   (est. cL4_assert_abort_6866a4)
 * Lock-protected assertion-failure abort: no-op, error-code fill, trace
 * record, error-code fill, then panic msg @0x6add5a. Noreturn.
 * Confidence: high (Category-B abort sequence) */
static void cL4_assert_abort_6866a4(void)
{
    cL4_noop_65f454();
    cL4_ec_fill_a();
    cL4_trace_fault_record(0);
    cL4_ec_fill_b();
    cL4_fatal(0x6add5a);
}

/* FUN_006866f8 @ 0x6866f8   (est. cL4_fatal_6866f8) — panic msg @0x6adbf2. */
static void cL4_fatal_6866f8(void) { cL4_fatal(0x6adbf2); }

/* FUN_00686730 @ 0x686730   (est. cL4_fatal_686730) — panic msg @0x6ae0c9. */
static void cL4_fatal_686730(void) { cL4_fatal(0x6ae0c9); }

/* FUN_00686768 @ 0x686768   (est. cL4_assert_abort_686768) — abort seq, msg @0x6ae259. */
static void cL4_assert_abort_686768(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a(); cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae259);
}

/* FUN_006867bc @ 0x6867bc   (est. cL4_assert_abort_6867bc) — abort seq, msg @0x6ae2f5. */
static void cL4_assert_abort_6867bc(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a(); cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae2f5);
}

/* FUN_00686810 @ 0x686810   (est. cL4_assert_abort_686810) — abort seq, msg @0x6ae392. */
static void cL4_assert_abort_686810(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a(); cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae392);
}

/* FUN_00686864 @ 0x686864   (est. cL4_fatal_686864) — panic msg @0x6ae3d4. */
static void cL4_fatal_686864(void) { cL4_fatal(0x6ae3d4); }

/* FUN_00686890 @ 0x686890   (est. cL4_fatal_686890) — panic msg @0x6ae439. */
static void cL4_fatal_686890(void) { cL4_fatal(0x6ae439); }

/* FUN_006868bc @ 0x6868bc   (est. cL4_fatal_6868bc) — panic msg @0x6ae1eb. */
static void cL4_fatal_6868bc(void) { cL4_fatal(0x6ae1eb); }

/* FUN_006868e8 @ 0x6868e8   (est. cL4_assert_abort_6868e8)
 * Abort sequence with an extra no-op (cL4_noop_766b0 @0x686904), msg @0x6ae6f2. */
static void cL4_assert_abort_6868e8(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_766b0();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae6f2);
}

/* FUN_00686930 @ 0x686930   (est. cL4_syscall_err_686930)
 * Syscall-result handler. Runs the supervisor call in a retry loop (while
 * param_3==1); if the result error code (low byte of param_3) is zero it
 * returns, else runs the diagnostic validator and, failing that, an abort
 * sequence ending in panic msg @0x6ae745. Confidence: medium */
static void cL4_syscall_err_686930(word_t p1, word_t p2, word_t p3)
{
    cL4_noop_765e4();
    do {
        cL4_supervisor_call();
    } while (p3 == 1);
    if ((p3 & 0xff) == 0) {                    /* success */
        cL4_noop_765fc();
        return;
    }
    cL4_syscall_validate(0, 0, 0);             /* dropped args; abort path */
    cL4_ec_fill_c();
    cL4_noop_766b0();
    cL4_trace_fault_record(0);
    cL4_ec_fill((word_t *)0, 0);
    cL4_fatal(0x6ae745);
}

/* FUN_006869bc @ 0x6869bc   (est. cL4_fatal_fmt_6869bc) — fmt_76674 arg 0x6ae4fe. */
static void cL4_fatal_6869bc(void) { cL4_fatal_fmt_76674(0x6ae4fe); }

/* FUN_006869e4 @ 0x6869e4   (est. cL4_fatal_fmt_6869e4) — fmt_76688 arg 0x6ae4fe. */
static void cL4_fatal_6869e4(void) { cL4_fatal_fmt_76688(0x6ae4fe); }

/* FUN_00686a0c @ 0x686a0c   (est. cL4_assert_abort_686a0c)
 * Abort sequence ending in the shared noreturn panic cL4_fatal_76650(). */
static void cL4_assert_abort_686a0c(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a(); cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal_76650();
}

/* FUN_00686a54 @ 0x686a54   (est. cL4_fatal_686a54) — panic msg @0x6ae156. */
static void cL4_fatal_686a54(void) { cL4_fatal(0x6ae156); }

/* FUN_00686a8c @ 0x686a8c   (est. cL4_map_flush)
 * Bumps a global counter (_DAT_00700248), allocates a fresh context
 * (cL4_ctx_new), maps a 0x4000-byte region into it, copies the region into
 * the target context, then runs the supervisor call in a retry loop while the
 * flag at param_4+0x68 is 1. Confidence: medium
 * Notes: writes _DAT_00700248; helpers FUN_00668c78/00678ae0/00672f64. */
static void cL4_map_flush(word_t p1, word_t *src, word_t *dst, word_t p4)
{
    word_t ctx;

    cL4_counter_0248 = cL4_counter_0248 + 1;   /* _DAT_00700248++ */
    ctx = cL4_ctx_new();
    cL4_ctx_map(ctx, *src, 0x4000, 1, 0);
    cL4_ctx_copy(*src, 0x4000, *dst, 0, 0);
    do {
        cL4_supervisor_call();
    } while (*(long *)(p4 + 0x68) == 1);
}

/* FUN_00686b10 @ 0x686b10   (est. cL4_assert_abort_686b10) — abort seq, msg @0x6aed40. */
static void cL4_assert_abort_686b10(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a(); cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6aed40);
}

/* FUN_00686b64 @ 0x686b64   (est. cL4_syscall_err_686b64)
 * Syscall-result handler like cL4_syscall_err_686930; abort msg @0x6aeba6. */
static void cL4_syscall_err_686b64(word_t p1, word_t p2, word_t p3)
{
    cL4_noop_765e4();
    do {
        cL4_supervisor_call();
    } while (p3 == 1);
    if ((p3 & 0xff) == 0) {
        cL4_noop_765fc();
        return;
    }
    cL4_syscall_validate(0, 0, 0);
    cL4_ec_fill_c();
    cL4_trace_fault_record(0);
    cL4_ec_fill((word_t *)0, 0);
    cL4_fatal(0x6aeba6);
}

/* FUN_00686c04 @ 0x686c04   (est. cL4_fatal_fmt_686c04) — fmt_7669c arg 0x6aee06. */
static void cL4_fatal_686c04(void) { cL4_fatal_fmt_7669c(0x6aee06); }

/* FUN_00686c2c @ 0x686c2c   (est. cL4_assert_abort_686c2c) — abort seq → cL4_fatal_76650(). */
static void cL4_assert_abort_686c2c(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a(); cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal_76650();
}

/* FUN_00686c74 @ 0x686c74   (est. cL4_fatal_686c74) — panic msg @0x6ac205. */
static void cL4_fatal_686c74(void) { cL4_fatal(0x6ac205); }

/* FUN_00686c8c @ 0x686c8c   (est. cL4_ec_trace_abort_686c8c)
 * Records an error descriptor for the current context, traces it, fills a
 * second error descriptor, then panics with msg @0x6a71a1. Noreturn.
 * Confidence: medium */
static void cL4_ec_trace_abort_686c8c(word_t p1, word_t p2, word_t p3)
{
    word_t ctx;
    word_t buf[4];

    ctx = cL4_current_ctx;
    cL4_ec_fill(buf, 0);
    cL4_trace_fault_record(ctx);
    cL4_ec_fill((word_t *)p3, p1);
    cL4_fatal(0x6a71a1);
}

/* FUN_00686d10 @ 0x686d10   (est. cL4_assert_abort_686d10) — abort seq → cL4_fatal_76650(). */
static void cL4_assert_abort_686d10(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a(); cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal_76650();
}

/* FUN_00686d58 @ 0x686d58   (est. cL4_fatal_686d58) — panic msg @0x6ad560. */
static void cL4_fatal_686d58(void) { cL4_fatal(0x6ad560); }

/* FUN_00686d90 @ 0x686d90   (est. cL4_fatal_686d90) — panic msg @0x6ad5d3. */
static void cL4_fatal_686d90(void) { cL4_fatal(0x6ad5d3); }

/* FUN_00686dc8 @ 0x686dc8   (est. cL4_fatal_686dc8) — panic msg @0x6ad8c1. */
static void cL4_fatal_686dc8(void) { cL4_fatal(0x6ad8c1); }

/* FUN_00686e00 @ 0x686e00   (est. cL4_fatal_686e00) — panic msg @0x6ad83f. */
static void cL4_fatal_686e00(void) { cL4_fatal(0x6ad83f); }

/* FUN_00686e38 @ 0x686e38   (est. cL4_fatal_686e38) — panic msg @&DAT_006ad928. */
static void cL4_fatal_686e38(void) { cL4_fatal(0x6ad928); }

/* FUN_00686e70 @ 0x686e70   (est. cL4_fatal_686e70) — panic msg @0x6abe1a. */
static void cL4_fatal_686e70(void) { cL4_fatal(0x6abe1a); }

/* FUN_00686ea8 @ 0x686ea8   (est. cL4_fatal_686ea8) — panic msg @0x6acc25. */
static void cL4_fatal_686ea8(void) { cL4_fatal(0x6acc25); }

/* FUN_00686ee0 @ 0x686ee0   (est. cL4_fatal_fmt_686ee0) — fmt_76660 arg 0x6aee7e. */
static void cL4_fatal_686ee0(void) { cL4_fatal_fmt_76660(0x6aee7e); }

/* FUN_00686f08 @ 0x686f08   (est. cL4_fatal_fmt_686f08) — fmt_76660 arg 0x6aee7e. */
static void cL4_fatal_686f08(void) { cL4_fatal_fmt_76660(0x6aee7e); }

/* FUN_00686f30 @ 0x686f30   (est. cL4_fatal_686f30) — panic msg @0x6ac9c3. */
static void cL4_fatal_686f30(void) { cL4_fatal(0x6ac9c3); }

/* FUN_00686f68 @ 0x686f68   (est. cL4_fatal_686f68) — panic msg @0x6ad137. */
static void cL4_fatal_686f68(void) { cL4_fatal(0x6ad137); }

/* FUN_00686f94 @ 0x686f94   (est. cL4_vtbl_dispatch_write)
 * Dispatches through a vtable slot: calls (*(fn*)(*(param_1+0xb8)+0x10))
 * with param_1+0xb0, runs the supervisor call in a retry loop (while
 * param_2==1), then stores param_4 into a field (offset +0x18) of the object
 * reachable via param_3+0x28. Confidence: low (indirect/obscured) */
static void cL4_vtbl_dispatch_write(word_t p1, word_t p2, word_t p3, word_t p4)
{
    void (**vtbl)(word_t);
    word_t *node;

    vtbl = (void (**)(word_t))(*(word_t *)(p1 + 0xb8));
    (vtbl[2])(*(word_t *)(p1 + 0xb0));         /* (+0x10 slot = index 2) */
    do {
        cL4_supervisor_call();
    } while (p2 == 1);
    node = *(word_t **)(*(word_t *)(p3 + 0x28) + 8);
    if (*(word_t *)(node + 3) == 0) {          /* +0x18 slot empty */
        *(word_t *)(node + 3) = p4;
    }
}

/* FUN_00686ffc @ 0x686ffc   (est. cL4_assert_abort_686ffc) — abort seq, msg @0x6ad37f. */
static void cL4_assert_abort_686ffc(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a(); cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ad37f);
}

/* FUN_00687050 @ 0x687050   (est. cL4_assert_abort_687050)
 * Abort sequence with cL4_noop_76614 (@0x68706c), msg @0x6ae96e. */
static void cL4_assert_abort_687050(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_76614();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae96e);
}

/* FUN_00687098 @ 0x687098   (est. cL4_syscall_err_687098)
 * Syscall-result handler like cL4_syscall_err_686930; abort msg @0x6ae745. */
static void cL4_syscall_err_687098(word_t p1, word_t p2, word_t p3)
{
    cL4_noop_765e4();
    do {
        cL4_supervisor_call();
    } while (p3 == 1);
    if ((p3 & 0xff) == 0) {
        cL4_noop_765fc();
        return;
    }
    cL4_syscall_validate(0, 0, 0);
    cL4_ec_fill_c();
    cL4_noop_76614();
    cL4_trace_fault_record(0);
    cL4_ec_fill((word_t *)0, 0);
    cL4_fatal(0x6ae745);
}

/* FUN_00687124 @ 0x687124   (est. cL4_assert_abort_687124)
 * Abort sequence with cL4_noop_7663c (@0x687140), msg @0x6ae819. */
static void cL4_assert_abort_687124(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_7663c();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae819);
}

/* FUN_00687174 @ 0x687174   (est. cL4_assert_abort_687174)
 * Abort sequence with cL4_noop_7663c (@0x687190), msg @0x6ae887. */
static void cL4_assert_abort_687174(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_7663c();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae887);
}

/* FUN_006871c4 @ 0x6871c4   (est. cL4_count_inc_1c8)
 * Increments the global counter _DAT_007001c8. Confidence: high */
static void cL4_count_inc_1c8(void) { cL4_counter_1c8 = cL4_counter_1c8 + 1; }

/* FUN_006871d8 @ 0x6871d8   (est. cL4_count_inc_1d8)
 * Increments the global counter _DAT_007001d8. Confidence: high */
static void cL4_count_inc_1d8(void) { cL4_counter_1d8 = cL4_counter_1d8 + 1; }

/* FUN_006871ec @ 0x6871ec   (est. cL4_count_inc_1d4)
 * Increments the global counter _DAT_007001d4. Confidence: high */
static void cL4_count_inc_1d4(void) { cL4_counter_1d4 = cL4_counter_1d4 + 1; }

/* FUN_00687200 @ 0x687200   (est. cL4_count_inc_1dc)
 * Increments the global counter _DAT_007001dc. Confidence: high */
static void cL4_count_inc_1dc(void) { cL4_counter_1dc = cL4_counter_1dc + 1; }

/* FUN_00687214 @ 0x687214   (est. cL4_assert_abort_687214)
 * Abort sequence with cL4_noop_7663c (@0x687230), msg @0x6ae9e8. */
static void cL4_assert_abort_687214(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_7663c();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae9e8);
}

/* FUN_00687264 @ 0x687264   (est. cL4_assert_abort_687264)
 * Abort sequence with cL4_noop_7663c (@0x687280), msg @0x6ae2f5. */
static void cL4_assert_abort_687264(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_7663c();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae2f5);
}

/* FUN_006872b4 @ 0x6872b4   (est. cL4_assert_abort_6872b4)
 * Abort sequence with cL4_noop_7663c (@0x6872d0), msg @0x6ae392. */
static void cL4_assert_abort_6872b4(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_7663c();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae392);
}

/* FUN_00687304 @ 0x687304   (est. cL4_assert_abort_687304)
 * Abort sequence with cL4_noop_7663c (@0x687320), msg @0x6aeae2. */
static void cL4_assert_abort_687304(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_7663c();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6aeae2);
}

/* FUN_00687354 @ 0x687354   (est. cL4_assert_abort_687354)
 * Abort sequence with cL4_noop_76614 (@0x687370), msg @0x6ae745. */
static void cL4_assert_abort_687354(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_76614();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6ae745);
}

/* FUN_0068739c @ 0x68739c   (est. cL4_assert_abort_68739c)
 * Abort sequence with cL4_noop_76614 (@0x6873b8), msg @0x6aeb60. */
static void cL4_assert_abort_68739c(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_76614();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6aeb60);
}

/* FUN_006873e4 @ 0x6873e4   (est. cL4_assert_abort_6873e4)
 * Abort sequence with cL4_noop_76614 (@0x687400), msg @0x6aeba6. */
static void cL4_assert_abort_6873e4(void)
{
    cL4_noop_65f454(); cL4_ec_fill_a();
    cL4_noop_76614();
    cL4_trace_fault_record(0); cL4_ec_fill_b();
    cL4_fatal(0x6aeba6);
}

/* FUN_0068742c @ 0x68742c   (est. cL4_fatal_68742c) — panic msg @0x6ae79c. */
static void cL4_fatal_68742c(void) { cL4_fatal(0x6ae79c); }

/* FUN_00687464 @ 0x687464   (est. cL4_fatal_fmt_687464) — fmt_76674 arg 0x6ae787. */
static void cL4_fatal_687464(void) { cL4_fatal_fmt_76674(0x6ae787); }

/* FUN_0068748c @ 0x68748c   (est. cL4_fatal_fmt_68748c) — fmt_76688 arg 0x6ae787. */
static void cL4_fatal_68748c(void) { cL4_fatal_fmt_76688(0x6ae787); }

/* FUN_006874b4 @ 0x6874b4   (est. cL4_trace_fault_record2)
 * Identical to cL4_trace_fault_record (FUN_006864cc): trace event, raw
 * record, queue flush for the current context. Confidence: high */
static void cL4_trace_fault_record2(word_t tag)
{
    cL4_trace_fault(tag, 0x6a53b8);
    cL4_trace_rec(cL4_current_ctx, 0, (word_t)&tag);
    cL4_trace_flush(10, cL4_current_ctx);
}

/* FUN_00687524 @ 0x687524   (est. cL4_fatal_687524) — panic msg @&DAT_006af078. */
static void cL4_fatal_687524(void) { cL4_fatal(0x6af078); }

/* FUN_00687550 @ 0x687550   (est. cL4_fatal_687550)
 * Noreturn; panics via cL4_fatal_79394 (fixed msg @0x6afd4f). */
static void cL4_fatal_687550(void) { cL4_fatal_79394(); }

/* FUN_00687564 @ 0x687564   (est. cL4_assert_abort_687564)
 * Assertion-abort sequence (check 79348/793c4 + trace record 2), panic msg
 * @0x6afb59. Noreturn. Confidence: high */
static void cL4_assert_abort_687564(void)
{
    cL4_noop_65f454();
    cL4_check_79348();
    cL4_trace_fault_record2(0);
    cL4_check_793c4();
    cL4_fatal(0x6afb59);
}

/* FUN_006875c0 @ 0x6875c0   (est. cL4_assert_abort_6875c0)
 * Assertion-abort sequence (79348/793c4 + trace), panic msg @0x6a71a1. */
static void cL4_assert_abort_6875c0(void)
{
    cL4_noop_65f454();
    cL4_check_79348();
    cL4_trace_fault_record2(0);
    cL4_check_793c4();
    cL4_fatal(0x6a71a1);
}

/* FUN_0068761c @ 0x68761c   (est. cL4_fatal_68761c) — panic msg @0x6af7a8. */
static void cL4_fatal_68761c(void) { cL4_fatal(0x6af7a8); }

/* FUN_00687654 @ 0x687654   (est. cL4_fatal_793_687654) — cL4_fatal_793b0 arg 0x6af3d6. */
static void cL4_fatal_687654(void) { cL4_fatal_793b0(0x6af3d6); }

/* FUN_0068767c @ 0x68767c   (est. cL4_assert_abort_68767c)
 * Assertion-abort sequence (79348/79368/793c4 + trace) ending in the shared
 * noreturn cL4_fatal_793d0. Noreturn. Confidence: high */
static void cL4_assert_abort_68767c(void)
{
    cL4_noop_65f454();
    cL4_check_79348();
    cL4_check_79368();
    cL4_trace_fault_record2(0);
    cL4_check_793c4();
    cL4_fatal_793d0();
}

/* FUN_006876a4 @ 0x6876a4   (est. cL4_fatal_793_6876a4) — cL4_fatal_793b0 arg 0x6af46a. */
static void cL4_fatal_6876a4(void) { cL4_fatal_793b0(0x6af46a); }

/* FUN_006876cc @ 0x6876cc   (est. cL4_trace_obj_lookup_6876cc)
 * Classifies the current context's type, records a trace/fault event for it
 * (@0x6afd87), then looks up/releases the context object. Confidence: medium
 * Notes: ctx from _DAT_006b4368; helpers FUN_006775c0/0067d1f0/0067d190. */
static void cL4_trace_obj_lookup_6876cc(void)
{
    word_t ctx;

    ctx = cL4_current_ctx;
    cL4_type_classify(0, 0);
    cL4_trace_fault(ctx, 0x6afd87);
    cL4_obj_lookup(cL4_current_ctx);
}

/* FUN_00687758 @ 0x687758   (est. cL4_fatal_793_687758) — cL4_fatal_793e0 arg 0x6afe99. */
static void cL4_fatal_687758(void) { cL4_fatal_793e0(0x6afe99); }

/* FUN_00687784 @ 0x687784   (est. cL4_trace_obj_lookup_687784)
 * Records a trace/fault event for the current context (@0x6afdf9) then looks
 * up/releases the context object. Confidence: high
 * Notes: ctx from _DAT_006b4368; helpers FUN_0067d1f0/0067d190. */
static void cL4_trace_obj_lookup_687784(void)
{
    cL4_trace_fault(cL4_current_ctx, 0x6afdf9);
    cL4_obj_lookup(cL4_current_ctx);
}

/* FUN_006877ec @ 0x6877ec   (est. cL4_fatal_793_6877ec) — cL4_fatal_793b0 arg 0x6af489. */
static void cL4_fatal_6877ec(void) { cL4_fatal_793b0(0x6af489); }

/* FUN_00687814 @ 0x687814   (est. cL4_fatal_687814) — panic msg @0x6af591. */
static void cL4_fatal_687814(void) { cL4_fatal(0x6af591); }

/* FUN_0068784c @ 0x68784c   (est. cL4_bounds_check_copy)
 * Bounds-checked single-element copy. Runs the supervisor call in a retry
 * loop (while *param_1==1), then, if the element at param_3+*param_2 lies
 * within [param_3, param_4), copies it to *param_5. Returns true on any
 * overflow/out-of-bounds condition (the decompiler's overlap test), false
 * on success. Confidence: medium */
static bool cL4_bounds_check_copy(long *p1, long *p2, word_t *p3, word_t *p4, word_t *p5)
{
    word_t *elem, *next;

    do {
        cL4_supervisor_call();
    } while (*p1 == 1);

    elem = p3 + *p2;
    next = elem + 1;
    if ((elem >= p3 && p4 >= next) && next >= elem) {
        *p5 = *elem;
    }
    /* overflow / out-of-bounds overlap test */
    return (elem < p3 || p4 < next) || next < elem;
}

/* FUN_006878a0 @ 0x6878a0   (est. cL4_fatal_793_6878a0) — cL4_fatal_793e0 arg 0x6af662. */
static void cL4_fatal_6878a0(void) { cL4_fatal_793e0(0x6af662); }

/* FUN_006878cc @ 0x6878cc   (est. cL4_assert_abort_6878cc)
 * Assertion-abort sequence (79348/793c4 + trace), panic msg @0x6af68f. */
static void cL4_assert_abort_6878cc(void)
{
    cL4_noop_65f454();
    cL4_check_79348();
    cL4_trace_fault_record2(0);
    cL4_check_793c4();
    cL4_fatal(0x6af68f);
}

/* FUN_00687928 @ 0x687928   (est. cL4_fatal_687928) — panic msg @0x6af6de. */
static void cL4_fatal_687928(void) { cL4_fatal(0x6af6de); }

/* FUN_00687960 @ 0x687960   (est. cL4_fatal_687960) — panic msg @0x6b04c5. */
static void cL4_fatal_687960(void) { cL4_fatal(0x6b04c5); }

/* FUN_00687998 @ 0x687998   (est. cL4_assert_abort_687998)
 * Assertion-abort sequence (79348/793c4 + trace), panic msg @0x6b01cc. */
static void cL4_assert_abort_687998(void)
{
    cL4_noop_65f454();
    cL4_check_79348();
    cL4_trace_fault_record2(0);
    cL4_check_793c4();
    cL4_fatal(0x6b01cc);
}

/* FUN_006879f4 @ 0x6879f4   (est. cL4_fatal_6879f4) — panic msg @0x6b0ce5. */
static void cL4_fatal_6879f4(void) { cL4_fatal(0x6b0ce5); }

/* FUN_00687a2c @ 0x687a2c   (est. cL4_fatal_687a2c) — panic msg @0x6b077c. */
static void cL4_fatal_687a2c(void) { cL4_fatal(0x6b077c); }

/* FUN_00687a64 @ 0x687a64   (est. cL4_fatal_687a64) — panic msg @0x6b0e22. */
static void cL4_fatal_687a64(void) { cL4_fatal(0x6b0e22); }

/* FUN_00687a9c @ 0x687a9c   (est. cL4_fatal_687a9c) — panic msg @0x6b08e3. */
static void cL4_fatal_687a9c(void) { cL4_fatal(0x6b08e3); }

/* FUN_00687ad4 @ 0x687ad4   (est. cL4_fatal_687ad4) — panic msg @0x6b0995. */
static void cL4_fatal_687ad4(void) { cL4_fatal(0x6b0995); }

/* FUN_00687b0c @ 0x687b0c   (est. cL4_fatal_687b0c) — panic msg @0x6b0b54. */
static void cL4_fatal_687b0c(void) { cL4_fatal(0x6b0b54); }

/* FUN_00687b48 @ 0x687b48   (est. cL4_fatal_687b48) — panic msg @0x6b1023. */
static void cL4_fatal_687b48(void) { cL4_fatal(0x6b1023); }
