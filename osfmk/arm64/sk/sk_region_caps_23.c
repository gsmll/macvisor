/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 23: 0x80000-0x100000 caps region, syscall/exception dispatch +
 * capability-operation wrappers.
 * All names are estimates unless string/header matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 *
 * The FUN_00100xxx family is the shared cL4 syscall trampoline: a
 * register-saving prologue / restore epilogue (FUN_00100a68 prologue,
 * FUN_00100a84 epilogue), with the body emitting a message/error via
 * thunk_FUN_002acbb8 (push a {tag,value} message word), FUN_003a25d4
 * (finalize/publish a message), FUN_00294bdc (emit a 3-word message),
 * and FUN_003a261c (masked pointer probe). FUN_0011d7e8 is the noreturn
 * stack-canary/return-address check failure.
 * ------------------------------------------------------------------ */
extern unsigned long cL4_alloc_obj(unsigned long size, unsigned long tag); /* FUN_0036a940 */
extern void cL4_ref_retain(unsigned long obj);                          /* FUN_0036b270 */
extern void cL4_ref_release(unsigned long obj);                         /* FUN_0036b118 */
extern void cL4_lo_lock(unsigned long obj);                             /* FUN_0036a1a0 */
extern void cL4_enter_guarded(unsigned long obj);                       /* FUN_0036986c */
extern void cL4_bad_state(void);                                        /* FUN_0036b6f4 */
extern void cL4_done(void);                                             /* FUN_0036b6ac */
extern void cL4_msg_copy_words(void *dst, unsigned long a, unsigned long b); /* FUN_00369efc */
extern void cL4_report_hex(unsigned int word, unsigned long tag);       /* FUN_00100f58 */
extern void cL4_push_word(unsigned long tag, unsigned long value);      /* thunk_FUN_002acbb8 */
extern void cL4_emit_3words(unsigned long a, unsigned long b, unsigned int c); /* FUN_00294bdc */
extern void cL4_publish(unsigned long v);                               /* FUN_003a25d4 */
extern unsigned long cL4_masked_ptr(unsigned long p);                   /* FUN_003a261c */
extern void cL4_restore_return(void);                                   /* FUN_0011d7e8 (noreturn) */
extern void cL4_msg_build0(unsigned long a, unsigned long b, unsigned long c, unsigned long d,
                           ...);                                        /* FUN_00377824/FUN_00377bec */
extern void cL4_log_string(unsigned long addr);                         /* FUN_00086840 */
extern unsigned long cL4_sched_yield(void);                             /* FUN_0006d450 */
extern void cL4_lock_state(long obj);                                   /* FUN_0006b2dc / FUN_0006b2ec */
extern unsigned long cL4_alloc_cap(unsigned long size);                 /* FUN_0036a908 */
extern void cL4_free(void *p, unsigned long size);                      /* thunk_FUN_00012568 */
extern void cL4_msg_collect(void *out);                                 /* FUN_000fda88 defined below */
extern void cL4_grow_buf(void);                                         /* FUN_000824e4 / FUN_000824c4 */
extern void cL4_dynalloc(unsigned long size, unsigned long tag);        /* FUN_0036a940 */

/* Global: the current thread / TCB pointer (_DAT_006c0380). */
extern unsigned long cL4_current_thread;

/* ------------------------------------------------------------------ *
 * Forward declarations for functions defined later in this file.
 * ------------------------------------------------------------------ */
void cap_publish_init(unsigned long *rec, unsigned long flag);
void cap_publish_setup(unsigned long *frame);
void cap_publish_with_vtable(unsigned long payload, unsigned long *obj, unsigned long flag);
void cap_op_dispatch(void (*op)(void));
void cap_op_dispatch_a(void);
void cap_op_dispatch_c(void);
void cap_op_dispatch_h(void);
void cap_op_dispatch_j(void);
void cap_op_dispatch_l(unsigned long p1, unsigned long p2, unsigned long p3,
                       unsigned long p4, unsigned int p5, unsigned long p6,
                       unsigned int p7, unsigned int p8, unsigned int p9,
                       unsigned long p10, unsigned long p11, unsigned long p12,
                       unsigned long p13);
void cap_op_dispatch_n(void);
void cap_op_mint_dispatch(unsigned long, unsigned long, unsigned long, unsigned long,
                          unsigned int, unsigned long, unsigned long, unsigned int,
                          unsigned long, long, unsigned long);
void cap_delete_dispatch(void);
void cap_emit_element(unsigned long, unsigned long, unsigned long, unsigned long,
                      unsigned long, unsigned long *);
unsigned long cap_iter_find_match(unsigned long, unsigned long, unsigned long);
void cap_retain_setup(long cap);
unsigned long msg_emit_typed(unsigned long value, unsigned long tag, unsigned long a, unsigned long b);
void sc_op_generic5(unsigned long a, unsigned long b, unsigned long c, unsigned long d,
                    void (*op)(long, unsigned long, unsigned long, unsigned long));

/* ------------------------------------------------------------------ *
 * Capability-object publish / init helpers
 * ------------------------------------------------------------------ */

/* FUN_000f9b4c @ 0xf9b4c   (est. cap_publish_object)
 * Ghidra: void FUN_000f9b4c(void)
 * Publishes a capability/object into the per-object registry. If the
 * scheduler is not yet running (FUN_0006d450 == 0) it emits an error
 * message and re-enters the guarded loop; otherwise it resolves a cap
 * slot, records it in the current object frame and an auxiliary 0x18-byte
 * node, then retains the target. Falls to the bad-state handler otherwise.
 * Confidence: medium
 * Notes: GENTER-style message emission via FUN_0036993c/FUN_0036986c. */
void cap_publish_object(void)
{
    long sched;
    unsigned long cap;

    sched = cL4_sched_yield();                       /* FUN_0006d450 */
    if (sched == 0) {
        cL4_msg_build0(0x662d28, 0x662a78, 0, 0);    /* error message words */
        /* publish {0xd000000000000023, 0x80000000005c4a20, 1} */
        cL4_push_word(0xd000000000000023, 0x80000000005c4a20);
        cL4_enter_guarded(1);
        return;
    }
    cap = /* FUN_001000b8(0) */ 0;
    cap = /* FUN_000fd854(sched, cap): resolve+insert cap into frame */ 0;
    /* the resolved cap is stored in the current object frame +0x10 and in a
     * freshly allocated 0x18-byte aux node (+0x10), frame->+0x18 = node */
    if (/* unaff_x21 (err) == 0 */ 1) {
        /* frame->0x10 = cap; node = alloc(0x652a80,0x18); node->0x10 = cap;
         * frame->0x18 = node; retain(cap) */
        cL4_ref_retain(cap);
        return;
    }
    cL4_bad_state();
}

/* FUN_000f9c60 @ 0xf9c60   (est. cap_publish_dispatch)
 * Ghidra: void FUN_000f9c60(void)
 * Thin wrapper that delegates to the full publish routine.
 * Confidence: high */
void cap_publish_dispatch(void)
{
    unsigned long frame[8];
    /* FUN_000f9c94 */ cap_publish_setup(frame);
}

/* FUN_000f9c78 @ 0xf9c78   (est. cap_publish_setup_phase)
 * Ghidra: void FUN_000f9c78(undefined8 param_1)
 * Runs the phase-0 publish path with flag 0.
 * Confidence: high */
void cap_publish_setup_phase(unsigned char *rec)
{
    /* FUN_000fa034(rec, 0) */ cap_publish_init((unsigned long *)rec, 0);
}

/* FUN_000f9c94 @ 0xf9c94   (est. cap_publish_setup)
 * Ghidra: void FUN_000f9c94(long *param_1)
 * Sets up a capability-publish node: initializes a 40-byte stack record,
 * resolves a name/capability (FUN_00002534), links it into a 0x20-byte
 * node that carries the object and the resolved tag, and installs the
 * node as the current object's root. On success records the type/tag
 * words into the caller's frame.
 * Confidence: medium
 * Notes: FUN_00365b6c is a message/link builder; FUN_0036a940 allocs. */
void cap_publish_setup(unsigned long *frame)
{
    unsigned char rec[40];
    unsigned long resolved, node;

    cap_publish_setup_phase(rec);                    /* FUN_000f9c78 */
    if (/* err == 0 */ 1) {
        resolved = /* FUN_00002534(&0x64e8c8,&0x4c0720) */ 0;
        /* FUN_00365b6c(&tag, rec, resolved, 0x652ae0, 7) */
        node = cL4_alloc_obj(0x652a18, 0x20);        /* alloc node */
        /* node->0x10 = current obj; node->0x18 = resolved tag */
        frame[3] = 0x652a18;
        frame[4] = 0x6628f8;
        frame[0] = node;
        cL4_enter_guarded(0);
    }
}

/* FUN_000f9d7c @ 0xf9d7c   (est. cap_publish_reentry)
 * Ghidra: void FUN_000f9d7c(void)
 * Re-enters the publish dispatch path.
 * Confidence: high */
void cap_publish_reentry(void)
{
    /* FUN_000f9c60 */ cap_publish_dispatch();
}

/* FUN_000f9d94 @ 0xf9d94   (est. cap_publish_with_vtable)
 * Ghidra: void FUN_000f9d94(undefined8 param_1, long *param_2, ulong param_3)
 * Publishes an object through its vtable. Stores the payload pointer in
 * the current frame +0x10, invokes the object's vtable entry +0x1b8 to
 * serialize 9 message words into the frame, then calls the storage
 * object's vtable close callback (+0x70 if param_3&1 clear, else +0x68).
 * Releases all held references on both success and failure paths.
 * Confidence: low
 * Notes: vtable dispatch via *(**obj+0x1b8); FUN_0036b118 releases. */
void cap_publish_with_vtable(unsigned long payload, unsigned long *obj, unsigned long flag)
{
    unsigned long msgs[6];
    unsigned long close_cb;
    unsigned long *storage;

    (void)cL4_current_thread;                             /* frame base in x20 */
    *(unsigned long *)(cL4_current_thread + 0x10) = payload;
    close_cb = *(unsigned long *)(*obj + 0x1b8);    /* vtable serialize fn */
    cL4_enter_guarded(0);
    ((void (*)(unsigned long *, int, int, int, int, int))close_cb)(msgs, 9, 0, 0, 0, 0);
    if (/* err == 0 */ 1) {
        /* copy the 9 serialized words into the frame +0x18..+0x49 */
        storage = *(unsigned long **)(*(unsigned long *)(cL4_current_thread + 0x10) + 0x10);
        close_cb = *(unsigned long *)(*storage + ((flag & 1) ? 0x68 : 0x70));
        cL4_enter_guarded(0);
        ((void (*)(unsigned long *))close_cb)(msgs);
        cL4_ref_release((unsigned long)storage);
        cL4_ref_release((unsigned long)obj);
        cL4_ref_release(payload);
    } else {
        cL4_ref_release(payload);
        cL4_ref_release((unsigned long)obj);
        cL4_ref_release(*(unsigned long *)(cL4_current_thread + 0x10));
        cL4_bad_state();
    }
}

