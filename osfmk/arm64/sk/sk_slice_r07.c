/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * This region (0x3d2f10-0x3d952c) is the Swift standard-library + concurrency
 * runtime embedded in the kernel: Unicode scalar property tables, once
 * (pthread_once-style) primitives, and the async task / executor machinery.
 * All names are estimates unless string-matched. */

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/* cL4 returns many values as a 16-byte pair (two 64-bit words in x0/x1).
 * Model it as a struct so callers can carry both halves. */
typedef struct { unsigned long lo, hi; } cL4_w16_t;
/* ------------------------------------------------------------------ *
 * Binary globals referenced by these bodies (declared extern; they live in
 * the kernel image at the given addresses). Scalar words for the runtime
 * once/executor state; byte arrays for the read-only Unicode property tables.
 * ------------------------------------------------------------------ */
extern volatile unsigned long _DAT_006adec5;
extern volatile unsigned long _DAT_006adee0;
extern volatile unsigned long _DAT_006adf10;
extern volatile unsigned long _DAT_006adf18;
extern volatile unsigned long _DAT_006adf20;
extern volatile unsigned long _DAT_006adf50;
extern volatile unsigned long _DAT_006adf58;
extern volatile unsigned long _DAT_006adf60;
extern volatile unsigned long _DAT_006adf68;
extern volatile unsigned long _DAT_006c0b20;
extern volatile unsigned long _DAT_006c0b30;
extern volatile unsigned long _DAT_006c0b40;
extern volatile unsigned long _DAT_006c0b50;

extern unsigned long (*DAT_00658c80)(unsigned long, ...);

extern unsigned char DAT_003697c0[1];
extern unsigned char DAT_00405fa4[1];
extern unsigned char DAT_00405fdc[1];
extern unsigned char DAT_004f2a70[1];
extern unsigned char DAT_004f2f18[1];
extern unsigned char DAT_004f3938[1];
extern unsigned char DAT_004f3c88[1];
extern unsigned char DAT_004f3d60[1];
extern unsigned char DAT_004f4b10[1];
extern unsigned char DAT_004f4e7a[1];
extern unsigned char DAT_004f5ab0[1];
extern unsigned char DAT_004f80d2[1];
extern unsigned char DAT_004f80ec[1];
extern unsigned char DAT_004fa170[1];
extern unsigned char DAT_004fb4f8[1];
extern unsigned char DAT_004fb4fc[1];
extern unsigned char DAT_00500450[1];
extern unsigned char DAT_00500a58[1];
extern unsigned char DAT_00500e70[1];
extern unsigned char DAT_00500e86[1];
extern unsigned char DAT_00501670[1];
extern unsigned char DAT_00501af0[1];
extern unsigned char DAT_00501ed0[1];
extern unsigned char DAT_00501fc8[1];
extern unsigned char DAT_005024e8[1];
extern unsigned char DAT_00502630[1];
extern unsigned char DAT_005054e4[1];
extern unsigned char DAT_005057b0[1];
extern unsigned char DAT_00505918[1];
extern unsigned char DAT_00505970[1];
extern unsigned char DAT_00505a3e[1];
extern unsigned char DAT_00505e12[1];
extern unsigned char DAT_0050a214[1];
extern unsigned char DAT_00532a14[1];
extern unsigned char DAT_0056adec[1];
extern unsigned char DAT_005781a0[1];
extern unsigned char DAT_0058cb70[1];
extern unsigned char DAT_00590350[1];
extern unsigned char DAT_00590388[1];
extern unsigned char DAT_00598508[1];
extern unsigned char DAT_0059850c[1];
extern unsigned char DAT_00599fe0[1];
extern unsigned char DAT_0059a668[1];
extern unsigned char DAT_0059a808[1];
extern unsigned char DAT_0059af5a[1];
extern unsigned char DAT_0059af70[1];
extern unsigned char DAT_0059e0f8[1];
extern unsigned char DAT_0059e108[1];
extern unsigned char DAT_0059ff7c[1];
extern unsigned char DAT_0059ff8c[1];
extern unsigned char DAT_0059ff9c[1];
extern unsigned char DAT_0059ffac[1];
extern unsigned char DAT_00614564[1];
extern unsigned char DAT_00614a5c[1];
extern unsigned char DAT_006adec5[1];
extern unsigned char DAT_006adee0[1];

extern unsigned char LAB_003d4740[1];
extern unsigned char LAB_003d5c6c[1];
extern unsigned char LAB_003d7700[1];
extern unsigned char LAB_003d7ae4[1];
extern unsigned char LAB_003d7e74[1];
extern unsigned char LAB_003d830c[1];
extern unsigned char LAB_003d8e60[1];
extern unsigned char LAB_00614a7c[1];

extern unsigned char u_hF____0059e0f8[1];


/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * ------------------------------------------------------------------ */

/* FUN_0038df24 @ 0x38df24 — build a formatted string into *out using the
 * format string in x1 (Swift String(format:) helper). */
extern void cL4_str_format(unsigned long *out, const char *fmt, ...);
/* FUN_004b9d68 @ 0x4b9d68 — take a retained string/object reference. */
extern void cL4_ref_take(unsigned long obj);
/* FUN_00012568 @ 0x12568 — release a Swift String / print a string to the
 * kernel log (the thunk pair). Used after formatting fatal messages. */
extern void cL4_thunk_print(unsigned long str);
/* FUN_003d2e80 @ 0x3d2e80 — continuation used by the generic print path. */
extern void cL4_print_dispatch(unsigned long a, unsigned long b,
                               unsigned long c, unsigned long d);
/* FUN_00054414 @ 0x54414 — zero-init a buffer of length in x1 (memset 0). */
extern void cL4_thunk_zero(unsigned long *buf, unsigned long len);
/* FUN_00054464 @ 0x54464 — store an immediate 64-bit value (global store). */
extern void cL4_thunk_store64(unsigned long value);
/* FUN_0005453c @ 0x5453c — store an immediate 64-bit value (variant thunk). */
extern void cL4_thunk_store64_b(unsigned long value);
/* FUN_0006037c @ 0x6037c — return a global word pointer. */
extern unsigned long *cL4_thunk_global(void);
/* FUN_0011ae84 @ 0x11ae84 — string parse helper returning a uint status. */
extern unsigned int cL4_str_parse_uint(unsigned long str, unsigned long *out);
/* FUN_00115080 @ 0x115080 — string parse helper returning a value. */
extern unsigned long cL4_str_parse(unsigned long str);
/* FUN_001180e0 @ 0x1180e0 — cnd_broadcast(&_DAT_006c0b40); 0 on success. */
extern int cL4_cnd_broadcast(unsigned long cnd);
/* FUN_0011812c @ 0x11812c — cnd_wait(&_DAT_006c0b40, &_DAT_006c0b30); 0 on success. */
extern int cL4_cnd_wait(unsigned long cnd, unsigned long mtx);
/* FUN_00118164 @ 0x118164 — mtx_lock(&_DAT_006c0b30); 0 on success. */
extern int cL4_mtx_lock(unsigned long mtx);
/* FUN_00118194 @ 0x118194 — mtx_unlock(&_DAT_006c0b30); 0 on success. */
extern int cL4_mtx_unlock(unsigned long mtx);
/* FUN_00118148 @ 0x118148 — mtx_init(&_DAT_006c0b30, type); 0 on success. */
extern int cL4_mtx_init(unsigned long mtx, int type);
/* FUN_001180fc @ 0x1180fc — cnd_init(&_DAT_006c0b40); 0 on success. */
extern int cL4_cnd_init(unsigned long cnd);
/* FUN_00060524 @ 0x60524 — return the current thread/task pointer. */
extern unsigned long cL4_current_thread(void);
/* FUN_000539c0 @ 0x539c0 — return nonzero if the two values are equal. */
extern int cL4_eq(unsigned long a, unsigned long b);
/* FUN_003a2578 @ 0x3a2578 — [[noreturn]] kernel fatal error with a string. */
extern void cL4_fatal(const char *msg);
/* FUN_001afa84 @ 0x1afa84 — [[noreturn]] Swift runtime fatal error with
 * source location (file/line/column) metadata. */
extern void cL4_runtime_fatal(unsigned long a, int b, int c, unsigned long d,
                              unsigned long e, const char *file, int line,
                              int col, ...);
/* FUN_0035ac70 @ 0x35ac70 — allocate/build a Swift String from a C literal. */
extern unsigned long cL4_str_from_cstr(const char *s);
/* FUN_003593c0 @ 0x3593c0 — return a static fatal-error message handle. */
extern unsigned long cL4_static_str(unsigned long a);
/* FUN_00350b54 @ 0x350b54 — allocate a fresh task/job record. */
extern unsigned long cL4_task_alloc(void);
/* FUN_0036a940 @ 0x36a940 — return the current executor/job storage. */
extern unsigned long cL4_executor_storage(void);
/* FUN_0036b270 @ 0x36b270 — retain an object/run-once barrier. */
extern void cL4_retain(unsigned long obj);
/* FUN_0036b118 @ 0x36b118 — release an object/run-once barrier. */
extern void cL4_release(unsigned long obj);
/* FUN_000f5e5c @ 0xf5e5c — destructor hook for a box/context at +0x18. */
extern void cL4_box_destroy(unsigned long box);
/* FUN_00100c04 @ 0x100c04 — clear/abort a task context. */
extern void cL4_task_abort(void);
/* FUN_002a4ab4 @ 0x2a4ab4 — stack-marker/metadata push (value in x0). */
extern void cL4_stack_mark(unsigned long kind);
/* FUN_002acbb8 @ 0x2acbb8 — emit a metadata/trace record (kind, payload). */
extern void cL4_trace_emit(unsigned long kind, unsigned long payload);
/* FUN_00268540 @ 0x268540 — runtime crash/abort path returning a frame. */
extern unsigned long cL4_crash_frame(unsigned long a, unsigned long b);
/* FUN_0040a694 @ 0x40a694 — deallocate an object frame. */
extern void cL4_frame_dealloc(unsigned long frame);
/* FUN_003a25d4 @ 0x3a25d4 — release a Swift string/object. */
extern void cL4_obj_release(unsigned long obj);
/* FUN_00409eXX-family async helpers: task creation / job dispatch. */
extern void cL4_async_enter(void);
extern void cL4_async_leave(void);
/* FUN_00350d04 @ 0x350d04 — begin an async job on the current executor. */
extern void cL4_async_begin(void);
extern void cL4_async_cleanup(void);

/* Popcount of a 64-bit word — used by the Unicode bitmap index helpers. */
static inline int cl4_popcount64(unsigned long w)
{
    return __builtin_popcountll(w);
}


extern unsigned long FUN_0040ab60();
extern unsigned long FUN_00406420();
extern void FUN_003dd540();
/* External kernel/runtime helper FUN_* referenced by these bodies. Declared
 * as variadic word-returning externs (bodies reconstructed by their owning
 * range workers; kept in FUN_ form to preserve the address map). */
extern unsigned long FUN_000027e8();
extern unsigned long FUN_00027754();
extern unsigned long FUN_0007c028();
extern unsigned long FUN_0007c1a4();
extern unsigned long FUN_0007c1c4();
extern unsigned long FUN_000839d8();
extern unsigned long FUN_000839f8();
extern unsigned long FUN_0008409c();
extern unsigned long FUN_00084180();
extern unsigned long FUN_00084220();
extern unsigned long FUN_00084234();
extern unsigned long FUN_0008dae4();
extern unsigned long FUN_0008e1ec();
extern unsigned long FUN_0009461c();
extern unsigned long FUN_000aa4ec();
extern unsigned long FUN_000b430c();
extern unsigned long FUN_000b4390();
extern unsigned long FUN_000e15d8();
extern unsigned long FUN_000e72d4();
extern unsigned long FUN_00118abc();
extern unsigned long FUN_0011aa70();
extern unsigned long FUN_0011b39c();
extern unsigned long FUN_0014ae44();
extern unsigned long FUN_001afe4c();
extern unsigned long FUN_001b1780();
extern unsigned long FUN_00208418();
extern unsigned long FUN_00310d68();
extern unsigned long FUN_0031d5f0();
extern unsigned long FUN_003488bc();
extern unsigned long FUN_00349530();
extern unsigned long FUN_00349f3c();
extern unsigned long FUN_0034a2f8();
extern unsigned long FUN_0034a478();
extern unsigned long FUN_0034a74c();
extern unsigned long FUN_0034b05c();
extern unsigned long FUN_0034b7e4();
extern unsigned long FUN_0034bcf0();
extern unsigned long FUN_0034e4ec();
extern unsigned long FUN_003504a0();
extern unsigned long FUN_003504ac();
extern unsigned long FUN_003504c4();
extern unsigned long FUN_00350500();
extern unsigned long FUN_00350624();
extern unsigned long FUN_0035063c();
extern unsigned long FUN_00350744();
extern unsigned long FUN_00350750();
extern unsigned long FUN_00350798();
extern unsigned long FUN_003507e0();
extern unsigned long FUN_00350968();
extern unsigned long FUN_00350974();
extern unsigned long FUN_003509c8();
extern unsigned long FUN_003509ec();
extern unsigned long FUN_00350b54();
extern unsigned long FUN_00350d04();
extern unsigned long FUN_00351384();
extern unsigned long FUN_003513b4();
extern unsigned long FUN_00351f10();
extern unsigned long FUN_00352018();
extern unsigned long FUN_00352700();
extern unsigned long FUN_00353080();
extern unsigned long FUN_00353c00();
extern unsigned long FUN_00353d70();
extern unsigned long FUN_00356b80();
extern unsigned long FUN_003593c0();
extern unsigned long FUN_0035a7e8();
extern unsigned long FUN_0035ac70();
extern unsigned long FUN_0036986c();
extern unsigned long FUN_0036b6ac();
extern unsigned long FUN_00377824();
extern unsigned long FUN_00377bec();
extern unsigned long FUN_00377dcc();
extern unsigned long FUN_0039a128();
extern unsigned long FUN_003e9df8();
extern unsigned long FUN_003eaf4c();
extern unsigned long FUN_003fcafc();
extern unsigned long FUN_003fcb2c();
extern unsigned long FUN_003fcb5c();
extern unsigned long FUN_003fcb8c();
extern unsigned long FUN_003fcc1c();
extern unsigned long FUN_003fcc4c();
extern unsigned long FUN_003fccc4();
extern unsigned long FUN_003fccd4();
extern unsigned long FUN_003fcd04();
extern unsigned long FUN_00406268();
extern unsigned long FUN_00406288();
extern unsigned long FUN_004062a8();
extern unsigned long FUN_004062e8();
extern unsigned long FUN_0040652c();
extern unsigned long FUN_0040654c();
extern unsigned long FUN_00406574();
extern unsigned long FUN_00406590();
extern unsigned long FUN_00406608();
extern unsigned long FUN_00406704();
extern unsigned long FUN_0040679c();
extern unsigned long FUN_0040683c();
extern unsigned long FUN_0040684c();
extern unsigned long FUN_0040686c();
extern unsigned long FUN_00406894();
extern unsigned long FUN_004068f4();
extern unsigned long FUN_0040697c();
extern unsigned long FUN_00406aa4();
extern unsigned long FUN_00406ab4();
extern unsigned long FUN_00406bb4();
extern unsigned long FUN_00406bc4();
extern unsigned long FUN_00406bd4();
extern unsigned long FUN_00406c3c();
extern unsigned long FUN_00406cc8();
extern unsigned long FUN_00406cf0();
extern unsigned long FUN_00406d70();
extern unsigned long FUN_00406da8();
extern unsigned long FUN_00406dd0();
extern unsigned long FUN_00406e8c();
extern unsigned long FUN_00406f18();
extern unsigned long FUN_00406f2c();
extern unsigned long FUN_00406f40();
extern unsigned long FUN_00406f50();
extern unsigned long FUN_00406fc0();
extern unsigned long FUN_00406fe0();
extern unsigned long FUN_00407000();
extern unsigned long FUN_00407018();
extern unsigned long FUN_004070cc();
extern unsigned long FUN_004070d8();
extern unsigned long FUN_00407100();
extern unsigned long FUN_0040711c();
extern unsigned long FUN_00407164();
extern unsigned long FUN_004071c0();
extern unsigned long FUN_00407214();
extern unsigned long FUN_00407248();
extern unsigned long FUN_004072a0();
extern unsigned long FUN_0040738c();
extern unsigned long FUN_00407398();
extern unsigned long FUN_004073cc();
extern unsigned long FUN_00407450();
extern unsigned long FUN_004074c4();
extern unsigned long FUN_00407588();
extern unsigned long FUN_00407594();
extern unsigned long FUN_004075c4();
extern unsigned long FUN_0040761c();
extern unsigned long FUN_00407670();
extern unsigned long FUN_00407700();
extern unsigned long FUN_00407740();
extern unsigned long FUN_004077a0();
extern unsigned long FUN_00407824();
extern unsigned long FUN_004078d4();
extern unsigned long FUN_004078e8();
extern unsigned long FUN_004078f4();
extern unsigned long FUN_0040790c();
extern unsigned long FUN_00407954();
extern unsigned long FUN_00407978();
extern unsigned long FUN_00407984();
extern unsigned long FUN_004079a8();
extern unsigned long FUN_004079b4();
extern unsigned long FUN_004079cc();
extern unsigned long FUN_00407a04();
extern unsigned long FUN_00407aa0();
extern unsigned long FUN_00407c5c();
extern unsigned long FUN_00407c78();
extern unsigned long FUN_00407c8c();
extern unsigned long FUN_00407ca0();
extern unsigned long FUN_00407cd4();
extern unsigned long FUN_00407db0();
extern unsigned long FUN_00407e10();
extern unsigned long FUN_00407e58();
extern unsigned long FUN_00407ea0();
extern unsigned long FUN_00407f48();
extern unsigned long FUN_00407f9c();
extern unsigned long FUN_00407fb4();
extern unsigned long FUN_00408044();
extern unsigned long FUN_00408058();
extern unsigned long FUN_004080cc();
extern unsigned long FUN_004081c0();
extern unsigned long FUN_004082a8();
extern unsigned long FUN_00408308();
extern unsigned long FUN_00408380();
extern unsigned long FUN_004083b4();
extern unsigned long FUN_0040841c();
extern unsigned long FUN_00408454();
extern unsigned long FUN_004084d4();
extern unsigned long FUN_00408574();
extern unsigned long FUN_00408588();
extern unsigned long FUN_0040859c();
extern unsigned long FUN_004088d8();
extern unsigned long FUN_00408db8();
extern unsigned long FUN_004094ec();
extern unsigned long FUN_0040a7f0();
extern unsigned long FUN_0040a860();
extern unsigned long FUN_0040ada4();
extern unsigned long FUN_0040bb18();
extern unsigned long FUN_0040bd24();

/* Helpers that return a 16-byte pair (two words in x0/x1) — override the
 * generic word-returning externs above. */
cL4_w16_t FUN_0036993c(unsigned long, unsigned long, unsigned long, unsigned long);
cL4_w16_t FUN_00406fd4(void);
cL4_w16_t FUN_0040700c(void);
cL4_w16_t FUN_00408bdc(unsigned long, unsigned long);
cL4_w16_t FUN_00351330(void);
cL4_w16_t FUN_00406fec(void);
cL4_w16_t FUN_0040678c(void);
cL4_w16_t FUN_00350518(void);

/* Forward declarations of same-file functions (referenced before
 * their definitions). Kept in Ghidra FUN_ form to preserve the address map.
 * Empty-arg decls so call sites with decompiler-dropped register args compile. */
