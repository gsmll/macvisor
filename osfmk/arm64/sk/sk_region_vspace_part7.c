/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary;
 * estimates unless matched. This slice (0x24f2a0..0x2550d0) is the cL4 kernel's
 * embedded Swift-runtime support: string/Unicode scalar iteration helpers,
 * Swift Collection/UnsafeBufferPointer slice routines, and a few object/vspace
 * glue thunks built on those primitives. Identity of most functions is inferred
 * from the embedded s_Swift_*_swift_* fatal-error strings and the Unicode /
 * CollectionOfOne / UnsafeBufferPointer callers; confidence medium unless a
 * string/obvious identity matches (high) or the decompiler failed to recover a
 * jump table (low). */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

extern uint64_t rt_00002534();  /* FUN_00002534 */
extern uint64_t rt_000027e8();  /* FUN_000027e8 */
extern uint64_t rt_00012568();  /* FUN_00012568 */
extern uint64_t rt_000126e8();  /* FUN_000126e8 */
extern uint64_t rt_00027754();  /* FUN_00027754 */
extern uint64_t rt_00027788();  /* FUN_00027788 */
extern uint64_t rt_00027818();  /* FUN_00027818 */
extern uint64_t rt_00041138();  /* FUN_00041138 */
extern uint64_t rt_0006b6f4();  /* FUN_0006b6f4 */
extern uint64_t rt_0006f768();  /* FUN_0006f768 */
extern uint64_t rt_0007c0c4();  /* FUN_0007c0c4 */
extern uint64_t rt_0007c198();  /* FUN_0007c198 */
extern uint64_t rt_0007c1a4();  /* FUN_0007c1a4 */
extern uint64_t rt_0007c1c4();  /* FUN_0007c1c4 */
extern uint64_t rt_000839d8();  /* FUN_000839d8 */
extern uint64_t rt_0008412c();  /* FUN_0008412c */
extern uint64_t rt_00084180();  /* FUN_00084180 */
extern uint64_t rt_00084220();  /* FUN_00084220 */
extern uint64_t rt_00084234();  /* FUN_00084234 */
extern uint64_t rt_000867ec();  /* FUN_000867ec */
extern uint64_t rt_0008e500();  /* FUN_0008e500 */
extern uint64_t rt_0008e518();  /* FUN_0008e518 */
extern uint64_t rt_0009461c();  /* FUN_0009461c */
extern uint64_t rt_000a6894();  /* FUN_000a6894 */
extern uint64_t rt_000a68c4();  /* FUN_000a68c4 */
extern uint64_t rt_000a68f4();  /* FUN_000a68f4 */
extern uint64_t rt_000a6e14();  /* FUN_000a6e14 */
extern uint64_t rt_000b43d0();  /* FUN_000b43d0 */
extern uint64_t rt_00100efc();  /* FUN_00100efc */
extern uint64_t rt_00106e3c();  /* FUN_00106e3c */
extern uint64_t rt_00167404();  /* FUN_00167404 */
extern uint64_t rt_0016749c();  /* FUN_0016749c */
extern uint64_t rt_0019e690();  /* FUN_0019e690 */
extern uint64_t rt_0019ea20();  /* FUN_0019ea20 */
extern uint64_t rt_0019fa60();  /* FUN_0019fa60 */
extern uint64_t rt_001a0194();  /* FUN_001a0194 */
extern uint64_t rt_001a1648();  /* FUN_001a1648 */
extern uint64_t rt_001a84f4();  /* FUN_001a84f4 */
extern uint64_t rt_001a8564();  /* FUN_001a8564 */
extern uint64_t rt_001a89a8();  /* FUN_001a89a8 */
extern uint64_t rt_001afa84();  /* FUN_001afa84 */
extern uint64_t rt_001afe4c();  /* FUN_001afe4c */
extern uint64_t rt_001b07b8();  /* FUN_001b07b8 */
extern uint64_t rt_001b6bd8();  /* FUN_001b6bd8 */
extern uint64_t rt_001b6c4c();  /* FUN_001b6c4c */
extern uint64_t rt_001dfc88();  /* FUN_001dfc88 */
extern uint64_t rt_001e088c();  /* FUN_001e088c */
extern uint64_t rt_001e3a28();  /* FUN_001e3a28 */
extern uint64_t rt_001e3f70();  /* FUN_001e3f70 */
extern uint64_t rt_001e4cbc();  /* FUN_001e4cbc */
extern uint64_t rt_001e664c();  /* FUN_001e664c */
extern uint64_t rt_001e6be8();  /* FUN_001e6be8 */
extern uint64_t rt_001e6e60();  /* FUN_001e6e60 */
extern uint64_t rt_001e7038();  /* FUN_001e7038 */
extern uint64_t rt_001e7664();  /* FUN_001e7664 */
extern uint64_t rt_001ee030();  /* FUN_001ee030 */
extern uint64_t rt_001ee0c8();  /* FUN_001ee0c8 */
extern uint64_t rt_001ee0fc();  /* FUN_001ee0fc */
extern uint64_t rt_001f5d68();  /* FUN_001f5d68 */
extern uint64_t rt_00200b38();  /* FUN_00200b38 */
extern uint64_t rt_00205844();  /* FUN_00205844 */
extern uint64_t rt_0021acec();  /* FUN_0021acec */
extern uint64_t rt_0022995c();  /* FUN_0022995c */
extern uint64_t rt_00247360();  /* FUN_00247360 */
extern uint64_t rt_002478d4();  /* FUN_002478d4 */
extern uint64_t rt_0024881c();  /* FUN_0024881c */
extern uint64_t rt_002488b4();  /* FUN_002488b4 */
extern uint64_t rt_0024893c();  /* FUN_0024893c */
extern uint64_t rt_0024abdc();  /* FUN_0024abdc */
extern uint64_t rt_0024ddf0();  /* FUN_0024ddf0 */
extern uint64_t rt_0024f0a0();  /* FUN_0024f0a0 */
extern uint64_t rt_0024f114();  /* FUN_0024f114 */
extern uint64_t rt_0024f23c();  /* FUN_0024f23c */
extern uint64_t rt_00255738();  /* FUN_00255738 */
extern uint64_t rt_0026bd30();  /* FUN_0026bd30 */
extern uint64_t rt_0027d530();  /* FUN_0027d530 */
extern uint64_t rt_0028e8c0();  /* FUN_0028e8c0 */
extern uint64_t rt_0029eb58();  /* FUN_0029eb58 */
extern uint64_t rt_002a200c();  /* FUN_002a200c */
extern uint64_t rt_002a49a8();  /* FUN_002a49a8 */
extern uint64_t rt_002a4b90();  /* FUN_002a4b90 */
extern uint64_t rt_002a4c98();  /* FUN_002a4c98 */
extern uint64_t rt_002a9ba8();  /* FUN_002a9ba8 */
extern uint64_t rt_002a9d64();  /* FUN_002a9d64 */
extern uint64_t rt_002bbcd8();  /* FUN_002bbcd8 */
extern uint64_t rt_002c6d00();  /* FUN_002c6d00 */
extern uint64_t rt_00310d68();  /* FUN_00310d68 */
extern uint64_t rt_003192a8();  /* FUN_003192a8 */
extern uint64_t rt_00319338();  /* FUN_00319338 */
extern uint64_t rt_00319628();  /* FUN_00319628 */
extern uint64_t rt_0031cc3c();  /* FUN_0031cc3c */
extern uint64_t rt_0031cc54();  /* FUN_0031cc54 */
extern uint64_t rt_0031cc6c();  /* FUN_0031cc6c */
extern uint64_t rt_0031cd48();  /* FUN_0031cd48 */
extern uint64_t rt_0031ce04();  /* FUN_0031ce04 */
extern uint64_t rt_0031cf30();  /* FUN_0031cf30 */
extern uint64_t rt_0031cf48();  /* FUN_0031cf48 */
extern uint64_t rt_0031cf70();  /* FUN_0031cf70 */
extern uint64_t rt_0031cfdc();  /* FUN_0031cfdc */
extern uint64_t rt_00347de8();  /* FUN_00347de8 */
extern uint64_t rt_00347f2c();  /* FUN_00347f2c */
extern uint64_t rt_00347fb4();  /* FUN_00347fb4 */
extern uint64_t rt_00348034();  /* FUN_00348034 */
extern uint64_t rt_00348074();  /* FUN_00348074 */
extern uint64_t rt_00348194();  /* FUN_00348194 */
extern uint64_t rt_0034834c();  /* FUN_0034834c */
extern uint64_t rt_003483c4();  /* FUN_003483c4 */
extern uint64_t rt_003486b8();  /* FUN_003486b8 */
extern uint64_t rt_003486fc();  /* FUN_003486fc */
extern uint64_t rt_003488bc();  /* FUN_003488bc */
extern uint64_t rt_0034895c();  /* FUN_0034895c */
extern uint64_t rt_00348b7c();  /* FUN_00348b7c */
extern uint64_t rt_00348b94();  /* FUN_00348b94 */
extern uint64_t rt_00348c48();  /* FUN_00348c48 */
extern uint64_t rt_00348ce8();  /* FUN_00348ce8 */
extern uint64_t rt_00348d4c();  /* FUN_00348d4c */
extern uint64_t rt_00348d64();  /* FUN_00348d64 */
extern uint64_t rt_00348d94();  /* FUN_00348d94 */
extern uint64_t rt_00348e00();  /* FUN_00348e00 */
extern uint64_t rt_00348f38();  /* FUN_00348f38 */
extern uint64_t rt_00348f50();  /* FUN_00348f50 */
extern uint64_t rt_00349068();  /* FUN_00349068 */
extern uint64_t rt_003494e8();  /* FUN_003494e8 */
extern uint64_t rt_00349530();  /* FUN_00349530 */
extern uint64_t rt_003495a8();  /* FUN_003495a8 */
extern uint64_t rt_00349720();  /* FUN_00349720 */
extern uint64_t rt_0034975c();  /* FUN_0034975c */
extern uint64_t rt_003497a0();  /* FUN_003497a0 */
extern uint64_t rt_003497c8();  /* FUN_003497c8 */
extern uint64_t rt_00349830();  /* FUN_00349830 */
extern uint64_t rt_003498a8();  /* FUN_003498a8 */
extern uint64_t rt_00349944();  /* FUN_00349944 */
extern uint64_t rt_003499c8();  /* FUN_003499c8 */
extern uint64_t rt_00349ef4();  /* FUN_00349ef4 */
extern uint64_t rt_00349fcc();  /* FUN_00349fcc */
extern uint64_t rt_0034a148();  /* FUN_0034a148 */
extern uint64_t rt_0034a210();  /* FUN_0034a210 */
extern uint64_t rt_0034a274();  /* FUN_0034a274 */
extern uint64_t rt_0034a2c0();  /* FUN_0034a2c0 */
extern uint64_t rt_0034a32c();  /* FUN_0034a32c */
extern uint64_t rt_0034a450();  /* FUN_0034a450 */
extern uint64_t rt_0034a478();  /* FUN_0034a478 */
extern uint64_t rt_0034a7ac();  /* FUN_0034a7ac */
extern uint64_t rt_0034a900();  /* FUN_0034a900 */
extern uint64_t rt_0034a958();  /* FUN_0034a958 */
extern uint64_t rt_0034aa3c();  /* FUN_0034aa3c */
extern uint64_t rt_0034ab20();  /* FUN_0034ab20 */
extern uint64_t rt_0034aee4();  /* FUN_0034aee4 */
extern uint64_t rt_0034b05c();  /* FUN_0034b05c */
extern uint64_t rt_0034b0c4();  /* FUN_0034b0c4 */
extern uint64_t rt_0034b0d4();  /* FUN_0034b0d4 */
extern uint64_t rt_0034b128();  /* FUN_0034b128 */
extern uint64_t rt_0034b1dc();  /* FUN_0034b1dc */
extern uint64_t rt_0034b278();  /* FUN_0034b278 */
extern uint64_t rt_0034b318();  /* FUN_0034b318 */
extern uint64_t rt_0034b358();  /* FUN_0034b358 */
extern uint64_t rt_0034b3e8();  /* FUN_0034b3e8 */
extern uint64_t rt_0034b518();  /* FUN_0034b518 */
extern uint64_t rt_0034b5e8();  /* FUN_0034b5e8 */
extern uint64_t rt_0034b628();  /* FUN_0034b628 */
extern uint64_t rt_0034b690();  /* FUN_0034b690 */
extern uint64_t rt_0034b778();  /* FUN_0034b778 */
extern uint64_t rt_0034b788();  /* FUN_0034b788 */
extern uint64_t rt_0034b7c8();  /* FUN_0034b7c8 */
extern uint64_t rt_0034b7e4();  /* FUN_0034b7e4 */
extern uint64_t rt_0034b824();  /* FUN_0034b824 */
extern uint64_t rt_0034b89c();  /* FUN_0034b89c */
extern uint64_t rt_0034b9e8();  /* FUN_0034b9e8 */
extern uint64_t rt_0034bb84();  /* FUN_0034bb84 */
extern uint64_t rt_0034bd6c();  /* FUN_0034bd6c */
extern uint64_t rt_0034bf74();  /* FUN_0034bf74 */
extern uint64_t rt_0034c084();  /* FUN_0034c084 */
extern uint64_t rt_0034c094();  /* FUN_0034c094 */
extern uint64_t rt_0034c0a4();  /* FUN_0034c0a4 */
extern uint64_t rt_0034c2a4();  /* FUN_0034c2a4 */
extern uint64_t rt_0034c51c();  /* FUN_0034c51c */
extern uint64_t rt_0034c59c();  /* FUN_0034c59c */
extern uint64_t rt_0034c5bc();  /* FUN_0034c5bc */
extern uint64_t rt_0034c60c();  /* FUN_0034c60c */
extern uint64_t rt_0034c9f8();  /* FUN_0034c9f8 */
extern uint64_t rt_0034ce98();  /* FUN_0034ce98 */
extern uint64_t rt_0034ced8();  /* FUN_0034ced8 */
extern uint64_t rt_0034d044();  /* FUN_0034d044 */
extern uint64_t rt_0034d0e0();  /* FUN_0034d0e0 */
extern uint64_t rt_0034d2b4();  /* FUN_0034d2b4 */
extern uint64_t rt_0034d3c4();  /* FUN_0034d3c4 */
extern uint64_t rt_0034d464();  /* FUN_0034d464 */
extern uint64_t rt_0034da78();  /* FUN_0034da78 */
extern uint64_t rt_0034ddd8();  /* FUN_0034ddd8 */
extern uint64_t rt_0034de14();  /* FUN_0034de14 */
extern uint64_t rt_0034ded4();  /* FUN_0034ded4 */
extern uint64_t rt_0034df04();  /* FUN_0034df04 */
extern uint64_t rt_0034e0e4();  /* FUN_0034e0e4 */
extern uint64_t rt_0034e130();  /* FUN_0034e130 */
extern uint64_t rt_0034e3ac();  /* FUN_0034e3ac */
extern uint64_t rt_0034e72c();  /* FUN_0034e72c */
extern uint64_t rt_0034eb54();  /* FUN_0034eb54 */
extern uint64_t rt_0034eb74();  /* FUN_0034eb74 */
extern uint64_t rt_0034ec48();  /* FUN_0034ec48 */
extern uint64_t rt_0034ecc8();  /* FUN_0034ecc8 */
extern uint64_t rt_0034ed28();  /* FUN_0034ed28 */
extern uint64_t rt_0034ede8();  /* FUN_0034ede8 */
extern uint64_t rt_0034ee38();  /* FUN_0034ee38 */
extern uint64_t rt_0034ee58();  /* FUN_0034ee58 */
extern uint64_t rt_0034f078();  /* FUN_0034f078 */
extern uint64_t rt_0034f198();  /* FUN_0034f198 */
extern uint64_t rt_0034f5f4();  /* FUN_0034f5f4 */
extern uint64_t rt_0034f664();  /* FUN_0034f664 */
extern uint64_t rt_0034f98c();  /* FUN_0034f98c */
extern uint64_t rt_0034fd5c();  /* FUN_0034fd5c */
extern uint64_t rt_0034fe90();  /* FUN_0034fe90 */
extern uint64_t rt_0034ff88();  /* FUN_0034ff88 */
extern uint64_t rt_0034ffb8();  /* FUN_0034ffb8 */
extern uint64_t rt_003501b8();  /* FUN_003501b8 */
extern uint64_t rt_00350328();  /* FUN_00350328 */
extern uint64_t rt_0035047c();  /* FUN_0035047c */
extern uint64_t rt_003504ac();  /* FUN_003504ac */
extern uint64_t rt_003504b8();  /* FUN_003504b8 */
extern uint64_t rt_003504c4();  /* FUN_003504c4 */
extern uint64_t rt_003504e8();  /* FUN_003504e8 */
extern uint64_t rt_00350500();  /* FUN_00350500 */
extern uint64_t rt_00350518();  /* FUN_00350518 */
extern uint64_t rt_00350530();  /* FUN_00350530 */
extern uint64_t rt_003505c4();  /* FUN_003505c4 */
extern uint64_t rt_00350630();  /* FUN_00350630 */
extern uint64_t rt_00350648();  /* FUN_00350648 */
extern uint64_t rt_003506b0();  /* FUN_003506b0 */
extern uint64_t rt_00350744();  /* FUN_00350744 */
extern uint64_t rt_003507bc();  /* FUN_003507bc */
extern uint64_t rt_003507d4();  /* FUN_003507d4 */
extern uint64_t rt_0035084c();  /* FUN_0035084c */
extern uint64_t rt_00350858();  /* FUN_00350858 */
extern uint64_t rt_00350868();  /* FUN_00350868 */
extern uint64_t rt_00350884();  /* FUN_00350884 */
extern uint64_t rt_003508a8();  /* FUN_003508a8 */
extern uint64_t rt_003508d8();  /* FUN_003508d8 */
extern uint64_t rt_003508f0();  /* FUN_003508f0 */
extern uint64_t rt_0035098c();  /* FUN_0035098c */
extern uint64_t rt_003509bc();  /* FUN_003509bc */
extern uint64_t rt_003509c8();  /* FUN_003509c8 */
extern uint64_t rt_00350a04();  /* FUN_00350a04 */
extern uint64_t rt_00350a64();  /* FUN_00350a64 */
extern uint64_t rt_00350a94();  /* FUN_00350a94 */
extern uint64_t rt_00350aa0();  /* FUN_00350aa0 */
extern uint64_t rt_00350ab8();  /* FUN_00350ab8 */
extern uint64_t rt_00350af4();  /* FUN_00350af4 */
extern uint64_t rt_00350b0c();  /* FUN_00350b0c */
extern uint64_t rt_00350b18();  /* FUN_00350b18 */
extern uint64_t rt_00350b54();  /* FUN_00350b54 */
extern uint64_t rt_00350b84();  /* FUN_00350b84 */
extern uint64_t rt_00350b90();  /* FUN_00350b90 */
extern uint64_t rt_00350bd8();  /* FUN_00350bd8 */
extern uint64_t rt_00350c2c();  /* FUN_00350c2c */
extern uint64_t rt_00350c38();  /* FUN_00350c38 */
extern uint64_t rt_00350d94();  /* FUN_00350d94 */
extern uint64_t rt_00350ed0();  /* FUN_00350ed0 */
extern uint64_t rt_00350fdc();  /* FUN_00350fdc */
extern uint64_t rt_0035102c();  /* FUN_0035102c */
extern uint64_t rt_00351094();  /* FUN_00351094 */
extern uint64_t rt_003510c4();  /* FUN_003510c4 */
extern uint64_t rt_0035113c();  /* FUN_0035113c */
extern uint64_t rt_003511c0();  /* FUN_003511c0 */
extern uint64_t rt_00351274();  /* FUN_00351274 */
extern uint64_t rt_003512f4();  /* FUN_003512f4 */
extern uint64_t rt_00351348();  /* FUN_00351348 */
extern uint64_t rt_00351450();  /* FUN_00351450 */
extern uint64_t rt_00351494();  /* FUN_00351494 */
extern uint64_t rt_003515b4();  /* FUN_003515b4 */
extern uint64_t rt_003515d8();  /* FUN_003515d8 */
extern uint64_t rt_003516cc();  /* FUN_003516cc */
extern uint64_t rt_003516e4();  /* FUN_003516e4 */
extern uint64_t rt_00351774();  /* FUN_00351774 */
extern uint64_t rt_0035187c();  /* FUN_0035187c */
extern uint64_t rt_003518dc();  /* FUN_003518dc */
extern uint64_t rt_0035193c();  /* FUN_0035193c */
extern uint64_t rt_00351a50();  /* FUN_00351a50 */
extern uint64_t rt_00351a5c();  /* FUN_00351a5c */
extern uint64_t rt_00351aa4();  /* FUN_00351aa4 */
extern uint64_t rt_00351aec();  /* FUN_00351aec */
extern uint64_t rt_00351b78();  /* FUN_00351b78 */
extern uint64_t rt_00351be0();  /* FUN_00351be0 */
extern uint64_t rt_00351c88();  /* FUN_00351c88 */
extern uint64_t rt_00351cc4();  /* FUN_00351cc4 */
extern uint64_t rt_00351d00();  /* FUN_00351d00 */
extern uint64_t rt_00351d30();  /* FUN_00351d30 */
extern uint64_t rt_00351d9c();  /* FUN_00351d9c */
extern uint64_t rt_00351e08();  /* FUN_00351e08 */
extern uint64_t rt_00351e20();  /* FUN_00351e20 */
extern uint64_t rt_00351f10();  /* FUN_00351f10 */
extern uint64_t rt_00351f1c();  /* FUN_00351f1c */
extern uint64_t rt_00352018();  /* FUN_00352018 */
extern uint64_t rt_003522d4();  /* FUN_003522d4 */
extern uint64_t rt_003523f0();  /* FUN_003523f0 */
extern uint64_t rt_00352680();  /* FUN_00352680 */
extern uint64_t rt_00352938();  /* FUN_00352938 */
extern uint64_t rt_00352a4c();  /* FUN_00352a4c */
extern uint64_t rt_00352ad8();  /* FUN_00352ad8 */
extern uint64_t rt_00352bd4();  /* FUN_00352bd4 */
extern uint64_t rt_00352bec();  /* FUN_00352bec */
extern uint64_t rt_00352c80();  /* FUN_00352c80 */
extern uint64_t rt_00352db8();  /* FUN_00352db8 */
extern uint64_t rt_00352ddc();  /* FUN_00352ddc */
extern uint64_t rt_00352e0c();  /* FUN_00352e0c */
extern uint64_t rt_00352ea8();  /* FUN_00352ea8 */
extern uint64_t rt_00352ecc();  /* FUN_00352ecc */
extern uint64_t rt_00352efc();  /* FUN_00352efc */
extern uint64_t rt_003530d8();  /* FUN_003530d8 */
extern uint64_t rt_003531d8();  /* FUN_003531d8 */
extern uint64_t rt_00353220();  /* FUN_00353220 */
extern uint64_t rt_003532a8();  /* FUN_003532a8 */
extern uint64_t rt_00353448();  /* FUN_00353448 */
extern uint64_t rt_00353468();  /* FUN_00353468 */
extern uint64_t rt_00353528();  /* FUN_00353528 */
extern uint64_t rt_0035370c();  /* FUN_0035370c */
extern uint64_t rt_003538b0();  /* FUN_003538b0 */
extern uint64_t rt_00353ad8();  /* FUN_00353ad8 */
extern uint64_t rt_00353b40();  /* FUN_00353b40 */
extern uint64_t rt_00353cfc();  /* FUN_00353cfc */
extern uint64_t rt_00353d14();  /* FUN_00353d14 */
extern uint64_t rt_00353d64();  /* FUN_00353d64 */
extern uint64_t rt_00353ed8();  /* FUN_00353ed8 */
extern uint64_t rt_00353ef0();  /* FUN_00353ef0 */
extern uint64_t rt_003542b0();  /* FUN_003542b0 */
extern uint64_t rt_003542c4();  /* FUN_003542c4 */
extern uint64_t rt_003543a0();  /* FUN_003543a0 */
extern uint64_t rt_003543dc();  /* FUN_003543dc */
extern uint64_t rt_0035454c();  /* FUN_0035454c */
extern uint64_t rt_00354798();  /* FUN_00354798 */
extern uint64_t rt_003547f8();  /* FUN_003547f8 */
extern uint64_t rt_00354828();  /* FUN_00354828 */
extern uint64_t rt_003548dc();  /* FUN_003548dc */
extern uint64_t rt_00354cfc();  /* FUN_00354cfc */
extern uint64_t rt_00354d80();  /* FUN_00354d80 */
extern uint64_t rt_00354d94();  /* FUN_00354d94 */
extern uint64_t rt_00354e0c();  /* FUN_00354e0c */
extern uint64_t rt_00354edc();  /* FUN_00354edc */
extern uint64_t rt_00355988();  /* FUN_00355988 */
extern uint64_t rt_00355b38();  /* FUN_00355b38 */
extern uint64_t rt_00355b68();  /* FUN_00355b68 */
extern uint64_t rt_00355c78();  /* FUN_00355c78 */
extern uint64_t rt_00355ca4();  /* FUN_00355ca4 */
extern uint64_t rt_00355e68();  /* FUN_00355e68 */
extern uint64_t rt_00355f70();  /* FUN_00355f70 */
extern uint64_t rt_00355fa0();  /* FUN_00355fa0 */
extern uint64_t rt_00356194();  /* FUN_00356194 */
extern uint64_t rt_003562c8();  /* FUN_003562c8 */
extern uint64_t rt_003562d4();  /* FUN_003562d4 */
extern uint64_t rt_00356328();  /* FUN_00356328 */
extern uint64_t rt_003564d0();  /* FUN_003564d0 */
extern uint64_t rt_00356b44();  /* FUN_00356b44 */
extern uint64_t rt_00356bb0();  /* FUN_00356bb0 */
extern uint64_t rt_00356fd8();  /* FUN_00356fd8 */
extern uint64_t rt_00357050();  /* FUN_00357050 */
extern uint64_t rt_003577a0();  /* FUN_003577a0 */
extern uint64_t rt_00357a68();  /* FUN_00357a68 */
extern uint64_t rt_00357b7c();  /* FUN_00357b7c */
extern uint64_t rt_00357c44();  /* FUN_00357c44 */
extern uint64_t rt_00357c74();  /* FUN_00357c74 */
extern uint64_t rt_00357ca0();  /* FUN_00357ca0 */
extern uint64_t rt_00357cb4();  /* FUN_00357cb4 */
extern uint64_t rt_00357f74();  /* FUN_00357f74 */
extern uint64_t rt_00358144();  /* FUN_00358144 */
extern uint64_t rt_003583dc();  /* FUN_003583dc */
extern uint64_t rt_0035847c();  /* FUN_0035847c */
extern uint64_t rt_003586d8();  /* FUN_003586d8 */
extern uint64_t rt_00358858();  /* FUN_00358858 */
extern uint64_t rt_00358c74();  /* FUN_00358c74 */
extern uint64_t rt_00358cd4();  /* FUN_00358cd4 */
extern uint64_t rt_00358d70();  /* FUN_00358d70 */
extern uint64_t rt_00358e88();  /* FUN_00358e88 */
extern uint64_t rt_00359024();  /* FUN_00359024 */
extern uint64_t rt_003591d0();  /* FUN_003591d0 */
extern uint64_t rt_00359360();  /* FUN_00359360 */
extern uint64_t rt_003593a8();  /* FUN_003593a8 */
extern uint64_t rt_003593c0();  /* FUN_003593c0 */
extern uint64_t rt_0035946c();  /* FUN_0035946c */
extern uint64_t rt_003594f4();  /* FUN_003594f4 */
extern uint64_t rt_00359bec();  /* FUN_00359bec */
extern uint64_t rt_00359f3c();  /* FUN_00359f3c */
extern uint64_t rt_00359fb4();  /* FUN_00359fb4 */
extern uint64_t rt_0035a010();  /* FUN_0035a010 */
extern uint64_t rt_0035a01c();  /* FUN_0035a01c */
extern uint64_t rt_0035a11c();  /* FUN_0035a11c */
extern uint64_t rt_0035a140();  /* FUN_0035a140 */
extern uint64_t rt_0035a268();  /* FUN_0035a268 */
extern uint64_t rt_0035a2c4();  /* FUN_0035a2c4 */
extern uint64_t rt_0035a2f0();  /* FUN_0035a2f0 */
extern uint64_t rt_0035a52c();  /* FUN_0035a52c */
extern uint64_t rt_0035a584();  /* FUN_0035a584 */
extern uint64_t rt_0035a6f4();  /* FUN_0035a6f4 */
extern uint64_t rt_0035a7c0();  /* FUN_0035a7c0 */
extern uint64_t rt_0035a7d4();  /* FUN_0035a7d4 */
extern uint64_t rt_0035a7e8();  /* FUN_0035a7e8 */
extern uint64_t rt_0035aafc();  /* FUN_0035aafc */
extern uint64_t rt_0035aba4();  /* FUN_0035aba4 */
extern uint64_t rt_0035acdc();  /* FUN_0035acdc */
extern uint64_t rt_00362bc0();  /* FUN_00362bc0 */
extern uint64_t rt_00362c34();  /* FUN_00362c34 */
extern uint64_t rt_0036a908();  /* FUN_0036a908 */
extern uint64_t rt_0036a940();  /* FUN_0036a940 */
extern uint64_t rt_0036b118();  /* FUN_0036b118 */
extern uint64_t rt_0036b270();  /* FUN_0036b270 */
extern uint64_t rt_003722e4();  /* FUN_003722e4 */
extern uint64_t rt_00376820();  /* FUN_00376820 */
extern uint64_t rt_00377824();  /* FUN_00377824 */
extern uint64_t rt_00377bec();  /* FUN_00377bec */
extern uint64_t rt_0039fcc4();  /* FUN_0039fcc4 */
extern uint64_t rt_003a25d4();  /* FUN_003a25d4 */
extern uint64_t rt_003a265c();  /* FUN_003a265c */
extern uint64_t rt_003a2898();  /* FUN_003a2898 */

