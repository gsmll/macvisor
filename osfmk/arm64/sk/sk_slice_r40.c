/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R40: 0x004afbc4-0x004b109c (120 functions). This slice is a
 * cluster of fail-closed cL4 assertion/fatal trap shims plus a handful of
 * real functions in the "tightbeam" / large-transport message path: the
 * "Unexpected L4 Error" fatal entry (004afbc4), the large-transport
 * descriptor decoder (004afd3c), a span/slot size update (004afe60), a
 * region assert+handler path (004aff30), and a supervisor-wait loop
 * (004b0744). The bulk are deterministic abort stubs: each calls a cL4
 * diagnostic reporter (FUN_00004cc0 / FUN_00118b28 / FUN_00115424 / ...)
 * with a fixed message string, then executes the SoftwareBreakpoint
 * fail-closed trap (rendered CL4_SWBP(addr)) - none returns. All names
 * are estimates unless a message string / header matches (the
 * TB_ASSERT / TB_FATAL / malloc_assertion / XRT / security-assertion and
 * cL4_large_transport / tb_codec source-file strings).
 *
 * Conventions (sibling-slice): out-of-slice callees keep their FUN_
 * addresses as unprototyped externs (word_t result = x0); in-slice
 * functions use sk_r40_<addr>. SoftwareBreakpoint(1, addr) is rendered
 * CL4_SWBP(addr).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;
typedef unsigned char byte;
typedef unsigned long ulong;   /* Ghidra ulong -> used in a few bodies */
typedef unsigned int uint;     /* Ghidra uint  -> used in a few bodies */
typedef uint64_t (*code)();
typedef struct { uint64_t lo, hi; } skr40_w16;

/* Ghidra SoftwareBreakpoint(1, addr) - fail-closed trap, does not return. */
static inline unsigned long CL4_SWBP(unsigned long addr)
{ (void)addr; __builtin_trap(); }

/* Ghidra CallSupervisor(4) - supervisor call; returns status in x0. */
static inline unsigned long CL4_CALLSV(uint32_t n)
{ (void)n; __builtin_trap(); }

/* String / data literals referenced by this slice. */
extern word_t DAT_005aacf2;
extern word_t DAT_005aae47;
extern word_t DAT_005aaec9;
extern word_t DAT_005aaf7e;
extern word_t DAT_005aafd8;
extern word_t DAT_005ab052;
extern word_t DAT_005ab0ce;
extern word_t DAT_005ab2f4;
extern word_t DAT_005ab4a5;
extern word_t DAT_005ab526;
extern word_t DAT_005ab54f;
extern word_t DAT_005ab7d5;
extern word_t DAT_005ab8c1;
extern word_t DAT_005ab8e0;
extern word_t DAT_005ab916;
extern word_t DAT_005abaf2;
extern word_t DAT_005abb2a;
extern word_t DAT_005abe4f;
extern word_t DAT_005abf8d;
extern word_t DAT_005abfaf;
extern word_t DAT_005abfe5;
extern word_t DAT_005ac15a;
extern word_t DAT_005ac250;
extern word_t DAT_005ac2b6;
extern word_t DAT_005ac2f3;
extern word_t DAT_005ac322;
extern word_t DAT_005ac44d;
extern word_t DAT_005ac48b;
extern word_t DAT_005ac697;
extern char s_Security_assertion_failed___s__f_005a8b30;
extern char s_TB_ASSERT__new_slot____L4_Nil____005ab5d1;
extern char s_TB_ASSERT__tb_message_get_dispos_005ab863;
extern char s_TB_ASSERT__tb_message_get_state__005ab810;
extern char s_TB_ASSERT__td__slots_i_____L4_Ni_005aabee;
extern char s_TB_FATAL__overflow_detected_when_005aae93;
extern char s_TB_FATAL__overflow_detected_when_005abc23;
extern char s_TB_FATAL__overflow_detected_when_005abd5d;
extern char s_Unexpected_L4_Error___s__zu__err_005a8bef;
extern char s_XRT_UNLIKELY_key____XRT__THREAD__005ab149;
extern char s__AppleInternal_Library_BuildRoot_005ab177;
extern char s__AppleInternal_Library_BuildRoot_005abc59;
extern char s__AppleInternal_Library_BuildRoot_005ac07c;
extern char s__AppleInternal_Library_BuildRoot_005ac71d;
extern char s_cL4_large_transport_c_005ac025;
extern char s_internal_h_005aad1c;
extern char s_malloc_assertion____uintptr_t_se_005a98d0;
extern char s_malloc_assertion____zone__xzz_me_005a9c5b;
extern char s_malloc_assertion___chunk_capacit_005aa61b;
extern char s_malloc_assertion___memtag_config_005a9b17;
extern char s_malloc_assertion___quarantine____005a9ebb;
extern char s_malloc_assertion___uintptr_t_seg_005a967b;
extern char s_malloc_assertion___uintptr_t_seg_005a97c6;
extern char s_malloc_assertion__allocation_fro_005a903b;
extern char s_malloc_assertion__middle_pte___X_005a9358;
extern char s_malloc_assertion__middle_pte_mid_005a956f;
extern char s_malloc_assertion__old_size__fail_005aa432;
extern char s_malloc_assertion__ranges_0__min__005a9139;
extern char s_malloc_assertion__ranges_0__min__005a9463;
extern char s_malloc_assertion__success__faile_005aa047;
extern char s_malloc_assertion__success__faile_005aa24e;
extern char s_tb_codec_c_005ac712;
extern char s_xrt_thread_tss_get_005ab292;

