/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0). Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary; estimates unless matched. */
/* Region slice 11: 0x0026cd08..0x00277ba8 — the cL4 embedded Swift runtime
 * (Range / String / Collection / UTF-8 index machinery) plus object/thunk
 * wrappers. Function names below use Swift vocabulary (Range, String,
 * Collection, lowerBound, upperBound, removeFirst, removeLast, UTF-8 scalar)
 * and are estimates unless a string matched. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* cl4_result_t (lo,hi) models the AArch64 x0/x1 16-byte register-pair return
 * the Swift runtime uses for Optional/String/Collection values. The shared
 * cL4/seL4 runtime library (out of this slice) reconstructs every sk_rt_*
 * helper; each maps to a Ghidra FUN_ address in its trailing comment. The
 * `()` K&R prototype keeps the callee's true arity unspecified; helpers that
 * produce a 16-byte pair are declared to return cl4_result_t, the rest a
 * scalar. */
extern uint64_t sk_rt_000026e8();  /* FUN_000026e8 */
extern uint64_t sk_rt_00012568();  /* FUN_00012568 */
extern uint64_t sk_rt_00027754();  /* FUN_00027754 */
extern uint64_t sk_rt_000277b8();  /* FUN_000277b8 */
extern uint64_t sk_rt_00027818();  /* FUN_00027818 */
extern uint64_t sk_rt_00041138();  /* FUN_00041138 */
extern cl4_result_t sk_rt_0006b6f4();  /* FUN_0006b6f4 */
extern uint64_t sk_rt_0006e778();  /* FUN_0006e778 */
extern uint64_t sk_rt_0007767c();  /* FUN_0007767c */
extern cl4_result_t sk_rt_00077698();  /* FUN_00077698 */
extern uint64_t sk_rt_00077894();  /* FUN_00077894 */
extern uint64_t sk_rt_0007c1a4();  /* FUN_0007c1a4 */
extern uint64_t sk_rt_0007c1c4();  /* FUN_0007c1c4 */
extern uint64_t sk_rt_000836a4();  /* FUN_000836a4 */
extern cl4_result_t sk_rt_000839d8();  /* FUN_000839d8 */
extern uint64_t sk_rt_00084174();  /* FUN_00084174 */
extern uint64_t sk_rt_00084180();  /* FUN_00084180 */
extern cl4_result_t sk_rt_00084220();  /* FUN_00084220 */
extern uint64_t sk_rt_00084234();  /* FUN_00084234 */
extern uint64_t sk_rt_0008e388();  /* FUN_0008e388 */
extern uint64_t sk_rt_0008e500();  /* FUN_0008e500 */
extern cl4_result_t sk_rt_0008e518();  /* FUN_0008e518 */
extern uint64_t sk_rt_0008f6f4();  /* FUN_0008f6f4 */
extern uint64_t sk_rt_0008f728();  /* FUN_0008f728 */
extern uint64_t sk_rt_0008f758();  /* FUN_0008f758 */
extern uint64_t sk_rt_0009461c();  /* FUN_0009461c */
extern uint64_t sk_rt_000a6894();  /* FUN_000a6894 */
extern uint64_t sk_rt_000a68c4();  /* FUN_000a68c4 */
extern uint64_t sk_rt_000a68f4();  /* FUN_000a68f4 */
extern uint64_t sk_rt_000a6e14();  /* FUN_000a6e14 */
extern uint64_t sk_rt_000a6f88();  /* FUN_000a6f88 */
extern uint64_t sk_rt_000b4390();  /* FUN_000b4390 */
extern uint64_t sk_rt_000bd3a4();  /* FUN_000bd3a4 */
extern uint64_t sk_rt_000dbcc8();  /* FUN_000dbcc8 */
extern cl4_result_t sk_rt_000dbd0c();  /* FUN_000dbd0c */
extern uint64_t sk_rt_000dbdf4();  /* FUN_000dbdf4 */
extern uint64_t sk_rt_000dbf08();  /* FUN_000dbf08 */
extern cl4_result_t sk_rt_000e15d8();  /* FUN_000e15d8 */
extern uint64_t sk_rt_000e72b0();  /* FUN_000e72b0 */
extern cl4_result_t sk_rt_00100c38();  /* FUN_00100c38 */
extern uint64_t sk_rt_00100efc();  /* FUN_00100efc */
extern cl4_result_t sk_rt_00106e3c();  /* FUN_00106e3c */
extern uint64_t sk_rt_0014ae44();  /* FUN_0014ae44 */
extern uint64_t sk_rt_0016186c();  /* FUN_0016186c */
extern uint64_t sk_rt_00167404();  /* FUN_00167404 */
extern uint64_t sk_rt_0016de38();  /* FUN_0016de38 */
extern uint64_t sk_rt_0017e880();  /* FUN_0017e880 */
extern uint64_t sk_rt_0019b25c();  /* FUN_0019b25c */
extern uint64_t sk_rt_0019e578();  /* FUN_0019e578 */
extern uint64_t sk_rt_0019e728();  /* FUN_0019e728 */
extern uint64_t sk_rt_0019f410();  /* FUN_0019f410 */
extern uint64_t sk_rt_001a0414();  /* FUN_001a0414 */
extern uint64_t sk_rt_001a0534();  /* FUN_001a0534 */
extern uint64_t sk_rt_001a2838();  /* FUN_001a2838 */
extern uint64_t sk_rt_001a29d4();  /* FUN_001a29d4 */
extern uint64_t sk_rt_001a4d84();  /* FUN_001a4d84 */
extern cl4_result_t sk_rt_001a89a8();  /* FUN_001a89a8 */
extern uint64_t sk_rt_001aeab4();  /* FUN_001aeab4 */
extern uint64_t sk_rt_001afa84();  /* FUN_001afa84 */
extern uint64_t sk_rt_001afe4c();  /* FUN_001afe4c */
extern uint64_t sk_rt_001b1780();  /* FUN_001b1780 */
extern uint64_t sk_rt_001b3984();  /* FUN_001b3984 */
extern uint64_t sk_rt_001bbfdc();  /* FUN_001bbfdc */
extern cl4_result_t sk_rt_001c050c();  /* FUN_001c050c */
extern uint64_t sk_rt_001d2df0();  /* FUN_001d2df0 */
extern uint64_t sk_rt_001d80e0();  /* FUN_001d80e0 */
extern uint64_t sk_rt_001d96e0();  /* FUN_001d96e0 */
extern uint64_t sk_rt_001d974c();  /* FUN_001d974c */
extern uint64_t sk_rt_001d9890();  /* FUN_001d9890 */
extern uint64_t sk_rt_001dc298();  /* FUN_001dc298 */
extern uint64_t sk_rt_001dc430();  /* FUN_001dc430 */
extern uint64_t sk_rt_001dd1ec();  /* FUN_001dd1ec */
extern uint64_t sk_rt_001e3048();  /* FUN_001e3048 */
extern uint64_t sk_rt_001e3a28();  /* FUN_001e3a28 */
extern uint64_t sk_rt_001e3f70();  /* FUN_001e3f70 */
extern uint64_t sk_rt_001e4348();  /* FUN_001e4348 */
extern uint64_t sk_rt_001e7664();  /* FUN_001e7664 */
extern uint64_t sk_rt_001fe95c();  /* FUN_001fe95c */
extern uint64_t sk_rt_001fea40();  /* FUN_001fea40 */
extern uint64_t sk_rt_001ff258();  /* FUN_001ff258 */
extern uint64_t sk_rt_00203b08();  /* FUN_00203b08 */
extern uint64_t sk_rt_00205844();  /* FUN_00205844 */
extern cl4_result_t sk_rt_00208418();  /* FUN_00208418 */
extern uint64_t sk_rt_00209f18();  /* FUN_00209f18 */
extern uint64_t sk_rt_0021867c();  /* FUN_0021867c */
extern uint64_t sk_rt_0022b584();  /* FUN_0022b584 */
extern uint64_t sk_rt_00231b0c();  /* FUN_00231b0c */
extern uint64_t sk_rt_0028cba8();  /* FUN_0028cba8 */
extern uint64_t sk_rt_00291ee0();  /* FUN_00291ee0 */
extern cl4_result_t sk_rt_0029fb80();  /* FUN_0029fb80 */
extern uint64_t sk_rt_002a200c();  /* FUN_002a200c */
extern cl4_result_t sk_rt_002a2698();  /* FUN_002a2698 */
extern cl4_result_t sk_rt_002a2f60();  /* FUN_002a2f60 */
extern uint64_t sk_rt_002a4c98();  /* FUN_002a4c98 */
extern uint64_t sk_rt_002a72e4();  /* FUN_002a72e4 */
extern uint64_t sk_rt_002a7c00();  /* FUN_002a7c00 */
extern uint64_t sk_rt_002a7f58();  /* FUN_002a7f58 */
extern cl4_result_t sk_rt_002a95b4();  /* FUN_002a95b4 */
extern uint64_t sk_rt_002a9ba8();  /* FUN_002a9ba8 */
extern uint64_t sk_rt_002ab130();  /* FUN_002ab130 */
extern uint64_t sk_rt_002ab4d4();  /* FUN_002ab4d4 */
extern cl4_result_t sk_rt_002ab5bc();  /* FUN_002ab5bc */
extern uint64_t sk_rt_002ab6a0();  /* FUN_002ab6a0 */
extern cl4_result_t sk_rt_002ab8ac();  /* FUN_002ab8ac */
extern uint64_t sk_rt_002ae098();  /* FUN_002ae098 */
extern uint64_t sk_rt_002b3978();  /* FUN_002b3978 */
extern uint64_t sk_rt_002b3b84();  /* FUN_002b3b84 */
extern uint64_t sk_rt_002b3cf8();  /* FUN_002b3cf8 */
extern cl4_result_t sk_rt_002b439c();  /* FUN_002b439c */
extern uint64_t sk_rt_002c88f8();  /* FUN_002c88f8 */
extern uint64_t sk_rt_002c8c2c();  /* FUN_002c8c2c */
extern uint64_t sk_rt_002c8df4();  /* FUN_002c8df4 */
extern uint64_t sk_rt_00310924();  /* FUN_00310924 */
extern uint64_t sk_rt_00310b08();  /* FUN_00310b08 */
extern uint64_t sk_rt_00310ca4();  /* FUN_00310ca4 */
extern cl4_result_t sk_rt_00310d34();  /* FUN_00310d34 */
extern uint64_t sk_rt_00310d68();  /* FUN_00310d68 */
extern uint64_t sk_rt_00310d80();  /* FUN_00310d80 */
extern uint64_t sk_rt_00310e08();  /* FUN_00310e08 */
extern uint64_t sk_rt_00310e20();  /* FUN_00310e20 */
extern uint64_t sk_rt_00310f04();  /* FUN_00310f04 */
extern uint64_t sk_rt_00319218();  /* FUN_00319218 */
extern uint64_t sk_rt_00319230();  /* FUN_00319230 */
extern uint64_t sk_rt_00319248();  /* FUN_00319248 */
extern uint64_t sk_rt_003192a8();  /* FUN_003192a8 */
extern uint64_t sk_rt_00319308();  /* FUN_00319308 */
extern uint64_t sk_rt_0031945c();  /* FUN_0031945c */
extern uint64_t sk_rt_003195f8();  /* FUN_003195f8 */
extern uint64_t sk_rt_00319628();  /* FUN_00319628 */
extern uint64_t sk_rt_00319658();  /* FUN_00319658 */
extern uint64_t sk_rt_00319a4c();  /* FUN_00319a4c */
extern uint64_t sk_rt_0031a14c();  /* FUN_0031a14c */
extern uint64_t sk_rt_0031a1ac();  /* FUN_0031a1ac */
extern uint64_t sk_rt_0031b080();  /* FUN_0031b080 */
extern uint64_t sk_rt_0031b164();  /* FUN_0031b164 */
extern uint64_t sk_rt_0031b194();  /* FUN_0031b194 */
extern uint64_t sk_rt_0031b71c();  /* FUN_0031b71c */
extern uint64_t sk_rt_0031d488();  /* FUN_0031d488 */
extern uint64_t sk_rt_0031d630();  /* FUN_0031d630 */
extern uint64_t sk_rt_0031d660();  /* FUN_0031d660 */
extern uint64_t sk_rt_0031d678();  /* FUN_0031d678 */
extern uint64_t sk_rt_0031d6a8();  /* FUN_0031d6a8 */
extern uint64_t sk_rt_0031d6d8();  /* FUN_0031d6d8 */
extern uint64_t sk_rt_0031d708();  /* FUN_0031d708 */
extern uint64_t sk_rt_0031d738();  /* FUN_0031d738 */
extern uint64_t sk_rt_0031d768();  /* FUN_0031d768 */
extern uint64_t sk_rt_0031d798();  /* FUN_0031d798 */
extern uint64_t sk_rt_0031d7b0();  /* FUN_0031d7b0 */
extern uint64_t sk_rt_0031e0d4();  /* FUN_0031e0d4 */
extern uint64_t sk_rt_0031e104();  /* FUN_0031e104 */
extern uint64_t sk_rt_00347d60();  /* FUN_00347d60 */
extern uint64_t sk_rt_00348730();  /* FUN_00348730 */
extern uint64_t sk_rt_0034883c();  /* FUN_0034883c */
extern uint64_t sk_rt_0034887c();  /* FUN_0034887c */
extern uint64_t sk_rt_003488bc();  /* FUN_003488bc */
extern uint64_t sk_rt_003489a8();  /* FUN_003489a8 */
extern uint64_t sk_rt_003489c0();  /* FUN_003489c0 */
extern uint64_t sk_rt_00348a18();  /* FUN_00348a18 */
extern uint64_t sk_rt_00348a34();  /* FUN_00348a34 */
extern uint64_t sk_rt_00348a50();  /* FUN_00348a50 */
extern uint64_t sk_rt_00348a9c();  /* FUN_00348a9c */
extern uint64_t sk_rt_00348abc();  /* FUN_00348abc */
extern uint64_t sk_rt_00348b7c();  /* FUN_00348b7c */
extern cl4_result_t sk_rt_00348b94();  /* FUN_00348b94 */
extern uint64_t sk_rt_00348bbc();  /* FUN_00348bbc */
extern uint64_t sk_rt_00348bd8();  /* FUN_00348bd8 */
extern uint64_t sk_rt_00348c30();  /* FUN_00348c30 */
extern uint64_t sk_rt_00348cd0();  /* FUN_00348cd0 */
extern uint64_t sk_rt_00348ce8();  /* FUN_00348ce8 */
extern uint64_t sk_rt_00348d18();  /* FUN_00348d18 */
extern uint64_t sk_rt_00348d4c();  /* FUN_00348d4c */
extern uint64_t sk_rt_00348d64();  /* FUN_00348d64 */
extern uint64_t sk_rt_00348d7c();  /* FUN_00348d7c */
extern uint64_t sk_rt_00348e00();  /* FUN_00348e00 */
extern uint64_t sk_rt_00348e18();  /* FUN_00348e18 */
extern uint64_t sk_rt_00348e60();  /* FUN_00348e60 */
extern uint64_t sk_rt_00348f14();  /* FUN_00348f14 */
extern uint64_t sk_rt_00348f38();  /* FUN_00348f38 */
extern uint64_t sk_rt_00348f50();  /* FUN_00348f50 */
extern uint64_t sk_rt_00348fd8();  /* FUN_00348fd8 */
extern uint64_t sk_rt_00349068();  /* FUN_00349068 */
extern uint64_t sk_rt_003490b8();  /* FUN_003490b8 */
extern uint64_t sk_rt_003490d0();  /* FUN_003490d0 */
extern uint64_t sk_rt_0034911c();  /* FUN_0034911c */
extern uint64_t sk_rt_00349178();  /* FUN_00349178 */
extern uint64_t sk_rt_00349204();  /* FUN_00349204 */
extern uint64_t sk_rt_0034921c();  /* FUN_0034921c */
extern uint64_t sk_rt_00349234();  /* FUN_00349234 */
extern uint64_t sk_rt_0034924c();  /* FUN_0034924c */
extern uint64_t sk_rt_0034928c();  /* FUN_0034928c */
extern uint64_t sk_rt_003493c4();  /* FUN_003493c4 */
extern uint64_t sk_rt_00349410();  /* FUN_00349410 */
extern uint64_t sk_rt_0034947c();  /* FUN_0034947c */
extern uint64_t sk_rt_003494b4();  /* FUN_003494b4 */
extern uint64_t sk_rt_003494e8();  /* FUN_003494e8 */
extern uint64_t sk_rt_0034951c();  /* FUN_0034951c */
extern uint64_t sk_rt_00349530();  /* FUN_00349530 */
extern uint64_t sk_rt_003495a8();  /* FUN_003495a8 */
extern uint64_t sk_rt_00349618();  /* FUN_00349618 */
extern uint64_t sk_rt_00349720();  /* FUN_00349720 */
extern uint64_t sk_rt_00349748();  /* FUN_00349748 */
extern uint64_t sk_rt_003497b4();  /* FUN_003497b4 */
extern uint64_t sk_rt_003497c8();  /* FUN_003497c8 */
extern uint64_t sk_rt_003497ec();  /* FUN_003497ec */
extern uint64_t sk_rt_003498a8();  /* FUN_003498a8 */
extern uint64_t sk_rt_00349910();  /* FUN_00349910 */
extern uint64_t sk_rt_00349944();  /* FUN_00349944 */
extern uint64_t sk_rt_0034998c();  /* FUN_0034998c */
extern uint64_t sk_rt_003499c8();  /* FUN_003499c8 */
extern uint64_t sk_rt_003499dc();  /* FUN_003499dc */
extern uint64_t sk_rt_003499f0();  /* FUN_003499f0 */
extern uint64_t sk_rt_00349a68();  /* FUN_00349a68 */
extern uint64_t sk_rt_00349b00();  /* FUN_00349b00 */
extern uint64_t sk_rt_00349b3c();  /* FUN_00349b3c */
extern uint64_t sk_rt_00349c84();  /* FUN_00349c84 */
extern uint64_t sk_rt_00349cbc();  /* FUN_00349cbc */
extern uint64_t sk_rt_00349f3c();  /* FUN_00349f3c */
extern uint64_t sk_rt_00349fe0();  /* FUN_00349fe0 */
extern uint64_t sk_rt_0034a120();  /* FUN_0034a120 */
extern uint64_t sk_rt_0034a274();  /* FUN_0034a274 */
extern uint64_t sk_rt_0034a2ac();  /* FUN_0034a2ac */
extern uint64_t sk_rt_0034a30c();  /* FUN_0034a30c */
extern uint64_t sk_rt_0034a37c();  /* FUN_0034a37c */
extern uint64_t sk_rt_0034a400();  /* FUN_0034a400 */
extern uint64_t sk_rt_0034a5c8();  /* FUN_0034a5c8 */
extern uint64_t sk_rt_0034a654();  /* FUN_0034a654 */
extern uint64_t sk_rt_0034a69c();  /* FUN_0034a69c */
extern uint64_t sk_rt_0034a798();  /* FUN_0034a798 */
extern uint64_t sk_rt_0034a7ac();  /* FUN_0034a7ac */
extern uint64_t sk_rt_0034a900();  /* FUN_0034a900 */
extern uint64_t sk_rt_0034a944();  /* FUN_0034a944 */
extern uint64_t sk_rt_0034a958();  /* FUN_0034a958 */
extern uint64_t sk_rt_0034aa28();  /* FUN_0034aa28 */
extern uint64_t sk_rt_0034aac4();  /* FUN_0034aac4 */
extern uint64_t sk_rt_0034ab10();  /* FUN_0034ab10 */
extern uint64_t sk_rt_0034ab20();  /* FUN_0034ab20 */
extern uint64_t sk_rt_0034acf0();  /* FUN_0034acf0 */
extern uint64_t sk_rt_0034ad20();  /* FUN_0034ad20 */
extern uint64_t sk_rt_0034aee4();  /* FUN_0034aee4 */
extern uint64_t sk_rt_0034af20();  /* FUN_0034af20 */
extern uint64_t sk_rt_0034b05c();  /* FUN_0034b05c */
extern uint64_t sk_rt_0034b07c();  /* FUN_0034b07c */
extern cl4_result_t sk_rt_0034b0b4();  /* FUN_0034b0b4 */
extern uint64_t sk_rt_0034b0d4();  /* FUN_0034b0d4 */
extern uint64_t sk_rt_0034b178();  /* FUN_0034b178 */
extern uint64_t sk_rt_0034b1a0();  /* FUN_0034b1a0 */
extern uint64_t sk_rt_0034b278();  /* FUN_0034b278 */
extern uint64_t sk_rt_0034b2a8();  /* FUN_0034b2a8 */
extern uint64_t sk_rt_0034b2f8();  /* FUN_0034b2f8 */
extern uint64_t sk_rt_0034b348();  /* FUN_0034b348 */
extern uint64_t sk_rt_0034b3d8();  /* FUN_0034b3d8 */
extern uint64_t sk_rt_0034b3e8();  /* FUN_0034b3e8 */
extern uint64_t sk_rt_0034b3f8();  /* FUN_0034b3f8 */
extern uint64_t sk_rt_0034b460();  /* FUN_0034b460 */
extern uint64_t sk_rt_0034b4c0();  /* FUN_0034b4c0 */
extern uint64_t sk_rt_0034b5fc();  /* FUN_0034b5fc */
extern uint64_t sk_rt_0034b640();  /* FUN_0034b640 */
extern uint64_t sk_rt_0034b668();  /* FUN_0034b668 */
extern uint64_t sk_rt_0034b6e0();  /* FUN_0034b6e0 */
extern uint64_t sk_rt_0034b6f4();  /* FUN_0034b6f4 */
extern uint64_t sk_rt_0034b708();  /* FUN_0034b708 */
extern uint64_t sk_rt_0034b758();  /* FUN_0034b758 */
extern uint64_t sk_rt_0034b768();  /* FUN_0034b768 */
extern uint64_t sk_rt_0034b7c8();  /* FUN_0034b7c8 */
extern uint64_t sk_rt_0034b804();  /* FUN_0034b804 */
extern uint64_t sk_rt_0034b824();  /* FUN_0034b824 */
extern uint64_t sk_rt_0034b87c();  /* FUN_0034b87c */
extern uint64_t sk_rt_0034b8bc();  /* FUN_0034b8bc */
extern uint64_t sk_rt_0034ba08();  /* FUN_0034ba08 */
extern uint64_t sk_rt_0034ba68();  /* FUN_0034ba68 */
extern uint64_t sk_rt_0034baa8();  /* FUN_0034baa8 */
extern uint64_t sk_rt_0034bc04();  /* FUN_0034bc04 */
extern uint64_t sk_rt_0034bc6c();  /* FUN_0034bc6c */
extern uint64_t sk_rt_0034bc80();  /* FUN_0034bc80 */
extern uint64_t sk_rt_0034bccc();  /* FUN_0034bccc */
extern uint64_t sk_rt_0034bd58();  /* FUN_0034bd58 */
extern uint64_t sk_rt_0034bd90();  /* FUN_0034bd90 */
extern uint64_t sk_rt_0034bdfc();  /* FUN_0034bdfc */
extern uint64_t sk_rt_0034bec4();  /* FUN_0034bec4 */
extern uint64_t sk_rt_0034beec();  /* FUN_0034beec */
extern uint64_t sk_rt_0034bf64();  /* FUN_0034bf64 */
extern uint64_t sk_rt_0034c074();  /* FUN_0034c074 */
extern uint64_t sk_rt_0034c094();  /* FUN_0034c094 */
extern uint64_t sk_rt_0034c0a4();  /* FUN_0034c0a4 */
extern uint64_t sk_rt_0034c158();  /* FUN_0034c158 */
extern uint64_t sk_rt_0034c20c();  /* FUN_0034c20c */
extern uint64_t sk_rt_0034c2d8();  /* FUN_0034c2d8 */
extern uint64_t sk_rt_0034c2f8();  /* FUN_0034c2f8 */
extern uint64_t sk_rt_0034c344();  /* FUN_0034c344 */
extern uint64_t sk_rt_0034c454();  /* FUN_0034c454 */
extern uint64_t sk_rt_0034c54c();  /* FUN_0034c54c */
extern uint64_t sk_rt_0034c55c();  /* FUN_0034c55c */
extern uint64_t sk_rt_0034c5bc();  /* FUN_0034c5bc */
extern uint64_t sk_rt_0034c6d4();  /* FUN_0034c6d4 */
extern uint64_t sk_rt_0034c6e4();  /* FUN_0034c6e4 */
extern uint64_t sk_rt_0034c9f8();  /* FUN_0034c9f8 */
extern uint64_t sk_rt_0034ce78();  /* FUN_0034ce78 */
extern uint64_t sk_rt_0034cea8();  /* FUN_0034cea8 */
extern uint64_t sk_rt_0034cfa4();  /* FUN_0034cfa4 */
extern uint64_t sk_rt_0034cfc4();  /* FUN_0034cfc4 */
extern uint64_t sk_rt_0034cfd4();  /* FUN_0034cfd4 */
extern uint64_t sk_rt_0034d044();  /* FUN_0034d044 */
extern uint64_t sk_rt_0034d130();  /* FUN_0034d130 */
extern uint64_t sk_rt_0034d140();  /* FUN_0034d140 */
extern uint64_t sk_rt_0034d190();  /* FUN_0034d190 */
extern uint64_t sk_rt_0034d244();  /* FUN_0034d244 */
extern uint64_t sk_rt_0034d2b4();  /* FUN_0034d2b4 */
extern uint64_t sk_rt_0034d354();  /* FUN_0034d354 */
extern uint64_t sk_rt_0034d384();  /* FUN_0034d384 */
extern uint64_t sk_rt_0034d394();  /* FUN_0034d394 */
extern uint64_t sk_rt_0034d3d4();  /* FUN_0034d3d4 */
extern uint64_t sk_rt_0034d424();  /* FUN_0034d424 */
extern uint64_t sk_rt_0034d464();  /* FUN_0034d464 */
extern uint64_t sk_rt_0034d574();  /* FUN_0034d574 */
extern uint64_t sk_rt_0034d5ec();  /* FUN_0034d5ec */
extern uint64_t sk_rt_0034d734();  /* FUN_0034d734 */
extern cl4_result_t sk_rt_0034d844();  /* FUN_0034d844 */
extern uint64_t sk_rt_0034d8d4();  /* FUN_0034d8d4 */
extern uint64_t sk_rt_0034d8e4();  /* FUN_0034d8e4 */
extern uint64_t sk_rt_0034da88();  /* FUN_0034da88 */
extern uint64_t sk_rt_0034db18();  /* FUN_0034db18 */
extern uint64_t sk_rt_0034db48();  /* FUN_0034db48 */
extern uint64_t sk_rt_0034db88();  /* FUN_0034db88 */
extern uint64_t sk_rt_0034de64();  /* FUN_0034de64 */
extern uint64_t sk_rt_0034ded4();  /* FUN_0034ded4 */
extern uint64_t sk_rt_0034dee4();  /* FUN_0034dee4 */
extern uint64_t sk_rt_0034df74();  /* FUN_0034df74 */
extern uint64_t sk_rt_0034dfa4();  /* FUN_0034dfa4 */
extern uint64_t sk_rt_0034e054();  /* FUN_0034e054 */
extern uint64_t sk_rt_0034e094();  /* FUN_0034e094 */
extern uint64_t sk_rt_0034e0c4();  /* FUN_0034e0c4 */
extern uint64_t sk_rt_0034e0d4();  /* FUN_0034e0d4 */
extern uint64_t sk_rt_0034e1ec();  /* FUN_0034e1ec */
extern uint64_t sk_rt_0034e374();  /* FUN_0034e374 */
extern cl4_result_t sk_rt_0034e4a4();  /* FUN_0034e4a4 */
extern uint64_t sk_rt_0034e4b4();  /* FUN_0034e4b4 */
extern uint64_t sk_rt_0034e55c();  /* FUN_0034e55c */
extern uint64_t sk_rt_0034e61c();  /* FUN_0034e61c */
extern uint64_t sk_rt_0034e67c();  /* FUN_0034e67c */
extern uint64_t sk_rt_0034e6ac();  /* FUN_0034e6ac */
extern uint64_t sk_rt_0034e6bc();  /* FUN_0034e6bc */
extern uint64_t sk_rt_0034ea54();  /* FUN_0034ea54 */
extern uint64_t sk_rt_0034eb94();  /* FUN_0034eb94 */
extern uint64_t sk_rt_0034ec98();  /* FUN_0034ec98 */
extern uint64_t sk_rt_0034ed38();  /* FUN_0034ed38 */
extern uint64_t sk_rt_0034ee18();  /* FUN_0034ee18 */
extern uint64_t sk_rt_0034ee48();  /* FUN_0034ee48 */
extern uint64_t sk_rt_0034ee58();  /* FUN_0034ee58 */
extern uint64_t sk_rt_0034f044();  /* FUN_0034f044 */
extern uint64_t sk_rt_0034f198();  /* FUN_0034f198 */
extern uint64_t sk_rt_0034f1a8();  /* FUN_0034f1a8 */
extern uint64_t sk_rt_0034f1c4();  /* FUN_0034f1c4 */
extern uint64_t sk_rt_0034f1e0();  /* FUN_0034f1e0 */
extern uint64_t sk_rt_0034f21c();  /* FUN_0034f21c */
extern uint64_t sk_rt_0034f2d4();  /* FUN_0034f2d4 */
extern uint64_t sk_rt_0034f354();  /* FUN_0034f354 */
extern uint64_t sk_rt_0034f454();  /* FUN_0034f454 */
extern uint64_t sk_rt_0034f514();  /* FUN_0034f514 */
extern uint64_t sk_rt_0034f5b4();  /* FUN_0034f5b4 */
extern uint64_t sk_rt_0034f644();  /* FUN_0034f644 */
extern cl4_result_t sk_rt_0034f958();  /* FUN_0034f958 */
extern uint64_t sk_rt_0034fb88();  /* FUN_0034fb88 */
extern uint64_t sk_rt_0034fd3c();  /* FUN_0034fd3c */
extern uint64_t sk_rt_0034fd8c();  /* FUN_0034fd8c */
extern uint64_t sk_rt_0034fde0();  /* FUN_0034fde0 */
extern uint64_t sk_rt_0034feb0();  /* FUN_0034feb0 */
extern cl4_result_t sk_rt_0034ffb8();  /* FUN_0034ffb8 */
extern uint64_t sk_rt_00350088();  /* FUN_00350088 */
extern uint64_t sk_rt_0035012c();  /* FUN_0035012c */
extern uint64_t sk_rt_00350220();  /* FUN_00350220 */
extern uint64_t sk_rt_00350298();  /* FUN_00350298 */
extern uint64_t sk_rt_00350308();  /* FUN_00350308 */
extern uint64_t sk_rt_0035036c();  /* FUN_0035036c */
extern uint64_t sk_rt_00350390();  /* FUN_00350390 */
extern uint64_t sk_rt_003503a0();  /* FUN_003503a0 */
extern uint64_t sk_rt_00350410();  /* FUN_00350410 */
extern uint64_t sk_rt_00350428();  /* FUN_00350428 */
extern uint64_t sk_rt_00350434();  /* FUN_00350434 */
extern uint64_t sk_rt_0035044c();  /* FUN_0035044c */
extern uint64_t sk_rt_00350464();  /* FUN_00350464 */
extern cl4_result_t sk_rt_00350470();  /* FUN_00350470 */
extern uint64_t sk_rt_00350494();  /* FUN_00350494 */
extern uint64_t sk_rt_003504a0();  /* FUN_003504a0 */
extern uint64_t sk_rt_003504ac();  /* FUN_003504ac */
extern uint64_t sk_rt_003504b8();  /* FUN_003504b8 */
extern uint64_t sk_rt_003504c4();  /* FUN_003504c4 */
extern uint64_t sk_rt_003504d0();  /* FUN_003504d0 */
extern cl4_result_t sk_rt_003504e8();  /* FUN_003504e8 */
extern cl4_result_t sk_rt_003504f4();  /* FUN_003504f4 */
extern cl4_result_t sk_rt_00350500();  /* FUN_00350500 */
extern cl4_result_t sk_rt_0035050c();  /* FUN_0035050c */
extern uint64_t sk_rt_00350518();  /* FUN_00350518 */
extern cl4_result_t sk_rt_00350524();  /* FUN_00350524 */
extern uint64_t sk_rt_0035053c();  /* FUN_0035053c */
extern uint64_t sk_rt_0035056c();  /* FUN_0035056c */
extern uint64_t sk_rt_003505c4();  /* FUN_003505c4 */
extern uint64_t sk_rt_003505d0();  /* FUN_003505d0 */
extern uint64_t sk_rt_003505e8();  /* FUN_003505e8 */
extern uint64_t sk_rt_00350600();  /* FUN_00350600 */
extern cl4_result_t sk_rt_0035060c();  /* FUN_0035060c */
extern cl4_result_t sk_rt_00350618();  /* FUN_00350618 */
extern uint64_t sk_rt_00350624();  /* FUN_00350624 */
extern uint64_t sk_rt_0035063c();  /* FUN_0035063c */
extern uint64_t sk_rt_00350648();  /* FUN_00350648 */
extern uint64_t sk_rt_0035066c();  /* FUN_0035066c */
extern uint64_t sk_rt_003506e8();  /* FUN_003506e8 */
extern cl4_result_t sk_rt_00350720();  /* FUN_00350720 */
extern uint64_t sk_rt_00350738();  /* FUN_00350738 */
extern uint64_t sk_rt_00350744();  /* FUN_00350744 */
extern uint64_t sk_rt_00350750();  /* FUN_00350750 */
extern uint64_t sk_rt_00350768();  /* FUN_00350768 */
extern uint64_t sk_rt_00350780();  /* FUN_00350780 */
extern uint64_t sk_rt_00350798();  /* FUN_00350798 */
extern uint64_t sk_rt_003507bc();  /* FUN_003507bc */
extern uint64_t sk_rt_003507e0();  /* FUN_003507e0 */
extern uint64_t sk_rt_00350804();  /* FUN_00350804 */
extern uint64_t sk_rt_00350810();  /* FUN_00350810 */
extern cl4_result_t sk_rt_0035084c();  /* FUN_0035084c */
extern uint64_t sk_rt_00350878();  /* FUN_00350878 */
extern uint64_t sk_rt_00350884();  /* FUN_00350884 */
extern uint64_t sk_rt_003508a8();  /* FUN_003508a8 */
extern cl4_result_t sk_rt_003508b4();  /* FUN_003508b4 */
extern uint64_t sk_rt_003508c0();  /* FUN_003508c0 */
extern uint64_t sk_rt_003508cc();  /* FUN_003508cc */
extern uint64_t sk_rt_003508d8();  /* FUN_003508d8 */
extern uint64_t sk_rt_003508e4();  /* FUN_003508e4 */
extern uint64_t sk_rt_003508f0();  /* FUN_003508f0 */
extern uint64_t sk_rt_003508fc();  /* FUN_003508fc */
extern uint64_t sk_rt_00350908();  /* FUN_00350908 */
extern uint64_t sk_rt_00350914();  /* FUN_00350914 */
extern uint64_t sk_rt_00350920();  /* FUN_00350920 */
extern uint64_t sk_rt_0035092c();  /* FUN_0035092c */
extern uint64_t sk_rt_00350944();  /* FUN_00350944 */
extern uint64_t sk_rt_00350950();  /* FUN_00350950 */
extern uint64_t sk_rt_00350968();  /* FUN_00350968 */
extern cl4_result_t sk_rt_003509b0();  /* FUN_003509b0 */
extern uint64_t sk_rt_003509bc();  /* FUN_003509bc */
extern uint64_t sk_rt_003509c8();  /* FUN_003509c8 */
extern uint64_t sk_rt_003509d4();  /* FUN_003509d4 */
extern uint64_t sk_rt_003509e0();  /* FUN_003509e0 */
extern uint64_t sk_rt_00350a04();  /* FUN_00350a04 */
extern uint64_t sk_rt_00350a1c();  /* FUN_00350a1c */
extern uint64_t sk_rt_00350a34();  /* FUN_00350a34 */
extern uint64_t sk_rt_00350a40();  /* FUN_00350a40 */
extern uint64_t sk_rt_00350a64();  /* FUN_00350a64 */
extern uint64_t sk_rt_00350a70();  /* FUN_00350a70 */
extern uint64_t sk_rt_00350a7c();  /* FUN_00350a7c */
extern uint64_t sk_rt_00350a88();  /* FUN_00350a88 */
extern uint64_t sk_rt_00350aac();  /* FUN_00350aac */
extern cl4_result_t sk_rt_00350ab8();  /* FUN_00350ab8 */
extern uint64_t sk_rt_00350ac4();  /* FUN_00350ac4 */
extern uint64_t sk_rt_00350ad0();  /* FUN_00350ad0 */
extern uint64_t sk_rt_00350af4();  /* FUN_00350af4 */
extern cl4_result_t sk_rt_00350b00();  /* FUN_00350b00 */
extern uint64_t sk_rt_00350b24();  /* FUN_00350b24 */
extern uint64_t sk_rt_00350b30();  /* FUN_00350b30 */
extern cl4_result_t sk_rt_00350b3c();  /* FUN_00350b3c */
extern uint64_t sk_rt_00350b48();  /* FUN_00350b48 */
extern uint64_t sk_rt_00350b78();  /* FUN_00350b78 */
extern uint64_t sk_rt_00350b84();  /* FUN_00350b84 */
extern uint64_t sk_rt_00350ba8();  /* FUN_00350ba8 */
extern uint64_t sk_rt_00350bb4();  /* FUN_00350bb4 */
extern uint64_t sk_rt_00350bd8();  /* FUN_00350bd8 */
extern cl4_result_t sk_rt_00350bf0();  /* FUN_00350bf0 */
extern uint64_t sk_rt_00350bfc();  /* FUN_00350bfc */
extern uint64_t sk_rt_00350c08();  /* FUN_00350c08 */
extern uint64_t sk_rt_00350c14();  /* FUN_00350c14 */
extern uint64_t sk_rt_00350c2c();  /* FUN_00350c2c */
extern uint64_t sk_rt_00350c38();  /* FUN_00350c38 */
extern uint64_t sk_rt_00350c50();  /* FUN_00350c50 */
extern cl4_result_t sk_rt_00350c80();  /* FUN_00350c80 */
extern uint64_t sk_rt_00350e64();  /* FUN_00350e64 */
extern cl4_result_t sk_rt_00350ea4();  /* FUN_00350ea4 */
extern uint64_t sk_rt_00350ed0();  /* FUN_00350ed0 */
extern uint64_t sk_rt_00350f3c();  /* FUN_00350f3c */
extern uint64_t sk_rt_00350f4c();  /* FUN_00350f4c */
extern uint64_t sk_rt_00351058();  /* FUN_00351058 */
extern uint64_t sk_rt_003510ac();  /* FUN_003510ac */
extern uint64_t sk_rt_003510dc();  /* FUN_003510dc */
extern uint64_t sk_rt_00351100();  /* FUN_00351100 */
extern uint64_t sk_rt_00351118();  /* FUN_00351118 */
extern cl4_result_t sk_rt_00351130();  /* FUN_00351130 */
extern cl4_result_t sk_rt_0035113c();  /* FUN_0035113c */
extern uint64_t sk_rt_00351148();  /* FUN_00351148 */
extern uint64_t sk_rt_00351160();  /* FUN_00351160 */
extern uint64_t sk_rt_00351178();  /* FUN_00351178 */
extern uint64_t sk_rt_00351184();  /* FUN_00351184 */
extern uint64_t sk_rt_00351190();  /* FUN_00351190 */
extern uint64_t sk_rt_0035119c();  /* FUN_0035119c */
extern uint64_t sk_rt_003511c0();  /* FUN_003511c0 */
extern uint64_t sk_rt_003511d8();  /* FUN_003511d8 */
extern uint64_t sk_rt_00351220();  /* FUN_00351220 */
extern uint64_t sk_rt_00351238();  /* FUN_00351238 */
extern uint64_t sk_rt_00351250();  /* FUN_00351250 */
extern uint64_t sk_rt_00351274();  /* FUN_00351274 */
extern uint64_t sk_rt_0035128c();  /* FUN_0035128c */
extern uint64_t sk_rt_00351298();  /* FUN_00351298 */
extern uint64_t sk_rt_003512c0();  /* FUN_003512c0 */
extern uint64_t sk_rt_003512cc();  /* FUN_003512cc */
extern uint64_t sk_rt_00351300();  /* FUN_00351300 */
extern uint64_t sk_rt_00351318();  /* FUN_00351318 */
extern uint64_t sk_rt_00351348();  /* FUN_00351348 */
extern cl4_result_t sk_rt_00351354();  /* FUN_00351354 */
extern uint64_t sk_rt_00351384();  /* FUN_00351384 */
extern uint64_t sk_rt_003513a8();  /* FUN_003513a8 */
extern uint64_t sk_rt_003513c0();  /* FUN_003513c0 */
extern uint64_t sk_rt_003513fc();  /* FUN_003513fc */
extern uint64_t sk_rt_00351414();  /* FUN_00351414 */
extern uint64_t sk_rt_00351420();  /* FUN_00351420 */
extern uint64_t sk_rt_003514ac();  /* FUN_003514ac */
extern uint64_t sk_rt_003514b8();  /* FUN_003514b8 */
extern uint64_t sk_rt_003514d0();  /* FUN_003514d0 */
extern uint64_t sk_rt_00351554();  /* FUN_00351554 */
extern uint64_t sk_rt_0035159c();  /* FUN_0035159c */
extern uint64_t sk_rt_003515d8();  /* FUN_003515d8 */
extern uint64_t sk_rt_003515e4();  /* FUN_003515e4 */
extern uint64_t sk_rt_003515fc();  /* FUN_003515fc */
extern uint64_t sk_rt_0035169c();  /* FUN_0035169c */
extern uint64_t sk_rt_003516a8();  /* FUN_003516a8 */
extern uint64_t sk_rt_003516b4();  /* FUN_003516b4 */
extern uint64_t sk_rt_003516cc();  /* FUN_003516cc */
extern uint64_t sk_rt_003516d8();  /* FUN_003516d8 */
extern uint64_t sk_rt_003516f0();  /* FUN_003516f0 */
extern uint64_t sk_rt_00351744();  /* FUN_00351744 */
extern uint64_t sk_rt_00351750();  /* FUN_00351750 */
extern uint64_t sk_rt_00351790();  /* FUN_00351790 */
extern cl4_result_t sk_rt_003517b4();  /* FUN_003517b4 */
extern uint64_t sk_rt_00351894();  /* FUN_00351894 */
extern uint64_t sk_rt_003518a0();  /* FUN_003518a0 */
extern uint64_t sk_rt_003518b8();  /* FUN_003518b8 */
extern uint64_t sk_rt_003518c4();  /* FUN_003518c4 */
extern uint64_t sk_rt_00351990();  /* FUN_00351990 */
extern uint64_t sk_rt_0035199c();  /* FUN_0035199c */
extern uint64_t sk_rt_003519b4();  /* FUN_003519b4 */
extern uint64_t sk_rt_003519d4();  /* FUN_003519d4 */
extern uint64_t sk_rt_00351a14();  /* FUN_00351a14 */
extern uint64_t sk_rt_00351a2c();  /* FUN_00351a2c */
extern uint64_t sk_rt_00351a38();  /* FUN_00351a38 */
extern uint64_t sk_rt_00351aa4();  /* FUN_00351aa4 */
extern uint64_t sk_rt_00351ad4();  /* FUN_00351ad4 */
extern uint64_t sk_rt_00351b2c();  /* FUN_00351b2c */
extern uint64_t sk_rt_00351b84();  /* FUN_00351b84 */
extern cl4_result_t sk_rt_00351bac();  /* FUN_00351bac */
extern uint64_t sk_rt_00351bec();  /* FUN_00351bec */
extern uint64_t sk_rt_00351c10();  /* FUN_00351c10 */
extern uint64_t sk_rt_00351c28();  /* FUN_00351c28 */
extern uint64_t sk_rt_00351c4c();  /* FUN_00351c4c */
extern uint64_t sk_rt_00351c58();  /* FUN_00351c58 */
extern uint64_t sk_rt_00351cc4();  /* FUN_00351cc4 */
extern uint64_t sk_rt_00351cd0();  /* FUN_00351cd0 */
extern uint64_t sk_rt_00351d0c();  /* FUN_00351d0c */
extern cl4_result_t sk_rt_00351d24();  /* FUN_00351d24 */
extern uint64_t sk_rt_00351da8();  /* FUN_00351da8 */
extern uint64_t sk_rt_00351dcc();  /* FUN_00351dcc */
extern uint64_t sk_rt_00351dfc();  /* FUN_00351dfc */
extern cl4_result_t sk_rt_00351e08();  /* FUN_00351e08 */
extern uint64_t sk_rt_00351e6c();  /* FUN_00351e6c */
extern uint64_t sk_rt_00351e84();  /* FUN_00351e84 */
extern uint64_t sk_rt_00351e90();  /* FUN_00351e90 */
extern uint64_t sk_rt_00351ec0();  /* FUN_00351ec0 */
extern uint64_t sk_rt_00351ef8();  /* FUN_00351ef8 */
extern uint64_t sk_rt_00351f10();  /* FUN_00351f10 */
extern uint64_t sk_rt_00351f28();  /* FUN_00351f28 */
extern uint64_t sk_rt_00351f88();  /* FUN_00351f88 */
extern uint64_t sk_rt_00352018();  /* FUN_00352018 */
extern uint64_t sk_rt_00352350();  /* FUN_00352350 */
extern uint64_t sk_rt_00352370();  /* FUN_00352370 */
extern uint64_t sk_rt_00352438();  /* FUN_00352438 */
extern uint64_t sk_rt_00352468();  /* FUN_00352468 */
extern uint64_t sk_rt_00352474();  /* FUN_00352474 */
extern cl4_result_t sk_rt_00352498();  /* FUN_00352498 */
extern uint64_t sk_rt_00352680();  /* FUN_00352680 */
extern uint64_t sk_rt_00352698();  /* FUN_00352698 */
extern uint64_t sk_rt_00352758();  /* FUN_00352758 */
extern uint64_t sk_rt_00352798();  /* FUN_00352798 */
extern uint64_t sk_rt_003527e0();  /* FUN_003527e0 */
extern uint64_t sk_rt_00352800();  /* FUN_00352800 */
extern uint64_t sk_rt_00352840();  /* FUN_00352840 */
extern uint64_t sk_rt_00352920();  /* FUN_00352920 */
extern uint64_t sk_rt_00352a4c();  /* FUN_00352a4c */
extern uint64_t sk_rt_00352af0();  /* FUN_00352af0 */
extern uint64_t sk_rt_00352b98();  /* FUN_00352b98 */
extern cl4_result_t sk_rt_00352ba4();  /* FUN_00352ba4 */
extern uint64_t sk_rt_00352bb0();  /* FUN_00352bb0 */
extern uint64_t sk_rt_00352bbc();  /* FUN_00352bbc */
extern uint64_t sk_rt_00352c80();  /* FUN_00352c80 */
extern uint64_t sk_rt_00352c8c();  /* FUN_00352c8c */
extern uint64_t sk_rt_00352c98();  /* FUN_00352c98 */
extern uint64_t sk_rt_00352d28();  /* FUN_00352d28 */
extern uint64_t sk_rt_00352d34();  /* FUN_00352d34 */
extern uint64_t sk_rt_00352d64();  /* FUN_00352d64 */
extern uint64_t sk_rt_00352d70();  /* FUN_00352d70 */
extern uint64_t sk_rt_00352db8();  /* FUN_00352db8 */
extern uint64_t sk_rt_00352ddc();  /* FUN_00352ddc */
extern uint64_t sk_rt_00352df4();  /* FUN_00352df4 */
extern uint64_t sk_rt_00352e6c();  /* FUN_00352e6c */
extern uint64_t sk_rt_00352ee4();  /* FUN_00352ee4 */
extern uint64_t sk_rt_00352efc();  /* FUN_00352efc */
extern uint64_t sk_rt_00352fe8();  /* FUN_00352fe8 */
extern uint64_t sk_rt_003530bc();  /* FUN_003530bc */
extern uint64_t sk_rt_003530e8();  /* FUN_003530e8 */
extern uint64_t sk_rt_00353100();  /* FUN_00353100 */
extern uint64_t sk_rt_00353130();  /* FUN_00353130 */
extern uint64_t sk_rt_0035313c();  /* FUN_0035313c */
extern uint64_t sk_rt_00353190();  /* FUN_00353190 */
extern uint64_t sk_rt_0035319c();  /* FUN_0035319c */
extern uint64_t sk_rt_003531d8();  /* FUN_003531d8 */
extern uint64_t sk_rt_00353208();  /* FUN_00353208 */
extern uint64_t sk_rt_00353214();  /* FUN_00353214 */
extern uint64_t sk_rt_0035336c();  /* FUN_0035336c */
extern uint64_t sk_rt_00353480();  /* FUN_00353480 */
extern uint64_t sk_rt_003534bc();  /* FUN_003534bc */
extern uint64_t sk_rt_00353504();  /* FUN_00353504 */
extern uint64_t sk_rt_0035351c();  /* FUN_0035351c */
extern uint64_t sk_rt_00353534();  /* FUN_00353534 */
extern uint64_t sk_rt_0035367c();  /* FUN_0035367c */
extern uint64_t sk_rt_00353734();  /* FUN_00353734 */
extern uint64_t sk_rt_003537f0();  /* FUN_003537f0 */
extern uint64_t sk_rt_003537fc();  /* FUN_003537fc */
extern uint64_t sk_rt_003538b0();  /* FUN_003538b0 */
extern uint64_t sk_rt_00353a00();  /* FUN_00353a00 */
extern uint64_t sk_rt_00353a24();  /* FUN_00353a24 */
extern uint64_t sk_rt_00353a90();  /* FUN_00353a90 */
extern uint64_t sk_rt_00353aa0();  /* FUN_00353aa0 */
extern uint64_t sk_rt_00353abc();  /* FUN_00353abc */
extern uint64_t sk_rt_00353ac8();  /* FUN_00353ac8 */
extern uint64_t sk_rt_00353b94();  /* FUN_00353b94 */
extern uint64_t sk_rt_00353ccc();  /* FUN_00353ccc */
extern cl4_result_t sk_rt_00353cfc();  /* FUN_00353cfc */
extern uint64_t sk_rt_00353d14();  /* FUN_00353d14 */
extern cl4_result_t sk_rt_00353d7c();  /* FUN_00353d7c */
extern uint64_t sk_rt_00353d94();  /* FUN_00353d94 */
extern cl4_result_t sk_rt_00353dac();  /* FUN_00353dac */
extern uint64_t sk_rt_00353e7c();  /* FUN_00353e7c */
extern uint64_t sk_rt_00353e88();  /* FUN_00353e88 */
extern uint64_t sk_rt_00353efc();  /* FUN_00353efc */
extern uint64_t sk_rt_00353f14();  /* FUN_00353f14 */
extern uint64_t sk_rt_003542d0();  /* FUN_003542d0 */
extern uint64_t sk_rt_00354300();  /* FUN_00354300 */
extern uint64_t sk_rt_00354318();  /* FUN_00354318 */
extern uint64_t sk_rt_00354324();  /* FUN_00354324 */
extern uint64_t sk_rt_0035433c();  /* FUN_0035433c */
extern uint64_t sk_rt_00354364();  /* FUN_00354364 */
extern uint64_t sk_rt_003543ac();  /* FUN_003543ac */
extern uint64_t sk_rt_003543b8();  /* FUN_003543b8 */
extern uint64_t sk_rt_003543c4();  /* FUN_003543c4 */
extern uint64_t sk_rt_003544c8();  /* FUN_003544c8 */
extern uint64_t sk_rt_00354618();  /* FUN_00354618 */
extern uint64_t sk_rt_00354624();  /* FUN_00354624 */
extern uint64_t sk_rt_00354660();  /* FUN_00354660 */
extern cl4_result_t sk_rt_00354744();  /* FUN_00354744 */
extern uint64_t sk_rt_003548a0();  /* FUN_003548a0 */
extern uint64_t sk_rt_003548e8();  /* FUN_003548e8 */
extern uint64_t sk_rt_00354930();  /* FUN_00354930 */
extern uint64_t sk_rt_003549c0();  /* FUN_003549c0 */
extern uint64_t sk_rt_00354b2c();  /* FUN_00354b2c */
extern uint64_t sk_rt_00354b68();  /* FUN_00354b68 */
extern uint64_t sk_rt_00354b74();  /* FUN_00354b74 */
extern uint64_t sk_rt_00354ca8();  /* FUN_00354ca8 */
extern uint64_t sk_rt_00354d2c();  /* FUN_00354d2c */
extern uint64_t sk_rt_00354d50();  /* FUN_00354d50 */
extern uint64_t sk_rt_00354ddc();  /* FUN_00354ddc */
extern uint64_t sk_rt_00354de8();  /* FUN_00354de8 */
extern uint64_t sk_rt_00354f1c();  /* FUN_00354f1c */
extern uint64_t sk_rt_00354f4c();  /* FUN_00354f4c */
extern uint64_t sk_rt_00355100();  /* FUN_00355100 */
extern uint64_t sk_rt_00355314();  /* FUN_00355314 */
extern uint64_t sk_rt_00355430();  /* FUN_00355430 */
extern uint64_t sk_rt_0035543c();  /* FUN_0035543c */
extern uint64_t sk_rt_00355604();  /* FUN_00355604 */
extern uint64_t sk_rt_00355634();  /* FUN_00355634 */
extern uint64_t sk_rt_003556f4();  /* FUN_003556f4 */
extern uint64_t sk_rt_00355958();  /* FUN_00355958 */
extern uint64_t sk_rt_003559d8();  /* FUN_003559d8 */
extern uint64_t sk_rt_00355cb0();  /* FUN_00355cb0 */
extern uint64_t sk_rt_00355e74();  /* FUN_00355e74 */
extern uint64_t sk_rt_00355ea4();  /* FUN_00355ea4 */
extern uint64_t sk_rt_00355f40();  /* FUN_00355f40 */
extern uint64_t sk_rt_00356000();  /* FUN_00356000 */
extern cl4_result_t sk_rt_0035603c();  /* FUN_0035603c */
extern uint64_t sk_rt_00356048();  /* FUN_00356048 */
extern uint64_t sk_rt_00356078();  /* FUN_00356078 */
extern uint64_t sk_rt_003561a0();  /* FUN_003561a0 */
extern uint64_t sk_rt_003562bc();  /* FUN_003562bc */
extern uint64_t sk_rt_003562e0();  /* FUN_003562e0 */
extern uint64_t sk_rt_00356454();  /* FUN_00356454 */
extern uint64_t sk_rt_0035646c();  /* FUN_0035646c */
extern uint64_t sk_rt_003564d0();  /* FUN_003564d0 */
extern uint64_t sk_rt_003564e8();  /* FUN_003564e8 */
extern uint64_t sk_rt_00356768();  /* FUN_00356768 */
extern uint64_t sk_rt_0035678c();  /* FUN_0035678c */
extern uint64_t sk_rt_003567a4();  /* FUN_003567a4 */
extern uint64_t sk_rt_003567b0();  /* FUN_003567b0 */
extern uint64_t sk_rt_003567bc();  /* FUN_003567bc */
extern uint64_t sk_rt_00356864();  /* FUN_00356864 */
extern uint64_t sk_rt_0035694c();  /* FUN_0035694c */
extern uint64_t sk_rt_00356958();  /* FUN_00356958 */
extern uint64_t sk_rt_00356964();  /* FUN_00356964 */
extern uint64_t sk_rt_00356a2c();  /* FUN_00356a2c */
extern uint64_t sk_rt_00356ae8();  /* FUN_00356ae8 */
extern uint64_t sk_rt_00356b80();  /* FUN_00356b80 */
extern uint64_t sk_rt_00356cd4();  /* FUN_00356cd4 */
extern uint64_t sk_rt_00356e1c();  /* FUN_00356e1c */
extern uint64_t sk_rt_0035705c();  /* FUN_0035705c */
extern uint64_t sk_rt_00357368();  /* FUN_00357368 */
extern uint64_t sk_rt_00357788();  /* FUN_00357788 */
extern uint64_t sk_rt_00357884();  /* FUN_00357884 */
extern uint64_t sk_rt_003578a8();  /* FUN_003578a8 */
extern uint64_t sk_rt_003578b4();  /* FUN_003578b4 */
extern uint64_t sk_rt_003579d8();  /* FUN_003579d8 */
extern uint64_t sk_rt_00357bc4();  /* FUN_00357bc4 */
extern uint64_t sk_rt_00357c20();  /* FUN_00357c20 */
extern uint64_t sk_rt_00357c74();  /* FUN_00357c74 */
extern uint64_t sk_rt_00357cb4();  /* FUN_00357cb4 */
extern uint64_t sk_rt_00358164();  /* FUN_00358164 */
extern uint64_t sk_rt_0035847c();  /* FUN_0035847c */
extern uint64_t sk_rt_00358490();  /* FUN_00358490 */
extern uint64_t sk_rt_0035849c();  /* FUN_0035849c */
extern uint64_t sk_rt_00358630();  /* FUN_00358630 */
extern uint64_t sk_rt_0035863c();  /* FUN_0035863c */
extern uint64_t sk_rt_00358804();  /* FUN_00358804 */
extern uint64_t sk_rt_00358918();  /* FUN_00358918 */
extern uint64_t sk_rt_00358948();  /* FUN_00358948 */
extern uint64_t sk_rt_0035896c();  /* FUN_0035896c */
extern uint64_t sk_rt_00358978();  /* FUN_00358978 */
extern uint64_t sk_rt_00358ac8();  /* FUN_00358ac8 */
extern uint64_t sk_rt_00358e7c();  /* FUN_00358e7c */
extern uint64_t sk_rt_00358e88();  /* FUN_00358e88 */
extern uint64_t sk_rt_00358f84();  /* FUN_00358f84 */
extern uint64_t sk_rt_003593e8();  /* FUN_003593e8 */
extern uint64_t sk_rt_00359568();  /* FUN_00359568 */
extern uint64_t sk_rt_003595d8();  /* FUN_003595d8 */
extern uint64_t sk_rt_003599a0();  /* FUN_003599a0 */
extern uint64_t sk_rt_00359a84();  /* FUN_00359a84 */
extern uint64_t sk_rt_00359c58();  /* FUN_00359c58 */
extern uint64_t sk_rt_00359cd8();  /* FUN_00359cd8 */
extern uint64_t sk_rt_00359e34();  /* FUN_00359e34 */
extern uint64_t sk_rt_00359e40();  /* FUN_00359e40 */
extern uint64_t sk_rt_00359f08();  /* FUN_00359f08 */
extern uint64_t sk_rt_00359f48();  /* FUN_00359f48 */
extern uint64_t sk_rt_00359f8c();  /* FUN_00359f8c */
extern uint64_t sk_rt_0035a16c();  /* FUN_0035a16c */
extern uint64_t sk_rt_0035a2d0();  /* FUN_0035a2d0 */
extern uint64_t sk_rt_0035a3f4();  /* FUN_0035a3f4 */
extern uint64_t sk_rt_0035a49c();  /* FUN_0035a49c */
extern uint64_t sk_rt_0035a4e0();  /* FUN_0035a4e0 */
extern uint64_t sk_rt_0035a518();  /* FUN_0035a518 */
extern uint64_t sk_rt_0035acdc();  /* FUN_0035acdc */
extern uint64_t sk_rt_0035acfc();  /* FUN_0035acfc */
extern uint64_t sk_rt_0036986c();  /* FUN_0036986c */
extern uint64_t sk_rt_0036a908();  /* FUN_0036a908 */
extern uint64_t sk_rt_0036a940();  /* FUN_0036a940 */
extern uint64_t sk_rt_0036b118();  /* FUN_0036b118 */
extern uint64_t sk_rt_0036b270();  /* FUN_0036b270 */
extern uint64_t sk_rt_003722e4();  /* FUN_003722e4 */
extern cl4_result_t sk_rt_00376820();  /* FUN_00376820 */
extern uint64_t sk_rt_00377824();  /* FUN_00377824 */
extern uint64_t sk_rt_00377bec();  /* FUN_00377bec */
extern uint64_t sk_rt_003a25d4();  /* FUN_003a25d4 */
extern uint64_t sk_rt_003a2610();  /* FUN_003a2610 */
extern uint64_t sk_rt_0060e3fc();  /* FUN_0060e3fc */
extern uint64_t sk_rt_0060e40c();  /* FUN_0060e40c */
extern uint64_t sk_rt_0026bdc4();  /* FUN_0026bdc4 */
extern uint64_t sk_rt_0026c274();  /* FUN_0026c274 */
extern uint64_t sk_rt_0026c2a0();  /* FUN_0026c2a0 */
extern uint64_t sk_rt_0026c6d8();  /* FUN_0026c6d8 */
extern uint64_t sk_rt_0027b41c();  /* FUN_0027b41c */
extern uint64_t sk_rt_00350a24();  /* FUN_00350a24 */
extern uint64_t sk_rt_004c2450();  /* FUN_004c2450 */
extern uint64_t sk_rt_004e7b40();  /* FUN_004e7b40 */
extern uint64_t sk_rt_0026ca24();  /* FUN_0026ca24 */
extern uint64_t sk_rt_0026cbd0();  /* FUN_0026cbd0 */
extern uint64_t sk_rt_0026ea04();  /* FUN_0026ea04 */
extern uint64_t sk_rt_0026fe90();  /* FUN_0026fe90 */
extern uint64_t sk_rt_00270074();  /* FUN_00270074 */
extern uint64_t sk_rt_00270744();  /* FUN_00270744 */
extern uint64_t sk_rt_00270ab4();  /* FUN_00270ab4 */
extern uint64_t sk_rt_00270ae4();  /* FUN_00270ae4 */
extern uint64_t sk_rt_00270d80();  /* FUN_00270d80 */
extern uint64_t sk_rt_00270e80();  /* FUN_00270e80 */
extern uint64_t sk_rt_002710ac();  /* FUN_002710ac */
extern uint64_t sk_rt_00271304();  /* FUN_00271304 */
extern uint64_t sk_rt_00271b70();  /* FUN_00271b70 */
extern uint64_t sk_rt_00271bdc();  /* FUN_00271bdc */
extern uint64_t sk_rt_00271fa0();  /* FUN_00271fa0 */
extern uint64_t sk_rt_00273310();  /* FUN_00273310 */
extern cl4_result_t sk_rt_0027590c();  /* FUN_0027590c */
extern cl4_result_t sk_rt_00275cd0();  /* FUN_00275cd0 */
extern uint64_t sk_rt_00276034();  /* FUN_00276034 */
extern uint64_t sk_rt_002775c8();  /* FUN_002775c8 */


