/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 10: 0x348074-0x349abc syscall/exception-entry region.
 * All names are estimates unless string/header-matched.
 * Uses seL4/cL4 vocabulary (TCB, cap, CNode, IPC, notification, endpoint,
 * vspace, sched, syscall, trap). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helper declarations (declared extern
 * with a one-line note; their bodies are reconstructed by the range
 * worker that owns them).
 * ------------------------------------------------------------------ */
extern uint64_t FUN_00027754(void);                 /* region 0x0002xxxx */
extern uint64_t FUN_0008f6c0(void);                 /* region 0x0008xxxx */
extern uint64_t FUN_0008f6f4(void);                 /* region 0x0008xxxx */
extern void FUN_0006a4c0(uint64_t, uint64_t);       /* region 0x0006xxxx */
extern void FUN_000a649c(uint64_t);                 /* region 0x000axxxx */
extern void FUN_0017e880(void);                     /* region 0x0017xxxx */
extern void FUN_0016186c(void);                     /* region 0x0016xxxx */
extern void FUN_00291ee0(void);                     /* region 0x0029xxxx */
extern void FUN_0020c7fc(void);                     /* region 0x0020xxxx */
extern void FUN_00310a44(void);                     /* in-range, other slice */
extern void FUN_003109b4(void);                     /* in-range, other slice */
extern void FUN_00310ad4(void);                     /* in-range, other slice */
extern void FUN_0036993c(uint64_t, uint64_t, uint64_t, uint64_t); /* in-range, other slice */
extern void FUN_001afa84(uint64_t, uint64_t, uint64_t, uint64_t,
                         uint64_t, const char *, uint64_t, uint64_t)
    __attribute__((noreturn));                      /* Swift runtime fatalError, region 0x001axxxx */

/* String/type-metadata artifacts referenced by this slice. */
extern const char sk_fatal_error_str[];             /* s_Fatal_error_005accd0 @ 0x005accd0 */
extern const char sk_swift_codable_str[];           /* s_Swift_Codable_swift_005ce990 @ 0x005ce990 */
extern const char sk_swift_existcoll_str[];         /* s_Swift_ExistentialCollection_swif_005cf680 @ 0x005cf680 */


/*--------------------------------------------------------------------*/
/* FUN_00348074 @ 0x00348074   (est. sk_fatal_error_result_01)
 * Ghidra: FUN_00348074(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_01(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003480ac @ 0x003480ac   (est. sk_fatal_error_result_02)
 * Ghidra: FUN_003480ac(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_02(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003480e4 @ 0x003480e4   (est. sk_fatal_error_result_03)
 * Ghidra: FUN_003480e4(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_03(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348128 @ 0x00348128   (est. sk_fatal_error_result_04)
 * Ghidra: FUN_00348128(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_04(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348160 @ 0x00348160   (est. sk_fatal_error_result_05)
 * Ghidra: FUN_00348160(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_05(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348194 @ 0x00348194   (est. sk_fatal_error_result_06)
 * Ghidra: FUN_00348194(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_06(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003481cc @ 0x003481cc   (est. sk_fatal_error_result_07)
 * Ghidra: FUN_003481cc(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_07(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003481fc @ 0x003481fc   (est. sk_fatal_error_result_08)
 * Ghidra: FUN_003481fc(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_08(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348244 @ 0x00348244   (est. sk_fatal_error_result_09)
 * Ghidra: FUN_00348244(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_09(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348284 @ 0x00348284   (est. sk_fatal_error_result_10)
 * Ghidra: FUN_00348284(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_10(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003482c4 @ 0x003482c4   (est. sk_fatal_error_result_11)
 * Ghidra: FUN_003482c4(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_11(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348304 @ 0x00348304   (est. sk_fatal_error_result_12)
 * Ghidra: FUN_00348304(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_12(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0034834c @ 0x0034834c   (est. sk_fatal_error_result_13)
 * Ghidra: FUN_0034834c(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_13(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348384 @ 0x00348384   (est. sk_fatal_error_result_14)
 * Ghidra: FUN_00348384(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_14(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003483c4 @ 0x003483c4   (est. sk_fatal_error_result_15)
 * Ghidra: FUN_003483c4(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_15(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348404 @ 0x00348404   (est. sk_fatal_error_result_16)
 * Ghidra: FUN_00348404(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_16(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0034843c @ 0x0034843c   (est. sk_fatal_error_result_17)
 * Ghidra: FUN_0034843c(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_17(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0034846c @ 0x0034846c   (est. sk_fatal_error_result_18)
 * Ghidra: FUN_0034846c(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_18(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003484b4 @ 0x003484b4   (est. sk_fatal_error_result_19)
 * Ghidra: FUN_003484b4(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_19(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003484e4 @ 0x003484e4   (est. sk_fatal_error_msg_01)
 * Ghidra: FUN_003484e4(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_01(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00348508 @ 0x00348508   (est. sk_fatal_error_result_20)
 * Ghidra: FUN_00348508(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_20(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348548 @ 0x00348548   (est. sk_fatal_error_result_21)
 * Ghidra: FUN_00348548(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_21(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348588 @ 0x00348588   (est. sk_fatal_error_result_22)
 * Ghidra: FUN_00348588(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_22(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003485b8 @ 0x003485b8   (est. sk_fatal_error_result_23)
 * Ghidra: FUN_003485b8(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_23(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003485f0 @ 0x003485f0   (est. sk_fatal_error_msg_02)
 * Ghidra: FUN_003485f0(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_02(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00348614 @ 0x00348614   (est. sk_fatal_error_msg_03)
 * Ghidra: FUN_00348614(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_03(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00348638 @ 0x00348638   (est. sk_fatal_error_msg_04)
 * Ghidra: FUN_00348638(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_04(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_0034865c @ 0x0034865c   (est. sk_fatal_error_msg_05)
 * Ghidra: FUN_0034865c(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_05(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00348680 @ 0x00348680   (est. sk_fatal_error_result_24)
 * Ghidra: FUN_00348680(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_24(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003486b8 @ 0x003486b8   (est. sk_fatal_error_msg_06)
 * Ghidra: FUN_003486b8(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_06(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_003486d8 @ 0x003486d8   (est. sk_inout_buffer_01)
 * Ghidra: FUN_003486d8(void)
 * Swift inout/result-buffer accessor: returns a 16-byte {buffer, metadata}
 * pair pointing at a caller frame slot (x29-0x58) with metadata 0x677880.
 * Confidence: medium.
 * Notes: uses unaff_x29; high word 0x677880 (type info). */
