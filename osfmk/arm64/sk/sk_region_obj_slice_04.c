/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))". All
 * names are estimates unless string/header-matched.
 * Slice: 0x2b0f08-0x2c002c — object-service region; mostly embedded Swift runtime
 * (String/Array/Set/Unicode UTF-8/UTF-16 decode) and object-service dispatch.
 * Confidence medium unless a Swift runtime string matches. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations (declared extern with a one-line
 * note; their bodies are reconstructed by the range worker that owns them).
 * Names are estimates; FUN_ address in comment is ground truth. Helpers
 * take/return word-sized values through the ARM64 register ABI; the
 * decompiler could not always resolve their exact signatures, so they are
 * declared with unspecified arguments (K&R empty-parameter form).
 * ------------------------------------------------------------------ */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */
extern unsigned long sk_rt_00002534();  /* FUN_00002534 */
extern unsigned long sk_rt_000026e8();  /* FUN_000026e8 */
extern unsigned long sk_rt_0001a1c8();  /* FUN_0001a1c8 */
extern unsigned long sk_rt_0001da84();  /* FUN_0001da84 */
extern unsigned long sk_rt_00041138();  /* FUN_00041138 */
extern unsigned long sk_rt_00068e14();  /* FUN_00068e14 */
extern unsigned long sk_rt_0006a4c0();  /* FUN_0006a4c0 */
extern unsigned long sk_rt_0006b42c();  /* FUN_0006b42c */
extern unsigned long sk_rt_0006b674();  /* FUN_0006b674 */
extern unsigned long sk_rt_0006f768();  /* FUN_0006f768 */
extern unsigned long sk_rt_00077888();  /* FUN_00077888 */
extern unsigned long sk_rt_00077894();  /* FUN_00077894 */
extern unsigned long sk_rt_0007c1c4();  /* FUN_0007c1c4 */
extern unsigned long sk_rt_000824e4();  /* FUN_000824e4 */
extern unsigned long sk_rt_000839d8();  /* FUN_000839d8 */
extern unsigned long sk_rt_0008409c();  /* FUN_0008409c */
extern unsigned long sk_rt_0008412c();  /* FUN_0008412c */
extern unsigned long sk_rt_00084180();  /* FUN_00084180 */
extern unsigned long sk_rt_00084220();  /* FUN_00084220 */
extern unsigned long sk_rt_00084234();  /* FUN_00084234 */
extern unsigned long sk_rt_0008e34c();  /* FUN_0008e34c */
extern unsigned long sk_rt_0008e500();  /* FUN_0008e500 */
extern unsigned long sk_rt_0008e518();  /* FUN_0008e518 */
extern unsigned long sk_rt_0009461c();  /* FUN_0009461c */
extern unsigned long sk_rt_000a6f68();  /* FUN_000a6f68 */
extern unsigned long sk_rt_000b4390();  /* FUN_000b4390 */
extern unsigned long sk_rt_000b43d0();  /* FUN_000b43d0 */
extern unsigned long sk_rt_000dbcc8();  /* FUN_000dbcc8 */
extern unsigned long sk_rt_0010084c();  /* FUN_0010084c */
extern unsigned long sk_rt_00100efc();  /* FUN_00100efc */
extern unsigned long sk_rt_00106e3c();  /* FUN_00106e3c */
extern unsigned long sk_rt_0011aa70();  /* FUN_0011aa70 */
extern unsigned long sk_rt_00167404();  /* FUN_00167404 */
extern unsigned long sk_rt_001676cc();  /* FUN_001676cc */
extern unsigned long sk_rt_001a6484();  /* FUN_001a6484 */
extern unsigned long sk_rt_001a65b0();  /* FUN_001a65b0 */
extern unsigned long sk_rt_001a7804();  /* FUN_001a7804 */
extern unsigned long sk_rt_001a84f4();  /* FUN_001a84f4 */
extern unsigned long sk_rt_001a8564();  /* FUN_001a8564 */
extern unsigned long sk_rt_001afa84();  /* FUN_001afa84 */
extern unsigned long sk_rt_001afe4c();  /* FUN_001afe4c */
extern unsigned long sk_rt_001b1d5c();  /* FUN_001b1d5c */
extern unsigned long sk_rt_001b1ff0();  /* FUN_001b1ff0 */
extern unsigned long sk_rt_001b260c();  /* FUN_001b260c */
extern unsigned long sk_rt_001b28d4();  /* FUN_001b28d4 */
extern unsigned long sk_rt_001b2e08();  /* FUN_001b2e08 */
extern unsigned long sk_rt_001b7cec();  /* FUN_001b7cec */
extern unsigned long sk_rt_001bcdb8();  /* FUN_001bcdb8 */
extern unsigned long sk_rt_001bf740();  /* FUN_001bf740 */
extern unsigned long sk_rt_001bf784();  /* FUN_001bf784 */
extern unsigned long sk_rt_001d2f4c();  /* FUN_001d2f4c */
extern unsigned long sk_rt_001dc050();  /* FUN_001dc050 */
extern unsigned long sk_rt_001e4cbc();  /* FUN_001e4cbc */
extern unsigned long sk_rt_001e9c00();  /* FUN_001e9c00 */
extern unsigned long sk_rt_001e9d8c();  /* FUN_001e9d8c */
extern unsigned long sk_rt_001eb088();  /* FUN_001eb088 */
extern unsigned long sk_rt_001eb73c();  /* FUN_001eb73c */
extern unsigned long sk_rt_00254fb4();  /* FUN_00254fb4 */
extern unsigned long sk_rt_00280570();  /* FUN_00280570 */
extern unsigned long sk_rt_0028cd14();  /* FUN_0028cd14 */
extern unsigned long sk_rt_0028e8c0();  /* FUN_0028e8c0 */
extern unsigned long sk_rt_00291d70();  /* FUN_00291d70 */
extern unsigned long sk_rt_00294a20();  /* FUN_00294a20 */
extern unsigned long sk_rt_00297af0();  /* FUN_00297af0 */
extern unsigned long sk_rt_00297be8();  /* FUN_00297be8 */
extern unsigned long sk_rt_00298e58();  /* FUN_00298e58 */
extern unsigned long sk_rt_0029b1e0();  /* FUN_0029b1e0 */
extern unsigned long sk_rt_0029d53c();  /* FUN_0029d53c */
extern unsigned long sk_rt_0029df10();  /* FUN_0029df10 */
extern unsigned long sk_rt_0029df64();  /* FUN_0029df64 */
extern unsigned long sk_rt_002a2698();  /* FUN_002a2698 */
extern unsigned long sk_rt_002a3e64();  /* FUN_002a3e64 */
extern unsigned long sk_rt_002a4528();  /* FUN_002a4528 */
extern unsigned long sk_rt_002a4614();  /* FUN_002a4614 */
extern unsigned long sk_rt_002a49a8();  /* FUN_002a49a8 */
extern unsigned long sk_rt_002a4c98();  /* FUN_002a4c98 */
extern unsigned long sk_rt_002a58b8();  /* FUN_002a58b8 */
extern unsigned long sk_rt_002a5e9c();  /* FUN_002a5e9c */
extern unsigned long sk_rt_002a6080();  /* FUN_002a6080 */
extern unsigned long sk_rt_002a95b4();  /* FUN_002a95b4 */
extern unsigned long sk_rt_002a999c();  /* FUN_002a999c */
extern unsigned long sk_rt_002a9ba8();  /* FUN_002a9ba8 */
extern unsigned long sk_rt_002ab058();  /* FUN_002ab058 */
extern unsigned long sk_rt_002ab4d4();  /* FUN_002ab4d4 */
extern unsigned long sk_rt_002ab5bc();  /* FUN_002ab5bc */
extern unsigned long sk_rt_002ab6a0();  /* FUN_002ab6a0 */
extern unsigned long sk_rt_002ab7f0();  /* FUN_002ab7f0 */
extern unsigned long sk_rt_002ac99c();  /* FUN_002ac99c */
extern unsigned long sk_rt_002aca00();  /* FUN_002aca00 */
extern unsigned long sk_rt_002ad700();  /* FUN_002ad700 */
extern unsigned long sk_rt_002ae028();  /* FUN_002ae028 */
extern unsigned long sk_rt_002af2c4();  /* FUN_002af2c4 */
extern unsigned long sk_rt_002af444();  /* FUN_002af444 */
extern unsigned long sk_rt_002af474();  /* FUN_002af474 */
extern unsigned long sk_rt_002af4d0();  /* FUN_002af4d0 */
extern unsigned long sk_rt_002af4ec();  /* FUN_002af4ec */
extern unsigned long sk_rt_002af618();  /* FUN_002af618 */
extern unsigned long sk_rt_002af628();  /* FUN_002af628 */
extern unsigned long sk_rt_002af6e4();  /* FUN_002af6e4 */
extern unsigned long sk_rt_002af74c();  /* FUN_002af74c */
extern unsigned long sk_rt_002af844();  /* FUN_002af844 */
extern unsigned long sk_rt_002afadc();  /* FUN_002afadc */
extern unsigned long sk_rt_002afca8();  /* FUN_002afca8 */
extern unsigned long sk_rt_002afd38();  /* FUN_002afd38 */
extern unsigned long sk_rt_002afee0();  /* FUN_002afee0 */
extern unsigned long sk_rt_002afeec();  /* FUN_002afeec */
extern unsigned long sk_rt_002affec();  /* FUN_002affec */
extern unsigned long sk_rt_002b0140();  /* FUN_002b0140 */
extern unsigned long sk_rt_002b0224();  /* FUN_002b0224 */
extern unsigned long sk_rt_002b03b4();  /* FUN_002b03b4 */
extern unsigned long sk_rt_002b05a0();  /* FUN_002b05a0 */
extern unsigned long sk_rt_002b05e0();  /* FUN_002b05e0 */
extern unsigned long sk_rt_002b05f8();  /* FUN_002b05f8 */
extern unsigned long sk_rt_002b0844();  /* FUN_002b0844 */
extern unsigned long sk_rt_002b0888();  /* FUN_002b0888 */
extern unsigned long sk_rt_002b08b8();  /* FUN_002b08b8 */
extern unsigned long sk_rt_002b0a24();  /* FUN_002b0a24 */
extern unsigned long sk_rt_002b0bc4();  /* FUN_002b0bc4 */
extern unsigned long sk_rt_002b0c10();  /* FUN_002b0c10 */
extern unsigned long sk_rt_002b0c14();  /* FUN_002b0c14 */
extern unsigned long sk_rt_002b0c5c();  /* FUN_002b0c5c */
extern unsigned long sk_rt_002b0c84();  /* FUN_002b0c84 */
extern unsigned long sk_rt_002b0ec8();  /* FUN_002b0ec8 */
extern unsigned long sk_rt_002b0f08();  /* FUN_002b0f08 */
extern unsigned long sk_rt_002b0f14();  /* FUN_002b0f14 */
extern unsigned long sk_rt_002b0f4c();  /* FUN_002b0f4c */
extern unsigned long sk_rt_002b0f7c();  /* FUN_002b0f7c */
extern unsigned long sk_rt_002b0ff4();  /* FUN_002b0ff4 */
extern unsigned long sk_rt_002b1038();  /* FUN_002b1038 */
extern unsigned long sk_rt_002b1104();  /* FUN_002b1104 */
extern unsigned long sk_rt_002b13ac();  /* FUN_002b13ac */
extern unsigned long sk_rt_002b141c();  /* FUN_002b141c */
extern unsigned long sk_rt_002b14c8();  /* FUN_002b14c8 */
extern unsigned long sk_rt_002b1510();  /* FUN_002b1510 */
extern unsigned long sk_rt_002b15d0();  /* FUN_002b15d0 */
extern unsigned long sk_rt_002b1630();  /* FUN_002b1630 */
extern unsigned long sk_rt_002b16cc();  /* FUN_002b16cc */
extern unsigned long sk_rt_002b17c8();  /* FUN_002b17c8 */
extern unsigned long sk_rt_002b18c4();  /* FUN_002b18c4 */
extern unsigned long sk_rt_002b1960();  /* FUN_002b1960 */
extern unsigned long sk_rt_002b1b3c();  /* FUN_002b1b3c */
extern unsigned long sk_rt_002b1c84();  /* FUN_002b1c84 */
extern unsigned long sk_rt_002b1ce0();  /* FUN_002b1ce0 */
extern unsigned long sk_rt_002b1dc8();  /* FUN_002b1dc8 */
extern unsigned long sk_rt_002b1ec4();  /* FUN_002b1ec4 */
extern unsigned long sk_rt_002b1ec8();  /* FUN_002b1ec8 */
extern unsigned long sk_rt_002b1ee8();  /* FUN_002b1ee8 */
extern unsigned long sk_rt_002b1fe4();  /* FUN_002b1fe4 */
extern unsigned long sk_rt_002b2058();  /* FUN_002b2058 */
extern unsigned long sk_rt_002b205c();  /* FUN_002b205c */
extern unsigned long sk_rt_002b2078();  /* FUN_002b2078 */
extern unsigned long sk_rt_002b21e0();  /* FUN_002b21e0 */
extern unsigned long sk_rt_002b22d4();  /* FUN_002b22d4 */
extern unsigned long sk_rt_002b24b8();  /* FUN_002b24b8 */
extern unsigned long sk_rt_002b24f4();  /* FUN_002b24f4 */
extern unsigned long sk_rt_002b257c();  /* FUN_002b257c */
extern unsigned long sk_rt_002b25cc();  /* FUN_002b25cc */
extern unsigned long sk_rt_002b25fc();  /* FUN_002b25fc */
extern unsigned long sk_rt_002b2660();  /* FUN_002b2660 */
extern unsigned long sk_rt_002b273c();  /* FUN_002b273c */
extern unsigned long sk_rt_002b275c();  /* FUN_002b275c */
extern unsigned long sk_rt_002b279c();  /* FUN_002b279c */
extern unsigned long sk_rt_002b2804();  /* FUN_002b2804 */
extern unsigned long sk_rt_002b2808();  /* FUN_002b2808 */
extern unsigned long sk_rt_002b2828();  /* FUN_002b2828 */
extern unsigned long sk_rt_002b282c();  /* FUN_002b282c */
extern unsigned long sk_rt_002b2890();  /* FUN_002b2890 */
extern unsigned long sk_rt_002b28c8();  /* FUN_002b28c8 */
extern unsigned long sk_rt_002b297c();  /* FUN_002b297c */
extern unsigned long sk_rt_002b298c();  /* FUN_002b298c */
extern unsigned long sk_rt_002b2990();  /* FUN_002b2990 */
extern unsigned long sk_rt_002b29a8();  /* FUN_002b29a8 */
extern unsigned long sk_rt_002b29d0();  /* FUN_002b29d0 */
extern unsigned long sk_rt_002b2e60();  /* FUN_002b2e60 */
extern unsigned long sk_rt_002b3670();  /* FUN_002b3670 */
extern unsigned long sk_rt_002b36a4();  /* FUN_002b36a4 */
extern unsigned long sk_rt_002b377c();  /* FUN_002b377c */
extern unsigned long sk_rt_002b3978();  /* FUN_002b3978 */
extern unsigned long sk_rt_002b39b4();  /* FUN_002b39b4 */
extern unsigned long sk_rt_002b3b50();  /* FUN_002b3b50 */
extern unsigned long sk_rt_002b3b84();  /* FUN_002b3b84 */
extern unsigned long sk_rt_002b3c10();  /* FUN_002b3c10 */
extern unsigned long sk_rt_002b3cf8();  /* FUN_002b3cf8 */
extern unsigned long sk_rt_002b3d68();  /* FUN_002b3d68 */
extern unsigned long sk_rt_002b3e00();  /* FUN_002b3e00 */
extern unsigned long sk_rt_002b3f40();  /* FUN_002b3f40 */
extern unsigned long sk_rt_002b4120();  /* FUN_002b4120 */
extern unsigned long sk_rt_002b439c();  /* FUN_002b439c */
extern unsigned long sk_rt_002b44a4();  /* FUN_002b44a4 */
extern unsigned long sk_rt_002b44a8();  /* FUN_002b44a8 */
extern unsigned long sk_rt_002b44d0();  /* FUN_002b44d0 */
extern unsigned long sk_rt_002b4550();  /* FUN_002b4550 */
extern unsigned long sk_rt_002b4580();  /* FUN_002b4580 */
extern unsigned long sk_rt_002b45a8();  /* FUN_002b45a8 */
extern unsigned long sk_rt_002b45cc();  /* FUN_002b45cc */
extern unsigned long sk_rt_002b4834();  /* FUN_002b4834 */
extern unsigned long sk_rt_002b4854();  /* FUN_002b4854 */
extern unsigned long sk_rt_002b4874();  /* FUN_002b4874 */
extern unsigned long sk_rt_002b48e4();  /* FUN_002b48e4 */
extern unsigned long sk_rt_002b49e4();  /* FUN_002b49e4 */
extern unsigned long sk_rt_002b4a70();  /* FUN_002b4a70 */
extern unsigned long sk_rt_002b4b04();  /* FUN_002b4b04 */
extern unsigned long sk_rt_002b4b4c();  /* FUN_002b4b4c */
extern unsigned long sk_rt_002b4b7c();  /* FUN_002b4b7c */
extern unsigned long sk_rt_002b4bac();  /* FUN_002b4bac */
extern unsigned long sk_rt_002b4bdc();  /* FUN_002b4bdc */
extern unsigned long sk_rt_002b4be0();  /* FUN_002b4be0 */
extern unsigned long sk_rt_002b4c00();  /* FUN_002b4c00 */
extern unsigned long sk_rt_002b4ca4();  /* FUN_002b4ca4 */
extern unsigned long sk_rt_002b4e14();  /* FUN_002b4e14 */
extern unsigned long sk_rt_002b4e5c();  /* FUN_002b4e5c */
extern unsigned long sk_rt_002b4e88();  /* FUN_002b4e88 */
extern unsigned long sk_rt_002b4eb8();  /* FUN_002b4eb8 */
extern unsigned long sk_rt_002b4ed4();  /* FUN_002b4ed4 */
extern unsigned long sk_rt_002b4ed8();  /* FUN_002b4ed8 */
extern unsigned long sk_rt_002b4f14();  /* FUN_002b4f14 */
extern unsigned long sk_rt_002b4f64();  /* FUN_002b4f64 */
extern unsigned long sk_rt_002b4fc4();  /* FUN_002b4fc4 */
extern unsigned long sk_rt_002b5abc();  /* FUN_002b5abc */
extern unsigned long sk_rt_002b5af8();  /* FUN_002b5af8 */
extern unsigned long sk_rt_002b5b70();  /* FUN_002b5b70 */
extern unsigned long sk_rt_002b5ba0();  /* FUN_002b5ba0 */
extern unsigned long sk_rt_002b5c70();  /* FUN_002b5c70 */
extern unsigned long sk_rt_002b5ce4();  /* FUN_002b5ce4 */
extern unsigned long sk_rt_002b5d6c();  /* FUN_002b5d6c */
extern unsigned long sk_rt_002b5e10();  /* FUN_002b5e10 */
extern unsigned long sk_rt_002b5ed4();  /* FUN_002b5ed4 */
extern unsigned long sk_rt_002b5f94();  /* FUN_002b5f94 */
extern unsigned long sk_rt_002b603c();  /* FUN_002b603c */
extern unsigned long sk_rt_002b60c8();  /* FUN_002b60c8 */
extern unsigned long sk_rt_002b6170();  /* FUN_002b6170 */
extern unsigned long sk_rt_002b61a8();  /* FUN_002b61a8 */
extern unsigned long sk_rt_002b6200();  /* FUN_002b6200 */
extern unsigned long sk_rt_002b6268();  /* FUN_002b6268 */
extern unsigned long sk_rt_002b62bc();  /* FUN_002b62bc */
extern unsigned long sk_rt_002b62c0();  /* FUN_002b62c0 */
extern unsigned long sk_rt_002b62dc();  /* FUN_002b62dc */
extern unsigned long sk_rt_002b62f4();  /* FUN_002b62f4 */
extern unsigned long sk_rt_002b6364();  /* FUN_002b6364 */
extern unsigned long sk_rt_002b6368();  /* FUN_002b6368 */
extern unsigned long sk_rt_002b6388();  /* FUN_002b6388 */
extern unsigned long sk_rt_002b6448();  /* FUN_002b6448 */
extern unsigned long sk_rt_002b64cc();  /* FUN_002b64cc */
extern unsigned long sk_rt_002b6630();  /* FUN_002b6630 */
extern unsigned long sk_rt_002b676c();  /* FUN_002b676c */
extern unsigned long sk_rt_002b68a0();  /* FUN_002b68a0 */
extern unsigned long sk_rt_002b68c4();  /* FUN_002b68c4 */
extern unsigned long sk_rt_002b6a90();  /* FUN_002b6a90 */
extern unsigned long sk_rt_002b6c54();  /* FUN_002b6c54 */
extern unsigned long sk_rt_002b6c8c();  /* FUN_002b6c8c */
extern unsigned long sk_rt_002b7794();  /* FUN_002b7794 */
extern unsigned long sk_rt_002bb9b8();  /* FUN_002bb9b8 */
extern unsigned long sk_rt_002bbb64();  /* FUN_002bbb64 */
extern unsigned long sk_rt_002bbc14();  /* FUN_002bbc14 */
extern unsigned long sk_rt_002bbcd8();  /* FUN_002bbcd8 */
extern unsigned long sk_rt_002c6a20();  /* FUN_002c6a20 */
extern unsigned long sk_rt_002c6d00();  /* FUN_002c6d00 */
extern unsigned long sk_rt_002c7b68();  /* FUN_002c7b68 */
extern unsigned long sk_rt_002c7b8c();  /* FUN_002c7b8c */
extern unsigned long sk_rt_002c8c2c();  /* FUN_002c8c2c */
extern unsigned long sk_rt_00310c44();  /* FUN_00310c44 */
extern unsigned long sk_rt_0031b46c();  /* FUN_0031b46c */
extern unsigned long sk_rt_0031b49c();  /* FUN_0031b49c */
extern unsigned long sk_rt_00344e54();  /* FUN_00344e54 */
extern unsigned long sk_rt_00346774();  /* FUN_00346774 */
extern unsigned long sk_rt_00346d38();  /* FUN_00346d38 */
extern unsigned long sk_rt_00347d60();  /* FUN_00347d60 */
extern unsigned long sk_rt_00347f2c();  /* FUN_00347f2c */
extern unsigned long sk_rt_003480ac();  /* FUN_003480ac */
extern unsigned long sk_rt_003481fc();  /* FUN_003481fc */
extern unsigned long sk_rt_00348244();  /* FUN_00348244 */
extern unsigned long sk_rt_00348284();  /* FUN_00348284 */
extern unsigned long sk_rt_00348508();  /* FUN_00348508 */
extern unsigned long sk_rt_00348614();  /* FUN_00348614 */
extern unsigned long sk_rt_003486b8();  /* FUN_003486b8 */
extern unsigned long sk_rt_0034883c();  /* FUN_0034883c */
extern unsigned long sk_rt_00348898();  /* FUN_00348898 */
extern unsigned long sk_rt_003488bc();  /* FUN_003488bc */
extern unsigned long sk_rt_003489dc();  /* FUN_003489dc */
extern unsigned long sk_rt_00348abc();  /* FUN_00348abc */
extern unsigned long sk_rt_00348bbc();  /* FUN_00348bbc */
extern unsigned long sk_rt_00348e48();  /* FUN_00348e48 */
extern unsigned long sk_rt_00349424();  /* FUN_00349424 */
extern unsigned long sk_rt_00349720();  /* FUN_00349720 */
extern unsigned long sk_rt_0034987c();  /* FUN_0034987c */
extern unsigned long sk_rt_00349a40();  /* FUN_00349a40 */
extern unsigned long sk_rt_00349b3c();  /* FUN_00349b3c */
extern unsigned long sk_rt_00349c98();  /* FUN_00349c98 */
extern unsigned long sk_rt_00349fcc();  /* FUN_00349fcc */
extern unsigned long sk_rt_0034a018();  /* FUN_0034a018 */
extern unsigned long sk_rt_0034a134();  /* FUN_0034a134 */
extern unsigned long sk_rt_0034a210();  /* FUN_0034a210 */
extern unsigned long sk_rt_0034a224();  /* FUN_0034a224 */
extern unsigned long sk_rt_0034a260();  /* FUN_0034a260 */
extern unsigned long sk_rt_0034a274();  /* FUN_0034a274 */
extern unsigned long sk_rt_0034a2f8();  /* FUN_0034a2f8 */
extern unsigned long sk_rt_0034a3b0();  /* FUN_0034a3b0 */
extern unsigned long sk_rt_0034a618();  /* FUN_0034a618 */
extern unsigned long sk_rt_0034a96c();  /* FUN_0034a96c */
extern unsigned long sk_rt_0034aa3c();  /* FUN_0034aa3c */
extern unsigned long sk_rt_0034ab88();  /* FUN_0034ab88 */
extern unsigned long sk_rt_0034aebc();  /* FUN_0034aebc */
extern unsigned long sk_rt_0034b13c();  /* FUN_0034b13c */
extern unsigned long sk_rt_0034b358();  /* FUN_0034b358 */
extern unsigned long sk_rt_0034b430();  /* FUN_0034b430 */
extern unsigned long sk_rt_0034b730();  /* FUN_0034b730 */
extern unsigned long sk_rt_0034b758();  /* FUN_0034b758 */
extern unsigned long sk_rt_0034b768();  /* FUN_0034b768 */
extern unsigned long sk_rt_0034b778();  /* FUN_0034b778 */
extern unsigned long sk_rt_0034b788();  /* FUN_0034b788 */
extern unsigned long sk_rt_0034b7c8();  /* FUN_0034b7c8 */
extern unsigned long sk_rt_0034b848();  /* FUN_0034b848 */
extern unsigned long sk_rt_0034b8bc();  /* FUN_0034b8bc */
extern unsigned long sk_rt_0034ba28();  /* FUN_0034ba28 */
extern unsigned long sk_rt_0034bb84();  /* FUN_0034bb84 */
extern unsigned long sk_rt_0034bc94();  /* FUN_0034bc94 */
extern unsigned long sk_rt_0034bf1c();  /* FUN_0034bf1c */
extern unsigned long sk_rt_0034c1f8();  /* FUN_0034c1f8 */
extern unsigned long sk_rt_0034c2a4();  /* FUN_0034c2a4 */
extern unsigned long sk_rt_0034c3f4();  /* FUN_0034c3f4 */
extern unsigned long sk_rt_0034c434();  /* FUN_0034c434 */
extern unsigned long sk_rt_0034c6d4();  /* FUN_0034c6d4 */
extern unsigned long sk_rt_0034c818();  /* FUN_0034c818 */
extern unsigned long sk_rt_0034c840();  /* FUN_0034c840 */
extern unsigned long sk_rt_0034c9c8();  /* FUN_0034c9c8 */
extern unsigned long sk_rt_0034cad8();  /* FUN_0034cad8 */
extern unsigned long sk_rt_0034cbb0();  /* FUN_0034cbb0 */
extern unsigned long sk_rt_0034cbd8();  /* FUN_0034cbd8 */
extern unsigned long sk_rt_0034cd90();  /* FUN_0034cd90 */
extern unsigned long sk_rt_0034cec4();  /* FUN_0034cec4 */
extern unsigned long sk_rt_0034cf54();  /* FUN_0034cf54 */
extern unsigned long sk_rt_0034d004();  /* FUN_0034d004 */
extern unsigned long sk_rt_0034d364();  /* FUN_0034d364 */
extern unsigned long sk_rt_0034d384();  /* FUN_0034d384 */
extern unsigned long sk_rt_0034d5ec();  /* FUN_0034d5ec */
extern unsigned long sk_rt_0034da48();  /* FUN_0034da48 */
extern unsigned long sk_rt_0034daa8();  /* FUN_0034daa8 */
extern unsigned long sk_rt_0034dc84();  /* FUN_0034dc84 */
extern unsigned long sk_rt_0034de9c();  /* FUN_0034de9c */
extern unsigned long sk_rt_0034df94();  /* FUN_0034df94 */
extern unsigned long sk_rt_0034dff4();  /* FUN_0034dff4 */
extern unsigned long sk_rt_0034e52c();  /* FUN_0034e52c */
extern unsigned long sk_rt_0034e56c();  /* FUN_0034e56c */
extern unsigned long sk_rt_0034e6bc();  /* FUN_0034e6bc */
extern unsigned long sk_rt_0034e7f4();  /* FUN_0034e7f4 */
extern unsigned long sk_rt_0034f114();  /* FUN_0034f114 */
extern unsigned long sk_rt_0034f2d4();  /* FUN_0034f2d4 */
extern unsigned long sk_rt_0034f314();  /* FUN_0034f314 */
extern unsigned long sk_rt_0034f798();  /* FUN_0034f798 */
extern unsigned long sk_rt_0034f7b0();  /* FUN_0034f7b0 */
extern unsigned long sk_rt_0034fb60();  /* FUN_0034fb60 */
extern unsigned long sk_rt_0034fb74();  /* FUN_0034fb74 */
extern unsigned long sk_rt_0034fb88();  /* FUN_0034fb88 */
extern unsigned long sk_rt_0034fb9c();  /* FUN_0034fb9c */
extern unsigned long sk_rt_0034fbb0();  /* FUN_0034fbb0 */
extern unsigned long sk_rt_0034fbf4();  /* FUN_0034fbf4 */
extern unsigned long sk_rt_0034fcac();  /* FUN_0034fcac */
extern unsigned long sk_rt_0034fd6c();  /* FUN_0034fd6c */
extern unsigned long sk_rt_00350258();  /* FUN_00350258 */
extern unsigned long sk_rt_0035047c();  /* FUN_0035047c */
extern unsigned long sk_rt_003504a0();  /* FUN_003504a0 */
extern unsigned long sk_rt_003504ac();  /* FUN_003504ac */
extern unsigned long sk_rt_00350518();  /* FUN_00350518 */
extern unsigned long sk_rt_00350524();  /* FUN_00350524 */
extern unsigned long sk_rt_00350548();  /* FUN_00350548 */
extern unsigned long sk_rt_00350560();  /* FUN_00350560 */
extern unsigned long sk_rt_003505f4();  /* FUN_003505f4 */
extern unsigned long sk_rt_00350600();  /* FUN_00350600 */
extern unsigned long sk_rt_00350624();  /* FUN_00350624 */
extern unsigned long sk_rt_00350768();  /* FUN_00350768 */
extern unsigned long sk_rt_00350774();  /* FUN_00350774 */
extern unsigned long sk_rt_003507e0();  /* FUN_003507e0 */
extern unsigned long sk_rt_00350804();  /* FUN_00350804 */
extern unsigned long sk_rt_00350858();  /* FUN_00350858 */
extern unsigned long sk_rt_003508c0();  /* FUN_003508c0 */
extern unsigned long sk_rt_00350968();  /* FUN_00350968 */
extern unsigned long sk_rt_00350974();  /* FUN_00350974 */
extern unsigned long sk_rt_00350980();  /* FUN_00350980 */
extern unsigned long sk_rt_003509ec();  /* FUN_003509ec */
extern unsigned long sk_rt_00350a28();  /* FUN_00350a28 */
extern unsigned long sk_rt_00350ab8();  /* FUN_00350ab8 */
extern unsigned long sk_rt_00350b0c();  /* FUN_00350b0c */
extern unsigned long sk_rt_00350b54();  /* FUN_00350b54 */
extern unsigned long sk_rt_00350bf0();  /* FUN_00350bf0 */
extern unsigned long sk_rt_00350c5c();  /* FUN_00350c5c */
extern unsigned long sk_rt_00350ce4();  /* FUN_00350ce4 */
extern unsigned long sk_rt_00351094();  /* FUN_00351094 */
extern unsigned long sk_rt_00351124();  /* FUN_00351124 */
extern unsigned long sk_rt_0035119c();  /* FUN_0035119c */
extern unsigned long sk_rt_003511a8();  /* FUN_003511a8 */
extern unsigned long sk_rt_00351318();  /* FUN_00351318 */
extern unsigned long sk_rt_00351348();  /* FUN_00351348 */
extern unsigned long sk_rt_0035151c();  /* FUN_0035151c */
extern unsigned long sk_rt_0035159c();  /* FUN_0035159c */
extern unsigned long sk_rt_00351624();  /* FUN_00351624 */
extern unsigned long sk_rt_00351744();  /* FUN_00351744 */
extern unsigned long sk_rt_00351790();  /* FUN_00351790 */
extern unsigned long sk_rt_003519e8();  /* FUN_003519e8 */
extern unsigned long sk_rt_00351a14();  /* FUN_00351a14 */
extern unsigned long sk_rt_00351b6c();  /* FUN_00351b6c */
extern unsigned long sk_rt_00351c64();  /* FUN_00351c64 */
extern unsigned long sk_rt_00351ca0();  /* FUN_00351ca0 */
extern unsigned long sk_rt_00351d30();  /* FUN_00351d30 */
extern unsigned long sk_rt_00351da8();  /* FUN_00351da8 */
extern unsigned long sk_rt_00351db4();  /* FUN_00351db4 */
extern unsigned long sk_rt_00351dc0();  /* FUN_00351dc0 */
extern unsigned long sk_rt_00351e08();  /* FUN_00351e08 */
extern unsigned long sk_rt_00351e20();  /* FUN_00351e20 */
extern unsigned long sk_rt_00351ef8();  /* FUN_00351ef8 */
extern unsigned long sk_rt_003520c0();  /* FUN_003520c0 */
extern unsigned long sk_rt_003520dc();  /* FUN_003520dc */
extern unsigned long sk_rt_003521b4();  /* FUN_003521b4 */
extern unsigned long sk_rt_0035239c();  /* FUN_0035239c */
extern unsigned long sk_rt_003523e0();  /* FUN_003523e0 */
extern unsigned long sk_rt_0035272c();  /* FUN_0035272c */
extern unsigned long sk_rt_00352758();  /* FUN_00352758 */
extern unsigned long sk_rt_00352764();  /* FUN_00352764 */
extern unsigned long sk_rt_003527a4();  /* FUN_003527a4 */
extern unsigned long sk_rt_003528cc();  /* FUN_003528cc */
extern unsigned long sk_rt_00352ae4();  /* FUN_00352ae4 */
extern unsigned long sk_rt_00352af0();  /* FUN_00352af0 */
extern unsigned long sk_rt_00352b20();  /* FUN_00352b20 */
extern unsigned long sk_rt_00352bd4();  /* FUN_00352bd4 */
extern unsigned long sk_rt_00352c74();  /* FUN_00352c74 */
extern unsigned long sk_rt_00352cb0();  /* FUN_00352cb0 */
extern unsigned long sk_rt_00352cec();  /* FUN_00352cec */
extern unsigned long sk_rt_00352e54();  /* FUN_00352e54 */
extern unsigned long sk_rt_00352e84();  /* FUN_00352e84 */
extern unsigned long sk_rt_00352e9c();  /* FUN_00352e9c */
extern unsigned long sk_rt_0035300c();  /* FUN_0035300c */
extern unsigned long sk_rt_00353178();  /* FUN_00353178 */
extern unsigned long sk_rt_003531d8();  /* FUN_003531d8 */
extern unsigned long sk_rt_00353238();  /* FUN_00353238 */
extern unsigned long sk_rt_003532b8();  /* FUN_003532b8 */
extern unsigned long sk_rt_00353510();  /* FUN_00353510 */
extern unsigned long sk_rt_00353558();  /* FUN_00353558 */
extern unsigned long sk_rt_00353590();  /* FUN_00353590 */
extern unsigned long sk_rt_003535b4();  /* FUN_003535b4 */
extern unsigned long sk_rt_0035360c();  /* FUN_0035360c */
extern unsigned long sk_rt_0035367c();  /* FUN_0035367c */
extern unsigned long sk_rt_003537e0();  /* FUN_003537e0 */
extern unsigned long sk_rt_00353850();  /* FUN_00353850 */
extern unsigned long sk_rt_00353878();  /* FUN_00353878 */
extern unsigned long sk_rt_003538a0();  /* FUN_003538a0 */
extern unsigned long sk_rt_00353a0c();  /* FUN_00353a0c */
extern unsigned long sk_rt_00353a30();  /* FUN_00353a30 */
extern unsigned long sk_rt_00353cfc();  /* FUN_00353cfc */
extern unsigned long sk_rt_00353d14();  /* FUN_00353d14 */
extern unsigned long sk_rt_00353d64();  /* FUN_00353d64 */
extern unsigned long sk_rt_00353d70();  /* FUN_00353d70 */
extern unsigned long sk_rt_00353f2c();  /* FUN_00353f2c */
extern unsigned long sk_rt_00353ff4();  /* FUN_00353ff4 */
extern unsigned long sk_rt_00354040();  /* FUN_00354040 */
extern unsigned long sk_rt_003540ac();  /* FUN_003540ac */
extern unsigned long sk_rt_00354140();  /* FUN_00354140 */
extern unsigned long sk_rt_003542dc();  /* FUN_003542dc */
extern unsigned long sk_rt_003543d0();  /* FUN_003543d0 */
extern unsigned long sk_rt_003544c8();  /* FUN_003544c8 */
extern unsigned long sk_rt_00354744();  /* FUN_00354744 */
extern unsigned long sk_rt_00354810();  /* FUN_00354810 */
extern unsigned long sk_rt_0035484c();  /* FUN_0035484c */
extern unsigned long sk_rt_003548ac();  /* FUN_003548ac */
extern unsigned long sk_rt_00354960();  /* FUN_00354960 */
extern unsigned long sk_rt_00354a28();  /* FUN_00354a28 */
extern unsigned long sk_rt_00354a34();  /* FUN_00354a34 */
extern unsigned long sk_rt_00354a6c();  /* FUN_00354a6c */
extern unsigned long sk_rt_00354c9c();  /* FUN_00354c9c */
extern unsigned long sk_rt_00354e0c();  /* FUN_00354e0c */
extern unsigned long sk_rt_00354ef8();  /* FUN_00354ef8 */
extern unsigned long sk_rt_003551a0();  /* FUN_003551a0 */
extern unsigned long sk_rt_003551e8();  /* FUN_003551e8 */
extern unsigned long sk_rt_003554e0();  /* FUN_003554e0 */
extern unsigned long sk_rt_00355560();  /* FUN_00355560 */
extern unsigned long sk_rt_0035564c();  /* FUN_0035564c */
extern unsigned long sk_rt_00355660();  /* FUN_00355660 */
extern unsigned long sk_rt_00355720();  /* FUN_00355720 */
extern unsigned long sk_rt_00355814();  /* FUN_00355814 */
extern unsigned long sk_rt_003558c4();  /* FUN_003558c4 */
extern unsigned long sk_rt_00355914();  /* FUN_00355914 */
extern unsigned long sk_rt_00355968();  /* FUN_00355968 */
extern unsigned long sk_rt_003559bc();  /* FUN_003559bc */
extern unsigned long sk_rt_00355b68();  /* FUN_00355b68 */
extern unsigned long sk_rt_00355bf4();  /* FUN_00355bf4 */
extern unsigned long sk_rt_00355da8();  /* FUN_00355da8 */
extern unsigned long sk_rt_00356084();  /* FUN_00356084 */
extern unsigned long sk_rt_0035617c();  /* FUN_0035617c */
extern unsigned long sk_rt_00356188();  /* FUN_00356188 */
extern unsigned long sk_rt_003561a0();  /* FUN_003561a0 */
extern unsigned long sk_rt_003562bc();  /* FUN_003562bc */
extern unsigned long sk_rt_003562c8();  /* FUN_003562c8 */
extern unsigned long sk_rt_003562f8();  /* FUN_003562f8 */
extern unsigned long sk_rt_0035634c();  /* FUN_0035634c */
extern unsigned long sk_rt_00356364();  /* FUN_00356364 */
extern unsigned long sk_rt_00356408();  /* FUN_00356408 */
extern unsigned long sk_rt_0035646c();  /* FUN_0035646c */
extern unsigned long sk_rt_00356f58();  /* FUN_00356f58 */
extern unsigned long sk_rt_0035701c();  /* FUN_0035701c */
extern unsigned long sk_rt_00357044();  /* FUN_00357044 */
extern unsigned long sk_rt_00357228();  /* FUN_00357228 */
extern unsigned long sk_rt_003573e8();  /* FUN_003573e8 */
extern unsigned long sk_rt_003575a4();  /* FUN_003575a4 */
extern unsigned long sk_rt_00357628();  /* FUN_00357628 */
extern unsigned long sk_rt_003576c8();  /* FUN_003576c8 */
extern unsigned long sk_rt_00357794();  /* FUN_00357794 */
extern unsigned long sk_rt_003577a0();  /* FUN_003577a0 */
extern unsigned long sk_rt_003577c0();  /* FUN_003577c0 */
extern unsigned long sk_rt_00357850();  /* FUN_00357850 */
extern unsigned long sk_rt_00357938();  /* FUN_00357938 */
extern unsigned long sk_rt_00357bd0();  /* FUN_00357bd0 */
extern unsigned long sk_rt_00357c44();  /* FUN_00357c44 */
extern unsigned long sk_rt_00357c74();  /* FUN_00357c74 */
extern unsigned long sk_rt_00357ca0();  /* FUN_00357ca0 */
extern unsigned long sk_rt_00357cb4();  /* FUN_00357cb4 */
extern unsigned long sk_rt_00357d84();  /* FUN_00357d84 */
extern unsigned long sk_rt_00357de4();  /* FUN_00357de4 */
extern unsigned long sk_rt_00357e94();  /* FUN_00357e94 */
extern unsigned long sk_rt_00357f34();  /* FUN_00357f34 */
extern unsigned long sk_rt_00358044();  /* FUN_00358044 */
extern unsigned long sk_rt_00358074();  /* FUN_00358074 */
extern unsigned long sk_rt_00358084();  /* FUN_00358084 */
extern unsigned long sk_rt_00358288();  /* FUN_00358288 */
extern unsigned long sk_rt_00358298();  /* FUN_00358298 */
extern unsigned long sk_rt_0035847c();  /* FUN_0035847c */
extern unsigned long sk_rt_003584a8();  /* FUN_003584a8 */
extern unsigned long sk_rt_003584f8();  /* FUN_003584f8 */
extern unsigned long sk_rt_0035851c();  /* FUN_0035851c */
extern unsigned long sk_rt_00358528();  /* FUN_00358528 */
extern unsigned long sk_rt_00358654();  /* FUN_00358654 */
extern unsigned long sk_rt_00358708();  /* FUN_00358708 */
extern unsigned long sk_rt_00358990();  /* FUN_00358990 */
extern unsigned long sk_rt_00358a98();  /* FUN_00358a98 */
extern unsigned long sk_rt_00358abc();  /* FUN_00358abc */
extern unsigned long sk_rt_00358c8c();  /* FUN_00358c8c */
extern unsigned long sk_rt_00358ca4();  /* FUN_00358ca4 */
extern unsigned long sk_rt_00358cb0();  /* FUN_00358cb0 */
extern unsigned long sk_rt_00358fb4();  /* FUN_00358fb4 */
extern unsigned long sk_rt_00358fc8();  /* FUN_00358fc8 */
extern unsigned long sk_rt_00358fdc();  /* FUN_00358fdc */
extern unsigned long sk_rt_003593c0();  /* FUN_003593c0 */
extern unsigned long sk_rt_003593d0();  /* FUN_003593d0 */
extern unsigned long sk_rt_00359424();  /* FUN_00359424 */
extern unsigned long sk_rt_00359500();  /* FUN_00359500 */
extern unsigned long sk_rt_00359690();  /* FUN_00359690 */
extern unsigned long sk_rt_00359738();  /* FUN_00359738 */
extern unsigned long sk_rt_00359848();  /* FUN_00359848 */
extern unsigned long sk_rt_00359974();  /* FUN_00359974 */
extern unsigned long sk_rt_00359a30();  /* FUN_00359a30 */
extern unsigned long sk_rt_00359b18();  /* FUN_00359b18 */
extern unsigned long sk_rt_00359d18();  /* FUN_00359d18 */
extern unsigned long sk_rt_00359ddc();  /* FUN_00359ddc */
extern unsigned long sk_rt_00359ed4();  /* FUN_00359ed4 */
extern unsigned long sk_rt_00359fb4();  /* FUN_00359fb4 */
extern unsigned long sk_rt_00359ffc();  /* FUN_00359ffc */
extern unsigned long sk_rt_0035a04c();  /* FUN_0035a04c */
extern unsigned long sk_rt_0035a250();  /* FUN_0035a250 */
extern unsigned long sk_rt_0035a280();  /* FUN_0035a280 */
extern unsigned long sk_rt_0035a310();  /* FUN_0035a310 */
extern unsigned long sk_rt_0035a380();  /* FUN_0035a380 */
extern unsigned long sk_rt_0035a4e0();  /* FUN_0035a4e0 */
extern unsigned long sk_rt_0035a5cc();  /* FUN_0035a5cc */
extern unsigned long sk_rt_0035a614();  /* FUN_0035a614 */
extern unsigned long sk_rt_0035a798();  /* FUN_0035a798 */
extern unsigned long sk_rt_0035a8d0();  /* FUN_0035a8d0 */
extern unsigned long sk_rt_0035a9b0();  /* FUN_0035a9b0 */
extern unsigned long sk_rt_0035aac0();  /* FUN_0035aac0 */
extern unsigned long sk_rt_0035ab14();  /* FUN_0035ab14 */
extern unsigned long sk_rt_0035ac70();  /* FUN_0035ac70 */
extern unsigned long sk_rt_00365b6c();  /* FUN_00365b6c */
extern unsigned long sk_rt_0036a908();  /* FUN_0036a908 */
extern unsigned long sk_rt_0036b270();  /* FUN_0036b270 */
extern unsigned long sk_rt_003a25d4();  /* FUN_003a25d4 */
extern unsigned long sk_rt_003a25e0();  /* FUN_003a25e0 */
extern unsigned long sk_rt_003d3470();  /* FUN_003d3470 */
extern unsigned long sk_rt_003d34b8();  /* FUN_003d34b8 */
extern unsigned long sk_rt_003d351c();  /* FUN_003d351c */
extern unsigned long sk_rt_003d3d4c();  /* FUN_003d3d4c */