/* ===================================================================== */
/* Mechanical thunks & forwarders (empty wrappers to in-slice/shared code) */
/* ===================================================================== */

/* FUN_0026cdb8 @ 0x0026cdb8   (est. sk_thunk_range_lt)
 * Ghidra: void FUN_0026cdb8(void)
 * Forwarding thunk to the shared range-comparison runtime helper FUN_00231b0c.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_range_lt(void)
{
    sk_rt_00231b0c();
}

/* FUN_0026cdbc @ 0x0026cdbc   (est. sk_thunk_range_gt)
 * Ghidra: void FUN_0026cdbc(void)
 * Forwarding thunk to the shared range-comparison runtime helper FUN_00231b0c.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_range_gt(void)
{
    sk_rt_00231b0c();
}

/* FUN_0026da9c @ 0x0026da9c   (est. sk_thunk_da9c)
 * Ghidra: void FUN_0026da9c(void)
 * Forwards to the in-slice helper FUN_0026ca24.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_da9c(void)
{
    sk_rt_0026ca24();
}

/* FUN_0026daa0 @ 0x0026daa0   (est. sk_thunk_daa0)
 * Ghidra: void FUN_0026daa0(void)
 * Forwards to the in-slice helper FUN_0026ca24.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_daa0(void)
{
    sk_rt_0026ca24();
}

/* FUN_0026e9d8 @ 0x0026e9d8   (est. sk_thunk_e9d8)
 * Ghidra: void FUN_0026e9d8(void)
 * Forwards to the in-slice string transform FUN_0026ea04.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_e9d8(void)
{
    sk_rt_0026ea04();
}

/* FUN_0026e9dc @ 0x0026e9dc   (est. sk_thunk_e9dc)
 * Ghidra: void FUN_0026e9dc(void)
 * Forwards to the in-slice string transform FUN_0026ea04.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_e9dc(void)
{
    sk_rt_0026ea04();
}

/* FUN_0026f138 @ 0x0026f138   (est. sk_thunk_f138)
 * Ghidra: void FUN_0026f138(void)
 * Forwards to the in-slice range dispatch FUN_00270ab4.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_f138(void)
{
    sk_rt_00270ab4();
}

/* FUN_0026f13c @ 0x0026f13c   (est. sk_thunk_f13c)
 * Ghidra: void FUN_0026f13c(void)
 * Forwards to the in-slice range dispatch FUN_00270ab4.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_f13c(void)
{
    sk_rt_00270ab4();
}

/* FUN_0026f7cc @ 0x0026f7cc   (est. sk_thunk_f7cc)
 * Ghidra: void FUN_0026f7cc(void)
 * Forwards to the in-slice string op FUN_0026fe90.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_f7cc(void)
{
    sk_rt_0026fe90();
}

/* FUN_0026f7d0 @ 0x0026f7d0   (est. sk_thunk_f7d0)
 * Ghidra: void FUN_0026f7d0(void)
 * Forwards to the in-slice string op FUN_0026fe90.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_f7d0(void)
{
    sk_rt_0026fe90();
}

/* FUN_0026f7f8 @ 0x0026f7f8   (est. sk_thunk_f7f8)
 * Ghidra: void FUN_0026f7f8(void)
 * Forwards to the in-slice range dispatch FUN_00270ab4.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_f7f8(void)
{
    sk_rt_00270ab4();
}

/* FUN_0026f7fc @ 0x0026f7fc   (est. sk_thunk_f7fc)
 * Ghidra: void FUN_0026f7fc(void)
 * Forwards to the in-slice range dispatch FUN_00270ab4.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_f7fc(void)
{
    sk_rt_00270ab4();
}

/* FUN_0026f824 @ 0x0026f824   (est. sk_thunk_f824)
 * Ghidra: void FUN_0026f824(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Forwards to the range dispatch FUN_00270ae4 after resolving the flag/kind
 * from the collection's metadata header.
 * Confidence: low
 * Notes: dereferences the metadata word at (flags & ~1) - 8. */
