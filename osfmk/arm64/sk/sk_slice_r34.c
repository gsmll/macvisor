/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in program cl4_kernel.raw. Version "cL4 microkernel (cL4
 * (679.100.61))". All names are estimates unless string/header-matched.
 *
 * This file covers wave batch SKR34, slice 0x004a3714-0x004aa050: the Swift
 * Foundation/RegexBuilder _StringProcessing regular-expression engine. These
 * functions are the RegexBuilder AST node lifetime and emission layer: the
 * deep copy / move-assignment and deallocation (deinit) operators for the
 * various regex AST node structs (each a large fixed-layout record whose
 * reference-counted fields are retained/released in a fixed order), the
 * UTF-8/codepoint decode-and-count helpers used while walking the pattern
 * source (LZCOUNT-based leading-zero classification, 1/2/4-byte element
 * reads), and the DSL string-emission helpers that print the character
 * classes, quantifiers, groups and alternation nodes of a parsed regex.
 *
 * All out-of-range callees are declared as externs. Pair-returning (16-byte)
 * helpers use the cl4_result_t struct {lo,hi}. Many helpers are entered with
 * register-globals (unaff_x19/x20 = a self/context pointer carried in a
 * callee-saved register); those are transcribed as named parameters with a
 * note, exactly as in the neighbouring slices.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* 16-byte (two-word) result used by the return-by-value helpers below. */
typedef cl4_result_t sk_r34_pair_t;

/* LZCOUNT - leading-zero count of a 32-bit word (matches the Ghidra
 * pseudo-op). */
static inline unsigned sk_r34_lzcount(uint32_t x)
{ return (unsigned)__builtin_clz((unsigned)x); }
#define LZCOUNT(x) sk_r34_lzcount((uint32_t)(x))

/* SoftwareBreakpoint(1, addr) - trap/fault at a binary address. */
#define SK_TRAP(a) __builtin_trap()

/* ------------------------------------------------------------------ *
 * Out-of-range cL4/Swift-runtime helpers referenced by this slice.
 * Unprototyped AAPCS64 externs. cl4_result_t for the 16-byte returns.
 * FUN_ addresses in comments. Names are estimates.
 * ------------------------------------------------------------------ */
extern unsigned long sk_x_00002534(); /* FUN_00002534 */
extern unsigned long sk_x_000026e8(); /* FUN_000026e8 */
extern unsigned long sk_x_00002834(); /* FUN_00002834 */
extern unsigned long sk_x_000126e8(); /* FUN_000126e8 */
extern unsigned long sk_x_00019858(); /* FUN_00019858 */
extern unsigned long sk_x_00027614(); /* FUN_00027614 */
extern unsigned long sk_x_00027754(); /* FUN_00027754 */
extern unsigned long sk_x_00041138(); /* FUN_00041138 */
extern cl4_result_t sk_x_00068e14(); /* FUN_00068e14 */
extern unsigned long sk_x_0006b438(); /* FUN_0006b438 */
extern cl4_result_t sk_x_0006b6f4(); /* FUN_0006b6f4 */
extern unsigned long sk_x_0007764c(); /* FUN_0007764c */
extern unsigned long sk_x_0007766c(); /* FUN_0007766c */
extern unsigned long sk_x_000776cc(); /* FUN_000776cc */
extern unsigned long sk_x_000776d8(); /* FUN_000776d8 */
extern unsigned long sk_x_0007791c(); /* FUN_0007791c */
extern unsigned long sk_x_000839f8(); /* FUN_000839f8 */
extern unsigned long sk_x_0008409c(); /* FUN_0008409c */
extern unsigned long sk_x_00084180(); /* FUN_00084180 */
extern cl4_result_t sk_x_00084220(); /* FUN_00084220 */
extern unsigned long sk_x_00084234(); /* FUN_00084234 */
extern unsigned long sk_x_000867ec(); /* FUN_000867ec */
extern unsigned long sk_x_00086840(); /* FUN_00086840 */
extern unsigned long sk_x_0008e500(); /* FUN_0008e500 */
extern cl4_result_t sk_x_0008e518(); /* FUN_0008e518 */
extern unsigned long sk_x_0009461c(); /* FUN_0009461c */
extern unsigned long sk_x_000a6f88(); /* FUN_000a6f88 */
extern unsigned long sk_x_000abbdc(); /* FUN_000abbdc */
extern cl4_result_t sk_x_000b4390(); /* FUN_000b4390 */
extern cl4_result_t sk_x_000b43d0(); /* FUN_000b43d0 */
extern unsigned long sk_x_000b4594(); /* FUN_000b4594 */
extern unsigned long sk_x_000b45b0(); /* FUN_000b45b0 */
extern unsigned long sk_x_000dce50(); /* FUN_000dce50 */
extern unsigned long sk_x_00100e34(); /* FUN_00100e34 */
extern unsigned long sk_x_00100efc(); /* FUN_00100efc */
extern unsigned long sk_x_00106e3c(); /* FUN_00106e3c */
extern unsigned long sk_x_00114330(); /* FUN_00114330 */
extern unsigned long sk_x_00117cc4(); /* FUN_00117cc4 */
extern unsigned long sk_x_0014ae44(); /* FUN_0014ae44 */
extern unsigned long sk_x_00167404(); /* FUN_00167404 */
extern unsigned long sk_x_001ae8a8(); /* FUN_001ae8a8 */
extern unsigned long sk_x_001b798c(); /* FUN_001b798c */
extern unsigned long sk_x_002298d4(); /* FUN_002298d4 */
extern unsigned long sk_x_00229a3c(); /* FUN_00229a3c */
extern unsigned long sk_x_00267510(); /* FUN_00267510 */
extern unsigned long sk_x_0029fa0c(); /* FUN_0029fa0c */
extern unsigned long sk_x_002a0cf8(); /* FUN_002a0cf8 */
extern unsigned long sk_x_002a49a8(); /* FUN_002a49a8 */
extern unsigned long sk_x_002a4ab4(); /* FUN_002a4ab4 */
extern unsigned long sk_x_002a9ba8(); /* FUN_002a9ba8 */
extern unsigned long sk_x_002ab130(); /* FUN_002ab130 */
extern unsigned long sk_x_002acbb8(); /* FUN_002acbb8 */
extern unsigned long sk_x_002ae098(); /* FUN_002ae098 */
extern cl4_result_t sk_x_002bc524(); /* FUN_002bc524 */
extern unsigned long sk_x_002bc5bc(); /* FUN_002bc5bc */
extern cl4_result_t sk_x_002bd4e4(); /* FUN_002bd4e4 */
extern cl4_result_t sk_x_002bd540(); /* FUN_002bd540 */
extern unsigned long sk_x_002bd6f4(); /* FUN_002bd6f4 */
extern unsigned long sk_x_002bd724(); /* FUN_002bd724 */
extern unsigned long sk_x_002bd784(); /* FUN_002bd784 */
extern unsigned long sk_x_0032b65c(); /* FUN_0032b65c */
extern unsigned long sk_x_00349530(); /* FUN_00349530 */
extern unsigned long sk_x_0034a018(); /* FUN_0034a018 */
extern unsigned long sk_x_0034ab20(); /* FUN_0034ab20 */
extern unsigned long sk_x_0034b044(); /* FUN_0034b044 */
extern unsigned long sk_x_0034b07c(); /* FUN_0034b07c */
extern cl4_result_t sk_x_0034b264(); /* FUN_0034b264 */
extern unsigned long sk_x_0034b3f8(); /* FUN_0034b3f8 */
extern unsigned long sk_x_0034b7e4(); /* FUN_0034b7e4 */
extern unsigned long sk_x_0034b848(); /* FUN_0034b848 */
extern unsigned long sk_x_0034c444(); /* FUN_0034c444 */
extern unsigned long sk_x_0034cb88(); /* FUN_0034cb88 */
extern unsigned long sk_x_0034cec4(); /* FUN_0034cec4 */
extern unsigned long sk_x_0034e34c(); /* FUN_0034e34c */
extern cl4_result_t sk_x_0034f2f4(); /* FUN_0034f2f4 */
extern unsigned long sk_x_0034fbb0(); /* FUN_0034fbb0 */
extern unsigned long sk_x_00350404(); /* FUN_00350404 */
extern unsigned long sk_x_003504a0(); /* FUN_003504a0 */
extern cl4_result_t sk_x_003504d0(); /* FUN_003504d0 */
extern unsigned long sk_x_00350518(); /* FUN_00350518 */
extern unsigned long sk_x_00350548(); /* FUN_00350548 */
extern unsigned long sk_x_0035056c(); /* FUN_0035056c */
extern unsigned long sk_x_003505c4(); /* FUN_003505c4 */
extern cl4_result_t sk_x_003507e0(); /* FUN_003507e0 */
extern unsigned long sk_x_00350914(); /* FUN_00350914 */
extern unsigned long sk_x_00350c08(); /* FUN_00350c08 */
extern cl4_result_t sk_x_00350c5c(); /* FUN_00350c5c */
extern unsigned long sk_x_003510c4(); /* FUN_003510c4 */
extern unsigned long sk_x_003511d8(); /* FUN_003511d8 */
extern cl4_result_t sk_x_00351244(); /* FUN_00351244 */
extern unsigned long sk_x_003514a0(); /* FUN_003514a0 */
extern unsigned long sk_x_00351b78(); /* FUN_00351b78 */
extern unsigned long sk_x_00351d30(); /* FUN_00351d30 */
extern cl4_result_t sk_x_00351e20(); /* FUN_00351e20 */
extern unsigned long sk_x_00351e3c(); /* FUN_00351e3c */
extern unsigned long sk_x_00352018(); /* FUN_00352018 */
extern unsigned long sk_x_00352ae4(); /* FUN_00352ae4 */
extern unsigned long sk_x_00352b20(); /* FUN_00352b20 */
extern cl4_result_t sk_x_0035300c(); /* FUN_0035300c */
extern unsigned long sk_x_00353238(); /* FUN_00353238 */
extern unsigned long sk_x_0035354c(); /* FUN_0035354c */
extern unsigned long sk_x_003537c4(); /* FUN_003537c4 */
extern unsigned long sk_x_00353960(); /* FUN_00353960 */
extern unsigned long sk_x_00355da8(); /* FUN_00355da8 */
extern unsigned long sk_x_00356364(); /* FUN_00356364 */
extern unsigned long sk_x_00356370(); /* FUN_00356370 */
extern cl4_result_t sk_x_0035638c(); /* FUN_0035638c */
extern unsigned long sk_x_00357c74(); /* FUN_00357c74 */
extern cl4_result_t sk_x_00357cb4(); /* FUN_00357cb4 */
extern unsigned long sk_x_0035847c(); /* FUN_0035847c */
extern unsigned long sk_x_0035944c(); /* FUN_0035944c */
extern unsigned long sk_x_0036b118(); /* FUN_0036b118 */
extern unsigned long sk_x_0036b21c(); /* FUN_0036b21c */
extern unsigned long sk_x_0036b270(); /* FUN_0036b270 */
extern unsigned long sk_x_003728b8(); /* FUN_003728b8 */
extern unsigned long sk_x_00376820(); /* FUN_00376820 */
extern cl4_result_t sk_x_00377824(); /* FUN_00377824 */
extern unsigned long sk_x_00377bec(); /* FUN_00377bec */
extern unsigned long sk_x_00377dcc(); /* FUN_00377dcc */
extern unsigned long sk_x_003a25d4(); /* FUN_003a25d4 */
extern unsigned long sk_x_0041d788(); /* FUN_0041d788 */
extern unsigned long sk_x_0044ca08(); /* FUN_0044ca08 */
extern unsigned long sk_x_0044ca2c(); /* FUN_0044ca2c */
extern unsigned long sk_x_0044ca60(); /* FUN_0044ca60 */
extern unsigned long sk_x_004633e0(); /* FUN_004633e0 */
extern unsigned long sk_x_0046511c(); /* FUN_0046511c */
extern unsigned long sk_x_004657ac(); /* FUN_004657ac */
extern unsigned long sk_x_004661a4(); /* FUN_004661a4 */
extern unsigned long sk_x_0047c528(); /* FUN_0047c528 */
extern unsigned long sk_x_0047c62c(); /* FUN_0047c62c */
extern unsigned long sk_x_0047c7b0(); /* FUN_0047c7b0 */
extern unsigned long sk_x_0047dc1c(); /* FUN_0047dc1c */
extern unsigned long sk_x_0047eff4(); /* FUN_0047eff4 */
extern unsigned long sk_x_0047f0a8(); /* FUN_0047f0a8 */
extern unsigned long sk_x_0048afec(); /* FUN_0048afec */
extern unsigned long sk_x_0048c718(); /* FUN_0048c718 */
extern unsigned long sk_x_0048deb0(); /* FUN_0048deb0 */
extern unsigned long sk_x_0049cb88(); /* FUN_0049cb88 */
extern unsigned long sk_x_0049d630(); /* FUN_0049d630 */
extern unsigned long sk_x_0049d8a8(); /* FUN_0049d8a8 */
extern unsigned long sk_x_0049ec7c(); /* FUN_0049ec7c */
extern unsigned long sk_x_004a1a88(); /* FUN_004a1a88 */
extern unsigned long sk_x_004a2a60(); /* FUN_004a2a60 */
extern cl4_result_t sk_x_004a3038(); /* FUN_004a3038 */
extern cl4_result_t sk_x_004aa47c(); /* FUN_004aa47c */
extern unsigned long sk_x_004aa550(); /* FUN_004aa550 */
extern cl4_result_t sk_x_004aa5dc(); /* FUN_004aa5dc */
extern unsigned long sk_x_004aa638(); /* FUN_004aa638 */
extern unsigned long sk_x_004aa74c(); /* FUN_004aa74c */
extern unsigned long sk_x_004aa8a0(); /* FUN_004aa8a0 */
extern unsigned long sk_x_004aaa9c(); /* FUN_004aaa9c */
extern unsigned long sk_x_004aaaf4(); /* FUN_004aaaf4 */
extern unsigned long sk_x_004aaba8(); /* FUN_004aaba8 */
extern unsigned long sk_x_004aac14(); /* FUN_004aac14 */
extern cl4_result_t sk_x_004aacb0(); /* FUN_004aacb0 */
extern unsigned long sk_x_004aaccc(); /* FUN_004aaccc */
extern unsigned long sk_x_004aad1c(); /* FUN_004aad1c */
extern unsigned long sk_x_004aae14(); /* FUN_004aae14 */
extern unsigned long sk_x_004aae88(); /* FUN_004aae88 */
extern unsigned long sk_x_004aaed8(); /* FUN_004aaed8 */
extern unsigned long sk_x_004aaf48(); /* FUN_004aaf48 */
extern unsigned long sk_x_004aafb8(); /* FUN_004aafb8 */
extern unsigned long sk_x_004ab0ac(); /* FUN_004ab0ac */
extern unsigned long sk_x_004ab0fc(); /* FUN_004ab0fc */
extern cl4_result_t sk_x_004ab10c(); /* FUN_004ab10c */
extern unsigned long sk_x_004ab11c(); /* FUN_004ab11c */
extern unsigned long sk_x_004ab13c(); /* FUN_004ab13c */
extern unsigned long sk_x_004ab150(); /* FUN_004ab150 */
extern unsigned long sk_x_004ab230(); /* FUN_004ab230 */
extern unsigned long sk_x_004ab2dc(); /* FUN_004ab2dc */
extern unsigned long sk_x_004ab310(); /* FUN_004ab310 */
extern unsigned long sk_x_004ab5c8(); /* FUN_004ab5c8 */
extern unsigned long sk_x_004ab5ec(); /* FUN_004ab5ec */
extern unsigned long sk_x_004ab600(); /* FUN_004ab600 */
extern cl4_result_t sk_x_004ab710(); /* FUN_004ab710 */
extern unsigned long sk_x_004ab734(); /* FUN_004ab734 */
extern unsigned long sk_x_004ab74c(); /* FUN_004ab74c */
extern unsigned long sk_x_004ab8fc(); /* FUN_004ab8fc */
extern unsigned long sk_x_004ab954(); /* FUN_004ab954 */
extern cl4_result_t sk_x_004ab9a4(); /* FUN_004ab9a4 */
extern unsigned long sk_x_004aba1c(); /* FUN_004aba1c */
extern unsigned long sk_x_004aba50(); /* FUN_004aba50 */
extern unsigned long sk_x_004aba60(); /* FUN_004aba60 */
extern unsigned long sk_x_004aba70(); /* FUN_004aba70 */
extern unsigned long sk_x_004aba94(); /* FUN_004aba94 */
extern unsigned long sk_x_004abae4(); /* FUN_004abae4 */
extern unsigned long sk_x_004abb80(); /* FUN_004abb80 */
extern unsigned long sk_x_004abbac(); /* FUN_004abbac */
extern unsigned long sk_x_004abbc4(); /* FUN_004abbc4 */
extern unsigned long sk_x_004abbe0(); /* FUN_004abbe0 */
extern unsigned long sk_x_004abc50(); /* FUN_004abc50 */
extern unsigned long sk_x_004abcc0(); /* FUN_004abcc0 */
extern unsigned long sk_x_004abd2c(); /* FUN_004abd2c */
extern unsigned long sk_x_004abda8(); /* FUN_004abda8 */
extern unsigned long sk_x_004abe5c(); /* FUN_004abe5c */
extern unsigned long sk_x_004abec0(); /* FUN_004abec0 */
extern unsigned long sk_x_004abee0(); /* FUN_004abee0 */
extern cl4_result_t sk_x_004abf7c(); /* FUN_004abf7c */
extern unsigned long sk_x_004abf98(); /* FUN_004abf98 */
extern unsigned long sk_x_004ac0d8(); /* FUN_004ac0d8 */
extern unsigned long sk_x_004ac0f0(); /* FUN_004ac0f0 */
extern unsigned long sk_x_004ac1d4(); /* FUN_004ac1d4 */
extern unsigned long sk_x_004ac378(); /* FUN_004ac378 */
extern unsigned long sk_x_004ac3d8(); /* FUN_004ac3d8 */
extern unsigned long sk_x_004ac3fc(); /* FUN_004ac3fc */
extern unsigned long sk_x_004ac40c(); /* FUN_004ac40c */
extern unsigned long sk_x_004ac42c(); /* FUN_004ac42c */
extern unsigned long sk_x_004ac43c(); /* FUN_004ac43c */
extern unsigned long sk_x_004ac45c(); /* FUN_004ac45c */
extern unsigned long sk_x_004ac484(); /* FUN_004ac484 */
extern unsigned long sk_x_004ac49c(); /* FUN_004ac49c */
extern unsigned long sk_x_004ac4ac(); /* FUN_004ac4ac */
extern unsigned long sk_x_004ac4d0(); /* FUN_004ac4d0 */
extern unsigned long sk_x_004ac550(); /* FUN_004ac550 */
extern unsigned long sk_x_004ac660(); /* FUN_004ac660 */
extern unsigned long sk_x_004ac744(); /* FUN_004ac744 */
extern unsigned long sk_x_004ac7b0(); /* FUN_004ac7b0 */
extern unsigned long sk_x_004ac87c(); /* FUN_004ac87c */
extern unsigned long sk_x_004ac948(); /* FUN_004ac948 */
extern unsigned long sk_x_004ac998(); /* FUN_004ac998 */
extern unsigned long sk_x_004aca4c(); /* FUN_004aca4c */
extern cl4_result_t sk_x_004aca58(); /* FUN_004aca58 */
extern unsigned long sk_x_004aca80(); /* FUN_004aca80 */
extern unsigned long sk_x_004acb80(); /* FUN_004acb80 */
extern unsigned long sk_x_004accf0(); /* FUN_004accf0 */

/* Forward declarations for in-slice helpers referenced before their
 * definition. */
static void sk_r34_node_init_stream(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4);
static unsigned long sk_r34_node_publish(unsigned long a);
static void sk_r34_emit_nodepub(unsigned long self, unsigned long src);

/* End of extern block. Bodies below. */


/* ------------------------------------------------------------------ *
 * FUN_004a3714 @ 0x004a3714   (est. sk_regex_triple_release)
 * Ghidra: void FUN_004a3714(undefined8 param_1, undefined8 param_2, byte param_3)
 * If the third argument (a character-class / element-type byte) is < 4,
 * release the second argument (an object reference). This is a shared
 * element-release helper: the low bits of the element type select which
 * release path a sibling uses.
 * Confidence: medium
 * Notes: out-of-range release helper FUN_0036b270.
 */
static void sk_r34_release_elem_lt4(unsigned long a, unsigned long b, unsigned char t)
{
    if (t < 4) {
        sk_x_0036b270(b);
    }
}

/* FUN_004a372c @ 0x004a372c   (est. sk_regex_retain_or_release)
 * Ghidra: void FUN_004a372c(long param_1, undefined8 p2, undefined8 p3, undefined8 p4, undefined8 p5)
 * If the first argument (a condition/flag) is nonzero, forward the remaining
 * three arguments to the triple release helper FUN_0049cb88.
 * Confidence: medium
 */
static void sk_r34_maybe_release_triple(long cond, unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    if (cond != 0) {
        sk_x_0049cb88(a, b, c);
    }
}

/* FUN_004a3744 @ 0x004a3744   (est. sk_regex_elem_release_x20)
 * Ghidra: void FUN_004a3744(void)
 * Release the element stored at self+0x20/0x28 with type byte at self+0x30
 * (a triple), then run the teardown helper FUN_0036b21c. self is carried in
 * x20 (register-global).
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static void sk_r34_elem_release_self(unsigned long self)
{
    sk_x_0049cb88(*(unsigned long *)(self + 0x20),
                  *(unsigned long *)(self + 0x28),
                  *(unsigned char *)(self + 0x30));
    sk_x_0036b21c();
}

/* FUN_004a3748 @ 0x004a3748   (est. sk_regex_elem_release_indirect)
 * Ghidra: void FUN_004a3748(undefined8 param_1, undefined8 param_2)
 * Indirect release of an element: forwards both arguments to the retain
 * helper FUN_0049d630. (Sibling of the 0x3744/0x38e4 pair.)
 * Confidence: medium
 */