/* Out-of-slice callees (bodies owned by their range workers). */
/* Report / assertion helpers (all noreturn before the trap): */
extern word_t FUN_00004cc0();  /* malloc assertion report (noreturn; message in arg) */
extern word_t FUN_00118b28();  /* tightbeam TB_ASSERT/TB_FATAL report (noreturn; fmt string in arg) */
extern word_t FUN_001150e0();  /* security assertion report (noreturn; fmt string in arg) */
extern word_t FUN_00115424();  /* XRT thread assertion report (file, buildroot, func, line; noreturn) */
extern word_t FUN_00015e2c();  /* AppleInternal build-root assertion report (noreturn) */
extern word_t FUN_000179c8();  /* cL4_large_transport/build-root assertion report (noreturn) */
extern word_t FUN_000179d8();  /* cL4_large_transport/build-root assertion report (noreturn) */
extern word_t FUN_000179e8();  /* cL4_large_transport/build-root assertion report (noreturn) */
extern word_t FUN_000179f8();  /* cL4_large_transport/build-root assertion report (noreturn) */
extern word_t FUN_00019800();  /* tb_codec assertion report (noreturn) */
extern word_t FUN_00019810();  /* tb_codec assertion report (noreturn) */
extern word_t FUN_00019820();  /* tb_codec assertion report (noreturn) */
extern word_t FUN_00019830();  /* tb_codec assertion report (noreturn) */
extern word_t FUN_00019840();  /* tb_codec assertion report (noreturn) */
extern word_t FUN_00013228();  /* TB assertion report helper (no arg) */
extern word_t FUN_00013244();  /* TB assertion report helper (no arg) */
extern word_t FUN_00014fa0();  /* TB assertion report helper (no arg) */
extern word_t FUN_00014fbc();  /* TB assertion report helper (no arg) */
extern word_t FUN_000159c0();  /* TB assertion report helper (no arg) */
extern word_t FUN_000159c8();  /* TB assertion report helper (no arg) */
extern word_t FUN_0001611c();  /* TB assertion report helper (file arg; noreturn) */
extern word_t FUN_00015e08();  /* TB assertion report helper (no arg) */
/* Decode / alloc / message helpers: */
extern word_t FUN_00002e50();  /* buffer/descriptor allocator (8 args) */
extern void   FUN_00007d00();  /* commit marshalled descriptor */
extern void   FUN_00003788();  /* memory move of trailing data */
extern void   FUN_00007530();  /* early init hook */
extern int    FUN_0011582c();  /* validate/assert check */
extern void   FUN_0001018c();  /* error handler (1 stack arg) */
/* Fatal entry (004afbc4) helpers: */
extern void FUN_000017cc();  /* per-cpu bootstrap hook */
extern void FUN_004afa6c();  /* region unwind (r39) */
extern void FUN_004afae4();  /* noreturn "Unexpected L4 Error" panic (r39) */
/* Supervisor wait loop (004b0744) helpers: */
extern void FUN_004b23d8();  /* state handler */
extern skr40_w16 FUN_00034a2c();  /* returns {x0=base, x1=vtbl} pair */
extern void thunk_FUN_00012568();  /* tail target @ 0x000125b0 */

/* ================================================================== */
/* Fail-closed assertion / fatal trap shims */
/* ================================================================== */

/* FUN_004afc5c @ 0x004afc5c - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion__allocation_fro_005a903b) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004afc5c(void)
{
    FUN_00004cc0(s_malloc_assertion__allocation_fro_005a903b);
    /* noreturn report + trap */
}

/* FUN_004afc78 @ 0x004afc78 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion__ranges_0__min__005a9139) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004afc78(void)
{
    FUN_00004cc0(s_malloc_assertion__ranges_0__min__005a9139);
    /* noreturn report + trap */
}

/* FUN_004afc94 @ 0x004afc94 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion__middle_pte___X_005a9358) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004afc94(void)
{
    FUN_00004cc0(s_malloc_assertion__middle_pte___X_005a9358);
    /* noreturn report + trap */
}

/* FUN_004afcb0 @ 0x004afcb0 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion__middle_pte_mid_005a956f) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004afcb0(void)
{
    FUN_00004cc0(s_malloc_assertion__middle_pte_mid_005a956f);
    /* noreturn report + trap */
}

/* FUN_004afccc @ 0x004afccc - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion__ranges_0__min__005a9463) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004afccc(void)
{
    FUN_00004cc0(s_malloc_assertion__ranges_0__min__005a9463);
    /* noreturn report + trap */
}

/* FUN_004afce8 @ 0x004afce8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion___uintptr_t_seg_005a967b) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004afce8(void)
{
    FUN_00004cc0(s_malloc_assertion___uintptr_t_seg_005a967b);
    /* noreturn report + trap */
}