void sk_thunk_f824(uint64_t a, uint64_t b, uint64_t flags)
{
    sk_rt_00270ae4(a, b, *(uint64_t *)((flags & 0xfffffffffffffffe) - 8));
}

/* FUN_00270048 @ 0x00270048   (est. sk_thunk_70048)
 * Ghidra: void FUN_00270048(void)
 * Forwards to the in-slice range dispatch FUN_00270ab4.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_70048(void)
{
    sk_rt_00270ab4();
}

/* FUN_0027004c @ 0x0027004c   (est. sk_thunk_7004c)
 * Ghidra: void FUN_0027004c(void)
 * Forwards to the in-slice range dispatch FUN_00270ab4.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_7004c(void)
{
    sk_rt_00270ab4();
}

/* FUN_00270a5c @ 0x00270a5c   (est. sk_thunk_70a5c)
 * Ghidra: void FUN_00270a5c(void)
 * Forwards to the in-slice string op FUN_0026fe90.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_70a5c(void)
{
    sk_rt_0026fe90();
}

/* FUN_00270a60 @ 0x00270a60   (est. sk_thunk_70a60)
 * Ghidra: void FUN_00270a60(void)
 * Forwards to the in-slice string op FUN_0026fe90.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_70a60(void)
{
    sk_rt_0026fe90();
}

/* FUN_00270a88 @ 0x00270a88   (est. sk_thunk_70a88)
 * Ghidra: void FUN_00270a88(void)
 * Forwards to the in-slice range dispatch FUN_00270ab4.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_70a88(void)
{
    sk_rt_00270ab4();
}

/* FUN_00270a8c @ 0x00270a8c   (est. sk_thunk_70a8c)
 * Ghidra: void FUN_00270a8c(void)
 * Forwards to the in-slice range dispatch FUN_00270ab4.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_70a8c(void)
{
    sk_rt_00270ab4();
}

/* FUN_0026fe64 @ 0x0026fe64   (est. sk_thunk_fe64)
 * Ghidra: void FUN_0026fe64(void)
 * Forwards to the in-slice string op FUN_0026fe90.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_fe64(void)
{
    sk_rt_0026fe90();
}

/* FUN_0026fe68 @ 0x0026fe68   (est. sk_thunk_fe68)
 * Ghidra: void FUN_0026fe68(void)
 * Forwards to the in-slice string op FUN_0026fe90.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_fe68(void)
{
    sk_rt_0026fe90();
}

/* FUN_00270ae4 @ 0x00270ae4   (est. sk_thunk_70ae4)
 * Ghidra: void FUN_00270ae4(void)
 * Forwards to the in-slice collection check FUN_00270074.
 * Confidence: low
 * Notes: tail-call wrapper. */
void sk_thunk_70ae4(void)
{
    sk_rt_00270074();
}

/* FUN_00273eb0 @ 0x00273eb0   (est. sk_fatal_73eb0)
 * Ghidra: void FUN_00273eb0(void)
 * Unconditional fatal-error path: reports a precondition failure and traps.
 * Confidence: high
 * Notes: FUN_00347d60 then noreturn FUN_001afe4c. */
void sk_fatal_73eb0(void)
{
    sk_rt_00347d60();
    sk_rt_001afe4c();
}

/* FUN_00274960 @ 0x00274960   (est. sk_fatal_74960)
 * Ghidra: void FUN_00274960(void)
 * Unconditional fatal-error path: reports a precondition failure and traps.
 * Confidence: high
 * Notes: FUN_00347d60 then noreturn FUN_001afe4c. */
void sk_fatal_74960(void)
{
    sk_rt_00347d60();
    sk_rt_001afe4c();
}

/* FUN_002740dc @ 0x002740dc   (est. sk_runtime_constant_capacity)
 * Ghidra: undefined8 FUN_002740dc(void)
 * Returns the fixed 4 GiB capacity constant used by a collection/resize path.
 * Confidence: high
 * Notes: returns 0x100000000. */
uint64_t sk_runtime_constant_capacity(void)
{
    return 0x100000000ull;
}

/* FUN_00271ce4 @ 0x00271ce4   (est. sk_bitbuffer_append_16)
 * Ghidra: undefined8 FUN_00271ce4(void)
 * Appends a 16-bit value into the packed UInt buffer via FUN_00271fa0.
 * Confidence: medium
 * Notes: returns 0. */
uint64_t sk_bitbuffer_append_16(void)
{
    sk_rt_00271fa0();
    return 0;
}

/* FUN_00271d24 @ 0x00271d24   (est. sk_utf8buffer_append_ret0)
 * Ghidra: undefined4 FUN_00271d24(void)
 * Delegates to the UTF-8 buffer append helper FUN_002c8df4; returns 0.
 * Confidence: low
 * Notes: returns 0. */
uint32_t sk_utf8buffer_append_ret0(void)
{
    sk_rt_002c8df4();
    return 0;
}

/* ===================================================================== */
/* Range / bounds-check core                                             */
/* ===================================================================== */

/* FUN_0026d8d4 @ 0x0026d8d4   (est. sk_range_fatal_lower_upper)
 * Ghidra: void FUN_0026d8d4(void)
 * Raises the fatal "Range requires lowerBound < upperBound" trap.
 * Confidence: high
 * Notes: noreturn; s_Fatal_error_005accd0, s_Range_requires_lowerBound_<__upp_005cda00,
 *   s_Swift_Range_swift_005cda30. */
void sk_range_fatal_lower_upper(void)
{
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11, 2, 0x2f9, 1);
}

/* FUN_0026d930 @ 0x0026d930   (est. sk_range_subscript_bounds)
 * Ghidra: void FUN_0026d930(undefined8 param_1, long param_2, ulong param_3)
 * Bounds-checks a subscript into a Range: resolves the metadata, reads the
 * collection's base/endpoints, and dispatches the element access through the
 * range's collection-view vtable.
 * Confidence: medium
 * Notes: view vtable calls at +0x20 (access) and +8 (release). */
void sk_range_subscript_bounds(uint64_t out, uint64_t range, uint64_t flags)
{
    uint64_t meta = *(uint64_t *)((flags & 0xfffffffffffffffe) - 8);
    uint64_t base = *(uint64_t *)(range + 0x10);
    uint64_t obj = *(uint64_t *)(base - 8);
    sk_rt_0036a908(*(uint64_t *)(obj + 0x40), 0);
    sk_rt_00310ca4; /* placeholder; view access */
    sk_rt_0026c6d8(out, range, meta);
    sk_rt_00377bec(*(uint64_t *)(obj + 8), base);
}

/* FUN_0026de60 @ 0x0026de60   (est. sk_collection_contains)
 * Ghidra: uint FUN_0026de60(undefined8 param_1, long param_2)
 * Membership test over a Range/Collection: obtains the collection's bounds
 * (start at +0x10, end at +0x18) and dispatches an element-equality compare,
 * returning whether the element is contained.
 * Confidence: medium
 * Notes: uses FUN_00310e20 predicate and FUN_0016186c comparison. */
uint32_t sk_collection_contains(uint64_t elem, uint64_t coll)
{
    uint64_t start = *(uint64_t *)(coll + 0x10);
    uint64_t end = *(uint64_t *)(coll + 0x18);
    uint64_t ok = sk_rt_00310e20(end);
    if ((ok & 1) == 0) {
        return 0;
    }
    int32_t off = *(int32_t *)(coll + 0x24);
    uint64_t res = sk_rt_0016186c(elem, start, end);
    return res & 1;
}

/* FUN_0026fa8c @ 0x0026fa8c   (est. sk_collection_contains_cl)
 * Ghidra: uint FUN_0026fa8c(undefined8 param_1, undefined8 param_2, code *param_3)
 * Closure-driven membership test: runs the caller's predicate over the
 * collection and returns the boolean result.
 * Confidence: medium
 * Notes: FUN_00358164 then predicate call via param_3. */
uint32_t sk_collection_contains_cl(uint64_t a, uint64_t b, void *pred)
{
    sk_rt_00358164();
    sk_rt_0035012c(pred);
    sk_rt_0034df74();
    return sk_rt_0034df74() & 1;
}

/* FUN_0026fe20 @ 0x0026fe20   (est. sk_collection_contains_cl2)
 * Ghidra: uint FUN_0026fe20(void)
 * Closure-driven membership test variant; predicate passed in x3.
 * Confidence: medium
 * Notes: mirror of FUN_0026fa8c with the predicate register in x3. */
uint32_t sk_collection_contains_cl2(void)
{
    void *pred = 0; /* in_x3 */
    sk_rt_00358164();
    sk_rt_0035012c(pred);
    sk_rt_0034df74();
    return sk_rt_0034df74() & 1;
}

/* FUN_0026da44 @ 0x0026da44   (est. sk_string_op_irqsave)
 * Ghidra: void FUN_0026da44(void)
 * A string/collection mutation guarded by interrupt save/restore and object
 * lock: saves IRQ state, takes the object lock, performs a shifted 16-byte
 * buffer operation, releases and restores IRQ state.
 * Confidence: low
 * Notes: FUN_00357cb4 (irqsave), FUN_00349944 (lock), NEON_ext on a 16-byte
 *   value, FUN_00376820 (dispatch), FUN_00357c74 (irqrestore). */
void sk_string_op_irqsave(void)
{
    sk_rt_00357cb4();
    sk_rt_00349944();
    /* 16-byte NEON rotate of the flag word */
    sk_rt_00376820();
    sk_rt_003498a8();
    sk_rt_001e3a28();
    sk_rt_00357c74();
}

/* FUN_0026f164 @ 0x0026f164   (est. sk_string_prepend)
 * Ghidra: void FUN_0026f164(void)
 * Prepends a scalar onto a string/collection: initializes a temp view,
 * copies the incoming scalar, and stores it at the collection head.
 * Confidence: medium
 * Notes: uses stack view auStack_78; FUN_000836a4/FUN_00353ccc view setup. */
void sk_string_prepend(void)
{
    sk_rt_0035acfc();
    sk_rt_0035a2d0();
    sk_rt_0034ad20();
    sk_rt_000a68c4();
    sk_rt_0034bd58();
    sk_rt_000836a4();
    sk_rt_00353ccc();
    uint64_t t = sk_rt_0031a14c();
    sk_rt_0034e6ac(t);
    sk_rt_00353504();
    if (0 == 0) { /* unaff_x21 check elided */
        sk_rt_0035543c();
        sk_rt_000836a4();
        sk_rt_0035159c();
        uint64_t t2 = sk_rt_0031a14c();
        sk_rt_003508c0(t2);
        sk_rt_00356958();
    }
    sk_rt_000026e8();
}

/* FUN_0026e938 @ 0x0026e938   (est. sk_string_scalar_loop)
 * Ghidra: void FUN_0026e938(void)
 * Walks a string/collection scalar-by-scalar dispatching to a runtime op,
 * using the element count at +0x24 for the iteration bound.
 * Confidence: low
 * Notes: FUN_0031945c predicate; FUN_003508d8 step. */
void sk_string_scalar_loop(void)
{
    sk_rt_0034a958();
    void *pred = (void *)sk_rt_0031945c();
    sk_rt_003508d8();
    sk_rt_003508d8();
}

/* FUN_0026e1d8 @ 0x0026e1d8   (est. sk_string_optional_unwrap)
 * Ghidra: undefined1 [16] FUN_0026e1d8(undefined8 param_1, undefined8 param_2)
 * Unwraps two Optional String values (param_1, param_2) into a pair of
 * non-optional strings, coercing a nil (0xe000000000000000) into the empty
 * string and otherwise validating/releasing the tag bits.
 * Confidence: medium
 * Notes: nil tag 0xe000000000000000, embedded-string tag 0xe3ba000000000000;
 *   FUN_00205844/FUN_00291ee0/FUN_002a4c98 string ops; FUN_003a25d4 release. */
cl4_result_t sk_string_optional_unwrap(uint64_t opt_a, uint64_t opt_b)
{
    cl4_result_t lo = { .lo = 0, .hi = 0xe000000000000000ull };
    cl4_result_t hi = { .lo = 0, .hi = 0xe000000000000000ull };
    sk_rt_00205844(&hi, lo, 0x677880, 0x6756a8, 0x66e1b8);
    /* resolve nil/embedded tags for first optional */
    if ((hi.hi & 0x2000000000000000ull) != 0) {
        /* inlined scalar */
    }
    if ((hi.hi & 0x2000000000000000ull) != 0 &&
        ((hi.lo & (hi.hi ^ 0xffffffffffffffffull)) >> 0x3d & 1) == 0) {
        sk_rt_003a25d4(hi.hi);
        /* became nil -> empty */
        return (cl4_result_t){ .lo = 0x3c2e2e, .hi = 0xe300000000000000ull };
    }
    /* ... second optional unwrap mirrored ... */
    sk_rt_00205844(&hi, hi, 0x677880, 0x6756a8, 0x66e1b8);
    return hi;
}

/* FUN_0026e3b0 @ 0x0026e3b0   (est. sk_string_subscript_optional)
 * Ghidra: void FUN_0026e3b0(void)
 * Subscripts a String at an Optional-bound index, coercing an out-of-bounds /
 * nil index to a nil result and otherwise returning the scalar.
 * Confidence: low
 * Notes: uses FUN_00354744 metadata, FUN_0035896c base, nil tag handling. */
void sk_string_subscript_optional(void)
{
    cl4_result_t md = sk_rt_00354744();
    uint64_t base = sk_rt_0035896c();
    uint64_t val = *(uint64_t *)(base + 0x10);
    sk_rt_003507e0();
    sk_rt_001b1780();
    uint64_t v = sk_rt_00349cbc();
    sk_rt_003a25d4();
    sk_rt_002a4c98(md.hi, 0xe300000000000000ull, 0, 3);
    sk_rt_001b1780();
    sk_rt_003544c8();
}

/* FUN_0026e490 @ 0x0026e490   (est. sk_string_transform_optional)
 * Ghidra: void FUN_0026e490(void)
 * Chained Optional String transform with multiple nil-check / release stages;
 * composes several partial-result updates and returns via the epilogue
 * helper. The four labelled stages each validate a scalar tag.
 * Confidence: low
 * Notes: many FUN_0034xxxx string-runtime ops; nil tags 0xe000000000000000. */
void sk_string_transform_optional(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    uint64_t v = *(uint64_t *)(cpu + 0x10);
    sk_rt_003499f0();
    cl4_result_t r1 = sk_rt_00106e3c();
    sk_rt_001a89a8(r1.lo, r1.hi, 1);
    sk_rt_00351e08();
    sk_rt_003a25d4(0xe000000000000000ull);
    sk_rt_003511d8();
    cl4_result_t r2 = sk_rt_001c050c();
    sk_rt_0034a274();
    /* stage-1 optional branch */
    sk_rt_003a25d4();
    /* stage-2 */
    cl4_result_t r3 = sk_rt_001a89a8();
    sk_rt_003a25d4(0xe000000000000000ull);
    sk_rt_00351f28();
    /* stage-3 */
    sk_rt_001a89a8();
    sk_rt_00354ddc();
    sk_rt_0034a900();
    /* stage-4 */
    cl4_result_t r4 = sk_rt_0006b6f4();
    sk_rt_0008e500(r4.lo, r4.hi);
}

/* FUN_0026e7e4 @ 0x0026e7e4   (est. sk_range_description_string)
 * Ghidra: void FUN_0026e7e4(void)
 * Builds the human-readable description of a Range: allocates a string
 * buffer, writes "lowerBound"/"upperBound" tokens and the two endpoints,
 * then returns it. Tokens are packed ASCII in the literals.
 * Confidence: medium
 * Notes: literals 0x756f427265776f6c ("lowerBou" little-endian) and
 *   0x756f427265707075 ("upperBou"); FUN_0036a940 alloc (size 0x80, tag 7). */