static void sk_r34_elem_release_indirect(unsigned long a, unsigned long b)
{
    sk_x_0049d630(a, b);
}

/* FUN_004a3774 @ 0x004a3774   (est. sk_regex_node_init_char)
 * Ghidra: void FUN_004a3774(undefined8 p1, undefined8 p2, undefined8 p3, undefined8 *param_4)
 * Initialise a regex AST node from a 3-field source record at param_4. If the
 * flag byte at param_4+2 is 1 the node is the empty/default form (zeros a
 * 5-word template with a set valid flag); otherwise it decodes the source
 * record via FUN_004a4ac4 / FUN_004a4b14 and emits the DSL representation
 * through a long chain of string-append helpers, ending by emitting the
 * parsed content (FUN_0044ca08 etc).
 * Confidence: low
 * Notes: string refs __asciiOnlyDigits__ (0x5e2fd0) etc; DAT_005a3c90.
 */
static void sk_r34_node_init(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long *src)
{
    unsigned long v[3];
    long n;
    v[0] = p2; v[1] = p3;
    if (*(char *)(src + 2) == 1) {
        /* default/empty node */
        src[3] = 0; src[4] = 0; src[5] = 0; src[6] = 0; src[7] = 0; src[8] = 1;
    } else {
        /* decode the source record and emit DSL */
        sk_r34_node_init_stream(0, 0, 0x656100, 0x5a3c90);
        n = v[0];
        sk_r34_node_publish(0x656100);
        if (n == 0) {
            sk_x_00350914();
            sk_x_00352ae4();
            sk_x_0029fa0c();
            /* ... long emission chain (truncated in decompile) */
        }
    }
}

/* FUN_004a38c8 @ 0x004a38c8   (est. sk_regex_retain_unless_tagged)
 * Ghidra: void FUN_004a38c8(ulong param_1)
 * Retain the object unless it is a tagged small value (the tag mask test
 * (param_1 ^ ~0) & 0xf000000000000007 == 0). Otherwise release/retain via
 * the masked helper FUN_0036b118.
 * Confidence: medium
 */
static void sk_r34_retain_unless_tagged(unsigned long obj)
{
    if (((obj ^ 0xffffffffffffffffULL) & 0xf000000000000007ULL) == 0) {
        return;
    }
    sk_x_0036b118(obj & 0xffffffffffffffbULL);
}

/* FUN_004a38e4 @ 0x004a38e4   (est. sk_regex_elem_apply3)
 * Ghidra: void FUN_004a38e4(undefined8 *param_1, undefined8 param_2)
 * Indirect-dispatch element operation: call the function pointer at self+0x10
 * with the two words of param_1 and param_2. self in x20.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static void sk_r34_elem_apply3(unsigned long *p, unsigned long a, unsigned long self)
{
    (*(void (**)(unsigned long, unsigned long, unsigned long))(self + 0x10))(*p, p[1], a);
}

/* FUN_004a3918 @ 0x004a3918   (est. sk_regex_consume_arg)
 * Ghidra: undefined8 FUN_004a3918(undefined8 param_1)
 * Run the per-step helper FUN_0049d630 then return the argument unchanged.
 * Confidence: medium
 */
static unsigned long sk_r34_run_and_return(unsigned long a)
{
    sk_x_0049d630();
    return a;
}

/* FUN_004a3940 @ 0x004a3940   (est. sk_regex_debug2)
 * Ghidra: void FUN_004a3940(undefined8 param_1, undefined8 param_2)
 * Forward both arguments (swapped) to FUN_0049d8a8.
 * Confidence: medium
 */
static void sk_r34_debug2(unsigned long a, unsigned long b)
{
    sk_x_0049d8a8(b, a);
}

/* FUN_004a3950 @ 0x004a3950   (est. sk_regex_node_default)
 * Ghidra: void FUN_004a3950(undefined8 *param_1)
 * Initialise a node at param_1 to its default state: set the discriminator
 * word to 1, zero the 0x90-byte body (thunk_FUN_00114330(p+1, 0x90)), then
 * set the tail sentinel words: slot 0x13 = 0x8000000000000000, slots
 * 0x14/0x15 = 0.
 * Confidence: medium
 */
static void sk_r34_node_default(unsigned long *p)
{
    *p = 1;
    sk_x_00114330(p + 1, 0x90);
    p[0x14] = 0;
    p[0x15] = 0;
    p[0x13] = 0x8000000000000000ULL;
}

/* FUN_004a398c @ 0x004a398c   (est. sk_regex_node_alloc)
 * Ghidra: undefined8 FUN_004a398c(void)
 * Allocate a fresh regex node: open the arena (FUN_000776d8), and if the
 * self pointer (x20) is null return 0; otherwise bump the node count
 * (FUN_0007764c), allocate 0x10*self bytes (FUN_0007791c), get the bump
 * pointer (thunk_FUN_000126e8) and step it back by 0x20 (FUN_0007766c),
 * returning the base.
 * Confidence: low
 * Notes: self = unaff_x20.
 */
static unsigned long sk_r34_node_alloc(unsigned long self)
{
    unsigned long r;
    long sz;
    sk_x_000776d8();
    if (self == 0) {
        sk_x_000776cc();
        r = 0;
    } else {
        sk_x_0007764c();
        r = sk_x_0007791c(self << 4);
        sz = sk_x_000126e8();
        sk_x_0007766c(sz + -0x20);
    }
    return r;
}

/* FUN_004a39dc @ 0x004a39dc   (est. sk_regex_utf8_advance)
 * Ghidra: void FUN_004a39dc(ulong *param_1, ulong param_2, ulong param_3)
 * Advance a UTF-8/string position. Reads a word from *param_1, computes the
 * byte offset (FUN_00167404), and depending on the tag bits of param_3
 * (bit 0x3c / 0x3d) and param_2 (bit 0x3c) fetches a 1/2/4-byte element at
 * the computed base, decodes it via LZCOUNT to get the character width, and
 * stores the updated position (offset<<16 | 5) back into *param_1. Falls to
 * the multi-byte path FUN_002a49a8 when tag bit 0x3c of param_3 is set.
 * Confidence: medium
 * Notes: classic seL4 tagged-word UTF-8 walker (cf slice r29).
 */
static void sk_r34_utf8_advance(unsigned long *pos, unsigned long base, unsigned long tag)
{
    unsigned long off;
    long addr;
    unsigned char b;
    unsigned w;
    unsigned long v[2];
    off = sk_x_00167404(*pos);
    if ((tag >> 0x3c & 1) == 0) {
        off = off >> 0x10;
        if ((tag >> 0x3d & 1) == 0) {
            if ((base >> 0x3c & 1) == 0) {
                addr = sk_x_002a9ba8(base, tag);
            } else {
                addr = (long)(tag & 0xfffffffffffffffULL) + 0x20;
            }
            b = *(unsigned char *)(addr + off);
        } else {
            v[0] = base;
            v[1] = tag & 0xffffffffffffffULL;
            b = *(unsigned char *)((long)&v + off);
        }
        w = (unsigned)LZCOUNT((unsigned)b << 0x18 ^ 0xffffffffu);
        if (-1 < (char)b) {
            w = 1;
        }
        off = (off + w) * 0x10000 | 5;
    } else {
        off = sk_x_002a49a8(off, base, tag);
    }
    *pos = off;
}

/* FUN_004a3a94 @ 0x004a3a94   (est. sk_regex_str_tail_check)
 * Ghidra: ulong FUN_004a3a94(undefined8 p1, ulong param_2, ulong param_3)
 * Check the tail of a string/element for a terminating byte (0xbf). Reads the
 * current arena size (FUN_002ab130) and traps if it is below 0x4000. If tag
 * bit 0x3c of param_3 is set, defers to the multi-byte helper FUN_002ae098.
 * Otherwise walks to the byte at the computed position and tests whether it
 * is 0xbf (with a SCARRY4 overflow guard on the element decode).
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x4a3b70) on underflow.
 */
static unsigned long sk_r34_str_tail_check(unsigned long p1, unsigned long base, unsigned long tag)
{
    unsigned long sz, r;
    long addr;
    unsigned v;
    unsigned char b;
    unsigned long v2[2];
    sz = sk_x_002ab130();
    if (sz < 0x4000) {
        SK_TRAP(0x4a3b70);
    }
    if ((tag >> 0x3c & 1) != 0) {
        r = sk_x_002ae098(sz, base, tag);
        return r;
    }
    if ((tag >> 0x3d & 1) == 0) {
        if ((base >> 0x3c & 1) == 0) {
            addr = sk_x_002a9ba8(base, tag);
        } else {
            addr = (long)(tag & 0xfffffffffffffffULL) + 0x20;
        }
        v = *(unsigned char *)(addr + (sz >> 0x10) + -1);
        if (v != 0xffffffbf && (v + 0x20000000 < 0x40000000) == 0) {
            /* not a terminating byte */
        }
        /* decode element width and return the count */
        b = *(unsigned char *)(addr + (sz >> 0x10) + -1);
        /* (truncated by decompiler) */
        r = (b == 0xbf) ? 1 : 0;
        return r;
    } else {
        v2[0] = base;
        v2[1] = tag & 0xffffffffffffffULL;
        b = *(unsigned char *)((long)&v2 + (sz >> 0x10) + -1);
        r = (b == 0xbf) ? 1 : 0;
        return r;
    }
}

/* FUN_004a3bd8 @ 0x004a3bd8   (est. sk_regex_elem_dispatch)
 * Ghidra: void FUN_004a3bd8(undefined8 p1, undefined8 p2, undefined8 param_3)
 * Element dispatch: fetch the handler pointer at self+0x10, run the stream
 * setup helpers, and invoke the handler on the decoded element. On failure
 * (result & 1 == 0) returns the empty/error pair; otherwise converts the
 * result and writes it out. Traps (does not return) at 0x4a3c6c on the
 * tagged-nonzero path.
 * Confidence: low
 * Notes: self = unaff_x20; SoftwareBreakpoint(1,0x4a3c6c).
 */
static void sk_r34_elem_dispatch(unsigned long p1, unsigned long p2, unsigned long e, unsigned long self)
{
    unsigned long (*handler)(unsigned long);
    unsigned long r;
    cl4_result_t res;
    sk_x_00084220();
    handler = *(unsigned long (**)(unsigned long))(self + 0x10);
    sk_x_0035056c(e);
    sk_x_00267510();
    r = sk_x_001ae8a8();
    sk_x_003a25d4(0);
    sk_x_004ab11c(r & 0xff00000000ULL);
    if (r != 0) {
        r = (unsigned long)handler(r);
        if ((r & 1) == 0) {
            res = sk_x_00068e14();
        } else {
            res = sk_x_000b4390();
            r = sk_x_001b798c(res.lo, res.hi, 0);
            res.lo = r;
            res.hi = 0;
        }
        sk_x_00084234(res.lo, res.hi, 0);
        return;
    }
    SK_TRAP(0x4a3c6c);
}

/* FUN_004a3c6c @ 0x004a3c6c   (est. sk_regex_elem_release_teardown)
 * Ghidra: void FUN_004a3c6c(void)
 * Release the element at self+0x18 (object release FUN_003a25d4), then run
 * the constant/pair helper FUN_00002834 and the teardown FUN_0036b21c.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static void sk_r34_elem_release_teardown(unsigned long self)
{
    sk_x_003a25d4(*(unsigned long *)(self + 0x18));
    sk_x_00002834();
    sk_x_0036b21c();
}

/* FUN_004a3c70 @ 0x004a3c70   (est. sk_regex_release28_then_teardown)
 * Ghidra: void FUN_004a3c70(void)
 * Release the reference at self+0x18 (FUN_003a25d4) then run the pair helper
 * FUN_00002834 and the teardown FUN_0036b21c. (Sibling of 0x3c6c; this one
 * drops the reference at self+0x18.)
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static void sk_r34_release28_then_teardown(unsigned long self)
{
    sk_x_003a25d4(*(unsigned long *)(self + 0x18));
    sk_x_00002834();
    sk_x_0036b21c();
}

/* FUN_004a3cdc @ 0x004a3cdc   (est. sk_regex_elem_equal)
 * Ghidra: uint FUN_004a3cdc(undefined8 param_1, code *param_2)
 * Compare the 16-byte element stored at self+0x10 against the result of
 * calling the comparator param_2(). Returns 1 if equal, else runs the
 * inequality helper FUN_00351b78 + FUN_002a0cf8. Releases the hi word.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static unsigned sk_r34_elem_equal(unsigned long a, unsigned long (*cmp)(void), unsigned long self)
{
    cl4_result_t mine, o;
    unsigned r;
    mine.lo = *(unsigned long *)(self + 0x10);
    mine.hi = *(unsigned long *)(self + 0x18);
    o.lo = cmp();
    if (o.lo == mine.lo) {
        r = 1;
    } else {
        sk_x_00351b78(o.lo, o.hi);
        r = sk_x_002a0cf8();
    }
    sk_x_003a25d4(o.hi);
    return r & 1;
}

/* FUN_004a3d60 @ 0x004a3d60   (est. sk_regex_elem_byte_equal)
 * Ghidra: bool FUN_004a3d60(void)
 * Compare the byte at self+0x10 against the character-class byte from
 * FUN_002bd6f4. self in x20.
 * Confidence: medium
 */
static bool sk_r34_elem_byte_equal(unsigned long self)
{
    char a, b;
    a = *(char *)(self + 0x10);
    b = (char)sk_x_002bd6f4();
    return a == b;
}

/* FUN_004a3d8c @ 0x004a3d8c   (est. sk_regex_elem_mode_match)
 * Ghidra: bool FUN_004a3d8c(void)
 * Test whether the byte at self+0x10 equals the current element mode byte
 * from FUN_002bd724, combined with the sibling classifier FUN_0046511c.
 * Confidence: medium
 * Notes: relies on flags from the classify helper (in_ZR).
 */
static bool sk_r34_elem_mode_match(unsigned long self)
{
    unsigned char b;
    unsigned w;
    b = *(unsigned char *)(self + 0x10);
    w = sk_x_002bd724();
    sk_x_0046511c();
    return w == b;
}

/* FUN_004a3dcc @ 0x004a3dcc   (est. sk_regex_elem_double_equal)
 * Ghidra: bool FUN_004a3dcc(void)
 * Compare the double at self+0x10 against FUN_002bd784, and additionally
 * require the low byte of the returned word != 1. self in x20.
 * Confidence: medium
 */
static bool sk_r34_elem_double_equal(unsigned long self)
{
    double d;
    unsigned long lo;
    unsigned w;
    d = *(double *)(self + 0x10);
    lo = sk_x_002bd784();
    w = (unsigned)(lo >> 32);
    return d == *(double *)&lo && (w & 0xff) != 1;
}

/* FUN_004a3e20 @ 0x004a3e20   (est. sk_regex_elem_less_equal)
 * Ghidra: bool FUN_004a3e20(undefined8 p1, undefined8 p2, uint param_3)
 * Range/order test: compare the pair (self+0x10, self+0x18) against the
 * pair from FUN_002bc524. Returns the <= result, but only if the low byte
 * of param_3 != 1 (otherwise always false).
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static bool sk_r34_elem_less_equal(unsigned long p1, unsigned long p2, unsigned mode, unsigned long self)
{
    cl4_result_t o;
    unsigned long lo1, hi1;
    bool le, res;
    lo1 = *(unsigned long *)(self + 0x10);
    hi1 = *(unsigned long *)(self + 0x18);
    o = sk_x_002bc524();
    le = o.lo <= lo1;
    if (o.lo == lo1) {
        le = o.hi <= hi1;
    }
    res = false;
    if ((mode & 0xff) != 1) {
        res = le;
    }
    return res;
}

/* FUN_004a3e68 @ 0x004a3e68   (est. sk_regex_elem_char_match)
 * Ghidra: uint FUN_004a3e68(void)
 * Character-match test: fetch the element byte at self+0x10, build the
 * candidate word via FUN_0047f0a8, run FUN_000abbdc, release the candidate
 * and return the low bit.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static unsigned sk_r34_elem_char_match(unsigned long self)
{
    unsigned char b;
    unsigned long w;
    unsigned r;
    b = *(unsigned char *)(self + 0x10);
    w = sk_x_0047f0a8();
    r = sk_x_000abbdc(b, w);
    sk_x_0036b118(w);
    return r & 1;
}

/* FUN_004a3eac @ 0x004a3eac   (est. sk_regex_elem_ascii_equal)
 * Ghidra: bool FUN_004a3eac(void)
 * Compare the ASCII byte at self+0x10 against the byte from FUN_0047eff4.
 * Confidence: medium
 */
static bool sk_r34_elem_ascii_equal(unsigned long self)
{
    char a, b;
    a = *(char *)(self + 0x10);
    b = (char)sk_x_0047eff4();
    return a == b;
}

/* FUN_004a3ed8 @ 0x004a3ed8   (est. sk_regex_elem_release_pair)
 * Ghidra: void FUN_004a3ed8(void)
 * Release the two references at self+0x18 and self+0x20, run the
 * constant/arena helper FUN_000dce50, and the teardown FUN_0036b21c.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static void sk_r34_elem_release_pair(unsigned long self)
{
    sk_x_0036b118(*(unsigned long *)(self + 0x18));
    sk_x_0036b118(*(unsigned long *)(self + 0x20));
    sk_x_000dce50();
    sk_x_0036b21c();
}

/* FUN_004a3edc @ 0x004a3edc   (est. sk_regex_elem_release_pair_dup)
 * Ghidra: void FUN_004a3edc(void)
 * Byte-identical to FUN_004a3ed8: release the two references at self+0x18
 * and self+0x20, run FUN_000dce50 and FUN_0036b21c. (The decompiler emitted
 * a second body for the same target.)
 * Confidence: medium
 */
static void sk_r34_elem_release_pair_dup(unsigned long self)
{
    sk_x_0036b118(*(unsigned long *)(self + 0x18));
    sk_x_0036b118(*(unsigned long *)(self + 0x20));
    sk_x_000dce50();
    sk_x_0036b21c();
}

/* FUN_004a3f04 @ 0x004a3f04   (est. sk_regex_elem_range_byte_equal)
 * Ghidra: bool FUN_004a3f04(void)
 * Compare the byte at self+0x10 against the range-limit byte from
 * FUN_002bc5bc.
 * Confidence: medium
 */
static bool sk_r34_elem_range_byte_equal(unsigned long self)
{
    char a, b;
    a = *(char *)(self + 0x10);
    b = (char)sk_x_002bc5bc();
    return a == b;
}

/* FUN_004a3f38 @ 0x004a3f38   (est. sk_regex_utf8_decode)
 * Ghidra: void FUN_004a3f38(undefined8 p1, undefined8 p2, undefined8 param_3)
 * Decode one UTF-8 codepoint from a tagged string (self/context in x19/x20/
 * x21) and dispatch to the handler at self+0x10. Handles both the 2-byte
 * path (tag bit 0x3d) and the variable-byte path (tag bits 0x3c/0x3d),
 * computing the element width via FUN_00355da8 / FUN_0034b848 and combining
 * the decode result into a tagged word ((w & 0xffffffc0) | (flags & 0x3f)).
 * On success, releases the previous and re-decodes the byte; falls back to
 * the empty pair FUN_00068e14 on failure.
 * Confidence: low
 * Notes: complex; register-globals x19/x20/x21.
 */
static void sk_r34_utf8_decode(unsigned long p1, unsigned long p2, unsigned long e, unsigned long self,
                               unsigned long ctx19, unsigned long ctx21)
{
    unsigned long (*handler)(unsigned long);
    unsigned long cp;
    long addr;
    unsigned char b;
    unsigned w, flags;
    cl4_result_t res;
    sk_x_00357cb4();
    sk_x_0008409c();
    handler = *(unsigned long (**)(unsigned long))(self + 0x10);
    sk_x_003504a0(e);
    cp = sk_x_00167404();
    if ((ctx19 >> 0x3c & 1) != 0) {
        sk_x_003504a0(cp & 0xffffffffffff0000ULL);
        cp = sk_x_002a49a8();
        /* fall through to dispatch */
    } else if ((ctx19 >> 0x3d & 1) != 0) {
        sk_x_004ab0ac();
        cp = sk_x_00355da8(cp >> 0x10);
        if (0 > 0) goto dispatch;
        cp = sk_x_0034b848();
        switch (0) {
        case 1: goto one;
        case 2: goto two;
        case 3: goto three;
        default: goto dispatch;
        }
    } else {
        if ((ctx21 >> 0x3c & 1) == 0) {
            sk_x_00084180();
            addr = sk_x_002a9ba8();
        } else {
            addr = sk_x_00356364();
        }
        cp = sk_x_00355da8(addr + (cp >> 0x10));
        if (0 > 0) goto dispatch;
        cp = sk_x_0034b848();
        switch (0) {
        default: goto dispatch;
        case 1: goto one;
        case 2: goto two;
        case 3: goto three;
        }
    }
two:
    w = sk_x_0034cec4();
    flags = 0;
    goto done;
three:
    w = sk_x_0034a018();
    flags = 0;
done:
    cp = (unsigned long)(w & 0xffffffc0) | (flags & 0x3f);
dispatch:
    cp = (unsigned long)handler(cp);
    if ((cp & 1) == 0) {
        res = sk_x_00068e14();
    } else {
        sk_x_00100efc();
        cp = sk_x_00167404();
        if ((ctx19 >> 0x3c & 1) == 0) {
            cp = cp >> 0x10;
            if ((ctx19 >> 0x3d & 1) == 0) {
                if ((ctx21 >> 0x3c & 1) == 0) {
                    sk_x_00084180();
                    addr = sk_x_002a9ba8();
                } else {
                    addr = sk_x_00356364();
                }
                b = *(unsigned char *)(addr + cp);
            } else {
                addr = sk_x_004ab0ac();
                b = *(unsigned char *)(0 + cp);
            }
            sk_x_0034b3f8(b, addr, 0);
            res.lo = cp + 0;
            res.hi = sk_x_004abd2c(res.lo);
        } else {
            sk_x_003504a0();
            cp = sk_x_002a49a8();
            res.hi = 0;
            res.lo = cp;
        }
    }
    sk_x_00357c74(res.lo, res.hi, 0);
    return;
one:
    cp = sk_x_0034fbb0();
    goto dispatch;
}