/* FUN_004afd04 @ 0x004afd04 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion___uintptr_t_seg_005a97c6) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004afd04(void)
{
    FUN_00004cc0(s_malloc_assertion___uintptr_t_seg_005a97c6);
    /* noreturn report + trap */
}

/* FUN_004afd20 @ 0x004afd20 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion____uintptr_t_se_005a98d0) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004afd20(void)
{
    FUN_00004cc0(s_malloc_assertion____uintptr_t_se_005a98d0);
    /* noreturn report + trap */
}

/* FUN_004aff70 @ 0x004aff70 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion____zone__xzz_me_005a9c5b) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004aff70(void)
{
    FUN_00004cc0(s_malloc_assertion____zone__xzz_me_005a9c5b);
    /* noreturn report + trap */
}

/* FUN_004aff8c @ 0x004aff8c - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion__success__faile_005aa24e) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004aff8c(void)
{
    FUN_00004cc0(s_malloc_assertion__success__faile_005aa24e);
    /* noreturn report + trap */
}

/* FUN_004affa8 @ 0x004affa8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion___memtag_config_005a9b17) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004affa8(void)
{
    FUN_00004cc0(s_malloc_assertion___memtag_config_005a9b17);
    /* noreturn report + trap */
}

/* FUN_004affc4 @ 0x004affc4 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion___chunk_capacit_005aa61b) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004affc4(void)
{
    FUN_00004cc0(s_malloc_assertion___chunk_capacit_005aa61b);
    /* noreturn report + trap */
}

/* FUN_004affe0 @ 0x004affe0 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion___quarantine____005a9ebb) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004affe0(void)
{
    FUN_00004cc0(s_malloc_assertion___quarantine____005a9ebb);
    /* noreturn report + trap */
}

/* FUN_004afffc @ 0x004afffc - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion__success__faile_005aa047) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004afffc(void)
{
    FUN_00004cc0(s_malloc_assertion__success__faile_005aa047);
    /* noreturn report + trap */
}

/* FUN_004b0018 @ 0x004b0018 - fail-closed assertion/fatal shim.
 * Reports via FUN_00004cc0 (s_malloc_assertion__old_size__fail_005aa432) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0018(void)
{
    FUN_00004cc0(s_malloc_assertion__old_size__fail_005aa432);
    /* noreturn report + trap */
}

/* FUN_004b0034 @ 0x004b0034 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_ASSERT__td__slots_i_____L4_Ni_005aabee) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0034(void)
{
    FUN_00118b28(s_TB_ASSERT__td__slots_i_____L4_Ni_005aabee);
    CL4_SWBP(0x4b0068);
}

/* FUN_004b0068 @ 0x004b0068 - fail-closed assertion/fatal shim.
 * Reports via FUN_00013228 then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0068(void)
{
    FUN_00013228();
    CL4_SWBP(0x4b0080);
}

/* FUN_004b0080 @ 0x004b0080 - fail-closed assertion/fatal shim.
 * Reports via FUN_00013244 then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0080(void)
{
    FUN_00013244();
    CL4_SWBP(0x4b0098);
}

/* FUN_004b0098 @ 0x004b0098 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005aae47) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0098(void)
{
    FUN_00118b28(DAT_005aae47);
    CL4_SWBP(0x4b00c8);
}

/* FUN_004b00c8 @ 0x004b00c8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005aaec9) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b00c8(void)
{
    FUN_00118b28(DAT_005aaec9);
    CL4_SWBP(0x4b00f8);
}

/* FUN_004b00f8 @ 0x004b00f8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005aae93) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b00f8(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005aae93);
    CL4_SWBP(0x4b0128);
}

/* FUN_004b0128 @ 0x004b0128 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab0ce) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0128(void)
{
    FUN_00118b28(DAT_005ab0ce);
    CL4_SWBP(0x4b0158);
}

/* FUN_004b0158 @ 0x004b0158 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab052) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0158(void)
{
    FUN_00118b28(DAT_005ab052);
    CL4_SWBP(0x4b0188);
}

/* FUN_004b0188 @ 0x004b0188 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005aafd8) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0188(void)
{
    FUN_00118b28(DAT_005aafd8);
    CL4_SWBP(0x4b01b8);
}

/* FUN_004b01b8 @ 0x004b01b8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005aaf7e) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b01b8(void)
{
    FUN_00118b28(DAT_005aaf7e);
    CL4_SWBP(0x4b01e8);
}

/* FUN_004b01e8 @ 0x004b01e8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00115424 (s_XRT_UNLIKELY_key____XRT__THREAD__005ab149 / s__AppleInternal_Library_BuildRoot_005ab177 / s_xrt_thread_tss_get_005ab292 / 0x1d1) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b01e8(void)
{
    FUN_00115424(s_XRT_UNLIKELY_key____XRT__THREAD__005ab149, s__AppleInternal_Library_BuildRoot_005ab177, s_xrt_thread_tss_get_005ab292, 0x1d1);
    /* noreturn report + trap */
}

