/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1). Ground truth: Ghidra FUN_ names + addresses.
 * All names are estimates unless string/header matched.
 * Slice 24: 0x80000-0x100000 caps region (tail: InternalExclaveLauncher
 * component object-allocation / init / exception machinery).
 *
 * These 20 functions (0xff47c - 0xffff8) belong to a single self-contained
 * component whose debug banner string is "InternalExclaveLauncher_Component"
 * (0x5c6300). They implement the launcher's typed-object allocation methods
 * ("init(allocate:with:...)", "init(allocateUntypedSize:with:...)"), guarded
 * flag accessors, a lazily-created sub-object, and a pair of exception / error
 * path dispatchers. The object state lives at fixed offsets from the
 * component pointer carried in the preserved register x20 (reconstructed here
 * as `self`). */

#include <stdint.h>
#include <stddef.h>

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range workers that own them).
 * ------------------------------------------------------------------ */

/* FUN_000027e8 @ 0x27e8 — fetch the current thread / exception-frame pointer
 * (the cL4 current-thread global); sets up the exception context used by the
 * error-path builders below. */
extern unsigned long cL4_current_exception_frame(void);
/* FUN_0006e7c0 @ 0x6e7c0 — copy an IPC/argument register block `src` into
 * the 16-byte record at `dst` (message-register collection). */
extern void cL4_copy_ipc_regs(unsigned long src, void *dst);
/* FUN_00034f70 @ 0x34f70 — allocate a fresh launcher object from the cL4
 * allocator; returns a non-zero pointer on success, 0 on failure. */
extern unsigned long cL4_launcher_alloc(void);
/* FUN_00085374 @ 0x85374 — noreturn panic taking a format string, count,
 * and line/source constants ("init(allocate:with:...)" 0x5c64b0, line 0x1ac). */
extern void cL4_panic_init_alloc(unsigned long fmt, long a, long b, long c);
/* FUN_00157230 @ 0x157230 — map a launcher object-type id (param) to the
 * internal cL4 object kind byte; returns 0x14 (20) for the allocate:with:
 * path, the kind byte otherwise. */
extern unsigned int cL4_object_type_kind(unsigned long type);
/* FUN_000f6d58 @ 0xf6d58 — dereference a tagged/branch-capability pointer and
 * return the method/vtable entry (function pointer) for the allocate:with:
 * dispatch. */
extern unsigned long cL4_method_ptr_alloc(unsigned long tagged);
/* FUN_0006a4c0 @ 0x6a4c0 — write the IPC argument words into the exception/
 * message frame for the upcoming method call (mirror of FUN_0006e7c0). */
extern void cL4_setup_ipc_call(unsigned long frame, unsigned long w0);
/* FUN_000770b8 @ 0x770b8 — dereference a tagged/branch-capability pointer and
 * return the method/vtable entry for the allocateUntypedSize dispatch. */
extern unsigned long cL4_method_ptr_untyped(unsigned long tagged);
/* FUN_00026e8 @ 0x26e8 — finalize / commit the exception frame after a
 * launcher operation completes (return path). */
extern void cL4_commit_exception_frame(unsigned long frame);
/* FUN_000867a8 @ 0x867a8 — lock acquire for the launcher state word. */
extern void cL4_launcher_lock(unsigned long addr);
/* FUN_0036a1a0 @ 0x36a1a0 — lock release / completion for the launcher state
 * word; clears the lock slot when not in the fast path. */
extern void cL4_launcher_unlock(unsigned long a, void *b, unsigned long c, long d);
/* FUN_0009455c @ 0x9455c — lock acquire for the launcher sub-object word
 * (wraps the same completion primitive). */
extern void cL4_subobj_lock(unsigned long addr);
/* FUN_0009456c @ 0x9456c — lock acquire for the launcher flag word. */
extern void cL4_flag_lock(unsigned long addr);
/* FUN_004b23d8 @ 0x4b23d8 — free / destroy a launcher object allocated by
 * cL4_launcher_alloc. */
extern void cL4_launcher_free(unsigned long obj);
/* FUN_0036986c @ 0x36986c — completion / release barrier used on the launcher
 * error-return path. */
extern void cL4_launcher_rollback(void);
/* FUN_002a4ab4 @ 0x2a4ab4 — begin an error report with a (presumably log)
 * code. */
extern void cL4_error_report(unsigned long code);
/* FUN_003a25d4 @ 0x3a25d4 — emit an error message word / build the error
 * result {lo,hi} pair (seL4-style error packing). */
extern unsigned long cL4_error_pack(unsigned long value);
/* FUN_00086840 @ 0x86840 — log a format string ("Unknown ObjectType" 0x5c64d0). */
extern void cL4_logf(unsigned long fmt);
/* FUN_00027724 @ 0x27724 — look up / return the global object handle for a
 * kernel object by id (0x670738 = the exception/fatal path object). */
extern unsigned long cL4_object_lookup(unsigned long id);
/* FUN_001afa84 @ 0x1afa84 — noreturn fatal-error printer taking the "Fatal
 * error" banner (0x5accd0) and the component/source string
 * ("InternalExclaveLauncher_Component" 0x5c6300, line 0x1af). */
