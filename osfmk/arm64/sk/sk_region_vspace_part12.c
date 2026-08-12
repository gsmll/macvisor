/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary;
 * estimates unless matched. Slice 12: 0x277be4-0x27ffd8, vspace/MMU layer. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* Faithful reconstruction helpers. STK stands in for un-resolvable stack-relative
 * address operands; SBORROW8/SCARRY8 approximate the ARM64 carry/borrow flags that
 * Ghidra uses to guard the debug traps (SoftwareBreakpoint) below. PAIR(x) is the
 * identity: it marks the lo half of a 16-byte register-pair return (hi is
 * unspecified/leftover in the decompile and approximated as 0). */
#define STK ((uint8_t *)0)
#define PAIR(x) (x)
#define SBORROW8(a,b) ((int64_t)(a) - (int64_t)(b) < 0)
#define SCARRY8(a,b)  ((int64_t)(a) + (int64_t)(b) < 0)

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helper declarations. These live in the shared runtime
 * library outside this slice (FUN_000xxxxx/001xxxxx/003xxxxx) or in the
 * 0x200000-0x280000 vspace region owned by sibling slice workers; their
 * bodies are reconstructed there. Signatures are unknown (raw binary), so
 * empty-paren (unspecified-argument) prototypes are used -- faithful to the
 * decompiler's call sites. Function-pointer globals are DAT_* with (*)(). */
extern uint64_t FUN_0008e518(void); /* runtime: frame prologue getter */
extern uint64_t FUN_00002534();
extern uint64_t FUN_00002688();
extern uint64_t FUN_000026e8();
extern uint64_t FUN_00002834();
extern uint64_t FUN_00019858();
extern uint64_t FUN_00027614();
extern uint64_t FUN_00027754();
extern uint64_t FUN_000651bc();
extern uint64_t FUN_0006a4c0();
extern uint64_t FUN_0006b2ec();
extern uint64_t FUN_0006b6f4();
extern uint64_t FUN_0006e778();
extern uint64_t FUN_0006f768();
extern uint64_t FUN_0006f794();
extern uint64_t FUN_00077894();
extern uint64_t FUN_0007c028();
extern uint64_t FUN_0007c1a4();
extern uint64_t FUN_0007c1c4();
extern uint64_t FUN_0008412c();
extern uint64_t FUN_00084174();
extern uint64_t FUN_00084180();
extern uint64_t FUN_00084220();
extern uint64_t FUN_00084234();
extern uint64_t FUN_000867ec();
extern uint64_t FUN_0008e0d4();
extern uint64_t FUN_0008e388();
extern uint64_t FUN_0008e500();
extern uint64_t FUN_0008e518();
extern uint64_t FUN_0009e234();
extern uint64_t FUN_000a68f4();
extern uint64_t FUN_000a6e14();
extern uint64_t FUN_000a6f88();
extern uint64_t FUN_000aa46c();
extern uint64_t FUN_000b43d0();
extern uint64_t FUN_000dbd0c();
extern uint64_t FUN_000dbe70();
extern uint64_t FUN_000e15d8();
extern uint64_t FUN_000e72b0();
extern uint64_t FUN_00100efc();
extern uint64_t FUN_0011d7e8();
extern uint64_t FUN_0014ae44();
extern uint64_t FUN_0019afd4();
extern uint64_t FUN_0019b25c();
extern uint64_t FUN_0019e644();
extern uint64_t FUN_0019ea20();
extern uint64_t FUN_0019fa60();
extern uint64_t FUN_0019fd10();
extern uint64_t FUN_001a0194();
extern uint64_t FUN_001a0414();
extern uint64_t FUN_001a1854();
extern uint64_t FUN_001a2128();
extern uint64_t FUN_001a4d84();
extern uint64_t FUN_001a6ab8();
extern uint64_t FUN_001a84f4();
extern uint64_t FUN_001a8564();
extern uint64_t FUN_001a89a8();
extern uint64_t FUN_001a9ac8();
extern uint64_t FUN_001afa84();
extern uint64_t FUN_001afe4c();
extern uint64_t FUN_001bcf40();
extern uint64_t FUN_001d80e0();
extern uint64_t FUN_001d88fc();
extern uint64_t FUN_001d9890();
extern uint64_t FUN_001db6b0();
extern uint64_t FUN_001dc430();
extern uint64_t FUN_001dc554();
extern uint64_t FUN_001dc754();
extern uint64_t FUN_001de698();
extern uint64_t FUN_001defb0();
extern uint64_t FUN_001df16c();
extern uint64_t FUN_001e088c();
extern uint64_t FUN_001e3048();
extern uint64_t FUN_001e3a28();
extern uint64_t FUN_001e664c();
extern uint64_t FUN_001e6be8();
extern uint64_t FUN_001e7038();
extern uint64_t FUN_001e7664();
extern uint64_t FUN_001e9f14();
extern uint64_t FUN_001f2104();
extern uint64_t FUN_001fe95c();
extern uint64_t FUN_001fea40();
extern uint64_t FUN_001ff258();
extern uint64_t FUN_0020083c();
extern uint64_t FUN_00206770();
extern uint64_t FUN_00211188();
extern uint64_t FUN_002357b4();
extern uint64_t FUN_0026b434();
extern uint64_t FUN_0026b71c();
extern uint64_t FUN_00270c08();
extern uint64_t FUN_00270d80();
extern uint64_t FUN_00271c4c();
extern uint64_t FUN_0027743c();
extern uint64_t FUN_00277474();
extern uint64_t FUN_00277ba8();
extern uint64_t FUN_0029207c();
extern uint64_t FUN_00292490();
extern uint64_t FUN_0029259c();
extern uint64_t FUN_002a4c98();
extern uint64_t FUN_0031090c();
extern uint64_t FUN_00310924();
extern uint64_t FUN_00310954();
extern uint64_t FUN_00310b08();
extern uint64_t FUN_00310b98();
extern uint64_t FUN_00310d34();
extern uint64_t FUN_00310d68();
extern uint64_t FUN_00310d80();
extern uint64_t FUN_00310d98();
extern uint64_t FUN_00310df0();
extern uint64_t FUN_00310e08();
extern uint64_t FUN_00310e20();
extern uint64_t FUN_00310e74();
extern uint64_t FUN_00310ea4();
extern uint64_t FUN_00310ed4();
extern uint64_t FUN_00319218();
extern uint64_t FUN_0031945c();
extern uint64_t FUN_003195f8();
extern uint64_t FUN_00319658();
extern uint64_t FUN_00319808();
extern uint64_t FUN_00319a4c();
extern uint64_t FUN_0031b080();
extern uint64_t FUN_0031b71c();
extern uint64_t FUN_0031b858();
extern uint64_t FUN_0031d488();
extern uint64_t FUN_0031d4e8();
extern uint64_t FUN_0031d518();
extern uint64_t FUN_0031d8b0();
extern uint64_t FUN_0031d8c8();
extern uint64_t FUN_0031d8e0();
extern uint64_t FUN_0031d910();
extern uint64_t FUN_0031d928();
extern uint64_t FUN_0031d940();
extern uint64_t FUN_0031d964();
extern uint64_t FUN_0031da6c();
extern uint64_t FUN_0031da9c();
extern uint64_t FUN_0031dacc();
extern uint64_t FUN_0031dafc();
extern uint64_t FUN_0031db2c();
extern uint64_t FUN_0031dc0c();
extern uint64_t FUN_0031dc24();
extern uint64_t FUN_0031dc40();
extern uint64_t FUN_0031e104();
extern uint64_t FUN_00325088();
extern uint64_t FUN_00344b1c();
extern uint64_t FUN_00344b98();
extern uint64_t FUN_00344ca8();
extern uint64_t FUN_00344e54();
extern uint64_t FUN_00347d60();
extern uint64_t FUN_00348638();
extern uint64_t FUN_003486fc();
extern uint64_t FUN_0034887c();
extern uint64_t FUN_003488bc();
extern uint64_t FUN_003489a8();
extern uint64_t FUN_00348a18();
extern uint64_t FUN_00348a34();
extern uint64_t FUN_00348a50();
extern uint64_t FUN_00348a80();
extern uint64_t FUN_00348a9c();
extern uint64_t FUN_00348bd8();
extern uint64_t FUN_00348c30();
extern uint64_t FUN_00348c48();
extern uint64_t FUN_00348cd0();
extern uint64_t FUN_00348ce8();
extern uint64_t FUN_00348d00();
extern uint64_t FUN_00348d4c();
extern uint64_t FUN_00348d64();
extern uint64_t FUN_00348e18();
extern uint64_t FUN_00348e30();
extern uint64_t FUN_00348e60();
extern uint64_t FUN_00348e9c();
extern uint64_t FUN_00348eb4();
extern uint64_t FUN_00348f38();
extern uint64_t FUN_00348f50();
extern uint64_t FUN_00348fd8();
extern uint64_t FUN_00349068();
extern uint64_t FUN_00349080();
extern uint64_t FUN_003490b8();
extern uint64_t FUN_003490d0();
extern uint64_t FUN_003490ec();
extern uint64_t FUN_00349178();
extern uint64_t FUN_00349204();
extern uint64_t FUN_00349234();
extern uint64_t FUN_0034926c();
extern uint64_t FUN_003493ac();
extern uint64_t FUN_003493c4();
extern uint64_t FUN_0034947c();
extern uint64_t FUN_003494e8();
extern uint64_t FUN_00349720();
extern uint64_t FUN_00349734();
extern uint64_t FUN_00349748();
extern uint64_t FUN_003497b4();
extern uint64_t FUN_00349830();
extern uint64_t FUN_003498a8();
extern uint64_t FUN_00349910();
extern uint64_t FUN_00349944();
extern uint64_t FUN_0034998c();
extern uint64_t FUN_003499b4();
extern uint64_t FUN_003499c8();
extern uint64_t FUN_003499f0();
extern uint64_t FUN_00349a68();
extern uint64_t FUN_00349b00();
extern uint64_t FUN_00349b3c();
extern uint64_t FUN_00349c44();
extern uint64_t FUN_00349c84();
extern uint64_t FUN_00349dcc();
extern uint64_t FUN_00349de8();
extern uint64_t FUN_00349ef4();
extern uint64_t FUN_00349f24();
extern uint64_t FUN_00349fcc();
extern uint64_t FUN_0034a168();
extern uint64_t FUN_0034a1b0();
extern uint64_t FUN_0034a1c8();
extern uint64_t FUN_0034a210();
extern uint64_t FUN_0034a2ac();
extern uint64_t FUN_0034a30c();
extern uint64_t FUN_0034a390();
extern uint64_t FUN_0034a400();
extern uint64_t FUN_0034a4e0();
extern uint64_t FUN_0034a4f8();
extern uint64_t FUN_0034a510();
extern uint64_t FUN_0034a618();
extern uint64_t FUN_0034a688();
extern uint64_t FUN_0034a944();
extern uint64_t FUN_0034a958();
extern uint64_t FUN_0034a9c0();
extern uint64_t FUN_0034a9e8();
extern uint64_t FUN_0034aab0();
extern uint64_t FUN_0034aac4();
extern uint64_t FUN_0034aadc();
extern uint64_t FUN_0034ab20();
extern uint64_t FUN_0034ac00();
extern uint64_t FUN_0034ac14();
extern uint64_t FUN_0034ac28();
extern uint64_t FUN_0034ac50();
extern uint64_t FUN_0034acf0();
extern uint64_t FUN_0034ae44();
extern uint64_t FUN_0034ae94();
extern uint64_t FUN_0034aea8();
extern uint64_t FUN_0034aee4();
extern uint64_t FUN_0034af20();
extern uint64_t FUN_0034afa0();
extern uint64_t FUN_0034b02c();
extern uint64_t FUN_0034b05c();
extern uint64_t FUN_0034b07c();
extern uint64_t FUN_0034b0b4();
extern uint64_t FUN_0034b0c4();
extern uint64_t FUN_0034b0d4();
extern uint64_t FUN_0034b128();
extern uint64_t FUN_0034b164();
extern uint64_t FUN_0034b18c();
extern uint64_t FUN_0034b1c0();
extern uint64_t FUN_0034b250();
extern uint64_t FUN_0034b278();
extern uint64_t FUN_0034b2a8();
extern uint64_t FUN_0034b2f8();
extern uint64_t FUN_0034b308();
extern uint64_t FUN_0034b3c8();
extern uint64_t FUN_0034b3d8();
extern uint64_t FUN_0034b3e8();
extern uint64_t FUN_0034b430();
extern uint64_t FUN_0034b470();
extern uint64_t FUN_0034b4c0();
extern uint64_t FUN_0034b518();
extern uint64_t FUN_0034b57c();
extern uint64_t FUN_0034b5fc();
extern uint64_t FUN_0034b640();
extern uint64_t FUN_0034b758();
extern uint64_t FUN_0034b778();
extern uint64_t FUN_0034b788();
extern uint64_t FUN_0034b7e4();
extern uint64_t FUN_0034b804();
extern uint64_t FUN_0034b87c();
extern uint64_t FUN_0034b8bc();
extern uint64_t FUN_0034ba28();
extern uint64_t FUN_0034baa8();
extern uint64_t FUN_0034bab8();
extern uint64_t FUN_0034bc6c();
extern uint64_t FUN_0034bd30();
extern uint64_t FUN_0034bdfc();
extern uint64_t FUN_0034bec4();
extern uint64_t FUN_0034c064();
extern uint64_t FUN_0034c084();
extern uint64_t FUN_0034c108();
extern uint64_t FUN_0034c2b4();
extern uint64_t FUN_0034c2f8();
extern uint64_t FUN_0034c330();
extern uint64_t FUN_0034c3a0();
extern uint64_t FUN_0034c3c4();
extern uint64_t FUN_0034c444();
extern uint64_t FUN_0034c754();
extern uint64_t FUN_0034c8a0();
extern uint64_t FUN_0034c8b8();
extern uint64_t FUN_0034c920();
extern uint64_t FUN_0034c9c8();
extern uint64_t FUN_0034c9d8();
extern uint64_t FUN_0034ca28();
extern uint64_t FUN_0034ce68();
extern uint64_t FUN_0034ce78();
extern uint64_t FUN_0034ce98();
extern uint64_t FUN_0034cf34();
extern uint64_t FUN_0034cf74();
extern uint64_t FUN_0034cf94();
extern uint64_t FUN_0034cfd4();
extern uint64_t FUN_0034cfe4();
extern uint64_t FUN_0034d004();
extern uint64_t FUN_0034d024();
extern uint64_t FUN_0034d090();
extern uint64_t FUN_0034d1b0();
extern uint64_t FUN_0034d264();
extern uint64_t FUN_0034d344();
extern uint64_t FUN_0034d384();
extern uint64_t FUN_0034d3a4();
extern uint64_t FUN_0034d3b4();
extern uint64_t FUN_0034d3e4();
extern uint64_t FUN_0034d414();
extern uint64_t FUN_0034d464();
extern uint64_t FUN_0034d758();
extern uint64_t FUN_0034d904();
extern uint64_t FUN_0034d934();
extern uint64_t FUN_0034d944();
extern uint64_t FUN_0034da38();
extern uint64_t FUN_0034db68();
extern uint64_t FUN_0034df34();
extern uint64_t FUN_0034e024();
extern uint64_t FUN_0034e0a4();
extern uint64_t FUN_0034e0c4();
extern uint64_t FUN_0034e0d4();
extern uint64_t FUN_0034e120();
extern uint64_t FUN_0034e130();
extern uint64_t FUN_0034e33c();
extern uint64_t FUN_0034e3fc();
extern uint64_t FUN_0034e464();
extern uint64_t FUN_0034e52c();
extern uint64_t FUN_0034e5cc();
extern uint64_t FUN_0034e5fc();
extern uint64_t FUN_0034e60c();
extern uint64_t FUN_0034e72c();
extern uint64_t FUN_0034eb94();
extern uint64_t FUN_0034ece8();
extern uint64_t FUN_0034edf8();
extern uint64_t FUN_0034eef8();
extern uint64_t FUN_0034ef38();
extern uint64_t FUN_0034f014();
extern uint64_t FUN_0034f1c4();
extern uint64_t FUN_0034f4a4();
extern uint64_t FUN_0034f634();
extern uint64_t FUN_0034f644();
extern uint64_t FUN_0034f8bc();
extern uint64_t FUN_0034f9c8();
extern uint64_t FUN_0034f9ec();
extern uint64_t FUN_0034fbd4();
extern uint64_t FUN_0034fce4();
extern uint64_t FUN_0034fdbc();
extern uint64_t FUN_0034fec0();
extern uint64_t FUN_0034ffb8();
extern uint64_t FUN_003501e4();
extern uint64_t FUN_003502e8();
extern uint64_t FUN_00350328();
extern uint64_t FUN_003503a0();
extern uint64_t FUN_003503d0();
extern uint64_t FUN_003503e0();
extern uint64_t FUN_00350404();
extern uint64_t FUN_00350410();
extern uint64_t FUN_00350428();
extern uint64_t FUN_00350434();
extern uint64_t FUN_0035044c();
extern uint64_t FUN_00350464();
extern uint64_t FUN_00350470();
extern uint64_t FUN_00350488();
extern uint64_t FUN_00350494();
extern uint64_t FUN_003504a0();
extern uint64_t FUN_003504ac();
extern uint64_t FUN_003504d0();
extern uint64_t FUN_003504e8();
extern uint64_t FUN_003504f4();
extern uint64_t FUN_00350500();
extern uint64_t FUN_00350518();
extern uint64_t FUN_00350524();
extern uint64_t FUN_00350530();
extern uint64_t FUN_0035053c();
extern uint64_t FUN_00350560();
extern uint64_t FUN_0035056c();
extern uint64_t FUN_003505e8();
extern uint64_t FUN_003505f4();
extern uint64_t FUN_0035060c();
extern uint64_t FUN_00350618();
extern uint64_t FUN_00350624();
extern uint64_t FUN_00350630();
extern uint64_t FUN_00350648();
extern uint64_t FUN_00350720();
extern uint64_t FUN_0035072c();
extern uint64_t FUN_00350738();
extern uint64_t FUN_00350744();
extern uint64_t FUN_00350798();
extern uint64_t FUN_003507c8();
extern uint64_t FUN_003507d4();
extern uint64_t FUN_00350804();
extern uint64_t FUN_00350810();
extern uint64_t FUN_0035084c();
extern uint64_t FUN_00350858();
extern uint64_t FUN_00350878();
extern uint64_t FUN_00350884();
extern uint64_t FUN_003508a8();
extern uint64_t FUN_003508b4();
extern uint64_t FUN_003508c0();
extern uint64_t FUN_003508cc();
extern uint64_t FUN_003508d8();
extern uint64_t FUN_003508e4();
extern uint64_t FUN_003508f0();
extern uint64_t FUN_00350908();
extern uint64_t FUN_00350914();
extern uint64_t FUN_00350920();
extern uint64_t FUN_00350944();
extern uint64_t FUN_0035098c();
extern uint64_t FUN_00350998();
extern uint64_t FUN_003509a4();
extern uint64_t FUN_003509b0();
extern uint64_t FUN_003509bc();
extern uint64_t FUN_003509d4();
extern uint64_t FUN_003509e0();
extern uint64_t FUN_003509ec();
extern uint64_t FUN_00350a04();
extern uint64_t FUN_00350a10();
extern uint64_t FUN_00350a28();
extern uint64_t FUN_00350a34();
extern uint64_t FUN_00350a40();
extern uint64_t FUN_00350a64();
extern uint64_t FUN_00350a70();
extern uint64_t FUN_00350aa0();
extern uint64_t FUN_00350aac();
extern uint64_t FUN_00350ab8();
extern uint64_t FUN_00350af4();
extern uint64_t FUN_00350b00();
extern uint64_t FUN_00350b0c();
extern uint64_t FUN_00350b24();
extern uint64_t FUN_00350b30();
extern uint64_t FUN_00350b54();
extern uint64_t FUN_00350b6c();
extern uint64_t FUN_00350b84();
extern uint64_t FUN_00350ba8();
extern uint64_t FUN_00350bc0();
extern uint64_t FUN_00350bd8();
extern uint64_t FUN_00350bf0();
extern uint64_t FUN_00350bfc();
extern uint64_t FUN_00350c08();
extern uint64_t FUN_00350c20();
extern uint64_t FUN_00350c38();
extern uint64_t FUN_00350c50();
extern uint64_t FUN_00350c80();
extern uint64_t FUN_00350d24();
extern uint64_t FUN_00350d94();
extern uint64_t FUN_00350dd4();
extern uint64_t FUN_00350e64();
extern uint64_t FUN_00350e94();
extern uint64_t FUN_00350ea4();
extern uint64_t FUN_00350ed0();
extern uint64_t FUN_00350eec();
extern uint64_t FUN_00350f9c();
extern uint64_t FUN_003510a0();
extern uint64_t FUN_003510c4();
extern uint64_t FUN_003510d0();
extern uint64_t FUN_003510f4();
extern uint64_t FUN_00351100();
extern uint64_t FUN_00351118();
extern uint64_t FUN_0035113c();
extern uint64_t FUN_00351160();
extern uint64_t FUN_00351178();
extern uint64_t FUN_003511c0();
extern uint64_t FUN_00351214();
extern uint64_t FUN_0035125c();
extern uint64_t FUN_00351274();
extern uint64_t FUN_003512c0();
extern uint64_t FUN_003512cc();
extern uint64_t FUN_00351300();
extern uint64_t FUN_0035130c();
extern uint64_t FUN_00351318();
extern uint64_t FUN_00351324();
extern uint64_t FUN_00351330();
extern uint64_t FUN_0035133c();
extern uint64_t FUN_00351354();
extern uint64_t FUN_00351360();
extern uint64_t FUN_00351384();
extern uint64_t FUN_003513b4();
extern uint64_t FUN_003513d8();
extern uint64_t FUN_00351408();
extern uint64_t FUN_00351414();
extern uint64_t FUN_0035142c();
extern uint64_t FUN_00351450();
extern uint64_t FUN_0035145c();
extern uint64_t FUN_00351488();
extern uint64_t FUN_00351494();
extern uint64_t FUN_003514a0();
extern uint64_t FUN_003514b8();
extern uint64_t FUN_003514d0();
extern uint64_t FUN_003514dc();
extern uint64_t FUN_0035152c();
extern uint64_t FUN_003515b4();
extern uint64_t FUN_003515cc();
extern uint64_t FUN_003515fc();
extern uint64_t FUN_00351648();
extern uint64_t FUN_0035166c();
extern uint64_t FUN_00351684();
extern uint64_t FUN_0035169c();
extern uint64_t FUN_003516b4();
extern uint64_t FUN_003516d8();
extern uint64_t FUN_003516e4();
extern uint64_t FUN_003516f0();
extern uint64_t FUN_003516fc();
extern uint64_t FUN_00351720();
extern uint64_t FUN_003517c0();
extern uint64_t FUN_0035187c();
extern uint64_t FUN_003518ac();
extern uint64_t FUN_003518b8();
extern uint64_t FUN_003518c4();
extern uint64_t FUN_00351990();
extern uint64_t FUN_0035199c();
extern uint64_t FUN_003519b4();
extern uint64_t FUN_00351a08();
extern uint64_t FUN_00351a20();
extern uint64_t FUN_00351ab0();
extern uint64_t FUN_00351abc();
extern uint64_t FUN_00351ad4();
extern uint64_t FUN_00351af8();
extern uint64_t FUN_00351b20();
extern uint64_t FUN_00351c4c();
extern uint64_t FUN_00351c88();
extern uint64_t FUN_00351cc4();
extern uint64_t FUN_00351dcc();
extern uint64_t FUN_00351df0();
extern uint64_t FUN_00351e08();
extern uint64_t FUN_00351e48();
extern uint64_t FUN_00351e84();
extern uint64_t FUN_00351ec0();
extern uint64_t FUN_00351ee0();
extern uint64_t FUN_00351f10();
extern uint64_t FUN_00351f1c();
extern uint64_t FUN_00351f58();
extern uint64_t FUN_00351f88();
extern uint64_t FUN_00352098();
extern uint64_t FUN_00352468();
extern uint64_t FUN_00352474();
extern uint64_t FUN_00352498();
extern uint64_t FUN_00352554();
extern uint64_t FUN_0035256c();
extern uint64_t FUN_00352680();
extern uint64_t FUN_003526b8();
extern uint64_t FUN_00352758();
extern uint64_t FUN_00352834();
extern uint64_t FUN_00352840();
extern uint64_t FUN_00352894();
extern uint64_t FUN_00352920();
extern uint64_t FUN_00352980();
extern uint64_t FUN_00352a40();
extern uint64_t FUN_00352b50();
extern uint64_t FUN_00352b80();
extern uint64_t FUN_00352b8c();
extern uint64_t FUN_00352b98();
extern uint64_t FUN_00352bb0();
extern uint64_t FUN_00352c4c();
extern uint64_t FUN_00352c58();
extern uint64_t FUN_00352c98();
extern uint64_t FUN_00352ca4();
extern uint64_t FUN_00352cb0();
extern uint64_t FUN_00352cec();
extern uint64_t FUN_00352d64();
extern uint64_t FUN_00352ddc();
extern uint64_t FUN_00352efc();
extern uint64_t FUN_00353000();
extern uint64_t FUN_0035300c();
extern uint64_t FUN_00353034();
extern uint64_t FUN_00353050();
extern uint64_t FUN_00353098();
extern uint64_t FUN_003530f4();
extern uint64_t FUN_00353130();
extern uint64_t FUN_0035313c();
extern uint64_t FUN_00353238();
extern uint64_t FUN_00353274();
extern uint64_t FUN_00353360();
extern uint64_t FUN_003536ac();
extern uint64_t FUN_00353718();
extern uint64_t FUN_00353734();
extern uint64_t FUN_003537f0();
extern uint64_t FUN_003539f4();
extern uint64_t FUN_00353a00();
extern uint64_t FUN_00353a30();
extern uint64_t FUN_00353a6c();
extern uint64_t FUN_00353ba0();
extern uint64_t FUN_00353bac();
extern uint64_t FUN_00353bb8();
extern uint64_t FUN_00353c18();
extern uint64_t FUN_00353cf0();
extern uint64_t FUN_00353cfc();
extern uint64_t FUN_00353d14();
extern uint64_t FUN_00353d70();
extern uint64_t FUN_00353d7c();
extern uint64_t FUN_00353dac();
extern uint64_t FUN_00353dfc();
extern uint64_t FUN_00353e94();
extern uint64_t FUN_00353f2c();
extern uint64_t FUN_00353f50();
extern uint64_t FUN_00354028();
extern uint64_t FUN_00354064();
extern uint64_t FUN_00354300();
extern uint64_t FUN_003543c4();
extern uint64_t FUN_0035460c();
extern uint64_t FUN_00354660();
extern uint64_t FUN_00354708();
extern uint64_t FUN_0035478c();
extern uint64_t FUN_003547ec();
extern uint64_t FUN_003547f8();
extern uint64_t FUN_003548ac();
extern uint64_t FUN_003548dc();
extern uint64_t FUN_00354924();
extern uint64_t FUN_00354a00();
extern uint64_t FUN_00354a78();
extern uint64_t FUN_00354b08();
extern uint64_t FUN_00354b50();
extern uint64_t FUN_00354bbc();
extern uint64_t FUN_00354d74();
extern uint64_t FUN_00354de8();
extern uint64_t FUN_00354f10();
extern uint64_t FUN_00354f80();
extern uint64_t FUN_0035505c();
extern uint64_t FUN_00355100();
extern uint64_t FUN_00355224();
extern uint64_t FUN_00355448();
extern uint64_t FUN_00355464();
extern uint64_t FUN_00355684();
extern uint64_t FUN_00355958();
extern uint64_t FUN_003559d8();
extern uint64_t FUN_00355b10();
extern uint64_t FUN_00355bdc();
extern uint64_t FUN_00355c28();
extern uint64_t FUN_00355ca4();
extern uint64_t FUN_00355cb0();
extern uint64_t FUN_00355cbc();
extern uint64_t FUN_00355db4();
extern uint64_t FUN_00355dc0();
extern uint64_t FUN_00355f04();
extern uint64_t FUN_00355f40();
extern uint64_t FUN_00355fac();
extern uint64_t FUN_00356048();
extern uint64_t FUN_0035606c();
extern uint64_t FUN_003560f8();
extern uint64_t FUN_003561a0();
extern uint64_t FUN_00356340();
extern uint64_t FUN_00356408();
extern uint64_t FUN_00356600();
extern uint64_t FUN_00356750();
extern uint64_t FUN_00356780();
extern uint64_t FUN_003567e0();
extern uint64_t FUN_0035687c();
extern uint64_t FUN_00356900();
extern uint64_t FUN_00356924();
extern uint64_t FUN_0035697c();
extern uint64_t FUN_003569cc();
extern uint64_t FUN_00356a08();
extern uint64_t FUN_00356a7c();
extern uint64_t FUN_00356aa0();
extern uint64_t FUN_00356ac4();
extern uint64_t FUN_00356ba4();
extern uint64_t FUN_00357068();
extern uint64_t FUN_00357338();
extern uint64_t FUN_00357398();
extern uint64_t FUN_003573c0();
extern uint64_t FUN_0035745c();
extern uint64_t FUN_0035748c();
extern uint64_t FUN_00357a84();
extern uint64_t FUN_00357aa8();
extern uint64_t FUN_00357ac0();
extern uint64_t FUN_00357af8();
extern uint64_t FUN_00357bec();
extern uint64_t FUN_00357c74();
extern uint64_t FUN_00357cb4();
extern uint64_t FUN_00357fc4();
extern uint64_t FUN_00358288();
extern uint64_t FUN_00358324();
extern uint64_t FUN_00358720();
extern uint64_t FUN_00358864();
extern uint64_t FUN_00358924();
extern uint64_t FUN_00358954();
extern uint64_t FUN_003589cc();
extern uint64_t FUN_00358a74();
extern uint64_t FUN_00358ad4();
extern uint64_t FUN_00358b24();
extern uint64_t FUN_00358b9c();
extern uint64_t FUN_00358bcc();
extern uint64_t FUN_00358cf8();
extern uint64_t FUN_00358da0();
extern uint64_t FUN_00358dc4();
extern uint64_t FUN_00358df4();
extern uint64_t FUN_00358e34();
extern uint64_t FUN_00358e7c();
extern uint64_t FUN_00358ec4();
extern uint64_t FUN_00358ee8();
extern uint64_t FUN_00358f00();
extern uint64_t FUN_00358f78();
extern uint64_t FUN_00358fb4();
extern uint64_t FUN_00358fc8();
extern uint64_t FUN_00358fe8();
extern uint64_t FUN_00359000();
extern uint64_t FUN_00359134();
extern uint64_t FUN_00359350();
extern uint64_t FUN_00359490();
extern uint64_t FUN_00359568();
extern uint64_t FUN_003597f0();
extern uint64_t FUN_00359880();
extern uint64_t FUN_00359920();
extern uint64_t FUN_00359ad4();
extern uint64_t FUN_00359c0c();
extern uint64_t FUN_00359d44();
extern uint64_t FUN_00359e28();
extern uint64_t FUN_00359e40();
extern uint64_t FUN_00359f48();
extern uint64_t FUN_00359f60();
extern uint64_t FUN_0035a1e8();
extern uint64_t FUN_0035a4ec();
extern uint64_t FUN_0035a560();
extern uint64_t FUN_0035a718();
extern uint64_t FUN_0035a7e8();
extern uint64_t FUN_0035a8d0();
extern uint64_t FUN_0035a9b0();
extern uint64_t FUN_003625e4();
extern uint64_t FUN_0036298c();
extern uint64_t FUN_00369340();
extern uint64_t FUN_00369584();
extern uint64_t FUN_0036986c();
extern uint64_t FUN_003698b0();
extern uint64_t FUN_0036993c();
extern uint64_t FUN_0036a908();
extern uint64_t FUN_0036a940();
extern uint64_t FUN_0036a9a0();
extern uint64_t FUN_0036b118();
extern uint64_t FUN_0036b270();
extern uint64_t FUN_0036b588();
extern uint64_t FUN_0036b6ac();
extern uint64_t FUN_003722e4();
extern uint64_t FUN_00376820();
extern uint64_t FUN_00377824();
extern uint64_t FUN_00377bec();
extern uint64_t FUN_0039fb68();
extern uint64_t FUN_0039fcc4();
extern uint64_t FUN_0039fcd8();
extern uint64_t FUN_0039ff2c();
extern uint64_t FUN_003a017c();
extern uint64_t FUN_003a0440();
extern uint64_t FUN_003a0690();
extern uint64_t FUN_003a0968();
extern uint64_t FUN_003a25d4();
extern uint64_t FUN_003a261c();
extern uint64_t thunk_FUN_00077a90(); /* out of slice (PLT thunk) */
extern uint64_t thunk_FUN_002298d4(); /* out of slice (PLT thunk) */
extern uint64_t thunk_FUN_0036b270(); /* out of slice (PLT thunk) */
extern uint64_t (*DAT_00658c00)(); /* out of slice (global fnptr) */
extern unsigned long DAT_003471a4; /* out of slice (global data) */
extern unsigned long DAT_003471a8; /* out of slice (global data) */
extern unsigned long DAT_004baeb0;
extern unsigned long DAT_004baeb8; /* out of slice (global data) */
extern unsigned long DAT_004e8214; /* out of slice (global data) */
extern unsigned long DAT_004ea72c; /* out of slice (global data) */
extern unsigned long DAT_004eaac8; /* out of slice (global data) */
extern unsigned long DAT_004eaae4; /* out of slice (global data) */
extern unsigned long DAT_004eabe4; /* out of slice (global data) */
extern unsigned long DAT_004eac1c; /* out of slice (global data) */
extern unsigned long DAT_004f1754; /* out of slice (global data) */
extern unsigned long DAT_004f2210; /* out of slice (global data) */
extern unsigned long DAT_004f2670; /* out of slice (global data) */
extern unsigned long DAT_005be7c0; /* out of slice (global data) */
extern unsigned long DAT_005d3ad7; /* out of slice (global data) */
extern unsigned long DAT_0060e208; /* out of slice (global data) */
extern unsigned long DAT_0060e230; /* out of slice (global data) */
extern unsigned long DAT_00657700; /* out of slice (global data) */