/* FUN_004b0214 @ 0x004b0214 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab2f4) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0214(void)
{
    FUN_00118b28(DAT_005ab2f4);
    CL4_SWBP(0x4b0244);
}

/* FUN_004b0244 @ 0x004b0244 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005aacf2) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0244(void)
{
    FUN_00118b28(DAT_005aacf2);
    CL4_SWBP(0x4b0274);
}

/* FUN_004b0274 @ 0x004b0274 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab4a5) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0274(void)
{
    FUN_00118b28(DAT_005ab4a5);
    CL4_SWBP(0x4b02a4);
}

/* FUN_004b02a4 @ 0x004b02a4 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab526) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b02a4(void)
{
    FUN_00118b28(DAT_005ab526);
    CL4_SWBP(0x4b02d4);
}

/* FUN_004b02d4 @ 0x004b02d4 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab54f) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b02d4(void)
{
    FUN_00118b28(DAT_005ab54f);
    CL4_SWBP(0x4b0304);
}

/* FUN_004b0304 @ 0x004b0304 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005aae93) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0304(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005aae93);
    CL4_SWBP(0x4b0334);
}

/* FUN_004b0334 @ 0x004b0334 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_ASSERT__new_slot____L4_Nil____005ab5d1) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0334(void)
{
    FUN_00118b28(s_TB_ASSERT__new_slot____L4_Nil____005ab5d1);
    CL4_SWBP(0x4b0368);
}

/* FUN_004b0368 @ 0x004b0368 - fail-closed assertion/fatal shim.
 * Reports via FUN_000159c0 then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0368(void)
{
    FUN_000159c0();
    CL4_SWBP(0x4b03a0);
}

/* FUN_004b03a0 @ 0x004b03a0 - fail-closed assertion/fatal shim.
 * Reports via FUN_000159c8 then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b03a0(void)
{
    FUN_000159c8();
    CL4_SWBP(0x4b03d8);
}

/* FUN_004b03d8 @ 0x004b03d8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00014fbc then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b03d8(void)
{
    FUN_00014fbc();
    CL4_SWBP(0x4b03f0);
}

/* FUN_004b03f0 @ 0x004b03f0 - fail-closed assertion/fatal shim.
 * Reports via FUN_00014fa0 then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b03f0(void)
{
    FUN_00014fa0();
    CL4_SWBP(0x4b0408);
}

/* FUN_004b0408 @ 0x004b0408 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab916) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0408(void)
{
    FUN_00118b28(DAT_005ab916);
    CL4_SWBP(0x4b0438);
}

/* FUN_004b0438 @ 0x004b0438 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab8e0) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0438(void)
{
    FUN_00118b28(DAT_005ab8e0);
    CL4_SWBP(0x4b0468);
}

/* FUN_004b0468 @ 0x004b0468 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab8c1) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0468(void)
{
    FUN_00118b28(DAT_005ab8c1);
    CL4_SWBP(0x4b0498);
}

/* FUN_004b0498 @ 0x004b0498 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005aacf2) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0498(void)
{
    FUN_00118b28(DAT_005aacf2);
    CL4_SWBP(0x4b04c8);
}

/* FUN_004b04c8 @ 0x004b04c8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab7d5) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b04c8(void)
{
    FUN_00118b28(DAT_005ab7d5);
    CL4_SWBP(0x4b04f8);
}

/* FUN_004b04f8 @ 0x004b04f8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005abaf2) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b04f8(void)
{
    FUN_00118b28(DAT_005abaf2);
    CL4_SWBP(0x4b0528);
}

/* FUN_004b0528 @ 0x004b0528 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005abb2a) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0528(void)
{
    FUN_00118b28(DAT_005abb2a);
    CL4_SWBP(0x4b0558);
}

/* FUN_004b0558 @ 0x004b0558 - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e08 then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0558(void)
{
    FUN_00015e08();
    CL4_SWBP(0x4b0570);
}

/* FUN_004b0570 @ 0x004b0570 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005abc23) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0570(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005abc23);
    CL4_SWBP(0x4b05a0);
}

/* FUN_004b05a0 @ 0x004b05a0 - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005abc59) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b05a0(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005abc59);
    CL4_SWBP(0x4b05c4);
}

/* FUN_004b05c4 @ 0x004b05c4 - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005abc59) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b05c4(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005abc59);
    CL4_SWBP(0x4b05e8);
}

/* FUN_004b05e8 @ 0x004b05e8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005abc59) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b05e8(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005abc59);
    CL4_SWBP(0x4b060c);
}

/* FUN_004b060c @ 0x004b060c - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005abe4f) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b060c(void)
{
    FUN_00118b28(DAT_005abe4f);
    CL4_SWBP(0x4b063c);
}

/* FUN_004b063c @ 0x004b063c - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005abf8d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b063c(void)
{
    FUN_00118b28(DAT_005abf8d);
    CL4_SWBP(0x4b066c);
}

/* FUN_004b066c @ 0x004b066c - fail-closed assertion/fatal shim.
 * Reports via FUN_0001611c (s_internal_h_005aad1c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b066c(void)
{
    FUN_0001611c(s_internal_h_005aad1c);
    CL4_SWBP(0x4b0690);
}

/* FUN_004b0690 @ 0x004b0690 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005abd5d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0690(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005abd5d);
    CL4_SWBP(0x4b06c0);
}

/* FUN_004b06c0 @ 0x004b06c0 - fail-closed assertion/fatal shim.
 * Reports via FUN_0001611c (s_internal_h_005aad1c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b06c0(void)
{
    FUN_0001611c(s_internal_h_005aad1c);
    CL4_SWBP(0x4b06e4);
}

/* FUN_004b06e4 @ 0x004b06e4 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005abd5d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b06e4(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005abd5d);
    CL4_SWBP(0x4b0714);
}

/* FUN_004b0714 @ 0x004b0714 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005aae93) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0714(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005aae93);
    CL4_SWBP(0x4b0744);
}

/* FUN_004b07c0 @ 0x004b07c0 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005abfaf) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b07c0(void)
{
    FUN_00118b28(DAT_005abfaf);
    CL4_SWBP(0x4b07f0);
}

/* FUN_004b07f0 @ 0x004b07f0 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005abfaf) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b07f0(void)
{
    FUN_00118b28(DAT_005abfaf);
    CL4_SWBP(0x4b0820);
}

/* FUN_004b0820 @ 0x004b0820 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005abfe5) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0820(void)
{
    FUN_00118b28(DAT_005abfe5);
    CL4_SWBP(0x4b0850);
}

/* FUN_004b0850 @ 0x004b0850 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179e8 (s_cL4_large_transport_c_005ac025) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0850(void)
{
    FUN_000179e8(s_cL4_large_transport_c_005ac025);
    CL4_SWBP(0x4b0874);
}

/* FUN_004b0874 @ 0x004b0874 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179c8 (s__AppleInternal_Library_BuildRoot_005ac07c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0874(void)
{
    FUN_000179c8(s__AppleInternal_Library_BuildRoot_005ac07c);
    CL4_SWBP(0x4b0898);
}

/* FUN_004b0898 @ 0x004b0898 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179f8 (s_cL4_large_transport_c_005ac025) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0898(void)
{
    FUN_000179f8(s_cL4_large_transport_c_005ac025);
    CL4_SWBP(0x4b08bc);
}

/* FUN_004b08bc @ 0x004b08bc - fail-closed assertion/fatal shim.
 * Reports via FUN_000179e8 (s_cL4_large_transport_c_005ac025) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b08bc(void)
{
    FUN_000179e8(s_cL4_large_transport_c_005ac025);
    CL4_SWBP(0x4b08e0);
}

/* FUN_004b08e0 @ 0x004b08e0 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179e8 (s_cL4_large_transport_c_005ac025) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b08e0(void)
{
    FUN_000179e8(s_cL4_large_transport_c_005ac025);
    CL4_SWBP(0x4b0904);
}

/* FUN_004b0904 @ 0x004b0904 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ac250) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0904(void)
{
    FUN_00118b28(DAT_005ac250);
    CL4_SWBP(0x4b0934);
}

/* FUN_004b0934 @ 0x004b0934 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005abc23) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0934(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005abc23);
    CL4_SWBP(0x4b0964);
}

/* FUN_004b0964 @ 0x004b0964 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179c8 (s__AppleInternal_Library_BuildRoot_005ac07c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0964(void)
{
    FUN_000179c8(s__AppleInternal_Library_BuildRoot_005ac07c);
    CL4_SWBP(0x4b0988);
}

/* FUN_004b0988 @ 0x004b0988 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005abc23) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0988(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005abc23);
    CL4_SWBP(0x4b09b8);
}

/* FUN_004b09b8 @ 0x004b09b8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ac15a) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b09b8(void)
{
    FUN_00118b28(DAT_005ac15a);
    CL4_SWBP(0x4b09e8);
}

/* FUN_004b09e8 @ 0x004b09e8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005aaec9) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b09e8(void)
{
    FUN_00118b28(DAT_005aaec9);
    CL4_SWBP(0x4b0a18);
}

/* FUN_004b0a18 @ 0x004b0a18 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179d8 (s__AppleInternal_Library_BuildRoot_005ac07c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0a18(void)
{
    FUN_000179d8(s__AppleInternal_Library_BuildRoot_005ac07c);
    CL4_SWBP(0x4b0a3c);
}

/* FUN_004b0a3c @ 0x004b0a3c - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ac2b6) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0a3c(void)
{
    FUN_00118b28(DAT_005ac2b6);
    CL4_SWBP(0x4b0a6c);
}

/* FUN_004b0a6c @ 0x004b0a6c - fail-closed assertion/fatal shim.
 * Reports via FUN_000179c8 (s__AppleInternal_Library_BuildRoot_005ac07c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0a6c(void)
{
    FUN_000179c8(s__AppleInternal_Library_BuildRoot_005ac07c);
    CL4_SWBP(0x4b0a90);
}

/* FUN_004b0a90 @ 0x004b0a90 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005aaec9) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0a90(void)
{
    FUN_00118b28(DAT_005aaec9);
    CL4_SWBP(0x4b0ac0);
}

/* FUN_004b0ac0 @ 0x004b0ac0 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179d8 (s__AppleInternal_Library_BuildRoot_005ac07c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0ac0(void)
{
    FUN_000179d8(s__AppleInternal_Library_BuildRoot_005ac07c);
    CL4_SWBP(0x4b0ae4);
}

/* FUN_004b0ae4 @ 0x004b0ae4 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ac2f3) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0ae4(void)
{
    FUN_00118b28(DAT_005ac2f3);
    CL4_SWBP(0x4b0b14);
}

/* FUN_004b0b14 @ 0x004b0b14 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ab4a5) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0b14(void)
{
    FUN_00118b28(DAT_005ab4a5);
    CL4_SWBP(0x4b0b44);
}

/* FUN_004b0b44 @ 0x004b0b44 - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ac322) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0b44(void)
{
    FUN_00118b28(DAT_005ac322);
    CL4_SWBP(0x4b0b74);
}

/* FUN_004b0b74 @ 0x004b0b74 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179c8 (s__AppleInternal_Library_BuildRoot_005ac07c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0b74(void)
{
    FUN_000179c8(s__AppleInternal_Library_BuildRoot_005ac07c);
    CL4_SWBP(0x4b0b98);
}

/* FUN_004b0b98 @ 0x004b0b98 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179f8 (s_cL4_large_transport_c_005ac025) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0b98(void)
{
    FUN_000179f8(s_cL4_large_transport_c_005ac025);
    CL4_SWBP(0x4b0bbc);
}

/* FUN_004b0bbc @ 0x004b0bbc - fail-closed assertion/fatal shim.
 * Reports via FUN_000179d8 (s__AppleInternal_Library_BuildRoot_005ac07c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0bbc(void)
{
    FUN_000179d8(s__AppleInternal_Library_BuildRoot_005ac07c);
    CL4_SWBP(0x4b0be0);
}

/* FUN_004b0be0 @ 0x004b0be0 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179f8 (s_cL4_large_transport_c_005ac025) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0be0(void)
{
    FUN_000179f8(s_cL4_large_transport_c_005ac025);
    CL4_SWBP(0x4b0c04);
}

/* FUN_004b0c04 @ 0x004b0c04 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179c8 (s__AppleInternal_Library_BuildRoot_005ac07c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0c04(void)
{
    FUN_000179c8(s__AppleInternal_Library_BuildRoot_005ac07c);
    CL4_SWBP(0x4b0c28);
}

/* FUN_004b0c28 @ 0x004b0c28 - fail-closed assertion/fatal shim.
 * Reports via FUN_000179c8 (s__AppleInternal_Library_BuildRoot_005ac07c) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0c28(void)
{
    FUN_000179c8(s__AppleInternal_Library_BuildRoot_005ac07c);
    CL4_SWBP(0x4b0c4c);
}

/* FUN_004b0c4c @ 0x004b0c4c - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ac44d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0c4c(void)
{
    FUN_00118b28(DAT_005ac44d);
    CL4_SWBP(0x4b0c7c);
}

/* FUN_004b0c7c @ 0x004b0c7c - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ac48b) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0c7c(void)
{
    FUN_00118b28(DAT_005ac48b);
    CL4_SWBP(0x4b0cac);
}

/* FUN_004b0cac @ 0x004b0cac - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005abd5d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0cac(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005abd5d);
    CL4_SWBP(0x4b0cdc);
}

/* FUN_004b0cdc @ 0x004b0cdc - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (DAT_005ac697) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0cdc(void)
{
    FUN_00118b28(DAT_005ac697);
    CL4_SWBP(0x4b0d0c);
}

/* FUN_004b0d0c @ 0x004b0d0c - fail-closed assertion/fatal shim.
 * Reports via FUN_00118b28 (s_TB_FATAL__overflow_detected_when_005abd5d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0d0c(void)
{
    FUN_00118b28(s_TB_FATAL__overflow_detected_when_005abd5d);
    CL4_SWBP(0x4b0d3c);
}

/* FUN_004b0d3c @ 0x004b0d3c - fail-closed assertion/fatal shim.
 * Reports via FUN_00019820 (s_tb_codec_c_005ac712) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0d3c(void)
{
    FUN_00019820(s_tb_codec_c_005ac712);
    CL4_SWBP(0x4b0d60);
}

/* FUN_004b0d60 @ 0x004b0d60 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019840 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0d60(void)
{
    FUN_00019840(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0d84);
}

/* FUN_004b0d84 @ 0x004b0d84 - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0d84(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0da8);
}

/* FUN_004b0da8 @ 0x004b0da8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019800 (s_tb_codec_c_005ac712) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0da8(void)
{
    FUN_00019800(s_tb_codec_c_005ac712);
    CL4_SWBP(0x4b0dcc);
}

/* FUN_004b0dcc @ 0x004b0dcc - fail-closed assertion/fatal shim.
 * Reports via FUN_00019830 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0dcc(void)
{
    FUN_00019830(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0df0);
}

/* FUN_004b0df0 @ 0x004b0df0 - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0df0(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0e14);
}

/* FUN_004b0e14 @ 0x004b0e14 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019810 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0e14(void)
{
    FUN_00019810(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0e38);
}

/* FUN_004b0e38 @ 0x004b0e38 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019820 (s_tb_codec_c_005ac712) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0e38(void)
{
    FUN_00019820(s_tb_codec_c_005ac712);
    CL4_SWBP(0x4b0e5c);
}

/* FUN_004b0e5c @ 0x004b0e5c - fail-closed assertion/fatal shim.
 * Reports via FUN_00019840 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0e5c(void)
{
    FUN_00019840(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0e80);
}

/* FUN_004b0e80 @ 0x004b0e80 - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0e80(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0ea4);
}

/* FUN_004b0ea4 @ 0x004b0ea4 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019800 (s_tb_codec_c_005ac712) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0ea4(void)
{
    FUN_00019800(s_tb_codec_c_005ac712);
    CL4_SWBP(0x4b0ec8);
}

/* FUN_004b0ec8 @ 0x004b0ec8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019830 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0ec8(void)
{
    FUN_00019830(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0eec);
}

/* FUN_004b0eec @ 0x004b0eec - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0eec(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0f10);
}

/* FUN_004b0f10 @ 0x004b0f10 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019810 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0f10(void)
{
    FUN_00019810(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0f34);
}

/* FUN_004b0f34 @ 0x004b0f34 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019820 (s_tb_codec_c_005ac712) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0f34(void)
{
    FUN_00019820(s_tb_codec_c_005ac712);
    CL4_SWBP(0x4b0f58);
}

/* FUN_004b0f58 @ 0x004b0f58 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019840 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0f58(void)
{
    FUN_00019840(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0f7c);
}

/* FUN_004b0f7c @ 0x004b0f7c - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0f7c(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0fa0);
}

/* FUN_004b0fa0 @ 0x004b0fa0 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019800 (s_tb_codec_c_005ac712) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0fa0(void)
{
    FUN_00019800(s_tb_codec_c_005ac712);
    CL4_SWBP(0x4b0fc4);
}

/* FUN_004b0fc4 @ 0x004b0fc4 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019830 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0fc4(void)
{
    FUN_00019830(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b0fe8);
}

/* FUN_004b0fe8 @ 0x004b0fe8 - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b0fe8(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b100c);
}

/* FUN_004b100c @ 0x004b100c - fail-closed assertion/fatal shim.
 * Reports via FUN_00019810 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b100c(void)
{
    FUN_00019810(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b1030);
}

/* FUN_004b1030 @ 0x004b1030 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019820 (s_tb_codec_c_005ac712) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b1030(void)
{
    FUN_00019820(s_tb_codec_c_005ac712);
    CL4_SWBP(0x4b1054);
}

/* FUN_004b1054 @ 0x004b1054 - fail-closed assertion/fatal shim.
 * Reports via FUN_00019840 (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b1054(void)
{
    FUN_00019840(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b1078);
}

/* FUN_004b1078 @ 0x004b1078 - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b1078(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b109c);
}

/* FUN_004b109c @ 0x004b109c - fail-closed assertion/fatal shim.
 * Reports via FUN_00015e2c (s__AppleInternal_Library_BuildRoot_005ac71d) then traps.
 * Confidence: high (deterministic abort; noreturn). */