/* FUN_004a40b8 @ 0x004a40b8   (est. sk_regex_anychar_match)
 * Ghidra: uint FUN_004a40b8(undefined8 param_1)
 * Match-any-character test. Fetches the candidate pair from FUN_002bd4e4,
 * copies it via FUN_0009461c, classifies with FUN_0047dc1c, releases the
 * count (FUN_003a25d4), and returns the low bit. Then repeats the same for
 * the range pair from FUN_002bd540(param_1).
 * Confidence: medium
 */
static unsigned sk_r34_anychar_match(unsigned long a)
{
    cl4_result_t p;
    unsigned long cnt;
    unsigned r;
    p = sk_x_002bd4e4();
    if (p.hi != 0) {
        sk_x_0009461c(p.lo, p.hi, p.lo);
        r = sk_x_0047dc1c();
        sk_x_003a25d4(p.hi);
        if ((r & 1) != 0) {
            return 1;
        }
    }
    p = sk_x_002bd540(a);
    if (p.hi == 0) {
        r = 0;
    } else {
        sk_x_0009461c(p.lo, p.hi, p.lo);
        r = sk_x_0047dc1c();
        sk_x_003a25d4(p.hi);
        r = r & 1;
    }
    return r;
}

/* FUN_004a4158 @ 0x004a4158   (est. sk_regex_node_flag)
 * Ghidra: uint FUN_004a4158(void)
 * Indirect flag query: call the handler at self+0x10 and return its low bit.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static unsigned sk_r34_node_flag(unsigned long self)
{
    unsigned r;
    r = (*(unsigned (**)(void))(self + 0x10))();
    return r & 1;
}

/* FUN_004a4184 @ 0x004a4184   (est. sk_regex_str_emit_seq)
 * Ghidra: void FUN_004a4184(undefined8 param_1, long param_2)
 * Emit a run of single-char elements: for each of the param_2 entries in the
 * array at param_2+0x20, call FUN_00229a3c with the element. First closes the
 * array (thunk_FUN_002298d4 on the count).
 * Confidence: medium
 */
static void sk_r34_str_emit_seq(unsigned long a, long src)
{
    long n;
    unsigned char *p;
    n = *(long *)(src + 0x10);
    sk_x_002298d4(n);
    if (n != 0) {
        p = (unsigned char *)(src + 0x20);
        do {
            sk_x_00229a3c(*p);
            n = n - 1;
            p = p + 1;
        } while (n != 0);
    }
}

/* FUN_004a41d4 @ 0x004a41d4   (est. sk_regex_elem_call5)
 * Ghidra: void FUN_004a41d4(undefined8 *param_1, undefined8 *param_2, undefined8 *param_3)
 * Indirect 5-arg element call through self+0x10.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static void sk_r34_elem_call5(unsigned long *p1, unsigned long *p2, unsigned long *p3, unsigned long self)
{
    (*(void (**)(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long))(self + 0x10))(
        *p1, p1[1], *p2, *p3, p3[1]);
}

/* FUN_004a4214 @ 0x004a4214   (est. sk_regex_indirect_call)
 * Ghidra: undefined8 FUN_004a4214(undefined8 param_1)
 * Call through a global function pointer (overlapping-symbol warning in
 * Ghidra) and return the argument unchanged.
 * Confidence: low
 * Notes: Ghidra: "Globals starting with '_' overlap smaller symbols".
 */
static unsigned long sk_r34_indirect_call(unsigned long a)
{
    (void)a;
    return a;
}

/* FUN_004a4260 @ 0x004a4260   (est. sk_regex_str_emit_close)
 * Ghidra: void FUN_004a4260(void)
 * Finish emitting a string: run the two stream helpers FUN_004ab13c /
 * FUN_004acb80, release the element at self+0x78 (masked), and run the
 * teardown FUN_0036b21c.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static void sk_r34_str_emit_close(unsigned long self)
{
    sk_x_004ab13c();
    sk_x_004acb80();
    sk_x_0036b118(*(unsigned long *)(self + 0x78) & 0xfffffffffffffffULL);
    sk_x_0036b21c();
}

/* FUN_004a42a0 @ 0x004a42a0   (est. sk_regex_node_build)
 * Ghidra: void FUN_004a42a0(void)
 * Build a regex node: if the arena is empty (FUN_00352b20 == 0), open it,
 * fetch the template from FUN_00027614 and store the constructed node
 * through FUN_00376820 into *self(x19).
 * Confidence: low
 * Notes: self = unaff_x19; in_x3 register arg.
 */
static void sk_r34_node_build(unsigned long self, unsigned long x3)
{
    if (sk_x_00352b20() == 0) {
        sk_x_00106e3c();
        sk_x_00376820(x3, sk_x_00027614());
        *(unsigned long *)self = sk_x_00376820(0, 0);
    }
}

/* FUN_004a42e0 @ 0x004a42e0   (est. sk_regex_elem_emit1)
 * Ghidra: void FUN_004a42e0(undefined8 param_1)
 * Emit one element: forward param_1 and the reference at self+0x10 to
 * FUN_0048afec with flag 1. self in x20.
 * Confidence: medium
 */
static void sk_r34_elem_emit1(unsigned long a, unsigned long self)
{
    sk_x_0048afec(a, *(unsigned long *)(self + 0x10), 1);
}

/* FUN_004a4310 @ 0x004a4310   (est. sk_regex_emit_charclass)
 * Ghidra: void FUN_004a4310(void)
 * Emit a RegexBuilder character-class DSL snippet for the node at
 * self+0x10 (x20). Walks the class descriptor array (each entry 0x18 bytes,
 * count at +0x10 of the payload): for each element tag byte < 0xd it emits
 * one of the pre-built DSL string constants (0x5e2fd0 "asciiOnlyDigits",
 * 0x5e2f30, 0x5e2f10, 0x5e2f70, etc) via FUN_002a4ab4 + FUN_004aca4c +
 * FUN_0041d788; tags 1/3/5/6/7/8 skip emission.
 * Confidence: low
 * Notes: string refs 0x5e2f50/0x5e2f10/0x5e2f30/0x5e2f70; 0x7365726f6e67692e
 *   ("ingenores"?) and 0xed00002865736143 tag words.
 */
static void sk_r34_emit_charclass(unsigned long self)
{
    unsigned long tag0;
    unsigned char *p;
    long n;
    unsigned long v0, v1;
    sk_x_000b4594();
    n = *(long *)(*(long *)(self + 0x10) + 0x10);
    if (n != 0) {
        tag0 = 0xe400000000000000ULL;
        if (*(char *)(self + 0x18) == 0) {
            tag0 = 0xe500000000000000ULL;
        }
        v0 = 0x80000000005e2f50ULL;
        sk_x_00086840(0x5e2fd0);
        p = (unsigned char *)(*(long *)(self + 0x10) + 0x20);
        do {
            if (*p < 0xd) {
                switch (*p) {
                default:
                    sk_x_004aba94();
                    sk_x_002a4ab4(0x10);
                    sk_x_003a25d4(0);
                    v0 = 0x7365726f6e67692eULL;
                    v1 = 0xed00002865736143ULL;
                    break;
                case 1: case 3: case 5: case 6: case 7: case 8:
                    break;
                case 2:
                    sk_x_004aba94();
                    sk_x_002a4ab4(0x1c);
                    sk_x_003a25d4(0);
                    v0 = 0xd000000000000019ULL;
                    v1 = 0x80000000005e2f30ULL;
                    break;
                case 4:
                    sk_x_004aba94();
                    sk_x_002a4ab4(0x17);
                    sk_x_003a25d4(0);
                    v0 = 0xd000000000000014ULL;
                    v1 = 0x80000000005e2f10ULL;
                    break;
                case 9:
                    sk_x_004aba94();
                    sk_x_002a4ab4(0x14);
                    sk_x_003a25d4(0);
                    v0 = 0xd000000000000011ULL;
                    v1 = 0;
                    break;
                case 10:
                    sk_x_004aba94();
                    sk_x_002a4ab4(0x1e);
                    sk_x_003a25d4(0);
                    v0 = 0xd00000000000001bULL;
                    v1 = 0;
                    break;
                case 0xb:
                    sk_x_004aba94();
                    sk_x_002a4ab4(0x18);
                    sk_x_003a25d4(0);
                    v0 = 0xd000000000000015ULL;
                    v1 = 0x80000000005e2f70ULL;
                    break;
                case 0xc:
                    sk_x_004aba94();
                    sk_x_002a4ab4(0x1c);
                    sk_x_003a25d4(0);
                    v0 = 0xd000000000000019ULL;
                    v1 = 0x80000000005e2f50ULL;
                }
                sk_x_000b4390();
                sk_x_002acbb8();
                sk_x_003a25d4(tag0);
                sk_x_00100e34();
                sk_x_002acbb8();
                sk_x_004aca4c(v0);
                sk_x_0041d788();
                sk_x_003a25d4(v1);
            }
            n = n - 1;
            p = p + 0x18;
        } while (n != 0);
    }
    sk_x_000b45b0(0);
}

/* FUN_004a45a0 @ 0x004a45a0   (est. sk_regex_elem_emit0)
 * Ghidra: void FUN_004a45a0(undefined8 param_1)
 * Emit one element: forward param_1 and the reference at self+0x10 to
 * FUN_0048afec with flag 0. self in x20.
 * Confidence: medium
 */
static void sk_r34_elem_emit0(unsigned long a, unsigned long self)
{
    sk_x_0048afec(a, *(unsigned long *)(self + 0x10), 0);
}

/* FUN_004a45d0 @ 0x004a45d0   (est. sk_regex_emit_ref_list)
 * Ghidra: void FUN_004a45d0(void)
 * Emit a list of references: for each of the self+0x10 entries in the array
 * at self+0x20, retain the masked element (FUN_0036b270), run the two stream
 * helpers and emit (FUN_0048afec), then release it.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static void sk_r34_emit_ref_list(unsigned long self)
{
    unsigned long *p;
    long n;
    unsigned long v;
    p = (unsigned long *)(self + 0x20);
    for (n = *(long *)(self + 0x10); n != 0; n = n - 1) {
        v = *p;
        sk_x_0036b270(v & 0xffffffffffffffbULL);
        sk_x_0035354c();
        sk_x_0048afec();
        sk_x_0036b118(v & 0xffffffffffffffbULL);
        p = p + 1;
    }
}

/* FUN_004a463c @ 0x004a463c   (est. sk_regex_elem_retain2)
 * Ghidra: void FUN_004a463c(ulong param_1, undefined8 param_2, char param_3)
 * Element retain: if the type byte param_3 == 1 retain param_2, else retain
 * the masked param_1.
 * Confidence: medium
 */
static void sk_r34_elem_retain2(unsigned long a, unsigned long b, char t)
{
    if (t == 1) {
        sk_x_0036b270(b);
        return;
    }
    sk_x_0036b270(a & 0xffffffffffffffbULL);
}

/* FUN_004a465c @ 0x004a465c   (est. sk_regex_emit_tagged_list)
 * Ghidra: void FUN_004a465c(void)
 * Emit a tagged element list: walk the self+0x10 entries of the array at
 * self+0x30 (each 0x18 bytes = value + type byte), retaining/emitting
 * according to the per-element type tag. self in x20.
 * Confidence: low
 */
static void sk_r34_emit_tagged_list(unsigned long self)
{
    char t;
    unsigned long v;
    long n;
    unsigned char *p;
    cl4_result_t res;
    sk_x_00084220();
    n = *(long *)(self + 0x10);
    if (n != 0) {
        p = (unsigned char *)(self + 0x30);
        do {
            t = *p;
            if (t == 1) {
                sk_x_0036b270(*(unsigned long *)(p - 8));
                sk_x_003507e0();
                sk_x_0041d788();
            } else {
                sk_x_0036b270(*(unsigned long *)(p - 0x10) & 0xffffffffffffffbULL);
                sk_x_0035354c();
                sk_x_0048afec();
            }
            p = p + 0x18;
            res = sk_x_003507e0();
            sk_r34_release_elem_lt4(res.lo, res.hi, (unsigned char)t);
            n = n - 1;
        } while (n != 0);
    }
    sk_x_00084234(0);
}

/* FUN_004a46f0 @ 0x004a46f0   (est. sk_regex_elem_release2)
 * Ghidra: void FUN_004a46f0(ulong param_1, undefined8 param_2, char param_3)
 * Element release: if the type byte param_3 == 1 release param_2 via
 * FUN_003a25d4, else release the masked param_1 via FUN_0036b118.
 * Confidence: medium
 */
static void sk_r34_elem_release2(unsigned long a, unsigned long b, char t)
{
    if (t == 1) {
        sk_x_003a25d4(b);
        return;
    }
    sk_x_0036b118(a & 0xffffffffffffffbULL);
}

/* FUN_004a4724 @ 0x004a4724   (est. sk_regex_emit_group)
 * Ghidra: void FUN_004a4724(void)
 * Emit a RegexBuilder group node: print an opening delimiter (0x28664f796e
 * 61 2e = ".ayOnf(" little-endian? a 4-char DSL token), then for each child
 * in the list at self+0x18->+0x10 run FUN_004ab5c8, and separate children
 * with a comma (0x2c). Also prints the child type tag when the element is
 * non-trivial (tag bits 0x2000000000000000).
 * Confidence: low
 * Notes: self = unaff_x20; string/DSL tokens 0x28664f796e612e,
 *   0xe700000000000000.
 */
static void sk_r34_emit_group(unsigned long self)
{
    unsigned long *p;
    unsigned long w, tag;
    long n;
    unsigned long v0, v1;
    p = *(unsigned long **)(self + 0x10);
    n = *(long *)(self + 0x18);
    sk_x_0044ca60();
    tag = p[1];
    w = *p & 0xffffffffffffULL;
    if ((tag & 0x2000000000000000ULL) != 0) {
        w = (tag >> 0x38) & 0xf;
    }
    if (w != 0) {
        v0 = 0x28664f796e612eULL;
        v1 = 0xe700000000000000ULL;
        sk_x_004abbac();
        sk_x_0036b270(tag);
        sk_x_00100efc();
        sk_x_002acbb8();
        sk_x_004657ac();
        sk_x_002acbb8();
        sk_x_002acbb8(0, 0);
        sk_x_003a25d4(0);
        sk_x_003a25d4(tag);
        sk_x_00100e34();
        sk_x_002acbb8();
        sk_x_0044ca08(v0, v1);
        sk_x_003a25d4(v1);
        if (*(long *)(n + 0x10) != 0) {
            sk_x_004abe5c(0x2c);
        }
        sk_x_0044ca2c();
    }
    n = *(long *)(n + 0x10);
    while (n != 0) {
        sk_x_004ab5c8(&v0);
        sk_x_00117cc4();
        sk_x_004ac7b0();
        sk_r34_debug2(0, 0);
        sk_x_0048deb0(&v0, 0);
        sk_r34_run_and_return(0);
        n = n - 1;
        if (n != 0) {
            sk_x_004abe5c(0x2c);
        }
        sk_x_0044ca2c();
    }
}

/* FUN_004a487c @ 0x004a487c   (est. sk_regex_emit_node_deinit)
 * Ghidra: void FUN_004a487c(void)
 * Deinitialise/emit a regex node: run the pair helpers, emit the two-word
 * node header via FUN_0048c718 with the byte flag, then run FUN_00100e34 and
 * the closing helpers.
 * Confidence: low
 * Notes: self = unaff_x20; constants 0xd000000000000015 / 0x80000000005e3140.
 */
static void sk_r34_emit_node_deinit(unsigned long self)
{
    unsigned long a;
    unsigned char b;
    a = *(unsigned long *)(self + 0x10);
    b = *(unsigned char *)(self + 0x18);
    sk_x_0044ca60();
    sk_x_0044ca08(0xd000000000000015ULL, 0x80000000005e3140ULL);
    sk_x_0048c718(a, b, 0, 0);
    sk_x_00100e34();
    sk_x_0044ca08();
}

/* FUN_004a4938 @ 0x004a4938   (est. sk_regex_emit_node2)
 * Ghidra: void FUN_004a4938(void)
 * Deinitialise/emit a regex node variant: same shape as 0x487c but with the
 * extra prelude FUN_000867ec / FUN_00084180.
 * Confidence: low
 * Notes: self = unaff_x20.
 */
static void sk_r34_emit_node2(unsigned long self)
{
    unsigned long a;
    unsigned char b;
    sk_x_000867ec();
    a = *(unsigned long *)(self + 0x10);
    b = *(unsigned char *)(self + 0x18);
    sk_x_0044ca60();
    sk_x_00084180();
    sk_x_0044ca08();
    sk_x_0048c718(a, b, 0, 0);
    sk_x_00100e34();
    sk_x_0044ca08();
}

/* FUN_004a49a0 @ 0x004a49a0   (est. sk_regex_elem_release3)
 * Ghidra: void FUN_004a49a0(ulong param_1, undefined8 param_2, char param_3)
 * Element release variant: if type byte == 1 release masked param_1 via
 * FUN_0036b118, else release param_2 via FUN_003a25d4.
 * Confidence: medium
 */
static void sk_r34_elem_release3(unsigned long a, unsigned long b, char t)
{
    if (t == 1) {
        sk_x_0036b118(a & 0xffffffffffffffbULL);
        return;
    }
    sk_x_003a25d4(b);
}

/* FUN_004a49c0 @ 0x004a49c0   (est. sk_regex_node_build2)
 * Ghidra: void FUN_004a49c0(void)
 * Build a regex node variant: if the arena is empty, open it, fetch the
 * template and a per-call value from in_x3, and store the constructed node
 * (through FUN_00376820 with the template ref 0x4e9f8c) into *self(x19).
 * Confidence: low
 * Notes: self = unaff_x19; DAT_004e9f8c.
 */
static void sk_r34_node_build2(unsigned long self, unsigned long (*x3)(void))
{
    unsigned long u;
    unsigned long local;
    if (sk_x_00352b20() == 0) {
        sk_x_00106e3c();
        u = sk_x_00027614();
        local = x3();
        *(unsigned long *)self = sk_x_00376820(0x4e9f8c, u, &local);
    }
}

/* FUN_004a4a34 @ 0x004a4a34   (est. sk_regex_forward2)
 * Ghidra: void FUN_004a4a34(undefined8 param_1, undefined8 param_2)
 * Forward both args (swapped) to FUN_0049ec7c.
 * Confidence: medium
 */
static void sk_r34_forward2(unsigned long a, unsigned long b)
{
    sk_x_0049ec7c(b, a);
}

/* FUN_004a4a44 @ 0x004a4a44   (est. sk_regex_str_end)
 * Ghidra: long FUN_004a4a44(ulong param_1)
 * Compute the end offset of a string: if the low bit of param_1 is set, load
 * the indirect pointer (param_1 & ~1); return (base + 0xc) + *(int*)(base+0xc)
 * (base + 0xc + the length stored at base+0xc).
 * Confidence: medium
 */
static long sk_r34_str_end(unsigned long s)
{
    if ((s & 1) != 0) {
        s = *(unsigned long *)(s & 0xfffffffffffffffeULL);
    }
    return (long)(s + 0xc) + (long)*(int *)(s + 0xc);
}

/* FUN_004a4a74 @ 0x004a4a74   (est. sk_regex_node_not_flag)
 * Ghidra: uint FUN_004a4a74(void)
 * Indirect flag query: call the handler at self+0x20 and return the
 * complement's low bit.
 * Confidence: medium
 * Notes: self = unaff_x20.
 */
static unsigned sk_r34_node_not_flag(unsigned long self)
{
    unsigned r;
    r = (*(unsigned (**)(void))(self + 0x20))();
    return (r ^ 0xffffffffu) & 1;
}

/* FUN_004a4aa4 @ 0x004a4aa4   (est. sk_regex_forward_rebuild)
 * Ghidra: void FUN_004a4aa4(undefined8 param_1, undefined8 param_2)
 * Forward both args (swapped) to FUN_004a8ff8 (in-range; declared below).
 * Confidence: medium
 */
static void sk_r34_forward_rebuild(unsigned long a, unsigned long b)
{
    sk_r34_emit_nodepub(b, a);
}

/* FUN_004a4ab4 @ 0x004a4ab4   (est. sk_regex_forward_sibling)
 * Ghidra: void FUN_004a4ab4(undefined8 param_1, undefined8 param_2)
 * Forward both args (swapped) to FUN_004a2a60 (out-of-range sibling).
 * Confidence: medium
 */
static void sk_r34_forward_sibling(unsigned long a, unsigned long b)
{
    sk_x_004a2a60(b, a);
}

/* FUN_004a4ac4 @ 0x004a4ac4   (est. sk_regex_node_init_stream)
 * Ghidra: void FUN_004a4ac4(undefined8 p1, undefined8 p2, undefined8 p3, undefined8 param_4)
 * Initialise a node stream: run the stream opener FUN_003504d0, the constant
 * helper FUN_00002534(p3, param_4), the stream helper FUN_00349530, then
 * indirect-dispatch through offset 0x10 of the result.
 * Confidence: low
 */
static void sk_r34_node_init_stream(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4)
{
    sk_x_003504d0();
    sk_x_00002534(p3, p4);
    sk_x_00349530();
    (*(void (**)(void))(0 + 0x10))();
}

/* FUN_004a4b14 @ 0x004a4b14   (est. sk_regex_node_publish)
 * Ghidra: undefined8 FUN_004a4b14(undefined8 param_1)
 * Publish a constructed node: open the arena (FUN_00106e3c), fetch the
 * template FUN_00002534, dispatch FUN_0034ab20(uVar1,uVar1), then indirect
 * call through offset +8 with param_1. Returns param_1.
 * Confidence: low
 */
static unsigned long sk_r34_node_publish(unsigned long a)
{
    unsigned long t;
    sk_x_00106e3c();
    t = sk_x_00002534();
    sk_x_0034ab20(t, t);
    (*(void (**)(unsigned long))(0 + 8))(a);
    return a;
}

