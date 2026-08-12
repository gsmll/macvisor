/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice SKR46: 0x4ba0a0-0x652204 — the embedded Swift runtime ("Prespecializations"
 * library bootstrap, generic-metadata instantiation, fatal-error reporting) plus the
 * L4 IPC glue that drives the cL4 supervisor-call (CallSupervisor) ABI. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* The cL4 supervisor-call entry: the sole way from the Secure Kernel into the
 * lower guarded level. `n` selects the operation. */
#define CallSupervisor(n)  __asm__ volatile("hvc #0" ::: "memory")

/* 16-byte {lo,hi} value the runtime passes through registers/vtables. */
typedef cl4_result_t sk_pair_t;

/* Generic callable used for opaque Swift-runtime vtable dispatch
 * (the decompiler shows `(**(code **)(ctx+off))()` indirect calls). */
typedef long (*sk_fp_t)();

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 / Swift-runtime helpers (declared extern; the FUN_
 * address in each comment is ground truth; bodies are reconstructed by
 * the range worker that owns them).  Ellipsis prototypes keep call-site
 * argument counts permissive across the runtime callers.
 * ------------------------------------------------------------------ */

/* Swift-runtime metadata/report core (region 0x0011xxxx-0x0040xxxx). */
extern long FUN_001185ec();   /* register prespecialization library */
extern long FUN_0011883c();   /* runtime metadata retain/report     */
extern long FUN_00118c38();   /* runtime abort helper               */
extern long FUN_0011858c();   /* runtime cleanup                    */
extern long FUN_0011d7e8();   /* fatal: does not return             */
extern long FUN_00116d60();   /* fatal: does not return             */
extern long FUN_00118b28();   /* printf (TB_FATAL printer)          */
extern long FUN_00117cc4();   /* build crash message                */
extern long FUN_001a84f4();   /* fatal trap                         */
extern long FUN_00111854();   /* alloc retry hook                   */

/* FUN_00111854 @ 0x00111854  (est. sk_alloc_retry_hook)
 * Ghidra: undefined8 FUN_00111854(void) { return _DAT_006ad9e8; }
 * Returns the global allocator retry-hook pointer (DAT_006ad9e8).
 * Confidence: high (trivial global read; verified vs decompile 2026-08-12)
 */
long sk_alloc_retry_hook_00111854(void)
{
    extern long sk_dat_006ad9e8;  /* _DAT_006ad9e8 */
    return sk_dat_006ad9e8;
}
extern long FUN_000101a0();   /* atomic allocation attempt          */
extern long FUN_000124a4();   /* aligned allocation attempt         */
extern long FUN_0000456c();   /* parse/read word                    */
extern long FUN_00019850();   /* symbolic reference resolution      */
extern long FUN_00369bb0();   /* fatal: symbol lookup failure       */
extern long FUN_003a28ac();   /* sprintf-style format into buffer   */
extern long FUN_003d2b90();   /* Swift error construction          */
extern long FUN_003d2d34();   /* fatal error message formatting     */
extern long FUN_003878b0();   /* runtime init guard                 */
extern long FUN_00369818();   /* malloc-check mode detect           */
extern long FUN_0036e51c();   /* runtime version query              */
extern long FUN_004b8898();   /* critical-section enter             */
extern long FUN_004b895c();   /* critical-section leave             */
extern long FUN_0035b644();   /* deinit/teardown                   */
extern long FUN_0040f620();   /* current task fetch                */
extern long FUN_00369b0c();   /* flag check                        */
extern long FUN_00369b04();   /* fatal report                      */
extern long FUN_004080b0();   /* unhandled trap                    */
extern long FUN_004b5a74();   /* runtime state setup               */
extern long FUN_004b9df8();   /* fatal: print message              */
extern long FUN_004b89f8();   /* fatal: bad_alloc                  */
extern long FUN_00118c64();   /* register destructor               */
extern long FUN_0067f578();   /* crash tag function                */
extern long thunk_FUN_00012568(); /* release/deallocate            */

/* L4 IPC + runtime state helpers (region 0x0064xxxx-0x0065xxxx). */
extern long FUN_0067d798();   /* debug/trace print                 */
extern long FUN_00656a30();   /* runtime version check             */
extern long FUN_00682804();   /* image metadata lookup             */
extern long FUN_00682944();   /* image metadata fetch              */
extern long FUN_00682ec8();   /* metadata symbol lookup            */
extern long FUN_00682b48();   /* metadata section iterate          */
extern long FUN_00682bdc();   /* metadata iterator state           */
extern long FUN_00683024();   /* metadata iterator next            */
extern long FUN_00682bfc();   /* metadata iterator free            */
extern long FUN_0067d72c();   /* trace print                      */
extern long FUN_00654d4c();   /* global metadata list head         */
extern long FUN_00654d60();   /* allocator                        */
extern long FUN_0065e6fc();   /* string length                     */
extern long FUN_00656a4c();   /* string format/copy                */
extern long FUN_00656aa0();   /* string append                     */
extern long FUN_0065684c();   /* runtime flag                      */
extern long FUN_0065be40();   /* cpu/thread id                     */
extern long FUN_0065fd44();   /* ipc buffer count                  */
extern long FUN_0065fc28();   /* ipc buffer word                   */
extern long FUN_0065fd3c();   /* ipc receive check                 */
extern long FUN_0065fb08();   /* memset                          */
extern long FUN_0065fca8();   /* ipc buffer reset                  */
extern long FUN_0065fbb0();   /* ipc buffer store                  */
extern long FUN_00661318();   /* ipc write cap getter              */
extern long FUN_00664304();   /* ipc write cap setup               */
extern long FUN_0065fa24();   /* ipc buffer build                  */
extern long FUN_0065fd4c();   /* ipc send                         */
extern long FUN_006645ec();   /* ipc call dispatch                 */
extern sk_pair_t FUN_0066a8c4(); /* runtime global context (lo/hi) */
extern long FUN_0066ad54();   /* runtime alloc                    */
extern long FUN_00681c28();   /* memcpy                          */
extern long FUN_00681d20();   /* memcpy                          */
extern long FUN_00681d9c();   /* memcpy                          */
extern long FUN_00681c20();   /* allocator size                   */
extern long FUN_00681f44();   /* allocator free                   */
extern long FUN_006827a8();   /* allocator                        */
extern long FUN_006860f4();   /* runtime dealloc                  */
extern long FUN_0067f660();   /* fatal: stack-cookie mismatch (noreturn) */
extern long FUN_0067f6d8();   /* runtime context fetch             */
extern long FUN_0065558c();   /* fatal (noreturn)                  */
extern long FUN_0065c2f0();   /* fatal with message (noreturn)     */
extern long FUN_0067b280();   /* fatal overflow (noreturn)         */
extern long FUN_006833d4();   /* fatal assert (noreturn)           */

/* Runtime panic/debug printers. */
extern long FUN_006839d0();   /* panic: bad arg                   */
extern sk_pair_t FUN_006839a8(); /* panic context                 */
extern long FUN_006839f8();   /* panic printer                    */
extern long FUN_00683a20();   /* panic printer                    */
extern long FUN_00683a48();   /* panic printer                    */
extern long FUN_00683a70();   /* panic printer                    */
extern sk_pair_t FUN_00683a98(); /* panic context                 */
extern long FUN_00683ac0();   /* panic printer                    */
extern long FUN_00683ad8();   /* panic printer                    */
extern long FUN_00683af0();   /* panic printer                    */
extern long FUN_00683b08();   /* panic printer                    */
extern long FUN_00683b20();   /* panic printer                    */
extern long FUN_00683c64();   /* panic printer                    */
extern long FUN_00683d48();   /* panic printer                    */
extern long FUN_00683d60();   /* panic printer                    */
extern long FUN_00683da0();   /* panic printer                    */
extern long FUN_00683700();   /* panic printer                    */
extern long FUN_006836d8();   /* panic printer                    */
extern long FUN_006834f0();   /* panic printer                    */
extern long FUN_00683454();   /* panic printer                    */
extern long FUN_0068347c();   /* panic printer                    */
extern long FUN_006834a4();   /* panic printer                    */
extern sk_pair_t FUN_006834cc(); /* panic context                 */
extern long FUN_006836b0();   /* panic printer                    */
extern long FUN_00683688();   /* panic printer                    */
extern long FUN_00683518();   /* panic printer                    */
extern long FUN_00683540();   /* panic printer                    */
extern long FUN_00683568();   /* panic printer                    */
extern long FUN_00683658();   /* panic printer                    */
extern long FUN_00683590();   /* panic printer                    */
extern long FUN_006835b8();   /* panic printer                    */
extern long FUN_00683630();   /* panic printer                    */
extern long FUN_006835e0();   /* panic printer                    */
extern long FUN_00683608();   /* panic printer                    */
extern long FUN_00683750();   /* panic printer                    */
extern long FUN_00683728();   /* panic printer                    */
extern long FUN_006837a0();   /* panic printer                    */
extern long FUN_00683778();   /* panic printer                    */
extern long FUN_006837c8();   /* panic printer                    */
extern long FUN_00683890();   /* panic printer                    */
extern long FUN_006838e0();   /* panic printer                    */
extern long FUN_006838b8();   /* panic printer                    */
extern long FUN_00683908();   /* panic printer                    */
extern long FUN_00683930();   /* panic printer                    */
extern long FUN_00683958();   /* panic printer                    */
extern long FUN_00683980();   /* panic printer                    */
extern long FUN_00683840();   /* panic printer                    */
extern long FUN_006837f0();   /* panic printer                    */

/* Metadata iteration / image state. */
extern long FUN_00655848();   /* current image state              */
extern long FUN_00653b74();   /* type metadata lookup             */
extern long FUN_00653bb8();   /* type lookup                      */
extern long FUN_00653c98();   /* type metadata check              */
extern long FUN_0065cb74();   /* image list head                  */
extern long FUN_0065cc50();   /* image deregister                 */
extern long FUN_0065e454();   /* image register                   */
extern long FUN_00655c84();   /* metadata walk                    */
extern long FUN_0065c9fc();   /* thread id                        */
extern long FUN_0066469c();   /* cpu info                         */
extern long FUN_006529d8();   /* string fetch                     */
extern long FUN_0067ce74();   /* memcpy into buffer               */
extern long FUN_006531d8();   /* metadata write                   */
extern long FUN_00652a38();   /* metadata copy                    */
extern long FUN_00652e34();   /* metadata bind                    */
extern long FUN_00672de4();   /* type registration                */
extern long FUN_00662380();   /* memory store                     */
extern long FUN_0067ca84();   /* message print                    */
extern sk_pair_t FUN_0067cc5c(); /* metadata lookup               */
extern long FUN_0067b220();   /* strlen                          */
extern long thunk_FUN_0067aa00(); /* memcpy                      */
extern long thunk_FUN_0067a780(); /* memset                      */
extern long thunk_FUN_0067aff0(); /* memcmp                      */
extern long thunk_FUN_0065564c(); /* memcpy                      */
extern long FUN_00656c84();   /* runtime cleanup after IPC bind */
extern long FUN_00656a14();   /* runtime generic-type counter */
extern long FUN_0068342c();   /* panic printer                 */
extern long FUN_00683404();   /* panic printer                 */

/* ------------------------------------------------------------------ *
/* 0x4ba0a0-0x4bac9c — Swift runtime bootstrap: prespecialization library
 * registration and the fatal-error / allocation-report helpers that the
 * embedded Swift runtime uses when it cannot proceed.
 * ------------------------------------------------------------------ */

/* Binary global at 0x6adfb0: malloc-check mode (0=unknown, 1=checked, 2=unchecked). */
static unsigned char sk_r46_malloc_check_mode;
/* Segment-command global referenced by the stack allocator bounds check. */
extern unsigned char segment_command_00000020;

void sk_r46_fatal_unhandled_1(void);

/* FUN_004ba0a0 @ 0x004ba0a0   (est. sk_r46_prespecializations_register_0)
 * Ghidra: void FUN_004ba0a0(void)
 * Registers the "Prespecializations library" with the Swift runtime using the
 * runtime's metadata discriminator magic (0xeb1a02bf914012ba) and the 
 * library-specific header string at 0x5d4b89. Called once during kernel boot to
 * make the pre-instantiated generic metadata available.
 * Confidence: medium
 * Notes: string ref s_Prespecializations_library__Sett_005d4b89 */
void sk_r46_prespecializations_register_0(void)
{
    FUN_001185ec(0xeb1a02bf914012ba, (void *)0x5d4b89); /* "Prespecializations library ..." @ 0x5d4b89 */
}

/* FUN_004ba0f4 @ 0x004ba0f4   (est. sk_r46_prespecializations_register_1)
 * Ghidra: void FUN_004ba0f4(void)
 * Second registration site: same discriminator magic, header string at 0x5d4bdd.
 * Confidence: medium
 * Notes: string ref s_Prespecializations_library__Sett_005d4bdd */
void sk_r46_prespecializations_register_1(void)
{
    FUN_001185ec(0xeb1a02bf914012ba, (void *)0x5d4bdd); /* "Prespecializations library ..." @ 0x5d4bdd */
}

/* FUN_004ba148 @ 0x004ba148   (est. sk_r46_prespecializations_register_versioned)
 * Ghidra: void FUN_004ba148(void)
 * Registers the prespecializations library after querying the runtime version
 * (FUN_0036e51c) and passing it as the first argument alongside the library
 * header string at 0x5d4c8f.
 * Confidence: medium
 * Notes: string ref s_Prespecializations_library___s_005d4c8f */
void sk_r46_prespecializations_register_versioned(void)
{
    uint64_t version = (uint64_t)FUN_0036e51c();
    FUN_001185ec(version, (void *)0x5d4c8f); /* "Prespecializations library ..." @ 0x5d4c8f */
}

/* FUN_004ba180 @ 0x004ba180   (est. sk_r46_swift_critical_section_once)
 * Ghidra: void FUN_004ba180(void)
 * Enter a critical section guarded by the runtime lock at 0x6c0548; if the lock
 * was not already held (FUN_004b8898 returns nonzero) the section is a single
 * call that leaves the lock again.
 * Confidence: medium
 * Notes: lock object DAT_006c0548 */
void sk_r46_swift_critical_section_once(void)
{
    if (FUN_004b8898((void *)0x6c0548) != 0) {
        FUN_004b895c((void *)0x6c0548);
    }
}

/* FUN_004ba1b8 @ 0x004ba1b8   (est. sk_r46_swift_runtime_teardown_guard)
 * Ghidra: void FUN_004ba1b8(void)
 * Runs the runtime-init guard (FUN_003878b0); if the global critical lock is
 * taken, invokes the deinit/teardown helper (FUN_0035b644) and drops the lock.
 * Confidence: medium */
void sk_r46_swift_runtime_teardown_guard(void)
{
    FUN_003878b0();
    if (FUN_004b8898() != 0) {
        FUN_0035b644();
        FUN_004b895c();
    }
}

/* FUN_004ba1e0 @ 0x004ba1e0   (est. sk_r46_swift_runtime_teardown_guard_2)
 * Ghidra: void FUN_004ba1e0(void)
 * Identical to FUN_004ba1b8: init guard, then locked teardown+unlock.
 * Confidence: medium */
void sk_r46_swift_runtime_teardown_guard_2(void)
{
    FUN_003878b0();
    if (FUN_004b8898() != 0) {
        FUN_0035b644();
        FUN_004b895c();
    }
}

/* FUN_004ba214 @ 0x004ba214   (est. sk_r46_symbolic_reference_resolve)
 * Ghidra: void FUN_004ba214(undefined2 *param_1, undefined8 param_2)
 * Resolves a symbolic reference: reads a word from param_2, stores it into the
 * two-byte output slot, and walks the runtime's fixup list (FUN_00019850) until
 * the resolved slot carries the marker byte 0x01. If resolution fails it traps
 * with "Failed to look up symbolic reference".
 * Confidence: medium
 * Notes: string s_Failed_to_look_up_symbolic_refer_005d51b4; SoftwareBreakpoint(1,0x4ba2e4) */
void sk_r46_symbolic_reference_resolve(uint16_t *out, uint64_t ref)
{
    uint32_t word = (uint32_t)FUN_0000456c(ref);
    *out = (uint16_t)word;
    if ((word >> 8 & 1) != 0) {
        long slot = FUN_00019850(out);
        if (slot != 0) {
            if (*(char *)((long)out + 1) != '\x01') goto resolve_failed;
            FUN_00019850(out);
        }
        if (*(char *)((long)out + 1) != '\x01') {
resolve_failed:
            /* trap: SoftwareBreakpoint(1,0x4ba2e4) - unreachable */
            __builtin_unreachable();
        }
        slot = FUN_00019850(out);
        if (slot != 0) {
            if (*(char *)((long)out + 1) != '\x01') goto resolve_failed;
            FUN_00019850(out);
        }
    }
    FUN_00369bb0(0, (void *)0x5d51b4); /* "Failed to look up symbolic reference" @ 0x5d51b4 */
}

/* FUN_004ba2e4 @ 0x004ba2e4   (est. sk_r46_critical_section_fixed)
 * Ghidra: void FUN_004ba2e4(void)
 * Critical section around a single fixed resource (arg 0x657740): if the lock is
 * taken, run teardown and release.
 * Confidence: medium */
void sk_r46_critical_section_fixed(void)
{
    if (FUN_004b8898((void *)0x657740) != 0) {
        FUN_0035b644();
        FUN_004b895c();
    }
}

/* FUN_004ba310 @ 0x004ba310   (est. sk_r46_report_assert_message)
 * Ghidra: void FUN_004ba310(undefined8 param_1, undefined8 param_2, long param_3)
 * Formats a "%s%s" / "%s%s@%s:%u" message (the @file:line suffix appears when
 * param_3 is nonzero) into a stack buffer and reports it to the Swift runtime
 * with the metadata discriminator. Stack-cookie protected.
 * Confidence: medium
 * Notes: strings s__s_s_005d684e, s__s_s_at__s__u_005d683f */
void sk_r46_report_assert_message(uint64_t a, uint64_t b, long line)
{
    char buf[1024];
    uint64_t cookie = 0xd37adf4bb401ff2a; /* -0x2c8502b44bfffed6 */
    const char *fmt = (line == 0) ? (const char *)0x5d684e : (const char *)0x5d683f; /* "%s%s" / "%s%s@%s:%u" */
    FUN_003a28ac(buf, b, line, (void *)fmt);
    FUN_0011883c(buf, 0xeb1a02bf914012ba);
    if (cookie == 0xd37adf4bb401ff2a) {
        FUN_0011858c();
        return;
    }
    FUN_0011d7e8(0xeb1a02bf914012ba); /* fatal: does not return */
}

/* FUN_004ba3a8 @ 0x004ba3a8   (est. sk_r46_fatal_out_of_memory)
 * Ghidra: void FUN_004ba3a8(void)
 * Reports "LLVM ERROR: out of memory" via the assert-message helper and aborts.
 * Confidence: medium
 * Notes: strings s_LLVM_ERROR__005d6832, s_out_of_memory_005b211e */
void sk_r46_fatal_out_of_memory(void)
{
    sk_r46_report_assert_message(0x5d6832, 0x5b211e, 0); /* "LLVM ERROR: " / "out of memory" */
    FUN_00116d60(); /* fatal: does not return */
}

/* FUN_004ba3d4 @ 0x004ba3d4   (est. sk_r46_fatal_error_report)
 * Ghidra: void FUN_004ba3d4(void)
 * Reports a "fatal error: %s" message to the runtime and aborts.
 * Confidence: medium
 * Notes: string s_fatal_error___s_005d9054 */
void sk_r46_fatal_error_report(uint64_t msg)
{
    (void)msg;
    FUN_001185ec(0xeb1a02bf914012ba, (void *)0x5d9054); /* "fatal error: %s" @ 0x5d9054 */
    FUN_00116d60(); /* fatal: does not return */
}

/* FUN_004ba408 @ 0x004ba408   (est. sk_r46_fatal_should_be_child_of)
 * Ghidra: void FUN_004ba408(void)
 * Swift-compiler fatal: "should be printed as a child of a ..."
 * Confidence: medium
 * Notes: string s_should_be_printed_as_a_child_of_a_005d8846 */
void sk_r46_fatal_should_be_child_of(void)
{
    sk_r46_fatal_error_report(0x5d8846);
}

/* FUN_004ba420 @ 0x004ba420   (est. sk_r46_fatal_option_sets)
 * Ghidra: void FUN_004ba420(void)
 * Swift-compiler fatal: "option sets should have been han[dled] ..."
 * Confidence: medium
 * Notes: string s_option_sets_should_have_been_han_005d7a0d */
void sk_r46_fatal_option_sets(void)
{
    sk_r46_fatal_error_report(0x5d7a0d);
}

/* FUN_004ba438 @ 0x004ba438   (est. sk_r46_fatal_printSpecialization)
 * Ghidra: void FUN_004ba438(void)
 * Swift-compiler fatal: "should be handled in printSpecia[lization]..."
 * Confidence: medium
 * Notes: string s_should_be_handled_in_printSpecia_005d7851 */
void sk_r46_fatal_printSpecialization(void)
{
    sk_r46_fatal_error_report(0x5d7851);
}