/* In-slice forward declarations. */

uint64_t vspace_op_00277be4(void);
uint64_t vspace_op_00277d80(void);
uint64_t vspace_op_00277de0(void);
uint64_t vspace_op_002782a4(void);
uint64_t vspace_op_00278dac(void);
uint64_t vspace_op_00278e54(void);
uint64_t vspace_op_0027905c(uint64_t arg1,uint64_t arg2,int64_t arg3,uint64_t arg4,
                 uint64_t arg5);
uint64_t vspace_op_00279558(void);
uint64_t vspace_op_00279568(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
uint64_t vspace_op_00279c5c(void);
uint64_t vspace_op_00279c60(void);
uint64_t vspace_op_00279c7c(void);
uint64_t vspace_op_00279cbc(void);
uint64_t vspace_op_00279cc0(void);
uint64_t vspace_op_00279cdc(void);
uint64_t vspace_op_00279ce0(void);
uint64_t vspace_op_00279cfc(void);
uint64_t vspace_op_00279d78(void);
uint64_t vspace_op_00279e90(void);
uint64_t vspace_op_0027a6e0(void);
uint64_t vspace_op_0027ad9c(uint64_t arg1,uint64_t arg2);
uint64_t vspace_op_0027ade0(void);
uint64_t vspace_op_0027b304(void);
uint64_t vspace_op_0027b3c0(void);
uint64_t vspace_op_0027b41c(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4,
                 uint64_t arg5);
uint64_t vspace_op_0027b8c0(void);
uint64_t vspace_op_0027bb78(void);
uint64_t vspace_op_0027bc50(uint64_t arg1);
uint64_t vspace_op_0027bc98(int64_t *param_1,uint64_t *param_2,int64_t arg3);
uint64_t vspace_op_0027bd10(int64_t *param_1,uint64_t arg2,uint64_t arg3,uint64_t arg4,
            uint64_t arg5);
uint64_t vspace_op_0027bdd4(uint64_t arg1,uint64_t arg2);
uint64_t vspace_op_0027be40(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027bedc(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027bf78(void);
uint64_t vspace_op_0027bfc8(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027c010(void);
uint64_t vspace_op_0027c054(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027c0a8(void);
uint64_t vspace_op_0027c1c0(void);
uint64_t vspace_op_0027c224(uint64_t arg1,int64_t arg2,int64_t arg3);
uint64_t vspace_op_0027c37c(void);
uint64_t vspace_op_0027c3d0(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027c418(void);
uint64_t vspace_op_0027c45c(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027c4a0(void);
uint64_t vspace_op_0027c50c(int64_t *param_1,uint64_t arg2,int64_t arg3);
uint64_t vspace_op_0027c5b4(void);
uint64_t vspace_op_0027c5f8(void);
uint64_t vspace_op_0027c64c(void);
uint64_t vspace_op_0027c698(void);
uint64_t vspace_op_0027c740(void);
uint64_t vspace_op_0027c770(void);
uint64_t vspace_op_0027c7a0(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
uint64_t vspace_op_0027c85c(uint64_t arg1,uint64_t arg2,uint64_t *param_3);
uint64_t vspace_op_0027cd04(void);
uint64_t vspace_op_0027ce54(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027cf48(void);
uint64_t vspace_op_0027d13c(void);
uint64_t vspace_op_0027d37c(void);
uint64_t vspace_op_0027d49c(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027d530(int64_t arg1);
uint64_t vspace_op_0027d648(uint64_t arg1);
uint64_t vspace_op_0027d674(uint8_t *param_1,uint64_t *param_2);
uint64_t vspace_op_0027d6a4(uint64_t *param_1);
uint64_t vspace_op_0027d6d0(void);
uint64_t vspace_op_0027da14(uint64_t arg1,int64_t arg2,int64_t arg3);
uint64_t vspace_op_0027da90(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027db18(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027db60(void);
uint64_t vspace_op_0027dba4(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027dbe4(uint64_t *param_1);
uint64_t vspace_op_0027dc0c(int64_t *param_1,uint64_t *param_2,uint64_t arg3);
uint64_t vspace_op_0027dc80(int64_t *param_1,uint64_t arg2,int64_t arg3);
uint64_t vspace_op_0027dd28(uint64_t arg1,uint64_t arg2);
uint64_t vspace_op_0027dd94(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027de1c(void);
uint64_t vspace_op_0027de68(int64_t arg1,int64_t arg2);
uint64_t vspace_op_0027df2c(uint64_t arg1);
uint64_t vspace_op_0027df74(uint64_t arg1);
uint64_t vspace_op_0027dfbc(void);
uint64_t vspace_op_0027e044(void);
uint64_t vspace_op_0027e0d4(void);
uint64_t vspace_op_0027e17c(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);
uint64_t vspace_op_0027e4ac(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027e698(void);
uint64_t vspace_op_0027e718(void);
uint64_t vspace_op_0027e778(void);
uint64_t vspace_op_0027e8e4(void);
uint64_t vspace_op_0027ea48(void);
uint64_t vspace_op_0027ebac(void);
uint64_t vspace_op_0027ed08(uint64_t arg1,uint64_t arg2);
uint64_t vspace_op_0027ed7c(uint64_t arg1,int64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027eebc(void);
uint64_t vspace_op_0027f010(void);
uint64_t vspace_op_0027f100(void);
uint64_t vspace_op_0027f448(void);
uint64_t vspace_op_0027f83c(int64_t arg1,int64_t arg2);
uint64_t vspace_op_0027f94c(void);
uint64_t vspace_op_0027f9b0(uint64_t arg1,uint64_t arg2,uint64_t arg3);
uint64_t vspace_op_0027fb24(void);
uint64_t vspace_op_0027fbfc(void);
uint64_t vspace_op_0027fca0(void);
uint64_t vspace_op_0027fd38(void);
uint64_t vspace_op_0027fdd4(uint64_t arg1,uint64_t arg2,int64_t arg3);
uint64_t vspace_op_0027fe84(void);
uint64_t vspace_op_0027ffd8(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4);

/* FUN_00277be4 @ 0x00277be4  (est. vspace_op_00277be4)
 * Ghidra: void vspace_op_00277be4(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00277be4(void)
{
    uint64_t v1;
    uint64_t v2;
    int64_t x8;
    uint64_t (*x8_00)();;
    uint64_t (*x8_01)();;
    uint64_t (*x8_02)();;
    uint64_t (*x9)();;
    int64_t x16;
    uint64_t x20;
    int64_t x26;
    uint64_t av3;
    uint64_t is00000008;
    uint64_t st40;
    int64_t loc8;
  
  FUN_0008e518();
  FUN_00358a74();
  FUN_00356900();
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_00348f50();
  FUN_0034d024();
  FUN_00310e08();
  FUN_00348cd0();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b0c4();
  FUN_00350920();
  v1 = FUN_00310d80();
  FUN_0036b270();
  v2 = FUN_00349234();
  FUN_00376820(v2,v1);
  v1 = FUN_0035a4ec();
  FUN_00355ca4(v1,st40);
  FUN_001db6b0();
  FUN_0036b118();
  if (loc8 != *(int64_t *)(x26 + 0x10)) {
    FUN_00352840();
    FUN_001dc430();
    FUN_00352bb0();
    FUN_00350618();
    (*x9)();
    FUN_00351354(*(uint64_t *)(x16 + 8));
    (*x8_00)();
    FUN_00310e20();
    v1 = FUN_003505f4();
    FUN_0034df34(v1,x20);
    (*x8_01)();
    FUN_00357af8();
    FUN_0035060c();
    (*x8_02)();
  }
  av3 = FUN_00352980();
  FUN_0008e500(av3,(0u /* hi: unspecified */),is00000008);
  return 0;
}


/* FUN_00277d80 @ 0x00277d80  (est. vspace_op_00277d80)
 * Ghidra: void vspace_op_00277d80(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00277d80(void)
{
    uint32_t v1;
  
  FUN_0034d1b0();
  FUN_00310e08();
  v1 = FUN_001e3048();
  if ((v1 & 1) != 0) {
    return 0;
  }
  FUN_0034d1b0();
  FUN_0031b71c();
  FUN_0035a7e8();
  vspace_op_00277de0();
  return 0;
}


/* FUN_00277de0 @ 0x00277de0  (est. vspace_op_00277de0)
 * Ghidra: void vspace_op_00277de0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00277de0(void)
{
    uint64_t v1;
    int i2;
    int64_t l3;
    uint64_t v4;
    uint64_t v5;
    int64_t l6;
    uint64_t v7;
    uint64_t v8;
    int64_t l9;
    int64_t x8;
    int64_t x8_00;
    uint64_t x8_01;
    int64_t x8_02;
    uint64_t (*x8_03)();;
    uint64_t (*x8_04)();;
    uint64_t (*x8_05)();;
    uint64_t (*x8_06)();;
    uint64_t (*x8_07)();;
    uint64_t (*x8_08)();;
    uint64_t (*x9)();;
    int64_t x16;
    int64_t x16_00;
    int64_t x16_01;
    uint64_t * x20;
    int64_t x21;
    uint64_t (*fn10)();;
    uint64_t (*fn11)();;
    uint64_t x26;
    int64_t x27;
    uint64_t x30;
    uint64_t av12;
    uint64_t loc40;
    uint64_t us30;
    uint64_t loc28;
  
  av12 = FUN_0008e518();
  l3 = av12;
  v8 = *(uint64_t *)((0u /* hi: unspecified */) + 0x10);
  v1 = *(uint64_t *)((0u /* hi: unspecified */) + 0x18);
  FUN_0035256c(0xff);
  FUN_00310e08();
  FUN_0034e130();
  v4 = FUN_00319218();
  FUN_0034ab20();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034a2ac();
  v5 = FUN_0034b0b4();
  FUN_003722e4(v5,v8,v8);
  FUN_00348cd0();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_00348bd8();
  (*DAT_00658c00)();
  FUN_0034ac50();
  FUN_0007c028();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_00348a9c();
  (*DAT_00658c00)();
  FUN_0034ae94();
  (*DAT_00658c00)();
  FUN_00350464();
  FUN_00349080();
  (*DAT_00658c00)(*(uint64_t *)(x8_02 + 0x40));
  FUN_003493c4();
  FUN_0034c2f8();
  (*DAT_00658c00)();
  FUN_0034b87c();
  av12 = vspace_op_0027b8c0(); /* dropped 3 leftover-register arg(s) */
  l9 = (0u /* hi: unspecified */);
  l6 = av12;
  if (l6 == l9) {
    FUN_003505e8(*(uint64_t *)(x16_01 + 0x10));
    (*x8_03)();
    FUN_00350530();
    av12 = FUN_00310d80();
    FUN_00351f88(av12,(0u /* hi: unspecified */),av12);
    FUN_001de698();
  }
  else {
    FUN_00358b24(l6);
    FUN_001dc430();
    av12 = FUN_00351360(*(uint64_t *)(x16_00 + 0x10));
    (*x8_04)(av12,(0u /* hi: unspecified */),v8);
    fn10 = *(uint64_t (**)())(x16_01 + 8);
    FUN_003507d4();
    (*fn10)();
    FUN_00350e64(x8_01);
    FUN_0019afd4();
    FUN_003516e4(*(uint64_t *)(x16_00 + 8));
    (*x8_05)();
    if (SBORROW8(l9,1)) {
      fn10 = ((uint64_t (*)())(uintptr_t)0x278290);
      (*fn10)();
    }
    FUN_00358b24(l9 + -1);
    FUN_001dc430();
    (*x8_04)();
    FUN_003507d4();
    v5 = (*fn10)();
    FUN_00353f50(v5,l3 + *(int *)(x21 + 0x24));
    FUN_00351dcc();
    FUN_0019b25c();
    FUN_003516e4();
    (*x8_05)();
    FUN_0035166c(v1);
    FUN_003518ac(x8_01,loc28);
    v7 = (*x8_06)();
    if ((v7 & 1) == 0) {
      FUN_00347d60();
      FUN_001afe4c();
    }
    fn11 = *(uint64_t (**)())(x16_00 + 0x20);
    v5 = FUN_003537f0();
    (*fn11)(v5,x8_01,v8);
    (*fn11)(l3 + *(int *)(x27 + 0x30),loc28,v8);
    FUN_00351990();
    av12 = FUN_0007c1c4();
    (*x9)(av12,(0u /* hi: unspecified */),x27);
    i2 = *(int *)(x27 + 0x30);
    av12 = FUN_000b43d0();
    (*fn11)(av12,(0u /* hi: unspecified */),v8);
    (*x8_05)(us30 + i2,v8);
    av12 = FUN_0007c1c4(*(uint64_t *)(x16 + 0x20));
    (*x8_07)(av12,(0u /* hi: unspecified */),x27);
    (*fn11)(loc40 + *(int *)(x21 + 0x24),us30 + *(int *)(x27 + 0x30),v8);
    FUN_00352498();
    (*x8_05)();
    if (SBORROW8(l9,l6)) {
      fn10 = ((uint64_t (*)())(uintptr_t)0x2782a4);
      (*fn10)();
    }
    if (l9 - l6 == 1) {
      FUN_00358b24(x26,l6);
      FUN_001dc430();
      av12 = FUN_00351ec0();
      v7 = FUN_00206770(av12,(0u /* hi: unspecified */),v8,v1);
      FUN_0006b6f4();
      (*fn10)();
      if ((v7 & 1) != 0) {
        FUN_003508a8();
        (*fn10)();
        v8 = 0;
        goto LAB_00278274;
      }
    }
    FUN_00358720();
    av12 = FUN_00350c80();
    (*x8_08)(av12,(0u /* hi: unspecified */),x21);
    FUN_00350530();
    FUN_00310d80();
    v8 = FUN_00349204();
    FUN_00376820(v8,v4);
    FUN_0034cf74(l6);
    FUN_001dc754();
  }
  v8 = 1;
LAB_00278274:
  FUN_0008e500(v8,x30);
  return 0;
}


/* FUN_002782a4 @ 0x002782a4  (est. vspace_op_002782a4)
 * Ghidra: void vspace_op_002782a4(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_002782a4(void)
{
    int i1;
    int64_t l2;
    int64_t l3;
    uint64_t * p4;
    uint32_t v5;
    uint64_t v6;
    int64_t l7;
    int64_t l8;
    uint64_t v9;
    uint64_t v10;
    int64_t l11;
    int64_t l12;
    uint64_t v13;
    int64_t x8;
    int64_t x8_00;
    int64_t x8_01;
    uint64_t (*x8_02)();;
    uint64_t (*x8_03)();;
    int64_t x8_04;
    uint64_t (*x8_05)();;
    uint64_t (*x8_06)();;
    uint64_t x8_07;
    uint64_t (*x8_08)();;
    int64_t x8_09;
    int64_t x8_10;
    uint64_t (*x8_11)();;
    int64_t x8_12;
    uint64_t (*x8_13)();;
    uint64_t (*x8_14)();;
    uint64_t (*x8_15)();;
    int64_t x8_16;
    uint64_t (*x8_17)();;
    uint64_t (*x8_18)();;
    uint64_t (*x8_19)();;
    uint64_t (*x9)();;
    uint64_t (*x9_00)();;
    uint64_t (*x9_01)();;
    uint64_t * x16;
    int64_t x16_00;
    int64_t x16_01;
    uint64_t * x20;
    uint64_t v14;
    int64_t x22;
    uint64_t (*fn15)();;
    uint64_t (*fn16)();;
    uint64_t (*fn17)();;
    uint64_t x30;
    uint64_t av18;
    uint64_t is00000050;
    uint64_t is00000058;
    uint64_t (*loc128)();;
    uint64_t (*loc110)();;
    uint64_t locf8;
    int64_t loce8;
    uint64_t loca8;
    uint64_t loca0;
    uint64_t loc90;
    int64_t loc80;
    uint64_t loc50;
    int64_t loc48;
    int64_t loc40;
    uint64_t * loc38;
  
  FUN_0034d1b0();
  FUN_00310e08();
  v6 = FUN_001e3048();
  if ((v6 & 1) != 0) {
    return 0;
  }
  FUN_0034d1b0();
  FUN_0031b71c();
  FUN_0035a7e8();
  av18 = FUN_0008e518();
  l7 = av18;
  v13 = *(uint64_t *)((0u /* hi: unspecified */) + 0x10);
  is00000058 = x30;
  FUN_003510a0(0xff);
  l8 = FUN_00310e08();
  FUN_00350920();
  FUN_0031d8b0();
  FUN_00349c44(STK);
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_00350428();
  v9 = FUN_0034c754();
  v9 = FUN_00319218(v9,l8);
  FUN_0034ab20();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b250();
  v10 = FUN_0034b0b4();
  l11 = FUN_003722e4(v10,v13,v13);
  FUN_000a6f88();
  loc38 = x16;
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_003490d0();
  (*DAT_00658c00)();
  FUN_0034c2b4();
  FUN_003499c8();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_00348a34();
  (*DAT_00658c00)();
  FUN_0034a1c8();
  (*DAT_00658c00)();
  FUN_0034a9c0();
  (*DAT_00658c00)();
  FUN_0034aadc();
  (*DAT_00658c00)();
  FUN_0034b640();
  (*DAT_00658c00)();
  FUN_0034aac4();
  (*DAT_00658c00)();
  FUN_0034ae44();
  (*DAT_00658c00)();
  FUN_00349f24();
  (*DAT_00658c00)();
  FUN_0034b758();
  FUN_0034a688();
  (*DAT_00658c00)(*(uint64_t *)(x8_01 + 0x40));
  FUN_003493c4();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_00350434();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_00350434();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_0034a9e8();
  (*DAT_00658c00)();
  FUN_0034a1b0();
  (*DAT_00658c00)();
  FUN_00350434();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_0034a4e0();
  (*DAT_00658c00)();
  FUN_0034a510();
  (*DAT_00658c00)();
  FUN_0034b3d8();
  v10 = *x20;
  av18 = FUN_00353bb8();
  av18 = vspace_op_0027b8c0(); /* dropped 3 leftover-register arg(s) */
  l12 = av18;
  if (l12 == (0u /* hi: unspecified */)) goto LAB_00278d7c;
  loc48 = (0u /* hi: unspecified */);
  FUN_00350ba8();
  FUN_001dc430();
  fn15 = *(uint64_t (**)())(x16_00 + 0x10);
  loc50 = v10;
  av18 = FUN_003507c8();
  (*fn15)(av18,(0u /* hi: unspecified */),v13);
  FUN_00350b6c(*(uint64_t *)(x16_01 + 8));
  FUN_00355f40();
  (*x8_02)();
  FUN_00353d7c();
  FUN_00351ee0();
  FUN_003512cc(l7);
  v5 = (*x8_03)();
  fn17 = *(uint64_t (**)())(x16_00 + 8U);
  FUN_00350470();
  (*fn17)();
  l2 = loc48 + -1;
  if (SBORROW8(loc48,1)) {
    fn15 = ((uint64_t (*)())(uintptr_t)0x278d98);
    (*fn15)();
  }
  v14 = (uint64_t)(x16_00 + 8U) & 0xffffffffffff | 0x4f8000000000000;
  i1 = *(int *)(l8 + 0x24);
  v10 = FUN_00351f58();
  FUN_001dc430(v10,loc50,l8);
  FUN_00358ee8();
  *(uint64_t (**)())(x8_04 + -0x100) = fn15;
  (*fn15)();
  (*loc110)();
  FUN_00355cb0();
  FUN_0035044c();
  FUN_0034e5fc(l7 + i1);
  v6 = (*x8_05)();
  FUN_00350470();
  v10 = (*fn17)(v14);
  if ((v5 & 1) == 0) {
    if ((v6 & 1) == 0) {
      v13 = FUN_00310d80(0,l8);
      v9 = FUN_0034b5fc();
      v9 = FUN_00376820(v9,v13);
      FUN_00359f60(STK,v13,v9);
      FUN_001a4d84();
      goto LAB_00278d7c;
    }
    FUN_00352c98(STK,v10,l7 + i1);
    FUN_00358ee8();
    fn15 = *(uint64_t (**)())(x8_12 + -0x100);
    (*fn15)();
    FUN_003519b4(STK);
    FUN_001dc430(l2,loc50,l8);
    (*fn15)(loca8,fn17 + *(int *)(l8 + 0x24),v13);
    FUN_00350944();
    (*loc110)();
    FUN_00353dfc();
    FUN_00310e20();
    FUN_0034eef8();
    FUN_0034cfd4();
    v6 = (*x8_13)();
    if ((v6 & 1) == 0) goto LAB_00278d98;
    fn16 = *(uint64_t (**)())(x16_00 + 0x20);
    av18 = FUN_003508f0();
    (*fn16)(av18,(0u /* hi: unspecified */),v13);
    FUN_00359e28();
    FUN_003510f4();
    (*fn16)();
    p4 = loc38;
    FUN_00352a40();
    FUN_00356780();
    FUN_003511c0();
    (*x9_00)();
    i1 = *(int *)(l11 + 0x30);
    FUN_00353dac(STK);
    FUN_00351494();
    (*fn16)();
    (*fn17)(fn15 + i1,v13);
    FUN_003511c0(p4[4],fn15);
    (*x8_14)();
    (*fn16)(l8 + *(int *)(l8 + 0x24),fn15 + *(int *)(l11 + 0x30),v13);
    FUN_00353cf0();
    (*fn17)();
    FUN_0035748c(&loc40);
    av18 = FUN_00350bf0();
    fn15 = x8_15;
LAB_00278cf4:
    (*fn15)(av18,(0u /* hi: unspecified */),l8);
    FUN_00350500();
    FUN_00310d80();
    v13 = FUN_00349204();
  }
  else {
    if ((v6 & 1) == 0) {
      v10 = FUN_003526b8(STK,l12);
      FUN_001dc430(v10,loc50,l8);
      FUN_00350560();
      FUN_00358ee8();
      fn15 = *(uint64_t (**)())(x8_16 + -0x100);
      (*fn15)();
      FUN_00350494();
      (*loc110)();
      (*fn15)(loca0,l7,v13);
      FUN_00353dfc();
      FUN_00310e20();
      FUN_0034c8b8();
      FUN_0034cfd4();
      v6 = (*x8_17)();
      p4 = loc38;
      if ((v6 & 1) == 0) goto LAB_00278d98;
      fn16 = *(uint64_t (**)())(x16_00 + 0x20);
      FUN_0034fec0();
      (*fn16)();
      FUN_00359e40();
      FUN_00350b84();
      (*fn16)();
      FUN_00352a40();
      FUN_00356780();
      FUN_003513d8();
      (*x9_01)();
      i1 = *(int *)(l11 + 0x30);
      av18 = FUN_000b43d0();
      (*fn16)(av18,(0u /* hi: unspecified */),v13);
      (*fn17)(fn15 + i1,v13);
      FUN_003513d8(p4[4],fn15);
      (*x8_18)();
      (*fn16)(loce8 + *(int *)(l8 + 0x24),fn15 + *(int *)(l11 + 0x30),v13);
      FUN_00353cf0();
      (*fn17)();
      FUN_0035748c(&loc40);
      av18 = FUN_00100efc();
      fn15 = x8_19;
      goto LAB_00278cf4;
    }
    v9 = FUN_00357338(STK);
    FUN_001dc430(v9,loc50,l8);
    FUN_00350eec();
    (*loc128)();
    FUN_0006b6f4();
    (*loc110)();
    (*loc128)(loc90,l7,v13);
    FUN_00353dfc();
    FUN_00310e20();
    FUN_0034d3a4();
    FUN_0034cfd4();
    v6 = (*x8_06)();
    l3 = loc40;
    if ((v6 & 1) == 0) {
LAB_00278d98:
      FUN_00347d60();
      FUN_001afe4c();
    }
    fn16 = *(uint64_t (**)())(x16_00 + 0x20);
    av18 = FUN_003507c8();
    (*fn16)(av18,(0u /* hi: unspecified */),v13);
    FUN_00350b84(l3 + *(int *)(l11 + 0x30));
    (*fn16)();
    FUN_00353a00();
    FUN_0034c9d8();
    (*x9)();
    i1 = *(int *)(l11 + 0x30);
    FUN_00351300(loc80);
    (*fn16)();
    (*fn17)(x22 + i1,v13);
    FUN_0034c9d8(loc38[4]);
    loc38 = loc38 + 4;
    (*x8_08)();
    FUN_00358924((int64_t)*(int *)(l11 + 0x30),loc80 + *(int *)(l8 + 0x24));
    (*fn16)();
    FUN_00350618();
    (*fn17)();
    v9 = FUN_0035a718();
    FUN_00354b50(STK,v9,l7 + x8_09);
    FUN_00358ee8();
    fn15 = *(uint64_t (**)())(x8_10 + -0x100);
    FUN_00358bcc();
    (*fn15)();
    FUN_003519b4(STK);
    v9 = FUN_001dc430(l2,loc50,l8);
    av18 = FUN_00352b8c(&loc50,v9,v14 + (int64_t)*(int *)(l8 + 0x24));
    (*fn15)(av18,(0u /* hi: unspecified */),v13);
    FUN_00350a70();
    (*loc110)();
    FUN_0034f014();
    FUN_00350af4();
    FUN_0034cfd4();
    v6 = (*x8_11)();
    if ((v6 & 1) == 0) goto LAB_00278d98;
    FUN_00351118(loc40);
    (*fn16)();
    FUN_00350b84(loc40 + *(int *)(l11 + 0x30));
    (*fn16)();
    FUN_0034c9d8();
    (*x9)();
    i1 = *(int *)(l11 + 0x30);
    FUN_00354b50(STK);
    FUN_00351300();
    (*fn16)();
    (*fn17)(x22 + i1,v13);
    FUN_0034c9d8();
    (*x8_08)();
    FUN_00358924((int64_t)*(int *)(l11 + 0x30),
                 (x8_07 & 0xffffffffffff | 0xe3ba000000000000) +
                 (int64_t)*(int *)(l8 + 0x24));
    (*fn16)();
    FUN_00350618();
    (*fn17)();
    FUN_00352098(STK);
    FUN_00350624(loc80);
    vspace_op_0027bb78();
    FUN_003504e8();
    FUN_00310d80();
    v13 = FUN_0034b1c0();
    v9 = locf8;
  }
  FUN_00376820(v13,v9);
  FUN_003515fc(l12,loc48);
  FUN_00359f60();
  FUN_001dc754();
LAB_00278d7c:
  FUN_0008e500(is00000058);
  return 0;
}


/* FUN_00278dac @ 0x00278dac  (est. vspace_op_00278dac)
 * Ghidra: void vspace_op_00278dac(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00278dac(void)
{
    uint64_t av1;
  
  FUN_003504d0();
  FUN_0034d024();
  av1 = FUN_00310e08();
  FUN_0007c1c4(av1,(0u /* hi: unspecified */),av1,0x66d4d0);
  FUN_001defb0();
  return 0;
}


/* FUN_00278e54 @ 0x00278e54  (est. vspace_op_00278e54)
 * Ghidra: void vspace_op_00278e54(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00278e54(void)
{
    uint8_t zr;
    uint64_t (*fn1)();;
    uint64_t v2;
    uint64_t x1;
    uint64_t x1_00;
    uint64_t ix4;
    uint64_t ix5;
    int64_t x8;
    uint64_t (*x8_00)();;
    uint64_t (*x8_01)();;
    uint64_t (*x8_02)();;
    uint64_t (*x9)();;
    int64_t x16;
    int64_t x16_00;
    uint64_t av3;
    uint64_t is00000018;
  
  FUN_0008e518();
  FUN_00353274();
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_00348f38();
  FUN_00350a64();
  FUN_0034d464();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b05c();
  FUN_00349830();
  FUN_0035169c();
  FUN_00377824();
  FUN_00348ce8();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034aee4();
  FUN_0034c3c4();
  FUN_0034ca28();
  FUN_00377bec();
  FUN_00357ac0();
  FUN_0027743c();
  FUN_00352680(ix5);
  FUN_00351324();
  (*x9)();
  FUN_0034b278();
  FUN_003509d4();
  FUN_00377bec();
  fn1 = (uint64_t (*)())FUN_000a68f4();
  while( true ) {
    FUN_00358e34();
    FUN_003515cc();
    (*fn1)();
    FUN_0034b2a8();
    if ((bool)zr) break;
    FUN_000dbd0c(*(uint64_t *)(x16 + 0x20));
    (*x8_00)();
    av3 = FUN_00350500();
    FUN_0031d8c8(av3,(0u /* hi: unspecified */),x1_00);
    vspace_op_0027905c(0 /* leftover-register arg */, 0 /* leftover-register arg */, 0 /* leftover-register arg */, 0 /* leftover-register arg */, 0 /* leftover-register arg */); /* padded 5 leftover-register arg(s) */
    FUN_00350518(*(uint64_t *)(x16 + 8));
    (*x8_01)();
  }
  FUN_0034ece8(x1,ix4);
  ((uint64_t (*)())(*((void **)(x16_00 + 8))))();
  FUN_0035313c();
  FUN_00350944();
  (*x8_02)();
  v2 = FUN_0035a560();
  FUN_0008e500(v2,is00000018);
  return 0;
}


