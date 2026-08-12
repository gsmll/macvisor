/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 *
 * TightBeam (TB) service-dispatch trap thunks (SKR43 batch, 0x4b4424-0x4b5744).
 * This is a dense table of 120 noreturn trap sites emitted by the compiler for
 * TB_ASSERT / TB_FATAL checks in the TightBeam server-dispatch layer (libvas,
 * source file EASM_C.c).  Each thunk calls one of four shared report/trap
 * printers (FUN_0004b478 / FUN_0004b488 / FUN_0004b454 / FUN_00118b28) with a
 * fixed message string, then hits a SoftwareBreakpoint(1, next) that does not
 * return.  The message text identifies the TightBeam server method whose
 * vtable slot was NULL ("implementation for X is not present") or whose call
 * returned an unexpected error ("invalid error returned from X").
 *
 * Ground truth: Ghidra FUN_ names + addresses.  All names are estimates unless
 * string-matched.  Confidence: high (structural + string-matched).
 */

#include <stdint.h>

typedef uint64_t word_t;

/* Shared TightBeam report/trap printers (noreturn).  Each reports the fixed
 * message and then traps (the SoftwareBreakpoint that ends every site). */
extern void cL4_tb_report_unexpected_error(word_t file) __attribute__((noreturn)); /* FUN_0004b478 */
extern void cL4_tb_report_completion(word_t file)     __attribute__((noreturn)); /* FUN_0004b488 */
extern void cL4_tb_report_invalid_value(word_t code)  __attribute__((noreturn)); /* FUN_0004b454 */
extern void cL4_tb_report_message(word_t msg)         __attribute__((noreturn)); /* FUN_00118b28 */

/* Every thunk ends with SoftwareBreakpoint(1, next) which returns a code
 * pointer that is called and never returns; rendered as __builtin_trap(). */
/* FUN_004b4424 @ 0x004b4424  (est. sk_tb_trap_completion_block_4424)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4448); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",  (%s:%d)\n
 * Confidence: high (structural; string-matched) */