/* FUN_004a4b60 @ 0x004a4b60   (est. sk_regex_forward_sibling2)
 * Ghidra: void FUN_004a4b60(undefined8 param_1, undefined8 param_2)
 * Forward both args (swapped) to FUN_004a1a88 (out-of-range sibling).
 * Confidence: medium
 */
static void sk_r34_forward_sibling2(unsigned long a, unsigned long b)
{
    sk_x_004a1a88(b, a);
}

/* FUN_004a4b70 @ 0x004a4b70   (est. sk_regex_memzero)
 * Ghidra: void FUN_004a4b70(undefined8 param_1)
 * Zero 0x90 bytes at param_1 (thunk_FUN_00114330).
 * Confidence: medium
 */
static void sk_r34_memzero(unsigned long a)
{
    sk_x_00114330(a, 0x90);
}

/* FUN_004a4b7c @ 0x004a4b7c   (est. sk_regex_parse_guard)
 * Ghidra: void FUN_004a4b7c(void)
 * Parse guard: run the stream openers, fetch the class/kind pointers at
 * self+0x10/+0x20 and a handler pointer through FUN_0014ae44 from self+0x30,
 * validate the token (FUN_00027754), build the candidate from FUN_004aa5dc +
 * FUN_00377824, normalize it (FUN_00084180), run the handler and write the
 * boolean result.
 * Confidence: low
 * Notes: self = unaff_x20.
 */
static void sk_r34_parse_guard(unsigned long self)
{
    unsigned long a, b, c;
    unsigned long (*handler)(void);
    unsigned r;
    cl4_result_t res;
    sk_x_00084220();
    sk_x_0008409c();
    a = *(unsigned long *)(self + 0x10);
    b = *(unsigned long *)(self + 0x20);
    handler = (unsigned long (*)(void))sk_x_0014ae44(*(unsigned long *)(self + 0x30));
    sk_x_00027754(b);
    res = sk_x_004aa5dc();
    res = sk_x_00377824(res.lo, res.hi, a);
    sk_x_00084180(res.lo, res.hi, res.lo);
    r = handler();
    sk_x_00084234(r & 1, 0);
}

/* FUN_004a4d80 @ 0x004a4d80   (est. sk_regex_swap_drop)
 * Ghidra: void FUN_004a4d80(void)
 * Swap-and-drop: read the current value through FUN_004ab2dc, replace it,
 * then release the old and new masked values.
 * Confidence: low
 */
static void sk_r34_swap_drop(void)
{
    unsigned long *p;
    unsigned long old;
    p = (unsigned long *)sk_x_004ab2dc();
    old = *p;
    *p = 0;
    sk_x_0036b270(0 & 0xffffffffffffffbULL);
    sk_x_0036b118(old & 0xffffffffffffffbULL);
}

/* FUN_004a4f08 @ 0x004a4f08   (est. sk_regex_node_deinit_large)
 * Ghidra: void FUN_004a4f08(void)
 * Deallocate a large regex node at self(x19): open the arena (FUN_00352b20),
 * then release every reference-counted field in the fixed layout.
 * Confidence: high (release-order deinit, matches siblings)
 * Notes: self = unaff_x19.
 */
static void sk_r34_node_deinit_large(unsigned long self)
{
    sk_x_00352b20();
    sk_x_0036b118();
    sk_x_003a25d4(*(unsigned long *)(self + 0x10));
    sk_x_0036b118(*(unsigned long *)(self + 0x18));
    sk_x_003a25d4(*(unsigned long *)(self + 0x20));
    sk_x_0036b118(*(unsigned long *)(self + 0x28));
    sk_x_0036b118(*(unsigned long *)(self + 0x30));
    sk_x_0036b118(*(unsigned long *)(self + 0x38));
    sk_x_0036b118(*(unsigned long *)(self + 0x40));
    sk_x_0036b118(*(unsigned long *)(self + 0x48));
    sk_x_0036b118(*(unsigned long *)(self + 0x50));
    sk_x_0036b118(*(unsigned long *)(self + 0x58));
    sk_x_0036b118(*(unsigned long *)(self + 0xa0));
    sk_x_0036b118(*(unsigned long *)(self + 0xa8));
    sk_x_003a25d4(*(unsigned long *)(self + 0xb8));
    sk_x_003a25d4(*(unsigned long *)(self + 0xc0));
}

/* FUN_004a4f9c @ 0x004a4f9c   (est. sk_regex_node_copy_large)
 * Ghidra: undefined8 * FUN_004a4f9c(undefined8 *param_1, undefined8 *param_2)
 * Deep-copy a large regex node from param_2 into param_1: copy the entire
 * fixed-layout record (0x19 words + flag byte), then retain every reference
 * field in the fixed order (the "copy with retain" / copy-assignment op).
 * Returns param_1.
 * Confidence: high  (verified 1:1 vs decompile; retain args = source field values)
 * Notes: 16-byte-word record copy + retain-all.
 */
static unsigned long *sk_r34_node_copy_large(unsigned long *dst, unsigned long *src)
{
    unsigned long a, b, c, d, e, f, g, h;
    *dst = *src;
    *(unsigned short *)(dst + 1) = *(unsigned short *)(src + 1);
    dst[3] = src[3];
    dst[2] = src[2];
    dst[5] = src[5];
    dst[4] = src[4];
    dst[7] = src[7];
    dst[6] = src[6];
    dst[9] = src[9];
    dst[8] = src[8];
    dst[0xb] = src[0xb];
    dst[10] = src[10];
    dst[0xd] = src[0xd];
    dst[0xc] = src[0xc];
    dst[0xe] = src[0xe];
    dst[0xf] = src[0xf];
    *(unsigned char *)(dst + 0x10) = *(unsigned char *)(src + 0x10);
    dst[0x11] = src[0x11];
    dst[0x12] = src[0x12];
    *(unsigned char *)(dst + 0x13) = *(unsigned char *)(src + 0x13);
    dst[0x15] = src[0x15];
    dst[0x14] = src[0x14];
    *(unsigned char *)(dst + 0x16) = *(unsigned char *)(src + 0x16);
    dst[0x18] = src[0x18];
    dst[0x17] = src[0x17];
    /* retain every reference field (order + args from decompile) */
    sk_x_0036b270();
    sk_x_004aba1c();
    sk_x_0036b270();
    sk_x_0036b270(src[3]);       /* uVar6 */
    sk_x_004abae4();
    sk_x_0036b270();
    sk_x_0036b270(src[5]);       /* uVar7 */
    sk_x_004ac3d8();
    sk_x_0036b270(src[7]);       /* uVar4 */
    sk_x_004ac4ac();
    sk_x_0036b270(src[2]);       /* uVar2 */
    sk_x_0036b270(src[10]);      /* uVar9 */
    sk_x_0036b270(src[9]);       /* uVar1 */
    sk_x_004ac550();
    sk_x_0036b270(src[0xd]);     /* uVar5 */
    sk_x_004abb80();
    sk_x_0036b270();
    sk_x_0036b270(src[0x18]);    /* uVar3 */
    return dst;
}

/* FUN_004a50e0 @ 0x004a50e0   (est. sk_regex_node_copy_s50)
 * Ghidra: void FUN_004a50e0(void)
 * Move/copy-assign a regex node from x20 into self x19, releasing the
 * replaced reference fields and retaining the new ones in the fixed order.
 * Confidence: medium
 * Notes: self = unaff_x19, src = unaff_x20.
 */
static void sk_r34_node_copy_s50(unsigned long self, unsigned long src)
{
    unsigned long a;
    sk_x_004aae14();
    sk_x_0036b118();
    sk_x_004ac744();
    a = *(unsigned long *)(self + 0x10);
    *(unsigned long *)(self + 0x10) = *(unsigned long *)(src + 0x10);
    sk_x_0036b270();
    sk_x_003a25d4(a);
    sk_x_004ab0fc();
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004aafb8();
    sk_x_0036b270();
    sk_x_003a25d4(a);
    sk_x_004aaed8();
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x30);
    *(unsigned long *)(self + 0x30) = *(unsigned long *)(src + 0x30);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x38);
    *(unsigned long *)(self + 0x38) = *(unsigned long *)(src + 0x38);
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004aae88();
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004aba60();
    sk_x_0036b118(a);
    sk_x_004aba50();
    sk_x_0036b118(a);
    sk_x_004aba70();
    sk_x_0036b118(a);
    *(unsigned long *)(self + 0x60) = *(unsigned long *)(src + 0x60);
    sk_x_004ac0f0();
    *(unsigned char *)(self + 0x80) = *(unsigned char *)(src + 0x80);
    *(unsigned long *)(self + 0x78) = 0;
    *(unsigned long *)(self + 0x88) = *(unsigned long *)(src + 0x88);
    a = *(unsigned long *)(src + 0x90);
    *(unsigned char *)(self + 0x98) = *(unsigned char *)(src + 0x98);
    *(unsigned long *)(self + 0x90) = a;
    a = *(unsigned long *)(self + 0xa0);
    *(unsigned long *)(self + 0xa0) = *(unsigned long *)(src + 0xa0);
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004ac43c();
    sk_x_0036b118(a);
    sk_x_004ac660();
    sk_x_004abf98();
    sk_x_0036b270();
    sk_x_003a25d4(a);
    a = *(unsigned long *)(self + 0xc0);
    *(unsigned long *)(self + 0xc0) = *(unsigned long *)(src + 0xc0);
    sk_x_0036b270();
    sk_x_003a25d4(a);
}

/* FUN_004a5244 @ 0x004a5244   (est. sk_regex_node_copy_s52)
 * Ghidra: void FUN_004a5244(void)
 * Copy-assign a regex node from x20 into self x19 with per-field release of
 * replaced references.
 * Confidence: high
 * Notes: self = unaff_x19, src = unaff_x20. Verified 1:1 vs decompile.
 */
static void sk_r34_node_copy_s52(unsigned long self, unsigned long src)
{
    unsigned long a, b;
    sk_x_004aaf48();
    sk_x_004accf0();
    sk_x_004ac744();
    sk_x_003a25d4(*(unsigned long *)(self + 0x10));
    a = *(unsigned long *)(self + 0x18);
    b = *(unsigned long *)(src + 0x10);
    *(unsigned long *)(self + 0x18) = *(unsigned long *)(src + 0x18);
    *(unsigned long *)(self + 0x10) = b;
    sk_x_0036b118(a);
    sk_x_003a25d4(*(unsigned long *)(self + 0x20));
    a = *(unsigned long *)(self + 0x28);
    b = *(unsigned long *)(src + 0x20);
    *(unsigned long *)(self + 0x28) = *(unsigned long *)(src + 0x28);
    *(unsigned long *)(self + 0x20) = b;
    sk_x_0036b118(a);
    sk_x_0036b118(*(unsigned long *)(self + 0x30));
    a = *(unsigned long *)(self + 0x38);
    b = *(unsigned long *)(src + 0x30);
    *(unsigned long *)(self + 0x38) = *(unsigned long *)(src + 0x38);
    *(unsigned long *)(self + 0x30) = b;
    sk_x_0036b118(a);
    sk_x_0036b118(*(unsigned long *)(self + 0x40));
    a = *(unsigned long *)(self + 0x48);
    b = *(unsigned long *)(src + 0x40);
    *(unsigned long *)(self + 0x48) = *(unsigned long *)(src + 0x48);
    *(unsigned long *)(self + 0x40) = b;
    sk_x_0036b118(a);
    sk_x_0036b118(*(unsigned long *)(self + 0x50));
    a = *(unsigned long *)(self + 0x58);
    b = *(unsigned long *)(src + 0x50);
    *(unsigned long *)(self + 0x58) = *(unsigned long *)(src + 0x58);
    *(unsigned long *)(self + 0x50) = b;
    sk_x_0036b118(a);
    a = *(unsigned long *)(src + 0x60);
    *(unsigned long *)(self + 0x68) = *(unsigned long *)(src + 0x68);
    *(unsigned long *)(self + 0x60) = a;
    a = *(unsigned long *)(src + 0x78);
    *(unsigned long *)(self + 0x70) = *(unsigned long *)(src + 0x70);
    *(unsigned long *)(self + 0x78) = a;
    *(unsigned char *)(self + 0x80) = *(unsigned char *)(src + 0x80);
    a = *(unsigned long *)(src + 0x90);
    *(unsigned long *)(self + 0x88) = *(unsigned long *)(src + 0x88);
    *(unsigned long *)(self + 0x90) = a;
    *(unsigned char *)(self + 0x98) = *(unsigned char *)(src + 0x98);
    sk_x_0036b118(*(unsigned long *)(self + 0xa0));
    sk_x_004ac1d4(*(unsigned long *)(self + 0xa8));
    sk_x_0036b118();
    sk_x_004ac660();
    sk_x_003a25d4(*(unsigned long *)(self + 0xb8));
    a = *(unsigned long *)(self + 0xc0);
    b = *(unsigned long *)(src + 0xb8);
    *(unsigned long *)(self + 0xc0) = *(unsigned long *)(src + 0xc0);
    *(unsigned long *)(self + 0xb8) = b;
    sk_x_003a25d4(a);
}

/* FUN_004a5414 @ 0x004a5414   (est. sk_regex_node_deinit_s54)
 * Ghidra: void FUN_004a5414(void)
 * Deallocate a regex node at self(x19): open the arena and release every
 * reference field in the fixed layout.
 * Confidence: high
 * Notes: self = unaff_x19.
 */
static void sk_r34_node_deinit_s54(unsigned long self)
{
    sk_x_00352b20();
    sk_x_0036b118();
    sk_x_0036b118(*(unsigned long *)(self + 8));
    sk_x_003a25d4(*(unsigned long *)(self + 0x18));
    sk_x_0036b118(*(unsigned long *)(self + 0x20));
    sk_x_003a25d4(*(unsigned long *)(self + 0x28));
    sk_x_0036b118(*(unsigned long *)(self + 0x30));
    sk_x_0036b118(*(unsigned long *)(self + 0x38));
    sk_x_0036b118(*(unsigned long *)(self + 0x40));
    sk_x_0036b118(*(unsigned long *)(self + 0x48));
    sk_x_0036b118(*(unsigned long *)(self + 0x50));
    sk_x_0036b118(*(unsigned long *)(self + 0x58));
    sk_x_0036b118(*(unsigned long *)(self + 0x60));
    sk_x_0036b118(*(unsigned long *)(self + 0xa8));
    sk_x_0036b118(*(unsigned long *)(self + 0xb0));
    sk_x_003a25d4(*(unsigned long *)(self + 0xc0));
    sk_x_003a25d4(*(unsigned long *)(self + 200));
}

/* FUN_004a54b0 @ 0x004a54b0   (est. sk_regex_node_copy_s54)
 * Ghidra: void FUN_004a54b0(void)
 * Copy-assign a regex node: open the pair stream (FUN_0035638c), allocate
 * the destination (FUN_004ab600), copy every field of the 0xd8+ record, then
 * retain all reference fields in the fixed order.
 * Confidence: medium
 * Notes: big field-by-field copy; see decompile.
 */
static void sk_r34_node_copy_s54(unsigned long self)
{
    cl4_result_t p;
    unsigned long *d, *s;
    unsigned long a, b, c, e, f, g, h, i, j, k, l, m;
    p = sk_x_0035638c();
    s = (unsigned long *)(p.hi + 8);
    d = (unsigned long *)sk_x_004ab600();
    *(unsigned short *)(d + 0x10) = *(unsigned short *)(s + 0x10);
    d[0x18] = s[0x18]; d[0x20] = s[0x20];
    d[0x30] = s[0x30]; d[0x28] = s[0x28];
    d[0x40] = s[0x40]; d[0x38] = s[0x38];
    d[0x50] = s[0x50]; d[0x48] = s[0x48];
    d[0x60] = s[0x60]; d[0x58] = s[0x58];
    d[0x70] = s[0x70]; d[0x68] = s[0x68];
    d[0x78] = s[0x78]; d[0x80] = s[0x80];
    *(unsigned char *)(d + 0x88) = *(unsigned char *)(s + 0x88);
    d[0x90] = s[0x90]; d[0x98] = s[0x98];
    *(unsigned char *)(d + 0xa0) = *(unsigned char *)(s + 0xa0);
    d[0xb0] = s[0xb0]; d[0xa8] = s[0xa8];
    *(unsigned char *)(d + 0xb8) = *(unsigned char *)(s + 0xb8);
    d[200] = s[200]; d[0xc0] = s[0xc0];
    *(unsigned char *)(d + 0xd0) = *(unsigned char *)(s + 0xd0);
    *(unsigned long *)(p.lo + 0xd8) = *(unsigned long *)(s + 0xd8);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_004aba1c();
    sk_x_0036b270();
    sk_x_0036b270(0);
    sk_x_004abae4();
    sk_x_0036b270();
    sk_x_0036b270(0);
    sk_x_004ac3d8();
    sk_x_0036b270(0);
    sk_x_004ac4ac();
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_004ac550();
    sk_x_0036b270(0);
    sk_x_004abb80();
    sk_x_0036b270();
    sk_x_0036b270(0);
    sk_x_00356370(p.lo, 0);
}

/* FUN_004a561c @ 0x004a561c   (est. sk_regex_node_copy_s56)
 * Ghidra: void FUN_004a561c(void)
 * Copy-assign a regex node from x20 into self x19 (many fields, release old
 * refs / retain new refs in fixed order).
 * Confidence: medium
 * Notes: self = unaff_x19, src = unaff_x20.
 */
static void sk_r34_node_copy_s56(unsigned long self, unsigned long src)
{
    unsigned long a, b;
    sk_x_004aae14();
    sk_x_0036b118();
    a = *(unsigned long *)(self + 8);
    *(unsigned long *)(self + 8) = *(unsigned long *)(src + 8);
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004aad1c();
    sk_x_004ab0fc();
    sk_x_0036b270();
    sk_x_003a25d4(a);
    sk_x_004aafb8();
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004aaed8();
    sk_x_0036b270();
    sk_x_003a25d4(a);
    a = *(unsigned long *)(self + 0x30);
    *(unsigned long *)(self + 0x30) = *(unsigned long *)(src + 0x30);
    sk_x_0036b270();
    sk_x_0036b118(a);
    b = *(unsigned long *)(self + 0x38);
    *(unsigned long *)(self + 0x38) = *(unsigned long *)(src + 0x38);
    sk_x_0036b270();
    sk_x_0036b118(b);
    sk_x_004aae88();
    sk_x_0036b270();
    sk_x_0036b118(b);
    sk_x_004aba60();
    sk_x_0036b118(b);
    sk_x_004aba50();
    sk_x_0036b118(b);
    sk_x_004aba70();
    sk_x_0036b118(b);
    sk_x_004abda8();
    sk_x_0036b118(b);
    sk_x_004ac0f0();
    *(unsigned long *)(self + 0x78) = 0;
    a = *(unsigned long *)(src + 0x80);
    *(unsigned char *)(self + 0x88) = *(unsigned char *)(src + 0x88);
    *(unsigned long *)(self + 0x80) = a;
    *(unsigned long *)(self + 0x90) = *(unsigned long *)(src + 0x90);
    a = *(unsigned long *)(src + 0x98);
    *(unsigned char *)(self + 0xa0) = *(unsigned char *)(src + 0xa0);
    *(unsigned long *)(self + 0x98) = a;
    sk_x_004ac43c();
    sk_x_0036b118(b);
    a = *(unsigned long *)(self + 0xb0);
    *(unsigned long *)(self + 0xb0) = *(unsigned long *)(src + 0xb0);
    sk_x_0036b270();
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0xb8) = *(unsigned char *)(src + 0xb8);
    a = *(unsigned long *)(self + 0xc0);
    *(unsigned long *)(self + 0xc0) = *(unsigned long *)(src + 0xc0);
    sk_x_0036b270();
    sk_x_003a25d4(a);
    a = *(unsigned long *)(self + 200);
    *(unsigned long *)(self + 200) = *(unsigned long *)(src + 200);
    sk_x_0036b270();
    sk_x_003a25d4(a);
    sk_x_004ac0d8();
}

/* FUN_004a57a0 @ 0x004a57a0   (est. sk_regex_node_copy_s57)
 * Ghidra: void FUN_004a57a0(void)
 * Copy-assign a small regex node from x20 into self x19.
 * Confidence: high
 * Notes: self = unaff_x19 (unsigned long*), src = unaff_x20. Verified 1:1 vs decompile.
 */
static void sk_r34_node_copy_s57(unsigned long *self, unsigned long *src)
{
    unsigned long *p;
    unsigned long a, b;
    p = (unsigned long *)sk_x_00350c5c().lo;
    sk_x_0036b118(*p);
    a = self[1];
    b = *src;
    self[1] = src[1];
    *self = b;
    sk_x_0036b118(a);
    sk_x_004aad1c();
    sk_x_003a25d4(self[3]);
    sk_x_004abec0();
    sk_x_0036b118();
    sk_x_003a25d4(self[5]);
    a = self[6];
    b = src[5];
    self[6] = src[6];
    self[5] = b;
    sk_x_0036b118(a);
    sk_x_0036b118(self[7]);
    sk_x_004ac40c();
    sk_x_0036b118(self[9]);
    sk_x_004ac4d0();
    sk_x_0036b118(self[0xb]);
    sk_x_004ac3fc();
    a = src[0xd];
    self[0xe] = src[0xe];
    self[0xd] = a;
    a = src[0x10];
    self[0xf] = src[0xf];
    self[0x10] = a;
    *(unsigned char *)(self + 0x11) = *(unsigned char *)(src + 0x11);
    a = src[0x13];
    self[0x12] = src[0x12];
    self[0x13] = a;
    *(unsigned char *)(self + 0x14) = *(unsigned char *)(src + 0x14);
    sk_x_0036b118(self[0x15]);
    a = self[0x16];
    b = src[0x15];
    self[0x16] = src[0x16];
    self[0x15] = b;
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0x17) = *(unsigned char *)(src + 0x17);
    sk_x_003a25d4(self[0x18]);
    a = self[0x19];
    b = src[0x18];
    self[0x19] = src[0x19];
    self[0x18] = b;
    sk_x_003a25d4(a);
    sk_x_004ac0d8();
}