/* FUN_0027905c @ 0x0027905c  (est. vspace_op_0027905c)
 * Ghidra: void vspace_op_0027905c(uint64_t arg1,uint64_t arg2,int64_t arg3,uint64_t arg4,                  uint64_t arg5)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027905c(uint64_t arg1,uint64_t arg2,int64_t arg3,uint64_t arg4,
                 uint64_t arg5)
{
    int i1;
    uint64_t v2;
    uint64_t v3;
    int64_t x8;
    int64_t x8_00;
    uint64_t (*x8_01)();;
    uint64_t (*x8_02)();;
    uint64_t (*x8_03)();;
    uint64_t (*x9)();;
    uint64_t (*x9_00)();;
    uint64_t (*x9_01)();;
    int64_t x16;
    int64_t x16_00;
    int64_t x19;
    uint64_t (*fn4)();;
    uint64_t v5;
    int64_t x22;
    uint64_t (*fn6)();;
    uint64_t v7;
    int64_t x28;
    uint64_t av8;
    uint64_t is00000018;
    uint64_t loc30;
    uint64_t loc28;
  
  FUN_0008e518();
  FUN_00350a28();
  v5 = *(uint64_t *)(arg3 + 0x10);
  v2 = FUN_0034b0b4();
  FUN_00357bec(v2,v5);
  FUN_00348ce8();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_00348a9c();
  (*DAT_00658c00)();
  FUN_0034b4c0();
  FUN_00349734();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_00348f50();
  v7 = *(uint64_t *)(x19 + 0x18);
  FUN_003502e8();
  FUN_00310e08();
  FUN_00348e18();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034aab0();
  FUN_00319658(arg5);
  v2 = FUN_003503a0();
  (*x9)(v2,arg4,arg5);
  FUN_0035166c(v7);
  FUN_003507c8();
  FUN_00350e94();
  v3 = (*x8_01)();
  if ((v3 & 1) != 0) {
    FUN_00352474();
    av8 = FUN_00350c38();
    (*x9_00)(av8,(0u /* hi: unspecified */),v5);
    fn6 = *(uint64_t (**)())(x16_00 + 0x20);
    FUN_00350998(x28 + *(int *)(x22 + 0x30));
    (*fn6)();
    FUN_0034d384();
    FUN_00351df0();
    (*x9_01)();
    i1 = *(int *)(x22 + 0x30);
    av8 = FUN_003508f0();
    (*fn6)(av8,(0u /* hi: unspecified */),v5);
    fn4 = *(uint64_t (**)())(x16_00 + 8);
    (*fn4)(loc28 + i1,v5);
    FUN_00351274(*(uint64_t *)(x16 + 0x20));
    (*x8_02)();
    av8 = FUN_00357fc4((int64_t)*(int *)(x22 + 0x30));
    (*fn6)(av8,(0u /* hi: unspecified */),v5);
    FUN_003504f4();
    (*fn4)();
    av8 = FUN_00350530();
    v2 = FUN_0031b71c(av8,(0u /* hi: unspecified */),v7);
    vspace_op_00277de0(); /* dropped 2 leftover-register arg(s) */
    v2 = FUN_0034e33c();
    (*x8_03)(v2,x19);
    v2 = FUN_00353034();
    FUN_0008e500(v2,is00000018);
    return 0;
  }
  FUN_00347d60();
  FUN_001afe4c();
}