/* FUN_004ba450 @ 0x004ba450   (est. sk_r46_fatal_Node_Kind)
 * Ghidra: void FUN_004ba450(void)
 * Swift-compiler fatal: "should be handled in Node::Kind::..."
 * Confidence: medium
 * Notes: string s_should_be_handled_in_Node__Kind__005d768e */
void sk_r46_fatal_Node_Kind(void)
{
    sk_r46_fatal_error_report(0x5d768e);
}

/* FUN_004ba468 @ 0x004ba468   (est. sk_r46_fatal_bad_directness)
 * Ghidra: void FUN_004ba468(void)
 * Swift-compiler fatal: "bad directness".
 * Confidence: medium
 * Notes: string s_bad_directness_005d909f */
void sk_r46_fatal_bad_directness(void)
{
    sk_r46_fatal_error_report(0x5d909f);
}

/* FUN_004ba480 @ 0x004ba480   (est. sk_r46_fatal_bad_node_kind_colon)
 * Ghidra: void FUN_004ba480(void)
 * Swift-compiler fatal: "bad node kind: ".
 * Confidence: medium
 * Notes: string s_bad_node_kind__005d900f */
void sk_r46_fatal_bad_node_kind_colon(void)
{
    sk_r46_fatal_error_report(0x5d900f);
}

/* FUN_004ba498 @ 0x004ba498   (est. sk_r46_fatal_bad_node_kind)
 * Ghidra: void FUN_004ba498(void)
 * Swift-compiler fatal: "bad node kind".
 * Confidence: medium
 * Notes: string s_bad_node_kind_005d7043 */
void sk_r46_fatal_bad_node_kind(void)
{
    sk_r46_fatal_error_report(0x5d7043);
}

/* FUN_004ba4b0 @ 0x004ba4b0   (est. sk_r46_fatal_no_state_after_Results)
 * Ghidra: void FUN_004ba4b0(void)
 * Swift-compiler fatal: "no state after Results".
 * Confidence: medium
 * Notes: string s_no_state_after_Results_005d906e */
void sk_r46_fatal_no_state_after_Results(void)
{
    sk_r46_fatal_error_report(0x5d906e);
}

/* FUN_004ba4c8 @ 0x004ba4c8   (est. sk_r46_fatal_bad_state)
 * Ghidra: void FUN_004ba4c8(void)
 * Swift-compiler fatal: "bad state".
 * Confidence: medium
 * Notes: string s_bad_state_005d9085 */
void sk_r46_fatal_bad_state(void)
{
    sk_r46_fatal_error_report(0x5d9085);
}

/* FUN_004ba4e0 @ 0x004ba4e0   (est. sk_r46_fatal_bad_value_witness_kind)
 * Ghidra: void FUN_004ba4e0(void)
 * Swift-compiler fatal: "bad value witness kind".
 * Confidence: medium
 * Notes: string s_bad_value_witness_kind_005d91f5 */
void sk_r46_fatal_bad_value_witness_kind(void)
{
    sk_r46_fatal_error_report(0x5d91f5);
}

/* FUN_004ba4f8 @ 0x004ba4f8   (est. sk_r46_fatal_not_abstract_storage)
 * Ghidra: void FUN_004ba4f8(void)
 * Swift-compiler fatal: "Not an abstract storage node".
 * Confidence: medium
 * Notes: string s_Not_an_abstract_storage_node_005d901e */
void sk_r46_fatal_not_abstract_storage(void)
{
    sk_r46_fatal_error_report(0x5d901e);
}

/* FUN_004ba510 @ 0x004ba510   (est. sk_r46_make_swift_error)
 * Ghidra: void FUN_004ba510(undefined8 param_1)
 * Builds a Swift error value from a code using FUN_003d2b90 and reports it via
 * the runtime metadata path, releasing on the failure path.
 * Confidence: low (error-value packing is partially opaque)
 * Notes: thunk_FUN_00012568 release; 0x7fffffffffffffff mask clears the sign bit */
void sk_r46_make_swift_error(uint64_t code)
{
    uint64_t err_lo = 0, err_hi = 0, err_size = 0;
    FUN_003d2b90(&err_lo, code, 0);
    uint64_t out_lo = err_lo, out_hi = err_hi, out_size = err_size;
    if ((long)err_size < 0) {
        FUN_0011883c(err_lo, 0xeb1a02bf914012ba);
        thunk_FUN_00012568(out_lo, out_hi & 0x7fffffffffffffff);
    } else {
        FUN_0011883c(&out_lo, 0xeb1a02bf914012ba);
    }
}

/* FUN_004ba5a4 @ 0x004ba5a4   (est. sk_r46_report_fatal_error_2)
 * Ghidra: void FUN_004ba5a4(undefined8 param_1, undefined8 param_2)
 * Formats a fatal error message from two arguments and reports it; if formatting
 * fails, prints "unable to format fatal error message" and aborts.
 * Confidence: medium
 * Notes: string s_unable_to_format_fatal_error_mes_005db677 */
void sk_r46_report_fatal_error_2(uint64_t a, uint64_t b)
{
    uint64_t msg;
    if ((int)FUN_003d2d34(&msg, a, b) < 0) {
        FUN_004b9df8((void *)0x5db677); /* "unable to format fatal error message" */
        FUN_00116d60(); /* fatal */
    }
    FUN_004b9df8((void *)msg);
    FUN_00116d60(); /* fatal */
}

/* FUN_004ba5c4 @ 0x004ba5c4   (est. sk_r46_report_fatal_error_3)
 * Ghidra: void FUN_004ba5c4(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Formats a fatal error message from two values (b, c) and reports it; aborts if
 * formatting fails.
 * Confidence: medium
 * Notes: string s_unable_to_format_fatal_error_mes_005db677 */
void sk_r46_report_fatal_error_3(uint64_t a, uint64_t b, uint64_t c)
{
    (void)a;
    uint64_t msg;
    if ((int)FUN_003d2d34(&msg, b, c) < 0) {
        FUN_004b9df8((void *)0x5db677); /* "unable to format fatal error message" */
        FUN_00116d60(); /* fatal */
    }
    FUN_004b9df8((void *)msg);
    FUN_00116d60(); /* fatal */
}

/* FUN_004ba5dc @ 0x004ba5dc   (est. sk_r46_report_fatal_error_1)
 * Ghidra: void FUN_004ba5dc(undefined8 param_1, undefined8 param_2)
 * Formats a fatal error message from two values and reports it; aborts if
 * formatting fails.
 * Confidence: medium
 * Notes: string s_unable_to_format_fatal_error_mes_005db677 */
void sk_r46_report_fatal_error_1(uint64_t a, uint64_t b)
{
    uint64_t msg;
    if ((int)FUN_003d2d34(&msg, a, b) < 0) {
        FUN_004b9df8((void *)0x5db677); /* "unable to format fatal error message" */
        FUN_00116d60(); /* fatal */
    }
    FUN_004b9df8((void *)msg);
    FUN_00116d60(); /* fatal */
}

/* FUN_004ba620 @ 0x004ba620   (est. sk_r46_runtime_abort)
 * Ghidra: void FUN_004ba620(void)
 * Reports an abort to the Swift runtime and terminates.
 * Confidence: medium */
void sk_r46_runtime_abort(void)
{
    FUN_00118c38(0xeb1a02bf914012ba);
    FUN_00116d60(); /* fatal: does not return */
}

/* FUN_004ba640 @ 0x004ba640   (est. sk_r46_allocator_stack_alloc)
 * Ghidra: undefined8 * FUN_004ba640(void)
 * Allocates a fixed 0x20-byte slot from a malloc-checked stack allocator; if the
 * runtime is in malloc-check mode (DAT_006adfb0) it materialises a 0x6adfa8-magic
 * header block at the current frame.
 * Confidence: low
 * Notes: magic 0x6adfa8; globals DAT_006adfb0, segment_command ref */
uint64_t *sk_r46_allocator_stack_alloc(void)
{
    sk_pair_t frame = { 0, 0 };
    uint64_t *out = (uint64_t *)frame.lo;
    out[0] = 0;
    out[1] = 0;
    *((uint32_t *)(out + 2)) = 0;
    if (&segment_command_00000020 < (void *)__builtin_frame_address(0)) {
        if (sk_r46_malloc_check_mode == '\0') {
            int ok = (int)FUN_00369818();
            sk_r46_malloc_check_mode = '\x01';
            if (ok == 0) sk_r46_malloc_check_mode = '\x02';
        }
        if (sk_r46_malloc_check_mode == '\x01') {
            uint64_t *blk = (uint64_t *)((frame.hi + 0xfU) & ~0xfULL);
            blk[0] = 0x6adfa8;
            blk[1] = 0;
            *((int *)(blk + 2)) = ((int)frame.hi + (int)(uintptr_t)__builtin_frame_address(0)) - (int)(uintptr_t)blk - 0x20;
            *((uint32_t *)((long)blk + 0x14)) = 0;
            out[1] = (uint64_t)blk;
            *((uint32_t *)(out + 2)) = 1;
        }
    }
    return out;
}

/* FUN_004ba660 @ 0x004ba660   (est. sk_r46_allocator_stack_alloc_sized)
 * Ghidra: undefined8 * FUN_004ba660(undefined8 *param_1, long param_2, ulong param_3)
 * Stack allocator: fills the output header at param_1 and, when the requested size
 * exceeds 0x20 and the runtime is in malloc-check mode, materialises a 0x6adfa8-magic
 * sub-block at the aligned end of the region.
 * Confidence: low
 * Notes: magic 0x6adfa8; globals DAT_006adfb0 */
uint64_t *sk_r46_allocator_stack_alloc_sized(uint64_t *out, long base, uint64_t size)
{
    out[0] = 0;
    out[1] = 0;
    *((uint32_t *)(out + 2)) = 0;
    if (0x20 < size) {
        if (sk_r46_malloc_check_mode == '\0') {
            int ok = (int)FUN_00369818();
            sk_r46_malloc_check_mode = '\x01';
            if (ok == 0) sk_r46_malloc_check_mode = '\x02';
        }
        if (sk_r46_malloc_check_mode == '\x01') {
            uint64_t *blk = (uint64_t *)((uintptr_t)base + 0xfU & ~0xfULL);
            blk[0] = 0x6adfa8;
            blk[1] = 0;
            *((int *)(blk + 2)) = (((int)base + (int)size) - (int)(uintptr_t)blk) - 0x20;
            *((uint32_t *)((long)blk + 0x14)) = 0;
            out[1] = (uint64_t)blk;
            *((uint32_t *)(out + 2)) = 1;
        }
    }
    return out;
}

/* FUN_004ba704 @ 0x004ba704   (est. sk_r46_allocator_image_alloc)
 * Ghidra: void FUN_004ba704(undefined8 *param_1)
 * Under the critical lock allocates a 0x200-byte image structure at 0x6c0c88 and
 * registers a destructor for it, then stores the pointer into *param_1.
 * Confidence: low
 * Notes: DAT_006c0c80 lock; blk 0x6c0c88/0x6c0ca0; LAB_0040bdcc destructor */
void sk_r46_allocator_image_alloc(uint64_t *out)
{
    if (FUN_004b8898((void *)0x6c0c80) != 0) {
        sk_r46_allocator_stack_alloc_sized((uint64_t *)0x6c0c88, 0x6c0ca0, 0x200);
        FUN_00118c64((void *)0x40bdcc, 0x6c0c88, 0); /* destructor LAB_0040bdcc */
        FUN_004b895c((void *)0x6c0c80);
    }
    *out = 0x6c0c88;
}

/* FUN_004ba780 @ 0x004ba780   (est. sk_r46_allocator_stack_free)
 * Ghidra: void FUN_004ba780(undefined8 param_1)
 * Frees a stack-allocated pointer; in malloc-check mode verifies it is the most
 * recently allocated block ("freed pointer was not the last allocation") then
 * releases it.
 * Confidence: medium
 * Notes: string s_freed_pointer_was_not_the_last_a_005dc9a8; thunk_FUN_00012568 */
void sk_r46_allocator_stack_free(uint64_t p)
{
    if (sk_r46_malloc_check_mode == '\0') {
        int ok = (int)FUN_00369818();
        sk_r46_malloc_check_mode = '\x01';
        if (ok == 0) sk_r46_malloc_check_mode = '\x02';
    }
    if (sk_r46_malloc_check_mode == '\x01') {
        /* "freed pointer was not the last allocation" @ 0x5dc9a8 - fatal */
        sk_r46_fatal_error_report(0x5dc9a8);
        FUN_00116d60(); /* fatal */
    }
    thunk_FUN_00012568(p);
}

/* FUN_004ba7ec @ 0x004ba7ec   (est. sk_r46_fatal_unhandled_2)
 * Ghidra: void FUN_004ba7ec(void)
 * Reports an unhandled fatal condition: prints the crash context (FUN_0040f620),
 * builds a 0x58-byte message around FUN_0067f578, raises it with a debug assert
 * and terminates.
 * Confidence: low
 * Notes: FUN_0067f578 tag fn; FUN_00369b04(1,...) */
void sk_r46_fatal_unhandled_2(void)
{
    sk_r46_fatal_unhandled_1();
    uint64_t ctx;
    FUN_0040f620(&ctx);
    if (FUN_00369b0c() != 0) {
        char msg[88];
        FUN_00117cc4(msg, (void *)FUN_0067f578, 0x58);
        FUN_00369b04(1, ctx, msg);
    }
    FUN_0011883c(ctx, 0xeb1a02bf914012ba);
    FUN_0011858c(0xeb1a02bf914012ba);
    thunk_FUN_00012568(ctx);
    FUN_00116d60(); /* fatal */
}

/* FUN_004ba800 @ 0x004ba800   (est. sk_r46_fatal_unhandled_1)
 * Ghidra: void FUN_004ba800(void)
 * Reports an unhandled fatal condition (see FUN_004ba7ec).
 * Confidence: low
 * Notes: FUN_0067f578 tag fn */
void sk_r46_fatal_unhandled_1(void)
{
    uint64_t ctx;
    FUN_0040f620(&ctx);
    if (FUN_00369b0c() != 0) {
        char msg[88];
        FUN_00117cc4(msg, (void *)FUN_0067f578, 0x58);
        FUN_00369b04(1, ctx, msg);
    }
    FUN_0011883c(ctx, 0xeb1a02bf914012ba);
    FUN_0011858c(0xeb1a02bf914012ba);
    thunk_FUN_00012568(ctx);
    FUN_00116d60(); /* fatal */
}

/* FUN_004ba880 @ 0x004ba880   (est. sk_r46_unhandled_trap_0)
 * Ghidra: void FUN_004ba880(void)
 * Routes to the unhandled-trap handler (FUN_004080b0) then traps.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x4ba898) */
void sk_r46_unhandled_trap_0(void)
{
    FUN_004080b0();
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba898) */
}

/* FUN_004ba898 @ 0x004ba898   (est. sk_r46_unhandled_trap_1)
 * Ghidra: void FUN_004ba898(void)
 * Fatal trap chain: enters the trap (FUN_004ba880), prepares runtime state
 * (FUN_004b5a74), then traps via FUN_001a84f4.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x4ba8d4) */
void sk_r46_unhandled_trap_1(void)
{
    sk_r46_unhandled_trap_0();
    FUN_004b5a74();
    char buf[72];
    FUN_001a84f4(buf);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba8d4) */
}

/* FUN_004ba89c @ 0x004ba89c   (est. sk_r46_unhandled_trap_1_dup)
 * Ghidra: void FUN_004ba89c(void)
 * Duplicate of FUN_004ba898 (same trap chain).
 * Confidence: low */
void sk_r46_unhandled_trap_1_dup(void)
{
    sk_r46_unhandled_trap_0();
    FUN_004b5a74();
    char buf[72];
    FUN_001a84f4(buf);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba8d4) */
}

/* FUN_004ba8ac @ 0x004ba8ac   (est. sk_r46_unhandled_trap_2)
 * Ghidra: void FUN_004ba8ac(void)
 * Trap chain without the unhandled-trap prelude: runtime state + trap.
 * Confidence: low */
void sk_r46_unhandled_trap_2(void)
{
    FUN_004b5a74();
    char buf[72];
    FUN_001a84f4(buf);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba8d4) */
}

/* FUN_004ba8b8 @ 0x004ba8b8   (est. sk_r46_unhandled_trap_3)
 * Ghidra: void FUN_004ba8b8(void)
 * Final trap leaf: traps via FUN_001a84f4.
 * Confidence: low */
void sk_r46_unhandled_trap_3(void)
{
    char buf[72];
    FUN_001a84f4(buf);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba8d4) */
}

/* FUN_004ba8d4 @ 0x004ba8d4   (est. sk_r46_tb_fatal_invalid_result_0)
 * Ghidra: void FUN_004ba8d4(void)
 * TB_FATAL: prints "invalid result returned ..." (0x5cad83) and traps.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4ba904) */
void sk_r46_tb_fatal_invalid_result_0(void)
{
    FUN_00118b28((void *)0x5cad83);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba904) */
}

/* FUN_004ba904 @ 0x004ba904   (est. sk_r46_tb_fatal_invalid_result_1)
 * Ghidra: void FUN_004ba904(void)
 * TB_FATAL: prints "invalid result returned ..." (0x5cacd6) and traps.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4ba934) */
void sk_r46_tb_fatal_invalid_result_1(void)
{
    FUN_00118b28((void *)0x5cacd6);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba934) */
}

/* FUN_004ba934 @ 0x004ba934   (est. sk_r46_tb_fatal_invalid_result_2)
 * Ghidra: void FUN_004ba934(void)
 * TB_FATAL: prints "TB_FATAL: invalid result returned ..." (0x5e3e8f) and traps.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4ba964) */
void sk_r46_tb_fatal_invalid_result_2(void)
{
    FUN_00118b28((void *)0x5e3e8f);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba964) */
}

/* FUN_004ba964 @ 0x004ba964   (est. sk_r46_tb_fatal_invalid_result_3)
 * Ghidra: void FUN_004ba964(void)
 * TB_FATAL: prints "TB_FATAL: invalid result returned ..." (0x5e3ecd) and traps.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4ba994) */
void sk_r46_tb_fatal_invalid_result_3(void)
{
    FUN_00118b28((void *)0x5e3ecd);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba994) */
}

/* FUN_004ba994 @ 0x004ba994   (est. sk_r46_tb_fatal_invalid_result_4)
 * Ghidra: void FUN_004ba994(void)
 * TB_FATAL: prints "TB_FATAL: invalid result returned ..." (0x5e3f0d) and traps.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4ba9c4) */
void sk_r46_tb_fatal_invalid_result_4(void)
{
    FUN_00118b28((void *)0x5e3f0d);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba9c4) */
}

/* FUN_004ba9c4 @ 0x004ba9c4   (est. sk_r46_tb_fatal_invalid_result_5)
 * Ghidra: void FUN_004ba9c4(void)
 * TB_FATAL: prints "TB_FATAL: invalid result returned ..." (0x5e3f48) and traps.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(1,0x4ba9f4) */
void sk_r46_tb_fatal_invalid_result_5(void)
{
    FUN_00118b28((void *)0x5e3f48);
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(1,0x4ba9f4) */
}

/* FUN_004baa58 @ 0x004baa58   (est. sk_r46_alloc_atomically_loop)
 * Ghidra: void FUN_004baa58(ulong param_1)
 * Retry loop for an atomic allocation of at least 1 element: repeatedly attempts
 * the allocation (FUN_000101a0 with an 0xc0000000000-flavoured capability tag);
 * while it fails and a runtime hook (FUN_00111854) is installed, invokes the hook
 * and retries.
 * Confidence: low
 * Notes: unaff_x30 spill; unreachable block 0x4baadc removed by decompiler */
void sk_r46_alloc_atomically_loop(uint64_t count)
{
    if (count < 2) count = 1;
    for (;;) {
        long rc = FUN_000101a0(count, 0xc0000000000);
        if (rc != 0) break;
        void *hook = (void *)FUN_00111854();
        if (hook == 0) break;
        ((sk_fp_t)hook)();
    }
}

/* FUN_004baaec @ 0x004baaec   (est. sk_r46_alloc_atomically_loop_2)
 * Ghidra: void FUN_004baaec(ulong param_1)
 * Duplicate retry loop of FUN_004baa58.
 * Confidence: low
 * Notes: unreachable block 0x4bab70 removed */
void sk_r46_alloc_atomically_loop_2(uint64_t count)
{
    if (count < 2) count = 1;
    for (;;) {
        long rc = FUN_000101a0(count, 0xc0000000000);
        if (rc != 0) break;
        void *hook = (void *)FUN_00111854();
        if (hook == 0) break;
        ((sk_fp_t)hook)();
    }
}

/* FUN_004bab7c @ 0x004bab7c   (est. sk_r46_alloc_bad_alloc_throw)
 * Ghidra: void FUN_004bab7c(ulong param_1, ulong param_2)
 * Aligned allocation: rounds count up to 1 and alignment to 8, aligns the size,
 * then retries via FUN_000124a4 while the runtime hook runs. On persistent
 * failure aborts with "bad_alloc was thrown in -fno-exceptions mode".
 * Confidence: medium
 * Notes: string s_bad_alloc_was_thrown_in__fno_exc_005c7a0c */