/* FUN_004a5c44 @ 0x004a5c44   (est. sk_regex_emit_quant)
 * Ghidra: void FUN_004a5c44(void)
 * Emit a RegexBuilder quantifier node: opens the pair stream (FUN_00357cb4),
 * builds the quantifier string (FUN_003505c4(0x13f), FUN_00351b78(0x13f,...),
 * FUN_00377824), formats it (FUN_003728b8) and dispatches through
 * FUN_00019858.
 * Confidence: low
 * Notes: error/kind tag 0x13f.
 */
static void sk_r34_emit_quant(unsigned long (*handler)(void))
{
    cl4_result_t p, r;
    unsigned long a;
    p = sk_x_00357cb4();
    a = *(unsigned long *)(p.lo + 0x18);
    sk_x_003505c4(0x13f);
    r.lo = handler();
    if (r.lo < 0x40) {
        sk_x_00351b78(0x13f, a);
        r = sk_x_00377824();
        if (r.hi < 0x40) {
            p = sk_x_004ab710();
            sk_x_003728b8(p.lo, p.hi, 2);
            sk_x_00019858();
        }
    }
}

/* FUN_004a5cfc @ 0x004a5cfc   (est. sk_regex_emit_utf8_span)
 * Ghidra: void FUN_004a5cfc(undefined8 p1, undefined8 p2, long param_3)
 * Emit a UTF-8 span: decode the character ranges at param_3+0x10/0x18 through
 * the pair helpers, compute the byte lengths, and dispatch the two decoded
 * spans through indirect function pointers (offset 0x10). Falls to
 * FUN_004ab5ec on the non-trivial path.
 * Confidence: low
 * Notes: DAT_0061628c.
 */
static void sk_r34_emit_utf8_span(unsigned long p1, unsigned long p2, unsigned long src, unsigned long self)
{
    cl4_result_t st, r;
    unsigned long a, b, lo1, lo2;
    unsigned len1, len2;
    unsigned long u1, u2;
    long base1, base2;
    st = sk_x_00351e20();
    lo1 = st.lo; lo2 = st.hi;
    a = *(unsigned long *)(src + 0x10);
    b = *(unsigned long *)(src + 0x18);
    sk_x_004aa74c();
    r = sk_x_00377824(r.lo, b, a, 0x61628c);
    sk_x_000a6f88();
    sk_x_0034e34c();
    len1 = (unsigned)*(unsigned char *)(0 + 0x50);
    base1 = 0 + (unsigned long)(unsigned char)len1;
    sk_x_004aa8a0();
    r = sk_x_00377824(r.lo, b, a, 0x61628c);
    sk_x_000a6f88();
    len2 = (unsigned)*(unsigned char *)(0 + 0x50);
    base2 = (base1 & ~((unsigned long)len1 & 0xff)) + 0 + (unsigned long)(unsigned char)len2;
    if (((len1 | len2) & 0xff) < 8 && ((len1 | len2) & 0x100000) == 0 &&
        (base2 & ~((unsigned long)len2 & 0xff)) + *(long *)(0 + 0x40) < 0x19) {
        u1 = ~((unsigned long)len1 & 0xff);
        u2 = ~((unsigned long)len2 & 0xff);
        (*(void (**)(unsigned long, unsigned long, unsigned long))(0 + 0x10))(lo1, lo2, r.lo);
        (*(void (**)(unsigned long, unsigned long, unsigned long))(0 + 0x10))(base1 + lo1 & u1, base1 + lo2 & u1, a);
        (*(void (**)(unsigned long, unsigned long, unsigned long))(0 + 0x10))(base2 + lo1 & u2, base2 + lo2 & u2, b);
    } else {
        sk_x_004ab5ec(*(unsigned long *)lo2);
    }
    sk_x_00351d30(lo1, 0);
}

/* FUN_004a5ea8 @ 0x004a5ea8   (est. sk_regex_emit_utf8_range)
 * Ghidra: void FUN_004a5ea8(void)
 * Emit a UTF-8 range node: open the pair stream (FUN_00084220), compute the
 * span length, dispatch the two halves through indirect calls, and close.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x004a5f98" - treated as indirect call.
 */
static void sk_r34_emit_utf8_range(void)
{
    cl4_result_t p;
    unsigned long a, lo;
    long len;
    unsigned long b1, b2;
    p = sk_x_00084220();
    lo = p.lo;
    a = *(unsigned long *)(p.hi + 0x10);
    sk_x_004aa74c();
    sk_x_003510c4();
    sk_x_00377824();
    sk_x_0034ab20(0, 0);
    (*(void (**)(unsigned long))(0 + 8))(lo);
    sk_x_004aaba8(*(unsigned long *)(0 + 0x40));
    b1 = (unsigned long)*(unsigned char *)(0 + 0x50);
    (*(void (**)(unsigned long, unsigned long))(0 + 8))(0 + b1 + lo & (b1 ^ 0xffffffffffffffffULL), a);
    len = *(long *)(0 + 0x40);
    sk_x_004aa8a0();
    sk_x_003510c4();
    sk_x_00377824();
    sk_x_00350404(0, 0);
    b2 = (unsigned long)*(unsigned char *)(0 + 0x50);
    (*(void (**)(unsigned long))(0 + 8))(len + lo + b2 + (0 + b1 & (b1 ^ 0xffffffffffffffffULL)) &
                                          (b2 ^ 0xffffffffffffffffULL));
}

/* FUN_004a6078 @ 0x004a6078   (est. sk_regex_emit_utf8_18)
 * Ghidra: void FUN_004a6078(void)
 * Emit a UTF-8 string via the 0x18-slot indirect dispatch pattern: compute
 * the span length, call the two/three 0x18 handlers with the decoded
 * boundaries (x19/x20 register-globals), and close.
 * Confidence: low
 * Notes: self = unaff_x19, unaff_x20.
 */
static void sk_r34_emit_utf8_18(unsigned long self, unsigned long other)
{
    unsigned long a, lo, len1, len2;
    long l;
    sk_x_00084220();
    sk_x_004aa550();
    sk_x_00349530();
    (*(void (**)(void))(0 + 0x18))();
    sk_x_003537c4(*(unsigned long *)(0 + 0x40));
    len1 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = 0 + len1;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x18))(a + self & (len1 ^ 0xffffffffffffffffULL),
                                                           a + other & (len1 ^ 0xffffffffffffffffULL));
    l = *(long *)(0 + 0x40);
    sk_x_004aa8a0();
    sk_x_0034c444();
    sk_x_00377824();
    sk_x_00349530();
    len2 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = (a & (len1 ^ 0xffffffffffffffffULL)) + l + len2;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x18))(a + self & (len2 ^ 0xffffffffffffffffULL),
                                                           a + other & (len2 ^ 0xffffffffffffffffULL));
    sk_x_00084234();
}

/* FUN_004a6154 @ 0x004a6154   (est. sk_regex_emit_utf8_20)
 * Ghidra: void FUN_004a6154(void)
 * Same as 0x6078 but dispatches through the 0x20 slots.
 * Confidence: low
 */
static void sk_r34_emit_utf8_20(unsigned long self, unsigned long other)
{
    unsigned long a, len1, len2;
    long l;
    sk_x_00084220();
    sk_x_004aa550();
    sk_x_00349530();
    (*(void (**)(void))(0 + 0x20))();
    sk_x_003537c4(*(unsigned long *)(0 + 0x40));
    len1 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = 0 + len1;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x20))(a + self & (len1 ^ 0xffffffffffffffffULL),
                                                           a + other & (len1 ^ 0xffffffffffffffffULL));
    l = *(long *)(0 + 0x40);
    sk_x_004aa8a0();
    sk_x_0034c444();
    sk_x_00377824();
    sk_x_00349530();
    len2 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = (a & (len1 ^ 0xffffffffffffffffULL)) + l + len2;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x20))(a + self & (len2 ^ 0xffffffffffffffffULL),
                                                           a + other & (len2 ^ 0xffffffffffffffffULL));
    sk_x_00084234();
}

/* FUN_004a6230 @ 0x004a6230   (est. sk_regex_emit_utf8_28)
 * Ghidra: void FUN_004a6230(void)
 * Same as 0x6078 but dispatches through the 0x28 slots.
 * Confidence: low
 */
static void sk_r34_emit_utf8_28(unsigned long self, unsigned long other)
{
    unsigned long a, len1, len2;
    long l;
    sk_x_00084220();
    sk_x_004aa550();
    sk_x_00349530();
    (*(void (**)(void))(0 + 0x28))();
    sk_x_003537c4(*(unsigned long *)(0 + 0x40));
    len1 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = 0 + len1;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x28))(a + self & (len1 ^ 0xffffffffffffffffULL),
                                                           a + other & (len1 ^ 0xffffffffffffffffULL));
    l = *(long *)(0 + 0x40);
    sk_x_004aa8a0();
    sk_x_0034c444();
    sk_x_00377824();
    sk_x_00349530();
    len2 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = (a & (len1 ^ 0xffffffffffffffffULL)) + l + len2;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x28))(a + self & (len2 ^ 0xffffffffffffffffULL),
                                                           a + other & (len2 ^ 0xffffffffffffffffULL));
    sk_x_00084234();
}

/* FUN_004a630c @ 0x004a630c   (est. sk_regex_utf8_subspan)
 * Ghidra: void FUN_004a630c(undefined8 p1, undefined8 p2, long param_3)
 * Compute and emit a UTF-8 sub-span of the string at param_3: decodes the
 * byte lengths, walks the element array (1/2/4-byte reads selected by the
 * width code), computes the resulting span, and emits via FUN_00351d30 /
 * FUN_000839f8.
 * Confidence: low
 * Notes: DAT_0061628c; LZCOUNT-based element width.
 */
static void sk_r34_utf8_subspan(unsigned long p1, unsigned long p2, unsigned long src, unsigned long self)
{
    unsigned long a, b;
    unsigned w1, w2, len1, len2;
    long l1, l2, l3;
    cl4_result_t st, res;
    unsigned long u15, u17;
    unsigned char *el;
    unsigned long lv[3];
    st = sk_x_00351e20();
    w1 = (unsigned)(st.hi >> 32);
    el = (unsigned char *)st.lo;
    a = *(unsigned long *)(src + 0x10);
    b = *(unsigned long *)(src + 0x18);
    sk_x_004aa74c();
    sk_x_00353960(0, b);
    l1 = sk_x_00377824().lo;
    len1 = *(unsigned *)(l1 - 8 + 0x54);
    l2 = *(long *)(a - 8);
    u17 = *(unsigned *)(l2 + 0x54);
    w2 = u17;
    if (u17 <= len1) w2 = len1;
    sk_x_004aa8a0();
    sk_x_00353960(0, b);
    l3 = sk_x_00377824().lo;
    len2 = *(unsigned *)(l3 - 8 + 0x54);
    if (len2 > w2) w2 = len2;
    u15 = (unsigned long)*(unsigned char *)(l3 + 0x50);
    if (w1 != 0) {
        u17 = (*(long *)(l1 - 8 + 0x40) + (unsigned long)*(unsigned char *)(l2 + 0x50) &
               ((unsigned long)*(unsigned char *)(l2 + 0x50) ^ 0xffffffffffffffffULL)) +
              *(long *)(l2 + 0x40) + u15;
        if (w1 < w2 || w1 - w2 == 0) goto emit;
        /* compute element width and read the value */
        u15 = (u17 & (u15 ^ 0xffffffffffffffffULL)) + *(long *)(l3 + 0x40);
        if ((unsigned)u15 < 4) {
            w2 = (((w1 - w2) + ~(~0u << ((unsigned)u15 * 8 & 0x1f))) >> ((unsigned)u15 * 8 & 0x1f)) + 1;
            if (0xff < w2) {
                if (w2 >> 0x10 == 0) w2 = *(unsigned short *)((long)el + u15);
                else w2 = *(unsigned *)((long)el + u15);
                goto found;
            }
            if (1 < w2) goto found_byte;
        } else {
found_byte:
            w2 = *(unsigned char *)((long)el + u15);
found:
            if (w2 != 0) {
                if ((unsigned)u15 < 4) u17 = w2 - 1 << ((unsigned)u15 * 8 & 0x1f);
                else u17 = 0;
                switch ((unsigned)u15 < 4 ? (unsigned)u15 : 4) {
                default: u17 |= (unsigned char)*el; break;
                case 2: u17 |= (unsigned short)*el; break;
                case 3: u17 |= ((unsigned)(el[2])<<16)|((unsigned)(el[1])<<8)|el[0]; break;
                case 4: u17 |= *(unsigned *)el; break;
                case 0: break;
                }
                sk_x_00351d30(w2 + (unsigned)u17 + 1, 0);
                return;
            }
        }
        if (w2 != 0) {
emit:
            if (w1 < len2) {
                res.hi = len2;
                res.lo = (u17 + (unsigned long)el) & ~u15;
                sk_x_00351d30(res.lo, res.hi, l3, 0);
                sk_x_000839f8();
                return;
            } else {
                res.hi = len1;
                res.lo = (unsigned long)el;
                if (len1 < u17) {
                    res = sk_x_004aca58((unsigned long)el, len1, l3);
                }
                sk_x_00351d30(res.lo, res.hi, a, 0);
                sk_x_000839f8();
                return;
            }
        }
    }
    sk_x_00351d30(0, 0);
}

/* FUN_004a6930 @ 0x004a6930   (est. sk_regex_node_deinit_s69)
 * Ghidra: void FUN_004a6930(void)
 * Deallocate a regex node at self(x19): open the arena and release every
 * reference field in the fixed layout.
 * Confidence: high
 * Notes: self = unaff_x19.
 */
static void sk_r34_node_deinit_s69(unsigned long self)
{
    sk_x_00352b20();
    sk_x_0036b118();
    sk_x_0036b118(*(unsigned long *)(self + 0x18));
    sk_x_003a25d4(*(unsigned long *)(self + 0x20));
    sk_x_0036b118(*(unsigned long *)(self + 0x28));
    sk_x_0036b118(*(unsigned long *)(self + 0x38));
    sk_x_0036b118(*(unsigned long *)(self + 0x40));
    sk_x_0036b118(*(unsigned long *)(self + 0x48));
    sk_x_0036b118(*(unsigned long *)(self + 0x50));
    sk_x_0036b118(*(unsigned long *)(self + 0x58));
    sk_x_0036b118(*(unsigned long *)(self + 0x60));
    sk_x_0036b118(*(unsigned long *)(self + 0x70));
    sk_x_0036b118(*(unsigned long *)(self + 0x78));
    sk_x_0036b118(*(unsigned long *)(self + 0x80));
    sk_x_0036b118(*(unsigned long *)(self + 0x88));
    sk_x_003a25d4(*(unsigned long *)(self + 0x98));
    sk_x_0036b118(*(unsigned long *)(self + 0xb8));
    sk_x_003a25d4(*(unsigned long *)(self + 0xc0));
    sk_x_0036b118(*(unsigned long *)(self + 0xf8));
    sk_x_0036b118(*(unsigned long *)(self + 0x100));
    sk_x_0036b118(*(unsigned long *)(self + 0x108));
    sk_x_0036b118(*(unsigned long *)(self + 0x110));
    sk_x_0036b118(*(unsigned long *)(self + 0x118));
    sk_x_0036b118(*(unsigned long *)(self + 0x120));
    sk_x_0036b118(*(unsigned long *)(self + 0x130));
    sk_x_0036b118(*(unsigned long *)(self + 0x138));
    sk_x_0036b118(*(unsigned long *)(self + 0x140));
    sk_x_0036b118(*(unsigned long *)(self + 0x148));
    sk_x_0036b118(*(unsigned long *)(self + 0x150));
    sk_x_0036b118(*(unsigned long *)(self + 0x160));
}

/* FUN_004a6a38 @ 0x004a6a38   (est. sk_regex_node_copy_deep)
 * Ghidra: void FUN_004a6a38(void)
 * Deep copy-assign a large regex node into self(x19) from the sibling
 * context reached through a chain of out-of-range retain helpers
 * (FUN_004aac14 -> ...+0x20/0x28, FUN_004abcc0 -> ...+0x50, FUN_004abee0 ->
 * ...+0x60, FUN_004ab74c -> ...+0x70/0x78/0x80/0x88/...): copies every
 * reference field of the ~0x168-byte record, then retains each copied
 * reference in the fixed order.
 * Confidence: low
 * Notes: self = unaff_x19; many extraout_x1 register results.
 */
static void sk_r34_node_copy_deep(unsigned long self)
{
    unsigned long *s;
    unsigned long a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
    sk_x_004aac14();
    /* src base derived from the register-global chain */
    s = (unsigned long *)(*(unsigned long *)(0 + 0x28));
    self + 0x28; (void)0;
    sk_x_004abcc0();
    sk_x_004abee0();
    sk_x_004ab74c();
    /* copy fixed fields (offsets from decompile) */
    *(unsigned long *)(self + 0x78) = *(unsigned long *)(s + 0x78);
    *(unsigned long *)(self + 0x70) = *(unsigned long *)(s + 0x70);
    *(unsigned long *)(self + 0x88) = *(unsigned long *)(s + 0x88);
    *(unsigned long *)(self + 0x80) = *(unsigned long *)(s + 0x80);
    *(unsigned long *)(self + 0x90) = *(unsigned long *)(s + 0x90);
    *(unsigned long *)(self + 0x98) = *(unsigned long *)(s + 0x98);
    *(unsigned long *)(self + 0xa8) = *(unsigned long *)(s + 0xa8);
    *(unsigned long *)(self + 0xa0) = *(unsigned long *)(s + 0xa0);
    *(unsigned char *)(self + 0xb0) = *(unsigned char *)(s + 0xb0);
    *(unsigned long *)(self + 0xc0) = *(unsigned long *)(s + 0xc0);
    *(unsigned long *)(self + 0xb8) = *(unsigned long *)(s + 0xb8);
    *(unsigned char *)(self + 0xd0) = *(unsigned char *)(s + 0xd0);
    *(unsigned long *)(self + 200) = *(unsigned long *)(s + 200);
    *(unsigned long *)(self + 0xe0) = *(unsigned long *)(s + 0xe0);
    *(unsigned long *)(self + 0xd8) = *(unsigned long *)(s + 0xd8);
    *(unsigned long *)(self + 0xf0) = *(unsigned long *)(s + 0xf0);
    *(unsigned long *)(self + 0xe8) = *(unsigned long *)(s + 0xe8);
    *(unsigned long *)(self + 0x100) = *(unsigned long *)(s + 0x100);
    *(unsigned long *)(self + 0xf8) = *(unsigned long *)(s + 0xf8);
    *(unsigned long *)(self + 0x108) = *(unsigned long *)(s + 0x108);
    *(unsigned long *)(self + 0x118) = *(unsigned long *)(s + 0x118);
    *(unsigned long *)(self + 0x110) = *(unsigned long *)(s + 0x110);
    *(unsigned long *)(self + 0x120) = *(unsigned long *)(s + 0x120);
    *(unsigned char *)(self + 0x128) = *(unsigned char *)(s + 0x128);
    *(unsigned long *)(self + 0x138) = *(unsigned long *)(s + 0x138);
    *(unsigned long *)(self + 0x130) = *(unsigned long *)(s + 0x130);
    *(unsigned long *)(self + 0x148) = *(unsigned long *)(s + 0x148);
    *(unsigned long *)(self + 0x140) = *(unsigned long *)(s + 0x140);
    *(unsigned long *)(self + 0x150) = *(unsigned long *)(s + 0x150);
    *(unsigned char *)(self + 0x158) = *(unsigned char *)(s + 0x158);
    *(unsigned long *)(self + 0x160) = *(unsigned long *)(s + 0x160);
    *(unsigned char *)(self + 0x168) = *(unsigned char *)(s + 0x168);
    /* retain all references in order */
    sk_x_0036b270();
    sk_x_004aba1c();
    sk_x_0036b270();
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_004abae4();
    sk_x_0036b270();
    sk_x_0036b270();
    sk_x_004ac3d8();
    sk_x_0036b270(0);
    sk_x_004ac550();
    sk_x_0036b270(0);
    sk_x_004abb80();
    sk_x_0036b270();
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_004ac4ac();
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
}

/* FUN_004a6c6c @ 0x004a6c6c   (est. sk_regex_node_copy_s6c)
 * Ghidra: void FUN_004a6c6c(void)
 * Copy-assign a regex node from x20 into self x19, releasing/retaining the
 * reference fields in the fixed order.
 * Confidence: medium
 * Notes: self = unaff_x19, src = unaff_x20.
 */