void sk_range_description_string(void)
{
    sk_rt_0008e518();
    sk_rt_00353aa0();
    sk_rt_000a6f88();
    uint64_t b = sk_rt_003519d4();
    uint64_t buf = sk_rt_0036a940(b, 0x80, 7);
    uint64_t g = sk_rt_004c2450();
    *(uint64_t *)(buf + 0x18) = 0x4c2458; /* DAT_004c2458 */
    *(uint64_t *)(buf + 0x10) = g;
    *(uint64_t *)(buf + 0x20) = 0x756f427265776f6cull; /* "lowerBou" */
    *(uint64_t *)(buf + 0x28) = 0xea0000000000646eull; /* "nd..." */
    sk_rt_00319a4c(buf + 0x30);
    sk_rt_0034d140();
    sk_rt_00310e20;
    *(uint64_t *)(buf + 0x50) = 0x756f427265707075ull; /* "upperBou" */
    *(uint64_t *)(buf + 0x58) = 0xea0000000000646eull;
    sk_rt_00319a4c(buf + 0x60);
    sk_rt_000e15d8();
    sk_rt_0034d5ec();
    sk_rt_001e4348();
    sk_rt_00358804();
    sk_rt_0008e500();
}

/* FUN_0026f488 @ 0x0026f488   (est. sk_range_check_lower_upper2)
 * Ghidra: void FUN_0026f488(long param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, long param_5)
 * Second lowerBound<upperBound validation path: copies the range endpoints,
 * dispatches the closure compare, and on failure raises the fatal trap.
 * Confidence: medium
 * Notes: strings s_Fatal_error_005accd0 / s_Range_requires_lowerBound_<__upp_005cda00;
 *   fatal FUN_001afe4c. */
void sk_range_check_lower_upper2(uint64_t out, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t rng)
{
    uint64_t base = *(uint64_t *)(rng + 0x10);
    uint64_t r = sk_rt_003722e4(0, base, base, 0x5e1f90, 0);
    uint64_t rr = *(uint64_t *)(r - 8);
    sk_rt_0036a908(*(uint64_t *)(rr + 0x40), 0);
    uint64_t lo = sk_rt_000277b8(a4);
    sk_rt_00310e20(*(uint64_t *)(rng + 0x18));
    uint64_t ok = sk_rt_00310e20();
    if ((ok & 1) != 0) {
        /* copy both endpoints, then release */
        sk_rt_00310e08(0, base);
        return;
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11);
}

/* FUN_0026fad0 @ 0x0026fad0   (est. sk_range_check_lower_upper3)
 * Ghidra: void FUN_0026fad0(long param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, long param_5)
 * Third lowerBound<upperBound validation variant (two endpoint copies then
 * compare). On failure raises the fatal trap.
 * Confidence: medium
 * Notes: strings + fatal as FUN_0026f488. */
void sk_range_check_lower_upper3(uint64_t out, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t rng)
{
    uint64_t base = *(uint64_t *)(rng + 0x10);
    uint64_t r = sk_rt_003722e4(0, base, base, 0x5e1f90, 0);
    uint64_t rr = *(uint64_t *)(r - 8);
    sk_rt_0036a908(*(uint64_t *)(rr + 0x40), 0);
    uint64_t lo = sk_rt_000277b8(a4);
    uint64_t r2 = sk_rt_00319658(a4);
    uint64_t ok = sk_rt_00310e20(*(uint64_t *)(rng + 0x18));
    if ((ok & 1) != 0) {
        sk_rt_00310e08(0, base);
        return;
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11);
}

/* FUN_0027035c @ 0x0027035c   (est. sk_range_check_lower_upper4)
 * Ghidra: void FUN_0027035c(long param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4, long param_5)
 * Fourth lowerBound<upperBound validation variant. On failure raises trap.
 * Confidence: medium
 * Notes: strings + fatal as above. */
void sk_range_check_lower_upper4(uint64_t out, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t rng)
{
    uint64_t base = *(uint64_t *)(rng + 0x10);
    uint64_t r = sk_rt_003722e4(0, base, base, 0x5e1f90, 0);
    uint64_t rr = *(uint64_t *)(r - 8);
    sk_rt_0036a908(*(uint64_t *)(rr + 0x40), 0);
    sk_rt_00310e20(*(uint64_t *)(rng + 0x18));
    sk_rt_00310924(a4);
    uint64_t ok = sk_rt_00310e20();
    if ((ok & 1) != 0) {
        sk_rt_00310e08(0, base);
        return;
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11);
}

/* ===================================================================== */
/* Range dispatch / thunk engine                                         */
/* ===================================================================== */

/* FUN_00270ab4 @ 0x00270ab4   (est. sk_range_dispatch)
 * Ghidra: void FUN_00270ab4(undefined8 param_1, long param_2, ulong param_3, code *param_4)
 * Generic Range method dispatch: calls the closure param_4 with the resolved
 * collection base/endpoints and the metadata word. Used as the forwarding
 * target for the many range thunks.
 * Confidence: medium
 * Notes: reads +0x10/+0x18 of the collection and the metadata at (flags&~1)-8. */
void sk_range_dispatch(uint64_t a, uint64_t coll, uint64_t flags, void *fn)
{
    sk_rt_00310ca4(a, *(uint64_t *)(coll + 0x10), *(uint64_t *)(coll + 0x18),
                   *(uint64_t *)((flags & 0xfffffffffffffffe) - 8));
}

/* FUN_0026f240 @ 0x0026f240   (est. sk_range_dispatch_checked)
 * Ghidra: void FUN_0026f240(void)
 * Bounds-checked range dispatch: after the standard object-lock setup, runs a
 * collection-view vtable op at +0x20/+8; if the collection is empty it falls
 * through to the fatal trap.
 * Confidence: low
 * Notes: FUN_00347d60 + noreturn FUN_001afe4c on the empty path. */
void sk_range_dispatch_checked(void)
{
    sk_rt_0008e518();
    sk_rt_00353a24();
    sk_rt_00359f08();
    cl4_result_t md = sk_rt_0034b0b4();
    sk_rt_00353534();
    sk_rt_003722e4();
    sk_rt_00348d64();
    sk_rt_0036a908();
    sk_rt_0034b3d8();
    sk_rt_003494e8();
    sk_rt_0034c074();
    sk_rt_0034f1e0();
    sk_rt_003567bc();
    uint64_t v = sk_rt_00351aa4();
    uint64_t end = *(uint64_t *)(sk_rt_00310e20() + 0x18);
    uint64_t ok = sk_rt_00350ac4();
    if ((ok & 1) != 0) {
        /* vtable +0x20 body op, then +8 release */
        sk_rt_003504a0();
        sk_rt_00359e34();
        sk_rt_00351554();
        sk_rt_00351d0c();
        sk_rt_00350ad0();
        sk_rt_00351298();
        sk_rt_003504e8();
        sk_rt_00310e08();
        uint64_t t = sk_rt_00353ac8();
        sk_rt_003509d4();
        sk_rt_0008e500();
        return;
    }
    sk_rt_00347d60();
    sk_rt_001afe4c();
}

/* FUN_0026f844 @ 0x0026f844   (est. sk_range_dispatch_checked2)
 * Ghidra: void FUN_0026f844(void)
 * Bounds-checked range dispatch variant (mirrors FUN_0026f240).
 * Confidence: low
 * Notes: FUN_00347d60 + noreturn on empty path. */
void sk_range_dispatch_checked2(void)
{
    sk_rt_0008e518();
    sk_rt_00359f8c();
    sk_rt_00359f08();
    cl4_result_t md = sk_rt_0034b0b4();
    sk_rt_00353534();
    sk_rt_003722e4();
    sk_rt_00348e60();
    sk_rt_0036a908();
    sk_rt_0034b758();
    sk_rt_003494e8();
    sk_rt_0034b8bc();
    sk_rt_000277b8();
    sk_rt_00350c50();
    sk_rt_003514d0();
    sk_rt_00319658();
    sk_rt_00350b30();
    uint64_t end = *(uint64_t *)(sk_rt_00310e20() + 0x18);
    uint64_t ok = sk_rt_0034beec();
    if ((ok & 1) != 0) {
        sk_rt_00350470();
        sk_rt_003508c0();
        sk_rt_0034ee58();
        sk_rt_003515e4();
        sk_rt_00351554();
        sk_rt_003504e8();
        sk_rt_00310e08();
        uint64_t t = sk_rt_00353ac8();
        sk_rt_003508cc();
        sk_rt_0008e500();
        return;
    }
    sk_rt_00347d60();
    sk_rt_001afe4c();
}

/* FUN_002700f8 @ 0x002700f8   (est. sk_range_dispatch_checked3)
 * Ghidra: void FUN_002700f8(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Bounds-checked range dispatch variant.
 * Confidence: low
 * Notes: FUN_00347d60 + noreturn on empty path. */
void sk_range_dispatch_checked3(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    sk_rt_0008e518();
    sk_rt_00359f08();
    cl4_result_t md = sk_rt_0034b0b4();
    sk_rt_00353534();
    sk_rt_003722e4();
    sk_rt_00348d64();
    sk_rt_0036a908();
    sk_rt_0034b3d8();
    sk_rt_003494e8();
    sk_rt_0034b4c0();
    sk_rt_00352474();
    sk_rt_00350624();
    sk_rt_00310924(d);
    sk_rt_00351250();
    uint64_t end = *(uint64_t *)(sk_rt_00310e20() + 0x18);
    sk_rt_0034e054();
    sk_rt_0034beec();
    uint64_t ok = sk_rt_0034beec();
    if ((ok & 1) != 0) {
        sk_rt_003510dc();
        sk_rt_00359e34();
        sk_rt_0035056c();
        sk_rt_00351e84();
        sk_rt_0034cfc4();
        sk_rt_00351554();
        sk_rt_003504e8();
        sk_rt_00310e08();
        uint64_t t = sk_rt_00353ac8();
        sk_rt_003508cc();
        sk_rt_0008e500();
        return;
    }
    sk_rt_00347d60();
    sk_rt_001afe4c();
}

/* ===================================================================== */
/* Collection string ops (2xxxx)                                         */
/* ===================================================================== */

/* FUN_0027169c @ 0x0027169c   (est. sk_string_optional_init)
 * Ghidra: undefined1 [16] FUN_0027169c(undefined8 param_1, long param_2)
 * Initializes an Optional String from a raw buffer+count: nil when count==0,
 * otherwise allocates, copies, and returns the String value; traps if a nil
 * is unexpectedly encountered mid-unwrap.
 * Confidence: medium
 * Notes: strings s_Unexpectedly_found_nil_while_unw_005cd7d0,
 *   s_Swift_String_swift_005ce680; FUN_00209f18 alloc, FUN_0036b118 free. */
cl4_result_t sk_string_optional_init(uint64_t buf, int64_t count)
{
    if (count == 0) {
        return (cl4_result_t){ .lo = 0, .hi = 0xe000000000000000ull };
    }
    sk_rt_00271b70();
    uint64_t p = sk_rt_00209f18();
    cl4_result_t r = sk_rt_002a2f60(p, 1);
    if (r.hi == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cd7d0, 0x39, 2, 0x5ce680, 0x12, 2, 0x1c2, 1);
    }
    sk_rt_0036b118(p);
    uint64_t lo = sk_rt_001e3f70(0, 0xe000000000000000ull, r.lo, r.hi);
    return (cl4_result_t){ .lo = lo, .hi = r.hi };
}

/* FUN_00271778 @ 0x00271778   (est. sk_repeat_collection_init)
 * Ghidra: undefined1 [16] FUN_00271778(undefined8 param_1, long param_2)
 * Initializes a Repeat<Element> collection: repeats the scalar param_1
 * param_2 times into an index buffer, trapping on a non-positive repetition
 * count or an out-of-range index.
 * Confidence: medium
 * Notes: strings s_Index_out_of_range_005cd940 / s_Swift_Repeat_swift_005d0350;
 *   FUN_002ab5bc/FUN_002a95b4 buffer append. */
cl4_result_t sk_repeat_collection_init(uint64_t scalar, int64_t count)
{
    cl4_result_t idx = { .lo = 7, .hi = 0xf };
    if (count != 0) {
        uint64_t n = sk_rt_00271b70(scalar, count);
        if (n != 0) {
            uint64_t it = n & (0xffffffffffffffffull ^ ((int64_t)n >> 0x3f));
            do {
                if (it == 0) {
                    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cd940, 0x12, 2, 0x5d0350, 0x12);
                }
                sk_rt_002ab5bc(idx.lo, idx.lo, idx.hi, idx.lo, 0, 0xe000000000000000ull);
                cl4_result_t r = sk_rt_002a95b4();
                sk_rt_002ab5bc(r.lo, r.hi, &idx.hi, &idx.lo, 0x3478c4);
                it = it - 1;
                n = n - 1;
            } while (n != 0);
        }
    }
    return idx;
}

/* FUN_0027195c @ 0x0027195c   (est. sk_utf8buffer_repeat_count)
 * Ghidra: uint FUN_0027195c(int param_1, long param_2)
 * Builds the packed UTF-8 buffer repeat-count bitmap: folds (param_1+1)&0xff
 * into a byte map param_2 times, trapping on a negative count or overflow.
 * Confidence: medium
 * Notes: strings s_Repetition_count_should_be_non_n_005d0320,
 *   s_Swift_Repeat_swift_005d0350, &DAT_005be7c0 / s_Swift_ValidUTF8Buffer_swift_005d08c0. */
uint32_t sk_utf8buffer_repeat_count(int32_t ch, int64_t count)
{
    uint32_t map = 0;
    if (count == 0) {
        return 0;
    }
    if (count < 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d0320, 0x27, 2, 0x5d0350, 0x12, 2, 0x28, 1);
    }
    do {
        if ((map & 0xff000000) != 0) {
            sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d08c0, 0x1b, 2, 0xa7, 1);
        }
        map = ((ch + 1) & 0xff) << (-((uint32_t)__builtin_clzll(map) & 0x18) & 0x18) | map;
        count = count - 1;
    } while (count != 0);
    return map;
}

/* FUN_00271b70 @ 0x00271b70   (est. sk_repeat_count_checked)
 * Ghidra: undefined1 [16] FUN_00271b70(undefined8 param_1, long param_2)
 * Validates a non-negative repetition count, returning {count,value}; traps
 * on a negative count.
 * Confidence: high
 * Notes: string s_Repetition_count_should_be_non_n_005d0320; noreturn trap. */
cl4_result_t sk_repeat_count_checked(uint64_t value, int64_t count)
{
    if (count >= 0) {
        return (cl4_result_t){ .lo = count, .hi = value };
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d0320, 0x27, 2, 0x5d0350, 0x12, 2, 0x28, 1);
    return (cl4_result_t){ 0, 0 }; /* unreachable */
}

/* FUN_00271bdc @ 0x00271bdc   (est. sk_repeat_count_checked2)
 * Ghidra: undefined1 [16] FUN_00271bdc(undefined8 param_1, undefined8 param_2, long param_3)
 * Validates a non-negative repetition count (mirror of FUN_00271b70).
 * Confidence: high
 * Notes: string s_Repetition_count_should_be_non_n_005d0320. */
cl4_result_t sk_repeat_count_checked2(uint64_t value, uint64_t a2, int64_t count)
{
    if (count >= 0) {
        return (cl4_result_t){ .lo = count, .hi = value };
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d0320, 0x27, 2, 0x5d0350, 0x12, 2, 0x28, 1);
    return (cl4_result_t){ 0, 0 };
}

/* FUN_00271c4c @ 0x00271c4c   (est. sk_repeat_init_dispatch)
 * Ghidra: void FUN_00271c4c(undefined8 param_1, long param_2)
 * Repeat-collection init dispatch: on a valid non-negative count, stores the
 * count and dispatches through the collection vtable (+0x20); on a negative
 * count reports the failure and traps.
 * Confidence: medium
 * Notes: jumptable at 0x00271cb8 (indirect dispatch); trap FUN_001afe4c. */
void sk_repeat_init_dispatch(uint64_t value, int64_t count)
{
    if (count >= 0) {
        sk_rt_003530e8();
        sk_rt_00350a64();
        uint64_t t = sk_rt_0031d660();
        sk_rt_00354d2c(*(int32_t *)(t + 0x1c));
        sk_rt_00310e20; /* jumptable dispatch */
        return;
    }
    sk_rt_003488bc(1);
    sk_rt_003499dc();
    sk_rt_001afe4c();
}

/* FUN_00270074 @ 0x00270074   (est. sk_collection_check)
 * Ghidra: void FUN_00270074(void)
 * Collection validity/state check: initializes a temp view, resolves the
 * collection base, and calls the +0x24-sized dispatch; used as the target of
 * several range thunks.
 * Confidence: low
 * Notes: FUN_0031a14c base; FUN_003562bc dispatch. */
void sk_collection_check(void)
{
    sk_rt_003564e8();
    sk_rt_00355e74();
    sk_rt_00351a14();
    sk_rt_0034ad20();
    sk_rt_000a68c4();
    sk_rt_0034bd58();
    sk_rt_0034ec98();
    sk_rt_000836a4();
    sk_rt_0035159c();
    uint64_t t = sk_rt_0031a14c();
    sk_rt_003562bc(t, t);
    sk_rt_00352e6c();
    sk_rt_00354624();
    sk_rt_00356454();
}

/* FUN_002706dc @ 0x002706dc   (est. sk_collection_to_string)
 * Ghidra: void FUN_002706dc(void)
 * Renders a collection to its string form: opens a string buffer view,
 * appends the collection's elements (base at +0x18, count at +0x20), then
 * calls the finalizer FUN_00270744.
 * Confidence: medium
 * Notes: FUN_000839d8 metadata; FUN_00270744 finalize. */
void sk_collection_to_string(void)
{
    sk_rt_00351cc4();
    sk_rt_0034b804();
    sk_rt_0034e094();
    cl4_result_t md = sk_rt_000839d8();
    sk_rt_00350af4(md.lo, md.hi);
    sk_rt_00270744();
}

/* FUN_00270744 @ 0x00270744   (est. sk_collection_to_string_finalize)
 * Ghidra: void FUN_00270744(undefined8 param_1, long param_2, undefined8 param_3)
 * Finalizes a collection->String render: locks the collection object, copies
 * the element view through the metadata and appends it to the output string,
 * releasing locks on exit.
 * Confidence: medium
 * Notes: FUN_00377824/FUN_00377bec lock pair; FUN_0008f728 copy helper. */
void sk_collection_to_string_finalize(uint64_t out, uint64_t coll, uint64_t meta)
{
    uint64_t obj = sk_rt_00377824(0, meta, coll, 0x612294, 0x6122b4);
    uint64_t o2 = *(uint64_t *)(obj - 8);
    sk_rt_0036a908(*(uint64_t *)(o2 + 0x40) + 0xf, 0);
    sk_rt_00377bec(meta, coll, obj, 0x612294, 0x6122ac);
    uint64_t cpu = sk_rt_0008f6f4();
    uint64_t obj2 = sk_rt_00377824(0, cpu, obj, 0x60e3fc, 0x60e40c);
    sk_rt_0036a908(*(uint64_t *)(*(uint64_t *)(obj2 - 8) + 0x40) + 0xf, 0);
    uint64_t base = *(uint64_t *)(coll - 8);
    sk_rt_00310e20(base + 0x10);
    sk_rt_00377bec(cpu, obj, obj2, 0x60e3fc, 0x60e404);
    sk_rt_00310ca4(0x4e4980, 0x200, obj2);
    sk_rt_00310ca4(out, base, coll, meta);
    sk_rt_00310e20(meta);
}

/* FUN_00270b1c @ 0x00270b1c   (est. sk_string_append_check)
 * Ghidra: void FUN_00270b1c(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Append-with-check: after object setup, if the collection still has room
 * (result bit set) appends and returns; else reports the failure and traps.
 * Confidence: low
 * Notes: FUN_0034b348 + noreturn FUN_001afe4c on the full path. */
void sk_string_append_check(uint64_t a, uint64_t b, uint64_t c)
{
    sk_rt_00084220();
    sk_rt_003561a0();
    sk_rt_00349b3c();
    sk_rt_0036a908();
    sk_rt_00348f50();
    sk_rt_00351ad4(c);
    sk_rt_0034f1c4();
    sk_rt_00351744();
    uint64_t ok = sk_rt_00351744();
    if ((ok & 1) != 0) {
        sk_rt_0034d384();
        sk_rt_00351744();
        sk_rt_00350494();
        sk_rt_00084234();
        return;
    }
    sk_rt_0034b348();
    sk_rt_0034951c();
    sk_rt_00349410();
    sk_rt_003504b8();
    sk_rt_001afe4c();
}

/* FUN_00270c08 @ 0x00270c08   (est. sk_string_insert_check)
 * Ghidra: void FUN_00270c08(void)
 * Insert-with-capacity-check: reserves space, inserts the scalar, and
 * returns; on insufficient capacity reports and traps.
 * Confidence: low
 * Notes: FUN_0034b348 + noreturn FUN_001afe4c on the failure path. */
void sk_string_insert_check(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_0035199c();
    sk_rt_0034de64();
    sk_rt_003516cc();
    sk_rt_00377824();
    sk_rt_00348d4c();
    sk_rt_0007c1a4();
    sk_rt_0034aee4();
    sk_rt_00350220();
    uint64_t k = sk_rt_00377bec();
    sk_rt_0034c454();
    sk_rt_00319308();
    sk_rt_00348cd0();
    sk_rt_0007c1a4();
    sk_rt_0034b2f8();
    sk_rt_003506e8();
    sk_rt_0035a3f4();
    sk_rt_00100efc();
    sk_rt_00349fe0(k);
    sk_rt_0034cfd4();
    uint64_t ok = sk_rt_0034cfd4();
    if ((ok & 1) != 0) {
        sk_rt_00351118();
        sk_rt_003489a8();
        sk_rt_003504c4();
        sk_rt_00352438();
        sk_rt_001d9890();
        sk_rt_003518b8();
        sk_rt_0008e500(cpu);
        return;
    }
    sk_rt_00350410();
    sk_rt_003488bc();
    sk_rt_003593e8();
    sk_rt_00349410();
    sk_rt_003504b8();
    sk_rt_001afe4c();
}

/* FUN_00270d80 @ 0x00270d80   (est. sk_string_remove_op)
 * Ghidra: void FUN_00270d80(void)
 * String remove-at-index operation: locks the string object, removes the
 * element at the resolved index through the view vtable, and releases.
 * Confidence: low
 * Notes: FUN_00377824/FUN_00377bec lock pair; FUN_000dbd0c index metadata. */
void sk_string_remove_op(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_003518c4();
    sk_rt_00357bc4();
    sk_rt_003514b8();
    sk_rt_0034a944();
    sk_rt_00350600();
    uint64_t k = sk_rt_00377824();
    sk_rt_00355314();
    cl4_result_t idx = sk_rt_000dbd0c();
    sk_rt_00377bec(idx.lo, idx.hi, k);
    sk_rt_0034dee4();
    sk_rt_00310e08();
    sk_rt_00348e60();
    sk_rt_0007c1a4();
    sk_rt_0034af20();
    sk_rt_0031b164();
    sk_rt_00351184();
    sk_rt_003507e0();
    sk_rt_00351c58();
    sk_rt_00319628();
    sk_rt_00351250();
    sk_rt_003513a8();
    sk_rt_00350ab8();
    sk_rt_0008e500();
}

/* FUN_00270e80 @ 0x00270e80   (est. sk_string_remove_op2)
 * Ghidra: void FUN_00270e80(void)
 * String remove-at-index variant (mirrors FUN_00270d80).
 * Confidence: low
 * Notes: FUN_00377824/FUN_00377bec lock pair; FUN_00350618 index metadata. */
void sk_string_remove_op2(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_0035694c();
    sk_rt_00351ad4();
    sk_rt_0034a944();
    sk_rt_00351420();
    uint64_t k = sk_rt_00377824();
    sk_rt_00355314();
    cl4_result_t idx = sk_rt_00350618();
    sk_rt_00377bec(idx.lo, idx.hi, k);
    sk_rt_0034c55c();
    sk_rt_00310e08();
    sk_rt_00351f10();
    sk_rt_0007c1a4();
    sk_rt_0034b0d4();
    sk_rt_0031b164();
    sk_rt_0034f514();
    sk_rt_003527e0();
    sk_rt_0034d140();
    sk_rt_0031d630();
    uint64_t v = sk_rt_003505d0();
    sk_rt_003515fc(v, k);
    sk_rt_0008e500();
}

/* ===================================================================== */
/* Collection buffer & index machinery                                   */
/* ===================================================================== */

/* FUN_00270f80 @ 0x00270f80   (est. sk_collection_obj_alloc)
 * Ghidra: void FUN_00270f80(void)
 * Allocates and initializes a collection descriptor object: allocates a
 * 0x50-byte block (tag 0xc48f) with an internal buffer, records the element
 * bounds and metadata, then registers it and starts the first element via
 * FUN_00270d80.
 * Confidence: medium
 * Notes: alloc FUN_0036a908(0x50, 0xc48f); multiple nested allocations. */
void sk_collection_obj_alloc(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    uint64_t *slot = (uint64_t *)sk_rt_0034d2b4();
    uint64_t *obj = (uint64_t *)sk_rt_0036a908(0x50, 0xc48f);
    *slot = (uint64_t)obj;
    sk_rt_00350bd8();
    sk_rt_0034c20c();
    uint64_t k = sk_rt_00377824();
    obj[5] = k;
    sk_rt_00352018();
    uint64_t size = sk_rt_0034a654();
    obj[7] = sk_rt_0036a908(size, 0xc48f);
    obj[8] = sk_rt_0036a908(size, 0xc48f);
    sk_rt_0034998c();
    obj[9] = sk_rt_0036a908(size, 0xc48f);
    sk_rt_00350ad0();
    sk_rt_0034e55c(obj[8]);
    sk_rt_003543c4();
    sk_rt_00270d80();
    sk_rt_0008e500(sk_rt_002710ac(), obj[8]);
}

/* FUN_002710ac @ 0x002710ac   (est. sk_collection_obj_release)
 * Ghidra: void FUN_002710ac(void)
 * Releases a collection descriptor object and its buffers: reads the
 * registered object, tears down its views, releases the nested allocations,
 * and unregisters it.
 * Confidence: medium
 * Notes: FUN_00077698/FUN_0007767c object registry; thunk_FUN_00012568 release. */
void sk_collection_obj_release(void)
{
    cl4_result_t reg = sk_rt_00077698();
    uint64_t *obj = (uint64_t *)(reg.lo);
    uint64_t b1 = obj[8];
    uint64_t b3 = obj[9];
    uint64_t b0 = obj[7];
    if ((reg.hi & 1) == 0) {
        sk_rt_000e15d8(reg.lo, reg.hi, obj[0], obj[1], obj[2], obj[3]);
        sk_rt_00270e80();
    } else {
        uint64_t k = obj[5];
        uint64_t l = obj[6];
        cl4_result_t r = sk_rt_0034e4a4(l);
        sk_rt_0008e388(r.lo, r.hi, k);
        sk_rt_00351dcc();
        sk_rt_00270e80();
        sk_rt_00351160(*(uint64_t *)(l + 8));
    }
    sk_rt_00012568(b3);
    sk_rt_00012568(b1);
    sk_rt_00012568(b0);
    sk_rt_0007767c(obj);
    sk_rt_00012568();
}

/* FUN_00271178 @ 0x00271178   (est. sk_collection_remove_check)
 * Ghidra: void FUN_00271178(void)
 * Remove-with-check: validates the collection is non-empty, removes the
 * element at the resolved index, and returns; empty -> report + trap.
 * Confidence: low
 * Notes: FUN_0034b348 + noreturn on the empty path. */