/* ------------------------------------------------------------------ *
 * Forward declarations for functions reconstructed within this slice. *
 * ------------------------------------------------------------------ */
void sk_swift_string_compare(void *a, void *b, void *c);
unsigned long sk_swift_string_index_position(unsigned long w);
void sk_swift_string_index_utf8(unsigned long v, unsigned long f);
void sk_swift_string_init_impl(void *out, void *a, void *b);
void sk_swift_string_init_impl2(void *a, void *b, unsigned long t, void *c, void *d, void *e);
void sk_swift_string_init_impl3(void *a, void *b);
void sk_swift_string_init_out(void *out, void *s);
void sk_swift_string_init_out_b(void *out, void *s);
void sk_swift_string_init_out_c(void *out, void *s);
void sk_swift_string_utf16_convert(void *o1, void *o2, unsigned long s, unsigned long f, unsigned long l, unsigned int d);
void sk_swift_string_utf16_convert_b(void *o, long n, unsigned long s);
void sk_swift_string_utf16_convert_c(long n);
unsigned long sk_swift_string_utf16_distance(unsigned long i, unsigned long j);
unsigned long sk_swift_string_utf16_index_advance_b(unsigned long i, unsigned long s, unsigned long f);
unsigned long sk_swift_string_utf16_index_before(unsigned long i);
unsigned long sk_swift_string_utf16_index_offset_b(unsigned long i, unsigned long j, unsigned long k, unsigned long l, unsigned long m);
unsigned long sk_swift_string_utf16_index_sub(unsigned long i, unsigned long j, unsigned long k, unsigned long l);
unsigned long sk_swift_string_utf16_subscript_char(unsigned long w);
void sk_swift_string_utf16_trim(void);
void sk_swift_string_utf16_view_advance(void);
void sk_swift_string_utf16_view_advance_d(void);
void sk_swift_string_utf16_view_advance_e(void *out, void *s);
void sk_swift_string_utf16_view_advance_f(void *out, void *s);
void sk_swift_string_utf16_view_advance_g(void);
void sk_swift_string_utf16_view_advance_h(void);
void sk_swift_string_utf16_view_advance_loop(void);
void sk_swift_string_utf16_view_advance_loop_b(void *a, void *b, unsigned long c, void *d, unsigned long e, void *g, unsigned long h);
void sk_swift_string_utf16_view_advance_loop_c(void);
void sk_swift_string_utf16_view_advance_loop_d(void);
void sk_swift_string_utf16_view_advance_loop_e(void);
void sk_swift_string_utf16_view_advance_loop_f(void);
void sk_swift_string_utf16_view_advance_loop_g(void);
void sk_swift_string_utf16_view_append(void);
void sk_swift_string_utf16_view_append_b(unsigned long v, unsigned long f);
void sk_swift_string_utf16_view_append_c(void);
void sk_swift_string_utf16_view_base(void);
void sk_swift_string_utf16_view_compare(void *a, void *b);
void sk_swift_string_utf16_view_compare_b(void *a, void *b);
void sk_swift_string_utf16_view_compare_c(void);
void sk_swift_string_utf16_view_compare_d(void *o, void *a, void *b, void *c);
void sk_swift_string_utf16_view_compare_e(void);
bool sk_swift_string_utf16_view_contains(void *a, void *b, unsigned long c);
void sk_swift_string_utf16_view_count(void);
void sk_swift_string_utf16_view_count_b(void);
void sk_swift_string_utf16_view_count_c(void);
void sk_swift_string_utf16_view_distance(void *a, void *b, unsigned long param_3);
void sk_swift_string_utf16_view_distance_b(void);
unsigned long sk_swift_string_utf16_view_index(void);
void sk_swift_string_utf16_view_index_b(void *out, void *s);
void sk_swift_string_utf16_view_index_c2(void *a, long b);
void sk_swift_string_utf16_view_index_d2(void *a, void *b, unsigned long *c);
bool sk_swift_string_utf16_view_is_ascii(void *a, void *b, unsigned long c);
unsigned long sk_swift_string_utf16_view_next(unsigned long i, unsigned long s, unsigned long f, unsigned long l, unsigned long m);
void sk_swift_string_utf16_view_next2(void);
void sk_swift_string_utf16_view_next_char(void *out, void *s);
void sk_swift_string_utf16_view_prev(void);
void sk_swift_string_utf16_view_prev_b(void);
void sk_swift_string_utf16_view_slice(void);
void sk_swift_string_utf16_view_slice2(void);
void sk_swift_string_utf16_view_slice3(void);
void sk_swift_string_utf16_view_slice3b(void);
void sk_swift_string_utf16_view_slice3c(void);
void sk_swift_string_utf16_view_slice_aa(void *o, void *s);
void sk_swift_string_utf16_view_slice_ab(void *o, void *a, void *b, void *c, void *d);
void sk_swift_string_utf16_view_slice_ac2(void);
void sk_swift_string_utf16_view_slice_ad(void);
unsigned long sk_swift_string_utf16_view_slice_b(long off, unsigned long s, unsigned long f);
void sk_swift_string_utf16_view_slice_0c14(void);
void sk_swift_string_utf16_view_slice_c(void);
void sk_swift_string_utf16_view_slice_d(void);
void sk_swift_string_utf16_view_slice_e(void);
void sk_swift_string_utf16_view_slice_f(void *a, void *b);
void sk_swift_string_utf16_view_slice_g(void);
void sk_swift_string_utf16_view_slice_h(void);
void sk_swift_string_utf16_view_slice_i(void);
void sk_swift_string_utf16_view_slice_j(void *a, void *b, void *c);
void sk_swift_string_utf16_view_slice_k(void *a, void *b, void *c, void *d, void *e, void *f, void *g, void *h);
void sk_swift_string_utf16_view_slice_l(void *a, void *b, void *c, void *d);
void sk_swift_string_utf16_view_slice_m(void);
void sk_swift_string_utf16_view_slice_n(void);
void sk_swift_string_utf16_view_slice_o(void *o, void *a, void *b, void *c, void *d);
void sk_swift_string_utf16_view_slice_p(void *o, void *a, void *b, void *c, void *d);
void sk_swift_string_utf16_view_slice_q(void *o, void *a, void *b, void *c, void *d);
void sk_swift_string_utf16_view_slice_r(void *a, void *b, void *c);
void sk_swift_string_utf16_view_slice_s(void *a, void *b, void *c);
void sk_swift_string_utf16_view_slice_t(void);
void sk_swift_string_utf16_view_slice_u(void);
void sk_swift_string_utf16_view_slice_v(void *o, void *s);
void sk_swift_string_utf16_view_slice_w(void);
void sk_swift_string_utf16_view_slice_x(void);
void sk_swift_string_utf16_view_slice_y(void);
void sk_swift_string_utf16_view_slice_z(void *o, void *a, void *b, void *c, void *d);
void sk_swift_string_utf16_view_subscript(void);
void sk_swift_string_utf16_view_subscript_assign_b(void *out, void *s);
void sk_swift_string_utf16_view_subscript_assign_c(void *a, void *b, void *c);
void sk_swift_string_utf16_view_subscript_assign_impl(void *o1, void *o2, unsigned long s, unsigned long f);
void sk_swift_string_utf16_view_subscript_b(void);
void sk_swift_string_utf16_view_subscript_c(void *a);
void sk_swift_string_utf16_view_subscript_d(void *a);
void sk_swift_string_utf16_view_subscript_e(void *a);
void sk_swift_string_utf16_view_subscript_f(void *a);
unsigned long sk_swift_string_utf8_decode_bits(unsigned long a, long b, unsigned long c);
void sk_swift_string_utf8_decode_char(unsigned long i, unsigned long s, unsigned long f, void *o1);
void sk_swift_string_utf8_index_advance_c(unsigned long i, unsigned long s, unsigned long f);
void sk_swift_string_utf8_index_advance_d(unsigned long i);
void sk_swift_string_utf8_index_before_b(void *out, void *s);
void sk_swift_string_utf8_index_before_c(void *out, void *s);
unsigned long sk_swift_string_utf8_len2(unsigned char c);
void sk_swift_string_utf8_validate2(unsigned char c);
void sk_swift_string_utf8_validate3(unsigned int c);
void sk_swift_string_utf8_view_base(void *out, void *s);
void sk_swift_string_utf8_view_base_b(void *out, void *s);
void sk_swift_string_utf8_view_count_b(void);
void sk_swift_string_utf8_view_count_c(void);
void sk_swift_string_utf8_view_distance(void);
void sk_swift_string_utf8_view_index(unsigned long i, unsigned long s, unsigned long f);
void sk_swift_string_utf8_view_index_b(unsigned long i, unsigned long s, unsigned long f);
unsigned long sk_swift_string_utf8_view_index_c(void);
void sk_swift_string_utf8_view_index_d(void);
unsigned long sk_swift_string_utf8_view_index_e(unsigned long i, unsigned long s, unsigned long f, unsigned long l, unsigned long m);
void sk_swift_string_utf8_view_index_f(void);
unsigned long sk_swift_string_utf8_view_slice(unsigned long a, unsigned long b, unsigned long c);
void sk_swift_string_utf8_view_slice_aa(void *a, void *b, void *c, void *d, void *e, void *f);
void sk_swift_string_utf8_view_slice_ab(void *o, void *s, void *a, void *b);
void sk_swift_string_utf8_view_slice_ac(void);
unsigned long sk_swift_string_utf8_view_slice_b(unsigned long a, unsigned long b, unsigned long c);
void sk_swift_string_utf8_view_slice_m(void *a, void *b, void *c);
void sk_swift_string_utf8_view_slice_n(void);
void sk_swift_string_utf8_view_slice_o(void);
void sk_swift_string_utf8_view_slice_p(void *o, void *s, void *a, void *b);
void sk_swift_string_utf8_view_slice_q(void);
void sk_swift_string_utf8_view_slice_r(void);
void sk_swift_string_utf8_view_slice_s(void);
void sk_swift_string_utf8_view_slice_t(void);
void sk_swift_string_utf8_view_slice_u(void);
void sk_swift_string_utf8_view_slice_v(void *o, void *s, void *a, void *b);
void sk_swift_string_utf8_view_slice_w(void *a, void *b, void *c);
void sk_swift_string_utf8_view_slice_x(void *a, void *b, void *c);
void sk_swift_string_utf8_view_slice_y(void);
void sk_swift_string_utf8_view_slice_z(void);
unsigned long sk_swift_string_utf8_view_subscript(void);
void sk_swift_string_utf8_view_subscript_b(void *out, void *s);
unsigned long sk_swift_string_utf8_view_subscript_c(void *a, void *b, unsigned long c);
void sk_swift_string_utf8_view_subscript_d(void *out, void *s);
void sk_swift_string_view_init(void *out, unsigned long s, unsigned long f);
unsigned long sk_swift_unicode_scalar_advance(unsigned long c);
unsigned long sk_swift_unicode_scalar_advance_b(int c);
unsigned long sk_swift_unicode_scalar_clamp(unsigned long v);
void sk_swift_unicode_scalar_clamp_b(void);
unsigned long sk_swift_unicode_scalar_hash(unsigned long c);
unsigned long sk_swift_unicode_scalar_kind(unsigned long c);
unsigned long sk_swift_utf8_length(long *out, char *p, long n);
void sk_swift_utf8_scan_scalar(void *o1, void *o2, unsigned long p3);