void FUN_003d2f10();
void FUN_003d2f9c();
void FUN_003d2ffc();
void FUN_003d30b0();
long FUN_003d30c4();
long FUN_003d3130();
void FUN_003d319c();
void FUN_003d31d8();
void FUN_003d31e8();
unsigned long FUN_003d31f8();
unsigned long FUN_003d3200();
unsigned int FUN_003d326c();
long FUN_003d3398();
bool FUN_003d3470();
unsigned int FUN_003d34b8();
bool FUN_003d351c();
unsigned short FUN_003d3550();
unsigned int FUN_003d35b0();
int FUN_003d35f0();
unsigned long FUN_003d36b0();
unsigned int FUN_003d3740();
cL4_w16_t FUN_003d37a4();
unsigned long FUN_003d37f0();
unsigned int FUN_003d3838();
long FUN_003d3964();
unsigned short FUN_003d3ac0();
unsigned int FUN_003d3b30();
unsigned int FUN_003d3b98();
long FUN_003d3c1c();
void FUN_003d3c88();
unsigned char FUN_003d3d4c();
bool FUN_003d3dac();
void FUN_003d3dd8();
void FUN_003d3e94();
void FUN_003d3ed0();
void FUN_003d3f0c();
long FUN_003d3f78();
void FUN_003d3fcc();
void FUN_003d40bc();
void FUN_003d40c0();
unsigned long FUN_003d40e4();
void FUN_003d412c();
void FUN_003d4278();
void FUN_003d4368();
void FUN_003d4428();
void FUN_003d44a8();
void FUN_003d4518();
void FUN_003d45b0();
long FUN_003d4658();
void FUN_003d4688();
void FUN_003d47f8();
void FUN_003d484c();
void FUN_003d48e8();
void FUN_003d4980();
void FUN_003d4a28();
void FUN_003d4d0c();
bool FUN_003d4d80();
void FUN_003d4dbc();
void FUN_003d4e84();
unsigned int FUN_003d4ebc();
void FUN_003d4f18();
void FUN_003d4f78();
void FUN_003d4fd8();
long FUN_003d5028();
void FUN_003d5058();
void FUN_003d50cc();
void FUN_003d5138();
void FUN_003d5194();
void FUN_003d51c4();
void FUN_003d520c();
unsigned int FUN_003d5284();
void FUN_003d52d0();
unsigned int FUN_003d5308();
void FUN_003d5338();
unsigned int FUN_003d5370();
void FUN_003d53bc();
void FUN_003d53ec();
void FUN_003d541c();
void FUN_003d5670();
void FUN_003d58a0();
void FUN_003d5a4c();
void FUN_003d5dc8();
void FUN_003d6034();
void FUN_003d62dc();
void FUN_003d6418();
void FUN_003d6470();
void FUN_003d64a0();
void FUN_003d6530();
void FUN_003d6724();
void FUN_003d69f8();
void FUN_003d6b14();
void FUN_003d6d50();
void FUN_003d71b8();
void FUN_003d72f0();
void FUN_003d7414();
void FUN_003d7440();
void FUN_003d7460();
void FUN_003d7494();
void FUN_003d74d0();
void FUN_003d7540();
void FUN_003d75f8();
void FUN_003d77bc();
void FUN_003d7978();
void FUN_003d7c18();
void FUN_003d7d60();
void FUN_003d7f60();
void FUN_003d816c();
void FUN_003d85b8();
void FUN_003d86f0();
void FUN_003d871c();
void FUN_003d873c();
void FUN_003d87ac();
void FUN_003d89a4();
void FUN_003d8b64();
void FUN_003d8cc0();
void FUN_003d8fbc();
void FUN_003d91ac();
void FUN_003d93f8();
void FUN_003d952c();

/* ------------------------------------------------------------------ *
 * 0x3d2f10 - 0x3d2ffc : Swift print / fatal-error wrappers and the
 * standard-library float-string parse helpers.
 * ------------------------------------------------------------------ */

/* FUN_003d2f10 @ 0x3d2f10   (est. cL4_swift_uint_conv2)
 * Ghidra: void FUN_003d2f10(undefined8, undefined8, undefined8, undefined8, undefined8)
 * Formats the message "%s, %s, %s" (three string arguments), takes a
 * reference, prints it via the thunk, then forwards to the generic print
 * dispatch. The extra argument (param_5) is the format-argument bundle.
 * Confidence: low
 * Notes: string ref s___,___,___@0x5db6b1; caller sk_region_sched names it
 *   "swift_uint_conv2" (a Swift UInt->String conversion entry). */
void FUN_003d2f10(unsigned long param_1, unsigned long param_2,
                  unsigned long param_3, unsigned long param_4,
                  unsigned long param_5)
{
    unsigned long local_48;
    cL4_str_format(&local_48, (const char *)0x5db6b1); /* "%s, %s, %s" */
    cL4_ref_take(param_5);
    cL4_thunk_print(local_48);
    cL4_print_dispatch(param_1, param_2, param_3, param_4);
}

/* FUN_003d2f9c @ 0x3d2f9c   (est. cL4_swift_unimplemented_fatal)
 * Ghidra: void FUN_003d2f9c(void)
 * Formats the string "%s: %s: Fatal error: Use of unimplemented initializer"
 * and raises it as a fatal error. Used when a Swift type's
 * init()/init(from:) is unimplemented.
 * Confidence: medium
 * Notes: string ref s__s__Fatal_error__Use_of_unimi@0x5db6bd. */
void FUN_003d2f9c(void)
{
    unsigned long local_28;
    cL4_str_format(&local_28,
                   (const char *)0x5db6bd); /* "%s: %s: Fatal error: Use of unimplemented..." */
    cL4_ref_take(*(unsigned int *)0);       /* in_stack_00000000 */
    cL4_thunk_print(local_28);
}

/* FUN_003d2ffc @ 0x3d2ffc   (est. cL4_once_guard_lazy)
 * Ghidra: void FUN_003d2ffc(void)  [globals overlap]
 * Lazy one-time global initialization guard. If the once-token at
 * 0x6adee0 is not already armed (>= 0), run the init closure. Then, based
 * on the flag byte at 0x6adec5, either clear the two global slots
 * (0x6adf10/0x6adf18) or leave them, and record the completed state in
 * 0x6adf20.
 * Confidence: low
 * Notes: _DAT_006adee0/_DAT_006adec5/_DAT_006adf10/_DAT_006adf18/
 *   _DAT_006adf20 are the Swift runtime global-init state. */
void FUN_003d2ffc(void)
{
    int done;
    if (-1 < (long)_DAT_006adee0) {
        FUN_003d3dd8((((unsigned char*)DAT_006adee0)), (void *)(((unsigned char*)DAT_003697c0)), 0);
    }
    done = (DAT_006adec5 != 1);
    if (done) {
        unsigned long local_20 = 0, uStack_18 = 0;
        cL4_thunk_zero(&uStack_18, 8);
        cL4_thunk_zero(&local_20, 8);
        _DAT_006adf10 = uStack_18;
        _DAT_006adf18 = local_20;
    } else {
        _DAT_006adf10 = 0;
        _DAT_006adf18 = 0;
        _DAT_006adf20 = 0;
    }
    _DAT_006adf20 = (_DAT_006adf20 & 0xffffffffffffff00) | (unsigned long)!done;
}

/* FUN_003d3130 @ 0x3d3130   (est. cL4_str_to_int_parse)
 * Ghidra: long FUN_003d3130(long, undefined4*)
 * Parse an integer from the string in param_1. If the string is a plain
 * number (FUN_003d3200 returns 0, i.e. not nan/inf), clear a scratch word
 * and parse normally, storing the status. Otherwise the value is computed
 * from the string length and a "nan"/"inf" sentinel is produced.
 * Confidence: low
 * Notes: FUN_003d3200 detects the literal tokens "nan"/"snan"/"inf". */
long FUN_003d3130(long param_1, unsigned int *param_2)
{
    int iVar1;
    long local_28;
    iVar1 = FUN_003d3200((unsigned char *)param_1);
    if (iVar1 == 0) {
        local_28 = 0;
        *cL4_thunk_global() = 0;
        *param_2 = cL4_str_parse_uint(param_1, &local_28);
    } else {
        *param_2 = 0x7fa00000;
        local_28 = cL4_str_parse(param_1);
        local_28 = param_1 + local_28;
    }
    return local_28;
}

/* FUN_003d31d8 @ 0x3d31d8   (est. cL4_swift_once_store_guard)
 * Ghidra: void FUN_003d31d8(void)
 * Store the canonical once-guard token value 0xb4000769f84206c9 into the
 * global slot handled by the thunk (a Swift lazy-global once marker).
 * Confidence: low
 * Notes: mirror of FUN_003d31e8 which stores the same constant. */
void FUN_003d31d8(void)
{
    cL4_thunk_store64(0xb4000769f84206c9);
}

/* FUN_003d31e8 @ 0x3d31e8   (est. cL4_swift_once_store_guard_b)
 * Ghidra: void FUN_003d31e8(void)
 * Same once-guard store as FUN_003d31d8 but through the alternative store
 * thunk (0x5453c); returns nothing.
 * Confidence: low */
void FUN_003d31e8(void)
{
    cL4_thunk_store64_b(0xb4000769f84206c9);
}

/* FUN_003d31f8 @ 0x3d31f8   (est. cL4_nop_identity)
 * Ghidra: undefined8 FUN_003d31f8(void)
 * Identity/no-op returning zero.
 * Confidence: high
 * Notes: trivial body. */
unsigned long FUN_003d31f8(void)
{
    return 0;
}

/* FUN_003d3200 @ 0x3d3200   (est. cL4_str_is_nan_inf_token)
 * Ghidra: undefined8 FUN_003d3200(byte*)
 * Return 1 if the NUL-terminated string at param_1 is the token "nan"
 * (optionally signed, case-insensitive; also accepts "snan" prefix),
 * otherwise 0. Used by the float/double parser to recognise
 * NaN/Infinity literals.
 * Confidence: high
 * Notes: matches the Swift Float/Double init(from: String) NaN detection. */
unsigned long FUN_003d3200(unsigned char *param_1)
{
    unsigned char bVar1;
    bVar1 = *param_1;
    if (bVar1 == 0x2d || bVar1 == 0x2b) {   /* '-' or '+' */
        param_1++;
        bVar1 = *param_1;
    }
    if ((((bVar1 | 0x20) == 0x73) &&        /* 's'/'S' */
         ((param_1[1] | 0x20) == 0x6e)) &&  /* 'n'/'N' */
        (((param_1[2] | 0x20) == 0x61) &&   /* 'a'/'A' */
         (param_1[3] == 0x61 && param_1[4] == 0))) {
        /* "snan" (signaling NaN) */
        return 1;
    }
    return 0;
}

/* FUN_003d326c @ 0x3d326c   (est. cL4_unicode_bitmap_index)
 * Ghidra: uint FUN_003d326c(int, long, long, long, long)
 * Core two-level bitmap index lookup shared by the Unicode scalar property
 * tables. For each of the `param_2` ranges, mixes the 16-bit range value
 * with a MurmurHash-style constant through the level-0 bitmap (param_3),
 * counts set bits (popcount) in the bitmap to derive a cumulative offset,
 * then indexes the level-1 table (param_4) and returns the populated
 * property value. Returns 0 when the range is unmapped.
 * Confidence: medium
 * Notes: this is the Swift standard library's Unicode property lookup;
 *   the constants 0x1b873593 / 0xe6546b64 are MurmurHash3 mix steps. */
unsigned int FUN_003d326c(int param_1, long param_2, long param_3,
                          long param_4, long param_5)
{
    unsigned int uVar1, uVar6, uVar8;
    unsigned short uVar2;
    unsigned long uVar3, uVar7, uVar9, lVar4, lVar5;
    char c;
    long i;

    if (param_2 != 0) {
        lVar5 = 0;
        do {
            lVar4 = *(long *)(param_3 + lVar5 * 8);
            uVar2 = *(unsigned short *)(param_5 + lVar5 * 2);
            uVar1 = (unsigned int)(param_1 * 0x16a88000u |
                    (unsigned int)(param_1 * -0x3361d2afu) >> 0x11) * 0x1b873593u ^
                    (unsigned int)lVar5;
            uVar1 = ((unsigned int)uVar2 * 0x16a88000u |
                     (unsigned int)uVar2 * -0x3361d2afu >> 0x11) * 0x1b873593u ^
                    (uVar1 >> 0x13 | uVar1 << 0xd) * 5u + 0xe6546b64u;
            uVar1 = (uVar1 >> 0x13 | uVar1 << 0xd) * 5u + 0xe6546b64u;
            uVar1 = (uVar1 ^ uVar1 >> 0x10 ^ 8) * -0x7a143595u;
            uVar1 = (uVar1 ^ uVar1 >> 0xd) * -0x3d4d51cbu;
            uVar1 = uVar1 ^ uVar1 >> 0x10;
            uVar6 = 0;
            uVar8 = (unsigned int)uVar2;
            if (uVar8 != 0) {
                uVar6 = uVar1 / uVar8;
            }
            uVar1 = uVar1 - uVar6 * uVar8;
            uVar3 = (unsigned long)(uVar1 >> 6);
            uVar9 = *(unsigned long *)(lVar4 + uVar3 * 8);
            if ((uVar9 >> (uVar1 & 0x3f) & 1) != 0) {
                uVar6 = (unsigned int)*(unsigned short *)
                        (*(long *)(param_4 + lVar5 * 8) + (unsigned long)(uVar1 >> 9) * 2);
                for (uVar7 = uVar3 & 0x3f8; uVar3 != uVar7; uVar7++) {
                    unsigned long v = *(unsigned long *)(lVar4 + uVar7 * 8);
                    uVar6 += (unsigned int)cl4_popcount64(v);
                }
                lVar5 = uVar9 << (unsigned long)(-(uVar1 & 0x3f) & 0x3f);
                if ((uVar1 & 0x3f) != 0) {
                    uVar6 += (unsigned int)cl4_popcount64(lVar5);
                }
                return uVar6 & 0xffff;
            }
            lVar5++;
        } while (param_2 != lVar5);
    }
    return 0;
}

/* FUN_003d3398 @ 0x3d3398   (est. cL4_unicode_range_index)
 * Ghidra: long FUN_003d3398(uint, long*, long)
 * Second-level Unicode property table lookup. Given a scalar value
 * param_1, a level-0 bitmap (param_2) and a level-1 offset table
 * (param_3), navigate the two-level radix (0x4400-byte / 0x110 sub-blocks)
 * via popcount accumulation, and return the byte offset into the property
 * table. Returns 0x7fffffffffffffff (the canonical "not found" sentinel)
 * when the value is unmapped.
 * Confidence: medium
 * Notes: 0x7fffffffffffffff sentinel is checked by every caller. */
long FUN_003d3398(unsigned int param_1, long *param_2, long param_3)
{
    unsigned short uVar1;
    unsigned long uVar2, uVar5, uVar8;
    long lVar3, lVar4, lVar6;
    int iVar7;

    uVar2 = param_1;
    lVar3 = *param_2;
    if (uVar2 / 0x4400 <= (unsigned long)(lVar3 - 1)) {
        uVar8 = uVar2 / 0x110 & 0x3f;
        if (((unsigned long)param_2[uVar2 / 0x4400 + 1] >> uVar8 & 1) != 0) {
            uVar1 = *(unsigned short *)(param_3 + (uVar2 / 0x4400) * 2);
            uVar5 = uVar1;
            iVar7 = (int)uVar8;
            if (iVar7 != 0) {
                lVar6 = param_2[uVar2 / 0x4400 + 1] << ((unsigned long)(unsigned int)-iVar7 & 0x3f);
                uVar5 = (unsigned long)((unsigned int)uVar1 +
                                        (unsigned int)cl4_popcount64(lVar6));
            }
            lVar6 = (uVar5 & 0xffff) * 4 + (uVar5 & 0xffff);
            param_1 = param_1 % 0x110;
            if (((unsigned long)param_2[lVar3 + lVar6 + (unsigned long)(param_1 >> 6) + 1]
                  >> (param_1 & 0x3f) & 1) != 0) {
                uVar1 = *(unsigned short *)(param_3 + lVar3 * 2 + lVar6 * 2 +
                                            (unsigned long)(param_1 >> 6) * 2);
                lVar4 = param_2[lVar3 + lVar6 + (unsigned long)(param_1 >> 6) + 1] <<
                        ((unsigned long)-(param_1 & 0x3f) & 0x3f);
                if ((param_1 & 0x3f) != 0) {
                    uVar1 = (unsigned short)(uVar1 +
                                             (unsigned short)cl4_popcount64(lVar4));
                }
                return ((unsigned long)param_2[lVar3 + lVar6 + 5] >> 0x10) +
                       (unsigned long)uVar1;
            }
        }
    }
    return 0x7fffffffffffffff;
}

/* ------------------------------------------------------------------ *
 * 0x3d3470 - 0x3d3c88 : Unicode scalar property getters built on the
 * two-level index (general category, binary properties, case mapping).
 * ------------------------------------------------------------------ */

/* FUN_003d3470 @ 0x3d3470   (est. cL4_unicode_prop_is_valid_scalar)
 * Ghidra: bool FUN_003d3470(undefined8)
 * Return true if param_1 is a defined Unicode scalar value (>= 0xA9 and
 * present in the property table). 
 * Confidence: medium
 * Notes: DAT_004f2a70/DAT_004f2f18 are the first property table. */
bool FUN_003d3470(unsigned long param_1)
{
    long lVar1;
    if ((unsigned int)param_1 < 0xa9) {
        return false;
    }
    lVar1 = FUN_003d3398(param_1, (long *)(((unsigned char*)DAT_004f2a70)), (long)(((unsigned char*)DAT_004f2f18)));
    return lVar1 != 0x7fffffffffffffff;
}

/* FUN_003d34b8 @ 0x3d34b8   (est. cL4_unicode_general_category)
 * Ghidra: uint FUN_003d34b8(uint)
 * Binary search the sorted general-category range table at 0x4f3040 and
 * return the 5-bit general category code (bits 29..) for the scalar.
 * Confidence: medium
 * Notes: entry layout: 21-bit first, 8-bit count, 5-bit category. */
unsigned int FUN_003d34b8(unsigned int param_1)
{
    unsigned int uVar1, uVar2, uVar3;
    uVar3 = 1;
    do {
        uVar1 = *(unsigned int *)((long)(int)uVar3 * 4 + 0x4f3040);
        if (param_1 < (uVar1 & 0x1fffff)) {
            uVar3 <<= 1;
        } else {
            uVar2 = 0x1ff;
            if (uVar1 >> 0x1d != 5) {
                uVar2 = 0xff;
            }
            if (param_1 <= (uVar2 & uVar1 >> 0x15) + (uVar1 & 0x1fffff)) {
                return uVar1 >> 0x1d;
            }
            uVar3 = uVar3 << 1 | 1;
        }
        if (0x23d < (int)uVar3) {
            return 0xff;
        }
    } while (1);
}

/* FUN_003d351c @ 0x3d351c   (est. cL4_unicode_prop_binary_1)
 * Ghidra: bool FUN_003d351c(undefined8)
 * Return true if the scalar is present in the binary property table
 * (DAT_004f3938/DAT_004f3c88) — e.g. "Alphabetic".
 * Confidence: medium */
bool FUN_003d351c(unsigned long param_1)
{
    long lVar1;
    lVar1 = FUN_003d3398(param_1, (long *)(((unsigned char*)DAT_004f3938)), (long)(((unsigned char*)DAT_004f3c88)));
    return lVar1 != 0x7fffffffffffffff;
}

/* FUN_003d3550 @ 0x3d3550   (est. cL4_unicode_case_mapping16)
 * Ghidra: undefined2 FUN_003d3550(undefined8)
 * For a scalar > 0xBF, look it up and return a 16-bit case-mapping value
 * from the table indexed by the property byte.
 * Confidence: low
 * Notes: DAT_004f3d60/DAT_004f4b10/DAT_004f4e7a/DAT_004f5ab0. */