void sk_r46_alloc_bad_alloc_throw(uint64_t count, uint64_t align)
{
    if (count < 2) count = 1;
    if (align < 9) align = 8;
    uint64_t size = (count + align - 1) & -align;
    if (count <= size) count = size;
    for (;;) {
        if (FUN_000124a4(align, count) != 0) return;
        void *hook = (void *)FUN_00111854();
        if (hook == 0) break;
        ((sk_fp_t)hook)();
    }
    FUN_004b89f8((void *)0x5c7a0c); /* "bad_alloc was thrown in -fno-exceptions mode" */
}

/* FUN_004babf4 @ 0x004babf4   (est. sk_r46_alloc_bad_alloc_quiet)
 * Ghidra: void FUN_004babf4(ulong param_1, ulong param_2)
 * Aligned allocation retry loop that returns silently (no bad_alloc abort) on
 * persistent failure. Same alignment/rounding as FUN_004bab7c.
 * Confidence: medium
 * Notes: unreachable block 0x4bac8c removed */
void sk_r46_alloc_bad_alloc_quiet(uint64_t count, uint64_t align)
{
    if (count < 2) count = 1;
    if (align < 9) align = 8;
    uint64_t size = (count + align - 1) & -align;
    if (count <= size) count = size;
    for (;;) {
        long rc = FUN_000124a4(align, count);
        if (rc != 0) return;
        void *hook = (void *)FUN_00111854();
        if (hook == 0) return;
        ((sk_fp_t)hook)();
    }
}

/* FUN_004bac9c @ 0x004bac9c   (est. sk_r46_alloc_bad_alloc_quiet_2)
 * Ghidra: void FUN_004bac9c(ulong param_1, ulong param_2)
 * Duplicate quiet aligned-allocation retry loop of FUN_004babf4.
 * Confidence: medium
 * Notes: unreachable block 0x4bad34 removed */
void sk_r46_alloc_bad_alloc_quiet_2(uint64_t count, uint64_t align)
{
    if (count < 2) count = 1;
    if (align < 9) align = 8;
    uint64_t size = (count + align - 1) & -align;
    if (count <= size) count = size;
    for (;;) {
        long rc = FUN_000124a4(align, count);
        if (rc != 0) return;
        void *hook = (void *)FUN_00111854();
        if (hook == 0) return;
        ((sk_fp_t)hook)();
    }
}
/* ================================================================== *
 * Part 2 — 0x5d0b20-0x60e40c data regions and the 0x64 L4 IPC glue.
 * ================================================================== */

/* Binary globals used by the L4 IPC / prespecialization runtime. The
 * `_DAT_`/`DAT_` Ghidra names are ground truth; descriptive aliases below. */
extern uint64_t sk_r46_cookie;              /* _DAT_006b5ed0 stack cookie       */
extern uint64_t sk_r46_prespec0_sz;         /* _DAT_006b72b0                    */
extern uint64_t sk_r46_prespec1_sz;         /* _DAT_006b7290                    */
extern uint32_t *sk_r46_p0;                 /* _DAT_006b72c0                    */
extern uint32_t *sk_r46_p1;                 /* _DAT_006b72c8                    */
extern uint32_t *sk_r46_p2;                 /* _DAT_006b72d0                    */
extern uint8_t  sk_r46_pflag;               /* DAT_006b72d8                     */
extern uint64_t sk_r46_w0;                  /* _DAT_006b7350                    */
extern uint64_t sk_r46_w1;                  /* _DAT_006b7358                    */
extern uint64_t sk_r46_w2;                  /* _DAT_006b7360                    */
extern uint64_t sk_r46_w3;                  /* _DAT_006b7364                    */
extern uint64_t sk_r46_w4;                  /* _DAT_006b7368                    */
extern uint64_t sk_r46_w5;                  /* _DAT_006b736c                    */
extern int      sk_r46_done;                /* _DAT_006b7374                    */
extern int      sk_r46_seq;                 /* _DAT_006b7378                    */
extern uint64_t sk_r46_seqbuf;              /* _DAT_006b737c                    */
extern uint64_t sk_r46_sz0;                 /* _DAT_006b4008                    */
extern uint8_t *sk_r46_sz0p;                /* _DAT_006b4010                    */
extern int      sk_r46_mode;                /* _DAT_006b4180                    */
extern uint32_t *sk_r46_img;                /* _DAT_006b4290                    */
extern uint8_t *sk_r46_e0;                  /* _DAT_006b72e0                    */
extern uint8_t *sk_r46_e1;                  /* _DAT_006b72e8                    */
extern uint8_t *sk_r46_e2;                  /* _DAT_006b72f0                    */
extern uint64_t sk_r46_c0;                  /* _DAT_006b7328                    */
extern uint64_t sk_r46_c1;                  /* _DAT_006b7330                    */
extern uint64_t sk_r46_c2;                  /* _DAT_006b7338                    */
extern uint64_t sk_r46_c3;                  /* _DAT_006b7340                    */
extern uint64_t sk_r46_c4;                  /* _DAT_006b7348                    */
extern uint64_t sk_r46_c5;                  /* _DAT_006b7318                    */
extern uint64_t *sk_r46_taglist;            /* _DAT_006b5ed8                    */
extern uint64_t sk_r46_ctx_1d0;             /* _DAT_006881d0                    */
extern uint64_t sk_r46_ctx_1d8;             /* _DAT_006881d8                    */
extern uint64_t sk_r46_ctx_1e0;             /* _DAT_006881e0                    */
extern uint64_t sk_r46_ctx_1e8;             /* _DAT_006881e8                    */
extern uint64_t sk_r46_ctx_1f0;             /* _DAT_006881f0                    */
extern uint64_t sk_r46_ctx_1f8;             /* _DAT_006881f8                    */
extern uint64_t sk_r46_ctx_200;             /* _DAT_00688200                    */
extern uint64_t sk_r46_ctx_208;             /* _DAT_00688208                    */
extern uint64_t sk_r46_ctx_1c0;             /* _DAT_006881c0                    */
extern uint64_t sk_r46_ctx_1c8;             /* _DAT_006881c8                    */
extern int      sk_r46_cache_count;         /* _DAT_006bb418                   */

/* Accessors for the record-layout table at 0x6b5f28 (stride 0x30: {size, fn, fn}). */
#define SK_TBL_SIZE(i)   (*(uint64_t *)((uintptr_t)0x6b5f28 + (uint64_t)(i) * 0x30))
#define SK_TBL_FN0(i)    (*(uint64_t *)((uintptr_t)0x6b5f30 + (uint64_t)(i) * 0x30))
#define SK_TBL_FN1(i)    (*(uint64_t *)((uintptr_t)0x6b5f38 + (uint64_t)(i) * 0x30))
/* Forward declarations for sk_r46_* helpers defined later in this file. */
uint64_t sk_r46_metadata_section_find(uint64_t, uint64_t, uint64_t, uint64_t *);
uint64_t sk_r46_metadata_section_scan(uint64_t, uint64_t, uint64_t, uint64_t);
void sk_r46_page_map_desc(long *, long, long, long, long);
long sk_r46_page_map_desc_inplace(uint64_t *, uint64_t);
void sk_r46_allocator_reset(void);
uint16_t *sk_r46_record_iter_next(long *);
uint32_t sk_r46_record_kind(uint16_t *);
uint64_t sk_r46_record_count(uint16_t *);
long sk_r46_metadata_record_element(uint16_t *, uint64_t);
long sk_r46_metadata_record_base(long *, uint64_t);
long sk_r46_l4_call_prim(uint64_t, uint64_t, uint64_t, uint64_t *, long, uint64_t, uint64_t *, uint64_t);
void sk_r46_l4_signal(uint64_t, uint64_t, uint64_t);
void sk_r46_l4_error_string(uint64_t *, uint8_t);
void sk_r46_l4_error_print(uint64_t, uint64_t);
void sk_r46_l4_ipc_receive(uint64_t *, int);
void sk_r46_l4_ipc_fill(uint64_t, uint64_t *);
long sk_r46_l4_ipc_call(uint64_t, uint64_t, uint64_t *);
void *sk_r46_image_state_get(void);
void *sk_r46_image_state_bounds(void);
sk_pair_t sk_r46_metadata_record_register(uint64_t, long, uint32_t, uint8_t);
void sk_r46_record_element_visit(uint64_t *, uint64_t);
void sk_r46_image_register_cb(uint64_t *);


/* ------------------------------------------------------------------ *
 * 0x5d0b20 / 0x60e3fc / 0x60e40c / 0x610504 / 0x64696c — not real code:
 * Ghidra decoded bad/uninitialised instruction data at these addresses.
 * ------------------------------------------------------------------ */

/* FUN_005d0b20 @ 0x005d0b20   (est. sk_r46_baddata_005d0b20)
 * Ghidra: void FUN_005d0b20(void) { halt_baddata(); }
 * Not a real function: the decompiler hit bad instruction data and truncated
 * control flow. This is a data region, not code.
 * Confidence: low (not real code) */
void sk_r46_baddata_005d0b20(void)
{
    __builtin_unreachable(); /* decompiler: halt_baddata() - bad instruction data */
}

/* FUN_0060e3fc @ 0x0060e3fc   (est. sk_r46_baddata_0060e3fc)
 * Ghidra: void FUN_0060e3fc(void) { halt_baddata(); }
 * Data region mis-decoded as a function; not real code.
 * Confidence: low (not real code) */
void sk_r46_baddata_0060e3fc(void)
{
    __builtin_unreachable(); /* decompiler: halt_baddata() - bad instruction data */
}

/* FUN_0060e40c @ 0x0060e40c   (est. sk_r46_sve_instruction_0060e40c)
 * Ghidra: void FUN_0060e40c(void)
 * A single SVE SDOT instruction (in_z7 = SVE_sdot(in_z7,in_z0,in_z12)) followed by
 * an undefined-instruction trap — an SVE preempt/undef path.
 * Confidence: low
 * Notes: UndefinedInstructionException(0,0x60e410) */
void sk_r46_sve_instruction_0060e40c(void)
{
    /* SVE_sdot(z7, z0, z12) then UndefinedInstructionException(0,0x60e410) */
    __asm__ volatile("sdot z7.s, z0.s, z12.s");
    __builtin_unreachable(); /* trap: UndefinedInstructionException(0,0x60e410) */
}

/* FUN_00610504 @ 0x00610504   (est. sk_r46_baddata_00610504)
 * Ghidra: void FUN_00610504(void) { halt_baddata(); }
 * Data region mis-decoded as a function; not real code.
 * Confidence: low (not real code) */
void sk_r46_baddata_00610504(void)
{
    __builtin_unreachable(); /* decompiler: halt_baddata() - bad instruction data */
}

/* FUN_0064696c @ 0x0064696c   (est. sk_r46_undef_instruction_0064696c)
 * Ghidra: void FUN_0064696c(void)
 * A single undefined-instruction trap (UndefinedInstructionException(0x26e4,0x64696c)).
 * Likely a deliberately placed undef / single-instruction data block.
 * Confidence: low */
void sk_r46_undef_instruction_0064696c(void)
{
    __builtin_unreachable(); /* trap: UndefinedInstructionException(0x26e4,0x64696c) */
}

/* ------------------------------------------------------------------ *
 * 0x64cbc0 — the prespecialization loader.  Walks the cL4 kernel's
 * "Prespecializations" metadata (the pre-instantiated generic-type records),
 * instantiates their type metadata into a fresh image, binds the metadata
 * through the L4 IPC interface (CallSupervisor), and publishes the resulting
 * metadata so the Swift runtime can use it.  Large, intricate boot-path
 * function; transcribed faithfully at statement level.
 * ------------------------------------------------------------------ */

/* FUN_0064cbc0 @ 0x0064cbc0   (est. sk_r46_prespecializations_load)
 * Ghidra: undefined8 FUN_0064cbc0(void)
 * Loads and instantiates the kernel's prespecialized generic metadata: iterates
 * the metadata section list, counts/collects the type records, maps pages via
 * CallSupervisor for the new image, binds the metadata records, and reports the
 * instantiated types back through the runtime. Returns 0 on success.
 * Confidence: low (very large, many opaque runtime hooks)
 * Notes: WARNING "Type propagation algorithm not settling"; globals overlap */
uint64_t sk_r46_prespecializations_load(void)
{
    uint64_t cookie = sk_r46_cookie;
    FUN_0067d798(0x6a4cda);
    if ((int)FUN_00656a30() < 3) {
        goto cbc0_short;
    }
    {
        uint64_t *img = 0;
        if (FUN_00682804(&img) == 0) goto cbc0_short;
        uint64_t meta_lo = 0, meta_hi = 0;
        if (FUN_00682944(img[0], img[1], &meta_lo) == 0) goto cbc0_short;
        if (sk_r46_metadata_section_scan(meta_lo, 0, 0x6a459e, 0x11) == 0) {
            sk_pair_t rec = { 0, 0 };
            uint64_t out = 0;
            if (((sk_r46_metadata_section_find(meta_lo, 0, 0x6a4590, &rec) & 1) == 0) ||
                FUN_00682ec8(rec.lo, rec.hi, 0x6a459a, &out, 0) == 0)
                goto cbc0_short;
        } else {
            FUN_0067d798(0x6a4d1e);
        }
        FUN_0067d798(0x6a4d04);
        FUN_0067d798(0x6a4d67);
        /* Count the prespecialization records in the metadata list. */
        uint64_t *node = (uint64_t *)FUN_00654d4c();
        uint32_t seen = 0;
        if (node != (uint64_t *)-1) {
            uint32_t idx = 0;
            do {
                if (node + 0x800 < node) goto cbc0_trap;
                if (*node != 0) {
                    uint32_t j = 0;
                    uint64_t *r = node + 4;
                    do {
                        if ((r != 0) && ((r < node + 4 || node + 0x800 < r + 4) || r + 4 < r))
                            goto cbc0_trap;
                        if (*(char *)((long)r + 7) == '\x03') {
                            uint64_t sz1 = (r[1] & 0xfffffffffff) * 0x1000;
                            uint64_t sz2 = (r[2] & 0xfffffffffff) * 0x1000;
                            if (seen == 1) {
                                FUN_0067d72c(0x6a471c);
                                sk_r46_page_map_desc((long *)0x6b72a0, *r & 0xffffffffffffff, sz1, sz2, 0);
                                if (sk_r46_prespec0_sz != 0x4000) goto cbc0_trap;
                                seen = 2;
                            } else {
                                if (seen != 0) goto cbc0_collect;
                                FUN_0067d72c(0x6a45d7);
                                sk_r46_page_map_desc((long *)0x6b7280, *r & 0xffffffffffffff, sz1, sz2, 1);
                                seen = 1;
                                if (sk_r46_prespec1_sz != 0x4000) goto cbc0_trap;
                            }
                        }
                        j++;
                        r += 4;
                    } while (j < *node);
                    if (1 < seen) break;
                }
                node = (uint64_t *)node[1];
            } while (node != (uint64_t *)-1);
        }
cbc0_collect:
        if (sk_r46_prespec0_sz == 0) {
            FUN_00683700();
            FUN_006836d8();
            FUN_006834f0();
            FUN_0065558c();
        }
        if (sk_r46_prespec1_sz == 0) {
            FUN_00683700();
            FUN_006836d8();
            FUN_006834f0();
            FUN_0065558c();
        }
        FUN_0067d798(0x6a4d84);
        if (sk_r46_mode != 0) {
            uint64_t *img2 = 0;
            if (FUN_00682804(&img2) != 0) {
                uint64_t meta2_lo = 0, meta2_hi = 0;
                if (((FUN_00682944(img2[0], img2[1], &meta2_lo) & 1) != 0) &&
                    sk_r46_metadata_section_scan(meta2_lo, 0, 0x6a4856, 6) != 0) {
                    FUN_0067d798(0x6a4d9e);
                    goto cbc0_bind;
                }
            }
            uint64_t flags = (uint64_t)FUN_0065684c();
            if (((flags - 1U) < 9) && ((1ULL << (flags & 0x3f) & 0x1d9U) != 0)) {
                if (sk_r46_mode == 1) {
                    if (sk_r46_sz0 >= 0x2001) {
                        sk_r46_p0 = (uint32_t *)(sk_r46_sz0p + 0x2000);
                        sk_r46_p1 = (uint32_t *)((uintptr_t)sk_r46_p0 + (sk_r46_sz0 - 0x2000));
                        sk_r46_p2 = sk_r46_p0;
                        if (sk_r46_p0 != 0) {
                            sk_r46_pflag = '\x01';
                            goto cbc0_bind;
                        }
                    }
                    FUN_00683454();
                    FUN_0068347c();
                    FUN_006834a4();
                } else {
                    FUN_00683454();
                    FUN_0068347c();
                    FUN_006834a4();
                }
            }
            /* Map/bind the prespecialization pages through the L4 IPC interface. */
            sk_pair_t st = FUN_006834cc();
            int seq = sk_r46_seq;
            uint8_t *b2 = (uint8_t *)sk_r46_c4;
            uint8_t *b1 = (uint8_t *)sk_r46_c3;
            uint8_t *b0 = (uint8_t *)sk_r46_c2;
            uint64_t st0 = st.lo;
            if (st0 < 2) {
                if (st0 == 0) {
                    if ((((sk_r46_done & 1) == 0) &&
                         (int *)(uintptr_t)FUN_0065be40() != 0 &&
                         (sk_r46_p2 != 0) && (sk_r46_p1 != 0) && (sk_r46_p0 != 0)) &&
                        (seq == *(int *)(uintptr_t)FUN_0065be40())) {
                        if (sk_r46_pflag == '\x01') {
                            sk_r46_p0[3] = sk_r46_p0[3] & ~4u;
                            sk_r46_p0[0] = 0;
                            sk_r46_p0[3] = sk_r46_p0[3] | 4;
                        }
                        sk_r46_done = 1;
                        sk_r46_allocator_reset();
                        thunk_FUN_0065564c(&sk_r46_seqbuf, 0xc);
                        uint64_t ctx = (uint64_t)FUN_0067f6d8();
                        FUN_00681c28(ctx, sk_r46_w0, 0x20, sk_r46_img, &sk_r46_seqbuf);
                    }
                } else if (st0 == 1 && sk_r46_done == 1) {
                    /* Map the second prespec region. */
                    uint64_t t = (uint64_t)FUN_0065be40();
                    if (st.hi == *(long *)(t + 0x10)) {
                        if ((uintptr_t)sk_r46_c4 >= (uintptr_t)sk_r46_c2 &&
                            ((uintptr_t)sk_r46_c4 - (uintptr_t)sk_r46_c2) >> 0xe != 0) {
                            sk_r46_seqbuf = (uint64_t)sk_r46_seq + 1;
                            sk_r46_seq = (int)sk_r46_seqbuf;
                            thunk_FUN_0067aa00((void *)0x6bb37c, (void *)sk_r46_c2, 0x4000);
                        }
                        if ((uintptr_t)sk_r46_e1 >= (uintptr_t)sk_r46_e0 &&
                            ((uintptr_t)sk_r46_e1 - (uintptr_t)sk_r46_e0) >= 0x4000) {
                            thunk_FUN_0067a780((void *)sk_r46_e0, 0x4000);
                        }
                        FUN_00656c84();
                        uint64_t ctx = (uint64_t)FUN_0067f6d8();
                        FUN_00681d20(ctx, sk_r46_w0, 0x4000, (void *)sk_r46_c2);
                        FUN_00656c84();
                    }
                }
            } else if (st0 == 2) {
                if (sk_r46_done == 1) {
                    uint64_t ctx = (uint64_t)FUN_0067f6d8(0xbad08007);
                    FUN_00681d9c(ctx, sk_r46_w0, 0x10, (void *)0x6b7364);
                    uint8_t *d = sk_r46_e0;
                    if ((uintptr_t)sk_r46_e0 <= (uintptr_t)sk_r46_e1 &&
                        ((uintptr_t)sk_r46_e1 - (uintptr_t)sk_r46_e0) >> 0xe != 0) {
                        thunk_FUN_0067a780(sk_r46_e0, 0x4000);
                        uint64_t a = sk_r46_seqbuf, b = sk_r46_w3, c = sk_r46_w4, d4 = sk_r46_w5;
                        *(uint64_t *)((long)d + 0x14) = d4;
                        *(uint64_t *)((long)d + 0xc) = c;
                        ((uint64_t *)d)[1] = b;
                        ((uint64_t *)d)[0] = a;
                        sk_r46_done = 0;
                        sk_r46_seq = sk_r46_seq + 1;
                        sk_r46_allocator_reset();
                        goto cbc0_done;
                    }
                    goto cbc0_trap;
                }
            } else if (st0 == 3 && (sk_r46_seq + 1) == *(int *)(uintptr_t)FUN_0065be40()) {
                sk_r46_done = 0;
                sk_r46_seq = *(int *)(uintptr_t)FUN_0065be40();
                sk_r46_allocator_reset();
                if (sk_r46_pflag == '\x01') {
                    sk_r46_p0[3] = sk_r46_p0[3] & ~4u;
                }
            }
cbc0_done:
            /* idle loop after the final IPC completion */
            CallSupervisor(0);
            for (;;) {}
        }
cbc0_bind:
        FUN_0067d798(0x6a4dd2);
        uint64_t sz1 = sk_r46_prespec1_sz;
        sk_r46_e0 = (uint8_t *)sk_r46_page_map_desc_inplace((uint64_t *)0x6b7280, sk_r46_prespec1_sz);
        sk_r46_e1 = sk_r46_e0 + sz1;
        sk_r46_e2 = sk_r46_e0;
        FUN_0067d72c(0x6a485d);
        FUN_0067d798(0x6a4df1);
        uint64_t sz0 = sk_r46_prespec0_sz;
        long *base = (long *)sk_r46_page_map_desc_inplace((uint64_t *)0x6b72a0, sk_r46_prespec0_sz);
        if (sz0 < 0x20) goto cbc0_trap;
        sk_r46_img = (uint32_t *)base;
        FUN_0067d72c(0x6a490b);
        /* Bind the metadata through the runtime context's vtable (offset +0x30). */
        {
            sk_pair_t ctx = FUN_0066a8c4();
            char ok = ((sk_fp_t)(ctx.hi + 0x30))(ctx.lo, 0x128, (uint64_t *)0, 0, 0, 0, 0, 0, base);
            if (ok != '\0') { FUN_006834f0(); FUN_0065558c(); }
        }
        /* Walk and instantiate each prespecialization record. */
        uint64_t mrec[2] = { 0, 0 };
        uint64_t total = (uint64_t)sk_r46_record_iter_next((long *)mrec);
        while (total != 0) {
            uint64_t count = *(uint64_t *)(total + 4);
            uint32_t kind = (uint32_t)sk_r46_record_kind((uint16_t *)total);
            uint64_t n = (uint64_t)sk_r46_record_count((uint16_t *)total);
            FUN_0067d72c(0x6a4a14);
            if (n != 0) {
                uint64_t i = 0;
                do {
                    uint64_t *rec = (uint64_t *)sk_r46_metadata_record_element((uint16_t *)total, i);
                    int cnt = *(int *)((long)&mrec + (uint64_t)kind * 4);
                    *(int *)((long)&mrec + (uint64_t)kind * 4) = cnt + 1;
                    if ((int)kind < 0x10) {
                        if ((int)kind < 9) {
                            if (kind == 0) {
                                void *key = (void *)sk_r46_metadata_record_base((long *)sk_r46_ctx_1c0, rec[0x21]);
                                if ((int)thunk_FUN_0067aff0(0x6a4a08, rec + 1, 0x100) != 0) {
                                    FUN_00683930(); FUN_0068342c(); FUN_00683404();
                                }
                                FUN_0067d72c(0x6a4a67);
                            } else if (kind == 6) {
                                sk_r46_metadata_record_base((long *)sk_r46_ctx_1c0, rec[0x22]);
                                if (sk_r46_mode != 1) FUN_006838b8();
                                FUN_0067d72c(0x6a4b19);
                            }
                        } else {
                            if (kind == 9) { FUN_00683840(rec, sk_r46_ctx_1c0); }
                            else if (kind == 0xe) { FUN_006837f0(rec, sk_r46_ctx_1c0); }
                            else if (kind == 0xf) { FUN_0067d72c(0x6a4ba0); }
                        }
                    } else if ((int)kind < 0x19) {
                        if (kind == 0x10) { sk_r46_metadata_record_base((long *)sk_r46_ctx_1c0, rec[0]); FUN_0067d72c(0x6a4bcb); }
                        else if (kind == 0x11) { sk_r46_metadata_record_base((long *)sk_r46_ctx_1c0, rec[0]); FUN_0067d72c(0x6a4bf3); }
                        else { FUN_0067d72c(0x6a4c15); }
                    } else {
                        if (kind == 0x19) { FUN_0067d72c(0x6a4e58); }
                        else if (kind == 0x1c) { FUN_0067d72c(0x6a4e41); }
                        else FUN_0067d72c(0x6a4c15);
                    }
                    i++;
                } while (i != n);
            }
            total = (uint64_t)sk_r46_record_iter_next((long *)mrec);
        }
        /* Publish the collected prespecializations through the L4 IPC interface. */
        uint32_t kind2 = (uint32_t)FUN_00656a14();
        uint64_t *node2 = (uint64_t *)FUN_00654d4c();
        if (node2 != (uint64_t *)-1) {
            uint64_t last = 0;
            do {
                if (node2 + 0x800 < node2) goto cbc0_trap;
                if (*node2 != 0) {
                    uint32_t j = 0;
                    do {
                        uint64_t *r = node2 + 4 + j * 4;
                        if ((r != 0) && ((r < node2 + 4 || node2 + 0x800 < r + 4) || r + 4 < r))
                            goto cbc0_trap;
                        uint64_t val = *r & 0xffffffffffffff;
                        uint8_t tag = (uint8_t)(*r >> 0x38);
                        if (tag < 0x14) {
                            if ((1u << (tag & 0x1f) & 0xa6110U) == 0) {
                                if (tag == 6) {
                                    FUN_00683958(); FUN_00683980();
                                } else if (tag != 0xb) {
                                    FUN_0067d72c(0x6a4c9e);
                                    j++;
                                    continue;
                                } else {
                                    last = val;
                                }
                            }
                        } else if (tag == 3) {
                            uint64_t t2;
                            for (t2 = 0; t2 < 0x18; t2 += 8) {
                                if (val == **((uint64_t **)(t2 + (uintptr_t)sk_r46_taglist))) break;
                            }
                            CallSupervisor(4);
                        } else if (tag == 0) {
                            CallSupervisor(4);
                        } else if (kind2 != tag) {
                            FUN_006833d4(0x6a4c75);
                        } else {
                            CallSupervisor(4);
                        }
                        FUN_0067d72c(0x6a4c9e);
                        j++;
                    } while (j < *node2);
                }
                node2 = (uint64_t *)node2[1];
            } while (node2 != (uint64_t *)-1);
        }
        if (sk_r46_cookie == cookie) return 0;
        FUN_0067f660();
    }
cbc0_short:
    FUN_0067d798(0x6a4ce9);
    if (sk_r46_cookie == cookie) return 0;
    FUN_0067f660();
cbc0_trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x64d7a0) */
}
/* ================================================================== *
 * Part 3 — 0x64dc94-0x64fec8 L4 IPC primitives + metadata iteration.
 * ================================================================== */

