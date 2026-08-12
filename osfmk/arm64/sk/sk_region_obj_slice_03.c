/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses. All names are estimates unless string-matched.
 *
 * Slice 03: 0x2a7268-0x2af444 (157 functions). This is the kernel's embedded Swift runtime /
 * object-service band: String/Substring/Unicode-scalar index and validation helpers, UTF-8
 * encode/decode iterators, small-string representation packing, Range/Collection index math,
 * growable-array and dictionary accessors, and a set of object-service dispatch wrappers that
 * route through the shared 0x3xxxxx Swift-stdlib method tables. Many bodies are duplicated
 * twins (one per ABI/kind selector) and share a small set of String-index helpers that live in
 * this slice (002a9ba8, 002ab8ac, 002ad62c, 002acbb8, ...). Naming uses Swift runtime vocabulary
 * (String, UnicodeScalar, Range, ContiguousArray, UTF8, Dictionary); confidence is high where a
 * Swift runtime string literal is referenced and medium otherwise.
 *
 * NOTE on the ABI: this Swift runtime band is heavily register-threaded; the decompiler reads
 * helper results as 16-byte {lo,hi} word pairs (x0:x1) that it consumes inconsistently as
 * scalars or pairs. To keep every call site valid C, ALL out-of-slice helpers are declared
 * returning `sk_word16_t` (a {lo,hi} union) with unspecified argument lists: a call whose result
 * is used as a scalar reads `.lo`; a call used as a pair reads `.lo`/`.hi`; a call used as a
 * plain statement simply discards the struct result (legal C). Bodies in this slice are
 * transcribed to use `.lo`/`.hi` at every consumption point. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "sk_internal.h"

/* 16-byte {lo, hi} result (Swift "word pair" in x0:x1). */
typedef union {
    struct { uint64_t lo; uint64_t hi; };
    uint8_t b[16];
} sk_word16_t;

typedef unsigned int uint;


/* Fatal Swift runtime error (noreturn). Signature follows the decompiled call. */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */
#define SK_FATAL(code,msg,msglen,type,typlen) \
    do { sk_fatal_error(0xb,2,(unsigned long)(msg),(msglen),2,(unsigned long)(type),(typlen),2,(code),1); \
         __builtin_trap(); } while (0)

/* SoftwareBreakpoint(1, addr) -> unconditional trap. */
#define SW_BREAK(addr) __builtin_trap()

/* ------------------------------------------------------------------ *
 * Out-of-slice helper declarations. All return a 16-byte word pair; use
 * `.lo`/`.hi` at the call site. Bodies owned by sibling slices.
 * ------------------------------------------------------------------ */

extern void FUN_001afa84() __attribute__((noreturn));

/* --- Swift runtime method-dispatch / object-service entry points (0x3xxxxx) --- */
extern sk_word16_t FUN_0034cff4();
extern sk_word16_t FUN_0034998c();
extern sk_word16_t FUN_00348a34();
extern sk_word16_t FUN_0034c2d8();
extern sk_word16_t FUN_0034baa8();
extern sk_word16_t FUN_0034b87c();
extern sk_word16_t FUN_00352cb0();
extern sk_word16_t FUN_00354140();
extern sk_word16_t FUN_00350a64();
extern sk_word16_t FUN_003528ac();
extern sk_word16_t FUN_00350a34();
extern sk_word16_t FUN_00350d14();
extern sk_word16_t FUN_00351118();
extern sk_word16_t FUN_00350efc();
extern sk_word16_t FUN_00350b84();
extern sk_word16_t FUN_003509bc();
extern sk_word16_t FUN_00351494();
extern sk_word16_t FUN_0035133c();
extern sk_word16_t FUN_00351648();
extern sk_word16_t FUN_0035370c();
extern sk_word16_t FUN_0035900c();
extern sk_word16_t FUN_00350bb4();
extern sk_word16_t FUN_00351dd8();
extern sk_word16_t FUN_00351bec();
extern sk_word16_t FUN_00350318();
extern sk_word16_t FUN_00319320();
extern sk_word16_t FUN_0034e2e4();
extern sk_word16_t FUN_00353f68();
extern sk_word16_t FUN_0034ab10();
extern sk_word16_t FUN_0034dfa4();
extern sk_word16_t FUN_00349494();
extern sk_word16_t FUN_00348a80();
extern sk_word16_t FUN_0034b3d8();
extern sk_word16_t FUN_003489c0();
extern sk_word16_t FUN_0034b758();
extern sk_word16_t FUN_00348974();
extern sk_word16_t FUN_0034987c();
extern sk_word16_t FUN_0034c840();
extern sk_word16_t FUN_0034a3b0();
extern sk_word16_t FUN_0034bf1c();
extern sk_word16_t FUN_0034a260();
extern sk_word16_t FUN_0034fcac();
extern sk_word16_t FUN_00350624();
extern sk_word16_t FUN_0034e424();
extern sk_word16_t FUN_00357ca0();
extern sk_word16_t FUN_0034d654();
extern sk_word16_t FUN_00354a28();
extern sk_word16_t FUN_0034e084();
extern sk_word16_t FUN_003504a0();
extern sk_word16_t FUN_00353850();
extern sk_word16_t FUN_00357c44();
extern sk_word16_t FUN_0034ed98();
extern sk_word16_t FUN_00357794();
extern sk_word16_t FUN_0034cad8();
extern sk_word16_t FUN_0034c034();
extern sk_word16_t FUN_0034ef68();
extern sk_word16_t FUN_00354a34();
extern sk_word16_t FUN_0034f314();
extern sk_word16_t FUN_003480ac();
extern sk_word16_t FUN_00354ef8();
extern sk_word16_t FUN_003542e8();
extern sk_word16_t FUN_003504d0();
extern sk_word16_t FUN_00356a20();
extern sk_word16_t FUN_00351e08();
extern sk_word16_t FUN_0034d004();
extern sk_word16_t FUN_00351d30();
extern sk_word16_t FUN_00351e20();
extern sk_word16_t FUN_00350b0c();
extern sk_word16_t FUN_0034d6e8();
extern sk_word16_t FUN_00348898();
extern sk_word16_t FUN_0034c978();
extern sk_word16_t FUN_0034846c();
extern sk_word16_t FUN_00351be0();
extern sk_word16_t FUN_00348304();
extern sk_word16_t FUN_00351774();
extern sk_word16_t FUN_00351790();
extern sk_word16_t FUN_00350548();
extern sk_word16_t FUN_0034b85c();
extern sk_word16_t FUN_0034a900();
extern sk_word16_t FUN_0034951c();
extern sk_word16_t FUN_003587e0();
extern sk_word16_t FUN_0034ae08();
extern sk_word16_t FUN_003488bc();
extern sk_word16_t FUN_0034a96c();
extern sk_word16_t FUN_00350a28();
extern sk_word16_t FUN_0034b3f8();
extern sk_word16_t FUN_00350d94();
extern sk_word16_t FUN_00353448();
extern sk_word16_t FUN_00348614();
extern sk_word16_t FUN_0034b848();
extern sk_word16_t FUN_0034fbb0();
extern sk_word16_t FUN_0034cec4();
extern sk_word16_t FUN_0034a018();
extern sk_word16_t FUN_00353ff4();
extern sk_word16_t FUN_0035646c();
extern sk_word16_t FUN_0034883c();
extern sk_word16_t FUN_003576c8();
extern sk_word16_t FUN_00356364();
extern sk_word16_t FUN_00354fac();
extern sk_word16_t FUN_00356328();
extern sk_word16_t FUN_0034f414();
extern sk_word16_t FUN_0034f3b4();
extern sk_word16_t FUN_00353a18();
extern sk_word16_t FUN_00354404();
extern sk_word16_t FUN_00351e3c();
extern sk_word16_t FUN_003523e0();
extern sk_word16_t FUN_00352764();
extern sk_word16_t FUN_00353510();
extern sk_word16_t FUN_003554e0();
extern sk_word16_t FUN_00350258();
extern sk_word16_t FUN_00359424();
extern sk_word16_t FUN_00350a10();
extern sk_word16_t FUN_00353e50();
extern sk_word16_t FUN_0034d6c8();
extern sk_word16_t FUN_00351dcc();
extern sk_word16_t FUN_0034a834();
extern sk_word16_t FUN_003509c8();
extern sk_word16_t FUN_003486b8();
extern sk_word16_t FUN_00349644();
extern sk_word16_t FUN_003565a8();
extern sk_word16_t FUN_003505c4();
extern sk_word16_t FUN_0034d3d4();
extern sk_word16_t FUN_00356590();
extern sk_word16_t FUN_00351a50();
extern sk_word16_t FUN_00350c68();
extern sk_word16_t FUN_00354a00();
extern sk_word16_t FUN_0035136c();
extern sk_word16_t FUN_00351ab0();
extern sk_word16_t FUN_0034ff88();
extern sk_word16_t FUN_00354858();
extern sk_word16_t FUN_00350ed0();
extern sk_word16_t FUN_003516f0();
extern sk_word16_t FUN_00348e48();
extern sk_word16_t FUN_003481fc();
extern sk_word16_t FUN_003520dc();
extern sk_word16_t FUN_00350494();
extern sk_word16_t FUN_003513b4();
extern sk_word16_t FUN_00351450();
extern sk_word16_t FUN_00350b24();
extern sk_word16_t FUN_003510dc();
extern sk_word16_t FUN_00356774();
extern sk_word16_t FUN_00350ad0();
extern sk_word16_t FUN_00350560();
extern sk_word16_t FUN_003505e8();
extern sk_word16_t FUN_00359478();
extern sk_word16_t FUN_003511cc();
extern sk_word16_t FUN_00353e08();
extern sk_word16_t FUN_00351a20();
extern sk_word16_t FUN_00351744();
extern sk_word16_t FUN_00355d1c();
extern sk_word16_t FUN_00357c04();
extern sk_word16_t FUN_0032d2f4();
extern sk_word16_t FUN_00351a38();
extern sk_word16_t FUN_00349b3c();
extern sk_word16_t FUN_0034f730();
extern sk_word16_t FUN_0034b8bc();
extern sk_word16_t FUN_0034bd90();
extern sk_word16_t FUN_0035a280();
extern sk_word16_t FUN_00350878();
extern sk_word16_t FUN_00353d64();
extern sk_word16_t FUN_00350278();
extern sk_word16_t FUN_0035484c();
extern sk_word16_t FUN_00351e84();
extern sk_word16_t FUN_0035745c();
extern sk_word16_t FUN_003508c0();
extern sk_word16_t FUN_00352498();
extern sk_word16_t FUN_00353034();
extern sk_word16_t FUN_0034fd04();
extern sk_word16_t FUN_0035a2d0();
extern sk_word16_t FUN_0034fce4();
extern sk_word16_t FUN_0034b0d4();
extern sk_word16_t FUN_003499c8();
extern sk_word16_t FUN_003490ec();
extern sk_word16_t FUN_0034da98();
extern sk_word16_t FUN_00348fd8();
extern sk_word16_t FUN_0034d3c4();
extern sk_word16_t FUN_0034ed68();
extern sk_word16_t FUN_00353178();
extern sk_word16_t FUN_00351da8();
extern sk_word16_t FUN_0034b730();
extern sk_word16_t FUN_00350bcc();
extern sk_word16_t FUN_0035063c();
extern sk_word16_t FUN_0035098c();
extern sk_word16_t FUN_00350798();
extern sk_word16_t FUN_0034b788();
extern sk_word16_t FUN_0035053c();
extern sk_word16_t FUN_00347d60();
extern sk_word16_t FUN_00347f2c();
extern sk_word16_t FUN_00355968();
extern sk_word16_t FUN_003523fc();
extern sk_word16_t FUN_0035847c();
extern sk_word16_t FUN_00352bd4();
extern sk_word16_t FUN_00348c48();
extern sk_word16_t FUN_00351ca0();
extern sk_word16_t FUN_0034f98c();
extern sk_word16_t FUN_0034dab8();
extern sk_word16_t FUN_0035ab14();
extern sk_word16_t FUN_0035ab08();
extern sk_word16_t FUN_003513f0();
extern sk_word16_t FUN_003511f0();
extern sk_word16_t FUN_00351b78();
extern sk_word16_t FUN_00351b60();
extern sk_word16_t FUN_00352ee4();
extern sk_word16_t FUN_003493ac();
extern sk_word16_t FUN_00349444();
extern sk_word16_t FUN_0035256c();
extern sk_word16_t FUN_00348d64();
extern sk_word16_t FUN_0034a958();
extern sk_word16_t FUN_003548c4();
extern sk_word16_t FUN_00352920();
extern sk_word16_t FUN_0034b318();
extern sk_word16_t FUN_00352894();
extern sk_word16_t FUN_0034b508();
extern sk_word16_t FUN_00350c80();
extern sk_word16_t FUN_00351eb4();
extern sk_word16_t FUN_00351ef8();
extern sk_word16_t FUN_0035156c();
extern sk_word16_t FUN_0035084c();
extern sk_word16_t FUN_003504f4();
extern sk_word16_t FUN_003511e4();
extern sk_word16_t FUN_0034b3c8();
extern sk_word16_t FUN_00353208();
extern sk_word16_t FUN_00358540();
extern sk_word16_t FUN_003195f8();
extern sk_word16_t FUN_0034a2f8();
extern sk_word16_t FUN_003573e8();
extern sk_word16_t FUN_0034dec4();
extern sk_word16_t FUN_0035a0d8();
extern sk_word16_t FUN_0031e210();
extern sk_word16_t FUN_0035ab20();
extern sk_word16_t FUN_00357cb4();
extern sk_word16_t FUN_00357c74();
extern sk_word16_t FUN_003577b4();
extern sk_word16_t FUN_00359c84();
extern sk_word16_t FUN_00357938();
extern sk_word16_t FUN_00352c6c();
extern sk_word16_t FUN_0034a180();
extern sk_word16_t FUN_00376820();
extern sk_word16_t FUN_003267b4();
extern sk_word16_t FUN_0034e314();
extern sk_word16_t FUN_0034c094();
extern sk_word16_t FUN_0034bb38();
extern sk_word16_t FUN_00359f54();
extern sk_word16_t FUN_00351f0();
extern sk_word16_t FUN_00377824();
extern sk_word16_t FUN_00377bec();
extern sk_word16_t FUN_003a261c();
extern sk_word16_t FUN_00365b6c();
extern sk_word16_t FUN_003a25d4();
extern sk_word16_t FUN_003a25e0();
extern sk_word16_t FUN_0036b118();
extern sk_word16_t FUN_0036b270();
extern sk_word16_t FUN_0036a940();
extern sk_word16_t FUN_00002534();
extern sk_word16_t FUN_00351db4();
extern sk_word16_t FUN_00351d18();
extern sk_word16_t FUN_00355da8();
extern sk_word16_t FUN_00351ca0();
extern sk_word16_t FUN_00354a28();
extern sk_word16_t FUN_0034a274();
extern sk_word16_t FUN_0034b430();
extern sk_word16_t FUN_0034aee4();
extern sk_word16_t FUN_00350524();
extern sk_word16_t FUN_00350618();
extern sk_word16_t FUN_00350944();
extern sk_word16_t FUN_00350a04();
extern sk_word16_t FUN_00350c5c();
extern sk_word16_t FUN_00350ea4();
extern sk_word16_t FUN_003510dc();
extern sk_word16_t FUN_0035145c();
extern sk_word16_t FUN_00351488();
extern sk_word16_t FUN_00351708();
extern sk_word16_t FUN_0035193c();
extern sk_word16_t FUN_00353100();
extern sk_word16_t FUN_003548b8();
extern sk_word16_t FUN_00355bb8();
extern sk_word16_t FUN_00356524();
extern sk_word16_t FUN_00358b90();
extern sk_word16_t FUN_0034c51c();
extern sk_word16_t FUN_0034cbb0();
extern sk_word16_t FUN_0035089c();
extern sk_word16_t FUN_003507e0();
extern sk_word16_t FUN_003504ac();
extern sk_word16_t FUN_00350c80();

extern sk_word16_t FUN_00353a24();

extern sk_word16_t FUN_0018de98();

extern sk_word16_t FUN_0035298c();

extern sk_word16_t FUN_00319338();

extern sk_word16_t FUN_0031be18();

extern sk_word16_t FUN_00354300();

extern sk_word16_t FUN_00350df4();

extern sk_word16_t FUN_001afe4c();

extern sk_word16_t FUN_002a6efc();


extern sk_word16_t FUN_00344e54();
extern sk_word16_t FUN_00349fcc();
extern sk_word16_t FUN_0034ba28();
extern sk_word16_t FUN_00350470();
extern sk_word16_t FUN_00353590();
extern sk_word16_t FUN_00359a30();
extern uint64_t DAT_004f2240;


extern sk_word16_t FUN_00358da0();
extern sk_word16_t FUN_003518c4();
extern sk_word16_t FUN_003516cc();
extern sk_word16_t FUN_00348e18();
extern sk_word16_t FUN_00351444();
extern sk_word16_t FUN_003509e0();
extern sk_word16_t FUN_003508cc();
extern sk_word16_t FUN_00351654();


extern sk_word16_t FUN_0029ea8c();
extern sk_word16_t FUN_0031e030();
extern sk_word16_t FUN_00348ce8();
extern sk_word16_t FUN_00349720();
extern sk_word16_t FUN_0034c444();
extern sk_word16_t FUN_00351750();


extern sk_word16_t FUN_00355770();
extern sk_word16_t FUN_00355814();
extern sk_word16_t FUN_00359fc0();


extern sk_word16_t FUN_000bd3a4();
extern sk_word16_t FUN_00100efc();
extern sk_word16_t FUN_003194f8();
extern sk_word16_t FUN_0031e2e0();
extern sk_word16_t FUN_00348f50();
extern sk_word16_t FUN_0034ef78();
extern sk_word16_t FUN_0035047c();
extern sk_word16_t FUN_00351984();
extern sk_word16_t FUN_00353274();

extern sk_word16_t FUN_00267820();
extern sk_word16_t FUN_00310c44();
extern sk_word16_t FUN_0031b46c();
extern sk_word16_t FUN_0031b49c();
extern sk_word16_t FUN_00346d38();
extern sk_word16_t FUN_003493d8();
extern sk_word16_t FUN_0034a6b0();
extern sk_word16_t FUN_0034aebc();
extern sk_word16_t FUN_00350b54();
extern sk_word16_t FUN_003510a0();
extern sk_word16_t FUN_003510c4();
extern sk_word16_t FUN_00352480();
extern sk_word16_t FUN_003542dc();
extern sk_word16_t FUN_003551f8();
extern sk_word16_t FUN_00356048();
extern sk_word16_t FUN_00359208();
extern sk_word16_t FUN_003598a0();
extern sk_word16_t FUN_0035b67c();
extern sk_word16_t FUN_0036b6ac();
extern sk_word16_t FUN_0039a128();
extern sk_word16_t FUN_003d3550();



extern void FUN_002a7268();
extern void FUN_002a72e4();
extern void FUN_002a74f8();
extern uint64_t FUN_002a782c();
extern uint64_t FUN_002a7c00();
extern sk_word16_t FUN_002a7f58();
extern void FUN_002a82cc();
extern void FUN_002a8870();
extern void FUN_002a88bc();
extern void FUN_002a8954();
extern void FUN_002a8a88();
extern void FUN_002a8ca0();
extern void FUN_002a8d04();
extern void FUN_002a8e28();
extern void FUN_002a8f40();
extern void FUN_002a919c();
extern void FUN_002a92b8();
extern void FUN_002a93b8();
extern void FUN_002a95b4();
extern void FUN_002a999c();
extern void FUN_002a9a88();
extern void FUN_002a9b7c();
extern sk_word16_t FUN_002a9b9c();
extern sk_word16_t FUN_002a9ba8();
extern void FUN_002a9bd0();
extern void FUN_002a9c14();
extern sk_word16_t FUN_002a9d64();
extern sk_word16_t FUN_002a9f3c();
extern void FUN_002aa154();
extern void FUN_002aa2a0();
extern void FUN_002aa55c();
extern void FUN_002aa584();
extern void FUN_002aa5e8();
extern sk_word16_t FUN_002aa62c();
extern sk_word16_t FUN_002aa68c();
extern sk_word16_t FUN_002aaae4();
extern void FUN_002aab54();
extern uint64_t FUN_002aacf8();
extern void FUN_002aadb8();
extern uint64_t FUN_002aadf0();
extern void FUN_002aae80();
extern uint64_t FUN_002aaeb8();
extern void FUN_002aaf60();
extern void FUN_002aaf64();
extern uint64_t FUN_002aaf80();
extern void FUN_002ab058();
extern sk_word16_t FUN_002ab130();
extern sk_word16_t FUN_002ab220();
extern sk_word16_t FUN_002ab2d4();
extern sk_word16_t FUN_002ab388();
extern uint64_t FUN_002ab49c();
extern uint64_t FUN_002ab4d4();
extern void FUN_002ab5bc();
extern void FUN_002ab6a0();
extern sk_word16_t FUN_002ab778();
extern void FUN_002ab7f0();
extern sk_word16_t FUN_002ab8ac();
extern void FUN_002ab984();
extern void FUN_002ab9e0();
extern void FUN_002aba18();
extern void FUN_002aba8c();
extern uint64_t FUN_002abcb0();
extern void FUN_002abda8();
extern uint64_t FUN_002abe60();
extern void FUN_002abf50();
extern void FUN_002ac024();
extern void FUN_002ac0d8();
extern void FUN_002ac168();
extern void FUN_002ac214();
extern sk_word16_t FUN_002ac260();
extern void FUN_002ac3bc();
extern void FUN_002ac73c();
extern void FUN_002ac764();
extern void FUN_002ac768();
extern void FUN_002ac784();
extern void FUN_002ac828();
extern sk_word16_t FUN_002ac854();
extern void FUN_002ac99c();
extern void FUN_002aca00();
extern void FUN_002acbb8();
extern void FUN_002acc20();
extern void FUN_002acd30();
extern void FUN_002ace24();
extern void FUN_002acfbc();
extern void FUN_002acfc0();
extern void FUN_002acfe0();
extern void FUN_002acfe4();
extern void FUN_002ad02c();
extern void FUN_002ad060();
extern void FUN_002ad088();
extern void FUN_002ad0d4();
extern void FUN_002ad10c();
extern void FUN_002ad1a0();
extern void FUN_002ad1c8();
extern void FUN_002ad1f8();
extern void FUN_002ad1fc();
extern void FUN_002ad228();
extern void FUN_002ad274();
extern void FUN_002ad2c4();
extern void FUN_002ad310();
extern void FUN_002ad358();
extern int64_t FUN_002ad3a8();
extern void FUN_002ad450();
extern void FUN_002ad454();
extern uint64_t FUN_002ad480();
extern void FUN_002ad4d8();
extern void FUN_002ad4dc();
extern uint64_t FUN_002ad4fc();
extern void FUN_002ad608();
extern sk_word16_t FUN_002ad62c();
extern void FUN_002ad668();
extern void FUN_002ad66c();
extern void FUN_002ad68c();
extern void FUN_002ad6d8();
extern void FUN_002ad6dc();
extern uint64_t FUN_002ad700();
extern void FUN_002ad78c();
extern void FUN_002ad95c();
extern void FUN_002ada34();
extern void FUN_002adcf8();
extern void FUN_002add28();
extern void FUN_002add84();
extern void FUN_002addc0();
extern uint64_t FUN_002ade9c();
extern void FUN_002adf54();
extern uint64_t FUN_002adfb4();
extern uint32_t FUN_002ae028();
extern sk_word16_t FUN_002ae098();
extern sk_word16_t FUN_002ae1ac();
extern sk_word16_t FUN_002ae2c0();
extern void FUN_002ae6d4();
extern void FUN_002ae818();
extern void FUN_002ae858();
extern sk_word16_t FUN_002ae880();
extern void FUN_002aea60();
extern void FUN_002aeaa0();
extern void FUN_002aead0();
extern void FUN_002aead4();
extern void FUN_002aeb14();
extern void FUN_002aeb18();
extern void FUN_002aeb30();
extern void FUN_002aebe0();
extern void FUN_002aeca8();
extern void FUN_002aecf0();
extern void FUN_002af068();
extern void FUN_002af0d0();
extern void FUN_002af138();
extern void FUN_002af19c();
extern void FUN_002af214();
extern void FUN_002af24c();
extern void FUN_002af27c();
extern void FUN_002af2ac();
extern void FUN_002af2b0();
extern uint64_t FUN_002af2c4();
extern sk_word16_t FUN_002af340();
extern void FUN_002af40c();
extern void FUN_002af444();

/* Out-of-slice String/Collection helpers. */
extern sk_word16_t FUN_00209928();
extern sk_word16_t FUN_002093d4();
extern sk_word16_t FUN_001e3f70();
extern sk_word16_t FUN_001d95f4();
extern sk_word16_t FUN_002a2f60();
extern sk_word16_t FUN_002a2bb0();
extern sk_word16_t FUN_002a4c98();
extern sk_word16_t FUN_002a49d4();
extern sk_word16_t FUN_002a4a2c();
extern sk_word16_t FUN_002a4ab4();
extern sk_word16_t FUN_002a49a8();
extern sk_word16_t FUN_002a66f0();
extern sk_word16_t FUN_002a6900();
extern sk_word16_t FUN_002a6a18();
extern sk_word16_t FUN_002a539c();
extern sk_word16_t FUN_002a5400();
extern sk_word16_t FUN_002a55c0();
extern sk_word16_t FUN_002a58b8();
extern sk_word16_t FUN_002a5bf0();
extern sk_word16_t FUN_002a6238();
extern sk_word16_t FUN_002a3e64();
extern sk_word16_t FUN_002a200c();
extern sk_word16_t FUN_002a1278();
extern sk_word16_t FUN_002a0d50();
extern sk_word16_t FUN_0029ead8();
extern sk_word16_t FUN_0029c18c();
extern sk_word16_t FUN_0029c2bc();
extern sk_word16_t FUN_0029b1e0();
extern sk_word16_t FUN_0029db34();
extern sk_word16_t FUN_00298e58();
extern sk_word16_t FUN_0028e8c0();
extern sk_word16_t FUN_00291ee0();
extern sk_word16_t FUN_00285e24();
extern sk_word16_t FUN_00284ff4();
extern sk_word16_t FUN_00258c60();
extern sk_word16_t FUN_002364dc();
extern sk_word16_t FUN_0021bf60();
extern sk_word16_t FUN_002171a8();
extern sk_word16_t FUN_002177bc();
extern sk_word16_t FUN_00217c60();
extern sk_word16_t FUN_00217ea0();
extern sk_word16_t FUN_00218068();
extern sk_word16_t FUN_00216b88();
extern sk_word16_t FUN_0022d2f4();
extern sk_word16_t FUN_002523d8();
extern sk_word16_t FUN_00255324();
extern sk_word16_t FUN_002557b8();
extern sk_word16_t FUN_0026bd30();
extern sk_word16_t FUN_0027169c();
extern sk_word16_t FUN_00273310();
extern sk_word16_t FUN_002740dc();
extern sk_word16_t FUN_0027630c();
extern sk_word16_t FUN_002764a8();
extern sk_word16_t FUN_002b15d0();
extern sk_word16_t FUN_002b257c();
extern sk_word16_t FUN_002b0f08();
extern sk_word16_t FUN_002b0f7c();
extern sk_word16_t FUN_002bbbe8();
extern sk_word16_t FUN_002bbcd8();
extern sk_word16_t FUN_002c6c04();
extern sk_word16_t FUN_002c6d00();
extern sk_word16_t FUN_002c6aac();
extern sk_word16_t FUN_0001da84();
extern sk_word16_t FUN_001676cc();
extern sk_word16_t FUN_00167404();
extern sk_word16_t FUN_001a4e10();
extern sk_word16_t FUN_001a89a8();
extern sk_word16_t FUN_001a8a8c();
extern sk_word16_t FUN_001a8564();
extern sk_word16_t FUN_001a84f4();
extern sk_word16_t FUN_001a4efc();
extern sk_word16_t FUN_001a0870();
extern sk_word16_t FUN_0019cac8();
extern sk_word16_t FUN_001bcdcc();
extern sk_word16_t FUN_001bd66c();
extern sk_word16_t FUN_001d2d1c();
extern sk_word16_t FUN_001d2f4c();
extern sk_word16_t FUN_001e4cbc();
extern sk_word16_t FUN_001e9d8c();
extern sk_word16_t FUN_001eb088();
extern sk_word16_t FUN_001eb73c();
extern sk_word16_t FUN_001ee030();
extern sk_word16_t FUN_001f98e8();
extern sk_word16_t FUN_0011aa70();
extern sk_word16_t FUN_0011d7e8();
extern sk_word16_t FUN_00106e3c();
extern sk_word16_t FUN_0010084c();
extern sk_word16_t FUN_000e15d8();
extern sk_word16_t FUN_000e72b0();
extern sk_word16_t FUN_000dbd0c();
extern sk_word16_t FUN_000dbde8();
extern sk_word16_t FUN_000b773c();
extern sk_word16_t FUN_000b4390();
extern sk_word16_t FUN_000b43d0();
extern sk_word16_t FUN_000b43e8();
extern sk_word16_t FUN_000b45b0();
extern sk_word16_t FUN_000b4594();
extern sk_word16_t FUN_000a6f88();
extern sk_word16_t FUN_000a6e20();
extern sk_word16_t FUN_000a6e14();
extern sk_word16_t FUN_000a68f4();
extern sk_word16_t FUN_000a68c4();
extern sk_word16_t FUN_000a93e4();
extern sk_word16_t FUN_000a9454();
extern sk_word16_t FUN_0009461c();
extern sk_word16_t FUN_0008e518();
extern sk_word16_t FUN_0008e500();
extern sk_word16_t FUN_00084220();
extern sk_word16_t FUN_00084234();
extern sk_word16_t FUN_00084180();
extern sk_word16_t FUN_00084174();
extern sk_word16_t FUN_0008412c();
extern sk_word16_t FUN_0008409c();
extern sk_word16_t FUN_0007c1c4();
extern sk_word16_t FUN_0007c1a4();
extern sk_word16_t FUN_0007c028();
extern sk_word16_t FUN_00077894();
extern sk_word16_t FUN_00077888();
extern sk_word16_t FUN_00077604();
extern sk_word16_t FUN_000775b8();
extern sk_word16_t FUN_00077070();
extern sk_word16_t FUN_0006b6f4();
extern sk_word16_t FUN_0006b42c();
extern sk_word16_t FUN_0006b3f4();
extern sk_word16_t FUN_0006b2ec();
extern sk_word16_t FUN_0006a4c0();
extern sk_word16_t FUN_000651bc();
extern sk_word16_t FUN_00041138();
extern sk_word16_t FUN_00027754();
extern sk_word16_t FUN_00002834();
extern sk_word16_t FUN_000026e8();
extern sk_word16_t FUN_0001d4a0();
extern sk_word16_t FUN_0001a1c8();
extern sk_word16_t FUN_00019858();

/* thunks (tail-call stubs). */
extern void thunk_FUN_002a2f60();
extern void thunk_FUN_0036b270();
extern void thunk_FUN_002acbb8();
extern void thunk_FUN_002298d4();
extern void thunk_FUN_00200b38();
extern sk_word16_t thunk_FUN_001ed960();
extern void thunk_FUN_002a2698();
extern sk_word16_t thunk_FUN_000126e8();

/* Shared globals / dispatch pointer. */
extern uint64_t (*DAT_00658c00)();
extern uint64_t DAT_00657778;
extern uint64_t DAT_00657798;
extern uint64_t DAT_006577c8;
extern uint64_t DAT_006577d0;
extern uint64_t DAT_006577a8;
extern uint64_t DAT_006577d8[];
extern uint64_t DAT_00657600;
extern uint64_t DAT_00657608;
extern uint64_t DAT_00657688;
extern uint64_t DAT_00657690;
extern uint64_t DAT_004f1968;
extern uint64_t DAT_004f1970;
extern uint64_t DAT_004f2170;
extern uint64_t DAT_004f2160;
extern uint64_t DAT_004f2168;
extern uint64_t DAT_004c4010;
extern uint64_t DAT_004e7fb0;
extern uint64_t DAT_004e9a4c;
extern uint64_t DAT_004e7a30;
extern uint64_t DAT_004e7d78;
extern uint64_t DAT_00611b24;
extern uint64_t DAT_00612600;
extern uint64_t DAT_005d32c2;
extern uint64_t DAT_005d32c4;
extern uint64_t DAT_005a3680;
extern uint64_t DAT_002ada30;
extern uint64_t LAB_00657688;
extern uint64_t DAT_00657680;
extern uint64_t LAB_0027ccec;
extern uint64_t LAB_003243b0;
extern uint64_t LAB_00657690;