unsigned short FUN_003d3550(unsigned long param_1)
{
    long lVar1;
    if (0xbf < (unsigned int)param_1) {
        lVar1 = FUN_003d3398(param_1, (long *)(((unsigned char*)DAT_004f3d60)), (long)(((unsigned char*)DAT_004f4b10)));
        if (lVar1 != 0x7fffffffffffffff) {
            return *(unsigned short *)((((unsigned char*)DAT_004f5ab0)) +
                (unsigned long)(unsigned char)((((unsigned char*)DAT_004f4e7a)))[lVar1] * 2);
        }
    }
    return 0;
}

/* FUN_003d35b0 @ 0x3d35b0   (est. cL4_unicode_prop_word32)
 * Ghidra: undefined4 FUN_003d35b0(undefined8)
 * Index a 32-bit property value for the scalar from the 12-range table.
 * Confidence: low
 * Notes: FUN_003d326c(…,0xc,0x67d130,0x67d190,(((unsigned char*)DAT_004f80d2))). */
unsigned int FUN_003d35b0(unsigned long param_1)
{
    long lVar1;
    lVar1 = FUN_003d326c(param_1, 0xc, (long)0x67d130, (long)0x67d190,
                         (long)(((unsigned char*)DAT_004f80d2)));
    return *(unsigned int *)((((unsigned char*)DAT_004f80ec)) + lVar1 * 4);
}

/* FUN_003d35f0 @ 0x3d35f0   (est. cL4_unicode_combining_class)
 * Ghidra: int FUN_003d35f0(uint, undefined8)
 * Search a 4-entry sorted table (0x67d1f0/0x67d210) via the index helper
 * for the given class value and return the mapped combining class
 * (0x3fff field) plus the scalar, or -1 if not present.
 * Confidence: low
 * Notes: binary search over puVar5 entries; -1 sentinel on miss. */
int FUN_003d35f0(unsigned int param_1, unsigned long param_2)
{
    unsigned int uVar1, uVar2, uVar3, uVar6, uVar7;
    unsigned int *puVar5;
    long lVar4;

    lVar4 = FUN_003d326c(param_2, 4, (long)0x67d1f0, (long)0x67d210,
                         (long)(((unsigned char*)DAT_004fa170)));
    puVar5 = *(unsigned int **)(lVar4 * 8 + 0x67d230);
    uVar6 = *puVar5;
    if (((unsigned int)param_2 == (uVar6 & 0x1fffff)) &&
        (uVar6 = (uVar6 >> 0x15) - 1, uVar6 != 0)) {
        uVar7 = 1;
        do {
            uVar1 = uVar7 + (uVar6 - uVar7 >> 1);
            uVar3 = puVar5[uVar1];
            uVar2 = uVar3 & 0x1ffff;
            if (param_1 == uVar2) {
                uVar7 = uVar3 >> 0x11 & 0x3fff;
                uVar6 = (int)(uVar3) < 0 ? (unsigned int)-(int)uVar7 : uVar7;
                return (int)(uVar6 + param_1);
            }
            uVar3 = uVar1 - 1;
            if (uVar2 <= param_1) {
                uVar3 = uVar6;
            }
            if (uVar2 < param_1) {
                uVar7 = uVar1 + 1;
                uVar3 = uVar6;
            }
            uVar6 = uVar3;
        } while (uVar7 <= uVar6);
    }
    return -1;
}

/* FUN_003d36b0 @ 0x3d36b0   (est. cL4_unicode_uppercase_mapping)
 * Ghidra: undefined8 FUN_003d36b0(uint)
 * Binary search the case-conversion range table (0x4fb4f8) and return the
 * mapped uppercase value for the scalar, or 0 if unmapped.
 * Confidence: medium
 * Notes: entry layout: 21-bit first, 21-bit count<<... */
unsigned long FUN_003d36b0(unsigned int param_1)
{
    int iVar1, iVar3, iVar4, iVar5;
    unsigned int uVar2, uVar6;

    iVar4 = 0;
    iVar5 = 0x13d4;
    do {
        iVar1 = iVar4 + ((unsigned int)(iVar5 - iVar4) >> 1);
        if (iVar1 == 0x13d4) {
            uVar6 = 0x10ffff;
        } else {
            uVar6 = (*(unsigned int *)((((unsigned char*)DAT_004fb4fc)) + (long)iVar1 * 4) & 0x1fffff) - 1;
        }
        uVar2 = *(unsigned int *)((((unsigned char*)DAT_004fb4f8)) + (long)iVar1 * 4) & 0x1fffff;
        if (uVar2 <= param_1 && param_1 <= uVar6) {
            return *(unsigned long *)((((unsigned char*)DAT_00500450)) +
                (unsigned long)(*(unsigned int *)((((unsigned char*)DAT_004fb4f8)) + (long)iVar1 * 4) >> 0x15) * 8);
        }
        iVar3 = iVar1 - 1;
        if (uVar2 <= param_1) {
            iVar3 = iVar5;
        }
        if (uVar6 < param_1) {
            iVar4 = iVar1 + 1;
            iVar3 = iVar5;
        }
        iVar5 = iVar3;
    } while (iVar4 <= iVar5);
    return 0;
}

/* FUN_003d3740 @ 0x3d3740   (est. cL4_unicode_bidi_class)
 * Ghidra: uint FUN_003d3740(uint)
 * Binary search the sorted table at 0x500a58 and return the 5-bit bidi /
 * general-property class for the scalar; 0xff on miss.
 * Confidence: medium
 * Notes: entry layout: 21-bit first, 8-bit count, 5-bit class. */
unsigned int FUN_003d3740(unsigned int param_1)
{
    int iVar2, iVar4, iVar6, iVar7;
    unsigned int uVar1, uVar3, uVar5;

    iVar6 = 0;
    iVar7 = 0x105;
    do {
        iVar2 = iVar6 + ((unsigned int)(iVar7 - iVar6) >> 1);
        uVar5 = *(unsigned int *)((((unsigned char*)DAT_00500a58)) + (long)iVar2 * 4);
        uVar3 = uVar5 & 0x1fffff;
        uVar1 = uVar3 + (uVar5 >> 0x15 & 0xff);
        if (uVar3 <= param_1 && param_1 <= uVar1) {
            return uVar5 >> 0x1d;
        }
        iVar4 = iVar2 - 1;
        if (uVar3 <= param_1) {
            iVar4 = iVar7;
        }
        if (uVar1 < param_1) {
            iVar6 = iVar2 + 1;
            iVar4 = iVar7;
        }
        iVar7 = iVar4;
    } while (iVar6 <= iVar7);
    return 0xff;
}

/* FUN_003d37a4 @ 0x3d37a4   (est. cL4_unicode_pair16)
 * Ghidra: undefined1[16] FUN_003d37a4(undefined8)
 * Return a 16-byte pair whose low 8 bytes hold a mapped 64-bit value for
 * the scalar (from DAT_00501670 via the 11-range index), high 8 bytes 0.
 * Confidence: low
 * Notes: FUN_003d326c(…,0xb,0x67d470,0x67d4c8,(((unsigned char*)DAT_00500e70))). */
cL4_w16_t FUN_003d37a4(unsigned long param_1)
{
    long lVar1;
    cL4_w16_t r;
    lVar1 = FUN_003d326c(param_1, 0xb, (long)0x67d470, (long)0x67d4c8,
                         (long)(((unsigned char*)DAT_00500e70)));
    r.lo = *(unsigned long *)((((unsigned char*)DAT_00501670)) +
        (unsigned long)(unsigned char)((((unsigned char*)DAT_00500e86)))[lVar1] * 8);
    r.hi = 0;
    return r;
}

/* FUN_003d37f0 @ 0x3d37f0   (est. cL4_unicode_64bit_prop)
 * Ghidra: undefined8 FUN_003d37f0(undefined8)
 * Return the 64-bit property value for the scalar from the table at
 * 0x67d520, or 0 if unmapped.
 * Confidence: medium
 * Notes: DAT_00501af0/DAT_00501ed0 are the index tables. */
unsigned long FUN_003d37f0(unsigned long param_1)
{
    long lVar1;
    unsigned long uVar2;
    lVar1 = FUN_003d3398(param_1, (long *)(((unsigned char*)DAT_00501af0)), (long)(((unsigned char*)DAT_00501ed0)));
    if (lVar1 == 0x7fffffffffffffff) {
        uVar2 = 0;
    } else {
        uVar2 = *(unsigned long *)(lVar1 * 8 + 0x67d520);
    }
    return uVar2;
}

/* FUN_003d3838 @ 0x3d3838   (est. cL4_unicode_general_category_value)
 * Ghidra: undefined4 FUN_003d3838(undefined8, int)
 * Look up the scalar in the category table (0x501fc8/0x5024e8) and return
 * the category value, selecting a byte lane by param_2 (0=lo, 1=mid,
 * 2=hi). Returns 0 on miss.
 * Confidence: low
 * Notes: DAT_00502630 holds packed category bytes. */
unsigned int FUN_003d3838(unsigned long param_1, int param_2)
{
    long lVar1;
    unsigned int uVar2;

    lVar1 = FUN_003d3398(param_1, (long *)(((unsigned char*)DAT_00501fc8)), (long)(((unsigned char*)DAT_005024e8)));
    if (lVar1 != 0x7fffffffffffffff) {
        uVar2 = *(unsigned int *)((((unsigned char*)DAT_00502630)) + lVar1 * 4);
        if (param_2 != 0) {
            if (param_2 == 2) {
                uVar2 >>= 0x10;
            } else if (param_2 == 1) {
                uVar2 >>= 8;
            } else {
                return 0;
            }
        }
        if ((uVar2 & 0xff) != 0xff) {
            return *(unsigned int *)((((unsigned char*)DAT_005054e4)) + (unsigned long)(uVar2 & 0xff) * 4);
        }
    }
    return 0;
}

/* FUN_003d38c4 @ 0x3d38c4   (est. cL4_unicode_decomposition_string)
 * Ghidra: byte* FUN_003d38c4(undefined8, int, ulong*)
 * Look up the scalar in the decomposition table and return a pointer into
 * the decomposition string storage (0x505a3f); for param_2==1 store the
 * single-byte length, for param_2==2 advance past a two-byte length prefix,
 * for 0 keep the whole string. Returns 0 on miss.
 * Confidence: low
 * Notes: DAT_005057b0/DAT_00505918 index; 0x505a3f string pool. */
unsigned char *FUN_003d38c4(unsigned long param_1, int param_2, unsigned long *param_3)
{
    unsigned char *pbVar1, *pbVar3, *pbVar5;
    long lVar2;
    unsigned long uVar4;

    lVar2 = FUN_003d3398(param_1, (long *)(((unsigned char*)DAT_005057b0)), (long)(((unsigned char*)DAT_00505918)));
    if (lVar2 == 0x7fffffffffffffff) {
        pbVar3 = 0;
    } else {
        pbVar3 = (unsigned char *)((unsigned long)*(unsigned short *)
                                   ((((unsigned char*)DAT_00505970)) + lVar2 * 2) + 0x505a3f);
        uVar4 = (unsigned char)((((unsigned char*)DAT_00505a3e)))[*(unsigned short *)((((unsigned char*)DAT_00505970)) + lVar2 * 2)];
        pbVar1 = pbVar3 + uVar4;
        pbVar5 = pbVar1 + 1;
        if (param_2 == 2) {
            pbVar3 = pbVar5 + *pbVar1 + 1;
            uVar4 = (unsigned long)pbVar5[*pbVar1];
        } else if (param_2 == 1) {
            *param_3 = (unsigned long)*pbVar1;
            return pbVar5;
        } else if (param_2 != 0) {
            return 0;
        }
        *param_3 = uVar4;
    }
    return pbVar3;
}

/* FUN_003d3964 @ 0x3d3964   (est. cL4_unicode_lowercase_mapping)
 * Ghidra: long FUN_003d3964(ulong, long, long)
 * Produce the lowercase mapping of scalar param_1 into the output buffer
 * param_2, copying at most param_3 bytes. Walks the per-scalar case-mapping
 * records (0x532a14) writing mapped bytes (spaces separating runs), stopping
 * when the buffer limit or record end is reached.
 * Confidence: low
 * Notes: DAT_00505e12/DAT_0050a214 index; DAT_0056adec/DAT_005781a0
 *   mapping byte tables. */
long FUN_003d3964(unsigned long param_1, long param_2, long param_3)
{
    unsigned int uVar1, uVar12, uVar2, iVar3;
    unsigned long uVar4;
    long lVar5, lVar7;
    unsigned char bVar6;
    unsigned char *pbVar8, *pbVar9;
    int iVar10, iVar13, iVar14;
    int *piVar11;

    if (*(unsigned short *)((((unsigned char*)DAT_00505e12)) + (param_1 >> 7 & 0x1ffffff) * 2) != 0xffff) {
        uVar12 = (unsigned int)param_1 & 0x7f |
                 (unsigned int)*(unsigned short *)((((unsigned char*)DAT_00505e12)) +
                    (param_1 >> 7 & 0x1ffffff) * 2) << 7;
        iVar3 = *(int *)((((unsigned char*)DAT_0050a214)) + (unsigned long)uVar12 * 4);
        if (((unsigned int)param_1 == 0x20) || (iVar3 != 0)) {
            if (uVar12 == 0xa1ff) {
                iVar10 = 0x383d6;
            } else {
                piVar11 = (int *)((((unsigned char*)DAT_0050a214)) + (unsigned long)uVar12 * 4);
                do {
                    piVar11++;
                    iVar10 = *piVar11;
                } while (iVar10 == 0);
            }
            if (iVar10 == iVar3) {
                return -1;
            }
            uVar12 = 0;
            iVar13 = 0;
            do {
                uVar4 = (unsigned char)((((unsigned char*)DAT_00532a14)))[uVar12 + iVar3];
                if (uVar4 == 0xff) {
                    uVar1 = iVar3 + 1 + uVar12;
                    uVar2 = uVar12 + iVar3 + 2;
                    uVar12 += 2;
                    uVar4 = (unsigned long)((unsigned char)((((unsigned char*)DAT_00532a14)))[uVar2] << 8 |
                                            (unsigned char)((((unsigned char*)DAT_00532a14)))[uVar1]);
                }
                bVar6 = ((((unsigned char*)DAT_005781a0)))[*(unsigned int *)((((unsigned char*)DAT_0056adec)) + uVar4 * 4)];
                iVar14 = iVar13;
                if ((char)bVar6 >= 0) {
                    lVar5 = (param_3 <= iVar13) ? (long)iVar13 : param_3;
                    lVar7 = lVar5 - iVar13;
                    pbVar9 = (((unsigned char*)DAT_005781a0)) + *(unsigned int *)((((unsigned char*)DAT_0056adec)) + uVar4 * 4);
                    pbVar8 = (unsigned char *)(param_2 + iVar13);
                    do {
                        pbVar9++;
                        if (lVar7 == 0) {
                            return lVar5;
                        }
                        *pbVar8 = bVar6;
                        bVar6 = *pbVar9;
                        lVar7--;
                        iVar14++;
                        pbVar8++;
                    } while ((char)bVar6 >= 0);
                }
                lVar5 = (long)iVar14;
                if (param_3 <= iVar14) {
                    return lVar5;
                }
                lVar7 = lVar5 + 1;
                *(unsigned char *)(param_2 + lVar5) = bVar6 & 0x7f;
                if (param_3 <= lVar7) {
                    return lVar7;
                }
                iVar13 = iVar14 + 2;
                *(unsigned char *)(param_2 + lVar7) = 0x20;   /* space separator */
                uVar12++;
            } while (uVar12 < (unsigned int)(iVar10 - iVar3));
            return (long)(iVar14 + 1);
        }
    }
    return 0;
}

/* FUN_003d3ac0 @ 0x3d3ac0   (est. cL4_unicode_decompose_canonical16)
 * Ghidra: undefined2 FUN_003d3ac0(ulong)
 * Binary search the canonical-decomposition range table (0x58cb70) and
 * return the 16-bit decomposition code for the scalar; 0xffff on miss.
 * Confidence: medium
 * Notes: entry layout: 21-bit first, 32-bit count, 8-bit code index. */
unsigned short FUN_003d3ac0(unsigned long param_1)
{
    int iVar1, iVar3, iVar4, iVar5;
    unsigned long uVar2, uVar6, uVar7;

    iVar4 = 0;
    param_1 &= 0xffffffff;
    iVar5 = 0x6fb;
    do {
        iVar1 = iVar4 + ((unsigned int)(iVar5 - iVar4) >> 1);
        uVar6 = *(unsigned long *)((((unsigned char*)DAT_0058cb70)) + (long)iVar1 * 8);
        uVar7 = uVar6 & 0x1fffff;
        uVar2 = uVar7 + (uVar6 >> 0x20);
        if (uVar7 <= param_1 && param_1 <= uVar2) {
            return *(unsigned short *)((((unsigned char*)DAT_00590350)) + (uVar6 >> 0x15 & 0xff) * 2);
        }
        iVar3 = iVar1 - 1;
        if (uVar7 <= param_1) {
            iVar3 = iVar5;
        }
        if (uVar2 < param_1) {
            iVar4 = iVar1 + 1;
            iVar3 = iVar5;
        }
        iVar5 = iVar3;
    } while (iVar4 <= iVar5);
    return 0xffff;
}

/* FUN_003d3b30 @ 0x3d3b30   (est. cL4_unicode_compat_mapping)
 * Ghidra: uint FUN_003d3b30(ulong)
 * Binary search the compatibility-decomposition table (0x590388) and
 * return the 21-bit mapping offset (bits 0x15..); 0xff on miss.
 * Confidence: medium */
unsigned int FUN_003d3b30(unsigned long param_1)
{
    int iVar1, iVar3, iVar4, iVar6;
    unsigned int uVar5;
    unsigned long uVar2, uVar7, uVar8;

    iVar4 = 0;
    param_1 &= 0xffffffff;
    iVar6 = 0x102f;
    do {
        iVar1 = iVar4 + ((unsigned int)(iVar6 - iVar4) >> 1);
        uVar7 = *(unsigned long *)((((unsigned char*)DAT_00590388)) + (long)iVar1 * 8);
        uVar8 = uVar7 & 0x1fffff;
        uVar2 = uVar8 + (uVar7 >> 0x20);
        if (uVar8 <= param_1 && param_1 <= uVar2) {
            uVar5 = (unsigned int)(uVar7 >> 0x15);
            return uVar5 & 0xff;
        }
        iVar3 = iVar1 - 1;
        if (uVar8 <= param_1) {
            iVar3 = iVar6;
        }
        if (uVar2 < param_1) {
            iVar4 = iVar1 + 1;
            iVar3 = iVar6;
        }
        iVar6 = iVar3;
    } while (iVar4 <= iVar6);
    return 0xff;
}

/* FUN_003d3b98 @ 0x3d3b98   (est. cL4_unicode_case_fold_code)
 * Ghidra: uint FUN_003d3b98(uint)
 * Binary search the case-folding table (0x598508) and return the folding
 * code (bits 0x15..); 0xff on miss.
 * Confidence: medium */