extern void cL4_fatal_error(unsigned long banner, long b, long c, unsigned long d,
                            unsigned long e, unsigned long src, long line,
                            long g, long h, long i);
/* thunk_FUN_002acbb8 @ 0x2acbb8 — print / flush a log line built by the
 * cL4_logf / message machinery. */
extern void cL4_log_flush(unsigned long a, unsigned long b);
/* FUN_00100aa0 @ 0x100aa0 — register/set the launcher error-path completion
 * hook. */
extern void cL4_set_error_hook(void);
/* FUN_00100e34 @ 0x100e34 — build and return a {lo,hi} error result for the
 * exception path. */
extern unsigned long cL4_exc_error_result(void);
/* FUN_00100f08 @ 0x100f08 — build and return a {lo,hi} success result for the
 * exception path. */
extern unsigned long cL4_exc_ok_result(void);
/* FUN_00100c04 @ 0x100c04 — enable the pre-emption / fault-trap mode used by
 * the error branch of FUN_000ff47c. */
extern void cL4_fault_trap_enable(void);
/* FUN_00100e1c @ 0x100e1c — enter the launcher exception context (setup). */
extern void cL4_exc_enter(void);
/* FUN_00100bf0 @ 0x100bf0 — set up the error path prior to reporting. */
extern void cL4_exc_error_setup(void);
/* FUN_001005f4 @ 0x1005f4 — prepare the exception message registers. */
extern void cL4_exc_prepare_mr(void);
/* FUN_00100b94 @ 0x100b94 — begin a fatal log record for the launcher. */
extern void cL4_exc_fatal_begin(void);
/* FUN_00100c38 @ 0x100c38 — advance / finalize a log record on the error path. */
extern void cL4_exc_fatal_step(void);
/* FUN_00100c84 @ 0x100c84 — finalize the error-path log record. */
extern void cL4_exc_fatal_end(void);
/* FUN_00100c20 @ 0x100c20 — allocate a 0x1d8-byte launcher sub-object with the
 * given tag; returns its pointer (or the current record). */
extern unsigned long cL4_subobj_alloc(unsigned long tag, long extra);
/* FUN_00100a34 @ 0x100a34 — bind the freshly allocated sub-object into the
 * launcher state. */
extern void cL4_subobj_bind(unsigned long sub, unsigned long reg);
/* FUN_000faac4 @ 0xfaac4 — finalize / publish the lazily-created sub-object. */
extern void cL4_subobj_publish(void);
/* FUN_001005b4 @ 0x1005b4 — teardown path for the already-initialized branch
 * of FUN_000ffba8. */
extern void cL4_subobj_teardown(void);
/* FUN_00100a14 @ 0x100a14 — helper writing the teardown state word. */
extern void cL4_subobj_teardown_state(void);
/* FUN_00055a90 @ 0x55a90 — validate a launcher object type id; returns 0 on
 * unknown/invalid type. */
extern unsigned long cL4_validate_object_type(unsigned long type);
/* FUN_001e9c00 @ 0x1e9c00 — lookup / normalize an object type name for the
 * exception path. */
extern unsigned long cL4_type_name_lookup(void);
/* FUN_0001e790 @ 0x1e790 — write a value into the exception message registers. */
extern void cL4_exc_mr_write(unsigned long value);
/* FUN_00100d88 @ 0x100d88 — finalize an exception-path log record. */
extern void cL4_exc_log_end(void);
/* FUN_00100c94 @ 0x100c94 — advance the exception-path log record. */
extern void cL4_exc_log_step(void);
/* FUN_00100e70 @ 0x100e70 — prepare the exception-path error reporting. */
extern void cL4_exc_err_prepare(void);
/* FUN_00100efc @ 0x100efc — emit the "type <value> ..." fragment of the
 * unknown-type message. */
extern void cL4_exc_type_frag(void);
/* FUN_00100ecc @ 0x100ecc — completion barrier for the launcher error path. */
extern void cL4_exc_err_barrier(void);
/* FUN_000dbd8c @ 0xdbd8c — return the current log/exception context pointer. */
extern unsigned long cL4_exc_context(void);
/* FUN_000fa374 @ 0xfa374 — register a callback function (an interrupt /
 * signal dispatch handler) into the launcher's dispatch table. */
extern void cL4_register_callback(unsigned long fn);
/* FUN_00151974 / FUN_00151a6c @ 0x151974, 0x151a6c — open/close the
 * BuildRoot log context ("/AppleInternal/Library/BuildRoot..." 0x5c61a0). */
extern void cL4_log_open(void);
extern void cL4_log_close(void);
/* FUN_001000c4 @ 0x1000c4 — retain / acquire a reference on the sub-object. */
extern void cL4_subobj_retain(unsigned long sub);
/* FUN_001000dc @ 0x1000dc — release a reference on the sub-object. */
extern void cL4_subobj_release(unsigned long sub);
/* FUN_00100b74 @ 0x100b74 — log a location/marker string with the BuildRoot
 * prefix (used on the lazy-init path). */