static void sk_r34_node_copy_s6c(unsigned long self, unsigned long src)
{
    unsigned long a;
    sk_x_004aae14();
    sk_x_0036b118();
    a = *(unsigned long *)(src + 8);
    *(unsigned char *)(self + 0x10) = *(unsigned char *)(src + 0x10);
    *(unsigned long *)(self + 8) = a;
    sk_x_004aaaf4();
    sk_x_004ab0fc();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_004aafb8();
    sk_x_0036b270();
    sk_x_003a25d4();
    sk_x_004aaed8();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_004ab230();
    sk_x_0036b118();
    sk_x_004aae88();
    sk_x_0036b270();
    sk_x_0036b118();
    sk_x_004aba60();
    sk_x_0036b118();
    sk_x_004aba50();
    sk_x_0036b118();
    sk_x_004aba70();
    sk_x_0036b118();
    sk_x_004abda8();
    sk_x_0036b118();
    sk_x_004ab734();
    sk_x_0036b118();
    sk_x_004abbe0();
    sk_x_0036b118();
    sk_x_004abbc4();
    sk_x_0036b118();
    sk_x_004ac49c();
    sk_x_0036b118();
    sk_x_004ac484();
    sk_x_003a25d4();
    sk_x_004661a4();
    sk_x_004ac660();
    sk_x_004abf98();
    sk_x_0036b270();
    sk_x_0036b118();
    a = *(unsigned long *)(self + 0xc0);
    *(unsigned long *)(self + 0xc0) = *(unsigned long *)(src + 0xc0);
    sk_x_0036b270();
    sk_x_003a25d4(a);
    a = *(unsigned long *)(src + 200);
    *(unsigned char *)(self + 0xd0) = *(unsigned char *)(src + 0xd0);
    *(unsigned long *)(self + 200) = a;
    *(unsigned long *)(self + 0xd8) = *(unsigned long *)(src + 0xd8);
    *(unsigned long *)(self + 0xe0) = *(unsigned long *)(src + 0xe0);
    *(unsigned long *)(self + 0xe8) = *(unsigned long *)(src + 0xe8);
    *(unsigned long *)(self + 0xf0) = *(unsigned long *)(src + 0xf0);
    a = *(unsigned long *)(self + 0xf8);
    *(unsigned long *)(self + 0xf8) = *(unsigned long *)(src + 0xf8);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x100);
    *(unsigned long *)(self + 0x100) = *(unsigned long *)(src + 0x100);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x108);
    *(unsigned long *)(self + 0x108) = *(unsigned long *)(src + 0x108);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x110);
    *(unsigned long *)(self + 0x110) = *(unsigned long *)(src + 0x110);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x118);
    *(unsigned long *)(self + 0x118) = *(unsigned long *)(src + 0x118);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x120);
    *(unsigned long *)(self + 0x120) = *(unsigned long *)(src + 0x120);
    sk_x_0036b270();
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0x128) = *(unsigned char *)(src + 0x128);
    a = *(unsigned long *)(self + 0x130);
    *(unsigned long *)(self + 0x130) = *(unsigned long *)(src + 0x130);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x138);
    *(unsigned long *)(self + 0x138) = *(unsigned long *)(src + 0x138);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x140);
    *(unsigned long *)(self + 0x140) = *(unsigned long *)(src + 0x140);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x148);
    *(unsigned long *)(self + 0x148) = *(unsigned long *)(src + 0x148);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x150);
    *(unsigned long *)(self + 0x150) = *(unsigned long *)(src + 0x150);
    sk_x_0036b270();
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0x158) = *(unsigned char *)(src + 0x158);
    a = *(unsigned long *)(self + 0x160);
    *(unsigned long *)(self + 0x160) = *(unsigned long *)(src + 0x160);
    sk_x_0036b270();
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0x168) = *(unsigned char *)(src + 0x168);
}

/* FUN_004a6f08 @ 0x004a6f08   (est. sk_regex_node_copy_s6f)
 * Ghidra: void FUN_004a6f08(void)
 * Copy-assign a regex node from x20 into self x19 (release/retain order).
 * Confidence: medium
 * Notes: self = unaff_x19, src = unaff_x20.
 */
static void sk_r34_node_copy_s6f(unsigned long self, unsigned long src)
{
    unsigned long a, b;
    sk_x_004aaf48();
    sk_x_004accf0();
    *(unsigned long *)(self + 8) = *(unsigned long *)(src + 8);
    *(unsigned char *)(self + 0x10) = *(unsigned char *)(src + 0x10);
    sk_x_004aaaf4();
    a = *(unsigned long *)(self + 0x18);
    *(unsigned long *)(self + 0x18) = *(unsigned long *)(src + 0x18);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x20);
    *(unsigned long *)(self + 0x20) = *(unsigned long *)(src + 0x20);
    sk_x_003a25d4(a);
    sk_x_004ac42c();
    *(unsigned char *)(self + 0x30) = *(unsigned char *)(src + 0x30);
    a = *(unsigned long *)(self + 0x38);
    *(unsigned long *)(self + 0x38) = *(unsigned long *)(src + 0x38);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x40);
    *(unsigned long *)(self + 0x40) = *(unsigned long *)(src + 0x40);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x48);
    *(unsigned long *)(self + 0x48) = *(unsigned long *)(src + 0x48);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x50);
    *(unsigned long *)(self + 0x50) = *(unsigned long *)(src + 0x50);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x58);
    *(unsigned long *)(self + 0x58) = *(unsigned long *)(src + 0x58);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x60);
    *(unsigned long *)(self + 0x60) = *(unsigned long *)(src + 0x60);
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0x68) = *(unsigned char *)(src + 0x68);
    a = *(unsigned long *)(self + 0x70);
    *(unsigned long *)(self + 0x70) = *(unsigned long *)(src + 0x70);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x78);
    *(unsigned long *)(self + 0x78) = *(unsigned long *)(src + 0x78);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x80);
    *(unsigned long *)(self + 0x80) = *(unsigned long *)(src + 0x80);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x88);
    *(unsigned long *)(self + 0x88) = *(unsigned long *)(src + 0x88);
    sk_x_0036b118(a);
    a = *(unsigned long *)(src + 0x98);
    b = *(unsigned long *)(self + 0x98);
    *(unsigned long *)(self + 0x90) = *(unsigned long *)(src + 0x90);
    *(unsigned long *)(self + 0x98) = a;
    sk_x_003a25d4(b);
    sk_x_004ac1d4();
    sk_x_004ac660();
    a = *(unsigned long *)(self + 0xb8);
    *(unsigned long *)(self + 0xb8) = *(unsigned long *)(src + 0xb8);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0xc0);
    *(unsigned long *)(self + 0xc0) = *(unsigned long *)(src + 0xc0);
    sk_x_003a25d4(a);
    *(unsigned long *)(self + 200) = *(unsigned long *)(src + 200);
    *(unsigned char *)(self + 0xd0) = *(unsigned char *)(src + 0xd0);
    a = *(unsigned long *)(src + 0xd8);
    *(unsigned long *)(self + 0xe0) = *(unsigned long *)(src + 0xe0);
    *(unsigned long *)(self + 0xd8) = a;
    a = *(unsigned long *)(src + 0xe8);
    *(unsigned long *)(self + 0xf0) = *(unsigned long *)(src + 0xf0);
    *(unsigned long *)(self + 0xe8) = a;
    a = *(unsigned long *)(self + 0xf8);
    *(unsigned long *)(self + 0xf8) = *(unsigned long *)(src + 0xf8);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x100);
    *(unsigned long *)(self + 0x100) = *(unsigned long *)(src + 0x100);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x108);
    *(unsigned long *)(self + 0x108) = *(unsigned long *)(src + 0x108);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x110);
    *(unsigned long *)(self + 0x110) = *(unsigned long *)(src + 0x110);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x118);
    *(unsigned long *)(self + 0x118) = *(unsigned long *)(src + 0x118);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x120);
    *(unsigned long *)(self + 0x120) = *(unsigned long *)(src + 0x120);
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0x128) = *(unsigned char *)(src + 0x128);
    a = *(unsigned long *)(self + 0x130);
    *(unsigned long *)(self + 0x130) = *(unsigned long *)(src + 0x130);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x138);
    *(unsigned long *)(self + 0x138) = *(unsigned long *)(src + 0x138);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x140);
    *(unsigned long *)(self + 0x140) = *(unsigned long *)(src + 0x140);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x148);
    *(unsigned long *)(self + 0x148) = *(unsigned long *)(src + 0x148);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x150);
    *(unsigned long *)(self + 0x150) = *(unsigned long *)(src + 0x150);
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0x158) = *(unsigned char *)(src + 0x158);
    a = *(unsigned long *)(self + 0x160);
    *(unsigned long *)(self + 0x160) = *(unsigned long *)(src + 0x160);
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0x168) = *(unsigned char *)(src + 0x168);
}

/* FUN_004a7240 @ 0x004a7240   (est. sk_regex_emit_pattern)
 * Ghidra: void FUN_004a7240(void)
 * Emit a full RegexBuilder pattern: open the pair stream (FUN_00041138),
 * guard the size (FUN_003510c4(0x13f)), build the pattern node through
 * FUN_004a3038 / FUN_004aaa9c / FUN_00350548(0xff), format it
 * (FUN_003728b8 with 6), and dispatch via FUN_0035847c.
 * Confidence: low
 * Notes: kind tags 0x13f / 0xff.
 */
static void sk_r34_emit_pattern(void)
{
    cl4_result_t r;
    unsigned long lo;
    sk_x_00041138();
    sk_x_003510c4(0x13f);
    r = sk_x_004a3038();
    lo = r.lo;
    if (r.hi < 0x40) {
        sk_x_004aaa9c();
        sk_x_00350548(0xff);
        sk_x_00377824();
        sk_x_004ab310();
        sk_x_000b43d0();
        sk_x_00351e3c();
        sk_x_00377bec();
        sk_x_004633e0(0, 0);
        r = sk_x_00377824(0x13f, 0, 0);
        lo = r.lo;
        if (r.hi < 0x40) {
            sk_x_004abc50(*(long *)(lo - 8) + 0x40);
            r = sk_x_004ab710();
            sk_x_003728b8(r.lo, r.hi, 6);
            sk_x_00019858();
            goto out;
        }
    }
    r.hi = 0x3f;
    r.lo = lo;
out:
    sk_x_0035847c(r.lo, r.hi, 0);
}

/* FUN_004a731c @ 0x004a731c   (est. sk_regex_emit_concat)
 * Ghidra: void FUN_004a731c(undefined8 p1, undefined8 p2, long param_3)
 * Emit a concatenation/range node: decode the two/three spans at param_3
 * (offsets 0x10/0x18) via the pair helpers, compute the total byte length,
 * and dispatch the three decoded substrings through indirect handlers.
 * Falls to the retain path FUN_00350c08 / FUN_0036b270 on the non-trivial
 * branch.
 * Confidence: low
 * Notes: DAT_0061628c; complex tagged walker.
 */
static void sk_r34_emit_concat(unsigned long p1, unsigned long p2, unsigned long src, unsigned long self)
{
    cl4_result_t st, r;
    unsigned long a, b, c;
    unsigned len1, len2, len3;
    long base1, base2, base3;
    unsigned long u1, u2, u3;
    long *el, *el2;
    st = sk_x_0035300c();
    el = (long *)st.lo; el2 = (long *)st.hi;
    a = *(unsigned long *)(src + 0x10);
    b = *(unsigned long *)(src + 0x18);
    sk_x_004aa74c();
    sk_x_003514a0();
    sk_x_00377824();
    sk_x_000a6f88();
    sk_x_0034e34c();
    len1 = (unsigned)*(unsigned char *)(0 + 0x50);
    base1 = 0 + (unsigned long)(unsigned char)len1;
    base2 = *(long *)(0 + 0x40);
    sk_x_004aa8a0();
    sk_x_003514a0();
    sk_x_00377824();
    sk_x_000a6f88();
    len2 = (unsigned)*(unsigned char *)(0 + 0x50);
    base3 = (base1 & ~((unsigned long)len1 & 0xff)) + base2 + (unsigned long)(unsigned char)len2;
    base2 = *(long *)(0 + 0x40);
    sk_x_004ab310();
    sk_x_003511d8(b);
    sk_x_00377bec();
    r = sk_x_004aa47c(0, 0);
    sk_x_00377824(r.lo, r.hi, 0);
    sk_x_000a6f88();
    len3 = (unsigned)*(unsigned char *)(0 + 0x50);
    u3 = (unsigned long)len3 & 0xff;
    base1 = (base3 & ~((unsigned long)len2 & 0xff)) + base2 + (unsigned long)(unsigned char)len3;
    base2 = *(long *)(0 + 0x40) + 7;
    if ((((len1 | *(unsigned *)(0 + 0x50) | len2) & 0xff) < 8 &&
         (((len1 | *(unsigned *)(0 + 0x50) | len2) | len3) & 0x100000) == 0) &&
        (base2 + (base1 & (u3 ^ 0xffffffffffffffffULL)) & 0xfffffffffffffff8ULL) + 0x12 < 0x19) {
        u1 = ~((unsigned long)len1 & 0xff);
        u2 = ~((unsigned long)len2 & 0xff);
        sk_x_00350c08(*(unsigned long *)(0 + 0x10), el);
        (*(void (**)(void))(0))();
        (*(void (**)(unsigned long, unsigned long, unsigned long))(0 + 0x10))(
            base1 + (long)el & u1, base1 + (long)el2 & u1, a);
        (*(void (**)(unsigned long, unsigned long, unsigned long))(0 + 0x10))(
            base3 + (long)el & u2, base3 + (long)el2 & u2, b);
        r = sk_x_000b43d0(*(unsigned long *)(0 + 0x10));
        (*(void (**)(unsigned long, unsigned long, unsigned long))(0))(
            r.lo, r.hi, 0);
        /* copy the small tail record */
        *((unsigned long *)(base2 + (base1 + (long)el & ~u3) & 0xfffffffffffffff8ULL)) =
            *((unsigned long *)(base2 + (base1 + (long)el2 & ~u3) & 0xfffffffffffffff8ULL));
    } else {
        u3 = (unsigned long)((len1 | *(unsigned *)(0 + 0x50) | len2) | 7);
        base1 = *el2;
        *el = base1;
        sk_x_0036b270();
    }
    sk_x_00353238(el, 0);
}

/* FUN_004a75d4 @ 0x004a75d4   (est. sk_regex_emit_range_8)
 * Ghidra: void FUN_004a75d4(void)
 * Emit a UTF-8 range via the 0x8-slot indirect pattern (three spans).
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x004a7728" - treated as indirect call.
 */
static void sk_r34_emit_range_8(void)
{
    cl4_result_t p;
    unsigned long a, lo;
    long l1, l2, l3;
    unsigned long b1, b2, b3, x;
    unsigned long r;
    p = sk_x_0008e518();
    lo = p.lo;
    a = *(unsigned long *)(p.hi + 0x10);
    sk_x_004aa74c();
    sk_x_003510c4();
    sk_x_00377824();
    sk_x_0034ab20();
    (*(void (**)(unsigned long, unsigned long))(0 + 8))(lo, 0);
    sk_x_004aaba8(*(unsigned long *)(0 + 0x40));
    b1 = (unsigned long)*(unsigned char *)(0 + 0x50);
    (*(void (**)(unsigned long, unsigned long))(0 + 8))(0 + b1 + lo & (b1 ^ 0xffffffffffffffffULL), a);
    l1 = *(long *)(0 + 0x40);
    sk_x_004aa8a0();
    sk_x_003510c4();
    sk_x_00377824();
    sk_x_0034ab20(0, 0);
    b2 = (unsigned long)*(unsigned char *)(0 + 0x50);
    x = (0 + b1 & (b1 ^ 0xffffffffffffffffULL)) + l1 + b2;
    (*(void (**)(unsigned long))(0 + 8))(x + lo & (b2 ^ 0xffffffffffffffffULL));
    l2 = *(long *)(0 + 0x40);
    sk_x_004ab310();
    sk_x_0006b6f4();
    sk_x_00351e3c();
    sk_x_00377bec();
    p = sk_x_004aa47c(0, 0);
    sk_x_00377824(p.lo, p.hi, 0);
    sk_x_00350404(0, 0);
    b3 = (unsigned long)*(unsigned char *)(0 + 0x50);
    (*(void (**)(unsigned long))(0 + 8))(l2 + lo + b3 +
                                          (x & (b2 ^ 0xffffffffffffffffULL)) &
                                          (b3 ^ 0xffffffffffffffffULL));
}

/* FUN_004a7874 @ 0x004a7874   (est. sk_regex_emit_utf8_18b)
 * Ghidra: void FUN_004a7874(void)
 * UTF-8 span emitter via the 0x18-slot dispatch pattern with a third span.
 * Confidence: low
 * Notes: self = unaff_x19, unaff_x20.
 */
static void sk_r34_emit_utf8_18b(unsigned long self, unsigned long other)
{
    unsigned long a, lo, l1, l2;
    long l;
    cl4_result_t p, r;
    unsigned long u3, u4;
    sk_x_0008e518();
    sk_x_004aa550();
    sk_x_0034ab20();
    (*(void (**)(void))(0 + 0x18))();
    sk_x_003537c4(*(unsigned long *)(0 + 0x40));
    u3 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = 0 + u3;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x18))(a + self & (u3 ^ 0xffffffffffffffffULL),
                                                           a + other & (u3 ^ 0xffffffffffffffffULL));
    l = *(long *)(0 + 0x40);
    sk_x_004aa8a0();
    sk_x_0034c444();
    sk_x_00377824();
    sk_x_00349530();
    u4 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = (a & (u3 ^ 0xffffffffffffffffULL)) + l + u4;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x18))(a + self & (u4 ^ 0xffffffffffffffffULL),
                                                           a + other & (u4 ^ 0xffffffffffffffffULL));
    l = *(long *)(0 + 0x40);
    sk_x_004aacb0();
    p = sk_x_004aa47c(0, 0);
    sk_x_00377824(p.lo, p.hi, 0);
    sk_x_00349530();
    u3 = (unsigned long)*(unsigned char *)(0 + 0x50);
    l1 = (a & (u4 ^ 0xffffffffffffffffULL)) + l + u3;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x18))(l1 + self & (u3 ^ 0xffffffffffffffffULL),
                                                           l1 + other & (u3 ^ 0xffffffffffffffffULL));
    sk_x_004aa638(*(unsigned long *)(0 + 0x40));
    sk_x_0008e500(0, 0);
}

/* FUN_004a79bc @ 0x004a79bc   (est. sk_regex_emit_utf8_20b)
 * Ghidra: void FUN_004a79bc(void)
 * UTF-8 span emitter via the 0x20-slot dispatch pattern with a third span.
 * Confidence: low
 */
static void sk_r34_emit_utf8_20b(unsigned long self, unsigned long other)
{
    unsigned long a, l1;
    long l;
    cl4_result_t p;
    unsigned long u3, u4;
    sk_x_0008e518();
    sk_x_004aa550();
    sk_x_0034ab20();
    (*(void (**)(void))(0 + 0x20))();
    sk_x_003537c4(*(unsigned long *)(0 + 0x40));
    u3 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = 0 + u3;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x20))(a + self & (u3 ^ 0xffffffffffffffffULL),
                                                           a + other & (u3 ^ 0xffffffffffffffffULL));
    l = *(long *)(0 + 0x40);
    sk_x_004aa8a0();
    sk_x_0034c444();
    sk_x_00377824();
    sk_x_00349530();
    u4 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = (a & (u3 ^ 0xffffffffffffffffULL)) + l + u4;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x20))(a + self & (u4 ^ 0xffffffffffffffffULL),
                                                           a + other & (u4 ^ 0xffffffffffffffffULL));
    l = *(long *)(0 + 0x40);
    sk_x_004aacb0();
    p = sk_x_004aa47c(0, 0);
    sk_x_00377824(p.lo, p.hi, 0);
    sk_x_00349530();
    u3 = (unsigned long)*(unsigned char *)(0 + 0x50);
    l1 = (a & (u4 ^ 0xffffffffffffffffULL)) + l + u3;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x20))(l1 + self & (u3 ^ 0xffffffffffffffffULL),
                                                           l1 + other & (u3 ^ 0xffffffffffffffffULL));
    sk_x_004aa638(*(unsigned long *)(0 + 0x40));
    sk_x_0008e500(0, 0);
}

/* FUN_004a7b04 @ 0x004a7b04   (est. sk_regex_emit_utf8_28b)
 * Ghidra: void FUN_004a7b04(void)
 * UTF-8 span emitter via the 0x28-slot dispatch pattern with a third span.
 * Confidence: low
 */
static void sk_r34_emit_utf8_28b(unsigned long self, unsigned long other)
{
    unsigned long a, l1;
    long l;
    cl4_result_t p;
    unsigned long u3, u4;
    sk_x_0008e518();
    sk_x_004aa550();
    sk_x_0034ab20();
    (*(void (**)(void))(0 + 0x28))();
    sk_x_003537c4(*(unsigned long *)(0 + 0x40));
    u3 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = 0 + u3;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x28))(a + self & (u3 ^ 0xffffffffffffffffULL),
                                                           a + other & (u3 ^ 0xffffffffffffffffULL));
    l = *(long *)(0 + 0x40);
    sk_x_004aa8a0();
    sk_x_0034c444();
    sk_x_00377824();
    sk_x_00349530();
    u4 = (unsigned long)*(unsigned char *)(0 + 0x50);
    a = (a & (u3 ^ 0xffffffffffffffffULL)) + l + u4;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x28))(a + self & (u4 ^ 0xffffffffffffffffULL),
                                                           a + other & (u4 ^ 0xffffffffffffffffULL));
    l = *(long *)(0 + 0x40);
    sk_x_004aacb0();
    p = sk_x_004aa47c(0, 0);
    sk_x_00377824(p.lo, p.hi, 0);
    sk_x_00349530();
    u3 = (unsigned long)*(unsigned char *)(0 + 0x50);
    l1 = (a & (u4 ^ 0xffffffffffffffffULL)) + l + u3;
    (*(void (**)(unsigned long, unsigned long))(0 + 0x28))(l1 + self & (u3 ^ 0xffffffffffffffffULL),
                                                           l1 + other & (u3 ^ 0xffffffffffffffffULL));
    sk_x_004aa638(*(unsigned long *)(0 + 0x40));
    sk_x_0008e500(0, 0);
}

/* FUN_004a7c4c @ 0x004a7c4c   (est. sk_regex_emit_concat2)
 * Ghidra: void FUN_004a7c4c(undefined8 p1, undefined8 p2, long param_3)
 * Emit a concatenation node variant: decode the three spans at param_3
 * (0x10/0x18), compute lengths, walk the element array with 1/2/4-byte
 * reads to find the terminating byte, and emit via FUN_00353238 /
 * FUN_000839f8.
 * Confidence: low
 * Notes: DAT_0061628c; SoftwareBreakpoint(1,0x4a7f78).
 */