unsigned int FUN_003d3b98(unsigned int param_1)
{
    int iVar1, iVar3, iVar4, iVar5;
    unsigned int uVar2, uVar6;

    iVar4 = 0;
    iVar5 = 0x6b5;
    do {
        iVar1 = iVar4 + ((unsigned int)(iVar5 - iVar4) >> 1);
        if (iVar1 == 0x6b5) {
            uVar6 = 0x10ffff;
        } else {
            uVar6 = (*(unsigned int *)((((unsigned char*)DAT_0059850c)) + (long)iVar1 * 4) & 0x1fffff) - 1;
        }
        uVar2 = *(unsigned int *)((((unsigned char*)DAT_00598508)) + (long)iVar1 * 4) & 0x1fffff;
        if (uVar2 <= param_1 && param_1 <= uVar6) {
            uVar6 = *(unsigned int *)((((unsigned char*)DAT_00598508)) + (long)iVar1 * 4) >> 0x15;
            return uVar6 & 0xff;
        }
        iVar3 = iVar1 - 1;
        if (uVar2 <= param_1) {
            iVar3 = iVar5;
        }
        if (uVar6 < param_1) {
            iVar4 = iVar1 + 1;
            iVar3 = iVar5;
        }
        iVar5 = iVar3;
    } while (iVar4 <= iVar5);
    return 0xff;
}

/* FUN_003d3c1c @ 0x3d3c1c   (est. cL4_unicode_script_info)
 * Ghidra: long FUN_003d3c1c(undefined8, byte*)
 * Look up the scalar in the script table and return (a) the script byte in
 * *param_2 (bits 0xb..) and (b) an offset into the script-name string pool
 * (0x59ad42). Returns 0 on miss.
 * Confidence: low
 * Notes: DAT_00599fe0/DAT_0059a668 index; DAT_0059a808 code table. */
long FUN_003d3c1c(unsigned long param_1, unsigned char *param_2)
{
    unsigned short uVar1;
    long lVar2;

    lVar2 = FUN_003d3398(param_1, (long *)(((unsigned char*)DAT_00599fe0)), (long)(((unsigned char*)DAT_0059a668)));
    if (lVar2 == 0x7fffffffffffffff) {
        lVar2 = 0;
    } else {
        uVar1 = *(unsigned short *)((((unsigned char*)DAT_0059a808)) + lVar2 * 2);
        *param_2 = (unsigned char)(uVar1 >> 0xb);
        lVar2 = ((unsigned long)uVar1 & 0x7ff) + 0x59ad42;
    }
    return lVar2;
}

/* FUN_003d3c88 @ 0x3d3c88   (est. cL4_unicode_decompose_multi)
 * Ghidra: void FUN_003d3c88(ulong, int*)
 * Decompose the scalar into its canonical decomposition, writing the
 * mapped scalar values into the int array param_2 (one entry per code
 * point, via the 0x11-bit packing in the decomposition table). A single
 * scalar that is its own decomposition writes itself.
 * Confidence: low
 * Notes: DAT_0059af5a/DAT_0059af70 index; DAT_0059e0f8/DAT_0059e108
 *   multi-codepoint records. */
void FUN_003d3c88(unsigned long param_1, int *param_2)
{
    unsigned int uVar1, uVar2, uVar6;
    long lVar3;
    unsigned long uVar4, uVar5;

    lVar3 = FUN_003d326c(param_1, 0xb, (long)0x67d658, (long)0x67d6b0,
                         (long)(((unsigned char*)DAT_0059af5a)));
    uVar4 = *(unsigned long *)((((unsigned char*)DAT_0059af70)) + lVar3 * 8);
    uVar6 = (unsigned int)param_1;
    if (uVar6 == ((unsigned int)uVar4 & 0x1fffff)) {
        if ((long)uVar4 < 0) {
            lVar3 = FUN_003d326c(param_1, 5, (long)0x67d708, (long)0x67d730,
                                 (long)u_hF____0059e0f8);
            uVar5 = *(unsigned long *)((((unsigned char*)DAT_0059e108)) + lVar3 * 8);
            uVar4 = uVar5 >> 0x3e;
            do {
                uVar1 = (unsigned int)uVar5 & 0xffff;
                uVar2 = (unsigned int)(-(int)uVar1);
                if ((uVar5 & 0x10000) != 0) {
                    uVar2 = uVar1;
                }
                uVar5 >>= 0x11;
                *param_2 = (int)(uVar2 + uVar6);
                uVar4--;
                param_2++;
            } while (uVar4 != 0);
            return;
        }
        param_1 = (unsigned long)(uVar6 - (int)(uVar4 >> 0x15));
    }
    *param_2 = (int)param_1;
}

/* FUN_003d3d4c @ 0x3d3d4c   (est. cL4_unicode_byte_property)
 * Ghidra: undefined1 FUN_003d3d4c(uint)
 * Walk the 8-bit property trie at 0x59e9d4 (leaf at 0x59fae4) to return the
 * single-byte property for the scalar; 0xff on miss.
 * Confidence: low
 * Notes: trie entries: 21-bit first, 21-bit count. */
unsigned char FUN_003d3d4c(unsigned int param_1)
{
    unsigned int uVar1, uVar2, uVar3;

    uVar3 = 1;
    do {
        uVar2 = *(unsigned int *)((long)(int)uVar3 * 4 + 0x59e9d4);
        uVar1 = uVar2 & 0x1fffff;
        if (param_1 < uVar1) {
            uVar3 <<= 1;
        } else {
            if (param_1 <= (uVar1 + (uVar2 >> 0x15)) - 1) {
                return *(unsigned char *)((long)(int)uVar3 + 0x59fae4);
            }
            uVar3 = uVar3 << 1 | 1;
        }
    } while ((int)uVar3 < 0x444);
    return 0xff;
}

/* FUN_003d3dac @ 0x3d3dac   (est. cL4_is_once_completed)
 * Ghidra: bool FUN_003d3dac(void)
 * Return true if the once token at 0x6c0b20 equals the current thread's
 * recorded token (i.e. the once block has already been run on this thread).
 * Confidence: medium
 * Notes: _DAT_006c0b20 is the shared once token. */
bool FUN_003d3dac(void)
{
    int iVar1;
    unsigned long uVar2;

    uVar2 = cL4_current_thread();
    iVar1 = cL4_eq(uVar2, _DAT_006c0b20);
    return iVar1 != 0;
}

/* FUN_003d3dd8 @ 0x3d3dd8   (est. cL4_once_execute)
 * Ghidra: void FUN_003d3dd8(long*, code*, undefined8)
 * pthread_once-style primitive. If the token *param_1 is zero, arm it,
 * run the closure param_2 with param_3, then mark it -1 (complete) and
 * broadcast the condvar; a waiting thread wakes via cnd_wait. If the token
 * is already -1 (complete) returns immediately.
 * Confidence: high
 * Notes: uses globals 0x6c0b40 (onceCond) and 0x6c0b30 (onceMutex); the
 *   failure strings are cnd_broadcast/cnd_wait/mtx_lock/mtx_unlock asserts. */
void FUN_003d3dd8(long *param_1, void (*param_2)(unsigned long), unsigned long param_3)
{
    int iVar1;

    if (*param_1 == 0) {
        *param_1 = 1;
        (*param_2)(param_3);
        *param_1 = -1;
        FUN_003d3e94();
        FUN_003d3ed0();
        iVar1 = cL4_cnd_broadcast(0x6c0b40);
        if (iVar1 != 0) {
            cL4_fatal((const char *)0x5dbc8c);   /* "cnd_broadcast (onceCond) failed..." */
        }
        return;
    }
    FUN_003d3e94();
    do {
        if (*param_1 < 0) {
            FUN_003d3ed0();
            return;
        }
        iVar1 = cL4_cnd_wait(0x6c0b40, 0x6c0b30);
    } while (iVar1 == 0);
    cL4_fatal((const char *)0x5dbcbc);   /* "cnd_wait (onceCond, onceMutex)..." */
}

/* FUN_003d3e94 @ 0x3d3e94   (est. cL4_once_mutex_lock)
 * Ghidra: void FUN_003d3e94(void)
 * Lock the once mutex (0x6c0b30), asserting success.
 * Confidence: high
 * Notes: string ref s_mtx_lock__onceMutex___failed@0x5dbc32. */
void FUN_003d3e94(void)
{
    int iVar1;

    iVar1 = cL4_mtx_lock(0x6c0b30);
    if (iVar1 == 0) {
        return;
    }
    cL4_fatal((const char *)0x5dbc32);   /* "mtx_lock (onceMutex) failed w..." */
}

/* FUN_003d3ed0 @ 0x3d3ed0   (est. cL4_once_mutex_unlock)
 * Ghidra: void FUN_003d3ed0(void)
 * Unlock the once mutex (0x6c0b30), asserting success.
 * Confidence: high
 * Notes: string ref s_mtx_unlock__onceMutex___failed@0x5dbc5e. */
void FUN_003d3ed0(void)
{
    int iVar1;

    iVar1 = cL4_mtx_unlock(0x6c0b30);
    if (iVar1 == 0) {
        return;
    }
    cL4_fatal((const char *)0x5dbc5e);   /* "mtx_unlock (onceMutex) failed..." */
}

/* FUN_003d3f0c @ 0x3d3f0c   (est. cL4_once_global_init)
 * Ghidra: void FUN_003d3f0c(void)
 * One-time global initialiser: record the current thread as the once owner
 * and initialise the once mutex and condvar (0x6c0b30 / 0x6c0b40),
 * asserting success.
 * Confidence: high
 * Notes: string refs s___mtx_init__onceMutex___mtx_pl@0x5dbbca and
 *   s___cnd_init__onceCond___failed@0x5dbc05. */
void FUN_003d3f0c(void)
{
    int iVar1;

    _DAT_006c0b20 = cL4_current_thread();
    iVar1 = cL4_mtx_init(0x6c0b30, 0);
    if (iVar1 != 0) {
        cL4_fatal((const char *)0x5dbbca);   /* "mtx_init (onceMutex) mtx_pl..." */
    }
    iVar1 = cL4_cnd_init(0x6c0b40);
    if (iVar1 == 0) {
        return;
    }
    cL4_fatal((const char *)0x5dbc05);   /* "cnd_init (onceCond) failed w..." */
}

/* FUN_003d3f78 @ 0x3d3f78   (est. cL4_executor_job_create)
 * Ghidra: long FUN_003d3f78(void)
 * Allocate a new job/task record, initialise its executor context fields
 * (+0x10 from the current task, +0x18/+0x20 preserved registers), run the
 * retain barrier, and return the new record.
 * Confidence: low
 * Notes: uses FUN_00350b54/FUN_0036a940 and thunk_FUN_0036b270. */
long FUN_003d3f78(void)
{
    unsigned long uVar1;
    long lVar2;

    uVar1 = cL4_task_alloc();
    lVar2 = cL4_executor_storage();
    *(unsigned long *)(lVar2 + 0x10) = uVar1;
    *(unsigned long *)(lVar2 + 0x18) = 0;   /* unaff_x21 (callee-saved) */
    *(unsigned long *)(lVar2 + 0x20) = 0;   /* unaff_x19 (callee-saved) */
    cL4_retain(0);
    return lVar2;
}

/* FUN_003d3fcc @ 0x3d3fcc   (est. cL4_executor_teardown)
 * Ghidra: void FUN_003d3fcc(void)
 * Tear down the current async job/executor context: destroy the box at
 * +0x18, and if a task handle exists at +0x10, abort the task, emit trace
 * records, release references and free the frame.
 * Confidence: low
 * Notes: heavy use of trace_emit (0x2acbb8) and runtime-crash frames. */
void FUN_003d3fcc(void)
{
    unsigned long uVar1;
    long lVar2;

    cL4_box_destroy(0);                     /* unaff_x20 + 0x18 */
    if (*(long *)0x10 != 0) {
        cL4_task_abort();
        cL4_stack_mark(0x90);
        cL4_trace_emit(0xd000000000000020, 0x80000000005dbce0);
        uVar1 = *(unsigned long *)0x20;
        cL4_retain(uVar1);
        FUN_000b4390();
        cL4_trace_emit(0, 0);
        cL4_obj_release(uVar1);
        cL4_trace_emit(0xd00000000000006e, 0x80000000005dc5e0);
        lVar2 = cL4_crash_frame(0, 0);
        cL4_obj_release(0);
        cL4_frame_dealloc(lVar2 + 0x20);
        cL4_release(lVar2);
    }
}

/* ------------------------------------------------------------------ *
 * 0x3d40bc - 0x3d5a4c : Swift Concurrency async task / executor
 * machinery. The decompiler could not recover the indirect jump tables in
 * these coroutine bodies ("Too many branches"); they are reconstructed at
 * structural level with the observed call sequence preserved.
 * ------------------------------------------------------------------ */

/* FUN_003d40bc @ 0x3d40bc   (est. cL4_async_executor_cleanup_pair)
 * Ghidra: void FUN_003d40bc(void)
 * Tear down the executor context and run the async leave barrier.
 * Confidence: low
 * Notes: wraps FUN_003d3fcc + FUN_0036b6ac. */
void FUN_003d40bc(void)
{
    FUN_003d3fcc();
    FUN_0036b6ac();
}

/* FUN_003d40c0 @ 0x3d40c0   (est. cL4_async_executor_cleanup_pair2)
 * Ghidra: void FUN_003d40c0(void)
 * Same executor teardown as FUN_003d40bc (duplicate entry).
 * Confidence: low */
void FUN_003d40c0(void)
{
    FUN_003d3fcc();
    FUN_0036b6ac();
}

/* FUN_003d40e4 @ 0x3d40e4   (est. cL4_async_task_new)
 * Ghidra: undefined8 FUN_003d40e4(undefined8, undefined8, undefined8)
 * Create a new async task/job record and release the passed closure value
 * (param_3); returns the new record.
 * Confidence: low */
unsigned long FUN_003d40e4(unsigned long param_1, unsigned long param_2,
                           unsigned long param_3)
{
    unsigned long uVar1;

    uVar1 = FUN_003d3f78();
    cL4_obj_release(param_3);
    return uVar1;
}

/* FUN_003d412c @ 0x3d412c   (est. cL4_async_task_complete)
 * Ghidra: void FUN_003d412c(undefined8, long)
 * Complete an async task: destroy its context, then atomically swap the
 * completion flag at param_2+0x10 (via LOAcquire/LORelease). If a previous
 * completion was already present, forward to FUN_003d4278; otherwise
 * report the task completion through the trace/metadata path.
 * Confidence: low
 * Notes: LOAcquire/LORelease are the OSAtomic acquire/release barriers;
 *   ends in a SoftwareBreakpoint(1, 0x3d4278) trap on the error path. */
void FUN_003d412c(unsigned long param_1, long param_2)
{
    unsigned long uVar1;
    long lVar3;

    FUN_0007c028(param_1, param_1);
    (*DAT_00658c80)(0);
    FUN_000aa4ec();
    FUN_0040841c();
    (*(void (**)(void))0)();
    /* LOAcquire(); */
    lVar3 = *(long *)(param_2 + 0x10);
    *(long *)(param_2 + 0x10) = 0;
    /* LORelease(); */
    if (lVar3 != 0) {
        FUN_003d4278();
        return;
    }
    cL4_stack_mark(0x62);
    FUN_00407c5c();
    cL4_trace_emit(0xd000000000000020, 0);
    uVar1 = *(unsigned long *)(param_2 + 0x20);
    cL4_retain(uVar1);
    FUN_003504c4();
    cL4_trace_emit(0, 0);
    cL4_obj_release(uVar1);
    cL4_trace_emit(0 | 0x1c, 0x80000000005dbd10);
    FUN_00084180();
    FUN_001b1780();
    cL4_trace_emit(0xa21, 0xe200000000000000);
    FUN_00350d04();
    FUN_00407a04(0xac);
    /* __builtin_trap(); */
}

/* FUN_003d4278 @ 0x3d4278   (est. cL4_async_task_complete_already)
 * Ghidra: void FUN_003d4278(undefined8, long, long)
 * Completion path taken when the async task was already completing: invoke
 * the object's completion callback (at +0x20 / +0x40+0x28) and deallocate
 * the frame.
 * Confidence: low
 * Notes: uses object dispatch at *(lVar1+0x20) and *(obj+0x40)+0x28. */
void FUN_003d4278(unsigned long param_1, long param_2, long param_3)
{
    long lVar1;
    void (**pcVar2)();

    lVar1 = *(long *)(param_3 + -8);
    (*DAT_00658c80)(*(unsigned long *)(lVar1 + 0x40), param_1, param_1);
    pcVar2 = *(void (***)(void))(lVar1 + 0x20);
    (*pcVar2)();
    (*pcVar2)(*(unsigned long *)(*(long *)(param_2 + 0x40) + 0x28), 0, param_3);
    FUN_0040a7f0(param_2);
}

/* FUN_003d4368 @ 0x3d4368   (est. cL4_async_executor_fatal)
 * Ghidra: void FUN_003d4368(void)
 * Fatal-error path for the async executor: tear down state, report through
 * the trace/metadata system, and trap (SoftwareBreakpoint at 0x3d4428).
 * Confidence: low
 * Notes: ends with __builtin_trap. */
void FUN_003d4368(void)
{
    unsigned long uVar1;

    FUN_000b430c();
    cL4_stack_mark(0x61);
    FUN_00407c5c();
    cL4_trace_emit(0xd000000000000020, 0);
    uVar1 = *(unsigned long *)0x20;
    cL4_retain(uVar1);
    FUN_000e15d8();
    cL4_trace_emit(0, 0);
    cL4_obj_release(uVar1);
    cL4_trace_emit(0 | 0x1b, 0x80000000005dbd80);
    FUN_003507e0();
    FUN_001b1780();
    cL4_trace_emit(0xa21, 0xe200000000000000);
    FUN_004070cc();
    FUN_00407a04(0xc4);
    /* __builtin_trap(); */
}

/* FUN_003d4428 @ 0x3d4428   (est. cL4_async_dispatch_thunk)
 * Ghidra: void FUN_003d4428(undefined8, undefined8, undefined8, long, undefined8)
 * Dispatch through the async machinery: build a 16-byte job pair, invoke the
 * object's entry at param_4-8 +0x20, and forward the second word to the
 * cleanup path.
 * Confidence: low */
void FUN_003d4428(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                  long param_4, unsigned long param_5)
{
    cL4_w16_t auVar1;

    auVar1 = FUN_0036993c(param_4, param_5, 0, 0);
    (*(void (**)(unsigned long, unsigned long, long))(*(long *)(param_4 + -8) + 0x20))
        (auVar1.hi, param_1, param_4);
    FUN_0040a860(param_2, auVar1.lo);
}

/* FUN_003d44a8 @ 0x3d44a8   (est. cL4_async_run_closure)
 * Ghidra: void FUN_003d44a8(undefined8, code*, undefined8, undefined8, undefined8)
 * Run the async closure param_2: retain the job, create it, invoke the
 * closure, then release the job record.
 * Confidence: low */
void FUN_003d44a8(unsigned long param_1, void (*param_2)(void), unsigned long param_3,
                  unsigned long param_4, unsigned long param_5)
{
    unsigned long uVar1;

    cL4_retain(param_5);
    uVar1 = FUN_003d40e4(param_1, param_4, param_5);
    (*param_2)();
    cL4_release(uVar1);
}

/* FUN_003d4518 @ 0x3d4518   (est. cL4_async_task_begin_suite)
 * Ghidra: void FUN_003d4518(...8 params)
 * Begin an async task suite: store the 8 parameters into the frame's
 * +0x58..0x80 slots, branch on a job flag, and schedule a continuation
 * (FUN_003d45b0) for the task.
 * Confidence: low
 * Notes: the inner branch runs FUN_003d4658 / FUN_0034bcf0 on one side and
 *   FUN_004075c4 on the other. */