static void sk_r40_004b109c(void)
{
    FUN_00015e2c(s__AppleInternal_Library_BuildRoot_005ac71d);
    CL4_SWBP(0x4b10c0);
}

/* ================================================================== */
/* Real functions */
/* ================================================================== */

/* FUN_004afbc4 @ 0x004afbc4 - "Unexpected L4 Error" fatal entry.
 * Runs the per-cpu bootstrap hook (FUN_000017cc) and the region unwind
 * (FUN_004afa6c, r39), then noreturn-panics via FUN_004afae4 with the
 * "Unexpected L4 Error: %s: %zu (err...)" format string.
 * Confidence: high (string-matched fatal; noreturn tail). */
static void sk_r40_004afbc4(void)
{
    FUN_000017cc();      /* per-cpu bootstrap hook */
    FUN_004afa6c();      /* region unwind / cleanup (r39) */
    FUN_004afae4(s_Unexpected_L4_Error___s__zu__err_005a8bef);  /* noreturn */
}

/* FUN_004afc1c @ 0x004afc1c - "Security assertion failed" abort.
 * Noreturn report via FUN_001150e0 with the security-assertion format.
 * Confidence: high (string-matched; noreturn). */
static void sk_r40_004afc1c(void)
{
    FUN_001150e0(s_Security_assertion_failed___s__f_005a8b30);  /* noreturn */
}