void sk_collection_remove_check(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_00352ee4();
    sk_rt_0034c54c();
    sk_rt_0035113c();
    sk_rt_003515fc();
    sk_rt_00377824();
    sk_rt_00348d4c();
    sk_rt_0007c1a4();
    sk_rt_0034aee4();
    sk_rt_00350b00();
    sk_rt_00351220();
    uint64_t k = sk_rt_00377bec();
    sk_rt_0034e0c4();
    sk_rt_00319308();
    sk_rt_00348cd0();
    sk_rt_0007c1a4();
    sk_rt_0034bdfc();
    sk_rt_000277b8();
    sk_rt_00350b24();
    sk_rt_00350bf0();
    sk_rt_0034a30c(k);
    sk_rt_00350f3c();
    uint64_t ok = sk_rt_00350f3c();
    if ((ok & 1) != 0) {
        sk_rt_003508fc();
        sk_rt_003489a8();
        sk_rt_003504ac();
        sk_rt_00270d80();
        sk_rt_003510ac();
        sk_rt_0008e500(cpu);
        return;
    }
    sk_rt_00350410();
    sk_rt_003488bc();
    sk_rt_003593e8();
    sk_rt_00349410();
    sk_rt_003504b8();
    sk_rt_001afe4c();
}

/* FUN_00271304 @ 0x00271304   (est. sk_collection_remove_check2)
 * Ghidra: void FUN_00271304(void)
 * Remove-with-check variant (mirrors FUN_00271178).
 * Confidence: low
 * Notes: FUN_0034b348 + noreturn on the empty path. */
void sk_collection_remove_check2(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_00351ef8();
    sk_rt_0034de64();
    sk_rt_0034d8d4();
    sk_rt_00377824();
    sk_rt_00348d4c();
    sk_rt_0007c1a4();
    sk_rt_0034aee4();
    sk_rt_0034fde0();
    uint64_t k = sk_rt_00377bec();
    sk_rt_0034c454();
    sk_rt_00319308();
    sk_rt_0034a37c();
    sk_rt_0007c1a4();
    sk_rt_0034b2f8();
    sk_rt_000277b8();
    sk_rt_00350b24();
    sk_rt_00350c80();
    sk_rt_00349fe0(k);
    sk_rt_0034cfd4();
    uint64_t ok = sk_rt_0034cfd4();
    if ((ok & 1) != 0) {
        sk_rt_00351118();
        sk_rt_000bd3a4();
        sk_rt_00270e80();
        sk_rt_0008e500();
        return;
    }
    sk_rt_00350410();
    sk_rt_003488bc();
    sk_rt_003593e8();
    sk_rt_00349410();
    sk_rt_003504b8();
    sk_rt_001afe4c();
}

/* FUN_00271554 @ 0x00271554   (est. sk_collection_remove_wrap)
 * Ghidra: void FUN_00271554(void)
 * Wrapper around the remove check: reads the descriptor object, dispatches
 * either the empty or populated remove path, and releases the object.
 * Confidence: low
 * Notes: FUN_00084220/FUN_00084234 registry; thunk_FUN_00012568 release. */
void sk_collection_remove_wrap(void)
{
    cl4_result_t reg = sk_rt_00084220();
    uint64_t *obj = (uint64_t *)(reg.lo);
    uint64_t b2 = *(uint64_t *)(obj + 0x38 / 8);
    uint64_t b1 = *(uint64_t *)(obj + 0x40 / 8);
    if ((reg.hi & 1) == 0) {
        sk_rt_00271304(b1);
    } else {
        uint64_t l = *(uint64_t *)(obj + 0x30 / 8);
        sk_rt_00352474();
        sk_rt_0034d3d4();
        sk_rt_00356b80(b2);
        sk_rt_00271304();
        sk_rt_000e15d8(*(uint64_t *)(l + 8));
    }
    sk_rt_00012568(b1);
    sk_rt_00012568(b2);
    sk_rt_00084234(obj);
    sk_rt_00012568();
}

/* FUN_002715f8 @ 0x002715f8   (est. sk_collection_is_empty)
 * Ghidra: void FUN_002715f8(void)
 * Predicate testing whether a collection is empty: compares the start and
 * end bounds, and returns the boolean; an intermediate equality probe is
 * used for the mixed-bound case.
 * Confidence: medium
 * Notes: FUN_00310e20 predicate; FUN_001e3048 equality probe. */
void sk_collection_is_empty(void)
{
    sk_rt_00084220();
    sk_rt_00351a38();
    uint64_t start = sk_rt_00310e20();
    sk_rt_00350bb4();
    uint64_t a = sk_rt_00310e20();
    if ((a & 1) == 0) {
        uint64_t b = sk_rt_00310e20();
        if (((b & 1) == 0) && ((sk_rt_001e3048() & 1) == 0)) {
            sk_rt_00353abc();
            uint32_t r = sk_rt_001e3048() ^ 1;
            sk_rt_00084234(r & 1);
            return;
        }
    }
    sk_rt_00084234(0);
}

/* FUN_00271d58 @ 0x00271d58   (est. sk_string_prefix_op)
 * Ghidra: void FUN_00271d58(void)
 * String prefix operation: opens a prefix view, resolves the prefix-length
 * index, and renders the prefix scalar; used by collection prefix helpers.
 * Confidence: low
 * Notes: FUN_00084220/FUN_00084234 registry; FUN_0031e0d4 index. */
void sk_string_prefix_op(void)
{
    sk_rt_00084220();
    sk_rt_0034b668();
    sk_rt_0031e0d4();
    sk_rt_003503a0();
    sk_rt_0031d678();
    cl4_result_t v = sk_rt_0034d844();
    sk_rt_00356a2c(v.lo, v.hi);
    sk_rt_00084234();
}

/* FUN_00271dc8 @ 0x00271dc8   (est. sk_string_buffer_append)
 * Ghidra: void FUN_00271dc8(undefined8 param_1, undefined8 param_2)
 * Appends the scalar param_1 into the packed string buffer addressed by x20,
 * extending the buffer; releases the old value.
 * Confidence: medium
 * Notes: FUN_002ab5bc/FUN_002a95b4 buffer append; FUN_003a25d4 release. */
void sk_string_buffer_append(uint64_t scalar, uint64_t old)
{
    uint64_t *buf = 0; /* unaff_x20 */
    sk_rt_002ab5bc(buf[1], buf[1], buf[0], buf[1], buf[2], buf[3]);
    sk_rt_002a95b4();
    sk_rt_003a25d4(old);
}

/* FUN_00271e58 @ 0x00271e58   (est. sk_string_buffer_append2)
 * Ghidra: void FUN_00271e58(void)
 * Appends into the packed string buffer (mirror of FUN_00271dc8).
 * Confidence: medium
 * Notes: FUN_002ab5bc/FUN_002a95b4 buffer append. */
void sk_string_buffer_append2(void)
{
    uint64_t *buf = 0; /* unaff_x20 */
    sk_rt_002ab5bc(buf[1], buf[1], buf[0], buf[1], buf[2], buf[3]);
    sk_rt_002a95b4();
}

/* FUN_00272200 @ 0x00272200   (est. sk_string_buffer_append3)
 * Ghidra: void FUN_00272200(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Appends param_3 into the packed string buffer (mirror); releases param_2.
 * Confidence: medium
 * Notes: FUN_002ab5bc/FUN_002a95b4 buffer append; FUN_003a25d4 release. */
void sk_string_buffer_append3(uint64_t a, uint64_t old, uint64_t scalar)
{
    uint64_t *buf = 0; /* unaff_x20 */
    sk_rt_002ab5bc(scalar, scalar, buf[0], buf[1], buf[2], buf[3]);
    sk_rt_002a95b4();
    sk_rt_003a25d4(old);
}

/* FUN_00271edc @ 0x00271edc   (est. sk_string_remove_subrange)
 * Ghidra: void FUN_00271edc(void)
 * Removes a subrange from a string: locks the object, removes the range
 * through the view, and releases.
 * Confidence: low
 * Notes: FUN_00377824/FUN_00377bec lock pair. */
void sk_string_remove_subrange(void)
{
    sk_rt_00084220();
    sk_rt_0034a958();
    sk_rt_003514b8();
    sk_rt_00349748();
    sk_rt_00350600();
    sk_rt_00377824();
    sk_rt_00348d4c();
    sk_rt_0007c1a4();
    sk_rt_0034aee4();
    sk_rt_00310924();
    sk_rt_00350b24();
    sk_rt_0008e388();
    sk_rt_0031d6a8();
    sk_rt_000dbdf4();
    sk_rt_0035063c();
    sk_rt_0034c9f8();
    sk_rt_00084234();
}

/* FUN_00271fa0 @ 0x00271fa0   (est. sk_bitbuffer_append_16)
 * Ghidra: void FUN_00271fa0(uint param_1)
 * Appends a 16-bit value into a packed UInt buffer at the current bit offset
 * (stored at +4 of the buffer object), shifting the new bits into place and
 * advancing the offset; traps if the buffer would overflow 32 bits.
 * Confidence: medium
 * Notes: string s_Swift_UIntBuffer_swift_005d0610; DAT_005be7c0. */
void sk_bitbuffer_append_scalar(uint32_t val)
{
    uint32_t *buf = 0; /* unaff_x20 */
    uint8_t off = (uint8_t)buf[1];
    if (off < 0x20) {
        buf[0] = buf[0] & (((uint32_t)0xffffffffffffffffull << (off & 0x1f)) - 1) |
                 (val & 0xffff) << (off & 0x1f);
        *(uint8_t *)(buf + 1) = off + 0x10;
        return;
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d0610, 0x16, 2, 0xbe, 1);
}

/* FUN_00272464 @ 0x00272464   (est. sk_string_buffer_append4)
 * Ghidra: void FUN_00272464(undefined8 param_1, undefined8 param_2)
 * Appends param_2 into the packed string buffer (mirror).
 * Confidence: medium
 * Notes: FUN_002ab5bc/FUN_002a95b4 buffer append. */
void sk_string_buffer_append4(uint64_t a, uint64_t scalar)
{
    uint64_t *buf = 0; /* unaff_x20 */
    sk_rt_002ab5bc(scalar, scalar, buf[0], buf[1], buf[2], buf[3]);
    sk_rt_002a95b4();
}

/* FUN_002724e4 @ 0x002724e4   (est. sk_string_buffer_append_scalar)
 * Ghidra: void FUN_002724e4(undefined8 param_1, undefined8 param_2)
 * Appends the scalar param_2 through the typed append path (FUN_002ab8ac)
 * and stores it via FUN_002a7f58.
 * Confidence: medium
 * Notes: FUN_002ab8ac with flags 0x174/0x164; FUN_002a7f58 store. */
void sk_string_buffer_append_scalar(uint64_t a, uint64_t scalar)
{
    uint64_t *buf = 0; /* unaff_x20 */
    cl4_result_t r = sk_rt_002ab8ac(scalar, scalar, buf[0], buf[1], 0x174, 0x164);
    sk_rt_002a7f58(r.lo, r.hi, a);
}

/* FUN_00272294 @ 0x00272294   (est. sk_utf8buffer_append)
 * Ghidra: void FUN_00272294(int param_1, undefined8 param_2)
 * Appends a UTF-8 scalar param_1 into the packed ValidUTF8Buffer: validates
 * via the two-pass range check (FUN_002c8c2c / FUN_001d96e0 / FUN_001d974c),
 * folds the low 8 bits into the byte map, and writes it back. Traps on
 * invalid UTF-8 (0xc1/0xc2/0xa7) or out-of-bounds index (0x2ca).
 * Confidence: medium
 * Notes: strings s_Swift_ValidUTF8Buffer_swift_005d08c0,
 *   s_Index_out_of_bounds_005cdab0, s_Swift_Collection_swift_005cdad0. */
void sk_utf8buffer_append(int32_t ch, uint64_t a2)
{
    uint32_t *buf = 0; /* unaff_x20 */
    uint32_t u = *buf;
    uint64_t r = sk_rt_002c8c2c(a2, u);
    if ((r & 1) == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d08c0, 0x1b, 2, 0xc1, 1);
    }
    uint64_t r2 = sk_rt_001d96e0(a2, u);
    uint32_t lo = (uint32_t)r2;
    uint32_t hi = (uint32_t)(r2 >> 0x20);
    uint32_t map = 0;
    uint32_t v;
    if (lo != hi) {
        do {
            v = (uint32_t)r2;
            if (lo < v || v <= hi) goto oob;
            if ((map & 0xff000000) != 0) goto full;
            r2 = (uint64_t)(v >> 8);
            map = (v & 0xff) << (-((uint32_t)__builtin_clzll(map) & 0x18) & 0x18) | map;
        } while (v >> 8 != hi);
        if ((map & 0xff000000) != 0) goto full;
    }
    map = ((ch + 1) & 0xff) << (-((uint32_t)__builtin_clzll(map) & 0x18) & 0x18) | map;
    r2 = sk_rt_001d974c(a2, u);
    lo = (uint32_t)r2;
    hi = (uint32_t)(r2 >> 0x20);
    uint32_t cur = lo;
    do {
        if (cur == hi) {
            *buf = map;
            return;
        }
        v = (uint32_t)r2;
        if (lo < v || v <= hi) goto oob;
        if ((map & 0xff000000) != 0) goto full;
        cur = v >> 8;
        r2 = (uint64_t)cur;
        map = (v & 0xff) << (-((uint32_t)__builtin_clzll(map) & 0x18) & 0x18) | map;
    } while (true);
full:
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d08c0, 0x1b, 2, 0xa7, 1);
oob:
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cdab0, 0x13, 2, 0x5cdad0, 0x16, 2, 0x2ca, 1);
}

/* FUN_002739c0 @ 0x002739c0   (est. sk_utf8buffer_append_repeat)
 * Ghidra: void FUN_002739c0(ulong param_1)
 * Append-by-repeat: if the flag bit 0 is set, folds the buffer's low byte
 * into the map (validating index/UTF-8); otherwise the map is left at 0.
 * Confidence: medium
 * Notes: mirrors FUN_00272294's fold; strings ValidUTF8Buffer/Collection. */
void sk_utf8buffer_append_repeat(uint64_t flag)
{
    uint32_t *buf = 0; /* unaff_x20 */
    uint32_t map = 0;
    if ((flag & 1) != 0) {
        uint32_t u = *buf;
        uint64_t r = sk_rt_002c8c2c(u, u);
        if ((r & 1) == 0) {
            sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d08c0, 0x1b, 2, 0xc1, 1);
        }
        uint64_t r2 = sk_rt_001d96e0(u, u);
        uint32_t lo = (uint32_t)r2;
        uint32_t hi = (uint32_t)(r2 >> 0x20);
        uint32_t v;
        if (lo != hi) {
            do {
                v = (uint32_t)r2;
                if (lo < v || v <= hi) goto oob;
                if ((map & 0xff000000) != 0) goto full;
                r2 = (uint64_t)(v >> 8);
                map = (v & 0xff) << (-((uint32_t)__builtin_clzll(map) & 0x18) & 0x18) | map;
            } while (v >> 8 != hi);
        }
        r2 = sk_rt_001d974c(0, u);
        lo = (uint32_t)r2;
        hi = (uint32_t)(r2 >> 0x20);
        uint32_t cur = lo;
        while (cur != hi) {
            uint32_t v = (uint32_t)r2;
            if (lo < v || v <= hi) goto oob;
            if ((map & 0xff000000) != 0) goto full;
            cur = v >> 8;
            r2 = (uint64_t)cur;
            map = (v & 0xff) << (-((uint32_t)__builtin_clzll(map) & 0x18) & 0x18) | map;
        }
    }
    *buf = map;
    return;
full:
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d08c0, 0x1b, 2, 0xa7, 1);
oob:
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cdab0, 0x13, 2, 0x5cdad0, 0x16, 2, 0x2ca, 1);
}

/* ===================================================================== */
/* removeFirst / removeLast / scalar decode                              */
/* ===================================================================== */

/* FUN_00272820 @ 0x00272820   (est. sk_collection_remove_first)
 * Ghidra: int FUN_00272820(undefined8 param_1)
 * removeFirst on a ValidUTF8Buffer-backed collection: refuses an empty
 * collection (0x222), validates the index bounds, folds the first byte into
 * the map, and returns index-1. Traps on empty (0x222), invalid range (0x2f9),
 * invalid UTF-8 (0xc1/0xc2/0xa7), or out-of-bounds (0x2ca).
 * Confidence: medium
 * Notes: strings s_Can_t_remove_from_an_empty_colle_005d0370,
 *   s_Swift_RangeReplaceableCollection_005cdd20, s_Range_requires_lowerBound_... */
int32_t sk_collection_remove_first(uint64_t idx)
{
    uint32_t *buf = 0; /* unaff_x20 */
    uint32_t u = *buf;
    if (u == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d0370, 0x25, 2, 0x5cdd20, 0x26, 2, 0x222, 1);
    }
    uint64_t lb = sk_rt_002c88f8();
    if ((uint32_t)idx < (uint32_t)lb) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11, 2, 0x2f9, 1);
    }
    uint64_t r = sk_rt_002c8c2c(idx, u);
    uint64_t code = 0xc1;
    if ((r & 1) != 0) {
        uint64_t r2 = sk_rt_002c8c2c(lb, u);
        if ((r2 & 1) != 0) {
            uint64_t r3 = sk_rt_001d96e0(idx, u);
            uint32_t lo = (uint32_t)r3;
            uint32_t hi = (uint32_t)(r3 >> 0x20);
            uint32_t map = 0;
            uint32_t v;
            if (lo != hi) {
                do {
                    v = (uint32_t)r3;
                    if (lo < v || v <= hi) goto oob;
                    if ((map & 0xff000000) != 0) goto full;
                    r3 = (uint64_t)(v >> 8);
                    map = (v & 0xff) << (-((uint32_t)__builtin_clzll(map) & 0x18) & 0x18) | map;
                } while (v >> 8 != hi);
            }
            uint64_t r4 = sk_rt_001d974c(lb, u);
            lo = (uint32_t)r4;
            hi = (uint32_t)(r4 >> 0x20);
            uint32_t cur = lo;
            do {
                if (cur == hi) {
                    *buf = map;
                    return (uint32_t)idx - 1;
                }
                v = (uint32_t)r4;
                if (lo < v || v <= hi) goto oob;
                if ((map & 0xff000000) != 0) goto full;
                cur = v >> 8;
                r4 = (uint64_t)cur;
                map = (v & 0xff) << (-((uint32_t)__builtin_clzll(map) & 0x18) & 0x18) | map;
            } while (true);
        }
        code = 0xc2;
    }
full:
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d08c0, 0x1b, 2, code, 1);
oob:
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cdab0, 0x13, 2, 0x5cdad0, 0x16, 2, 0x2ca, 1);
    return 0;
}

/* FUN_00272a98 @ 0x00272a98   (est. sk_range_remove_first)
 * Ghidra: undefined1 [16] FUN_00272a98(ulong param_1)
 * removeFirst returning the removed Range value: refuses empty collection,
 * resolves the removed range via the collection geometry helpers, validates
 * the bound, and updates the collection; else fatal range trap.
 * Confidence: medium
 * Notes: FUN_002b439c/FUN_002ab6a0/FUN_002b3b84 geometry; range fatal string. */
cl4_result_t sk_range_remove_first(uint64_t idx)
{
    uint64_t *buf = 0; /* unaff_x20 */
    uint64_t b = buf[0];
    uint64_t e = buf[1];
    if (((e ^ b) >> 0xe) == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d0370, 0x25, 2, 0x5cdd20, 0x26, 2, 0x222, 1);
    }
    uint64_t s = buf[2];
    uint64_t f = buf[3];
    cl4_result_t r0 = sk_rt_002b439c(idx, b, e, s, f);
    uint64_t a = sk_rt_002ab6a0(idx, b, e, s, f);
    uint64_t v = sk_rt_002b3b84(a, b, e, s, f);
    if ((idx >> 0xe) <= (v >> 0xe)) {
        sk_rt_002ab5bc(idx, v, b, e, s, f);
        sk_rt_002a95b4();
        return r0;
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11, 2, 0x2f9, 1);
    return (cl4_result_t){ 0, 0 };
}

/* FUN_00272fc0 @ 0x00272fc0   (est. sk_bitbuffer_remove_first)
 * Ghidra: uint FUN_00272fc0(uint param_1)
 * removeFirst on a packed UInt buffer: refuses an empty buffer (0x222),
 * validates the range bound (0x2f9), shifts out the leading bits, and returns
 * the removed low word. Traps on overflow (0xd4/0xdd) via UIntBuffer string.
 * Confidence: medium
 * Notes: strings s_Can_t_remove_from_an_empty_colle_005d0370 /
 *   s_Range_requires_lowerBound_... / s_Swift_UIntBuffer_swift_005d0610. */
uint32_t sk_bitbuffer_remove_first(uint32_t idx)
{
    uint32_t *buf = 0; /* unaff_x20 */
    uint8_t b = (uint8_t)buf[1];
    if (b == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d0370, 0x25, 2, 0x5cdd20, 0x26, 2, 0x222, 1);
    }
    if ((idx & 0xff) > 0xef) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11, 2, 0x2f9, 1);
    }
    uint32_t code = 0xd4;
    uint32_t nb = idx + 0x10;
    if (!(b < (idx & 0xff)) && !(b < (nb & 0xff))) {
        int32_t d = (int32_t)((nb & 0xff) - (idx & 0xff)) / -0x10;
        int16_t sd = (int16_t)d;
        if ((int64_t)((uint64_t)(b >> 4) + (int64_t)sd) < 3) {
            uint32_t u = *buf;
            uint32_t m2 = idx >> 1 & 0x18;
            uint32_t m3 = nb >> 1 & 0x18;
            *buf = ((u >> m3) >> m3) << ((nb & 0xff) + sd * 0x10 & 0x10) |
                   u & (((uint32_t)1 << m2) << m2) - 1;
            *(uint8_t *)(buf + 1) = b + (int8_t)d * 0x10;
            return u >> (idx & 0x1f);
        }
        code = 0xdd;
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d0610, 0x16, 2, code, 1);
    return 0;
}

/* FUN_00273168 @ 0x00273168   (est. sk_bitbuffer_remove_first_8)
 * Ghidra: uint FUN_00273168(uint param_1)
 * removeFirst variant for 8-bit packed elements (mirrors FUN_00272fc0).
 * Confidence: medium
 * Notes: strings as FUN_00272fc0. */
uint32_t sk_bitbuffer_remove_first_8(uint32_t idx)
{
    uint32_t *buf = 0; /* unaff_x20 */
    uint8_t b = (uint8_t)buf[1];
    if (b == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d0370, 0x25, 2, 0x5cdd20, 0x26, 2, 0x222, 1);
    }
    if ((idx & 0xff) > 0xf7) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11, 2, 0x2f9, 1);
    }
    uint32_t code = 0xd4;
    uint32_t nb = idx + 8;
    if (!(b < (idx & 0xff)) && !(b < (nb & 0xff))) {
        int32_t d = (int32_t)((nb & 0xff) - (idx & 0xff)) / -8;
        int16_t sd = (int16_t)d;
        if ((int64_t)((uint64_t)(b >> 3) + (int64_t)sd) < 5) {
            uint32_t u = *buf;
            uint32_t m2 = idx >> 1 & 0x1c;
            uint32_t m3 = nb >> 1 & 0x1c;
            *buf = ((u >> m3) >> m3) << ((nb & 0xff) + sd * 8 & 0x18) |
                   u & (((uint32_t)1 << m2) << m2) - 1;
            *(uint8_t *)(buf + 1) = b + (int8_t)d * 8;
            return u >> (idx & 0x1f);
        }
        code = 0xdd;
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d0610, 0x16, 2, code, 1);
    return 0;
}

/* FUN_00274128 @ 0x00274128   (est. sk_range_remove_first_nil)
 * Ghidra: undefined1 [16] FUN_00274128(void)
 * removeFirst on a nested collection pair: refuses when the two collection
 * bounds are equal (0x331), resolves the removed range, and updates both the
 * buffer and its scalar view.
 * Confidence: medium
 * Notes: strings s_Unexpectedly_found_nil_while_unw_005cd7d0 /
 *   s_Swift_RangeReplaceableCollection_005cdd20; geometry FUN_002b3cf8. */
cl4_result_t sk_range_remove_first_nil(void)
{
    uint64_t **x20 = 0; /* unaff_x20 */
    uint64_t b = *(uint64_t *)*x20;
    uint64_t e = *(uint64_t *)(*x20 + 8);
    if ((b >> 0xe) == (e >> 0xe)) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cd7d0, 0x39, 2, 0x5cdd20, 0x26, 2, 0x331, 1);
    }
    uint64_t sb = *(uint64_t *)x20[1];
    uint64_t se = *(uint64_t *)(x20[1] + 8);
    uint64_t v = sk_rt_002b3cf8(e, b, e, sb, se);
    cl4_result_t r0 = sk_rt_002b439c(v, b, e, sb, se);
    uint64_t v2 = sk_rt_002b3cf8(e, b, e, sb, se);
    if ((b >> 0xe) <= (v2 >> 0xe)) {
        cl4_result_t nr = sk_rt_002ab5bc(b, v2, b, e, sb, se);
        *x20 = (uint64_t *)nr.lo;
        *(uint64_t *)x20[1] = sb;
        *(uint64_t *)(x20[1] + 8) = se;
        return r0;
    }
    sk_rt_003a25d4(r0.hi);
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11, 2, 0x2f9, 1);
    return (cl4_result_t){ 0, 0 };
}

/* ===================================================================== */
/* removeLast & UTF-8 scalar decode                                      */
/* ===================================================================== */

/* FUN_00272c58 @ 0x00272c58   (est. sk_string_remove_last_scalar)
 * Ghidra: uint FUN_00272c58(ulong param_1)
 * removeLast returning the decoded UTF-8 scalar: resolves the last scalar
 * position, decodes the 1-4 byte UTF-8 sequence (with the LZCOUNT-length
 * switch), validates the bound, and returns the scalar; else fatal range trap.
 * Confidence: medium
 * Notes: Swift_UnicodeHelpers string 0x34; UTF-8 decode; range fatal string. */
uint32_t sk_string_remove_last_scalar(uint64_t idx)
{
    uint64_t *buf = 0; /* unaff_x20 */
    uint64_t b = buf[0];
    uint64_t e = buf[1];
    if (((e ^ b) >> 0xe) == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d0370, 0x25, 2, 0x5cdd20, 0x26, 2, 0x222, 1);
    }
    uint64_t s = buf[2];
    uint64_t f = buf[3];
    uint64_t pos = sk_rt_002ab4d4(idx, b, e, s, f);
    uint64_t sc = 0;
    uint64_t byte;
    if ((f >> 0x3c & 1) != 0) {
        sk_rt_001afa84(0x5accd0, 0xb, 2, 0xd000000000000034ull, 0x5ce6d0, 0x5ce730, 0x1a, 2);
    }
    /* decode the leading UTF-8 byte and length at pos>>16 */
    uint64_t l = (f >> 0x3d & 1) != 0 ? 0 : (s >> 0x3c & 1) == 0 ? sk_rt_002a9ba8(s, f)
                                                                 : (f & 0xfffffffffffffff) + 0x20;
    uint8_t *p = (uint8_t *)(l + (pos >> 0x10));
    uint8_t c0 = p[0];
    uint32_t cp = c0;
    if ((int8_t)c0 < 0) {
        switch (__builtin_clzll((uint64_t)(uint32_t)((c0 << 0x18) ^ 0xffffffffu))) {
        case 2: cp = p[1] & 0x3f | (c0 & 0x1f) << 6; break;
        case 3: cp = (c0 & 0xf) << 0xc | (p[1] & 0x3f) << 6 | (p[2] & 0x3f); break;
        case 4: cp = (c0 & 0xf) << 0x12 | (p[1] & 0x3f) << 0xc | (p[2] & 0x3f) << 6 | (p[3] & 0x3f); break;
        }
    }
    /* compute the scalar length and validate bound */
    uint64_t q = sk_rt_00167404(idx, s, f) >> 0x10;
    uint64_t ll = (f >> 0x3d & 1) != 0 ? 0 : (s >> 0x3c & 1) == 0 ? sk_rt_002a9ba8(s, f)
                                                                  : (f & 0xfffffffffffffff) + 0x20;
    uint8_t cb = *(uint8_t *)(ll + q);
    uint32_t clen = (uint32_t)__builtin_clzll((uint64_t)(uint32_t)((cb << 0x18) ^ 0xffffffffu));
    if ((int8_t)cb >= 0) clen = 1;
    if ((idx >> 0xe) <= ((q + clen) << 2)) {
        sk_rt_002ab5bc(idx, (q + clen) * 0x10000 | 5, b, e, s, f);
        sk_rt_002a95b4();
        return cp;
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11, 2, 0x2f9, 1);
    return 0;
}