void FUN_003d4518(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                  unsigned long param_4, unsigned long param_5, unsigned long param_6,
                  unsigned long param_7, unsigned long param_8)
{
    cL4_w16_t auVar1;

    auVar1 = FUN_00406fd4();
    *(unsigned long *)(0x78) = param_7;
    *(unsigned long *)(0x80) = param_8;
    *(unsigned long *)(0x68) = param_5;
    *(unsigned long *)(0x70) = param_6;
    *(long *)(0x58) = auVar1.lo;
    *(unsigned long *)(0x60) = param_4;
    if (auVar1.hi == 0) {
        FUN_004075c4();
    } else {
        FUN_004078d4();
        FUN_003d4658(param_3);
        FUN_0034bcf0();
        (*(void (**)(void))0)();
        FUN_00407588();
    }
    FUN_00408db8((void *)FUN_003d45b0, param_4);
}

/* FUN_003d45b0 @ 0x3d45b0   (est. cL4_async_task_begin_cont)
 * Ghidra: void FUN_003d45b0(void)
 * Continuation body for an async task: load the stored parameters, build a
 * new frame with its metadata table, and dispatch through the task runner.
 * Confidence: low
 * Notes: DAT_00405fa4 is the frame metadata vtable. */
void FUN_003d45b0(void)
{
    unsigned long uVar1, uVar2, uVar3, uVar4;

    uVar3 = FUN_00408058();
    FUN_0040700c();
    uVar1 = *(unsigned long *)0x78;
    uVar2 = *(unsigned long *)0x70;
    *(long *)0x10 = 0;
    *(unsigned long *)0x38 = *(unsigned long *)0x58;
    *(unsigned long **)0x18 = (((unsigned char*)DAT_00405fa4));
    uVar4 = FUN_0040ab60((unsigned long)0x18, 0x10, 0);
    FUN_00356b80(uVar4, uVar2, uVar1);
    FUN_003d44a8(0, (void (*)(void))0, 0, 0, 0);
    FUN_00408044((unsigned long)0x10, uVar3);
    FUN_0040ada4();
}

/* FUN_003d4658 @ 0x3d4658   (est. cL4_async_unbox_payload)
 * Ghidra: long FUN_003d4658(ulong)
 * If the low bit of param_1 is set, dereference the boxed payload pointer
 * (masking the tag); otherwise return the tagged value's body: offset+4
 * plus the length word at +4.
 * Confidence: medium
 * Notes: classic tagged/boxed Swift payload decode. */
long FUN_003d4658(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 4) + (long)*(int *)(param_1 + 4);
}

/* FUN_003d4688 @ 0x3d4688   (est. cL4_async_executor_step)
 * Ghidra: void FUN_003d4688(void)
 * One step of the async executor: run the standard prologue sequence, build
 * a new frame with its continuation label (LAB_003d4740), and schedule
 * FUN_003d47f8. Ends in an unrecoverable jump-table dispatch.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d473c". */