/* FUN_004afd3c @ 0x004afd3c - large-transport descriptor decoder.
 * Given a transport context (ctx), a marshalled node descriptor (node) and
 * a destination buffer (buf), allocates a result descriptor whose element
 * count is (node[0x100] >> 14), sizes each element at 0x60 bytes, and sets
 * the per-element flags (0x40), offset (0x44) and count (0x48) so the
 * payload can be split across the message. Commits via FUN_00007d00.
 * Returns the new descriptor, or 0 when allocation fails.
 * Confidence: medium (register-artifact body; decode semantics inferred). */
static long sk_r40_004afd3c(long ctx, long node, word_t buf, word_t tail)
{
    uint count = *(uint *)(node + 0x100) >> 0xe;
    long result = FUN_00002e50(buf, 10, 0,
        (ulong)count * *(byte *)(node + 0x105), 0,
        *(uint *)(node + 0x100), 0, 0);
    if (result != 0) {
        *(char *)(result + 0x41) = (char)((node - *(long *)(ctx + 0xe8)) / 0x110);
        *(word_t *)(result + 0x10) = 0;
        *(word_t *)(result + 0x18) = 0;
        *(byte *)(result + 0x40) = *(byte *)(result + 0x40) | 0x10;
        if (1 < *(byte *)(node + 0x105)) {
            ulong i = 1;
            long off = (ulong)count * 0x60;
            do {
                long e = result + off;
                byte b3 = *(byte *)(e + 0x40);
                *(byte *)(e + 0x40) = b3 & 0xf0 | 4;
                byte b2 = *(byte *)(result + 0x40) & 0x10;
                *(byte *)(e + 0x40) = b3 & 0xe0 | 4 | b2;
                *(byte *)(e + 0x40) = b3 & 0x60 | 4 | b2 | *(byte *)(result + 0x40) & 0x80;
                *(int *)(e + 0x44) = (int)off;
                *(uint *)(e + 0x48) = count;
                i += 1;
                off += (ulong)count * 0x60;
            } while (i < *(byte *)(node + 0x105));
        }
        FUN_00007d00(ctx, node, result, tail, 0);
        *(uint16_t *)(result + 0x42) = *(uint16_t *)(ctx + 0xd0);
    }
    return result;
}