extern void cL4_log_marker(unsigned long marker, unsigned long a, unsigned long prefix);
/* FUN_000770e8 @ 0x770e8 — dereference a tagged/branch-capability pointer and
 * return the method entry for the sub-object init dispatch. */
extern unsigned long cL4_method_ptr_subobj(unsigned long tagged);
/* FUN_00100d40 @ 0x100d40 — finalize the launcher object after lazy init. */
extern void cL4_launcher_finalize(void);
/* FUN_0036b6ac @ 0x36b6ac — completion / release barrier for the finalize path. */
extern void cL4_launcher_done(void);
/* FUN_0036b270 @ 0x36b270 — spinlock acquire for the launcher init word. */
extern void cL4_init_lock(void);
/* FUN_00100e1c is shared with exc_enter; FUN_00100ecc already declared. */

/* Global state words referenced by the launcher (kept as externs so the
 * in-range bodies stay faithful; the owning workers reconstruct them). */
extern unsigned long UINT_006775b0;  /* 0x6775b0 — fatal-error message object */
extern unsigned long UINT_0007bf58;  /* 0x7bf58 — shared launcher lock object */

/* The launcher component pointer. In the Ghidra decompile this object pointer
 * is carried in the preserved register x20 (unaff_x20); every function here
 * operates on it. It is the "self" receiver of the InternalExclaveLauncher
 * component methods. */
extern unsigned long self;   /* unaff_x20 — component object base */

/* The status/error flag of the most recent launcher operation. In the Ghidra
 * decompile the low part of the method-call result status is held in the
 * preserved register x21 (unaff_x21); a non-zero value marks a failed call. */
extern unsigned long errno_flag;   /* unaff_x21 — last-operation error flag */

/* ------------------------------------------------------------------ *
 * InternalExclaveLauncher component object allocation / init / exception
 * machinery.  In every function `self` is the component pointer carried in
 * the preserved register x20 (shown as unaff_x20 in the Ghidra decompile).
 * ------------------------------------------------------------------ */

/* Forward declaration (FUN_000ffa4c) used by the two start entry points. */
void exclave_launcher_lazy_init(void);

/* FUN_000ff47c @ 0x000ff47c   (est. exclave_launcher_object_dispatch)
 * Ghidra: undefined1 [16] FUN_000ff47c(void)
 * Main exception-path dispatcher for the launcher. Enters the exception
 * context, then probes a per-object flag through the exception frame's vtable
 * (+0x48). Depending on the probe result it either (flag clear) runs the
 * trap-mode error path — building an error result via the ok/fatal machinery —
 * or (flag set) runs the fault-mode path, ending with a success result. Both
 * branches funnel through the same log flush and return a 16-byte {lo,hi}
 * result pair to the caller (the seL4-style exception return).
 * Confidence: medium
 * Notes: gh id artifacts FUN_000027e8, FUN_00100aa0, FUN_000dbd8c,
 *   FUN_00027724, thunk_FUN_002acbb8, FUN_003a25d4, FUN_00100e34/FUN_00100f08.
 *   Return value ZEXT816 to a 16-byte word pair. */
typedef struct cl4_result_16 {
    unsigned long lo;
    unsigned long hi;
} cl4_result_16_t;

cl4_result_16_t exclave_launcher_object_dispatch(void)
{
    unsigned long frame;
    unsigned long flag;
    cl4_result_16_t result;

    frame = cL4_current_exception_frame();

    /* Probe the exception-frame dispatch flag via its vtable (+0x48). */
    flag = (*(unsigned long (**)(void))(frame + 0x48))();

    if ((flag & 1) == 0) {
        /* Flag clear: ordinary error-reporting path. */
        cL4_set_error_hook();
        cL4_object_lookup(frame);
        {
            unsigned long ctx = cL4_exc_context();
            (*(void (**)(unsigned long, unsigned long))(ctx))(
                ctx, 0xeb00000000287974ull);
        }
        cL4_log_flush(0, 0);
        cL4_error_pack(0);
        result = (cl4_result_16_t){ .lo = 0, .hi = cL4_exc_error_result() };
    } else {
        /* Flag set: fault-trap path, reports and returns success. */
        cL4_fault_trap_enable();
        cL4_error_report(0x15);
        cL4_error_pack(result.lo);
        cL4_set_error_hook();
        cL4_object_lookup(frame);
        {
            unsigned long ctx = cL4_exc_context();
            (*(void (**)(unsigned long, unsigned long))(ctx))(
                ctx, 0xeb00000000287974ull);
        }
        cL4_log_flush(0, 0);
        cL4_error_pack(0);
        result.hi = cL4_exc_ok_result();
        result.lo = 0xe800000000000000ull;
    }

    cL4_log_flush(result.lo, result.hi);
    return result;
}