void FUN_003d4688(void)
{
    unsigned long *puVar1;

    FUN_004079cc();
    FUN_004070d8();
    FUN_00352700();
    FUN_0034e4ec();
    FUN_0040bb18(0x40);
    FUN_00407fb4();
    FUN_00407db0(0x59ff48);
    FUN_0040bb18(0);
    puVar1 = (unsigned long *)FUN_00406fe0();
    *(unsigned long **)0x18 = puVar1;
    *puVar1 = 0;
    puVar1[1] = (unsigned long)0x3d4740;   /* LAB_003d4740 continuation */
    FUN_00407f9c(puVar1, (void *)FUN_003d47f8);
    FUN_004078f4();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d47f8 @ 0x3d47f8   (est. cL4_async_executor_step_cont)
 * Ghidra: void FUN_003d47f8(void)
 * Continuation of the executor step: run cleanup, create the next job, call
 * the saved closure, and release.
 * Confidence: low */
void FUN_003d47f8(void)
{
    unsigned long uVar1;

    FUN_00408574();
    FUN_003504ac();
    uVar1 = FUN_003d40e4(0, 0, 0);
    (*(void (**)(void))0)();
    cL4_release(uVar1);
}

/* FUN_003d484c @ 0x3d484c   (est. cL4_async_frame_run)
 * Ghidra: void FUN_003d484c(undefined8, code*)
 * Build an async frame (metadata DAT_00405fa4), run the closure param_2,
 * then tear the frame down.
 * Confidence: low */
void FUN_003d484c(unsigned long param_1, void (*param_2)(void))
{
    *(long *)0x10 = 0;
    *(unsigned long *)0x38 = param_1;
    *(unsigned long **)0x18 = (((unsigned char*)DAT_00405fa4));
    FUN_0040ab60((unsigned long)0x18, 0x10, 0);
    (*param_2)();
    FUN_0040ada4((unsigned long)0x10);
}

/* FUN_003d48e8 @ 0x3d48e8   (est. cL4_async_task_begin_suite_b)
 * Ghidra: void FUN_003d48e8(...8 params)
 * Mirror of FUN_003d4518 with continuation FUN_003d4980.
 * Confidence: low */
void FUN_003d48e8(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                  unsigned long param_4, unsigned long param_5, unsigned long param_6,
                  unsigned long param_7, unsigned long param_8)
{
    cL4_w16_t auVar1;

    auVar1 = FUN_00406fd4();
    *(unsigned long *)0x78 = param_7;
    *(unsigned long *)0x80 = param_8;
    *(unsigned long *)0x68 = param_5;
    *(unsigned long *)0x70 = param_6;
    *(long *)0x58 = auVar1.lo;
    *(unsigned long *)0x60 = param_4;
    if (auVar1.hi == 0) {
        FUN_004075c4();
    } else {
        FUN_004078d4();
        FUN_003d4658(param_3);
        FUN_0034bcf0();
        (*(void (**)(void))0)();
        FUN_00407588();
    }
    FUN_00408db8((void *)FUN_003d4980, param_4);
}

/* FUN_003d4980 @ 0x3d4980   (est. cL4_async_task_begin_cont_b)
 * Ghidra: void FUN_003d4980(void)
 * Continuation mirroring FUN_003d45b0 but with continuation FUN_003d4a28.
 * Confidence: low */
void FUN_003d4980(void)
{
    unsigned long uVar1, uVar2, uVar3, uVar4;

    uVar3 = FUN_00408058();
    FUN_0040700c();
    uVar1 = *(unsigned long *)0x78;
    uVar2 = *(unsigned long *)0x70;
    *(long *)0x10 = 0;
    *(unsigned long *)0x38 = *(unsigned long *)0x58;
    *(void (**)(void))0x18 = FUN_003d4a28;
    uVar4 = FUN_0040ab60((unsigned long)0x18, 0x10, 1);
    FUN_00356b80(uVar4, uVar2, uVar1);
    FUN_003d44a8(0, (void (*)(void))0, 0, 0, 0);
    FUN_00408044((unsigned long)0x10, uVar3);
    FUN_0040ada4();
}

/* FUN_003d4a28 @ 0x3d4a28   (est. cL4_async_task_finish)
 * Ghidra: void FUN_003d4a28(void)
 * Finish an async task: run the frame prologue and, if the result slot at
 * +0x30 is nonzero, forward it to FUN_0036986c before the exit dispatch.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d4ad0". */
void FUN_003d4a28(void)
{
    FUN_00406fd4();
    FUN_00407018();
    if (*(long *)0x30 != 0) {
        FUN_0036986c();
    }
    FUN_00407e10();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d4d0c @ 0x3d4d0c   (est. cL4_concurrency_fatal_deleted_metatype)
 * Ghidra: void FUN_003d4d0c(void)
 * Fatal "call of deleted metatype" error in the Concurrency module: build
 * the message, then raise the runtime fatal with file "Concurrency/Errors.swift".
 * Confidence: medium
 * Notes: string refs s_Fatal_error__Call_of_deleted_met@0x5cfef0 and
 *   s__Concurrency_Errors_swift@0x5dbde0 (module "Concurrency", file "Errors.swift"). */
void FUN_003d4d0c(void)
{
    unsigned long uVar1;

    FUN_00406fd4();
    FUN_0035ac70((const char *)0x5cfef0);   /* "Fatal error: Call of deleted metatype" */
    uVar1 = FUN_003593c0();
    cL4_runtime_fatal(uVar1, 0xb, 2, 0xd000000000000023,
                      0x8000000000000000, "_Concurrency/Errors.swift", 0x19, 2);
}

/* FUN_003d4d80 @ 0x3d4d80   (est. cL4_is_concurrency_available)
 * Ghidra: bool FUN_003d4d80(void)
 * Return nonzero if the Concurrency runtime feature (keyed on DAT_00614564)
 * is available.
 * Confidence: medium */
bool FUN_003d4d80(void)
{
    unsigned long uVar1;
    long lVar2;

    uVar1 = FUN_000027e8();
    lVar2 = FUN_0008dae4(uVar1, 0, (unsigned long)(((unsigned char*)DAT_00614564)));
    return lVar2 != 0;
}

/* FUN_003d4dbc @ 0x3d4dbc   (est. cL4_concurrency_fatal_error)
 * Ghidra: void FUN_003d4dbc(undefined8)
 * General Concurrency fatal error: tear down, emit the fatal-error record,
 * and trap.
 * Confidence: medium
 * Notes: string refs s_Fatal_error@0x5accd0 and
 *   s__Concurrency_Executor_swift@0x5dbde0 (module "_Concurrency"). */
void FUN_003d4dbc(unsigned long param_1)
{
    FUN_000b430c();
    cL4_stack_mark(0x3c);
    cL4_trace_emit(0xd00000000000003a, 0x80000000005dbde0);
    FUN_00208418(param_1, 0);
    FUN_000e72d4();
    cL4_obj_release(param_1);
    FUN_004070cc(0x3d4e28);
    cL4_runtime_fatal((unsigned long)(const char *)0x5accd0, 0xb, 2);   /* "Fatal error" */
}

/* FUN_003d4e84 @ 0x3d4e84   (est. cL4_concurrency_noop)
 * Ghidra: void FUN_003d4e84(void)
 * No-op.
 * Confidence: high
 * Notes: empty body. */
void FUN_003d4e84(void)
{
    return;
}

/* FUN_003d4ebc @ 0x3d4ebc   (est. cL4_executor_owned)
 * Ghidra: uint FUN_003d4ebc(undefined8, undefined8, undefined8)
 * Return 1 if the current executor owns the given job (a boolean check via
 * the executor run-loop); 0 otherwise.
 * Confidence: low
 * Notes: uses FUN_00350b54 / FUN_0014ae44 / FUN_0035063c. */
unsigned int FUN_003d4ebc(unsigned long param_1, unsigned long param_2,
                          unsigned long param_3)
{
    unsigned int uVar1;
    unsigned long uVar2;

    FUN_00350b54();
    uVar2 = FUN_0014ae44(param_3);
    FUN_0035063c(uVar2, 0, 0);
    uVar1 = (*(unsigned int (**)(void))0)();
    return uVar1 & 1;
}

/* FUN_003d4f18 @ 0x3d4f18   (est. cL4_executor_fatal_unsupported)
 * Ghidra: void FUN_003d4f18(void)
 * [[noreturn]] fatal "unsupported executor" error in _Concurrency module.
 * Confidence: medium
 * Notes: strings s_Fatal_error@0x5accd0 and s__Concurrency_Executor_swift@0x5dbe40. */
void FUN_003d4f18(void)
{
    cL4_runtime_fatal((unsigned long)(const char *)0x5accd0, 0xb, 2,
                      0xd000000000000034, 0x80000000005dbe40,
                      "_Concurrency/Executor.swift", 0x1b, 2, 0x240, 1);
}

/* FUN_003d4f78 @ 0x3d4f78   (est. cL4_executor_fatal_condition)
 * Ghidra: void FUN_003d4f78(void)
 * [[noreturn]] fatal "run(until:) not supported" error in the executor.
 * Confidence: medium
 * Notes: string ref s_run_until_condition___not_suppor@0x5dbe60. */
void FUN_003d4f78(void)
{
    unsigned long uVar1;

    uVar1 = FUN_0035ac70((const char *)0x5dbe60);  /* "run(until:) not supported..." */
    uVar1 = FUN_003593c0(uVar1, uVar1);
    cL4_runtime_fatal(uVar1, 0xb, 2, 0xd000000000000034,
                      0x8000000000000000, "_Concurrency/Executor.swift", 0x1b, 2);
}

/* FUN_003d4fd8 @ 0x3d4fd8   (est. cL4_executor_global_update)
 * Ghidra: void FUN_003d4fd8(void)
 * Update the global executor/job word (0x6adf60): run the prologue, build
 * a new job, and atomically swap the global.
 * Confidence: low
 * Notes: _DAT_006adf60 is the shared executor job global. */
void FUN_003d4fd8(void)
{
    cL4_w16_t auVar1;

    FUN_00406fc0();
    FUN_003d5028();
    FUN_0034bcf0();
    auVar1 = (*(cL4_w16_t (**)(void))0)();
    cL4_release(_DAT_006adf60);
    _DAT_006adf60 = auVar1.lo;
}

/* FUN_003d5028 @ 0x3d5028   (est. cL4_async_unbox_payload_b)
 * Ghidra: long FUN_003d5028(ulong)
 * Tagged/boxed payload decode (offset+8 variant of FUN_003d4658).
 * Confidence: medium */
long FUN_003d5028(unsigned long param_1)
{
    if ((param_1 & 1) != 0) {
        param_1 = *(unsigned long *)(param_1 & 0xfffffffffffffffe);
    }
    return (long)(param_1 + 8) + (long)*(int *)(param_1 + 8);
}

/* FUN_003d5058 @ 0x3d5058   (est. cL4_executor_global_lazy)
 * Ghidra: void FUN_003d5058(void)
 * Lazy initialisation of the executor globals: if already initialised
 * return; otherwise (unless the init token is -1) build the initial job
 * record, then publish the executor state words and take a reference.
 * Confidence: low
 * Notes: _DAT_006adf60/_DAT_006adf68/_DAT_006adf50/_DAT_006adf58 are the
 *   executor globals; _DAT_006c0b50 is the init token. */
void FUN_003d5058(void)
{
    long lVar1;

    if (_DAT_006adf60 != 0) {
        return;
    }
    if (_DAT_006c0b50 == -1) {
        lVar1 = 0;
    } else {
        FUN_00406c3c();
        FUN_0039a128();
        lVar1 = _DAT_006adf60;
    }
    _DAT_006adf68 = _DAT_006adf58;
    _DAT_006adf60 = _DAT_006adf50;
    cL4_retain(_DAT_006adf50);
    cL4_release(lVar1);
}

/* FUN_003d50cc @ 0x3d50cc   (est. cL4_executor_run_loop_guard)
 * Ghidra: void FUN_003d50cc(void)
 * Enter the executor run loop guarded by a recursive-check global: if the
 * loop is already active return; otherwise set the re-entry flag, run the
 * loop, and trap on abnormal exit.
 * Confidence: low
 * Notes: "Subroutine does not return" on the tail FUN_001afe4c. */
void FUN_003d50cc(void)
{
    FUN_004094ec();
    if (_DAT_006adf60 != 0) {
        cL4_retain(0);
        return;
    }
    FUN_003488bc(1);
    FUN_00407984();
    FUN_0034a2f8();
    FUN_001afe4c();   /* [[noreturn]] */
}

/* FUN_003d5138 @ 0x3d5138   (est. cL4_executor_run_loop_guard_b)
 * Ghidra: void FUN_003d5138(void)
 * Mirror of FUN_003d50cc (same guard logic, no retain on the active path).
 * Confidence: low */
void FUN_003d5138(void)
{
    FUN_004094ec();
    if (_DAT_006adf60 != 0) {
        return;
    }
    FUN_003488bc(1);
    FUN_00407984();
    FUN_0034a2f8();
    FUN_001afe4c();   /* [[noreturn]] */
}

/* FUN_003d5194 @ 0x3d5194   (est. cL4_executor_retain_barrier)
 * Ghidra: void FUN_003d5194(void)
 * Retain the executor global job record.
 * Confidence: low */
void FUN_003d5194(void)
{
    cL4_retain(0);
}

/* FUN_003d51c4 @ 0x3d51c4   (est. cL4_async_retain_dispatch)
 * Ghidra: void FUN_003d51c4(undefined8, undefined8, undefined8)
 * Retain param_3 and run the generic dispatch prologue.
 * Confidence: low */
void FUN_003d51c4(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    FUN_00027754(param_3);
    FUN_0007c1c4();
}

/* FUN_003d520c @ 0x3d520c   (est. cL4_async_task_offer)
 * Ghidra: void FUN_003d520c(...6 params)
 * Offer an async task to an executor: run the prologue, fetch the job
 * (param_5/param_6), and unless the low-bit flag is set, enqueue it with
 * the given enqueue flag and finish.
 * Confidence: low */
void FUN_003d520c(unsigned long param_1, unsigned long param_2, unsigned int param_3,
                  unsigned long param_4, unsigned long param_5, unsigned long param_6)
{
    cL4_w16_t auVar1;

    FUN_00353d70();
    auVar1 = FUN_00408bdc(param_5, param_6);
    if ((auVar1.lo & 1) != 0) {
        return;
    }
    FUN_00351384(auVar1.lo, auVar1.hi, param_3 & 1);
    FUN_0040761c();
    FUN_004088d8();
}

/* FUN_003d5284 @ 0x3d5284   (est. cL4_executor_has_jobs)
 * Ghidra: uint FUN_003d5284(void)
 * Return 1 if the current executor has queued jobs, 0 otherwise.
 * Confidence: low */
unsigned int FUN_003d5284(void)
{
    unsigned int uVar1;
    unsigned long uVar2;

    FUN_0034a74c();
    uVar2 = FUN_003fcafc(0);
    FUN_003504a0(uVar2);
    uVar1 = (*(unsigned int (**)(void))0)();
    return uVar1 & 1;
}

/* FUN_003d52d0 @ 0x3d52d0   (est. cL4_executor_wake_worker)
 * Ghidra: void FUN_003d52d0(void)
 * Wake the executor worker via the standard prologue + FUN_003fcb8c path.
 * Confidence: low */
void FUN_003d52d0(void)
{
    FUN_00406fc0();
    FUN_003fcb8c();
    FUN_0034bcf0();
    (*(void (**)(void))0)();
}

/* FUN_003d5308 @ 0x3d5308   (est. cL4_async_available_and_retain)
 * Ghidra: uint FUN_003d5308(undefined8, undefined8, undefined8)
 * Retain param_3 then return whether the Concurrency runtime is available.
 * Confidence: low */
unsigned int FUN_003d5308(unsigned long param_1, unsigned long param_2,
                          unsigned long param_3)
{
    unsigned int uVar1;

    FUN_00027754(param_3);
    uVar1 = FUN_003d4d80();
    return uVar1 & 1;
}

/* FUN_003d5338 @ 0x3d5338   (est. cL4_executor_sleep)
 * Ghidra: void FUN_003d5338(void)
 * Put the executor worker to sleep via FUN_003fcb2c.
 * Confidence: low */
void FUN_003d5338(void)
{
    FUN_00406fc0();
    FUN_003fcb2c();
    FUN_0034bcf0();
    (*(void (**)(void))0)();
}

/* FUN_003d5370 @ 0x3d5370   (est. cL4_executor_state)
 * Ghidra: uint FUN_003d5370(void)
 * Query executor state: return the low bit, or -1 if the state byte is 2.
 * Confidence: low */
unsigned int FUN_003d5370(void)
{
    unsigned int uVar1, uVar2;

    FUN_00406fc0();
    FUN_003fcb5c();
    FUN_0034bcf0();
    uVar2 = (*(unsigned int (**)(void))0)();
    uVar1 = uVar2 & 1;
    if ((uVar2 & 0xff) == 2) {
        uVar1 = 0xffffffff;
    }
    return uVar1;
}

/* FUN_003d53bc @ 0x3d53bc   (est. cL4_executor_teardown_guard)
 * Ghidra: void FUN_003d53bc(void)
 * Executor teardown wrapper: FUN_00406574, then the teardown body
 * FUN_003d53ec, then the retain barrier.
 * Confidence: low */
void FUN_003d53bc(void)
{
    FUN_00406574();
    FUN_003d53ec();
    cL4_retain(0);
}

/* FUN_003d53ec @ 0x3d53ec   (est. cL4_executor_teardown_body)
 * Ghidra: void FUN_003d53ec(void)
 * Executor teardown body forwarding to FUN_003e9df8.
 * Confidence: low */
void FUN_003d53ec(void)
{
    FUN_003e9df8();
}

/* FUN_003d541c @ 0x3d541c   (est. cL4_async_task_suite_enter)
 * Ghidra: void FUN_003d541c(void)
 * Large async task-suite entry: run the frame prologue, capture the task
 * record, build the executor/job context (slot +0x30..0x90), then dispatch
 * into the async run loop via an unrecoverable jump table.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d55b0". */
void FUN_003d541c(void)
{
    unsigned long uVar1;
    cL4_w16_t auVar4;

    FUN_00407ca0();
    FUN_0040700c();
    FUN_00407214();
    FUN_00350798();
    uVar1 = FUN_00310d68();
    *(unsigned long *)0x30 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x38 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x40 = uVar1;
    FUN_0040683c();
    *(unsigned long *)0x48 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x50 = uVar1;
    FUN_00406da8();
    uVar1 = FUN_00406fec().lo;
    *(unsigned long *)0x58 = uVar1;
    FUN_00350500();
    uVar1 = FUN_00310d68();
    *(unsigned long *)0x60 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x68 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x70 = uVar1;
    FUN_00406f50();
    *(unsigned long *)0x78 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x80 = uVar1;
    auVar4 = FUN_00406fec();
    uVar1 = auVar4.lo;
    *(unsigned long *)0x88 = uVar1;
    FUN_0007c1c4(uVar1, auVar4.hi, uVar1);
    uVar1 = FUN_00377bec();
    *(unsigned long *)0x90 = uVar1;
    FUN_003fcc1c();
    FUN_00408588();
    FUN_00406268();
    FUN_0040bb18(0);
    FUN_00406fe0();
    *(unsigned long **)0xa0 = (unsigned long *)FUN_00406fe0();
    FUN_00407398();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d5670 @ 0x3d5670   (est. cL4_async_task_suite_body)
 * Ghidra: void FUN_003d5670(undefined8, undefined8, code*)
 * Async task-suite body: branch on a zero-flag. The taken path reads the
 * captured result from +0x58/+0x60/+0x68, clears task state and dispatches
 * via the unrecoverable jump table; the fall-through path runs the closure
 * machinery (FUN_00406bd4 / FUN_004062a8) and builds a continuation frame.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d5704 / 0x003d57a0". */
void FUN_003d5670(unsigned long param_1, unsigned long param_2,
                  void (*UNRECOVERED_JUMPTABLE)(void))
{
    unsigned long uVar3, uVar4;

    uVar3 = FUN_00407ca0();
    FUN_0040700c();
    uVar4 = *(unsigned long *)0x58;
    (void)FUN_00406420();
    if (0) {   /* in_ZR branch (zero-flag) */
        FUN_0040711c(*(unsigned long *)0x68, uVar4, *(unsigned long *)0x60);
        FUN_004077a0();
        FUN_0040686c();
        FUN_0040bd24(uVar4);
        FUN_0040bd24(0);
        FUN_0040bd24(0);
        FUN_00407e58(0, 0, uVar3);
        /* jump-table dispatch (unrecovered) */
        return;
    }
    FUN_00406bd4(*(unsigned long *)0x78, *(unsigned long *)0x80);
    FUN_004062a8(0);
    FUN_0040bb18(0);
    FUN_00406fe0();
    *(unsigned long **)0xb0 = (unsigned long *)FUN_00406fe0();
    FUN_00407824(*(unsigned long *)0x40, *(unsigned long *)0x80);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d58a0 @ 0x3d58a0   (est. cL4_async_task_suite_body_b)
 * Ghidra: void FUN_003d58a0(void)
 * Mirror task-suite body: the taken path reads the result from +0x28/+0x30/
 * +0x38 and teardown from +0x98/+0x88; the fall-through runs the closure
 * path (FUN_0011aa70 / FUN_00407aa0). Unrecoverable jump table dispatch.
 * Confidence: low */
void FUN_003d58a0(void)
{
    unsigned long uVar1, uVar2, uVar4;

    uVar1 = FUN_0040790c();
    FUN_004070d8();
    uVar4 = *(unsigned long *)0x28;
    (void)FUN_00406420();
    if (0) {
        FUN_0040711c(*(unsigned long *)0x38, uVar4, *(unsigned long *)0x30);
        FUN_00377dcc(0, *(unsigned long *)0x88);
        FUN_00406268();
        FUN_0040bb18(0);
        FUN_00406fe0();
        *(unsigned long **)0xa0 = (unsigned long *)FUN_00406fe0();
        FUN_00407398();
        FUN_004080cc();
        /* jump-table dispatch (unrecovered) */
        return;
    }
    uVar2 = *(unsigned long *)0x50;
    FUN_00407aa0();
    FUN_0011aa70();
    (*(void (**)(void))0)();
    FUN_003504a0();
    (*(void (**)(void))0)();
    FUN_004077a0();
    FUN_00406cf0();
    FUN_0040bd24(uVar4);
    FUN_0040bd24(uVar2);
    FUN_0040bd24(0);
    FUN_004079b4(0, 0, uVar1);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d5a4c @ 0x3d5a4c   (est. cL4_async_task_suite_enter_b)
 * Ghidra: void FUN_003d5a4c(void)
 * Mirror of the large task-suite entry FUN_003d541c with the continuation
 * record (LAB_003d5c6c) and an extra result slot at +0xc8.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d5c68". */
void FUN_003d5a4c()
{
    unsigned long uVar1;
    cL4_w16_t auVar4;

    FUN_00407ca0();
    FUN_0040700c();
    FUN_00406f40();
    FUN_00408308();
    FUN_00350798();
    uVar1 = FUN_00310d68();
    *(unsigned long *)0x48 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x50 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x58 = uVar1;
    FUN_0040683c();
    *(unsigned long *)0x60 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x68 = uVar1;
    FUN_00350798();
    FUN_00350974();
    uVar1 = FUN_00377824();
    *(unsigned long *)0x70 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x78 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x80 = uVar1;
    uVar1 = FUN_00406fec().lo;
    *(unsigned long *)0x88 = uVar1;
    FUN_00350500();
    uVar1 = FUN_00310d68();
    *(unsigned long *)0x90 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x98 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0xa0 = uVar1;
    FUN_00406f50();
    *(unsigned long *)0xa8 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0xb0 = uVar1;
    auVar4 = FUN_00406fec();
    uVar1 = auVar4.lo;
    *(unsigned long *)0xb8 = uVar1;
    FUN_0007c1c4(uVar1, auVar4.hi, uVar1);
    uVar1 = FUN_00377bec();
    *(unsigned long *)0xc0 = uVar1;
    uVar1 = FUN_003fcc4c();
    *(long *)200 = uVar1;
    FUN_00377dcc(0, *(unsigned long *)0xb8);
    FUN_00406288();
    FUN_0040bb18(0);
    FUN_00406fe0();
    *(unsigned long **)0xd0 = (unsigned long *)FUN_00406fe0();
    FUN_00406bc4(*(unsigned long *)0xa0);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d5dc8 @ 0x3d5dc8   (est. cL4_async_task_suite_body_c)
 * Ghidra: void FUN_003d5dc8(undefined8, undefined8, code*)
 * Task-suite body variant: taken path reads the result from +0x58..+0xa0
 * (four releases) and dispatches; fall-through runs the closure path.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d5e70 / 0x003d5f0c". */
void FUN_003d5dc8(unsigned long param_1, unsigned long param_2,
                  void (*UNRECOVERED_JUMPTABLE)(void))
{
    unsigned long uVar3, uVar4;

    uVar3 = FUN_00407c8c();
    FUN_0040700c();
    uVar4 = FUN_00406420();
    if (0) {
        FUN_0040711c(*(unsigned long *)0x98, uVar4, *(unsigned long *)0x90);
        FUN_0040686c();
        FUN_0040bd24(*(unsigned long *)0xa0);
        FUN_0040bd24(*(unsigned long *)0x80);
        FUN_0040bd24(*(unsigned long *)0x68);
        FUN_0040bd24(*(unsigned long *)0x58);
        FUN_00407c78(0, 0, uVar3);
        /* jump-table dispatch (unrecovered) */
        return;
    }
    FUN_00406bd4(*(unsigned long *)0xa8, *(unsigned long *)0xb0);
    FUN_004062a8(0);
    FUN_0040bb18(0);
    FUN_00406fe0();
    *(unsigned long **)0xe8 = (unsigned long *)FUN_00406fe0();
    FUN_00408380(*(unsigned long *)0x58, *(unsigned long *)0xb0);
    FUN_00407c78();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d6034 @ 0x3d6034   (est. cL4_async_task_suite_body_d)
 * Ghidra: void FUN_003d6034(void)
 * Task-suite body variant: taken path (result at +0x48/+0x50, teardown at
 * +200/+0xb8) mirrors the enter path; fall-through runs the closure path.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d6114 / 0x003d61a0". */
void FUN_003d6034(void)
{
    unsigned long uVar1, uVar2, uVar5, uVar6, uVar7;

    uVar1 = FUN_0040790c();
    FUN_004070d8();
    uVar2 = FUN_00406420();
    if (0) {
        FUN_0040711c(*(unsigned long *)0x50, uVar2, *(unsigned long *)0x48);
        FUN_00377dcc(0, *(unsigned long *)0xb8);
        FUN_00406288();
        FUN_0040bb18(0);
        FUN_00406fe0();
        *(unsigned long **)0xd0 = (unsigned long *)FUN_00406fe0();
        FUN_00406bc4(*(unsigned long *)0xa0);
        FUN_004080cc();
        /* jump-table dispatch (unrecovered) */
        return;
    }
    FUN_00407aa0();
    FUN_0011aa70();
    (*(void (**)(void))0)();
    FUN_003504a0();
    (*(void (**)(void))0)();
    uVar2 = *(unsigned long *)0xa0;
    uVar5 = *(unsigned long *)0x80;
    uVar6 = *(unsigned long *)0x68;
    uVar7 = *(unsigned long *)0x58;
    FUN_00406cf0();
    FUN_0040bd24(uVar2);
    FUN_0040bd24(uVar5);
    FUN_0040bd24(uVar6);
    FUN_0040bd24(uVar7);
    FUN_004079b4(0, 0, uVar1);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d62dc @ 0x3d62dc   (est. cL4_async_task_suite_setup)
 * Ghidra: void FUN_003d62dc(undefined8, undefined8, undefined8, undefined8, long)
 * Set up an async task suite: capture param_4, build the job via
 * FUN_00377824 (metadata table DAT_00614a5c / LAB_00614a7c), allocate the
 * frame and its continuation frame, then run the task-suite body
 * FUN_003d5a4c with the recorded closure.
 * Confidence: low
 * Notes: DAT_00405fdc is the frame metadata table. */
void FUN_003d62dc(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                  unsigned long param_4, long param_5)
{
    long lVar1;
    unsigned long uVar2;
    long *plVar3;

    *(unsigned long *)0x10 = param_4;
    lVar1 = FUN_00377824(0, *(unsigned long *)(param_5 + 0x20),
                         *(unsigned long *)(param_5 + 0x10),
                         (unsigned long)(((unsigned char*)DAT_00614a5c)), (unsigned long)&LAB_00614a7c);
    *(long *)0x18 = lVar1;
    lVar1 = *(long *)(lVar1 + -8);
    *(long *)0x20 = lVar1;
    uVar2 = FUN_0040bb18(*(long *)(lVar1 + 0x40) + 0xf & 0xfffffffffffffff0);
    *(unsigned long *)0x28 = uVar2;
    plVar3 = (long *)FUN_0040bb18(DAT_0059ff7c);
    *(long **)0x30 = plVar3;
    *plVar3 = 0;
    plVar3[1] = (long)(((unsigned char*)DAT_00405fdc));
    FUN_003d5a4c(plVar3, param_1, param_2, param_3, param_5, uVar2);
}

/* FUN_003d6418 @ 0x3d6418   (est. cL4_executor_release_semaphore)
 * Ghidra: void FUN_003d6418(long, undefined8, undefined8)
 * Release `param_1` permits of the executor semaphore; a negative count is
 * a fatal error ("can't drop a negative number of...").
 * Confidence: medium
 * Notes: string ref s_Can_t_drop_a_negative_number_of_e@0x5dbed0. */
void FUN_003d6418(long param_1, unsigned long param_2, unsigned long param_3)
{
    if (-1 < param_1) {
        FUN_0035a7e8(param_1, param_2, param_2, param_3);
        FUN_003d6470();
        return;
    }
    FUN_0035ac70((const char *)0x5dbed0);   /* "Can't drop a negative number of..." */
    FUN_00406aa4();
    FUN_0040697c();
    FUN_004084d4();
    /* __builtin_trap(); */
}

/* FUN_003d6470 @ 0x3d6470   (est. cL4_executor_release_after)
 * Ghidra: void FUN_003d6470(void)
 * Post-release executor step forwarding to FUN_003dd540.
 * Confidence: low */
void FUN_003d6470()
{
    FUN_003dd540();
}

/* FUN_003d64a0 @ 0x3d64a0   (est. cL4_async_result_build)
 * Ghidra: void FUN_003d64a0(void)
 * Build an async result: capture the task context, build the job record,
 * run the frame prologue and schedule the continuation.
 * Confidence: low */
void FUN_003d64a0(void)
{
    unsigned long uVar1;

    FUN_00407000();
    uVar1 = FUN_00406704();
    *(unsigned long *)0x38 = uVar1;
    uVar1 = FUN_00310d68(0, uVar1);
    *(unsigned long *)0x40 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x48 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x50 = uVar1;
    FUN_00407594();
    FUN_00408db8();
}

/* FUN_003d6530 @ 0x3d6530   (est. cL4_async_refcount_dec)
 * Ghidra: void FUN_003d6530(void)
 * Decrement an async task's reference count at +0x24; when it reaches zero
 * clear the slot and run the completion path (FUN_004071c0), else continue
 * with the decremented path (FUN_004074c4).
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d6664". */
void FUN_003d6530(void)
{
    int iVar1;
    long lVar3;

    FUN_00407ca0();
    FUN_0040700c();
    iVar1 = *(int *)(*(long *)0x18 + 0x24);
    *(int *)0x78 = iVar1;
    lVar3 = *(long *)(*(long *)0x20 + (long)iVar1);
    *(long *)0x58 = lVar3;
    if (lVar3 < 1) {
        lVar3 = *(long *)0x30;
        *(unsigned long *)(*(long *)0x20 + (long)iVar1) = 0;
        FUN_0040652c();
        FUN_00406608();
        FUN_004068f4();
        FUN_00406268();
        FUN_0040bb18(*(unsigned int *)(lVar3 + 4));
        *(unsigned long **)0x70 = (unsigned long *)FUN_00406fe0();
        FUN_004071c0();
    } else {
        lVar3 = *(long *)0x30;
        FUN_0040652c();
        FUN_00406608();
        FUN_004068f4();
        FUN_00406268();
        FUN_0040bb18(*(unsigned int *)(lVar3 + 4));
        *(unsigned long **)0x60 = (unsigned long *)FUN_00406fe0();
        FUN_004074c4();
    }
    FUN_00406ab4();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d6724 @ 0x3d6724   (est. cL4_async_refcount_offer)
 * Ghidra: void FUN_003d6724(void)
 * Offer a task and, based on the result of the ownership check
 * (FUN_000839f8 / FUN_00351330), either complete immediately (clear slot,
 * release context) or decrement the reference count and re-run the
 * completion decision.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d67c4 / 0x003d68e0". */
void FUN_003d6724(void)
{
    int iVar1;
    unsigned long uVar2, uVar4, uVar6;
    long lVar7;
    cL4_w16_t auVar8;

    uVar2 = FUN_00407c8c();
    FUN_0040700c();
    uVar4 = *(unsigned long *)0x38;
    auVar8 = FUN_00351330();
    uVar4 = FUN_000839f8(auVar8.lo, auVar8.hi, uVar4);
    if ((int)uVar4 == 1) {
        iVar1 = *(int *)0x78;
        lVar7 = *(long *)0x20;
        uVar6 = *(unsigned long *)0x10;
        FUN_00353c00(*(unsigned long *)0x48, uVar4, *(unsigned long *)0x40);
        *(unsigned long *)(lVar7 + iVar1) = 0;
        FUN_00350744(uVar6);
        FUN_000839d8();
        FUN_0040bd24(*(unsigned long *)0x50);
        FUN_00407c78(0, 0, uVar2);
        /* jump-table dispatch (unrecovered) */
        return;
    }
    lVar7 = *(long *)0x58;
    FUN_00353c00(*(unsigned long *)0x48, uVar4, *(unsigned long *)0x40);
    lVar7--;
    *(long *)0x58 = lVar7;
    if (lVar7 == 0 || *(long *)0x58 < 1) {
        *(unsigned long *)(*(long *)0x20 + (long)*(int *)0x78) = 0;
        FUN_0040652c();
        FUN_00406608();
        FUN_004068f4();
        FUN_00406268();
        FUN_0040bb18(*(unsigned int *)(*(long *)0x30 + 4));
        *(unsigned long **)0x70 = (unsigned long *)FUN_00406fe0();
        FUN_004071c0();
    } else {
        FUN_0040652c();
        FUN_00406608();
        FUN_004068f4();
        FUN_00406268();
        FUN_0040bb18(*(unsigned int *)(*(long *)0x30 + 4));
        *(unsigned long **)0x60 = (unsigned long *)FUN_00406fe0();
        FUN_004074c4();
    }
    FUN_00406ab4();
    FUN_00407c78();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d69f8 @ 0x3d69f8   (est. cL4_async_task_suite_run)
 * Ghidra: void FUN_003d69f8(undefined8, undefined8, undefined8, long)
 * Run an async task suite: capture the job context from param_4+0x10, build
 * the job record and result frame, and branch on a worker flag to complete
 * through one of two paths, then schedule the continuation.
 * Confidence: low */
void FUN_003d69f8(unsigned long param_1, unsigned long param_2,
                 unsigned long param_3, long param_4,
                 unsigned long extra1, unsigned long extra2)
{
    unsigned long uVar1;
    (void)param_1; (void)param_2; (void)extra1; (void)extra2;

    FUN_00408058();
    FUN_0040700c();
    FUN_00406cc8();
    FUN_00408308();
    *(unsigned long *)0x48 = *(unsigned long *)(param_4 + 0x10);
    uVar1 = FUN_0040684c();
    *(unsigned long *)0x50 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x58 = 0;
    uVar1 = FUN_0040859c(0);
    *(unsigned long *)0x60 = uVar1;
    uVar1 = FUN_0040bb18(0);
    *(unsigned long *)0x68 = uVar1;
    uVar1 = FUN_00406dd0();
    *(unsigned long *)0x70 = uVar1;
    uVar1 = FUN_00310d68(0, uVar1);
    *(unsigned long *)0x78 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x80 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x88 = uVar1;
    if (0) {   /* worker flag */
        FUN_00407248();
        uVar1 = 0;
    } else {
        FUN_00406590();
        (*(void (**)(void))0)();
        FUN_0008e1ec();
        uVar1 = 0;
    }
    *(unsigned long *)0x90 = uVar1;
    *(unsigned long *)0x98 = param_3;
    FUN_00353080();
    FUN_00408044();
    FUN_00408db8();
}

/* FUN_003d6b14 @ 0x3d6b14   (est. cL4_async_task_suite_body_e)
 * Ghidra: void FUN_003d6b14(undefined8, undefined8, undefined8)
 * Task-suite body variant using the +0x28/+0x30 slot pair and the
 * +0x88/+0x68 context; unrecoverable jump-table dispatch.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d6c60". */
void FUN_003d6b14(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    int iVar1;
    long lVar3;

    FUN_00407ca0();
    FUN_0040700c();
    iVar1 = *(int *)(*(long *)0x28 + 0x24);
    *(int *)0xb8 = iVar1;
    lVar3 = *(long *)(*(long *)0x30 + (long)iVar1);
    *(long *)0xa0 = lVar3;
    if (lVar3 < 1) {
        lVar3 = *(long *)0x48;
        *(unsigned long *)(*(long *)0x30 + (long)iVar1) = 0;
        FUN_0040652c();
        FUN_00406608();
        FUN_00406e8c();
        FUN_00406288();
        FUN_0040bb18(*(unsigned int *)(lVar3 + 4));
        *(unsigned long **)0xb0 = (unsigned long *)FUN_00406fe0();
        FUN_00406f2c();
    } else {
        lVar3 = *(long *)0x48;
        FUN_0040652c();
        FUN_00406608();
        FUN_00406e8c();
        FUN_00406288();
        FUN_0040bb18(*(unsigned int *)(lVar3 + 4));
        *(unsigned long **)0xa8 = (unsigned long *)FUN_00406fe0();
        FUN_00407164(*(unsigned long *)0x88, 0, param_3, *(unsigned long *)0x68);
    }
    FUN_00406d70();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d6d50 @ 0x3d6d50   (est. cL4_async_refcount_offer_b)
 * Ghidra: void FUN_003d6d50(void)
 * Mirror of FUN_003d6724 with the +0x70/+0xb8 slot layout; unrecoverable
 * jump-table dispatch.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d6e04 / 0x003d6f38". */
void FUN_003d6d50(void)
{
    int iVar1;
    unsigned long uVar2, uVar4, uVar6;
    long lVar7;
    cL4_w16_t auVar8;

    uVar2 = FUN_00407c8c();
    FUN_0040700c();
    uVar4 = *(unsigned long *)0x70;
    auVar8 = FUN_00351330();
    uVar4 = FUN_000839f8(auVar8.lo, auVar8.hi, uVar4);
    if ((int)uVar4 == 1) {
        iVar1 = *(int *)0xb8;
        lVar7 = *(long *)0x30;
        uVar6 = *(unsigned long *)0x10;
        FUN_00353c00(*(unsigned long *)0x80, uVar4, *(unsigned long *)0x78);
        *(unsigned long *)(lVar7 + iVar1) = 0;
        FUN_00350744(uVar6);
        FUN_000839d8();
        FUN_0040bd24(*(unsigned long *)0x88);
        FUN_0040bd24(*(unsigned long *)0x68);
        FUN_0040bd24(*(unsigned long *)0x60);
        FUN_00407c78(0, 0, uVar2);
        /* jump-table dispatch (unrecovered) */
        return;
    }
    lVar7 = *(long *)0xa0;
    FUN_00353c00(*(unsigned long *)0x80, uVar4, *(unsigned long *)0x78);
    lVar7--;
    *(long *)0xa0 = lVar7;
    if (lVar7 == 0 || *(long *)0xa0 < 1) {
        *(unsigned long *)(*(long *)0x30 + (long)*(int *)0xb8) = 0;
        FUN_0040652c();
        FUN_00406608();
        FUN_00406e8c();
        FUN_00406288();
        FUN_0040bb18(*(unsigned int *)(*(long *)0x48 + 4));
        *(unsigned long **)0xb0 = (unsigned long *)FUN_00406fe0();
        FUN_00406f2c();
    } else {
        FUN_0040652c();
        FUN_00406608();
        FUN_00406e8c();
        FUN_00406288();
        FUN_0040bb18(*(unsigned int *)(*(long *)0x48 + 4));
        *(unsigned long **)0xa8 = (unsigned long *)FUN_00406fe0();
        FUN_00407164(*(unsigned long *)0x88);
    }
    FUN_00406d70();
    FUN_00407c78();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d71b8 @ 0x3d71b8   (est. cL4_async_task_suite_setup_b)
 * Ghidra: void FUN_003d71b8(undefined8, undefined8, undefined8, undefined8, long)
 * Set up a task suite (mirror of FUN_003d62dc) using context param_5+0x18
 * and running FUN_003d69f8.
 * Confidence: low
 * Notes: DAT_0059ff8c is the size global. */
void FUN_003d71b8(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                  unsigned long param_4, long param_5)
{
    long lVar1;
    unsigned long uVar2;
    long *plVar3;

    *(unsigned long *)0x10 = param_4;
    lVar1 = FUN_00377824(0, *(unsigned long *)(param_5 + 0x18),
                         *(unsigned long *)(param_5 + 0x10),
                         (unsigned long)(((unsigned char*)DAT_00614a5c)), (unsigned long)&LAB_00614a7c);
    *(long *)0x18 = lVar1;
    lVar1 = *(long *)(lVar1 + -8);
    *(long *)0x20 = lVar1;
    uVar2 = FUN_0040bb18(*(long *)(lVar1 + 0x40) + 0xf & 0xfffffffffffffff0);
    *(unsigned long *)0x28 = uVar2;
    plVar3 = (long *)FUN_0040bb18(DAT_0059ff8c);
    *(long **)0x30 = plVar3;
    *plVar3 = 0;
    plVar3[1] = (long)(((unsigned char*)DAT_00405fdc));
    FUN_003d69f8(plVar3, param_1, param_2, param_3, param_5, uVar2);
}

/* FUN_003d72f0 @ 0x3d72f0   (est. cL4_async_drop_permits)
 * Ghidra: void FUN_003d72f0(void)
 * Drop a number of executor permits: read the count, run the retain/release
 * protocol, and either call FUN_003d6470 to finish or trap on a carry
 * overflow.
 * Confidence: low
 * Notes: ends in a SoftwareBreakpoint(1, 0x3d7414) on SCARRY overflow. */
void FUN_003d72f0(void)
{
    long lVar2;

    FUN_00084220();
    FUN_003509ec();
    (void)*(unsigned long *)0x10;
    FUN_0034b7e4();
    lVar2 = (*DAT_00658c80)(0);
    if (lVar2 < 0) {
        FUN_0034a478((const char *)0x5dbed0);   /* "Can't drop a negative number of..." */
        FUN_00406aa4();
        FUN_0040697c();
        FUN_004084d4();
        /* __builtin_trap(); */
    }
    FUN_00350518();
    (*(void (**)(void))0)();
    lVar2 = *(long *)(0 + *(int *)(0 + 0x24));
    FUN_003509c8();
    (*(void (**)(void))0)();
    if (0) {   /* SCARRY8 overflow check */
        /* __builtin_trap(); */
    }
    FUN_003d6470(0, 0, lVar2, 0, 0);
    FUN_00084234(0);
}

/* FUN_003d7414 @ 0x3d7414   (est. cL4_executor_teardown_guard_b)
 * Ghidra: void FUN_003d7414(void)
 * Executor teardown wrapper forwarding to FUN_003d7440.
 * Confidence: low */
void FUN_003d7414(void)
{
    FUN_00406574();
    FUN_003d7440();
    cL4_retain(0);
}

/* FUN_003d7440 @ 0x3d7440   (est. cL4_executor_teardown_body_b)
 * Ghidra: void FUN_003d7440(void)
 * Executor teardown body forwarding to FUN_003eaf4c.
 * Confidence: low */
void FUN_003d7440(void)
{
    FUN_003eaf4c();
}

/* FUN_003d7460 @ 0x3d7460   (est. cL4_executor_flush_marks)
 * Ghidra: void FUN_003d7460(void)
 * Flush executor trace/mark records: run FUN_0009461c, FUN_003fccc4,
 * FUN_0009461c in sequence.
 * Confidence: low */
void FUN_003d7460(void)
{
    FUN_0009461c();
    FUN_003fccc4();
    FUN_0009461c();
}

/* FUN_003d7494 @ 0x3d7494   (est. cL4_async_store_result_pair)
 * Ghidra: void FUN_003d7494(undefined8, undefined8, long)
 * Store a two-word result into the frame slot selected by param_3+0x24,
 * releasing the old value first.
 * Confidence: low */
void FUN_003d7494(unsigned long param_1, unsigned long param_2, long param_3)
{
    unsigned long *puVar1;

    FUN_0008409c();
    puVar1 = (unsigned long *)(0 + *(int *)(param_3 + 0x24));
    FUN_0031d5f0(*puVar1, puVar1[1]);
    *puVar1 = param_1;
    puVar1[1] = param_2;
}

/* FUN_003d74d0 @ 0x3d74d0   (est. cL4_async_store_result_suite)
 * Ghidra: void FUN_003d74d0(void)
 * Store the async result suite: run the prologue, fetch the slot from
 * FUN_003fccd4+0x24, release the old value, run the retention protocol and
 * store the two new words.
 * Confidence: low */
void FUN_003d74d0(void)
{
    unsigned long *puVar1;
    long lVar2;

    FUN_00084220();
    FUN_0040679c();
    FUN_00407450();
    lVar2 = FUN_003fccd4();
    puVar1 = (unsigned long *)(0 + *(int *)(lVar2 + 0x24));
    FUN_0040654c();
    FUN_00350968();
    FUN_00377824();
    FUN_00349530();
    (*(void (**)(void))0)();
    *puVar1 = 0;
    puVar1[1] = 0;
    FUN_00084234(0);
}

/* FUN_003d7540 @ 0x3d7540   (est. cL4_async_result_build_b)
 * Ghidra: void FUN_003d7540(void)
 * Build an async result (mirror of FUN_003d64a0) using the +0x40 slot and
 * two property captures.
 * Confidence: low */
void FUN_003d7540(void)
{
    unsigned long uVar1;

    FUN_00407000();
    FUN_00406704();
    FUN_004079a8();
    FUN_00350798();
    uVar1 = FUN_00310d68();
    *(unsigned long *)0x40 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x48 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x50 = uVar1;
    FUN_0040683c();
    *(unsigned long *)0x58 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x60 = uVar1;
    FUN_00407594();
    FUN_00408db8();
}

/* FUN_003d75f8 @ 0x3d75f8   (est. cL4_async_task_read_pair)
 * Ghidra: void FUN_003d75f8(void)
 * Read the two-word async task payload from +0x24, build a continuation
 * frame (LAB_003d7ae4 or LAB_003d7700 depending on the first word), and
 * dispatch via the unrecoverable jump table.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d76fc". */
void FUN_003d75f8(void)
{
    int iVar3;
    long lVar2, lVar5;
    long *plVar1;

    FUN_00407c8c();
    FUN_0040700c();
    *(long *)0x68 = 0;
    iVar3 = *(int *)(*(long *)0x18 + 0x24);
    *(int *)0xa8 = iVar3;
    plVar1 = (long *)(*(long *)0x20 + (long)iVar3);
    lVar5 = *plVar1;
    *(long *)0x70 = lVar5;
    *(long *)0x78 = plVar1[1];
    lVar2 = *(long *)0x30;
    FUN_0040652c();
    FUN_00406608();
    FUN_004068f4();
    FUN_00406268();
    FUN_0040bb18(*(unsigned int *)(lVar2 + 4));
    *(unsigned long *)0x80 = 0;
    FUN_004083b4(0);
    if (lVar5 == 0) {
        /* LAB_003d7ae4 continuation */
        FUN_00407670();
    } else {
        /* LAB_003d7700 continuation */
        FUN_00407740();
    }
    FUN_00406ab4();
    FUN_00407c78();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d77bc @ 0x3d77bc   (est. cL4_async_task_continue)
 * Ghidra: void FUN_003d77bc(void)
 * Continue an async task: branch on a zero-flag from the ownership check
 * (FUN_00349f3c). Taken path reads the result from +0x40/+0x48/+0x50 and
 * dispatches; fall-through stores the continuation context and runs the
 * closure machinery.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d783c / 0x003d78d0". */
void FUN_003d77bc(void)
{
    unsigned long uVar2, uVar3;

    uVar2 = FUN_00407ca0();
    FUN_0040700c();
    uVar3 = FUN_00349f3c(*(unsigned long *)0x50);
    if (0) {
        FUN_00407f48(*(unsigned long *)0x48, uVar3, *(unsigned long *)0x40);
        FUN_00406f18();
        FUN_004081c0();
        FUN_0040bd24(0);
        FUN_00407e58(0, 0, uVar2);
        /* jump-table dispatch (unrecovered) */
        return;
    }
    FUN_00406894(*(unsigned long *)0x58, *(unsigned long *)0x60);
    *(unsigned long *)0x90 = 0;
    *(unsigned long *)0x98 = 0;
    FUN_003504a0();
    (*(void (**)(void))0)();
    FUN_004072a0();
    *(long **)0xa0 = (long *)FUN_0040bb18(0);
    FUN_00406bb4(*(unsigned long *)0x60);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d7978 @ 0x3d7978   (est. cL4_async_task_finish_suite)
 * Ghidra: void FUN_003d7978(void)
 * Finish an async task suite: branch on the flag at +0xac. Taken path runs
 * the completion decision (LAB_003d7ae4/LAB_003d7700); fall-through clears
 * the task slot, runs the release protocol and dispatches.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d7ae0 / 0x003d7a94". */
void FUN_003d7978(void)
{
    unsigned long uVar3, uVar4;
    long lVar2, lVar5;
    unsigned long *puVar1;

    uVar3 = FUN_0040790c();
    FUN_004070d8();
    if ((*(unsigned char *)0xac & 1) != 0) {
        FUN_00407cd4();
        lVar5 = *(long *)0x70;
        lVar2 = *(long *)0x30;
        FUN_0040652c();
        FUN_00406608();
        FUN_004068f4();
        FUN_00406268();
        FUN_0040bb18(*(unsigned int *)(lVar2 + 4));
        *(unsigned long *)0x80 = 0;
        FUN_004083b4(0);
        if (lVar5 == 0) {
            FUN_00407670();
        } else {
            FUN_00407740();
        }
        FUN_00406ab4();
        FUN_004080cc();
        /* jump-table dispatch (unrecovered) */
        return;
    }
    uVar4 = *(unsigned long *)0x60;
    puVar1 = (unsigned long *)(*(long *)0x20 + (long)*(int *)0xa8);
    FUN_0031d5f0(*(unsigned long *)0x70, *(unsigned long *)0x78);
    *puVar1 = 0;
    puVar1[1] = 0;
    FUN_0011aa70();
    (*(void (**)(void))0)();
    FUN_0040738c();
    FUN_00350750();
    FUN_000839d8();
    FUN_004081c0();
    FUN_0040bd24(uVar4);
    FUN_004079b4(0, 0, uVar3);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d7c18 @ 0x3d7c18   (est. cL4_async_task_suite_run_b)
 * Ghidra: void FUN_003d7c18(undefined8, undefined8, undefined8, long)
 * Run a task suite (mirror of FUN_003d69f8) capturing the +0x10 context and
 * a second property set.
 * Confidence: low */
void FUN_003d7c18(unsigned long param_1, unsigned long param_2,
                 unsigned long param_3, long param_4,
                 unsigned long extra1, unsigned long extra2)
{
    unsigned long uVar1;
    (void)param_1; (void)param_2; (void)extra1; (void)extra2;

    FUN_00408058();
    FUN_0040700c();
    FUN_00406cc8();
    FUN_00408308();
    *(unsigned long *)0x48 = *(unsigned long *)(param_4 + 0x10);
    uVar1 = FUN_0040684c();
    *(unsigned long *)0x50 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x58 = 0;
    uVar1 = FUN_0040859c(0);
    *(unsigned long *)0x60 = uVar1;
    uVar1 = FUN_0040bb18(0);
    *(unsigned long *)0x68 = uVar1;
    uVar1 = FUN_00406dd0();
    *(unsigned long *)0x70 = uVar1;
    FUN_00350798();
    uVar1 = FUN_00310d68();
    *(unsigned long *)0x78 = uVar1;
    FUN_00352018();
    *(unsigned long *)0x80 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x88 = uVar1;
    FUN_0040683c();
    *(unsigned long *)0x90 = 0;
    uVar1 = FUN_004078e8(0);
    *(unsigned long *)0x98 = uVar1;
    if (0) {
        FUN_00407248();
        uVar1 = 0;
    } else {
        FUN_00406590();
        (*(void (**)(void))0)();
        FUN_0008e1ec();
        uVar1 = 0;
    }
    *(unsigned long *)0xa0 = uVar1;
    *(unsigned long *)0xa8 = param_3;
    FUN_00353080();
    FUN_00408044();
    FUN_00408db8();
}

/* FUN_003d7d60 @ 0x3d7d60   (est. cL4_async_task_read_pair_b)
 * Ghidra: void FUN_003d7d60(undefined8, undefined8, undefined8)
 * Read the two-word task payload from the +0x28/+0x30 slot pair (variant of
 * FUN_003d75f8) and dispatch.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d7e70". */
void FUN_003d7d60(unsigned long param_1, unsigned long param_2, unsigned long param_3)
{
    int iVar3;
    long lVar2, lVar5;
    long *plVar1;

    FUN_00407c8c();
    FUN_0040700c();
    *(long *)0xb0 = 0;
    iVar3 = *(int *)(*(long *)0x28 + 0x24);
    *(int *)0xe8 = iVar3;
    plVar1 = (long *)(*(long *)0x30 + (long)iVar3);
    lVar5 = *plVar1;
    *(long *)0xb8 = lVar5;
    *(long *)0xc0 = plVar1[1];
    lVar2 = *(long *)0x48;
    FUN_0040652c();
    FUN_00406608();
    FUN_00406e8c();
    FUN_00406288();
    FUN_0040bb18(*(unsigned int *)(lVar2 + 4));
    *(unsigned long *)200 = 0;
    FUN_004083b4(0);
    if (lVar5 == 0) {
        /* LAB_003d830c continuation */
        FUN_00406f2c();
    } else {
        /* LAB_003d7e74 continuation */
        FUN_00407164(*(unsigned long *)0x88, 0, param_3, *(unsigned long *)0x68);
    }
    FUN_00406d70();
    FUN_00407c78();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d7f60 @ 0x3d7f60   (est. cL4_async_task_continue_b)
 * Ghidra: void FUN_003d7f60(void)
 * Continue an async task (mirror of FUN_003d77bc) using +0x78/+0x80/+0x88
 * slots and the closure machinery.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d8008 / 0x003d809c". */
void FUN_003d7f60(void)
{
    unsigned long uVar2, uVar3, uVar4, uVar6;
    long lVar1;

    uVar3 = FUN_00407ca0();
    FUN_0040700c();
    uVar4 = FUN_00349f3c(*(unsigned long *)0x88);
    if (0) {
        FUN_00407f48(*(unsigned long *)0x80, uVar4, *(unsigned long *)0x78);
        FUN_00350744(*(unsigned long *)0x10);
        FUN_000839d8();
        uVar6 = *(unsigned long *)0x88;
        uVar4 = *(unsigned long *)0x60;
        uVar2 = *(unsigned long *)0x68;
        FUN_0040bd24(*(unsigned long *)0x98);
        FUN_0040bd24(uVar6);
        FUN_0040bd24(uVar2);
        FUN_0040bd24(uVar4);
        FUN_00407e58(0, 0, uVar3);
        /* jump-table dispatch (unrecovered) */
        return;
    }
    lVar1 = *(long *)0xb8;
    FUN_00406894(*(unsigned long *)0x90, *(unsigned long *)0x98);
    *(unsigned long *)0xd0 = 0;
    *(unsigned long *)0xd8 = 0;
    FUN_003504a0();
    (*(void (**)(void))0)();
    FUN_004072a0();
    *(long **)0xe0 = (long *)FUN_0040bb18(0);
    FUN_00406bb4(*(unsigned long *)0x98);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d816c @ 0x3d816c   (est. cL4_async_task_finish_suite_b)
 * Ghidra: void FUN_003d816c(void)
 * Finish an async task suite (mirror of FUN_003d7978) using the +0xec flag
 * and the +0x90 continuation.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d8308 / 0x003d82bc". */
void FUN_003d816c(void)
{
    unsigned long uVar2, uVar4, uVar5, uVar6;
    long lVar3, lVar7;
    unsigned long *puVar1;

    uVar5 = FUN_0040790c();
    FUN_004070d8();
    if ((*(unsigned char *)0xec & 1) != 0) {
        (*(void (**)(unsigned long, unsigned long))(*(long *)0x90 + 8))
            (*(unsigned long *)0x98, *(unsigned long *)0x70);
        lVar7 = *(long *)0xb8;
        lVar3 = *(long *)0x48;
        FUN_0040652c();
        FUN_00406608();
        FUN_00406e8c();
        FUN_00406288();
        FUN_0040bb18(*(unsigned int *)(lVar3 + 4));
        *(unsigned long *)200 = 0;
        FUN_004083b4(0);
        if (lVar7 == 0) {
            FUN_00406f2c();
        } else {
            FUN_00407164(*(unsigned long *)0x88);
        }
        FUN_00406d70();
        FUN_004080cc();
        /* jump-table dispatch (unrecovered) */
        return;
    }
    puVar1 = (unsigned long *)(*(long *)0x30 + (long)*(int *)0xe8);
    FUN_0031d5f0(*(unsigned long *)0xb8, *(unsigned long *)0xc0);
    *puVar1 = 0;
    puVar1[1] = 0;
    FUN_0011aa70();
    (*(void (**)(void))0)();
    FUN_00350750(*(unsigned long *)0x10);
    FUN_000839d8();
    uVar6 = *(unsigned long *)0x88;
    uVar2 = *(unsigned long *)0x60;
    uVar4 = *(unsigned long *)0x68;
    FUN_0040bd24(*(unsigned long *)0x98);
    FUN_0040bd24(uVar6);
    FUN_0040bd24(uVar4);
    FUN_0040bd24(uVar2);
    FUN_004079b4(0, 0, uVar5);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d85b8 @ 0x3d85b8   (est. cL4_async_task_suite_setup_c)
 * Ghidra: void FUN_003d85b8(undefined8, undefined8, undefined8, undefined8, long)
 * Set up a task suite (variant of FUN_003d62dc) using param_5+0x18 context
 * and running FUN_003d7c18.
 * Confidence: low
 * Notes: DAT_0059ff9c is the size global. */
void FUN_003d85b8(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                  unsigned long param_4, long param_5)
{
    long lVar1;
    unsigned long uVar2;
    long *plVar3;

    *(unsigned long *)0x10 = param_4;
    lVar1 = FUN_00377824(0, *(unsigned long *)(param_5 + 0x18),
                         *(unsigned long *)(param_5 + 0x10),
                         (unsigned long)(((unsigned char*)DAT_00614a5c)), (unsigned long)&LAB_00614a7c);
    *(long *)0x18 = lVar1;
    lVar1 = *(long *)(lVar1 + -8);
    *(long *)0x20 = lVar1;
    uVar2 = FUN_0040bb18(*(long *)(lVar1 + 0x40) + 0xf & 0xfffffffffffffff0);
    *(unsigned long *)0x28 = uVar2;
    plVar3 = (long *)FUN_0040bb18(DAT_0059ff9c);
    *(long **)0x30 = plVar3;
    *plVar3 = 0;
    plVar3[1] = (long)(((unsigned char*)DAT_00405fdc));
    FUN_003d7c18(plVar3, param_1, param_2, param_3, param_5, uVar2);
}

/* FUN_003d86f0 @ 0x3d86f0   (est. cL4_executor_teardown_guard_c)
 * Ghidra: void FUN_003d86f0(void)
 * Executor teardown wrapper forwarding to FUN_003d871c.
 * Confidence: low */
void FUN_003d86f0(void)
{
    FUN_00406574();
    FUN_003d871c();
    cL4_retain(0);
}

/* FUN_003d871c @ 0x3d871c   (est. cL4_executor_teardown_body_c)
 * Ghidra: void FUN_003d871c(void)
 * Executor teardown body forwarding to FUN_003eaf4c.
 * Confidence: low */
void FUN_003d871c(void)
{
    FUN_003eaf4c();
}

/* FUN_003d873c @ 0x3d873c   (est. cL4_async_store_result_suite_b)
 * Ghidra: void FUN_003d873c(void)
 * Store an async result suite (variant): run the prologue, fetch the slot
 * from FUN_003fcd04+0x24 and pass it to FUN_00407ea0.
 * Confidence: low */
void FUN_003d873c(void)
{
    long lVar1;

    FUN_0040679c();
    FUN_0040654c();
    FUN_00350968();
    FUN_00377824();
    FUN_00349530();
    (*(void (**)(void))0)();
    FUN_00350798();
    lVar1 = FUN_003fcd04();
    FUN_00407ea0((long)*(int *)(lVar1 + 0x24));
}

/* FUN_003d87ac @ 0x3d87ac   (est. cL4_async_task_suite_capture)
 * Ghidra: void FUN_003d87ac(void)
 * Capture an async task suite: run the frame prologue, record the task
 * context (auVar4._8_8_ + 0x18), build the job record, and dispatch via the
 * unrecoverable jump table.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d88e4". */
void FUN_003d87ac(void)
{
    long lVar1;
    unsigned long uVar2;
    cL4_w16_t auVar4;

    FUN_00407ca0();
    auVar4 = FUN_0040700c();
    *(long *)0x18 = auVar4.hi;
    *(unsigned long *)0x20 = 0;
    *(long *)0x10 = auVar4.lo;
    lVar1 = *(long *)(auVar4.hi + 0x18);
    FUN_00406da8();
    uVar2 = FUN_00406fec().lo;
    *(unsigned long *)0x28 = uVar2;
    FUN_00350500();
    uVar2 = FUN_00310d68();
    *(unsigned long *)0x30 = uVar2;
    FUN_00352018();
    *(unsigned long *)0x38 = 0;
    uVar2 = FUN_004078e8(0);
    *(unsigned long *)0x40 = uVar2;
    FUN_00406f50();
    *(unsigned long *)0x48 = 0;
    uVar2 = FUN_004078e8(0);
    *(unsigned long *)0x50 = uVar2;
    auVar4 = FUN_00406fec();
    uVar2 = auVar4.lo;
    *(unsigned long *)0x58 = uVar2;
    FUN_0007c1c4(uVar2, auVar4.hi, uVar2);
    uVar2 = FUN_00377bec();
    *(unsigned long *)0x60 = uVar2;
    FUN_003fcc1c();
    FUN_00408454();
    FUN_00377dcc(0, *(unsigned long *)0x58);
    FUN_00406268();
    FUN_0040bb18(*(unsigned int *)(lVar1 + 4));
    *(unsigned long **)0x70 = (unsigned long *)FUN_00406fe0();
    FUN_004073cc();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d89a4 @ 0x3d89a4   (est. cL4_async_task_continue_c)
 * Ghidra: void FUN_003d89a4(void)
 * Continue an async task (mirror of FUN_003d77bc) using +0x28/+0x30/+0x38
 * slots and closure machinery FUN_00406894/FUN_004062e8.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d8a24 / 0x003d8abc". */
void FUN_003d89a4(void)
{
    unsigned long uVar2, uVar3, uVar5;
    long lVar1;

    uVar2 = FUN_00407ca0();
    FUN_0040700c();
    uVar5 = *(unsigned long *)0x28;
    uVar3 = FUN_00406420();
    if (0) {
        FUN_0040711c(*(unsigned long *)0x38, uVar3, *(unsigned long *)0x30);
        FUN_00407954();
        FUN_0040686c();
        FUN_0040bd24(uVar5);
        FUN_00407e58(0, 0, uVar2);
        /* jump-table dispatch (unrecovered) */
        return;
    }
    lVar1 = *(long *)0x18;
    FUN_00406894(*(unsigned long *)0x48, *(unsigned long *)0x50);
    *(unsigned long *)0x80 = 0;
    *(unsigned long *)0x88 = 0;
    FUN_00350624();
    (*(void (**)(void))0)();
    FUN_004062e8((long)*(int *)(lVar1 + 0x24));
    *(long **)0x90 = (long *)FUN_0040bb18(0);
    FUN_00406bb4(*(unsigned long *)0x50);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d8b64 @ 0x3d8b64   (est. cL4_async_task_dispatch)
 * Ghidra: void FUN_003d8b64(void)
 * Dispatch an async task: branch on the flag at +0x98. If set, call the
 * task's continuation at +0x80 and release; otherwise run the closure at
 * +0x48 and the teardown path.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d8be0 / 0x003d8c60". */
void FUN_003d8b64(void)
{
    unsigned long *puVar1;
    long lVar2;

    FUN_00406fd4();
    if (*(char *)0x98 == 1) {
        (*(void (**)(unsigned long, unsigned long, unsigned long, unsigned long))
            (*(unsigned long *)0x80))
            (*(unsigned long *)0x88, *(unsigned long *)0x10,
             *(unsigned long *)0x50, *(unsigned long *)0x28);
        FUN_00407954();
        FUN_00406cf0();
        FUN_0040bd24(0);
        FUN_0040678c();
        /* jump-table dispatch (unrecovered) */
        return;
    }
    (*(void (**)(unsigned long, unsigned long))(*(long *)0x48 + 8))
        (*(unsigned long *)0x50, *(unsigned long *)0x28);
    lVar2 = *(long *)0x68;
    FUN_00377dcc(0, *(unsigned long *)0x58);
    FUN_00406268();
    FUN_0040bb18(*(unsigned int *)(lVar2 + 4));
    *(unsigned long **)0x70 = (unsigned long *)FUN_00406fe0();
    FUN_004073cc();
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d8cc0 @ 0x3d8cc0   (est. cL4_async_task_suite_enter_c)
 * Ghidra: void FUN_003d8cc0(void)
 * Enter a task suite (variant of FUN_003d5a4c) using the +0x40 job slot and
 * the LAB_003d8e60 continuation.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d8e5c". */
void FUN_003d8cc0()
{
    long lVar1;
    unsigned long uVar2;
    cL4_w16_t auVar4;

    FUN_00407ca0();
    FUN_0040700c();
    FUN_00406f40();
    lVar1 = *(long *)(0 + 0x18);
    FUN_00350798();
    FUN_00350974();
    uVar2 = FUN_00377824();
    *(unsigned long *)0x40 = uVar2;
    FUN_00352018();
    *(unsigned long *)0x48 = 0;
    uVar2 = FUN_004078e8(0);
    *(unsigned long *)0x50 = uVar2;
    uVar2 = FUN_00406fec().lo;
    *(unsigned long *)0x58 = uVar2;
    FUN_00350500();
    uVar2 = FUN_00310d68();
    *(unsigned long *)0x60 = uVar2;
    FUN_00352018();
    *(unsigned long *)0x68 = 0;
    uVar2 = FUN_004078e8(0);
    *(unsigned long *)0x70 = uVar2;
    FUN_00406f50();
    *(unsigned long *)0x78 = 0;
    uVar2 = FUN_004078e8(0);
    *(unsigned long *)0x80 = uVar2;
    auVar4 = FUN_00406fec();
    uVar2 = auVar4.lo;
    *(unsigned long *)0x88 = uVar2;
    FUN_0007c1c4(uVar2, auVar4.hi, uVar2);
    uVar2 = FUN_00377bec();
    *(unsigned long *)0x90 = uVar2;
    FUN_003fcc4c();
    FUN_00408588();
    FUN_00406288();
    FUN_0040bb18(*(unsigned int *)(lVar1 + 4));
    *(unsigned long **)0xa0 = (unsigned long *)FUN_00406fe0();
    FUN_00406bc4(*(unsigned long *)0x70);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d8fbc @ 0x3d8fbc   (est. cL4_async_task_continue_d)
 * Ghidra: void FUN_003d8fbc(void)
 * Continue an async task (mirror of FUN_003d89a4) using +0x58/+0x60/+0x68
 * slots.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d9044 / 0x003d90dc". */
void FUN_003d8fbc(void)
{
    unsigned long uVar2, uVar3, uVar5;
    long lVar1;

    uVar2 = FUN_00407ca0();
    FUN_0040700c();
    uVar5 = *(unsigned long *)0x58;
    uVar3 = FUN_00406420();
    if (0) {
        FUN_0040711c(*(unsigned long *)0x68, uVar3, *(unsigned long *)0x60);
        FUN_00407978();
        uVar3 = *(unsigned long *)0x50;
        FUN_0040686c();
        FUN_0040bd24(uVar5);
        FUN_0040bd24(uVar3);
        FUN_00407e58(0, 0, uVar2);
        /* jump-table dispatch (unrecovered) */
        return;
    }
    lVar1 = *(long *)0x28;
    FUN_00406894(*(unsigned long *)0x78, *(unsigned long *)0x80);
    *(unsigned long *)0xb8 = 0;
    *(unsigned long *)0xc0 = 0;
    FUN_00350624();
    (*(void (**)(void))0)();
    FUN_004062e8((long)*(int *)(lVar1 + 0x24));
    *(long **)200 = (long *)FUN_0040bb18(0);
    FUN_00406bb4(*(unsigned long *)0x80);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d91ac @ 0x3d91ac   (est. cL4_async_task_dispatch_b)
 * Ghidra: void FUN_003d91ac(void)
 * Dispatch an async task (mirror of FUN_003d8b64) using the +0xd0 flag and
 * +0xb8 continuation.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x003d9230 / 0x003d92e0". */
void FUN_003d91ac(void)
{
    unsigned long uVar1;
    unsigned long *puVar2;
    long lVar3;

    FUN_00406fd4();
    if (*(char *)0xd0 == 1) {
        (*(void (**)(unsigned long, unsigned long, unsigned long, unsigned long))
            (*(unsigned long *)0xb8))
            (*(unsigned long *)0xc0, *(unsigned long *)0x10,
             *(unsigned long *)0x80, *(unsigned long *)0x58);
        FUN_00407978();
        uVar1 = *(unsigned long *)0x50;
        FUN_00406cf0();
        FUN_0040bd24(0);
        FUN_0040bd24(uVar1);
        FUN_0040678c();
        /* jump-table dispatch (unrecovered) */
        return;
    }
    (*(void (**)(unsigned long, unsigned long))(*(long *)0x78 + 8))
        (*(unsigned long *)0x80, *(unsigned long *)0x58);
    lVar3 = *(long *)0x98;
    FUN_00377dcc(0, *(unsigned long *)0x88);
    FUN_00406288();
    FUN_0040bb18(*(unsigned int *)(lVar3 + 4));
    *(unsigned long **)0xa0 = (unsigned long *)FUN_00406fe0();
    FUN_00406bc4(*(unsigned long *)0x70);
    /* jump-table dispatch (unrecovered) */
}

/* FUN_003d93f8 @ 0x3d93f8   (est. cL4_async_task_suite_setup_d)
 * Ghidra: void FUN_003d93f8(undefined8, undefined8, undefined8, undefined8, long)
 * Set up a task suite (variant of FUN_003d62dc) using param_5+0x18 context
 * and running FUN_003d8cc0.
 * Confidence: low
 * Notes: DAT_0059ffac is the size global. */
void FUN_003d93f8(unsigned long param_1, unsigned long param_2, unsigned long param_3,
                  unsigned long param_4, long param_5)
{
    long lVar1;
    unsigned long uVar2;
    long *plVar3;

    *(unsigned long *)0x10 = param_4;
    lVar1 = FUN_00377824(0, *(unsigned long *)(param_5 + 0x18),
                         *(unsigned long *)(param_5 + 0x10),
                         (unsigned long)(((unsigned char*)DAT_00614a5c)), (unsigned long)&LAB_00614a7c);
    *(long *)0x18 = lVar1;
    lVar1 = *(long *)(lVar1 + -8);
    *(long *)0x20 = lVar1;
    uVar2 = FUN_0040bb18(*(long *)(lVar1 + 0x40) + 0xf & 0xfffffffffffffff0);
    *(unsigned long *)0x28 = uVar2;
    plVar3 = (long *)FUN_0040bb18(DAT_0059ffac);
    *(long **)0x30 = plVar3;
    *plVar3 = 0;
    plVar3[1] = (long)(((unsigned char*)DAT_00405fdc));
    FUN_003d8cc0(plVar3, param_1, param_2, param_3, param_5, uVar2);
}

/* FUN_003d952c @ 0x3d952c   (est. cL4_async_task_finish_suite_c)
 * Ghidra: void FUN_003d952c(void)
 * Finish an async task suite (variant): run the prologue and closure
 * machinery, then pass the slot selected by +0x24 to FUN_004082a8.
 * Confidence: low */
void FUN_003d952c(void)
{
    FUN_00084220();
    FUN_0008409c();
    FUN_0040654c();
    FUN_003513b4();
    FUN_00377824();
    FUN_00351f10();
    FUN_0007c1a4();
    (*DAT_00658c80)();
    FUN_0034b05c();
    FUN_00407100();
    FUN_00350518();
    (*(void (**)(void))0)();
    FUN_004082a8((long)*(int *)(0 + 0x24));
    FUN_00407700();
    (*(void (**)(void))0)();
    FUN_00084234(0);
}

/* FUN_003d30b0 @ 0x3d30b0   (est. cL4_float_dispatch_helper)
 * Ghidra: void FUN_003d30b0(void)
 * Forward to the shared float/parse dispatch helper FUN_00118abc.
 * Confidence: medium
 * Notes: trivial wrapper. */
void FUN_003d30b0(void)
{
    FUN_00118abc();
}

/* FUN_003d30c4 @ 0x3d30c4   (est. cL4_str_to_double_parse)
 * Ghidra: long FUN_003d30c4(long, undefined8*)
 * Parse a double from the string in param_1 (double-precision analogue of
 * FUN_003d3130). If the token is not nan/inf, clear a scratch word and parse
 * normally, storing the status; otherwise produce the 0x7ff4... bit pattern
 * (infinity/NaN) and a length-derived value.
 * Confidence: low
 * Notes: mirror of FUN_003d3130; 0x7ff4 prefix is the IEEE double infinity
 *   exponent bit pattern. */
long FUN_003d30c4(long param_1, unsigned long *param_2)
{
    int iVar1;
    unsigned long uVar3;
    long local_28;

    iVar1 = FUN_003d3200((unsigned char *)param_1);
    if (iVar1 == 0) {
        local_28 = 0;
        *cL4_thunk_global() = 0;
        uVar3 = FUN_0011b39c(param_1, &local_28);
        *param_2 = uVar3;
    } else {
        *param_2 = 0x7ff4000000000000;
        local_28 = cL4_str_parse(param_1);
        local_28 = param_1 + local_28;
    }
    return local_28;
}

/* FUN_003d319c @ 0x3d319c   (est. cL4_str_to_float_parse)
 * Ghidra: void FUN_003d319c(undefined8, float2*)
 * Parse a single-precision float from the string and store it into the
 * 2-float vector slot param_2 (the low element is the parsed value).
 * Confidence: medium
 * Notes: forwards to FUN_003d3130 (the double parser) and narrows. */
void FUN_003d319c(unsigned long param_1, float *param_2)
{
    float local_24;

    FUN_003d3130(param_1, (unsigned int *)&local_24);
    *param_2 = local_24;
}