/* FUN_00279558 @ 0x00279558  (est. vspace_op_00279558)
 * Ghidra: void vspace_op_00279558(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279558(void)
{
  FUN_00347d60();
  FUN_001afe4c();
}


/* FUN_00279568 @ 0x00279568  (est. vspace_op_00279568)
 * Ghidra: void vspace_op_00279568(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279568(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
    uint64_t * p1;
    uint64_t v2;
    int i3;
    int64_t l4;
    uint64_t v5;
    uint64_t v6;
    uint64_t v7;
    uint64_t v8;
    uint64_t x1;
    uint64_t x1_00;
    uint64_t v9;
    int64_t x8;
    int64_t x8_00;
    uint64_t x8_01;
    int64_t x8_02;
    int64_t x8_03;
    uint64_t (*x8_04)();;
    uint64_t (*x8_05)();;
    uint64_t (*x8_06)();;
    uint64_t (*x8_07)();;
    uint64_t (*x8_08)();;
    uint64_t (*x8_09)();;
    int64_t x8_10;
    uint64_t (*x8_11)();;
    uint64_t (*x8_12)();;
    uint64_t (*fn10)();;
    int64_t x9;
    uint64_t (*x9_00)();;
    int64_t x16;
    int64_t x16_00;
    int64_t x19;
    uint64_t v11;
    uint64_t (*fn12)();;
    uint64_t x22;
    int64_t x26;
    uint64_t (*fn13)();;
    uint64_t x30;
    uint64_t av14;
    uint64_t av15;
    int64_t loc60;
    int64_t loc58;
    int64_t loc20;
    int64_t loc18;
    uint8_t st8[8];
  
  FUN_0008e518();
  v8 = arg4;
  FUN_00354de8();
  FUN_0034b0b4();
  l4 = FUN_00359000();
  FUN_000a6f88();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_003493c4();
  FUN_0034cf34();
  (*DAT_00658c00)();
  FUN_0034bc6c();
  FUN_003502e8();
  FUN_00310e08();
  FUN_00348e60();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_00348a34();
  (*DAT_00658c00)();
  FUN_0034baa8();
  (*DAT_00658c00)();
  FUN_0034ac00();
  (*DAT_00658c00)();
  FUN_0034ac28();
  (*DAT_00658c00)();
  FUN_00350464();
  FUN_00349080();
  (*DAT_00658c00)(*(uint64_t *)(x8_02 + 0x40));
  FUN_003493c4();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_0034a4f8();
  (*DAT_00658c00)();
  FUN_0034ac14();
  (*DAT_00658c00)();
  FUN_0034a400();
  (*DAT_00658c00)();
  FUN_0034b758();
  av14 = FUN_0035072c();
  FUN_00356a08(av14,(0u /* hi: unspecified */),1);
  av14 = vspace_op_0027b8c0();
  if (av14 == (0u /* hi: unspecified */)) {
    ((uint64_t (*)())(*((void **)(x16_00 + 0x10))))();
    FUN_003514dc();
    v5 = FUN_00277474();
  }
  else {
    FUN_00351e08();
    FUN_003508e4();
    v5 = FUN_001a0414();
    FUN_00353130();
    fn10 = *(uint64_t (**)())(x8_03 + 0x10);
    v9 = arg3;
    (*fn10)();
    FUN_0007c1c4();
    FUN_00353a6c();
    av14 = FUN_001dc554();
    if (v9 != v8 >> 1) {
      FUN_00353bac();
      FUN_00357068();
      p1 = (uint64_t *)(x9 + 8);
      FUN_00352b80();
      v7 = x1;
      v11 = v9;
      do {
        FUN_001a9ac8(x8_01,v11,v7,(0u /* hi: unspecified */),v9,v8,x26);
        v2 = v11 + 1;
        if (SCARRY8(v11,1)) {
          fn10 = ((uint64_t (*)())(uintptr_t)0x279c5c);
          (*fn10)();
        }
        FUN_00355224();
        av15 = FUN_00350af4();
        (*x8_04)(av15,(0u /* hi: unspecified */),x26);
        FUN_0034c9d8();
        (*fn10)();
        av15 = FUN_003509bc();
        (*fn10)(av15,(0u /* hi: unspecified */),arg3);
        FUN_00310e20(arg4);
        FUN_0034d3a4();
        FUN_0035130c();
        v6 = (*x8_05)();
        if ((v6 & 1) == 0) goto LAB_00279c48;
        fn12 = (uint64_t (*)())*p1;
        FUN_00350560();
        (*fn12)();
        fn13 = *(uint64_t (**)())(x9 + 0x20);
        av15 = FUN_000dbd0c();
        (*fn13)(av15,(0u /* hi: unspecified */),arg3);
        FUN_00077894(loc60 + *(int *)(l4 + 0x30));
        (*fn13)();
        FUN_00350d24();
        av15 = FUN_00351160();
        (*x8_06)(av15,(0u /* hi: unspecified */),l4);
        i3 = *(int *)(l4 + 0x30);
        FUN_00077894(loc20);
        (*fn13)();
        (*fn12)(loc58 + i3,arg3);
        FUN_003510d0(STK);
        av15 = FUN_00351160();
        (*x8_07)(av15,(0u /* hi: unspecified */),l4);
        (*fn13)(loc20 + *(int *)(x26 + 0x24),loc58 + *(int *)(l4 + 0x30),arg3);
        FUN_00100efc();
        (*fn12)();
        v6 = FUN_001e3048(x26);
        if ((v6 & 1) == 0) {
          FUN_003508e4();
          FUN_00310d34();
          FUN_00357aa8();
          FUN_001a1854(loc20);
          v7 = FUN_0035460c();
        }
        else {
          FUN_0035460c();
          v7 = ((uint64_t (*)())(*(p1)))(loc20,x26);
        }
        FUN_00353f2c(v7,loc18 + *(int *)(x26 + 0x24));
        (*fn10)();
        FUN_00351648(*p1);
        (*x8_08)();
        v11 = v11 + 1;
        v7 = x1_00;
      } while (v2 != v8 >> 1);
    }
    FUN_0036b118(av14);
    FUN_00358ad4();
    FUN_0034c9d8();
    v7 = (*fn10)();
    av14 = FUN_00352b8c(STK,v7,x19 + *(int *)(x26 + 0x24));
    (*fn10)(av14,(0u /* hi: unspecified */),arg3);
    FUN_00310e20(arg4);
    FUN_0034d3a4();
    FUN_00350e94();
    v8 = (*x8_09)();
    if ((v8 & 1) == 0) {
LAB_00279c48:
      FUN_00347d60();
      FUN_001afe4c();
    }
    FUN_003519b4(STK);
    fn13 = *(uint64_t (**)())(x8_10 + 8);
    FUN_00350560();
    (*fn13)();
    fn12 = *(uint64_t (**)())(arg4 + 0x20);
    FUN_00356924();
    FUN_00350998();
    (*fn12)();
    FUN_00077894(fn10 + *(int *)(l4 + 0x30));
    (*fn12)();
    FUN_00351c4c();
    av14 = FUN_003509bc();
    (*x9_00)(av14,(0u /* hi: unspecified */),l4);
    i3 = *(int *)(l4 + 0x30);
    av14 = FUN_003504ac();
    (*fn12)(av14,(0u /* hi: unspecified */),arg3);
    (*fn13)(loc58 + i3,arg3);
    av14 = FUN_003509bc(*(uint64_t *)(x16 + 0x20));
    (*x8_11)(av14,(0u /* hi: unspecified */),l4);
    av14 = FUN_00359c0c((int64_t)*(int *)(l4 + 0x30));
    FUN_00353130(av14,(0u /* hi: unspecified */),arg3);
    (*fn12)();
    FUN_00100efc();
    (*fn13)();
    v8 = FUN_001e3048(x26);
    if ((v8 & 1) == 0) {
      FUN_00350720();
      FUN_00310d34();
      FUN_00357aa8();
      FUN_001a1854(x22);
    }
    else {
      FUN_00350bc0(st8);
      FUN_003509e0();
      (*x8_12)();
    }
    v5 = FUN_00277ba8(v5,arg3,arg4);
  }
  FUN_0008e500(v5,x30);
  return 0;
}


/* FUN_00279c5c @ 0x00279c5c  (est. vspace_op_00279c5c)
 * Ghidra: void vspace_op_00279c5c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279c5c(void)
{
    uint64_t v1;
    uint64_t * x20;
  
  FUN_00359350();
  v1 = vspace_op_00279c7c();
  *x20 = v1;
  return 0;
}


/* FUN_00279c60 @ 0x00279c60  (est. vspace_op_00279c60)
 * Ghidra: void vspace_op_00279c60(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279c60(void)
{
    uint64_t v1;
    uint64_t * x20;
  
  FUN_00359350();
  v1 = vspace_op_00279c7c();
  *x20 = v1;
  return 0;
}


/* FUN_00279c7c @ 0x00279c7c  (est. vspace_op_00279c7c)
 * Ghidra: void vspace_op_00279c7c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279c7c(void)
{
  FUN_003504d0();
  vspace_op_00279e90();
  FUN_00354924();
  FUN_0036b118();
  FUN_0036b118();
  return 0;
}


/* FUN_00279cbc @ 0x00279cbc  (est. vspace_op_00279cbc)
 * Ghidra: void vspace_op_00279cbc(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279cbc(void)
{
    uint64_t v1;
    uint64_t * x20;
  
  FUN_00359350();
  v1 = FUN_0020083c();
  *x20 = v1;
  return 0;
}


/* FUN_00279cc0 @ 0x00279cc0  (est. vspace_op_00279cc0)
 * Ghidra: void vspace_op_00279cc0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279cc0(void)
{
    uint64_t v1;
    uint64_t * x20;
  
  FUN_00359350();
  v1 = FUN_0020083c();
  *x20 = v1;
  return 0;
}


/* FUN_00279cdc @ 0x00279cdc  (est. vspace_op_00279cdc)
 * Ghidra: void vspace_op_00279cdc(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279cdc(void)
{
    uint64_t v1;
    uint64_t * x20;
  
  FUN_00359350();
  v1 = vspace_op_00279cfc();
  *x20 = v1;
  return 0;
}


/* FUN_00279ce0 @ 0x00279ce0  (est. vspace_op_00279ce0)
 * Ghidra: void vspace_op_00279ce0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279ce0(void)
{
    uint64_t v1;
    uint64_t * x20;
  
  FUN_00359350();
  v1 = vspace_op_00279cfc();
  *x20 = v1;
  return 0;
}


/* FUN_00279cfc @ 0x00279cfc  (est. vspace_op_00279cfc)
 * Ghidra: uint64_t vspace_op_00279cfc(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279cfc(void)
{
    uint64_t v1;
    uint64_t v2;
    uint64_t x1;
  
  FUN_00349fcc();
  FUN_0036b270(x1);
  FUN_0036b270();
  FUN_0034b788();
  vspace_op_00279c7c();
  FUN_0008412c();
  v1 = FUN_0020083c();
  FUN_0036b118();
  FUN_0008e388();
  FUN_0035053c();
  v2 = vspace_op_0027ad9c(0 /* leftover-register arg */, 0 /* leftover-register arg */); /* padded 2 leftover-register arg(s) */
  FUN_0036b118(v1);
  return v2;
}


/* FUN_00279d78 @ 0x00279d78  (est. vspace_op_00279d78)
 * Ghidra: void vspace_op_00279d78(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279d78(void)
{
    uint64_t v1;
    uint64_t v2;
    int64_t x8;
    uint64_t (*x8_00)();;
    uint64_t x16;
    int64_t x19;
    uint64_t x30;
  
  FUN_0008e518();
  FUN_00352758();
  FUN_0034d3e4();
  FUN_00310e08();
  FUN_0034b57c();
  FUN_00351408(x16);
  (*DAT_00658c00)();
  v1 = FUN_0034bab8();
  if (*(int64_t *)(x19 + 0x10) != 0) {
    FUN_0036b270();
    do {
      FUN_0007c1c4();
      FUN_00350bfc();
      FUN_001fea40();
      FUN_0034d3e4();
      v1 = FUN_0031b71c();
      v2 = FUN_00348a50();
      FUN_00376820(v2,v1);
      FUN_0034887c();
      v2 = FUN_00355958();
      FUN_001e7664(v2,v1);
      FUN_0035084c();
      vspace_op_002782a4();
      FUN_000a6e14(*(uint64_t *)(x8 + 8));
      (*x8_00)();
    } while (*(int64_t *)(x19 + 0x10) != 0);
    v1 = FUN_0036b118();
  }
  FUN_0008e500(v1,x30);
  return 0;
}


/* FUN_00279e90 @ 0x00279e90  (est. vspace_op_00279e90)
 * Ghidra: void vspace_op_00279e90(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_00279e90(void)
{
    int i1;
    uint64_t v2;
    uint64_t v3;
    uint64_t (*fn4)();;
    uint64_t v5;
    uint64_t v6;
    uint64_t v7;
    uint64_t v8;
    int64_t l9;
    int64_t x8;
    int64_t x8_00;
    uint64_t x8_01;
    int64_t x8_02;
    uint64_t x8_03;
    uint64_t (*x8_04)();;
    uint64_t (*x8_05)();;
    uint64_t (*x8_06)();;
    uint64_t (*x8_07)();;
    uint64_t (*x8_08)();;
    uint64_t x8_09;
    uint64_t x10;
    uint64_t v10;
    uint64_t x13;
    uint64_t v11;
    uint64_t * x14;
    uint64_t v12;
    int64_t x16;
    uint64_t * x19;
    uint64_t x21;
    uint64_t (*fn13)();;
    int64_t x22;
    int64_t x25;
    uint64_t (*fn14)();;
    uint64_t (*fn15)();;
    uint64_t x30;
    uint64_t av16;
    int64_t loc118;
    int64_t loc110;
    int64_t loc108;
    int64_t * locc0;
    uint64_t locb8;
    int64_t loc60;
    int64_t loc50;
    int64_t loc48;
    uint8_t st40[8];
    uint8_t loc38[8];
    uint8_t st30[8];
    uint64_t loc28;
    uint64_t loc20;
    int64_t * loc18;
    int64_t loc10;
    uint8_t st8[8];
  
  FUN_0008e518();
  av16 = FUN_00350a10();
  loc60 = (0u /* hi: unspecified */);
  FUN_0034b0b4();
  FUN_00359000();
  FUN_003490b8(st8);
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_003493c4();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_00350464();
  FUN_00355db4();
  FUN_00349080();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_003493c4();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_00350434();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_0034a1b0();
  (*DAT_00658c00)();
  FUN_00350464();
  FUN_0034bec4();
  FUN_00310e08();
  FUN_00348ce8();
  (*DAT_00658c00)(*(uint64_t *)(x8_02 + 0x40));
  FUN_003493c4();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_00350434();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_00349c84();
  (*DAT_00658c00)();
  FUN_0034a4e0();
  (*DAT_00658c00)();
  FUN_0034b3d8();
  FUN_00358864();
  loc48 = av16;
  FUN_0034bec4();
  v2 = FUN_0031b71c();
  v3 = FUN_00348c30();
  fn4 = (uint64_t (*)())FUN_00376820(v3,v2);
  FUN_003518b8();
  v5 = FUN_0019fd10();
  if ((v5 & 1) == 0) {
    loc48 = loc60;
    FUN_003518b8();
    v5 = FUN_0019fd10();
    if ((v5 & 1) == 0) {
      loc10 = FUN_003573c0(loc60);
      loc18 = &loc48;
      FUN_0036b270();
      FUN_0036b270(&loc48);
      loc20 = FUN_001a0414(0);
      locb8 = 0;
      FUN_00353360(x16 + 0x10);
      v10 = x8_03 & 0xffffffffffff | 0xe3ba000000000000;
      v11 = x13 & 0xffffffffffff | 0x4f8000000000000;
      v12 = (uint64_t)x14 & 0xffffffffffff | 0x4f8000000000000;
      v5 = x10;
LAB_0027a170:
      if (0 < *(int64_t *)(loc60 + 0x10)) {
        if ((int64_t)v5 < locc0[2]) {
          FUN_001dc430(x25,v5,locc0,x22);
          FUN_0035460c();
          fn14 = (uint64_t (*)())*x19;
          FUN_0034c064();
          (*fn14)();
          FUN_00354064();
          fn13 = *(uint64_t (**)())fn4;
          FUN_00350630();
          (*fn13)();
          FUN_00357338(STK);
          FUN_001dc430(0,loc60,x22);
          FUN_00352c98(STK);
          FUN_00350ed0();
          (*fn14)();
          FUN_00350af4();
          (*fn13)();
          FUN_0034afa0(x19);
          FUN_003516b4();
          v6 = (*x8_04)();
          fn15 = (uint64_t (*)())*x14;
          FUN_00351274();
          (*fn15)();
          FUN_00350518();
          (*fn15)();
          v7 = locb8;
          v8 = v5;
          if ((v6 & 1) != 0) {
            FUN_00350488();
            FUN_00310d80();
            v2 = FUN_003569cc();
            FUN_001f2104(v2,&loc18);
            v7 = FUN_00358954(v5);
            v8 = x8_01;
          }
          FUN_001dc430(loc50,v7,loc10,x22);
          v5 = v7;
LAB_0027a2cc:
          FUN_00352b98(v5 + 1);
          v5 = v8;
          fn4 = fn15;
          do {
            locc0 = loc18;
            if (loc18[2] <= (int64_t)v5) {
LAB_0027a598:
              FUN_003508e4();
              FUN_00310d34();
              FUN_00358e7c();
              FUN_001a1854(loc50);
              loc60 = loc10;
              goto LAB_0027a170;
            }
            i1 = *(int *)(x22 + 0x24);
            av16 = FUN_00100efc(x25);
            FUN_001dc430(av16,(0u /* hi: unspecified */),x22);
            av16 = FUN_00350470();
            (*fn14)(v10,av16,(0u /* hi: unspecified */),x21);
            FUN_00351360();
            (*fn13)(v11);
            fn4 = (uint64_t (*)())FUN_00310954(x19);
            FUN_003518ac(loc50 + i1,x8_01);
            v7 = (*fn4)();
            FUN_0035145c();
            (*fn15)(v12);
            if ((v7 & 1) == 0) goto LAB_0027a598;
            av16 = FUN_00100efc(x25);
            FUN_001dc430(av16,(0u /* hi: unspecified */),x22);
            (*fn14)(v10,x8_01,x25 + *(int *)(x22 + 0x24),x21);
            FUN_00351360();
            (*fn13)(v11);
            FUN_003518ac(loc50 + i1,x8_01);
            v7 = (*fn4)();
            FUN_0035145c();
            (*fn15)(v12);
            if ((v7 & 1) == 0) goto LAB_0027a3f0;
            v5 = v5 + 1;
          } while( true );
        }
        FUN_00353734();
        loc28 = x8_09;
        FUN_00350488();
        v2 = FUN_00310d80();
        FUN_0034f8bc();
        FUN_00002534();
        v3 = FUN_00349910();
        FUN_00376820(v3,v2);
        FUN_003489a8();
        goto LAB_0027a65c;
      }
      if ((int64_t)v5 < locc0[2]) {
        loc28 = v5;
        FUN_00350488();
        v2 = FUN_00310d80();
        FUN_0034f8bc();
        FUN_00002534();
        v3 = FUN_00349910();
        FUN_00376820(v3,v2);
        FUN_003489a8();
LAB_0027a65c:
        FUN_003513b4(&loc48,&loc28);
        FUN_00270d80();
        FUN_00350488();
        v2 = FUN_00310d34();
        FUN_00350488();
        av16 = FUN_00310df0();
        FUN_0034e3fc(av16,(0u /* hi: unspecified */),av16);
        FUN_001a2128(&loc48,v2);
      }
      FUN_003504a0(loc20);
      l9 = FUN_00277ba8();
      FUN_0036b118(loc60);
      FUN_00359ad4();
      FUN_0036b118();
      loc60 = l9;
    }
    else {
      FUN_00359ad4();
      loc60 = FUN_0036b270();
    }
  }
  else {
    FUN_0036b270(loc60);
  }
  FUN_0008e500(loc60,x30);
  return 0;
LAB_0027a3f0:
  v2 = FUN_00352c98(STK);
  (*fn14)(v2,loc50,x21);
  FUN_00357338(STK);
  av16 = FUN_00100efc();
  v2 = FUN_001dc430(av16,(0u /* hi: unspecified */),x22);
  av16 = FUN_00352d64(STK,v2,v7 + (int64_t)*(int *)(x22 + 0x24));
  (*fn14)(av16,(0u /* hi: unspecified */),x21);
  FUN_00352498();
  (*fn13)();
  FUN_0034f014();
  FUN_00350738();
  FUN_0034d344();
  (*x8_05)();
  v8 = FUN_00358954();
  if ((v8 & 1) == 0) {
    FUN_00347d60();
    FUN_001afe4c();
  }
  FUN_0035145c();
  (*fn13)();
  fn4 = *(uint64_t (**)())(x16 + 0x20);
  av16 = FUN_003508f0();
  (*fn4)(av16,(0u /* hi: unspecified */),x21);
  FUN_00351720(loc118 + *(int *)(loc108 + 0x30));
  (*fn4)();
  FUN_003510d0(st30);
  av16 = FUN_00350a04();
  (*x8_06)(av16,(0u /* hi: unspecified */),loc108);
  i1 = *(int *)(loc108 + 0x30);
  FUN_00359f60();
  av16 = FUN_00351648();
  (*fn4)(av16,(0u /* hi: unspecified */),x21);
  (*fn15)(loc110 + i1,x21);
  FUN_003510d0(loc38);
  av16 = FUN_00350a04();
  (*x8_07)(av16,(0u /* hi: unspecified */),loc108);
  (*fn4)(v7 + (int64_t)*(int *)(x22 + 0x24),loc110 + *(int *)(loc108 + 0x30),
            x21);
  FUN_003507d4();
  (*fn15)();
  FUN_003510d0(st40);
  FUN_000dbe70(loc50);
  (*x8_08)();
  FUN_00350488();
  FUN_00310d80();
  v2 = FUN_003569cc();
  FUN_001f2104(v2,&loc18);
  v8 = v10;
  goto LAB_0027a2cc;
}


/* FUN_0027a6e0 @ 0x0027a6e0  (est. vspace_op_0027a6e0)
 * Ghidra: void vspace_op_0027a6e0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027a6e0(void)
{
    int i1;
    int64_t l2;
    int64_t l3;
    uint64_t v4;
    uint64_t v5;
    uint64_t v6;
    uint64_t v7;
    uint64_t v8;
    int64_t x1;
    int64_t x8;
    int64_t x8_00;
    int64_t x8_01;
    int64_t x8_02;
    int64_t x8_03;
    uint64_t (*x8_04)();;
    uint64_t (*x8_05)();;
    uint64_t (*x8_06)();;
    uint64_t (*x8_07)();;
    uint64_t (*x8_08)();;
    uint64_t (*x8_09)();;
    uint64_t (*x8_10)();;
    uint64_t (*x8_11)();;
    uint64_t (*x8_12)();;
    uint64_t (*fn9)();;
    int64_t x8_13;
    int64_t l10;
    uint64_t (*x9)();;
    uint64_t (*x9_00)();;
    uint64_t (*x9_01)();;
    int64_t x16;
    int64_t x16_00;
    uint64_t (*x19)();;
    uint64_t x21;
    int64_t x22;
    int64_t x24;
    int64_t l11;
    int64_t l12;
    uint64_t x30;
    uint64_t av13;
    uint64_t loca8;
    int64_t loc98;
    uint64_t loc88;
    uint64_t loc70;
    uint64_t loc50;
    uint64_t loc10[2];
  
  FUN_0008e518();
  l2 = FUN_0034b470();
  FUN_0034b0b4();
  l3 = FUN_00359000();
  FUN_000a6f88();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_003493c4();
  FUN_0034d944();
  (*DAT_00658c00)();
  FUN_00350464();
  FUN_00349080();
  (*DAT_00658c00)(*(uint64_t *)(x8_01 + 0x40));
  FUN_0034926c();
  (*DAT_00658c00)();
  FUN_0034a400();
  (*DAT_00658c00)();
  FUN_00350464();
  FUN_00353e94();
  FUN_0034bec4();
  v4 = FUN_00310e08();
  FUN_000a6f88(v4,v4);
  (*DAT_00658c00)(*(uint64_t *)(x8_02 + 0x40));
  FUN_003493c4();
  FUN_0034da38();
  (*DAT_00658c00)();
  FUN_00349f24();
  (*DAT_00658c00)();
  FUN_0034ae94();
  (*DAT_00658c00)();
  FUN_00349c84();
  (*DAT_00658c00)();
  FUN_00350464();
  FUN_0034c754();
  loc10[0] = FUN_001a0414();
  v4 = FUN_00355dc0(*(uint64_t *)(x22 + 0x10));
  if (x8_03 == 0) {
LAB_0027ad7c:
    FUN_003504a0(v4);
    v4 = FUN_00277ba8();
    FUN_0008e500(v4,x30);
    return 0;
  }
  l12 = 0;
  l10 = *(int64_t *)(l2 + 0x10);
  l2 = 0;
LAB_0027a918:
  FUN_00357338(STK);
  FUN_001dc430(l2,x22,x1);
  l2 = l2 + 1;
  FUN_003510d0(loc10);
  FUN_00353098(loc50);
  (*x8_04)();
  for (; l12 < l10; l12 = l12 + 1) {
    av13 = FUN_003509b0(x24);
    v4 = FUN_001dc430(av13,(0u /* hi: unspecified */),x1);
    FUN_003548ac(v4,x24 + *(int *)(x1 + 0x24));
    (*x9)();
    FUN_00354bbc();
    FUN_000dbd0c();
    (*x8_05)();
    FUN_0034f014();
    FUN_0034d344(loc88,loc50);
    v5 = (*x8_06)();
    FUN_00100efc(*(uint64_t *)(x16 + 8));
    (*x8_07)();
    if ((v5 & 1) == 0) break;
  }
  do {
    if (l10 <= l12) break;
    av13 = FUN_003509b0(x24);
    FUN_001dc430(av13,(0u /* hi: unspecified */),x1);
    FUN_003510a0(loc88);
    (*x9_00)();
    FUN_000dbd0c(*(uint64_t *)(x16_00 + 8));
    (*x8_08)();
    v5 = loc50 + (int64_t)*(int *)(x1 + 0x24);
    FUN_0035044c(x19);
    FUN_0035053c(loc88,v5);
    v6 = (*x8_09)();
    FUN_003509bc();
    (*x9_01)();
    fn9 = x8_08;
    if ((v6 & 1) == 0) goto LAB_0027ad58;
    FUN_00358dc4();
    FUN_00351178(l12);
    FUN_001dc430();
    FUN_00310b08(x19);
    FUN_0034ce68();
    FUN_0035053c();
    v7 = (*x8_10)();
    v8 = loc50;
    if ((v7 & 1) == 0) {
      FUN_00350ab8(v7,loc50);
      FUN_0034d344();
      v7 = (*x8_09)();
      v8 = v5;
      if ((v7 & 1) == 0) {
        v8 = v6;
      }
    }
    (*x9_00)(loc70,v8,x21);
    l11 = (int64_t)*(int *)(x1 + 0x24);
    FUN_0034d344(v5,v6 + l11);
    v8 = (*x8_09)();
    if ((v8 & 1) == 0) {
      FUN_0034d344(loc50,v6 + l11);
      v8 = (*x8_10)();
      if ((v8 & 1) != 0) {
        FUN_000a6e14();
        (*x8_08)();
        FUN_003530f4();
        goto LAB_0027ab88;
      }
      FUN_00358f00(loca8,v6 + l11);
      (*x9_00)();
      FUN_000a6e14();
      (*x8_08)();
    }
    else {
      FUN_000a6e14();
      (*x8_08)();
      FUN_00352498();
LAB_0027ab88:
      FUN_00358f00();
      (*x9_00)();
    }
    x19 = *(uint64_t (**)())(x16 + 0x20);
    (*x19)(x8_00,loc70,x21);
    FUN_003510c4(x8_00 + *(int *)(l3 + 0x30));
    (*x19)();
    FUN_003510d0(STK);
    av13 = FUN_0009e234();
    (*x8_11)(av13,(0u /* hi: unspecified */),l3);
    i1 = *(int *)(l3 + 0x30);
    FUN_00355100(STK);
    FUN_00077894();
    (*x19)();
    (*x9_01)(loc98 + i1,x21);
    FUN_003510d0(STK);
    av13 = FUN_0009e234();
    (*x8_12)(av13,(0u /* hi: unspecified */),l3);
    (*x19)(loc50 + (int64_t)*(int *)(x1 + 0x24),loc98 + *(int *)(l3 + 0x30),
                 x21);
    FUN_00100efc();
    (*x9_01)();
    FUN_003508e4();
    FUN_00310d34();
    FUN_00357aa8();
    FUN_001a1854(loc50);
    FUN_00351e48(STK);
    FUN_00352c4c(l12);
    v4 = FUN_001dc430();
    FUN_003548ac(v4,l3 + *(int *)(x1 + 0x24));
    (*x9_00)(x16 + 0x10U & 0xffffffffffff | 0xe3ba000000000000);
    FUN_00351360();
    (*x8_08)();
    FUN_0035130c(v5,loc88);
    FUN_00357398();
    v5 = (*x8_10)();
    FUN_00100efc();
    (*x9_01)();
    x24 = l3;
    if ((v5 & 1) == 0) {
      (*x8_08)(loc50,x1);
      goto LAB_0027ad64;
    }
    l12 = l12 + 1;
  } while( true );
  fn9 = *(uint64_t (**)())(x16_00 + 8);