uint64_t sk_swift_alloc_concat(void *param_1, void *param_2, void *param_3);
void sk_swift_alloc_string(void);
void sk_swift_append_11(void *param_1, void *param_2, unsigned long param_3);
void sk_swift_append_12(void *param_1, void *param_2, unsigned long param_3);
void sk_swift_builder_append(void *param_1, void *param_2, unsigned long param_3, long param_4,
                             unsigned long param_5, void *param_6, long param_7, void *param_8);
uint64_t sk_swift_codepoint_words(unsigned int param_1);
long sk_swift_collection_count(void);
long sk_swift_collection_count2(void);
void sk_swift_concat_builder(void *param_1, void *param_2, uint32_t *param_3, unsigned long param_4);
uint64_t sk_swift_concat_release(void);
uint64_t sk_swift_coo_valid(long param_1);
void sk_swift_copy_word(void *param_1, void *param_2);
void sk_swift_dispatch_1(void);
void sk_swift_dispatch_2(void);
void sk_swift_dispatch_3(void);
void sk_swift_dispatch_4(void);
void sk_swift_dispatch_6(void);
void sk_swift_dispatch_7(void *param_1, void *param_2, void *jmp);
void sk_swift_dispatch_8(void);
void sk_swift_dump_state(void *param_1, void *param_2, void *param_3, void *param_4);
void sk_swift_dump_state10(void);
void sk_swift_dump_state11(void);
void sk_swift_dump_state12(void);
void sk_swift_dump_state13(void);
void sk_swift_dump_state14(void);
void sk_swift_dump_state15(void);
void sk_swift_dump_state16(void *param_1, void *param_2, long param_3);
void sk_swift_dump_state17(void *param_1, void *param_2, void *param_3, void *param_4,
                           void *param_5, void *param_6, void *param_7);
void sk_swift_dump_state18(void);
void sk_swift_dump_state19(long param_1);
void sk_swift_dump_state2(void *p1, void *p2, void *p3, void *p4, void *p5, void *p6);
void sk_swift_dump_state20(void);
void sk_swift_dump_state21(void);
void sk_swift_dump_state22(void *param_1, void *param_2, void *param_3);
void sk_swift_dump_state23(void);
void sk_swift_dump_state24(void);
void sk_swift_dump_state25(void);
void sk_swift_dump_state26(void);
void sk_swift_dump_state27(void);
void sk_swift_dump_state28(void);
void sk_swift_dump_state29(void);
void sk_swift_dump_state3(void);
void sk_swift_dump_state30(void);
void sk_swift_dump_state31(void *param_1, void *param_2, long param_3, void *param_4, void *param_5);
void sk_swift_dump_state33(void *param_1, void *param_2);
void sk_swift_dump_state34(void);
void sk_swift_dump_state4(void);
void sk_swift_dump_state5(void);
void sk_swift_dump_state6(void);
void sk_swift_dump_state7(void);
void sk_swift_dump_state8(void);
void sk_swift_dump_state9(void);
void sk_swift_escape_encoder(void);
void sk_swift_fatal_break(void);
void sk_swift_fatal_code(void);
void sk_swift_fatal_code2(void);
void sk_swift_fatal_code3(void);
void sk_swift_fatal_code4(void);
void sk_swift_fatal_code5(void);
void sk_swift_fatal_msg(void *param_1, void *param_2, void *param_3);
void sk_swift_hex_digit(unsigned int param_1);
void sk_swift_hex_string(unsigned long param_1);
void sk_swift_keypath_sink(void);
void sk_swift_keypath_sink2(void);
void sk_swift_keypath_sink3(void);
void sk_swift_keypath_teardown(void);
long sk_swift_make_string(void *param_1, void *param_2, unsigned long param_3);
unsigned long sk_swift_next_scalar(void);
void sk_swift_release_obj_1(void);
void sk_swift_release_obj_2(void);
void sk_swift_release_slot_1(void *param_1);
void sk_swift_release_slot_2(void *param_1);
unsigned long sk_swift_scalar_pos(unsigned long param_1, unsigned long param_2);
void sk_swift_scalar_store32(uint32_t *param_1);
unsigned long sk_swift_string_advance(void *param_1, unsigned long param_2, unsigned long param_3);
void sk_swift_string_advance_store(void);
unsigned int sk_swift_string_align(void);
void sk_swift_string_append_1(void *param_1, void *param_2, void *param_3);
void sk_swift_string_append_10(void *param_1, void *param_2, void *param_3);
void sk_swift_string_append_2(void);
void sk_swift_string_append_3(void *param_1, void *param_2, void *param_3);
void sk_swift_string_append_4(void *param_1, void *param_2);
void sk_swift_string_append_5(void *param_1, void *param_2, void *param_3);
void sk_swift_string_append_6(void *param_1);
void sk_swift_string_append_7(void *param_1);
void sk_swift_string_append_8(void);
void sk_swift_string_append_9(void *param_1, void *param_2, void *param_3);
void sk_swift_string_append_slice(void *param_1, void *param_2, void *param_3);
unsigned long sk_swift_string_len(void);
unsigned char sk_swift_string_min_align(void);
long sk_swift_string_offset(long param_1, long param_2);
long sk_swift_string_offset2(long param_1);
void sk_swift_string_validate(void);
void sk_swift_unicode_emit(void *param_1, void *param_2, void *param_3, void *param_4);
unsigned long sk_swift_utf16_encode(long param_1, unsigned long param_2);
unsigned long sk_swift_utf8_iterate(void);
unsigned long sk_swift_utf8_scalar_len(void *param_1, unsigned long param_2, unsigned long param_3);
void sk_swift_utf8_scalar_store(unsigned long *param_1, unsigned long param_2, unsigned long param_3);
void sk_swift_xor_string(void);
void sk_swift_xor_string2(void);
void sk_swift_apply_2(void *param_1, void (*param_2)(void *), void *param_3, void *param_4, long param_5, void *param_6, long *param_7);
void sk_swift_apply_3(void *param_1, void *param_2, void (*param_3)(void *, void *));
void sk_swift_apply_4(void *param_1, void (*param_2)(void *, long, long, void *), void *param_3, long param_4, long param_5, void *param_6, long param_7, void *param_8, void *param_9, void *param_10);
void sk_swift_apply_5(void *param_1, void *param_2, void (*param_3)(void *, void *), void *param_4, long param_5, void *param_6, long param_7, void *param_8, void *param_9);
void sk_swift_apply_6(void *param_1, void *param_2, void (*param_3)(void *, void *), void *param_4, long param_5, void *param_6, long param_7, void *param_8, void *param_9);
void sk_swift_apply_fn_1(void *param_1, void (*fn)(void));
void sk_swift_apply_fn_2(void *param_1, void (*fn)(void));
void sk_swift_apply_fn_3(void *param_1, void (*fn)(void));
unsigned int sk_swift_coo_index(long param_1, unsigned int param_2, void (*param_3)(unsigned int *, unsigned int *));
void sk_swift_dispatch_5(long param_1, void (*param_2)(unsigned long), void *jmp);
unsigned long sk_swift_utf8_decode_scalar(void *param_1, unsigned long param_2, unsigned long param_3, void (*param_4)(void *, unsigned int *));
extern const void *swift_keypath_str;   /* s_Unsupported_KeyPath_type_to_be_r_005d3a60 */
extern uint64_t DAT_005ce74b, DAT_005ce74f, DAT_005ce751, DAT_005ce754, DAT_005ce757,
         DAT_005ce75a, DAT_005ce75d, DAT_005ce760, DAT_005ce763, DAT_004e7a30;
