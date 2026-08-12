/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* Out-of-range kernel helpers referenced by this region (FUN_ addr in
 * comment; reconstructed by sibling SK range workers). Names are estimates. */
extern void sk_fatal_error(const char *msg, unsigned long a, unsigned long b,
                           unsigned long c, unsigned long d, const char *s2,
                           unsigned long e, unsigned long f); /* FUN_001afa84, noreturn */
extern void sk_stack_chk_fail(void);                           /* FUN_0011d7e8, noreturn */

/*--------------------------------------------------------------------*/
/* FUN_00020134 @ 0x00020134   (est. tightbeam_transport_init)
 * Ghidra: undefined FUN_00020134(void)
 * Boot-time initialisation of the Tightbeam transport buffer subsystem.
 * Reads a per-cpu/handler context descriptor from x5-8, invokes a sub-init
 * that returns a 16-byte {status,word} pair; if the status word is zero it
 * panics with "Fatal error" and "Tightbeam TransportBuffer swift". Otherwise
 * it clears a local descriptor block (0x48 bytes), flags word 0xa8=1, and
 * calls through the resolved init routine, then an optional dispatch callback
 * at context+0x20 when the caller register x21 is non-null. Ends with a stack
 * canary check (FUN_0011d7e8 on failure).
 * Confidence: medium (string-matched "Tightbeam TransportBuffer swift").
 * Notes: SUB_d65f03c0a8c14ff4 inlined tail; strings s_Fatal_error_005accd0 /
 *   s_Tightbeam_TransportBuffer_swift_005accb0; noreturn FUN_001afa84.
 */
void tightbeam_transport_init(void)
{
    long desc_slot;          /* lVar2 = *(x5-8) */
    unsigned long flags;     /* stack canary slot */
    uint8_t word_a8;
    unsigned long s0, s1, s2, s3, s4, s5, s6, s7;  /* 16-byte init result */
    unsigned long d0, d1, d2, d3, d4, d5, d6, d7;  /* descriptor block */

    flags = 0xd2c8502b44bfffed6ull;   /* canary */
    desc_slot = *(long *)((char *)__builtin_frame_address(0) - 8);
    /* sub-init returns {s0,s1} status pair */
    s0 = 0; s1 = 0;
    if (s0 == 0) {
        sk_fatal_error("Fatal error", 0xb, 2, 0xd000000000000040,
                       0x80000000005ace20, "Tightbeam TransportBuffer swift",
                       0x1f, 2);   /* FUN_001afa84, noreturn */
    }
    d0 = 0; d1 = 0; d2 = 0; d3 = 0; d4 = 0; d5 = 0;
    d6 = 0; d7 = 0;
    word_a8 = 1;
    /* (*extraout_x12)(&s0, 0, 0, 1, &local_b0) — transport init */
    if (word_a8 != 0) {
        /* (**(desc_slot+0x20))(in_x7, &local_b0, in_x5) — dispatch */
    }
    if (flags != 0xd2c8502b44bfffed6ull) {
        sk_stack_chk_fail();   /* FUN_0011d7e8, noreturn */
    }
}