/* FUN_000ff580 @ 0x000ff580   (est. exclave_launcher_invoke_0x78)
 * Ghidra: void FUN_000ff580(void)
 * Invokes the launcher method located at vtable offset +0x78 on the object
 * pointed to by the component's first word. A thin virtual dispatch used as a
 * late-binding entry point into the launcher's method table.
 * Confidence: medium
 * Notes: reads *(self) (the vtable pointer), dispatches **(self)+0x78. */
void exclave_launcher_invoke_0x78(void)
{
    unsigned long *vtable;
    vtable = *(unsigned long **)self;
    (*(void (**)(void))((unsigned char *)vtable + 0x78))();
}

/* FUN_000ff5c8 @ 0x000ff5c8   (est. exclave_launcher_get_flag_0x50)
 * Ghidra: undefined1 FUN_000ff5c8(void)
 * Locked getter for the launcher state byte at self+0x50: acquires the state
 * lock, reads the byte, releases the lock, and returns it. Paired with the
 * setter FUN_000ff5f8.
 * Confidence: high
 * Notes: mirrors the unlock pattern FUN_000867a8 / FUN_0036a1a0. */
unsigned char exclave_launcher_get_flag_0x50(void)
{
    unsigned char v;
    cL4_launcher_lock(self + 0x50);
    v = *(unsigned char *)(self + 0x50);
    cL4_launcher_unlock(0, &v, 0, 0);
    return v;
}

/* FUN_000ff5f8 @ 0x000ff5f8   (est. exclave_launcher_set_flag_0x50)
 * Ghidra: void FUN_000ff5f8(undefined1 param_1)
 * Locked setter for the launcher state byte at self+0x50: acquires the state
 * lock, stores `value`, and releases the lock. Paired with the getter
 * FUN_000ff5c8.
 * Confidence: high
 * Notes: mirror of the getter using the FUN_0009456c lock primitive. */
void exclave_launcher_set_flag_0x50(unsigned char value)
{
    cL4_flag_lock(self + 0x50);
    *(unsigned char *)(self + 0x50) = value;
    cL4_launcher_unlock(0, &value, 0, 0);
}

/* FUN_000ff634 @ 0x000ff634   (est. exclave_launcher_lock_0x50)
 * Ghidra: undefined1 [16] FUN_000ff634(void)
 * Acquires the state lock on self+0x50 and returns a {lo,hi} pair where hi is
 * the lock word's address and lo points at the shared lock object DAT_0007bf58.
 * Used by callers that need to hold the state lock across a sequence.
 * Confidence: medium
 * Notes: returns { &DAT_0007bf58, self+0x50 }. */
cl4_result_16_t exclave_launcher_lock_0x50(void)
{
    cl4_result_16_t r;
    cL4_subobj_lock(self + 0x50);
    r.hi = self + 0x50;
    r.lo = (unsigned long)&UINT_0007bf58;  /* 0x7bf58 — shared lock object */
    return r;
}

/* FUN_000ff678 @ 0x000ff678   (est. exclave_launcher_get_flag_0x51)
 * Ghidra: undefined1 FUN_000ff678(void)
 * Locked getter for the launcher state byte at self+0x51 (the second state
 * flag). Same pattern as FUN_000ff5c8 but for offset +0x51.
 * Confidence: high
 * Notes: offset 0x51, FUN_000867a8 lock. */
unsigned char exclave_launcher_get_flag_0x51(void)
{
    unsigned char v;
    cL4_launcher_lock(self + 0x51);
    v = *(unsigned char *)(self + 0x51);
    cL4_launcher_unlock(0, &v, 0, 0);
    return v;
}

/* FUN_000ff6a8 @ 0x000ff6a8   (est. exclave_launcher_set_flag_0x51)
 * Ghidra: void FUN_000ff6a8(undefined1 param_1)
 * Locked setter for the launcher state byte at self+0x51. Paired with the
 * getter FUN_000ff678.
 * Confidence: high
 * Notes: offset 0x51, FUN_0009456c lock. */
void exclave_launcher_set_flag_0x51(unsigned char value)
{
    cL4_flag_lock(self + 0x51);
    *(unsigned char *)(self + 0x51) = value;
    cL4_launcher_unlock(0, &value, 0, 0);
}

/* FUN_000ff6e4 @ 0x000ff6e4   (est. exclave_launcher_lock_0x51)
 * Ghidra: undefined1 [16] FUN_000ff6e4(void)
 * Acquires the state lock on self+0x51 and returns a {lo,hi} pair (shared lock
 * object, lock-word address). Mirror of FUN_000ff634 for offset +0x51.
 * Confidence: medium
 * Notes: returns { &DAT_0007bf58, self+0x51 }. */
cl4_result_16_t exclave_launcher_lock_0x51(void)
{
    cl4_result_16_t r;
    cL4_subobj_lock(self + 0x51);
    r.hi = self + 0x51;
    r.lo = (unsigned long)&UINT_0007bf58;  /* 0x7bf58 — shared lock object */
    return r;
}