void *sk_swift_keypath_dict_2(void *param_1, void *param_2, void *param_3, void *param_4, void *param_5);
void *sk_swift_unicode_len_init(void *param_1, void *param_2, long param_3, void *param_4);
void *sk_swift_unicode_len_init2(void *param_1, void *param_2, long param_3, void *param_4);
extern uint64_t rt_00255738();           /* swift_emit_char (in-slice sibling) */

extern uint64_t rt_0021acec();           /* slice sibling */
extern uint64_t rt_002a4c98();           /* slice sibling */
extern uint64_t rt_00205844();           /* slice sibling */
extern uint64_t rt_002478d4();           /* slice sibling */
extern uint64_t rt_002a49a8();           /* slice sibling */
extern uint64_t rt_002bbcd8();           /* slice sibling */
extern uint64_t rt_0029eb58();           /* slice sibling */
extern uint64_t rt_002c6d00();           /* slice sibling */
extern uint64_t rt_002a9d64();           /* slice sibling */
extern uint64_t rt_0022995c();           /* slice sibling */
extern uint64_t rt_0024893c();           /* slice sibling */
extern uint64_t rt_002488b4();           /* slice sibling */
extern uint64_t rt_0021acec();           /* slice sibling */

/*--------------------------------------------------------------------*/
/* FUN_0024f2a0 @ 0x0024f2a0   (est. sk_swift_concat_builder)
 * Ghidra: void FUN_0024f2a0(undefined8 param_1, undefined8 param_2, uint *param_3, ulong param_4)
 * Appends bytes to a growing Swift string buffer: saves/restores the builder
 * context word pair, writes a 0/1 flag byte at the write cursor (header at
 * x20[6], cursor at +0x10, payload at +0x20), then dispatches on the low byte
 * of param_4 (character kind) to emit the encoded form through the byte emitter
 * FUN_0024f0a0. The count at x20[5] increments with a SoftwareBreakpoint carry
 * trap.
 * Confidence: medium (Swift String append; identity inferred).
 * Notes: unaff_x20 is the builder context; FUN_00351e20/00354edc/003543dc are
 *   runtime barriers; SoftwareBreakpoint at 0x24f46c/0x24f470. */