/* FUN_000f9f2c @ 0xf9f2c   (est. cap_publish_error_generic)
 * Ghidra: undefined1 [16] FUN_000f9f2c(void)
 * Emits a guarded error and returns the 16-byte message
 * {0xd00000000000002e, 0x80000000005c60e0} ("object not found"-style).
 * Confidence: medium
 * Notes: thunk_FUN_002acbb8 pushes message words; FUN_003a25d4 publishes. */
void cap_publish_error_generic(unsigned long out[2])
{
    cL4_push_word(0x1d, 0);                          /* FUN_002a4ab4 */
    cL4_publish(0xe000000000000000);                 /* begin message */
    cL4_push_word(0, 0);                             /* FUN_00027724 path */
    cL4_push_word(0x677830, 0x671df8);
    cL4_push_word(0, 0);
    cL4_publish(0);
    cL4_push_word(0x29, 0xe100000000000000);
    out[1] = 0x80000000005c60e0;
    out[0] = 0xd00000000000002e;
}

/* FUN_000f9ff4 @ 0xf9ff4   (est. cap_publish_error_wrap)
 * Ghidra: void FUN_000f9ff4(void)
 * Thin wrapper for the generic publish error.
 * Confidence: high */
void cap_publish_error_wrap(void)
{
    unsigned long m[2];
    cap_publish_error_generic(m);
}

/* FUN_000fa018 @ 0xfa018   (est. cap_publish_init_phase1)
 * Ghidra: void FUN_000fa018(undefined8 param_1)
 * Runs the phase-1 publish path (flag 1).
 * Confidence: high */
void cap_publish_init_phase1(unsigned long obj)
{
    unsigned long frame[8];
    /* FUN_000fa034(obj, 1) */ cap_publish_init(frame, 1);
}

/* FUN_000fa034 @ 0xfa034   (est. cap_publish_init)
 * Ghidra: void FUN_000fa034(undefined8 *param_1, undefined8 param_2)
 * Allocates a 0x51-byte object of tag 0x652ae0, runs the vtable publish
 * (FUN_000f9d94), and on success records the type words (0x652ae0,
 * 0x662960) plus the allocated object into the caller's record.
 * Confidence: low
 * Notes: FUN_0036a940 alloc; FUN_0036b270 retain. */
void cap_publish_init(unsigned long *rec, unsigned long flag)
{
    unsigned long obj;

    obj = cL4_alloc_obj(0x652ae0, 0x51);             /* allocate object */
    cL4_enter_guarded(0);
    cL4_enter_guarded(flag);
    obj = /* FUN_000f9d94() */ 0;
    if (/* err == 0 */ 1) {
        rec[3] = 0x652ae0;
        rec[4] = 0x662960;
        rec[0] = obj;
    }
}

/* FUN_000fa0d0 @ 0xfa0d0   (est. cap_err_not_authorized)
 * Ghidra: undefined1 [16] FUN_000fa0d0(void)
 * Returns the static 16-byte error {0xd000000000000016,
 * 0x80000000004c3eb0} ("not authorized" permission error).
 * Confidence: medium */
void cap_err_not_authorized(unsigned long out[2])
{
    out[1] = 0x80000000004c3eb0;
    out[0] = 0xd000000000000016;
}

/* FUN_000fa0ec / FUN_000fa0f0 — wrappers to phase-1 publish. */
void cap_publish_phase1_a(void) { cap_publish_init_phase1(0); }
void cap_publish_phase1_b(void) { cap_publish_init_phase1(0); }

/* FUN_000fa104 / FUN_000fa108 — wrappers to phase-0 publish. */
void cap_publish_phase0_a(void) { cap_publish_setup_phase(0); }
void cap_publish_phase0_b(void) { cap_publish_setup_phase(0); }

/* FUN_000fa11c / FUN_000fa120 — return the 0xd000000000000016 error word. */
unsigned long cap_err_not_auth_a(void)
{
    unsigned long m[2];
    cap_err_not_authorized(m);
    return 0xd000000000000016;
}
unsigned long cap_err_not_auth_b(void)
{
    unsigned long m[2];
    cap_err_not_authorized(m);
    return 0xd000000000000016;
}

/* FUN_000fa1b0 @ 0xfa1b0   (est. cap_destroy_obj)
 * Ghidra: void FUN_000fa1b0(void)
 * Destroys the capability object at tag 0x6529b0.
 * Confidence: low
 * Notes: FUN_00077770 is an object teardown. */
void cap_destroy_obj(void)
{
    /* FUN_00077770(0x6529b0) */;
}

/* FUN_000fa1bc / FUN_000fa1c0 — wrappers to the publish re-entry. */
void cap_publish_reentry_a(void) { cap_publish_reentry(); }
void cap_publish_reentry_b(void) { cap_publish_reentry(); }

/* FUN_000fa1e0 @ 0xfa1e0   (est. cap_op_enter)
 * Ghidra: void FUN_000fa1e0(void)
 * Enters a capability operation through FUN_00084af0.
 * Confidence: medium */
void cap_op_enter(void)
{
    unsigned long m[2];
    /* FUN_000fa374(FUN_00084af0) */ cap_op_dispatch((void (*)(void))0);
}

/* FUN_000fa218 / FUN_000fa28c / FUN_000fa300 @ 0xfa218..0xfa300
 *   (est. cap_err_Brokerde_<kind>)
 * Ghidra: undefined1 [16] FUN_000fa218(void)
 * Return a 16-byte "Brokerde"-prefixed error message (tag varies:
 * 0x22/0x22/0x1c; data pointer varies). Emits message words first.
 * Confidence: medium
 * Notes: literal 0x646572656b6f7242 = "Brokerde" (LE). */
void cap_err_Brokerde_a(unsigned long out[2])
{
    cL4_push_word(0xd000000000000022, 0x80000000005c6570);
    cL4_push_word(0x29, 0xe100000000000000);
    out[1] = 0xe900000000000028;
    out[0] = 0x646572656b6f7242;
}
void cap_err_Brokerde_b(unsigned long out[2])
{
    cL4_push_word(0xd000000000000022, 0x80000000005c6540);
    cL4_push_word(0x29, 0xe100000000000000);
    out[1] = 0xe900000000000028;
    out[0] = 0x646572656b6f7242;
}
void cap_err_Brokerde_c(unsigned long out[2])
{
    cL4_push_word(0xd00000000000001c, 0x80000000005c5db0);
    cL4_push_word(0x29, 0xe100000000000000);
    out[1] = 0xe900000000000028;
    out[0] = 0x646572656b6f7242;
}

/* FUN_000fa374 @ 0xfa374   (est. cap_op_dispatch)
 * Ghidra: undefined1 [16] FUN_000fa374(code *param_1)
 * Generic capability-operation dispatcher: acquires the current object
 * from the frame, runs the supplied operation callback, releases the
 * object, and emits the operation's result as a message word.
 * Confidence: low
 * Notes: FUN_00100d08/FUN_00100e34 frame enter/exit; thunk push result. */
void cap_op_dispatch(void (*op)(void))
{
    unsigned long m[2];
    unsigned long obj;

    (void)cL4_current_thread;                              /* FUN_00100d08() */
    obj = *(unsigned long *)(cL4_current_thread + 0x10);
    cL4_enter_guarded(obj);
    op();
    cL4_ref_release(obj);
    cL4_push_word(m[0], m[1]);
    cL4_publish(m[1]);
    cL4_enter_guarded(0);
}

/* FUN_000fa3f8 @ 0xfa3f8   (est. cap_op_dispatch_msg)
 * Ghidra: undefined1 [16] FUN_000fa3f8(undefined8 param_1, undefined8 param_2)
 * Capability operation dispatcher with a two-argument payload. Builds a
 * message (FUN_00377824/FUN_00377bec), runs the operation via the
 * dispatch target FUN_000fa4c8, and emits a tagged message result.
 * Confidence: low
 * Notes: FUN_002dc0d0 combines result+error into a pair. */
void cap_op_dispatch_msg(unsigned long a, unsigned long b)
{
    unsigned long msg[3], op;

    (void)cL4_current_thread;                              /* FUN_00100d08() */
    op = /* FUN_000fa4c8(..) */ 0;
    ((void (*)(unsigned long, unsigned long))op)(a, b);
    cL4_msg_build0(0, b, a, 0x6074f0, 0x607508);
    cL4_msg_build0(b, a, 0, 0x6074f0, 0x607500);
    /* FUN_002dc0d0 combine */;
    cL4_push_word(0, 0);
    cL4_publish(0);
    cL4_enter_guarded(0);
}

/* FUN_000fa4c8 @ 0xfa4c8   (est. cap_dispatch_target)
 * Ghidra: long FUN_000fa4c8(ulong param_1)
 * Returns a dispatch target: if the low bit is set, follows the
 * pointer at (param_1 & ~1) and adds the 32-bit displacement at +0x10.
 * Confidence: low
 * Notes: PC-relative dispatch idiom (ADR-based jump table). */
long cap_dispatch_target(unsigned long p)
{
    if ((p & 1) != 0)
        p = *(unsigned long *)(p & 0xfffffffffffffffe);
    return (long)(p + 0x10) + (long)*(int *)(p + 0x10);
}

/* FUN_000fa550 @ 0xfa550   (est. cap_log_pair)
 * Ghidra: void FUN_000fa550(undefined8 param_1)
 * Emits a two-word message from param_1 split into lo/hi parts.
 * Confidence: low
 * Notes: FUN_00369efc copies a {lo,hi} word pair into the message. */
void cap_log_pair(unsigned long v)
{
    unsigned long w[2];
    w[0] = (unsigned int)v;
    w[1] = (unsigned int)(v >> 32);
    cL4_msg_copy_words(w, 0x65fa88, 0x65f980);
}

/* FUN_000fa59c / FUN_000fa5d8 / FUN_000fa658 / FUN_000fa694
 *   @ 0xfa59c..0xfa694 (est. cap_log_<tag>)
 * Ghidra: void FUN_000fa59c(undefined4 param_1)
 * Emit a hex log message with the given tag string pointer.
 * Confidence: low
 * Notes: FUN_00100f58(word, tag). */
void cap_log_tag_660318(unsigned int w) { cL4_report_hex(w, 0x660318); }
void cap_log_tag_660740(unsigned int w) { cL4_report_hex(w, 0x660740); }
void cap_log_tag_661d90(unsigned int w) { cL4_report_hex(w, 0x661d90); }
void cap_log_tag_662680(unsigned int w) { cL4_report_hex(w, 0x662680); }

/* FUN_000fa614 @ 0xfa614   (est. cap_log_pair_tag)
 * Ghidra: void FUN_000fa614(undefined8 param_1, undefined8 param_2)
 * Emits a two-word message with a tag.
 * Confidence: low */