LAB_0027ad58:
  (*fn9)(loc50,x1);
LAB_0027ad64:
  FUN_00353bac();
  v4 = loc10[0];
  if (l2 == x8_13) goto LAB_0027ad7c;
  goto LAB_0027a918;
}


/* FUN_0027ad9c @ 0x0027ad9c  (est. vspace_op_0027ad9c)
 * Ghidra: uint64_t vspace_op_0027ad9c(uint64_t arg1,uint64_t arg2)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027ad9c(uint64_t arg1,uint64_t arg2)
{
  FUN_0034d024();
  FUN_0031d8c8();
  FUN_00355c28();
  vspace_op_00279d78(); /* dropped 1 leftover-register arg(s) */
  return arg2;
}


/* FUN_0027ade0 @ 0x0027ade0  (est. vspace_op_0027ade0)
 * Ghidra: void vspace_op_0027ade0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027ade0(void)
{
    int i1;
    uint64_t v2;
    uint64_t v3;
    uint64_t v4;
    uint64_t v5;
    uint64_t v6;
    uint64_t v7;
    int64_t l8;
    int64_t x8;
    int64_t x8_00;
    uint64_t (*x8_01)();;
    int64_t x8_02;
    uint64_t (*x8_03)();;
    uint64_t (*x8_04)();;
    uint64_t (*x8_05)();;
    int64_t x16;
    int64_t x16_00;
    int64_t x19;
    int64_t l9;
    int64_t x21;
    int64_t l10;
    int64_t x24;
    int64_t x25;
    uint64_t (*fn11)();;
    uint64_t x30;
    uint64_t av12;
    uint64_t * locc0;
    uint64_t locb0;
    int64_t loc90;
    int64_t loc68;
    int64_t loc60;
    uint64_t us58;
    uint64_t loc50;
    int64_t loc38;
    int64_t loc30;
    int64_t xlStack_28;
    int64_t loc20;
    uint64_t us18;
    uint64_t loc10;
  
  FUN_0008e518();
  av12 = FUN_00358da0();
  l8 = (0u /* hi: unspecified */);
  l9 = av12;
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_003497b4();
  FUN_00355fac();
  FUN_0034d024();
  FUN_00310e08();
  FUN_00348e18();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_003493c4();
  FUN_0034acf0();
  (*DAT_00658c00)();
  FUN_0034bd30();
  (*DAT_00658c00)();
  FUN_00350464();
  FUN_00354028();
  FUN_0036b270(l9);
  loc60 = l9;
  FUN_0034c920();
  v2 = FUN_0031b71c();
  v3 = FUN_00348c30();
  av12 = FUN_00376820(v3,v2);
  v3 = av12;
  FUN_00270c08(&loc20,v3,(0u /* hi: unspecified */),v2,v3);
  loc30 = 0;
  xlStack_28 = l8;
  FUN_0036b270(l8);
  loc38 = l9;
  FUN_00352554(x16 + 0x10);
  l9 = 0;
  do {
    l10 = *(int64_t *)(l8 + 0x10);
    if (l9 == l10) {
      FUN_0036b118(l8);
      FUN_0035505c();
      FUN_0036b118();
      FUN_0036b118(loc10);
LAB_0027b1e4:
      FUN_0008e500(l9 == l10,x30);
      return 0;
    }
    FUN_00351ab0(loc90,l9);
    FUN_001fea40();
    loc60 = l9;
    v4 = FUN_00348a50();
    FUN_00376820(v4,v2);
    FUN_0034887c();
    v4 = FUN_0035a1e8();
    FUN_001e7664(v4,v2);
    FUN_00355224();
    FUN_0034ce78();
    (*x8_01)();
    (*DAT_00658c00)();
    FUN_00358288();
    *(int64_t *)(x8_02 + -0x20) = x24;
    *(int64_t *)(x8_02 + -0x18) = x25;
    *(int64_t *)(x8_02 + -0x10) = x21;
    av12 = FUN_0035113c();
    v5 = FUN_0031b080(av12,(0u /* hi: unspecified */),v3);
    FUN_00353050(&loc60,FUN_0031d8e0);
    FUN_001d80e0();
    v4 = loc10;
    l10 = loc60;
    if ((char)us58 == '\x01') {
      FUN_0036b118(l8);
      FUN_0035505c();
      FUN_0036b118();
      FUN_0036b118(loc10);
      FUN_00354f80();
      (*x8_05)(x21);
      x24 = loc90;
LAB_0027b1d8:
      FUN_00356750();
      l10 = x24;
      goto LAB_0027b1e4;
    }
    us58 = us18;
    loc60 = loc20;
    loc50 = loc10;
    loc68 = l10;
    v6 = FUN_00352ca4(STK,&loc68);
    FUN_001ff258(v6,v5);
    ((uint64_t (*)())(*(locc0)))(locb0,x25 + *(int *)(x19 + 0x24),x24);
    fn11 = *(uint64_t (**)())(x16_00 + 8);
    FUN_0035060c();
    (*fn11)();
    i1 = *(int *)(x19 + 0x24);
    FUN_0035044c(x25);
    FUN_003512cc(locb0,x21 + i1);
    v7 = (*x8_03)();
    v5 = FUN_0034f9ec(STK);
    (*x8_04)(v5,x24);
    if ((v7 & 1) != 0) {
      FUN_0036b118(v4);
      FUN_0036b118(l8);
      FUN_0035505c();
      FUN_0036b118();
      (*fn11)(x21);
      goto LAB_0027b1d8;
    }
    loc68 = l10;
    FUN_0034f8bc();
    av12 = FUN_00002534();
    FUN_003489a8(av12,(0u /* hi: unspecified */),av12);
    FUN_001d9890(&loc60,&loc68,v2);
    FUN_0036b118(v4);
    us18 = us58;
    loc20 = loc60;
    loc10 = loc50;
    FUN_00084180();
    (*fn11)();
    l9 = loc30;
  } while( true );
}


/* FUN_0027b204 @ 0x0027b204  (est. vspace_op_0027b204)
 * Ghidra: uint32_t vspace_op_0027b204(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint32_t vspace_op_0027b204(void)
{
    uint32_t v1;
    uint64_t v2;
    int64_t x8;
    uint64_t (*x8_00)();;
    uint64_t (*x8_01)();;
    uint64_t (*x8_02)();;
    uint64_t (*x9)();;
    int64_t x16;
  
  FUN_003539f4();
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_00349178();
  FUN_00352468(x16);
  (*x9)();
  FUN_00310e20();
  FUN_0034c8b8();
  FUN_00350aac();
  v2 = (*x8_00)();
  if ((v2 & 1) == 0) {
    v1 = 0;
  }
  else {
    FUN_0034d904();
    FUN_00310e08();
    FUN_0035044c();
    FUN_00350aac();
    v1 = (*x8_01)();
  }
  FUN_003509bc(*(uint64_t *)(x16 + 8));
  (*x8_02)();
  return v1 & 1;
}


/* FUN_0027b304 @ 0x0027b304  (est. vspace_op_0027b304)
 * Ghidra: uint64_t vspace_op_0027b304(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027b304(void)
{
    uint64_t v1;
    uint64_t v2;
    uint64_t x1;
  
  FUN_00349fcc();
  v1 = vspace_op_00278dac(); /* dropped 1 leftover-register arg(s) */
  if ((v1 & 1) != 0) {
    return 0;
  }
  FUN_0008412c();
  v2 = vspace_op_0027ade0();
  return v2;
}


/* FUN_0027b368 @ 0x0027b368  (est. vspace_op_0027b368)
 * Ghidra: uint32_t vspace_op_0027b368(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint32_t vspace_op_0027b368(void)
{
    uint32_t v1;
    uint64_t v2;
    uint64_t x1;
  
  FUN_00349fcc();
  FUN_0036b270(x1);
  FUN_0008412c();
  v2 = FUN_0020083c();
  FUN_00350624();
  v1 = FUN_001fe95c();
  FUN_0036b118(v2);
  return v1 & 1;
}


/* FUN_0027b3c0 @ 0x0027b3c0  (est. vspace_op_0027b3c0)
 * Ghidra: void vspace_op_0027b3c0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027b3c0(void)
{
    uint64_t v1;
    uint64_t v2;
    uint64_t av3;
  
  FUN_00352ddc();
  v1 = FUN_0031b71c();
  v2 = FUN_00348c30();
  FUN_00376820(v2,v1);
  FUN_00357a84();
  av3 = FUN_00019858();
  FUN_001a6ab8(av3,(0u /* hi: unspecified */),v1);
  return 0;
}


/* FUN_0027b41c @ 0x0027b41c  (est. vspace_op_0027b41c)
 * Ghidra: void vspace_op_0027b41c(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4,                  uint64_t arg5)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027b41c(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4,
                 uint64_t arg5)
{
    uint8_t v1;
    uint64_t v2;
    uint64_t v3;
    uint64_t v4;
    uint64_t v5;
    uint64_t v6;
    uint64_t x1;
    uint64_t x1_00;
    uint64_t x1_01;
    uint64_t x8;
    uint64_t (*x8_00)();;
    int64_t x8_01;
    uint64_t (*x8_02)();;
    uint64_t (*x8_03)();;
    uint64_t (*x8_04)();;
    uint64_t (*x9)();;
    uint64_t (*x9_00)();;
    int64_t x10;
    uint64_t x20;
    int64_t x21;
    uint64_t x26;
    char ww27;
    uint64_t x30;
    uint64_t av7;
    uint64_t is00000008;
    uint64_t locf0;
    uint64_t st60;
    uint64_t loc50;
    uint64_t us48;
    uint64_t loc40;
  
  FUN_00353cfc();
  FUN_00355cbc();
  FUN_00351ad4();
  FUN_00027754();
  av7 = FUN_00348e30();
  v2 = FUN_00377824(av7,(0u /* hi: unspecified */),arg3);
  FUN_0034ab20();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034c330();
  FUN_0034b164();
  FUN_00353000();
  v3 = FUN_00377824();
  FUN_000a6f88(v3,v3);
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_00350428();
  FUN_003516fc();
  FUN_003515b4(0xff);
  FUN_003722e4();
  FUN_00352efc();
  FUN_0034d464();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034bdfc();
  FUN_003508e4();
  FUN_00353000();
  FUN_00377824();
  FUN_00348cd0();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_00350428();
  FUN_003509a4();
  FUN_00359880();
  v3 = FUN_00027614();
  FUN_00350ea4();
  FUN_00354300();
  FUN_00377bec();
  FUN_00352894();
  v4 = FUN_00325088(0x656260,(uint64_t)&DAT_004ea72c);
  FUN_0031d910(0,STK);
  FUN_00349c44(STK);
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_003501e4();
  FUN_00359568();
  FUN_0031d928(0,STK);
  FUN_00348d4c();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b05c();
  loc50 = arg3;
  us48 = arg4;
  loc40 = arg5;
  FUN_00310e74(arg4);
  FUN_00358324();
  (*x9)(STK,FUN_0031d940,st60,x10 + 8,arg3,arg4);
  if (x21 == 0) {
    FUN_0035606c();
    v1 = ww27 == '\x01';
    if ((bool)v1) {
      v5 = FUN_0029207c(x20,x1,arg3,(0u /* hi: unspecified */));
      FUN_00310b98(x26);
      FUN_00352ca4(STK);
      FUN_00351354();
      (*x9_00)();
      is00000008 = v5;
      v6 = FUN_00310d34(0,v2);
      v6 = FUN_00376820((uint64_t)&DAT_004e8214,v6);
      FUN_00348e9c(v6,v6);
      FUN_00356600(STK);
      v6 = FUN_0019fa60();
      FUN_00351af8(STK,v6,STK);
      FUN_00351100(v3);
      FUN_001bcf40();
      FUN_00350bc0(STK);
      FUN_003512c0();
      (*x8_00)();
      FUN_00292490(v3,locf0);
      FUN_00353718();
      FUN_003589cc();
      while( true ) {
        FUN_0029259c();
        av7 = FUN_00351330();
        av7 = FUN_00350884(av7,(0u /* hi: unspecified */),x1_01);
        if ((bool)v1) break;
        FUN_003508cc(*(uint64_t *)(x8_01 + 0x20));
        (*x8_02)();
        FUN_00354b08();
        av7 = FUN_00351450();
        FUN_0019ea20(av7,(0u /* hi: unspecified */),v2);
        FUN_00310ed4(v4);
        v6 = FUN_00350a40();
        FUN_00351f1c(v6,x8);
        (*x8_03)();
      }
      FUN_00350bc0(STK,av7,(0u /* hi: unspecified */),x1_00);
      (*x8_04)(v3);
      FUN_0036b118(v5);
    }
  }
  FUN_00353d14(x30);
  return 0;
}


/* FUN_0027b8c0 @ 0x0027b8c0  (est. vspace_op_0027b8c0)
 * Ghidra: void vspace_op_0027b8c0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027b8c0(void)
{
    int i1;
    int64_t l2;
    uint64_t v3;
    uint64_t v4;
    uint64_t v5;
    int64_t l6;
    uint64_t ix5;
    uint64_t (*x8)();;
    uint64_t (*x8_00)();;
    uint64_t (*x8_01)();;
    uint64_t (*x8_02)();;
    int64_t x16;
    int64_t x19;
    int64_t x27;
    uint64_t av7;
    uint64_t is00000018;
    int64_t loc40[4];
    int64_t loc20;
    int64_t al18[2];
    int64_t loc8;
  
  av7 = FUN_0008e518();
  l6 = (0u /* hi: unspecified */);
  FUN_00350328();
  FUN_00310e08();
  FUN_00348e18();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b0d4();
  if (*(uint64_t *)(l6 + 0x10) < 2) {
    loc40[0] = l6;
    FUN_003504e8();
    v3 = FUN_00310d80();
    v4 = FUN_00349234();
    v4 = FUN_00376820(v4,v3);
    v5 = FUN_0019fd10(v3,v4);
    l6 = 0;
    if ((v5 & 1) == 0) {
      FUN_0034e0a4(v5,0);
      FUN_001dc430();
      i1 = *(int *)(x19 + 0x24);
      FUN_0035044c(ix5);
      FUN_003516b4(av7 + (int64_t)i1);
      v5 = (*x8)();
      if ((v5 & 1) == 0) {
        i1 = *(int *)(x19 + 0x24);
        FUN_00351ee0(ix5);
        FUN_003516b4(av7,x27 + i1);
        (*x8_01)();
        FUN_003508cc(*(uint64_t *)(x16 + 8));
        v5 = (*x8_02)();
        l6 = 1;
      }
      else {
        FUN_003508cc(*(uint64_t *)(x16 + 8));
        v5 = (*x8_00)();
        l6 = 0;
      }
    }
  }
  else {
    loc8 = l6;
    (*DAT_00658c00)();
    FUN_003504e8();
    v3 = FUN_00310d80();
    v4 = FUN_00349234();
    FUN_00376820(v4,v3);
    FUN_003514dc(loc40,FUN_0031d964);
    FUN_001db6b0();
    l2 = loc40[0];
    al18[0] = loc40[0];
    loc20 = l6;
    FUN_0034f8bc();
    FUN_00002534();
    v4 = FUN_00349910();
    FUN_00376820(v4,v3);
    FUN_003489a8();
    FUN_00351abc(loc40,al18);
    FUN_00270d80();
    (*DAT_00658c00)();
    FUN_003504e8();
    v3 = FUN_00310df0();
    v4 = FUN_00348d00();
    FUN_00376820(v4,v3);
    FUN_0035a4ec();
    FUN_003508c0();
    FUN_001db6b0();
    v5 = FUN_0036b118(loc40[0]);
    l6 = loc8;
    if (loc8 < l2) {
      FUN_00347d60();
      FUN_001afe4c();
    }
  }
  av7 = FUN_00359920(v5,l6);
  FUN_0008e500(av7,(0u /* hi: unspecified */),is00000018);
  return 0;
}


/* FUN_0027bb78 @ 0x0027bb78  (est. vspace_op_0027bb78)
 * Ghidra: void vspace_op_0027bb78(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027bb78(void)
{
    uint64_t (*xUNRECOVERED_JUMPTABLE)();;
    int64_t l1;
    int64_t x16;
    int64_t x21;
  
  FUN_00350a28();
  FUN_00356ba4();
  FUN_0034b07c();
  xUNRECOVERED_JUMPTABLE = *(uint64_t (**)())(x16 + 0x20);
  (*xUNRECOVERED_JUMPTABLE)();
  FUN_0034d414();
  l1 = FUN_003722e4();
  FUN_00350624(x21 + *(int *)(l1 + 0x30));
  (*xUNRECOVERED_JUMPTABLE)();
  return 0;
}


/* FUN_0027bc50 @ 0x0027bc50  (est. vspace_op_0027bc50)
 * Ghidra: void vspace_op_0027bc50(uint64_t arg1)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027bc50(uint64_t arg1)
{
    uint64_t v1;
  
  v1 = FUN_00376820((uint64_t)&DAT_004eaac8,arg1);
  FUN_001e088c(arg1,v1);
  return 0;
}


/* FUN_0027bc98 @ 0x0027bc98  (est. vspace_op_0027bc98)
 * Ghidra: uint8_t * vspace_op_0027bc98(int64_t *param_1, uint64_t *param_2, int64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027bc98(int64_t *param_1,uint64_t *param_2,int64_t arg3)
{
    int64_t l1;
    uint64_t v2;
    uint64_t * x20;
  
  l1 = FUN_0036a908(0x28,0xfbee);
  *param_1 = l1;
  v2 = vspace_op_0027bd10(((int64_t *)l1), *param_2, *x20, *(uint64_t *)(arg3 + 0x10),
                       *(uint64_t *)(arg3 + 0x18));
  *(uint64_t *)(l1 + 0x20) = v2;
  return (uint64_t)&DAT_003471a4;
}


/* FUN_0027bd10 @ 0x0027bd10  (est. vspace_op_0027bd10)
 * Ghidra: uint64_t vspace_op_0027bd10(int64_t *param_1,uint64_t arg2,uint64_t arg3,uint64_t arg4,             uint64_t arg5)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t
vspace_op_0027bd10(int64_t *param_1,uint64_t arg2,uint64_t arg3,uint64_t arg4,
            uint64_t arg5)
{
    int64_t l1;
    uint64_t av2;
  
  l1 = FUN_00310e08(0,arg4,arg5);
  *param_1 = l1;
  l1 = *(int64_t *)(l1 + -8);
  param_1[1] = l1;
  l1 = FUN_0036a908(*(uint64_t *)(l1 + 0x40),0x8951);
  param_1[2] = l1;
  FUN_001fea40(l1,arg2,arg3,arg4,arg5);
  (void)(l1); /* hi write (unspecified) dropped */
  av2 = (uint64_t)&DAT_003471a8;
  return av2;
}


/* FUN_0027bdd4 @ 0x0027bdd4  (est. vspace_op_0027bdd4)
 * Ghidra: void vspace_op_0027bdd4(uint64_t arg1,uint64_t arg2)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027bdd4(uint64_t arg1,uint64_t arg2)
{
    uint64_t v1;
  
  v1 = FUN_00376820((uint64_t)&DAT_004eaae4,arg2);
  FUN_0019fa60(arg1,arg2,v1,0x6720e8);
  return 0;
}


/* FUN_0027be40 @ 0x0027be40  (est. vspace_op_0027be40)
 * Ghidra: void vspace_op_0027be40(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027be40(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  v1 = FUN_00376820((uint64_t)&DAT_004eaae4);
  FUN_001e7664(arg1,arg2,arg3,v1,0x6720e8);
  return 0;
}


/* FUN_0027bedc @ 0x0027bedc  (est. vspace_op_0027bedc)
 * Ghidra: void vspace_op_0027bedc(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027bedc(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  v1 = FUN_00376820((uint64_t)&DAT_004eaae4);
  FUN_001e7038(arg1,arg2,arg3,v1,0x6720e8);
  return 0;
}


/* FUN_0027bf78 @ 0x0027bf78  (est. vspace_op_0027bf78)
 * Ghidra: void vspace_op_0027bf78(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027bf78(void)
{
    uint64_t ix3;
    uint64_t (*ix4)();;
  
  FUN_003509ec();
  FUN_00358b9c();
  FUN_00376820(ix3);
  FUN_0034887c();
  FUN_00355448();
  (*ix4)();
  return 0;
}


/* FUN_0027bfc8 @ 0x0027bfc8  (est. vspace_op_0027bfc8)
 * Ghidra: void vspace_op_0027bfc8(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027bfc8(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  FUN_00349ef4();
  v1 = FUN_00348a50();
  FUN_00376820(v1,arg3);
  FUN_003486fc();
  FUN_0034b128();
  FUN_001e664c();
  return 0;
}


/* FUN_0027c010 @ 0x0027c010  (est. vspace_op_0027c010)
 * Ghidra: void vspace_op_0027c010(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c010(void)
{
    uint64_t v1;
    uint64_t ix3;
  
  FUN_00349944();
  v1 = FUN_00348a50();
  FUN_00376820(v1,ix3);
  FUN_003498a8();
  FUN_001e3a28();
  return 0;
}


/* FUN_0027c054 @ 0x0027c054  (est. vspace_op_0027c054)
 * Ghidra: void vspace_op_0027c054(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c054(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  FUN_000867ec();
  v1 = FUN_00348a50();
  FUN_00376820(v1,arg3);
  FUN_003486fc();
  FUN_0034b778();
  FUN_001e6be8();
  return 0;
}


/* FUN_0027c0a8 @ 0x0027c0a8  (est. vspace_op_0027c0a8)
 * Ghidra: void vspace_op_0027c0a8(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c0a8(void)
{
    uint64_t v1;
    uint64_t v2;
    uint64_t av3;
  
  FUN_0035098c();
  FUN_0034d024();
  v1 = FUN_00310e08();
  v2 = FUN_0035142c();
  FUN_00376820(v2,v1);
  av3 = FUN_000b43d0();
  FUN_001df16c(av3,(0u /* hi: unspecified */),v1);
  return 0;
}