static void sk_r34_emit_concat2(unsigned long p1, unsigned long p2, unsigned long src, unsigned long self)
{
    cl4_result_t st, r;
    unsigned char *el;
    unsigned w;
    unsigned long a, b;
    long l6, l7, l8;
    unsigned len1, len2, len3, maxlen;
    unsigned long u1, u2, u17;
    long base1, base2;
    unsigned char bv;
    unsigned r15, r16, r3;
    st = sk_x_0035300c();
    w = (unsigned)(st.hi >> 32);
    el = (unsigned char *)st.lo;
    l6 = *(long *)(src + 0x10);
    b = *(unsigned long *)(src + 0x18);
    sk_x_004aa74c();
    l7 = sk_x_00377824(0, b, l6, 0x61628c).lo;
    len1 = *(unsigned *)(*(long *)(l7 - 8) + 0x54);
    r16 = *(unsigned *)(*(long *)(l6 - 8) + 0x54);
    maxlen = (r16 <= len1) ? len1 : r16;
    sk_x_004aa8a0();
    sk_x_00377824(0, b, l6, 0x61628c);
    sk_x_004ac948();
    len2 = *(unsigned *)(0 + 0x54);
    r3 = (len2 <= maxlen) ? maxlen : len2;
    sk_x_004ab310();
    b = sk_x_00377bec(b, l6, l7, 0x61628c);
    r = sk_x_004aa47c(b, b);
    r = sk_x_00377824(r.lo, r.hi, l7);
    sk_x_00352018(r.lo, r.hi, r.lo);
    sk_x_004ac948();
    u17 = (unsigned long)*(unsigned char *)(0 + 0x50);
    if (w != 0) {
        u1 = (*(long *)(0 + 0x40) + (*(long *)(0 + 0x40) & ~((unsigned long)*(unsigned char *)(0 + 0x50))) +
              0 + *(long *)(0 + 0x40)) + u17;
        u2 = (u1 & (u17 ^ 0xffffffffffffffffULL)) + *(long *)(0 + 0x40) + u17;
        l6 = *(long *)(0 + 0x40) + 7;
        if (w >= r3 && w - r3 != 0) {
            base2 = (l6 + (u2 & (u17 ^ 0xffffffffffffffffULL)) & 0xfffffffffffffff8ULL) + 0x12;
            r16 = (unsigned)base2;
            r15 = 2;
            r3 = r15;
            if (r16 < 4) r3 = ((w - r3) + 0xffff >> 0x10) + 1;
            if (0xffff < r3) r15 = 4;
            if (r3 < 0x100) r15 = 1;
            r16 = 0;
            if (1 < r3) r16 = r15;
            switch (r16) {
            case 1:
                bv = *(unsigned char *)((long)el + base2);
                if (bv != 0) {
                    r15 = bv - 1 << ((unsigned)base2 & 3) * 8;
                    r16 = (r16 < 4) ? (unsigned)(unsigned short)*el : *(unsigned *)el;
                    if (r16 >= 4) r15 = 0;
                    sk_x_00353238((r16 | r15) + 0, 0);
                    return;
                }
                break;
            case 2:
                if (*(unsigned short *)((long)el + base2) != 0) {
                    r15 = *(unsigned short *)((long)el + base2) - 1 << ((unsigned)base2 & 3) * 8;
                    r16 = (r16 < 4) ? (unsigned)(unsigned short)*el : *(unsigned *)el;
                    if (r16 >= 4) r15 = 0;
                    sk_x_00353238((r16 | r15) + 0, 0);
                    return;
                }
                break;
            case 4:
                if (*(unsigned *)((long)el + base2) != 0) {
                    r15 = *(unsigned *)((long)el + base2) - 1 << ((unsigned)base2 & 3) * 8;
                    r16 = (r16 < 4) ? (unsigned)(unsigned short)*el : *(unsigned *)el;
                    if (r16 >= 4) r15 = 0;
                    sk_x_00353238((r16 | r15) + 0, 0);
                    return;
                }
                break;
            case 3:
                SK_TRAP(0x4a7f78);
            }
        }
        if (r3 == *(unsigned *)(0 + 0x50)) {
            if (maxlen < len2) {
                r.hi = len2;
                r.lo = u1 + (unsigned long)el & ~u17;
                r.lo = r.lo >> 32 << 32;
                r.lo |= (unsigned long)len2;
            } else {
                r.hi = len1;
                r.lo = (unsigned long)el;
                if (len1 < r16) r = sk_x_004aca58();
            }
            sk_x_00353238(r.lo, r.hi);
            sk_x_000839f8();
            return;
        }
        u17 = u2 + (unsigned long)el & ~u17;
        r.hi = 0;
        r.lo = u17;
        if ((unsigned)0 == *(unsigned *)(0 + 0x50)) {
            sk_x_00353238(r.lo, r.hi);
            sk_x_000839f8();
            return;
        }
        r15 = *(unsigned char *)((l6 + u17 & 0xfffffffffffffff8ULL) + 0x10);
        if (1 < r15) {
            r15 = r15 + 0x7ffffffe & 0x7fffffff;
            sk_x_00353238(r15 + 1, 0);
            return;
        }
    }
    sk_x_00353238(0, 0);
}

/* FUN_004a83c0 @ 0x004a83c0   (est. sk_regex_node_release3)
 * Ghidra: void FUN_004a83c0(long param_1)
 * Release the three reference fields at param_1+0x30/+0x38/+0x40.
 * Confidence: high
 */
static void sk_r34_node_release3(unsigned long a)
{
    sk_x_0036b118(*(unsigned long *)(a + 0x30));
    sk_x_0036b118(*(unsigned long *)(a + 0x38));
    sk_x_0036b118(*(unsigned long *)(a + 0x40));
}

/* FUN_004a83f8 @ 0x004a83f8   (est. sk_regex_node_copy_s83)
 * Ghidra: undefined8 * FUN_004a83f8(undefined8 *param_1, undefined8 *param_2)
 * Copy-assign a regex node: copy the two header words plus the 0x40-byte
 * record from the sibling (FUN_004ab9a4), then retain the copied reference
 * fields.
 * Confidence: medium
 * Notes: record copy via FUN_004ab9a4 pair.
 */
static unsigned long *sk_r34_node_copy_s83(unsigned long *dst, unsigned long *src)
{
    cl4_result_t p;
    unsigned long *s, *d;
    unsigned long a, b, c;
    dst[1] = src[1];
    *dst = *src;
    p = sk_x_004ab9a4();
    s = (unsigned long *)p.hi;
    d = (unsigned long *)p.lo;
    d[0x18] = s[0x18]; d[0x20] = s[0x20];
    *(unsigned short *)(d + 0x28) = *(unsigned short *)(s + 0x28);
    d[0x38] = s[0x38]; d[0x30] = s[0x30];
    dst[8] = s[0x40];
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    sk_x_0036b270(0);
    return dst;
}

/* FUN_004a8468 @ 0x004a8468   (est. sk_regex_node_copy_s84)
 * Ghidra: void FUN_004a8468(void)
 * Copy-assign a regex node from the sibling context (FUN_0034b264 pair)
 * plus x19/x20 into self.
 * Confidence: low
 * Notes: self/x20, src/x19 register globals.
 */
static void sk_r34_node_copy_s84(unsigned long self, unsigned long src)
{
    cl4_result_t p;
    unsigned long *s, *d;
    unsigned long a;
    p = sk_x_0034b264();
    s = (unsigned long *)p.hi;
    d = (unsigned long *)p.lo;
    d[8] = s[8];
    *(unsigned char *)(d + 0x10) = *(unsigned char *)(s + 0x10);
    d[0x20] = s[0x20]; d[0x18] = s[0x18];
    *(unsigned char *)(d + 0x28) = *(unsigned char *)(s + 0x28);
    *(unsigned char *)(d + 0x29) = *(unsigned char *)(s + 0x29);
    a = *(unsigned long *)(self + 0x30);
    *(unsigned long *)(self + 0x30) = *(unsigned long *)(s + 0x30);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x38);
    *(unsigned long *)(self + 0x38) = *(unsigned long *)(src + 0x38);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x40);
    *(unsigned long *)(self + 0x40) = *(unsigned long *)(src + 0x40);
    sk_x_0036b270();
    sk_x_0036b118(a);
}

/* FUN_004a8504 @ 0x004a8504   (est. sk_regex_node_copy_s85)
 * Ghidra: void FUN_004a8504(void)
 * Copy-assign a regex node from x19 into x20 (sibling of 0x8468).
 * Confidence: low
 */
static void sk_r34_node_copy_s85(unsigned long self, unsigned long src)
{
    cl4_result_t p;
    unsigned long *s, *d;
    unsigned long a;
    p = sk_x_003504d0();
    d = (unsigned long *)p.lo;
    s = (unsigned long *)p.hi;
    *d = *s;
    d[1] = s[1];
    p = sk_x_004ab9a4();
    s = (unsigned long *)p.hi;
    d = (unsigned long *)p.lo;
    d[0x20] = s[0x20]; d[0x18] = s[0x18];
    *(unsigned char *)(d + 0x28) = *(unsigned char *)(s + 0x28);
    *(unsigned char *)(d + 0x29) = *(unsigned char *)(s + 0x29);
    sk_x_0036b118(*(unsigned long *)(d + 0x30));
    a = *(unsigned long *)(self + 0x38);
    *(unsigned long *)(self + 0x38) = *(unsigned long *)(src + 0x38);
    *(unsigned long *)(self + 0x30) = *(unsigned long *)(src + 0x30);
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x40);
    *(unsigned long *)(self + 0x40) = *(unsigned long *)(src + 0x40);
    sk_x_0036b118(a);
}

/* FUN_004a8610 @ 0x004a8610   (est. sk_regex_pair_copy)
 * Ghidra: undefined8 * FUN_004a8610(undefined8 *param_1, undefined8 *param_2)
 * Copy a 2-word pair (with retain) and return param_1.
 * Confidence: high
 */
static unsigned long *sk_r34_pair_copy(unsigned long *dst, unsigned long *src)
{
    dst[1] = src[1];
    *dst = *src;
    sk_x_0036b270();
    return dst;
}

/* FUN_004a89fc @ 0x004a89fc   (est. sk_regex_triple_swap)
 * Ghidra: long FUN_004a89fc(long param_1)
 * Copy a 3-field (2 word + byte) record into param_1: fetch from the
 * sibling (FUN_004ab600) and the char-pair helper FUN_0006b6f4, emit the
 * element via sk_r34_release_elem_lt4, then store the three fields.
 * Confidence: medium
 */
static long sk_r34_triple_swap(long dst)
{
    cl4_result_t p;
    unsigned long a, b;
    unsigned char t;
    sk_x_004ab600();
    a = *(unsigned long *)(0 + 0x10);
    b = *(unsigned long *)(0 + 0x18);
    t = *(unsigned char *)(0 + 0x20);
    p = sk_x_0006b6f4();
    sk_r34_release_elem_lt4(p.lo, p.hi, t);
    *(unsigned long *)(dst + 0x10) = a;
    *(unsigned long *)(dst + 0x18) = b;
    *(unsigned char *)(dst + 0x20) = t;
    return dst;
}

/* FUN_004a8a48 @ 0x004a8a48   (est. sk_regex_triple_swap2)
 * Ghidra: void FUN_004a8a48(void)
 * Swap a 3-field record into self(x19) from the sibling (FUN_0034f2f4 pair)
 * and the char-pair helper, emitting the old element and copying the new.
 * Confidence: low
 */
static void sk_r34_triple_swap2(unsigned long self)
{
    cl4_result_t p;
    unsigned long *s;
    unsigned long a, b, oa, ob;
    unsigned char t, ot;
    p = sk_x_0034f2f4();
    s = (unsigned long *)p.hi;
    *(unsigned long *)(p.lo + 8) = *(unsigned long *)(s + 8);
    a = *(unsigned long *)(s + 0x10);
    b = *(unsigned long *)(s + 0x18);
    t = *(unsigned char *)(s + 0x20);
    p = sk_x_0006b6f4();
    sk_r34_release_elem_lt4(p.lo, p.hi, t);
    oa = *(unsigned long *)(self + 0x10);
    ob = *(unsigned long *)(self + 0x18);
    *(unsigned long *)(self + 0x10) = a;
    *(unsigned long *)(self + 0x18) = b;
    ot = *(unsigned char *)(self + 0x20);
    *(unsigned char *)(self + 0x20) = t;
    sk_x_0049cb88(oa, ob, ot);
}

/* FUN_004a8aa4 @ 0x004a8aa4   (est. sk_regex_quad_swap)
 * Ghidra: undefined8 * FUN_004a8aa4(undefined8 *param_1, undefined8 *param_2)
 * Swap the 4-word + byte element from param_2 into param_1, releasing the
 * old element via FUN_0049cb88.
 * Confidence: medium
 */
static unsigned long *sk_r34_quad_swap(unsigned long *dst, unsigned long *src)
{
    unsigned char t;
    unsigned long a, b, c, d;
    t = *(unsigned char *)(src + 4);
    a = dst[2];
    b = dst[3];
    c = *src;
    d = src[3];
    dst[1] = src[1];
    *dst = c;
    dst[3] = d;
    dst[2] = src[2];
    b = *(unsigned char *)(dst + 4);
    *(unsigned char *)(dst + 4) = t;
    sk_x_0049cb88(a, b, 0);
    return dst;
}

/* FUN_004a8b9c @ 0x004a8b9c   (est. sk_regex_triple_apply)
 * Ghidra: undefined8 * FUN_004a8b9c(undefined8 *param_1, undefined8 *param_2, undefined8 param_3, code *param_4)
 * Apply a callback to a 2-word + byte element: call param_4 with the
 * char-pair from FUN_0006b6f4 plus the element byte, then copy the element
 * into param_1 and return it.
 * Confidence: medium
 */
static unsigned long *sk_r34_triple_apply(unsigned long *dst, unsigned long *src, unsigned long p3,
                                          void (*cb)(unsigned long, unsigned long, unsigned char))
{
    unsigned long a, b;
    unsigned char t;
    cl4_result_t p;
    a = *src;
    b = src[1];
    t = *(unsigned char *)(src + 2);
    p = sk_x_0006b6f4();
    cb(p.lo, p.hi, t);
    *dst = a;
    dst[1] = b;
    *(unsigned char *)(dst + 2) = t;
    return dst;
}

/* FUN_004a8c14 @ 0x004a8c14   (est. sk_regex_triple_swap2cb)
 * Ghidra: undefined8 * FUN_004a8c14(undefined8 *param_1, undefined8 *param_2, undefined8 p3, code *param_4, code *param_5)
 * Swap a 2-word + byte element from param_2 into param_1 with two callbacks:
 * emit the new element via param_4 (with FUN_000b4390 char pair) and release
 * the old element via param_5.
 * Confidence: medium
 */
static unsigned long *sk_r34_triple_swap2cb(unsigned long *dst, unsigned long *src, unsigned long p3,
                                            void (*emit)(unsigned long, unsigned long, unsigned char),
                                            void (*rel)(unsigned long, unsigned long, unsigned char))
{
    unsigned long a, b, oa, ob;
    unsigned char t, ot;
    cl4_result_t p;
    a = *src;
    b = src[1];
    t = *(unsigned char *)(src + 2);
    p = sk_x_000b4390();
    emit(p.lo, p.hi, t);
    oa = *dst;
    ob = dst[1];
    *dst = a;
    dst[1] = b;
    ot = *(unsigned char *)(dst + 2);
    *(unsigned char *)(dst + 2) = t;
    rel(oa, ob, ot);
    return dst;
}

/* FUN_004a8c94 @ 0x004a8c94   (est. sk_regex_triple_swap1cb)
 * Ghidra: undefined8 * FUN_004a8c94(undefined8 *param_1, undefined8 *param_2, undefined8 p3, code *param_4)
 * Swap a 2-word + byte element from param_2 into param_1, releasing the old
 * element via param_4.
 * Confidence: medium
 */
static unsigned long *sk_r34_triple_swap1cb(unsigned long *dst, unsigned long *src, unsigned long p3,
                                            void (*rel)(unsigned long, unsigned long, unsigned char))
{
    unsigned char t, ot;
    unsigned long a, b, c;
    t = *(unsigned char *)(src + 2);
    a = *dst;
    b = dst[1];
    c = *src;
    dst[1] = src[1];
    *dst = c;
    ot = *(unsigned char *)(dst + 2);
    *(unsigned char *)(dst + 2) = t;
    rel(a, b, ot);
    return dst;
}

/* FUN_004a8d9c @ 0x004a8d9c   (est. sk_regex_quad_copy)
 * Ghidra: undefined8 * FUN_004a8d9c(undefined8 *param_1, undefined8 *param_2)
 * Copy a 4-word element (3 words + byte) with retain, return param_1.
 * Confidence: high
 */
static unsigned long *sk_r34_quad_copy(unsigned long *dst, unsigned long *src)
{
    dst[1] = src[1];
    *dst = *src;
    dst[2] = src[2];
    *(unsigned char *)(dst + 3) = *(unsigned char *)(src + 3);
    sk_x_0036b270();
    return dst;
}

/* FUN_004a8ddc @ 0x004a8ddc   (est. sk_regex_elem_move)
 * Ghidra: void FUN_004a8ddc(void)
 * Move the 2-word + byte element from self(x19) into the target(x20).
 * Confidence: medium
 */
static void sk_r34_elem_move(unsigned long self, unsigned long dst)
{
    unsigned long a;
    sk_x_0034b044();
    sk_x_0036b270();
    sk_x_003a25d4();
    *(unsigned long *)(dst + 8) = *(unsigned long *)(self + 8);
    a = *(unsigned long *)(self + 0x10);
    *(unsigned char *)(dst + 0x18) = *(unsigned char *)(self + 0x18);
    *(unsigned long *)(dst + 0x10) = a;
}

/* FUN_004a8e2c @ 0x004a8e2c   (est. sk_regex_elem_emit_copy)
 * Ghidra: void FUN_004a8e2c(void)
 * Emit a copy of the element from the sibling context (FUN_003504d0 pair)
 * into the target(x20), copying 3 words + byte from self(x19).
 * Confidence: low
 */
static void sk_r34_elem_emit_copy(unsigned long self, unsigned long *dst)
{
    cl4_result_t p;
    unsigned long a;
    p = sk_x_003504d0();
    a = *(unsigned long *)p.lo;
    *dst = *(unsigned long *)p.hi;
    sk_x_003a25d4(a);
    a = *(unsigned long *)(self + 0x10);
    dst[1] = *(unsigned long *)(self + 8);
    dst[2] = a;
    *(unsigned char *)(dst + 3) = *(unsigned char *)(self + 0x18);
}

/* FUN_004a8ef8 @ 0x004a8ef8   (est. sk_regex_node_maybe_deinit)
 * Ghidra: void FUN_004a8ef8(long param_1)
 * If the node at param_1+0x30 is nonzero, run the deinit helper FUN_000026e8
 * on param_1+0x18.
 * Confidence: medium
 */
static void sk_r34_node_maybe_deinit(unsigned long a)
{
    if (*(long *)(a + 0x30) != 0) {
        sk_x_000026e8(a + 0x18);
    }
}

/* FUN_004a8f0c @ 0x004a8f0c   (est. sk_regex_node_rebuild)
 * Ghidra: void FUN_004a8f0c(void)
 * Rebuild a regex node into self(x19) from the sibling context: if the
 * sibling +0x30 is empty, copy the sibling's 16-byte field into self+0x28;
 * otherwise adopt the sibling +0x30 pointer and dispatch the +0x18 pair
 * through an indirect handler.
 * Confidence: low
 * Notes: self = unaff_x19, src = unaff_x20.
 */
static void sk_r34_node_rebuild(unsigned long self, unsigned long src)
{
    cl4_result_t p;
    if (*(long *)(0 + 0x30) == 0) {
        p = sk_x_004ab10c();
        *(cl4_result_t *)(self + 0x28) = p;
    } else {
        *(long *)(self + 0x30) = *(long *)(0 + 0x30);
        sk_x_0034b07c();
        (*(void (**)(unsigned long, unsigned long))(*(unsigned long *)0))(self + 0x18, src + 0x18);
    }
    sk_x_004ab8fc();
}

/* FUN_004a8f70 @ 0x004a8f70   (est. sk_regex_node_rebuild2)
 * Ghidra: void FUN_004a8f70(void)
 * Rebuild a regex node into self(x19): copy the sibling's first two words
 * (via FUN_004ab9a4), then depending on the +0x30 pointer adopt either the
 * deep-copy (FUN_0032b65c) or deinit (FUN_000026e8) path.
 * Confidence: low
 */
static void sk_r34_node_rebuild2(unsigned long self, unsigned long src)
{
    unsigned long *p;
    long l;
    p = (unsigned long *)sk_x_004ab9a4(0).lo;
    p[1] = 0;
    *p = 0;
    l = *(long *)(0 + 0x30);
    if (p[6] == 0) {
        if (l != 0) {
            *(long *)(self + 0x30) = l;
            sk_x_0034b07c();
            (*(void (**)(unsigned long, unsigned long))(*(unsigned long *)0))(self + 0x18, src + 0x18);
            goto out;
        }
    } else {
        if (l != 0) {
            sk_x_0032b65c(self + 0x18, src + 0x18);
            goto out;
        }
        sk_x_000026e8(self + 0x18);
    }
    sk_x_004ab954();
out:
    sk_x_004ac998();
}

/* FUN_004a8ff8 @ 0x004a8ff8   (est. sk_regex_emit_nodepub)
 * Ghidra: void FUN_004a8ff8(void)
 * Publish/emit a regex node into self(x19): if the sibling +0x30 is
 * nonzero, deinit self+0x18 (FUN_000026e8); then copy the sibling's 16-byte
 * field into self+0x28 and run the stream helper.
 * Confidence: low
 * Notes: self = unaff_x19.
 */
static void sk_r34_emit_nodepub(unsigned long self, unsigned long src)
{
    long l;
    cl4_result_t p;
    sk_x_00350c5c();
    l = sk_x_004ab150();
    if (*(long *)(l + 0x30) != 0) {
        sk_x_000026e8(self + 0x18);
    }
    p = sk_x_004ab10c();
    *(cl4_result_t *)(self + 0x28) = p;
    sk_x_004ab8fc();
}

/* FUN_004a90e4 @ 0x004a90e4   (est. sk_regex_node_deinit_s90)
 * Ghidra: void FUN_004a90e4(long param_1)
 * Deallocate a regex node at param_1, releasing every reference field in
 * the fixed layout.
 * Confidence: high
 */