/* FUN_000ff728 @ 0x000ff728   (est. exclave_launcher_allocate_with)
 * Ghidra: void FUN_000ff728(undefined1 param_1, long param_2)
 * The "init(allocate:with:)" launcher method. Copies the IPC argument block
 * (param_2) into the local frame, records the requested object-type byte
 * (param_1) at self+0x38, allocates a fresh launcher object (panicking on
 * allocator failure), and maps the requested type through the object-type
 * kind table. For the expected kind (0x14 = allocate-with) it pulls the two
 * IPC argument words from param_2, builds the method call, dispatches through
 * the object's method table, and stores the returned handle at self+0x40 with
 * a zeroed status word at self+0x50. On a failure branch it frees the object
 * and rolls back. An unknown object type triggers the fatal "Unknown
 * ObjectType" path.
 * Confidence: medium
 * Notes: strings "init(allocate:with:...)" 0x5c64b0 (panic, line 0x1ac),
 *   "Unknown ObjectType" 0x5c64d0, "Fatal error" 0x5accd0,
 *   "InternalExclaveLauncher_Component" 0x5c6300 line 0x1af. Calls
 *   FUN_0006e7c0, FUN_00034f70, FUN_00085374, FUN_00157230, FUN_0006a4c0,
 *   FUN_000f6d58, FUN_004b23d8, FUN_0036986c, FUN_00100ecc, FUN_00026e8,
 *   FUN_002a4ab4, FUN_003a25d4, FUN_00086840, FUN_00027724, FUN_001afa84. */
void exclave_launcher_allocate_with(unsigned char obj_type, unsigned long args)
{
    unsigned long kind;
    unsigned long obj;
    unsigned long w0, w1;
    unsigned long (*method)(unsigned long, unsigned long, unsigned long, unsigned long);

    cL4_copy_ipc_regs(args, (void *)(self + 0x10));
    *(unsigned char *)(self + 0x38) = obj_type;

    obj = cL4_launcher_alloc();
    if (obj == 0) {
        cL4_panic_init_alloc(0x5c64b0, 0x14, 2, 0x1ac);
    }
    *(unsigned long *)(self + 0x48) = obj;

    kind = cL4_object_type_kind(obj_type);
    if ((kind & 0xff) == 0x14) {
        /* Expected allocate-with kind: dispatch through the object's method. */
        w0 = *(unsigned long *)(args + 0x18);
        w1 = *(unsigned long *)(args + 0x20);
        cL4_setup_ipc_call(args, w0);
        method = (unsigned long (*)(unsigned long, unsigned long,
                                    unsigned long, unsigned long))cL4_method_ptr_alloc(w1);
        {
            unsigned long ret = method(*(unsigned long *)(self + 0x48), kind, w0, w1);
            if (errno_flag == 0) {
                *(unsigned long *)(self + 0x40) = ret;
                *(unsigned short *)(self + 0x50) = 0;
            } else {
                cL4_launcher_free(*(unsigned long *)(self + 0x48));
                cL4_launcher_rollback();
                cL4_exc_err_barrier();
            }
        }
        cL4_commit_exception_frame(args);
        return;
    }

    /* Unknown object type: report and die. */
    cL4_error_report(0x15);
    cL4_error_pack(0xe000000000000000ull);
    cL4_logf(0x5c64d0);  /* "Unknown ObjectType" */
    cL4_object_lookup(0x670738);
    cL4_log_flush((unsigned long)&UINT_006775b0, 0x670738);
    cL4_fatal_error(0x5accd0, 0xb, 2, 0xd000000000000013ull, 0,
                    0x5c6300, 0x2f, 2, 0x1af, 0);
}

/* FUN_000ff914 @ 0x000ff914   (est. exclave_launcher_allocate_untyped_with)
 * Ghidra: void FUN_000ff914(undefined8 param_1, long param_2)
 * The "init(allocateUntypedSize:with:)" launcher method. Like the allocate:with:
 * path but always records object-type 3 at self+0x38, allocates a fresh
 * launcher object (panicking on failure), reads the two IPC argument words
 * from param_2, and dispatches through the untyped method table (via
 * FUN_000770b8). On success it stores the returned handle at self+0x40 and
 * zeroes the status word at self+0x50; on failure it frees the object and
 * rolls back.
 * Confidence: medium
 * Notes: string "init(allocateUntypedSize:with:...)" 0x5c64f0 (panic,
 *   line 0x1c1). Calls FUN_0006e7c0, FUN_00034f70, FUN_00085374, FUN_0006a4c0,
 *   FUN_000770b8, FUN_004b23d8, FUN_0036986c, FUN_00100ecc, FUN_00026e8. */