/* FUN_0027c1c0 @ 0x0027c1c0  (est. vspace_op_0027c1c0)
 * Ghidra: void vspace_op_0027c1c0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c1c0(void)
{
    uint64_t (*x19)();;
    uint64_t * x20;
    int64_t x21;
    uint8_t st78[72];
  
  FUN_00354f10();
  FUN_00359134();
  (*x19)(st78,*x20,*(uint64_t *)(x21 + 0x10),
               *(uint64_t *)(x21 + 0x18));
  FUN_001a8564();
  return 0;
}


/* FUN_0027c224 @ 0x0027c224  (est. vspace_op_0027c224)
 * Ghidra: void vspace_op_0027c224(uint64_t arg1,int64_t arg2,int64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c224(uint64_t arg1,int64_t arg2,int64_t arg3)
{
    int64_t l1;
    uint64_t v2;
    uint8_t * p3;
    uint64_t x1;
    uint64_t (*x8)();;
    uint64_t (*x9)();;
    uint64_t (*x9_00)();;
    int64_t x12;
    uint64_t x16;
    int64_t x16_00;
    int64_t x16_01;
    uint64_t v4;
  
  v4 = *(uint64_t *)(arg3 + 0x10);
  FUN_0034d414();
  l1 = FUN_003722e4();
  FUN_0034b57c();
  FUN_00351408(x16);
  (*DAT_00658c00)();
  p3 = STK + -x12;
  if (arg2 == 1) {
    FUN_00352834();
    FUN_00350ed0();
    v2 = (*x9_00)();
    l1 = (int64_t)*(int *)(l1 + 0x30);
    p3 = p3 + l1;
  }
  else {
    if (arg2 != 0) {
      FUN_00350410();
      FUN_003488bc();
      FUN_0006f768();
      FUN_00356408();
    }
    FUN_00352834();
    FUN_00350ed0();
    v2 = (*x9)();
    l1 = (int64_t)*(int *)(l1 + 0x30);
  }
  FUN_003494e8(l1,v2,p3);
  FUN_003503e0();
  ((uint64_t (*)())(*((void **)(x16_01 + 0x20))))(arg1,x1,v4);
  FUN_00084180(*(uint64_t *)(x16_00 + 8));
  (*x8)();
  return 0;
}


/* FUN_0027c37c @ 0x0027c37c  (est. vspace_op_0027c37c)
 * Ghidra: void vspace_op_0027c37c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c37c(void)
{
  FUN_0034c084();
  FUN_00348eb4();
  FUN_00376820();
  FUN_0034887c();
  FUN_0034ffb8();
  FUN_001e7038();
  return 0;
}


/* FUN_0027c3d0 @ 0x0027c3d0  (est. vspace_op_0027c3d0)
 * Ghidra: void vspace_op_0027c3d0(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c3d0(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  FUN_00349ef4();
  v1 = FUN_00348eb4();
  FUN_00376820(v1,arg3);
  FUN_003486fc();
  FUN_0034b128();
  FUN_001e664c();
  return 0;
}


/* FUN_0027c418 @ 0x0027c418  (est. vspace_op_0027c418)
 * Ghidra: void vspace_op_0027c418(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c418(void)
{
    uint64_t v1;
    uint64_t ix3;
  
  FUN_00349944();
  v1 = FUN_00348eb4();
  FUN_00376820(v1,ix3);
  FUN_003498a8();
  FUN_001e3a28();
  return 0;
}


/* FUN_0027c45c @ 0x0027c45c  (est. vspace_op_0027c45c)
 * Ghidra: void vspace_op_0027c45c(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c45c(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  FUN_000867ec();
  v1 = FUN_00348eb4();
  FUN_00376820(v1,arg3);
  FUN_003486fc();
  FUN_0034b778();
  FUN_001e6be8();
  return 0;
}


/* FUN_0027c4a0 @ 0x0027c4a0  (est. vspace_op_0027c4a0)
 * Ghidra: uint8_t * vspace_op_0027c4a0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c4a0(void)
{
    int64_t l1;
    uint64_t v2;
    uint64_t * x21;
    int64_t * x22;
  
  FUN_000867ec();
  l1 = FUN_0036a908(0x28,0x2ca3);
  *x22 = l1;
  v2 = vspace_op_0027c50c(((int64_t *)l1), *x21, 0 /* leftover-register arg */); /* padded 1 leftover-register arg(s) */
  *(uint64_t *)(l1 + 0x20) = v2;
  return (uint64_t)&DAT_003471a4;
}


/* FUN_0027c50c @ 0x0027c50c  (est. vspace_op_0027c50c)
 * Ghidra: uint64_t vspace_op_0027c50c(int64_t *param_1,uint64_t arg2,int64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c50c(int64_t *param_1,uint64_t arg2,int64_t arg3)
{
    int64_t l1;
    uint64_t av2;
  
  l1 = *(int64_t *)(arg3 + 0x10);
  *param_1 = l1;
  l1 = *(int64_t *)(l1 + -8);
  param_1[1] = l1;
  l1 = FUN_0036a908(*(uint64_t *)(l1 + 0x40),0x5c18);
  param_1[2] = l1;
  vspace_op_0027c224(((uint64_t)l1), ((int64_t)arg2), ((int64_t)arg3));
  (void)(l1); /* hi write (unspecified) dropped */
  av2 = (uint64_t)&DAT_003471a8;
  return av2;
}