/* FUN_004b4424 @ 0x004b4424  (est. sk_tb_trap_completion_block_4424)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4448); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4424(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4448); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4448 @ 0x004b4448  (est. sk_tb_trap_unexpected_error_4448)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b446c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4448(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b446c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b446c @ 0x004b446c  (est. sk_tb_trap_assert_dyldmapregion_446c)
 * TightBeam assert trap site for server method assert_dyldmapregion.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b449c); does not return).
 * msg @ 0x005ba043: TB_ASSERT: (server->dyldmapregion != ((void*)0)) && "implementation for dyldMapRegion is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_dyldmapregion_446c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->dyldmapregion != ((void*)0)) && \"implementation for dyldMapRegion is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b449c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b449c @ 0x004b449c  (est. sk_tb_trap_completion_block_449c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b44c0); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_449c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b44c0); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b44c0 @ 0x004b44c0  (est. sk_tb_trap_unexpected_error_44c0)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b44e4); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_44c0(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b44e4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b44e4 @ 0x004b44e4  (est. sk_tb_trap_assert_unregisterthread_44e4)
 * TightBeam assert trap site for server method assert_unregisterthread.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4514); does not return).
 * msg @ 0x005b9f82: TB_ASSERT: (server->unregisterthread != ((void*)0)) && "implementation for unregisterThread is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_unregisterthread_44e4(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->unregisterthread != ((void*)0)) && \"implementation for unregisterThread is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4514); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4514 @ 0x004b4514  (est. sk_tb_trap_completion_block_4514)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4538); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4514(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4538); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4538 @ 0x004b4538  (est. sk_tb_trap_unexpected_error_4538)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b455c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4538(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b455c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b455c @ 0x004b455c  (est. sk_tb_trap_assert_registerthreadexecutioncontext_455c)
 * TightBeam assert trap site for server method assert_registerthreadexecutioncontext.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b458c); does not return).
 * msg @ 0x005b9e97: TB_ASSERT: (server->registerthreadexecutioncontext != ((void*)0)) && "implementation for registerThreadExecutionContext is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_registerthreadexecutioncontext_455c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->registerthreadexecutioncontext != ((void*)0)) && \"implementation for registerThreadExecutionContext is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b458c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b458c @ 0x004b458c  (est. sk_tb_trap_completion_block_458c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b45b0); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_458c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b45b0); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b45b0 @ 0x004b45b0  (est. sk_tb_trap_unexpected_error_45b0)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b45d4); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_45b0(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b45d4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b45d4 @ 0x004b45d4  (est. sk_tb_trap_assert_registerthread_45d4)
 * TightBeam assert trap site for server method assert_registerthread.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4604); does not return).
 * msg @ 0x005b9ddc: TB_ASSERT: (server->registerthread != ((void*)0)) && "implementation for registerThread is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_registerthread_45d4(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->registerthread != ((void*)0)) && \"implementation for registerThread is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4604); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4604 @ 0x004b4604  (est. sk_tb_trap_completion_block_4604)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4628); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4604(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4628); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4628 @ 0x004b4628  (est. sk_tb_trap_unexpected_error_4628)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b464c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4628(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b464c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b464c @ 0x004b464c  (est. sk_tb_trap_assert_mapmacho_464c)
 * TightBeam assert trap site for server method assert_mapmacho.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b467c); does not return).
 * msg @ 0x005b9d33: TB_ASSERT: (server->mapmacho != ((void*)0)) && "implementation for mapMacho is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_mapmacho_464c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->mapmacho != ((void*)0)) && \"implementation for mapMacho is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b467c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b467c @ 0x004b467c  (est. sk_tb_trap_completion_block_467c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b46a0); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_467c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b46a0); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b46a0 @ 0x004b46a0  (est. sk_tb_trap_unexpected_error_46a0)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b46c4); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_46a0(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b46c4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b46c4 @ 0x004b46c4  (est. sk_tb_trap_assert_setupsuccessful_46c4)
 * TightBeam assert trap site for server method assert_setupsuccessful.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b46f4); does not return).
 * msg @ 0x005b9c75: TB_ASSERT: (server->setupsuccessful != ((void*)0)) && "implementation for setupSuccessful is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_setupsuccessful_46c4(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->setupsuccessful != ((void*)0)) && \"implementation for setupSuccessful is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b46f4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b46f4 @ 0x004b46f4  (est. sk_tb_trap_completion_block_46f4)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4718); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_46f4(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4718); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4718 @ 0x004b4718  (est. sk_tb_trap_unexpected_error_4718)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b473c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4718(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b473c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b473c @ 0x004b473c  (est. sk_tb_trap_assert_spansetfaultstate_473c)
 * TightBeam assert trap site for server method assert_spansetfaultstate.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b476c); does not return).
 * msg @ 0x005b9bb1: TB_ASSERT: (server->spansetfaultstate != ((void*)0)) && "implementation for spanSetFaultstate is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spansetfaultstate_473c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spansetfaultstate != ((void*)0)) && \"implementation for spanSetFaultstate is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b476c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b476c @ 0x004b476c  (est. sk_tb_trap_assert_capability_476c)
 * TightBeam assert trap site for server method assert_capability.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b479c); does not return).
 * msg @ 0x005b9a76: TB_ASSERT: (tb_message_decode_capability(msg, (uint64_t *) &frame) == TB_ERROR_SUCCESS) && "failed to decode capability",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_capability_476c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (tb_message_decode_capability(msg, (uint64_t *) &frame) == TB_ERROR_SUCCESS) && \"failed to decode capability\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b479c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b479c @ 0x004b479c  (est. sk_tb_trap_completion_block_479c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b47c0); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_479c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b47c0); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b47c0 @ 0x004b47c0  (est. sk_tb_trap_unexpected_error_47c0)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b47e4); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_47c0(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b47e4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b47e4 @ 0x004b47e4  (est. sk_tb_trap_assert_spanmapframe_47e4)
 * TightBeam assert trap site for server method assert_spanmapframe.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4814); does not return).
 * msg @ 0x005b9afc: TB_ASSERT: (server->spanmapframe != ((void*)0)) && "implementation for spanMapFrame is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spanmapframe_47e4(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spanmapframe != ((void*)0)) && \"implementation for spanMapFrame is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4814); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4814 @ 0x004b4814  (est. sk_tb_trap_completion_block_4814)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4838); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4814(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4838); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4838 @ 0x004b4838  (est. sk_tb_trap_unexpected_error_4838)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b485c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4838(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b485c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b485c @ 0x004b485c  (est. sk_tb_trap_assert_spandepopulate_485c)
 * TightBeam assert trap site for server method assert_spandepopulate.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b488c); does not return).
 * msg @ 0x005b99aa: TB_ASSERT: (server->spandepopulate != ((void*)0)) && "implementation for spanDepopulate is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spandepopulate_485c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spandepopulate != ((void*)0)) && \"implementation for spanDepopulate is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b488c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b488c @ 0x004b488c  (est. sk_tb_trap_completion_block_488c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b48b0); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_488c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b48b0); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b48b0 @ 0x004b48b0  (est. sk_tb_trap_unexpected_error_48b0)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b48d4); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_48b0(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b48d4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b48d4 @ 0x004b48d4  (est. sk_tb_trap_assert_spanpopulate_48d4)
 * TightBeam assert trap site for server method assert_spanpopulate.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4904); does not return).
 * msg @ 0x005b98e4: TB_ASSERT: (server->spanpopulate != ((void*)0)) && "implementation for spanPopulate is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spanpopulate_48d4(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spanpopulate != ((void*)0)) && \"implementation for spanPopulate is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4904); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4904 @ 0x004b4904  (est. sk_tb_trap_completion_block_4904)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4928); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4904(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4928); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4928 @ 0x004b4928  (est. sk_tb_trap_unexpected_error_4928)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b494c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4928(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b494c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b494c @ 0x004b494c  (est. sk_tb_trap_assert_spanbump_494c)
 * TightBeam assert trap site for server method assert_spanbump.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b497c); does not return).
 * msg @ 0x005b983a: TB_ASSERT: (server->spanbump != ((void*)0)) && "implementation for spanBump is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spanbump_494c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spanbump != ((void*)0)) && \"implementation for spanBump is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b497c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b497c @ 0x004b497c  (est. sk_tb_trap_completion_block_497c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b49a0); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_497c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b49a0); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b49a0 @ 0x004b49a0  (est. sk_tb_trap_unexpected_error_49a0)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b49c4); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_49a0(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b49c4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b49c4 @ 0x004b49c4  (est. sk_tb_trap_assert_spandowngrade_49c4)
 * TightBeam assert trap site for server method assert_spandowngrade.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b49f4); does not return).
 * msg @ 0x005b9782: TB_ASSERT: (server->spandowngrade != ((void*)0)) && "implementation for spanDowngrade is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spandowngrade_49c4(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spandowngrade != ((void*)0)) && \"implementation for spanDowngrade is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b49f4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b49f4 @ 0x004b49f4  (est. sk_tb_trap_completion_block_49f4)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4a18); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_49f4(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4a18); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4a18 @ 0x004b4a18  (est. sk_tb_trap_unexpected_error_4a18)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4a3c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4a18(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4a3c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4a3c @ 0x004b4a3c  (est. sk_tb_trap_assert_spanconfig_4a3c)
 * TightBeam assert trap site for server method assert_spanconfig.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4a6c); does not return).
 * msg @ 0x005b9647: TB_ASSERT: (server->spanconfig != ((void*)0)) && "implementation for spanConfig is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spanconfig_4a3c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spanconfig != ((void*)0)) && \"implementation for spanConfig is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4a6c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4a6c @ 0x004b4a6c  (est. sk_tb_trap_completion_block_4a6c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4a90); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4a6c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4a90); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4a90 @ 0x004b4a90  (est. sk_tb_trap_unexpected_error_4a90)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4ab4); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4a90(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4ab4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4ab4 @ 0x004b4ab4  (est. sk_tb_trap_assert_spandestroy_4ab4)
 * TightBeam assert trap site for server method assert_spandestroy.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4ae4); does not return).
 * msg @ 0x005b9595: TB_ASSERT: (server->spandestroy != ((void*)0)) && "implementation for spanDestroy is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spandestroy_4ab4(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spandestroy != ((void*)0)) && \"implementation for spanDestroy is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4ae4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4ae4 @ 0x004b4ae4  (est. sk_tb_trap_completion_block_4ae4)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4b08); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4ae4(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4b08); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4b08 @ 0x004b4b08  (est. sk_tb_trap_unexpected_error_4b08)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4b2c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4b08(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4b2c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4b2c @ 0x004b4b2c  (est. sk_tb_trap_assert_spanresize_4b2c)
 * TightBeam assert trap site for server method assert_spanresize.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4b5c); does not return).
 * msg @ 0x005b94e5: TB_ASSERT: (server->spanresize != ((void*)0)) && "implementation for spanResize is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spanresize_4b2c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spanresize != ((void*)0)) && \"implementation for spanResize is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4b5c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4b5c @ 0x004b4b5c  (est. sk_tb_trap_completion_block_4b5c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4b80); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4b5c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4b80); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4b80 @ 0x004b4b80  (est. sk_tb_trap_unexpected_error_4b80)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4ba4); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4b80(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4ba4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4ba4 @ 0x004b4ba4  (est. sk_tb_trap_assert_spansplit_4ba4)
 * TightBeam assert trap site for server method assert_spansplit.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4bd4); does not return).
 * msg @ 0x005b9422: TB_ASSERT: (server->spansplit != ((void*)0)) && "implementation for spanSplit is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spansplit_4ba4(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spansplit != ((void*)0)) && \"implementation for spanSplit is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4bd4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4bd4 @ 0x004b4bd4  (est. sk_tb_trap_completion_block_4bd4)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4bf8); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4bd4(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4bf8); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4bf8 @ 0x004b4bf8  (est. sk_tb_trap_unexpected_error_4bf8)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4c1c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4bf8(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4c1c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4c1c @ 0x004b4c1c  (est. sk_tb_trap_assert_spanmerge_4c1c)
 * TightBeam assert trap site for server method assert_spanmerge.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4c4c); does not return).
 * msg @ 0x005b9375: TB_ASSERT: (server->spanmerge != ((void*)0)) && "implementation for spanMerge is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spanmerge_4c1c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spanmerge != ((void*)0)) && \"implementation for spanMerge is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4c4c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4c4c @ 0x004b4c4c  (est. sk_tb_trap_completion_block_4c4c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4c70); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4c4c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4c70); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4c70 @ 0x004b4c70  (est. sk_tb_trap_unexpected_error_4c70)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4c94); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4c70(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4c94); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4c94 @ 0x004b4c94  (est. sk_tb_trap_assert_spanalloc_4c94)
 * TightBeam assert trap site for server method assert_spanalloc.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4cc4); does not return).
 * msg @ 0x005b9225: TB_ASSERT: (server->spanalloc != ((void*)0)) && "implementation for spanAlloc is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spanalloc_4c94(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spanalloc != ((void*)0)) && \"implementation for spanAlloc is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4cc4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4cc4 @ 0x004b4cc4  (est. sk_tb_trap_completion_block_4cc4)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4ce8); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4cc4(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4ce8); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4ce8 @ 0x004b4ce8  (est. sk_tb_trap_unexpected_error_4ce8)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4d0c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4ce8(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4d0c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4d0c @ 0x004b4d0c  (est. sk_tb_trap_assert_faulthandlerdestroy_4d0c)
 * TightBeam assert trap site for server method assert_faulthandlerdestroy.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4d3c); does not return).
 * msg @ 0x005b915b: TB_ASSERT: (server->faulthandlerdestroy != ((void*)0)) && "implementation for faulthandlerDestroy is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_faulthandlerdestroy_4d0c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->faulthandlerdestroy != ((void*)0)) && \"implementation for faulthandlerDestroy is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4d3c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4d3c @ 0x004b4d3c  (est. sk_tb_trap_completion_block_4d3c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4d60); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4d3c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4d60); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4d60 @ 0x004b4d60  (est. sk_tb_trap_unexpected_error_4d60)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4d84); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4d60(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4d84); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4d84 @ 0x004b4d84  (est. sk_tb_trap_assert_faulthandlercompletefault_4d84)
 * TightBeam assert trap site for server method assert_faulthandlercompletefault.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4db4); does not return).
 * msg @ 0x005b907f: TB_ASSERT: (server->faulthandlercompletefault != ((void*)0)) && "implementation for faulthandlerCompleteFault is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_faulthandlercompletefault_4d84(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->faulthandlercompletefault != ((void*)0)) && \"implementation for faulthandlerCompleteFault is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4db4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4db4 @ 0x004b4db4  (est. sk_tb_trap_completion_block_4db4)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4dd8); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4db4(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4dd8); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4dd8 @ 0x004b4dd8  (est. sk_tb_trap_unexpected_error_4dd8)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4dfc); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4dd8(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4dfc); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4dfc @ 0x004b4dfc  (est. sk_tb_trap_assert_faulthandlerstartfault_4dfc)
 * TightBeam assert trap site for server method assert_faulthandlerstartfault.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4e2c); does not return).
 * msg @ 0x005b8f64: TB_ASSERT: (server->faulthandlerstartfault != ((void*)0)) && "implementation for faulthandlerStartFault is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_faulthandlerstartfault_4dfc(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->faulthandlerstartfault != ((void*)0)) && \"implementation for faulthandlerStartFault is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4e2c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4e2c @ 0x004b4e2c  (est. sk_tb_trap_completion_block_4e2c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4e50); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4e2c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4e50); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4e50 @ 0x004b4e50  (est. sk_tb_trap_unexpected_error_4e50)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4e74); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4e50(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4e74); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4e74 @ 0x004b4e74  (est. sk_tb_trap_assert_faulthandlercreate_4e74)
 * TightBeam assert trap site for server method assert_faulthandlercreate.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4ea4); does not return).
 * msg @ 0x005b8e9c: TB_ASSERT: (server->faulthandlercreate != ((void*)0)) && "implementation for faulthandlerCreate is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_faulthandlercreate_4e74(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->faulthandlercreate != ((void*)0)) && \"implementation for faulthandlerCreate is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4ea4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4ea4 @ 0x004b4ea4  (est. sk_tb_trap_completion_block_4ea4)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4ec8); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4ea4(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4ec8); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4ec8 @ 0x004b4ec8  (est. sk_tb_trap_unexpected_error_4ec8)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4eec); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4ec8(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4eec); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4eec @ 0x004b4eec  (est. sk_tb_trap_assert_freekernelobject_4eec)
 * TightBeam assert trap site for server method assert_freekernelobject.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4f1c); does not return).
 * msg @ 0x005b8ddb: TB_ASSERT: (server->freekernelobject != ((void*)0)) && "implementation for freeKernelObject is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_freekernelobject_4eec(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->freekernelobject != ((void*)0)) && \"implementation for freeKernelObject is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4f1c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4f1c @ 0x004b4f1c  (est. sk_tb_trap_completion_block_4f1c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4f40); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4f1c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4f40); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4f40 @ 0x004b4f40  (est. sk_tb_trap_unexpected_error_4f40)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4f64); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4f40(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4f64); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4f64 @ 0x004b4f64  (est. sk_tb_trap_assert_allocsmecontext_4f64)
 * TightBeam assert trap site for server method assert_allocsmecontext.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4f94); does not return).
 * msg @ 0x005b8d1c: TB_ASSERT: (server->allocsmecontext != ((void*)0)) && "implementation for allocSMEContext is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_allocsmecontext_4f64(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->allocsmecontext != ((void*)0)) && \"implementation for allocSMEContext is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b4f94); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4f94 @ 0x004b4f94  (est. sk_tb_trap_completion_block_4f94)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4fb8); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_4f94(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4fb8); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4fb8 @ 0x004b4fb8  (est. sk_tb_trap_unexpected_error_4fb8)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b4fdc); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_4fb8(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b4fdc); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b4fdc @ 0x004b4fdc  (est. sk_tb_trap_assert_allocamxcontext_4fdc)
 * TightBeam assert trap site for server method assert_allocamxcontext.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b500c); does not return).
 * msg @ 0x005b8c5d: TB_ASSERT: (server->allocamxcontext != ((void*)0)) && "implementation for allocAMXContext is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_allocamxcontext_4fdc(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->allocamxcontext != ((void*)0)) && \"implementation for allocAMXContext is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b500c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b500c @ 0x004b500c  (est. sk_tb_trap_completion_block_500c)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5030); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_500c(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5030); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5030 @ 0x004b5030  (est. sk_tb_trap_unexpected_error_5030)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5054); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_5030(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5054); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5054 @ 0x004b5054  (est. sk_tb_trap_assert_allocexecutioncontext_5054)
 * TightBeam assert trap site for server method assert_allocexecutioncontext.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5084); does not return).
 * msg @ 0x005b8b8c: TB_ASSERT: (server->allocexecutioncontext != ((void*)0)) && "implementation for allocExecutionContext is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_allocexecutioncontext_5054(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->allocexecutioncontext != ((void*)0)) && \"implementation for allocExecutionContext is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5084); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5084 @ 0x004b5084  (est. sk_tb_trap_completion_block_5084)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b50a8); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_5084(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b50a8); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b50a8 @ 0x004b50a8  (est. sk_tb_trap_unexpected_error_50a8)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b50cc); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_50a8(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b50cc); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b50cc @ 0x004b50cc  (est. sk_tb_trap_assert_allocendpoint_50cc)
 * TightBeam assert trap site for server method assert_allocendpoint.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b50fc); does not return).
 * msg @ 0x005b8ad3: TB_ASSERT: (server->allocendpoint != ((void*)0)) && "implementation for allocEndpoint is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_allocendpoint_50cc(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->allocendpoint != ((void*)0)) && \"implementation for allocEndpoint is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b50fc); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b50fc @ 0x004b50fc  (est. sk_tb_trap_completion_block_50fc)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5120); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_50fc(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5120); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5120 @ 0x004b5120  (est. sk_tb_trap_unexpected_error_5120)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5144); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_5120(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5144); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5144 @ 0x004b5144  (est. sk_tb_trap_assert_spanat_5144)
 * TightBeam assert trap site for server method assert_spanat.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5174); does not return).
 * msg @ 0x005b898c: TB_ASSERT: (server->spanat != ((void*)0)) && "implementation for spanAt is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_spanat_5144(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->spanat != ((void*)0)) && \"implementation for spanAt is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5174); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5174 @ 0x004b5174  (est. sk_tb_trap_completion_block_5174)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5198); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_5174(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5198); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5198 @ 0x004b5198  (est. sk_tb_trap_unexpected_error_5198)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b51bc); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_5198(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b51bc); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b51bc @ 0x004b51bc  (est. sk_tb_trap_assert_handlefault_51bc)
 * TightBeam assert trap site for server method assert_handlefault.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b51ec); does not return).
 * msg @ 0x005b88d9: TB_ASSERT: (server->handlefault != ((void*)0)) && "implementation for handleFault is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_handlefault_51bc(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->handlefault != ((void*)0)) && \"implementation for handleFault is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b51ec); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b51ec @ 0x004b51ec  (est. sk_tb_trap_completion_block_51ec)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5210); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_51ec(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5210); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5210 @ 0x004b5210  (est. sk_tb_trap_unexpected_error_5210)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5234); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_5210(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5234); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5234 @ 0x004b5234  (est. sk_tb_trap_assert_rootcopy_5234)
 * TightBeam assert trap site for server method assert_rootcopy.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5264); does not return).
 * msg @ 0x005b882f: TB_ASSERT: (server->rootcopy != ((void*)0)) && "implementation for rootCopy is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_rootcopy_5234(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->rootcopy != ((void*)0)) && \"implementation for rootCopy is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5264); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5264 @ 0x004b5264  (est. sk_tb_trap_completion_block_5264)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5288); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_5264(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5288); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5288 @ 0x004b5288  (est. sk_tb_trap_unexpected_error_5288)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b52ac); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_5288(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b52ac); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b52ac @ 0x004b52ac  (est. sk_tb_trap_assert_framecopy_52ac)
 * TightBeam assert trap site for server method assert_framecopy.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b52dc); does not return).
 * msg @ 0x005b8782: TB_ASSERT: (server->framecopy != ((void*)0)) && "implementation for frameCopy is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_framecopy_52ac(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->framecopy != ((void*)0)) && \"implementation for frameCopy is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b52dc); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b52dc @ 0x004b52dc  (est. sk_tb_trap_completion_block_52dc)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5300); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_52dc(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5300); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5300 @ 0x004b5300  (est. sk_tb_trap_unexpected_error_5300)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5324); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_5300(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5324); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5324 @ 0x004b5324  (est. sk_tb_trap_assert_physicaladdress_5324)
 * TightBeam assert trap site for server method assert_physicaladdress.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5354); does not return).
 * msg @ 0x005b86a4: TB_ASSERT: (server->physicaladdress != ((void*)0)) && "implementation for physicalAddress is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_physicaladdress_5324(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->physicaladdress != ((void*)0)) && \"implementation for physicalAddress is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5354); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5354 @ 0x004b5354  (est. sk_tb_trap_completion_block_5354)
 * TightBeam assert trap site for server method completion_block.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5378); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (cmp.encoded) && "completion block must be called before returning",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_completion_block_5354(void)
{
    cL4_tb_report_completion((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b5378); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5378 @ 0x004b5378  (est. sk_tb_trap_unexpected_error_5378)
 * TightBeam assert trap site for server method unexpected_error.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b539c); does not return).
 * msg @ 0x005b8541: TB_ASSERT: (err == TB_ERROR_SUCCESS || err == TB_ERROR_USER_FAILURE) && "unexpected tb_error_t returned",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_unexpected_error_5378(void)
{
    cL4_tb_report_unexpected_error((word_t)"EASM_C.c");
    /* SoftwareBreakpoint(1, 0x4b539c); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b539c @ 0x004b539c  (est. sk_tb_trap_assert_getsegmentinfotable_539c)
 * TightBeam assert trap site for server method assert_getsegmentinfotable.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b53cc); does not return).
 * msg @ 0x005b854a: TB_ASSERT: (server->getsegmentinfotable != ((void*)0)) && "implementation for getSegmentInfoTable is not present",    (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_assert_getsegmentinfotable_539c(void)
{
    cL4_tb_report_message((word_t)"TB_ASSERT: (server->getsegmentinfotable != ((void*)0)) && \"implementation for getSegmentInfoTable is not present\", \x08\x08 (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b53cc); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b53cc @ 0x004b53cc  (est. sk_tb_trap_invalid_value_53cc)
 * TightBeam assert trap site for server method invalid_value.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b53e4); does not return).
 * msg @ 0xNone: TB_FATAL: invalid value: unexpected case value, %llx (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_invalid_value_53cc(void)
{
    cL4_tb_report_invalid_value((word_t)0);
    /* SoftwareBreakpoint(1, 0x4b53e4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b53e4 @ 0x004b53e4  (est. sk_tb_trap_fatal_physicalAddress_53e4)
 * TightBeam fatal trap site for server method fatal_physicalAddress.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5414); does not return).
 * msg @ 0x005ba4f6: TB_FATAL: invalid error returned from physicalAddress (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_physicalAddress_53e4(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from physicalAddress (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5414); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5414 @ 0x004b5414  (est. sk_tb_trap_fatal_frameCopy_5414)
 * TightBeam fatal trap site for server method fatal_frameCopy.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5444); does not return).
 * msg @ 0x005ba535: TB_FATAL: invalid error returned from frameCopy (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_frameCopy_5414(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from frameCopy (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5444); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5444 @ 0x004b5444  (est. sk_tb_trap_fatal_rootCopy_5444)
 * TightBeam fatal trap site for server method fatal_rootCopy.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5474); does not return).
 * msg @ 0x005ba56e: TB_FATAL: invalid error returned from rootCopy (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_rootCopy_5444(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from rootCopy (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5474); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5474 @ 0x004b5474  (est. sk_tb_trap_fatal_handleFault_5474)
 * TightBeam fatal trap site for server method fatal_handleFault.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b54a4); does not return).
 * msg @ 0x005ba5a6: TB_FATAL: invalid error returned from handleFault (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_handleFault_5474(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from handleFault (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b54a4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b54a4 @ 0x004b54a4  (est. sk_tb_trap_fatal_spanAt_54a4)
 * TightBeam fatal trap site for server method fatal_spanAt.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b54d4); does not return).
 * msg @ 0x005ba5e1: TB_FATAL: invalid error returned from spanAt (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_spanAt_54a4(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from spanAt (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b54d4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b54d4 @ 0x004b54d4  (est. sk_tb_trap_fatal_allocEndpoint_54d4)
 * TightBeam fatal trap site for server method fatal_allocEndpoint.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5504); does not return).
 * msg @ 0x005ba617: TB_FATAL: invalid error returned from allocEndpoint (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_allocEndpoint_54d4(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from allocEndpoint (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5504); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5504 @ 0x004b5504  (est. sk_tb_trap_fatal_allocExecutionContext_5504)
 * TightBeam fatal trap site for server method fatal_allocExecutionContext.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5534); does not return).
 * msg @ 0x005ba654: TB_FATAL: invalid error returned from allocExecutionContext (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_allocExecutionContext_5504(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from allocExecutionContext (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5534); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5534 @ 0x004b5534  (est. sk_tb_trap_fatal_allocAMXContext_5534)
 * TightBeam fatal trap site for server method fatal_allocAMXContext.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5564); does not return).
 * msg @ 0x005ba699: TB_FATAL: invalid error returned from allocAMXContext (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_allocAMXContext_5534(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from allocAMXContext (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5564); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5564 @ 0x004b5564  (est. sk_tb_trap_fatal_allocSMEContext_5564)
 * TightBeam fatal trap site for server method fatal_allocSMEContext.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5594); does not return).
 * msg @ 0x005ba6d8: TB_FATAL: invalid error returned from allocSMEContext (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_allocSMEContext_5564(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from allocSMEContext (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5594); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5594 @ 0x004b5594  (est. sk_tb_trap_fatal_freeKernelObject_5594)
 * TightBeam fatal trap site for server method fatal_freeKernelObject.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b55c4); does not return).
 * msg @ 0x005ba717: TB_FATAL: invalid error returned from freeKernelObject (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_freeKernelObject_5594(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from freeKernelObject (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b55c4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b55c4 @ 0x004b55c4  (est. sk_tb_trap_fatal_faulthandlerCreate_55c4)
 * TightBeam fatal trap site for server method fatal_faulthandlerCreate.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b55f4); does not return).
 * msg @ 0x005ba757: TB_FATAL: invalid error returned from faulthandlerCreate (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_faulthandlerCreate_55c4(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from faulthandlerCreate (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b55f4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b55f4 @ 0x004b55f4  (est. sk_tb_trap_fatal_faulthandlerStartFault_55f4)
 * TightBeam fatal trap site for server method fatal_faulthandlerStartFault.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5624); does not return).
 * msg @ 0x005ba799: TB_FATAL: invalid error returned from faulthandlerStartFault (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_faulthandlerStartFault_55f4(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from faulthandlerStartFault (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5624); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5624 @ 0x004b5624  (est. sk_tb_trap_fatal_faulthandlerCompleteFault_5624)
 * TightBeam fatal trap site for server method fatal_faulthandlerCompleteFault.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5654); does not return).
 * msg @ 0x005ba7df: TB_FATAL: invalid error returned from faulthandlerCompleteFault (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_faulthandlerCompleteFault_5624(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from faulthandlerCompleteFault (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5654); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5654 @ 0x004b5654  (est. sk_tb_trap_fatal_faulthandlerDestroy_5654)
 * TightBeam fatal trap site for server method fatal_faulthandlerDestroy.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5684); does not return).
 * msg @ 0x005ba828: TB_FATAL: invalid error returned from faulthandlerDestroy (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_faulthandlerDestroy_5654(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from faulthandlerDestroy (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5684); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5684 @ 0x004b5684  (est. sk_tb_trap_fatal_spanAlloc_5684)
 * TightBeam fatal trap site for server method fatal_spanAlloc.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b56b4); does not return).
 * msg @ 0x005ba86b: TB_FATAL: invalid error returned from spanAlloc (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_spanAlloc_5684(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from spanAlloc (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b56b4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b56b4 @ 0x004b56b4  (est. sk_tb_trap_fatal_spanMerge_56b4)
 * TightBeam fatal trap site for server method fatal_spanMerge.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b56e4); does not return).
 * msg @ 0x005ba8a4: TB_FATAL: invalid error returned from spanMerge (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_spanMerge_56b4(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from spanMerge (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b56e4); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b56e4 @ 0x004b56e4  (est. sk_tb_trap_fatal_spanSplit_56e4)
 * TightBeam fatal trap site for server method fatal_spanSplit.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5714); does not return).
 * msg @ 0x005ba8dd: TB_FATAL: invalid error returned from spanSplit (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_spanSplit_56e4(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from spanSplit (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5714); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5714 @ 0x004b5714  (est. sk_tb_trap_fatal_spanResize_5714)
 * TightBeam fatal trap site for server method fatal_spanResize.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5744); does not return).
 * msg @ 0x005ba916: TB_FATAL: invalid error returned from spanResize (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_spanResize_5714(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from spanResize (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5744); (*ret)(); — unreachable */
    __builtin_trap();
}

/* FUN_004b5744 @ 0x004b5744  (est. sk_tb_trap_fatal_spanDestroy_5744)
 * TightBeam fatal trap site for server method fatal_spanDestroy.  Reports the message below via
 * the shared printer, then traps (SoftwareBreakpoint(1, 0x4b5774); does not return).
 * msg @ 0x005ba950: TB_FATAL: invalid error returned from spanDestroy (%s:%d)\n
 * Confidence: high (structural; string-matched) */
static void sk_tb_trap_fatal_spanDestroy_5744(void)
{
    cL4_tb_report_message((word_t)"TB_FATAL: invalid error returned from spanDestroy (%s:%d)\n");
    /* SoftwareBreakpoint(1, 0x4b5774); (*ret)(); — unreachable */
    __builtin_trap();
}