extern long FUN_00656c84();   /* runtime cleanup after IPC bind      */

/* Additional binary globals used here (Ghidra _DAT_/DAT_ names ground truth). */
extern uint64_t sk_r46_imglo;    /* _DAT_006fec50                        */
extern uint64_t sk_r46_imghi;    /* _DAT_006fec58                        */
extern uint64_t sk_r46_curcpu;   /* _DAT_006fec98                        */
extern uint64_t sk_r46_dataslide;/* _DAT_006fec88                        */
extern uint8_t  sk_r46_imgflag;  /* DAT_006fec90                         */
extern uint64_t sk_r46_base;     /* _DAT_006b6bb8                        */
extern uint64_t sk_r46_l4e_0;    /* _DAT_00688358                        */
extern uint64_t sk_r46_l4e_1;    /* _DAT_00688368                        */
extern uint64_t sk_r46_l4e_2;    /* _DAT_00688370                        */
extern uint64_t sk_r46_reg0;     /* _DAT_006bb3d0                        */
extern uint64_t sk_r46_reg1;     /* _DAT_006bb3d8                        */
extern uint8_t  sk_r46_v_6cc1;   /* DAT_006b6cc1                         */
extern uint8_t  sk_r46_v_6cc2;   /* DAT_006b6cc2                         */
extern uint16_t sk_r46_v_6cbf;   /* _DAT_006b6cbf                        */
extern uint16_t sk_r46_v_6cc3;   /* _DAT_006b6cc3                        */
extern uint8_t  sk_r46_v_6cc5;   /* DAT_006b6cc5                         */
extern uint8_t  sk_r46_v_6cc6;   /* DAT_006b6cc6                         */

/* The L4 IPC message buffer (the code writes tpidrro_el0 then traps). */
#define SK_MSG_STORE(buf, off, val)  do { (buf)[(off)] = (uint8_t)(val); } while (0)

/* FUN_0064dc94 @ 0x0064dc94   (est. sk_r46_metadata_section_find)
 * Ghidra: undefined8 sk_r46_metadata_section_find(undefined8 param_1, undefined8 param_2,
 *                                  undefined8 param_3, undefined8 *param_4)
 * Walks the metadata section list starting at {param_1,param_2} looking for a
 * section whose name compares equal to param_3; on a match returns nonzero and
 * stores the section base into *param_4.
 * Confidence: medium
 * Notes: uses FUN_00682b48/6bdc/83024/82bfc/82ec8 iterator */
uint64_t sk_r46_metadata_section_find(uint64_t a, uint64_t b, uint64_t key, uint64_t *out)
{
    uint64_t it = 0;
    if (FUN_00682b48(a, b, &it) != 0) {
        uint64_t st = FUN_00682bdc(&it);
        while ((st & 1) == 0) {
            uint64_t lo = 0, hi = 0;
            if (FUN_00683024(&it, &lo) == 0) return 0;
            uint64_t mlo = 0, mhi = 0;
            uint64_t r = FUN_00682ec8(lo, hi, 0x6a45d2, &mlo, &mhi);
            if ((int)r == 0) return r;
            if ((mhi != 0) && ((int)thunk_FUN_0067aff0(mlo, key) == 0)) {
                out[1] = hi;
                out[0] = lo;
                return r;
            }
            FUN_00682bfc(&it);
            st = FUN_00682bdc(&it);
        }
    }
    return 0;
}

/* FUN_0064dd64 @ 0x0064dd64   (est. sk_r46_metadata_section_scan)
 * Ghidra: ulong sk_r46_metadata_section_scan(undefined8 param_1, undefined8 param_2,
 *                            undefined8 param_3, ulong param_4)
 * Scans the metadata section for a run of at least param_4 bytes whose name
 * prefix matches param_3; returns 1 when a match of exactly the requested size
 * is found.
 * Confidence: medium */
uint64_t sk_r46_metadata_section_scan(uint64_t a, uint64_t b, uint64_t key, uint64_t want)
{
    uint64_t s1 = 0, h1 = 0, s2 = 0, h2 = 0;
    uint64_t r = sk_r46_metadata_section_find(a, b, 0x6a45b0, &s1);
    if ((int)r == 0) return r;
    r = sk_r46_metadata_section_find(s1, h1, 0x6a45b7, &s2);
    if ((int)r == 0) return r;
    uint64_t lo = 0, hi = 0;
    r = FUN_00682ec8(s2, h2, 0x6a45c4, &lo, &hi);
    if ((int)r != 0) {
        uint64_t res = 0;
        if (lo != 0 && hi != 0) {
            uint64_t n = hi - want;
            uint64_t p = lo;
            if (want <= hi) {
                do {
                    int c = (int)thunk_FUN_0067aff0(p, key, want);
                    if (c == 0) return 1;
                    p = p + 1;
                } while (n-- != 0);
            }
        }
        return res;
    }
    return r;
}

/* FUN_0064de38 @ 0x0064de38   (est. sk_r46_page_map_desc)
 * Ghidra: void sk_r46_page_map_desc(long *param_1, long param_2, long param_3,
 *                            long param_4, long param_5)
 * If param_2 is zero, panic. If param_4 is nonzero, fill the descriptor at
 * param_1 with {param_2,param_3,param_4,param_5}. Otherwise map a page via the
 * L4 IPC message buffer (0x11-tagged page-map request, CallSupervisor(0)).
 * Confidence: low
 * Notes: panic helpers FUN_006839a8/d0/f8/83a20/83a48; callbacks via lStack_78 */
void sk_r46_page_map_desc(long *out, long p2, long p3, long p4, long p5)
{
    if (p2 == 0) {
        FUN_006839d0();
    } else if (p4 != 0) {
        out[0] = p2; out[1] = p3; out[2] = p4; out[3] = p5;
        return;
    }
    sk_pair_t ctx = FUN_006839a8();
    uint64_t ctx_lo = ctx.lo, ctx_hi = ctx.hi;
    if (((uint32_t *)ctx.lo)[2] != (uint32_t)ctx.hi) {
        FUN_006839f8();
        FUN_00683a20();
        FUN_00683a48();
        FUN_0065558c();
    }
    if ((ctx.hi & 0x3fff) != 0) {
        FUN_00683a20();
        FUN_00683a48();
        FUN_0065558c();
    }
    uint8_t msg[32];
    SK_MSG_STORE(msg, 0, 0x11);
    uint64_t ctx2 = (uint64_t)FUN_0066a8c4().lo;
    uint64_t cb_ctx = 0, cb_fn = 0;
    uint32_t req = 0x1808;
    if (ctx_lo != 1) req = 0x1800;
    char ok = ((sk_fp_t)(FUN_0066a8c4().hi + 0x30))(FUN_0066a8c4().lo, req, msg, &cb_ctx, 0, 0);
    if (ok == '\0') {
        uint64_t slot = (uint64_t)FUN_0066ad54();
        uint64_t pages = ctx_lo >> 0xe;
        uint64_t i = 0;
        while (i < pages) {
            uint64_t src = ((uint64_t *)ctx.lo)[0];
            uint8_t m[24];
            SK_MSG_STORE(m, 0, 0x11);
            SK_MSG_STORE(m, 8, i << 0xe);
            SK_MSG_STORE(m, 16, slot);
            CallSupervisor(0);
            if (src != 0) {
                FUN_00683a70(src, 0);
                FUN_006839f8(); FUN_00683a20(); FUN_00683a48(); FUN_0065558c();
            }
            if (cb_fn != 0) {
                if (((sk_fp_t)(cb_fn + 0x28))(cb_ctx, i << 0xe, slot) != 0) {
                    FUN_00683a98();
                    FUN_00683a70(src, 0);
                    FUN_006839f8(); FUN_00683a20(); FUN_00683a48(); FUN_0065558c();
                }
            }
            CallSupervisor(4);
            i++;
        }
        FUN_006860f4(slot);
        if (cb_fn != 0) {
            ((sk_fp_t)(cb_fn + 8))(cb_ctx, msg);
            return;
        }
        FUN_0065558c();
    }
    FUN_00683a48();
    FUN_0065558c();
}

/* FUN_0064de64 @ 0x0064de64   (est. sk_r46_page_map_desc_inplace)
 * Ghidra: void sk_r46_page_map_desc_inplace(ulong *param_1, ulong param_2)
 * Maps param_2 bytes worth of pages for the descriptor already stored at
 * param_1 (param_1[2]==param_2). Same 0x11-tagged page-map path as
 * FUN_0064de38 but reading the descriptor fields from *param_1.
 * Confidence: low
 * Notes: panic helpers; lStack_78 callback */
long sk_r46_page_map_desc_inplace(uint64_t *desc, uint64_t size)
{
    if (desc[2] == size) {
        if ((size & 0x3fff) == 0) {
            uint64_t flg = desc[3];
            uint8_t msg[32];
            SK_MSG_STORE(msg, 0, 0x11);
            uint64_t cb_ctx = 0, cb_fn = 0;
            uint32_t req = 0x1808;
            if (flg != 1) req = 0x1800;
            char ok = ((sk_fp_t)(FUN_0066a8c4().hi + 0x30))(FUN_0066a8c4().lo, req, msg, &cb_ctx, 0, 0);
            if (ok == '\0') {
                uint64_t slot = (uint64_t)FUN_0066ad54();
                uint64_t pages = desc[2] >> 0xe;
                uint64_t i = 0;
                while (i < pages) {
                    uint64_t src = desc[0];
                    uint8_t m[24];
                    SK_MSG_STORE(m, 0, 0x11);
                    SK_MSG_STORE(m, 8, i << 0xe);
                    SK_MSG_STORE(m, 16, slot);
                    CallSupervisor(0);
                    if (src != 0) {
                        FUN_00683a70(src, 0);
                        FUN_006839f8(); FUN_00683a20(); FUN_00683a48(); FUN_0065558c();
                    }
                    if (cb_fn != 0) {
                        if (((sk_fp_t)(cb_fn + 0x28))(cb_ctx, i << 0xe, slot) != 0) {
                            FUN_00683a98();
                            FUN_00683a70(src, 0);
                            FUN_006839f8(); FUN_00683a20(); FUN_00683a48(); FUN_0065558c();
                        }
                    }
                    CallSupervisor(4);
                    i++;
                }
                FUN_006860f4(slot);
                if (cb_fn != 0) {
                    ((sk_fp_t)(cb_fn + 8))(cb_ctx, msg);
                    return (long)desc;
                }
                FUN_0065558c();
            }
            FUN_00683a48();
            FUN_0065558c();
        }
        FUN_00683a20();
        FUN_00683a48();
        FUN_0065558c();
    }
    FUN_006839f8();
    FUN_00683a20();
    FUN_00683a48();
    FUN_0065558c();
    return 0;
}

/* FUN_0064dfe4 @ 0x0064dfe4   (est. sk_r46_allocator_reset)
 * Ghidra: void sk_r46_allocator_reset(void)
 * Refreshes the runtime allocator: queries its size and clears the four-word
 * sequence/context header (0x6b7358..). Traps on size overflow.
 * Confidence: low
 * Notes: SoftwareBreakpoint(0x5519,0x64e030) */
void sk_r46_allocator_reset(void)
{
    FUN_0067f6d8();
    uint64_t n = (uint64_t)FUN_00681c20();
    if (sk_r46_w0 <= sk_r46_w0 + n) {
        FUN_00681f44();
        sk_r46_w1 = 0;
        sk_r46_w2 = 0;
        sk_r46_done = 0;
        sk_r46_w4 = 0;
        return;
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x64e030) */
}

/* FUN_0064e030 @ 0x0064e030   (est. sk_r46_panic_6a4605)
 * Ghidra: void FUN_0064e030(undefined8 param_1)
 * Panics with message tag 0x6a4605.
 * Confidence: low */
void sk_r46_panic_6a4605(uint64_t a)
{
    (void)a;
    FUN_006833d4(0x6a4605);
}

/* FUN_0064e044 @ 0x0064e044   (est. sk_r46_image_info_set)
 * Ghidra: undefined1[16] FUN_0064e044(undefined8 param_1, long param_2)
 * Records the global image info {lo,hi}; the first call wins (a second
 * initialisation panics). Returns the recorded pair. Lazily primes the default
 * image info (0x6b6bb8/0x6b4298) when empty.
 * Confidence: low
 * Notes: globals _DAT_006fec50/58; panic FUN_00683ac0/d8 */
sk_pair_t sk_r46_image_info_set(uint64_t lo, long hi)
{
    if (sk_r46_imghi == 0) {
        if (hi != 0) {
            sk_r46_imglo = lo;
            sk_r46_imghi = (uint64_t)hi;
            sk_pair_t r = { lo, (uint64_t)hi };
            return r;
        }
    } else {
        FUN_00683ac0();
    }
    FUN_00683ad8();
    if (sk_r46_imghi == 0) {
        sk_r46_image_info_set(sk_r46_base, 0x6b4298);
    }
    sk_pair_t r = { sk_r46_imglo, sk_r46_imghi };
    return r;
}

/* FUN_0064e07c @ 0x0064e07c   (est. sk_r46_image_info_get)
 * Ghidra: undefined1[16] FUN_0064e07c(void)
 * Returns the recorded global image info, priming the default (0x6b6bb8/0x6b4298)
 * if not yet set.
 * Confidence: low */
sk_pair_t sk_r46_image_info_get(void)
{
    if (sk_r46_imghi == 0) {
        sk_r46_image_info_set(sk_r46_base, 0x6b4298);
    }
    sk_pair_t r = { sk_r46_imglo, sk_r46_imghi };
    return r;
}

/* FUN_0064e0c8 @ 0x0064e0c8   (est. sk_r46_l4_call_receive)
 * Ghidra: long FUN_0064e0c8(undefined8 param_1, ulong param_2, ulong param_3,
 *                            long param_4, ulong param_5)
 * Performs an L4 IPC call+receive. When the target is not a plain receive
 * (flags bit 3 clear) it issues the call via the L4 message buffer and, on
 * success, invokes FUN_0064eaf8. Otherwise uses the per-cpu slot state.
 * Confidence: low
 * Notes: tpidrro_el0 message buffer; FUN_0066469c cpu info; FUN_0065c2f0 fatal */
long sk_r46_l4_call_receive(uint64_t target, uint64_t sel, uint64_t arg, long buf, uint64_t flags)
{
    uint64_t cookie = sk_r46_cookie;
    bool noRet = (flags & 8) == 0;
    bool isPlain = ((int)sel) != 3;
    long out = buf;
    if (!noRet || !isPlain) {
        uint8_t m[32];
        SK_MSG_STORE(m, 8, sel & 0xffffffff);
        SK_MSG_STORE(m, 16, arg >> 6);
        SK_MSG_STORE(m, 24, flags & 0xffffffff);
        long r = sk_r46_l4_call_prim(target, 1, 3, &out, 1, 1, 0, 0);
        if (r == 0 && noRet && isPlain) {
            sk_r46_l4_signal(sel, out, buf);
        }
        return r;
    }
    uint64_t cpu = (uint64_t)FUN_0066469c();
    uint64_t slot = sk_r46_curcpu;
    if (*(long *)(cpu + (slot - 1) * 8 + 0x1f8) == -1) {
        FUN_0065c2f0(0, 0x6a4ef1);
    }
    out = *(long *)((uint8_t *)0 + (slot - 1) * 8 + 0x1f8);
    return sk_r46_l4_call_prim(target, 1, 3, &out, 1, 1, 0, 0);
}