/* FUN_0027c5b4 @ 0x0027c5b4  (est. vspace_op_0027c5b4)
 * Ghidra: void vspace_op_0027c5b4(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c5b4(void)
{
    uint64_t v1;
  
  FUN_00351cc4();
  FUN_00348eb4();
  v1 = FUN_00376820();
  FUN_00348e9c(v1,v1);
  FUN_00353c18();
  FUN_0019fa60();
  return 0;
}


/* FUN_0027c5f8 @ 0x0027c5f8  (est. vspace_op_0027c5f8)
 * Ghidra: void vspace_op_0027c5f8(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c5f8(void)
{
  FUN_0034c084();
  FUN_00348eb4();
  FUN_00376820();
  FUN_0034887c();
  FUN_0034ffb8();
  FUN_001e7664();
  return 0;
}


/* FUN_0027c64c @ 0x0027c64c  (est. vspace_op_0027c64c)
 * Ghidra: void vspace_op_0027c64c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c64c(void)
{
    uint64_t (*x19)();;
  
  FUN_00350858();
  FUN_00358b9c();
  FUN_00348eb4();
  FUN_00376820();
  FUN_0034887c();
  FUN_00355448();
  (*x19)();
  return 0;
}


/* FUN_0027c698 @ 0x0027c698  (est. vspace_op_0027c698)
 * Ghidra: void vspace_op_0027c698(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c698(void)
{
    int i1;
    int64_t l2;
    int64_t x8;
    uint64_t (*x8_00)();;
    int64_t x16;
    int64_t x21;
  
  FUN_00351cc4();
  FUN_000a6f88();
  ((uint64_t (*)())(*((void **)(x8 + 0x10))))();
  FUN_00376820((uint64_t)&DAT_004f1754);
  FUN_0034fce4();
  l2 = FUN_0031090c();
  i1 = *(int *)(l2 + 0x24);
  FUN_0007c1c4(*(uint64_t *)(x16 + 8));
  (*x8_00)();
  *(uint64_t *)(x21 + i1) = 0;
  return 0;
}


/* FUN_0027c740 @ 0x0027c740  (est. vspace_op_0027c740)
 * Ghidra: void vspace_op_0027c740(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c740(void)
{
  FUN_0034b1c0();
  FUN_00376820();
  FUN_00353a30();
  FUN_001a0194();
  return 0;
}


/* FUN_0027c770 @ 0x0027c770  (est. vspace_op_0027c770)
 * Ghidra: void vspace_op_0027c770(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c770(void)
{
  FUN_0034b1c0();
  FUN_00376820();
  FUN_00353a30();
  FUN_001e088c();
  return 0;
}


/* FUN_0027c7a0 @ 0x0027c7a0  (est. vspace_op_0027c7a0)
 * Ghidra: uint64_t vspace_op_0027c7a0(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t
vspace_op_0027c7a0(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
    uint64_t av1;
    uint64_t (*loc38)();;
    int64_t loc30;
    int64_t loc28;
  
  loc28 = -0x2c8502b44bfffed6;
  loc38 = (uint64_t (*)())0x0;
  loc30 = 0;
  FUN_003a0690(arg1,arg2,arg3,arg4,&loc30,&loc38,0x67b1e8);
  if (loc30 == 0) {
    av1 = (0);
  }
  else {
    av1 = FUN_001e9f14();
  }
  if (loc38 != (uint64_t (*)())0x0) {
    (*loc38)(loc30);
  }
  if (loc28 == -0x2c8502b44bfffed6) {
    return av1;
  }
  FUN_0011d7e8();
}


/* FUN_0027c85c @ 0x0027c85c  (est. vspace_op_0027c85c)
 * Ghidra: void vspace_op_0027c85c(uint64_t arg1,uint64_t arg2,uint64_t *param_3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027c85c(uint64_t arg1,uint64_t arg2,uint64_t *param_3)
{
    int i1;
    uint64_t av2;
    uint64_t av3;
    uint8_t zr;
    uint32_t v4;
    int64_t l6;
    uint64_t v7;
    uint64_t v8;
    uint64_t v9;
    uint64_t * x8;
    int64_t x8_00;
    int64_t x8_01;
    int64_t x8_02;
    uint64_t v10;
    uint64_t v11;
    uint8_t v12;
    uint64_t x30;
    uint64_t v13;
    uint64_t av14;
    uint64_t av15;
    uint64_t is00000020;
    uint64_t is00000028;
    int64_t l5;
  
  av14 = FUN_0035a9b0();
  l6 = (0u /* hi: unspecified */);
  l5 = av14;
  if (l6 == 0) {
    v10 = *(uint64_t *)(l5 + 0x18);
    FUN_003509bc();
    v9 = FUN_0006a4c0();
    v9 = FUN_003625e4(v9,v10,1);
    av15 = FUN_0039fb68(l5,v9,0x67b1e8);
    l6 = (0u /* hi: unspecified */);
    (void)(av15); /* hi write (unspecified) dropped */
    av14 = av15;
  }
  v11 = (0u /* hi: unspecified */);
  FUN_000e15d8(av14,l6,0x67b1e8);
  l6 = FUN_0039fcd8();
  if (l6 < 0) {
    FUN_00347d60();
    FUN_001afe4c();
  }
  FUN_00319808(l5,STK);
  l6 = FUN_0036a940(0x678cb0,0x38,7);
  FUN_00310d98(STK,l6 + 0x10);
  *(uint64_t *)(l6 + 0x30) = v11;
  FUN_00002534((uint64_t)&DAT_00657700,(uint64_t)&DAT_004f2210);
  av14 = FUN_00358fe8();
  FUN_00350798(av14,(0u /* hi: unspecified */),FUN_00344b1c);
  v7 = FUN_00211188();
  FUN_00319808(l5,STK);
  v8 = FUN_0036a940(0x678cd8,0x68,7);
  (void)(v8); /* hi write (unspecified) dropped */
  av15 = v11;
  *(uint64_t *)(v8 + 0x10) = v11;
  v9 = *param_3;
  v13 = param_3[3];
  v10 = param_3[2];
  *(uint64_t *)(v8 + 0x20) = param_3[1];
  *(uint64_t *)(v8 + 0x18) = v9;
  *(uint64_t *)(v8 + 0x30) = v13;
  *(uint64_t *)(v8 + 0x28) = v10;
  v9 = *(uint64_t *)((int64_t)param_3 + 0x19);
  *(uint64_t *)(v8 + 0x39) = *(uint64_t *)((int64_t)param_3 + 0x21);
  *(uint64_t *)(v8 + 0x31) = v9;
  FUN_00310d98(STK,v8 + 0x48);
  FUN_003597f0();
  FUN_00344ca8(param_3,STK);
  v4 = FUN_003a0968(l5,0x67b1e8);
  i1 = (int)(char)v4;
  (void)(i1);
  av3 = v11;
  (void)(0); /* hi/aux write (unspecified) dropped */
  if ((v4 >> 7 & 1) == 0) {
    if (i1 == 0) {
      v12 = 9;
LAB_0027ca14:
      FUN_000026e8(l5);
      FUN_00359d44();
      FUN_00344e54(param_3);
      *x8 = v11;
      x8[1] = v7;
      *(uint8_t *)(x8 + 2) = v12;
      x8[3] = (uint64_t)FUN_00344b98;
      x8[4] = v8;
      *(uint8_t *)(x8 + 5) = 0;
      FUN_0035a8d0(x30);
      return 0;
    }
    v4 = v4 & 0xff;
    if (v4 == 99) {
      v12 = 1;
      goto LAB_0027ca14;
    }
    if (v4 == 0x74) {
      v12 = 3;
      goto LAB_0027ca14;
    }
    if (v4 == 0x66) {
      v12 = 8;
      goto LAB_0027ca14;
    }
    if (v4 == 0x73) {
      v12 = 0;
      goto LAB_0027ca14;
    }
    zr = 0;
    if (v4 == 0x65) {
      v12 = 2;
      goto LAB_0027ca14;
    }
  }
  FUN_0006e778(0x1e);
  is00000020 = FUN_003548dc();
  v9 = FUN_001a89a8((uint64_t)0 /* s_Unknown_raw_display_style___005d3cd0 */,0x1b,1);
  (void)(x8); /* hi write (unspecified) dropped */
  av2 = v9;
  FUN_0034b02c();
  if ((x8_00 == 0) && (((v11 & (v7 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    FUN_003a25d4(v7);
    av15 = av2;
  }
  else {
    if ((v7 >> 0x3d & 1) == 0) {
      FUN_0034c3a0();
    }
    else if (((uint64_t)x8 >> 0x3d & 1) != 0) {
      FUN_0034edf8();
      FUN_0034a390();
      if (!(bool)zr) {
        FUN_003517c0();
        FUN_003a25d4(v7);
        FUN_003a25d4(x8);
        goto LAB_0027caf0;
      }
    }
    FUN_0034ef38();
    FUN_002a4c98();
    FUN_003a25d4(x8);
    av15 = is00000020;
  }
LAB_0027caf0:
  is00000028 = (0u /* hi: unspecified */);
  v7 = is00000028;
  is00000020 = av15;
  v11 = is00000020;
  is00000020 = av15;
  av14 = FUN_00356340();
  FUN_002357b4(av14,(0u /* hi: unspecified */),i1);
  FUN_00349dcc();
  if ((x8_01 == 0) && (((v11 & (v7 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    FUN_003a25d4(v7);
    is00000020 = av3;
  }
  else {
    if ((v7 >> 0x3d & 1) == 0) {
      FUN_0034a618();
    }
    FUN_0034c9c8();
    FUN_002a4c98();
    FUN_003a25d4(i1);
  }
  v8 = is00000028;
  v11 = is00000020;
  FUN_00350744((uint64_t)&DAT_005d3ad7);
  FUN_001a89a8();
  FUN_00354a00();
  FUN_0034b18c();
  if ((x8_02 == 0) && (((v11 & (v8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    FUN_003a25d4(v8);
  }
  else {
    if ((v8 >> 0x3d & 1) == 0) {
      FUN_0034c3a0();
    }
    else if ((v7 >> 0x3d & 1) != 0) {
      FUN_0034e52c();
      FUN_0034a390();
      if (!(bool)zr) {
        FUN_00352c58();
        FUN_003a25d4(v7);
        goto LAB_0027cbd8;
      }
    }
    FUN_0034ef38();
    FUN_002a4c98();
    FUN_003a25d4(v7);
  }
LAB_0027cbd8:
  FUN_00350d94(0xb6);
  FUN_0006f768();
  FUN_003543c4();
  FUN_001afa84();
}


/* FUN_0027cd04 @ 0x0027cd04  (est. vspace_op_0027cd04)
 * Ghidra: void vspace_op_0027cd04(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027cd04(void)
{
    uint64_t x8;
    int64_t x8_00;
    uint64_t (*x8_01)();;
    uint64_t (*x9)();;
    uint64_t (*x9_00)();;
    int64_t x16;
    uint64_t (*fn1)();;
    uint64_t x30;
  
  FUN_0008e518();
  FUN_00352cec();
  FUN_00349b3c();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_00348a18();
  (*DAT_00658c00)();
  FUN_0034b308();
  (*DAT_00658c00)();
  FUN_0034ae94();
  (*DAT_00658c00)();
  FUN_0034b4c0();
  fn1 = *(uint64_t (**)())(x16 + 0x10);
  FUN_00350624();
  (*fn1)();
  FUN_00350624();
  (*fn1)();
  FUN_00356ac4();
  (*fn1)();
  FUN_0031da6c();
  FUN_00350c50();
  FUN_00350878();
  (*x9)();
  FUN_0031d4e8();
  FUN_00350878(x8);
  (*x9_00)();
  FUN_0034f9c8();
  (*x8_01)();
  FUN_0008e500(x30);
  return 0;
}


/* FUN_0027ce54 @ 0x0027ce54  (est. vspace_op_0027ce54)
 * Ghidra: void vspace_op_0027ce54(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027ce54(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
    int64_t x8;
    uint64_t (*x8_00)();;
    uint64_t (*x8_01)();;
    uint64_t (*x9)();;
    uint64_t (*x9_00)();;
    int64_t x16;
    uint64_t x30;
  
  FUN_00084220();
  FUN_003504d0();
  FUN_00349b3c();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_00348a80();
  (*DAT_00658c00)();
  FUN_0034b3d8();
  FUN_00351e84();
  FUN_0034e464();
  (*x9)();
  FUN_0031d4e8(arg3);
  FUN_00350b30();
  FUN_00350810();
  (*x9_00)();
  FUN_003514b8(arg3);
  FUN_0014ae44();
  FUN_0034d3a4();
  FUN_0034fdbc();
  (*x8_00)();
  FUN_0035060c(*(uint64_t *)(x16 + 8));
  (*x8_01)();
  v1 = FUN_0035687c();
  FUN_00084234(v1,x30);
  return 0;
}


/* FUN_0027cf48 @ 0x0027cf48  (est. vspace_op_0027cf48)
 * Ghidra: void vspace_op_0027cf48(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027cf48(void)
{
    uint64_t v1;
    int64_t x8;
    uint64_t (*x8_00)();;
    uint64_t (*x8_01)();;
    uint64_t (*x9)();;
    uint64_t (*x9_00)();;
    uint64_t x30;
  
  FUN_00084220();
  FUN_00350dd4();
  FUN_00349b3c();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_00348a80();
  (*DAT_00658c00)();
  FUN_0034b3d8();
  FUN_00352bb0();
  FUN_00350624();
  (*x9)();
  FUN_0031d4e8();
  FUN_0034f644();
  FUN_00350878();
  (*x9_00)();
  FUN_0031d518();
  FUN_0034cfe4();
  (*x8_00)();
  FUN_00357af8();
  FUN_0035060c();
  (*x8_01)();
  v1 = FUN_0035687c();
  FUN_00084234(v1,x30);
  return 0;
}


/* FUN_0027d040 @ 0x0027d040  (est. vspace_op_0027d040)
 * Ghidra: uint32_t vspace_op_0027d040(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint32_t vspace_op_0027d040(void)
{
    uint32_t v1;
    uint64_t (*x8)();;
  
  FUN_0034a958();
  FUN_0031da9c();
  FUN_0034c8a0();
  v1 = (*x8)();
  return v1 & 1;
}


/* FUN_0027d07c @ 0x0027d07c  (est. vspace_op_0027d07c)
 * Ghidra: uint32_t vspace_op_0027d07c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint32_t vspace_op_0027d07c(void)
{
    uint32_t v1;
    uint64_t x1;
    int64_t x8;
    uint64_t (*x8_00)();;
    uint64_t (*x8_01)();;
    uint64_t (*x9)();;
    int64_t x16;
  
  FUN_003518c4();
  FUN_000a6f88();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_003490ec();
  FUN_0031dacc(x1);
  FUN_0035133c();
  FUN_0006b6f4();
  (*x9)();
  FUN_0034a30c();
  FUN_00084174();
  FUN_00350aac();
  v1 = (*x8_00)();
  FUN_00350aa0(*(uint64_t *)(x16 + 8));
  (*x8_01)();
  return v1 & 1;
}


/* FUN_0027d13c @ 0x0027d13c  (est. vspace_op_0027d13c)
 * Ghidra: void vspace_op_0027d13c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027d13c(void)
{
    uint8_t zr;
    uint64_t (*fn1)();;
    uint64_t v2;
    uint64_t x1;
    uint64_t ix3;
    uint64_t ix4;
    uint64_t x8;
    int64_t x8_00;
    uint64_t (*x8_01)();;
    uint64_t (*x8_02)();;
    uint64_t (*x8_03)();;
    uint64_t (*x8_04)();;
    uint64_t (*x9)();;
    int64_t x16;
    uint64_t x30;
    uint64_t loc28;
  
  FUN_0008e518();
  FUN_0034ce98();
  FUN_00377824();
  FUN_00348d64();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_00348a9c();
  (*DAT_00658c00)();
  FUN_0034b3d8();
  FUN_00350500();
  FUN_0034d464();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034af20();
  FUN_00349830();
  FUN_00352840();
  FUN_00377824();
  FUN_00348ce8();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b0c4();
  fn1 = (uint64_t (*)())FUN_0031dacc(ix3);
  (*fn1)(x8,x1,ix3);
  FUN_00352680(ix4);
  FUN_00350914();
  (*x9)();
  FUN_0034b278();
  FUN_00350a04();
  FUN_00377bec();
  fn1 = (uint64_t (*)())FUN_000a68f4();
  while( true ) {
    FUN_003504ac();
    (*fn1)();
    FUN_0034b2a8();
    if ((bool)zr) break;
    FUN_003516f0(*(uint64_t *)(x16 + 0x20),loc28);
    (*x8_01)();
    FUN_00358ec4();
    FUN_0031dafc();
    v2 = FUN_003505f4();
    (*x8_02)(v2,loc28,x1);
    FUN_00351274(*(uint64_t *)(x16 + 8));
    (*x8_03)();
  }
  FUN_00354660();
  FUN_00355b10();
  (*x8_04)();
  FUN_0008e500(x30);
  return 0;
}


/* FUN_0027d37c @ 0x0027d37c  (est. vspace_op_0027d37c)
 * Ghidra: void vspace_op_0027d37c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027d37c(void)
{
    int64_t x8;
    uint64_t (*x8_00)();;
    uint64_t (*x8_01)();;
    uint64_t (*x9)();;
    int64_t x16;
    uint64_t (*fn1)();;
    uint64_t x30;
  
  FUN_0008e518();
  FUN_0034fbd4();
  FUN_00349b3c();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_00348a80();
  (*DAT_00658c00)();
  FUN_0034aea8();
  (*DAT_00658c00)();
  FUN_0034b87c();
  fn1 = *(uint64_t (**)())(x16 + 0x10);
  FUN_0034db68();
  (*fn1)();
  FUN_00350624();
  (*fn1)();
  FUN_0031da6c();
  FUN_00350b24();
  FUN_00350878();
  (*x9)();
  FUN_0031d488();
  FUN_00350648();
  FUN_00350878();
  (*x8_00)();
  FUN_003505e8(*(uint64_t *)(x16 + 8));
  (*x8_01)();
  FUN_0008e500(x30);
  return 0;
}


/* FUN_0027d49c @ 0x0027d49c  (est. vspace_op_0027d49c)
 * Ghidra: void vspace_op_0027d49c(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027d49c(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t (*fn1)();;
    uint64_t v2;
    uint64_t x8;
    uint64_t x30;
    uint64_t is00000008;
  
  FUN_00357cb4();
  is00000008 = FUN_00350b54();
  fn1 = (uint64_t (*)())FUN_0031db2c(arg3);
  FUN_00351684();
  FUN_003560f8();
  FUN_00377824();
  FUN_00352efc();
  v2 = FUN_00310d34();
  FUN_00352920(x8,STK,v2,0x66acf0);
  (*fn1)();
  FUN_00357c74(x30);
  return 0;
}


/* FUN_0027d530 @ 0x0027d530  (est. vspace_op_0027d530)
 * Ghidra: uint64_t vspace_op_0027d530(int64_t arg1)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027d530(int64_t arg1)
{
    uint32_t v1;
    uint64_t v2;
    uint32_t v3;
  
  if (arg1 - 0x300U < 7) {
    switch(arg1) {
    default:
      return 5;
    case 0x301:
      return 6;
    case 0x302:
      return 7;
    case 0x303:
      return 8;
    case 0x304:
      return 9;
    case 0x305:
      return 10;
    case 0x306:
      v2 = 0xb;
    }
  }
  else {
    if (3 < arg1 - 0x200U) {
      v3 = 0xf;
      if (arg1 != 0xffff) {
        v3 = 0x10;
      }
      v1 = 0xe;
      if (arg1 != 0x501) {
        v1 = v3;
      }
      v3 = 0xd;
      if (arg1 != 0x500) {
        v3 = v1;
      }
      v1 = 0xc;
      if (arg1 != 0x400) {
        v1 = v3;
      }
      v3 = 0;
      if (arg1 != 0) {
        v3 = v1;
      }
      return (uint64_t)v3;
    }
    v2 = 1;
    switch(arg1) {
    case 0x201:
      return 2;
    case 0x202:
      v2 = FUN_0006f794(1);
      return v2;
    case 0x203:
      return 4;
    }
  }
  return v2;
}


/* FUN_0027d648 @ 0x0027d648  (est. vspace_op_0027d648)
 * Ghidra: uint64_t vspace_op_0027d648(uint64_t arg1)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027d648(uint64_t arg1)
{
  return *(uint64_t *)((uint64_t)&DAT_004f2670 + (arg1 & 0xff) * 8);
}


/* FUN_0027d674 @ 0x0027d674  (est. vspace_op_0027d674)
 * Ghidra: void vspace_op_0027d674(uint8_t *param_1,uint64_t *param_2)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027d674(uint8_t *param_1,uint64_t *param_2)
{
    uint8_t v1;
  
  v1 = vspace_op_0027d530(*param_2);
  *param_1 = v1;
  return 0;
}


/* FUN_0027d6a4 @ 0x0027d6a4  (est. vspace_op_0027d6a4)
 * Ghidra: void vspace_op_0027d6a4(uint64_t *param_1)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027d6a4(uint64_t *param_1)
{
    uint64_t v1;
    uint8_t * x20;
  
  v1 = vspace_op_0027d648(*x20);
  *param_1 = v1;
  return 0;
}


/* FUN_0027d6d0 @ 0x0027d6d0  (est. vspace_op_0027d6d0)
 * Ghidra: void vspace_op_0027d6d0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027d6d0(void)
{
    uint8_t v1;
    uint8_t b2;
    char c3;
    uint64_t v4;
    int64_t l5;
    uint8_t * p6;
    uint64_t v7;
    uint64_t x8;
    uint64_t (*x19)();;
    int64_t l8;
    uint64_t x30;
    uint64_t av9;
    uint64_t av10;
    uint8_t * is00000020;
    uint64_t (*is00000028)();;
    uint16_t is00000030;
    uint64_t is00000038;
  
  FUN_0035300c();
  av9 = FUN_00356048();
  FUN_0006b2ec();
  is00000038 = x8;
  b2 = FUN_0036298c();
  v1 = ((((uint32_t)((0u /* hi: unspecified */))) ^ 0xffffffff) & 0xaa1703ea) == 0;
  if (((b2 ^ v1) & 1) == 0) {
    l5 = FUN_0039ff2c(av9);
    if (l5 < 0) {
      FUN_00347d60();
      FUN_001afe4c();
    }
    if (l5 != 0) {
      l8 = 0;
      do {
        FUN_0008e388();
        av10 = FUN_003a0440();
        is00000020 = (uint8_t *)0x0;
        is00000028 = (uint64_t (*)())0x0;
        is00000030 = 0;
        FUN_0008e388(av10,(0u /* hi: unspecified */),STK);
        FUN_003a017c();
        FUN_0039fcc4();
        c3 = vspace_op_0027d530(0 /* leftover-register arg */); /* padded 1 leftover-register arg(s) */
        v1 = c3 == '\x10';
        p6 = is00000020;
        if (is00000020 == (uint8_t *)0x0) {
          p6 = (uint8_t *)&DAT_005be7c0;
        }
        FUN_00351214(p6);
        v7 = (*x19)();
        if ((v7 & 1) == 0) {
          if (is00000028 != (uint64_t (*)())0x0) {
            (*is00000028)(is00000020);
          }
          goto LAB_0027d718;
        }
        if (is00000028 != (uint64_t (*)())0x0) {
          (*is00000028)(is00000020);
        }
        l8 = l8 + 1;
        v1 = l5 == l8;
      } while (!(bool)v1);
    }
    v4 = 1;
  }
  else {
LAB_0027d718:
    v4 = 0;
  }
  v4 = FUN_000651bc(is00000038,v4);
  if ((bool)v1) {
    FUN_00353238(v4,x30);
    return 0;
  }
  FUN_0011d7e8();
}


/* FUN_0027da14 @ 0x0027da14  (est. vspace_op_0027da14)
 * Ghidra: void vspace_op_0027da14(uint64_t arg1,int64_t arg2,int64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027da14(uint64_t arg1,int64_t arg2,int64_t arg3)
{
    int64_t * x20;
  
  if ((-1 < arg2) && (arg2 < *x20)) {
    (**(uint64_t (**)())(*(int64_t *)(*(int64_t *)(arg3 + 0x10) + -8) + 0x10))
              (arg1,(int64_t)x20 + (int64_t)*(int *)(arg3 + 0x1c));
    return 0;
  }
  FUN_00348638(1);
  FUN_00349de8();
  FUN_001afe4c();
}


/* FUN_0027da90 @ 0x0027da90  (est. vspace_op_0027da90)
 * Ghidra: void vspace_op_0027da90(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027da90(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  v1 = FUN_00376820((uint64_t)&DAT_004eabe4);
  FUN_001e7038(arg1,arg2,arg3,v1,0x6720e8);
  return 0;
}


/* FUN_0027db18 @ 0x0027db18  (est. vspace_op_0027db18)
 * Ghidra: void vspace_op_0027db18(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027db18(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  FUN_00349ef4();
  v1 = FUN_0034a168();
  FUN_00376820(v1,arg3);
  FUN_003486fc();
  FUN_0034b128();
  FUN_001e664c();
  return 0;
}


/* FUN_0027db60 @ 0x0027db60  (est. vspace_op_0027db60)
 * Ghidra: void vspace_op_0027db60(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027db60(void)
{
    uint64_t v1;
    uint64_t ix3;
  
  FUN_00349944();
  v1 = FUN_0034a168();
  FUN_00376820(v1,ix3);
  FUN_003498a8();
  FUN_001e3a28();
  return 0;
}


/* FUN_0027dba4 @ 0x0027dba4  (est. vspace_op_0027dba4)
 * Ghidra: void vspace_op_0027dba4(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027dba4(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  FUN_000867ec();
  v1 = FUN_0034a168();
  FUN_00376820(v1,arg3);
  FUN_003486fc();
  FUN_0034b778();
  FUN_001e6be8();
  return 0;
}


/* FUN_0027dbe4 @ 0x0027dbe4  (est. vspace_op_0027dbe4)
 * Ghidra: void vspace_op_0027dbe4(uint64_t *param_1)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027dbe4(uint64_t *param_1)
{
    uint64_t v1;
  
  v1 = thunk_FUN_00077a90();
  *param_1 = v1;
  return 0;
}


/* FUN_0027dc0c @ 0x0027dc0c  (est. vspace_op_0027dc0c)
 * Ghidra: uint8_t * vspace_op_0027dc0c(int64_t *param_1, uint64_t *param_2, uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027dc0c(int64_t *param_1,uint64_t *param_2,uint64_t arg3)
{
    int64_t l1;
    uint64_t v2;
  
  l1 = FUN_0036a908(0x28,0x5e33);
  *param_1 = l1;
  v2 = vspace_op_0027dc80(((int64_t *)l1), *param_2, ((int64_t)arg3));
  *(uint64_t *)(l1 + 0x20) = v2;
  return (uint64_t)&DAT_003471a4;
}


/* FUN_0027dc80 @ 0x0027dc80  (est. vspace_op_0027dc80)
 * Ghidra: uint64_t vspace_op_0027dc80(int64_t *param_1,uint64_t arg2,int64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027dc80(int64_t *param_1,uint64_t arg2,int64_t arg3)
{
    int64_t l1;
    uint64_t av2;
  
  l1 = *(int64_t *)(arg3 + 0x10);
  *param_1 = l1;
  l1 = *(int64_t *)(l1 + -8);
  param_1[1] = l1;
  l1 = FUN_0036a908(*(uint64_t *)(l1 + 0x40),0x783c);
  param_1[2] = l1;
  vspace_op_0027da14(((uint64_t)l1), ((int64_t)arg2), ((int64_t)arg3));
  (void)(l1); /* hi write (unspecified) dropped */
  av2 = (uint64_t)&DAT_003471a8;
  return av2;
}


/* FUN_0027dd28 @ 0x0027dd28  (est. vspace_op_0027dd28)
 * Ghidra: void vspace_op_0027dd28(uint64_t arg1,uint64_t arg2)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027dd28(uint64_t arg1,uint64_t arg2)
{
    uint64_t v1;
  
  v1 = FUN_00376820((uint64_t)&DAT_004eabe4,arg2);
  FUN_0019fa60(arg1,arg2,v1,0x6720e8);
  return 0;
}


/* FUN_0027dd94 @ 0x0027dd94  (est. vspace_op_0027dd94)
 * Ghidra: void vspace_op_0027dd94(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027dd94(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    uint64_t v1;
  
  v1 = FUN_00376820((uint64_t)&DAT_004eabe4);
  FUN_001e7664(arg1,arg2,arg3,v1,0x6720e8);
  return 0;
}


/* FUN_0027de1c @ 0x0027de1c  (est. vspace_op_0027de1c)
 * Ghidra: void vspace_op_0027de1c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027de1c(void)
{
    uint64_t (*x19)();;
  
  FUN_00350858();
  FUN_00358b9c();
  FUN_0034a168();
  FUN_00376820();
  FUN_0034887c();
  FUN_00355448();
  (*x19)();
  return 0;
}


/* FUN_0027de68 @ 0x0027de68  (est. vspace_op_0027de68)
 * Ghidra: void vspace_op_0027de68(int64_t arg1,int64_t arg2)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027de68(int64_t arg1,int64_t arg2)
{
    int i1;
    uint64_t v2;
    int64_t l3;
    int64_t l4;
  
  l4 = *(int64_t *)(arg2 + -8);
  ((uint64_t (*)())(*((void **)(l4 + 0x10))))(arg1);
  v2 = FUN_00376820((uint64_t)&DAT_004eac1c,arg2);
  l3 = FUN_0031090c(0,arg2,v2);
  i1 = *(int *)(l3 + 0x24);
  ((uint64_t (*)())(*((void **)(l4 + 8))))();
  *(uint64_t *)(arg1 + i1) = 0;
  return 0;
}


/* FUN_0027df2c @ 0x0027df2c  (est. vspace_op_0027df2c)
 * Ghidra: void vspace_op_0027df2c(uint64_t arg1)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027df2c(uint64_t arg1)
{
    uint64_t v1;
  
  v1 = FUN_00376820((uint64_t)&DAT_004eac1c,arg1);
  FUN_001a0194(arg1,v1);
  return 0;
}


/* FUN_0027df74 @ 0x0027df74  (est. vspace_op_0027df74)
 * Ghidra: void vspace_op_0027df74(uint64_t arg1)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027df74(uint64_t arg1)
{
    uint64_t v1;
  
  v1 = FUN_00376820((uint64_t)&DAT_004eac1c,arg1);
  FUN_001e088c(arg1,v1);
  return 0;
}


/* FUN_0027dfbc @ 0x0027dfbc  (est. vspace_op_0027dfbc)
 * Ghidra: void vspace_op_0027dfbc(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027dfbc(void)
{
    int64_t x8;
    uint64_t (*x8_00)();;
  
  FUN_00350a28();
  FUN_00356ba4();
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_00349178();
  FUN_00353ba0();
  (*x8_00)();
  FUN_0034ba28();
  FUN_00271c4c();
  return 0;
}


/* FUN_0027e044 @ 0x0027e044  (est. vspace_op_0027e044)
 * Ghidra: void vspace_op_0027e044(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027e044(void)
{
    uint64_t v1;
    int64_t l2;
    int64_t l3;
    uint64_t x8;
    uint64_t x19;
    uint64_t x20;
    uint8_t st70[64];
  
  FUN_003504d0();
  v1 = FUN_0008e0d4();
  l2 = FUN_0036a9a0(v1,st70);
  v1 = DAT_004baeb0;
  *(uint64_t *)(l2 + 0x18) = DAT_004baeb8;
  *(uint64_t *)(l2 + 0x10) = v1;
  l3 = FUN_00352cb0();
  *(uint64_t *)(l3 + 0x38) = x8;
  *(uint64_t *)(l3 + 0x20) = x20;
  *(uint64_t *)(l3 + 0x28) = x19;
  thunk_FUN_0036b270();
  FUN_0026b434(l2,0x20,0xe100000000000000,0,0xe000000000000000);
  FUN_0036b588(l2);
  FUN_00002688();
  FUN_00002834();
  FUN_0036b6ac();
  return 0;
}


/* FUN_0027e0d4 @ 0x0027e0d4  (est. vspace_op_0027e0d4)
 * Ghidra: void vspace_op_0027e0d4(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027e0d4(void)
{
    uint64_t v1;
    int64_t l2;
    int64_t x16;
    uint64_t x19;
    uint8_t st70[64];
  
  FUN_003504d0();
  v1 = FUN_0008e0d4();
  l2 = FUN_0036a9a0(v1,st70);
  v1 = DAT_004baeb0;
  *(uint64_t *)(l2 + 0x18) = DAT_004baeb8;
  *(uint64_t *)(l2 + 0x10) = v1;
  *(uint64_t *)(l2 + 0x38) = x19;
  FUN_00319a4c(l2 + 0x20);
  FUN_0034b3e8();
  ((uint64_t (*)())(*((void **)(x16 + 0x10))))();
  FUN_0026b71c(l2,0x20,0xe100000000000000,10,0xe100000000000000);
  FUN_0036b588(l2);
  FUN_00002688();
  FUN_00002834();
  FUN_0036b6ac();
  return 0;
}


/* FUN_0027e17c @ 0x0027e17c  (est. vspace_op_0027e17c)
 * Ghidra: void vspace_op_0027e17c(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027e17c(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
    int i1;
    uint32_t v2;
    int64_t l3;
    uint64_t v4;
    int64_t x8;
    uint64_t x8_00;
    int64_t x8_01;
    uint64_t x8_02;
    int64_t x8_03;
    uint64_t (*x8_04)();;
    uint64_t (*x8_05)();;
    uint64_t (*x8_06)();;
    uint64_t (*x8_07)();;
    uint64_t (*x8_08)();;
    uint64_t (*x9)();;
    uint64_t (*x9_00)();;
    int64_t x16;
    int64_t x16_00;
    int64_t x16_01;
    int64_t x23;
    uint64_t (*fn5)();;
    uint64_t x30;
  
  FUN_0008e518();
  FUN_00349a68();
  (*DAT_00658c00)(*(uint64_t *)(x8 + 0x40));
  FUN_003497b4();
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8_01 + 0x40));
  FUN_003497b4();
  FUN_00350908();
  FUN_00351488();
  FUN_0031dc0c();
  FUN_00348e18();
  (*DAT_00658c00)(*(uint64_t *)(x8_03 + 0x40));
  FUN_00348a18();
  (*DAT_00658c00)();
  FUN_0034b8bc();
  FUN_0034d414();
  FUN_003515b4();
  FUN_003722e4();
  FUN_00348fd8();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  l3 = FUN_0034b2f8();
  l3 = (int64_t)*(int *)(l3 + 0x30);
  fn5 = *(uint64_t (**)())(x16_01 + 0x10);
  FUN_00356aa0();
  (*fn5)();
  FUN_0035745c(x23 + l3);
  (*fn5)();
  FUN_00350524();
  i1 = FUN_00369584();
  if (i1 == 1) {
    FUN_0034cf94();
    (*fn5)();
    i1 = FUN_00369584(x23 + l3);
    if (i1 == 1) {
      FUN_003547ec();
      (*x9)(x8_00,x23 + l3,arg4);
      FUN_00356a7c();
      FUN_0014ae44();
      FUN_0034e60c();
      FUN_00351b20();
      v2 = (*x8_04)();
      fn5 = *(uint64_t (**)())(x16 + 8);
      FUN_00350b00();
      (*fn5)();
      FUN_0035084c();
      (*fn5)();
      goto LAB_0027e468;
    }
    v4 = FUN_0035152c();
    arg3 = arg4;
    fn5 = x8_06;
  }
  else {
    FUN_0034d758();
    (*fn5)();
    i1 = FUN_00369584(x23 + l3);
    if (i1 != 1) {
      FUN_0035478c();
      (*x9_00)(x8_02,x23 + l3,arg3);
      FUN_00354a78();
      v4 = FUN_0034f1c4();
      FUN_00351b20(v4,x8_02);
      v2 = (*x8_07)();
      fn5 = *(uint64_t (**)())(x16_00 + 8);
      FUN_00350b00();
      (*fn5)();
      FUN_00351384();
      (*fn5)();
      goto LAB_0027e468;
    }
    v4 = FUN_00351a08();
    fn5 = x8_05;
  }
  (*fn5)(v4,arg3);
  v2 = 0;
LAB_0027e468:
  FUN_0034eb94();
  (*x8_08)();
  FUN_0008e500(v2 & 1,x30);
  return 0;
}


/* FUN_0027e4ac @ 0x0027e4ac  (est. vspace_op_0027e4ac)
 * Ghidra: void vspace_op_0027e4ac(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027e4ac(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    int i1;
    uint64_t x1;
    uint64_t x8;
    uint64_t (*x8_00)();;
    uint64_t (*x8_01)();;
    uint64_t (*x8_02)();;
    uint64_t (*x8_03)();;
    int64_t x9;
    int64_t x9_00;
    uint64_t (*x9_01)();;
    uint64_t (*x9_02)();;
    int64_t x10;
    int64_t x10_00;
    int64_t x12;
    int64_t x16;
    uint64_t x30;
  
  FUN_0008e518();
  FUN_003499b4();
  (*DAT_00658c00)();
  FUN_0034d3b4();
  FUN_0034b7e4();
  (*DAT_00658c00)();
  FUN_0034d3b4();
  FUN_0034b7e4();
  (*DAT_00658c00)();
  FUN_00350f9c();
  ((uint64_t (*)())(*((void **)(x12 + 0x10))))(x9_00 - x10_00,x8,x1);
  FUN_003514d0();
  i1 = FUN_00369584();
  if (i1 == 1) {
    FUN_003567e0();
    FUN_003504a0(x9 - x10);
    (*x9_01)();
    thunk_FUN_002298d4(1);
    FUN_003559d8();
    FUN_0031945c();
    FUN_00351318();
    FUN_00350878();
    (*x8_00)();
    FUN_0034f9c8();
    (*x8_01)();
  }
  else {
    FUN_0035478c();
    FUN_0034e024();
    (*x9_02)();
    thunk_FUN_002298d4(0);
    FUN_0031945c(arg3);
    FUN_00351318();
    FUN_00350c08();
    (*x8_02)();
    FUN_003508f0(*(uint64_t *)(x16 + 8));
    (*x8_03)();
  }
  FUN_0008e500(x30);
  return 0;
}


/* FUN_0027e698 @ 0x0027e698  (est. vspace_op_0027e698)
 * Ghidra: void vspace_op_0027e698(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027e698(void)
{
    uint8_t b1;
  
  FUN_00355684();
  b1 = FUN_00348c48();
  FUN_0034d264(b1,(uint64_t)0 /* s_uespemosmodnarodarenegylsetybdet_004e7a30._16_8_ */,
               b1 ^ (uint8_t)(uint64_t)0 /* s_uespemosmodnarodarenegylsetybdet_004e7a30._0_8_ */);
  vspace_op_0027e4ac(0 /* leftover-register arg */, 0 /* leftover-register arg */, 0 /* leftover-register arg */); /* padded 3 leftover-register arg(s) */
  FUN_001a8564();
  return 0;
}


/* FUN_0027e718 @ 0x0027e718  (est. vspace_op_0027e718)
 * Ghidra: void vspace_op_0027e718(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027e718(void)
{
    uint64_t (*x19)();;
    uint8_t st88[72];
  
  FUN_00354f10();
  FUN_001a84f4(st88);
  FUN_0034c444(st88);
  (*x19)();
  FUN_001a8564();
  return 0;
}


/* FUN_0027e778 @ 0x0027e778  (est. vspace_op_0027e778)
 * Ghidra: void vspace_op_0027e778(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027e778(void)
{
    int i1;
    uint64_t x8;
    int64_t x8_00;
    int64_t x8_01;
    uint64_t (*x8_02)();;
    uint64_t (*x9)();;
    int64_t x13;
    int64_t x16;
    int64_t x16_00;
    uint64_t v2;
    int64_t x22;
    uint64_t (*x24)();;
    uint64_t x30;
    uint64_t av3;
  
  FUN_0008e518();
  FUN_0035199c();
  FUN_003561a0();
  FUN_0034998c();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_00349068();
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8_01 + 0x40));
  FUN_003493ac();
  ((uint64_t (*)())(*((void **)(x13 + 0x10))))();
  FUN_003508b4();
  i1 = FUN_00369584();
  if (i1 != 1) {
    FUN_000aa46c();
    FUN_003511c0();
    (*x9)();
    FUN_00354d74();
    (*x24)();
    FUN_000e72b0(*(uint64_t *)(x16 + 8));
    (*x8_02)();
    v2 = *(uint64_t *)(x22 + 0x18);
  }
  else {
    v2 = *(uint64_t *)(x22 + 0x18);
    FUN_0034b518();
    ((uint64_t (*)())(*((void **)(x16_00 + 0x20))))(x8);
  }
  av3 = FUN_00350530();
  FUN_0031dc0c(av3,(0u /* hi: unspecified */),v2);
  av3 = FUN_00353a30();
  FUN_00369340(av3,(0u /* hi: unspecified */),i1 == 1);
  FUN_0008e500(x30);
  return 0;
}