/* FUN_00273310 @ 0x00273310   (est. sk_string_scalar_decode)
 * Ghidra: void FUN_00273310(void)
 * Decodes and emits the scalar at a string index: validates the index, decodes
 * the UTF-8 sequence (LZCOUNT switch), computes the scalar length, writes the
 * (offset|5) position, and stores the scalar via the typed append.
 * Confidence: medium
 * Notes: Swift_UnicodeHelpers 0x34 trap; FUN_002ab8ac/FUN_002a7c00 append. */
void sk_string_scalar_decode(void)
{
    uint64_t *buf = 0; /* unaff_x20 */
    uint64_t b = buf[0];
    uint64_t e = buf[1];
    sk_rt_00041138();
    uint64_t cap = sk_rt_0034c094(b & 0xffffffffffff);
    if (cap == 0) {
        sk_rt_003488bc(1);
        sk_rt_0034a69c();
        sk_rt_00353f14();
        sk_rt_001afe4c();
    }
    sk_rt_00351190();
    uint64_t pos = sk_rt_00167404() >> 0x10;
    uint64_t cp = 0;
    uint64_t l = (e >> 0x3d & 1) != 0 ? 0 : (b >> 0x3c & 1) == 0 ? sk_rt_002a9ba8() : (e & 0xfffffffffffffff) + 0x20;
    uint8_t c0 = *(uint8_t *)(l + pos);
    uint32_t clen = 1;
    if ((int8_t)c0 < 0) {
        switch (__builtin_clzll((uint64_t)(uint32_t)((c0 << 0x18) ^ 0xffffffffu))) {
        case 2: cp = *(uint8_t *)(l + pos + 1) & 0x3f | (c0 & 0x1f) << 6; clen = 2; break;
        case 3: cp = (c0 & 0xf) << 0xc | (*(uint8_t *)(l + pos + 1) & 0x3f) << 6 | (*(uint8_t *)(l + pos + 2) & 0x3f); clen = 3; break;
        case 4: cp = (c0 & 0xf) << 0x12 | (*(uint8_t *)(l + pos + 1) & 0x3f) << 0xc | (*(uint8_t *)(l + pos + 2) & 0x3f) << 6 | (*(uint8_t *)(l + pos + 3) & 0x3f); clen = 4; break;
        }
    }
    sk_rt_0034b3f8(cp);
    if (((pos + clen) << 2) < (cap >> 0xe)) {
        sk_rt_00347d60();
        sk_rt_001afe4c();
    }
    sk_rt_00350a1c(cap, (pos + clen) * 0x10000 | 5);
    sk_rt_002ab8ac();
    sk_rt_002a7c00();
    sk_rt_0035847c(cp);
}

/* FUN_00273880 @ 0x00273880   (est. sk_string_remove_last_reset)
 * Ghidra: void FUN_00273880(ulong param_1)
 * removeLast: if the flag bit 0 is set, resolves the last scalar via the typed
 * index and removes it; otherwise resets the buffer to an empty state.
 * Confidence: medium
 * Notes: flag-bit test; FUN_002ab8ac/FUN_002a7c00; nil reset. */
void sk_string_remove_last_reset(uint64_t flag)
{
    uint64_t *buf = 0; /* unaff_x20 */
    if ((flag & 1) != 0) {
        uint64_t b = buf[0];
        uint64_t e = buf[1];
        uint64_t v = b;
        if ((e & 0x2000000000000000ull) != 0) {
            v = e >> 0x38 & 0xf;
        }
        uint32_t d = (uint32_t)(b >> 0x3b) & 1;
        if ((e & 0x1000000000000000ull) == 0) {
            d = 1;
        }
        uint64_t len = 7;
        if (d == 0) len = 0xb;
        sk_rt_002ab8ac(0xf, len | v << 0x10, b, e, 0x174, 0x164);
        sk_rt_002a7c00();
        return;
    }
    sk_rt_003a25d4(buf[1]);
    buf[0] = 0;
    buf[1] = 0xe000000000000000ull;
}

/* FUN_002738f0 @ 0x002738f0   (est. sk_string_reset_or_remove)
 * Ghidra: void FUN_002738f0(ulong param_1)
 * Resets a string collection: if flag bit 0 clear, releases and re-initializes
 * the four buffer words from a global constant; else validates the bounds and
 * removes the trailing element.
 * Confidence: medium
 * Notes: _DAT_004e7b40/004e7b48 constant; range fatal on bad bound. */
void sk_string_reset_or_remove(uint64_t flag)
{
    uint64_t *buf = 0; /* unaff_x20 */
    if ((flag & 1) == 0) {
        sk_rt_003a25d4(buf[3]);
        uint64_t g = sk_rt_004e7b40();
        buf[1] = 0x4e7b48;
        buf[0] = g;
        buf[2] = 0;
        buf[3] = 0xe000000000000000ull;
    } else {
        if ((buf[1] >> 0xe) < (buf[0] >> 0xe)) {
            sk_rt_00347d60();
            sk_rt_001afe4c();
        }
        sk_rt_00351790();
        sk_rt_002ab5bc();
        sk_rt_00350aac();
        sk_rt_002a95b4();
    }
}

/* FUN_00274290 @ 0x00274290   (est. sk_string_remove_last_backward)
 * Ghidra: ulong FUN_00274290(void)
 * removeLast (backward scan): refuses an empty collection (0x331), resolves
 * the last scalar position, walks backward over a multi-byte UTF-8 sequence,
 * updates the end bound, and returns the removed scalar. Traps on an
 * out-of-bounds string index (0x84) or bad range (0x2f9).
 * Confidence: medium
 * Notes: strings s_String_index_is_out_of_bounds_005ce6a0 /
 *   s_Swift_StringUnicodeScalarView_sw_005ce6c0; FUN_001b3984/FUN_002ab130. */
uint64_t sk_string_remove_last_backward(void)
{
    uint64_t **x20 = 0; /* unaff_x20 */
    uint64_t b = *(uint64_t *)*x20;
    uint64_t e = *(uint64_t *)(*x20 + 8);
    uint64_t sb = *(uint64_t *)x20[1];
    uint64_t se = *(uint64_t *)(x20[1] + 8);
    uint64_t st = sk_rt_001b3984(b, e, sb, se);
    if ((st & 0xff00000000ull) == 0x100000000ull) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cd7d0, 0x39, 2, 0x5cdd20, 0x26, 2, 0x331, 1);
    }
    uint64_t pos = sk_rt_002ab130(e, sb, se);
    if ((pos >> 0xe) == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5ce6a0, 0x1d, 2, 0x5ce6c0, 0x23, 2, 0x84, 1);
    }
    uint64_t clen = 0;
    if ((se >> 0x3c & 1) == 0) {
        if ((se >> 0x3d & 1) != 0) {
            /* inline string: count backward continuation bytes */
            if (1) {
                clen = 1;
                uint8_t *p = (uint8_t *)((se & 0xffffffffffffff) + (pos >> 0x10));
                while ((int8_t)*--p < -0x40) clen++;
            }
        } else {
            uint64_t l = (sb >> 0x3c & 1) == 0 ? sk_rt_002a9ba8(sb, se) : (se & 0xfffffffffffffff) + 0x20;
            uint8_t *p = (uint8_t *)(l + (pos >> 0x10) - 1);
            clen = 1;
            while ((int8_t)*p-- < -0x40) clen++;
        }
        pos = (pos + clen * -0x10000) & 0xffffffffffff0000ull;
        if ((b >> 0xe) <= (pos >> 0xe)) {
            cl4_result_t nr = sk_rt_002ab5bc(b, pos | 5, b, e, sb, se);
            *x20 = (uint64_t *)nr.lo;
            *(uint64_t *)x20[1] = sb;
            *(uint64_t *)(x20[1] + 8) = se;
            return st & 0xffffffffffull;
        }
    } else {
        sk_rt_002ae098(pos, sb, se);
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11, 2, 0x2f9, 1);
    return 0;
}

/* FUN_00274994 @ 0x00274994   (est. sk_string_remove_last_scalar2)
 * Ghidra: void FUN_00274994(void)
 * removeLast with scalar decode: refuses an empty collection (0x363), resolves
 * the last scalar, decodes and removes it. Traps on out-of-bounds (0x84) or
 * bad range (0x2f9).
 * Confidence: medium
 * Notes: strings s_Can_t_remove_last_element_from_a_005d03a0 /
 *   s_Swift_RangeReplaceableCollection_005cdd20; decode via FUN_00273310. */
void sk_string_remove_last_scalar2(void)
{
    uint64_t *buf = 0; /* unaff_x20 */
    uint64_t b = buf[0];
    uint64_t e = buf[1];
    uint64_t v = b & 0xffffffffffff;
    if ((e & 0x2000000000000000ull) != 0) {
        v = e >> 0x38 & 0xf;
    }
    if (v == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d03a0, 0x32, 2, 0x5cdd20, 0x26, 2, 0x363, 1);
    }
    uint32_t d = (uint32_t)(b >> 0x3b) & 1;
    if ((e & 0x1000000000000000ull) == 0) {
        d = 1;
    }
    uint64_t len = 7;
    if (d == 0) len = 0xb;
    uint64_t pos = sk_rt_002ab130(len | v << 0x10, b, e);
    if ((pos >> 0xe) == 0) {
        sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5ce6a0, 0x1d, 2, 0x5ce6c0, 0x23, 2, 0x84, 1);
    }
    uint64_t clen = 0;
    if ((e >> 0x3c & 1) == 0) {
        if ((e >> 0x3d & 1) != 0) {
            uint8_t *p = (uint8_t *)((e & 0xffffffffffffff) + (pos >> 0x10));
            clen = 1;
            if ((uint8_t)p[1] == 0xbf || (int8_t)p[1] < -0x41) {
                while ((int8_t)*p-- < -0x40) clen++;
            }
        } else {
            uint64_t l = (b >> 0x3c & 1) == 0 ? sk_rt_002a9ba8(b, e) : (e & 0xfffffffffffffff) + 0x20;
            uint8_t *p = (uint8_t *)(l + (pos >> 0x10) - 1);
            clen = 1;
            while ((int8_t)*p-- < -0x40) clen++;
        }
    } else {
        sk_rt_002ae098(pos, b, e);
    }
    sk_rt_00273310((pos + clen * -0x10000) & 0xffffffffffff0000ull | 5);
}

/* FUN_00274b4c @ 0x00274b4c   (est. sk_collection_remove_last_elem)
 * Ghidra: ulong FUN_00274b4c(void)
 * removeLast returning the removed element: if the collection has a trailing
 * element at +0x10, resolves its index and returns it; else traps (0x363).
 * Confidence: medium
 * Notes: strings s_Can_t_remove_last_element_from_a_005d03a0 /
 *   s_Swift_RangeReplaceableCollection_005cdd20; FUN_001a2838/FUN_001a29d4. */
uint64_t sk_collection_remove_last_elem(void)
{
    uint64_t **x20 = 0; /* unaff_x20 */
    if (*(uint64_t *)(*x20 + 0x10) != 0) {
        uint64_t v = sk_rt_001a2838();
        if ((v & 0xff000000000000ull) == 0x1000000000000ull) {
            v = sk_rt_001a29d4(*(uint64_t *)(*x20 + 0x10) - 1);
        }
        return v & 0xffffffffffffull;
    }
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5d03a0, 0x32, 2, 0x5cdd20, 0x26, 2, 0x363, 1);
    return 0;
}

/* FUN_002718e0 @ 0x002718e0   (est. sk_string_append_opt)
 * Ghidra: undefined8 FUN_002718e0(undefined8 param_1, undefined8 param_2, long param_3)
 * Appends an Optional String: if count==0 releases the nil value; otherwise
 * repeats the scalar into the buffer and returns the width 0xf.
 * Confidence: medium
 * Notes: FUN_002a72e4 repeat; thunk_FUN_002b3978 append; FUN_003a25d4 release. */
uint64_t sk_string_append_opt(uint64_t a, uint64_t old, int64_t count)
{
    if (count == 0) {
        sk_rt_003a25d4(old);
    } else {
        sk_rt_00271bdc();
        sk_rt_002a72e4();
        sk_rt_003a25d4(count);
        sk_rt_002b3978(0, 0xe000000000000000ull);
    }
    return 0xf;
}

/* ===================================================================== */
/* String map / filter / transform                                       */
/* ===================================================================== */

/* FUN_0027590c @ 0x0027590c   (est. sk_string_map)
 * Ghidra: undefined8 FUN_0027590c(ulong param_1, ulong param_2, code *param_3)
 * Maps each UTF-8 scalar of a string through the closure param_3, building a
 * new packed string. Decodes each scalar, runs the closure, and appends the
 * result via the typed append; returns the resulting string. Early-returns
 * when the closure reports an error (x21 flag).
 * Confidence: medium
 * Notes: UTF-8 decode (LZCOUNT switch); FUN_002a200c/FUN_002a2698 append;
 *   FUN_002a4c98/FUN_00291ee0 tag coercion; FUN_003a25d4 releases. */
uint64_t sk_string_map(uint64_t str, uint64_t flags, void *fn)
{
    uint64_t count = str & 0xffffffffffff;
    if ((flags & 0x2000000000000000ull) != 0) {
        count = flags >> 0x38 & 0xf;
    }
    if (count == 0) {
        sk_rt_003a25d4(flags);
        return 0;
    }
    if ((flags >> 0x3c & 1) != 0) {
        sk_rt_001afa84(0x5accd0, 0xb, 2, 0xd000000000000034ull, 0x5ce6d0, 0x5ce730, 0x1a, 2, 0xfd, 1);
    }
    uint64_t off = 0;
    uint64_t out = 0;
    do {
        uint64_t l = (flags >> 0x3d & 1) == 0
            ? ((str >> 0x3c & 1) == 0 ? sk_rt_002a9ba8(str, flags) : (flags & 0xfffffffffffffff) + 0x20)
            : (flags & 0xffffffffffffff);
        uint8_t *p = (uint8_t *)(l + off);
        uint8_t c0 = p[0];
        uint32_t cp = c0;
        int clen = 1;
        if ((int8_t)c0 < 0) {
            switch (__builtin_clzll((uint64_t)(uint32_t)((c0 << 0x18) ^ 0xffffffffu))) {
            case 2: cp = p[1] & 0x3f | (c0 & 0x1f) << 6; clen = 2; break;
            case 3: cp = (c0 & 0xf) << 0xc | (p[1] & 0x3f) << 6 | (p[2] & 0x3f); clen = 3; break;
            case 4: cp = (c0 & 0xf) << 0x12 | (p[1] & 0x3f) << 0xc | (p[2] & 0x3f) << 6 | (p[3] & 0x3f); clen = 4; break;
            }
        }
        uint64_t r = ((uint64_t (*)(uint32_t *))fn)(&cp);
        if (0 /* x21 error flag */) {
            sk_rt_003a25d4(flags);
            return sk_rt_003a25d4(0);
        }
        if ((r & 1) == 0) {
            /* encode scalar back to UTF-8 */
            uint32_t t;
            if (cp < 0x80) t = cp + 1;
            else {
                uint32_t g = (cp & 0x3f) * 0x100;
                uint32_t t2 = (g | cp >> 6 & 0x3f) * 0x100;
                uint32_t a = (cp >> 0x12 | (t2 | cp >> 0xc & 0x3f) << 8) + 0x818181f1;
                if (cp >> 0x10 == 0) a = (cp >> 0xc) + t2 + 0x8181e1;
                t = (cp >> 6) + g + 0x81c1;
                if (cp > 0x7ff) t = a;
            }
            uint64_t w = (uint64_t)(4 - (__builtin_clzll((uint64_t)t) >> 3));
            uint32_t enc = t + 0xfefefefeff &
                           (0xffffffffffffffffull << ((w & 7) << 3));
            uint32_t isbig = sk_rt_002a200c(&enc, w);
            cl4_result_t nr = sk_rt_002a2698(&enc, w, isbig & 1);
            sk_rt_002a4c98(nr.lo, nr.hi, 0, 0);
            sk_rt_003a25d4(nr.hi);
        }
        off += clen;
    } while (off < count);
    sk_rt_003a25d4(flags);
    return 0;
}

/* FUN_00275cd0 @ 0x00275cd0   (est. sk_string_map_range)
 * Ghidra: undefined8 FUN_00275cd0(ulong param_1, ulong param_2, ulong param_3, ulong param_4, code *param_5)
 * Maps a sub-range of a string through the closure param_5, decoding each
 * scalar in [param_1, param_2) and appending the results. Returns the new
 * packed string.
 * Confidence: medium
 * Notes: mirrors FUN_0027590c over a Range; UTF-8 decode; typed append. */
uint64_t sk_string_map_range(uint64_t lo, uint64_t hi, uint64_t s, uint64_t flags, void *fn)
{
    uint64_t out = 0xf;
    if ((hi >> 0xe) == (lo >> 0xe)) {
        sk_rt_003a25d4(flags);
        return 0xf;
    }
    uint64_t cur = lo;
    uint64_t q = 0;
    uint32_t cl = 0;
    do {
        uint64_t pos = sk_rt_002ab4d4(cur, lo, hi, s, flags);
        uint64_t l = (flags >> 0x3d & 1) == 0
            ? ((s >> 0x3c & 1) == 0 ? sk_rt_002a9ba8(s, flags) : (flags & 0xfffffffffffffff) + 0x20)
            : (flags & 0xffffffffffffff);
        uint8_t *p = (uint8_t *)(l + (pos >> 0x10));
        uint8_t c0 = p[0];
        uint32_t cp = c0;
        int clen = 1;
        if ((int8_t)c0 < 0) {
            switch (__builtin_clzll((uint64_t)(uint32_t)((c0 << 0x18) ^ 0xffffffffu))) {
            case 2: cp = p[1] & 0x3f | (c0 & 0x1f) << 6; break;
            case 3: cp = (c0 & 0xf) << 0xc | (p[1] & 0x3f) << 6 | (p[2] & 0x3f); break;
            case 4: cp = (c0 & 0xf) << 0x12 | (p[1] & 0x3f) << 0xc | (p[2] & 0x3f) << 6 | (p[3] & 0x3f); break;
            }
        }
        q = sk_rt_00167404(cur, s, flags) >> 0x10;
        uint64_t ll = (flags >> 0x3d & 1) == 0
            ? ((s >> 0x3c & 1) == 0 ? sk_rt_002a9ba8(s, flags) : (flags & 0xfffffffffffffff) + 0x20)
            : (flags & 0xffffffffffffff);
        uint8_t cb = *(uint8_t *)(ll + q);
        cl = (uint32_t)__builtin_clzll((uint64_t)(uint32_t)((cb << 0x18) ^ 0xffffffffu));
        if ((int8_t)cb >= 0) cl = 1;
        uint64_t r = ((uint64_t (*)(uint32_t *))fn)(&cp);
        if (0 /* x21 */) {
            sk_rt_003a25d4(flags);
            return sk_rt_003a25d4(0);
        }
        if ((r & 1) == 0) {
            sk_rt_002ab5bc(7, 7, out, 7, 0, 0xe000000000000000ull);
            cl4_result_t nr = sk_rt_002a95b4();
            sk_rt_002a95b4(nr.lo, nr.hi, &out, &(uint64_t){7}, 0x343c98);
        }
        cur = (q + cl) * 0x10000 | 5;
    } while ((hi >> 0xe) != ((q + cl) * 4));
    sk_rt_003a25d4(flags);
    return out;
}

/* FUN_0027630c @ 0x0027630c   (est. sk_string_flatmap)
 * Ghidra: void FUN_0027630c(code *param_1)
 * flatMap over a string's scalars: allocates an output buffer, iterates each
 * scalar through the closure param_1, and concatenates the results; releases
 * the intermediate values on completion or error.
 * Confidence: medium
 * Notes: FUN_0029fb80 iterator; FUN_00291ee0/FUN_002a4c98 tag handling. */
void sk_string_flatmap(void *fn)
{
    uint64_t **x20 = 0; /* unaff_x20 */
    uint64_t b = *(uint64_t *)*x20;
    uint64_t e = *(uint64_t *)(*x20 + 8);
    sk_rt_0036b270();
    uint64_t out0 = 0, out1 = 0xe000000000000000ull;
    do {
        cl4_result_t it = sk_rt_0029fb80();
        if (it.hi == 0) {
            sk_rt_003a2610(e, 2);
            *x20 = (uint64_t *)out0;
            return;
        }
        uint64_t r = ((uint64_t (*)(cl4_result_t))fn)(it);
        if (0 /* x21 */) {
            sk_rt_003a25d4(e);
            sk_rt_003a25d4(it.hi);
            sk_rt_003a25d4(out1);
            return;
        }
        if ((r & 1) != 0) {
            sk_rt_003a25d4(it.hi);
            continue;
        }
        /* append scalar to output */
        uint64_t v = it.lo;
        if ((it.hi & 0x2000000000000000ull & out1) == 0) {
            uint64_t w = v & 0xffffffffffff;
            if ((it.hi & 0x2000000000000000ull) != 0) w = it.hi >> 0x38 & 0xf;
            sk_rt_002a4c98(v, it.hi, 0, w);
        } else {
            sk_rt_00291ee0(out0, out1, v, it.hi);
        }
        sk_rt_003a25d4(it.hi);
    } while (true);
}

/* FUN_002764a8 @ 0x002764a8   (est. sk_string_map_wrap)
 * Ghidra: void FUN_002764a8(undefined8 param_1, undefined8 param_2)
 * Wrapper: reads the string from x20, runs FUN_0027590c (map) with the
 * closure, and stores the result back into the string slot.
 * Confidence: low
 * Notes: FUN_0036b270 alloc; stores result to *x20. */
void sk_string_map_wrap(uint64_t a, uint64_t b)
{
    uint64_t **x20 = 0; /* unaff_x20 */
    uint64_t s = *(uint64_t *)*x20;
    uint64_t f = *(uint64_t *)(*x20 + 8);
    sk_rt_0036b270(f);
    cl4_result_t r = sk_rt_0027590c(s, f, a, b);
    if (0 /* x21 */ == 0) {
        sk_rt_003a25d4(f);
        *x20 = (uint64_t *)r.lo;
    }
}

/* FUN_00276514 @ 0x00276514   (est. sk_string_map_range_wrap)
 * Ghidra: void FUN_00276514(undefined8 param_1, undefined8 param_2)
 * Wrapper: reads the string + scalar view from x20, runs FUN_00275cd0
 * (range map), and stores the result back.
 * Confidence: low
 * Notes: FUN_0036b270 alloc; stores result to *x20. */
void sk_string_map_range_wrap(uint64_t a, uint64_t b)
{
    uint64_t **x20 = 0; /* unaff_x20 */
    uint64_t s = *(uint64_t *)*x20;
    uint64_t f = *(uint64_t *)(*x20 + 8);
    uint64_t sb = *(uint64_t *)x20[1];
    uint64_t se = *(uint64_t *)(x20[1] + 8);
    sk_rt_0036b270(se);
    cl4_result_t r = sk_rt_00275cd0(s, f, sb, se, a, b);
    if (0 /* x21 */ == 0) {
        sk_rt_003a25d4(se);
        *x20 = (uint64_t *)r.lo;
        *(uint64_t *)x20[1] = sb;
        *(uint64_t *)(x20[1] + 8) = se;
    }
}

/* FUN_002765a0 @ 0x002765a0   (est. sk_string_filter)
 * Ghidra: void FUN_002765a0(code *param_1)
 * filter: iterates the string's Range of scalars through the closure param_1,
 * collecting the accepted scalars into a new string; returns the result.
 * Confidence: medium
 * Notes: FUN_002b439c/FUN_002ab6a0/FUN_002b3b84 range geometry; typed append. */
void sk_string_filter(void *fn)
{
    uint64_t *buf = 0; /* unaff_x20 */
    uint64_t b = buf[0];
    uint64_t e = buf[1];
    uint64_t s = buf[2];
    uint64_t f = buf[3];
    uint64_t out = 0xf;
    uint64_t cur = b;
    uint64_t r0hi = 0;
    while (true) {
        if ((cur ^ e) < 0x4000) {
            sk_rt_003a25d4(f);
            buf[0] = out;
            buf[1] = 7;
            buf[2] = 0;
            buf[3] = 0xe000000000000000ull;
            return;
        }
        cl4_result_t r0 = sk_rt_002b439c(cur, b, e, s, f);
        r0hi = r0.hi;
        uint64_t a = sk_rt_002ab6a0(cur, b, e, s, f);
        cur = sk_rt_002b3b84(a, b, e, s, f);
        uint64_t r = ((uint64_t (*)(cl4_result_t))fn)(r0);
        if (0 /* x21 */) break;
        if ((r & 1) == 0) {
            sk_rt_002ab5bc(7, 7, out, 7, 0, 0xe000000000000000ull);
            cl4_result_t nr = sk_rt_002a95b4();
            sk_rt_002a95b4(nr.lo, nr.hi, &out, &(uint64_t){7}, 0x343c84);
            sk_rt_003a25d4(r0.hi);
        } else {
            sk_rt_003a25d4(r0.hi);
        }
    }
    sk_rt_003a25d4(r0hi);
    sk_rt_003a25d4(0);
}

/* FUN_0027675c @ 0x0027675c   (est. sk_utf8buffer_filter)
 * Ghidra: void FUN_0027675c(code *param_1)
 * filter over a packed UTF-8 buffer: iterates bytes from most-significant,
 * runs the closure on each (byte-1), and folds accepted bytes into the map.
 * Confidence: medium
 * Notes: ValidUTF8Buffer overflow 0xa7 trap; byte-fold loop. */
void sk_utf8buffer_filter(void *fn)
{
    uint32_t *buf = 0; /* unaff_x20 */
    uint32_t map = 0;
    uint32_t u = *buf;
    while (true) {
        uint32_t v = u;
        if (v == 0) {
            *buf = map;
            return;
        }
        uint8_t byte = (uint8_t)v - 1;
        uint64_t r = ((uint64_t (*)(uint8_t *))fn)(&byte);
        if (0 /* x21 */) break;
        u = v >> 8;
        if ((r & 1) == 0) {
            if ((map & 0xff000000) != 0) {
                sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5be7c0, 0, 2, 0x5d08c0, 0x1b, 2, 0xa7, 1);
            }
            map = (v & 0xff) << (-((uint32_t)__builtin_clzll(map) & 0x18) & 0x18) | map;
        }
    }
}

/* ===================================================================== */
/* Remaining string / collection ops                                     */
/* ===================================================================== */

/* FUN_00273fe0 @ 0x00273fe0   (est. sk_string_remove_at)
 * Ghidra: void FUN_00273fe0(void)
 * remove(at:) on a string: locks the object, removes the scalar at the
 * resolved index, and releases.
 * Confidence: low
 * Notes: FUN_00377824/FUN_00377bec lock pair; FUN_00350470 index metadata. */