/* FUN_0064e20c @ 0x0064e20c   (est. sk_r46_l4_call_reply)
 * Ghidra: void FUN_0064e20c(undefined8 param_1, undefined8 param_2,
 *                            ulong param_3, ulong param_4)
 * Issues an L4 IPC reply (method 2) with the message buffer arguments.
 * Confidence: low */
void sk_r46_l4_call_reply(uint64_t target, uint64_t a, uint64_t b, uint64_t c)
{
    uint8_t m[32];
    SK_MSG_STORE(m, 8, a);
    SK_MSG_STORE(m, 16, b & 0xffffffff);
    SK_MSG_STORE(m, 24, c >> 6);
    sk_r46_l4_call_prim(target, 2, 3, &c, 1, 1, 0, 0);
}

/* FUN_0064e28c @ 0x0064e28c   (est. sk_r46_l4_call_read)
 * Ghidra: void FUN_0064e28c(undefined8 param_1, ulong param_2, undefined8 *param_3)
 * Issues an L4 IPC read (method 8) and stores the single returned word.
 * Confidence: low */
void sk_r46_l4_call_read(uint64_t target, uint64_t a, uint64_t *out)
{
    uint64_t res = 0;
    uint8_t m[32];
    SK_MSG_STORE(m, 8, a >> 6);
    if (sk_r46_l4_call_prim(target, 8, 1, 0, 0, 1, &res, 1) == 0) {
        *out = res;
    }
}

/* FUN_0064e2f0 @ 0x0064e2f0   (est. sk_r46_l4_call_nothread)
 * Ghidra: void FUN_0064e2f0(undefined8 param_1, undefined8 param_2)
 * Issues an L4 IPC call (method 0x20) with the current thread id.
 * Confidence: low */
void sk_r46_l4_call_nothread(uint64_t a, uint64_t target)
{
    uint64_t tid = (uint64_t)FUN_0065c9fc();
    uint8_t m[32];
    SK_MSG_STORE(m, 8, tid);
    sk_r46_l4_call_prim(target, 0x20, 1, 0, 0, 1, 0, 0);
}

/* FUN_0064e3bc @ 0x0064e3bc   (est. sk_r46_l4_call_6)
 * Ghidra: void FUN_0064e3bc(undefined8 param_1, undefined8 param_2,
 *                            undefined8 param_3, undefined8 param_4)
 * Issues an L4 IPC call (method 2) with one word argument.
 * Confidence: low */
void sk_r46_l4_call_6(uint64_t target, uint64_t a, uint64_t b, uint64_t v)
{
    sk_r46_l4_call_prim(target, 2, 6, &v, 1, 1, 0, 0);
}

/* FUN_0064eaf8 @ 0x0064eaf8   (est. sk_r46_l4_signal)
 * Ghidra: void FUN_0064eaf8(ulong param_1, ulong param_2, ulong param_3)
 * Sends an L4 notification (CallSupervisor(0)) carrying {param_1, param_3}; on a
 * nonzero error status formats and panics.
 * Confidence: low
 * Notes: tpidrro_el0 message buffer; FUN_0064eee8 error->string; FUN_006833d4 */
void sk_r46_l4_signal(uint64_t sel, uint64_t st, uint64_t arg)
{
    uint64_t cookie = sk_r46_cookie;
    uint8_t m[24];
    uint64_t buf[4];
    SK_MSG_STORE(m, 0, sel & 0xffffffff);
    SK_MSG_STORE(m, 8, 0);
    SK_MSG_STORE(m, 16, arg);
    CallSupervisor(0);
    if ((st & 0xff) != 0) {
        sk_r46_l4_error_string(buf, (uint8_t)(st & 0xff));
        FUN_006833d4(0x6a514a);
    }
    FUN_00683b20(st, m, buf);
    if (sk_r46_cookie != cookie) FUN_0067f660();
}

/* FUN_0064eee8 @ 0x0064eee8   (est. sk_r46_l4_error_string)
 * Ghidra: void FUN_0064eee8(undefined8 *param_1, byte param_2)
 * Copies the 32-byte L4 error-code description (e.g. "L4_ErrorCodeSuccess") into
 * the 4-word output; codes above 9 use a generic table entry.
 * Confidence: medium
 * Notes: strings s_L4_ErrorCodeSuccess_00688218 .. _PermissionInvalid_00688338 */
void sk_r46_l4_error_string(uint64_t *out, uint8_t code)
{
    if (9 < code) {
        out[0] = sk_r46_l4e_0; out[1] = sk_r46_l4e_1; out[2] = sk_r46_l4e_2;
        out[3] = sk_r46_l4e_0;
        sk_r46_l4_error_print((uint64_t)out, 0x20);
        return;
    }
    /* Table of 32-byte L4 error descriptions at 0x688218 + code*0x20. */
    const uint8_t *src = (const uint8_t *)(0x688218 + (uint32_t)code * 0x20);
    out[0] = *(uint64_t *)(src);
    out[1] = *(uint64_t *)(src + 8);
    out[2] = *(uint64_t *)(src + 0x10);
    out[3] = *(uint64_t *)(src + 0x18);
}

/* FUN_0064effc @ 0x0064effc   (est. sk_r46_l4_error_print)
 * Ghidra: void FUN_0064effc(undefined8 param_1, undefined8 param_2)
 * Prints a 0x20-byte L4 error description via FUN_0067ca84.
 * Confidence: medium
 * Notes: message tag 0x6a5139 */
void sk_r46_l4_error_print(uint64_t msg, uint64_t len)
{
    FUN_0067ca84(msg, 0x1f, 0, len, 0x6a5139, 0);
}

/* FUN_0064f2bc @ 0x0064f2bc   (est. sk_r46_l4_error_string_copy)
 * Ghidra: void FUN_0064f2bc(undefined8 param_1, byte param_2)
 * Copies the 32-byte L4 error-code description (table at 0x688378) into param_1.
 * Confidence: medium
 * Notes: strings s_L4_ErrorCodeSuccess_00688378 .. _PermissionInvalid_00688498 */
void sk_r46_l4_error_string_copy(uint64_t *out, uint8_t code)
{
    if (9 < code) {
        thunk_FUN_0067aa00(out, (void *)0x6884b8, 0x20);
        sk_r46_l4_error_print((uint64_t)out, 0x20);
        return;
    }
    thunk_FUN_0067aa00(out, (void *)(0x688378 + (uint32_t)code * 0x20), 0x20);
}

/* FUN_0064f3f4 @ 0x0064f3f4   (est. sk_r46_l4_ipc_call)
 * Ghidra: long FUN_0064f3f4(undefined8 param_1, undefined8 param_2, long param_3)
 * Performs an L4 IPC call to endpoint param_1 with the message in param_2; when
 * a reply buffer is supplied (param_3) and the call succeeds, fills it with the
 * reply words (FUN_0064f068).
 * Confidence: low */
long sk_r46_l4_ipc_call(uint64_t endpoint, uint64_t msg, uint64_t *reply)
{
    uint64_t st;
    sk_r46_l4_ipc_receive(&st, 0);
    long rc = FUN_006645ec(endpoint, &st);
    if (reply != 0 && rc == 0) {
        sk_r46_l4_ipc_fill(st, reply);
    }
    return rc;
}

/* FUN_0064f068 @ 0x0064f068   (est. sk_r46_l4_ipc_fill)
 * Ghidra: void FUN_0064f068(undefined8 param_1, undefined2 *param_2)
 * Fills the caller's IPC reply buffer from a received L4 message: copies the
 * count, thread id, cap word and up to the available payload words, trimming to
 * the declared capacity.
 * Confidence: low
 * Notes: FUN_0065fd44/5fc28/5fd3c/5fb08/5fa24 IPC buffer helpers */
void sk_r46_l4_ipc_fill(uint64_t msg, uint64_t *out)
{
    uint64_t cnt = (uint64_t)FUN_0065fd44();
    if (cnt != 0) {
        *out = (uint64_t)FUN_0065fc28(0);
    }
    if (FUN_0065fd3c(msg) != 0) {
        /* thread id + capability bits from the per-cpu msg buffer */
        out[2] = 0;
    }
    if (1 < cnt) {
        out[2] = (uint64_t)FUN_0065fc28(1);
        if (cnt != 2 && *(long *)(out + 3) != 0) {
            uint64_t n = (uint64_t)FUN_0065fc28(2);
            uint64_t cap = cnt * 8 - 0x18;
            if (cap <= n) n = cap;
            if (out[4] <= n) n = out[4];
            FUN_0065fb08(out[3], n, 3);
            uint8_t *p = (uint8_t *)out[3];
            p[n] = 0;
            out[4] = n;
        }
    }
}

/* FUN_0064f194 @ 0x0064f194   (est. sk_r46_l4_ipc_receive)
 * Ghidra: void FUN_0064f194(undefined2 *param_1, int param_2)
 * Receives an L4 IPC reply: resets the message buffer, optionally issues the
 * reply-wait (CallSupervisor(1)), and copies the returned words/cap into the
 * caller's buffer. Returns an L4 error code via the thunk.
 * Confidence: low
 * Notes: CallSupervisor(1); SoftwareBreakpoint(0x5519,0x64f2bc) */
void sk_r46_l4_ipc_receive(uint64_t *out, int flag)
{
    uint64_t cookie = sk_r46_cookie;
    if (flag == 0) {
        FUN_0065fca8(0);
    } else {
        uint64_t u = (uint64_t)FUN_00661318();
        FUN_00664304(u, 0);
        CallSupervisor(1);
    }
    FUN_0065fbb0(0, out[0]);
    FUN_0065fbb0(1, out[2]);
    if (out[3] == 0) {
        /* no payload */
    } else {
        uint64_t n = out[4];
        if (0x1a7 < n) n = 0x1a8;
        FUN_0065fbb0(2, n);
        if (out[4] < n) __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x64f2bc) */
        FUN_0065fa24(out[3], n, 3, 0);
    }
    if (sk_r46_cookie != cookie) FUN_0067f660();
}
/* ================================================================== *
 * Part 4 — 0x64e430-0x64fec8: multi-word IPC, core call primitive,
 * console write, image fixup, metadata iteration.
 * ================================================================== */

/* Per-cpu L4 IPC message buffer words (tpidrro_el0 in the binary). */
static uint64_t sk_r46_msg[8];
static uint64_t sk_r46_msgext[8];

extern char __data[];   /* __DATA segment start (relocation slide anchor) */

/* FUN_0064ebcc @ 0x0064ebcc   (est. sk_r46_l4_call_prim)
 * Ghidra: void FUN_0064ebcc(ulong param_1, ulong param_2, ulong param_3,
 *                            undefined8 *param_4, long param_5, ulong param_6,
 *                            ulong *param_7, ulong param_8)
 * Core L4 IPC call primitive: packs the message descriptor (method<<16 | word
 * count), copies up to param_3 words plus param_5 extended words into the
 * per-cpu message buffer, traps via CallSupervisor(0), and checks the returned
 * status. On failure it formats and panics; on success optionally stores the
 * result words into param_7.  param_8 is the expected result count.
 * Confidence: low
 * Notes: panic tags 0x6a4f8e/0x6a506e/0x6a50e3; tpidrro_el0 message buffer */
long sk_r46_l4_call_prim(uint64_t target, uint64_t method, uint64_t nword,
                         uint64_t *args, long nargs, uint64_t want_result,
                         uint64_t *result, uint64_t nresult)
{
    uint64_t cookie = sk_r46_cookie;
    uint64_t saved[16];
    uint64_t i = 0;
    for (i = 0; i < nword && i < 16; i++) saved[i] = sk_r46_msg[1 + i];
    uint64_t desc = (method << 0x10) | (nword & 0x3f);
    for (;;) {
        for (i = 0; i < nword; i++) sk_r46_msg[1 + i] = saved[i];
        if (nargs != 0) {
            for (i = 0; i < (uint32_t)nargs && i < 8; i++) sk_r46_msgext[i] = args[i];
        }
        sk_r46_msg[0] = desc;
        CallSupervisor(0);
        sk_r46_msg[0] = desc;
        uint64_t st = sk_r46_msg[0];
        if (st != 0) {
            /* error: format the failing call and panic */
            sk_r46_msg[1] = (uint64_t)nresult;   /* result count */
            sk_r46_msg[2] = desc;
            sk_r46_msg[3] = target;
            FUN_006833d4(0x6a506e);
        }
        if (want_result != 0 && result != 0) {
            for (i = 0; i < nresult && i < 8; i++) result[i] = sk_r46_msg[1 + i];
        }
        break;
    }
    if (sk_r46_cookie != cookie) FUN_0067f660();
    return 0;
}

/* FUN_0064e430 @ 0x0064e430   (est. sk_r46_l4_call_multi)
 * Ghidra: void FUN_0064e430(undefined8 param_1, uint param_2, uint param_3,
 *                            ulong param_4, long param_5, long param_6)
 * Allocates up to 4 word-argument slots, fills them via a callback (param_5),
 * issues a multi-word L4 IPC call (method 0xb), and invokes a result callback
 * (param_6) per returned word. Releases the temporary slots afterwards.
 * Confidence: low
 * Notes: FUN_0066469c cpu info; FUN_0066ad54 alloc; panic tags 0x6a4ef1/0x6a4f12 */
void sk_r46_l4_call_multi(uint64_t target, uint32_t method, uint32_t flags,
                          uint64_t narg, long get_arg, long on_result)
{
    uint64_t cookie = sk_r46_cookie;
    uint64_t slots[4];
    uint64_t shifted[4];
    uint64_t vals[4];
    uint64_t results[4];
    uint64_t i;
    uint64_t n = narg;
    if (3 < n) n = 4;
    /* allocate the temporary word slots */
    uint64_t cpu = (uint64_t)FUN_0066469c();
    uint64_t sl = sk_r46_curcpu;
    if (*(long *)(cpu + (sl - 1) * 8 + 0x1f8) == -1) {
        FUN_0065c2f0(0, 0x6a4ef1);
    }
    slots[0] = *(long *)(0 + (sl - 1) * 8 + 0x1f8);
    for (i = 1; i < n; i++) {
        slots[i] = (uint64_t)FUN_0066ad54();
        if (slots[i] == 0) { FUN_00683b08(); FUN_00683af0(); FUN_0067f660(); }
    }
    /* gather and shift the arguments */
    uint64_t done = 0, k = narg;
    do {
        uint64_t m = k;
        if (k < 2) m = 1;
        if (3 < m) m = 4;
        uint64_t to_shift = m;
        uint64_t cnt = k;
        if (k == done) cnt = 0;
        if (cnt != 0) {
            uint64_t vi = 0;
            while (vi < cnt && vi < 4) {
                vals[vi] = ((sk_fp_t)(get_arg + 0x10))(get_arg, done + vi);
                vi++;
            }
            for (vi = 0; vi < cnt && vi < 4; vi++) shifted[vi] = vals[vi] >> 6;
        }
        sk_r46_msg[0] = 0;
        sk_r46_msg[1] = method;
        sk_r46_msg[2] = flags;
        sk_r46_msg[3] = cnt;
        for (i = 0; i < cnt && i < 4; i++) sk_r46_msg[4 + i] = shifted[i];
        long rc = sk_r46_l4_call_prim(target, 0xb, cnt + 3, (uint64_t *)sk_r46_msg, cnt, 0, results, cnt);
        if (rc != 0) { for (i = 0; i < cnt; i++) results[i] = (uint64_t)rc; }
        if (cnt != 0) {
            for (i = 0; i < cnt; i++) {
                uint64_t r = results[i];
                if (r == 0) {
                    sk_r46_l4_signal(method, slots[i], vals[i]);
                }
                if (on_result != 0) {
                    ((sk_fp_t)(on_result + 0x10))(on_result, r, done + i, vals[i]);
                }
            }
        }
        done += 4;
        k = (narg >= 4) ? (narg - done) : 0;
    } while (done < narg);
    /* release the temporary slots */
    for (i = 1; i < n; i++) FUN_006860f4(slots[i]);
    if (sk_r46_cookie != cookie) FUN_0067f660();
}

/* FUN_0064f458 @ 0x0064f458   (est. sk_r46_l4_console_write)
 * Ghidra: long FUN_0064f458(ulong param_1, ulong param_2)
 * Writes param_2 bytes from param_1 to the console via L4 IPC: if the payload
 * fits (param_2 < 0x199) it is sent in one message, otherwise it is chunked in
 * 0x199-byte pieces with an open/close write sequence (tags 0x80/0x81/0x82/0x84).
 * Returns an L4 error code.
 * Confidence: low
 * Notes: endpoint from DAT_006b6cc1..; msg tags 0x80..0x84 */
long sk_r46_l4_console_write(uint64_t buf, uint64_t len)
{
    uint64_t cookie = sk_r46_cookie;
    uint8_t saved[0x1c0];
    thunk_FUN_0067aa00(saved, (void *)sk_r46_msg, 0x1c0);
    uint64_t ep = (uint64_t)sk_r46_v_6cc1 << 0x10 | (uint64_t)sk_r46_v_6cc2 << 0x18 |
                  (uint64_t)sk_r46_v_6cbf |
                  (uint64_t)((uint32_t)sk_r46_v_6cc5 << 0x10 | (uint32_t)sk_r46_v_6cc6 << 0x18 |
                             (uint32_t)sk_r46_v_6cc3) << 0x20;
    long rc;
    if (ep == 0) {
        rc = 4;
    } else if (len < 0x199) {
        uint64_t m[8] = { 0 };
        m[0] = 0x80;               /* write-open tag */
        m[5] = 1;
        m[3] = buf;
        m[4] = len;
        rc = sk_r46_l4_ipc_call(ep, (uint64_t)m, 0);
    } else {
        uint64_t m[8] = { 0 };
        uint64_t m2[8];
        uint64_t rem = len;
        m[0] = 0x83;
        sk_r46_l4_ipc_call(ep, (uint64_t)m, (uint64_t *)&m2);
        uint64_t st = m2[2];
        do {
            uint64_t chunk = rem;
            if (0x197 < chunk) chunk = 0x198;
            uint64_t src = buf + (len - rem);
            uint64_t p = len + buf + 1 - rem;
            while (*((char *)p - 1) != '\0') p++;
            FUN_0067ce74((void *)m, (void *)src, chunk + 1, 0x199);
            uint64_t msg2[8];
            msg2[0] = 0x81;                 /* write-continue tag */
            msg2[1] = st;
            msg2[2] = (uint64_t)sk_r46_msg;
            msg2[3] = (uint64_t)FUN_0067b220((void *)m);
            msg2[4] = 1;
            rc = sk_r46_l4_ipc_call(ep, (uint64_t)msg2, (uint64_t *)&m2);
            rem -= chunk;
        } while (rem != 0 && m2[1] != 0);
        uint64_t close[8] = { 0 };
        close[0] = 0x82;
        close[1] = st;
        rc = sk_r46_l4_ipc_call(ep, (uint64_t)close, 0);
        if (rc != 0) goto done;
        uint64_t close2[8] = { 0 };
        close2[0] = 0x84;
        close2[1] = st;
        rc = sk_r46_l4_ipc_call(ep, (uint64_t)close2, 0);
    }
done:
    thunk_FUN_0067aa00((void *)sk_r46_msg, saved, 0x1c0);
    if (sk_r46_cookie != cookie) FUN_0067f660();
    return rc;
}

/* FUN_0064f7e8 @ 0x0064f7e8   (est. sk_r46_reloc_walk)
 * Ghidra: ulong * FUN_0064f7e8(ulong *param_1, undefined8 param_2, long param_3,
 *                               long param_4, long param_5)
 * Walks a relocation chain anchored at param_1 within a page-aligned region,
 * applying a slide of param_5 to each entry that does not carry the relocation-
 * done tag (bit 0x3e set). Returns the next chain pointer or 0 at chain end.
 * Confidence: medium
 * Notes: reloc tag bit 0x3e; page size 0x800 entries */
uint64_t *sk_r46_reloc_walk(uint64_t *entry, uint64_t base, long stride,
                            long slide_hi, long slide)
{
    uint64_t *page0 = (uint64_t *)((uintptr_t)entry & ~0x3fffULL);
    uint64_t *p = entry;
    uint64_t tag = 0;
    do {
        uint64_t w = *p;
        if ((w >> 0x3e & 1) == 0) {
            uint64_t v;
            if ((long)w < 0) {
                v = (uint64_t)(slide + slide_hi + (w & 0xffffffff));
            } else {
                v = (uint64_t)(slide + ((w >> 0x2b) << 0x38) +
                               ((long)(w << 0x15) >> 0x15 & 0xffffffffffffffU));
            }
            *p = v;
        }
        tag = w >> 0x33 & 0x7ff;
        p = (uint64_t *)((long)p + tag * stride);
    } while (tag != 0 && page0 <= p && p < page0 + 0x800);
    if (tag == 0) p = 0;
    return p;
}