void exclave_launcher_allocate_untyped_with(unsigned long w0, unsigned long args)
{
    unsigned long obj;
    unsigned long w1;
    unsigned long (*method)(unsigned long, unsigned long, unsigned long, unsigned long);

    cL4_copy_ipc_regs(args, (void *)(self + 0x10));
    *(unsigned char *)(self + 0x38) = 3;

    obj = cL4_launcher_alloc();
    if (obj == 0) {
        cL4_panic_init_alloc(0x5c64f0, 0x1f, 2, 0x1c1);
    }
    *(unsigned long *)(self + 0x48) = obj;

    w1 = *(unsigned long *)(args + 0x18);
    w0 = *(unsigned long *)(args + 0x20);
    cL4_setup_ipc_call(args, w1);
    method = (unsigned long (*)(unsigned long, unsigned long,
                                unsigned long, unsigned long))cL4_method_ptr_untyped(w0);
    {
        unsigned long ret = method(obj, w1, w0, 0);
        if (errno_flag == 0) {
            *(unsigned long *)(self + 0x40) = ret;
            *(unsigned short *)(self + 0x50) = 0;
        } else {
            cL4_launcher_free(*(unsigned long *)(self + 0x48));
            cL4_launcher_rollback();
            cL4_exc_err_barrier();
        }
    }
    cL4_commit_exception_frame(args);
}

/* FUN_000ffa28 @ 0x000ffa28   (est. exclave_launcher_start_0x51_commit)
 * Ghidra: void FUN_000ffa28(void)
 * Runs the guarded lazy-init (FUN_000ffa4c) then commits the exception frame
 * at self+0x10. The plain entry point for the launcher start sequence.
 * Confidence: high
 * Notes: FUN_000ffa4c + FUN_00026e8(self+0x10). */
void exclave_launcher_start_0x51_commit(void)
{
    exclave_launcher_lazy_init();
    cL4_commit_exception_frame(self + 0x10);
}

/* FUN_000ffa2c @ 0x000ffa2c   (est. exclave_launcher_start_0x51_commit_2)
 * Ghidra: void FUN_000ffa2c(void)
 * Byte-identical to FUN_000ffa28: guarded lazy-init followed by the exception
 * frame commit. A second symbol at the same body (duplicate entry point).
 * Confidence: high
 * Notes: aliases FUN_000ffa28; both call FUN_000ffa4c + FUN_00026e8. */
void exclave_launcher_start_0x51_commit_2(void)
{
    exclave_launcher_lazy_init();
    cL4_commit_exception_frame(self + 0x10);
}

/* FUN_000ffa4c @ 0x000ffa4c   (est. exclave_launcher_lazy_init)
 * Ghidra: void FUN_000ffa4c(void)
 * Guarded one-time lazy initialization of a launcher sub-object. Takes the
 * flag at self+0x51 (once-guard): if its low bit is clear, sets it and checks
 * the other state byte at self+0x50. If that is also clear it retains the
 * object at self+0x48, opens the BuildRoot log context, logs two location
 * markers, builds an IPC call from self+0x28/0x30, and dispatches through the
 * sub-object init method table (FUN_000770e8). The sub-object is then
 * released on every path.
 * Confidence: medium
 * Notes: strings "/AppleInternal/Library/BuildRoot..." 0x5c61a0, markers at
 *   LAB_000f614c / LAB_000f6164. Calls FUN_0009456c, FUN_0036a1a0,
 *   FUN_000867a8, FUN_001000c4, FUN_00151974, FUN_00100b74, FUN_00151a6c,
 *   FUN_001000dc, FUN_0006a4c0, FUN_000770e8, FUN_004b23d8. */
void exclave_launcher_lazy_init(void)
{
    unsigned char flag_0x51;
    unsigned char flag_0x50;
    unsigned long sub;
    unsigned long w0, w1;
    void (*method)(unsigned long, unsigned long, unsigned long);

    cL4_flag_lock(self + 0x51);
    flag_0x51 = *(unsigned char *)(self + 0x51);
    cL4_launcher_unlock(0, &flag_0x51, 0, 0);

    if ((flag_0x51 & 1) == 0) {
        *(unsigned char *)(self + 0x51) = 1;
        cL4_launcher_lock(self + 0x50);
        flag_0x50 = *(unsigned char *)(self + 0x50);
        cL4_launcher_unlock(0, &flag_0x50, 0, 0);

        if ((flag_0x50 & 1) == 0) {
            sub = *(unsigned long *)(self + 0x48);
            cL4_subobj_retain(sub);
            cL4_log_open();
            cL4_log_marker(0x000f614c, 0, 0x5c61a0);
            cL4_log_close();
            cL4_subobj_release(sub);
            cL4_log_open();
            cL4_log_marker(0x000f6164, 0, 0x5c61a0);
            cL4_log_close();

            w0 = *(unsigned long *)(self + 0x28);
            w1 = *(unsigned long *)(self + 0x30);
            cL4_setup_ipc_call(self + 0x10, w0);
            method = (void (*)(unsigned long, unsigned long, unsigned long))
                     cL4_method_ptr_subobj(w1);
            method(sub, w0, w1);
        }
        cL4_launcher_free(*(unsigned long *)(self + 0x48));
    }
}

/* FUN_000ffb80 @ 0x000ffb80   (est. exclave_launcher_start_finalize)
 * Ghidra: void FUN_000ffb80(void)
 * Full launcher start: guarded lazy-init, exception-frame commit, then the
 * launcher object finalize and done barrier. One of two identical entry
 * points (see FUN_000ffb84).
 * Confidence: high
 * Notes: FUN_000ffa4c + FUN_00026e8 + FUN_00100d40 + FUN_0036b6ac. */