/* FUN_004afe60 @ 0x004afe60 - span/slot size update.
 * Rounds the requested size up to a 0x4000 granule, locates the owning
 * descriptor (via node[0x41] into the ctx slot table) and the chunks
 * current size field at +0x23, and - when the chunk needs shrinking or
 * regrowing - writes the new size and memmoves the trailing payload
 * (FUN_00003788). Returns whether the new size fits the descriptor cap.
 * Confidence: medium (register-artifact body; semantics inferred). */
static bool sk_r40_004afe60(long ctx, ulong node, long data, ulong size)
{
    if ((size & 0x3fff) != 0)
        size = (size & 0x3fc000) + 0x4000;
    uint cap = *(uint *)(*(long *)(ctx + 0xe8) + (ulong)*(byte *)(node + 0x41) * 0x110 + 0x100);
    ulong capv = (ulong)cap;
    if (size <= capv) {
        ulong base = 0xffffffffffff8000;
        if (0x7fffffff < (uint)(int)*(char *)(node + 0x40))
            base = 0xfffffffffffe0000;
        base = base & node;
        uint idx = 0;
        if (capv != 0)
            idx = (uint)(((data - *(long *)(base + 0x38)) +
                ((long)((node - base) + -0x50) / 0x60 & 0xffffffffU) * -0x4000) / capv);
        byte *szp = (byte *)(node + (ulong)((idx & 0xff) * (cap >> 0xe)) * 0x60 + 0x23);
        byte old = *szp;
        ulong oldsz = (ulong)old * 0x4000;
        if (oldsz - size != 0) {
            *szp = (byte)(size >> 0xe);
            if (size <= oldsz && oldsz - size != 0)
                FUN_00003788(*(word_t *)(base + 0x10), data + size,
                             (uint)old - (int)(size >> 0xe));
        }
    }
    return size <= capv;
}