void cap_log_pair_tag(unsigned long a, unsigned long b)
{
    unsigned long w[2];
    w[0] = a; w[1] = b;
    cL4_msg_copy_words(w, 0x6607d0, 0x660680);
}

/* FUN_000fa6d0 @ 0xfa6d0   (est. cap_log_triple)
 * Ghidra: void FUN_000fa6d0(undefined8 p1, undefined8 p2, undefined1 p3)
 * Emits a three-word message {p1, p2, p3}.
 * Confidence: low */
void cap_log_triple(unsigned long a, unsigned long b, unsigned char c)
{
    unsigned long w[3];
    w[0] = a; w[1] = b; w[2] = c;
    cL4_msg_copy_words(w, 0x662d28, 0x662a78);
}

/* ------------------------------------------------------------------ *
 * Capability operation dispatchers (delete / move / mint / revoke /
 * copy) — these share the cL4 syscall trampoline. Each performs an
 * operation check, walks a linked list of pending message words, and
 * emits a structured reply. The list-walk is the decompiler's view of
 * the "tagged word chain" traversed by cL4_msg_emit.
 * ------------------------------------------------------------------ */

/* FUN_000fa718 @ 0xfa718   (est. cap_delete_dispatch)
 * Ghidra: void FUN_000fa718(void)
 * Deletes a capability: checks the operation via the storage vtable,
 * walks the pending message-word chain (copying bytes), verifies the
 * tail length matches, and emits the reply. Falls to a breakpoint if
 * the chain length is inconsistent, and to the canary-check handler on
 * exit.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfa7f4) on length mismatch; FUN_0011d7e8
 *   is the noreturn return-address check. */
void cap_delete_dispatch(void)
{
    unsigned char b;
    unsigned long len, chain, probe;

    (void)cL4_current_thread;                              /* FUN_00100a68 prologue */
    cL4_enter_guarded(0);
    if (/* op check via vtable */ 1) {
        /* walk pending message chain; copy non-zero bytes into buffer */
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow buffer */ }
                /* append byte to buffer */
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            /* walk buffer consuming bytes, advancing the length */
            do {
                /* consume one byte */
            } while (/* more */ 0);
            if (len != b) {                         /* tail mismatch */
                /* SoftwareBreakpoint(1, 0xfa7f4) */
                cL4_enter_guarded(0);
            }
        }
        /* emit reply words via cL4_push_word / cL4_emit_3words */
        cL4_publish(0);
    }
    cL4_enter_guarded(0);
    /* canary check: FUN_0011d7e8 noreturn on failure */
}

/* FUN_000fa8f0 @ 0xfa8f0   (est. cap_op_dispatch_a)
 * Ghidra: void FUN_000fa8f0(void)
 * Capability-operation dispatcher variant: checks the op against the
 * frame's +0x10 target, walks the pending chain, and emits the reply.
 * Confidence: low
 * Notes: same trampoline shape as cap_delete_dispatch. */
void cap_op_dispatch_a(void)
{
    unsigned char b;
    unsigned long len, probe;
    long op;

    (void)cL4_current_thread;                              /* prologue */
    op = /* FUN_00100cec */ 0;
    if (/* op != 0 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume byte */ } while (/* more */ 0);
            if (len != b) {
                /* SoftwareBreakpoint(1, 0xfa9c8) */
            }
        }
        /* emit reply */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000faac4 @ 0xfaac4   (est. cap_op_dispatch_b)
 * Ghidra: void FUN_000faac4(void)
 * Capability-operation dispatcher variant targeting the frame's +0x48
 * field. Same trampoline shape as cap_op_dispatch_a.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0xfab9c) on length mismatch. */
void cap_op_dispatch_b(void)
{
    unsigned char b;
    unsigned long len, probe;
    long op;

    (void)cL4_current_thread;                              /* prologue */
    op = /* FUN_00100cec */ 0;
    if (/* op != 0 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume byte */ } while (/* more */ 0);
            if (len != b) {
                /* SoftwareBreakpoint(1, 0xfab9c) */
            }
        }
        /* emit reply */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fac98 @ 0xfac98   (est. cap_op_move_dispatch)
 * Ghidra: void FUN_000fac98(12 args)
 * Capability MOVE dispatcher: resolves the destination node
 * (FUN_000877e0/FUN_000aaeac), builds the operation, walks the pending
 * message-word chain, and emits a multi-part reply including the
 * operation result and two 3-word argument groups.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfae04) on chain mismatch; node build via
 *   FUN_000fda88; many in_stack_* spill slots for the reply groups. */
void cap_op_move_dispatch(unsigned long p1, unsigned long p2, unsigned long p3,
                          unsigned long p4, unsigned int p5, unsigned long p6,
                          unsigned long p7, unsigned int p8, unsigned long p9,
                          unsigned long p10, unsigned long p11)
{
    unsigned char b;
    unsigned long len, probe;
    unsigned long node;

    (void)cL4_current_thread;                              /* prologue */
    node = /* FUN_000877e0(p11) + FUN_000b3fdc(0) + FUN_000aaeac(p11) */ 0;
    if (/* node == 0 */ 0) {
        cL4_ref_release(p11);
        cL4_ref_release(p10);
        cL4_enter_guarded(0);
    } else {
        cap_publish_setup(0);                        /* FUN_000fda88 buffer */
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
                /* advance node list head/len */;
            }
        } while (/* more */ 0);
        len = /* node->2 */ 0;
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (/* head != tail */ 1) {
                /* SoftwareBreakpoint(1, 0xfae04) */
            }
        }
        /* emit reply: result + two 3-word groups */;
        cL4_push_word(p1, p2);
        cL4_push_word(0, 0xe500000000000000);
        cL4_emit_3words(p3, p4, p5);
        cL4_emit_3words(p6, p7, p8);
        cL4_ref_release(p11);
        cL4_ref_release(p10);
        cL4_enter_guarded(0);
    }
    /* canary check on exit */
}

/* FUN_000faf5c @ 0xfaf5c   (est. cap_op_frame_enter)
 * Ghidra: void FUN_000faf5c(void)
 * Enters the capability operation frame and runs FUN_000fcc6c.
 * Confidence: medium
 * Notes: FUN_000651bc is the exit/canary check. */
void cap_op_frame_enter(void)
{
    cL4_lock_state(0);
    /* FUN_000fcc6c */ cap_op_dispatch_c();
    /* FUN_000651bc */;
}

/* FUN_000fafb4 @ 0xfafb4   (est. cap_op_dispatch_d)
 * Ghidra: void FUN_000fafb4(void)
 * Capability-operation dispatcher: resolves the target from the frame
 * (+0x18 -> +0x48), checks against the scheduler domain, walks the
 * pending chain, emits a multi-part reply.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfb0a0) on mismatch; FUN_0009ea90 is a
 *   lookup/validate. */
void cap_op_dispatch_d(void)
{
    unsigned char b;
    unsigned long target, len, probe, sched;

    (void)cL4_current_thread;                              /* prologue */
    target = *(unsigned long *)(*(long *)(cL4_current_thread + 0x18) + 0x48);
    sched = cL4_sched_yield();                       /* FUN_0006d450 */
    if (/* FUN_0009ea90(target, sched) != 0 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfb0a0) */ }
        }
        /* emit reply with two 3-word groups */;
    }
    cL4_enter_guarded(0);
    /* FUN_000651bc */;
}

/* FUN_000fb1ac @ 0xfb1ac   (est. cap_op_dispatch_e)
 * Ghidra: void FUN_000fb1ac(void)
 * Capability-operation dispatcher targeting frame +0x48; same trampoline
 * shape. Emits a 3-part reply.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfb278) on mismatch. */
void cap_op_dispatch_e(void)
{
    unsigned char b;
    unsigned long len, probe;

    (void)cL4_current_thread;                              /* prologue */
    if (/* op via +0x48 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfb278) */ }
        }
        /* emit reply */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fb374 @ 0xfb374   (est. cap_op_mint_dispatch)
 * Ghidra: void FUN_000fb374(11 args)
 * Capability MINT dispatcher: resolves the operation from the source
 * node (+0x38/+0x40), walks the pending message-word chain, emits a
 * reply naming the minted endpoint (string ref "mintEndpoint").
 * Confidence: low
 * Notes: reads s_mintEndpoint___005c6886; SoftwareBreakpoint(1,0xfb594)
 *   on chain mismatch; stack canary -0x2c8502b44bfffed6. */
void cap_op_mint_dispatch(unsigned long p1, unsigned long p2, unsigned long p3,
                          unsigned long p4, unsigned int p5, unsigned long p6,
                          unsigned long p7, unsigned int p8, unsigned long p9,
                          long node, unsigned long p11)
{
    unsigned char b;
    unsigned long len, probe, op;

    op = /* FUN_00100418(node+0x38, p11, 3, 3, node+0x40) */ 0;
    if (op != 0) {
        cap_publish_setup(0);                        /* FUN_000fda88 buffer */
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume 16-byte entries */ } while (/* more */ 0);
            if (len != /* consumed */ 0) {
                /* SoftwareBreakpoint(1, 0xfb594) */
            }
        }
        /* emit reply: mint endpoint, result, two 3-word groups */;
        cL4_push_word(0x2820, 0xe200000000000000);
        cL4_push_word(0x202c29, 0xe300000000000000);
        cL4_push_word(p1, p2);
        cL4_push_word(0x207461202c, 0xe500000000000000);
        cL4_emit_3words(p3, p4, p5);
        cL4_push_word(0x3a, 0xe100000000000000);
        cL4_emit_3words(p6, p7, p8);
        cL4_push_word(0x3a, 0xe100000000000000);
        /* emit p9 */;
    }
    cL4_enter_guarded(node);
    /* stack canary check */
}

/* FUN_000fb7d0 @ 0xfb7d0   (est. cap_op_dispatch_f)
 * Ghidra: void FUN_000fb7d0(void)
 * Capability-operation dispatcher: validates a 64K-aligned shift, walks
 * the pending chain, emits a 3-part reply.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfb9bc) on invalid shift, 0xfb9c0 on
 *   chain mismatch. */
void cap_op_dispatch_f(void)
{
    unsigned char b;
    unsigned long len, probe;
    long sh;

    (void)cL4_current_thread;                              /* prologue */
    sh = /* FUN_0006b2dc */ 0;
    if (/* sh >> 0x32 != 0 */ 0) {
        /* SoftwareBreakpoint(1, 0xfb9bc) */
    }
    if (/* op != 0 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfb9c0) */ }
        }
        /* emit reply */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fb9c4 @ 0xfb9c4   (est. cap_op_dispatch_g)
 * Ghidra: void FUN_000fb9c4(void)
 * Capability-operation dispatcher with 64K-aligned shift and a resolve
 * check (FUN_00084824). Emits a 3-part reply.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfbbc0/0xfbbc4) on bad shift, 0xfbac0 on
 *   chain mismatch. */
