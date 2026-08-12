/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice R27: addresses 0x0046ae94 - 0x0047c4e4. This is the embedded Swift
 * _StringProcessing regex-bytecode-generator region (strings: Backreference_kind,
 * Anchor_*, Handled_in_ByteCodeGen, _StringProcessing_ByteCodeGen_sw). The
 * functions here compile the parsed regex AST into the cL4 regex-match
 * bytecode stream. All names are estimates unless string-matched.
 *
 * Conventions: out-of-slice callees keep their FUN_ names as extern
 * identifiers; in-slice functions use sk_bcg_<addr> names (or string-derived
 * names). 16-byte x0:x1 returns are wpair_t. Decompiler register artifacts
 * (extraout_xN, unaff_xN) are modelled as locals/params. SoftwareBreakpoint
 * fail-closed checks (>> 0xe tag/range compares) are rendered as
 * CL4_SWBP(addr). Confidence: medium unless a function header says otherwise. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t word_t;
typedef unsigned long long u64;
typedef unsigned char byte;
typedef unsigned int uint;
typedef struct { uint64_t lo, hi; } wpair_t;   /* 16-byte (x0:x1) returns */
typedef uint64_t (*code)();

#define LZCOUNT(x)     ((unsigned long)__builtin_clzll((unsigned long)(x)))
#define CL4_FATAL()    __builtin_trap()
#define SCARRY8(a, b)  (__builtin_add_overflow((a), (b), &(unsigned long){0}))
#define SBORROW8(a, b) (__builtin_sub_overflow((a), (b), &(unsigned long){0}))

/* Ghidra SoftwareBreakpoint(1, addr) - fail-closed trap, does not return. */
static inline unsigned long CL4_SWBP(unsigned long addr)
{ (void)addr; __builtin_trap(); }

/* cL4 guarded-entry / exception-return supervisor call. The decompiler renders
 * the guarded-level entry as an indirect call through the constant address
 * SUB_54ffff60f100041f; modelled here as an extern thunk (sibling-slice
 * convention, cf. sk_slice_r26.c). */
extern word_t sk_svc_call();

/* Out-of-slice callees (bodies reconstructed by their range workers). */

extern wpair_t FUN_00002534(); /* out of slice 0x2534 */
extern word_t FUN_00002818(); /* out of slice 0x2818 */
extern word_t FUN_00002834(); /* out of slice 0x2834 */
extern word_t FUN_00002874(); /* out of slice 0x2874 */
extern word_t FUN_0001612c(); /* out of slice 0x1612c */
extern word_t FUN_00019858(); /* out of slice 0x19858 */
extern word_t FUN_0001ba10(); /* out of slice 0x1ba10 */
extern wpair_t FUN_0001d4f4(); /* out of slice 0x1d4f4 */
extern word_t FUN_0001da84(); /* out of slice 0x1da84 */
extern word_t FUN_0001dd14(); /* out of slice 0x1dd14 */
extern word_t FUN_00027724(); /* out of slice 0x27724 */
extern word_t FUN_00027754(); /* out of slice 0x27754 */
extern word_t FUN_000277b8(); /* out of slice 0x277b8 */
extern word_t FUN_000277e8(); /* out of slice 0x277e8 */
extern word_t FUN_00027818(); /* out of slice 0x27818 */
extern word_t FUN_00068e14(); /* out of slice 0x68e14 */
extern wpair_t FUN_0006ae9c(); /* out of slice 0x6ae9c */
extern word_t FUN_0006b3f4(); /* out of slice 0x6b3f4 */
extern word_t FUN_0006b42c(); /* out of slice 0x6b42c */
extern word_t FUN_0006f6b4(); /* out of slice 0x6f6b4 */
extern word_t FUN_00071fe4(); /* out of slice 0x71fe4 */
extern word_t FUN_00072c0c(); /* out of slice 0x72c0c */
extern word_t FUN_00073690(); /* out of slice 0x73690 */
extern word_t FUN_00074a28(); /* out of slice 0x74a28 */
extern word_t FUN_0007767c(); /* out of slice 0x7767c */
extern wpair_t FUN_00077698(); /* out of slice 0x77698 */
extern word_t FUN_00077888(); /* out of slice 0x77888 */
extern word_t FUN_00077894(); /* out of slice 0x77894 */
extern word_t FUN_0007c028(); /* out of slice 0x7c028 */
extern word_t FUN_0007c1a4(); /* out of slice 0x7c1a4 */
extern wpair_t FUN_0007c1c4(); /* out of slice 0x7c1c4 */
extern word_t FUN_00083450(); /* out of slice 0x83450 */
extern word_t FUN_000839d8(); /* out of slice 0x839d8 */
extern word_t FUN_000839f8(); /* out of slice 0x839f8 */
extern word_t FUN_0008409c(); /* out of slice 0x8409c */
extern word_t FUN_00084174(); /* out of slice 0x84174 */
extern wpair_t FUN_00084180(); /* out of slice 0x84180 */
extern wpair_t FUN_00084220(); /* out of slice 0x84220 */
extern word_t FUN_00084234(); /* out of slice 0x84234 */
extern word_t FUN_000867ec(); /* out of slice 0x867ec */
extern word_t FUN_00086840(); /* out of slice 0x86840 */
extern wpair_t FUN_0008e388(); /* out of slice 0x8e388 */
extern word_t FUN_0008e500(); /* out of slice 0x8e500 */
extern wpair_t FUN_0008e518(); /* out of slice 0x8e518 */
extern wpair_t FUN_0009461c(); /* out of slice 0x9461c */
extern wpair_t FUN_0009e234(); /* out of slice 0x9e234 */
extern word_t FUN_000a68c4(); /* out of slice 0xa68c4 */
extern word_t FUN_000a68f4(); /* out of slice 0xa68f4 */
extern wpair_t FUN_000a6e14(); /* out of slice 0xa6e14 */
extern word_t FUN_000a6f68(); /* out of slice 0xa6f68 */
extern word_t FUN_000a6f88(); /* out of slice 0xa6f88 */
extern word_t FUN_000a6fe0(); /* out of slice 0xa6fe0 */
extern word_t FUN_000aa4ec(); /* out of slice 0xaa4ec */
extern word_t FUN_000b4390(); /* out of slice 0xb4390 */
extern wpair_t FUN_000b43d0(); /* out of slice 0xb43d0 */
extern word_t FUN_000b4594(); /* out of slice 0xb4594 */
extern word_t FUN_000b45b0(); /* out of slice 0xb45b0 */
extern word_t FUN_000bd3a4(); /* out of slice 0xbd3a4 */
extern word_t FUN_000dbbe0(); /* out of slice 0xdbbe0 */
extern wpair_t FUN_000dbd0c(); /* out of slice 0xdbd0c */
extern word_t FUN_000e0654(); /* out of slice 0xe0654 */
extern wpair_t FUN_000e15d8(); /* out of slice 0xe15d8 */
extern wpair_t FUN_000e72b0(); /* out of slice 0xe72b0 */
extern word_t FUN_000ec004(); /* out of slice 0xec004 */
extern word_t FUN_000ec044(); /* out of slice 0xec044 */
extern word_t FUN_000f4a9c(); /* out of slice 0xf4a9c */
extern word_t FUN_000f5e5c(); /* out of slice 0xf5e5c */
extern word_t FUN_00100c38(); /* out of slice 0x100c38 */
extern wpair_t FUN_00100efc(); /* out of slice 0x100efc */
extern word_t FUN_00106e3c(); /* out of slice 0x106e3c */
extern word_t FUN_00117cc4(); /* out of slice 0x117cc4 */
extern word_t FUN_00117d14(); /* out of slice 0x117d14 */
extern word_t FUN_0011e71c(); /* out of slice 0x11e71c */
extern word_t FUN_0014ae44(); /* out of slice 0x14ae44 */
extern word_t FUN_0016749c(); /* out of slice 0x16749c */
extern word_t FUN_001676cc(); /* out of slice 0x1676cc */
extern word_t FUN_0019dfc4(); /* out of slice 0x19dfc4 */
extern word_t FUN_0019e578(); /* out of slice 0x19e578 */
extern word_t FUN_0019e924(); /* out of slice 0x19e924 */
extern word_t FUN_0019ea20(); /* out of slice 0x19ea20 */
extern word_t FUN_0019ed3c(); /* out of slice 0x19ed3c */
extern word_t FUN_0019fa60(); /* out of slice 0x19fa60 */
extern word_t FUN_001a1854(); /* out of slice 0x1a1854 */
extern word_t FUN_001a29a0(); /* out of slice 0x1a29a0 */
extern word_t FUN_001a9a84(); /* out of slice 0x1a9a84 */
extern word_t FUN_001a9ac8(); /* out of slice 0x1a9ac8 */
extern word_t FUN_001ae8a8(); /* out of slice 0x1ae8a8 */
extern word_t FUN_001afa84(); /* out of slice 0x1afa84 */
extern word_t FUN_001b36ec(); /* out of slice 0x1b36ec */
extern word_t FUN_001bb7a0(); /* out of slice 0x1bb7a0 */
extern word_t FUN_001d80e0(); /* out of slice 0x1d80e0 */
extern word_t FUN_001d9890(); /* out of slice 0x1d9890 */
extern word_t FUN_001e3048(); /* out of slice 0x1e3048 */
extern word_t FUN_001ee018(); /* out of slice 0x1ee018 */
extern word_t FUN_001f0130(); /* out of slice 0x1f0130 */
extern word_t FUN_00205844(); /* out of slice 0x205844 */
extern wpair_t FUN_00255d4c(); /* out of slice 0x255d4c */
extern word_t FUN_00258c60(); /* out of slice 0x258c60 */
extern word_t FUN_002591b4(); /* out of slice 0x2591b4 */
extern wpair_t FUN_00267510(); /* out of slice 0x267510 */
extern word_t FUN_00270c08(); /* out of slice 0x270c08 */
extern word_t FUN_00273fe0(); /* out of slice 0x273fe0 */
extern word_t FUN_00294cb4(); /* out of slice 0x294cb4 */
extern word_t FUN_0029c058(); /* out of slice 0x29c058 */
extern wpair_t FUN_0029fa0c(); /* out of slice 0x29fa0c */
extern wpair_t FUN_0029fb80(); /* out of slice 0x29fb80 */
extern word_t FUN_002a0cf8(); /* out of slice 0x2a0cf8 */
extern wpair_t FUN_002a3e64(); /* out of slice 0x2a3e64 */
extern wpair_t FUN_002a49a8(); /* out of slice 0x2a49a8 */
extern word_t FUN_002a4ab4(); /* out of slice 0x2a4ab4 */
extern word_t FUN_002a9ba8(); /* out of slice 0x2a9ba8 */
extern word_t FUN_002acbb8(); /* out of slice 0x2acbb8 */
extern word_t FUN_002b24b8(); /* out of slice 0x2b24b8 */
extern wpair_t FUN_002b3978(); /* out of slice 0x2b3978 */
extern word_t FUN_002b3b50(); /* out of slice 0x2b3b50 */
extern word_t FUN_002b3cf8(); /* out of slice 0x2b3cf8 */
extern wpair_t FUN_002b3f40(); /* out of slice 0x2b3f40 */
extern word_t FUN_002b4120(); /* out of slice 0x2b4120 */
extern wpair_t FUN_002b439c(); /* out of slice 0x2b439c */
extern word_t FUN_002b7088(); /* out of slice 0x2b7088 */
extern word_t FUN_002b723c(); /* out of slice 0x2b723c */
extern wpair_t FUN_002b74c0(); /* out of slice 0x2b74c0 */
extern word_t FUN_002bc2f8(); /* out of slice 0x2bc2f8 */
extern word_t FUN_002bd848(); /* out of slice 0x2bd848 */
extern word_t FUN_002bd8f0(); /* out of slice 0x2bd8f0 */
extern word_t FUN_002bde1c(); /* out of slice 0x2bde1c */
extern word_t FUN_002c0054(); /* out of slice 0x2c0054 */
extern word_t FUN_00310924(); /* out of slice 0x310924 */
extern word_t FUN_00310d34(); /* out of slice 0x310d34 */
extern word_t FUN_00310d68(); /* out of slice 0x310d68 */
extern word_t FUN_00310e08(); /* out of slice 0x310e08 */
extern word_t FUN_00310e20(); /* out of slice 0x310e20 */
extern word_t FUN_003192a8(); /* out of slice 0x3192a8 */
extern word_t FUN_00319308(); /* out of slice 0x319308 */
extern word_t FUN_00319628(); /* out of slice 0x319628 */
extern word_t FUN_00319658(); /* out of slice 0x319658 */
extern word_t FUN_0031d488(); /* out of slice 0x31d488 */
extern word_t FUN_0031d5f0(); /* out of slice 0x31d5f0 */
extern word_t FUN_0031d600(); /* out of slice 0x31d600 */
extern word_t FUN_0031d678(); /* out of slice 0x31d678 */
extern word_t FUN_0031e0d4(); /* out of slice 0x31e0d4 */
extern word_t FUN_003272b8(); /* out of slice 0x3272b8 */
extern word_t FUN_003493c4(); /* out of slice 0x3493c4 */
extern word_t FUN_00349530(); /* out of slice 0x349530 */
extern word_t FUN_00349a18(); /* out of slice 0x349a18 */
extern word_t FUN_00349fe0(); /* out of slice 0x349fe0 */
extern word_t FUN_0034ab10(); /* out of slice 0x34ab10 */
extern word_t FUN_0034ab20(); /* out of slice 0x34ab20 */
extern word_t FUN_0034aee4(); /* out of slice 0x34aee4 */
extern word_t FUN_0034af20(); /* out of slice 0x34af20 */
extern word_t FUN_0034b0b4(); /* out of slice 0x34b0b4 */
extern word_t FUN_0034b0c4(); /* out of slice 0x34b0c4 */
extern word_t FUN_0034b0d4(); /* out of slice 0x34b0d4 */
extern word_t FUN_0034b318(); /* out of slice 0x34b318 */
extern word_t FUN_0034b3f8(); /* out of slice 0x34b3f8 */
extern word_t FUN_0034b460(); /* out of slice 0x34b460 */
extern word_t FUN_0034b4c0(); /* out of slice 0x34b4c0 */
extern word_t FUN_0034b540(); /* out of slice 0x34b540 */
extern word_t FUN_0034ba48(); /* out of slice 0x34ba48 */
extern word_t FUN_0034ba68(); /* out of slice 0x34ba68 */
extern word_t FUN_0034be0c(); /* out of slice 0x34be0c */
extern word_t FUN_0034c444(); /* out of slice 0x34c444 */
extern word_t FUN_0034c6d4(); /* out of slice 0x34c6d4 */
extern wpair_t FUN_0034cff4(); /* out of slice 0x34cff4 */
extern word_t FUN_0034db28(); /* out of slice 0x34db28 */
extern word_t FUN_0034dfa4(); /* out of slice 0x34dfa4 */
extern word_t FUN_0034e5bc(); /* out of slice 0x34e5bc */
extern word_t FUN_0034eb74(); /* out of slice 0x34eb74 */
extern word_t FUN_0034ecc8(); /* out of slice 0x34ecc8 */
extern word_t FUN_003503f8(); /* out of slice 0x3503f8 */
extern word_t FUN_00350404(); /* out of slice 0x350404 */
extern word_t FUN_00350428(); /* out of slice 0x350428 */
extern word_t FUN_00350464(); /* out of slice 0x350464 */
extern word_t FUN_00350470(); /* out of slice 0x350470 */
extern word_t FUN_003504a0(); /* out of slice 0x3504a0 */
extern wpair_t FUN_003504c4(); /* out of slice 0x3504c4 */
extern word_t FUN_003504d0(); /* out of slice 0x3504d0 */
extern wpair_t FUN_003504e8(); /* out of slice 0x3504e8 */
extern wpair_t FUN_003504f4(); /* out of slice 0x3504f4 */
extern wpair_t FUN_00350500(); /* out of slice 0x350500 */
extern wpair_t FUN_0035050c(); /* out of slice 0x35050c */
extern word_t FUN_00350518(); /* out of slice 0x350518 */
extern wpair_t FUN_00350524(); /* out of slice 0x350524 */
extern wpair_t FUN_00350530(); /* out of slice 0x350530 */
extern word_t FUN_0035053c(); /* out of slice 0x35053c */
extern word_t FUN_00350548(); /* out of slice 0x350548 */
extern word_t FUN_00350560(); /* out of slice 0x350560 */
extern word_t FUN_0035056c(); /* out of slice 0x35056c */
extern word_t FUN_003505c4(); /* out of slice 0x3505c4 */
extern wpair_t FUN_003505e8(); /* out of slice 0x3505e8 */
extern wpair_t FUN_0035060c(); /* out of slice 0x35060c */
extern wpair_t FUN_00350618(); /* out of slice 0x350618 */
extern word_t FUN_00350624(); /* out of slice 0x350624 */
extern word_t FUN_0035063c(); /* out of slice 0x35063c */
extern wpair_t FUN_00350738(); /* out of slice 0x350738 */
extern wpair_t FUN_00350774(); /* out of slice 0x350774 */
extern wpair_t FUN_00350798(); /* out of slice 0x350798 */
extern word_t FUN_003507bc(); /* out of slice 0x3507bc */
extern wpair_t FUN_003507e0(); /* out of slice 0x3507e0 */
extern word_t FUN_0035084c(); /* out of slice 0x35084c */
extern word_t FUN_00350878(); /* out of slice 0x350878 */
extern word_t FUN_00350884(); /* out of slice 0x350884 */
extern word_t FUN_0035089c(); /* out of slice 0x35089c */
extern wpair_t FUN_003508b4(); /* out of slice 0x3508b4 */
extern wpair_t FUN_003508cc(); /* out of slice 0x3508cc */
extern wpair_t FUN_003508e4(); /* out of slice 0x3508e4 */
extern word_t FUN_003508fc(); /* out of slice 0x3508fc */
extern wpair_t FUN_00350914(); /* out of slice 0x350914 */
extern word_t FUN_00350968(); /* out of slice 0x350968 */
extern word_t FUN_00350980(); /* out of slice 0x350980 */
extern word_t FUN_003509a4(); /* out of slice 0x3509a4 */
extern wpair_t FUN_003509b0(); /* out of slice 0x3509b0 */
extern wpair_t FUN_003509bc(); /* out of slice 0x3509bc */
extern word_t FUN_003509c8(); /* out of slice 0x3509c8 */
extern word_t FUN_003509ec(); /* out of slice 0x3509ec */
extern wpair_t FUN_00350a04(); /* out of slice 0x350a04 */
extern word_t FUN_00350a1c(); /* out of slice 0x350a1c */
extern wpair_t FUN_00350a70(); /* out of slice 0x350a70 */
extern word_t FUN_00350aa0(); /* out of slice 0x350aa0 */
extern word_t FUN_00350ab8(); /* out of slice 0x350ab8 */
extern wpair_t FUN_00350af4(); /* out of slice 0x350af4 */
extern wpair_t FUN_00350b3c(); /* out of slice 0x350b3c */
extern word_t FUN_00350b48(); /* out of slice 0x350b48 */
extern word_t FUN_00350b54(); /* out of slice 0x350b54 */
extern word_t FUN_00350b84(); /* out of slice 0x350b84 */
extern word_t FUN_00350b9c(); /* out of slice 0x350b9c */
extern word_t FUN_00350bc0(); /* out of slice 0x350bc0 */
extern word_t FUN_00350bfc(); /* out of slice 0x350bfc */
extern word_t FUN_00350c08(); /* out of slice 0x350c08 */
extern word_t FUN_00350c20(); /* out of slice 0x350c20 */
extern word_t FUN_00350c98(); /* out of slice 0x350c98 */
extern word_t FUN_00350d94(); /* out of slice 0x350d94 */
extern word_t FUN_003510ac(); /* out of slice 0x3510ac */
extern wpair_t FUN_003510b8(); /* out of slice 0x3510b8 */
extern wpair_t FUN_003510dc(); /* out of slice 0x3510dc */
extern word_t FUN_00351118(); /* out of slice 0x351118 */
extern word_t FUN_00351130(); /* out of slice 0x351130 */
extern word_t FUN_00351178(); /* out of slice 0x351178 */
extern word_t FUN_003511a8(); /* out of slice 0x3511a8 */
extern word_t FUN_003511cc(); /* out of slice 0x3511cc */
extern word_t FUN_003511d8(); /* out of slice 0x3511d8 */
extern word_t FUN_003511f0(); /* out of slice 0x3511f0 */
extern word_t FUN_00351214(); /* out of slice 0x351214 */
extern word_t FUN_00351274(); /* out of slice 0x351274 */
extern word_t FUN_003512c0(); /* out of slice 0x3512c0 */
extern word_t FUN_00351300(); /* out of slice 0x351300 */
extern wpair_t FUN_00351324(); /* out of slice 0x351324 */
extern wpair_t FUN_00351354(); /* out of slice 0x351354 */
extern word_t FUN_0035136c(); /* out of slice 0x35136c */
extern word_t FUN_00351384(); /* out of slice 0x351384 */
extern word_t FUN_00351390(); /* out of slice 0x351390 */
extern word_t FUN_0035139c(); /* out of slice 0x35139c */
extern word_t FUN_003513a8(); /* out of slice 0x3513a8 */
extern word_t FUN_003513b4(); /* out of slice 0x3513b4 */
extern wpair_t FUN_00351414(); /* out of slice 0x351414 */
extern wpair_t FUN_00351450(); /* out of slice 0x351450 */
extern wpair_t FUN_0035145c(); /* out of slice 0x35145c */
extern word_t FUN_00351488(); /* out of slice 0x351488 */
extern word_t FUN_003514a0(); /* out of slice 0x3514a0 */
extern wpair_t FUN_003514e8(); /* out of slice 0x3514e8 */
extern word_t FUN_0035156c(); /* out of slice 0x35156c */
extern word_t FUN_00351584(); /* out of slice 0x351584 */
extern word_t FUN_003515d8(); /* out of slice 0x3515d8 */
extern word_t FUN_003515fc(); /* out of slice 0x3515fc */
extern word_t FUN_0035166c(); /* out of slice 0x35166c */
extern word_t FUN_003516b4(); /* out of slice 0x3516b4 */
extern word_t FUN_00351714(); /* out of slice 0x351714 */
extern word_t FUN_00351750(); /* out of slice 0x351750 */
extern word_t FUN_00351774(); /* out of slice 0x351774 */
extern word_t FUN_00351790(); /* out of slice 0x351790 */
extern word_t FUN_003517c0(); /* out of slice 0x3517c0 */
extern word_t FUN_0035193c(); /* out of slice 0x35193c */
extern wpair_t FUN_0035199c(); /* out of slice 0x35199c */
extern word_t FUN_00351a50(); /* out of slice 0x351a50 */
extern word_t FUN_00351aec(); /* out of slice 0x351aec */
extern word_t FUN_00351b78(); /* out of slice 0x351b78 */
extern word_t FUN_00351bd4(); /* out of slice 0x351bd4 */
extern word_t FUN_00351c7c(); /* out of slice 0x351c7c */
extern word_t FUN_00351cd0(); /* out of slice 0x351cd0 */
extern word_t FUN_00351d18(); /* out of slice 0x351d18 */
extern wpair_t FUN_00351db4(); /* out of slice 0x351db4 */
extern word_t FUN_00351de4(); /* out of slice 0x351de4 */
extern word_t FUN_00351dfc(); /* out of slice 0x351dfc */
extern word_t FUN_00351e3c(); /* out of slice 0x351e3c */
extern word_t FUN_00351f1c(); /* out of slice 0x351f1c */
extern word_t FUN_00351f4c(); /* out of slice 0x351f4c */
extern word_t FUN_00351f88(); /* out of slice 0x351f88 */
extern wpair_t FUN_00352290(); /* out of slice 0x352290 */
extern word_t FUN_003522c8(); /* out of slice 0x3522c8 */
extern word_t FUN_003527b8(); /* out of slice 0x3527b8 */
extern word_t FUN_00352840(); /* out of slice 0x352840 */
extern word_t FUN_00352ae4(); /* out of slice 0x352ae4 */
extern word_t FUN_00352af0(); /* out of slice 0x352af0 */
extern word_t FUN_00352c40(); /* out of slice 0x352c40 */
extern word_t FUN_00352c4c(); /* out of slice 0x352c4c */
extern word_t FUN_00352c80(); /* out of slice 0x352c80 */
extern word_t FUN_00352e9c(); /* out of slice 0x352e9c */
extern word_t FUN_00352ea8(); /* out of slice 0x352ea8 */
extern word_t FUN_00352efc(); /* out of slice 0x352efc */
extern word_t FUN_0035300c(); /* out of slice 0x35300c */
extern word_t FUN_00353208(); /* out of slice 0x353208 */
extern word_t FUN_00353238(); /* out of slice 0x353238 */
extern word_t FUN_003532b8(); /* out of slice 0x3532b8 */
extern wpair_t FUN_003535a8(); /* out of slice 0x3535a8 */
extern word_t FUN_00353960(); /* out of slice 0x353960 */
extern wpair_t FUN_00353cfc(); /* out of slice 0x353cfc */
extern word_t FUN_00353d14(); /* out of slice 0x353d14 */
extern word_t FUN_00353ff4(); /* out of slice 0x353ff4 */
extern word_t FUN_003542b8(); /* out of slice 0x3542b8 */
extern word_t FUN_00354410(); /* out of slice 0x354410 */
extern word_t FUN_003544c8(); /* out of slice 0x3544c8 */
extern word_t FUN_00354744(); /* out of slice 0x354744 */
extern wpair_t FUN_003548dc(); /* out of slice 0x3548dc */
extern word_t FUN_00354998(); /* out of slice 0x354998 */
extern word_t FUN_00354f1c(); /* out of slice 0x354f1c */
extern word_t FUN_00356370(); /* out of slice 0x356370 */
extern wpair_t FUN_0035638c(); /* out of slice 0x35638c */
extern word_t FUN_00356bb0(); /* out of slice 0x356bb0 */
extern wpair_t FUN_003583e8(); /* out of slice 0x3583e8 */
extern word_t FUN_00358454(); /* out of slice 0x358454 */
extern word_t FUN_00359018(); /* out of slice 0x359018 */
extern word_t FUN_003593c0(); /* out of slice 0x3593c0 */
extern word_t FUN_00359af8(); /* out of slice 0x359af8 */
extern word_t FUN_0035a8d0(); /* out of slice 0x35a8d0 */
extern word_t FUN_0035a9b0(); /* out of slice 0x35a9b0 */
extern word_t FUN_0035b67c(); /* out of slice 0x35b67c */
extern word_t FUN_00365b6c(); /* out of slice 0x365b6c */
extern wpair_t FUN_0036986c(); /* out of slice 0x36986c */
extern wpair_t FUN_0036993c(); /* out of slice 0x36993c */
extern word_t FUN_0036a940(); /* out of slice 0x36a940 */
extern word_t FUN_0036a9a0(); /* out of slice 0x36a9a0 */
extern word_t FUN_0036b118(); /* out of slice 0x36b118 */
extern wpair_t FUN_0036b270(); /* out of slice 0x36b270 */
extern word_t FUN_0036b588(); /* out of slice 0x36b588 */
extern word_t FUN_0036b6ac(); /* out of slice 0x36b6ac */
extern word_t FUN_003722e4(); /* out of slice 0x3722e4 */
extern word_t FUN_0037233c(); /* out of slice 0x37233c */
extern word_t FUN_00376820(); /* out of slice 0x376820 */
extern wpair_t FUN_00377824(); /* out of slice 0x377824 */
extern wpair_t FUN_00377bec(); /* out of slice 0x377bec */
extern word_t FUN_00377dcc(); /* out of slice 0x377dcc */
extern word_t FUN_003a25d4(); /* out of slice 0x3a25d4 */
extern word_t FUN_003a25e0(); /* out of slice 0x3a25e0 */
extern word_t FUN_003a261c(); /* out of slice 0x3a261c */
extern word_t FUN_0040668c(); /* out of slice 0x40668c */
extern word_t FUN_00407300(); /* out of slice 0x407300 */
extern word_t FUN_00407ab8(); /* out of slice 0x407ab8 */
extern word_t FUN_00407eac(); /* out of slice 0x407eac */
extern word_t FUN_00407ed0(); /* out of slice 0x407ed0 */
extern word_t FUN_004127b4(); /* out of slice 0x4127b4 */
extern word_t FUN_004176bc(); /* out of slice 0x4176bc */
extern word_t FUN_00417aa0(); /* out of slice 0x417aa0 */
extern word_t FUN_0041a0dc(); /* out of slice 0x41a0dc */
extern word_t FUN_0041a868(); /* out of slice 0x41a868 */
extern word_t FUN_0041bfb4(); /* out of slice 0x41bfb4 */
extern word_t FUN_0041c1d8(); /* out of slice 0x41c1d8 */
extern word_t FUN_004292ac(); /* out of slice 0x4292ac */
extern word_t FUN_0042c060(); /* out of slice 0x42c060 */
extern word_t FUN_0042c5a4(); /* out of slice 0x42c5a4 */
extern word_t FUN_0044f818(); /* out of slice 0x44f818 */
extern word_t FUN_00457a88(); /* out of slice 0x457a88 */
extern word_t FUN_00458af8(); /* out of slice 0x458af8 */
extern word_t FUN_00458b14(); /* out of slice 0x458b14 */
extern word_t FUN_00462aac(); /* out of slice 0x462aac */
extern word_t FUN_00462b6c(); /* out of slice 0x462b6c */
extern word_t FUN_004633e0(); /* out of slice 0x4633e0 */
extern word_t FUN_00463bd4(); /* out of slice 0x463bd4 */
extern wpair_t FUN_00463f94(); /* out of slice 0x463f94 */
extern word_t FUN_0046490c(); /* out of slice 0x46490c */
extern word_t FUN_00464a44(); /* out of slice 0x464a44 */
extern word_t FUN_00464ae8(); /* out of slice 0x464ae8 */
extern word_t FUN_00464b04(); /* out of slice 0x464b04 */
extern word_t FUN_00464f4c(); /* out of slice 0x464f4c */
extern word_t FUN_00465258(); /* out of slice 0x465258 */
extern word_t FUN_00465db0(); /* out of slice 0x465db0 */
extern word_t FUN_00466104(); /* out of slice 0x466104 */
extern word_t FUN_00466214(); /* out of slice 0x466214 */
extern word_t FUN_00466244(); /* out of slice 0x466244 */
extern word_t FUN_00467678(); /* out of slice 0x467678 */
extern word_t FUN_0046777c(); /* out of slice 0x46777c */
extern wpair_t FUN_00467848(); /* out of slice 0x467848 */
extern word_t FUN_00467de4(); /* out of slice 0x467de4 */
extern word_t FUN_00468c6c(); /* out of slice 0x468c6c */
extern word_t FUN_00468ce4(); /* out of slice 0x468ce4 */
extern word_t FUN_00468d98(); /* out of slice 0x468d98 */
extern word_t FUN_00468dd4(); /* out of slice 0x468dd4 */
extern word_t FUN_00468ee4(); /* out of slice 0x468ee4 */
extern word_t FUN_00469250(); /* out of slice 0x469250 */
extern word_t FUN_00469918(); /* out of slice 0x469918 */
extern word_t FUN_00469c50(); /* out of slice 0x469c50 */
extern word_t FUN_00469dc4(); /* out of slice 0x469dc4 */
extern word_t FUN_00469f74(); /* out of slice 0x469f74 */
extern wpair_t FUN_0046a1b0(); /* out of slice 0x46a1b0 */
extern wpair_t FUN_0046a368(); /* out of slice 0x46a368 */
extern word_t FUN_0046a5c8(); /* out of slice 0x46a5c8 */
extern word_t FUN_0047c948(); /* out of slice 0x47c948 */
extern word_t FUN_0047c9d4(); /* out of slice 0x47c9d4 */
extern word_t FUN_0047ca18(); /* out of slice 0x47ca18 */
extern word_t FUN_0047cadc(); /* out of slice 0x47cadc */
extern word_t FUN_0047cc98(); /* out of slice 0x47cc98 */
extern word_t FUN_0047dee8(); /* out of slice 0x47dee8 */
extern word_t FUN_0047dfc4(); /* out of slice 0x47dfc4 */
extern word_t FUN_0047e5dc(); /* out of slice 0x47e5dc */
extern word_t FUN_0047ea18(); /* out of slice 0x47ea18 */
extern word_t FUN_00481320(); /* out of slice 0x481320 */
extern wpair_t FUN_004816b4(); /* out of slice 0x4816b4 */
extern word_t FUN_00481780(); /* out of slice 0x481780 */
extern word_t FUN_0048185c(); /* out of slice 0x48185c */
extern word_t FUN_004818d8(); /* out of slice 0x4818d8 */
extern word_t FUN_00481918(); /* out of slice 0x481918 */
extern word_t FUN_004819ac(); /* out of slice 0x4819ac */
extern word_t FUN_00481a38(); /* out of slice 0x481a38 */
extern wpair_t FUN_00481ac4(); /* out of slice 0x481ac4 */
extern word_t FUN_00481b40(); /* out of slice 0x481b40 */
extern word_t FUN_00481b9c(); /* out of slice 0x481b9c */
extern word_t FUN_0048525c(); /* out of slice 0x48525c */
extern word_t FUN_0048d694(); /* out of slice 0x48d694 */
extern word_t FUN_0048ee9c(); /* out of slice 0x48ee9c */
extern word_t FUN_0048ef24(); /* out of slice 0x48ef24 */
extern word_t FUN_0049490c(); /* out of slice 0x49490c */
extern word_t FUN_004950f0(); /* out of slice 0x4950f0 */
extern word_t FUN_00496f58(); /* out of slice 0x496f58 */
extern word_t FUN_004974ac(); /* out of slice 0x4974ac */
extern word_t FUN_004974ec(); /* out of slice 0x4974ec */
extern wpair_t FUN_00497504(); /* out of slice 0x497504 */
extern word_t FUN_004979bc(); /* out of slice 0x4979bc */
extern word_t FUN_004979d4(); /* out of slice 0x4979d4 */
extern word_t FUN_004979f8(); /* out of slice 0x4979f8 */
extern word_t FUN_004982ac(); /* out of slice 0x4982ac */
extern word_t FUN_00498328(); /* out of slice 0x498328 */
extern word_t FUN_004985b4(); /* out of slice 0x4985b4 */
extern word_t FUN_004985e0(); /* out of slice 0x4985e0 */
extern word_t FUN_00498708(); /* out of slice 0x498708 */
extern word_t FUN_00498ad4(); /* out of slice 0x498ad4 */
extern word_t FUN_00498b28(); /* out of slice 0x498b28 */
extern word_t FUN_00498b7c(); /* out of slice 0x498b7c */
extern word_t FUN_00498bdc(); /* out of slice 0x498bdc */
extern word_t FUN_00498c1c(); /* out of slice 0x498c1c */
extern word_t FUN_00498c54(); /* out of slice 0x498c54 */
extern word_t FUN_00498c6c(); /* out of slice 0x498c6c */
extern word_t FUN_00498c84(); /* out of slice 0x498c84 */
extern word_t FUN_00498e50(); /* out of slice 0x498e50 */
extern word_t FUN_00498f0c(); /* out of slice 0x498f0c */
extern word_t FUN_00498fd0(); /* out of slice 0x498fd0 */
extern word_t FUN_00499094(); /* out of slice 0x499094 */
extern word_t FUN_00499158(); /* out of slice 0x499158 */
extern word_t FUN_0049938c(); /* out of slice 0x49938c */
extern word_t FUN_00499450(); /* out of slice 0x499450 */
extern word_t FUN_00499a0c(); /* out of slice 0x499a0c */
extern wpair_t FUN_00499f0c(); /* out of slice 0x499f0c */
extern word_t FUN_00499fcc(); /* out of slice 0x499fcc */
extern word_t FUN_0049a4a4(); /* out of slice 0x49a4a4 */
extern word_t FUN_0049a4b8(); /* out of slice 0x49a4b8 */
extern word_t FUN_0049a51c(); /* out of slice 0x49a51c */
extern word_t FUN_0049a550(); /* out of slice 0x49a550 */
extern word_t FUN_0049a644(); /* out of slice 0x49a644 */
extern word_t FUN_0049a758(); /* out of slice 0x49a758 */
extern word_t FUN_0049aa14(); /* out of slice 0x49aa14 */
extern word_t FUN_0049ab00(); /* out of slice 0x49ab00 */
extern wpair_t FUN_0049c0e4(); /* out of slice 0x49c0e4 */
extern word_t FUN_0049c850(); /* out of slice 0x49c850 */
extern word_t FUN_0049ca2c(); /* out of slice 0x49ca2c */
extern word_t FUN_0049ca44(); /* out of slice 0x49ca44 */
extern word_t FUN_0049df0c(); /* out of slice 0x49df0c */
extern word_t FUN_0049df18(); /* out of slice 0x49df18 */
extern word_t FUN_0049e2d4(); /* out of slice 0x49e2d4 */
extern word_t FUN_0049e2f0(); /* out of slice 0x49e2f0 */
extern word_t FUN_0049fcf8(); /* out of slice 0x49fcf8 */
extern word_t FUN_0049fd10(); /* out of slice 0x49fd10 */
extern word_t FUN_004a2fa8(); /* out of slice 0x4a2fa8 */
extern word_t FUN_004a3038(); /* out of slice 0x4a3038 */
extern word_t FUN_004a30d4(); /* out of slice 0x4a30d4 */
extern word_t FUN_004a32c4(); /* out of slice 0x4a32c4 */
extern word_t FUN_004a32ec(); /* out of slice 0x4a32ec */
extern word_t FUN_004a3318(); /* out of slice 0x4a3318 */
extern word_t FUN_004a3340(); /* out of slice 0x4a3340 */
extern word_t FUN_004a3368(); /* out of slice 0x4a3368 */
extern word_t FUN_004a3390(); /* out of slice 0x4a3390 */
extern word_t FUN_004a369c(); /* out of slice 0x4a369c */
extern word_t FUN_004a36c4(); /* out of slice 0x4a36c4 */
extern word_t FUN_004a36d4(); /* out of slice 0x4a36d4 */
extern word_t FUN_004a36fc(); /* out of slice 0x4a36fc */
extern word_t FUN_004a372c(); /* out of slice 0x4a372c */
extern word_t FUN_004a3774(); /* out of slice 0x4a3774 */
extern word_t FUN_004a38c8(); /* out of slice 0x4a38c8 */
extern word_t FUN_004a3918(); /* out of slice 0x4a3918 */
extern word_t FUN_004a3940(); /* out of slice 0x4a3940 */
extern word_t FUN_004a3950(); /* out of slice 0x4a3950 */
extern word_t FUN_004a39dc(); /* out of slice 0x4a39dc */
extern word_t FUN_004a3a94(); /* out of slice 0x4a3a94 */
extern word_t FUN_004a4a44(); /* out of slice 0x4a4a44 */
extern word_t FUN_004a4a74(); /* out of slice 0x4a4a74 */
extern word_t FUN_004a4b14(); /* out of slice 0x4a4b14 */
extern word_t FUN_004aa370(); /* out of slice 0x4aa370 */
extern word_t FUN_004aa3e4(); /* out of slice 0x4aa3e4 */
extern word_t FUN_004aa44c(); /* out of slice 0x4aa44c */
extern word_t FUN_004aa464(); /* out of slice 0x4aa464 */
extern word_t FUN_004aa47c(); /* out of slice 0x4aa47c */
extern word_t FUN_004aa494(); /* out of slice 0x4aa494 */
extern word_t FUN_004aa4ac(); /* out of slice 0x4aa4ac */
extern word_t FUN_004aa4e0(); /* out of slice 0x4aa4e0 */
extern word_t FUN_004aa4fc(); /* out of slice 0x4aa4fc */
extern word_t FUN_004aa580(); /* out of slice 0x4aa580 */
extern word_t FUN_004aa594(); /* out of slice 0x4aa594 */
extern word_t FUN_004aa5ac(); /* out of slice 0x4aa5ac */
extern word_t FUN_004aa5c4(); /* out of slice 0x4aa5c4 */
extern wpair_t FUN_004aa5dc(); /* out of slice 0x4aa5dc */
extern word_t FUN_004aa610(); /* out of slice 0x4aa610 */
extern word_t FUN_004aa67c(); /* out of slice 0x4aa67c */
extern word_t FUN_004aa6a8(); /* out of slice 0x4aa6a8 */
extern word_t FUN_004aa6c4(); /* out of slice 0x4aa6c4 */
extern word_t FUN_004aa6d8(); /* out of slice 0x4aa6d8 */
extern word_t FUN_004aa720(); /* out of slice 0x4aa720 */
extern word_t FUN_004aa75c(); /* out of slice 0x4aa75c */
extern word_t FUN_004aa770(); /* out of slice 0x4aa770 */
extern word_t FUN_004aa780(); /* out of slice 0x4aa780 */
extern word_t FUN_004aa7a8(); /* out of slice 0x4aa7a8 */
extern word_t FUN_004aa7fc(); /* out of slice 0x4aa7fc */
extern word_t FUN_004aa80c(); /* out of slice 0x4aa80c */
extern word_t FUN_004aa878(); /* out of slice 0x4aa878 */
extern word_t FUN_004aa890(); /* out of slice 0x4aa890 */
extern word_t FUN_004aa8f0(); /* out of slice 0x4aa8f0 */
extern word_t FUN_004aa938(); /* out of slice 0x4aa938 */
extern word_t FUN_004aa94c(); /* out of slice 0x4aa94c */
extern word_t FUN_004aa95c(); /* out of slice 0x4aa95c */
extern word_t FUN_004aa970(); /* out of slice 0x4aa970 */
extern word_t FUN_004aa9c0(); /* out of slice 0x4aa9c0 */
extern word_t FUN_004aa9d0(); /* out of slice 0x4aa9d0 */
extern word_t FUN_004aa9e8(); /* out of slice 0x4aa9e8 */
extern word_t FUN_004aaa38(); /* out of slice 0x4aaa38 */
extern word_t FUN_004aaa48(); /* out of slice 0x4aaa48 */
extern word_t FUN_004aaa9c(); /* out of slice 0x4aaa9c */
extern word_t FUN_004aaae0(); /* out of slice 0x4aaae0 */
extern word_t FUN_004aab1c(); /* out of slice 0x4aab1c */
extern word_t FUN_004aab88(); /* out of slice 0x4aab88 */
extern word_t FUN_004aabe4(); /* out of slice 0x4aabe4 */
extern word_t FUN_004aabf4(); /* out of slice 0x4aabf4 */
extern word_t FUN_004aac04(); /* out of slice 0x4aac04 */
extern word_t FUN_004aac40(); /* out of slice 0x4aac40 */
extern word_t FUN_004aac68(); /* out of slice 0x4aac68 */
extern word_t FUN_004aac78(); /* out of slice 0x4aac78 */
extern word_t FUN_004aacb0(); /* out of slice 0x4aacb0 */
extern word_t FUN_004aace0(); /* out of slice 0x4aace0 */
extern word_t FUN_004aacf8(); /* out of slice 0x4aacf8 */
extern word_t FUN_004aad30(); /* out of slice 0x4aad30 */
extern word_t FUN_004aad44(); /* out of slice 0x4aad44 */
extern word_t FUN_004aad54(); /* out of slice 0x4aad54 */
extern word_t FUN_004aad6c(); /* out of slice 0x4aad6c */
extern word_t FUN_004aad84(); /* out of slice 0x4aad84 */
extern word_t FUN_004aae2c(); /* out of slice 0x4aae2c */
extern word_t FUN_004aae98(); /* out of slice 0x4aae98 */
extern word_t FUN_004aaee8(); /* out of slice 0x4aaee8 */
extern word_t FUN_004aaf08(); /* out of slice 0x4aaf08 */
extern word_t FUN_004aaf38(); /* out of slice 0x4aaf38 */
extern word_t FUN_004aaf58(); /* out of slice 0x4aaf58 */
extern wpair_t FUN_004aaf9c(); /* out of slice 0x4aaf9c */
extern word_t FUN_004aafac(); /* out of slice 0x4aafac */
extern word_t FUN_004aaffc(); /* out of slice 0x4aaffc */
extern word_t FUN_004ab018(); /* out of slice 0x4ab018 */
extern word_t FUN_004ab064(); /* out of slice 0x4ab064 */
extern word_t FUN_004ab0e0(); /* out of slice 0x4ab0e0 */
extern word_t FUN_004ab0f0(); /* out of slice 0x4ab0f0 */
extern word_t FUN_004ab164(); /* out of slice 0x4ab164 */
extern word_t FUN_004ab18c(); /* out of slice 0x4ab18c */
extern word_t FUN_004ab1a0(); /* out of slice 0x4ab1a0 */
extern word_t FUN_004ab1dc(); /* out of slice 0x4ab1dc */
extern word_t FUN_004ab224(); /* out of slice 0x4ab224 */
extern word_t FUN_004ab248(); /* out of slice 0x4ab248 */
extern word_t FUN_004ab260(); /* out of slice 0x4ab260 */
extern word_t FUN_004ab278(); /* out of slice 0x4ab278 */
extern word_t FUN_004ab288(); /* out of slice 0x4ab288 */
extern word_t FUN_004ab2b8(); /* out of slice 0x4ab2b8 */
extern word_t FUN_004ab2e8(); /* out of slice 0x4ab2e8 */
extern word_t FUN_004ab2f8(); /* out of slice 0x4ab2f8 */
extern word_t FUN_004ab310(); /* out of slice 0x4ab310 */
extern word_t FUN_004ab31c(); /* out of slice 0x4ab31c */
extern word_t FUN_004ab328(); /* out of slice 0x4ab328 */
extern word_t FUN_004ab334(); /* out of slice 0x4ab334 */
extern word_t FUN_004ab344(); /* out of slice 0x4ab344 */
extern word_t FUN_004ab394(); /* out of slice 0x4ab394 */
extern word_t FUN_004ab3f4(); /* out of slice 0x4ab3f4 */
extern word_t FUN_004ab420(); /* out of slice 0x4ab420 */
extern word_t FUN_004ab430(); /* out of slice 0x4ab430 */
extern word_t FUN_004ab448(); /* out of slice 0x4ab448 */
extern word_t FUN_004ab478(); /* out of slice 0x4ab478 */
extern word_t FUN_004ab484(); /* out of slice 0x4ab484 */
extern word_t FUN_004ab490(); /* out of slice 0x4ab490 */
extern word_t FUN_004ab49c(); /* out of slice 0x4ab49c */
extern word_t FUN_004ab4e8(); /* out of slice 0x4ab4e8 */
extern word_t FUN_004ab510(); /* out of slice 0x4ab510 */
extern wpair_t FUN_004ab55c(); /* out of slice 0x4ab55c */
extern word_t FUN_004ab568(); /* out of slice 0x4ab568 */
extern word_t FUN_004ab5b0(); /* out of slice 0x4ab5b0 */
extern word_t FUN_004ab5c8(); /* out of slice 0x4ab5c8 */
extern word_t FUN_004ab5d4(); /* out of slice 0x4ab5d4 */
extern wpair_t FUN_004ab618(); /* out of slice 0x4ab618 */
extern word_t FUN_004ab624(); /* out of slice 0x4ab624 */
extern word_t FUN_004ab630(); /* out of slice 0x4ab630 */
extern word_t FUN_004ab644(); /* out of slice 0x4ab644 */
extern word_t FUN_004ab6ac(); /* out of slice 0x4ab6ac */
extern word_t FUN_004ab6b8(); /* out of slice 0x4ab6b8 */
extern word_t FUN_004ab770(); /* out of slice 0x4ab770 */
extern word_t FUN_004ab7ac(); /* out of slice 0x4ab7ac */
extern word_t FUN_004ab7e0(); /* out of slice 0x4ab7e0 */
extern word_t FUN_004ab7f0(); /* out of slice 0x4ab7f0 */
extern word_t FUN_004ab800(); /* out of slice 0x4ab800 */
extern word_t FUN_004ab858(); /* out of slice 0x4ab858 */
extern word_t FUN_004ab890(); /* out of slice 0x4ab890 */
extern word_t FUN_004ab8ac(); /* out of slice 0x4ab8ac */
extern word_t FUN_004ab910(); /* out of slice 0x4ab910 */
extern wpair_t FUN_004ab980(); /* out of slice 0x4ab980 */
extern word_t FUN_004ab98c(); /* out of slice 0x4ab98c */
extern word_t FUN_004ab998(); /* out of slice 0x4ab998 */
extern word_t FUN_004ab9b0(); /* out of slice 0x4ab9b0 */
extern word_t FUN_004ab9bc(); /* out of slice 0x4ab9bc */
extern word_t FUN_004ab9ec(); /* out of slice 0x4ab9ec */
extern word_t FUN_004aba28(); /* out of slice 0x4aba28 */
extern word_t FUN_004aba88(); /* out of slice 0x4aba88 */
extern word_t FUN_004abaa0(); /* out of slice 0x4abaa0 */
extern word_t FUN_004abaac(); /* out of slice 0x4abaac */
extern word_t FUN_004abacc(); /* out of slice 0x4abacc */
extern word_t FUN_004abafc(); /* out of slice 0x4abafc */
extern word_t FUN_004abb1c(); /* out of slice 0x4abb1c */
extern word_t FUN_004abb28(); /* out of slice 0x4abb28 */
extern word_t FUN_004abb58(); /* out of slice 0x4abb58 */
extern word_t FUN_004abb8c(); /* out of slice 0x4abb8c */
extern word_t FUN_004abbb8(); /* out of slice 0x4abbb8 */
extern word_t FUN_004abc0c(); /* out of slice 0x4abc0c */
extern word_t FUN_004abc18(); /* out of slice 0x4abc18 */
extern word_t FUN_004abc44(); /* out of slice 0x4abc44 */
extern word_t FUN_004abc98(); /* out of slice 0x4abc98 */
extern word_t FUN_004abcb4(); /* out of slice 0x4abcb4 */
extern word_t FUN_004abd04(); /* out of slice 0x4abd04 */
extern word_t FUN_004abd64(); /* out of slice 0x4abd64 */
extern word_t FUN_004abd70(); /* out of slice 0x4abd70 */
extern word_t FUN_004abd90(); /* out of slice 0x4abd90 */
extern word_t FUN_004abd9c(); /* out of slice 0x4abd9c */
extern word_t FUN_004abdb8(); /* out of slice 0x4abdb8 */
extern word_t FUN_004abe68(); /* out of slice 0x4abe68 */
extern word_t FUN_004abe84(); /* out of slice 0x4abe84 */
extern word_t FUN_004abe90(); /* out of slice 0x4abe90 */
extern word_t FUN_004abea0(); /* out of slice 0x4abea0 */
extern word_t FUN_004abf10(); /* out of slice 0x4abf10 */
extern word_t FUN_004abf20(); /* out of slice 0x4abf20 */
extern word_t FUN_004abf30(); /* out of slice 0x4abf30 */
extern word_t FUN_004abf40(); /* out of slice 0x4abf40 */
extern word_t FUN_004abf5c(); /* out of slice 0x4abf5c */
extern word_t FUN_004abf6c(); /* out of slice 0x4abf6c */
extern word_t FUN_004abfb8(); /* out of slice 0x4abfb8 */
extern word_t FUN_004abfc8(); /* out of slice 0x4abfc8 */
extern word_t FUN_004abff8(); /* out of slice 0x4abff8 */
extern word_t FUN_004ac034(); /* out of slice 0x4ac034 */
extern word_t FUN_004ac06c(); /* out of slice 0x4ac06c */
extern word_t FUN_004ac088(); /* out of slice 0x4ac088 */
extern word_t FUN_004ac0a4(); /* out of slice 0x4ac0a4 */
extern word_t FUN_004ac0c0(); /* out of slice 0x4ac0c0 */
extern word_t FUN_004ac114(); /* out of slice 0x4ac114 */
extern word_t FUN_004ac120(); /* out of slice 0x4ac120 */
extern word_t FUN_004ac12c(); /* out of slice 0x4ac12c */
extern word_t FUN_004ac138(); /* out of slice 0x4ac138 */
extern word_t FUN_004ac150(); /* out of slice 0x4ac150 */
extern word_t FUN_004ac15c(); /* out of slice 0x4ac15c */
extern wpair_t FUN_004ac180(); /* out of slice 0x4ac180 */
extern word_t FUN_004ac198(); /* out of slice 0x4ac198 */
extern word_t FUN_004ac1a4(); /* out of slice 0x4ac1a4 */
extern word_t FUN_004ac1e0(); /* out of slice 0x4ac1e0 */
extern word_t FUN_004ac1f8(); /* out of slice 0x4ac1f8 */
extern word_t FUN_004ac210(); /* out of slice 0x4ac210 */
extern word_t FUN_004ac2a0(); /* out of slice 0x4ac2a0 */
extern word_t FUN_004ac2ac(); /* out of slice 0x4ac2ac */
extern word_t FUN_004ac2b8(); /* out of slice 0x4ac2b8 */
extern word_t FUN_004ac2d0(); /* out of slice 0x4ac2d0 */
extern word_t FUN_004ac2dc(); /* out of slice 0x4ac2dc */
extern word_t FUN_004ac33c(); /* out of slice 0x4ac33c */
extern word_t FUN_004ac360(); /* out of slice 0x4ac360 */
extern word_t FUN_004ac36c(); /* out of slice 0x4ac36c */
extern word_t FUN_004ac44c(); /* out of slice 0x4ac44c */
extern word_t FUN_004ac4b8(); /* out of slice 0x4ac4b8 */
extern word_t FUN_004ac508(); /* out of slice 0x4ac508 */
extern word_t FUN_004ac520(); /* out of slice 0x4ac520 */
extern word_t FUN_004ac52c(); /* out of slice 0x4ac52c */
extern word_t FUN_004ac594(); /* out of slice 0x4ac594 */
extern word_t FUN_004ac5b4(); /* out of slice 0x4ac5b4 */
extern word_t FUN_004ac5dc(); /* out of slice 0x4ac5dc */
extern word_t FUN_004ac60c(); /* out of slice 0x4ac60c */
extern word_t FUN_004ac61c(); /* out of slice 0x4ac61c */
extern word_t FUN_004ac628(); /* out of slice 0x4ac628 */
extern word_t FUN_004ac634(); /* out of slice 0x4ac634 */
extern word_t FUN_004ac640(); /* out of slice 0x4ac640 */
extern word_t FUN_004ac68c(); /* out of slice 0x4ac68c */
extern wpair_t FUN_004ac6a4(); /* out of slice 0x4ac6a4 */
extern wpair_t FUN_004ac6b0(); /* out of slice 0x4ac6b0 */
extern word_t FUN_004ac6bc(); /* out of slice 0x4ac6bc */
extern word_t FUN_004ac6e4(); /* out of slice 0x4ac6e4 */
extern word_t FUN_004ac70c(); /* out of slice 0x4ac70c */
extern word_t FUN_004ac720(); /* out of slice 0x4ac720 */
extern word_t FUN_004ac72c(); /* out of slice 0x4ac72c */
extern word_t FUN_004ac738(); /* out of slice 0x4ac738 */
extern word_t FUN_004ac778(); /* out of slice 0x4ac778 */
extern word_t FUN_004ac7a4(); /* out of slice 0x4ac7a4 */
extern word_t FUN_004ac7d4(); /* out of slice 0x4ac7d4 */
extern word_t FUN_004ac7e0(); /* out of slice 0x4ac7e0 */
extern word_t FUN_004ac7ec(); /* out of slice 0x4ac7ec */
extern word_t FUN_004ac7f8(); /* out of slice 0x4ac7f8 */
extern word_t FUN_004ac850(); /* out of slice 0x4ac850 */
extern word_t FUN_004ac85c(); /* out of slice 0x4ac85c */
extern word_t FUN_004ac89c(); /* out of slice 0x4ac89c */
extern word_t FUN_004ac8a8(); /* out of slice 0x4ac8a8 */
extern word_t FUN_004ac8b4(); /* out of slice 0x4ac8b4 */
extern word_t FUN_004ac8c0(); /* out of slice 0x4ac8c0 */
extern word_t FUN_004ac930(); /* out of slice 0x4ac930 */
extern word_t FUN_004ac954(); /* out of slice 0x4ac954 */
extern word_t FUN_004ac960(); /* out of slice 0x4ac960 */
extern word_t FUN_004ac980(); /* out of slice 0x4ac980 */
extern word_t FUN_004ac9c0(); /* out of slice 0x4ac9c0 */
extern word_t FUN_004ac9cc(); /* out of slice 0x4ac9cc */
extern word_t FUN_004ac9f8(); /* out of slice 0x4ac9f8 */
extern wpair_t FUN_004aca94(); /* out of slice 0x4aca94 */
extern word_t FUN_004acaa0(); /* out of slice 0x4acaa0 */
extern word_t FUN_004acb6c(); /* out of slice 0x4acb6c */
extern word_t FUN_004acb94(); /* out of slice 0x4acb94 */
extern word_t FUN_004acbf8(); /* out of slice 0x4acbf8 */
extern word_t FUN_004acc0c(); /* out of slice 0x4acc0c */
extern word_t FUN_004acc20(); /* out of slice 0x4acc20 */
extern word_t FUN_004acca8(); /* out of slice 0x4acca8 */
extern word_t FUN_004acce4(); /* out of slice 0x4acce4 */
extern word_t FUN_004acd08(); /* out of slice 0x4acd08 */
extern word_t FUN_004acd14(); /* out of slice 0x4acd14 */
extern word_t FUN_004b5a74(); /* out of slice 0x4b5a74 */

extern word_t DAT_004aa278;
extern word_t DAT_004baeb0;
extern word_t DAT_004baeb8;
extern word_t DAT_004c0740;
extern word_t DAT_004c2450;
extern word_t DAT_004c2458;
extern word_t DAT_004e8214;
extern word_t DAT_004e8268;
extern word_t DAT_005a3c68;
extern word_t DAT_005a3c70;
extern word_t DAT_005a3c78;
extern word_t DAT_005a3c80;
extern word_t DAT_005a4ac0;
extern word_t DAT_005a4b20;
extern word_t DAT_005a4c10;
extern word_t DAT_005a4c18;
extern word_t DAT_005a5580;
extern word_t DAT_005a5e3c;
extern word_t DAT_0060e208;
extern word_t DAT_00611b24;
extern word_t LAB_00611b34;
extern word_t DAT_00616214;
extern word_t DAT_0061628c;
extern word_t DAT_00657678;
extern word_t DAT_00657778;
extern word_t DAT_006577e0;
extern word_t DAT_00657d18;
extern word_t DAT_00657e10;
extern word_t DAT_00657e48;
extern word_t DAT_00688af0;
extern word_t _DAT_004baeb0;
extern word_t _DAT_004c2450;
extern word_t s_Anchor_endOfLine_005e2bb0;
extern word_t s_Anchor_endOfSubjectBeforeNewline_005e2b00;
extern word_t s_Anchor_firstMatchingPositionInSu_005e2a80;
extern word_t s_Anchor_startOfLine_005e2bd0;
extern word_t s_Fatal_error_005accd0;
extern word_t s_Handled_in_ByteCodeGen_or_earlie_005e2e20;
extern word_t s_Handled_in__emitCustomCharacterC_005e28c0;
extern word_t s_L4_ErrorCodeTruncated_006886a8;
extern word_t s_Removed_in__flatteningCustomChar_005e2850;
extern word_t s_TODO__Assertion_resetStartOfMatc_005e2a50;
extern word_t s__AppleInternal_Library_BuildRoot_;
extern word_t s__StringProcessing_ByteCodeGen_sw_005e2820;
extern word_t str_backreference_kind_5e2a10;
extern word_t str_backwards_assertions_5e27b0;
extern word_t str_build_root_5e2560;
extern word_t str_character_predicates_5e2660;
extern word_t str_cstring_0064c108;
extern word_t str_must_have_lower_bound_5e27d0;
extern word_t str_reset_keep_assertion_5e29f0;
extern word_t str_these_should_produce_capture_5e2780;
extern word_t uRam00000000004baeb8;
extern word_t uRam00000000004c2458;

/* ==================== SKR27 function bodies ==================== */


/* Forward declarations for all in-slice static functions (defined later in file). */
static bool sk_bcg_0046e900(void);
static bool sk_bcg_0047c0dc(void);
static byte sk_bcg_0046e6b0(word_t p1, word_t *p2, byte p3, long *p4, word_t p5, word_t p6, word_t p7);
static uint sk_bcg_00476c0c(long param_1);
static void sk_bcg_0046ae94(word_t p1, word_t p2, word_t p3, word_t p4, long p5, long p6, word_t p7, word_t p8, word_t p9);
static void sk_bcg_0046bd78(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8);
static void sk_bcg_0046c0cc(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8);
static void sk_bcg_0046c600(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8, word_t p9, word_t p10, word_t p11, word_t p12);
static void sk_bcg_0046c764(void);
static void sk_bcg_0046c828(word_t p1, word_t p2, word_t p3, word_t p4);
static void sk_bcg_0046c91c(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_0046c9f0(word_t p1, long p2);
static void sk_bcg_0046ca44(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5);
static void sk_bcg_0046cb54(void);
static void sk_bcg_0046d208(word_t p1, word_t p2, word_t p3);
static void sk_bcg_0046d670(void);
static void sk_bcg_0046d740(word_t p1);
static void sk_bcg_0046d810(long p1, word_t p2, code *p3);
static void sk_bcg_0046d860(void);
static void sk_bcg_0046d988(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8);
static void sk_bcg_0046e384(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7);
static void sk_bcg_0046e7a8(void);
static void sk_bcg_0046ea18(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5);
static void sk_bcg_0046ea44(void);
static void sk_bcg_0046ece8(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5);
static void sk_bcg_0046ef90(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5);
static void sk_bcg_0046f2f0(word_t param_1);
static void sk_bcg_0046f334(word_t param_1);
static void sk_bcg_0046f344(void);
static void sk_bcg_0046f37c(void);
static void sk_bcg_0046f3c8(wpair_t *out, word_t p2, word_t p3, word_t p4);
static void sk_bcg_0046f4cc(wpair_t *out, word_t *in2, word_t *in3);
static void sk_bcg_0046f510(wpair_t *out, word_t *in2, word_t p3);
static void sk_bcg_0046f54c(word_t p1, word_t p2, word_t p3, word_t p4);
static void sk_bcg_0046f820(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_bcg_0046fb9c(word_t param_1, word_t param_2, word_t param_3);
static void sk_bcg_0046feb0(word_t inreg);
static void sk_bcg_004700d4(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5);
static void sk_bcg_00470298(word_t inreg);
static void sk_bcg_0047042c(void);
static void sk_bcg_00470644(word_t p1, word_t p2, word_t p3, word_t p4);
static void sk_bcg_00470998(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00470ae4(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00470c28(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00470d88(void);
static void sk_bcg_00470ebc(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00470ff8(word_t p1, word_t p2, long p3);
static void sk_bcg_0047153c(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00471644(word_t p1, word_t p2, word_t p3, long param_4, code *param_5, word_t p6, word_t p7, word_t p8, word_t p9, word_t param_10);
static void sk_bcg_00471aec(word_t p1, word_t p2, word_t p3);
static void sk_bcg_00471c14(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8, word_t p9, word_t p10, word_t p11, word_t p12);
static void sk_bcg_00471cfc(void);
static void sk_bcg_00471e78(void);
static void sk_bcg_00471f20(void);
static void sk_bcg_004720b8(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_bcg_0047277c(void);
static void sk_bcg_00472974(word_t param_1, word_t param_2, long param_3, word_t param_4, code *param_5);
static void sk_bcg_00472f00(void);
static void sk_bcg_00472f04(void);
static void sk_bcg_00472f44(void);
static void sk_bcg_004730f0(long param_1, word_t param_2, unsigned long param_3, word_t param_4, code *param_5);
static void sk_bcg_00473244(word_t param_1, word_t param_2, unsigned long param_3, unsigned long param_4);
static void sk_bcg_00474fe8(long *param_1);
static void sk_bcg_00475544(void);
static void sk_bcg_00475bf4(void);
static void sk_bcg_00475c7c(void);
static void sk_bcg_00475cf8(void);
static void sk_bcg_00475e14(void);
static void sk_bcg_00476518(void);
static void sk_bcg_004765b0(void);
static void sk_bcg_004766ec(long param_1);
static void sk_bcg_0047684c(u64 param_1);
static void sk_bcg_00476c28(byte *param_1, byte *param_2);
static void sk_bcg_00476c58(u64 param_1, word_t param_2);
static void sk_bcg_00476dd0(long param_1, word_t param_2);
static void sk_bcg_00476e18(u64 param_1, u64 param_2, uint param_3);
static void sk_bcg_00476e74(long param_1);
static void sk_bcg_00476fd0(word_t p1, word_t p2, word_t p3, word_t p4);
static void sk_bcg_004773a8(long p1, word_t p2, word_t p3, code *size_fn, code *emit_fn, code *finalize_fn);
static void sk_bcg_00477494(word_t index);
static void sk_bcg_00477504(void);
static void sk_bcg_00477590(word_t p1, long p2);
static void sk_bcg_004775d0(void);
static void sk_bcg_004776ec(word_t p1, word_t p2, long p3, long p4, word_t p5);
static void sk_bcg_00477e10(void);
static void sk_bcg_00478110(word_t vec, word_t val, word_t flag);
static void sk_bcg_00478a98(void);
static void sk_bcg_004795b0(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_bcg_00479c18(void);
static void sk_bcg_00479fe4(void);
static void sk_bcg_0047a258(void);
static void sk_bcg_0047aa0c(void);
static void sk_bcg_0047b844(void);
static void sk_bcg_0047bcc8(void);
static void sk_bcg_0047bd74(void);
static void sk_bcg_0047be1c(word_t param_1, word_t param_2, unsigned int param_3);
static word_t sk_bcg_0047c1b0(word_t p1);
static void sk_bcg_0047c3a4(void);
static void sk_bcg_0047c474(void);
static void sk_bcg_0047c4e4(word_t param_1, word_t param_2);
static word_t sk_bcg_0046df0c(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8);
static word_t sk_bcg_0046e038(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static word_t sk_bcg_0046e128(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8, word_t p9, word_t p10);
static word_t sk_bcg_0046e274(void);
static word_t sk_bcg_004769a4(void);
static word_t sk_bcg_00476d44(long param_1);
static word_t sk_bcg_00476e94(word_t ctx, word_t selector);
static word_t sk_bcg_004772d0(void);
static word_t sk_bcg_00477694(long vec, word_t sel);
static word_t sk_bcg_004776c4(long vec);
static word_t sk_bcg_00477e8c(word_t desc);
static wpair_t sk_bcg_0046c4e0(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7);
static wpair_t sk_bcg_0046f298(word_t p1, word_t p2, long p3);
static wpair_t sk_bcg_0046f3f4(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static wpair_t sk_bcg_0046f474(word_t obj, word_t p2, word_t p3, word_t p4, word_t p5);
static wpair_t sk_bcg_004730e4(word_t param_1, word_t param_2, long param_3);
static wpair_t sk_bcg_004731b8(long param_1, long param_2);
static wpair_t sk_bcg_00476cd4(word_t param_1, word_t param_2);
static wpair_t sk_bcg_00476d88(long param_1);
static wpair_t sk_bcg_00477338(long delta, word_t vec);


/* FUN_0046ae94 @ 0x0046ae94   (est. sk_bcg_0046ae94)
 * Ghidra: void sk_bcg_0046ae94(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4,
 *                           long p5,long p6,ulong p7,undefined8 p8)
 * Regex ByteCodeGen: builds/emits a matching instruction into the bytecode stream.
 * It wires a freshly-created "consumer" object (lVar6) whose method table is read
 * from param_6/param_7 metadata, then walks the parsed-AST node tree via a series
 * of FUN_0046a1b0 / FUN_0046ab9b0-style compile steps, using tag/range checks
 * (value >> 0xe comparisons) as fail-closed traps. On success it flushes the
 * assembled program through the indirect method slots (lVar18/lVar19 +0x10/+8).
 * Confidence: medium   Notes: SUB_54ffff60f100041f masked trampoline; many
 * FUN_003a25d4(release) calls; thunk_FUN_002b74c0. */
static void sk_bcg_0046ae94(word_t p1, word_t p2, word_t p3, word_t p4,
                            long p5, long p6, word_t p7, word_t p8, word_t p9)
{
    word_t r2;             /* x1ret */
    word_t r3;
    word_t uvar7, uvar8, uvar9;
    word_t uvar10, uvar11, uvar13, uvar14, uvar15, uvar16, uvar17;
    int iret;
    int iret2;
    long lvar6;
    long lvar18, lvar19, lvar20;
    word_t *pstack12;      /* puVar12 */
    wpair_t pair21, pair22, pair23;
    word_t outword, consumer, l_c0;
    long l90;
    word_t l88, l68, l50, l48, l28;
    word_t ustack_80, ustack_70, ustack_60, ustack_40, ustack_30, ustack_20, ustack_10;
    word_t l78, l38, l18;
    /* in60/68/70; auStack_8 */

    pair21 = FUN_0008e518();
    lvar6 = (long)FUN_00027754(p8);
    FUN_004aac68();
    FUN_00077894();
    uvar7 = FUN_00377824().lo;
    FUN_000a6f88();
    FUN_0007c1a4();
    sk_svc_call();                       /* masked self-modifying/trampoline fn SUB_54ffff60f100041f */
    FUN_00350428();
    FUN_003509a4();
    FUN_004ac8b4();
    FUN_00100efc();
    FUN_0035053c();
    uvar8 = FUN_00377bec().lo;
    FUN_004974ec(0xff, uvar7);
    FUN_004aa970();
    uvar9 = FUN_00497504().lo;
    FUN_000a6f88();
    FUN_0007c1a4();
    sk_svc_call();                       /* masked trampoline */
    FUN_00350428();
    FUN_003509a4();
    pair22 = FUN_00350530();
    uvar15 = p7;
    FUN_0037233c(pair22.lo, pair22.hi, p6, p7, 0, 0);
    FUN_000a6f88();
    FUN_0007c1a4();
    sk_svc_call();                       /* masked trampoline */
    l90 = (long)FUN_0034b460();
    iret = *(int *)(l90 + 0x30);
    lvar20 = (long)*(int *)(l90 + 0x40);
    FUN_003514a0(lvar6);
    sk_svc_call();                       /* masked trampoline */
    lvar18 = *(long *)(p6 - 8);
    (**(code **)(lvar18 + 0x10))(lvar6 + iret, pair21.lo, p6);
    lvar19 = *(long *)((long)p7 - 8);
    FUN_00351300(lvar6 + lvar20);
    sk_svc_call();                       /* masked trampoline */
    FUN_00465db0();
    iret2 = (int)FUN_00365b6c(&l28, lvar6);
    uvar13 = ustack_20;
    uvar10 = l28;
    if (iret2 == 0) {
LAB_0046b290:
        FUN_004aac04();
        iret2 = (int)FUN_004ac5dc();
        uvar11 = ustack_10;
        r3 = l18;
        uvar13 = ustack_20;
        uvar10 = l28;
        if (iret2 == 0) {
LAB_0046b538:
            FUN_00465db0();
            FUN_004ac5dc(&l68);
            iret2 = (int)FUN_004ab9b0();
            uvar10 = ustack_60;
            if (iret2 == 0) {
LAB_0046b7a4:
                FUN_004aac04();
                iret2 = (int)FUN_004ac5dc();
                if (iret2 != 0) {
                    FUN_00465db0();
                    iret2 = (int)FUN_004ab510(&l88);
                    uvar13 = ustack_80;
                    uvar10 = l88;
                    if (iret2 != 0) {
                        FUN_004aaf38();
                        iret2 = (int)FUN_004ab3f4();
                        if (iret2 == 0) {
                            FUN_003a25d4(uvar13);
                            goto LAB_0046ba28;
                        }
                        FUN_004ab624();
                        uvar11 = l48;
                        if (ustack_20 >> 0xe < l28 >> 0xe) {
                            CL4_SWBP(0x46bd64);
                        }
                        FUN_004ac0a4();
                        FUN_004aaffc();
                        uvar17 = uvar15;
                        FUN_003a25d4(ustack_10);
                        uvar14 = uvar13;
                        pair21 = FUN_0001d4f4(0xf, uvar10);
                        FUN_003a25d4(uvar13);
                        if (ustack_40 >> 0xe < uvar11 >> 0xe) {
                            CL4_SWBP(0x46bd68);
                        }
                        FUN_00350b3c();
                        uvar13 = ustack_40;
                        pair22 = FUN_002b74c0();
                        uvar10 = pair22.lo;
                        FUN_003a25d4(ustack_30);
                        FUN_004aaa48();
                        FUN_0046a1b0(pair21.lo, pair21.hi, uvar14, uvar17, uvar10, pair22.hi,
                                     uvar11, uvar13);
                        FUN_003517c0();
                        FUN_003a25d4(uvar15);
                        FUN_003a25d4(uvar17);
                        FUN_003a25d4(uvar13);
                        FUN_003513b4(0xf);
                        FUN_0001d4f4();
                        FUN_00351a50();
                        FUN_004ac9cc();
                        FUN_003a25d4(ustack_30);
                        l68 = uvar15;
                        ustack_60 = uvar17;
LAB_0046bb64:
                        l50 = uvar10;
                        uvar7 = FUN_004ac980();
                        pstack12 = &l68;
                        goto LAB_0046bb70;
                    }
LAB_0046ba28:
                    FUN_004aaf38();
                    iret2 = (int)FUN_004ab510();
                    uvar10 = l48;
                    if (iret2 != 0) {
                        FUN_00465db0();
                        iret2 = (int)FUN_004ab3f4(&l88);
                        if (iret2 != 0) {
                            if (ustack_20 >> 0xe < l28 >> 0xe) {
                                CL4_SWBP(0x46bd6c);
                            }
                            FUN_004ab624();
                            uvar13 = ustack_80;
                            FUN_004ac0a4();
                            FUN_004aaffc();
                            FUN_003a25d4(ustack_10);
                            FUN_004ac6a4();
                            if (r2 >> 0xe < uvar10 >> 0xe) {   /* x1ret */
                                CL4_SWBP(0x46bd70);
                            }
                            uvar14 = r2;
                            pair21 = FUN_002b74c0(uvar10, r2, uvar10, r2, l38, ustack_30);
                            FUN_004ac9cc(ustack_30);
                            FUN_003a25d4();
                            FUN_004abd64();
                            uvar11 = uvar13;
                            pair22 = FUN_0001d4f4();
                            FUN_003a25d4(uvar13);
                            FUN_004aaa48();
                            FUN_0046a1b0(pair21.lo, pair21.hi, ustack_30, uvar10, pair22.lo,
                                         pair22.hi, uvar11, uvar14);
                            FUN_00351a50();
                            FUN_003a25d4(uvar15);
                            FUN_003a25d4(uvar10);
                            FUN_003a25d4(uvar14);
                            FUN_00350968(0xf);
                            FUN_0001d4f4();
                            FUN_004abd9c();
                            FUN_004acce4();
                            ustack_60 = ustack_30;
                            l68 = uvar11;
                            goto LAB_0046bb64;
                        }
                        FUN_003a25d4(ustack_10);
                        ustack_10 = ustack_30;
                    }
                    FUN_003a25d4(ustack_10);
                }
                FUN_00319628(lvar6);
                FUN_00351bd4(consumer, p3);
                sk_svc_call();                       /* masked trampoline */
                FUN_00469250(outword, pair21.lo, uvar7, p6, uvar8,
                             (word_t)0 /*in60*/, (word_t)0 /*in70*/);
                FUN_00350bc0((word_t)0);                 /* &auStack_8 */
                sk_svc_call(consumer, uvar7);       /* masked trampoline */
                FUN_0046a5c8((word_t)0 /*x8ret*/, outword, pair21.hi, p4, p5, uvar9,
                             l_c0, p8, 0x687b18, (word_t)0 /*in68*/);
                FUN_00350bc0(&ustack_30);
                FUN_003514e8();
                sk_svc_call();                       /* masked trampoline */
                lvar18 = -0x70;
                goto LAB_0046bd14;
            }
            FUN_004aac04();
            iret2 = (int)FUN_004ab510();
            uvar14 = ustack_10;
            uvar11 = ustack_20;
            uvar13 = l28;
            if (iret2 == 0) {
LAB_0046b668:
                FUN_004aac04();
                iret2 = (int)FUN_004ab3f4();
                uvar14 = ustack_10;
                uvar11 = ustack_20;
                uvar13 = l28;
                if (iret2 == 0) {
LAB_0046b7a0:
                    FUN_003a25d4(uvar10);
                    goto LAB_0046b7a4;
                }
                FUN_004aac78();
                iret2 = (int)FUN_004ab510();
                if (iret2 == 0) {
                    FUN_004aaf38();
                    iret2 = (int)FUN_004ab510();
                    uvar17 = l48;
                    if (iret2 == 0) {
                        FUN_003a25d4(uvar10);
                        uvar10 = uvar14;
                        goto LAB_0046b7a0;
                    }
                    pair21 = FUN_004ac6a4(0xf);
                    FUN_0001d4f4(pair21.lo, pair21.hi, uvar10);
                    FUN_004aaffc();
                    FUN_004acce4();
                    if (ustack_40 >> 0xe < uvar17 >> 0xe) {
                        CL4_SWBP(0x46bd74);
                    }
                    FUN_004ab624();
                    FUN_00352c4c(uvar17);
                    FUN_004ac738();
                    FUN_002b74c0();
                    FUN_004acbf8();
                    if (uvar11 >> 0xe < uvar13 >> 0xe) {
                        CL4_SWBP(0x46bd78);
                    }
                    FUN_00351790();
                    FUN_002b74c0();
                    uvar11 = ustack_40;
                    FUN_003517c0();
                    FUN_003a25d4(uvar14);
                    FUN_004aaa48();
                    FUN_00350a04();
                    FUN_004ac1f8();
                    FUN_0046a1b0();
                    FUN_003517c0();
                    FUN_003a25d4(uvar13);
                    FUN_003a25d4(uvar10);
                    l88 = ustack_30;
                }
                else {
                    FUN_004ab624();
                    uvar17 = l48;
                    FUN_004ac6a4(0xf);
                    FUN_0001d4f4();
                    FUN_003a25d4(uvar10);
                    uvar7 = FUN_0001d4f4(0xf, uvar17, ustack_40).lo;
                    FUN_004acbf8();
                    if (uvar11 >> 0xe < uvar13 >> 0xe) {
                        CL4_SWBP(0x46bd60);
                    }
                    pair21 = FUN_003504f4();
                    FUN_002b74c0(pair21.lo, pair21.hi, uvar13, uvar11, l18, uvar14);
                    FUN_003517c0();
                    FUN_003a25d4(uvar14);
                    FUN_004aaae0((word_t)0 /*&s10*/);
                    FUN_004ac1f8(uvar7, l18);
                    FUN_0046a1b0();
                    FUN_003517c0();
                    FUN_003a25d4(uvar15);
                    FUN_003a25d4(uvar10);
                    l88 = ustack_40;
                }
                uvar7 = FUN_003a25d4(uvar11);
                ustack_80 = p7;
            }
            else {
                FUN_004aac78();
                iret2 = (int)FUN_004ab3f4();
                if (iret2 == 0) {
                    FUN_003a25d4(uvar14);
                    goto LAB_0046b668;
                }
                FUN_004ab624();
                uvar17 = l48;
                FUN_00350548(0xf);
                FUN_0001d4f4();
                FUN_004abc98();
                FUN_003a25d4(uvar10);
                if (uvar11 >> 0xe < uvar13 >> 0xe) {
                    CL4_SWBP(0x46bd58);
                }
                pair21 = FUN_00350a70();
                FUN_004abb1c(pair21.lo, pair21.hi, uvar13, uvar11);
                FUN_002b74c0();
                FUN_00354f1c();
                uvar16 = uvar11;
                FUN_003a25d4(uvar14);
                uvar14 = ustack_40;
                pair21 = FUN_0001d4f4(0xf, uvar17);
                FUN_003a25d4(ustack_40);
                FUN_000ec044();
                FUN_004aaae0((word_t)0 /*&s20*/);
                pair22 = FUN_00351450();
                FUN_0046a1b0(pair22.lo, pair22.hi, uvar13, uvar11, pair21.lo, pair21.hi, uvar14,
                             uvar16);
                FUN_00351a50();
                FUN_003a25d4(uvar15);
                FUN_003a25d4(uvar11);
                uvar7 = FUN_003a25d4(uvar16);
                ustack_80 = uvar10;
                l88 = uvar14;
            }
            pstack12 = &l88;
        }
        else {
            FUN_004aaf38();
            iret2 = (int)FUN_004ab510();
            uvar17 = ustack_30;
            r2 = l38;   /* r2 */
            uvar14 = l48;
            if (iret2 != 0) {
                FUN_004ab1dc();
                FUN_004ab644(&l68, lvar6 + lvar20);
                iret2 = (int)FUN_00365b6c();
                if (iret2 != 0) {
                    FUN_004ab624();
                    uvar10 = l50;
                    pair21 = FUN_004ac6a4(uvar14);
                    pair21 = FUN_0046a1b0(pair21.lo, pair21.hi, r2, uvar17);
                    FUN_003a25d4(uvar11);
                    FUN_003a25d4(uvar17);
                    FUN_003a25d4(uvar10);
                    FUN_003513b4(0xf);
                    FUN_0001d4f4();
                    FUN_00351a50();
                    FUN_004ac9cc();
                    FUN_003a25d4(pair21.hi);
                    l88 = uvar10;
                    ustack_80 = uvar11;
                    ustack_70 = r3;
                    l78 = pair21.lo;
                    uvar7 = FUN_004ac980();
                    FUN_004ac44c(uvar7, &l88);
                    FUN_00350bc0((word_t)0 /*&s30*/);
                    pstack12 = (word_t *)0;   /* x8ret1 */
                    goto LAB_0046b38c;
                }
                FUN_003a25d4(uvar17);
            }
            FUN_00465db0();
            iret2 = (int)FUN_004ab510(&l68);
            uvar14 = ustack_60;
            if (iret2 == 0) {
                FUN_003a25d4(uvar11);
                goto LAB_0046b538;
            }
            FUN_00465db0();
            iret2 = (int)FUN_004ab3f4(&l88);
            if (iret2 == 0) {
                FUN_003a25d4(uvar11);
                FUN_003a25d4(uvar14);
                goto LAB_0046b538;
            }
            FUN_004ab624();
            FUN_004ab9b0();
            uvar15 = ustack_80;
            if (uvar13 >> 0xe < uvar10 >> 0xe) {
                CL4_SWBP(0x46bd5c);
            }
            FUN_003514a0(uvar10);
            pair21 = FUN_002b74c0();
            uvar17 = uvar13;
            FUN_003a25d4(uvar11);
            FUN_004abd64();
            uvar10 = uvar14;
            pair22 = FUN_0001d4f4();
            uvar11 = uvar10;
            uvar16 = uvar17;
            FUN_003a25d4(uvar14);
            FUN_00350c20(0xf);
            pair23 = FUN_0001d4f4();
            FUN_003a25d4(uvar15);
            uvar15 = uvar13;
            FUN_000ec044();
            FUN_0046a1b0(pair22.lo, pair22.hi, uvar10, uvar17, pair23.lo, pair23.hi, uvar11,
                         uvar16, p4, pair21, (word_t)0 /*x8ret2*/, uvar15);
            FUN_00351a50();
            FUN_003a25d4(uvar13);
            FUN_003a25d4(uvar17);
            FUN_003a25d4(uvar16);
            FUN_00350968(0xf);
            FUN_0001d4f4();
            FUN_004abd9c();
            FUN_004acce4();
            l48 = pair23.lo;
            uvar7 = FUN_004ac980();
            pstack12 = &l48;
        }
LAB_0046bb70:
        FUN_004ac44c(uvar7, pstack12);
        (**(code **)(lvar19 + 8))(lvar6 + lvar20, l_c0);
    }
    else {
        FUN_004aac78();
        iret2 = (int)FUN_004ab510();
        uvar11 = ustack_40;
        if (iret2 == 0) {
            FUN_003a25d4(uvar13);
            goto LAB_0046b290;
        }
        FUN_00465db0();
        FUN_004ab644(&l68, lvar6 + lvar20);
        iret2 = (int)FUN_00365b6c();
        if (iret2 == 0) {
            FUN_003a25d4(uvar13);
            FUN_003a25d4(uvar11);
            goto LAB_0046b290;
        }
        FUN_004ab624();
        FUN_004ab9b0();
        uvar17 = ustack_60;
        uvar14 = l68;
        FUN_0001d4f4(0xf, uvar10, uvar13);
        FUN_004abc98();
        FUN_004acce4();
        FUN_004abd64();
        uvar10 = uvar11;
        pair22 = FUN_0001d4f4();
        uvar13 = uvar10;
        uvar16 = uvar15;
        FUN_003a25d4(uvar11);
        FUN_00350c20(0xf);
        FUN_0001d4f4();
        FUN_004abd9c();
        FUN_003a25d4(uvar17);
        FUN_000ec044();
        FUN_004aaae0((word_t)0 /*&s20*/);
        FUN_0046a1b0(pair22.lo, pair22.hi, uvar10, uvar15, uvar14, uvar11, uvar13, uvar16);
        FUN_00351a50();
        FUN_003a25d4(pair21.hi);
        FUN_003a25d4(uvar15);
        uvar7 = FUN_003a25d4(uvar16);
        l88 = uvar14;
        ustack_80 = uvar13;
        FUN_004ac44c(uvar7, &l88, 0x6753a0);
        FUN_00350bc0((word_t)0 /*&s30*/);
        p7 = l_c0;
        pstack12 = (word_t *)0;   /* x8ret0 */
LAB_0046b38c:
        ((code)pstack12)(lvar6 + lvar20, p7);
    }
    (**(code **)(lvar18 + 8))(lvar6 + iret, p6);
    lvar18 = -0x28;
    l90 = p5;
LAB_0046bd14:
    FUN_00350bc0((long)0 + lvar18); /* &s50 stack slot */
    sk_svc_call(lvar6, l90);        /* masked trampoline */
    FUN_0008e500((word_t)0 /*x9ret*/);
    return;
}



/* FUN_0046bd78 @ 0x0046bd78   (est. sk_bcg_0046bd78)
 * Ghidra: void sk_bcg_0046bd78(undefined8 p1..p8)
 * Regex ByteCodeGen driver: allocates a consumer object (FUN_0034b0b4/003722e4),
 * builds it through the standard prologue, then on success calls FUN_0046ae94 to
 * emit the compiled bytecode into the object stream. A checked-flag (uvar7&1)
 * gates the final emit path; the else branch traps at 0x46c0cc (fail-closed).
 * Confidence: medium   Notes: SUB_54ffff60f100041f masked trampoline. */
static void sk_bcg_0046bd78(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6, word_t p7, word_t p8)
{
    long lvar5, lvar6;
    int iret;
    word_t r2, r3, r4, uvar7;
    wpair_t pair10, pair11;
    word_t x8ret, x9ret;
    long x8ret0, x8ret1, x8ret2, x8ret3;
    long x16ret, x16ret0, x16ret1;
    code *pcvar8, *pcvar9;

    pair10 = FUN_0008e518();
    r2 = FUN_00027754(p7);
    FUN_004aa770();
    FUN_003511d8();
    r3 = FUN_00377824().lo;
    r4 = FUN_0034b0b4();
    lvar5 = (long)FUN_003722e4(r4, r3, r3);
    FUN_000a6f88();
    sk_svc_call(*(word_t *)(x8ret0 + 0x40));  /* masked trampoline */
    FUN_003493c4();
    FUN_003503f8();
    sk_svc_call();                                   /* masked trampoline */
    FUN_00350464();
    FUN_0007c028();
    sk_svc_call(*(word_t *)(x8ret2 + 0x40)); /* masked trampoline */
    FUN_0034ab10();
    FUN_0034dfa4();
    sk_svc_call();                                   /* masked trampoline */
    FUN_0034ba68();
    FUN_00464f4c();
    FUN_0034be0c(r2);
    r4 = FUN_00377bec().lo;
    pair11 = FUN_00350500();
    lvar6 = (long)FUN_00310e08(pair11.lo, pair11.hi, r4);
    FUN_000a6f88();
    FUN_0007c1a4();
    sk_svc_call();                                   /* masked trampoline */
    FUN_00350428();
    FUN_0035156c(r2);
    FUN_00100efc();
    sk_svc_call();                                   /* masked trampoline */
    FUN_00351750(r2);
    FUN_00100efc();
    sk_svc_call();                                   /* masked trampoline */
    FUN_0035166c(r4);
    FUN_003508cc();
    FUN_003516b4();
    uvar7 = (word_t)sk_svc_call();                   /* masked trampoline */
    if ((uvar7 & 1) != 0) {
        pcvar8 = *(code **)(x16ret0 + 0x20);
        (*pcvar8)(x8ret1);
        (*pcvar8)(x8ret1 + *(int *)(lvar5 + 0x30));
        FUN_00351300(x9ret);
        sk_svc_call();                               /* masked trampoline */
        iret = *(int *)(lvar5 + 0x30);
        pair11 = FUN_003505e8();
        (*pcvar8)(pair11.lo, pair11.hi, r3);
        pcvar9 = *(code **)(x16ret0 + 8);
        (*pcvar9)(x9ret + iret, r3);
        FUN_00351300(*(word_t *)(x16ret + 0x20), x9ret);
        sk_svc_call();                               /* masked trampoline */
        (*pcvar8)(x8ret3 + *(int *)(lvar6 + 0x24), x9ret + *(int *)(lvar5 + 0x30), r3);
        FUN_00084174();
        (*pcvar9)();
        *(word_t *)(x8ret3 - 0x10) = (word_t)0 /*in68*/;
        *(word_t *)(x8ret3 - 0x18) = (word_t)0 /*in60*/;
        *(word_t *)(x8ret3 - 0x20) = p8;
        sk_bcg_0046ae94(x8ret, pair10.lo, pair10.hi, x8ret3, p3, p4, p5, p6, p7);
        FUN_0035084c(*(word_t *)(x16ret1 + 8));
        sk_svc_call();                               /* masked trampoline */
        FUN_0008e500(x9ret);
        return;
    }
    CL4_SWBP(0x46c0cc);                                  /* fail-closed */
}



/* FUN_0046c0cc @ 0x0046c0cc   (est. sk_bcg_0046c0cc)
 * Ghidra: void sk_bcg_0046c0cc(undefined8 p1..p8)
 * Regex ByteCodeGen emit driver, sibling of 0046bd78. Allocates the consumer,
 * emits the compiled bytecode via the object's method table (l60 +0x20/+8),
 * stores spilled args at negative offsets on the code buffer, then invokes
 * FUN_0046ae94. The checked-flag gate (uvar7&1) else-branch traps at 0x46c4e0.
 * Confidence: medium   Notes: SUB_54ffff60f100041f masked trampoline; DAT_0060e208
 * tag/range marker passed to string-build helpers. */
static void sk_bcg_0046c0cc(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6, word_t p7, word_t p8)
{
    long lvar5, lvar6, lvar1;
    word_t r2, r3, r4, uvar7;
    wpair_t pair48;          /* pair48: initial FUN_0008e518 */
    wpair_t pair10;          /* pair10: reused */
    word_t l38, l30, l98;
    long lc0, lb8, lb0, la8, la0;
    long l90, l88, l80, l78, l70, l68, l60, l58, l50;
    long x8ret0, x8ret1, x8ret2, x8ret3, x8ret4, x8ret5;
    long x9ret, x9ret0;
    long x12ret, x16ret, x16ret0, x16ret1, x16ret2;
    word_t u20;
    code *pcvar8, *pcvar9;
    code *l90c;         /* l90 as fn ptr */
    word_t x8ret;

    pair48 = FUN_0008e518();
    l38 = p8;
    l30 = p3;
    r2 = FUN_00027754(p7);
    r3 = FUN_004aa770();
    r3 = FUN_00377824(r3, r2, p4, (word_t)0 /*DAT_0060e208*/).lo;
    r4 = FUN_0034b0b4();
    FUN_004ab644(r4, r3);
    FUN_003722e4();
    l50 = (long)FUN_000a6f88();
    l58 = x16ret;
    sk_svc_call(*(word_t *)(x8ret0 + 0x40));  /* masked trampoline */
    FUN_003493c4();
    l70 = x9ret;
    FUN_003503f8();
    sk_svc_call();                                   /* masked trampoline */
    FUN_00350464();
    FUN_004ac2b8();
    FUN_0007c028();
    l60 = x16ret0;
    sk_svc_call(*(word_t *)(x8ret1 + 0x40)); /* masked trampoline */
    FUN_0034ab10();
    FUN_0034b540();
    sk_svc_call();                                   /* masked trampoline */
    FUN_00464f4c();
    pair10 = FUN_003508cc();
    r4 = FUN_00377bec(pair10.lo, pair10.hi, r3, (word_t)0 /*DAT_0060e208*/).lo;
    pair10 = FUN_0035050c();
    lvar5 = (long)FUN_00310e08(pair10.lo, pair10.hi, r4);
    FUN_000a6f88();
    l68 = x16ret1;
    FUN_0007c1a4();
    sk_svc_call();                                   /* masked trampoline */
    FUN_00350428();
    l80 = x8ret2;
    FUN_0007c028();
    sk_svc_call(*(word_t *)(x8ret3 + 0x40)); /* masked trampoline */
    FUN_000aa4ec();
    lvar6 = x9ret0 - x8ret4;
    l88 = lvar6;
    FUN_00350624();
    sk_svc_call();                                   /* masked trampoline */
    FUN_0035156c(r2);
    FUN_003510ac((long)&lc0 - x12ret);
    sk_svc_call();                                   /* masked trampoline */
    FUN_00351750(r2);
    FUN_003510ac();
    sk_svc_call();                                   /* masked trampoline */
    FUN_0007c1c4(*(word_t *)(x16ret2 + 8));
    l90c = (code *)x8ret5;                  /* l90 */
    sk_svc_call();                                   /* masked trampoline */
    FUN_0035166c(r4);
    FUN_00352ae4((long)&lc0 - x12ret);
    uvar7 = (word_t)sk_svc_call();                   /* masked trampoline */
    if ((uvar7 & 1) != 0) {
        la8 = (long)0 /*in60*/;
        la0 = (long)0 /*in68*/;
        l98 = (word_t)(x16ret2 + 8) & 0xffffffffffff | 0x4f8000000000000;
        pcvar8 = *(code **)(l60 + 0x20);
        lb0 = (long)p4;
        pair10 = FUN_00350738();
        (*pcvar8)(pair10.lo, pair10.hi, r3);
        lvar1 = l50;
        (*pcvar8)(l78 + *(int *)(l50 + 0x30));
        lb8 = lvar5;
        pair10 = FUN_000dbd0c();
        sk_svc_call(pair10.lo, pair10.hi, lvar1);    /* masked trampoline */
        lc0 = (long)*(int *)(lvar1 + 0x30);
        FUN_00351dfc(l80);
        (*pcvar8)();
        pcvar9 = *(code **)(l60 + 8);
        (*pcvar9)(l70 + lc0, r3);
        pair10 = FUN_000dbd0c(*(word_t *)(l58 + 0x20));
        sk_svc_call(pair10.lo, pair10.hi, lvar1);    /* masked trampoline */
        (*pcvar8)(l80 + *(int *)(lb8 + 0x24), l70 + *(int *)(lvar1 + 0x30), r3);
        (*pcvar9)(l70, r3);
        *(word_t *)(lvar6 - 0x10) = (word_t)la0;
        *(word_t *)(lvar6 - 0x18) = (word_t)la8;
        *(word_t *)(lvar6 - 0x20) = l38;
        sk_bcg_0046ae94(u20, pair48.lo, pair48.hi, l80, l30, lb0, p5, p6, p7);
        FUN_00100efc(*(word_t *)(l68 + 8));
        sk_svc_call();                               /* masked trampoline */
        FUN_0007c1c4();
        (*l90c)();
        FUN_0008e500(x8ret);
        return;
    }
    CL4_SWBP(0x46c4e0);                                  /* fail-closed */
}

/* FUN_0046c4e0 @ 0x0046c4e0   (est. sk_bcg_0046c4e0)
 * Ghidra: undefined1[16] sk_bcg_0046c4e0(p1..p7); returns wpair_t
 * Regex ByteCodeGen leaf: builds a 16-bit packed selector from the input
 * (param_7 tag bits -> kind nibble via >>0x38 & 0xf, and a node-flag bit
 * >>0x3b), calls FUN_0029fa0c to allocate the emitter state, then runs
 * FUN_0046a368 to append the compiled node and FUN_004a4b14 to finalize with
 * the two string metadata globals (DAT_00657e48 / DAT_005a5580). Returns the
 * assembled pair.
 * Confidence: medium   Notes: DAT_00657e48 / DAT_005a5580 string tables. */
static wpair_t sk_bcg_0046c4e0(word_t p1, word_t p2, word_t p3, word_t p4,
                               word_t p5, word_t p6, word_t p7)
{
    word_t r1, r2, r3, r4;
    word_t r5;               /* u5 */
    wpair_t pair6;
    word_t ld0, ustack_c8, ustack_c0, ustack_b8, lb0;
    word_t ustack_a8, ustack_a0, ustack_98, l90, ustack_88, ustack_80, ustack_78;
    word_t l70, ustack_68, ustack_60, ustack_58;

    r1 = p6;
    if ((p7 & 0x2000000000000000) != 0) {
        r1 = p7 >> 0x38 & 0xf;
    }
    r5 = (word_t)(p6 >> 0x3b) & 1;
    if ((p7 & 0x1000000000000000) == 0) {
        r5 = 1;
    }
    r2 = 7;
    if (r5 == 0) {
        r2 = 0xb;
    }
    r3 = p6;
    r4 = p7;
    pair6 = FUN_0029fa0c(0xf, r2 | r1 << 0x10, p6, p7);
    FUN_00468ee4(&ld0, p1, p2, pair6.lo, pair6.hi, r3, r4);
    FUN_003a25d4(r4);
    ustack_88 = ustack_c8;
    l90 = ld0;
    ustack_78 = ustack_b8;
    ustack_80 = ustack_c0;
    ustack_68 = ustack_a8;
    l70 = lb0;
    ustack_58 = ustack_98;
    ustack_60 = ustack_a0;
    pair6 = FUN_0046a368(&l90, p3, p4, p5, p6, p7);
    FUN_004a4b14(&ld0, (word_t)0 /*DAT_00657e48*/, (word_t)0 /*DAT_005a5580*/);
    return pair6;
}

/* FUN_0046c600 @ 0x0046c600   (est. sk_bcg_0046c600)
 * Ghidra: void sk_bcg_0046c600(undefined8 p1..p12)
 * Regex ByteCodeGen dispatcher: captures the current consumer state (l130 /
 * l70 via FUN_00084180), checks the tag/range ordering (>>0xe), and when
 * in-bounds routes to FUN_00469f74 to compile the next node, then closes out
 * with FUN_0046a5c8 and an indirect call on the builder's method slot +8. The
 * fail-closed trap at 0x46c764 guards the out-of-range path.
 * Confidence: medium   Notes: x9ret / x16ret indirect slots. */
static void sk_bcg_0046c600(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5,
                            word_t p6, word_t p7, word_t p8, word_t p9, word_t p10,
                            word_t p11, word_t p12)
{
    word_t r2;
    word_t l130[24];
    word_t l70[2];
    long x16ret;

    r2 = FUN_00027754(p10);
    FUN_0035156c();
    FUN_00084180(l130);
    sk_svc_call();                                   /* masked trampoline */
    FUN_00351750(r2);
    FUN_00084180(l70);
    sk_svc_call();                                   /* masked trampoline */
    if (l130[0] >> 0xe <= l70[0] >> 0xe) {
        FUN_00469f74(l130, p2, l130[0], l70[0], p4, p5, p7, p9, r2, p12);
        FUN_004aabe4();
        FUN_00351214(0xff);
        FUN_00377824();
        FUN_00352efc();
        r2 = FUN_004979bc();
        FUN_00351584(p1, l130, p3);
        FUN_0046a5c8();
        FUN_003509c8(r2);
        (**(code **)(x16ret + 8))(l130, r2);
        return;
    }
    CL4_SWBP(0x46c764);                                  /* fail-closed */
}

/* FUN_0046c764 @ 0x0046c764   (est. sk_bcg_0046c764)
 * Ghidra: void sk_bcg_0046c764(void)
 * Regex ByteCodeGen dispatch shim: reads the builder's begin/end range values
 * (via FUN_00027754 + in30/38), validates the >>0xe tag ordering,
 * then delegates to FUN_0046c600 with a 16-byte pair from FUN_00350914. The
 * out-of-order path traps at 0x46c828.
 * Confidence: medium   Notes: in30/38; x8ret/9. */
static void sk_bcg_0046c764(void)
{
    word_t r1, r3;
    wpair_t pair4;
    word_t x8ret, x9ret;

    FUN_0035300c();
    r3 = FUN_00027754((word_t)0 /*in6*/);
    FUN_0035156c();
    FUN_00100efc((word_t)0 /*&s38*/);
    sk_svc_call();                                   /* masked trampoline */
    r1 = (word_t)0 /*in38*/;
    FUN_00351750(r3);
    FUN_00100efc((word_t)0 /*&s30*/);
    sk_svc_call();                                   /* masked trampoline */
    if (r1 >> 0xe <= (word_t)0 /*in30*/ >> 0xe) {
        pair4 = FUN_00350914(x8ret);
        sk_bcg_0046c600(pair4.lo, pair4.hi, r1, 0, 0, 0, 0, 0, 0, 0, 0, 0); /* register-residue args */
        FUN_00353238(x9ret);
        return;
    }
    CL4_SWBP(0x46c828);                                  /* fail-closed */
}

/* FUN_0046c828 @ 0x0046c828   (est. sk_bcg_0046c828)
 * Ghidra: void sk_bcg_0046c828(undefined8 p1..p4)
 * Regex ByteCodeGen helper: builds a fresh pair (FUN_00350914), dispatches into
 * FUN_0046c764, and stores the result through the builder's method slot +8 with
 * p4 as an argument. Spills in_stack_00000060 at a negative buffer offset.
 * Confidence: medium   Notes: SUB_54ffff60f100041f masked trampoline; indirect
 * x16ret+8 call. */
static void sk_bcg_0046c828(word_t p1, word_t p2, word_t p3, word_t p4)
{
    word_t r1;
    wpair_t pair2;
    word_t x8ret;
    long x8ret0, x8ret1, x9ret, x16ret;

    FUN_0008e518();
    r1 = p4;
    FUN_0007c028();
    sk_svc_call(*(word_t *)(x8ret0 + 0x40));  /* masked trampoline */
    FUN_000aa4ec();
    pair2 = FUN_0007c1c4();
    sk_svc_call(pair2.lo, pair2.hi, r1);             /* masked trampoline */
    *(word_t *)((x9ret - x8ret1) - 0x10) = (word_t)0 /*in60*/;
    pair2 = FUN_00350914();
    FUN_004ab910(pair2.lo, pair2.hi, p3);
    sk_bcg_0046c764();
    (**(code **)(x16ret + 8))(x9ret - x8ret1, p4);
    FUN_0008e500(x8ret);
    return;
}

/* FUN_0046c91c @ 0x0046c91c   (est. sk_bcg_0046c91c)
 * Ghidra: void sk_bcg_0046c91c(undefined8 p1..p6)
 * Regex ByteCodeGen leaf: builds the consumer state (FUN_00084220 pair), looks
 * up/derives the builder (FUN_004aa4fc/00377824), writes param_3/param_4 into
 * the object at offsets from the metadata structure (l2 +0x24/+0x28), and
 * publishes the two halves through the builder's method slot +8.
 * Confidence: medium   Notes: x8ret/x16ret; u30. */
static void sk_bcg_0046c91c(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6)
{
    word_t r1;
    long lvar2;
    long x8ret, x16ret, x16ret0;
    word_t u30;
    wpair_t pair3;

    pair3 = FUN_00084220();
    r1 = FUN_004aa4fc();
    r1 = FUN_00377824(r1, p6, p5).lo;
    FUN_0035063c(x8ret, pair3.hi, r1);
    FUN_00468dd4();
    FUN_003509c8(p5);
    (**(code **)(x16ret + 8))(pair3.hi, p5);
    FUN_003509c8(r1);
    (**(code **)(x16ret0 + 8))(pair3.lo, r1);
    FUN_003504a0(0);
    lvar2 = (long)FUN_004979d4();
    *(word_t *)(x8ret + *(int *)(lvar2 + 0x24)) = p3;
    *(word_t *)(x8ret + *(int *)(lvar2 + 0x28)) = (word_t)(unsigned char)p4;
    FUN_00084234(u30);
    return;
}

/* FUN_0046c9f0 @ 0x0046c9f0   (est. sk_bcg_0046c9f0)
 * Ghidra: void sk_bcg_0046c9f0(undefined8 p1,long p2)
 * Regex ByteCodeGen step: advances the builder by pulling two fields from the
 * AST/metadata object (param_2 +0x18 / +0x10), re-derives the builder, then
 * dispatches param_1 through the method slot +0x10 (a jumptable dispatch that
 * the decompiler could not resolve to a single target).
 * Confidence: medium   Notes: indirect jumptable call via x16ret+0x10. */
static void sk_bcg_0046c9f0(word_t p1, long p2)
{
    long x16ret;

    FUN_004aa4fc(p2, *(word_t *)(p2 + 0x18), *(word_t *)(p2 + 0x10));
    FUN_00377824();
    FUN_00350404();
    /* indirect jumptable dispatch (unresolved target) */
    (**(code **)(x16ret + 0x10))(p1);
    return;
}

/* FUN_0046ca44 @ 0x0046ca44   (est. sk_bcg_0046ca44)
 * Ghidra: void sk_bcg_0046ca44(undefined8 p1..p5)
 * Regex ByteCodeGen leaf: allocates a consumer (FUN_004a30d4), zeroes two
 * object fields (l2 +0x2c / +0x34), derives the builder and a message string
 * (DAT_0061628c), installs a computed value via FUN_000277b8 into the +0x24
 * slot, and stores the tail fields (+0x28 / +0x30) from the 16-byte pair and the
 * param_3 byte. Closes via FUN_0007767c.
 * Confidence: medium   Notes: DAT_0061628c message string; x8ret/x16. */
static void sk_bcg_0046ca44(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    int iret;
    long lvar2;
    word_t r3, r4;
    code *pcvar5;
    long x8ret, x16ret;
    word_t u30;
    wpair_t pair6, pair7;
    unsigned int sc = (unsigned int)p3;

    pair6 = FUN_00077698();
    lvar2 = (long)FUN_004a30d4(0, p4, p5);
    *(word_t *)(x8ret + *(int *)(lvar2 + 0x2c)) = 0;
    *(word_t *)(x8ret + *(int *)(lvar2 + 0x34)) = 0;
    FUN_004aad84();
    FUN_0034e5bc();
    r3 = FUN_00377824().lo;
    FUN_004ab310();
    pair7 = FUN_000dbd0c();
    r4 = FUN_00377bec(pair7.lo, pair7.hi, r3, (word_t)0 /*DAT_0061628c*/).lo;
    pcvar5 = (code *)FUN_000277b8();
    iret = *(int *)(lvar2 + 0x24);
    r3 = FUN_00377dcc(0, r3);
    (*pcvar5)(x8ret + iret, r3, r4);
    FUN_00351300(0);
    r3 = FUN_00497504().lo;
    FUN_00468ce4(x8ret);
    FUN_003509c8(r3);
    (**(code **)(x16ret + 8))(pair6.lo, r3);
    *(long *)(x8ret + *(int *)(lvar2 + 0x28)) = (long)pair6.hi;
    *(char *)(x8ret + *(int *)(lvar2 + 0x30)) = (char)sc;
    FUN_0007767c(u30);
    return;
}

/* FUN_0046cb54 @ 0x0046cb54   (est. sk_bcg_0046cb54)
 * Ghidra: void sk_bcg_0046cb54(void)
 * Regex ByteCodeGen main loop: drives the matching-state machine. Reads the
 * consumer metadata from the 0008e518 pair (+0x10/+0x18), builds the builder,
 * then loops over the AST region advancing via FUN_0046c9f0 and re-emitting
 * through the method table. Uses tag/range (>>0xe) fail-closed traps throughout
 * (0x46d204/0x46d208) and dispatches FUN_0046d208 at the tail.
 * Confidence: low   Notes: SUB_54ffff60f100041f masked trampoline; DAT_0060e208;
 * many indirect method-table calls (x12ret/x16 +8/+0x10/+0x20). */
static void sk_bcg_0046d208(word_t p1, word_t p2, word_t p3);
static void sk_bcg_0046d670(void);
static void sk_bcg_0046cb54(void)
{
    int iret;
    long lvar4;
    long lvar8, lvar9, lvar16, lvar17, lvar18;
    word_t r5, r6, r7, r10, r11, r12;
    word_t r14;
    bool bvar3;
    word_t u20, u27;
    long x8ret, x8ret0, x8ret1, x8ret2;
    long x9ret, x9ret0;
    long x12ret, x16ret, x16ret0, x16ret1, x16ret2;
    code *pcvar13, *pcvar15, *pcvar19;
    wpair_t pair20, pair21;
    word_t ld8, l78;

    pair20 = FUN_0008e518();
    lvar4 = (long)pair20.lo;
    r12 = *(word_t *)(lvar4 + 0x10);
    r5 = *(word_t *)(lvar4 + 0x18);
    FUN_004aa75c();
    r5 = FUN_00377824(0xff, r5, r12).lo;
    FUN_004ab310();
    pair21 = FUN_0009e234();
    r5 = FUN_00377bec(pair21.lo, pair21.hi, r5).lo;
    r6 = FUN_004aa770();
    FUN_00350a1c(r6, r5);
    r6 = FUN_00377824().lo;
    r7 = FUN_0034b0b4();
    FUN_004ab9ec(r7, r6);
    lvar8 = (long)FUN_003722e4();
    FUN_000a6f88();
    sk_svc_call(*(word_t *)(x8ret0 + 0x40));  /* masked trampoline */
    FUN_003493c4();
    FUN_003503f8();
    sk_svc_call();                                   /* masked trampoline */
    FUN_00350464();
    FUN_004ac2b8();
    FUN_00464f4c();
    FUN_00350b9c(r5);
    r7 = FUN_00377bec().lo;
    lvar9 = (long)FUN_00310e08(0xff, r6);
    FUN_00350500();
    r10 = FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    sk_svc_call();                                   /* masked trampoline */
    FUN_0034b460();
    FUN_0007c028();
    sk_svc_call(*(word_t *)(x8ret1 + 0x40)); /* masked trampoline */
    FUN_003493c4();
    FUN_003503f8();
    sk_svc_call();                                   /* masked trampoline */
    FUN_0034ba68();
    FUN_0007c028();
    FUN_0007c1a4();
    sk_svc_call();                                   /* masked trampoline */
    FUN_0034af20();
    FUN_003504e8();
    r11 = FUN_00377dcc();
    FUN_000a6f88();
    FUN_0007c1a4();
    sk_svc_call();                                   /* masked trampoline */
    FUN_00350428();
    if ((*(unsigned char *)(u20 + *(int *)(lvar4 + 0x34)) & 1) != 0) {
        r12 = FUN_004aa80c();
        FUN_00377824(r12, r5, r11);
        pair20 = FUN_00352290();
        FUN_0008e500(pair20.lo, pair20.hi, 1);
        FUN_000839d8();
        return;
    }
    lvar18 = (long)*(int *)(lvar4 + 0x24);
    sk_bcg_0046c9f0(0, 0); /* register-residue args */
    FUN_00351750(r5);
    FUN_003510ac();
    sk_svc_call();                                   /* masked trampoline */
    pcvar15 = *(code **)(x12ret + 8);
    (*pcvar15)(x8ret2, r11);
    FUN_00027754(r7);
    pcvar13 = (code *)FUN_0014ae44();
    FUN_00351f4c(u20 + lvar18);
    r14 = (word_t)sk_svc_call();                     /* masked trampoline */
    pcvar19 = *(code **)(x16ret2 + 8);
    FUN_00350ab8();
    (*pcvar19)();
    if ((r14 & 1) == 0) {
        iret = *(int *)(lvar4 + 0x2c);
        lvar17 = *(long *)(u20 + iret);
        lvar16 = *(long *)(u20 + *(int *)(lvar4 + 0x28));
        bvar3 = (bool)(lvar17 == lvar16);
        if (lvar17 < lvar16) {
            FUN_004ab624();
            r12 = FUN_004a3038(0, r12, r5);
            while (true) {
                FUN_00468c6c((word_t)0 /*DAT_0060e208*/, r12);
                FUN_00350884((word_t)0 /*DAT_0060e208*/, 1, lvar9);
                if (bvar3) break;
                pair21 = FUN_003508b4(*(word_t *)(x16ret1 + 0x20));
                sk_svc_call(pair21.lo, pair21.hi, lvar9);   /* masked trampoline */
                bvar3 = (*(char *)(u20 + *(int *)(lvar4 + 0x30)) == '\x01');
                if (!bvar3) {
LAB_0046cfc8:
                    if (SCARRY8(lvar17, 1)) {
                        CL4_SWBP(0x46d204);
                    }
                    *(long *)(u20 + iret) = lvar17 + 1;
                    sk_bcg_0046c9f0(x8ret2, lvar4);
                    FUN_0035166c(r7);
                    FUN_00351f4c(u20 + lvar18, u27);
                    r14 = (word_t)sk_svc_call();             /* masked trampoline */
                    if ((r14 & 1) == 0) {
                        CL4_SWBP(0x46d208);
                    }
                    pcvar13 = *(code **)(x16ret2 + 0x10);
                    (*pcvar13)(l78, u20 + lvar18, r6);
                    FUN_00352c4c(l78 + *(int *)(lvar8 + 0x30));
                    (*pcvar13)();
                    pair21 = FUN_003510dc();
                    sk_svc_call(pair21.lo, pair21.hi, lvar8);  /* masked trampoline */
                    iret = *(int *)(lvar8 + 0x30);
                    pcvar13 = *(code **)(x16ret2 + 0x20);
                    FUN_00351214(x9ret0);
                    sk_svc_call();                            /* masked trampoline */
                    (*pcvar19)(x9ret + iret, r6);
                    pair21 = FUN_003510dc(*(word_t *)(x16ret + 0x20));
                    sk_svc_call(pair21.lo, pair21.hi, lvar8); /* masked trampoline */
                    (*pcvar13)(x9ret0 + *(int *)(lvar9 + 0x24), x9ret + *(int *)(lvar8 + 0x30), r6);
                    FUN_00350738();
                    (*pcvar19)();
                    FUN_00319628(r5);
                    FUN_00350c08(x8ret, x9ret0);
                    sk_svc_call();                            /* masked trampoline */
                    pcvar13 = *(code **)(x16ret1 + 8);
                    FUN_003514e8();
                    (*pcvar13)();
                    FUN_000a6e14();
                    (*pcvar15)((word_t)(x12ret + 8) & 0xffffffffffff | 0x4f8000000000000);
                    r12 = FUN_004aa80c();
                    r12 = FUN_00377824(r12, r5, ld8).lo;
                    FUN_000839d8(x8ret, 0, 1, r12);
                    sk_bcg_0046d670();
                    FUN_003508cc();
                    (*pcvar13)();
                    goto LAB_0046d1e8;
                }
                FUN_00351f4c(u20 + lvar18, u27);
                r14 = (word_t)(*pcvar13)();
                if ((r14 & 1) == 0) goto LAB_0046cfc8;
                sk_bcg_0046d670();
                (**(code **)(x16ret1 + 8))(u27, lvar9);
            }
            (**(code **)(x16ret0 + 8))((word_t)0 /*DAT_0060e208*/, r10);
        }
    }
    sk_bcg_0046d208(x8ret, 0, 0); /* register-residue args */
LAB_0046d1e8:
    FUN_0008e500(pair20.hi);
    return;
}

/* FUN_0046d208 @ 0x0046d208   (est. sk_bcg_0046d208)
 * Ghidra: void sk_bcg_0046d208(undefined8 p1..p3)
 * Regex ByteCodeGen continuation: builds the consumer from the 0008e518 pair,
 * derives the builder and message string (DAT_0060e208), sets a flag byte
 * (+0x34 = 1), advances via FUN_0046c9f0 and FUN_0046d670, and finally reports
 * success/failure through FUN_000839d8(result bit r14-based). Traps at
 * 0x46d670 on the fail-closed path.
 * Confidence: medium   Notes: SUB_54ffff60f100041f masked trampoline; DAT_0060e208;
 * thunk_FUN_001a29a0; indirect method-table calls. */
static void sk_bcg_0046d208(word_t p1, word_t p2, word_t p3)
{
    word_t r1, r2, r3, r7;
    long lvar4, lvar5;
    word_t r6;
    word_t x8ret, x8ret0;
    long x8ret1, x8ret2, x8ret3, x8ret4;
    long x9ret, x12ret, x16ret, x16ret0, x16ret1, x16ret2;
    word_t u30;
    code *pcvar8, *pcvar9, *pcvar10;
    wpair_t pair11, pair12;

    pair11 = FUN_0008e518();
    r7 = pair11.hi;
    r1 = p3;
    FUN_004aaa9c();
    FUN_003511cc(0xff, r1);
    FUN_00377824();
    FUN_004ab310();
    FUN_003504a0(p3);
    r1 = FUN_00377bec().lo;
    r2 = FUN_004aa770();
    FUN_00350a1c(r2, r1);
    r2 = FUN_00377824().lo;
    FUN_00464f4c(r2);
    pair12 = FUN_00350524();
    pair12 = FUN_00377bec(pair12.lo, pair12.hi, x8ret0, (word_t)0 /*DAT_0060e208*/);
    r2 = pair12.lo;
    FUN_00350500(r2, pair12.hi, r2);
    FUN_00319308();
    FUN_000a6f88();
    FUN_0007c1a4();
    sk_svc_call();                                   /* masked trampoline */
    FUN_00350428();
    FUN_003504e8();
    r3 = FUN_00377dcc();
    FUN_000a6f88();
    FUN_0007c1a4();
    sk_svc_call();                                   /* masked trampoline */
    pair12 = FUN_00350530();
    lvar4 = (long)FUN_004a30d4(pair12.lo, pair12.hi, p3);
    FUN_000a6f88();
    FUN_0007c1a4();
    sk_svc_call();                                   /* masked trampoline */
    pair12 = FUN_0034cff4();
    FUN_0007c028(pair12.lo, pair12.hi, x8ret0);
    sk_svc_call(*(word_t *)(x8ret3 + 0x40)); /* masked trampoline */
    FUN_0034ab10();
    sk_svc_call();                                   /* masked trampoline */
    lvar5 = (long)FUN_0034b4c0();
    *(unsigned char *)(pair11.lo + (long)*(int *)(lvar5 + 0x34)) = 1;
    pcvar8 = *(code **)(x16ret2 + 0x10);
    (*pcvar8)();
    FUN_00351118(*(word_t *)(x16ret1 + 0x10), r7);
    sk_svc_call();                                   /* masked trampoline */
    sk_bcg_0046c9f0(x8ret1 - x8ret2, lvar4);
    pcvar9 = *(code **)(x16ret1 + 8);
    (*pcvar9)(r7, lvar4);
    FUN_00351750(r1);
    FUN_00350a04(x9ret - x12ret);
    sk_svc_call();                                   /* masked trampoline */
    FUN_003508fc(*(word_t *)(x16ret0 + 8));
    sk_svc_call();                                   /* masked trampoline */
    FUN_00027754(r2);
    r1 = FUN_0014ae44();
    FUN_00351414(r1);
    r6 = (word_t)sk_svc_call();                      /* masked trampoline */
    pcvar10 = *(code **)(x16ret2 + 8);
    (*pcvar10)(x9ret - x12ret, x8ret0);
    FUN_003509b0();
    (*pcvar10)();
    if (((r6 & 1) == 0) || ((*(unsigned char *)(pair11.lo + (long)*(int *)(lvar4 + 0x30)) & 1) == 0)) {
        pair11 = FUN_00084180(x8ret4);
        sk_svc_call(pair11.lo, pair11.hi, lvar4);    /* masked trampoline */
        sk_bcg_0046c9f0(x8ret1 - x8ret2, lvar4);
        (*pcvar9)(r7, lvar4);
        (*pcvar8)();
        FUN_003516b4();
        r6 = (word_t)sk_svc_call();                  /* masked trampoline */
        if ((r6 & 1) == 0) {
            CL4_SWBP(0x46d670);
        }
        pair11 = FUN_00351414(x8ret1);
        FUN_001a29a0(pair11.lo, pair11.hi, r2);          /* thunk_FUN_001a29a0 */
        FUN_00407300();
        FUN_00350a1c(x8ret, x8ret1, r3);
        FUN_001d9890();
        FUN_003514e8(*(word_t *)(x16ret + 8));
        sk_svc_call();                               /* masked trampoline */
        FUN_00350a70();
        sk_svc_call();                               /* masked trampoline */
        r1 = 0;
    }
    else {
        r1 = 1;
    }
    FUN_004aa80c();
    FUN_003505c4();
    r2 = FUN_00377824().lo;
    FUN_000839d8(x8ret, r1, 1, r2);
    FUN_0008e500(u30);
    return;
}

/* FUN_0046d670 @ 0x0046d670   (est. sk_bcg_0046d670)
 * Ghidra: void sk_bcg_0046d670(void)
 * Regex ByteCodeGen step: rebuilds the consumer/builder (FUN_004a30d4), computes
 * field offsets (l4 +0x24), then performs an indirect jumptable dispatch
 * through the builder's method table (l2 -8 +0x18) passing the two computed
 * pointers. The jumptable could not be recovered.
 * Confidence: medium   Notes: u19/u20; indirect jumptable call. */
static void sk_bcg_0046d670(void)
{
    int iret;
    long lvar2, lvar4;
    word_t r3;
    word_t in3;
    long u19, u20;

    FUN_00084220();
    FUN_0035199c();
    FUN_003504d0();
    FUN_004aa75c();
    FUN_00377824(0xff, in3);
    FUN_004aacb0();
    FUN_004aa770();
    FUN_0034db28();
    lvar2 = (long)FUN_00377824().lo;
    FUN_00464f4c();
    FUN_00350470();
    FUN_00352ea8();
    FUN_00377bec();
    r3 = FUN_00350c98();
    lvar4 = (long)FUN_00310e08(r3, lvar2);
    iret = *(int *)(lvar4 + 0x24);
    FUN_00077894(0);
    lvar4 = (long)FUN_004a30d4();
    /* indirect jumptable dispatch (unresolved target) */
    (**(code **)(*(long *)(lvar2 - 8) + 0x18))
        (u20 + *(int *)(lvar4 + 0x24), u19 + iret, lvar2);
    return;
}

/* FUN_0046d740 @ 0x0046d740   (est. sk_bcg_0046d740)
 * Ghidra: void sk_bcg_0046d740(undefined8 p1)
 * Regex ByteCodeGen dispatch shim: builds the consumer (FUN_00497504 pair),
 * runs the masked trampoline prologue, then calls FUN_0046ca44 to compile the
 * node. Passes param_1 through to the method-table slot +0x10.
 * Confidence: medium   Notes: x8ret/x12; SUB_54ffff60f100041f. */
static void sk_bcg_0046d740(word_t p1)
{
    long x12ret;
    word_t x8ret;
    wpair_t pair1;

    FUN_003505c4(0);
    pair1 = FUN_00497504();
    FUN_000a6f88(pair1.lo, pair1.hi, pair1.lo);
    FUN_0007c1a4();
    sk_svc_call();                                   /* masked trampoline */
    FUN_0034b0c4();
    FUN_00351714(*(word_t *)(x12ret + 0x10));
    sk_svc_call();                                   /* masked trampoline */
    FUN_00352c40(p1);
    sk_bcg_0046ca44(0, 0, 0, 0, 0); /* register-residue args */
    return;
}

/* FUN_0046d810 @ 0x0046d810   (est. sk_bcg_0046d810)
 * Ghidra: void sk_bcg_0046d810(long p1,undefined8 p2,code *p3)
 * Regex ByteCodeGen dispatch tail: calls the supplied function pointer param_3,
 * then performs an indirect jumptable dispatch through the metadata object's
 * method table (param_1 -8 +8). The second jumptable could not be recovered.
 * Confidence: medium   Notes: indirect jumptable call. */
static void sk_bcg_0046d810(long p1, word_t p2, code *p3)
{
    (*p3)();
    /* indirect jumptable dispatch (unresolved target) */
    (**(code **)(*(long *)(p1 - 8) + 8))();
    return;
}

/* ==================== SKR27 function bodies ==================== */

/* Signed-borrow (unsigned underflow) helper for subtraction a - b, mirroring
 * Ghidra's SBORROW8(a,b) flag used by the fail-closed range/count checks. */
#define SBORROW8(a,b) ((uint64_t)(a) < (uint64_t)(b))

/* In-slice static callees (sk_bcg_<addr>) referenced before/from other parts
 * of slice R27; forward-declared here so the assembled slice resolves them.
 * Decompiler "register residue" may make some call sites pass fewer/more args
 * than the declared prototype - that is preserved faithfully. */
static void     sk_bcg_0046c91c(word_t p1, word_t p2, word_t p3, word_t p4,
                                word_t p5, word_t p6);
static void sk_bcg_0046d860(void);
static word_t   sk_bcg_0046df0c(word_t, word_t, word_t, word_t, word_t,
                                word_t, word_t, word_t);
static word_t   sk_bcg_0046e128(word_t, word_t, word_t, word_t, word_t,
                                word_t, word_t, word_t, word_t, word_t);
static void sk_bcg_0046e7a8(void);
static void     sk_bcg_0046ece8(word_t, word_t, word_t, word_t, word_t);
static wpair_t  sk_bcg_0046f298(word_t, word_t, long);

/* FUN_0046d860 @ 0x0046d860   (est. sk_bcg_0046d860)
 * Ghidra: void sk_bcg_0046d860(void)
 * ByteCodeGen emission prologue used when appending one regex alternative:
 * runs the builder initialisation helpers, applies the masked
 * self-modifying/trampoline patch to the current instruction slot, grows the
 * buffer twice, then routes the freshly built range pair through the
 * caller-returned thunk and releases the temporary objects.
 * Confidence: medium   Notes: SUB_54ffff60f100041f masked trampoline fn;
 * register artifacts (extraout_x8_00/_01/_02/_03, extraout_x9/x12/x13/x16,
 * in_x3/in_x4, unaff_x30) modelled as implicit inputs. */
static void sk_bcg_0046d860(void)
{
    word_t r_x3, r_x4;              /* in_x3, in_x4 */
    word_t res;                     /* extraout_x8 */
    long slot_a, slot_b, slot_c;    /* extraout_x8_00/_01/_02 */
    code *slot_fn;                  /* extraout_x8_03 */
    long thunk_base;                /* extraout_x9 */
    word_t thunk_arg;               /* extraout_x12 */
    long ctx_a;                     /* extraout_x13 */
    long ctx_b;                     /* extraout_x16 */
    word_t ret_ctx;                 /* unaff_x30 */
    wpair_t pair;                   /* auVar1 */

    FUN_0008e518();
    FUN_0035089c();
    FUN_0007c028();
    /* masked self-modifying/trampoline fn (SUB_54ffff60f100041f) */
    ((code)0x54ffff60f100041f)(*(word_t *)(slot_a + 0x40));
    FUN_000aa4ec();
    FUN_0007c028();
    /* masked self-modifying/trampoline fn (SUB_54ffff60f100041f) */
    ((code)0x54ffff60f100041f)(*(word_t *)(slot_b + 0x40));
    FUN_000aa4ec();
    /* indirect call through slot ctx_a + 0x10 */
    (*(code *)(ctx_a + 0x10))(thunk_base - slot_c, thunk_arg, r_x3);
    pair = FUN_000e72b0(*(word_t *)(ctx_b + 0x10));
    (*slot_fn)(pair.lo, pair.hi, r_x4);
    FUN_00350914(res);
    sk_bcg_0046c91c(0, 0, 0, 0, 0, 0); /* register-residue args (decompiler dropped them) */
    FUN_0008e500(ret_ctx);
}
/* FUN_0046d988 @ 0x0046d988   (est. sk_bcg_0046d988)
 * Ghidra: void sk_bcg_0046d988(undefined8,undefined8,uint,long,undefined8,undefined8,undefined8,undefined8)
 * Compiles one regex AST node into the bytecode stream. It probes the runtime
 * builder state and, depending on the matched kind, either records the node as
 * a fresh 0x40-byte instruction record (packing the child range, match flags
 * and source range pair) or defers to the sub-emitters sk_bcg_0046e128 /
 * sk_bcg_0046df0c for the multi-part (group/anchor) cases. It finishes by
 * re-emitting the accumulated range pair through the caller-returned thunk and
 * tearing down the temporary builder state.
 * Confidence: medium   Notes: SUB_54ffff60f100041f masked trampoline fn;
 * register artifacts (slot_a/_01/_02, probe_fn, ctx_a,
 * extraout_x1, base) modelled as implicit inputs. */
static void sk_bcg_0046d988(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6, word_t p7, word_t p8)
{
    int kind;
    word_t v2, v3, v4, v5, v7, v8;
    long l3, l6, l9, l11;
    wpair_t w12, w13;
    word_t node_arg, stack_a, stack_b, stack_c, stack_d;
    wpair_t range_pair;             /* local_28 */
    long node_rec, saved_cnt;       /* local_18, stack_10 */
    word_t base;                    /* unaff_x21 */
    word_t arg_res, out_ctx;        /* extraout_x1, extraout_x8 */
    long slot_a, slot_b;            /* extraout_x8_00/_01 */
    code *tail_fn;                  /* extraout_x8_02 */
    code *probe_fn, *thunk;         /* extraout_x9, pcVar10 */
    long ctx_a, ctx_b;              /* extraout_x16/_16_00 */

    w12 = FUN_0008e518();
    v4 = w12.hi;
    l9 = p4;
    v2 = p6;
    FUN_0007c028();
    /* masked self-modifying/trampoline fn (SUB_54ffff60f100041f) */
    ((code)0x54ffff60f100041f)(*(word_t *)(slot_a + 0x40));
    FUN_000aa4ec();
    FUN_004974ec(0xff, l9, v2);
    FUN_004aa970();
    v2 = FUN_004979d4();
    FUN_0034ab20();
    FUN_0007c1a4();
    /* masked self-modifying/trampoline fn (SUB_54ffff60f100041f) */
    ((code)0x54ffff60f100041f)();
    FUN_00350428();
    w13 = FUN_003504e8();
    FUN_004ac628(w13.lo, w13.hi, p5);
    FUN_000a6f88();
    FUN_0007c1a4();
    /* masked self-modifying/trampoline fn (SUB_54ffff60f100041f) */
    ((code)0x54ffff60f100041f)();
    l3 = FUN_0034cff4().lo;
    l11 = (long)*(int *)(l3 + 0x30);
    l3 = *(long *)(p4 - 8);
    FUN_00350624();
    (*probe_fn)();
    thunk = *(code **)(ctx_a + 0x10);
    (*thunk)(base + l11, w12.lo, p5);
    FUN_004aac78();
    FUN_003504a0();
    kind = FUN_00365b6c();
    if (kind == 0) {
LAB_0046dc80:
        FUN_004aac04();
        FUN_003504a0();
        kind = FUN_00365b6c();
        l6 = saved_cnt;
        l9 = node_rec;
        v7 = range_pair.hi;
        v5 = range_pair.lo;
        if (kind == 0) {
LAB_0046dd98:
            w12 = FUN_000e15d8();
            (*thunk)(w12.lo, w12.hi, p5);
            FUN_00027754(p6);
            w12 = FUN_004aa5dc();
            v5 = FUN_00377824(w12.lo, w12.hi, p4).lo;
            FUN_00356bb0(p7);
            w12 = FUN_003509bc();
            v7 = FUN_0019e578(w12.lo, w12.hi, p5);
            l3 = FUN_0036a940(0x686110, 0x40, 7);
            *(long *)(l3 + 0x10) = p4;
            *(word_t *)(l3 + 0x18) = p5;
            *(word_t *)(l3 + 0x20) = p6;
            *(word_t *)(l3 + 0x28) = p7;
            *(word_t *)(l3 + 0x30) = p8;
            *(word_t *)(l3 + 0x38) = v5;
            l9 = p4;
            FUN_00467de4(v7, (word_t)0 /* &DAT_004aa278 */, l3, p4, p6);
            range_pair = FUN_003535a8();
            node_rec = l3;
            saved_cnt = l9;
            /* decompile passed register residue: (slot_b, range_pair,
               v4, p3&1, p4, extraout_x1, 0x687b40) */
            sk_bcg_0046d860();
            FUN_0036b118(l9);
            FUN_0036b118(p7);
            FUN_0036b118(v7);
            v4 = FUN_004aa80c();
            v4 = FUN_00377824(v4, p6, p4).lo;
            v2 = FUN_0019e578(slot_b, v4, v2, 0x687ac8);
            l3 = ctx_b;
            goto LAB_0046dedc;
        }
        FUN_004aac78();
        kind = FUN_004ac60c();
        if (kind == 0) {
            FUN_004aaf38();
            kind = FUN_004ac60c();
            if (kind == 0) {
                FUN_003a25d4(l6);
                goto LAB_0046dd98;
            }
            *(long *)(slot_b - 0x10) = l9;
            *(long *)(slot_b - 8) = l6;
            v4 = sk_bcg_0046e128(stack_a, stack_b, stack_c, stack_d, v4,
                              p3 & 1, v5, v7, 0, 0); /* register-residue args */
            stack_b = stack_d;
        } else {
            v4 = sk_bcg_0046df0c(stack_a, stack_b, v4, p3 & 1, v5, v7, l9, l6);
        }
        FUN_003a25d4(l6);
        FUN_003a25d4(stack_b);
        v2 = FUN_004aa80c();
        w12 = FUN_00377824(v2, p6, p4);
        FUN_004abdb8(w12.lo, w12.hi, w12.lo);
        v2 = FUN_0019dfc4(v4);
        FUN_0036b118(v4);
        thunk = *(code **)(ctx_a + 8);
    } else {
        FUN_004ab9b0();
        FUN_00465db0();
        kind = FUN_004ac60c(range_pair);
        l6 = range_pair.hi;
        if (kind == 0) {
            v5 = FUN_004aac04();
            v8 = p5;
            kind = FUN_00365b6c(v5, base + l11);
            l6 = saved_cnt;
            v7 = range_pair.hi;
            v5 = range_pair.lo;
            if (kind == 0) {
                FUN_003a25d4(stack_b);
                p6 = node_arg;
                goto LAB_0046dc80;
            }
            FUN_0035139c(0xf);
            FUN_0001d4f4();
            FUN_003a25d4(stack_b);
            *(word_t *)(slot_b - 0x10) = v8;
            *(long *)(slot_b - 8) = l9;
            FUN_00351cd0(v5, v7);
            v4 = sk_bcg_0046e128(0,0,0,0,0,0,0,0,0,0); /* register-residue args */
            FUN_003a25d4(l9);
        } else {
            FUN_0035139c(0xf);
            FUN_0001d4f4();
            FUN_004ac33c();
            FUN_003a25d4(stack_b);
            w12 = FUN_00351450();
            v4 = sk_bcg_0046df0c(w12.lo, w12.hi, v4, 0, 0, 0, 0, 0); /* register-residue args */
            FUN_003a25d4(l9);
        }
        FUN_003a25d4(l6);
        v2 = FUN_004aa80c();
        w12 = FUN_00377824(v2, node_arg, p4);
        FUN_004abdb8(w12.lo, w12.hi, w12.lo);
        v2 = FUN_0019dfc4(v4);
        FUN_0036b118(v4);
        thunk = *(code **)(ctx_a + 8);
    }
    (*thunk)(base + l11, p5);
LAB_0046dedc:
    FUN_00084180(*(word_t *)(l3 + 8));
    (*tail_fn)();
    FUN_0008e500(v2, out_ctx);
}
/* FUN_0046df0c @ 0x0046df0c   (est. sk_bcg_0046df0c)
 * Ghidra: undefined8 sk_bcg_0046df0c(undefined8,undefined8,undefined8,byte,ulong,ulong,undefined8,undefined8)
 * Sub-emitter for a multi-part (group/anchor) regex node. It verifies that the
 * supplied range is ordered (lower <= upper, else fail-closed), then emits a
 * builder record combining the range pair with a 0xe000000000000000 tag-mask
 * and stores the node's payload; the record is finalised and registered under
 * the group metadata key. Returns the record handle.
 * Confidence: medium   Notes: range-ordered SWBP check; indirect builder
 * dispatch; DAT_005a3c70 metadata key. */
static word_t sk_bcg_0046df0c(word_t p1, word_t p2, word_t p3, word_t p4,
                              word_t p5, word_t p6, word_t p7, word_t p8)
{
    wpair_t w6, w7, w8, rec;        /* rec = local_f8 */
    word_t v3, v4, v5;
    word_t lo_span, hi_span, payload; /* local_e8, stack_e0, local_78 */
    byte flag;                      /* local_70 */
    word_t r;
    byte scratch[96];               /* auStack_d8 */

    if ((p5 >> 0xe) <= (p6 >> 0xe)) {
        w6 = FUN_002b74c0(p5, p6, p5, p6, p7, p8);
        v3 = p5;
        v4 = p6;
        w7 = FUN_002b3978(0, 0xe000000000000000);
        v5 = v4;
        w8 = FUN_0001d4f4(0xf, p1, p2);
        FUN_0046777c(scratch, w7.lo, w7.hi, v3, v4, w8.lo, w8.hi, p2, v5);
        flag = (byte)(p4 & 1);
        lo_span = p5;
        hi_span = p6;
        payload = p3;
        rec = w6;
        r = FUN_004979f8(rec);
        FUN_004a4b14(rec, 0x657bc8, (word_t)0 /* &DAT_005a3c70 */);
        return r;
    }
    /* SoftwareBreakpoint(1,0x46e038) - range not ordered, fail closed */
    CL4_SWBP(0x46e038);
    return 0;
}
/* FUN_0046e038 @ 0x0046e038   (est. sk_bcg_0046e038)
 * Ghidra: undefined8 sk_bcg_0046e038(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Emits a closure/anchor record: after acquiring the builder lock and opening
 * a new sub-emitter with a thunk target, it packs the caller's range pair and
 * flag byte into the record payload, finalises it through sk_bcg_004979f8 and
 * returns the caller-supplied flag value.
 * Confidence: medium   Notes: FUN_004b5a74 thunk target; register-artifact
 * range fields. */
static word_t sk_bcg_0046e038(word_t p1, word_t p2, word_t p3, word_t p4,
                              word_t p5, word_t p6)
{
    word_t rng1_lo, rng1_hi, rng2_lo, rng2_hi;   /* local_110..stack_f8 */
    word_t rng3_lo, rng3_hi, rng4_lo, rng4_hi;   /* local_f0..stack_d8 */
    word_t payload;                 /* local_70 */
    byte flag;                      /* local_68 */
    byte scratch[96];               /* auStack_d0 */

    FUN_00027754(p6);
    FUN_00356bb0();
    FUN_00270c08(&rng1_lo, FUN_004b5a74, 0, p5);
    FUN_0011e71c();
    FUN_002b3978();
    FUN_00350b48(0xf);
    FUN_0001d4f4();
    FUN_00462aac();
    FUN_00350af4(scratch);
    FUN_00351cd0();
    FUN_0046777c();
    rng3_hi = rng1_hi;
    rng3_lo = rng1_lo;
    rng4_lo = rng2_lo;
    rng4_hi = rng2_hi;
    flag = (byte)p4;
    payload = p3;
    FUN_004979f8(&rng3_lo);
    FUN_004ac088();
    return p4;
}
/* FUN_0046e128 @ 0x0046e128   (est. sk_bcg_0046e128)
 * Ghidra: undefined8 sk_bcg_0046e128(ulong,ulong,undefined8,undefined8,undefined8,byte,ulong,ulong,undefined8,undefined8)
 * Sub-emitter for a two-range (source span + target span) regex node. Both
 * ranges are validated as ordered (lower <= upper, else fail-closed), then a
 * builder record is emitted that carries the target span with its tag-mask
 * 0xe000000000000000 and the source span; the record is finalised and
 * registered under the group metadata key. Returns the record handle.
 * Confidence: medium   Notes: two ordered-range SWBP checks; DAT_005a3c70
 * metadata key. */
static word_t sk_bcg_0046e128(word_t p1, word_t p2, word_t p3, word_t p4,
                              word_t p5, word_t p6, word_t p7, word_t p8,
                              word_t p9, word_t p10)
{
    wpair_t w5, w6, w7, rec;        /* rec = local_f8 */
    word_t v3, v4;
    word_t lo_span, hi_span, payload; /* local_e8, stack_e0, local_78 */
    byte flag;                      /* local_70 */
    word_t r;
    byte scratch[96];               /* auStack_d8 */

    if ((p8 >> 0xe) < (p7 >> 0xe)) {
        /* SoftwareBreakpoint(1,0x46e270) - target span not ordered */
        CL4_SWBP(0x46e270);
        return 0;
    }
    w5 = FUN_002b74c0(p7, p8, p7, p8, p9, p10);
    v3 = p7;
    v4 = p8;
    w6 = FUN_002b3978(0, 0xe000000000000000);
    if ((p1 >> 0xe) <= (p2 >> 0xe)) {
        w7 = FUN_002b74c0(p1, p2, p1, p2, p3, p4);
        FUN_0046777c(scratch, w6.lo, w6.hi, v3, v4, w7.lo, w7.hi, p1, p2);
        flag = (byte)(p6 & 1);
        lo_span = p7;
        hi_span = p8;
        payload = p5;
        rec = w5;
        r = FUN_004979f8(rec);
        FUN_004a4b14(rec, 0x657bc8, (word_t)0 /* &DAT_005a3c70 */);
        return r;
    }
    /* SoftwareBreakpoint(1,0x46e274) - source span not ordered */
    CL4_SWBP(0x46e274);
    return 0;
}
/* FUN_0046e274 @ 0x0046e274   (est. sk_bcg_0046e274)
 * Ghidra: undefined8 sk_bcg_0046e274(void)
 * Alternative closure/anchor emitter (mirrors sk_bcg_0046e038): opens a new
 * sub-emitter with the thunk target, validates the two register-supplied range
 * halves are ordered, then packs the range pair and flag byte into a record and
 * finalises it. Returns the caller-supplied value in x4.
 * Confidence: medium   Notes: FUN_004b5a74 thunk target; range-ordered SWBP
 * check; register artifacts (ret_val/flag_in/arg_b/arg_c, range_hi/_x25). */
static word_t sk_bcg_0046e274(void)
{
    word_t ret_val, arg_b, arg_c;     /* in_x4/in_x6/in_x7 */
    byte flag_in;                     /* in_w5 */
    word_t range_hi, range_lo;    /* unaff_x24/unaff_x25 */
    word_t slot_a, slot_b, slot_c, slot_d;   /* local_120..stack_108 */
    word_t slot_e, slot_f, slot_g, slot_h;   /* local_100..stack_e8 */
    word_t payload;                 /* local_80 */
    byte flag;                      /* local_78 */
    byte scratch[96];               /* auStack_e0 */
    word_t v2;

    FUN_00407ab8();
    FUN_00027754(arg_c);
    FUN_00356bb0();
    FUN_00270c08(&slot_a, FUN_004b5a74, 0, arg_b);
    FUN_0011e71c();
    v2 = FUN_002b3978().lo;
    if ((range_lo >> 0xe) <= (range_hi >> 0xe)) {
        FUN_00350618();
        FUN_004ab910();
        FUN_002b74c0();
        FUN_00462aac();
        FUN_00352840(scratch, v2);
        FUN_0046777c();
        flag = (byte)(flag_in & 1);
        slot_f = slot_b;
        slot_e = slot_a;
        slot_g = slot_c;
        slot_h = slot_d;
        payload = ret_val;
        FUN_004979f8(&slot_e);
        FUN_004ac088();
        return ret_val;
    }
    /* SoftwareBreakpoint(1,0x46e384) - range not ordered, fail closed */
    CL4_SWBP(0x46e384);
    return 0;
}
/* FUN_0046e384 @ 0x0046e384   (est. sk_bcg_0046e384)
 * Ghidra: void sk_bcg_0046e384(undefined8,undefined8,uint,undefined8,undefined8,undefined8,undefined8)
 * Top-level AST-to-bytecode compiler driver. It walks the regex node list; for
 * each child either emits it inline or recurses via sk_bcg_0046e7a8, tracking
 * the accumulated range. When a range change or the single-match flag demands
 * it, the range pair is recorded into the (growable) 0x20-byte-entry array of
 * the builder object and the node list is advanced. On exhaustion the whole
 * builder is released.
 * Confidence: medium   Notes: DAT_005a3c68 metadata key; range-ordered SWBP
 * check; growable array (>> 1 <= count -> grow); register artifacts. */
static void sk_bcg_0046e384(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6, word_t p7)
{
    long l1, l3, l6;
    word_t v2, v3, v4, v5;
    word_t v6, v7;
    code *pc8;
    wpair_t w9;
    long builder_hint;              /* extraout_x8 */
    code *probe_fn;                 /* extraout_x8_00 */
    code *thunk_a, *thunk_b, *thunk_c;  /* extraout_x9/_9_00/_9_01 */
    long ctx_a, ctx_b, ctx_c;       /* extraout_x16/_16_00/_16_01 */
    word_t ret_ctx;                 /* unaff_x30 */
    word_t cur_range, prev_range, prev_range_hi; /* local_2a0/_2b0, stack_2a8 */
    word_t rec_f3, rec_f4, rec_f5;  /* stack_298, local_290, stack_288 */
    word_t span, e_lo, e_hi, e_meta, e_flag; /* local_130, local_60..local_40 */
    long builder, e_count, saved_a, saved_b;  /* local_128, local_58, stack_28/10 */
    word_t rec_a, rec_b, rec_c, rec_d; /* local_38, local_30, local_20, local_18 */
    byte scratch[192];              /* auStack_120 */

    w9 = FUN_0008e518();
    v4 = p6;
    FUN_000a6f68();
    builder = builder_hint;
    v4 = FUN_00027754(v4);
    FUN_0035156c();
    FUN_000b4390(&span);
    (*thunk_a)();
    if (0 < (long)w9.hi) {
        v5 = FUN_003192a8(v4);
        FUN_000b4390(v5);
        v6 = (*probe_fn)();
        if ((v6 & 1) == 0) {
            /* decompile passed register residue: (scratch, w9.lo, p4..p7) */
            sk_bcg_0046e7a8();
            FUN_004aabe4();
            FUN_00352840(0xff);
            FUN_00377824();
            FUN_003508e4();
            v5 = FUN_00498c54();
            FUN_00469dc4(&cur_range);
            FUN_003509c8(v5);
            (*(code *)(ctx_a + 8))(scratch, v5);
            FUN_003508e4();
            v5 = FUN_00498c6c();
            while (1) {
                FUN_00469c50(&e_lo, v5);
                v6 = e_flag;
                v3 = e_hi;
                l1 = e_count;
                v2 = e_lo;
                if (e_count == 0) break;
                v7 = FUN_004abd70(e_meta);
                if (((v7 & 1) != 0) && (*(long *)(builder + 0x10) == w9.hi)) {
                    FUN_003509c8(v5);
                    (*(code *)(ctx_c + 8))(&cur_range, v5);
                    span = v6;
                    rec_b = v2;
                    saved_b = l1;
                    FUN_000f5e5c(&rec_b);
                    rec_a = v3;
                    FUN_004aa938();
                    FUN_004a4b14(&rec_a);
                    goto LAB_0046e5b8;
                }
                span = v6;
                rec_d = v2;
                saved_a = l1;
                FUN_000f5e5c(&rec_d);
                rec_c = v3;
                FUN_004a4b14(&rec_c, 0x657bc0, (word_t)0 /* &DAT_005a3c68 */);
            }
            FUN_003509c8(v5);
            (*(code *)(ctx_b + 8))(&cur_range, v5);
LAB_0046e5b8:
            v6 = span;
            pc8 = (code *)FUN_00310924(v4);
            FUN_0008e388(&cur_range);
            (*pc8)();
            v7 = v6 >> 0xe;
            if ((v7 != (cur_range >> 0xe)) || ((p3 & 1) == 0)) {
                (*pc8)(&cur_range, p4, v4);
                if ((cur_range >> 0xe) < v7) {
                    /* SoftwareBreakpoint(1,0x46e6b0) - range shrank */
                    CL4_SWBP(0x46e6b0);
                }
                prev_range = v6;
                prev_range_hi = cur_range;
                FUN_00319628(v4);
                FUN_00351178(&cur_range, &prev_range);
                (*thunk_c)();
                v6 = FUN_003a261c(builder);
                if ((v6 & 1) == 0) {
                    FUN_0006b3f4(*(word_t *)(builder + 0x10));
                    builder = FUN_00073690();
                }
                v6 = *(word_t *)(builder + 0x10);
                if ((*(word_t *)(builder + 0x18) >> 1) <= v6) {
                    FUN_000ec004();
                    builder = FUN_00073690();
                }
                *(word_t *)(builder + 0x10) = v6 + 1;
                l1 = builder + v6 * 0x20;
                *(word_t *)(l1 + 0x20) = cur_range;
                *(word_t *)(l1 + 0x28) = rec_f3;
                *(word_t *)(l1 + 0x30) = rec_f4;
                *(word_t *)(l1 + 0x38) = rec_f5;
            }
            goto LAB_0046e438;
        }
    }
    FUN_00351750(v4);
    FUN_000b4390(&cur_range);
    (*thunk_b)();
    FUN_004abd70(cur_range);
LAB_0046e438:
    FUN_0008e500(builder, ret_ctx);
}
/* FUN_0046e6b0 @ 0x0046e6b0   (est. sk_bcg_0046e6b0)
 * Ghidra: byte sk_bcg_0046e6b0(ulong,ulong *,byte,long *,undefined8,undefined8,undefined8)
 * Range-append helper for a single-match node. If the current range already
 * matches the caller's range tag (and the flag is set) it returns 0; otherwise
 * it appends the caller's range to the builder's 0x20-byte-entry array (growing
 * via FUN_00498b28 when needed) and returns 1 (meaning "changed/inserted").
 * Confidence: medium   Notes: range-tag SWBP check; growable array via
 * FUN_00498b28(FUN_00073690); register artifact extraout_x9. */
static byte sk_bcg_0046e6b0(word_t p1, word_t *p2, byte p3, long *p4,
                            word_t p5, word_t p6, word_t p7)
{
    long l2, l3;
    code *thunk;                    /* extraout_x9 */
    word_t cur_range, new_range, rec_lo; /* local_80, stack_78, local_70 */
    word_t rec_f2, rec_f3, rec_f4;  /* stack_68, local_60, stack_58 */

    cur_range = *p2;
    p3 = (byte)(((cur_range >> 0xe) == (p1 >> 0xe)) & (word_t)p3);
    if (p3 == 0) {
        if ((p1 >> 0xe) < (cur_range >> 0xe)) {
            /* SoftwareBreakpoint(1,0x46e7a8) - range not ordered */
            CL4_SWBP(0x46e7a8);
        }
        new_range = p1;
        FUN_00027754(p7);
        FUN_00319628();
        FUN_003511d8(&rec_lo, &cur_range);
        (*thunk)();
        FUN_00498b28((word_t)FUN_00073690);
        l3 = *(long *)(*p4 + 0x10);
        FUN_00100efc();
        FUN_00498c1c();
        l2 = *p4;
        *(long *)(l2 + 0x10) = l3 + 1;
        l2 = l2 + l3 * 0x20;
        *(word_t *)(l2 + 0x28) = rec_f2;
        *(word_t *)(l2 + 0x20) = rec_lo;
        *(word_t *)(l2 + 0x30) = rec_f3;
        *(word_t *)(l2 + 0x38) = rec_f4;
    }
    return p3 ^ 1;
}
/* FUN_0046e7a8 @ 0x0046e7a8   (est. sk_bcg_0046e7a8)
 * Ghidra: void sk_bcg_0046e7a8(void)
 * Recursive node emitter: for the current regex node it captures the three
 * source spans (via the two range resolvers), validates they are ordered, and
 * stores the spans plus the node's metadata into a freshly sized 0x90-byte
 * record block. It then releases the temporary objects and returns to the
 * caller-returned continuation.
 * Confidence: medium   Notes: two ordered-range SWBP checks; indirect range
 * resolvers via FUN_000277b8 / FUN_00310924; register artifacts
 * (arg_a/arg_b, extraout_x8, unaff_x30, in_stack_*). */
static void sk_bcg_0046e7a8(void)
{
    word_t v1, v2, v3, v4, v5, v6, v7;
    code *pc8, *pc9;
    word_t arg_a, arg_b;            /* arg_a/arg_b */
    long rec_base_out;              /* extraout_x8 */
    code *probe_fn;                 /* extraout_x8_00 */
    word_t ret_ctx;                 /* unaff_x30 */
    word_t span_a, span_b, thunk_slot; /* stack_8, stack_10, stack_18 */
    word_t meta_a, meta_b, rec_base;   /* stack_28, stack_30, stack_38 */

    FUN_00464b04();
    FUN_004ab5d4(arg_b);
    FUN_00351274();
    v6 = (*probe_fn)();
    FUN_00469918(&rec_base);
    FUN_0036b118(v6);
    v7 = FUN_00027754(arg_a);
    FUN_003511f0(&thunk_slot, FUN_004b5a74, 0);
    FUN_00270c08();
    v5 = meta_b;
    v6 = meta_a;
    pc8 = (code *)FUN_000277b8(v7);
    FUN_000e15d8(&span_b);
    (*pc8)();
    v3 = span_b;
    pc9 = (code *)FUN_00310924(v7);
    FUN_000e15d8(&span_a);
    (*pc9)();
    v1 = span_a;
    if ((span_a >> 0xe) < (v3 >> 0xe)) {
        /* SoftwareBreakpoint(1,0x46e8fc) - span pair not ordered */
        CL4_SWBP(0x46e8fc);
    }
    FUN_000e15d8(&span_b);
    (*pc8)();
    v4 = span_b;
    FUN_000e15d8(&span_a);
    (*pc9)();
    v2 = span_a;
    if ((v4 >> 0xe) <= (span_a >> 0xe)) {
        FUN_00117cc4(rec_base_out, &rec_base, 0x90);
        *(word_t *)(rec_base_out + 0x90) = v6;
        *(word_t *)(rec_base_out + 0x98) = v5;
        *(word_t *)(rec_base_out + 0xa0) = v3;
        *(word_t *)(rec_base_out + 0xa8) = v1;
        *(word_t *)(rec_base_out + 0xb0) = v4;
        *(word_t *)(rec_base_out + 0xb8) = v2;
        FUN_00464ae8(ret_ctx);
        return;
    }
    /* SoftwareBreakpoint(1,0x46e900) - span pair not ordered, fail closed */
    CL4_SWBP(0x46e900);
}
/* FUN_0046e900 @ 0x0046e900   (est. sk_bcg_0046e900)
 * Ghidra: bool sk_bcg_0046e900(void)
 * Single-match fast-path probe. It resolves the current node's data object and,
 * when a continuation slot is present, re-invokes the node sub-compiler on the
 * resolved pair and disposes of the transient. Returns whether a continuation
 * was present (local_70 != 0).
 * Confidence: medium   Notes: indirect continuation call via extraout_x16 + 8;
 * register artifacts (arg_a/arg_b, extraout_x8, unaff_x30). */
static void sk_bcg_0046ea18(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5);
static bool sk_bcg_0046e900(void)
{
    word_t v1;
    word_t arg_a, arg_b;            /* in_x3/in_x4 */
    code *probe_fn;                 /* extraout_x8 */
    long ctx;                       /* extraout_x16 */
    word_t payload, tmp;            /* local_78, stack_60 */
    long cont;                      /* local_70 */

    FUN_0034b318();
    FUN_00356bb0(arg_a);
    FUN_004abfb8();
    FUN_00270c08();
    FUN_004ab5d4(arg_b);
    FUN_00084180();
    v1 = (*probe_fn)();
    FUN_004aa95c();
    FUN_00350878();
    FUN_00377824();
    FUN_0034e5bc(&payload, payload);
    sk_bcg_0046ea18(0,0,0,0,0); /* register-residue args */
    FUN_003a25d4(tmp);
    FUN_0036b118(v1);
    if (cont != 0) {
        FUN_003542b8();
        FUN_004974ac();
        FUN_00352efc();
        v1 = FUN_00310d68();
        FUN_0034ab20(v1, v1);
        (*(code *)(ctx + 8))(&payload);
    }
    return cont != 0;
}
/* FUN_0046ea18 @ 0x0046ea18   (est. sk_bcg_0046ea18)
 * Ghidra: void sk_bcg_0046ea18(void)
 * Thin trampoline that forwards to the node-builder clean-up helper
 * (FUN_0049490c). */
static void sk_bcg_0046ea18(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5;  /* register-residue args */
    FUN_0049490c();
}
/* FUN_0046ea44 @ 0x0046ea44   (est. sk_bcg_0046ea44)
 * Ghidra: void sk_bcg_0046ea44(void)
 * Emits a quantified/counted block. With the count==4 fast path it iterates
 * over the 0x4000-bit-aligned index range, materialising each index into the
 * builder's index table (a bitmap word + 0x10-byte entry + offset table),
 * growing the table when the index set changes. It then closes with either a
 * single-iteration or a counted-iteration tail and finalises the block.
 * Confidence: medium   Notes: DAT_00657778/DAT_00657d18/DAT_005a4ac0 keys;
 * SBORROW8/SCARRY8 range checks; register artifacts (in_x3..in_x7, unaff_x25,
 * extraout_x8). */
static void sk_bcg_0046ea44(void)
{
    word_t *entry_ptr;              /* puVar1 */
    long l3, l4, l7;
    word_t v5, v6, v8, v9;
    long count_flag;                /* in_x3 */
    word_t idx_lo, idx_hi, payload, meta; /* in_x4..in_x7 */
    word_t result;                  /* extraout_x8 */
    word_t range_val;               /* unaff_x25 */
    wpair_t w10, w11, w12;

    FUN_0035300c();
    v5 = meta;
    FUN_00407ab8();
    FUN_0036b270(v5);
    FUN_0042c060(4, idx_lo, idx_hi, payload, meta);
    FUN_00351790();
    l3 = FUN_002b4120();
    FUN_003a25d4(payload);
    FUN_004ab288((word_t)0 /* &DAT_00657778 */, 0x6728f0, 0x677880);
    l4 = FUN_001f0130();
    if (l3 == 4) {
        l3 = 0;
        while (0x3fff < (idx_lo ^ idx_hi)) {
            FUN_00351dfc(idx_lo);
            FUN_002b439c();
            FUN_00352c80();
            FUN_00351dfc(idx_lo);
            idx_lo = FUN_002b3b50();
            if (SBORROW8(l3, 1)) {
                /* SoftwareBreakpoint(1,0x46ecd0) - index count underflow */
                CL4_SWBP(0x46ecd0);
            }
            v5 = FUN_003a261c(l4);
            FUN_00084180();
            w10 = FUN_0006ae9c();
            v9 = w10.lo;
            l7 = *(long *)(l4 + 0x10);
            v8 = (word_t)(~(uint)w10.hi) & 1;
            if (SBORROW8(l7, v8)) {
                /* SoftwareBreakpoint(1,0x46ecd4) - entry count underflow */
                CL4_SWBP(0x46ecd4);
            }
            v6 = FUN_00002534((word_t)0 /* &DAT_00657d18 */,
                              (word_t)0 /* &DAT_005a4ac0 */).lo;
            v8 = FUN_00258c60(v5, l7 + v8, v6);
            if ((v8 & 1) != 0) {
                FUN_00084180();
                w12 = FUN_0006ae9c();
                v9 = w12.lo;
                if (((uint)w10.hi & 1) != ((uint)w12.hi & 1)) {
                    FUN_002591b4(0x6728f0);   /* subroutine does not return */
                }
            }
            if ((w10.hi & 1) == 0) {
                l7 = l4 + (v9 >> 6) * 8;
                *(word_t *)(l7 + 0x40) = *(word_t *)(l7 + 0x40)
                                       | (1ULL << (v9 & 0x3f));
                entry_ptr = (word_t *)(*(long *)(l4 + 0x30) + v9 * 0x10);
                *entry_ptr = 4;
                entry_ptr[1] = payload;
                *(long *)(*(long *)(l4 + 0x38) + v9 * 8) = l3;
                if (SBORROW8(*(long *)(l4 + 0x10), 1)) {
                    /* SoftwareBreakpoint(1,0x46ecd8) - entry count underflow */
                    CL4_SWBP(0x46ecd8);
                }
                *(long *)(l4 + 0x10) = *(long *)(l4 + 0x10) + 1;
            } else {
                FUN_003a25d4(payload);
                *(long *)(*(long *)(l4 + 0x38) + v9 * 8) = l3;
            }
            l3 = l3 + 1;
        }
    } else {
        FUN_003511a8();
        FUN_00353960();
        FUN_002b4120();
    }
    FUN_003a25d4(meta);
    if (count_flag == 0) {
        w10.lo = 0;
        w10.hi = 1;                 /* ZEXT816(1) << 0x40 */
    } else {
        FUN_0034db28(range_val);
        w10 = FUN_002b3f40();
        FUN_003a25d4(count_flag);
    }
    w11 = FUN_00351450();
    FUN_00353238(w11.lo, w11.hi, w10.lo, w10.hi, result);
}
/* FUN_0046ece8 @ 0x0046ece8   (est. sk_bcg_0046ece8)
 * Ghidra: void sk_bcg_0046ece8(undefined8,undefined8,undefined8,undefined8,ulong)
 * Emits an alternation/choice block. It reads the builder's span table, then
 * walks each alternative: for an alternative whose span still overlaps the
 * running range it consumes the source span and advances, otherwise it
 * terminates the current range and stores the accumulated span into the output
 * record. Writes a 5-field result (index, range, and two flag bytes) back
 * through the caller-provided pointer.
 * Confidence: medium   Notes: multiple range-ordered SWBP checks; wpair
 * comparisons; register artifacts (unaff_x20/x30, extraout_w1, extraout_x8). */
static void sk_bcg_0046ece8(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    word_t v1, v2, v3, v6, v7, v8, v9, v10, v12, v13, v14;
    byte carry, v11, v15;           /* extraout_w1, uVar11, uVar15 */
    wpair_t w17, w18, w4;
    word_t a19_lo;                  /* auVar19._0_8_ */
    byte a19_flag;                  /* auVar19._8_4_ & 0xff */
    long l16;
    word_t *out;                    /* extraout_x8 */
    word_t bld, ret_ctx;            /* unaff_x20/unaff_x30 */

    w17 = FUN_0035638c();
    v10 = w17.hi;
    l16 = *(long *)(bld + 0x48);
    if (l16 < 1) {
        /* SoftwareBreakpoint(1,0x46ef8c) - empty span table */
        CL4_SWBP(0x46ef8c);
    }
    v1 = *(word_t *)(bld + 0x20);
    v2 = *(word_t *)(bld + 0x28);
    v13 = *(word_t *)(bld + 0x30);
    v3 = *(word_t *)(bld + 0x38);
    w18 = FUN_000a6e14();
    w4.lo = v13;
    w4.hi = v1;
    v12 = v2;
    v14 = v13;
    v6 = FUN_002b3cf8(w18.lo, w18.hi, v2);
    FUN_003511f0(p5, w17.lo);
    v7 = FUN_002b3cf8();
    while (1) {
        if ((v10 >> 0xe) < (v7 >> 0xe)) {
            /* SoftwareBreakpoint(1,0x46ef84) - span run out of order */
            CL4_SWBP(0x46ef84);
        }
        FUN_00350b84();
        FUN_00352c40();
        FUN_002b74c0();
        FUN_00351a50();
        w18 = FUN_002b439c(v6, v1, v2, v13, v3);
        a19_lo = FUN_004292ac(w18.lo, w18.hi, p5, bld, v12, v14);
        v7 = a19_lo;
        FUN_003a25d4(v14);
        FUN_003a25d4(w18.hi);
        if (a19_flag == 1) break;
        p5 = v6;
        v8 = v7;
        if ((v7 >> 0xe) < (w17.lo >> 0xe)) {
            /* SoftwareBreakpoint(1,0x46ef88) - span advance out of order */
            CL4_SWBP(0x46ef88);
        }
        do {
            while (1) {
                if ((p5 >> 0xe) <= (v1 >> 0xe)) {
                    FUN_000bd3a4(v7);
                    v10 = FUN_002b3b50();
                    if ((v10 >> 0xe) < (v8 >> 0xe)) {
                        /* SoftwareBreakpoint(1,0x46ef90) - span out of order */
                        CL4_SWBP(0x46ef90);
                    }
                    FUN_003511f0(v10, l16);
                    v7 = FUN_002b3f40().lo;
                    v15 = 0;
                    v11 = carry;
                    goto LAB_0046ef44;
                }
                p5 = FUN_002b3cf8(p5, v1, v2, v13, v3);
                w18 = FUN_00351354();
                FUN_00353208(w18.lo, w18.hi, v10);
                v8 = FUN_002b3cf8();
                w18 = FUN_0009461c();
                FUN_002b439c(w18.lo, w18.hi, v2, v13, v3);
                FUN_003548dc();
                w18 = FUN_00351354();
                FUN_00353208(w18.lo, w18.hi, v10);
                w18 = FUN_002b439c();
                v12 = w18.lo;
                if ((w18.lo == w4.lo) && (w18.hi == w4.hi)) break;
                FUN_003a25d4(v1);
                FUN_003a25d4(w18.hi);
            }
            FUN_00350aa0();
            v9 = FUN_002a0cf8();
            FUN_003a25d4(v1);
            FUN_003a25d4(w18.hi);
        } while ((v9 & 1) != 0);
        FUN_0035139c(v7);
        v14 = p3;
        v7 = FUN_002b3b50();
        bld = v1;
    }
    v8 = 0;
    v10 = 0;
    v15 = 1;
    v11 = 1;
LAB_0046ef44:
    out[0] = v8;
    out[1] = v10;
    *(byte *)(out + 2) = v15;
    out[3] = v7;
    *(byte *)(out + 4) = v11;
    FUN_00356370(ret_ctx);
}
/* FUN_0046ef90 @ 0x0046ef90   (est. sk_bcg_0046ef90)
 * Ghidra: void sk_bcg_0046ef90(undefined8,undefined8,undefined8,ulong,ulong)
 * Alternation/choice walker over a counted span range. Depending on the
 * builder's span table it either single-steps (0x4000-aligned) or iterates the
 * count of remaining spans, matching each source span against the target range
 * and, on a run boundary, emitting a compressed match record via
 * sk_bcg_0046f298. The result (range pair, index, two flag bytes) is written
 * back through the caller-provided pointer.
 * Confidence: medium   Notes: SBORROW8/SWBP range checks; wpair comparisons;
 * register artifacts (unaff_x20/x25/x30, extraout_w1/w8, extraout_x8,
 * in_stack_*). */
static void sk_bcg_0046ef90(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    long l1, l6, l16, l17, l18;
    word_t v2, v3, v4, v5, v9, v10, v11, v12, v13, v14, v15;
    byte w1, w1_00, w8, w8_00;      /* extraout_w1/w1_00/w8/w8_00, uVar13 */
    byte v8;                        /* uVar8 flag */
    wpair_t w19, w20;
    word_t a21_lo;                  /* auVar21._0_8_ */
    byte a21_flag;                  /* auVar21._8_4_ & 0xff */
    long bld, ret_ctx;              /* unaff_x20/unaff_x30 */
    word_t range_val;               /* unaff_x25 */
    word_t stack_68, stack_70, stack_80;
    byte stack_78, stack_88;
    word_t *out;                    /* extraout_x8 */

    w19 = FUN_003583e8();
    v14 = w19.hi;
    v9 = w19.lo;
    l17 = *(long *)(bld + 0x48);
    if (l17 == 0) {
        v10 = p5;
        if ((p5 ^ v14) < 0x4000) {
            v12 = FUN_00068e14(0);
            v8 = w8_00;
            v13 = w1;
        } else {
            v12 = FUN_002b3b50(p5, v9, v14, p3, p4);
            v8 = 0;
            v13 = 0;
        }
    } else {
        l16 = *(long *)(bld + 0x40);
        if (*(long *)(l16 + 0x10) == 0) {
            FUN_00352ae4(&stack_68, v9, v14);
            sk_bcg_0046ece8(0,0,0,0,0); /* register-residue args */
            v12 = stack_80;
            p5 = stack_70;
            v10 = stack_68;
            v8 = stack_78;
            v13 = stack_88;
        } else {
            if (SBORROW8(l17, 1)) {
                /* SoftwareBreakpoint(1,0x46f294) - span count underflow */
                CL4_SWBP(0x46f294);
            }
            v2 = *(word_t *)(bld + 0x20);
            v4 = *(word_t *)(bld + 0x28);
            v3 = *(word_t *)(bld + 0x30);
            v5 = *(word_t *)(bld + 0x38);
            v12 = p5;
            v11 = v4;
            l18 = l17;
            do {
                while (1) {
                    w19.hi = v4;
                    w19.lo = range_val;
                    l18 = l18 - 1;
                    v10 = FUN_002b3cf8(v12, v9, v14, p3, p4);
                    v11 = FUN_002b3cf8(v11, v2, v4, v3, v5);
                    if ((v11 >> 0xe) < (v2 >> 0xe)) break;
                    FUN_002b439c(v11, v2, v4, v3, v5);
                    FUN_004ac960();
                    w20 = FUN_00100efc();
                    w20 = FUN_002b439c(w20.lo, w20.hi, v14, p3, p4);
                    v15 = w20.hi;
                    if ((w20.lo == w19.lo) && (w20.hi == w19.hi)) {
                        FUN_003a25d4(v4);
                        FUN_003a25d4(v15);
                    } else {
                        FUN_003512c0(w20.lo, v15, w20.lo);
                        range_val = FUN_002a0cf8();
                        FUN_003a25d4(v4);
                        FUN_003a25d4(v15);
                        if ((range_val & 1) == 0) break;
                    }
                    if (SBORROW8(l18, 1)) {
                        /* SoftwareBreakpoint(1,0x46f288) - span count underflow */
                        CL4_SWBP(0x46f288);
                    }
                    if ((v11 >> 0xe) == (v2 >> 0xe)) {
                        if ((p5 >> 0xe) < (v10 >> 0xe)) {
                            /* SoftwareBreakpoint(1,0x46f298) - range out of order */
                            CL4_SWBP(0x46f298);
                        }
                        v12 = FUN_002b3f40(p5, l17, v14, v9, v14, p3, p4).lo;
                        v8 = 0;
                        v13 = w1_00;
                        goto LAB_0046f260;
                    }
                    v12 = v10;
                    if ((v10 >> 0xe) <= (v9 >> 0xe)) {
                        /* SoftwareBreakpoint(1,0x46f28c) - range out of order */
                        CL4_SWBP(0x46f28c);
                    }
                }
                FUN_003504a0(v10);
                w19 = FUN_002b439c();
                a21_lo = sk_bcg_0046f298(w19.lo, w19.hi, l16).lo;
                FUN_003a25d4(w19.hi);
                l1 = 0;
                if (a21_flag != 1) {
                    l1 = (long)a21_lo;
                }
                l6 = l18 - l1;
                if (SBORROW8(l18, l1)) {
                    /* SoftwareBreakpoint(1,0x46f290) - span count underflow */
                    CL4_SWBP(0x46f290);
                }
                v8 = (byte)(l6 == 1);
                if (l6 < 2) {
                    l6 = 1;
                }
                FUN_002b3f40(p5, l6, v14, v9, v14, p3, p4);
                v12 = FUN_00351db4().lo;
                range_val = p4;
                v11 = v4;
                l18 = l17;
                p5 = v12;
            } while (!(bool)v8);
            v10 = 0;
            p5 = 0;
            v13 = 1;
            v8 = w8;
        }
    }
LAB_0046f260:
    out[0] = v10;
    out[1] = p5;
    *(byte *)(out + 2) = v8;
    out[3] = v12;
    *(byte *)(out + 4) = v13;
    FUN_00358454(ret_ctx);
}
/* FUN_0046f298 @ 0x0046f298   (est. sk_bcg_0046f298)
 * Ghidra: undefined1[16] sk_bcg_0046f298(undefined8,undefined8,long)
 * Builds a compressed match record for one alternative: if the given builder
 * has pending entries it reads the head index from the offset table (or a 0
 * when the index set is empty), packs it with the "have entry" flag and
 * zeroes the tag bits; otherwise it returns the 16-byte "empty / nothing"
 * marker (1 in the high word).
 * Confidence: medium   Notes: 16-byte wpair return; DAT-free. */
static wpair_t sk_bcg_0046f298(word_t p1, word_t p2, long p3)
{
    bool have_entry;
    word_t v2;
    wpair_t w3;

    if (*(long *)(p3 + 0x10) != 0) {
        w3 = FUN_0006ae9c();
        have_entry = (w3.hi & 1) == 0;
        if (have_entry) {
            v2 = 0;
        } else {
            v2 = *(word_t *)(*(long *)(p3 + 0x38) + w3.lo * 8);
        }
        /* auVar3[8] = have_entry; auVar3._0_8_ = v2; auVar3._9_7_ = 0 */
        w3.lo = v2;
        w3.hi = (word_t)have_entry;
        return w3;
    }
    w3.lo = 0;
    w3.hi = 1;                      /* ZEXT816(1) << 0x40 */
    return w3;
}

/* ==================== SKR27 function bodies ==================== */

/* Extra externs for this part (thunk variants + callees not in the shared
 * header; see CONTRACT). Bodies owned by their slice workers. */

extern word_t thunk_FUN_00498708();
extern wpair_t thunk_FUN_002b74c0();
extern word_t DAT_0060e208;
extern word_t DAT_00611b24;
extern word_t LAB_00611b34;
extern word_t thunk_FUN_0036b270();
extern word_t thunk_FUN_001a29a0();

/* FUN_0046f2f0 @ 0x46f2f0  (est. sk_bcg_0046f2f0)
 * Ghidra: void sk_bcg_0046f2f0(undefined8 param_1)
 * Regex ByteCodeGen entry helper: lays out a 96-byte stack buffer through
 * the byte-copy helper, then forwards its argument to the main body at
 * sk_bcg_0046f334. Thin trampoline wrapper.
 * Confidence: medium   Notes: FUN_00117cc4 = byte copy (cL4_memcpy_v). */
static void sk_bcg_0046f334(word_t param_1);
static void sk_bcg_0046f2f0(word_t param_1)
{
    unsigned char buf[96];
    FUN_00117cc4((word_t)buf);      /* byte-copy init of the 96-byte stack buf */
    sk_bcg_0046f334(param_1);
}

/* FUN_0046f334 @ 0x46f334  (est. sk_bcg_0046f334)
 * Ghidra: void sk_bcg_0046f334(undefined8 param_1)
 * Passes its single argument through the byte-copy helper. Minimal shim
 * used as a forwarding target from sk_bcg_0046f2f0.
 * Confidence: medium   Notes: FUN_00117cc4 = byte copy. */
static void sk_bcg_0046f334(word_t param_1)
{
    FUN_00117cc4(param_1);      /* byte-copy helper on the argument */
}

/* FUN_0046f344 @ 0x46f344  (est. sk_bcg_0046f344)
 * Ghidra: void sk_bcg_0046f344(void)
 * Fetches a 16-byte pair from the pair producer FUN_00463f94 and copies a
 * fixed 0x59-byte region out of it through the byte-copy helper, then
 * calls the teardown helper. Likely reads a regex-instruction payload and
 * stores a 0x59-byte structure.
 * Confidence: medium   Notes: 0x59 constant = copy length; DAT-free. */
static void sk_bcg_0046f344(void)
{
    wpair_t pair = FUN_00463f94();        /* 16-byte pair producer */
    FUN_00117cc4(pair.lo, pair.hi, 0x59); /* byte-copy, 0x59 bytes */
    FUN_00468d98();
}

/* FUN_0046f37c @ 0x46f37c  (est. sk_bcg_0046f37c)
 * Ghidra: void sk_bcg_0046f37c(void)
 * Regex ByteCodeGen emit path: runs the 0x867ec pre-step, pulls a 16-byte
 * pair from FUN_004ab618, byte-copies a 0x59-byte region, then runs the
 * 0x100efc step and the 0x498708 thunk. Companion of sk_bcg_0046f344.
 * Confidence: medium   Notes: 0x59 copy length; thunk_FUN_00498708. */
static void sk_bcg_0046f37c(void)
{
    wpair_t pair;
    FUN_000867ec();
    pair = FUN_004ab618();              /* 16-byte pair producer */
    FUN_00117cc4(pair.lo, pair.hi, 0x59);
    FUN_00100efc();
    thunk_FUN_00498708();
}

/* FUN_0046f3c8 @ 0x46f3c8  (est. sk_bcg_0046f3c8)
 * Ghidra: void sk_bcg_0046f3c8(undefined1 (*param_1) [16],undefined8 p2,undefined8 p3,undefined1 p4)
 * Fills a 16-byte output pair: the pair half comes from FUN_00467848, and
 * the first byte of the following slot is stamped with the byte p4.
 * Confidence: medium */
static void sk_bcg_0046f3c8(wpair_t *out, word_t p2, word_t p3, word_t p4)
{
    wpair_t v = FUN_00467848();   /* 16-byte pair producer */
    *out = v;
    out[1].lo = (out[1].lo & ~0xFFULL) | (uint8_t)p4;  /* param_1[1][0] = p4 */
    (void)p2; (void)p3;
}

/* FUN_0046f3f4 @ 0x46f3f4  (est. sk_bcg_0046f3f4)
 * Ghidra: void sk_bcg_0046f3f4(p1..p6)
 * Regex ByteCodeGen dispatch: builds a 16-byte pair via FUN_00084220, folds
 * it plus p3/p4 into a builder call (thunk_FUN_002b74c0) with p5/p6, then
 * performs teardown/emit steps (0x4abf6c, 0x36b270 on ctx+0x38, 0x462b6c,
 * 0x84234 on the aux register, 0x46ea44).
 * Confidence: low   Notes: unaff_x20/unaff_x30 register artifacts. */
static wpair_t sk_bcg_0046f3f4(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6)
{
    word_t ctx;    /* unaff_x20 */
    word_t aux;    /* unaff_x30 */
    wpair_t pair = FUN_00084220();
    wpair_t result;   /* register-carried 16-byte return */

    result = thunk_FUN_002b74c0(p5, p6, pair.lo, pair.hi, p3, p4);
    FUN_004abf6c();
    thunk_FUN_0036b270(*(word_t *)(ctx + 0x38));  /* unaff_x20 + 0x38 */
    FUN_00462b6c(result.lo);
    FUN_00084234(aux);                            /* unaff_x30 */
    sk_bcg_0046ea44();
    (void)p1; (void)p2;
    return result;   /* register residue: last x0:x1 pair */
}

/* FUN_0046f474 @ 0x46f474  (est. sk_bcg_0046f474)
 * Ghidra: void sk_bcg_0046f474(void)
 * Regex ByteCodeGen state check: if the byte at obj+0x18 is 0x01 it takes
 * the short path (0x19858); otherwise it lays out a 40-byte stack buffer,
 * runs the 0x4ac8c0 step and stores the x8/x9 register outputs back into
 * obj+0x10 (word) and obj+0x18 (byte).
 * Confidence: low   Notes: in_x4 = caller object; extraout_x8/w9 artifacts. */
static wpair_t sk_bcg_0046f474(word_t obj, word_t p2, word_t p3, word_t p4, word_t p5)
{
    word_t out_x8;        /* extraout_x8 */
    word_t out_w9;        /* extraout_w9 */
    unsigned char sbuf[40];
    (void)p2; (void)p3; (void)p4; (void)p5;

    if (*(char *)(obj + 0x18) == '\x01') {
        FUN_00019858();
    } else {
        sk_bcg_0046ef90((word_t)sbuf, 0, 0, 0, 0); /* register-residue args */
        FUN_004ac8c0();
        *(word_t *)(obj + 0x10) = out_x8;        /* extraout_x8 */
        *(unsigned char *)(obj + 0x18) = (unsigned char)out_w9; /* extraout_w9 */
    }
    return (wpair_t){ out_x8, (word_t)out_w9 };  /* register residue */
}

/* FUN_0046f4cc @ 0x46f4cc  (est. sk_bcg_0046f4cc)
 * Ghidra: void sk_bcg_0046f4cc(undefined1 (*param_1) [16],undefined8 *param_2,undefined8 *param_3)
 * Regex ByteCodeGen pair builder: gathers two words from in2[2..3], calls
 * sk_bcg_0046f3f4 with the 2x2 word inputs, writes the resulting pair to
 * *out and stamps the following slot with the gathered words.
 * Confidence: medium */
static void sk_bcg_0046f4cc(wpair_t *out, word_t *in2, word_t *in3)
{
    word_t u1, u2;
    wpair_t v;

    u1 = in2[2];
    u2 = in2[3];
    v = sk_bcg_0046f3f4(in2[0], in2[1], u1, u2, in3[0], in3[1]);
    *out = v;
    out[1].lo = u1;                              /* *(u64*)param_1[1] = uVar1 */
    out[1].hi = (out[1].hi & ~0xFFULL) | (uint8_t)u2; /* param_1[1][8] = (char)uVar2 */
}

/* FUN_0046f510 @ 0x46f510  (est. sk_bcg_0046f510)
 * Ghidra: void sk_bcg_0046f510(undefined1 (*param_1) [16],undefined8 *param_2,undefined8 param_3)
 * Regex ByteCodeGen pair builder: forwards in2[0..3] plus p3 into
 * sk_bcg_0046f474, writes the returned pair to *out and stamps the first
 * byte of the next slot with in2[2].
 * Confidence: medium */
static void sk_bcg_0046f510(wpair_t *out, word_t *in2, word_t p3)
{
    word_t u1 = in2[2];
    wpair_t v = sk_bcg_0046f474(in2[0], in2[1], u1, in2[3], p3);
    *out = v;
    out[1].lo = (out[1].lo & ~0xFFULL) | (uint8_t)u1; /* param_1[1][0] = (char)uVar1 */
}

/* FUN_0046f54c @ 0x46f54c  (est. sk_bcg_0046f54c)
 * Ghidra: void sk_bcg_0046f54c(param_1,param_2,param_3,param_4)
 * Regex ByteCodeGen emit sequence: folds the two 16-bit payload words
 * (param_3/param_4) through the byte-copy helper and several builder/tramp
 * steps, computes a size from a register pair, and dispatches through
 * indirect function pointers. On the success path (low bit of the final
 * status word set) it completes the emit and returns; otherwise it
 * fail-closes at the 0x46f820 software breakpoint.
 * Confidence: low   Notes: heavy extraout_xN register aliasing; masked
 * self-modifying trampoline calls (SUB_54ffff60f100041f) */
static void sk_bcg_0046f820(word_t param_1, word_t param_2, word_t param_3, word_t param_4);
static void sk_bcg_0046f54c(word_t p1, word_t p2, word_t p3, word_t p4)
{
    word_t r2, r3, r4, r5, r7, status;
    word_t ctx;               /* unaff_x20 */
    word_t aux;               /* unaff_x30 */
    word_t x1;                /* extraout_x1 */
    word_t x8;                /* extraout_x8 */
    long   x9, x12, x12b, lsize;   /* extraout_x9 / extraout_x12 / _00 */
    code   fn9;               /* extraout_x9_00 / _01 */
    code   fn8;               /* extraout_x8_01 / _02 */
    word_t fnp16;                   /* extraout_x16 / _00 / _01 base (raw addr) */
    word_t scratch;                   /* local_50 */
    wpair_t pr;
    int    zr;                /* in_ZR (flags) */

    FUN_0008e518();
    r7 = x1;                                  /* extraout_x1 */
    r2 = FUN_00377bec(p4, p3, x1, 0x616214, 0x61621c).lo;  /* &DAT_00616214/1c */
    FUN_004aa67c();
    FUN_00351bd4();
    r3 = FUN_00377824().lo;
    FUN_00464f4c();
    FUN_003515d8(r2);
    FUN_00377bec();
    r4 = FUN_00350c98();
    FUN_00319308(r4, r3);
    r4 = FUN_000a6f88();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();  /* masked self-modifying/trampoline fn */
    FUN_00350428();
    FUN_004ac36c();
    r5 = FUN_00310d68(0, r3);
    FUN_000a6f88();
    ((code)(uintptr_t)0x54ffff60f100041f)(*(word_t *)(x8 + 0x40)); /* masked tramp */
    FUN_0034ab10();
    lsize = x9 - x12;                         /* extraout_x9 - extraout_x12 */
    ((code)(uintptr_t)0x54ffff60f100041f)();  /* masked tramp */
    FUN_0007c028();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();  /* masked tramp */
    FUN_0034b460();
    sk_bcg_0046f820(lsize - x12b, ctx, p3, p4);  /* extraout_x12_00; register-residue arg */
    pr = FUN_00350a70();
    fn9(pr.lo, pr.hi, r5);                    /* extraout_x9_00 indirect */
    FUN_00350884(lsize, 1, r3);
    zr = /* flags from last compare */ 0;
    if (zr) {
        FUN_0035156c(r2);
        fn9(x1, r2);                          /* extraout_x9_01 indirect */
        FUN_00350884(lsize, 1, r3);
        if (/* !flags */ 1) {
            (**(code **)(fnp16 + 8))(lsize, r5);   /* indirect at _00+8 */
        }
    } else {
        (**(code **)(fnp16 + 0x20))();             /* indirect at _01+0x20 */
    }
    FUN_00349fe0(r7);
    FUN_00351de4();
    status = (*fn8)();                        /* extraout_x8_01 indirect */
    if ((status & 1) != 0) {
        pr = FUN_0009e234(scratch);
        thunk_FUN_001a29a0(pr.lo, pr.hi, r7);
        FUN_00407300();
        FUN_001d9890(x8, scratch, x1, r4, r2);
        FUN_003514e8(*(word_t *)(fnp16 + 8));
        (*fn8)();                             /* extraout_x8_02 indirect */
        FUN_0008e500(aux);                    /* unaff_x30 */
        return;
    }
    CL4_SWBP(0x46f820);   /* SoftwareBreakpoint(1,0x46f820), does not return */
    (void)p1; (void)p2;
}

/* FUN_0046f820 @ 0x46f820  (est. sk_bcg_0046f820)
 * Ghidra: void sk_bcg_0046f820(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Regex ByteCodeGen emit core: runs a long builder sequence (0xff/param_3
 * into 0x3515fc, register folding via 0x77bec/0x77824/0x4aa67c, 0x277b8
 * indirect dispatch on the 0x77dcc value), computes offsets from register
 * pairs, and on the success path (status low bit set) performs the final
 * emit through several indirect function pointers; otherwise fail-closes at
 * the 0x46fb9c software breakpoint.
 * Confidence: low   Notes: heavy extraout_xN register aliasing; masked
 * self-modifying trampoline calls (SUB_54ffff60f100041f) */
static void sk_bcg_0046f820(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    int    idx;                       /* *(int*)(reg+0x30) / 0x24 */
    word_t r2, r3, r4, r5, r9;
    word_t regA, regB;                /* unaff_x21 / unaff_x22 */
    word_t aux;                       /* unaff_x30 */
    word_t x8;                        /* extraout_x8 */
    long   x9, x12;                   /* extraout_x9 / extraout_x12 */
    code   fn8;                       /* extraout_x8_04/_05/_06 indirect */
    code   fn9;                       /* extraout_x9_01/_02 indirect */
    code   fnp;                       /* FUN_000277b8 result */
    word_t fnp16;                   /* extraout_x16 / _00 / _01 base (raw addr) */
    word_t lsize;                     /* extraout_x8_00 etc (sizes) */
    wpair_t pr;
    word_t status;

    FUN_0008e518();
    r2 = FUN_00350980();
    FUN_003515fc(0xff, param_3);
    FUN_00377824();
    FUN_0035053c();
    r3 = FUN_00377bec().lo;
    r4 = FUN_004aa67c();
    FUN_0035053c(r4, r3);
    r4 = FUN_00377824().lo;
    r5 = FUN_0034b0b4();
    FUN_003722e4(r5, r4, r4);
    regA = FUN_000a6f88();
    ((code)(uintptr_t)0x54ffff60f100041f)(*(word_t *)(x8 + 0x40)); /* masked tramp */
    FUN_003493c4();
    FUN_003503f8();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_00350464();
    FUN_0007c028();
    ((code)(uintptr_t)0x54ffff60f100041f)(*(word_t *)(x8 + 0x40)); /* masked tramp */
    FUN_0034ab10();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_0034b4c0();
    FUN_00464f4c();
    FUN_003509bc();
    FUN_00351de4();
    r5 = FUN_00377bec().lo;
    regB = FUN_00310e08(0, r4, r5);
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_00350428();
    fnp = (code)FUN_000277b8(r3);
    FUN_00350798();
    r9 = FUN_00377dcc();
    fnp(r9, r3);
    FUN_00351750(r3);
    FUN_0035084c(x9 - x12);                    /* extraout_x9_00 - extraout_x12 */
    fn9();                                     /* extraout_x9_01 indirect */
    FUN_0035166c(r5);
    pr = FUN_00351414();
    status = fn8(pr.lo, pr.hi, r4, r5);        /* extraout_x8_04 indirect */
    if ((status & 1) != 0) {
        fnp = *(code **)(fnp16 + 0x20);
        pr = FUN_00351324();
        fnp(pr.lo, pr.hi, r4);
        FUN_0035136c(x8 + *(int *)(regA + 0x30));  /* extraout_x8_01 */
        fnp();
        pr = FUN_003510b8();
        fn9(pr.lo, pr.hi, regA);               /* extraout_x9_02 indirect */
        idx = *(int *)(regA + 0x30);
        pr = FUN_003508b4();
        fnp(pr.lo, pr.hi, r4);
        fnp = *(code **)(fnp16 + 8);
        fnp(x9 + idx, r4);                     /* extraout_x9 + idx */
        pr = FUN_003510b8(*(word_t *)(fnp16 + 0x20));
        fn8(pr.lo, pr.hi, regA);               /* extraout_x8_05 indirect */
        fnp(x8 + *(int *)(regB + 0x24), x9 + *(int *)(regA + 0x30), r4);
        FUN_0009e234();
        fnp();
        fnp = (code)FUN_004a4a44(regA);        /* unaff_x21 */
        fnp(x8, r2, x8, regB, regA);           /* extraout_x8, _03, unaff_x22 */
        FUN_003508cc(*(word_t *)(fnp16 + 8));
        fn8();                                 /* extraout_x8_06 indirect */
        FUN_0008e500(aux);                     /* unaff_x30 */
        return;
    }
    CL4_SWBP(0x46fb9c);   /* SoftwareBreakpoint(1,0x46fb9c), does not return */
    (void)param_1; (void)param_2;
}

/* FUN_0046fb9c @ 0x46fb9c  (est. sk_bcg_0046fb9c)
 * Ghidra: void sk_bcg_0046fb9c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Regex ByteCodeGen emit path with a terminal dispatch on FUN_000839f8:
 * builds pairs and runs trampoline steps, calls sk_bcg_0046f820, and on
 * the FUN_000839f8==1 branch finishes via one indirect pointer; on the
 * other branch it runs the teardown chain, checks the status low bit
 * (fail-closing at 0x46feb0 if clear) and completes the emit.
 * Confidence: low   Notes: extraout_xN register aliasing; masked tramp
 * calls; &DAT_0060e208 address reference. */
static void sk_bcg_0046fb9c(word_t param_1, word_t param_2, word_t param_3)
{
    int    i1;
    word_t r3, r4, r5, r6, r7, r8;
    word_t aux;                       /* unaff_x30 */
    word_t x8;                        /* extraout_x8 */
    code   fn8;                       /* extraout_x8_01.._04 indirect */
    word_t fnp16;                   /* extraout_x16 / _00 / _01 / _02 base (raw addr) */
    wpair_t pr;
    word_t status;

    r3 = FUN_0008e518().lo;
    FUN_00351b78(0xff, param_3);
    r4 = FUN_00377824().lo;
    FUN_0035056c(param_3);
    r5 = FUN_00377bec().lo;
    r6 = FUN_004aa770();
    r6 = FUN_00377824(r6, r5, r4, 0x60e208).lo;
    FUN_00464f4c();
    FUN_0035060c();
    FUN_00351584();
    FUN_00377bec();
    r7 = FUN_00350c98();
    FUN_00319308(r7, r6);
    r6 = FUN_000a6f88();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_00350428();
    FUN_003504e8();
    FUN_00377dcc();
    r7 = FUN_000a6f88();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_00350428();
    FUN_00350500();
    FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_0034af20();
    FUN_0007c028();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_0034cff4();
    pr = FUN_00350af4();
    sk_bcg_0046f820(pr.lo, pr.hi, param_3, 0); /* register-residue arg */
    i1 = FUN_000839f8();
    if (i1 == 1) {
        FUN_00350b3c(*(word_t *)(fnp16 + 8));  /* extraout_x16_01 */
        fn8();                                 /* extraout_x8_04 indirect */
    } else {
        (**(code **)(fnp16 + 0x20))((word_t)0x60e208);  /* &DAT_0060e208 */
        (**(code **)(fnp16 + 0x20))(x8, r3, r7);        /* extraout_x8_00 */
        FUN_00027754(r4);
        r8 = FUN_0014ae44();
        FUN_00350bfc(r8, 0x60e208, 0x60e208);          /* &DAT_0060e208 */
        status = fn8();                        /* extraout_x8_01 indirect */
        if ((status & 1) == 0) {
            CL4_SWBP(0x46feb0);  /* SoftwareBreakpoint(1,0x46feb0), no return */
        }
        pr = FUN_0008e388(x8);
        thunk_FUN_001a29a0(pr.lo, pr.hi, r4);
        FUN_00407300();
        FUN_001d9890(r3, x8, r7, r6, r5);
        FUN_003514e8(*(word_t *)(fnp16 + 8));  /* extraout_x16 */
        fn8();                                 /* extraout_x8_02 indirect */
        FUN_00350ab8(*(word_t *)(fnp16 + 8));  /* extraout_x16_00 */
        fn8();                                 /* extraout_x8_03 indirect */
    }
    FUN_0008e500(i1 != 1, aux);                /* unaff_x30 */
    (void)param_1; (void)param_2;
}

/* FUN_0046feb0 @ 0x46feb0  (est. sk_bcg_0046feb0)
 * Ghidra: void sk_bcg_0046feb0(void)
 * Regex ByteCodeGen emit path: preps via 0x27754 (with in_x3), builds
 * pairs through 0x4aa770/0x77824, runs trampoline steps, calls
 * sk_bcg_0046f820, and branches on the 0x350884 status: the success path
 * runs an indirect pointer, checks the status low bit (fail-close at
 * 0x4700d4 if clear) and completes; otherwise a single indirect dispatch.
 * Confidence: low   Notes: extraout_xN register aliasing; masked tramp
 * calls; in_x3 register artifact. */
static void sk_bcg_0046feb0(word_t inreg)  /* in_x3 */
{
    word_t r2, r3, r4;
    word_t aux;                       /* unaff_x30 */
    code   fn8;                       /* extraout_x8 / _00 / _01 indirect */
    word_t fnp16;                   /* extraout_x16 / _00 / _01 base (raw addr) */
    wpair_t pr;
    word_t status;
    int    zr;                        /* in_ZR (flags) */

    FUN_0008e518();
    r2 = FUN_00027754(inreg);
    r3 = FUN_004aa770();
    FUN_00351b78(r3, r2);
    r3 = FUN_00377824().lo;
    FUN_00464f4c();
    FUN_00350b84(r2);
    r2 = FUN_00377bec().lo;
    pr = FUN_0035050c();
    FUN_0031d600(pr.lo, pr.hi, r2);
    r4 = FUN_000a6f88();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_0034b0d4();
    FUN_0035050c();
    FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_0034af20();
    FUN_0007c028();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_004aba28();
    sk_bcg_0046f820(0, 0, 0, 0); /* register-residue args */
    FUN_00350884();
    zr = /* flags from last compare */ 0;
    if (zr) {
        (**(code **)(fnp16 + 8))();             /* indirect at _00+8 */
    } else {
        pr = FUN_003510dc(*(word_t *)(fnp16 + 0x20));  /* _01+0x20 */
        fn8(pr.lo, pr.hi, r3);                 /* extraout_x8 indirect */
        FUN_00349fe0(r2);
        status = fn8();                        /* extraout_x8_00 indirect */
        if ((status & 1) == 0) {
            CL4_SWBP(0x4700d4);  /* SoftwareBreakpoint(1,0x4700d4), no return */
        }
        pr = FUN_00350618();
        thunk_FUN_001a29a0(pr.lo, pr.hi, r2);
        FUN_0040668c();
        pr = FUN_003508b4();
        FUN_00273fe0(pr.lo, pr.hi, r4, inreg);
        FUN_003508cc(*(word_t *)(fnp16 + 8));  /* extraout_x16 */
        fn8();                                 /* extraout_x8_01 indirect */
    }
    FUN_0008e500(aux);                         /* unaff_x30 */
}

/* FUN_004700d4 @ 0x4700d4  (est. sk_bcg_004700d4)
 * Ghidra: void sk_bcg_004700d4(param_1..param_5)
 * Regex ByteCodeGen slot emitter: preps via 0x633e0, folds param_5 into
 * 0x77824, computes a size from a register pair, lays out a 16-byte stack
 * pair from param_2..param_5 and dispatches through 0x351f1c with the
 * 0x4a4a74 thunk. On unaff_x21==0 it runs the 0x839f8 dispatch: the ==1
 * branch walks emit steps; otherwise an indirect dispatch at off+0x20.
 * Confidence: low   Notes: extraout_xN register aliasing; masked tramp
 * calls; unaff_x21 register artifact. */
static void sk_bcg_004700d4(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    int    i1;
    word_t r2;
    word_t x1;                        /* extraout_x1 */
    word_t x8;                        /* extraout_x8 */
    long   x9, x12, x12b, lsize;      /* extraout_x9 / extraout_x12 / _00 */
    word_t ctx;                       /* unaff_x21 */
    code   fn9;                       /* extraout_x9_00 / _01 indirect */
    code   fn8;                       /* extraout_x8_00 indirect */
    code   *fnp16;                    /* extraout_x16 base */
    word_t stack[2];                  /* auStack_80 16-byte */
    wpair_t pr;

    FUN_004633e0();
    FUN_00377824(0xff, p5);
    FUN_00352efc();
    r2 = FUN_00310d68();
    FUN_000a6f88();
    ((code)(uintptr_t)0x54ffff60f100041f)(*(word_t *)(x8 + 0x40)); /* masked tramp */
    FUN_0034ab10();
    lsize = x9 - x12;                 /* extraout_x9 - extraout_x12 */
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    /* stack pair locals: local_70=p4, uStack_68=p5, local_60=p2, uStack_58=p3 */
    FUN_00351f1c(lsize - x12b, FUN_004a4a74, (word_t)stack);  /* extraout_x12_00 */
    FUN_001d80e0();
    if (ctx == 0) {                   /* unaff_x21 */
        pr = FUN_003508cc();
        fn9(pr.lo, pr.hi, r2);        /* extraout_x9_00 indirect */
        i1 = FUN_000839f8(lsize, 1, x1);
        if (i1 == 1) {
            FUN_00310924(p5);
            FUN_00351384(p1);
            fn9();                    /* extraout_x9_01 indirect */
            FUN_00351390(lsize);
            i1 = FUN_000839f8();
            if (i1 != 1) {
                FUN_00350a70(*(word_t *)(fnp16 + 8));
                fn8();                /* extraout_x8_00 indirect */
            }
        } else {
            (**(code **)(*(word_t *)(x1 - 8) + 0x20))(p1, lsize, x1);
        }
    }
}

/* FUN_00470298 @ 0x470298  (est. sk_bcg_00470298)
 * Ghidra: void sk_bcg_00470298(void)
 * Regex ByteCodeGen emit path: builds a pair from 0x53cfc, folds in_x3 via
 * 0x4aa770/0x77824, calls sk_bcg_004700d4, and on unaff_x21==0 runs the
 * teardown chain (0x27754, 0x351f4c), checks the status low bit
 * (fail-close at 0x47042c if clear), and completes the emit.
 * Confidence: low   Notes: extraout_xN register aliasing; masked tramp
 * calls; in_x3/unaff_x21 register artifacts; &DAT_0060e208. */
static void sk_bcg_00470298(word_t inreg)  /* in_x3 */
{
    word_t r2, r3;
    word_t aux;                       /* unaff_x30 */
    word_t ctx;                       /* unaff_x21 */
    word_t x8;                        /* extraout_x8 */
    code   fn8;                       /* extraout_x8_00 / _01 indirect */
    code   *fnp16;                    /* extraout_x16 base */
    wpair_t pr;
    word_t status;

    pr = FUN_00353cfc();
    r2 = FUN_004aa770();
    r2 = FUN_00377824(r2, inreg).lo;
    FUN_00464f4c();
    pr = FUN_000e15d8();
    r3 = FUN_00377bec(pr.lo, pr.hi, r2, 0x60e208).lo;   /* &DAT_0060e208 */
    pr = FUN_003508e4();
    FUN_00319308(pr.lo, pr.hi, r3);
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_0034b0c4();
    FUN_003509c8(r2);
    FUN_0007c1a4();
    ((code)(uintptr_t)0x54ffff60f100041f)();   /* masked tramp */
    FUN_0034b0d4();
    FUN_00351e3c(pr.lo, pr.hi);
    sk_bcg_004700d4(0,0,0,0,0); /* register-residue args */
    if (ctx == 0) {                   /* unaff_x21 */
        FUN_00027754(r3);
        r2 = FUN_0014ae44();
        FUN_00351f4c(r2);
        status = fn8();               /* extraout_x8_00 indirect */
        if ((status & 1) == 0) {
            CL4_SWBP(0x47042c);  /* SoftwareBreakpoint(1,0x47042c), no return */
        }
        pr = FUN_00350914(0x60e208);  /* &DAT_0060e208 */
        thunk_FUN_001a29a0(pr.lo, pr.hi, r3);
        FUN_00407300();
        FUN_00350518();
        FUN_00351e3c(x8);
        FUN_001d9890();
        FUN_00350518(*(word_t *)(fnp16 + 8));  /* extraout_x16 */
        fn8();                        /* extraout_x8_01 indirect */
    }
    FUN_00353d14(aux);                /* unaff_x30 */
}

/* ==================== SKR27 function bodies ==================== */


/* ---- Part 3: extra externs used by this part but absent from the shared
 * header (out-of-slice callees + thunks + masked trampoline). ---- */
extern word_t thunk_FUN_0006f6b4(); /* thunk -> FUN_0006f6b4 */
extern word_t thunk_FUN_001a29a0(); /* thunk -> FUN_001a29a0 */
extern wpair_t thunk_FUN_002b74c0();
extern word_t DAT_0060e208;
extern word_t DAT_00611b24;
extern word_t LAB_00611b34; /* thunk -> FUN_002b74c0 */
extern void SUB_54ffff60f100041f(void); /* masked self-modifying/trampoline fn */

/* Forward declarations of this part's own static functions (cross-calls). */
static void sk_bcg_0047042c(void);
static void sk_bcg_00470644(word_t p1, word_t p2, word_t p3, word_t p4);
static void sk_bcg_00470998(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00470ae4(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00470c28(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00470d88(void);
static void sk_bcg_00470ebc(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00470ff8(word_t p1, word_t p2, long p3);
static void sk_bcg_0047153c(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6);
static void sk_bcg_00471644(word_t p1, word_t p2, word_t p3, long param_4, code *param_5, word_t p6, word_t p7, word_t p8, word_t p9, word_t param_10);
static void sk_bcg_00471aec(word_t p1, word_t p2, word_t p3);
static void sk_bcg_00471c14(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6, word_t p7, word_t p8, word_t p9, word_t p10, word_t p11, word_t p12);
static void sk_bcg_00471cfc(void);
static void sk_bcg_00471e78(void);
static void sk_bcg_00471f20(void);
/* FUN_0047042c @ 0x0047042c   (est. sk_bcg_0047042c)
 * Ghidra: void sk_bcg_0047042c(void)
 * Regex ByteCodeGen setup helper: opens a builder context (FUN_00353cfc),
 * resolves a label/target pair (FUN_00377824), then runs a sequence of
 * codegen fixups through a masked trampoline. When the pending continuation
 * register is clear it performs a fail-closed check and finalizes a
 * sub-expression build via thunk_FUN_001a29a0 / FUN_001d9890.
 * Confidence: medium   Notes: DAT_0060e208; masked trampoline SUB_...041f */
static void sk_bcg_0047042c(void)
{
    wpair_t r6;                 /* auVar6[16] */
    word_t t1;                  /* uVar1 */
    word_t t2;                  /* uVar5 = uVar1 */
    word_t t3;                  /* uVar2 */
    word_t in_x3 = 0;           /* in_x3 (incoming x3) */
    word_t x21 = 0;             /* unaff_x21 */
    word_t x20 = 0;             /* unaff_x20 */
    word_t x30 = 0;             /* unaff_x30 */
    word_t e_x8, e_x16, e_x16b; /* extraout_x8 / x16 / x16_00 */
    code x9_fn, x8fn, x8fn2;    /* function pointers carried in x8/x9 */

    r6 = (wpair_t)FUN_00353cfc();
    t1 = (word_t)FUN_004aa770();
    t1 = FUN_00377824(t1, in_x3).lo;
    FUN_00464f4c();
    FUN_003510b8();
    t2 = t1;
    FUN_00377bec();
    t3 = (word_t)FUN_00350c98();
    t3 = (word_t)FUN_00319308(t3, t1);
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();                      /* masked self-modifying/trampoline fn */
    FUN_0034aee4();
    FUN_0007c028();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x8 + 0x40)); /* masked; arg = *(extraout_x8+0x40) */
    FUN_000aa4ec();
    FUN_004ac2ac();
    FUN_003509c8(t1);
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();                      /* masked self-modifying/trampoline fn */
    FUN_0034af20();
    FUN_00350a1c(r6.lo, r6.hi);
    sk_bcg_004700d4(0,0,0,0,0); /* register-residue args */
    if (x21 == 0) {
        FUN_00350624(&DAT_0060e208);      /* DAT_0060e208 */
        ((code)x9_fn)();                  /* (*extraout_x9)() */
        FUN_00027754(t2);
        code fn = (code)FUN_0014ae44();   /* pcVar3 */
        word_t r = fn();                  /* uVar4 = (*pcVar3)() */
        if ((r & 1) == 0) {
            CL4_SWBP(0x470644);           /* SoftwareBreakpoint(1,0x470644) */
        }
        r6 = FUN_00350b3c();
        thunk_FUN_001a29a0(r6.lo, r6.hi, t2);
        FUN_00407300();
        r6 = (wpair_t)FUN_003505e8(x20);
        FUN_001d9890(r6.lo, r6.hi, t3, in_x3);
        FUN_000a6e14(*(word_t *)(e_x16 + 8));
        ((code)x8fn)();                   /* (*extraout_x8_00)() */
        FUN_00350524(*(word_t *)(e_x16b + 8));
        ((code)x8fn2)();                  /* (*extraout_x8_01)() */
    }
    FUN_00353d14(x30);
    return;
}

/* FUN_00470644 @ 0x00470644   (est. sk_bcg_00470644)
 * Ghidra: void sk_bcg_00470644(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)
 * Regex ByteCodeGen continuation builder: resolves a node id (FUN_00027754),
 * chains label/target + child references, then, when the pending register is
 * clear, performs a fail-closed dispatch through several resolved function
 * pointers (FUN_000277b8, FUN_00310e20) and finalizes with node-copy and
 * link helpers. Uses a masked trampoline for fixups.
 * Confidence: medium   Notes: masked trampoline SUB_...041f; pointer-table
 *                          calls via extraout_x16 */
static void sk_bcg_00470644(word_t p1, word_t p2, word_t p3, word_t p4)
{
    wpair_t r10, r11;           /* auVar10/auVar11[16] */
    word_t t2, t3, t4;          /* uVar2/uVar3/uVar4 */
    long l5, l6;                /* lVar5/lVar6 */
    code fn_a, fn_b, fn_c, fn_d, fn_e, fn_f; /* pcVar7/pcVar9/extraout fn ptrs */
    word_t e_x8, e_x8b, e_x9, e_x12, e_x16, e_x16b; /* extraout regs */
    word_t x21 = 0, x25 = 0, x30 = 0;  /* unaff_x21/x25/x30 */
    word_t e_x16c;              /* extraout_x16_01 */
    int i;                      /* iVar1 */

    r10 = (wpair_t)FUN_00353cfc();
    t2 = (word_t)FUN_00027754(p4);
    t3 = (word_t)FUN_004aa67c();
    t3 = FUN_00377824(t3, t2, p3).lo;
    t4 = (word_t)FUN_0034b0b4();
    FUN_004ab644(t4, t3);
    l5 = (long)FUN_003722e4();
    FUN_000a6f88();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x8 + 0x40)); /* masked; *(extraout_x8+0x40) */
    FUN_003493c4();
    FUN_003503f8();
    ((code)&SUB_54ffff60f100041f)();                          /* masked trampoline fn */
    FUN_00350464();
    FUN_00464f4c();
    FUN_003513b4(t2);
    t4 = FUN_00377bec().lo;
    r11 = (wpair_t)FUN_0035050c();
    l6 = (long)FUN_00310e08(r11.lo, r11.hi, t4);
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();                          /* masked trampoline fn */
    FUN_004aba28();
    FUN_0007c028();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x8b + 0x40)); /* masked; *(extraout_x8_01+0x40) */
    FUN_0034ab10();
    FUN_0034b540();
    ((code)&SUB_54ffff60f100041f)();                          /* masked trampoline fn */
    sk_bcg_004700d4(e_x8 - e_x12, r10.lo, r10.hi, p3, t2);       /* args from extraout_x8_00/x12 */
    if (x21 == 0) {
        fn_a = (code)FUN_000277b8(t2);
        fn_a(p3, t2);
        fn_b = (code)FUN_00310e20(t4);
        {
            word_t r8 = fn_b();                 /* uVar8 = (*pcVar7)() */
            if ((r8 & 1) == 0) {
                CL4_SWBP(0x470998);             /* SoftwareBreakpoint(1,0x470998) */
            }
        }
        fn_c = *(code **)(e_x16c + 0x20);       /* pcVar9 = *(extraout_x16_01+0x20) */
        r10 = FUN_0035145c();
        fn_c(r10.lo, r10.hi, t3);
        FUN_00350b84(e_x8 + *(int *)(l5 + 0x30)); /* arg = extraout_x8_00 + *(lVar5+0x30) */
        fn_c();
        r10 = (wpair_t)FUN_000e72b0();
        fn_d(r10.lo, r10.hi, l5);               /* (*extraout_x9_00)(...) */
        i = *(int *)(l5 + 0x30);
        r10 = (wpair_t)FUN_00350914();
        fn_c(r10.lo, r10.hi, t3);
        fn_e = *(code **)(e_x16c + 8);          /* pcVar7 = *(extraout_x16_01+8) */
        fn_e(e_x9 + i, t3);                     /* (extraout_x9 + iVar1, uVar3) */
        r10 = (wpair_t)FUN_000e72b0(*(word_t *)(e_x16 + 0x20));
        fn_f(r10.lo, r10.hi, l5);               /* (*extraout_x8_02)(...) */
        fn_c(x25 + *(int *)(l6 + 0x24), e_x9 + *(int *)(l5 + 0x30), t3); /* (unaff_x25+.., extraout_x9+.., uVar3) */
        FUN_00100c38();
        fn_e();
        fn_a = (code)FUN_0031d488(p4);
        fn_a(x25, p3, p4);                      /* (unaff_x25, p3, p4) */
        FUN_003508cc(*(word_t *)(e_x16b + 8));
        fn_b();                                 /* (*extraout_x8_03)() */
    }
    FUN_00353d14(x30);
    return;
}

/* FUN_00470998 @ 0x00470998   (est. sk_bcg_00470998)
 * Ghidra: void sk_bcg_00470998(undefined8 p1,...,undefined8 p6)
 * Regex ByteCodeGen node builder: after a masked-trampoline fixup round it
 * stages a 6-word record (FUN_00499450(0,&record)) and pushes it into the
 * current builder through two resolved function pointers (FUN_00350618 /
 * FUN_00350b3c), then finishes the node. Ends with the shared epilogue.
 * Confidence: medium   Notes: masked trampoline SUB_...041f; in-stack record */
static void sk_bcg_00470998(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6)
{
    wpair_t r2;                 /* auVar2[16] */
    word_t t1;                  /* uVar1 = param_3 */
    word_t e_x1, e_x8, e_x16, e_x16b; /* extraout_x1/x8/x16/x16_00 */
    code x9fn, x8fn, x8fn2;     /* function pointers in x8/x9 */
    word_t x30 = 0;             /* unaff_x30 */
    word_t rec[6];              /* local_28..local_8 (6-word record) */

    FUN_0008e518();
    t1 = p3;
    FUN_0007c028();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x8 + 0x40)); /* masked; *(extraout_x8_00+0x40) */
    FUN_000aa4ec();
    FUN_004aba28();
    rec[0] = e_x1;              /* local_28 = extraout_x1 */
    rec[1] = t1;                /* uStack_20 = uVar1 */
    rec[2] = p4;                /* local_18 */
    rec[3] = p5;                /* uStack_10 */
    rec[4] = p6;                /* local_8 */
    FUN_00499450(0, &rec);
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();                          /* masked trampoline fn */
    FUN_0034af20();
    r2 = (wpair_t)FUN_00350618();
    x9fn(r2.lo, r2.hi, p3);     /* (*extraout_x9)(r2_0, r2_8, p3) */
    r2 = (wpair_t)FUN_00350b3c(*(word_t *)(e_x16 + 0x20));
    x8fn(r2.lo, r2.hi, p3);     /* (*extraout_x8_01)(...) */
    FUN_00350b9c(e_x8);
    sk_bcg_0046f54c(0,0,0,0); /* register-residue args */
    FUN_00350ab8(*(word_t *)(e_x16b + 8));
    x8fn2();                    /* (*extraout_x8_02)() */
    FUN_0008e500(x30);
    return;
}

/* FUN_00470ae4 @ 0x00470ae4   (est. sk_bcg_00470ae4)
 * Ghidra: void sk_bcg_00470ae4(undefined8 p1,...,undefined8 p6)
 * Regex ByteCodeGen node builder (sibling of FUN_00470998): stages a 6-word
 * record via FUN_00499450, resolves two push fns (FUN_003504c4 /
 * FUN_000e72b0) and appends the node, then closes with FUN_00084234.
 * Confidence: medium   Notes: masked trampoline SUB_...041f; in-stack record */
static void sk_bcg_00470ae4(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6)
{
    wpair_t r2;                 /* auVar2[16] */
    word_t t1;                  /* uVar1 = param_3 */
    word_t e_x1, e_x8, e_x16, e_x16b; /* extraout regs */
    code x9fn, x8fn, x8fn2;     /* function pointers in x8/x9 */
    word_t x30 = 0;             /* unaff_x30 */
    word_t rec[6];

    FUN_00084220();
    t1 = p3;
    FUN_0007c028();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x8 + 0x40)); /* masked; *(extraout_x8+0x40) */
    FUN_000aa4ec();
    FUN_004ac2ac();
    rec[0] = e_x1;
    rec[1] = t1;
    rec[2] = p4;
    rec[3] = p5;
    rec[4] = p6;
    FUN_00499450(0, &rec);
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();                          /* masked trampoline fn */
    FUN_0034aee4();
    r2 = FUN_003504c4();
    x9fn(r2.lo, r2.hi, p3);     /* (*extraout_x9)(...) */
    r2 = (wpair_t)FUN_000e72b0(*(word_t *)(e_x16 + 0x20));
    x8fn(r2.lo, r2.hi, p3);     /* (*extraout_x8_00)(...) */
    sk_bcg_0046fb9c(0,0,0); /* register-residue args */
    FUN_00100c38(*(word_t *)(e_x16b + 8));
    x8fn2();                    /* (*extraout_x8_01)() */
    FUN_00084234(x30);
    return;
}

/* FUN_00470c28 @ 0x00470c28   (est. sk_bcg_00470c28)
 * Ghidra: void sk_bcg_00470c28(undefined8 p1,...,undefined8 p6)
 * Regex ByteCodeGen node builder: resolves a child id (FUN_00027754), stages
 * the 6-word record, then pushes the node via two resolved fns (FUN_003509b0
 * and a helper behind a masked trampoline). Ends with FUN_0008e500.
 * Confidence: medium   Notes: masked trampoline SUB_...041f; in-stack record */
static void sk_bcg_00470c28(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6)
{
    wpair_t r1;                 /* auVar1[16] */
    word_t e_x1;                /* extraout_x1 */
    word_t e_x8, e_x8b;         /* extraout_x8 / x8_00 */
    word_t e_x9;                /* extraout_x9 */
    code x9fn, x8fn, x8fn2;     /* extraout_x9_00 / x8_01 / x8_02 */
    word_t e_x16, e_x16b;       /* extraout_x16 / x16_00 */
    word_t x30 = 0;             /* unaff_x30 */
    word_t rec[6];

    FUN_0008e518();
    FUN_0007c028();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x8 + 0x40)); /* masked; *(extraout_x8+0x40) */
    FUN_000aa4ec();
    rec[2] = (word_t)FUN_00027754(p4);   /* local_18 = FUN_00027754(p4) */
    rec[0] = e_x1;                       /* local_28 = extraout_x1 */
    rec[1] = p3;                         /* uStack_20 = p3 */
    rec[3] = p5;                         /* uStack_10 = p5 */
    rec[4] = p6;                         /* local_8 = p6 */
    FUN_00499450(0, &rec);
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();     /* masked trampoline fn */
    FUN_0034af20();
    FUN_0035139c(e_x9 - e_x8b);          /* arg = extraout_x9 - extraout_x8_00 */
    x9fn();                              /* (*extraout_x9_00)() */
    r1 = FUN_003509b0(*(word_t *)(e_x16 + 0x20));
    x8fn(r1.lo, r1.hi, p3);              /* (*extraout_x8_01)(...) */
    FUN_00351178();
    sk_bcg_0046feb0(0); /* register-residue arg */
    FUN_00350b3c(*(word_t *)(e_x16b + 8));
    x8fn2();                             /* (*extraout_x8_02)() */
    FUN_0008e500(x30);
    return;
}

/* FUN_00470d88 @ 0x00470d88   (est. sk_bcg_00470d88)
 * Ghidra: void sk_bcg_00470d88(void)
 * Regex ByteCodeGen range/span helper: registers a range callback
 * (FUN_00270c08 with FUN_004b5a74), builds a span, then — when the in-stack
 * length word is nonzero — performs a fail-closed page-boundary check
 * ((in>>0xe) < (out>>0xe) traps at 0x470ebc) and copies the span through
 * FUN_00352c40 / thunk_FUN_002b74c0.
 * Confidence: medium   Notes: in-stack args; unreachable block removed;
 *                          DAT_0060e208-free */
static void sk_bcg_00470d88(void)
{
    wpair_t r7;                 /* auVar7[16] */
    word_t t2, t5, t6;          /* uVar2/uVar5/uVar6 */
    word_t t1, t3;              /* uVar1/uVar3 */
    code x8fn;                  /* extraout_x8 */
    word_t in_x3 = 0, in_x4 = 0;      /* in_x3/in_x4 */
    word_t e_x1;                /* extraout_x1 */
    /* in-stack args (implicit incoming stack words) */
    word_t s10 = 0, s18 = 0, s28 = 0, s30 = 0, s38 = 0; /* in_stack_..10/18/28/30/38 */

    FUN_0035a9b0();
    FUN_00356bb0(in_x3);
    FUN_00270c08(&s10, FUN_004b5a74, 0, e_x1);   /* (addr, callback, 0, x1) */
    t2 = s28;                   /* uVar2 = in_stack_00000028 */
    t1 = s18;                   /* uVar1 = in_stack_00000018 */
    t6 = s10;                   /* uVar6 = in_stack_00000010 */
    FUN_004ab5d4(in_x4);
    FUN_003504f4();
    t5 = x8fn();                /* uVar5 = (*extraout_x8)() */
    FUN_004aa95c();
    FUN_00351178();
    FUN_00377824();
    FUN_0034be0c(&s10, t6);
    sk_bcg_0046ea18(0,0,0,0,0); /* register-residue args */
    FUN_0036b118(t5);
    t3 = s30;                   /* uVar3 = in_stack_00000030 */
    if (s18 != 0) {
        FUN_004acc20();
        s38 = 0;
        FUN_004aa938();
        FUN_004a4b14(&s38);
        if ((t1 >> 0xe) < (t3 >> 0xe)) {
            CL4_SWBP(0x470ebc);           /* SoftwareBreakpoint(1,0x470ebc) */
        }
        r7 = (wpair_t)FUN_00350af4();
        FUN_00352c40(r7.lo, r7.hi, t6);
        t6 = thunk_FUN_002b74c0().lo;
        FUN_003a25d4(t2);
    }
    FUN_0034be0c(t6);
    FUN_0035a8d0();
    return;
}

/* FUN_00470ebc @ 0x00470ebc   (est. sk_bcg_00470ebc)
 * Ghidra: void sk_bcg_00470ebc(undefined8 p1,...,undefined8 p6)
 * Regex ByteCodeGen span/range builder (sibling of FUN_00470d88): registers a
 * range callback and builds a span via FUN_0046ea18, then, when the in-stack
 * length is nonzero, re-links the child node through FUN_0031d488 /
 * FUN_0035136c and clears the record via FUN_004a4b14.
 * Confidence: medium   Notes: in-stack args; unreachable block removed */
static void sk_bcg_00470ebc(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6)
{
    wpair_t r6;                 /* auVar6[16] */
    word_t t1, t3, t4, t5;      /* uVar1/uVar3/uVar4/uVar5 */
    long l2;                    /* lVar2 */
    code x8fn, x8fn2;           /* extraout_x8 / x8_00 */
    word_t e_x1;                /* extraout_x1 */
    word_t x30 = 0;             /* unaff_x30 */
    /* in-stack args */
    word_t s10 = 0, s18 = 0, s30 = 0, s38 = 0, s40 = 0, s48 = 0;
    word_t s50 = 0, s58 = 0, s60 = 0, s68 = 0;

    FUN_0035638c();
    FUN_00356bb0(p4);
    FUN_00270c08(&s30, FUN_004b5a74, 0, e_x1);
    t3 = s48;                   /* uVar3 = in_stack_00000048 */
    t1 = s40;                   /* uVar1 = in_stack_00000040 */
    FUN_004ab5d4(p6);
    FUN_003507bc();
    t4 = x8fn();                /* uVar4 = (*extraout_x8)() */
    t5 = (word_t)FUN_004aa95c();
    FUN_00377824(t5, p6, p3);
    r6 = FUN_00350a04(&s30);
    sk_bcg_0046ea18(r6.lo, r6.hi, t1, t3, t4);
    FUN_003a25d4(t3);
    FUN_0036b118(t4);
    t3 = s40;                   /* uVar3 = in_stack_00000040 */
    l2 = s38;                   /* lVar2 = in_stack_00000038 */
    t1 = s30;                   /* uVar1 = in_stack_00000030 */
    if (s38 != 0) {
        s18 = s50;              /* in_stack_18 = in_stack_50 */
        s10 = s48;              /* in_stack_10 = in_stack_48 */
        t4 = (word_t)FUN_0031d488(p5);
        FUN_0035136c(t4, &s10);
        x8fn2();                /* (*extraout_x8_00)() */
        s60 = t1;               /* in_stack_60 = uVar1 */
        s68 = l2;               /* in_stack_68 = lVar2 */
        FUN_000f5e5c(&s60);
        s58 = t3;               /* in_stack_58 = uVar3 */
        FUN_004aa938();
        FUN_004a4b14(&s58);
    }
    FUN_00356370(x30);
    return;
}

/* FUN_00470ff8 @ 0x00470ff8   (est. sk_bcg_00470ff8)
 * Ghidra: void sk_bcg_00470ff8(undefined8 p1,undefined8 p2,long p3)
 * Regex ByteCodeGen top-level node emitter: reads child/target words at
 * p3+0x10..+0x28, resolves them (FUN_00027754/FUN_00377824), then runs the
 * main emit loop. Each iteration calls the emit fn (FUN_000a68f4) and checks a
 * fail-closed flag (in_ZR); on success it finishes via a finalize fn and
 * returns 0; otherwise it tries alternative paths (FUN_0014ae44 predicate,
 * FUN_000277e8/FUN_00027818) with a LAB_004714d4/00471514 retry structure.
 * Confidence: medium   Notes: DAT_00611b24 / LAB_00611b34 label table; masked
 *                          trampoline SUB_...041f; in-stack record at +0x40 */
static void sk_bcg_00470ff8(word_t p1, word_t p2, long p3)
{
    int i1;                     /* iVar1 */
    word_t t2, t3, t4, t5;      /* uVar2/uVar3/uVar4/uVar5 */
    word_t t11, t12, t13, t14;  /* uVar11..uVar14 (node words) */
    long l6, l8;                /* lVar6/lVar8 */
    word_t r10;                 /* uVar10 */
    code fn, fn2;               /* pcVar7/pcVar9 */
    wpair_t a15;                /* auVar15[16] */
    word_t e_x1;                /* extraout_x1 */
    word_t e_x8, e_x8b, e_x8c;  /* extraout_x8 / x8_01 / x8_02 */
    word_t e_x9, e_x9b;         /* extraout_x9 / x9_00 */
    word_t e_x12, e_x16, e_x16b; /* extraout_x12/x16/x16_00 */
    word_t e_x16c;              /* extraout_x16_01 */
    code x8fn1, x8fn2, x8fn3, x8fn4, x8fn6, x8fn7, x8fn8, x8fn9; /* extraout_x8_0* */
    wpair_t (*x8fn5)();  /* extraout_x8_06: 16-byte pair return */
    code x9fn;                  /* extraout_x9_01 */
    word_t x20 = 0, x30 = 0;    /* unaff_x20/x30 */
    word_t local_50;            /* local_50 */
    word_t st40;                /* stack0x00000040 */
    bool in_ZR = 0;             /* in_ZR (zero-flag) */
    unsigned char auStack_28[40];   /* auStack_28 local byte buffer */

    FUN_0008e518();
    t13 = *(word_t *)(p3 + 0x20);
    t2 = (word_t)FUN_00027754(t13);
    t14 = *(word_t *)(p3 + 0x10);
    t2 = FUN_00377824(0xff, t2, t14, &DAT_00611b24, &LAB_00611b34).lo;
    FUN_003508e4();
    t3 = (word_t)FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();                           /* masked trampoline fn */
    FUN_00350428();
    FUN_004ac36c();
    FUN_0007c028();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x8b + 0x40));  /* masked; *(extraout_x8_00+0x40) */
    FUN_003493c4();
    FUN_003503f8();
    ((code)&SUB_54ffff60f100041f)();                           /* masked trampoline fn */
    FUN_00350464();
    t12 = *(word_t *)(p3 + 0x18);
    FUN_0007c028();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x8c + 0x40));  /* masked; *(extraout_x8_02+0x40) */
    FUN_000aa4ec();
    t11 = *(word_t *)(p3 + 0x28);
    FUN_003505c4(0);
    t4 = FUN_00377824().lo;
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();                           /* masked trampoline fn */
    FUN_0034cff4();
    t5 = (word_t)FUN_004aa47c();
    t5 = FUN_00377824(t5, t13, t14).lo;
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();                           /* masked trampoline fn */
    l6 = (e_x9b - e_x8) - e_x8c;      /* (extraout_x9_00 - extraout_x8_03) - extraout_x8_04 */
    (**(code **)(e_x12 + 0x10))(l6, e_x1);
    (**(code **)(e_x16b + 0x10))(e_x9b - e_x8, x20, t12);
    FUN_000a68c4(t11);
    FUN_003504c4(&DAT_00611b24);
    x9fn();                          /* (*extraout_x9_01)() */
    a15 = (wpair_t)FUN_000e15d8();
    FUN_00407eac(a15.lo, a15.hi, t4);
    t11 = FUN_00377bec().lo;
    fn = (code)FUN_000a68f4();
    do {
        fn(local_50, t4, t11);       /* (*pcVar7)(local_50,uVar4,uVar11) */
        FUN_00350884(local_50, 1, t2);
        if (in_ZR) {
            (**(code **)(e_x16c + 8))(&DAT_00611b24, t4);
            FUN_00350bc0(&st40);
            x8fn7(local_50, t3);     /* (*extraout_x8_08)(local_50,uVar3) */
            (**(code **)(e_x12 + 0x20))(e_x8, l6, t5);
            t2 = 0;
            goto done_00471514;
        }
        a15 = (wpair_t)FUN_0008e388(*(word_t *)(e_x16 + 0x20));
        x8fn4(a15.lo, a15.hi, t2);   /* (*extraout_x8_05)(...) */
        a15 = FUN_003514e8();
        FUN_0046490c(a15.lo, a15.hi, t5);
        FUN_00464f4c();
        t12 = FUN_00377bec().lo;
        a15 = FUN_00350798();
        l8 = (long)FUN_00310e08(a15.lo, a15.hi, t12);
        i1 = *(int *)(l8 + 0x24);
        t12 = (word_t)FUN_00027754(t12);
        fn2 = (code)FUN_0014ae44();
        r10 = fn2(l6, e_x1 + i1, t5, t12);   /* (*pcVar9)(...) */
        if ((r10 & 1) != 0) {
            FUN_00351130(*(word_t *)(e_x16 + 8));
            x8fn8();                 /* (*extraout_x8_09)() */
            goto retry_004714d4;
        }
        t12 = (word_t)FUN_000277e8(t13);
        FUN_00350a1c(t12, auStack_28, l6);
        a15 = x8fn5();      /* auVar15 = (*extraout_x8_06)() */
        (**(code **)(e_x16 + 0x10))(e_x9, a15.hi, t2);
        ((code)a15.lo)(auStack_28, auStack_28, 0);   /* (*auVar15._0_8_)(...) */
        t12 = (word_t)FUN_0014ae44(*(word_t *)(p3 + 0x30));
        FUN_00351f4c(t12, e_x9, e_x8b);
        r10 = x8fn6();               /* uVar10 = (*extraout_x8_07)() */
        fn2 = *(code **)(e_x16 + 8);
        FUN_00350ab8();
        fn2();
        FUN_00351130();
        fn2();
        if ((r10 & 1) == 0) goto retry_004714d4;
        fn2 = (code)FUN_00027818(t13);
        fn2(l6, t14, t13);
    } while (1);
    /* fallthrough only via goto above */
retry_004714d4: {
        (**(code **)(e_x16c + 8))(&DAT_00611b24, t4);
        (**(code **)(e_x12 + 8))(l6, t5);
        t2 = 1;
    }
done_00471514: {
        FUN_00351c7c(e_x8, t2);
        FUN_000839d8();
        FUN_0008e500(x30);
        return;
    }
}

/* FUN_0047153c @ 0x0047153c   (est. sk_bcg_0047153c)
 * Ghidra: void sk_bcg_0047153c(undefined8 p1,...,undefined8 p6)
 * Regex ByteCodeGen span builder: registers a range callback (FUN_00270c08
 * with FUN_004b5a74), builds a span via FUN_00467678, then writes the 5-word
 * in-stack span record back through an extraout_x8 array pointer.
 * Confidence: medium   Notes: in-stack args; unreachable block removed */
static void sk_bcg_0047153c(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6)
{
    wpair_t r8;                 /* auVar8[16] */
    word_t t1, t2, t3, t4, t5, t6, t7;  /* uVar1..uVar7 */
    word_t e_x1;                /* extraout_x1 */
    word_t *xp8;                /* extraout_x8 (pointer) */
    code x8fn;                  /* extraout_x8_00 */
    word_t x30 = 0;             /* unaff_x30 */
    word_t s28, s30, s38, s40, s48;   /* in-stack args */

    FUN_000b4594();
    FUN_00356bb0(p5);
    FUN_00270c08(&s28, FUN_004b5a74, 0, e_x1);
    t4 = s40;                   /* uVar4 = in_stack_00000040 */
    t1 = s38;                   /* uVar1 = in_stack_00000038 */
    FUN_004ab5d4(p6);
    FUN_00350560();
    t7 = x8fn();                /* uVar7 = (*extraout_x8_00)() */
    r8 = FUN_00350a04(&s28);
    FUN_00467678(r8.lo, r8.hi, t1, t4, t7, p3);
    t6 = s48;                   /* uVar6 = in_stack_00000048 */
    t5 = s40;                   /* uVar5 = in_stack_00000040 */
    t3 = s38;                   /* uVar3 = in_stack_00000038 */
    t2 = s30;                   /* uVar2 = in_stack_00000030 */
    t1 = s28;                   /* uVar1 = in_stack_00000028 */
    FUN_003a25d4(t4);
    FUN_0036b118(t7);
    xp8[1] = t2;                /* extraout_x8[1] = uVar2 */
    xp8[0] = t1;                /* *extraout_x8 = uVar1 */
    xp8[3] = t5;                /* extraout_x8[3] = uVar5 */
    xp8[2] = t3;                /* extraout_x8[2] = uVar3 */
    xp8[4] = t6;                /* extraout_x8[4] = uVar6 */
    FUN_000b45b0(x30);
    return;
}

/* FUN_00471644 @ 0x00471644   (est. sk_bcg_00471644)
 * Ghidra: void sk_bcg_00471644(p1,p2,p3,long param_4,code *param_5,p6..p10)
 * Regex ByteCodeGen main span-emit driver: validates param_4>=0, builds a
 * node record (local_48), registers an emit callback (param_5), and walks a
 * linked list (FUN_0001ba10 / FUN_0019ed3c) emitting each element. Performs
 * a fail-closed page-boundary check ((local_30>>0xe)<(uVar10>>0xe) traps at
 * 0x471ae8). Terminates the walk when the list head matches the sentinel.
 * Confidence: medium   Notes: masked trampoline SUB_...041f; DAT_005a3c78/80,
 *                          DAT_004e8268 string refs */
static void sk_bcg_00471644(word_t p1, word_t p2, word_t p3, long param_4,
                            code *param_5, word_t p6, word_t p7, word_t p8,
                            word_t p9, word_t param_10)
{
    word_t t1, t2, t3, t6, t7;  /* uVar1/uVar2/uVar3/uVar6/uVar7 */
    word_t r10;                 /* uVar10 */
    code fn, fn2;               /* pcVar4/pcVar5 */
    long l8, l9;                /* lVar8/lVar9 */
    wpair_t r11;                /* auVar11[16] */
    word_t e_x1;                /* extraout_x1 */
    word_t e_x8, e_x8b;         /* extraout_x8 / x8_00 */
    word_t e_x9;                /* extraout_x9 / x9_00 */
    code x9fn;                  /* extraout_x9_01 */
    word_t e_x16, e_x16b;       /* extraout_x16 / x16_00 */
    word_t x21 = 0;             /* unaff_x21 */
    word_t x30 = 0;             /* unaff_x30 */
    /* locals from the decompile */
    word_t local_48, local_50, local_70, local_80, local_28, local_30, local_38;
    word_t uStack_68, uStack_78, uStack_40, uStack_18, local_20;
    word_t s60, s68, s70, s78, s80;  /* in_stack_00000060..80 */

    FUN_00353cfc();
    FUN_003509c8();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x16 + 0x40));  /* masked; *(extraout_x16+0x40) */
    t2 = (word_t)FUN_000aa4ec();
    if (param_4 < 0) {
        CL4_SWBP(0x471aec);     /* SoftwareBreakpoint(1,0x471aec) */
    }
    FUN_0031e0d4(s70);
    FUN_00351354(e_x8);
    x9fn();                     /* (*extraout_x9_01)() */
    local_70 = e_x1;
    FUN_00002534(0x657bd0, &DAT_005a3c78);
    t3 = (word_t)FUN_00027754(s70);
    FUN_0040668c();
    FUN_0035053c(&local_48, &local_70, p7);
    FUN_001d9890();
    fn = (code)FUN_0031d678(s70);
    FUN_004aa878();
    fn(&local_48, 0x675c68);
    local_70 = e_x1;
    uStack_68 = p3;
    fn2 = (code)FUN_00319628(t3);
    fn2(&local_48, &local_70, p7, t3);
    t6 = (word_t)FUN_003272b8();
    sk_bcg_00471aec(t2, 0x675c68, p8); t7 = 0; /* void call; register-residue */
    FUN_003a25d4(local_30);
    local_70 = t7;
    FUN_004974ac(0xff, p8);
    FUN_0035050c();
    t2 = (word_t)FUN_00310d34();
    t6 = (word_t)FUN_00376820(&DAT_004e8268, t2);
    FUN_001bb7a0(&local_48, param_4, t2, t6);
    t7 = local_48;
    FUN_003515d8(local_48);
    l8 = (long)FUN_0001ba10();
    local_50 = l8;
    FUN_004ac85c(t7);
    FUN_003515d8();
    FUN_004ab9b0();
    l9 = (long)FUN_0019ed3c();
    r10 = e_x1;
    do {
        if (l8 == l9) {
            FUN_0036b118(t7);
            local_80 = r10;
            r11 = (wpair_t)FUN_00002534(0x657bd8, &DAT_005a3c80);
            FUN_00407300(r11.lo, r11.hi, r11.lo);
            FUN_001d9890(&local_70, &local_80, p7);
            FUN_004abdb8();
            FUN_004aa878();
            FUN_004ac9c0(&local_70);
            fn();
            goto exit_00471ac8;
        }
        FUN_00351aec(&local_48, l8, t7);
        FUN_001a9ac8();
        FUN_00351aec(&local_50, t7);
        FUN_004ac738();
        FUN_0019e924();
        t1 = local_28;
        if ((local_30 >> 0xe) < (r10 >> 0xe)) {
            CL4_SWBP(0x471ae8); /* SoftwareBreakpoint(1,0x471ae8) */
        }
        uStack_78 = local_30;
        local_80 = r10;
        fn2(&local_70, &local_80, p7, t3);
        FUN_004aa878();
        FUN_004abdb8(&local_70);
        FUN_004ac9c0();
        fn();
        (*param_5)(e_x9 - e_x8b, &local_48);   /* (*param_5)(extraout_x9_00 - extraout_x8_00, &local_48) */
        r10 = local_38;
        if (x21 != 0) {
            FUN_003509c8(p7);
            (**(code **)(e_x16b + 8))(e_x8, p7);
            uStack_68 = uStack_40;
            local_70 = local_48;
            FUN_000f5e5c(&local_70);
            local_80 = local_38;
            FUN_004aa938();
            FUN_004a4b14(&local_80);
            FUN_0036b118(t7);
            goto exit_00471ac8;
        }
        uStack_18 = uStack_40;
        local_20 = local_48;
        FUN_000f5e5c(&local_20);
        param_10 = r10;
        FUN_004aa938(&param_10);
        FUN_004a4b14();
        t2 = (word_t)FUN_00027754(s78);
        FUN_004ac9c0(e_x9 - e_x8b, s60, t2);
        fn();
        l8 = local_50;
        r10 = t1;
    } while (1);
exit_00471ac8: {
        FUN_00353d14(x30);
        return;
    }
}

/* FUN_00471aec @ 0x00471aec   (est. sk_bcg_00471aec)
 * Ghidra: void sk_bcg_00471aec(undefined8 p1,undefined8 p2,undefined8 p3)
 * Regex ByteCodeGen record dumper: initializes a collection (thunk_FUN_0006f6b4),
 * opens two list iterators (FUN_00469c50), and drains the first list by
 * re-adding each element (FUN_001a1854) while lVar-local_20 is nonzero, then
 * closes both iterators. Used by the emit driver FUN_00471644.
 * Confidence: medium   Notes: large local buffers auStack_260/auStack_e8 */
static void sk_bcg_00471aec(word_t p1, word_t p2, word_t p3)
{
    word_t t1, t2;              /* uVar1/uVar2 */
    word_t e_x16, e_x16b;       /* extraout_x16 / x16_00 */
    word_t x30 = 0;             /* unaff_x30 */
    word_t local_288;           /* local_288 */
    long l280;                  /* lStack_280 */
    word_t local_278, uStack_270, local_268;   /* 3-word staging */
    word_t local_28, local_18, uStack_10, local_8;  /* record locals */
    long local_20;              /* local_20 */
    word_t local_f0;            /* local_f0 = thunk result */
    unsigned char auStack_e8[192];   /* auStack_e8 buffer */
    unsigned char auStack_260[368];  /* auStack_260 buffer */

    FUN_0008e518();
    FUN_004abd04();
    FUN_004974ac(0, p3);
    local_f0 = (word_t)thunk_FUN_0006f6b4();
    FUN_000a6e14(auStack_e8);
    FUN_00351e3c();
    sk_bcg_0046e7a8();
    FUN_0035050c();
    t1 = (word_t)FUN_00498c54();
    FUN_00469dc4(auStack_260);
    FUN_003509c8(t1);
    (**(code **)(e_x16 + 8))(auStack_e8, t1);
    FUN_0035050c();
    t1 = (word_t)FUN_00498c6c();
    while (1) {
        FUN_00469c50(&local_28, t1);
        if (local_20 == 0) break;
        uStack_270 = uStack_10;
        local_278 = local_18;
        local_268 = local_8;
        local_288 = local_28;
        l280 = local_20;
        FUN_003504e8();
        t2 = (word_t)FUN_00310d34();
        FUN_001a1854(&local_288, t2);
    }
    FUN_003509c8(t1);
    (**(code **)(e_x16b + 8))(auStack_260, t1);
    FUN_0008e500(local_f0, x30);
    return;
}

/* FUN_00471c14 @ 0x00471c14   (est. sk_bcg_00471c14)
 * Ghidra: void sk_bcg_00471c14(p1..p12)
 * Regex ByteCodeGen range-check wrapper: resolves two bound values
 * (FUN_00027754), computes them via FUN_00310924 into local_58/local_60, and
 * dispatches to the emit driver FUN_00471644 when low<=high
 * (local_58>>0xe <= local_60>>0xe); otherwise fail-closed trap at 0x471cfc.
 * Confidence: medium */
static void sk_bcg_00471c14(word_t p1, word_t p2, word_t p3, word_t p4,
                            word_t p5, word_t p6, word_t p7, word_t p8,
                            word_t p9, word_t p10, word_t p11, word_t p12)
{
    code fn, fn2;               /* extraout_x9 / x9_00 */
    word_t t2;                  /* uVar2 */
    word_t local_60, local_58;   /* bounds */

    t2 = (word_t)FUN_00027754(p10);
    FUN_000277b8();
    FUN_003511a8(&local_58);
    fn();                       /* (*extraout_x9)() */
    FUN_00310924(t2);
    FUN_003511a8(&local_60);
    fn2();                      /* (*extraout_x9_00)() */
    if ((local_58 >> 0xe) <= (local_60 >> 0xe)) {
        sk_bcg_00471644(p1, p2, local_58, local_60, (code)p3, p4, p5, p6, p7, p8); /* 1 register-residue arg dropped */ /* 4 register-residue args dropped */
        return;
    }
    CL4_SWBP(0x471cfc);         /* SoftwareBreakpoint(1,0x471cfc) */
}

/* FUN_00471cfc @ 0x00471cfc   (est. sk_bcg_00471cfc)
 * Ghidra: void sk_bcg_00471cfc(void)
 * Regex ByteCodeGen range-check entry: after a masked-trampoline fixup round
 * resolves two bounds (FUN_00027754/FUN_000277b8/FUN_00310924) and, when
 * low<=high, builds via FUN_000e72b0 then dispatches to FUN_00471644; on an
 * empty/zero continuation it runs a cleanup pair. Trap at 0x471e78 otherwise.
 * Confidence: medium   Notes: masked trampoline SUB_...041f; in-stack arg */
static void sk_bcg_00471cfc(void)
{
    word_t t1;                  /* uVar1 */
    code fn, fn2;               /* pcVar2 / extraout_x9 */
    word_t in_x4 = 0;           /* in_x4 */
    word_t e_x8, e_x16;         /* extraout_x8 / x16 */
    code x9fn;                  /* extraout_x9 */
    word_t x21 = 0;             /* unaff_x21 */
    word_t s0 = 0;              /* in_stack_00000000 */
    word_t local_60, local_58;

    FUN_0007c028();
    ((code)&SUB_54ffff60f100041f)(*(word_t *)(e_x8 + 0x40));  /* masked; *(extraout_x8+0x40) */
    FUN_000aa4ec();
    FUN_004aba28();
    t1 = (word_t)FUN_00027754(s0);
    fn = (code)FUN_000277b8();
    fn(&local_58, in_x4, t1);
    fn2 = (code)FUN_00310924(t1);
    fn2(&local_60, in_x4, t1);
    if ((local_58 >> 0xe) <= (local_60 >> 0xe)) {
        FUN_000e72b0();
        sk_bcg_00471644(0,0,0,0,0,0,0,0,0,0); /* register-residue args */
        if (x21 == 0) {
            FUN_0007c1c4();
            ((code)x9fn)();             /* (*extraout_x9)() */
            (**(code **)(e_x16 + 0x20))();
        }
        return;
    }
    CL4_SWBP(0x471e78);         /* SoftwareBreakpoint(1,0x471e78) */
}

/* FUN_00471e78 @ 0x00471e78   (est. sk_bcg_00471e78)
 * Ghidra: void sk_bcg_00471e78(void)
 * Regex ByteCodeGen finalize/teardown: resets a builder (FUN_00351488),
 * locates a node field (FUN_0049fcf8, +0x24), resolves a method
 * (FUN_004aa47c) and calls the resolved vtable slot (extraout_x16_00+0x20)
 * with an adjusted offset. Indirect jump not fully recovered.
 * Confidence: medium   Notes: indirect jump treated as call */
static void sk_bcg_00471e78(void)
{
    int i1;                     /* iVar1 */
    long l2;                    /* lVar2 */
    wpair_t r3;                 /* auVar3[16] */
    word_t e_x8;                /* extraout_x8 */
    word_t e_x16, e_x16b;       /* extraout_x16 / x16_00 */

    FUN_00077888();
    FUN_003509ec();
    FUN_00351488(0);
    FUN_0049fd10();
    FUN_00349530();
    (**(code **)(e_x16 + 0x20))(e_x8);
    FUN_00350624(0);
    l2 = (long)FUN_0049fcf8();
    i1 = *(int *)(l2 + 0x24);
    FUN_004aa47c();
    FUN_00350968();
    r3 = (wpair_t)FUN_00377824();
    FUN_00350404(r3.lo, r3.hi, r3.lo);
    /* indirect jump (too many branches) treated as a call */
    (**(code **)(e_x16b + 0x20))(e_x8 + i1);
    return;
}

/* FUN_00471f20 @ 0x00471f20   (est. sk_bcg_00471f20)
 * Ghidra: void sk_bcg_00471f20(void)
 * Regex ByteCodeGen finalizer wrapper: resolves a node (FUN_00027754), runs a
 * masked-trampoline fixup round, then resolves a vtable method
 * (FUN_00310e08) and calls it (extraout_x16+0x10) with a string label
 * (DAT_0061628c) and offset, followed by the teardown FUN_00471e78.
 * Confidence: medium   Notes: masked trampoline SUB_...041f; DAT_0061628c */
static void sk_bcg_00471f20(void)
{
    wpair_t r5;                 /* auVar5[16] */
    word_t t1, t2;              /* uVar1/uVar2 */
    long l3;                    /* lVar3 */
    word_t in_x3 = 0;           /* in_x3 */
    word_t e_x8;                /* extraout_x8 */
    word_t e_x16;               /* extraout_x16 */
    code fn;                    /* pcVar4 */

    r5 = (wpair_t)FUN_0008e518();
    t1 = (word_t)FUN_00027754(in_x3);
    FUN_004aad84();
    FUN_000bd3a4();
    FUN_00377824();
    FUN_004ab310();
    FUN_00077894(t1);
    FUN_00377bec();
    FUN_00077894(0);
    t1 = FUN_00377824().lo;
    FUN_000a6f88();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();      /* masked trampoline fn */
    FUN_0034b0c4();
    FUN_003511d8(0);
    FUN_0049fd10();
    FUN_0007c1a4();
    ((code)&SUB_54ffff60f100041f)();      /* masked trampoline fn */
    FUN_0034b0d4();
    fn = *(code **)(e_x16 + 0x10);        /* pcVar4 */
    fn();
    FUN_004abd90();
    FUN_000839d8();
    FUN_00464f4c();
    FUN_00100efc();
    FUN_00353960();
    FUN_00377bec();
    t2 = (word_t)FUN_00350c98();
    l3 = (long)FUN_00310e08(t2, t1);
    fn(&DAT_0061628c, r5.hi + *(int *)(l3 + 0x24), t1);  /* (DAT_0061628c, auVar5_8 + off, uVar1) */
    FUN_00350530();
    FUN_00377dcc();
    sk_bcg_00471e78(); /* register-residue arg dropped */
    FUN_0008e500(r5.lo);
    return;
}

/* ==================== SKR27 function bodies ==================== */


/* ------------------------------------------------------------------ *
 * Part 4 externs: callees owned by other SKR27 parts / slices that are
 * not declared in the shared header above. Signatures reflect the
 * register use observed at the call sites (all default to word_t).
 * ------------------------------------------------------------------ */

/* Thunk variants referenced by name in the decompiles (jump-stubs to the
 * corresponding FUN_ targets declared in the shared header). */
extern word_t thunk_FUN_0001612c();
extern word_t thunk_FUN_002acbb8();
extern word_t thunk_FUN_0036b270();
extern word_t thunk_FUN_0044f818();

/* Forward declarations: defined later in this file (address order). */
static void sk_bcg_00475bf4(void);
static void sk_bcg_00475c7c(void);
static void sk_bcg_00475cf8(void);
/* FUN_004720b8 @ 0x004720b8   (est. sk_bcg_004720b8)
 * Ghidra: void sk_bcg_004720b8(undefined8 param_1, undefined8 param_2, undefined8 param_3, undefined8 param_4)
 * Regex-ByteCodeGen emission driver: builds a bytecode node for a regex AST
 * atom, threading a size delta and two "builder" pointers (in x16-based
 * closure slots) through a long chain of Swift runtime / trampoline helper
 * calls. Branch on a carry/zero flag from a buffer-growth check decides
 * whether to append a new instruction or re-emit through a second builder.
 * Confidence: medium   Notes: many SUB_54ffff60f100041f masked trampoline
 * calls and extraout_* / zflag register artifacts. */
static void sk_bcg_004720b8(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    wpair_t av18;    /* 16-byte pair */
    wpair_t av19;    /* 16-byte pair */
    long ln13, ln6, ln7, ln11, ln14, ln15;
    word_t v2, v3, v4, v5, v8, v9, v10;
    unsigned long v12;
    int iv1;
    word_t loc_c8, loc_c0, loc_78;
    bool zflag;         /* zero flag set by preceding call (register artifact) */
    /* extraout_* register artifacts (Ghidra names kept in comments) */
    word_t x8_0, x8_00, x8_01, x8_02, x8_03, x8_04, x8_05, x8_06, x8_07, x8_08, x8_09, x8_10;
    word_t x9_0, x9_1, x9_2, x9_3, x9_4, x9_5;
    word_t x12_0, x12_1;
    word_t x16_0, x16_1, x16_2, x16_3;
    word_t ux27, ux30;
    code *pc16;
    code *pc17;
    /* masked self-modifying/trampoline fn: SUB_54ffff60f100041f */
    code *tramp = (code *)(uintptr_t)0x54ffff60f100041f;

    av18 = FUN_0008e518();
    ln13 = av18.hi;                     /* av18._8_8_ */
    v2 = FUN_00027754(param_4);
    FUN_004aad84();
    FUN_00350878();
    v3 = FUN_00377824().lo;
    FUN_004ab310();
    FUN_00351bd4(v2);
    v2 = FUN_00377bec().lo;
    FUN_00407ed0();
    FUN_00351214();
    v4 = FUN_00377824().lo;
    v5 = FUN_0034b0b4();
    ln6 = FUN_003722e4(v5, v4, v4);
    FUN_000a6f88();
    (*tramp)(*(word_t *)(x8_00 + 0x40));     /* masked self-modifying/trampoline fn */
    FUN_003493c4();
    FUN_003503f8();
    (*tramp)();                              /* masked self-modifying/trampoline fn */
    FUN_00350464();
    FUN_004ac2b8();
    FUN_00464f4c();
    FUN_00350738();
    FUN_003522c8();
    v5 = FUN_00377bec().lo;
    ln7 = FUN_00310e08(0xff, v4, v5);
    FUN_00350798();
    FUN_00310d68();
    v8 = FUN_000a6f88();
    FUN_0007c1a4();
    (*tramp)();                              /* masked self-modifying/trampoline fn */
    FUN_00350428();
    ln14 = *(long *)(ln7 + -8);
    (*tramp)(*(word_t *)(ln14 + 0x40));    /* masked self-modifying/trampoline fn */
    FUN_003493c4();
    FUN_003503f8();
    (*tramp)();                              /* masked self-modifying/trampoline fn */
    FUN_0034ba68();
    av19 = FUN_003508e4();
    v9 = FUN_0049fd10(av19.lo, av19.hi, v2);
    FUN_000a6f88();
    (*tramp)(*(word_t *)(x8_02 + 0x40));     /* masked self-modifying/trampoline fn */
    FUN_003493c4();
    FUN_003503f8();
    (*tramp)();                              /* masked self-modifying/trampoline fn */
    ln15 = x8_01 - x12_0;                  /* extraout_x8_01 - exx12 */
    FUN_0007c028();
    (*tramp)(*(word_t *)(x8_03 + 0x40));     /* masked self-modifying/trampoline fn */
    FUN_003493c4();
    FUN_003503f8();
    (*tramp)();                              /* masked self-modifying/trampoline fn */
    (**(code **)(x16_1 + 0x10))(ln15, ln13, v9);   /* extraout_x16_01 */
    FUN_00350884(ln15, 1, v4);          /* sets Z flag -> zflag */
    if (zflag) {
        FUN_00350af4(*(word_t *)(x16_1 + 8));
        (*((code *)x8_04))();                /* extraout_x8_04 */
        v2 = 1;
    } else {
        FUN_004ab9b0();
        pc16 = *(code **)(x16_2 + 0x20);
        av19 = FUN_000b43d0();
        (*pc16)(av19.lo, av19.hi, v4);
        v10 = FUN_004ac85c(0);
        ln11 = FUN_0049fcf8(v10, v3, v2);
        iv1 = *(int *)(ln11 + 0x24);
        FUN_0035166c(v5);
        FUN_003516b4(ln15 - x12_1, ln13 + iv1);   /* extraout_x12_00 */
        v12 = (*((code *)x8_05))();       /* extraout_x8_05 */
        if ((v12 & 1) == 0) {
            /* WARNING: Does not return */
            CL4_SWBP(0x47277c);
        }
        FUN_003513a8(loc_78);
        (*((code *)x8_06))();                /* extraout_x8_06 */
        (**(code **)(x16_2 + 0x10))(loc_78 + *(int *)(ln6 + 0x30), ln13 + iv1, v4);
        av19 = FUN_00351324();
        (*((code *)x9_3))(av19.lo, av19.hi, ln6);   /* extraout_x9_03 */
        iv1 = *(int *)(ln6 + 0x30);
        av19 = FUN_0035060c();
        (*((code *)x8_06))(av19.lo, av19.hi, v4);
        pc17 = *(code **)(x16_2 + 8);
        (*pc17)(x9_0 + iv1, v4);     /* exx9 + iv1 */
        av19 = FUN_00351324(*(word_t *)(x16_0 + 0x20));  /* exx16 */
        (*((code *)x8_06))(av19.lo, av19.hi, ln6);
        (*((code *)x8_06))(x9_1 + *(int *)(ln7 + 0x24), x9_0 + *(int *)(ln6 + 0x30), v4);
        FUN_00084174();
        (*pc17)();
        pc16 = (code *)FUN_004a2fa8(param_4);
        (*pc16)(x8_01, av18.lo, x9_1, param_3, param_4);
        FUN_003510dc();
        (*((code *)x9_4))();                 /* extraout_x9_04 */
        av18 = FUN_00352290();
        FUN_00350884(av18.lo, av18.hi, ln7);   /* sets Z flag -> zflag */
        if (zflag) {
            (**(code **)(x16_0 + 8))(x8_01, v8);     /* extraout_x16_00 */
            v2 = 1;
        } else {
            pc16 = *(code **)(ln14 + 0x20);
            (*pc16)(ux27, x8_01, ln7);
            v12 = FUN_001e3048(ln7);
            if ((v12 & 1) == 0) {
                word_t stack_slot40;
                FUN_00350bc0(&stack_slot40);  /* &stack0x00000040 */
                FUN_004ac640();
                (*((code *)x8_09))();        /* extraout_x8_09 */
                FUN_000ec044(ln6, ux27 + *(int *)(ln7 + 0x24), v4);
                (*((code *)x8_10))();        /* extraout_x8_10 */
                FUN_004abd90(ln6, 0);
                FUN_000839d8();
            } else {
                iv1 = *(int *)(ln7 + 0x24);
                FUN_00351750(v2);
                (*((code *)x9_5))(x9_2, loc_c8, v2);  /* extraout_x9_05 */
                FUN_00349fe0(v5);
                FUN_003516b4(ux27 + iv1, x9_2);
                v12 = (*((code *)x8_07))();  /* extraout_x8_07 */
                FUN_00350518();
                (*pc17)();
                if ((v12 & 1) == 0) {
                    pc17 = (code *)FUN_00319658(v2);
                    (*pc17)(x9_1, ux27 + iv1, loc_c8, v2);
                    FUN_0034ba48();
                    FUN_000839d8();
                    (**(code **)(loc_c0 + 0x28))(ln13, x9_1, v9);
                } else {
                    word_t stack_slot40;
                    FUN_00350bc0(&stack_slot40);  /* &stack0x00000040 */
                    FUN_004ac640();
                    (*((code *)x8_08))();        /* extraout_x8_08 */
                    FUN_004abd90(v2, 1);
                    FUN_000839d8();
                }
            }
            (*pc16)(x8_0, ux27, ln7);  /* exx8 */
            v2 = 0;
        }
    }
    FUN_000839d8(x8_0, v2, 1, ln7);    /* exx8 */
    FUN_0008e500(ux30);
}

/* FUN_0047277c @ 0x0047277c   (est. sk_bcg_0047277c)
 * Ghidra: void sk_bcg_0047277c(void)
 * ByteCodeGen buffer-grow loop: builds a capacity-checked element buffer
 * (used to accumulate regex instruction indices), repeatedly growing it
 * while appending elements, guarding every arithmetic/bounds check with a
 * fail-closed trap. The single element appended on the first pass is
 * pre-scanned here. Calls a Swift "Array" reserve/append sequence.
 * Confidence: medium   Notes: heavy bounds/trap checks (SCARRY8/SBORROW8);
 * DAT_004baeb0 pair loaded into the new buffer header. */
static void sk_bcg_0047277c(void)
{
    unsigned long v1;
    code *pc2;
    long ln3;
    word_t v4, v5;
    unsigned long v6, v7, v8;
    word_t ux30;
    wpair_t av9;
    unsigned long istk_00000010;   /* stack arg */
    unsigned long istk_00000018;   /* stack arg */
    long lStack;                       /* lstk0000000000000038 */

    FUN_0035300c();
    FUN_00349a18();
    FUN_00002534((word_t)"\x00" + 8, &DAT_004c0740);   /* str_cstring_0064c108 + 8 */
    FUN_00359018();
    lStack = FUN_0036a940();
    v4 = _DAT_004baeb0;
    *(word_t *)(lStack + 0x18) = uRam00000000004baeb8;  /* DAT_004baeb8 */
    *(word_t *)(lStack + 0x10) = v4;                 /* DAT_004baeb0 */
    FUN_00350524();
    ln3 = thunk_FUN_0001612c();
    *(long *)(lStack + 0x20) = ln3;
    if (1 < ln3) {
        lStack = FUN_0001dd14(1, ln3, 0, lStack);
    }
    FUN_003504e8();
    v4 = FUN_00310d34();
    v5 = FUN_00376820(&DAT_004e8214, v4);
    FUN_0019fa60(&istk_00000010, v4, v5, 0x6720e8);   /* &stack0x00000010 */
    v1 = istk_00000018;
    if (SBORROW8(istk_00000018, istk_00000010)) {
        /* WARNING: Does not return */
        CL4_SWBP(0x472968);
    }
    if (istk_00000018 != istk_00000010) {
        v7 = istk_00000010 + 1;
        if (SCARRY8(istk_00000010, 1)) {
            /* WARNING: Does not return */
            CL4_SWBP(0x47296c);
        }
        if ((long)v7 < (long)istk_00000010 || (long)istk_00000018 < (long)v7) {
            /* WARNING: Does not return */
            CL4_SWBP(0x472970);
        }
        if (v7 != istk_00000018) {
            if ((long)istk_00000018 <= (long)v7) {
                /* WARNING: Does not return */
                CL4_SWBP(0x472974);
            }
            do {
                if ((long)v7 < 0) {
                    if (SBORROW8(0, v7)) {
                        /* WARNING: Does not return */
                        CL4_SWBP(0x472958);
                    }
                    if ((long)v7 < 0) {
                        /* WARNING: Does not return */
                        CL4_SWBP(0x472960);
                    }
                    v8 = *(unsigned long *)(lStack + 0x10);
                    if (v8 <= v7) {
                        /* WARNING: Does not return */
                        CL4_SWBP(0x472964);
                    }
                    ln3 = *(long *)(lStack + v7 * 8 + 0x20);
                    if ((long)-v7 <= ln3) {
                        av9 = FUN_004ac180();
                        goto LAB_00472920;
                    }
                    v6 = FUN_003a261c(lStack);
                    if ((v6 & 1) == 0) {
                        FUN_000dbbe0(v6, v8 + 1);
                        lStack = FUN_0001dd14();
                    }
                    v8 = *(unsigned long *)(lStack + 0x10);
                    if (*(unsigned long *)(lStack + 0x18) >> 1 <= v8) {
                        FUN_004aa720();
                        lStack = FUN_0001dd14();
                    }
                    *(unsigned long *)(lStack + 0x10) = v8 + 1;
                    *(long *)(lStack + v8 * 8 + 0x20) = ln3;
                } else {
                    v8 = FUN_004ac180().lo;
                    av9.hi = 0;
                    av9.lo = v8;
LAB_00472920:
                    FUN_00351e3c(av9.lo, av9.hi);
                    sk_bcg_00472f44();
                }
                v7 = v7 + 1;
            } while (v1 != v7);
        }
    }
    FUN_00353238(lStack, ux30);
}

/* FUN_00472974 @ 0x00472974   (est. sk_bcg_00472974)
 * Ghidra: void sk_bcg_00472974(undefined8 param_1, undefined8 param_2, long param_3, undefined8 param_4, code *param_5)
 * ByteCodeGen element-scan loop with two builder closures: iterates the
 * range [param_3 .. thunk_FUN_0001612c(param_4,v4)) appending bytecode
 * instructions via a masked trampoline, and on completion either emits a
 * final node through an x12-based closure or reports a special "was
 * captured" marker. Every iteration guarded by carry/bounds traps.
 * Confidence: medium   Notes: SUB_54ffff60f100041f masked trampoline;
 * many extraout_* artifacts. */
static void sk_bcg_00472974(word_t param_1, word_t param_2, long param_3, word_t param_4, code *param_5)
{
    int iv1;
    word_t v2, v3, v4, v7;
    long ln5, ln6;
    unsigned long v8;
    wpair_t (*pc9)();   /* returns 16-byte pair (auVar11) */
    code *pc10;
    /* extraout_* register artifacts */
    long x8_0, x8_1, x8_2;
    word_t x8_3;
    code *x8_4, *x8_5, *x8_6, *x8_7;
    word_t x9_0, x9_1, x9_2;
    code *x9_3, *x9_4;
    long x12_0;
    long x16_0, x16_1;
    wpair_t av11;
    word_t istk_00000060, istk_00000068, istk_00000080, istk_00000088;
    word_t *istk_00000070;
    long *istk_00000078;
    long loc_d8;
    word_t astk_28[5];   /* astk_28 [40] */

    v2 = FUN_0008e518().lo;
    FUN_004633e0();
    v3 = FUN_00377824(0xff, istk_00000088, istk_00000080).lo;
    v4 = FUN_0034b0b4();
    ln5 = FUN_003722e4(v4, v3, v3);
    FUN_000a6f88();
    (*((code *)(uintptr_t)0x54ffff60f100041f))(*(word_t *)(x8_1 + 0x40));  /* masked trampoline */
    FUN_003493c4();
    FUN_003503f8();
    (*((code *)(uintptr_t)0x54ffff60f100041f))();   /* masked trampoline */
    FUN_00350464();
    FUN_003509a4();
    FUN_00027754(istk_00000088);
    av11 = FUN_004aa5dc();
    v4 = FUN_00377824(av11.lo, av11.hi, istk_00000080).lo;
    FUN_000a6f88();
    (*((code *)(uintptr_t)0x54ffff60f100041f))(*(word_t *)(x8_2 + 0x40));  /* masked trampoline */
    FUN_003493c4();
    FUN_003503f8();
    (*((code *)(uintptr_t)0x54ffff60f100041f))();   /* masked trampoline */
    FUN_00350464();
    FUN_0007c028();
    FUN_0007c1a4();
    (*((code *)(uintptr_t)0x54ffff60f100041f))();   /* masked trampoline */
    FUN_0034cff4();
    av11 = FUN_00084180();
    (*x9_4)(av11.lo, av11.hi, v3);         /* extraout_x9_02 */
    for (; ln6 = thunk_FUN_0001612c(param_4, v4), param_3 != ln6; param_3 = param_3 + 1) {
        av11 = FUN_00350914();
        FUN_0046490c(av11.lo, av11.hi, v3);
        FUN_00464f4c();
        v7 = FUN_00377bec().lo;
        av11 = FUN_00350500();
        FUN_00310e08(av11.lo, av11.hi, v7);
        FUN_00349fe0(v7);
        FUN_003516b4();
        v8 = (*x8_5)();                          /* extraout_x8_03 */
        if ((v8 & 1) != 0) break;
        FUN_0019ea20(x8_3, param_3, param_4, v4);   /* extraout_x8_02 */
        pc9 = (wpair_t (*)())FUN_000277e8(istk_00000088);
        av11 = (*pc9)(astk_28);
        (**(code **)(x16_1 + 0x10))(x9_1, av11.hi, v4);   /* extraout_x16_00, extraout_x9_01 */
        ((code)av11.lo)(astk_28, astk_28, 0);   /* indirect call via av11._0_8_ */
        FUN_0009e234();
        v8 = (*param_5)();
        pc9 = *(code **)(x16_1 + 8);
        FUN_00350618();
        (*pc9)();
        (*pc9)(x8_3, v4);                     /* extraout_x8_02 */
        if ((v8 & 1) == 0) break;
        if (SCARRY8(param_3, 1)) {
            /* WARNING: Does not return */
            CL4_SWBP(0x472ee8);
        }
        v7 = FUN_00027818(istk_00000088);
        FUN_00352840(v7);
        (*x8_6)();                                  /* extraout_x8_04 */
    }
    ln6 = thunk_FUN_0001612c(param_4, v4);
    if (ln6 == param_3) {
        FUN_0046490c();
        FUN_00464f4c();
        av11 = FUN_00350914();
        v2 = FUN_00377bec(av11.lo, av11.hi, v3).lo;
        FUN_0035166c();
        FUN_000b4390();
        FUN_0035053c();
        v8 = (*x8_7)();                          /* extraout_x8_05 */
        if ((v8 & 1) == 0) {
            /* WARNING: Does not return */
            CL4_SWBP(0x472eec);
        }
        av11 = FUN_003507e0();
        (*x9_4)(av11.lo, av11.hi, v3);     /* extraout_x9_02 */
        pc9 = *(code **)(x12_0 + 0x20);
        (*pc9)(loc_d8 + *(int *)(ln5 + 0x30));
        av11 = FUN_003508cc();
        (*x9_3)(av11.lo, av11.hi, ln5);     /* extraout_x9_03 */
        iv1 = *(int *)(ln5 + 0x30);
        FUN_00352c4c(x8_0);                         /* exx8 */
        (*pc9)();
        pc10 = *(code **)(x12_0 + 8);
        (*pc10)(x9_0 + iv1, v3);            /* extraout_x9_00 */
        av11 = FUN_003508cc(*(word_t *)(x16_0 + 0x20));  /* exx16 */
        (*x8_4)(av11.lo, av11.hi, ln5);     /* extraout_x8_06 */
        iv1 = *(int *)(ln5 + 0x30);
        av11 = FUN_003508e4();
        ln5 = FUN_00310e08(av11.lo, av11.hi, v2);
        (*pc9)(x8_0 + *(int *)(ln5 + 0x24), x9_0 + iv1, v3);
        FUN_00350914();
        (*pc10)();
        av11 = FUN_00350774(x8_0, 0);
    } else {
        (**(code **)(x12_0 + 0x18))(istk_00000060, v2, v3);
        FUN_00350548(*(word_t *)(x12_0 + 0x28), istk_00000068);
        (*x8_4)();                                  /* extraout_x8_07 */
        *istk_00000070 = 0;
        *istk_00000078 = param_3;
        FUN_0046490c();
        FUN_00464f4c();
        av11 = FUN_00350914();
        FUN_00377bec(av11.lo, av11.hi, v3);
        v2 = FUN_00350c98();
        FUN_00310e08(v2, v3);
        av11.hi = 1;
        av11.lo = x8_0;
    }
    FUN_000839d8(av11.lo, av11.hi);
    FUN_0008e500(x9_0);
}

/* FUN_00472f00 @ 0x00472f00   (est. sk_bcg_00472f00)
 * Ghidra: void sk_bcg_00472f00(void)
 * Thin trampoline: forwards directly to sk_bcg_00471f20(the shared
 * ByteCodeGen entry/teardown helper owned by another part).
 * Confidence: high (trivial thunk) */
static void sk_bcg_00472f00(void)
{
    sk_bcg_00471f20();
}

/* FUN_00472f04 @ 0x00472f04   (est. sk_bcg_00472f04)
 * Ghidra: void sk_bcg_00472f04(void)
 * Thin trampoline: forwards directly to sk_bcg_00471f20(shared helper).
 * Confidence: high (trivial thunk) */
static void sk_bcg_00472f04(void)
{
    sk_bcg_00471f20();
}

/* FUN_00472f44 @ 0x00472f44   (est. sk_bcg_00472f44)
 * Ghidra: void sk_bcg_00472f44(void)
 * ByteCodeGen range-collector: reads two builder/capacity values and an
 * index from caller-injected registers (ix5/ix6/ix7), then loops
 * appending per-element "range" records into a growing buffer, calling an
 * indirect element builder for each and finally writing the collected
 * count and bound back through the ix5/ix6/ix7 output slots.
 * Confidence: medium   Notes: in_* register inputs; SUB_54ffff60f100041f
 * masked trampoline; extraout_* artifacts. */
static void sk_bcg_00472f44(void)
{
    long ln1, ln3, ln5;
    long *pl2;
    long exx1;            /* exx1 */
    code *ix3;                 /* register input */
    long *ix5, *ix6, *ix7; /* register inputs */
    word_t exx8;
    long x8_0;                   /* extraout_x8_00 */
    long x12_0;                  /* exx12 */
    long x16_0;                  /* exx16 */
    unsigned long ux22;
    code *pc4;
    wpair_t av6;
    long *loc_30, *loc_28, *loc_20;
    code *loc_18;
    long loc_10, loc_8;

    FUN_0008e518();
    loc_18 = ix3;
    FUN_0007c028();
    (*((code *)(uintptr_t)0x54ffff60f100041f))(*(word_t *)(x8_0 + 0x40));  /* masked trampoline */
    FUN_0034ab10();
    FUN_0034b540();
    av6.lo = sk_svc_call(); av6.hi = 0;   /* masked trampoline (SUB_54ffff60f100041f) */
    loc_8 = av6.lo;
    if (SCARRY8(loc_8, av6.hi)) {
        /* WARNING: Does not return */
        CL4_SWBP(0x4730e4);
    }
    loc_30 = ix5;
    loc_28 = ix6;
    loc_20 = ix7;
    FUN_00350a04();
    loc_10 = thunk_FUN_0001612c();
    for (ln5 = exx1; ln1 = loc_8 + ln5, ln1 < loc_10; ln5 = ln5 + 1) {
        FUN_00352840((long)&loc_30 - x12_0, ln5);   /* &loc_30 - exx12 */
        FUN_0019ea20();
        FUN_00352840(ln1);
        FUN_0019ea20();
        FUN_00351324();
        ux22 = (*loc_18)();
        pc4 = *(code **)(x16_0 + 8);                 /* exx16 */
        FUN_003509b0();
        (*pc4)();
        FUN_003510ac();
        (*pc4)();
        if ((ux22 & 1) == 0) break;
        if (SCARRY8(ln5, 1)) {
            /* WARNING: Does not return */
            CL4_SWBP(0x4730e0);
        }
    }
    pl2 = loc_30;
    FUN_00498b28(FUN_0001dd14);
    FUN_004ac7e0();
    FUN_003510b8();
    FUN_00498c1c();
    ln3 = *pl2;
    *(unsigned long *)(ln3 + 0x10) = ux22 + 1;
    *(long *)(ln3 + ux22 * 8 + 0x20) = ln5;
    *loc_28 = loc_8;
    *loc_20 = ln1;
    FUN_0008e500(exx8);
}

/* FUN_004730e4 @ 0x004730e4   (est. sk_bcg_004730e4)
 * Ghidra: undefined1[16] sk_bcg_004730e4(undefined8 param_1, undefined8 param_2, long param_3)
 * Returns a 16-byte pair built from the bytecode-buffer element count at
 * param_3+0x10 (in the low word) with the high word cleared and the pair
 * shifted left 0x40 (a Swift String/Substring-style tagged representation).
 * Confidence: high   Notes: returns wpair_t; "av1 << 0x40". */
static wpair_t sk_bcg_004730e4(word_t param_1, word_t param_2, long param_3)
{
    wpair_t av1;
    av1.hi = 0;
    av1.lo = *(unsigned long *)(param_3 + 0x10);
    return av1;   /* av1 << 0x40 */
}

/* FUN_004730f0 @ 0x004730f0   (est. sk_bcg_004730f0)
 * Ghidra: void sk_bcg_004730f0(long param_1, undefined8 param_2, ulong param_3, undefined8 param_4, code *param_5)
 * ByteCodeGen UTF-8/literal-size classifier: validates param_1 (non-negative),
 * resolves a code-unit width from param_3's tagged flags, and either emits a
 * size-class node via an indirect builder or traps. A capture-count check
 * (v2>>0xe vs count<<2) selects the success path.
 * Confidence: medium   Notes: tag-bit decode of param_3; indirect param_5 call;
 * exx8; trap 0x4731b4/0x4731b8. */
static void sk_bcg_004730f0(long param_1, word_t param_2, unsigned long param_3, word_t param_4, code *param_5)
{
    unsigned long v1, v2, v6;
    code *pc3;
    bool v4;
    word_t v5;
    code *exx8;   /* exx8 */
    uint v7;
    unsigned long ux21;

    if (param_1 < 0) {
        /* WARNING: Does not return */
        CL4_SWBP(0x4731b4);
    }
    v5 = FUN_00350b54(param_4);
    v1 = ux21 & 0xffffffffffff;
    if ((param_3 & 0x2000000000000000) != 0) {
        v1 = param_3 >> 0x38 & 0xf;
    }
    v7 = (uint)(ux21 >> 0x3b) & 1;
    if ((param_3 & 0x1000000000000000) == 0) {
        v7 = 1;
    }
    v4 = v7 == 0;
    FUN_00351b78(0xf, v5);
    (*exx8)();
    v6 = FUN_00351db4().lo;
    v2 = v1 << 0x10;
    if (!v4) {
        v2 = v6;
    }
    if (v2 >> 0xe <= v1 << 2) {
        FUN_00077894();
        v5 = (*param_5)();
        FUN_004abf6c();
        FUN_003a25d4();
        FUN_0034c444(v5);
        return;
    }
    /* WARNING: Does not return */
    CL4_SWBP(0x4731b8);
}

/* FUN_004731b8 @ 0x004731b8   (est. sk_bcg_004731b8)
 * Ghidra: undefined1[16] sk_bcg_004731b8(long param_1, long param_2)
 * Range-node builder: checks param_1 non-negative and a capacity lower
 * bound; returns a 16-byte pair {param_2, param_2+0x20} describing a
 * bytecode element region, else traps on the size check.
 * Confidence: high   Notes: returns wpair_t; zflag flag from FUN_0035053c. */
static wpair_t sk_bcg_004731b8(long param_1, long param_2)
{
    long ln1, ln3, ln4;
    code *pc2;
    bool zflag;   /* zero flag from preceding call */
    wpair_t av5;

    if (param_1 < 0) {
        /* WARNING: Does not return */
        CL4_SWBP(0x473218);
    }
    ln4 = *(long *)(param_2 + 0x10);
    FUN_0035053c(0, param_1);      /* sets Z flag -> zflag */
    FUN_001a9a84();
    ln3 = FUN_00351db4().lo;
    ln1 = ln4;
    if (!zflag) {
        ln1 = ln3;
    }
    if (ln1 <= ln4) {
        if (-1 < ln1) {
            av5.hi = param_2 + 0x20;
            av5.lo = param_2;
            return av5;
        }
        /* WARNING: Does not return */
        CL4_SWBP(0x473220);
    }
    /* WARNING: Does not return */
    CL4_SWBP(0x47321c);
}

/* FUN_00473244 @ 0x00473244   (est. sk_bcg_00473244)
 * Ghidra: void sk_bcg_00473244(undefined8 param_1, undefined8 param_2, ulong param_3, ulong param_4)
 * The ByteCodeGen node dispatcher: switches on a "node kind" tag (v23,
 * derived from an element value) and for each regex-construct kind emits
 * the corresponding Swift bytecode instructions into the builder buffer
 * behind ux20, growing arrays as needed. Kinds handled include
 * character classes/ranges (case 1), captures/backreferences, quantified
 * repetition (case 3), assertions, literals, and many error paths that
 * build fatal-message structs. Recurses on children (case 0xc/0xe/etc.)
 * and ends with a shared completion tail (FUN_00353d14).
 * Confidence: medium   Notes: enormous multi-case switch; heavy
 * DAT_/string-fatal paths; many extraout_* artifacts and traps 0x474xxx. */
static void sk_bcg_00473244(word_t param_1, word_t param_2, unsigned long param_3, unsigned long param_4)
{
    byte bv2;
    bool bv4;
    uint v23, v24;
    int iv6;
    word_t v2, v3, v4, v5, v7;
    word_t v8, v9, v16, v17, v18, v19;
    word_t v21, v25, v26, v27, v28, v29, v31;
    long ln13, ln14, ln15, ln20, ln30;
    word_t ux20, ux21, ux22, ux25;
    wpair_t av33, av34;
    code *pc3;
    byte *pb8;
    unsigned long *pv22, *pv32;
    word_t *pv11;
    word_t *x1_out0;    /* exx1    (undefined8* write target) */
    word_t *x1_out1;    /* extraout_x1_00 */
    word_t *x1_out2;    /* extraout_x1_01 */
    word_t *x1_out3;    /* extraout_x1_02 */
    word_t *x1_out4;    /* extraout_x1_03 */
    word_t *x1_out5;    /* extraout_x1_06 */
    word_t x1_0, x1_04, x1_05, x1_07, x1_08, x1_09, x1_10, x1_11, x1_12, x1_13;
    word_t x1_14, x1_15, x1_16, x1_17, x1_18, x1_19;
    /* exw8 / exw9 / exw10 / exx9 / exx10 /
     * exx16 / exx8 families (register artifacts) */
    uint w8_0, w8_1, w8_2, w8_3, w8_4, w8_5;
    uint w9_0, w9_1, w9_2, w9_3, w9_4;
    uint w10_0, w10_1, w10_2;
    uint w16_0;
    word_t x8_0, x8_1, x8_2, x8_3, x8_4, x8_5, x8_6, x8_7, x8_8, x8_9;
    word_t x8_10, x8_11, x8_12, x8_13, x8_14, x8_15, x8_16, x8_17, x8_18, x8_19;
    word_t x8_20, x8_21, x8_22;
    word_t x9_0, x9_1, x9_2, x9_3, x9_4, x9_5, x9_6, x9_7, x9_8, x9_9;
    word_t x9_10, x9_11, x9_12, x9_13, x9_14, x9_15, x9_16;
    word_t x10_0, x10_1;
    word_t x16_0, x16_1, x16_2, x16_3, x16_4, x16_5, x16_6, x16_7, x16_8, x16_9;
    word_t x16_10, x16_11, x16_12, x16_13, x16_14;
    word_t *pv1;
    word_t pv10, pv12;
    word_t loc_490, stk_488, stk_480, stk_478, loc_470;
    word_t loc_468, stk_460, loc_458, stk_450, loc_448;
    word_t loc_440, stk_438, stk_430, stk_428, loc_420;
    word_t loc_418, stk_410, loc_408, stk_400, loc_3f8;
    word_t loc_3f0, stk_3e8, stk_3e0, stk_3d8, loc_3d0;
    word_t loc_3c8, stk_3c0, loc_3b8, stk_3b0, loc_3a8;
    long lStack_3a0, loc_398, lStack_390, loc_388, lStack_380;
    byte loc_378;
    word_t loc_370, stk_368, stk_360, stk_358, loc_350;
    word_t stk_348, stk_340, stk_338;
    word_t loc_1d0, stk_1c8, loc_1c0, stk_1b8, loc_1b0;
    word_t loc_120, stk_118, loc_110, stk_108, loc_100;
    long loc_f8, loc_f0, loc_e8;
    word_t loc_280[22];
    word_t loc_30[6];
    word_t astk_330[22];   /* astk_330 [176] */
    word_t astk_70[5];     /* astk_70 [40] */
    word_t loc_48, loc_40, loc_38;
    word_t astk_a0[5];     /* astk_a0 [40] */
    word_t loc_c8[5];       /* loc_c8 [40] */
    word_t loc_78, stk_70, loc_d8, stk_d0;

    FUN_00353cfc();
    v8 = FUN_004ac198();
    v23 = w16_0 & 0xfffffffe | (uint)v8 >> 2 & 1;
    v21 = 1;
    v28 = 0;
    v5 = v23 == 0x10;
    switch (v23) {
    default:
        v26 = *(unsigned long *)(v8 + 0x10);
        FUN_0036b270(v26);
        sk_bcg_00476fd0(0,0,0,0); /* register-residue args */
        goto LAB_0047419c;
    case 1:
        FUN_004ab4e8();
        v28 = FUN_004ab998();
        ln20 = FUN_0036b270(*(word_t *)((v28 & x8_2) + 0x10)).lo;   /* extraout_x8_02 */
        pv10 = (word_t)DAT_00657778;
        ln13 = 0x20;
        for (ln15 = *(long *)(ln20 + 0x10); ln15 != 0; ln15 = ln15 + -1) {
            v28 = *(unsigned long *)(ln20 + ln13);
            FUN_004ac15c();
            FUN_0036b270(v28 & ux22);
            ln30 = sk_bcg_0047c1b0(v28);
            FUN_004ab998();
            FUN_0036b118(v28 & ux22);
            v8 = *(unsigned long *)(ln30 + 0x10);
            v28 = *(unsigned long *)(pv10 + 0x10);
            ux22 = v28 + v8;
            if (SCARRY8(v28, v8)) {
                /* WARNING: Does not return */
                CL4_SWBP(0x474ef4);
            }
            v21 = FUN_003a261c(pv10);
            if ((int)v21 == 0) {
                if ((long)v28 <= (long)ux22) {
                    v28 = ux22;
                }
LAB_004737ec:
                pv10 = FUN_00498f0c(v21, v28, 1, pv10);
                FUN_004ac778();
                v26 = x8_3;              /* extraout_x8_03 */
            } else {
                v26 = *(unsigned long *)(pv10 + 0x18) >> 1;
                if ((long)v26 < (long)ux22) {
                    if (v28 <= ux22) {
                        v28 = ux22;
                    }
                    goto LAB_004737ec;
                }
            }
            v26 = v26 - *(long *)(pv10 + 0x10);
            if ((long)v26 < 0) {
                /* WARNING: Does not return */
                CL4_SWBP(0x474ef8);
            }
            if (*(long *)(ln30 + 0x10) == 0) {
                FUN_0036b118(ln30);
                if (v8 != 0) {
                    /* WARNING: Does not return */
                    CL4_SWBP(0x474efc);
                }
            } else {
                if (v26 < v8) {
                    /* WARNING: Does not return */
                    CL4_SWBP(0x474f04);
                }
                pv12 = pv10 + *(long *)(pv10 + 0x10) * 8 + 0x20;   /* element array start */
                pv1 = (word_t *)(ln30 + 0x20);
                if ((word_t *)pv1 < (word_t *)(uintptr_t)(pv12 + v8 * 8) &&
                    (word_t *)(uintptr_t)pv12 < (word_t *)((char *)pv1 + v8 * 8)) {
                    /* WARNING: Does not return */
                    CL4_SWBP(0x474f10);
                }
                FUN_0035b67c((word_t *)(uintptr_t)pv12, pv1, v8, 0x687408);
                FUN_0036b118(ln30);
                if (v8 != 0) {
                    if (SCARRY8(*(long *)(pv10 + 0x10), v8)) {
                        /* WARNING: Does not return */
                        CL4_SWBP(0x474f0c);
                    }
                    *(unsigned long *)(pv10 + 0x10) = *(long *)(pv10 + 0x10) + v8;
                }
            }
            ln13 = ln13 + 8;
        }
        loc_40 = 0;
        loc_38 = 0xe000000000000000;
        FUN_000a6f68();
        v27 = uRam00000000004baeb8;   /* DAT_004baeb8 */
        v21 = _DAT_004baeb0;          /* DAT_004baeb0 */
        v28 = *(unsigned long *)(pv10 + 0x10);
        loc_48 = x8_4;                 /* extraout_x8_04 */
        if (v28 != 0) {
            bv4 = false;
            v8 = 0;
            pv12 = (word_t)DAT_00657778;
            v26 = v28 - 1;
            do {
                if (v28 <= v8) {
                    /* WARNING: Does not return */
                    CL4_SWBP(0x474f00);
                }
                v28 = *(unsigned long *)(pv10 + v8 * 8 + 0x20);
                v23 = (uint)(v28 >> 0x3b) & 0x1e | (uint)v28 >> 2 & 1;
                if (v23 == 10) {
                    v28 = v28 & (unsigned long)ux20;
                    v16 = *(word_t *)(v28 + 0x10);
                    v17 = *(word_t *)(v28 + 0x18);
                    FUN_0036b270(v28);
                    thunk_FUN_0036b270(v17);
                    thunk_FUN_002acbb8(v16, v17);
                    FUN_0036b118(v28);
                    FUN_003a25d4(v17);
LAB_00473b54:
                    if (v26 == v8) {
                        FUN_0036b118(pv10);
                        v17 = loc_38;
                        v16 = loc_40;
                        FUN_004aa6c4();
                        v18 = FUN_00002534().lo;
                        ln13 = FUN_0036a9a0(v18, astk_70);
                        *(word_t *)(ln13 + 0x18) = v27;
                        *(word_t *)(ln13 + 0x10) = v21;
                        FUN_004aad30();
                        v28 = FUN_0036a940();
                        *(word_t *)(v28 + 0x10) = v16;
                        *(word_t *)(v28 + 0x18) = v17;
                        *(unsigned long *)(ln13 + 0x20) = v28 | 0x5000000000000000;
                        FUN_0049a758(ln13);
                        goto LAB_00474524;
                    }
                    bv4 = true;
                } else {
                    if (v23 == 9) {
                        FUN_004ac70c(loc_40);
                        if (x8_6 != 0) goto LAB_00473b54;   /* extraout_x8_06 */
                    } else if (v23 == 8) {
                        v29 = v28 & (unsigned long)ux20;
                        FUN_00117cc4(&loc_1d0, v29 + 0x10, 0xb0);
                        FUN_00117d14(&loc_120, v29 + 0x10, 0xb0);
                        iv6 = FUN_0049e2d4(&loc_1d0);
                        if (iv6 == 0) {
                            ln13 = FUN_0049e2f0(&loc_120);
                            v16 = *(word_t *)(ln13 + 8);
                            FUN_0036b270(v29);
                            FUN_004a36c4(&loc_1d0, loc_280);
                        } else {
                            if (iv6 != 1) goto LAB_00473990;
                            pv11 = (word_t *)FUN_0049e2f0(&loc_120);
                            bv4 = 0x7f < *(uint *)pv11;
                            if (bv4) {
                                FUN_004ac150();
                                if (bv4) {
                                    FUN_00463bd4();
                                    FUN_004aace0();
                                } else {
                                    FUN_004ab164();
                                }
                            }
                            FUN_004ac72c();
                            FUN_004ac720();
                            loc_280[0] = (x8_5 & 0xffffffff) + 0xfefefefefefeff &
                                           (x9_1 ^ 0xffffffffffffffff);   /* extraout_x8_05, extraout_x9_01 */
                            FUN_0036b270(v29);
                            FUN_00294cb4(loc_280, w10_0 - (w9_0 >> 3));   /* exw10 - exw9>>3 */
                            v16 = x1_04;              /* extraout_x1_04 */
                        }
                        FUN_003510dc();
                        thunk_FUN_002acbb8();
                        FUN_0036b118(v29);
                        FUN_003a25d4(v16);
                        goto LAB_00473b54;
                    }
LAB_00473990:
                    v17 = loc_38;
                    v16 = loc_40;
                    if (bv4) {
                        FUN_004aa6c4();
                        v18 = FUN_00002534().lo;
                        ln13 = FUN_0036a9a0(v18, loc_30);
                        *(word_t *)(ln13 + 0x18) = v27;
                        *(word_t *)(ln13 + 0x10) = v21;
                        FUN_004aad30();
                        v29 = FUN_0036a940();
                        *(word_t *)(v29 + 0x10) = v16;
                        *(word_t *)(v29 + 0x18) = v17;
                        pv32 = (unsigned long *)(ln13 + 0x20);
                        *pv32 = v29 | 0x5000000000000000;
                        v29 = *(unsigned long *)(pv12 + 0x10);
                        FUN_0036b270(v28 & (unsigned long)ux20);
                        v16 = FUN_003a261c(pv12);
                        if (((int)v16 == 0) ||
                            (v9 = *(unsigned long *)(pv12 + 0x18) >> 1, v9 <= v29)) {
                            pv12 = FUN_00498f0c(v16, v29 + 1, 1, pv12);
                            FUN_004ac778();
                            v9 = x8_7;               /* extraout_x8_07 */
                        }
                        v29 = *(unsigned long *)(pv12 + 0x10);
                        if (v9 < v29) {
                            /* WARNING: Does not return */
                            CL4_SWBP(0x474f14);
                        }
                        if (v9 == v29) {
                            /* WARNING: Does not return */
                            CL4_SWBP(0x474f18);
                        }
                        if ((word_t *)((char *)pv32) < (word_t *)(uintptr_t)(pv12 + v29 * 8 + 0x28) &&
                            (word_t *)(uintptr_t)(pv12 + v29 * 8 + 0x20) < (word_t *)(ln13 + 0x28)) {
                            /* WARNING: Does not return */
                            CL4_SWBP(0x474f20);
                        }
                        FUN_0035b67c((word_t *)(uintptr_t)(pv12 + v29 * 8 + 0x20), pv32, 1, 0x687408);
                        FUN_0036b118(ln13);
                        *(long *)(pv12 + 0x10) = *(long *)(pv12 + 0x10) + 1;
                        loc_40 = 0;
                        loc_38 = 0xe000000000000000;
                    } else {
                        FUN_0036b270(v28 & (unsigned long)ux20);
                    }
                    v29 = FUN_003a261c(pv12);
                    if ((v29 & 1) == 0) {
                        FUN_0006b3f4(*(word_t *)(pv12 + 0x10));
                        pv12 = FUN_00498f0c();
                    }
                    v29 = *(unsigned long *)(pv12 + 0x10);
                    if (*(unsigned long *)(pv12 + 0x18) >> 1 <= v29) {
                        FUN_000ec004();
                        pv12 = FUN_00498f0c();
                    }
                    *(unsigned long *)(pv12 + 0x10) = v29 + 1;
                    *(unsigned long *)(pv12 + v29 * 8 + 0x20) = v28;
                    loc_48 = pv12;
                    if (v26 == v8) {
                        FUN_0036b118(pv10);
                        FUN_003a25d4(loc_38);
                        goto LAB_00474524;
                    }
                    bv4 = false;
                }
                v28 = *(unsigned long *)(pv10 + 0x10);
                v8 = v8 + 1;
            } while (true);
        }
        FUN_0036b118(pv10);
LAB_00474524:
        pv10 = loc_48;
        v28 = *(unsigned long *)(loc_48 + 0x10);
        for (v8 = 0; v28 != v8; v8 = v8 + 1) {
            if (*(unsigned long *)(pv10 + 0x10) <= v8) {
                /* WARNING: Does not return */
                CL4_SWBP(0x474f08);
            }
            v26 = *(unsigned long *)(pv10 + v8 * 8 + 0x20);
            FUN_004ab998();
            FUN_0036b270(v26 & (unsigned long)ux20);
            sk_bcg_00473244(v26, 0, 0, 0); /* register-residue args */
            FUN_0036b118(v26 & (unsigned long)ux20);
            if (ux21 != 0) {
                FUN_0036b118(pv10);
                goto LAB_004745ac;
            }
        }
        FUN_0036b118(pv10);
        if (ux21 != 0) {
LAB_004745ac:
            FUN_0036b118(ln20);
            v21 = x1_13;              /* extraout_x1_13 */
            goto switchD_00473298_caseD_9;
        }
        FUN_0036b118(ln20);
        goto LAB_00474e78;
    case 2:
        FUN_004ab260();
        v21 = *(word_t *)(x8_8 + 0x10);        /* extraout_x8_08 */
        v17 = *(word_t *)(x8_8 + 0x18);
        v31 = *(word_t *)(x8_8 + 0x20);
        v27 = *(word_t *)(x8_8 + 0x30);
        ln13 = *(long *)(x8_8 + 0x38);
        v16 = *(word_t *)(x8_8 + 0x40);
        v18 = *(word_t *)(x8_8 + 0x48);
        v19 = *(word_t *)(x8_8 + 0x50);
        bv2 = *(byte *)(x8_8 + 0x58);
        v28 = (unsigned long)bv2;
        v5 = *(word_t *)(x8_8 + 0x28);
        FUN_00351f1c();
        FUN_004a36fc();
        sk_bcg_004775d0();
        sk_bcg_0047c474(); v8 = 0; /* register-residue args/return */
        FUN_004aa594();
        FUN_00498b28(ux20, x16_0);
        FUN_004ac7a4();
        FUN_004ab484();
        FUN_000a6e14();
        FUN_00498c1c();
        FUN_004ac7a4();
        FUN_004aa9e8();
        *(unsigned long *)(x9_2 + 0x20) = v8 | 0x1700000000000000;   /* extraout_x9_02 */
        *(word_t *)(ux20 + 8) = x8_9;          /* extraout_x8_09 */
        sk_bcg_00473244(v27, 0, 0, 0); av34.lo = 0; av34.hi = 0; /* register-residue */
        if (ux21 != 0) {
            FUN_00351f1c(ln13, v16);
            FUN_004a372c();
            FUN_0048525c();
            v21 = x1_05;             /* extraout_x1_05 */
            goto switchD_00473298_caseD_9;
        }
        FUN_004aa594();
        FUN_00498b28(ux20, x16_4);
        v21 = FUN_004ab018();
        FUN_00498c1c(v21, v17);
        FUN_004ab7ac();
        FUN_004aa9e8();
        *(unsigned long *)(x9_6 + 0x20) = v8 | 0x1800000000000000;    /* extraout_x9_06 */
        *(word_t *)(ux20 + 8) = x8_17;         /* extraout_x8_17 */
        if ((av34.hi & 0xff) != 1) {             /* av34._8_4_ & 0xff */
            sk_bcg_0047c4e4(av34.lo, v8);
        }
        if (ln13 != 0) {
            ln15 = FUN_0036a940(0x687d70, 0x31, 7);
            *(long *)(ln15 + 0x10) = ln13;
            *(word_t *)(ln15 + 0x18) = v16;
            *(word_t *)(ln15 + 0x20) = v18;
            *(word_t *)(ln15 + 0x28) = v19;
            *(byte *)(ln15 + 0x30) = bv2;
            FUN_0047c948(FUN_004a3774, ln15);
            FUN_0036b118(ln15);
            FUN_00351414();
            FUN_0047c9d4();
        }
        FUN_0048525c();
        goto LAB_00474c68;
    case 3:
        FUN_00117cc4(&loc_3c8, (v8 & 0xffffffffffffffb) + 0x10, 0x51);
        v21 = *(word_t *)((v8 & 0xffffffffffffffb) + 0x68);
        sk_bcg_004775d0();
        v23 = FUN_0041a868();
        if ((v23 & 0xff) != 2) {
            if ((v23 & 1) == 0) {
                FUN_004ab49c(str_backwards_assertions_5e27b0);
                FUN_004ab490(&loc_1d0, 0xd000000000000014, x9_8 | 0x8000000000000000);   /* extraout_x9_08 */
                thunk_FUN_0044f818();
                FUN_004aa370();
                av33 = FUN_004aaf9c();
                pv32 = (unsigned long *)av33.hi;
                ux21 = av33.lo;
                pv32[1] = stk_1c8;
                *pv32 = loc_1d0;
                pv32[3] = stk_1b8;
                pv32[2] = loc_1c0;
                FUN_004abe68(loc_1b0);
joined_r0x00474484:
                if (ux21 == 0) goto LAB_00474e70;
            } else {
                v27 = sk_bcg_004772d0();
                v28 = sk_bcg_004772d0();
                FUN_004aa5ac();
                FUN_00498b28(x16_2);
                FUN_003509b0();
                FUN_00498c1c();
                FUN_004ab334(*(word_t *)(ux20 + 8));
                *(word_t *)(x9_4 + 0x20) = 0x1100000000000000;   /* extraout_x9_04 */
                *(word_t *)(ux20 + 8) = x8_14;   /* extraout_x8_14 */
                FUN_004ab484();
                FUN_00481918(v28);
                FUN_004ab484();
                FUN_00498b28();
                FUN_004ac7a4();
                FUN_004ab484();
                FUN_003509b0();
                FUN_00498c1c();
                FUN_004ac7a4();
                FUN_004ab334();
                *(word_t *)(x9_5 + 0x20) = 0x1100000000000000;   /* extraout_x9_05 */
                *(word_t *)(ux20 + 8) = x8_15;   /* extraout_x8_15 */
                FUN_00481918(v27);
                sk_bcg_00473244(v21, 0, 0, 0); /* register-residue args */
                if ((v23 >> 8 & 1) == 0) {
                    if (ux21 == 0) {
                        FUN_004aa464();
                        FUN_00498b28(x16_3);
                        FUN_004aad44(*(word_t *)(ux20 + 8));
                        FUN_00498c1c();
                        FUN_004aa9e8(*(word_t *)(ux20 + 8));
                        FUN_004aaa38();
                        FUN_00481918(v27);
                        FUN_004ab478();
                        FUN_00498b28();
                        FUN_004aad44(*(word_t *)(ux20 + 8));
                        FUN_00498c1c();
                        FUN_004aa9e8(*(word_t *)(ux20 + 8));
                        FUN_004aaa38();
                        FUN_00498b28();
                        FUN_004aad44(*(word_t *)(ux20 + 8));
                        FUN_00498c1c();
                        FUN_004aa9e8(*(word_t *)(ux20 + 8));
                        FUN_004aaa38();
                        sk_bcg_00477494(v27);
LAB_004749d8:
                        FUN_004aa464();
                        FUN_00498b28(x16_8);
                        FUN_00350618();
                        FUN_00498c1c();
                        FUN_004aab88(*(word_t *)(ux20 + 8));
                        FUN_004aaa38();
                        sk_bcg_00477494(v28);
                        goto LAB_00474e70;
                    }
                } else if (ux21 == 0) {
                    FUN_004aa464();
                    FUN_00498b28(x16_7);
                    FUN_004aad44(*(word_t *)(ux20 + 8));
                    FUN_00498c1c();
                    FUN_004aa9e8(*(word_t *)(ux20 + 8));
                    FUN_004aaa38();
                    FUN_00481918(v27);
                    FUN_004ab478();
                    FUN_00498b28();
                    FUN_004aad44(*(word_t *)(ux20 + 8));
                    FUN_00498c1c();
                    FUN_004aa9e8(*(word_t *)(ux20 + 8));
                    FUN_004aaa38();
                    sk_bcg_00477494(v27);
                    FUN_004ab478();
                    FUN_00498b28();
                    FUN_00350618();
                    FUN_00498c1c();
                    FUN_004aab88(*(word_t *)(ux20 + 8));
                    *(word_t *)(x9_10 + 0x20) = 0x1300000000000000;  /* extraout_x9_10 */
                    *(word_t *)(ux20 + 8) = x8_18;  /* extraout_x8_18 */
                    goto LAB_004749d8;
                }
            }
LAB_00474e64:
            FUN_0048525c();
            v21 = x1_18;             /* extraout_x1_18 */
            goto switchD_00473298_caseD_9;
        }
        if (loc_378 < 2) {
LAB_004745b8:
            FUN_004ab394(str_these_should_produce_capture_5e2780);
            pv32 = loc_280;
            FUN_004ab490(loc_280, x10_1 + 0xf, x9_9 | 0x8000000000000000);  /* extraout_x10_00 + 0xf, extraout_x9_09 */
LAB_004745dc:
            thunk_FUN_0044f818();
            FUN_004aa4e0();
            av33 = FUN_004aaf9c();
            pv22 = (unsigned long *)av33.hi;
            ux21 = av33.lo;
            v8 = *pv32;
            pv22[1] = pv32[1];
            *pv22 = v8;
            v8 = pv32[2];
            pv22[3] = pv32[3];
            pv22[2] = v8;
            FUN_004abe68(pv32[4]);
            FUN_0048525c();
            v21 = x1_14;             /* extraout_x1_14 */
            break;
        }
        if (loc_378 == 2) {
            loc_120 = loc_3c8;
            stk_118 = stk_3c0;
            loc_110 = loc_3b8;
            stk_108 = stk_3b0;
            loc_100 = loc_3a8;
            loc_f8 = lStack_3a0;
            loc_f0 = loc_398;
            loc_e8 = lStack_390;
            if ((*(byte *)((word_t)ux20 + 0xd0) & 1) == 0) {
                sk_bcg_004766ec((long)&loc_120);
            }
            sk_bcg_004766ec((long)&loc_120);
LAB_00474e54:
            sk_bcg_00473244(v21, 0, 0, 0); /* register-residue args */
            goto joined_r0x00474484;
        }
        if (loc_378 != 3) goto LAB_00474e54;
        if ((((loc_3b8 == 0 && stk_3c0 == 0) && (loc_3c8 == 0 && stk_3b0 == 0)) &&
            ((loc_3a8 == 0 && lStack_3a0 == 0) && loc_398 == 0)) &&
            ((lStack_390 == 0 && lStack_380 == 0) && loc_388 == 0)) goto LAB_004745b8;
        if ((loc_3c8 != 3) ||
           ((((loc_3b8 != 0 || stk_3c0 != 0) || stk_3b0 != 0) ||
            ((loc_3a8 != 0 || lStack_3a0 != 0) || loc_398 != 0)) ||
            ((lStack_390 != 0 || lStack_380 != 0) || loc_388 != 0))) {
            if ((1 < loc_3c8 - 7 && (loc_3c8 & 0xfffffffffffffffe) != 4) ||
               ((((loc_3b8 != 0 || stk_3c0 != 0) || stk_3b0 != 0) ||
                ((loc_3a8 != 0 || lStack_3a0 != 0) || loc_398 != 0)) ||
                ((lStack_390 != 0 || lStack_380 != 0) || loc_388 != 0))) goto LAB_00474e54;
            FUN_004ab49c();
            pv32 = loc_30;
            FUN_004aaee8();
            FUN_004ab490(loc_30);
            goto LAB_004745dc;
        }
        v27 = sk_bcg_004772d0();
        v28 = sk_bcg_004772d0();
        FUN_00498b28(FUN_00499158);
        v16 = FUN_004aa7a8();
        FUN_00498c1c(v16, FUN_00499158);
        FUN_004ab7f0();
        FUN_004ab7e0();
        FUN_00481918(v28);
        FUN_00498b28(FUN_00499158);
        v16 = FUN_004aa7a8();
        FUN_00498c1c(v16, FUN_00499158);
        FUN_004ab7f0();
        FUN_004ab7e0();
        FUN_00481918(v27);
        sk_bcg_00473244(v21, 0, 0, 0); /* register-residue args */
        if (ux21 != 0) goto LAB_00474e64;
        FUN_00498b28(ux20, FUN_00499158);
        v21 = FUN_004ab018();
        FUN_00498c1c(v21, FUN_00499158);
        FUN_004ab7ac();
        FUN_004aa9e8();
        FUN_004ab344();
        FUN_00481918(v27);
        FUN_004ab484();
        FUN_00498b28(FUN_00499158);
        v21 = FUN_004ab018();
        FUN_00498c1c(v21, FUN_00499158);
        FUN_004ab7ac();
        FUN_004aa9e8();
        FUN_004ab344();
        sk_bcg_00477494(v27);
        FUN_004ab484();
        FUN_00498b28(FUN_00499158);
        FUN_004ab7ac();
        FUN_004ab484();
        FUN_00350618();
        FUN_00498c1c();
        FUN_004ab7ac();
        FUN_004aab88();
        FUN_004ab344();
        FUN_00498b28(FUN_00499158);
        FUN_004ab7ac();
        FUN_004ab484();
        FUN_00350618();
        FUN_00498c1c();
        FUN_004aab88(*(word_t *)(ux20 + 8));
        *(word_t *)(x9_0 + 0x20) = 0x1d00000000000000;   /* extraout_x9_00 */
        FUN_004abc44();
        sk_bcg_00477494(v28);
LAB_00474e70:
        FUN_0048525c();
        goto LAB_00474e78;
    case 4:
        FUN_004ab800();
        v28 = *(unsigned long *)(x8_0 + 0x10);    /* exx8 */
        FUN_0036b270(v28 & (unsigned long)ux20);
        sk_bcg_00473244(v28, 0, 0, 0); /* register-residue args */
        v26 = v28 & (unsigned long)ux20;
LAB_0047419c:
        FUN_0036b118(v26);
        v21 = x1_10;             /* extraout_x1_10 */
        break;
    case 5:
        FUN_004ab49c(v8, 1);
        FUN_004ab490(&loc_490, 0x6f697469646e6f43, 0xec000000736c616e);
        thunk_FUN_0044f818();
        FUN_004aa370();
        FUN_004aaf9c();
        x1_out4[1] = stk_488;    /* extraout_x1_06 */
        *x1_out4 = loc_490;
        x1_out4[3] = stk_478;
        x1_out4[2] = stk_480;
        loc_3d0 = loc_470;
        goto LAB_00473d2c;
    case 6:
        FUN_004ab260();
        v23 = (uint)param_4;
        stk_368 = *(word_t *)(x8_11 + 0x18);   /* extraout_x8_11 */
        loc_370 = *(word_t *)(x8_11 + 0x10);
        stk_358 = *(word_t *)(x8_11 + 0x28);
        stk_360 = *(word_t *)(x8_11 + 0x20);
        stk_348 = *(word_t *)(x8_11 + 0x38);
        loc_350 = *(word_t *)(x8_11 + 0x30);
        stk_338 = *(word_t *)(x8_11 + 0x48);
        stk_340 = *(word_t *)(x8_11 + 0x40);
        bv2 = *(byte *)(x8_11 + 0x50);
        v28 = (unsigned long)bv2;
        v27 = *(word_t *)(x8_11 + 0x58);
        if (bv2 >> 6 != 0) {
            v5 = bv2 >> 6 == 1;
            if (v5) {
                v28 = sk_bcg_00477694(*(word_t *)ux20, bv2 & 0x3f);
            } else {
                v7 = sk_bcg_004776c4(*(word_t *)ux20);
                v28 = (unsigned long)(v7 & 0xff);
            }
        }
        FUN_0041bfb4();
        av33 = FUN_00351db4();
        v21 = av33.hi;
        ln13 = av33.lo;
        if (v5) {
            FUN_004ab394(str_must_have_lower_bound_5e27d0);
            FUN_004ab490(&loc_120, x10_0 | 3, x9_7 | 0x8000000000000000);  /* exx10, extraout_x9_07 */
            thunk_FUN_0044f818();
            FUN_004aa4e0();
            av33 = FUN_004aaf9c();
            pv32 = (unsigned long *)av33.hi;
            ux21 = av33.lo;
            pv32[1] = stk_118;
            *pv32 = loc_120;
            pv32[3] = stk_108;
            pv32[2] = loc_110;
            pv32[4] = loc_100;
            FUN_0036986c();
            v21 = x1_11;         /* extraout_x1_11 */
        } else if ((v23 & 0xff) == 1) {
            v21 = 1;
            v8 = param_3;
LAB_004744b4:
            sk_bcg_004776ec(v27, v28, ln13, v8, v21); av33.lo = 0; av33.hi = 0; /* register-residue return */
            v21 = av33.hi;
            if ((av33.lo & 1) == 0) {
                v16 = sk_bcg_004772d0();
                v17 = sk_bcg_004772d0();
                v18 = sk_bcg_004772d0();
                v19 = sk_bcg_004772d0();
                if (ln13 < 2) {
                    v26 = 0x500000000000000;
                } else {
                    ux25 = *(unsigned long *)(ux20 + 0x68);
                    if (SCARRY8(ux25, 1)) {
                        /* WARNING: Does not return */
                        CL4_SWBP(0x474f38);
                    }
                    *(unsigned long *)(ux20 + 0x68) = ux25 + 1;
                    FUN_00350b3c();
                    FUN_004818d8();
                    v26 = ux25 | 0x500000000000000;
                }
                if ((v23 & 0xff) == 1 || (long)v8 < 1) {
                    v29 = 0x500000000000000;
                } else {
                    ux25 = *(unsigned long *)(ux20 + 0x68);
                    if (SCARRY8(ux25, 1)) {
                        /* WARNING: Does not return */
                        CL4_SWBP(0x474f3c);
                    }
                    *(unsigned long *)(ux20 + 0x68) = ux25 + 1;
                    FUN_000a6e14();
                    FUN_004818d8();
                    v29 = ux25 | 0x500000000000000;
                }
                if (((uint)v28 & 0xff) == 2) {
                    sk_bcg_00477e10();
                }
                sk_bcg_00477494(v16);
                if (ln13 == 0) {
                    v26 = 0x400000000000000;
LAB_00474b28:
                    FUN_004aa594();
                    FUN_00498b28(x16_9);
                    v21 = FUN_004ab770();
                    FUN_00498c1c(v21, ux25);
                    FUN_004aa9c0(*(word_t *)(ux20 + 8));
                    *(unsigned long *)(x9_11 + 0x20) = v26;   /* extraout_x9_11 */
                    FUN_004abc44();
                    FUN_00481918(v18);
                } else if (ln13 != 1) {
                    if (ln13 < 2) {
                        /* WARNING: Does not return */
                        CL4_SWBP(0x474b08);
                    }
                    goto LAB_00474b28;
                }
                sk_bcg_00477494(v17);
                if ((*(byte *)((word_t)ux20 + 0xd8) & 1) == 0) {
                    v25 = sk_bcg_00477e8c(v27);
                    iv6 = 0;
                    v9 = 1;
                    v26 = 0x600000000000000;
                    if (((v25 & 1) == 0) && ((v23 & 0xff) == 1)) {
LAB_00474bac:
                        v9 = *(unsigned long *)(ux20 + 0x78);
                        if (SCARRY8(v9, 1)) {
                            /* WARNING: Does not return */
                            CL4_SWBP(0x474f40);
                        }
                        *(unsigned long *)(ux20 + 0x78) = v9 + 1;
                        FUN_004aa464();
                        FUN_00498b28(x16_10);
                        v21 = FUN_004aa7fc(*(word_t *)(ux20 + 8));
                        FUN_00498c1c(v21, v26);
                        FUN_004aab88(*(word_t *)(ux20 + 8));
                        *(unsigned long *)(x9_12 + 0x20) = v9 | 0x200000000000000;  /* extraout_x9_12 */
                        *(word_t *)(ux20 + 8) = x8_19;   /* extraout_x8_19 */
                        v26 = v9 | 0x600000000000000;
                        iv6 = 1;
                        v9 = x10_1;      /* extraout_x10_01 */
                    }
                } else {
                    v26 = ux21;
                    if ((v23 & 0xff) == 1) goto LAB_00474bac;
                    iv6 = 0;
                    v9 = 1;
                    v26 = 0x600000000000000;
                }
                sk_bcg_00473244(v27, 0, 0, 0); /* register-residue args */
                v21 = x1_17;         /* extraout_x1_17 */
                if (ux21 == 0) {
                    if (iv6 != 0) {
                        if ((v9 & 1) != 0) {
                            /* WARNING: Does not return */
                            CL4_SWBP(0x474f60);
                        }
                        FUN_004aa5ac();
                        FUN_00498b28(x16_11);
                        v21 = FUN_004aa7fc(*(word_t *)(ux20 + 8));
                        FUN_00498c1c(v21, iv6);
                        FUN_004aab88(*(word_t *)(ux20 + 8));
                        *(unsigned long *)(x9_13 + 0x20) = v26;  /* extraout_x9_13 */
                        FUN_004abc44();
                        FUN_00481918(v19);
                    }
                    if (1 < ln13) {
                        FUN_004aa464();
                        FUN_00498b28(x16_12);
                        v21 = FUN_004aa7fc(*(word_t *)(ux20 + 8));
                        FUN_00498c1c(v21, v26);
                        FUN_004aab88(*(word_t *)(ux20 + 8));
                        *(word_t *)(x9_14 + 0x20) = 0x400000000000000;  /* extraout_x9_14 */
                        FUN_004abc44();
                        FUN_00481918(v16);
                    }
                    sk_bcg_00477494(v18);
                    pc3 = (code *)ux20;
                    if ((v23 & 0xff) != 1) {
                        if ((long)v8 < 0) {
                            /* WARNING: Does not return */
                            CL4_SWBP(0x474f64);
                        }
                        v26 = 0x400000000000000;
                        if (v8 != 0) {
                            v26 = v29;
                        }
                        pc3 = FUN_00499158;
                        FUN_00498b28(FUN_00499158);
                        v9 = *(unsigned long *)(*(long *)(ux20 + 8) + 0x10);
                        FUN_00350618();
                        FUN_00498c1c();
                        FUN_004aab88(*(word_t *)(ux20 + 8));
                        *(unsigned long *)(x9_15 + 0x20) = v26;  /* extraout_x9_15 */
                        *(word_t *)(ux20 + 8) = x8_21;   /* extraout_x8_21 */
                        FUN_00481918(v19);
                    }
                    FUN_004aa594();
                    FUN_00498b28(x16_13);
                    v21 = FUN_004ab770();
                    FUN_00498c1c(v21, v9);
                    FUN_004ab224(*(word_t *)(ux20 + 8));
                    ln13 = x8_22 + 0x20;   /* extraout_x8_22 */
                    if ((v28 & 0xff) == 0) {
                        *(word_t *)(ln13 + (long)pc3 * 8) = 0x1500000000000000;
LAB_00474ed0:
                        FUN_004abc44();
                        FUN_004819ac(v17, v19);
                    } else {
                        if (((uint)v28 & 0xff) != 1) {
                            *(word_t *)(ln13 + (long)pc3 * 8) = 0x1300000000000000;
                            *(long *)(ux20 + 8) = x8_22;
                            FUN_004aa4ac();
                            FUN_00498b28(x16_14);
                            FUN_00350518();
                            FUN_00498c1c();
                            FUN_004aa9c0(*(word_t *)(ux20 + 8));
                            *(word_t *)(x9_16 + 0x20) = 0x1500000000000000;  /* extraout_x9_16 */
                            goto LAB_00474ed0;
                        }
                        *(word_t *)(ln13 + (long)pc3 * 8) = 0x1100000000000000;
                        FUN_004abc44();
                        FUN_00481918(v17);
                    }
                    sk_bcg_00477494(v19);
                    v21 = x1_19;     /* extraout_x1_19 */
                }
            }
        } else if (param_3 != 0) {
            v8 = param_3 - ln13;
            if (ln13 <= (long)param_3) {
                if (SBORROW8(param_3, ln13)) {
                    /* WARNING: Does not return */
                    CL4_SWBP(0x474f34);
                }
                v21 = 0;
                goto LAB_004744b4;
            }
        }
        break;
    case 7:
        FUN_004ab260();
        v26 = *(unsigned long *)(x8_1 + 0x10);    /* extraout_x8_01 */
        bv2 = *(byte *)(x8_1 + 0x18);
        v21 = FUN_0036b270(v26).lo;
        v8 = FUN_0047ca18(v21, 0);
        v28 = v26;
        if ((v8 & 1) == 0) {
            FUN_004ac954(v26, bv2);
            sk_bcg_0047aa0c();
            goto LAB_0047419c;
        }
        FUN_0036b118(v26);
        if ((bv2 & 1) != 0) {
            FUN_004ab49c();
            FUN_004ab490(&loc_468, 0x6465747265766e49, 0xec000000796e6120);
            thunk_FUN_0044f818();
            FUN_004aa370();
            FUN_004aaf9c();
            x1_out3[1] = stk_460;    /* extraout_x1_03 */
            *x1_out3 = loc_468;
            x1_out3[3] = stk_450;
            x1_out3[2] = loc_458;
            loc_3d0 = loc_448;
            goto LAB_00473d2c;
        }
        FUN_004ac954();
        sk_bcg_00475cf8();
        v21 = x1_12;         /* extraout_x1_12 */
        break;
    case 8:
        FUN_004ab260();
        FUN_004ac12c(astk_330);
        FUN_00117cc4();
        FUN_004a36c4(astk_330, &loc_120);
        FUN_004ac954(astk_330);
        sk_bcg_00475544();
        FUN_004a36d4(astk_330);
        v21 = x1_08;         /* extraout_x1_08 */
        break;
    case 9:
    case 0x10:
        goto switchD_00473298_caseD_9;
    case 10:
        FUN_004ab260();
        v28 = *(unsigned long *)(x8_0 + 0x10);    /* extraout_x8_00 */
        v8 = *(unsigned long *)(x8_0 + 0x18);
        v29 = *(unsigned long *)(ux20 + 0xd8);
        thunk_FUN_0036b270(v8);
        v26 = v8 >> 0x38 & 0xf;
        if ((v29 & 1) == 0) {
            ln13 = *(long *)ux20;
            v9 = sk_bcg_00476c0c(ln13);
            if ((v9 & 1) != 0) {
                FUN_003507bc();
                v9 = FUN_0047cadc();
                if ((v9 & 1) != 0) goto LAB_00473dd0;
            }
            v9 = v28 & 0xffffffffffff;
            if ((v8 & 0x2000000000000000) != 0) {
                v9 = v26;
            }
            if (v9 == 0) goto LAB_00473dd0;
            if ((v8 >> 0x3c & 1) != 0) {
                FUN_003507bc();
                v9 = FUN_002b24b8();
            }
            if ((long)v9 < 5) goto LAB_00473dd0;
            if (*(long *)(ln13 + 0x10) == 0) {
                /* WARNING: Does not return */
                CL4_SWBP(0x474f50);
            }
            v23 = *(uint *)(ln13 + *(long *)(ln13 + 0x10) * 4 + 0x1c);
            if ((v23 & 1) != 0) goto LAB_00473dd0;
            FUN_003507bc();
            v21 = FUN_00083450();
            sk_bcg_00476c58(v21, v23 >> 0x10 & 1);
            FUN_0036b118(v21);
        } else {
LAB_00473dd0:
            ln13 = *(long *)ux20;
            if (*(long *)(ln13 + 0x10) == 0) {
                /* WARNING: Does not return */
                CL4_SWBP(0x474f4c);
            }
            ln15 = ln13 + 0x1c;
            if ((*(uint *)(ln15 + *(long *)(ln13 + 0x10) * 4) >> 0x10 & 1) == 0) {
                v5 = (v8 & 0x2000000000000000) == 0;
                v29 = v28 & 0xffffffffffff;
                if (!v5) {
                    v29 = v26;
                }
                FUN_004abe90(v29);
                stk_108 = x8_12;                 /* extraout_x8_12 */
                thunk_FUN_0036b270(v8);
                while (true) {
                    FUN_0029fb80();
                    if (x1_09 == 0) break;          /* extraout_x1_09 */
                    FUN_00354410();
                    FUN_003532b8();
                    ln20 = x8_13;                 /* extraout_x8_13 */
                    if (!v5) {
                        ln20 = x9_3;
                    }
                    if (ln20 != 0) {
                        ln30 = 0;
                        do {
                            if (((unsigned long)&loc_120 >> 0x3c & 1) != 0) {
                                av33 = FUN_002a49a8(ln30 << 0x10, v28, &loc_120);
                                goto LAB_00473ed4;
                            }
                            if (((unsigned long)&loc_120 >> 0x3d & 1) == 0) {
                                ln14 = ((unsigned long)&loc_120 & 0xfffffffffffffff) + 0x20;
                                if ((v28 >> 0x3c & 1) == 0) {
                                    FUN_00351714();
                                    ln14 = FUN_002a9ba8();
                                }
                                bv2 = *(byte *)(ln14 + ln30);
                                v26 = (unsigned long)bv2;
                                v23 = (uint)bv2;
                                if (-1 < (char)bv2) goto switchD_00473e90_caseD_0;
                                FUN_00352af0();
                                switch (x16_0) {    /* extraout_x16_00 */
                                default:
                                    goto switchD_00473e90_caseD_0;
                                case 1:
switchD_00473e90_caseD_1:
                                    FUN_00353ff4();
                                    av33.lo = w8_0 & 0xfffff800 | w8_0 & 0x3f | (v23 & 0x1f) << 6;   /* exw8 */
                                    av33.hi = 2;
                                    break;
                                case 2:
switchD_00473e90_caseD_2:
                                    FUN_00352e9c();
                                    av33.lo = (v23 & 0xf) << 0xc | (w9_1 & 0x3f) << 6 | w8_1 & 0x3f;  /* extraout_w9_00, extraout_w8_00 */
                                    av33.hi = 3;
                                    break;
                                case 3:
switchD_00473e90_caseD_3:
                                    FUN_0034c6d4();
                                    av33.lo = (v23 & 0xf) << 0x12 | (w9_2 & 0x3f) << 0xc |
                                                 (w10_1 & 0x3f) << 6 | w8_2 & 0x3f;   /* extraout_w9_01, extraout_w10_00, extraout_w8_01 */
                                    av33.hi = 4;
                                }
                            } else {
                                loc_1d0 = v28;
                                stk_1c8 = (unsigned long)&loc_120 & 0xffffffffffffff;
                                bv2 = *(byte *)((long)&loc_1d0 + ln30);
                                v26 = (unsigned long)bv2;
                                v23 = (uint)bv2;
                                if ((char)bv2 < '\0') {
                                    FUN_00352af0();
                                    switch (x16_1) {    /* extraout_x16_01 */
                                    case 1:
                                        goto switchD_00473e90_caseD_1;
                                    case 2:
                                        goto switchD_00473e90_caseD_2;
                                    case 3:
                                        goto switchD_00473e90_caseD_3;
                                    }
                                }
switchD_00473e90_caseD_0:
                                av33.hi = 1;
                                av33.lo = v26;
                            }
LAB_00473ed4:
                            if (*(long *)(ln13 + 0x10) == 0) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x474260);
                            }
                            if ((*(uint *)(ln15 + *(long *)(ln13 + 0x10) * 4) & 1) == 0) {
                                ln14 = *(long *)(ux20 + 8);
LAB_00473f2c:
                                v26 = FUN_003a261c(ln14);
                                if ((v26 & 1) == 0) {
                                    FUN_0006b3f4(*(word_t *)(ln14 + 0x10));
                                    ln14 = FUN_00499158();
                                }
                                v26 = 0x900000000000000;
                            } else {
                                v26 = FUN_002bc2f8(av33.lo);
                                ln14 = *(long *)(ux20 + 8);
                                if ((v26 & 1) == 0) goto LAB_00473f2c;
                                v26 = FUN_003a261c(ln14);
                                if ((v26 & 1) == 0) {
                                    FUN_0006b3f4(*(word_t *)(ln14 + 0x10));
                                    ln14 = FUN_00499158();
                                }
                                v26 = 0x980000000000000;
                            }
                            v29 = *(unsigned long *)(ln14 + 0x10);
                            if (*(unsigned long *)(ln14 + 0x18) >> 1 <= v29) {
                                FUN_0006b42c();
                                FUN_004abb28();
                                ln14 = FUN_00499158();
                            }
                            *(unsigned long *)(ln14 + 0x10) = v29 + 1;
                            *(unsigned long *)(ln14 + v29 * 8 + 0x20) = av33.lo & 0xffffffff | v26;
                            *(long *)(ux20 + 8) = ln14;
                            ln30 = av33.hi + ln30;
                            v5 = ln30 == ln20;
                        } while (ln30 < ln20);
                    }
                    FUN_003a25d4(&loc_120);
                }
            } else {
                if ((v29 & 1) == 0) {
                    v29 = v28 & 0xffffffffffff;
                    if ((v8 & 0x2000000000000000) != 0) {
                        v29 = v26;
                    }
                    FUN_004abe90(v29);
                    stk_108 = x8_16;             /* extraout_x8_16 */
                    thunk_FUN_0036b270(v8);
                    while (true) {
                        av33 = FUN_0029fb80();
                        ln20 = av33.hi;
                        if (ln20 == 0) break;
                        if (av33.lo == 0xa0d && ln20 == -0x1e00000000000000) {
LAB_00474250:
                            FUN_003a25d4(ln20);
                        } else {
                            FUN_00351f88();
                            FUN_004aa890();
                            v29 = FUN_002a0cf8();
                            if ((v29 & 1) != 0) goto LAB_00474250;
                            FUN_00351f88();
                            v29 = FUN_002bd848();
                            if ((v29 & 1) == 0) {
LAB_00474b08:
                                FUN_003a25d4(ln20);
                                FUN_003a25d4(v8);
                                goto LAB_00474c18;
                            }
                            FUN_00351f88();
                            v29 = FUN_0016749c();
                            if ((v29 & 0xff00000000) == 0x100000000) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x474f44);
                            }
                            if ((v29 & 0xffffff80) != 0) goto LAB_00474b08;
                            FUN_00351f88();
                            v29 = FUN_0016749c();
                            if ((v29 & 0xff00000000) == 0x100000000) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x474f48);
                            }
                            FUN_004ac930();
                            FUN_003a25d4();
                            if ((av33.lo & 0xffffff00) != 0) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x474f1c);
                            }
                        }
                    }
                    FUN_003a25d4(v8);
                    if (x8_16 == 0) goto LAB_00474c18;
                    FUN_00350518();
                    sk_bcg_00476cd4(0, 0); /* register-residue args */
                    if ((param_3 ^ param_4) >> 0xe == 0) {
                        FUN_003a25d4(x1_15);        /* extraout_x1_15 */
                        /* WARNING: Does not return */
                        CL4_SWBP(0x474f5c);
                    }
                    FUN_004abaac();
                    FUN_004a3a94();
                    FUN_004ac2d0();
                    FUN_003a25d4();
                    FUN_00350518();
                    av33 = sk_bcg_00476cd4(0, 0); /* register-residue args */
                    v26 = param_3 >> 0xe;
                    loc_1d0 = param_3;
                    if (v26 != param_4 >> 0xe) {
                        v23 = (uint)(v28 >> 0x3b) & 1;
                        if ((v8 & 0x1000000000000000) == 0) {
                            v23 = 1;
                        }
                        do {
                            v29 = loc_1d0;
                            FUN_004a39dc(&loc_1d0, av33.lo, av33.hi, param_3, param_4);
                            if (((v29 & 0xc) != 4UL << v23) && ((v29 & 1) != 0)) {
                                v9 = v29 >> 0x10;
                                if (x8_16 <= v9) {
                                    /* WARNING: Does not return */
                                    CL4_SWBP(0x474f2c);
                                }
LAB_00474750:
                                if ((v8 >> 0x3c & 1) == 0) goto LAB_00474754;
LAB_00474848:
                                v29 = FUN_002a49a8(v29 & 0xffffffffffff0000, v28).lo;
                                goto switchD_004747a8_caseD_0;
                            }
                            if ((v29 & 0xc) == 4UL << v23) {
                                FUN_00350618();
                                v29 = FUN_0001da84();
                            }
                            v9 = v29 >> 0x10;
                            if (x8_16 <= v9) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x474f30);
                            }
                            if ((v29 & 1) != 0) goto LAB_00474750;
                            FUN_00350618();
                            v29 = FUN_001676cc();
                            v9 = v29 >> 0x10;
                            if ((v8 >> 0x3c & 1) != 0) goto LAB_00474848;
LAB_00474754:
                            if ((v8 & 0x2000000000000000) != 0) {
                                loc_120 = v28;
                                stk_118 = v8 & 0xffffffffffffff;
                                bv2 = *(byte *)((long)&loc_120 + v9);
                                v29 = (unsigned long)bv2;
                                v7 = (uint)bv2;
                                if ((char)bv2 < '\0') {
                                    FUN_00352af0();
                                    switch (x16_6) {    /* extraout_x16_06 */
                                    case 1:
                                        goto switchD_004747a8_caseD_1;
                                    case 2:
                                        goto switchD_004747a8_caseD_2;
                                    case 3:
                                        goto switchD_004747a8_caseD_3;
                                    }
                                }
                                goto switchD_004747a8_caseD_0;
                            }
                            ln20 = (v8 & 0xfffffffffffffff) + 0x20;
                            if ((v28 >> 0x3c & 1) == 0) {
                                ln20 = FUN_002a9ba8(v28, v8);
                            }
                            bv2 = *(byte *)(ln20 + v9);
                            v29 = (unsigned long)bv2;
                            v7 = (uint)bv2;
                            if (-1 < (char)bv2) goto switchD_004747a8_caseD_0;
                            FUN_00352af0();
                            switch (x16_5) {        /* extraout_x16_05 */
                            case 1:
switchD_004747a8_caseD_1:
                                FUN_00353ff4();
                                v29 = (unsigned long)(w8_3 & 0xfffff800 | w8_3 & 0x3f | (v7 & 0x1f) << 6);   /* extraout_w8_02 */
                                break;
                            case 2:
switchD_004747a8_caseD_2:
                                FUN_00352e9c();
                                v7 = (v7 & 0xf) << 0xc | (w9_3 & 0x3f) << 6;   /* extraout_w9_02 */
                                v24 = w8_4;      /* extraout_w8_03 */
                                goto LAB_00474828;
                            case 3:
switchD_004747a8_caseD_3:
                                FUN_0034c6d4();
                                v7 = (v7 & 0xf) << 0x12 | (w9_4 & 0x3f) << 0xc |
                                        (w10_2 & 0x3f) << 6;   /* extraout_w9_03, extraout_w10_01 */
                                v24 = w8_5;      /* extraout_w8_04 */
LAB_00474828:
                                v29 = (unsigned long)(v7 | v24 & 0x3f);
                            }
switchD_004747a8_caseD_0:
                            if (*(long *)(ln13 + 0x10) == 0) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x474f24);
                            }
                            if (((*(uint *)(ln15 + *(long *)(ln13 + 0x10) * 4) & 1) == 0) ||
                               (v9 = FUN_002bc2f8(v29), (v9 & 1) == 0)) {
                                v25 = 0x900000000000000;
                                v9 = 0x940000000000000;
                            } else {
                                v25 = 0x980000000000000;
                                v9 = 0x9c0000000000000;
                            }
                            if (v26 != (v28 & 0xffffffffffff) >> 0xe) {
                                v9 = v25;
                            }
                            ln20 = *(long *)(ux20 + 8);
                            v26 = FUN_003a261c(ln20);
                            if ((v26 & 1) == 0) {
                                FUN_0006b3f4(*(word_t *)(ln20 + 0x10));
                                ln20 = FUN_00499158();
                            }
                            v26 = *(unsigned long *)(ln20 + 0x10);
                            if (*(unsigned long *)(ln20 + 0x18) >> 1 <= v26) {
                                v21 = FUN_0006b42c();
                                ln20 = FUN_00499158(v21, v26 + 1, 1, ln20);
                            }
                            *(unsigned long *)(ln20 + 0x10) = v26 + 1;
                            *(unsigned long *)(ln20 + v26 * 8 + 0x20) = v9 | v29 & 0xffffffff;
                            *(long *)(ux20 + 8) = ln20;
                            v26 = loc_1d0 >> 0xe;
                        } while (v26 != param_4 >> 0xe);
                    }
                    FUN_003a25d4(av33.hi);
                    goto LAB_00474c60;
                }
LAB_00474c18:
                v28 = v28 & 0xffffffffffff;
                if ((v8 & 0x2000000000000000) != 0) {
                    v28 = v26;
                }
                FUN_004abe90(v28);
                stk_108 = x8_20;             /* extraout_x8_20 */
                thunk_FUN_0036b270(v8);
                while (FUN_0029fb80(), x1_16 != 0) {   /* extraout_x1_16 */
                    sk_bcg_00475e14();
                    FUN_003a25d4(x1_16);
                }
            }
            FUN_003a25d4(v8);
        }
LAB_00474c60:
        FUN_003a25d4(v8);
LAB_00474c68:
        v28 = 0;
        v21 = 1;
        goto switchD_00473298_caseD_9;
    case 0xb:
        FUN_004ab49c(v8, 1);
        FUN_004ab490(&loc_440, 0x6620746e65736261, 0xef6e6f6974636e75);
        thunk_FUN_0044f818();
        FUN_004aa370();
        FUN_004aaf9c();
        x1_out2[1] = stk_438;    /* extraout_x1_02 */
        *x1_out2 = loc_440;
        x1_out2[3] = stk_428;
        x1_out2[2] = stk_430;
        loc_3d0 = loc_420;
        goto LAB_00473d2c;
    case 0xc:
        FUN_004ab260();
        FUN_004ac954(*(word_t *)(x8_10 + 0x10));   /* extraout_x8_10 */
        sk_bcg_00473244(0, 0, 0, 0); av33.lo = 0; av33.hi = 0; /* register-residue */
        v21 = av33.hi;
        if (ux21 == 0) {
            v28 = av33.lo;
        }
        goto switchD_00473298_caseD_9;
    case 0xd:
        FUN_004ab49c(v8, 1);
        FUN_004ab490(&loc_418, 0x72656d75736e6f63, 0xe800000000000000);
        thunk_FUN_0044f818();
        FUN_004aa370();
        FUN_004aaf9c();
        x1_out1[1] = stk_410;    /* extraout_x1_01 */
        *x1_out1 = loc_418;
        x1_out1[3] = stk_400;
        x1_out1[2] = loc_408;
        loc_3d0 = loc_3f8;
        goto LAB_00473d2c;
    case 0xe:
        v8 = v8 & 0xffffffffffffffb;
        FUN_00002834(0x687d48);
        ln13 = FUN_0036a940();
        v21 = *(word_t *)(v8 + 0x20);
        v27 = *(word_t *)(v8 + 0x18);
        *(word_t *)(ln13 + 0x18) = *(word_t *)(v8 + 0x20);
        *(word_t *)(ln13 + 0x10) = v27;
        FUN_0036b270(v21);
        sk_bcg_00477504(); /* register-residue args dropped */
        FUN_0036b118(ln13);
        v28 = *(unsigned long *)(ux20 + 0x70);
        if (SCARRY8(v28, 1)) {
            /* WARNING: Does not return */
            CL4_SWBP(0x474f28);
        }
        *(unsigned long *)(ux20 + 0x70) = v28 + 1;
        FUN_00350518();
        sk_bcg_00477590(0, 0); /* register-residue args */
        v21 = 0;
        goto switchD_00473298_caseD_9;
    case 0xf:
        FUN_004ab49c(str_character_predicates_5e2660, v8, 1);
        FUN_004ab490(&loc_3f0, 0xd000000000000014, x9_0 | 0x8000000000000000);  /* exx9 */
        thunk_FUN_0044f818();
        FUN_004aa370();
        FUN_004aaf9c();
        x1_out0[1] = stk_3e8;    /* exx1 */
        *x1_out0 = loc_3f0;
        x1_out0[3] = stk_3d8;
        x1_out0[2] = stk_3e0;
LAB_00473d2c:
        FUN_004abe68(loc_3d0);
        v21 = x1_07;             /* extraout_x1_07 */
        goto switchD_00473298_caseD_9;
    }
    if (ux21 == 0) {
LAB_00474e78:
        v21 = 1;
        v28 = 0;
    }
switchD_00473298_caseD_9:
    FUN_00353d14(v28, v21, x1_0);   /* exx1 */
}

/* FUN_00474fe8 @ 0x00474fe8   (est. sk_bcg_00474fe8)
 * Ghidra: void sk_bcg_00474fe8(long *param_1)
 * ByteCodeGen finalize/emit: consumes a bitmask of set capture groups from
 * a builder at ux20, iterates the set bits (bit-reversal/leading-zero
 * scan) to attach "capture" bytecode entries, then, when no error is
 * pending, folds the remaining builder state (character classes, ranges,
 * names) into the caller's param_1 output record and returns it.
 * Confidence: medium   Notes: heavy bit-reversal trick + LZCOUNT scan;
 * string-fatal paths (s__AppleInternal_Library_BuildRoot_...). */
static void sk_bcg_00474fe8(long *param_1)
{
    unsigned long *pv1;
    long *pl2;
    uint v3;
    char cv4;
    code *pc5;
    bool bv6;
    word_t v7, v8, v12, v14, v20, v21, v28, v30;
    long ln9, ln10, ln13, ln16, ln17, ln18, ln19, ln22, ln23, ln24, ln25, ln26, ln29, ln31, ln32, ln34, ln35;
    long ln5;
    word_t exx16;     /* exx16 */
    word_t *exx1;     /* exx1 (undefined8* write target) */
    word_t *pv11, *pv15;
    long *ux20;
    long ux21;
    wpair_t av38;
    char *pc27;
    word_t v33, v36, v37;
    word_t loc_100, stk_f8, loc_f0, loc_e8, stk_e0, loc_d8, stk_d0, loc_c8, loc_c0;
    word_t loc_b8[5];
    word_t astk_90[6];

    ln22 = ux20[0x17];
    v20 = 1UL << ((unsigned long)*(byte *)(ln22 + 0x20) & 0x3f);
    v28 = 0xffffffffffffffff;
    if ((*(byte *)(ln22 + 0x20) & 0x3f) < 6) {
        v28 = ~(-1L << (v20 & 0x3f));
    }
    v28 = v28 & *(unsigned long *)(ln22 + 0x40);
    ln24 = *ux20;
    thunk_FUN_0036b270(ln22);
    v8 = FUN_003a261c(ln24);
    if ((v8 & 1) == 0) {
        ln24 = FUN_0049a51c(ln24);
    }
    ln29 = 0;
    *ux20 = ln24;
joined_r0x00475080:
    do {
        if (v28 != 0) {
            ln16 = ux20[0x18];
            if (*(long *)(ln16 + 0x10) != 0) {
                v8 = (v28 & 0xaaaaaaaaaaaaaaaa) >> 1 | (v28 & 0x5555555555555555) << 1;
                v8 = (v8 & 0xcccccccccccccccc) >> 2 | (v8 & 0x3333333333333333) << 2;
                v8 = (v8 & 0xf0f0f0f0f0f0f0f0) >> 4 | (v8 & 0xf0f0f0f0f0f0f0f) << 4;
                v8 = (v8 & 0xff00ff00ff00ff00) >> 8 | (v8 & 0xff00ff00ff00ff) << 8;
                v8 = (v8 & 0xffff0000ffff0000) >> 0x10 | (v8 & 0xffff0000ffff) << 0x10;
                v8 = LZCOUNT(v8 >> 0x20 | v8 << 0x20) | ln29 << 6;
                ln26 = *(long *)(*(long *)(ln22 + 0x38) + v8 * 8);
                av38 = FUN_00499f0c(*(word_t *)(*(long *)(ln22 + 0x30) + v8 * 8));
                if ((av38.hi & 1) != 0) {
                    v28 = v28 - 1 & v28;
                    ln18 = *(long *)(ln26 + 0x10);
                    if (ln18 != 0) {
                        ln17 = *(long *)(*(long *)(ln16 + 0x38) + av38.lo * 8);
                        FUN_0036b270(ln26);
                        ln16 = 0x20;
                        do {
                            v8 = *(unsigned long *)(ln26 + ln16);
                            if ((long)v8 < 0) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x475514);
                            }
                            if (*(unsigned long *)(ln24 + 0x10) <= v8) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x475518);
                            }
                            *(unsigned long *)(ln24 + 0x20 + v8 * 8) =
                                 (unsigned long)(*(short *)(ln24 + 0x20 + v8 * 8) == 1) |
                                 ln17 << 0x10 | 0x1b00000000000000U;
                            ln16 = ln16 + 8;
                            ln18 = ln18 + -1;
                        } while (ln18 != 0);
                        FUN_0036b118(ln26);
                        *ux20 = ln24;
                    }
                    goto joined_r0x00475080;
                }
            }
            FUN_0036b118(ln22);
            ux21 = FUN_004aa610();
            FUN_004acb6c();
            goto LAB_0047516c;
        }
        bv6 = SCARRY8(ln29, 1);
        ln29 = ln29 + 1;
        if (bv6) {
            /* WARNING: Does not return */
            CL4_SWBP(0x47551c);
        }
        if ((long)(v20 + 0x3f >> 6) <= ln29) break;
        v28 = ((unsigned long *)(ln22 + 0x40))[ln29];
    } while (true);
    FUN_0036b118(ln22);
LAB_0047516c:
    if (ux21 == 0) {
        v7 = (char)ux20[0x13] == '\x01';
        if (v7) {
            ln22 = *ux20;
        } else {
            sk_bcg_00477494(ux20[0x12]);
            FUN_004aa464();
            FUN_00498b28(exx16);
            ln24 = *(long *)(*ux20 + 0x10);
            FUN_00350618();
            FUN_00498c1c();
            ln22 = *ux20;
            *(long *)(ln22 + 0x10) = ln24 + 1;
            *(word_t *)(ln22 + ln24 * 8 + 0x20) = 0x1d00000000000000;
            *ux20 = ln22;
        }
        ln24 = ux20[0xb];
        FUN_0036b270(ln22);
        v28 = 0;
        pc27 = (char *)(ln24 + 0x38);
        while (FUN_004ac850(), !v7) {
            if (*(unsigned long *)(ln24 + 0x10) <= v28) {
                /* WARNING: Does not return */
                CL4_SWBP(0x475520);
            }
            v20 = *(unsigned long *)(pc27 + -0x18);
            if ((long)v20 < 0) {
                /* WARNING: Does not return */
                CL4_SWBP(0x475524);
            }
            if (*(unsigned long *)(ln22 + 0x10) <= v20) {
                /* WARNING: Does not return */
                CL4_SWBP(0x475528);
            }
            v8 = *(unsigned long *)(pc27 + -0x10);
            if ((long)v8 < 0) {
                /* WARNING: Does not return */
                CL4_SWBP(0x47552c);
            }
            v30 = *(unsigned long *)(ux20[10] + 0x10);
            if (v30 <= v8) {
                /* WARNING: Does not return */
                CL4_SWBP(0x475530);
            }
            ln29 = ux20[10] + 0x20;
            pv1 = (unsigned long *)(ln29 + v8 * 0x10);
            if ((char)pv1[1] == '\x01') {
                /* WARNING: Does not return */
                CL4_SWBP(0x47553c);
            }
            v12 = *(unsigned long *)(pc27 + -8);
            cv4 = *pc27;
            v14 = *(unsigned long *)(ln22 + v20 * 8 + 0x20);
            v21 = *pv1;
            av38 = FUN_004816b4(v14 >> 0x38);
            v3 = av38.lo & 0xff;
            v8 = v21;
            if ((((1 < v3 - 0x11 && v3 != 4) && (v8 = v21 | v14 << 0x10, v3 != 5)) &&
                (v3 != 6)) && (v8 = v21, v3 != 0x14)) {
                if (v3 != 0x15) {
                    if (v3 == 0x1e) {
                        /* WARNING: Does not return */
                        CL4_SWBP(0x475540);
                    }
                    pv15 = astk_90;
                    FUN_004aaee8(av38.lo, av38.hi, (word_t)"\x00" + 0x5e2560);  /* str_build_root_5e2560 */
                    pv11 = astk_90;
LAB_004754c4:
                    thunk_FUN_0044f818(pv11);
                    FUN_004aa4e0();
                    FUN_004aaf9c();
                    v33 = *pv15;
                    v37 = pv15[3];
                    v36 = pv15[2];
                    exx1[1] = pv15[1];
                    *exx1 = v33;
                    exx1[3] = v37;
                    exx1[2] = v36;
                    FUN_004abe68(pv15[4]);
                    FUN_0036b118(ln22);
                    return;
                }
                if (cv4 == '\x01') {
                    pv15 = loc_b8;
                    FUN_004aaee8(av38.lo, av38.hi, (word_t)"\x00" + 0x5e2560);
                    pv11 = loc_b8;
                    goto LAB_004754c4;
                }
                if (v30 <= v12) {
                    /* WARNING: Does not return */
                    CL4_SWBP(0x475538);
                }
                pl2 = (long *)(ln29 + v12 * 0x10);
                if ((char)pl2[1] == '\x01') {
                    /* WARNING: Does not return */
                    CL4_SWBP(0x475544);
                }
                v8 = v21 | *pl2 << 0x10;
            }
            v30 = FUN_003a261c(ln22);
            if ((v30 & 1) == 0) {
                ln22 = FUN_0049a51c(ln22);
            }
            v7 = v20 == *(unsigned long *)(ln22 + 0x10);
            if (*(unsigned long *)(ln22 + 0x10) <= v20) {
                /* WARNING: Does not return */
                CL4_SWBP(0x475534);
            }
            *(unsigned long *)(ln22 + v20 * 8 + 0x20) = v8 | (unsigned long)v3 << 0x38;
            pc27 = pc27 + 0x20;
            v28 = v28 + 1;
        }
        ln25 = ux20[3];
        ln23 = ux20[9];
        ln24 = ux20[0xd];
        FUN_0036b270(ln25);
        ln29 = ux20[6];
        ln34 = ux20[6];
        ln31 = ux20[5];
        FUN_0036b270(ln31);
        FUN_0036b270(ln29);
        ln29 = ux20[8];
        ln35 = ux20[8];
        ln32 = ux20[7];
        FUN_0036b270(ln32);
        FUN_0036b270(ln29);
        av38 = FUN_0036b270(ln23);
        FUN_00350530(av38.lo, av38.hi, (word_t)"\x00" + 8, &DAT_004c0740);   /* str_cstring_0064c108 + 8 */
        ln17 = FUN_00481b40();
        loc_e8 = (word_t)DAT_00688af0;
        av38 = FUN_00481ac4(&loc_100, ln24);
        FUN_004abd64(av38.lo, av38.hi, &DAT_00657678, &DAT_005a4b20);
        ln9 = FUN_00481b40();
        loc_100 = 0;
        stk_f8 = 0;
        loc_f0 = 1;
        stk_e0 = 0;
        loc_e8 = 0;
        stk_d0 = 0;
        loc_d8 = 0;
        loc_c8 = 0;
        loc_c0 = 1;
        ln10 = FUN_00481b9c(&loc_100, ux20[0x11]);
        ln13 = ux20[0xf];
        ln16 = ux20[0x10];
        ln26 = ux20[1];
        v7 = *(word_t *)((long)ux20 + 9);
        ln19 = ux20[0x18];
        ln24 = ux20[0x14];
        ln29 = ux20[0x15];
        ln18 = ux20[0x16];
        *param_1 = ln22;
        param_1[1] = ln13;
        *(char *)(param_1 + 2) = (char)ln16;
        *(char *)((long)param_1 + 0x11) = (char)ln26;
        *(word_t *)((long)param_1 + 0x12) = v7;
        param_1[3] = ln24;
        param_1[4] = ln19;
        param_1[5] = ln29;
        *(char *)(param_1 + 6) = (char)ln18;
        param_1[7] = ln25;
        param_1[9] = ln34;
        param_1[8] = ln31;
        param_1[0xb] = ln35;
        param_1[10] = ln32;
        param_1[0xc] = ln23;
        *(word_t *)(param_1 + 0xd) = 0;
        param_1[0xe] = ln17;
        param_1[0xf] = av38.lo;
        param_1[0x10] = ln9;
        param_1[0x11] = ln10;
        FUN_0036b270(ln24);
        thunk_FUN_0036b270(ln19);
        FUN_0036b270(ln29);
    }
}

/* FUN_00475544 @ 0x00475544   (est. sk_bcg_00475544)
 * Ghidra: void sk_bcg_00475544(void)
 * ByteCodeGen special-form emitter: reads a decoded Swift "insn" struct from
 * two stack buffers and switches on its tag to emit the bytecode for a
 * backreference / quantifier / capture / error-form. Cases build fatal-message
 * structs (Backreference_kind, .K reset-keep-assertion) or append kind-tagged
 * instruction words into the builder at ux19.
 * Confidence: medium   Notes: many extraout_* artifacts; string-fatal paths;
 * traps 0x475b9c..0x475bc8. */
static void sk_bcg_00475544(void)
{
    unsigned long v1, v2, v11;
    code *pc3;
    unsigned int v4;
    uint v5;
    int iv6;
    byte *pb8;
    word_t v9, v14;
    long ln10;
    unsigned int *pv12;
    word_t *pv13;
    word_t x1, x1_0, x1_1, x1_2;   /* exx1, _00, _01, _02 */
    byte bv15;
    uint w8_0, w8_1;               /* exw8, _00 */
    code *x8, *x8_2;               /* exx8, extraout_x8_02 */
    long x8_0, x8_3;               /* extraout_x8_00, extraout_x8_03 */
    unsigned long x8_1, x8_4;      /* extraout_x8_01, extraout_x8_04 */
    long x9, x9_1, x9_2, x9_3, x9_5, x9_6;   /* exx9, _01.._06 */
    unsigned long x9_0, x9_4;      /* extraout_x9_00, _04 */
    long x10;                      /* exx10 */
    word_t x16, x16_0, x16_1, x16_2, x16_3;  /* exx16.._03 */
    long *ux19;
    long ux21;
    wpair_t av16;
    word_t loc_458, stk_450, loc_448, stk_440, loc_438;
    word_t astk_1e8[22];        /* astk_1e8 [176] */
    word_t loc_138[2];
    word_t loc_128, stk_127, stk_120, loc_118;
    word_t loc_d8, stk_d0;
    word_t loc_c8[5];      /* loc_c8 [40] */
    word_t astk_430[22];        /* astk_430 [176] */
    word_t loc_380, stk_378, stk_370, stk_368, loc_360, stk_358;
    word_t stk_350, stk_348, loc_290, stk_288, stk_280, stk_278;
    word_t loc_270, stk_268, stk_260, stk_258;
    word_t astk_340[22];        /* astk_340 [176] */
    word_t loc_248, loc_240, loc_228;
    word_t astk_a0[5];          /* astk_a0 [40] */
    word_t loc_78, stk_70;

    FUN_00464a44();
    FUN_004ab0f0(astk_1e8);
    FUN_00117cc4();
    FUN_004ab0f0(astk_430);
    FUN_00117cc4();
    v4 = FUN_0049e2d4(astk_430);
    switch (v4) {
    default:
        FUN_0049e2f0(astk_430);
        FUN_000e0654();
        sk_bcg_00475e14();
        break;
    case 1:
        FUN_0049e2f0(astk_430);
        pv12 = (unsigned int *)FUN_004ab568();
        if (x9_1 == 0) {            /* extraout_x9_01 */
            /* WARNING: Does not return */
            CL4_SWBP(0x475ba4);
        }
        v5 = FUN_004ab55c(*pv12).lo;
        if ((w8_0 >> 0x10 & 1) == 0) {   /* exw8 */
            sk_bcg_00476518();
        } else {
            if (v5 < 0x80) {
                v11 = (unsigned long)(v5 + 1);
            } else if (v5 < 0x800) {
                v11 = FUN_004abff8();
            } else {
                FUN_004ab9bc((v5 & 0x3f) << 8);
                v11 = FUN_004aacf8();
            }
            av16 = FUN_00255d4c(v11);
            loc_138[0] = av16.lo;
            if (av16.hi < 0) {
                /* WARNING: Does not return */
                CL4_SWBP(0x475b9c);
            }
            FUN_00294cb4(loc_138);
            sk_bcg_00475e14();
            FUN_003a25d4(x1_1);     /* extraout_x1_01 */
        }
        break;
    case 2:
        pv13 = (word_t *)FUN_0049e2f0(astk_430);
        v5 = sk_bcg_00476e94(*ux19, *pv13);
        v11 = FUN_00481320(v5 & 0xff01ffff);
        v11 = v11 | 0xc00000000000000;
        goto LAB_00475684;
    case 3:
        pb8 = (byte *)FUN_0049e2f0(astk_430);
        bv15 = *pb8;
        if ((unsigned long)bv15 == 3) {
            FUN_004ab394(str_reset_keep_assertion_5e29f0);
            FUN_004ab490(loc_138, x10 + 5, x9_0 | 0x8000000000000000);  /* exx10, extraout_x9_00 */
            thunk_FUN_0044f818();
            FUN_004aa370();
            av16 = FUN_004aaf9c();
            pv13 = (word_t *)av16.hi;
            ux21 = av16.lo;
            pv13[1] = loc_138[1];
            *pv13 = loc_138[0];
            pv13[3] = stk_120;
            pv13[2] = (stk_127 << 8) | (loc_128 & 0xff);   /* CONCAT71(stk_127, loc_128) */
            FUN_004abe68(loc_118);
        } else {
            ln10 = *ux19;
            if (*(long *)(ln10 + 0x10) == 0) {
                /* WARNING: Does not return */
                CL4_SWBP(0x475bac);
            }
            v5 = *(uint *)(ln10 + 0x1c + *(long *)(ln10 + 0x10) * 4);
            sk_bcg_00476e74(ln10); v11 = 0; /* register-residue return */
            if (*(long *)(ln10 + 0x10) == 0) {
                /* WARNING: Does not return */
                CL4_SWBP(0x475bb0);
            }
            v1 = 0x10000000000000;
            if ((*(uint *)(ln10 + 0x1c + *(long *)(ln10 + 0x10) * 4) & 0x10000) != 0) {
                v1 = 0;
            }
            v2 = 0x20000000000000;
            if ((v11 & 1) == 0) {
                v2 = 0;
            }
            v11 = 0x40000000000000;
            if ((v5 & 0x40) != 0) {
                v11 = 0;
            }
            FUN_004aa4ac();
            FUN_00498b28(x16_2);
            FUN_00350518();
            FUN_00498c1c();
            FUN_004aa9c0(ux19[1]);
            *(unsigned long *)(x9_3 + 0x20) = v1 | (unsigned long)bv15 |
                 (unsigned long)((v5 & 4) >> 2) << 0x37 | v11 | v2 | 0xf00000000000000;
            ux19[1] = x8_3;    /* extraout_x8_03 */
        }
        if (ux21 != 0) {
            return;
        }
        break;
    case 4:
        v9 = FUN_0049e2f0(astk_430);
        FUN_00117cc4(&loc_248, v9, 0x60);
        v11 = FUN_004127b4();
        if ((v11 & 1) == 0) {
            if (loc_228 == '\0') {
                if ((loc_240 & 0xff) == 1) {
                    v9 = FUN_004ab49c(0xd000000000000010);
                    ln10 = -0x90;
                    FUN_004ab490(astk_a0, v9, x9_4 | 0x8000000000000000);  /* extraout_x9_04 */
                    thunk_FUN_0044f818();
                    v14 = FUN_004aa4e0();
                    v9 = x16_3;  /* extraout_x16_03 */
                    goto LAB_004758dc;
                }
                if (SBORROW8(loc_248, 1)) {
                    /* WARNING: Does not return */
                    CL4_SWBP(0x475ba0);
                }
                FUN_004ab568(loc_248 + -1);
                if (x9_6 == 0) {    /* extraout_x9_06 */
                    /* WARNING: Does not return */
                    CL4_SWBP(0x475bc8);
                }
                v9 = FUN_004ab55c().lo;
                sk_bcg_00476dd0(v9, (x8_4 & 0x10000) == 0);   /* extraout_x8_04 */
            } else {
                if (loc_228 == '\x01') {
                    FUN_004ac4b8();
                    FUN_003a25d4(loc_138[1]);
                    FUN_00086840(str_backreference_kind_5e2a10);
                    FUN_004ac06c();
                    FUN_004ab2b8();
                    FUN_00027724(x16_0);
                    FUN_004ac2dc();
                    (*x8_2)();
                    thunk_FUN_002acbb8();
                    FUN_003a25d4(x1_0);      /* extraout_x1_00 */
                    FUN_004ab49c(loc_d8, stk_d0);
                    ln10 = -0x68;
                    FUN_004ab490(&loc_78);
                    goto LAB_004758d4;
                }
                FUN_004ab568();
                if (x9_5 == 0) {    /* extraout_x9_05 */
                    /* WARNING: Does not return */
                    CL4_SWBP(0x475bb4);
                }
                av16 = FUN_004ab55c();
                sk_bcg_00476e18(av16.lo, av16.hi, (w8_1 >> 0x10 & 1) == 0);  /* extraout_w8_00 */
                if (ux21 == 0) {
                    ux21 = 0;
                }
            }
        } else {
            FUN_004ac4b8();
            FUN_003a25d4(loc_138[1]);
            FUN_00086840(str_backreference_kind_5e2a10);
            FUN_004ac06c();
            FUN_004ab2b8();
            FUN_00027724(x16);
            FUN_004ac2dc();
            (*x8)();
            thunk_FUN_002acbb8();
            FUN_003a25d4(x1);
            FUN_004ab49c(loc_d8, stk_d0);
            ln10 = -0xb8;
            FUN_004ab490(loc_c8);
LAB_004758d4:
            thunk_FUN_0044f818();
            v14 = FUN_004aa370();
            v9 = x16_1;          /* extraout_x16_01 */
LAB_004758dc:
            av16 = FUN_0036993c(v14, v9, 0, 0);
            pv13 = (word_t *)av16.hi;
            ux21 = av16.lo;
            v9 = *(word_t *)((char *)&loc_78 + ln10);
            pv13[1] = *(word_t *)((char *)&loc_78 + ln10 + 8);
            *pv13 = v9;
            v9 = *(word_t *)((char *)&loc_78 + ln10 + 0x10);
            pv13[3] = *(word_t *)((char *)&loc_78 + ln10 + 0x18);
            pv13[2] = v9;
            FUN_004abe68(*(word_t *)((char *)&loc_78 + ln10 + 0x20));
        }
joined_r0x00475844:
        if (ux21 != 0) {
LAB_00475910:
            *(word_t *)(ux19 + 0x1a) = 1;
            return;
        }
        break;
    case 5:
        FUN_0049e2f0(astk_430);
        pv13 = (word_t *)FUN_004ab568();
        if (x9_2 == 0) {            /* extraout_x9_02 */
            /* WARNING: Does not return */
            CL4_SWBP(0x475ba8);
        }
        v9 = FUN_004ab55c(*pv13).lo;
        sk_bcg_004765b0(v9, (x8_1 & 0x10000) == 0);   /* extraout_x8_01 */
        break;
    case 6:
        pv13 = (word_t *)FUN_0049e2f0(astk_430);
        stk_378 = pv13[1];
        loc_380 = *pv13;
        stk_368 = pv13[3];
        stk_370 = pv13[2];
        stk_358 = pv13[5];
        loc_360 = pv13[4];
        stk_348 = pv13[7];
        stk_350 = pv13[6];
        if ((*(byte *)(ux19 + 0x1a) & 1) == 0) {
            stk_288 = pv13[1];
            loc_290 = *pv13;
            stk_278 = pv13[3];
            stk_280 = pv13[2];
            stk_268 = pv13[5];
            loc_270 = pv13[4];
            stk_258 = pv13[7];
            stk_260 = pv13[6];
            sk_bcg_004766ec(&loc_290);
        }
        sk_bcg_004766ec(&loc_380);
        break;
    case 7:
        v9 = FUN_0049e2f0(astk_430);
        bv15 = 0;
        FUN_00117cc4(astk_340, v9);
        ln10 = sk_bcg_0047684c(*ux19);
        if (ux21 != 0) goto LAB_00475910;
        if (ln10 == 0) {
            loc_78 = 0;
            stk_70 = 0xe000000000000000;
            { wpair_t _w = sk_bcg_004769a4(); loc_138[0] = _w.lo; loc_138[1] = _w.hi; }   /* loc_138 = sk_bcg_004769a4() */
            v9 = loc_138[1];
            loc_128 = bv15 & 1;
            av16 = FUN_00002534(&LAB_00657e08, &DAT_005a4c10);
            FUN_000f4a9c(av16.lo, av16.hi, av16.lo);
            FUN_00205844(loc_138, &loc_78);
            FUN_003a25d4(v9);
            FUN_004ab49c(loc_78, stk_70);
            FUN_004ab490(&loc_458);
            thunk_FUN_0044f818();
            FUN_004aa370();
            FUN_004aaf9c();
            x1_2[1] = stk_450;   /* extraout_x1_02 */
            *x1_2 = loc_458;
            x1_2[3] = stk_440;
            x1_2[2] = loc_448;
            FUN_004abe68(loc_438);
            goto LAB_00475910;
        }
        v11 = FUN_00481a38(ln10);
        FUN_00350470();
        FUN_0031d5f0();
        v11 = v11 | 0xe00000000000000;
LAB_00475684:
        FUN_00498b28(FUN_00499158);
        FUN_00350518();
        FUN_00498c1c();
        FUN_004aa9c0(ux19[1]);
        *(unsigned long *)(x9 + 0x20) = v11;   /* exx9 */
        ux19[1] = x8_0;       /* extraout_x8_00 */
        break;
    case 8:
        sk_bcg_00475bf4();
        break;
    case 9:
        sk_bcg_00475c7c();
        break;
    case 10:
        sk_bcg_00475cf8();
        goto joined_r0x00475844;
    }
    iv6 = FUN_0049e2d4(astk_1e8);
    if (iv6 != 3 && iv6 != 6) {
        *(word_t *)(ux19 + 0x1a) = 1;
    }
}

/* FUN_00475bf4 @ 0x00475bf4   (est. sk_bcg_00475bf4)
 * Ghidra: void sk_bcg_00475bf4(void)
 * ByteCodeGen dot-matches-newline helper: if a node/flag descriptor is
 * present (exx9), reads a flag word and appends a kind-tagged
 * instruction (0x700000000010001 or 0x700000000010000 depending on the
 * 0x10000 flag) into the builder at ux20; else traps fail-closed.
 * Confidence: high   Notes: exx8/x9/x16 artifacts; trap 0x475c7c. */
static void sk_bcg_00475bf4(void)
{
    word_t v1;
    uint v2;
    code *pc3;
    long x8_0;             /* exx8 */
    word_t x8_1;           /* extraout_x8_00 */
    long x9;               /* exx9 */
    long x9_0;             /* extraout_x9_00 */
    word_t x16;            /* exx16 */
    long ux20;

    FUN_004abacc();
    if (x9 != 0) {
        v2 = *(uint *)(x8_0 + x9 * 4 + 0x1c);
        FUN_004aa3e4();
        FUN_00498b28(x16);
        FUN_004aab1c();
        FUN_00498c1c();
        FUN_004aabf4(*(word_t *)(ux20 + 8));
        v1 = 0x700000000010001;
        if ((v2 & 0x10000) != 0) {
            v1 = 0x700000000010000;
        }
        *(word_t *)(x9_0 + 0x20) = v1;
        *(word_t *)(ux20 + 8) = x8_1;
        return;
    }
    /* WARNING: Does not return */
    CL4_SWBP(0x475c7c);
}

/* FUN_00475c7c @ 0x00475c7c   (est. sk_bcg_00475c7c)
 * Ghidra: void sk_bcg_00475c7c(void)
 * ByteCodeGen assertion helper (sibling of sk_bcg_00475bf4): appends a
 * kind-tagged assertion instruction (0xd00000000000000 or 0xd00000000000001
 * depending on the 0x10000 flag) into the builder at ux20; traps if no
 * descriptor is present.
 * Confidence: high   Notes: extraout_* artifacts; trap 0x475cf8. */
static void sk_bcg_00475c7c(void)
{
    word_t v1;
    uint v2;
    code *pc3;
    long x8_0;             /* exx8 */
    word_t x8_1;           /* extraout_x8_00 */
    long x9;               /* exx9 */
    long x9_0;             /* extraout_x9_00 */
    word_t x16;            /* exx16 */
    long ux20;

    FUN_004abacc();
    if (x9 != 0) {
        v2 = *(uint *)(x8_0 + x9 * 4 + 0x1c);
        FUN_004aa3e4();
        FUN_00498b28(x16);
        FUN_004aab1c();
        FUN_00498c1c();
        FUN_004aabf4(*(word_t *)(ux20 + 8));
        v1 = 0xd00000000000000;
        if ((v2 & 0x10000) == 0) {
            v1 = 0xd00000000000001;
        }
        *(word_t *)(x9_0 + 0x20) = v1;
        *(word_t *)(ux20 + 8) = x8_1;
        return;
    }
    /* WARNING: Does not return */
    CL4_SWBP(0x475cf8);
}

/* FUN_00475cf8 @ 0x00475cf8   (est. sk_bcg_00475cf8)
 * Ghidra: void sk_bcg_00475cf8(void)
 * ByteCodeGen dispatch helper for the "isMatch/matches empty-flag" variant:
 * inspects two flag bits of a decoded element and routes to the assertion
 * (sk_bcg_00475c7c) or dot-matches-newline (sk_bcg_00475bf4) emitter, or
 * builds a two-part expression node (via FUN_0036a9a0 + two
 * FUN_00466104-built subnodes) stored into a fresh builder record; traps if
 * no descriptor is present.
 * Confidence: medium   Notes: exw8/x9 artifacts; DAT_004c2450 pair;
 * trap 0x475e14. */
static void sk_bcg_00475cf8(void)
{
    code *pc1;
    word_t v2;
    long ln3;
    unsigned long v4;
    uint w8;               /* exw8 */
    long x9;               /* exx9 */
    word_t astk_1d0[6]; /* astk_1d0 [48] */
    word_t loc_1a0[22];  /* loc_1a0 [176] */
    word_t astk_f0[22]; /* astk_f0 [176] */

    FUN_004abacc();
    if (x9 != 0) {
        FUN_004ab55c();
        if ((w8 >> 4 & 1) == 0) {
            sk_bcg_00475c7c();
        } else if ((w8 >> 9 & 1) == 0) {
            sk_bcg_00475bf4();
        } else {
            FUN_004aa6c4();
            v2 = FUN_00002534().lo;
            ln3 = FUN_0036a9a0(v2, astk_1d0);
            v2 = _DAT_004c2450;
            *(word_t *)(ln3 + 0x18) = uRam00000000004c2458;   /* DAT_004c2458 */
            *(word_t *)(ln3 + 0x10) = v2;                  /* DAT_004c2450 */
            FUN_00466104(0x686228);
            v4 = FUN_0036a940();
            loc_1a0[0] = 4;
            FUN_0049ca2c(loc_1a0);
            FUN_00117cc4(v4 + 0x10, loc_1a0, 0xb0);
            *(unsigned long *)(ln3 + 0x20) = v4 | 0x4000000000000000;
            FUN_00466104(0x686228);
            v4 = FUN_0036a940();
            FUN_004a3950(astk_f0);
            FUN_00117cc4(v4 + 0x10, astk_f0, 0xb0);
            *(unsigned long *)(ln3 + 0x28) = v4 | 0x4000000000000000;
            FUN_003509bc();
            sk_bcg_00476fd0(0,0,0,0); /* register-residue args */
            FUN_0036b588(ln3);
            FUN_004985e0();
            FUN_00002834();
            FUN_0036b6ac();
        }
        return;
    }
    /* WARNING: Does not return */
    CL4_SWBP(0x475e14);
}

/* ==================== SKR27 function bodies ==================== */


/* FUN_00475e14 @ 0x475e14   (est. sk_bcg_00475e14)
 * Ghidra: void sk_bcg_00475e14(void)
 * Emits a run of compiled bytecode instructions for a regex alternative:
 * walks a UTF-8/UTF-16 input-range iterator (a "grapheme/range cursor"
 * identified by unaff_x20, an emitter context) and appends one encoded
 * instruction word per visited code point/byte into the growing instruction
 * buffer at unaff_x20[1]. Handles the scalar-byte path and the
 * sign-extended/prefix-byte paths (0x8/0x9 prefix selector cases), folding in
 * length/locality flags (0x900000000000000 / 0x980000000000000) and flushing
 * via SoftwareBreakpoint(1,0x4764c8) when the emission table is empty.
 * Confidence: medium   Notes: unaff_x20/x30/in_x3 register inputs, masked
 * indirect-trampoline calls (0x47abbb8 buffer grow, 0x3a261c object validate),
 * many SoftwareBreakpoint fail-closed checks (0x4764b8..0x4764d8). */
static void sk_bcg_00475e14(void)
{
    word_t uVar1, uVar2, uVar7, uVar8, uVar9, uVar12, uVar20, uVar21, uVar22, uVar23;
    word_t uVar11, uVar16;
    word_t lVar6, lVar19, lVar24;
    uint  uVar13, uVar14, uVar15, uVar18;
    byte  bVar4;
    long  lVar7_16;
    word_t unaff_x20, unaff_x30;            /* register inputs */
    word_t extraout_w8, extraout_w9, extraout_x16;
    word_t uVar3;
    long *ctx = (long *)unaff_x20;          /* emitter context (unaff_x20) */
    word_t *cursor;                        /* plVar17 */
    wpair_t auVar25, auVar26;
    ulong uVar3;

    auVar25 = (wpair_t)FUN_0035638c();
    uVar11 = auVar25.hi;
    uVar16 = auVar25.lo;
    lVar19 = *ctx;
    if (*(long *)(lVar19 + 0x10) == 0) {
        /* WARNING: Does not return */
        CL4_SWBP(0x4764c8);          /* empty emission table -> fail closed */
    }
    uVar13 = *(uint *)(lVar19 + 0x1c + *(long *)(lVar19 + 0x10) * 4);
    uVar22 = uVar11 >> 0x38 & 0xf;
    if ((uVar13 >> 0x10 & 1) == 0) {
        uVar20 = uVar16 & 0xffffffffffff;
        if ((uVar11 & 0x2000000000000000) != 0) {
            uVar20 = uVar22;
        }
        if (uVar20 != 0) {
            lVar24 = 0;
            cursor = (long *)ctx;
            do {
                if ((uVar11 >> 0x3c & 1) != 0) {
                    FUN_00350878(lVar24 << 0x10);
                    auVar25 = (wpair_t)FUN_002a49a8();
                    goto LAB_00475ef8;
                }
                uVar13 = (uint)cursor;
                if ((uVar11 >> 0x3d & 1) == 0) {
                    lVar6 = (uVar11 & 0xfffffffffffffff) + 0x20;
                    if ((uVar16 >> 0x3c & 1) == 0) {
                        FUN_003507e0();
                        lVar6 = FUN_002a9ba8();
                    }
                    FUN_004abbb8(lVar6 + lVar24);   /* masked buffer-grow/trampoline fn */
                    if (-1 < extraout_w9) goto switchD_00475ec0_caseD_0;
                    FUN_003527b8();
                    switch (extraout_x16) {
                    default: goto switchD_00475ec0_caseD_0;
                    case 1:
switchD_00475ec0_caseD_1:
                        FUN_00353ff4();
                        auVar25 = (wpair_t){0};      /* low 32 bits rebuilt */
                        auVar25.lo = (extraout_w8 & 0xfffff800) | (extraout_w8 & 0x3f)
                                   | (uVar13 & 0x1f) << 6;
                        auVar25.hi = 2;
                        break;
                    case 2:
switchD_00475ec0_caseD_2:
                        FUN_00352e9c();
                        auVar25 = (wpair_t){0};
                        auVar25.lo = (uVar13 & 0xf) << 0xc | (extraout_w9_01 & 0x3f) << 6
                                   | extraout_w8_00 & 0x3f;
                        auVar25.hi = 3;
                        break;
                    case 3:
switchD_00475ec0_caseD_3:
                        FUN_0034c6d4();
                        FUN_004abfc8();
                        auVar25 = (wpair_t){0};
                        auVar25.lo = uVar13 & 0xffffffc0 | extraout_w8_01 & 0x3f;
                        auVar25.hi = 4;
                    }
                }
                else {
                    in_stack_00000060 = uVar16;
                    in_stack_00000068 = uVar11 & 0xffffffffffffff;
                    FUN_004abbb8((long)&stack0x00000060 + lVar24);   /* buffer grow */
                    if (extraout_w9_00 < 0) {
                        FUN_003527b8();
                        switch (extraout_x16_00) {
                        case 1: goto switchD_00475ec0_caseD_1;
                        case 2: goto switchD_00475ec0_caseD_2;
                        case 3: goto switchD_00475ec0_caseD_3;
                        }
                    }
switchD_00475ec0_caseD_0:
                    auVar25.hi = 1;
                    auVar25.lo = (word_t)cursor;
                }
LAB_00475ef8:
                if (*(long *)(lVar19 + 0x10) == 0) {
                    /* WARNING: Does not return */
                    CL4_SWBP(0x4760e0);
                }
                if ((*(uint *)(lVar19 + 0x1c + *(long *)(lVar19 + 0x10) * 4) & 1) == 0) {
                    lVar6 = ctx[1];
LAB_00475f4c:
                    uVar22 = FUN_003a261c(lVar6);       /* validate emit buffer */
                    if ((uVar22 & 1) == 0) {
                        FUN_0006b3f4(*(u64 *)(lVar6 + 0x10));
                        lVar6 = FUN_00499158();
                    }
                    uVar22 = 0x900000000000000;
                }
                else {
                    uVar22 = FUN_002bc2f8(auVar25.lo);
                    lVar6 = ctx[1];
                    if ((uVar22 & 1) == 0) goto LAB_00475f4c;
                    uVar22 = FUN_003a261c(lVar6);
                    if ((uVar22 & 1) == 0) {
                        FUN_0006b3f4(*(u64 *)(lVar6 + 0x10));
                        lVar6 = FUN_00499158();
                    }
                    uVar22 = 0x980000000000000;
                }
                uVar7 = *(word_t *)(lVar6 + 0x10);
                cursor = (long *)(uVar7 + 1);
                if (*(word_t *)(lVar6 + 0x18) >> 1 <= uVar7) {
                    FUN_000ec004();
                    lVar6 = FUN_00499158();
                }
                *(long **)(lVar6 + 0x10) = cursor;
                *(word_t *)(lVar6 + uVar7 * 8 + 0x20) = auVar25.lo & 0xffffffff | uVar22;
                ctx[1] = lVar6;
                lVar24 = auVar25.hi + lVar24;
            } while (lVar24 < (long)uVar20);
        }
        goto LAB_004760c8;
    }
    uVar20 = unaff_x30;
    if ((uVar13 & 1) == 0) {
LAB_00476064:
        if ((*(byte *)(ctx + 0x1b) & 1) == 0) {
            FUN_003507e0();
            FUN_002bd8f0();
            FUN_00466214();
            if (!(bool)in_ZR) {
                FUN_003507e0();
                sk_bcg_00476cd4(0, 0); /* register-residue args */
                if ((uVar20 ^ in_x3) >> 0xe == 0) {
                    FUN_003a25d4(extraout_x1);
                    /* WARNING: Does not return */
                    CL4_SWBP(0x4764d4);
                }
                FUN_004abaac();
                uVar7 = FUN_004a3a94();
                FUN_003a25d4(extraout_x1);
                FUN_003507e0();
                auVar26 = (wpair_t)sk_bcg_00476cd4(0, 0); /* register-residue args */
                uVar12 = auVar26.hi;
                uVar8 = auVar26.lo;
                uVar21 = uVar20 >> 0xe;
                if (uVar21 != in_x3 >> 0xe) {
                    uVar13 = auVar26._4_4_ >> 0x1b & 1;   /* auVar26.lo bit 0x1b */
                    if ((uVar12 & 0x1000000000000000) == 0) {
                        uVar13 = 1;
                    }
                    uVar1 = uVar8 & 0xffffffffffff;
                    if ((uVar12 & 0x2000000000000000) != 0) {
                        uVar1 = uVar12 >> 0x38 & 0xf;
                    }
                    uVar14 = auVar25.lo >> 0x1b & 1;
                    if ((uVar11 & 0x1000000000000000) == 0) {
                        uVar14 = 1;
                    }
                    uVar2 = uVar16 & 0xffffffffffff;
                    if ((uVar11 & 0x2000000000000000) != 0) {
                        uVar2 = uVar22;
                    }
                    do {
                        uVar23 = uVar20 & 0xc;
                        uVar22 = uVar20;
                        if (uVar23 == 4L << uVar13 || (uVar20 & 1) == 0) {
                            if (uVar23 == 4L << uVar13) {
                                uVar22 = FUN_0001da84(uVar20, uVar8, uVar12);
                            }
                            if (uVar1 <= uVar22 >> 0x10) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x4764b8);
                            }
                            if ((uVar22 & 1) == 0) {
                                uVar9 = FUN_001676cc(uVar22, uVar8, uVar12);
                                uVar22 = uVar22 & 0xc | uVar9 & 0xfffffffffffffff3 | 1;
                            }
                        }
                        else if (uVar1 <= uVar20 >> 0x10) {
                            /* WARNING: Does not return */
                            CL4_SWBP(0x4764bc);
                        }
                        if ((uVar12 >> 0x3c & 1) == 0) {
                            uVar22 = uVar22 >> 0x10;
                            if ((uVar12 >> 0x3d & 1) == 0) {
                                lVar19 = (uVar12 & 0xfffffffffffffff) + 0x20;
                                if ((uVar8 >> 0x3c & 1) == 0) {
                                    lVar19 = FUN_002a9ba8(uVar8, uVar12);
                                }
                                uVar3 = *(byte *)(lVar19 + uVar22);
                            }
                            else {
                                in_stack_00000060 = uVar8;
                                in_stack_00000068 = uVar12 & 0xffffffffffffff;
                                uVar3 = *(byte *)((long)&stack0x00000060 + uVar22);
                            }
                            FUN_0034b3f8(uVar3);
                            uVar22 = (uVar22 + extraout_x8_00) * 0x10000 | 5;
                        }
                        else {
                            uVar22 = FUN_002a49a8(uVar22, uVar8, uVar12).lo;
                        }
                        if ((uVar23 != 4L << uVar14) && ((uVar20 & 1) != 0)) {
                            uVar23 = uVar20 >> 0x10;
                            if (uVar2 <= uVar23) {
                                /* WARNING: Does not return */
                                CL4_SWBP(0x4764c0);
                            }
LAB_004762d4:
                            if ((uVar11 >> 0x3c & 1) == 0) goto LAB_004762d8;
LAB_004763d0:
                            uVar20 = FUN_002a49a8(uVar20 & 0xffffffffffff0000, uVar16, uVar11).lo;
                            goto switchD_0047632c_caseD_0;
                        }
                        if (uVar23 == 4L << uVar14) {
                            uVar20 = FUN_0001da84(uVar20, uVar16, uVar11);
                        }
                        uVar23 = uVar20 >> 0x10;
                        if (uVar2 <= uVar23) {
                            /* WARNING: Does not return */
                            CL4_SWBP(0x4764c4);
                        }
                        if ((uVar20 & 1) != 0) goto LAB_004762d4;
                        uVar20 = FUN_001676cc(uVar20, uVar16, uVar11);
                        uVar23 = uVar20 >> 0x10;
                        if ((uVar11 >> 0x3c & 1) != 0) goto LAB_004763d0;
LAB_004762d8:
                        if ((uVar11 >> 0x3d & 1) != 0) {
                            in_stack_00000060 = uVar16;
                            in_stack_00000068 = uVar11 & 0xffffffffffffff;
                            bVar4 = *(byte *)((long)&stack0x00000060 + uVar23);
                            uVar20 = (word_t)bVar4;
                            uVar18 = (uint)bVar4;
                            if ((char)bVar4 < '\0') {
                                FUN_00352af0();
                                switch (extraout_x16_03) {
                                case 1: goto switchD_0047632c_caseD_1;
                                case 2: goto switchD_0047632c_caseD_2;
                                case 3: goto switchD_0047632c_caseD_3;
                                }
                            }
                            goto switchD_0047632c_caseD_0;
                        }
                        lVar19 = (uVar11 & 0xfffffffffffffff) + 0x20;
                        if ((uVar16 >> 0x3c & 1) == 0) {
                            lVar19 = FUN_002a9ba8(uVar16, uVar11);
                        }
                        bVar4 = *(byte *)(lVar19 + uVar23);
                        uVar20 = (word_t)bVar4;
                        uVar18 = (uint)bVar4;
                        if (-1 < (char)bVar4) goto switchD_0047632c_caseD_0;
                        FUN_00352af0();
                        switch (extraout_x16_02) {
                        case 1:
switchD_0047632c_caseD_1:
                            FUN_00353ff4();
                            uVar20 = (word_t)(extraout_w8_02 & 0xfffff800
                                    | extraout_w8_02 & 0x3f | (uVar18 & 0x1f) << 6);
                            break;
                        case 2:
switchD_0047632c_caseD_2:
                            FUN_00352e9c();
                            uVar18 = (uVar18 & 0xf) << 0xc | (extraout_w9_02 & 0x3f) << 6;
                            uVar15 = extraout_w8_03;
                            goto LAB_004763ac;
                        case 3:
switchD_0047632c_caseD_3:
                            FUN_0034c6d4();
                            uVar18 = (uVar18 & 0xf) << 0x12 | (extraout_w9_03 & 0x3f) << 0xc
                                   | (extraout_w10 & 0x3f) << 6;
                            uVar15 = extraout_w8_04;
LAB_004763ac:
                            uVar20 = (word_t)(uVar18 | uVar15 & 0x3f);
                        }
switchD_0047632c_caseD_0:
                        uVar23 = 0x940000000000000;
                        if (uVar21 != uVar7 >> 0xe) {
                            uVar23 = 0x900000000000000;
                        }
                        lVar19 = ctx[1];
                        uVar21 = FUN_003a261c(lVar19);   /* validate emit buffer */
                        if ((uVar21 & 1) == 0) {
                            FUN_0006b3f4(*(u64 *)(lVar19 + 0x10));
                            lVar19 = FUN_00499158();
                        }
                        uVar21 = *(word_t *)(lVar19 + 0x10);
                        if (*(word_t *)(lVar19 + 0x18) >> 1 <= uVar21) {
                            uVar10 = FUN_0006b42c();
                            lVar19 = FUN_00499158(uVar10, uVar21 + 1, 1, lVar19);
                        }
                        *(word_t *)(lVar19 + 0x10) = uVar21 + 1;
                        *(word_t *)(lVar19 + uVar21 * 8 + 0x20) = uVar23 | uVar20 & 0xffffffff;
                        ctx[1] = lVar19;
                        uVar21 = uVar22 >> 0xe;
                        uVar20 = uVar22;
                    } while (uVar21 != in_x3 >> 0xe);
                }
                FUN_00356370(uVar12, unaff_x30);
                FUN_003a25d4();
                return;
            }
        }
        FUN_003507e0();
        lVar19 = FUN_00481780();
        uVar16 = lVar19 << 0x10 | 0x800000000000000;
    }
    else {
        FUN_003507e0();
        uVar7 = FUN_002bde1c();
        if ((uVar7 & 1) == 0) goto LAB_00476064;
        if ((*(byte *)(ctx + 0x1b) & 1) == 0) {
            FUN_003507e0();
            FUN_002bd8f0();
            FUN_00466214();
            if ((bool)in_ZR) goto LAB_00476048;
            FUN_003507e0();
            FUN_001b36ec();
            uVar16 = FUN_0034ecc8();
            if ((bool)in_ZR) {
                /* WARNING: Does not return */
                CL4_SWBP(0x4764d8);
            }
            uVar16 = uVar16 & 0xffffffff | 0x9c0000000000000;
        }
        else {
LAB_00476048:
            FUN_003507e0();
            lVar19 = FUN_00481780();
            uVar16 = lVar19 << 0x10 | 0x800000000000001;
        }
    }
    FUN_004aa3e4();
    FUN_00498b28(extraout_x16_01);
    FUN_00100efc();
    FUN_00498c1c();
    FUN_004aabf4(ctx[1]);
    *(word_t *)(extraout_x9 + 0x20) = uVar16;
    ctx[1] = extraout_x8;
LAB_004760c8:
    FUN_00356370(unaff_x30);
    return;
}

/* FUN_00476518 @ 0x476518   (est. sk_bcg_00476518)
 * Ghidra: void sk_bcg_00476518(void)
 * Emits a single literal/matched-width instruction for the current regex
 * position: computes the next position token (unaff_x20+8 is the emit-buffer
 * slot), folds the matched-width flag (0x900000000000000 vs 0x980000000000000
 * depending on 0x2bc2f8's classification of the token), and appends the
 * packed word (low 32 bits of token | flag) to the buffer. Fail-closed via
 * SoftwareBreakpoint(1,0x4765b0) if no further position is available.
 * Confidence: medium   Notes: unaff_x20 context pointer, register
 * extraout_x8/x9/x16 artifacts. */
static void sk_bcg_00476518(void)
{
    word_t uVar2, uVar3;
    long ctx = unaff_x20;               /* emitter context (unaff_x20) */

    uVar2 = FUN_004abacc();
    if (extraout_x9 != 0) {
        FUN_004ab55c();
        if (((extraout_x8 & 1) == 0) || (uVar3 = FUN_002bc2f8(uVar2), (uVar3 & 1) == 0)) {
            uVar3 = 0x900000000000000;
        }
        else {
            uVar3 = 0x980000000000000;
        }
        FUN_004aa3e4();
        FUN_00498b28(extraout_x16);
        FUN_004aab1c();
        FUN_00498c1c();
        FUN_004aabf4(*(u64 *)(ctx + 8));
        *(word_t *)(extraout_x9_00 + 0x20) = uVar2 & 0xffffffff | uVar3;
        *(u64 *)(ctx + 8) = extraout_x8_00;
        return;
    }
    /* WARNING: Does not return */
    CL4_SWBP(0x4765b0);
}

/* FUN_004765b0 @ 0x4765b0   (est. sk_bcg_004765b0)
 * Ghidra: void sk_bcg_004765b0(void)
 * Prepares/commits an instruction-emission slot: resets the tail counter
 * (0x476dd0(0)), reads the emitter table depth at *ctx+0x10, classifies the
 * current code-point token (0x3a261c validate, 0x499f0c token unpack), and
 * grows the emission string/buffer via 0x258c60 with a length bound,
 * fail-closing on carry (SoftwareBreakpoint(1,0x4766dc)) and aborting
 * (0x2591b4, noreturn) if the token's continuation flag toggles. When the
 * committed flag (hi bit) is clear it emits a marker through 0x510b8/0x499fcc,
 * then pushes the new run pointer into the per-token slot chain at
 * *(ctx+0x38)[token]*8.
 * Confidence: medium   Notes: DAT_00657e10/0x5a4c18/0x657778 globals,
 * 0x2591b4 is a noreturn abort. */
static void sk_bcg_004765b0(void)
{
    long *plVar1;
    word_t uVar3, uVar4, uVar5;
    long lVar6, lVar7, lVar9, lVar10;
    long *ctx = unaff_x20;              /* emitter context (unaff_x20) */
    wpair_t auVar11, auVar12;

    uVar3 = FUN_00354744();
    sk_bcg_00476dd0(0);
    lVar10 = *(long *)(*ctx + 0x10);
    uVar4 = FUN_003a261c(ctx[0x17]);
    lVar9 = ctx[0x17];
    auVar11 = (wpair_t)FUN_00499f0c(uVar3);
    lVar7 = auVar11.lo;
    lVar6 = *(long *)(lVar9 + 0x10);
    uVar8 = (word_t)~auVar11.hi_lo & 1;   /* auVar11._8_4_ low bit, negated */
    if (SCARRY8(lVar6, uVar8)) {
        /* WARNING: Does not return */
        CL4_SWBP(0x4766dc);
    }
    uVar5 = FUN_00002534(&DAT_00657e10, &DAT_005a4c18).lo;   /* globals 0x657e10, 0x5a4c18 */
    auVar12 = (wpair_t)FUN_00258c60(uVar4, lVar6 + uVar8, uVar5);
    if ((auVar12.lo & 1) != 0) {
        auVar12 = (wpair_t)FUN_00499f0c(uVar3);
        lVar7 = auVar12.lo;
        if ((auVar11.hi_lo & 1) != (auVar12.hi_lo & 1)) {
            /* WARNING: Subroutine does not return */
            FUN_002591b4(0x686a38);
        }
    }
    ctx[0x17] = lVar9;
    if ((auVar11.hi & 1) == 0) {
        FUN_003510b8(auVar12.lo, auVar12.hi, &DAT_00657778);   /* global 0x657778 */
        FUN_00499fcc();
    }
    plVar1 = (long *)(*(long *)(lVar9 + 0x38) + lVar7 * 8);
    FUN_00498b28((word_t)FUN_0049938c);
    FUN_004aaf58();
    lVar7 = *plVar1;
    *(long *)(lVar7 + 0x10) = (long)ctx + 1;
    *(long *)(lVar7 + (long)ctx * 8 + 0x20) = lVar10 + -1;
    *plVar1 = lVar7;
    FUN_003544c8(unaff_x30);
    return;
}

/* FUN_004766ec @ 0x4766ec   (est. sk_bcg_004766ec)
 * Ghidra: void sk_bcg_004766ec(long param_1)
 * Merges character-set (character-class) membership flags into the current
 * instruction word at *ctx+0x1c+count*4. param_1 holds the class descriptor
 * (two sub-tables at +0x18 and +0x38, each with a count at +0x10 and a run of
 * 0x18-byte entries). For the first (+0x18) table it ORs one-hot bit masks
 * (indexed via global table DAT_005a5e3c) into the word, preserving the
 * upper flag lanes; for the second (+0x38) table it ANDs/clears the mask
 * bits and, when the word's flag bits (0x80020) overlap with a cleared lane,
 * folds the mask (optionally complementing) into the accumulated value.
 * Fail-closes on an out-of-range count (SoftwareBreakpoint 0x476848/0x47684c).
 * Confidence: medium   Notes: DAT_005a5e3c per-code-point bit-table. */
static void sk_bcg_004766ec(long param_1)
{
    long lVar1, lVar7, lVar10;
    uint uVar2, uVar3, uVar4, uVar9;
    byte *pbVar8;
    long *ctx = unaff_x20;              /* emitter context (unaff_x20) */
    word_t uVar6, uVar11;

    lVar10 = *ctx;
    uVar11 = *(word_t *)(lVar10 + 0x10);
    uVar6 = FUN_003a261c(lVar10);
    if ((uVar6 & 1) == 0) {
        lVar10 = FUN_0049a4b8(lVar10);
    }
    if (uVar11 != 0) {
        if (uVar11 <= *(word_t *)(lVar10 + 0x10)) {
            lVar1 = lVar10 + 0x1c;
            if (*(char *)(param_1 + 0x10) != '\x01') {
                *(uint *)(lVar1 + uVar11 * 4) = 0x14040;
            }
            lVar7 = *(long *)(*(long *)(param_1 + 0x18) + 0x10);
            if (lVar7 != 0) {
                uVar9 = *(uint *)(lVar1 + uVar11 * 4);
                pbVar8 = (byte *)(*(long *)(param_1 + 0x18) + 0x20);
                do {
                    uVar4 = 1 << (ulong)(*(uint *)(&DAT_005a5e3c + (ulong)*pbVar8 * 4) & 0x1f);
                    uVar3 = uVar9 & 0xfff8ffff;
                    if ((uVar4 & 0x7ff8ffff) != 0) {
                        uVar3 = uVar9;
                    }
                    uVar2 = uVar3 & 0xffff3fff;
                    if ((uVar4 & 0x7fff3fff) != 0) {
                        uVar2 = uVar3;
                    }
                    uVar9 = uVar2 & 0xfff7ffdf;
                    if ((uVar4 & 0x7ff7ffdf) != 0) {
                        uVar9 = uVar2;
                    }
                    uVar9 = uVar9 | uVar4;
                    lVar7 = lVar7 + -1;
                    pbVar8 = pbVar8 + 0x18;
                } while (lVar7 != 0);
                *(uint *)(lVar1 + uVar11 * 4) = uVar9;
            }
            lVar7 = *(long *)(*(long *)(param_1 + 0x38) + 0x10);
            if (lVar7 != 0) {
                uVar9 = *(uint *)(lVar1 + uVar11 * 4);
                pbVar8 = (byte *)(*(long *)(param_1 + 0x38) + 0x20);
                do {
                    uVar4 = 1 << (ulong)(*(uint *)(&DAT_005a5e3c + (ulong)*pbVar8 * 4) & 0x1f);
                    uVar3 = uVar9 & 0xfff7ffdf;
                    if ((uVar4 & 0x7ff7ffdf) != 0) {
                        uVar3 = uVar9;
                    }
                    if (((uVar9 & 0x80020) != 0 && (uVar4 & 0x7ff7ffdf) == 0)
                        || (uVar3 & uVar4) != 0) {
                        uVar9 = 0xffffffff;
                        if ((uVar3 & uVar4) != 0) {
                            uVar9 = ~uVar4;
                        }
                        uVar9 = uVar9 & uVar3;
                        *(uint *)(lVar1 + uVar11 * 4) = uVar9;
                    }
                    lVar7 = lVar7 + -1;
                    pbVar8 = pbVar8 + 0x18;
                } while (lVar7 != 0);
            }
            *ctx = lVar10;
            return;
        }
        /* WARNING: Does not return */
        CL4_SWBP(0x47684c);
    }
    /* WARNING: Does not return */
    CL4_SWBP(0x476848);
}

/* FUN_0047684c @ 0x47684c   (est. sk_bcg_0047684c)
 * Ghidra: void sk_bcg_0047684c(undefined8 param_1)
 * Dispatches a compiler "handled-here" directive: builds a small context
 * frame (0x117cc4) and switches on the AST-node kind returned by
 * 0x458af8. Kinds 0xe/0xf/0x10 (plus the default) log the
 * "Handled in ByteCodeGen or earlier" string (0x5e2e20) and abort
 * (0x1afa84, noreturn); kinds 2,5,6,7,9,0xa-0xd are forwarded to
 * 0x19858; kind 3 goes to the 0xac9f8/0x47dfc4 pair; kind 8 computes a
 * wpair via 0xe0654 and forwards both halves plus param_1 to 0x47dee8;
 * kind 0x11 is a no-op.
 * Confidence: medium   Notes: string s_Handled_in_ByteCodeGen_or_earlie_005e2e20
 * at 0x5e2e20; 0x1afa84 is a noreturn abort. */
static void sk_bcg_0047684c(u64 param_1)
{
    uint uVar1;
    u64 uVar2;
    wpair_t auVar3;

    FUN_00117cc4(stack_d0);                     /* build directive context frame */
    uVar1 = FUN_00458af8(stack_d0);
    uVar2 = 0;
    switch (uVar1) {
    default:
        uVar2 = FUN_00458b14(stack_d0, 0);
    case 0xe:
    case 0xf:
    case 0x10:
        FUN_00002874(s_Handled_in_ByteCodeGen_or_earlie_005e2e20, uVar2); /* 0x5e2e20 */
        FUN_003593c0();
        FUN_00002818();
        /* WARNING: Subroutine does not return */
        FUN_001afa84();
    case 2:
    case 5:
    case 6:
    case 7:
    case 9:
    case 0xa:
    case 0xb:
    case 0xc:
    case 0xd:
        FUN_00458b14(stack_d0, 0);
        FUN_00019858();
        break;
    case 3:
        FUN_00458b14(stack_d0, 0);
        FUN_004ac9f8();
        FUN_0047dfc4();
        break;
    case 8:
        FUN_00458b14(stack_d0, 0);
        auVar3 = (wpair_t)FUN_000e0654();
        FUN_0047dee8(auVar3.lo, auVar3.hi, param_1);
        break;
    case 0x11:
        break;
    }
    return;
}

/* FUN_004769a4 @ 0x4769a4   (est. sk_bcg_004769a4)
 * Ghidra: long sk_bcg_004769a4(void)
 * Emits the bytecode for a regex zero-width assertion/anchor: switches on the
 * assertion kind from 0x48ee9c and calls the anchor-emitter 0x4aa8f0 with the
 * matching named-string label (e.g. "Anchor_endOfSubjectBeforeNewline" at
 * 0x5e2b00, "Anchor_startOfLine" at 0x5e2bd0, "Anchor_endOfLine" at 0x5e2bb0,
 * "Anchor_firstMatchingPositionInSu..." at 0x5e2a80, "TODO: Assertion
 * resetStartOfMatch" at 0x5e2a50). Kinds 0xd (plus 2/0xb) build an AST frame
 * (0x4ab618/0x117cc4) and re-dispatch on the resolved kind (0x58af8), with
 * lookaround-width selection via 0xac2a0 and final fallback to 0x48ef24 /
 * 0x48d694.
 * Confidence: medium   Notes: string labels recorded; several 0x4aa8f0 calls
 * take default (() ) arguments with extraout_x8 lane offsets. */
static word_t sk_bcg_004769a4(void)
{
    uint uVar1;
    int iVar3;
    word_t lVar4;
    wpair_t auVar5;

    uVar1 = FUN_0048ee9c();
    lVar4 = 0x2f5e2f;
    switch (uVar1) {
    default:
        FUN_004abf10();
        FUN_004aa8f0();
        lVar4 = extraout_x8 + 2;
        break;
    case 1:
        FUN_004aa8f0(s_Anchor_endOfSubjectBeforeNewline_005e2b00, 0x2f5e2f,
                     0xe300000000000000, 0);   /* 0x5e2b00 */
        lVar4 = extraout_x8_03 + 0xd;
        break;
    case 2:
        lVar4 = FUN_004ab858();
        break;
    case 3:
        FUN_004aa8f0(s_TODO__Assertion_resetStartOfMatc_005e2a50, 0x2f5e2f,
                     0xe300000000000000, 0);   /* 0x5e2a50 */
        lVar4 = extraout_x8_00 + 0xe;
        break;
    case 4:
        FUN_004aa8f0(s_Anchor_firstMatchingPositionInSu_005e2a80, 0x2f5e2f,
                     0xe300000000000000, 0);   /* 0x5e2a80 */
        lVar4 = extraout_x8_05 + 0x12;
        break;
    case 5:
        FUN_004abf40();
        FUN_004aa8f0();
        lVar4 = extraout_x8_06 + 7;
        break;
    case 6:
        FUN_004abf20();
        FUN_004aa8f0();
        lVar4 = extraout_x8_04 + 0x10;
        break;
    case 7:
        FUN_004aa8f0(s_Anchor_startOfLine_005e2bd0, 0x2f5e2f,
                     0xe300000000000000, 0);   /* 0x5e2bd0 */
        lVar4 = extraout_x8_07 + -1;
        break;
    case 8:
        FUN_004aa8f0(s_Anchor_endOfLine_005e2bb0, 0x2f5e2f,
                     0xe300000000000000, 0);   /* 0x5e2bb0 */
        lVar4 = extraout_x8_02 + -3;
        break;
    case 9:
        break;
    case 10:
        lVar4 = 0x2f242f;
        break;
    case 0xb:
        lVar4 = FUN_004ab858();
        break;
    case 0xc:
        FUN_004abf30();
        FUN_004aa8f0();
        lVar4 = extraout_x8_01 + 9;
        break;
    case 0xd:
        auVar5 = (wpair_t)FUN_004ab618(0x2f5e2f, 0xe300000000000000, 0);
        FUN_00117cc4(auVar5.lo, auVar5.hi, 0x99);
        iVar3 = FUN_00458af8(stack_b0);
        if ((uint)(iVar3 - 5) < 4) {
            FUN_00458b14(stack_b0);
            goto switchD_00476b58_caseD_2;
        }
        if (iVar3 == 3) {
            FUN_00458b14(stack_b0);
            FUN_004ac2a0();
            if ((uint)extraout_x16 < 0xc) {
                uVar1 = (uint)extraout_x8_08 & 0xff;
                switch (extraout_x16) {
                default:
                    if (uVar1 != 0x12) goto switchD_00476b58_caseD_2;
                    break;
                case 1:
                    if (uVar1 != 0x3c) goto switchD_00476b58_caseD_2;
                    break;
                case 2:
                case 3:
switchD_00476b58_caseD_2:
                    lVar4 = FUN_0048d694();
                    return lVar4;
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                    break;
                case 0xb:
                    if (((uint)extraout_x8_08 & 0xfe) != 4) goto switchD_00476b58_caseD_2;
                }
            }
            else if ((((uint)extraout_x16 == 0xf) && (extraout_x8_08 == 2))
                     && (FUN_004ab1a0(), extraout_x8_09 == 0)) {
                goto switchD_00476b58_caseD_2;
            }
        }
        lVar4 = FUN_0048ef24();
    }
    return lVar4;
}

/* FUN_00476c0c @ 0x476c0c   (est. sk_bcg_00476c0c)
 * Ghidra: uint sk_bcg_00476c0c(long param_1)
 * Returns the "is a run of one or more character classes" flag for the
 * instruction at index count (param_1+0x10) of the emission table
 * (param_1+0x1c+count*4): the value is bit 0x10 (>>0x10 & 1) of the stored
 * instruction word. Fail-closes (SoftwareBreakpoint(1,0x476c28)) when the
 * count is zero.
 * Confidence: high   Notes: trivial flag extractor. */
static uint sk_bcg_00476c0c(long param_1)
{
    if (*(long *)(param_1 + 0x10) != 0) {
        return *(uint *)(param_1 + *(long *)(param_1 + 0x10) * 4 + 0x1c) >> 0x10 & 1;
    }
    /* WARNING: Does not return */
    CL4_SWBP(0x476c28);
}

/* FUN_00476c28 @ 0x476c28   (est. sk_bcg_00476c28)
 * Ghidra: void sk_bcg_00476c28(byte *param_1, undefined1 *param_2)
 * Classifies the code point byte *param_2 via 0x2c0054 and stores the
 * low bit of the result (the "is a single atom" classification) into the
 * out-parameter *param_1.
 * Confidence: high   Notes: trivial classifier wrapper. */
static void sk_bcg_00476c28(byte *param_1, byte *param_2)
{
    byte bVar1;

    bVar1 = FUN_002c0054(*param_2);
    *param_1 = bVar1 & 1;
    return;
}

/* FUN_00476c58 @ 0x476c58   (est. sk_bcg_00476c58)
 * Ghidra: void sk_bcg_00476c58(undefined8 param_1, ulong param_2)
 * Emits a wide-literal instruction into the current slot: obtains the literal
 * token via 0x48185c, then chains the append helpers 0x4aa3e4/0x498b28/
 * 0x100efc/0x498c1c and writes the packed word
 * ((param_2 & 1) | token<<0x10 | 0xa00000000000000) into the buffer tail at
 * extraout_x9+0x20, committing the new tail via *ctx.
 * Confidence: medium   Notes: unaff_x20 context pointer, extraout_x8/x9/x16
 * register artifacts. */
static void sk_bcg_00476c58(u64 param_1, word_t param_2)
{
    long lVar1;
    long *ctx = unaff_x20;              /* emitter context (unaff_x20) */

    lVar1 = FUN_0048185c();
    FUN_004aa3e4();
    FUN_00498b28(extraout_x16);
    FUN_00100efc();
    FUN_00498c1c();
    FUN_004aabf4(*ctx);
    *(word_t *)(extraout_x9 + 0x20) = param_2 & 1 | lVar1 << 0x10 | 0xa00000000000000;
    *ctx = extraout_x8;
    return;
}

/* FUN_00476cd4 @ 0x476cd4   (est. sk_bcg_00476cd4)
 * Ghidra: undefined1 [16] sk_bcg_00476cd4(ulong param_1, ulong param_2)
 * Normalizes a code-point/position descriptor pair: if the "wide/encoded"
 * flag (bit 0x2000000000000000) of param_2 is set, the effective low half is
 * taken from the top nibble of param_2 (param_2>>0x38 & 0xf) instead of
 * param_1. It then runs the descriptor through thunk 0x36b270 (masked
 * self-modifying/trampoline fn) and returns {param_1, param_2} as a wpair.
 * Confidence: medium   Notes: thunk_FUN_0036b270 indirect-trampoline call. */
static wpair_t sk_bcg_00476cd4(word_t param_1, word_t param_2)
{
    word_t uVar1;
    wpair_t auVar2;

    uVar1 = param_1;
    if ((param_2 & 0x2000000000000000) != 0) {
        uVar1 = param_2 >> 0x38 & 0xf;
    }
    thunk_FUN_0036b270(uVar1, param_2);   /* masked self-modifying/trampoline fn */
    auVar2.hi = param_2;
    auVar2.lo = param_1;
    return auVar2;
}

/* FUN_00476d44 @ 0x476d44   (est. sk_bcg_00476d44)
 * Ghidra: ulong sk_bcg_00476d44(long param_1)
 * Reads the currently-pending instruction's metadata word: if the emission
 * count (param_1+0x10) is zero it returns the sentinel 0xf000000000000007;
 * otherwise it loads the metadata word at param_1+0x18+count*8 and passes the
 * low 60 bits (masked with 0xffffffffffffffb) through thunk 0x36b270
 * (trampoline) before returning the raw value.
 * Confidence: medium   Notes: thunk_FUN_0036b270 indirect-trampoline call. */
static word_t sk_bcg_00476d44(long param_1)
{
    word_t uVar1;

    if (*(long *)(param_1 + 0x10) == 0) {
        uVar1 = 0xf000000000000007;
    }
    else {
        uVar1 = *(word_t *)(param_1 + *(long *)(param_1 + 0x10) * 8 + 0x18);
        FUN_0036b270(uVar1 & 0xffffffffffffffb);   /* masked self-modifying/trampoline fn */
    }
    return uVar1;
}

/* FUN_00476d88 @ 0x476d88   (est. sk_bcg_00476d88)
 * Ghidra: undefined1 [16] sk_bcg_00476d88(long param_1)
 * Reads the current pending (width,index) pair from the emission context:
 * if the count (param_1+0x10) is zero returns {0,0}; otherwise reads the
 * 16-byte slot at (param_1+0x10)+count*16 (lo=width/label, hi=metadata),
 * passes the metadata half through thunk 0x36b270 (trampoline), and returns
 * {lo,hi} as a wpair.
 * Confidence: medium   Notes: thunk_FUN_0036b270 indirect-trampoline call. */
static wpair_t sk_bcg_00476d88(long param_1)
{
    long *plVar1;
    long lVar2, lVar3;
    wpair_t auVar4;

    lVar2 = *(long *)(param_1 + 0x10);
    if (lVar2 == 0) {
        lVar2 = 0;
        lVar3 = 0;
    }
    else {
        plVar1 = (long *)(param_1 + 0x10) + lVar2 * 2;
        lVar2 = *plVar1;
        lVar3 = plVar1[1];
        thunk_FUN_0036b270(lVar3);   /* masked self-modifying/trampoline fn */
    }
    auVar4.hi = lVar3;
    auVar4.lo = lVar2;
    return auVar4;
}

/* FUN_00476dd0 @ 0x476dd0   (est. sk_bcg_00476dd0)
 * Ghidra: void sk_bcg_00476dd0(long param_1, ulong param_2)
 * Emits a compact literal instruction: packs the width (param_1<<0x10) with
 * the low flag bit of param_2 and writes it via the raw emitter 0x4aa494,
 * then chains the append helpers 0x498b28/0x4aaf58 and finalizes with
 * 0x4aa6a8.
 * Confidence: medium   Notes: straight-line emitter chain. */
static void sk_bcg_00476dd0(long param_1, word_t param_2)
{
    FUN_004aa494(param_2 & 1 | param_1 << 0x10);
    FUN_00498b28(extraout_x16);
    FUN_004aaf58();
    FUN_004aa6a8();
    return;
}

/* FUN_00476e18 @ 0x476e18   (est. sk_bcg_00476e18)
 * Ghidra: void sk_bcg_00476e18(undefined8 param_1, undefined8 param_2, uint param_3)
 * Emits a repetition/width instruction: forwards param_1/param_2 plus the
 * context field at ctx+0xa0 to 0x41c1d8, then asks 0x351db4 for the next
 * width. If the borrow flag is set it emits via 0x4aa610/0x4acb6c, else it
 * decrements the width and emits the literal with flag bit (param_3&1) via
 * 0x476dd0, fail-closing on a borrow of 1 (SoftwareBreakpoint(1,0x476e74)).
 * Confidence: medium   Notes: unaff_x20 context pointer, in_ZR borrow flag. */
static void sk_bcg_00476e18(u64 param_1, u64 param_2, uint param_3)
{
    long lVar2;
    long ctx = unaff_x20;               /* emitter context (unaff_x20) */

    FUN_0041c1d8(param_1, param_2, *(u64 *)(ctx + 0xa0));
    lVar2 = FUN_00351db4().lo;
    if ((bool)in_ZR) {
        FUN_004aa610();
        FUN_004acb6c();
    }
    else {
        if (SBORROW8(lVar2, 1)) {
            /* WARNING: Does not return */
            CL4_SWBP(0x476e74);
        }
        sk_bcg_00476dd0(lVar2 + -1, param_3 & 1);
    }
    return;
}

/* FUN_00476e74 @ 0x476e74   (est. sk_bcg_00476e74)
 * Ghidra: void sk_bcg_00476e74(long param_1)
 * Emits a single character-class instruction: when the count (param_1+0x10)
 * is non-zero it forwards the packed instruction word
 * (param_1+0x1c+count*4) to 0x354998 for emission; otherwise it fail-closes
 * via SoftwareBreakpoint(1,0x476e94).
 * Confidence: high   Notes: trivial guarded emitter. */
static void sk_bcg_00476e74(long param_1)
{
    if (*(long *)(param_1 + 0x10) != 0) {
        FUN_00354998(*(uint *)(param_1 + *(long *)(param_1 + 0x10) * 4 + 0x1c));
        return;
    }
    /* WARNING: Does not return */
    CL4_SWBP(0x476e94);
}

/* ==================== SKR27 function bodies ==================== */

/* Extra out-of-slice / cross-part callees used by part 6 bodies. */
extern word_t thunk_FUN_0036b270(); /* thunk alias of FUN_0036b270 */

/* FUN_00476e94 @ 0x00476e94   (est. sk_bcg_00476e94)
 * Ghidra: uint sk_bcg_00476e94(undefined8 param_1, ulong param_2)
 * Regex-bytecode-kind selector. Maps a parsed bytecode/instruction selector
 * (param_2 low byte) to a canonical "kind" tag (uVar3) plus a flag (uVar2)
 * that are handed to FUN_00496f58, which encodes the final bytecode word.
 * Unknown selectors fall through; selector 0xd traps on an error path
 * (string "L4ErrorCodeTruncated" family). The result is masked to 0xff01ffff.
 * Confidence: medium   Notes: switch dispatch; noreturn on case 0xd. */
static word_t sk_bcg_00476e94(word_t ctx, word_t selector)
{
    word_t kind;          /* uVar3 */
    word_t flag;          /* uVar2 */
    word_t result;        /* uVar1 */

    kind = 2;
    flag = 0;
    switch (selector & 0xff) {
    case 1:
        goto set_flag;                 /* kind stays 2 */
    case 2:
        flag = 0;
        kind = 3;
        break;
    case 3:
        flag = 1;
        kind = selector;
        break;
    case 4:
    case 6:
        flag = 0;
        kind = selector;
        break;
    case 5:
        kind = 4;
        goto set_flag;
    case 7:
        kind = 6;
        goto set_flag;
    case 8:
        flag = 0;
        kind = 5;
        break;
    case 9:
        kind = 5;
        goto set_flag;
    case 10:
        flag = 0;
        kind = 7;
        break;
    case 11:
        kind = 7;
        goto set_flag;
    case 12:
        flag = 0;
        kind = 1;
        break;
    case 13:
        FUN_00350d94(0xb2);            /* error/truncation path */
        FUN_004aac40();
        FUN_001afa84();                /* does not return */
        break;
    set_flag:
        flag = 1;
        break;
    }
    FUN_0036b270(ctx);
    result = FUN_00496f58(kind, ctx, flag);
    return result & 0xff01ffff;
}

/* FUN_00476fd0 @ 0x00476fd0   (est. sk_bcg_00476fd0)
 * Ghidra: void sk_bcg_00476fd0(undefined8 param_1,undefined8 param_2,ulong param_3,ulong param_4)
 * Emits the bytecode for a run of instructions from the regex AST into the
 * context's per-slot vectors. param_3 is the start instruction index and
 * param_4 (shifted >>1) the end; it walks entries in the anchor table
 * (built by FUN_004772d0/FUN_00477338), growing the "payload"/"aux" vectors
 * (ctx+8, ctx+0x58, ctx+0x60) via growth-check FUN_003a261c and pushes tags
 * 0x1100000000000000 / 0x400000000000000, wiring up indices (swA/hb8)
 * into the emitted records. SWBP traps on out-of-range / exhausted bounds.
 * Confidence: medium   Notes: heavy use of implicit registers unaff_x22/x23/x25;
 * FUN_0036b118 is a release/cleanup helper, FUN_0036b270 an acquire helper. */
static void sk_bcg_00476fd0(word_t p1, word_t p2, word_t p3, word_t p4)
{
    word_t *ctx;            /* unaff_x22 - implicit register context base */
    word_t x23;             /* unaff_x23 - implicit register (arg to FUN_00476d44) */
    word_t slot_val;        /* unaff_x25 - implicit register carried value */
    wpair_t range;          /* auVar12 = sk_bcg_00477338(1) */
    word_t anchor;          /* fl4 = sk_bcg_004772d0() */
    word_t idx;             /* param_3 (current instruction index) */
    word_t end;             /* param_4 >> 1 (end index) */
    word_t e, e2;           /* swA/fl6/uVar10 scratch from FUN_003a261c */
    word_t count;           /* swA - element count */
    word_t tail;            /* hb8 - saved payload index */
    word_t capflag;         /* uVar3 - capacity / bound flag */
    word_t *slot;           /* lVar7 / resH - vector base pointer */
    word_t *slot8;          /* lVar7 - ctx+8 base kept for tail read */
    long off;               /* resH / tagB - element offset */

    FUN_0035089c();
    anchor = sk_bcg_004772d0();
    range = sk_bcg_00477338(1);
    end = p4 >> 1;
    FUN_0036b270();
    idx = p3;
    for (;;) {
        if (end == idx) {
            FUN_0036b118(range.lo);
            e = sk_bcg_00476d44(x23);
            if (((e ^ 0xffffffffffffffffULL) & 0xf000000000000007ULL) != 0) {
                FUN_004ab890();
                sk_bcg_00473244(0, 0, 0, 0); /* register-residue args */
                FUN_004a38c8(e);
                if (end == 0) {
                    sk_bcg_00477494(anchor);
                }
                return;
            }
            CL4_SWBP(0x4772d0);          /* exhaustive-match SWBP */
        }
        capflag = (end <= idx);
        if ((long)end <= (long)idx) {
            break;                       /* -> SWBP 0x4772c8 below */
        }
        e = *(word_t *)(range.hi + idx * 8);
        slot = *(word_t **)(ctx + 0x58 / 8);      /* ctx+0x58 */
        tail = *(word_t *)(slot + 0x10 / 8);
        FUN_004ab4e8();
        FUN_0036b270(e & /* extraout_x8 */ (word_t)0);
        e2 = FUN_003a261c(slot);
        if ((e2 & 1) == 0) {
            FUN_004aa94c(e2, tail + 1);
            slot = (word_t *)FUN_00498fd0();
        }
        off = *(long *)(slot + 0x10 / 8);
        FUN_004ac89c(*(word_t *)(slot + 0x18 / 8));
        if (capflag) {
            FUN_004aa720();
            slot = (word_t *)FUN_00498fd0();
        }
        *(long *)(slot + 0x10 / 8) = slot_val;    /* unaff_x25 */
        FUN_004ab8ac(slot + off * 0x10);
        *(word_t **)(ctx + 0x58 / 8) = slot;
        slot = *(word_t **)(ctx + 8 / 8);
        e2 = FUN_003a261c(slot);
        if ((e2 & 1) == 0) {
            FUN_004aa5c4();
            slot = (word_t *)FUN_00499158();
        }
        count = *(word_t *)(slot + 0x10 / 8);
        capflag = (*(word_t *)(slot + 0x18 / 8) >> 1) <= count;
        if (capflag) {
            FUN_004aa720();
            slot = (word_t *)FUN_00499158();
        }
        *(word_t *)(slot + 0x10 / 8) = count + 1;
        *(word_t *)(slot + count * 8 + 0x20) = 0x1100000000000000ULL;
        *(word_t **)(ctx + 8 / 8) = slot;
        slot = *(word_t **)(ctx + 0x60 / 8);
        e2 = FUN_003a261c(slot);
        if ((e2 & 1) == 0) {
            FUN_004aa5c4();
            slot = (word_t *)FUN_00499094();
        }
        off = *(long *)(slot + 0x10 / 8);
        FUN_004ac89c(*(word_t *)(slot + 0x18 / 8));
        if (capflag) {
            FUN_004aa720();
            slot = (word_t *)FUN_00499094();
        }
        *(word_t *)(slot + 0x10 / 8) = count + 1;
        slot = slot + off * 0x20;
        *(word_t *)(slot + 0x20 / 8) = count;
        *(word_t *)(slot + 0x28 / 8) = tail;
        FUN_004ab420();
        *(word_t **)(ctx + 0x60 / 8) = slot - off * 0x20;
        FUN_004ab890(e);
        sk_bcg_00473244(0, 0, 0, 0); /* register-residue args */
        FUN_004ab4e8();
        FUN_0036b118(e & /* extraout_x8_00 */ (word_t)0);
        if (end != 0) {
            FUN_0036b118(range.lo);
            return;
        }
        /* ---- end == 0 tail path ---- */
        slot8 = *(word_t **)(ctx + 8 / 8);
        e2 = FUN_003a261c(slot8);
        if ((e2 & 1) == 0) {
            FUN_004aa5c4();
            slot8 = (word_t *)FUN_00499158();
        }
        count = *(word_t *)(slot8 + 0x10 / 8);
        slot_val = count + 1;            /* unaff_x25 */
        capflag = (*(word_t *)(slot8 + 0x18 / 8) >> 1) <= count;
        if (capflag) {
            FUN_004aa720();
            slot8 = (word_t *)FUN_00499158();
        }
        *(word_t *)(slot8 + 0x10 / 8) = slot_val;
        *(word_t *)(slot8 + count * 8 + 0x20) = 0x400000000000000ULL;
        *(word_t **)(ctx + 8 / 8) = slot8;
        slot = *(word_t **)(ctx + 0x60 / 8);
        e2 = FUN_003a261c(slot);
        if ((e2 & 1) == 0) {
            FUN_0006b3f4(*(word_t *)(slot + 0x10 / 8));
            slot = (word_t *)FUN_00499094();
        }
        off = *(long *)(slot + 0x10 / 8);
        FUN_004ac89c(*(word_t *)(slot + 0x18 / 8));
        if (capflag) {
            FUN_004aa720();
            slot = (word_t *)FUN_00499094();
        }
        *(word_t *)(slot + 0x10 / 8) = slot_val;
        slot = slot + off * 0x20;
        *(word_t *)(slot + 0x20 / 8) = count;
        *(word_t *)(slot + 0x28 / 8) = anchor;   /* fl4 */
        FUN_004ab420();
        *(word_t **)(ctx + 0x60 / 8) = slot - off * 0x20;
        /* lb = *(slot8 + 0x10)  (lVar7 kept the ctx+8 base) */
        e = *(word_t *)(slot8 + 0x10 / 8);
        slot = *(word_t **)(ctx + 0x58 / 8);
        e2 = FUN_003a261c(slot);
        if ((e2 & 1) == 0) {
            slot = (word_t *)FUN_0049a4a4(slot);
        }
        if (*(word_t *)(slot + 0x10 / 8) <= tail) {
            CL4_SWBP(0x4772cc);
        }
        slot = slot + tail * 0x10;
        *(word_t *)(slot + 0x20 / 8) = e;        /* lb - saved count word */
        *(word_t *)(slot + 0x28 / 8) = 0;        /* byte 0 */
        *(word_t **)(ctx + 0x58 / 8) = slot - tail * 0x10;
        idx = idx + 1;
    }
    CL4_SWBP(0x4772c8);          /* unreachable bound trap */
}

/* FUN_004772d0 @ 0x004772d0   (est. sk_bcg_004772d0)
 * Ghidra: undefined8 sk_bcg_004772d0(void)
 * Appends a fresh "anchor" record to the context's anchor slot (ctx+0x50).
 * Returns the slot's previous element count; stores a new entry at offset
 * unaff_x22 with a zero payload word and a flag byte of 1, then bumps the
 * slot's count to unaff_x22+1. Runs several acquire/flush helpers between
 * read and write (FUN_004ab5b0/FUN_00498b28/FUN_004ac7e0/FUN_00100efc/
 * FUN_00498c1c) as part of the vector-append discipline.
 * Confidence: medium   Notes: implicit registers unaff_x20 (ctx) / unaff_x22
 * (insertion index); byte store at +0x28. */
static word_t sk_bcg_004772d0(void)
{
    word_t *ctx;            /* unaff_x20 - implicit register context base */
    word_t x22;             /* unaff_x22 - implicit insertion index */
    word_t **slotp;         /* plVar4 = &ctx+0x50 */
    word_t *slot;           /* lVar2 */
    word_t old_count;       /* uVar3 */

    slotp = (word_t **)(ctx + 0x50);
    slot = *slotp;
    old_count = *(word_t *)(slot + 0x10);
    FUN_004ab5b0();
    FUN_00498b28(/* extraout_x16 */ 0);
    FUN_004ac7e0();
    FUN_00100efc();
    FUN_00498c1c();
    slot = *slotp;
    *(word_t *)(slot + 0x10) = x22 + 1;
    *(word_t *)(slot + x22 * 0x10 + 0x20) = 0;
    *(word_t *)(slot + x22 * 0x10 + 0x28) = 1;    /* flag byte */
    *slotp = slot;
    return old_count;
}

/* FUN_00477338 @ 0x00477338   (est. sk_bcg_00477338)
 * Ghidra: undefined1 [16] sk_bcg_00477338(long param_1,long param_2)
 * Returns a 16-byte {base, data} pair describing a vector whose header is at
 * param_2 (element-array base = param_2+0x20) after a resize/reserve of
 * abs(count - param_1) elements via FUN_0035053c + FUN_001a9a84. The new
 * element count comes from FUN_00351db4 unless its condition flag (in_ZR)
 * keeps the old count; bounds checks trap (SWBP 0x4773a4/0x4773a8) if the
 * resulting count is negative or exceeds the stored count. param_1 must be
 * non-negative (SWBP 0x4773a0 otherwise).
 * Confidence: medium   Notes: 16-byte return; in_ZR is a decompiler flag
 * artifact of the FUN_00351db4 call. */
static wpair_t sk_bcg_00477338(long delta, word_t vec)
{
    word_t count;           /* fl4 = *(vec+0x10) */
    word_t diff;            /* fl4 - param_1 */
    word_t absd;            /* abs(diff) */
    word_t n;               /* uVar3 = FUN_00351db4() */
    word_t u;               /* uVar1 */
    bool zf;                /* in_ZR: zero/condition flag of FUN_00351db4 */
    wpair_t out;            /* auVar5 */

    if (delta < 0) {
        CL4_SWBP(0x4773a0);
    }
    count = *(word_t *)(vec + 0x10);
    diff = count - (word_t)delta;
    absd = diff & (((long)diff >> 0x3f) ^ 0xffffffffffffffffULL);   /* |diff| */
    FUN_0035053c(0, absd);
    FUN_001a9a84();
    n = FUN_00351db4().lo;
    u = count;
    if (!zf) {              /* in_ZR clear -> use new count */
        u = n;
    }
    if ((long)u >= 0) {
        if (u <= count) {
            out.lo = vec;
            out.hi = vec + 0x20;
            return out;
        }
        CL4_SWBP(0x4773a8);
    }
    CL4_SWBP(0x4773a4);
    return out;             /* unreachable */
}

/* FUN_004773a8 @ 0x004773a8   (est. sk_bcg_004773a8)
 * Ghidra: void sk_bcg_004773a8(long,undefined8,undefined8,code*,code*,code*)
 * Emits a range/instruction marker into the bytecode via an indirect builder.
 * Calls the caller-supplied function pointers param_4 (a size/getter),
 * param_5 (a 16-byte-returning emit helper, given a tag + flags word derived
 * from implicit registers unaff_x19/unaff_x21), and param_6 (a finalize),
 * then runs release/finalize helpers. If the size from param_4 underflows
 * the baseline (SBORROW8) the function traps (SWBP 0x477494); param_1 must
 * be non-negative (SWBP 0x477490).
 * Confidence: medium   Notes: indirect (code*) calls; 16-byte return from
 * param_5; SBORROW8 is the ARM signed-borrow (no-underflow) condition. */
static void sk_bcg_004773a8(long p1, word_t p2, word_t p3,
                            code *size_fn, code *emit_fn, code *finalize_fn)
{
    word_t base;            /* lVar4 = FUN_00350b54() */
    word_t size;            /* lVar5 = (*size_fn)() */
    word_t x19;             /* unaff_x19 - implicit register */
    word_t x21;             /* unaff_x21 - implicit register */
    word_t flags;           /* uVar2 - flag/kind word */
    uint   wide;            /* swB - width/kind selector */
    word_t tag;             /* uVar1 - packed tag */
    wpair_t out;            /* auVar8 - 16-byte return of (*emit_fn) */
    word_t word;            /* final uVar2 */
    word_t u6;              /* fl6 = (*finalize_fn)() */

    if (p1 < 0) {
        CL4_SWBP(0x477490);
    }
    base = FUN_00350b54();
    FUN_00106e3c();
    size = size_fn();
    if (!/* SBORROW8(size, base): size >= base */ ((long)size < (long)base)) {
        flags = x21;
        if ((x19 & 0x2000000000000000ULL) != 0) {
            flags = (x19 >> 0x38) & 0xf;
        }
        wide = (uint)(x21 >> 0x3b) & 1;
        if ((x19 & 0x1000000000000000ULL) == 0) {
            wide = 1;
        }
        tag = 7;
        if (wide == 0) {
            tag = 0xb;
        }
        out = emit_fn(0xf, (size - base) & (((long)(size - base) >> 0x3f)
                                              ^ 0xffffffffffffffffULL),
                      tag | (flags << 0x10));
        tag = (flags << 0x10) | 0xb;
        if (wide != 0) {
            tag = (flags << 0x10) | 7;
        }
        word = out.lo;
        if ((out.hi & 0xff) == 1) {
            word = tag;
        }
        FUN_0035063c(0xf, word);
        u6 = finalize_fn();
        FUN_004abf6c();
        FUN_003a25d4();
        FUN_0034c444(u6);
        return;
    }
    CL4_SWBP(0x477494);
}

/* FUN_00477494 @ 0x00477494   (est. sk_bcg_00477494)
 * Ghidra: void sk_bcg_00477494(ulong param_1)
 * Finalizes the anchor record at index param_1 in the context's anchor slot
 * (ctx+0x50): writes the implicit register unaff_x22 into the record's
 * payload word (+0x20) and clears its flag byte (+0x28). The slot is
 * re-fetched/grown via FUN_003a261c/FUN_0049a4a4. Traps (SWBP 0x477500 /
 * 0x477504) if the index is negative or past the slot's count.
 * Confidence: medium   Notes: implicit registers unaff_x20 (ctx) /
 * unaff_x22 (stored value); byte store at +0x28. */
static void sk_bcg_00477494(word_t index)
{
    word_t *ctx;            /* unaff_x20 - implicit register context base */
    word_t value;           /* unaff_x22 - implicit value to store */
    word_t *slot;           /* lVar4 */
    word_t r;               /* uVar3 = FUN_003a261c */

    FUN_004ac7e0();
    slot = *(word_t **)(ctx + 0x50);
    r = FUN_003a261c(slot);
    if ((r & 1) == 0) {
        slot = (word_t *)FUN_0049a4a4(slot);
    }
    if ((long)index >= 0) {
        if (index < *(word_t *)(slot + 0x10)) {
            slot = slot + index * 0x10;
            *(word_t *)(slot + 0x20) = value;
            *(word_t *)(slot + 0x28) = 0;    /* flag byte */
            *(word_t **)(ctx + 0x50) = slot - index * 0x10;
            return;
        }
        CL4_SWBP(0x477504);
    }
    CL4_SWBP(0x477500);
}

/* FUN_00477504 @ 0x00477504   (est. sk_bcg_00477504)
 * Ghidra: void sk_bcg_00477504(void)
 * Emits a "truncated error" bytecode marker. It reports the L4 error-code
 * truncated condition (string "L4ErrorCodeTruncated" at 0x6886a8) through
 * FUN_00002834, then sequences a series of bytecode emit/acquire helpers and
 * dispatches the value at ctx+0x48 through FUN_004ab224 before finalizing
 * with FUN_004abf5c.
 * Confidence: medium   Notes: string-address literal 0x6886a8+8; implicit
 * register unaff_x20 (ctx). */
static void sk_bcg_00477504(void)
{
    word_t *ctx;            /* unaff_x20 - implicit register context base */

    FUN_0008409c();
    FUN_00002834((word_t)(0x6886a8 + 8));   /* "L4ErrorCodeTruncated"+8 (s_L4_ErrorCodeTruncated_006886a8) */
    FUN_0036a940();
    FUN_004ac5b4();
    FUN_003507e0();
    FUN_00498ad4();
    FUN_004aad54();
    FUN_00498bdc();
    FUN_004ab224(*(word_t *)(ctx + 0x48));
    FUN_004abf5c();
}

/* FUN_00477590 @ 0x00477590   (est. sk_bcg_00477590)
 * Ghidra: void sk_bcg_00477590(ulong param_1,long param_2)
 * Emits a packed two-field bytecode tag: the low 16 bits come from param_1
 * and the next 16 from param_2 (packed as param_1 | param_2<<16), pushed via
 * FUN_004aa494, then several acquire/append helpers run
 * (FUN_00498b28/FUN_004aaf58/FUN_004aa6a8).
 * Confidence: medium   Notes: straightforward emit sequence. */
static void sk_bcg_00477590(word_t p1, long p2)
{
    FUN_004aa494(p1 | ((word_t)p2 << 0x10));
    FUN_00498b28(/* extraout_x16 */ 0);
    FUN_004aaf58();
    FUN_004aa6a8();
}

/* FUN_004775d0 @ 0x004775d0   (est. sk_bcg_004775d0)
 * Ghidra: void sk_bcg_004775d0(void)
 * Appends a data word into the bytecode vector at *ctx (unaff_x20): after
 * FUN_00084220/FUN_004abacc(extraout_x8/x9), copies the tag word at
 * (extraout_x8 + extraout_x9*4 + 0x1c), registers a callback bundle via
 * FUN_00498b7c(four function pointers), and stores the tag into the grown
 * vector at element unaff_x24 (+0x20). Traps (SWBP 0x477694) when the
 * growth produced no element (extraout_x9 == 0).
 * Confidence: medium   Notes: register artifacts extraout_x8/x8_00/x9,
 * unaff_x24 index; callback pointers cast to word_t. */
static void sk_bcg_004775d0(void)
{
    word_t *slotp;          /* unaff_x20 - implicit register: pointer to slot */
    word_t x24;             /* unaff_x24 - implicit element index */
    word_t tag;             /* uVar1 - copied tag word */
    word_t handle;          /* uVar3 = FUN_00084220() */
    long x8, x8b;           /* extraout_x8 / extraout_x8_00 */
    long x9;                /* extraout_x9 */

    handle = FUN_00084220().lo;
    FUN_004abacc();
    if (x9 != 0) {
        tag = *(unsigned int *)(x8 + x9 * 4 + 0x1c);
        FUN_00498b7c((word_t)FUN_004982ac, (word_t)FUN_00071fe4,
                     (word_t)FUN_00074a28, (word_t)FUN_00498e50);
        FUN_004aad54();
        FUN_00352c40();
        FUN_00498c84();
        FUN_004ab224(*slotp);
        *(unsigned int *)(x8b + x24 * 4 + 0x20) = tag;
        *slotp = x8b;
        FUN_00084234(handle);
        return;
    }
    CL4_SWBP(0x477694);
}

/* FUN_00477694 @ 0x00477694   (est. sk_bcg_00477694)
 * Ghidra: uint sk_bcg_00477694(long param_1,uint param_2)
 * Kind-resolution helper over the emitted bytecode vector param_1. If the
 * vector is non-empty and the low byte of param_2 is not the "anchored"
 * selector (2) while the last element's tag has the 0x20 bit set, the
 * selector is collapsed to (low byte == 0). Empty vector traps SWBP 0x4776c4.
 * Confidence: high   Notes: element tag read via *(param_1+count*4+0x1c). */
static word_t sk_bcg_00477694(long vec, word_t sel)
{
    long count;             /* *(vec+0x10) */

    count = *(long *)(vec + 0x10);
    if (count != 0) {
        if (((sel & 0xff) != 2) &&
            (*(unsigned int *)(vec + count * 4 + 0x1c) & 0x20) != 0) {
            sel = ((sel & 0xff) == 0);
        }
        return sel;
    }
    CL4_SWBP(0x4776c4);
    return 0;               /* unreachable */
}

/* FUN_004776c4 @ 0x004776c4   (est. sk_bcg_004776c4)
 * Ghidra: uint sk_bcg_004776c4(long param_1)
 * Reads a 2-bit mode from the last element's tag of bytecode vector param_1:
 * bit 5 yields 1, and the 0x80000 flag overrides to 2. Empty vector traps
 * SWBP 0x4776ec.
 * Confidence: high   Notes: element tag read via *(param_1+count*4+0x1c). */
static word_t sk_bcg_004776c4(long vec)
{
    long count;             /* *(vec+0x10) */
    unsigned int tag;       /* uVar1 */
    word_t mode;            /* uVar2 */

    count = *(long *)(vec + 0x10);
    if (count != 0) {
        tag = *(unsigned int *)(vec + count * 4 + 0x1c);
        mode = (tag >> 5) & 1;
        if ((tag & 0x80000) != 0) {
            mode = 2;
        }
        return mode;
    }
    CL4_SWBP(0x4776ec);
    return 0;               /* unreachable */
}

/* FUN_004776ec @ 0x004776ec   (est. sk_bcg_004776ec)
 * Ghidra: void sk_bcg_004776ec(undefined8,undefined8,long,long,ulong)
 * Core bytecode-instruction emitter state machine. Iterates instructions
 * produced by FUN_0008e518(a 16-byte descriptor: lo = opcode/kind word,
 * hi = flags), and for each dispatch on the derived kind fl6 emits the
 * corresponding opcode word into the output vector (*ctx + ctx[1]) via the
 * shared emit tail (FUN_004aabf4 / store +0x20). Handles: scalar/ASCII
 * ranges (kind 8 inner switch: ASCII 0x40/0x61/0x7f classification and
 * char-class bitmaps), anchor matching (kind 7 via FUN_00478110), and
 * character/range opcode packing (kinds 2/8/9/10) with the 0x4000000000 /
 * 0x1600001xxxxxxx flags and param_3<<0x1b offset packing. Traps (SWBP
 * 0x477da0..0x477dbc) on exhausted vectors / negative offsets. Reads global
 * 16-byte constant at 0x4baeb0.
 * Confidence: medium   Notes: enormous switch; many register artifacts
 * (extraout_x8*/x9/x16, unaff_x20 ctx, unaff_x30); indirect grow helpers. */
static void sk_bcg_004776ec(word_t p1, word_t p2, long p3, long p4, word_t p5)
{
    word_t *ctx;            /* unaff_x20 - implicit context pointer (mutated) */
    word_t x30;             /* unaff_x30 - implicit register */
    word_t *vecP;        /* vector = *ctx */
    word_t *vecQ;        /* secondary vector / re-dispatch target */
    wpair_t pair;           /* auVar18 = FUN_0008e518() */
    word_t lo, hi;          /* lb=pair.lo, uVar13=pair.hi */
    word_t kind;            /* fl6 - derived kind tag */
    word_t elem_tag;        /* uVar2 - *(vecP + count*4 + 0x1c) */
    word_t swA, swB, swC, swD, swE, op;  /* scratch / opcode word */
    word_t resL, resH;   /* helper results */
    word_t x8a, x8b, x8c, x8d, x8e;   /* extraout_x8 / x8_00 / x8_01 / x8_02 / x8_03 */
    long   x9a;             /* extraout_x9 */
    bool   ckflag;           /* flag from FUN_004ac1e0 */
    word_t lo16;            /* resL == 0xa0d lower half of paired constant */
    word_t hi16;            /* resH == -0x1e00000000000000 upper half */

    (void)p1; (void)p2;
    for (;;) {
        pair = FUN_0008e518();
        hi = pair.hi;
        lo = pair.lo;
        vecP = (word_t *)*ctx;
        if (vecP[2] == 0) {
            CL4_SWBP(0x477da0);                 /* exhausted vector */
        }
        swB = 0;
        if (((*(word_t *)((char *)ctx + 0x1b) & 1) != 0) || (0xff < p3)) {
            goto do_ret;                        /* caseD_4 (return 0) */
        }
        if (((0xff < p4) && ((p5 & 0xff) == 0)) || ((hi & 0xff) == 1)) {
            goto do_ret;                        /* caseD_1 (return 0) */
        }
        kind = ((((uint)(lo >> 32) >> 0x1b) & 0x1e) | (((uint)lo >> 2) & 1));
        if (9 < (kind - 3)) {
            goto do_ret;                        /* kind > 12 -> return 0 */
        }
        elem_tag = *(unsigned int *)((word_t)vecP + vecP[2] * 4 + 0x1c);
        switch (kind) {
        default:                                /* kinds 0,1,2,3 */
            FUN_00117cc4(/*auStack_b8*/ (word_t)0, (lo & 0xffffffffffffffbULL) + 0x10, 0x51);
            vecQ = (word_t *)*(word_t *)((lo & 0xffffffffffffffbULL) + 0x68);
            /* local_428 builder struct: kind tag 3, first field 1 */
            resL = 1;
            resH = 3;
            op = FUN_0041a0dc(/*auStack_b8*/ (word_t)0, /*&local_428*/ (word_t)0);
            ctx = vecQ;
            if ((op & 1) == 0) {
                goto do_ret;                    /* return 0 */
            }
            break;                              /* -> re-dispatch loop */
        case 4:
        case 5:
        case 6:
        case 9:
        case 10:
        case 11:
            goto do_ret;                        /* return 0 */
        case 7:                                 /* anchor instruction */
            FUN_004ac0c0();
            swB = *(word_t *)(x8a + 0x10);
            swA = *(word_t *)(x8a + 0x18);    /* flag byte */
            FUN_0036b270(swB);
            resL = sk_bcg_00478110(vecP, swB, swA);
            FUN_004ac33c();
            FUN_0036b118(swB);
            swA = (resL == 2);
            if (swA) {
                goto do_ret;                    /* return 0 */
            }
            FUN_004aa6d8();
            FUN_00498b28(/*extraout_x16*/ 0);
            FUN_004acb94();
            FUN_004aafac(ctx[7]);
            FUN_004abafc();
            swB = 0;
            if (!swA) {
                swB = x8b;                    /* extraout_x8_00 */
            }
            if (((p5 & 0xff) == 0) && (p4 < 0)) {
                CL4_SWBP(0x477d7c);
            }
            if (p3 < 0) {
                CL4_SWBP(0x477d74);
            }
            ckflag = false;
            FUN_004ac1e0(swB);
            if (ckflag) {
                CL4_SWBP(0x477d78);
            }
            FUN_004aa494();
            FUN_00498b28(/*extraout_x16_00*/ 0);
            FUN_004aaf58();
            FUN_004aa6a8();                     /* LAB_0047799c */
            swB = 1;                          /* LAB_00477c9c */
            goto do_ret;                        /* return 1 */
        case 8:                                 /* character-class instruction */
            FUN_00117cc4(/*auStack_168*/ (word_t)0, (lo & 0xffffffffffffffbULL) + 0x10, 0xb0);
            FUN_00117d14(/*auStack_b8*/ (word_t)0, (lo & 0xffffffffffffffbULL) + 0x10, 0xb0);
            kind = FUN_0049e2d4(/*auStack_168*/ (word_t)0);
            if (10 < kind) {
                goto do_ret;                    /* return 0 */
            }
            switch (kind) {
            default:
                vecQ = (word_t *)FUN_0049e2f0(/*auStack_b8*/ (word_t)0);
                if (vecP[2] == 0) {
                    CL4_SWBP(0x477db8);
                }
                resL = vecQ[0];             /* low 8 bytes of value */
                resH = vecQ[1];            /* high 8 bytes */
                if ((elem_tag & 1) != 0) {      /* big/qualified class */
                    FUN_004acca8(/*auStack_218*/ (word_t)0);
                    FUN_004acd14(/*auStack_218*/ (word_t)0);
                    FUN_00350738();
                    op = FUN_002bde1c();
                    if ((op & 1) == 0) {
                        goto class_scalar;      /* LAB_00477b10 */
                    }
                    swB = FUN_004ab630();
                    resL = FUN_0036a940(swB, 0x180, 7);
                    /* load 16-byte global constant at 0x4baeb0 */
                    *(word_t *)(resL + 0x18) = *(word_t *)0x4baeb8;  /* uRam00000000004baeb8 */
                    *(word_t *)(resL + 0x10) = *(word_t *)0x4baeb0;  /* _DAT_004baeb0 */
                    FUN_004acca8(/*&local_428*/ (word_t)0);
                    FUN_0049c850(/*&local_428*/ (word_t)0);
                    FUN_00117cc4(resL + 0x20, /*&local_428*/ (word_t)0, 0x160);
                    FUN_004acca8(/*auStack_2c8*/ (word_t)0);
                    FUN_004acd14(/*auStack_2c8*/ (word_t)0);
                    resH = sk_bcg_00478110(vecP, resL, 0);
                    FUN_004ac33c();
                    FUN_0036b588(resL);
                    FUN_004985b4();
                    FUN_00002834();
                    FUN_0036b6ac();
                    swA = (resH == 2);
                    if (!swA) {
                        FUN_004aa6d8();
                        FUN_00498b28(/*extraout_x16_01*/ 0);
                        FUN_004acb94();
                        FUN_004aafac(ctx[7]);
                        FUN_004abafc();
                        swB = 0;
                        if (!swA) {
                            swB = x8c;        /* extraout_x8_01 */
                        }
                        if (((p5 & 0xff) == 0) && (p4 < 0)) {
                            CL4_SWBP(0x477db0);
                        }
                        if (p3 < 0) {
                            CL4_SWBP(0x477da4);
                        }
                        ckflag = false;
                        FUN_004ac1e0(swB);
                        if (ckflag) {
                            CL4_SWBP(0x477da8);
                        }
                        FUN_004aa494();
                        FUN_00498b28(/*extraout_x16_03*/ 0);
                        FUN_004aaf58();
                        FUN_004a36d4(/*auStack_168*/ (word_t)0);
                        FUN_004aa6a8();         /* LAB_0047799c */
                        swB = 1;              /* LAB_00477c9c */
                        goto do_ret;            /* return 1 */
                    }
                    FUN_004a36d4(/*auStack_168*/ (word_t)0);
                    goto do_ret;                /* return 0 (LAB_00477b40) */
                }
                FUN_004acca8(/*&local_428*/ (word_t)0);
                FUN_004acd14(/*&local_428*/ (word_t)0);
            class_scalar:                       /* LAB_00477b10 */
                swA = (resL == 0xa0d) && (resH == -0x1e00000000000000ULL);
                if (swA) {
                    FUN_004a36d4(/*auStack_168*/ (word_t)0);
                    goto do_ret;                /* return 0 */
                }
                FUN_00350738();
                FUN_004aa890();
                op = FUN_002a0cf8();
                if ((op & 1) != 0) {
                    FUN_004a36d4(/*auStack_168*/ (word_t)0);
                    goto do_ret;                /* return 0 */
                }
                FUN_00350738();
                FUN_002bd8f0();
                swC = FUN_00466214();
                if (swA) {
                    FUN_004a36d4(/*auStack_168*/ (word_t)0);
                    goto do_ret;                /* return 0 */
                }
                if ((p5 & 0xff) == 0) {
                    if (p4 < 0) {
                        CL4_SWBP(0x477db4);
                    }
                    swD = (word_t)p4 << 0x13;
                } else {
                    swD = 0x40000;
                }
                if (p3 < 0) {
                    CL4_SWBP(0x477dac);
                }
                op = 0x4000000000ULL;
                if ((elem_tag & 0x10000) != 0) {
                    op = 0;
                }
                swE = 0x1600000800000000ULL;
                if ((hi & 0xff) != 0) {
                    swE = 0x1600000800020000ULL;
                }
                op = swE | ((word_t)p3 << 0x1b) | (swC & 0xff) | swD | op;
                FUN_004aa3e4();
                FUN_00498b28(/*extraout_x16_04*/ 0);
                FUN_00100efc();
                FUN_00498c1c();
                FUN_004a36d4(/*auStack_168*/ (word_t)0);
                goto emit;                      /* LAB_00477c8c */
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                goto do_ret;                    /* return 0 */
            case 2:                             /* range/kind-2 opcode */
                op = sk_bcg_00476e94(vecP, *(word_t *)FUN_0049e2f0(/*auStack_b8*/ (word_t)0));
                swC = (word_t)((uint)op & 0xff);
                if (((uint)op >> 0x18) != 0) {
                    swC |= 0x200;
                }
                if ((p5 & 0xff) == 0) {
                    if (p4 < 0) {
                        CL4_SWBP(0x477d94);
                    }
                    swE = (word_t)p4 << 0x13;
                } else {
                    swE = 0x40000;
                }
                if (p3 < 0) {
                    CL4_SWBP(0x477d84);
                }
                swB = 0x4000000000ULL;
                if ((elem_tag & 0x10000) != 0) {
                    swB = 0;
                }
                swD = 0x1600002000000000ULL;
                if ((hi & 0xff) != 0) {
                    swD = 0x1600002000020000ULL;
                }
                op = swD | ((word_t)p3 << 0x1b) | ((word_t)((uint)(op >> 6) & 0x400))
                     | swC | swE | swB;
                break;                          /* -> common tail 8 */
            case 8:
                if ((p5 & 0xff) == 0) {
                    if (p4 < 0) {
                        CL4_SWBP(0x477d90);
                    }
                    swC = (word_t)p4 << 0x13;
                } else {
                    swC = 0x40000;
                }
                if (p3 < 0) {
                    CL4_SWBP(0x477d80);
                }
                swB = 0x4000000000ULL;
                if ((elem_tag & 0x10000) != 0) {
                    swB = 0;
                }
                swD = 0x1600001000000001ULL;
                if ((hi & 0xff) != 0) {
                    swD = 0x1600001000020001ULL;
                }
                goto c14;                       /* LAB_00477c14 */
            case 9:
                if ((p5 & 0xff) == 0) {
                    if (p4 < 0) {
                        CL4_SWBP(0x477d98);
                    }
                    swC = (word_t)p4 << 0x13;
                } else {
                    swC = 0x40000;
                }
                if (p3 < 0) {
                    CL4_SWBP(0x477d88);
                }
                swB = 0x4000000000ULL;
                if ((elem_tag & 0x10000) != 0) {
                    swB = 0;
                }
                swD = 0x1600001000000000ULL;
                if ((hi & 0xff) != 0) {
                    swD = 0x1600001000020000ULL;
                }
            c14:                                /* LAB_00477c14 */
                op = swD | ((word_t)p3 << 0x1b) | swC | swB;
                break;                          /* -> common tail 8 */
            case 10:
                if (vecP[2] == 0) {
                    CL4_SWBP(0x477dbc);
                }
                if ((p5 & 0xff) == 0) {
                    if (p4 < 0) {
                        CL4_SWBP(0x477d9c);
                    }
                    op = (word_t)p4 << 0x13;
                } else {
                    op = 0x40000;
                }
                if (p3 < 0) {
                    CL4_SWBP(0x477d8c);
                }
                swC = 0x4000000000ULL;
                if ((elem_tag & 0x10000) != 0) {
                    swC = 0;
                }
                swD = 0x1600001000000000ULL;
                if ((hi & 0xff) != 0) {
                    swD = 0x1600001000020000ULL;
                }
                op = swD | ((word_t)p3 << 0x1b)
                     | ((word_t)(*(unsigned int *)((word_t)vecP + vecP[2] * 4 + 0x1c) >> 4) & 1)
                     | swC | op;
                break;                          /* -> common tail 8 */
            }
            /* common tail 8: FUN_004aa3e4... then emit */
            FUN_004aa3e4();
            FUN_00498b28(/*extraout_x16_02*/ 0);
            FUN_00100efc();
            FUN_00498c1c();
            goto emit;                          /* LAB_00477c8c */
        case 12:                                /* re-dispatch descriptor */
            vecQ = (word_t *)FUN_004ab98c(lo & 0xfffffffffffffffULL, 0);
            ctx = vecP;
            break;                              /* -> re-dispatch loop */
        }
        FUN_0008e500(vecQ, hi);              /* loop bottom (re-dispatch) */
        continue;
    emit:                                       /* LAB_00477c8c */
        FUN_004aabf4(ctx[1]);
        *(word_t *)(x9a + 0x20) = op;
        ctx[1] = x8d;                           /* extraout_x8_02 */
        swB = 1;                              /* LAB_00477c9c */
        goto do_ret;                            /* return 1 */
    do_ret:                                     /* switchD_004777b4_caseD_4 */
        FUN_0008e500(swB, x30);
        return;
    }
}

/* FUN_00477e10 @ 0x00477e10   (est. sk_bcg_00477e10)
 * Ghidra: void sk_bcg_00477e10(void)
 * Emits an "anchor" opcode (0x1200000000000000) into the output vector
 * (*ctx). If the cached-anchor flag byte at ctx+0x13 is set, a fresh anchor
 * index is obtained via FUN_004772d0, stashed at ctx[0x12], and the flag
 * cleared; otherwise the cached index is reused. The opcode is appended via
 * the shared emit tail (FUN_004aabf4(*ctx); store +0x20; *ctx = grown) and
 * the anchor index is finalized with FUN_00481918.
 * Confidence: medium   Notes: implicit register unaff_x20 (ctx); byte flag
 * at ctx+0x13; register artifacts extraout_x8/x9/x16. */
static void sk_bcg_00477e10(void)
{
    word_t *ctx;            /* unaff_x20 - implicit context pointer */
    word_t anchor;          /* uVar1 - cached / fresh anchor index */
    word_t x8a;             /* extraout_x8 (grown vector) */
    long   x9a;             /* extraout_x9 */

    if (*(char *)((char *)ctx + 0x13) == 1) {
        anchor = sk_bcg_004772d0();
        ctx[0x12] = anchor;
        *(char *)((char *)ctx + 0x13) = 0;
    } else {
        anchor = ctx[0x12];
    }
    FUN_004aa3e4();
    FUN_00498b28(/*extraout_x16*/ 0);
    FUN_004ac7e0();
    FUN_00100efc();
    FUN_00498c1c();
    FUN_004aabf4(*ctx);
    *(word_t *)(x9a + 0x20) = 0x1200000000000000ULL;
    *ctx = x8a;
    FUN_00481918(anchor);
}

/* FUN_00477e8c @ 0x00477e8c   (est. sk_bcg_00477e8c)
 * Ghidra: uint sk_bcg_00477e8c(ulong param_1)
 * Recursive bytecode subtree validator / walker. Given a descriptor word
 * param_1 whose low bits select a kind (uVar1), it either accepts, rejects,
 * or descends into child descriptors: kinds 2/3 re-dispatch to nested
 * descriptors fetched from a per-kind offset, kinds 7/8/10 are scalar
 * character/flag checks, and kind 12 re-dispatches through FUN_004ab98c.
 * The default kind and kind 1 walk a vector of child descriptors (recurse
 * into FUN_00477e8c over the implicit register unaff_x20) returning 1 only
 * if every child validates; the walk uses saved implicit registers
 * (local_20/30/40 = unaff_x20/22/24). Traps SWBP 0x4780d8/0x4780dc on
 * out-of-range child indices.
 * Confidence: medium   Notes: recursive; heavy implicit-register (unaff_x20/
 * x22/x24) state; register artifacts extraout_x8*/x9/x10. */
static word_t sk_bcg_00477e8c(word_t desc)
{
    word_t kind;            /* uVar1 - kind selector */
    bool   is_twelve;       /* uVar3 = (uVar1 == 0xc) */
    word_t x20, x22, x24;   /* unaff_x20/x22/x24 - implicit registers */
    word_t s20, s22, s24;   /* local_20/30/40 saved copies */
    word_t *child;          /* lVar8 - child vector base */
    word_t count;           /* hb8 - child count */
    word_t idx;             /* swB - walk index */
    word_t r;               /* swA - child result / scratch */
    word_t x8a, x8b, x8c, x8d, x8e, x8f;   /* extraout_x8 / x8_00 / x8_01 / x8_02 / x8_03 / x8_04 / x8_05 / x8_06 */
    long   x9a, x10a;       /* extraout_x9 / extraout_x10 */
    word_t f0, f8, f10, f18, f20, f28, f30, f38, f40, f48, f50, f58;  /* case 6 fields */

    for (;;) {
        kind = ((word_t)((uint)(desc >> 0x3b) & 0x1e) | ((uint)desc >> 2 & 1));
        if (0xc < kind) {
            return 0;
        }
        is_twelve = (kind == 0xc);
        s24 = x24;
        s22 = x22;
        s20 = x20;
        switch (kind) {
        default:
            FUN_004ac15c();
            child = (word_t *)*(word_t *)(x8a + 0x10);
            count = *(word_t *)(child + 0x10);
            FUN_0036b270(child);
            idx = 0;
            goto walk_default;              /* LAB_00477efc */
        case 1:
            FUN_004ac15c();
            child = (word_t *)*(word_t *)((x8c & x22) + 0x10);
            count = *(word_t *)(child + 0x10);
            FUN_0036b270(child);
            idx = 0;
            goto walk_case1;                /* LAB_00477f8c */
        case 2:
            FUN_004ac0c0();
            desc = *(word_t *)(x8b + 0x30);
            x20 = s20; x22 = s22; x24 = s24;
            break;                          /* re-dispatch loop */
        case 3:
            FUN_004ac0c0();
            desc = *(word_t *)(x8f + 0x68);
            x20 = s20; x22 = s22; x24 = s24;
            if ((*(char *)(x8f + 0x60) == 3) &&
                (desc = FUN_004ab064(*(word_t *)(x8f + 0x18), *(word_t *)(x8f + 0x40),
                                     *(word_t *)(x8f + 0x50), *(word_t *)(x8f + 0x20),
                                     *(word_t *)(x8f + 0x30)),
                 x20 = s20, x22 = s22, x24 = s24,
                 ((x9a - 7 < 2) || ((x9a & 0xfffffffffffffffeULL) == 4)) &&
                 (x10a == 0 && x8e == 0))) {
                return 0;
            }
            break;                          /* re-dispatch loop */
        case 4:
        case 5:
        case 9:
        case 11:
            goto fail0;                     /* switchD_00477ee0_caseD_4 -> return 0 */
        case 6:
            FUN_004ac0c0();
            f8   = *(word_t *)(x8d + 0x18);
            f0   = *(word_t *)(x8d + 0x10);
            f28  = *(word_t *)(x8d + 0x28);
            f20  = *(word_t *)(x8d + 0x20);
            f38  = *(word_t *)(x8d + 0x38);
            f30  = *(word_t *)(x8d + 0x30);
            f48  = *(word_t *)(x8d + 0x48);
            f40  = *(word_t *)(x8d + 0x40);
            desc = *(word_t *)(x8d + 0x58);
            FUN_0041bfb4();
            child = (word_t *)FUN_00351db4();
            x20 = s20; x22 = s22; x24 = s24;
            if (is_twelve || ((long)child < 1)) {
                return 0;
            }
            break;                          /* re-dispatch loop */
        case 7:
            FUN_004ac0c0();
            r = FUN_0036b270(*(word_t *)(x8b + 0x10)).lo;
            FUN_0047cc98(r, 0);
            FUN_00351d18();
            FUN_0036b118();
            return (word_t)(x20 & 1);
        case 8:
            FUN_004ac0c0();
            FUN_004ac12c(/*&local_f0*/ (word_t)0);
            FUN_00117cc4();
            r = FUN_0049e2d4(/*&local_f0*/ (word_t)0);
            if (r == 3 || r == 4 || r == 6) {
                return 0;
            }
            return 1;
        case 10:
            FUN_004ac0c0();
            FUN_00359af8(*(word_t *)(x8e + 0x18));
            return (word_t)(x8f != 0);      /* extraout_x8_04 */
        case 12:
            desc = FUN_004ab98c(desc & 0xfffffffffffffffULL, 0);
            x20 = s20; x22 = s22; x24 = s24;
            break;                          /* re-dispatch loop */
        }
        continue;                           /* re-dispatch with new desc */
    }
walk_default:                               /* LAB_00477efc */
    if (count == idx) {
        goto ok1;                           /* LAB_00477fc0 -> return 1 */
    }
    if (*(word_t *)(child + 0x10) <= idx) {
        CL4_SWBP(0x4780d8);
    }
    FUN_004acc0c();
    r = sk_bcg_00477e8c(x20);
    FUN_0036b118(x20 & x22);
    idx = x24;
    if ((r & 1) == 0) {
fail0:                                      /* LAB_00477f30 */
        FUN_0036b118(child);
        return 0;
    }
    goto walk_default;
walk_case1:                                 /* LAB_00477f8c */
    for (;;) {
        if (*(word_t *)(child + 0x10) <= idx) {
            CL4_SWBP(0x4780dc);
        }
        FUN_004acc0c();
        r = sk_bcg_00477e8c(x20);
        FUN_0036b118(x20 & x22);
        idx = x24;
        if ((r & 1) != 0) {
            break;
        }
        if (count == idx) {
            goto fail0;                     /* return 0 */
        }
    }
ok1:                                        /* LAB_00477fc0 */
    FUN_0036b118(child);
    return 1;
}

/* FUN_00478110 @ 0x00478110   (est. sk_bcg_00478110)
 * Ghidra: void sk_bcg_00478110(undefined8,undefined8,ulong)
 * Builds a character-class bitmask (two 64-bit accumulator words bitLo/bitHi,
 * merged into local_708/local_710) for a parsed regex AST element at
 * elemP (a 0x160-byte element in the vector vecH). Elements of kind 3
 * (from FUN_0049df0c) are escaped/char-literal runs whose codepoints are
 * decoded via FUN_003548dc/FUN_002a0cf8/FUN_002bd848/FUN_0034ecc8 and
 * case-folded (0x20/0x40/0x61 offsets, 0x7f sentinel) into bitmap bits;
 * other kinds route through a rich kind/representation switch
 * (FUN_00458af8/FUN_00458b14 classification, FUN_0049e2f0 unwrap) that
 * accumulates the same two words. Returns via FUN_0008e500(flg, acc,
 * acc, x30). Dozens of fail-closed SWBP traps on malformed ranges.
 * Confidence: medium   Notes: largest function in the part; many stack
 * buffers and register artifacts (extraout_x1, unaff_x23, unaff_x30). */
static void sk_bcg_00478110(word_t vec, word_t val, word_t flag)
{
    wpair_t pair;           /* auVar26 - 16-byte returns */
    word_t *vecH;         /* pair.hi - element vector pointer */
    word_t baseL;          /* pair.lo - element base */
    word_t *elemP;         /* current element (0x160 stride) */
    word_t tagB;           /* baseL + 0x1c (tag base) */
    word_t el;          /* outer element index */
    word_t cnt;          /* element count */
    word_t flg;          /* case/flag accumulator */
    word_t accA, accB;      /* local_708 / local_710 merged bitmaps */
    word_t bitLo, bitHi;  /* per-codepoint bitmap words */
    word_t scv, swC, swE;   /* scratch */
    unsigned int lb, hb8, c32;  /* codepoint / range bounds */
    int    knd;           /* kind / classification result */
    bool   fl5, fl4, fl6;   /* flags */
    word_t x23;             /* unaff_x23 - implicit register (codepoint) */
    word_t x30;             /* unaff_x30 - implicit register */
    long   x1out;           /* extraout_x1 from FUN_0029fb80 */
    word_t bm_lo, bm_hi;   /* per-codepoint bitmaps */
    byte   flgbuf[8];    /* flag buffer */
    word_t b2c8, b168, b428, b6d8, b638;   /* opaque stack buffers */
    word_t c1, c2;          /* 16-byte value low/high halves */
    word_t wide_v;          /* FUN_004176bc result / FUN_00458af8 value */
    long   x8;              /* extraout_x8 */

    pair = FUN_0008e518();
    vecH = (word_t *)pair.hi;
    baseL = pair.lo;
    el = 0;
    accA = 0;
    accB = 0;
    flg = flag & 1;
    cnt = *(word_t *)(vecH + 0x10);
    tagB = baseL + 0x1c;
    for (;;) {
        /* ---- inner: walk elements until one is not kind 3 ---- */
        for (;;) {
            if (el == cnt) {
                FUN_0008e500(flg, accA, accB, x30);
                return;
            }
            if (*(word_t *)(vecH + 0x10) <= el) {
                CL4_SWBP(0x478a54);
            }
            elemP = (word_t *)(vecH + 0x20 / 8 + el * 0x160 / 8);
            FUN_004ab31c(b2c8);
            FUN_00117cc4();
            el = el + 1;
            FUN_004ab31c(b168);
            FUN_00117cc4();
            knd = FUN_0049df0c(b2c8);
            if (knd != 3) {
                break;
            }
            /* ---- kind 3: escaped/char-literal run ---- */
            FUN_0049df18(b168);
            FUN_004ab430();
            b638 = 0;
            FUN_004ab2e8();
            elemP = (word_t *)FUN_0049df18(b428);
            c1 = *(word_t *)(elemP + 8 / 8);
            FUN_004a3940(b2c8, flgbuf);
            thunk_FUN_0036b270(c1);
            bitLo = 0;
            bitHi = 0;
            for (;;) {
                FUN_0029fb80();
                if (x1out == 0) {           /* extraout_x1 */
                    break;
                }
                pair = FUN_003548dc();
                c1 = pair.lo;
                c2 = pair.hi;
                fl5 = (c1 == 0xa0d);
                fl4 = fl5 && (0xe1ffffffffffffffULL < c2);
                fl6 = fl5 && (c2 == 0xe200000000000000ULL);
                if (fl6) {
class_skip:                                 /* LAB_00478494 */
                    FUN_003a25d4(b638);
                    FUN_004a3918(b2c8);
                    goto merge_acc;         /* LAB_004784a4 */
                }
                FUN_00350aa0();
                FUN_004aa890();
                scv = FUN_002a0cf8();
                if ((scv & 1) != 0) {
                    goto class_skip;
                }
                FUN_00350aa0();
                FUN_004aa890();
                scv = FUN_002a0cf8();
                if ((scv & 1) == 0) {
                    FUN_00350aa0();
                    scv = FUN_002bd848();
                    if ((scv & 1) != 0) {
                        FUN_00350aa0();
                        FUN_0016749c();
                        scv = FUN_0034ecc8();
                        if (fl6) {
                            CL4_SWBP(0x478a74);
                        }
                        fl6 = ((scv & 0xffffff80ULL) == 0);
                        if (fl6) {
                            FUN_00350aa0();
                            FUN_0016749c();
                            x23 = FUN_0034ecc8();
                            if (fl6) {
                                CL4_SWBP(0x478a78);
                            }
                            FUN_003a25d4(b638);
                            fl6 = ((x23 & 0xffffff00ULL) == 0);
                            fl4 = 0;
                            if (!fl6) {
                                CL4_SWBP(0x478a4c);
                            }
                            goto codept;    /* LAB_00478408 */
                        }
                    }
                    goto class_skip;
                }
                FUN_003a25d4(b638);
                x23 = 10;
codept:                                     /* LAB_00478408 */
                if (*(long *)(baseL + 0x10) == 0) {
                    CL4_SWBP(0x478a48);
                }
                lb = *(unsigned int *)(tagB + *(long *)(baseL + 0x10) * 4);
                bm_lo = 0;
                bm_hi = 0;
                flgbuf[0] = (byte)(flag & 1);
                FUN_004950f0(x23);
                if ((lb & 1) != 0) {
                    lb = (unsigned int)x23;
                    FUN_004ac7ec(lb - 0x40);
                    if (fl4 && !fl6) {
                        FUN_004ac7ec(lb - 0x61);
                        if (fl4) {
                            goto done_codept;   /* LAB_00478460 */
                        }
                        lb = lb - 0x20;
                    } else {
                        lb = lb | 0x20;
                    }
                    FUN_004950f0(lb);
                }
done_codept:                                /* LAB_00478460 */
                if (((unsigned int)flag & 1) != (unsigned int)flgbuf[0]) {
                    CL4_SWBP(0x478a50);
                }
                bitLo = bm_lo | bitLo;
                bitHi = bm_hi | bitHi;
            }
            FUN_004a3918(b2c8);
            FUN_004a3918(b2c8);
merge_acc:                                  /* LAB_00478850 */
            if (flg != 2) {
                if (((unsigned int)flag & 1) != ((unsigned int)flg & 1)) {
                    CL4_SWBP(0x478a70);
                }
                accA = bitLo | accA;
                accB = bitHi | accB;
                flg = flg & 1;
            }
        }
        /* ---- element is not kind 3 ---- */
        fl6 = (knd == 1);
        if (fl6) {
            FUN_004ac1a4(b168);
            FUN_004ab0f0(b638);
            FUN_00117cc4();
            knd = FUN_004ac210(elemP);
            if (fl6) {
                x23 = FUN_0049e2f0(b638);
                FUN_004ac634(b6d8);
                knd = FUN_00458af8(x23);
                fl6 = (knd == 4);
                if (fl6) {
                    wide_v = *(word_t *)FUN_00458b14(b6d8);   /* byte */
                    FUN_004ab2e8();
                    FUN_0049df18(b428);
                    FUN_004aad6c();
                    FUN_004176bc(wide_v);
                    lb = (unsigned int)FUN_0034ecc8();
                    if (fl6) {
                        goto merge_acc;
                    }
cls_7f:                                     /* LAB_004785d8 */
                    fl6 = (lb == 0x7f);
                    if (lb < 0x80) {
                        goto range_2;       /* LAB_00478694 */
                    }
                } else {
                    if (knd == 1) {
                        lb = *(unsigned int *)FUN_00458b14(b6d8);
                        FUN_004ab2e8();
                        FUN_0049df18(b428);
                        FUN_004aad6c();
                        goto cls_7f;
                    }
                    FUN_004ab2e8();
                    FUN_0049df18(b428);
                    FUN_004aad6c();
                }
                FUN_004ac634(b428);
                knd = FUN_00458af8(x23);
                if (knd == 0) {
                    c1 = *(word_t *)FUN_00458b14(b428);
                    x23 = c1;
                    fl6 = (c1 == 0xa0d) &&
                            (*(word_t *)(FUN_00458b14(b428) + 8) == 0xe200000000000000ULL);
                    if (c1 != 0xa0d ||
                        (*(word_t *)(FUN_00458b14(b428) + 8) != 0xe200000000000000ULL)) {
                        FUN_0035145c();
                        FUN_004aa890();
                        scv = FUN_002a0cf8();
                        if ((scv & 1) == 0) {
                            FUN_0035145c();
                            FUN_002bd8f0();
                            lb = (unsigned int)FUN_00466214();
                            if (!fl6) {
                                lb = lb & 0xff;
                                goto range_2;
                            }
                        }
                    }
                }
                goto merge_acc;
            }
            if (knd == 1) {
                lb = *(unsigned int *)FUN_0049e2f0(b638);
                fl6 = (lb == 0x80);
                if (lb < 0x80) {
                    FUN_004ab2e8();
                    FUN_0049df18(b428);
                    FUN_004aad6c();
                    goto range_2;
                }
            } else if (knd == 0) {
                c1 = *(word_t *)FUN_0049e2f0(b638);
                x23 = c1;
                fl6 = (c1 == 0xa0d) &&
                        (*(word_t *)(FUN_0049e2f0(b638) + 8) == 0xe200000000000000ULL);
                if (fl6) {
                    goto reset_acc;         /* LAB_004784ac */
                }
                FUN_0035145c();
                FUN_004aa890();
                scv = FUN_002a0cf8();
                if ((scv & 1) != 0) {
                    goto reset_acc;
                }
                FUN_0035145c();
                FUN_004aa890();
                scv = FUN_002a0cf8();
                if ((scv & 1) == 0) {
                    FUN_004ab2e8();
                    FUN_0049df18(b428);
                    FUN_004aad6c();
                    FUN_0035145c();
                    scv = FUN_002bd848();
                    if ((scv & 1) != 0) {
                        FUN_0035145c();
                        FUN_0016749c();
                        scv = FUN_0034ecc8();
                        if (fl6) {
                            CL4_SWBP(0x478a7c);
                        }
                        fl6 = ((scv & 0xffffff80ULL) == 0);
                        if (fl6) {
                            FUN_0035145c();
                            FUN_0016749c();
                            lb = (unsigned int)FUN_0034ecc8();
                            if (fl6) {
                                CL4_SWBP(0x478a88);
                            }
                            fl6 = ((lb & 0xffffff00ULL) == 0);
                            if (!fl6) {
                                CL4_SWBP(0x478a64);
                            }
                            lb = lb & 0xff;
                            goto range_2;
                        }
                    }
                    goto merge_acc;
                }
                FUN_004ab2e8();
                FUN_0049df18(b428);
                FUN_004aad6c();
                lb = 10;
range_2:                                    /* LAB_00478694 */
                FUN_004ac52c(b428);
                knd = FUN_004ac210(elemP + 0xb0 / 8);
                if (!fl6) {
                    fl6 = (knd == 1);
                    if (fl6) {
                        hb8 = *(unsigned int *)FUN_0049e2f0(b428);
                        FUN_004a3918(b2c8);
                        if (hb8 < 0x80) {
                            goto bitmap_range;   /* LAB_00478934 */
                        }
                        goto reset_acc;
                    }
                    if (knd != 0) {
                        goto merge_acc;
                    }
                    FUN_0049e2f0(b428);
                    FUN_004ac7f8();
                    fl6 = (fl6 && x23 == 0xe200000000000000ULL);
                    if (fl6) {
                        goto merge_acc;
                    }
                    FUN_00351450();
                    FUN_004aa890();
                    scv = FUN_002a0cf8();
                    if ((scv & 1) != 0) {
                        goto merge_acc;
                    }
                    FUN_00351450();
                    FUN_004aa890();
                    scv = FUN_002a0cf8();
                    if ((scv & 1) == 0) {
                        FUN_00351450();
                        scv = FUN_002bd848();
                        if ((scv & 1) != 0) {
                            FUN_00351450();
                            FUN_0016749c();
                            scv = FUN_0034ecc8();
                            if (fl6) {
                                CL4_SWBP(0x478a8c);
                            }
                            fl6 = ((scv & 0xffffff80ULL) == 0);
                            if (fl6) {
                                FUN_00351450();
                                FUN_0016749c();
                                hb8 = (unsigned int)FUN_0034ecc8();
                                if (fl6) {
                                    CL4_SWBP(0x478a90);
                                }
                                FUN_004a3918(b2c8);
                                if ((hb8 & 0xffffff00ULL) != 0) {
                                    CL4_SWBP(0x478a6c);
                                }
                                hb8 = hb8 & 0xff;
                                goto bitmap_range;
                            }
                        }
                        goto merge_acc;
                    }
                    FUN_004a3918(b2c8);
                    hb8 = 10;
bitmap_range:                               /* LAB_00478934 */
                    if (*(long *)(baseL + 0x10) == 0) {
                        CL4_SWBP(0x478a5c);
                    }
                    if (hb8 < lb) {
                        CL4_SWBP(0x478a60);
                    }
                    bitHi = 0;
                    bitLo = 0;
                    scv = (word_t)lb;
                    for (;;) {
                        c32 = (unsigned int)scv;
                        lb = c32 & 0xff;
                        x23 = 0;
                        if ((char)scv > '?') {
                            x23 = 1ULL << (scv & 0x3f);
                        }
                        x23 = x23 | bitHi;
                        if (scv < 0x40) {
                            bitLo = bitLo | (1ULL << (scv & 0x3f));
                            x23 = bitHi;
                        }
                        bitHi = x23;
                        if ((*(unsigned int *)(tagB + *(long *)(baseL + 0x10) * 4) & 1) != 0) {
                            if ((lb - 0x61) < 0x1a) {
                                bitHi = x23 | (1ULL << ((word_t)(c32 + 0xa0) & 0x3f));
                            }
                            if ((lb - 0x40) < 0x1b) {
                                bitHi = x23 | (1ULL << ((word_t)(c32 + 0xe0) & 0x3f));
                            }
                        }
                        if (hb8 == scv) {
                            break;
                        }
                        scv = scv + 1;
                        if (lb == 0xff) {
                            CL4_SWBP(0x478a44);
                        }
                    }
                    goto merge_acc;
                }
                /* second branch of LAB_00478694: fl6 true */
                x23 = FUN_0049e2f0(b428);
                FUN_004ac634(flgbuf);
                knd = FUN_00458af8(x23);
                fl6 = (knd == 4);
                if (fl6) {
                    hb8 = (unsigned int)FUN_004176bc(*(word_t *)FUN_00458b14(flgbuf));
                    FUN_0034ecc8();
                    if (fl6) {
                        goto merge_acc;
                    }
cls_wide:                                   /* LAB_004788c0 */
                    fl6 = (hb8 == 0x7f);
                    if (hb8 < 0x80) {
                        FUN_004a3918(b2c8);
                        goto bitmap_range;
                    }
                } else {
                    fl6 = false;
                    if (knd == 1) {
                        hb8 = *(unsigned int *)FUN_00458b14(flgbuf);
                        goto cls_wide;
                    }
                }
                FUN_004ac634(b6d8);
                knd = FUN_00458af8(x23);
                if (knd == 0) {
                    FUN_00458b14(b6d8);
                    FUN_004ac7f8();
                    if (!fl6 || x23 != 0xe200000000000000ULL) {
                        FUN_00351450();
                        FUN_004aa890();
                        scv = FUN_002a0cf8();
                        if ((scv & 1) == 0) {
                            FUN_00351450();
                            hb8 = (unsigned int)FUN_002bd8f0();
                            FUN_004a3918(b2c8);
                            if ((hb8 & 0xff00) == 0x100) {
                                goto reset_acc;
                            }
                            hb8 = hb8 & 0xff;
                            goto bitmap_range;
                        }
                    }
                }
                goto merge_acc;
            }
            goto reset_acc;                 /* fallthrough for knd==1 path */
        } else {
            /* knd != 1 */
            if (knd != 0) {
                goto reset_acc;
            }
            FUN_004ac1a4(b168);
            FUN_004ab0f0(flgbuf);
            FUN_00117cc4();
            knd = FUN_004ac210(elemP);
            if (!fl6) {
                fl6 = (knd == 1);
                if (fl6) {
                    scv = (word_t)*(unsigned int *)FUN_0049e2f0(flgbuf);
                    if (*(unsigned int *)FUN_0049e2f0(flgbuf) < 0x80) {
                        goto lowbit;        /* LAB_00478808 */
                    }
                } else if (knd == 0) {
                    FUN_0049e2f0(flgbuf);
                    FUN_004ac7f8();
                    fl6 = (fl6 && x23 == 0xe200000000000000ULL);
                    if (fl6) {
                        goto reset_acc;
                    }
                    FUN_00351450();
                    FUN_004aa890();
                    scv = FUN_002a0cf8();
                    if ((scv & 1) != 0) {
                        goto reset_acc;
                    }
                    FUN_00351450();
                    FUN_004aa890();
                    scv = FUN_002a0cf8();
                    if ((scv & 1) == 0) {
                        FUN_004ab2e8();
                        swC = FUN_0049df18(b428);
                        FUN_004a36c4(swC, b638);
                        FUN_00351450();
                        scv = FUN_002bd848();
                        if ((scv & 1) != 0) {
                            FUN_00351450();
                            FUN_0016749c();
                            scv = FUN_0034ecc8();
                            if (fl6) {
                                CL4_SWBP(0x478a80);
                            }
                            fl6 = ((scv & 0xffffff80ULL) == 0);
                            if (fl6) {
                                FUN_00351450();
                                FUN_0016749c();
                                scv = FUN_0034ecc8();
                                if (fl6) {
                                    CL4_SWBP(0x478a84);
                                }
                                FUN_004a3918(b2c8);
                                if ((scv & 0xffffff00ULL) != 0) {
                                    CL4_SWBP(0x478a68);
                                }
                                goto lowbit;
                            }
                        }
                        goto merge_acc;
                    }
                    scv = 10;
                    goto lowbit;
                }
                goto reset_acc;
            }
            swC = FUN_0049e2f0(flgbuf);
            FUN_00465258(b6d8);
            knd = FUN_00458af8(swC);
            fl6 = (knd == 4);
            if (fl6) {
                x23 = (word_t)*(byte *)FUN_00458b14(b6d8);
                FUN_004ab2e8();
                swE = FUN_0049df18(b428);
                FUN_004a36c4(swE, b638);
                FUN_004176bc(x23);
                scv = FUN_0034ecc8();
                if (fl6) {
                    goto merge_acc;
                }
cls_w2:                                     /* LAB_00478618 */
                fl6 = ((unsigned int)scv == 0x7f);
                x23 = scv;
                if (0x7f < (unsigned int)scv) {
                    goto wide_2;            /* LAB_004787ac */
                }
                FUN_004a3918(b2c8);
lowbit:                                     /* LAB_00478808 */
                if (*(long *)(baseL + 0x10) == 0) {
                    CL4_SWBP(0x478a58);
                }
                lb = (unsigned int)scv;
                if ((lb & 0xff) < 0x40) {
                    bitHi = 0;
                    bitLo = 1ULL << (scv & 0x3f);
                    goto merge_acc;
                }
                if ((char)scv < '@') {
                    bitHi = 0;
                } else {
                    bitHi = 1ULL << ((word_t)(lb - 0x40) & 0x3f);
                    if ((*(unsigned int *)(tagB + *(long *)(baseL + 0x10) * 4) & 1) != 0) {
                        fl5 = (0x5a < (lb & 0xff));
                        if (fl5) {
                            FUN_004ac7ec(lb - 0x61);
                            if (fl5) {
                                goto low_clear;   /* LAB_0047884c */
                            }
                            knd = -0x60;
                        } else {
                            knd = -0x20;
                        }
                        bitLo = 0;
                        bitHi = bitHi | (1ULL << ((word_t)(lb + knd) & 0x3f));
                        goto merge_acc;
                    }
                }
low_clear:                                  /* LAB_0047884c */
                bitLo = 0;
                goto merge_acc;
            }
            fl6 = (knd == 1);
            if (fl6) {
                scv = (word_t)*(unsigned int *)FUN_00458b14(b6d8);
                FUN_004ab2e8();
                swE = FUN_0049df18(b428);
                FUN_004a36c4(swE, b638);
                goto cls_w2;
            }
            FUN_004ab2e8();
            swE = FUN_0049df18(b428);
            FUN_004a36c4(swE, b638);
wide_2:                                     /* LAB_004787ac */
            FUN_00465258(b428);
            knd = FUN_00458af8(swC);
            if (knd == 0) {
                FUN_00458b14(b428);
                FUN_004ac7f8();
                if (!fl6 || x23 != 0xe200000000000000ULL) {
                    FUN_00351450();
                    FUN_004aa890();
                    scv = FUN_002a0cf8();
                    if ((scv & 1) == 0) {
                        FUN_00351450();
                        scv = FUN_002bd8f0();
                        FUN_004a3918(b2c8);
                        if (((unsigned int)scv & 0xff00) == 0x100) {
                            goto reset_acc;
                        }
                        goto lowbit;
                    }
                }
            }
        }
merge_acc2:                                 /* LAB_004784a4 */
        FUN_004a3918(b2c8);
reset_acc:                                  /* LAB_004784ac */
        accA = 0;
        accB = 0;
        flg = 2;
    }
}

/* ==================== SKR27 function bodies ==================== */



/* Extra out-of-part/out-of-slice callees used by these functions. */
extern word_t thunk_FUN_002acbb8();
extern wpair_t thunk_FUN_002b74c0();
extern word_t DAT_0060e208;
extern word_t DAT_00611b24;
extern word_t LAB_00611b34;
extern word_t thunk_FUN_0036b270();
extern word_t thunk_FUN_0044f818();


/* FUN_00478a98 @ 0x00478a98   (est. sk_bcg_00478a98)
 * Ghidra: void sk_bcg_00478a98(void)
 * Top-level bytecode-generation dispatcher for the regex AST list held at
 * (root+0x10). Reads each element (0x160-byte nodes at root+0x20) and, based
 * on the element kind tag from FUN_0049df0c, emits the corresponding
 * bytecode via kind-specific emitters (character, custom-character,
 * flattening, etc.). After consuming the whole list it walks the generated
 * node stream (tag 0/1/3/4 elements) and stitches them into the output
 * instruction buffer with bounds/overlap checks. Handles are reference-counted.
 * Confidence: medium   Notes: many out-of-slice callees; DAT_006577e0/segname
 * globals via section_00000158; SWBP checks at 0x4795xx. */
static void sk_bcg_00478a98(void)
{
    wpair_t root_pair;
    word_t lVar21;
    word_t lVar18;
    word_t *unaff_x20;      /* extraout/x-reg artifacts */
    word_t unaff_x21, unaff_x25;
    word_t lVar11, lVar13;
    word_t uVar14, uVar15, uVar20, uVar23, uVar17;
    word_t uVar7;           /* element-kind tag from switch */
    word_t local_640;
    word_t lVar22;
    unsigned char local_638;
    word_t local_430;
    unsigned char unaff_w28;
    int iVar8;
    unsigned char uVar4, uVar5;
    word_t uVar6;
    unsigned char auVar24[16], auVar25[16];
    word_t auStack_2c8[44];
    unsigned char auStack_428[352];
    unsigned char auStack_168[360];
    word_t local_4e0[22];

    auVar24[0] = (unsigned char)FUN_0008e518();   /* 16-byte x0:x1 */
    lVar21 = *(word_t *)(*(word_t *)&auVar24[0] + 0x10);
    FUN_000a6f68();
    local_430 = extraout_x8;
    lVar18 = extraout_x8;
    if (lVar21 != 0) {
        unaff_x20 = local_4e0;
        local_4e0[0] = extraout_x8;
        FUN_004ab448();
        FUN_0049a550();
        lVar18 = local_4e0[0];
        do {
            FUN_004ac360(auStack_2c8);
            FUN_00117cc4();
            FUN_004ac360(auStack_168);
            FUN_00117cc4();
            uVar6 = FUN_0049df0c(auStack_2c8);
            uVar7 = (uint)unaff_x21;
            switch (uVar6) {
            default:
                FUN_004ac520();
                auStack_2c8[0] = uVar6;   /* puVar16 = auStack_2c8 */
                goto label_b38;
            case 2:
                FUN_0049df18(auStack_168);
                plVar9 = (word_t *)FUN_004ac7d4();
                if (extraout_x9 == 0) {
                    CL4_SWBP(0x47956c);
                }
                unaff_x20 = (word_t *)*plVar9;
                lVar11 = plVar9[1];
                FUN_004ab55c();
                if ((extraout_w8 >> 0x10 & 1) == 0) {
                    FUN_004ab278();
                    FUN_004ac034(auStack_428);
                    FUN_0036b270(unaff_x20);
                } else {
                    FUN_004ab278();
                    FUN_004ac034(auStack_428);
                    unaff_x20 = (word_t *)FUN_004acd08();
                }
                sk_bcg_00479c18(unaff_x20);
                FUN_004ac2d0();
                FUN_0036b118();
                FUN_004a3918(auStack_2c8);
                local_640 = unaff_x25;
                local_638 = (char)lVar11;
                FUN_004a3390(&local_640);
                auStack_2c8[0] = (word_t)&local_640;
label_b38:
                FUN_00117cc4(auStack_428, auStack_2c8[0], 0x160);
                goto label_dc0;
            case 5:
                FUN_0049df18(auStack_168);
                FUN_004ac7d4();
                if (extraout_x9_01 == 0) {
                    CL4_SWBP(0x479568);
                }
                FUN_004aaf08();
                if ((uVar7 >> 0x10 & 1) == 0) {
                    FUN_004ac520();
                    FUN_0036b270(unaff_x20);
                } else {
                    FUN_004ab278();
                    FUN_004ac034(auStack_428);
                    unaff_x20 = (word_t *)FUN_004acd08();
                }
                FUN_004ab18c();
                FUN_0036a940();
                FUN_004ac930();
                uVar15 = sk_bcg_00479c18();
                FUN_0036b118(unaff_x20);
                section_00000158.segname._8_8_ = uVar15;
                if ((uVar7 >> 0x10 & 1) == 0) {
                    section_00000158.addr._0_1_ = unaff_w28;
                    FUN_0036b270(unaff_x25);
                } else {
                    section_00000158.addr._0_1_ = unaff_w28;
                    unaff_x25 = FUN_004ac594();
                }
                unaff_x20 = (word_t *)sk_bcg_00479c18(unaff_x25);
                FUN_0036b118(unaff_x25);
                FUN_004ac508();
                local_640 = 0x160;
                FUN_004a32ec(&local_640);
                break;
            case 6:
                FUN_0049df18(auStack_168);
                FUN_004ac7d4();
                if (extraout_x9_02 == 0) {
                    CL4_SWBP(0x479560);
                }
                FUN_004aaf08();
                if ((uVar7 >> 0x10 & 1) == 0) {
                    FUN_004ac520();
                    FUN_0036b270(unaff_x20);
                } else {
                    FUN_004ab278();
                    FUN_004ac034(auStack_428);
                    unaff_x20 = (word_t *)FUN_004acd08();
                }
                FUN_004ab18c();
                FUN_0036a940();
                FUN_004ac930();
                uVar15 = sk_bcg_00479c18();
                FUN_0036b118(unaff_x20);
                section_00000158.segname._8_8_ = uVar15;
                if ((uVar7 >> 0x10 & 1) == 0) {
                    section_00000158.addr._0_1_ = unaff_w28;
                    FUN_0036b270(unaff_x25);
                } else {
                    section_00000158.addr._0_1_ = unaff_w28;
                    unaff_x25 = FUN_004ac594();
                }
                unaff_x20 = (word_t *)sk_bcg_00479c18(unaff_x25);
                FUN_0036b118(unaff_x25);
                FUN_004ac508();
                local_640 = 0x160;
                FUN_004a3318(&local_640);
                break;
            case 7:
                FUN_0049df18(auStack_168);
                FUN_004ac7d4();
                if (extraout_x9_00 == 0) {
                    CL4_SWBP(0x479564);
                }
                FUN_004aaf08();
                if ((uVar7 >> 0x10 & 1) == 0) {
                    FUN_004ac520();
                    FUN_0036b270(unaff_x20);
                } else {
                    FUN_004ab278();
                    FUN_004ac034(auStack_428);
                    unaff_x20 = (word_t *)FUN_004acd08();
                }
                FUN_004ab18c();
                FUN_0036a940();
                FUN_004ac930();
                uVar15 = sk_bcg_00479c18();
                FUN_0036b118(unaff_x20);
                section_00000158.segname._8_8_ = uVar15;
                if ((uVar7 >> 0x10 & 1) == 0) {
                    section_00000158.addr._0_1_ = unaff_w28;
                    FUN_0036b270(unaff_x25);
                } else {
                    section_00000158.addr._0_1_ = unaff_w28;
                    unaff_x25 = FUN_004ac594();
                }
                unaff_x20 = (word_t *)sk_bcg_00479c18(unaff_x25);
                FUN_0036b118(unaff_x25);
                FUN_004ac508();
                local_640 = 0x160;
                FUN_004a32c4(&local_640);
            }
            FUN_00117cc4(auStack_428, &local_640, 0x160);
label_dc0:
            unaff_x21 = *(word_t *)(lVar18 + 0x10);
            unaff_x25 = unaff_x21 + 1;
            local_4e0[0] = lVar18;
            if (*(word_t *)(lVar18 + 0x18) >> 1 <= unaff_x21) {
                uVar15 = FUN_0006b42c();
                unaff_x20 = local_4e0;
                FUN_0049a550(uVar15, unaff_x25, 1);
            }
            *(word_t *)(local_4e0[0] + 0x10) = unaff_x25;
            FUN_00117cc4(local_4e0[0] + unaff_x21 * 0x160 + 0x20, auStack_428, 0x160);
            lVar21 = lVar21 + -1;
            lVar18 = local_4e0[0];
        } while (lVar21 != 0);
        FUN_000a6f68();
        local_430 = extraout_x8_00;
    }
    lVar21 = 0;
    if (*(word_t *)(lVar18 + 0x10) == 0) {
label_9510:
        FUN_0036b118(lVar18);
label_9518:
        FUN_0008e500(local_430, auVar24[8]);
        return;
    }
    bVar2 = false;
    uVar20 = 0;
    uVar23 = *(word_t *)(lVar18 + 0x10) - 1;
    FUN_00466244();
    lVar11 = 0x687e28;
    lVar22 = 0x20;
    uVar14 = extraout_x8_01;
    do {
        if (uVar14 <= uVar20) {
            CL4_SWBP(0x479538);
        }
        FUN_00117cc4(auStack_2c8, lVar18 + lVar22, 0x160);
        FUN_00117d14(auStack_168, lVar18 + lVar22, 0x160);
        uVar7 = FUN_0049df0c(auStack_2c8);
        if (uVar7 < 5) {
            uVar4 = 3 < uVar7;
            uVar5 = uVar7 == 4;
            switch (uVar7) {
            default:
                FUN_004ac1a4(auStack_168);
                FUN_004ab0f0(local_4e0);
                FUN_00117cc4();
                iVar8 = FUN_0049e2d4(unaff_x20);
                uVar4 = iVar8 != 0;
                uVar5 = iVar8 == 1;
                if (uVar5) {
                    FUN_0049e2f0(local_4e0);
                    FUN_004abc0c();
                    if (uVar4 && !uVar5) {
                        FUN_004ac150();
                        if (uVar4) {
                            FUN_00463bd4();
                            FUN_004aace0();
                        } else {
                            FUN_004ab164();
                        }
                    }
                    FUN_004ac72c();
                    FUN_004ac720();
                    FUN_004ab278();
                    uVar15 = FUN_0049df18(auStack_428);
                    FUN_004a36c4(uVar15, &local_640);
                    FUN_004abcb4();
                    FUN_00294cb4();
                    uVar15 = extraout_x1;
                } else {
                    if (iVar8 != 0) {
                        FUN_004ab278();
                        uVar15 = FUN_0049df18(auStack_428);
                        FUN_004a36c4(uVar15, &local_640);
                        goto label_8fec;
                    }
                    lVar13 = FUN_0049e2f0(local_4e0);
                    uVar15 = *(word_t *)(lVar13 + 8);
                    FUN_004ab278();
                    uVar10 = FUN_0049df18(auStack_428);
                    FUN_004a3940(auStack_2c8, &local_640);
                    FUN_004a36c4(uVar10, &local_640);
                }
                lVar13 = *(word_t *)(lVar11 + 0x10);
                uVar14 = FUN_003a261c(lVar11);
                if ((uVar14 & 1) == 0) {
                    lVar11 = FUN_00457a88(lVar11);
                }
                if (lVar13 == 0) {
                    CL4_SWBP(0x479558);
                }
                FUN_004abea0();
                if (uVar4 && !uVar5) {
                    CL4_SWBP(0x47955c);
                }
                unaff_x20 = (word_t *)(extraout_x8_04 + lVar13 * 0x10);
                FUN_00350a70();
                thunk_FUN_002acbb8();
                FUN_003a25d4(uVar15);
                FUN_004a3918(auStack_2c8);
                break;
            case 1:
                lVar13 = FUN_0049df18(auStack_168);
                FUN_00117cc4(local_4e0, lVar13, 0xb0);
                iVar8 = FUN_0049e2d4(lVar13);
                uVar4 = iVar8 != 0;
                uVar5 = iVar8 == 1;
                if (uVar5) {
                    FUN_0049e2f0(local_4e0);
                    FUN_004abc0c();
                    if (uVar4 && !uVar5) {
                        FUN_004ac150();
                        if (uVar4) {
                            FUN_00463bd4();
                            FUN_004aace0();
                        } else {
                            FUN_004ab164();
                        }
                    }
                    FUN_004ac72c();
                    FUN_004ac720();
                    FUN_004ab278();
                    uVar15 = FUN_0049df18(auStack_428);
                    FUN_004aae98(uVar15, &local_640);
                    FUN_004abcb4();
                    FUN_00294cb4();
                    uVar15 = extraout_x1_00;
                } else {
                    if (iVar8 != 0) {
                        FUN_004ab278();
                        uVar15 = FUN_0049df18(auStack_428);
                        FUN_004aae98(uVar15, &local_640);
                        goto label_8fec;
                    }
                    lVar19 = FUN_0049e2f0(local_4e0);
                    uVar15 = *(word_t *)(lVar19 + 8);
                    FUN_004ac520();
                    FUN_004a36c4(lVar13, auStack_428);
                }
                FUN_00117cc4(auStack_428, lVar13 + 0xb0, 0xb0);
                iVar8 = FUN_0049e2d4(lVar13 + 0xb0);
                uVar4 = iVar8 != 0;
                uVar5 = iVar8 == 1;
                if (uVar5) {
                    FUN_0049e2f0(auStack_428);
                    FUN_004abc0c();
                    if (uVar4 && !uVar5) {
                        uVar4 = 0x7ff < extraout_w8_00;
                        uVar5 = extraout_w8_00 == 0x800;
                        if (uVar4) {
                            FUN_00463bd4();
                            FUN_004aace0();
                        } else {
                            FUN_004ab164();
                        }
                    }
                    uVar10 = FUN_004ac72c();
                    FUN_004ac720(uVar10, extraout_w10 - (extraout_w9 >> 3));
                    local_640 = extraout_x13 + (extraout_x8_05 & 0xffffffff) &
                                (extraout_x9_03 ^ 0xffffffffffffffff);
                    auVar25[0] = (unsigned char)FUN_00294cb4(&local_640);
                } else {
                    if (iVar8 != 0) {
                        FUN_003a25d4(uVar15);
                        goto label_8fec;
                    }
                    pauVar12 = (unsigned char (*)[16])FUN_0049e2f0(auStack_428);
                    auVar25[0] = pauVar12[0][0];
                    FUN_00117cc4(&local_640, lVar13 + 0xb0, 0xb0);
                    FUN_004acd14(&local_640);
                }
                lVar13 = *(word_t *)(lVar11 + 0x10);
                uVar14 = FUN_003a261c(lVar11);
                if ((uVar14 & 1) == 0) {
                    lVar11 = FUN_00457a88(lVar11);
                }
                if (lVar13 == 0) {
                    CL4_SWBP(0x479570);
                }
                FUN_004abea0();
                if (uVar4 && !uVar5) {
                    CL4_SWBP(0x479574);
                }
                FUN_00350ab8();
                thunk_FUN_002acbb8();
                FUN_003a25d4(uVar15);
                uVar14 = *(word_t *)(lVar11 + 0x10);
                unaff_x20 = (word_t *)(uVar14 + 1);
                if (*(word_t *)(lVar11 + 0x18) >> 1 <= uVar14) {
                    FUN_000ec004();
                    lVar11 = FUN_00072c0c();
                }
                *(word_t **)(lVar11 + 0x10) = unaff_x20;
                *(unsigned char (*)[16])(lVar11 + uVar14 * 0x10 + 0x20) = auVar25;
                FUN_004a3918(auStack_2c8);
                break;
            case 2:
                goto label_8ea8_case2;
            case 3:
                FUN_0049df18(auStack_168);
                lVar19 = *(word_t *)(lVar11 + 0x10);
                FUN_004ab278();
                lVar13 = FUN_0049df18(auStack_428);
                thunk_FUN_0036b270(*(word_t *)(lVar13 + 8));
                uVar14 = FUN_003a261c(lVar11);
                if ((uVar14 & 1) == 0) {
                    lVar11 = FUN_00457a88(lVar11);
                }
                if (lVar19 == 0) {
                    CL4_SWBP(0x479548);
                }
                FUN_004abea0();
                if (uVar4 && !uVar5) {
                    CL4_SWBP(0x479550);
                }
                unaff_x20 = (word_t *)(extraout_x8_02 + lVar19 * 0x10);
                FUN_000e72b0();
                thunk_FUN_002acbb8();
                FUN_004a3918(auStack_2c8);
                break;
            case 4:
                lVar13 = *(word_t *)(lVar11 + 0x10);
                if (lVar13 == 0) {
                    CL4_SWBP(0x47954c);
                }
                FUN_00359af8(((word_t *)(lVar11 + 0x10))[lVar13 * 2 + 1]);
                if (extraout_x8_03 != 0) break;
                FUN_004ab278();
                lVar13 = FUN_0049df18(auStack_428);
                thunk_FUN_0036b270(*(word_t *)(lVar13 + 8));
                goto label_8fec;
            }
            if (uVar23 == uVar20) {
                FUN_0036b118(lVar18);
                uVar15 = sk_bcg_004795b0(lVar11);
                FUN_0036b118(lVar11);
                FUN_0049a644(uVar15);
                goto label_9518;
            }
            bVar2 = true;
        } else {
label_8ea8_case2:
            FUN_004ac520();
label_8fec:
            if (bVar2) {
                lVar13 = sk_bcg_004795b0(lVar11);
                FUN_0036b118(lVar11);
                uVar14 = *(word_t *)(lVar13 + 0x10);
                lVar11 = *(word_t *)(lVar21 + 0x10) + uVar14;
                if (SCARRY8(*(word_t *)(lVar21 + 0x10), uVar14)) {
                    CL4_SWBP(0x47953c);
                }
                uVar15 = FUN_003a261c(lVar21);
                if (((int)uVar15 == 0) || (uVar17 = *(word_t *)(lVar21 + 0x18) >> 1, (long)uVar17 < lVar11)) {
                    lVar19 = *(word_t *)(lVar21 + 0x10);
                    if (*(word_t *)(lVar21 + 0x10) <= lVar11) {
                        lVar19 = lVar11;
                    }
                    lVar21 = FUN_00498e50(uVar15, lVar19, 1, lVar21, FUN_00498328, &LAB_0049853c, FUN_00499a0c);
                    uVar17 = *(word_t *)(lVar21 + 0x18) >> 1;
                }
                uVar17 = uVar17 - *(word_t *)(lVar21 + 0x10);
                if ((long)uVar17 < 0) {
                    CL4_SWBP(0x479540);
                }
                if (*(word_t *)(lVar13 + 0x10) == 0) {
                    FUN_0036b118(lVar13);
                    if (uVar14 != 0) {
                        CL4_SWBP(0x479544);
                    }
                } else {
                    if (uVar17 < uVar14) {
                        CL4_SWBP(0x479554);
                    }
                    uVar17 = lVar21 + *(word_t *)(lVar21 + 0x10) * 0x160 + 0x20;
                    uVar1 = lVar13 + 0x20;
                    if (uVar1 < uVar17 + uVar14 * 0x160 && uVar17 < uVar1 + uVar14 * 0x160) {
                        CL4_SWBP(0x47957c);
                    }
                    FUN_0035b67c(uVar17, uVar1, uVar14, 0x686868);
                    FUN_0036b118(lVar13);
                    if (uVar14 != 0) {
                        if (SCARRY8(*(word_t *)(lVar21 + 0x10), uVar14)) {
                            CL4_SWBP(0x479578);
                        }
                        *(word_t *)(lVar21 + 0x10) = *(word_t *)(lVar21 + 0x10) + uVar14;
                    }
                }
                lVar11 = 0x687e28;
            }
            uVar14 = FUN_003a261c(lVar21);
            if ((uVar14 & 1) == 0) {
                FUN_004aa44c(*(word_t *)(lVar21 + 0x10));
                FUN_0006b3f4();
                lVar21 = FUN_00498e50();
            }
            uVar14 = *(word_t *)(lVar21 + 0x10);
            unaff_x20 = (word_t *)(uVar14 + 1);
            if (*(word_t *)(lVar21 + 0x18) >> 1 <= uVar14) {
                uVar15 = FUN_0006b42c();
                lVar21 = FUN_00498e50(uVar15, unaff_x20, 1, lVar21, FUN_00498328, &LAB_0049853c, FUN_00499a0c);
            }
            *(word_t **)(lVar21 + 0x10) = unaff_x20;
            FUN_00117cc4(lVar21 + uVar14 * 0x160 + 0x20, auStack_2c8, 0x160);
            local_430 = lVar21;
            if (uVar23 == uVar20) {
                FUN_0036b118(lVar11);
                goto label_9510;
            }
            bVar2 = false;
        }
        uVar14 = *(word_t *)(lVar18 + 0x10);
        lVar22 = lVar22 + 0x160;
        uVar20 = uVar20 + 1;
    } while (true);
}


/* FUN_004795b0 @ 0x004795b0   (est. sk_bcg_004795b0)
 * Ghidra: void sk_bcg_004795b0(undefined8 param_1,undefined8 param_2,code *param_3,code *param_4)
 * Emits a sequence/backreference bytecode run: given an input handle and
 * start/end instruction pointers, it either (single-element fast path) builds
 * a fresh AST node from the input handle and appends one instruction, or
 * (general path) iterates the element list emitting per-element opcodes with
 * full tag/range bounds checks (SoftwareBreakpoint fail-closed) and extends
 * the destination node stream, copying 0x160-byte elements between lists.
 * Reference-counted throughout; ends with FUN_0008e500 teardown.
 * Confidence: medium   Notes: heavy indirect/out-of-slice callees; SWBP at
 * 0x479bf0..0x479c18; globals _DAT_004baeb0, uRam00000000004baeb8. */
static void sk_bcg_004795b0(word_t param_1, word_t param_2, word_t param_3, word_t param_4)
{
    wpair_t root_pair;
    wpair_t el_pair, r_pair, a_pair, b_pair, c_pair;
    word_t lVar7;
    word_t uVar16, uVar17, uVar1, uVar2, uVar3, uVar5, uVar8, uVar10, uVar12, uVar21;
    word_t uVar18;
    word_t lVar9;
    word_t *puVar19, *puVar22;
    word_t pcVar11, pcVar15, pcVar20, pcVar13, pcVar14, pcVar6;
    word_t uVar4;
    unsigned char local_428[11][16];
    unsigned char local_378[11][16];
    unsigned char auStack_2c8[176];
    unsigned char auStack_218[176];
    unsigned char local_168[22][16];
    word_t unaff_x28;

    root_pair.lo = FUN_0008e518();
    lVar7 = root_pair.lo;
    uVar16 = *(word_t *)(lVar7 + 0x10);
    if (uVar16 == 1) {
        uVar5 = FUN_004ab630();
        pcVar6 = FUN_0036a940(uVar5, 0x180, 7);
        uVar5 = _DAT_004baeb0;
        *(word_t *)(pcVar6 + 0x18) = uRam00000000004baeb8;
        *(word_t *)(pcVar6 + 0x10) = uVar5;
        local_168[0][0] = *(word_t *)(lVar7 + 0x20);
        uVar5 = *(word_t *)(lVar7 + 0x28);
        local_168[0][8] = uVar5;
        FUN_004a3340(local_168);
        FUN_004abb58(pcVar6 + 0x20);
        thunk_FUN_0036b270(uVar5);
    } else {
        c_pair = sk_bcg_00477338(1, lVar7);   /* 16-byte return */
        pcVar6 = c_pair.hi;
        uVar17 = param_4 >> 1;
        pcVar13 = param_3;
        pcVar14 = param_4;
        lVar7 = FUN_0036b270(lVar7).lo;
        puVar22 = (word_t *)(lVar7 + 0x38);
        uVar1 = param_4 >> 1;
        FUN_000a6fe0();
        puVar19 = extraout_x10;
        pcVar20 = param_3;
        for (uVar21 = 1; (b_pair.hi = pcVar20, b_pair.lo = unaff_x28,
            param_3 + (uVar21 - uVar1) != 1); uVar21 = uVar21 + 1) {
            if ((long)uVar17 <= (long)(param_3 + (uVar21 - 1))) {
                CL4_SWBP(0x479bf0);
            }
            if (uVar16 <= uVar21) {
                CL4_SWBP(0x479bf4);
            }
            uVar12 = puVar19[-1];
            uVar3 = *puVar19;
            uVar2 = puVar22[-1];
            uVar5 = *puVar22;
            FUN_003a25e0(uVar3, 2);
            thunk_FUN_0036b270(uVar5);
            if (uVar21 == 1) {
                pcVar15 = FUN_001ee018;
                FUN_003515d8(1);
                sk_bcg_004773a8();
                FUN_004acaa0();
                pcVar13 = param_4;
            } else {
                FUN_004ab248();
                FUN_003515d8(1);
                b_pair = sk_bcg_004730f0();
                pcVar15 = b_pair.hi;
                uVar8 = b_pair.lo;
                FUN_00351790();
                lVar9 = FUN_002b4120();
                uVar10 = lVar9 - 1;
                uVar4 = uVar10 == 0;
                if (SBORROW8(lVar9, 1)) {
                    CL4_SWBP(0x479bf8);
                }
                FUN_002b3f40(uVar8, uVar10 & ((long)uVar10 >> 0x3f ^ 0xffffffffffffffff), pcVar15, uVar8,
                            pcVar15, pcVar13, pcVar14);
                pcVar11 = FUN_00351db4().lo;
                pcVar20 = pcVar15;
                if (!uVar4) {
                    pcVar20 = pcVar11;
                }
                if (pcVar20 >> 0xe < uVar8 >> 0xe) {
                    CL4_SWBP(0x479bfc);
                }
                thunk_FUN_002b74c0(uVar8, pcVar20, uVar8, pcVar15, pcVar13, pcVar14);
                FUN_004acaa0();
                FUN_003a25d4(pcVar14);
            }
            pcVar11 = pcVar6;
            if ((b_pair.hi ^ b_pair.lo) < 0x4000) {
                FUN_003a25d4(pcVar13);
            } else {
                pcVar15 = pcVar13;
                a_pair = FUN_002a3e64(b_pair.hi, b_pair.lo, uVar21);
                FUN_003a25d4(pcVar13);
                uVar10 = FUN_003a261c(pcVar6);
                if ((uVar10 & 1) == 0) {
                    FUN_004aa44c(*(word_t *)(pcVar6 + 0x10));
                    FUN_0006b3f4();
                    pcVar11 = FUN_00498e50();
                    pcVar15 = pcVar6;
                }
                uVar10 = *(word_t *)(pcVar11 + 0x10);
                b_pair.hi = uVar10;
                b_pair.lo = a_pair.hi;
                if (*(word_t *)(pcVar11 + 0x18) >> 1 <= uVar10) {
                    FUN_0006b42c();
                    FUN_004ab0e0();
                    pcVar11 = FUN_00498e50();
                }
                local_168[0][0] = a_pair.lo;
                local_168[0][8] = a_pair.hi;
                FUN_004a3340(local_168);
                *(word_t *)(pcVar11 + 0x10) = uVar10 + 1;
                FUN_004abb58(pcVar11 + uVar10 * 0x160 + 0x20);
            }
            pcVar20 = b_pair.hi;
            unaff_x28 = b_pair.lo;
            uVar10 = uVar12 & 0xffffffffffff;
            if ((uVar3 & 0x2000000000000000) != 0) {
                uVar10 = uVar3 >> 0x38 & 0xf;
            }
            if (uVar10 == 0) {
                FUN_003a25d4(uVar3);
                CL4_SWBP(0x479c08);
            }
            uVar18 = (uint)(uVar12 >> 0x3b) & 1;
            if ((uVar3 & 0x1000000000000000) == 0) {
                uVar18 = 1;
            }
            uVar12 = 7;
            if (uVar18 == 0) {
                uVar12 = 0xb;
            }
            FUN_003515d8(uVar12 | uVar10 << 0x10);
            FUN_0029c058();
            FUN_003515d8();
            b_pair = FUN_00267510().lo;
            FUN_003a25d4(uVar3);
            FUN_0034eb74(uVar2 & 0xffffffffffff);
            if (extraout_x8 == 0) {
                FUN_003a25d4(uVar5);
                CL4_SWBP(0x479c14);
            }
            a_pair = FUN_00267510(0xf, extraout_x1, uVar5).lo;
            FUN_003a25d4(uVar5);
            uVar12 = FUN_003a261c(pcVar11);
            pcVar14 = pcVar15;
            pcVar6 = pcVar11;
            if ((uVar12 & 1) == 0) {
                FUN_004aa44c(*(word_t *)(pcVar11 + 0x10));
                FUN_0006b3f4();
                pcVar6 = FUN_00498e50();
                pcVar14 = pcVar11;
            }
            param_4 = *(word_t *)(pcVar6 + 0x10);
            if ((word_t)(*(word_t *)(pcVar6 + 0x18) >> 1) <= param_4) {
                uVar5 = FUN_0006b42c();
                FUN_00350774(uVar5, param_4 + 1);
                pcVar6 = FUN_00498e50();
            }
            local_428[0][0] = a_pair.lo;
            local_428[0][8] = a_pair.hi;
            FUN_0049ca44(local_428);
            local_378[0][0] = b_pair.lo;
            local_378[0][8] = b_pair.hi;
            FUN_0049ca44(local_378);
            FUN_00117cc4(auStack_2c8, local_378, 0xb0);
            FUN_00117cc4(auStack_218, local_428, 0xb0);
            pcVar13 = 0x160;
            FUN_00117cc4(local_168, auStack_2c8);
            FUN_004a3368(local_168);
            *(word_t *)(pcVar6 + 0x10) = param_4 + 1;
            FUN_004abb58(pcVar6 + param_4 * 0x160 + 0x20);
            puVar22 = puVar22 + 2;
            puVar19 = puVar19 + 2;
        }
        FUN_0036b118(c_pair.lo);
        c_pair = sk_bcg_00476d88(lVar7);
        lVar7 = c_pair.hi;
        uVar5 = c_pair.lo;
        if (lVar7 == 0) {
            CL4_SWBP(0x479c18);
        }
        FUN_004ab248(lVar7, uVar5, lVar7, uVar5);
        c_pair = sk_bcg_004730f0(1, uVar5, extraout_x8_00);
        if ((c_pair.lo ^ c_pair.hi) < 0x4000) {
            FUN_003a25d4(pcVar14);
        } else {
            c_pair = FUN_002a3e64().lo;
            FUN_003a25d4(pcVar14);
            uVar16 = FUN_003a261c(pcVar6);
            if ((uVar16 & 1) == 0) {
                FUN_004aa44c(*(word_t *)(pcVar6 + 0x10));
                FUN_0006b3f4();
                pcVar6 = FUN_00498e50();
            }
            uVar16 = *(word_t *)(pcVar6 + 0x10);
            if (*(word_t *)(pcVar6 + 0x18) >> 1 <= uVar16) {
                uVar5 = FUN_0006b42c();
                FUN_00350774(uVar5, uVar16 + 1);
                pcVar6 = FUN_00498e50();
            }
            local_168[0][0] = c_pair.lo;
            local_168[0][8] = c_pair.hi;
            FUN_004a3340(local_168);
            *(word_t *)(pcVar6 + 0x10) = uVar16 + 1;
            FUN_004abb58(pcVar6 + uVar16 * 0x160 + 0x20);
        }
    }
    FUN_0008e500(pcVar6, root_pair.hi);
}


/* FUN_00479c18 @ 0x00479c18   (est. sk_bcg_00479c18)
 * Ghidra: void sk_bcg_00479c18(void)
 * Walks the bytecode-generator node list (elements of 0x160 bytes at
 * root+0x20). For kind-3 elements it iterates a nested instruction list
 * (via FUN_0029fb80 / FUN_0049ab00) appending 0x160-byte elements into the
 * destination stream; kind-0 elements are transcribed via
 * FUN_0049e2d4/FUN_0049e2f0 and appended the same way. Retains the global
 * DAT_006577e0 handles, drops references, and releases the root at the end.
 * Confidence: medium   Notes: DAT_006577e0; many out-of-slice callees. */
static void sk_bcg_00479c18(void)
{
    wpair_t root_pair, el_pair;
    word_t lVar9, lVar7, lVar10;
    word_t iVar2;
    word_t uVar5, uVar3;
    unsigned int uVar1;
    unsigned int *puVar4;
    word_t *puVar6, *puVar8;
    word_t local_5a8;
    word_t local_440;
    unsigned char auStack_430[352];
    unsigned char auStack_2d0[352];
    unsigned char auStack_170[352];
    unsigned char auStack_5b0[8];
    unsigned char local_660[11][16];
    word_t *local_10, *puStack_8;
    word_t unaff_x19;

    root_pair.lo = FUN_0008e518();
    local_10 = &DAT_006577e0;
    puStack_8 = &DAT_006577e0;
    lVar9 = *(word_t *)(root_pair.lo + 0x10);
    if (lVar9 == 0) {
        puVar6 = (word_t *)FUN_000a6fe0();
        puVar8 = puVar6;
    } else {
        lVar10 = 0;
        FUN_000a6fe0();
        do {
            lVar7 = root_pair.lo + 0x20 + lVar10 * 0x160;
            FUN_004ab31c(auStack_2d0);
            FUN_00117cc4();
            FUN_004ab31c(auStack_170);
            FUN_00117cc4();
            iVar2 = FUN_0049df0c(auStack_2d0);
            if (iVar2 == 3) {
                FUN_0049df18(auStack_170);
                FUN_004ab430();
                local_440 = 0;
                FUN_004abc18();
                lVar7 = FUN_0049df18(auStack_430);
                uVar5 = *(word_t *)(lVar7 + 8);
                FUN_004a3940(auStack_2d0, auStack_5b0);
                thunk_FUN_0036b270(uVar5);
                while (true) {
                    el_pair = FUN_0029fb80().lo;
                    lVar7 = el_pair.hi;
                    if (lVar7 == 0) break;
                    thunk_FUN_0036b270(lVar7);
                    FUN_00077894(auStack_5b0);
                    uVar3 = FUN_0049ab00();
                    FUN_003a25d4(local_5a8);
                    if ((uVar3 & 1) == 0) {
                        FUN_003a25d4(lVar7);
                    } else {
                        uVar3 = FUN_003a261c(unaff_x19);
                        if ((uVar3 & 1) == 0) {
                            FUN_004aa44c(*(word_t *)(unaff_x19 + 0x10));
                            FUN_0006b3f4();
                            unaff_x19 = FUN_00498e50();
                        }
                        uVar3 = *(word_t *)(unaff_x19 + 0x10);
                        if (*(word_t *)(unaff_x19 + 0x18) >> 1 <= uVar3) {
                            FUN_0006b42c();
                            FUN_004ab0e0();
                            unaff_x19 = FUN_00498e50();
                        }
                        local_660[0][0] = el_pair.lo;
                        local_660[0][8] = el_pair.hi;
                        FUN_0049ca44(local_660);
                        FUN_004ac61c(auStack_5b0);
                        FUN_0049c850(auStack_5b0);
                        *(word_t *)(unaff_x19 + 0x10) = uVar3 + 1;
                        FUN_00117cc4(unaff_x19 + uVar3 * 0x160 + 0x20, auStack_5b0, 0x160);
                    }
                }
                FUN_004a3918(auStack_2d0);
label_e78:
                FUN_004a3918(auStack_2d0);
            } else {
                if (iVar2 == 0) {
                    FUN_004ac1a4(auStack_170);
                    FUN_004ab0f0(local_660);
                    FUN_00117cc4();
                    iVar2 = FUN_0049e2d4(lVar7);
                    if (iVar2 == 1) {
                        puVar4 = (unsigned int *)FUN_0049e2f0(local_660);
                        uVar1 = *puVar4;
                        FUN_004abc18();
                        uVar5 = FUN_0049df18(auStack_430);
                        FUN_004a36c4(uVar5, auStack_5b0);
                        uVar3 = FUN_0049aa14(auStack_5b0, uVar1);
                    } else {
                        if (iVar2 != 0) {
                            FUN_004abc18();
                            uVar5 = FUN_0049df18(auStack_430);
                            FUN_004a36c4(uVar5, auStack_5b0);
                            goto label_ee0;
                        }
                        FUN_0049e2f0(local_660);
                        FUN_004abc18();
                        FUN_004ac1a4(auStack_430);
                        FUN_004a3940(auStack_2d0, auStack_5b0);
                        FUN_004a36c4(lVar7, auStack_5b0);
                        FUN_003511d8(auStack_5b0);
                        uVar3 = FUN_0049ab00();
                        FUN_003a25d4(local_5a8);
                    }
                    if ((uVar3 & 1) == 0) goto label_e78;
                } else {
                    FUN_004a3940(auStack_2d0, auStack_430);
                }
label_ee0:
                uVar3 = FUN_003a261c(unaff_x19);
                if ((uVar3 & 1) == 0) {
                    FUN_004aa44c(*(word_t *)(unaff_x19 + 0x10));
                    FUN_0006b3f4();
                    unaff_x19 = FUN_00498e50();
                }
                uVar3 = *(word_t *)(unaff_x19 + 0x10);
                if (*(word_t *)(unaff_x19 + 0x18) >> 1 <= uVar3) {
                    FUN_0006b42c();
                    FUN_004ab0e0();
                    unaff_x19 = FUN_00498e50();
                }
                *(word_t *)(unaff_x19 + 0x10) = uVar3 + 1;
                FUN_00117cc4(unaff_x19 + uVar3 * 0x160 + 0x20, auStack_2d0, 0x160);
            }
            lVar10 = lVar10 + 1;
            puVar6 = puStack_8;
            puVar8 = local_10;
        } while (lVar10 != lVar9);
    }
    FUN_003a25d4(puVar6);
    FUN_003a25d4(puVar8);
    FUN_0008e500(unaff_x19, root_pair.hi);
}


/* FUN_00479fe4 @ 0x00479fe4   (est. sk_bcg_00479fe4)
 * Ghidra: void sk_bcg_00479fe4(void)
 * Emits a custom-character / unicode-scalar instruction run. Opens the
 * emitted-instruction list, and while the current scalar page (>>0xe) has
 * not caught up to the target range, records source-span entries into three
 * parallel node lists (span buffer at +0x58, code buffer at +8, metadata at
 * +0x60) with fail-closed SWBP checks. Ends by pushing the tail element and
 * releasing handles. 
 * Confidence: medium   Notes: SWBP at 0x47a250..0x47a258; FUN_0042c5a4 as
 * function pointer; many out-of-slice callees. */
static void sk_bcg_00479fe4(void)
{
    word_t pcVar1;
    word_t uVar2, uVar3, uVar5, uVar6, uVar7;
    word_t extraout_w8;
    word_t extraout_x9;
    word_t extraout_x16, extraout_x16_00;
    word_t unaff_x20, unaff_x21, unaff_x22, unaff_x30;
    word_t lVar8, lVar9, lVar10, lVar11;
    wpair_t el_pair;
    word_t in_stack_00000028;

    FUN_0035193c();
    FUN_004abacc();
    if (extraout_x9 == 0) {
        CL4_SWBP(0x47a254);
    }
    FUN_003509ec();
    FUN_004ab55c();
    if ((extraout_w8 >> 0x10 & 1) == 0) {
        uVar3 = sk_bcg_004772d0();
        thunk_FUN_0036b270();
        pcVar1 = FUN_0042c5a4;
        FUN_00077894(1);
        el_pair = sk_bcg_004773a8();
        in_stack_00000028 = el_pair.lo;
        uVar7 = el_pair.hi >> 0xe;
        lVar8 = unaff_x21;
        while (true) {
            uVar2 = uVar7 == in_stack_00000028 >> 0xe;
            if (uVar2) {
                FUN_003a25d4(pcVar1);
                FUN_001b36ec(unaff_x22, unaff_x21);
                FUN_0034ecc8();
                if (!uVar2) {
                    sk_bcg_00476518();
                    sk_bcg_00477494(uVar3);
                    FUN_00351774(unaff_x30);
                    return;
                }
                CL4_SWBP(0x47a258);
            }
            uVar2 = in_stack_00000028 >> 0xe <= uVar7;
            FUN_00351dfc();
            lVar4 = FUN_002b7088();
            FUN_00351dfc(&stack0x00000028);
            FUN_002b723c();
            lVar11 = *(word_t *)(*(word_t *)(unaff_x20 + 0x58) + 0x10);
            FUN_004ab5b0();
            FUN_00498b28(extraout_x16);
            lVar10 = *(word_t *)(*(word_t *)(unaff_x20 + 0x58) + 0x10);
            FUN_00498c1c(lVar10, lVar8);
            lVar9 = *(word_t *)(unaff_x20 + 0x58);
            *(word_t *)(lVar9 + 0x10) = lVar10 + 1;
            FUN_004ab8ac(lVar9 + lVar10 * 0x10);
            *(word_t *)(unaff_x20 + 0x58) = lVar9;
            FUN_004aa3e4();
            FUN_00498b28(extraout_x16_00);
            uVar5 = FUN_004aa7a8();
            FUN_00498c1c(uVar5, lVar8);
            FUN_004ab7f0();
            FUN_004ab7e0();
            FUN_00481918(lVar11);
            sk_bcg_00476518(lVar4);
            FUN_00498b28(lVar8);
            uVar5 = FUN_004aab1c();
            FUN_00498c1c(uVar5, lVar8);
            FUN_004aabf4(*(word_t *)(unaff_x20 + 8));
            FUN_004ab7e0();
            FUN_00498b28(lVar8);
            uVar5 = FUN_004aab1c();
            FUN_00498c1c(uVar5, lVar8);
            lVar8 = *(word_t *)(unaff_x20 + 8);
            *(word_t *)(lVar8 + 0x10) = lVar4 + 1;
            *(word_t *)(lVar8 + lVar4 * 8 + 0x20) = 0x400000000000000;
            *(word_t *)(unaff_x20 + 8) = lVar8;
            FUN_00481918(uVar3);
            uVar5 = *(word_t *)(lVar8 + 0x10);
            uVar6 = FUN_003a261c(lVar9);
            if ((uVar6 & 1) == 0) {
                lVar9 = FUN_0049a4a4(lVar9);
            }
            FUN_004ac120();
            if (uVar2) break;
            lVar4 = lVar9 + lVar11 * 0x10;
            *(word_t *)(lVar4 + 0x20) = uVar5;
            *(unsigned char *)(lVar4 + 0x28) = 0;
            *(word_t *)(unaff_x20 + 0x58) = lVar9;
        }
        CL4_SWBP(0x47a250);
    }
    el_pair = FUN_00100efc().lo;
    FUN_00351774(el_pair.lo, el_pair.hi, unaff_x30);
    sk_bcg_00475e14();
}


/* FUN_0047a258 @ 0x0047a258   (est. sk_bcg_0047a258)
 * Ghidra: void sk_bcg_0047a258(void)
 * Bytecode-generator main instruction emitter switch. Reads the current
 * instruction element kind (FUN_0049df0c) and emits the corresponding
 * bytecode into the output stream (0x20-aligned code slots, 0x10-byte
 * entries): case 0 (default) custom-character/scalar handling, case 1
 * backreference, case 2 anchor pair, case 3 fatal 'Removed in
 * flatteningCustomCharacter' path, case 5/6/7 multi-slot instruction
 * sequences with 0x160-byte list growth and fail-closed SWBP checks.
 * Confidence: medium   Notes: s_Removed_in__flatteningCustomChar_005e2850;
 * SWBP at 0x47a984..0x47a9a8; many out-of-slice emitters. */
static void sk_bcg_0047a258(void)
{
    word_t uVar1, uVar12, uVar17;
    word_t pcVar2;
    word_t uVar3, uVar4, uVar5;
    unsigned int uVar6;
    word_t uVar7, uVar8, uVar9, uVar10, uVar11;
    word_t extraout_w8, extraout_x8;
    word_t extraout_x9;
    word_t extraout_x16;
    word_t extraout_x1_00, extraout_x1_01;
    word_t *unaff_x20;
    word_t unaff_x21;
    word_t lVar13, lVar15;
    word_t uVar14, uVar16;
    wpair_t el_pair;
    word_t in_stack_00000008;
    unsigned char auStack_2c8[352];
    unsigned char auStack_168[176];
    unsigned char auStack_b8[184];

    FUN_00353cfc();
    FUN_004ac360(auStack_2c8);
    FUN_00117cc4();
    uVar6 = FUN_0049df0c(auStack_2c8);
    plVar7 = (word_t *)FUN_0049df18(auStack_2c8);
    switch (uVar6) {
    default:
        FUN_004ab0f0(auStack_168);
        FUN_00117cc4();
        FUN_004ab0f0(auStack_b8);
        FUN_00117cc4();
        iVar6 = FUN_0049e2d4(auStack_b8);
        uVar3 = iVar6 != 0;
        uVar4 = iVar6 == 1;
        if (uVar4) {
            FUN_0049e2f0(auStack_b8);
            FUN_004abc0c();
            if (uVar3 && !uVar4) {
                FUN_004ac150();
                if (uVar3) {
                    FUN_00463bd4();
                    uVar12 = FUN_004ac6bc();
                } else {
                    uVar12 = FUN_004ac6e4();
                }
            } else {
                uVar12 = (word_t)(extraout_w8 + 1);
            }
            el_pair = FUN_00255d4c(uVar12).lo;
            in_stack_00000008 = el_pair.lo;
            if (el_pair.hi < 0) {
                CL4_SWBP(0x47a9a8);
            }
            FUN_00294cb4(&stack0x00000008);
            sk_bcg_00479fe4();
            FUN_003a25d4(extraout_x1_01);
        } else if (iVar6 == 0) {
            FUN_0049e2f0(auStack_b8);
            FUN_000e0654();
            sk_bcg_00479fe4();
        } else {
            FUN_004ab890(auStack_168);
            sk_bcg_00475544();
        }
        break;
    case 1:
        sk_bcg_0047b844(*unaff_x20);
        if (unaff_x21 == 0) {
            uVar12 = FUN_00481a38();
            FUN_0036b118(extraout_x1_00);
            FUN_004aa4ac();
            FUN_00498b28(extraout_x16);
            FUN_00350518();
            FUN_00498c1c();
            FUN_004aa9c0(unaff_x20[1]);
            *(word_t *)(extraout_x9 + 0x20) = uVar12 | 0xe00000000000000;
            unaff_x20[1] = extraout_x8;
        }
        break;
    case 2:
        lVar13 = *plVar7;
        uVar3 = (unsigned char)plVar7[1];
        goto label_a908;
    case 3:
        FUN_00002874(s_Removed_in__flatteningCustomChar_005e2850);
        FUN_003593c0();
        FUN_00002818();
        /* Subroutine does not return */
        FUN_001afa84();
    case 4:
        break;
    case 5:
        uVar12 = unaff_x20[0xf];
        if (SCARRY8(uVar12, 1)) {
            CL4_SWBP(0x47a98c);
        }
        lVar15 = *plVar7;
        lVar13 = *(word_t *)(lVar15 + 0x20);
        uVar3 = *(unsigned char *)(lVar15 + 0x28);
        uVar4 = *(unsigned char *)(lVar15 + 0x18);
        uVar14 = *(word_t *)(lVar15 + 0x10);
        unaff_x20[0xf] = uVar12 + 1;
        FUN_004aa5ac();
        FUN_00498b28(extraout_x16_05);
        FUN_003509b0();
        FUN_00498c1c();
        FUN_004ab334(unaff_x20[1]);
        *(word_t *)(extraout_x9_14 + 0x20) = uVar12 | 0x200000000000000;
        unaff_x20[1] = extraout_x8_10;
        FUN_004ab890(uVar14, uVar4);
        sk_bcg_0047aa0c();
        if (unaff_x21 != 0) break;
        FUN_004aa594();
        FUN_00498b28(extraout_x16_06);
        uVar14 = FUN_004aad44(unaff_x20[1]);
        FUN_00498c1c(uVar14, uVar4);
        FUN_004aa9e8(unaff_x20[1]);
        *(word_t *)(extraout_x9_15 + 0x20) = uVar12 | 0x300000000000000;
        unaff_x20[1] = extraout_x8_11;
label_a908:
        FUN_004ab890(lVar13, uVar3);
        sk_bcg_0047aa0c();
        break;
    case 6:
        uVar12 = unaff_x20[0xf];
        if (SCARRY8(uVar12, 1)) {
            CL4_SWBP(0x47a984);
        }
        lVar13 = *plVar7;
        uVar16 = *(word_t *)(lVar13 + 0x20);
        uVar4 = *(unsigned char *)(lVar13 + 0x28);
        uVar3 = *(unsigned char *)(lVar13 + 0x18);
        uVar8 = *(word_t *)(lVar13 + 0x10);
        unaff_x20[0xf] = uVar12 + 1;
        uVar11 = sk_bcg_004772d0();
        FUN_00498b28(FUN_00499158);
        lVar15 = *(word_t *)(unaff_x20[1] + 0x10);
        uVar14 = FUN_004ab2f8();
        FUN_00498c1c(uVar14, FUN_00499158);
        lVar13 = unaff_x20[1];
        *(word_t *)(lVar13 + 0x10) = lVar15 + 1;
        *(word_t *)(lVar13 + lVar15 * 8 + 0x20) = uVar12 | 0x200000000000000;
        unaff_x20[1] = lVar13;
        FUN_004ab890(uVar8, uVar3);
        sk_bcg_0047aa0c();
        if (unaff_x21 != 0) break;
        FUN_004aa4ac();
        FUN_00498b28(extraout_x16_00);
        uVar14 = FUN_004aad44(unaff_x20[1]);
        FUN_00498c1c(uVar14, lVar15);
        FUN_004aa9e8(unaff_x20[1]);
        *(word_t *)(extraout_x9_00 + 0x20) = 0x1100000000000000;
        unaff_x20[1] = extraout_x8_00;
        FUN_00481918(uVar11);
        FUN_004ab2f8();
        FUN_00498b28();
        uVar14 = FUN_004aad44(unaff_x20[1]);
        FUN_00498c1c(uVar14, lVar15);
        FUN_004aa9e8(unaff_x20[1]);
        *(word_t *)(extraout_x9_01 + 0x20) = uVar12 | 0x300000000000000;
        unaff_x20[1] = extraout_x8_01;
        FUN_004ab890(uVar16, uVar4);
        sk_bcg_0047aa0c();
        FUN_004aa4ac();
        FUN_00498b28(extraout_x16_01);
        FUN_00350518();
        FUN_00498c1c();
        FUN_004aa9c0(unaff_x20[1]);
        FUN_004aaa38();
        FUN_00498b28(lVar15);
        FUN_00350518();
        FUN_00498c1c();
        FUN_004aa9c0(unaff_x20[1]);
        FUN_004aaa38();
        goto label_a848;
    case 7:
        uVar17 = unaff_x20[0xf];
        uVar12 = uVar17 + 1;
        if (SCARRY8(uVar17, 1)) {
            CL4_SWBP(0x47a988);
        }
        lVar13 = *plVar7;
        uVar16 = *(word_t *)(lVar13 + 0x10);
        uVar4 = *(unsigned char *)(lVar13 + 0x18);
        uVar14 = *(word_t *)(lVar13 + 0x20);
        uVar3 = *(unsigned char *)(lVar13 + 0x28);
        unaff_x20[0xf] = uVar12;
        uVar1 = uVar17 + 2;
        if (SCARRY8(uVar12, 1)) {
            CL4_SWBP(0x47a990);
        }
        unaff_x20[0xf] = uVar1;
        if (SCARRY8(uVar1, 1)) {
            CL4_SWBP(0x47a994);
        }
        unaff_x20[0xf] = uVar17 + 3;
        sk_bcg_004772d0();
        uVar8 = sk_bcg_004772d0();
        uVar9 = sk_bcg_004772d0();
        uVar10 = sk_bcg_004772d0();
        uVar11 = sk_bcg_004772d0();
        FUN_004aa5ac();
        FUN_00498b28(extraout_x16_02);
        FUN_003509b0();
        FUN_00498c1c();
        FUN_004ab334(unaff_x20[1]);
        *(word_t *)(extraout_x9_02 + 0x20) = uVar17 | 0x200000000000000;
        unaff_x20[1] = extraout_x8_02;
        FUN_004abe84();
        FUN_003509b0();
        FUN_00498c1c();
        FUN_004ab334(unaff_x20[1]);
        *(word_t *)(extraout_x9_03 + 0x20) = 0x1100000000000000;
        unaff_x20[1] = extraout_x8_03;
        FUN_004ab478();
        FUN_00481918();
        FUN_004ab890(uVar16, uVar4);
        sk_bcg_0047aa0c();
        if (unaff_x21 != 0) break;
        FUN_004aa4ac();
        FUN_00498b28(extraout_x16_03);
        FUN_00351274();
        FUN_00498c1c();
        FUN_004aab88(unaff_x20[1]);
        *(word_t *)(extraout_x9_04 + 0x20) = 0x1300000000000000;
        unaff_x20[1] = extraout_x8_04;
        FUN_004ab478();
        sk_bcg_00477494(0); /* register-residue arg */
        FUN_004ab2f8();
        FUN_00498b28();
        FUN_00350518();
        FUN_00498c1c();
        FUN_004aa9c0(unaff_x20[1]);
        *(word_t *)(extraout_x9_05 + 0x20) = uVar12 | 0x200000000000000;
        unaff_x20[1] = extraout_x8_05;
        FUN_004ab2f8();
        FUN_00498b28();
        FUN_00350518();
        FUN_00498c1c();
        FUN_004aa9c0(unaff_x20[1]);
        *(word_t *)(extraout_x9_06 + 0x20) = uVar17 | 0x300000000000000;
        unaff_x20[1] = extraout_x8_06;
        FUN_004ab2f8();
        FUN_00498b28();
        FUN_00350518();
        FUN_00498c1c();
        FUN_004aa9c0(unaff_x20[1]);
        *(word_t *)(extraout_x9_07 + 0x20) = 0x1100000000000000;
        unaff_x20[1] = extraout_x8_07;
        FUN_00481918(uVar8);
        FUN_004ab890(uVar14, uVar3);
        sk_bcg_0047aa0c();
        FUN_004aa5ac();
        FUN_00498b28(extraout_x16_04);
        FUN_004aa9d0();
        FUN_004aa780();
        *(word_t *)(extraout_x9_08 + 0x20) = 0x1300000000000000;
        FUN_004ab328();
        sk_bcg_00477494(uVar8);
        FUN_004abe84();
        FUN_004aa9d0();
        FUN_004aa780();
        *(word_t *)(extraout_x9_09 + 0x20) = uVar1 | 0x200000000000000;
        unaff_x20[1] = extraout_x8_08;
        FUN_004abe84();
        FUN_004aa9d0();
        FUN_004aa780();
        *(word_t *)(extraout_x9_10 + 0x20) = uVar12 | 0x300000000000000;
        unaff_x20[1] = extraout_x8_09;
        FUN_004abe84();
        FUN_004aa9d0();
        FUN_004aa780();
        *(word_t *)(extraout_x9_11 + 0x20) = uVar1 | 0x600000000000000;
        FUN_004ab328();
        FUN_00481918(uVar10);
        FUN_004abe84();
        FUN_004aa9d0();
        FUN_004aa780();
        *(word_t *)(extraout_x9_12 + 0x20) = uVar17 | 0x600000000000000;
        FUN_004ab328();
        FUN_00481918(uVar9);
        FUN_004abe84();
        FUN_004aa9d0();
        FUN_004aa780();
        FUN_004aaa38();
        FUN_00481918(uVar11);
        FUN_004ab478();
        sk_bcg_00477494(0); /* register-residue arg */
        FUN_004abe84();
        FUN_004aa9d0();
        FUN_004aa780();
        *(word_t *)(extraout_x9_13 + 0x20) = uVar1 | 0x300000000000000;
        FUN_004ab328();
        FUN_00498b28(0x1100000000000000);
        FUN_004aa9d0();
        FUN_004aa780();
        FUN_004aaa38();
        FUN_00481918(uVar11);
        sk_bcg_00477494(uVar10);
        FUN_004abe84();
        FUN_004aa9d0();
        FUN_004aa780();
        FUN_004aaa38();
label_a848:
        sk_bcg_00477494(uVar11);
    }
    FUN_00353d14(extraout_x1);
}


/* FUN_0047aa0c @ 0x0047aa0c   (est. sk_bcg_0047aa0c)
 * Ghidra: void sk_bcg_0047aa0c(void)
 * Core bytecode-generator that walks the parsed AST list (root at
 * local_508+0x10) and recursively flattens nested lists (0x160-byte
 * elements) into a flat instruction stream in local_430, dispatching each
 * nested element via FUN_0049df0c kind tags (case 2 = nested list; else
 * leaf). After flattening it walks the source span list and for each span
 * emits code/metadata entries (0x1100..., 0x1300... tag-prefixed slots)
 * into the three node lists at +0x58, +8, +0x60. Fail-closed SWBP checks
 * at 0x47b804..0x47b844. 
 * Confidence: medium   Notes: SUB_54ffff60f100041f masked trampoline;
 * huge stack frame; many out-of-slice emitters. */
static void sk_bcg_0047aa0c(void)
{
    word_t uVar1, uVar3, uVar5;
    word_t uVar9, uVar10, uVar11, uVar12, uVar16;
    word_t uVar20, uVar22, uVar23, uVar24, uVar25, uVar26, uVar27, uVar28, uVar29, uVar30;
    word_t pcVar2;
    word_t iVar4;
    word_t *plVar7, *puVar8;
    word_t lVar6, lVar14, lVar15, lVar17, lVar18, lVar19, lVar21;
    word_t unaff_x20, unaff_x21, unaff_x30;
    word_t local_1ba4;
    unsigned char auStack_1b08[352], auStack_19a8[352], auStack_1848[352];
    unsigned char auStack_16e8[352], auStack_1588[352], auStack_1428[352];
    unsigned char auStack_12c8[352], auStack_1168[352], auStack_1008[352];
    unsigned char auStack_ea8[352], auStack_d48[352], auStack_be8[352];
    unsigned char auStack_a88[1056], auStack_668[352];
    word_t local_508, local_500, local_430;
    unsigned char auStack_428[352], auStack_2c8[352], auStack_168[360];
    wpair_t el_pair;
    unsigned char auVar31[12], auVar32[16];
    word_t in_x3;

    FUN_00353cfc();
    /* masked self-modifying/trampoline fn */
    el_pair.lo = ((word_t (*)())&SUB_54ffff60f100041f)();
    el_pair.hi = el_pair.hi;
    uVar10 = el_pair.lo;
    FUN_00117cc4(&local_508);
    if (*(word_t *)(local_508 + 0x10) == 0) {
        CL4_SWBP(0x47b830);
    }
    if ((*(unsigned int *)(local_508 + 0x1c + *(word_t *)(local_508 + 0x10) * 4) >> 0x10 & 1) == 0) {
        FUN_0036b270(uVar10);
    } else {
        uVar10 = sk_bcg_00478a98(uVar10);
    }
    uVar5 = sk_bcg_00479c18(uVar10);
    el_pair.hi = el_pair.hi;
    el_pair.lo = uVar5;
    auVar31[0] = el_pair.lo; auVar31[8] = el_pair.hi;
    FUN_0036b118(uVar10);
    uVar12 = (word_t)(el_pair.hi & 1);
    FUN_00350470();
    lVar6 = sk_bcg_00478110();
    if (lVar6 == 2) {
        if ((local_430 & 1) == 0) {
            uVar12 = (word_t)(el_pair.hi & 1);
            FUN_00350470();
            el_pair = sk_bcg_0047be1c();
            FUN_0036b118(uVar5);
        }
    } else if ((local_430 & 1) == 0) {
        FUN_0036b118(uVar5);
        if (*(word_t *)(local_508 + 0x10) == 0) {
            CL4_SWBP(0x47b834);
        }
        if ((*(unsigned int *)(local_508 + 0x1c + *(word_t *)(local_508 + 0x10) * 4) >> 0x10 & 1) == 0) {
            FUN_00352c4c((unsigned int)lVar6 & 1);
            sk_bcg_0047bcc8();
        } else {
            FUN_00352c4c((unsigned int)lVar6 & 1);
            sk_bcg_0047bd74();
        }
        goto label_b7e0;
    }
    local_1ba4 = el_pair.hi;
    lVar6 = el_pair.lo;
    uVar22 = 0;
    uVar25 = *(word_t *)(lVar6 + 0x10);
    FUN_00466244();
    while (uVar22 != uVar25) {
        if (*(word_t *)(lVar6 + 0x10) <= uVar22) {
            CL4_SWBP(0x47b80c);
        }
        FUN_004ab980();
        FUN_004ab31c();
        FUN_00117cc4();
        uVar22 = uVar22 + 1;
        FUN_004abaa0();
        FUN_004ab31c();
        FUN_00117d14();
        FUN_004ab980();
        iVar4 = FUN_0049df0c();
        if (iVar4 != 4) {
            if (iVar4 == 2) {
                FUN_004abaa0();
                plVar7 = (word_t *)FUN_0049df18();
                lVar14 = *plVar7;
                uVar16 = *(word_t *)(lVar14 + 0x10);
                uVar12 = 0x160;
                FUN_00117cc4(auStack_428, auStack_2c8);
                puVar8 = (word_t *)FUN_0049df18(auStack_428);
                FUN_0036b270(*puVar8);
                for (uVar28 = 0; uVar28 != uVar16; uVar28 = uVar28 + 1) {
                    if (*(word_t *)(lVar14 + 0x10) <= uVar28) {
                        CL4_SWBP(0x47b810);
                    }
                    FUN_004ab31c(lVar14 + 0x20, auStack_be8);
                    FUN_00117cc4();
                    FUN_004ab31c(auStack_a88);
                    FUN_00117d14();
                    iVar4 = FUN_0049df0c(auStack_be8);
                    if (iVar4 != 4) {
                        if (iVar4 != 2) goto label_af60;
                        plVar7 = (word_t *)FUN_0049df18(auStack_a88);
                        lVar17 = *plVar7;
                        uVar29 = *(word_t *)(lVar17 + 0x10);
                        uVar12 = 0x160;
                        FUN_00117cc4(auStack_d48, auStack_be8);
                        puVar8 = (word_t *)FUN_0049df18(auStack_d48);
                        FUN_0036b270(*puVar8);
                        for (uVar30 = 0; uVar30 != uVar29; uVar30 = uVar30 + 1) {
                            if (*(word_t *)(lVar17 + 0x10) <= uVar30) {
                                CL4_SWBP(0x47b818);
                            }
                            FUN_004ab31c(lVar17 + 0x20, auStack_1008);
                            FUN_00117cc4();
                            FUN_004ab31c(auStack_ea8);
                            FUN_00117d14();
                            iVar4 = FUN_0049df0c(auStack_1008);
                            if (iVar4 != 4) {
                                if (iVar4 != 2) {
                                    FUN_004a3918(auStack_be8);
                                    goto label_af60;
                                }
                                plVar7 = (word_t *)FUN_0049df18(auStack_ea8);
                                lVar18 = *plVar7;
                                uVar23 = *(word_t *)(lVar18 + 0x10);
                                uVar12 = 0x160;
                                FUN_00117cc4(auStack_1168, auStack_1008);
                                puVar8 = (word_t *)FUN_0049df18(auStack_1168);
                                FUN_0036b270(*puVar8);
                                for (uVar24 = 0; uVar24 != uVar23; uVar24 = uVar24 + 1) {
                                    if (*(word_t *)(lVar18 + 0x10) <= uVar24) {
                                        CL4_SWBP(0x47b814);
                                    }
                                    FUN_004ab31c(lVar18 + 0x20, auStack_1428);
                                    FUN_00117cc4();
                                    FUN_004ab31c(auStack_12c8);
                                    FUN_00117d14();
                                    iVar4 = FUN_0049df0c(auStack_1428);
                                    if (iVar4 != 4) {
                                        if (iVar4 != 2) {
                                            FUN_004a3940(auStack_1428, auStack_1588);
                                            FUN_004a3918(auStack_1008);
                                            FUN_004a3918(auStack_be8);
                                            FUN_004a3918(auStack_1428);
                                            goto label_af60;
                                        }
                                        plVar7 = (word_t *)FUN_0049df18(auStack_12c8);
                                        lVar15 = *plVar7;
                                        uVar20 = *(word_t *)(lVar15 + 0x10);
                                        uVar12 = 0x160;
                                        FUN_00117cc4(auStack_1588, auStack_1428);
                                        puVar8 = (word_t *)FUN_0049df18(auStack_1588);
                                        FUN_0036b270(*puVar8);
                                        for (uVar27 = 0; uVar27 != uVar20; uVar27 = uVar27 + 1) {
                                            if (*(word_t *)(lVar15 + 0x10) <= uVar27) {
                                                CL4_SWBP(0x47b808);
                                            }
                                            FUN_004ab31c(auStack_1848);
                                            FUN_00117cc4();
                                            FUN_004ab31c(auStack_16e8);
                                            FUN_00117d14();
                                            iVar4 = FUN_0049df0c(auStack_1848);
                                            if (iVar4 != 4) {
                                                if (iVar4 != 2) {
                                                    FUN_004a3940(auStack_1848, auStack_19a8);
label_af2c:
                                                    FUN_004a3918(auStack_1428);
                                                    FUN_004a3918(auStack_1008);
                                                    FUN_004a3918(auStack_be8);
                                                    FUN_004a3918(auStack_1848);
                                                    goto label_af60;
                                                }
                                                plVar7 = (word_t *)FUN_0049df18(auStack_16e8);
                                                lVar21 = *plVar7;
                                                lVar19 = *(word_t *)(lVar21 + 0x10);
                                                uVar12 = 0x160;
                                                FUN_00117cc4(auStack_19a8, auStack_1848);
                                                puVar8 = (word_t *)FUN_0049df18(auStack_19a8);
                                                FUN_0036b270(*puVar8);
                                                uVar26 = 0xffffffffffffffff;
                                                while (uVar26 - lVar19 != -1) {
                                                    uVar26 = uVar26 + 1;
                                                    if (*(word_t *)(lVar21 + 0x10) <= uVar26) {
                                                        CL4_SWBP(0x47b804);
                                                    }
                                                    FUN_004ab5c8(auStack_668);
                                                    FUN_00117cc4();
                                                    FUN_004a3940(auStack_668, auStack_1b08);
                                                    uVar9 = sk_bcg_0047c0dc();
                                                    FUN_004a3918(auStack_668);
                                                    if ((uVar9 & 1) == 0) goto label_af2c;
                                                }
                                                FUN_004a3918(auStack_1848);
                                            }
                                        }
                                        FUN_004a3918(auStack_1428);
                                    }
                                }
                                FUN_004a3918(auStack_1008);
                            }
                        }
                        FUN_004a3918(auStack_be8);
                    }
                }
                FUN_004ab980();
                FUN_004a3918();
            } else {
                uVar10 = FUN_004ab980().lo;
                FUN_004a3940(uVar10, auStack_428);
label_af60:
                uVar12 = FUN_003a261c(local_430);
                if ((uVar12 & 1) == 0) {
                    FUN_000dbbe0(uVar12, *(word_t *)(local_430 + 0x10) + 1);
                    FUN_0049a550();
                }
                uVar28 = *(word_t *)(local_430 + 0x10);
                if (*(word_t *)(local_430 + 0x18) >> 1 <= uVar28) {
                    FUN_0006b42c();
                    FUN_004abb28();
                    FUN_0049a550();
                }
                *(word_t *)(local_430 + 0x10) = uVar28 + 1;
                uVar12 = 0x160;
                FUN_00117cc4(local_430 + uVar28 * 0x160 + 0x20, auStack_2c8);
            }
        }
    }
    FUN_0036b118(lVar6);
    if ((local_1ba4 & 1) == 0) {
        uVar10 = sk_bcg_004772d0();
        uVar5 = sk_bcg_00477338(1, local_430);
        in_x3 = in_x3 >> 1;
        FUN_0036b270(local_430);
        lVar6 = 0x160;
        for (; in_x3 != uVar12; uVar12 = uVar12 + 1) {
            uVar3 = in_x3 <= uVar12;
            if ((long)in_x3 <= (long)uVar12) {
                CL4_SWBP(0x47b820);
            }
            FUN_004abaa0();
            FUN_004ac8a8();
            FUN_00117cc4();
            lVar6 = *(word_t *)(unaff_x20 + 0x58);
            uVar28 = *(word_t *)(lVar6 + 0x10);
            uVar11 = FUN_004abaa0();
            FUN_004a3940(uVar11, auStack_428);
            uVar22 = FUN_003a261c(lVar6);
            if ((uVar22 & 1) == 0) {
                FUN_004aa94c(uVar22, uVar28 + 1);
                lVar6 = FUN_00498fd0();
            }
            lVar14 = *(word_t *)(lVar6 + 0x10);
            FUN_004ac68c(*(word_t *)(lVar6 + 0x18));
            if (uVar3) {
                FUN_004aa720();
                lVar6 = FUN_00498fd0();
            }
            *(word_t *)(lVar6 + 0x10) = uVar25;
            FUN_004ab8ac(lVar6 + lVar14 * 0x10);
            *(word_t *)(unaff_x20 + 0x58) = lVar6;
            lVar6 = *(word_t *)(unaff_x20 + 8);
            uVar22 = FUN_003a261c(lVar6);
            if ((uVar22 & 1) == 0) {
                FUN_004aa5c4();
                lVar6 = FUN_00499158();
            }
            lVar14 = *(word_t *)(lVar6 + 0x10);
            FUN_004ac68c(*(word_t *)(lVar6 + 0x18));
            if (uVar3) {
                FUN_004aa720();
                lVar6 = FUN_00499158();
            }
            *(word_t *)(lVar6 + 0x10) = uVar25;
            *(word_t *)(lVar6 + lVar14 * 8 + 0x20) = 0x1100000000000000;
            *(word_t *)(unaff_x20 + 8) = lVar6;
            lVar6 = *(word_t *)(unaff_x20 + 0x60);
            uVar22 = FUN_003a261c(lVar6);
            if ((uVar22 & 1) == 0) {
                FUN_0006b3f4(*(word_t *)(lVar6 + 0x10));
                lVar6 = FUN_00499094();
            }
            uVar22 = *(word_t *)(lVar6 + 0x10);
            uVar3 = *(word_t *)(lVar6 + 0x18) >> 1 <= uVar22;
            if (uVar3) {
                uVar11 = FUN_0006b42c();
                lVar6 = FUN_00499094(uVar11, uVar22 + 1, 1, lVar6);
            }
            *(word_t *)(lVar6 + 0x10) = uVar22 + 1;
            lVar17 = lVar6 + uVar22 * 0x20;
            *(word_t *)(lVar17 + 0x20) = lVar14;
            *(word_t *)(lVar17 + 0x28) = uVar28;
            FUN_004ab420();
            *(word_t *)(unaff_x20 + 0x60) = lVar6;
            FUN_004abaa0();
            sk_bcg_0047a258();
            if (unaff_x21 != 0) {
                FUN_0036b118(uVar5);
                FUN_004abaa0();
                FUN_004a3918();
                goto label_b7c0;
            }
            FUN_004abaa0();
            FUN_004a3918();
            lVar6 = *(word_t *)(unaff_x20 + 8);
            uVar22 = FUN_003a261c(lVar6);
            if ((uVar22 & 1) == 0) {
                FUN_0006b3f4(*(word_t *)(lVar6 + 0x10));
                lVar6 = FUN_00499158();
            }
            lVar14 = *(word_t *)(lVar6 + 0x10);
            FUN_004ac68c(*(word_t *)(lVar6 + 0x18));
            if (uVar3) {
                FUN_004aa720();
                lVar6 = FUN_00499158();
            }
            *(word_t *)(lVar6 + 0x10) = uVar25;
            *(word_t *)(lVar6 + lVar14 * 8 + 0x20) = 0x1300000000000000;
            *(word_t *)(unaff_x20 + 8) = lVar6;
            uVar22 = FUN_003a261c(lVar6);
            if ((uVar22 & 1) == 0) {
                FUN_0006b3f4(*(word_t *)(lVar6 + 0x10));
                lVar6 = FUN_00499158();
            }
            lVar14 = *(word_t *)(lVar6 + 0x10);
            FUN_004ac68c(*(word_t *)(lVar6 + 0x18));
            if (uVar3) {
                FUN_004aa720();
                lVar6 = FUN_00499158();
            }
            *(word_t *)(lVar6 + 0x10) = uVar25;
            *(word_t *)(lVar6 + lVar14 * 8 + 0x20) = 0x400000000000000;
            *(word_t *)(unaff_x20 + 8) = lVar6;
            lVar17 = *(word_t *)(unaff_x20 + 0x60);
            uVar22 = FUN_003a261c(lVar17);
            if ((uVar22 & 1) == 0) {
                FUN_0006b3f4(*(word_t *)(lVar17 + 0x10));
                lVar17 = FUN_00499094();
            }
            lVar18 = *(word_t *)(lVar17 + 0x10);
            FUN_004ac89c(*(word_t *)(lVar17 + 0x18));
            if (uVar3) {
                FUN_004aa720();
                lVar17 = FUN_00499094();
            }
            *(word_t *)(lVar17 + 0x10) = uVar25;
            lVar18 = lVar17 + lVar18 * 0x20;
            *(word_t *)(lVar18 + 0x20) = lVar14;
            *(word_t *)(lVar18 + 0x28) = uVar10;
            FUN_004ab420();
            *(word_t *)(unaff_x20 + 0x60) = lVar17;
            uVar11 = *(word_t *)(lVar6 + 0x10);
            lVar14 = *(word_t *)(unaff_x20 + 0x58);
            uVar22 = FUN_003a261c(lVar14);
            if ((uVar22 & 1) == 0) {
                lVar14 = FUN_0049a4a4(lVar14);
            }
            if (*(word_t *)(lVar14 + 0x10) <= uVar28) {
                CL4_SWBP(0x47b828);
            }
            lVar6 = lVar14 + uVar28 * 0x10;
            *(word_t *)(lVar6 + 0x20) = uVar11;
            *(unsigned char *)(lVar6 + 0x28) = 0;
            *(word_t *)(unaff_x20 + 0x58) = lVar14;
        }
        uVar5 = FUN_0036b118(lVar6, uVar5);
        if (*(word_t *)(local_430 + 0x10) == 0) {
            CL4_SWBP(0x47b82c);
        }
        el_pair = FUN_004ab980(uVar5, local_430 + *(word_t *)(local_430 + 0x10) * 0x160 + -0x140).lo;
        FUN_00117cc4(el_pair.lo, el_pair.hi, 0x160);
        uVar5 = FUN_004ab980().lo;
        FUN_004a3940(uVar5, auStack_428);
        FUN_004ab980();
        sk_bcg_0047a258();
        FUN_004ab980();
        FUN_004a3918();
        if (unaff_x21 == 0) {
            sk_bcg_00477494(uVar10);
        }
label_b7c0:
        FUN_0036b118(local_430);
    } else {
        uVar10 = sk_bcg_004772d0(unaff_x20);
        uVar5 = sk_bcg_00477338(1, local_430);
        FUN_0036b270(local_430);
        pcVar13 = section_00000158.sectname + 8;
        lVar6 = local_500;
        for (; in_x3 >> 1 != uVar12; uVar12 = uVar12 + 1) {
            if ((long)(in_x3 >> 1) <= (long)uVar12) {
                CL4_SWBP(0x47b81c);
            }
            FUN_004ac138();
            FUN_004ac8a8();
            FUN_00117cc4();
            lVar14 = *(word_t *)(unaff_x20 + 0x58);
            uVar22 = *(word_t *)(lVar14 + 0x10);
            uVar11 = FUN_004ac138();
            FUN_004a3940(uVar11, auStack_168);
            uVar25 = FUN_003a261c(lVar14);
            if ((uVar25 & 1) == 0) {
                FUN_004aa94c(uVar25, uVar22 + 1);
                lVar14 = FUN_00498fd0();
            }
            uVar25 = *(word_t *)(lVar14 + 0x10);
            if (*(word_t *)(lVar14 + 0x18) >> 1 <= uVar25) {
                uVar11 = FUN_0006b42c();
                FUN_00351c7c(uVar11, uVar25 + 1);
                lVar14 = FUN_00498fd0();
            }
            *(word_t *)(lVar14 + 0x10) = uVar25 + 1;
            FUN_004ab8ac(lVar14 + uVar25 * 0x10);
            *(word_t *)(unaff_x20 + 0x58) = lVar14;
            uVar25 = FUN_003a261c(lVar6);
            if ((uVar25 & 1) == 0) {
                FUN_0006b3f4(*(word_t *)(lVar6 + 0x10));
                lVar6 = FUN_00499158();
            }
            uVar25 = *(word_t *)(lVar6 + 0x10);
            if (*(word_t *)(lVar6 + 0x18) >> 1 <= uVar25) {
                FUN_000ec004();
                lVar6 = FUN_00499158();
            }
            *(word_t *)(lVar6 + 0x10) = uVar25 + 1;
            *(word_t *)(lVar6 + uVar25 * 8 + 0x20) = 0x1100000000000000;
            *(word_t *)(unaff_x20 + 8) = lVar6;
            lVar6 = *(word_t *)(unaff_x20 + 0x60);
            uVar28 = FUN_003a261c(lVar6);
            if ((uVar28 & 1) == 0) {
                FUN_0006b3f4(*(word_t *)(lVar6 + 0x10));
                lVar6 = FUN_00499094();
            }
            uVar28 = *(word_t *)(lVar6 + 0x10);
            if (*(word_t *)(lVar6 + 0x18) >> 1 <= uVar28) {
                uVar11 = FUN_0006b42c();
                FUN_00350774(uVar11, uVar28 + 1);
                lVar6 = FUN_00499094();
            }
            *(word_t *)(lVar6 + 0x10) = uVar28 + 1;
            lVar14 = lVar6 + uVar28 * 0x20;
            *(word_t *)(lVar14 + 0x20) = uVar25;
            *(word_t *)(lVar14 + 0x28) = uVar22;
            FUN_004ab420();
            *(word_t *)(unaff_x20 + 0x60) = lVar6;
            FUN_004ac138();
            sk_bcg_0047a258();
            if (unaff_x21 != 0) {
                FUN_0036b118(uVar5);
                FUN_0036b118(local_430);
                FUN_004ac138();
                FUN_004a3918();
                goto label_b7e0;
            }
            FUN_004ac138();
            FUN_004a3918();
            lVar6 = *(word_t *)(unaff_x20 + 8);
            uVar25 = FUN_003a261c(lVar6);
            if ((uVar25 & 1) == 0) {
                FUN_0006b3f4(*(word_t *)(lVar6 + 0x10));
                lVar6 = FUN_00499158();
            }
            uVar25 = *(word_t *)(lVar6 + 0x10);
            lVar14 = uVar25 + 1;
            if (*(word_t *)(lVar6 + 0x18) >> 1 <= uVar25) {
                uVar11 = FUN_0006b42c();
                lVar6 = FUN_00499158(uVar11, lVar14, 1, lVar6);
            }
            *(word_t *)(lVar6 + 0x10) = lVar14;
            *(word_t *)(lVar6 + uVar25 * 8 + 0x20) = 0x1300000000000000;
            *(word_t *)(unaff_x20 + 8) = lVar6;
            lVar17 = uVar25 + 2;
            if ((long)(*(word_t *)(lVar6 + 0x18) >> 1) < lVar17) {
                FUN_000ec004();
                lVar6 = FUN_00499158();
            }
            *(word_t *)(lVar6 + 0x10) = lVar17;
            *(word_t *)(lVar6 + lVar14 * 8 + 0x20) = 0x1d00000000000000;
            *(word_t *)(unaff_x20 + 8) = lVar6;
            lVar14 = *(word_t *)(unaff_x20 + 0x58);
            uVar25 = FUN_003a261c(lVar14);
            if ((uVar25 & 1) == 0) {
                lVar14 = FUN_0049a4a4(lVar14);
            }
            if (*(word_t *)(lVar14 + 0x10) <= uVar22) {
                CL4_SWBP(0x47b824);
            }
            lVar18 = lVar14 + uVar22 * 0x10;
            *(word_t *)(lVar18 + 0x20) = lVar17;
            *(unsigned char *)(lVar18 + 0x28) = 0;
            *(word_t *)(unaff_x20 + 0x58) = lVar14;
            pcVar13 = unaff_x20;
        }
        FUN_0036b118(pcVar13, uVar5);
        FUN_004aa464();
        FUN_00498b28(extraout_x16);
        FUN_00350618();
        FUN_00498c1c();
        FUN_004aab88(*(word_t *)(unaff_x20 + 8));
        *(word_t *)(extraout_x9 + 0x20) = 0x1100000000000000;
        *(word_t *)(unaff_x20 + 8) = extraout_x8;
        uVar5 = FUN_00481918(uVar10);
        if (*(word_t *)(local_430 + 0x10) == 0) {
            FUN_0036b118(local_430);
            CL4_SWBP(0x47b840);
        }
        el_pair = FUN_004ac6b0(uVar5, local_430 + *(word_t *)(local_430 + 0x10) * 0x160 + -0x140).lo;
        FUN_00117cc4(el_pair.lo, el_pair.hi, 0x160);
        uVar5 = FUN_004ac6b0().lo;
        FUN_004a3940(uVar5, auStack_168);
        FUN_0036b118(local_430);
        FUN_004ac6b0();
        sk_bcg_0047a258();
        FUN_004ac6b0();
        FUN_004a3918();
        if (unaff_x21 == 0) {
            FUN_004aa4ac();
            FUN_00498b28(extraout_x16_00);
            FUN_00350518();
            FUN_00498c1c();
            FUN_004aa9c0(*(word_t *)(unaff_x20 + 8));
            *(word_t *)(extraout_x9_00 + 0x20) = 0x1300000000000000;
            *(word_t *)(unaff_x20 + 8) = extraout_x8_00;
            FUN_00498b28(uVar22);
            FUN_00350518();
            FUN_00498c1c();
            FUN_004aa9c0(*(word_t *)(unaff_x20 + 8));
            *(word_t *)(extraout_x9_01 + 0x20) = 0x1d00000000000000;
            *(word_t *)(unaff_x20 + 8) = extraout_x8_01;
            sk_bcg_00477494(uVar10);
            lVar6 = *(word_t *)(*(word_t *)unaff_x20 + 0x10);
            if (lVar6 == 0) {
                CL4_SWBP(0x47b844);
            }
            el_pair.hi = *(unsigned int *)(*(word_t *)unaff_x20 + lVar6 * 4 + 0x1c);
            FUN_004aa464();
            FUN_00498b28(extraout_x16_01);
            lVar14 = *(word_t *)(*(word_t *)(unaff_x20 + 8) + 0x10);
            FUN_00350470();
            FUN_00498c1c();
            lVar6 = *(word_t *)(unaff_x20 + 8);
            *(word_t *)(lVar6 + 0x10) = lVar14 + 1;
            uVar10 = 0x700000000010001;
            if ((el_pair.hi >> 0x10 & 1) != 0) {
                uVar10 = 0x700000000010000;
            }
            *(word_t *)(lVar6 + 0x20 + lVar14 * 8) = uVar10;
            *(word_t *)(unaff_x20 + 8) = lVar6;
        }
    }
label_b7e0:
    FUN_00353d14(unaff_x30);
}


/* FUN_0047b844 @ 0x0047b844   (est. sk_bcg_0047b844)
 * Ghidra: void sk_bcg_0047b844(void)
 * Emitter for the customCharacter instruction: reads a 0xb0-byte
 * instruction element, and depending on the sub-kind emitted by
 * FUN_0047c3a4 builds the output opcode. For an empty backref it emits a
 * plain custom-char op (0xe0-prefixed); otherwise it evaluates the
 * conditional/backreference path, and when the scalar-range flags demand it
 * (0x47bc2c/0x47bc30 SWBP checks) it materialises the 'Invalid range'
 * diagnostic (0x687de8/0x687e10 strings) or the combined custom-char +
 * range op (0x2d, 0xe1-prefixed). Ends via FUN_004aca94/FUN_00353d14.
 * Confidence: medium   Notes: s_Handled_in__emitCustomCharacterC_005e28c0,
 * 'Invalid range' 0x2064696c61766e49 'Invalid range' literals, DAT globals;
 * SWBP at 0x47bc2c..0x47bc34. */
static void sk_bcg_0047b844(void)
{
    word_t uVar1, uVar2, uVar3, uVar5, uVar6, uVar7, uVar8, uVar9;
    word_t pcVar4;
    word_t uVar5b;
    word_t lVar12;
    word_t *puVar11;
    unsigned char (*pauVar10)[16];
    word_t local_3f8, local_348;
    word_t uStack_3f0, uStack_340, uStack_330, uStack_320, uStack_308, uStack_300;
    word_t uStack_2f8, uStack_2e0, uStack_2d0, uStack_2e8;
    word_t local_2f0, local_2e8, local_2d8, local_2c8, local_318;
    word_t local_338, local_328, local_310;
    unsigned char auStack_2c0[352], auStack_160[176], auStack_b0[176];
    wpair_t el_pair, r_pair;

    el_pair.lo = FUN_00353cfc();
    FUN_00117cc4(auStack_2c0);
    uVar8 = FUN_0049df0c(auStack_2c0);
    uVar9 = FUN_0049df18(auStack_2c0);
    r_pair.hi = 0;
    r_pair.lo = uVar9;
    uVar5b = (uVar8 & 0xffffffff) == 7;
    switch (uVar8 & 0xffffffff) {
    default:
        FUN_00002874(s_Handled_in__emitCustomCharacterC_005e28c0);
        FUN_003593c0();
        FUN_00002818();
        break;
    case 1:
        FUN_00117cc4(auStack_b0, uVar9, 0xb0);
        FUN_00117cc4(auStack_160, uVar9 + 0xb0, 0xb0);
        el_pair = sk_bcg_0047c3a4();
        lVar12 = el_pair.hi;
        if (lVar12 == 0) {
            local_348 = 0;
            uStack_340 = 0xe000000000000000;
            el_pair.lo = FUN_00117cc4(&local_3f8, auStack_b0, 0xb0);
            FUN_000f4a9c(el_pair.lo, el_pair.hi, 0x6868f8);
            FUN_00205844(&local_3f8, &local_348);
            FUN_004abb8c();
            FUN_004ab6b8(local_348, uStack_340);
            FUN_004ab6ac(&local_2e8);
            thunk_FUN_0044f818();
            FUN_004aa370();
            FUN_004aaf9c();
            puVar11[1] = uStack_2e0;
            *puVar11 = local_2e8;
            puVar11[3] = uStack_2d0;
            puVar11[2] = local_2d8;
            puVar11 = extraout_x1_01;
            local_318 = local_2c8;
label_bb78:
            puVar11[4] = local_318;
        } else {
            sk_bcg_0047c3a4();
            if (extraout_x1 == 0) {
                FUN_003a25d4(lVar12);
                local_348 = 0;
                uStack_340 = 0xe000000000000000;
                el_pair.lo = FUN_00117cc4(&local_3f8, auStack_160, 0xb0);
                FUN_000f4a9c(el_pair.lo, el_pair.hi, 0x6868f8);
                FUN_00205844(&local_3f8, &local_348);
                FUN_004abb8c();
                FUN_004ab6b8(local_348, uStack_340);
                FUN_004ab6ac(&local_310);
                thunk_FUN_0044f818();
                FUN_004aa370();
                FUN_004aaf9c();
                puVar11[1] = uStack_308;
                *puVar11 = local_310;
                puVar11[3] = uStack_2f8;
                puVar11[2] = uStack_300;
                puVar11 = extraout_x1_03;
                local_318 = local_2f0;
                goto label_bb78;
            }
            FUN_00354410();
            FUN_000a6e14();
            uVar9 = FUN_00417aa0();
            if ((uVar9 & 1) == 0) {
label_baec:
                FUN_003a25d4(auStack_160);
                FUN_004aa610();
                *extraout_x1_02 = el_pair;
                pauVar10 = extraout_x1_02;
            } else {
                FUN_000a6e14();
                FUN_001ae8a8();
                uVar6 = FUN_0034ecc8();
                if (uVar5b) {
                    CL4_SWBP(0x47bc2c);
                }
                uVar9 = FUN_0047ea18();
                if ((uVar9 & 1) == 0) goto label_baec;
                FUN_003a25d4(lVar12);
                FUN_00351714();
                uVar9 = FUN_00417aa0();
                if ((uVar9 & 1) != 0) {
                    FUN_00351714();
                    FUN_001ae8a8();
                    uVar7 = FUN_0034ecc8();
                    if (uVar5b) {
                        CL4_SWBP(0x47bc30);
                    }
                    uVar9 = FUN_0047ea18();
                    if ((uVar9 & 1) != 0) {
                        FUN_003a25d4(auStack_160);
                        if (uVar6 <= uVar7) {
                            lVar12 = *(word_t *)(el_pair.lo + 0x10);
                            if (lVar12 == 0) {
                                CL4_SWBP(0x47bc34);
                            }
                            uVar2 = *(unsigned int *)(el_pair.lo + lVar12 * 4 + 0x1c);
                            uVar1 = uVar2 & 0x10000;
                            uVar3 = 0x687de8;
                            if (uVar1 != 0) {
                                uVar3 = 0x687e10;
                            }
                            lVar12 = FUN_0036a940(0x4aa250, uVar3, 0x1d, 7);
                            el_pair.hi = lVar12;
                            el_pair.lo = lVar12;
                            *(char *)(lVar12 + 0x10) = (char)(uVar1 >> 0x10);
                            *(unsigned int *)(lVar12 + 0x14) = uVar6;
                            *(unsigned int *)(lVar12 + 0x18) = uVar7;
                            *(unsigned char *)(lVar12 + 0x1c) = (unsigned char)uVar2 & 1;
                            goto label_case4;
                        }
                        local_3f8 = 0;
                        uStack_3f0 = 0xe000000000000000;
                        FUN_002a4ab4(0x13);
                        local_348 = local_3f8;
                        uStack_340 = uStack_3f0;
                        thunk_FUN_002acbb8(0x2064696c61766e49, 0xee002065676e6172);
                        FUN_00117cc4(&local_3f8, auStack_b0, 0xb0);
                        FUN_00205844(&local_3f8, &local_348, 0x6868f8, 0x6756a8, 0x66e1b8);
                        thunk_FUN_002acbb8(0x2d, 0xe100000000000000);
                        FUN_00117cc4(&local_3f8, auStack_160, 0xb0);
                        FUN_00352c40(&local_3f8, &local_348, 0x6868f8);
                        FUN_00205844();
                        FUN_004ab6b8(local_348, uStack_340);
                        FUN_004ab6ac(&local_338);
                        thunk_FUN_0044f818();
                        FUN_004aa370();
                        FUN_004aaf9c();
                        puVar11[1] = uStack_330;
                        *puVar11 = local_338;
                        puVar11[3] = uStack_320;
                        puVar11[2] = local_328;
                        puVar11 = extraout_x1_00;
                        goto label_bb78;
                    }
                }
                FUN_004aa610();
                *(word_t *)*extraout_x1_04 = uVar8;
                *(unsigned char **)(*extraout_x1_04 + 8) = auStack_160;
                pauVar10 = extraout_x1_04;
            }
            pauVar10[1][0] = 1;
        }
        el_pair = FUN_0036986c().lo;
label_case4:
        el_pair = FUN_004aca94(el_pair.lo, el_pair.hi);
        FUN_00353d14(el_pair.lo, el_pair.hi, el_pair.hi);
        return;
    case 3:
        FUN_00002818(s__StringProcessing_ByteCodeGen_sw_005e2820 + 0x10, s_Fatal_error_005accd0, 0);
        break;
    case 4:
        goto label_case4;
    }
    /* Subroutine does not return */
    FUN_001afa84();
}


/* FUN_0047bcc8 @ 0x0047bcc8   (est. sk_bcg_0047bcc8)
 * Ghidra: void sk_bcg_0047bcc8(void)
 * Emits an instruction into the code stream with a scalar-range tag:
 * reads the current code-list count, appends an entry whose 0x20 word is
 * the low-byte scalar (from FUN_00350980) tagged 0xb00000000000001, then
 * releases handles. Sibling of 0047bd74 (distinguished only by the tag
 * constant 0xb00000000000001 vs 0xb00000000000000).
 * Confidence: medium   Notes: many out-of-slice emitters. */
static void sk_bcg_0047bcc8(void)
{
    word_t uVar1;
    word_t extraout_x8, extraout_x8_00;
    word_t extraout_x9, extraout_x9_00;
    word_t extraout_x16, extraout_x16_00;
    word_t *unaff_x20;
    word_t *plVar2;
    word_t unaff_x21, unaff_x22, unaff_x30;
    word_t lVar3;

    FUN_00084220();
    uVar1 = FUN_00350980();
    plVar2 = unaff_x20 + 6;
    lVar3 = *(word_t *)(*plVar2 + 0x10);
    FUN_004aa6d8();
    FUN_00498b28(extraout_x16);
    FUN_00350618();
    FUN_00498c1c();
    FUN_004aa580(*plVar2);
    *(unsigned char *)(extraout_x9 + 0x20) = uVar1;
    *(word_t *)(extraout_x9 + 0x28) = unaff_x22;
    *(word_t *)(extraout_x9 + 0x30) = unaff_x21;
    *plVar2 = extraout_x8;
    FUN_004aa3e4();
    FUN_00498b28(extraout_x16_00);
    FUN_00100efc();
    FUN_00498c1c();
    FUN_004aabf4(*unaff_x20);
    *(word_t *)(extraout_x9_00 + 0x20) = lVar3 << 0x10 | 0xb00000000000001;
    *unaff_x20 = extraout_x8_00;
    FUN_00084234(unaff_x30);
}

/* FUN_0047bd74 @ 0x0047bd74   (est. sk_bcg_0047bd74)
 * Ghidra: void sk_bcg_0047bd74(void)
 * Same shape as 0047bcc8 (scalar-range code entry emitter), differing only
 * in the stored tag constant 0xb00000000000000 instead of
 * 0xb00000000000001. Used on the non-flattened path in the generator.
 * Confidence: medium   Notes: identical body to 0047bcc8 apart from tag. */
static void sk_bcg_0047bd74(void)
{
    word_t uVar1;
    word_t extraout_x8, extraout_x8_00;
    word_t extraout_x9, extraout_x9_00;
    word_t extraout_x16, extraout_x16_00;
    word_t *unaff_x20;
    word_t *plVar2;
    word_t unaff_x21, unaff_x22, unaff_x30;
    word_t lVar3;

    FUN_00084220();
    uVar1 = FUN_00350980();
    plVar2 = unaff_x20 + 6;
    lVar3 = *(word_t *)(*plVar2 + 0x10);
    FUN_004aa6d8();
    FUN_00498b28(extraout_x16);
    FUN_00350618();
    FUN_00498c1c();
    FUN_004aa580(*plVar2);
    *(unsigned char *)(extraout_x9 + 0x20) = uVar1;
    *(word_t *)(extraout_x9 + 0x28) = unaff_x22;
    *(word_t *)(extraout_x9 + 0x30) = unaff_x21;
    *plVar2 = extraout_x8;
    FUN_004aa3e4();
    FUN_00498b28(extraout_x16_00);
    FUN_00100efc();
    FUN_00498c1c();
    FUN_004aabf4(*unaff_x20);
    *(word_t *)(extraout_x9_00 + 0x20) = lVar3 << 0x10 | 0xb00000000000000;
    *unaff_x20 = extraout_x8_00;
    FUN_00084234(unaff_x30);
}

/* FUN_0047be1c @ 0x0047be1c   (est. sk_bcg_0047be1c)
 * Ghidra: void sk_bcg_0047be1c(undefined8 param_1,undefined8 param_2,uint param_3)
 * Collects a list of 0x160-byte instruction elements from the generator
 * root, partitioning each element between two destination lists depending
 * on whether FUN_0047e5dc classifies it as kind 2, then (when both lists
 * are non-empty) builds a two-element container node (0x2e0 allocation,
 * _DAT_004c2450 metatype) holding both 0x160-byte sub-lists. Returns via
 * FUN_0008e500 with param_3's low bit.
 * Confidence: medium   Notes: _DAT_004c2450, uRam00000000004c2458 globals;
 * out-of-slice classification + list helpers. */
static void sk_bcg_0047be1c(word_t param_1, word_t param_2, unsigned int param_3)
{
    word_t uVar2, uVar3;
    word_t lVar1, lVar4, lVar5, lVar6, lVar7, lVar8;
    word_t unaff_x22, unaff_x30;
    wpair_t root_pair, c_pair;
    word_t local_428, local_2c8;
    unsigned char local_420, local_2c0;
    unsigned char auStack_168[360];

    root_pair.lo = FUN_0008e518();
    lVar4 = root_pair.hi;
    lVar8 = *(word_t *)(lVar4 + 0x10);
    lVar6 = unaff_x22;
    if (lVar8 == 0) {
        FUN_00466244();
    } else {
        lVar7 = lVar4 + 0x20;
        FUN_00466244();
        do {
            FUN_00117cc4(auStack_168, lVar7, 0x160);
            FUN_004a3940(auStack_168, &local_2c8);
            lVar1 = FUN_0047e5dc(root_pair.lo, 0);
            if (lVar1 == 2) {
                uVar2 = FUN_003a261c(lVar6);
                lVar1 = lVar6;
                if ((uVar2 & 1) == 0) {
                    FUN_004aa44c(*(word_t *)(lVar6 + 0x10));
                    FUN_0006b3f4();
                    lVar1 = FUN_00498e50();
                }
                uVar2 = *(word_t *)(lVar1 + 0x10);
                lVar5 = uVar2 + 1;
                lVar6 = lVar1;
                if (*(word_t *)(lVar1 + 0x18) >> 1 <= uVar2) {
                    uVar3 = FUN_0006b42c();
                    FUN_004abd90(uVar3, lVar5);
                    lVar1 = FUN_00498e50();
                    lVar6 = lVar1;
                }
            } else {
                uVar2 = FUN_003a261c(unaff_x22);
                lVar1 = unaff_x22;
                if ((uVar2 & 1) == 0) {
                    FUN_004aa44c(*(word_t *)(unaff_x22 + 0x10));
                    FUN_0006b3f4();
                    lVar1 = FUN_00498e50();
                }
                uVar2 = *(word_t *)(lVar1 + 0x10);
                lVar5 = uVar2 + 1;
                unaff_x22 = lVar1;
                if (*(word_t *)(lVar1 + 0x18) >> 1 <= uVar2) {
                    uVar3 = FUN_0006b42c();
                    lVar1 = FUN_00498e50(uVar3, lVar5, 1, lVar1, FUN_00498328, &LAB_0049853c, FUN_00499a0c);
                    unaff_x22 = lVar1;
                }
            }
            *(word_t *)(lVar1 + 0x10) = lVar5;
            FUN_00117cc4(lVar1 + uVar2 * 0x160 + 0x20, auStack_168, 0x160);
            lVar7 = lVar7 + 0x160;
            lVar8 = lVar8 + -1;
        } while (lVar8 != 0);
    }
    if ((*(word_t *)(unaff_x22 + 0x10) == 0) || (*(word_t *)(lVar6 + 0x10) == 0)) {
        FUN_0036b270(lVar4);
        FUN_0036b118(lVar6);
        FUN_0036b118(unaff_x22);
    } else {
        uVar3 = FUN_004ab630();
        lVar4 = FUN_0036a940(uVar3, 0x2e0, 7);
        uVar3 = _DAT_004c2450;
        *(word_t *)(lVar4 + 0x18) = uRam00000000004c2458;
        *(word_t *)(lVar4 + 0x10) = uVar3;
        local_420 = 0;
        local_428 = unaff_x22;
        FUN_004a3390(&local_428);
        FUN_00117cc4(lVar4 + 0x20, &local_428, 0x160);
        local_2c0 = 0;
        local_2c8 = lVar6;
        FUN_004a3390(&local_2c8);
        FUN_00117cc4(lVar4 + 0x180, &local_2c8, 0x160);
    }
    FUN_0008e500(lVar4, param_3 & 1, unaff_x30);
}


/* FUN_0047c0dc @ 0x0047c0dc   (est. sk_bcg_0047c0dc)
 * Ghidra: bool sk_bcg_0047c0dc(void)
 * Recursive predicate over the generator node list: reads a node, and
 * returns true if it is kind 4; for a kind-2 (nested list) node it walks
 * the 0x160-byte elements and recurses, returning true iff every element
 * also satisfies the predicate; otherwise false. Leaf/false detection is
 * the fail case used by the flattening walk.
 * Confidence: medium   Notes: recursive; out-of-slice kind helpers. */
static bool sk_bcg_0047c0dc(void)
{
    bool bVar1;
    word_t iVar2;
    word_t *plVar3;
    word_t uVar4;
    word_t lVar5, lVar6;
    unsigned char auStack_460[352], auStack_300[352], auStack_1a0[352];

    FUN_00117cc4(auStack_300);
    iVar2 = FUN_0049df0c(auStack_300);
    if (iVar2 == 4) {
        FUN_0049df18(auStack_300);
        bVar1 = true;
    } else if (iVar2 == 2) {
        plVar3 = (word_t *)FUN_0049df18(auStack_300);
        lVar6 = *(word_t *)(*plVar3 + 0x10) + 1;
        lVar5 = *plVar3 + 0x20;
        do {
            lVar6 = lVar6 + -1;
            bVar1 = lVar6 == 0;
            if (lVar6 == 0) {
                return true;
            }
            FUN_00117cc4(auStack_1a0, lVar5, 0x160);
            FUN_004a3940(auStack_1a0, auStack_460);
            uVar4 = sk_bcg_0047c0dc();
            FUN_004a3918(auStack_1a0);
            lVar5 = lVar5 + 0x160;
        } while ((uVar4 & 1) != 0);
    } else {
        bVar1 = false;
    }
    return bVar1;
}

/* FUN_0047c1b0 @ 0x0047c1b0   (est. sk_bcg_0047c1b0)
 * Ghidra: void sk_bcg_0047c1b0(void)
 * Recursive instruction-sequence collector: given a node, walks its
 * elements (recursing on each) and concatenates the resulting bytecode
 * runs into a growing list, with overflow-carry / bounds SWBP checks
 * (0x47c38c..0x47c3a4). Builds a fresh node of metatype _DAT_004baeb0 when
 * a new root is required. Used to assemble sequence/backreference bodies.
 * Confidence: medium   Notes: _DAT_004baeb0, uRam00000000004baeb8 globals;
 * recursive; many emitters. */
static word_t sk_bcg_0047c1b0(word_t p1)
{
    word_t pcVar1;
    word_t in_ZR;
    word_t lVar2, lVar6;
    word_t uVar3, uVar4, uVar5, uVar7, uVar8, uVar9, uVar10;
    word_t extraout_x1, extraout_w8, extraout_x8;
    word_t unaff_x19, unaff_x20, unaff_x21, unaff_x24;
    (void)p1;  /* register-residue arg */

    FUN_0008e518();
    FUN_004aae2c();
    if (in_ZR || extraout_w8 == 4) {
        FUN_004ac114();
        uVar5 = *(word_t *)((unaff_x20 & unaff_x21) + 0x10);
        FUN_0036b270(uVar5 & unaff_x21);
        unaff_x19 = sk_bcg_0047c1b0(uVar5);
        FUN_0036b118(uVar5 & unaff_x21);
    } else if (extraout_w8 == 1) {
        FUN_004aba88();
        lVar6 = *(word_t *)((unaff_x20 & unaff_x24) + 0x10);
        uVar9 = *(word_t *)(lVar6 + 0x10);
        FUN_0036b270(lVar6);
        FUN_000a6fe0();
        for (uVar5 = 0; uVar9 != uVar5; uVar5 = uVar5 + 1) {
            if (*(word_t *)(lVar6 + 0x10) <= uVar5) {
                CL4_SWBP(0x47c38c);
            }
            uVar7 = *(word_t *)(lVar6 + uVar5 * 8 + 0x20);
            FUN_0036b270(uVar7 & unaff_x24);
            lVar2 = sk_bcg_0047c1b0(uVar7);
            FUN_0036b118(uVar7 & unaff_x24);
            uVar8 = *(word_t *)(lVar2 + 0x10);
            uVar10 = *(word_t *)(unaff_x19 + 0x10);
            uVar7 = uVar10 + uVar8;
            if (SCARRY8(uVar10, uVar8)) {
                CL4_SWBP(0x47c390);
            }
            uVar3 = FUN_003a261c(unaff_x19);
            if ((int)uVar3 == 0) {
                if ((long)uVar10 <= (long)uVar7) {
                    uVar10 = uVar7;
                }
label_c2ac:
                FUN_00350774(uVar3, uVar10);
                unaff_x19 = FUN_00498f0c();
                FUN_004ac778();
                uVar4 = extraout_x8;
            } else {
                uVar4 = *(word_t *)(unaff_x19 + 0x18) >> 1;
                if ((long)uVar4 < (long)uVar7) {
                    if (uVar10 <= uVar7) {
                        uVar10 = uVar7;
                    }
                    goto label_c2ac;
                }
            }
            uVar4 = uVar4 - *(word_t *)(unaff_x19 + 0x10);
            if ((long)uVar4 < 0) {
                CL4_SWBP(0x47c394);
            }
            if (*(word_t *)(lVar2 + 0x10) == 0) {
                FUN_0036b118(lVar2);
                if (uVar8 != 0) {
                    CL4_SWBP(0x47c398);
                }
            } else {
                if (uVar4 < uVar8) {
                    CL4_SWBP(0x47c39c);
                }
                uVar7 = unaff_x19 + *(word_t *)(unaff_x19 + 0x10) * 8 + 0x20;
                if (lVar2 + 0x20U < uVar7 + uVar8 * 8 && uVar7 < lVar2 + 0x20U + uVar8 * 8) {
                    CL4_SWBP(0x47c3a4);
                }
                FUN_00351b78();
                FUN_0035b67c();
                FUN_0036b118(lVar2);
                if (uVar8 != 0) {
                    if (SCARRY8(*(word_t *)(unaff_x19 + 0x10), uVar8)) {
                        CL4_SWBP(0x47c3a0);
                    }
                    *(word_t *)(unaff_x19 + 0x10) = *(word_t *)(unaff_x19 + 0x10) + uVar8;
                }
            }
        }
        FUN_0036b118(lVar6);
    } else {
        FUN_004aa6c4();
        FUN_00002534();
        FUN_00359018();
        unaff_x19 = FUN_0036a940();
        uVar3 = _DAT_004baeb0;
        *(word_t *)(unaff_x19 + 0x18) = uRam00000000004baeb8;
        *(word_t *)(unaff_x19 + 0x10) = uVar3;
        *(word_t *)(unaff_x19 + 0x20) = unaff_x20;
        FUN_0036b270(unaff_x20 & 0xffffffffffffffb);
    }
    FUN_0008e500(unaff_x19, extraout_x1);
    return unaff_x19;   /* register-carried return value */
}


/* FUN_0047c3a4 @ 0x0047c3a4   (est. sk_bcg_0047c3a4)
 * Ghidra: void sk_bcg_0047c3a4(void)
 * Emits the customCharacter sub-instruction: classifies the parsed element
 * (FUN_0049e2d4) and, for the primary/overloaded case, computes a scalar
 * value via FUN_004ac6bc/FUN_004ac6e4 and produces a code-slot pair via
 * FUN_00255d4c/FUN_00294cb4(SWBP if the hi word is negative); the empty
 * case copies the element through FUN_004acd14. Ends with FUN_003507e0.
 * Confidence: medium   Notes: SWBP at 0x47c468; out-of-slice helpers. */
static void sk_bcg_0047c3a4(void)
{
    word_t pcVar1;
    word_t uVar2, uVar3, uVar5;
    word_t iVar4;
    word_t extraout_w8;
    wpair_t el_pair;
    word_t local_190[22];
    unsigned char auStack_e0[176];

    FUN_004ab0f0(auStack_e0);
    FUN_00117cc4();
    iVar4 = FUN_0049e2d4(auStack_e0);
    uVar2 = iVar4 != 0;
    uVar3 = iVar4 == 1;
    if (uVar3) {
        FUN_0049e2f0(auStack_e0);
        FUN_004abc0c();
        if (uVar2 && !uVar3) {
            FUN_004ac150();
            if (uVar2) {
                FUN_00463bd4();
                uVar5 = FUN_004ac6bc();
            } else {
                uVar5 = FUN_004ac6e4();
            }
        } else {
            uVar5 = (word_t)(extraout_w8 + 1);
        }
        el_pair = FUN_00255d4c(uVar5).lo;
        local_190[0] = el_pair.lo;
        if (el_pair.hi < 0) {
            CL4_SWBP(0x47c468);
        }
        FUN_00294cb4(local_190);
    } else if (iVar4 == 0) {
        FUN_0049e2f0(auStack_e0);
        FUN_004ab0f0(local_190);
        FUN_00117cc4();
        FUN_004acd14(local_190);
    }
    FUN_003507e0();
}

/* FUN_0047c474 @ 0x0047c474   (est. sk_bcg_0047c474)
 * Ghidra: void sk_bcg_0047c474(void)
 * Instruction-slot reference/refcount finaliser: refreshes the element
 * value via FUN_0035199c(optionally FUN_0049c0e4) and, when a non-null
 * sibling is present, pushes a dependent value (offset +0xa0) through
 * FUN_00100efc/FUN_0041c1d8. Then increments the +0x88 refcount, trapping
 * on overflow (SWBP 0x47c4e4).
 * Confidence: medium   Notes: SWBP at 0x47c4e4; small leaf-like emitter. */
static void sk_bcg_0047c474(void)
{
    word_t pcVar1;
    word_t unaff_x20, unaff_x21;
    wpair_t el_pair;

    el_pair = FUN_0035199c().lo;
    if ((el_pair.hi & 0xff) != 1) {
        el_pair = FUN_0049c0e4(*(word_t *)(unaff_x20 + 0x88), el_pair.lo);
    }
    if (unaff_x21 != 0) {
        FUN_00100efc(el_pair.lo, el_pair.hi, *(word_t *)(unaff_x20 + 0xa0));
        FUN_0041c1d8();
    }
    if (!SCARRY8(*(word_t *)(unaff_x20 + 0x88), 1)) {
        *(word_t *)(unaff_x20 + 0x88) = *(word_t *)(unaff_x20 + 0x88) + 1;
        return;
    }
    CL4_SWBP(0x47c4e4);
}

/* FUN_0047c4e4 @ 0x0047c4e4   (est. sk_bcg_0047c4e4)
 * Ghidra: void sk_bcg_0047c4e4(ulong param_1,long param_2)
 * Tiny emitter that packs two fields into a single opcode word
 * (param_1 | param_2 << 0x10) and appends it to the code stream via
 * FUN_004aa494/FUN_00498b28/FUN_004aaf58/FUN_004aa6a8. Final function of
 * the R27 slice.
 * Confidence: medium   Notes: trivial two-field opcode pack. */
static void sk_bcg_0047c4e4(word_t param_1, word_t param_2)
{
    word_t extraout_x16;

    FUN_004aa494(param_1 | param_2 << 0x10);
    FUN_00498b28(extraout_x16);
    FUN_004aaf58();
    FUN_004aa6a8();
}
