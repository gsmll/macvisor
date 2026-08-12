/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in the cl4_kernel.raw program. Names use seL4/cL4 vocabulary; all
 * are estimates unless string/header matched.
 *
 * Slice 0x0049eee8-0x004a36fc (worker SKR33): the frame / context bookkeeping
 * layer of the cap-invocation machinery. These small functions open the
 * running op context (x19/x20/x22), seed per-invocation fields from the
 * current thread frame, resolve descriptor/status words, bind continuation
 * records, and tail-dispatch into the reply/continuation tables. Many are
 * offset-shifted siblings that differ only in which context slot they touch.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Hardware / intrinsic helpers (same semantics as the Ghidra pseudo-ops
 * used in the decompiles).
 * ------------------------------------------------------------------ */
static inline unsigned sk_clz64(uint64_t x) { return (unsigned)__builtin_clzll(x); }
#define LZCOUNT(x) sk_clz64((uint64_t)(x))
static inline void sk_break(uint64_t a, uint64_t b) __attribute__((noreturn))
{ (void)a; (void)b; __asm__ volatile("brk #1"); }
#define SoftwareBreakpoint(a,b) sk_break((uint64_t)(a),(uint64_t)(b))

/* ------------------------------------------------------------------ *
 * Globals referenced by this slice (image-base addresses are the Ghidra
 * ground truth).
 * ------------------------------------------------------------------ */

/* ------------------------------------------------------------------ *
 * Out-of-slice callees (reconstructed by other slice workers). The
 * sk_x_XXXXXXXX names encode the Ghidra FUN_ address. Functions that Ghidra
 * shows returning a 16-byte register pair are typed cl4_result_t.
 * ------------------------------------------------------------------ */