/* FUN_0064f894 @ 0x0064f894   (est. sk_r46_fixup_bind)
 * Ghidra: void FUN_0064f894(uint *param_1, uint *param_2)
 * Binds the fixup chain spanning the uint array [param_1, param_2): for each
 * 4/8-byte entry applies the relocation slide, skipping the special section
 * ranges when the image-flag is set.
 * Confidence: medium
 * Notes: reloc table at __data; SoftwareBreakpoint(0x5519,0x64f9fc) */
void sk_r46_fixup_bind(uint32_t *start, uint32_t *end)
{
    uint32_t *p = start + 1;
    if (p <= end && start <= p) {
        uint64_t step = (*start & 1) ? 8 : 4;
        if (p != end) {
            long slide = (long)((uintptr_t)&__data - sk_r46_dataslide);
            do {
                if (p + 1 < p || end < p + 1) goto f894_trap;
                if (*p == 0xffffffff) return;
                uint8_t *addr = (uint8_t *)((uintptr_t)&__data + *p);
                if (sk_r46_imgflag == '\x01') {
                    /* skip entries inside the two reserved section ranges */
                }
                uint64_t *rel = (uint64_t *)sk_r46_reloc_walk((uint64_t *)addr,
                                 (uint64_t)addr & ~0x3fffULL, step, slide, sk_r46_dataslide);
                while (rel != 0) {
                    rel = (uint64_t *)sk_r46_reloc_walk(rel, (uint64_t)rel & ~0x3fffULL,
                                                        step, slide, sk_r46_dataslide);
                }
                p += (step == 8) ? 2 : 1;
            } while (p != end);
        }
        return;
    }
f894_trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x64f9fc) */
}

/* FUN_0064fa00 @ 0x0064fa00   (est. sk_r46_image_register)
 * Ghidra: void FUN_0064fa00(undefined8 param_1, undefined8 param_2)
 * Registers the image with the runtime (FUN_0065e454) and records the image
 * {lo,hi} pair in the 0x6bb3d0/0x6bb3d8 globals.
 * Confidence: medium */
void sk_r46_image_register(uint64_t lo, uint64_t hi)
{
    uint64_t local[2] = { lo, hi };
    FUN_0065e454(0x6bb380, (void *)sk_r46_image_register_cb, &local);
    sk_r46_reg0 = local[0];
    sk_r46_reg1 = local[1];
}

/* FUN_0064fa54 @ 0x0064fa54   (est. sk_r46_image_register_cb)
 * Ghidra: void FUN_0064fa54(undefined8 *param_1)
 * Image-registration callback: walks the image metadata and deregisters it.
 * Confidence: medium */
void sk_r46_image_register_cb(uint64_t *p)
{
    FUN_00655c84(0x6bb388, &__data, sk_r46_dataslide, p[1], p[0], 0x80);
    FUN_0065cc50(0x6bb388);
}

/* FUN_0064faa4 @ 0x0064faa4   (est. sk_r46_metadata_end)
 * Ghidra: ulong FUN_0064faa4(long param_1)
 * Returns the highest end address among all type records (kind 0x19) in the
 * metadata block at param_1, or -1 when the block has no records.
 * Confidence: medium */
uint64_t sk_r46_metadata_end(long base)
{
    uint32_t count = *(uint32_t *)(base + 0x10);
    if (count == 0) return 0xffffffffffffffff;
    int *rec = (int *)(base + 0x20);
    uint64_t best = 0xffffffffffffffff;
    uint64_t maxend = 0xffffffffffffffff;
    for (uint32_t i = 0; i < count; i++) {
        uint64_t cand = maxend;
        if (*rec == 0x19 && thunk_FUN_0067aff0(rec + 2, 0x6a53e0, 0x10) != 0) {
            uint64_t e = *(uint64_t *)(rec + 6);
            if (best <= e) e = best;
            cand = e;
        }
        maxend = cand;
        rec = (int *)((long)rec + (uint32_t)rec[1]);
    }
    return maxend;
}

/* FUN_0064fb28 @ 0x0064fb28   (est. sk_r46_metadata_maxend)
 * Ghidra: ulong FUN_0064fb28(long param_1)
 * Returns the maximum end address over the type records in the metadata block.
 * Confidence: medium */
uint64_t sk_r46_metadata_maxend(long base)
{
    uint32_t count = *(uint32_t *)(base + 0x10);
    if (count == 0) return 0;
    int *rec = (int *)(base + 0x20);
    uint64_t acc = 0;
    for (uint32_t i = 0; i < count; i++) {
        uint64_t v = acc;
        if (*rec == 0x19) {
            uint64_t e = *(long *)(rec + 8) + *(long *)(rec + 6);
            if ((uint64_t)(*(long *)(rec + 8) + *(long *)(rec + 6)) <= acc) e = acc;
            v = e;
        }
        acc = v;
        rec = (int *)((long)rec + (uint32_t)rec[1]);
    }
    return acc;
}

/* FUN_0064fb74 @ 0x0064fb74   (est. sk_r46_metadata_record_at)
 * Ghidra: int * FUN_0064fb74(long param_1, int *param_2)
 * Returns the next type record (kind 0x19) at or after the given position, or a
 * zero-length placeholder when a type record would be unaligned.
 * Confidence: medium */
int *sk_r46_metadata_record_at(long base, int *at)
{
    uint32_t count = *(uint32_t *)(base + 0x10);
    if (count != 0) {
        int *rec = (int *)(base + 0x20);
        for (uint32_t i = 0; i < count; i++) {
            int *res = at;
            if (*rec == 0x19) {
                if (at == 0) {
                    if (rec + 0x12 < rec) __builtin_unreachable();
                    return rec;
                }
                res = 0;
                if (at != rec) res = at;
            }
            rec = (int *)((long)rec + (uint32_t)rec[1]);
            at = res;
        }
    }
    return 0;
}

/* FUN_0064fbc4 @ 0x0064fbc4   (est. sk_r46_metadata_record_by_name)
 * Ghidra: ulong FUN_0064fbc4(undefined8 param_1, undefined8 param_2)
 * Finds the type record in the metadata block whose 16-byte name compares equal
 * to param_2; returns its address or 0.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x64fc48) */
uint64_t sk_r46_metadata_record_by_name(uint64_t base, uint64_t name)
{
    uint64_t p = 0, lim = 0;
    for (;;) {
        p = (uint64_t)sk_r46_metadata_record_at((long)base, (int *)p);
        if (p == 0) return 0;
        lim = p + 0x48;
        if (thunk_FUN_0067aff0(name, (void *)(p + 8), 0x10) == 0) break;
    }
    if (p <= lim) return p;
    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x64fc48) */
}

/* FUN_0064fc4c @ 0x0064fc4c   (est. sk_r46_metadata_record_by_name_50)
 * Ghidra: ulong FUN_0064fc4c(long param_1, undefined8 param_2)
 * Like FUN_0064fbc4 but walks the 0x50-stride variant of the record table.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x64fd08) */
uint64_t sk_r46_metadata_record_by_name_50(long base, uint64_t name)
{
    uint64_t p = base + 0x48;
    uint64_t prev = 0, lim = 0;
    for (;;) {
        if (prev == 0) {
            if (*(int *)(base + 0x40) == 0) return 0;
            lim = p;
            if (base + 0x98U < p) goto fc4c_trap;
        } else {
            if (lim < prev + 0x50 || prev + 0x50 < prev) goto fc4c_trap;
            if (*(uint32_t *)(base + 0x40) == 0) return 0;
            if (prev < (uint64_t)(base + 0x48)) return 0;
            if ((uint64_t)(base - 8 + *(uint32_t *)(base + 0x40) * 0x50) <= prev) return 0;
            lim = prev + 0x50;
        }
        if (lim == 0) return 0;
        prev = lim + 0x50;
        if (thunk_FUN_0067aff0(name, (void *)lim, 0x10) == 0) break;
    }
    if (lim <= prev) return lim;
fc4c_trap:
    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x64fd08) */
}

/* FUN_0064fd24 @ 0x0064fd24   (est. sk_r46_metadata_first_1b)
 * Ghidra: int * FUN_0064fd24(long param_1)
 * Returns the first record of kind 0x1b in the metadata block (or 0).
 * Confidence: medium */
int *sk_r46_metadata_first_1b(long base)
{
    uint32_t count = *(uint32_t *)(base + 0x10);
    if (count != 0) {
        int *rec = (int *)(base + 0x20);
        for (uint32_t i = 0; i < count; i++) {
            if (*rec == 0x1b) return rec + 2;
            rec = (int *)((long)rec + (uint32_t)rec[1]);
        }
    }
    return 0;
}

/* FUN_0064fd5c @ 0x0064fd5c   (est. sk_r46_metadata_strings)
 * Ghidra: void FUN_0064fd5c(long param_1, ulong *param_2, ulong *param_3, long *param_4)
 * Extracts the string-table range {count, base} from the metadata block (record
 * kind 2) and returns its base/end.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x64fe58) */
void sk_r46_metadata_strings(long base, uint64_t *count, uint64_t *strbase, long *end)
{
    uint64_t rec = sk_r46_metadata_record_by_name((uint64_t)base, 0x6a53eb);
    uint32_t n = *(uint32_t *)(base + 0x10);
    long srec = 0;
    if (n != 0) {
        srec = *(long *)(rec + 0x18);
        int *r = (int *)(base + 0x20);
        uint32_t left = n;
        do {
            if (*r == 2) {
                uint64_t rec2 = sk_r46_metadata_record_by_name((uint64_t)base, 0x6a53f2);
                if (rec2 == 0 || (n = (uint32_t)r[3], r[3] == 0)) goto fd5c_empty;
                long o = *(long *)(rec2 + 0x28);
                srec = *(long *)(rec2 + 0x18) + (base - srec);
                uint64_t a = (srec - o) + (uint32_t)r[2];
                uint64_t b = a + (uint64_t)n * 0x10;
                if (b < a || ((uint64_t)((long)(b - a) >> 4) < n)) goto fd5c_trap;
                uint32_t k = r[4];
                *count = n;
                *strbase = a;
                srec = ((uint64_t)k - o) + srec;
                goto fd5c_done;
            }
            r = (int *)((long)r + (uint32_t)r[1]);
            left--;
        } while (left != 0);
    }
    sk_r46_metadata_record_by_name((uint64_t)base, 0x6a53f2);
fd5c_empty:
    srec = 0;
    *count = 0;
    *strbase = 0;
fd5c_done:
    *end = srec;
    return;
fd5c_trap:
    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x64fe58) */
}

/* FUN_0064fe58 @ 0x0064fe58   (est. sk_r46_metadata_field_find)
 * Ghidra: long FUN_0064fe58(ulong param_1, long *param_2, long param_3,
 *                            long param_4, long param_5)
 * Scans param_3 descriptor entries starting at param_4 and returns the one with
 * the smallest index >= param_1 (matching the record-size check), storing the
 * index into *param_2.
 * Confidence: medium */
long sk_r46_metadata_field_find(uint64_t min, long *out, long n, long base, long slide)
{
    long idx = 0, found = 0;
    if (n != 0) {
        long *e = (long *)(base + 8);
        for (long i = 0; i < n; i++) {
            if ((*(uint8_t *)((long)e - 4) & 0xee) == 0xe) {
                long k = *e;
                if (k - 1U < min && (min - k < min - idx)) {
                    found = (uint64_t)*(uint32_t *)(e - 1) + slide;
                    idx = k;
                }
            }
            e += 2;
        }
    }
    *out = idx;
    return found;
}

/* FUN_0064fec8 @ 0x0064fec8   (est. sk_r46_prespec_finalize)
 * Ghidra: void FUN_0064fec8(void)
 * Finalises the prespecialization caches: when the image flag is set, walks the
 * registered image list, instantiates each kind-0x1b record's metadata into the
 * 0x6bb418 cache slots, registers them with the type table, then flushes the
 * image metadata and returns.
 * Confidence: low
 * Notes: globals _DAT_006bb418, _DAT_006fec90; SoftwareBreakpoint(0x5519,0x650410) */
void sk_r46_prespec_finalize(void)
{
    if (sk_r46_imgflag == '\x01') {
        long *img = (long *)FUN_0065cb74();
        uint64_t base = (uint64_t)sk_r46_image_state_get();
        if (base != 0 && base + 8 < base) goto fec8_trap;
        uint64_t ctxt = (uint64_t)sk_r46_image_state_bounds();
        for (; img != 0; img = (long *)*img) {
            if (*(char *)(img + 1) < '\0') {
                uint64_t rec[2] = { 0, 0 };
                uint64_t r = (uint64_t)sk_r46_record_iter_next((long *)rec);
                while (r != 0) {
                    if ((uint32_t)sk_r46_record_kind((uint16_t *)r) == 0x1b) {
                        uint64_t n = (uint64_t)sk_r46_record_count((uint16_t *)r);
                        uint64_t i = 0;
                        while (i < n) {
                            if (0x13 < sk_r46_cache_count) {
                                FUN_00683d48();
                                goto fec8_trap;
                            }
                            uint16_t *recp = (uint16_t *)sk_r46_metadata_record_element((uint16_t *)r, i);
                            uint64_t flags = (uint64_t)(uint8_t)recp[0xd] << 0x10 |
                                             (uint64_t)*(uint8_t *)((long)recp + 0x1b) << 0x18 |
                                             (uint64_t)recp[0xc] |
                                             (uint64_t)((uint32_t)(uint8_t)recp[0xf] << 0x10 |
                                                        (uint32_t)*(uint8_t *)((long)recp + 0x1f) << 0x18 |
                                                        (uint32_t)recp[0xe]) << 0x20;
                            uint64_t size = (uint64_t)(uint8_t)recp[9] << 0x10 |
                                            (uint64_t)*(uint8_t *)((long)recp + 0x13) << 0x18 |
                                            (uint64_t)recp[8] |
                                            (uint64_t)((uint32_t)(uint8_t)recp[0xb] << 0x10 |
                                                       (uint32_t)*(uint8_t *)((long)recp + 0x17) << 0x18 |
                                                       (uint32_t)recp[10]) << 0x20;
                            uint64_t cc = sk_r46_cache_count;
                            uint64_t slot = cc * 0x40;
                            uint64_t a1 = (uint64_t)(uint8_t)recp[1] << 0x10 |
                                          (uint64_t)*(uint8_t *)((long)recp + 3) << 0x18 |
                                          (uint64_t)*recp |
                                          (uint64_t)((uint32_t)(uint8_t)recp[3] << 0x10 |
                                                     (uint32_t)*(uint8_t *)((long)recp + 7) << 0x18 |
                                                     (uint32_t)recp[2]) << 0x20;
                            uint64_t res = (uint64_t)FUN_00653b74(a1, size);
                            *(uint64_t *)(slot + 0x6bb420) = a1;
                            *(uint64_t *)(slot + 0x6bb430) = size;
                            *(uint64_t *)(slot + 0x6bb438) = flags;
                            *(uint8_t *)(slot + 0x6bb440) = (uint8_t)cc;
                            *(uint64_t *)(slot + 0x6bb448) = res;
                            *(uint64_t *)(slot + 0x6bb450) = 0;
                            *(uint64_t *)(slot + 0x6bb458) = 0;
                            sk_r46_cache_count = (int)(cc + 1);
                            sk_pair_t reg = sk_r46_metadata_record_register(a1, size, 0x90808, 0x11);
                            uint64_t tag = (uint64_t)FUN_00672de4(reg.lo, reg.hi, 0x6b5f10,
                                                                 (uint64_t *)(slot + 0x6bb420));
                            if ((tag & 0xff) != 0) {
                                FUN_00683d48();
                                goto fec8_trap;
                            }
                            *(uint64_t *)(slot + 0x6bb450) = reg.lo;
                            *(uint64_t *)(slot + 0x6bb458) = reg.hi;
                            i++;
                        }
                    }
                    r = (uint64_t)sk_r46_record_iter_next((long *)rec);
                }
            }
        }
    }
    FUN_0067d72c(0x6a4c9e);
    return;
fec8_trap:
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x650410) */
}
/* ================================================================== *
 * Part 5 — 0x650418-0x652204: metadata record iteration, string/IPC
 * bulk-copy, and the record-kind dispatch helpers.
 * ================================================================== */

extern long FUN_00665630();   /* release/restore to endpoint          */
extern long FUN_006793f4();   /* debug print                          */

/* Stats counters (Ghidra _DAT_006fec60..80). */
extern uint64_t sk_r46_stat_0;   /* _DAT_006fec60 */
extern uint64_t sk_r46_stat_1;   /* _DAT_006fec64 */
extern uint64_t sk_r46_stat_2;   /* _DAT_006fec68 */
extern uint64_t sk_r46_stat_3;   /* _DAT_006fec6c */
extern uint64_t sk_r46_stat_4;   /* _DAT_006fec70 */
extern uint64_t sk_r46_stat_5;   /* _DAT_006fec74 */
extern uint64_t sk_r46_stat_6;   /* _DAT_006fec78 */
extern uint64_t sk_r46_stat_7;   /* _DAT_006fec7c */
extern uint64_t sk_r46_stat_8;   /* _DAT_006fec80 */
extern uint64_t sk_r46_ctx_endpoint; /* _DAT_006bb400 */
extern uint64_t sk_r46_ep2;      /* _DAT_006b42f0 */
extern uint64_t sk_r46_dbg;      /* _DAT_006b4378 */

/* FUN_00650418 @ 0x00650418   (est. sk_r46_endpoint_status)
 * Ghidra: void FUN_00650418(void)
 * Queries the 0x6bb400 endpoint's status through the runtime context vtable
 * (+0x58). If the status byte is clear it restores 0x6b42f0 and returns;
 * otherwise it traps (bounds-checked against the 0x6b5e50 error table).
 * Confidence: low
 * Notes: SoftwareBreakpoint(0x5519,0x6504a0) */
void sk_r46_endpoint_status(void)
{
    sk_pair_t ctx = FUN_0066a8c4();
    uint64_t st = ((sk_fp_t)(ctx.hi + 0x58))(ctx.lo, 0x6bb400);
    if ((st & 0xff) == 0) {
        FUN_00665630(0x6b42f0);
        return;
    }
    uint64_t idx = (st & 0xff) * 8;
    uint8_t *p = (uint8_t *)(idx + 0x6b5e50);
    if (p <= (uint8_t *)0x6b5e58 + idx) { /* bounds: within the 0x6b5e58..0x6b5e91 window */
        FUN_006833d4(0x6a53fd);
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6504a0) */
}

/* FUN_006504a0 @ 0x006504a0   (est. sk_r46_metadata_record_register)
 * Ghidra: undefined1[16] FUN_006504a0(undefined8 param_1, long param_2,
 *                                      uint param_3, undefined1 param_4)
 * Registers a metadata record {addr=param_1, size=param_2, flags=param_3,
 * kind=param_4} with the Swift runtime via the context vtable (+0x30, request
 * `param_3 | 0x801`). Returns the runtime's {lo,hi} response.
 * Confidence: low
 * Notes: panic path via 0x6b5e50 error table; FUN_006793f4 debug print */
sk_pair_t sk_r46_metadata_record_register(uint64_t addr, long size, uint32_t flags, uint8_t kind)
{
    uint64_t out_lo = 0, out_hi = 0;
    if (size != 0) {
        uint8_t req[32];
        SK_MSG_STORE(req, 0, 0x11);
        SK_MSG_STORE(req, 16, addr);
        SK_MSG_STORE(req, 24, (uint64_t)size);
        SK_MSG_STORE(req, 32, kind);
        sk_pair_t ctx = FUN_0066a8c4();
        uint64_t st = ((sk_fp_t)(ctx.hi + 0x30))(ctx.lo, flags | 0x801, req, &out_lo, 0, 0);
        if ((st & 0xff) != 0) {
            uint64_t idx = (st & 0xff) * 8;
            uint8_t *p = (uint8_t *)(idx + 0x6b5e50);
            if (p <= (uint8_t *)0x6b5e58 + idx) {
                FUN_0067d72c(0x6a5491);
                uint64_t dbg = sk_r46_dbg;
                sk_pair_t ctx2 = FUN_0066a8c4();
                FUN_006793f4(dbg, ctx2.lo, ctx2.hi);
                FUN_0065c2f0(0, 0x6a54c4);
            }
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x6505e0) */
        }
        if (out_hi == 0) FUN_0065558c();
        ((sk_fp_t)(out_hi + 8))(out_lo, req);
    }
    sk_pair_t r = { out_lo, out_hi };
    return r;
}

/* FUN_006505e0 @ 0x006505e0   (est. sk_r46_l4_notify)
 * Ghidra: void FUN_006505e0(long *param_1, ulong param_2, undefined8 param_3,
 *                            ulong *param_4)
 * Sends an L4 notification for entry param_2 of the table at param_1: bumps the
 * per-path stats counters and, when the entry is resident, issues a 0x11-tagged
 * CallSupervisor(0) and maps any nonzero status to an L4 error description.
 * Confidence: low
 * Notes: stats globals _DAT_006fec60..; L4 error table 0x6884d8 */