/* String / fatal literal addresses referenced by the Swift runtime traps. */
extern uint64_t s_Fatal_error_005accd0;
extern uint64_t s_Index_out_of_range_005cd940;
extern uint64_t s_Index_out_of_bounds_005cdab0;
extern uint64_t s_Swift_Collection_swift_005cdad0;
extern uint64_t s_Swift_Repeat_swift_005d0350;
extern uint64_t s_Unexpectedly_found_nil_while_unw_005cd7d0;
extern uint64_t s_Swift_String_swift_005ce680;
extern uint64_t s_Swift_Range_swift_005cda30;
extern uint64_t s_Range_requires_lowerBound__upp_005cda00;
extern uint64_t s_String_index_is_out_of_bounds_005ce6a0;
extern uint64_t s_Swift_StringUnicodeScalarView_sw_005ce6c0;
extern uint64_t s_Swift_StringIndexValidation_swif_005d32a0;
extern uint64_t s_Substring_index_is_out_of_bounds_005d0960;
extern uint64_t s_Substring_index_range_is_out_of_b_005d3890;
extern uint64_t s_Unicode_Scalar_UTF8View_index_is_005cfe40;
extern uint64_t s_Swift_UnicodeScalar_swift_005cfe00;
extern uint64_t s_UnsafeMutableRawPointer_initiali_005d0820;
extern uint64_t s_UnsafeMutableRawPointer_initiali_005d0860;
extern uint64_t s_Swift_UnicodeHelpers_swift_005ce730;

/* ------------------------------------------------------------------ *
 * Per-cpu container slot base (the decompiler's *unaff_x20): a pointer to a
 * 16-byte {lo,hi} word-pair slot threaded through the Swift runtime calls. */
extern uint64_t *base_slot(void);