/* FUN_004aff30 @ 0x004aff30 - region assert + handler path.
 * Runs the early-init hook (FUN_00007530), validates the third argument via
 * FUN_0011582c, and on failure invokes the error handler FUN_0001018c
 * passing the offending value (stored to the stack as its argument).
 * Confidence: medium (semantics of the two helpers inferred). */
static void sk_r40_004aff30(word_t a, word_t b, word_t p3)
{
    FUN_00007530();
    int r = FUN_0011582c(p3);
    if (r != 0)
        FUN_0001018c(p3);
}

/* FUN_004b0744 @ 0x004b0744 - supervisor wait / dispatch loop.
 * Spins on CallSupervisor(4) while the status word at param_1[2] is 1, then
 * invokes the state handler FUN_004b23d8(param_1[2]). When the flag byte at
 * param_1[3] is set, resolves a vtable pair via FUN_00034a2c and dispatches
 * through the class vtable slot +0x38 with (base, *param_1, 0, 0), then an
 * indirect call. Finally tail-calls thunk_FUN_00012568(param_1).
 * Confidence: medium (register-artifact dispatch; CallSupervisor + blraa). */
static void sk_r40_004b0744(word_t *param_1)
{
    do {
        CL4_CALLSV(4);   /* CallSupervisor(4): status into x0 */
    } while (param_1[2] == 1);
    FUN_004b23d8(param_1[2]);
    if (*(char *)(param_1 + 3) == 1) {
        skr40_w16 vt = FUN_00034a2c();   /* {x0=lo=base, x1=hi=vtbl} */
        /* blraa x17=0xfbee: call *(vt.hi + 0x38)(vt.lo, *param_1, 0, 0) */
        ((code)(*(word_t *)(vt.hi + 0x38)))(vt.lo, *param_1, 0, 0);
        /* blraa x17=0x9659: indirect method call through *( *param_1 ) */
        ((code)(*(word_t *)*param_1))();
    }
    thunk_FUN_00012568(param_1);
}