void sk_r46_l4_notify(long *table, uint64_t idx, uint64_t arg, uint64_t *out)
{
    uint64_t cookie = sk_r46_cookie;
    sk_r46_stat_0 = sk_r46_stat_0 + 1;
    if (idx < (uint64_t)table[2]) {
        if (idx < (uint64_t)table[1]) {
            uint64_t st = table[3];
            uint8_t m[24];
            SK_MSG_STORE(m, 0, 0x11);
            SK_MSG_STORE(m, 8, idx);
            SK_MSG_STORE(m, 16, arg);
            CallSupervisor(0);
            if ((st & 0xff) != 0) {
                uint8_t code = (uint8_t)FUN_00683da0(st, (uint8_t[32]){0});
                if (9 < code) {
                    uint64_t buf[4];
                    thunk_FUN_0067aa00(buf, (void *)0x688618, 0x20);
                    sk_r46_l4_error_print((uint64_t)buf, 0x20);
                    return;
                }
                uint64_t buf2[4];
                thunk_FUN_0067aa00(buf2, (void *)(0x6884d8 + (uint32_t)code * 0x20), 0x20);
                return;
            }
            if ((int)FUN_00653bb8(table[5], *table + idx) == 0) {
                sk_r46_stat_4 = sk_r46_stat_4 + 1;
            } else {
                sk_r46_stat_3 = sk_r46_stat_3 + 1;
                *out = (uint64_t)*(uint8_t *)(table + 4);
            }
        } else {
            sk_r46_stat_2 = sk_r46_stat_2 + 1;
        }
    } else {
        sk_r46_stat_1 = sk_r46_stat_1 + 1;
    }
    if (sk_r46_cookie != cookie) FUN_0067f660();
}

/* FUN_006507fc @ 0x006507fc   (est. sk_r46_l4_error_string_copy_2)
 * Ghidra: void FUN_006507fc(undefined8 param_1, byte param_2)
 * Copies the 32-byte L4 error-code description (table at 0x6884d8) into param_1.
 * Confidence: medium
 * Notes: strings s_L4_ErrorCodeSuccess_006884d8 .. _PermissionInvalid_006885f8 */
void sk_r46_l4_error_string_copy_2(uint64_t *out, uint8_t code)
{
    if (9 < code) {
        thunk_FUN_0067aa00(out, (void *)0x688618, 0x20);
        sk_r46_l4_error_print((uint64_t)out, 0x20);
        return;
    }
    thunk_FUN_0067aa00(out, (void *)(0x6884d8 + (uint32_t)code * 0x20), 0x20);
}

/* FUN_00650934 @ 0x00650934   (est. sk_r46_prespec_notify_handler)
 * Ghidra: undefined8 FUN_00650934(undefined8 *param_1, undefined8 param_2, long *param_3)
 * Dispatches a received prespecialization notification when *param_3==1: calls
 * the registered handler (param_1[2]) and processes the result code, consulting
 * the 0x6bb418 cache for the returned type index. Returns 0/1/2 status.
 * Confidence: low
 * Notes: cache globals; SoftwareBreakpoint(0x5519,0x650af8) */
uint64_t sk_r46_prespec_notify_handler(uint64_t *obj, uint64_t arg, long *req)
{
    if (*req == 1) {
        sk_r46_stat_5 = sk_r46_stat_5 + 1;
        uint64_t out[6] = { 0, 0, 0, 0, 0, 0 };
        uint8_t code = ((sk_fp_t)obj[2])(obj[0], obj[1], req[1],
                                         *(uint8_t *)((long)req + 0x19), out);
        if (code != 0 && (out[0] & 1) != 0) {
            uint8_t *p = (uint8_t *)((uint64_t)code * 8 + 0x6b5e50);
            if (p <= (uint8_t *)0x6b5e58 + (uint64_t)code * 8) {
                FUN_006833d4(0x6a5682);
            }
            __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x650af8) */
        }
        if (code == 5) {
            sk_r46_stat_6 = sk_r46_stat_6 + 1;
            return 0;
        } else if (code == 0) {
            if ((out[0] & 1) == 0) {
                return 1;
            }
            sk_r46_stat_8 = sk_r46_stat_8 + 1;
            if ((0x13 < out[4]) || (sk_r46_cache_count <= out[4])) {
                FUN_006833d4(0x6a5740);
            }
            uint64_t slot = *(uint64_t *)(out[4] * 0x40 + 0x6bb448);
            if (slot == 0) FUN_006833d4(0x6a56c9);
            if ((FUN_00653c98(slot, out[2], out[3]) & 1) == 0) {
                FUN_006833d4(0x6a5705);
            }
            ((sk_fp_t)(obj[2] + 8))(obj[0], obj[1], out[2], 1);
            return 1;
        } else {
            sk_r46_stat_7 = sk_r46_stat_7 + 1;
            return 2;
        }
    }
    return 0;
}

/* FUN_00650af8 @ 0x00650af8   (est. sk_r46_metadata_record_base)
 * Ghidra: long sk_r46_metadata_record_base(long *param_1, ulong param_2)
 * Returns the address of record param_2 (each 0x40 bytes) in the metadata block
 * at param_1, bounds-checked against param_1[1]; panics if the index field is
 * out of range (param_2 >> 0x3a).
 * Confidence: medium
 * Notes: FUN_0067b280 fatal */
long sk_r46_metadata_record_base(long *base, uint64_t idx)
{
    if (idx >> 0x3a != 0) FUN_0067b280(0x6a576b);
    if (idx * 0x40 < (uint64_t)base[1]) {
        return idx * 0x40 + *base;
    }
    return 0;
}

/* FUN_00650b3c @ 0x00650b3c   (est. sk_r46_metadata_record_element)
 * Ghidra: long sk_r46_metadata_record_element(ushort *param_1, ulong param_2)
 * Returns a pointer to element param_2 of the record at param_1: reads the
 * record kind (must be < 0x1d), multiplies by the per-kind element size
 * (0x6b5f28 table), and bounds-checks against the record's element count.
 * Confidence: medium
 * Notes: table at 0x6b5f28; FUN_0065c2f0 fatal */
long sk_r46_metadata_record_element(uint16_t *rec, uint64_t idx)
{
    uint64_t kind = (uint64_t)(uint8_t)rec[1] << 0x10 |
                    (uint64_t)*(uint8_t *)((long)rec + 3) << 0x18 | (uint64_t)*rec;
    if (0x1c < (uint32_t)kind) FUN_0065c2f0(0, 0x6a592b);
    uint64_t esz = SK_TBL_SIZE(kind);
    uint64_t off = idx * esz;
    uint64_t count = (uint64_t)(uint8_t)rec[3] << 0x10 |
                     (uint64_t)*(uint8_t *)((long)rec + 7) << 0x18 | (uint64_t)rec[2] |
                     (uint64_t)((uint32_t)(uint8_t)rec[5] << 0x10 |
                                (uint32_t)*(uint8_t *)((long)rec + 0xb) << 0x18 |
                                (uint32_t)rec[4]) << 0x20;
    if (esz == 0) return 0;                 /* guard: idx*esz must not overflow */
    if (off < count) return (long)rec + off + 0xc;
    return 0;
}

/* FUN_00650c10 @ 0x00650c10   (est. sk_r46_record_kind)
 * Ghidra: uint sk_r46_record_kind(ushort *param_1)
 * Returns the record kind word (first 32 bits of the header).
 * Confidence: high (trivial field read) */
uint32_t sk_r46_record_kind(uint16_t *rec)
{
    return (uint32_t)(uint8_t)rec[1] << 0x10 | (uint32_t)*(uint8_t *)((long)rec + 3) << 0x18 |
           (uint32_t)*rec;
}

/* FUN_00650c34 @ 0x00650c34   (est. sk_r46_record_count)
 * Ghidra: ulong sk_r46_record_count(ushort *param_1)
 * Returns the number of elements in the record (element count / element size).
 * Confidence: medium
 * Notes: table at 0x6b5f28; FUN_0065c2f0 fatal */
uint64_t sk_r46_record_count(uint16_t *rec)
{
    uint64_t kind = (uint64_t)(uint8_t)rec[1] << 0x10 |
                    (uint64_t)*(uint8_t *)((long)rec + 3) << 0x18 | (uint64_t)*rec;
    if ((uint32_t)kind < 0x1d) {
        uint64_t esz = SK_TBL_SIZE(kind);
        uint64_t cnt = 0;
        if (esz != 0) {
            cnt = ((uint64_t)(uint8_t)rec[3] << 0x10 |
                   (uint64_t)*(uint8_t *)((long)rec + 7) << 0x18 | (uint64_t)rec[2] |
                   (uint64_t)((uint32_t)(uint8_t)rec[5] << 0x10 |
                              (uint32_t)*(uint8_t *)((long)rec + 0xb) << 0x18 |
                              (uint32_t)rec[4]) << 0x20) / esz;
        }
        return cnt;
    }
    FUN_0065c2f0(0, 0x6a592b);
}

/* FUN_00650ce0 @ 0x00650ce0   (est. sk_r46_record_iterate)
 * Ghidra: undefined8 FUN_00650ce0(ushort *param_1, undefined8 param_2,
 *                                  undefined8 param_3, ulong *param_4)
 * Iterates the elements of the record at param_1 using the per-kind callback
 * (0x6b5f30) with FUN_00650dc8 as the element visitor. On success stores the
 * element count into *param_4 and returns 1.
 * Confidence: medium
 * Notes: table 0x6b5f30/38; callback FUN_00650dc8 */
uint64_t sk_r46_record_iterate(uint16_t *rec, uint64_t a, uint64_t b, uint64_t *count_out)
{
    uint64_t kind = (uint64_t)(uint8_t)rec[1] << 0x10 |
                    (uint64_t)*(uint8_t *)((long)rec + 3) << 0x18 | (uint64_t)*rec;
    if (0x1c < (uint32_t)kind) FUN_0065c2f0(0, 0x6a592b);
    uint64_t off = kind * 0x30;
    long end = 0;
    if (SK_TBL_FN0(kind) != 0 && SK_TBL_FN1(kind) != 0) {
        uint16_t *local = rec;
        uint64_t r = ((sk_fp_t)SK_TBL_FN0(kind))(a, b, (void *)sk_r46_record_element_visit, &local);
        if ((int)r == 0) return r;
        if (end != 0) {
            uint64_t cnt = 0;
            if (SK_TBL_SIZE(kind) != 0) {
                cnt = ((end - (long)rec) - 0xcU) / SK_TBL_SIZE(kind);
            }
            *count_out = cnt;
            return 1;
        }
    }
    return 0;
}

/* FUN_00650dc8 @ 0x00650dc8   (est. sk_r46_record_element_visit)
 * Ghidra: void FUN_00650dc8(undefined8 *param_1, ulong param_2)
 * Element visitor invoked by the record iterator: computes the element pointer
 * from the element index and stores it via FUN_0067cc5c.
 * Confidence: medium
 * Notes: table 0x6b5f28/38; SoftwareBreakpoint(0x5519,0x650eb4) */
void sk_r46_record_element_visit(uint64_t *ctx, uint64_t idx)
{
    if (ctx == 0) return;
    uint16_t *rec = (uint16_t *)*ctx;
    uint64_t kind = (uint64_t)(uint8_t)rec[1] << 0x10 |
                    (uint64_t)*(uint8_t *)((long)rec + 3) << 0x18 | (uint64_t)*rec;
    if ((uint32_t)kind < 0x1d) {
        uint64_t off = kind * 0x30;
        uint64_t esz = SK_TBL_SIZE(kind);
        uint64_t cnt = 0;
        if (esz != 0) {
            cnt = ((uint64_t)(uint8_t)rec[3] << 0x10 |
                   (uint64_t)*(uint8_t *)((long)rec + 7) << 0x18 | (uint64_t)rec[2] |
                   (uint64_t)((uint32_t)(uint8_t)rec[5] << 0x10 |
                              (uint32_t)*(uint8_t *)((long)rec + 0xb) << 0x18 |
                              (uint32_t)rec[4]) << 0x20) / esz;
        }
        if (idx * esz < cnt || idx * esz - cnt == 0) {
            ctx[1] = (uint64_t)FUN_0067cc5c(idx, rec + 6, cnt, esz,
                                            *(uint64_t *)(off + 0x6b5f38)).lo;
            return;
        }
        __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x650eb4) */
    }
    FUN_0065c2f0(0, 0x6a592b);
}

/* FUN_00650ec8 @ 0x00650ec8   (est. sk_r46_record_nop)
 * Ghidra: void FUN_00650ec8(void)
 * No-op placeholder.
 * Confidence: high (trivial) */
void sk_r46_record_nop(void)
{
}

/* FUN_00650ed0 @ 0x00650ed0   (est. sk_r46_record_iter_next)
 * Ghidra: ushort * sk_r46_record_iter_next(long *param_1)
 * Advances to the next record in the block described by {*param_1, param_1[1]},
 * validating each record's size field; returns the next record or 0 at end.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x65105c); FUN_0067b280 fatal */
uint16_t *sk_r46_record_iter_next(long *state)
{
    uint16_t *base = (uint16_t *)*state;
    uint64_t off = (uint64_t)state[1];
    uint16_t *cur = base + 4;
    for (;;) {
        uint64_t lim = off + 0xc;
        uint64_t hdr = (uint64_t)(uint8_t)base[1] << 0x10 |
                       (uint64_t)*(uint8_t *)((long)base + 3) << 0x18 | (uint64_t)*base |
                       (uint64_t)((uint32_t)(uint8_t)base[3] << 0x10 |
                                  (uint32_t)*(uint8_t *)((long)base + 7) << 0x18 |
                                  (uint32_t)base[2]) << 0x20;
        if (hdr < lim) return 0;
        uint16_t *next = (uint16_t *)((long)cur + off);
        if (next != 0 &&
            ((next + 6 < next || next < cur) ||
             ((uint16_t *)((long)cur + hdr) < next + 6) ||
             (hdr - lim <
              ((uint64_t)(uint8_t)next[3] << 0x10 |
               (uint64_t)*(uint8_t *)((long)next + 7) << 0x18 | (uint64_t)next[2] |
               (uint64_t)((uint32_t)(uint8_t)next[5] << 0x10 |
                          (uint32_t)*(uint8_t *)((long)next + 0xb) << 0x18 |
                          (uint32_t)next[4]) << 0x20))))
            break;
        if (0xfffffffffffffff3 < off) FUN_0067b280(0x6a576b);
        uint64_t sz = (uint64_t)(uint8_t)next[3] << 0x10 |
                      (uint64_t)*(uint8_t *)((long)next + 7) << 0x18 | (uint64_t)next[2] |
                      (uint64_t)((uint32_t)(uint8_t)next[5] << 0x10 |
                                 (uint32_t)*(uint8_t *)((long)next + 0xb) << 0x18 |
                                 (uint32_t)next[4]) << 0x20;
        off = sz + lim;
        if (sz + lim < sz) FUN_0067b280(0x6a576b);
        state[1] = off;
        if (next != 0 && next + 6 < next) break;
        if (sk_r46_record_kind(next) < 0x1d) return next;
    }
    __builtin_unreachable(); /* trap: SoftwareBreakpoint(0x5519,0x65105c) */
}

/* FUN_00651074 @ 0x00651074   (est. sk_r46_record_has_more)
 * Ghidra: bool FUN_00651074(long *param_1)
 * Returns whether the record block at param_1 has more records to iterate.
 * Confidence: medium */
bool sk_r46_record_has_more(long *state)
{
    uint16_t *base = (uint16_t *)*state;
    uint64_t hdr = (uint64_t)(uint8_t)base[1] << 0x10 |
                   (uint64_t)*(uint8_t *)((long)base + 3) << 0x18 | (uint64_t)*base |
                   (uint64_t)((uint32_t)(uint8_t)base[3] << 0x10 |
                              (uint32_t)*(uint8_t *)((long)base + 7) << 0x18 |
                              (uint32_t)base[2]) << 0x20;
    return hdr < (uint64_t)state[1] + 0xcU;
}

/* FUN_006510cc @ 0x006510cc   (est. sk_r46_image_state_get)
 * Ghidra: void FUN_006510cc(void)
 * Returns the current image state (base at +0x78); panics if unset.
 * Confidence: medium
 * Notes: FUN_00655848 image state; SoftwareBreakpoint(0x5519,0x6510fc) */
void *sk_r46_image_state_get(void)
{
    uint64_t st = (uint64_t)FUN_00655848();
    if (st + 0x160 < st) __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x6510fc) */
    if (*(long *)(st + 0x78) != 0) {
        return (void *)st;
    }
    FUN_0065c2f0(0, 0x6a5953);
}

/* FUN_00651108 @ 0x00651108   (est. sk_r46_image_state_bounds)
 * Ghidra: void FUN_00651108(void)
 * Returns the image state after validating the +0xa8/+0xb0 bounds.
 * Confidence: medium
 * Notes: SoftwareBreakpoint(0x5519,0x651144) */
void *sk_r46_image_state_bounds(void)
{
    uint64_t st = (uint64_t)FUN_00655848();
    if (st <= st + 0x160 &&
        *(uint64_t *)(st + 0xa8) <= *(uint64_t *)(st + 0xa8) + *(long *)(st + 0xb0)) {
        return (void *)st;
    }
    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x651144) */
}

/* FUN_0065114c @ 0x0065114c   (est. sk_r46_string_fetch_ipc)
 * Ghidra: void FUN_0065114c(undefined8 param_1, ulong param_2, code *param_3,
 *                            undefined8 param_4)
 * Fetches up to param_2 bytes of a string via IPC (FUN_006529d8), copies it into
 * a 0x110-byte scratch buffer and invokes the callback (param_3).
 * Confidence: low
 * Notes: scratch 0x110; FUN_0067ce74 memcpy */
void sk_r46_string_fetch_ipc(uint64_t src, uint64_t len, sk_fp_t cb, uint64_t ctx)
{
    uint64_t cookie = sk_r46_cookie;
    uint8_t buf[264];
    thunk_FUN_0067a780(buf, 0x110);
    uint64_t got = (uint64_t)FUN_006529d8(src, len);
    if (got != 0) {
        if (0xff < len) len = 0x100;
        FUN_0067ce74(buf, (void *)got, len, 0x108);
        cb(ctx, buf);
    }
    if (sk_r46_cookie != cookie) FUN_0067f660(got != 0);
}

/* FUN_00651804 @ 0x00651804   (est. sk_r46_string_fetch_ipc_120)
 * Ghidra: void FUN_00651804(undefined8 param_1, ulong param_2, code *param_3,
 *                            undefined8 param_4)
 * String-fetch variant with a 0x120 scratch buffer.
 * Confidence: low */
void sk_r46_string_fetch_ipc_120(uint64_t src, uint64_t len, sk_fp_t cb, uint64_t ctx)
{
    uint64_t cookie = sk_r46_cookie;
    uint8_t buf[288];
    thunk_FUN_0067a780(buf, 0x120);
    uint64_t got = (uint64_t)FUN_006529d8(src, len);
    if (got != 0) {
        if (0xff < len) len = 0x100;
        FUN_0067ce74(buf, (void *)got, len, 0x120);
        cb(ctx, buf);
    }
    if (sk_r46_cookie != cookie) FUN_0067f660(got != 0);
}

/* FUN_00651214 / 00651218 / 006518c8 / 006518cc — 256-byte string compares. */

/* FUN_00651214 @ 0x00651214   (est. sk_r46_strcmp_256)
 * Ghidra: uint FUN_00651214(long param_1, long param_2)
 * Three-way compare of the 256-byte strings at (param_1+8) and (param_2+8).
 * Confidence: medium */
uint32_t sk_r46_strcmp_256(long a, long b)
{
    int r = (int)thunk_FUN_0067aff0(a + 8, b + 8, 0x100);
    uint32_t res = (uint32_t)(0 < r);
    if (r < 0) res = 0xffffffff;
    return res;
}

/* FUN_00651218 @ 0x00651218   (est. sk_r46_strcmp_256_2)
 * Ghidra: uint FUN_00651218(long param_1, long param_2)
 * Duplicate of FUN_00651214.
 * Confidence: medium */
uint32_t sk_r46_strcmp_256_2(long a, long b)
{
    int r = (int)thunk_FUN_0067aff0(a + 8, b + 8, 0x100);
    uint32_t res = (uint32_t)(0 < r);
    if (r < 0) res = 0xffffffff;
    return res;
}

/* FUN_006518c8 @ 0x006518c8   (est. sk_r46_strcmp_256_3)
 * Ghidra: uint FUN_006518c8(undefined8 param_1, undefined8 param_2)
 * Three-way compare of two 256-byte strings.
 * Confidence: medium */
uint32_t sk_r46_strcmp_256_3(uint64_t a, uint64_t b)
{
    int r = (int)thunk_FUN_0067aff0(a, b, 0x100);
    uint32_t res = (uint32_t)(0 < r);
    if (r < 0) res = 0xffffffff;
    return res;
}

/* FUN_006518cc @ 0x006518cc   (est. sk_r46_strcmp_256_4)
 * Ghidra: uint FUN_006518cc(undefined8 param_1, undefined8 param_2)
 * Duplicate of FUN_006518c8.
 * Confidence: medium */