void sk_string_remove_at(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_003542d0();
    sk_rt_00351bec();
    sk_rt_0034a944();
    sk_rt_00350c08();
    uint64_t k = sk_rt_00377824();
    sk_rt_00355314();
    cl4_result_t idx = sk_rt_00350470();
    sk_rt_00377bec(idx.lo, idx.hi, k);
    sk_rt_0034dee4();
    sk_rt_00310e08();
    sk_rt_00348e60();
    sk_rt_0007c1a4();
    sk_rt_0034af20();
    sk_rt_0031b164();
    sk_rt_00351184();
    sk_rt_0034f5b4();
    sk_rt_00354318();
    sk_rt_0031d488();
    sk_rt_00350a7c();
    sk_rt_0035056c();
    sk_rt_00350ab8();
    sk_rt_0008e500();
}

/* FUN_002740e4 @ 0x002740e4   (est. sk_string_reserve_capacity)
 * Ghidra: void FUN_002740e4(void)
 * Reserves capacity on a string: opens the buffer, records the current CPU
 * metadata, and runs the reserve-allocation path.
 * Confidence: low
 * Notes: FUN_00352800/FUN_00351d24/FUN_000839d8; FUN_00377824 lock. */
void sk_string_reserve_capacity(void)
{
    sk_rt_00352800();
    sk_rt_00027754();
    sk_rt_00348b94();
    sk_rt_00377824();
    cl4_result_t md = sk_rt_00351d24();
    sk_rt_000839d8(md.lo, md.hi, 1);
}

/* FUN_002754f4 @ 0x002754f4   (est. sk_string_trim)
 * Ghidra: void FUN_002754f4(void)
 * Trims whitespace from a string: opens the trim view, walks the leading and
 * trailing scalars, and renders the trimmed substring.
 * Confidence: low
 * Notes: FUN_0031d678 trim; FUN_00350624/FUN_00353208 view ops. */
void sk_string_trim(void)
{
    sk_rt_00084220();
    sk_rt_003543ac();
    sk_rt_0035128c();
    sk_rt_00358e88();
    sk_rt_00349a68();
    sk_rt_0036a908();
    sk_rt_00349068();
    sk_rt_0034b07c();
    sk_rt_0034feb0();
    sk_rt_0031d678();
    sk_rt_00350648();
    sk_rt_00350624();
    sk_rt_00353208();
    sk_rt_00084234();
}

/* FUN_00275780 @ 0x00275780   (est. sk_string_trim_ws)
 * Ghidra: void FUN_00275780(void)
 * Whitespace-trim helper: builds the whitespace character set and strips it
 * from both ends of the string.
 * Confidence: low
 * Notes: FUN_0035603c whitespace set; FUN_0031d678 trim. */
void sk_string_trim_ws(void)
{
    sk_rt_003543ac();
    sk_rt_00353e88();
    sk_rt_00349a68();
    sk_rt_0036a908();
    sk_rt_00348f38();
    cl4_result_t ws = sk_rt_0035603c();
    sk_rt_00350a24(ws.lo, ws.hi);
    sk_rt_0031d678();
    sk_rt_0035066c();
    sk_rt_00350624();
    sk_rt_00353208();
}

/* FUN_0027582c @ 0x0027582c   (est. sk_string_trim_cl)
 * Ghidra: void FUN_0027582c(void)
 * Closure-based trim: strips characters matching the caller's predicate from
 * both ends.
 * Confidence: low
 * Notes: FUN_0031d678 trim; FUN_003549c0 predicate. */
void sk_string_trim_cl(void)
{
    sk_rt_00084220();
    sk_rt_00351da8();
    uint64_t v = sk_rt_00357788();
    sk_rt_00349a68(v, v);
    sk_rt_0036a908();
    sk_rt_00349068();
    sk_rt_0034b07c();
    sk_rt_00100c38();
    void *fn = (void *)sk_rt_0031d678();
    sk_rt_00027754();
    sk_rt_003549c0();
    sk_rt_00351f88();
    sk_rt_00352920();
    sk_rt_00084234();
}

/* FUN_002755c0 @ 0x002755c0   (est. sk_string_split)
 * Ghidra: void FUN_002755c0(void)
 * Splits a string on a separator: iterates scalars, partitions on the
 * separator, and collects the substrings. Uses a SoftwareBreakpoint trap for
 * the overflow check on the accumulating sizes.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1,0x275780); FUN_00352920 collect. */
void sk_string_split(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_00359c58();
    sk_rt_00357788();
    sk_rt_00349720();
    sk_rt_0036a908();
    sk_rt_003497b4();
    sk_rt_00351c10();
    sk_rt_00349a68();
    sk_rt_0036a908();
    sk_rt_0034947c();
    sk_rt_0031e0d4();
    sk_rt_0034d354();
    sk_rt_00351bec();
    sk_rt_00353efc();
    sk_rt_00350494();
    uint64_t a = sk_rt_00310e20();
    sk_rt_000a6894();
    sk_rt_003514ac();
    uint64_t b = sk_rt_00310e20();
    /* accumulate split sizes; overflow traps */
    sk_rt_0031d768();
    sk_rt_00351318();
    sk_rt_003504a0();
    sk_rt_00350b00();
    sk_rt_0031d678();
    cl4_result_t v = sk_rt_003509b0();
    sk_rt_00352920(v.lo, v.hi);
    sk_rt_003549c0();
    sk_rt_00100efc();
    sk_rt_00352920();
    sk_rt_0008e500();
}

/* FUN_00276840 @ 0x00276840   (est. sk_string_reversed)
 * Ghidra: void FUN_00276840(void)
 * Reversed-string view: opens the reversed view over the string and renders
 * it via FUN_00276034.
 * Confidence: low
 * Notes: FUN_003513fc reversed-view init; FUN_00276034 iterate. */
void sk_string_reversed(void)
{
    sk_rt_00353cfc();
    sk_rt_00356048();
    sk_rt_003537fc();
    sk_rt_00349720();
    sk_rt_0036a908();
    sk_rt_00348a34();
    sk_rt_0034b8bc();
    sk_rt_00352bb0();
    sk_rt_00350b00();
    sk_rt_003513fc(0x347a20);
    sk_rt_00276034();
    if (0 /* x21 */ == 0) {
        sk_rt_0034fd3c();
        sk_rt_003508d8();
    }
    sk_rt_00352df4();
    sk_rt_00353d14();
}

/* FUN_0027743c @ 0x0027743c   (est. sk_string_repeat_append)
 * Ghidra: void FUN_0027743c(undefined8 param_1, undefined8 param_2)
 * Appends a repeated scalar to a string: bounds-checks, appends, and returns.
 * Confidence: low
 * Notes: FUN_00352efc bounds; FUN_00310e08; FUN_001a0414/FUN_001dd1ec append. */
void sk_string_repeat_append(uint64_t a, uint64_t b)
{
    sk_rt_00352efc(a, b, b);
    sk_rt_00310e08();
    sk_rt_0034da88();
    sk_rt_001a0414();
    sk_rt_001dd1ec();
}

/* FUN_00277474 @ 0x00277474   (est. sk_string_repeat_alloc)
 * Ghidra: void FUN_00277474(void)
 * Allocates the buffer for a repeated string: reads the element width at
 * +0x50, sizes the allocation, and initializes the repeated buffer.
 * Confidence: low
 * Notes: FUN_0036a940 alloc; FUN_001a0534 init; width byte at +0x50. */
void sk_string_repeat_alloc(void)
{
    sk_rt_00310e08(0xff);
    sk_rt_00350798();
    sk_rt_0031d798();
    uint64_t v = sk_rt_00349b00();
    uint64_t width = *(uint8_t *)(sk_rt_00310e20() + 0x50);
    uint64_t size = (width + 0x20) & (width ^ 0xffffffffffffffffull);
    uint64_t buf = sk_rt_0036a940(v, size + *(uint64_t *)(sk_rt_00310e20() + 0x48), width | 7);
    uint64_t p = sk_rt_001a0534(buf, 1);
    sk_rt_00350968(*(uint64_t *)(sk_rt_00310e20() + 0x20), p + size);
    sk_rt_003509bc();
    sk_rt_001dd1ec();
}

/* FUN_00277ba8 @ 0x00277ba8   (est. sk_string_capacity_commit)
 * Ghidra: void FUN_00277ba8(void)
 * Commits capacity on a string: records the buffer metadata and size into the
 * string's backing store.
 * Confidence: low
 * Notes: FUN_0019e578 commit; FUN_00310d34 metadata. */
void sk_string_capacity_commit(void)
{
    sk_rt_00352ddc();
    sk_rt_00310e08();
    sk_rt_00352efc();
    cl4_result_t md = sk_rt_00310d34();
    sk_rt_0034921c(md.lo, md.hi, md.lo);
    sk_rt_0019e578();
}

/* ===================================================================== */
/* Remaining string / collection ops (2)                                 */
/* ===================================================================== */

/* FUN_0026dabc @ 0x0026dabc   (est. sk_range_operation)
 * Ghidra: void FUN_0026dabc(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Generic Range operation dispatcher: opens the range, resolves the scalar
 * endpoints and metadata, runs a sequence of view-vtable operations
 * (access +0x20, step +8, plus helper calls), and tears down via the epilogue
 * helper.
 * Confidence: low
 * Notes: complex Swift runtime glue with many FUN_0034xxxx view ops. */
void sk_range_operation(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    cl4_result_t md = sk_rt_0034b0b4();
    uint64_t base = md.hi;
    sk_rt_003722e4(md.lo, base, base);
    uint64_t r = sk_rt_000a6f88();
    sk_rt_0036a908();
    sk_rt_0034928c();
    sk_rt_0034aa28();
    sk_rt_0034d8e4();
    sk_rt_00377824();
    sk_rt_00348e00();
    sk_rt_0007c1a4();
    sk_rt_0034b708();
    sk_rt_00350878(c);
    sk_rt_00377bec();
    sk_rt_00027754();
    sk_rt_003564d0();
    sk_rt_0034d424();
    sk_rt_00377824();
    sk_rt_0034ab20();
    sk_rt_0007c1a4();
    sk_rt_0034b2f8();
    sk_rt_003494e8();
    sk_rt_0036a908();
    sk_rt_00348a18();
    sk_rt_0034b3d8();
    uint64_t v = sk_rt_003549c0(c);
    sk_rt_003504e8();
    uint64_t p = sk_rt_00310f04();
    sk_rt_0034b768();
    sk_rt_00377bec();
    uint64_t q = sk_rt_0034bc04();
    sk_rt_00352a4c(q, 0x200);
    sk_rt_0034cea8();
    sk_rt_00351a2c();
    sk_rt_0034db18();
    sk_rt_00354f4c(c);
    sk_rt_00350e64();
    sk_rt_00354660();
    sk_rt_003507bc();
    sk_rt_00353a00();
    sk_rt_0035056c();
    sk_rt_003509c8(p);
    cl4_result_t md2 = sk_rt_00350ab8();
    sk_rt_00351300();
    sk_rt_00351d0c();
    cl4_result_t md3 = sk_rt_00350ea4();
    sk_rt_00351118();
    cl4_result_t md4 = sk_rt_00350ea4();
    cl4_result_t md5 = sk_rt_0035050c();
    sk_rt_00310e08(md5.lo, md5.hi, v);
    uint64_t t = sk_rt_00353ac8();
    sk_rt_00100c38();
    sk_rt_0008e500();
}

/* FUN_0026def8 @ 0x0026def8   (est. sk_range_transform)
 * Ghidra: void FUN_0026def8(void)
 * Range transform over scalar endpoints: iterates the range's scalars through
 * a series of view-vtable operations, transforming each and advancing; uses
 * FUN_00351354/FUN_00353d7c/FUN_003509b0 helpers and the +0x10/+0x20 vtable
 * entries.
 * Confidence: low
 * Notes: Swift runtime glue; many FUN_0034xxxx view ops. */
void sk_range_transform(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_00359f48();
    uint64_t base = sk_rt_0034b0b4().hi + 0x10;
    sk_rt_003579d8();
    sk_rt_00348ce8();
    sk_rt_0036a908();
    sk_rt_0034928c();
    sk_rt_0034b87c();
    sk_rt_00349b00();
    sk_rt_0036a908();
    sk_rt_00348a9c();
    sk_rt_0034b8bc();
    uint64_t f = sk_rt_00310b08();
    sk_rt_00350a40();
    sk_rt_00350298();
    uint64_t ok = sk_rt_00350298();
    if ((ok & 1) == 0) {
        sk_rt_0035044c(f);
        sk_rt_00350298();
    } else {
        cl4_result_t v = sk_rt_00351354();
        sk_rt_00350a40();
    }
    uint64_t off = sk_rt_00310e20();
    sk_rt_0035044c(f);
    sk_rt_00350aac();
    uint64_t ok2 = sk_rt_00350298();
    if ((ok2 & 1) == 0) {
        cl4_result_t v = sk_rt_00353d7c();
        sk_rt_00350aac();
        sk_rt_00350aac();
    } else {
        cl4_result_t v = sk_rt_00353d7c();
    }
    cl4_result_t v2 = sk_rt_00100c38();
    sk_rt_00352474();
    sk_rt_00350618();
    cl4_result_t v3 = sk_rt_00350b3c();
    sk_rt_00350618();
    sk_rt_0035a518();
    sk_rt_003512c0();
    sk_rt_0008e500();
}

/* FUN_0026ea04 @ 0x0026ea04   (est. sk_range_transform2)
 * Ghidra: void FUN_0026ea04(undefined8 param_1, undefined8 param_2, undefined1 *param_3, undefined8 param_4, code *param_5)
 * Range transform over scalars with a closure param_5: iterates the scalar
 * endpoints, applies the closure, and accumulates the results into the output
 * buffer, with the standard Optional-tag validation at each stage. Traps on a
 * bad range bound (0x2f9).
 * Confidence: low
 * Notes: large Swift runtime glue; strings s_with_a_lowerBound___005cef40 /
 *   s___greater_than_upperBound___005cef60; fatal FUN_001afe4c. */
void sk_range_transform2(uint64_t a, uint64_t b, uint8_t *p3, uint64_t p4, void *fn)
{
    cl4_result_t md = sk_rt_00353cfc();
    uint64_t base = md.hi;
    uint64_t l = md.lo;
    cl4_result_t md2 = sk_rt_0034b0b4();
    uint64_t r = sk_rt_003722e4(md2.lo, md2.hi, md2.hi);
    sk_rt_000a6f88();
    sk_rt_0036a908();
    sk_rt_003493c4();
    sk_rt_0034d244();
    sk_rt_0034ea54();
    sk_rt_003499c8();
    sk_rt_0036a908();
    sk_rt_00348abc();
    sk_rt_0034c2d8();
    cl4_result_t md3 = sk_rt_0035050c();
    ((void (*)(uint64_t, uint64_t, uint8_t *))fn)(md3.lo, md3.hi, p3);
    sk_rt_00348e18();
    sk_rt_0007c1a4();
    sk_rt_0034af20();
    uint64_t v = *(uint64_t *)(l + 0x20);
    sk_rt_00350a04();
    sk_rt_000dbcc8();
    sk_rt_00352680(v);
    sk_rt_00350a70();
    if (0 /* x21 */ != 0) return;
    sk_rt_00356864();
    sk_rt_000836a4();
    sk_rt_00353ccc();
    sk_rt_0031a1ac();
    uint64_t sv = sk_rt_00351058();
    sk_rt_00356864();
    sk_rt_000836a4();
    sk_rt_00353ccc();
    sk_rt_0031a1ac();
    sk_rt_00353480();
    sk_rt_003508d8();
    sk_rt_00356078();
    sk_rt_00310e20();
    uint64_t q = sk_rt_000dbdf4();
    sk_rt_0034cfd4(q);
    uint64_t ok = sk_rt_0034cfd4();
    if ((ok & 1) != 0) {
        /* vtable +0x20 body op with +8 release */
        sk_rt_00350088();
        sk_rt_00351118();
        sk_rt_00351990();
        sk_rt_0034fd8c();
        sk_rt_003516a8();
        sk_rt_0034fd8c();
        sk_rt_003595d8();
        sk_rt_00350c38();
        sk_rt_000026e8();
        sk_rt_0035056c();
        return;
    }
    sk_rt_00348730();
    uint64_t e = *(uint64_t *)(l + 0x18);
    uint64_t v2 = *(uint64_t *)(l + 0x20);
    sk_rt_0034e1ec();
    sk_rt_0017e880(v2);
    uint64_t sv2 = sk_rt_00350a88();
    sk_rt_0006e778(0x48);
    cl4_result_t b0 = sk_rt_00351e08();
    cl4_result_t rv = sk_rt_0034f958();
    sk_rt_0034a274();
    /* four Optional-validation stages */
    cl4_result_t s1 = sk_rt_00208418(fn, 0);
    sk_rt_0034d044();
    sk_rt_003a25d4();
    /* ... continue accumulate stages ... */
    cl4_result_t s2 = sk_rt_001a89a8();
    sk_rt_0034bf64();
    sk_rt_003a25d4();
    sk_rt_00359cd8();
    sk_rt_00350b78();
    sk_rt_001b1780();
    sk_rt_00350b78();
    sk_rt_001a89a8();
    sk_rt_003562e0();
    uint64_t vv = sk_rt_00349cbc();
    sk_rt_0034c6e4();
    /* stage-4 accumulation */
    sk_rt_003508fc();
    sk_rt_001b1780();
    sk_rt_003508fc();
    sk_rt_0034b178();
    sk_rt_001a89a8();
    sk_rt_00358f84();
    uint64_t vv2 = sk_rt_00349cbc();
    sk_rt_0034c6e4();
    /* store result {value, fn, count, 0, kind=3} */
    sk_rt_0036986c();
    sk_rt_000026e8();
    sk_rt_000026e8(l);
    sk_rt_00358490();
    sk_rt_00353d14(r);
}

/* ===================================================================== */
/* Remaining string / collection ops (3)                                 */
/* ===================================================================== */

/* FUN_0026cdec @ 0x0026cdec   (est. sk_range_validate)
 * Ghidra: void FUN_0026cdec(undefined8 param_1, undefined8 param_2, long param_3, ulong param_4)
 * Validates a Range's lower/upper bound relationship: locks the collection,
 * copies both endpoint values through the metadata, runs the closure compare
 * (FUN_00310e20), and raises the fatal lowerBound<upperBound trap on failure.
 * Confidence: medium
 * Notes: FUN_00377824/FUN_00377bec lock pair; fatal FUN_001afe4c. */
void sk_range_validate(uint64_t a, uint64_t b, uint64_t rng, uint64_t flags)
{
    uint64_t meta = *(uint64_t *)((flags & 0xfffffffffffffffe) - 8);
    uint64_t base = *(uint64_t *)(rng + 0x10);
    uint64_t obj = sk_rt_00377824(0, meta, base, 0x612294, 0x6122b4);
    uint64_t o = *(uint64_t *)(obj - 8);
    sk_rt_0036a908(*(uint64_t *)(o + 0x40) + 0xf, 0);
    sk_rt_00377bec(meta, base, obj, 0x612294, 0x6122ac);
    sk_rt_00027754();
    uint64_t cpu = sk_rt_0008f6f4();
    uint64_t obj2 = sk_rt_00377824(0, cpu, obj, 0x60e3fc, 0x60e40c);
    sk_rt_0036a908(*(uint64_t *)(*(uint64_t *)(obj2 - 8) + 0x40) + 0xf, 0);
    uint64_t r = sk_rt_003722e4(0, base, base, 0x5e1f90, 0);
    uint64_t rr = *(uint64_t *)(r - 8);
    sk_rt_0036a908(*(uint64_t *)(rr + 0x40));
    uint64_t base2 = *(uint64_t *)(base - 8);
    sk_rt_0036a908(*(uint64_t *)(base2 + 0x40));
    uint64_t rng2 = *(uint64_t *)(rng - 8);
    sk_rt_0036a908(*(uint64_t *)(rng2 + 0x40));
    sk_rt_0026c274();
    sk_rt_0026c2a0();
    uint64_t meta2 = sk_rt_00027754(meta);
    uint64_t cmp = sk_rt_00310e20();
    uint64_t ok = cmp;
    if ((ok & 1) != 0) {
        /* both endpoints valid: copy them, then run the +0x10/+0x20 view ops */
        sk_rt_0026cbd0();
        sk_rt_0026cbd0();
        sk_rt_00310e08();
        sk_rt_001d2df0();
        sk_rt_00377bec(cpu, obj, obj2, 0x60e3fc, 0x60e404);
        sk_rt_00310ca4();
        sk_rt_00310ca4();
        sk_rt_00310ca4();
        return;
    }
    /* fatal: Range requires lowerBound < upperBound */
    sk_rt_001afe4c(0x5accd0, 0xb, 2, 0x5cda00, 0x27, 2, 0x5cda30, 0x11);
}

/* FUN_0026fe90 @ 0x0026fe90   (est. sk_collection_iterate)
 * Ghidra: void FUN_0026fe90(void)
 * Iterates a collection's elements: opens the collection view, walks each
 * element dispatching the +0x20 vtable body op, and tears down.
 * Confidence: low
 * Notes: FUN_00352798/FUN_00349b3c view init; fatal FUN_001afe4c. */
void sk_collection_iterate(void)
{
    sk_rt_00353cfc();
    sk_rt_00352798();
    sk_rt_00349b3c();
    sk_rt_0036a908();
    sk_rt_003497b4();
    sk_rt_00350908();
    sk_rt_00348cd0();
    sk_rt_0036a908();
    sk_rt_00348a34();
    sk_rt_0034c2d8();
    sk_rt_003508fc();
    sk_rt_0034f1a8();
    sk_rt_00352680();
    sk_rt_000a6e14();
    if (0 /* x21 */ == 0) {
        sk_rt_000836a4();
        sk_rt_0035159c();
        sk_rt_0031a1ac();
        sk_rt_00352e6c();
        /* vtable +0x20 body op */
        sk_rt_00350bf0();
        sk_rt_000026e8();
        sk_rt_00352370();
    }
    sk_rt_000026e8();
    sk_rt_00353e7c();
    sk_rt_00353d14();
}

/* FUN_0026e490 @ 0x0026e490   (est. sk_string_concat_optional)
 * Ghidra: void FUN_0026e490(void)
 * Chained Optional String concatenation with per-stage nil validation: each
 * stage coerces a nil (0xe000000000000000) tag and accumulates the scalar
 * into the result buffer. Traps on overflow (ValidUTF8Buffer 0xa7).
 * Confidence: low
 * Notes: many FUN_0034xxxx runtime ops; nil tag handling. */
void sk_string_concat_optional(void)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    uint64_t v = *(uint64_t *)(cpu + 0x10);
    sk_rt_003499f0();
    sk_rt_0036a908();
    sk_rt_00349068();
    cl4_result_t r1 = sk_rt_00106e3c();
    sk_rt_001a89a8(r1.lo, r1.hi, 1);
    sk_rt_00351e08();
    sk_rt_003a25d4(0xe000000000000000ull);
    sk_rt_003511d8();
    sk_rt_0035084c();
    cl4_result_t r2 = sk_rt_001c050c();
    sk_rt_0034a274();
    /* stage-1 nil check */
    sk_rt_003a25d4();
    /* stage-2 */
    cl4_result_t r3 = sk_rt_001a89a8();
    sk_rt_003a25d4(0xe000000000000000ull);
    sk_rt_00351f28();
    sk_rt_0034b824();
    /* stage-3 */
    cl4_result_t r4 = sk_rt_001a89a8();
    sk_rt_00354ddc();
    sk_rt_0034a900();
    /* stage-4 */
    sk_rt_0034b178();
    sk_rt_001a89a8();
    sk_rt_0034bd90();
    sk_rt_003a25d4();
    cl4_result_t r5 = sk_rt_0006b6f4();
    sk_rt_0008e500(r5.lo, r5.hi);
}

/* ===================================================================== */
/* Remaining string / collection ops (4)                                 */
/* ===================================================================== */

/* FUN_00275100 @ 0x00275100   (est. sk_string_transform3)
 * Ghidra: void FUN_00275100(undefined8 param_1, ... param_6)
 * Range transform over a string with per-scalar closure: iterates the scalar
 * endpoints, applies the closure (FUN_00310e20 predicate + view vtable ops),
 * and accumulates results. On an empty/negative range it reports and traps.
 * Confidence: low
 * Notes: fatal FUN_001afe4c on the failure path. */
void sk_string_transform3(uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_003542d0();
    sk_rt_00351ef8(c);
    sk_rt_0034c158();
    sk_rt_00350f4c();
    sk_rt_00377824();
    uint64_t r = sk_rt_0034a654();
    sk_rt_000a6f88();
    sk_rt_0036a908();
    sk_rt_003493c4();
    sk_rt_0034c2f8();
    sk_rt_0034bc6c();
    sk_rt_0034e6bc();
    sk_rt_00377bec();
    sk_rt_0034d734();
    sk_rt_00310e08();
    uint64_t r2 = sk_rt_000a6f88();
    sk_rt_0007c1a4();
    sk_rt_0034a2ac();
    sk_rt_00350500();
    sk_rt_00310d68();
    uint64_t r3 = sk_rt_000a6f88();
    sk_rt_0007c1a4();
    sk_rt_0034af20();
    sk_rt_0034998c();
    sk_rt_0036a908();
    sk_rt_00348abc();
    sk_rt_0034a120();
    sk_rt_0034b8bc();
    if (0 /* x20 == 0 */) {
        sk_rt_0008e500();
        return;
    }
    if (0 /* x20 < 0 */) {
        sk_rt_0034b348();
        sk_rt_0034951c();
        sk_rt_00358918();
        sk_rt_0034a69c();
    } else {
        sk_rt_0031d738(d);
        sk_rt_00350a88();
        sk_rt_00351420();
        uint64_t ok = sk_rt_00310e20();
        if ((ok & 1) != 0) {
            sk_rt_0008e500();
            return;
        }
        sk_rt_00310924();
        sk_rt_00350c50();
        sk_rt_00350a04();
        sk_rt_000277b8();
        sk_rt_00350b30();
        sk_rt_00350a04();
        sk_rt_003195f8(c);
        sk_rt_00351184();
        sk_rt_00351384();
        sk_rt_00351cd0();
        sk_rt_00351274();
        uint64_t q = sk_rt_0034b2a8();
        if (0 /* !in_ZR */) {
            /* vtable +0x20 body op with +8 release */
            sk_rt_00350ea4();
            sk_rt_00355cb0();
            sk_rt_00310e20();
            sk_rt_0034db88();
            sk_rt_003516b4();
            uint64_t ok2 = sk_rt_0034db88();
            if ((ok2 & 1) != 0) {
                sk_rt_00350ab8();
                sk_rt_0035a49c();
                sk_rt_00350b48();
                sk_rt_00352474();
                sk_rt_0035169c();
                sk_rt_00350b48();
                sk_rt_0035169c();
                sk_rt_00350518();
                sk_rt_00355604();
                sk_rt_0031d488();
                uint64_t sv = sk_rt_00350804();
                sk_rt_0035336c();
                sk_rt_000b4390();
                sk_rt_0008e500();
                return;
            }
            sk_rt_00347d60();
        } else {
            sk_rt_00351e6c(q, r3);
            sk_rt_00348b7c(f);
            sk_rt_0035863c();
            sk_rt_0034a69c();
        }
    }
    sk_rt_00353f14();
    sk_rt_001afe4c();
}

/* FUN_002734e4 @ 0x002734e4   (est. sk_string_transform4)
 * Ghidra: void FUN_002734e4(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Range transform with closure and Optional result handling: after the object
 * setup, iterates the endpoints applying the closure; on the success path
 * stores the transformed value via the vtable; on failure reports + traps.
 * Confidence: low
 * Notes: fatal FUN_001afe4c. */