void cap_op_dispatch_g(void)
{
    unsigned char b;
    unsigned long len, probe;
    long sh;

    (void)cL4_current_thread;                              /* prologue */
    sh = /* FUN_0006b2dc */ 0;
    if (/* sh < 0 */ 0) { /* SoftwareBreakpoint(1, 0xfbbc0) */ }
    if (/* sh >> 0x32 != 0 */ 0) { /* SoftwareBreakpoint(1, 0xfbbc4) */ }
    if (/* FUN_00084824(resolve, sh<<14, p3) != 0 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfbac0) */ }
        }
        /* emit reply */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fbbc8 @ 0xfbbc8   (est. cap_op_dispatch_g_enter)
 * Ghidra: void FUN_000fbbc8(void)
 * Enters the operation frame and runs FUN_000fbdcc.
 * Confidence: medium */
void cap_op_dispatch_g_enter(void)
{
    cL4_enter_guarded(0);
    /* FUN_000fbdcc */ cap_op_dispatch_h();
    /* FUN_000651bc */;
}

/* FUN_000fbbfc @ 0xfbbfc   (est. cap_op_dispatch_h)
 * Ghidra: void FUN_000fbbfc(void)
 * Capability-operation dispatcher with a zero-shift resolve check.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfbcd0) on chain mismatch. */
void cap_op_dispatch_h(void)
{
    unsigned char b;
    unsigned long len, probe;

    (void)cL4_current_thread;                              /* prologue */
    if (/* FUN_00084824(resolve, 0) != 0 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfbcd0) */ }
        }
        /* emit reply */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fbdcc @ 0xfbdcc   (est. cap_op_dispatch_i)
 * Ghidra: void FUN_000fbdcc(void)
 * Capability-operation dispatcher (list-scan variant). Scans a pending
 * message-word list, emits a multi-part reply.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfbf94) on chain mismatch. */
void cap_op_dispatch_i(void)
{
    unsigned char b;
    unsigned long len, probe;

    (void)cL4_current_thread;                              /* prologue */
    if (/* op via FUN_001000dc */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfbf94) */ }
        }
        /* emit reply with two 3-word groups */;
    }
    /* FUN_000651bc */;
}

/* FUN_000fbf98 @ 0xfbf98   (est. cap_op_dispatch_j_enter)
 * Ghidra: void FUN_000fbf98(void)
 * Enters the operation frame and runs FUN_000fbfcc.
 * Confidence: medium */
void cap_op_dispatch_j_enter(void)
{
    cL4_enter_guarded(0);
    /* FUN_000fbfcc */ cap_op_dispatch_j();
    /* FUN_000651bc */;
}

/* FUN_000fbfcc @ 0xfbfcc   (est. cap_op_dispatch_j)
 * Ghidra: void FUN_000fbfcc(void)
 * Capability-operation dispatcher (scheduler-domain check variant).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfc0c0) on chain mismatch. */
void cap_op_dispatch_j(void)
{
    unsigned char b;
    unsigned long len, probe, target, sched;

    (void)cL4_current_thread;                              /* prologue */
    target = *(unsigned long *)(*(long *)(cL4_current_thread + 0x10) + 0x48);
    sched = cL4_sched_yield();                       /* FUN_0006d450 */
    if (/* FUN_0009ea90(target, sched) != 0 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfc0c0) */ }
        }
        /* emit reply with two 3-word groups */;
    }
    cL4_enter_guarded(0);
    /* FUN_000651bc */;
}

/* FUN_000fc1cc @ 0xfc1cc   (est. cap_op_dispatch_k)
 * Ghidra: void FUN_000fc1cc(void)
 * Capability-operation dispatcher that builds a node (FUN_000fda88),
 * validates against the frame's +0x10 target, walks the pending chain,
 * and emits a 3-part reply.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfc30c) on chain mismatch. */
void cap_op_dispatch_k(void)
{
    unsigned char b;
    unsigned long len, probe, target;

    (void)cL4_current_thread;                              /* prologue */
    target = *(unsigned long *)(*(long *)(cL4_current_thread + 0x10) + 0x48);
    if (/* FUN_0009ea90(target, frame+0x10) == 0 */ 0) {
        cL4_ref_release(/* frame+0x10 */ 0);
    } else {
        cap_publish_setup(0);                        /* FUN_000fda88 */
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = /* node->2 */ 0;
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (/* head != tail */ 1) { /* SoftwareBreakpoint(1, 0xfc30c) */ }
        }
        /* emit reply with two 3-word groups */;
        cL4_ref_release(/* frame+0x10 */ 0);
    }
    cL4_enter_guarded(/* frame+0x8 */ 0);
}

/* FUN_000fc454 @ 0xfc454   (est. cap_op_dispatch_l)
 * Ghidra: void FUN_000fc454(void)
 * Capability-operation dispatcher (vtable check, 3-part reply).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfc640) on chain mismatch. */
void cap_op_dispatch_l(unsigned long p1, unsigned long p2, unsigned long p3,
                       unsigned long p4, unsigned int p5, unsigned long p6,
                       unsigned int p7, unsigned int p8, unsigned int p9,
                       unsigned long p10, unsigned long p11, unsigned long p12,
                       unsigned long p13)
{
    unsigned char b;
    unsigned long len, probe;

    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5; (void)p6;
    (void)p7; (void)p8; (void)p9; (void)p10; (void)p11; (void)p12; (void)p13;
    (void)cL4_current_thread;                              /* prologue */
    if (/* op via FUN_00100464 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfc640) */ }
        }
        /* emit reply */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fc644 @ 0xfc644   (est. cap_op_dispatch_m)
 * Ghidra: void FUN_000fc644(void)
 * Capability-operation dispatcher with a two-arg resolve check
 * (FUN_0005579c). Emits a 3-part reply.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfc800) on chain mismatch. */
void cap_op_dispatch_m(void)
{
    unsigned char b;
    unsigned long len, probe;

    (void)cL4_current_thread;                              /* prologue */
    if (/* FUN_0005579c() != 0 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfc800) */ }
        }
        /* emit reply with two 3-word groups */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fc804 @ 0xfc804   (est. cap_op_frame_enter2)
 * Ghidra: void FUN_000fc804(void)
 * Enters the operation frame and runs FUN_000fcc6c.
 * Confidence: medium */
void cap_op_frame_enter2(void)
{
    cL4_lock_state(0);
    /* FUN_000fcc6c */ cap_op_dispatch_n();
    /* FUN_000651bc */;
}

/* FUN_000fc85c @ 0xfc85c   (est. cap_op_dispatch_size)
 * Ghidra: void FUN_000fc85c(11 args)
 * Capability-operation dispatcher with a size-range check: validates the
 * requested size against FUN_0006d024, aligns a 0x4000 boundary, walks
 * the pending chain, and emits a 3-part reply.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfca70/0xfca74/0xfca78) on size/chain
 *   failures. */
void cap_op_dispatch_size(unsigned long p1, unsigned long p2, long p3, unsigned long p4,
                          long p5, unsigned long p6, unsigned long p7, unsigned long p8,
                          unsigned long p9, unsigned long p10, unsigned long p11)
{
    unsigned char b;
    unsigned long size, len, probe;

    (void)cL4_current_thread;                              /* prologue */
    size = /* FUN_0006d024(p11) */ 0;
    if (p11 < size) { /* SoftwareBreakpoint(1, 0xfca70) */ }
    if (/* p10 > 0xffffffffffffc000 */ 0) { /* SoftwareBreakpoint(1, 0xfca74) */ }
    if (/* op via FUN_00100464 */ 1) {
        do {
            b = *(unsigned char *)(p5 + p3);
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfca78) */ }
            p8 &= 0xffffffff;
        }
        /* emit reply: two 3-word groups */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fca7c @ 0xfca7c   (est. cap_op_dispatch_o)
 * Ghidra: void FUN_000fca7c(void)
 * Capability-operation dispatcher (2-arg node resolve, 3-part reply).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfcc68) on chain mismatch. */
void cap_op_dispatch_o(void)
{
    unsigned char b;
    unsigned long len, probe;

    (void)cL4_current_thread;                              /* prologue */
    if (/* FUN_00100418(node, ...) != 0 */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfcc68) */ }
        }
        /* emit reply */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fcc6c @ 0xfcc6c   (est. cap_op_dispatch_n)
 * Ghidra: void FUN_000fcc6c(void)
 * Capability-operation dispatcher (frame-lock + vtable check variant).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfce38) on chain mismatch. */