/* FUN_0027e8e4 @ 0x0027e8e4  (est. vspace_op_0027e8e4)
 * Ghidra: void vspace_op_0027e8e4(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027e8e4(void)
{
    int i1;
    uint64_t (*fn2)();;
    uint64_t x8;
    int64_t x8_00;
    int64_t x8_01;
    uint64_t (*x8_02)();;
    uint64_t (*x8_03)();;
    uint64_t (*x9)();;
    int64_t x16;
    int64_t x16_00;
    uint64_t x30;
    uint64_t av3;
  
  FUN_0008e518();
  fn2 = (uint64_t (*)())FUN_0034d090();
  FUN_003499c8();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_003493ac();
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8_01 + 0x40));
  FUN_0034947c();
  FUN_00355464();
  (*x8_02)();
  FUN_00351414();
  i1 = FUN_00369584();
  if (i1 != 1) {
    FUN_0034b518();
    ((uint64_t (*)())(*((void **)(x16_00 + 0x20))))(x8);
  }
  else {
    FUN_0035478c();
    FUN_0034f4a4();
    (*x9)();
    FUN_003547f8();
    (*fn2)();
    FUN_00350a34(*(uint64_t *)(x16 + 8));
    (*x8_03)();
  }
  FUN_0034e0d4();
  FUN_0031dc0c();
  av3 = FUN_00353a30();
  FUN_00369340(av3,(0u /* hi: unspecified */),i1 == 1);
  FUN_0008e500(x30);
  return 0;
}


/* FUN_0027ea48 @ 0x0027ea48  (est. vspace_op_0027ea48)
 * Ghidra: void vspace_op_0027ea48(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027ea48(void)
{
    int i1;
    uint64_t x8;
    int64_t x8_00;
    int64_t x8_01;
    uint64_t (*x8_02)();;
    uint64_t (*x9)();;
    int64_t x13;
    int64_t x16;
    int64_t x16_00;
    uint64_t (*x22)();;
    uint64_t x30;
    uint64_t av2;
  
  FUN_0008e518();
  FUN_00354708();
  FUN_00349734();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_00349068();
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8_01 + 0x40));
  FUN_003493ac();
  ((uint64_t (*)())(*((void **)(x13 + 0x10))))();
  FUN_00350a34();
  i1 = FUN_00369584();
  if (i1 == 1) {
    FUN_0034b3c8();
    ((uint64_t (*)())(*((void **)(x16_00 + 0x20))))(x8);
    FUN_0034d904();
    FUN_0031dc0c();
    av2 = FUN_00353a30();
    FUN_00369340(av2,(0u /* hi: unspecified */),1);
  }
  else {
    FUN_000aa46c();
    FUN_003514a0();
    (*x9)();
    FUN_00354d74();
    (*x22)();
    FUN_003507d4(*(uint64_t *)(x16 + 8));
    (*x8_02)();
  }
  FUN_0008e500(x30);
  return 0;
}


/* FUN_0027ebac @ 0x0027ebac  (est. vspace_op_0027ebac)
 * Ghidra: void vspace_op_0027ebac(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027ebac(void)
{
    int i1;
    uint64_t x8;
    int64_t x8_00;
    int64_t x8_01;
    uint64_t (*x8_02)();;
    uint64_t (*x8_03)();;
    uint64_t (*x9)();;
    int64_t x16;
    int64_t x16_00;
    uint64_t (*x23)();;
    uint64_t x30;
    uint64_t av2;
  
  FUN_0008e518();
  FUN_00353d70();
  FUN_00355bdc();
  FUN_003499f0();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_003493ac();
  FUN_00349720();
  (*DAT_00658c00)(*(uint64_t *)(x8_01 + 0x40));
  FUN_0034947c();
  FUN_00355464();
  (*x8_02)();
  FUN_00350ab8();
  i1 = FUN_00369584();
  if (i1 == 1) {
    FUN_00352b50();
    FUN_0034e5cc();
    (*x9)();
    FUN_003547f8();
    (*x23)();
    FUN_003508b4(*(uint64_t *)(x16 + 8));
    (*x8_03)();
  }
  else {
    FUN_0034b804();
    ((uint64_t (*)())(*((void **)(x16_00 + 0x20))))(x8);
    FUN_0034d004(0);
    FUN_0031dc0c();
    av2 = FUN_00353a30();
    FUN_00369340(av2,(0u /* hi: unspecified */),0);
  }
  FUN_0008e500(x30);
  return 0;
}


/* FUN_0027ed08 @ 0x0027ed08  (est. vspace_op_0027ed08)
 * Ghidra: void vspace_op_0027ed08(uint64_t arg1,uint64_t arg2)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027ed08(uint64_t arg1,uint64_t arg2)
{
    uint64_t (*fn1)();;
    uint64_t * x20;
    uint64_t loc50;
    uint64_t us48;
    uint64_t us40;
    uint64_t us38;
    char loc30;
  
  loc30 = *(char *)(x20 + 4);
  us48 = x20[1];
  loc50 = *x20;
  us38 = x20[3];
  us40 = x20[2];
  if (loc30 != '\x01') {
    FUN_00310d98(&loc50,arg1);
    return 0;
  }
  FUN_003698b0(arg2,0x674330,0x66d208);
  fn1 = ((uint64_t (*)())(uintptr_t)0x27ed7c);
  (*fn1)();
}


/* FUN_0027ed7c @ 0x0027ed7c  (est. vspace_op_0027ed7c)
 * Ghidra: void vspace_op_0027ed7c(uint64_t arg1,int64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027ed7c(uint64_t arg1,int64_t arg2,uint64_t arg3)
{
    int i1;
    uint64_t x1;
    int64_t x8;
    int64_t x12;
    int64_t l2;
    uint8_t * p3;
  
  (*DAT_00658c00)(*(uint64_t *)(*(int64_t *)(arg2 + -8) + 0x40));
  p3 = STK + -(x8 + 0xfU & 0xfffffffffffffff0);
  ((uint64_t (*)())(*((void **)(x12 + 0x20))))(p3,x1,arg2);
  i1 = FUN_00369584(p3,arg2);
  if (i1 == 1) {
    l2 = *(int64_t *)(arg2 + 0x18);
    (**(uint64_t (**)())(*(int64_t *)(l2 + -8) + 0x20))(arg3,p3,l2);
    FUN_003698b0(arg3,l2,*(uint64_t *)(arg2 + 0x20));
  }
  else {
    (**(uint64_t (**)())(*(int64_t *)(*(int64_t *)(arg2 + 0x10) + -8) + 0x20))(arg1,p3);
  }
  return 0;
}


/* FUN_0027eebc @ 0x0027eebc  (est. vspace_op_0027eebc)
 * Ghidra: void vspace_op_0027eebc(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027eebc(void)
{
    int i1;
    int64_t l2;
    uint64_t x8;
    int64_t x8_00;
    int64_t x8_01;
    uint64_t (*x8_02)();;
    int64_t x12;
    int64_t x16;
    uint64_t v3;
    uint64_t (*fn4)();;
    uint64_t av5;
    uint64_t av6;
  
  av5 = FUN_00358fb4();
  l2 = av5;
  v3 = *(uint64_t *)(l2 + 0x18);
  FUN_00349b00();
  (*DAT_00658c00)(*(uint64_t *)(x8_00 + 0x40));
  FUN_00348f50();
  FUN_000a6f88();
  (*DAT_00658c00)(*(uint64_t *)(x8_01 + 0x40));
  FUN_00349068();
  FUN_00358df4(*(uint64_t *)(x12 + 0x10));
  (*x8_02)();
  FUN_000e72b0();
  i1 = FUN_00369584();
  if (i1 == 1) {
    fn4 = *(uint64_t (**)())(x16 + 0x20);
    av6 = FUN_00350738();
    (*fn4)(av6,(0u /* hi: unspecified */),v3);
    FUN_0035187c(v3,*(uint64_t *)(l2 + 0x20));
    FUN_0036993c();
    FUN_0035697c();
    FUN_00351a20();
    (*fn4)();
    FUN_0036986c();
  }
  else {
    (**(uint64_t (**)())(*(int64_t *)(*(int64_t *)(l2 + 0x10) + -8) + 0x20))(x8);
  }
  FUN_00355f04();
  FUN_00358fc8((0u /* hi: unspecified */));
  return 0;
}


/* FUN_0027f010 @ 0x0027f010  (est. vspace_op_0027f010)
 * Ghidra: void vspace_op_0027f010(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027f010(void)
{
    uint64_t (*fn1)();;
    uint64_t (*x8)();;
    int64_t x16;
    uint64_t x30;
    uint64_t av2;
  
  FUN_00084220();
  fn1 = (uint64_t (*)())FUN_00350b0c();
  FUN_0034a210();
  av2 = FUN_00027614();
  FUN_00350798(av2,(0u /* hi: unspecified */),av2,0x66c1c8);
  FUN_0031dc0c();
  FUN_00348ce8();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b0c4();
  (*fn1)();
  av2 = FUN_00351384();
  FUN_00369340(av2,(0u /* hi: unspecified */),0);
  FUN_0034e120(*(uint64_t *)(x16 + 0x20));
  (*x8)();
  FUN_00084234(x30);
  return 0;
}


/* FUN_0027f100 @ 0x0027f100  (est. vspace_op_0027f100)
 * Ghidra: void vspace_op_0027f100(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027f100(void)
{
    bool b1;
    uint32_t v2;
    uint32_t v3;
    uint16_t v4;
    uint16_t v5;
    uint64_t v6;
    int64_t l7;
    int64_t * x20;
    int64_t l8;
    uint64_t v9;
    int64_t l10;
    int64_t l11;
  
  l7 = *x20;
  v6 = *(uint64_t *)(l7 + 0x10);
  if (1 < v6) {
    l8 = 0;
    v9 = v6 - 1;
    l10 = v6 * 8 + 0x1c;
    l11 = 1;
    do {
      if ((*(uint64_t *)(l7 + 0x10) <= l11 - 1U) || (*(uint64_t *)(l7 + 0x10) <= v9)) {
        FUN_001afe4c((uint64_t)0 /* s_Fatal_error_005accd0 */,0xb,2,(uint64_t)0 /* s_Index_out_of_range_005cd940 */,0x12,2,
                     (uint64_t)0 /* s_Swift_ContiguousArrayBuffer_swif_005cd960 */,0x21,2,0x2b4,1);
      }
      v2 = *(uint32_t *)(l7 + l8 + 0x20);
      v4 = *(uint16_t *)(l7 + l8 + 0x24);
      v3 = *(uint32_t *)((uint16_t *)(l7 + l10) + -2);
      v5 = *(uint16_t *)(l7 + l10);
      v6 = FUN_003a261c(l7);
      *x20 = l7;
      if ((v6 & 1) == 0) {
        l7 = FUN_0019e644(l7);
      }
      *(uint32_t *)(l7 + l8 + 0x20) = v3;
      *(uint16_t *)(l7 + l8 + 0x24) = v5;
      *(uint32_t *)((uint16_t *)(l7 + l10) + -2) = v2;
      *(uint16_t *)(l7 + l10) = v4;
      *x20 = l7;
      v9 = v9 - 1;
      l10 = l10 + -8;
      l8 = l8 + 8;
      b1 = l11 < (int64_t)v9;
      l11 = l11 + 1;
    } while (b1);
  }
  return 0;
}


/* FUN_0027f448 @ 0x0027f448  (est. vspace_op_0027f448)
 * Ghidra: void vspace_op_0027f448(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027f448(void)
{
    int64_t l1;
    int64_t x16;
    int64_t x19;
    uint64_t av2;
  
  l1 = FUN_00351cc4();
  av2 = FUN_00350bd8(*(uint64_t *)(l1 + 0x18));
  FUN_00349748(av2,(0u /* hi: unspecified */),*(uint64_t *)(x19 + 0x10));
  FUN_00377824();
  FUN_00350404();
  ((uint64_t (*)())(*((void **)(x16 + 0x10))))();
  return 0;
}


/* FUN_0027f83c @ 0x0027f83c  (est. vspace_op_0027f83c)
 * Ghidra: void vspace_op_0027f83c(int64_t arg1,int64_t arg2)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027f83c(int64_t arg1,int64_t arg2)
{
    uint64_t v1;
    uint64_t (*fn2)();;
    int64_t l3;
    int64_t l4;
    uint64_t v5;
    int64_t l6;
  
  l6 = *(int64_t *)(arg2 + 0x10);
  l4 = *(int64_t *)(l6 + -8);
  ((uint64_t (*)())(*((void **)(l4 + 0x10))))(arg1);
  v5 = *(uint64_t *)(arg2 + 0x18);
  v1 = FUN_00027754(v5);
  fn2 = (uint64_t (*)())FUN_00310924();
  l3 = FUN_0031b858(0,l6,v5);
  (*fn2)(arg1 + *(int *)(l3 + 0x24),l6,v1);
  ((uint64_t (*)())(*((void **)(l4 + 8))))();
  return 0;
}


/* FUN_0027f94c @ 0x0027f94c  (est. vspace_op_0027f94c)
 * Ghidra: void vspace_op_0027f94c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027f94c(void)
{
    int64_t l1;
    int64_t x16;
    int64_t x19;
    uint64_t av2;
  
  l1 = FUN_00351cc4();
  av2 = FUN_00350bd8(*(uint64_t *)(l1 + 0x18));
  FUN_00349748(av2,(0u /* hi: unspecified */),*(uint64_t *)(x19 + 0x10));
  FUN_00377824();
  FUN_00350404();
  ((uint64_t (*)())(*((void **)(x16 + 0x10))))();
  return 0;
}


/* FUN_0027f9b0 @ 0x0027f9b0  (est. vspace_op_0027f9b0)
 * Ghidra: void vspace_op_0027f9b0(uint64_t arg1,uint64_t arg2,uint64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027f9b0(uint64_t arg1,uint64_t arg2,uint64_t arg3)
{
    int64_t x16;
  
  FUN_003503d0();
  FUN_00350bd8(arg3);
  FUN_00349748();
  FUN_00377824();
  FUN_00350404();
  ((uint64_t (*)())(*((void **)(x16 + 0x20))))();
  return 0;
}


/* FUN_0027fa8c @ 0x0027fa8c  (est. vspace_op_0027fa8c)
 * Ghidra: uint32_t vspace_op_0027fa8c(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint32_t vspace_op_0027fa8c(void)
{
    uint32_t v1;
    uint64_t ix3;
    uint64_t (*x8)();;
  
  FUN_0034b430();
  FUN_0035125c(ix3);
  FUN_0034c108();
  FUN_0035056c();
  FUN_00377824();
  FUN_00350c20();
  FUN_00377bec();
  FUN_00310b08();
  FUN_00350804();
  FUN_0034cfd4();
  v1 = (*x8)();
  return v1 & 1;
}


/* FUN_0027fb24 @ 0x0027fb24  (est. vspace_op_0027fb24)
 * Ghidra: void vspace_op_0027fb24(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027fb24(void)
{
    uint64_t (*xUNRECOVERED_JUMPTABLE)();;
    uint64_t v1;
    int64_t x21;
    uint64_t av2;
  
  FUN_0034a958();
  xUNRECOVERED_JUMPTABLE = (uint64_t (*)())FUN_0031945c();
  av2 = FUN_00350bd8(*(uint64_t *)(x21 + 0x18));
  FUN_00349748(av2,(0u /* hi: unspecified */),*(uint64_t *)(x21 + 0x10));
  v1 = FUN_00377824();
  FUN_00351c88(v1,v1);
  (*xUNRECOVERED_JUMPTABLE)();
  return 0;
}


/* FUN_0027fbfc @ 0x0027fbfc  (est. vspace_op_0027fbfc)
 * Ghidra: void vspace_op_0027fbfc(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027fbfc(void)
{
    int64_t l1;
    uint64_t (*x9)();;
    uint64_t (*x19)();;
    uint64_t v2;
    uint64_t x30;
    uint64_t av3;
  
  FUN_00084220();
  l1 = FUN_0034c084();
  v2 = *(uint64_t *)(l1 + 0x18);
  FUN_00352894(v2);
  FUN_00349748();
  FUN_003510a0();
  FUN_00377824();
  FUN_00351f10();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b05c();
  (*x19)();
  FUN_0034e72c();
  (*x9)();
  av3 = FUN_003504f4();
  vspace_op_0027f9b0(((uint64_t)av3), (0u /* hi: unspecified */),v2);
  FUN_00084234(x30);
  return 0;
}


/* FUN_0027fca0 @ 0x0027fca0  (est. vspace_op_0027fca0)
 * Ghidra: void vspace_op_0027fca0(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027fca0(void)
{
    uint64_t (*x9)();;
    int64_t x19;
    uint64_t v1;
    uint64_t av2;
  
  FUN_0034c084();
  FUN_00359490();
  FUN_00350bd8();
  v1 = *(uint64_t *)(x19 + 0x10);
  av2 = FUN_00349748();
  FUN_00377824(av2,(0u /* hi: unspecified */),v1);
  FUN_00351f10();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b0c4();
  FUN_0031e104();
  FUN_00350c50();
  FUN_0034ca28();
  (*x9)();
  FUN_00353f50();
  FUN_00350810();
  vspace_op_0027f9b0(0 /* leftover-register arg */, 0 /* leftover-register arg */, 0 /* leftover-register arg */); /* padded 3 leftover-register arg(s) */
  return 0;
}


/* FUN_0027fd38 @ 0x0027fd38  (est. vspace_op_0027fd38)
 * Ghidra: void vspace_op_0027fd38(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027fd38(void)
{
    uint64_t (*x9)();;
    uint64_t x30;
  
  FUN_00084220();
  FUN_0034c084();
  FUN_00359490();
  FUN_00352894();
  FUN_00349748();
  FUN_003508d8();
  FUN_00377824();
  FUN_00351f10();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b05c();
  FUN_00319658();
  FUN_0034e72c();
  FUN_00350c20();
  (*x9)();
  FUN_0035060c();
  vspace_op_0027f9b0(0 /* leftover-register arg */, 0 /* leftover-register arg */, 0 /* leftover-register arg */); /* padded 3 leftover-register arg(s) */
  FUN_00084234(x30);
  return 0;
}


/* FUN_0027fdd4 @ 0x0027fdd4  (est. vspace_op_0027fdd4)
 * Ghidra: void vspace_op_0027fdd4(uint64_t arg1,uint64_t arg2,int64_t arg3)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027fdd4(uint64_t arg1,uint64_t arg2,int64_t arg3)
{
    uint64_t (*fn1)();;
    int64_t x1;
    int64_t l2;
    uint64_t (*x9)();;
    uint64_t v3;
    uint64_t v4;
    uint64_t x30;
    uint64_t av5;
  
  FUN_00084220();
  l2 = arg3;
  FUN_00358f78();
  v3 = *(uint64_t *)(l2 + 0x18);
  FUN_00350bd8(v3);
  v4 = *(uint64_t *)(arg3 + 0x10);
  av5 = FUN_00349748();
  FUN_00377824(av5,(0u /* hi: unspecified */),v4);
  FUN_00351f10();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034b0c4();
  if (!SBORROW8(0,x1)) {
    FUN_00310ea4(v3);
    FUN_0034f634();
    FUN_0034cf74();
    (*x9)();
    FUN_0034e464();
    vspace_op_0027f9b0(0 /* leftover-register arg */, 0 /* leftover-register arg */, 0 /* leftover-register arg */); /* padded 3 leftover-register arg(s) */
    FUN_00084234(x30);
    return 0;
  }
  fn1 = ((uint64_t (*)())(uintptr_t)0x27fe84);
  (*fn1)();
}


/* FUN_0027fe84 @ 0x0027fe84  (est. vspace_op_0027fe84)
 * Ghidra: void vspace_op_0027fe84(void)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027fe84(void)
{
    uint64_t (*fn1)();;
    int64_t ix3;
    int64_t l2;
    uint64_t x8;
    uint64_t (*x8_00)();;
    uint64_t (*x9)();;
    int64_t x16;
    uint64_t v3;
    uint64_t v4;
    int64_t x28;
    uint64_t x30;
    uint64_t av5;
  
  FUN_0008e518();
  l2 = ix3;
  FUN_00359f48();
  v3 = *(uint64_t *)(l2 + 0x18);
  FUN_00350bd8(v3);
  v4 = *(uint64_t *)(ix3 + 0x10);
  av5 = FUN_0034a944();
  FUN_00377824(av5,(0u /* hi: unspecified */),v4);
  FUN_00352efc();
  FUN_00310d68();
  FUN_00348ce8();
  FUN_0007c1a4();
  (*DAT_00658c00)();
  FUN_0034aee4();
  if (!SBORROW8(0,x28)) {
    FUN_003195f8(v3);
    v3 = FUN_0034d934();
    FUN_003516d8(v3,-x28);
    (*x9)();
    (*DAT_00658c00)();
    FUN_0034e0c4();
    FUN_0031dc40();
    FUN_003536ac();
    FUN_000dbe70(x8,FUN_0031dc24);
    FUN_00358cf8();
    FUN_001d88fc();
    FUN_0035084c(*(uint64_t *)(x16 + 8));
    (*x8_00)();
    FUN_0008e500(x30);
    return 0;
  }
  fn1 = ((uint64_t (*)())(uintptr_t)0x27ffd8);
  (*fn1)();
}


/* FUN_0027ffd8 @ 0x0027ffd8  (est. vspace_op_0027ffd8)
 * Ghidra: void vspace_op_0027ffd8(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
 * Faithful mechanical transcription; registers preserved (x8/x16/x19-30),
 * vtable indirect calls kept, SoftwareBreakpoint->trap fns. Conf: low-med.
 * Notes: out-of-range callees extern; DAT_ globals extern; STK=stack. */
uint64_t vspace_op_0027ffd8(uint64_t arg1,uint64_t arg2,uint64_t arg3,uint64_t arg4)
{
    uint64_t v1;
    int64_t l2;
    int64_t x8;
    int64_t x12;
    uint64_t av3;
  
  v1 = FUN_00027754(arg4);
  av3 = FUN_00377824(0,v1,arg3,(uint64_t)&DAT_0060e208,(uint64_t)&DAT_0060e230);
  l2 = av3;
  (*DAT_00658c00)(*(int64_t *)(*(int64_t *)(l2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0,l2,
                  (0u /* hi: unspecified */),l2);
  ((uint64_t (*)())(*((void **)(x12 + 0x10))))((uint64_t)STK + -x8,arg2);
  vspace_op_0027f9b0(((uint64_t)arg1), (uint64_t)STK + -x8, ((uint64_t)arg3)); /* dropped 1 leftover-register arg(s) */
  return 0;
}