cl4_result_t sk_inout_buffer_01(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)__builtin_frame_address(0)-0x58;  /* x29-0x58 */
    r.hi = 0x677880;  /* type metadata */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003486fc @ 0x003486fc   (est. sk_noop_01)
 * Ghidra: FUN_003486fc(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_01(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348718 @ 0x00348718   (est. sk_type_metadata_01)
 * Ghidra: FUN_00348718(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004e8268.
 * Confidence: medium.
 * Notes: returns &DAT_004e8268. */
void *sk_type_metadata_01(void) { return (void *)0x004e8268; }  /* DAT_004e8268 */

/*--------------------------------------------------------------------*/
/* FUN_00348730 @ 0x00348730   (est. sk_register_metadata_pair)
 * Ghidra: FUN_00348730(void)
 * Registers a pair of type metadata descriptors (0x672b20, 0x66b2e0) with
 * zero extra flags/args via the in-range registration helper FUN_0036993c.
 * Swift conformance/registration leaf.
 * Confidence: medium.
 * Notes: callee FUN_0036993c(0x672b20, 0x66b2e0, 0, 0). */
void sk_register_metadata_pair(void)
{
    FUN_0036993c(0x672b20, 0x66b2e0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00348758 @ 0x00348758   (est. sk_fatal_codable_58)
 * Ghidra: FUN_00348758(ulong param_1)
 * Swift runtime fatal-error trap for "Swift.Codable": does not return. Raises
 * Swift.fatalError (FUN_001afa84) with the "Fatal error" message, code 0xb,
 * kind 0xd000000000000034, and a Swift.Codable accessor field at 0x13.
 * Confidence: high (Swift type string matched).
 * Notes: WARNING: subroutine does not return; refs s_Swift_Codable_swift_005ce990; calls FUN_001afa84. */
void sk_fatal_codable_58(uint64_t idx)
{
    /* FUN_001afa84 is the Swift runtime fatalError (noreturn). */
    FUN_001afa84((uint64_t)&sk_fatal_error_str, 0xb, 2, 0xd000000000000034,
                 idx | 0x8000000000000000ull, &sk_swift_codable_str[0], 0x13, 2);
}

/*--------------------------------------------------------------------*/
/* FUN_0034878c @ 0x0034878c   (est. sk_noop_02)
 * Ghidra: FUN_0034878c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_02(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003487a4 @ 0x003487a4   (est. sk_fatal_error_result_25)
 * Ghidra: FUN_003487a4(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_25(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003487d4 @ 0x003487d4   (est. sk_fatal_error_msg_07)
 * Ghidra: FUN_003487d4(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_07(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_003487f8 @ 0x003487f8   (est. sk_fatal_error_msg_08)
 * Ghidra: FUN_003487f8(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_08(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_0034883c @ 0x0034883c   (est. sk_fatal_error_result_26)
 * Ghidra: FUN_0034883c(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_26(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0034887c @ 0x0034887c   (est. sk_noop_03)
 * Ghidra: FUN_0034887c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_03(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348898 @ 0x00348898   (est. sk_fatal_error_msg_09)
 * Ghidra: FUN_00348898(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_09(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_003488bc @ 0x003488bc   (est. sk_fatal_error_msg_10)
 * Ghidra: FUN_003488bc(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_10(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_003488d8 @ 0x003488d8   (est. sk_fatal_error_msg_11)
 * Ghidra: FUN_003488d8(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_11(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_003488f4 @ 0x003488f4   (est. sk_noop_04)
 * Ghidra: FUN_003488f4(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_04(void) { }

/*--------------------------------------------------------------------*/
/* FUN_0034890c @ 0x0034890c   (est. sk_fatal_error_result_27)
 * Ghidra: FUN_0034890c(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_27(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0034893c @ 0x0034893c   (est. sk_noop_05)
 * Ghidra: FUN_0034893c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_05(void) { }

/*--------------------------------------------------------------------*/
/* FUN_0034895c @ 0x0034895c   (est. sk_noop_06)
 * Ghidra: FUN_0034895c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_06(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348974 @ 0x00348974   (est. sk_fatal_error_msg_12)
 * Ghidra: FUN_00348974(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_12(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00348990 @ 0x00348990   (est. sk_type_metadata_02)
 * Ghidra: FUN_00348990(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004eb028.
 * Confidence: medium.
 * Notes: returns &DAT_004eb028. */
void *sk_type_metadata_02(void) { return (void *)0x004eb028; }  /* DAT_004eb028 */

/*--------------------------------------------------------------------*/
/* FUN_003489a8 @ 0x003489a8   (est. sk_noop_07)
 * Ghidra: FUN_003489a8(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_07(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003489c0 @ 0x003489c0   (est. sk_noop_08)
 * Ghidra: FUN_003489c0(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_08(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003489dc @ 0x003489dc   (est. sk_fatal_error_msg_13)
 * Ghidra: FUN_003489dc(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_13(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_003489fc @ 0x003489fc   (est. sk_fatal_error_msg_14)
 * Ghidra: FUN_003489fc(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_14(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00348a18 @ 0x00348a18   (est. sk_noop_09)
 * Ghidra: FUN_00348a18(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_09(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348a34 @ 0x00348a34   (est. sk_noop_10)
 * Ghidra: FUN_00348a34(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_10(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348a50 @ 0x00348a50   (est. sk_type_metadata_03)
 * Ghidra: FUN_00348a50(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004eaae4.
 * Confidence: medium.
 * Notes: returns &DAT_004eaae4. */
void *sk_type_metadata_03(void) { return (void *)0x004eaae4; }  /* DAT_004eaae4 */

/*--------------------------------------------------------------------*/
/* FUN_00348a68 @ 0x00348a68   (est. sk_init_vtable)
 * Ghidra: FUN_00348a68(undefined8 param_1)
 * Initialises an object context: stores value at ctx[3] (offset 0x18) and
 * sets the vtable/type slot ctx[4] (offset 0x20) to DAT_004f1628.
 * Confidence: medium.
 * Notes: uses unaff_x20 (this); &DAT_004f1628. */
void sk_init_vtable(void *ctx, void *value)
{
    ((void **)ctx)[3] = value;           /* +0x18 */
    ((void **)ctx)[4] = (void *)0x4f1628; /* +0x20, DAT_004f1628 */
}

/*--------------------------------------------------------------------*/
/* FUN_00348a80 @ 0x00348a80   (est. sk_noop_11)
 * Ghidra: FUN_00348a80(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_11(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348a9c @ 0x00348a9c   (est. sk_stack_alloc_01)
 * Ghidra: FUN_00348a9c(long param_1)
 * Stack-buffer allocation helper: rounds size up to 16 bytes and records the
 * resulting stack pointer into a caller frame slot (x29-0x78). Swift
 * alloca-style primitive for temporary scratch buffers.
 * Confidence: medium.
 * Notes: uses unaff_x29 and &stack0. */
void sk_stack_alloc_01(uint64_t size)
{
    uint64_t aligned = (size + 0xfU) & ~0xfU;
    *(uint64_t *)((uint64_t)__builtin_frame_address(0)-0x78) =
        (uint64_t)__builtin_frame_address(0) - aligned;  /* &stack0 - aligned */
}

/*--------------------------------------------------------------------*/
/* FUN_00348abc @ 0x00348abc   (est. sk_noop_12)
 * Ghidra: FUN_00348abc(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_12(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348ad8 @ 0x00348ad8   (est. sk_type_metadata_04)
 * Ghidra: FUN_00348ad8(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004eb078.
 * Confidence: medium.
 * Notes: returns &DAT_004eb078. */
void *sk_type_metadata_04(void) { return (void *)0x004eb078; }  /* DAT_004eb078 */

/*--------------------------------------------------------------------*/
/* FUN_00348af4 @ 0x00348af4   (est. sk_inout_buffer_02)
 * Ghidra: FUN_00348af4(void)
 * Swift inout/result-buffer accessor: returns a 16-byte {buffer, metadata}
 * pair pointing at a caller frame slot (x29-0x58) with metadata 0x677880.
 * Confidence: medium.
 * Notes: uses unaff_x29; high word 0x677880 (type info). */
cl4_result_t sk_inout_buffer_02(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)__builtin_frame_address(0)-0x58;  /* x29-0x58 */
    r.hi = 0x677880;  /* type metadata */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348b1c @ 0x00348b1c   (est. sk_wrap_0020c7fc_1c)
 * Ghidra: FUN_00348b1c(void)
 * Thin wrapper that tail-calls FUN_0020c7fc and returns.
 * Confidence: medium.
 * Notes: single callee FUN_0020c7fc. */
void sk_wrap_0020c7fc_1c(void) { FUN_0020c7fc(); }

/*--------------------------------------------------------------------*/
/* FUN_00348b40 @ 0x00348b40   (est. sk_fatal_error_msg_15)
 * Ghidra: FUN_00348b40(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_15(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00348b5c @ 0x00348b5c   (est. sk_stack_alloc_02)
 * Ghidra: FUN_00348b5c(long param_1)
 * Stack-buffer allocation helper: rounds size up to 16 bytes and records the
 * resulting stack pointer into a caller frame slot (x29-0xa0). Swift
 * alloca-style primitive for temporary scratch buffers.
 * Confidence: medium.
 * Notes: uses unaff_x29 and &stack0. */
void sk_stack_alloc_02(uint64_t size)
{
    uint64_t aligned = (size + 0xfU) & ~0xfU;
    *(uint64_t *)((uint64_t)__builtin_frame_address(0)-0xa0) =
        (uint64_t)__builtin_frame_address(0) - aligned;  /* &stack0 - aligned */
}

/*--------------------------------------------------------------------*/
/* FUN_00348b7c @ 0x00348b7c   (est. sk_fatal_error_msg_16)
 * Ghidra: FUN_00348b7c(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_16(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00348b94 @ 0x00348b94   (est. sk_result_from_fn)
 * Ghidra: FUN_00348b94(void)
 * Returns the {lo,hi} result pair {FUN_00027754(), 0}: packs the return of
 * the out-of-range helper FUN_00027754 into the low word with a zero high.
 * Confidence: medium.
 * Notes: callee FUN_00027754. */
cl4_result_t sk_result_from_fn(void)
{
    cl4_result_t r;
    r.lo = FUN_00027754();
    r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348bbc @ 0x00348bbc   (est. sk_noop_13)
 * Ghidra: FUN_00348bbc(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_13(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348bd8 @ 0x00348bd8   (est. sk_stack_alloc_03)
 * Ghidra: FUN_00348bd8(long param_1)
 * Stack-buffer allocation helper: rounds size up to 16 bytes and records the
 * resulting stack pointer into a caller frame slot (x29-0x80). Swift
 * alloca-style primitive for temporary scratch buffers.
 * Confidence: medium.
 * Notes: uses unaff_x29 and &stack0. */
void sk_stack_alloc_03(uint64_t size)
{
    uint64_t aligned = (size + 0xfU) & ~0xfU;
    *(uint64_t *)((uint64_t)__builtin_frame_address(0)-0x80) =
        (uint64_t)__builtin_frame_address(0) - aligned;  /* &stack0 - aligned */
}

/*--------------------------------------------------------------------*/
/* FUN_00348bf8 @ 0x00348bf8   (est. sk_word_to_result)
 * Ghidra: FUN_00348bf8(ulong param_1)
 * Packs a single word value into the low word of a {lo,hi} result with a
 * zero high word. Swift word->result coercion helper.
 * Confidence: medium.
 * Notes: auVar1 << 0x40 with hi=0. */
cl4_result_t sk_word_to_result(uint64_t value)
{
    cl4_result_t r;
    r.lo = value;
    r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348c18 @ 0x00348c18   (est. sk_fatal_error_msg_17)
 * Ghidra: FUN_00348c18(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_17(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00348c30 @ 0x00348c30   (est. sk_type_metadata_05)
 * Ghidra: FUN_00348c30(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004eaac8.
 * Confidence: medium.
 * Notes: returns &DAT_004eaac8. */
void *sk_type_metadata_05(void) { return (void *)0x004eaac8; }  /* DAT_004eaac8 */

/*--------------------------------------------------------------------*/
/* FUN_00348c48 @ 0x00348c48   (est. sk_load_global_16)
 * Ghidra: FUN_00348c48(void)
 * Loads and returns the 16-byte global value at DAT_006adf10 as a
 * {lo,hi} result pair.
 * Confidence: medium.
 * Notes: returns _DAT_006adf10. */
cl4_result_t sk_load_global_16(void) { return *(cl4_result_t *)(uintptr_t)0x6adf10; }

/*--------------------------------------------------------------------*/
/* FUN_00348c64 @ 0x00348c64   (est. sk_noop_14)
 * Ghidra: FUN_00348c64(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_14(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348c84 @ 0x00348c84   (est. sk_call3_84)
 * Ghidra: FUN_00348c84(void)
 * Calls FUN_00310ad4(), FUN_00027754() then FUN_0016186c() and returns.
 * Confidence: medium.
 * Notes: fixed 3-callee sequence. */
void sk_call3_84(void) { FUN_00310ad4(); FUN_00027754(); FUN_0016186c(); }

/*--------------------------------------------------------------------*/
/* FUN_00348ca8 @ 0x00348ca8   (est. sk_call3_a8)
 * Ghidra: FUN_00348ca8(void)
 * Calls FUN_00310ad4(), FUN_00027754() then FUN_0016186c() and returns.
 * Confidence: medium.
 * Notes: fixed 3-callee sequence. */
void sk_call3_a8(void) { FUN_00310ad4(); FUN_00027754(); FUN_0016186c(); }

/*--------------------------------------------------------------------*/
/* FUN_00348cd0 @ 0x00348cd0   (est. sk_noop_15)
 * Ghidra: FUN_00348cd0(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_15(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348ce8 @ 0x00348ce8   (est. sk_noop_16)
 * Ghidra: FUN_00348ce8(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_16(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348d00 @ 0x00348d00   (est. sk_type_metadata_06)
 * Ghidra: FUN_00348d00(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004e8400.
 * Confidence: medium.
 * Notes: returns &DAT_004e8400. */
void *sk_type_metadata_06(void) { return (void *)0x004e8400; }  /* DAT_004e8400 */

/*--------------------------------------------------------------------*/
/* FUN_00348d18 @ 0x00348d18   (est. sk_type_metadata_07)
 * Ghidra: FUN_00348d18(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004e956c.
 * Confidence: medium.
 * Notes: returns &DAT_004e956c. */
void *sk_type_metadata_07(void) { return (void *)0x004e956c; }  /* DAT_004e956c */

/*--------------------------------------------------------------------*/
/* FUN_00348d30 @ 0x00348d30   (est. sk_noop_17)
 * Ghidra: FUN_00348d30(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_17(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348d4c @ 0x00348d4c   (est. sk_noop_18)
 * Ghidra: FUN_00348d4c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_18(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348d64 @ 0x00348d64   (est. sk_noop_19)
 * Ghidra: FUN_00348d64(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_19(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348d7c @ 0x00348d7c   (est. sk_noop_20)
 * Ghidra: FUN_00348d7c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_20(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348d94 @ 0x00348d94   (est. sk_zero_01)
 * Ghidra: FUN_00348d94(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_01(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_00348dac @ 0x00348dac   (est. sk_fatal_error_result_28)
 * Ghidra: FUN_00348dac(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_28(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348dd8 @ 0x00348dd8   (est. sk_zero_02)
 * Ghidra: FUN_00348dd8(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_02(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_00348e00 @ 0x00348e00   (est. sk_noop_21)
 * Ghidra: FUN_00348e00(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_21(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348e18 @ 0x00348e18   (est. sk_noop_22)
 * Ghidra: FUN_00348e18(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_22(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348e30 @ 0x00348e30   (est. sk_word_to_result_b)
 * Ghidra: FUN_00348e30(ulong param_1)
 * Same as FUN_00348bf8: packs value into {lo,0}.
 * Confidence: medium.
 * Notes: auVar1 << 0x40 with hi=0. */
cl4_result_t sk_word_to_result_b(uint64_t value)
{
    cl4_result_t r;
    r.lo = value;
    r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348e48 @ 0x00348e48   (est. sk_range_describe)
 * Ghidra: FUN_00348e48(long param_1,long param_2,long param_3)
 * Describes a half-open range: returns {lo, hi} where lo is the computed
 * end bound (count ? count+start : 0) and hi is the length (end-start).
 * Swift Range/CountableRange representation helper.
 * Confidence: medium.
 * Notes: pure arithmetic, no calls. */
cl4_result_t sk_range_describe(int64_t start, int64_t end, int64_t count)
{
    cl4_result_t r;
    r.lo = count ? (uint64_t)(count + start) : 0;
    r.hi = (uint64_t)(end - start);
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348e60 @ 0x00348e60   (est. sk_noop_23)
 * Ghidra: FUN_00348e60(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_23(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348e78 @ 0x00348e78   (est. sk_call3_78)
 * Ghidra: FUN_00348e78(void)
 * Calls FUN_00310ad4(), FUN_00027754() then FUN_0016186c() and returns.
 * Confidence: medium.
 * Notes: fixed 3-callee sequence. */
void sk_call3_78(void) { FUN_00310ad4(); FUN_00027754(); FUN_0016186c(); }

/*--------------------------------------------------------------------*/
/* FUN_00348e9c @ 0x00348e9c   (est. sk_noop_24)
 * Ghidra: FUN_00348e9c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_24(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348eb4 @ 0x00348eb4   (est. sk_type_metadata_08)
 * Ghidra: FUN_00348eb4(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004f0e38.
 * Confidence: medium.
 * Notes: returns &DAT_004f0e38. */
void *sk_type_metadata_08(void) { return (void *)0x004f0e38; }  /* DAT_004f0e38 */

/*--------------------------------------------------------------------*/
/* FUN_00348ecc @ 0x00348ecc   (est. sk_inout_buffer_03)
 * Ghidra: FUN_00348ecc(void)
 * Swift inout/result-buffer accessor: returns a 16-byte {buffer, metadata}
 * pair pointing at a caller frame slot (x29-0x58) with metadata 0x677880.
 * Confidence: medium.
 * Notes: uses unaff_x29; high word 0x677880 (type info). */
cl4_result_t sk_inout_buffer_03(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)__builtin_frame_address(0)-0x58;  /* x29-0x58 */
    r.hi = 0x677880;  /* type metadata */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348ee4 @ 0x00348ee4   (est. sk_fatal_error_result_29)
 * Ghidra: FUN_00348ee4(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_29(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00348f14 @ 0x00348f14   (est. sk_wrap_00027754_14)
 * Ghidra: FUN_00348f14(void)
 * Thin wrapper that tail-calls FUN_00027754 and returns.
 * Confidence: medium.
 * Notes: single callee FUN_00027754. */
void sk_wrap_00027754_14(void) { FUN_00027754(); }

/*--------------------------------------------------------------------*/
/* FUN_00348f38 @ 0x00348f38   (est. sk_noop_25)
 * Ghidra: FUN_00348f38(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_25(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348f50 @ 0x00348f50   (est. sk_noop_26)
 * Ghidra: FUN_00348f50(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_26(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348f68 @ 0x00348f68   (est. sk_noop_27)
 * Ghidra: FUN_00348f68(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_27(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348fb4 @ 0x00348fb4   (est. sk_type_metadata_09)
 * Ghidra: FUN_00348fb4(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004c1010.
 * Confidence: medium.
 * Notes: returns &DAT_004c1010. */
void *sk_type_metadata_09(void) { return (void *)0x004c1010; }  /* DAT_004c1010 */

/*--------------------------------------------------------------------*/
/* FUN_00348fd8 @ 0x00348fd8   (est. sk_noop_28)
 * Ghidra: FUN_00348fd8(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_28(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00348ff0 @ 0x00348ff0   (est. sk_wrap_00310a44_f0)
 * Ghidra: FUN_00348ff0(void)
 * Thin wrapper that tail-calls FUN_00310a44 and returns.
 * Confidence: medium.
 * Notes: single callee FUN_00310a44. */
void sk_wrap_00310a44_f0(void) { FUN_00310a44(); }

/*--------------------------------------------------------------------*/
/* FUN_00349018 @ 0x00349018   (est. sk_wrap_003109b4_18)
 * Ghidra: FUN_00349018(void)
 * Thin wrapper that tail-calls FUN_003109b4 and returns.
 * Confidence: medium.
 * Notes: single callee FUN_003109b4. */
void sk_wrap_003109b4_18(void) { FUN_003109b4(); }

/*--------------------------------------------------------------------*/
/* FUN_00349040 @ 0x00349040   (est. sk_wrap_003109b4_40)
 * Ghidra: FUN_00349040(void)
 * Thin wrapper that tail-calls FUN_003109b4 and returns.
 * Confidence: medium.
 * Notes: single callee FUN_003109b4. */
void sk_wrap_003109b4_40(void) { FUN_003109b4(); }

/*--------------------------------------------------------------------*/
/* FUN_00349068 @ 0x00349068   (est. sk_noop_29)
 * Ghidra: FUN_00349068(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_29(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349080 @ 0x00349080   (est. sk_noop_30)
 * Ghidra: FUN_00349080(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_30(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349098 @ 0x00349098   (est. sk_noop_31)
 * Ghidra: FUN_00349098(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_31(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003490b8 @ 0x003490b8   (est. sk_store_frame_slot)
 * Ghidra: FUN_003490b8(long param_1,undefined8 param_2)
 * Stores value into the caller frame slot at base-0x100. Leaf used by the
 * Swift runtime to spill a register into a known frame location.
 * Confidence: medium.
 * Notes: *(base-0x100) = value. */
void sk_store_frame_slot(uint64_t base, uint64_t value)
{
    *(uint64_t *)(base - 0x100) = value;
}

/*--------------------------------------------------------------------*/
/* FUN_003490d0 @ 0x003490d0   (est. sk_noop_32)
 * Ghidra: FUN_003490d0(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_32(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003490ec @ 0x003490ec   (est. sk_noop_33)
 * Ghidra: FUN_003490ec(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_33(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349104 @ 0x00349104   (est. sk_noop_34)
 * Ghidra: FUN_00349104(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_34(void) { }

/*--------------------------------------------------------------------*/
/* FUN_0034911c @ 0x0034911c   (est. sk_noop_35)
 * Ghidra: FUN_0034911c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_35(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349134 @ 0x00349134   (est. sk_metadata_result_01)
 * Ghidra: FUN_00349134(void)
 * Returns the 16-byte {0, 0x677880} pair: low word 0, high word the type
 * metadata 0x677880. Swift result-buffer metadata holder.
 * Confidence: medium.
 * Notes: ZEXT816(0x677880) << 0x40. */
cl4_result_t sk_metadata_result_01(void)
{
    cl4_result_t r;
    r.lo = 0;
    r.hi = 0x677880;  /* type metadata */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00349150 @ 0x00349150   (est. sk_noop_36)
 * Ghidra: FUN_00349150(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_36(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349178 @ 0x00349178   (est. sk_noop_37)
 * Ghidra: FUN_00349178(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_37(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349190 @ 0x00349190   (est. sk_fatal_existcoll_90)
 * Ghidra: FUN_00349190(ulong param_1)
 * Swift runtime fatal-error trap for "Swift.ExistentialCollection": does not return. Raises
 * Swift.fatalError (FUN_001afa84) with the "Fatal error" message, code 0xb,
 * kind 0xd000000000000014, and a Swift.ExistentialCollection accessor field at 0x21.
 * Confidence: high (Swift type string matched).
 * Notes: WARNING: subroutine does not return; refs s_Swift_ExistentialCollection_swif_005cf680; calls FUN_001afa84. */
void sk_fatal_existcoll_90(uint64_t idx)
{
    /* FUN_001afa84 is the Swift runtime fatalError (noreturn). */
    FUN_001afa84((uint64_t)&sk_fatal_error_str, 0xb, 2, 0xd000000000000014,
                 idx | 0x8000000000000000ull, &sk_swift_existcoll_str[0], 0x21, 2);
}

/*--------------------------------------------------------------------*/
/* FUN_003491c4 @ 0x003491c4   (est. sk_call3_c4)
 * Ghidra: FUN_003491c4(void)
 * Calls FUN_00310ad4(), FUN_00027754() then FUN_0016186c() and returns.
 * Confidence: medium.
 * Notes: fixed 3-callee sequence. */
void sk_call3_c4(void) { FUN_00310ad4(); FUN_00027754(); FUN_0016186c(); }

/*--------------------------------------------------------------------*/
/* FUN_003491ec @ 0x003491ec   (est. sk_noop_38)
 * Ghidra: FUN_003491ec(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_38(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349204 @ 0x00349204   (est. sk_type_metadata_10)
 * Ghidra: FUN_00349204(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004ec334.
 * Confidence: medium.
 * Notes: returns &DAT_004ec334. */
void *sk_type_metadata_10(void) { return (void *)0x004ec334; }  /* DAT_004ec334 */

/*--------------------------------------------------------------------*/
/* FUN_0034921c @ 0x0034921c   (est. sk_noop_39)
 * Ghidra: FUN_0034921c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_39(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349234 @ 0x00349234   (est. sk_type_metadata_11)
 * Ghidra: FUN_00349234(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004e8bd0.
 * Confidence: medium.
 * Notes: returns &DAT_004e8bd0. */
void *sk_type_metadata_11(void) { return (void *)0x004e8bd0; }  /* DAT_004e8bd0 */

/*--------------------------------------------------------------------*/
/* FUN_0034924c @ 0x0034924c   (est. sk_noop_40)
 * Ghidra: FUN_0034924c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_40(void) { }

/*--------------------------------------------------------------------*/
/* FUN_0034926c @ 0x0034926c   (est. sk_stack_alloc_04)
 * Ghidra: FUN_0034926c(long param_1)
 * Stack-buffer allocation helper: rounds size up to 16 bytes and records the
 * resulting stack pointer into a caller frame slot (x29-0xf8). Swift
 * alloca-style primitive for temporary scratch buffers.
 * Confidence: medium.
 * Notes: uses unaff_x29 and &stack0. */
void sk_stack_alloc_04(uint64_t size)
{
    uint64_t aligned = (size + 0xfU) & ~0xfU;
    *(uint64_t *)((uint64_t)__builtin_frame_address(0)-0xf8) =
        (uint64_t)__builtin_frame_address(0) - aligned;  /* &stack0 - aligned */
}

/*--------------------------------------------------------------------*/
/* FUN_0034928c @ 0x0034928c   (est. sk_stack_alloc_05)
 * Ghidra: FUN_0034928c(long param_1)
 * Stack-buffer allocation helper: rounds size up to 16 bytes and records the
 * resulting stack pointer into a caller frame slot (x29-0x70). Swift
 * alloca-style primitive for temporary scratch buffers.
 * Confidence: medium.
 * Notes: uses unaff_x29 and &stack0. */
void sk_stack_alloc_05(uint64_t size)
{
    uint64_t aligned = (size + 0xfU) & ~0xfU;
    *(uint64_t *)((uint64_t)__builtin_frame_address(0)-0x70) =
        (uint64_t)__builtin_frame_address(0) - aligned;  /* &stack0 - aligned */
}

/*--------------------------------------------------------------------*/
/* FUN_003492ac @ 0x003492ac   (est. sk_stack_alloc_06)
 * Ghidra: FUN_003492ac(long param_1)
 * Stack-buffer allocation helper: rounds size up to 16 bytes and records the
 * resulting stack pointer into a caller frame slot (x29-0x88). Swift
 * alloca-style primitive for temporary scratch buffers.
 * Confidence: medium.
 * Notes: uses unaff_x29 and &stack0. */
void sk_stack_alloc_06(uint64_t size)
{
    uint64_t aligned = (size + 0xfU) & ~0xfU;
    *(uint64_t *)((uint64_t)__builtin_frame_address(0)-0x88) =
        (uint64_t)__builtin_frame_address(0) - aligned;  /* &stack0 - aligned */
}

/*--------------------------------------------------------------------*/
/* FUN_003492cc @ 0x003492cc   (est. sk_call3_cc)
 * Ghidra: FUN_003492cc(void)
 * Calls FUN_00310ad4(), FUN_00027754() then FUN_0016186c() and returns.
 * Confidence: medium.
 * Notes: fixed 3-callee sequence. */
void sk_call3_cc(void) { FUN_00310ad4(); FUN_00027754(); FUN_0016186c(); }

/*--------------------------------------------------------------------*/
/* FUN_003492f0 @ 0x003492f0   (est. sk_noop_41)
 * Ghidra: FUN_003492f0(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_41(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349308 @ 0x00349308   (est. sk_inout_buffer_04)
 * Ghidra: FUN_00349308(void)
 * Swift inout/result-buffer accessor: returns a 16-byte {buffer, metadata}
 * pair pointing at a caller frame slot (x29-0x60) with metadata 0x677880.
 * Confidence: medium.
 * Notes: uses unaff_x29; high word 0x677880 (type info). */
cl4_result_t sk_inout_buffer_04(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)__builtin_frame_address(0)-0x60;  /* x29-0x60 */
    r.hi = 0x677880;  /* type metadata */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00349330 @ 0x00349330   (est. sk_inout_buffer_05)
 * Ghidra: FUN_00349330(void)
 * Swift inout/result-buffer accessor: returns a 16-byte {buffer, metadata}
 * pair pointing at a caller frame slot (x29-0x60) with metadata 0x677880.
 * Confidence: medium.
 * Notes: uses unaff_x29; high word 0x677880 (type info). */
cl4_result_t sk_inout_buffer_05(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)__builtin_frame_address(0)-0x60;  /* x29-0x60 */
    r.hi = 0x677880;  /* type metadata */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00349358 @ 0x00349358   (est. sk_noop_42)
 * Ghidra: FUN_00349358(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_42(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349370 @ 0x00349370   (est. sk_type_metadata_12)
 * Ghidra: FUN_00349370(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004c1010.
 * Confidence: medium.
 * Notes: returns &DAT_004c1010. */
void *sk_type_metadata_12(void) { return (void *)0x004c1010; }  /* DAT_004c1010 */

/*--------------------------------------------------------------------*/
/* FUN_00349394 @ 0x00349394   (est. sk_zero_03)
 * Ghidra: FUN_00349394(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_03(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_003493ac @ 0x003493ac   (est. sk_noop_43)
 * Ghidra: FUN_003493ac(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_43(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003493c4 @ 0x003493c4   (est. sk_noop_44)
 * Ghidra: FUN_003493c4(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_44(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003493d8 @ 0x003493d8   (est. sk_noop_45)
 * Ghidra: FUN_003493d8(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_45(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003493ec @ 0x003493ec   (est. sk_type_metadata_13)
 * Ghidra: FUN_003493ec(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004c1010.
 * Confidence: medium.
 * Notes: returns &DAT_004c1010. */
void *sk_type_metadata_13(void) { return (void *)0x004c1010; }  /* DAT_004c1010 */

/*--------------------------------------------------------------------*/
/* FUN_00349410 @ 0x00349410   (est. sk_noop_46)
 * Ghidra: FUN_00349410(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_46(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349424 @ 0x00349424   (est. sk_noop_47)
 * Ghidra: FUN_00349424(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_47(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349444 @ 0x00349444   (est. sk_zero_04)
 * Ghidra: FUN_00349444(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_04(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_0034945c @ 0x0034945c   (est. sk_spill_frame_args)
 * Ghidra: FUN_0034945c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5)
 * Spills several argument/register values into caller frame slots
 * (x29-0x48, x29-0x60, x29-0x58, x29-0x68). Leaf register-spill epilogue
 * helper; keeps live values across a Swift ABI boundary.
 * Confidence: medium.
 * Notes: uses unaff_x21 and unaff_x29. */
void sk_spill_frame_args(uint64_t p1, uint64_t p4, uint64_t p5, uint64_t x21)
{
    *(uint64_t *)((uint64_t)__builtin_frame_address(0) - 0x48) = p5;
    *(uint64_t *)((uint64_t)__builtin_frame_address(0) - 0x60) = p4;
    *(uint64_t *)((uint64_t)__builtin_frame_address(0) - 0x58) = x21;
    *(uint64_t *)((uint64_t)__builtin_frame_address(0) - 0x68) = p1;
}

/*--------------------------------------------------------------------*/
/* FUN_0034947c @ 0x0034947c   (est. sk_noop_48)
 * Ghidra: FUN_0034947c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_48(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349494 @ 0x00349494   (est. sk_noop_49)
 * Ghidra: FUN_00349494(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_49(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003494b4 @ 0x003494b4   (est. sk_noop_50)
 * Ghidra: FUN_003494b4(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_50(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003494d4 @ 0x003494d4   (est. sk_fatal_error_msg_18)
 * Ghidra: FUN_003494d4(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_18(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_003494e8 @ 0x003494e8   (est. sk_noop_51)
 * Ghidra: FUN_003494e8(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_51(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003494fc @ 0x003494fc   (est. sk_type_metadata_14)
 * Ghidra: FUN_003494fc(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004c1010.
 * Confidence: medium.
 * Notes: returns &DAT_004c1010. */
void *sk_type_metadata_14(void) { return (void *)0x004c1010; }  /* DAT_004c1010 */

/*--------------------------------------------------------------------*/
/* FUN_0034951c @ 0x0034951c   (est. sk_fatal_error_msg_19)
 * Ghidra: FUN_0034951c(void)
 * Returns a pointer to the "Fatal error" message literal
 * (s_Fatal_error_005accd0). Swift-runtime fatal-message accessor.
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
const char *sk_fatal_error_msg_19(void) { return sk_fatal_error_str; }

/*--------------------------------------------------------------------*/
/* FUN_00349530 @ 0x00349530   (est. sk_noop_52)
 * Ghidra: FUN_00349530(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_52(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349544 @ 0x00349544   (est. sk_call3_44)
 * Ghidra: FUN_00349544(void)
 * Calls FUN_00310ad4(), FUN_00027754() then FUN_0016186c() and returns.
 * Confidence: medium.
 * Notes: fixed 3-callee sequence. */
void sk_call3_44(void) { FUN_00310ad4(); FUN_00027754(); FUN_0016186c(); }

/*--------------------------------------------------------------------*/
/* FUN_00349580 @ 0x00349580   (est. sk_wrap_00291ee0_80)
 * Ghidra: FUN_00349580(void)
 * Thin wrapper that tail-calls FUN_00291ee0 and returns.
 * Confidence: medium.
 * Notes: single callee FUN_00291ee0. */
void sk_wrap_00291ee0_80(void) { FUN_00291ee0(); }

/*--------------------------------------------------------------------*/
/* FUN_003495a8 @ 0x003495a8   (est. sk_wrap_00291ee0_a8)
 * Ghidra: FUN_003495a8(void)
 * Thin wrapper that tail-calls FUN_00291ee0 and returns.
 * Confidence: medium.
 * Notes: single callee FUN_00291ee0. */
void sk_wrap_00291ee0_a8(void) { FUN_00291ee0(); }

/*--------------------------------------------------------------------*/
/* FUN_003495cc @ 0x003495cc   (est. sk_fatal_error_result_30)
 * Ghidra: FUN_003495cc(void)
 * Builds the cL4 "Fatal error" result: a 16-byte pair whose low word is a
 * pointer to the literal "Fatal error" and whose high word is the code 0xb
 * (the classic seL4 error-pack {message, code}).
 * Confidence: medium.
 * Notes: refs s_Fatal_error_005accd0. */
cl4_result_t sk_fatal_error_result_30(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)&sk_fatal_error_str;  /* s_Fatal_error_005accd0 */
    r.hi = 0xb;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00349600 @ 0x00349600   (est. sk_zero_05)
 * Ghidra: FUN_00349600(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_05(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_00349618 @ 0x00349618   (est. sk_noop_53)
 * Ghidra: FUN_00349618(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_53(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349630 @ 0x00349630   (est. sk_inout_buffer_06)
 * Ghidra: FUN_00349630(void)
 * Swift inout/result-buffer accessor: returns a 16-byte {buffer, metadata}
 * pair pointing at a caller frame slot (x29-0x60) with metadata 0x677880.
 * Confidence: medium.
 * Notes: uses unaff_x29; high word 0x677880 (type info). */
cl4_result_t sk_inout_buffer_06(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)__builtin_frame_address(0)-0x60;  /* x29-0x60 */
    r.hi = 0x677880;  /* type metadata */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00349644 @ 0x00349644   (est. sk_noop_54)
 * Ghidra: FUN_00349644(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_54(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349658 @ 0x00349658   (est. sk_object_finalize)
 * Ghidra: FUN_00349658(long param_1)
 * Finalises an object: saves the word at obj+0x20, releases the field at
 * obj+0x18 through FUN_0006a4c0(obj, field), then releases the saved word
 * through FUN_000a649c. Two-stage Swift/C++ object teardown.
 * Confidence: medium.
 * Notes: callees FUN_0006a4c0, FUN_000a649c. */
void sk_object_finalize(void *obj)
{
    uint64_t v = *(uint64_t *)((uint8_t *)obj + 0x20);
    FUN_0006a4c0((uint64_t)obj, *(uint64_t *)((uint8_t *)obj + 0x18));
    FUN_000a649c(v);
}

/*--------------------------------------------------------------------*/
/* FUN_00349684 @ 0x00349684   (est. sk_result_from_fns)
 * Ghidra: FUN_00349684(void)
 * Calls FUN_0008f6c0(), then packs FUN_0008f6f4() into the low word of a
 * {lo,0} result. Helper that harvests a value after a setup call.
 * Confidence: medium.
 * Notes: callees FUN_0008f6c0, FUN_0008f6f4. */
cl4_result_t sk_result_from_fns(void)
{
    cl4_result_t r;
    FUN_0008f6c0();
    r.lo = FUN_0008f6f4();
    r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_003496b0 @ 0x003496b0   (est. sk_bitset_insert_byte)
 * Ghidra: FUN_003496b0(ulong param_1)
 * Inserts a byte from memory into a bit field: returns
 * ((uint64_t)*byte << (shift & 0x38)) | value. Builds a wide bitmap/flag word
 * from a byte value shifted into a 0-56 bit lane.
 * Confidence: medium.
 * Notes: uses in_x11/in_x12 registers directly. */
uint64_t sk_bitset_insert_byte(uint64_t value, uint64_t shift, const uint8_t *byte)
{
    return (uint64_t)*byte << (shift & 0x38) | value;
}

/*--------------------------------------------------------------------*/
/* FUN_003496cc @ 0x003496cc   (est. sk_noop_55)
 * Ghidra: FUN_003496cc(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_55(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003496e8 @ 0x003496e8   (est. sk_call3_e8)
 * Ghidra: FUN_003496e8(void)
 * Calls FUN_00310ad4(), FUN_00027754() then FUN_0016186c() and returns.
 * Confidence: medium.
 * Notes: fixed 3-callee sequence. */
void sk_call3_e8(void) { FUN_00310ad4(); FUN_00027754(); FUN_0016186c(); }

/*--------------------------------------------------------------------*/
/* FUN_0034970c @ 0x0034970c   (est. sk_inout_buffer_07)
 * Ghidra: FUN_0034970c(void)
 * Swift inout/result-buffer accessor: returns a 16-byte {buffer, metadata}
 * pair pointing at a caller frame slot (x29-0x58) with metadata 0x677880.
 * Confidence: medium.
 * Notes: uses unaff_x29; high word 0x677880 (type info). */
cl4_result_t sk_inout_buffer_07(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)__builtin_frame_address(0)-0x58;  /* x29-0x58 */
    r.hi = 0x677880;  /* type metadata */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00349720 @ 0x00349720   (est. sk_noop_56)
 * Ghidra: FUN_00349720(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_56(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349734 @ 0x00349734   (est. sk_noop_57)
 * Ghidra: FUN_00349734(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_57(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349748 @ 0x00349748   (est. sk_zero_06)
 * Ghidra: FUN_00349748(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_06(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_0034975c @ 0x0034975c   (est. sk_noop_58)
 * Ghidra: FUN_0034975c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_58(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349770 @ 0x00349770   (est. sk_zero_07)
 * Ghidra: FUN_00349770(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_07(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_00349788 @ 0x00349788   (est. sk_zero_08)
 * Ghidra: FUN_00349788(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_08(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_003497a0 @ 0x003497a0   (est. sk_zero_09)
 * Ghidra: FUN_003497a0(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_09(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_003497b4 @ 0x003497b4   (est. sk_noop_59)
 * Ghidra: FUN_003497b4(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_59(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003497c8 @ 0x003497c8   (est. sk_wrap_00291ee0_c8)
 * Ghidra: FUN_003497c8(void)
 * Thin wrapper that tail-calls FUN_00291ee0 and returns.
 * Confidence: medium.
 * Notes: single callee FUN_00291ee0. */
void sk_wrap_00291ee0_c8(void) { FUN_00291ee0(); }

/*--------------------------------------------------------------------*/
/* FUN_003497ec @ 0x003497ec   (est. sk_metadata_result_5be7c0)
 * Ghidra: FUN_003497ec(void)
 * Returns the 16-byte {0x5be7c0, 0} pair: low word the metadata/value
 * 0x5be7c0, high word 0. Swift value-metadata holder.
 * Confidence: medium.
 * Notes: ZEXT816(0x5be7c0). */
cl4_result_t sk_metadata_result_5be7c0(void)
{
    cl4_result_t r;
    r.lo = 0x5be7c0;
    r.hi = 0;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00349800 @ 0x00349800   (est. sk_metadata_result_02)
 * Ghidra: FUN_00349800(void)
 * Returns the 16-byte {0, 0x677880} pair: low word 0, high word the type
 * metadata 0x677880. Swift result-buffer metadata holder.
 * Confidence: medium.
 * Notes: ZEXT816(0x677880) << 0x40. */
cl4_result_t sk_metadata_result_02(void)
{
    cl4_result_t r;
    r.lo = 0;
    r.hi = 0x677880;  /* type metadata */
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00349818 @ 0x00349818   (est. sk_noop_60)
 * Ghidra: FUN_00349818(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_60(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349830 @ 0x00349830   (est. sk_zero_10)
 * Ghidra: FUN_00349830(void)
 * Returns 0. Trivial success/flag constant leaf.
 * Confidence: medium.
 * Notes: constant-0 return. */
uint64_t sk_zero_10(void) { return 0; }

/*--------------------------------------------------------------------*/
/* FUN_00349844 @ 0x00349844   (est. sk_noop_61)
 * Ghidra: FUN_00349844(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_61(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349858 @ 0x00349858   (est. sk_call3_58)
 * Ghidra: FUN_00349858(void)
 * Calls FUN_00310ad4(), FUN_00027754() then FUN_0016186c() and returns.
 * Confidence: medium.
 * Notes: fixed 3-callee sequence. */
void sk_call3_58(void) { FUN_00310ad4(); FUN_00027754(); FUN_0016186c(); }

/*--------------------------------------------------------------------*/
/* FUN_0034987c @ 0x0034987c   (est. sk_noop_62)
 * Ghidra: FUN_0034987c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_62(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349890 @ 0x00349890   (est. sk_noop_63)
 * Ghidra: FUN_00349890(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_63(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003498a8 @ 0x003498a8   (est. sk_noop_64)
 * Ghidra: FUN_003498a8(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_64(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003498c4 @ 0x003498c4   (est. sk_noop_65)
 * Ghidra: FUN_003498c4(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_65(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003498dc @ 0x003498dc   (est. sk_type_metadata_15)
 * Ghidra: FUN_003498dc(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004e8f2c.
 * Confidence: medium.
 * Notes: returns &DAT_004e8f2c. */
void *sk_type_metadata_15(void) { return (void *)0x004e8f2c; }  /* DAT_004e8f2c */

/*--------------------------------------------------------------------*/
/* FUN_003498f4 @ 0x003498f4   (est. sk_noop_66)
 * Ghidra: FUN_003498f4(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_66(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349910 @ 0x00349910   (est. sk_type_metadata_16)
 * Ghidra: FUN_00349910(void)
 * Swift type-metadata accessor: returns a pointer to the type
 * descriptor/metadata record DAT_004e8b98.
 * Confidence: medium.
 * Notes: returns &DAT_004e8b98. */
void *sk_type_metadata_16(void) { return (void *)0x004e8b98; }  /* DAT_004e8b98 */

/*--------------------------------------------------------------------*/
/* FUN_00349928 @ 0x00349928   (est. sk_noop_67)
 * Ghidra: FUN_00349928(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_67(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349944 @ 0x00349944   (est. sk_noop_68)
 * Ghidra: FUN_00349944(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_68(void) { }

/*--------------------------------------------------------------------*/
/* FUN_0034995c @ 0x0034995c   (est. sk_call2_5c)
 * Ghidra: FUN_0034995c(void)
 * Calls FUN_0006a4c0() then FUN_0017e880() and returns.
 * Confidence: medium.
 * Notes: callees ['FUN_0006a4c0', 'FUN_0017e880']. */
void sk_call2_5c(void) { FUN_0006a4c0(0, 0); FUN_0017e880(); }  /* decompiler dropped the 2 args at this call site */

/*--------------------------------------------------------------------*/
/* FUN_0034998c @ 0x0034998c   (est. sk_noop_69)
 * Ghidra: FUN_0034998c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_69(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003499a0 @ 0x003499a0   (est. sk_noop_70)
 * Ghidra: FUN_003499a0(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_70(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003499b4 @ 0x003499b4   (est. sk_noop_71)
 * Ghidra: FUN_003499b4(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_71(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003499c8 @ 0x003499c8   (est. sk_noop_72)
 * Ghidra: FUN_003499c8(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_72(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003499dc @ 0x003499dc   (est. sk_noop_73)
 * Ghidra: FUN_003499dc(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_73(void) { }

/*--------------------------------------------------------------------*/
/* FUN_003499f0 @ 0x003499f0   (est. sk_noop_74)
 * Ghidra: FUN_003499f0(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_74(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349a04 @ 0x00349a04   (est. sk_noop_75)
 * Ghidra: FUN_00349a04(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_75(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349a18 @ 0x00349a18   (est. sk_noop_76)
 * Ghidra: FUN_00349a18(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_76(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349a2c @ 0x00349a2c   (est. sk_noop_77)
 * Ghidra: FUN_00349a2c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_77(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349a40 @ 0x00349a40   (est. sk_noop_78)
 * Ghidra: FUN_00349a40(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_78(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349a54 @ 0x00349a54   (est. sk_noop_79)
 * Ghidra: FUN_00349a54(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_79(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349a68 @ 0x00349a68   (est. sk_noop_80)
 * Ghidra: FUN_00349a68(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_80(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349a7c @ 0x00349a7c   (est. sk_noop_81)
 * Ghidra: FUN_00349a7c(void)
 * Empty no-op stub. Common Swift-runtime padding/unused leaf in the
 * syscall/exception-entry region; performs no work.
 * Confidence: medium.
 * Notes: empty body. */
void sk_noop_81(void) { }

/*--------------------------------------------------------------------*/
/* FUN_00349a9c @ 0x00349a9c   (est. sk_copy_word)
 * Ghidra: FUN_00349a9c(void)
 * Copies a single machine word from one register-held address to another
 * (*dst = *src). Leaf register-to-register word copy.
 * Confidence: medium.
 * Notes: uses unaff_x19/unaff_x20. */
void sk_copy_word(uint64_t *dst, const uint64_t *src)
{
    *dst = *src;
}

/*--------------------------------------------------------------------*/
/* FUN_00349abc @ 0x00349abc   (est. sk_inout_buffer_08)
 * Ghidra: FUN_00349abc(void)
 * Swift inout/result-buffer accessor: returns a 16-byte {buffer, metadata}
 * pair pointing at a caller frame slot (x29-0x60) with metadata 0x677880.
 * Confidence: medium.
 * Notes: uses unaff_x29; high word 0x677880 (type info). */
cl4_result_t sk_inout_buffer_08(void)
{
    cl4_result_t r;
    r.lo = (uint64_t)__builtin_frame_address(0)-0x60;  /* x29-0x60 */
    r.hi = 0x677880;  /* type metadata */
    return r;
}