/* In-slice forward declarations (functions defined in this file). */
extern void   sk_swift_kind_dispatch_guard(void);
extern void   sk_swift_string_unicode_advance(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_obj_service_dispatch(uint64_t, uint64_t, uint64_t);
extern uint64_t sk_swift_string_append(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t sk_swift_string_append_empty(uint64_t, uint64_t);
extern sk_word16_t sk_swift_substring_slice(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_literal_build(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_grow_check(uint64_t);
extern void   sk_swift_utf8_append_validated(void);
extern void   sk_swift_utf8_append_ascii_loop(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_utf8_append_multibyte_loop(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_utf8_append_simple(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_utf8_append_params(uint64_t, uint64_t, uint64_t *, uint64_t);
extern void   sk_swift_utf8_append_refs(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_utf8_unicode_scalar_encode(uint64_t, uint64_t, uint32_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_utf8_append_wide(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_utf8_append_ascii(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_utf8_append_builder(void);
extern void   sk_swift_string_advance_end(void);
extern void   sk_swift_string_scalar_count(void);
extern void   sk_swift_obj_release_pair(void);
extern void   sk_swift_obj_release_single(void);
extern sk_word16_t sk_swift_string_storage_base(uint64_t, uint64_t);
extern sk_word16_t sk_swift_string_resolve_storage(void);
extern void   sk_swift_closure_invoke(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_range_merge(void);
extern sk_word16_t sk_swift_string_index_offset(uint64_t, uint64_t, uint64_t, uint64_t);
extern sk_word16_t sk_swift_string_index_step(uint64_t, int64_t, uint64_t, uint64_t);
extern void   sk_swift_task_descriptor_build(void);
extern void   sk_swift_string_split_whitespace(void);
extern void   sk_swift_index_emit_word(uint64_t, uint64_t);
extern void   sk_swift_utf8_emit_validated(void);
extern void   sk_swift_utf8_emit_state(void);
extern sk_word16_t sk_swift_uint_radix_label(uint64_t);
extern sk_word16_t sk_swift_uint_description(uint64_t);
extern sk_word16_t sk_swift_dictionary_lookup_guard(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_iterate_lines(void);
extern uint64_t sk_swift_string_has_prefix(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_obj_release_pair2(void);
extern uint64_t sk_swift_string_grown_index(void);
extern void   sk_swift_obj_release_pair3(void);
extern uint64_t sk_swift_string_grown_index2(void);
extern void   sk_swift_string_index_emit_a(void);
extern void   sk_swift_string_index_emit_b(void);
extern uint64_t sk_swift_string_index_resolve(void);
extern void   sk_swift_string_prefix_emit(void);
extern sk_word16_t sk_swift_string_index_validate(uint64_t, uint64_t, uint64_t);
extern sk_word16_t sk_swift_substring_index_validate(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern sk_word16_t sk_swift_substring_index_validate_closed(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern sk_word16_t sk_swift_substring_index_range_validate(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t sk_swift_string_index_repack(uint64_t);
extern uint64_t sk_swift_substring_index_repack(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_index_range_commit(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_prefix_emit2(void);
extern sk_word16_t sk_swift_string_index_validate_inline(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_range_emit(void);
extern sk_word16_t sk_swift_string_buffer_reserve(void);
extern void   sk_swift_string_describe(void);
extern void   sk_swift_string_new_builtin(sk_word16_t *);
extern void   sk_swift_string_init_hash(void);
extern void   sk_swift_string_hash_finalize(void);
extern uint64_t sk_swift_string_contains_char(uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_canonicalize(void);
extern uint64_t sk_swift_string_has_scalar(uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_canonicalize_scalar(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_contains_char2(uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_sha_compress_block(uint8_t *, int64_t, uint64_t *);
extern void   sk_swift_array_append_bytes(uint64_t);
extern void   sk_swift_array_for_each(uint64_t);
extern sk_word16_t sk_swift_utf8_validate_and_advance(void);
extern void   sk_swift_obj_service_rethrow(sk_word16_t *, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_obj_new_error(sk_word16_t *);
extern void   sk_swift_string_append_refs2(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_append_refs3(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_append_literal(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_new_empty(sk_word16_t *);
extern sk_word16_t sk_swift_array_release_pair(uint64_t);
extern void   sk_swift_obj_service_dispatch2(uint64_t);
extern void   sk_swift_obj_service_dispatch3(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_obj_release_slot(void);
extern void   sk_swift_string_op_dispatch(void);
extern void   sk_swift_string_op_dispatch2(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_next_scalar(void);
extern void   sk_swift_string_append_scalar_a(uint64_t, uint64_t);
extern void   sk_swift_string_append_scalar_b(uint64_t, uint64_t);
extern void   sk_swift_string_release_a(uint64_t);
extern void   sk_swift_string_release_b(uint64_t);
extern void   sk_swift_string_new_substr(sk_word16_t *, uint64_t *, uint64_t);
extern void   sk_swift_string_op_pair(sk_word16_t *);
extern void   sk_swift_string_release_slot(uint64_t *);
extern void   sk_swift_string_release_substr(uint64_t *, uint64_t *);
extern void   sk_swift_string_op_dispatch3(uint64_t, uint64_t *, uint64_t);
extern void   sk_swift_string_new_from_ptr(sk_word16_t *);
extern void   sk_swift_string_new_utf8(sk_word16_t *);
extern void   sk_swift_string_copy_a(void);
extern void   sk_swift_string_copy_b(void);
extern void   sk_swift_string_fail_index(void);
extern void   sk_swift_string_fail_bounds_a(void);
extern void   sk_swift_string_fail_bounds_b(void);
extern void   sk_swift_fatal_range_0x168(void);
extern void   sk_swift_fatal_range_0x16d(void);
extern int64_t sk_swift_float_to_int(void);
extern void   sk_swift_array_element_ptr(void);
extern void   sk_swift_array_element_ptr2(void);
extern uint64_t sk_swift_array_element_ptr_resolve(void);
extern void   sk_swift_array_release_header_a(void);
extern void   sk_swift_array_release_header_b(void);
extern uint64_t sk_swift_string_init_buffer(int64_t, uint64_t);
extern void   sk_swift_array_append_byte(uint64_t, uint8_t);
extern sk_word16_t sk_swift_string_byte_extent(uint64_t, uint64_t);
extern void   sk_swift_string_meta_release_a(void);
extern void   sk_swift_string_meta_release_b(void);
extern void   sk_swift_string_meta_release_full(void);
extern void   sk_swift_string_meta_release_full2_a(void);
extern void   sk_swift_string_meta_release_full2_b(void);
extern uint64_t sk_swift_dict_lookup_or_create(void);
extern void   sk_swift_dict_find_slot(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_dict_lookup_index(void);
extern void   sk_swift_dict_rebuild_slots(void);
extern void   sk_swift_dict_sync_buckets(void);
extern void   sk_swift_dict_set_capacity(uint64_t, uint8_t);
extern void   sk_swift_dict_new_bucket(uint64_t);
extern void   sk_swift_dict_new_bucket_desc(void);
extern uint64_t sk_swift_unsafe_rawpointer_init(uint64_t, uint64_t, int64_t, uint64_t, uint64_t);
extern void   sk_swift_unsafe_rawpointer_store(uint8_t, uint64_t, int64_t, int64_t);
extern uint64_t sk_swift_string_scalar_advance(void);
extern uint32_t sk_swift_utf8_char_width(int64_t, uint64_t, uint64_t);
extern sk_word16_t sk_swift_utf8_next_char(void);
extern sk_word16_t sk_swift_utf8_decode_char(int64_t, uint64_t, uint64_t);
extern sk_word16_t sk_swift_string_scalar_prev(uint64_t, int64_t, uint64_t, uint64_t *, uint64_t);
extern void   sk_swift_string_scalar_prev_one(uint64_t *);
extern void   sk_swift_string_scalar_next(void);
extern void   sk_swift_string_scalar_step(void);
extern sk_word16_t sk_swift_unicode_scalar_decode(uint32_t *, uint64_t *);
extern void   sk_swift_string_normalize(void);
extern void   sk_swift_string_append_guard(void);
extern void   sk_swift_string_offset_apply_a(void);
extern void   sk_swift_string_offset_apply_b(void);
extern void   sk_swift_string_finalize_a(void);
extern void   sk_swift_string_finalize_b(void);
extern void   sk_swift_string_scalar_next_index(uint64_t *, uint64_t *);
extern void   sk_swift_string_scalar_next_index2(uint64_t *);
extern void   sk_swift_string_append_closure(uint64_t, uint64_t, uint64_t, uint64_t);
extern void   sk_swift_unicode_scalar_next(uint32_t *);
extern void   sk_swift_string_append_desc(void);
extern void   sk_swift_string_builder_commit(void);
extern void   sk_swift_string_new_from_flag(sk_word16_t *, uint32_t *);
extern void   sk_swift_string_commit2(void);
extern void   sk_swift_string_index_fetch(uint32_t *, uint64_t *);
extern void   sk_swift_string_index_fetch2(uint32_t *);
extern void   sk_swift_string_index_fetch3(uint32_t *);
extern void   sk_swift_string_index_copy_a(void);
extern void   sk_swift_string_index_copy_b(void);
extern uint64_t sk_swift_string_index_resolve2(void);
extern sk_word16_t sk_swift_string_is_scalar_boundary(uint64_t, uint64_t, uint64_t);
extern void   sk_swift_string_dispatch_guard2(void);
extern void   sk_swift_string_op_guard(uint64_t, uint64_t);

/* ================================================================== *
 * FUNCTIONS IN ADDRESS ORDER (0x2a7268-0x2af444)
 * ================================================================== */

/* FUN_002a7268 @ 0x002a7268   (est. sk_swift_kind_dispatch_guard)
 * Ghidra: void FUN_002a7268(void)
 * Swift "is this the expected type" guard for the object-service layer.
 * Resolves the runtime type descriptor for a global (DAT_00657600 /
 * DAT_004f1968); if the resolved word equals a known "special" value
 * (0x6753a0 or 0x675c68) it traps via a software breakpoint (those kinds
 * are unimplemented/fatal), otherwise it falls back to the alternate
 * descriptor table and silently returns on mismatch.
 * Confidence: medium
 * Notes: pure type-dispatch guard; SW_BREAK at 0x2a72dc/e0/e4. */
void sk_swift_kind_dispatch_guard(void)
{
    uint64_t kind = FUN_00002534((uint64_t)&DAT_00657600, (uint64_t)&DAT_004f1968).lo;
    if (kind == 0x6753a0) {
        SW_BREAK(0x2a72dc);
    }
    if (kind != 0x675c68) {
        uint64_t alt = FUN_00002534(0x652b30, (uint64_t)&DAT_004c4010).lo;
        if (kind != alt) {
            return;
        }
        SW_BREAK(0x2a72e4);
    }
    SW_BREAK(0x2a72e0);
}

/* FUN_002a72e4 @ 0x002a72e4   (est. sk_swift_string_unicode_advance)
 * Ghidra: void FUN_002a72e4(ulong param_1, ulong param_2, ulong param_3)
 * Advances a String.Index / UnicodeScalar.Index through a UTF-8 buffer by a
 * run-length `count` given the String storage pair (lo, hi) and the per-cpu
 * container slot (*unaff_x20) holding the current {lo,hi} cursor. Each step
 * re-validates the encoding, releases replaced references, and writes the
 * new cursor back into the slot. Runs the Swift Range index-out-of-range
 * fatal when the requested advance overruns the buffer.
 * Confidence: medium
 * Notes: slot *unaff_x20 is a {lo,hi} word pair; thunk_FUN_0036b270 /
 *   FUN_003a25d4 release refs, FUN_002a4c98 inserts, FUN_00291ee0 merges. */
void sk_swift_string_unicode_advance(uint64_t count, uint64_t lo, uint64_t hi)
{
    uint64_t *slot = (uint64_t *)(uintptr_t)base_slot();
    uint64_t resolved = FUN_00002534((uint64_t)&DAT_00657608, (uint64_t)&DAT_004f1970).lo;
    if (resolved == 0x6753a0) {
        thunk_FUN_002acbb8(lo, hi);
        return;
    }
    if (resolved == 0x675c68) {
        SW_BREAK(0x2a74f8);
    }
    uint64_t alt = FUN_00002534(0x652b30, (uint64_t)&DAT_004c4010).lo;
    if (resolved != alt) {
        uint64_t width = hi & 0xffffffffffff;
        if ((lo & 0x2000000000000000) != 0) {
            width = lo >> 0x38 & 0xf;
        }
        uint64_t remaining = count & ((long)count >> 0x3f ^ 0xffffffffffffffffU);
        thunk_FUN_0036b270(lo);
        while (true) {
            if (count == 0) {
                FUN_003a25d4(lo);
                return;
            }
            if (remaining == 0) break;
            uint64_t curLo = slot[0];
            uint64_t curHi = slot[1];
            uint64_t curW = curLo & 0xffffffffffff;
            if ((curHi & 0x2000000000000000) != 0) {
                curW = curHi >> 0x38 & 0xf;
            }
            if ((curW == 0) && (((curLo & (curHi ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                thunk_FUN_0036b270(lo);
                FUN_003a25d4(curHi);
                slot[0] = hi;
                slot[1] = lo;
            }
            else if (((curHi >> 0x3d & 1) == 0) ||
                    (((lo >> 0x3d & 1) == 0) ||
                     (((uint)FUN_00291ee0(curLo, curHi, lo, hi).lo & 0xff) == 1))) {
                thunk_FUN_0036b270(lo);
                FUN_002a4c98(hi, lo, 0, width);
                FUN_003a25d4(lo);
            }
            else {
                FUN_003a25d4(curHi);
                slot = (uint64_t *)(uintptr_t)FUN_00291ee0(curLo, curHi, lo, hi).lo;
            }
            remaining = remaining - 1;
            count = count - 1;
        }
        SK_FATAL(0x51, (unsigned long)&s_Index_out_of_range_005cd940, 0x12,
                 (unsigned long)&s_Swift_Repeat_swift_005d0350, 0x12);
    }
    uint64_t n = *(uint64_t *)(count + 0x10);
    if (n != 0) {
        uint64_t *p = (uint64_t *)(count + 0x28);
        do {
            uint64_t key2 = p[-1];
            uint64_t val2 = p[0];
            uint64_t curLo = slot[0];
            uint64_t curHi = slot[1];
            uint64_t curW = curLo & 0xffffffffffff;
            if ((curHi & 0x2000000000000000) != 0) {
                curW = curHi >> 0x38 & 0xf;
            }
            if ((curW == 0) && (((curLo & (curHi ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                thunk_FUN_0036b270(val2);
                FUN_003a25d4(curHi);
                slot[0] = key2;
                slot[1] = val2;
            }
            else {
                uint64_t valW = val2 >> 0x38 & 0xf;
                uint64_t t;
                if ((curHi >> 0x3d & 1) == 0) {
                    t = key2 & 0xffffffffffff;
                    if ((val2 & 0x2000000000000000) != 0) {
                        t = valW;
                    }
                }
                else if ((val2 >> 0x3d & 1) == 0) {
                    t = key2 & 0xffffffffffff;
                }
                else {
                    sk_word16_t m = FUN_00291ee0(curLo, curHi, key2, val2);
                    t = valW;
                    if (((uint)m.lo & 0xff) != 1) {
                        FUN_003a25d4(curHi);
                        slot = (uint64_t *)(uintptr_t)m.lo;
                        goto next_slot;
                    }
                }
                thunk_FUN_0036b270(val2);
                FUN_002a4c98(key2, val2, 0, t);
                FUN_003a25d4(val2);
            }
next_slot:
            p = p + 2;
            n = n - 1;
        } while (n != 0);
    }
}

/* FUN_002a74f8 @ 0x002a74f8   (est. sk_swift_obj_service_dispatch)
 * Ghidra: void FUN_002a74f8(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Object-service dispatch hub. Saves the register frame, then dispatches on
 * the per-cpu method-table kind: for the three Swift "task/thread" kinds it
 * restores the saved frame and tails through the shared object-service
 * handlers (002acbb8 / 002a4c98 / the String-merge path). Otherwise it runs
 * a two-phase parse via FUN_00365b6c, invokes the resolved method-table
 * closure, merges the produced {lo,hi} pair into the per-cpu container slot,
 * and finally restores the frame. Fatal on parse validation failure.
 * Confidence: medium
 * Notes: register-threaded dispatch; heavy indirect calls through DAT_00658c00
 *   and extraout_ method-table slots. */
void sk_swift_obj_service_dispatch(uint64_t a, uint64_t b, uint64_t c)
{
    FUN_0008e518();
    FUN_00353a24();
    FUN_00350a64();
    FUN_003528ac();
    uint64_t task = FUN_00377824().lo;
    FUN_000a6f88();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_00349494();
    DAT_00658c00();
    FUN_00348a34();
    DAT_00658c00();
    FUN_0034baa8();
    DAT_00658c00();
    FUN_0034b87c();
    FUN_00352cb0();
    /* Three dispatch kinds are handled directly; the general path runs the
     * parse-and-merge sequence below. */
    FUN_00354140();
    FUN_00351494();
    FUN_00350d14();
    FUN_00351118();
    int parse = (int)FUN_00365b6c().lo;
    if (parse == 0) {
        FUN_003509bc();
        FUN_00350efc();
        FUN_00350b84();
        parse = (int)FUN_00365b6c().lo;
        if (parse == 0) {
            FUN_00351494();
            FUN_000a68c4(c);
            FUN_0035133c();
            FUN_000dbd0c();
            sk_word16_t pair = FUN_00350618();
            uint64_t t = FUN_00377bec(pair.lo, pair.hi, task, (uint64_t)&DAT_00611b24).lo;
            uint64_t acc = 0;
            do {
                uint64_t hi = *(uint64_t *)(base_slot() + 8);
                uint64_t lo2 = FUN_0034c094(*(uint64_t *)base_slot() & 0xffffffffffff).lo;
                if (hi != 0) {
                    FUN_003a25d4(hi);
                    *(uint64_t *)base_slot() = lo2;
                    *(uint64_t *)(base_slot() + 8) = 0;
                }
            } while (0);
            FUN_00351dd8(acc, t);
            goto done_dispatch;
        }
        FUN_002a4c98(0, 0, 0, 0);
    }
    else {
        thunk_FUN_002acbb8(0, 0);
    }
    FUN_003a25d4(0);
done_dispatch:
    FUN_0008e500(0);
}

/* FUN_002a782c @ 0x002a782c   (est. sk_swift_string_append)
 * Ghidra: ulong FUN_002a782c(undefined8 param_1, undefined8 param_2, ulong param_3, ulong param_4)
 * Appends a second String (hi, lo) onto the first (param_1, param_2)
 * producing a new String whose storage pair is returned. The standard Swift
 * small-string / grown-string logic is used: if the current string is a
 * grown (indirect) buffer it re-enters through FUN_002a6900; for the
 * small-string forms it allocates a contiguous buffer (FUN_002ab8ac), copies
 * both parts (FUN_00209928 / FUN_002093d4 / FUN_001d95f4), merges, and
 * returns the packed {lo,hi} result word. On a nil canonical slot it raises
 * the "unexpectedly found nil while unwrapping" fatal.
 * Confidence: medium
 * Notes: Swift String append; SK_FATAL 0x1c2 (Swift.String). */
uint64_t sk_swift_string_append(uint64_t p1, uint64_t p2, uint64_t hi, uint64_t lo)
{
    uint64_t *slot = (uint64_t *)(uintptr_t)base_slot();
    uint64_t sLo = slot[0];
    uint64_t sHi = slot[1];
    if ((((sLo & (sHi ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0) ||
        ((FUN_003a261c(sHi & 0xfffffffffffffff).lo & 1) == 0)) {
        uint64_t hw = 0, lw = 0xe000000000000000;
        sk_word16_t d = FUN_002a49d4(sLo, sHi);
        uint64_t len = d.lo;
        if ((d.b[4] & 0xff) != 1 && 0xf < len) {
            sk_word16_t t2 = FUN_002a4a2c();
            if ((t2.b[4] & 0xff) == 1 || t2.lo < len) {
                FUN_002a4ab4(len);
            }
        }
        sk_word16_t r = FUN_002ab8ac(0xf, p1, sLo, sHi, 0xd2, 0x50);
        FUN_003a25e0(sHi, 2);
        uint64_t v = FUN_00209928(r.lo, r.hi, sLo, sHi).lo;
        FUN_003a25d4(sHi);
        sk_word16_t m = FUN_002a2f60(v, 1);
        uint64_t mlen = m.hi;
        if (mlen != 0) {
            FUN_0036b118(v);
            uint64_t e = lw;
            sk_word16_t t3 = FUN_001e3f70(hw, lw, m.lo, mlen);
            uint64_t th = t3.hi;
            FUN_003a25d4(mlen);
            FUN_003a25d4(e);
            uint64_t w2 = t3.lo & 0xffffffffffff;
            if ((th & 0x2000000000000000) != 0) {
                w2 = th >> 0x38 & 0xf;
            }
            uint64_t v2 = FUN_002093d4(hi, lo).lo;
            sk_word16_t m2 = FUN_002a2f60(v2, 1);
            uint64_t mlen2 = m2.hi;
            if (mlen2 != 0) {
                FUN_0036b118(v2);
                uint64_t l8 = mlen2;
                sk_word16_t t4 = FUN_001e3f70(t3.lo, th, m2.lo, mlen2);
                uint64_t th2 = t4.hi;
                FUN_003a25d4(mlen2);
                FUN_003a25d4(th);
                uint64_t v3 = sHi;
                sk_word16_t d2 = FUN_001d95f4(p2, sLo, sHi);
                thunk_FUN_0036b270(th2);
                FUN_003a25d4(sHi);
                uint64_t v4 = FUN_00209928(d2.lo, d2.hi, v3, l8).lo;
                FUN_003a25d4(l8);
                sk_word16_t m3 = FUN_002a2f60(v4, 1);
                uint64_t mlen3 = m3.hi;
                if (mlen3 != 0) {
                    FUN_003a25d4(th2);
                    FUN_0036b118(v4);
                    sk_word16_t t5 = FUN_001e3f70(t4.lo, th2, m3.lo, mlen3);
                    FUN_003a25d4(sHi);
                    FUN_003a25d4(mlen3);
                    FUN_003a25d4(th2);
                    slot[0] = t5.lo;
                    slot[1] = t5.hi;
                    return w2;
                }
            }
        }
        SK_FATAL(0x1c2, (unsigned long)&s_Unexpectedly_found_nil_while_unw_005cd7d0, 0x39,
                 (unsigned long)&s_Swift_String_swift_005ce680, 0x12);
    }
    if ((lo >> 0x3c & 1) != 0) {
        return FUN_002a6900(p1, p2, hi, lo, (uint64_t)&LAB_0027ccec, 0).lo;
    }
    if ((lo >> 0x3d & 1) != 0) {
        uint64_t lw = lo & 0xffffffffffffff;
        uint64_t hw = hi;
        return FUN_002a66f0(p1, p2, (uint64_t)&hw, lo >> 0x38 & 0xf, 0).lo;
    }
    sk_word16_t st;
    if ((hi >> 0x3c & 1) == 0) {
        st = FUN_002a9ba8(hi, lo);
    }
    else {
        st.hi = hi & 0xffffffffffff;
        st.lo = (lo & 0xfffffffffffffff) + 0x20;
    }
    return FUN_002a66f0(p1, p2, st.lo, st.hi, 0).lo;
}

/* FUN_002a7c00 @ 0x002a7c00   (est. sk_swift_string_append_empty)
 * Ghidra: ulong FUN_002a7c00(undefined8 param_1, undefined8 param_2)
 * Append variant that prepends a fixed empty/sentinel String storage
 * (0 / 0xe000000000000000) rather than a second caller string; otherwise
 * identical to sk_swift_string_append: allocates, copies, merges, returns
 * the packed pair word. On the grown-buffer form re-enters via
 * FUN_002a6a18.
 * Confidence: medium
 * Notes: Swift String prepend-empty; SK_FATAL 0x1c2 on nil. */
uint64_t sk_swift_string_append_empty(uint64_t p1, uint64_t p2)
{
    uint64_t *slot = (uint64_t *)(uintptr_t)base_slot();
    uint64_t sLo = slot[0];
    uint64_t sHi = slot[1];
    if ((((sLo & (sHi ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0) &&
        ((FUN_003a261c(sHi & 0xfffffffffffffff).lo & 1) != 0)) {
        return FUN_002a6a18(p1, p2, (uint64_t)&LAB_0027ccec, 0).lo;
    }
    sk_word16_t d = FUN_002a49d4(sLo, sHi);
    uint64_t len = d.lo;
    if ((d.b[4] & 0xff) != 1 && 0xf < len) {
        sk_word16_t t2 = FUN_002a4a2c();
        if ((t2.b[4] & 0xff) == 1 || t2.lo < len) {
            FUN_002a4ab4(len);
        }
    }
    sk_word16_t r = FUN_002ab8ac(0xf, p1, sLo, sHi, 0xd2, 0x50);
    FUN_003a25e0(sHi, 2);
    uint64_t v = FUN_00209928(r.lo, r.hi, sLo, sHi).lo;
    FUN_003a25d4(sHi);
    sk_word16_t m = FUN_002a2f60(v, 1);
    uint64_t mlen = m.hi;
    if (mlen != 0) {
        FUN_0036b118(v);
        sk_word16_t t3 = FUN_001e3f70(0, 0xe000000000000000, m.lo, mlen);
        uint64_t th = t3.hi;
        FUN_003a25d4(mlen);
        FUN_003a25d4(0xe000000000000000);
        uint64_t w2 = t3.lo & 0xffffffffffff;
        if ((th & 0x2000000000000000) != 0) {
            w2 = th >> 0x38 & 0xf;
        }
        FUN_0018de98(0, 0, 0);
        sk_word16_t m2 = FUN_002a2f60((uint64_t)&DAT_00657778, 1);
        uint64_t mlen2 = m2.hi;
        if (mlen2 != 0) {
            FUN_0036b118((uint64_t)&DAT_00657778);
            uint64_t l8 = mlen2;
            sk_word16_t t4 = FUN_001e3f70(t3.lo, th, m2.lo, mlen2);
            uint64_t th2 = t4.hi;
            FUN_003a25d4(mlen2);
            FUN_003a25d4(th);
            uint64_t v3 = sHi;
            sk_word16_t d2 = FUN_001d95f4(p2, sLo, sHi);
            thunk_FUN_0036b270(th2);
            FUN_003a25d4(sHi);
            uint64_t v4 = FUN_00209928(d2.lo, d2.hi, v3, l8).lo;
            FUN_003a25d4(l8);
            sk_word16_t m3 = FUN_002a2f60(v4, 1);
            uint64_t mlen3 = m3.hi;
            if (mlen3 != 0) {
                FUN_003a25d4(th2);
                FUN_0036b118(v4);
                sk_word16_t t5 = FUN_001e3f70(t4.lo, th2, m3.lo, mlen3);
                FUN_003a25d4(sHi);
                FUN_003a25d4(mlen3);
                FUN_003a25d4(th2);
                slot[0] = t5.lo;
                slot[1] = t5.hi;
                return w2;
            }
        }
    }
    SK_FATAL(0x1c2, (unsigned long)&s_Unexpectedly_found_nil_while_unw_005cd7d0, 0x39,
             (unsigned long)&s_Swift_String_swift_005ce680, 0x12);
}

/* Per-cpu container slot base (the decompiler's *unaff_x20): a pointer to a
 * 16-byte {lo,hi} word-pair slot threaded through the Swift runtime calls. */
extern uint64_t *base_slot(void);

/* In-slice forward declarations (functions defined in this file). */
extern void sk_swift_kind_dispatch_guard(void);
extern void sk_swift_string_unicode_advance(uint64_t, uint64_t, uint64_t);
extern void sk_swift_obj_service_dispatch(uint64_t, uint64_t, uint64_t);
extern uint64_t sk_swift_string_append(uint64_t, uint64_t, uint64_t, uint64_t);
extern uint64_t sk_swift_string_append_empty(uint64_t, uint64_t);

/* FUN_002a7f58 @ 0x002a7f58   (est. sk_swift_substring_slice)
 * Ghidra: undefined1 [16] FUN_002a7f58(ulong param_1, ulong param_2, undefined8 param_3)
 * Computes a Substring {base,length} pair for the UTF-8 region [lo, hi) of a
 * String storage pair in the per-cpu slot. Handles the grown/indirect buffer
 * via FUN_002a8f40 (validating through FUN_0021bf60 against the canonical
 * bounds table); for small strings it allocates, copies, merges, and returns
 * the packed 16-byte pair. Traps on arithmetic overflow and on nil.
 * Confidence: medium
 * Notes: Swift Substring slice; SW_BREAK at 0x2a8270/4; SK_FATAL 0x1c2. */
sk_word16_t sk_swift_substring_slice(uint64_t lo, uint64_t hi, uint64_t p3)
{
    uint64_t *slot = (uint64_t *)(uintptr_t)base_slot();
    uint64_t sLo = slot[0];
    uint64_t sHi = slot[1];
    if ((((sLo & (sHi ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0) &&
        ((FUN_003a261c(sHi & 0xfffffffffffffff).lo & 1) != 0)) {
        uint64_t base = FUN_0021bf60(0, 0, 0, 1, 0, 1, p3, (uint64_t)&LAB_0027ccec, 0).lo;
        uint64_t start = base + (lo >> 0x10);
        if (base > (lo >> 0x10)) {
            SW_BREAK(0x2a8270);
        }
        uint64_t lw = sLo & 0xffffffffffff;
        if ((sHi & 0x2000000000000000) != 0) {
            lw = sHi >> 0x38 & 0xf;
        }
        uint64_t endOff = lw - (hi >> 0x10);
        uint64_t total = start + endOff;
        if (total < start) {
            SW_BREAK(0x2a8274);
        }
        uint64_t off = lo >> 0x10;
        if (0xf < total) {
            sk_word16_t t = FUN_002a4a2c();
            if ((t.b[4] & 0xff) == 1 || t.lo < total) {
                FUN_002a4ab4(total);
            }
        }
        uint64_t curHi = slot[1];
        FUN_002a8f40(off, hi >> 0x10, p3, (uint64_t)&LAB_0027ccec, 0, base);
        slot[0] = *(uint64_t *)((curHi & 0xfffffffffffffff) + 0x18);
        sk_word16_t out;
        out.hi = total;
        out.lo = off;
        return out;
    }
    sk_word16_t d = FUN_002a49d4(sLo, sHi);
    uint64_t len = d.lo;
    if ((d.b[4] & 0xff) != 1 && 0xf < len) {
        sk_word16_t t = FUN_002a4a2c();
        if ((t.b[4] & 0xff) == 1 || t.lo < len) {
            FUN_002a4ab4(len);
        }
    }
    sk_word16_t r = FUN_002ab8ac(0xf, lo, sLo, sHi, 0xd2, 0x50);
    FUN_003a25e0(sHi, 2);
    uint64_t v = FUN_00209928(r.lo, r.hi, sLo, sHi).lo;
    sk_word16_t m = FUN_002a2f60(v, 1);
    uint64_t mlen = m.hi;
    if (mlen == 0) {
        SK_FATAL(0x1c2, (unsigned long)&s_Unexpectedly_found_nil_while_unw_005cd7d0, 0x39,
                 (unsigned long)&s_Swift_String_swift_005ce680, 0x12);
    }
    FUN_0036b118(v);
    FUN_003a25d4(sHi);
    uint64_t l8 = mlen;
    sk_word16_t t2 = FUN_001e3f70(0, 0xe000000000000000, m.lo, mlen);
    uint64_t th = t2.hi;
    uint64_t tv = t2.lo;
    FUN_003a25d4(mlen);
    FUN_003a25d4(0xe000000000000000);
    FUN_0029c18c(p3);
    uint64_t v3 = sHi;
    sk_word16_t d2 = FUN_001d95f4(hi, sLo, sHi);
    FUN_003a25d4(sHi);
    uint64_t v4 = FUN_00209928(d2.lo, d2.hi, v3, l8).lo;
    sk_word16_t m2 = FUN_002a2f60(v4, 1);
    uint64_t mlen2 = m2.hi;
    if (mlen2 != 0) {
        FUN_0036b118(v4);
        FUN_003a25d4(l8);
        uint64_t w2 = tv & 0xffffffffffff;
        if ((th & 0x2000000000000000) != 0) {
            w2 = th >> 0x38 & 0xf;
        }
        uint64_t pl = tv & 0xffffffffffff;
        if ((th & 0x2000000000000000) != 0) {
            pl = th >> 0x38 & 0xf;
        }
        sk_word16_t t3 = FUN_001e3f70(tv, th, m2.lo, mlen2);
        FUN_003a25d4(sHi);
        FUN_003a25d4(mlen2);
        FUN_003a25d4(th);
        slot[0] = t3.lo;
        slot[1] = t3.hi;
        sk_word16_t out;
        out.hi = pl;
        out.lo = w2;
        return out;
    }
    SK_FATAL(0x1c2, (unsigned long)&s_Unexpectedly_found_nil_while_unw_005cd7d0, 0x39,
             (unsigned long)&s_Swift_String_swift_005ce680, 0x12);
}

/* FUN_002a82cc @ 0x002a82cc   (est. sk_swift_string_literal_build)
 * Ghidra: void FUN_002a82cc(undefined8 param_1 .. param_5)
 * Builds a String from a static literal / descriptor argument: saves the
 * frame, walks a set of Swift method-table closures (each invoked through
 * DAT_00658c00), validates the two-phase parse via FUN_00365b6c, and
 * publishes the resulting string word. The literal is drawn from a fixed
 * kind word (0x674148) and the produced pair merged into the per-cpu slot.
 * Confidence: medium
 * Notes: register-threaded Swift string literal construction. */
void sk_swift_string_literal_build(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
    uint64_t *slot = (uint64_t *)(uintptr_t)base_slot();
    sk_word16_t f = FUN_0008e518();
    uint64_t u11 = f.hi;
    uint64_t u4 = f.lo;
    uint64_t l30 = 0, l28 = 0, l18 = 0;
    FUN_00351bec(p5);
    FUN_00350318();
    FUN_00319320();
    uint64_t u5 = FUN_000a6f88().lo;
    FUN_0007c1a4();
    DAT_00658c00();
    sk_word16_t g = FUN_0034aee4();
    FUN_0035298c(g.lo, g.hi, 0x674148);
    uint64_t u6 = FUN_00319338().lo;
    FUN_0034e2e4(u6, u6);
    FUN_0031be18(0xff);
    FUN_00353f68();
    FUN_00319320();
    u6 = FUN_000a6f88().lo;
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034cff4();
    FUN_0034998c();
    DAT_00658c00();
    FUN_00348a34();
    DAT_00658c00();
    FUN_0034c2d8();
    uint64_t u9 = slot[1];
    if ((((*slot & (u9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0) ||
        (FUN_003a261c(u9 & 0xfffffffffffffff).lo == 0)) {
        l30 = 0; l28 = 0xe000000000000000;
        FUN_00350a34();
        FUN_002a49d4();
        uint64_t u7 = FUN_00351db4().lo;
        if (0xf < (long)u7) {
            sk_word16_t t = FUN_002a4a2c();
            uint64_t l8 = FUN_00351db4().lo;
            if (l8 < (long)u7) {
                FUN_002a4ab4(u7);
            }
        }
        FUN_00354300(0xf, u4);
        FUN_00354404();
        FUN_002ab8ac();
        FUN_00351a50();
        FUN_003a25e0(u9, 2);
        FUN_0009461c();
        FUN_00354300();
        uint64_t u7b = FUN_00209928().lo;
        thunk_FUN_002a2f60(u7b, 1);
        if (1 != 0) {
            FUN_00350df4();
            FUN_0036b118();
            FUN_003a25d4(u9);
            uint64_t u1 = l28;
            FUN_00350c68(l30);
            FUN_001e3f70();
            FUN_00354a00();
            FUN_003a25d4(0);
            FUN_003a25d4(u1);
            l30 = u7b;
            l28 = u7;
            FUN_0035136c(p3);
            FUN_0029c2bc();
            u1 = l28;
            uint64_t u13 = l30;
            FUN_00351ab0(u11);
            FUN_001d95f4();
            FUN_003a25d4(u9);
            sk_word16_t g2 = FUN_00350a04();
            uint64_t u10 = FUN_00209928(g2.lo, g2.hi, u10, 0).lo;
            thunk_FUN_002a2f60(u10, 1);
            if (1 != 0) {
                FUN_0036b118(u10);
                FUN_003a25d4(0);
                FUN_0034ff88(u7b & 0xffffffffffff);
                FUN_001e3f70();
                FUN_00354858();
                FUN_003a25d4(u9);
                FUN_003a25d4(0);
                FUN_003a25d4(u1);
                slot[0] = u7b;
                slot[1] = u13;
                goto done_literal;
            }
        }
        FUN_0034a2f8((uint64_t)&s_Fatal_error_005accd0);
        FUN_001afe4c();
    }
    FUN_00350ed0();
    FUN_003505c4((uint64_t)&l30);
    if (FUN_00365b6c().lo == 0) {
        FUN_00350ed0();
        uint64_t l8 = 0x675de8;
        FUN_003516f0((uint64_t)&l30);
        uint64_t u9 = FUN_00365b6c().lo;
        if ((u9 & 1) == 0) goto do_merge_literal;
        if ((l18 >> 0x3c & 1) != 0) {
            FUN_003a25d4(l18);
            thunk_FUN_00200b38(p4);
            FUN_00216b88((uint64_t)&LAB_0027ccec, 0, u5, 0x674148, 0x66cbe0, 0x66cf30);
            FUN_00359478();
            FUN_003505e8();
            uint64_t l38 = p5;
            uint64_t u10 = FUN_0034a180().lo;
            u10 = FUN_00376820(u10, 0, (uint64_t)&l38).lo;
            uint64_t s40 = FUN_003267b4().lo;
            uint64_t l48 = u10;
            uint64_t l50 = FUN_00376820((uint64_t)&DAT_004e9a4c, 0, (uint64_t)&l48).lo;
            u10 = FUN_0034e314().lo;
            FUN_00376820(u10, u6, (uint64_t)&l50);
            FUN_003511cc(u4, u11);
            FUN_002a6efc();
            FUN_00351a50();
            FUN_00353e08();
            FUN_000b4390();
            goto done_literal;
        }
        if ((l28 >> 0x3d & 1) == 0) {
            if ((l30 >> 0x3c & 1) == 0) {
                FUN_002a9ba8(l30, l28);
                goto do_merge_literal;
            }
            FUN_003573e8(l28 & 0xfffffffffffffff);
        }
        else {
            l30 = FUN_00359f54(l30).lo;
            l28 = 0;
        }
do_merge_literal:
        FUN_0009461c();
        FUN_003520dc();
        sk_word16_t r = FUN_0028e8c0();
        if (r.lo < 0 || l8 < r.hi) {
            FUN_003481fc();
            FUN_001afe4c();
        }
        FUN_00348e48();
        FUN_001e4cbc();
        FUN_00351790();
    }
    FUN_002a66f0(u4, u11);
    FUN_0034dec4();
    FUN_003a25d4();
done_literal:
    sk_word16_t out = FUN_0009461c();
    FUN_0008e500(out.lo, out.hi, 0);
}

/* FUN_002a8870 @ 0x002a8870   (est. sk_swift_grow_check)
 * Ghidra: void FUN_002a8870(long param_1)
 * Grow-reserve helper: if the requested size exceeds the small-string inline
 * threshold (0x10) and the current container capacity is insufficient, it
 * triggers a reallocation (FUN_002a4ab4). Otherwise no-op.
 * Confidence: medium
 * Notes: Swift grow check. */
void sk_swift_grow_check(uint64_t size)
{
    if (0xf < size) {
        FUN_002a4a2c();
        uint64_t cap = FUN_00351db4().lo;
        if (cap < size) {
            FUN_002a4ab4(size);
        }
    }
}

/* FUN_002a88bc @ 0x002a88bc   (est. sk_swift_utf8_append_validated)
 * Ghidra: void FUN_002a88bc(void)
 * Appends a validated UTF-8 run into the per-cpu String builder at
 * unaff_x20+0x20. Computes the destination extent via FUN_002ad62c, tracks
 * the overflow bit from the builder header (+0x18), and if the grown-header
 * sign bit is set consults FUN_002a200c for the reserve size. Finalizes with
 * FUN_002a2bb0 on the packed offset, trapping on index overflow.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2a8950/4; Swift UTF-8 append. */
void sk_swift_utf8_append_validated(void)
{
    uint64_t *b = (uint64_t *)base_slot();
    sk_word16_t v = FUN_00355bb8();
    uint64_t l4 = v.lo;
    uint64_t l1 = (uint64_t)(uintptr_t)b + 0x20 + l4;
    uint64_t l5 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + v.hi, l1 + 0).lo;
    FUN_003577b4();
    sk_word16_t g = FUN_00350524();
    FUN_0035ab20(g.lo, g.hi, l1);
    uint64_t u3;
    if (*(int64_t *)((uintptr_t)b + 0x18) < 0) {
        FUN_00350524();
        u3 = FUN_002a200c().lo;
    }
    else {
        u3 = 0;
    }
    if (l4 + 0 > l4) {
        SW_BREAK(0x2a8950);
    }
    if (l4 + 0 + l5 < l4 + 0) {
        SW_BREAK(0x2a8954);
    }
    FUN_002a2bb0(l4 + 0 + l5, u3 & 1);
}

/* FUN_002a8954 @ 0x002a8954   (est. sk_swift_utf8_append_ascii_loop)
 * Ghidra: void FUN_002a8954(long param_1, long param_2, ulong param_3, ulong param_4, ...)
 * UTF-8 ASCII append loop: computes the destination extent (FUN_002ad62c),
 * releases the two incoming String references, then repeatedly fetches
 * characters from FUN_002171a8 until the end marker (0x100 in bits 8..15),
 * storing each into the builder and tracking overflow. Validates the
 * resulting range via FUN_00344e54 and finalizes with FUN_002a2bb0.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2a8a2c/84/88; Swift ASCII append. */
void sk_swift_utf8_append_ascii_loop(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6, uint64_t p7)
{
    uint64_t *b = (uint64_t *)base_slot();
    uint64_t l4 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + p2, (uint64_t)(uintptr_t)b + 0x20 + p1 + p7).lo;
    uint64_t u6 = *(uint64_t *)((uintptr_t)b + 0x18) >> 0x3f;
    uint64_t l5 = 0;
    thunk_FUN_0036b270(p4);
    FUN_0036b270(p6);
    while (true) {
        uint64_t c = FUN_002171a8().lo;
        if ((c & 0xff00) == 0x100) break;
        u6 = (uint64_t)((uint32_t)((int32_t)(int8_t)c < 0x80000000) & (uint32_t)u6);
        *(uint8_t *)((uintptr_t)b + p1 + l5 + 0x20) = (uint8_t)c;
        l5 = l5 + 1;
    }
    FUN_00344e54((uint64_t)&p3, 0x657730, (uint64_t)&DAT_004f2240);
    if (p1 + p7 < p1) {
        SW_BREAK(0x2a8a84);
    }
    if (p1 + p7 + l4 < p1 + p7) {
        SW_BREAK(0x2a8a88);
    }
    FUN_002a2bb0(p1 + p7 + l4, u6);
}

/* FUN_002a8a88 @ 0x002a8a88   (est. sk_swift_utf8_append_multibyte_loop)
 * Ghidra: void FUN_002a8a88(long param_1 .. param_7)
 * UTF-8 multibyte append loop: computes the destination extent, releases the
 * incoming references, then repeatedly decodes a Unicode scalar via
 * FUN_002523d8, validates the continuation-byte count, encodes it through
 * FUN_00255324/FUN_0026bd30, and writes the encoded bytes into the builder.
 * Ends on the stream end marker and finalizes with FUN_002a2bb0.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2a8c94/98/9c/a0; Swift UTF-8 multibyte encode. */
void sk_swift_utf8_append_multibyte_loop(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6, uint64_t p7)
{
    uint64_t *b = (uint64_t *)base_slot();
    uint64_t l7 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + p2, (uint64_t)(uintptr_t)b + 0x20 + p1 + p7).lo;
    uint64_t u10 = *(uint64_t *)((uintptr_t)b + 0x18) >> 0x3f;
    uint64_t l9 = 0, l8 = 0, u12 = 0;
    bool b4 = false;
    thunk_FUN_0036b270(p4);
    FUN_0036b270(p6);
loop_top:
    if (b4) {
        while (true) {
            uint32_t u11 = (uint32_t)u12;
            if (u11 < 0x80) { if (l8 != 1) break; }
            else if (u11 < 0x800) { if (l8 != 2) break; }
            else if (u11 >> 0x10 == 0) { if (l8 != 3) break; }
            else if (l8 != 4) break;
            goto fetch_next;
        }
        uint64_t c6 = FUN_00255324(l8, u12).lo;
        uint64_t u1 = 3;
        if (0xffff < u12) { u1 = 4; }
        uint64_t u2 = 2;
        if (0x7ff < u12) { u2 = u1; }
        u1 = 1;
        if (0x7f < u12) { u1 = u2; }
        sk_word16_t g = FUN_0026bd30(0, u1);
        FUN_001d2d1c(l8, g.lo, g.hi);
        l8 = l8 + 1;
        u10 = (uint64_t)((uint32_t)((int32_t)(int8_t)c6 < 0x80000000) & (uint32_t)u10);
        *(uint8_t *)((uintptr_t)b + p1 + l9 + 0x20) = (uint8_t)c6;
        b4 = true;
        l9 = l9 + 1;
        goto loop_top;
    }
fetch_next:
    u12 = FUN_002523d8().lo;
    if ((u12 & 0xff00000000) == 0x100000000) {
        FUN_0036b118(p6);
        FUN_003a25d4(p4);
        if (p1 + p7 < p1) { SW_BREAK(0x2a8c9c); }
        if (p1 + p7 + l7 < p1 + p7) { SW_BREAK(0x2a8ca0); }
        FUN_002a2bb0(p1 + p7 + l7, u10);
        return;
    }
    l8 = 0;
    b4 = true;
    goto loop_top;
}

/* FUN_002a8ca0 @ 0x002a8ca0   (est. sk_swift_utf8_append_simple)
 * Ghidra: void FUN_002a8ca0(long param_1, long param_2, undefined8 param_3, undefined8 param_4, long param_5)
 * Simple UTF-8 append: computes the destination extent and finalizes the
 * builder with FUN_002a2bb0 using the overflow bit, trapping on index
 * overflow. A thin twin of the append family.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2a8d00/4. */
void sk_swift_utf8_append_simple(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
    uint64_t *b = (uint64_t *)base_slot();
    uint64_t l2 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + p2, (uint64_t)(uintptr_t)b + 0x20 + p1 + p5).lo;
    if (p1 + p5 < p1) { SW_BREAK(0x2a8d00); }
    if (p1 + p5 + l2 < p1 + p5) { SW_BREAK(0x2a8d04); }
    FUN_002a2bb0(p1 + p5 + l2, *(uint64_t *)((uintptr_t)b + 0x18) >> 0x3f);
}

/* FUN_002a8d04 @ 0x002a8d04   (est. sk_swift_utf8_append_params)
 * Ghidra: void FUN_002a8d04(long param_1, long param_2, undefined8 *param_3, long param_4)
 * UTF-8 append variant that reads its String operands from a 6-word
 * parameter block (param_3). Computes the extent, releases the operand
 * references, iterates FUN_002177bc until end, writes bytes, validates the
 * range, and finalizes with FUN_002a2bb0.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2a8dd0/e24/e28; Swift append from param block. */
void sk_swift_utf8_append_params(uint64_t p1, uint64_t p2, uint64_t *p3, uint64_t p4)
{
    uint64_t *b = (uint64_t *)base_slot();
    uint64_t l4 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + p2, (uint64_t)(uintptr_t)b + 0x20 + p1 + p4).lo;
    uint64_t u7 = *(uint64_t *)((uintptr_t)b + 0x18) >> 0x3f;
    uint64_t l6 = 0;
    thunk_FUN_0036b270();
    FUN_0036b270(p3[5]);
    while (true) {
        uint64_t c = FUN_002177bc().lo;
        if ((c & 0xff00) == 0x100) break;
        u7 = (uint64_t)((uint32_t)((int32_t)(int8_t)c < 0x80000000) & (uint32_t)u7);
        *(uint8_t *)((uintptr_t)b + p1 + l6 + 0x20) = (uint8_t)c;
        l6 = l6 + 1;
    }
    FUN_00344e54((uint64_t)&p3, (uint64_t)&LAB_00657690, (uint64_t)&DAT_004f2170);
    if (p1 + p4 < p1) { SW_BREAK(0x2a8e24); }
    if (p1 + p4 + l4 < p1 + p4) { SW_BREAK(0x2a8e28); }
    FUN_002a2bb0(p1 + p4 + l4, u7);
}

/* FUN_002a8e28 @ 0x002a8e28   (est. sk_swift_utf8_append_refs)
 * Ghidra: void FUN_002a8e28(long param_1, long param_2, undefined8 param_3, undefined8 param_4, undefined8 param_5, long param_6)
 * UTF-8 append twin: computes extent, releases incoming references, iterates
 * FUN_00217c60 until end, writes bytes, then releases the two operands and
 * finalizes with FUN_002a2bb0.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2a8ee8/f3c/f40. */
void sk_swift_utf8_append_refs(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6)
{
    uint64_t *b = (uint64_t *)base_slot();
    uint64_t l4 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + p2, (uint64_t)(uintptr_t)b + 0x20 + p1 + p6).lo;
    uint64_t u6 = *(uint64_t *)((uintptr_t)b + 0x18) >> 0x3f;
    uint64_t l5 = 0;
    FUN_0036b270(p3);
    FUN_0036b270(p5);
    while (true) {
        uint64_t c = FUN_00217c60().lo;
        if ((c & 0xff00) == 0x100) break;
        u6 = (uint64_t)((uint32_t)((int32_t)(int8_t)c < 0x80000000) & (uint32_t)u6);
        *(uint8_t *)((uintptr_t)b + p1 + l5 + 0x20) = (uint8_t)c;
        l5 = l5 + 1;
    }
    FUN_0036b118(p3);
    FUN_0036b118(p5);
    FUN_003a25d4(0);
    if (p1 + p6 < p1) { SW_BREAK(0x2a8f3c); }
    if (p1 + p6 + l4 < p1 + p6) { SW_BREAK(0x2a8f40); }
    FUN_002a2bb0(p1 + p6 + l4, u6);
}

/* FUN_002a8f40 @ 0x002a8f40   (est. sk_swift_utf8_unicode_scalar_encode)
 * Ghidra: void FUN_002a8f40(long param_1, long param_2, undefined4 param_3, code *param_4, undefined8 param_5, long param_6)
 * UTF-8 Unicode-scalar encoder: computes the destination extent, releases the
 * incoming reference, and repeatedly decodes scalar units from the caller
 * closure (param_4) into 16-bit units, validating continuation counts and
 * encoding each into the builder via FUN_002557b8. Runs the Swift
 * UnicodeScalar.UTF8View fatal on malformed sequences and the
 * Collection index-out-of-bounds fatal on buffer overrun.
 * Confidence: medium
 * Notes: SK_FATAL 0x1e2 (UnicodeScalar) and 0x2ca (Collection);
 *   SW_BREAK at 0x2a9194/98/9c. */
void sk_swift_utf8_unicode_scalar_encode(uint64_t p1, uint64_t p2, uint32_t p3, uint64_t p4, uint64_t p5, uint64_t p6)
{
    uint64_t *b = (uint64_t *)base_slot();
    uint64_t l1 = (uint64_t)(uintptr_t)b + 0x20 + p1;
    uint64_t l7 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + p2, l1 + p6).lo;
    uint64_t u11 = *(uint64_t *)((uintptr_t)b + 0x18) >> 0x3f;
    uint64_t u9 = 0, u12 = 0, l10 = 0;
    bool b2 = false, b4 = true;
    uint32_t local_68 = p3;
    do {
        while (b4) {
recheck:
            if (b2) {
                FUN_0036b118(p5);
                if (p1 + p6 < p1) { SW_BREAK(0x2a9198); }
                if (p1 + p6 + l7 < p1 + p6) { SW_BREAK(0x2a919c); }
                FUN_002a2bb0(p1 + p6 + l7, u11);
                return;
            }
            uint32_t local_64 = 0;
            FUN_002171a8(); /* source byte fetch via closure state */
            (*(void (*)(uint32_t *, uint32_t *))(uintptr_t)p4)(&local_64, &local_68);
            b4 = false;
            u9 = 0;
            local_68 = 0;
            u12 = (uint64_t)local_64;
            b2 = true;
        }
        uint64_t u8 = u12 >> 0x10;
        if (u12 < 0x80) {
            if (u9 == 1) goto recheck;
            if (u9 != 0) goto bad_utf8;
        }
        else {
            if (0x7ff < u12) {
                if (u8 == 0) {
                    if (u9 != 3) goto cont_check;
                }
                else if (u9 != 4) goto cont_check;
                goto recheck;
            }
            b4 = 1 < u9;
            if (u9 == 2) goto recheck;
            goto valid_byte;
        }
cont_check:
        if ((long)u9 < 0) goto bad_utf8;
        b4 = 2 < u9;
        if (u8 != 0) {
            if (3 < u9) goto bad_utf8;
        }
        if (b4) {
bad_utf8:
            SK_FATAL(0x1e2, (unsigned long)&s_Unicode_Scalar_UTF8View_index_is_005cfe40, 0x2e,
                     (unsigned long)&s_Swift_UnicodeScalar_swift_005cfe00, 0x19);
        }
valid_byte:
        uint64_t c6 = FUN_002557b8(u12, u9).lo;
        if (u12 < 0x80) {
            if (u9 != 0) goto bad_index;
        }
        else if (u12 < 0x800) {
            if (1 < u9) goto bad_index;
        }
        else if ((u8 == 0) && (u9 == 3)) goto bad_index;
        b4 = false;
        u9 = u9 + 1;
        u11 = (uint64_t)((uint32_t)((int32_t)(int8_t)c6 < 0x80000000) & (uint32_t)u11);
        *(uint8_t *)(l1 + l10) = (uint8_t)c6;
        l10 = l10 + 1;
        continue;
bad_index:
        SK_FATAL(0x2ca, (unsigned long)&s_Index_out_of_bounds_005cdab0, 0x13,
                 (unsigned long)&s_Swift_Collection_swift_005cdad0, 0x16);
    } while (true);
}

/* FUN_002a919c @ 0x002a919c   (est. sk_swift_utf8_append_wide)
 * Ghidra: void FUN_002a919c(long param_1 .. param_7)
 * UTF-8 append twin for wide (16-bit unit) sources: computes extent,
 * releases references, iterates FUN_00217ea0, writes bytes, releases
 * operands, finalizes with FUN_002a2bb0.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2a9260/b4/b8. */
void sk_swift_utf8_append_wide(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6, uint64_t p7)
{
    uint64_t *b = (uint64_t *)base_slot();
    uint64_t l4 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + p2, (uint64_t)(uintptr_t)b + 0x20 + p1 + p7).lo;
    uint64_t u6 = *(uint64_t *)((uintptr_t)b + 0x18) >> 0x3f;
    uint64_t l5 = 0;
    thunk_FUN_0036b270(p4);
    FUN_0036b270(p6);
    while (true) {
        uint64_t c = FUN_00217ea0().lo;
        if ((c & 0xff00) == 0x100) break;
        u6 = (uint64_t)((uint32_t)((int32_t)(int8_t)c < 0x80000000) & (uint32_t)u6);
        *(uint8_t *)((uintptr_t)b + p1 + l5 + 0x20) = (uint8_t)c;
        l5 = l5 + 1;
    }
    FUN_003a25d4(p4);
    FUN_0036b118(p6);
    FUN_003a25d4(0);
    if (p1 + p7 < p1) { SW_BREAK(0x2a92b4); }
    if (p1 + p7 + l4 < p1 + p7) { SW_BREAK(0x2a92b8); }
    FUN_002a2bb0(p1 + p7 + l4, u6);
}

/* FUN_002a92b8 @ 0x002a92b8   (est. sk_swift_utf8_append_ascii)
 * Ghidra: void FUN_002a92b8(long param_1, long param_2, undefined8 param_3, undefined8 param_4, long param_5)
 * ASCII UTF-8 append twin: computes extent, releases the single reference,
 * iterates FUN_00218068, writes bytes, releases the operand, finalizes.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2a9368/b4/b8. */
void sk_swift_utf8_append_ascii(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
    uint64_t *b = (uint64_t *)base_slot();
    uint64_t l4 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + p2, (uint64_t)(uintptr_t)b + 0x20 + p1 + p5).lo;
    uint64_t u6 = *(uint64_t *)((uintptr_t)b + 0x18) >> 0x3f;
    uint64_t l5 = 0;
    FUN_0036b270(p4);
    while (true) {
        uint64_t c = FUN_00218068().lo;
        if ((c & 0xff00) == 0x100) break;
        u6 = (uint64_t)((uint32_t)((int32_t)(int8_t)c < 0x80000000) & (uint32_t)u6);
        *(uint8_t *)((uintptr_t)b + p1 + l5 + 0x20) = (uint8_t)c;
        l5 = l5 + 1;
    }
    FUN_0036b118(p4);
    FUN_003a25d4(0);
    if (p1 + p5 < p1) { SW_BREAK(0x2a93b4); }
    if (p1 + p5 + l4 < p1 + p5) { SW_BREAK(0x2a93b8); }
    FUN_002a2bb0(p1 + p5 + l4, u6);
}

/* FUN_002a93b8 @ 0x002a93b8   (est. sk_swift_utf8_append_builder)
 * Ghidra: void FUN_002a93b8(void)
 * String-builder UTF-8 append entry: saves the frame, resolves the builder
 * base (FUN_00377824), computes the destination extent, then iterates a
 * byte-producing closure (FUN_00350560) until the end marker, storing each
 * byte into the builder and tracking overflow. Validates the final range and
 * restores the frame, trapping on index overflow.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2a9558/b0/b4; frame restore via FUN_0008e500. */
void sk_swift_utf8_append_builder(void)
{
    uint64_t *b = (uint64_t *)base_slot();
    sk_word16_t f = FUN_0008e518();
    uint64_t l2 = f.lo;
    FUN_0007c028();
    DAT_00658c00();
    FUN_003493ac();
    FUN_00352ee4();
    FUN_00349444();
    FUN_0035256c();
    FUN_00377824();
    FUN_00348d64();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034aee4();
    uint64_t l3 = FUN_002ad62c((uint64_t)(uintptr_t)b + 0x20 + f.hi, (uint64_t)(uintptr_t)b + 0x20 + l2 + 0).lo;
    uint64_t u5 = *(uint64_t *)((uintptr_t)b + 0x18) >> 0x3f;
    FUN_000a68c4();
    FUN_00350b24();
    FUN_003510dc();
    FUN_00356774();
    FUN_00350ad0();
    FUN_00377bec();
    uint64_t l6 = 0;
    uint8_t local_2;
    while (true) {
        FUN_00350560((uint64_t)&local_2);
        if (local_2 == 0x01) break;
        u5 = (uint64_t)((uint32_t)(local_2 != 0xffffffff && !((uint32_t)local_2 + 1 > 0xffffffff)) & (uint32_t)u5);
        *(uint8_t *)((uintptr_t)b + l2 + l6 + 0x20) = local_2;
        l6 = l6 + 1;
    }
    FUN_000e72b0(0);
    if (l2 + 0 < l2) { SW_BREAK(0x2a95b0); }
    if (l2 + 0 + l3 < l2 + 0) { SW_BREAK(0x2a95b4); }
    FUN_002a2bb0(l2 + 0 + l3, u5);
    FUN_0008e500(0);
}

/* FUN_002a95b4 @ 0x002a95b4   (est. sk_swift_string_advance_end)
 * Ghidra: void FUN_002a95b4(void)
 * Advances a String index to the end of the current Unicode scalar,
 * distinguishing small-string from grown/indirect String forms. Resolves the
 * encoded-unit width, handles the indirect (grown) buffer via FUN_00351b60 /
 * FUN_0001da84 and the inline forms, skipping a trailing surrogate / combining
 * marker, and packs the result into *unaff_x21 (or *unaff_x19 for the
 * alternate slot). Traps on bounds violations.
 * Confidence: medium
 * Notes: register-threaded String index advance; complex small-string
 *   dispatch (Swift String.Index). */
void sk_swift_string_advance_end(void)
{
    uint64_t *x21 = (uint64_t *)base_slot();
    uint64_t *x19 = x21 + 2;
    sk_word16_t f;
    (void)f;
    FUN_000b4594();
    FUN_00350a10();
    uint64_t u5 = FUN_00353e50().lo;
    uint64_t u12 = x21[1];
    uint64_t u14 = x21[0];
    if (((u12 >> 0x3c & 1) == 0) || ((u14 >> 0x3b & 1) != 0)) {
        /* ASCII / small-string advance */
        uint64_t cur = *(uint64_t *)base_slot();
        uint64_t u13 = cur >> 0x10;
        uint64_t u15 = *x19;
        uint64_t u11 = u15 >> 0x10;
        uint64_t l7 = (0 - 0) + (u13 - (u5 >> 0x10));
        uint64_t u1 = l7 + (*x19 >> 0x10);
        uint64_t u14b = u15 >> 8 & 0x3f;
        u12 = u11;
        if (u14b != 0) {
            u12 = u14b + u11;
        }
        if (u13 <= u12) {
            uint64_t l6;
            if (u11 == u1) {
                l6 = 0;
            }
            else {
                /* resolve the next scalar boundary */
                uint64_t sv = x21[0];
                uint64_t sh = x21[1];
                if ((sh >> 0x3c & 1) == 0) {
                    if ((sh >> 0x3d & 1) == 0) {
                        uint64_t bptr;
                        if ((sv >> 0x3c & 1) == 0) {
                            FUN_00350470();
                            bptr = FUN_002a9ba8().lo;
                        }
                        else {
                            bptr = (sh & 0xfffffffffffffff) + 0x20;
                        }
                        if (u11 + 1 != FUN_002a9ba8().hi) {
                            if (bptr == 0) {
                                FUN_00347f2c();
                                FUN_001afe4c();
                            }
                            uint16_t w = *(uint16_t *)(bptr + u11);
                            if ((w == 0xa0d) || ((w & 0x8080) != 0)) goto wide_scalar;
                        }
                    }
                    else {
                        l6 = 1;
                        goto pack6;
                    }
                    l6 = 1;
                    goto pack6;
                }
wide_scalar:
                FUN_003513b4(u11);
                l6 = FUN_002c6d00().lo;
                if (l6 < 0x40) goto pack6;
            }
pack6:
            {
                uint64_t u14c = 0;
                if (((uint32_t)(u15 >> 1) & 1) != 0) {
                    uint64_t u11b = FUN_0029ead8(5, x21[0], x21[1]).lo;
                    if (u11b & 1) u14c = 2;
                }
                *x21 = u14c | 5;
            }
        }
    }
    else {
        /* grown / indirect String form */
        uint64_t u13 = x21[0];
        uint64_t u11 = u13;
        if ((u13 & 0xc) == 4) {
            FUN_00351b60(u13);
            u11 = FUN_0001da84().lo;
        }
        FUN_0034d6c8(x21[1] & 0xffffffffffff, u5, u11);
        FUN_00351dcc(0xf);
        uint64_t l7 = FUN_002b15d0().lo;
        uint64_t u5b = *x19;
        if ((u13 & 0xc) == 4) {
            FUN_00351b60(u13);
            u13 = FUN_0001da84().lo;
        }
        if ((u5b & 0xc) == 4) {
            sk_word16_t t = FUN_0035145c();
            u5b = FUN_0001da84(t.lo, t.hi, u12).lo;
        }
        FUN_00351dcc(u13, u5b);
        uint64_t l6 = FUN_002b15d0().lo;
        if ((u5b & 0xc) == 4) {
            sk_word16_t t = FUN_00350ea4();
            u5b = FUN_0001da84(t.lo, t.hi, u12).lo;
        }
        FUN_000a6e14();
        FUN_00351dcc();
        uint64_t l8 = FUN_002b15d0().lo;
        uint64_t l9 = l6 + 0;
        l6 = l9 - l8;
        uint64_t lVar1;
        if (0 == 0) {
            lVar1 = 0;
        }
        else {
            lVar1 = 0;
        }
        *x19 = (lVar1 << 8) | 5;
    }
    FUN_000b45b0(0);
}

/* FUN_002a999c @ 0x002a999c   (est. sk_swift_string_scalar_count)
 * Ghidra: void FUN_002a999c(void)
 * Computes / validates the Unicode-scalar count for a String: reads the
 * per-cpu bounds, resolves the scalar/character counts via the Swift runtime
 * primitives, and dispatches either the small-string path (FUN_00357c44)
 * or the grown-buffer path (FUN_002b15d0). Traps on out-of-range.
 * Confidence: medium
 * Notes: register-threaded scalar count; SK_FATAL on bounds violation. */
void sk_swift_string_scalar_count(void)
{
    FUN_00357ca0();
    FUN_00349fcc();
    FUN_00357794();
    uint64_t u1 = FUN_0034a3b0().lo;
    if (u1 & 1) u1 = 1;
    FUN_00353590(u1);
    FUN_00359a30();
    FUN_0034ba28();
    uint64_t x22 = FUN_0001da84().lo;
    if ((*(uint64_t *)base_slot() >> 0x3c & 1) == 0) {
        FUN_00357c44((uint64_t)((*(uint64_t *)(base_slot()+1) >> 0x10) - (x22 >> 0x10)), 0);
        return;
    }
    FUN_0034a274();
    FUN_0008412c();
    FUN_00357c44();
    FUN_002b15d0();
}

/* FUN_002a9a88 @ 0x002a9a88   (est. sk_swift_obj_release_pair)
 * Ghidra: void FUN_002a9a88(void)
 * Releases a {lo,hi} object pair: resolves the current object from
 * FUN_0034b430 and decrements the reference on the combined word
 * (lo|hi), then frees the header via FUN_0036b118.
 * Confidence: medium
 * Notes: Swift object release pair. */
void sk_swift_obj_release_pair(void)
{
    sk_word16_t v = FUN_0034b430();
    thunk_FUN_0036b270(v.hi | v.lo);
    FUN_0036b118();
}

/* FUN_002a9b7c @ 0x002a9b7c   (est. sk_swift_obj_release_single)
 * Ghidra: void FUN_002a9b7c(void)
 * Single object release: tails into the shared release primitive.
 * Confidence: medium */
void sk_swift_obj_release_single(void)
{
    FUN_0035ab14();
}

/* FUN_002a9b9c @ 0x002a9b9c   (est. sk_swift_string_storage_base)
 * Ghidra: undefined8 FUN_002a9b9c(undefined8 param_1, ulong param_2)
 * Returns the String storage base pointer: the address at +0x18 of the
 * buffer described by `param_2`'s low 52 bits.
 * Confidence: medium
 * Notes: Swift String storage base fetch. */
sk_word16_t sk_swift_string_storage_base(uint64_t a, uint64_t b)
{
    sk_word16_t r;
    r.lo = *(uint64_t *)((b & 0xfffffffffffffff) + 0x18);
    r.hi = 0;
    return r;
}

/* FUN_002a9ba8 @ 0x002a9ba8   (est. sk_swift_string_resolve_storage)
 * Ghidra: void FUN_002a9ba8(void)
 * Resolves the String storage base/pointer for the current per-cpu String
 * and returns it (delegates to sk_swift_string_storage_base). Used by nearly
 * every small-string path in this slice.
 * Confidence: medium
 * Notes: in-slice helper; returns the storage word (lo). */
sk_word16_t sk_swift_string_resolve_storage(void)
{
    sk_word16_t r;
    r.lo = FUN_002a9b9c().lo;
    r.hi = 0;
    return r;
}

/* FUN_002a9bd0 @ 0x002a9bd0   (est. sk_swift_closure_invoke)
 * Ghidra: void FUN_002a9bd0(code *param_1, undefined8 param_2, undefined8 param_3)
 * Invokes the function pointer param_1 with param_3 as its single argument.
 * Confidence: medium
 * Notes: trivial closure invoke. */
void sk_swift_closure_invoke(uint64_t fn, uint64_t p2, uint64_t p3)
{
    (*(void (*)(uint64_t))(uintptr_t)fn)(p3);
}

/* FUN_002a9c14 @ 0x002a9c14   (est. sk_swift_range_merge)
 * Ghidra: void FUN_002a9c14(void)
 * Merges two Range expressions (per-cpu slots) into a single closed range,
 * releasing intermediate references. Computes both bounds via
 * FUN_002a9d64, merges the storage pairs, ORs the "closed" flags, and
 * validates lowerBound <= upperBound via the Swift Range fatal.
 * Confidence: medium
 * Notes: SK_FATAL 0x2f9 (Swift.Range lowerBound<upperBound). */
void sk_swift_range_merge(void)
{
    uint64_t *slot = (uint64_t *)(uintptr_t)base_slot();
    uint64_t u4 = slot[2];
    uint64_t u1 = slot[3];
    uint64_t u6 = slot[0];
    thunk_FUN_0036b270(u1);
    uint64_t u2 = FUN_002a9d64(0xf, u6, u4, u1).lo;
    FUN_003a25d4(u1);
    uint64_t u7 = slot[1];
    thunk_FUN_0036b270(u1);
    uint64_t u3 = FUN_002a9d64(u6, u7, u4, u1).lo;
    FUN_003a25d4(u1);
    sk_word16_t g = FUN_0001d4a0(u4, u1);
    uint64_t u4b = FUN_002a9f3c(0xf, u2, g.lo, g.hi).lo;
    uint64_t u5 = FUN_002a9f3c(u4b, u3, g.lo, g.hi).lo;
    if ((u6 & 2) != 0) { u4b = u4b | 3; }
    if ((u7 & 2) != 0) { u5 = u5 | 3; }
    if (u4b >> 0xe <= u5 >> 0xe) {
        FUN_003a25d4(u1);
        slot[0] = u4b;
        slot[1] = u5;
        *(uint64_t *)(slot + 2) = g.lo;
        *(uint64_t *)(slot + 3) = g.hi;
        return;
    }
    SK_FATAL(0x2f9, (unsigned long)&s_Range_requires_lowerBound__upp_005cda00, 0x27,
             (unsigned long)&s_Swift_Range_swift_005cda30, 0x11);
}

/* FUN_002a9d64 @ 0x002a9d64   (est. sk_swift_string_index_offset)
 * Ghidra: ulong FUN_002a9d64(undefined8 param_1, undefined8 param_2, ulong param_3, ulong param_4)
 * Offsets a String index by a scalar count, walking the UTF-8 buffer either
 * forward or backward depending on the sign of the requested offset. Handles
 * both inline small strings and grown/indirect buffers (FUN_002ae098), and
 * runs the Swift StringUnicodeScalarView index-out-of-bounds fatal on
 * overrun. Returns the packed encoded-index word.
 * Confidence: medium
 * Notes: SK_FATAL 0xce/0xc9 (StringUnicodeScalarView index). */
sk_word16_t sk_swift_string_index_offset(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t u6 = 0;
    sk_word16_t r = FUN_002ab130(p1, p3, p4);
    uint64_t pu = r.lo;
    uint64_t u6b = FUN_002ab130(p2, p3, p4).lo;
    uint64_t u15 = u6b >> 0xe;
    if (pu >> 0xe < u15) {
        uint64_t l16 = 0;
        uint64_t l9 = (p4 & 0xfffffffffffffff) + 0x20;
        uint64_t u14 = 0;
        uint32_t u11 = 0;
        do {
            u6 = l16 + 1;
            if ((p4 >> 0x3c & 1) != 0) {
                FUN_002a49a8();
                goto fatal_unicode;
            }
            u14 = pu >> 0x10;
            uint64_t bptr;
            if ((p4 >> 0x3d & 1) == 0) {
                bptr = l9;
                if ((p3 >> 0x3c & 1) == 0) {
                    bptr = FUN_002a9ba8(p3, p4).lo;
                }
                l9 = bptr;
            }
            else {
                l9 = (uint64_t)(uintptr_t)&p3;
            }
            uint8_t b1 = *(uint8_t *)(l9 + u14);
            u11 = 31 - __builtin_clz((uint32_t)b1 << 0x18 ^ 0xffffffff);
            if ((int8_t)b1 >= 0) { u11 = 1; }
            pu = (u14 + u11) * 0x10000;
            l16 = l16 + 1;
        } while ((u14 + u11 & 0xffffffffffff) * 4 < u15);
    }
    else if (u15 < pu >> 0xe) {
        u6 = 0;
        uint64_t l16 = 0;
        uint64_t l9 = (p4 & 0xfffffffffffffff) + 0x20;
        do {
            bool b4 = (u6 - 1) > u6;
            u6 = u6 - 1;
            if ((p4 >> 0x3c & 1) != 0) goto fatal_unicode;
            uint64_t l8;
            if ((p4 >> 0x3d & 1) == 0) {
                l8 = l9;
                if ((p3 >> 0x3c & 1) == 0) {
                    l8 = FUN_002a9ba8(p3, p4).lo;
                }
                int64_t l7 = 0;
                uint8_t *pc;
                do {
                    pc = (uint8_t *)(l8 + (pu >> 0x10) - 1 + l7);
                    l7 = l7 - 1;
                } while ((int8_t)*pc < -0x40);
                l7 = -l7;
                u6 = u6;
                pu = (uint64_t)((int64_t)(long)((long)pu + l7 * -0x10000)) & 0xffffffffffff0000;
            }
            else {
                pu = (uint64_t)((int64_t)(long)((long)pu - 0x10000)) & 0xffffffffffff0000;
            }
        } while (u15 < pu >> 0xe);
    }
    else {
        u6 = 0;
    }
    sk_word16_t r_out;
    r_out.lo = u6;
    r_out.hi = 0;
    return r_out;
fatal_unicode:
    SK_FATAL(0xce, (unsigned long)&s_String_index_is_out_of_bounds_005ce6a0, 0x1d,
             (unsigned long)&s_Swift_StringUnicodeScalarView_sw_005ce6c0, 0x23);
}

/* FUN_002a9f3c @ 0x002a9f3c   (est. sk_swift_string_index_step)
 * Ghidra: ulong FUN_002a9f3c(undefined8 param_1, long param_2, ulong param_3, ulong param_4)
 * Steps a String index by exactly `param_2` Unicode scalars (positive or
 * negative), walking the UTF-8 bytes and returning the packed encoded-index
 * word. Twin of sk_swift_string_index_offset for fixed steps; runs the same
 * index-out-of-bounds fatal.
 * Confidence: medium
 * Notes: SK_FATAL 0xce/0xc9 (StringUnicodeScalarView). */
sk_word16_t sk_swift_string_index_step(uint64_t p1, int64_t p2, uint64_t p3, uint64_t p4)
{
    uint64_t u3 = FUN_002ab130(p1, p3, p4).lo;
    uint64_t u9 = u3;
    if (p2 < 0) {
        uint64_t l4 = 0;
        for (int64_t l10 = 0; p2 < l10; l10 = l10 - 1) {
            u9 = u9 >> 0x10;
            if (u9 == 0) goto fatal_idx_ce;
            if ((p4 >> 0x3c & 1) != 0) {
                u9 = FUN_002ae098(u3, p3, p4).lo;
                { sk_word16_t r2; r2.lo = u9 >> 0xe; r2.hi = 0; return r2; }
            }
            uint64_t l5;
            if ((p4 >> 0x3d & 1) == 0) {
                l5 = (p4 & 0xfffffffffffffff) + 0x20;
                if ((p3 >> 0x3c & 1) == 0) {
                    l5 = FUN_002a9ba8(p3, p4).lo;
                }
                uint8_t *pc;
                do {
                    pc = (uint8_t *)(l5 + -1 + u9);
                    u9 = u9 - 1;
                } while ((int8_t)*pc < -0x40);
            }
            else {
                u9 = u9 - 1;
            }
            u9 = u9 << 0x10 | 5;
        }
    }
    else {
        uint64_t u3b = p3 & 0xffffffffffff;
        if ((p4 & 0x2000000000000000) != 0) {
            u3b = p4 >> 0x38 & 0xf;
        }
        for (; p2 != 0; p2 = p2 - 1) {
            u9 = u9 >> 0x10;
            if (u3b <= u9) {
                SK_FATAL(0xc9, (unsigned long)&s_String_index_is_out_of_bounds_005ce6a0, 0x1d,
                         (unsigned long)&s_Swift_StringUnicodeScalarView_sw_005ce6c0, 0x23);
            }
            if ((p4 >> 0x3c & 1) != 0) {
                FUN_002a49a8();
            }
            uint64_t l4;
            uint8_t b1;
            if ((p4 >> 0x3d & 1) == 0) {
                l4 = (p4 & 0xfffffffffffffff) + 0x20;
                if ((p3 >> 0x3c & 1) == 0) {
                    l4 = FUN_002a9ba8(p3, p4).lo;
                }
                b1 = *(uint8_t *)(l4 + u9);
            }
            else {
                b1 = *(uint8_t *)((uintptr_t)&p3 + u9);
            }
            uint32_t u6 = 31 - __builtin_clz((uint32_t)b1 << 0x18 ^ 0xffffffff);
            if ((int8_t)b1 >= 0) { u6 = 1; }
            u9 = (u9 + u6) * 0x10000 | 5;
        }
    }
    sk_word16_t r;
    r.lo = u9;
    r.hi = 0;
    return r;
fatal_idx_ce:
    SK_FATAL(0xce, (unsigned long)&s_String_index_is_out_of_bounds_005ce6a0, 0x1d,
             (unsigned long)&s_Swift_StringUnicodeScalarView_sw_005ce6c0, 0x23);
}

/* FUN_002aa154 @ 0x002aa154   (est. sk_swift_task_descriptor_build)
 * Ghidra: void FUN_002aa154(void)
 * Builds a task/thread descriptor String: saves the frame, runs the Swift
 * method-table closures (through DAT_00658c00), resolves the task descriptor
 * (FUN_00377824 / FUN_00377bec), walks a byte-producing closure, and
 * restores the frame with the produced pair.
 * Confidence: medium
 * Notes: register-threaded task descriptor build. */
void sk_swift_task_descriptor_build(void)
{
    sk_word16_t f = FUN_0008e518();
    FUN_00358da0();
    FUN_003518c4();
    FUN_003516cc();
    FUN_00377824();
    FUN_00348e18();
    DAT_00658c00();
    FUN_003489c0();
    DAT_00658c00();
    FUN_0034b758();
    FUN_0031e210();
    FUN_000dbd0c();
    FUN_000dbd0c();
    FUN_00350618();
    FUN_00351444();
    uint64_t u2 = FUN_00377bec().lo;
    uint8_t auStack_8[8];
    FUN_00351bec();
    FUN_0035156c();
    FUN_003509e0((uint64_t)&auStack_8);
    FUN_003508cc();
    FUN_0035a0d8(u2);
    FUN_00351654((uint64_t)&auStack_8, 0);
    FUN_00350524();
    sk_word16_t r = FUN_003548b8();
    FUN_0008e500(r.lo, r.hi, f.lo);
}

/* FUN_002aa2a0 @ 0x002aa2a0   (est. sk_swift_string_split_whitespace)
 * Ghidra: void FUN_002aa2a0(void)
 * Splits the current String on a whitespace/newline separator: saves the
 * frame, walks the scalar-decode closure producing (lo,hi) parts, and
 * accumulates them into the output slot. Handles the "found separator"
 * path and the tail-part path, then publishes the result.
 * Confidence: medium
 * Notes: register-threaded Swift String split. */
void sk_swift_string_split_whitespace(void)
{
    uint64_t local_18[2], local_8, local_20;
    sk_word16_t f = FUN_0008e518();
    sk_word16_t v = FUN_00351708();
    FUN_003516cc();
    FUN_00377824();
    FUN_00348ce8();
    DAT_00658c00();
    FUN_0034ab10();
    FUN_0034dfa4();
    DAT_00658c00();
    FUN_0034b87c();
    FUN_0031e210();
    FUN_00350494();
    FUN_003504f4();
    FUN_00351eb4();
    uint64_t u4 = FUN_00377bec().lo;
    FUN_00351ef8();
    FUN_0035156c();
    FUN_00350c80((uint64_t)&local_18);
    FUN_0035084c();
    uint64_t u1 = ((uint64_t *)&local_18)[0];
    FUN_00350494();
    FUN_00351750((uint64_t)&DAT_00612600);
    FUN_00350c80((uint64_t)&local_8);
    FUN_003504ac();
    uint64_t u2 = *(uint64_t *)&local_8;
    if (v.lo < 0) {
        FUN_003511e4();
        FUN_0034b3c8();
        local_8 = u1;
        local_20 = u2;
        FUN_003195f8(u4);
        FUN_00353208((uint64_t)&local_18, (uint64_t)&local_8, v.lo, (uint64_t)&local_20);
        FUN_0035084c();
        FUN_00358540();
        if (0) goto split_done;
    }
    ((uint64_t *)&local_18)[0] = (u2 & 0xffffffffffff0000) + 0x10000;
split_done:
    FUN_0008e500(((uint64_t *)&local_18)[0], f.hi);
}

/* FUN_002aa55c @ 0x002aa55c   (est. sk_swift_index_emit_word)
 * Ghidra: void FUN_002aa55c(undefined8 param_1, ulong param_2)
 * Emits a packed String-index word: tails into thunk_FUN_002298d4 with
 * param_2 shifted down 14 bits (the encoded unit offset).
 * Confidence: medium
 * Notes: trivial index emit. */
void sk_swift_index_emit_word(uint64_t p1, uint64_t p2)
{
    thunk_FUN_002298d4(p2 >> 0xe);
}

/* FUN_002aa584 @ 0x002aa584   (est. sk_swift_utf8_emit_validated)
 * Ghidra: void FUN_002aa584(void)
 * Emits a validated UTF-8 index: reads a partially-validated scalar from
 * FUN_00351ca0, then tails into thunk_FUN_002298d4 and FUN_001a8564.
 * Confidence: medium
 * Notes: Swift UTF-8 validated emit. */
void sk_swift_utf8_emit_validated(void)
{
    FUN_00348c48();
    uint64_t u1 = FUN_00351ca0(0, 0, 0).lo;
    thunk_FUN_002298d4(u1 >> 0xe);
    FUN_001a8564();
}

/* FUN_002aa5e8 @ 0x002aa5e8   (est. sk_swift_utf8_emit_state)
 * Ghidra: void FUN_002aa5e8(void)
 * Emits the current UTF-8 index state: reads the per-cpu slot word, saves
 * the state frame (FUN_001a84f4), tails into thunk_FUN_002298d4 and
 * FUN_001a8564.
 * Confidence: medium
 * Notes: Swift UTF-8 state emit. */
void sk_swift_utf8_emit_state(void)
{
    uint64_t u1 = *(uint64_t *)base_slot();
    uint8_t auStack_68[72];
    FUN_001a84f4((uint64_t)&auStack_68);
    thunk_FUN_002298d4(u1 >> 0xe);
    FUN_001a8564();
}

/* FUN_002aa62c @ 0x002aa62c   (est. sk_swift_uint_radix_label)
 * Ghidra: undefined1 [16] FUN_002aa62c(ulong param_1)
 * Builds the static Swift type-name label word-pair for a numeric radix:
 * for the binary form (bit 3 set) returns {"utf16","binary"-tagged words},
 * for other bases returns the hex/decimal label words. Produces a {lo,hi}
 * pair of packed small-String tags.
 * Confidence: medium
 * Notes: Swift numeric radix label; returns {lo,hi} word pair. */
sk_word16_t sk_swift_uint_radix_label(uint64_t flags)
{
    sk_word16_t out;
    bool binary = (flags & 8) != 0;
    out.lo = binary ? 0x3631667475 : 0x6e776f6e6b6e75;
    out.hi = binary ? 0xe500000000000000 : 0xe700000000000000;
    uint64_t alt = binary ? 0x796e61 : 0x38667475;
    uint64_t altHi = binary ? 0xe300000000000000 : 0xe400000000000000;
    if ((flags & 4) != 0) {
        out.hi = altHi;
        out.lo = alt;
    }
    return out;
}

/* FUN_002aa68c @ 0x002aa68c   (est. sk_swift_uint_description)
 * Ghidra: undefined1 [16] FUN_002aa68c(ulong param_1)
 * Formats an unsigned integer value (param_1 >> 0x10, the encoded digits)
 * as a Swift String description: builds the decimal digit string via
 * FUN_002364dc, appends the radix label (sk_swift_uint_radix_label) and a
 * leading bracket character, merging each into a {lo,hi} word-pair result.
 * Confidence: medium
 * Notes: Swift UInt description; heavy small-String append/merge. */
sk_word16_t sk_swift_uint_description(uint64_t value)
{
    sk_word16_t acc = FUN_002364dc(10, 0, value >> 0x10);
    uint64_t u8 = acc.hi, u6 = acc.lo;
    FUN_003a25d4(0xe000000000000000);
    uint64_t u7 = u6 & 0xffffffffffff;
    if ((u8 & 0x2000000000000000) != 0) { u7 = u8 >> 0x38 & 0xf; }
    sk_word16_t merged;
    if ((u7 == 0) && (((u6 & (u8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        FUN_003a25d4(u8);
        merged.hi = 0xe100000000000000;
        merged.lo = 0x5b;
    }
    else {
        if ((u8 >> 0x3d & 1) != 0) {
            sk_word16_t m = FUN_00291ee0(u6, u8, 0x5b, 0xe100000000000000);
            if (((uint)m.lo & 0xff) != 1) {
                FUN_003a25d4(u8);
                merged = m;
                goto have_open;
            }
        }
        FUN_002a4c98(0x5b, 0xe100000000000000, 0, 1);
        merged = acc;
    }
have_open:
    {
        uint64_t u4 = merged.hi, u5 = merged.lo;
        sk_word16_t radix = sk_swift_uint_radix_label(value);
        uint64_t u8b = radix.hi, u6b = radix.lo;
        uint64_t u7b = u5 & 0xffffffffffff;
        if ((u4 & 0x2000000000000000) != 0) { u7b = u4 >> 0x38 & 0xf; }
        sk_word16_t merged2;
        if ((u7b == 0) && (((u5 & (u4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            FUN_003a25d4(u4);
            merged2 = merged;
        }
        else {
            uint64_t u7c = u8b >> 0x38 & 0xf;
            uint64_t t;
            if ((u4 >> 0x3d & 1) == 0) {
                t = u6b & 0xffffffffffff;
                if ((u8b & 0x2000000000000000) != 0) { t = u7c; }
            }
            else if ((u8b >> 0x3d & 1) == 0) {
                t = u6b & 0xffffffffffff;
            }
            else {
                sk_word16_t m = FUN_00291ee0(u5, u4, u6b, u8b);
                if (((uint)m.lo & 0xff) != 1) {
                    FUN_003a25d4(u8b);
                    FUN_003a25d4(u4);
                    merged2 = m;
                    goto have_digits;
                }
                t = u7c;
            }
            FUN_002a4c98(u6b, u8b, 0, t);
            FUN_003a25d4(u8b);
            merged2 = merged;
        }
have_digits:
        {
            uint64_t u6c = merged2.hi, u8c = merged2.lo;
            sk_word16_t digits = FUN_001a89a8((uint64_t)&DAT_005d32c2, 1, 1);
            uint64_t u8d = digits.hi, u6d = digits.lo;
            uint64_t u7d = u8c & 0xffffffffffff;
            if ((u6c & 0x2000000000000000) != 0) { u7d = u6c >> 0x38 & 0xf; }
            sk_word16_t merged3;
            if ((u7d == 0) && (((u8c & (u6c ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                FUN_003a25d4(u6c);
                merged3 = merged2;
            }
            else {
                uint64_t u7e;
                if ((u6c >> 0x3d & 1) == 0) {
                    u7e = u6d & 0xffffffffffff;
                    if ((u8d & 0x2000000000000000) != 0) { u7e = u8d >> 0x38 & 0xf; }
                }
                else if ((u8d >> 0x3d & 1) == 0) {
                    u7e = u6d & 0xffffffffffff;
                }
                else {
                    sk_word16_t m = FUN_00291ee0(u8c, u6c, u6d, u8d);
                    if (((uint)m.lo & 0xff) != 1) {
                        FUN_003a25d4(u8d);
                        FUN_003a25d4(u6c);
                        merged3 = m;
                        goto have_suffix;
                    }
                    u7e = u8d >> 0x38 & 0xf;
                }
                FUN_002a4c98(u6d, u8d, 0, u7e);
                FUN_003a25d4(u8d);
                merged3 = merged2;
            }
have_suffix:
            return merged3;
        }
    }
}

/* FUN_002aaae4 @ 0x002aaae4   (est. sk_swift_dictionary_lookup_guard)
 * Ghidra: undefined1 [16] FUN_002aaae4(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Dictionary lookup guard: resolves the lookup kind (extraout_var), sets the
 * "found" flag via FUN_0034a3b0, resolves the key (FUN_0001da84), probes the
 * hash via FUN_0029ea8c, and returns a {lo,hi} pair where lo holds the
 * found-slot word (or 0) and hi the low flag bits.
 * Confidence: medium
 * Notes: Swift Dictionary lookup probe. */
sk_word16_t sk_swift_dictionary_lookup_guard(uint64_t p1, uint64_t p2, uint64_t p3)
{
    sk_word16_t out;
    FUN_0034c034();
    bool small = (p3 & 0x1000000000000000) == 0;
    uint64_t u2 = (FUN_0034a3b0().lo >> 0x1b) & 1;
    if (small) { u2 = 1; }
    FUN_0034a3b0(u2);
    if (small) {
        FUN_0034ef68();
        FUN_0001da84();
    }
    FUN_0034ef68();
    uint64_t u2b = FUN_0029ea8c().lo;
    FUN_003a25d4();
    uint64_t u3 = 3;
    if ((u2b & 1) == 0) { u3 = 0; }
    out.lo = u3;
    out.hi = (u2b ^ 0xffffffff) & 1;
    out.b[12] = 0;
    out.b[13] = 0;
    out.b[14] = 0;
    out.b[15] = 0;
    return out;
}

/* FUN_002aab54 @ 0x002aab54   (est. sk_swift_string_iterate_lines)
 * Ghidra: void FUN_002aab54(void)
 * Iterates the lines/scalars of a String: saves the frame, walks the
 * two-phase parse, resolves each part (FUN_00351488), and either merges the
 * next part or resolves the tail via FUN_00353100, publishing the result.
 * Confidence: medium
 * Notes: register-threaded String line iteration. */
void sk_swift_string_iterate_lines(void)
{
    sk_word16_t f = FUN_0008e518();
    uint64_t u2 = FUN_00350b0c().lo;
    FUN_00349720();
    DAT_00658c00();
    FUN_00348a80();
    DAT_00658c00();
    FUN_0034b3d8();
    FUN_00350d14();
    FUN_00351a20();
    uint64_t u3 = FUN_00365b6c().lo;
    sk_word16_t res;
    if ((u3 & 1) == 0) {
        FUN_0034ed68();
        FUN_00350efc();
        FUN_00351744();
        u3 = FUN_00365b6c().lo;
        if ((u3 & 1) == 0) {
            FUN_0031e030(0);
            FUN_00355d1c();
            FUN_00357c04();
            FUN_00350ed0();
            FUN_0032d2f4();
            FUN_00351790();
            sk_word16_t v = FUN_00351488(u2);
            u2 = v.hi;
            res.lo = v.lo;
            goto merge_or_tail;
        }
        FUN_000b43d0(0);
        uint64_t u4 = (uint64_t)(FUN_0034cad8(1).lo >> 0x3b) & 1;
        if ((0 & 0x1000000000000000) == 0) { u4 = 1; }
        FUN_0034cad8(u4);
        FUN_0034c444(u2);
        FUN_002aacf8();
        FUN_00356328();
        FUN_003a25d4();
        if ((0 & 1) != 0) goto tail_zero;
    }
    else {
        FUN_000b43d0(0);
merge_or_tail:
        FUN_002aaae4(u2, res.lo, 0);
        uint64_t u3b = FUN_00351db4().lo;
        if (0) goto tail_zero;
        res = FUN_00358b90();
        goto finish;
tail_zero:
        res.lo = u3b;
        res.hi = 0;
finish:
        res = FUN_00353100(res.lo, res.hi);
    }
    FUN_0008e500(res.lo, res.hi, f.lo);
}

/* FUN_002aacf8 @ 0x002aacf8   (est. sk_swift_string_has_prefix)
 * Ghidra: undefined8 FUN_002aacf8(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Tests whether the current String has the given prefix: resolves the prefix
 * kind, checks the string is in the grown (indirect) form, validates the
 * prefix bounds (FUN_002af340), and returns the boolean comparison result.
 * Confidence: medium
 * Notes: Swift String.hasPrefix. */
uint64_t sk_swift_string_has_prefix(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_00354a28();
    uint64_t u1 = 0;
    if (FUN_0034a3b0(1).lo & 1) u1 = 1;
    FUN_0034a3b0(u1);
    if (u1 & 1) return 0;
    FUN_00084220();
    sk_word16_t v = FUN_0035089c();
    uint64_t u5 = v.lo >> 0xe;
    bool match = false;
    if ((v.hi >> 0xe <= u5) && (u5 <= p3 >> 0xe)) {
        FUN_00351da8();
        FUN_00353178();
        uint64_t u3 = FUN_002af340().lo;
        if ((u3 & 1) != 0) {
            uint64_t u3b = u3;
            if ((((0 >> 1) & 1) == 0) &&
                (u5 != 0 && u5 != p3 >> 0xe)) {
                FUN_0034b730();
                u3b = FUN_002c6c04().lo;
            }
            match = u5 == u3b >> 0xe;
        }
    }
    return FUN_00084234(match, 0).lo;
}

/* FUN_002aadb8 @ 0x002aadb8   (est. sk_swift_obj_release_pair2)
 * Ghidra: void FUN_002aadb8(void)
 * Releases a {lo,hi} object pair and continues into the follow-up handler.
 * Confidence: medium */
void sk_swift_obj_release_pair2(void)
{
    sk_word16_t v = FUN_0034b430();
    thunk_FUN_0036b270(v.lo);
    FUN_0034bf1c();
    FUN_002aadf0();
}

/* FUN_002aadf0 @ 0x002aadf0   (est. sk_swift_string_grown_index)
 * Ghidra: ulong FUN_002aadf0(void)
 * Resolves a String index for the grown/indirect buffer form: dispatches on
 * the containment kind, and either returns the small-string index word or
 * re-validates through the grown-buffer helpers, returning the packed index.
 * Confidence: medium
 * Notes: Swift grown String index resolve. */
uint64_t sk_swift_string_grown_index(void)
{
    FUN_0034c840();
    uint64_t u1 = 0;
    if (FUN_0034a3b0(1).lo & 1) u1 = 1;
    FUN_0034a3b0(u1);
    uint64_t x19 = 0;
    if (u1 & 1) {
        FUN_0034bf1c();
        x19 = FUN_0001da84().lo;
    }
    FUN_0034a260();
    uint64_t cap = FUN_0034a260().lo;
    if (cap < x19 >> 0x10) {
        FUN_003a25d4();
    }
    else if ((*(uint64_t *)base_slot() >> 0x3c & 1) == 0) {
        FUN_003a25d4();
        if ((x19 & 0xc000) == 0) {
            return x19;
        }
    }
    else {
        FUN_0011aa70();
        FUN_002b257c();
        FUN_00356328();
        FUN_003a25d4();
        if ((*(uint64_t *)(base_slot()+1) & 1) != 0) {
            return x19;
        }
    }
    FUN_00358b90();
    return x19;
}

/* FUN_002aae80 @ 0x002aae80   (est. sk_swift_obj_release_pair3)
 * Ghidra: void FUN_002aae80(void)
 * Releases a {lo,hi} object pair and continues into the follow-up handler.
 * Confidence: medium */
void sk_swift_obj_release_pair3(void)
{
    sk_word16_t v = FUN_0034b430();
    thunk_FUN_0036b270(v.lo);
    FUN_0034bf1c();
    FUN_002aaeb8();
}

/* FUN_002aaeb8 @ 0x002aaeb8   (est. sk_swift_string_grown_index2)
 * Ghidra: ulong FUN_002aaeb8(void)
 * Grown String index resolve twin: validates the index against the buffer
 * extent and returns the packed index word, using the small-string path when
 * the buffer is not grown.
 * Confidence: medium
 * Notes: Swift grown String index resolve (variant). */
uint64_t sk_swift_string_grown_index2(void)
{
    FUN_0034c840();
    uint64_t u1 = 0;
    if (FUN_0034a3b0(1).lo & 1) u1 = 1;
    FUN_0034a3b0(u1);
    uint64_t x19 = 0;
    if (u1 & 1) {
        FUN_0034bf1c();
        x19 = FUN_0001da84().lo;
    }
    FUN_0034a260();
    uint64_t cap = FUN_0034a260().lo;
    if (cap < x19 >> 0x10) {
        FUN_003a25d4();
    }
    else {
        if ((*(uint64_t *)base_slot() >> 0x3c & 1) == 0) {
            if ((x19 & 0xc000) != 0) {
                FUN_003a25d4();
                return x19;
            }
            FUN_0034bf1c();
            FUN_002af340();
            FUN_00356328();
            FUN_003a25d4();
        }
        else {
            sk_word16_t v = FUN_003a25d4();
            FUN_002b0f08(v.lo, v.hi, x19);
        }
        if ((*(uint64_t *)(base_slot()+1) & 1) != 0) {
            return x19;
        }
    }
    FUN_00358b90();
    return x19;
}

/* FUN_002aaf60 @ 0x002aaf60   (est. sk_swift_string_index_emit_a)
 * Ghidra: void FUN_002aaf60(void)
 * Emits a String index word (delegates to sk_swift_string_index_resolve).
 * Confidence: medium */
void sk_swift_string_index_emit_a(void)
{
    FUN_002aaf80();
}

/* FUN_002aaf64 @ 0x002aaf64   (est. sk_swift_string_index_emit_b)
 * Ghidra: void FUN_002aaf64(void)
 * Emits a String index word (twin of 002aaf60).
 * Confidence: medium */
void sk_swift_string_index_emit_b(void)
{
    FUN_002aaf80();
}

/* FUN_002aaf80 @ 0x002aaf80   (est. sk_swift_string_index_resolve)
 * Ghidra: ulong FUN_002aaf80(void)
 * Resolves a String index: dispatches on the buffer kind; for small strings
 * walks the scalar-count helper (FUN_002ab778 / FUN_001676cc) and packs the
 * index, for the grown form validates the offset and returns the packed
 * word. Traps on out-of-range.
 * Confidence: medium
 * Notes: Swift String index resolve; SK_FATAL on bounds. */
uint64_t sk_swift_string_index_resolve(void)
{
    uint64_t u2 = FUN_0034fcac().lo;
    uint64_t u1 = 0;
    if (FUN_0034a3b0(1).lo & 1) u1 = 1;
    uint64_t u3;
    if (((u2 >> 1 & 1) == 0) || (FUN_0034a3b0(u1), 0)) {
        FUN_00350624();
        u3 = FUN_002ab778().lo;
        u2 = (uint64_t)(uint32_t)u3;
        if ((u3 & 1) == 0) {
            FUN_00350624();
            u3 = FUN_001676cc().lo;
            u3 = FUN_00357938(u3 & 0xfffffffffffffff3).lo;
            u2 = (uint64_t)(uint32_t)u3;
        }
        if ((u2 >> 1 & 1) == 0) {
            if ((0xffff < u3) && (FUN_0034cbb0(u3 >> 0x10), 0)) {
                FUN_00350624();
                u3 = FUN_002c6aac().lo;
                return u3;
            }
            u3 = u3 | 3;
        }
    }
    else {
        u3 = FUN_0034a274().lo;
        if (FUN_0034a274().lo < u3 >> 0x10) {
            FUN_0034e424();
            FUN_00348974();
            FUN_0034987c();
            FUN_001afe4c();
        }
    }
    return u3;
}

/* FUN_002ab058 @ 0x002ab058   (est. sk_swift_string_prefix_emit)
 * Ghidra: void FUN_002ab058(void)
 * Emits a validated String prefix comparison result: dispatches on the
 * grown/indirect form, resolves the prefix index (FUN_002ab220 /
 * FUN_00355770), and publishes the boolean result through FUN_00357c44.
 * Traps on out-of-range bounds.
 * Confidence: medium
 * Notes: Swift prefix emit; SK_FATAL on bounds. */
void sk_swift_string_prefix_emit(void)
{
    FUN_00357ca0();
    FUN_0034d654();
    uint64_t u3 = FUN_00354a28().lo;
    uint64_t u1 = 0;
    if (0) u1 = 1;
    uint64_t u4;
    if ((u3 >> 1 & 1) != 0) {
        FUN_0034a3b0(u1);
        if (!0) {
            u4 = FUN_00355770().lo;
            if (u4 < FUN_00355770().lo) {
                FUN_003488bc(1);
                FUN_0034a96c();
                FUN_001afe4c();
            }
            goto done_prefix;
        }
    }
    FUN_0034e084();
    u4 = FUN_002ab220().lo;
    if ((u4 & 1) == 0) {
        FUN_003504a0();
        FUN_001676cc();
        FUN_00353850();
        u4 = 1;
    }
    if ((((0 >> 1 & 1) == 0) || ((u4 >> 1 & 1) == 0)) &&
        (FUN_00355770(), 0)) {
        FUN_0034e084();
        FUN_00357c44();
        FUN_002c6c04();
        return;
    }
done_prefix:
    FUN_00357c44(u4, 0);
}

/* FUN_002ab130 @ 0x002ab130   (est. sk_swift_string_index_validate)
 * Ghidra: ulong FUN_002ab130(ulong param_1, ulong param_2, ulong param_3)
 * Validates a String index against the string's bounds: for a grown/indirect
 * index (kind bits matching the buffer kind) it re-validates via
 * FUN_002ab778/FUN_001676cc and repacks; for the inline form it checks the
 * encoded offset against the buffer width and runs the
 * StringIndexValidation fatal on overrun. Returns the validated index word.
 * Confidence: medium
 * Notes: SK_FATAL 0xa5 (StringIndexValidation). */
sk_word16_t sk_swift_string_index_validate(uint64_t idx, uint64_t sLo, uint64_t sHi)
{
    uint64_t u2 = (sLo >> 0x3b) & 1;
    if ((sHi & 0x1000000000000000) == 0) { u2 = 1; }
    if (((idx & 1) == 0) || ((idx & 0xc) == 4L << u2)) {
        uint64_t r = FUN_002ab778(idx, sLo, sHi, 0x35).lo;
        if ((r & 1) == 0) {
            uint64_t u1 = FUN_001676cc(r, sLo, sHi).lo;
            idx = r & 0xc | u1 & 0xfffffffffffffff3 | 1;
        } else {
            idx = r;
        }
    }
    else {
        uint64_t u1 = sLo & 0xffffffffffff;
        if ((sHi & 0x2000000000000000) != 0) {
            u1 = sHi >> 0x38 & 0xf;
        }
        if (u1 < idx >> 0x10) {
            SK_FATAL(0xa5, (unsigned long)&s_String_index_is_out_of_bounds_005ce6a0, 0x1d,
                     (unsigned long)&s_Swift_StringIndexValidation_swif_005d32a0, 0x21);
        }
    }
    sk_word16_t r;
    r.lo = idx;
    r.hi = 0;
    return r;
}

/* FUN_002ab220 @ 0x002ab220   (est. sk_swift_substring_index_validate)
 * Ghidra: void FUN_002ab220(ulong param_1, ulong param_2, ulong param_3, undefined8 param_4, ulong param_5)
 * Validates a Substring index: normalizes a grown index via FUN_0001da84 and
 * checks it lies within [param_2, param_3], running the Substring-index
 * out-of-bounds fatal otherwise.
 * Confidence: medium
 * Notes: SK_FATAL 0x41 (StringIndexValidation, Substring). */
sk_word16_t sk_swift_substring_index_validate(uint64_t idx, uint64_t lo, uint64_t hi, uint64_t sLo, uint64_t sHi)
{
    uint64_t u1 = (sLo >> 0x3b) & 1;
    if ((sHi & 0x1000000000000000) == 0) { u1 = 1; }
    if ((idx & 0xc) == 4L << u1) {
        idx = FUN_0001da84(idx, sLo, sHi).lo;
    }
    if (idx >> 0xe < lo >> 0xe || hi >> 0xe < idx >> 0xe) {
        SK_FATAL(0x41, (unsigned long)&s_Substring_index_is_out_of_bounds_005d0960, 0x20,
                 (unsigned long)&s_Swift_StringIndexValidation_swif_005d32a0, 0x21);
    }
    sk_word16_t r; r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_002ab2d4 @ 0x002ab2d4   (est. sk_swift_substring_index_validate_closed)
 * Ghidra: void FUN_002ab2d4(ulong param_1, ulong param_2, ulong param_3, undefined8 param_4, ulong param_5)
 * Validates a Substring index against a closed range [lo, hi]: identical to
 * FUN_002ab220 but uses the half-open bound check (hi < idx is allowed).
 * Runs the same fatal.
 * Confidence: medium
 * Notes: SK_FATAL 0x2b (StringIndexValidation, Substring). */
sk_word16_t sk_swift_substring_index_validate_closed(uint64_t idx, uint64_t lo, uint64_t hi, uint64_t sLo, uint64_t sHi)
{
    uint64_t u1 = (sLo >> 0x3b) & 1;
    if ((sHi & 0x1000000000000000) == 0) { u1 = 1; }
    if ((idx & 0xc) == 4L << u1) {
        idx = FUN_0001da84(idx, sLo, sHi).lo;
    }
    if (idx >> 0xe < lo >> 0xe || hi >> 0xe <= idx >> 0xe) {
        SK_FATAL(0x2b, (unsigned long)&s_Substring_index_is_out_of_bounds_005d0960, 0x20,
                 (unsigned long)&s_Swift_StringIndexValidation_swif_005d32a0, 0x21);
    }
    sk_word16_t r; r.lo = 0; r.hi = 0;
    return r;
}

/* FUN_002ab388 @ 0x002ab388   (est. sk_swift_substring_index_range_validate)
 * Ghidra: undefined1 [16] FUN_002ab388(ulong param_1..param_6)
 * Validates a Substring index range [param_1, param_2] against the bounds
 * [param_3, param_4]: normalizes grown indices, checks the ordering, and
 * runs the Substring range out-of-bounds fatal on violation. Returns the
 * validated {lo,hi} range pair.
 * Confidence: medium
 * Notes: SK_FATAL 99 (StringIndexValidation, Substring range). */
sk_word16_t sk_swift_substring_index_range_validate(uint64_t a, uint64_t b, uint64_t lo, uint64_t hi, uint64_t sLo, uint64_t sHi)
{
    uint64_t u1 = (sLo >> 0x3b) & 1;
    if ((sHi & 0x1000000000000000) == 0) { u1 = 1; }
    if ((b & 0xc) == 4L << u1) { b = FUN_0001da84(b, sLo, sHi).lo; }
    if ((a & 0xc) == 4L << u1) { a = FUN_0001da84(a, sLo, sHi).lo; }
    if ((a >> 0xe < lo >> 0xe || b >> 0xe < a >> 0xe) || hi >> 0xe < b >> 0xe) {
        SK_FATAL(99, (unsigned long)&s_Substring_index_range_is_out_of_b_005d3890, 0x26,
                 (unsigned long)&s_Swift_StringIndexValidation_swif_005d32a0, 0x21);
    }
    sk_word16_t out;
    out.hi = b;
    out.lo = a;
    return out;
}

/* FUN_002ab49c @ 0x002ab49c   (est. sk_swift_string_index_repack)
 * Ghidra: ulong FUN_002ab49c(ulong param_1)
 * Repacks a grown String index word into the canonical form: if not already
 * packed (bit 0 clear), resolves it through FUN_001676cc / FUN_00355814 and
 * sets the packed flag.
 * Confidence: medium
 * Notes: Swift String index repack. */
uint64_t sk_swift_string_index_repack(uint64_t idx)
{
    if ((idx & 1) == 0) {
        FUN_001676cc(idx);
        FUN_00355814();
        idx = 1;
    }
    return idx;
}

/* FUN_002ab4d4 @ 0x002ab4d4   (est. sk_swift_substring_index_repack)
 * Ghidra: ulong FUN_002ab4d4(ulong param_1..param_5)
 * Repacks a Substring index: validates against [param_2, param_3] and packs
 * it; runs the Substring index out-of-bounds fatal on violation.
 * Confidence: medium
 * Notes: SK_FATAL 0x8f (StringIndexValidation, Substring). */
uint64_t sk_swift_substring_index_repack(uint64_t idx, uint64_t lo, uint64_t hi, uint64_t sLo, uint64_t sHi)
{
    uint64_t u2 = (sLo >> 0x3b) & 1;
    if ((sHi & 0x1000000000000000) == 0) { u2 = 1; }
    if (((idx & 1) == 0) || ((idx & 0xc) == 4L << u2)) {
        FUN_002ab2d4();
        if ((idx & 1) == 0) {
            uint64_t u1 = FUN_001676cc(idx, sLo, sHi).lo;
            idx = idx & 0xc | u1 & 0xfffffffffffffff3 | 1;
        }
    }
    else if (idx >> 0xe < lo >> 0xe || hi >> 0xe <= idx >> 0xe) {
        SK_FATAL(0x8f, (unsigned long)&s_Substring_index_is_out_of_bounds_005d0960, 0x20,
                 (unsigned long)&s_Swift_StringIndexValidation_swif_005d32a0, 0x21);
    }
    return idx;
}

/* FUN_002ab5bc @ 0x002ab5bc   (est. sk_swift_string_index_range_commit)
 * Ghidra: void FUN_002ab5bc(undefined8 param_1..param_6)
 * Commits a validated String index range: normalizes both endpoints via the
 * Swift index helpers, validates the ordering, and commits the range via
 * FUN_0007c1c4. Traps on out-of-range.
 * Confidence: medium
 * Notes: Swift String range commit; SK_FATAL on bounds. */
void sk_swift_string_index_range_commit(uint64_t p1, uint64_t p2, uint64_t lo, uint64_t hi, uint64_t sLo, uint64_t sHi)
{
    uint64_t u2 = (sLo >> 0x20);
    FUN_003542e8();
    FUN_003504d0();
    bool small = (sHi & 0x1000000000000000) == 0;
    u2 = u2 >> 0x1b & 1;
    if (small) { u2 = 1; }
    uint64_t x20 = *(uint64_t *)base_slot();
    uint64_t x19 = *(uint64_t *)(base_slot()+1);
    if ((((x20 & 1) == 0) || (FUN_0034cad8(u2), small)) || ((x19 & 1) == 0) ||
        ((x19 & 0xc) == 0)) {
        FUN_0007c1c4();
        FUN_00356a20();
        FUN_002ab388();
        FUN_00351e08();
        if ((x19 & 1) == 0) {
            FUN_003504ac();
            FUN_001676cc();
            FUN_00355814();
        }
        if ((x20 & 1) == 0) {
            FUN_00077894();
            FUN_001676cc();
            FUN_00359fc0();
        }
    }
    else if ((x20 >> 0xe < lo >> 0xe) || (hi >> 0xe < x19 >> 0xe)) {
        FUN_003488bc(1);
        FUN_003587e0();
        FUN_0034ae08();
        FUN_001afe4c();
    }
    FUN_0007c1c4();
}

/* FUN_002ab6a0 @ 0x002ab6a0   (est. sk_swift_string_prefix_emit2)
 * Ghidra: void FUN_002ab6a0(void)
 * Prefix emit twin using the half-open (Substring) index validation:
 * identical structure to sk_swift_string_prefix_emit but bounds-checked
 * with FUN_002ab2d4.
 * Confidence: medium
 * Notes: SK_FATAL on bounds. */
void sk_swift_string_prefix_emit2(void)
{
    FUN_00357ca0();
    FUN_0034d654();
    uint64_t u3 = FUN_00354a28().lo;
    uint64_t u1 = 0;
    if (0) u1 = 1;
    uint64_t u4;
    if ((u3 >> 1 & 1) != 0) {
        FUN_0034a3b0(u1);
        if (!0) {
            u4 = FUN_00355770().lo;
            if (u4 <= FUN_00355770().lo) {
                FUN_003488bc(1);
                FUN_0034a96c();
                FUN_001afe4c();
            }
            goto done_prefix2;
        }
    }
    FUN_0034e084();
    u4 = FUN_002ab2d4().lo;
    if ((u4 & 1) == 0) {
        FUN_003504a0();
        FUN_001676cc();
        FUN_00353850();
        u4 = 1;
    }
    if ((((0 >> 1 & 1) == 0) || ((u4 >> 1 & 1) == 0)) &&
        (FUN_00355770(), 0)) {
        FUN_0034e084();
        FUN_00357c44();
        FUN_002c6c04();
        return;
    }
done_prefix2:
    FUN_00357c44(u4, 0);
}

/* FUN_002ab778 @ 0x002ab778   (est. sk_swift_string_index_validate_inline)
 * Ghidra: void FUN_002ab778(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Inline String index validation helper: resolves the buffer kind, checks
 * the encoded offset against the buffer width (FUN_0034a260), and traps on
 * out-of-range via the shared fatal path.
 * Confidence: medium
 * Notes: SK_FATAL on bounds. */
sk_word16_t sk_swift_string_index_validate_inline(uint64_t p1, uint64_t p2, uint64_t p3)
{
    FUN_0034b85c();
    bool small = (p3 & 0x1000000000000000) == 0;
    uint64_t u3 = 0;
    if (small) { u3 = 1; }
    FUN_0034a3b0(u3);
    if (small) {
        FUN_00350548();
        FUN_0001da84();
    }
    uint64_t u2 = FUN_0034a260().lo;
    sk_word16_t r;
    if (u2 >> 0x10 <= FUN_0034a260().lo) {
        r.lo = 0; r.hi = 0;
        return r;
    }
    FUN_0035047c();
    FUN_00348974();
    FUN_0034987c();
    FUN_001afe4c();
}

/* FUN_002ab7f0 @ 0x002ab7f0   (est. sk_swift_string_range_emit)
 * Ghidra: void FUN_002ab7f0(void)
 * Emits a validated String range: normalizes both endpoints via the grown
 * index helpers, checks the range against the buffer bounds, and publishes
 * the pair via FUN_000b43d0/FUN_00357c44. Traps on out-of-range.
 * Confidence: medium
 * Notes: SK_FATAL on bounds. */
void sk_swift_string_range_emit(void)
{
    FUN_00357ca0();
    FUN_00353274();
    FUN_0035098c();
    FUN_00357794();
    uint64_t u1 = 0;
    if (0) u1 = 1;
    uint64_t u2 = 4L << (u1 & 0x3f);
    uint64_t x20 = *(uint64_t *)base_slot();
    uint64_t x21 = *(uint64_t *)(base_slot()+1);
    if ((0 & 0xc) == u2) {
        FUN_000bd3a4();
        x20 = FUN_0001da84().lo;
    }
    if ((x21 & 0xc) == u2) {
        FUN_0034ef78();
        x21 = FUN_0001da84().lo;
    }
    FUN_0034a900();
    if ((FUN_0034a900().lo * 4) < x20 >> 0xe || x20 >> 0xe < x21 >> 0xe) {
        FUN_0035047c();
        FUN_0034951c();
        FUN_003587e0();
        FUN_0034ae08();
        FUN_001afe4c();
    }
    sk_word16_t r = FUN_000b43d0();
    FUN_00357c44(r.lo, r.hi, 0);
}

/* FUN_002ab8ac @ 0x002ab8ac   (est. sk_swift_string_buffer_reserve)
 * Ghidra: void FUN_002ab8ac(void)
 * Reserves a String buffer for `n` bytes: validates the caller's bounds
 * (both endpoints), normalizes grown index endpoints, and commits the
 * reservation via FUN_0007c1c4. Traps on out-of-range.
 * Confidence: medium
 * Notes: in-slice; the Swift buffer reserve path. */
sk_word16_t sk_swift_string_buffer_reserve(void)
{
    FUN_0034ed98();
    FUN_00357794();
    uint64_t u1 = 0;
    if (0) u1 = 1;
    uint64_t x20 = *(uint64_t *)base_slot();
    uint64_t x19 = *(uint64_t *)(base_slot()+1);
    if ((((x20 & 1) == 0) || (FUN_0034cad8(u1), 0)) || ((x19 & 1) == 0) ||
        ((x19 & 0xc) == 0)) {
        FUN_0007c1c4();
        FUN_00351b78();
        FUN_002ab7f0();
        FUN_00351e08();
        if ((x20 & 1) == 0) {
            FUN_00077894();
            FUN_001676cc();
            FUN_00359fc0();
        }
        if ((x19 & 1) == 0) {
            sk_word16_t v = FUN_003504ac();
            FUN_001676cc(v.lo, v.hi, 0);
            FUN_00355814();
        }
    }
    else {
        FUN_0034f98c(0 & 0xffffffffffff);
        if (FUN_0034f98c().lo < x19 >> 0x10) {
            FUN_0034dab8();
            FUN_0034951c();
            FUN_003587e0();
            FUN_0034ae08();
            FUN_001afe4c();
        }
    }
    FUN_0007c1c4();
    sk_word16_t r;
    r.lo = 0;
    r.hi = 0;
    return r;
}

/* FUN_002ab984 @ 0x002ab984   (est. sk_swift_string_describe)
 * Ghidra: void FUN_002ab984(void)
 * Describes a String value: resolves the descriptor (FUN_0034a958 /
 * FUN_003194f8), invokes the description closure with the type words, and
 * runs the resolved method-table closure.
 * Confidence: medium
 * Notes: Swift String description dispatch. */
void sk_swift_string_describe(void)
{
    FUN_0034a958();
    uint64_t u1 = FUN_003194f8().lo;
    FUN_003548c4(u1, u1, 0x6756a8, 0x66e1b8);
    FUN_00352920();
}

/* FUN_002ab9e0 @ 0x002ab9e0   (est. sk_swift_string_new_builtin)
 * Ghidra: void FUN_002ab9e0(undefined1 (*param_1) [16])
 * Produces a fresh empty String word-pair via FUN_001a8a8c and stores it
 * into the caller's 16-byte output buffer.
 * Confidence: medium */
void sk_swift_string_new_builtin(sk_word16_t *out)
{
    *out = FUN_001a8a8c();
}

/* FUN_002aba18 @ 0x002aba18   (est. sk_swift_string_init_hash)
 * Ghidra: void FUN_002aba18(void)
 * Initializes a String hash seed: runs the seed (FUN_0034b318), the two
 * hash rounds (FUN_00027754), and finalizes the hash context
 * (FUN_00352894 / FUN_00357c04 / FUN_00285e24).
 * Confidence: medium
 * Notes: Swift String hashing init. */
void sk_swift_string_init_hash(void)
{
    FUN_0034b318();
    FUN_00027754(0);
    FUN_00027754();
    FUN_00352894();
    FUN_00357c04(0);
    FUN_0034b508();
    FUN_00285e24();
}

/* FUN_002aba8c @ 0x002aba8c   (est. sk_swift_string_hash_finalize)
 * Ghidra: void FUN_002aba8c(void)
 * Finalizes a String hash: saves the frame, runs the two hash rounds
 * (FUN_0034fce4 / FUN_0031e2e0), invokes the Swift method-table closures
 * through DAT_00658c00, and restores the frame with the hash result.
 * Confidence: medium
 * Notes: register-threaded String hash finalize. */
void sk_swift_string_hash_finalize(void)
{
    sk_word16_t f = FUN_0008e518();
    FUN_0035a2d0();
    FUN_00349720();
    DAT_00658c00();
    FUN_00348f50();
    FUN_00027754(0);
    FUN_0034fce4();
    uint64_t u1 = FUN_0031e2e0().lo;
    FUN_000a6f88();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034b0d4();
    FUN_003499c8();
    DAT_00658c00();
    FUN_003490ec();
    FUN_00027754(0);
    FUN_0034da98();
    FUN_0031e2e0();
    FUN_00348fd8();
    FUN_0007c1a4();
    DAT_00658c00();
    FUN_0034d3c4();
    FUN_00351e84();
    FUN_003513b4(0);
    FUN_00351984(0);
    FUN_0035745c();
    FUN_003508c0(0);
    sk_word16_t v = FUN_00350944();
    FUN_00285e24(v.lo, v.hi, u1);
    FUN_0034fd04();
    FUN_00352498(0);
    uint64_t u1b = FUN_00353034().lo;
    FUN_0008e500(u1b, f.lo);
}

/* FUN_002abcb0 @ 0x002abcb0   (est. sk_swift_string_contains_char)
 * Ghidra: ulong FUN_002abcb0(undefined8 param_1, undefined8 param_2, ulong param_3, ulong param_4)
 * Tests whether the String contains a given Character: resolves the two
 * String storage pairs, compares their canonical forms via the Swift
 * comparison helpers, and returns the boolean. Uses the small-string compare
 * when both operands are inline, otherwise the grown-buffer path.
 * Confidence: medium
 * Notes: Swift String.contains(Character). */
uint64_t sk_swift_string_contains_char(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    sk_word16_t v = FUN_00077888();
    uint64_t u3 = v.hi;
    if ((p4 & 0x2000000000000000) != 0) { p3 = p4; }
    if (((p4 >> 0x3c & 1) != 0) || ((p3 >> 0x3e & 1) == 0)) {
        goto not_ascii;
    }
    uint64_t u1 = v.lo;
    if ((u3 & 0x2000000000000000) != 0) { u1 = u3; }
    if (((u3 >> 0x3c & 1) != 0) || ((u1 >> 0x3e & 1) == 0)) {
not_ascii:
        FUN_0035053c();
        return FUN_000b773c().lo & 1;
    }
    uint64_t u6 = v.lo & 0xffffffffffff;
    uint64_t u5 = u3 >> 0x38 & 0xf;
    uint64_t u1b = u6;
    if ((u3 & 0x2000000000000000) != 0) { u1b = u5; }
    sk_word16_t c = FUN_0034cbb0(u1b);
    if (FUN_0034cbb0().lo <= FUN_0034cbb0().hi) {
        if ((c.hi >> 0x3d & 1) == 0) {
            uint64_t bptr;
            if ((c.lo >> 0x3c & 1) == 0) {
                bptr = FUN_002a9ba8().lo;
            }
            else {
                bptr = FUN_0035ab14().lo;
            }
            uint8_t local_31;
            FUN_0035053c((uint64_t)&local_31, bptr, c.hi);
            FUN_002abda8();
            if ((local_31 & 1) != 0) {
                FUN_00350624(u6 << 0x10);
                return FUN_0029ead8().lo & 1;
            }
        }
        else {
            uint64_t uStack_40 = c.hi & 0xffffffffffffff;
            uint64_t local_48 = c.lo;
            uint8_t local_49;
            FUN_0034b788((uint64_t)&local_49, (uint64_t)&local_48);
            FUN_002abda8();
            if (local_49 == 0x01) {
                FUN_00350624(u6 << 0x10);
                return FUN_0029ead8().lo & 1;
            }
        }
    }
    return 0;
}

/* FUN_002abda8 @ 0x002abda8   (est. sk_swift_string_canonicalize)
 * Ghidra: void FUN_002abda8(void)
 * Canonicalizes a String for comparison: resolves the storage pair, handles
 * the grown/indirect form (FUN_00350798), and commits the canonical form via
 * FUN_002a1278, publishing the equality into the caller's byte slot. Traps
 * on an out-of-range storage.
 * Confidence: medium
 * Notes: Swift String canonicalize; SK_FATAL on bounds. */
void sk_swift_string_canonicalize(void)
{
    sk_word16_t v = FUN_0035098c();
    uint64_t in_x3 = 0;
    bool grown = (in_x3 >> 0x3d & 1) != 0;
    if (!grown) {
        if ((0 >> 0x3c & 1) == 0) {
            FUN_002a9ba8(0, in_x3);
            FUN_00351790();
        }
        FUN_00350798();
    }
    else {
        uint64_t uStack_38 = in_x3 & 0xffffffffffffff;
        FUN_00350798(in_x3 >> 0x38 & 0xf, v.lo, v.hi, (uint64_t)&uStack_38);
    }
    FUN_003520dc();
    sk_word16_t r = FUN_0028e8c0();
    if (r.lo < 0 || r.hi > (int64_t)in_x3) {
        FUN_003481fc();
        FUN_001afe4c();
    }
    FUN_00348e48();
    FUN_001e4cbc();
    FUN_003523fc();
    FUN_002a1278();
}

/* FUN_002abe60 @ 0x002abe60   (est. sk_swift_string_has_scalar)
 * Ghidra: uint FUN_002abe60(undefined8 param_1, undefined8 param_2, ulong param_3, ulong param_4)
 * Tests whether the String contains a given Unicode scalar: resolves both
 * storage pairs, compares byte ranges, and returns the boolean. Handles the
 * small-string and grown-buffer comparison paths.
 * Confidence: medium
 * Notes: Swift String.contains(UnicodeScalar). */
uint64_t sk_swift_string_has_scalar(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    sk_word16_t v = FUN_00077888();
    uint64_t u4 = v.hi;
    if ((p4 & 0x2000000000000000) != 0) { p3 = p4; }
    if (((p4 >> 0x3c & 1) == 0) && ((p3 >> 0x3e & 1) != 0)) {
        uint64_t u2 = v.lo;
        if ((u4 & 0x2000000000000000) != 0) { u2 = u4; }
        if (((u4 >> 0x3c & 1) == 0) && ((u2 >> 0x3e & 1) != 0)) {
            sk_word16_t c = FUN_0034a274();
            uint64_t u5 = c.hi;
            uint64_t u2b = c.lo;
            uint64_t u6 = u5 >> 0x38 & 0xf;
            uint64_t u4b = u2b & 0xffffffffffff;
            if ((u5 & 0x2000000000000000) != 0) { u4b = u6; }
            if ((int64_t)(FUN_0034a274().lo - u4b) >= 0) {
                uint8_t local_51;
                if ((u5 >> 0x3d & 1) == 0) {
                    uint64_t bptr;
                    if ((u2b >> 0x3c & 1) == 0) {
                        bptr = FUN_002a9ba8().lo;
                    }
                    else {
                        bptr = FUN_0035ab14().lo;
                    }
                    uint8_t local_39[9];
                    FUN_0035053c((uint64_t)&local_39, bptr, c.hi);
                    FUN_002abf50();
                    local_51 = local_39[0];
                }
                else {
                    uint64_t uStack_48 = u5 & 0xffffffffffffff;
                    uint64_t local_50 = u2b;
                    FUN_0035053c((uint64_t)&local_51, (uint64_t)&local_50, u6);
                    FUN_002abf50();
                }
                if ((local_51 & 1) != 0) {
                    FUN_00350624((FUN_0034a274().lo - u4b) * 0x10000);
                    return FUN_0029ead8().lo & 1;
                }
            }
            return 0;
        }
    }
    FUN_0035053c();
    return FUN_00284ff4().lo & 1;
}

/* FUN_002abf50 @ 0x002abf50   (est. sk_swift_string_canonicalize_scalar)
 * Ghidra: void FUN_002abf50(undefined8 param_1..param_5)
 * Canonicalizes a String for scalar comparison: resolves the storage pair,
 * checks the requested range against the buffer, canonicalizes, and
 * publishes the equality flag. Traps on out-of-range.
 * Confidence: medium
 * Notes: Swift String canonicalize scalar; SK_FATAL on bounds. */
void sk_swift_string_canonicalize_scalar(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
    FUN_00041138();
    uint64_t u3 = p4 >> 0x38 & 0xf;
    uint64_t u1 = p3 & 0xffffffffffff;
    if ((p4 & 0x2000000000000000) != 0) { u1 = u3; }
    if (u1 < p5) {
        FUN_00347d60();
        FUN_001afe4c();
    }
    uint64_t u3b = p3 & 0xffffffffffff;
    if ((p3 >> 0x3c & 1) == 0) {
        FUN_00355968();
        FUN_002a9ba8();
        FUN_00351790();
        u3b = p4;
    }
    FUN_003520dc(p5);
    sk_word16_t r = FUN_0028e8c0();
    if (r.lo < 0 || r.hi > (int64_t)u3b) {
        FUN_003481fc();
        FUN_001afe4c();
    }
    FUN_00348e48();
    FUN_001e4cbc();
    FUN_003523fc();
    FUN_002a1278();
    FUN_0035847c(0);
}

/* FUN_002ac024 @ 0x002ac024   (est. sk_swift_string_contains_char2)
 * Ghidra: void FUN_002ac024(undefined8 param_1, undefined8 param_2, undefined8 param_3, ulong param_4)
 * String.contains(Character) twin: resolves the character storage, canonical
 * compares, and stores the boolean result into *unaff_x19. Traps on
 * out-of-range storage.
 * Confidence: medium
 * Notes: Swift String.contains(Character); SK_FATAL on bounds. */
void sk_swift_string_contains_char2(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
    uint8_t *x19 = (uint8_t *)base_slot();
    FUN_003542e8();
    sk_word16_t v = FUN_00350c5c(p3);
    bool grown = (p4 >> 0x3d & 1) != 0;
    uint64_t u3b = p4;
    if (!grown) {
        if ((0 >> 0x3c & 1) == 0) {
            FUN_002a9ba8(0, p4);
            FUN_00351790();
        }
        else {
            u3b = 0 & 0xffffffffffff;
        }
        FUN_00100efc();
    }
    else {
        uint64_t uStack_38 = p4 & 0xffffffffffffff;
        FUN_00100efc(v.lo, v.hi, (uint64_t)&uStack_38);
        u3b = 0;
    }
    FUN_003520dc();
    sk_word16_t r = FUN_0028e8c0();
    if (r.lo < 0 || r.hi > (int64_t)u3b) {
        FUN_003481fc();
        FUN_001afe4c();
    }
    FUN_00348e48();
    FUN_001e4cbc();
    uint8_t b = (uint8_t)FUN_002ac260().lo;
    *x19 = b & 1;
}

/* FUN_002ac0d8 @ 0x002ac0d8   (est. sk_sha_compress_block)
 * Ghidra: void FUN_002ac0d8(byte *param_1, long param_2, ulong *param_3)
 * Feeds a byte stream into a 5-word (SHA-1 style) hash state. For each input
 * byte that lands on a word boundary (byte-count mod 8 == 7) it compresses
 * the current block with the SHA-1 round mix (rotations and additions) into
 * the 5-word state; otherwise it simply appends the byte to the current word.
 * Confidence: high
 * Notes: SHA-1 compression loop; state is 5 words (param_3[0..4]). */
void sk_sha_compress_block(uint8_t *src, int64_t len, uint64_t *state)
{
    if (src == NULL) return;
    for (; len != 0; len = len - 1) {
        uint64_t w = state[0];
        uint64_t pos = w >> 0x38 & 7;
        uint64_t b = (uint64_t)*src << (pos << 3);
        if (pos == 7) {
            b = b | w & 0xffffffffffffff;
            uint64_t e0 = state[4] ^ b;
            uint64_t a = state[2];
            uint64_t f = a + state[1];
            uint64_t d = f ^ (a >> 0x33 | a << 0xd);
            uint64_t b0 = state[3] + e0 + d;
            uint64_t e = state[3] + e0 ^ (e0 >> 0x30 | e0 << 0x10);
            uint64_t c = e + (f >> 0x20 | f << 0x20);
            w = w & 0xff00000000000000;
            state[3] = b0 >> 0x20 | b0 << 0x20;
            state[4] = c ^ (e >> 0x2b | e << 0x15);
            state[1] = c ^ b;
            state[2] = b0 ^ (d >> 0x2f | d << 0x11);
        }
        else {
            w = b | w;
        }
        state[0] = w + 0x100000000000000;
        src = src + 1;
    }
}

/* FUN_002ac168 @ 0x002ac168   (est. sk_swift_array_append_bytes)
 * Ghidra: void FUN_002ac168(long param_1)
 * Appends a run of bytes to a growable array: iterates the source byte
 * pointer, checks whether the array needs regrowth (FUN_003a261c /
 * FUN_0006b3f4 / FUN_0006b42c), grows the backing store, and stores each
 * byte at [header + count + 0x20], incrementing the used count.
 * Confidence: medium
 * Notes: Swift ContiguousArray byte append; header at +0x10 (count),
 *   +0x18 (capacity), +0x20 (data). */
void sk_swift_array_append_bytes(uint64_t count)
{
    uint64_t *x19 = (uint64_t *)base_slot();
    uint64_t *x21 = x19 + 2;
    uint64_t n = x19[2];
    if (n == 0) return;
    uint64_t src = *(uint64_t *)base_slot();
    FUN_00084220();
    FUN_0034b430();
    for (; n != 0; n = n - 1) {
        uint8_t byte = *(uint8_t *)src;
        uint64_t hdr = *x19;
        uint64_t h = FUN_003a261c(hdr).lo;
        *x19 = hdr;
        if ((h & 1) == 0) {
            FUN_0006b3f4(*(uint64_t *)(hdr + 0x10));
            hdr = FUN_001a0870().lo;
            *x19 = hdr;
        }
        uint64_t used = *(uint64_t *)(hdr + 0x10);
        if (*(uint64_t *)(hdr + 0x18) >> 1 <= used) {
            FUN_0006b42c();
            FUN_00352480(0, used + 1);
            hdr = FUN_001a0870().lo;
            *x19 = hdr;
        }
        src = src + 1;
        *(uint64_t *)(hdr + 0x10) = used + 1;
        *(uint8_t *)(hdr + used + 0x20) = byte;
    }
    FUN_00084234(0);
}

/* FUN_002ac214 @ 0x002ac214   (est. sk_swift_array_for_each)
 * Ghidra: void FUN_002ac214(long param_1)
 * Applies a callback to every element of a byte array: iterates the element
 * pointer and invokes the closure for each, stopping on the element count.
 * Confidence: medium
 * Notes: Swift array forEach; callback via *unaff_x19. */
void sk_swift_array_for_each(uint64_t count)
{
    uint64_t cb = *(uint64_t *)base_slot();
    uint64_t *x21 = (uint64_t *)base_slot() + 2;
    uint64_t n = x21[0];
    uint64_t src = x21[1];
    if (count == 0) return;
    FUN_00356048();
    FUN_0035089c();
    do {
        if (n == 0) return;
        (*(void (*)(uint64_t))(uintptr_t)cb)(*(uint64_t *)src);
        n = n - 1;
        src = src + 8;
    } while (0);
}

/* FUN_002ac260 @ 0x002ac260   (est. sk_swift_utf8_validate_and_advance)
 * Ghidra: void FUN_002ac260(void)
 * Validates a UTF-8 sequence and advances the per-cpu index: decodes the
 * leading byte, checks the continuation bytes / scalar value against the
 * canonical table (FUN_003d3550), and updates the shared cursor. Traps on
 * an invalid sequence.
 * Confidence: medium
 * Notes: Swift UTF-8 validation; SK_FATAL on invalid. */
sk_word16_t sk_swift_utf8_validate_and_advance(void)
{
    uint8_t *x19 = (uint8_t *)base_slot();
    uint64_t x21 = *(uint64_t *)(base_slot()+2);
    uint64_t x20 = *(uint64_t *)(base_slot()+3);
    FUN_00354a34();
    uint64_t u4 = 1;
    if (0 < 0) {
        uint64_t l8 = 0;
        do {
            if (l8 < 0) {
                FUN_0034f314(u4);
                FUN_003480ac();
                FUN_001afe4c();
            }
            uint8_t *pb = (uint8_t *)(x21 + l8);
            uint32_t lead = (uint32_t)*pb;
            uint8_t out = 0;
            uint64_t step;
            uint32_t val;
            if (*pb < 0xcc) {
                out = 0;
                step = 1;
                if (0xbf < lead) { step = 2; }
                val = 0;
            }
            else {
                uint32_t b1 = (uint32_t)pb[1];
                int lz = __builtin_clz((uint32_t)lead << 0x18 ^ 0xffffffff) - 24;
                if (lz == 2) {
                    val = (lead & 0x1f) << 6;
                    step = 2;
                }
                else if (lz == 3) {
                    val = (lead & 0xf) << 0xc | (b1 & 0x3f) << 6;
                    b1 = (uint32_t)pb[2];
                    step = 3;
                }
                else {
                    uint32_t b2 = b1 & 0x3f;
                    b1 = (uint32_t)pb[3];
                    val = (lead & 0xf) << 0x12 | b2 << 0xc | (pb[2] & 0x3f) << 6;
                    step = 4;
                }
                if (val < 0x300) {
                    val = 0;
                }
                else {
                    val = FUN_003d3550(val | b1 & 0x3f).lo;
                }
                u4 = 0;
                out = (uint8_t)(val >> 3);
                if (((val & 6) != 0) ||
                    ((val >> 3 & 0xff) != 0 && (val >> 3 & 0xff) < (uint32_t)*x19)) goto invalid;
            }
            *x19 = out;
            l8 = step + l8;
        } while (l8 < x20);
    }
    u4 = 1;
invalid:
    FUN_00354ef8(u4, 0);
    sk_word16_t r; r.lo = u4; r.hi = 0;
    return r;
}

/* FUN_002ac3bc @ 0x002ac3bc   (est. sk_swift_obj_service_rethrow)
 * Ghidra: void FUN_002ac3bc(undefined1 (*param_1) [16], undefined8 param_2..param_8)
 * Rethrows an error from the object-service layer: dispatches on the error
 * kind word (0x676518 vs others), invokes the error-owner destructor and
 * rebuilds the error payload, publishing the result into the caller's
 * 16-byte buffer. Runs the "unexpectedly found nil" fatal on a missing
 * payload.
 * Confidence: medium
 * Notes: SK_FATAL 0x1c2 (Swift.String); Swift error rethrow. */
void sk_swift_obj_service_rethrow(sk_word16_t *out, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    uint64_t l6 = *(uint64_t *)(p4 + -8);
    uint64_t extraout_x8 = 0;
    uint64_t local_90;
    FUN_00344e54((uint64_t)&extraout_x8, 0x656168, (uint64_t)&DAT_005a3680);
    if (p2 == 0x676518) {
        uint64_t u3 = FUN_00027754(p6).lo;
        FUN_00310c44();
        FUN_00077070((uint64_t)&local_90, 0);
        FUN_0006a4c0((uint64_t)&local_90, 0);
        FUN_0031b46c(0);
        FUN_0006a4c0((uint64_t)&local_90, 0);
        FUN_0031b49c(0);
        (*(void (*)(uint64_t, uint64_t))(uintptr_t)(l6 + 8))(p2, p4);
        sk_word16_t v = FUN_00298e58(p2, p4, p6);
        *out = v;
        return;
    }
    sk_word16_t v = FUN_001eb088(p2, 0, 1, p4);
    if (v.hi == 0) {
        SK_FATAL(0x1c2, (unsigned long)&s_Unexpectedly_found_nil_while_unw_005cd7d0, 0x39,
                 (unsigned long)&s_Swift_String_swift_005ce680, 0x12);
    }
    (*(void (*)(uint64_t, uint64_t))(uintptr_t)(l6 + 8))(p2, p4);
    *out = v;
}

/* FUN_002ac73c @ 0x002ac73c   (est. sk_swift_obj_new_error)
 * Ghidra: void FUN_002ac73c(undefined1 (*param_1) [16])
 * Produces a fresh error object word-pair via FUN_001eb73c.
 * Confidence: medium */
void sk_swift_obj_new_error(sk_word16_t *out)
{
    *out = FUN_001eb73c();
}

/* FUN_002ac764 @ 0x002ac764   (est. sk_swift_string_append_refs2)
 * Ghidra: void FUN_002ac764(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * String append wrapper: forwards the two operands and the per-cpu String
 * pair into FUN_001e9d8c.
 * Confidence: medium */
void sk_swift_string_append_refs2(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t *slot = (uint64_t *)base_slot();
    FUN_001e9d8c(p1, p2, slot[0], slot[1], p3);
}

/* FUN_002ac768 @ 0x002ac768   (est. sk_swift_string_append_refs3)
 * Ghidra: void FUN_002ac768(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * String append wrapper twin of 002ac764.
 * Confidence: medium */
void sk_swift_string_append_refs3(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t *slot = (uint64_t *)base_slot();
    FUN_001e9d8c(p1, p2, slot[0], slot[1], p3);
}

/* FUN_002ac784 @ 0x002ac784   (est. sk_swift_string_append_literal)
 * Ghidra: void FUN_002ac784(long param_1, undefined8 param_2..param_6)
 * Appends a String literal onto the current String: for the builtin kind
 * (0x676518) builds a literal storage pair (FUN_00346d38) and appends via
 * FUN_001e9d8c; otherwise delegates to FUN_0029b1e0.
 * Confidence: medium
 * Notes: Swift String literal append. */
void sk_swift_string_append_literal(uint64_t kind, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6)
{
    uint64_t *slot = (uint64_t *)base_slot();
    uint8_t auStack_60[16];
    if (kind == 0x676518) {
        FUN_001e9d8c(FUN_00346d38().lo, (uint64_t)&auStack_60, slot[0], slot[1], p4);
    }
    else {
        FUN_0029b1e0();
    }
}

/* FUN_002ac828 @ 0x002ac828   (est. sk_swift_string_new_empty)
 * Ghidra: void FUN_002ac828(undefined1 (*param_1) [16])
 * Produces a fresh empty String word-pair via FUN_0001a1c8.
 * Confidence: medium */
void sk_swift_string_new_empty(sk_word16_t *out)
{
    *out = FUN_0001a1c8();
}

/* FUN_002ac854 @ 0x002ac854   (est. sk_swift_array_release_pair)
 * Ghidra: undefined1 [16] FUN_002ac854(long param_1)
 * Releases the {key,value} pairs of a growable array: walks the array's
 * element slots, releasing each pair's references (merging word pairs where
 * needed), then frees the array header (FUN_0036b118). Returns the last
 * released {lo,hi} pair.
 * Confidence: medium
 * Notes: Swift array pair release; returns {lo,hi}. */
sk_word16_t sk_swift_array_release_pair(uint64_t arr)
{
    uint64_t n = *(uint64_t *)(arr + 0x10);
    sk_word16_t out;
    if (n == 0) {
        FUN_0036b118(arr);
        out.lo = 0;
        out.hi = 0xe000000000000000;
        return out;
    }
    uint64_t *p = (uint64_t *)(arr + 0x28);
    out.lo = 0;
    out.hi = 0xe000000000000000;
    do {
        sk_word16_t cur = out;
        uint64_t key = p[-1];
        uint64_t val = p[0];
        uint64_t curLo = cur.lo, curHi = cur.hi;
        uint64_t w = curLo & 0xffffffffffff;
        if ((curHi & 0x2000000000000000) != 0) { w = curHi >> 0x38 & 0xf; }
        if ((w == 0) && (((curLo & (curHi ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            thunk_FUN_0036b270(val);
            FUN_003a25d4(curHi);
            out.lo = key;
            out.hi = val;
        }
        else {
            uint64_t valW = val >> 0x38 & 0xf;
            uint64_t t;
            if ((curHi >> 0x3d & 1) == 0) {
                t = key & 0xffffffffffff;
                if ((val & 0x2000000000000000) != 0) { t = valW; }
            }
            else if ((val >> 0x3d & 1) == 0) {
                t = key & 0xffffffffffff;
            }
            else {
                sk_word16_t m = FUN_00291ee0(curLo, curHi, key, val);
                if (((uint)m.lo & 0xff) != 1) {
                    FUN_003a25d4(curHi);
                    out = m;
                    goto next_pair;
                }
                t = valW;
            }
            thunk_FUN_0036b270(val);
            FUN_002a4c98(key, val, 0, t);
            FUN_003a25d4(val);
            out = cur;
        }
next_pair:
        p = p + 2;
        n = n - 1;
    } while (n != 0);
    FUN_0036b118(arr);
    return out;
}

/* FUN_002ac99c @ 0x002ac99c   (est. sk_swift_obj_service_dispatch2)
 * Ghidra: void FUN_002ac99c(undefined8 param_1)
 * Second object-service dispatch guard: resolves the service type; on the
 * "special" kind it traps, otherwise it releases the object pair via
 * sk_swift_array_release_pair.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2ac9fc/aca00. */
void sk_swift_obj_service_dispatch2(uint64_t p1)
{
    uint64_t l2 = FUN_00002534(0x652b30, (uint64_t)&DAT_004c4010).lo;
    if (l2 == 0x6753a0) {
        SW_BREAK(0x2ac9fc);
    }
    if (l2 != 0x675c68) {
        sk_swift_array_release_pair(p1);
        return;
    }
    SW_BREAK(0x2aca00);
}

/* FUN_002aca00 @ 0x002aca00   (est. sk_swift_obj_service_dispatch3)
 * Ghidra: void FUN_002aca00(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Object-service dispatch: dispatches on the per-cpu service kind (via the
 * three method-table selectors), releasing the current object pair for the
 * task/thread kinds, parsing a pair stream for the String kind, and
 * publishing the result. Fatal on parse failure.
 * Confidence: medium
 * Notes: register-threaded object-service dispatch. */
void sk_swift_obj_service_dispatch3(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t *x19 = (uint64_t *)base_slot();
    uint64_t u2;
    uint64_t local_20 = 0, uStack_18 = 0, local_10 = 0, uStack_8 = 0;
    sk_word16_t r;
    FUN_00084220();
    FUN_00351a38();
    FUN_00349b3c();
    DAT_00658c00();
    FUN_0034ab10();
    FUN_0034f730();
    DAT_00658c00();
    FUN_0034b8bc();
    FUN_00352cb0();
    uint64_t kind1 = FUN_00352cb0().lo;
    if (kind1 != FUN_00352cb0().hi) {
        FUN_00354140();
        if (0 == 0) {
            FUN_002a3e64(x19[0], x19[1], x19[2], x19[3]);
            FUN_0034bd90();
            FUN_003a25d4();
            r = FUN_0006b6f4();
            goto done_dispatch3;
        }
        uint64_t l1 = FUN_0010084c().lo;
        if (0 == l1) {
            FUN_00084234(x19[0], 0);
            sk_swift_array_release_pair(p1);
            return;
        }
        FUN_0035a280();
        FUN_00350878();
        FUN_00353d64();
        FUN_003510a0((uint64_t)&local_20);
        uint64_t u2b = FUN_00365b6c().lo;
        if ((u2b & 1) == 0) {
            FUN_00350278();
            FUN_0035484c();
            FUN_003510c4((uint64_t)&local_20);
            u2b = FUN_00365b6c().lo;
            if ((u2b & 1) != 0) {
                FUN_003507e0(0);
                FUN_002a3e64(local_20, uStack_18, local_10, uStack_8);
                FUN_00351e08();
                FUN_003a25d4(uStack_8);
                goto done_dispatch3b;
            }
            local_20 = 0;
            uStack_18 = 0xe000000000000000;
            sk_word16_t v = FUN_003507e0();
            FUN_002a74f8(v.lo, v.hi, p3);
        }
        FUN_003507e0(0);
    }
done_dispatch3b:
    r = FUN_0007c1c4();
done_dispatch3:
    FUN_00084234(r.lo, r.hi, 0);
}

/* FUN_002acbb8 @ 0x002acbb8   (est. sk_swift_obj_release_slot)
 * Ghidra: void FUN_002acbb8(void)
 * Releases the object currently held in the per-cpu container slot: if the
 * held pair is a canonical empty (width 0 / unique flag set), releases both
 * words and clears the slot; otherwise it re-releases via the follow-up
 * path.
 * Confidence: medium
 * Notes: in-slice; Swift object slot release. */
void sk_swift_obj_release_slot(void)
{
    uint64_t *slot = (uint64_t *)base_slot();
    uint64_t u1 = slot[1];
    FUN_003598a0(slot[0]);
    if ((0 == 0) && (((0 & (u1 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        thunk_FUN_0036b270();
        FUN_003a25d4(u1);
        slot[0] = 0;
        slot[1] = 0;
        return;
    }
    FUN_00084180();
    FUN_00267820();
}

/* FUN_002acc20 @ 0x002acc20   (est. sk_swift_string_op_dispatch)
 * Ghidra: void FUN_002acc20(void)
 * String operation dispatch: selects among the four String operation kinds
 * (grown/indirect, small, and two merge variants) and dispatches to the
 * corresponding handler (FUN_002a55c0 / FUN_002a58b8 / FUN_002a6238 /
 * FUN_002a5bf0), validating the string bounds through FUN_002ab8ac.
 * Confidence: medium
 * Notes: register-threaded String op dispatch. */
void sk_swift_string_op_dispatch(void)
{
    uint64_t *slot = (uint64_t *)base_slot();
    uint64_t *x22 = slot + 2;
    FUN_00084220();
    FUN_0034f414();
    sk_word16_t r = FUN_00352cb0();
    uint64_t kind = 0;
    if (kind == r.lo) {
        FUN_00084180(r.lo, r.hi, slot[0], slot[1]);
        FUN_00354404();
        FUN_002ab8ac();
        FUN_00351e3c();
        FUN_00084234();
        FUN_002a55c0();
        return;
    }
    FUN_00354140();
    uint64_t kind2 = 0;
    if (kind2 != 0) {
        sk_word16_t v = FUN_0010084c();
        if (kind != v.lo) {
            FUN_00084180(v.lo, v.hi, slot[0], slot[1]);
            FUN_00354404();
            FUN_002ab8ac();
            FUN_00353a18();
            FUN_00084234();
            FUN_002a6238();
            return;
        }
        FUN_00084180(v.lo, v.hi, slot[0], slot[1]);
        FUN_00354404();
        sk_word16_t m = FUN_002ab8ac();
        FUN_00084234(m.lo, m.hi, x22[0], 0);
        FUN_002a5bf0();
        return;
    }
    FUN_00084180(r.lo, r.hi, slot[0], slot[1]);
    FUN_00354404();
    FUN_002ab8ac();
    FUN_0034f3b4();
    FUN_00084234();
    FUN_002a58b8();
}

/* FUN_002acd30 @ 0x002acd30   (est. sk_swift_string_op_dispatch2)
 * Ghidra: void FUN_002acd30(undefined8 param_1, undefined8 param_2, long param_3)
 * Second String operation dispatch: selects among the four String operation
 * kinds and dispatches to the corresponding scalar/character handler
 * (FUN_002a55c0 / FUN_002a58b8 / FUN_002a6238 / FUN_002a5bf0).
 * Confidence: medium
 * Notes: register-threaded String op dispatch (scalar variants). */
void sk_swift_string_op_dispatch2(uint64_t p1, uint64_t p2, uint64_t kind)
{
    uint64_t *x21 = (uint64_t *)base_slot();
    FUN_0008409c();
    FUN_00352cb0();
    if (kind == FUN_00352cb0().lo) {
        uint64_t u2 = FUN_0035ab08().lo;
        FUN_00351b78(u2, u2);
        FUN_002a55c0();
        return;
    }
    FUN_00354140();
    if (kind != 0) {
        uint64_t l1 = FUN_0010084c().lo;
        if (kind != l1) {
            uint64_t u2 = FUN_0035ab08().lo;
            FUN_003513f0(u2, u2);
            FUN_002a6238();
            return;
        }
        uint64_t u3 = x21[0];
        uint64_t u2 = FUN_0035ab08().lo;
        FUN_002a5bf0(u2, u2, u3);
        return;
    }
    uint64_t u2 = FUN_0035ab08().lo;
    FUN_003511f0(u2, u2);
    FUN_002a58b8();
}

/* FUN_002ace24 @ 0x002ace24   (est. sk_swift_string_next_scalar)
 * Ghidra: void FUN_002ace24(void)
 * Advances the per-cpu String iterator to the next Unicode scalar: resolves
 * the current scalar, checks for the end of the scalar sequence, decodes the
 * next scalar's width, and advances the cursor. Traps on malformed UTF-8 /
 * index overrun.
 * Confidence: medium
 * Notes: Swift String scalar iterator; SK_FATAL on bounds. */
void sk_swift_string_next_scalar(void)
{
    uint64_t *slot = (uint64_t *)base_slot();
    FUN_003565a8();
    uint64_t u1 = slot[0];
    uint64_t u2 = slot[1];
    FUN_003505c4();
    sk_word16_t v = FUN_00167404();
    uint64_t u8 = v.hi;
    uint64_t u6 = v.lo;
    uint64_t u7 = u6 >> 8 & 0x3f;
    uint64_t u10 = u2 >> 0x38 & 0xf;
    uint64_t u9 = u6 >> 0x10;
    if (u7 != 0) goto scalar_done;
    u8 = u1 & 0xffffffffffff;
    uint64_t u7b = u8;
    if ((u2 & 0x2000000000000000) != 0) { u7b = u10; }
    if (u6 >> 0xe == u7b * 4) {
        /* canonical empty scalar -> set to default and re-read */
        uint64_t w = 0;
        sk_word16_t acc;
        acc.lo = 0;
        acc.hi = u8;
        do {
            while (true) {
                if ((u2 >> 0x3c & 1) == 0) {
                    uint64_t byteOff = acc.lo + (u6 >> 0x10);
                    if ((byteOff & 0xffffffffffff) < u9) {
                        FUN_00347d60();
                        FUN_001afe4c();
                    }
                    uint64_t bptr;
                    if ((u2 >> 0x3d & 1) == 0) {
                        if ((u1 >> 0x3c & 1) == 0) {
                            FUN_000e15d8();
                            FUN_002a9ba8();
                            FUN_00351790();
                            bptr = 0;
                        }
                        else {
                            bptr = u1 & 0xffffffffffff;
                        }
                        FUN_00350494();
                    }
                    else {
                        FUN_00350494(acc.lo, acc.hi, (uint64_t)&slot);
                    }
                    FUN_003520dc();
                    sk_word16_t r = FUN_0028e8c0();
                    if (r.lo < 0 || r.hi > (int64_t)bptr) {
                        FUN_003481fc();
                        FUN_001afe4c();
                    }
                    FUN_00348e48();
                    FUN_001e4cbc();
                    FUN_000b43e8();
                    sk_word16_t g = FUN_002a200c();
                    FUN_000b4390(g.lo, g.hi, g.b[4] & 1);
                    thunk_FUN_002a2698();
                    FUN_000b43e8();
                    FUN_002a5400(u6, byteOff * 0x10000 | 1);
                    sk_word16_t r2 = FUN_000b4390();
                    FUN_00356590(r2.lo, r2.hi, 0);
                    return;
                }
                FUN_002bbcd8();
                FUN_000e15d8();
                sk_word16_t g = FUN_002a9ba8();
                u8 = g.hi;
                if (u9 + 1 == u8) goto scalar_done;
                if (g.lo == 0) {
                    FUN_00347f2c();
                    FUN_001afe4c();
                }
                uint16_t wc = *(uint16_t *)(g.lo + u9);
                FUN_00352bd4(wc);
                if (0 == 0) goto scalar_done;
                break;
            }
        } while (true);
    }
    else {
        if ((u2 >> 0x3c & 1) != 0) goto scalar_end;
        if ((u2 >> 0x3d & 1) == 0) {
            if ((u1 >> 0x3c & 1) != 0) {
                u8 = u8;
                u6 = (u2 & 0xfffffffffffffff) + 0x20;
            }
            goto scalar_read;
        }
        if (u9 + 1 == u10) goto scalar_done;
        uint16_t wc = *(uint16_t *)((uintptr_t)&slot + u9);
        FUN_00352bd4(wc);
        if (0 == 0) goto scalar_done;
scalar_end:
        FUN_0034d3d4();
        goto scalar_done;
    }
scalar_read:
    u8 = 0;
scalar_done:
    (void)u8;
}

/* FUN_002acfbc @ 0x002acfbc   (est. sk_swift_string_append_scalar_a)
 * Ghidra: void FUN_002acfbc(undefined8 param_1, undefined8 param_2)
 * Appends a scalar to the current String: validates via FUN_00354404 /
 * FUN_002ab8ac and commits via FUN_002a5400.
 * Confidence: medium */
void sk_swift_string_append_scalar_a(uint64_t p1, uint64_t p2)
{
    uint64_t *slot = (uint64_t *)base_slot();
    FUN_00354404(p1, p2, slot[0], slot[1]);
    FUN_002ab8ac();
    FUN_002a5400();
}

/* FUN_002acfc0 @ 0x002acfc0   (est. sk_swift_string_append_scalar_b)
 * Ghidra: void FUN_002acfc0(undefined8 param_1, undefined8 param_2)
 * Append scalar twin of 002acfbc.
 * Confidence: medium */
void sk_swift_string_append_scalar_b(uint64_t p1, uint64_t p2)
{
    uint64_t *slot = (uint64_t *)base_slot();
    FUN_00354404(p1, p2, slot[0], slot[1]);
    FUN_002ab8ac();
    FUN_002a5400();
}

/* FUN_002acfe0 @ 0x002acfe0   (est. sk_swift_string_release_a)
 * Ghidra: void FUN_002acfe0(ulong param_1)
 * Releases the current String if it owns a buffer (bit 0 set -> delegate to
 * FUN_002a539c); otherwise releases the slot's hi word and resets the slot
 * to the canonical empty {0, 0xe000000000000000}.
 * Confidence: medium
 * Notes: Swift String release. */
void sk_swift_string_release_a(uint64_t owns)
{
    uint64_t *slot = (uint64_t *)base_slot();
    if ((owns & 1) != 0) {
        FUN_002a539c();
        return;
    }
    FUN_003a25d4(slot[1]);
    slot[0] = 0;
    slot[1] = 0xe000000000000000;
}

/* FUN_002acfe4 @ 0x002acfe4   (est. sk_swift_string_release_b)
 * Ghidra: void FUN_002acfe4(ulong param_1)
 * String release twin of 002acfe0.
 * Confidence: medium */
void sk_swift_string_release_b(uint64_t owns)
{
    uint64_t *slot = (uint64_t *)base_slot();
    if ((owns & 1) != 0) {
        FUN_002a539c();
        return;
    }
    FUN_003a25d4(slot[1]);
    slot[0] = 0;
    slot[1] = 0xe000000000000000;
}

/* FUN_002ad02c @ 0x002ad02c   (est. sk_swift_string_new_substr)
 * Ghidra: void FUN_002ad02c(undefined1 (*param_1) [16], undefined8 *param_2, undefined8 param_3)
 * Produces a fresh Substring word-pair from a String pair via
 * thunk_FUN_001ed960.
 * Confidence: medium */
void sk_swift_string_new_substr(sk_word16_t *out, uint64_t *src, uint64_t p3)
{
    *out = thunk_FUN_001ed960(src[0], src[1], p3);
}

/* FUN_002ad060 @ 0x002ad060   (est. sk_swift_string_op_pair)
 * Ghidra: void FUN_002ad060(undefined1 (*param_1) [16])
 * Computes an object-service String operation pair via FUN_002aca00.
 * Confidence: medium */
void sk_swift_string_op_pair(sk_word16_t *out)
{
    FUN_002aca00();
    out->lo = 0;
    out->hi = 0;
}

/* FUN_002ad088 @ 0x002ad088   (est. sk_swift_string_release_slot)
 * Ghidra: void FUN_002ad088(undefined8 *param_1)
 * Releases a String held in a caller slot: releases the pair via
 * thunk_FUN_002acbb8 then decrements the hi word.
 * Confidence: medium */
void sk_swift_string_release_slot(uint64_t *p1)
{
    uint64_t u1 = p1[1];
    thunk_FUN_002acbb8(p1[0], u1);
    FUN_003a25d4(u1);
}

/* FUN_002ad0d4 @ 0x002ad0d4   (est. sk_swift_string_release_substr)
 * Ghidra: void FUN_002ad0d4(undefined8 *param_1, undefined8 *param_2)
 * Releases a Substring held in a slot: forwards the pair and the owner into
 * FUN_001bd66c then decrements the hi word.
 * Confidence: medium */
void sk_swift_string_release_substr(uint64_t *p1, uint64_t *p2)
{
    uint64_t u1 = p1[1];
    FUN_001bd66c(p1[0], u1, p2[0]);
    FUN_003a25d4(u1);
}

/* FUN_002ad10c @ 0x002ad10c   (est. sk_swift_string_op_dispatch3)
 * Ghidra: void FUN_002ad10c(undefined8 param_1, undefined8 *param_2, long param_3)
 * Third String operation dispatch: dispatches to FUN_002acd30 then invokes
 * the per-kind closure at param_3-8 + 8. Jumptable unrecovered.
 * Confidence: low
 * Notes: unrecovered jumptable at 0x2ad164. */
void sk_swift_string_op_dispatch3(uint64_t p1, uint64_t *p2, uint64_t p3)
{
    FUN_002acd30(p1, p2[0]);
    (*(void (*)(uint64_t, uint64_t))(uintptr_t)(*(uint64_t *)(p3 + -8) + 8))(p1, p3);
}

/* FUN_002ad1a0 @ 0x002ad1a0   (est. sk_swift_string_new_from_ptr)
 * Ghidra: void FUN_002ad1a0(undefined1 (*param_1) [16])
 * Produces a String word-pair from a raw pointer via FUN_00019858.
 * Confidence: medium */
void sk_swift_string_new_from_ptr(sk_word16_t *out)
{
    *out = FUN_00019858();
}

/* FUN_002ad1c8 @ 0x002ad1c8   (est. sk_swift_string_new_utf8)
 * Ghidra: void FUN_002ad1c8(undefined1 (*param_1) [16])
 * Produces a String word-pair from a UTF-8 buffer via FUN_001a4e10.
 * Confidence: medium */
void sk_swift_string_new_utf8(sk_word16_t *out)
{
    *out = FUN_001a4e10();
}

/* FUN_002ad1f8 @ 0x002ad1f8   (est. sk_swift_string_copy_a)
 * Ghidra: void FUN_002ad1f8(void)
 * Copies the current String (delegates to FUN_0027630c).
 * Confidence: medium */
void sk_swift_string_copy_a(void)
{
    FUN_0027630c();
}

/* FUN_002ad1fc @ 0x002ad1fc   (est. sk_swift_string_copy_b)
 * Ghidra: void FUN_002ad1fc(void)
 * Copies the current String (twin of 002ad1f8).
 * Confidence: medium */
void sk_swift_string_copy_b(void)
{
    FUN_0027630c();
}

/* FUN_002ad228 @ 0x002ad228   (est. sk_swift_string_fail_index)
 * Ghidra: void FUN_002ad228(void)
 * Raises the Swift index failure: calls the trap helpers then fatals.
 * Confidence: medium
 * Notes: noreturn via FUN_001afe4c. */
void sk_swift_string_fail_index(void)
{
    FUN_00348614(1);
    FUN_0034987c();
    FUN_001afe4c();
}

/* FUN_002ad274 @ 0x002ad274   (est. sk_swift_string_fail_bounds_a)
 * Ghidra: void FUN_002ad274(void)
 * Raises the Swift bounds failure (variant A): calls the trap helpers then
 * fatals.
 * Confidence: medium
 * Notes: noreturn via FUN_001afe4c. */
void sk_swift_string_fail_bounds_a(void)
{
    FUN_003488bc(1);
    FUN_003587e0();
    FUN_0034ae08();
    FUN_001afe4c();
}

/* FUN_002ad2c4 @ 0x002ad2c4   (est. sk_swift_string_fail_bounds_b)
 * Ghidra: void FUN_002ad2c4(void)
 * Raises the Swift bounds failure (variant B): identical to 002ad274.
 * Confidence: medium
 * Notes: noreturn via FUN_001afe4c. */
void sk_swift_string_fail_bounds_b(void)
{
    FUN_003488bc(1);
    FUN_003587e0();
    FUN_0034ae08();
    FUN_001afe4c();
}

/* FUN_002ad310 @ 0x002ad310   (est. sk_swift_fatal_range_0x168)
 * Ghidra: void FUN_002ad310(void)
 * Fatal error with selector 0x168: calls the precondition helper and the
 * stackshot-conclave fatal.
 * Confidence: medium
 * Notes: noreturn via FUN_001afa84. */
void sk_swift_fatal_range_0x168(void)
{
    FUN_00350d94(0x168);
    FUN_00353448();
    FUN_001afa84();
}

/* FUN_002ad358 @ 0x002ad358   (est. sk_swift_fatal_range_0x16d)
 * Ghidra: void FUN_002ad358(void)
 * Fatal error with selector 0x16d: twin of 002ad310.
 * Confidence: medium
 * Notes: noreturn via FUN_001afa84. */
void sk_swift_fatal_range_0x16d(void)
{
    FUN_00350d94(0x16d);
    FUN_00353448();
    FUN_001afa84();
}

/* FUN_002ad3a8 @ 0x002ad3a8   (est. sk_swift_float_to_int)
 * Ghidra: long FUN_002ad3a8(void)
 * Converts a floating-point value (from FUN_0034bb38) to a long, trapping
 * on NaN / out-of-range / overflow via the shared fatal path.
 * Confidence: medium
 * Notes: Swift Float-to-Int conversion; noreturn fatal on failure. */
int64_t sk_swift_float_to_int(void)
{
    float f = (float)FUN_0034bb38().lo;
    if (f <= 9.223372e18f) {
        if (f < 9.223372e18f) {
            return (int64_t)f;
        }
    }
    FUN_003488bc(1);
    FUN_003493d8();
    FUN_00351be0();
    FUN_001afe4c();
}

/* FUN_002ad450 @ 0x002ad450   (est. sk_swift_array_element_ptr)
 * Ghidra: void FUN_002ad450(void)
 * Returns / validates the element pointer of a growable array: if the header
 * count is negative (malformed), resolves via FUN_002ad480 and re-commits
 * through FUN_0019cac8.
 * Confidence: medium */
void sk_swift_array_element_ptr(void)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    if (*(int64_t *)((uintptr_t)x20 + 0x10) < 0) {
        uint64_t u1 = FUN_002ad480();
        FUN_0019cac8(1, u1);
    }
}

/* FUN_002ad454 @ 0x002ad454   (est. sk_swift_array_element_ptr2)
 * Ghidra: void FUN_002ad454(void)
 * Element-pointer helper twin of 002ad450.
 * Confidence: medium */
void sk_swift_array_element_ptr2(void)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    if (*(int64_t *)((uintptr_t)x20 + 0x10) < 0) {
        uint64_t u1 = FUN_002ad480();
        FUN_0019cac8(1, u1);
    }
}

/* FUN_002ad480 @ 0x002ad480   (est. sk_swift_array_element_ptr_resolve)
 * Ghidra: ulong FUN_002ad480(void)
 * Resolves the element-data pointer of a growable array: if the header count
 * is negative, computes the aligned data offset via FUN_00359c84; otherwise
 * traps on the malformed-header fatal.
 * Confidence: medium
 * Notes: SK_FATAL on malformed header. */
uint64_t sk_swift_array_element_ptr_resolve(void)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    if (*(int64_t *)((uintptr_t)x20 + 0x10) < 0) {
        FUN_00359c84();
        return 0;
    }
    FUN_003488bc(1);
    FUN_0034a6b0();
    FUN_001afe4c();
}

/* FUN_002ad4d8 @ 0x002ad4d8   (est. sk_swift_array_release_header_a)
 * Ghidra: void FUN_002ad4d8(void)
 * Releases an array element pointer then the header via FUN_00002834 /
 * FUN_0036b6ac.
 * Confidence: medium */
void sk_swift_array_release_header_a(void)
{
    FUN_002ad450();
    FUN_00002834();
    FUN_0036b6ac();
}

/* FUN_002ad4dc @ 0x002ad4dc   (est. sk_swift_array_release_header_b)
 * Ghidra: void FUN_002ad4dc(void)
 * Header release twin of 002ad4d8.
 * Confidence: medium */
void sk_swift_array_release_header_b(void)
{
    FUN_002ad450();
    FUN_00002834();
    FUN_0036b6ac();
}

/* FUN_002ad4fc @ 0x002ad4fc   (est. sk_swift_string_init_buffer)
 * Ghidra: long FUN_002ad4fc(long param_1, ulong param_2)
 * Allocates and initializes a String buffer of `param_1` bytes with
 * capacity `param_2`: computes the aligned allocation size (0x20 header +
 * inline space), allocates a typed object of kind 7 via FUN_0036a940,
 * initializes the header (+0x10 capacity word, +0x18 count), zeroes the
 * tail, and returns the buffer base. Traps on size arithmetic overflow.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2ad5c4..0x2ad608; Swift String buffer init. */
uint64_t sk_swift_string_init_buffer(int64_t count, uint64_t cap)
{
    if (count + 1 < count) { SW_BREAK(0x2ad5c4); }
    int64_t l1 = 8;
    if (count < 0x40) { l1 = 0; }
    int64_t l3 = count + 1 + l1;
    if (count + 1 + l1 < count + 1) { SW_BREAK(0x2ad5c8); }
    if (l3 + 0x20 < l3) { SW_BREAK(0x2ad5cc); }
    uint64_t u5;
    uint64_t base;
    if (l3 + 0x20 < 0x80) {
        u5 = (uint64_t)(l3 + 0x2f) & 0xfffffffffffffff0;
        if (u5 - 0x20 > u5) { SW_BREAK(0x2ad600); }
        base = FUN_0036a940(0x657248, u5, 7).lo;
    }
    else {
        if (l3 + 0x20 + 0xf < l3 + 0x20) { SW_BREAK(0x2ad608); }
        base = FUN_0036a940(0x657248, (uint64_t)(l3 + 0x2f) & 0xfffffffffffffff0, 7).lo;
        u5 = thunk_FUN_000126e8().lo;
        if (u5 - 0x20 > u5) { SW_BREAK(0x2ad5fc); }
    }
    if (!(u5 - 0x20 - l1 > u5 - 0x20)) {
        uint64_t u6 = 0x8000000000000000;
        if (count < 0x40) { u6 = 0; }
        u6 = ((u5 - 0x20) - l1) | u6;
        *(uint64_t *)(base + 0x10) = u6;
        *(uint64_t *)(base + 0x18) = cap;
        if ((int64_t)u6 < 0) {
            uint64_t *pu4 = (uint64_t *)(uintptr_t)FUN_002ad480();
            *pu4 = 0;
        }
        *(uint8_t *)(base + (cap & 0xffffffffffff) + 0x20) = 0;
        return base;
    }
    SW_BREAK(0x2ad604);
}

/* FUN_002ad608 @ 0x002ad608   (est. sk_swift_array_append_byte)
 * Ghidra: void FUN_002ad608(long param_1, byte param_2)
 * Appends a single byte to a growable array: advances the used count by
 * `param_1` and finalizes with FUN_002a2bb0, trapping on index overflow.
 * Confidence: medium
 * Notes: SW_BREAK at 0x2ad62c. */
void sk_swift_array_append_byte(uint64_t incr, uint8_t flag)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    uint64_t used = *(uint64_t *)((uintptr_t)x20 + 0x18) & 0xffffffffffff;
    if (used + incr < used) { SW_BREAK(0x2ad62c); }
    FUN_002a2bb0(used + incr, ((int64_t)*(uint64_t *)((uintptr_t)x20 + 0x18) < 0) & flag);
}

/* FUN_002ad62c @ 0x002ad62c   (est. sk_swift_string_byte_extent)
 * Ghidra: long FUN_002ad62c(undefined8 param_1, undefined8 param_2)
 * Computes the byte extent (offset delta) for a String builder: resolves the
 * builder header (FUN_00359c84), adds the canonical 0x20 offset, and returns
 * the total byte span used by the builder.
 * Confidence: medium
 * Notes: in-slice; Swift String builder extent. */
sk_word16_t sk_swift_string_byte_extent(uint64_t a, uint64_t b)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    uint64_t l1 = FUN_00359c84(*(uint64_t *)((uintptr_t)x20 + 0x18), a, b, b).lo;
    uint64_t u2 = FUN_003577b4().lo;
    FUN_0035ab20(u2, (FUN_00359c84().lo - l1) + 0x20);
    sk_word16_t r;
    r.lo = (FUN_00359c84().lo - l1) + 0x20;
    r.hi = 0;
    return r;
}

/* FUN_002ad668 @ 0x002ad668   (est. sk_swift_string_meta_release_a)
 * Ghidra: void FUN_002ad668(void)
 * Releases the two metadata words of a String builder (+0x10 and +0x28).
 * Confidence: medium */
void sk_swift_string_meta_release_a(void)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    FUN_0036b118(*(uint64_t *)((uintptr_t)x20 + 0x10));
    FUN_0036b118(*(uint64_t *)((uintptr_t)x20 + 0x28));
}

/* FUN_002ad66c @ 0x002ad66c   (est. sk_swift_string_meta_release_b)
 * Ghidra: void FUN_002ad66c(void)
 * Metadata release twin of 002ad668.
 * Confidence: medium */
void sk_swift_string_meta_release_b(void)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    FUN_0036b118(*(uint64_t *)((uintptr_t)x20 + 0x10));
    FUN_0036b118(*(uint64_t *)((uintptr_t)x20 + 0x28));
}

/* FUN_002ad68c @ 0x002ad68c   (est. sk_swift_string_meta_release_full)
 * Ghidra: void FUN_002ad68c(void)
 * Releases the full metadata of a String builder: if the first metadata word
 * is non-empty and the ownership flag (+0x30 bit 0) is clear, releases the
 * count word via FUN_00359208 first; then releases both metadata words.
 * Confidence: medium */
void sk_swift_string_meta_release_full(void)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    uint64_t l1 = *(uint64_t *)((uintptr_t)x20 + 0x10);
    if (l1 == 0) {
        if ((*(uint8_t *)((uintptr_t)x20 + 0x30) & 1) == 0) {
            FUN_00359208(*(uint64_t *)((uintptr_t)x20 + 0x18));
            l1 = *(uint64_t *)((uintptr_t)x20 + 0x10);
        }
        else {
            l1 = 0;
        }
    }
    FUN_0036b118(l1);
    FUN_0036b118(*(uint64_t *)((uintptr_t)x20 + 0x28));
}

/* FUN_002ad6d8 @ 0x002ad6d8   (est. sk_swift_string_meta_release_full2_a)
 * Ghidra: void FUN_002ad6d8(void)
 * Full metadata release then the shared release helper.
 * Confidence: medium */
void sk_swift_string_meta_release_full2_a(void)
{
    FUN_002ad68c();
    FUN_0036b6ac();
}

/* FUN_002ad6dc @ 0x002ad6dc   (est. sk_swift_string_meta_release_full2_b)
 * Ghidra: void FUN_002ad6dc(void)
 * Full metadata release twin of 002ad6d8.
 * Confidence: medium */
void sk_swift_string_meta_release_full2_b(void)
{
    FUN_002ad68c();
    FUN_0036b6ac();
}

/* FUN_002ad700 @ 0x002ad700   (est. sk_swift_dict_lookup_or_create)
 * Ghidra: long FUN_002ad700(void)
 * Looks up (or lazily creates) a value in a Swift Dictionary: resolves the
 * dictionary bucket pointer (FUN_0008409c / FUN_002ad480), and if the bucket
 * is empty lazily allocates a fresh value (FUN_0036a940 / FUN_0029db34),
 * storing it into the bucket. Returns the bucket's stored value.
 * Confidence: medium
 * Notes: Swift Dictionary lookup-or-insert. */
uint64_t sk_swift_dict_lookup_or_create(void)
{
    sk_word16_t v = FUN_0008409c();
    uint64_t *bucket;
    if (((v.lo & (v.hi ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0) {
        bucket = (uint64_t *)((v.hi & 0xfffffffffffffff) + 0x28);
    }
    else {
        bucket = (uint64_t *)(uintptr_t)FUN_002ad480();
    }
    uint64_t stored = *bucket;
    if (stored == 0) {
        FUN_00002834(0x657188);
        FUN_0036a940();
        FUN_00351d18();
        thunk_FUN_0036b270();
        FUN_00084180();
        FUN_0029db34();
        uint64_t l3 = *bucket;
        if (l3 == 0) {
            *bucket = 0;
            stored = stored;
        }
        else {
            FUN_0036b118(0);
            stored = l3;
        }
    }
    return stored;
}

/* FUN_002ad78c @ 0x002ad78c   (est. sk_swift_dict_find_slot)
 * Ghidra: void FUN_002ad78c(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Finds a Dictionary slot for the given key: walks the dictionary's bucket
 * array, decoding each bucket's key/value pair (including the small-integer
 * and short-string encodings) and comparing against the target. Returns the
 * matching bucket index, or -1 if absent.
 * Confidence: medium
 * Notes: Swift Dictionary slot find; -1 = not found. */
void sk_swift_dict_find_slot(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    uint64_t *x21 = x20 + 2;
    uint64_t l3 = FUN_00351e20().lo;
    uint64_t n = *(uint64_t *)(l3 + 0x10);
    int64_t l10 = 0;
    if (n != 0) {
        uint64_t l4 = FUN_00350b0c().lo;
        do {
            uint64_t *bucket = (uint64_t *)(l4 + 0x20 + l10 * 0x18);
            if ((*(uint8_t *)(bucket + 2) & 1) != 0) {
                FUN_003488bc(1);
                FUN_0034d6e8();
                FUN_00351be0();
                FUN_001afe4c();
            }
            if (*bucket == 0) {
                FUN_00348898(1);
                FUN_0034c978();
                FUN_00351be0();
                FUN_001afe4c();
            }
            uint64_t key = bucket[1];
            uint64_t val;
            if ((int64_t)key < 0) {
                FUN_0034846c();
                FUN_001afe4c();
            }
            if (key == 0) {
                key = 0;
                val = 0xe000000000000000;
            }
            else if (key < 0x10) {
                /* small integer key */
                key = key;
                val = 0;
            }
            else {
                if ((*(uint8_t *)(bucket + 2) & 2) != 0) {
                    key = key | 0xc000000000000000;
                }
                key = key | 0x1000000000000000;
                val = *bucket + 0x7fffffffffffffe0U | 0x8000000000000000;
            }
            if (key == x21[1] && val == x20[0]) {
                FUN_003a25d4(val);
                goto found;
            }
            if (((val ^ 0xffffffffffffffff) & 0x6000000000000000) == 0 &&
                (p3 & 0x6000000000000000) == 0x6000000000000000) {
                FUN_003a25d4(val);
            }
            else {
                FUN_0034d004();
                uint64_t u6 = FUN_002a0d50().lo;
                FUN_003a25d4(val);
                if ((u6 & 1) != 0) goto found;
            }
            l10 = l10 + 1;
        } while (l10 != (int64_t)n);
    }
    l10 = -1;
found:
    FUN_00351d30(l10, 0);
}

/* FUN_002ad95c @ 0x002ad95c   (est. sk_swift_dict_lookup_index)
 * Ghidra: void FUN_002ad95c(void)
 * Looks up a key in a Dictionary and returns its value index: resolves the
 * bucket array, finds the matching bucket (via FUN_0039a128), and reads the
 * value at the bucket's stored offset. Returns -1 if absent, else the value.
 * Confidence: medium
 * Notes: Swift Dictionary lookup; -1 = not found. */
void sk_swift_dict_lookup_index(void)
{
    FUN_00357ca0();
    uint64_t *x3 = (uint64_t *)0;
    FUN_00350a28();
    uint64_t bucket0 = FUN_0006b2ec().lo;
    uint64_t l4 = *x3;
    uint64_t u2 = FUN_0036b270().lo;
    bool isNeg = l4 == (uint64_t)-1;
    if (!isNeg) {
        FUN_0039a128((uint64_t)x3, (uint64_t)&DAT_002ada30, 0);
        u2 = 0;
    }
    FUN_0036b118(u2);
    uint64_t l4b = x3[1];
    uint64_t u2b;
    if (*(uint64_t *)(l4b + 0x10) == 0) {
        u2b = 0xffffffffffffffff;
    }
    else {
        thunk_FUN_0036b270(l4b);
        FUN_0007c1c4();
        sk_word16_t v = FUN_001f98e8();
        if ((v.hi & 1) == 0) {
            u2b = 0xffffffffffffffff;
        }
        else {
            u2b = *(uint64_t *)(*(uint64_t *)(l4b + 0x38) + v.lo * 8);
        }
        FUN_003a25d4(l4b);
    }
    FUN_000651bc(0);
    if (!isNeg) {
        FUN_0011d7e8();
    }
    FUN_00357c44(u2b, 0);
}

/* FUN_002ada34 @ 0x002ada34   (est. sk_swift_dict_rebuild_slots)
 * Ghidra: void FUN_002ada34(void)
 * Rebuilds a Dictionary's slot array from its bucket array: resolves the
 * bucket header, walks each bucket, decodes key/value pairs (small-int /
 * short-string / full forms), hashes each key (FUN_00258c60), and writes the
 * slot bitmap, key/value words, and index into the slot tables
 * (DAT_006577c8/d0/d8). Commits the new bucket count.
 * Confidence: medium
 * Notes: Swift Dictionary slot rebuild; writes global slot tables. */
void sk_swift_dict_rebuild_slots(void)
{
    sk_word16_t v = FUN_0035193c();
    uint64_t *x20 = (uint64_t *)(uintptr_t)v.lo;
    uint64_t l2 = *x20;
    uint64_t n = *(uint64_t *)(l2 + 0x10);
    uint64_t *out = (uint64_t *)(uintptr_t)x20[1];
    FUN_0036b270(l2);
    FUN_003a261c((uint64_t)&DAT_00657798);
    FUN_00002534((uint64_t)&LAB_00657688, (uint64_t)&DAT_004f2168);
    FUN_00077894(0);
    FUN_00258c60();
    if (n != 0) {
        FUN_0036b270(l2);
        uint64_t u15 = 0;
        do {
            if (*(uint64_t *)(l2 + 0x10) <= u15) {
                FUN_00348304();
                FUN_001afe4c();
            }
            uint64_t *bucket = (uint64_t *)(l2 + 0x20 + u15 * 0x18);
            if ((*(uint8_t *)(bucket + 2) & 1) != 0) {
                FUN_003488bc(1);
                FUN_0034d6e8();
                FUN_00351be0();
                FUN_001afe4c();
            }
            if (*bucket == 0) {
                FUN_00348898(1);
                FUN_0034c978();
                FUN_00351be0();
                FUN_001afe4c();
            }
            uint64_t key = bucket[1];
            uint64_t val;
            if ((int64_t)key < 0) {
                FUN_0034846c();
                FUN_001afe4c();
            }
            if (key == 0) {
                key = 0;
                val = 0xe000000000000000;
            }
            else if (key < 0x10) {
                key = key;
                val = 0;
            }
            else {
                if ((*(uint8_t *)(bucket + 2) & 2) != 0) {
                    key = key | 0xc000000000000000;
                }
                key = key | 0x1000000000000000;
                val = *bucket + 0x7fffffffffffffe0U | 0x8000000000000000;
            }
            FUN_003a261c((uint64_t)&DAT_00657798);
            FUN_000e15d8();
            FUN_001f98e8();
            uint64_t u9 = FUN_000775b8().lo;
            uint64_t hash = FUN_00258c60(0, 0, 0).lo;
            if ((hash & 1) != 0) {
                FUN_000e15d8();
                FUN_001f98e8();
                FUN_00077604();
            }
            if ((0 & 1) == 0) {
                DAT_006577d8[u9 >> 6] = DAT_006577d8[u9 >> 6] | 1L << (u9 & 0x3f);
                uint64_t *sl = (uint64_t *)(DAT_006577c8 + u9 * 0x10);
                sl[0] = key;
                sl[1] = val;
                *(uint64_t *)(DAT_006577d0 + u9 * 8) = u15;
                DAT_006577a8 = DAT_006577a8 + 1;
            }
            else {
                FUN_003a25d4(val);
                *(uint64_t *)(DAT_006577d0 + u9 * 8) = u15;
                DAT_006577a8 = DAT_006577a8;
            }
            u15 = u15 + 1;
        } while (u15 != n);
        FUN_0036b118(l2);
    }
    *out = (uint64_t)&DAT_00657798;
    FUN_00351774(l2, v.hi);
    FUN_0036b118();
}

/* FUN_002adcf8 @ 0x002adcf8   (est. sk_swift_dict_sync_buckets)
 * Ghidra: void FUN_002adcf8(void)
 * Re-synchronizes the Dictionary bucket tables (three passes through the
 * shared hash/insert helpers).
 * Confidence: medium */
void sk_swift_dict_sync_buckets(void)
{
    FUN_0009461c();
    FUN_000a93e4();
    FUN_0009461c();
}

/* FUN_002add28 @ 0x002add28   (est. sk_swift_dict_set_capacity)
 * Ghidra: void FUN_002add28(undefined8 param_1, undefined1 param_2)
 * Sets a Dictionary's capacity: releases the old capacity word, stores the
 * new capacity and a flag word into the header.
 * Confidence: medium */
void sk_swift_dict_set_capacity(uint64_t cap, uint8_t flag)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    FUN_000a9454(*(uint64_t *)((uintptr_t)x20 + 0x18), *(uint8_t *)((uintptr_t)x20 + 0x20));
    *(uint64_t *)((uintptr_t)x20 + 0x18) = cap;
    *(uint8_t *)((uintptr_t)x20 + 0x20) = flag;
}

/* FUN_002add84 @ 0x002add84   (est. sk_swift_dict_new_bucket)
 * Ghidra: void FUN_002add84(long param_1)
 * Creates a fresh Dictionary bucket: builds a new empty bucket descriptor
 * (FUN_002addc0) and stores its flag into the caller's bucket at +0x20.
 * Confidence: medium */
void sk_swift_dict_new_bucket(uint64_t bucket)
{
    uint8_t auStack_48[32];
    uint8_t local_28;
    FUN_002addc0();
    FUN_003551f8();
    *(uint8_t *)(bucket + 0x20) = local_28;
}

/* FUN_002addc0 @ 0x002addc0   (est. sk_swift_dict_new_bucket_desc)
 * Ghidra: void FUN_002addc0(void)
 * Builds a new empty Dictionary bucket descriptor: resolves the storage,
 * packs the {empty,key,index,count,flags} fields, and writes them into the
 * caller's 40-byte descriptor buffer. Handles both small-string and
 * grown-buffer key encodings.
 * Confidence: medium
 * Notes: Swift Dictionary bucket descriptor build. */
void sk_swift_dict_new_bucket_desc(void)
{
    uint64_t *x20 = (uint64_t *)base_slot();
    uint64_t *x21 = x20 + 2;
    FUN_00357cb4();
    sk_word16_t v = FUN_0035098c();
    bool small = (v.hi & 0x2000000000000000) == 0;
    uint64_t u2 = v.lo & 0xffffffffffff;
    if (!small) { u2 = v.hi >> 0x38 & 0xf; }
    uint8_t b1 = v.b[7] >> 7;
    if (!small) { b1 = v.b[0xf] >> 6 & 1; }
    FUN_002a49d4();
    uint64_t u4 = FUN_00351db4().lo;
    uint64_t u6 = 0;
    if (!small) { u6 = u4; }
    uint64_t u4b;
    uint8_t b5;
    if ((x20[0] >> 0x3d & 1) == 0) {
        if ((x20[0] >> 0x3e & 1) == 0) {
            if ((int64_t)x20[0] < 0) {
                u4b = FUN_003542dc().lo;
                b5 = 2;
            }
            else {
                if ((x21[0] >> 0x3d & 1) == 0) {
                    FUN_00350d94(0x73);
                    FUN_00353448();
                    FUN_001afa84();
                }
                u4b = FUN_0036b270(x20[0] & 0xfffffffffffffff).lo;
                b5 = 1;
            }
        }
        else {
            u4b = FUN_0036b270(x20[0] & 0xfffffffffffffff).lo;
            b5 = 0;
        }
    }
    else {
        u4b = 0;
        b5 = 3;
        u6 = 0xf;
    }
    uint8_t *desc = (uint8_t *)(uintptr_t)FUN_00357cb4().lo;
    desc[0] = b1;
    *(uint64_t *)(desc + 8) = u2;
    *(uint64_t *)(desc + 0x10) = u6;
    *(uint64_t *)(desc + 0x18) = u4b;
    desc[0x20] = b5;
    FUN_00357c74(0);
}

/* FUN_002ade9c @ 0x002ade9c   (est. sk_swift_unsafe_rawpointer_init)
 * Ghidra: ulong FUN_002ade9c(undefined8 param_1, undefined8 param_2, long param_3, ulong param_4, undefined8 param_5)
 * Swift UnsafeMutableRawPointer initializer: validates that the buffer
 * [param_3, param_3 + param_3*stride) does not overflow the source object's
 * bounds, returning param_4 on success. Runs the UnsafeMutableRawPointer
 * init and index-out-of-bounds fatals on violation.
 * Confidence: medium
 * Notes: SK_FATAL 0xd6/0xd7 (UnsafeMutableRawPointer init). */
uint64_t sk_swift_unsafe_rawpointer_init(uint64_t p1, uint64_t p2, int64_t p3, uint64_t p4, uint64_t p5)
{
    uint64_t *x16 = (uint64_t *)(uintptr_t)FUN_0034a834().lo;
    if (p3 < 0) {
        FUN_003488bc(1);
        FUN_0034a834();
    }
    else {
        FUN_003509c8(p5);
        int64_t stride = *(int64_t *)((uintptr_t)x16 + 0x48);
        int64_t off = p3 * stride;
        if (p4 + off <= 0 || 0 + off <= p4) {
            FUN_0035b67c(p4);
            return p4;
        }
        FUN_003488bc(1);
        FUN_0034a834();
    }
    sk_word16_t v = FUN_00356524();
    uint64_t u2 = v.hi;
    uint64_t code;
    if ((int64_t)u2 < 0) {
        FUN_0035047c();
        code = 0xd6;
    }
    else {
        if ((p3 != 0) && (u2 < (uint64_t)(0 - p3))) {
            *(char *)(p3 + u2) = v.b[0];
            return v.lo;
        }
        FUN_0035047c();
        code = 0xd7;
    }
    FUN_003486b8(code);
    FUN_00349644();
    FUN_000dbde8();
    FUN_001afe4c();
}

/* FUN_002adf54 @ 0x002adf54   (est. sk_swift_unsafe_rawpointer_store)
 * Ghidra: void FUN_002adf54(undefined1 param_1, ulong param_2, long param_3, long param_4)
 * Stores a byte into an UnsafeMutableRawPointer range: validates [param_2,
 * param_3+param_2) against [param_3, param_4) and writes the byte, running
 * the index-out-of-bounds fatal on violation.
 * Confidence: medium
 * Notes: SK_FATAL 0xd6/0xd7. */
void sk_swift_unsafe_rawpointer_store(uint8_t byte, uint64_t off, int64_t base, int64_t bound)
{
    uint64_t code;
    if ((int64_t)off < 0) {
        FUN_0035047c();
        code = 0xd6;
    }
    else {
        if ((base != 0) && (off < (uint64_t)(bound - base))) {
            *(uint8_t *)(base + off) = byte;
            return;
        }
        FUN_0035047c();
        code = 0xd7;
    }
    FUN_003486b8(code);
    FUN_00349644();
    FUN_000dbde8();
    FUN_001afe4c();
}

/* FUN_002adfb4 @ 0x002adfb4   (est. sk_swift_string_scalar_advance)
 * Ghidra: ulong FUN_002adfb4(void)
 * Advances a String scalar index by one encoded unit: resolves the current
 * encoded offset, dispatches on the buffer kind, and returns the packed
 * index word.
 * Confidence: medium
 * Notes: Swift String scalar advance. */
uint64_t sk_swift_string_scalar_advance(void)
{
    uint64_t *x19 = (uint64_t *)base_slot();
    uint64_t *x20 = x19 + 2;
    uint64_t *x21 = x20 + 2;
    FUN_00350a28();
    uint64_t u1 = FUN_00167404().lo;
    uint64_t u21 = 0;
    if ((x19[0] >> 0x3c & 1) == 0) {
        u21 = u1 >> 0x10;
        if ((x19[0] >> 0x3d & 1) != 0) {
            FUN_00354fac();
            goto have_off;
        }
        if ((x20[0] >> 0x3c & 1) != 0) {
            FUN_00356364();
            goto have_off;
        }
    }
    else {
        FUN_002a49a8();
    }
    FUN_0007c1c4();
    FUN_002a9ba8();
have_off:
    FUN_0034b3f8();
    return (u21 + FUN_0034b3f8().lo) * 0x10000 | 5;
}

/* FUN_002ae028 @ 0x002ae028   (est. sk_swift_utf8_char_width)
 * Ghidra: undefined4 FUN_002ae028(long param_1, ulong param_2, ulong param_3)
 * Returns the UTF-8 encoded width (1..4) of the byte at offset `param_1` of
 * the String storage pair (param_2=lo, param_3=hi). Resolves the buffer
 * pointer for inline/small or grown forms and decodes the leading-byte
 * length.
 * Confidence: medium
 * Notes: Swift UTF-8 character width. */
uint32_t sk_swift_utf8_char_width(int64_t off, uint64_t sLo, uint64_t sHi)
{
    uint8_t b1;
    if ((sHi >> 0x3d & 1) == 0) {
        uint64_t bptr;
        if ((sLo >> 0x3c & 1) == 0) {
            FUN_00106e3c();
            bptr = FUN_002a9ba8().lo;
        }
        else {
            bptr = FUN_003576c8().lo;
        }
        b1 = *(uint8_t *)(bptr + off);
    }
    else {
        b1 = *(uint8_t *)((uintptr_t)&sLo + off);
    }
    uint32_t w = 31 - __builtin_clz((uint32_t)b1 << 0x18 ^ 0xffffffff);
    if ((int8_t)b1 >= 0) { w = 1; }
    return w;
}

/* FUN_002ae098 @ 0x002ae098   (est. sk_swift_utf8_next_char)
 * Ghidra: ulong FUN_002ae098(void)
 * Decodes the next Unicode scalar from the per-cpu String and returns its
 * packed index: resolves the current scalar, walks the UTF-8 continuation
 * bytes, and returns the value. Traps on a malformed leading byte.
 * Confidence: medium
 * Notes: Swift UTF-8 next-char decode. */
sk_word16_t sk_swift_utf8_next_char(void)
{
    uint64_t *x19 = (uint64_t *)base_slot();
    uint64_t *x20 = x19 + 2;
    FUN_002a49a8();
    FUN_00350a28();
    uint64_t u2 = FUN_00167404().lo;
    if ((x19[0] >> 0x3c & 1) != 0) {
        FUN_0035646c();
        FUN_0034883c();
        FUN_001afa84();
    }
    uint64_t scalar;
    if ((x19[0] >> 0x3d & 1) == 0) {
        uint64_t bptr;
        if ((x20[0] >> 0x3c & 1) == 0) {
            FUN_0007c1c4();
            bptr = FUN_002a9ba8().lo;
        }
        else {
            bptr = FUN_00356364().lo;
        }
        scalar = FUN_00355da8(bptr + (u2 >> 0x10)).lo;
        if (0 >= 0) { sk_word16_t r; r.lo=scalar; r.hi=0; return r; }
        scalar = FUN_0034b848().lo;
        switch (0) {
        case 1: { sk_word16_t r; r.lo=FUN_0034fbb0().lo; r.hi=0; return r; }
        case 2: { uint64_t c = FUN_0034cec4().lo; sk_word16_t r; r.lo=(c & 0xffffffc0)|0; r.hi=0; return r; }
        case 3: { uint64_t c = FUN_0034a018().lo; sk_word16_t r; r.lo=(c & 0xffffffc0)|0; r.hi=0; return r; }
        }
        { sk_word16_t r; r.lo=scalar; r.hi=0; return r; }
    }
    scalar = FUN_00355da8(0 + (u2 >> 0x10)).lo;
    if (0 >= 0) { sk_word16_t r; r.lo=scalar; r.hi=0; return r; }
    scalar = FUN_0034b848().lo;
    switch (0) {
    case 1: { sk_word16_t r; r.lo=FUN_0034fbb0().lo; r.hi=0; return r; }
    case 2: { uint64_t c = FUN_0034cec4().lo; sk_word16_t r; r.lo=(c & 0xffffffc0)|0; r.hi=0; return r; }
    case 3: { uint64_t c = FUN_0034a018().lo; sk_word16_t r; r.lo=(c & 0xffffffc0)|0; r.hi=0; return r; }
    }
    { sk_word16_t r; r.lo=scalar; r.hi=0; return r; }
}

/* FUN_002ae1ac @ 0x002ae1ac   (est. sk_swift_utf8_decode_char)
 * Ghidra: undefined1 [16] FUN_002ae1ac(long param_1, ulong param_2, ulong param_3)
 * Decodes the Unicode scalar at offset `param_1` of the String storage pair,
 * returning a {scalar, width} pair. Resolves the buffer pointer, decodes the
 * leading byte, and assembles the scalar with its encoded width.
 * Confidence: medium
 * Notes: Swift UTF-8 scalar decode; returns {value,width}. */
sk_word16_t sk_swift_utf8_decode_char(int64_t off, uint64_t sLo, uint64_t sHi)
{
    sk_word16_t out;
    uint64_t scalar;
    uint64_t width;
    if ((sHi >> 0x3c & 1) != 0) {
        FUN_0035646c();
        FUN_0034883c();
        FUN_001afa84();
    }
    if ((sHi >> 0x3d & 1) == 0) {
        uint64_t bptr;
        if ((sLo >> 0x3c & 1) == 0) {
            FUN_00106e3c();
            bptr = FUN_002a9ba8().lo;
        }
        else {
            bptr = FUN_003576c8().lo;
        }
        scalar = FUN_00355da8(bptr + off).lo;
        if (0 < 0) {
            scalar = FUN_0034b848().lo;
            uint64_t w;
            switch (0) {
            case 1:
                scalar = FUN_00353ff4().lo;
                scalar = (scalar & 0x1f) << 6 | (scalar & 0x3f);
                width = 2;
                goto pack;
            case 2:
                scalar = FUN_0034cec4().lo;
                scalar = (scalar & 0xffffffc0) | (scalar & 0x3f);
                width = 3;
                goto pack;
            case 3:
                scalar = FUN_0034a018().lo;
                scalar = (scalar & 0xffffffc0) | (scalar & 0x3f);
                width = 4;
                goto pack;
            }
            width = 1;
        } else {
            width = 1;
        }
    }
    else {
        scalar = FUN_00355da8((int64_t)&sLo + off).lo;
        if (0 < 0) {
            scalar = FUN_0034b848().lo;
            uint64_t w;
            switch (0) {
            case 1: { scalar = FUN_00353ff4().lo; scalar = (scalar & 0x1f) << 6 | (scalar & 0x3f); width = 2; goto pack; }
            case 2: { scalar = FUN_0034cec4().lo; scalar = (scalar & 0xffffffc0) | (scalar & 0x3f); width = 3; goto pack; }
            case 3: { scalar = FUN_0034a018().lo; scalar = (scalar & 0xffffffc0) | (scalar & 0x3f); width = 4; goto pack; }
            }
            width = 1;
        } else {
            width = 1;
        }
    }
pack:
    out.hi = width;
    out.lo = scalar;
    return out;
}

/* FUN_002ae2c0 @ 0x002ae2c0   (est. sk_swift_string_scalar_prev)
 * Ghidra: undefined1 [16] FUN_002ae2c0(ulong param_1, long param_2, ulong param_3, ulong *param_4, ulong param_5)
 * Steps a String index backward by `param_2` Unicode scalars, walking the
 * UTF-8 bytes and returning the resulting {packed-index, success} pair.
 * Handles both inline and grown buffers, running the
 * StringUnicodeScalarView index-out-of-bounds fatal on overrun.
 * Confidence: medium
 * Notes: SK_FATAL 0x84/0xe5/0xec (StringUnicodeScalarView). */
sk_word16_t sk_swift_string_scalar_prev(uint64_t p1, int64_t p2, uint64_t p3, uint64_t *p4, uint64_t p5)
{
    sk_word16_t out;
    uint64_t u10 = (p4[0] >> 0x3b) & 1;
    if ((p5 & 0x1000000000000000) == 0) { u10 = 1; }
    if ((p3 & 0xc) == 4L << u10) { p3 = FUN_0001da84(p3, p4[0], p5).lo; }
    uint64_t u3 = p1;
    if ((p1 & 0xc) == 4L << u10) { u3 = FUN_0001da84(p1, p4[0], p5).lo; }
    uint64_t u4 = FUN_002ab130(p1, p4[0], p5).lo;
    uint64_t u3b = u3 >> 0xe;
    uint64_t u9 = 0;
    if (p2 < 0) {
        p3 = p3 >> 0xe;
        uint64_t u8 = u4;
        for (int64_t l13 = 0; p2 < l13; l13 = l13 - 1) {
            if (p3 <= u3b && u4 >> 0xe <= p3) goto scalar_found;
            u4 = u4 >> 0x10;
            if (u4 == 0) goto fatal_ec;
            if ((p5 >> 0x3c & 1) != 0) {
                uint64_t *pu = (uint64_t *)(uintptr_t)FUN_002ae098(u8, p4[0], p5).lo;
                uint64_t sv = p4[0], sh = p4[1];
                sk_word16_t idx = FUN_002ab130(*pu, sv, sh);
                u8 = idx.lo;
                if (u8 >> 0xe == 0) {
                    SK_FATAL(0x84, (unsigned long)&s_String_index_is_out_of_bounds_005ce6a0, 0x1d,
                             (unsigned long)&s_Swift_StringUnicodeScalarView_sw_005ce6c0, 0x23);
                }
                if ((sh >> 0x3c & 1) == 0) {
                    if ((sh >> 0x3d & 1) != 0) {
                        u4 = (u8 >> 0x10) * 0x10000;
                    }
                    else if ((sv >> 0x3c & 1) == 0) {
                        FUN_002ae098(u8, sv, sh);
                        sk_word16_t g = FUN_002a9ba8(sv, sh);
                        uint64_t bptr = g.lo;
                        int64_t back = 0;
                        do {
                            back = back - 1;
                        } while (*(int8_t *)(bptr + (u8 >> 0x10) + back) < -0x40);
                        u4 = (uint64_t)((int64_t)(u8 >> 0x10) + back) << 0x10 | 5;
                    }
                }
                else {
                    FUN_002ae098(u8, sv, sh);
                }
            }
            else {
                uint64_t l6;
                if ((p5 >> 0x3d & 1) == 0) {
                    l6 = (p5 & 0xfffffffffffffff) + 0x20;
                    if ((p4[0] >> 0x3c & 1) == 0) {
                        l6 = FUN_002a9ba8(p4[0], p5).lo;
                    }
                    int64_t back = 0;
                    do {
                        back = back - 1;
                    } while (*(int8_t *)(l6 + (u4 >> 0x10) + back) < -0x40);
                    u4 = (uint64_t)((int64_t)(u4 >> 0x10) + back) << 0x10 | 5;
                }
                else {
                    u4 = ((u4 >> 0x10) - 1) << 0x10 | 5;
                }
            }
        }
        if (u3b < p3 || p3 <= u4 >> 0xe) goto scalar_nf;
    }
    else {
        p3 = p3 >> 0xe;
        uint64_t u8 = p4[0] & 0xffffffffffff;
        if ((p5 & 0x2000000000000000) != 0) { u8 = p5 >> 0x38 & 0xf; }
        for (; p2 != 0; p2 = p2 - 1) {
            if (u3b <= p3 && p3 <= u4 >> 0xe) goto scalar_found;
            u4 = u4 >> 0x10;
            if (u8 <= u4) {
                SK_FATAL(0xe5, (unsigned long)&s_String_index_is_out_of_bounds_005ce6a0, 0x1d,
                         (unsigned long)&s_Swift_StringUnicodeScalarView_sw_005ce6c0, 0x23);
            }
            if ((p5 >> 0x3c & 1) != 0) {
                FUN_002a49a8();
fatal_ec:
                SK_FATAL(0xec, (unsigned long)&s_String_index_is_out_of_bounds_005ce6a0, 0x1d,
                         (unsigned long)&s_Swift_StringUnicodeScalarView_sw_005ce6c0, 0x23);
            }
            uint8_t b1;
            uint64_t l5;
            if ((p5 >> 0x3d & 1) == 0) {
                l5 = (p5 & 0xfffffffffffffff) + 0x20;
                if ((p4[0] >> 0x3c & 1) == 0) {
                    l5 = FUN_002a9ba8(p4[0], p5).lo;
                }
                b1 = *(uint8_t *)(l5 + u4);
            }
            else {
                b1 = *(uint8_t *)((uintptr_t)&p4[0] + u4);
            }
            uint32_t w = 31 - __builtin_clz((uint32_t)b1 << 0x18 ^ 0xffffffff);
            if ((int8_t)b1 >= 0) { w = 1; }
            u4 = (u4 + w) * 0x10000 | 5;
        }
        if (p3 < u3b || u4 >> 0xe <= p3) goto scalar_nf;
    }
scalar_found:
    out.lo = 0;
    out.hi = 1;
    return out;
scalar_nf:
    out.lo = 0;
    out.hi = 0;
    return out;
}

/* FUN_002ae6d4 @ 0x002ae6d4   (est. sk_swift_string_scalar_prev_one)
 * Ghidra: void FUN_002ae6d4(ulong *param_1)
 * Steps a String index back one Unicode scalar (twin of the backward path):
 * validates the index, walks back over continuation bytes, and stores the
 * resulting packed index into *param_1.
 * Confidence: medium
 * Notes: Swift String scalar-prev; SK_FATAL 0x84. */
void sk_swift_string_scalar_prev_one(uint64_t *p1)
{
    uint64_t *slot = (uint64_t *)base_slot();
    uint64_t u1 = slot[0], u2 = slot[1];
    uint64_t u4 = FUN_002ab130(*p1, u1, u2).lo;
    if (u4 >> 0xe == 0) {
        SK_FATAL(0x84, (unsigned long)&s_String_index_is_out_of_bounds_005ce6a0, 0x1d,
                 (unsigned long)&s_Swift_StringUnicodeScalarView_sw_005ce6c0, 0x23);
    }
    int64_t back;
    if ((u2 >> 0x3c & 1) == 0) {
        if ((u2 >> 0x3d & 1) != 0) {
            back = 1;
            goto store;
        }
        uint64_t bptr;
        if ((u1 >> 0x3c & 1) == 0) {
            FUN_002ae098(u4, u1, u2);
            bptr = FUN_002a9ba8(u1, u2).lo;
        }
        else {
            bptr = (u2 & 0xfffffffffffffff) + 0x20;
        }
        back = 0;
        do {
            back = back - 1;
        } while (*(int8_t *)(bptr + (u4 >> 0x10) + back) < -0x40);
        back = -back;
    }
    else {
        FUN_002ae098(u4, u1, u2);
        back = 1;
    }
store:
    *p1 = (u4 + back * -0x10000) & 0xffffffffffff0000 | 5;
}

/* FUN_002ae818 @ 0x002ae818   (est. sk_swift_string_scalar_next)
 * Ghidra: void FUN_002ae818(void)
 * Advances a String scalar index forward by one and stores it into *unaff_x19
 * (delegates through FUN_002a9f3c).
 * Confidence: medium */
void sk_swift_string_scalar_next(void)
{
    uint64_t *x19 = (uint64_t *)base_slot();
    FUN_00350258();
    uint64_t u1 = FUN_002a9f3c().lo;
    *x19 = u1;
}

/* FUN_002ae858 @ 0x002ae858   (est. sk_swift_string_scalar_step)
 * Ghidra: void FUN_002ae858(void)
 * Steps a String scalar index by a fixed amount via FUN_002a9d64.
 * Confidence: medium */
void sk_swift_string_scalar_step(void)
{
    FUN_00359424();
    FUN_002a9d64();
}

/* FUN_002ae880 @ 0x002ae880   (est. sk_swift_unicode_scalar_decode)
 * Ghidra: undefined1 [16] FUN_002ae880(uint *param_1, undefined8 *param_2)
 * Decodes the Unicode scalar at the current index of the String storage pair,
 * returning the {scalar,pointer} pair and storing the scalar into *param_1.
 * Dispatches on the buffer kind, decoding 1-4 byte sequences.
 * Confidence: medium
 * Notes: Swift UnicodeScalar decode; SK_FATAL 0xfd (UnicodeHelpers). */
sk_word16_t sk_swift_unicode_scalar_decode(uint32_t *out, uint64_t *src)
{
    uint64_t *slot = (uint64_t *)base_slot();
    uint64_t u1 = slot[0], u2 = slot[1];
    uint64_t u4 = FUN_00167404(*src, u1, u2).lo;
    if ((u2 >> 0x3c & 1) != 0) {
        SK_FATAL(0xfd, (unsigned long)&s_Fatal_error_005accd0, 0xb,
                 (unsigned long)&s_Swift_UnicodeHelpers_swift_005ce730, 0x1a);
    }
    uint8_t *pb;
    if ((u2 >> 0x3d & 1) != 0) {
        pb = (uint8_t *)((uintptr_t)&u1 + (u4 >> 0x10));
    }
    else {
        uint64_t bptr;
        if ((u1 >> 0x3c & 1) == 0) {
            bptr = FUN_002a9ba8(u1, u2).lo;
        }
        else {
            bptr = (u2 & 0xfffffffffffffff) + 0x20;
        }
        pb = (uint8_t *)(bptr + (u4 >> 0x10));
    }
    uint32_t lead = (uint32_t)*pb;
    uint32_t scalar;
    if ((int8_t)*pb < 0) {
        int lz = __builtin_clz((uint32_t)lead << 0x18 ^ 0xffffffff) - 24;
        switch (lz) {
        case 2:
            scalar = (pb[1] & 0x3f) | (lead & 0x1f) << 6;
            break;
        case 3:
            scalar = (lead & 0xf) << 0xc | (pb[1] & 0x3f) << 6 | pb[2] & 0x3f;
            break;
        case 4:
            scalar = (lead & 0xf) << 0x12 | (pb[1] & 0x3f) << 0xc | (pb[2] & 0x3f) << 6 | pb[3] & 0x3f;
            break;
        default:
            scalar = lead;
        }
    }
    else {
        scalar = lead;
    }
    *out = scalar;
    sk_word16_t r;
    r.hi = (uint64_t)(uintptr_t)pb;
    r.lo = (uint64_t)(uintptr_t)FUN_0001a1c8;
    return r;
}

/* FUN_002aea60 @ 0x002aea60   (est. sk_swift_string_normalize)
 * Ghidra: void FUN_002aea60(void)
 * Normalizes the current String: resolves the storage, validates the range
 * via FUN_002ab8ac, and releases the intermediate reference.
 * Confidence: medium */
void sk_swift_string_normalize(void)
{
    FUN_00077888();
    FUN_00354404();
    FUN_002ab8ac();
    FUN_003523e0();
    thunk_FUN_0036b270();
    FUN_0034aebc();
}

/* FUN_002aeaa0 @ 0x002aeaa0   (est. sk_swift_string_append_guard)
 * Ghidra: void FUN_002aeaa0(void)
 * Append guard: runs the append-reserve, the copy, and the finalize steps.
 * Confidence: medium */
void sk_swift_string_append_guard(void)
{
    FUN_00353510();
    FUN_001bcdcc();
    FUN_003554e0();
}

/* FUN_002aead0 @ 0x002aead0   (est. sk_swift_string_offset_apply_a)
 * Ghidra: void FUN_002aead0(void)
 * Applies the String index-offset primitive to the current String.
 * Confidence: medium */
void sk_swift_string_offset_apply_a(void)
{
    uint64_t *slot = (uint64_t *)base_slot();
    FUN_001ee030(slot[0], slot[1], (uint64_t)(uintptr_t)&sk_swift_string_index_offset);
}

/* FUN_002aead4 @ 0x002aead4   (est. sk_swift_string_offset_apply_b)
 * Ghidra: void FUN_002aead4(void)
 * Offset-apply twin of 002aead0.
 * Confidence: medium */
void sk_swift_string_offset_apply_b(void)
{
    uint64_t *slot = (uint64_t *)base_slot();
    FUN_001ee030(slot[0], slot[1], (uint64_t)(uintptr_t)&sk_swift_string_index_offset);
}

/* FUN_002aeb14 @ 0x002aeb14   (est. sk_swift_string_finalize_a)
 * Ghidra: void FUN_002aeb14(void)
 * Finalizes a String builder operation (reserve then commit).
 * Confidence: medium */
void sk_swift_string_finalize_a(void)
{
    FUN_00352764();
    FUN_001d2f4c();
}

/* FUN_002aeb18 @ 0x002aeb18   (est. sk_swift_string_finalize_b)
 * Ghidra: void FUN_002aeb18(void)
 * Finalize twin of 002aeb14.
 * Confidence: medium */
void sk_swift_string_finalize_b(void)
{
    FUN_00352764();
    FUN_001d2f4c();
}

/* FUN_002aeb30 @ 0x002aeb30   (est. sk_swift_string_scalar_next_index)
 * Ghidra: void FUN_002aeb30(ulong *param_1, undefined8 *param_2)
 * Computes the next Unicode-scalar index for the String storage pair and
 * stores the packed index into *param_1. Resolves the buffer pointer and
 * adds the encoded width of the current byte.
 * Confidence: medium
 * Notes: Swift String next-scalar index. */
void sk_swift_string_scalar_next_index(uint64_t *out, uint64_t *src)
{
    uint64_t *slot = (uint64_t *)base_slot();
    uint64_t u1 = slot[0], u2 = slot[1];
    uint64_t u4 = FUN_00167404(*src, u1, u2).lo;
    uint64_t off = u4 >> 0x10;
    uint8_t b1;
    if ((u2 >> 0x3c & 1) == 0) {
        if ((u2 >> 0x3d & 1) != 0) {
            b1 = *(uint8_t *)((uintptr_t)&u1 + off);
            goto have_byte;
        }
        uint64_t bptr;
        if ((u1 >> 0x3c & 1) == 0) {
            bptr = FUN_002a9ba8(u1, u2).lo;
        }
        else {
            bptr = (u2 & 0xfffffffffffffff) + 0x20;
        }
        b1 = *(uint8_t *)(bptr + off);
    }
    else {
        FUN_002a49a8();
        b1 = *(uint8_t *)(FUN_002a9ba8(u1, u2).lo + off);
    }
have_byte:
    uint32_t w = 31 - __builtin_clz((uint32_t)b1 << 0x18 ^ 0xffffffff);
    if ((int8_t)b1 >= 0) { w = 1; }
    *out = (off + w) * 0x10000 | 5;
}

/* FUN_002aebe0 @ 0x002aebe0   (est. sk_swift_string_scalar_next_index2)
 * Ghidra: void FUN_002aebe0(ulong *param_1)
 * Next-scalar index twin of 002aeb30.
 * Confidence: medium */
void sk_swift_string_scalar_next_index2(uint64_t *out)
{
    uint64_t *slot = (uint64_t *)base_slot();
    uint64_t u1 = slot[0], u2 = slot[1];
    uint64_t u4 = FUN_00167404(*out, u1, u2).lo;
    uint64_t off = u4 >> 0x10;
    uint8_t b1;
    if ((u2 >> 0x3c & 1) == 0) {
        if ((u2 >> 0x3d & 1) != 0) {
            b1 = *(uint8_t *)((uintptr_t)&u1 + off);
            goto have_byte2;
        }
        uint64_t bptr;
        if ((u1 >> 0x3c & 1) == 0) {
            bptr = FUN_002a9ba8(u1, u2).lo;
        }
        else {
            bptr = (u2 & 0xfffffffffffffff) + 0x20;
        }
        b1 = *(uint8_t *)(bptr + off);
    }
    else {
        FUN_002a49a8();
        b1 = *(uint8_t *)(FUN_002a9ba8(u1, u2).lo + off);
    }
have_byte2:
    uint32_t w = 31 - __builtin_clz((uint32_t)b1 << 0x18 ^ 0xffffffff);
    if ((int8_t)b1 >= 0) { w = 1; }
    *out = (off + w) * 0x10000 | 5;
}

/* FUN_002aeca8 @ 0x002aeca8   (est. sk_swift_string_append_closure)
 * Ghidra: void FUN_002aeca8(undefined8 param_1, undefined8 param_2, code *param_3, undefined8 param_4)
 * Appends a value produced by the closure param_3 onto the current String:
 * invokes the closure to obtain a {lo,hi} pair, stores it into the per-cpu
 * slot, and initializes the trailing owner fields.
 * Confidence: medium */
void sk_swift_string_append_closure(uint64_t p1, uint64_t p2, uint64_t fn, uint64_t p4)
{
    uint64_t *x19 = (uint64_t *)base_slot();
    FUN_00353510();
    sk_word16_t v = (*(sk_word16_t (*)(void))(uintptr_t)fn)();
    *x19 = v.lo;
    x19[1] = v.hi;
    *(uint64_t *)x19[2] = 0;
    *(uint64_t *)(x19[2] + 8) = p4;
}

/* FUN_002aecf0 @ 0x002aecf0   (est. sk_swift_unicode_scalar_next)
 * Ghidra: void FUN_002aecf0(uint *param_1)
 * Decodes the next Unicode scalar from the per-cpu String and stores it into
 * *param_1 (with a width byte). Dispatches on the buffer kind and decodes
 * 1-4 byte sequences, advancing the cursor.
 * Confidence: medium
 * Notes: Swift UnicodeScalar next; SK_FATAL 0xfd (UnicodeHelpers). */
void sk_swift_unicode_scalar_next(uint32_t *out)
{
    uint64_t *slot = (uint64_t *)base_slot();
    uint64_t u1 = slot[2];
    uint32_t scalar;
    uint8_t width;
    if ((int64_t)slot[3] <= (int64_t)u1) {
        scalar = 0;
        width = 1;
        goto store;
    }
    uint64_t u2 = slot[1];
    if ((u2 >> 0x3c & 1) != 0) {
        SK_FATAL(0xfd, (unsigned long)&s_Fatal_error_005accd0, 0xb,
                 (unsigned long)&s_Swift_UnicodeHelpers_swift_005ce730, 0x1a);
    }
    uint8_t *pb;
    if ((u2 >> 0x3d & 1) == 0) {
        uint64_t bptr;
        if ((slot[0] >> 0x3c & 1) == 0) {
            bptr = FUN_002a9ba8().lo;
        }
        else {
            bptr = (u2 & 0xfffffffffffffff) + 0x20;
        }
        pb = (uint8_t *)(bptr + u1);
        scalar = (uint32_t)*pb;
        if ((int8_t)*pb < 0) {
            int lz = __builtin_clz((uint32_t)scalar << 0x18 ^ 0xffffffff) - 24;
            switch (lz) {
            case 2: scalar = (pb[1] & 0x3f) | (scalar & 0x1f) << 6; width = 2; break;
            case 3: scalar = (scalar & 0xf) << 0xc | (pb[1] & 0x3f) << 6 | pb[2] & 0x3f; width = 3; break;
            case 4: scalar = (scalar & 0xf) << 0x12 | (pb[1] & 0x3f) << 0xc | (pb[2] & 0x3f) << 6 | pb[3] & 0x3f; width = 4; break;
            default: width = 1; break;
            }
        } else {
            width = 1;
        }
    }
    else {
        pb = (uint8_t *)((uintptr_t)&slot[0] + u1);
        scalar = (uint32_t)*pb;
        if ((int8_t)*pb < 0) {
            int lz = __builtin_clz((uint32_t)scalar << 0x18 ^ 0xffffffff) - 24;
            switch (lz) {
            case 2: scalar = (pb[1] & 0x3f) | (scalar & 0x1f) << 6; width = 2; break;
            case 3: scalar = (scalar & 0xf) << 0xc | (pb[1] & 0x3f) << 6 | pb[2] & 0x3f; width = 3; break;
            case 4: scalar = (scalar & 0xf) << 0x12 | (pb[1] & 0x3f) << 0xc | (pb[2] & 0x3f) << 6 | pb[3] & 0x3f; width = 4; break;
            default: width = 1; break;
            }
        } else {
            width = 1;
        }
    }
    slot[2] = u1 + width;
store:
    *out = scalar;
    *(uint8_t *)((uintptr_t)out + 4) = width;
}

/* FUN_002af068 @ 0x002af068   (est. sk_swift_string_append_desc)
 * Ghidra: void FUN_002af068(void)
 * Appends a description to the current String: resolves the descriptor pair
 * (FUN_000a6e20), validates via FUN_002ab8ac, and appends the literal via
 * FUN_002a82cc.
 * Confidence: medium */
void sk_swift_string_append_desc(void)
{
    uint64_t *slot = (uint64_t *)base_slot();
    sk_word16_t v = FUN_000a6e20();
    FUN_002ab8ac(v.lo, v.hi, slot[0], slot[1], 0x174, 0x164);
    FUN_00351b78();
    FUN_002a82cc();
}

/* FUN_002af0d0 @ 0x002af0d0   (est. sk_swift_string_builder_commit)
 * Ghidra: void FUN_002af0d0(void)
 * Commits a String builder result: reads the produced pair, invokes the
 * caller closure, and tails through the follow-up dispatch.
 * Confidence: medium
 * Notes: unrecovered jumptable at 0x2af130. */
void sk_swift_string_builder_commit(void)
{
    uint64_t *pu = (uint64_t *)(uintptr_t)FUN_00350b54().lo;
    FUN_0035063c(pu[0], pu[1]);
    FUN_00350bcc();
    (*(void (*)(void))(uintptr_t)(*(uint64_t *)(uintptr_t)FUN_00350bcc().lo + 8))();
}

/* FUN_002af138 @ 0x002af138   (est. sk_swift_string_new_from_flag)
 * Ghidra: void FUN_002af138(undefined1 (*param_1) [16], undefined4 *param_2)
 * Produces a String word-pair from a flag/kind value via FUN_0027169c.
 * Confidence: medium */
void sk_swift_string_new_from_flag(sk_word16_t *out, uint32_t *flag)
{
    *out = FUN_0027169c(*flag);
}

/* FUN_002af19c @ 0x002af19c   (est. sk_swift_string_commit2)
 * Ghidra: void FUN_002af19c(void)
 * Commits a String builder (twin): runs the caller closure then tails
 * through the follow-up dispatch.
 * Confidence: medium
 * Notes: unrecovered jumptable at 0x2af1ec. */
void sk_swift_string_commit2(void)
{
    FUN_0008409c();
    FUN_00350bcc();
    (*(void (*)(void))(uintptr_t)(*(uint64_t *)(uintptr_t)FUN_00350bcc().lo + 8))();
}

/* FUN_002af214 @ 0x002af214   (est. sk_swift_string_index_fetch)
 * Ghidra: void FUN_002af214(undefined4 *param_1, undefined8 *param_2)
 * Fetches a String index value via FUN_00273310 and stores it into *param_1.
 * Confidence: medium */
void sk_swift_string_index_fetch(uint32_t *out, uint64_t *src)
{
    *out = (uint32_t)FUN_00273310(*src).lo;
}

/* FUN_002af24c @ 0x002af24c   (est. sk_swift_string_index_fetch2)
 * Ghidra: void FUN_002af24c(undefined4 *param_1)
 * Fetches a String index value (twin) with a status byte.
 * Confidence: medium */
void sk_swift_string_index_fetch2(uint32_t *out)
{
    uint64_t u1 = FUN_002740dc().lo;
    *out = (uint32_t)u1;
    *(uint8_t *)((uintptr_t)out + 4) = 0;
}

/* FUN_002af27c @ 0x002af27c   (est. sk_swift_string_index_fetch3)
 * Ghidra: void FUN_002af27c(undefined4 *param_1)
 * Fetches a String index value (twin) via FUN_001a4efc.
 * Confidence: medium */
void sk_swift_string_index_fetch3(uint32_t *out)
{
    *out = (uint32_t)FUN_001a4efc().lo;
}

/* FUN_002af2ac @ 0x002af2ac   (est. sk_swift_string_index_copy_a)
 * Ghidra: void FUN_002af2ac(void)
 * Copies a String index (delegates to FUN_002764a8).
 * Confidence: medium */
void sk_swift_string_index_copy_a(void)
{
    FUN_002764a8();
}

/* FUN_002af2b0 @ 0x002af2b0   (est. sk_swift_string_index_copy_b)
 * Ghidra: void FUN_002af2b0(void)
 * Index copy twin of 002af2ac.
 * Confidence: medium */
void sk_swift_string_index_copy_b(void)
{
    FUN_002764a8();
}

/* FUN_002af2c4 @ 0x002af2c4   (est. sk_swift_string_index_resolve2)
 * Ghidra: ulong FUN_002af2c4(void)
 * Grown String index resolve: dispatches on the buffer kind and returns the
 * packed index word, re-validating through FUN_002af340 for the grown form.
 * Confidence: medium */
uint64_t sk_swift_string_index_resolve2(void)
{
    FUN_0034c840();
    uint64_t u1 = 0;
    if (FUN_0034a3b0(1).lo & 1) u1 = 1;
    FUN_0034a3b0(u1);
    uint64_t x19 = 0;
    if (u1 & 1) {
        FUN_0034bf1c();
        x19 = FUN_0001da84().lo;
    }
    FUN_0034a260();
    uint64_t cap = FUN_0034a260().lo;
    if (cap < x19 >> 0x10) {
        FUN_003a25d4();
    }
    else {
        FUN_0034bf1c();
        FUN_002af340();
        FUN_00356328();
        FUN_003a25d4();
        if ((*(uint64_t *)(base_slot()+1) & 1) != 0) {
            return x19;
        }
    }
    FUN_00358b90();
    return x19;
}

/* FUN_002af340 @ 0x002af340   (est. sk_swift_string_is_scalar_boundary)
 * Ghidra: bool FUN_002af340(ulong param_1, ulong param_2, ulong param_3)
 * Tests whether the String index param_1 lies on a Unicode-scalar boundary of
 * the storage pair (param_2=lo, param_3=hi): checks the encoded offset is a
 * valid scalar start (not a continuation byte / mid-scalar), handling both
 * inline and grown buffers.
 * Confidence: medium
 * Notes: Swift scalar-boundary test. */
sk_word16_t sk_swift_string_is_scalar_boundary(uint64_t idx, uint64_t sLo, uint64_t sHi)
{
    sk_word16_t r;
    r.hi = 0;
    if ((idx & 0xc000) != 0) { r.lo = 0; return r; }
    if (0x3fff < idx) {
        uint64_t u3 = sLo & 0xffffffffffff;
        if ((sHi & 0x2000000000000000) != 0) { u3 = sHi >> 0x38 & 0xf; }
        if (idx >> 0xe != u3 * 4) {
            bool b;
            if ((sHi >> 0x3c & 1) == 0) {
                int8_t c;
                if ((sHi >> 0x3d & 1) == 0) {
                    uint64_t bptr;
                    if ((sLo >> 0x3c & 1) == 0) {
                        FUN_00106e3c();
                        bptr = FUN_002a9ba8().lo;
                    }
                    else {
                        bptr = (sHi & 0xfffffffffffffff) + 0x20;
                    }
                    c = *(int8_t *)(bptr + (idx >> 0x10));
                }
                else {
                    c = *(int8_t *)((uintptr_t)&sLo + (idx >> 0x10));
                }
                b = -0x41 < c;
            }
            else {
                uint64_t u3b = FUN_002bbbe8().lo;
                b = idx >> 0xe == u3b >> 0xe;
            }
            r.lo = b;
            return r;
        }
    }
    r.lo = 1;
    return r;
}

/* FUN_002af40c @ 0x002af40c   (est. sk_swift_string_dispatch_guard2)
 * Ghidra: void FUN_002af40c(void)
 * Releases a pair then dispatches into the Unicode/description path.
 * Confidence: medium */
void sk_swift_string_dispatch_guard2(void)
{
    sk_word16_t v = FUN_0034b430();
    thunk_FUN_0036b270(v.lo);
    FUN_0034bf1c();
    FUN_002aaae4();
}

/* FUN_002af444 @ 0x002af444   (est. sk_swift_string_op_guard)
 * Ghidra: void FUN_002af444(undefined8 param_1, undefined8 param_2)
 * Final String operation guard: forwards the two operands, the descriptor
 * table, and the canonical bounds/closure words into FUN_002b0f7c.
 * Confidence: medium */
void sk_swift_string_op_guard(uint64_t p1, uint64_t p2)
{
    FUN_002b0f7c(p1, p2, 0x6758c0, (uint64_t)&DAT_00657680, (uint64_t)&DAT_004f2160, (uint64_t)&LAB_003243b0);
}