void exclave_launcher_start_finalize(void)
{
    exclave_launcher_lazy_init();
    cL4_commit_exception_frame(self + 0x10);
    cL4_launcher_finalize();
    cL4_launcher_done();
}

/* FUN_000ffb84 @ 0x000ffb84   (est. exclave_launcher_start_finalize_2)
 * Ghidra: void FUN_000ffb84(void)
 * Byte-identical to FUN_000ffb80 (duplicate symbol on the same body).
 * Confidence: high
 * Notes: alias of FUN_000ffb80. */
void exclave_launcher_start_finalize_2(void)
{
    exclave_launcher_lazy_init();
    cL4_commit_exception_frame(self + 0x10);
    cL4_launcher_finalize();
    cL4_launcher_done();
}

/* FUN_000ffba8 @ 0x000ffba8   (est. exclave_launcher_init_or_teardown)
 * Ghidra: void FUN_000ffba8(void)
 * Two-way launcher init/teardown. Enters the exception context and reads the
 * state byte at self+0x50 under the state lock. If it is clear, runs the
 * first-time setup path: spins on the init lock, reports, builds an error
 * record, allocates a 0x1d8-byte sub-object and binds it, then publishes it.
 * If it is already set, runs the teardown path: tears down the sub-object
 * and writes a distinctive sentinel into two consecutive words
 * (x24+4 = 0xffffffff80065c70... from -0x7fffffffffa39b90).
 * Confidence: low
 * Notes: complex multi-path; many FUN_00100* log/exception helpers. Calls
 *   FUN_00100e1c, FUN_000867a8, FUN_0036a1a0, FUN_0036b270, FUN_002a4ab4,
 *   FUN_003a25d4, FUN_00100bf0, FUN_001005f4, FUN_00027724, FUN_00100b94,
 *   FUN_00100c38, FUN_00100c84, FUN_00100c20, FUN_00100a34, FUN_000faac4,
 *   FUN_001005b4, FUN_00100a14. */
void exclave_launcher_init_or_teardown(void)
{
    unsigned char flag;
    unsigned long sub;
    unsigned long x24_reg;   /* unaff_x24 — preserved register: teardown target */
    unsigned long x8_reg;    /* extraout_x8 — bind register */

    cL4_exc_enter();
    cL4_launcher_lock(self + 0x50);
    flag = *(unsigned char *)(self + 0x50);
    cL4_launcher_unlock(0, &flag, 0, 0);

    if ((flag & 1) == 0) {
        /* First-time init path. */
        cL4_init_lock();
        cL4_error_report(0x22);
        cL4_error_pack(0xe000000000000000ull);
        cL4_exc_error_setup();
        cL4_exc_prepare_mr();
        cL4_object_lookup(0);
        cL4_exc_fatal_begin();
        cL4_exc_fatal_step();
        {
            unsigned long ctx = cL4_exc_context();
            (*(void (**)(void))(ctx))();
        }
        cL4_log_flush(0, 0);
        cL4_error_pack(0);
        cL4_exc_fatal_end();
        cL4_exc_fatal_step();
        {
            unsigned long ctx = cL4_exc_context();
            (*(void (**)(void))(ctx))();
        }
        cL4_log_flush(0, 0);
        cL4_error_pack(0);

        sub = cL4_subobj_alloc(0x1d8, x24_reg);
        cL4_subobj_bind(sub, x8_reg);
        cL4_subobj_publish();
        cL4_error_pack(0);
    } else {
        /* Already-initialized teardown path. */
        cL4_subobj_teardown();
        {
            unsigned long *p = (unsigned long *)(x24_reg + 4);
            *p = (unsigned long)(x24_reg + 4);
            p[1] = 0x80000000005c6470ull;  /* -0x7fffffffffa39b90 */
        }
        cL4_subobj_teardown_state();
        cL4_launcher_rollback();
    }
}

/* FUN_000ffd0c @ 0x000ffd0c   (est. exclave_launcher_exception_validate)
 * Ghidra: undefined1 [16] FUN_000ffd0c(void)
 * Exception-path object-type validation. Validates the launcher type byte at
 * self+0x38 via FUN_00055a90. On an unknown type it reports the error and
 * builds the "(unknown type ..." message ("unknwn" bytes 0x6e776f6e6b6e7528 /
 * 0xee00206570797420), logs it, and returns an error result. On a known type
 * it normalizes the type name and proceeds. Then it reads the state byte at
 * self+0x50: a value of 1 selects one error branch (error code 0x51), any
 * other value selects the other (error code 0x4a); both build a
 * "type <value> ..." report and an exception result. Returns a 16-byte
 * {lo,hi} result (hi forced to 0xe000000000000000).
 * Confidence: low
 * Notes: string fragment bytes "unknwn(type <hex>" + ", type ". Calls
 *   FUN_00055a90, FUN_001e9c00, FUN_000867a8, FUN_0036a1a0, FUN_002a4ab4,
 *   FUN_00100e70, FUN_001005f4, FUN_00027724, FUN_000dbd8c, FUN_0001e790,
 *   FUN_00100d88, FUN_00100c94, FUN_00100efc, FUN_00100e34/FUN_00100f08. */