void cap_op_dispatch_n(void)
{
    unsigned char b;
    unsigned long len, probe;

    (void)cL4_current_thread;                              /* prologue */
    cL4_lock_state(0);
    if (/* op via vtable */ 1) {
        do {
            b = /* *(byte*)(base+idx) */ 0;
            if (b != 0) {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(unsigned long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume */ } while (/* more */ 0);
            if (len != b) { /* SoftwareBreakpoint(1, 0xfce38) */ }
        }
        /* emit reply with two 3-word groups */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fce3c @ 0xfce3c   (est. cap_op_dispatch_p)
 * Ghidra: void FUN_000fce3c(11 args)
 * Capability-operation dispatcher that builds a message chain and emits
 * a multi-part reply including a result and two 3-word argument groups.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfd194) on chain mismatch; the reply uses
 *   thunk_FUN_002acbb8 and FUN_00294bdc. */
void cap_op_dispatch_p(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4,
                       unsigned long p5, unsigned long p6, unsigned int p7, unsigned long p8,
                       unsigned long p9, unsigned char p10, unsigned long p11)
{
    unsigned char c;
    unsigned long len, probe;
    unsigned long node;

    cL4_lock_state(0);
    if (/* node == 0 && op != 0 */ 1) {
        cap_publish_setup(0);                        /* FUN_000fda88 */
        do {
            c = /* *(byte*)(base) */ 0;
            if (c != '\0') {
                probe = cL4_masked_ptr(0);
                if ((probe & 1) == 0) { /* grow */ }
            }
        } while (/* more */ 0);
        len = *(long *)(/* buf */ 0 + 0x10);
        if (len == 0) {
            cL4_ref_release(0);
            /* FUN_000776cc */;
        } else {
            do { /* consume 16-byte entries */ } while (len != /* n */ 0);
            if (len != /* consumed */ 0) { /* SoftwareBreakpoint(1, 0xfd194) */ }
        }
        /* emit reply */;
        cL4_push_word(0x2820, 0xe200000000000000);
        cL4_push_word(p3, p4);
        cL4_push_word(0, 0xe500000000000000);
        cL4_emit_3words(p5, p6, p7);
        cL4_emit_3words(p8, p9, p10);
    }
    /* FUN_000651bc */;
}

/* ------------------------------------------------------------------ *
 * cL4 syscall handlers with string-matched identities
 * ------------------------------------------------------------------ */

/* FUN_000fd198 @ 0xfd198   (est. sc_copy_cap)
 * Ghidra: undefined8 FUN_000fd198(4 args)
 * COPY capability syscall: resolves the current thread (FUN_00034f70),
 * runs the copy operation (FUN_00087704), and on success returns the
 * copy result; on failure logs the error and releases the source.
 * Confidence: low
 * Notes: FUN_004b23d8 logs the failed operation. */
unsigned long sc_copy_cap(unsigned long result, unsigned long src, unsigned long dst,
                          unsigned long flags)
{
    long t;

    t = /* FUN_00034f70() */ 0;
    if (t == 0) { /* FUN_001008cc alloc */ }
    /* FUN_00087704(t, src, dst, flags) */;
    if (/* err == 0 */ 1) {
        result = (*(unsigned long (*)(long))0)(t);
        cL4_ref_release(dst);
        cL4_ref_release(src);
    } else {
        /* FUN_004b23d8(t) */;
        cL4_enter_guarded(0);
        cL4_ref_release(dst);
        cL4_ref_release(src);
    }
    return result;
}

/* FUN_000fd268 / FUN_000fd6cc — wrappers to sc_op_generic5. */
void sc_op_wrap_a(void) { sc_op_generic5(0,0,0,0,(void (*)(long,unsigned long,unsigned long,unsigned long))0); }
void sc_op_wrap_b(void) { sc_op_generic5(0,0,0,0,(void (*)(long,unsigned long,unsigned long,unsigned long))0); }

/* FUN_000fd294 @ 0xfd294   (est. sc_copy_cap2)
 * Ghidra: void FUN_000fd294(3 args)
 * COPY capability syscall variant (FUN_000e8620).
 * Confidence: low */
void sc_copy_cap2(unsigned long a, unsigned long b, unsigned long c)
{
    long t;

    t = /* FUN_00034f70() */ 0;
    if (t == 0) { /* FUN_001008cc */ }
    /* FUN_000e8620(t, b, c) */;
    if (/* err == 0 */ 1) {
        (*(void (*)(long))0)(t);
    } else {
        /* FUN_004b23d8(t) */;
        cL4_enter_guarded(0);
    }
}

/* FUN_000fd334 @ 0xfd334   (est. sc_init_syscall)
 * Ghidra: void FUN_000fd334(4 args)
 * INIT syscall: resolves the thread and dispatches an init operation
 * referencing s_init___005c3f20 with a fixed argument set.
 * Confidence: low
 * Notes: string s_init___005c3f20 names the init entry. */
void sc_init_syscall(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    long t;

    t = /* FUN_00034f70() */ 0;
    if (t == 0) { /* FUN_001008cc */ }
    cap_op_dispatch_l(0xd000000000000019, 0x80000000005c65a0,
                      0x5c65e0 /* s__AppleInternal_Library_BuildRoot */, 0x115, 2,
                      0x5c3f20 /* s_init___ */, 6, 2, 0x4a, b, t, c, d);
    if (/* err == 0 */ 1) {
        (*(void (*)(long))0)(t);
    } else {
        /* FUN_004b23d8(t) */;
        cL4_enter_guarded(0);
    }
}

/* FUN_000fd41c @ 0xfd41c   (est. sc_init_deviceTree)
 * Ghidra: void FUN_000fd41c(4 args)
 * INIT-DEVICETREE syscall: resolves the thread, emits a message naming
 * the device-tree init (s_init_name_deviceTree___005c6830), and
 * dispatches an init operation with that name.
 * Confidence: low
 * Notes: strings s_init_name_deviceTree___005c6830 (name) and
 *   s__AppleInternal_Library_BuildRoot_005c6700. */
void sc_init_deviceTree(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    long t;

    t = /* FUN_00034f70() */ 0;
    if (t == 0) { /* FUN_001008cc */ }
    cL4_push_word(0x3a, 0);                          /* FUN_002a4ab4 */
    cL4_push_word(0xd000000000000035, 0x80000000005c2c20);
    /* FUN_00027724/FUN_003a25d4 message finalize */;
    cap_op_dispatch_l(0, 0xe000000000000000,
                      0x5c6700 /* s__AppleInternal_Library_BuildRoot */, 0x122, 2,
                      0x5c6830 /* s_init_name_deviceTree___ */, 0x16, 2, 0x7b, b, t, c, d);
    if (/* err == 0 */ 1) {
        cL4_publish(0xe000000000000000);
        (*(void (*)(long))0)(t);
    } else {
        cL4_publish(0xe000000000000000);
        /* FUN_004b23d8(t) */;
        cL4_enter_guarded(0);
    }
}

/* FUN_000fd5d8 @ 0xfd5d8   (est. sc_mint_endpoint)
 * Ghidra: undefined8 FUN_000fd5d8(2 args)
 * MINT-ENDPOINT syscall: resolves the thread, dispatches a mint
 * operation naming "mintEndpoint" (s_mintEndpoint___005c6886).
 * Confidence: low
 * Notes: string s_mintEndpoint___005c6886. */
unsigned long sc_mint_endpoint(unsigned long result, unsigned long arg)
{
    long t;

    t = /* FUN_00034f70() */ 0;
    if (t == 0) { /* FUN_001008cc */ }
    cL4_ref_retain(arg);
    cap_op_mint_dispatch(0xd000000000000032, 0x80000000005c6830,
                         0x5c0e90 /* s__AppleInternal_Library_BuildRoot */, 0x105, 2,
                         0x5c6886 /* s_mintEndpoint___ */, 0xe, 2, 0x140, t, arg);
    if (/* err == 0 */ 1) {
        result = (*(unsigned long (*)(long))0)(t);
        cL4_ref_release(arg);
    } else {
        /* FUN_004b23d8(t) */;
        cL4_enter_guarded(0);
        cL4_ref_release(arg);
    }
    return result;
}

/* FUN_000fd6f8 @ 0xfd6f8   (est. sc_op_generic5)
 * Ghidra: void FUN_000fd6f8(5 args)
 * Generic 5-argument cL4 syscall: resolves the thread, invokes the
 * supplied operation callback, and completes the operation.
 * Confidence: low
 * Notes: the callback is a function pointer (param_5). */
void sc_op_generic5(unsigned long a, unsigned long b, unsigned long c, unsigned long d,
                    void (*op)(long, unsigned long, unsigned long, unsigned long))
{
    long t;

    t = /* FUN_00034f70() */ 0;
    if (t == 0) { /* FUN_001008cc */ }
    op(t, b, c, d);
    if (/* err == 0 */ 1) {
        (*(void (*)(long))0)(t);
    } else {
        /* FUN_004b23d8(t) */;
        cL4_enter_guarded(0);
    }
}

/* FUN_000fd7b0 @ 0xfd7b0   (est. sc_op_generic1)
 * Ghidra: void FUN_000fd7b0(code *param_1)
 * Generic 1-argument cL4 syscall: resolves the thread, invokes the
 * callback, then calls the frame's +0x60 completion method.
 * Confidence: low */
void sc_op_generic1(void (*op)(long))
{
    long t;

    t = /* FUN_00034f70() */ 0;
    if (t == 0) { /* FUN_001008cc */ }
    op(t);
    if (/* err == 0 */ 1) {
        (*(void (**)(long))(cL4_current_thread + 0x60))(t);
    } else {
        /* FUN_004b23d8(t) */;
        cL4_enter_guarded(0);
    }
}

/* FUN_000fd854 @ 0xfd854   (est. sc_init_copy)
 * Ghidra: void FUN_000fd854(long param_1)
 * INIT-COPY syscall: resolves the thread, emits a message naming
 * "copy" (s_init_copy___005c616c), and dispatches the copy operation.
 * Confidence: low
 * Notes: strings s_init_copy___005c616c and "into " (0x206f746e6920). */
void sc_init_copy(long arg)
{
    long t;

    if (arg == 0) {
        /* emit "bad arg" message {0xd00000000000002b, ...} */;
    } else {
        t = /* FUN_00034f70() */ 0;
        if (t == 0) {
            /* FUN_00085374(s_init_copy___005c616c, 0xb, 2, 0x134) */;
        }
        cL4_push_word(0x24, 0);                      /* FUN_002a4ab4 */
        cL4_publish(0xe000000000000000);
        cL4_push_word(0x206f746e6920 /* "into " */, 0xe600000000000000);
        /* FUN_00100c20(0x136, 0xd00000000000001a) */;
        cap_op_dispatch_n();                         /* FUN_000fcc6c */
        if (/* err == 0 */ 1) {
            cL4_publish(0);
            (*(void (**)(long))(cL4_current_thread + 0x60))(t);
            return;
        }
        cL4_publish(0);
        /* FUN_004b23d8(t) */;
    }
    cL4_enter_guarded(0);
}

/* ------------------------------------------------------------------ *
 * Error-code builders and message helpers
 * ------------------------------------------------------------------ */

/* FUN_000fda38 @ 0xfda38   (est. msg_alloc_dispatch)
 * Ghidra: undefined8 FUN_000fda38(2 args)
 * Allocates a message object and runs FUN_000ff728 to populate it.
 * Confidence: low */
unsigned long msg_alloc_dispatch(unsigned long a, unsigned long b)
{
    unsigned long m;

    cL4_enter_guarded(0);                            /* FUN_00100d40 */
    m = cL4_alloc_obj(0, 0);                         /* FUN_0036a940 */
    /* FUN_000ff728(a, b) */;
    return m;
}

/* FUN_000fda88 @ 0xfda88   (est. cL4_error_code_words)
 * Ghidra: void FUN_000fda88(undefined8 *param_1, byte param_2)
 * Fills a 4-word record with the canonical L4 error-code words for the
 * given code (0..9). Codes map to the static error strings
 * "L4 ErrorCode Success/Preempted/Canceled/Truncated/CapInvalid/
 * SlotInvalid/MethodInvalid/ArgumentInvalid/OperationInvalid/
 * PermissionInvalid". Codes > 9 copy a default record.
 * Confidence: high (string-matched: s_L4_ErrorCode* at 0x4c4458..)
 * Notes: default path copies 4 words from _DAT_004c4598 region. */
void cL4_error_code_words(unsigned long *rec, unsigned char code)
{
    static const uintptr_t names[10] = {
        /* s_L4_ErrorCodeSuccess_004c4458        */ 0x4c4458,
        /* s_L4_ErrorCodePreempted_004c4478      */ 0x4c4478,
        /* s_L4_ErrorCodeCanceled_004c4498       */ 0x4c4498,
        /* s_L4_ErrorCodeTruncated_004c44b8      */ 0x4c44b8,
        /* s_L4_ErrorCodeCapInvalid_004c44d8     */ 0x4c44d8,
        /* s_L4_ErrorCodeSlotInvalid_004c44f8    */ 0x4c44f8,
        /* s_L4_ErrorCodeMethodInvalid_004c4518  */ 0x4c4518,
        /* s_L4_ErrorCodeArgumentInvalid_004c4538 */ 0x4c4538,
        /* s_L4_ErrorCodeOperationInvalid_004c4558 */ 0x4c4558,
        /* s_L4_ErrorCodePermissionInvalid_004c4578 */ 0x4c4578,
    };
    const unsigned long *src;

    if (code > 9) {
        /* copy 4 words from _DAT_004c4598 (default error record) */
        rec[0] = /* _DAT_004c4598 */ 0;
        rec[1] = /* uRam_004c45a0 */ 0;
        rec[2] = /* _DAT_004c45a8 */ 0;
        rec[3] = /* uRam_004c45b0 */ 0;
        cL4_lock_state((long)rec);
        return;
    }
    src = (const unsigned long *)names[code];
    rec[0] = src[0];
    rec[1] = src[1];
    rec[2] = src[2];
    rec[3] = src[3];
}

/* FUN_000fdb98 @ 0xfdb98   (est. cap_move_from_slot)
 * Ghidra: void FUN_000fdb98(void)
 * Moves a capability from a slot. Locks the frame's +0x50 field; if its
 * low bit is clear, emits "Failed to move capability from" and raises a
 * move error (tag 0x1e2); otherwise marks the slot moved (bit set).
 * Confidence: low
 * Notes: strings s_Failed_to_move_capability_from_005c62b0. */
void cap_move_from_slot(void)
{
    unsigned long f;

    cL4_enter_guarded(0);                            /* FUN_00100e40 */
    cL4_lock_state(cL4_current_thread + 0x50);       /* FUN_0009456c */
    cL4_lo_lock(0);                                  /* FUN_0036a1a0 */
    if ((*(unsigned char *)(cL4_current_thread + 0x50) & 1) == 0) {
        cL4_ref_retain(0);
        cL4_push_word(0x27, 0);                      /* FUN_002a4ab4 */
        cL4_publish(0xe000000000000000);
        cL4_log_string(0x5c62b0 /* s_Failed_to_move_capability_from_ */);
        /* FUN_00100c20(0x1e2, ...) */;
        cap_op_dispatch_a();                         /* FUN_000faac4 */
        cL4_publish(0);
        if (/* err == 0 */ 1)
            *(unsigned char *)(cL4_current_thread + 0x50) = 1;
    } else {
        /* emit "already moved" error {.., 0x80000000005c62c0} */;
        cL4_enter_guarded(0);
    }
}

/* FUN_000fdd10 @ 0xfdd10   (est. cap_err_Brokerde_wrap)
 * Ghidra: void FUN_000fdd10(void)
 * Thin wrapper for the Brokerde error.
 * Confidence: high */
void cap_err_Brokerde_wrap(void)
{
    unsigned long m[2];
    cap_err_Brokerde_a(m);
}

/* FUN_000fdd34 / FUN_000fdd38 — vtable dispatch on flag bit 0. */
void cap_vtable_dispatch_a(unsigned long p, unsigned int flag)
{
    if ((flag & 1) == 0)
        (*(void (**)(void))(*(unsigned long *)cL4_current_thread + 0x70))();
    else
        (*(void (**)(void))(*(unsigned long *)cL4_current_thread + 0x68))();
}
void cap_vtable_dispatch_b(unsigned long p, unsigned int flag)
{
    cap_vtable_dispatch_a(p, flag);
}

/* FUN_000fdd78 @ 0xfdd78   (est. msg_copy_from_frame)
 * Ghidra: void FUN_000fdd78(3 args)
 * Copies up to 0x100 words of message data from the current frame to a
 * destination, handling both direct and chained/borrowed source layouts.
 * On a large source it copies via the staging buffer; otherwise it
 * resolves a 0x110-word source region and copies it. Emits the final
 * message to the caller's buffer.
 * Confidence: low
 * Notes: FUN_001ee018 reads a message-length field; FUN_002cb61c copies
 *   a buffer range; FUN_00117cc4 copies words; FUN_00100030 is the
 *   fallback copy callback. */
void msg_copy_from_frame(unsigned long dst, unsigned long src, unsigned long mode)
{
    unsigned long st[2];
    long n;

    cL4_lock_state(0);                               /* FUN_0006b2ec */
    n = /* FUN_001ee018() */ 0;
    if (/* n > 0xff */ 0) {
        /* copy via staging buffer */
        goto done;
    }
    /* FUN_00114330(scratch, 0x110) */;
    if ((src >> 0x3c & 1) != 0) {
        /* FUN_002a4468(FUN_00100030, st, src, mode, 0x67b148) */;
    } else if ((mode >> 0x3d & 1) == 0) {
        /* resolve + copy contiguous range via FUN_002cb61c */;
    } else {
        /* resolve + copy chained range */;
    }
    /* copy resolved words into dst via FUN_00117cc4 */;
done:
    /* FUN_00117cc4(dst, &st, 0x101) */;
    /* FUN_000651bc */;
}

/* ------------------------------------------------------------------ *
 * Message emit / error-report wrappers (0xfdf68..0xff2e4)
 * ------------------------------------------------------------------ */

/* FUN_000fdf68 @ 0xfdf68   (est. msg_emit_multi)
 * Ghidra: void FUN_000fdf68(38 args)
 * Emits a large multi-word message from 18 {value, tag} argument pairs
 * plus a header byte, via FUN_001e9c00. The argument list is packed
 * into a 0x128-byte local frame and passed to the emitter.
 * Confidence: low
 * Notes: FUN_001e9c00 is the bulk message emitter; canary check on exit. */
void msg_emit_multi(unsigned long hdr, unsigned long a1, unsigned long t1,
                    unsigned long a2, unsigned long t2, /* ... 18 pairs ... */
                    unsigned long a18, unsigned long t18)
{
    unsigned char frame[0x128];
    (void)hdr; (void)a1; (void)t1; (void)a2; (void)t2; (void)a18; (void)t18;
    /* FUN_0006b2ec */;
    /* pack hdr + 18 {value,tag} pairs into frame */
    /* FUN_001e9c00(&frame) */;
    /* FUN_000651bc */;
}

/* FUN_000fe11c / FUN_000fe120 — emit a message tagged 0x660878. */
void msg_emit_tag_660878_a(unsigned long *p) { msg_emit_typed(*p, 0x660878, 0, 0); }
void msg_emit_tag_660878_b(unsigned long *p) { msg_emit_typed(*p, 0x660878, 0, 0); }

/* FUN_000fe14c @ 0xfe14c   (est. msg_emit_typed)
 * Ghidra: undefined8 FUN_000fe14c(4 args)
 * Emits a typed message for the value in *param_1, then runs the
 * dispatch FUN_000267d4.
 * Confidence: low
 * Notes: FUN_00100a48 is the emit prologue. */
unsigned long msg_emit_typed(unsigned long value, unsigned long tag,
                             unsigned long a, unsigned long b)
{
    cL4_enter_guarded(0);                            /* FUN_00100a48 */
    /* FUN_000267d4(&value) */;
    return 0;
}

/* FUN_000fe1c8 @ 0xfe1c8   (est. msg_emit_fixed)
 * Ghidra: undefined8 FUN_000fe1c8(undefined8 param_1)
 * Emits a fixed 5-tag message then dispatches.
 * Confidence: low */
unsigned long msg_emit_fixed(unsigned long v)
{
    /* FUN_000267d4(&v, 0x65a898, 0x662bc0, 0x65a7d0, 0x6629d8) */;
    return 0;
}

/* FUN_000fe294 @ 0xfe294   (est. msg_emit_4tag)
 * Ghidra: undefined8 FUN_000fe294(5 args)
 * Emits a 4-tag message then dispatches.
 * Confidence: low */
unsigned long msg_emit_4tag(unsigned long a, unsigned long b, unsigned long c,
                            unsigned long d, unsigned long e)
{
    /* FUN_00027754(e) */;
    cL4_enter_guarded(0);                            /* FUN_00100a48 */
    /* FUN_000267d4(a, .., c) */;
    return 0;
}

/* FUN_000fe310 / FUN_000fe314 — emit a message tagged 0x6611d8. */
void msg_emit_tag_6611d8_a(unsigned long *p) { msg_emit_typed(*p, 0x6611d8, 0, 0); }
void msg_emit_tag_6611d8_b(unsigned long *p) { msg_emit_typed(*p, 0x6611d8, 0, 0); }

/* FUN_000fe340 / FUN_000fe344 — dispatch cap_move vs cap_move_cached. */
void cap_move_dispatch(unsigned long p, unsigned int flag)
{
    if ((flag & 1) == 0)
        cap_move_from_slot();                        /* FUN_000fdb98 */
    else
        /* FUN_000ffba8 */;
}
void cap_move_dispatch2(unsigned long p, unsigned int flag) { cap_move_dispatch(p, flag); }

/* FUN_000fe364 @ 0xfe364   (est. msg_alloc_dispatch2)
 * Ghidra: undefined8 FUN_000fe364(2 args)
 * Allocates a message object and runs FUN_000ff914 to populate it.
 * Confidence: low */
unsigned long msg_alloc_dispatch2(unsigned long a, unsigned long b)
{
    unsigned long m;

    cL4_enter_guarded(0);                            /* FUN_00100d40 */
    m = cL4_alloc_obj(0, 0);                         /* FUN_0036a940 */
    /* FUN_000ff914(a, b) */;
    return m;
}

/* FUN_000fe3b4 @ 0xfe3b4   (est. sc_move_cap)
 * Ghidra: void FUN_000fe3b4(long param_1)
 * MOVE capability syscall: resolves the thread and dispatches a move
 * operation. If the argument is null it emits a "bad cap" error
 * {0xd00000000000002b, ..., 2}.
 * Confidence: low
 * Notes: strings s_init_move___005c635c and
 *   s_Attempted_to_move_capability_tha_005c6330. */
void sc_move_cap(long arg)
{
    long t;

    if (arg == 0) {
        /* emit {0xd00000000000002b, 0x80000000005c6310, 2} */;
    } else {
        t = /* FUN_00034f70() */ 0;
        if (t == 0) {
            /* FUN_00085374(s_init_move___005c635c, 0xb, 2, 0x146) */;
        }
        /* FUN_00100c20(s_Attempted_to_move_capability_tha_005c6330 + 0x20) */;
        /* FUN_00100b74(0xd000000000000019, err | 0x8000000000000000) */;
        cap_op_dispatch_n();                         /* FUN_000fcc6c */
        if (/* err == 0 */ 1) {
            (*(void (*)(long))0)(t);
            return;
        }
        /* FUN_004b23d8(t) */;
    }
    cL4_enter_guarded(0);
}

/* FUN_000fe514 — wrapper to Brokerde error b. */
void cap_err_Brokerde_wrap2(void) { unsigned long m[2]; cap_err_Brokerde_b(m); }

/* FUN_000fe538 — dispatch via FUN_000f6b74. */
void cap_op_dispatch_cb(void) { unsigned long m[2]; cap_op_dispatch((void (*)(void))0x000f6b74); }

/* FUN_000fe570 — wrapper to Brokerde error c. */
void cap_err_Brokerde_wrap3(void) { unsigned long m[2]; cap_err_Brokerde_c(m); }

/* FUN_000fe594 @ 0xfe594   (est. msg_emit2)
 * Ghidra: void FUN_000fe594(2 args)
 * Builds a message from two args and dispatches the emit callback.
 * Confidence: low
 * Notes: FUN_00377824/FUN_00377bec build the message words. */
void msg_emit2(unsigned long a, unsigned long b)
{
    unsigned long m1, m2;

    m1 = /* FUN_00377824(0, b, a, 0x607548, 0x607560) */ 0;
    m2 = /* FUN_00377bec(b, a, m1, 0x607548, 0x607558) */ 0;
    (*(void (*)(unsigned long, unsigned long))0x00100088)(m1, m2);
}

/* FUN_000fe618 @ 0xfe618   (est. msg_serialize)
 * Ghidra: void FUN_000fe618(4 args)
 * Serializes a capability range [param_1, param_2) into a message. If
 * the range length matches the node's +0x40 record it serializes the
 * elements (each +0x48 wide) via FUN_001a26e0 + FUN_000fe934; otherwise
 * it emits a "Serialization buffer for" error naming the format.
 * Confidence: low
 * Notes: strings s_Serialization_buffer_for_005c6390;
 *   SoftwareBreakpoint(1,0xfe840/0xfe844) on bad state. */
void msg_serialize(unsigned long start, unsigned long end, unsigned long p3, unsigned long p4)
{
    long len, elsize, node;

    len = 0;
    if (start != 0)
        len = end - start;
    node = /* FUN_00377824(0, p4, p3, ...) */ 0;
    if (len == *(long *)(*(long *)(node - 8) + 0x40)) {
        if (start == 0) {
            start = 0; len = 0;
        } else {
            /* validate start against node mask bits */;
            elsize = *(long *)(*(long *)(node - 8) + 0x48);
            if (elsize == 0) { /* SoftwareBreakpoint(1, 0xfe844) */ }
            len = 0;
            if (elsize != 0)
                len = (end - start) / elsize;
        }
        /* FUN_001a26e0(start, len, node) */;
        cap_emit_element(0, 0, 0, 0, 0, 0);          /* FUN_000fe934 */
    } else {
        /* emit "Serialization buffer for" error */;
        cL4_log_string(0x5c6390 /* s_Serialization_buffer_for_ */);
        /* build error {0xd000000000000019, ..} + format */;
        cL4_enter_guarded(0);
    }
}

/* FUN_000fe844 @ 0xfe844   (est. msg_emit_by_sign)
 * Ghidra: void FUN_000fe844(4 args)
 * Emits a message choosing the tag by the sign of param_2: negative
 * resolves via FUN_000bd174 with tag 0x6611d8, else via FUN_000a9468
 * with tag 0x660878. Dispatches via FUN_000267d4.
 * Confidence: low */
void msg_emit_by_sign(unsigned long v, unsigned long sign, unsigned long a, unsigned long b)
{
    unsigned long local, t;

    if ((long)sign < 0) {
        local = sign & 0x7fffffffffffffff;
        /* t = FUN_000bd174(0) */; t = 0;
        t = 0x6611d8;
    } else {
        local = sign;
        /* t = FUN_000a9468(0) */; t = 0;
        t = 0x660878;
    }
    /* FUN_000267d4(&local, a, t, b, tag) */;
}

/* FUN_000fe900 / FUN_000fe904 — emit-by-sign returning 1 on success. */
unsigned int msg_emit_by_sign_ok_a(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned int r;
    msg_emit_by_sign(a, *(unsigned long *)cL4_current_thread, b, c);
    r = 1;
    return r;
}
unsigned int msg_emit_by_sign_ok_b(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned int r;
    msg_emit_by_sign(a, *(unsigned long *)cL4_current_thread, b, c);
    r = 1;
    return r;
}

/* FUN_000fe934 @ 0xfe934   (est. cap_emit_element)
 * Ghidra: void FUN_000fe934(6 args)
 * Emits a capability element through the node's serialization callback
 * (FUN_00100434). On error records the failure into param_6.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfe9b0) when the element is null. */
void cap_emit_element(unsigned long el, unsigned long p2, unsigned long p3,
                      unsigned long p4, unsigned long cb, unsigned long *err)
{
    if (el != 0) {
        (*(void (*)(unsigned long, unsigned long, unsigned long))cb)(el, p4, cb);
        if (/* err */ 0)
            *err = /* unaff_x21 */ 0;
        return;
    }
    /* SoftwareBreakpoint(1, 0xfe9b0) */
}

/* FUN_000fe9b0 @ 0xfe9b0   (est. msg_resolve_emit)
 * Ghidra: void FUN_000fe9b0(3 args)
 * Resolves a message and emits it via FUN_0004e774.
 * Confidence: low */
void msg_resolve_emit(unsigned long a, unsigned long b, unsigned long c)
{
    unsigned long st[3];
    cL4_lock_state(a);                               /* FUN_0006b2dc */
    st[0] = 0; st[1] = c; st[2] = 0;
    /* FUN_0004e774(st, ..) */;
    /* FUN_000651bc */;
}

/* FUN_000fe9fc @ 0xfe9fc   (est. cap_iterate_find)
 * Ghidra: void FUN_000fe9fc(4 args)
 * Iterates a capability collection (FUN_0004eb44 iterator) and applies
 * FUN_000fea84 to each non-null element until it matches; returns the
 * first matching element.
 * Confidence: low
 * Notes: iterator via FUN_0004ecf0/FUN_0004eb4c. */
void cap_iterate_find(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned char it[16];
    unsigned long el, found;

    cL4_lock_state(b);                               /* FUN_0006b2ec */
    it[0] = /* FUN_0004eb44() */ 0;
    found = 0;
    if ((/* FUN_0004ecf0(it) */ 0 & 1) == 0) {
        do {
            el = /* FUN_0004eb4c(it) */ 0;
            if (el != 0) {
                el = cap_iter_find_match(el, c, d);  /* FUN_000fea84 */
                if (el != 0) { found = el; break; }
            }
        } while (/* FUN_0004ecf0(it) */ 0 == 0);
    }
    /* FUN_000651bc(found) */;
}

/* FUN_000fea84 @ 0xfea84   (est. cap_iter_find_match)
 * Ghidra: undefined8 FUN_000fea84(3 args)
 * Returns param_1 if the element's type (FUN_0004e88c) matches the
 * expected type computed by FUN_00100088, else null.
 * Confidence: low */
unsigned long cap_iter_find_match(unsigned long el, unsigned long a, unsigned long b)
{
    int want, got;

    want = /* FUN_0004e88c() */ 0;
    got = (*(int (*)(unsigned long, unsigned long))0x00100088)(a, b);
    if (want != got)
        el = 0;
    return el;
}

/* FUN_000feae0 @ 0xfeae0   (thunk_FUN_0004e8b0) (est. tb_resource_rate)
 * Ghidra: ulong thunk_FUN_0004e8b0(ushort *param_1)
 * Computes a tbplaceholder resource rate: packs a 32-bit key from the
 * resource header, looks up the divisor in a 0x30-stride table at
 * 0x65bf70, and divides the 64-bit resource field by it. Keys >= 0x1d
 * panic with "unknown tbplaceholder resource type".
 * Confidence: low
 * Notes: strings s_unknown_tbplaceholder_resource_t_005bb75b; table base
 *   0x65bf70. */
unsigned long tb_resource_rate(unsigned short *hdr)
{
    unsigned long key, rate, divisor;

    key = (unsigned long)(unsigned char)hdr[1] << 0x10 |
          (unsigned long)*(unsigned char *)((long)hdr + 3) << 0x18 |
          (unsigned long)*hdr;
    if (key < 0x1d) {
        divisor = *(unsigned long *)(key * 0x30 + 0x65bf70);
        rate = 0;
        if (divisor != 0) {
            rate = ((unsigned long)(unsigned char)hdr[3] << 0x10 |
                    (unsigned long)*(unsigned char *)((long)hdr + 7) << 0x18 |
                    (unsigned long)hdr[2] |
                    (unsigned long)((unsigned int)(unsigned char)hdr[5] << 0x10 |
                                    (unsigned int)*(unsigned char *)((long)hdr + 0xb) << 0x18 |
                                    (unsigned int)hdr[4]) << 0x20) / divisor;
        }
        return rate;
    }
    /* FUN_0005b190(0, s_unknown_tbplaceholder_resource_t_005bb75b) — noreturn */
    return 0;
}

/* FUN_000feae4 @ 0xfeae4   (est. tb_resource_validate)
 * Ghidra: void FUN_000feae4(2 args)
 * Validates a tbplaceholder resource; panics (breakpoint) on failure.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfeb10) on validation failure. */
void tb_resource_validate(unsigned long a, unsigned long b)
{
    if (/* FUN_0004e7b8(b, a) */ 0 != 0)
        return;
    /* SoftwareBreakpoint(1, 0xfeb10) */
}

/* FUN_000feb10 @ 0xfeb10   (est. counter_increment)
 * Ghidra: long FUN_000feb10(long param_1)
 * Increments a counter, panicking on signed overflow.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfeb20) on overflow. */
long counter_increment(long c)
{
    if (/* !SCARRY8(c, 1) */ c != -1)
        return c + 1;
    /* SoftwareBreakpoint(1, 0xfeb20) */
    return 0;
}

/* FUN_000feb28 @ 0xfeb28   (est. tb_rate_store)
 * Ghidra: void FUN_000feb28(undefined8 *param_1)
 * Stores the tbplaceholder resource rate into *param_1.
 * Confidence: low */
void tb_rate_store(unsigned long *out)
{
    *out = tb_resource_rate(*(unsigned short **)cL4_current_thread);
}

/* FUN_000feb54 @ 0xfeb54   (est. tb_resource_alloc)
 * Ghidra: undefined1 [16] FUN_000feb54(long *param_1, undefined8 *param_2, long param_3)
 * Allocates a 0x30-byte tbplaceholder resource object (tag 0x6868),
 * initializes it from the current object + the frame (+0x10/+0x18
 * fields), and returns a {dtor, obj} pair with dtor FUN_000febd0.
 * Confidence: low */
void tb_resource_alloc(unsigned long *out, unsigned long *src, long frame)
{
    unsigned long m[2];
    unsigned long obj;

    obj = /* FUN_0036a908(0x30, 0x6868) */ 0;
    *out = obj;
    m[0] = /* FUN_000fec0c(obj, *src, *cL4_current_thread, *(frame+0x10),
                          *(frame+0x18)) */ 0;
    m[1] = obj;
    *(unsigned long *)(obj + 0x20) = m[1];
    *(long *)(obj + 0x28) = m[0];
    out[1] = obj + 0x20;
    out[0] = 0x000febd0;                             /* FUN_000febd0 */
}

/* FUN_000febd0 @ 0xfebd0   (est. tb_resource_dtor)
 * Ghidra: void FUN_000febd0(long *param_1)
 * Destroys a tbplaceholder resource: calls its +0x28 finalizer then
 * frees the object.
 * Confidence: low */
void tb_resource_dtor(unsigned long *self)
{
    unsigned long obj;

    obj = *self;
    (*(void (**)(unsigned long))(obj + 0x28))(obj);
    cL4_free((void *)obj, 0);
}

/* FUN_000fec0c @ 0xfec0c   (est. tb_resource_init)
 * Ghidra: undefined1 [16] FUN_000fec0c(3 args)
 * Validates and initializes a tbplaceholder resource; returns
 * {FUN_0001a1c8, validated handle}.
 * Confidence: low */
unsigned long tb_resource_init(unsigned long obj, unsigned long a, unsigned long b)
{
    unsigned long h;
    h = /* FUN_000feae4(a, b) */ 0;
    return h;
}

/* FUN_000fec8c / FUN_000fecb8 — increment a counter in place. */
void counter_inc_store_a(unsigned long *p, unsigned long *q) { *p = counter_increment(*q); }
void counter_inc_store_b(unsigned long *p) { *p = counter_increment(*p); }

/* FUN_000fed08 @ 0xfed08   (est. msg_emit_tag_6629e8)
 * Ghidra: void FUN_000fed08(undefined8 param_1)
 * Emits a message tagged 0x6629e8.
 * Confidence: low
 * Notes: FUN_001e088c is the emit. */
void msg_emit_tag_6629e8(unsigned long v)
{
    /* FUN_001e088c(v, 0x6629e8) */;
}

/* FUN_000fed50 @ 0xfed50   (est. tb_placeholder_flush)
 * Ghidra: void FUN_000fed50(void)
 * Flushes/commits the tbplaceholder resource state.
 * Confidence: low
 * Notes: thunk_FUN_00284424. */
void tb_placeholder_flush(void)
{
    /* thunk_FUN_00284424() */;
}

/* FUN_000fed94 @ 0xfed94   (est. msg_copy_range)
 * Ghidra: void FUN_000fed94(5 args)
 * Copies a message range [param_1, param_1+len) into param_4/param_5;
 * panics on negative length.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0xfedf4) on negative length. */
void msg_copy_range(unsigned long dst, unsigned long a, unsigned long b, unsigned long p4,
                    unsigned long p5)
{
    long n;

    n = /* FUN_001ee018(a, b) */ 0;
    if (n >= 0) {
        /* FUN_002cb61c(dst, dst + n, p4, p5) */;
        return;
    }
    /* SoftwareBreakpoint(1, 0xfedf4) */
}

/* FUN_000fee0c @ 0xfee0c   (est. msg_error_builder)
 * Ghidra: undefined1 [16] FUN_000fee0c(3 args)
 * Builds an L4 error message word-pair from a severity code: 1=missing
 * resource, 2=invalid argument, 3=serialization error, default=L4
 * Error. Returns {tag, value} with an English message prefix.
 * Confidence: medium
 * Notes: strings s_Missing_resource__005c6410,
 *   s_Invalid_argument__005c63f0, s_Serialization_error__005c63d0.
 *   Verified: switch/pair-build matches decompile exactly; the string fn
 *   FUN_00086840 is a no-op so out[1] for cases 1-3 is the (indeterminate)
 *   no-op return, rendered as 0. */
void msg_error_builder(unsigned long a, unsigned long b, unsigned char kind,
                       unsigned long out[2])
{
    switch (kind) {
    default:
        out[0] = 0x726f72724520344c;                 /* "L4 Error" */
        out[1] = 0xea0000000000203a;                 /* ": \n" */
        break;
    case 1:
        cL4_push_word(0x14, 0);
        cL4_log_string(0x5c6410 /* s_Missing_resource__ */);
        out[0] = 0xd000000000000012;
        out[1] = 0;
        break;
    case 2:
        cL4_push_word(0x14, 0);
        cL4_log_string(0x5c63f0 /* s_Invalid_argument__ */);
        out[0] = 0xd000000000000012;
        out[1] = 0;
        break;
    case 3:
        cL4_push_word(0x17, 0);
        cL4_log_string(0x5c63d0 /* s_Serialization_error__ */);
        out[0] = 0xd000000000000015;
        out[1] = 0;
        break;
    }
    cL4_push_word(a, b);
}

/* FUN_000fef30 @ 0xfef30   (est. cap_flag_get)
 * Ghidra: undefined1 FUN_000fef30(void)
 * Returns the current object's +0x18 flag byte.
 * Confidence: low */
unsigned char cap_flag_get(void)
{
    cL4_lock_state(cL4_current_thread + 0x18);       /* FUN_000867a8 */
    cL4_lo_lock(0);                                  /* FUN_0036a1a0 */
    return *(unsigned char *)(cL4_current_thread + 0x18);
}

/* FUN_000fef60 @ 0xfef60   (est. cap_flag_set)
 * Ghidra: void FUN_000fef60(undefined1 param_1)
 * Sets the current object's +0x18 flag byte.
 * Confidence: low */
void cap_flag_set(unsigned char v)
{
    cL4_lock_state(cL4_current_thread + 0x18);       /* FUN_0009456c */
    cL4_lo_lock(0);                                  /* FUN_0036a1a0 */
    *(unsigned char *)(cL4_current_thread + 0x18) = v;
}

/* FUN_000fef9c @ 0xfef9c   (est. cap_retain_set)
 * Ghidra: void FUN_000fef9c(undefined8 param_1)
 * Allocates and retains a capability object.
 * Confidence: low */
void cap_retain_set(unsigned long cap)
{
    cL4_alloc_obj(0, 0);                             /* FUN_0036a940 */
    /* FUN_000fefe8(cap) */ cap_retain_setup(cap);
}

/* FUN_000fefe8 @ 0xfefe8   (est. cap_retain_setup)
 * Ghidra: void FUN_000fefe8(long param_1)
 * Sets the current object's capability (+0x10) and clears its flag
 * (+0x18); emits a "null cap" error if the argument is null.
 * Confidence: low */
void cap_retain_setup(long cap)
{
    if (cap == 0) {
        /* emit {0xd00000000000002e, 0x80000000005c6410} */;
        cL4_enter_guarded(0);
        cL4_bad_state();
    } else {
        *(long *)(cL4_current_thread + 0x10) = cap;
        *(unsigned char *)(cL4_current_thread + 0x18) = 0;
    }
}

/* FUN_000ff06c @ 0xff06c   (est. cap_revoke_delete)
 * Ghidra: void FUN_000ff06c(void)
 * Revokes and then deletes the current object's capability. Reads the
 * +0x18 flag; if clear, runs the revoke operation (FUN_000fa718) with a
 * "Failed to revoke capability" error, then the delete operation with a
 * "Failed to delete capability" error. Releases the capability object
 * on completion.
 * Confidence: low
 * Notes: strings s_Failed_to_revoke_capability_005c5630 and
 *   s_Failed_to_delete_capability_005c5610; FUN_004b23d8 releases. */
void cap_revoke_delete(void)
{
    cL4_lock_state(cL4_current_thread + 0x18);       /* FUN_000867a8 */
    cL4_lo_lock(0);                                  /* FUN_0036a1a0 */
    if ((*(unsigned char *)(cL4_current_thread + 0x18) & 1) == 0) {
        cL4_ref_retain(0x5c5630 /* s_Failed_to_revoke_capability_ */);
        /* FUN_00100b14(0x16a) */;
        cap_delete_dispatch();                       /* FUN_000fa718 */
        cL4_ref_retain(0x5c5610 /* s_Failed_to_delete_capability_ */);
        /* FUN_00100b14(0x16b) */;
        cap_delete_dispatch();                       /* FUN_000fa718 */
    }
    /* FUN_004b23d8(*(frame+0x10)) */;
}

/* FUN_000ff154 / FUN_000ff158 — revoke+delete with completion. */
void cap_revoke_delete_done_a(void)
{
    cap_revoke_delete();
    cL4_done();                                      /* FUN_0036b6ac */
}
void cap_revoke_delete_done_b(void)
{
    cap_revoke_delete();
    cL4_done();                                      /* FUN_0036b6ac */
}

/* FUN_000ff17c @ 0xff17c   (est. cap_delete_cap)
 * Ghidra: void FUN_000ff17c(void)
 * DELETES a capability: checks the current object's +0x48 method
 * (returns non-zero if deletable). If deletable, emits "Failed to
 * delete capability" and runs the delete dispatcher (FUN_000fa8f0);
 * otherwise emits a "not deletable" error (word 0x80000000005c6470).
 * Confidence: low
 * Notes: string s_Failed_to_delete_capability (via 0x5c6470 ref);
 *   FUN_000027e8 is a capability-type probe. */
void cap_delete_cap(void)
{
    unsigned long v, tag;
    long meth;

    cL4_enter_guarded(0);                            /* FUN_00100e1c */
    /* FUN_000027e8() */;
    v = (*(unsigned long (**)(void))(/* obj */ cL4_current_thread + 0x48))();
    if ((v & 1) == 0) {
        cL4_ref_retain(0);
        cL4_push_word(0x22, 0);                      /* FUN_002a4ab4 */
        cL4_publish(0xe000000000000000);
        /* FUN_00100c20(0x177, ...) */;
        cap_op_dispatch_a();                         /* FUN_000fa8f0 */
        cL4_publish(0);
    } else {
        /* emit {.., 0x80000000005c6470} error */;
        cL4_enter_guarded(0);
    }
}

/* FUN_000ff2e4 @ 0xff2e4   (est. cap_move_cap)
 * Ghidra: void FUN_000ff2e4(void)
 * MOVES a capability: checks the current object's +0x48 method. If
 * deletable, emits "Failed to move capability from" and runs the move
 * dispatcher (FUN_000fa8f0), then invokes the +0x50 method to complete
 * the move; otherwise emits a "not movable" error.
 * Confidence: low
 * Notes: string s_Failed_to_move_capability_from_005c62b0. */
void cap_move_cap(void)
{
    unsigned long v;
    long meth;

    cL4_enter_guarded(0);                            /* FUN_00100e40 */
    /* FUN_000027e8() */;
    v = (*(unsigned long (**)(void))(/* obj */ cL4_current_thread + 0x48))();
    if ((v & 1) == 0) {
        cL4_ref_retain(0);
        cL4_push_word(0x27, 0);                      /* FUN_002a4ab4 */
        cL4_publish(0xe000000000000000);
        cL4_log_string(0x5c62b0 /* s_Failed_to_move_capability_from_ */);
        /* FUN_00100c20(0x181, ...) */;
        cap_op_dispatch_a();                         /* FUN_000fa8f0 */
        cL4_publish(0);
        if (/* err == 0 */ 1)
            (*(void (**)(int))(*(unsigned long *)cL4_current_thread + 0x50))(1);
    } else {
        /* emit {.., 0x80000000005c62c0} error */;
        cL4_enter_guarded(0);
    }
}