void sk_swift_concat_builder(void *param_1, void *param_2, uint32_t *param_3, unsigned long param_4)
{
    uint64_t fl = rt_00351e20();                 /* builder flags (auVar11) */
    unsigned long uVar4 = fl >> 0x40;            /* high flags */
    unsigned int  uVar3 = (unsigned int)fl;      /* low flags */
    void **ctx = param_2;                        /* unaff_x20 */
    unsigned long saved = (unsigned long)ctx[10];
    long lVar9;
    (void)param_1;
    ctx[10] = ctx[0];
    rt_00354edc();                               /* runtime entry barrier */
    lVar9 = *(long *)((char *)ctx[6] + 0x10);
    rt_003543dc();                               /* runtime barrier */
    rt_001a1648(lVar9);                          /* buffer-advance primitive */
    *(long *)((char *)ctx[6] + 0x10) = lVar9 + 1;
    if ((uVar3 & 0xff) == 1) {
        *(unsigned char *)((char *)ctx[6] + 0x20 + lVar9) = 0;
        if ((uVar4 & 1) != 0) ctx[9] = (void *)saved;
    } else {
        *(unsigned char *)((char *)ctx[6] + 0x20 + lVar9) = 1;
    }
    unsigned int uVar8 = (unsigned int)(uintptr_t)param_3;
    switch (param_4 & 0xff) {
    case 1:
        rt_00357a68(uVar3 & 0xff);
        rt_0024f0a0(0xffffff);
        rt_0024f0a0((unsigned long)param_3);
        rt_00351d30(0);
        return;
    case 2:
        if ((fl & 0xff) == 0) {
            unsigned long p = rt_001ee0c8((unsigned long)param_3 & 0xffffffff, ctx[4]);
            unsigned long c = (unsigned long)*(unsigned int *)(ctx + 5) + (unsigned int)p;
            if (c < (unsigned long)*(unsigned int *)(ctx + 5)) { /* carry -> breakpoint */ }
            *(unsigned int *)(ctx + 5) = (unsigned int)c;
            rt_0024f0a0(0x1000000 | 0x800000 | 0x7fffff);
        } else {
            unsigned long p = rt_001ee0fc();
            if (p >> 0x20 != 0) {
                rt_003583dc(); rt_00348194(); rt_003523f0();
                rt_001afe4c();                 /* fatal, noreturn */
            }
            rt_0024f0a0(0x3000000 | 0x800000 | 0x7fffff);
        }
        rt_0024f0a0((unsigned long)param_3);
        rt_00351d30(0);
        return;
    case 3:
        param_3 = (uint32_t *)(uintptr_t)*param_3;
        rt_00357a68(uVar3 & 0xff);
        rt_0024f0a0(0xffffff);
        rt_0024f0a0((unsigned long)param_3);
        rt_00351d30(0);
        return;
    default:
        {
            unsigned long uVar5 = (uVar4 & 1) ? 0x800000 : 0;
            unsigned long uVar7 = ((uVar3 & 0xff) != 1) ? 0x1000000 : 0x3000000;
            rt_0024f0a0(uVar5 | uVar8 | uVar7);
            if ((uVar3 & 0xff) != 1) {
                unsigned int c = *(unsigned int *)(ctx + 5) + uVar8;
                if (c < *(unsigned int *)(ctx + 5)) { /* carry -> breakpoint */ }
                *(unsigned int *)(ctx + 5) = c;
            }
            rt_00351d30(0);
            return;
        }
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0024f498 @ 0x0024f498   (est. sk_swift_builder_append)
 * Ghidra: void FUN_0024f498(undefined8 param_1, undefined8 param_2, ulong param_3,
 *          long param_4, ulong param_5, undefined8 param_6, long param_7, code *param_8)
 * Larger string-builder append: writes a leading 0 flag byte, then based on the
 * low byte of param_3 (0/1/2/3) chooses a payload source (pointer arithmetic,
 * an allocation, or an indirect call through ctx[3]), selects a 0x80000/
 * 0x480000/0x880000/0xc80000 length/flag word, and emits through FUN_0024f0a0 /
 * FUN_0024f114 / FUN_0024f23c. When param_8 (a sink closure) is non-null it
 * copies the produced bytes into a second buffer with an alignment/copy loop.
 * Confidence: medium (Swift string builder; identity inferred).
 * Notes: SoftwareBreakpoint at 0x24f920/0x24f924/0x24f928/0x24f954/0x24f958/
 *   0x24f91c; references LAB_00657758 (Swift string object). */
void sk_swift_builder_append(void *param_1, void *param_2, unsigned long param_3, long param_4,
                             unsigned long param_5, void *param_6, long param_7, void *param_8)
{
    uint64_t fl = rt_0035193c();
    unsigned long uVar13 = fl;
    unsigned int  uVar3 = (unsigned int)(fl >> 0x40) & 0xff;
    void **ctx = param_2;                        /* unaff_x20 */
    long lVar22;
    bool bVar7 = param_7 != 0;
    unsigned int uVar10, uVar11, uVar17;

    rt_00354edc();
    lVar22 = *(long *)((char *)ctx[6] + 0x10);
    rt_003543dc();
    rt_001a1648(lVar22);
    *(long *)((char *)ctx[6] + 0x10) = lVar22 + 1;
    *(unsigned char *)((char *)ctx[6] + lVar22 + 0x20) = 0;
    unsigned long uVar12 = (unsigned long)ctx[10];
    ctx[10] = ctx[0];
    if (param_7 != 0 && (uVar13 & 1) == 0) { ctx[9] = (void *)uVar12; bVar7 = true; }
    unsigned int uVar10b = uVar3 - 1;
    bool uVar8 = (uVar10b == 1);
    long pcVar5 = (long)(param_5 & 0xffffffff);
    if (1 < uVar10b) {
        long pcVar1 = param_4 + (long)(int)param_5;
        uVar8 = (param_3 & 0xff) == 3;
        switch (param_3 & 0xff) {
        case 0: pcVar5 = pcVar1; break;
        case 1: break;
        case 2: pcVar5 = (long)rt_001ee0fc(0); break;
        case 3:
            if (pcVar1 == 0) { rt_00347f2c(); rt_001afe4c(); }
            pcVar5 = (long)rt_001ee0fc((unsigned long)pcVar1);
            break;
        }
    }
    uVar11 = 0; uVar10 = 0x80000;
    if (param_8 == 0) {
        if ((uVar13 & 1) == 0) {
            if (bVar7) { uVar17 = 0x480000; uVar10 = 0x400000; }
            else { rt_0035a584(); if (!uVar8) { uVar11 = 0; uVar10 = 0x80000; }
                   else { uVar11 = 0; uVar10 = 0; } }
        } else if (bVar7) { uVar17 = 0xc80000; uVar10 = 0xc00000; }
        else { rt_0035a584(); if (!uVar8) { uVar11 = 0; uVar10 = 0x800000; }
               else { uVar11 = 0; uVar10 = 0; } }
    } else {
        rt_0035a584();
        if (uVar8) {
            if ((uVar13 & 1) == 0) { if (bVar7) { uVar11 = 0; uVar10 = 0x480000; }
                                     else { uVar11 = 0; uVar10 = 0x80000; } }
            else if (bVar7) { uVar11 = 0; uVar10 = 0xc80000; }
            else { uVar11 = 0; uVar10 = 0x880000; }
        } else {
            uVar10 = bVar7 ? 0x480000 : 0x80000;
            uVar17 = bVar7 ? 0xc80000 : 0x880000;
            uVar11 = 0x10;
            if ((uVar13 & 1) != 0) uVar10 = uVar17;
        }
    }
    uVar10 |= uVar11;
    uVar17 = uVar10 | ((uVar3 != 1) ? 0x100000 : 0x200000);
    if (((fl >> 0x40) & 0xff) != 0) uVar10 = uVar17;
    rt_0024f0a0(uVar10 | 0x2000000);
    rt_0024f114(pcVar5);
    rt_0024f23c((unsigned long)param_6, 0x6f72);
    if (param_7 != 0) {
        bool k = (uVar13 & 1) == 0;
        rt_0024f23c((unsigned long)param_7, k ? 0x6f70 : 0x7469);
    }
    if (param_8 == 0) {
        rt_0035a584();
        rt_0035a52c();
        rt_0024f114(0);
        rt_0024f114(0);
    } else {
        rt_0024f114(0);
        rt_0024f114(0);
        long lv = (long)rt_0024abdc(0);
        if (lv != 0) *(unsigned char *)(ctx + 8) = 0;
        rt_00350530();
    }
    rt_00351774(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0024f97c @ 0x0024f97c   (est. sk_swift_fatal_code)
 * Ghidra: void FUN_0024f97c(void)
 * Fatal error shim: reports code 1 then enters the noreturn fatal handler.
 * Confidence: high (noreturn fatal; trivial body). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_fatal_code(void)
{
    rt_00347de8(1);
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0024f99c @ 0x0024f99c   (est. sk_swift_make_string)
 * Ghidra: long FUN_0024f99c(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Constructs a Swift string object: sets up the closure context, allocates a
 * builder, installs a closure, then conditionally stores ~param_3 into the
 * object header (+0x10) when the caller flag is set.
 * Confidence: medium (Swift string init; identity inferred). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
long sk_swift_make_string(void *param_1, void *param_2, unsigned long param_3)
{
    rt_0034e130((unsigned long)param_1, (unsigned long)param_2, (unsigned long)param_2);
    long lVar1 = (long)rt_0031cc54();
    rt_00247360(0xc, rt_0031cd48(), 0);   /* install closure */
    rt_00353528();
    rt_0039fcc4();
    rt_0027d530();
    rt_003594f4();
    if ((bool)rt_0008412c() && (long)param_3 >= 0) {
        *(unsigned long *)(lVar1 + 0x10) = ~param_3;
    }
    return lVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_0024fa2c @ 0x0024fa2c   (est. sk_swift_keypath_sink)
 * Ghidra: void FUN_0024fa2c(void)
 * KeyPath sink: reads the context, selects the keypath type builder
 * (FUN_0031cc6c or FUN_0031cc54), then copies a 16-byte header into a freshly
 * allocated 0x40-byte object and registers it with a closure.
 * Confidence: medium (Swift KeyPath; identity from s_Unsupported_KeyPath string).
 * Notes: SoftwareBreakpoint at 0x24fb84/0x24fb88/0x24fb8c. */
void sk_swift_keypath_sink(void)
{
    long lVar5;                                 /* unaff_x22 */
    rt_00084220();
    rt_0035a2c4();
    uint64_t kp = rt_0024881c();
    long lVar3 = (long)(kp & 0xffffffffffff);
    lVar5 = (long)rt_0031cc6c();
    void (*fn)(void) = (void (*)(void))*(void **)(lVar5 + 0x50);
    fn(); fn();
    rt_0034f5f4();
    if (rt_0031cc6c() == (uint64_t)lVar5) {
        uint64_t t = rt_003504e8();
        rt_0031cc6c(t, t >> 0x40, 0);
    } else {
        rt_0034f5f4();
        if (rt_0031cc54() != (uint64_t)lVar5) {
            rt_0034a478((unsigned long)swift_keypath_str);
            rt_003593c0();
            rt_0006f768();
            rt_003532a8();                     /* fatal, noreturn */
        }
        uint64_t t = rt_003504e8();
        rt_0031cc54(t, t >> 0x40, 0);
    }
    unsigned long uVar4 = (lVar3 + 0xfU) & ~7ull;
    uint64_t a = rt_00355b38();
    rt_00247360(a, rt_0031ce04());
    rt_003504e8();
    rt_0031cc3c();
    rt_0035a7e8();
    rt_0035187c();
    rt_00362bc0();
    rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0024fbbc @ 0x0024fbbc   (est. sk_swift_keypath_sink2)
 * Ghidra: void FUN_0024fbbc(void)
 * KeyPath stringifier: reads the current keypath through the method table at
 * [x16+0x50], converts it to a Swift string, prepends a '\\' escape, and prints
 * the result via the diagnostic output FUN_0009461c.
 * Confidence: medium (Swift KeyPath description; identity inferred). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_keypath_sink2(void)
{
    rt_00041138();
    rt_0035a010();
    rt_00356194();
    rt_003a25d4(0xe000000000000000);
    rt_00356194();
    uint64_t p = rt_00354d80();
    rt_00353d64(p, p >> 0x40, p);
    rt_0034895c();
    rt_00205844(0, 0);
    rt_00352ad8(0);
    rt_0036b270(0xe000000000000000);
    rt_0034fd5c();
    rt_002a4c98();
    rt_003593a8();
    rt_00355ca4();
    rt_002478d4();
    rt_00351a50();
    rt_003a25d4(0xe000000000000000);
    uint64_t d = rt_0009461c();
    rt_0035847c(d, d >> 0x40, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0024fd30 @ 0x0024fd30   (est. sk_swift_dump_state)
 * Ghidra: void FUN_0024fd30(undefined8 param_1, undefined8 param_2, undefined8 param_3,
 *          undefined8 param_4)
 * Swift runtime dump/diagnostic loop: runs a series of runtime barriers, then
 * iterates invoking the current state-machine dispatch (FUN_00350884) and the
 * method-table entry at [x16+0x20], handling a callback error path and a
 * termination path.
 * Confidence: low (state-machine dispatch; jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state(void *param_1, void *param_2, void *param_3, void *param_4)
{
    rt_00353cfc(); rt_00355e68(); rt_0035454c(); rt_003516cc();
    rt_00377824(); rt_00348d64(); rt_0007c1a4();
    rt_0034aee4(); rt_00350500(); rt_0034d464(); rt_0007c1a4();
    rt_0034b0d4(); rt_003499c8();
    rt_00348f50(); rt_0035113c(); rt_00351f1c(); rt_00377824();
    rt_00348ce8(); rt_0007c1a4();
    rt_0034d3c4();
    uint64_t v = rt_00358cd4();
    rt_00352680((unsigned long)param_4);
    rt_00359bec(); rt_003516e4();
    rt_0034b278(); rt_00350c38();
    uint64_t u = rt_00377bec();
    (void)u;
    for (;;) {
        uint64_t st = rt_00350884();
        if ((bool)rt_0008412c()) {
            rt_0034ed28();
            uint64_t r = rt_0034ed28();
            rt_00353220(r, 1);
            rt_000839d8();
            rt_00351348();
            rt_00353d14((unsigned long)param_4);
            return;
        }
        uint64_t fn = *(uint64_t *)(rt_00351f1c() + 0x20);
        rt_00350a04(st, st >> 0x40, 0);
        rt_00357050();
        uint64_t r3 = rt_00350a04(st, st >> 0x40, 0);
        if ((long)rt_00351f1c() != 0) {
            rt_000a6e14(0);
            rt_0034ed28();
            rt_00351348();
            rt_00353d14((unsigned long)param_4);
            return;
        }
        if ((r3 & 1) != 0) {
            rt_0034ed28();
            rt_003515d8(0);
            rt_00353220(fn, 0);
            rt_000839d8();
            rt_00351348();
            rt_00353d14((unsigned long)param_4);
            return;
        }
        rt_0034ed28();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_0024ffe8 @ 0x0024ffe8   (est. sk_swift_keypath_sink3)
 * Ghidra: void FUN_0024ffe8(void)
 * Thin forwarder to FUN_0024fbbc.
 * Confidence: high (trivial forwarder). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_keypath_sink3(void)
{
    sk_swift_keypath_sink2();
}

/*--------------------------------------------------------------------*/
/* FUN_0025000c @ 0x0025000c   (est. sk_swift_dump_state2)
 * Ghidra: void FUN_0025000c(void)
 * Swift runtime diagnostic: builds a value description through FUN_00100efc,
 * invokes the method-table entries at [x16+0x20] (twice) and unwinds.
 * Confidence: low (runtime diagnostic; jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state2(void *p1, void *p2, void *p3, void *p4, void *p5, void *p6)
{
    rt_00084220();
    uint64_t u = rt_0034aa3c();
    rt_00350328(); rt_003515b4();
    uint64_t v = rt_003722e4();
    rt_0034ab20(); rt_0007c1a4();
    rt_0034aee4();
    uint64_t d = rt_00100efc();
    rt_0019ea20(d, d >> 0x40, v);
    rt_0034b518();
    rt_0034b3e8();
    rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0025010c @ 0x0025010c   (est. sk_swift_string_append_slice)
 * Ghidra: void FUN_0025010c(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Swift String append: initializes the string context from the type table
 * (DAT_004e9d20) and forwards to the append helper FUN_001e7038.
 * Confidence: medium (Swift String append; identity inferred). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_slice(void *param_1, void *param_2, void *param_3)
{
    uint64_t u = rt_00376820((unsigned long)0x4e9d20);
    rt_001e7038((unsigned long)param_1, (unsigned long)param_2, (unsigned long)param_3, u, 0x6720e8);
}

/*--------------------------------------------------------------------*/
/* FUN_002501a8 @ 0x002501a8   (est. sk_swift_string_append_1)
 * Ghidra: void FUN_002501a8(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Swift String append variant: initializes the string from the current type,
 * forwards to FUN_001e664c.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_1(void *param_1, void *param_2, void *param_3)
{
    rt_00349ef4();
    uint64_t u = rt_0034b628();
    rt_00376820(u, (unsigned long)param_3);
    rt_003486fc(); rt_0034b128();
    rt_001e664c((unsigned long)param_1, (unsigned long)param_2, (unsigned long)param_3);
}

/*--------------------------------------------------------------------*/
/* FUN_002501f0 @ 0x002501f0   (est. sk_swift_string_append_2)
 * Ghidra: void FUN_002501f0(void)
 * Swift String append variant: initializes the string from the current type,
 * forwards to FUN_001e3a28.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_2(void)
{
    rt_00349944();
    uint64_t u = rt_0034b628();
    rt_00376820(u, 0);
    rt_003498a8();
    rt_001e3a28();
}

/*--------------------------------------------------------------------*/
/* FUN_00250234 @ 0x00250234   (est. sk_swift_string_append_3)
 * Ghidra: void FUN_00250234(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Swift String append variant: initializes the string from the current TCB
 * type, forwards to FUN_001e6be8.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_3(void *param_1, void *param_2, void *param_3)
{
    rt_000867ec();
    uint64_t u = rt_0034b628();
    rt_00376820(u, (unsigned long)param_3);
    rt_003486fc(); rt_0034b778();
    rt_001e6be8((unsigned long)param_1, (unsigned long)param_2, (unsigned long)param_3);
}

/*--------------------------------------------------------------------*/
/* FUN_00250274 @ 0x00250274   (est. sk_swift_keypath_dict_1)
 * Ghidra: undefined1 [16] FUN_00250274(long *param_1, undefined8 *param_2, long param_3)
 * Swift dictionary keypath descriptor: allocates a 0x40-byte builder, fills it
 * with the key/value type info from param_3 (+0x10/+0x18), allocates the value
 * slot, and registers the two element closures.
 * Confidence: medium (Swift KeyPath/Dictionary; identity inferred). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_keypath_dict_1(void *param_1, void *param_2, long param_3)
{
    long lVar3 = (long)rt_0036a908(0x40, 0xfb);
    *(long *)param_1 = lVar3;
    long lVar1 = *(long *)(param_3 + 0x10);
    long lVar2 = *(long *)(param_3 + 0x18);
    long lVar4 = (long)rt_003722e4(0, lVar1, lVar2, 0, 0);
    *(long *)(lVar3 + 0x20) = lVar4;
    long lVar6 = *(long *)(lVar4 + -8);
    *(long *)(lVar3 + 0x28) = lVar6;
    long lv = (long)rt_0036a908(*(unsigned long *)(lVar6 + 0x40), 0xfb);
    *(long *)(lVar3 + 0x30) = lv;
    uint64_t t = (uint64_t)sk_swift_keypath_dict_2((void *)(uintptr_t)lVar3, (void *)(uintptr_t)*(unsigned long *)param_2, (void *)0, (void *)(uintptr_t)lVar1, (void *)(uintptr_t)lVar2);
    *(long *)(lVar3 + 0x38) = (long)(t & 0xffffffffffff);
    (*(void (**)(void))(*(long *)(lVar1 + -8) + 0x10))();
    (*(void (**)(void))(*(long *)(lVar2 + -8) + 0x10))();
    return (void *)(uintptr_t)lv;
}

/*--------------------------------------------------------------------*/
/* FUN_002503c4 @ 0x002503c4   (est. sk_swift_keypath_teardown)
 * Ghidra: void FUN_002503c4(void)
 * KeyPath teardown: releases the two child slots via the runtime table and
 * unwinds.
 * Confidence: low (runtime teardown; jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_keypath_teardown(void)
{
    rt_00358c74();
    rt_0007c1c4(0);
    rt_0034a148(0, 0, 0);
    rt_00012568(0);
    rt_00012568();
}

/*--------------------------------------------------------------------*/
/* FUN_0025041c @ 0x0025041c   (est. sk_swift_keypath_dict_2)
 * Ghidra: undefined1 [16] FUN_0025041c(long *param_1, undefined8 param_2, undefined8 param_3,
 *          undefined8 param_4, undefined8 param_5)
 * Swift dictionary keypath descriptor (leaf): allocates the builder and value
 * slot, then forwards the key/value to FUN_0025000c.
 * Confidence: medium (Swift KeyPath/Dictionary). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_keypath_dict_2(void *param_1, void *param_2, void *param_3, void *param_4, void *param_5)
{
    long lVar1 = (long)rt_003722e4(0, (unsigned long)param_4, (unsigned long)param_5, 0, 0);
    *(long *)param_1 = lVar1;
    long lVar2 = *(long *)(lVar1 + -8);
    *(long *)((char *)param_1 + 8) = lVar2;
    long lv = (long)rt_0036a908(*(unsigned long *)(lVar2 + 0x40), 0x42bd);
    *(long *)((char *)param_1 + 0x10) = lv;
    sk_swift_dump_state2((void *)(uintptr_t)lv, (void *)(uintptr_t)(lv + *(int *)(lVar1 + 0x30)),
                         param_2, param_3, param_4, param_5);
    return (void *)(uintptr_t)lv;
}

/*--------------------------------------------------------------------*/
/* FUN_00250504 @ 0x00250504   (est. sk_swift_string_append_4)
 * Ghidra: void FUN_00250504(undefined8 param_1, undefined8 param_2)
 * Swift String append: init from DAT_004e9d20, forward to FUN_0019fa60.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_4(void *param_1, void *param_2)
{
    uint64_t u = rt_00376820((unsigned long)0x4e9d20, (unsigned long)param_2);
    rt_0019fa60((unsigned long)param_1, (unsigned long)param_2, u, 0x6720e8);
}

/*--------------------------------------------------------------------*/
/* FUN_00250574 @ 0x00250574   (est. sk_swift_string_append_5)
 * Ghidra: void FUN_00250574(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Swift String append: init from DAT_004e9d20, forward to FUN_001e7664.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_5(void *param_1, void *param_2, void *param_3)
{
    uint64_t u = rt_00376820((unsigned long)0x4e9d20);
    rt_001e7664((unsigned long)param_1, (unsigned long)param_2, (unsigned long)param_3, u, 0x6720e8);
}

/*--------------------------------------------------------------------*/
/* FUN_00250610 @ 0x00250610   (est. sk_swift_string_append_6)
 * Ghidra: void FUN_00250610(undefined8 param_1)
 * Swift String append: init from DAT_004e9d58, forward to FUN_001a0194.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_6(void *param_1)
{
    uint64_t u = rt_00376820((unsigned long)0x4e9d58, (unsigned long)param_1);
    rt_001a0194((unsigned long)param_1, u);
}

/*--------------------------------------------------------------------*/
/* FUN_00250658 @ 0x00250658   (est. sk_swift_string_append_7)
 * Ghidra: void FUN_00250658(undefined8 param_1)
 * Swift String append: init from DAT_004e9d58, forward to FUN_001e088c.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_7(void *param_1)
{
    uint64_t u = rt_00376820((unsigned long)0x4e9d58, (unsigned long)param_1);
    rt_001e088c((unsigned long)param_1, u);
}

/*--------------------------------------------------------------------*/
/* FUN_002506b4 @ 0x002506b4   (est. sk_swift_string_append_8)
 * Ghidra: void FUN_002506b4(void)
 * Swift String append: init from the bridge pair, forward to FUN_001f5d68.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_8(void)
{
    rt_00350b54(); rt_00352ddc();
    uint64_t u1 = rt_0031cf30();
    uint64_t u2 = rt_00354798();
    rt_00376820(u2, u1);
    rt_00351b78();
    rt_001f5d68();
}

/*--------------------------------------------------------------------*/
/* FUN_00250710 @ 0x00250710   (est. sk_swift_dump_state3)
 * Ghidra: void FUN_00250710(void)
 * Swift runtime diagnostic variant: runs the barrier sequence, builds the value
 * via FUN_003506b0, forwards through the runtime dispatch, unwinds.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state3(void)
{
    rt_00084220();
    rt_00351cc4(); rt_003564d0(0);
    rt_0034c60c(); rt_00377824(); rt_00348d64(); rt_0007c1a4();
    rt_0034b05c(); rt_003506b0(); rt_003504ac();
    rt_00354cfc(); rt_00200b38(); rt_0034ded4();
    rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002507cc @ 0x002507cc   (est. sk_swift_dispatch_1)
 * Ghidra: void FUN_002507cc(void)
 * Swift runtime dispatch: sets up and jumps through the recovered jump table
 * (FUN_000a68c4).
 * Confidence: low (indirect jump; jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dispatch_1(void)
{
    rt_00351cc4(); rt_003564d0(0);
    uint64_t t = rt_000a68c4();
    rt_003504ac();
    (*(void (**)(void))t)();
}

/*--------------------------------------------------------------------*/
/* FUN_00250900 @ 0x00250900   (est. thunk sk_swift_string_append_9)
 * Ghidra: void thunk_FUN_00250904(...)
 * Thunk to FUN_00250904.
 * Confidence: high (thunk). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_9(void *param_1, void *param_2, void *param_3)
{
    sk_swift_string_append_10(param_1, param_2, param_3);
}

/*--------------------------------------------------------------------*/
/* FUN_00250904 @ 0x00250904   (est. sk_swift_string_append_10)
 * Ghidra: void FUN_00250904(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Swift String append: spins up the string with irq-save, reads the value type
 * from [x21+0x10], takes the object lock, invokes the method-table entry at
 * [x16+0x10], and restores.
 * Confidence: medium (Swift String append). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_append_10(void *param_1, void *param_2, void *param_3)
{
    rt_00357ca0(); rt_00349ef4(); rt_00352ecc((unsigned long)param_3);
    uint64_t u = *(unsigned long *)(rt_0034a958() + 0x10);
    rt_0034b358();
    rt_0034eb54();
    uint64_t t = rt_00348b94();
    rt_00377824(t, t >> 0x40, u);
    rt_00349530();
    (*(void (**)(void))(rt_00351f1c() + 0x10))();
    rt_00357c44(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00250998 @ 0x00250998   (est. sk_swift_dispatch_2)
 * Ghidra: void FUN_00250998(void)
 * Swift runtime dispatch: sets up and jumps through the recovered jump table
 * (FUN_003192a8) with the value from [x21+0x10].
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dispatch_2(void)
{
    rt_0034f664();
    uint64_t t = rt_003192a8();
    (*(void (**)(uint64_t))t)(*(unsigned long *)(rt_0034a958() + 0x10));
}

/*--------------------------------------------------------------------*/
/* FUN_002509d8 @ 0x002509d8   (est. sk_swift_unicode_emit)
 * Ghidra: void FUN_002509d8(undefined8 param_1, undefined8 param_2, undefined8 param_3,
 *          undefined8 param_4)
 * Emits a Unicode scalar: caps the value at 0x3fff (delegating larger values to
 * FUN_002532a8) then forwards the byte to FUN_0021acec.
 * Confidence: medium (Unicode emit; identity inferred). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_unicode_emit(void *param_1, void *param_2, void *param_3, void *param_4)
{
    uint64_t u = sk_swift_scalar_pos(0, 0);
    uint64_t v = u;
    if (u > 0x3fff) {
        sk_swift_utf8_decode_scalar((void *)(uintptr_t)param_1, (unsigned long)param_2, (unsigned long)param_3, (void (*)(void *, unsigned int *))(uintptr_t)param_4);
        v = 0xf;
    }
    rt_0021acec(v, 0, (u <= 0x3fff), u, 0, 1, (unsigned long)param_1, (unsigned long)param_2, (unsigned long)param_3, (unsigned long)param_4);
}

/*--------------------------------------------------------------------*/
/* FUN_00250a7c @ 0x00250a7c   (est. sk_swift_dispatch_3)
 * Ghidra: void FUN_00250a7c(void)
 * Swift runtime dispatch: sets up and jumps through the recovered jump table
 * (FUN_00027788) with the value from [x21+0x10].
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dispatch_3(void)
{
    rt_0034f664();
    uint64_t t = rt_00027788();
    (*(void (**)(uint64_t))t)(*(unsigned long *)(rt_0034a958() + 0x10));
}

/*--------------------------------------------------------------------*/
/* FUN_00250c58 @ 0x00250c58   (est. sk_swift_unicode_len_obj)
 * Ghidra: undefined * FUN_00250c58(long *param_1, undefined8 param_2, undefined8 param_3, ulong param_4)
 * Allocates a 0x28-byte Unicode helper object, initializes it via FUN_00250cd8
 * and stores the result at +0x20.
 * Confidence: medium (Swift Unicode object alloc). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_unicode_len_obj(void *param_1, void *param_2, void *param_3, unsigned long param_4)
{
    long lVar1 = (long)rt_0036a908(0x28, 0xbcc5);
    *(long *)param_1 = lVar1;
    uint64_t u = (uint64_t)sk_swift_unicode_len_init((void *)(uintptr_t)lVar1, (void *)(uintptr_t)param_2, (long)param_3,
                             (void *)(uintptr_t)*(unsigned long *)((param_4 & ~1ull) - 8));
    *(unsigned long *)(lVar1 + 0x20) = u;
    return (void *)(uintptr_t)lVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_00250cd8 @ 0x00250cd8   (est. sk_swift_unicode_len_init)
 * Ghidra: undefined1 [16] FUN_00250cd8(long *param_1, undefined8 param_2, long param_3,
 *          undefined8 param_4)
 * Initializes a Unicode helper object: reads the value type, takes the object
 * lock, allocates the value slot, and forwards to FUN_00250904.
 * Confidence: medium (Swift Unicode init). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_unicode_len_init(void *param_1, void *param_2, long param_3, void *param_4)
{
    uint64_t u = rt_00027754((unsigned long)param_4);
    long lVar2 = (long)rt_00377824(0, u, *(unsigned long *)(param_3 + 0x10), 0, 0);
    *(long *)param_1 = lVar2;
    long lv = *(long *)(lVar2 + -8);
    *(long *)((char *)param_1 + 8) = lv;
    long l2 = (long)rt_0036a908(*(unsigned long *)(lv + 0x40), 0x932d);
    *(long *)((char *)param_1 + 0x10) = l2;
    sk_swift_string_append_10((void *)(uintptr_t)l2, param_2, (void *)(uintptr_t)param_3);
    return (void *)(uintptr_t)l2;
}

/*--------------------------------------------------------------------*/
/* FUN_00250e30 @ 0x00250e30   (est. sk_swift_append_11)
 * Ghidra: void FUN_00250e30(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Swift append variant: reads the value type, takes the object lock, dispatches
 * through the method table at [x19], unwinds.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_append_11(void *param_1, void *param_2, unsigned long param_3)
{
    rt_00084220();
    uint64_t a = rt_00350858();
    unsigned long uVar2 = *(unsigned long *)((param_3 & ~1ull) - 8);
    uint64_t u = rt_00348d94(a, a >> 0x40, *(unsigned long *)((a & 0xffffffffffff) + 0x10));
    rt_00377824(u, uVar2);
    rt_00348d4c(); rt_0007c1a4();
    rt_0034a2c0(); rt_00350b84();
    uint64_t d = rt_003507d4();
    (*(void (**)(uint64_t, uint64_t, unsigned long))rt_00350858())(d, d >> 0x40, uVar2);
    rt_0034c9f8();
    rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00250f04 @ 0x00250f04   (est. sk_swift_append_12)
 * Ghidra: void FUN_00250f04(undefined8 param_1, undefined8 param_2, ulong param_3)
 * Swift append variant: reads the value type, takes the object lock, dispatches
 * through the method table at [x19], unwinds.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_append_12(void *param_1, void *param_2, unsigned long param_3)
{
    rt_00084220();
    rt_00350858();
    unsigned long uVar1 = *(unsigned long *)((param_3 & ~1ull) - 8);
    uint64_t a = rt_00350bd8(uVar1);
    uint64_t u = rt_00348d94(a, a >> 0x40, *(unsigned long *)(rt_0034a958() + 0x10));
    rt_00377824(u, 0);
    rt_00348d4c(); rt_0007c1a4();
    rt_0034a2c0(); rt_00350b84();
    uint64_t d = rt_003507d4();
    (*(void (**)(uint64_t, uint64_t, unsigned long))rt_00350858())(d, d >> 0x40, uVar1);
    rt_0034c9f8();
    rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00251058 @ 0x00251058   (est. sk_swift_dump_state4)
 * Ghidra: void FUN_00251058(void)
 * Swift runtime diagnostic variant: barrier sequence, dispatch via FUN_000a68c4,
 * unwinds.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state4(void)
{
    rt_00084220();
    rt_0034c084(); rt_003512f4(); rt_00377824(); rt_00348d64(); rt_0007c1a4();
    rt_0034b05c(); rt_000a68c4(); rt_0034e72c();
    rt_00354d94(); rt_00200b38(); rt_0034ded4();
    rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00251110 @ 0x00251110   (est. sk_swift_dispatch_4)
 * Ghidra: void FUN_00251110(void)
 * Swift runtime dispatch: sets up and jumps through the recovered jump table
 * (FUN_000a68c4).
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dispatch_4(void)
{
    rt_0034bd6c();
    uint64_t t = rt_000a68c4();
    rt_0034ffb8();
    (*(void (**)(void))t)();
}

/*--------------------------------------------------------------------*/
/* FUN_002511a8 @ 0x002511a8   (est. sk_swift_dispatch_5)
 * Ghidra: void FUN_002511a8(long param_1, code *param_2, code *UNRECOVERED_JUMPTABLE)
 * Calls param_2 with [param_1+0x18], then jumps through the jump table.
 * Confidence: low (indirect jump not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dispatch_5(long param_1, void (*param_2)(unsigned long), void *jmp)
{
    param_2(*(unsigned long *)(param_1 + 0x18));
    rt_00355988();
    (*(void (**)(void))jmp)();
}

/*--------------------------------------------------------------------*/
/* FUN_002512d4 @ 0x002512d4   (est. sk_swift_release_obj_1)
 * Ghidra: void FUN_002512d4(void)
 * Swift object release helper: takes the lock, releases via thunk_FUN_0036b270,
 * forwards the built value to FUN_001b07b8, releases the temp.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_release_obj_1(void)
{
    rt_0034bb84();
    rt_0036b270(0);
    uint64_t a = rt_0034c2a4();
    rt_001b07b8(a, a >> 0x40, 0);
    rt_003a25d4(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0025133c @ 0x0025133c   (est. sk_swift_release_obj_2)
 * Ghidra: void FUN_0025133c(void)
 * Swift object release helper variant: forwards to FUN_001dfc88.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_release_obj_2(void)
{
    rt_0034bb84();
    rt_0036b270(0);
    uint64_t a = rt_0034c2a4();
    rt_001dfc88(a, a >> 0x40, 0);
    rt_003a25d4(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002513a8 @ 0x002513a8   (est. sk_swift_fatal_code2)
 * Ghidra: void FUN_002513a8(void)
 * Fatal error shim: reports code 0x50 then enters noreturn fatal.
 * Confidence: high (trivial noreturn). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_fatal_code2(void)
{
    rt_00350d94(0x50);
    rt_00353448();
    rt_001afa84();
}

/*--------------------------------------------------------------------*/
/* FUN_002513f4 @ 0x002513f4   (est. sk_swift_fatal_msg)
 * Ghidra: void FUN_002513f4(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Fatal error shim: reports the message then enters noreturn fatal.
 * Confidence: high (trivial noreturn). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_fatal_msg(void *param_1, void *param_2, void *param_3)
{
    rt_0006f768((unsigned long)param_3);
    rt_001afa84();
}

/*--------------------------------------------------------------------*/
/* FUN_00251478 @ 0x00251478   (est. sk_swift_apply_fn_1)
 * Ghidra: void FUN_00251478(undefined8 param_1, code *param_2)
 * Indirect-call forwarder: invokes the supplied function pointer.
 * Confidence: high (trivial forwarder). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_apply_fn_1(void *param_1, void (*fn)(void)) { fn(); }

/* FUN_002514a0 @ 0x002514a0   (est. sk_swift_apply_fn_2)
 * Ghidra: void FUN_002514a0(undefined8 param_1, code *param_2)
 * Indirect-call forwarder: invokes the supplied function pointer.
 * Confidence: high (trivial forwarder). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_apply_fn_2(void *param_1, void (*fn)(void)) { fn(); }

/* FUN_002514c8 @ 0x002514c8   (est. sk_swift_apply_fn_3)
 * Ghidra: void FUN_002514c8(undefined8 param_1, code *param_2)
 * Indirect-call forwarder: invokes the supplied function pointer.
 * Confidence: high (trivial forwarder). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_apply_fn_3(void *param_1, void (*fn)(void)) { fn(); }

/*--------------------------------------------------------------------*/
/* FUN_002514f0 @ 0x002514f0   (est. sk_swift_dispatch_6)
 * Ghidra: void FUN_002514f0(void)
 * Swift runtime dispatch: calls the global method table entry, then a table
 * entry; if a context is non-null invokes the method at [x16+0x20].
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dispatch_6(void)
{
    rt_0034b7e4();
    rt_0007c1a4();
    rt_003501b8();
    rt_0034a148(0, 0, 0);
    if (rt_0034a958() != 0) {
        rt_003508d8(*(unsigned long *)(rt_00351f1c() + 0x20), 0);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00251604 @ 0x00251604   (est. sk_swift_fatal_break)
 * Ghidra: void FUN_00251604(void)
 * Fatal breakpoint: reports then SoftwareBreakpoint at 0x251620.
 * Confidence: high (noreturn breakpoint). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_fatal_break(void)
{
    rt_0036a940();
    /* SoftwareBreakpoint(1, 0x251620): does not return */
}

/*--------------------------------------------------------------------*/
/* FUN_00251638 @ 0x00251638   (est. sk_swift_dump_state5)
 * Ghidra: void FUN_00251638(void)
 * Swift runtime dump variant: builds a value, allocates a debug object, and if
 * a context is null appends to the current buffer else releases it.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state5(void)
{
    rt_0035a7c0(); rt_003494e8();
    rt_00348f38(); rt_0034df04();
    long lVar1 = (long)rt_0036a940();
    if (rt_0034a958() == 0) {
        rt_0035a140();
        rt_003508d8(lVar1 + *(long *)(rt_00351f1c() + 0x48));
    } else {
        rt_0036b118((uint64_t)lVar1);
    }
    uint64_t u = rt_00359f3c((uint64_t)lVar1);
    rt_0035a7d4(u, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00251758 @ 0x00251758   (est. sk_swift_dump_state6)
 * Ghidra: void FUN_00251758(void)
 * Swift runtime dump: appends the value from the method table.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state6(void)
{
    rt_000027e8();
    rt_00359360(*(unsigned long *)(rt_00351f1c() + 0x48));
}

/*--------------------------------------------------------------------*/
/* FUN_0025177c @ 0x0025177c   (est. sk_swift_collection_count)
 * Ghidra: long FUN_0025177c(void)
 * Computes a collection element count: reads the start, the byte-width from the
 * value descriptor, and divides (end-start) by the element size, trapping on
 * division overflow.
 * Confidence: medium (Swift collection count; identity inferred). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
long sk_swift_collection_count(void)
{
    long lVar1 = (long)rt_000126e8();
    sk_swift_dump_state7();
    rt_00351d9c();
    long lVar2 = (long)rt_003509c8(*(unsigned long *)(rt_00351f1c() + 0x40));
    long lVar3 = *(long *)(rt_00351f1c() + 0x48);
    if (lVar3 == 0) {
        rt_00348074(1);
    } else {
        lVar2 = (long)rt_0034a958() + lVar1 - lVar2;
        if (lVar2 != -0x8000000000000000LL || lVar3 != -1) {
            long r = 0;
            if (lVar3 != 0) r = lVar2 / lVar3;
            return r;
        }
        rt_0034834c(1);
    }
    rt_00351be0();
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_00251820 @ 0x00251820   (est. sk_swift_dump_state7)
 * Ghidra: void FUN_00251820(void)
 * Swift runtime dump: appends a value (byte-width masked) to the current
 * buffer.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state7(void)
{
    uint64_t u = rt_0007c0c4();
    rt_003509c8(*(unsigned long *)(rt_00351f1c() + 0x40), u);
    unsigned char b = *(unsigned char *)(rt_00351f1c() + 0x50);
    rt_00359360((unsigned long)b + 0x10 & ((unsigned long)b ^ 0xffffffffffffffff));
}

/*--------------------------------------------------------------------*/
/* FUN_00251880 @ 0x00251880   (est. sk_swift_dump_state8)
 * Ghidra: void FUN_00251880(void)
 * Swift runtime dump: appends a value at an offset into the buffer.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state8(void)
{
    rt_0034bb84();
    long lVar1 = *(long *)(*(unsigned long *)rt_0034a958() + 0x48);
    sk_swift_dump_state7();
    rt_003522d4((unsigned long)rt_0034a958() + (unsigned long)lVar1);
    rt_0034a148(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_002518dc @ 0x002518dc   (est. sk_swift_dump_state9)
 * Ghidra: void FUN_002518dc(void)
 * Swift runtime dump: appends the current value to the buffer.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state9(void)
{
    rt_0034bb84();
    sk_swift_dump_state7();
    rt_003522d4();
    rt_0034a148(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00251920 @ 0x00251920   (est. sk_swift_dump_state10)
 * Ghidra: void FUN_00251920(void)
 * Swift runtime dump: appends a value at an offset with a computed second arg.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state10(void)
{
    rt_0034bb84();
    rt_000027e8();
    long lVar2 = *(long *)(rt_00351f1c() + 0x48);
    uint64_t u = rt_0007c0c4();
    rt_003522d4((unsigned long)rt_0034a958() + (unsigned long)lVar2, u);
    rt_0034a148(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0025197c @ 0x0025197c   (est. sk_swift_concat_release)
 * Ghidra: undefined8 FUN_0025197c(void)
 * Builds a string via FUN_00251a58, then conditionally releases it and returns
 * the released value.
 * Confidence: medium (Swift string concat; identity inferred). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
uint64_t sk_swift_concat_release(void)
{
    rt_0034d2b4(); rt_00354828();
    sk_swift_alloc_string();
    uint64_t u = 0;
    rt_0036b270();
    rt_0034a210(); rt_00002534(); rt_00359024();
    rt_00352bec(rt_0031cf48(), 0);
    rt_00359fb4(); rt_001b6c4c();
    rt_0036b118(u);
    if (rt_0034a958() != 0) u = rt_0036b118(u);
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_00251a58 @ 0x00251a58   (est. sk_swift_alloc_string)
 * Ghidra: void FUN_00251a58(void)
 * Allocates a Swift string with irq-save, invokes FUN_00251d14, and on success
 * unwinds with the lock restore; else panics.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_alloc_string(void)
{
    rt_00357ca0();
    uint64_t u = rt_00349fcc();
    sk_swift_string_validate();
    if ((long)rt_0034a958() >= 0) {
        rt_0008412c();
        rt_00357c44(0);
        rt_001b6bd8();
        return;
    }
    rt_00348b7c(0x157);
    rt_0006f768();
    rt_00352e0c();
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_00251acc @ 0x00251acc   (est. sk_swift_apply_2)
 * Ghidra: void FUN_00251acc(undefined8 param_1, code *param_2, undefined8 param_3,
 *          undefined8 *param_4, long param_5, undefined8 param_6, long *param_7)
 * Applies a closure over a value: allocates a temp, invokes param_2, and if the
 * context is non-null calls the method-table entry at [lVar3+0x20] else stores
 * the context into *param_7.
 * Confidence: medium (Swift closure apply). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_apply_2(void *param_1, void (*param_2)(void *), void *param_3, void *param_4,
                      long param_5, void *param_6, long *param_7)
{
    long lVar3 = *(long *)(param_5 + -8);
    uint64_t uVar4 = *(uint64_t *)param_4;
    rt_0007c1a4();
    uint64_t u = rt_0036b270(uVar4);
    param_2((void *)u);
    rt_0036b118(uVar4);
    if (rt_0034a958() == 0) {
        (*(void (**)(void *, void *, long))(lVar3 + 0x20))(param_1, (void *)u, param_5);
    } else {
        *param_7 = rt_0034a958();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00251be4 @ 0x00251be4   (est. sk_swift_alloc_concat)
 * Ghidra: undefined8 FUN_00251be4(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Allocates a concat buffer, runs the two dump steps, releases the input.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
uint64_t sk_swift_alloc_concat(void *param_1, void *param_2, void *param_3)
{
    uint64_t u = rt_0036b270();
    sk_swift_dump_state11();
    sk_swift_collection_count2();
    rt_0036b118((uint64_t)param_1);
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_00251c40 @ 0x00251c40   (est. sk_swift_dump_state11)
 * Ghidra: void FUN_00251c40(void)
 * Swift runtime dump: runs the barrier, reads the value, invokes FUN_00251d14.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state11(void)
{
    rt_00353ed8();
    rt_0007c198();
    sk_swift_string_validate();
}

/*--------------------------------------------------------------------*/
/* FUN_00251c80 @ 0x00251c80   (est. sk_swift_collection_count2)
 * Ghidra: long FUN_00251c80(void)
 * Computes a collection element count (variant): (end - start) / elem_size.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
long sk_swift_collection_count2(void)
{
    rt_00350b0c();
    long lVar2 = (long)rt_000126e8();
    rt_000b43d0();
    long lVar3 = (long)sk_swift_string_len();
    long lVar4 = *(long *)(*(long *)(rt_0034a958() + -8) + 0x48);
    if (lVar4 == 0) {
        rt_00348074(1);
    } else {
        if (lVar2 - lVar3 != -0x8000000000000000LL || lVar4 != -1) {
            long r = 0;
            if (lVar4 != 0) r = (lVar2 - lVar3) / lVar4;
            return r;
        }
        rt_0034834c(1);
    }
    rt_00351be0();
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_00251d14 @ 0x00251d14   (est. sk_swift_string_validate)
 * Ghidra: void FUN_00251d14(void)
 * Validates a Swift string buffer: reads the header, checks the byte width and
 * the current cursor against the capacity, and traps on overflow/mismatch.
 * Confidence: medium (Swift string validation; SoftwareBreakpoint at 0x251df8). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_validate(void)
{
    uint64_t fl = rt_003531d8();
    rt_003a2898();
    if ((long)rt_0034a958() >= 0) {
        if ((long)rt_0034a958() != 0x10) {
            if ((fl >> 0x40 & 1) != 0) {
                rt_0034ce98(); rt_0031cf70(); rt_0035a7e8();
                long lVar2 = (long)rt_00362c34();
                if (lVar2 == 0) { rt_003488bc(1); rt_0034b1dc(); rt_001afe4c(); }
            }
            rt_003a2898(fl);
            if ((long)rt_0034a958() < 0) { rt_00347fb4(); rt_003523f0(); rt_001afe4c(); }
            rt_0034e3ac();
            unsigned long uVar3 = (unsigned long)(*(unsigned char *)(rt_00351f1c() + 0x50) + 0x10 &
                                                  (*(unsigned char *)(rt_00351f1c() + 0x50) ^ 0xff));
            if ((long)rt_0034a958() != (long)(uVar3 + *(long *)(rt_0034a958() + 0x40))) {
                rt_003488bc(1); rt_0034b1dc(); rt_001afe4c();
            }
        }
        return;
    }
    rt_00347fb4();
    rt_003523f0();
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_00251df8 @ 0x00251df8   (est. sk_swift_string_len)
 * Ghidra: ulong FUN_00251df8(void)
 * Returns the Swift string length (byte width + 0x10, aligned), trapping on
 * carry.
 * Confidence: high (string length helper; SoftwareBreakpoint at 0x251e78). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned long sk_swift_string_len(void)
{
    rt_00352018();
    unsigned long uVar4 = (unsigned long)(*(unsigned char *)(rt_00351f1c() + 0x50) + 0x10 &
                                          (*(unsigned char *)(rt_00351f1c() + 0x50) ^ 0xff));
    unsigned long uVar1 = uVar4 + *(long *)(rt_0034a958() + 0x40);
    unsigned char bVar2 = *(unsigned char *)(*(long *)(rt_0034a958() + -8) + 0x50);
    unsigned long uVar4b = (unsigned long)bVar2 + 1;
    if (uVar1 + uVar4b < uVar1) { /* carry -> breakpoint at 0x251e7c */ }
    return (uVar1 + uVar4b) - 1 & (unsigned long)(int)~(unsigned int)bVar2;
}

/*--------------------------------------------------------------------*/
/* FUN_00251e7c @ 0x00251e7c   (est. sk_swift_string_min_align)
 * Ghidra: byte FUN_00251e7c(void)
 * Returns the max of the two byte widths, but at least 7.
 * Confidence: high (simple helper). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned char sk_swift_string_min_align(void)
{
    rt_00351f10();
    unsigned char bVar1 = *(unsigned char *)(*(long *)(rt_0034a958() + -8) + 0x50);
    if (bVar1 <= *(unsigned char *)(rt_00351f1c() + 0x50)) bVar1 = *(unsigned char *)(rt_00351f1c() + 0x50);
    if (bVar1 < 8) bVar1 = 7;
    return bVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_00251ecc @ 0x00251ecc   (est. sk_swift_string_offset)
 * Ghidra: long FUN_00251ecc(long param_1, long param_2)
 * Returns param_1 plus the aligned (width+0x10) offset for the value at
 * [param_2-8].
 * Confidence: high (simple helper). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
long sk_swift_string_offset(long param_1, long param_2)
{
    unsigned int uVar1 = (unsigned int)*(unsigned char *)(*(long *)(param_2 + -8) + 0x50);
    return param_1 + (unsigned long)(uVar1 + 0x10 & (uVar1 ^ 0xffffffff));
}

/*--------------------------------------------------------------------*/
/* FUN_00251f6c @ 0x00251f6c   (est. sk_swift_apply_3)
 * Ghidra: void FUN_00251f6c(undefined8 param_1, undefined8 param_2, code *param_3)
 * Applies a closure over a value read from the type descriptor.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_apply_3(void *param_1, void *param_2, void (*param_3)(void *, void *))
{
    long lVar2 = *(long *)(rt_0034a958() + -8);
    uint64_t u = rt_0007c1a4();
    param_3((void *)u, (void *)(uintptr_t)u);
    if (rt_0034a958() != 0) {
        (*(void (**)(void *, void *, long))(lVar2 + 0x20))(param_1, (void *)u, rt_0034a958());
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00252024 @ 0x00252024   (est. sk_swift_apply_4)
 * Ghidra: void FUN_00252024(undefined8 param_1, code *param_2, undefined8 param_3,
 *          long param_4, long param_5, undefined8 param_6, long param_7,
 *          undefined8 param_8, undefined8 param_9, undefined8 param_10)
 * Applies a closure over a string slice: computes the byte offsets and invokes
 * param_2, then the method-table entry at [lVar3+0x20] if context non-null.
 * Confidence: medium (Swift string slice apply). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_apply_4(void *param_1, void (*param_2)(void *, long, long, void *), void *param_3,
                      long param_4, long param_5, void *param_6, long param_7,
                      void *param_8, void *param_9, void *param_10)
{
    long lVar3 = *(long *)(param_7 + -8);
    rt_0007c1a4();
    unsigned int uVar2 = (unsigned int)*(unsigned char *)(*(long *)(param_5 + -8) + 0x50);
    long lVar1 = (long)sk_swift_string_len();
    param_2(param_1, param_4 + (long)(uVar2 + 0x10 & (uVar2 ^ 0xffffffff)), param_4 + lVar1, (void *)0);
    if (rt_0034a958() != 0) {
        (*(void (**)(void *, void *, long))(lVar3 + 0x20))(param_10, (void *)0, param_7);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_00252144 @ 0x00252144   (est. sk_swift_string_offset2)
 * Ghidra: long FUN_00252144(long param_1)
 * Returns param_1 plus the Swift string length.
 * Confidence: high. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
long sk_swift_string_offset2(long param_1)
{
    rt_00106e3c();
    long lVar1 = (long)sk_swift_string_len();
    return param_1 + lVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_00252170 @ 0x00252170   (est. sk_swift_dump_state12)
 * Ghidra: void FUN_00252170(void)
 * Forwarder to FUN_00252238.
 * Confidence: high (trivial forwarder). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state12(void) { sk_swift_dump_state17(0,0,0,0,0,0,0); }

/* FUN_00252174 @ 0x00252174   (est. sk_swift_dump_state13)
 * Ghidra: void FUN_00252174(void)
 * Forwarder to FUN_00252238.
 * Confidence: high (trivial forwarder). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state13(void) { sk_swift_dump_state17(0,0,0,0,0,0,0); }

/* FUN_0025220c @ 0x0025220c   (est. sk_swift_dump_state14)
 * Ghidra: void FUN_0025220c(void)
 * Forwarder to FUN_00252238.
 * Confidence: high (trivial forwarder). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state14(void) { sk_swift_dump_state17(0,0,0,0,0,0,0); }

/* FUN_00252210 @ 0x00252210   (est. sk_swift_dump_state15)
 * Ghidra: void FUN_00252210(void)
 * Forwarder to FUN_00252238.
 * Confidence: high (trivial forwarder). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state15(void) { sk_swift_dump_state17(0,0,0,0,0,0,0); }

/*--------------------------------------------------------------------*/
/* FUN_0025219c @ 0x0025219c   (est. sk_swift_dump_state16)
 * Ghidra: void FUN_0025219c(undefined8 param_1, undefined8 param_2, long param_3)
 * Swift runtime dump: appends a value at an offset into the buffer.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state16(void *param_1, void *param_2, long param_3)
{
    rt_0034bb84();
    rt_0035a01c();
    unsigned char bVar1 = *(unsigned char *)(rt_00351f1c() + 0x50);
    rt_00355b68();
    long lVar2 = (long)sk_swift_string_len();
    rt_003522d4(param_3 + (long)(bVar1 + 0x10 & (bVar1 ^ 0xff)), param_3 + lVar2);
    rt_0034a148(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00252238 @ 0x00252238   (est. sk_swift_dump_state17)
 * Ghidra: void FUN_00252238(undefined8 param_1, ... undefined8 param_7)
 * Swift runtime dump: repacks its 7 args into two local pairs and forwards to
 * FUN_0025219c.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state17(void *param_1, void *param_2, void *param_3, void *param_4,
                           void *param_5, void *param_6, void *param_7)
{
    sk_swift_dump_state16(param_7, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_0025226c @ 0x0025226c   (est. sk_swift_string_align)
 * Ghidra: uint FUN_0025226c(void)
 * Returns the aligned (width+0x10) offset for the current value.
 * Confidence: high. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned int sk_swift_string_align(void)
{
    rt_00351f10();
    unsigned char b = *(unsigned char *)(rt_00351f1c() + 0x50);
    return (unsigned int)(b + 0x10) & (b ^ 0xff);
}

/*--------------------------------------------------------------------*/
/* FUN_002522a4 @ 0x002522a4   (est. sk_swift_release_slot_1)
 * Ghidra: void FUN_002522a4(undefined8 *param_1)
 * Releases the object at *param_1 via the runtime release helper.
 * Confidence: high. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_release_slot_1(void *param_1) { rt_003a265c(*(uint64_t *)param_1); }

/* FUN_002522a8 @ 0x002522a8   (est. sk_swift_release_slot_2)
 * Ghidra: void FUN_002522a8(undefined8 *param_1)
 * Releases the object at *param_1 via the runtime release helper.
 * Confidence: high. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_release_slot_2(void *param_1) { rt_003a265c(*(uint64_t *)param_1); }

/*--------------------------------------------------------------------*/
/* FUN_002522c4 @ 0x002522c4   (est. sk_swift_dump_state18)
 * Ghidra: void FUN_002522c4(void)
 * Swift runtime dump: builds a value, invokes the method-table entry at
 * [x16+0x20], and stores a result pair into the buffer at an offset.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state18(void)
{
    rt_0034aa3c();
    rt_00358e88();
    rt_003509c8(0);
    (*(void (**)(void))(rt_00351f1c() + 0x20))();
    rt_0034b788(0);
    long lVar2 = (long)rt_00319338();
    /* store result pair at [x24 + *(int*)(lVar2+0x2c)] */
    rt_0034a148(0, 0, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00252334 @ 0x00252334   (est. sk_swift_dump_state19)
 * Ghidra: void FUN_00252334(long param_1)
 * Swift runtime dump: appends the value at [param_1+0x2c] and prints.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state19(long param_1)
{
    rt_003591d0((long)*(int *)(param_1 + 0x2c));
    rt_0009461c();
}

/*--------------------------------------------------------------------*/
/* FUN_0025235c @ 0x0025235c   (est. sk_swift_dump_state20)
 * Ghidra: void FUN_0025235c(void)
 * Swift runtime dump variant: builds a value, stores a result pair, unwinds.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state20(void)
{
    rt_00084220();
    rt_0034aa3c(); rt_003562c8();
    uint64_t u = rt_00349830();
    rt_00377824(u, 0);
    rt_00349530();
    (*(void (**)(void))(rt_00351f1c() + 0x20))();
    rt_0034b788(0);
    long lVar3 = (long)rt_0031cfdc();
    /* store result pair at [x25 + *(int*)(lVar3+0x2c)] */
    rt_00084234(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002523d8 @ 0x002523d8   (est. sk_swift_utf8_iterate)
 * Ghidra: ulong FUN_002523d8(void)
 * UTF-8 scalar iterator: reads the next byte at the cursor (x20[2], guarded by
 * x20[3] as end), decodes a 1/2/3/4-byte UTF-8 scalar via LZCOUNT, advances the
 * cursor (x20[2]), and invokes the callback at x20[4] with the scalar. Returns
 * the callback's low word; 0x100000000 when the iterator is exhausted.
 * Confidence: high (UTF-8 scalar decode; s_Swift_UnicodeHelpers string). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned long sk_swift_utf8_iterate(void)
{
    /* unaff_x20 is the iterator context: [0]=base, [1]=flags, [2]=cursor,
     * [3]=end, [4]=callback. */
    unsigned long *iter = (unsigned long *)rt_0034a958();  /* context (unaff_x20) */
    if ((long)iter[3] <= (long)iter[2]) return 0x100000000; /* exhausted */
    unsigned long fl = iter[1];
    if ((fl >> 0x3c & 1) != 0) {
        /* inline UTF-8 buffer (s_Swift_UnicodeHelpers_swift_005ce730) */
        rt_001afa84();  /* fatal, noreturn */
    }
    unsigned long base;
    unsigned int sc;
    long adv;
    if ((fl >> 0x3d & 1) == 0) {
        if ((iter[0] >> 0x3c & 1) == 0) base = rt_002a9ba8();
        else base = (fl & 0xfffffffffffffffULL) + 0x20;
        unsigned char *pb = (unsigned char *)(base + iter[2]);
        sc = (unsigned int)*pb;
        if ((char)*pb < 0) {
            switch (rt_003a2898() & 0) {
            default: adv = 1; break;
            case 2: sc = pb[1] & 0x3f | (sc & 0x1f) << 6; adv = 2; break;
            case 3: sc = (sc & 0xf) << 0xc | (pb[1] & 0x3f) << 6 | pb[2] & 0x3f; adv = 3; break;
            case 4: sc = (sc & 0xf) << 0x12 | (pb[1] & 0x3f) << 0xc | (pb[2] & 0x3f) << 6 | pb[3] & 0x3f; adv = 4; break;
            }
        } else {
            adv = 1;
        }
    } else {
        /* inline buffer: scalar bytes at [&iter[0] + cursor] */
        unsigned char *pb = (unsigned char *)&iter[0] + iter[2];
        sc = (unsigned int)*pb;
        if ((char)*pb < 0) {
            switch (rt_003a2898() & 0) {
            default: adv = 1; break;
            case 2: sc = pb[1] & 0x3f | (sc & 0x1f) << 6; adv = 2; break;
            case 3: sc = (sc & 0xf) << 0xc | (pb[1] & 0x3f) << 6 | pb[2] & 0x3f; adv = 3; break;
            case 4: sc = (sc & 0xf) << 0x12 | (pb[1] & 0x3f) << 0xc | (pb[2] & 0x3f) << 6 | pb[3] & 0x3f; adv = 4; break;
            }
        } else {
            adv = 1;
        }
    }
    iter[2] = (unsigned long)adv + iter[2];
    uint64_t cb = iter[4];
    (*(void (**)(unsigned int *, unsigned int *))cb)(&sc, &sc);
    return (unsigned long)sc;
}

/* FUN_00252708 @ 0x00252708   (est. sk_swift_dump_state21)
 * Ghidra: void FUN_00252708(void)
 * Swift runtime dump variant: builds a value, appends a pair, forwards to
 * FUN_0025235c.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state21(void)
{
    rt_00351cc4(); rt_00349830(); rt_003505c4(); rt_00377824(); rt_00351f10(); rt_0007c1a4();
    rt_0034b0c4(); rt_003506b0(); rt_0034c2a4();
    uint64_t u = rt_0034a148(0, 0, 0);
    rt_00353468(u, 0, 0);
    sk_swift_dump_state20();
}

/*--------------------------------------------------------------------*/
/* FUN_002527a8 @ 0x002527a8   (est. sk_swift_dispatch_7)
 * Ghidra: void FUN_002527a8(undefined8 param_1, undefined8 param_2, code *UNRECOVERED_JUMPTABLE)
 * Swift runtime dispatch: sets up and jumps through the jump table.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dispatch_7(void *param_1, void *param_2, void *jmp)
{
    rt_00358144();
    rt_000a6894();
    rt_00355988();
    (*(void (**)(void))jmp)();
}

/*--------------------------------------------------------------------*/
/* FUN_002527e8 @ 0x002527e8   (est. sk_swift_scalar_pos)
 * Ghidra: ulong FUN_002527e8(ulong param_1, ulong param_2)
 * Computes a Swift scalar/position word: selects the offset (16-bit or 4-bit
 * field), and packs the flags (7 or 0xb) with the shifted index.
 * Confidence: high (Swift String position helper). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned long sk_swift_scalar_pos(unsigned long param_1, unsigned long param_2)
{
    unsigned long uVar1 = param_1;
    if ((param_2 & 0x2000000000000000ULL) != 0) uVar1 = param_2 >> 0x38 & 0xf;
    unsigned int uVar3 = (unsigned int)(param_1 >> 0x3b) & 1;
    if ((param_2 & 0x1000000000000000ULL) == 0) uVar3 = 1;
    unsigned long uVar2 = 7;
    if (uVar3 == 0) uVar2 = 0xb;
    return uVar2 | uVar1 << 0x10;
}

/*--------------------------------------------------------------------*/
/* FUN_00252818 @ 0x00252818   (est. sk_swift_string_advance)
 * Ghidra: ulong FUN_00252818(undefined8 param_1, ulong param_2, ulong param_3)
 * Swift string position advance: walks forward from the current position to the
 * next scalar boundary (skipping UTF-8 continuation/surrogate marker words
 * 0xa0d / 0x8080), returning the packed next-position word.
 * Confidence: medium (Swift String advance; identity inferred).
 * Notes: fatal on nil-optional unwrap (s_unsafelyUnwrapped string). */
unsigned long sk_swift_string_advance(void *param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long uVar2 = rt_0029eb58();
    unsigned long uVar3 = uVar2 >> 8 & 0x3f;
    unsigned long uVar8 = param_3 & 0x2000000000000000ULL;
    unsigned long uVar6 = param_2 & 0xffffffffffffULL;
    unsigned long uVar7 = param_3 >> 0x38 & 0xf;
    if (uVar3 == 0) {
        uVar3 = uVar6;
        if (uVar8 != 0) uVar3 = uVar7;
        if (uVar2 >> 0xe != uVar3 * 4) {
            uVar3 = uVar2 >> 0x10;
            if ((param_3 >> 0x3c & 1) == 0) {
                if (uVar8 == 0) {
                    uint64_t t;
                    if ((param_2 >> 0x3c & 1) == 0) t = rt_002a9ba8(param_2, param_3);
                    else t = (param_3 & 0xfffffffffffffffULL) + 0x20;
                    if (uVar3 + 1 != (t & 0xffffffffffff)) {
                        if (t == 0) rt_001afe4c();
                        unsigned short u = *(unsigned short *)((t & 0xffffffffffff) + uVar3);
                        if (u == 0xa0d || (u & 0x8080) != 0) { uVar3 = rt_002c6d00(uVar3, param_2, param_3); goto done1; }
                    }
                } else {
                    if (uVar3 + 1 != uVar7) {
                        unsigned short u = *(unsigned short *)(&param_2 + uVar3);
                        if (u == 0xa0d || (u & 0x8080) != 0) { uVar3 = rt_002c6d00(uVar3, param_2, param_3); goto done1; }
                    }
                }
                uVar3 = 1;
            } else {
                uVar3 = rt_002c6d00(uVar3, param_2, param_3);
            }
        }
    }
done1:
    uVar2 += uVar3 * 0x10000;
    unsigned long uVar9 = uVar2 & 0xffffffffffff0000ULL;
    uVar3 = uVar6;
    if (uVar8 != 0) uVar3 = uVar7;
    unsigned long uVar10 = param_3 & 0x1000000000000000ULL;
    long lVar4;
    if (uVar9 >> 0xe == uVar3 * 4) {
        lVar4 = 0;
    } else {
        uVar2 >>= 0x10;
        if (uVar10 == 0) {
            if (uVar8 == 0) {
                uint64_t t;
                if ((param_2 >> 0x3c & 1) == 0) t = rt_002a9ba8(param_2, param_3);
                else t = (param_3 & 0xfffffffffffffffULL) + 0x20;
                if (uVar2 + 1 != (t & 0xffffffffffff)) {
                    if (t == 0) rt_001afe4c();
                    unsigned short u = *(unsigned short *)((t & 0xffffffffffff) + uVar2);
                    if (u == 0xa0d || (u & 0x8080) != 0) { lVar4 = rt_002c6d00(uVar2, param_2, param_3); goto done2; }
                }
            } else {
                if (uVar2 + 1 != uVar7) {
                    unsigned short u = *(unsigned short *)(&param_2 + uVar2);
                    if (u == 0xa0d || (u & 0x8080) != 0) { lVar4 = rt_002c6d00(uVar2, param_2, param_3); goto done2; }
                }
            }
            uVar10 = 0;
            lVar4 = 1;
        } else {
            lVar4 = rt_002c6d00(uVar2, param_2, param_3);
            if (lVar4 > 0x3f) goto done3;
        }
    }
done2:
    uVar9 |= (unsigned long)lVar4 << 8;
done3:
    unsigned int uVar5 = (unsigned int)(param_2 >> 0x3b) & 1;
    if (uVar10 == 0) uVar5 = 1;
    unsigned long r = 7;
    if (uVar5 == 0) r = 0xb;
    return uVar9 | r;
}

/*--------------------------------------------------------------------*/
/* FUN_00252a64 @ 0x00252a64   (est. sk_swift_utf8_scalar_len)
 * Ghidra: ulong FUN_00252a64(undefined8 param_1, ulong param_2, ulong param_3)
 * Returns the packed position of the next scalar boundary after the byte at the
 * current cursor, decoding UTF-8 lead-byte width via LZCOUNT.
 * Confidence: high (UTF-8 scalar length; s_Swift_UnicodeHelpers string). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned long sk_swift_utf8_scalar_len(void *param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long uVar2 = rt_00167404();
    unsigned long unaff_x21;
    if ((param_3 >> 0x3c & 1) == 0) {
        unaff_x21 = uVar2 >> 0x10;
        if ((param_3 >> 0x3d & 1) != 0) {
            unsigned char b = *(unsigned char *)((char *)&param_2 + unaff_x21);
            unsigned int uVar4 = (unsigned int)rt_003a2898();
            if ((char)b >= 0) uVar4 = 1;
            return (unaff_x21 + uVar4) * 0x10000 | 5;
        }
        unsigned long lVar3;
        if ((param_2 >> 0x3c & 1) == 0) lVar3 = rt_002a9ba8(param_2, param_3);
        else lVar3 = (param_3 & 0xfffffffffffffffULL) + 0x20;
        unsigned char b = *(unsigned char *)(lVar3 + unaff_x21);
        unsigned int uVar4 = (unsigned int)rt_003a2898();
        if ((char)b >= 0) uVar4 = 1;
        return (unaff_x21 + uVar4) * 0x10000 | 5;
    }
    rt_002a49a8();
    rt_001afa84();
}

/*--------------------------------------------------------------------*/
/* FUN_00252b04 @ 0x00252b04   (est. sk_swift_coo_valid)
 * Ghidra: undefined8 FUN_00252b04(long param_1)
 * Swift CollectionOfOne: returns 1 if the element count is zero, else fatal.
 * Confidence: high (CollectionOfOne identity from string). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
uint64_t sk_swift_coo_valid(long param_1)
{
    if (param_1 == 0) return 1;
    rt_001afe4c();  /* fatal: CollectionOfOne index out of range */
}

/*--------------------------------------------------------------------*/
/* FUN_00252b68 @ 0x00252b68   (est. sk_swift_string_advance_store)
 * Ghidra: void FUN_00252b68(void)
 * String position advance that stores the result: computes the next scalar
 * position (like FUN_00252818) and writes the packed word to *x19.
 * Confidence: medium (Swift String advance + store). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_string_advance_store(void)
{
    uint64_t fl = rt_0035193c();
    unsigned long rt_state_local = 0;
    rt_0034da78();
    unsigned long uVar4 = rt_0029eb58();
    unsigned long uVar5 = uVar4 >> 8 & 0x3f;
    unsigned long uVar11 = rt_0034a958() & 0x2000000000000000ULL;
    unsigned long uVar9 = rt_0034a958() & 0xffffffffffffULL;
    unsigned long uVar10 = rt_0034a958() >> 0x38 & 0xf;
    if (uVar5 == 0) {
        uVar5 = uVar9;
        if (uVar11 != 0) uVar5 = uVar10;
        if (uVar4 >> 0xe == uVar5 * 4) {
            uVar5 = 0;
        } else {
            uVar4 >>= 0x10;
            if ((rt_0034a958() >> 0x3c & 1) == 0) {
                if (uVar11 == 0) {
                    uint64_t t;
                    if ((rt_0034a958() >> 0x3c & 1) == 0) { rt_0006b6f4(); t = rt_002a9ba8(); }
                    else t = (rt_0034a958() & 0xfffffffffffffffULL) + 0x20;
                    if (uVar4 + 1 != (t & 0xffffffffffff)) {
                        if (t == 0) rt_001afe4c();
                        rt_00352bd4(*(unsigned short *)((t & 0xffffffffffff) + uVar4));
                        if (rt_0034a148(0,0,0)) uVar5 = rt_002c6d00();
                    }
                } else {
                    if (uVar4 + 1 != uVar10) {
                        rt_00352bd4(*(unsigned short *)((char *)&rt_state_local + uVar4));
                        if (rt_0034a148(0,0,0)) uVar5 = rt_002c6d00();
                    }
                }
                uVar5 = 1;
            } else {
                rt_003510c4();
                uVar5 = rt_002c6d00();
            }
        }
    }
    uVar4 += uVar5 * 0x10000;
    unsigned long uVar12 = uVar4 & 0xffffffffffff0000ULL;
    uVar5 = uVar9;
    if (uVar11 != 0) uVar5 = uVar10;
    unsigned long uVar13 = rt_0034a958() & 0x1000000000000000ULL;
    long lVar6;
    if (uVar12 >> 0xe == uVar5 * 4) {
        lVar6 = 0;
    } else {
        uVar4 >>= 0x10;
        if (uVar13 == 0) {
            if (uVar11 == 0) {
                uint64_t t;
                if ((rt_0034a958() >> 0x3c & 1) == 0) { rt_0006b6f4(); t = rt_002a9ba8(); }
                else t = rt_003577a0();
                if (uVar4 + 1 != (t & 0xffffffffffff)) {
                    if (t == 0) rt_001afe4c();
                    rt_00352bd4(*(unsigned short *)((t & 0xffffffffffff) + uVar4));
                    if (rt_0034a148(0,0,0)) lVar6 = rt_002c6d00();
                }
            } else {
                if (uVar4 + 1 != uVar10) {
                    rt_00352bd4(*(unsigned short *)((char *)&rt_state_local + uVar4));
                    if (rt_0034a148(0,0,0)) lVar6 = rt_002c6d00();
                }
            }
            uVar13 = 0;
            lVar6 = 1;
        } else {
            rt_0034fe90();
            lVar6 = rt_002c6d00();
            if (lVar6 > 0x3f) goto done;
        }
    }
    uVar12 |= (unsigned long)lVar6 << 8;
done:
    unsigned int uVar8 = (unsigned int)(rt_0034a958() >> 0x3b) & 1;
    if (uVar13 == 0) uVar8 = 1;
    unsigned long r = 7;
    if (uVar8 == 0) r = 0xb;
    *(unsigned long *)rt_0034a958() = uVar12 | r;
    rt_00351774(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00252d38 @ 0x00252d38   (est. sk_swift_utf8_scalar_store)
 * Ghidra: void FUN_00252d38(ulong *param_1, ulong param_2, ulong param_3)
 * Stores the packed position of the next scalar boundary after the byte at the
 * current cursor into *param_1 (UTF-8 lead-byte width via LZCOUNT).
 * Confidence: high (UTF-8 scalar length; s_Swift_UnicodeHelpers string). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_utf8_scalar_store(unsigned long *param_1, unsigned long param_2, unsigned long param_3)
{
    unsigned long uVar2 = rt_00167404(*param_1);
    unsigned long unaff_x22;
    if ((param_3 >> 0x3c & 1) == 0) {
        unaff_x22 = uVar2 >> 0x10;
        if ((param_3 >> 0x3d & 1) != 0) {
            unsigned char b = *(unsigned char *)((char *)&param_2 + unaff_x22);
            unsigned int uVar4 = (unsigned int)rt_003a2898();
            if ((char)b >= 0) uVar4 = 1;
            *param_1 = (unaff_x22 + uVar4) * 0x10000 | 5;
            return;
        }
        unsigned long lVar3;
        if ((param_2 >> 0x3c & 1) == 0) lVar3 = rt_002a9ba8(param_2, param_3);
        else lVar3 = (param_3 & 0xfffffffffffffffULL) + 0x20;
        unsigned char b = *(unsigned char *)(lVar3 + unaff_x22);
        unsigned int uVar4 = (unsigned int)rt_003a2898();
        if ((char)b >= 0) uVar4 = 1;
        *param_1 = (unaff_x22 + uVar4) * 0x10000 | 5;
        return;
    }
    rt_002a49a8();
    rt_001afa84();
}

/*--------------------------------------------------------------------*/
/* FUN_00252de4 @ 0x00252de4   (est. sk_swift_dispatch_8)
 * Ghidra: void FUN_00252de4(void)
 * Swift runtime dispatch: sets up and jumps through the jump table
 * (FUN_00027818).
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dispatch_8(void)
{
    rt_0034a958();
    uint64_t t = rt_00027818();
    rt_00351c88(t, *(unsigned long *)(rt_0034a958() + 0x10));
    (*(void (**)(void))t)();
}

/*--------------------------------------------------------------------*/
/* FUN_00252e24 @ 0x00252e24   (est. sk_swift_buffer_scalar)
 * Ghidra: undefined1 [16] FUN_00252e24(undefined8 param_1, ulong param_2, ulong param_3,
 *          code *param_4)
 * Swift UnsafeBufferPointer scalar decode: walks from the current position to
 * the next scalar boundary, validates the slice bounds (Swift_Range / Invalid
 * slice fatal strings), copies up to 8 bytes, and returns the packed value.
 * Confidence: medium (Swift UnsafeBufferPointer; s_Swift_UnsafeBufferPointer
 *   and s_Index_out_of_range strings). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_buffer_scalar(void *param_1, unsigned long param_2, unsigned long param_3, void (*param_4)(void *, void *))
{
    unsigned long uVar4 = rt_00167404();
    unsigned long uVar5 = uVar4 >> 8 & 0x3f;
    unsigned long uVar13 = param_3 >> 0x38 & 0xf;
    unsigned long uVar11 = uVar4 >> 0x10;
    if (uVar5 == 0) {
        uVar5 = param_2 & 0xffffffffffffULL;
        if ((param_3 & 0x2000000000000000ULL) != 0) uVar5 = uVar13;
        if (uVar4 >> 0xe != uVar5 * 4) {
            if ((param_3 >> 0x3c & 1) != 0) goto skip1;
            if ((param_3 >> 0x3d & 1) != 0) {
                if (uVar11 + 1 == uVar13) { uVar5 = 1; goto skip2; }
                if (*(unsigned short *)((char *)&param_2 + uVar11) == 0xa0d ||
                    (*(unsigned short *)((char *)&param_2 + uVar11) & 0x8080) != 0) goto skip1;
                uVar5 = 1; goto skip2;
            }
            if ((param_2 >> 0x3c & 1) == 0) goto skip1;
            uVar5 = rt_002c6d00(uVar11, param_2, param_3);
            goto skip2;
        }
        uVar5 = 0;
    }
    while ((param_3 >> 0x3c & 1) != 0) {
        for (;;) {
            rt_002bbcd8();
            uint64_t t = rt_002a9ba8(param_2, param_3);
            if (uVar11 + 1 == (t & 0xffffffffffff)) break;
            if (t == 0) rt_001afe4c();
            unsigned short u = *(unsigned short *)((t & 0xffffffffffff) + uVar11);
            if (u != 0xa0d && (u & 0x8080) == 0) break;
            uVar5 = rt_002c6d00(uVar11, param_2, param_3);
            if ((param_3 >> 0x3c & 1) == 0) goto skip3;
        }
        uVar5 = 1;
    }
skip3:
skip1:
    uVar5 = rt_002c6d00(uVar11, param_2, param_3);
skip2:
    {
        long lVar12 = (long)uVar5 + (long)(uVar4 >> 0x10);
        unsigned long uVar10b = param_3;
        (void)uVar10b;
        /* slice bounds validation + up-to-8-byte copy of the scalar. */
        unsigned long lo = rt_0028e8c0(uVar11, lVar12, 0, 0, 0x7a8, 0x7a9);
        unsigned long slice = rt_001e4cbc(0, (long)(uVar13 ? 0 : uVar11));
        unsigned long local_70 = 0;
        unsigned long len = slice >> 0x40;
        if (len > 0xf) {
            unsigned long t = rt_002a4b90(0, 0, 0, 0);
            local_70 = *(unsigned long *)(t + 0x18);
        } else {
            unsigned long n = len;
            unsigned char *pb = (unsigned char *)(slice & 0xffffffffffff);
            for (unsigned long i = 0; i < n && i < 8; i++)
                local_70 |= (unsigned long)pb[i] << ((i & 7) * 8);
        }
        unsigned long out = 0xe000000000000000ULL;
        if ((local_70 & 0x8080808080808080ULL) != 0) out = 0xa000000000000000ULL;
        out |= len << 0x38 | local_70;
        param_4(&param_2, &local_70);
        rt_003a25d4(out);
        return (void *)(uintptr_t)param_2;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002532a8 @ 0x002532a8   (est. sk_swift_utf8_decode_scalar)
 * Ghidra: ulong FUN_002532a8(undefined8 param_1, ulong param_2, ulong param_3, code *param_4)
 * UTF-8 scalar decode: reads the byte at the cursor, decodes a 1-4 byte UTF-8
 * scalar, and calls param_4 with the scalar. Traps on 4-byte (unpaired
 * surrogate) sequences in the inline path.
 * Confidence: high (UTF-8 scalar decode; s_Swift_UnicodeHelpers string). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned long sk_swift_utf8_decode_scalar(void *param_1, unsigned long param_2, unsigned long param_3, void (*param_4)(void *, unsigned int *))
{
    unsigned long uVar2 = rt_00167404();
    unsigned char *pb;
    unsigned int local_44;
    if ((param_3 >> 0x3c & 1) != 0) {
        /* inline buffer with unpaired-surrogate trap (s_Swift_UnicodeHelpers) */
        rt_001afa84();
    }
    if ((param_3 >> 0x3d & 1) != 0) {
        pb = (unsigned char *)((char *)&param_2 + (uVar2 >> 0x10));
        local_44 = (unsigned int)*pb;
        if ((char)*pb < 0) {
            switch (rt_003a2898() & 0) {
            case 2: local_44 = pb[1] & 0x3f | (local_44 & 0x1f) << 6; break;
            case 3: local_44 = (local_44 & 0xf) << 0xc | (pb[1] & 0x3f) << 6 | pb[2] & 0x3f; break;
            case 4: local_44 = (local_44 & 0xf) << 0x12 | (pb[1] & 0x3f) << 0xc | (pb[2] & 0x3f) << 6 | pb[3] & 0x3f; break;
            }
        }
    } else {
        unsigned long lVar3;
        if ((param_2 >> 0x3c & 1) == 0) lVar3 = rt_002a9ba8(param_2, param_3);
        else lVar3 = (param_3 & 0xfffffffffffffffULL) + 0x20;
        pb = (unsigned char *)(lVar3 + (uVar2 >> 0x10));
        local_44 = (unsigned int)*pb;
        if ((char)*pb < 0) {
            switch (rt_003a2898() & 0) {
            case 2: local_44 = pb[1] & 0x3f | (local_44 & 0x1f) << 6; break;
            case 3: local_44 = (local_44 & 0xf) << 0xc | (pb[1] & 0x3f) << 6 | pb[2] & 0x3f; break;
            case 4: local_44 = (local_44 & 0xf) << 0x12 | (pb[1] & 0x3f) << 0xc | (pb[2] & 0x3f) << 6 | pb[3] & 0x3f; break;
            }
        }
    }
    param_4(&param_2, &local_44);
    return param_2 & 0xffffffff;
}

/*--------------------------------------------------------------------*/
/* FUN_0025346c @ 0x0025346c   (est. sk_swift_coo_element)
 * Ghidra: undefined1 [16] FUN_0025346c(long param_1, long param_2, code *param_3)
 * Swift CollectionOfOne element access: validates the single element, copies it
 * to a temp, invokes param_3 with the temp, releases the temp.
 * Confidence: high (CollectionOfOne identity). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_coo_element(long param_1, long param_2, void (*param_3)(void *, void *))
{
    rt_0019e690(param_1, 1, param_2);
    long p2 = param_2 + param_1 * 0x10;
    unsigned long local_50 = *(unsigned long *)(p2 + 0x20);
    unsigned long uVar1 = *(unsigned long *)(p2 + 0x28);
    rt_0036b270(uVar1);
    param_3(&local_50, &local_50);
    rt_003a25d4(uVar1);
    return (void *)(uintptr_t)local_50;
}

/*--------------------------------------------------------------------*/
/* FUN_002534e4 @ 0x002534e4   (est. sk_swift_coo_index)
 * Ghidra: undefined4 FUN_002534e4(long param_1, undefined4 param_2, code *param_3)
 * Swift CollectionOfOne subscript: if the index is 0 invoke param_3 with the
 * single element, else fatal (Index out of range).
 * Confidence: high (CollectionOfOne identity). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned int sk_swift_coo_index(long param_1, unsigned int param_2, void (*param_3)(unsigned int *, unsigned int *))
{
    if (param_1 == 0) {
        unsigned int local_28 = param_2;
        unsigned int local_24;
        param_3(&local_24, &local_28);
        return local_24;
    }
    rt_001afe4c();  /* fatal: CollectionOfOne Index out of range */
}

/*--------------------------------------------------------------------*/
/* FUN_00253570 @ 0x00253570   (est. sk_swift_coo_element2)
 * Ghidra: undefined1 [16] FUN_00253570(long param_1, undefined8 param_2, undefined8 param_3,
 *          code *param_4)
 * Swift CollectionOfOne element access variant: validates, copies, invokes.
 * Confidence: high (CollectionOfOne identity). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_coo_element2(long param_1, void *param_2, void *param_3, void (*param_4)(void *, void *))
{
    if (param_1 == 0) {
        unsigned long local_50 = (unsigned long)param_2;
        unsigned long local_48 = (unsigned long)param_3;
        rt_0036b270((uint64_t)param_3);
        param_4(&local_50, &local_50);
        rt_003a25d4((uint64_t)param_3);
        return (void *)(uintptr_t)local_50;
    }
    rt_001afe4c();  /* fatal: CollectionOfOne Index out of range */
}

/*--------------------------------------------------------------------*/
/* FUN_0025361c @ 0x0025361c   (est. sk_swift_dump_state22)
 * Ghidra: void FUN_0025361c(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Swift runtime dump variant: reads the value type, builds a description via
 * FUN_003497a0, dispatches through the method table, unwinds.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state22(void *param_1, void *param_2, void *param_3)
{
    rt_0008e518();
    rt_0034c59c();
    rt_00350bd8((unsigned long)param_3);
    unsigned long u = *(unsigned long *)(rt_0034a958() + 0x10);
    uint64_t d = rt_003497a0();
    rt_00377824(d, d >> 0x40, u);
    rt_00348e00(); rt_0007c1a4();
    rt_0034b0d4();
    rt_00352ecc();
    rt_00350b18(0);
    rt_00351aa4(rt_00351f1c());
    rt_00351d00();
    rt_003508a8(*(unsigned long *)(rt_00351f1c() + 8));
    rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0025372c @ 0x0025372c   (est. sk_swift_dump_state23)
 * Ghidra: void FUN_0025372c(void)
 * Swift runtime dump variant: builds a value, reads a pair from the buffer,
 * takes a lock, forwards to FUN_002522c4, releases.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state23(void)
{
    rt_0008e518();
    rt_0034b318(); rt_00350a64(); rt_00351aec(); rt_00377824(); rt_0034a450(); rt_0007c1a4();
    rt_0034b0d4(); rt_00319628(); rt_0035102c(); rt_0034ede8();
    unsigned long u = *(unsigned long *)(rt_0034a958() + *(int *)(rt_0034a958() + 0x2c) + 8);
    rt_00350c2c(); rt_00352ea8(); rt_00377bec(); rt_00027754(); rt_003547f8(); rt_00350ed0();
    sk_swift_dump_state18();
    rt_0036b270(u);
    rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00253804 @ 0x00253804   (est. sk_swift_unicode_len_obj2)
 * Ghidra: undefined * FUN_00253804(long *param_1, undefined8 param_2, undefined8 param_3, ulong param_4)
 * Allocates a 0x28-byte Unicode helper object, initializes it via FUN_00253884.
 * Confidence: medium (Swift Unicode object alloc). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_unicode_len_obj2(void *param_1, void *param_2, void *param_3, unsigned long param_4)
{
    long lVar1 = (long)rt_0036a908(0x28, 0xb536);
    *(long *)param_1 = lVar1;
    uint64_t u = (uint64_t)sk_swift_unicode_len_init2((void *)(uintptr_t)lVar1, (void *)(uintptr_t)param_2, (long)param_3,
                             (void *)(uintptr_t)*(unsigned long *)((param_4 & ~1ull) - 8));
    *(unsigned long *)(lVar1 + 0x20) = u;
    return (void *)(uintptr_t)lVar1;
}

/*--------------------------------------------------------------------*/
/* FUN_00253884 @ 0x00253884   (est. sk_swift_unicode_len_init2)
 * Ghidra: undefined1 [16] FUN_00253884(long *param_1, undefined8 param_2, long param_3, undefined8 param_4)
 * Initializes a Unicode helper object: reads the value from [param_3+0x18],
 * allocates the slot, forwards to FUN_0025361c.
 * Confidence: medium (Swift Unicode init). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_unicode_len_init2(void *param_1, void *param_2, long param_3, void *param_4)
{
    long lVar1 = *(long *)(param_3 + 0x18);
    *(long *)param_1 = lVar1;
    long lv = *(long *)(lVar1 + -8);
    *(long *)((char *)param_1 + 8) = lv;
    long l2 = (long)rt_0036a908(*(unsigned long *)(lv + 0x40), 0x5c89);
    *(long *)((char *)param_1 + 0x10) = l2;
    sk_swift_dump_state22((void *)(uintptr_t)l2, param_2, (void *)(uintptr_t)param_3);
    return (void *)(uintptr_t)l2;
}

/*--------------------------------------------------------------------*/
/* FUN_00253940 @ 0x00253940   (est. sk_swift_dump_state24)
 * Ghidra: void FUN_00253940(void)
 * Swift runtime dump variant: builds a value description and appends it.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state24(void)
{
    uint64_t a = rt_0035a6f4();
    rt_0034a32c(*(unsigned long *)(rt_0034a958() + -8), a, a >> 0x40, *(unsigned long *)((a & 0xffffffffffff) + 0x10));
    rt_00377824(0xff, 0);
    rt_00352efc(); rt_00310d68(); rt_0034b690();
    rt_000839d8();
}

/*--------------------------------------------------------------------*/
/* FUN_002539ac @ 0x002539ac   (est. sk_swift_dump_state25)
 * Ghidra: void FUN_002539ac(void)
 * Swift runtime dump variant: runs an irq-save / value-read sequence then jumps
 * through an unrecovered jump table.
 * Confidence: low (jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state25(void)
{
    rt_00357cb4(); rt_00349ef4();
    rt_00356bb0(*(unsigned long *)((0 & ~1ull) - 8));
    rt_0034b128(); rt_00357c74();
}
/* FUN_00253a14 @ 0x00253a14   (est. sk_swift_dump_state26)
 * Ghidra: void FUN_00253a14(void)
 * Swift runtime dump variant (irq-save / value-read + jump table).
 * Confidence: low (jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state26(void)
{
    rt_00357cb4(); rt_00349944();
    rt_00027754(*(unsigned long *)((0 & ~1ull) - 8));
    rt_003498a8(); rt_00357c74();
}
/* FUN_00253a7c @ 0x00253a7c   (est. sk_swift_dump_state27)
 * Ghidra: void FUN_00253a7c(void)
 * Swift runtime dump variant (irq-save / value-read + jump table).
 * Confidence: low (jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state27(void)
{
    rt_000867ec();
    rt_00356bb0(*(unsigned long *)((0 & ~1ull) - 8));
    rt_0034b778();
}
/* FUN_00253ae4 @ 0x00253ae4   (est. sk_swift_dump_state28)
 * Ghidra: void FUN_00253ae4(void)
 * Swift runtime dump variant (irq-save / value-read + jump table).
 * Confidence: low (jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state28(void)
{
    rt_00357cb4(); rt_00349ef4();
    rt_00027754(*(unsigned long *)((0 & ~1ull) - 8));
    rt_00356bb0(); rt_0034b128(); rt_00357c74();
}
/* FUN_00253b50 @ 0x00253b50   (est. sk_swift_dump_state29)
 * Ghidra: void FUN_00253b50(void)
 * Swift runtime dump variant (irq-save / value-read + jump table).
 * Confidence: low (jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state29(void)
{
    rt_00357cb4(); rt_00349944();
    rt_00027754(*(unsigned long *)((0 & ~1ull) - 8));
    rt_00027754(); rt_003498a8(); rt_00357c74();
}
/* FUN_00253bbc @ 0x00253bbc   (est. sk_swift_dump_state30)
 * Ghidra: void FUN_00253bbc(void)
 * Swift runtime dump variant (irq-save / value-read + jump table).
 * Confidence: low (jump table not recovered). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state30(void)
{
    rt_000867ec();
    rt_00027754(*(unsigned long *)((0 & ~1ull) - 8));
    rt_00356bb0(); rt_0034b778();
}

/*--------------------------------------------------------------------*/
/* FUN_00253d94 @ 0x00253d94   (est. sk_swift_apply_5)
 * Ghidra: void FUN_00253d94(undefined8 param_1, undefined8 param_2, code *param_3,
 *          undefined8 param_4, long param_5, undefined8 param_6, long param_7,
 *          undefined8 param_8, undefined8 param_9)
 * Applies a closure over a value: reads the type descriptor, builds the temp,
 * invokes the method-table entry at [param_5+0x2c], calls param_3, then the
 * deallocator at [lVar2+8].
 * Confidence: medium (Swift closure apply). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_apply_5(void *param_1, void *param_2, void (*param_3)(void *, void *), void *param_4,
                      long param_5, void *param_6, long param_7, void *param_8, void *param_9)
{
    long lVar2 = *(long *)(param_7 + -8);
    rt_0007c1a4();
    long lVar1 = (long)rt_00319338(0, (unsigned long)param_6, param_7, (unsigned long)param_9);
    (*(void (**)(void *, void *))(param_5 + *(int *)(lVar1 + 0x2c)))(0, param_2);
    param_3(param_1, (void *)0);
    (*(void (**)(void *, long))(lVar2 + 8))((void *)0, param_7);
}

/*--------------------------------------------------------------------*/
/* FUN_00253e98 @ 0x00253e98   (est. sk_swift_dump_state31)
 * Ghidra: void FUN_00253e98(undefined8 param_1, undefined8 param_2, long param_3,
 *          undefined8 param_4, undefined8 param_5)
 * Swift runtime dump variant: builds a value object (allocated via FUN_0036a940),
 * fills its fields, forwards through the runtime, unwinds.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state31(void *param_1, void *param_2, long param_3, void *param_4, void *param_5)
{
    rt_0008e518();
    uint64_t a = rt_003543a0();
    rt_00349720();
    rt_0007c1a4();
    unsigned long uVar4 = *(unsigned long *)(param_3 + 0x10);
    rt_003499c8();
    rt_00349068();
    rt_00351494(*(unsigned long *)(rt_0034a958() + 0x10));
    rt_0034ee58(); rt_00350ed0();
    unsigned long b = *(unsigned char *)(rt_00351f1c() + 0x50);
    unsigned long uVar3 = b + 0x40 & (b ^ 0xffffffffffffffff);
    long lVar5 = (long)rt_0036a940(0x66ab78, uVar3 + 0, b | 7);
    unsigned long uVar2 = *(unsigned long *)(rt_0034a958() + 0x18);
    *(unsigned long *)(lVar5 + 0x10) = uVar4;
    *(unsigned long *)(lVar5 + 0x18) = uVar2;
    *(unsigned long *)(lVar5 + 0x20) = 0;
    *(unsigned long *)(lVar5 + 0x28) = (unsigned long)param_5;
    rt_003511c0(*(unsigned long *)(rt_00351f1c() + 0x20), lVar5 + uVar3);
    rt_00027754((unsigned long)param_5);
    rt_00352a4c(0);
    sk_swift_dump_state18();
    rt_0036b270(a >> 0x40);
    rt_0008e500(0);
}

/*--------------------------------------------------------------------*/
/* FUN_00254020 @ 0x00254020   (est. sk_swift_apply_6)
 * Ghidra: void FUN_00254020(undefined8 param_1, undefined8 param_2, code *param_3,
 *          undefined8 param_4, long param_5, undefined8 param_6, long param_7,
 *          undefined8 param_8, undefined8 param_9)
 * Applies a closure over a value (variant with type lookup).
 * Confidence: medium (Swift closure apply). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_apply_6(void *param_1, void *param_2, void (*param_3)(void *, void *), void *param_4,
                      long param_5, void *param_6, long param_7, void *param_8, void *param_9)
{
    long lVar3 = *(long *)(param_7 + -8);
    rt_0007c1a4();
    uint64_t u = rt_00027754((unsigned long)param_9);
    long lVar2 = (long)rt_00319338(0, (unsigned long)param_6, param_7, u);
    (*(void (**)(void *, void *))(param_5 + *(int *)(lVar2 + 0x2c)))(0, param_2);
    param_3(param_1, (void *)0);
    (*(void (**)(void *, long))(lVar3 + 8))((void *)0, param_7);
}

/*--------------------------------------------------------------------*/
/* FUN_00254184 @ 0x00254184   (est. sk_swift_dump_state32)
 * Ghidra: undefined1 [16] FUN_00254184(long param_1, undefined8 param_2, uint param_3)
 * Swift runtime dump: builds a value description and forwards to FUN_0024893c.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void *sk_swift_dump_state32(long param_1, void *param_2, unsigned int param_3)
{
    rt_002488b4(param_1 + 0x18);
    uint64_t a = rt_003586d8();
    rt_0024893c(0, a, a >> 0x40, param_3);
    return (void *)(uintptr_t)param_2;
}

/*--------------------------------------------------------------------*/
/* FUN_00254200 @ 0x00254200   (est. sk_swift_dump_state33)
 * Ghidra: void FUN_00254200(undefined8 param_1, undefined8 param_2)
 * Swift runtime dump: runs the escape encoder FUN_00254244, then if the result
 * is zero emits param_2.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state33(void *param_1, void *param_2)
{
    sk_swift_escape_encoder();
    if (rt_0034a958() == 0) rt_00255738((unsigned long)param_2);
}

/*--------------------------------------------------------------------*/
/* FUN_00254244 @ 0x00254244   (est. sk_swift_escape_encoder)
 * Ghidra: void FUN_00254244(void)  [LARGE: Swift debugDescription string escape]
 * Swift debugDescription escape encoder: converts a single character into its
 * escaped textual form, handling the special escapes (quote, apostrophe,
 * backslash, tab, LF, CR, DEL, printable ASCII, and 1-4 hex-digit \u escapes
 * with surrogate pairs). It drives the string buffer through the runtime
 * append/emit helpers and the hex-digit emitter FUN_00254c18.
 * Confidence: low (Swift debugDescription escape; recovered shape, extensive
 *   unreachable-block removal in the decompiler).
 * Notes: DAT_005ce74b..DAT_005ce763 are the escape literal tables; 13
 *   unreachable blocks removed by the decompiler; SoftwareBreakpoint-free but
 *   heavily optimized. */
void sk_swift_escape_encoder(void)
{
    uint64_t fl = rt_00351e20();
    unsigned int ch = (unsigned int)fl;    /* extraout_w1: character code */
    if (ch == 0x22) {                       /* " */
        rt_00355fa0((unsigned long)&DAT_005ce75d);
        rt_00352c80();
    } else if (ch == 0x27) {                /* ' */
        rt_00355fa0((unsigned long)&DAT_005ce760);
        rt_00352c80();
    } else if (ch == 0x5c) {                /* \ */
        rt_00355fa0((unsigned long)&DAT_005ce763);
        rt_00352c80();
    } else if (ch - 0x20 < 0x5f) {          /* printable ASCII */
        rt_00355fa0((unsigned long)&DAT_005ce74b);
        rt_001a89a8();
        rt_00351a5c();
        sk_swift_hex_digit(ch >> 4);
        rt_0035a2f0();
        rt_00350af4();
        rt_001e3f70();
        rt_0034f198();
        rt_003a25d4();
        rt_003a25d4(ch >> 4);
        sk_swift_hex_digit(ch);
        rt_00351450(ch, ch, ch);
        rt_001e3f70();
        rt_00351a5c();
        rt_003a25d4();
        rt_003a25d4(ch);
        rt_00350744((unsigned long)&DAT_005ce74f);
        uint64_t u = rt_001a89a8();
        rt_00350af4(u, ch, u);
        rt_001e3f70();
        rt_00352c80();
        rt_003a25d4();
    } else if (ch == 0xd) {                 /* CR */
        rt_00355fa0((unsigned long)&DAT_005ce754);
        rt_00352c80();
    } else if (ch == 9) {                   /* TAB */
        rt_00355fa0((unsigned long)&DAT_005ce751);
        rt_00352c80();
    } else if (ch == 10) {                  /* LF */
        rt_00355fa0((unsigned long)&DAT_005ce757);
        rt_00352c80();
    } else if (ch == 0x7f) {                /* DEL */
        rt_00355fa0((unsigned long)&DAT_005ce75a);
        rt_00352c80();
    } else if (ch == 0) {                   /* NUL */
        rt_00355fa0((unsigned long)&DAT_005ce751);
        rt_00352c80();
    } else {                                /* multi-byte / hex escape */
        rt_00355fa0((unsigned long)&DAT_005ce74b);
        rt_00352c80();
    }
    uint64_t a = rt_00084180();
    rt_00351d30(a, a >> 0x40, 0);
}

/*--------------------------------------------------------------------*/
/* FUN_00254c18 @ 0x00254c18   (est. sk_swift_hex_digit)
 * Ghidra: void FUN_00254c18(uint param_1)
 * Emits a single hex digit character (0-9/A-F) for the low nibble of param_1
 * through the char emitter FUN_00255738.
 * Confidence: high (trivial hex-digit helper). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_hex_digit(unsigned int param_1)
{
    unsigned int uVar1 = (param_1 & 0xf) | 0x30;
    if ((param_1 & 0xf) > 9) uVar1 = (param_1 & 0xf) + 0x37;
    rt_00255738(uVar1);
}

/*--------------------------------------------------------------------*/
/* FUN_00254c7c @ 0x00254c7c   (est. sk_swift_dump_state34)
 * Ghidra: void FUN_00254c7c(void)
 * Swift runtime dump: forwards to the shared state helper FUN_003542b0.
 * Confidence: medium. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_dump_state34(void)
{
    rt_003542b0();
}

/*--------------------------------------------------------------------*/
/* FUN_00254c8c @ 0x00254c8c   (est. sk_swift_hex_string)
 * Ghidra: void FUN_00254c8c(ulong param_1)
 * Builds a Swift hex string for param_1: converts each nibble to a hex digit
 * through the escape/emit helpers, prepending '\\' and 'x' escapes as needed.
 * Confidence: low (Swift hex string; recovered shape). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_hex_string(unsigned long param_1)
{
    rt_003a25d4(0xe000000000000000ULL);
    sk_swift_escape_encoder();
    uint64_t a = 0;
    unsigned long uVar1 = a >> 0x40;
    unsigned long uVar2 = a & 0xffffffffffff;
    if (uVar1 == 0) {
        rt_00255738(param_1);
        rt_0035aba4();
        rt_0034ced8(uVar2 & 0xffffffffffff);
        uint64_t b = rt_00100efc();
        rt_002a4c98(b, b >> 0x40, 0);
        rt_003a25d4(uVar1);
        rt_0034a274();
        rt_000b43d0();
        return;
    }
    if ((uVar1 >> 0x3d & 1) == 0) { rt_0034ced8(uVar2 & 0xffffffffffff); rt_000b43d0(); return; }
    rt_00351e08();
    rt_003a25d4(0xe100000000000000ULL);
    rt_003a25d4(uVar1);
    rt_0034a274();
    rt_00350868(0x22);
    rt_002a4c98();
    rt_000b43d0();
}

/*--------------------------------------------------------------------*/
/* FUN_00254dc8 @ 0x00254dc8   (est. sk_swift_next_scalar)
 * Ghidra: ulong FUN_00254dc8(void)
 * Reads the next Unicode scalar from the current string cursor, dispatching
 * through a lookup, and returns it packed; 0x100000000 on end-of-string.
 * Confidence: medium (Unicode scalar read; identity inferred). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned long sk_swift_next_scalar(void)
{
    rt_0035098c();
    rt_0016749c();
    uint64_t a = rt_0034ecc8();
    unsigned long uVar2 = a & 0xffffffffffff;
    if ((bool)rt_0008412c()) {
        rt_003a25d4();
    } else {
        rt_000b43d0(uVar2, a >> 0x40, 0);
        rt_001ee030();
        rt_00356328();
        rt_003a25d4();
        if (rt_0034a958() == 1) return 0;
    }
    return 0x100000000;
}

/*--------------------------------------------------------------------*/
/* FUN_00254e50 @ 0x00254e50   (est. sk_swift_scalar_store32)
 * Ghidra: void FUN_00254e50(undefined4 *param_1)
 * Reads the next scalar and stores its low 32 bits into *param_1.
 * Confidence: high (trivial wrapper). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_scalar_store32(uint32_t *param_1)
{
    unsigned long u = sk_swift_next_scalar();
    *param_1 = (uint32_t)u;
}

/*--------------------------------------------------------------------*/
/* FUN_00254e80 @ 0x00254e80   (est. sk_swift_xor_string)
 * Ghidra: void FUN_00254e80(void)
 * Obfuscated constant string access: XORs the stored byte string
 * (s_uespemosmodnarodarenegylsetybdet_004e7a30, a reversed/obfuscated literal)
 * against a key byte and passes it to the string builder FUN_0034ec48.
 * Confidence: low (string obfuscation; literal identity unclear). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_xor_string(void)
{
    unsigned char b = (unsigned char)rt_00348c48();
    rt_0034ec48(b, (unsigned long)&DAT_004e7a30 + 0x10, b ^ (unsigned char)(*(unsigned char *)&DAT_004e7a30));
    rt_0022995c();
    rt_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_00254ed4 @ 0x00254ed4   (est. sk_swift_xor_string2)
 * Ghidra: void FUN_00254ed4(void)
 * Obfuscated constant string access variant: reads the word from the context,
 * builds the string through FUN_001a84f4, forwards.
 * Confidence: low. 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_xor_string2(void)
{
    unsigned int u = *(unsigned int *)rt_0034a958();
    rt_001a84f4(0);
    rt_0022995c(u);
    rt_001a8564();
}

/*--------------------------------------------------------------------*/
/* FUN_00254f50 @ 0x00254f50   (est. sk_swift_fatal_code3)
 * Ghidra: void FUN_00254f50(void)
 * Fatal error shim: reports code 1 then enters noreturn fatal.
 * Confidence: high (trivial noreturn). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_fatal_code3(void)
{
    rt_003488bc(1);
    rt_0006f768();
    rt_00352e0c();
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_00254fa4 @ 0x00254fa4   (est. sk_swift_codepoint_words)
 * Ghidra: undefined8 FUN_00254fa4(uint param_1)
 * Returns 1 if param_1 fits in 16 bits, else 2 (UTF-16 code-unit count).
 * Confidence: high (trivial helper). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
uint64_t sk_swift_codepoint_words(unsigned int param_1)
{
    uint64_t r = 1;
    if (param_1 > 0xffff) r = 2;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_00254fb4 @ 0x00254fb4   (est. sk_swift_utf16_encode)
 * Ghidra: ulong FUN_00254fb4(long param_1, ulong param_2)
 * UTF-16 surrogate encoding: for BMP scalars returns the value directly, and
 * for supplementary scalars splits into a high/low surrogate pair (offset by
 * 0x10000), trapping when the value does not fit.
 * Confidence: high (UTF-16 surrogate encode). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
unsigned long sk_swift_utf16_encode(long param_1, unsigned long param_2)
{
    unsigned int uVar2 = (unsigned int)param_2;
    if (param_1 == 1) {
        if (uVar2 >> 0x10 != 0) return (unsigned long)(uVar2 & 0x3ff | 0xffffdc00);
        rt_0035047c(); rt_003486b8(0x5b); rt_0034975c(); rt_001afe4c();
    }
    if (uVar2 >> 0x10 == 0) return param_2;
    uVar2 = (uVar2 + 0x3ff0000 >> 10 & 0xffff) + 0xd800;
    if (uVar2 >> 0x10 == 0) return (unsigned long)uVar2;
    /* SoftwareBreakpoint at 0x254ffc: does not return */
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_00255044 @ 0x00255044   (est. sk_swift_fatal_code4)
 * Ghidra: void FUN_00255044(void)
 * Fatal error shim: reports code 0x5b then enters noreturn fatal.
 * Confidence: high (trivial noreturn). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_fatal_code4(void)
{
    rt_0035047c();
    rt_003486b8(0x5b);
    rt_0034975c();
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002550a0 @ 0x002550a0   (est. sk_swift_fatal_code5)
 * Ghidra: void FUN_002550a0(void)
 * Fatal error shim: reports code 0x43 then enters noreturn fatal.
 * Confidence: high (trivial noreturn). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_fatal_code5(void)
{
    rt_0035047c();
    rt_003486b8(0x43);
    rt_0034975c();
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002550d0 @ 0x002550d0   (est. sk_swift_copy_word)
 * Ghidra: void FUN_002550d0(undefined8 *param_1, undefined8 *param_2)
 * Copies a word from the context through FUN_001e6e60 into *param_1.
 * Confidence: medium (Swift word copy). 
 * Notes: reconstructed from the Ghidra decompile (FUN_ address ground truth); calls shared Swift-runtime helpers declared as externs above.
 */
void sk_swift_copy_word(void *param_1, void *param_2)
{
    uint64_t u = rt_001e6e60(*(uint64_t *)param_2, 0);
    *(uint64_t *)param_1 = u;
}