cl4_result_16_t exclave_launcher_exception_validate(void)
{
    unsigned long type_valid;
    unsigned long type_word;
    unsigned char flag;
    cl4_result_16_t result;

    type_valid = cL4_validate_object_type(*(unsigned char *)(self + 0x38));
    if (type_valid == 0) {
        /* Unknown type: report "(unknown type <hex>". */
        result.lo = 0;
        result.hi = 0xe000000000000000ull;
        cL4_error_report(0x11);
        cL4_error_pack(result.hi);
        {
            /* "(unknown type " fragment — bytes packed in two words. */
            unsigned long *dst = &result.lo;
            dst[0] = 0x6e776f6e6b6e7528ull;   /* "(unknwon" */
            dst[1] = 0xee00206570797420ull;   /* " type \0" */
        }
        cL4_object_lookup(0x670738);
        cL4_log_flush((unsigned long)&UINT_006775b0, 0x670738);
        cL4_error_pack(0);
        cL4_exc_error_result();
        cL4_log_flush(0, 0);
        type_word = result.lo;
    } else {
        type_word = cL4_type_name_lookup();
    }

    cL4_launcher_lock(self + 0x50);
    flag = *(unsigned char *)(self + 0x50);
    cL4_launcher_unlock(0, &flag, 0, 0);

    if (flag == '\x01') {
        cL4_error_report(0x51);
        cL4_exc_err_prepare();
        cL4_exc_prepare_mr();
        cL4_object_lookup(0);
        {
            unsigned long ctx = cL4_exc_context();
            (*(void (**)(unsigned long, unsigned long))(ctx))(
                ctx, 0xd000000000000016ull);
        }
        cL4_log_flush(0, 0);
        cL4_error_pack(0);
        cL4_log_flush(0x203a65707974202cull, 0xe800000000000000ull);
        cL4_exc_type_frag();
        cL4_log_flush(0, 0);
        cL4_error_pack(type_word);
        cL4_exc_log_step();
        cL4_exc_mr_write(0);
        cL4_exc_log_end();
        cL4_log_flush(0, 0);
        cL4_error_pack(0);
        result.lo = cL4_exc_ok_result();
        result.hi = 0xe800000000000000ull;
    } else {
        cL4_error_report(0x4a);
        cL4_exc_err_prepare();
        cL4_exc_prepare_mr();
        cL4_object_lookup(0);
        {
            unsigned long ctx = cL4_exc_context();
            (*(void (**)(unsigned long, unsigned long))(ctx))(
                ctx, 0xd000000000000016ull);
        }
        cL4_log_flush(0, 0);
        cL4_error_pack(0);
        cL4_log_flush(0x203a65707974202cull, 0xe800000000000000ull);
        cL4_exc_type_frag();
        cL4_log_flush(0, 0);
        cL4_error_pack(type_word);
        cL4_exc_log_step();
        cL4_exc_mr_write(0);
        cL4_exc_log_end();
        cL4_log_flush(0, 0);
        cL4_error_pack(0);
        result = (cl4_result_16_t){ .lo = 0, .hi = cL4_exc_error_result() };
    }

    cL4_log_flush(result.lo, result.hi);
    return result;
}

/* FUN_000fff9c @ 0x000fff9c   (est. exclave_launcher_exception_validate_wrap)
 * Ghidra: void FUN_000fff9c(void)
 * Thin wrapper around exclave_launcher_exception_validate; discards the
 * returned 16-byte result.
 * Confidence: high
 * Notes: calls FUN_000ffd0c, ignores its return. */
void exclave_launcher_exception_validate_wrap(void)
{
    exclave_launcher_exception_validate();
}

/* FUN_000fffc0 @ 0x000fffc0   (est. exclave_launcher_register_signal_handler)
 * Ghidra: void FUN_000fffc0(void)
 * Registers the launcher signal/interrupt dispatch callback FUN_00101038 into
 * the launcher's callback table.
 * Confidence: high
 * Notes: FUN_000fa374(FUN_00101038). */
void exclave_launcher_register_signal_handler(void)
{
    cL4_register_callback(0x101038);  /* FUN_00101038 — out of slice */
}

/* FUN_000ffff8 @ 0x000ffff8   (est. exclave_launcher_register_signal_handler_2)
 * Ghidra: void FUN_000ffff8(void)
 * Registers the launcher dispatch callback FUN_00103600 into the launcher's
 * callback table (a second, distinct handler).
 * Confidence: high
 * Notes: FUN_000fa374(FUN_00103600). */
void exclave_launcher_register_signal_handler_2(void)
{
    cL4_register_callback(0x103600);  /* FUN_00103600 — out of slice */
}