uint32_t sk_r46_strcmp_256_4(uint64_t a, uint64_t b)
{
    int r = (int)thunk_FUN_0067aff0(a, b, 0x100);
    uint32_t res = (uint32_t)(0 < r);
    if (r < 0) res = 0xffffffff;
    return res;
}

/* FUN_00651244 @ 0x00651244   (est. sk_r46_metadata_bulk_copy)
 * Ghidra: long FUN_00651244(undefined8 param_1, ushort *param_2, long *param_3,
 *                            undefined1 *param_4, ulong param_5)
 * Bulk-copies prespecialization metadata from the source record (param_2) into
 * the 0x107-byte output chunks at param_4, resolving each element's address
 * through param_3 (the destination metadata block). Returns the element count.
 * Confidence: low
 * Notes: chunks 0x107; table 0x6b5f28/38; SoftwareBreakpoint(0x5519,0x6515b0) */
long sk_r46_metadata_bulk_copy(uint64_t a, uint16_t *rec, long *dst, uint8_t *out, uint64_t len)
{
    uint64_t kind = (uint64_t)(uint8_t)rec[1] << 0x10 |
                    (uint64_t)*(uint8_t *)((long)rec + 3) << 0x18 | (uint64_t)*rec;
    if (0x1c < (uint32_t)kind) FUN_0065c2f0(0, 0x6a592b);
    long total = 0;
    if (len >= 0x107) {
        uint64_t nchunk = len / 0x107;
        uint64_t off = kind * 0x30;
        uint64_t visitor = SK_TBL_FN1(kind);
        if (nchunk < 2) nchunk = 1;
        for (uint64_t c = 0; c < nchunk; c++) {
            uint8_t *chunk = out + c * 0x107;
            if (visitor == 0 || SK_TBL_FN0(kind) == 0) {
                uint64_t i = 0;
                long el;
                while ((el = sk_r46_metadata_record_element(rec, i)) != 0) {
                    if (chunk < out || out + len < chunk + 0x107) goto l244_trap;
                    if ((int)thunk_FUN_0067aff0((void *)(el + 8), chunk + 8, 0xff) == 0) {
                        uint64_t ea = (uint64_t)*(uint8_t *)(el + 0x10a) << 0x10 |
                                      (uint64_t)*(uint8_t *)(el + 0x10b) << 0x18 |
                                      (uint64_t)*(uint16_t *)(el + 0x108) |
                                      (uint64_t)((uint32_t)*(uint8_t *)(el + 0x10e) << 0x10 |
                                                 (uint32_t)*(uint8_t *)(el + 0x10f) << 0x18 |
                                                 (uint32_t)*(uint16_t *)(el + 0x10c)) << 0x20;
                        long ea2 = 0;
                        if (ea != 0) {
                            if (*(uint8_t *)(el + 0x10f) >> 2 != 0) FUN_0067b280(0x6a576b);
                            ea = ea * 0x40;
                            ea2 = (ea < (uint64_t)dst[1]) ? ea + *dst : 0;
                        }
                        chunk[0] = (uint8_t)ea2;
                        chunk[5] = (uint8_t)((uint64_t)ea2 >> 0x28);
                        chunk[3] = (uint8_t)((uint64_t)ea2 >> 0x18);
                        chunk[2] = (uint8_t)((uint64_t)ea2 >> 0x10);
                        chunk[4] = (uint8_t)((uint64_t)ea2 >> 0x20);
                        chunk[1] = (uint8_t)((uint64_t)ea2 >> 8);
                        chunk[7] = (uint8_t)((uint64_t)ea2 >> 0x38);
                        chunk[6] = (uint8_t)((uint64_t)ea2 >> 0x30);
                        total++;
                    }
                    i++;
                }
            } else {
                uint64_t cnt = 0;
                if (rec == 0) {
                    if (chunk < out || out + len < chunk + 0x107) goto l244_trap;
                    if (sk_r46_record_iterate(0, (uint64_t)(chunk + 8), 0xff, &cnt) != 0)
                        goto l244_have;
                } else {
                    if (chunk < out || out + len < chunk + 0x107) goto l244_trap;
                    if ((sk_r46_record_iterate(rec, (uint64_t)(chunk + 8), 0xff, &cnt) & 1) != 0) {
l244_have:
                        long el = sk_r46_metadata_record_element(rec, cnt);
                        if (el != 0 &&
                            (int)thunk_FUN_0067aff0((void *)(el + 8), chunk + 8, 0xff) == 0) {
                            if (chunk + 0x107 < chunk) goto l244_trap;
                            uint64_t ea = (uint64_t)*(uint8_t *)(el + 0x10a) << 0x10 |
                                          (uint64_t)*(uint8_t *)(el + 0x10b) << 0x18 |
                                          (uint64_t)*(uint16_t *)(el + 0x108) |
                                          (uint64_t)((uint32_t)*(uint8_t *)(el + 0x10e) << 0x10 |
                                                     (uint32_t)*(uint8_t *)(el + 0x10f) << 0x18 |
                                                     (uint32_t)*(uint16_t *)(el + 0x10c)) << 0x20;
                            long ea2 = 0;
                            if (ea != 0) {
                                if (*(uint8_t *)(el + 0x10f) >> 2 != 0) FUN_0067b280(0x6a576b);
                                ea = ea * 0x40;
                                ea2 = (ea < (uint64_t)dst[1]) ? ea + *dst : 0;
                            }
                            chunk[0] = (uint8_t)ea2;
                            chunk[5] = (uint8_t)((uint64_t)ea2 >> 0x28);
                            chunk[3] = (uint8_t)((uint64_t)ea2 >> 0x18);
                            chunk[2] = (uint8_t)((uint64_t)ea2 >> 0x10);
                            chunk[1] = (uint8_t)((uint64_t)ea2 >> 8);
                            chunk[4] = (uint8_t)((uint64_t)ea2 >> 0x20);
                            chunk[7] = (uint8_t)((uint64_t)ea2 >> 0x38);
                            chunk[6] = (uint8_t)((uint64_t)ea2 >> 0x30);
                            total++;
                        }
                    }
                }
            }
        }
    }
    return total;
l244_trap:
    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x6515b0) */
}

/* FUN_006515dc @ 0x006515dc   (est. sk_r46_metadata_bulk_copy_287)
 * Ghidra: long FUN_006515dc(undefined8 param_1, ushort *param_2, undefined8 param_3,
 *                            ulong param_4, ulong param_5)
 * Bulk-copy variant with 0x287-byte chunks, invoking FUN_00652a38 per element.
 * Confidence: low
 * Notes: chunks 0x287; SoftwareBreakpoint(0x5519,0x6517f0) */
long sk_r46_metadata_bulk_copy_287(uint64_t a, uint16_t *rec, uint64_t dst,
                                   uint64_t out, uint64_t len)
{
    uint64_t kind = (uint64_t)(uint8_t)rec[1] << 0x10 |
                    (uint64_t)*(uint8_t *)((long)rec + 3) << 0x18 | (uint64_t)*rec;
    if (0x1c < (uint32_t)kind) FUN_0065c2f0(0, 0x6a592b);
    long total = 0;
    if (len >= 0x287) {
        uint64_t nchunk = len / 0x287;
        uint64_t off = kind * 0x30;
        uint64_t visitor = SK_TBL_FN1(kind);
        if (nchunk < 2) nchunk = 1;
        for (uint64_t c = 0; c < nchunk; c++) {
            uint64_t chunk = out + c * 0x287;
            if (visitor == 0 || SK_TBL_FN0(kind) == 0) {
                uint64_t i = 0;
                long el;
                while ((el = sk_r46_metadata_record_element(rec, i)) != 0) {
                    if (chunk < out || out + len < chunk + 0x287) goto l5dc_trap;
                    if ((int)thunk_FUN_0067aff0((void *)el, (void *)(chunk + 0x188), 0xff) == 0) {
                        total += (uint32_t)FUN_00652a38(dst, el, chunk);
                    }
                    i++;
                }
            } else {
                uint64_t cnt = 0;
                if (rec == 0) {
                    if (chunk < out || out + len < chunk + 0x287) goto l5dc_trap;
                    if (sk_r46_record_iterate(0, (uint64_t)(chunk + 0x188), 0xff, &cnt) != 0)
                        goto l5dc_have;
                } else {
                    if (chunk < out || out + len < chunk + 0x287) goto l5dc_trap;
                    if ((sk_r46_record_iterate(rec, (uint64_t)(chunk + 0x188), 0xff, &cnt) & 1) != 0) {
l5dc_have:
                        long el = sk_r46_metadata_record_element(rec, cnt);
                        if (el != 0 &&
                            (int)thunk_FUN_0067aff0((void *)el, (void *)(chunk + 0x188), 0xff) == 0) {
                            if (chunk + 0x287 < chunk) goto l5dc_trap;
                            total += (uint32_t)FUN_00652a38(dst, el, chunk);
                        }
                    }
                }
            }
        }
    }
    return total;
l5dc_trap:
    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x6517f0) */
}

/* FUN_006518f0 @ 0x006518f0   (est. sk_r46_metadata_bulk_copy_e0)
 * Ghidra: long FUN_006518f0(undefined8 param_1, ushort *param_2, undefined8 param_3,
 *                            ulong param_4, ulong param_5)
 * Bulk-copy variant with 0x107 chunks and a 0xe0 compare window, invoking
 * FUN_006531d8 per element.
 * Confidence: low
 * Notes: SoftwareBreakpoint(0x5519,0x651b04) */
long sk_r46_metadata_bulk_copy_e0(uint64_t a, uint16_t *rec, uint64_t dst,
                                  uint64_t out, uint64_t len)
{
    uint64_t kind = (uint64_t)(uint8_t)rec[1] << 0x10 |
                    (uint64_t)*(uint8_t *)((long)rec + 3) << 0x18 | (uint64_t)*rec;
    if (0x1c < (uint32_t)kind) FUN_0065c2f0(0, 0x6a592b);
    long total = 0;
    if (len >= 0x107) {
        uint64_t nchunk = len / 0x107;
        uint64_t off = kind * 0x30;
        uint64_t visitor = SK_TBL_FN1(kind);
        if (nchunk < 2) nchunk = 1;
        for (uint64_t c = 0; c < nchunk; c++) {
            uint64_t chunk = out + c * 0x107;
            if (visitor == 0 || SK_TBL_FN0(kind) == 0) {
                uint64_t i = 0;
                long el;
                while ((el = sk_r46_metadata_record_element(rec, i)) != 0) {
                    if (chunk < out || out + len < chunk + 0x107) goto l8f0_trap;
                    if ((int)thunk_FUN_0067aff0((void *)el, (void *)(chunk + 8), 0xe0) == 0) {
                        if (chunk + 0x107 < chunk) goto l8f0_trap;
                        FUN_006531d8(dst, el, chunk);
                        total++;
                    }
                    i++;
                }
            } else {
                uint64_t cnt = 0;
                if (rec == 0) {
                    if (chunk < out || out + len < chunk + 0x107) goto l8f0_trap;
                    if (sk_r46_record_iterate(0, (uint64_t)(chunk + 8), 0xe0, &cnt) != 0)
                        goto l8f0_have;
                } else {
                    if (chunk < out || out + len < chunk + 0x107) goto l8f0_trap;
                    if ((sk_r46_record_iterate(rec, (uint64_t)(chunk + 8), 0xe0, &cnt) & 1) != 0) {
l8f0_have:
                        long el = sk_r46_metadata_record_element(rec, cnt);
                        if (el != 0 &&
                            (int)thunk_FUN_0067aff0((void *)el, (void *)(chunk + 8), 0xe0) == 0) {
                            if (chunk + 0x107 < chunk) goto l8f0_trap;
                            FUN_006531d8(dst, el, chunk);
                            total++;
                        }
                    }
                }
            }
        }
    }
    return total;
l8f0_trap:
    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x651b04) */
}

/* FUN_00651b18 @ 0x00651b18   (est. sk_r46_copy8)
 * Ghidra: bool FUN_00651b18(undefined8 *param_1, long param_2, code *param_3,
 *                            undefined8 param_4)
 * When param_2==8, copies the single 8-byte word at param_1 into a local and
 * passes it to the callback. Returns (param_2==8).
 * Confidence: medium */
bool sk_r46_copy8(uint64_t *src, long len, sk_fp_t cb, uint64_t ctx)
{
    uint64_t v = 0;
    if (len == 8) {
        if (src + 1 < src) __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x651b7c) */
        v = *src;
        cb(ctx, &v);
    }
    return len == 8;
}

/* FUN_00651c14 @ 0x00651c14   (est. sk_r46_metadata_copy16)
 * Ghidra: long FUN_00651c14(undefined8 param_1, long param_2, long *param_3,
 *                            ushort *param_4, ulong param_5)
 * Iterates 16-byte metadata entries at param_4, resolves each to its destination
 * address via param_3 and writes the pointer into the entry. Returns the count.
 * Confidence: low
 * Notes: SoftwareBreakpoint(0x5519,0x651e80); FUN_0067b280 fatal */
long sk_r46_metadata_copy16(uint64_t a, long src, long *dst, uint16_t *in, uint64_t len)
{
    long total = 0;
    if (len >= 0x10) {
        uint64_t n = len >> 4;
        uint16_t *p = in;
        for (uint64_t i = 0; i < n; i++) {
            uint64_t v = 0;
            if (p < in || (uint16_t *)((long)in + len) < p + 8) {
                __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x651e80) */
            }
            uint64_t hdr = (uint64_t)(uint8_t)p[1] << 0x10 |
                           (uint64_t)*(uint8_t *)((long)p + 3) << 0x18 | (uint64_t)*p |
                           (uint64_t)((uint32_t)(uint8_t)p[3] << 0x10 |
                                      (uint32_t)*(uint8_t *)((long)p + 7) << 0x18 |
                                      (uint32_t)p[2]) << 0x20;
            uint64_t cnt = 0;
            int ok;
            if (src == 0) {
                ok = (int)sk_r46_record_iterate(0, v, 8, &cnt);
                if (ok != 0) goto have;
            } else {
                uint64_t r = sk_r46_record_iterate((uint16_t *)src, v, 8, &cnt);
                if ((r & 1) != 0) {
have:
                    uint16_t *el = (uint16_t *)sk_r46_metadata_record_element((uint16_t *)src, cnt);
                    if (el != 0 &&
                        ((uint64_t)(uint8_t)el[1] << 0x10 |
                         (uint64_t)*(uint8_t *)((long)el + 3) << 0x18 | (uint64_t)*el |
                         (uint64_t)((uint32_t)(uint8_t)el[3] << 0x10 |
                                    (uint32_t)*(uint8_t *)((long)el + 7) << 0x18 |
                                    (uint32_t)el[2]) << 0x20) == hdr) {
                        if (*(uint8_t *)((long)el + 0xf) >> 2 != 0) FUN_0067b280(0x6a576b);
                        uint64_t ea = ((uint64_t)(uint8_t)el[5] << 0x10 |
                                      (uint64_t)*(uint8_t *)((long)el + 0xb) << 0x18 |
                                      (uint64_t)((uint8_t)*(uint8_t *)((long)el + 9) |
                                                 (uint8_t)el[4]) |
                                      (uint64_t)((uint32_t)(uint8_t)el[7] << 0x10 |
                                                 (uint32_t)*(uint8_t *)((long)el + 0xf) << 0x18 |
                                                 (uint32_t)el[6]) << 0x20) * 0x40;
                        long ea2 = (ea < (uint64_t)dst[1]) ? ea + *dst : 0;
                        *(char *)(p + 4) = (char)ea2;
                        *(char *)((long)p + 0xd) = (char)((uint64_t)ea2 >> 0x28);
                        *(char *)((long)p + 0xb) = (char)((uint64_t)ea2 >> 0x18);
                        *(char *)(p + 5) = (char)((uint64_t)ea2 >> 0x10);
                        *(char *)((long)p + 9) = (char)((uint64_t)ea2 >> 8);
                        *(char *)(p + 6) = (char)((uint64_t)ea2 >> 0x20);
                        *(char *)((long)p + 0xf) = (char)((uint64_t)ea2 >> 0x38);
                        *(char *)(p + 7) = (char)((uint64_t)ea2 >> 0x30);
                        total++;
                    }
                }
            }
            p += 8;
        }
    }
    return total;
}

/* FUN_00651e8c @ 0x00651e8c   (est. sk_r46_metadata_bind18)
 * Ghidra: long FUN_00651e8c(undefined8 param_1, long param_2, long *param_3,
 *                            undefined1 *param_4, ulong param_5)
 * Binds 0x18-byte metadata entries: for each, resolves the destination address
 * (0x6b5f28 element size * 0x40), maps a page via the 0x11-tagged
 * CallSupervisor(0) path, and writes the bound record into the output entry.
 * Returns the count of bound entries.
 * Confidence: low
 * Notes: SoftwareBreakpoint(0x5519,0x6521f4); FUN_0067b280 fatal */
long sk_r46_metadata_bind18(uint64_t a, long src, long *dst, uint8_t *out, uint64_t len)
{
    long total = 0;
    if (len >= 0x18) {
        uint64_t n = len / 0x18;
        uint8_t *p = out;
        for (uint64_t i = 0; i < n; i++) {
            long src2 = src;
            if (src == 0) src2 = 0;
            uint64_t cnt = sk_r46_record_count((uint16_t *)src2);
            uint16_t *el;
            if (cnt != 0 && (el = (uint16_t *)sk_r46_metadata_record_element((uint16_t *)src2, 0)) != 0) {
                if (*(uint8_t *)((long)el + 0x17) >> 2 != 0) FUN_0067b280(0x6a576b);
                uint64_t ea = ((uint64_t)(uint8_t)el[0x12] << 0x10 |
                               (uint64_t)(uint8_t)el[0x13] << 0x18 |
                               (uint64_t)((uint8_t)el[0x11] | (uint8_t)el[0x10]) |
                               (uint64_t)((uint32_t)(uint8_t)el[0x16] << 0x10 |
                                          (uint32_t)(uint8_t)el[0x17] << 0x18 |
                                          (uint32_t)*(uint16_t *)(el + 0x14)) << 0x20) * 0x40;
                long addr = (ea < (uint64_t)dst[1]) ? ea + *dst : 0;
                uint16_t sz = *(uint16_t *)(el + 8);
                uint8_t b2 = el[0xb], b3 = el[10];
                uint16_t sz2 = *(uint16_t *)(el + 0xc);
                uint8_t b4 = el[0xf], b5 = el[0xe];
                uint64_t span = (((uint64_t)b3 << 0x10 | (uint64_t)b2 << 0x18 | (uint64_t)sz |
                                  (uint64_t)((uint32_t)b5 << 0x10 | (uint32_t)b4 << 0x18 |
                                             (uint32_t)sz2) << 0x20) + 0x3fff) & ~0x3fffULL;
                uint8_t req[16];
                SK_MSG_STORE(req, 0, 0x11);
                SK_MSG_STORE(req, 1, 9);
                uint64_t lo = 0, hi = 0;
                sk_pair_t ctx = FUN_0066a8c4();
                uint64_t st = ((sk_fp_t)(ctx.hi + 0x30))(ctx.lo, 0x1800, req, &lo, 0, 0);
                if ((st & 0xff) != 0) {
                    FUN_0065c2f0(0, 0x6a5a23);
                    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x6521f4) */
                }
                FUN_00652e34(addr, lo, hi, span);
                if (hi == 0) FUN_0065558c();
                ((sk_fp_t)(hi + 8))(lo, req);
                if (p < out || out + len < p + 0x18) {
                    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x6521f4) */
                }
                p[0] = (uint8_t)req[8];
                p[1] = (uint8_t)(req[8] >> 8);
                p[8] = (uint8_t)sz;
                p[9] = (uint8_t)(sz >> 8);
                p[10] = b3;
                p[11] = b2;
                p[12] = (uint8_t)sz2;
                p[13] = (uint8_t)(sz2 >> 8);
                p[14] = b5;
                p[15] = b4;
                p[0x10] = el[0x10]; p[0x11] = el[0x11];
                p[0x12] = el[0x12]; p[0x13] = el[0x13];
                p[0x14] = el[0x14]; p[0x15] = el[0x15];
                p[0x16] = el[0x16]; p[0x17] = el[0x17];
                total++;
            }
            p += 0x18;
        }
    }
    return total;
}

/* FUN_00652204 @ 0x00652204   (est. sk_r46_has_prespec)
 * Ghidra: bool FUN_00652204(void)
 * Returns whether the current image has prespecialization metadata registered
 * (both the +0x78 and +0xa8 bases and the +0xb0 size are nonzero).
 * Confidence: medium
 * Notes: FUN_00655848 image state; SoftwareBreakpoint(0x5519,0x652254) */
bool sk_r46_has_prespec(void)
{
    uint64_t st = (uint64_t)FUN_00655848();
    if (st <= st + 0x160) {
        if (*(long *)(st + 0x78) == 0 || *(long *)(st + 0xa8) == 0) return false;
        return *(long *)(st + 0xb0) != 0;
    }
    __builtin_unreachable(); /* SoftwareBreakpoint(0x5519,0x652254) */
}
