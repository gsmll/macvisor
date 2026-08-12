/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses. All names are estimates unless string-matched.
 * Sub-range 5: 0x1d0000-0x1e0000 — scheduler/thread + Swift-runtime machinery.
 *
 * The region mixes (a) scheduler dispatch entry points (thunk pairs + dispatcher loops),
 * (b) Swift runtime collection/string/range helpers (ContiguousArray, UnsafeBufferPointer,
 * Range), and (c) fatal-error / bounds-assertion wrappers terminating in sk_001afe4c.
 * Bodies are faithful mechanical translations of the Ghidra decompiles: helper calls keep the
 * FUN_ address in the symbol (sk_<addr>); Ghidra register artifacts (uVar/local_/DAT_/s_) were
 * renamed to neutral pseudo-names to honour English-first (originals noted in comments where
 * meaningful). Confidence is low unless a string or the sched pattern matched.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

typedef uint64_t undefined8;
typedef uint8_t  undefined1;
typedef uint64_t undefined;
typedef uint8_t  byte;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint64_t ulong;
typedef unsigned long (*code)();
typedef struct { undefined8 _0_8_; undefined8 _8_8_; undefined8 _8_4_; } sk_c16_t;
typedef uint32_t undefined4;
typedef uint64_t undefined7;

/* concat: Ghidra CONCATnN register-pair combine (approximation for 64-bit). */
#define concat(a,b) ((uint64_t)((uint64_t)(a) << 32) | (uint32_t)(b))
/* ovf: Ghidra SCARRY8/SBORROW8/SUB168 overflow/borrow checks -> compiler intrinsic */
#define ovf __builtin_add_overflow

/* ---- External kernel/Swift-runtime helpers (FUN_ addr encoded in symbol) ---- */
extern unsigned long sk_00002534(); /* FUN_00002534 (out-of-slice helper) */
extern unsigned long sk_000026e8(); /* FUN_000026e8 (out-of-slice helper) */
extern unsigned long sk_00019858(); /* FUN_00019858 (out-of-slice helper) */
extern unsigned long sk_00027754(); /* FUN_00027754 (out-of-slice helper) */
extern unsigned long sk_00027788(); /* FUN_00027788 (out-of-slice helper) */
extern unsigned long sk_000277b8(); /* FUN_000277b8 (out-of-slice helper) */
extern unsigned long sk_000277e8(); /* FUN_000277e8 (out-of-slice helper) */
extern unsigned long sk_00027818(); /* FUN_00027818 (out-of-slice helper) */
extern unsigned long sk_00068e14(); /* FUN_00068e14 (out-of-slice helper) */
extern unsigned long sk_0006b3f4(); /* FUN_0006b3f4 (out-of-slice helper) */
extern unsigned long sk_0006b42c(); /* FUN_0006b42c (out-of-slice helper) */
extern unsigned long sk_0006b6f4(); /* FUN_0006b6f4 (out-of-slice helper) */
extern unsigned long sk_0006f6b4(); /* FUN_0006f6b4 (out-of-slice helper) */
extern unsigned long sk_00077888(); /* FUN_00077888 (out-of-slice helper) */
extern unsigned long sk_0007b384(); /* FUN_0007b384 (out-of-slice helper) */
extern unsigned long sk_0007c028(); /* FUN_0007c028 (out-of-slice helper) */
extern unsigned long sk_0007c1a4(); /* FUN_0007c1a4 (out-of-slice helper) */
extern unsigned long sk_0007c1c4(); /* FUN_0007c1c4 (out-of-slice helper) */
extern unsigned long sk_000839d8(); /* FUN_000839d8 (out-of-slice helper) */
extern unsigned long sk_000839f8(); /* FUN_000839f8 (out-of-slice helper) */
extern unsigned long sk_0008409c(); /* FUN_0008409c (out-of-slice helper) */
extern unsigned long sk_0008412c(); /* FUN_0008412c (out-of-slice helper) */
extern unsigned long sk_00084174(); /* FUN_00084174 (out-of-slice helper) */
extern unsigned long sk_00084180(); /* FUN_00084180 (out-of-slice helper) */
extern unsigned long sk_00084220(); /* FUN_00084220 (out-of-slice helper) */
extern unsigned long sk_00084234(); /* FUN_00084234 (out-of-slice helper) */
extern unsigned long sk_000867ec(); /* FUN_000867ec (out-of-slice helper) */
extern unsigned long sk_0008e388(); /* FUN_0008e388 (out-of-slice helper) */
extern unsigned long sk_0008e500(); /* FUN_0008e500 (out-of-slice helper) */
extern unsigned long sk_0008e518(); /* FUN_0008e518 (out-of-slice helper) */
extern unsigned long sk_0008f6c0(); /* FUN_0008f6c0 (out-of-slice helper) */
extern unsigned long sk_0009461c(); /* FUN_0009461c (out-of-slice helper) */
extern unsigned long sk_000a68c4(); /* FUN_000a68c4 (out-of-slice helper) */
extern unsigned long sk_000a68f4(); /* FUN_000a68f4 (out-of-slice helper) */
extern unsigned long sk_000a6f68(); /* FUN_000a6f68 (out-of-slice helper) */
extern unsigned long sk_000a6f88(); /* FUN_000a6f88 (out-of-slice helper) */
extern unsigned long sk_000b4390(); /* FUN_000b4390 (out-of-slice helper) */
extern unsigned long sk_000dbd0c(); /* FUN_000dbd0c (out-of-slice helper) */
extern unsigned long sk_000dbedc(); /* FUN_000dbedc (out-of-slice helper) */
extern unsigned long sk_000dbf08(); /* FUN_000dbf08 (out-of-slice helper) */
extern unsigned long sk_000e15d8(); /* FUN_000e15d8 (out-of-slice helper) */
extern unsigned long sk_000e72b0(); /* FUN_000e72b0 (out-of-slice helper) */
extern unsigned long sk_00100c38(); /* FUN_00100c38 (out-of-slice helper) */
extern unsigned long sk_00100efc(); /* FUN_00100efc (out-of-slice helper) */
extern unsigned long sk_00106e3c(); /* FUN_00106e3c (out-of-slice helper) */
extern unsigned long sk_00117cc4(); /* FUN_00117cc4 (out-of-slice helper) */
extern unsigned long sk_0014ae44(); /* FUN_0014ae44 (out-of-slice helper) */
extern unsigned long sk_0016186c(); /* FUN_0016186c (out-of-slice helper) */
extern unsigned long sk_00167404(); /* FUN_00167404 (out-of-slice helper) */
extern unsigned long sk_001679cc(); /* FUN_001679cc (out-of-slice helper) */
extern unsigned long sk_0019c44c(); /* FUN_0019c44c (out-of-slice helper) */
extern unsigned long sk_0019c53c(); /* FUN_0019c53c (out-of-slice helper) */
extern unsigned long sk_0019d15c(); /* FUN_0019d15c (out-of-slice helper) */
extern unsigned long sk_0019d6d0(); /* FUN_0019d6d0 (out-of-slice helper) */
extern unsigned long sk_0019dadc(); /* FUN_0019dadc (out-of-slice helper) */
extern unsigned long sk_0019e578(); /* FUN_0019e578 (out-of-slice helper) */
extern unsigned long sk_0019e5ec(); /* FUN_0019e5ec (out-of-slice helper) */
extern unsigned long sk_0019e66c(); /* FUN_0019e66c (out-of-slice helper) */
extern unsigned long sk_0019e690(); /* FUN_0019e690 (out-of-slice helper) */
extern unsigned long sk_0019ea20(); /* FUN_0019ea20 (out-of-slice helper) */
extern unsigned long sk_0019eb20(); /* FUN_0019eb20 (out-of-slice helper) */
extern unsigned long sk_0019ec24(); /* FUN_0019ec24 (out-of-slice helper) */
extern unsigned long sk_0019f1ec(); /* FUN_0019f1ec (out-of-slice helper) */
extern unsigned long sk_0019f370(); /* FUN_0019f370 (out-of-slice helper) */
extern unsigned long sk_0019f698(); /* FUN_0019f698 (out-of-slice helper) */
extern unsigned long sk_0019fa60(); /* FUN_0019fa60 (out-of-slice helper) */
extern unsigned long sk_0019fd10(); /* FUN_0019fd10 (out-of-slice helper) */
extern unsigned long sk_001a0158(); /* FUN_001a0158 (out-of-slice helper) */
extern unsigned long sk_001a0194(); /* FUN_001a0194 (out-of-slice helper) */
extern unsigned long sk_001a0414(); /* FUN_001a0414 (out-of-slice helper) */
extern unsigned long sk_001a04a4(); /* FUN_001a04a4 (out-of-slice helper) */
extern unsigned long sk_001a0734(); /* FUN_001a0734 (out-of-slice helper) */
extern unsigned long sk_001a0754(); /* FUN_001a0754 (out-of-slice helper) */
extern unsigned long sk_001a0774(); /* FUN_001a0774 (out-of-slice helper) */
extern unsigned long sk_001a0b30(); /* FUN_001a0b30 (out-of-slice helper) */
extern unsigned long sk_001a10d4(); /* FUN_001a10d4 (out-of-slice helper) */
extern unsigned long sk_001a10e4(); /* FUN_001a10e4 (out-of-slice helper) */
extern unsigned long sk_001a16e8(); /* FUN_001a16e8 (out-of-slice helper) */
extern unsigned long sk_001a1854(); /* FUN_001a1854 (out-of-slice helper) */
extern unsigned long sk_001a18f8(); /* FUN_001a18f8 (out-of-slice helper) */
extern unsigned long sk_001a26e0(); /* FUN_001a26e0 (out-of-slice helper) */
extern unsigned long sk_001a2740(); /* FUN_001a2740 (out-of-slice helper) */
extern unsigned long sk_001a27f0(); /* FUN_001a27f0 (out-of-slice helper) */
extern unsigned long sk_001a4554(); /* FUN_001a4554 (out-of-slice helper) */
extern unsigned long sk_001a5968(); /* FUN_001a5968 (out-of-slice helper) */
extern unsigned long sk_001a67bc(); /* FUN_001a67bc (out-of-slice helper) */
extern unsigned long sk_001a6ab8(); /* FUN_001a6ab8 (out-of-slice helper) */
extern unsigned long sk_001a76fc(); /* FUN_001a76fc (out-of-slice helper) */
extern unsigned long sk_001a7e30(); /* FUN_001a7e30 (out-of-slice helper) */
extern unsigned long sk_001a7e5c(); /* FUN_001a7e5c (out-of-slice helper) */
extern unsigned long sk_001a8564(); /* FUN_001a8564 (out-of-slice helper) */
extern unsigned long sk_001aeab4(); /* FUN_001aeab4 (out-of-slice helper) */
extern unsigned long sk_001afe4c(); /* FUN_001afe4c (out-of-slice helper) */
extern unsigned long sk_001b07b8(); /* FUN_001b07b8 (out-of-slice helper) */
extern unsigned long sk_001e3048(); /* FUN_001e3048 (out-of-slice helper) */
extern unsigned long sk_001e4cbc(); /* FUN_001e4cbc (out-of-slice helper) */
extern unsigned long sk_00229a3c(); /* FUN_00229a3c (out-of-slice helper) */
extern unsigned long sk_0023b7b8(); /* FUN_0023b7b8 (out-of-slice helper) */
extern unsigned long sk_00257f8c(); /* FUN_00257f8c (out-of-slice helper) */
extern unsigned long sk_0027743c(); /* FUN_0027743c (out-of-slice helper) */
extern unsigned long sk_00277474(); /* FUN_00277474 (out-of-slice helper) */
extern unsigned long sk_00277ba8(); /* FUN_00277ba8 (out-of-slice helper) */
extern unsigned long sk_00281a54(); /* FUN_00281a54 (out-of-slice helper) */
extern unsigned long sk_0028e8c0(); /* FUN_0028e8c0 (out-of-slice helper) */
extern unsigned long sk_00291d70(); /* FUN_00291d70 (out-of-slice helper) */
extern unsigned long sk_0029eb58(); /* FUN_0029eb58 (out-of-slice helper) */
extern unsigned long sk_002a0d50(); /* FUN_002a0d50 (out-of-slice helper) */
extern unsigned long sk_002a200c(); /* FUN_002a200c (out-of-slice helper) */
extern unsigned long sk_002a9ba8(); /* FUN_002a9ba8 (out-of-slice helper) */
extern unsigned long sk_002a9c14(); /* FUN_002a9c14 (out-of-slice helper) */
extern unsigned long sk_002ab8ac(); /* FUN_002ab8ac (out-of-slice helper) */
extern unsigned long sk_002bbcd8(); /* FUN_002bbcd8 (out-of-slice helper) */
extern unsigned long sk_002c6d00(); /* FUN_002c6d00 (out-of-slice helper) */
extern unsigned long sk_0031090c(); /* FUN_0031090c (out-of-slice helper) */
extern unsigned long sk_00310924(); /* FUN_00310924 (out-of-slice helper) */
extern unsigned long sk_00310ad4(); /* FUN_00310ad4 (out-of-slice helper) */
extern unsigned long sk_00310b38(); /* FUN_00310b38 (out-of-slice helper) */
extern unsigned long sk_00310d34(); /* FUN_00310d34 (out-of-slice helper) */
extern unsigned long sk_00310d68(); /* FUN_00310d68 (out-of-slice helper) */
extern unsigned long sk_00310d80(); /* FUN_00310d80 (out-of-slice helper) */
extern unsigned long sk_00310d98(); /* FUN_00310d98 (out-of-slice helper) */
extern unsigned long sk_00310dd8(); /* FUN_00310dd8 (out-of-slice helper) */
extern unsigned long sk_00310df0(); /* FUN_00310df0 (out-of-slice helper) */
extern unsigned long sk_00310e08(); /* FUN_00310e08 (out-of-slice helper) */
extern unsigned long sk_00310e20(); /* FUN_00310e20 (out-of-slice helper) */
extern unsigned long sk_00310f04(); /* FUN_00310f04 (out-of-slice helper) */
extern unsigned long sk_00310f34(); /* FUN_00310f34 (out-of-slice helper) */
extern unsigned long sk_00310f94(); /* FUN_00310f94 (out-of-slice helper) */
extern unsigned long sk_00310fc4(); /* FUN_00310fc4 (out-of-slice helper) */
extern unsigned long sk_00319218(); /* FUN_00319218 (out-of-slice helper) */
extern unsigned long sk_00319230(); /* FUN_00319230 (out-of-slice helper) */
extern unsigned long sk_003192a8(); /* FUN_003192a8 (out-of-slice helper) */
extern unsigned long sk_003192d8(); /* FUN_003192d8 (out-of-slice helper) */
extern unsigned long sk_00319308(); /* FUN_00319308 (out-of-slice helper) */
extern unsigned long sk_0031945c(); /* FUN_0031945c (out-of-slice helper) */
extern unsigned long sk_0031948c(); /* FUN_0031948c (out-of-slice helper) */
extern unsigned long sk_003195c8(); /* FUN_003195c8 (out-of-slice helper) */
extern unsigned long sk_00319628(); /* FUN_00319628 (out-of-slice helper) */
extern unsigned long sk_00319658(); /* FUN_00319658 (out-of-slice helper) */
extern unsigned long sk_003196e8(); /* FUN_003196e8 (out-of-slice helper) */
extern unsigned long sk_00319808(); /* FUN_00319808 (out-of-slice helper) */
extern unsigned long sk_00319a4c(); /* FUN_00319a4c (out-of-slice helper) */
extern unsigned long sk_0031a14c(); /* FUN_0031a14c (out-of-slice helper) */
extern unsigned long sk_0031a17c(); /* FUN_0031a17c (out-of-slice helper) */
extern unsigned long sk_0031a1ac(); /* FUN_0031a1ac (out-of-slice helper) */
extern unsigned long sk_0031a5dc(); /* FUN_0031a5dc (out-of-slice helper) */
extern unsigned long sk_0031a60c(); /* FUN_0031a60c (out-of-slice helper) */
extern unsigned long sk_0031a63c(); /* FUN_0031a63c (out-of-slice helper) */
extern unsigned long sk_0031a66c(); /* FUN_0031a66c (out-of-slice helper) */
extern unsigned long sk_0031a69c(); /* FUN_0031a69c (out-of-slice helper) */
extern unsigned long sk_0031a6cc(); /* FUN_0031a6cc (out-of-slice helper) */
extern unsigned long sk_0031a6fc(); /* FUN_0031a6fc (out-of-slice helper) */
extern unsigned long sk_0031a96c(); /* FUN_0031a96c (out-of-slice helper) */
extern unsigned long sk_0031a99c(); /* FUN_0031a99c (out-of-slice helper) */
extern unsigned long sk_0031a9cc(); /* FUN_0031a9cc (out-of-slice helper) */
extern unsigned long sk_0031a9fc(); /* FUN_0031a9fc (out-of-slice helper) */
extern unsigned long sk_0031aa2c(); /* FUN_0031aa2c (out-of-slice helper) */
extern unsigned long sk_0031ac9c(); /* FUN_0031ac9c (out-of-slice helper) */
extern unsigned long sk_0031accc(); /* FUN_0031accc (out-of-slice helper) */
extern unsigned long sk_0031acfc(); /* FUN_0031acfc (out-of-slice helper) */
extern unsigned long sk_0031ad2c(); /* FUN_0031ad2c (out-of-slice helper) */
extern unsigned long sk_0031ad5c(); /* FUN_0031ad5c (out-of-slice helper) */
extern unsigned long sk_0031ae4c(); /* FUN_0031ae4c (out-of-slice helper) */
extern unsigned long sk_0031af6c(); /* FUN_0031af6c (out-of-slice helper) */
extern unsigned long sk_0031afcc(); /* FUN_0031afcc (out-of-slice helper) */
extern unsigned long sk_0031affc(); /* FUN_0031affc (out-of-slice helper) */
extern unsigned long sk_0031b080(); /* FUN_0031b080 (out-of-slice helper) */
extern unsigned long sk_0031b0bc(); /* FUN_0031b0bc (out-of-slice helper) */
extern unsigned long sk_0031b0ec(); /* FUN_0031b0ec (out-of-slice helper) */
extern unsigned long sk_0031b110(); /* FUN_0031b110 (out-of-slice helper) */
extern unsigned long sk_0031b140(); /* FUN_0031b140 (out-of-slice helper) */
extern unsigned long sk_0031b164(); /* FUN_0031b164 (out-of-slice helper) */
extern unsigned long sk_0031b194(); /* FUN_0031b194 (out-of-slice helper) */
extern unsigned long sk_0031b1c4(); /* FUN_0031b1c4 (out-of-slice helper) */
extern unsigned long sk_0031b1f4(); /* FUN_0031b1f4 (out-of-slice helper) */
extern unsigned long sk_0031de7c(); /* FUN_0031de7c (out-of-slice helper) */
extern unsigned long sk_0031e4e0(); /* FUN_0031e4e0 (out-of-slice helper) */
extern unsigned long sk_00344ca8(); /* FUN_00344ca8 (out-of-slice helper) */
extern unsigned long sk_00344e54(); /* FUN_00344e54 (out-of-slice helper) */
extern unsigned long sk_00346774(); /* FUN_00346774 (out-of-slice helper) */
extern unsigned long sk_003469a8(); /* FUN_003469a8 (out-of-slice helper) */
extern unsigned long sk_00347040(); /* FUN_00347040 (out-of-slice helper) */
extern unsigned long sk_00347d60(); /* FUN_00347d60 (out-of-slice helper) */
extern unsigned long sk_00347da8(); /* FUN_00347da8 (out-of-slice helper) */
extern unsigned long sk_00348034(); /* FUN_00348034 (out-of-slice helper) */
extern unsigned long sk_003480ac(); /* FUN_003480ac (out-of-slice helper) */
extern unsigned long sk_00348284(); /* FUN_00348284 (out-of-slice helper) */
extern unsigned long sk_00348304(); /* FUN_00348304 (out-of-slice helper) */
extern unsigned long sk_00348384(); /* FUN_00348384 (out-of-slice helper) */
extern unsigned long sk_003483c4(); /* FUN_003483c4 (out-of-slice helper) */
extern unsigned long sk_00348508(); /* FUN_00348508 (out-of-slice helper) */
extern unsigned long sk_00348730(); /* FUN_00348730 (out-of-slice helper) */
extern unsigned long sk_003487a4(); /* FUN_003487a4 (out-of-slice helper) */
extern unsigned long sk_003488bc(); /* FUN_003488bc (out-of-slice helper) */
extern unsigned long sk_003488f4(); /* FUN_003488f4 (out-of-slice helper) */
extern unsigned long sk_0034893c(); /* FUN_0034893c (out-of-slice helper) */
extern unsigned long sk_003489a8(); /* FUN_003489a8 (out-of-slice helper) */
extern unsigned long sk_003489c0(); /* FUN_003489c0 (out-of-slice helper) */
extern unsigned long sk_003489dc(); /* FUN_003489dc (out-of-slice helper) */
extern unsigned long sk_00348a18(); /* FUN_00348a18 (out-of-slice helper) */
extern unsigned long sk_00348a34(); /* FUN_00348a34 (out-of-slice helper) */
extern unsigned long sk_00348a9c(); /* FUN_00348a9c (out-of-slice helper) */
extern unsigned long sk_00348abc(); /* FUN_00348abc (out-of-slice helper) */
extern unsigned long sk_00348b5c(); /* FUN_00348b5c (out-of-slice helper) */
extern unsigned long sk_00348b7c(); /* FUN_00348b7c (out-of-slice helper) */
extern unsigned long sk_00348b94(); /* FUN_00348b94 (out-of-slice helper) */
extern unsigned long sk_00348bbc(); /* FUN_00348bbc (out-of-slice helper) */
extern unsigned long sk_00348bd8(); /* FUN_00348bd8 (out-of-slice helper) */
extern unsigned long sk_00348bf8(); /* FUN_00348bf8 (out-of-slice helper) */
extern unsigned long sk_00348c48(); /* FUN_00348c48 (out-of-slice helper) */
extern unsigned long sk_00348cd0(); /* FUN_00348cd0 (out-of-slice helper) */
extern unsigned long sk_00348ce8(); /* FUN_00348ce8 (out-of-slice helper) */
extern unsigned long sk_00348d00(); /* FUN_00348d00 (out-of-slice helper) */
extern unsigned long sk_00348d18(); /* FUN_00348d18 (out-of-slice helper) */
extern unsigned long sk_00348d30(); /* FUN_00348d30 (out-of-slice helper) */
extern unsigned long sk_00348d4c(); /* FUN_00348d4c (out-of-slice helper) */
extern unsigned long sk_00348d64(); /* FUN_00348d64 (out-of-slice helper) */
extern unsigned long sk_00348d7c(); /* FUN_00348d7c (out-of-slice helper) */
extern unsigned long sk_00348d94(); /* FUN_00348d94 (out-of-slice helper) */
extern unsigned long sk_00348dd8(); /* FUN_00348dd8 (out-of-slice helper) */
extern unsigned long sk_00348e00(); /* FUN_00348e00 (out-of-slice helper) */
extern unsigned long sk_00348e18(); /* FUN_00348e18 (out-of-slice helper) */
extern unsigned long sk_00348e30(); /* FUN_00348e30 (out-of-slice helper) */
extern unsigned long sk_00348e60(); /* FUN_00348e60 (out-of-slice helper) */
extern unsigned long sk_00348e9c(); /* FUN_00348e9c (out-of-slice helper) */
extern unsigned long sk_00348f14(); /* FUN_00348f14 (out-of-slice helper) */
extern unsigned long sk_00348f38(); /* FUN_00348f38 (out-of-slice helper) */
extern unsigned long sk_00348f50(); /* FUN_00348f50 (out-of-slice helper) */
extern unsigned long sk_00348fd8(); /* FUN_00348fd8 (out-of-slice helper) */
extern unsigned long sk_003490b8(); /* FUN_003490b8 (out-of-slice helper) */
extern unsigned long sk_003490ec(); /* FUN_003490ec (out-of-slice helper) */
extern unsigned long sk_0034911c(); /* FUN_0034911c (out-of-slice helper) */
extern unsigned long sk_0034921c(); /* FUN_0034921c (out-of-slice helper) */
extern unsigned long sk_00349234(); /* FUN_00349234 (out-of-slice helper) */
extern unsigned long sk_0034926c(); /* FUN_0034926c (out-of-slice helper) */
extern unsigned long sk_003492ac(); /* FUN_003492ac (out-of-slice helper) */
extern unsigned long sk_003493c4(); /* FUN_003493c4 (out-of-slice helper) */
extern unsigned long sk_00349410(); /* FUN_00349410 (out-of-slice helper) */
extern unsigned long sk_003494d4(); /* FUN_003494d4 (out-of-slice helper) */
extern unsigned long sk_00349530(); /* FUN_00349530 (out-of-slice helper) */
extern unsigned long sk_00349618(); /* FUN_00349618 (out-of-slice helper) */
extern unsigned long sk_00349644(); /* FUN_00349644 (out-of-slice helper) */
extern unsigned long sk_00349720(); /* FUN_00349720 (out-of-slice helper) */
extern unsigned long sk_00349748(); /* FUN_00349748 (out-of-slice helper) */
extern unsigned long sk_003497a0(); /* FUN_003497a0 (out-of-slice helper) */
extern unsigned long sk_003497b4(); /* FUN_003497b4 (out-of-slice helper) */
extern unsigned long sk_00349830(); /* FUN_00349830 (out-of-slice helper) */
extern unsigned long sk_0034987c(); /* FUN_0034987c (out-of-slice helper) */
extern unsigned long sk_003498c4(); /* FUN_003498c4 (out-of-slice helper) */
extern unsigned long sk_003498dc(); /* FUN_003498dc (out-of-slice helper) */
extern unsigned long sk_00349910(); /* FUN_00349910 (out-of-slice helper) */
extern unsigned long sk_0034998c(); /* FUN_0034998c (out-of-slice helper) */
extern unsigned long sk_003499c8(); /* FUN_003499c8 (out-of-slice helper) */
extern unsigned long sk_003499f0(); /* FUN_003499f0 (out-of-slice helper) */
extern unsigned long sk_00349a18(); /* FUN_00349a18 (out-of-slice helper) */
extern unsigned long sk_00349a2c(); /* FUN_00349a2c (out-of-slice helper) */
extern unsigned long sk_00349a54(); /* FUN_00349a54 (out-of-slice helper) */
extern unsigned long sk_00349b3c(); /* FUN_00349b3c (out-of-slice helper) */
extern unsigned long sk_00349b88(); /* FUN_00349b88 (out-of-slice helper) */
extern unsigned long sk_00349c2c(); /* FUN_00349c2c (out-of-slice helper) */
extern unsigned long sk_00349c70(); /* FUN_00349c70 (out-of-slice helper) */
extern unsigned long sk_00349ea0(); /* FUN_00349ea0 (out-of-slice helper) */
extern unsigned long sk_00349ef4(); /* FUN_00349ef4 (out-of-slice helper) */
extern unsigned long sk_00349f08(); /* FUN_00349f08 (out-of-slice helper) */
extern unsigned long sk_00349f3c(); /* FUN_00349f3c (out-of-slice helper) */
extern unsigned long sk_0034a1b0(); /* FUN_0034a1b0 (out-of-slice helper) */
extern unsigned long sk_0034a1c8(); /* FUN_0034a1c8 (out-of-slice helper) */
extern unsigned long sk_0034a210(); /* FUN_0034a210 (out-of-slice helper) */
extern unsigned long sk_0034a2c0(); /* FUN_0034a2c0 (out-of-slice helper) */
extern unsigned long sk_0034a3c4(); /* FUN_0034a3c4 (out-of-slice helper) */
extern unsigned long sk_0034a3d8(); /* FUN_0034a3d8 (out-of-slice helper) */
extern unsigned long sk_0034a414(); /* FUN_0034a414 (out-of-slice helper) */
extern unsigned long sk_0034a450(); /* FUN_0034a450 (out-of-slice helper) */
extern unsigned long sk_0034a464(); /* FUN_0034a464 (out-of-slice helper) */
extern unsigned long sk_0034a4f8(); /* FUN_0034a4f8 (out-of-slice helper) */
extern unsigned long sk_0034a528(); /* FUN_0034a528 (out-of-slice helper) */
extern unsigned long sk_0034a5c8(); /* FUN_0034a5c8 (out-of-slice helper) */
extern unsigned long sk_0034a654(); /* FUN_0034a654 (out-of-slice helper) */
extern unsigned long sk_0034a6b0(); /* FUN_0034a6b0 (out-of-slice helper) */
extern unsigned long sk_0034a944(); /* FUN_0034a944 (out-of-slice helper) */
extern unsigned long sk_0034a980(); /* FUN_0034a980 (out-of-slice helper) */
extern unsigned long sk_0034a9c0(); /* FUN_0034a9c0 (out-of-slice helper) */
extern unsigned long sk_0034a9e8(); /* FUN_0034a9e8 (out-of-slice helper) */
extern unsigned long sk_0034aa14(); /* FUN_0034aa14 (out-of-slice helper) */
extern unsigned long sk_0034aa28(); /* FUN_0034aa28 (out-of-slice helper) */
extern unsigned long sk_0034aa9c(); /* FUN_0034aa9c (out-of-slice helper) */
extern unsigned long sk_0034aac4(); /* FUN_0034aac4 (out-of-slice helper) */
extern unsigned long sk_0034aadc(); /* FUN_0034aadc (out-of-slice helper) */
extern unsigned long sk_0034ab10(); /* FUN_0034ab10 (out-of-slice helper) */
extern unsigned long sk_0034ab20(); /* FUN_0034ab20 (out-of-slice helper) */
extern unsigned long sk_0034abb0(); /* FUN_0034abb0 (out-of-slice helper) */
extern unsigned long sk_0034ac00(); /* FUN_0034ac00 (out-of-slice helper) */
extern unsigned long sk_0034ac28(); /* FUN_0034ac28 (out-of-slice helper) */
extern unsigned long sk_0034ac8c(); /* FUN_0034ac8c (out-of-slice helper) */
extern unsigned long sk_0034acf0(); /* FUN_0034acf0 (out-of-slice helper) */
extern unsigned long sk_0034ad10(); /* FUN_0034ad10 (out-of-slice helper) */
extern unsigned long sk_0034ae30(); /* FUN_0034ae30 (out-of-slice helper) */
extern unsigned long sk_0034ae58(); /* FUN_0034ae58 (out-of-slice helper) */
extern unsigned long sk_0034ae94(); /* FUN_0034ae94 (out-of-slice helper) */
extern unsigned long sk_0034aea8(); /* FUN_0034aea8 (out-of-slice helper) */
extern unsigned long sk_0034aee4(); /* FUN_0034aee4 (out-of-slice helper) */
extern unsigned long sk_0034af20(); /* FUN_0034af20 (out-of-slice helper) */
extern unsigned long sk_0034af60(); /* FUN_0034af60 (out-of-slice helper) */
extern unsigned long sk_0034affc(); /* FUN_0034affc (out-of-slice helper) */
extern unsigned long sk_0034b05c(); /* FUN_0034b05c (out-of-slice helper) */
extern unsigned long sk_0034b07c(); /* FUN_0034b07c (out-of-slice helper) */
extern unsigned long sk_0034b0b4(); /* FUN_0034b0b4 (out-of-slice helper) */
extern unsigned long sk_0034b0c4(); /* FUN_0034b0c4 (out-of-slice helper) */
extern unsigned long sk_0034b0d4(); /* FUN_0034b0d4 (out-of-slice helper) */
extern unsigned long sk_0034b128(); /* FUN_0034b128 (out-of-slice helper) */
extern unsigned long sk_0034b13c(); /* FUN_0034b13c (out-of-slice helper) */
extern unsigned long sk_0034b164(); /* FUN_0034b164 (out-of-slice helper) */
extern unsigned long sk_0034b250(); /* FUN_0034b250 (out-of-slice helper) */
extern unsigned long sk_0034b278(); /* FUN_0034b278 (out-of-slice helper) */
extern unsigned long sk_0034b2a8(); /* FUN_0034b2a8 (out-of-slice helper) */
extern unsigned long sk_0034b2c8(); /* FUN_0034b2c8 (out-of-slice helper) */
extern unsigned long sk_0034b2f8(); /* FUN_0034b2f8 (out-of-slice helper) */
extern unsigned long sk_0034b308(); /* FUN_0034b308 (out-of-slice helper) */
extern unsigned long sk_0034b318(); /* FUN_0034b318 (out-of-slice helper) */
extern unsigned long sk_0034b348(); /* FUN_0034b348 (out-of-slice helper) */
extern unsigned long sk_0034b358(); /* FUN_0034b358 (out-of-slice helper) */
extern unsigned long sk_0034b3c8(); /* FUN_0034b3c8 (out-of-slice helper) */
extern unsigned long sk_0034b3d8(); /* FUN_0034b3d8 (out-of-slice helper) */
extern unsigned long sk_0034b3e8(); /* FUN_0034b3e8 (out-of-slice helper) */
extern unsigned long sk_0034b430(); /* FUN_0034b430 (out-of-slice helper) */
extern unsigned long sk_0034b460(); /* FUN_0034b460 (out-of-slice helper) */
extern unsigned long sk_0034b470(); /* FUN_0034b470 (out-of-slice helper) */
extern unsigned long sk_0034b4c0(); /* FUN_0034b4c0 (out-of-slice helper) */
extern unsigned long sk_0034b508(); /* FUN_0034b508 (out-of-slice helper) */
extern unsigned long sk_0034b540(); /* FUN_0034b540 (out-of-slice helper) */
extern unsigned long sk_0034b668(); /* FUN_0034b668 (out-of-slice helper) */
extern unsigned long sk_0034b708(); /* FUN_0034b708 (out-of-slice helper) */
extern unsigned long sk_0034b744(); /* FUN_0034b744 (out-of-slice helper) */
extern unsigned long sk_0034b758(); /* FUN_0034b758 (out-of-slice helper) */
extern unsigned long sk_0034b778(); /* FUN_0034b778 (out-of-slice helper) */
extern unsigned long sk_0034b7e4(); /* FUN_0034b7e4 (out-of-slice helper) */
extern unsigned long sk_0034b804(); /* FUN_0034b804 (out-of-slice helper) */
extern unsigned long sk_0034b85c(); /* FUN_0034b85c (out-of-slice helper) */
extern unsigned long sk_0034b87c(); /* FUN_0034b87c (out-of-slice helper) */
extern unsigned long sk_0034b8cc(); /* FUN_0034b8cc (out-of-slice helper) */
extern unsigned long sk_0034b960(); /* FUN_0034b960 (out-of-slice helper) */
extern unsigned long sk_0034ba28(); /* FUN_0034ba28 (out-of-slice helper) */
extern unsigned long sk_0034ba68(); /* FUN_0034ba68 (out-of-slice helper) */
extern unsigned long sk_0034ba78(); /* FUN_0034ba78 (out-of-slice helper) */
extern unsigned long sk_0034baa8(); /* FUN_0034baa8 (out-of-slice helper) */
extern unsigned long sk_0034bc80(); /* FUN_0034bc80 (out-of-slice helper) */
extern unsigned long sk_0034bc94(); /* FUN_0034bc94 (out-of-slice helper) */
extern unsigned long sk_0034bccc(); /* FUN_0034bccc (out-of-slice helper) */
extern unsigned long sk_0034bcdc(); /* FUN_0034bcdc (out-of-slice helper) */
extern unsigned long sk_0034bcf0(); /* FUN_0034bcf0 (out-of-slice helper) */
extern unsigned long sk_0034bd30(); /* FUN_0034bd30 (out-of-slice helper) */
extern unsigned long sk_0034bddc(); /* FUN_0034bddc (out-of-slice helper) */
extern unsigned long sk_0034be0c(); /* FUN_0034be0c (out-of-slice helper) */
extern unsigned long sk_0034be1c(); /* FUN_0034be1c (out-of-slice helper) */
extern unsigned long sk_0034be70(); /* FUN_0034be70 (out-of-slice helper) */
extern unsigned long sk_0034be94(); /* FUN_0034be94 (out-of-slice helper) */
extern unsigned long sk_0034bec4(); /* FUN_0034bec4 (out-of-slice helper) */
extern unsigned long sk_0034bf1c(); /* FUN_0034bf1c (out-of-slice helper) */
extern unsigned long sk_0034c074(); /* FUN_0034c074 (out-of-slice helper) */
extern unsigned long sk_0034c084(); /* FUN_0034c084 (out-of-slice helper) */
extern unsigned long sk_0034c2b4(); /* FUN_0034c2b4 (out-of-slice helper) */
extern unsigned long sk_0034c2c8(); /* FUN_0034c2c8 (out-of-slice helper) */
extern unsigned long sk_0034c2d8(); /* FUN_0034c2d8 (out-of-slice helper) */
extern unsigned long sk_0034c2f8(); /* FUN_0034c2f8 (out-of-slice helper) */
extern unsigned long sk_0034c3b4(); /* FUN_0034c3b4 (out-of-slice helper) */
extern unsigned long sk_0034c3c4(); /* FUN_0034c3c4 (out-of-slice helper) */
extern unsigned long sk_0034c3d4(); /* FUN_0034c3d4 (out-of-slice helper) */
extern unsigned long sk_0034c454(); /* FUN_0034c454 (out-of-slice helper) */
extern unsigned long sk_0034c4bc(); /* FUN_0034c4bc (out-of-slice helper) */
extern unsigned long sk_0034c54c(); /* FUN_0034c54c (out-of-slice helper) */
extern unsigned long sk_0034c55c(); /* FUN_0034c55c (out-of-slice helper) */
extern unsigned long sk_0034c59c(); /* FUN_0034c59c (out-of-slice helper) */
extern unsigned long sk_0034c5dc(); /* FUN_0034c5dc (out-of-slice helper) */
extern unsigned long sk_0034c664(); /* FUN_0034c664 (out-of-slice helper) */
extern unsigned long sk_0034c6b4(); /* FUN_0034c6b4 (out-of-slice helper) */
extern unsigned long sk_0034c754(); /* FUN_0034c754 (out-of-slice helper) */
extern unsigned long sk_0034c8b8(); /* FUN_0034c8b8 (out-of-slice helper) */
extern unsigned long sk_0034c8e0(); /* FUN_0034c8e0 (out-of-slice helper) */
extern unsigned long sk_0034c920(); /* FUN_0034c920 (out-of-slice helper) */
extern unsigned long sk_0034c9f8(); /* FUN_0034c9f8 (out-of-slice helper) */
extern unsigned long sk_0034ca08(); /* FUN_0034ca08 (out-of-slice helper) */
extern unsigned long sk_0034ca18(); /* FUN_0034ca18 (out-of-slice helper) */
extern unsigned long sk_0034cd18(); /* FUN_0034cd18 (out-of-slice helper) */
extern unsigned long sk_0034cd7c(); /* FUN_0034cd7c (out-of-slice helper) */
extern unsigned long sk_0034ce68(); /* FUN_0034ce68 (out-of-slice helper) */
extern unsigned long sk_0034ce78(); /* FUN_0034ce78 (out-of-slice helper) */
extern unsigned long sk_0034cf14(); /* FUN_0034cf14 (out-of-slice helper) */
extern unsigned long sk_0034cf34(); /* FUN_0034cf34 (out-of-slice helper) */
extern unsigned long sk_0034cf94(); /* FUN_0034cf94 (out-of-slice helper) */
extern unsigned long sk_0034cfa4(); /* FUN_0034cfa4 (out-of-slice helper) */
extern unsigned long sk_0034cff4(); /* FUN_0034cff4 (out-of-slice helper) */
extern unsigned long sk_0034d024(); /* FUN_0034d024 (out-of-slice helper) */
extern unsigned long sk_0034d180(); /* FUN_0034d180 (out-of-slice helper) */
extern unsigned long sk_0034d190(); /* FUN_0034d190 (out-of-slice helper) */
extern unsigned long sk_0034d254(); /* FUN_0034d254 (out-of-slice helper) */
extern unsigned long sk_0034d2a4(); /* FUN_0034d2a4 (out-of-slice helper) */
extern unsigned long sk_0034d2b4(); /* FUN_0034d2b4 (out-of-slice helper) */
extern unsigned long sk_0034d334(); /* FUN_0034d334 (out-of-slice helper) */
extern unsigned long sk_0034d344(); /* FUN_0034d344 (out-of-slice helper) */
extern unsigned long sk_0034d364(); /* FUN_0034d364 (out-of-slice helper) */
extern unsigned long sk_0034d394(); /* FUN_0034d394 (out-of-slice helper) */
extern unsigned long sk_0034d3c4(); /* FUN_0034d3c4 (out-of-slice helper) */
extern unsigned long sk_0034d3f4(); /* FUN_0034d3f4 (out-of-slice helper) */
extern unsigned long sk_0034d434(); /* FUN_0034d434 (out-of-slice helper) */
extern unsigned long sk_0034d464(); /* FUN_0034d464 (out-of-slice helper) */
extern unsigned long sk_0034d49c(); /* FUN_0034d49c (out-of-slice helper) */
extern unsigned long sk_0034d574(); /* FUN_0034d574 (out-of-slice helper) */
extern unsigned long sk_0034d6d8(); /* FUN_0034d6d8 (out-of-slice helper) */
extern unsigned long sk_0034d734(); /* FUN_0034d734 (out-of-slice helper) */
extern unsigned long sk_0034d758(); /* FUN_0034d758 (out-of-slice helper) */
extern unsigned long sk_0034d7cc(); /* FUN_0034d7cc (out-of-slice helper) */
extern unsigned long sk_0034d7dc(); /* FUN_0034d7dc (out-of-slice helper) */
extern unsigned long sk_0034d844(); /* FUN_0034d844 (out-of-slice helper) */
extern unsigned long sk_0034d868(); /* FUN_0034d868 (out-of-slice helper) */
extern unsigned long sk_0034d8f4(); /* FUN_0034d8f4 (out-of-slice helper) */
extern unsigned long sk_0034d9f8(); /* FUN_0034d9f8 (out-of-slice helper) */
extern unsigned long sk_0034da38(); /* FUN_0034da38 (out-of-slice helper) */
extern unsigned long sk_0034da88(); /* FUN_0034da88 (out-of-slice helper) */
extern unsigned long sk_0034da98(); /* FUN_0034da98 (out-of-slice helper) */
extern unsigned long sk_0034dad8(); /* FUN_0034dad8 (out-of-slice helper) */
extern unsigned long sk_0034dae8(); /* FUN_0034dae8 (out-of-slice helper) */
extern unsigned long sk_0034db28(); /* FUN_0034db28 (out-of-slice helper) */
extern unsigned long sk_0034dba8(); /* FUN_0034dba8 (out-of-slice helper) */
extern unsigned long sk_0034dbb8(); /* FUN_0034dbb8 (out-of-slice helper) */
extern unsigned long sk_0034dbc8(); /* FUN_0034dbc8 (out-of-slice helper) */
extern unsigned long sk_0034dc3c(); /* FUN_0034dc3c (out-of-slice helper) */
extern unsigned long sk_0034dccc(); /* FUN_0034dccc (out-of-slice helper) */
extern unsigned long sk_0034dcfc(); /* FUN_0034dcfc (out-of-slice helper) */
extern unsigned long sk_0034de64(); /* FUN_0034de64 (out-of-slice helper) */
extern unsigned long sk_0034de8c(); /* FUN_0034de8c (out-of-slice helper) */
extern unsigned long sk_0034ded4(); /* FUN_0034ded4 (out-of-slice helper) */
extern unsigned long sk_0034df24(); /* FUN_0034df24 (out-of-slice helper) */
extern unsigned long sk_0034df54(); /* FUN_0034df54 (out-of-slice helper) */
extern unsigned long sk_0034dfe4(); /* FUN_0034dfe4 (out-of-slice helper) */
extern unsigned long sk_0034e044(); /* FUN_0034e044 (out-of-slice helper) */
extern unsigned long sk_0034e0d4(); /* FUN_0034e0d4 (out-of-slice helper) */
extern unsigned long sk_0034e130(); /* FUN_0034e130 (out-of-slice helper) */
extern unsigned long sk_0034e1b0(); /* FUN_0034e1b0 (out-of-slice helper) */
extern unsigned long sk_0034e1d0(); /* FUN_0034e1d0 (out-of-slice helper) */
extern unsigned long sk_0034e33c(); /* FUN_0034e33c (out-of-slice helper) */
extern unsigned long sk_0034e384(); /* FUN_0034e384 (out-of-slice helper) */
extern unsigned long sk_0034e414(); /* FUN_0034e414 (out-of-slice helper) */
extern unsigned long sk_0034e434(); /* FUN_0034e434 (out-of-slice helper) */
extern unsigned long sk_0034e4b4(); /* FUN_0034e4b4 (out-of-slice helper) */
extern unsigned long sk_0034e57c(); /* FUN_0034e57c (out-of-slice helper) */
extern unsigned long sk_0034e5cc(); /* FUN_0034e5cc (out-of-slice helper) */
extern unsigned long sk_0034e5fc(); /* FUN_0034e5fc (out-of-slice helper) */
extern unsigned long sk_0034e60c(); /* FUN_0034e60c (out-of-slice helper) */
extern unsigned long sk_0034e63c(); /* FUN_0034e63c (out-of-slice helper) */
extern unsigned long sk_0034e66c(); /* FUN_0034e66c (out-of-slice helper) */
extern unsigned long sk_0034e67c(); /* FUN_0034e67c (out-of-slice helper) */
extern unsigned long sk_0034e70c(); /* FUN_0034e70c (out-of-slice helper) */
extern unsigned long sk_0034e808(); /* FUN_0034e808 (out-of-slice helper) */
extern unsigned long sk_0034ea40(); /* FUN_0034ea40 (out-of-slice helper) */
extern unsigned long sk_0034eb2c(); /* FUN_0034eb2c (out-of-slice helper) */
extern unsigned long sk_0034eb40(); /* FUN_0034eb40 (out-of-slice helper) */
extern unsigned long sk_0034ec48(); /* FUN_0034ec48 (out-of-slice helper) */
extern unsigned long sk_0034ece8(); /* FUN_0034ece8 (out-of-slice helper) */
extern unsigned long sk_0034ed28(); /* FUN_0034ed28 (out-of-slice helper) */
extern unsigned long sk_0034ed88(); /* FUN_0034ed88 (out-of-slice helper) */
extern unsigned long sk_0034ede8(); /* FUN_0034ede8 (out-of-slice helper) */
extern unsigned long sk_0034ee28(); /* FUN_0034ee28 (out-of-slice helper) */
extern unsigned long sk_0034ee48(); /* FUN_0034ee48 (out-of-slice helper) */
extern unsigned long sk_0034ee68(); /* FUN_0034ee68 (out-of-slice helper) */
extern unsigned long sk_0034ee98(); /* FUN_0034ee98 (out-of-slice helper) */
extern unsigned long sk_0034ef08(); /* FUN_0034ef08 (out-of-slice helper) */
extern unsigned long sk_0034ef48(); /* FUN_0034ef48 (out-of-slice helper) */
extern unsigned long sk_0034ef68(); /* FUN_0034ef68 (out-of-slice helper) */
extern unsigned long sk_0034f014(); /* FUN_0034f014 (out-of-slice helper) */
extern unsigned long sk_0034f044(); /* FUN_0034f044 (out-of-slice helper) */
extern unsigned long sk_0034f088(); /* FUN_0034f088 (out-of-slice helper) */
extern unsigned long sk_0034f0c0(); /* FUN_0034f0c0 (out-of-slice helper) */
extern unsigned long sk_0034f1e0(); /* FUN_0034f1e0 (out-of-slice helper) */
extern unsigned long sk_0034f384(); /* FUN_0034f384 (out-of-slice helper) */
extern unsigned long sk_0034f3e4(); /* FUN_0034f3e4 (out-of-slice helper) */
extern unsigned long sk_0034f4d4(); /* FUN_0034f4d4 (out-of-slice helper) */
extern unsigned long sk_0034f544(); /* FUN_0034f544 (out-of-slice helper) */
extern unsigned long sk_0034f5a4(); /* FUN_0034f5a4 (out-of-slice helper) */
extern unsigned long sk_0034f664(); /* FUN_0034f664 (out-of-slice helper) */
extern unsigned long sk_0034f754(); /* FUN_0034f754 (out-of-slice helper) */
extern unsigned long sk_0034f7ec(); /* FUN_0034f7ec (out-of-slice helper) */
extern unsigned long sk_0034f860(); /* FUN_0034f860 (out-of-slice helper) */
extern unsigned long sk_0034fce4(); /* FUN_0034fce4 (out-of-slice helper) */
extern unsigned long sk_0034fd4c(); /* FUN_0034fd4c (out-of-slice helper) */
extern unsigned long sk_0034fdcc(); /* FUN_0034fdcc (out-of-slice helper) */
extern unsigned long sk_0034fde0(); /* FUN_0034fde0 (out-of-slice helper) */
extern unsigned long sk_0034fe64(); /* FUN_0034fe64 (out-of-slice helper) */
extern unsigned long sk_0034fed0(); /* FUN_0034fed0 (out-of-slice helper) */
extern unsigned long sk_0034ffdc(); /* FUN_0034ffdc (out-of-slice helper) */
extern unsigned long sk_00350018(); /* FUN_00350018 (out-of-slice helper) */
extern unsigned long sk_00350048(); /* FUN_00350048 (out-of-slice helper) */
extern unsigned long sk_00350104(); /* FUN_00350104 (out-of-slice helper) */
extern unsigned long sk_003501fc(); /* FUN_003501fc (out-of-slice helper) */
extern unsigned long sk_0035036c(); /* FUN_0035036c (out-of-slice helper) */
extern unsigned long sk_00350390(); /* FUN_00350390 (out-of-slice helper) */
extern unsigned long sk_003503f8(); /* FUN_003503f8 (out-of-slice helper) */
extern unsigned long sk_00350410(); /* FUN_00350410 (out-of-slice helper) */
extern unsigned long sk_00350428(); /* FUN_00350428 (out-of-slice helper) */
extern unsigned long sk_00350434(); /* FUN_00350434 (out-of-slice helper) */
extern unsigned long sk_0035044c(); /* FUN_0035044c (out-of-slice helper) */
extern unsigned long sk_00350464(); /* FUN_00350464 (out-of-slice helper) */
extern unsigned long sk_00350470(); /* FUN_00350470 (out-of-slice helper) */
extern unsigned long sk_0035047c(); /* FUN_0035047c (out-of-slice helper) */
extern unsigned long sk_00350488(); /* FUN_00350488 (out-of-slice helper) */
extern unsigned long sk_003504a0(); /* FUN_003504a0 (out-of-slice helper) */
extern unsigned long sk_003504ac(); /* FUN_003504ac (out-of-slice helper) */
extern unsigned long sk_003504b8(); /* FUN_003504b8 (out-of-slice helper) */
extern unsigned long sk_003504c4(); /* FUN_003504c4 (out-of-slice helper) */
extern unsigned long sk_003504e8(); /* FUN_003504e8 (out-of-slice helper) */
extern unsigned long sk_003504f4(); /* FUN_003504f4 (out-of-slice helper) */
extern unsigned long sk_00350500(); /* FUN_00350500 (out-of-slice helper) */
extern unsigned long sk_0035050c(); /* FUN_0035050c (out-of-slice helper) */
extern unsigned long sk_00350518(); /* FUN_00350518 (out-of-slice helper) */
extern unsigned long sk_00350524(); /* FUN_00350524 (out-of-slice helper) */
extern unsigned long sk_00350530(); /* FUN_00350530 (out-of-slice helper) */
extern unsigned long sk_0035053c(); /* FUN_0035053c (out-of-slice helper) */
extern unsigned long sk_0035056c(); /* FUN_0035056c (out-of-slice helper) */
extern unsigned long sk_003505c4(); /* FUN_003505c4 (out-of-slice helper) */
extern unsigned long sk_003505d0(); /* FUN_003505d0 (out-of-slice helper) */
extern unsigned long sk_003505e8(); /* FUN_003505e8 (out-of-slice helper) */
extern unsigned long sk_003505f4(); /* FUN_003505f4 (out-of-slice helper) */
extern unsigned long sk_0035060c(); /* FUN_0035060c (out-of-slice helper) */
extern unsigned long sk_00350618(); /* FUN_00350618 (out-of-slice helper) */
extern unsigned long sk_00350624(); /* FUN_00350624 (out-of-slice helper) */
extern unsigned long sk_00350630(); /* FUN_00350630 (out-of-slice helper) */
extern unsigned long sk_0035063c(); /* FUN_0035063c (out-of-slice helper) */
extern unsigned long sk_00350648(); /* FUN_00350648 (out-of-slice helper) */
extern unsigned long sk_0035066c(); /* FUN_0035066c (out-of-slice helper) */
extern unsigned long sk_003506e8(); /* FUN_003506e8 (out-of-slice helper) */
extern unsigned long sk_00350720(); /* FUN_00350720 (out-of-slice helper) */
extern unsigned long sk_0035072c(); /* FUN_0035072c (out-of-slice helper) */
extern unsigned long sk_00350738(); /* FUN_00350738 (out-of-slice helper) */
extern unsigned long sk_00350768(); /* FUN_00350768 (out-of-slice helper) */
extern unsigned long sk_00350774(); /* FUN_00350774 (out-of-slice helper) */
extern unsigned long sk_00350780(); /* FUN_00350780 (out-of-slice helper) */
extern unsigned long sk_00350798(); /* FUN_00350798 (out-of-slice helper) */
extern unsigned long sk_003507bc(); /* FUN_003507bc (out-of-slice helper) */
extern unsigned long sk_003507d4(); /* FUN_003507d4 (out-of-slice helper) */
extern unsigned long sk_003507e0(); /* FUN_003507e0 (out-of-slice helper) */
extern unsigned long sk_00350810(); /* FUN_00350810 (out-of-slice helper) */
extern unsigned long sk_0035084c(); /* FUN_0035084c (out-of-slice helper) */
extern unsigned long sk_00350878(); /* FUN_00350878 (out-of-slice helper) */
extern unsigned long sk_00350884(); /* FUN_00350884 (out-of-slice helper) */
extern unsigned long sk_0035089c(); /* FUN_0035089c (out-of-slice helper) */
extern unsigned long sk_003508a8(); /* FUN_003508a8 (out-of-slice helper) */
extern unsigned long sk_003508b4(); /* FUN_003508b4 (out-of-slice helper) */
extern unsigned long sk_003508cc(); /* FUN_003508cc (out-of-slice helper) */
extern unsigned long sk_003508d8(); /* FUN_003508d8 (out-of-slice helper) */
extern unsigned long sk_003508e4(); /* FUN_003508e4 (out-of-slice helper) */
extern unsigned long sk_003508f0(); /* FUN_003508f0 (out-of-slice helper) */
extern unsigned long sk_003508fc(); /* FUN_003508fc (out-of-slice helper) */
extern unsigned long sk_00350908(); /* FUN_00350908 (out-of-slice helper) */
extern unsigned long sk_00350914(); /* FUN_00350914 (out-of-slice helper) */
extern unsigned long sk_00350920(); /* FUN_00350920 (out-of-slice helper) */
extern unsigned long sk_00350944(); /* FUN_00350944 (out-of-slice helper) */
extern unsigned long sk_00350950(); /* FUN_00350950 (out-of-slice helper) */
extern unsigned long sk_00350968(); /* FUN_00350968 (out-of-slice helper) */
extern unsigned long sk_00350974(); /* FUN_00350974 (out-of-slice helper) */
extern unsigned long sk_003509a4(); /* FUN_003509a4 (out-of-slice helper) */
extern unsigned long sk_003509b0(); /* FUN_003509b0 (out-of-slice helper) */
extern unsigned long sk_003509bc(); /* FUN_003509bc (out-of-slice helper) */
extern unsigned long sk_003509c8(); /* FUN_003509c8 (out-of-slice helper) */
extern unsigned long sk_003509d4(); /* FUN_003509d4 (out-of-slice helper) */
extern unsigned long sk_003509e0(); /* FUN_003509e0 (out-of-slice helper) */
extern unsigned long sk_003509f8(); /* FUN_003509f8 (out-of-slice helper) */
extern unsigned long sk_00350a04(); /* FUN_00350a04 (out-of-slice helper) */
extern unsigned long sk_00350a1c(); /* FUN_00350a1c (out-of-slice helper) */
extern unsigned long sk_00350a28(); /* FUN_00350a28 (out-of-slice helper) */
extern unsigned long sk_00350a34(); /* FUN_00350a34 (out-of-slice helper) */
extern unsigned long sk_00350a40(); /* FUN_00350a40 (out-of-slice helper) */
extern unsigned long sk_00350a70(); /* FUN_00350a70 (out-of-slice helper) */
extern unsigned long sk_00350a7c(); /* FUN_00350a7c (out-of-slice helper) */
extern unsigned long sk_00350a88(); /* FUN_00350a88 (out-of-slice helper) */
extern unsigned long sk_00350aa0(); /* FUN_00350aa0 (out-of-slice helper) */
extern unsigned long sk_00350aac(); /* FUN_00350aac (out-of-slice helper) */
extern unsigned long sk_00350ab8(); /* FUN_00350ab8 (out-of-slice helper) */
extern unsigned long sk_00350ad0(); /* FUN_00350ad0 (out-of-slice helper) */
extern unsigned long sk_00350af4(); /* FUN_00350af4 (out-of-slice helper) */
extern unsigned long sk_00350b18(); /* FUN_00350b18 (out-of-slice helper) */
extern unsigned long sk_00350b24(); /* FUN_00350b24 (out-of-slice helper) */
extern unsigned long sk_00350b30(); /* FUN_00350b30 (out-of-slice helper) */
extern unsigned long sk_00350b48(); /* FUN_00350b48 (out-of-slice helper) */
extern unsigned long sk_00350b6c(); /* FUN_00350b6c (out-of-slice helper) */
extern unsigned long sk_00350b78(); /* FUN_00350b78 (out-of-slice helper) */
extern unsigned long sk_00350b84(); /* FUN_00350b84 (out-of-slice helper) */
extern unsigned long sk_00350b9c(); /* FUN_00350b9c (out-of-slice helper) */
extern unsigned long sk_00350bc0(); /* FUN_00350bc0 (out-of-slice helper) */
extern unsigned long sk_00350bf0(); /* FUN_00350bf0 (out-of-slice helper) */
extern unsigned long sk_00350bfc(); /* FUN_00350bfc (out-of-slice helper) */
extern unsigned long sk_00350c2c(); /* FUN_00350c2c (out-of-slice helper) */
extern unsigned long sk_00350c50(); /* FUN_00350c50 (out-of-slice helper) */
extern unsigned long sk_00350c80(); /* FUN_00350c80 (out-of-slice helper) */
extern unsigned long sk_00350db4(); /* FUN_00350db4 (out-of-slice helper) */
extern unsigned long sk_00350e54(); /* FUN_00350e54 (out-of-slice helper) */
extern unsigned long sk_00350ea4(); /* FUN_00350ea4 (out-of-slice helper) */
extern unsigned long sk_00350ec0(); /* FUN_00350ec0 (out-of-slice helper) */
extern unsigned long sk_00350eec(); /* FUN_00350eec (out-of-slice helper) */
extern unsigned long sk_00350f7c(); /* FUN_00350f7c (out-of-slice helper) */
extern unsigned long sk_0035100c(); /* FUN_0035100c (out-of-slice helper) */
extern unsigned long sk_0035102c(); /* FUN_0035102c (out-of-slice helper) */
extern unsigned long sk_00351058(); /* FUN_00351058 (out-of-slice helper) */
extern unsigned long sk_00351088(); /* FUN_00351088 (out-of-slice helper) */
extern unsigned long sk_00351094(); /* FUN_00351094 (out-of-slice helper) */
extern unsigned long sk_003510ac(); /* FUN_003510ac (out-of-slice helper) */
extern unsigned long sk_003510b8(); /* FUN_003510b8 (out-of-slice helper) */
extern unsigned long sk_003510d0(); /* FUN_003510d0 (out-of-slice helper) */
extern unsigned long sk_003510dc(); /* FUN_003510dc (out-of-slice helper) */
extern unsigned long sk_003510f4(); /* FUN_003510f4 (out-of-slice helper) */
extern unsigned long sk_00351100(); /* FUN_00351100 (out-of-slice helper) */
extern unsigned long sk_0035110c(); /* FUN_0035110c (out-of-slice helper) */
extern unsigned long sk_00351118(); /* FUN_00351118 (out-of-slice helper) */
extern unsigned long sk_00351130(); /* FUN_00351130 (out-of-slice helper) */
extern unsigned long sk_0035113c(); /* FUN_0035113c (out-of-slice helper) */
extern unsigned long sk_00351160(); /* FUN_00351160 (out-of-slice helper) */
extern unsigned long sk_00351184(); /* FUN_00351184 (out-of-slice helper) */
extern unsigned long sk_00351190(); /* FUN_00351190 (out-of-slice helper) */
extern unsigned long sk_0035119c(); /* FUN_0035119c (out-of-slice helper) */
extern unsigned long sk_003511b4(); /* FUN_003511b4 (out-of-slice helper) */
extern unsigned long sk_003511cc(); /* FUN_003511cc (out-of-slice helper) */
extern unsigned long sk_003511d8(); /* FUN_003511d8 (out-of-slice helper) */
extern unsigned long sk_003511e4(); /* FUN_003511e4 (out-of-slice helper) */
extern unsigned long sk_003511f0(); /* FUN_003511f0 (out-of-slice helper) */
extern unsigned long sk_00351214(); /* FUN_00351214 (out-of-slice helper) */
extern unsigned long sk_00351220(); /* FUN_00351220 (out-of-slice helper) */
extern unsigned long sk_00351238(); /* FUN_00351238 (out-of-slice helper) */
extern unsigned long sk_00351250(); /* FUN_00351250 (out-of-slice helper) */
extern unsigned long sk_0035125c(); /* FUN_0035125c (out-of-slice helper) */
extern unsigned long sk_00351274(); /* FUN_00351274 (out-of-slice helper) */
extern unsigned long sk_00351280(); /* FUN_00351280 (out-of-slice helper) */
extern unsigned long sk_00351298(); /* FUN_00351298 (out-of-slice helper) */
extern unsigned long sk_003512c0(); /* FUN_003512c0 (out-of-slice helper) */
extern unsigned long sk_003512cc(); /* FUN_003512cc (out-of-slice helper) */
extern unsigned long sk_00351300(); /* FUN_00351300 (out-of-slice helper) */
extern unsigned long sk_00351318(); /* FUN_00351318 (out-of-slice helper) */
extern unsigned long sk_00351324(); /* FUN_00351324 (out-of-slice helper) */
extern unsigned long sk_00351330(); /* FUN_00351330 (out-of-slice helper) */
extern unsigned long sk_0035133c(); /* FUN_0035133c (out-of-slice helper) */
extern unsigned long sk_00351348(); /* FUN_00351348 (out-of-slice helper) */
extern unsigned long sk_00351354(); /* FUN_00351354 (out-of-slice helper) */
extern unsigned long sk_00351360(); /* FUN_00351360 (out-of-slice helper) */
extern unsigned long sk_0035136c(); /* FUN_0035136c (out-of-slice helper) */
extern unsigned long sk_00351378(); /* FUN_00351378 (out-of-slice helper) */
extern unsigned long sk_00351384(); /* FUN_00351384 (out-of-slice helper) */
extern unsigned long sk_00351390(); /* FUN_00351390 (out-of-slice helper) */
extern unsigned long sk_0035139c(); /* FUN_0035139c (out-of-slice helper) */
extern unsigned long sk_003513b4(); /* FUN_003513b4 (out-of-slice helper) */
extern unsigned long sk_003513d8(); /* FUN_003513d8 (out-of-slice helper) */
extern unsigned long sk_00351414(); /* FUN_00351414 (out-of-slice helper) */
extern unsigned long sk_00351420(); /* FUN_00351420 (out-of-slice helper) */
extern unsigned long sk_00351438(); /* FUN_00351438 (out-of-slice helper) */
extern unsigned long sk_00351450(); /* FUN_00351450 (out-of-slice helper) */
extern unsigned long sk_0035145c(); /* FUN_0035145c (out-of-slice helper) */
extern unsigned long sk_003514e8(); /* FUN_003514e8 (out-of-slice helper) */
extern unsigned long sk_003515a8(); /* FUN_003515a8 (out-of-slice helper) */
extern unsigned long sk_003515b4(); /* FUN_003515b4 (out-of-slice helper) */
extern unsigned long sk_003515c0(); /* FUN_003515c0 (out-of-slice helper) */
extern unsigned long sk_003515d8(); /* FUN_003515d8 (out-of-slice helper) */
extern unsigned long sk_0035166c(); /* FUN_0035166c (out-of-slice helper) */
extern unsigned long sk_003516b4(); /* FUN_003516b4 (out-of-slice helper) */
extern unsigned long sk_003516cc(); /* FUN_003516cc (out-of-slice helper) */
extern unsigned long sk_003516d8(); /* FUN_003516d8 (out-of-slice helper) */
extern unsigned long sk_003516e4(); /* FUN_003516e4 (out-of-slice helper) */
extern unsigned long sk_003516fc(); /* FUN_003516fc (out-of-slice helper) */
extern unsigned long sk_00351714(); /* FUN_00351714 (out-of-slice helper) */
extern unsigned long sk_0035172c(); /* FUN_0035172c (out-of-slice helper) */
extern unsigned long sk_00351744(); /* FUN_00351744 (out-of-slice helper) */
extern unsigned long sk_0035179c(); /* FUN_0035179c (out-of-slice helper) */
extern unsigned long sk_003517c0(); /* FUN_003517c0 (out-of-slice helper) */
extern unsigned long sk_003518a0(); /* FUN_003518a0 (out-of-slice helper) */
extern unsigned long sk_003518ac(); /* FUN_003518ac (out-of-slice helper) */
extern unsigned long sk_003518b8(); /* FUN_003518b8 (out-of-slice helper) */
extern unsigned long sk_003518c4(); /* FUN_003518c4 (out-of-slice helper) */
extern unsigned long sk_003518d0(); /* FUN_003518d0 (out-of-slice helper) */
extern unsigned long sk_0035190c(); /* FUN_0035190c (out-of-slice helper) */
extern unsigned long sk_00351924(); /* FUN_00351924 (out-of-slice helper) */
extern unsigned long sk_00351984(); /* FUN_00351984 (out-of-slice helper) */
extern unsigned long sk_00351990(); /* FUN_00351990 (out-of-slice helper) */
extern unsigned long sk_00351a08(); /* FUN_00351a08 (out-of-slice helper) */
extern unsigned long sk_00351a14(); /* FUN_00351a14 (out-of-slice helper) */
extern unsigned long sk_00351a38(); /* FUN_00351a38 (out-of-slice helper) */
extern unsigned long sk_00351a44(); /* FUN_00351a44 (out-of-slice helper) */
extern unsigned long sk_00351a68(); /* FUN_00351a68 (out-of-slice helper) */
extern unsigned long sk_00351ab0(); /* FUN_00351ab0 (out-of-slice helper) */
extern unsigned long sk_00351ac8(); /* FUN_00351ac8 (out-of-slice helper) */
extern unsigned long sk_00351ad4(); /* FUN_00351ad4 (out-of-slice helper) */
extern unsigned long sk_00351af8(); /* FUN_00351af8 (out-of-slice helper) */
extern unsigned long sk_00351b20(); /* FUN_00351b20 (out-of-slice helper) */
extern unsigned long sk_00351b2c(); /* FUN_00351b2c (out-of-slice helper) */
extern unsigned long sk_00351b38(); /* FUN_00351b38 (out-of-slice helper) */
extern unsigned long sk_00351b78(); /* FUN_00351b78 (out-of-slice helper) */
extern unsigned long sk_00351b84(); /* FUN_00351b84 (out-of-slice helper) */
extern unsigned long sk_00351ba0(); /* FUN_00351ba0 (out-of-slice helper) */
extern unsigned long sk_00351bac(); /* FUN_00351bac (out-of-slice helper) */
extern unsigned long sk_00351bb8(); /* FUN_00351bb8 (out-of-slice helper) */
extern unsigned long sk_00351bd4(); /* FUN_00351bd4 (out-of-slice helper) */
extern unsigned long sk_00351bec(); /* FUN_00351bec (out-of-slice helper) */
extern unsigned long sk_00351c4c(); /* FUN_00351c4c (out-of-slice helper) */
extern unsigned long sk_00351c88(); /* FUN_00351c88 (out-of-slice helper) */
extern unsigned long sk_00351ca0(); /* FUN_00351ca0 (out-of-slice helper) */
extern unsigned long sk_00351cf4(); /* FUN_00351cf4 (out-of-slice helper) */
extern unsigned long sk_00351d30(); /* FUN_00351d30 (out-of-slice helper) */
extern unsigned long sk_00351df0(); /* FUN_00351df0 (out-of-slice helper) */
extern unsigned long sk_00351dfc(); /* FUN_00351dfc (out-of-slice helper) */
extern unsigned long sk_00351e20(); /* FUN_00351e20 (out-of-slice helper) */
extern unsigned long sk_00351e48(); /* FUN_00351e48 (out-of-slice helper) */
extern unsigned long sk_00351e54(); /* FUN_00351e54 (out-of-slice helper) */
extern unsigned long sk_00351e84(); /* FUN_00351e84 (out-of-slice helper) */
extern unsigned long sk_00351e90(); /* FUN_00351e90 (out-of-slice helper) */
extern unsigned long sk_00351e9c(); /* FUN_00351e9c (out-of-slice helper) */
extern unsigned long sk_00351ec0(); /* FUN_00351ec0 (out-of-slice helper) */
extern unsigned long sk_00351ecc(); /* FUN_00351ecc (out-of-slice helper) */
extern unsigned long sk_00351ef8(); /* FUN_00351ef8 (out-of-slice helper) */
extern unsigned long sk_00351f1c(); /* FUN_00351f1c (out-of-slice helper) */
extern unsigned long sk_00351f40(); /* FUN_00351f40 (out-of-slice helper) */
extern unsigned long sk_00351f4c(); /* FUN_00351f4c (out-of-slice helper) */
extern unsigned long sk_00351f70(); /* FUN_00351f70 (out-of-slice helper) */
extern unsigned long sk_00351f7c(); /* FUN_00351f7c (out-of-slice helper) */
extern unsigned long sk_00351f88(); /* FUN_00351f88 (out-of-slice helper) */
extern unsigned long sk_00352008(); /* FUN_00352008 (out-of-slice helper) */
extern unsigned long sk_00352098(); /* FUN_00352098 (out-of-slice helper) */
extern unsigned long sk_0035215c(); /* FUN_0035215c (out-of-slice helper) */
extern unsigned long sk_00352270(); /* FUN_00352270 (out-of-slice helper) */
extern unsigned long sk_00352304(); /* FUN_00352304 (out-of-slice helper) */
extern unsigned long sk_00352314(); /* FUN_00352314 (out-of-slice helper) */
extern unsigned long sk_00352330(); /* FUN_00352330 (out-of-slice helper) */
extern unsigned long sk_00352360(); /* FUN_00352360 (out-of-slice helper) */
extern unsigned long sk_00352370(); /* FUN_00352370 (out-of-slice helper) */
extern unsigned long sk_003523f0(); /* FUN_003523f0 (out-of-slice helper) */
extern unsigned long sk_00352420(); /* FUN_00352420 (out-of-slice helper) */
extern unsigned long sk_00352480(); /* FUN_00352480 (out-of-slice helper) */
extern unsigned long sk_00352498(); /* FUN_00352498 (out-of-slice helper) */
extern unsigned long sk_003524b0(); /* FUN_003524b0 (out-of-slice helper) */
extern unsigned long sk_003524c8(); /* FUN_003524c8 (out-of-slice helper) */
extern unsigned long sk_00352554(); /* FUN_00352554 (out-of-slice helper) */
extern unsigned long sk_00352560(); /* FUN_00352560 (out-of-slice helper) */
extern unsigned long sk_0035256c(); /* FUN_0035256c (out-of-slice helper) */
extern unsigned long sk_00352584(); /* FUN_00352584 (out-of-slice helper) */
extern unsigned long sk_00352680(); /* FUN_00352680 (out-of-slice helper) */
extern unsigned long sk_00352700(); /* FUN_00352700 (out-of-slice helper) */
extern unsigned long sk_003527ec(); /* FUN_003527ec (out-of-slice helper) */
extern unsigned long sk_00352840(); /* FUN_00352840 (out-of-slice helper) */
extern unsigned long sk_0035284c(); /* FUN_0035284c (out-of-slice helper) */
extern unsigned long sk_00352858(); /* FUN_00352858 (out-of-slice helper) */
extern unsigned long sk_00352894(); /* FUN_00352894 (out-of-slice helper) */
extern unsigned long sk_00352914(); /* FUN_00352914 (out-of-slice helper) */
extern unsigned long sk_00352a40(); /* FUN_00352a40 (out-of-slice helper) */
extern unsigned long sk_00352a4c(); /* FUN_00352a4c (out-of-slice helper) */
extern unsigned long sk_00352ae4(); /* FUN_00352ae4 (out-of-slice helper) */
extern unsigned long sk_00352b14(); /* FUN_00352b14 (out-of-slice helper) */
extern unsigned long sk_00352b2c(); /* FUN_00352b2c (out-of-slice helper) */
extern unsigned long sk_00352b50(); /* FUN_00352b50 (out-of-slice helper) */
extern unsigned long sk_00352b8c(); /* FUN_00352b8c (out-of-slice helper) */
extern unsigned long sk_00352b98(); /* FUN_00352b98 (out-of-slice helper) */
extern unsigned long sk_00352bbc(); /* FUN_00352bbc (out-of-slice helper) */
extern unsigned long sk_00352be0(); /* FUN_00352be0 (out-of-slice helper) */
extern unsigned long sk_00352c40(); /* FUN_00352c40 (out-of-slice helper) */
extern unsigned long sk_00352c4c(); /* FUN_00352c4c (out-of-slice helper) */
extern unsigned long sk_00352c68(); /* FUN_00352c68 (out-of-slice helper) */
extern unsigned long sk_00352d34(); /* FUN_00352d34 (out-of-slice helper) */
extern unsigned long sk_00352d64(); /* FUN_00352d64 (out-of-slice helper) */
extern unsigned long sk_00352ddc(); /* FUN_00352ddc (out-of-slice helper) */
extern unsigned long sk_00352df4(); /* FUN_00352df4 (out-of-slice helper) */
extern unsigned long sk_00352e24(); /* FUN_00352e24 (out-of-slice helper) */
extern unsigned long sk_00352e60(); /* FUN_00352e60 (out-of-slice helper) */
extern unsigned long sk_00352e78(); /* FUN_00352e78 (out-of-slice helper) */
extern unsigned long sk_00352ea8(); /* FUN_00352ea8 (out-of-slice helper) */
extern unsigned long sk_00352eb4(); /* FUN_00352eb4 (out-of-slice helper) */
extern unsigned long sk_00352efc(); /* FUN_00352efc (out-of-slice helper) */
extern unsigned long sk_00352f18(); /* FUN_00352f18 (out-of-slice helper) */
extern unsigned long sk_00352f48(); /* FUN_00352f48 (out-of-slice helper) */
extern unsigned long sk_00352f88(); /* FUN_00352f88 (out-of-slice helper) */
extern unsigned long sk_00352fd4(); /* FUN_00352fd4 (out-of-slice helper) */
extern unsigned long sk_0035300c(); /* FUN_0035300c (out-of-slice helper) */
extern unsigned long sk_00353034(); /* FUN_00353034 (out-of-slice helper) */
extern unsigned long sk_00353050(); /* FUN_00353050 (out-of-slice helper) */
extern unsigned long sk_0035308c(); /* FUN_0035308c (out-of-slice helper) */
extern unsigned long sk_003530e8(); /* FUN_003530e8 (out-of-slice helper) */
extern unsigned long sk_003530f4(); /* FUN_003530f4 (out-of-slice helper) */
extern unsigned long sk_0035310c(); /* FUN_0035310c (out-of-slice helper) */
extern unsigned long sk_00353124(); /* FUN_00353124 (out-of-slice helper) */
extern unsigned long sk_00353160(); /* FUN_00353160 (out-of-slice helper) */
extern unsigned long sk_0035316c(); /* FUN_0035316c (out-of-slice helper) */
extern unsigned long sk_003531d8(); /* FUN_003531d8 (out-of-slice helper) */
extern unsigned long sk_003531f0(); /* FUN_003531f0 (out-of-slice helper) */
extern unsigned long sk_00353220(); /* FUN_00353220 (out-of-slice helper) */
extern unsigned long sk_0035322c(); /* FUN_0035322c (out-of-slice helper) */
extern unsigned long sk_00353238(); /* FUN_00353238 (out-of-slice helper) */
extern unsigned long sk_00353254(); /* FUN_00353254 (out-of-slice helper) */
extern unsigned long sk_00353274(); /* FUN_00353274 (out-of-slice helper) */
extern unsigned long sk_00353390(); /* FUN_00353390 (out-of-slice helper) */
extern unsigned long sk_00353430(); /* FUN_00353430 (out-of-slice helper) */
extern unsigned long sk_003534bc(); /* FUN_003534bc (out-of-slice helper) */
extern unsigned long sk_003534d4(); /* FUN_003534d4 (out-of-slice helper) */
extern unsigned long sk_003534e0(); /* FUN_003534e0 (out-of-slice helper) */
extern unsigned long sk_003534ec(); /* FUN_003534ec (out-of-slice helper) */
extern unsigned long sk_003536ac(); /* FUN_003536ac (out-of-slice helper) */
extern unsigned long sk_00353718(); /* FUN_00353718 (out-of-slice helper) */
extern unsigned long sk_00353734(); /* FUN_00353734 (out-of-slice helper) */
extern unsigned long sk_003537d4(); /* FUN_003537d4 (out-of-slice helper) */
extern unsigned long sk_003537f0(); /* FUN_003537f0 (out-of-slice helper) */
extern unsigned long sk_003537fc(); /* FUN_003537fc (out-of-slice helper) */
extern unsigned long sk_00353918(); /* FUN_00353918 (out-of-slice helper) */
extern unsigned long sk_0035396c(); /* FUN_0035396c (out-of-slice helper) */
extern unsigned long sk_003539e4(); /* FUN_003539e4 (out-of-slice helper) */
extern unsigned long sk_003539f4(); /* FUN_003539f4 (out-of-slice helper) */
extern unsigned long sk_00353a78(); /* FUN_00353a78 (out-of-slice helper) */
extern unsigned long sk_00353b10(); /* FUN_00353b10 (out-of-slice helper) */
extern unsigned long sk_00353b34(); /* FUN_00353b34 (out-of-slice helper) */
extern unsigned long sk_00353be8(); /* FUN_00353be8 (out-of-slice helper) */
extern unsigned long sk_00353c48(); /* FUN_00353c48 (out-of-slice helper) */
extern unsigned long sk_00353c54(); /* FUN_00353c54 (out-of-slice helper) */
extern unsigned long sk_00353c78(); /* FUN_00353c78 (out-of-slice helper) */
extern unsigned long sk_00353cb4(); /* FUN_00353cb4 (out-of-slice helper) */
extern unsigned long sk_00353cd8(); /* FUN_00353cd8 (out-of-slice helper) */
extern unsigned long sk_00353cf0(); /* FUN_00353cf0 (out-of-slice helper) */
extern unsigned long sk_00353cfc(); /* FUN_00353cfc (out-of-slice helper) */
extern unsigned long sk_00353d14(); /* FUN_00353d14 (out-of-slice helper) */
extern unsigned long sk_00353d94(); /* FUN_00353d94 (out-of-slice helper) */
extern unsigned long sk_00353e2c(); /* FUN_00353e2c (out-of-slice helper) */
extern unsigned long sk_00353e38(); /* FUN_00353e38 (out-of-slice helper) */
extern unsigned long sk_00353e50(); /* FUN_00353e50 (out-of-slice helper) */
extern unsigned long sk_00353ef0(); /* FUN_00353ef0 (out-of-slice helper) */
extern unsigned long sk_00353efc(); /* FUN_00353efc (out-of-slice helper) */
extern unsigned long sk_00353f44(); /* FUN_00353f44 (out-of-slice helper) */
extern unsigned long sk_00353f50(); /* FUN_00353f50 (out-of-slice helper) */
extern unsigned long sk_00353f88(); /* FUN_00353f88 (out-of-slice helper) */
extern unsigned long sk_00354010(); /* FUN_00354010 (out-of-slice helper) */
extern unsigned long sk_00354134(); /* FUN_00354134 (out-of-slice helper) */
extern unsigned long sk_0035414c(); /* FUN_0035414c (out-of-slice helper) */
extern unsigned long sk_00354168(); /* FUN_00354168 (out-of-slice helper) */
extern unsigned long sk_00354184(); /* FUN_00354184 (out-of-slice helper) */
extern unsigned long sk_003541a0(); /* FUN_003541a0 (out-of-slice helper) */
extern unsigned long sk_003541bc(); /* FUN_003541bc (out-of-slice helper) */
extern unsigned long sk_003541d8(); /* FUN_003541d8 (out-of-slice helper) */
extern unsigned long sk_003541f4(); /* FUN_003541f4 (out-of-slice helper) */
extern unsigned long sk_00354210(); /* FUN_00354210 (out-of-slice helper) */
extern unsigned long sk_003542d0(); /* FUN_003542d0 (out-of-slice helper) */
extern unsigned long sk_003542e8(); /* FUN_003542e8 (out-of-slice helper) */
extern unsigned long sk_00354300(); /* FUN_00354300 (out-of-slice helper) */
extern unsigned long sk_0035430c(); /* FUN_0035430c (out-of-slice helper) */
extern unsigned long sk_00354324(); /* FUN_00354324 (out-of-slice helper) */
extern unsigned long sk_00354394(); /* FUN_00354394 (out-of-slice helper) */
extern unsigned long sk_003543ac(); /* FUN_003543ac (out-of-slice helper) */
extern unsigned long sk_00354404(); /* FUN_00354404 (out-of-slice helper) */
extern unsigned long sk_00354458(); /* FUN_00354458 (out-of-slice helper) */
extern unsigned long sk_003544c8(); /* FUN_003544c8 (out-of-slice helper) */
extern unsigned long sk_00354594(); /* FUN_00354594 (out-of-slice helper) */
extern unsigned long sk_003545ac(); /* FUN_003545ac (out-of-slice helper) */
extern unsigned long sk_00354660(); /* FUN_00354660 (out-of-slice helper) */
extern unsigned long sk_003546a8(); /* FUN_003546a8 (out-of-slice helper) */
extern unsigned long sk_00354708(); /* FUN_00354708 (out-of-slice helper) */
extern unsigned long sk_00354720(); /* FUN_00354720 (out-of-slice helper) */
extern unsigned long sk_00354744(); /* FUN_00354744 (out-of-slice helper) */
extern unsigned long sk_0035475c(); /* FUN_0035475c (out-of-slice helper) */
extern unsigned long sk_00354780(); /* FUN_00354780 (out-of-slice helper) */
extern unsigned long sk_003547d4(); /* FUN_003547d4 (out-of-slice helper) */
extern unsigned long sk_003547ec(); /* FUN_003547ec (out-of-slice helper) */
extern unsigned long sk_003548d0(); /* FUN_003548d0 (out-of-slice helper) */
extern unsigned long sk_003549e4(); /* FUN_003549e4 (out-of-slice helper) */
extern unsigned long sk_00354a0c(); /* FUN_00354a0c (out-of-slice helper) */
extern unsigned long sk_00354a34(); /* FUN_00354a34 (out-of-slice helper) */
extern unsigned long sk_00354b14(); /* FUN_00354b14 (out-of-slice helper) */
extern unsigned long sk_00354b2c(); /* FUN_00354b2c (out-of-slice helper) */
extern unsigned long sk_00354b50(); /* FUN_00354b50 (out-of-slice helper) */
extern unsigned long sk_00354b68(); /* FUN_00354b68 (out-of-slice helper) */
extern unsigned long sk_00354bb0(); /* FUN_00354bb0 (out-of-slice helper) */
extern unsigned long sk_00354bbc(); /* FUN_00354bbc (out-of-slice helper) */
extern unsigned long sk_00354d14(); /* FUN_00354d14 (out-of-slice helper) */
extern unsigned long sk_00354d38(); /* FUN_00354d38 (out-of-slice helper) */
extern unsigned long sk_00354d44(); /* FUN_00354d44 (out-of-slice helper) */
extern unsigned long sk_00354d5c(); /* FUN_00354d5c (out-of-slice helper) */
extern unsigned long sk_00354d94(); /* FUN_00354d94 (out-of-slice helper) */
extern unsigned long sk_00354db8(); /* FUN_00354db8 (out-of-slice helper) */
extern unsigned long sk_00354ef8(); /* FUN_00354ef8 (out-of-slice helper) */
extern unsigned long sk_00354f10(); /* FUN_00354f10 (out-of-slice helper) */
extern unsigned long sk_00354f34(); /* FUN_00354f34 (out-of-slice helper) */
extern unsigned long sk_00354f80(); /* FUN_00354f80 (out-of-slice helper) */
extern unsigned long sk_00354f8c(); /* FUN_00354f8c (out-of-slice helper) */
extern unsigned long sk_00355068(); /* FUN_00355068 (out-of-slice helper) */
extern unsigned long sk_00355224(); /* FUN_00355224 (out-of-slice helper) */
extern unsigned long sk_00355418(); /* FUN_00355418 (out-of-slice helper) */
extern unsigned long sk_003554d4(); /* FUN_003554d4 (out-of-slice helper) */
extern unsigned long sk_003554e0(); /* FUN_003554e0 (out-of-slice helper) */
extern unsigned long sk_00355544(); /* FUN_00355544 (out-of-slice helper) */
extern unsigned long sk_00355578(); /* FUN_00355578 (out-of-slice helper) */
extern unsigned long sk_00355594(); /* FUN_00355594 (out-of-slice helper) */
extern unsigned long sk_00355634(); /* FUN_00355634 (out-of-slice helper) */
extern unsigned long sk_00355730(); /* FUN_00355730 (out-of-slice helper) */
extern unsigned long sk_003557a8(); /* FUN_003557a8 (out-of-slice helper) */
extern unsigned long sk_00355adc(); /* FUN_00355adc (out-of-slice helper) */
extern unsigned long sk_00355af8(); /* FUN_00355af8 (out-of-slice helper) */
extern unsigned long sk_00355b04(); /* FUN_00355b04 (out-of-slice helper) */
extern unsigned long sk_00355b74(); /* FUN_00355b74 (out-of-slice helper) */
extern unsigned long sk_00355bd0(); /* FUN_00355bd0 (out-of-slice helper) */
extern unsigned long sk_00355bdc(); /* FUN_00355bdc (out-of-slice helper) */
extern unsigned long sk_00355c1c(); /* FUN_00355c1c (out-of-slice helper) */
extern unsigned long sk_00355c28(); /* FUN_00355c28 (out-of-slice helper) */
extern unsigned long sk_00355d28(); /* FUN_00355d28 (out-of-slice helper) */
extern unsigned long sk_00355d78(); /* FUN_00355d78 (out-of-slice helper) */
extern unsigned long sk_00355e2c(); /* FUN_00355e2c (out-of-slice helper) */
extern unsigned long sk_00355e5c(); /* FUN_00355e5c (out-of-slice helper) */
extern unsigned long sk_00355e68(); /* FUN_00355e68 (out-of-slice helper) */
extern unsigned long sk_00355e74(); /* FUN_00355e74 (out-of-slice helper) */
extern unsigned long sk_00356000(); /* FUN_00356000 (out-of-slice helper) */
extern unsigned long sk_00356030(); /* FUN_00356030 (out-of-slice helper) */
extern unsigned long sk_00356078(); /* FUN_00356078 (out-of-slice helper) */
extern unsigned long sk_003560a8(); /* FUN_003560a8 (out-of-slice helper) */
extern unsigned long sk_003560c0(); /* FUN_003560c0 (out-of-slice helper) */
extern unsigned long sk_00356140(); /* FUN_00356140 (out-of-slice helper) */
extern unsigned long sk_00356224(); /* FUN_00356224 (out-of-slice helper) */
extern unsigned long sk_00356260(); /* FUN_00356260 (out-of-slice helper) */
extern unsigned long sk_0035626c(); /* FUN_0035626c (out-of-slice helper) */
extern unsigned long sk_00356290(); /* FUN_00356290 (out-of-slice helper) */
extern unsigned long sk_003562ec(); /* FUN_003562ec (out-of-slice helper) */
extern unsigned long sk_00356328(); /* FUN_00356328 (out-of-slice helper) */
extern unsigned long sk_003563a8(); /* FUN_003563a8 (out-of-slice helper) */
extern unsigned long sk_003563c4(); /* FUN_003563c4 (out-of-slice helper) */
extern unsigned long sk_003565c0(); /* FUN_003565c0 (out-of-slice helper) */
extern unsigned long sk_003565e0(); /* FUN_003565e0 (out-of-slice helper) */
extern unsigned long sk_00356600(); /* FUN_00356600 (out-of-slice helper) */
extern unsigned long sk_00356644(); /* FUN_00356644 (out-of-slice helper) */
extern unsigned long sk_00356670(); /* FUN_00356670 (out-of-slice helper) */
extern unsigned long sk_0035678c(); /* FUN_0035678c (out-of-slice helper) */
extern unsigned long sk_003567d4(); /* FUN_003567d4 (out-of-slice helper) */
extern unsigned long sk_0035681c(); /* FUN_0035681c (out-of-slice helper) */
extern unsigned long sk_00356834(); /* FUN_00356834 (out-of-slice helper) */
extern unsigned long sk_00356870(); /* FUN_00356870 (out-of-slice helper) */
extern unsigned long sk_003568e8(); /* FUN_003568e8 (out-of-slice helper) */
extern unsigned long sk_00356964(); /* FUN_00356964 (out-of-slice helper) */
extern unsigned long sk_003569b4(); /* FUN_003569b4 (out-of-slice helper) */
extern unsigned long sk_00356a44(); /* FUN_00356a44 (out-of-slice helper) */
extern unsigned long sk_00356ac4(); /* FUN_00356ac4 (out-of-slice helper) */
extern unsigned long sk_00356af4(); /* FUN_00356af4 (out-of-slice helper) */
extern unsigned long sk_00356b20(); /* FUN_00356b20 (out-of-slice helper) */
extern unsigned long sk_00356b80(); /* FUN_00356b80 (out-of-slice helper) */
extern unsigned long sk_00356cfc(); /* FUN_00356cfc (out-of-slice helper) */
extern unsigned long sk_0035705c(); /* FUN_0035705c (out-of-slice helper) */
extern unsigned long sk_003570f0(); /* FUN_003570f0 (out-of-slice helper) */
extern unsigned long sk_0035725c(); /* FUN_0035725c (out-of-slice helper) */
extern unsigned long sk_0035740c(); /* FUN_0035740c (out-of-slice helper) */
extern unsigned long sk_00357418(); /* FUN_00357418 (out-of-slice helper) */
extern unsigned long sk_00357694(); /* FUN_00357694 (out-of-slice helper) */
extern unsigned long sk_00357788(); /* FUN_00357788 (out-of-slice helper) */
extern unsigned long sk_00357874(); /* FUN_00357874 (out-of-slice helper) */
extern unsigned long sk_00357884(); /* FUN_00357884 (out-of-slice helper) */
extern unsigned long sk_003578a8(); /* FUN_003578a8 (out-of-slice helper) */
extern unsigned long sk_00357910(); /* FUN_00357910 (out-of-slice helper) */
extern unsigned long sk_0035792c(); /* FUN_0035792c (out-of-slice helper) */
extern unsigned long sk_00357944(); /* FUN_00357944 (out-of-slice helper) */
extern unsigned long sk_0035798c(); /* FUN_0035798c (out-of-slice helper) */
extern unsigned long sk_00357a34(); /* FUN_00357a34 (out-of-slice helper) */
extern unsigned long sk_00357a84(); /* FUN_00357a84 (out-of-slice helper) */
extern unsigned long sk_00357ab4(); /* FUN_00357ab4 (out-of-slice helper) */
extern unsigned long sk_00357b20(); /* FUN_00357b20 (out-of-slice helper) */
extern unsigned long sk_00357c20(); /* FUN_00357c20 (out-of-slice helper) */
extern unsigned long sk_00357c44(); /* FUN_00357c44 (out-of-slice helper) */
extern unsigned long sk_00357c74(); /* FUN_00357c74 (out-of-slice helper) */
extern unsigned long sk_00357ca0(); /* FUN_00357ca0 (out-of-slice helper) */
extern unsigned long sk_00357cb4(); /* FUN_00357cb4 (out-of-slice helper) */
extern unsigned long sk_00357d54(); /* FUN_00357d54 (out-of-slice helper) */
extern unsigned long sk_00357f14(); /* FUN_00357f14 (out-of-slice helper) */
extern unsigned long sk_00357f94(); /* FUN_00357f94 (out-of-slice helper) */
extern unsigned long sk_00357fd4(); /* FUN_00357fd4 (out-of-slice helper) */
extern unsigned long sk_003580e4(); /* FUN_003580e4 (out-of-slice helper) */
extern unsigned long sk_00358208(); /* FUN_00358208 (out-of-slice helper) */
extern unsigned long sk_003582f8(); /* FUN_003582f8 (out-of-slice helper) */
extern unsigned long sk_00358308(); /* FUN_00358308 (out-of-slice helper) */
extern unsigned long sk_003583c0(); /* FUN_003583c0 (out-of-slice helper) */
extern unsigned long sk_003583e8(); /* FUN_003583e8 (out-of-slice helper) */
extern unsigned long sk_0035841c(); /* FUN_0035841c (out-of-slice helper) */
extern unsigned long sk_00358454(); /* FUN_00358454 (out-of-slice helper) */
extern unsigned long sk_003584c0(); /* FUN_003584c0 (out-of-slice helper) */
extern unsigned long sk_00358540(); /* FUN_00358540 (out-of-slice helper) */
extern unsigned long sk_003585f4(); /* FUN_003585f4 (out-of-slice helper) */
extern unsigned long sk_00358600(); /* FUN_00358600 (out-of-slice helper) */
extern unsigned long sk_00358624(); /* FUN_00358624 (out-of-slice helper) */
extern unsigned long sk_0035863c(); /* FUN_0035863c (out-of-slice helper) */
extern unsigned long sk_003588d0(); /* FUN_003588d0 (out-of-slice helper) */
extern unsigned long sk_00358918(); /* FUN_00358918 (out-of-slice helper) */
extern unsigned long sk_0035893c(); /* FUN_0035893c (out-of-slice helper) */
extern unsigned long sk_00358960(); /* FUN_00358960 (out-of-slice helper) */
extern unsigned long sk_00358978(); /* FUN_00358978 (out-of-slice helper) */
extern unsigned long sk_003589cc(); /* FUN_003589cc (out-of-slice helper) */
extern unsigned long sk_003589d8(); /* FUN_003589d8 (out-of-slice helper) */
extern unsigned long sk_00358ae0(); /* FUN_00358ae0 (out-of-slice helper) */
extern unsigned long sk_00358bc0(); /* FUN_00358bc0 (out-of-slice helper) */
extern unsigned long sk_00358bcc(); /* FUN_00358bcc (out-of-slice helper) */
extern unsigned long sk_00358cd4(); /* FUN_00358cd4 (out-of-slice helper) */
extern unsigned long sk_00358cec(); /* FUN_00358cec (out-of-slice helper) */
extern unsigned long sk_00358d34(); /* FUN_00358d34 (out-of-slice helper) */
extern unsigned long sk_00358dac(); /* FUN_00358dac (out-of-slice helper) */
extern unsigned long sk_00358ddc(); /* FUN_00358ddc (out-of-slice helper) */
extern unsigned long sk_00358ea0(); /* FUN_00358ea0 (out-of-slice helper) */
extern unsigned long sk_00358f0c(); /* FUN_00358f0c (out-of-slice helper) */
extern unsigned long sk_00358f78(); /* FUN_00358f78 (out-of-slice helper) */
extern unsigned long sk_00359000(); /* FUN_00359000 (out-of-slice helper) */
extern unsigned long sk_00359030(); /* FUN_00359030 (out-of-slice helper) */
extern unsigned long sk_00359088(); /* FUN_00359088 (out-of-slice helper) */
extern unsigned long sk_00359134(); /* FUN_00359134 (out-of-slice helper) */
extern unsigned long sk_003593e8(); /* FUN_003593e8 (out-of-slice helper) */
extern unsigned long sk_00359550(); /* FUN_00359550 (out-of-slice helper) */
extern unsigned long sk_003595a8(); /* FUN_003595a8 (out-of-slice helper) */
extern unsigned long sk_0035964c(); /* FUN_0035964c (out-of-slice helper) */
extern unsigned long sk_003597d8(); /* FUN_003597d8 (out-of-slice helper) */
extern unsigned long sk_00359a48(); /* FUN_00359a48 (out-of-slice helper) */
extern unsigned long sk_00359a78(); /* FUN_00359a78 (out-of-slice helper) */
extern unsigned long sk_00359ad4(); /* FUN_00359ad4 (out-of-slice helper) */
extern unsigned long sk_00359b64(); /* FUN_00359b64 (out-of-slice helper) */
extern unsigned long sk_00359be0(); /* FUN_00359be0 (out-of-slice helper) */
extern unsigned long sk_00359bec(); /* FUN_00359bec (out-of-slice helper) */
extern unsigned long sk_00359ca4(); /* FUN_00359ca4 (out-of-slice helper) */
extern unsigned long sk_00359d9c(); /* FUN_00359d9c (out-of-slice helper) */
extern unsigned long sk_00359e14(); /* FUN_00359e14 (out-of-slice helper) */
extern unsigned long sk_00359e40(); /* FUN_00359e40 (out-of-slice helper) */
extern unsigned long sk_0035a01c(); /* FUN_0035a01c (out-of-slice helper) */
extern unsigned long sk_0035a040(); /* FUN_0035a040 (out-of-slice helper) */
extern unsigned long sk_0035a0b8(); /* FUN_0035a0b8 (out-of-slice helper) */
extern unsigned long sk_0035a184(); /* FUN_0035a184 (out-of-slice helper) */
extern unsigned long sk_0035a19c(); /* FUN_0035a19c (out-of-slice helper) */
extern unsigned long sk_0035a1c0(); /* FUN_0035a1c0 (out-of-slice helper) */
extern unsigned long sk_0035a274(); /* FUN_0035a274 (out-of-slice helper) */
extern unsigned long sk_0035a2b8(); /* FUN_0035a2b8 (out-of-slice helper) */
extern unsigned long sk_0035a2c4(); /* FUN_0035a2c4 (out-of-slice helper) */
extern unsigned long sk_0035a3dc(); /* FUN_0035a3dc (out-of-slice helper) */
extern unsigned long sk_0035a438(); /* FUN_0035a438 (out-of-slice helper) */
extern unsigned long sk_0035a4bc(); /* FUN_0035a4bc (out-of-slice helper) */
extern unsigned long sk_0035a4d4(); /* FUN_0035a4d4 (out-of-slice helper) */
extern unsigned long sk_0035a4f8(); /* FUN_0035a4f8 (out-of-slice helper) */
extern unsigned long sk_0035a590(); /* FUN_0035a590 (out-of-slice helper) */
extern unsigned long sk_0035a59c(); /* FUN_0035a59c (out-of-slice helper) */
extern unsigned long sk_0035a684(); /* FUN_0035a684 (out-of-slice helper) */
extern unsigned long sk_0035a6e8(); /* FUN_0035a6e8 (out-of-slice helper) */
extern unsigned long sk_0035a81c(); /* FUN_0035a81c (out-of-slice helper) */
extern unsigned long sk_0035abe4(); /* FUN_0035abe4 (out-of-slice helper) */
extern unsigned long sk_0035acfc(); /* FUN_0035acfc (out-of-slice helper) */
extern unsigned long sk_0036a908(); /* FUN_0036a908 (out-of-slice helper) */
extern unsigned long sk_0036a940(); /* FUN_0036a940 (out-of-slice helper) */
extern unsigned long sk_0036a9a0(); /* FUN_0036a9a0 (out-of-slice helper) */
extern unsigned long sk_0036b118(); /* FUN_0036b118 (out-of-slice helper) */
extern unsigned long sk_0036b270(); /* FUN_0036b270 (out-of-slice helper) */
extern unsigned long sk_0036b2d0(); /* FUN_0036b2d0 (out-of-slice helper) */
extern unsigned long sk_003722e4(); /* FUN_003722e4 (out-of-slice helper) */
extern unsigned long sk_00376820(); /* FUN_00376820 (out-of-slice helper) */
extern unsigned long sk_00377824(); /* FUN_00377824 (out-of-slice helper) */
extern unsigned long sk_00377bec(); /* FUN_00377bec (out-of-slice helper) */
extern unsigned long sk_003a25d4(); /* FUN_003a25d4 (out-of-slice helper) */
extern unsigned long sk_003a261c(); /* FUN_003a261c (out-of-slice helper) */
extern unsigned long sk_00610504(); /* FUN_00610504 (out-of-slice helper) */
extern unsigned long sk_t_00012568(); /* FUN_t_00012568 (out-of-slice helper) */
extern unsigned long sk_t_000126e8(); /* FUN_t_000126e8 (out-of-slice helper) */
extern unsigned long sk_t_001a0754(); /* FUN_t_001a0754 (out-of-slice helper) */
extern unsigned long sk_t_001a0774(); /* FUN_t_001a0774 (out-of-slice helper) */
extern unsigned long sk_t_002298d4(); /* FUN_t_002298d4 (out-of-slice helper) */
extern void sk_t_0026c2a0(undefined8 param_1,long param_2); /* FUN_t_0026c2a0 (out-of-slice helper) */
extern unsigned long sk_t_002a2698(); /* FUN_t_002a2698 (out-of-slice helper) */
extern unsigned long sk_t_0036b270(); /* FUN_t_0036b270 (out-of-slice helper) */

extern unsigned long sk_breakpoint(); /* SoftwareBreakpoint (noreturn trap) */

/* ---- External globals / string constants ---- */
extern unsigned long _g_004baeb0; /* Ghidra global */
extern unsigned long g_003471a4; /* Ghidra global */
extern unsigned long g_003471a8; /* Ghidra global */
extern unsigned long g_004bbc30; /* Ghidra global */
extern unsigned long g_004c06e0; /* Ghidra global */
extern unsigned long g_004e7fa8; /* Ghidra global */
extern unsigned long g_004e8b7c; /* Ghidra global */
extern unsigned long g_004e8b98; /* Ghidra global */
extern unsigned long g_004e8bb4; /* Ghidra global */
extern unsigned long g_004e8bd0; /* Ghidra global */
extern unsigned long g_004ec334; /* Ghidra global */
extern unsigned long g_004edcec; /* Ghidra global */
extern unsigned long g_004edd08; /* Ghidra global */
extern unsigned long g_004f2670; /* Ghidra global */
extern unsigned long g_005be7c0; /* Ghidra global */
extern unsigned long g_0060e208; /* Ghidra global */
extern unsigned long g_0060e22c; /* Ghidra global */
extern unsigned long g_0060e230; /* Ghidra global */
extern unsigned long g_0060e238; /* Ghidra global */
extern unsigned long g_0061052c; /* Ghidra global */
extern unsigned long g_00611b24; /* Ghidra global */
extern unsigned long sk_t_001dc298(); /* FUN_t_001dc298 (out-of-slice helper) */
/* Ghidra L_ data symbols (address-of data references) */
extern unsigned char L_0031ad8c; extern unsigned char L_0031adbc;
extern unsigned char L_0031adec; extern unsigned char L_0031ae1c;
extern unsigned char L_0031ae7c; extern unsigned char L_0031aeac;
extern unsigned char L_0031aedc; extern unsigned char L_0031af0c;
extern unsigned char L_0031af3c; extern unsigned char L_0031af9c;
extern unsigned char L_0060e218; extern unsigned char L_00611b34;
extern unsigned long g_0064c260; /* Ghidra global */
extern unsigned long g_0064e888; /* Ghidra global */
extern unsigned long g_00657778; /* Ghidra global */
extern unsigned long (*g_00658c00)(); /* Ghidra global (function pointer) */
extern unsigned long ram00000000004baeb8; /* Ghidra global */
extern unsigned char Can_t_construct_ContiguousArray_w_005cedd0_str[]; /* Ghidra string s_Can_t_construct_ContiguousArray_w_005cedd0 */
extern unsigned char Can_t_reassign_buffer_in_Array_u_005d39b0_str[]; /* Ghidra string s_Can_t_reassign_buffer_in_Array_u_005d39b0 */
extern unsigned char ContiguousArray_withUnsafeMutabl_005d3d30_str[]; /* Ghidra string s_ContiguousArray_withUnsafeMutabl_005d3d30 */
extern unsigned char Division_results_in_an_overflow_i_005ceb20_str[]; /* Ghidra string s_Division_results_in_an_overflow_i_005ceb20 */
extern unsigned char Encoder_has_not_implemented_supp_005ceb60_str[]; /* Ghidra string s_Encoder_has_not_implemented_supp_005ceb60 */
extern unsigned char Fatal_error_005accd0_str[]; /* Ghidra string s_Fatal_error_005accd0 */
extern unsigned char Index_out_of_bounds_005cdab0_str[]; /* Ghidra string s_Index_out_of_bounds_005cdab0 */
extern unsigned char Initialized_count_set_to_greater_005d3970_str[]; /* Ghidra string s_Initialized_count_set_to_greater_005d3970 */
extern unsigned char Invalid_slice_005cfa58_str[]; /* Ghidra string s_Invalid_slice_005cfa58 */
extern unsigned char Range_out_of_bounds_005cec20_str[]; /* Ghidra string s_Range_out_of_bounds_005cec20 */
extern unsigned char Range_requires_lowerBound__str[]; /* Ghidra string s_Range_requires_lowerBound_ */
extern unsigned char __upp_005cda00; /* Ghidra data @ 0x005cda00 (uppercase map) */
extern unsigned char Swift_Collection_swift_005cdad0_str[]; /* Ghidra string s_Swift_Collection_swift_005cdad0 */
extern unsigned char Swift_ContiguousArray_swift_005cecd0_str[]; /* Ghidra string s_Swift_ContiguousArray_swift_005cecd0 */
extern unsigned char Swift_Optional_swift_005ce1f0_str[]; /* Ghidra string s_Swift_Optional_swift_005ce1f0 */
extern unsigned char Swift_Range_swift_005cda30_str[]; /* Ghidra string s_Swift_Range_swift_005cda30 */
extern unsigned char Swift_UnsafeBufferPointer_swift_005cdc10_str[]; /* Ghidra string s_Swift_UnsafeBufferPointer_swift_005cdc10 */
extern unsigned char Swift_UnsafeRawBufferPointer_swi_005cde40_str[]; /* Ghidra string s_Swift_UnsafeRawBufferPointer_swi_005cde40 */
extern unsigned char UnsafeBufferPointer_has_a_nil_st_005cf020_str[]; /* Ghidra string s_UnsafeBufferPointer_has_a_nil_st_005cf020 */
extern unsigned char UnsafeBufferPointer_with_negativ_005cdf60_str[]; /* Ghidra string s_UnsafeBufferPointer_with_negativ_005cdf60 */
extern unsigned char UnsafeRawBufferPointer_has_a_nil_005cdf20_str[]; /* Ghidra string s_UnsafeRawBufferPointer_has_a_nil_005cdf20 */
extern unsigned char lower_upper_005e1f90_str[]; /* Ghidra string s_lower_upper_005e1f90 */
extern unsigned char uespemosmodnarodarenegylsetybdet_004e7a30_str[]; /* Ghidra string s_uespemosmodnarodarenegylsetybdet_004e7a30 */
extern unsigned char unsafelyUnwrapped_of_nil_optiona_005ce1c0_str[]; /* Ghidra string s_unsafelyUnwrapped_of_nil_optiona_005ce1c0 */


/* ---- In-file forward declarations (called before definition) ---- */
void sk_001d0100(void);
void sk_001d01f4(void);
ulong sk_001d02e8(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001d0380(undefined8 param_1,undefined8 param_2,undefined8 param_3);
ulong sk_001d0414(undefined8 param_1,undefined8 param_2,undefined8 param_3);
ulong sk_001d04b0(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001d0548(void);
void sk_001d054c(void);
void sk_001d0564(void);
void sk_001d0568(void);
void sk_001d0594(void);
void sk_001d0598(void);
void sk_001d05c4(void);
void sk_001d05c8(void);
void sk_001d05e0(void);
void sk_001d05e4(void);
void sk_001d05fc(void);
void sk_001d0600(void);
void sk_001d0618(void);
void sk_001d061c(void);
void sk_001d0634(void);
void sk_001d0638(void);
ulong sk_001d0664(void);
void sk_001d06fc(void);
void sk_001d0700(void);
ulong sk_001d072c(void);
void sk_001d07c4(void);
void sk_001d07c8(void);
ulong sk_001d07e0(void);
void sk_001d0878(void);
void sk_001d087c(void);
void sk_001d0894(void);
void sk_001d0920(void);
void sk_001d0924(void);
void sk_001d093c(void);
void sk_001d09cc(void);
void sk_001d0aa4(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001d0b8c(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001d0c74(void);
void sk_001d0cd4(void);
void sk_001d0e38(void);
void sk_001d0fcc(void);
void sk_001d1124(void);
void sk_001d1280(void);
void sk_001d1284(void);
void sk_001d12b0(void);
void sk_001d12b4(void);
void sk_001d12e0(void);
void sk_001d12e4(void);
void sk_001d1310(void);
void sk_001d1314(void);
void sk_001d1340(void);
void sk_001d1344(void);
void sk_001d1370(void);
void sk_001d14d4(void);
void sk_001d14d8(void);
void sk_001d1504(void);
void sk_001d1508(void);
void sk_001d1534(void);
void sk_001d1538(void);
void sk_001d1564(void);
void sk_001d16c0(void);
void sk_001d16c4(void);
void sk_001d16f0(void);
void sk_001d184c(void);
void sk_001d1850(void);
void sk_001d187c(void);
void sk_001d19d8(void);
void sk_001d19dc(void);
void sk_001d1a08(void);
void sk_001d1a0c(void);
void sk_001d1a38(void);
void sk_001d1bc0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6);
void sk_001d1e00(void);
void sk_001d1e18(void);
ulong sk_001d1e30(void);
void sk_001d1ec0(void);
ulong sk_001d1f4c(void);
ulong sk_001d1fe0(void);
void sk_001d2070(undefined8 param_1,undefined8 param_2);
void sk_001d2074(undefined8 param_1,undefined8 param_2);
void sk_001d20a0(undefined8 param_1,undefined8 param_2);
void sk_001d20a4(undefined8 param_1,undefined8 param_2);
void sk_001d20d0(undefined8 param_1,undefined8 param_2);
void sk_001d20d4(undefined8 param_1,undefined8 param_2);
void sk_001d2100(undefined8 param_1,undefined8 param_2);
void sk_001d2104(undefined8 param_1,undefined8 param_2);
void sk_001d2130(undefined8 param_1,undefined8 param_2);
void sk_001d2134(undefined8 param_1,undefined8 param_2);
void sk_001d2160(undefined8 param_1,undefined8 param_2);
void sk_001d2164(undefined8 param_1,undefined8 param_2);
void sk_001d2190(undefined8 param_1,undefined8 param_2);
void sk_001d2194(undefined8 param_1,undefined8 param_2);
void sk_001d21c0(undefined8 param_1,undefined8 param_2);
void sk_001d21c4(undefined8 param_1,undefined8 param_2);
ulong sk_001d21f0(void);
void sk_001d2288(undefined8 param_1,undefined8 param_2);
void sk_001d228c(undefined8 param_1,undefined8 param_2);
ulong sk_001d22b8(void);
void sk_001d2350(undefined8 param_1,undefined8 param_2);
void sk_001d2354(undefined8 param_1,undefined8 param_2);
ulong sk_001d2380(void);
void sk_001d2418(undefined8 param_1,undefined8 param_2);
void sk_001d241c(undefined8 param_1,undefined8 param_2);
void sk_001d2448(void);
void sk_001d24d4(undefined8 param_1,undefined8 param_2);
void sk_001d24d8(undefined8 param_1,undefined8 param_2);
void sk_001d2504(void);
void sk_001d2594(void);
void sk_001d2658(void);
void sk_001d269c(void);
void sk_001d26e0(void);
void sk_001d2754(void);
void sk_001d27c8(void);
void sk_001d283c(void);
void sk_001d28b0(void);
void sk_001d28f4(void);
void sk_001d2954(void);
void sk_001d2c60(void);
void sk_001d2d1c(long param_1,long param_2,long param_3);
void sk_001d2d5c(void);
void sk_001d2dcc(void);
void sk_001d2df0(void);
void sk_001d2eb4(void);
void sk_001d2f1c(void);
void sk_001d2f4c(ulong param_1,ulong param_2,ulong param_3,ulong param_4);
void sk_001d2f94(void);
void sk_001d30f8(void);
void sk_001d31b0(void);
void sk_001d332c(void);
void sk_001d36d8(void);
void sk_001d36e8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5);
void sk_001d39cc(uint param_1,uint param_2);
void sk_001d3a30(long param_1,long param_2);
void sk_001d3a94(void);
void sk_001d3b40(void);
void sk_001d3b98(long param_1,long param_2);
void sk_001d3c10(void);
void sk_001d3fc0(void);
void sk_001d3fd0(void);
void sk_001d4514(void);
void sk_001d4544(void);
void sk_001d4548(void);
void sk_001d4584(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001d4f3c(void);
void sk_001d4f4c(void);
void sk_001d58fc(void);
void sk_001d5c90(void);
void sk_001d5f58(void);
void sk_001d6094(void);
void sk_001d614c(undefined8 param_1,undefined8 param_2,void (*param_3)(),undefined8 param_4, undefined8 param_5,undefined8 param_6);
uint sk_001d69d8(undefined8 param_1,undefined8 param_2,uint param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7);
void sk_001d6ef0(void);
void sk_001d7368(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001d7814(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001d80e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001d83cc(void);
void sk_001d852c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001d8808(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5);
void sk_001d88fc(undefined8 param_1,void (*param_2)(),undefined8 param_3,long param_4,long param_5, undefined8 param_6,undefined8 param_7,undefined8 param_8);
void sk_001d8b38(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
uint sk_001d8cdc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5);
void sk_001d8d78(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
undefined8 sk_001d96e0(uint param_1,uint param_2);
uint sk_001d974c(uint param_1,uint param_2);
void sk_001d97b4(undefined8 param_1,undefined8 param_2,ulong param_3);
void sk_001d9840(long param_1,undefined8 param_2,long param_3);
void sk_001d9890(void);
undefined8 sk_001d9988(void);
void sk_001d9a40(undefined8 param_1,undefined8 param_2);
void sk_001d9a94(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001d9b00(void);
void sk_001d9b18(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001d9f28(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6);
ulong sk_001da01c(void (*param_1)());
long sk_001da1c0(void (*param_1)());
void sk_001da324(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001da714(undefined8 param_1,undefined8 param_2,void (*param_3)(),undefined8 param_4, undefined8 param_5,undefined8 param_6);
void sk_001daea8(void);
void sk_001db6b0(void);
void sk_001db938(void);
void sk_001dba34(void);
void sk_001dbc14(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001dbc64(void);
void sk_001dbd68(void);
void sk_001dbe74(void);
void sk_001dbf84(ulong param_1);
void sk_001dbffc(void);
void sk_001dc050(void);
void sk_001dc09c(void);
void sk_001dc0fc(undefined8 param_1,ulong param_2);
void sk_001dc130(void);
void sk_001dc1f4(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001dc23c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5);
void sk_001dc298(long param_1);
void sk_001dc2ec(void);
void sk_001dc304(long param_1,long param_2);
void sk_001dc3b8(undefined8 param_1,long param_2);
void sk_001dc3e8(void);
void sk_001dc430(undefined8 param_1,ulong param_2,long param_3,long param_4);
void sk_001dc4c0(undefined8 param_1,undefined8 param_2,undefined8 param_3,void (*param_4)(), void (*param_5)());
void sk_001dc554(void);
void sk_001dc56c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, void (*param_5)());
void sk_001dc5c4(void);
void sk_001dc620(undefined8 param_1,undefined8 param_2,long param_3,ulong param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,void (*param_8)());
void sk_001dc754(void);
void sk_001dc870(void);
void sk_001dc8f4(undefined8 param_1,undefined8 param_2,void (*param_3)());
void sk_001dc9bc(undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4, void (*param_5)(),void (*param_6)(),void (*jumptable)());
void sk_001dcbac(undefined8 param_1,undefined8 param_2,void (*param_3)());
void sk_001dcc34(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5);
void sk_001dccb4(void);
void sk_001dccd0(void);
undefined * sk_001dcd20(long *param_1,undefined8 *param_2,long param_3);
void sk_001dce5c(undefined8 *param_1,long param_2,undefined8 param_3,void (*param_4)());
void sk_001dcea0(undefined8 param_1,undefined8 param_2);
void sk_001dcf0c(undefined8 param_1);
undefined8 sk_001dcf90(void);
void sk_001dd024(void);
void sk_001dd104(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
void sk_001dd108(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
void sk_001dd128(void);
void sk_001dd154(void);
void sk_001dd1ec(void);
void sk_001dd220(undefined8 *param_1,undefined8 param_2,long param_3);
void sk_001dd24c(void);
void sk_001dd264(void);
void sk_001dd374(long param_1);
void sk_001dd408(undefined8 param_1,undefined8 param_2);
void sk_001dd420(undefined8 param_1,undefined8 param_2,void (*param_3)());
undefined * sk_001dd460(long param_1);
void sk_001dd4cc(long param_1);
void sk_001dd58c(long param_1,uint param_2,void (*jumptable)());
void sk_001dd614(long param_1,uint param_2,long param_3,void (*jumptable)());
void sk_001dd6ac(void);
void sk_001dd6cc(void);
void sk_001dd77c(void);
void sk_001dd7f4(undefined8 param_1,void (*jumptable)());
void sk_001dd858(long param_1);
void sk_001dd88c(long param_1,undefined8 param_2,void (*jumptable)());
void sk_001dd8cc(long param_1,undefined8 param_2,long param_3);
void sk_001ddb2c(void);
void sk_001ddd5c(void);
void sk_001de04c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001de4d4(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001de4d8(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001de508(void);
void sk_001de698(void);
void sk_001de6c4(void);
void sk_001de7c8(void);
void sk_001de8a8(void);
void sk_001de960(undefined8 *param_1,undefined8 param_2,undefined8 param_3,long param_4);
void sk_001de9bc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001dea34(undefined8 param_1,undefined8 param_2);
void sk_001dea60(undefined8 param_1,undefined8 param_2,void (*param_3)());
void sk_001deae8(undefined8 *param_1,long param_2);
void sk_001debac(undefined8 param_1,undefined8 param_2,void (*param_3)());
void sk_001dec50(undefined8 param_1,undefined8 param_2,void (*param_3)());
void sk_001ded00(long *param_1,long param_2,long *param_3,long *param_4,long *param_5);
void sk_001dedcc(void);
void sk_001dedd0(void);
void sk_001dedf8(void);
void sk_001dee70(undefined8 param_1,undefined8 param_2,undefined8 param_3);
void sk_001def38(long *param_1,long param_2,long param_3);
void sk_001defb0(void);
void sk_001defc8(void);
void sk_001df16c(void);
void sk_001df2a0(void);
void sk_001df2f4(void);
void sk_001df2f8(void);
void sk_001df334(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, void (*param_5)(),void (*param_6)());
void sk_001df428(long *param_1,void (*param_2)(),undefined8 param_3,long param_4);
void sk_001df4e4(void);
void sk_001df510(long param_1,long param_2,void (*param_3)(),undefined8 param_4,long param_5);
void sk_001df5a4(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
void sk_001df5a8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
void sk_001df5c8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
void sk_001df5cc(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4);
void sk_001df5ec(void);
void sk_001df604(void);
void sk_001df790(long param_1,long param_2);
void sk_001df7dc(void);
void sk_001df7f4(undefined8 param_1,undefined8 param_2,long param_3,long param_4,long param_5);
void sk_001df870(void (*param_1)(),undefined8 param_2,undefined8 param_3,long param_4);
void sk_001df924(void (*param_1)());
void sk_001df958(undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4);
void sk_001df98c(undefined8 param_1,void (*param_2)());
void sk_001dfa60(undefined8 param_1);
void sk_001dfadc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001dfb7c(void);
void sk_001dfba8(undefined8 param_1);
void sk_001dfc28(long param_1,long param_2,void (*param_3)());
void sk_001dfc88(undefined8 param_1,void (*param_2)(),undefined8 param_3,undefined8 param_4);
void sk_001dfec0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4);
void sk_001dff60(long param_1,long param_2);
void sk_001dffa0(void);

/* FUN_001d0100 @ 0x001d0100   (est. sk_r5_swift_001d0100) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0100(void)

{
  undefined8 stk00000008;
  long n1;
  undefined8 t2;
  undefined8 ax4;
  unsigned long (*eo8)();
  long eo16;
  undefined8 rx20;
  long *rx22;
  undefined8 rx26;
  undefined8 rx27;
  undefined8 rx30;
  
  sk_003563c4();
  sk_00354b2c();
  sk_003537fc();
  sk_00349b88();
  sk_00353918();
  n1 = sk_0034f7ec(0x676ed0);
  *rx22 = n1;
  *(undefined8 *)(n1 + 0x10) = rx27;
  *(undefined8 *)(n1 + 0x18) = rx26;
  sk_0031a5dc(ax4);
  sk_0034bccc();
  (*eo8)();
  sk_0034dcfc();
  t2 = sk_00002534();
  n1 = sk_0036a9a0(t2,&stk00000008);
  t2 = _g_004baeb0;
  *(undefined8 *)(n1 + 0x18) = ram00000000004baeb8;
  *(undefined8 *)(n1 + 0x10) = t2;
  sk_0034dc3c();
  sk_00377824();
  sk_0034b960();
  sk_00377bec();
  sk_0035893c();
  sk_00319a4c();
  sk_0034dae8();
  (**(unsigned long (**)() )(eo16 + 0x10))();
  sk_00356600();
  sk_001a18f8();
  sk_0035a81c(rx20);
  sk_003563a8(rx30);
  return;
}

/* FUN_001d01f4 @ 0x001d01f4   (est. sk_r5_swift_001d01f4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d01f4(void)

{
  undefined8 stk00000008;
  long n1;
  undefined8 t2;
  undefined8 ax4;
  unsigned long (*eo8)();
  long eo16;
  undefined8 rx20;
  long *rx22;
  undefined8 rx26;
  undefined8 rx27;
  undefined8 rx30;
  
  sk_003563c4();
  sk_00354b2c();
  sk_003537fc();
  sk_00349b88();
  sk_00353918();
  n1 = sk_0034f7ec(0x6773c0);
  *rx22 = n1;
  *(undefined8 *)(n1 + 0x10) = rx27;
  *(undefined8 *)(n1 + 0x18) = rx26;
  sk_0031a5dc(ax4);
  sk_0034bccc();
  (*eo8)();
  sk_0034dcfc();
  t2 = sk_00002534();
  n1 = sk_0036a9a0(t2,&stk00000008);
  t2 = _g_004baeb0;
  *(undefined8 *)(n1 + 0x18) = ram00000000004baeb8;
  *(undefined8 *)(n1 + 0x10) = t2;
  sk_0034dc3c();
  sk_00377824();
  sk_0034b960();
  sk_00377bec();
  sk_0035893c();
  sk_00319a4c();
  sk_0034dae8();
  (**(unsigned long (**)() )(eo16 + 0x10))();
  sk_00356600();
  sk_001a18f8();
  sk_0035a81c(rx20);
  sk_003563a8(rx30);
  return;
}

/* FUN_001d02e8 @ 0x001d02e8   (est. sk_r5_swift_001d02e8) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d02e8(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  uint t1;
  ulong t2;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  
  sk_0034c59c();
  sk_0031a60c(param_3);
  sk_0034ca08();
  t2 = (*eo8)();
  if ((t2 & 1) != 0) {
    sk_0031a63c();
    sk_0034affc();
    t2 = (*eo8_00)();
    if (rx21 != 0) {
      return t2;
    }
    if ((t2 & 1) == 0) {
      sk_0031a66c();
      sk_0034affc();
      t1 = (*eo8_01)();
      return (ulong)(t1 & 1);
    }
  }
  return 2;
}

/* FUN_001d0380 @ 0x001d0380   (est. sk_r5_swift_001d0380) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0380(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ulong t1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  
  sk_0034c59c();
  sk_0031a60c(param_3);
  sk_0034ca08();
  t1 = (*eo8)();
  if ((t1 & 1) != 0) {
    sk_0031a63c();
    sk_0034affc();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return;
    }
    if ((t1 & 1) == 0) {
      sk_0031a69c();
      sk_0034affc();
      (*eo8_01)();
      return;
    }
  }
  sk_00019858();
  return;
}

/* FUN_001d0414 @ 0x001d0414   (est. sk_r5_swift_001d0414) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d0414(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ulong t1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  
  sk_0034c59c();
  sk_0031a60c(param_3);
  sk_0034ca08();
  t1 = (*eo8)();
  if ((t1 & 1) != 0) {
    sk_0031a63c();
    sk_0034affc();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return t1;
    }
    if ((t1 & 1) == 0) {
      sk_0031a6cc();
      sk_0034affc();
      t1 = (*eo8_01)();
      return t1;
    }
  }
  t1 = sk_00068e14();
  return t1;
}

/* FUN_001d04b0 @ 0x001d04b0   (est. sk_r5_swift_001d04b0) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d04b0(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  ulong t1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  uint t2;
  
  sk_0034c59c();
  sk_0031a60c(param_3);
  sk_0034ca08();
  t1 = (*eo8)();
  if ((t1 & 1) != 0) {
    sk_0031a63c();
    sk_0034affc();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return t1;
    }
    if ((t1 & 1) == 0) {
      sk_0031a6fc();
      sk_0034affc();
      t2 = (*eo8_01)();
      return (ulong)t2;
    }
  }
  return 0x100000000;
}

/* FUN_001d0548 @ 0x001d0548   (est. sk_r5_swift_001d0548) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0548(void)

{
  sk_00354210();
  sk_001d0894();
  return;
}

/* FUN_001d054c @ 0x001d054c   (est. sk_r5_swift_001d054c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d054c(void)

{
  sk_00354210();
  sk_001d0894();
  return;
}

/* FUN_001d0564 @ 0x001d0564   (est. sk_r5_swift_001d0564) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0564(void)

{
  sk_001d0664();
  return;
}

/* FUN_001d0568 @ 0x001d0568   (est. sk_r5_swift_001d0568) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0568(void)

{
  sk_001d0664();
  return;
}

/* FUN_001d0594 @ 0x001d0594   (est. sk_r5_swift_001d0594) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0594(void)

{
  sk_001d072c();
  return;
}

/* FUN_001d0598 @ 0x001d0598   (est. sk_r5_swift_001d0598) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0598(void)

{
  sk_001d072c();
  return;
}

/* FUN_001d05c4 @ 0x001d05c4   (est. sk_r5_swift_001d05c4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d05c4(void)

{
  sk_003541f4();
  sk_001d07e0();
  return;
}

/* FUN_001d05c8 @ 0x001d05c8   (est. sk_r5_swift_001d05c8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d05c8(void)

{
  sk_003541f4();
  sk_001d07e0();
  return;
}

/* FUN_001d05e0 @ 0x001d05e0   (est. sk_r5_swift_001d05e0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d05e0(void)

{
  sk_003541d8();
  sk_001d0894();
  return;
}

/* FUN_001d05e4 @ 0x001d05e4   (est. sk_r5_swift_001d05e4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d05e4(void)

{
  sk_003541d8();
  sk_001d0894();
  return;
}

/* FUN_001d05fc @ 0x001d05fc   (est. sk_r5_swift_001d05fc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d05fc(void)

{
  sk_003541bc();
  sk_001d093c();
  return;
}

/* FUN_001d0600 @ 0x001d0600   (est. sk_r5_swift_001d0600) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0600(void)

{
  sk_003541bc();
  sk_001d093c();
  return;
}

/* FUN_001d0618 @ 0x001d0618   (est. sk_r5_swift_001d0618) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0618(void)

{
  sk_003541a0();
  sk_001d0894();
  return;
}

/* FUN_001d061c @ 0x001d061c   (est. sk_r5_swift_001d061c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d061c(void)

{
  sk_003541a0();
  sk_001d0894();
  return;
}

/* FUN_001d0634 @ 0x001d0634   (est. sk_r5_swift_001d0634) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0634(void)

{
  sk_001d0664();
  return;
}

/* FUN_001d0638 @ 0x001d0638   (est. sk_r5_swift_001d0638) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0638(void)

{
  sk_001d0664();
  return;
}

/* FUN_001d0664 @ 0x001d0664   (est. sk_r5_sched_op_001d0664) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d0664(void)

{
  uint t1;
  ulong t2;
  int iv3;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034af60();
  t2 = (*eo8)();
  if ((t2 & 1) != 0) {
    sk_0031a63c();
    sk_0034a528();
    t2 = (*eo8_00)();
    if (rx21 != 0) {
      return t2;
    }
    if ((t2 & 1) == 0) {
      (*rx25)();
      sk_0034a528();
      t1 = (*eo8_01)();
      iv3 = 0;
      goto L_001d06b8;
    }
  }
  t1 = 0;
  iv3 = 1;
L_001d06b8:
  return (ulong)(t1 & 0xff | iv3 << 8);
}

/* FUN_001d06fc @ 0x001d06fc   (est. sk_r5_swift_001d06fc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d06fc(void)

{
  sk_001d072c();
  return;
}

/* FUN_001d0700 @ 0x001d0700   (est. sk_r5_swift_001d0700) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0700(void)

{
  sk_001d072c();
  return;
}

/* FUN_001d072c @ 0x001d072c   (est. sk_r5_sched_op_001d072c) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d072c(void)

{
  uint t1;
  ulong t2;
  uint t3;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034af60();
  t2 = (*eo8)();
  if ((t2 & 1) != 0) {
    sk_0031a63c();
    sk_0034a528();
    t2 = (*eo8_00)();
    if (rx21 != 0) {
      return t2;
    }
    if ((t2 & 1) == 0) {
      (*rx25)();
      sk_0034a528();
      t1 = (*eo8_01)();
      t3 = 0;
      goto L_001d0780;
    }
  }
  t1 = 0;
  t3 = 0x10000;
L_001d0780:
  return (ulong)(t3 | t1 & 0xffff);
}

/* FUN_001d07c4 @ 0x001d07c4   (est. sk_r5_swift_001d07c4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d07c4(void)

{
  sk_00354184();
  sk_001d07e0();
  return;
}

/* FUN_001d07c8 @ 0x001d07c8   (est. sk_r5_swift_001d07c8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d07c8(void)

{
  sk_00354184();
  sk_001d07e0();
  return;
}

/* FUN_001d07e0 @ 0x001d07e0   (est. sk_r5_sched_op_001d07e0) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d07e0(void)

{
  ulong t1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  ulong t2;
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034af60();
  t1 = (*eo8)();
  if ((t1 & 1) != 0) {
    sk_0031a63c();
    sk_0034a528();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return t1;
    }
    if ((t1 & 1) == 0) {
      (*rx25)();
      sk_0034a528();
      t1 = (*eo8_01)();
      t2 = 0;
      goto L_001d0834;
    }
  }
  t1 = 0;
  t2 = 0x100000000;
L_001d0834:
  return t2 | t1 & 0xffffffff;
}

/* FUN_001d0878 @ 0x001d0878   (est. sk_r5_swift_001d0878) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0878(void)

{
  sk_00354168();
  sk_001d0894();
  return;
}

/* FUN_001d087c @ 0x001d087c   (est. sk_r5_swift_001d087c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d087c(void)

{
  sk_00354168();
  sk_001d0894();
  return;
}

/* FUN_001d0894 @ 0x001d0894   (est. sk_r5_sched_op_001d0894) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0894(void)

{
  ulong t1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034af60();
  t1 = (*eo8)();
  if ((t1 & 1) != 0) {
    sk_0031a63c();
    sk_0034a528();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return;
    }
    if ((t1 & 1) == 0) {
      (*rx25)();
      sk_0034a528();
      (*eo8_01)();
      return;
    }
  }
  sk_00068e14();
  return;
}

/* FUN_001d0920 @ 0x001d0920   (est. sk_r5_swift_001d0920) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0920(void)

{
  sk_0035414c();
  sk_001d093c();
  return;
}

/* FUN_001d0924 @ 0x001d0924   (est. sk_r5_swift_001d0924) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0924(void)

{
  sk_0035414c();
  sk_001d093c();
  return;
}

/* FUN_001d093c @ 0x001d093c   (est. sk_r5_sched_op_001d093c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d093c(void)

{
  ulong t1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034af60();
  t1 = (*eo8)();
  if ((t1 & 1) != 0) {
    sk_0031a63c();
    sk_0034a528();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return;
    }
    if ((t1 & 1) == 0) {
      (*rx25)();
      sk_0034a528();
      (*eo8_01)();
      return;
    }
  }
  sk_003509f8(0);
  return;
}

/* FUN_001d09cc @ 0x001d09cc   (est. sk_r5_swift_001d09cc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d09cc(void)

{
  ulong t1;
  undefined8 ax4;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo9)();
  long rx21;
  sk_c16_t at2;
  
  sk_0031a60c(ax4);
  at2._0_8_ = (undefined8)(sk_0034e66c());
  at2._8_8_ = 0;
  t1 = (*eo8)(at2._0_8_,at2._8_8_,ax4);
  if ((t1 & 1) != 0) {
    sk_0031a63c(ax4);
    sk_00350a40();
    sk_00351300();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return;
    }
    if ((t1 & 1) == 0) {
      sk_0031a96c(ax4);
      sk_00350390();
      sk_000dbf08();
      sk_0035a4bc();
      (*eo9)();
      sk_00354d5c();
      goto L_001d0a4c;
    }
  }
  sk_0035172c();
L_001d0a4c:
  sk_00352480();
  sk_000839d8();
  return;
}

/* FUN_001d0aa4 @ 0x001d0aa4   (est. sk_r5_swift_001d0aa4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0aa4(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 stk00000008;
  undefined8 t1;
  long n2;
  unsigned long (*eo8)();
  long eo16;
  undefined8 rx20;
  undefined8 *rx22;
  undefined8 rx30;
  
  sk_003563c4();
  sk_00355bdc();
  sk_00348730();
  sk_00353918();
  sk_0031a5dc(param_3);
  sk_0034bccc();
  (*eo8)();
  sk_0034dcfc();
  t1 = sk_00002534();
  n2 = sk_0036a9a0(t1,&stk00000008);
  t1 = _g_004baeb0;
  *(undefined8 *)(n2 + 0x18) = ram00000000004baeb8;
  *(undefined8 *)(n2 + 0x10) = t1;
  sk_0034dc3c();
  sk_00377824();
  sk_0034b960();
  sk_00377bec();
  sk_0035893c();
  sk_00319a4c();
  sk_0034dae8();
  (**(unsigned long (**)() )(eo16 + 0x10))();
  sk_00356600();
  sk_001a18f8();
  *rx22 = 0x676ed0;
  rx22[1] = rx20;
  sk_00359088(0x80000000005ceba0);
  sk_003563a8(rx30);
  return;
}

/* FUN_001d0b8c @ 0x001d0b8c   (est. sk_r5_swift_001d0b8c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0b8c(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 stk00000008;
  undefined8 t1;
  long n2;
  unsigned long (*eo8)();
  long eo16;
  undefined8 rx20;
  undefined8 *rx22;
  undefined8 rx30;
  
  sk_003563c4();
  sk_00355bdc();
  sk_00348730();
  sk_00353918();
  sk_0031a5dc(param_3);
  sk_0034bccc();
  (*eo8)();
  sk_0034dcfc();
  t1 = sk_00002534();
  n2 = sk_0036a9a0(t1,&stk00000008);
  t1 = _g_004baeb0;
  *(undefined8 *)(n2 + 0x18) = ram00000000004baeb8;
  *(undefined8 *)(n2 + 0x10) = t1;
  sk_0034dc3c();
  sk_00377824();
  sk_0034b960();
  sk_00377bec();
  sk_0035893c();
  sk_00319a4c();
  sk_0034dae8();
  (**(unsigned long (**)() )(eo16 + 0x10))();
  sk_00356600();
  sk_001a18f8();
  *rx22 = 0x6773c0;
  rx22[1] = rx20;
  sk_00359088(0x80000000005cebd0);
  sk_003563a8(rx30);
  return;
}

/* FUN_001d0c74 @ 0x001d0c74   (est. sk_r5_swift_001d0c74) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0c74(void)

{
  undefined8 ax3;
  unsigned long (*eo8)();
  
  sk_0034d2b4();
  sk_0031a14c(ax3);
  sk_00357b20();
  sk_0035139c();
  (*eo8)();
  return;
}

/* FUN_001d0cd4 @ 0x001d0cd4   (est. sk_r5_swift_001d0cd4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0cd4(void)

{
  undefined8 stk00000008;
  byte bv1;
  undefined8 t2;
  undefined8 t3;
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo9)();
  long eo16;
  long rx19;
  unsigned long (*rx28)();
  undefined8 sv00000008;
  undefined8 sv00000038;
  
  sk_00353cfc();
  sk_00355e74();
  sk_003527ec();
  t2 = sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348dd8();
  sk_00377824();
  sk_00348d7c();
  sk_0007c1a4();
  (*g_00658c00)();
  t3 = sk_0034b0d4();
  sk_00352e24(t3,t2);
  (*eo8_00)();
  sk_000a68c4();
  sk_0034dbc8();
  (*eo9)();
  sk_0034b278();
  sk_00350ab8();
  sk_00377bec();
  sk_0035abe4();
  do {
    sk_00350738((long)&stk00000008 + 7);
    (*rx28)();
    bv1 = sv00000008._7_1_;
    if (sv00000008._7_1_ == 2) break;
    t2 = sk_0031a99c();
    sk_00350b48(t2,bv1 & 1);
    (*eo8_01)();
  } while (rx19 == 0);
  sk_003508f0(*(undefined8 *)(eo16 + 8));
  (*eo8_02)();
  sk_00351348();
  sk_00353d14(sv00000038);
  return;
}

/* FUN_001d0e38 @ 0x001d0e38   (est. sk_r5_swift_001d0e38) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0e38(void)

{
  long n1;
  undefined8 t2;
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo9)();
  long eo16;
  long rx19;
  unsigned long (*rx28)();
  undefined8 sv00000038;
  undefined1 v10 [8];
  long v8;
  
  sk_00353cfc();
  sk_00355e68();
  sk_003527ec();
  sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348dd8();
  sk_00377824();
  sk_00348d7c();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b0d4();
  (**(unsigned long (**)() )(eo16 + 0x10))();
  sk_000a68c4();
  sk_0034dbc8();
  (*eo9)();
  sk_0034b278();
  sk_00350ab8();
  sk_00377bec();
  sk_0035abe4();
  do {
    sk_00350738(v10);
    (*rx28)();
    n1 = v8;
    if (v8 == 0) {
      sk_0034e33c();
      (*eo8_01)();
L_001d0fb4:
      sk_00351348();
      sk_00353d14(sv00000038);
      return;
    }
    t2 = sk_0031a9cc();
    sk_00350af4(t2);
    sk_00352ae4();
    (*eo8_00)();
    if (rx19 != 0) {
      sk_0034e33c();
      (*eo8_02)();
      sk_003a25d4(n1);
      goto L_001d0fb4;
    }
    sk_003a25d4(n1);
  } while( true );
}

/* FUN_001d0fcc @ 0x001d0fcc   (est. sk_r5_swift_001d0fcc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d0fcc(void)

{
  undefined1 zr;
  undefined8 t1;
  undefined8 t2;
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo9)();
  long rx21;
  unsigned long (*rx28)();
  undefined8 sv00000028;
  undefined1 v10 [16];
  
  sk_003549e4();
  sk_00355e74();
  sk_003527ec();
  t1 = sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348dd8();
  sk_00377824();
  sk_00348d7c();
  sk_0007c1a4();
  (*g_00658c00)();
  t2 = sk_0034b0d4();
  sk_00352e24(t2,t1);
  (*eo8_00)();
  sk_000a68c4();
  sk_0034dbc8();
  (*eo9)();
  sk_0034b278();
  sk_00350ab8();
  sk_00377bec();
  sk_0035abe4();
  do {
    sk_00350738(v10);
    (*rx28)();
    sk_00359550();
    if ((bool)zr) break;
    sk_0031a9fc();
    sk_0035a684();
    sk_0034d9f8();
    (*eo8_01)();
  } while (rx21 == 0);
  sk_0034e33c();
  (*eo8_02)();
  sk_00351348();
  sk_00354a0c(sv00000028);
  return;
}

/* FUN_001d1124 @ 0x001d1124   (est. sk_r5_swift_001d1124) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1124(void)

{
  undefined8 t1;
  undefined8 t2;
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo9)();
  long rx21;
  unsigned long (*rx28)();
  undefined8 sv00000038;
  undefined1 v8 [4];
  char v4;
  
  sk_003549e4();
  sk_00355e74();
  sk_003527ec();
  t1 = sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348dd8();
  sk_00377824();
  sk_00348d7c();
  sk_0007c1a4();
  (*g_00658c00)();
  t2 = sk_0034b0d4();
  sk_00352e24(t2,t1);
  (*eo8_00)();
  sk_000a68c4();
  sk_0034dbc8();
  (*eo9)();
  sk_0034b278();
  sk_00350ab8();
  sk_00377bec();
  sk_0035abe4();
  do {
    sk_00350738(v8);
    (*rx28)();
    if (v4 == '\x01') break;
    sk_0031aa2c();
    sk_0035a684();
    sk_0034d9f8();
    (*eo8_01)();
  } while (rx21 == 0);
  sk_00351924();
  sk_003508f0();
  (*eo8_02)();
  sk_00351348();
  sk_00354a0c(sv00000038);
  return;
}

/* FUN_001d1280 @ 0x001d1280   (est. sk_r5_swift_001d1280) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1280(void)

{
  sk_001d1370();
  return;
}

/* FUN_001d1284 @ 0x001d1284   (est. sk_r5_swift_001d1284) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1284(void)

{
  sk_001d1370();
  return;
}

/* FUN_001d12b0 @ 0x001d12b0   (est. sk_r5_swift_001d12b0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d12b0(void)

{
  sk_001d1564();
  return;
}

/* FUN_001d12b4 @ 0x001d12b4   (est. sk_r5_swift_001d12b4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d12b4(void)

{
  sk_001d1564();
  return;
}

/* FUN_001d12e0 @ 0x001d12e0   (est. sk_r5_swift_001d12e0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d12e0(void)

{
  sk_001d16f0();
  return;
}

/* FUN_001d12e4 @ 0x001d12e4   (est. sk_r5_swift_001d12e4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d12e4(void)

{
  sk_001d16f0();
  return;
}

/* FUN_001d1310 @ 0x001d1310   (est. sk_r5_swift_001d1310) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1310(void)

{
  sk_001d187c();
  return;
}

/* FUN_001d1314 @ 0x001d1314   (est. sk_r5_swift_001d1314) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1314(void)

{
  sk_001d187c();
  return;
}

/* FUN_001d1340 @ 0x001d1340   (est. sk_r5_swift_001d1340) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1340(void)

{
  sk_001d1370();
  return;
}

/* FUN_001d1344 @ 0x001d1344   (est. sk_r5_swift_001d1344) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1344(void)

{
  sk_001d1370();
  return;
}

/* FUN_001d1370 @ 0x001d1370   (est. sk_r5_swift_001d1370) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1370(void)

{
  undefined1 zr;
  undefined8 t1;
  undefined8 t2;
  undefined8 ax4;
  unsigned long (*ax5)();
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo9)();
  long rx21;
  unsigned long (*rx23)();
  undefined8 sv00000028;
  undefined1 ast10 [16];
  
  sk_00353cfc();
  sk_00358600();
  sk_003547d4();
  t1 = sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348dd8();
  sk_00358f0c();
  sk_00377824();
  sk_00348cd0();
  sk_0007c1a4();
  (*g_00658c00)();
  t2 = sk_0034af20();
  sk_00352e24(t2,t1);
  (*eo8_00)();
  sk_000a68c4(ax4);
  t1 = sk_0034d434();
  (*eo9)(t1,ax4);
  sk_0034b278();
  sk_0034f544();
  sk_00377bec();
  sk_00355b74();
  do {
    sk_003508b4(ast10);
    (*rx23)();
    sk_00359550();
    if ((bool)zr) break;
    (*ax5)();
    sk_00351318();
    sk_00353f88();
    sk_003515d8();
    (*eo8_01)();
  } while (rx21 == 0);
  sk_00352420();
  sk_003509b0();
  (*eo8_02)();
  sk_00351348();
  sk_00353d14(sv00000028);
  return;
}

/* FUN_001d14d4 @ 0x001d14d4   (est. sk_r5_swift_001d14d4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d14d4(void)

{
  sk_001d1a38();
  return;
}

/* FUN_001d14d8 @ 0x001d14d8   (est. sk_r5_swift_001d14d8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d14d8(void)

{
  sk_001d1a38();
  return;
}

/* FUN_001d1504 @ 0x001d1504   (est. sk_r5_swift_001d1504) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1504(void)

{
  sk_001d1370();
  return;
}

/* FUN_001d1508 @ 0x001d1508   (est. sk_r5_swift_001d1508) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1508(void)

{
  sk_001d1370();
  return;
}

/* FUN_001d1534 @ 0x001d1534   (est. sk_r5_swift_001d1534) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1534(void)

{
  sk_001d1564();
  return;
}

/* FUN_001d1538 @ 0x001d1538   (est. sk_r5_swift_001d1538) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1538(void)

{
  sk_001d1564();
  return;
}

/* FUN_001d1564 @ 0x001d1564   (est. sk_r5_swift_001d1564) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1564(void)

{
  undefined8 stk00000008;
  undefined8 t1;
  undefined8 t2;
  undefined8 ax4;
  unsigned long (*ax5)();
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo9)();
  long rx21;
  unsigned long (*rx23)();
  undefined8 sv00000008;
  undefined8 sv00000028;
  
  sk_00353cfc();
  sk_00358600();
  sk_003547d4();
  t1 = sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348dd8();
  sk_00358f0c();
  sk_00377824();
  sk_00348cd0();
  sk_0007c1a4();
  (*g_00658c00)();
  t2 = sk_0034af20();
  sk_00352e24(t2,t1);
  (*eo8_00)();
  sk_000a68c4(ax4);
  t1 = sk_0034d434();
  (*eo9)(t1,ax4);
  sk_0034b278();
  sk_0034f544();
  sk_00377bec();
  sk_00355b74();
  do {
    sk_003508b4((long)&stk00000008 + 6);
    (*rx23)();
    if (sv00000008._7_1_ == '\x01') break;
    (*ax5)();
    sk_00350f7c();
    (*eo8_01)();
  } while (rx21 == 0);
  sk_00351e54();
  sk_003509b0();
  (*eo8_02)();
  sk_00351348();
  sk_00353d14(sv00000028);
  return;
}

/* FUN_001d16c0 @ 0x001d16c0   (est. sk_r5_swift_001d16c0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d16c0(void)

{
  sk_001d16f0();
  return;
}

/* FUN_001d16c4 @ 0x001d16c4   (est. sk_r5_swift_001d16c4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d16c4(void)

{
  sk_001d16f0();
  return;
}

/* FUN_001d16f0 @ 0x001d16f0   (est. sk_r5_swift_001d16f0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d16f0(void)

{
  undefined8 stk00000008;
  undefined8 t1;
  undefined8 t2;
  undefined8 ax4;
  unsigned long (*ax5)();
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo9)();
  long rx21;
  unsigned long (*rx23)();
  undefined8 sv00000008;
  undefined8 sv00000028;
  
  sk_00353cfc();
  sk_00358600();
  sk_003547d4();
  t1 = sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348dd8();
  sk_00358f0c();
  sk_00377824();
  sk_00348cd0();
  sk_0007c1a4();
  (*g_00658c00)();
  t2 = sk_0034af20();
  sk_00352e24(t2,t1);
  (*eo8_00)();
  sk_000a68c4(ax4);
  t1 = sk_0034d434();
  (*eo9)(t1,ax4);
  sk_0034b278();
  sk_0034f544();
  sk_00377bec();
  sk_00355b74();
  do {
    sk_003508b4((long)&stk00000008 + 4);
    (*rx23)();
    if (sv00000008._6_1_ == '\x01') break;
    (*ax5)();
    sk_00350f7c();
    (*eo8_01)();
  } while (rx21 == 0);
  sk_00351e54();
  sk_003509b0();
  (*eo8_02)();
  sk_00351348();
  sk_00353d14(sv00000028);
  return;
}

/* FUN_001d184c @ 0x001d184c   (est. sk_r5_swift_001d184c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d184c(void)

{
  sk_001d187c();
  return;
}

/* FUN_001d1850 @ 0x001d1850   (est. sk_r5_swift_001d1850) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1850(void)

{
  sk_001d187c();
  return;
}

/* FUN_001d187c @ 0x001d187c   (est. sk_r5_swift_001d187c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d187c(void)

{
  undefined8 stk00000008;
  undefined8 t1;
  undefined8 t2;
  undefined8 ax4;
  unsigned long (*ax5)();
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo9)();
  long rx21;
  unsigned long (*rx23)();
  undefined8 sv00000008;
  undefined8 sv00000028;
  
  sk_00353cfc();
  sk_00358600();
  sk_003547d4();
  t1 = sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348dd8();
  sk_00358f0c();
  sk_00377824();
  sk_00348cd0();
  sk_0007c1a4();
  (*g_00658c00)();
  t2 = sk_0034af20();
  sk_00352e24(t2,t1);
  (*eo8_00)();
  sk_000a68c4(ax4);
  t1 = sk_0034d434();
  (*eo9)(t1,ax4);
  sk_0034b278();
  sk_0034f544();
  sk_00377bec();
  sk_00355b74();
  do {
    sk_003508b4(&stk00000008);
    (*rx23)();
    if (sv00000008._4_1_ == '\x01') break;
    (*ax5)();
    sk_00350f7c();
    (*eo8_01)();
  } while (rx21 == 0);
  sk_00351e54();
  sk_003509b0();
  (*eo8_02)();
  sk_00351348();
  sk_00353d14(sv00000028);
  return;
}

/* FUN_001d19d8 @ 0x001d19d8   (est. sk_r5_swift_001d19d8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d19d8(void)

{
  sk_001d1370();
  return;
}

/* FUN_001d19dc @ 0x001d19dc   (est. sk_r5_swift_001d19dc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d19dc(void)

{
  sk_001d1370();
  return;
}

/* FUN_001d1a08 @ 0x001d1a08   (est. sk_r5_swift_001d1a08) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1a08(void)

{
  sk_001d1a38();
  return;
}

/* FUN_001d1a0c @ 0x001d1a0c   (est. sk_r5_swift_001d1a0c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1a0c(void)

{
  sk_001d1a38();
  return;
}

/* FUN_001d1a38 @ 0x001d1a38   (est. sk_r5_swift_001d1a38) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1a38(void)

{
  undefined1 zr;
  undefined8 t1;
  undefined8 t2;
  undefined8 ax4;
  unsigned long (*ax5)();
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo9)();
  long eo16;
  long rx21;
  unsigned long (*rx23)();
  undefined8 sv00000018;
  undefined1 v20 [8];
  undefined8 st18;
  
  sk_00353cfc();
  sk_003547d4();
  sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_003490ec();
  t1 = sk_00349830();
  sk_00377824(t1,ax4);
  sk_00348cd0();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034af20();
  (**(unsigned long (**)() )(eo16 + 0x10))();
  sk_000a68c4(ax4);
  sk_00351184();
  sk_00351160();
  (*eo9)();
  sk_0034b278();
  sk_00351384();
  sk_00377bec();
  sk_00355b74();
  do {
    sk_003508b4(v20);
    (*rx23)();
    sk_00358540();
    t1 = st18;
    if ((bool)zr) break;
    (*ax5)();
    t2 = sk_00351318();
    sk_00352ea8(t2,t1);
    (*eo8_00)();
  } while (rx21 == 0);
  sk_00354660();
  sk_003509b0();
  (*eo8_01)();
  sk_00351348();
  sk_00353d14(sv00000018);
  return;
}

/* FUN_001d1bc0 @ 0x001d1bc0   (est. sk_r5_swift_001d1bc0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1bc0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6)

{
  undefined1 zr;
  undefined8 t1;
  unsigned long (*pc2)();
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo8_03)();
  unsigned long (*eo8_04)();
  unsigned long (*eo9)();
  long eo16;
  long rx21;
  undefined8 rx23;
  sk_c16_t at3;
  sk_c16_t at4;
  undefined8 sv00000018;
  
  at3._0_8_ = (undefined8)(sk_00353cfc());
  at3._8_8_ = 0;
  t1 = sk_0034f860();
  sk_00377824(t1,param_5);
  sk_00348e60();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b0d4();
  sk_003508e4();
  sk_0034d464();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034af20();
  sk_003499f0();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348f50();
  sk_0035050c();
  sk_003518d0();
  sk_00377824();
  sk_00348d64();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034d3c4();
  t1 = sk_00358cd4();
  (*eo8_00)(t1,at3._0_8_,param_3);
  sk_00352680(param_5);
  sk_00359bec();
  sk_00351160();
  (*eo9)();
  sk_0034b278();
  sk_00351384();
  t1 = sk_00377bec();
  pc2 = (unsigned long (*)() )sk_000a68f4();
  do {
    (*pc2)(rx23,t1);
    sk_00352560();
    sk_00350884();
    if ((bool)zr) break;
    sk_00350944(*(undefined8 *)(eo16 + 0x20));
    (*eo8_01)();
    sk_00356af4();
    sk_0031a14c();
    at4._0_8_ = (undefined8)(sk_0034ce68());
    at4._8_8_ = 0;
    (*eo8_02)(at4._0_8_,at4._8_8_,param_6,at3._8_8_);
    sk_00350914(*(undefined8 *)(eo16 + 8));
    (*eo8_03)();
  } while (rx21 == 0);
  sk_0034ed28();
  (*eo8_04)();
  sk_00351348();
  sk_00353d14(sv00000018);
  return;
}

/* FUN_001d1e00 @ 0x001d1e00   (est. sk_r5_swift_001d1e00) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1e00(void)

{
  sk_001d26e0();
  return;
}

/* FUN_001d1e18 @ 0x001d1e18   (est. sk_r5_swift_001d1e18) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1e18(void)

{
  sk_001d2754();
  return;
}

/* FUN_001d1e30 @ 0x001d1e30   (est. sk_r5_swift_001d1e30) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d1e30(void)

{
  uint t1;
  ulong t2;
  undefined8 eo1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  
  sk_0034cf14();
  sk_0031a17c(eo1);
  sk_0034c8b8();
  t2 = (*eo8)();
  if ((t2 & 1) == 0) {
    sk_0031ac9c();
    sk_0034cd18();
    t2 = (*eo8_00)();
    if (rx21 != 0) {
      return t2;
    }
    if ((t2 & 1) == 0) {
      sk_0031accc();
      sk_0034cd18();
      t1 = (*eo8_01)();
      return (ulong)(t1 & 1);
    }
  }
  return 2;
}

/* FUN_001d1ec0 @ 0x001d1ec0   (est. sk_r5_swift_001d1ec0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d1ec0(void)

{
  ulong t1;
  undefined8 eo1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  
  sk_0034cf14();
  sk_0031a17c(eo1);
  sk_0034c8b8();
  t1 = (*eo8)();
  if ((t1 & 1) == 0) {
    sk_0031ac9c();
    sk_0034cd18();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return;
    }
    if ((t1 & 1) == 0) {
      sk_0031acfc();
      sk_0034cd18();
      (*eo8_01)();
      return;
    }
  }
  sk_00019858();
  return;
}

/* FUN_001d1f4c @ 0x001d1f4c   (est. sk_r5_swift_001d1f4c) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d1f4c(void)

{
  ulong t1;
  undefined8 eo1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  
  sk_0034cf14();
  sk_0031a17c(eo1);
  sk_0034c8b8();
  t1 = (*eo8)();
  if ((t1 & 1) == 0) {
    sk_0031ac9c();
    sk_0034cd18();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return t1;
    }
    if ((t1 & 1) == 0) {
      sk_0031ad2c();
      sk_0034cd18();
      t1 = (*eo8_01)();
      return t1;
    }
  }
  t1 = sk_00068e14();
  return t1;
}

/* FUN_001d1fe0 @ 0x001d1fe0   (est. sk_r5_swift_001d1fe0) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d1fe0(void)

{
  ulong t1;
  undefined8 eo1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  uint t2;
  
  sk_0034cf14();
  sk_0031a17c(eo1);
  sk_0034c8b8();
  t1 = (*eo8)();
  if ((t1 & 1) == 0) {
    sk_0031ac9c();
    sk_0034cd18();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return t1;
    }
    if ((t1 & 1) == 0) {
      sk_0031ad5c();
      sk_0034cd18();
      t2 = (*eo8_01)();
      return (ulong)t2;
    }
  }
  return 0x100000000;
}

/* FUN_001d2070 @ 0x001d2070   (est. sk_r5_swift_001d2070) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2070(undefined8 param_1,undefined8 param_2)

{
  sk_001d2448(param_1,param_2,&L_0031ad8c,0x66d5);
  return;
}

/* FUN_001d2074 @ 0x001d2074   (est. sk_r5_swift_001d2074) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2074(undefined8 param_1,undefined8 param_2)

{
  sk_001d2448(param_1,param_2,&L_0031ad8c,0x66d5);
  return;
}

/* FUN_001d20a0 @ 0x001d20a0   (est. sk_r5_swift_001d20a0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d20a0(undefined8 param_1,undefined8 param_2)

{
  sk_001d21f0(param_1,param_2,&L_0031adbc,0x46be);
  return;
}

/* FUN_001d20a4 @ 0x001d20a4   (est. sk_r5_swift_001d20a4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d20a4(undefined8 param_1,undefined8 param_2)

{
  sk_001d21f0(param_1,param_2,&L_0031adbc,0x46be);
  return;
}

/* FUN_001d20d0 @ 0x001d20d0   (est. sk_r5_swift_001d20d0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d20d0(undefined8 param_1,undefined8 param_2)

{
  sk_001d22b8(param_1,param_2,&L_0031adec,0x630c);
  return;
}

/* FUN_001d20d4 @ 0x001d20d4   (est. sk_r5_swift_001d20d4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d20d4(undefined8 param_1,undefined8 param_2)

{
  sk_001d22b8(param_1,param_2,&L_0031adec,0x630c);
  return;
}

/* FUN_001d2100 @ 0x001d2100   (est. sk_r5_swift_001d2100) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2100(undefined8 param_1,undefined8 param_2)

{
  sk_001d2380(param_1,param_2,&L_0031ae1c,0xf7d5);
  return;
}

/* FUN_001d2104 @ 0x001d2104   (est. sk_r5_swift_001d2104) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2104(undefined8 param_1,undefined8 param_2)

{
  sk_001d2380(param_1,param_2,&L_0031ae1c,0xf7d5);
  return;
}

/* FUN_001d2130 @ 0x001d2130   (est. sk_r5_swift_001d2130) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2130(undefined8 param_1,undefined8 param_2)

{
  sk_001d2448(param_1,param_2,sk_0031ae4c,0xed02);
  return;
}

/* FUN_001d2134 @ 0x001d2134   (est. sk_r5_swift_001d2134) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2134(undefined8 param_1,undefined8 param_2)

{
  sk_001d2448(param_1,param_2,sk_0031ae4c,0xed02);
  return;
}

/* FUN_001d2160 @ 0x001d2160   (est. sk_r5_swift_001d2160) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2160(undefined8 param_1,undefined8 param_2)

{
  sk_001d2504(param_1,param_2,&L_0031ae7c,0x9678);
  return;
}

/* FUN_001d2164 @ 0x001d2164   (est. sk_r5_swift_001d2164) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2164(undefined8 param_1,undefined8 param_2)

{
  sk_001d2504(param_1,param_2,&L_0031ae7c,0x9678);
  return;
}

/* FUN_001d2190 @ 0x001d2190   (est. sk_r5_swift_001d2190) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2190(undefined8 param_1,undefined8 param_2)

{
  sk_001d2448(param_1,param_2,&L_0031aeac,0x5a17);
  return;
}

/* FUN_001d2194 @ 0x001d2194   (est. sk_r5_swift_001d2194) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2194(undefined8 param_1,undefined8 param_2)

{
  sk_001d2448(param_1,param_2,&L_0031aeac,0x5a17);
  return;
}

/* FUN_001d21c0 @ 0x001d21c0   (est. sk_r5_swift_001d21c0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d21c0(undefined8 param_1,undefined8 param_2)

{
  sk_001d21f0(param_1,param_2,&L_0031aedc,0xae16);
  return;
}

/* FUN_001d21c4 @ 0x001d21c4   (est. sk_r5_swift_001d21c4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d21c4(undefined8 param_1,undefined8 param_2)

{
  sk_001d21f0(param_1,param_2,&L_0031aedc,0xae16);
  return;
}

/* FUN_001d21f0 @ 0x001d21f0   (est. sk_r5_sched_op_001d21f0) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d21f0(void)

{
  uint t1;
  ulong t2;
  int iv3;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034be1c();
  t2 = (*eo8)();
  if ((t2 & 1) == 0) {
    sk_0031ac9c();
    sk_0034bcdc();
    t2 = (*eo8_00)();
    if (rx21 != 0) {
      return t2;
    }
    if ((t2 & 1) == 0) {
      (*rx25)();
      sk_0034bcdc();
      t1 = (*eo8_01)();
      iv3 = 0;
      goto L_001d2220;
    }
  }
  t1 = 0;
  iv3 = 1;
L_001d2220:
  return (ulong)(t1 & 0xff | iv3 << 8);
}

/* FUN_001d2288 @ 0x001d2288   (est. sk_r5_swift_001d2288) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2288(undefined8 param_1,undefined8 param_2)

{
  sk_001d22b8(param_1,param_2,&L_0031af0c,0x32e1);
  return;
}

/* FUN_001d228c @ 0x001d228c   (est. sk_r5_swift_001d228c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d228c(undefined8 param_1,undefined8 param_2)

{
  sk_001d22b8(param_1,param_2,&L_0031af0c,0x32e1);
  return;
}

/* FUN_001d22b8 @ 0x001d22b8   (est. sk_r5_sched_op_001d22b8) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d22b8(void)

{
  uint t1;
  ulong t2;
  uint t3;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034be1c();
  t2 = (*eo8)();
  if ((t2 & 1) == 0) {
    sk_0031ac9c();
    sk_0034bcdc();
    t2 = (*eo8_00)();
    if (rx21 != 0) {
      return t2;
    }
    if ((t2 & 1) == 0) {
      (*rx25)();
      sk_0034bcdc();
      t1 = (*eo8_01)();
      t3 = 0;
      goto L_001d22e8;
    }
  }
  t1 = 0;
  t3 = 0x10000;
L_001d22e8:
  return (ulong)(t3 | t1 & 0xffff);
}

/* FUN_001d2350 @ 0x001d2350   (est. sk_r5_swift_001d2350) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2350(undefined8 param_1,undefined8 param_2)

{
  sk_001d2380(param_1,param_2,&L_0031af3c,0x700);
  return;
}

/* FUN_001d2354 @ 0x001d2354   (est. sk_r5_swift_001d2354) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2354(undefined8 param_1,undefined8 param_2)

{
  sk_001d2380(param_1,param_2,&L_0031af3c,0x700);
  return;
}

/* FUN_001d2380 @ 0x001d2380   (est. sk_r5_sched_op_001d2380) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001d2380(void)

{
  ulong t1;
  unsigned long (*eo8)();
  ulong t2;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034be1c();
  t1 = (*eo8)();
  if ((t1 & 1) == 0) {
    sk_0031ac9c();
    sk_0034bcdc();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return t1;
    }
    if ((t1 & 1) == 0) {
      (*rx25)();
      sk_0034bcdc();
      t1 = (*eo8_01)();
      t2 = 0;
      goto L_001d23b0;
    }
  }
  t1 = 0;
  t2 = 0x100000000;
L_001d23b0:
  return t2 | t1 & 0xffffffff;
}

/* FUN_001d2418 @ 0x001d2418   (est. sk_r5_swift_001d2418) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2418(undefined8 param_1,undefined8 param_2)

{
  sk_001d2448(param_1,param_2,sk_0031af6c,0xf20);
  return;
}

/* FUN_001d241c @ 0x001d241c   (est. sk_r5_swift_001d241c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d241c(undefined8 param_1,undefined8 param_2)

{
  sk_001d2448(param_1,param_2,sk_0031af6c,0xf20);
  return;
}

/* FUN_001d2448 @ 0x001d2448   (est. sk_r5_sched_op_001d2448) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2448(void)

{
  ulong t1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034be1c();
  t1 = (*eo8)();
  if ((t1 & 1) == 0) {
    sk_0031ac9c();
    sk_0034bcdc();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return;
    }
    if ((t1 & 1) == 0) {
      (*rx25)();
      sk_0034bcdc();
      (*eo8_01)();
      return;
    }
  }
  sk_00068e14();
  return;
}

/* FUN_001d24d4 @ 0x001d24d4   (est. sk_r5_swift_001d24d4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d24d4(undefined8 param_1,undefined8 param_2)

{
  sk_001d2504(param_1,param_2,&L_0031af9c,0x70c4);
  return;
}

/* FUN_001d24d8 @ 0x001d24d8   (est. sk_r5_swift_001d24d8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d24d8(undefined8 param_1,undefined8 param_2)

{
  sk_001d2504(param_1,param_2,&L_0031af9c,0x70c4);
  return;
}

/* FUN_001d2504 @ 0x001d2504   (est. sk_r5_sched_op_001d2504) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2504(void)

{
  ulong t1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long rx21;
  unsigned long (*rx25)();
  
  sk_0034be1c();
  t1 = (*eo8)();
  if ((t1 & 1) == 0) {
    sk_0031ac9c();
    sk_0034bcdc();
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return;
    }
    if ((t1 & 1) == 0) {
      (*rx25)();
      sk_0034bcdc();
      (*eo8_01)();
      return;
    }
  }
  sk_003509f8(0);
  return;
}

/* FUN_001d2594 @ 0x001d2594   (est. sk_r5_swift_001d2594) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2594(void)

{
  ulong t1;
  undefined8 t2;
  undefined8 ax3;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo9)();
  long rx21;
  
  sk_00354db8();
  sk_0031a17c();
  sk_0034bddc();
  t1 = (*eo8)();
  if ((t1 & 1) == 0) {
    t2 = sk_0031ac9c(ax3);
    sk_00350618(t2);
    t1 = (*eo8_00)();
    if (rx21 != 0) {
      return;
    }
    if ((t1 & 1) == 0) {
      sk_0031a1ac(ax3);
      sk_00350390();
      sk_00351438();
      sk_00356b80();
      (*eo9)();
      sk_00354d5c();
      goto L_001d25dc;
    }
  }
  sk_0035172c();
L_001d25dc:
  sk_00352480();
  sk_000839d8();
  return;
}

/* FUN_001d2658 @ 0x001d2658   (est. sk_r5_swift_001d2658) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2658(void)

{
  unsigned long (*eo8)();
  
  sk_00352914();
  sk_00348730();
  sk_003517c0();
  sk_0034be70();
  (*eo8)();
  sk_0034f0c0();
  return;
}

/* FUN_001d269c @ 0x001d269c   (est. sk_r5_swift_001d269c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d269c(void)

{
  unsigned long (*eo8)();
  
  sk_00352914();
  sk_00348730();
  sk_003517c0();
  sk_0034be70();
  (*eo8)();
  sk_0034f088();
  return;
}

/* FUN_001d26e0 @ 0x001d26e0   (est. sk_r5_swift_001d26e0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d26e0(void)

{
  long n1;
  unsigned long (*eo8)();
  undefined8 rx23;
  undefined8 rx24;
  long *rx26;
  
  sk_0034c59c();
  sk_00349b88();
  sk_003534e0();
  n1 = sk_0034f7ec(0x676ed0);
  *rx26 = n1;
  *(undefined8 *)(n1 + 0x10) = rx24;
  *(undefined8 *)(n1 + 0x18) = rx23;
  sk_0034be70();
  (*eo8)();
  sk_00352f18(Division_results_in_an_overflow_i_005ceb20_str + 0x20);
  return;
}

/* FUN_001d2754 @ 0x001d2754   (est. sk_r5_swift_001d2754) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2754(void)

{
  long n1;
  unsigned long (*eo8)();
  undefined8 rx23;
  undefined8 rx24;
  long *rx26;
  
  sk_0034c59c();
  sk_00349b88();
  sk_003534e0();
  n1 = sk_0034f7ec(0x6773c0);
  *rx26 = n1;
  *(undefined8 *)(n1 + 0x10) = rx24;
  *(undefined8 *)(n1 + 0x18) = rx23;
  sk_0034be70();
  (*eo8)();
  sk_00352f18(Encoder_has_not_implemented_supp_005ceb60_str + 0x10);
  return;
}

/* FUN_001d27c8 @ 0x001d27c8   (est. sk_r5_swift_001d27c8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d27c8(void)

{
  long n1;
  unsigned long (*eo8)();
  undefined8 rx23;
  undefined8 rx24;
  long *rx26;
  
  sk_0034c59c();
  sk_00349b88();
  sk_003534e0();
  n1 = sk_0034f7ec(0x676ed0);
  *rx26 = n1;
  *(undefined8 *)(n1 + 0x10) = rx24;
  *(undefined8 *)(n1 + 0x18) = rx23;
  sk_0034be70();
  (*eo8)();
  sk_00352f18(Division_results_in_an_overflow_i_005ceb20_str + 0x20);
  return;
}

/* FUN_001d283c @ 0x001d283c   (est. sk_r5_swift_001d283c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d283c(void)

{
  long n1;
  unsigned long (*eo8)();
  undefined8 rx23;
  undefined8 rx24;
  long *rx26;
  
  sk_0034c59c();
  sk_00349b88();
  sk_003534e0();
  n1 = sk_0034f7ec(0x6773c0);
  *rx26 = n1;
  *(undefined8 *)(n1 + 0x10) = rx24;
  *(undefined8 *)(n1 + 0x18) = rx23;
  sk_0034be70();
  (*eo8)();
  sk_00352f18(Encoder_has_not_implemented_supp_005ceb60_str + 0x10);
  return;
}

/* FUN_001d28b0 @ 0x001d28b0   (est. sk_r5_swift_001d28b0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d28b0(void)

{
  unsigned long (*eo8)();
  
  sk_0035a2c4();
  sk_00348730();
  sk_003517c0();
  sk_0034be70();
  (*eo8)();
  sk_0034f0c0();
  return;
}

/* FUN_001d28f4 @ 0x001d28f4   (est. sk_r5_swift_001d28f4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d28f4(void)

{
  unsigned long (*eo8)();
  
  sk_0035a2c4();
  sk_00348730();
  sk_003517c0();
  sk_0034be70();
  (*eo8)();
  sk_0034f088();
  return;
}

/* FUN_001d2954 @ 0x001d2954   (est. sk_r5_swift_001d2954) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2954(void)

{
  int iv1;
  undefined8 t2;
  long n3;
  long eo8;
  long eo16;
  long eo16_00;
  
  t2 = sk_0034b85c();
  sk_0034b07c(t2,t2);
  (**(unsigned long (**)() )(eo16 + 0x20))(eo8);
  sk_0034e70c();
  n3 = sk_0031090c();
  iv1 = *(int *)(n3 + 0x24);
  sk_00349748();
  sk_00350968();
  sk_00377824();
  sk_0034ad10();
                                          (**(unsigned long (**)() )(eo16_00 + 0x20))(eo8 + iv1);
  return;
}

/* FUN_001d2c60 @ 0x001d2c60   (est. sk_r5_swift_001d2c60) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2c60(void)

{
  unsigned long (*eo8)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  undefined8 rx30;
  
  sk_00084220();
  sk_000867ec();
  sk_00349748();
  sk_00354394();
  sk_00377824();
  sk_00348d64();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b05c();
  sk_003547ec();
  sk_0034ee48();
  (*eo9)();
  sk_00319658();
  sk_00351250();
  sk_003504a0();
  (*eo9_00)();
  sk_0034ded4();
  (*eo8)();
  sk_00084234(rx30);
  return;
}

/* FUN_001d2d1c @ 0x001d2d1c   (est. sk_r5_fatal_assert_001d2d1c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2d1c(long param_1,long param_2,long param_3)

{
  if (param_1 < param_2 || param_3 <= param_1) {
    sk_00348384(1);
                        sk_001afe4c();
  }
  return;
}

/* FUN_001d2d5c @ 0x001d2d5c   (est. sk_r5_fatal_assert_001d2d5c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2d5c(void)

{
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Index_out_of_bounds_005cdab0_str,0x13,2,
               Swift_Collection_swift_005cdad0_str,0x16,2,0x2ca,1);
}

/* FUN_001d2dcc @ 0x001d2dcc   (est. sk_r5_fatal_assert_001d2dcc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2dcc(void)

{
  sk_00348384(1);
                      sk_001afe4c();
}

/* FUN_001d2df0 @ 0x001d2df0   (est. sk_r5_fatal_assert_001d2df0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2df0(void)

{
  undefined8 t1;
  ulong t2;
  undefined8 ax3;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  undefined8 rx30;
  
  sk_00357ca0();
  sk_00353274();
  sk_00351a38();
  t1 = sk_0034b164();
  sk_00377824(t1,ax3);
  sk_000e15d8();
  sk_00352a4c();
  t1 = sk_00377bec();
  sk_00310e20();
  sk_0034bcf0();
  sk_00351100();
  t2 = (*eo8)();
  if ((t2 & 1) != 0) {
    sk_0034e0d4();
    sk_00310e08();
    sk_0035044c(t1);
    sk_00351100();
    t2 = (*eo8_00)();
    if ((t2 & 1) != 0) {
      sk_00357c44(rx30);
      return;
    }
  }
  sk_00348384(1);
                      sk_001afe4c();
}

/* FUN_001d2eb4 @ 0x001d2eb4   (est. sk_r5_fatal_assert_001d2eb4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2eb4(void)

{
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_out_of_bounds_005cec20_str,0x13,2,
               Swift_Collection_swift_005cdad0_str,0x16,2,0x2da,1);
}

/* FUN_001d2f1c @ 0x001d2f1c   (est. sk_r5_fatal_assert_001d2f1c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2f1c(void)

{
  sk_003488bc(1);
  sk_0034893c();
                      sk_001afe4c();
}

/* FUN_001d2f4c @ 0x001d2f4c   (est. sk_r5_fatal_assert_001d2f4c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2f4c(ulong param_1,ulong param_2,ulong param_3,ulong param_4)

{
  if ((param_3 >> 0xe <= param_1 >> 0xe) && (param_2 >> 0xe <= param_4 >> 0xe)) {
    return;
  }
  sk_003488bc(1);
  sk_0034893c();
                      sk_001afe4c();
}

/* FUN_001d2f94 @ 0x001d2f94   (est. sk_r5_fatal_assert_001d2f94) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d2f94(void)

{
  undefined8 t1;
  unsigned long (*pc2)();
  ulong t3;
  undefined8 ax3;
  long eo8;
  long rx19;
  long rx21;
  undefined8 rx30;
  
  sk_00357ca0();
  sk_00353274();
  sk_0008409c();
  t1 = sk_0034b164();
  sk_00377824(t1,ax3);
  sk_000e15d8();
  sk_00352a4c();
  sk_00377bec();
  pc2 = (unsigned long (*)() )sk_00310e20();
  sk_0034bf1c();
  t3 = (*pc2)();
  if ((t3 & 1) != 0) {
    sk_0034e0d4();
    sk_00355d78();
    sk_00351100(rx21 + eo8,rx19 + eo8);
    t3 = (*pc2)();
    if ((t3 & 1) != 0) {
      sk_00357c44(rx30);
      return;
    }
  }
  sk_003488bc(1);
  sk_0034893c();
                      sk_001afe4c();
}

/* FUN_001d30f8 @ 0x001d30f8   (est. sk_r5_swift_001d30f8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d30f8(void)

{
  unsigned long (*eo8)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  undefined8 rx30;
  
  sk_00084220();
  sk_00349a18();
  sk_00349748();
  sk_00377824();
  sk_00348d4c();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034a2c0();
  sk_003513b4();
  (*eo9)();
  sk_0031afcc();
  sk_0035133c();
  sk_0034b358();
  (*eo9_00)();
  sk_0034c9f8();
  (*eo8)();
  sk_00084234(rx30);
  return;
}

/* FUN_001d31b0 @ 0x001d31b0   (est. sk_r5_swift_001d31b0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d31b0(void)

{
  int iv1;
  undefined8 t2;
  undefined8 ax4;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long eo16;
  long eo16_00;
  unsigned long (*pc3)();
  undefined8 sv00000048;
  
  sk_0008e518();
  sk_00357a34();
  sk_0034a944();
  sk_0035136c();
  sk_00377824();
  sk_0034ee68();
  sk_00310d68();
  sk_00348d4c();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034cff4();
  sk_003499f0();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034af20();
  sk_003192d8(ax4);
  sk_00351f7c();
  sk_00355d28();
  (*eo9)();
  sk_00356224();
  sk_003504ac();
  (*eo9_00)();
  sk_003524b0();
  iv1 = sk_0035681c();
  if (iv1 == 1) {
    sk_00350c2c(*(undefined8 *)(eo16 + 8));
    (*eo8)();
    sk_00355d28(*(undefined8 *)(eo16_00 + 0x10));
    (*eo8_00)();
  }
  else {
    pc3 = *(unsigned long (**)() )(eo16_00 + 0x20);
    sk_0034df24();
    (*pc3)();
    sk_00351324();
    (*pc3)();
  }
  t2 = sk_00357fd4();
  sk_0008e500(t2,sv00000048);
  return;
}

/* FUN_001d332c @ 0x001d332c   (est. sk_r5_fatal_assert_001d332c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d332c(void)

{
  undefined8 t1;
  ulong t2;
  unsigned long (*pc3)();
  unsigned long (*pc4)();
  undefined8 ax3;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo9)();
  long n5;
  long n6;
  undefined8 rx30;
  
  sk_0008e518();
  sk_003534d4();
  sk_0034c54c();
  sk_003516cc();
  sk_00377824();
  sk_00348d4c();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034aee4();
  sk_00351220(ax3);
  t1 = sk_00377bec();
  sk_0035166c();
  sk_003508b4();
  sk_003512cc();
  t2 = (*eo8)();
  if ((t2 & 1) == 0) {
    sk_00350410();
    sk_003488bc();
    sk_00349a2c();
    sk_0035110c();
                        sk_001afe4c();
  }
  sk_00350a04();
  (*eo9)();
  sk_00351ef8(t1);
  pc3 = (unsigned long (*)() )sk_0014ae44();
  sk_0035084c();
  sk_003512cc();
  t2 = (*pc3)();
  if ((t2 & 1) == 0) {
    pc4 = (unsigned long (*)() )sk_00027818(ax3);
    n5 = 0;
    do {
      n6 = n5 + 1;
      if (ovf(n5,1)) {
                            pc3 = (unsigned long (*)() )sk_breakpoint(1,0x1d34ac);
        (*pc3)();
      }
      (*pc4)();
      sk_003507d4();
      sk_003512cc();
      t2 = (*pc3)();
      n5 = n5 + 1;
    } while ((t2 & 1) == 0);
  }
  else {
    n6 = 0;
  }
  sk_00351e54();
  sk_00100c38();
  (*eo8_00)();
  sk_0008e500(n6,rx30);
  return;
}

/* FUN_001d36d8 @ 0x001d36d8   (est. sk_r5_fatal_assert_001d36d8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d36d8(void)

{
  sk_00347d60();
                      sk_001afe4c();
}

/* FUN_001d36e8 @ 0x001d36e8   (est. sk_r5_fatal_assert_001d36e8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d36e8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5)

{
  undefined8 t1;
  ulong t2;
  undefined8 t3;
  long eo8;
  long eo8_00;
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo8_03)();
  unsigned long (*eo9)();
  long eo16;
  long eo16_00;
  undefined8 rx21;
  unsigned long (*rx24)();
  unsigned long (*pc4)();
  undefined8 rx30;
  undefined8 st28;
  
  sk_0008e518();
  sk_003530e8();
  sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_003490ec();
  sk_00351bec(param_5);
  t1 = sk_0008f6c0();
  sk_00377824(0,t1,param_3,sk_00610504,&g_0061052c);
  sk_00348e60();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_00348a9c();
  (*g_00658c00)();
  sk_00350434();
  sk_003503f8();
  (*g_00658c00)();
  sk_0034ac00();
  (*g_00658c00)();
  sk_0034ba68();
  sk_00358ddc();
  sk_00310ad4();
  sk_00027754();
  sk_0034fce4();
  sk_00310e08();
  t2 = sk_001e3048();
  if ((t2 & 1) == 0) {
    sk_00310ad4();
    sk_00027754();
    sk_0034fce4();
    sk_00310e08();
    t1 = sk_003195c8(param_5);
    sk_0034d7cc(t1);
    (*eo8_01)();
    sk_0034f754();
    sk_00350b9c();
    sk_00377bec();
    sk_00358d34();
    sk_0034d364();
    sk_00352270();
    (*rx24)();
    sk_0034d7cc(*(undefined8 *)(eo16 + 0x10));
    (*eo8_02)();
    sk_00354d94();
    sk_0034f5a4();
    (*rx24)();
    sk_00357d54();
    sk_003509d4();
    t1 = sk_00377bec();
    t3 = sk_00353390(st28);
    sk_0023b7b8(t3,param_4);
    pc4 = *(unsigned long (**)() )(eo16_00 + 8);
    sk_00350914();
    (*pc4)();
    t1 = sk_00310f34(t1);
    sk_00350944(t1);
    sk_00351b2c();
    (*eo8_03)();
    sk_00350ab8();
    (*pc4)();
    sk_00350b78();
    (*pc4)();
    sk_0034e1d0();
    sk_00350048(rx21);
    sk_0034c3d4();
    (*eo9)();
    sk_0008e500(rx30);
    return;
  }
  sk_00350410();
  sk_003488bc();
  sk_00349a54();
  sk_003523f0();
                      sk_001afe4c();
}

/* FUN_001d39cc @ 0x001d39cc   (est. sk_r5_fatal_assert_001d39cc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d39cc(uint param_1,uint param_2)

{
  if (param_1 <= param_2) {
    return;
  }
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_out_of_bounds_005cec20_str,0x13,2,
               Swift_Collection_swift_005cdad0_str,0x16,2,0x2da,1);
}

/* FUN_001d3a30 @ 0x001d3a30   (est. sk_r5_fatal_assert_001d3a30) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d3a30(long param_1,long param_2)

{
  if ((-1 < param_1) && (param_2 < 3)) {
    return;
  }
  sk_003488bc(1);
  sk_0034893c();
                      sk_001afe4c();
}

/* FUN_001d3a94 @ 0x001d3a94   (est. sk_r5_fatal_assert_001d3a94) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d3a94(void)

{
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_out_of_bounds_005cec20_str,0x13,2,
               Swift_Collection_swift_005cdad0_str,0x16,2,0x2da,1);
}

/* FUN_001d3b40 @ 0x001d3b40   (est. sk_r5_fatal_assert_001d3b40) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d3b40(void)

{
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_out_of_bounds_005cec20_str,0x13,2,
               Swift_Collection_swift_005cdad0_str,0x16,2,0x2da,1);
}

/* FUN_001d3b98 @ 0x001d3b98   (est. sk_r5_fatal_assert_001d3b98) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d3b98(long param_1,long param_2)

{
  if ((-1 < param_1) && (param_2 < 3)) {
    return;
  }
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_out_of_bounds_005cec20_str,0x13,2,
               Swift_Collection_swift_005cdad0_str,0x16,2,0x2da,1);
}

/* FUN_001d3c10 @ 0x001d3c10   (est. sk_r5_fatal_assert_001d3c10) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d3c10(void)

{
  sk_003488bc(1);
  sk_0034893c();
                      sk_001afe4c();
}

/* FUN_001d3fc0 @ 0x001d3fc0   (est. sk_r5_fatal_assert_001d3fc0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d3fc0(void)

{
  sk_00347d60();
                      sk_001afe4c();
}

/* FUN_001d3fd0 @ 0x001d3fd0   (est. sk_r5_swift_001d3fd0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d3fd0(void)

{
  undefined8 t1;
  long n2;
  unsigned long (*jumptable)();
  long eo8;
  long eo8_00;
  long eo8_01;
  long eo16;
  long eo16_00;
  long rx19;
  undefined8 rx30;
  
  sk_00354744();
  t1 = sk_0035215c();
  sk_0034d024();
  n2 = sk_0031b080();
  sk_00354010((long)*(int *)(n2 + 0x28));
  (**(unsigned long (**)() )(eo16 + 0x20))(eo8 + eo8_00,t1);
  sk_0034d2a4();
  sk_0034ac8c();
  t1 = sk_00377824();
  sk_0034ab20();
  jumptable = *(unsigned long (**)() )(eo16_00 + 0x20);
  (*jumptable)(eo8);
  sk_000e15d8();
  sk_003516d8();
  sk_00377bec();
  sk_0034e414();
  sk_00355d78();
  sk_003544c8(eo8 + *(int *)(n2 + 0x24),rx19 + eo8_01,t1,
               jumptable,(undefined8 *)(eo16_00 + 0x20),rx30);
                                          (*jumptable)();
  return;
}

/* FUN_001d4514 @ 0x001d4514   (est. sk_r5_fatal_assert_001d4514) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d4514(void)

{
  sk_00347d60();
                      sk_001afe4c();
}

/* FUN_001d4544 @ 0x001d4544   (est. sk_r5_swift_001d4544) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d4544(void)

{
  sk_00281a54();
  return;
}

/* FUN_001d4548 @ 0x001d4548   (est. sk_r5_swift_001d4548) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d4548(void)

{
  sk_00281a54();
  return;
}

/* FUN_001d4584 @ 0x001d4584   (est. sk_r5_fatal_assert_001d4584) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d4584(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iv1;
  undefined1 t2;
  undefined8 t3;
  undefined8 t4;
  long n5;
  unsigned long (*pc6)();
  ulong t7;
  undefined8 eo8;
  long eo8_00;
  long eo8_01;
  long eo8_02;
  unsigned long (*eo8_03)();
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  unsigned long (*eo8_06)();
  unsigned long (*eo8_07)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  unsigned long (*eo9_01)();
  unsigned long (*eo9_02)();
  unsigned long (*eo9_03)();
  unsigned long (*eo9_04)();
  unsigned long (*eo9_05)();
  undefined8 eo13;
  long eo16;
  long eo16_00;
  long eo16_01;
  long eo16_02;
  long rx19;
  undefined8 rx20;
  unsigned long (*pc8)();
  undefined8 rx21;
  long rx25;
  long rx28;
  undefined8 rx30;
  sk_c16_t at9;
  undefined8 v78;
  undefined8 v70;
  undefined8 st58;
  
  sk_0008e518();
  t4 = param_3;
  sk_00359030();
  t3 = sk_0034a3c4();
  sk_0035063c(t3,t4);
  sk_00377824();
  sk_00348bf8();
  sk_003722e4();
  sk_00348fd8();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_003493c4();
  sk_0034cf34();
  (*g_00658c00)();
  sk_0034ffdc();
  sk_003554d4();
  sk_0034dbb8();
  sk_00377bec();
  sk_0034da98();
  sk_00310e08();
  sk_00348e18();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b250();
  sk_0035050c();
  t4 = sk_00310d68();
  sk_000a6f88();
  (*g_00658c00)(*(undefined8 *)(eo8_01 + 0x40));
  sk_0034ab10();
  sk_00352008();
  (*g_00658c00)();
  sk_0034c074();
  sk_003499c8();
  (*g_00658c00)(*(undefined8 *)(eo8_02 + 0x40));
  sk_00348a9c();
  (*g_00658c00)();
  sk_0034a464();
  (*g_00658c00)();
  sk_0034b308();
  (*g_00658c00)();
  sk_0034c2b4();
  if (rx25 < 0) {
    sk_00350410();
    sk_003488bc();
    sk_00349a2c();
    sk_0035110c();
  }
  else {
    sk_00353efc(param_3);
    n5 = (*eo8_03)(rx21,param_3);
    t2 = n5 - rx25 == 0;
    if (ovf(n5,rx25)) {
                          pc6 = (unsigned long (*)() )sk_breakpoint(1,0x1d4a20);
      (*pc6)();
    }
    sk_0034f1e0(n5 - rx25);
    sk_000b4390();
    (*eo9)();
    pc6 = (unsigned long (*)() )sk_00310924(param_3);
    sk_000b4390();
    (*pc6)();
    sk_003192d8(param_3);
    sk_0035133c();
    sk_003508cc();
    sk_003515c0();
    (*eo9_00)();
    pc6 = *(unsigned long (**)() )(eo16_01 + 8);
    sk_00100c38();
    (*pc6)();
    sk_00350a34();
    (*pc6)();
    at9._0_8_ = (undefined8)(sk_0008e388());
    at9._8_8_ = 0;
    (*eo9_01)(at9._0_8_,at9._8_8_,t4);
    sk_0034c4bc(eo13);
    if ((bool)t2) {
      sk_0035798c();
      (*eo9_02)(rx21,param_3);
      sk_00351130(*(undefined8 *)(eo16_00 + 8));
      (*eo8_04)();
    }
    else {
      sk_0035792c();
      sk_003504f4();
      (*eo9_03)();
    }
    sk_00355bd0();
    (*eo9)(rx21,param_3);
    sk_00356b20();
    sk_00310e20();
    sk_0034b8cc();
    sk_0034e5fc();
    t7 = (*eo8_05)();
    if ((t7 & 1) != 0) {
      pc8 = *(unsigned long (**)() )(eo16_01 + 0x20);
      sk_0034d868();
      (*pc8)();
      sk_00351300(v70 + *(int *)(rx28 + 0x30));
      (*pc8)();
      sk_00351e84();
      at9._0_8_ = (undefined8)(sk_003508b4());
      at9._8_8_ = 0;
      (*eo9_04)(at9._0_8_,at9._8_8_,rx28);
      iv1 = *(int *)(rx28 + 0x30);
      sk_00350b6c();
      (*pc8)();
      (*pc6)(st58 + iv1);
      at9._0_8_ = (undefined8)(sk_003508b4(*(undefined8 *)(eo16 + 0x20)));
      at9._8_8_ = 0;
      (*eo8_06)(at9._0_8_,at9._8_8_,rx28);
      sk_00355e5c((long)*(int *)(rx28 + 0x30),v78 + *(int *)(rx19 + 0x24));
      (*pc8)();
      sk_00350a34();
      (*pc6)();
      sk_00351bb8();
      sk_00351190(eo8,v78);
      (*eo9_05)();
      sk_0034b3e8();
      (**(unsigned long (**)() )(eo16_02 + 8))(rx20,rx21);
      sk_00354d38();
      sk_003504f4();
      (*eo8_07)();
      sk_0008e500(rx30);
      return;
    }
    sk_00347d60();
  }
                      sk_001afe4c();
}

/* FUN_001d4f3c @ 0x001d4f3c   (est. sk_r5_fatal_assert_001d4f3c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d4f3c(void)

{
  sk_00347d60();
                      sk_001afe4c();
}

/* FUN_001d4f4c @ 0x001d4f4c   (est. sk_r5_fatal_assert_001d4f4c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d4f4c(void)

{
  undefined8 stk00000018;
  undefined8 stk00000020;
  undefined8 stk00000028;
  undefined8 stk00000038;
  int iv1;
  undefined8 t2;
  ulong t3;
  unsigned long (*pc4)();
  long eo8;
  long eo8_00;
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo8_03)();
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  unsigned long (*eo8_06)();
  unsigned long (*eo8_07)();
  unsigned long (*eo8_08)();
  unsigned long (*eo8_09)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  unsigned long (*eo9_01)();
  unsigned long (*eo9_02)();
  unsigned long (*eo9_03)();
  unsigned long (*eo9_04)();
  long eo16;
  long eo16_00;
  undefined8 rx22;
  undefined8 rx23;
  undefined8 rx24;
  undefined8 t5;
  undefined8 rx26;
  undefined8 rx27;
  long sv00000008;
  long vf0;
  long vd0;
  long vc8;
  undefined8 vb0;
  long va8;
  undefined8 v98;
  long v90;
  undefined8 v78;
  unsigned long (*v68)();
  unsigned long (*v50)();
  undefined8 v38;
  
  sk_00353cfc();
  sk_003588d0();
  sk_00352554();
  sk_0034de64();
  sk_00353160();
  sk_00377824();
  sk_00348bf8();
  sk_003722e4();
  sk_003490b8(&stk00000038);
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_003493c4();
  sk_0034acf0();
  (*g_00658c00)();
  sk_00350464();
  sk_003509a4();
  sk_0034fde0();
  t2 = sk_00377bec();
  sk_0034c454();
  sk_00310e08();
  sk_003490b8(&stk00000028);
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034eb40();
  sk_00027754();
  sk_00348e30();
  sk_00377824();
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b250();
  sk_003499c8();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_0034926c();
  (*g_00658c00)();
  sk_0034aac4();
  (*g_00658c00)();
  sk_0034a414();
  (*g_00658c00)();
  sk_0034b87c();
  sk_000277b8();
  sk_00350b24();
  sk_00350c80();
  sk_00352f88();
  (*eo9)();
  sk_00310924();
  sk_00027754(t2);
  sk_0014ae44();
  sk_003565e0();
  do {
    t5 = rx24;
    sk_00350c80(v38);
    (*eo9_00)();
    sk_0035060c();
    sk_003512cc();
    t3 = (*v50)();
    sk_00354bbc();
    sk_003584c0();
    (*eo8_01)();
    if ((t3 & 1) != 0) {
      sk_0035964c();
L_001d5260:
      sk_00350470(vb0);
      sk_00355418();
      (*eo9_01)();
      sk_00351990();
      sk_000dbd0c();
      (*eo9_02)();
      t2 = sk_00310e20(t2);
      sk_00350a34(t2);
      sk_003518a0();
      t3 = (*eo8_06)();
      if ((t3 & 1) == 0) {
        sk_00347d60();
                            sk_001afe4c();
      }
      sk_00350738();
      (*eo8_01)();
      pc4 = *(unsigned long (**)() )(v90 + 0x20);
      sk_003518b8();
      (*pc4)();
      sk_00351dfc(vf0 + *(int *)(vc8 + 0x30));
      (*pc4)();
      sk_00351e48(&stk00000020);
      sk_0034f544();
      (*eo9_03)();
      iv1 = *(int *)(vc8 + 0x30);
      sk_00351438(v98);
      (*pc4)();
      (*eo8_01)(vd0 + iv1);
      sk_0034f544(*(undefined8 *)(va8 + 0x20));
      (*eo8_07)();
      sk_003565c0((long)*(int *)(vc8 + 0x30));
      (*pc4)();
      sk_00350b78();
      (*eo8_01)();
      sk_003568e8();
      sk_00319628();
      sk_00353718();
      sk_0035056c(vf0);
      (*eo9_04)();
      sk_0034b804();
      (**(unsigned long (**)() )(eo16 + 8))(rx27,rx22);
      sk_00350bc0(&stk00000018);
      sk_003518b8();
      (*eo8_08)();
L_001d5444:
      sk_003567d4();
      sk_00353d14(v98);
      return;
    }
    sk_000277e8(rx27);
    sk_00353cb4();
    sk_003560c0();
    pc4 = (unsigned long (*)() )(*eo8_02)();
    sk_00354b14();
    sk_00356260();
    (*eo8_03)();
    sk_0034c3b4();
    (*pc4)();
    t3 = (*v68)(v78);
    if (sv00000008 != 0) {
      sk_0034c664();
      (**(unsigned long (**)() )(eo16_00 + 8))(rx27,rx23);
      sk_00354f8c();
      sk_00350630();
      (*eo8_09)();
      sk_003508fc();
      (*eo8_01)();
      goto L_001d5444;
    }
    sk_00354f8c();
    sk_00350630();
    (*eo8_04)();
    rx22 = rx23;
    if ((t3 & 1) == 0) goto L_001d5260;
    sk_00027818(t5);
    sk_003505f4();
    sk_00350b84();
    (*eo8_05)();
    rx23 = rx27;
    rx24 = rx26;
    rx27 = t5;
  } while( true );
}

/* FUN_001d58fc @ 0x001d58fc   (est. sk_r5_fatal_assert_001d58fc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d58fc(void)

{
  sk_00347d60();
                      sk_001afe4c();
}

/* FUN_001d590c @ 0x001d590c   (est. sk_r5_fatal_assert_001d590c) */
/* Confidence: low (mechanical translation; names heuristic) */
undefined8 sk_001d590c(ulong param_1,undefined8 param_2,long param_3)

{
  sk_c16_t at1;
  
  if ((long)param_1 < 0) {
                        sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_requires_lowerBound__str<__upp_005cda00,0x27,2,
                 Swift_Range_swift_005cda30_str,0x11,2,0x2f9,1);
  }
  if ((long)param_1 <= param_3) {
    at1._8_8_ = 0;
    at1._0_8_ = param_1;
    return at1._0_8_ << 0x40;
  }
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,&g_005be7c0,0,2,
               Swift_UnsafeBufferPointer_swift_005cdc10_str,0x1f,2,0x293,1);
}

/* FUN_001d5c90 @ 0x001d5c90   (est. sk_r5_fatal_assert_001d5c90) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d5c90(void)

{
  sk_00347d60();
                      sk_001afe4c();
}

/* FUN_001d5f58 @ 0x001d5f58   (est. sk_r5_fatal_assert_001d5f58) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d5f58(void)

{
  sk_00347d60();
                      sk_001afe4c();
}

/* FUN_001d6094 @ 0x001d6094   (est. sk_r5_swift_001d6094) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d6094(void)

{
  undefined8 stk00000000;
  undefined8 stk00000008;
  undefined8 stk00000018;
  undefined8 stk00000020;
  undefined8 stk00000028;
  undefined8 stk00000040;
  undefined8 eo1;
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long eo16;
  
  sk_0034c084();
  sk_000a6f88();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348f38();
  sk_00310b38(eo1);
  sk_00350c50();
  sk_00084180();
  (*eo9)();
  sk_00350780();
  sk_001679cc();
  sk_00351058();
  sk_0034d334();
  (*eo9_00)();
  sk_003507bc(*(undefined8 *)(eo16 + 8));
  (*eo8_00)();
  return;
}

/* FUN_001d614c @ 0x001d614c   (est. sk_r5_fatal_assert_001d614c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d614c(undefined8 param_1,undefined8 param_2,void (*param_3)(),undefined8 param_4,
                 undefined8 param_5,undefined8 param_6)

{
  int iv1;
  undefined8 t2;
  undefined8 t3;
  undefined8 t4;
  ulong t5;
  long n6;
  long eo8;
  long eo8_00;
  long eo8_01;
  unsigned long (*eo8_02)();
  unsigned long (*pc7)();
  undefined8 *pt8;
  unsigned long (*eo8_03)();
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  unsigned long (*eo8_06)();
  long eo8_07;
  unsigned long (*eo8_08)();
  unsigned long (*eo8_09)();
  unsigned long (*eo8_10)();
  unsigned long (*eo8_11)();
  unsigned long (*eo8_12)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  unsigned long (*eo9_01)();
  long eo9_02;
  unsigned long (*eo9_03)();
  unsigned long (*eo9_04)();
  undefined8 eo13;
  long eo14;
  long eo16;
  long eo16_00;
  long eo16_01;
  long eo16_02;
  long eo16_03;
  long eo16_04;
  unsigned long (*pc9)();
  undefined8 rx20;
  long rx21;
  undefined8 rx24;
  undefined8 rx27;
  sk_c16_t at10;
  sk_c16_t at11;
  long sv00000008;
  long vf0;
  long vd0;
  void (*apcc8)() [2];
  undefined8 v40;
  
  at10._0_8_ = (undefined8)(sk_00353cfc());
  at10._8_8_ = 0;
  n6 = at10._0_8_;
  pc9 = param_3;
  sk_003548d0();
  sk_00350a1c();
  t2 = sk_00377824();
  sk_0034ab20();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034dccc();
  sk_0034df54(0xff);
  sk_00377824();
  sk_00348bf8();
  sk_003722e4();
  sk_003490b8(&stk00000018);
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_003493c4();
  sk_0034acf0();
  (*g_00658c00)();
  sk_00350464();
  sk_003509a4();
  sk_0035060c();
  sk_00351f1c();
  sk_00377bec();
  sk_0034da98();
  apcc8[1] = pc9;
  sk_00310e08();
  sk_00348ce8();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_00350428();
  sk_003509a4();
  sk_00027754(param_6);
  at11._0_8_ = (undefined8)(sk_00348e30());
  at11._8_8_ = 0;
  sk_00377824(at11._0_8_,at11._8_8_,param_5);
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0007c028();
  (*g_00658c00)(*(undefined8 *)(eo8_01 + 0x40));
  sk_003493c4();
  sk_0034acf0();
  (*g_00658c00)();
  sk_00349c2c();
  (*g_00658c00)();
  sk_0034a464();
  (*g_00658c00)();
  sk_0034b540();
  (*g_00658c00)();
  t3 = sk_0034ba68();
  if (n6 < 0) {
    sk_00350410();
    sk_003488bc();
    sk_0034987c();
L_001d69c4:
                        sk_001afe4c();
  }
  sk_00350500();
  sv00000008 = sk_001a0414();
  sk_000277b8(param_6);
  sk_003509e0();
  (*eo9)();
  if (n6 != 0) {
    t4 = sk_003192a8(param_6);
    sk_003509e0(t4);
    t5 = (*eo8_02)();
    if ((t5 & 1) == 0) {
      sk_0035678c();
      pc7 = *(unsigned long (**)() )(eo16_00 + 0x10);
      (*pc7)(n6,rx27,rx24);
      sk_00310924(param_6);
      sk_0035322c();
      sk_003509e0();
      (*eo9_01)();
      sk_00359ad4();
      sk_00027754();
      pc9 = (unsigned long (*)() )sk_0014ae44();
      pt8 = (undefined8 *)(eo16_00 + 8);
      do {
        while( true ) {
          sk_003518ac(n6,v40);
          t5 = (*pc9)();
          if ((t5 & 1) != 0) goto L_001d66b4;
          sk_000277e8(param_6);
          t4 = sk_00353cb4();
          at11._0_8_ = (undefined8)((*eo8_03)(t4,n6,param_5,param_6));
          at11._8_8_ = 0;
          (**(unsigned long (**)() )(eo14 + 0x10))(eo13,at11._8_8_,t3);
          sk_0034c3b4();
          (*at11._0_8_)();
          t5 = (*param_3)(eo13);
          if (rx21 != 0) {
            sk_0034dae8();
            (**(unsigned long (**)() )(eo16_03 + 8))(rx20,param_5);
            sk_00354b14();
            sk_00351274();
            (*eo8_09)();
            pc9 = (unsigned long (*)() )*pt8;
            (*pc9)(v40,rx24);
            sk_00351f88();
            (*pc9)();
            (*pc9)(rx27,rx24);
            n6 = sk_0036b118(sv00000008);
            goto L_001d64a0;
          }
          sk_00354b14();
          sk_00351274();
          (*eo8_04)();
          if ((t5 & 1) != 0) break;
          sk_00027818(param_6);
          sk_00350648();
          sk_00351298();
          (*eo8_08)();
        }
        t5 = sk_001d69d8(n6,rx27,at10._8_4_ & 1,&stk00000008,rx20,param_5,
                             param_6);
        sk_00354f80();
        (*eo8_05)(rx27,rx24);
        t4 = sk_00027818(param_6);
        sk_0034cf94(t4);
        (*eo8_06)();
        sk_00353050(rx27);
        (*pc7)();
      } while (((t5 & 1) == 0) ||
              (sk_00353e2c(*(undefined8 *)(sv00000008 + 0x10)),
              eo8_07 != eo9_02));
L_001d66b4:
      sk_003518ac(rx27,v40);
      t5 = (*pc9)();
      if (((t5 & 1) == 0) || ((at10._8_4_ & 1) == 0)) {
        sk_00353124(&stk00000028);
        sk_00351df0();
        (*pc7)();
        sk_00352584(&stk00000040);
        sk_00310e20();
        sk_0034d844();
        sk_0034dad8();
        t5 = (*eo8_10)();
        if ((t5 & 1) == 0) {
          sk_00347d60();
          goto L_001d69c4;
        }
        pc9 = *(unsigned long (**)() )(eo16_00 + 8);
        sk_00350ea4();
        (*pc9)();
        sk_00351324();
        (*pc9)();
        pc7 = *(unsigned long (**)() )(eo16_00 + 0x20);
        at11._0_8_ = (undefined8)(sk_0035072c());
        at11._8_8_ = 0;
        (*pc7)(at11._0_8_,at11._8_8_,rx24);
        sk_00355e2c();
        t3 = sk_003595a8();
        (*pc7)(t3,v40,rx24);
        sk_00351990();
        sk_00350b9c(vf0);
        (*eo9_03)();
        iv1 = *(int *)(eo16_00 + 0x38);
        sk_000dbedc();
        sk_00352314();
        (*pc7)();
        (*pc9)(pt8,vf0 + iv1,rx24);
        sk_00350b9c(*(undefined8 *)(eo16 + 0x20),vf0);
        (*eo8_11)();
        (*pc7)(vd0 + g_0060e22c,vf0 + *(int *)(eo16_00 + 0x38),rx24);
        sk_003516e4();
        (*pc9)(pt8);
        sk_00319628(param_6);
        sk_00352098(&stk00000020);
        sk_0035136c(vd0);
        (*eo9_04)();
        sk_0034c664();
        (**(unsigned long (**)() )(eo16_04 + 8))(rx20,param_5);
        sk_00350bc0(&stk00000000);
        sk_003505e8();
        (*eo8_12)();
        sk_00310d34(0,t2);
        sk_00355c1c();
        sk_001a1854((undefined8 *)(eo16 + 0x20));
        n6 = sv00000008;
      }
      else {
        sk_0034ece8(rx20,param_5);
        (**(unsigned long (**)() )(eo16_02 + 8))();
        pc9 = (unsigned long (*)() )*pt8;
        sk_00350bf0();
        (*pc9)();
        sk_00350ea4();
        (*pc9)();
        (*pc9)(rx27,rx24);
        n6 = sv00000008;
      }
      goto L_001d64a0;
    }
  }
  sk_00310924(param_6);
  sk_00351184();
  sk_003509e0();
  (*eo9_00)();
  sk_001d69d8();
  sk_0034b3e8();
  (**(unsigned long (**)() )(eo16_01 + 8))();
  pc9 = *(unsigned long (**)() )(eo16_00 + 8);
  (*pc9)();
  sk_00350aa0();
  (*pc9)();
  n6 = sv00000008;
L_001d64a0:
  t2 = sk_00359b64(n6);
  sk_00353d14(t2,*(undefined8 *)((long)apcc8 - eo8_00));
  return;
}

/* FUN_001d69d8 @ 0x001d69d8   (est. sk_r5_fatal_assert_001d69d8) */
/* Confidence: low (mechanical translation; names heuristic) */
uint sk_001d69d8(undefined8 param_1,undefined8 param_2,uint param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7)

{
  int iv1;
  long n2;
  long n3;
  uint t4;
  long n5;
  undefined8 t6;
  undefined8 t7;
  unsigned long (*pc8)();
  ulong t9;
  long eo8;
  long eo8_00;
  long eo8_01;
  long n10;
  long eo8_02;
  long n11;
  long eo12;
  long eo12_00;
  unsigned long (*pc12)();
  long n13;
  unsigned long (*pc14)();
  undefined1 ast100 [8];
  undefined8 stf8;
  undefined4 astf0 [4];
  unsigned long (*ve0)();
  long vd8;
  long vd0;
  long vc8;
  long vc0;
  long vb8;
  long vb0;
  long va8;
  long va0;
  long v98;
  undefined8 v90;
  undefined8 v88;
  undefined8 v80;
  undefined8 v78;
  undefined8 v70;
  uint v64;
  
  v90 = param_5;
  v78 = param_4;
  v64 = param_3;
  v98 = sk_00377824(0,param_7,param_6,&g_0060e208,&g_0060e238);
  (*g_00658c00)(*(long *)(*(long *)(v98 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  va0 = (long)&ve0 - eo8;
  n5 = sk_00377824(0xff,param_7,param_6,&g_0060e208,&g_0060e230);
  va8 = sk_003722e4(0,n5,n5,lower_upper_005e1f90_str,0);
  vb8 = *(long *)(va8 + -8);
  (*g_00658c00)(*(undefined8 *)(vb8 + 0x40));
  n11 = ((long)&ve0 - eo8) - (eo8_00 + 0xfU & 0xfffffffffffffff0);
  vb0 = n11;
  (*g_00658c00)();
  n11 = n11 - eo12;
  vd0 = n11;
  v88 = param_6;
  v80 = param_7;
  t6 = sk_00377bec(param_7,param_6,n5,&g_0060e208,&L_0060e218);
  vc0 = sk_00310e08(0,n5,t6);
  vc8 = *(long *)(vc0 + -8);
  (*g_00658c00)(*(long *)(vc8 + 0x40) + 0xfU & 0xfffffffffffffff0);
  n11 = n11 - eo8_01;
  n10 = *(long *)(n5 + -8);
  vd8 = n11;
  (*g_00658c00)(*(undefined8 *)(n10 + 0x40));
  n11 = n11 - (eo8_02 + 0xfU & 0xfffffffffffffff0);
  (*g_00658c00)();
  n13 = n11 - eo12_00;
  pc14 = *(unsigned long (**)() )(n10 + 0x10);
  v70 = param_2;
  (*pc14)(n13,param_2,n5);
  t7 = sk_00027754(t6);
  pc8 = (unsigned long (*)() )sk_0014ae44();
  t4 = (*pc8)(n13,param_1,n5,t7);
  ve0 = *(unsigned long (**)() )(n10 + 8);
  (*ve0)(n13,n5);
  t4 = t4 & v64;
  if ((t4 & 1) == 0) {
    (*pc14)(n11,v70,n5);
    pc8 = (unsigned long (*)() )sk_00310e20(t6);
    t9 = (*pc8)(n11,param_1,n5,t6);
    n2 = vd0;
    if ((t9 & 1) == 0) {
      *(undefined4 *)(n13 + -0x10) = 1;
      *(undefined8 *)(n13 + -0x18) = 0x2f9;
      *(undefined1 *)(n13 + -0x20) = 2;
                          sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_requires_lowerBound__str<__upp_005cda00,0x27,2,
                   Swift_Range_swift_005cda30_str,0x11);
    }
    pc12 = *(unsigned long (**)() )(n10 + 0x20);
    v64 = t4;
    (*pc12)(vd0,n11,n5);
    n3 = va8;
    (*pc14)(n2 + *(int *)(va8 + 0x30),param_1,n5);
    n13 = vb0;
    n10 = vb8;
    (**(unsigned long (**)() )(vb8 + 0x10))(vb0,n2,n3);
    n11 = vd8;
    iv1 = *(int *)(n3 + 0x30);
    (*pc12)(vd8,n13,n5);
    pc8 = ve0;
    (*ve0)(n13 + iv1,n5);
    t4 = v64;
    (**(unsigned long (**)() )(n10 + 0x20))(n13,n2,n3);
    n10 = vc0;
    (*pc12)(n11 + *(int *)(vc0 + 0x24),n13 + *(int *)(n3 + 0x30),n5);
    (*pc8)(n13,n5);
    t6 = v80;
    pc8 = (unsigned long (*)() )sk_00319628(v80);
    n5 = va0;
    (*pc8)(va0,n11,v88,t6);
    (**(unsigned long (**)() )(vc8 + 8))(n11,n10);
    t6 = sk_00310d34(0,v98);
    sk_001a1854(n5,t6);
  }
  return (t4 ^ 0xffffffff) & 1;
}

/* FUN_001d6ef0 @ 0x001d6ef0   (est. sk_r5_fatal_assert_001d6ef0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d6ef0(void)

{
  int iv1;
  undefined1 zr;
  long n2;
  undefined8 t3;
  long n4;
  ulong t5;
  unsigned long (*eo8)();
  long eo8_00;
  long eo8_01;
  long eo8_02;
  long eo8_03;
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  unsigned long (*eo8_06)();
  unsigned long (*pc6)();
  unsigned long (*eo8_07)();
  unsigned long (*eo8_08)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  unsigned long (*eo9_01)();
  unsigned long (*eo9_02)();
  unsigned long (*eo9_03)();
  unsigned long (*eo9_04)();
  long eo16;
  long eo16_00;
  long eo16_01;
  undefined8 rx19;
  undefined8 rx20;
  unsigned long (*pc7)();
  long rx28;
  undefined8 rx30;
  sk_c16_t at8;
  undefined8 v50;
  undefined8 v30;
  
  sk_0008e518();
  sk_00351a38();
  sk_0034d574();
  sk_00350a1c(0xff);
  sk_00377824();
  n2 = sk_0034a654();
  sk_000a6f88();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_00348b5c();
  (*g_00658c00)();
  sk_00350464();
  sk_00349618();
  (*g_00658c00)(*(undefined8 *)(eo8_01 + 0x40));
  sk_00348a9c();
  (*g_00658c00)();
  sk_0034ae94();
  (*g_00658c00)();
  sk_0034aa28();
  sk_0035705c();
  sk_0034ca18();
  t3 = sk_00377bec();
  sk_0034d3f4();
  sk_00310e08();
  n4 = sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_00350428();
  sk_0034911c();
  (*g_00658c00)(*(undefined8 *)(eo8_03 + 0x40));
  sk_003497b4();
  sk_00358978();
  sk_00348f14();
  sk_00377824(0xff);
  sk_0034e67c();
  sk_0034d464();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034af20();
  sk_00356000();
  sk_003507e0();
  t5 = (*eo8_04)();
  if ((t5 & 1) == 0) {
    sk_001aeab4(rx19);
    sk_0034f044();
    if (!(bool)zr) {
      sk_0034f384();
      (**(unsigned long (**)() )(eo16_01 + 0x20))(eo8);
      sk_00351984();
      sk_00350624();
      (*eo9)();
      sk_003506e8();
      sk_003507e0();
      (*eo9_00)();
      sk_00353d94();
      sk_00353f50();
      sk_00350878();
      (*eo9_01)();
      sk_00356644();
      (*eo8_05)();
      sk_00310924();
      sk_0035036c();
      (*eo9_02)(rx19);
      sk_00310e20(t3);
      sk_00350a88();
      sk_0034e5fc();
      t5 = (*eo8_06)();
      if ((t5 & 1) != 0) {
        pc6 = *(unsigned long (**)() )(eo16_00 + 8);
        t3 = (*pc6)(rx20,rx19);
        pc7 = *(unsigned long (**)() )(rx28 + 0x20);
        sk_003537f0(t3,v30);
        (*pc7)();
        sk_00351ab0(v30 + *(int *)(n2 + 0x30));
        (*pc7)();
        sk_00351c4c();
        at8._0_8_ = (undefined8)(sk_003508cc());
        at8._8_8_ = 0;
        (*eo9_03)(at8._0_8_,at8._8_8_,n2);
        iv1 = *(int *)(n2 + 0x30);
        sk_0035190c();
        (*pc7)();
        (*eo8)(v50 + iv1);
        at8._0_8_ = (undefined8)(sk_003508cc(*(undefined8 *)(eo16 + 0x20)));
        at8._8_8_ = 0;
        (*eo8_07)(at8._0_8_,at8._8_8_,n2);
        sk_00355e5c((long)*(int *)(n2 + 0x30),eo8_02 + *(int *)(n4 + 0x24));
        (*pc7)();
        sk_00350a34();
        (*eo8)();
        sk_00356964();
        sk_00352eb4();
        sk_003505c4(rx20,eo8_02);
        (*eo9_04)();
        sk_00353be8();
        sk_00084180();
        (*eo8_08)();
        sk_00350af4();
        (*pc6)();
        sk_0008e500(rx30);
        return;
      }
      sk_00347d60();
      goto L_001d7344;
    }
    sk_003489dc(0x686);
    sk_00349a2c();
  }
  else {
    sk_00350410();
    sk_003488bc();
    sk_00349a2c();
  }
  sk_0035110c();
L_001d7344:
                      sk_001afe4c();
}

/* FUN_001d7368 @ 0x001d7368   (est. sk_r5_fatal_assert_001d7368) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d7368(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  int iv1;
  undefined1 zr;
  undefined8 t2;
  long n3;
  undefined8 t4;
  ulong t5;
  long eo8;
  long n6;
  long eo8_00;
  long eo8_01;
  unsigned long (*eo8_02)();
  unsigned long (*eo8_03)();
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  unsigned long (*eo8_06)();
  unsigned long (*eo8_07)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  unsigned long (*eo9_01)();
  unsigned long (*eo9_02)();
  unsigned long (*eo9_03)();
  unsigned long (*eo9_04)();
  long eo13;
  long eo16;
  long eo16_00;
  undefined8 rx20;
  unsigned long (*pc7)();
  long rx21;
  long rx22;
  long rx24;
  undefined8 rx27;
  undefined8 rx30;
  sk_c16_t at8;
  undefined8 st40;
  undefined8 st18;
  
  sk_0008e518();
  t2 = sk_00357788();
  sk_0034d574();
  sk_003537d4();
  sk_00351f1c();
  sk_00377824();
  n3 = sk_0034a654();
  sk_000a6f88();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_003493c4();
  sk_0034c2f8();
  (*g_00658c00)();
  sk_0034aa14();
  sk_00350018();
  sk_00377bec();
  sk_0034d734();
  sk_00310e08();
  sk_00348ce8();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034cff4();
  n6 = *(long *)(rx24 + -8);
  (*g_00658c00)(*(undefined8 *)(n6 + 0x40));
  sk_003497b4();
  sk_0035a2b8();
  sk_00350500();
  sk_00310d68();
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b0c4();
  sk_0034998c();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_003489c0();
  (*g_00658c00)();
  sk_0034a464();
  (*g_00658c00)();
  sk_0034aea8();
  (*g_00658c00)();
  t4 = sk_00350464();
  if (eo13 == 0) {
L_001d7798:
    sk_0008e500(rx30);
    return;
  }
  if (eo13 < 0) {
    sk_00350410();
    sk_003488bc();
    sk_00358918();
    sk_00349a2c();
  }
  else {
    sk_003506e8();
    sk_003507e0(t2);
    (*eo9)();
    sk_00310924(rx21);
    sk_00350b24();
    sk_003507e0();
    (*eo9_00)();
    sk_003192d8(rx21);
    sk_00350c50();
    sk_00350630();
    sk_003518a0();
    (*eo9_01)();
    pc7 = *(unsigned long (**)() )(eo16_00 + 8);
    sk_000e72b0();
    (*pc7)();
    sk_00351274();
    (*pc7)();
    sk_00359be0();
    t2 = sk_0034b2a8();
    if (!(bool)zr) {
      sk_0034ee28(*(undefined8 *)(eo16_00 + 0x20));
      (*eo8_02)();
      sk_003534bc();
      sk_00350624(st18);
      (*eo9_02)();
      sk_003507e0(rx27);
      (*eo9_00)();
      sk_0007c1c4(*(undefined8 *)(n6 + 8));
      (*eo8_03)();
      sk_00310e20(param_3);
      sk_0034c5dc();
      sk_003516b4();
      t5 = (*eo8_04)();
      if ((t5 & 1) != 0) {
        sk_00356670();
        sk_003513d8();
        (*eo8_02)();
        (*eo8_02)(rx21 + *(int *)(n3 + 0x30),rx27);
        sk_003534bc();
        at8._0_8_ = (undefined8)(sk_003508a8());
        at8._8_8_ = 0;
        (*eo9_03)(at8._0_8_,at8._8_8_,n3);
        iv1 = *(int *)(n3 + 0x30);
        sk_003510ac();
        (*eo8_02)();
        (*pc7)(st40 + iv1);
        at8._0_8_ = (undefined8)(sk_003508a8(*(undefined8 *)(eo16 + 0x20)));
        at8._8_8_ = 0;
        (*eo8_05)(at8._0_8_,at8._8_8_,n3);
        (*eo8_02)(rx21 + *(int *)(rx22 + 0x24),st40 + *(int *)(n3 + 0x30))
        ;
        sk_00350a70();
        (*pc7)();
        sk_00351bb8();
        sk_003511d8(rx20,rx21);
        (*eo9_04)();
        sk_00354324();
        sk_0035072c();
        (*eo8_06)();
        sk_0006b6f4();
        (*eo8_03)();
        goto L_001d7798;
      }
      sk_00347d60();
      goto L_001d77d8;
    }
    sk_00351a08(t2,t4);
    (*eo8_07)();
    *(int *)(eo8_01 + -0x10) = (int)pc7;
    sk_00348b7c(0x69a);
    sk_0035863c();
    sk_00349a2c();
  }
  sk_0035110c();
L_001d77d8:
                      sk_001afe4c();
}

/* FUN_001d7814 @ 0x001d7814   (est. sk_r5_swift_001d7814) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d7814(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined1 zr;
  undefined8 t1;
  undefined8 t2;
  unsigned long (*pc3)();
  unsigned long (*pc4)();
  ulong t5;
  undefined8 t6;
  undefined8 eo8;
  long eo8_00;
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo8_03)();
  unsigned long (*eo8_04)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long eo16;
  long eo16_00;
  long eo16_01;
  long eo16_02;
  undefined8 rx27;
  unsigned long (*pc7)();
  undefined8 rx30;
  sk_c16_t at8;
  undefined8 st50;
  undefined8 v28;
  
  sk_0008e518();
  t1 = sk_00351a14();
  sk_00348b94(param_3);
  t2 = sk_00377824();
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034eb2c();
  sk_00349748();
  sk_003513b4();
  sk_00377824();
  sk_00348cd0();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_003492ac();
  (*g_00658c00)();
  sk_0034bc80();
  sk_00310d68(0xff);
  sk_0034e67c();
  sk_00310d68();
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b460();
  sk_0034a5c8();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_00350428();
  sk_00358978();
  sk_0031b0bc();
  sk_00351250();
  sk_00350b48(t1);
  (*eo9)();
  sk_0034f044();
  if ((bool)zr) {
    (**(unsigned long (**)() )(eo16_01 + 8))();
    sk_0034fe64();
    sk_00084174(v28);
    (*eo9_00)();
    pc3 = (unsigned long (*)() )sk_00310924();
    sk_0034c3c4();
    sk_00350524();
    sk_00377bec();
    sk_00027754();
    pc4 = (unsigned long (*)() )sk_0014ae44();
    while( true ) {
      sk_00357910();
      sk_00084174();
      (*pc3)();
      sk_00351b38(v28);
      t5 = (*pc4)();
      pc7 = *(unsigned long (**)() )(eo16_00 + 8);
      sk_00351f88();
      (*pc7)();
      if ((t5 & 1) != 0) break;
      t6 = sk_00351b84();
      sk_00351238(t6,v28);
      at8._0_8_ = (undefined8)((*eo8_01)());
      at8._8_8_ = 0;
      (**(unsigned long (**)() )(eo16 + 0x10))(st50,at8._8_8_,t2);
      sk_0034cfa4();
      (*at8._0_8_)();
      sk_003560a8();
      t6 = sk_0034d49c();
      sk_00351f4c(t6,t1);
      t5 = (*eo8_02)();
      sk_00350738(*(undefined8 *)(eo16 + 8));
      (*eo8_03)();
      if ((t5 & 1) != 0) {
        (**(unsigned long (**)() )(eo16_00 + 0x20))(eo8,v28,rx27);
        at8._0_8_ = (undefined8)(sk_00352c68());
        at8._8_8_ = 0;
        goto L_001d7b90;
      }
      t6 = sk_00027818();
      sk_00350810(t6,v28);
      (*eo8_04)();
    }
    (*pc7)(v28,rx27);
    at8._8_8_ = 1;
    at8._0_8_ = eo8;
L_001d7b90:
    sk_00350774(at8._0_8_,at8._8_8_);
    sk_000839d8();
  }
  else {
    pc3 = *(unsigned long (**)() )(eo16_02 + 0x20);
    sk_00350630();
    (*pc3)();
    sk_00351214(eo8);
    (*pc3)();
  }
  sk_0008e500(rx30);
  return;
}

/* FUN_001d7bb0 @ 0x001d7bb0   (est. sk_r5_fatal_assert_001d7bb0) */
/* Confidence: low (mechanical translation; names heuristic) */
undefined8 sk_001d7bb0(ulong param_1,ulong param_2)

{
  ulong t1;
  ushort t2;
  sk_c16_t at3;
  ulong t4;
  ulong t5;
  long n6;
  long n7;
  undefined8 t8;
  char *pc9;
  uint t10;
  ulong t11;
  ulong t12;
  ulong t13;
  ulong t14;
  long n15;
  sk_c16_t at16;
  undefined8 t17;
  ulong v70;
  ulong st68;
  
  t11 = param_2 >> 0x38 & 0xf;
  t1 = param_1 & 0xffffffffffff;
  if ((param_2 & 0x2000000000000000) != 0) {
    t1 = t11;
  }
  n15 = t1 * 4;
  t10 = (uint)(param_1 >> 0x3b) & 1;
  if ((param_2 & 0x1000000000000000) == 0) {
    t10 = 1;
  }
  t12 = param_2 & 0xffffffffffffff;
  at3._8_8_ = param_1 & 0xffffffffffff;
  at3._0_8_ = (param_2 & 0xfffffffffffffff) + 0x20;
  t1 = 7;
  if (t10 == 0) {
    t1 = 0xb;
  }
  t13 = 0xf;
  do {
    if (n15 - (t13 >> 0xe) == 0) {
      t13 = 0;
      t8 = 1;
L_001d7f5c:
      at16._8_8_ = t8;
      at16._0_8_ = t13;
      return at16._0_8_;
    }
    t4 = sk_00167404(t13,param_1,param_2);
    t5 = t4 >> 8 & 0x3f;
    t14 = t4 >> 0x10;
    if (t5 != 0) {
      if ((param_2 >> 0x3c & 1) == 0) {
L_001d7c50:
        t5 = t5 + t14;
        if ((long)t5 < (long)t14) {
                              sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_requires_lowerBound__str<__upp_005cda00,0x27
                       ,2,Swift_Range_swift_005cda30_str,0x11,2,0x2f9,1);
        }
        goto L_001d7c70;
      }
L_001d8054:
      sk_002bbcd8();
L_001d8058:
      t17 = 0x584;
      pc9 = UnsafeBufferPointer_has_a_nil_st_005cf020_str;
      t8 = 0x35;
      goto L_001d8048;
    }
    if (n15 - (t4 >> 0xe) == 0) {
      t5 = t14;
      if ((param_2 >> 0x3c & 1) != 0) goto L_001d8054;
L_001d7c70:
      if ((param_2 >> 0x3d & 1) == 0) goto L_001d7c74;
L_001d7d44:
      v70 = param_1;
      st68 = t12;
      if (t5 <= t11) {
        n7 = t5 - t14;
        if (-1 < n7) {
          t10 = sk_002a200c((long)&v70 + t14,n7);
          n6 = (long)&v70 + t14;
          goto L_001d7d80;
        }
        goto L_001d800c;
      }
L_001d7fcc:
      t17 = 0x7a9;
      pc9 = &g_005be7c0;
      t8 = 0;
L_001d8048:
                          sk_001afe4c(Fatal_error_005accd0_str,0xb,2,pc9,t8,2,
                   Swift_UnsafeBufferPointer_swift_005cdc10_str,0x1f,2,t17,1);
    }
    if ((param_2 >> 0x3c & 1) != 0) {
L_001d7f18:
      t5 = sk_002c6d00(t14,param_1,param_2);
      if ((param_2 >> 0x3c & 1) != 0) goto L_001d8054;
      goto L_001d7c50;
    }
    if ((param_2 >> 0x3d & 1) != 0) {
      v70 = param_1;
      st68 = t12;
      t5 = t14 + 1;
      if ((t5 != t11) &&
         ((*(ushort *)((long)&v70 + t14) == 0xa0d ||
          ((*(ushort *)((long)&v70 + t14) & 0x8080) != 0)))) goto L_001d7f18;
      goto L_001d7d44;
    }
    at16 = at3;
    if ((param_1 >> 0x3c & 1) == 0) {
      at16._0_8_ = (undefined8)(sk_002a9ba8(param_1,param_2));
      at16._8_8_ = 0;
    }
    t5 = t14 + 1;
    if (t5 != at16._8_8_) {
      if (at16._0_8_ == 0) goto L_001d8098;
      t2 = *(ushort *)(at16._0_8_ + t14);
      if ((t2 == 0xa0d) || ((t2 & 0x8080) != 0)) goto L_001d7f18;
    }
L_001d7c74:
    at16 = at3;
    if ((param_1 >> 0x3c & 1) == 0) {
      at16._0_8_ = (undefined8)(sk_002a9ba8(param_1,param_2));
      at16._8_8_ = 0;
    }
    if (at16._8_8_ < (long)t5) goto L_001d7fcc;
    n6 = 0;
    if (at16._0_8_ != 0) {
      n6 = at16._0_8_ + t14;
    }
    n7 = t5 - t14;
    if (n7 < 0) {
L_001d800c:
      t17 = 0x582;
      pc9 = UnsafeBufferPointer_with_negativ_005cdf60_str;
      t8 = 0x27;
      goto L_001d8048;
    }
    if ((n7 != 0) && (n6 == 0)) goto L_001d8058;
    t10 = sk_002a200c(n6,n7);
L_001d7d80:
    at16._0_8_ = (undefined8)(sk_t_002a2698(n6,n7,t10 & 1));
    at16._8_8_ = 0;
    t5 = at16._8_8_;
    if (at16._0_8_ != 0x30 || t5 != 0xe100000000000000) {
      if (((t5 ^ 0xffffffffffffffff) & 0x6000000000000000) == 0) {
        sk_003a25d4(t5);
      }
      else {
        t4 = sk_002a0d50(at16._0_8_,t5,0x30,0xe100000000000000,0);
        sk_003a25d4(t5);
        if ((t4 & 1) != 0) goto L_001d7dd4;
      }
      t8 = 0;
      goto L_001d7f5c;
    }
    sk_003a25d4(t5);
L_001d7dd4:
    t5 = sk_0029eb58(t13,param_1,param_2);
    t13 = t5 >> 8 & 0x3f;
    if (t13 == 0) {
      if (n15 - (t5 >> 0xe) == 0) {
        t13 = 0;
      }
      else {
        t13 = t5 >> 0x10;
        if ((param_2 >> 0x3d & 1) == 0) {
          at16 = at3;
          if ((param_1 >> 0x3c & 1) == 0) {
            at16._0_8_ = (undefined8)(sk_002a9ba8(param_1,param_2));
            at16._8_8_ = 0;
          }
          if (t13 + 1 != at16._8_8_) {
            if (at16._0_8_ == 0) goto L_001d8098;
            t2 = *(ushort *)(at16._0_8_ + t13);
L_001d7e58:
            if ((t2 == 0xa0d) || ((t2 & 0x8080) != 0)) {
              t13 = sk_002c6d00(t13,param_1,param_2);
              goto L_001d7e6c;
            }
          }
        }
        else {
          v70 = param_1;
          st68 = t12;
          if (t13 + 1 != t11) {
            t2 = *(ushort *)((long)&v70 + t13);
            goto L_001d7e58;
          }
        }
        t13 = 1;
      }
    }
L_001d7e6c:
    t5 = t5 + t13 * 0x10000;
    t13 = t5 & 0xffffffffffff0000;
    if (n15 - (t13 >> 0xe) == 0) {
      n7 = 0;
L_001d7ef0:
      t13 = t13 | n7 << 8;
    }
    else {
      t5 = t5 >> 0x10;
      if ((param_2 >> 0x3d & 1) != 0) {
        v70 = param_1;
        st68 = t12;
        if (t5 + 1 != t11) {
          t2 = *(ushort *)((long)&v70 + t5);
          goto L_001d7edc;
        }
L_001d7eec:
        n7 = 1;
        goto L_001d7ef0;
      }
      at16 = at3;
      if ((param_1 >> 0x3c & 1) == 0) {
        at16._0_8_ = (undefined8)(sk_002a9ba8(param_1,param_2));
        at16._8_8_ = 0;
      }
      if (t5 + 1 == at16._8_8_) goto L_001d7eec;
      if (at16._0_8_ == 0) {
L_001d8098:
                            sk_001afe4c(Fatal_error_005accd0_str,0xb,2,unsafelyUnwrapped_of_nil_optiona_005ce1c0_str,0x21,2
                     ,Swift_Optional_swift_005ce1f0_str,0x14,2,0x179,1);
      }
      t2 = *(ushort *)(at16._0_8_ + t5);
L_001d7edc:
      if ((t2 != 0xa0d) && ((t2 & 0x8080) == 0)) goto L_001d7eec;
      n7 = sk_002c6d00(t5,param_1,param_2);
      if (n7 < 0x40) goto L_001d7ef0;
    }
    t13 = t13 | t1;
  } while( true );
}

/* FUN_001d80e0 @ 0x001d80e0   (est. sk_r5_swift_001d80e0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d80e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  unsigned long (*pc1)();
  undefined8 t2;
  unsigned long (*pc3)();
  ulong t4;
  unsigned long (*pc5)();
  undefined8 t6;
  undefined8 eo8;
  long eo8_00;
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo8_03)();
  unsigned long (*eo8_04)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long eo16;
  long rx21;
  undefined8 rx22;
  undefined8 rx25;
  unsigned long (*pc7)();
  undefined8 rx30;
  sk_c16_t at8;
  undefined8 st70;
  undefined8 st28;
  undefined1 ast20 [32];
  
  pc1 = (unsigned long (*)() )sk_00353cfc();
  sk_00027754(param_4);
  at8._0_8_ = (undefined8)(sk_00348e30());
  at8._8_8_ = 0;
  t2 = sk_00377824(at8._0_8_,at8._8_8_,param_3);
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034aa9c();
  sk_003582f8();
  sk_0034d8f4();
  sk_00377824();
  sk_00348ce8();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_00348a9c();
  (*g_00658c00)();
  sk_0034b3d8();
  sk_000277b8(param_4);
  sk_00350b30();
  sk_00100c38();
  (*eo9)();
  sk_00310924(param_4);
  sk_00351360();
  sk_00352e78();
  sk_00377bec();
  sk_00027754();
  pc3 = (unsigned long (*)() )sk_0014ae44();
  do {
    sk_00100c38(st28);
    (*eo9_00)();
    sk_00350b6c();
    sk_00351b20();
    t4 = (*pc3)();
    pc7 = *(unsigned long (**)() )(eo16 + 8);
    sk_003508b4();
    (*pc7)();
    if ((t4 & 1) != 0) {
      sk_00350630();
      (*pc7)();
      t2 = 1;
L_001d83a4:
      sk_00352480(eo8,t2);
      sk_000839d8();
L_001d83b0:
      sk_00353d14(rx30);
      return;
    }
    pc5 = (unsigned long (*)() )sk_000277e8(param_4);
    pc5 = (unsigned long (*)() )(*pc5)(ast20,rx25,param_3,param_4);
    at8._0_8_ = (undefined8)(sk_00352b14());
    at8._8_8_ = 0;
    (*eo8_01)(at8._0_8_,at8._8_8_,t2);
    sk_0034cfa4();
    (*pc5)();
    t4 = (*pc1)(st70);
    sk_00354f8c();
    sk_00350a34();
    (*eo8_02)();
    if (rx21 != 0) {
      (*pc7)(rx25,rx22);
      goto L_001d83b0;
    }
    if ((t4 & 1) != 0) {
      at8._0_8_ = (undefined8)(sk_00352498(*(undefined8 *)(eo16 + 0x20)));
      at8._8_8_ = 0;
      (*eo8_04)(at8._0_8_,at8._8_8_,rx22);
      t2 = 0;
      goto L_001d83a4;
    }
    sk_00358ddc();
    t6 = sk_00027818();
    sk_00350b84(t6,rx25);
    (*eo8_03)();
    param_4 = t2;
  } while( true );
}

/* FUN_001d83cc @ 0x001d83cc   (est. sk_r5_swift_001d83cc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d83cc(void)

{
  undefined8 t1;
  undefined8 ax3;
  undefined8 eo8;
  unsigned long (*eo8_00)();
  long eo16;
  long rx21;
  undefined8 sv00000048;
  
  sk_00353cfc();
  sk_00351cf4();
  t1 = sk_00027754(ax3);
  sk_0034a944();
  sk_000dbf08();
  sk_00377824();
  sk_00352efc();
  sk_00310d68();
  sk_00348d64();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034aee4();
  sk_0034ed88();
  sk_001d852c();
  if (rx21 == 0) {
    (*g_00658c00)();
    sk_00027754(t1);
    sk_00348e30();
    sk_00377824();
    sk_003536ac();
    sk_00350810(eo8,sk_0031b0ec);
    sk_001d88fc();
    sk_000e72b0(*(undefined8 *)(eo16 + 8));
    (*eo8_00)();
  }
  sk_0035725c();
  sk_00353d14(sv00000048);
  return;
}

/* FUN_001d852c @ 0x001d852c   (est. sk_r5_swift_001d852c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d852c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  unsigned long (*pc1)();
  undefined8 t2;
  undefined8 t3;
  unsigned long (*pc4)();
  ulong t5;
  undefined8 t6;
  unsigned long (*pc7)();
  undefined8 eo1;
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo8_03)();
  unsigned long (*eo8_04)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long eo16;
  long rx21;
  undefined8 rx22;
  undefined8 rx26;
  unsigned long (*pc8)();
  undefined8 rx30;
  sk_c16_t at9;
  undefined8 v78;
  undefined8 st30;
  
  pc1 = (unsigned long (*)() )sk_00353cfc();
  t2 = sk_00027754(param_4);
  sk_00027754();
  at9._0_8_ = (undefined8)(sk_00348e30());
  at9._8_8_ = 0;
  t3 = sk_00377824(at9._0_8_,at9._8_8_,param_3);
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b250();
  sk_0034e808();
  sk_0035256c();
  sk_00377824();
  sk_00348e60();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348bd8();
  (*g_00658c00)();
  sk_0034c2d8();
  sk_00310924(t2);
  sk_00351250();
  sk_003510dc();
  (*eo9)();
  sk_000277b8(t2);
  sk_0034f3e4(t2);
  sk_00377bec();
  sk_00027754();
  pc4 = (unsigned long (*)() )sk_0014ae44();
  while( true ) {
    sk_003510dc(st30);
    (*eo9_00)();
    sk_00351160();
    sk_00351f4c();
    t5 = (*pc4)();
    pc8 = *(unsigned long (**)() )(eo16 + 8);
    sk_00351360();
    (*pc8)();
    if ((t5 & 1) != 0) {
      sk_00350b78();
      t2 = (*pc8)();
      t3 = 1;
      goto L_001d87c8;
    }
    sk_00356078();
    sk_003196e8();
    at9._0_8_ = (undefined8)(sk_0034d394());
    at9._8_8_ = 0;
    (*eo8_00)(at9._0_8_,at9._8_8_,t5);
    sk_000277e8(t2);
    t6 = sk_00353cb4();
    pc7 = (unsigned long (*)() )(*eo8_01)(t6,rx22,param_3,t2);
    sk_00354b14();
    (*eo8_02)(v78,eo1,t3);
    sk_0034c3b4();
    (*pc7)();
    t5 = (*pc1)(v78);
    sk_00358dac();
    sk_003508b4();
    (*eo8_03)();
    if (rx21 != 0) break;
    if ((t5 & 1) != 0) {
      at9._0_8_ = (undefined8)(sk_00350af4(*(undefined8 *)(eo16 + 0x20)));
      at9._8_8_ = 0;
      t2 = (*eo8_04)(at9._0_8_,at9._8_8_,rx26);
      t3 = 0;
L_001d87c8:
      sk_00353220(t2,t3);
      sk_000839d8();
L_001d87ec:
      sk_00353d14(rx30);
      return;
    }
  }
  (*pc8)(rx22,rx26);
  goto L_001d87ec;
}

/* FUN_001d8808 @ 0x001d8808   (est. sk_r5_swift_001d8808) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d8808(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5)

{
  undefined8 t1;
  unsigned long (*pc2)();
  long n3;
  sk_c16_t at4;
  undefined1 ast70 [32];
  
  t1 = sk_00027754(param_5);
  pc2 = (unsigned long (*)() )sk_000277e8();
  at4._0_8_ = (undefined8)((*pc2)(ast70,param_2,param_4,t1));
  at4._8_8_ = 0;
  t1 = sk_00027754(t1);
  n3 = sk_00377824(0,t1,param_4,&g_00611b24,&L_00611b34);
  (**(unsigned long (**)() )(*(long *)(n3 + -8) + 0x10))(param_1,at4._8_8_,n3);
  (*at4._0_8_)(ast70,0);
  return;
}

/* FUN_001d88fc @ 0x001d88fc   (est. sk_r5_swift_001d88fc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d88fc(undefined8 param_1,void (*param_2)(),undefined8 param_3,long param_4,long param_5,
                 undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iv1;
  long eo8;
  long n2;
  long eo8_00;
  long eo8_01;
  undefined8 eo12;
  long eo13;
  long n3;
  long rx21;
  long n4;
  undefined8 t5;
  long n6;
  long n7;
  long v80;
  undefined8 v78;
  undefined8 v70;
  unsigned long (*v68)();
  
  v80 = *(long *)(param_5 + -8);
  v78 = param_8;
  v70 = param_3;
  v68 = param_2;
  (*g_00658c00)(*(undefined8 *)(v80 + 0x40));
  n6 = (long)&v80 - (eo8 + 0xfU & 0xfffffffffffffff0);
  n4 = *(long *)(param_4 + 0x10);
  n2 = *(long *)(n4 + -8);
  (*g_00658c00)(*(undefined8 *)(n2 + 0x40));
  n7 = n6 - (eo8_00 + 0xfU & 0xfffffffffffffff0);
  (*g_00658c00)(*(undefined8 *)(*(long *)(param_4 + -8) + 0x40));
  n3 = n7 - (eo8_01 + 0xfU & 0xfffffffffffffff0);
  (**(unsigned long (**)() )(eo13 + 0x10))(n3,eo12);
  t5 = 1;
  iv1 = sk_000839f8(n3,1,n4);
  if (iv1 != 1) {
    (**(unsigned long (**)() )(n2 + 0x20))(n7,n3,n4);
    (*v68)(param_1,n7,n6);
    (**(unsigned long (**)() )(n2 + 8))(n7,n4);
    if (rx21 != 0) {
      (**(unsigned long (**)() )(v80 + 0x20))(v78,n6,param_5);
      return;
    }
    t5 = 0;
  }
  sk_000839d8(param_1,t5,1,param_6);
  return;
}

/* FUN_001d8b38 @ 0x001d8b38   (est. sk_r5_swift_001d8b38) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d8b38(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined1 zr;
  undefined8 t1;
  undefined8 eo8;
  unsigned long (*eo8_00)();
  long eo8_01;
  unsigned long (*eo9)();
  long eo16;
  long eo16_00;
  unsigned long (*pc2)();
  undefined8 rx21;
  undefined8 rx22;
  undefined8 rx30;
  
  sk_0008e518();
  sk_0035316c();
  sk_00351ad4(param_3);
  sk_0034a944();
  sk_00351420();
  t1 = sk_00377824();
  sk_00310d68(0xff,t1);
  sk_0034e57c();
  sk_00310d68();
  sk_00348cd0();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b2f8();
  sk_00349c70();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b0c4();
  sk_0031b110();
  sk_0035133c();
  sk_000b4390();
  (*eo9)();
  sk_0034e1b0();
  if ((bool)zr) {
    sk_003518b8(*(undefined8 *)(eo16 + 8));
    (*eo8_00)();
    (*g_00658c00)();
    sk_003539e4();
    *(undefined8 *)(eo8_01 + -0x20) = rx22;
    *(undefined8 *)(eo8_01 + -0x18) = param_3;
    *(undefined8 *)(eo8_01 + -0x10) = param_4;
    *(undefined8 *)(eo8_01 + -8) = rx21;
    sk_001d852c(eo8,sk_0031b140);
  }
  else {
    pc2 = *(unsigned long (**)() )(eo16_00 + 0x20);
    sk_00350518();
    (*pc2)();
    sk_00350b18(eo8);
    (*pc2)();
  }
  sk_0008e500(rx30);
  return;
}

/* FUN_001d8cdc @ 0x001d8cdc   (est. sk_r5_swift_001d8cdc) */
/* Confidence: low (mechanical translation; names heuristic) */
uint sk_001d8cdc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5)

{
  uint t1;
  undefined8 t2;
  unsigned long (*pc3)();
  
  sk_00027754(param_4);
  t2 = sk_00027754();
  t2 = sk_00377824(0,t2,param_3,&g_00611b24,&L_00611b34);
  pc3 = (unsigned long (*)() )sk_0014ae44(param_5);
  t1 = (*pc3)(param_1,param_2,t2,param_5);
  return t1 & 1;
}

/* FUN_001d8d78 @ 0x001d8d78   (est. sk_r5_fatal_assert_001d8d78) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d8d78(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 stk00000000;
  undefined8 stk00000008;
  undefined8 stk00000010;
  undefined8 stk00000018;
  undefined8 stk00000028;
  undefined8 stk00000030;
  unsigned long (*pc1)();
  int iv2;
  undefined1 zr;
  undefined8 t3;
  ulong t4;
  undefined8 t5;
  undefined8 t6;
  ulong t7;
  undefined8 t8;
  long eo8;
  long eo8_00;
  long eo8_01;
  long eo8_02;
  undefined8 eo8_03;
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  undefined8 *eo8_06;
  unsigned long (*eo8_07)();
  unsigned long (*eo8_08)();
  unsigned long (*eo8_09)();
  unsigned long (*eo8_10)();
  unsigned long (*eo8_11)();
  unsigned long (*eo8_12)();
  unsigned long (*eo8_13)();
  unsigned long (*eo8_14)();
  unsigned long (*eo8_15)();
  unsigned long (*eo9)();
  ulong t9;
  unsigned long (*eo9_00)();
  unsigned long (*eo9_01)();
  unsigned long (*eo9_02)();
  unsigned long (*eo16)();
  unsigned long (*eo16_00)();
  long eo16_01;
  unsigned long (*pc10)();
  long rx21;
  unsigned long (*pc11)();
  long rx26;
  sk_c16_t at12;
  undefined8 sv00000008;
  undefined8 v150;
  long v128;
  long v120;
  undefined8 st108;
  undefined8 ve0;
  undefined8 vd0;
  long vb8;
  undefined8 v80;
  undefined1 v58 [16];
  undefined8 *v48;
  ulong v40;
  unsigned long (*v38)();
  unsigned long (*v30)();
  unsigned long (*v28)();
  undefined8 v20;
  long v18;
  undefined8 v10;
  
  *(undefined8 *)v58 = sk_00353cfc(); *(undefined8 *)(v58 + 8) = 0;
  sk_0034de64();
  sk_00353160();
  t3 = sk_00377824();
  sk_0034b0b4();
  sk_00352360();
  sk_003722e4();
  sk_003490b8(&v20);
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_003493c4();
  sk_0034acf0();
  (*g_00658c00)();
  sk_00350464();
  sk_003509a4();
  sk_0034e5cc();
  t4 = sk_00377bec();
  at12._0_8_ = (undefined8)(sk_00350488());
  at12._8_8_ = 0;
  sk_00310e08(at12._0_8_,at12._8_8_,t4);
  sk_0034a450();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_00350428();
  sk_003509a4();
  at12._0_8_ = (undefined8)(sk_00350920());
  at12._8_8_ = 0;
  sk_00377824(at12._0_8_,at12._8_8_,param_3);
  sk_003490b8(&stk00000030);
  v30 = eo16;
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_003493c4();
  sk_0034acf0();
  (*g_00658c00)();
  sk_0034a4f8();
  (*g_00658c00)();
  sk_00350464();
  sk_0034c754();
  sk_00350b84();
  t5 = sk_00319308();
  sk_000a6f88();
  v38 = eo16_00;
  (*g_00658c00)(*(undefined8 *)(eo8_01 + 0x40));
  sk_003493c4();
  sk_0034acf0();
  (*g_00658c00)();
  sk_00350464();
  t6 = sk_0034c754();
  sk_00310d68(t6,t3);
  sk_003490b8(v58 + 8);
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034fdcc();
  v10 = t3;
  sk_00358208();
  (*g_00658c00)(*(undefined8 *)(eo8_02 + 0x40));
  sk_003493c4();
  sk_0034acf0();
  (*g_00658c00)();
  sk_0034aadc();
  (*g_00658c00)();
  sk_0034a1b0();
  (*g_00658c00)();
  sk_0034a9e8();
  (*g_00658c00)();
  sk_00350464();
  sk_00350908();
  sv00000008 = sk_001a0414();
  sk_000277b8(param_4);
  sk_00350b24();
  sk_003509b0();
  (*eo9)();
  v28 = *(unsigned long (**)() )(eo16_01 + 0x10);
  t9 = (ulong)(eo16_01 + 0x10) & 0xffffffffffff | 0xe3ba000000000000;
  v48 = (undefined8 *)(eo16_01 + 0x20);
  pc1 = v30 + 8;
  t7 = t4;
  v20 = eo8_03;
  while( true ) {
    pc10 = v28;
    sk_00359a78();
    sk_00351360();
    sk_0035a274();
    (*pc10)();
    sk_00027754(t7);
    sk_0014ae44();
    sk_0035066c();
    sk_00351744();
    t7 = (*eo8_04)();
    if ((t7 & 1) == 0) break;
    pc11 = (unsigned long (*)() )*v48;
    at12._0_8_ = (undefined8)(sk_00351160());
    at12._8_8_ = 0;
    (*pc11)(at12._0_8_,at12._8_8_,v10);
    sk_003489a8();
    sk_00351af8(&stk00000028);
    sk_00350bf0();
    sk_003534ec();
    sk_001d9890();
    sk_00351160();
    (*eo9_00)();
    sk_0034de8c();
    at12._0_8_ = (undefined8)(sk_00350944());
    at12._8_8_ = 0;
    t3 = sk_00377bec(at12._0_8_,at12._8_8_,vd0);
    sk_00352098(&stk00000018);
    sk_00358cec(*(undefined8 *)v58,*(undefined8 *)(v58 + 8),vd0);
    sk_001d80e0();
    pc10 = *(unsigned long (**)() )pc1;
    sk_00100c38();
    (*pc10)();
    if (rx21 != 0) {
      sk_003510d0(&stk00000010);
      (*eo8_13)(v20,v10);
L_001d9568:
      sk_0036b118(sv00000008);
L_001d9590:
      t3 = sk_00352df4();
      sk_00353d14(t3,st108);
      return;
    }
    v30 = pc11;
    at12._0_8_ = (undefined8)(sk_00351bac());
    at12._8_8_ = 0;
    sk_00350884(at12._0_8_,at12._8_8_,v10);
    t6 = v20;
    if ((bool)zr) {
      sk_003510d0(&stk00000010);
      sk_00353f44();
      (*eo8_14)();
      sk_00350bc0(v58);
      (*eo8_15)(ve0,v150);
L_001d9580:
      sk_001d9988(sv00000008,v10,t4);
      goto L_001d9590;
    }
    v18 = rx21;
    sk_003508b4();
    sk_0035a274();
    pc10 = v30;
    (*v30)();
    sk_00027754(t4);
    sk_0014ae44();
    t8 = sk_00350a40();
    sk_00351378(t8,v80);
    t7 = (*eo8_05)();
    if ((t7 & 1) == 0) break;
    sk_00353e38();
    t8 = v10;
    v38 = (unsigned long (*)() )*eo8_06;
    v40 = (ulong)eo8_06 & 0xffffffffffff | 0x4f8000000000000;
    (*v38)(t6,v10);
    at12._0_8_ = (undefined8)(sk_00350a04());
    at12._8_8_ = 0;
    (*v28)(at12._0_8_,at12._8_8_,t8);
    sk_003546a8();
    sk_0034ee98();
    (*pc10)();
    sk_003489a8();
    sk_00351af8(&stk00000008);
    at12._0_8_ = (undefined8)(sk_00351ec0());
    at12._8_8_ = 0;
    sk_001d9890(at12._0_8_,at12._8_8_,t5,param_4);
    sk_003508b4();
    (*eo9_00)();
    sk_0035179c(&stk00000000);
    sk_001d4f4c(*(undefined8 *)v58,*(undefined8 *)(v58 + 8),vd0,t3);
    if (v18 != 0) {
      (*v38)(v80,v10);
      goto L_001d9568;
    }
    sk_00310924(t3);
    sk_003562ec();
    sk_00351384();
    (*eo9_01)();
    sk_00353cf0();
    sk_00353718();
    (*eo8_07)();
    sk_00357884();
    sk_00351360();
    sk_0035a274();
    (*v28)();
    sk_00358960();
    t3 = sk_00310e20();
    sk_00351160(t3);
    sk_00352e60();
    t7 = (*eo8_08)();
    if ((t7 & 1) == 0) {
      sk_00347da8();
      goto L_001d95cc;
    }
    sk_00358bcc();
    at12._0_8_ = (undefined8)(sk_0035084c());
    at12._8_8_ = 0;
    t3 = v10;
    pc10 = v30;
    (*v30)(at12._0_8_,at12._8_8_,v10);
    sk_00359e40();
    sk_0035139c();
    (*pc10)();
    sk_003510d0(&v40);
    at12._0_8_ = (undefined8)(sk_00350914());
    at12._8_8_ = 0;
    (*eo8_09)(at12._0_8_,at12._8_8_,v120);
    iv2 = *(int *)(v120 + 0x30);
    sk_000dbf08(vb8);
    (*pc10)();
    (*v38)(v128 + iv2,t3);
    sk_003510d0(&v48);
    at12._0_8_ = (undefined8)(sk_00350914());
    at12._8_8_ = 0;
    (*eo8_10)(at12._0_8_,at12._8_8_,v120);
    (*pc10)(vb8 + *(int *)(rx26 + 0x24),v128 + *(int *)(v120 + 0x30),t3);
    sk_003508b4();
    pc10 = v38;
    (*v38)();
    sk_00350798();
    sk_00310d34();
    sk_00355c1c();
    sk_001a1854(vb8);
    sk_00310924(param_4);
    sk_0035a6e8();
    sk_00351354();
    (*eo9_02)();
    t3 = sk_0016186c(t9);
    sk_003505e8(t3);
    sk_00351b20();
    t7 = (*eo8_11)();
    sk_003504ac();
    (*pc10)();
    if ((t7 & 1) == 0) {
      sk_00356ac4();
      (*pc10)();
      t4 = t9;
      goto L_001d9580;
    }
    sk_00027818(param_4);
    sk_00350648();
    sk_00351ba0();
    (*eo8_12)();
    rx21 = 0;
    t7 = t9;
  }
  sk_00350410();
  sk_003488bc();
  sk_003593e8();
  sk_00349410();
L_001d95cc:
  sk_003504b8();
                      sk_001afe4c();
}

/* FUN_001d95f4 @ 0x001d95f4   (est. sk_r5_fatal_assert_001d95f4) */
/* Confidence: low (mechanical translation; names heuristic) */
undefined8 sk_001d95f4(ulong param_1,ulong param_2,ulong param_3)

{
  ulong t1;
  ulong t2;
  uint t3;
  sk_c16_t at4;
  
  t1 = param_2 & 0xffffffffffff;
  if ((param_3 & 0x2000000000000000) != 0) {
    t1 = param_3 >> 0x38 & 0xf;
  }
  if (param_1 >> 0xe <= t1 << 2) {
    t3 = (uint)(param_2 >> 0x3b) & 1;
    if ((param_3 & 0x1000000000000000) == 0) {
      t3 = 1;
    }
    t2 = 7;
    if (t3 == 0) {
      t2 = 0xb;
    }
    at4._0_8_ = (undefined8)(sk_002ab8ac(param_1,t2 | t1 << 0x10,param_2,param_3,0xd2,0x50));
    at4._8_8_ = 0;
    sk_t_0036b270(param_3);
    return at4._0_8_;
  }
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_requires_lowerBound__str<__upp_005cda00,0x27,2,
               Swift_Range_swift_005cda30_str,0x11,2,0x2f9,1);
}

/* FUN_001d96e0 @ 0x001d96e0   (est. sk_r5_fatal_assert_001d96e0) */
/* Confidence: low (mechanical translation; names heuristic) */
undefined8 sk_001d96e0(uint param_1,uint param_2)

{
  if (param_1 <= param_2) {
    return concat(param_1,param_2);
  }
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_requires_lowerBound__str<__upp_005cda00,0x27,2,
               Swift_Range_swift_005cda30_str,0x11,2,0x2f9,1);
}

/* FUN_001d974c @ 0x001d974c   (est. sk_r5_fatal_assert_001d974c) */
/* Confidence: low (mechanical translation; names heuristic) */
uint sk_001d974c(uint param_1,uint param_2)

{
  if (param_1 <= param_2) {
    return param_1;
  }
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Range_out_of_bounds_005cec20_str,0x13,2,
               Swift_Collection_swift_005cdad0_str,0x16,2,0x2da,1);
}

/* FUN_001d97b4 @ 0x001d97b4   (est. sk_r5_fatal_assert_001d97b4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d97b4(undefined8 param_1,undefined8 param_2,ulong param_3)

{
  ulong t1;
  undefined8 t2;
  uint eovar;
  long eo8;
  long eo8_00;
  uint t3;
  
  t1 = sk_00358ae0();
  if (t1 >> 0xe <= (ulong)(eo8 << 2)) {
    t2 = sk_00350a28();
    t3 = eovar >> 0x1b & 1;
    if ((param_3 & 0x1000000000000000) == 0) {
      t3 = 1;
    }
    t1 = 7;
    if (t3 == 0) {
      t1 = 0xb;
    }
    sk_0035053c(t2,t1 | eo8_00 << 0x10);
    sk_00354404();
    sk_002ab8ac();
    sk_00356290();
    sk_t_0036b270();
    sk_0008412c();
    return;
  }
  sk_00347d60();
                      sk_001afe4c();
}

/* FUN_001d9840 @ 0x001d9840   (est. sk_r5_fatal_assert_001d9840) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d9840(long param_1,undefined8 param_2,long param_3)

{
  if (param_3 < param_1) {
    sk_00347d60();
                        sk_001afe4c();
  }
  if (-1 < param_1) {
    return;
  }
  sk_0035047c();
  sk_003480ac();
                      sk_001afe4c();
}

/* FUN_001d9890 @ 0x001d9890   (est. sk_r5_swift_001d9890) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d9890(void)

{
  undefined8 t1;
  undefined8 ax3;
  undefined8 t2;
  undefined8 ax4;
  unsigned long (*eo8)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long eo16;
  undefined8 rx30;
  
  sk_0008e518();
  t2 = ax3;
  sk_003542d0();
  t1 = sk_0034cd7c();
  sk_00351f70(t1,t2);
  sk_00377824();
  sk_00357944();
  sk_003504ac();
  sk_00351f40();
  sk_00377bec();
  sk_0034c55c();
  sk_00310e08();
  sk_00348e60();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034af20();
  sk_0031b164(ax4);
  sk_00351184();
  sk_0034ce78();
  sk_00356b80();
  (*eo9)();
  sk_00319628(ax3);
  sk_0035133c();
  sk_00352b2c();
  sk_0035056c();
  (*eo9_00)();
  sk_00350ab8(*(undefined8 *)(eo16 + 8));
  (*eo8)();
  sk_0008e500(rx30);
  return;
}

/* FUN_001d9988 @ 0x001d9988   (est. sk_r5_swift_001d9988) */
/* Confidence: low (mechanical translation; names heuristic) */
undefined8 sk_001d9988(void)

{
  undefined8 t1;
  long rx21;
  
  sk_0034b430();
  sk_00310e08(0);
  sk_00349530();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b460();
  if (*(long *)(rx21 + 0x10) == 1) {
    sk_00350530();
    sk_0019ea20();
    sk_0036b118();
    sk_0034ba28();
    t1 = sk_00277474();
  }
  else if (*(long *)(rx21 + 0x10) == 0) {
    sk_0036b118();
    sk_0007c1c4();
    t1 = sk_0027743c();
  }
  else {
    sk_00350624();
    t1 = sk_00277ba8();
  }
  sk_0036b270();
  sk_0036b118();
  return t1;
}

/* FUN_001d9a40 @ 0x001d9a40   (est. sk_r5_swift_001d9a40) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d9a40(undefined8 param_1,undefined8 param_2)

{
  sk_00354d44(param_1,param_2,param_2);
  sk_001d8d78();
  return;
}

/* FUN_001d9a94 @ 0x001d9a94   (est. sk_r5_swift_001d9a94) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d9a94(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 t1;
  unsigned long (*eo8)();
  sk_c16_t at2;
  
  sk_003585f4();
  sk_00351a68();
  t1 = sk_00027754(param_4);
  at2._0_8_ = (undefined8)(sk_00349ea0(t1,t1));
  at2._8_8_ = 0;
  sk_00377824(at2._0_8_,at2._8_8_,param_3);
  sk_00351a44();
  sk_0014ae44();
  sk_0034ca08();
  sk_00351100();
  (*eo8)();
  sk_0035396c();
  return;
}

/* FUN_001d9b00 @ 0x001d9b00   (est. sk_r5_swift_001d9b00) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d9b00(void)

{
  sk_001d9b18();
  return;
}

/* FUN_001d9b18 @ 0x001d9b18   (est. sk_r5_swift_001d9b18) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d9b18(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined1 zr;
  undefined8 t1;
  unsigned long (*pc2)();
  unsigned long (*pc3)();
  ulong t4;
  undefined8 t5;
  undefined8 eo8;
  long eo8_00;
  undefined8 eo8_01;
  unsigned long (*pc6)();
  unsigned long (*eo8_02)();
  undefined8 eo8_03;
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  unsigned long (*eo8_06)();
  unsigned long (*eo8_07)();
  unsigned long (*eo8_08)();
  unsigned long (*eo8_09)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long n7;
  long eo13;
  long eo16;
  long rx19;
  long rx21;
  undefined8 rx22;
  unsigned long (*pc8)();
  unsigned long (*rx26)();
  undefined8 rx30;
  sk_c16_t at9;
  undefined8 v48;
  
  sk_00353cfc();
  sk_00353e50();
  sk_00352894(param_4);
  sk_00027754();
  at9._0_8_ = (undefined8)(sk_00348e30());
  at9._8_8_ = 0;
  sk_00377824(at9._0_8_,at9._8_8_,param_3);
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b708();
  sk_0034a944();
  sk_00350b48();
  sk_00377824();
  sk_0034da88();
  t1 = sk_00310d68();
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_00350428();
  n7 = *(long *)(rx19 + -8);
  (*g_00658c00)();
  (*g_00658c00)();
  sk_0034ef48();
  (*g_00658c00)();
  sk_0034baa8();
  sk_00350ad0();
  sk_001d80e0();
  if (rx21 == 0) {
    sk_00351390(eo8_01);
    sk_00350884();
    if ((bool)zr) {
      (**(unsigned long (**)() )(eo16 + 8))(eo8_01,t1);
      sk_00310924();
      sk_00350470(eo8);
      (*eo9)();
    }
    else {
      pc6 = *(unsigned long (**)() )(n7 + 0x20);
      sk_0035056c(rx22);
      (*eo8_02)();
      sk_00319658();
      sk_00351184();
      sk_00359a48(rx22);
      sk_003513b4();
      (*eo9_00)();
      pc2 = (unsigned long (*)() )sk_00310924();
      sk_0034c3c4();
      sk_0034d758();
      sk_00377bec();
      t1 = sk_00027754();
      pc3 = (unsigned long (*)() )sk_0014ae44();
      sk_00359ca4();
      while( true ) {
        sk_0034be94(eo8_00 - (eo13 + 0xfU & 0xfffffffffffffff0));
        (*pc2)();
        at9._0_8_ = (undefined8)(sk_003509b0());
        at9._8_8_ = 0;
        t4 = (*pc3)(at9._0_8_,at9._8_8_,rx19,t1);
        pc8 = *(unsigned long (**)() )(n7 + 8);
        sk_00351ec0();
        (*pc8)();
        if ((t4 & 1) != 0) break;
        sk_000277e8();
        sk_00353cb4();
        sk_00350bfc();
        pc8 = (unsigned long (*)() )(*eo8_04)();
        sk_00354f8c();
        sk_00351c88();
        (*eo8_05)();
        sk_0034c3b4();
        (*pc8)();
        t4 = (*rx26)(v48);
        sk_00354b14();
        sk_003510b8();
        (*eo8_06)();
        if ((t4 & 1) == 0) {
          t5 = sk_0031b194(param_4);
          sk_003510dc(t5);
          sk_00351280();
          (*eo8_07)();
          sk_00027818();
          sk_0034e044();
          (*eo8_08)();
        }
        sk_00027818();
        sk_00350a7c();
        sk_003513b4();
        (*eo8_09)();
      }
      (*pc8)(eo8_03);
      (*pc6)(eo8,rx22,rx19);
    }
  }
  sk_00353d14(rx30);
  return;
}

/* FUN_001d9f28 @ 0x001d9f28   (est. sk_r5_swift_001d9f28) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001d9f28(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6)

{
  undefined8 t1;
  undefined8 t2;
  undefined8 t3;
  long rx21;
  undefined8 v48;
  
  sk_00027754(param_6);
  t1 = sk_00027754();
  t1 = sk_00377824(0xff,t1,param_5,&g_00611b24,&L_00611b34);
  t1 = sk_0031de7c(0,t1);
  t2 = sk_00376820(&g_004edd08,t1);
  t3 = sk_00376820(&g_004edcec,t1);
  sk_001da324(&v48,param_3,param_4,t1,t2,t3);
  if (rx21 == 0) {
    *param_1 = v48;
  }
  return;
}

/* FUN_001da01c @ 0x001da01c   (est. sk_r5_fatal_assert_001da01c) */
/* Confidence: low (mechanical translation; names heuristic) */
ulong sk_001da01c(void (*param_1)())

{
  ulong t1;
  ulong t2;
  ulong *rx20;
  long rx21;
  long n3;
  ulong t4;
  ulong t5;
  ulong t6;
  ulong t7;
  ulong t8;
  undefined1 v52;
  undefined1 v51;
  
  t7 = rx20[1];
  t6 = t7 >> 0x38 & 0xf;
  if (t6 == 0) {
    t5 = 0;
  }
  else {
    t5 = 0;
    do {
      t8 = *rx20;
      v51 = (char)(t8 >> (t5 << 3 & 0x3f));
      if (7 < t5) {
        v51 = (char)(t7 >> (t5 << 3 & 0x38));
      }
      t1 = (*param_1)(&v51);
      if (rx21 != 0) {
        return t5;
      }
      t4 = t7 >> 0x38 & 0xf;
      if ((t1 & 1) != 0) {
        n3 = t6 - 1;
        t1 = t6 * 8 - 0x48;
        do {
          t6 = t6 - 1;
          if (((long)t6 < 0) || ((long)t4 <= n3)) goto L_001da148;
          if ((long)t6 <= (long)t5) {
            return t5;
          }
          v52 = (char)(t7 >> (t1 & 0x3f));
          if (t6 < 8) {
            v52 = (char)(t8 >> (t1 & 0x3f));
          }
          t2 = (*param_1)(&v52);
          t1 = t1 - 8;
        } while ((t2 & 1) != 0);
        sk_0019f370(t5,t6);
        t7 = rx20[1];
        t4 = t7 >> 0x38 & 0xf;
      }
      if (t4 <= t5) {
L_001da148:
                            sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Index_out_of_bounds_005cdab0_str,0x13,2,
                     Swift_Collection_swift_005cdad0_str,0x16,2,0x2ca,1);
      }
      t5 = t5 + 1;
    } while (t5 < t6);
  }
  return t5;
}

/* FUN_001da1c0 @ 0x001da1c0   (est. sk_r5_fatal_assert_001da1c0) */
/* Confidence: low (mechanical translation; names heuristic) */
long sk_001da1c0(void (*param_1)())

{
  ulong t1;
  long n2;
  long *rx20;
  long rx21;
  long n3;
  long n4;
  long n5;
  long n6;
  long n7;
  undefined1 v52;
  undefined1 v51;
  
  n4 = rx20[1];
  if (n4 < 1) {
    n3 = 0;
  }
  else {
    n3 = 0;
    n5 = *rx20;
    n7 = n4;
    do {
      if (n3 == n4) {
L_001da2dc:
                            sk_001afe4c(Fatal_error_005accd0_str,0xb,2,&g_005be7c0,0,2,
                     Swift_UnsafeBufferPointer_swift_005cdc10_str,0x1f,2,0x238,1);
      }
      v51 = *(undefined1 *)(n5 + n3);
      t1 = (*param_1)(&v51);
      if (rx21 != 0) {
        return n3;
      }
      n2 = n7;
      if ((t1 & 1) != 0) {
        do {
          n6 = n2 + -1;
          if (n6 <= n3) {
            return n3;
          }
          if (n4 < n7) goto L_001da2dc;
          v52 = *(undefined1 *)(n5 + -1 + n2);
          t1 = (*param_1)(&v52);
          n2 = n6;
        } while ((t1 & 1) != 0);
        sk_0031e4e0(n3,n6,n5,n4);
        n7 = n6;
      }
      n3 = n3 + 1;
    } while (n3 < n7);
  }
  return n3;
}

/* FUN_001da324 @ 0x001da324   (est. sk_r5_swift_001da324) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001da324(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 stk00000010;
  undefined8 stk00000030;
  undefined8 stk00000040;
  undefined8 t1;
  unsigned long (*pc2)();
  unsigned long (*pc3)();
  ulong t4;
  undefined8 t5;
  unsigned long (*pc6)();
  unsigned long (*pc7)();
  long eo8;
  long eo8_00;
  long eo8_01;
  undefined8 *eo8_02;
  unsigned long (*eo8_03)();
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  unsigned long (*eo8_06)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  unsigned long (*eo9_01)();
  undefined8 *eo10;
  long eo16;
  long rx21;
  undefined8 rx23;
  undefined8 rx24;
  unsigned long (*pc8)();
  undefined8 rx27;
  sk_c16_t at9;
  sk_c16_t at10;
  undefined8 vb8;
  
  at9._0_8_ = (undefined8)(sk_00353cfc());
  at9._8_8_ = 0;
  sk_00352b98();
  sk_00352894(param_4);
  sk_00027754();
  at10._0_8_ = (undefined8)(sk_00348e30());
  at10._8_8_ = 0;
  t1 = sk_00377824(at10._0_8_,at10._8_8_,param_3);
  sk_000a6f88();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_003493c4();
  sk_0034d254();
  (*g_00658c00)();
  sk_00350464();
  sk_0034d574();
  sk_0034c920();
  sk_00377824();
  sk_00348cd0();
  (*g_00658c00)(*(undefined8 *)(eo8_01 + 0x40));
  sk_00348a34();
  (*g_00658c00)();
  sk_0034b758();
  sk_000277b8();
  sk_0035133c();
  sk_00350618();
  (*eo9)();
  sk_00310924();
  sk_00351184();
  sk_00350618();
  (*eo9_00)();
  sk_0035284c();
  sk_00377bec();
  pc2 = (unsigned long (*)() )sk_0016186c();
  pc3 = (unsigned long (*)() )sk_0035a59c();
  do {
    sk_0035145c();
    sk_0034e434();
    t4 = (*pc2)();
    if ((t4 & 1) == 0) {
L_001da684:
      sk_003509b0();
      (*eo9_01)();
      sk_00351e9c(*(undefined8 *)(eo16 + 0x20),vb8);
      (*eo8_06)();
L_001da6f0:
      sk_00351348();
      sk_00353d14(*(undefined8 *)(eo8_00 + 0x58));
      return;
    }
    sk_000277e8(rx24);
    t5 = sk_00353cb4();
    sk_00351f1c(t5,rx23);
    at10._0_8_ = (undefined8)((*eo8_03)());
    at10._8_8_ = 0;
    pc2 = (unsigned long (*)() )*eo10;
    (*pc2)(eo8_00,at10._8_8_,t1);
    sk_0034c3b4();
    (*at10._0_8_)();
    (*at9._0_8_)(eo8_00);
    sk_00358ea0();
    pc8 = (unsigned long (*)() )*eo8_02;
    sk_003504c4();
    (*pc8)();
    if (rx21 != 0) {
      pc2 = *(unsigned long (**)() )(eo16 + 8);
      sk_00351414();
      (*pc2)();
      (*pc2)(rx23,rx27);
      goto L_001da6f0;
    }
    if ((at9._8_8_ & 1) != 0) {
      pc6 = (unsigned long (*)() )sk_003196e8(param_4);
      do {
        (*pc6)();
        t4 = (*pc3)(rx23);
        if ((t4 & 1) == 0) goto L_001da684;
        at10._0_8_ = (undefined8)(sk_00355634());
        at10._8_8_ = 0;
        pc7 = (unsigned long (*)() )(*eo8_03)(at10._0_8_,at10._8_8_,param_3,rx24);
        at10._0_8_ = (undefined8)(sk_0035a590());
        at10._8_8_ = 0;
        (*pc2)(at10._0_8_,at10._8_8_,t1);
        sk_0034c3b4();
        (*pc7)();
        (*at9._0_8_)(param_3);
        sk_00358ea0();
        sk_003504c4();
        (*pc8)();
      } while ((at9._8_8_ & 1) != 0);
      sk_00352b8c(&stk00000040);
      t5 = sk_0031b194();
      sk_0035145c(t5);
      sk_00351f1c();
      (*eo8_04)();
    }
    sk_00027818(rx24);
    sk_003505d0();
    sk_0035139c();
    (*eo8_05)();
    pc2 = pc3;
  } while( true );
}

/* FUN_001da714 @ 0x001da714   (est. sk_r5_fatal_assert_001da714) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001da714(undefined8 param_1,undefined8 param_2,void (*param_3)(),undefined8 param_4,
                 undefined8 param_5,undefined8 param_6)

{
  int iv1;
  long n2;
  undefined8 t3;
  long n4;
  undefined8 t5;
  long n6;
  undefined8 t7;
  ulong t8;
  long n9;
  long n10;
  undefined8 eo8;
  long eo8_00;
  long eo8_01;
  long eo8_02;
  undefined1 *eo8_03;
  unsigned long (*pc11)();
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  unsigned long (*eo8_06)();
  long eo8_07;
  unsigned long (*eo8_08)();
  unsigned long (*eo8_09)();
  unsigned long (*eo8_10)();
  unsigned long (*eo8_11)();
  unsigned long (*eo8_12)();
  unsigned long (*eo8_13)();
  unsigned long (*eo8_14)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  unsigned long (*eo9_01)();
  unsigned long (*eo11)();
  long eo12;
  long eo13;
  undefined8 eo14;
  long eo16;
  long eo16_00;
  long rx21;
  long rx23;
  unsigned long (*pc12)();
  unsigned long (*pc13)();
  sk_c16_t at14;
  sk_c16_t at15;
  unsigned long (*v100)();
  undefined8 vf8;
  long v50;
  
  at14._0_8_ = (undefined8)(sk_00353cfc());
  at14._8_8_ = 0;
  n9 = at14._8_8_;
  n2 = at14._0_8_;
  sk_00351ad4(param_6);
  sk_00352304();
  sk_00351118();
  t3 = sk_00377824();
  sk_0034b0b4();
  sk_00352360();
  n4 = sk_003722e4();
  sk_000a6f88();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_00348bbc();
  (*g_00658c00)();
  sk_0034ae58();
  sk_0035626c();
  sk_0035139c();
  t5 = sk_00377bec();
  at14._0_8_ = (undefined8)(sk_00350488());
  at14._8_8_ = 0;
  sk_00310e08(at14._0_8_,at14._8_8_,t5);
  sk_000a6f88();
  (*g_00658c00)(*(undefined8 *)(eo8_01 + 0x40));
  sk_0034ab10();
  sk_00350ec0();
  (*g_00658c00)();
  sk_0034bd30();
  (*g_00658c00)();
  n10 = (long)&v100 - eo12;
  sk_003499f0();
  (*g_00658c00)(*(undefined8 *)(eo8_02 + 0x40));
  sk_00348abc();
  (*g_00658c00)();
  (*g_00658c00)();
  sk_0034b308();
  (*g_00658c00)();
  (*g_00658c00)();
  at14._0_8_ = (undefined8)(sk_00350464());
  at14._8_8_ = 0;
  n6 = at14._0_8_;
  if (n2 == 1) {
    t8 = (*param_3)(n9);
    if (rx21 != 0) goto L_001dad10;
    if ((t8 & 1) == 0) {
      (**(unsigned long (**)() )(eo16_00 + 0x10))(eo8,n9 + *(int *)(n6 + 0x24),t3);
      goto L_001dad10;
    }
    pc11 = *(unsigned long (**)() )(eo16_00 + 0x10);
  }
  else {
    if (n2 != 0) {
      vf8 = eo14;
      sk_0031afcc();
      sk_00351250();
      (*eo9)(n9,n2 / 2,param_5);
      at15._0_8_ = (undefined8)(sk_00350944(*(undefined8 *)(eo16_00 + 0x10)));
      at15._8_8_ = 0;
      (*eo8_04)(at15._0_8_,at15._8_8_,t3);
      sk_00310e20(t5);
      t7 = sk_00350a40();
      sk_003516b4(t7,eo8_03);
      t8 = (*eo8_05)();
      if ((t8 & 1) == 0) {
        sk_0034b348();
        sk_0035a4d4();
        *eo8_03 = 2;
      }
      else {
        pc11 = *(unsigned long (**)() )(eo16_00 + 0x20);
        sk_0035100c();
        (*pc11)();
        t7 = sk_003595a8();
        (*eo8_04)(t7,eo8_03,t3);
        sk_00352a40();
        at15._0_8_ = (undefined8)(sk_00350524());
        at15._8_8_ = 0;
        sk_00352f88(at15._0_8_,at15._8_8_,n4);
        (*eo9_00)();
        iv1 = *(int *)(n4 + 0x30);
        sk_0034fed0();
        (*pc11)();
        pc13 = *(unsigned long (**)() )(eo16_00 + 8);
        (*pc13)(rx23 + iv1,t3);
        at15._0_8_ = (undefined8)(sk_00350524(*(undefined8 *)(eo16 + 0x20)));
        at15._8_8_ = 0;
        sk_00352554(at15._0_8_,at15._8_8_,n4);
        (*eo8_06)();
        sk_00357f94((long)*(int *)(n4 + 0x30));
        (*pc11)();
        sk_003504c4();
        (*pc13)();
        sk_003583c0(at14._8_8_);
        pc12 = *(unsigned long (**)() )(eo13 + 8);
        sk_00350a04();
        (*pc12)();
        if (rx21 != 0) {
          (*pc13)(eo8_03,t3);
          goto L_001dad10;
        }
        sk_00355068();
        v100 = pc12;
        t7 = sk_00354134();
        if (ovf(eo8_07,n2 / 2)) {
                              pc11 = (unsigned long (*)() )sk_breakpoint(1,0x1dae9c);
          (*pc11)();
        }
        at15._0_8_ = (undefined8)(sk_00352d64(&stk00000010,t7,n9 + *(int *)(n6 + 0x24)));
        at15._8_8_ = 0;
        (*eo11)(at15._0_8_,at15._8_8_,t3);
        t7 = sk_00310e20(t5);
        sk_00350914(t7);
        sk_00350db4();
        t8 = (*eo8_08)();
        if ((t8 & 1) != 0) {
          sk_000dbf08(v50);
          (*eo11)();
          sk_00351420(v50 + *(int *)(n4 + 0x30));
          (*pc11)();
          at15._0_8_ = (undefined8)(sk_00350aa0());
          at15._8_8_ = 0;
          sk_00353734(at15._0_8_,at15._8_8_,n4);
          (*eo8_09)();
          iv1 = *(int *)(n4 + 0x30);
          sk_00354b68();
          sk_0034fed0();
          (*pc11)();
          (*pc13)(rx23 + iv1,t3);
          at15._0_8_ = (undefined8)(sk_00350aa0());
          at15._8_8_ = 0;
          sk_00353718(at15._0_8_,at15._8_8_,n4);
          (*eo8_10)();
          sk_00357f94((long)*(int *)(n4 + 0x30));
          (*pc11)();
          sk_003504c4();
          (*pc13)();
          sk_00352f48(&stk00000030);
          sk_003583c0();
          sk_00352bbc(n10,n6);
          (*eo8_11)();
          t5 = sk_00310e20(t5);
          sk_00351b20(t5,at14._8_8_,pc11);
          t8 = (*eo8_12)();
          if ((t8 & 1) != 0) {
            at14._0_8_ = (undefined8)(sk_000dbd0c());
            at14._8_8_ = 0;
            (*pc11)(at14._0_8_,at14._8_8_,t3);
            sk_000dbf08(v50 + *(int *)(n4 + 0x30));
            (*pc11)();
            at14._0_8_ = (undefined8)(sk_00350aa0());
            at14._8_8_ = 0;
            sk_00353734(at14._0_8_,at14._8_8_,n4);
            (*eo8_13)();
            iv1 = *(int *)(n4 + 0x30);
            sk_0034fed0();
            (*pc11)();
            (*pc13)(rx23 + iv1,t3);
            at14._0_8_ = (undefined8)(sk_00350aa0());
            at14._8_8_ = 0;
            sk_00353718(at14._0_8_,at14._8_8_,n4);
            (*eo8_14)();
            sk_00357f94((long)*(int *)(n4 + 0x30));
            (*pc11)();
            sk_003504c4();
            (*pc13)();
            sk_001daea8(eo8,vf8,eo8_03,param_5,param_6);
            sk_00350ea4();
            sk_00358624((ulong)(eo13 + 8) & 0xffffffffffff | 0x4f8000000000000);
            (*eo9_01)();
            sk_003504c4();
            (*pc13)();
            goto L_001dad10;
          }
        }
        sk_00350410();
        sk_00351088();
        *eo8_03 = 2;
      }
      sk_003494d4();
      sk_00349410();
      sk_003504b8();
                          sk_001afe4c();
    }
    pc11 = *(unsigned long (**)() )(eo16_00 + 0x10);
  }
  (*pc11)(eo8,n9,t3);
L_001dad10:
  sk_00351348();
  sk_00353d14(*(undefined8 *)(eo8_03 + 0x58));
  return;
}

/* FUN_001daea8 @ 0x001daea8   (est. sk_r5_fatal_assert_001daea8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001daea8(void)

{
  undefined8 stk00000020;
  int iv1;
  undefined8 *pt2;
  undefined8 t3;
  long n4;
  undefined8 t5;
  undefined8 t6;
  ulong t7;
  undefined8 ax3;
  undefined8 eo8;
  long eo8_00;
  long eo8_01;
  long eo8_02;
  unsigned long (*eo8_03)();
  undefined8 *pt8;
  unsigned long (*eo8_04)();
  unsigned long (*eo8_05)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long eo16;
  long eo16_00;
  undefined8 rx19;
  unsigned long (*pc9)();
  unsigned long (*pc10)();
  unsigned long (*pc11)();
  unsigned long (*pc12)();
  long rx22;
  undefined8 *pt13;
  undefined8 rx26;
  long rx27;
  undefined8 rx30;
  sk_c16_t at14;
  sk_c16_t at15;
  undefined8 vd8;
  long vd0;
  undefined8 vb0;
  long va8;
  undefined8 v98;
  long v58;
  undefined *v28;
  undefined8 *v20;
  unsigned long (*v18)();
  undefined8 v10;
  
  at14._0_8_ = (undefined8)(sk_0008e518());
  at14._8_8_ = 0;
  v10 = at14._8_8_;
  sk_00350950(ax3);
  sk_00352304();
  sk_003510f4();
  t3 = sk_00377824();
  sk_0034b0b4();
  sk_00355adc();
  n4 = sk_003722e4();
  sk_000a6f88();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_0034926c();
  (*g_00658c00)();
  sk_00350464();
  sk_003557a8();
  sk_0035626c();
  sk_0035678c();
  sk_00350b18();
  t5 = sk_00377bec();
  at15._0_8_ = (undefined8)(sk_00350720());
  at15._8_8_ = 0;
  sk_00310e08(at15._0_8_,at15._8_8_,t5);
  sk_00348ce8();
  (*g_00658c00)(*(undefined8 *)(eo8_01 + 0x40));
  sk_003493c4();
  sk_0034acf0();
  (*g_00658c00)();
  sk_0034aa14();
  sk_00349c70();
  (*g_00658c00)(*(undefined8 *)(eo8_02 + 0x40));
  sk_003493c4();
  sk_0034da38();
  (*g_00658c00)();
  sk_0034aadc();
  (*g_00658c00)();
  sk_0034a9c0();
  (*g_00658c00)();
  sk_0034a1c8();
  (*g_00658c00)();
  sk_00350434();
  sk_0034acf0();
  (*g_00658c00)();
  sk_0034a464();
  (*g_00658c00)();
  sk_0034ba78();
  (*g_00658c00)();
  sk_0034c2c8();
  pt13 = (undefined8 *)(eo16_00 + 0x10);
  pc10 = (unsigned long (*)() )*pt13;
  at15._0_8_ = (undefined8)(sk_00355d28());
  at15._8_8_ = 0;
  (*pc10)(at15._0_8_,at15._8_8_,t3);
  at15._0_8_ = (undefined8)(sk_0035145c());
  at15._8_8_ = 0;
  t6 = (*pc10)(at15._0_8_,at15._8_8_,t3);
  sk_00355b04(t6,at14._0_8_ + (long)*(int *)(rx22 + 0x24));
  v20 = pt13;
  v18 = pc10;
  (*pc10)();
  sk_00352894(t5);
  pc10 = (unsigned long (*)() )sk_0014ae44();
  sk_00350524();
  v10 = t3;
  sk_003516d8();
  t7 = (*pc10)();
  if ((t7 & 1) == 0) {
    t7 = (*pc10)();
    if ((t7 & 1) == 0) {
      v28 = &g_0060e208;
      t7 = (ulong)v20 & 0xffffffffffff;
      (*v18)(eo8,rx26,v10);
      pt8 = (undefined8 *)(eo16_00 + 8U & 0xffffffffffff | 0x4f8000000000000);
      v20 = (undefined8 *)(t7 | 0xe3ba000000000000);
      while( true ) {
        pt2 = v20;
        at14._0_8_ = (undefined8)(sk_00354d14());
        at14._8_8_ = 0;
        pc9 = v18;
        (*v18)(at14._0_8_,at14._8_8_,v10);
        sk_00350968(v98);
        (*pc9)();
        sk_00310e20(t5);
        sk_00350104();
        sk_00350aac();
        t7 = (*eo8_04)();
        if ((t7 & 1) == 0) break;
        pc9 = *(unsigned long (**)() )(eo16_00 + 0x20);
        at14._0_8_ = (undefined8)(sk_00350a34());
        at14._8_8_ = 0;
        t3 = v10;
        (*pc9)(at14._0_8_,at14._8_8_,v10);
        sk_00352858(rx27 + *(int *)(n4 + 0x30));
        (*pc9)();
        sk_00353e38();
        sk_00350e54();
        (*eo9)();
        iv1 = *(int *)(n4 + 0x30);
        at14._0_8_ = (undefined8)(sk_00350c2c());
        at14._8_8_ = 0;
        (*pc9)(at14._0_8_,at14._8_8_,t3);
        sk_00354bb0();
        pc11 = (unsigned long (*)() )*pt2;
        (*pc11)(va8 + iv1,t3);
        sk_00352bbc();
        sk_00350e54();
        (*eo9_00)();
        (*pc9)(v58 + *(int *)(rx22 + 0x24),va8 + *(int *)(n4 + 0x30),t3);
        sk_00351360();
        (*pc11)();
        (*v18)(vb0,rx19,t3);
        sk_0034f014();
        sk_0035a3dc();
        sk_00351f4c();
        t7 = (*eo8_05)();
        t3 = v10;
        if ((t7 & 1) == 0) break;
        (*pc11)(v28,v10);
        at14._0_8_ = (undefined8)(sk_00350944());
        at14._8_8_ = 0;
        (*pc9)(at14._0_8_,at14._8_8_,t3);
        sk_00351bd4(rx27 + *(int *)(n4 + 0x30));
        (*v18)(v20);
        at14._0_8_ = (undefined8)(sk_00351354());
        at14._8_8_ = 0;
        (*eo9)(eo16 + 0x10U & 0xffffffffffff | 0xe3ba000000000000,at14._0_8_,
                       at14._8_8_,n4);
        iv1 = *(int *)(n4 + 0x30);
        at14._0_8_ = (undefined8)(sk_00350c2c());
        at14._8_8_ = 0;
        (*pc9)(at14._0_8_,at14._8_8_,t3);
        (*pc11)(va8 + iv1,t3);
        at14._0_8_ = (undefined8)(sk_00351354());
        at14._8_8_ = 0;
        sk_003570f0(at14._0_8_,at14._8_8_,n4);
        (*eo9_00)();
        (*pc9)(vd0 + *(int *)(rx22 + 0x24),va8 + *(int *)(n4 + 0x30),t3);
        sk_00351360();
        (*pc11)();
        t3 = sk_00353124(&stk00000020);
        sk_00350974(t3,vd8);
        sk_00257f8c();
        sk_003589cc();
        pc12 = (unsigned long (*)() )*pt8;
        (*pc12)(vd0,rx22);
        sk_003510ac();
        (*pc12)();
        sk_00351f4c(vd8,rx26);
        t7 = (*pc10)();
        pc12 = v18;
        if ((t7 & 1) != 0) {
          t7 = (*pc10)(eo8,rx26,v10,pt13);
          if ((t7 & 1) != 0) {
            t3 = sk_00354b50(&v28);
            (*pc11)(pt8,t3,v10);
            sk_0034ef68();
            (*pc12)(v20);
          }
          at14._0_8_ = (undefined8)(sk_0035190c());
          at14._8_8_ = 0;
          t7 = (*pc10)(at14._0_8_,at14._8_8_,v10,pt13);
          if ((t7 & 1) != 0) {
            (*pc11)(vd8,v10);
            sk_00084180();
            (*pc11)();
            sk_00354594();
            (*pc11)();
            sk_003508cc();
            (*pc11)();
            goto L_001db688;
          }
        }
        at14._0_8_ = (undefined8)(sk_0006b6f4());
        at14._8_8_ = 0;
        (*pc9)(at14._0_8_,at14._8_8_,v10);
        sk_003530f4();
        sk_00351b20();
        t7 = (*pc10)();
        t3 = v10;
        if ((t7 & 1) == 0) {
          sk_00353f44();
          (*pc11)(pt8);
        }
        else {
          (*pc11)(pt8,rx19,v10);
          at14._0_8_ = (undefined8)(sk_003508f0());
          at14._8_8_ = 0;
          (*pc9)(at14._0_8_,at14._8_8_,t3);
        }
      }
      sk_00347d60();
                          sk_001afe4c();
    }
    pc10 = *(unsigned long (**)() )(eo16_00 + 8);
    (*pc10)(rx26,v10);
    sk_003510b8();
    (*pc10)();
    at14._0_8_ = (undefined8)(sk_00350768(*(undefined8 *)(eo16_00 + 0x20),eo8));
    at14._8_8_ = 0;
    rx26 = at14._8_8_;
    t3 = at14._0_8_;
    pc10 = eo8_03;
  }
  else {
    pc10 = *(unsigned long (**)() )(eo16_00 + 8);
    (*pc10)(&g_0060e208,v10);
    sk_003504ac();
    (*pc10)();
    pc10 = *(unsigned long (**)() )(eo16_00 + 0x20);
    t3 = eo8;
  }
  (*pc10)(t3,rx26);
L_001db688:
  sk_0008e500(rx30);
  return;
}

/* FUN_001db6b0 @ 0x001db6b0   (est. sk_r5_swift_001db6b0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001db6b0(void)

{
  undefined8 t1;
  ulong t2;
  unsigned long (*pc3)();
  undefined8 t4;
  unsigned long (*pc5)();
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo8_02)();
  unsigned long (*eo9)();
  long eo16;
  long eo16_00;
  undefined8 rx20;
  long rx21;
  ulong t6;
  undefined8 rx23;
  undefined8 rx24;
  undefined8 rx26;
  sk_c16_t at7;
  undefined1 ast20 [32];
  
  sk_00353cfc();
  at7._0_8_ = (undefined8)(sk_003545ac());
  at7._8_8_ = 0;
  sk_00354db8();
  t1 = sk_00027754();
  sk_00349ea0(t1,t1);
  sk_00377824();
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034aee4();
  sk_00348d94();
  sk_00350b18();
  sk_00377824();
  t1 = sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b0d4();
  sk_00027788();
  sk_0034bddc();
  t2 = (*eo8)();
  pc3 = (unsigned long (*)() )sk_000277b8();
  (*pc3)();
  do {
    if ((long)t2 < 1) {
L_001db920:
      sk_00351348();
      sk_00353d14(rx20);
      return;
    }
    t6 = t2 >> 1;
    sk_003578a8();
    sk_0031afcc();
    sk_0035102c();
    sk_00350bfc(rx23,t6);
    (*eo9)();
    t4 = sk_000277e8(rx24);
    sk_00350bfc(t4,ast20);
    pc3 = (unsigned long (*)() )(*eo8_00)();
    sk_0035a19c(*(undefined8 *)(eo16 + 0x10),rx26);
    (*eo8_01)();
    sk_0034cfa4();
    (*pc3)();
    (*at7._0_8_)(rx26);
    sk_00358ea0();
    sk_00354bbc();
    sk_000e72b0();
    (*eo8_02)();
    pc3 = *(unsigned long (**)() )(eo16_00 + 8U);
    if (rx21 != 0) {
      (*pc3)();
      (*pc3)(rx23,t1);
      goto L_001db920;
    }
    if ((at7._8_8_ & 1) == 0) {
      (*pc3)(rx23,t1);
      sk_00358bc0();
      pc5 = (unsigned long (*)() )sk_00319658();
      (*pc5)(rx23);
      sk_003508f0();
      (*pc3)();
      t2 = t2 + ~t6;
      rx24 = 0;
    }
    else {
      (*pc3)(eo16_00 + 8U & 0xffffffffffff | 0x4f8000000000000);
      t2 = t6;
    }
  } while( true );
}

/* FUN_001db938 @ 0x001db938   (est. sk_r5_swift_001db938) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001db938(void)

{
  undefined8 t1;
  undefined8 t2;
  undefined8 eo1;
  long eo8;
  unsigned long (*eo8_00)();
  long eo12;
  undefined8 rx30;
  undefined8 v8;
  
  sk_00084220();
  sk_00355544();
  sk_00357788();
  sk_00349b3c();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348f50();
  sk_00350eec(*(undefined8 *)(eo12 + 0x10));
  (*eo8_00)();
  sk_003497a0();
  sk_003513b4();
  sk_00377824();
  sk_003515a8();
  sk_00352ae4();
  v8 = sk_0019e578();
  sk_00350798();
  t1 = sk_00310d80();
  t2 = sk_00349910();
  sk_00376820(t2,t1);
  t2 = sk_0034e4b4();
  sk_00376820(t2,t1);
  sk_0034c6b4();
  sk_001dba34();
  sk_003488f4();
  t1 = sk_0019e578(&v8,eo1,t1);
  sk_00084234(t1,rx30);
  return;
}

/* FUN_001dba34 @ 0x001dba34   (est. sk_r5_swift_001dba34) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dba34(void)

{
  bool bv1;
  undefined8 t2;
  unsigned long (*pc3)();
  long n4;
  ulong t5;
  undefined8 ax3;
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long eo16;
  undefined8 rx22;
  undefined8 rx25;
  undefined8 rx26;
  undefined8 rx30;
  sk_c16_t at6;
  undefined8 v18;
  ulong st10;
  undefined1 v8 [8];
  
  t2 = sk_0008e518();
  sk_0035125c(ax3);
  sk_00349748();
  sk_00352370();
  sk_00377824();
  sk_00348e60();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_003493c4();
  sk_003503f8();
  (*g_00658c00)();
  sk_0034b3d8();
  pc3 = (unsigned long (*)() )sk_00027788();
  sk_003508b4();
  n4 = (*pc3)();
  if (1 < n4) {
    sk_003508b4();
    t5 = (*pc3)();
    sk_0034f1e0();
    sk_003508b4();
    (*eo9)();
    if ((long)t5 < 2) {
      pc3 = *(unsigned long (**)() )(eo16 + 8);
    }
    else {
      sk_0031affc();
      do {
        v18 = 0;
        st10 = t5;
        sk_003516fc(v8,&v18,t2);
        sk_001d36e8();
        sk_003589d8();
        sk_0031b1c4();
        sk_00351184();
        sk_00100c38();
        sk_00353ef0();
        (*eo9_00)();
        sk_00354780();
        sk_0031b194();
        sk_0034e60c();
        sk_00354300();
        (*eo8_00)();
        pc3 = *(unsigned long (**)() )(eo16 + 8);
        sk_0035a3dc();
        (*pc3)();
        sk_00027818(rx22);
        at6._0_8_ = (undefined8)(sk_0034f4d4());
        at6._8_8_ = 0;
        (*eo8_01)(at6._0_8_,at6._8_8_,rx22);
        bv1 = 2 < t5;
        t5 = t5 - 1;
      } while (bv1);
    }
    (*pc3)(rx25,rx26);
  }
  sk_0008e500(rx30);
  return;
}

/* FUN_001dbc14 @ 0x001dbc14   (est. sk_r5_swift_001dbc14) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dbc14(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 t1;
  undefined8 eo16;
  
  t1 = sk_00353254();
  sk_001db938(t1,t1,param_3,param_4,eo16);
  return;
}

/* FUN_001dbc64 @ 0x001dbc64   (est. sk_r5_swift_001dbc64) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dbc64(void)

{
  unsigned long (*pc1)();
  undefined8 t2;
  undefined8 ax4;
  long eo8;
  unsigned long (*eo8_00)();
  long eo16;
  undefined8 rx30;
  
  sk_0008e518();
  sk_0034d6d8();
  sk_0034a980();
  sk_00377824();
  sk_00348e00();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348a18();
  (*g_00658c00)();
  sk_0034ba68();
  pc1 = (unsigned long (*)() )sk_0007b384();
  sk_00350518();
  (*pc1)();
  sk_00356a44();
  sk_00350518();
  (*pc1)();
  sk_0014ae44(ax4);
  sk_0034ce68();
  sk_0034d344();
  (*eo8_00)();
  pc1 = *(unsigned long (**)() )(eo16 + 8);
  sk_003507d4();
  (*pc1)();
  sk_003508a8();
  (*pc1)();
  t2 = sk_00353034();
  sk_0008e500(t2,rx30);
  return;
}

/* FUN_001dbd68 @ 0x001dbd68   (est. sk_r5_swift_001dbd68) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dbd68(void)

{
  uint t1;
  unsigned long (*pc2)();
  undefined8 ax4;
  long eo8;
  unsigned long (*eo8_00)();
  long eo16;
  undefined8 rx30;
  
  sk_0008e518();
  sk_0034d6d8();
  sk_0034a980();
  sk_00377824();
  sk_00348e00();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348a18();
  (*g_00658c00)();
  sk_0034ba68();
  pc2 = (unsigned long (*)() )sk_0007b384();
  sk_00350518();
  (*pc2)();
  sk_00356a44();
  sk_00350518();
  (*pc2)();
  sk_0014ae44(ax4);
  sk_0034ce68();
  sk_0034d344();
  t1 = (*eo8_00)();
  pc2 = *(unsigned long (**)() )(eo16 + 8);
  sk_003507d4();
  (*pc2)();
  sk_003508a8();
  (*pc2)();
  sk_0008e500((t1 ^ 0xffffffff) & 1,rx30);
  return;
}

/* FUN_001dbe74 @ 0x001dbe74   (est. sk_r5_swift_001dbe74) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dbe74(void)

{
  uint t1;
  undefined8 t2;
  unsigned long (*pc3)();
  undefined8 ax4;
  undefined8 ax5;
  long eo8;
  unsigned long (*eo8_00)();
  long eo16;
  undefined8 rx30;
  
  sk_0008e518();
  sk_00352fd4();
  t2 = sk_0034a980();
  sk_00377824(t2,ax4);
  sk_00348e00();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348a18();
  (*g_00658c00)();
  sk_0034ba68();
  pc3 = (unsigned long (*)() )sk_0007b384(ax4);
  sk_00350518();
  (*pc3)();
  sk_00356a44();
  sk_00350518();
  (*pc3)();
  sk_0014ae44(ax5);
  sk_0034ce68();
  sk_0034d344();
  t1 = (*eo8_00)();
  pc3 = *(unsigned long (**)() )(eo16 + 8);
  sk_003507d4();
  (*pc3)();
  sk_003508a8();
  (*pc3)();
  sk_0008e500((t1 ^ 0xffffffff) & 1,rx30);
  return;
}

/* FUN_001dbf84 @ 0x001dbf84   (est. sk_r5_swift_001dbf84) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dbf84(ulong param_1)

{
  sk_t_002298d4(*(undefined8 *)(&g_004f2670 + (param_1 & 0xff) * 8));
  sk_001a8564();
  return;
}

/* FUN_001dbffc @ 0x001dbffc   (est. sk_r5_swift_001dbffc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dbffc(void)

{
  undefined1 t1;
  byte eob0;
  
  sk_00348c48();
  t1 = sk_00351ca0(eob0,uespemosmodnarodarenegylsetybdet_004e7a30_str._16_8_,
                       eob0 ^ (byte)uespemosmodnarodarenegylsetybdet_004e7a30_str._0_8_);
  sk_t_002298d4(t1);
  sk_001a8564();
  return;
}

/* FUN_001dc050 @ 0x001dc050   (est. sk_r5_swift_001dc050) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc050(void)

{
  byte bv1;
  
  bv1 = sk_00348c48();
  sk_0034ec48(bv1,uespemosmodnarodarenegylsetybdet_004e7a30_str._16_8_,
               bv1 ^ (byte)uespemosmodnarodarenegylsetybdet_004e7a30_str._0_8_);
  sk_00229a3c();
  sk_001a8564();
  return;
}

/* FUN_001dc09c @ 0x001dc09c   (est. sk_r5_swift_001dc09c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc09c(void)

{
  unsigned long (*jumptable)();
  
  sk_0034f664();
  jumptable = (unsigned long (*)() )sk_0031948c();
  sk_0034bec4();
                                          (*jumptable)();
  return;
}

/* FUN_001dc0fc @ 0x001dc0fc   (est. sk_r5_thunk_to_001dc0fc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc0fc(undefined8 param_1,ulong param_2)

{
  sk_t_002298d4(*(undefined8 *)(&g_004f2670 + (param_2 & 0xff) * 8));
  return;
}

/* FUN_001dc130 @ 0x001dc130   (est. sk_r5_swift_001dc130) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc130(void)

{
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo9)();
  undefined8 rx30;
  
  sk_00084220();
  sk_00352700();
  sk_0035089c();
  sk_0034a980();
  sk_003511d8();
  sk_00377824();
  sk_00348d4c();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034aee4();
  sk_0007b384();
  sk_00350b24();
  sk_00100efc();
  (*eo9)();
  sk_0031945c();
  sk_003505d0();
  sk_003508d8();
  (*eo8)();
  sk_0034c9f8();
  (*eo8_00)();
  sk_00084234(rx30);
  return;
}

/* FUN_001dc1f4 @ 0x001dc1f4   (est. sk_r5_swift_001dc1f4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc1f4(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  unsigned long (*jumptable)();
  
  sk_00349ef4();
  jumptable = (unsigned long (*)() )sk_0031b1f4(param_3);
  sk_0034b128();
                                          (*jumptable)();
  return;
}

/* FUN_001dc23c @ 0x001dc23c   (est. sk_r5_swift_001dc23c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc23c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5)

{
  unsigned long (*eo9)();
  undefined8 v40;
  undefined8 st38;
  
  v40 = param_2;
  st38 = param_3;
  sk_0035125c(param_5);
  sk_0031b1f4();
  sk_00351190(param_1,&v40);
  (*eo9)();
  return;
}

/* FUN_001dc298 @ 0x001dc298   (est. sk_r5_swift_001dc298) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc298(long param_1)

{
  ulong t1;
  undefined8 t2;
  undefined8 *rx20;
  
  t2 = *(undefined8 *)(param_1 + 0x10);
  sk_003504e8();
  sk_00310dd8();
  t1 = sk_0019e5ec();
  if ((t1 & 1) == 0) {
    t2 = sk_0019e66c(*rx20,t2);
    *rx20 = t2;
  }
  return;
}

/* FUN_001dc2ec @ 0x001dc2ec   (est. sk_r5_fatal_assert_001dc2ec) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc2ec(void)

{
  sk_00348304();
                      sk_001afe4c();
}

/* FUN_001dc304 @ 0x001dc304   (est. sk_r5_fatal_assert_001dc304) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc304(long param_1,long param_2)

{
  if (*(long *)(param_2 + 0x10) < param_1) {
    sk_003488bc(1);
    sk_0034ae30();
  }
  else {
    if (-1 < param_1) {
      return;
    }
    sk_003488bc(1);
    sk_0034ae30();
  }
  sk_00353b34();
                      sk_001afe4c();
}

/* FUN_001dc3b8 @ 0x001dc3b8   (est. sk_r5_swift_001dc3b8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc3b8(undefined8 param_1,long param_2)

{
  sk_00357874(*(undefined1 *)(*(long *)(param_2 + -8) + 0x50));
  return;
}

/* FUN_001dc3e8 @ 0x001dc3e8   (est. sk_r5_swift_001dc3e8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc3e8(void)

{
  undefined8 t1;
  unsigned long (*ax3)();
  undefined8 *rx21;
  
  sk_003530e8();
  sk_00356834();
  sk_00310dd8();
  sk_00349f08();
  t1 = (*ax3)();
  *rx21 = t1;
  return;
}

/* FUN_001dc430 @ 0x001dc430   (est. sk_r5_fatal_assert_001dc430) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc430(undefined8 param_1,ulong param_2,long param_3,long param_4)

{
  long n1;
  
  if ((-1 < (long)param_2) && (param_2 < *(ulong *)(param_3 + 0x10))) {
    n1 = *(long *)(param_4 + -8);
                                            (**(unsigned long (**)() )(n1 + 0x10))
              (param_1,param_3 + ((ulong)*(byte *)(n1 + 0x50) + 0x20 &
                                 ((ulong)*(byte *)(n1 + 0x50) ^ 0xffffffffffffffff)) +
                       *(long *)(n1 + 0x48) * param_2);
    return;
  }
  sk_00348304();
                      sk_001afe4c();
}

/* FUN_001dc4c0 @ 0x001dc4c0   (est. sk_r5_swift_001dc4c0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc4c0(undefined8 param_1,undefined8 param_2,undefined8 param_3,void (*param_4)(),
                 void (*param_5)())

{
  long eo16;
  long *rx20;
  long n1;
  long rx21;
  undefined8 t2;
  long rx22;
  sk_c16_t at3;
  
  sk_0034b318();
  (*param_4)(param_3);
  n1 = *rx20;
  t2 = *(undefined8 *)(rx21 + 0x10);
  at3._0_8_ = (undefined8)(sk_003509bc());
  at3._8_8_ = 0;
  (*param_5)(at3._0_8_,at3._8_8_,t2);
  sk_003511e4();
                                          (**(unsigned long (**)() )(eo16 + 0x28))
            (n1 + ((ulong)*(byte *)(eo16 + 0x50) + 0x20 &
                     ((ulong)*(byte *)(eo16 + 0x50) ^ 0xffffffffffffffff)) +
             *(long *)(eo16 + 0x48) * rx22);
  return;
}

/* FUN_001dc554 @ 0x001dc554   (est. sk_r5_swift_001dc554) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc554(void)

{
  sk_001dc56c();
  return;
}

/* FUN_001dc56c @ 0x001dc56c   (est. sk_r5_swift_001dc56c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc56c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 void (*param_5)())

{
  undefined8 t1;
  unsigned long (*rx19)();
  
  t1 = sk_0034b13c();
  (*param_5)(t1,param_3);
  sk_00100efc();
  (*rx19)();
  sk_0034b508();
  sk_0019ec24();
  return;
}

/* FUN_001dc5c4 @ 0x001dc5c4   (est. sk_r5_swift_001dc5c4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc5c4(void)

{
  undefined8 stk00000040;
  sk_001dc620();
  return;
}

/* FUN_001dc620 @ 0x001dc620   (est. sk_r5_fatal_assert_001dc620) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc620(undefined8 param_1,undefined8 param_2,long param_3,ulong param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,void (*param_8)())

{
  undefined8 t1;
  undefined8 t2;
  long eo1;
  long n3;
  unsigned long (*pc4)();
  undefined8 eo8;
  long eo16;
  undefined8 *rx20;
  long n5;
  ulong rx21;
  long rx22;
  sk_c16_t at6;
  sk_c16_t _sv00000040;
  undefined8 sv00000048;
  long sv00000050;
  ulong sv00000058;
  unsigned long (*sv000000c0)();
  unsigned long (*sv000000c8)();
  
  sk_00355578();
  pc4 = param_8;
  at6._0_8_ = (undefined8)(sk_003542e8());
  at6._8_8_ = 0;
  n3 = param_3;
  (*pc4)(param_5,*rx20);
  sk_00084180();
  (*param_8)();
  sk_0034b778();
  (*sv000000c0)();
  sk_0034dfe4();
  n5 = *(long *)(eo16 + 0x48);
  sk_0036b118();
  if (eo1 + n5 * n3 == at6._8_8_ + n5 * param_3) {
    if ((long)(param_4 >> 1) < param_3) {
      sk_00347d60();
                          sk_001afe4c();
    }
    if (rx22 == param_3 && rx21 == param_4 >> 1) {
      sk_00354458(at6._0_8_,eo8);
      sk_0036b118();
      return;
    }
  }
  sv00000050 = param_3;
  sv00000058 = param_4;
  _sv00000040 = at6;
  sk_00350720();
  t1 = sk_00310df0();
  t2 = sk_00348d00();
  at6._0_8_ = (undefined8)(sk_00376820(t2,t1));
  at6._8_8_ = 0;
  sk_00100efc(at6._0_8_,at6._8_8_,&stk00000040);
  (*sv000000c8)();
  sk_00354458(eo8);
  return;
}

/* FUN_001dc754 @ 0x001dc754   (est. sk_r5_fatal_assert_001dc754) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc754(void)

{
  long n1;
  unsigned long (*pc2)();
  bool bv3;
  long n4;
  undefined8 t5;
  undefined8 t6;
  undefined8 ax3;
  undefined8 ax5;
  long eo8;
  unsigned long (*eo8_00)();
  undefined8 rx30;
  sk_c16_t at7;
  sk_c16_t at8;
  
  at7._0_8_ = (undefined8)(sk_00351e20());
  at7._8_8_ = 0;
  if (at7._0_8_ < 0) {
    sk_003488bc(1);
    sk_0034ae30();
  }
  else {
    at8._0_8_ = (undefined8)(sk_00353c48());
    at8._8_8_ = 0;
    if (at8._8_8_ <= eo8) {
      n1 = at7._8_8_ - at8._0_8_;
      if (ovf(at7._8_8_,at8._0_8_)) {
                            pc2 = (unsigned long (*)() )sk_breakpoint(1,0x1dc868);
        (*pc2)();
      }
      sk_003542e8();
      sk_00027788(ax5);
      sk_0034e63c();
      n4 = (*eo8_00)();
      bv3 = ovf(n4,n1);
      if (!bv3) {
        sk_0035a438(n4 - n1);
        if (!bv3) {
          t5 = sk_0034e384();
          sk_001dd614(t5,1,ax3);
          sk_0035113c();
          t5 = sk_00310dd8();
          t6 = sk_003498dc();
          sk_00376820(t6,t5);
          sk_00350618();
          sk_0035430c();
          sk_00356140();
          sk_00351d30(rx30);
          sk_0019c53c();
          return;
        }
                            pc2 = (unsigned long (*)() )sk_breakpoint(1,0x1dc870);
        (*pc2)();
      }
                          pc2 = (unsigned long (*)() )sk_breakpoint(1,0x1dc86c);
      (*pc2)();
    }
    sk_003488bc(1);
    sk_0034ae30();
  }
  sk_00353b34();
                      sk_001afe4c();
}

/* FUN_001dc870 @ 0x001dc870   (est. sk_r5_swift_001dc870) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc870(void)

{
  long rx19;
  undefined8 *rx20;
  sk_c16_t at1;
  
  sk_00349a18();
  sk_0036a908(0x40,0x952);
  at1._0_8_ = (undefined8)(sk_003501fc());
  at1._8_8_ = 0;
  sk_00100efc(at1._0_8_,at1._8_8_,*rx20,*(undefined8 *)(rx19 + 0x10));
  sk_001dc554();
  sk_00357694();
  sk_00353c54();
  return;
}

/* FUN_001dc8f4 @ 0x001dc8f4   (est. sk_r5_swift_001dc8f4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc8f4(undefined8 param_1,undefined8 param_2,void (*param_3)())

{
  undefined8 *pt1;
  undefined8 rx30;
  sk_c16_t at2;
  
  at2._0_8_ = (undefined8)(sk_0008e518());
  at2._8_8_ = 0;
  pt1 = (undefined8 *)*at2._0_8_;
  if ((at2._8_8_ & 1) == 0) {
    sk_0034db28(*pt1);
    sk_0035740c();
    (*param_3)();
  }
  else {
    sk_0036b270();
    sk_0034db28();
    sk_0035740c();
    (*param_3)();
    sk_0036b118(*pt1);
  }
  sk_0008e500(pt1,rx30);
  sk_t_00012568();
  return;
}

/* FUN_001dc9bc @ 0x001dc9bc   (est. sk_r5_swift_001dc9bc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dc9bc(undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4,
                 void (*param_5)(),void (*param_6)(),void (*jumptable)())

{
  long n1;
  long eo16;
  undefined8 t2;
  long n3;
  sk_c16_t at4;
  
  at4._0_8_ = (undefined8)(sk_00357cb4());
  at4._8_8_ = 0;
  n3 = *at4._8_8_;
  (*param_5)(param_3);
  t2 = *(undefined8 *)(param_3 + 0x10);
  sk_0034ede8();
  (*param_6)();
  sk_003507bc();
  sk_0019eb20();
  n1 = sk_0034b3c8();
  (**(unsigned long (**)() )(eo16 + 0x28))
            (n1 + *(long *)(eo16 + 0x48) * n3,at4._0_8_,t2);
  sk_0006b6f4();
  sk_00357c74();
                                          (*jumptable)();
  return;
}

/* FUN_001dcbac @ 0x001dcbac   (est. sk_r5_swift_001dcbac) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dcbac(undefined8 param_1,undefined8 param_2,void (*param_3)())

{
  undefined8 *pt1;
  undefined8 rx30;
  sk_c16_t at2;
  
  at2._0_8_ = (undefined8)(sk_0008e518());
  at2._8_8_ = 0;
  pt1 = (undefined8 *)*at2._0_8_;
  if ((at2._8_8_ & 1) == 0) {
    sk_0034be0c(*pt1);
    sk_0035740c();
    (*param_3)();
  }
  else {
    sk_0036b270();
    sk_0034be0c();
    sk_0035740c();
    (*param_3)();
    sk_0036b118(*pt1);
  }
  sk_0008e500(pt1,rx30);
  sk_t_00012568();
  return;
}

/* FUN_001dcc34 @ 0x001dcc34   (est. sk_r5_swift_001dcc34) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dcc34(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5)

{
  undefined8 t1;
  
  t1 = sk_00376820(&g_004e8bb4,param_4);
  sk_0019f1ec(param_1,param_2,param_3,param_4,t1,param_5);
  return;
}

/* FUN_001dccb4 @ 0x001dccb4   (est. sk_r5_swift_001dccb4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dccb4(void)

{
  sk_003580e4();
  sk_001dccd0();
  return;
}

/* FUN_001dccd0 @ 0x001dccd0   (est. sk_r5_swift_001dccd0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dccd0(void)

{
  sk_0019f698();
  return;
}

/* FUN_001dcd20 @ 0x001dcd20   (est. sk_r5_swift_001dcd20) */
/* Confidence: low (mechanical translation; names heuristic) */
undefined * sk_001dcd20(long *param_1,undefined8 *param_2,long param_3)

{
  long n1;
  undefined8 t2;
  undefined8 *rx20;
  
  n1 = sk_0036a908(0x28,0xd6c4);
  *param_1 = n1;
  t2 = sk_001dcd98(n1,*param_2,*rx20,*(undefined8 *)(param_3 + 0x10));
  *(undefined8 *)(n1 + 0x20) = t2;
  return &g_003471a4;
}

/* FUN_001dcd98 @ 0x001dcd98   (est. sk_r5_swift_001dcd98) */
/* Confidence: low (mechanical translation; names heuristic) */
undefined8 sk_001dcd98(long *param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  long n1;
  sk_c16_t at2;
  
  n1 = *(long *)(param_4 + -8);
  *param_1 = param_4;
  param_1[1] = n1;
  n1 = sk_0036a908(*(undefined8 *)(n1 + 0x40),0x87fe);
  param_1[2] = n1;
  sk_001dc430(n1,param_2,param_3,param_4);
  at2._8_8_ = n1;
  at2._0_8_ = &g_003471a8;
  return at2._0_8_;
}

/* FUN_001dce5c @ 0x001dce5c   (est. sk_r5_swift_001dce5c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dce5c(undefined8 *param_1,long param_2,undefined8 param_3,void (*param_4)())

{
  undefined8 *rx20;
  
  (*param_4)(*param_1,param_1[1],*rx20,*(undefined8 *)(param_2 + 0x10));
  sk_003554e0();
  return;
}

/* FUN_001dcea0 @ 0x001dcea0   (est. sk_r5_swift_001dcea0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dcea0(undefined8 param_1,undefined8 param_2)

{
  undefined8 t1;
  
  t1 = sk_00376820(&g_004e8b7c,param_2);
  sk_0019fa60(param_1,param_2,t1,0x6720e8);
  return;
}

/* FUN_001dcf0c @ 0x001dcf0c   (est. sk_r5_swift_001dcf0c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dcf0c(undefined8 param_1)

{
  undefined8 t1;
  
  t1 = sk_00376820(&g_004e8bd0,param_1);
  sk_001a0194(param_1,t1);
  return;
}

/* FUN_001dcf90 @ 0x001dcf90   (est. sk_r5_swift_001dcf90) */
/* Confidence: low (mechanical translation; names heuristic) */
undefined8 sk_001dcf90(void)

{
  undefined8 t1;
  long n2;
  undefined8 t3;
  unsigned long (*rx21)();
  undefined8 v38;
  
  t1 = sk_0034b470();
  n2 = sk_0036b270();
  if (n2 == 0) {
    v38 = 0;
    t1 = (*rx21)();
    sk_0009461c();
    t3 = sk_00376820();
    t1 = sk_001a4554(&v38,t1,t3);
  }
  else {
    sk_0036b118(t1);
  }
  return t1;
}

/* FUN_001dd024 @ 0x001dd024   (est. sk_r5_fatal_assert_001dd024) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd024(void)

{
  undefined8 t1;
  undefined8 t2;
  ulong t3;
  long eo8;
  long rx19;
  long rx22;
  long rx23;
  
  sk_00354a34();
  sk_003531d8();
  sk_00354708();
  sk_0035a01c();
  sk_003516cc();
  t1 = sk_00310d80();
  t2 = sk_00349234();
  sk_00376820(t2,t1);
  sk_00357ab4();
  t3 = sk_0019fd10(t1);
  if ((t3 & 1) != 0) {
L_001dd0a8:
    sk_00354ef8();
    return;
  }
  if (rx22 == 0) {
    sk_003488bc(1);
    sk_0034ae30();
  }
  else {
    if (*(long *)(rx19 + 0x10) <= rx23) {
      sk_00355730();
      sk_00351b78(rx19 + eo8);
      sk_0019dadc();
      goto L_001dd0a8;
    }
    sk_003488bc(1);
    sk_00356870();
    sk_0034ae30();
  }
  sk_00353b34();
                      sk_001afe4c();
}

/* FUN_001dd104 @ 0x001dd104   (est. sk_r5_swift_001dd104) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd104(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined8 *rx20;
  
  sk_001dd128(param_1,param_2,*rx20,*(undefined8 *)(param_4 + 0x10),param_3);
  return;
}

/* FUN_001dd108 @ 0x001dd108   (est. sk_r5_swift_001dd108) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd108(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined8 *rx20;
  
  sk_001dd128(param_1,param_2,*rx20,*(undefined8 *)(param_4 + 0x10),param_3);
  return;
}

/* FUN_001dd128 @ 0x001dd128   (est. sk_r5_swift_001dd128) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd128(void)

{
  sk_001dd154();
  return;
}

/* FUN_001dd154 @ 0x001dd154   (est. sk_r5_swift_001dd154) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd154(void)

{
  undefined8 ax5;
  undefined8 eo8;
  long rx21;
  
  sk_003545ac();
  sk_0034a210();
  sk_00002534();
  sk_003498c4();
  sk_0035a0b8();
  sk_003516d8(eo8,ax5);
  sk_001de8a8();
  if (rx21 == 0) {
    sk_00357418();
    sk_0034bc94();
    sk_000839d8();
  }
  return;
}

/* FUN_001dd1ec @ 0x001dd1ec   (est. sk_r5_swift_001dd1ec) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd1ec(void)

{
  sk_c16_t at1;
  undefined1 ast18 [8];
  
  sk_00352ddc();
  at1._0_8_ = (undefined8)(sk_00310d34());
  at1._8_8_ = 0;
  sk_0034921c(at1._0_8_,at1._8_8_,at1._0_8_);
  sk_0019e578(ast18);
  return;
}

/* FUN_001dd220 @ 0x001dd220   (est. sk_r5_swift_001dd220) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd220(undefined8 *param_1,undefined8 param_2,long param_3)

{
  undefined8 t1;
  
  t1 = sk_001dd1ec(param_2,*(undefined8 *)(param_3 + 0x10));
  *param_1 = t1;
  return;
}

/* FUN_001dd24c @ 0x001dd24c   (est. sk_r5_swift_001dd24c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd24c(void)

{
  sk_001dd264();
  return;
}

/* FUN_001dd264 @ 0x001dd264   (est. sk_r5_fatal_assert_001dd264) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd264(void)

{
  undefined8 t1;
  unsigned long (*ax3)();
  long eo8;
  unsigned long (*eo8_00)();
  unsigned long (*eo8_01)();
  long eo16;
  long rx22;
  unsigned long (*pc2)();
  undefined8 rx30;
  
  sk_0008e518();
  sk_00353430();
  sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348f38();
  sk_00106e3c();
  t1 = (*ax3)();
  if (rx22 < 0) {
    sk_00347da8();
L_001dd35c:
    sk_003504b8();
                        sk_001afe4c();
  }
  if (rx22 != 0) {
    pc2 = *(unsigned long (**)() )(eo16 + 0x10);
    do {
      if (rx22 == 0) {
        sk_00348034();
        goto L_001dd35c;
      }
      sk_00350624();
      (*pc2)();
      sk_00350618(*(undefined8 *)(eo16 + 0x20));
      (*eo8_00)();
      rx22 = rx22 + -1;
    } while (rx22 != 0);
  }
  sk_0007c1c4(*(undefined8 *)(eo16 + 8));
  (*eo8_01)();
  sk_0008e500(t1,rx30);
  return;
}

/* FUN_001dd374 @ 0x001dd374   (est. sk_r5_fatal_assert_001dd374) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd374(long param_1)

{
  long n1;
  
  if (param_1 < 0) {
                        sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Can_t_construct_ContiguousArray_w_005cedd0_str,0x2e,2,
                 Swift_ContiguousArray_swift_005cecd0_str,0x1b,2,0x25c,1);
  }
  if (param_1 != 0) {
    n1 = sk_001dd460(param_1);
    *(long *)(n1 + 0x10) = param_1;
  }
  return;
}

/* FUN_001dd408 @ 0x001dd408   (est. sk_r5_swift_001dd408) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd408(undefined8 param_1,undefined8 param_2)

{
  sk_001dd420(param_1,param_2,sk_001dd4cc);
  return;
}

/* FUN_001dd420 @ 0x001dd420   (est. sk_r5_swift_001dd420) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd420(undefined8 param_1,undefined8 param_2,void (*param_3)())

{
  long eo16;
  
  (*param_3)();
  sk_003597d8();
  sk_00357c20(*(undefined1 *)(eo16 + 0x50));
  return;
}

/* FUN_001dd460 @ 0x001dd460   (est. sk_r5_swift_001dd460) */
/* Confidence: low (mechanical translation; names heuristic) */
undefined * sk_001dd460(long param_1)

{
  undefined8 t1;
  undefined *pt2;
  long n3;
  
  if (param_1 < 1) {
    pt2 = &g_00657778;
  }
  else {
    t1 = sk_00002534(&g_0064e888,&g_004c06e0);
    pt2 = (undefined *)sk_0036a940(t1,param_1 + 0x20,7);
    n3 = sk_t_000126e8();
    *(undefined8 *)(pt2 + 0x10) = 0;
    *(long *)(pt2 + 0x18) = n3 * 2 + -0x40;
  }
  return pt2;
}

/* FUN_001dd4cc @ 0x001dd4cc   (est. sk_r5_fatal_assert_001dd4cc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd4cc(long param_1)

{
  long n1;
  
  if (-1 < param_1) {
    if (param_1 == 0) {
      sk_0006f6b4();
    }
    else {
      sk_0006f6b4();
      sk_0036b118();
      sk_0009461c();
      n1 = sk_001a04a4();
      *(long *)(n1 + 0x10) = param_1;
    }
    return;
  }
  sk_003488bc(1);
  sk_0034a6b0();
                      sk_001afe4c();
}

/* FUN_001dd58c @ 0x001dd58c   (est. sk_r5_swift_001dd58c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd58c(long param_1,uint param_2,void (*jumptable)())

{
  long n1;
  undefined8 t2;
  long *rx20;
  long n3;
  
  n3 = *rx20;
  t2 = sk_003a261c(n3);
  *rx20 = n3;
  if (((int)t2 != 0) && (param_1 <= (long)(*(ulong *)(n3 + 0x18) >> 1))) {
    return;
  }
  n1 = *(long *)(n3 + 0x10);
  if (*(long *)(n3 + 0x10) <= param_1) {
    n1 = param_1;
  }
                                          (*jumptable)(t2,n1,param_2 & 1);
  return;
}

/* FUN_001dd614 @ 0x001dd614   (est. sk_r5_swift_001dd614) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd614(long param_1,uint param_2,long param_3,void (*jumptable)())

{
  uint t1;
  long n2;
  long *rx20;
  
  sk_00310dd8(0,*(undefined8 *)(param_3 + 0x10));
  t1 = sk_0019e5ec();
  if (((t1 & 1) != 0) && (param_1 <= (long)(*(ulong *)(*rx20 + 0x18) >> 1))) {
    return;
  }
  n2 = *(long *)(*rx20 + 0x10);
  if (n2 <= param_1) {
    n2 = param_1;
  }
                                          (*jumptable)(t1 & 1,n2,param_2 & 1,param_3);
  return;
}

/* FUN_001dd6ac @ 0x001dd6ac   (est. sk_r5_swift_001dd6ac) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd6ac(void)

{
  undefined8 t1;
  undefined8 *rx20;
  
  t1 = sk_001a0b30();
  *rx20 = t1;
  return;
}

/* FUN_001dd6cc @ 0x001dd6cc   (est. sk_r5_swift_001dd6cc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd6cc(void)

{
  long n1;
  undefined8 t2;
  undefined8 t3;
  undefined8 rx30;
  
  n1 = sk_00357cb4();
  sk_00356834();
  t2 = sk_00310dd8();
  t3 = sk_003498dc();
  sk_00376820(t3,t2);
  sk_003511cc(n1,n1 + 1);
  t2 = sk_001a10d4();
  sk_000b4390();
  sk_001a10e4();
  sk_00356cfc();
  sk_0036b118();
  sk_00357c74(t2,rx30);
  sk_0036b118();
  return;
}

/* FUN_001dd77c @ 0x001dd77c   (est. sk_r5_swift_001dd77c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd77c(void)

{
  ulong t1;
  long n2;
  long *rx20;
  
  n2 = *rx20;
  t1 = sk_003a261c(n2);
  *rx20 = n2;
  if ((t1 & 1) != 0) {
    return;
  }
  sk_0006b3f4(*(undefined8 *)(n2 + 0x10));
  sk_t_001a0774();
  return;
}

/* FUN_001dd7f4 @ 0x001dd7f4   (est. sk_r5_swift_001dd7f4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd7f4(undefined8 param_1,void (*jumptable)())

{
  uint t1;
  
  sk_0035a040();
  sk_00310dd8();
  t1 = sk_0019e5ec();
  if ((t1 & 1) != 0) {
    return;
  }
  sk_00353c48();
  sk_0006b3f4();
                                          (*jumptable)();
  return;
}

/* FUN_001dd858 @ 0x001dd858   (est. sk_r5_swift_001dd858) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd858(long param_1)

{
  long *rx20;
  sk_c16_t at1;
  
  if (param_1 + 1 <= (long)(*(ulong *)(*rx20 + 0x18) >> 1)) {
    return;
  }
  at1._0_8_ = (undefined8)(sk_0006b42c());
  at1._8_8_ = 0;
  sk_001a0774(at1._0_8_,at1._8_8_,1);
  return;
}

/* FUN_001dd88c @ 0x001dd88c   (est. sk_r5_swift_001dd88c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd88c(long param_1,undefined8 param_2,void (*jumptable)())

{
  long *rx20;
  sk_c16_t at1;
  
  if (param_1 + 1 <= (long)(*(ulong *)(*rx20 + 0x18) >> 1)) {
    return;
  }
  at1._0_8_ = (undefined8)(sk_0006b42c());
  at1._8_8_ = 0;
                                          (*jumptable)(at1._0_8_,at1._8_8_,1);
  return;
}

/* FUN_001dd8cc @ 0x001dd8cc   (est. sk_r5_thunk_to_001dd8cc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dd8cc(long param_1,undefined8 param_2,long param_3)

{
  long n1;
  long n2;
  long *rx20;
  
  n1 = *rx20;
  *(long *)(n1 + 0x10) = param_1 + 1;
  n2 = *(long *)(*(long *)(param_3 + 0x10) + -8);
                                          (**(unsigned long (**)() )(n2 + 0x20))
            (n1 + ((ulong)*(byte *)(n2 + 0x50) + 0x20 &
                     ((ulong)*(byte *)(n2 + 0x50) ^ 0xffffffffffffffff)) +
             *(long *)(n2 + 0x48) * param_1);
  return;
}

/* FUN_001ddb2c @ 0x001ddb2c   (est. sk_r5_fatal_assert_001ddb2c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001ddb2c(void)

{
  long n1;
  ulong t2;
  unsigned long (*pc3)();
  long n4;
  undefined8 t5;
  long n6;
  long eo8;
  long *rx20;
  long n7;
  undefined8 t8;
  ulong t9;
  long n10;
  ulong t11;
  undefined8 *pt12;
  long n13;
  undefined8 *pt14;
  long n15;
  sk_c16_t at16;
  sk_c16_t at17;
  
  at16._0_8_ = (undefined8)(sk_0035300c());
  at16._8_8_ = 0;
  n4 = at16._0_8_;
  t9 = *(ulong *)(n4 + 0x10);
  sk_00353c48();
  if (ovf(eo8,t9)) {
                        pc3 = (unsigned long (*)() )sk_breakpoint(1,0x1ddd00);
    (*pc3)();
  }
  t5 = sk_0035475c(eo8 + t9);
  at17._0_8_ = (undefined8)(sk_001dd58c(t5,1));
  at17._8_8_ = 0;
  n13 = *rx20;
  t2 = (*(ulong *)(n13 + 0x18) >> 1) - *(long *)(n13 + 0x10);
  if ((long)t2 < 0) {
    sk_003487a4();
    sk_003524c8();
                        sk_001afe4c();
  }
  n6 = n13 + *(long *)(n13 + 0x10) * 0x10;
  n7 = *(long *)(n4 + 0x10);
  if (n7 == 0) {
    t11 = 0;
  }
  else {
    if (t2 < t9) {
      sk_003488bc(1);
      sk_00356870();
      sk_0034a3d8();
      sk_003504b8();
                          sk_001afe4c();
    }
    at17._0_8_ = (undefined8)(sk_0019d15c(n4 + 0x20,t9,n6 + 0x20));
    at17._8_8_ = 0;
    t11 = t9;
  }
  sk_0035050c(at17._0_8_,at17._8_8_,n6 + 0x20);
  n6 = sk_001a27f0();
  if (n6 < (long)t9) {
    sk_003488bc(1);
    sk_00355594();
    sk_0034ae30();
    sk_00353b34();
                        sk_001afe4c();
  }
  if (n6 != 0) {
    if (ovf(*(long *)(n13 + 0x10),n6)) {
                          pc3 = (unsigned long (*)() )sk_breakpoint(1,0x1ddd5c);
      (*pc3)();
    }
    *(long *)(n13 + 0x10) = *(long *)(n13 + 0x10) + n6;
  }
  if ((t11 == t2) && (n6 = *(long *)(n4 + 0x10), n7 != n6)) {
    n10 = *(long *)(n13 + 0x10);
    sk_00351390(n7);
    sk_0019e690();
    n15 = n4 + n7 * 0x10;
    t5 = *(undefined8 *)(n15 + 0x20);
    t8 = *(undefined8 *)(n15 + 0x28);
    sk_t_0036b270(t8);
    n7 = n7 + 1;
    do {
      if ((long)(*(ulong *)(n13 + 0x18) >> 1) < n10 + 1) {
        at17._0_8_ = (undefined8)(sk_0006b42c());
        at17._8_8_ = 0;
        sk_001a0734(at17._0_8_,at17._8_8_,1);
      }
      n15 = 0;
      n13 = *rx20;
      t9 = *(ulong *)(n13 + 0x18);
      pt14 = (undefined8 *)(n13 + n10 * 0x10 + 0x28);
      pt12 = (undefined8 *)(n4 + 0x28 + n7 * 0x10);
      while( true ) {
        n1 = n10 + n15;
        if ((long)(t9 >> 1) <= n1) break;
        pt14[-1] = t5;
        *pt14 = t8;
        if ((n7 - n6) + n15 == 0) {
          *(long *)(n13 + 0x10) = n10 + n15 + 1;
          goto L_001ddcd4;
        }
        if (*(long *)(n4 + 0x10) <= n7 + n15) {
          sk_00348304();
                              sk_001afe4c();
        }
        t5 = pt12[-1];
        t8 = *pt12;
        sk_t_0036b270(t8);
        n15 = n15 + 1;
        pt14 = pt14 + 2;
        pt12 = pt12 + 2;
      }
      *(long *)(n13 + 0x10) = n1;
      n10 = n1;
      n7 = n7 + n15;
    } while( true );
  }
L_001ddcd4:
  t5 = sk_0036b118(n4);
  *rx20 = n13;
  sk_00353238(t5,at16._8_8_);
  return;
}

/* FUN_001ddd5c @ 0x001ddd5c   (est. sk_r5_fatal_assert_001ddd5c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001ddd5c(void)

{
  undefined8 stk00000030;
  undefined8 stk00000050;
  undefined8 stk00000070;
  ulong t1;
  unsigned long (*pc2)();
  long n3;
  long n4;
  undefined8 t5;
  long eo8;
  long *rx20;
  long n6;
  ulong t7;
  ulong t8;
  long n9;
  long n10;
  sk_c16_t at11;
  sk_c16_t at12;
  long lStack0000000000000020;
  long sv00000048;
  long sv00000068;
  undefined8 sv00000070;
  undefined8 sv00000078;
  undefined8 sv00000080;
  undefined8 sv00000088;
  
  at11._0_8_ = (undefined8)(sk_003583e8());
  at11._8_8_ = 0;
  n3 = at11._0_8_;
  t7 = *(ulong *)(n3 + 0x10);
  sk_00353c48();
  if (ovf(eo8,t7)) {
                        pc2 = (unsigned long (*)() )sk_breakpoint(1,0x1ddff0);
    (*pc2)();
  }
  at12._0_8_ = (undefined8)(sk_001dd58c(eo8 + t7,1,sk_t_001a0754));
  at12._8_8_ = 0;
  lStack0000000000000020 = *rx20;
  t1 = (*(ulong *)(lStack0000000000000020 + 0x18) >> 1) -
          *(long *)(lStack0000000000000020 + 0x10);
  if ((long)t1 < 0) {
    sk_003487a4();
    sk_003524c8();
                        sk_001afe4c();
  }
  n4 = lStack0000000000000020 + *(long *)(lStack0000000000000020 + 0x10) * 0x20;
  n6 = *(long *)(n3 + 0x10);
  if (n6 == 0) {
    t8 = 0;
  }
  else {
    if (t1 < t7) {
      sk_003488bc(1);
      sk_00356870();
      sk_0034a3d8();
      sk_003504b8();
                          sk_001afe4c();
    }
    at12._0_8_ = (undefined8)(sk_0019d6d0(n3 + 0x20,t7,n4 + 0x20));
    at12._8_8_ = 0;
    t8 = t7;
  }
  sk_0035050c(at12._0_8_,at12._8_8_,n4 + 0x20);
  n4 = sk_001a27f0();
  if (n4 < (long)t7) {
    sk_003488bc(1);
    sk_00355594();
    sk_0034ae30();
    sk_00353b34();
                        sk_001afe4c();
  }
  if (n4 != 0) {
    if (ovf(*(long *)(lStack0000000000000020 + 0x10),n4)) {
                          pc2 = (unsigned long (*)() )sk_breakpoint(1,0x1de04c);
      (*pc2)();
    }
    *(long *)(lStack0000000000000020 + 0x10) = *(long *)(lStack0000000000000020 + 0x10) + n4;
  }
  if (t8 == t1) {
    n4 = *(long *)(lStack0000000000000020 + 0x10);
    n10 = *(long *)(n3 + 0x10);
    if (n6 == n10) {
      sv00000078 = 0;
      sv00000070 = 0;
      sv00000088 = 0;
      sv00000080 = 0;
    }
    else {
      sk_00351390(n6);
      sk_0019e690();
      sk_00319808(n3 + n6 * 0x20 + 0x20,&stk00000070);
      n6 = n6 + 1;
    }
    while( true ) {
      sk_003511f0(&stk00000070,&stk00000050);
      sk_00344ca8();
      if (sv00000068 == 0) break;
      sk_003505c4(&stk00000050);
      sk_00344e54();
      if ((long)(*(ulong *)(lStack0000000000000020 + 0x18) >> 1) < n4 + 1) {
        at12._0_8_ = (undefined8)(sk_0006b42c());
        at12._8_8_ = 0;
        sk_001a0754(at12._0_8_,at12._8_8_,1);
      }
      lStack0000000000000020 = *rx20;
      t7 = *(ulong *)(lStack0000000000000020 + 0x18);
      n9 = lStack0000000000000020 + n4 * 0x20;
      while( true ) {
        n9 = n9 + 0x20;
        sk_003511f0(&stk00000070,&stk00000030);
        sk_00344ca8();
        if (sv00000048 == 0) break;
        sk_00310d98(&stk00000030,&stk00000050);
        if ((long)(t7 >> 1) <= n4) {
          sk_000026e8(&stk00000050);
          goto L_001ddf88;
        }
        sk_003505c4(&stk00000070);
        sk_00344e54();
        sk_00310d98(&stk00000050,n9);
        if (n6 == n10) {
          sv00000078 = 0;
          sv00000070 = 0;
          sv00000088 = 0;
          sv00000080 = 0;
          n6 = n10;
        }
        else {
          if (*(long *)(n3 + 0x10) <= n6) {
            sk_00348304();
                                sk_001afe4c();
          }
          sk_00319808(n3 + 0x20 + n6 * 0x20,&stk00000070);
          n6 = n6 + 1;
        }
        n4 = n4 + 1;
      }
      sk_003505c4(&stk00000030);
      sk_00344e54();
L_001ddf88:
      *(long *)(lStack0000000000000020 + 0x10) = n4;
    }
    sk_003511d8(&stk00000070);
    sk_00344e54();
    sk_0036b118(n3);
    sk_003511d8(&stk00000050);
    t5 = sk_00344e54();
  }
  else {
    t5 = sk_0036b118(n3);
  }
  *rx20 = lStack0000000000000020;
  sk_00358454(t5,at11._8_8_);
  return;
}

/* FUN_001de04c @ 0x001de04c   (est. sk_r5_fatal_assert_001de04c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de04c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined1 t1;
  int iv2;
  undefined8 t3;
  undefined8 t4;
  long n5;
  long n6;
  undefined8 t7;
  undefined8 eo1;
  long eo8;
  undefined8 eo8_00;
  long eo8_01;
  unsigned long (*eo8_02)();
  long eo8_03;
  long eo8_04;
  unsigned long (*pc8)();
  undefined8 eo8_05;
  unsigned long (*eo8_06)();
  unsigned long (*eo8_07)();
  unsigned long (*eo8_08)();
  unsigned long (*eo9)();
  long n9;
  long eo16;
  long eo16_00;
  long eo16_01;
  long *rx20;
  unsigned long (*pc10)();
  long *rx21;
  long n11;
  ulong t12;
  unsigned long (*pc13)();
  undefined8 rx25;
  ulong t14;
  ulong t15;
  undefined8 rx30;
  sk_c16_t at16;
  undefined8 v38;
  
  sk_0008e518();
  at16._0_8_ = (undefined8)(sk_003518c4());
  at16._8_8_ = 0;
  sk_00349b3c(at16._0_8_,*(undefined8 *)(at16._8_8_ + 0x10));
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_003497b4();
  sk_00350908();
  t3 = sk_00310d68();
  sk_000a6f88();
  (*g_00658c00)(*(undefined8 *)(eo8_01 + 0x40));
  sk_003492ac();
  (*g_00658c00)();
  sk_0034ba78();
  (*g_00658c00)();
  sk_0034b4c0();
  sk_00349830();
  sk_00352840();
  t4 = sk_00377824();
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b05c();
  sk_00354f34(param_4);
  sk_00350914();
  n5 = (*eo8_02)();
  n6 = sk_00353c48();
  if (ovf(eo8_03,n6)) {
                        pc8 = (unsigned long (*)() )sk_breakpoint(1,0x1de4a4);
    (*pc8)();
  }
  t7 = sk_0034e384(eo8_03 + n6);
  sk_001dd614(t7,1);
  n11 = *rx20;
  sk_00355730();
  n9 = *(long *)(eo16 + 0x48);
  sk_001a26e0(n11 + eo8_04 + n9 * *(long *)(n11 + 0x10),
               (*(ulong *)(n11 + 0x18) >> 1) - *(long *)(n11 + 0x10));
  sk_003569b4();
  sk_00350630();
  sk_001a2740();
  sk_0034e130();
  n6 = sk_001a27f0();
  if (n6 < n5) {
    sk_00348b7c(0x365);
    sk_00355594();
    sk_0034ae30();
    sk_00353b34();
                        sk_001afe4c();
  }
  sk_003509c8(param_3);
  (**(unsigned long (**)() )(eo16_01 + 8))();
  if (0 < n6) {
    if (ovf(*(long *)(n11 + 0x10),n6)) {
                          pc8 = (unsigned long (*)() )sk_breakpoint(1,0x1de4d4);
      (*pc8)();
    }
    *(long *)(n11 + 0x10) = *(long *)(n11 + 0x10) + n6;
  }
  if (rx21 == rx20) {
    t15 = *(ulong *)(n11 + 0x10);
    sk_0034b278();
    at16._0_8_ = (undefined8)(sk_003514e8());
    at16._8_8_ = 0;
    t7 = sk_00377bec(at16._0_8_,at16._8_8_,t4);
    sk_000a68f4();
    sk_00351184();
    (*eo9)(t4,t7);
    pc8 = *(unsigned long (**)() )(eo16_00 + 0x10);
    t12 = (ulong)(eo16_00 + 0x10) & 0xffffffffffff | 0xe3ba000000000000;
    sk_00359ca4();
    while( true ) {
      at16._0_8_ = (undefined8)(sk_00351324());
      at16._8_8_ = 0;
      (*pc8)(t12,at16._0_8_,at16._8_8_,t3);
      at16._0_8_ = (undefined8)(sk_00351330());
      at16._8_8_ = 0;
      iv2 = sk_000839f8(at16._0_8_,at16._8_8_,eo1);
      pc13 = *(unsigned long (**)() )(eo16_00 + 8);
      t1 = iv2 == 1;
      if ((bool)t1) break;
      sk_0009461c();
      (*pc13)(eo8_05);
      sk_001a16e8(t15,rx21);
      n6 = *rx20;
      t14 = *(ulong *)(n6 + 0x18) >> 1;
      n5 = n6 + eo8_04;
      while( true ) {
        at16._0_8_ = (undefined8)(sk_00350944(n5));
        at16._8_8_ = 0;
        (*pc8)(t12,at16._0_8_,at16._8_8_,t3);
        sk_0034b2c8(v38);
        if ((bool)t1) break;
        pc10 = *(unsigned long (**)() )(eo16 + 0x20U);
        (*pc10)(eo8_00,v38,eo1);
        t1 = t15 == t14;
        if ((long)t14 <= (long)t15) {
          sk_00355224();
          sk_00350c80();
          (*eo8_06)();
          goto L_001de430;
        }
        (*pc13)(eo8_05);
        at16._0_8_ = (undefined8)(sk_003504ac());
        at16._8_8_ = 0;
        (*pc10)(eo16 + 0x20U & 0xffffffffffff | 0x48d8000000000000,at16._0_8_,
                   at16._8_8_,eo1);
        t15 = t15 + 1;
        (*eo9)(t4,t7);
        n5 = n9;
      }
      sk_003508a8();
      (*pc13)(eo8_05);
L_001de430:
      *(ulong *)(n6 + 0x10) = t15;
    }
    sk_00351e90();
    (*pc13)();
    sk_0035a4f8();
    (*eo8_08)(rx25,t4);
    sk_0009461c();
    (*pc13)();
  }
  else {
    sk_0035a4f8();
    (*eo8_07)(rx25,t4);
  }
  sk_0008e500(rx30);
  return;
}

/* FUN_001de4d4 @ 0x001de4d4   (est. sk_r5_swift_001de4d4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de4d4(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  unsigned long (*pc1)();
  long eo8;
  sk_c16_t at2;
  
  at2._0_8_ = (undefined8)(sk_00353c48());
  at2._8_8_ = 0;
  if (!ovf(eo8,at2._0_8_)) {
    sk_001dd614(eo8 + at2._0_8_,1,at2._8_8_,param_3);
    return;
  }
                      pc1 = (unsigned long (*)() )sk_breakpoint(1,0x1de508);
  (*pc1)();
}

/* FUN_001de4d8 @ 0x001de4d8   (est. sk_r5_swift_001de4d8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de4d8(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  unsigned long (*pc1)();
  long eo8;
  sk_c16_t at2;
  
  at2._0_8_ = (undefined8)(sk_00353c48());
  at2._8_8_ = 0;
  if (!ovf(eo8,at2._0_8_)) {
    sk_001dd614(eo8 + at2._0_8_,1,at2._8_8_,param_3);
    return;
  }
                      pc1 = (unsigned long (*)() )sk_breakpoint(1,0x1de508);
  (*pc1)();
}

/* FUN_001de508 @ 0x001de508   (est. sk_r5_fatal_assert_001de508) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de508(void)

{
  long n1;
  long eo16;
  long *rx20;
  long n2;
  
  sk_00357ca0();
  sk_00353b10();
  sk_t_001dc298();
  n2 = *rx20;
  n1 = *(long *)(n2 + 0x10);
  if (n1 != 0) {
    sk_003511b4();
    (**(unsigned long (**)() )(eo16 + 0x20))();
    *(long *)(n2 + 0x10) = n1 + -1;
    sk_0034b744();
    sk_00357c44();
    sk_000839d8();
    return;
  }
  sk_003488bc(1);
  sk_0034a6b0();
                      sk_001afe4c();
}

/* FUN_001de698 @ 0x001de698   (est. sk_r5_swift_001de698) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de698(void)

{
  sk_001de6c4();
  return;
}

/* FUN_001de6c4 @ 0x001de6c4   (est. sk_r5_swift_001de6c4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de6c4(void)

{
  unsigned long (*ax4)();
  long eo16;
  unsigned long (*rx21)();
  undefined8 rx30;
  
  sk_0008e518();
  sk_0034b668();
  sk_00350720();
  sk_00319218();
  sk_0034a450();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b0d4();
  (*rx21)();
  sk_0034dfe4();
  (**(unsigned long (**)() )(eo16 + 0x20))();
  sk_00376820(&g_004ec334);
  sk_00351e9c();
  (*ax4)();
  sk_0008e500(rx30);
  return;
}

/* FUN_001de7c8 @ 0x001de7c8   (est. sk_r5_swift_001de7c8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de7c8(void)

{
  undefined8 stk00000008;
  undefined8 t1;
  undefined8 t2;
  unsigned long (*ax3)();
  long eo8;
  long *rx20;
  undefined8 rx30;
  sk_c16_t at3;
  long sv00000018;
  
  at3._0_8_ = (undefined8)(sk_00357ca0());
  at3._8_8_ = 0;
  if ((at3._0_8_ & 1) == 0) {
    sk_0036b118(*rx20);
    sk_000a6f68();
    *rx20 = eo8;
  }
  else {
    t1 = sk_003a261c(*rx20);
    if ((int)t1 == 0) {
      sk_00351ecc(t1,*(ulong *)(*rx20 + 0x18) >> 1);
      sk_0019c44c();
      sk_00356328();
      sk_0036b118();
      *rx20 = (long)ax3;
    }
    else {
      sv00000018 = *rx20;
      sk_00351384();
      t1 = sk_00376820();
      sk_00348e9c(t1,t1);
      sk_0019fa60(&stk00000008,at3._8_8_);
      sk_00350500();
      t1 = sk_00319230();
      t2 = sk_00348d18();
      sk_00376820(t2,t1);
      sk_00353cf0();
      sk_00352c40();
      (*ax3)();
    }
  }
  sk_00357c44(rx30);
  return;
}

/* FUN_001de8a8 @ 0x001de8a8   (est. sk_r5_swift_001de8a8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de8a8(void)

{
  undefined8 ax5;
  unsigned long (*eo8)();
  long eo16;
  long rx21;
  sk_c16_t at1;
  
  sk_0034b7e4();
  (*g_00658c00)();
  sk_0034c8e0();
  sk_001a76fc();
  if (rx21 != 0) {
    at1._0_8_ = (undefined8)(sk_00084174(*(undefined8 *)(eo16 + 0x20)));
    at1._8_8_ = 0;
    (*eo8)(at1._0_8_,at1._8_8_,ax5);
  }
  return;
}

/* FUN_001de960 @ 0x001de960   (est. sk_r5_swift_001de960) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de960(undefined8 *param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined8 t1;
  
  t1 = sk_001dd24c(param_2,param_3,*(undefined8 *)(param_4 + 0x10));
  *param_1 = t1;
  return;
}

/* FUN_001de9bc @ 0x001de9bc   (est. sk_r5_swift_001de9bc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001de9bc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 t1;
  
  t1 = sk_00376820(&g_004e8b98,param_3);
  sk_001a5968(param_1,param_2,param_3,t1,param_4);
  return;
}

/* FUN_001dea34 @ 0x001dea34   (est. sk_r5_swift_001dea34) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dea34(undefined8 param_1,undefined8 param_2)

{
  sk_001dea60(param_1,param_2,sk_00310d80,&g_004e8bd0);
  return;
}

/* FUN_001dea60 @ 0x001dea60   (est. sk_r5_swift_001dea60) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dea60(undefined8 param_1,undefined8 param_2,void (*param_3)())

{
  undefined8 t1;
  undefined8 *rx21;
  sk_c16_t at2;
  undefined8 v60;
  undefined8 st58;
  undefined8 st50;
  undefined1 st48;
  undefined7 v47;
  undefined1 st40;
  undefined8 st3f;
  
  sk_003530e8();
  (*param_3)(0);
  sk_003504ac();
  sk_00376820();
  t1 = sk_0035310c();
  sk_0036b2d0(t1,2);
  at2._0_8_ = (undefined8)(sk_00357f14());
  at2._8_8_ = 0;
  sk_003515b4(at2._0_8_,at2._8_8_,5);
  sk_001a67bc();
  rx21[1] = st58;
  *rx21 = v60;
  rx21[3] = concat(v47,st48);
  rx21[2] = st50;
  *(undefined8 *)((long)rx21 + 0x21) = st3f;
  *(ulong *)((long)rx21 + 0x19) = concat(st40,v47);
  return;
}

/* FUN_001deae8 @ 0x001deae8   (est. sk_r5_swift_001deae8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001deae8(undefined8 *param_1,long param_2)

{
  undefined8 *rx20;
  undefined8 v50;
  undefined8 st48;
  undefined8 st40;
  undefined1 st38;
  undefined7 v37;
  undefined1 st30;
  undefined8 st2f;
  
  sk_001dea34(&v50,*rx20,*(undefined8 *)(param_2 + 0x10));
  param_1[1] = st48;
  *param_1 = v50;
  param_1[3] = concat(v37,st38);
  param_1[2] = st40;
  *(undefined8 *)((long)param_1 + 0x21) = st2f;
  *(ulong *)((long)param_1 + 0x19) = concat(st30,v37);
  return;
}

/* FUN_001debac @ 0x001debac   (est. sk_r5_swift_001debac) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001debac(undefined8 param_1,undefined8 param_2,void (*param_3)())

{
  sk_003543ac();
  sk_00352ddc();
  (*param_3)();
  sk_00350af4();
  sk_00376820();
  sk_00357a84();
  sk_0034d190();
  sk_001a6ab8();
  return;
}

/* FUN_001dec50 @ 0x001dec50   (est. sk_r5_swift_001dec50) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dec50(undefined8 param_1,undefined8 param_2,void (*param_3)())

{
  undefined8 stk00000008;
  undefined8 t1;
  ulong t2;
  long n3;
  long eo8;
  long n4;
  undefined8 rx30;
  sk_c16_t at5;
  undefined8 sv00000008;
  
  at5._0_8_ = (undefined8)(sk_00357cb4());
  at5._8_8_ = 0;
  n3 = at5._0_8_;
  n4 = *(long *)(at5._8_8_ + -8);
  if (n3 == 0) {
    sv00000008 = 0;
    t1 = (*param_3)();
    sk_00351450();
    sk_00376820();
    sk_00355c28();
    t2 = sk_0019fd10(t1);
    if ((t2 & 1) == 0) {
      sv00000008 = 0;
      sk_00350488();
      sk_00310dd8();
      sk_00349f08();
      n3 = sk_0019e578(&stk00000008);
      goto L_001decbc;
    }
  }
  sk_0036b270(n3);
L_001decbc:
  sk_00357c20(*(undefined1 *)(n4 + 0x50));
  sk_00357c74(n3,n3 + eo8,rx30);
  return;
}

/* FUN_001ded00 @ 0x001ded00   (est. sk_r5_fatal_assert_001ded00) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001ded00(long *param_1,long param_2,long *param_3,long *param_4,long *param_5)

{
  char *pc1;
  undefined8 t2;
  undefined8 t3;
  
  if (param_2 < *param_1) {
    t3 = 0x462;
    pc1 = Initialized_count_set_to_greater_005d3970_str;
    t2 = 0x39;
  }
  else {
    if (*param_3 != 0 && *param_4 == *param_3) {
      *(long *)(*param_5 + 0x10) = *param_1;
      return;
    }
    t3 = 0x466;
    pc1 = Can_t_reassign_buffer_in_Array_u_005d39b0_str;
    t2 = 0x4d;
  }
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,pc1,t2,2,Swift_ContiguousArray_swift_005cecd0_str,
               0x1b,2,t3,1);
}

/* FUN_001dedcc @ 0x001dedcc   (est. sk_r5_swift_001dedcc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dedcc(void)

{
  sk_001dedf8();
  return;
}

/* FUN_001dedd0 @ 0x001dedd0   (est. sk_r5_swift_001dedd0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dedd0(void)

{
  sk_001dedf8();
  return;
}

/* FUN_001dedf8 @ 0x001dedf8   (est. sk_r5_swift_001dedf8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dedf8(void)

{
  sk_0034d2b4();
  sk_0034a210();
  sk_00002534();
  sk_003498c4();
  sk_0035a0b8();
  sk_00352d34();
  sk_0034ef08();
  sk_001a76fc();
  return;
}

/* FUN_001dee70 @ 0x001dee70   (est. sk_r5_swift_001dee70) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dee70(undefined8 param_1,undefined8 param_2,undefined8 param_3)

{
  undefined8 eo8;
  long eo16;
  long n1;
  long *rx20;
  undefined8 t2;
  ulong t3;
  unsigned long (*rx27)();
  undefined8 rx30;
  undefined1 v70 [16];
  
  sk_0035acfc();
  sk_003537fc();
  sk_t_001dc298(param_3);
  n1 = *rx20;
  t2 = *(undefined8 *)(n1 + 0x10);
  sk_00356030();
  t3 = (ulong)*(byte *)(eo16 + 0x50) + 0x20 &
          ((ulong)*(byte *)(eo16 + 0x50) ^ 0xffffffffffffffff);
  v70 = sk_001a26e0(n1 + t3,t2);
  (*rx27)(eo8,v70);
  sk_0034a210();
  sk_00002534();
  sk_00348d30();
  sk_00351f1c(v70,n1 + t3);
  sk_001def38();
  sk_0035841c(rx30);
  return;
}

/* FUN_001def38 @ 0x001def38   (est. sk_r5_fatal_assert_001def38) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001def38(long *param_1,long param_2,long param_3)

{
  if ((*param_1 != 0 && param_2 == *param_1) && (param_1[1] == param_3)) {
    return;
  }
                      sk_001afe4c(Fatal_error_005accd0_str,0xb,2,ContiguousArray_withUnsafeMutabl_005d3d30_str,0x53,2,
               Swift_ContiguousArray_swift_005cecd0_str,0x1b,2,0x55b,1);
}

/* FUN_001defb0 @ 0x001defb0   (est. sk_r5_swift_001defb0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001defb0(void)

{
  sk_001defc8();
  return;
}

/* FUN_001defc8 @ 0x001defc8   (est. sk_r5_swift_001defc8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001defc8(void)

{
  bool bv1;
  uint t2;
  undefined8 t3;
  long eo1;
  unsigned long (*ax4)();
  long eo8;
  unsigned long (*eo8_00)();
  long n4;
  long eo14;
  undefined8 eo14_00;
  undefined8 eo16;
  unsigned long (*pc5)();
  long n6;
  undefined8 rx30;
  sk_c16_t at7;
  
  sk_0008e518();
  sk_003539f4();
  sk_0034b7e4();
  (*g_00658c00)(eo16);
  sk_00352330();
  (*g_00658c00)();
  at7._0_8_ = (undefined8)(sk_00358308());
  at7._8_8_ = 0;
  n4 = *(long *)(at7._0_8_ + 0x10);
  if (n4 == *(long *)(at7._8_8_ + 0x10)) {
    if (n4 == 0 || eo14 == eo1) {
      t2 = 1;
    }
    else {
      n6 = 0;
      do {
        t3 = sk_00353c78();
        (*ax4)(t3,eo14_00);
        sk_0035308c();
        sk_0035119c();
        (*ax4)();
        sk_0014ae44();
        sk_0034bddc();
        sk_00350aac();
        t2 = (*eo8_00)();
        pc5 = *(unsigned long (**)() )(eo8 + 8);
        sk_00351714();
        (*pc5)();
        sk_003512c0();
        (*pc5)();
        if ((t2 & 1) == 0) break;
        bv1 = n4 + -1 != n6;
        n6 = n6 + 1;
      } while (bv1);
    }
  }
  else {
    t2 = 0;
  }
  sk_0008e500(t2 & 1,rx30);
  return;
}

/* FUN_001df16c @ 0x001df16c   (est. sk_r5_swift_001df16c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df16c(void)

{
  unsigned long (*pc1)();
  long eo1;
  long eo8;
  unsigned long (*eo8_00)();
  long eo16;
  long rx22;
  long n2;
  long n3;
  undefined8 rx30;
  
  sk_0008e518();
  sk_00349a18();
  sk_00349720();
  (*g_00658c00)(*(undefined8 *)(eo8 + 0x40));
  sk_00348f38();
  sk_t_002298d4(*(undefined8 *)(eo1 + 0x10));
  n3 = *(long *)(rx22 + 0x10);
  if (n3 != 0) {
    pc1 = (unsigned long (*)() )sk_0031945c();
    n2 = 0;
    do {
      sk_0034d7dc();
      sk_001dc430();
      n2 = n2 + 1;
      sk_00355af8();
      sk_003504a0();
      (*pc1)();
      sk_003507bc(*(undefined8 *)(eo16 + 8));
      (*eo8_00)();
    } while (n3 != n2);
  }
  sk_0008e500(rx30);
  return;
}

/* FUN_001df2a0 @ 0x001df2a0   (est. sk_r5_swift_001df2a0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df2a0(void)

{
  unsigned long (*rx19)();
  undefined8 *rx20;
  long rx21;
  undefined1 ast78 [72];
  
  sk_00354f10();
  sk_00359134();
  (*rx19)(ast78,*rx20,*(undefined8 *)(rx21 + 0x10));
  sk_001a8564();
  return;
}

/* FUN_001df2f4 @ 0x001df2f4   (est. sk_r5_swift_001df2f4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df2f4(void)

{
  sk_001df334();
  return;
}

/* FUN_001df2f8 @ 0x001df2f8   (est. sk_r5_swift_001df2f8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df2f8(void)

{
  sk_001df334();
  return;
}

/* FUN_001df334 @ 0x001df334   (est. sk_r5_swift_001df334) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df334(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 void (*param_5)(),void (*param_6)())

{
  undefined8 eo8;
  long eo16;
  long n1;
  long *rx20;
  ulong t2;
  undefined8 t3;
  undefined1 v60 [16];
  
  sk_003537fc();
  (*param_5)(param_3);
  n1 = *rx20;
  t3 = *(undefined8 *)(n1 + 0x10);
  sk_00356030();
  t2 = (ulong)*(byte *)(eo16 + 0x50) + 0x20 &
          ((ulong)*(byte *)(eo16 + 0x50) ^ 0xffffffffffffffff);
  v60 = sk_001a26e0(n1 + t2,t3);
  sk_00352c4c(eo8,v60);
  sk_001df428();
  sk_0034a210();
  sk_00002534();
  sk_00348d30();
  sk_00353a78(v60,n1 + t2);
  (*param_6)();
  return;
}

/* FUN_001df428 @ 0x001df428   (est. sk_r5_fatal_assert_001df428) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df428(long *param_1,void (*param_2)(),undefined8 param_3,long param_4)

{
  unsigned long (*pc1)();
  long n2;
  long n3;
  long n4;
  long rx21;
  
  n2 = *param_1;
  n4 = *(long *)(*(long *)(param_4 + -8) + 0x48);
  n3 = param_1[1] * n4;
  if (ovf((long long)(param_1[1]) * (long long)(n4),8) != n3 >> 0x3f) {
                        pc1 = (unsigned long (*)() )sk_breakpoint(1,0x1df4d8);
    (*pc1)();
  }
  if (n3 < 0) {
    sk_003483c4();
L_001df4dc:
    sk_00351094();
                        sk_001afe4c();
  }
  if (n3 == 0) {
    if (n2 == 0) {
      n3 = 0;
      goto L_001df4a8;
    }
  }
  else if (n2 == 0) {
    sk_003488bc(1);
    sk_00349644();
    goto L_001df4dc;
  }
  n3 = n3 + n2;
L_001df4a8:
  (*param_2)(n2,n3);
  if (rx21 != 0) {
    sk_00354720();
  }
  return;
}

/* FUN_001df4e4 @ 0x001df4e4   (est. sk_r5_swift_001df4e4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df4e4(void)

{
  sk_001a7e5c();
  return;
}

/* FUN_001df510 @ 0x001df510   (est. sk_r5_fatal_assert_001df510) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df510(long param_1,long param_2,void (*param_3)(),undefined8 param_4,long param_5)

{
  unsigned long (*pc1)();
  long n2;
  long n3;
  long rx21;
  
  n3 = *(long *)(*(long *)(param_5 + -8) + 0x48);
  n2 = param_2 * n3;
  if (ovf((long long)(param_2) * (long long)(n3),8) != n2 >> 0x3f) {
                        pc1 = (unsigned long (*)() )sk_breakpoint(1,0x1df598);
    (*pc1)();
  }
  if (n2 < 0) {
    sk_00348284();
L_001df59c:
    sk_00351094();
                        sk_001afe4c();
  }
  if (n2 == 0) {
    if (param_1 == 0) {
      n2 = 0;
      goto L_001df568;
    }
  }
  else if (param_1 == 0) {
    sk_00348508();
    goto L_001df59c;
  }
  n2 = n2 + param_1;
L_001df568:
  (*param_3)(param_1,n2);
  if (rx21 != 0) {
    sk_00354720();
  }
  return;
}

/* FUN_001df5a4 @ 0x001df5a4   (est. sk_r5_swift_001df5a4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df5a4(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined8 *rx20;
  
  sk_001a7e30(param_1,param_2,*rx20,*(undefined8 *)(param_4 + 0x10),param_3);
  return;
}

/* FUN_001df5a8 @ 0x001df5a8   (est. sk_r5_swift_001df5a8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df5a8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined8 *rx20;
  
  sk_001a7e30(param_1,param_2,*rx20,*(undefined8 *)(param_4 + 0x10),param_3);
  return;
}

/* FUN_001df5c8 @ 0x001df5c8   (est. sk_r5_swift_001df5c8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df5c8(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined8 *rx20;
  
  sk_001df4e4(param_1,param_2,*rx20,*(undefined8 *)(param_4 + 0x10),param_3);
  return;
}

/* FUN_001df5cc @ 0x001df5cc   (est. sk_r5_swift_001df5cc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df5cc(undefined8 param_1,undefined8 param_2,undefined8 param_3,long param_4)

{
  undefined8 *rx20;
  
  sk_001df4e4(param_1,param_2,*rx20,*(undefined8 *)(param_4 + 0x10),param_3);
  return;
}

/* FUN_001df5ec @ 0x001df5ec   (est. sk_r5_swift_001df5ec) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df5ec(void)

{
  sk_001df7f4();
  return;
}

/* FUN_001df604 @ 0x001df604   (est. sk_r5_swift_001df604) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df604(void)

{
  undefined1 zr;
  undefined8 t1;
  unsigned long (*eo8)();
  unsigned long (*eo8_00)();
  unsigned long (*eo9)();
  unsigned long (*eo9_00)();
  long eo16;
  long eo16_00;
  undefined8 t2;
  undefined8 rx30;
  sk_c16_t at3;
  
  sk_0008e518();
  sk_00351cf4();
  sk_00358f78();
  t1 = sk_00310d68(0);
  sk_000a6f88();
  sk_0007c1a4();
  (*g_00658c00)();
  sk_0034b0d4();
  sk_0034b3e8();
  t2 = *(undefined8 *)(eo16_00 + 0x40);
  (*g_00658c00)();
  (*g_00658c00)();
  sk_0034b87c();
  sk_00352b50();
  at3._0_8_ = (undefined8)(sk_00350a70());
  at3._8_8_ = 0;
  (*eo9)(at3._0_8_,at3._8_8_,t1);
  sk_00349f3c();
  if (!(bool)zr) {
    at3._0_8_ = (undefined8)(sk_003509b0());
    at3._8_8_ = 0;
    sk_00117cc4(at3._0_8_,at3._8_8_,t2);
    sk_00310f94();
    sk_00351ac8();
    sk_003504ac();
    (*eo8_00)();
    sk_00351a44();
    sk_00310fc4();
    sk_00350b24();
    sk_00351190(t1);
    (*eo9_00)();
    sk_00351118();
    t1 = sk_00117cc4();
  }
  else {
    sk_00351ec0(*(undefined8 *)(eo16 + 8));
    t1 = (*eo8)();
  }
  sk_0034dba8(t1,(bool)zr);
  sk_000839d8();
  sk_0008e500(rx30);
  return;
}

/* FUN_001df790 @ 0x001df790   (est. sk_r5_fatal_assert_001df790) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df790(long param_1,long param_2)

{
  if (param_2 < 0) {
    sk_00348284();
  }
  else {
    if ((param_2 == 0) || (param_1 != 0)) {
      return;
    }
    sk_00348508();
  }
  sk_00351094();
                      sk_001afe4c();
}

/* FUN_001df7dc @ 0x001df7dc   (est. sk_r5_swift_001df7dc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df7dc(void)

{
  sk_001df870();
  return;
}

/* FUN_001df7f4 @ 0x001df7f4   (est. sk_r5_fatal_assert_001df7f4) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df7f4(undefined8 param_1,undefined8 param_2,long param_3,long param_4,long param_5)

{
  long n1;
  unsigned long (*eo9)();
  long eo10;
  
  if (*(long *)(*(long *)(param_5 + -8) + 0x48) * param_4 < 0) {
    sk_00348284();
L_001df868:
    sk_00351094();
                        sk_001afe4c();
  }
  sk_0035a184();
  if (eo10 == 0) {
    if (param_3 == 0) {
      n1 = 0;
      goto L_001df840;
    }
  }
  else if (param_3 == 0) {
    sk_00348508();
    goto L_001df868;
  }
  n1 = eo10 + param_3;
L_001df840:
  (*eo9)(param_3,n1);
  return;
}

/* FUN_001df870 @ 0x001df870   (est. sk_r5_fatal_assert_001df870) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df870(void (*param_1)(),undefined8 param_2,undefined8 param_3,long param_4)

{
  long n1;
  long n2;
  long *rx20;
  
  n1 = *rx20;
  n2 = *(long *)(*(long *)(*(long *)(param_4 + 0x10) + -8) + 0x48) * rx20[1];
  if (n2 < 0) {
    sk_00348284();
L_001df8f0:
    sk_00351094();
                        sk_001afe4c();
  }
  if (n2 == 0) {
    if (n1 == 0) {
      n2 = 0;
      goto L_001df8c8;
    }
  }
  else if (n1 == 0) {
    sk_00348508();
    goto L_001df8f0;
  }
  n2 = n2 + n1;
L_001df8c8:
  (*param_1)(n1,n2);
  return;
}

/* FUN_001df924 @ 0x001df924   (est. sk_r5_thunk_to_001df924) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df924(void (*param_1)())

{
  undefined8 *rx20;
  
  (*param_1)(*rx20,rx20[1]);
  return;
}

/* FUN_001df958 @ 0x001df958   (est. sk_r5_swift_001df958) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df958(undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4)

{
  undefined8 t1;
  unsigned long (*eo9)();
  
  sk_0035a184();
  t1 = 0;
  if (param_3 != 0) {
    t1 = param_4;
  }
  (*eo9)(param_3,t1);
  return;
}

/* FUN_001df98c @ 0x001df98c   (est. sk_r5_fatal_assert_001df98c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001df98c(undefined8 param_1,void (*param_2)())

{
  long n1;
  long n2;
  long *rx20;
  
  n1 = *rx20;
  n2 = sk_001a0158(n1,rx20[1]);
  if (n2 == 0) {
    if (n1 == 0) {
      n2 = 0;
      goto L_001dfa1c;
    }
  }
  else if (n1 == 0) {
                        sk_001afe4c(Fatal_error_005accd0_str,0xb,2,UnsafeRawBufferPointer_has_a_nil_005cdf20_str,0x38,2,
                 Swift_UnsafeRawBufferPointer_swi_005cde40_str,0x22,2,0x4c2,1);
  }
  n2 = n2 + n1;
L_001dfa1c:
  (*param_2)(param_1,n1,n2);
  return;
}

/* FUN_001dfa60 @ 0x001dfa60   (est. sk_r5_swift_001dfa60) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dfa60(undefined8 param_1)

{
  undefined8 ax3;
  undefined8 ax4;
  sk_c16_t at1;
  
  sk_t_0036b270(ax3);
  at1._0_8_ = (undefined8)(sk_00354d44());
  at1._8_8_ = 0;
  sk_001b07b8(param_1,at1._0_8_,at1._8_8_,ax4);
  sk_003a25d4(ax3);
  return;
}

/* FUN_001dfadc @ 0x001dfadc   (est. sk_r5_swift_001dfadc) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dfadc(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *rx20;
  undefined1 ast70 [16];
  undefined8 v60;
  undefined8 st58;
  undefined8 v50;
  undefined8 v40;
  undefined8 v38;
  
  v40 = *rx20;
  v38 = rx20[1];
  v60 = param_4;
  st58 = param_2;
  v50 = param_3;
  sk_t_0036b270(v38);
  sk_001b07b8(param_1,sk_003469a8,ast70,param_4);
  sk_003a25d4(v38);
  return;
}

/* FUN_001dfb7c @ 0x001dfb7c   (est. sk_r5_swift_001dfb7c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dfb7c(void)

{
  undefined8 ax3;
  
  sk_00077888();
  sk_t_0036b270(ax3);
  sk_0007c1c4();
  return;
}

/* FUN_001dfba8 @ 0x001dfba8   (est. sk_r5_swift_001dfba8) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dfba8(undefined8 param_1)

{
  undefined8 ax5;
  undefined8 ax6;
  sk_c16_t at1;
  
  sk_t_0036b270(ax5);
  at1._0_8_ = (undefined8)(sk_00354d44());
  at1._8_8_ = 0;
  sk_001dfc88(param_1,at1._0_8_,at1._8_8_,ax6);
  sk_003a25d4(ax5);
  return;
}

/* FUN_001dfc28 @ 0x001dfc28   (est. sk_r5_fatal_assert_001dfc28) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dfc28(long param_1,long param_2,void (*param_3)())

{
  if (param_2 < 0) {
    sk_00348284();
L_001dfc80:
    sk_00351094();
                        sk_001afe4c();
  }
  if (param_2 == 0) {
    if (param_1 == 0) {
      param_2 = 0;
      goto L_001dfc58;
    }
  }
  else if (param_1 == 0) {
    sk_00348508();
    goto L_001dfc80;
  }
  param_2 = param_2 + param_1;
L_001dfc58:
  (*param_3)(param_1,param_2);
  return;
}

/* FUN_001dfc88 @ 0x001dfc88   (est. sk_r5_fatal_assert_001dfc88) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dfc88(undefined8 param_1,void (*param_2)(),undefined8 param_3,undefined8 param_4)

{
  long n1;
  long n2;
  undefined8 t3;
  undefined8 t4;
  ulong t5;
  ulong *rx20;
  ulong t6;
  ulong t7;
  sk_c16_t at8;
  sk_c16_t at9;
  undefined1 aste0 [16];
  undefined8 vd0;
  unsigned long (*vc0)();
  undefined8 va0;
  unsigned long (*pcs98)();
  undefined8 v90;
  ulong v88;
  ulong v80;
  undefined1 v68 [8];
  ulong v60;
  ulong st58;
  
  t5 = rx20[3];
  if ((t5 >> 0x3c & 1) != 0) {
    sk_002a9c14();
    t5 = rx20[3];
  }
  t6 = *rx20 >> 0x10;
  t7 = rx20[1] >> 0x10;
  at8._0_8_ = (undefined8)((*g_00658c00)(rx20[2],t5));
  at8._8_8_ = 0;
  st58 = at8._8_8_;
  v60 = at8._0_8_;
  va0 = param_4;
  pcs98 = param_2;
  v90 = param_3;
  v88 = t6;
  v80 = t7;
  if ((st58 >> 0x3d & 1) == 0) {
    if ((v60 >> 0x3c & 1) == 0) {
      at8._0_8_ = (undefined8)(sk_002a9ba8());
      at8._8_8_ = 0;
    }
    else {
      at8._8_8_ = v60 & 0xffffffffffff;
      at8._0_8_ = (st58 & 0xfffffffffffffff) + 0x20;
    }
    at9._0_8_ = (undefined8)(sk_0028e8c0(t6,t7,at8._0_8_,at8._8_8_,0x7a8,0x7a9));
    at9._8_8_ = 0;
    n2 = at9._0_8_;
    if ((n2 < 0) || (at8._8_8_ < at9._8_8_)) {
      v80 = concat(v80._4_4_,1);
      v88 = 0x7db;
      v90 = concat(v90._1_7_,2);
                          sk_001afe4c(Fatal_error_005accd0_str,0xb,2,Invalid_slice_005cfa58_str,0xd,2,
                   Swift_UnsafeBufferPointer_swift_005cdc10_str,0x1f);
    }
    n1 = 0;
    if (at8._0_8_ != 0) {
      n1 = at8._0_8_ + n2;
    }
    sk_001e4cbc(n1,at9._8_8_ - n2);
    (*param_2)(param_1);
  }
  else {
    st58 = st58 & 0xffffffffffffff;
    (*g_00658c00)();
    vc0 = sk_00347040;
    vd0 = param_4;
    t3 = sk_00002534(0x656158,&g_004e7fa8);
    t4 = sk_00002534(&g_0064c260,&g_004bbc30);
    sk_00291d70(param_1,&v60,sk_00346774,aste0,t3,t4,param_4,0x66c1c8,v68);
  }
  return;
}

/* FUN_001dfec0 @ 0x001dfec0   (est. sk_r5_swift_001dfec0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dfec0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)

{
  undefined8 *rx20;
  undefined1 ast80 [16];
  undefined8 v70;
  undefined8 st68;
  undefined8 v60;
  undefined8 v50;
  undefined8 st48;
  undefined8 v40;
  undefined8 v38;
  
  v40 = rx20[2];
  v38 = rx20[3];
  st48 = rx20[1];
  v50 = *rx20;
  v70 = param_4;
  st68 = param_2;
  v60 = param_3;
  sk_t_0036b270(v38);
  sk_001dfc88(param_1,sk_003469a8,ast80,param_4);
  sk_003a25d4(v38);
  return;
}

/* FUN_001dff5c @ 0x001dff5c   (est. sk_r5_swift_001dff5c) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_t_0026c2a0(undefined8 param_1,long param_2)

{
  long rx20;
  
                                          (**(unsigned long (**)() )(*(long *)(*(long *)(param_2 + 0x10) + -8) + 0x10))
            (param_1,rx20 + *(int *)(param_2 + 0x24));
  return;
}

/* FUN_001dff60 @ 0x001dff60   (est. sk_r5_fatal_assert_001dff60) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dff60(long param_1,long param_2)

{
  if (param_1 <= param_2) {
    return;
  }
  sk_003488bc(1);
  sk_0034abb0();
  sk_00352be0();
                      sk_001afe4c();
}

/* FUN_001dffa0 @ 0x001dffa0   (est. sk_r5_fatal_assert_001dffa0) */
/* Confidence: low (mechanical translation; names heuristic) */
void sk_001dffa0(void)

{
  int iv1;
  undefined8 t2;
  ulong t3;
  undefined8 ax3;
  undefined8 eo8;
  long eo8_00;
  unsigned long (*eo8_01)();
  unsigned long (*pc4)();
  unsigned long (*eo8_02)();
  unsigned long (*pc5)();
  unsigned long (*eo8_03)();
  long eo16;
  long n6;
  long rx20;
  long rx21;
  long rx23;
  unsigned long (*pc7)();
  undefined8 rx30;
  sk_c16_t at8;
  undefined8 v28;
  undefined8 v8;
  
  sk_0008e518();
  sk_003531f0();
  sk_0034b0b4();
  sk_00359000();
  sk_00348d64();
  (*g_00658c00)(*(undefined8 *)(eo8_00 + 0x40));
  sk_00348a9c();
  (*g_00658c00)();
  sk_00350434();
  sk_003503f8();
  (*g_00658c00)();
  sk_0034ea40();
  (*g_00658c00)();
  sk_0034ac28();
  (*g_00658c00)();
  sk_0034c074();
  n6 = *(long *)(rx20 + -8);
  pc7 = *(unsigned long (**)() )(n6 + 0x20);
  sk_00351130();
  (*pc7)();
  iv1 = *(int *)(rx23 + 0x30);
  sk_00350968(rx21 + iv1);
  (*pc7)();
  t2 = sk_0035166c(ax3);
  sk_00353cd8(t2,rx21 + iv1);
  t3 = (*eo8_01)();
  if ((t3 & 1) != 0) {
    pc4 = *(unsigned long (**)() )(eo16 + 0x10);
    sk_003507e0();
    (*eo8_02)();
    pc5 = *(unsigned long (**)() )(eo16 + 0x20);
    sk_003504f4();
    (*eo8_03)();
    sk_0034d180();
    (*pc7)();
    sk_00359e14();
    (*pc7)();
    sk_0034fd4c();
    (*pc4)();
    iv1 = *(int *)(rx23 + 0x30);
    sk_00351744(eo8);
    (*pc7)();
    pc4 = *(unsigned long (**)() )(n6 + 8);
    (*pc4)(v28 + iv1);
    sk_0034fd4c();
    (*pc5)();
    at8._0_8_ = (undefined8)(sk_00350798());
    at8._8_8_ = 0;
    n6 = sk_00310f04(at8._0_8_,at8._8_8_,ax3);
    sk_00359d9c((long)*(int *)(n6 + 0x24));
    (*pc7)();
    sk_00351714();
    (*pc4)();
    (*pc4)(v8);
    sk_0035a1c0();
    (*pc4)();
    sk_0008e500(rx30);
    return;
  }
  sk_00350410();
  sk_003488bc();
  sk_0034abb0();
  sk_00352be0();
                      sk_001afe4c();
}