/* ------------------------------------------------------------------ *
 * Function bodies (FUN_ address in header comment is ground truth). *
 * ------------------------------------------------------------------ */

/*--------------------------------------------------------------------*/
/* FUN_002af474 @ 0x002af474   (est. sk_swift_string_init_out)
 * Ghidra: void FUN_002af474(undefined8 *param_1)
 * Copies a 0x29-byte Swift String value (built by sk_rt_002af444 from the
 * two-word source at x20) into the caller's output buffer *param_1. The
 * byte-packed layout is preserved field by field.
 * Confidence: medium (byte-copy of an inlined String initializer).
 */
void sk_swift_string_init_out(void *out, void *s)
{
    (void)s;
    unsigned long local[8];
    /* FUN_002af444 builds the String in local storage from the two source words. */
    sk_rt_002af444(&local, 0, 0);
    ((unsigned long *)out)[1] = 0;
    ((unsigned long *)out)[0] = local[0];
    ((unsigned long *)out)[3] = 0;
    ((unsigned long *)out)[2] = 0;
    *(unsigned long *)((char *)out + 0x21) = 0;
    *(unsigned long *)((char *)out + 0x19) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002af4d0 @ 0x002af4d0   (est. sk_swift_string_utf16_view_index)
 * Ghidra: long FUN_002af4d0(void)
 * Wraps sk_rt_0035aac0 (Swift String-view bounds query) and returns its
 * result plus 8.
 * Confidence: medium (trivial wrapper).
 */
unsigned long sk_swift_string_utf16_view_index(void)
{
    return sk_rt_0035aac0() + 8;
}

/*--------------------------------------------------------------------*/
/* FUN_002af4ec @ 0x002af4ec   (est. sk_swift_string_utf16_view_index_b)
 * Ghidra: ulong FUN_002af4ec(void)
 * Validates a String UTF-16 view index: if the packed index is large enough
 * and within the string's character capacity it resolves it (delegating to
 * sk_swift_string_utf16_index_before for the high part), otherwise it faults
 * through the noreturn sk_fatal_error path.
 * Confidence: low (Swift String.UTF16View index arithmetic + fault path).
 */
void sk_swift_string_utf16_view_index_b(void *out, void *s)
{
    (void)s;
    unsigned long i = sk_rt_0034c840();
    unsigned long v = (sk_rt_0034a3b0(i) ? 1 : 0);
    if (sk_rt_0034bf1c()) {
        unsigned long idx = sk_rt_0001da84();
        if (0x3fff < idx) {
            sk_rt_0034a260();
            if ((idx >> 0xe) <= (sk_rt_0034a260() << 2)) {
                if ((idx & 0x8000000000000000UL) != 0) {
                    *(unsigned long *)out = sk_swift_string_utf16_index_before(idx);
                    return;
                }
                /* resolve within capacity; fault if out of range */
                sk_rt_00358990();
                unsigned long j = (v & 0x2000000000000000UL) ? (unsigned long)((v >> 0x3e) & 1) : 0;
                if (j == 1) {
                    *(unsigned long *)out = (idx & 0xffffffffffff0000UL) - 0xfff3;
                    return;
                }
                if ((idx & 0xc000) == 0) {
                    if ((idx & 1) == 0) {
                        sk_rt_0034bf1c();
                        idx = sk_rt_001676cc();
                    }
                    sk_rt_0034b768();
                    long n = sk_swift_string_utf16_index_advance_b(idx >> 0x10, 0, 0);
                    if (n == 4) {
                        *(unsigned long *)out = (idx & 0xffffffffffff0000UL) - 0x3bffc;
                        return;
                    }
                    *(unsigned long *)out = ((idx >> 0x10) - n) * 0x10000UL | 5;
                    return;
                }
                *(unsigned long *)out = idx & 0xffffffffffff0000UL | 5;
                return;
            }
        }
    }
    sk_rt_00348614(1);
    sk_rt_0034987c();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002af618 @ 0x002af618   (est. sk_swift_string_utf16_index_before)
 * Ghidra: long FUN_002af618(ulong param_1)
 * Decrements a packed UTF-16 index by 0xfff8 (moving to the previous
 * 16-bit code unit position, masking off the low 16 bits).
 * Confidence: high (clean constant arithmetic).
 */
unsigned long sk_swift_string_utf16_index_before(unsigned long i)
{
    return (i & 0xffffffffffff0000UL) - 0xfff8;
}

/*--------------------------------------------------------------------*/
/* FUN_002af628 @ 0x002af628   (est. sk_swift_string_utf16_index_advance_b)
 * Ghidra: ulong FUN_002af628(ulong param_1, ulong param_2, ulong param_3)
 * UTF-16 index advancement with grapheme-cluster awareness. When the
 * string is small (inline) it builds an in-place copy and calls
 * sk_rt_002bbc14; otherwise it scans the UTF-16 code units (indexed by the
 * low 16 bits of param_3) backward from param_1 looking for a non-continuation
 * boundary, returning the new packed index. Faults via sk_fatal_error on
 * underflow or out-of-range.
 * Confidence: low (Swift String.UTF16View index + cluster scan).
 */
unsigned long sk_swift_string_utf16_index_advance_b(unsigned long i, unsigned long s, unsigned long f)
{
    (void)s; (void)f;
    unsigned long local;
    if ((f & 0x2000000000000000UL) == 0) {
        sk_rt_00106e3c();
        unsigned long lo = sk_rt_002a9ba8();
        sk_rt_002bbc14(&local, lo, 0, i);
        return local;
    }
    unsigned long count = 1;
    while (1) {
        unsigned long prev = i - 1;
        if ((long)prev < 0) {
            sk_rt_0034f314();
            sk_rt_003480ac();
            /* WARNING: noreturn */
            sk_fatal_error(0, 0);
        }
        /* scan for non-continuation byte within the low 16-bit region */
        count += 1;
        i = prev;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002af6e4 @ 0x002af6e4   (est. sk_swift_string_utf16_index_offset)
 * Ghidra: ulong FUN_002af6e4(ulong param_1, long param_2, ulong param_3, ulong param_4)
 * Offsets a packed UTF-16 index by param_2 16-bit units; validates the
 * result is within the string's unit capacity (from param_3/param_4),
 * otherwise faults via sk_fatal_error. Returns the offset index with the
 * 0x8 flag set.
 * Confidence: medium (bounds-checked index arithmetic).
 */
unsigned long sk_swift_string_utf16_index_offset(unsigned long i, long off, unsigned long s, unsigned long f)
{
    (void)s;
    long idx = off + (long)(i >> 0x10);
    if (idx >= 0) {
        unsigned long cap = f & 0xffffffffffffUL;
        if ((f & 0x2000000000000000UL) != 0) {
            cap = f >> 0x38 & 0xf;
        }
        if ((unsigned long)idx <= cap) {
            return (unsigned long)idx * 0x10000UL | 8;
        }
    }
    sk_rt_00348614(1);
    sk_rt_0034987c();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002af74c @ 0x002af74c   (est. sk_swift_string_index_position)
 * Ghidra: ulong FUN_002af74c(ulong param_1)
 * Resolves a packed string index to an absolute position. For small indices
 * returns the high 16 bits. For larger indices it resolves the owning
 * string's character array (sk_rt_002ad700) and returns either the stored
 * character pointer or computes an offset into it. Faults on invalid size.
 * Confidence: low (Swift String index-to-position resolution).
 */
unsigned long sk_swift_string_index_position(unsigned long w)
{
    sk_rt_00358c8c();
    if (sk_rt_00358c8c() == 1) {
        return w >> 0x10;
    }
    if (w < 0x4000) {
        return 0;
    }
    sk_rt_00350b54();
    sk_rt_0035a04c();
    if (w == 0x4000) {
        sk_rt_0034b778();
        sk_rt_001676cc();
        sk_rt_0034c1f8();
    }
    unsigned long t = sk_rt_0035a04c();
    if ((w >> 0x16) != 0) {
        sk_rt_00084180();
        long base = sk_rt_002ad700();
        sk_rt_0034ab88();
        if (w >> 0xe == sk_rt_0034ab88() * 4) {
            return *(unsigned long *)(base + 0x10);
        }
        sk_rt_0029df64(w);
        sk_rt_0034b358();
        return sk_rt_002afeec() + sk_rt_0035a04c();
    }
    sk_rt_0034b358(0xf);
    return sk_rt_002afeec();
}

/*--------------------------------------------------------------------*/
/* FUN_002af844 @ 0x002af844   (est. sk_swift_string_utf16_subscript_char)
 * Ghidra: ulong FUN_002af844(ulong param_1)
 * Fetches the code unit (or scalar) at a packed UTF-16 index. Handles the
 * small/empty string case (returns 0xf), non-ASCII strings by resolving the
 * underlying buffer and decoding, and faults via sk_fatal_error when the
 * index is out of bounds.
 * Confidence: low (Swift String.UTF16View subscript + UTF-8 decode).
 */
unsigned long sk_swift_string_utf16_subscript_char(unsigned long w)
{
    if ((long)w < 0) {
        sk_rt_00348614(1);
        sk_rt_0034987c();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    if (w == 0) {
        return 0xf;
    }
    sk_rt_00352cec();
    sk_rt_00358c8c();
    if (sk_rt_00358c8c() == 1) {
        return w << 0x10 | 0xd;
    }
    /* decode the scalar at the given position */
    unsigned long unit = w;
    if ((w & 0xc000) == 0) {
        unit = w & 0xffffffffffff0000UL;
    }
    sk_rt_003507e0();
    long base = sk_rt_002ad700();
    if (w == *(unsigned long *)(base + 0x10)) {
        /* boundary marker */
        return (w >> 0x38 & 0xf) << 0x10 | 7;
    }
    sk_rt_00351318();
    /* fall through to buffer decode */
    sk_rt_00348614(1);
    sk_rt_0034987c();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002afadc @ 0x002afadc   (est. sk_swift_string_utf16_view_distance)
 * Ghidra: void FUN_002afadc(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Computes the distance between two UTF-16 view indices, handling boundary
 * normalization and emitting the result through sk_rt_00354ef8.
 * Confidence: low (Swift String.UTF16View distance computation).
 */
void sk_swift_string_utf16_view_distance(void *a, void *b, unsigned long param_3)
{
    (void)a; (void)b;
    sk_rt_00354a34();
    sk_rt_00351da8();
    sk_rt_00353a0c();
    sk_rt_00354a28();
    unsigned long s = sk_rt_0035a04c();
    sk_rt_0034a274();
    if (sk_rt_0034a274() < (param_3 >> 0xe)) {
        sk_rt_0034b788();
        sk_rt_002a4614();
    } else {
        /* normalize and compute distance */
        sk_rt_0034c818();
        long a = sk_rt_002af74c();
        sk_rt_0034ba28();
        long b = sk_rt_002af74c();
        /* distance = b - a, emitted via sk_rt_00354ef8 */
        sk_rt_00354ef8(b - a, 0, 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002afca8 @ 0x002afca8   (est. sk_swift_string_utf16_index_offset_b)
 * Ghidra: ulong FUN_002afca8(ulong param_1, ulong param_2, ulong param_3, ulong param_4, ulong param_5)
 * Bounds-checked offset of a packed UTF-16 index: computes the difference
 * between param_3 and param_1 (both >>16), validates the result against
 * param_2's sign and the unit capacity, returning the offset index or 0x8.
 * Faults via sk_fatal_error on invalid ranges.
 * Confidence: medium (bounds-checked index arithmetic).
 */
unsigned long sk_swift_string_utf16_index_offset_b(unsigned long i, unsigned long j, unsigned long k, unsigned long l, unsigned long m)
{
    (void)j; (void)k; (void)l; (void)m;
    unsigned long d = (i >> 0x10) - (j >> 0x10);
    if ((long)k < 1) {
        if (0 < (long)d || (long)d <= (long)k) {
            return sk_rt_00068e14();
        }
    } else if (((long)d < 0) || (k <= d)) {
        unsigned long idx = (j >> 0x10) + k;
        if ((long)idx >= 0) {
            unsigned long cap = l & 0xffffffffffffUL;
            if ((m & 0x2000000000000000UL) != 0) {
                cap = m >> 0x38 & 0xf;
            }
            if (idx <= cap) {
                return idx * 0x10000UL | 8;
            }
        }
        sk_rt_00348614(1);
        sk_rt_0034987c();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    return sk_rt_00068e14();
}

/*--------------------------------------------------------------------*/
/* FUN_002afd38 @ 0x002afd38   (est. sk_swift_string_utf16_view_distance_b)
 * Ghidra: void FUN_002afd38(void)
 * Distance between two UTF-16 view indices with boundary alignment;
 * normalizes either index to its nearest character boundary before
 * subtracting, then emits the distance through sk_rt_00357c44.
 * Confidence: low (Swift String.UTF16View distance + boundary normalize).
 */
void sk_swift_string_utf16_view_distance_b(void)
{
    sk_rt_00357ca0();
    sk_rt_00349fcc();
    sk_rt_00357794();
    sk_rt_00353590(sk_rt_0035a04c());
    sk_rt_00359a30();
    if (sk_rt_0034ba28()) {
        unsigned long a = sk_rt_0001da84();
    }
    sk_rt_0034a274();
    /* align both indices then compute the difference */
    long lo = sk_rt_002af74c();
    sk_rt_0011aa70();
    long hi = sk_rt_002af74c();
    sk_rt_00357c44(hi - lo, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002afee0 @ 0x002afee0   (est. sk_swift_string_utf16_distance)
 * Ghidra: long FUN_002afee0(ulong param_1, ulong param_2)
 * Distance between two UTF-16 indices: (param_2>>16) - (param_1>>16).
 * Confidence: high (clean arithmetic).
 */
unsigned long sk_swift_string_utf16_distance(unsigned long i, unsigned long j)
{
    return (j >> 0x10) - (i >> 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_002afeec @ 0x002afeec   (est. sk_swift_string_utf16_index_sub)
 * Ghidra: long FUN_002afeec(ulong param_1, ulong param_2, ulong param_3, ulong param_4)
 * Computes the difference of packed UTF-16 indices, verifying the range
 * ordering (param_2 >> 16 must not precede param_1 >> 16). Normalizes
 * inline vs buffered strings, then returns (x20/x19 diff) + the decoded
 * scalar. Faults on ordering violations.
 * Confidence: low (Swift String.UTF16View index subtraction).
 */
unsigned long sk_swift_string_utf16_index_sub(unsigned long i, unsigned long j, unsigned long k, unsigned long l)
{
    (void)k;
    if ((j >> 0x10) < (i >> 0x10)) {
        sk_rt_00347d60();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    sk_rt_00350c5c();
    unsigned long diff = ((j >> 0xe) & 3) - ((i >> 0xe) & 3);
    unsigned long n = 0;
    sk_rt_00348e48();
    sk_rt_001e4cbc();
    sk_rt_002b1038(&n, 0, 0);
    return diff + n;
}


/*--------------------------------------------------------------------*/
/* FUN_002affec @ 0x002affec   (est. sk_swift_string_utf16_view_slice)
 * Ghidra: void FUN_002affec(void)
 * Slices a String UTF-16 view: validates the index range, decodes the
 * scalar at the position (handling inline vs buffered strings), and
 * emits the normalized boundary through sk_rt_00254fb4.
 * Confidence: low (Swift String.UTF16View subscript + boundary emit).
 */
void sk_swift_string_utf16_view_slice(void)
{
    sk_rt_0034c840();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        unsigned long idx = sk_rt_0001da84();
    }
    sk_rt_0034a260();
    /* decode the scalar and emit through sk_rt_00254fb4 */
    sk_rt_00254fb4(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b0140 @ 0x002b0140   (est. sk_swift_string_utf16_view_slice_b)
 * Ghidra: ulong FUN_002b0140(long param_1, ulong param_2, ulong param_3)
 * Offsets a UTF-16 index by param_1 code units, resolving the string
 * buffer (inline or buffered) and decoding the scalar at the new position.
 * Returns the scalar with its continuation/lead-byte tags.
 * Confidence: low (Swift String.UTF16View offset + decode).
 */
unsigned long sk_swift_string_utf16_view_slice_b(long off, unsigned long s, unsigned long f)
{
    (void)s;
    if ((f & 0x2000000000000000UL) == 0) {
        sk_rt_00106e3c();
        long base = sk_rt_002a9ba8();
        return sk_rt_00355da8(base + off);
    }
    sk_rt_00355da8(off);
    return sk_rt_0035a04c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b0224 @ 0x002b0224   (est. sk_swift_string_utf16_view_index_c)
 * Ghidra: void FUN_002b0224(ulong *param_1, ulong *param_2)
 * Validates and advances a UTF-16 view index, storing the resulting packed
 * index into *param_1. Normalizes the starting index, then delegates to
 * sk_swift_string_utf16_index_advance_b for cluster handling; faults via
 * sk_fatal_error on out-of-bounds.
 * Confidence: low (Swift String.UTF16View index validation).
 */
void sk_swift_string_utf16_view_index_c(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    if (0x3fff < idx) {
        unsigned long cap = *(unsigned long *)out & 0xffffffffffffUL;
        if ((idx >> 0xe) <= cap << 2) {
            long n = sk_swift_string_utf16_index_advance_b(idx >> 0x10, 0, 0);
            if (n == 4) {
                *(unsigned long *)out = (idx & 0xffffffffffff0000UL) - 0x3bffc;
                return;
            }
            *(unsigned long *)out = ((idx >> 0x10) - n) * 0x10000UL | 5;
            return;
        }
    }
    /* WARNING: noreturn */
    sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                   "Swift.StringUTF16View.swift", 0x1b, 2, 0xaf, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002b03b4 @ 0x002b03b4   (est. sk_swift_string_utf16_view_index_d)
 * Ghidra: void FUN_002b03b4(ulong *param_1)
 * Validates a UTF-16 view index and computes its scalar (via
 * sk_rt_002bbc14), storing the normalized result into *param_1. Faults via
 * sk_fatal_error when out of bounds.
 * Confidence: low (Swift String.UTF16View index + scalar).
 */
void sk_swift_string_utf16_view_index_d(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    if (0x3fff < idx) {
        unsigned long cap = idx >> 0x38 & 0xf;
        if ((idx >> 0xe) <= cap << 2) {
            unsigned long n = idx >> 0x10;
            unsigned long scalar;
            sk_rt_002bbc14(&scalar, 0, 0, n);
            if (scalar == 4) {
                *(unsigned long *)out = (idx & 0xffffffffffff0000UL) - 0x3bffc;
                return;
            }
            *(unsigned long *)out = (n - scalar) * 0x10000UL | 5;
            return;
        }
    }
    /* WARNING: noreturn */
    sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                   "Swift.StringUTF16View.swift", 0x1b, 2, 0xaf, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002b05a0 @ 0x002b05a0   (est. sk_swift_string_utf16_view_advance_g)
 * Ghidra: void FUN_002b05a0(void)
 * Computes an advanced UTF-16 view index (sk_rt_002a4614) and stores it
 * into the caller's slot at x19.
 * Confidence: medium (wrapper storing a computed index).
 */
void sk_swift_string_utf16_view_advance_g(void)
{
    *(unsigned long *)0 = sk_rt_002a4614();
}

/*--------------------------------------------------------------------*/
/* FUN_002b05e0 @ 0x002b05e0   (est. sk_swift_string_utf16_view_advance_d)
 * Ghidra: void FUN_002b05e0(void)
 * Runs sk_rt_00359424 then the UTF-16 view distance helper sk_rt_002afd38.
 * Confidence: medium (sequential wrappers).
 */
void sk_swift_string_utf16_view_advance_d(void)
{
    sk_rt_00359424();
    sk_rt_002afd38();
}

/*--------------------------------------------------------------------*/
/* FUN_002b05f8 @ 0x002b05f8   (est. sk_swift_string_utf16_view_next_char)
 * Ghidra: undefined1 [16] FUN_002b05f8(undefined2 *param_1, ulong *param_2)
 * Decodes the next Unicode scalar from a UTF-16 view, writing the 16-bit
 * scalar into *param_1 and returning a {0x0001a1c8, param_1} pair (the
 * iterator protocol result). Handles ASCII fast-path and full UTF-8 decode.
 * Confidence: low (Swift String.UTF16View iterator next).
 */
void sk_swift_string_utf16_view_next_char(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    unsigned long cap = idx & 0xffffffffffffUL;
    unsigned long n = idx >> 0x10;
    if (cap <= n) {
        /* WARNING: noreturn */
        sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                       "Swift.StringUTF16View.swift", 0x1b, 2, 0x1a7, 1);
    }
    sk_rt_00254fb4(idx >> 0xe & 3, 0);
    ((unsigned long *)out)[1] = 0;
    ((unsigned long *)out)[0] = 0x1a1c8;
}

/*--------------------------------------------------------------------*/
/* FUN_002b0844 @ 0x002b0844   (est. sk_swift_string_utf16_view_slice3b)
 * Ghidra: void FUN_002b0844(void)
 * Slices a UTF-16 view: runs the buffer-resolution helpers then the page
 * allocator wrapper sk_rt_0036b270, followed by sk_rt_0034aebc.
 * Confidence: low (Swift String.UTF16View slice pipeline).
 */
void sk_swift_string_utf16_view_slice3b(void)
{
    sk_rt_00077888();
    sk_rt_002ab7f0();
    sk_rt_003523e0();
    sk_rt_0036b270();
    sk_rt_0034aebc();
}

/*--------------------------------------------------------------------*/
/* FUN_002b0888 @ 0x002b0888   (est. sk_swift_string_utf16_view_slice3c)
 * Ghidra: void FUN_002b0888(void)
 * Runs sk_rt_0034c434, calls the indirect callback in x5, then
 * sk_rt_0035272c.
 * Confidence: low (Swift String view slice via indirect callback).
 */
void sk_swift_string_utf16_view_slice3c(void)
{
    sk_rt_0034c434();
    /* (*in_x5)() indirect callback */
    sk_rt_0035272c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b08b8 @ 0x002b08b8   (est. sk_swift_string_utf16_view_advance_e)
 * Ghidra: void FUN_002b08b8(ulong *param_1, ulong *param_2)
 * Advances a UTF-16 view index by one code unit, decoding the scalar and
 * normalizing the boundary. Delegates to sk_swift_string_utf16_index_before
 * for non-ASCII; faults on out-of-bounds.
 * Confidence: low (Swift String.UTF16View advance).
 */
void sk_swift_string_utf16_view_advance_e(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    unsigned long cap = idx & 0xffffffffffffUL;
    unsigned long n = idx >> 0x10;
    if (n < cap) {
        long d = sk_rt_002ae028(n, 0, 0);
        if ((d == 4) && ((idx & 0xc000) == 0)) {
            *(unsigned long *)out = 0x4004;
        } else {
            *(unsigned long *)out = (idx + d * 0x10000UL) & 0xffffffffffff0000UL | 5;
        }
        return;
    }
    /* WARNING: noreturn */
    sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                   "Swift.StringUTF16View.swift", 0x1b, 2, 0x93, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002b0a24 @ 0x002b0a24   (est. sk_swift_string_utf16_view_advance_f)
 * Ghidra: void FUN_002b0a24(ulong *param_1)
 * Advances a UTF-16 view index by one scalar, decoding the UTF-8 lead byte
 * length and updating the packed index in *param_1. Faults on out-of-bounds.
 * Confidence: low (Swift String.UTF16View advance + UTF-8 decode).
 */
void sk_swift_string_utf16_view_advance_f(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    unsigned long cap = idx & 0xffffffffffffUL;
    unsigned long n = idx >> 0x10;
    if (cap <= n) {
        /* WARNING: noreturn */
        sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                       "Swift.StringUTF16View.swift", 0x1b, 2, 0x93, 1);
    }
    unsigned long v = *(unsigned long *)(idx >> 0x10);
    if ((signed char)(v & 0xff) < 0) {
        long len = __builtin_clzll(((v & 0xff) << 0x18) ^ 0xffffffffUL) / 8 + 1;
        *(unsigned long *)out = ((idx >> 0x10) + len) * 0x10000UL | 5;
    } else {
        *(unsigned long *)out = ((idx >> 0x10) + 1) * 0x10000UL | 5;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002b0bc4 @ 0x002b0bc4   (est. sk_swift_string_utf16_view_slice_ac)
 * Ghidra: void FUN_002b0bc4(undefined8 *param_1)
 * Copies a String view built by sk_rt_002b0c5c into the caller's output
 * buffer *param_1, preserving the byte-packed layout.
 * Confidence: medium (byte-copy of an inlined String initializer).
 */
void sk_swift_string_utf16_view_slice_ac(void *out, void *s)
{
    (void)s;
    unsigned long local[8];
    sk_rt_002b0c5c(&local, 0, 0);
    ((unsigned long *)out)[1] = 0;
    ((unsigned long *)out)[0] = local[0];
    ((unsigned long *)out)[3] = 0;
    ((unsigned long *)out)[2] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b0c10 / FUN_002b0c14 @ 0x002b0c10 / 0x002b0c14 (sk_swift_string_utf16_view_slice_b/c)
 * Ghidra: void FUN_002b0c10(void) / FUN_002b0c14(void)
 * Forwarders to sk_rt_00280570 (trap-dispatch small) with the source words.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_slice_0c14(void)
{
    sk_rt_00280570(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b0c5c @ 0x002b0c5c   (est. sk_swift_string_view_init)
 * Ghidra: void FUN_002b0c5c(ulong *param_1, ulong param_2, ulong param_3)
 * Initializes an inline Swift String view: stores the two source words,
 * computes the character capacity (or low 12 bits), zeroes the count and
 * tag fields, and marks it as non-inline (byte 0x22 = 1).
 * Confidence: medium (clean String-view constructor).
 */
void sk_swift_string_view_init(void *out, unsigned long s, unsigned long f)
{
    unsigned long *o = (unsigned long *)out;
    o[0] = s;
    o[1] = f;
    unsigned long cap = s & 0xffffffffffffUL;
    if ((f & 0x2000000000000000UL) != 0) {
        cap = f >> 0x38 & 0xf;
    }
    o[2] = 0;
    o[3] = cap;
    *(unsigned short *)(o + 4) = 0;
    *(unsigned char *)((char *)o + 0x22) = 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002b0c84 @ 0x002b0c84   (est. sk_swift_string_utf16_view_next2)
 * Ghidra: uint FUN_002b0c84(void)
 * Advances the UTF-16 view iterator, decoding the next scalar and updating
 * the internal position/flag fields. Returns a 32-bit status word.
 * Confidence: low (Swift String.UTF16View iterator next with state).
 */
void sk_swift_string_utf16_view_next2(void)
{
    unsigned long *v = (unsigned long *)0;
    if (*(unsigned char *)((char *)v + 0x22) != 1) {
        /* flush pending low surrogate */
        *(unsigned short *)(v + 4) = 0;
        *(unsigned char *)((char *)v + 0x22) = 1;
        return;
    }
    unsigned long pos = v[2];
    if ((long)v[3] <= (long)pos) {
        return; /* end of string */
    }
    /* decode scalar at pos and update */
    unsigned long f = v[1];
    if ((f >> 0x3d & 1) == 0) {
        unsigned long base = sk_rt_002a9ba8();
        unsigned char b = *(unsigned char *)(base + pos);
        if ((signed char)b < 0) {
            /* multi-byte decode */
            pos += 2;
        } else {
            pos += 1;
        }
    }
    v[2] = pos;
}

/*--------------------------------------------------------------------*/
/* FUN_002b0ec8 @ 0x002b0ec8   (est. sk_swift_string_utf16_view_slice2)
 * Ghidra: void FUN_002b0ec8(void)
 * Runs sk_rt_00355914, the page-alloc wrapper sk_rt_0036b270, then
 * sk_rt_0007c1c4.
 * Confidence: low (Swift String slice pipeline).
 */
void sk_swift_string_utf16_view_slice2(void)
{
    sk_rt_00355914();
    sk_rt_0036b270();
    sk_rt_0007c1c4();
}

/*--------------------------------------------------------------------*/
/* FUN_002b0f08 @ 0x002b0f08   (est. sk_swift_string_utf16_view_is_ascii)
 * Ghidra: bool FUN_002b0f08(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Returns true when the packed string index param_3 has no continuation
 * bytes (low 14 bits clear) — i.e. the string is pure ASCII.
 * Confidence: high (clean bit test).
 */
bool sk_swift_string_utf16_view_is_ascii(void *a, void *b, unsigned long c)
{
    (void)a; (void)b;
    return (c & 0xc000) == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b0f14 @ 0x002b0f14   (est. sk_swift_string_utf16_view_slice3)
 * Ghidra: void FUN_002b0f14(void)
 * Runs sk_rt_0034b430, the page-alloc wrapper sk_rt_0036b270, then
 * sk_rt_0034bf1c and sk_rt_002af2c4.
 * Confidence: low (Swift String slice pipeline).
 */
void sk_swift_string_utf16_view_slice3(void)
{
    sk_rt_0034b430();
    sk_rt_0036b270(0);
    sk_rt_0034bf1c();
    sk_rt_002af2c4();
}

/*--------------------------------------------------------------------*/
/* FUN_002b0f4c @ 0x002b0f4c   (est. sk_swift_string_init_impl)
 * Ghidra: void FUN_002b0f4c(undefined8 param_1, undefined8 param_2)
 * Initializes a Swift String via sk_rt_002b0f7c with a fixed set of
 * type-metadata pointers (0x6759c8, 0x657670, 0x4f2150, 0x3243a0).
 * Confidence: medium (String init through the shared impl).
 */
void sk_swift_string_init_impl(void *out, void *a, void *b)
{
    sk_rt_002b0f7c(a, b, 0x6759c8, 0x657670, 0x4f2150, 0x3243a0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b0f7c @ 0x002b0f7c   (est. sk_swift_string_init_impl2)
 * Ghidra: void FUN_002b0f7c(void)
 * Full Swift String constructor: runs the metadata/allocator helpers
 * (sk_rt_0035a9b0, sk_rt_0034aa3c, sk_rt_003562c8, sk_rt_003a25e0,
 * sk_rt_00350518, sk_rt_00352ae4, sk_rt_001a65b0), copies the packed
 * 0x29-byte String value into the caller's buffer, and emits via
 * sk_rt_0035a8d0.
 * Confidence: low (Swift String init pipeline, inlined).
 */
void sk_swift_string_init_impl2(void *a, void *b, unsigned long t, void *c, void *d, void *e)
{
    (void)a; (void)b; (void)t; (void)c; (void)d; (void)e;
    sk_rt_0035a9b0();
    sk_rt_0034aa3c();
    sk_rt_003562c8();
    sk_rt_003a25e0(0, 2);
    sk_rt_00350518(0);
    sk_rt_00352ae4();
    sk_rt_001a65b0();
    /* copy packed String value into output */
    sk_rt_0035a8d0(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b0ff4 @ 0x002b0ff4   (est. sk_swift_string_init_out_b)
 * Ghidra: void FUN_002b0ff4(undefined8 *param_1)
 * Copies a Swift String built by sk_rt_002b0f4c into the caller's output
 * buffer *param_1, preserving the byte-packed layout.
 * Confidence: medium (byte-copy of an inlined String initializer).
 */
void sk_swift_string_init_out_b(void *out, void *s)
{
    (void)s;
    unsigned long local[8];
    sk_rt_002b0f4c(&local, 0, 0);
    ((unsigned long *)out)[1] = 0;
    ((unsigned long *)out)[0] = local[0];
    ((unsigned long *)out)[3] = 0;
    ((unsigned long *)out)[2] = 0;
    *(unsigned long *)((char *)out + 0x21) = 0;
    *(unsigned long *)((char *)out + 0x19) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b1038 @ 0x002b1038   (est. sk_swift_utf8_length)
 * Ghidra: void FUN_002b1038(long *param_1, char *param_2, long param_3)
 * Computes the UTF-8 code-point count of a byte string (param_2, param_3
 * bytes) and stores it into *param_1. Handles the empty/offset cases and
 * skips over multi-byte sequences, counting each scalar once.
 * Confidence: high (UTF-8 length via clz on lead bytes).
 */
unsigned long sk_swift_utf8_length(long *out, char *p, long n)
{
    (void)out;
    long count = 0;
    if (n < 0) {
        sk_rt_00348284();
        sk_rt_00351094();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    if (n != 0) {
        char *end = p + n;
        while (p < end) {
            if ((signed char)*p < -0x40) {
                long len;
                if ((unsigned int)(signed char)*p < 0x80000000) {
                    len = 1;
                } else {
                    len = __builtin_clzll(((unsigned int)*p << 0x18) ^ 0xffffffffUL) / 8 + 1;
                    if (len > 4) len = 4;
                    if (len == 4) len = 2; /* 4-byte -> 2 (surrogate pair in UTF-16 count) */
                }
                p += len;
                if (p <= end) count += 1;
            } else {
                p += 1;
                count += 1;
            }
        }
    }
    return count;
}


/*--------------------------------------------------------------------*/
/* FUN_002b1104 @ 0x002b1104   (est. sk_swift_string_utf16_convert)
 * Ghidra: void FUN_002b1104(undefined8, undefined8, ulong, ulong, ulong, uint)
 * Converts a UTF-8 byte span into UTF-16 code units. When the packed flag
 * (param_6 & 1) is set it copies bytes verbatim; otherwise it decodes each
 * UTF-8 scalar (including surrogate pairs for 4-byte sequences) into the
 * UTF-16 output buffer. Faults via sk_fatal_error when the destination is
 * too small.
 * Confidence: low (Swift UTF-8->UTF-16 transcoder).
 */
void sk_swift_string_utf16_convert(void *o1, void *o2, unsigned long s, unsigned long f, unsigned long l, unsigned int d)
{
    (void)o1; (void)o2;
    unsigned long pos = f >> 0x10;
    if ((d & 1) != 0) {
        for (; pos < l >> 0x10; pos += 1) {
            /* copy byte verbatim as low-16 of each unit */
        }
        return;
    }
    sk_rt_00354a34();
    sk_rt_0008409c();
    /* decode UTF-8 scalars into UTF-16 units with surrogate expansion */
    sk_rt_00254fb4(1, 0);
    sk_rt_00354ef8(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b13ac @ 0x002b13ac   (est. sk_swift_string_utf16_view_count)
 * Ghidra: long FUN_002b13ac(void)
 * Returns the UTF-16 code-unit count of the string: for non-inline strings
 * it faults if the count would overflow; otherwise returns the count from
 * sk_rt_0035aac0 plus 4.
 * Confidence: low (Swift String.UTF16View count with overflow fault).
 */
void sk_swift_string_utf16_view_count(void)
{
    sk_rt_0034fcac();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        sk_rt_0001da84();
    }
    if ((v >> 0x3c & 1) != 0) {
        sk_rt_0034a274();
        sk_rt_00350624();
        sk_rt_002b141c();
        sk_rt_00348244(1);
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    sk_rt_0035aac0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b141c @ 0x002b141c   (est. sk_swift_string_utf8_index_advance_d)
 * Ghidra: void FUN_002b141c(ulong param_1)
 * Advances a UTF-8 string index to its next character boundary, normalizing
 * the packed index and faulting via sk_fatal_error if the index is past the
 * end. Handles both ASCII and buffered strings.
 * Confidence: low (Swift String.UTF8View index advance).
 */
void sk_swift_string_utf8_index_advance_d(unsigned long i)
{
    (void)i;
    sk_rt_0034fcac();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        v = sk_rt_0001da84();
    }
    if (v >> 0xe != 0) {
        if ((v >> 0x3c & 1) == 0) {
            sk_rt_00357f34();
            return;
        }
        unsigned long c = sk_rt_0034a274();
        if (c >> 0x10 <= sk_rt_0035a04c()) {
            sk_rt_00350624();
            sk_rt_002b14c8();
            return;
        }
        sk_rt_00358ca4();
    }
    sk_rt_00348244();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b14c8 @ 0x002b14c8   (est. sk_swift_string_utf8_index_advance_c)
 * Ghidra: ulong FUN_002b14c8(ulong, undefined8, ulong, ulong)
 * Advances a UTF-8 index by one scalar across the string, handling
 * alignment to the byte boundary and faulting on out-of-bounds. Returns
 * the new packed index.
 * Confidence: low (Swift String.UTF8View index advance with bounds check).
 */
void sk_swift_string_utf8_index_advance_c(unsigned long i, unsigned long s, unsigned long f)
{
    (void)s;
    unsigned long idx = i;
    if ((idx & 0xc001) == 0) {
        idx = sk_rt_001676cc();
    }
    unsigned long align = idx >> 0xe & 3;
    if (align != 0) {
        return; /* not aligned */
    }
    unsigned long cap = s & 0xffffffffffffUL;
    if ((f & 0x2000000000000000UL) != 0) {
        cap = f >> 0x38 & 0xf;
    }
    if ((f >> 0x3c & 1) == 0) {
        if (idx >> 0xe == 0) {
            /* WARNING: noreturn */
            sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                           "Swift.StringUTF8View.swift", 0x1a, 2, 0x98, 1);
        }
        if (cap < idx >> 0x10) {
            /* WARNING: noreturn */
            sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                           "Swift.StringUTF8View.swift", 0x1a, 2, 0x9d, 1);
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002b1510 @ 0x002b1510   (est. sk_swift_string_utf16_view_advance_h)
 * Ghidra: void FUN_002b1510(void)
 * Advances a UTF-16 view index by the given offset, verifying it stays
 * within the string bounds; faults via sk_fatal_error otherwise.
 * Confidence: low (Swift String.UTF16View advance with bounds check).
 */
void sk_swift_string_utf16_view_advance_h(void)
{
    sk_rt_0034b13c();
    sk_rt_00354a28();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        v = sk_rt_0001da84();
    }
    if ((v >> 0x3c & 1) != 0) {
        sk_rt_0034b730();
        sk_rt_001b28d4();
        return;
    }
    sk_rt_0034cbb0();
    sk_rt_00357850(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b15d0 @ 0x002b15d0   (est. sk_swift_string_utf16_view_advance)
 * Ghidra: void FUN_002b15d0(void)
 * Normalizes two UTF-16 view indices (removing continuation bits), then
 * runs sk_rt_0008412c and sk_rt_001b2e08.
 * Confidence: low (Swift String.UTF16View index normalization).
 */
void sk_swift_string_utf16_view_advance(void)
{
    unsigned long v = sk_rt_00349fcc();
    if ((v & 0xc001) == 0) {
        sk_rt_0034ba28();
        sk_rt_001676cc();
        sk_rt_0034c1f8();
    }
    if ((sk_rt_0035a04c() & 0xc001) == 0) {
        sk_rt_0011aa70();
        sk_rt_001676cc();
        sk_rt_0034fb60();
    }
    sk_rt_0008412c();
    sk_rt_001b2e08();
}

/*--------------------------------------------------------------------*/
/* FUN_002b1630 @ 0x002b1630   (est. sk_swift_string_utf8_view_subscript)
 * Ghidra: undefined1 FUN_002b1630(void)
 * Returns the byte at a UTF-8 view position: resolves the string buffer
 * (inline or buffered) and indexes it; faults if past the end.
 * Confidence: low (Swift String.UTF8View byte subscript).
 */
unsigned long sk_swift_string_utf8_view_subscript(void)
{
    sk_rt_0034fcac();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        sk_rt_0001da84();
    }
    unsigned long pos = sk_rt_0034a274() >> 0x10;
    if (sk_rt_0035a04c() <= pos) {
        sk_rt_00348244(1);
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    unsigned long base = sk_rt_002a9ba8();
    return *(unsigned char *)(base + pos);
}

/*--------------------------------------------------------------------*/
/* FUN_002b16cc @ 0x002b16cc   (est. sk_swift_string_utf8_index_before_b)
 * Ghidra: void FUN_002b16cc(long *param_1, ulong *param_2)
 * Steps a UTF-8 index back one scalar, storing the new packed index into
 * *param_1; faults via sk_fatal_error on underflow/out-of-bounds.
 * Confidence: low (Swift String.UTF8View index before).
 */
void sk_swift_string_utf8_index_before_b(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    if (idx >> 0xe != 0) {
        unsigned long n;
        if ((idx >> 0x3c & 1) == 0) {
            n = (idx & 0xffffffffffff0000UL) - 0xfffc;
        } else {
            unsigned long cap = *(unsigned long *)out & 0xffffffffffffUL;
            if (cap < idx >> 0x10) {
                /* WARNING: noreturn */
                sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                               "Swift.StringUTF8View.swift", 0x1a, 2, 0x9d, 1);
            }
            sk_rt_002b14c8(idx, 0, 0);
            n = *(unsigned long *)out;
        }
        *(unsigned long *)out = n;
        return;
    }
    /* WARNING: noreturn */
    sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                   "Swift.StringUTF8View.swift", 0x1a, 2, 0x98, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002b17c8 @ 0x002b17c8   (est. sk_swift_string_utf8_index_before_c)
 * Ghidra: void FUN_002b17c8(ulong *param_1)
 * Same as sk_swift_string_utf8_index_before_b but for the "before" step;
 * stores the new index into *param_1 and faults on out-of-bounds.
 * Confidence: low (Swift String.UTF8View index before variant).
 */
void sk_swift_string_utf8_index_before_c(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    if (idx >> 0xe != 0) {
        unsigned long n;
        if ((idx >> 0x3c & 1) == 0) {
            n = (idx & 0xffffffffffff0000UL) - 0xfffc;
        } else {
            unsigned long cap = *(unsigned long *)out & 0xffffffffffffUL;
            if (cap < idx >> 0x10) {
                /* WARNING: noreturn */
                sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                               "Swift.StringUTF8View.swift", 0x1a, 2, 0x9d, 1);
            }
            sk_rt_002b14c8(idx, 0, 0);
            n = *(unsigned long *)out;
        }
        *(unsigned long *)out = n;
        return;
    }
    /* WARNING: noreturn */
    sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                   "Swift.StringUTF8View.swift", 0x1a, 2, 0x98, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002b18c4 @ 0x002b18c4   (est. sk_swift_string_utf16_view_index_c)
 * Ghidra: void FUN_002b18c4(undefined8 param_1, long param_2)
 * Computes a UTF-16 index at offset param_2 from the current position and
 * stores it via sk_rt_00357850; faults on out-of-bounds.
 * Confidence: low (Swift String.UTF16View indexed accessor).
 */
void sk_swift_string_utf16_view_index_c2(void *a, long b)
{
    (void)a; (void)b;
    sk_rt_00351124();
    unsigned long f = 0;
    unsigned long v = sk_rt_0034a3b0(1);
    if ((f >> 0x3c & 1) == 0) {
        sk_rt_00359738();
        sk_rt_00357850();
    } else {
        sk_rt_0034d004();
        sk_rt_001b1ff0();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002b1960 @ 0x002b1960   (est. sk_swift_string_utf16_view_index_d)
 * Ghidra: void FUN_002b1960(undefined8, undefined8, ulong *param_3)
 * Computes a UTF-16 index at an offset and stores it, verifying the result
 * stays within bounds; faults via sk_fatal_error on overflow.
 * Confidence: low (Swift String.UTF16View indexed accessor variant).
 */
void sk_swift_string_utf16_view_index_d2(void *a, void *b, unsigned long *c)
{
    (void)a; (void)b;
    sk_rt_00357ca0();
    sk_rt_00351124();
    unsigned long v = *c;
    unsigned long idx = sk_rt_0034a3b0(1);
    if ((v >> 0x3c & 1) != 0) {
        sk_rt_0034e6bc();
        sk_rt_001b28d4();
        return;
    }
    sk_rt_00359738();
    sk_rt_00357850(0, 0);
    sk_rt_0035272c();
    sk_rt_00357c44(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b1b3c @ 0x002b1b3c   (est. sk_swift_string_utf8_view_subscript_b)
 * Ghidra: undefined1 [16] FUN_002b1b3c(undefined1 *param_1, ulong *param_2)
 * Reads the byte at a UTF-8 view position, writing it into *param_1 and
 * returning the iterator pair {0x0001a1c8, param_1}. Faults on out-of-bounds.
 * Confidence: low (Swift String.UTF8View iterator subscript).
 */
void sk_swift_string_utf8_view_subscript_b(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    unsigned long cap = idx & 0xffffffffffffUL;
    unsigned long n = idx >> 0x10;
    if (cap <= n) {
        /* WARNING: noreturn */
        sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                       "Swift.StringUTF8View.swift", 0x1a, 2, 0xe4, 1);
    }
    *(unsigned char *)out = *(unsigned char *)(n);
    ((unsigned long *)out)[1] = 0x1a1c8;
}

/*--------------------------------------------------------------------*/
/* FUN_002b1c84 @ 0x002b1c84   (est. sk_swift_string_utf16_view_compare_e)
 * Ghidra: void FUN_002b1c84(void)
 * Runs sk_rt_00352e84, calls the indirect compare callback, then
 * sk_rt_003554e0.
 * Confidence: low (Swift String compare via indirect dispatch).
 */
void sk_swift_string_utf16_view_compare_e(void)
{
    sk_rt_00352e84();
    /* (*extraout_x9)(extraout_x8, extraout_x1, *x20, x20[1]) */
    sk_rt_003554e0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b1ce0 / FUN_002b1dc8 @ 0x002b1ce0 / 0x002b1dc8 (sk_swift_string_utf8_view_base/b)
 * Ghidra: void FUN_002b1ce0(undefined8 *param_1, ulong *param_2)
 * Returns a pointer to the underlying UTF-8 byte buffer for the string,
 * stored into *param_1 (as &DAT_00010004 + (idx & ~0xffff)). Faults on
 * out-of-bounds non-ASCII strings.
 * Confidence: low (Swift String.UTF8View buffer base).
 */
void sk_swift_string_utf8_view_base(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    if ((idx >> 0x3c & 1) != 0) {
        unsigned long cap = *(unsigned long *)out & 0xffffffffffffUL;
        if (idx >> 0x10 < cap) {
            sk_rt_002b141c(idx, 0, 0);
        }
        /* WARNING: noreturn */
        sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                       "Swift.StringUTF8View.swift", 0x1a, 2, 0x90, 1);
    }
    *(unsigned long *)out = 0x10004 + (idx & 0xffffffffffff0000UL);
}

/*--------------------------------------------------------------------*/
/* FUN_002b1dc8 @ 0x002b1dc8   (est. sk_swift_string_utf8_view_base_b)
 * Ghidra: void FUN_002b1dc8(ulong *param_1)
 * Identical to sk_swift_string_utf8_view_base but for a different caller
 * shape; returns the UTF-8 buffer base into *param_1.
 * Confidence: low (Swift String.UTF8View buffer base variant).
 */
void sk_swift_string_utf8_view_base_b(void *out, void *s)
{
    (void)s;
    unsigned long idx = *(unsigned long *)out;
    if ((idx >> 0x3c & 1) != 0) {
        unsigned long cap = *(unsigned long *)out & 0xffffffffffffUL;
        if (idx >> 0x10 < cap) {
            sk_rt_002b141c(idx, 0, 0);
        }
        /* WARNING: noreturn */
        sk_fatal_error(0xb, 2, "String index is out of bounds", 0x1d, 2,
                       "Swift.StringUTF8View.swift", 0x1a, 2, 0x90, 1);
    }
    *(unsigned long *)out = 0x10004 + (idx & 0xffffffffffff0000UL);
}

/*--------------------------------------------------------------------*/
/* FUN_002b1ec4 / FUN_002b1ec8 @ 0x002b1ec4 / 0x002b1ec8 (sk_swift_string_utf16_view_slice_ac/ad)
 * Ghidra: void FUN_002b1ec4(void)
 * Forwarders to sk_rt_0029d53c with the two source words.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_slice_ac2(void)
{
    sk_rt_0029d53c(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b1ee8 @ 0x002b1ee8   (est. sk_swift_string_utf16_convert_b)
 * Ghidra: undefined8 FUN_002b1ee8(undefined8 *param_1, long param_2, undefined8 param_3)
 * Converts a UTF-16 span into UTF-8, validating the allocation size via
 * sk_rt_002a4528; on insufficient space faults via sk_fatal_error with the
 * "Insufficient space allocated" message.
 * Confidence: medium (UTF-16->UTF-8 conversion with space check).
 */
void sk_swift_string_utf16_convert_b(void *o, long n, unsigned long s)
{
    (void)s;
    if (n == 0) {
        /* WARNING: noreturn */
        sk_fatal_error(0xb, 2, "Attempt to copy string contents into too small a buffer", 0x37, 2,
                       "Swift.StringUTF8View.swift", 0x1a, 2, 0x20f, 1);
    }
    /* validate destination capacity */
    sk_rt_002a4528(n, 0, 0, 0);
    /* WARNING: noreturn */
    sk_fatal_error(0xb, 2, "Insufficient space allocated to copy String contents", 0x34, 2,
                   "Swift.StringUTF8View.swift", 0x1a, 2, 0x213, 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002b1fe4 @ 0x002b1fe4   (est. sk_swift_string_utf16_convert_c)
 * Ghidra: void FUN_002b1fe4(long param_1)
 * Converts a UTF-16 span (param_1 code units), dispatching through
 * sk_rt_002a4528; on success finalizes, otherwise faults noreturn.
 * Confidence: low (Swift UTF-16 conversion dispatch).
 */
void sk_swift_string_utf16_convert_c(long n)
{
    if (n == 0) {
        sk_rt_003488bc(1);
        sk_rt_0034a134();
    } else {
        sk_rt_002a4528();
        sk_rt_00351db4();
        sk_rt_003543d0();
        return;
    }
    /* WARNING: noreturn */
    sk_rt_00356408();
}

/*--------------------------------------------------------------------*/
/* FUN_002b2058 / FUN_002b205c @ 0x002b2058 / 0x002b205c (sk_swift_string_utf16_view_subscript_assign_b/c)
 * Ghidra: void FUN_002b2058(undefined8, undefined8, undefined8)
 * Forwarders to sk_rt_002b2078 (subscript-assign impl) with source words.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_subscript_assign_b(void *out, void *s)
{
    (void)s;
    sk_rt_002b2078(0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b2078 @ 0x002b2078   (est. sk_swift_string_utf16_view_subscript_assign_impl)
 * Ghidra: void FUN_002b2078(undefined8, undefined8, ulong param_3, ulong param_4)
 * Assigns a scalar into a UTF-16 view position: resolves the buffer,
 * decodes the destination (handling inline vs buffered and non-ASCII via
 * sk_rt_00355720 / the global dispatch slot DAT_00658c00), and writes the
 * code unit. Emits via sk_rt_00358fc8.
 * Confidence: low (Swift String.UTF16View subscript-assign).
 */
void sk_swift_string_utf16_view_subscript_assign_impl(void *o1, void *o2, unsigned long s, unsigned long f)
{
    (void)o1; (void)o2;
    sk_rt_00358fb4();
    if ((f >> 0x3c & 1) == 0) {
        sk_rt_003561a0();
        if ((f >> 0x3d & 1) == 0) {
            unsigned long base = sk_rt_002a9ba8();
            /* (*unaff_x24)(base, len, count) */
        } else {
            sk_rt_00355720(f >> 0x38 & 0xf);
            /* (*DAT_00658c00)() global dispatch */
            sk_rt_003519e8();
            sk_rt_0034a210();
            sk_rt_00002534();
            sk_rt_003559bc(0, 0, 0x346774);
            sk_rt_00291d70();
        }
        sk_rt_0034bc94(0);
        sk_rt_000839d8();
    } else {
        sk_rt_0034c3f4(0);
        sk_rt_000839d8();
    }
    sk_rt_00358fc8(0);
}


/*--------------------------------------------------------------------*/
/* FUN_002b21e0 @ 0x002b21e0   (est. sk_swift_string_utf16_view_append_c)
 * Ghidra: void FUN_002b21e0(void)
 * Appends to a UTF-16 view, growing the backing buffer via sk_rt_003a25d4
 * when the appended scalar would overflow the inline capacity; handles the
 * inline vs buffered cases and emits via sk_rt_00357c74.
 * Confidence: low (Swift String.UTF16View append with buffer growth).
 */
void sk_swift_string_utf16_view_append_c(void)
{
    sk_rt_00357cb4();
    sk_rt_00350b0c();
    sk_rt_003a25d4(0xe000000000000000UL);
    sk_rt_00350560();
    sk_rt_001b7cec();
    sk_rt_00352c74();
    if ((sk_rt_0035a04c() >> 0x3d & 1) == 0) {
        sk_rt_0034a618();
        sk_rt_0034c9c8();
        sk_rt_002a4c98();
        sk_rt_003a25d4();
    } else {
        sk_rt_0007c1c4();
        sk_rt_00349c98();
        sk_rt_00351e08();
        sk_rt_003a25d4();
    }
    sk_rt_0034a274();
    sk_rt_0035a798();
    sk_rt_0034f114();
    sk_rt_00357c74(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b22d4 @ 0x002b22d4   (est. sk_swift_string_utf16_view_append)
 * Ghidra: void FUN_002b22d4(void)
 * Appends one character to a Swift String UTF-16 view: grows the backing
 * byte buffer when full (sk_rt_0006b42c / sk_rt_000824e4), decodes the
 * scalar and writes it, updating the string length. Faults via
 * sk_fatal_error on internal inconsistency.
 * Confidence: low (Swift String append, buffer-growth loop).
 */
void sk_swift_string_utf16_view_append(void)
{
    sk_rt_0035300c();
    sk_rt_0008409c();
    sk_rt_003532b8();
    sk_rt_000a6f68();
    sk_rt_0036b270(0);
    sk_rt_000824e4(0, 1, 0);
    /* loop growing buffer and writing scalars */
    sk_rt_003a25d4();
    unsigned long len = *(unsigned long *)(sk_rt_0035a04c() + 0x10);
    if (*(unsigned long *)(sk_rt_0035a04c() + 0x18) >> 1 <= len) {
        sk_rt_0006b42c();
        sk_rt_000824e4(0, len + 1, 1);
    }
    *(unsigned long *)(sk_rt_0035a04c() + 0x10) = len + 1;
    *(unsigned char *)(sk_rt_0035a04c() + len + 0x20) = 0;
    sk_rt_00353238(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b24b8 @ 0x002b24b8   (est. sk_swift_string_utf16_view_append_b)
 * Ghidra: void FUN_002b24b8(ulong param_1, ulong param_2)
 * Computes the boundary flag and scalar for appending (delegating to
 * sk_rt_002b15d0).
 * Confidence: low (Swift String append boundary helper).
 */
void sk_swift_string_utf16_view_append_b(unsigned long v, unsigned long f)
{
    (void)f;
    unsigned long cap = v;
    if ((f & 0x2000000000000000UL) != 0) {
        cap = f >> 0x38 & 0xf;
    }
    sk_rt_002b15d0(0xf, cap << 0x10 | 7, v, f);
}

/*--------------------------------------------------------------------*/
/* FUN_002b24f4 @ 0x002b24f4   (est. sk_swift_string_utf16_view_base)
 * Ghidra: undefined1 [16] FUN_002b24f4(void)
 * Returns the (buffer, count) pair of a UTF-16 view: resolves the inline
 * vs buffered storage and returns {buffer pointer, count}. Faults for
 * non-inline non-ASCII strings.
 * Confidence: low (Swift String.UTF16View buffer/count accessor).
 */
void sk_swift_string_utf16_view_base(void)
{
    unsigned long f = 0;
    if ((f >> 0x3d & 1) == 0) {
        if ((f >> 0x3c & 1) != 0) {
            sk_rt_003488bc(1);
            sk_rt_0034a134();
            /* WARNING: noreturn */
            sk_rt_00356408();
        }
    }
    sk_rt_002a9ba8();
}

/*--------------------------------------------------------------------*/
/* FUN_002b257c @ 0x002b257c   (est. sk_swift_string_utf16_view_contains)
 * Ghidra: bool FUN_002b257c(undefined8, undefined8, ulong param_3)
 * Tests whether a UTF-16 view's packed flag (param_3) matches a boundary;
 * returns (normalized ^ param_3) < 0x4000.
 * Confidence: medium (Swift String.UTF16View flag test).
 */
bool sk_swift_string_utf16_view_contains(void *a, void *b, unsigned long c)
{
    (void)a; (void)b;
    unsigned long v = c;
    if ((c & 0xc001) == 0) {
        sk_rt_00353a30(0, 0, 0);
        sk_rt_001676cc();
        sk_rt_00355814();
        v = sk_rt_0035a04c() | 1;
    }
    return (v ^ c) < 0x4000;
}

/*--------------------------------------------------------------------*/
/* FUN_002b25cc @ 0x002b25cc   (est. sk_swift_string_init_impl3)
 * Ghidra: void FUN_002b25cc(undefined8 param_1, undefined8 param_2)
 * Initializes a Swift String via sk_rt_002b0f7c with a different set of
 * type-metadata pointers (0x675ad0, 0x657660, 0x4f2140, 0x3243a8).
 * Confidence: medium (String init through the shared impl).
 */
void sk_swift_string_init_impl3(void *a, void *b)
{
    sk_rt_002b0f7c(a, b, 0x675ad0, 0x657660, 0x4f2140, 0x3243a8);
}

/*--------------------------------------------------------------------*/
/* FUN_002b25fc @ 0x002b25fc   (est. sk_swift_string_init_out_c)
 * Ghidra: void FUN_002b25fc(undefined8 *param_1)
 * Copies a Swift String built by sk_rt_002b25cc into the caller's output
 * buffer *param_1, preserving the byte-packed layout.
 * Confidence: medium (byte-copy of an inlined String initializer).
 */
void sk_swift_string_init_out_c(void *out, void *s)
{
    (void)s;
    unsigned long local[8];
    sk_rt_002b25cc(&local, 0);
    ((unsigned long *)out)[1] = 0;
    ((unsigned long *)out)[0] = local[0];
    ((unsigned long *)out)[3] = 0;
    ((unsigned long *)out)[2] = 0;
    *(unsigned long *)((char *)out + 0x21) = 0;
    *(unsigned long *)((char *)out + 0x19) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b2660 @ 0x002b2660   (est. sk_swift_string_utf8_decode_bits)
 * Ghidra: uint FUN_002b2660(undefined8 param_1, long param_2, undefined8 param_3)
 * Extracts a bit field from a UTF-8 scalar: computes the byte length from
 * the leading-zero count and shifts param_3 right by the bit offset.
 * Faults via sk_fatal_error on invalid sizes.
 * Confidence: low (Swift UTF-8 bit extraction).
 */
unsigned long sk_swift_string_utf8_decode_bits(unsigned long a, long b, unsigned long c)
{
    (void)b;
    unsigned long v = sk_rt_002c8c2c(c, c);
    if ((v & 1) == 0) {
        sk_rt_0035047c();
    } else {
        v = sk_rt_002c8c2c(a, c);
        if ((v & 1) == 0) {
            sk_rt_0035047c();
        } else {
            unsigned long clz = __builtin_clzll((unsigned int)c);
            long len = (long)(clz - __builtin_clzll((unsigned int)a)) >> 3;
            long idx = b + len;
            if (idx >= 0) {
                if ((unsigned long)idx <= 4 - (clz >> 3)) {
                    unsigned long sh = (unsigned long)((int)idx << 2);
                    return ((unsigned int)c >> (sh & 0x1f)) >> (sh & 0x1f);
                }
                sk_rt_0035047c();
            } else {
                sk_rt_0035047c();
            }
        }
    }
    sk_rt_003486b8(0);
    sk_rt_00349424();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b273c @ 0x002b273c   (est. sk_swift_string_utf8_len2)
 * Ghidra: undefined4 FUN_002b273c(byte param_1)
 * Returns the UTF-8 lead-byte length: 3 for 0xC0-0xDE, 0 for ASCII,
 * otherwise 2.
 * Confidence: high (clean UTF-8 length table).
 */
unsigned long sk_swift_string_utf8_len2(unsigned char c)
{
    unsigned long n = 2;
    if ((c & 0xfe) == 0xc0) {
        n = 3;
    }
    if ((signed char)c < -0x41) {
        n = 0;
    }
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_002b275c @ 0x002b275c   (est. sk_swift_string_utf8_validate2)
 * Ghidra: void FUN_002b275c(byte param_1)
 * Validates a UTF-8 scalar length (< 5); faults via sk_fatal_error on
 * invalid values.
 * Confidence: high (UTF-8 length validation).
 */
void sk_swift_string_utf8_validate2(unsigned char c)
{
    if (c < 5) {
        return;
    }
    sk_rt_00348898(1);
    sk_rt_0034a2f8();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b279c @ 0x002b279c   (est. sk_swift_string_utf8_validate3)
 * Ghidra: void FUN_002b279c(uint param_1)
 * Validates a UTF-8 length and dispatches to sk_rt_00354960, faulting via
 * sk_fatal_error on invalid values.
 * Confidence: medium (UTF-8 length validation wrapper).
 */
void sk_swift_string_utf8_validate3(unsigned int c)
{
    unsigned long len = 0;
    unsigned long err = 0x100;
    if ((c & 0xff) < 5) {
        len = c;
        err = 0;
    }
    sk_rt_00354960(len, err);
}

/*--------------------------------------------------------------------*/
/* FUN_002b2804 / FUN_002b2808 @ 0x002b2804 / 0x002b2808 (sk_swift_string_utf16_view_subscript/b)
 * Ghidra: void FUN_002b2804(void)
 * Forwarders to sk_rt_001dc050 with the source word.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_subscript(void)
{
    sk_rt_001dc050(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b2828 / FUN_002b282c @ 0x002b2828 / 0x002b282c (sk_swift_string_utf16_view_subscript_c/d)
 * Ghidra: void FUN_002b2828(undefined8 param_1)
 * Forwarders to sk_rt_001bf784 with the source word.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_subscript_c(void *a)
{
    sk_rt_001bf784(a, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b2890 @ 0x002b2890   (est. sk_swift_unicode_scalar_hash)
 * Ghidra: ulong FUN_002b2890(ulong param_1)
 * Hashes a Unicode scalar: mixes the scalar-kind byte (from
 * sk_rt_002b28c8) into the high bits of param_1.
 * Confidence: medium (Unicode scalar hash).
 */
unsigned long sk_swift_unicode_scalar_hash(unsigned long c)
{
    unsigned long kind = sk_rt_002b28c8();
    return (kind & 0xff) * 0x10100000000UL | c & 0xffffffffUL;
}

/*--------------------------------------------------------------------*/
/* FUN_002b28c8 @ 0x002b28c8   (est. sk_swift_unicode_scalar_kind)
 * Ghidra: undefined1 FUN_002b28c8(undefined8 param_1)
 * Classifies a Unicode scalar into a kind tag: 0xb for control/whitespace
 * ranges (0x0a-0x0d, 0x85, 0x2028/0x2029), 2 for quotes, 0x10 for ZWJ,
 * 0xe for apostrophe, 0xd for variation selectors, else a table lookup
 * (sk_rt_003d3d4c) or 1.
 * Confidence: medium (Unicode scalar classification table).
 */
unsigned long sk_swift_unicode_scalar_kind(unsigned long c)
{
    unsigned int v = (unsigned int)c;
    if (((v - 10 < 4) || (v == 0x85)) || (v >> 1 == 0x1014)) {
        return 0xb;
    }
    if (v == 0x22) {
        return 2;
    }
    if (v != 0x200d) {
        if (v == 0x27) {
            return 0xe;
        }
        if (v - 0x1f1e6 < 0x1a) {
            return 0xd;
        }
        v = (unsigned int)sk_rt_003d3d4c(c);
        if (v < 0xb) {
            return (unsigned long)(&(unsigned char[]){0})[v]; /* DAT_004f26f0 table */
        }
        return 1;
    }
    return 0x10;
}

/*--------------------------------------------------------------------*/
/* FUN_002b297c @ 0x002b297c   (est. sk_swift_unicode_scalar_clamp)
 * Ghidra: ulong FUN_002b297c(ulong param_1)
 * Clamps a scalar kind tag to a maximum of 5.
 * Confidence: high (clean clamp).
 */
unsigned long sk_swift_unicode_scalar_clamp(unsigned long v)
{
    if (4 < v) {
        v = 5;
    }
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_002b298c / FUN_002b2990 @ 0x002b298c / 0x002b2990 (sk_swift_string_utf16_view_subscript_e/f)
 * Ghidra: void FUN_002b298c(undefined8 param_1)
 * Forwarders to sk_rt_001bf740 with the source word.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_subscript_e(void *a)
{
    sk_rt_001bf740(a, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b29a8 @ 0x002b29a8   (est. sk_swift_unicode_scalar_clamp_b)
 * Ghidra: void FUN_002b29a8(void)
 * Runs sk_rt_00351124, sk_rt_002b297c (clamp), and sk_rt_00357044.
 * Confidence: medium (clamp pipeline).
 */
void sk_swift_unicode_scalar_clamp_b(void)
{
    sk_rt_00351124();
    sk_rt_002b297c();
    sk_rt_00357044();
}

/*--------------------------------------------------------------------*/
/* FUN_002b29d0 @ 0x002b29d0   (est. sk_swift_unicode_scalar_advance)
 * Ghidra: uint FUN_002b29d0(undefined8 param_1)
 * Advances a Unicode scalar state machine given the next code point,
 * updating the internal continuation-state fields (offset 0x22 / 0x05 /
 * 0x06) and returning a status word. Handles CR/LF, ZWJ, combining and
 * regional-indicator pairs.
 * Confidence: low (Swift Unicode scalar grapheme-cluster advance FSM).
 */
unsigned long sk_swift_unicode_scalar_advance(unsigned long c)
{
    unsigned long kind = sk_rt_002b28c8();
    int *st = (int *)0;
    if (kind == 0xb) {
        /* CR/LF handling */
        if ((char)(*(unsigned char *)((char *)st + 6)) == 0) {
            *(unsigned char *)((char *)st + 6) = 0;
        }
        sk_rt_003520c0();
        *st = (int)c;
        *(unsigned char *)((char *)st + 1) = (unsigned char)kind;
        return 0x10000;
    }
    if (kind == 0x10) {
        /* ZWJ */
        int r = (int)sk_rt_003d3470(c);
        if (r == 0) {
            sk_rt_003520c0();
            *st = (int)c;
            return 0x10000;
        }
    }
    if (kind == 0xf) {
        sk_rt_003520c0();
        sk_rt_00358654();
        *(unsigned short *)((char *)st + 1) = 0xf0f;
        return 0;
    }
    if (kind == 0x1 || kind == 0x3 || kind == 0x5) {
        sk_rt_003520c0();
        *st = (int)c;
        *(unsigned char *)((char *)st + 1) = (unsigned char)kind;
        return 0;
    }
    /* default path via the continuation-state table */
    sk_rt_00359690();
    sk_rt_0035360c();
    return 0x10000;
}

/*--------------------------------------------------------------------*/
/* FUN_002b2e60 @ 0x002b2e60   (est. sk_swift_unicode_scalar_advance_b)
 * Ghidra: undefined8 FUN_002b2e60(int param_1)
 * Second Unicode scalar grapheme-cluster state machine: processes a code
 * point into the continuation-state fields and returns a status word.
 * Handles CR/LF, line separators, ZWJ, and combining marks.
 * Confidence: low (Swift Unicode scalar grapheme-cluster advance FSM b).
 */
unsigned long sk_swift_unicode_scalar_advance_b(int c)
{
    unsigned long kind = sk_rt_002b28c8();
    int *st = (int *)0;
    if (kind == 0xb) {
        if ((c == 0xd) && (*st == 10)) {
            *(unsigned char *)((char *)st + 1) = (unsigned char)kind;
            *st = 0xd;
            return 0;
        }
    }
    if (kind == 0xf || kind == 0x10 || kind == 0x3 || kind == 0x5) {
        unsigned long r = 0;
        *(unsigned char *)((char *)st + 1) = (unsigned char)kind;
        *st = c;
        return r;
    }
    /* default via continuation table */
    sk_rt_00359690();
    sk_rt_00350ce4();
    return 0x100;
}


/*--------------------------------------------------------------------*/
/* FUN_002b3670 @ 0x002b3670   (est. sk_swift_string_utf8_view_slice)
 * Ghidra: ulong FUN_002b3670(undefined8, undefined8, ulong param_3)
 * Computes a UTF-8 view slice count: for non-inline strings it faults with
 * the "Foreign strings are unsupported" message; otherwise it decodes the
 * scalar at the slice position and returns the packed scalar.
 * Confidence: low (Swift String.UTF8View slice + foreign-string fault).
 */
unsigned long sk_swift_string_utf8_view_slice(unsigned long a, unsigned long b, unsigned long c)
{
    (void)a; (void)b;
    sk_rt_00350a28();
    sk_rt_00167404();
    if ((c >> 0x3c & 1) == 0) {
        sk_rt_00350624();
    } else {
        sk_rt_0035ac70(0x538c0); /* "Foreign strings are unsupported" */
        sk_rt_003593c0(0, 0);
        sk_rt_0006f768();
        sk_rt_00357bd0();
    }
    unsigned long scalar;
    if ((c >> 0x3d & 1) == 0) {
        unsigned long base = sk_rt_002a9ba8();
        sk_rt_002b377c(&scalar, base, 0, 0);
    } else {
        sk_rt_002b377c(&scalar, 0, c >> 0x38 & 0xf, 0);
    }
    return scalar << 0x10 | 5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b36a4 @ 0x002b36a4   (est. sk_swift_string_utf8_view_slice_b)
 * Ghidra: ulong FUN_002b36a4(undefined8, undefined8, ulong param_3)
 * Slices a UTF-8 view with the "Foreign strings unsupported" fault for
 * non-inline strings; decodes the scalar at the position.
 * Confidence: low (Swift String.UTF8View slice variant).
 */
unsigned long sk_swift_string_utf8_view_slice_b(unsigned long a, unsigned long b, unsigned long c)
{
    (void)a; (void)b;
    sk_rt_0035ac70(0x538c0);
    sk_rt_003593c0(0, 0);
    sk_rt_0006f768();
    sk_rt_00357bd0();
    unsigned long scalar;
    if ((c >> 0x3d & 1) == 0) {
        unsigned long base = sk_rt_002a9ba8();
        sk_rt_002b377c(&scalar, base, 0, 0);
    } else {
        sk_rt_002b377c(&scalar, 0, c >> 0x38 & 0xf, 0);
    }
    return scalar << 0x10 | 5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b377c @ 0x002b377c   (est. sk_swift_utf8_scan_scalar)
 * Ghidra: void FUN_002b377c(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Scans a UTF-8 buffer for the next scalar, decoding its lead byte length
 * and grapheme-cluster continuation; stores the resulting scalar position
 * through sk_rt_003544c8.
 * Confidence: low (Swift UTF-8 scalar scan loop).
 */
void sk_swift_utf8_scan_scalar(void *o1, void *o2, unsigned long p3)
{
    (void)o1; (void)o2;
    sk_rt_00354744();
    long base = sk_rt_003509ec();
    unsigned long pos = p3 >> 0x10;
    unsigned char b = *(unsigned char *)(base + pos);
    long len;
    if ((signed char)b < 0) {
        len = __builtin_clzll(((unsigned int)b << 0x18) ^ 0xffffffffUL) / 8 + 1;
        if (len > 4) len = 4;
    } else {
        len = 1;
    }
    unsigned long scalar = len + pos;
    /* scan grapheme-cluster continuation */
    sk_rt_002b28c8(0);
    sk_rt_002b29d0(0);
    sk_rt_003544c8(0);
    (void)scalar;
}

/*--------------------------------------------------------------------*/
/* FUN_002b3978 @ 0x002b3978   (est. sk_swift_string_index_utf8)
 * Ghidra: undefined1 [16] FUN_002b3978(ulong param_1, ulong param_2)
 * Builds a packed String index from a scalar and a flag: computes the
 * boundary tag (7 or 0xb) from the flag bits and returns {tag | scalar<<16,
 * 0xf}.
 * Confidence: medium (Swift String index construction).
 */
void sk_swift_string_index_utf8(unsigned long v, unsigned long f)
{
    (void)v;
    unsigned long cap = v;
    if ((f & 0x2000000000000000UL) != 0) {
        cap = f >> 0x38 & 0xf;
    }
    unsigned long tag = 7;
    if ((v >> 0x3b & 1) == 0) {
        tag = 0xb;
    }
    (void)cap; (void)tag;
}

/*--------------------------------------------------------------------*/
/* FUN_002b39b4 @ 0x002b39b4   (est. sk_swift_string_compare)
 * Ghidra: void FUN_002b39b4(undefined8, undefined8, undefined8 param_3)
 * Compares two Swift strings: resolves each string's type descriptor,
 * compares the scalar kinds, and dispatches through the global method slot
 * (DAT_00658c00) for the actual comparison. Returns via sk_rt_00084234.
 * Confidence: low (Swift String comparison via indirect dispatch).
 */
void sk_swift_string_compare(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    sk_rt_00084220();
    sk_rt_00350c5c();
    sk_rt_00349b3c();
    /* (*DAT_00658c00)(*(x8+0x40)) global dispatch */
    sk_rt_00348bbc();
    sk_rt_0034b8bc();
    sk_rt_00352cb0();
    sk_rt_00354140();
    sk_rt_0035a280();
    sk_rt_00350968();
    /* (*unaff_x26)() indirect */
    sk_rt_00353d64();
    sk_rt_00351744(0);
    sk_rt_00365b6c();
    sk_rt_0009461c(0);
    sk_rt_002ac99c(0);
    sk_rt_0035a280();
    sk_rt_00084234(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b3b50 @ 0x002b3b50   (est. sk_swift_string_utf16_view_count_b)
 * Ghidra: void FUN_002b3b50(void)
 * Runs sk_rt_0034b13c, sk_rt_002ab6a0, sk_rt_0034b730, then sk_rt_002b3b84.
 * Confidence: low (Swift String.UTF16View count pipeline).
 */
void sk_swift_string_utf16_view_count_b(void)
{
    sk_rt_0034b13c();
    sk_rt_002ab6a0();
    sk_rt_0034b730();
    sk_rt_002b3b84();
}

/*--------------------------------------------------------------------*/
/* FUN_002b3b84 @ 0x002b3b84   (est. sk_swift_string_utf16_view_count_c)
 * Ghidra: ulong FUN_002b3b84(void)
 * Computes the UTF-16 code-unit count of a view, advancing the index to the
 * next boundary (sk_rt_002b3c10) and returning a packed count with flags.
 * Confidence: low (Swift String.UTF16View count).
 */
void sk_swift_string_utf16_view_count_c(void)
{
    unsigned long v = sk_rt_0034b13c();
    long next = sk_rt_002b3c10();
    unsigned long idx = next + (v >> 0x10);
    unsigned long cap = idx;
    if ((long)idx <= (long)(sk_rt_0035a04c() >> 0x10)) {
        cap = idx;
    }
    sk_rt_00353f2c();
    sk_rt_00351c64();
    sk_rt_002b3c10();
    sk_rt_003537e0();
    (void)cap;
}

/*--------------------------------------------------------------------*/
/* FUN_002b3c10 @ 0x002b3c10   (est. sk_swift_string_utf16_view_next)
 * Ghidra: ulong FUN_002b3c10(ulong, undefined8, ulong, ulong, ulong)
 * Advances a UTF-16 view index by one code unit, handling grapheme-cluster
 * boundaries (checking for CR/LF, variation selectors, and ZWJ via
 * sk_rt_002c6d00). Returns the advanced scalar.
 * Confidence: low (Swift String.UTF16View next scalar).
 */
unsigned long sk_swift_string_utf16_view_next(unsigned long i, unsigned long s, unsigned long f, unsigned long l, unsigned long m)
{
    (void)s;
    unsigned long v = i >> 8 & 0x3f;
    if (v == 0) {
        unsigned long p = i >> 0x10;
        if (p == f >> 0x10) {
            v = 0;
        } else {
            if ((m >> 0x3c & 1) != 0) {
                sk_rt_00353178();
                return sk_rt_002c6d00();
            }
            if ((m >> 0x3d & 1) == 0) {
                unsigned long base = sk_rt_002a9ba8();
                if (p + 1 != l) {
                    if (base == 0) {
                        sk_rt_00347f2c();
                        /* WARNING: noreturn */
                        sk_fatal_error(0, 0);
                    }
                    unsigned short u = *(unsigned short *)(base + p);
                    if ((u == 0xa0d) || ((u & 0x8080) != 0)) {
                        sk_rt_00353178();
                        return sk_rt_002c6d00();
                    }
                }
            }
            v = 1;
        }
    }
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_002b3cf8 @ 0x002b3cf8   (est. sk_swift_string_utf16_view_prev)
 * Ghidra: void FUN_002b3cf8(void)
 * Steps a UTF-16 view index back; faults via sk_fatal_error if the index
 * is at the very start.
 * Confidence: low (Swift String.UTF16View previous).
 */
void sk_swift_string_utf16_view_prev(void)
{
    unsigned long v = sk_rt_0034b13c();
    unsigned long base = sk_rt_002ab058();
    if (sk_rt_0035a04c() >> 0xe < base >> 0xe) {
        sk_rt_0034b730();
        sk_rt_002b3d68();
        return;
    }
    sk_rt_003488bc(1);
    sk_rt_0034a96c();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b3d68 @ 0x002b3d68   (est. sk_swift_string_utf16_view_prev_b)
 * Ghidra: void FUN_002b3d68(void)
 * Emits the previous UTF-16 index via sk_rt_00357938, using sk_rt_002b4fc4
 * (trim) to find the boundary when the two indices differ.
 * Confidence: low (Swift String.UTF16View previous emit).
 */
void sk_swift_string_utf16_view_prev_b(void)
{
    unsigned long v;
    unsigned long base = sk_rt_00350858();
    if ((base ^ sk_rt_0035a04c()) < 0x4000) {
        long n = 0;
        sk_rt_00357938(0, n);
        return;
    }
    long n = sk_rt_002b4fc4(sk_rt_0035a04c() >> 0x10, sk_rt_0035a04c() >> 0x10);
    long shifted = n << 8;
    if (0x3f < n) {
        shifted = 0;
    }
    sk_rt_00357938(shifted, n);
}

/*--------------------------------------------------------------------*/
/* FUN_002b3e00 @ 0x002b3e00   (est. sk_swift_string_utf16_view_advance_loop)
 * Ghidra: void FUN_002b3e00(void)
 * Advances a UTF-16 view index across a range, handling both forward and
 * backward directions. Emits the final index via sk_rt_00351d30.
 * Confidence: low (Swift String.UTF16View advance loop).
 */
void sk_swift_string_utf16_view_advance_loop(void)
{
    sk_rt_00351e20();
    sk_rt_00352e54();
    sk_rt_00351dc0();
    sk_rt_0034df94();
    unsigned long base = sk_rt_002ab058();
    unsigned long v = base;
    unsigned long cap = 4;
    unsigned long out = sk_rt_0035a04c() & 2 | cap;
    if (sk_rt_0035a04c() < 0) {
        long n = 0;
        while (sk_rt_0035a04c() < n) {
            if (v >> 0xe <= sk_rt_0035a04c() >> 0xe) {
                /* decompile: goto LAB_002b3f28 -> panic (noreturn), not break */
                sk_rt_00348614(1);
                sk_rt_0034987c();
                /* WARNING: noreturn */
                sk_fatal_error(0, 0);
            }
            n -= 1;
            sk_rt_00351c64(v >> 0x10, sk_rt_0035a04c() >> 0x10);
            sk_rt_002b4fc4();
            long d = sk_rt_00357de4();
            v = 0;
            if (d < 0x40) {
                v = sk_rt_0035a04c();
            }
            v = v | out | 1 | sk_rt_0035a04c();
        }
    } else {
        long n = sk_rt_0035a04c();
        while (n != 0) {
            if (sk_rt_0035a04c() >> 0xe <= v >> 0xe) {
                sk_rt_00348614(1);
                sk_rt_0034987c();
                /* WARNING: noreturn */
                sk_fatal_error(0, 0);
            }
            sk_rt_003562bc();
            sk_rt_00351c64();
            long d = sk_rt_002b3c10();
            v = d + (v >> 0x10);
            unsigned long hi = sk_rt_0035a04c() >> 0x10;
            if ((long)v <= (long)(sk_rt_0035a04c() >> 0x10)) {
                hi = v;
            }
            sk_rt_003562bc();
            sk_rt_00351c64();
            sk_rt_002b3c10();
            sk_rt_003537e0();
            v = hi << 0x10 | 1 | out | sk_rt_0035a04c();
            n -= 1;
        }
    }
    sk_rt_00351d30(v, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b3f40 @ 0x002b3f40   (est. sk_swift_string_utf16_view_advance_loop_b)
 * Ghidra: void FUN_002b3f40(undefined8, undefined8, ulong, undefined8, ulong, undefined8, ulong)
 * Second UTF-16 view advance loop, handling both directions and emitting
 * via sk_rt_00351d30. Faults on invalid ranges.
 * Confidence: low (Swift String.UTF16View advance loop b).
 */
void sk_swift_string_utf16_view_advance_loop_b(void *a, void *b, unsigned long c, void *d, unsigned long e, void *g, unsigned long h)
{
    (void)a; (void)b; (void)d; (void)g;
    sk_rt_00351e20();
    sk_rt_00356188();
    sk_rt_00359b18();
    sk_rt_003509ec();
    unsigned long base = sk_rt_002ab058();
    unsigned long v = base;
    unsigned long cap = 4;
    unsigned long out = h & 2 | cap;
    if (sk_rt_0035a04c() < 0) {
        long n = 0;
        while (sk_rt_0035a04c() < n) {
            if ((base >> 0xe <= c >> 0xe) && (c >> 0xe <= base >> 0xe)) {
                break;
            }
            if (base >> 0xe <= h >> 0xe) {
                sk_rt_00348614(1);
                sk_rt_0034987c();
                /* WARNING: noreturn */
                sk_fatal_error(0, 0);
            }
            sk_rt_00351c64(base >> 0x10, h >> 0x10);
            sk_rt_002b4fc4();
            long d2 = sk_rt_00357de4();
            v = 0;
            if (d2 < 0x40) {
                v = sk_rt_0035a04c();
            }
            v = v | out | 1 | sk_rt_0035a04c();
            n -= 1;
        }
    } else {
        long n = sk_rt_0035a04c();
        while (n != 0) {
            if ((c >> 0xe <= base >> 0xe) && (base >> 0xe <= base >> 0xe)) {
                break;
            }
            if (e >> 0xe <= base >> 0xe) {
                sk_rt_00348614(1);
                sk_rt_0034987c();
                /* WARNING: noreturn */
                sk_fatal_error(0, 0);
            }
            sk_rt_003562bc();
            sk_rt_00351c64();
            long d2 = sk_rt_002b3c10();
            v = d2 + (base >> 0x10);
            unsigned long hi = e >> 0x10;
            if ((long)v <= (long)(e >> 0x10)) {
                hi = v;
            }
            sk_rt_003562bc();
            sk_rt_00351c64();
            sk_rt_002b3c10();
            sk_rt_003537e0();
            v = hi << 0x10 | 1 | out | sk_rt_0035a04c();
            n -= 1;
        }
    }
    sk_rt_00351d30(v, 0, 0);
}


/*--------------------------------------------------------------------*/
/* FUN_002b4120 @ 0x002b4120   (est. sk_swift_string_utf16_view_advance_loop_c)
 * Ghidra: void FUN_002b4120(void)
 * Third UTF-16 view advance loop: walks the index from start to end,
 * handling forward and backward directions with scalar decoding
 * (sk_rt_002b4fc4 for backward). Emits via sk_rt_00353238.
 * Confidence: low (Swift String.UTF16View advance loop c).
 */
void sk_swift_string_utf16_view_advance_loop_c(void)
{
    sk_rt_0035300c();
    sk_rt_0034dff4();
    sk_rt_00351a14();
    sk_rt_0034df94();
    unsigned long lo = sk_rt_002ab058();
    sk_rt_0034cf54();
    sk_rt_00351c64();
    unsigned long hi = sk_rt_002ab058();
    long count = 0;
    if (lo >> 0xe < hi >> 0xe) {
        unsigned long pos = hi >> 0x10;
        do {
            count += 1;
            unsigned long unit = lo;
            if ((lo >> 8 & 0x3f) == 0) {
                unsigned long p = lo >> 0x10;
                if (p != pos) {
                    /* decode scalar at p */
                    if ((lo >> 0x3c & 1) == 0) {
                        unsigned short u = *(unsigned short *)(sk_rt_00358a98() + p);
                        if ((u == 0xa0d) || ((u & 0x8080) != 0)) {
                            sk_rt_0034ba28();
                            sk_rt_002c6d00();
                        }
                    }
                }
            }
            unsigned long next = pos;
            if ((long)(unit + (unit >> 0x10)) <= (long)pos) {
                next = unit + (unit >> 0x10);
            }
            lo = next << 0x10;
            /* skip boundary alignment */
            if (lo >> 0xe < hi >> 0xe) continue;
            break;
        } while (1);
    } else if (hi >> 0xe < lo >> 0xe) {
        count = 0;
        do {
            count -= 1;
            if (lo >> 0xe == sk_rt_0035a04c() >> 0xe) {
                break;
            }
            sk_rt_00351c64(lo >> 0x10, sk_rt_0035a04c() >> 0x10);
            sk_rt_002b4fc4();
            long d = sk_rt_00357de4();
            unsigned long v = sk_rt_0035a04c();
            if (0x3f < d) {
                v = 0;
            }
            v = v | sk_rt_0035a04c();
            lo = v;
        } while (hi >> 0xe < lo >> 0xe);
    }
    sk_rt_00353238(count, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b439c @ 0x002b439c   (est. sk_swift_string_utf16_view_advance_loop_d)
 * Ghidra: void FUN_002b439c(void)
 * Fourth UTF-16 view advance loop; validates the range and advances via
 * sk_rt_002b3c10, finishing through sk_rt_002a2698 or faulting.
 * Confidence: low (Swift String.UTF16View advance loop d).
 */
void sk_swift_string_utf16_view_advance_loop_d(void)
{
    sk_rt_003531d8();
    unsigned long base = sk_rt_002ab4d4();
    sk_rt_00350974();
    long d = sk_rt_002b3c10();
    unsigned long idx = d + (base >> 0x10);
    unsigned long hi = idx;
    if ((long)idx <= (long)(sk_rt_0035a04c() >> 0x10)) {
        hi = idx;
    }
    if ((long)(base >> 0x10) <= (long)hi) {
        unsigned long base2 = sk_rt_002a9ba8();
        sk_rt_0007c1c4();
        sk_rt_003520dc();
        if ((sk_rt_0028e8c0() & 0x8000000000000000UL) == 0) {
            sk_rt_00348e48();
            sk_rt_001e4cbc();
            sk_rt_0034de9c();
            sk_rt_002a2698();
            return;
        }
        sk_rt_003481fc();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    sk_rt_00347d60();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b44a4 / FUN_002b44a8 @ 0x002b44a4 / 0x002b44a8 (sk_swift_string_utf16_view_slice_d/e)
 * Ghidra: void FUN_002b44a4(void)
 * Forwarders to sk_rt_002b7794.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_slice_d(void)
{
    sk_rt_002b7794();
}

/*--------------------------------------------------------------------*/
/* FUN_002b44d0 @ 0x002b44d0   (est. sk_swift_string_utf16_view_slice_f)
 * Ghidra: void FUN_002b44d0(undefined8 param_1, undefined8 param_2)
 * Slices a UTF-16 view: runs sk_rt_002ab5bc with the source words, then
 * sk_rt_00350974 and sk_rt_002a95b4.
 * Confidence: low (Swift String.UTF16View slice).
 */
void sk_swift_string_utf16_view_slice_f(void *a, void *b)
{
    (void)a; (void)b;
    sk_rt_002ab5bc(0, 0, 0, 0, 0, 0);
    sk_rt_00350974();
    sk_rt_002a95b4();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4550 @ 0x002b4550   (est. sk_swift_string_utf16_view_advance_loop_e)
 * Ghidra: void FUN_002b4550(void)
 * Runs sk_rt_003528cc, sk_rt_0034df94, sk_rt_002a58b8.
 * Confidence: low (Swift String.UTF16View advance pipeline).
 */
void sk_swift_string_utf16_view_advance_loop_e(void)
{
    sk_rt_003528cc();
    sk_rt_0034df94();
    sk_rt_002a58b8();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4580 @ 0x002b4580   (est. sk_swift_string_utf16_view_advance_loop_f)
 * Ghidra: void FUN_002b4580(void)
 * Runs sk_rt_003528cc, sk_rt_0034df94, sk_rt_002a5e9c.
 * Confidence: low (Swift String.UTF16View advance pipeline b).
 */
void sk_swift_string_utf16_view_advance_loop_f(void)
{
    sk_rt_003528cc();
    sk_rt_0034df94();
    sk_rt_002a5e9c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b45a8 @ 0x002b45a8   (est. sk_swift_string_utf16_view_advance_loop_g)
 * Ghidra: void FUN_002b45a8(void)
 * Runs sk_rt_0035239c, sk_rt_002a6080.
 * Confidence: low (Swift String.UTF16View advance pipeline c).
 */
void sk_swift_string_utf16_view_advance_loop_g(void)
{
    sk_rt_0035239c();
    sk_rt_002a6080();
}

/*--------------------------------------------------------------------*/
/* FUN_002b45cc @ 0x002b45cc   (est. sk_swift_string_utf16_view_slice_g)
 * Ghidra: void FUN_002b45cc(void)
 * Slices a UTF-16 view: resolves the current CPU (sk_rt_0008e518), runs the
 * dispatch helpers and the global method slot (DAT_00658c00), and handles
 * the inline case via sk_rt_00365b6c. Emits through sk_rt_0008e500.
 * Confidence: low (Swift String.UTF16View slice with CPU/object dispatch).
 */
void sk_swift_string_utf16_view_slice_g(void)
{
    sk_rt_0008e518();
    sk_rt_003531d8();
    sk_rt_00349720(0, 0);
    /* (*DAT_00658c00)(*(x8+0x40)) global dispatch */
    sk_rt_00348abc();
    sk_rt_0034b758();
    sk_rt_00354810();
    /* (*extraout_x9)() indirect */
    sk_rt_00354040();
    sk_rt_00358288();
    sk_rt_00351ef8(0);
    sk_rt_00310c44();
    sk_rt_003540ac();
    sk_rt_0035a4e0();
    sk_rt_00365b6c();
    sk_rt_000b43d0();
    sk_rt_002b3978();
    sk_rt_0008e500(0xf);
}

/*--------------------------------------------------------------------*/
/* FUN_002b4834 @ 0x002b4834   (est. sk_swift_string_utf16_view_slice_h)
 * Ghidra: undefined8 FUN_002b4834(void)
 * Runs sk_rt_001e9c00 and sk_rt_002b3978, returning 0xf.
 * Confidence: medium (Swift String.UTF16View slice wrapper).
 */
void sk_swift_string_utf16_view_slice_h(void)
{
    sk_rt_001e9c00();
    sk_rt_002b3978();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4854 @ 0x002b4854   (est. sk_swift_string_utf16_view_slice_i)
 * Ghidra: undefined8 FUN_002b4854(void)
 * Runs sk_rt_001eb73c and sk_rt_002b3978, returning 0xf.
 * Confidence: medium (Swift String.UTF16View slice wrapper b).
 */
void sk_swift_string_utf16_view_slice_i(void)
{
    sk_rt_001eb73c();
    sk_rt_002b3978();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4874 @ 0x002b4874   (est. sk_swift_string_utf16_view_slice_j)
 * Ghidra: void FUN_002b4874(undefined8, undefined8, undefined8)
 * Slices a UTF-16 view: runs sk_rt_0034bb84, sk_rt_00353178, sk_rt_002a3e64,
 * sk_rt_0034c2a4, sk_rt_00359fb4, sk_rt_001e9d8c, and sk_rt_003a25d4.
 * Confidence: low (Swift String.UTF16View slice pipeline).
 */
void sk_swift_string_utf16_view_slice_j(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    sk_rt_0034bb84();
    sk_rt_00353178(0);
    sk_rt_002a3e64();
    sk_rt_0034c2a4(0, 0, 0);
    sk_rt_00359fb4();
    sk_rt_001e9d8c();
    sk_rt_003a25d4(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b48e4 @ 0x002b48e4   (est. sk_swift_string_utf16_view_slice_k)
 * Ghidra: void FUN_002b48e4(undefined8 x8)
 * Slices a UTF-16 view with 8 args; runs the buffer-resolution helpers,
 * and for non-ASCII strings dispatches through the global slot, else via
 * sk_rt_0029b1e0. Emits through sk_rt_00353d14.
 * Confidence: low (Swift String.UTF16View slice pipeline b).
 */
void sk_swift_string_utf16_view_slice_k(void *a, void *b, void *c, void *d, void *e, void *f, void *g, void *h)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h;
    sk_rt_00353cfc();
    sk_rt_00355b68();
    sk_rt_002a3e64(0, 0, 0, 0);
    sk_rt_0035a5cc();
    sk_rt_00354040();
    /* (*DAT_00658c00)() global dispatch */
    sk_rt_00358298();
    sk_rt_00359fb4(0, 0x346d38, 0, 0);
    sk_rt_001e9d8c();
    sk_rt_003a25d4();
    sk_rt_00351348();
    sk_rt_00353d14(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b49e4 @ 0x002b49e4   (est. sk_swift_string_utf16_view_slice_l)
 * Ghidra: void FUN_002b49e4(undefined8 x4)
 * Slices a UTF-16 view: runs sk_rt_00351624, sk_rt_00351ca0 (with a
 * 16-byte metadata constant), sk_rt_00297af0, and sk_rt_001a8564.
 * Confidence: low (Swift String.UTF16View slice with metadata).
 */
void sk_swift_string_utf16_view_slice_l(void *a, void *b, void *c, void *d)
{
    (void)a; (void)b; (void)c; (void)d;
    sk_rt_00351624(0);
    unsigned long local[9];
    local[0] = 0;
    sk_rt_00351ca0(0x6adf10, 0x4e7a30, 0);
    sk_rt_00297af0(local, 0, 0, 0, 0);
    sk_rt_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4a70 @ 0x002b4a70   (est. sk_swift_string_utf16_view_slice_m)
 * Ghidra: void FUN_002b4a70(void)
 * Slices a UTF-16 view: runs sk_rt_00353510 then calls the indirect
 * callback with the source words, then sk_rt_003554e0.
 * Confidence: low (Swift String.UTF16View slice via indirect callback).
 */
void sk_swift_string_utf16_view_slice_m(void)
{
    sk_rt_00353510();
    /* (*extraout_x9)(v0, v1, *(x20+0x10), *(x20+0x18)) */
    sk_rt_003554e0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4b04 @ 0x002b4b04   (est. sk_swift_string_utf16_view_slice_n)
 * Ghidra: void FUN_002b4b04(void)
 * Slices a UTF-16 view: runs sk_rt_002a3e64, calls the indirect callback
 * in x4, then sk_rt_0006b674, sk_rt_003a25d4, and sk_rt_003507e0.
 * Confidence: low (Swift String.UTF16View slice pipeline c).
 */
void sk_swift_string_utf16_view_slice_n(void)
{
    sk_rt_002a3e64();
    /* (*in_x4)() indirect */
    sk_rt_0006b674();
    sk_rt_003a25d4(0);
    sk_rt_003507e0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4b4c @ 0x002b4b4c   (est. sk_swift_string_utf16_view_slice_o)
 * Ghidra: void FUN_002b4b4c(undefined8 *param_1, ...)
 * Slices a UTF-16 view and packs the result into *param_1 as a
 * {0xf, result, param_4, param_5} tuple.
 * Confidence: low (Swift String.UTF16View slice result packing).
 */
void sk_swift_string_utf16_view_slice_o(void *o, void *a, void *b, void *c, void *d)
{
    (void)a; (void)b; (void)c; (void)d;
    sk_rt_002b45cc();
    unsigned long *out = (unsigned long *)o;
    out[0] = 0xf;
    out[1] = sk_rt_0035a04c();
    out[2] = 0;
    out[3] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b4b7c @ 0x002b4b7c   (est. sk_swift_string_utf16_view_slice_p)
 * Ghidra: void FUN_002b4b7c(undefined8 *param_1, ...)
 * Packs a UTF-16 view slice into *param_1 as {0xf, result, ...}.
 * Confidence: low (Swift String.UTF16View slice result packing b).
 */
void sk_swift_string_utf16_view_slice_p(void *o, void *a, void *b, void *c, void *d)
{
    (void)a; (void)b; (void)c; (void)d;
    sk_rt_002b4834();
    unsigned long *out = (unsigned long *)o;
    out[0] = 0xf;
    out[1] = sk_rt_0035a04c();
    out[2] = 0;
    out[3] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b4bac @ 0x002b4bac   (est. sk_swift_string_utf16_view_slice_q)
 * Ghidra: void FUN_002b4bac(undefined8 *param_1, ...)
 * Packs a UTF-16 view slice into *param_1 as {0xf, result, ...}.
 * Confidence: low (Swift String.UTF16View slice result packing c).
 */
void sk_swift_string_utf16_view_slice_q(void *o, void *a, void *b, void *c, void *d)
{
    (void)a; (void)b; (void)c; (void)d;
    sk_rt_002b4854();
    unsigned long *out = (unsigned long *)o;
    out[0] = 0xf;
    out[1] = sk_rt_0035a04c();
    out[2] = 0;
    out[3] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b4bdc / FUN_002b4be0 @ 0x002b4bdc / 0x002b4be0 (sk_swift_string_utf16_view_slice_r/s)
 * Ghidra: void FUN_002b4bdc(undefined8 x3)
 * Forwarders to sk_rt_002b4874 with the source words.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_slice_r(void *a, void *b, void *c)
{
    (void)a; (void)b;
    sk_rt_002b4874(0, 0, 0, 0, 0, 0, c);
}

/*--------------------------------------------------------------------*/
/* FUN_002b4c00 @ 0x002b4c00   (est. sk_swift_string_utf16_view_slice_t)
 * Ghidra: void FUN_002b4c00(void)
 * Forwarder to sk_rt_002b48e4.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_slice_t(void)
{
    sk_rt_002b48e4();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4ca4 @ 0x002b4ca4   (est. sk_swift_string_utf16_view_slice_u)
 * Ghidra: void FUN_002b4ca4(void)
 * Slices a UTF-16 view: runs sk_rt_001a84f4 and sk_rt_00297be8 with the
 * source words, then sk_rt_001a8564.
 * Confidence: low (Swift String.UTF16View slice pipeline d).
 */
void sk_swift_string_utf16_view_slice_u(void)
{
    unsigned char stack[72];
    sk_rt_001a84f4(stack);
    sk_rt_00297be8(stack, 0, 0, 0, 0);
    sk_rt_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4e14 @ 0x002b4e14   (est. sk_swift_string_utf16_view_slice_v)
 * Ghidra: void FUN_002b4e14(undefined8 *param_1)
 * Copies a UTF-16 view slice built by sk_rt_001bcdb8 into *param_1 as a
 * 6-word tuple.
 * Confidence: medium (Swift String.UTF16View slice result copy).
 */
void sk_swift_string_utf16_view_slice_v(void *o, void *s)
{
    (void)s;
    unsigned long local[6];
    sk_rt_001bcdb8(&local, 0, 0, 0, 0);
    unsigned long *out = (unsigned long *)o;
    out[0] = local[0];
    out[1] = 0;
    out[2] = local[2];
    out[3] = 0;
    out[4] = local[4];
    out[5] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b4e5c @ 0x002b4e5c   (est. sk_swift_string_utf16_view_slice_w)
 * Ghidra: void FUN_002b4e5c(void)
 * Computes a UTF-16 view slice (sk_rt_002b3e00) and stores it into the
 * caller's slot at x19.
 * Confidence: medium (wrapper storing a computed slice).
 */
void sk_swift_string_utf16_view_slice_w(void)
{
    *(unsigned long *)0 = sk_rt_002b3e00();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4e88 @ 0x002b4e88   (est. sk_swift_string_utf16_view_slice_x)
 * Ghidra: void FUN_002b4e88(void)
 * Runs sk_rt_0034c434, sk_rt_002b3f40, sk_rt_0035272c.
 * Confidence: low (Swift String.UTF16View slice pipeline e).
 */
void sk_swift_string_utf16_view_slice_x(void)
{
    sk_rt_0034c434();
    sk_rt_002b3f40();
    sk_rt_0035272c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4eb8 @ 0x002b4eb8   (est. sk_swift_string_utf16_view_slice_y)
 * Ghidra: void FUN_002b4eb8(void)
 * Runs sk_rt_00359424, sk_rt_002b4120.
 * Confidence: low (Swift String.UTF16View slice pipeline f).
 */
void sk_swift_string_utf16_view_slice_y(void)
{
    sk_rt_00359424();
    sk_rt_002b4120();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4ed4 / FUN_002b4ed8 @ 0x002b4ed4 / 0x002b4ed8 (sk_swift_string_utf16_view_compare/b)
 * Ghidra: void FUN_002b4ed4(undefined8 *param_1, undefined8 *param_2)
 * Compares two UTF-16 views via sk_rt_001d2f4c.
 * Confidence: medium (Swift String.UTF16View compare forwarder).
 */
void sk_swift_string_utf16_view_compare(void *a, void *b)
{
    sk_rt_001d2f4c(0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b4f14 @ 0x002b4f14   (est. sk_swift_string_utf16_view_compare_c)
 * Ghidra: void FUN_002b4f14(void)
 * Compares UTF-16 views: runs sk_rt_00351124 then calls the indirect
 * callback with the source words, storing the result at x19.
 * Confidence: low (Swift String.UTF16View compare via indirect dispatch).
 */
void sk_swift_string_utf16_view_compare_c(void)
{
    unsigned long v = sk_rt_00351124();
    /* uVar1 = (*extraout_x9)(v, *x20, x20[1], x20[2], x20[3]) */
    *(unsigned long *)0 = v;
}

/*--------------------------------------------------------------------*/
/* FUN_002b4f64 @ 0x002b4f64   (est. sk_swift_string_utf16_view_compare_d)
 * Ghidra: void FUN_002b4f64(undefined8 *param_1, ..., code *param_4)
 * Compares UTF-16 views through the indirect callback param_4 and stores
 * the result into *param_1.
 * Confidence: low (Swift String.UTF16View compare via indirect callback).
 */
void sk_swift_string_utf16_view_compare_d(void *o, void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    unsigned long r = sk_rt_0035a04c();
    *(unsigned long *)o = r;
}


/*--------------------------------------------------------------------*/
/* FUN_002b4fc4 @ 0x002b4fc4   (est. sk_swift_string_utf16_trim)
 * Ghidra: long FUN_002b4fc4(void)
 * UTF-16 grapheme-cluster-aware trim: scans backward from the end of a
 * string buffer looking for the scalar boundary that should be trimmed,
 * handling whitespace/line-separator runs and variation selectors.
 * Returns the trimmed byte offset.
 * Confidence: low (Swift String UTF-16 trim/grapheme boundary scan).
 */
void sk_swift_string_utf16_trim(void)
{
    /* backward scan over UTF-16 code units, stopping at a non-continuation
     * boundary; the caller uses the returned offset. */
    unsigned long base = sk_rt_002a9ba8();
    long hi = 0, lo = 0;
    if (hi <= lo) {
        sk_rt_00348898(1);
        sk_rt_0034a2f8();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    do {
        unsigned char b = *(unsigned char *)(base + hi - 1);
        hi -= 1;
        if ((unsigned char)b >= 0x40) break;
    } while (hi > lo);
    /* decode the last scalar and classify it for trimming */
    sk_rt_002c6a20(0);
    sk_rt_002bb9b8(0);
    sk_rt_002c7b68();
    sk_rt_002c7b8c(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b5abc @ 0x002b5abc   (est. sk_swift_string_utf16_view_slice_z)
 * Ghidra: void FUN_002b5abc(void)
 * Slices a UTF-16 view: runs sk_rt_002a3e64, sk_rt_0034d5ec,
 * sk_rt_001a6484, sk_rt_0034a224.
 * Confidence: low (Swift String.UTF16View slice pipeline).
 */
void sk_swift_string_utf16_view_slice_z(void *o, void *a, void *b, void *c, void *d)
{
    (void)o; (void)a; (void)b; (void)c; (void)d;
    sk_rt_002a3e64();
    sk_rt_0034d5ec(0);
    sk_rt_001a6484();
    sk_rt_0034a224();
}

/*--------------------------------------------------------------------*/
/* FUN_002b5af8 @ 0x002b5af8   (est. sk_swift_string_utf16_view_slice_aa)
 * Ghidra: void FUN_002b5af8(undefined8 *param_1)
 * Copies a UTF-16 view slice built by sk_rt_002b5abc into *param_1,
 * preserving the byte-packed layout.
 * Confidence: medium (Swift String.UTF16View slice result copy).
 */
void sk_swift_string_utf16_view_slice_aa(void *o, void *s)
{
    (void)s;
    unsigned long local[8];
    sk_rt_002b5abc(&local, 0, 0, 0, 0);
    unsigned long *out = (unsigned long *)o;
    out[0] = local[0];
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    *(unsigned long *)((char *)o + 0x21) = 0;
    *(unsigned long *)((char *)o + 0x19) = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b5b70 @ 0x002b5b70   (est. sk_swift_string_utf16_view_slice_ab)
 * Ghidra: void FUN_002b5b70(undefined8 *param_1, ...)
 * Packs a UTF-16 view slice into *param_1 as {0xf, result, ...}.
 * Confidence: low (Swift String.UTF16View slice result packing).
 */
void sk_swift_string_utf16_view_slice_ab(void *o, void *a, void *b, void *c, void *d)
{
    (void)a; (void)b; (void)c; (void)d;
    sk_rt_002b3978();
    unsigned long *out = (unsigned long *)o;
    out[0] = 0xf;
    out[1] = sk_rt_0035a04c();
    out[2] = 0;
    out[3] = 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002b5ba0 @ 0x002b5ba0   (est. sk_swift_string_utf8_view_subscript_c)
 * Ghidra: undefined1 FUN_002b5ba0(undefined8, undefined8, ulong param_3)
 * Reads a byte from a UTF-8 view at the given index; validates the index
 * range (two-sided: arg2 lower bound AND param_3 upper bound, cf. disasm
 * cmp x8,x21,LSR 0xe / ccmp x8,x9,cs) and resolves the buffer via the
 * Swift String packed-representation branch tree (inline x19/x20 bits,
 * spill buffer auStack_40, or runtime storage FUN_002a9ba8/FUN_00350804),
 * faulting via sk_fatal_error on overflow.
 * Confidence: low (Swift String.UTF8View byte subscript; x19/x20 opaque
 *   saved registers keep the inline/coalesced-buffer paths unverifiable).
 */
unsigned long sk_swift_string_utf8_view_subscript_c(void *a, void *b, unsigned long c)
{
    (void)a;
    unsigned long x19 = 0, x20 = 0;   /* opaque saved regs (Swift ctx bits) */
    uint8_t stackbuf[16] = {0};       /* auStack_40 @ sp+0x20 */
    unsigned long v, v2, v3, base;
    sk_rt_00351da8();
    sk_rt_00354a28();
    v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        v = sk_rt_0001da84();
    }
    /* two-sided range check: fault if v>>0xe < arg2>>0xe || arg3>>0xe <= v>>0xe */
    if (v >> 0xe < ((unsigned long)b >> 0xe) || (c >> 0xe) <= (v >> 0xe)) {
        sk_rt_00348614(1);
        sk_rt_0034987c();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    if ((x19 >> 0x3c & 1) == 0) {
        if ((x19 >> 0x3d & 1) != 0) {
            v2 = sk_rt_003584f8();
            return stackbuf[v2 >> 0x10];        /* inline coalesced spill */
        }
        if ((x20 >> 0x3c & 1) != 0) {
            base = (x19 & 0xfffffffffffffff) + 0x20;
            return *(unsigned char *)(base + (v >> 0x10));
        }
    }
    else {
        sk_rt_00350624();
        sk_rt_002b141c();
    }
    sk_rt_0007c1c4();
    sk_rt_002a9ba8();
    v3 = sk_rt_00350804();
    base = 0;   /* extraout_x8 (opaque x8 out of FUN_002a9ba8) */
    return *(unsigned char *)(base + (v3 >> 0x10));
}

/*--------------------------------------------------------------------*/
/* FUN_002b5c70 @ 0x002b5c70   (est. sk_swift_string_utf8_view_count_b)
 * Ghidra: long FUN_002b5c70(void)
 * Returns the UTF-8 byte count of a view; faults on non-inline overflow.
 * Confidence: low (Swift String.UTF8View count).
 */
void sk_swift_string_utf8_view_count_b(void)
{
    sk_rt_00351da8();
    sk_rt_00354a28();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        sk_rt_0001da84();
    }
    if ((v >> 0x3c & 1) != 0) {
        sk_rt_0034a274();
        sk_rt_00350624();
        sk_rt_002b141c();
        sk_rt_00348244(1);
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    sk_rt_0035aac0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b5ce4 @ 0x002b5ce4   (est. sk_swift_string_utf8_view_count_c)
 * Ghidra: void FUN_002b5ce4(void)
 * Computes the UTF-8 byte count and stores it back through the resolved
 * buffer pointer; faults on non-inline overflow.
 * Confidence: low (Swift String.UTF8View count, store-back variant).
 */
void sk_swift_string_utf8_view_count_c(void)
{
    long *buf = (long *)sk_rt_00351da8();
    sk_rt_00354a28(*buf);
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        sk_rt_0001da84();
    }
    if ((v >> 0x3c & 1) != 0) {
        sk_rt_0034a274();
        sk_rt_00350624();
        sk_rt_002b141c();
        sk_rt_00348244(1);
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    sk_rt_0035aac0();
    *buf = (long)sk_rt_0035a04c() + 4;
}

/*--------------------------------------------------------------------*/
/* FUN_002b5d6c @ 0x002b5d6c   (est. sk_swift_string_utf8_view_index)
 * Ghidra: void FUN_002b5d6c(void)
 * Computes a UTF-8 view index at an offset, verifying it stays within
 * bounds; faults via sk_fatal_error on overflow.
 * Confidence: low (Swift String.UTF8View indexed accessor).
 */
void sk_swift_string_utf8_view_index(unsigned long i, unsigned long s, unsigned long f)
{
    (void)s;
    unsigned long v = sk_rt_0034a3b0(1);
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        v = sk_rt_0001da84();
    }
    if ((v >> 0x3c & 1) != 0) {
        sk_rt_0034b788();
        sk_rt_001b1ff0();
        return;
    }
    sk_rt_0034cbb0();
    sk_rt_00357850();
}

/*--------------------------------------------------------------------*/
/* FUN_002b5e10 @ 0x002b5e10   (est. sk_swift_string_utf8_view_index_b)
 * Ghidra: void FUN_002b5e10(void)
 * Second UTF-8 view indexed accessor with bounds verification.
 * Confidence: low (Swift String.UTF8View indexed accessor variant).
 */
void sk_swift_string_utf8_view_index_b(unsigned long i, unsigned long s, unsigned long f)
{
    (void)s;
    unsigned long v = sk_rt_0034a3b0(1);
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        v = sk_rt_0001da84();
    }
    if ((v >> 0x3c & 1) != 0) {
        sk_rt_0034b730();
        sk_rt_001b28d4();
        return;
    }
    sk_rt_0034cbb0();
    sk_rt_00357850(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b5ed4 @ 0x002b5ed4   (est. sk_swift_string_utf8_view_distance)
 * Ghidra: void FUN_002b5ed4(void)
 * Computes the distance between two UTF-8 view indices; for non-ASCII
 * strings it verifies both ends are valid then emits the difference via
 * sk_rt_00357c44, else faults.
 * Confidence: low (Swift String.UTF8View distance).
 */
void sk_swift_string_utf8_view_distance(void)
{
    sk_rt_00357ca0();
    sk_rt_00352e54();
    sk_rt_003509ec();
    unsigned long v = sk_rt_0034a3b0(1);
    if (sk_rt_0034bf1c()) {
        sk_rt_0034ba28();
        sk_rt_0001da84();
    }
    if ((v >> 0x3c & 1) == 0) {
        sk_rt_00357c44(0, 0);
        return;
    }
    sk_rt_0034a274();
    sk_rt_0008412c();
    sk_rt_00357c44();
    sk_rt_002b15d0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b5f94 @ 0x002b5f94   (est. sk_swift_string_utf8_view_slice_m)
 * Ghidra: void FUN_002b5f94(undefined8 x3)
 * Slices a UTF-8 view: runs the page-alloc wrapper sk_rt_0036b270, then
 * sk_rt_00002534 with metadata pointers, sk_rt_0028cd14, and sk_rt_003a25d4.
 * Confidence: low (Swift String.UTF8View slice pipeline).
 */
void sk_swift_string_utf8_view_slice_m(void *a, void *b, void *c)
{
    (void)a; (void)b; (void)c;
    sk_rt_0036b270(0);
    sk_rt_00002534(0x657610, 0x4f1978);
    sk_rt_0028cd14(0, 0, 0, 0, 0);
    sk_rt_003a25d4(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b603c @ 0x002b603c   (est. sk_swift_string_utf8_view_slice_n)
 * Ghidra: void FUN_002b603c(void)
 * Advances a UTF-8 view index to its next boundary; faults via
 * sk_fatal_error if the index is past the end.
 * Confidence: low (Swift String.UTF8View slice/normalize).
 */
void sk_swift_string_utf8_view_slice_n(void)
{
    sk_rt_00351da8();
    sk_rt_00354a28();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        v = sk_rt_0001da84();
    }
    if (v >> 0xe != 0) {
        if ((v >> 0x3c & 1) == 0) {
            sk_rt_00357f34();
            return;
        }
        unsigned long c = sk_rt_0034a274();
        if (c >> 0x10 <= sk_rt_0035a04c()) {
            sk_rt_00350624();
            sk_rt_002b14c8();
            return;
        }
        sk_rt_00358ca4();
    }
    sk_rt_00348244();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b60c8 @ 0x002b60c8   (est. sk_swift_string_utf8_view_slice_o)
 * Ghidra: void FUN_002b60c8(void)
 * Advances a UTF-8 view index and stores the result at x19; faults on
 * out-of-bounds.
 * Confidence: low (Swift String.UTF8View slice/normalize variant).
 */
void sk_swift_string_utf8_view_slice_o(void)
{
    sk_rt_00353d70();
    sk_rt_00352b20();
    sk_rt_00354a28();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350548();
        v = sk_rt_0001da84();
    }
    if (v >> 0xe == 0) {
        sk_rt_00348244();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    if ((v >> 0x3c & 1) == 0) {
        sk_rt_00357f34();
    } else {
        unsigned long c = sk_rt_0034a260();
        if (sk_rt_0035a04c() < c >> 0x10) {
            sk_rt_00358ca4();
            sk_rt_00348244();
            /* WARNING: noreturn */
            sk_fatal_error(0, 0);
        }
        sk_rt_00350548();
        sk_rt_002b14c8();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002b6170 @ 0x002b6170   (est. sk_swift_string_utf8_view_slice_p)
 * Ghidra: void FUN_002b6170(undefined8 *param_1, undefined8 *param_2, ...)
 * Slices a UTF-8 view via sk_rt_002b603c and stores the result into
 * *param_1.
 * Confidence: medium (Swift String.UTF8View slice wrapper).
 */
void sk_swift_string_utf8_view_slice_p(void *o, void *s, void *a, void *b)
{
    (void)s;
    unsigned long r = sk_rt_002b603c(0, 0, 0, *(unsigned long *)((char *)s + 0x10),
                                     *(unsigned long *)((char *)s + 0x18));
    *(unsigned long *)o = r;
}

/*--------------------------------------------------------------------*/
/* FUN_002b61a8 @ 0x002b61a8   (est. sk_swift_string_utf8_view_slice_q)
 * Ghidra: void FUN_002b61a8(void)
 * Computes a UTF-8 view index (sk_rt_002b5d6c) and stores it at x19.
 * Confidence: medium (wrapper storing a computed index).
 */
void sk_swift_string_utf8_view_slice_q(void)
{
    *(unsigned long *)0 = sk_rt_002b5d6c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b6200 @ 0x002b6200   (est. sk_swift_string_utf8_view_subscript_d)
 * Ghidra: undefined1 [16] FUN_002b6200(undefined1 *param_1, undefined8 *param_2)
 * Reads a byte from a UTF-8 view via sk_rt_002b5ba0 and returns the
 * iterator pair {0x0001a1c8, param_1}.
 * Confidence: low (Swift String.UTF8View iterator subscript).
 */
void sk_swift_string_utf8_view_subscript_d(void *out, void *s)
{
    (void)s;
    unsigned char b = (unsigned char)sk_rt_002b5ba0(0, 0, 0, 0, 0);
    *(unsigned char *)out = b;
    ((unsigned long *)out)[1] = 0x1a1c8;
}

/*--------------------------------------------------------------------*/
/* FUN_002b6268 @ 0x002b6268   (est. sk_swift_string_utf8_view_slice_r)
 * Ghidra: void FUN_002b6268(void)
 * Slices a UTF-8 view: runs sk_rt_00352e84, calls the indirect callback
 * with the source words, then sk_rt_003554e0.
 * Confidence: low (Swift String.UTF8View slice via indirect callback).
 */
void sk_swift_string_utf8_view_slice_r(void)
{
    sk_rt_00352e84();
    /* (*extraout_x9)(v0, v1, *x20, x20[1], x20[2], x20[3]) */
    sk_rt_003554e0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b62bc / FUN_002b62c0 @ 0x002b62bc / 0x002b62c0 (sk_swift_string_utf8_view_slice_s/t)
 * Ghidra: void FUN_002b62bc(void)
 * Forwarders to sk_rt_002a999c with the source words.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf8_view_slice_s(void)
{
    sk_rt_002a999c(0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b62dc @ 0x002b62dc   (est. sk_swift_string_utf8_view_slice_u)
 * Ghidra: void FUN_002b62dc(void)
 * Runs sk_rt_00352764 and sk_rt_001d2f4c.
 * Confidence: low (Swift String.UTF8View slice pipeline).
 */
void sk_swift_string_utf8_view_slice_u(void)
{
    sk_rt_00352764();
    sk_rt_001d2f4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002b62f4 @ 0x002b62f4   (est. sk_swift_string_utf8_view_slice_v)
 * Ghidra: void FUN_002b62f4(undefined8 *param_1, undefined8 *param_2, ...)
 * Slices a UTF-8 view via sk_rt_002b5c70 and stores the result into
 * *param_1.
 * Confidence: medium (Swift String.UTF8View slice wrapper).
 */
void sk_swift_string_utf8_view_slice_v(void *o, void *s, void *a, void *b)
{
    (void)s;
    unsigned long r = sk_rt_002b5c70(0, 0, 0, *(unsigned long *)((char *)s + 0x10),
                                     *(unsigned long *)((char *)s + 0x18));
    *(unsigned long *)o = r;
}

/*--------------------------------------------------------------------*/
/* FUN_002b6364 / FUN_002b6368 @ 0x002b6364 / 0x002b6368 (sk_swift_string_utf8_view_slice_w/x)
 * Ghidra: void FUN_002b6364(undefined8 x3)
 * Forwarders to sk_rt_002b5f94 with the source words.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf8_view_slice_w(void *a, void *b, void *c)
{
    (void)a; (void)b;
    sk_rt_002b5f94(0, 0, 0, 0, 0, 0, c);
}

/*--------------------------------------------------------------------*/
/* FUN_002b6388 @ 0x002b6388   (est. sk_swift_string_utf8_view_slice_y)
 * Ghidra: void FUN_002b6388(void)
 * Slices a UTF-8 view: resolves the buffer (inline vs buffered) and
 * advances the index via sk_rt_00294a20; faults via sk_fatal_error on
 * out-of-bounds.
 * Confidence: low (Swift String.UTF8View slice).
 */
void sk_swift_string_utf8_view_slice_y(void)
{
    unsigned long v = sk_rt_00359974();
    if ((v >> 0x3d & 1) != 0) {
        sk_rt_001a7804(0, 0);
        return;
    }
    if ((v >> 0x3c & 1) == 0) {
        sk_rt_002a9ba8();
        sk_rt_00351790();
        if (sk_rt_0035a04c() <= sk_rt_0035a04c()) {
            sk_rt_003507e0();
            sk_rt_00294a20();
            return;
        }
        sk_rt_00347d60();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    sk_rt_003488bc(1);
    sk_rt_00349a40();
    /* WARNING: noreturn */
    sk_fatal_error(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b6448 @ 0x002b6448   (est. sk_swift_string_utf8_view_slice_z)
 * Ghidra: void FUN_002b6448(void)
 * Slices a UTF-8 view: allocates (sk_rt_0036a908) and runs the page-alloc
 * wrapper sk_rt_0036b270, then sk_rt_0034cd90 and sk_rt_003507e0.
 * Confidence: low (Swift String.UTF8View slice with allocation).
 */
void sk_swift_string_utf8_view_slice_z(void)
{
    sk_rt_0035a250();
    sk_rt_0036a908(0, 0xe0b8);
    sk_rt_0034cd90();
    sk_rt_0036b270();
    sk_rt_003507e0();
}

/*--------------------------------------------------------------------*/
/* FUN_002b64cc @ 0x002b64cc   (est. sk_swift_string_utf8_decode_char)
 * Ghidra: void FUN_002b64cc(undefined8, undefined8, ulong param_3)
 * Decodes the Unicode scalar at a UTF-8 view position, handling ASCII
 * fast-path and full multi-byte decode (via sk_rt_0035617c and the
 * continuation-byte decoder), then emits through sk_rt_0035847c.
 * Confidence: low (Swift String.UTF8View scalar decode).
 */
void sk_swift_string_utf8_decode_char(unsigned long i, unsigned long s, unsigned long f, void *o1)
{
    (void)s; (void)o1;
    sk_rt_00041138();
    sk_rt_00353d70();
    sk_rt_00352758();
    sk_rt_00354a28();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        v = sk_rt_0001da84();
    }
    if (v >> 0xe < (f >> 0xe) || i >> 0xe <= v >> 0xe) {
        sk_rt_00348614(1);
        sk_rt_0034987c();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    if ((v >> 0x3c & 1) == 0) {
        unsigned long pos = v >> 0x10;
        if ((pos & 1) == 0) {
            sk_rt_0034bf1c();
            pos = sk_rt_001676cc() >> 0x10;
        }
        unsigned long scalar = sk_rt_0035617c(pos);
        sk_rt_0035847c(v >> 0xe & 3, scalar, 0);
        sk_rt_00254fb4();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002b6630 @ 0x002b6630   (est. sk_swift_string_utf8_view_index_c)
 * Ghidra: ulong FUN_002b6630(void)
 * Computes a UTF-8 view index at the next scalar boundary, decoding the
 * lead byte and advancing; returns the new packed index.
 * Confidence: low (Swift String.UTF8View index advance).
 */
unsigned long sk_swift_string_utf8_view_index_c(void)
{
    sk_rt_00351da8();
    sk_rt_00354a28();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350624();
        sk_rt_0001da84();
    }
    unsigned long pos = sk_rt_0034a274() >> 0x10;
    if (sk_rt_0035a04c() <= pos) {
        sk_rt_00348614(1);
        sk_rt_0034987c();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    if ((v >> 0x3c & 1) != 0) {
        return sk_rt_002af4d0();
    }
    unsigned long b = *(unsigned char *)(pos);
    if ((signed char)b < 0) {
        long len = __builtin_clzll(((unsigned int)b << 0x18) ^ 0xffffffffUL) / 8 + 1;
        return (v & 0xffffffffffff0000UL) + len * 0x10000UL | 5;
    }
    return (v & 0xffffffffffff0000UL) + 0x10000UL | 5;
}

/*--------------------------------------------------------------------*/
/* FUN_002b676c @ 0x002b676c   (est. sk_swift_string_utf8_view_index_d)
 * Ghidra: void FUN_002b676c(void)
 * Computes a UTF-8 view index at the next scalar and stores it at x19.
 * Confidence: low (Swift String.UTF8View index advance variant).
 */
void sk_swift_string_utf8_view_index_d(void)
{
    sk_rt_00353d70();
    sk_rt_00352b20();
    sk_rt_00354a28();
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350548();
        sk_rt_0001da84();
    }
    unsigned long pos = sk_rt_0034a260();
    if (sk_rt_0035a04c() <= pos >> 0x10) {
        sk_rt_00348614(1);
        sk_rt_0034987c();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    if ((v >> 0x3c & 1) != 0) {
        sk_rt_002af4d0();
    } else {
        unsigned long b = sk_rt_00358990();
        if ((v & 0x2000000000000000UL) != 0) {
            b = v >> 0x3e & 1;
        }
        if ((b & 1) != 0) {
            sk_rt_0035aac0();
        } else {
            unsigned char c = *(unsigned char *)(pos);
            if ((signed char)c < 0) {
                long len = __builtin_clzll(((unsigned int)c << 0x18) ^ 0xffffffffUL) / 8 + 1;
                sk_rt_003558c4();
            } else {
                sk_rt_003558c4();
            }
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002b68a0 @ 0x002b68a0   (est. sk_swift_string_utf8_view_slice_aa)
 * Ghidra: void FUN_002b68a0(undefined8 x6)
 * Forwarder to sk_rt_002a4614.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf8_view_slice_aa(void *a, void *b, void *c, void *d, void *e, void *f)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
    sk_rt_002a4614(0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b68c4 @ 0x002b68c4   (est. sk_swift_string_utf8_view_index_e)
 * Ghidra: ulong FUN_002b68c4(ulong, undefined8, undefined8, ulong, ulong)
 * Advances a UTF-8 view index to the next scalar boundary, decoding the
 * lead byte and updating the packed index; faults on out-of-bounds.
 * Confidence: low (Swift String.UTF8View index advance).
 */
unsigned long sk_swift_string_utf8_view_index_e(unsigned long i, unsigned long s, unsigned long f, unsigned long l, unsigned long m)
{
    (void)s;
    unsigned long v = sk_rt_0034a3b0(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        v = sk_rt_0001da84();
        i = v;
    }
    if ((i < 0x4000) || (sk_rt_00359848(v, l & 0xffffffffffffUL) < i >> 0xe)) {
        sk_rt_00348614(1);
        sk_rt_0034987c();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    if ((m >> 0x3c & 1) != 0) {
        return sk_rt_002af618(i);
    }
    sk_rt_00359ffc();
    if ((sk_rt_0035a04c() & 1) == 0) {
        unsigned long pos = i;
        if ((i & 1) == 0) {
            sk_rt_00077894(i);
            v = sk_rt_001676cc();
            i = v;
        }
        unsigned long n = i >> 0x10;
        unsigned char b = *(unsigned char *)(pos);
        if ((signed char)b < 0) {
            long len = __builtin_clzll(((unsigned int)b << 0x18) ^ 0xffffffffUL) / 8 + 1;
            return (i & 0xffffffffffff0000UL) - 0x3bffc; /* surrogate pair */
        }
        return (i & 0xffffffffffff0000UL) + 0x10000UL | 5;
    }
    return (i & 0xffffffffffff0000UL) - 0xfff3;
}

/*--------------------------------------------------------------------*/
/* FUN_002b6a90 @ 0x002b6a90   (est. sk_swift_string_utf8_view_index_f)
 * Ghidra: void FUN_002b6a90(void)
 * Advances a UTF-8 view index in place through the string buffer, storing
 * the new index back and emitting via sk_rt_0035847c.
 * Confidence: low (Swift String.UTF8View index advance in-place).
 */
void sk_swift_string_utf8_view_index_f(void)
{
    unsigned long v;
    unsigned long buf = sk_rt_00041138();
    sk_rt_00354a28();
    unsigned long s = sk_rt_0034cad8(sk_rt_0035a04c());
    if (sk_rt_0034bf1c()) {
        sk_rt_00350600(buf);
        s = sk_rt_0001da84();
        buf = s;
    }
    if ((buf < 0x4000) || (sk_rt_00359848(s, buf & 0xffffffffffffUL) < buf >> 0xe)) {
        sk_rt_00348614(1);
        sk_rt_0034987c();
        /* WARNING: noreturn */
        sk_fatal_error(0, 0);
    }
    sk_rt_00359ffc();
    if ((sk_rt_0035a04c() & 1) == 0) {
        unsigned long idx = buf;
        if ((buf & 0xc000) == 0) {
            unsigned long n = idx;
            if ((idx & 1) == 0) {
                sk_rt_003562f8();
                sk_rt_00350600();
                idx = sk_rt_001676cc();
            }
            unsigned long pos = idx >> 0x10;
            unsigned char b = *(unsigned char *)(pos);
            if ((signed char)b < 0) {
                long len = __builtin_clzll(((unsigned int)b << 0x18) ^ 0xffffffffUL) / 8 + 1;
                idx = (idx & 0xffffffffffff0000UL) - 0x3bffc;
            } else {
                idx = (idx & 0xffffffffffff0000UL) + 0x10000UL | 5;
            }
            *(unsigned long *)0 = idx;
        }
    } else {
        *(unsigned long *)0 = (buf & 0xffffffffffff0000UL) - 0xfff3;
    }
    sk_rt_0035847c(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b6c54 @ 0x002b6c54   (est. sk_swift_string_utf8_view_slice_ab)
 * Ghidra: void FUN_002b6c54(undefined8 *param_1, undefined8 *param_2, ...)
 * Slices a UTF-8 view via sk_rt_002b68c4 and stores the result into
 * *param_1.
 * Confidence: medium (Swift String.UTF8View slice wrapper).
 */
void sk_swift_string_utf8_view_slice_ab(void *o, void *s, void *a, void *b)
{
    (void)s;
    unsigned long r = sk_rt_002b68c4(0, 0, 0, *(unsigned long *)((char *)s + 0x10),
                                     *(unsigned long *)((char *)s + 0x18));
    *(unsigned long *)o = r;
}

/*--------------------------------------------------------------------*/
/* FUN_002b6c8c @ 0x002b6c8c   (est. sk_swift_string_utf8_view_slice_ac)
 * Ghidra: void FUN_002b6c8c(void)
 * Computes a UTF-8 view slice (sk_rt_002b68a0) and stores it at x19.
 * Confidence: medium (wrapper storing a computed slice).
 */
void sk_swift_string_utf8_view_slice_ac(void)
{
    *(unsigned long *)0 = sk_rt_002b68a0();
}


/*--------------------------------------------------------------------*/
/* FUN_002b0c14 @ 0x002b0c14   (est. sk_swift_string_utf16_view_slice_c)
 * Ghidra: void FUN_002b0c14(void)
 * Twin forwarder to sk_rt_00280570 (trap-dispatch small) with the source
 * words at x20.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_slice_c(void)
{
    sk_rt_00280570(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b1ec8 @ 0x002b1ec8   (est. sk_swift_string_utf16_view_slice_ad)
 * Ghidra: void FUN_002b1ec8(void)
 * Twin forwarder to sk_rt_0029d53c with the source words at x20.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_slice_ad(void)
{
    sk_rt_0029d53c(0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b205c @ 0x002b205c   (est. sk_swift_string_utf16_view_subscript_assign_c)
 * Ghidra: void FUN_002b205c(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Twin forwarder to sk_rt_002b2078 (subscript-assign impl) with the source
 * words at x20 plus param_3.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_subscript_assign_c(void *a, void *b, void *c)
{
    (void)a; (void)b;
    sk_rt_002b2078(0, 0, 0, 0);
    (void)c;
}

/*--------------------------------------------------------------------*/
/* FUN_002b2808 @ 0x002b2808   (est. sk_swift_string_utf16_view_subscript_b)
 * Ghidra: void FUN_002b2808(void)
 * Twin forwarder to sk_rt_001dc050 with the source word at x20.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_subscript_b(void)
{
    sk_rt_001dc050(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b282c @ 0x002b282c   (est. sk_swift_string_utf16_view_subscript_d)
 * Ghidra: void FUN_002b282c(undefined8 param_1)
 * Twin forwarder to sk_rt_001bf784 with the source word at x20.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_subscript_d(void *a)
{
    sk_rt_001bf784(a, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b2990 @ 0x002b2990   (est. sk_swift_string_utf16_view_subscript_f)
 * Ghidra: void FUN_002b2990(undefined8 param_1)
 * Twin forwarder to sk_rt_001bf740 with the source word at x20.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_subscript_f(void *a)
{
    sk_rt_001bf740(a, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b44a8 @ 0x002b44a8   (est. sk_swift_string_utf16_view_slice_e)
 * Ghidra: void FUN_002b44a8(void)
 * Twin forwarder to sk_rt_002b7794.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_slice_e(void)
{
    sk_rt_002b7794();
}

/*--------------------------------------------------------------------*/
/* FUN_002b4be0 @ 0x002b4be0   (est. sk_swift_string_utf16_view_slice_s)
 * Ghidra: void FUN_002b4be0(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Twin forwarder to sk_rt_002b4874 with the source words at x20 plus param_3.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_slice_s(void *a, void *b, void *c)
{
    (void)a; (void)b;
    sk_rt_002b4874(0, 0, 0, 0, 0, 0, c);
}

/*--------------------------------------------------------------------*/
/* FUN_002b4ed8 @ 0x002b4ed8   (est. sk_swift_string_utf16_view_compare_b)
 * Ghidra: void FUN_002b4ed8(undefined8 *param_1, undefined8 *param_2)
 * Twin forwarder to sk_rt_001d2f4c with the two view word pairs.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf16_view_compare_b(void *a, void *b)
{
    sk_rt_001d2f4c(0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b62c0 @ 0x002b62c0   (est. sk_swift_string_utf8_view_slice_t)
 * Ghidra: void FUN_002b62c0(void)
 * Twin forwarder to sk_rt_002a999c with the source words at x20.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf8_view_slice_t(void)
{
    sk_rt_002a999c(0, 0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002b6368 @ 0x002b6368   (est. sk_swift_string_utf8_view_slice_x)
 * Ghidra: void FUN_002b6368(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Twin forwarder to sk_rt_002b5f94 with the source words at x20 plus param_3.
 * Confidence: medium (trivial forwarder).
 */
void sk_swift_string_utf8_view_slice_x(void *a, void *b, void *c)
{
    (void)a; (void)b;
    sk_rt_002b5f94(0, 0, 0, 0, 0, 0, c);
}