extern unsigned long sk_x_000026e8();
extern unsigned long sk_x_00002834();
extern unsigned long sk_x_00012568();
extern unsigned long sk_x_00019858();
extern unsigned long sk_x_00021480();
extern unsigned long sk_x_00027614();
extern unsigned long sk_x_00027754();
extern unsigned long sk_x_0006b438();
extern unsigned long sk_x_000839d8();
extern unsigned long sk_x_000839f8();
extern unsigned long sk_x_00084220();
extern unsigned long sk_x_00084234();
extern cl4_result_t sk_x_0009461c();
extern unsigned long sk_x_000a6f88();
extern unsigned long sk_x_00114330();
extern unsigned long sk_x_00117cc4();
extern unsigned long sk_x_0024c9c0();
extern unsigned long sk_x_0032b65c();
extern unsigned long sk_x_00349530();
extern unsigned long sk_x_0034ab20();
extern unsigned long sk_x_0034b044();
extern unsigned long sk_x_0034b07c();
extern cl4_result_t sk_x_0034b264();
extern unsigned long sk_x_0034b7e4();
extern unsigned long sk_x_0034ba48();
extern unsigned long sk_x_0034bfb4();
extern unsigned long sk_x_0034e34c();
extern cl4_result_t sk_x_0034f2f4();
extern unsigned long sk_x_0034f8e4();
extern unsigned long sk_x_003504d0();
extern unsigned long sk_x_003507e0();
extern cl4_result_t sk_x_00350c5c();
extern cl4_result_t sk_x_00351244();
extern unsigned long sk_x_00351a38();
extern unsigned long sk_x_00351d18();
extern unsigned long sk_x_00352b20();
extern cl4_result_t sk_x_00354070();
extern unsigned long sk_x_003540d0();
extern unsigned long sk_x_00355538();
extern unsigned long sk_x_0035944c();
extern unsigned long sk_x_0036851c();
extern unsigned long sk_x_0036b118();
extern unsigned long sk_x_0036b21c();
extern unsigned long sk_x_0036b270();
extern unsigned long sk_x_003728b8();
extern unsigned long sk_x_00376820();
extern unsigned long sk_x_00377824();
extern unsigned long sk_x_00377dcc();
extern unsigned long sk_x_003a25d4();
extern unsigned long sk_x_00458940();
extern unsigned long sk_x_00459138();
extern unsigned long sk_x_004593ac();
extern unsigned long sk_x_0045a4b4();
extern unsigned long sk_x_00462bd8();
extern unsigned long sk_x_00462fec();
extern unsigned long sk_x_00463028();
extern unsigned long sk_x_00463058();
extern unsigned long sk_x_00463080();
extern unsigned long sk_x_004633e0();
extern unsigned long sk_x_00464ae8();
extern unsigned long sk_x_00464b04();
extern unsigned long sk_x_004661a4();
extern unsigned long sk_x_00492850();
extern unsigned long sk_x_00492920();
extern unsigned long sk_x_00492b3c();
extern unsigned long sk_x_00492c6c();
extern unsigned long sk_x_00497504();
extern unsigned long sk_x_0049df60();
extern unsigned long sk_x_0049dfa0();
extern unsigned long sk_x_004a4b14();
extern unsigned long sk_x_004a5414();
extern unsigned long sk_x_004a54b0();
extern unsigned long sk_x_004a83c0();
extern unsigned long sk_x_004a8ef8();
extern unsigned long sk_x_004a8f0c();
extern unsigned long sk_x_004a90e4();
extern unsigned long sk_x_004a96a0();
extern unsigned long sk_x_004aa47c();
extern unsigned long sk_x_004aa4fc();
extern unsigned long sk_x_004aa6f0();
extern unsigned long sk_x_004aa850();
extern unsigned long sk_x_004aa864();
extern unsigned long sk_x_004aa8b0();
extern cl4_result_t sk_x_004aa914();
extern unsigned long sk_x_004aaa88();
extern unsigned long sk_x_004aaaf4();
extern unsigned long sk_x_004aab30();
extern unsigned long sk_x_004aaba8();
extern unsigned long sk_x_004aabb8();
extern unsigned long sk_x_004aac14();
extern unsigned long sk_x_004aadb8();
extern unsigned long sk_x_004aae14();
extern unsigned long sk_x_004aae88();
extern unsigned long sk_x_004aaed8();
extern unsigned long sk_x_004aaf48();
extern unsigned long sk_x_004aafb8();
extern unsigned long sk_x_004ab0fc();
extern unsigned long sk_x_004ab10c();
extern unsigned long sk_x_004ab13c();
extern cl4_result_t sk_x_004ab150();
extern unsigned long sk_x_004ab1e8();
extern unsigned long sk_x_004ab230();
extern unsigned long sk_x_004ab2dc();
extern unsigned long sk_x_004ab5ec();
extern cl4_result_t sk_x_004ab600();
extern cl4_result_t sk_x_004ab710();
extern unsigned long sk_x_004ab734();
extern unsigned long sk_x_004ab74c();
extern unsigned long sk_x_004ab954();
extern unsigned long sk_x_004ab998();
extern unsigned long sk_x_004aba1c();
extern unsigned long sk_x_004aba50();
extern unsigned long sk_x_004aba60();
extern unsigned long sk_x_004aba70();
extern unsigned long sk_x_004abae4();
extern unsigned long sk_x_004abb64();
extern unsigned long sk_x_004abb80();
extern unsigned long sk_x_004abbc4();
extern unsigned long sk_x_004abbe0();
extern unsigned long sk_x_004abc50();
extern unsigned long sk_x_004abcc0();
extern unsigned long sk_x_004abda8();
extern unsigned long sk_x_004abdd0();
extern unsigned long sk_x_004abdec();
extern unsigned long sk_x_004abe08();
extern unsigned long sk_x_004abe40();
extern unsigned long sk_x_004abec0();
extern unsigned long sk_x_004abee0();
extern unsigned long sk_x_004abf50();
extern cl4_result_t sk_x_004abf7c();
extern unsigned long sk_x_004ac168();
extern unsigned long sk_x_004ac1d4();
extern unsigned long sk_x_004ac264();
extern unsigned long sk_x_004ac384();
extern unsigned long sk_x_004ac390();
extern unsigned long sk_x_004ac3a8();
extern unsigned long sk_x_004ac3c0();
extern unsigned long sk_x_004ac3d8();
extern unsigned long sk_x_004ac3fc();
extern unsigned long sk_x_004ac40c();
extern unsigned long sk_x_004ac42c();
extern unsigned long sk_x_004ac45c();
extern unsigned long sk_x_004ac46c();
extern unsigned long sk_x_004ac484();
extern unsigned long sk_x_004ac49c();
extern unsigned long sk_x_004ac4ac();
extern unsigned long sk_x_004ac4d0();
extern unsigned long sk_x_004ac550();
extern unsigned long sk_x_004ac6d0();
extern cl4_result_t sk_x_004ac784();
extern unsigned long sk_x_004ac790();
extern cl4_result_t sk_x_004ac7c8();
extern unsigned long sk_x_004ac804();
extern unsigned long sk_x_004ac87c();
extern unsigned long sk_x_004ac8fc();
extern unsigned long sk_x_004aca6c();
extern unsigned long sk_x_004aca80();
extern unsigned long sk_x_004acac0();
extern unsigned long sk_x_004acc70();
extern unsigned long sk_x_004accf0();
extern unsigned long sk_x_004a3714();