static void sk_r34_node_deinit_s90(unsigned long a)
{
    sk_x_003a25d4(*(unsigned long *)(a + 8));
    sk_x_0036b118(*(unsigned long *)(a + 0x28));
    sk_x_003a25d4(*(unsigned long *)(a + 0x30));
    sk_x_0036b118(*(unsigned long *)(a + 0x68));
    sk_x_0036b118(*(unsigned long *)(a + 0x70));
    sk_x_0036b118(*(unsigned long *)(a + 0x78));
    sk_x_0036b118(*(unsigned long *)(a + 0x80));
    sk_x_0036b118(*(unsigned long *)(a + 0x88));
    sk_x_0036b118(*(unsigned long *)(a + 0x90));
    sk_x_0036b118(*(unsigned long *)(a + 0xa0));
    sk_x_0036b118(*(unsigned long *)(a + 0xa8));
    sk_x_0036b118(*(unsigned long *)(a + 0xb0));
    sk_x_0036b118(*(unsigned long *)(a + 0xb8));
    sk_x_0036b118(*(unsigned long *)(a + 0xc0));
    sk_x_0036b118(*(unsigned long *)(a + 0xd0));
}

/* FUN_004a917c @ 0x004a917c   (est. sk_regex_node_copy_s91)
 * Ghidra: undefined8 * FUN_004a917c(undefined8 *param_1, undefined8 *param_2)
 * Deep-copy a 0x1b-word regex node from param_2 into param_1, then retain
 * retain all reference fields in order.
 * Confidence: high  (verified 1:1 vs decompile; retain args = source field values)
 * Notes: 16-byte-word record copy + retain-all.
 */
static unsigned long *sk_r34_node_copy_s91(unsigned long *dst, unsigned long *src)
{
    unsigned long a;
    dst[1] = src[1];
    *dst = *src;
    dst[3] = src[3];
    dst[2] = src[2];
    *(unsigned char *)(dst + 4) = *(unsigned char *)(src + 4);
    dst[6] = src[6];
    dst[5] = src[5];
    dst[7] = src[7];
    *(unsigned char *)(dst + 8) = *(unsigned char *)(src + 8);
    dst[10] = src[10];
    dst[9] = src[9];
    dst[0xc] = src[0xc];
    dst[0xb] = src[0xb];
    dst[0xe] = src[0xe];
    dst[0xd] = src[0xd];
    dst[0x10] = src[0x10];
    dst[0xf] = src[0xf];
    dst[0x12] = src[0x12];
    dst[0x11] = src[0x11];
    *(unsigned char *)(dst + 0x13) = *(unsigned char *)(src + 0x13);
    dst[0x15] = src[0x15];
    dst[0x14] = src[0x14];
    dst[0x17] = src[0x17];
    dst[0x16] = src[0x16];
    dst[0x18] = src[0x18];
    *(unsigned char *)(dst + 0x19) = *(unsigned char *)(src + 0x19);
    dst[0x1a] = src[0x1a];
    /* retain-all in the decompile's order (args = source field values) */
    sk_x_0036b270();
    sk_x_004abae4();
    sk_x_0036b270();
    sk_x_0036b270(src[6]);       /* uVar6 */
    sk_x_004aba1c();
    sk_x_0036b270();
    sk_x_0036b270(src[0xe]);     /* uVar3 */
    sk_x_004ac3d8();
    sk_x_0036b270(src[0x10]);    /* uVar4 */
    sk_x_004ac550();
    sk_x_0036b270(src[0x12]);    /* uVar5 */
    sk_x_004abb80();
    sk_x_0036b270();
    sk_x_0036b270(src[0x15]);    /* uVar2 */
    sk_x_004ac4ac();
    sk_x_0036b270(src[0x17]);    /* uVar7 */
    sk_x_0036b270(src[0x18]);    /* uVar8 */
    sk_x_0036b270(src[0x1a]);    /* uVar1 */
    return dst;
}

/* FUN_004a92d8 @ 0x004a92d8   (est. sk_regex_node_copy_s92)
 * Ghidra: void FUN_004a92d8(undefined8 param_1, long param_2)
 * Copy-assign a regex node into self(x19) from the sibling context
 * (FUN_0034f2f4) plus param_2.
 * Confidence: low
 * Notes: self = unaff_x19.
 */
static void sk_r34_node_copy_s92(unsigned long p1, unsigned long src, unsigned long self)
{
    unsigned long a;
    sk_x_0034f2f4();
    a = *(unsigned long *)(self + 8);
    *(unsigned long *)(self + 8) = *(unsigned long *)(0 + 8);
    sk_x_0036b270();
    sk_x_003a25d4(a);
    *(unsigned long *)(self + 0x10) = *(unsigned long *)(src + 0x10);
    *(unsigned long *)(self + 0x18) = *(unsigned long *)(src + 0x18);
    *(unsigned char *)(self + 0x20) = *(unsigned char *)(src + 0x20);
    sk_x_004aaed8();
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x30);
    *(unsigned long *)(self + 0x30) = *(unsigned long *)(src + 0x30);
    sk_x_0036b270();
    sk_x_003a25d4(a);
    sk_x_004ac998();
    *(unsigned long *)(self + 0x48) = *(unsigned long *)(src + 0x48);
    *(unsigned long *)(self + 0x50) = *(unsigned long *)(src + 0x50);
    *(unsigned long *)(self + 0x58) = *(unsigned long *)(src + 0x58);
    *(unsigned long *)(self + 0x60) = *(unsigned long *)(src + 0x60);
    a = *(unsigned long *)(self + 0x68);
    *(unsigned long *)(self + 0x68) = *(unsigned long *)(src + 0x68);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x70);
    *(unsigned long *)(self + 0x70) = *(unsigned long *)(src + 0x70);
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004abbe0();
    sk_x_0036b118(a);
    sk_x_004abbc4();
    sk_x_0036b118(a);
    sk_x_004ac49c();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x90);
    *(unsigned long *)(self + 0x90) = *(unsigned long *)(src + 0x90);
    sk_x_0036b270();
    sk_x_0036b118(a);
    *(unsigned char *)(self + 0x98) = *(unsigned char *)(src + 0x98);
    a = *(unsigned long *)(self + 0xa0);
    *(unsigned long *)(self + 0xa0) = *(unsigned long *)(src + 0xa0);
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004ac43c();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0xb0);
    *(unsigned long *)(self + 0xb0) = *(unsigned long *)(src + 0xb0);
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004abf98();
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0xc0);
    *(unsigned long *)(self + 0xc0) = *(unsigned long *)(src + 0xc0);
    sk_x_0036b270();
    sk_x_0036b118(a);
    *(unsigned char *)(self + 200) = *(unsigned char *)(src + 200);
    a = *(unsigned long *)(self + 0xd0);
    *(unsigned long *)(self + 0xd0) = *(unsigned long *)(src + 0xd0);
    sk_x_0036b270();
    sk_x_0036b118(a);
}

/* FUN_004a9484 @ 0x004a9484   (est. sk_regex_node_copy_s94)
 * Ghidra: void FUN_004a9484(void)
 * Copy-assign a regex node into self(x19, unsigned long*) from the sibling
 * context (FUN_00350c5c) and x20.
 * Confidence: low
 * Notes: self = unaff_x19 (word*), src = unaff_x20.
 */
static void sk_r34_node_copy_s94(unsigned long *self, unsigned long src)
{
    cl4_result_t p;
    unsigned long a, b;
    p = sk_x_00350c5c();
    b = *(unsigned long *)(p.hi + 8);
    a = *(unsigned long *)(p.lo + 8);
    *self = *(unsigned long *)p.hi;
    self[1] = b;
    sk_x_003a25d4(a);
    b = *(unsigned long *)(src + 0x10);
    self[3] = *(unsigned long *)(src + 0x18);
    self[2] = b;
    *(unsigned char *)(self + 4) = *(unsigned char *)(src + 0x20);
    sk_x_0036b118(self[5]);
    b = self[6];
    a = *(unsigned long *)(src + 0x28);
    self[6] = *(unsigned long *)(src + 0x30);
    self[5] = a;
    sk_x_003a25d4(b);
    sk_x_004ab8fc();
    b = *(unsigned long *)(src + 0x48);
    self[10] = *(unsigned long *)(src + 0x50);
    self[9] = b;
    b = *(unsigned long *)(src + 0x58);
    self[0xc] = *(unsigned long *)(src + 0x60);
    self[0xb] = b;
    sk_x_0036b118(self[0xd]);
    b = self[0xe];
    a = *(unsigned long *)(src + 0x68);
    self[0xe] = *(unsigned long *)(src + 0x70);
    self[0xd] = a;
    sk_x_0036b118(b);
    sk_x_0036b118(self[0xf]);
    b = self[0x10];
    a = *(unsigned long *)(src + 0x78);
    self[0x10] = *(unsigned long *)(src + 0x80);
    self[0xf] = a;
    sk_x_0036b118(b);
    sk_x_0036b118(self[0x11]);
    b = self[0x12];
    a = *(unsigned long *)(src + 0x88);
    self[0x12] = *(unsigned long *)(src + 0x90);
    self[0x11] = a;
    sk_x_0036b118(b);
    *(unsigned char *)(self + 0x13) = *(unsigned char *)(src + 0x98);
    sk_x_0036b118(self[0x14]);
    sk_x_004ac1d4(self[0x15]);
    sk_x_0036b118();
    sk_x_0036b118(self[0x16]);
    b = self[0x17];
    a = *(unsigned long *)(src + 0xb0);
    self[0x17] = *(unsigned long *)(src + 0xb8);
    self[0x16] = a;
    sk_x_0036b118(b);
    b = self[0x18];
    self[0x18] = *(unsigned long *)(src + 0xc0);
    sk_x_0036b118(b);
    *(unsigned char *)(self + 0x19) = *(unsigned char *)(src + 200);
    b = self[0x1a];
    self[0x1a] = *(unsigned long *)(src + 0xd0);
    sk_x_0036b118(b);
}

/* FUN_004a963c @ 0x004a963c   (est. sk_regex_node_deinit_s96)
 * Ghidra: void FUN_004a963c(void)
 * Deallocate a regex node at self(x19): open the arena and release the
 * reference fields.
 * Confidence: high
 * Notes: self = unaff_x19.
 */
static void sk_r34_node_deinit_s96(unsigned long self)
{
    sk_x_00352b20();
    sk_x_0036b118();
    sk_x_0036b118(*(unsigned long *)(self + 8));
    sk_x_0036b118(*(unsigned long *)(self + 0x10));
    sk_x_0036b118(*(unsigned long *)(self + 0x18));
    sk_x_0036b118(*(unsigned long *)(self + 0x20));
    sk_x_0036b118(*(unsigned long *)(self + 0x28));
    sk_x_0036b118(*(unsigned long *)(self + 0x38));
    sk_x_0036b118(*(unsigned long *)(self + 0x40));
    sk_x_0036b118(*(unsigned long *)(self + 0x48));
}

/* FUN_004a96a0 @ 0x004a96a0   (est. sk_regex_node_make_s96)
 * Ghidra: void FUN_004a96a0(undefined1 param_1 [16], undefined1 param_2 [16])
 * Build a regex node: allocate (FUN_00041138 + FUN_004aca80), fill the
 * record from param_2 and the sibling context, retain the reference fields,
 * and close.
 * Confidence: low
 * Notes: 16-byte in/out params.
 */
static void sk_r34_node_make_s96(unsigned long p1lo, unsigned long p1hi, unsigned long p2lo, unsigned long p2hi,
                                 unsigned long self)
{
    unsigned long *node;
    unsigned long a, b;
    sk_x_00041138();
    node = (unsigned long *)sk_x_004aca80();
    node[1] = 0;
    *node = 0;
    node[3] = p2hi;
    node[2] = p2lo;
    a = *(unsigned long *)(0 + 0x28);
    b = *(unsigned long *)(0 + 0x20);
    node[5] = a;
    node[4] = b;
    *(unsigned char *)(node + 6) = *(unsigned char *)(0 + 0x30);
    b = *(unsigned long *)(0 + 0x38);
    node[8] = *(unsigned long *)(0 + 0x40);
    node[7] = b;
    *(unsigned long *)(self + 0x48) = *(unsigned long *)(0 + 0x48);
    sk_x_0036b270(0);
    sk_x_0036b270();
    sk_x_004aba1c();
    sk_x_0036b270();
    sk_x_0036b270();
    sk_x_004abae4();
    sk_x_0036b270();
    sk_x_0036b270(a);
    sk_x_004ac3d8();
    sk_x_0036b270(b);
    sk_x_0036b270(0);
    sk_x_0035847c();
}

/* FUN_004a974c @ 0x004a974c   (est. sk_regex_node_copy_s97)
 * Ghidra: void FUN_004a974c(void)
 * Copy-assign a regex node from x20 into self x19.
 * Confidence: medium
 * Notes: self = unaff_x19, src = unaff_x20.
 */
static void sk_r34_node_copy_s97(unsigned long self, unsigned long src)
{
    unsigned long a;
    sk_x_004aae14();
    sk_x_0036b118();
    a = *(unsigned long *)(self + 8);
    *(unsigned long *)(self + 8) = *(unsigned long *)(src + 8);
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x10);
    *(unsigned long *)(self + 0x10) = *(unsigned long *)(src + 0x10);
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004ab0fc();
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004aafb8();
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004aaed8();
    sk_x_0036b270();
    sk_x_0036b118(a);
    sk_x_004ab230();
    sk_x_0036b118(a);
    sk_x_004aae88();
    sk_x_0036b270();
    sk_x_0036b118(a);
    a = *(unsigned long *)(self + 0x48);
    *(unsigned long *)(self + 0x48) = *(unsigned long *)(src + 0x48);
    sk_x_0036b270();
    sk_x_0036b118(a);
}

/* FUN_004a9814 @ 0x004a9814   (est. sk_regex_node_copy_s98)
 * Ghidra: void FUN_004a9814(void)
 * Copy-assign a regex node from x19 into x20 (inverse direction of 0x974c).
 * Confidence: low
 */
static void sk_r34_node_copy_s98(unsigned long self, unsigned long src)
{
    unsigned long *p;
    unsigned long a, b;
    p = (unsigned long *)sk_x_003504d0().lo;
    sk_x_0036b118(*p);
    sk_x_004ac45c();
    sk_x_0036b118(*(unsigned long *)(src + 0x10));
    a = *(unsigned long *)(src + 0x18);
    b = *(unsigned long *)(self + 0x10);
    *(unsigned long *)(src + 0x18) = *(unsigned long *)(self + 0x18);
    *(unsigned long *)(src + 0x10) = b;
    sk_x_0036b118(a);
    sk_x_0036b118(*(unsigned long *)(src + 0x20));
    sk_x_004ac87c(*(unsigned long *)(src + 0x28));
    sk_x_0036b118();
    *(unsigned char *)(src + 0x30) = *(unsigned char *)(self + 0x30);
    sk_x_0036b118(*(unsigned long *)(src + 0x38));
    a = *(unsigned long *)(src + 0x40);
    b = *(unsigned long *)(self + 0x38);
    *(unsigned long *)(src + 0x40) = *(unsigned long *)(self + 0x40);
    *(unsigned long *)(src + 0x38) = b;
    sk_x_0036b118(a);
    a = *(unsigned long *)(src + 0x48);
    *(unsigned long *)(src + 0x48) = *(unsigned long *)(self + 0x48);
    sk_x_0036b118(a);
}

/* FUN_004a9974 @ 0x004a9974   (est. sk_regex_emit_error)
 * Ghidra: void FUN_004a9974(long param_1)
 * Emit an error/report for the node: guard the size (FUN_00377dcc(0x13f,
 * param_1+0x10)), and if small enough format via FUN_00351244 +
 * FUN_003728b8(1) + FUN_00019858.
 * Confidence: low
 * Notes: kind tag 0x13f.
 */
static void sk_r34_emit_error(unsigned long a)
{
    cl4_result_t p;
    if (sk_x_00377dcc(0x13f, *(unsigned long *)(a + 0x10)) < 0x40) {
        p = sk_x_00351244();
        sk_x_003728b8(p.lo, p.hi, 1);
        sk_x_00019858();
    }
}

/* FUN_004a99e8 @ 0x004a99e8   (est. sk_regex_emit_dispatch)
 * Ghidra: void FUN_004a99e8(void)
 * Emit dispatch: run the two stream helpers, then based on the carry/zero
 * flags and length guard either call the 0x10-slot handler or the fallback
 * FUN_004ab5ec.
 * Confidence: low
 * Notes: relies on in_ZR/in_CY flags from helpers.
 */
static void sk_r34_emit_dispatch(void)
{
    sk_x_004ac378();
    sk_x_0034b7e4();
    sk_x_0035944c(0);
    if (0 && 0 < 0x19 && 0 == 0) {
        (*(void (**)(void))(0 + 0x10))();
    } else {
        sk_x_004ab5ec(*(unsigned long *)0);
    }
}

/* FUN_004a9a64 @ 0x004a9a64   (est. sk_regex_emit_slot10)
 * Ghidra: void FUN_004a9a64(void)
 * Dispatch through the 0x10 slot of the pair stream.
 * Confidence: low
 */
static void sk_r34_emit_slot10(void)
{
    sk_x_004ac378();
    sk_x_0034b07c();
    (*(void (**)(void))(0 + 0x10))();
}

/* FUN_004a9aa0 @ 0x004a9aa0   (est. sk_regex_emit_slot18)
 * Ghidra: void FUN_004a9aa0(void)
 * Dispatch through the 0x18 slot of the pair stream.
 * Confidence: low
 */
static void sk_r34_emit_slot18(void)
{
    sk_x_004ac378();
    sk_x_0034b07c();
    (*(void (**)(void))(0 + 0x18))();
}

/* FUN_004a9adc @ 0x004a9adc   (est. sk_regex_emit_slot20)
 * Ghidra: void FUN_004a9adc(void)
 * Dispatch through the 0x20 slot of the pair stream.
 * Confidence: low
 */
static void sk_r34_emit_slot20(void)
{
    sk_x_004ac378();
    sk_x_0034b07c();
    (*(void (**)(void))(0 + 0x20))();
}

/* FUN_004a9b18 @ 0x004a9b18   (est. sk_regex_emit_slot28)
 * Ghidra: void FUN_004a9b18(void)
 * Dispatch through the 0x28 slot of the pair stream.
 * Confidence: low
 */
static void sk_r34_emit_slot28(void)
{
    sk_x_004ac378();
    sk_x_0034b07c();
    (*(void (**)(void))(0 + 0x28))();
}

/* FUN_004a9c00 @ 0x004a9c00   (est. sk_regex_utf8_decode_next)
 * Ghidra: undefined8 FUN_004a9c00(void)
 * Decode the next UTF-8 codepoint from the string in the stream context
 * (FUN_004abf7c): read the 1/2/4-byte element at the position (width from
 * the size word), decode it via FUN_0006b438, and return the character;
 * returns 0 when the span is empty.
 * Confidence: medium
 * Notes: LZCOUNT-based element width.
 */
static unsigned long sk_r34_utf8_decode_next(void)
{
    cl4_result_t st;
    unsigned char *p;
    unsigned sz, w;
    unsigned long v, x;
    st = sk_x_004abf7c();
    p = (unsigned char *)st.lo;
    sz = (unsigned)(st.hi >> 32);
    if (sz < 0x100) {
        if (sz < 2) goto empty;
        w = *(unsigned char *)((long)p + 0);
    } else if (sz >> 0x10 == 0) {
        w = *(unsigned short *)((long)p + 0);
    } else {
        w = *(unsigned *)((long)p + 0);
    }
    if (w != 0) {
        x = (unsigned long)0;
        if ((unsigned)0 < 4) {
            x = (unsigned long)(w - 1) << (0 & 0x1f);
        }
        v = 0;
        if ((unsigned)0 != 0) {
            switch ((unsigned)0 < 4 ? (unsigned)0 : 4) {
            default: v = (unsigned char)*p; break;
            case 2: v = (unsigned short)*p; break;
            case 3: v = ((unsigned)p[2]<<16)|((unsigned)p[1]<<8)|p[0]; break;
            case 4: v = *(unsigned *)p; break;
            }
        }
        return sk_x_0006b438((unsigned)(v | x));
    }
empty:
    if ((unsigned)(st.hi >> 32) == 0) {
        return 0;
    }
    return sk_x_000839f8();
}

/* FUN_004a9f98 @ 0x004a9f98   (est. sk_regex_node_deinit_s9f)
 * Ghidra: void FUN_004a9f98(void)
 * Deallocate a small regex node at self(x19).
 * Confidence: high
 * Notes: self = unaff_x19.
 */
static void sk_r34_node_deinit_s9f(unsigned long self)
{
    sk_x_00352b20();
    sk_x_003a25d4();
    sk_x_0036b118(*(unsigned long *)(self + 8));
}

/* FUN_004a9fc4 @ 0x004a9fc4   (est. sk_regex_retain_pair)
 * Ghidra: undefined8 FUN_004a9fc4(undefined8 param_1, long param_2)
 * Retain the reference at param_2+8 and the value from FUN_004ab600; return
 * param_1.
 * Confidence: medium
 */
static unsigned long sk_r34_retain_pair(unsigned long a, unsigned long src)
{
    unsigned long v1, v2;
    v1 = *(unsigned long *)(src + 8);
    v2 = sk_x_004ab600();
    sk_x_0036b270(v2);
    sk_x_0036b270(v1);
    return a;
}

/* FUN_004aa000 @ 0x004aa000   (est. sk_regex_elem_swap_release)
 * Ghidra: void FUN_004aa000(void)
 * Swap-and-release: replace the reference at x20+8 with the one at x19+8,
 * releasing the old.
 * Confidence: medium
 * Notes: self = unaff_x19, target = unaff_x20.
 */
static void sk_r34_elem_swap_release(unsigned long self, unsigned long target)
{
    unsigned long a;
    sk_x_0034b044();
    sk_x_0036b270();
    sk_x_003a25d4();
    a = *(unsigned long *)(target + 8);
    *(unsigned long *)(target + 8) = *(unsigned long *)(self + 8);
    sk_x_0036b270();
    sk_x_0036b118(a);
}

/* FUN_004aa050 @ 0x004aa050   (est. sk_regex_emit_drop)
 * Ghidra: void FUN_004aa050(void)
 * Drop the current element: release the value through the sibling context
 * (FUN_003504d0) and run the emit helper FUN_004ac45c.
 * Confidence: low
 */
static void sk_r34_emit_drop(void)
{
    unsigned long *p;
    p = (unsigned long *)sk_x_003504d0().lo;
    sk_x_003a25d4(*p);
    sk_x_004ac45c();
}