void sk_string_transform4(uint64_t a, uint64_t b, uint64_t c)
{
    cl4_result_t md = sk_rt_0008e518();
    sk_rt_00351ad4(c);
    sk_rt_0034d574();
    sk_rt_00352840(0xff);
    uint64_t k = sk_rt_00377824();
    cl4_result_t md2 = sk_rt_0034b0b4();
    sk_rt_00353534();
    sk_rt_003722e4();
    sk_rt_00348d4c();
    sk_rt_0036a908();
    sk_rt_00348bbc();
    sk_rt_00350464();
    sk_rt_0034911c();
    sk_rt_0007c1a4();
    sk_rt_00350428();
    sk_rt_00358978();
    sk_rt_00350a04();
    sk_rt_00350a1c();
    uint64_t v = sk_rt_00377bec();
    cl4_result_t md3 = sk_rt_003504e8();
    sk_rt_00310e08(md3.lo, md3.hi, v);
    sk_rt_00348ce8();
    sk_rt_0007c1a4();
    sk_rt_0034b6f4();
    sk_rt_00356000();
    sk_rt_00350914();
    uint64_t ok = sk_rt_00350914();
    if ((ok & 1) == 0) {
        sk_rt_00351b84();
        sk_rt_00350b84();
        cl4_result_t c1 = sk_rt_00348b94();
        uint64_t v2 = md.hi;
        sk_rt_00377824();
        sk_rt_00349530();
        sk_rt_0034cfa4();
        sk_rt_00353d94();
        sk_rt_00352d28();
        sk_rt_00351dfc();
        sk_rt_00310e20(v);
        sk_rt_0034d394();
        sk_rt_00350ac4();
        uint64_t ok2 = sk_rt_00350ac4();
        if ((ok2 & 1) != 0) {
            uint64_t t = sk_rt_00352468();
            /* vtable +0x20 body op */
            sk_rt_00351554();
            sk_rt_00351c4c();
            sk_rt_0034db48();
            sk_rt_00350768();
            sk_rt_0034db48();
            sk_rt_00350524();
            sk_rt_00319248(c);
            uint64_t sv = sk_rt_00351894();
            sv = sk_rt_00319230(sv, v2);
            uint64_t v3 = sk_rt_00348d18();
            cl4_result_t out = sk_rt_00376820(v3, sv);
            sk_rt_00354324();
            sk_rt_00351384();
            sk_rt_0008e500();
            return;
        }
        sk_rt_00347d60();
    } else {
        sk_rt_00350410();
        sk_rt_003488bc();
        sk_rt_0034a69c();
        sk_rt_00353f14();
    }
    sk_rt_001afe4c();
}

/* FUN_00272520 @ 0x00272520   (est. sk_string_transform5)
 * Ghidra: void FUN_00272520(undefined8 param_1, undefined8 param_2, long param_3, undefined8 param_4)
 * Range transform with scalar dispatch (param_4): locks the object, iterates
 * the endpoints dispatching the +0x20 view op, and stores the result.
 * Confidence: low
 * Notes: fatal FUN_001afe4c on the failure path. */
void sk_string_transform5(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    cl4_result_t md = sk_rt_0008e518();
    sk_rt_00350950(d);
    sk_rt_00348f14();
    sk_rt_00377824(0xff, 0, c);
    sk_rt_00352efc();
    uint64_t q = sk_rt_00319218();
    sk_rt_0034ab20();
    sk_rt_0007c1a4();
    sk_rt_0034b6e0();
    sk_rt_0034d574();
    sk_rt_00351178(0xff);
    uint64_t k = sk_rt_00377824();
    cl4_result_t md2 = sk_rt_0034b0b4();
    sk_rt_003579d8();
    sk_rt_00348d64();
    sk_rt_0036a908();
    sk_rt_0034ab10();
    sk_rt_0034dfa4();
    sk_rt_0034b87c();
    uint64_t v = sk_rt_0035705c();
    sk_rt_00351100(v, c);
    uint64_t v2 = sk_rt_00377bec();
    sk_rt_0034e0d4();
    sk_rt_00310e08();
    sk_rt_00348e00();
    sk_rt_0007c1a4();
    sk_rt_0034b05c();
    uint64_t e = sk_rt_00310e20(v2);
    sk_rt_00350a40();
    sk_rt_00351100(e, md.hi);
    uint64_t ok = sk_rt_00350a40();
    if ((ok & 1) != 0) {
        /* vtable +0x10/+0x20/+8 body ops */
        sk_rt_00349b00();
        sk_rt_00359e40();
        sk_rt_00353214();
        sk_rt_003534bc();
        sk_rt_003508fc();
        cl4_result_t v3 = sk_rt_0035060c();
        sk_rt_003508fc();
        sk_rt_003556f4();
        sk_rt_0009461c();
        sk_rt_0034b07c();
        sk_rt_003578a8();
        uint64_t p = sk_rt_00319248();
        uint64_t w = sk_rt_00349204();
        sk_rt_00376820(w);
        cl4_result_t v4 = sk_rt_003504f4();
        sk_rt_0035313c();
        sk_rt_00351274();
        sk_rt_0008e500();
        return;
    }
    sk_rt_00347d60();
    sk_rt_001afe4c();
}

/* ===================================================================== */
/* Remaining string / collection ops (5)                                 */
/* ===================================================================== */

/* FUN_00276034 @ 0x00276034   (est. sk_collection_iterate_cl)
 * Ghidra: void FUN_00276034(void)
 * Iterates a collection through the closure FUN_00353cfc / FUN_000a68f4
 * loop: for each element, dispatches the body op and checks the error flag
 * (x21); on error tears down and returns, else continues until exhausted.
 * Confidence: low
 * Notes: closure loop via FUN_0031b1780; body op vtable +0x20. */
void sk_collection_iterate_cl(void)
{
    uint64_t cpu = sk_rt_00353cfc().lo;
    sk_rt_00354b2c();
    sk_rt_00027754();
    sk_rt_00351ad4();
    sk_rt_003508e4();
    sk_rt_00351c58();
    sk_rt_00377824();
    sk_rt_00348cd0();
    sk_rt_0007c1a4();
    sk_rt_0034af20();
    sk_rt_00350920();
    sk_rt_0034d464();
    sk_rt_0007c1a4();
    sk_rt_0034b460();
    sk_rt_00350308();
    sk_rt_00377824();
    sk_rt_00348d7c();
    sk_rt_0007c1a4();
    sk_rt_0034aee4();
    sk_rt_0031e0d4();
    sk_rt_00350c14();
    sk_rt_003567b0();
    sk_rt_000a68c4();
    sk_rt_00350b24();
    sk_rt_00350470();
    sk_rt_0034b278();
    sk_rt_00377bec();
    void *step = (void *)sk_rt_000a68f4();
    do {
        sk_rt_0034ed38();
        cl4_result_t el = sk_rt_00351bac();
        sk_rt_00350884(el.lo, el.hi);
        if (0 /* in_ZR */) {
            sk_rt_00354364();
            sk_rt_000e72b0();
            sk_rt_00351348();
            sk_rt_00353d14();
            return;
        }
        cl4_result_t el2 = sk_rt_00350b00();
        uint64_t ok = sk_rt_00353cfc().lo;
        if (0 /* x21 */ != 0) {
            sk_rt_003578b4();
            sk_rt_003509b0();
            sk_rt_00354364();
            sk_rt_000e72b0();
            break;
        }
        if ((ok & 1) == 0) {
            sk_rt_003578b4();
            sk_rt_003509b0();
        } else {
            sk_rt_003543b8();
            sk_rt_0016de38();
            uint64_t v = sk_rt_00350a7c();
            sk_rt_00310e20(v);
        }
    } while (true);
}

/* FUN_00274bfc @ 0x00274bfc   (est. sk_string_replace_subrange)
 * Ghidra: void FUN_00274bfc(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * replaceSubrange: locks the string, removes the given subrange, inserts the
 * replacement, and returns; empty/error paths report + trap.
 * Confidence: low
 * Notes: fatal FUN_001afe4c on the failure path. */
void sk_string_replace_subrange(uint64_t a, uint64_t b, uint64_t c)
{
    cl4_result_t md = sk_rt_0008e518();
    sk_rt_00351ef8(md.hi);
    sk_rt_00349748();
    sk_rt_000dbf08();
    sk_rt_00377824();
    sk_rt_00348d7c();
    sk_rt_0036a908();
    sk_rt_00348bd8();
    sk_rt_0034bc80();
    sk_rt_00348f14();
    sk_rt_00377824(0xff, 0, md.lo);
    sk_rt_0034e67c();
    sk_rt_00310d68();
    sk_rt_00348e18();
    sk_rt_0007c1a4();
    sk_rt_0034b2f8();
    sk_rt_0034a5c8();
    sk_rt_0007c1a4();
    sk_rt_0034af20();
    sk_rt_003192a8();
    sk_rt_000dbdf4();
    uint64_t ok = sk_rt_003192a8();
    if ((ok & 1) != 0) {
        sk_rt_00350744();
        sk_rt_0008e500();
        sk_rt_000839d8();
        return;
    }
    sk_rt_0031d6d8(c);
    uint64_t v = sk_rt_00350390();
    sk_rt_0034f044();
    if (0 /* in_ZR */) {
        sk_rt_0034eb94();
        sk_rt_00351750();
        sk_rt_00358630();
        sk_rt_00350c80();
        sk_rt_0031e104(md.hi);
        sk_rt_0035036c();
        sk_rt_0034ce78();
        sk_rt_00353b94();
        sk_rt_0031d708();
        sk_rt_0035319c();
        sk_rt_003505c4();
        sk_rt_00350a34();
    } else {
        sk_rt_00351414();
        sk_rt_00352498();
    }
    sk_rt_00350750();
    sk_rt_000839d8();
    sk_rt_0008e500();
}

/* FUN_00274e88 @ 0x00274e88   (est. sk_string_replace_subrange2)
 * Ghidra: void FUN_00274e88(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * replaceSubrange variant (mirrors FUN_00274bfc).
 * Confidence: low
 * Notes: fatal FUN_001afe4c on the failure path. */
void sk_string_replace_subrange2(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    cl4_result_t md = sk_rt_0008e518();
    sk_rt_00351ad4(md.hi);
    sk_rt_00349748();
    sk_rt_00351420();
    sk_rt_00377824();
    sk_rt_00348fd8();
    sk_rt_0036a908();
    sk_rt_00348bd8();
    sk_rt_0034bc80();
    sk_rt_00348f14();
    sk_rt_00377824(0xff, 0, md.lo);
    sk_rt_0034da88();
    sk_rt_00310d68();
    sk_rt_00348d64();
    sk_rt_0007c1a4();
    sk_rt_003494b4();
    sk_rt_0007c1a4();
    sk_rt_0034b0d4();
    sk_rt_003192a8();
    sk_rt_000dbdf4();
    uint64_t ok = sk_rt_003192a8();
    if ((ok & 1) == 0) {
        sk_rt_0031d6d8(c);
        uint64_t v = sk_rt_0034f644();
        sk_rt_00349f3c();
        if (0 /* in_ZR */) {
            sk_rt_0034ded4();
            sk_rt_00351750();
            sk_rt_00358630();
            sk_rt_00350b78();
            sk_rt_00354930(md.hi);
            sk_rt_0034ce78();
            sk_rt_003559d8();
            sk_rt_0031d708();
            sk_rt_003548e8();
            sk_rt_00077894();
            sk_rt_00351274();
        } else {
            sk_rt_003508c0();
            sk_rt_00351554();
        }
        sk_rt_0008e500();
        return;
    }
    sk_rt_0034b348();
    sk_rt_00348b7c(d);
    sk_rt_0034a69c();
    sk_rt_00353f14();
    sk_rt_001afe4c();
}

/* FUN_00276950 @ 0x00276950   (est. sk_collection_reduce)
 * Ghidra: void FUN_00276950(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * reduce over a collection: locks the object, initializes the accumulator,
 * iterates each element applying the combine closure (FUN_001fe95c /
 * FUN_0031b71c), and stores the final accumulator.
 * Confidence: low
 * Notes: FUN_00377824/FUN_00377bec lock pair; FUN_0036b118 release. */
void sk_collection_reduce(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_003504d0();
    sk_rt_00350950(c);
    sk_rt_0034bec4();
    uint64_t k = sk_rt_00377824();
    sk_rt_0034ab20();
    sk_rt_0007c1a4();
    sk_rt_0034b0d4();
    sk_rt_003504a0(0xff);
    uint64_t k2 = sk_rt_00377824();
    sk_rt_00084180();
    sk_rt_0035433c();
    uint64_t v = sk_rt_00377bec();
    cl4_result_t md = sk_rt_0035113c();
    sk_rt_00310e08(md.lo, md.hi, v);
    sk_rt_00348d4c();
    sk_rt_0007c1a4();
    sk_rt_0034924c();
    sk_rt_0036a908();
    sk_rt_003497b4();
    sk_rt_00351c10();
    cl4_result_t acc = sk_rt_00352498();
    uint64_t ok = sk_rt_001fe95c(acc.lo, acc.hi, v);
    if ((ok & 1) == 0) {
        sk_rt_003512c0();
        sk_rt_003513c0();
        uint64_t coll = sk_rt_00203b08();
        sk_rt_00352c8c();
        sk_rt_0031e0d4();
        sk_rt_0034ba08();
        if (*(uint64_t *)(coll + 0x10) != 0) {
            uint64_t (*get)(void) = (uint64_t (*)(void))sk_rt_00319628();
            uint64_t (*step)(void) = (uint64_t (*)(void))sk_rt_0031d678(c);
            do {
                cl4_result_t el = sk_rt_0006b6f4();
                sk_rt_001fea40(el.lo, el.hi, k2, v);
                sk_rt_0034d8e4();
                uint64_t q = sk_rt_0031b71c();
                uint64_t w = sk_rt_00348a50();
                sk_rt_00376820(w, q);
                sk_rt_0034887c();
                uint64_t z = sk_rt_00355958();
                sk_rt_001e7664(z, q);
                sk_rt_00353190();
                uint64_t e2 = sk_rt_00352fe8();
                sk_rt_003511c0();
                sk_rt_00377bec();
                sk_rt_003549c0();
            } while (*(uint64_t *)(coll + 0x10) != 0);
        }
        sk_rt_0035092c();
        sk_rt_0036b118(coll);
        sk_rt_00356ae8();
    }
    sk_rt_0008e500();
}

/* ===================================================================== */
/* Remaining string / collection ops (6) — largest                       */
/* ===================================================================== */

/* FUN_00276c34 @ 0x00276c34   (est. sk_collection_sort)
 * Ghidra: void FUN_00276c34(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Sorts a collection of elements: locks the object, builds a comparison
 * context, runs an in-place sort loop over the element buffer (partition /
 * merge with the vtable comparator at +0x10), and stores the sorted range.
 * Confidence: low
 * Notes: large Swift runtime sort; comparator vtable +0x10; FUN_0036b118
 *   releases; FUN_001afe4c trap on the failure path. */
void sk_collection_sort(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_00352758();
    sk_rt_00351bec(c);
    sk_rt_0034de64();
    sk_rt_00350c08(0xff);
    sk_rt_00377824();
    uint64_t r = sk_rt_0034a654();
    sk_rt_003490b8();
    sk_rt_0036a908();
    sk_rt_003493c4();
    sk_rt_0034acf0();
    sk_rt_00350464();
    sk_rt_00355f40();
    sk_rt_00349618();
    sk_rt_0036a908();
    sk_rt_003493c4();
    sk_rt_0034acf0();
    sk_rt_00350434();
    sk_rt_0034acf0();
    sk_rt_0034b640();
    sk_rt_00349c84();
    sk_rt_00350434();
    sk_rt_0034acf0();
    sk_rt_0034ba68();
    sk_rt_0034ee48();
    uint64_t k = sk_rt_00377bec();
    sk_rt_0035119c(0xff);
    sk_rt_00310e08();
    sk_rt_0034e67c();
    uint64_t v = sk_rt_00310d68();
    sk_rt_000a6f88();
    sk_rt_0007c1a4();
    sk_rt_0034b05c();
    sk_rt_0034a5c8();
    sk_rt_0036a908();
    sk_rt_003493c4();
    sk_rt_0034acf0();
    sk_rt_0034a400();
    sk_rt_0034aac4();
    sk_rt_0034b4c0();
    sk_rt_0036b270();
    cl4_result_t md = sk_rt_00350500();
    uint64_t ctx = sk_rt_0031b71c(md.lo, md.hi, k);
    uint64_t w = sk_rt_00348c30();
    sk_rt_00376820(w, ctx);
    sk_rt_00358e7c();
    sk_rt_00352d34();
    sk_rt_001aeab4();
    sk_rt_0034f044();
    if (0 /* in_ZR */) {
        uint64_t x = sk_rt_00351c28();
        sk_rt_0036b118();
    } else {
        sk_rt_00350b3c();
        sk_rt_00352b98();
        sk_rt_00356768();
        uint64_t (*cmp)(void);
        __builtin_memcpy(&cmp, (void *)(ctx + 0x10), sizeof(cmp));
        sk_rt_00350944();
        uint64_t c0 = cmp();
        sk_rt_00355100();
        sk_rt_001bbfdc();
        cl4_result_t md2 = sk_rt_00350720();
        void *get = (void *)sk_rt_0031b080(md2.lo, md2.hi);
        sk_rt_0021867c();
        /* in-place sort loop */
        while (true) {
            sk_rt_0022b584();
            if (0 /* local_28 == local_40[0] */) break;
            sk_rt_001ff258();
            sk_rt_00355634();
            sk_rt_0028cba8();
            sk_rt_00351554();
            sk_rt_00353734();
            sk_rt_00354b74();
            sk_rt_00350ed0();
            sk_rt_00350780(k);
            uint64_t (*step)(void) = (uint64_t (*)(void))sk_rt_0014ae44();
            sk_rt_000a6e14();
            sk_rt_003516b4();
            uint64_t done = step();
            if ((done & 1) == 0) {
                uint64_t (*get2)(void) = (uint64_t (*)(void))sk_rt_0031b194(c);
                void *put = (void *)sk_rt_00027818();
                do {
                    sk_rt_00350738();
                    sk_rt_0034ee48();
                    sk_rt_003505c4();
                    sk_rt_003512cc();
                    done = step();
                } while ((done & 1) == 0);
            }
            sk_rt_00350618();
            sk_rt_00100c38();
            cl4_result_t e3 = sk_rt_00352ba4();
            sk_rt_00354d50();
            sk_rt_0007c1c4();
            sk_rt_00357368();
        }
        sk_rt_00358ac8();
        sk_rt_0036b118();
        uint64_t (*get3)(void) = (uint64_t (*)(void))sk_rt_00310924();
        sk_rt_00027754(k);
        uint64_t (*step2)(void) = (uint64_t (*)(void))sk_rt_0014ae44();
        while (true) {
            sk_rt_00350bf0();
            sk_rt_00100c38();
            sk_rt_003516b4();
            uint64_t done = step2();
            sk_rt_00350518();
            if ((done & 1) != 0) break;
            sk_rt_003537f0();
            uint64_t x = sk_rt_0031b194();
            sk_rt_00350914(x);
            sk_rt_003515fc();
            void *put2 = (void *)sk_rt_00027818();
            cl4_result_t e4 = sk_rt_003508b4();
            cl4_result_t e5 = sk_rt_0035084c();
        }
        sk_rt_00352c98();
        sk_rt_00350810();
        sk_rt_00354618();
        sk_rt_00350bf0();
        sk_rt_00310e20(k);
        sk_rt_0034e61c();
        sk_rt_00350bfc();
        uint64_t ok = sk_rt_00350bfc();
        if ((ok & 1) == 0) {
            sk_rt_00347d60();
            sk_rt_001afe4c();
        }
        sk_rt_00084174();
        sk_rt_00354d50();
        sk_rt_00356768();
        cl4_result_t md3 = sk_rt_000dbd0c();
        sk_rt_003516f0();
        sk_rt_00351c4c();
        cl4_result_t e6 = sk_rt_00100c38();
        sk_rt_00355ea4();
        cl4_result_t e7 = sk_rt_00351130();
        cl4_result_t e8 = sk_rt_00100c38();
        sk_rt_000e72b0();
        sk_rt_00352698();
        sk_rt_0031d488();
        uint64_t sv = sk_rt_00350804();
        sk_rt_00350c2c();
    }
    sk_rt_0008e500();
}

/* FUN_002775c8 @ 0x002775c8   (est. sk_collection_sort_merge)
 * Ghidra: void FUN_002775c8(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Merge step of the sort: builds the merge context, runs the merge loop
 * comparing elements via the vtable comparator and copying runs, with
 * SoftwareBreakpoint traps on the size-overflow checks. Returns the merged
 * result through the epilogue helper.
 * Confidence: low
 * Notes: SoftwareBreakpoint(1, 0x277b90/0x277b94/0x277b98) overflow traps;
 *   FUN_0019e578/FUN_0019f410 merge context; FUN_001dc430 element copy. */
void sk_collection_sort_merge(uint64_t a, uint64_t b, uint64_t c)
{
    uint64_t cpu = sk_rt_0008e518().lo;
    sk_rt_00354de8();
    sk_rt_00349b3c();
    sk_rt_0036a908();
    sk_rt_003493c4();
    sk_rt_0034acf0();
    sk_rt_0034baa8();
    sk_rt_0034ea54();
    sk_rt_00310e08(0);
    sk_rt_00348cd0();
    sk_rt_0036a908();
    sk_rt_003493c4();
    sk_rt_0034acf0();
    sk_rt_00350464();
    sk_rt_00350920();
    cl4_result_t md = sk_rt_00310d34();
    sk_rt_0034921c(md.lo, md.hi, md.lo);
    uint64_t ctx = sk_rt_0019e578();
    sk_rt_00350920();
    uint64_t v1 = sk_rt_00310d80();
    uint64_t v2 = sk_rt_00349910();
    sk_rt_00376820(v2, v1);
    uint64_t v3 = sk_rt_0034e4b4();
    sk_rt_00376820(v3, v1);
    sk_rt_00351b2c();
    sk_rt_0027b41c();
    uint64_t v4 = sk_rt_00349234();
    sk_rt_00376820(v4, v1);
    uint64_t v5 = sk_rt_0035a4e0();
    sk_rt_001d80e0(v5, 0, v1);
    if (0 /* local_28 == 1 */) {
        sk_rt_00350920();
        sk_rt_001a0414();
        sk_rt_001dd1ec();
        sk_rt_0036b118(ctx);
    } else {
        uint64_t base = sk_rt_00310e20();
        uint64_t nb = base + 1;
        if (0 /* SCARRY8 */) {
            sk_rt_00351b2c();
        }
        uint64_t n = *(uint64_t *)(ctx + 0x10);
        uint64_t cnt = 0;
        if (nb < n) {
            uint64_t i = 0;
            sk_rt_00352bbc();
            sk_rt_00355f40();
            sk_rt_00358948();
            sk_rt_00359568();
            do {
                cl4_result_t e = sk_rt_0034ffb8();
                sk_rt_001dc430(e.lo, e.hi);
                uint64_t r = sk_rt_001e3048();
                sk_rt_00350c80();
                if ((r & 1) == 0) {
                    sk_rt_00350ba8();
                    sk_rt_001dc430();
                    sk_rt_00351148();
                    sk_rt_00350c80();
                    sk_rt_00350ba8();
                    sk_rt_001dc430();
                    sk_rt_003567a4();
                    cl4_result_t e2 = sk_rt_000e15d8();
                    sk_rt_00352d70(c);
                    sk_rt_0034c344();
                    uint64_t ok = sk_rt_00310e20();
                    sk_rt_00354b68();
                    sk_rt_003509bc();
                    sk_rt_00351ec0();
                    if ((ok & 1) == 0) {
                        cnt = cnt + 1;
                        if (0 /* SCARRY8 */) {
                            sk_rt_003515d8();
                        }
                        sk_rt_0019f410();
                        sk_rt_00358948();
                    } else {
                        sk_rt_003515d8();
                        uint64_t w = sk_rt_001dc430();
                        sk_rt_003548a0(w);
                        sk_rt_00353130();
                        sk_rt_003509e0();
                        sk_rt_003519b4();
                        sk_rt_003515d8();
                        uint64_t w2 = sk_rt_001dc430();
                        cl4_result_t e3 = sk_rt_00353dac();
                        sk_rt_003508f0();
                        cl4_result_t e4 = sk_rt_00350bf0();
                        sk_rt_0019b25c(e4.lo, e4.hi, r, c);
                        sk_rt_00351e90();
                        sk_rt_003509bc();
                        uint64_t w3 = sk_rt_00356964();
                        sk_rt_001dc430(w3, ctx);
                        cl4_result_t e5 = sk_rt_00350c80();
                        sk_rt_003508f0();
                        sk_rt_00355430();
                        uint64_t z = sk_rt_00353190();
                        sk_rt_0035053c(z);
                        sk_rt_0026bdc4();
                        sk_rt_00352d64();
                        cl4_result_t e6 = sk_rt_00350524();
                        sk_rt_0019e728(e6.lo, e6.hi);
                        sk_rt_00357c20();
                        sk_rt_00351178();
                    }
                }
                nb = nb + 1;
                n = *(uint64_t *)(ctx + 0x10);
            } while (nb < n);
        }
        if (0 /* SCARRY8(cnt,1) */) {
            sk_rt_003515d8();
        }
        if (n < cnt + 1) {
            sk_rt_00347d60();
            sk_rt_001afe4c();
        }
        uint64_t w = sk_rt_0034b5fc();
        sk_rt_00376820(w);
        sk_rt_001a4d84();
    }
    uint64_t out = sk_rt_00353100();
    sk_rt_0008e500(out);
}

/* FUN_0026cd08 @ 0x0026cd08   (est. sk_runtime_range_alloc)
 * Ghidra: undefined1 [16] FUN_0026cd08(long *param_1, undefined8 param_2, long param_3, undefined8 param_4)
 * Builds a Range/Collection object: records the collection base and its
 * metadata header in out[0..1], allocates a fresh runtime instance sized by
 * the type's allocation field, and initializes it via the shared allocator
 * init. Returns {type-info, instance} as a 16-byte register pair.
 * Confidence: medium
 * Notes: alloc FUN_0036a908; init FUN_0026cbd0; result tag DAT_003471a8. */
cl4_result_t sk_runtime_range_alloc(uint64_t *out, uint64_t arg2, uint64_t type_desc, uint64_t arg4)
{
    uint64_t base = *(uint64_t *)(type_desc + 0x10);
    out[0] = base;
    base = *(uint64_t *)(base - 8);
    out[1] = base;
    base = sk_rt_0036a908(*(uint64_t *)(base + 0x40), 0);
    out[2] = base;
    sk_rt_0026cbd0(base, arg2, type_desc, arg4);
    return (cl4_result_t){ .lo = (uint64_t)0x3471a8, .hi = base };
}

/* FUN_00277520 @ 0x00277520   (est. sk_collection_sort_entry)
 * Ghidra: undefined8 FUN_00277520(void)
 * Entry point of the collection sort: builds the sort context from the
 * current CPU metadata, and either runs the full sort (via FUN_002775c8) or,
 * when the context already matches, returns the pre-sorted value.
 * Confidence: low
 * Notes: FUN_0031b71c context; FUN_002775c8 sort; FUN_0036b270 alloc. */
uint64_t sk_collection_sort_entry(void)
{
    sk_rt_003531d8();
    cl4_result_t md = sk_rt_003517b4();
    uint64_t ctx = sk_rt_0031b71c(md.lo, md.hi);
    if (0 /* x19 != ctx */) {
        sk_rt_00351238();
        sk_rt_0019e578();
        sk_rt_00077894();
        return sk_rt_002775c8();
    }
    uint64_t v = 0; /* *unaff_x20 */
    sk_rt_0034b3e8();
    sk_rt_0036b270(v);
    sk_rt_0007c1c4();
    return v;
}
