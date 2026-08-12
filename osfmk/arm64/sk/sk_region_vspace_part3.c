/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0). Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary; estimates unless matched.
 * Slice 3: 0x21476c - 0x228e28. This is the Swift standard-library runtime support layer
 * embedded in the cL4 kernel (String/UTF8 indexing, Flatten distance, UnsafeBufferPointer,
 * ContiguousArrayBuffer, Float/Float16/Double min-max and bit-pattern parse, fatal-error traps).
 * All rt_* helpers are the shared cL4/Swift runtime OUTSIDE this slice; declared extern. */

#include <stdint.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

typedef uint64_t (*code)();
#define ABS(x) ((x)<0?-(x):(x))
#define CONCAT44(a,b) ((((uint64_t)(a))<<32)|(uint64_t)(b))
#define LZCOUNT(x) (__builtin_clzll((unsigned long long)(x)))
/* 16-byte pair returned by runtime helpers (Ghidra `undefined1 [16]`). */
typedef struct { uint64_t lo; uint64_t hi; uint32_t _hi32; uint16_t _lo16; } rt16;
/* 16-byte value usable both as a lo/hi struct and as a byte array. */
typedef union { struct { uint64_t lo, hi; uint32_t _hi32; uint16_t _lo16; }; uint8_t b[16]; } rt16u;
static inline rt16 rt16_mklo(uint64_t lo){ rt16 r; r.lo=lo; r.hi=0; r._hi32=(uint32_t)(lo>>32); r._lo16=(uint16_t)lo; return r; }
#define SW_BREAK0(...)   ((void*)0) /* SoftwareBreakpoint (null fn ptr) */
#define SCARRY8(a,b)  (((uint64_t)(a)) > ((uint64_t)(a) + (uint64_t)(b)))
#define SBORROW8(a,b) (((uint64_t)(a)) < ((uint64_t)(b)))
/* PAC'd indirect dispatch through the runtime's per-thread table slot 0. */
#define G_00658c00 (*(uint64_t (**)())0x658c00)
#define SW_BREAK(addr) ((void*)0) /* SoftwareBreakpoint(1, addr) -> null fn ptr */
/* Data / callback addresses referenced by the runtime layer. */
extern uint8_t G_00010004, G_0031be54, G_003471a4, G_003471a8, G_005be7c0;
extern uint8_t G_0060e208, G_0060e230, G_0060e458, G_0060e468, G_0060ff00;
extern uint8_t G_0061014c, G_00611b24, LBL_00611b34;
extern uint8_t G_004e7a30[64];
/* Swift fatal-error / module-name string literals (used by the noreturn trap). */
extern uint8_t s_Fatal_error_005accd0[], s_Index_out_of_range_005cd940[],
  s_Negative_value_is_not_representa_005ce190[], s_Not_enough_bits_to_represent_the_005cd650[],
  s_String_index_is_out_of_bounds_005ce6a0[], s_Swift_CollectionOfOne_swift_005d0d40[],
  s_Swift_ContiguousArrayBuffer_swif_005cd960[], s_Swift_FlatMap_swift_005d3ba0[],
  s_Swift_Flatten_swift_005cf8d0[], s_Swift_Integers_swift_005cd680[],
  s_Swift_Optional_swift_005ce1f0[], s_Swift_Range_swift_005cda30[],
  s_Swift_StringUTF8View_swift_005d0670[], s_Swift_UnsafeBufferPointer_swift_005cdc10[],
  s_Unexpectedly_found_nil_while_unw_005cd7d0[], s_UnsafeBufferPointer_has_a_nil_st_005cf020[],
  s_UnsafeBufferPointer_with_negativ_005cdf60[], s_unsafelyUnwrapped_of_nil_optiona_005ce1c0[],
  s_Range_requires_lowerBound_005cda00[];


/* ---- shared cL4/Swift runtime externs (out of slice; bodies owned elsewhere) ---- */
extern uint64_t rt_0001da84(); /* FUN_0001da84 */
extern uint64_t rt_0001df60(); /* FUN_0001df60 */
extern uint64_t rt_00027754(); /* FUN_00027754 */
extern uint64_t rt_00027788(); /* FUN_00027788 */
extern uint64_t rt_000277b8(); /* FUN_000277b8 */
extern uint64_t rt_000277e8(); /* FUN_000277e8 */
extern uint64_t rt_00027818(); /* FUN_00027818 */
extern uint64_t rt_0006b6f4(); /* FUN_0006b6f4 */
extern uint64_t rt_00077708(); /* FUN_00077708 */
extern uint64_t rt_00077894(); /* FUN_00077894 */
extern uint64_t rt_0007c028(); /* FUN_0007c028 */
extern uint64_t rt_0007c1a4(); /* FUN_0007c1a4 */
extern rt16 rt_0007c1c4(); /* FUN_0007c1c4 */
extern rt16 rt_000839d8(); /* FUN_000839d8 */
extern uint64_t rt_000839f8(); /* FUN_000839f8 */
extern uint64_t rt_00083a18(); /* FUN_00083a18 */
extern uint64_t rt_0008412c(); /* FUN_0008412c */
extern uint64_t rt_00084174(); /* FUN_00084174 */
extern uint64_t rt_00084180(); /* FUN_00084180 */
extern uint64_t rt_00084220(); /* FUN_00084220 */
extern uint64_t rt_00084234(); /* FUN_00084234 */
extern rt16 rt_0008e388(); /* FUN_0008e388 */
extern uint64_t rt_0008e500(); /* FUN_0008e500 */
extern rt16 rt_0008e518(); /* FUN_0008e518 */
extern uint64_t rt_0008f6c0(); /* FUN_0008f6c0 */
extern uint64_t rt_0008f6f4(); /* FUN_0008f6f4 */
extern uint64_t rt_0008f728(); /* FUN_0008f728 */
extern uint64_t rt_0008f758(); /* FUN_0008f758 */
extern rt16 rt_0009461c(); /* FUN_0009461c */
extern uint64_t rt_0009e234(); /* FUN_0009e234 */
extern uint64_t rt_000a68c4(); /* FUN_000a68c4 */
extern uint64_t rt_000a68f4(); /* FUN_000a68f4 */
extern uint64_t rt_000a6b64(); /* FUN_000a6b64 */
extern uint64_t rt_000a6e14(); /* FUN_000a6e14 */
extern uint64_t rt_000a6f88(); /* FUN_000a6f88 */
extern rt16 rt_000b4390(); /* FUN_000b4390 */
extern rt16 rt_000b43d0(); /* FUN_000b43d0 */
extern uint64_t rt_000dbcc8(); /* FUN_000dbcc8 */
extern rt16 rt_000dbd0c(); /* FUN_000dbd0c */
extern uint64_t rt_000dbdf4(); /* FUN_000dbdf4 */
extern uint64_t rt_000dbe70(); /* FUN_000dbe70 */
extern uint64_t rt_000dbedc(); /* FUN_000dbedc */
extern uint64_t rt_000e15d8(); /* FUN_000e15d8 */
extern uint64_t rt_000e72b0(); /* FUN_000e72b0 */
extern uint64_t rt_00100c38(); /* FUN_00100c38 */
extern uint64_t rt_00100efc(); /* FUN_00100efc */
extern uint64_t rt_00149368(); /* FUN_00149368 */
extern uint64_t rt_0014ae44(); /* FUN_0014ae44 */
extern uint64_t rt_0016186c(); /* FUN_0016186c */
extern uint64_t rt_0016796c(); /* FUN_0016796c */
extern uint64_t rt_0016799c(); /* FUN_0016799c */
extern uint64_t rt_001679cc(); /* FUN_001679cc */
extern uint64_t rt_001679fc(); /* FUN_001679fc */
extern uint64_t rt_00167a2c(); /* FUN_00167a2c */
extern uint64_t rt_0019fe7c(); /* FUN_0019fe7c */
extern uint64_t rt_001a29a0(); /* FUN_001a29a0 */
extern uint64_t rt_001a8564(); /* FUN_001a8564 */
extern uint64_t rt_001afe4c(); /* FUN_001afe4c */
extern uint64_t rt_001b9040(); /* FUN_001b9040 */
extern uint64_t rt_001d30f8(); /* FUN_001d30f8 */
extern uint64_t rt_001d3fd0(); /* FUN_001d3fd0 */
extern rt16 rt_001dff60(); /* FUN_001dff60 */
extern uint64_t rt_001f1878(); /* FUN_001f1878 */
extern uint64_t rt_00200b38(); /* FUN_00200b38 */
extern uint64_t rt_00229ebc(); /* FUN_00229ebc */
extern uint64_t rt_00250904(); /* FUN_00250904 */
extern uint64_t rt_002527e8(); /* FUN_002527e8 */
extern uint64_t rt_00252818(); /* FUN_00252818 */
extern uint64_t rt_00252a64(); /* FUN_00252a64 */
extern uint64_t rt_00252b04(); /* FUN_00252b04 */
extern uint64_t rt_00252b68(); /* FUN_00252b68 */
extern uint64_t rt_00252d38(); /* FUN_00252d38 */
extern rt16 rt_00252e24(); /* FUN_00252e24 */
extern uint64_t rt_002532a8(); /* FUN_002532a8 */
extern rt16 rt_0025346c(); /* FUN_0025346c */
extern uint64_t rt_002534e4(); /* FUN_002534e4 */
extern rt16 rt_00253570(); /* FUN_00253570 */
extern uint64_t rt_00261d60(); /* FUN_00261d60 */
extern uint64_t rt_002655cc(); /* FUN_002655cc */
extern uint64_t rt_00268734(); /* FUN_00268734 */
extern uint64_t rt_0028c784(); /* FUN_0028c784 */
extern uint64_t rt_0029e8dc(); /* FUN_0029e8dc */
extern uint64_t rt_002a200c(); /* FUN_002a200c */
extern rt16 rt_002a2698(); /* FUN_002a2698 */
extern uint64_t rt_002a4b90(); /* FUN_002a4b90 */
extern rt16 rt_002a9ba8(); /* FUN_002a9ba8 */
extern uint64_t rt_002a9d64(); /* FUN_002a9d64 */
extern uint64_t rt_002ab4d4(); /* FUN_002ab4d4 */
extern uint64_t rt_002ab6a0(); /* FUN_002ab6a0 */
extern rt16 rt_002b141c(); /* FUN_002b141c */
extern uint64_t rt_002b15d0(); /* FUN_002b15d0 */
extern uint64_t rt_002b24b8(); /* FUN_002b24b8 */
extern uint64_t rt_002b3b84(); /* FUN_002b3b84 */
extern uint64_t rt_002b4120(); /* FUN_002b4120 */
extern rt16 rt_002b439c(); /* FUN_002b439c */
extern uint64_t rt_002bbcd8(); /* FUN_002bbcd8 */
extern uint64_t rt_002c6d00(); /* FUN_002c6d00 */
extern rt16 rt_002e648c(); /* FUN_002e648c */
extern uint64_t rt_00310924(); /* FUN_00310924 */
extern uint64_t rt_00310954(); /* FUN_00310954 */
extern uint64_t rt_003109b4(); /* FUN_003109b4 */
extern uint64_t rt_00310a14(); /* FUN_00310a14 */
extern uint64_t rt_00310a44(); /* FUN_00310a44 */
extern uint64_t rt_00310a74(); /* FUN_00310a74 */
extern uint64_t rt_00310ad4(); /* FUN_00310ad4 */
extern uint64_t rt_00310b08(); /* FUN_00310b08 */
extern uint64_t rt_00310cd4(); /* FUN_00310cd4 */
extern rt16 rt_00310d68(); /* FUN_00310d68 */
extern uint64_t rt_00310e08(); /* FUN_00310e08 */
extern uint64_t rt_00310f34(); /* FUN_00310f34 */
extern uint64_t rt_003192a8(); /* FUN_003192a8 */
extern uint64_t rt_003192d8(); /* FUN_003192d8 */
extern uint64_t rt_00319338(); /* FUN_00319338 */
extern uint64_t rt_0031945c(); /* FUN_0031945c */
extern uint64_t rt_003195c8(); /* FUN_003195c8 */
extern uint64_t rt_00319628(); /* FUN_00319628 */
extern uint64_t rt_00319658(); /* FUN_00319658 */
extern uint64_t rt_003196e8(); /* FUN_003196e8 */
extern uint64_t rt_00319778(); /* FUN_00319778 */
extern uint64_t rt_0031afcc(); /* FUN_0031afcc */
extern uint64_t rt_0031b110(); /* FUN_0031b110 */
extern uint64_t rt_0031b62c(); /* FUN_0031b62c */
extern uint64_t rt_0031bc40(); /* FUN_0031bc40 */
extern uint64_t rt_0031bc58(); /* FUN_0031bc58 */
extern uint64_t rt_0031bc70(); /* FUN_0031bc70 */
extern uint64_t rt_0031be18(); /* FUN_0031be18 */
extern uint64_t rt_0031be30(); /* FUN_0031be30 */
extern uint64_t rt_0031be60(); /* FUN_0031be60 */
extern uint64_t rt_0031be78(); /* FUN_0031be78 */
extern uint64_t rt_0031be90(); /* FUN_0031be90 */
extern uint64_t rt_0031bec0(); /* FUN_0031bec0 */
extern uint64_t rt_0031bef0(); /* FUN_0031bef0 */
extern uint64_t rt_0031bf20(); /* FUN_0031bf20 */
extern uint64_t rt_0031bf50(); /* FUN_0031bf50 */
extern uint64_t rt_0031bf80(); /* FUN_0031bf80 */
extern uint64_t rt_0031bfb0(); /* FUN_0031bfb0 */
extern uint64_t rt_0031bfe0(); /* FUN_0031bfe0 */
extern uint64_t rt_0031c070(); /* FUN_0031c070 */
extern uint64_t rt_0031c0a0(); /* FUN_0031c0a0 */
extern uint64_t rt_0031c0d0(); /* FUN_0031c0d0 */
extern uint64_t rt_0031c100(); /* FUN_0031c100 */
extern uint64_t rt_0031c130(); /* FUN_0031c130 */
extern uint64_t rt_0031c160(); /* FUN_0031c160 */
extern uint64_t rt_0031c190(); /* FUN_0031c190 */
extern uint64_t rt_0031c1c0(); /* FUN_0031c1c0 */
extern uint64_t rt_0031c1f0(); /* FUN_0031c1f0 */
extern uint64_t rt_0031c220(); /* FUN_0031c220 */
extern uint64_t rt_0031c250(); /* FUN_0031c250 */
extern uint64_t rt_0031c280(); /* FUN_0031c280 */
extern uint64_t rt_0031c2b0(); /* FUN_0031c2b0 */
extern uint64_t rt_0031c2e0(); /* FUN_0031c2e0 */
extern uint64_t rt_0031c310(); /* FUN_0031c310 */
extern uint64_t rt_0031c340(); /* FUN_0031c340 */
extern uint64_t rt_0031c370(); /* FUN_0031c370 */
extern uint64_t rt_0031c3a0(); /* FUN_0031c3a0 */
extern uint64_t rt_0031c3d0(); /* FUN_0031c3d0 */
extern uint64_t rt_0031c400(); /* FUN_0031c400 */
extern uint64_t rt_0031c430(); /* FUN_0031c430 */
extern uint64_t rt_0031c460(); /* FUN_0031c460 */
extern uint64_t rt_0031c490(); /* FUN_0031c490 */
extern uint64_t rt_0031c4c0(); /* FUN_0031c4c0 */
extern uint64_t rt_0031c4f0(); /* FUN_0031c4f0 */
extern uint64_t rt_0031c520(); /* FUN_0031c520 */
extern uint64_t rt_0031c550(); /* FUN_0031c550 */
extern uint64_t rt_0031c580(); /* FUN_0031c580 */
extern uint64_t rt_0031c5b0(); /* FUN_0031c5b0 */
extern uint64_t rt_0031c5e0(); /* FUN_0031c5e0 */
extern uint64_t rt_0031c610(); /* FUN_0031c610 */
extern uint64_t rt_0031c640(); /* FUN_0031c640 */
extern uint64_t rt_0031c670(); /* FUN_0031c670 */
extern uint64_t rt_0031c788(); /* FUN_0031c788 */
extern uint64_t rt_0031d6d8(); /* FUN_0031d6d8 */
extern uint64_t rt_00347d60(); /* FUN_00347d60 */
extern uint64_t rt_00347e28(); /* FUN_00347e28 */
extern uint64_t rt_00347fb4(); /* FUN_00347fb4 */
extern uint64_t rt_003480e4(); /* FUN_003480e4 */
extern uint64_t rt_003486b8(); /* FUN_003486b8 */
extern uint64_t rt_00348898(); /* FUN_00348898 */
extern uint64_t rt_003488bc(); /* FUN_003488bc */
extern uint64_t rt_003489c0(); /* FUN_003489c0 */
extern uint64_t rt_003489dc(); /* FUN_003489dc */
extern uint64_t rt_00348a34(); /* FUN_00348a34 */
extern uint64_t rt_00348a9c(); /* FUN_00348a9c */
extern uint64_t rt_00348abc(); /* FUN_00348abc */
extern uint64_t rt_00348b5c(); /* FUN_00348b5c */
extern rt16 rt_00348b94(); /* FUN_00348b94 */
extern uint64_t rt_00348bbc(); /* FUN_00348bbc */
extern uint64_t rt_00348bd8(); /* FUN_00348bd8 */
extern uint64_t rt_00348c48(); /* FUN_00348c48 */
extern uint64_t rt_00348c84(); /* FUN_00348c84 */
extern uint64_t rt_00348cd0(); /* FUN_00348cd0 */
extern uint64_t rt_00348ce8(); /* FUN_00348ce8 */
extern uint64_t rt_00348d4c(); /* FUN_00348d4c */
extern uint64_t rt_00348d64(); /* FUN_00348d64 */
extern uint64_t rt_00348d7c(); /* FUN_00348d7c */
extern uint64_t rt_00348e00(); /* FUN_00348e00 */
extern uint64_t rt_00348e18(); /* FUN_00348e18 */
extern uint64_t rt_00348e60(); /* FUN_00348e60 */
extern uint64_t rt_00348e78(); /* FUN_00348e78 */
extern uint64_t rt_00348f14(); /* FUN_00348f14 */
extern uint64_t rt_00348f38(); /* FUN_00348f38 */
extern uint64_t rt_00348fb4(); /* FUN_00348fb4 */
extern uint64_t rt_00348fd8(); /* FUN_00348fd8 */
extern uint64_t rt_00349068(); /* FUN_00349068 */
extern uint64_t rt_00349080(); /* FUN_00349080 */
extern uint64_t rt_003490b8(); /* FUN_003490b8 */
extern uint64_t rt_003490d0(); /* FUN_003490d0 */
extern uint64_t rt_0034911c(); /* FUN_0034911c */
extern uint64_t rt_0034926c(); /* FUN_0034926c */
extern uint64_t rt_003492cc(); /* FUN_003492cc */
extern uint64_t rt_00349370(); /* FUN_00349370 */
extern uint64_t rt_003493c4(); /* FUN_003493c4 */
extern uint64_t rt_003493ec(); /* FUN_003493ec */
extern uint64_t rt_0034947c(); /* FUN_0034947c */
extern uint64_t rt_003494b4(); /* FUN_003494b4 */
extern uint64_t rt_003494e8(); /* FUN_003494e8 */
extern uint64_t rt_003494fc(); /* FUN_003494fc */
extern uint64_t rt_00349530(); /* FUN_00349530 */
extern uint64_t rt_00349618(); /* FUN_00349618 */
extern uint64_t rt_00349630(); /* FUN_00349630 */
extern uint64_t rt_00349684(); /* FUN_00349684 */
extern uint64_t rt_003496e8(); /* FUN_003496e8 */
extern uint64_t rt_00349720(); /* FUN_00349720 */
extern uint64_t rt_00349734(); /* FUN_00349734 */
extern uint64_t rt_00349748(); /* FUN_00349748 */
extern uint64_t rt_0034975c(); /* FUN_0034975c */
extern rt16 rt_003497a0(); /* FUN_003497a0 */
extern uint64_t rt_003497b4(); /* FUN_003497b4 */
extern uint64_t rt_00349830(); /* FUN_00349830 */
extern uint64_t rt_00349944(); /* FUN_00349944 */
extern uint64_t rt_003499c8(); /* FUN_003499c8 */
extern uint64_t rt_003499f0(); /* FUN_003499f0 */
extern uint64_t rt_00349a18(); /* FUN_00349a18 */
extern uint64_t rt_00349a68(); /* FUN_00349a68 */
extern uint64_t rt_00349abc(); /* FUN_00349abc */
extern rt16 rt_00349b14(); /* FUN_00349b14 */
extern uint64_t rt_00349b3c(); /* FUN_00349b3c */
extern uint64_t rt_00349b64(); /* FUN_00349b64 */
extern uint64_t rt_00349c44(); /* FUN_00349c44 */
extern uint64_t rt_00349c70(); /* FUN_00349c70 */
extern uint64_t rt_00349d80(); /* FUN_00349d80 */
extern uint64_t rt_00349dfc(); /* FUN_00349dfc */
extern uint64_t rt_00349e10(); /* FUN_00349e10 */
extern rt16 rt_00349ef4(); /* FUN_00349ef4 */
extern uint64_t rt_00349f3c(); /* FUN_00349f3c */
extern uint64_t rt_00349f5c(); /* FUN_00349f5c */
extern uint64_t rt_00349f74(); /* FUN_00349f74 */
extern uint64_t rt_00349f8c(); /* FUN_00349f8c */
extern uint64_t rt_00349fe0(); /* FUN_00349fe0 */
extern uint64_t rt_0034a034(); /* FUN_0034a034 */
extern uint64_t rt_0034a07c(); /* FUN_0034a07c */
extern uint64_t rt_0034a1b0(); /* FUN_0034a1b0 */
extern uint64_t rt_0034a1c8(); /* FUN_0034a1c8 */
extern uint64_t rt_0034a1f8(); /* FUN_0034a1f8 */
extern uint64_t rt_0034a2ac(); /* FUN_0034a2ac */
extern uint64_t rt_0034a2c0(); /* FUN_0034a2c0 */
extern uint64_t rt_0034a2f8(); /* FUN_0034a2f8 */
extern uint64_t rt_0034a30c(); /* FUN_0034a30c */
extern uint64_t rt_0034a354(); /* FUN_0034a354 */
extern uint64_t rt_0034a400(); /* FUN_0034a400 */
extern uint64_t rt_0034a428(); /* FUN_0034a428 */
extern uint64_t rt_0034a450(); /* FUN_0034a450 */
extern uint64_t rt_0034a464(); /* FUN_0034a464 */
extern uint64_t rt_0034a4e0(); /* FUN_0034a4e0 */
extern uint64_t rt_0034a4f8(); /* FUN_0034a4f8 */
extern uint64_t rt_0034a588(); /* FUN_0034a588 */
extern uint64_t rt_0034a62c(); /* FUN_0034a62c */
extern uint64_t rt_0034a688(); /* FUN_0034a688 */
extern uint64_t rt_0034a74c(); /* FUN_0034a74c */
extern uint64_t rt_0034a760(); /* FUN_0034a760 */
extern uint64_t rt_0034a774(); /* FUN_0034a774 */
extern uint64_t rt_0034a7c0(); /* FUN_0034a7c0 */
extern uint64_t rt_0034a944(); /* FUN_0034a944 */
extern uint64_t rt_0034a9ac(); /* FUN_0034a9ac */
extern uint64_t rt_0034a9c0(); /* FUN_0034a9c0 */
extern uint64_t rt_0034a9d4(); /* FUN_0034a9d4 */
extern uint64_t rt_0034a9e8(); /* FUN_0034a9e8 */
extern uint64_t rt_0034aa14(); /* FUN_0034aa14 */
extern uint64_t rt_0034aa28(); /* FUN_0034aa28 */
extern uint64_t rt_0034aa54(); /* FUN_0034aa54 */
extern uint64_t rt_0034aa9c(); /* FUN_0034aa9c */
extern uint64_t rt_0034aab0(); /* FUN_0034aab0 */
extern uint64_t rt_0034aac4(); /* FUN_0034aac4 */
extern uint64_t rt_0034aadc(); /* FUN_0034aadc */
extern uint64_t rt_0034ab10(); /* FUN_0034ab10 */
extern uint64_t rt_0034ab20(); /* FUN_0034ab20 */
extern uint64_t rt_0034abd8(); /* FUN_0034abd8 */
extern uint64_t rt_0034abec(); /* FUN_0034abec */
extern uint64_t rt_0034ac14(); /* FUN_0034ac14 */
extern uint64_t rt_0034ac50(); /* FUN_0034ac50 */
extern uint64_t rt_0034ac8c(); /* FUN_0034ac8c */
extern uint64_t rt_0034acf0(); /* FUN_0034acf0 */
extern uint64_t rt_0034ad00(); /* FUN_0034ad00 */
extern uint64_t rt_0034ad10(); /* FUN_0034ad10 */
extern uint64_t rt_0034ae80(); /* FUN_0034ae80 */
extern uint64_t rt_0034aea8(); /* FUN_0034aea8 */
extern uint64_t rt_0034aee4(); /* FUN_0034aee4 */
extern uint64_t rt_0034af04(); /* FUN_0034af04 */
extern uint64_t rt_0034af20(); /* FUN_0034af20 */
extern uint64_t rt_0034afc0(); /* FUN_0034afc0 */
extern uint64_t rt_0034b05c(); /* FUN_0034b05c */
extern uint64_t rt_0034b07c(); /* FUN_0034b07c */
extern uint64_t rt_0034b0c4(); /* FUN_0034b0c4 */
extern uint64_t rt_0034b0d4(); /* FUN_0034b0d4 */
extern uint64_t rt_0034b100(); /* FUN_0034b100 */
extern uint64_t rt_0034b250(); /* FUN_0034b250 */
extern uint64_t rt_0034b278(); /* FUN_0034b278 */
extern uint64_t rt_0034b2c8(); /* FUN_0034b2c8 */
extern uint64_t rt_0034b2f8(); /* FUN_0034b2f8 */
extern uint64_t rt_0034b318(); /* FUN_0034b318 */
extern uint64_t rt_0034b348(); /* FUN_0034b348 */
extern uint64_t rt_0034b358(); /* FUN_0034b358 */
extern uint64_t rt_0034b3c8(); /* FUN_0034b3c8 */
extern uint64_t rt_0034b3d8(); /* FUN_0034b3d8 */
extern uint64_t rt_0034b3e8(); /* FUN_0034b3e8 */
extern uint64_t rt_0034b460(); /* FUN_0034b460 */
extern uint64_t rt_0034b4a0(); /* FUN_0034b4a0 */
extern uint64_t rt_0034b4c0(); /* FUN_0034b4c0 */
extern uint64_t rt_0034b4d0(); /* FUN_0034b4d0 */
extern uint64_t rt_0034b4ec(); /* FUN_0034b4ec */
extern uint64_t rt_0034b508(); /* FUN_0034b508 */
extern uint64_t rt_0034b640(); /* FUN_0034b640 */
extern uint64_t rt_0034b668(); /* FUN_0034b668 */
extern uint64_t rt_0034b67c(); /* FUN_0034b67c */
extern uint64_t rt_0034b690(); /* FUN_0034b690 */
extern uint64_t rt_0034b708(); /* FUN_0034b708 */
extern uint64_t rt_0034b758(); /* FUN_0034b758 */
extern uint64_t rt_0034b768(); /* FUN_0034b768 */
extern uint64_t rt_0034b778(); /* FUN_0034b778 */
extern uint64_t rt_0034b7b8(); /* FUN_0034b7b8 */
extern uint64_t rt_0034b804(); /* FUN_0034b804 */
extern uint64_t rt_0034b814(); /* FUN_0034b814 */
extern uint64_t rt_0034b87c(); /* FUN_0034b87c */
extern uint64_t rt_0034b88c(); /* FUN_0034b88c */
extern uint64_t rt_0034b8bc(); /* FUN_0034b8bc */
extern uint64_t rt_0034b8cc(); /* FUN_0034b8cc */
extern uint64_t rt_0034b8ec(); /* FUN_0034b8ec */
extern uint64_t rt_0034b9e8(); /* FUN_0034b9e8 */
extern uint64_t rt_0034b9f8(); /* FUN_0034b9f8 */
extern uint64_t rt_0034ba08(); /* FUN_0034ba08 */
extern uint64_t rt_0034ba18(); /* FUN_0034ba18 */
extern uint64_t rt_0034ba28(); /* FUN_0034ba28 */
extern uint64_t rt_0034ba48(); /* FUN_0034ba48 */
extern uint64_t rt_0034ba78(); /* FUN_0034ba78 */
extern uint64_t rt_0034bb94(); /* FUN_0034bb94 */
extern uint64_t rt_0034bc04(); /* FUN_0034bc04 */
extern uint64_t rt_0034bc58(); /* FUN_0034bc58 */
extern uint64_t rt_0034bc6c(); /* FUN_0034bc6c */
extern uint64_t rt_0034bc80(); /* FUN_0034bc80 */
extern uint64_t rt_0034bcf0(); /* FUN_0034bcf0 */
extern uint64_t rt_0034bd6c(); /* FUN_0034bd6c */
extern uint64_t rt_0034bdcc(); /* FUN_0034bdcc */
extern uint64_t rt_0034bdec(); /* FUN_0034bdec */
extern uint64_t rt_0034be0c(); /* FUN_0034be0c */
extern uint64_t rt_0034be54(); /* FUN_0034be54 */
extern uint64_t rt_0034bec4(); /* FUN_0034bec4 */
extern uint64_t rt_0034bed4(); /* FUN_0034bed4 */
extern uint64_t rt_0034beec(); /* FUN_0034beec */
extern uint64_t rt_0034befc(); /* FUN_0034befc */
extern uint64_t rt_0034bf2c(); /* FUN_0034bf2c */
extern uint64_t rt_0034bf48(); /* FUN_0034bf48 */
extern uint64_t rt_0034bf84(); /* FUN_0034bf84 */
extern uint64_t rt_0034bf94(); /* FUN_0034bf94 */
extern uint64_t rt_0034bfa4(); /* FUN_0034bfa4 */
extern uint64_t rt_0034bfe0(); /* FUN_0034bfe0 */
extern uint64_t rt_0034c054(); /* FUN_0034c054 */
extern uint64_t rt_0034c074(); /* FUN_0034c074 */
extern uint64_t rt_0034c084(); /* FUN_0034c084 */
extern uint64_t rt_0034c0b4(); /* FUN_0034c0b4 */
extern uint64_t rt_0034c0d0(); /* FUN_0034c0d0 */
extern uint64_t rt_0034c0ec(); /* FUN_0034c0ec */
extern uint64_t rt_0034c108(); /* FUN_0034c108 */
extern uint64_t rt_0034c158(); /* FUN_0034c158 */
extern uint64_t rt_0034c220(); /* FUN_0034c220 */
extern uint64_t rt_0034c234(); /* FUN_0034c234 */
extern uint64_t rt_0034c290(); /* FUN_0034c290 */
extern uint64_t rt_0034c2a4(); /* FUN_0034c2a4 */
extern uint64_t rt_0034c2b4(); /* FUN_0034c2b4 */
extern uint64_t rt_0034c2c8(); /* FUN_0034c2c8 */
extern uint64_t rt_0034c2e8(); /* FUN_0034c2e8 */
extern uint64_t rt_0034c2f8(); /* FUN_0034c2f8 */
extern uint64_t rt_0034c330(); /* FUN_0034c330 */
extern uint64_t rt_0034c344(); /* FUN_0034c344 */
extern uint64_t rt_0034c368(); /* FUN_0034c368 */
extern uint64_t rt_0034c384(); /* FUN_0034c384 */
extern uint64_t rt_0034c3b4(); /* FUN_0034c3b4 */
extern uint64_t rt_0034c3c4(); /* FUN_0034c3c4 */
extern uint64_t rt_0034c3d4(); /* FUN_0034c3d4 */
extern uint64_t rt_0034c3f4(); /* FUN_0034c3f4 */
extern uint64_t rt_0034c414(); /* FUN_0034c414 */
extern uint64_t rt_0034c444(); /* FUN_0034c444 */
extern uint64_t rt_0034c454(); /* FUN_0034c454 */
extern uint64_t rt_0034c464(); /* FUN_0034c464 */
extern uint64_t rt_0034c480(); /* FUN_0034c480 */
extern uint64_t rt_0034c4bc(); /* FUN_0034c4bc */
extern uint64_t rt_0034c4fc(); /* FUN_0034c4fc */
extern uint64_t rt_0034c5ac(); /* FUN_0034c5ac */
extern uint64_t rt_0034c5dc(); /* FUN_0034c5dc */
extern uint64_t rt_0034c5ec(); /* FUN_0034c5ec */
extern uint64_t rt_0034c60c(); /* FUN_0034c60c */
extern uint64_t rt_0034c61c(); /* FUN_0034c61c */
extern uint64_t rt_0034c674(); /* FUN_0034c674 */
extern uint64_t rt_0034c694(); /* FUN_0034c694 */
extern uint64_t rt_0034c6a4(); /* FUN_0034c6a4 */
extern uint64_t rt_0034c6c4(); /* FUN_0034c6c4 */
extern uint64_t rt_0034c754(); /* FUN_0034c754 */
extern uint64_t rt_0034c7d4(); /* FUN_0034c7d4 */
extern uint64_t rt_0034c7f0(); /* FUN_0034c7f0 */
extern uint64_t rt_0034c870(); /* FUN_0034c870 */
extern uint64_t rt_0034c888(); /* FUN_0034c888 */
extern uint64_t rt_0034c8a0(); /* FUN_0034c8a0 */
extern uint64_t rt_0034c8b8(); /* FUN_0034c8b8 */
extern uint64_t rt_0034c8c8(); /* FUN_0034c8c8 */
extern uint64_t rt_0034c920(); /* FUN_0034c920 */
extern uint64_t rt_0034c9b8(); /* FUN_0034c9b8 */
extern uint64_t rt_0034c9f8(); /* FUN_0034c9f8 */
extern uint64_t rt_0034cae8(); /* FUN_0034cae8 */
extern uint64_t rt_0034cbc4(); /* FUN_0034cbc4 */
extern uint64_t rt_0034cd04(); /* FUN_0034cd04 */
extern uint64_t rt_0034cd40(); /* FUN_0034cd40 */
extern uint64_t rt_0034cd54(); /* FUN_0034cd54 */
extern uint64_t rt_0034cd7c(); /* FUN_0034cd7c */
extern uint64_t rt_0034cdc8(); /* FUN_0034cdc8 */
extern uint64_t rt_0034cdd8(); /* FUN_0034cdd8 */
extern uint64_t rt_0034cde8(); /* FUN_0034cde8 */
extern uint64_t rt_0034ce38(); /* FUN_0034ce38 */
extern uint64_t rt_0034ce68(); /* FUN_0034ce68 */
extern uint64_t rt_0034cea8(); /* FUN_0034cea8 */
extern uint64_t rt_0034cee8(); /* FUN_0034cee8 */
extern uint64_t rt_0034cf64(); /* FUN_0034cf64 */
extern uint64_t rt_0034cf74(); /* FUN_0034cf74 */
extern uint64_t rt_0034cf84(); /* FUN_0034cf84 */
extern uint64_t rt_0034cfa4(); /* FUN_0034cfa4 */
extern uint64_t rt_0034cfd4(); /* FUN_0034cfd4 */
extern uint64_t rt_0034cff4(); /* FUN_0034cff4 */
extern uint64_t rt_0034d054(); /* FUN_0034d054 */
extern uint64_t rt_0034d140(); /* FUN_0034d140 */
extern uint64_t rt_0034d170(); /* FUN_0034d170 */
extern uint64_t rt_0034d180(); /* FUN_0034d180 */
extern uint64_t rt_0034d190(); /* FUN_0034d190 */
extern rt16 rt_0034d1d0(); /* FUN_0034d1d0 */
extern uint64_t rt_0034d1fc(); /* FUN_0034d1fc */
extern uint64_t rt_0034d234(); /* FUN_0034d234 */
extern uint64_t rt_0034d244(); /* FUN_0034d244 */
extern uint64_t rt_0034d254(); /* FUN_0034d254 */
extern uint64_t rt_0034d264(); /* FUN_0034d264 */
extern uint64_t rt_0034d294(); /* FUN_0034d294 */
extern uint64_t rt_0034d2a4(); /* FUN_0034d2a4 */
extern uint64_t rt_0034d2b4(); /* FUN_0034d2b4 */
extern uint64_t rt_0034d2d4(); /* FUN_0034d2d4 */
extern rt16 rt_0034d2f4(); /* FUN_0034d2f4 */
extern uint64_t rt_0034d324(); /* FUN_0034d324 */
extern uint64_t rt_0034d344(); /* FUN_0034d344 */
extern uint64_t rt_0034d354(); /* FUN_0034d354 */
extern uint64_t rt_0034d364(); /* FUN_0034d364 */
extern rt16 rt_0034d374(); /* FUN_0034d374 */
extern uint64_t rt_0034d3a4(); /* FUN_0034d3a4 */
extern uint64_t rt_0034d3e4(); /* FUN_0034d3e4 */
extern uint64_t rt_0034d404(); /* FUN_0034d404 */
extern uint64_t rt_0034d414(); /* FUN_0034d414 */
extern uint64_t rt_0034d444(); /* FUN_0034d444 */
extern uint64_t rt_0034d464(); /* FUN_0034d464 */
extern uint64_t rt_0034d4b8(); /* FUN_0034d4b8 */
extern uint64_t rt_0034d504(); /* FUN_0034d504 */
extern uint64_t rt_0034d520(); /* FUN_0034d520 */
extern uint64_t rt_0034d53c(); /* FUN_0034d53c */
extern uint64_t rt_0034d558(); /* FUN_0034d558 */
extern uint64_t rt_0034d598(); /* FUN_0034d598 */
extern uint64_t rt_0034d778(); /* FUN_0034d778 */
extern rt16 rt_0034d810(); /* FUN_0034d810 */
extern uint64_t rt_0034d820(); /* FUN_0034d820 */
extern uint64_t rt_0034d844(); /* FUN_0034d844 */
extern uint64_t rt_0034d868(); /* FUN_0034d868 */
extern uint64_t rt_0034d8f4(); /* FUN_0034d8f4 */
extern uint64_t rt_0034d934(); /* FUN_0034d934 */
extern uint64_t rt_0034d970(); /* FUN_0034d970 */
extern uint64_t rt_0034d9cc(); /* FUN_0034d9cc */
extern uint64_t rt_0034da88(); /* FUN_0034da88 */
extern uint64_t rt_0034dad8(); /* FUN_0034dad8 */
extern uint64_t rt_0034daf8(); /* FUN_0034daf8 */
extern uint64_t rt_0034db08(); /* FUN_0034db08 */
extern uint64_t rt_0034db18(); /* FUN_0034db18 */
extern uint64_t rt_0034db78(); /* FUN_0034db78 */
extern uint64_t rt_0034dbb8(); /* FUN_0034dbb8 */
extern uint64_t rt_0034dbe8(); /* FUN_0034dbe8 */
extern uint64_t rt_0034dc20(); /* FUN_0034dc20 */
extern uint64_t rt_0034dc54(); /* FUN_0034dc54 */
extern uint64_t rt_0034dc9c(); /* FUN_0034dc9c */
extern uint64_t rt_0034de24(); /* FUN_0034de24 */
extern uint64_t rt_0034de44(); /* FUN_0034de44 */
extern uint64_t rt_0034df34(); /* FUN_0034df34 */
extern uint64_t rt_0034df44(); /* FUN_0034df44 */
extern uint64_t rt_0034df74(); /* FUN_0034df74 */
extern uint64_t rt_0034df84(); /* FUN_0034df84 */
extern uint64_t rt_0034dfa4(); /* FUN_0034dfa4 */
extern uint64_t rt_0034e014(); /* FUN_0034e014 */
extern uint64_t rt_0034e034(); /* FUN_0034e034 */
extern uint64_t rt_0034e054(); /* FUN_0034e054 */
extern uint64_t rt_0034e064(); /* FUN_0034e064 */
extern uint64_t rt_0034e084(); /* FUN_0034e084 */
extern uint64_t rt_0034e094(); /* FUN_0034e094 */
extern uint64_t rt_0034e104(); /* FUN_0034e104 */
extern uint64_t rt_0034e130(); /* FUN_0034e130 */
extern uint64_t rt_0034e140(); /* FUN_0034e140 */
extern uint64_t rt_0034e15c(); /* FUN_0034e15c */
extern uint64_t rt_0034e1b0(); /* FUN_0034e1b0 */
extern uint64_t rt_0034e1d0(); /* FUN_0034e1d0 */
extern uint64_t rt_0034e2d0(); /* FUN_0034e2d0 */
extern uint64_t rt_0034e2e4(); /* FUN_0034e2e4 */
extern uint64_t rt_0034e33c(); /* FUN_0034e33c */
extern uint64_t rt_0034e3ac(); /* FUN_0034e3ac */
extern uint64_t rt_0034e444(); /* FUN_0034e444 */
extern uint64_t rt_0034e464(); /* FUN_0034e464 */
extern uint64_t rt_0034e474(); /* FUN_0034e474 */
extern uint64_t rt_0034e494(); /* FUN_0034e494 */
extern uint64_t rt_0034e4dc(); /* FUN_0034e4dc */
extern uint64_t rt_0034e50c(); /* FUN_0034e50c */
extern uint64_t rt_0034e51c(); /* FUN_0034e51c */
extern uint64_t rt_0034e52c(); /* FUN_0034e52c */
extern uint64_t rt_0034e54c(); /* FUN_0034e54c */
extern uint64_t rt_0034e57c(); /* FUN_0034e57c */
extern uint64_t rt_0034e5cc(); /* FUN_0034e5cc */
extern uint64_t rt_0034e62c(); /* FUN_0034e62c */
extern uint64_t rt_0034e64c(); /* FUN_0034e64c */
extern uint64_t rt_0034e68c(); /* FUN_0034e68c */
extern uint64_t rt_0034e6cc(); /* FUN_0034e6cc */
extern uint64_t rt_0034e6dc(); /* FUN_0034e6dc */
extern uint64_t rt_0034e6ec(); /* FUN_0034e6ec */
extern uint64_t rt_0034e70c(); /* FUN_0034e70c */
extern uint64_t rt_0034e71c(); /* FUN_0034e71c */
extern uint64_t rt_0034e72c(); /* FUN_0034e72c */
extern uint64_t rt_0034e73c(); /* FUN_0034e73c */
extern uint64_t rt_0034e74c(); /* FUN_0034e74c */
extern uint64_t rt_0034e784(); /* FUN_0034e784 */
extern rt16 rt_0034e8a4(); /* FUN_0034e8a4 */
extern uint64_t rt_0034e94c(); /* FUN_0034e94c */
extern uint64_t rt_0034e990(); /* FUN_0034e990 */
extern uint64_t rt_0034eaac(); /* FUN_0034eaac */
extern uint64_t rt_0034eae8(); /* FUN_0034eae8 */
extern uint64_t rt_0034eafc(); /* FUN_0034eafc */
extern uint64_t rt_0034eb64(); /* FUN_0034eb64 */
extern uint64_t rt_0034ec1c(); /* FUN_0034ec1c */
extern uint64_t rt_0034ece8(); /* FUN_0034ece8 */
extern uint64_t rt_0034ed08(); /* FUN_0034ed08 */
extern uint64_t rt_0034ed88(); /* FUN_0034ed88 */
extern uint64_t rt_0034eda8(); /* FUN_0034eda8 */
extern uint64_t rt_0034edc8(); /* FUN_0034edc8 */
extern uint64_t rt_0034ede8(); /* FUN_0034ede8 */
extern uint64_t rt_0034ee08(); /* FUN_0034ee08 */
extern uint64_t rt_0034ee18(); /* FUN_0034ee18 */
extern uint64_t rt_0034ee58(); /* FUN_0034ee58 */
extern uint64_t rt_0034ee68(); /* FUN_0034ee68 */
extern uint64_t rt_0034ee98(); /* FUN_0034ee98 */
extern uint64_t rt_0034eeb8(); /* FUN_0034eeb8 */
extern uint64_t rt_0034eee8(); /* FUN_0034eee8 */
extern uint64_t rt_0034ef08(); /* FUN_0034ef08 */
extern uint64_t rt_0034ef18(); /* FUN_0034ef18 */
extern uint64_t rt_0034ef28(); /* FUN_0034ef28 */
extern uint64_t rt_0034efa8(); /* FUN_0034efa8 */
extern uint64_t rt_0034efb8(); /* FUN_0034efb8 */
extern uint64_t rt_0034efdc(); /* FUN_0034efdc */
extern uint64_t rt_0034eff8(); /* FUN_0034eff8 */
extern uint64_t rt_0034f1e0(); /* FUN_0034f1e0 */
extern uint64_t rt_0034f1fc(); /* FUN_0034f1fc */
extern uint64_t rt_0034f294(); /* FUN_0034f294 */
extern uint64_t rt_0034f2b4(); /* FUN_0034f2b4 */
extern uint64_t rt_0034f374(); /* FUN_0034f374 */
extern uint64_t rt_0034f394(); /* FUN_0034f394 */
extern uint64_t rt_0034f3a4(); /* FUN_0034f3a4 */
extern uint64_t rt_0034f424(); /* FUN_0034f424 */
extern uint64_t rt_0034f474(); /* FUN_0034f474 */
extern uint64_t rt_0034f494(); /* FUN_0034f494 */
extern uint64_t rt_0034f4a4(); /* FUN_0034f4a4 */
extern rt16 rt_0034f4b4(); /* FUN_0034f4b4 */
extern uint64_t rt_0034f4d4(); /* FUN_0034f4d4 */
extern uint64_t rt_0034f4f4(); /* FUN_0034f4f4 */
extern rt16 rt_0034f514(); /* FUN_0034f514 */
extern uint64_t rt_0034f534(); /* FUN_0034f534 */
extern uint64_t rt_0034f554(); /* FUN_0034f554 */
extern uint64_t rt_0034f564(); /* FUN_0034f564 */
extern uint64_t rt_0034f5d4(); /* FUN_0034f5d4 */
extern uint64_t rt_0034f604(); /* FUN_0034f604 */
extern uint64_t rt_0034f614(); /* FUN_0034f614 */
extern uint64_t rt_0034f644(); /* FUN_0034f644 */
extern uint64_t rt_0034f654(); /* FUN_0034f654 */
extern uint64_t rt_0034f664(); /* FUN_0034f664 */
extern uint64_t rt_0034f754(); /* FUN_0034f754 */
extern uint64_t rt_0034f778(); /* FUN_0034f778 */
extern uint64_t rt_0034f788(); /* FUN_0034f788 */
extern uint64_t rt_0034f838(); /* FUN_0034f838 */
extern uint64_t rt_0034f84c(); /* FUN_0034f84c */
extern uint64_t rt_0034f9d8(); /* FUN_0034f9d8 */
extern uint64_t rt_0034f9ec(); /* FUN_0034f9ec */
extern uint64_t rt_0034facc(); /* FUN_0034facc */
extern uint64_t rt_0034fb3c(); /* FUN_0034fb3c */
extern uint64_t rt_0034fe08(); /* FUN_0034fe08 */
extern uint64_t rt_0034fe38(); /* FUN_0034fe38 */
extern uint64_t rt_0034fe48(); /* FUN_0034fe48 */
extern uint64_t rt_0034fe64(); /* FUN_0034fe64 */
extern uint64_t rt_0034fe80(); /* FUN_0034fe80 */
extern uint64_t rt_00350048(); /* FUN_00350048 */
extern uint64_t rt_00350068(); /* FUN_00350068 */
extern uint64_t rt_00350088(); /* FUN_00350088 */
extern uint64_t rt_003500f4(); /* FUN_003500f4 */
extern uint64_t rt_00350104(); /* FUN_00350104 */
extern uint64_t rt_0035012c(); /* FUN_0035012c */
extern uint64_t rt_00350164(); /* FUN_00350164 */
extern uint64_t rt_00350210(); /* FUN_00350210 */
extern uint64_t rt_003502d8(); /* FUN_003502d8 */
extern uint64_t rt_003502f8(); /* FUN_003502f8 */
extern uint64_t rt_0035034c(); /* FUN_0035034c */
extern uint64_t rt_0035035c(); /* FUN_0035035c */
extern uint64_t rt_003503a0(); /* FUN_003503a0 */
extern uint64_t rt_003503ec(); /* FUN_003503ec */
extern uint64_t rt_00350404(); /* FUN_00350404 */
extern uint64_t rt_00350410(); /* FUN_00350410 */
extern uint64_t rt_0035041c(); /* FUN_0035041c */
extern uint64_t rt_00350428(); /* FUN_00350428 */
extern uint64_t rt_00350434(); /* FUN_00350434 */
extern rt16 rt_00350440(); /* FUN_00350440 */
extern uint64_t rt_0035044c(); /* FUN_0035044c */
extern uint64_t rt_00350464(); /* FUN_00350464 */
extern uint64_t rt_00350470(); /* FUN_00350470 */
extern uint64_t rt_00350488(); /* FUN_00350488 */
extern rt16 rt_00350494(); /* FUN_00350494 */
extern uint64_t rt_003504a0(); /* FUN_003504a0 */
extern rt16 rt_003504ac(); /* FUN_003504ac */
extern uint64_t rt_003504c4(); /* FUN_003504c4 */
extern uint64_t rt_003504d0(); /* FUN_003504d0 */
extern uint64_t rt_003504e8(); /* FUN_003504e8 */
extern uint64_t rt_003504f4(); /* FUN_003504f4 */
extern uint64_t rt_00350500(); /* FUN_00350500 */
extern rt16 rt_0035050c(); /* FUN_0035050c */
extern uint64_t rt_00350518(); /* FUN_00350518 */
extern uint64_t rt_00350524(); /* FUN_00350524 */
extern uint64_t rt_00350530(); /* FUN_00350530 */
extern uint64_t rt_0035053c(); /* FUN_0035053c */
extern uint64_t rt_00350554(); /* FUN_00350554 */
extern uint64_t rt_00350560(); /* FUN_00350560 */
extern uint64_t rt_0035056c(); /* FUN_0035056c */
extern uint64_t rt_00350578(); /* FUN_00350578 */
extern uint64_t rt_003505c4(); /* FUN_003505c4 */
extern uint64_t rt_003505d0(); /* FUN_003505d0 */
extern uint64_t rt_003505dc(); /* FUN_003505dc */
extern rt16 rt_003505e8(); /* FUN_003505e8 */
extern uint64_t rt_003505f4(); /* FUN_003505f4 */
extern uint64_t rt_00350600(); /* FUN_00350600 */
extern uint64_t rt_0035060c(); /* FUN_0035060c */
extern uint64_t rt_00350618(); /* FUN_00350618 */
extern uint64_t rt_00350624(); /* FUN_00350624 */
extern rt16 rt_00350630(); /* FUN_00350630 */
extern uint64_t rt_0035063c(); /* FUN_0035063c */
extern uint64_t rt_00350648(); /* FUN_00350648 */
extern uint64_t rt_00350654(); /* FUN_00350654 */
extern uint64_t rt_0035066c(); /* FUN_0035066c */
extern uint64_t rt_003506b0(); /* FUN_003506b0 */
extern uint64_t rt_003506cc(); /* FUN_003506cc */
extern uint64_t rt_003506e8(); /* FUN_003506e8 */
extern uint64_t rt_00350704(); /* FUN_00350704 */
extern uint64_t rt_00350720(); /* FUN_00350720 */
extern uint64_t rt_0035072c(); /* FUN_0035072c */
extern rt16 rt_00350738(); /* FUN_00350738 */
extern uint64_t rt_00350744(); /* FUN_00350744 */
extern uint64_t rt_00350750(); /* FUN_00350750 */
extern uint64_t rt_00350768(); /* FUN_00350768 */
extern uint64_t rt_00350774(); /* FUN_00350774 */
extern uint64_t rt_00350780(); /* FUN_00350780 */
extern uint64_t rt_00350798(); /* FUN_00350798 */
extern uint64_t rt_003507a4(); /* FUN_003507a4 */
extern rt16 rt_003507bc(); /* FUN_003507bc */
extern uint64_t rt_003507c8(); /* FUN_003507c8 */
extern uint64_t rt_003507d4(); /* FUN_003507d4 */
extern uint64_t rt_003507e0(); /* FUN_003507e0 */
extern uint64_t rt_003507ec(); /* FUN_003507ec */
extern uint64_t rt_00350810(); /* FUN_00350810 */
extern rt16 rt_0035084c(); /* FUN_0035084c */
extern uint64_t rt_00350878(); /* FUN_00350878 */
extern uint64_t rt_00350884(); /* FUN_00350884 */
extern uint64_t rt_003508a8(); /* FUN_003508a8 */
extern rt16 rt_003508b4(); /* FUN_003508b4 */
extern uint64_t rt_003508c0(); /* FUN_003508c0 */
extern rt16 rt_003508cc(); /* FUN_003508cc */
extern uint64_t rt_003508e4(); /* FUN_003508e4 */
extern rt16 rt_003508f0(); /* FUN_003508f0 */
extern rt16 rt_003508fc(); /* FUN_003508fc */
extern uint64_t rt_00350908(); /* FUN_00350908 */
extern uint64_t rt_00350914(); /* FUN_00350914 */
extern uint64_t rt_00350920(); /* FUN_00350920 */
extern rt16 rt_00350938(); /* FUN_00350938 */
extern uint64_t rt_00350944(); /* FUN_00350944 */
extern uint64_t rt_00350950(); /* FUN_00350950 */
extern uint64_t rt_00350968(); /* FUN_00350968 */
extern uint64_t rt_00350974(); /* FUN_00350974 */
extern uint64_t rt_00350998(); /* FUN_00350998 */
extern rt16 rt_003509a4(); /* FUN_003509a4 */
extern rt16 rt_003509b0(); /* FUN_003509b0 */
extern rt16 rt_003509bc(); /* FUN_003509bc */
extern rt16 rt_003509d4(); /* FUN_003509d4 */
extern rt16 rt_003509e0(); /* FUN_003509e0 */
extern rt16 rt_00350a04(); /* FUN_00350a04 */
extern uint64_t rt_00350a1c(); /* FUN_00350a1c */
extern uint64_t rt_00350a34(); /* FUN_00350a34 */
extern uint64_t rt_00350a40(); /* FUN_00350a40 */
extern uint64_t rt_00350a4c(); /* FUN_00350a4c */
extern uint64_t rt_00350a64(); /* FUN_00350a64 */
extern rt16 rt_00350a70(); /* FUN_00350a70 */
extern uint64_t rt_00350a7c(); /* FUN_00350a7c */
extern uint64_t rt_00350a88(); /* FUN_00350a88 */
extern uint64_t rt_00350aa0(); /* FUN_00350aa0 */
extern uint64_t rt_00350aac(); /* FUN_00350aac */
extern uint64_t rt_00350ab8(); /* FUN_00350ab8 */
extern uint64_t rt_00350ac4(); /* FUN_00350ac4 */
extern uint64_t rt_00350ad0(); /* FUN_00350ad0 */
extern uint64_t rt_00350adc(); /* FUN_00350adc */
extern uint64_t rt_00350af4(); /* FUN_00350af4 */
extern rt16 rt_00350b00(); /* FUN_00350b00 */
extern uint64_t rt_00350b18(); /* FUN_00350b18 */
extern uint64_t rt_00350b24(); /* FUN_00350b24 */
extern uint64_t rt_00350b30(); /* FUN_00350b30 */
extern rt16 rt_00350b3c(); /* FUN_00350b3c */
extern uint64_t rt_00350b48(); /* FUN_00350b48 */
extern rt16 rt_00350b54(); /* FUN_00350b54 */
extern uint64_t rt_00350b6c(); /* FUN_00350b6c */
extern uint64_t rt_00350b78(); /* FUN_00350b78 */
extern uint64_t rt_00350b84(); /* FUN_00350b84 */
extern uint64_t rt_00350bb4(); /* FUN_00350bb4 */
extern uint64_t rt_00350bc0(); /* FUN_00350bc0 */
extern uint64_t rt_00350bcc(); /* FUN_00350bcc */
extern rt16 rt_00350bd8(); /* FUN_00350bd8 */
extern uint64_t rt_00350bf0(); /* FUN_00350bf0 */
extern uint64_t rt_00350bfc(); /* FUN_00350bfc */
extern uint64_t rt_00350c08(); /* FUN_00350c08 */
extern uint64_t rt_00350c14(); /* FUN_00350c14 */
extern uint64_t rt_00350c2c(); /* FUN_00350c2c */
extern rt16 rt_00350c38(); /* FUN_00350c38 */
extern uint64_t rt_00350c68(); /* FUN_00350c68 */
extern uint64_t rt_00350c74(); /* FUN_00350c74 */
extern uint64_t rt_00350c80(); /* FUN_00350c80 */
extern uint64_t rt_00350c8c(); /* FUN_00350c8c */
extern uint64_t rt_00350cb4(); /* FUN_00350cb4 */
extern uint64_t rt_00350cc4(); /* FUN_00350cc4 */
extern uint64_t rt_00350db4(); /* FUN_00350db4 */
extern uint64_t rt_00350e34(); /* FUN_00350e34 */
extern uint64_t rt_00350e54(); /* FUN_00350e54 */
extern uint64_t rt_00350ea4(); /* FUN_00350ea4 */
extern uint64_t rt_00350eb0(); /* FUN_00350eb0 */
extern uint64_t rt_00350ed0(); /* FUN_00350ed0 */
extern uint64_t rt_00350fec(); /* FUN_00350fec */
extern uint64_t rt_0035100c(); /* FUN_0035100c */
extern uint64_t rt_0035102c(); /* FUN_0035102c */
extern uint64_t rt_00351038(); /* FUN_00351038 */
extern rt16 rt_003510a0(); /* FUN_003510a0 */
extern rt16 rt_003510ac(); /* FUN_003510ac */
extern rt16 rt_003510b8(); /* FUN_003510b8 */
extern uint64_t rt_003510c4(); /* FUN_003510c4 */
extern uint64_t rt_003510dc(); /* FUN_003510dc */
extern uint64_t rt_003510f4(); /* FUN_003510f4 */
extern rt16 rt_0035113c(); /* FUN_0035113c */
extern uint64_t rt_00351148(); /* FUN_00351148 */
extern uint64_t rt_00351154(); /* FUN_00351154 */
extern uint64_t rt_00351160(); /* FUN_00351160 */
extern uint64_t rt_00351178(); /* FUN_00351178 */
extern uint64_t rt_00351184(); /* FUN_00351184 */
extern uint64_t rt_00351190(); /* FUN_00351190 */
extern uint64_t rt_003511a8(); /* FUN_003511a8 */
extern uint64_t rt_003511cc(); /* FUN_003511cc */
extern uint64_t rt_003511d8(); /* FUN_003511d8 */
extern uint64_t rt_003511fc(); /* FUN_003511fc */
extern uint64_t rt_00351208(); /* FUN_00351208 */
extern uint64_t rt_00351214(); /* FUN_00351214 */
extern uint64_t rt_00351220(); /* FUN_00351220 */
extern uint64_t rt_00351238(); /* FUN_00351238 */
extern uint64_t rt_0035125c(); /* FUN_0035125c */
extern uint64_t rt_00351274(); /* FUN_00351274 */
extern uint64_t rt_0035128c(); /* FUN_0035128c */
extern uint64_t rt_00351298(); /* FUN_00351298 */
extern uint64_t rt_003512c0(); /* FUN_003512c0 */
extern uint64_t rt_003512d8(); /* FUN_003512d8 */
extern uint64_t rt_003512f4(); /* FUN_003512f4 */
extern uint64_t rt_0035130c(); /* FUN_0035130c */
extern uint64_t rt_00351318(); /* FUN_00351318 */
extern rt16 rt_00351324(); /* FUN_00351324 */
extern rt16 rt_00351330(); /* FUN_00351330 */
extern uint64_t rt_0035133c(); /* FUN_0035133c */
extern uint64_t rt_00351354(); /* FUN_00351354 */
extern uint64_t rt_00351360(); /* FUN_00351360 */
extern uint64_t rt_0035136c(); /* FUN_0035136c */
extern uint64_t rt_00351378(); /* FUN_00351378 */
extern rt16 rt_00351384(); /* FUN_00351384 */
extern uint64_t rt_003513a8(); /* FUN_003513a8 */
extern uint64_t rt_003513b4(); /* FUN_003513b4 */
extern uint64_t rt_003513c0(); /* FUN_003513c0 */
extern uint64_t rt_003513e4(); /* FUN_003513e4 */
extern uint64_t rt_003513f0(); /* FUN_003513f0 */
extern uint64_t rt_003513fc(); /* FUN_003513fc */
extern uint64_t rt_00351414(); /* FUN_00351414 */
extern uint64_t rt_00351420(); /* FUN_00351420 */
extern uint64_t rt_00351438(); /* FUN_00351438 */
extern uint64_t rt_00351444(); /* FUN_00351444 */
extern uint64_t rt_00351450(); /* FUN_00351450 */
extern uint64_t rt_0035145c(); /* FUN_0035145c */
extern uint64_t rt_00351494(); /* FUN_00351494 */
extern uint64_t rt_003514a0(); /* FUN_003514a0 */
extern uint64_t rt_003514ac(); /* FUN_003514ac */
extern uint64_t rt_003514b8(); /* FUN_003514b8 */
extern uint64_t rt_003514d0(); /* FUN_003514d0 */
extern uint64_t rt_003514dc(); /* FUN_003514dc */
extern rt16 rt_003514e8(); /* FUN_003514e8 */
extern uint64_t rt_0035152c(); /* FUN_0035152c */
extern uint64_t rt_00351548(); /* FUN_00351548 */
extern uint64_t rt_00351554(); /* FUN_00351554 */
extern uint64_t rt_00351560(); /* FUN_00351560 */
extern uint64_t rt_0035156c(); /* FUN_0035156c */
extern uint64_t rt_00351584(); /* FUN_00351584 */
extern uint64_t rt_00351590(); /* FUN_00351590 */
extern uint64_t rt_003515b4(); /* FUN_003515b4 */
extern uint64_t rt_003515cc(); /* FUN_003515cc */
extern uint64_t rt_003515d8(); /* FUN_003515d8 */
extern uint64_t rt_003515f0(); /* FUN_003515f0 */
extern uint64_t rt_003515fc(); /* FUN_003515fc */
extern rt16 rt_00351648(); /* FUN_00351648 */
extern uint64_t rt_00351684(); /* FUN_00351684 */
extern uint64_t rt_0035169c(); /* FUN_0035169c */
extern uint64_t rt_003516a8(); /* FUN_003516a8 */
extern uint64_t rt_003516b4(); /* FUN_003516b4 */
extern uint64_t rt_003516c0(); /* FUN_003516c0 */
extern uint64_t rt_003516cc(); /* FUN_003516cc */
extern uint64_t rt_003516e4(); /* FUN_003516e4 */
extern uint64_t rt_003516f0(); /* FUN_003516f0 */
extern uint64_t rt_003516fc(); /* FUN_003516fc */
extern uint64_t rt_00351714(); /* FUN_00351714 */
extern uint64_t rt_00351720(); /* FUN_00351720 */
extern rt16 rt_0035172c(); /* FUN_0035172c */
extern uint64_t rt_00351750(); /* FUN_00351750 */
extern uint64_t rt_0035179c(); /* FUN_0035179c */
extern rt16 rt_003517a8(); /* FUN_003517a8 */
extern uint64_t rt_003517cc(); /* FUN_003517cc */
extern uint64_t rt_003518a0(); /* FUN_003518a0 */
extern uint64_t rt_003518b8(); /* FUN_003518b8 */
extern uint64_t rt_003518c4(); /* FUN_003518c4 */
extern uint64_t rt_003518e8(); /* FUN_003518e8 */
extern uint64_t rt_003518f4(); /* FUN_003518f4 */
extern uint64_t rt_00351900(); /* FUN_00351900 */
extern uint64_t rt_0035190c(); /* FUN_0035190c */
extern uint64_t rt_00351930(); /* FUN_00351930 */
extern uint64_t rt_00351978(); /* FUN_00351978 */
extern uint64_t rt_00351984(); /* FUN_00351984 */
extern rt16 rt_0035199c(); /* FUN_0035199c */
extern rt16 rt_003519a8(); /* FUN_003519a8 */
extern uint64_t rt_003519b4(); /* FUN_003519b4 */
extern uint64_t rt_003519fc(); /* FUN_003519fc */
extern uint64_t rt_00351a08(); /* FUN_00351a08 */
extern uint64_t rt_00351a2c(); /* FUN_00351a2c */
extern uint64_t rt_00351a38(); /* FUN_00351a38 */
extern uint64_t rt_00351a50(); /* FUN_00351a50 */
extern uint64_t rt_00351a68(); /* FUN_00351a68 */
extern uint64_t rt_00351a74(); /* FUN_00351a74 */
extern uint64_t rt_00351aa4(); /* FUN_00351aa4 */
extern uint64_t rt_00351ab0(); /* FUN_00351ab0 */
extern uint64_t rt_00351ac8(); /* FUN_00351ac8 */
extern uint64_t rt_00351ad4(); /* FUN_00351ad4 */
extern uint64_t rt_00351aec(); /* FUN_00351aec */
extern uint64_t rt_00351af8(); /* FUN_00351af8 */
extern uint64_t rt_00351b20(); /* FUN_00351b20 */
extern uint64_t rt_00351b2c(); /* FUN_00351b2c */
extern uint64_t rt_00351b78(); /* FUN_00351b78 */
extern uint64_t rt_00351b84(); /* FUN_00351b84 */
extern uint64_t rt_00351ba0(); /* FUN_00351ba0 */
extern uint64_t rt_00351bd4(); /* FUN_00351bd4 */
extern uint64_t rt_00351bec(); /* FUN_00351bec */
extern uint64_t rt_00351c10(); /* FUN_00351c10 */
extern uint64_t rt_00351c34(); /* FUN_00351c34 */
extern uint64_t rt_00351c4c(); /* FUN_00351c4c */
extern uint64_t rt_00351c64(); /* FUN_00351c64 */
extern uint64_t rt_00351c94(); /* FUN_00351c94 */
extern uint64_t rt_00351cac(); /* FUN_00351cac */
extern uint64_t rt_00351cb8(); /* FUN_00351cb8 */
extern uint64_t rt_00351cc4(); /* FUN_00351cc4 */
extern uint64_t rt_00351cd0(); /* FUN_00351cd0 */
extern uint64_t rt_00351d0c(); /* FUN_00351d0c */
extern rt16 rt_00351d24(); /* FUN_00351d24 */
extern uint64_t rt_00351d4c(); /* FUN_00351d4c */
extern uint64_t rt_00351da8(); /* FUN_00351da8 */
extern rt16 rt_00351dc0(); /* FUN_00351dc0 */
extern uint64_t rt_00351dcc(); /* FUN_00351dcc */
extern rt16 rt_00351df0(); /* FUN_00351df0 */
extern uint64_t rt_00351dfc(); /* FUN_00351dfc */
extern uint64_t rt_00351e14(); /* FUN_00351e14 */
extern uint64_t rt_00351e3c(); /* FUN_00351e3c */
extern uint64_t rt_00351e48(); /* FUN_00351e48 */
extern uint64_t rt_00351e78(); /* FUN_00351e78 */
extern uint64_t rt_00351e84(); /* FUN_00351e84 */
extern uint64_t rt_00351e90(); /* FUN_00351e90 */
extern uint64_t rt_00351e9c(); /* FUN_00351e9c */
extern uint64_t rt_00351ea8(); /* FUN_00351ea8 */
extern uint64_t rt_00351ee0(); /* FUN_00351ee0 */
extern uint64_t rt_00351ef8(); /* FUN_00351ef8 */
extern uint64_t rt_00351f10(); /* FUN_00351f10 */
extern uint64_t rt_00351f1c(); /* FUN_00351f1c */
extern uint64_t rt_00351f40(); /* FUN_00351f40 */
extern uint64_t rt_00351f4c(); /* FUN_00351f4c */
extern uint64_t rt_00351f7c(); /* FUN_00351f7c */
extern uint64_t rt_00351f88(); /* FUN_00351f88 */
extern uint64_t rt_00352098(); /* FUN_00352098 */
extern uint64_t rt_003520b4(); /* FUN_003520b4 */
extern uint64_t rt_003520f8(); /* FUN_003520f8 */
extern uint64_t rt_00352118(); /* FUN_00352118 */
extern uint64_t rt_00352134(); /* FUN_00352134 */
extern uint64_t rt_00352140(); /* FUN_00352140 */
extern uint64_t rt_0035215c(); /* FUN_0035215c */
extern uint64_t rt_003521d4(); /* FUN_003521d4 */
extern uint64_t rt_00352200(); /* FUN_00352200 */
extern uint64_t rt_003523ac(); /* FUN_003523ac */
extern uint64_t rt_003523f0(); /* FUN_003523f0 */
extern uint64_t rt_003523fc(); /* FUN_003523fc */
extern uint64_t rt_0035242c(); /* FUN_0035242c */
extern uint64_t rt_00352438(); /* FUN_00352438 */
extern uint64_t rt_00352450(); /* FUN_00352450 */
extern uint64_t rt_00352474(); /* FUN_00352474 */
extern uint64_t rt_00352480(); /* FUN_00352480 */
extern rt16 rt_00352498(); /* FUN_00352498 */
extern rt16 rt_003524a4(); /* FUN_003524a4 */
extern uint64_t rt_003524b0(); /* FUN_003524b0 */
extern uint64_t rt_003524e0(); /* FUN_003524e0 */
extern uint64_t rt_0035256c(); /* FUN_0035256c */
extern uint64_t rt_00352578(); /* FUN_00352578 */
extern uint64_t rt_00352584(); /* FUN_00352584 */
extern uint64_t rt_003525f4(); /* FUN_003525f4 */
extern uint64_t rt_0035266c(); /* FUN_0035266c */
extern uint64_t rt_00352680(); /* FUN_00352680 */
extern rt16 rt_00352698(); /* FUN_00352698 */
extern uint64_t rt_003526b8(); /* FUN_003526b8 */
extern uint64_t rt_00352720(); /* FUN_00352720 */
extern uint64_t rt_00352744(); /* FUN_00352744 */
extern uint64_t rt_0035284c(); /* FUN_0035284c */
extern uint64_t rt_00352864(); /* FUN_00352864 */
extern uint64_t rt_00352870(); /* FUN_00352870 */
extern uint64_t rt_0035287c(); /* FUN_0035287c */
extern rt16 rt_00352888(); /* FUN_00352888 */
extern uint64_t rt_00352894(); /* FUN_00352894 */
extern uint64_t rt_003528ac(); /* FUN_003528ac */
extern uint64_t rt_00352944(); /* FUN_00352944 */
extern uint64_t rt_00352968(); /* FUN_00352968 */
extern uint64_t rt_00352980(); /* FUN_00352980 */
extern uint64_t rt_00352998(); /* FUN_00352998 */
extern uint64_t rt_003529a4(); /* FUN_003529a4 */
extern uint64_t rt_003529b0(); /* FUN_003529b0 */
extern uint64_t rt_00352a1c(); /* FUN_00352a1c */
extern uint64_t rt_00352a4c(); /* FUN_00352a4c */
extern uint64_t rt_00352a64(); /* FUN_00352a64 */
extern uint64_t rt_00352ae4(); /* FUN_00352ae4 */
extern uint64_t rt_00352b08(); /* FUN_00352b08 */
extern rt16 rt_00352b14(); /* FUN_00352b14 */
extern uint64_t rt_00352b2c(); /* FUN_00352b2c */
extern uint64_t rt_00352b44(); /* FUN_00352b44 */
extern uint64_t rt_00352b5c(); /* FUN_00352b5c */
extern uint64_t rt_00352b68(); /* FUN_00352b68 */
extern uint64_t rt_00352b80(); /* FUN_00352b80 */
extern uint64_t rt_00352b8c(); /* FUN_00352b8c */
extern uint64_t rt_00352b98(); /* FUN_00352b98 */
extern uint64_t rt_00352bb0(); /* FUN_00352bb0 */
extern uint64_t rt_00352bbc(); /* FUN_00352bbc */
extern uint64_t rt_00352bc8(); /* FUN_00352bc8 */
extern uint64_t rt_00352bec(); /* FUN_00352bec */
extern uint64_t rt_00352bf8(); /* FUN_00352bf8 */
extern uint64_t rt_00352c10(); /* FUN_00352c10 */
extern uint64_t rt_00352c28(); /* FUN_00352c28 */
extern uint64_t rt_00352c34(); /* FUN_00352c34 */
extern uint64_t rt_00352c4c(); /* FUN_00352c4c */
extern uint64_t rt_00352c8c(); /* FUN_00352c8c */
extern uint64_t rt_00352c98(); /* FUN_00352c98 */
extern uint64_t rt_00352ca4(); /* FUN_00352ca4 */
extern uint64_t rt_00352cbc(); /* FUN_00352cbc */
extern uint64_t rt_00352d04(); /* FUN_00352d04 */
extern uint64_t rt_00352d28(); /* FUN_00352d28 */
extern uint64_t rt_00352d34(); /* FUN_00352d34 */
extern uint64_t rt_00352d40(); /* FUN_00352d40 */
extern uint64_t rt_00352d4c(); /* FUN_00352d4c */
extern rt16 rt_00352d64(); /* FUN_00352d64 */
extern uint64_t rt_00352d70(); /* FUN_00352d70 */
extern uint64_t rt_00352d88(); /* FUN_00352d88 */
extern uint64_t rt_00352d94(); /* FUN_00352d94 */
extern uint64_t rt_00352dd0(); /* FUN_00352dd0 */
extern uint64_t rt_00352e30(); /* FUN_00352e30 */
extern uint64_t rt_00352e60(); /* FUN_00352e60 */
extern uint64_t rt_00352e78(); /* FUN_00352e78 */
extern uint64_t rt_00352ea8(); /* FUN_00352ea8 */
extern uint64_t rt_00352ecc(); /* FUN_00352ecc */
extern rt16 rt_00352efc(); /* FUN_00352efc */
extern uint64_t rt_00352f48(); /* FUN_00352f48 */
extern uint64_t rt_00352f54(); /* FUN_00352f54 */
extern uint64_t rt_00353000(); /* FUN_00353000 */
extern uint64_t rt_00353034(); /* FUN_00353034 */
extern uint64_t rt_00353050(); /* FUN_00353050 */
extern uint64_t rt_0035305c(); /* FUN_0035305c */
extern uint64_t rt_00353074(); /* FUN_00353074 */
extern uint64_t rt_003530a4(); /* FUN_003530a4 */
extern uint64_t rt_003530cc(); /* FUN_003530cc */
extern uint64_t rt_003530f4(); /* FUN_003530f4 */
extern rt16 rt_00353124(); /* FUN_00353124 */
extern uint64_t rt_00353130(); /* FUN_00353130 */
extern uint64_t rt_00353148(); /* FUN_00353148 */
extern uint64_t rt_0035316c(); /* FUN_0035316c */
extern uint64_t rt_00353184(); /* FUN_00353184 */
extern rt16 rt_0035319c(); /* FUN_0035319c */
extern uint64_t rt_003531e4(); /* FUN_003531e4 */
extern uint64_t rt_0035322c(); /* FUN_0035322c */
extern uint64_t rt_0035336c(); /* FUN_0035336c */
extern uint64_t rt_00353378(); /* FUN_00353378 */
extern uint64_t rt_00353384(); /* FUN_00353384 */
extern uint64_t rt_00353390(); /* FUN_00353390 */
extern uint64_t rt_0035343c(); /* FUN_0035343c */
extern uint64_t rt_00353468(); /* FUN_00353468 */
extern uint64_t rt_00353480(); /* FUN_00353480 */
extern uint64_t rt_0035348c(); /* FUN_0035348c */
extern uint64_t rt_003534bc(); /* FUN_003534bc */
extern uint64_t rt_003534f8(); /* FUN_003534f8 */
extern uint64_t rt_0035359c(); /* FUN_0035359c */
extern uint64_t rt_003536dc(); /* FUN_003536dc */
extern uint64_t rt_00353718(); /* FUN_00353718 */
extern uint64_t rt_00353734(); /* FUN_00353734 */
extern uint64_t rt_003537f0(); /* FUN_003537f0 */
extern uint64_t rt_003538bc(); /* FUN_003538bc */
extern uint64_t rt_00353930(); /* FUN_00353930 */
extern uint64_t rt_00353960(); /* FUN_00353960 */
extern uint64_t rt_00353990(); /* FUN_00353990 */
extern uint64_t rt_0035399c(); /* FUN_0035399c */
extern uint64_t rt_00353a00(); /* FUN_00353a00 */
extern uint64_t rt_00353a18(); /* FUN_00353a18 */
extern uint64_t rt_00353a24(); /* FUN_00353a24 */
extern uint64_t rt_00353a84(); /* FUN_00353a84 */
extern uint64_t rt_00353b04(); /* FUN_00353b04 */
extern uint64_t rt_00353b10(); /* FUN_00353b10 */
extern uint64_t rt_00353b58(); /* FUN_00353b58 */
extern uint64_t rt_00353b88(); /* FUN_00353b88 */
extern uint64_t rt_00353bac(); /* FUN_00353bac */
extern uint64_t rt_00353bd0(); /* FUN_00353bd0 */
extern uint64_t rt_00353be8(); /* FUN_00353be8 */
extern uint64_t rt_00353bf4(); /* FUN_00353bf4 */
extern uint64_t rt_00353c18(); /* FUN_00353c18 */
extern uint64_t rt_00353c3c(); /* FUN_00353c3c */
extern uint64_t rt_00353c60(); /* FUN_00353c60 */
extern uint64_t rt_00353c6c(); /* FUN_00353c6c */
extern uint64_t rt_00353c78(); /* FUN_00353c78 */
extern uint64_t rt_00353c84(); /* FUN_00353c84 */
extern uint64_t rt_00353cc0(); /* FUN_00353cc0 */
extern uint64_t rt_00353ce4(); /* FUN_00353ce4 */
extern uint64_t rt_00353d94(); /* FUN_00353d94 */
extern uint64_t rt_00353dac(); /* FUN_00353dac */
extern uint64_t rt_00353db8(); /* FUN_00353db8 */
extern uint64_t rt_00353df0(); /* FUN_00353df0 */
extern uint64_t rt_00353dfc(); /* FUN_00353dfc */
extern uint64_t rt_00353e08(); /* FUN_00353e08 */
extern uint64_t rt_00353e38(); /* FUN_00353e38 */
extern uint64_t rt_00353e50(); /* FUN_00353e50 */
extern uint64_t rt_00353e94(); /* FUN_00353e94 */
extern uint64_t rt_00353ee4(); /* FUN_00353ee4 */
extern uint64_t rt_00353f20(); /* FUN_00353f20 */
extern uint64_t rt_00353f44(); /* FUN_00353f44 */
extern uint64_t rt_00353f94(); /* FUN_00353f94 */
extern uint64_t rt_00353fa0(); /* FUN_00353fa0 */
extern uint64_t rt_00353fac(); /* FUN_00353fac */
extern uint64_t rt_0035404c(); /* FUN_0035404c */
extern uint64_t rt_00354058(); /* FUN_00354058 */
extern uint64_t rt_00354064(); /* FUN_00354064 */
extern uint64_t rt_00354088(); /* FUN_00354088 */
extern uint64_t rt_00354128(); /* FUN_00354128 */
extern uint64_t rt_00354134(); /* FUN_00354134 */
extern uint64_t rt_00354270(); /* FUN_00354270 */
extern uint64_t rt_003542b8(); /* FUN_003542b8 */
extern uint64_t rt_0035430c(); /* FUN_0035430c */
extern uint64_t rt_00354364(); /* FUN_00354364 */
extern uint64_t rt_00354370(); /* FUN_00354370 */
extern uint64_t rt_00354394(); /* FUN_00354394 */
extern uint64_t rt_003543c4(); /* FUN_003543c4 */
extern uint64_t rt_003543f8(); /* FUN_003543f8 */
extern uint64_t rt_0035441c(); /* FUN_0035441c */
extern uint64_t rt_00354474(); /* FUN_00354474 */
extern uint64_t rt_0035454c(); /* FUN_0035454c */
extern uint64_t rt_00354570(); /* FUN_00354570 */
extern uint64_t rt_0035457c(); /* FUN_0035457c */
extern uint64_t rt_003545a0(); /* FUN_003545a0 */
extern uint64_t rt_003545e8(); /* FUN_003545e8 */
extern uint64_t rt_0035460c(); /* FUN_0035460c */
extern uint64_t rt_0035463c(); /* FUN_0035463c */
extern uint64_t rt_00354648(); /* FUN_00354648 */
extern uint64_t rt_0035466c(); /* FUN_0035466c */
extern uint64_t rt_003546c0(); /* FUN_003546c0 */
extern uint64_t rt_00354780(); /* FUN_00354780 */
extern uint64_t rt_0035478c(); /* FUN_0035478c */
extern uint64_t rt_003547ec(); /* FUN_003547ec */
extern uint64_t rt_003547f8(); /* FUN_003547f8 */
extern uint64_t rt_00354810(); /* FUN_00354810 */
extern uint64_t rt_00354828(); /* FUN_00354828 */
extern uint64_t rt_00354834(); /* FUN_00354834 */
extern uint64_t rt_00354840(); /* FUN_00354840 */
extern uint64_t rt_003548e8(); /* FUN_003548e8 */
extern uint64_t rt_003549a8(); /* FUN_003549a8 */
extern uint64_t rt_00354ab0(); /* FUN_00354ab0 */
extern uint64_t rt_00354abc(); /* FUN_00354abc */
extern uint64_t rt_00354ac8(); /* FUN_00354ac8 */
extern uint64_t rt_00354b68(); /* FUN_00354b68 */
extern uint64_t rt_00354b74(); /* FUN_00354b74 */
extern uint64_t rt_00354bbc(); /* FUN_00354bbc */
extern uint64_t rt_00354ca8(); /* FUN_00354ca8 */
extern uint64_t rt_00354cc0(); /* FUN_00354cc0 */
extern uint64_t rt_00354cfc(); /* FUN_00354cfc */
extern uint64_t rt_00354d08(); /* FUN_00354d08 */
extern uint64_t rt_00354d68(); /* FUN_00354d68 */
extern uint64_t rt_00354d74(); /* FUN_00354d74 */
extern uint64_t rt_00354f8c(); /* FUN_00354f8c */
extern uint64_t rt_00355018(); /* FUN_00355018 */
extern uint64_t rt_00355100(); /* FUN_00355100 */
extern uint64_t rt_003553d8(); /* FUN_003553d8 */
extern uint64_t rt_00355404(); /* FUN_00355404 */
extern uint64_t rt_00355424(); /* FUN_00355424 */
extern uint64_t rt_00355430(); /* FUN_00355430 */
extern rt16 rt_00355634(); /* FUN_00355634 */
extern uint64_t rt_00355640(); /* FUN_00355640 */
extern uint64_t rt_00355684(); /* FUN_00355684 */
extern uint64_t rt_00355780(); /* FUN_00355780 */
extern uint64_t rt_003557a8(); /* FUN_003557a8 */
extern uint64_t rt_003557b4(); /* FUN_003557b4 */
extern uint64_t rt_003557d8(); /* FUN_003557d8 */
extern uint64_t rt_00355884(); /* FUN_00355884 */
extern uint64_t rt_00355988(); /* FUN_00355988 */
extern uint64_t rt_003559d8(); /* FUN_003559d8 */
extern uint64_t rt_00355a40(); /* FUN_00355a40 */
extern uint64_t rt_00355ad0(); /* FUN_00355ad0 */
extern uint64_t rt_00355af8(); /* FUN_00355af8 */
extern uint64_t rt_00355b04(); /* FUN_00355b04 */
extern uint64_t rt_00355b1c(); /* FUN_00355b1c */
extern uint64_t rt_00355bb8(); /* FUN_00355bb8 */
extern rt16 rt_00355bc4(); /* FUN_00355bc4 */
extern uint64_t rt_00355c58(); /* FUN_00355c58 */
extern uint64_t rt_00355d28(); /* FUN_00355d28 */
extern uint64_t rt_00355db4(); /* FUN_00355db4 */
extern uint64_t rt_00355dfc(); /* FUN_00355dfc */
extern uint64_t rt_00355e50(); /* FUN_00355e50 */
extern uint64_t rt_00355e80(); /* FUN_00355e80 */
extern uint64_t rt_00355e8c(); /* FUN_00355e8c */
extern uint64_t rt_00355ea4(); /* FUN_00355ea4 */
extern uint64_t rt_00355ef8(); /* FUN_00355ef8 */
extern uint64_t rt_00355f10(); /* FUN_00355f10 */
extern uint64_t rt_00356060(); /* FUN_00356060 */
extern rt16 rt_0035606c(); /* FUN_0035606c */
extern uint64_t rt_00356078(); /* FUN_00356078 */
extern uint64_t rt_003560a8(); /* FUN_003560a8 */
extern uint64_t rt_00356140(); /* FUN_00356140 */
extern uint64_t rt_0035614c(); /* FUN_0035614c */
extern uint64_t rt_003561b8(); /* FUN_003561b8 */
extern uint64_t rt_003561dc(); /* FUN_003561dc */
extern uint64_t rt_00356224(); /* FUN_00356224 */
extern uint64_t rt_00356230(); /* FUN_00356230 */
extern rt16 rt_00356248(); /* FUN_00356248 */
extern uint64_t rt_00356278(); /* FUN_00356278 */
extern uint64_t rt_00356334(); /* FUN_00356334 */
extern uint64_t rt_0035647c(); /* FUN_0035647c */
extern uint64_t rt_003564a4(); /* FUN_003564a4 */
extern uint64_t rt_00356670(); /* FUN_00356670 */
extern uint64_t rt_003566b4(); /* FUN_003566b4 */
extern uint64_t rt_003566d8(); /* FUN_003566d8 */
extern uint64_t rt_0035675c(); /* FUN_0035675c */
extern uint64_t rt_00356768(); /* FUN_00356768 */
extern uint64_t rt_003567bc(); /* FUN_003567bc */
extern uint64_t rt_003567ec(); /* FUN_003567ec */
extern uint64_t rt_00356810(); /* FUN_00356810 */
extern uint64_t rt_0035681c(); /* FUN_0035681c */
extern uint64_t rt_00356834(); /* FUN_00356834 */
extern uint64_t rt_00356840(); /* FUN_00356840 */
extern rt16 rt_00356864(); /* FUN_00356864 */
extern uint64_t rt_003568e8(); /* FUN_003568e8 */
extern uint64_t rt_0035690c(); /* FUN_0035690c */
extern uint64_t rt_00356924(); /* FUN_00356924 */
extern uint64_t rt_00356958(); /* FUN_00356958 */
extern uint64_t rt_00356964(); /* FUN_00356964 */
extern uint64_t rt_003569d8(); /* FUN_003569d8 */
extern uint64_t rt_003569e4(); /* FUN_003569e4 */
extern uint64_t rt_003569f0(); /* FUN_003569f0 */
extern uint64_t rt_003569fc(); /* FUN_003569fc */
extern uint64_t rt_00356a08(); /* FUN_00356a08 */
extern uint64_t rt_00356a70(); /* FUN_00356a70 */
extern uint64_t rt_00356aac(); /* FUN_00356aac */
extern uint64_t rt_00356b20(); /* FUN_00356b20 */
extern uint64_t rt_00356b98(); /* FUN_00356b98 */
extern uint64_t rt_00356bb0(); /* FUN_00356bb0 */
extern uint64_t rt_00356c30(); /* FUN_00356c30 */
extern uint64_t rt_00356c48(); /* FUN_00356c48 */
extern uint64_t rt_00356e34(); /* FUN_00356e34 */
extern uint64_t rt_0035705c(); /* FUN_0035705c */
extern uint64_t rt_003570f0(); /* FUN_003570f0 */
extern uint64_t rt_003571ec(); /* FUN_003571ec */
extern uint64_t rt_00357250(); /* FUN_00357250 */
extern uint64_t rt_00357274(); /* FUN_00357274 */
extern uint64_t rt_00357350(); /* FUN_00357350 */
extern uint64_t rt_003573c0(); /* FUN_003573c0 */
extern uint64_t rt_00357400(); /* FUN_00357400 */
extern uint64_t rt_0035748c(); /* FUN_0035748c */
extern uint64_t rt_00357508(); /* FUN_00357508 */
extern uint64_t rt_003575b0(); /* FUN_003575b0 */
extern uint64_t rt_003575bc(); /* FUN_003575bc */
extern uint64_t rt_0035764c(); /* FUN_0035764c */
extern uint64_t rt_00357664(); /* FUN_00357664 */
extern uint64_t rt_00357710(); /* FUN_00357710 */
extern uint64_t rt_00357760(); /* FUN_00357760 */
extern uint64_t rt_003578a8(); /* FUN_003578a8 */
extern uint64_t rt_003578c0(); /* FUN_003578c0 */
extern uint64_t rt_003579f4(); /* FUN_003579f4 */
extern uint64_t rt_00357a34(); /* FUN_00357a34 */
extern uint64_t rt_00357a90(); /* FUN_00357a90 */
extern uint64_t rt_00357be0(); /* FUN_00357be0 */
extern uint64_t rt_00357c88(); /* FUN_00357c88 */
extern uint64_t rt_00357fd4(); /* FUN_00357fd4 */
extern uint64_t rt_003580c4(); /* FUN_003580c4 */
extern uint64_t rt_003582a8(); /* FUN_003582a8 */
extern uint64_t rt_003584ec(); /* FUN_003584ec */
extern uint64_t rt_00358624(); /* FUN_00358624 */
extern uint64_t rt_00358690(); /* FUN_00358690 */
extern uint64_t rt_003586f0(); /* FUN_003586f0 */
extern uint64_t rt_00358720(); /* FUN_00358720 */
extern uint64_t rt_0035872c(); /* FUN_0035872c */
extern uint64_t rt_00358828(); /* FUN_00358828 */
extern uint64_t rt_00358948(); /* FUN_00358948 */
extern uint64_t rt_00358954(); /* FUN_00358954 */
extern uint64_t rt_0035899c(); /* FUN_0035899c */
extern uint64_t rt_003589c0(); /* FUN_003589c0 */
extern uint64_t rt_003589cc(); /* FUN_003589cc */
extern uint64_t rt_00358a08(); /* FUN_00358a08 */
extern rt16 rt_00358a44(); /* FUN_00358a44 */
extern uint64_t rt_00358a68(); /* FUN_00358a68 */
extern uint64_t rt_00358ad4(); /* FUN_00358ad4 */
extern uint64_t rt_00358bc0(); /* FUN_00358bc0 */
extern uint64_t rt_00358cbc(); /* FUN_00358cbc */
extern uint64_t rt_00358cc8(); /* FUN_00358cc8 */
extern uint64_t rt_00358d10(); /* FUN_00358d10 */
extern uint64_t rt_00358d58(); /* FUN_00358d58 */
extern uint64_t rt_00358d7c(); /* FUN_00358d7c */
extern uint64_t rt_00358d88(); /* FUN_00358d88 */
extern uint64_t rt_00358da0(); /* FUN_00358da0 */
extern uint64_t rt_00358db8(); /* FUN_00358db8 */
extern uint64_t rt_00358dc4(); /* FUN_00358dc4 */
extern uint64_t rt_00358dd0(); /* FUN_00358dd0 */
extern uint64_t rt_00358df4(); /* FUN_00358df4 */
extern uint64_t rt_00358e34(); /* FUN_00358e34 */
extern uint64_t rt_00358f54(); /* FUN_00358f54 */
extern uint64_t rt_00358f9c(); /* FUN_00358f9c */
extern rt16 rt_00358ff4(); /* FUN_00358ff4 */
extern uint64_t rt_00359018(); /* FUN_00359018 */
extern uint64_t rt_00359338(); /* FUN_00359338 */
extern uint64_t rt_00359478(); /* FUN_00359478 */
extern uint64_t rt_003594f4(); /* FUN_003594f4 */
extern rt16 rt_00359518(); /* FUN_00359518 */
extern uint64_t rt_0035955c(); /* FUN_0035955c */
extern uint64_t rt_0035964c(); /* FUN_0035964c */
extern rt16 rt_00359834(); /* FUN_00359834 */
extern uint64_t rt_0035985c(); /* FUN_0035985c */
extern uint64_t rt_00359a78(); /* FUN_00359a78 */
extern uint64_t rt_00359c64(); /* FUN_00359c64 */
extern uint64_t rt_00359ca4(); /* FUN_00359ca4 */
extern uint64_t rt_00359de8(); /* FUN_00359de8 */
extern uint64_t rt_00359eb4(); /* FUN_00359eb4 */
extern uint64_t rt_00359f28(); /* FUN_00359f28 */
extern uint64_t rt_00359f6c(); /* FUN_00359f6c */
extern uint64_t rt_0035a080(); /* FUN_0035a080 */
extern uint64_t rt_0035a08c(); /* FUN_0035a08c */
extern uint64_t rt_0035a104(); /* FUN_0035a104 */
extern uint64_t rt_0035a1b4(); /* FUN_0035a1b4 */
extern uint64_t rt_0035a2d0(); /* FUN_0035a2d0 */
extern uint64_t rt_0035a3d0(); /* FUN_0035a3d0 */
extern uint64_t rt_0035a3f4(); /* FUN_0035a3f4 */
extern uint64_t rt_0035a44c(); /* FUN_0035a44c */
extern uint64_t rt_0035a478(); /* FUN_0035a478 */
extern uint64_t rt_0035a4f8(); /* FUN_0035a4f8 */
extern uint64_t rt_0035a540(); /* FUN_0035a540 */
extern uint64_t rt_0035a578(); /* FUN_0035a578 */
extern uint64_t rt_0035a590(); /* FUN_0035a590 */
extern uint64_t rt_0035a59c(); /* FUN_0035a59c */
extern uint64_t rt_0035a6e8(); /* FUN_0035a6e8 */
extern uint64_t rt_0035a6f4(); /* FUN_0035a6f4 */
extern uint64_t rt_0035a700(); /* FUN_0035a700 */
extern uint64_t rt_0035a718(); /* FUN_0035a718 */
extern rt16 rt_0035a758(); /* FUN_0035a758 */
extern uint64_t rt_0035a76c(); /* FUN_0035a76c */
extern uint64_t rt_0035ac40(); /* FUN_0035ac40 */
extern uint64_t rt_0035ac58(); /* FUN_0035ac58 */
extern uint64_t rt_00365b6c(); /* FUN_00365b6c */
extern uint64_t rt_0036a908(); /* FUN_0036a908 */
extern rt16 rt_0036a940(); /* FUN_0036a940 */
extern uint64_t rt_0036b118(); /* FUN_0036b118 */
extern uint64_t rt_0036b270(); /* FUN_0036b270 */
extern uint64_t rt_003722e4(); /* FUN_003722e4 */
extern uint64_t rt_00376820(); /* FUN_00376820 */
extern rt16 rt_00377824(); /* FUN_00377824 */
extern rt16 rt_00377bec(); /* FUN_00377bec */
extern uint64_t rt_00377dcc(); /* FUN_00377dcc */
extern uint64_t rt_003a25d4(); /* FUN_003a25d4 */
extern uint64_t rt_0060e3fc(); /* FUN_0060e3fc */

/* ---- forward declarations for in-slice functions ---- */
void FUN_0021476c( void);
void FUN_00214784( void);
void FUN_002147f8( void);
void FUN_002149d0( void);
uint64_t FUN_00214a64( void);
void FUN_00214af4( void);
void FUN_00214d18( void);
void FUN_00214d80(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_002152b8(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_00215428( void);
void FUN_00215600( void);
void FUN_002159d4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4);
void FUN_00215cd0(uint64_t param_1, uint64_t param_2, uint64_t param_3, long param_4, uint64_t param_5);
void FUN_00216114( void);
void FUN_00216284( void);
void FUN_00216354(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void * FUN_00216418(long * param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4);
rt16 FUN_00216498(long * param_1, uint64_t param_2, long param_3, uint64_t param_4);
void FUN_002165c0(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_0021662c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_00216900( void);
void FUN_00216a00(uint64_t param_1, uint64_t param_2, long param_3);
void FUN_00216b88( void);
void FUN_00216c60( void);
void FUN_00216dbc(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5);
void FUN_00216f9c(uint64_t param_1, uint64_t param_2, uint64_t param_3, long param_4);
void FUN_002170e0(void);
void FUN_00217100( void);
uint32_t FUN_002171a8( void);
uint32_t FUN_002177bc( void);
uint32_t FUN_00217c60( void);
uint32_t FUN_00217ea0( void);
uint32_t FUN_00218068( void);
void FUN_002181e0( void);
void FUN_002185ec( void);
void FUN_0021867c(uint64_t param_1);
void FUN_0021868c( void);
void FUN_00218714( void);
void FUN_002187e0( void);
void FUN_00218ae4( void);
void FUN_0021914c(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_002191fc( void);
rt16 FUN_0021927c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4);
rt16 FUN_00219370( void);
rt16 FUN_0021947c(long param_1, code * param_2);
bool FUN_00219554(uint64_t param_1, uint64_t param_2, code * param_3);
void FUN_002195e0(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_002198fc( void);
void FUN_00219a00(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4);
void FUN_00219fcc(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4);
void FUN_0021a5bc( void);
long FUN_0021a660(unsigned long param_1, unsigned long param_2, char param_3, unsigned long param_4, unsigned long param_5, char param_6, uint64_t param_7, uint64_t param_8, uint64_t param_9, uint64_t param_10);
long FUN_0021acec(unsigned long param_1, long param_2, char param_3, unsigned long param_4, long param_5, char param_6, uint64_t param_7, uint64_t param_8, uint64_t param_9, uint64_t param_10);
long FUN_0021b1a4(unsigned long param_1, unsigned long param_2, char param_3, unsigned long param_4, unsigned long param_5, char param_6);
long FUN_0021b91c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, long param_7, code * param_8, uint64_t param_9);
long FUN_0021bf60(long param_1, long param_2, char param_3, long param_4, long param_5, char param_6, uint64_t param_7, code * param_8, uint64_t param_9);
long FUN_0021c41c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, uint64_t param_7, uint64_t param_8, code * param_9, uint64_t param_10);
void FUN_0021cad0(uint64_t param_1, uint64_t param_2, long param_3, long param_4, uint64_t param_5);
uint32_t FUN_0021d760( void);
void FUN_0021d7a0( void);
void FUN_0021da44(uint64_t param_1, uint64_t param_2, long param_3);
void FUN_0021db04(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, uint64_t param_6);
void FUN_0021de4c( void);
void FUN_0021dfcc(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4);
void FUN_0021e254( void);
void * FUN_0021e3a0(long * param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4);
rt16 FUN_0021e420(long * param_1, uint64_t param_2, long param_3, uint64_t param_4, uint64_t param_5);
void FUN_0021e548( void);
void FUN_0021e5c4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4);
void FUN_0021e614(uint64_t param_1, uint64_t param_2, uint64_t param_3);
void FUN_0021e6e4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, unsigned long param_5);
void FUN_0021e75c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, unsigned long param_6);
void FUN_0021e7dc(uint64_t param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4);
uint32_t FUN_0021e844(long param_1);
void FUN_0021e870(void);
bool FUN_0021e874(uint8_t * param_1, uint8_t * param_2);
void FUN_0021e8c0(uint8_t * param_1, uint64_t * param_2);
void FUN_0021e8f0(uint64_t * param_1);
uint32_t FUN_0021e940( void);
uint32_t FUN_0021e980( void);
uint32_t FUN_0021e9c0( void);
uint32_t FUN_0021ea00( void);
uint32_t FUN_0021ea44( void);
void FUN_0021ea88( void);
void FUN_0021ebbc( void);
void FUN_0021ec38( void);
void FUN_0021edec( void);
void FUN_0021ee60( void);
void FUN_0021eec4( void);
unsigned long FUN_0021ef30(unsigned long param_1, rt16 param_2);
float FUN_0021ef5c(float param_1, float param_2);
double FUN_0021ef80(double param_1, double param_2);
unsigned long FUN_0021efbc(unsigned long param_1, rt16 param_2);
float FUN_0021efe8(float param_1, float param_2);
double FUN_0021f00c(double param_1, double param_2);
void FUN_0021f048( void);
unsigned long FUN_0021f104(unsigned long param_1, rt16 param_2);
float FUN_0021f138(float param_1, float param_2);
double FUN_0021f164(double param_1, double param_2);
unsigned long FUN_0021f1a8(unsigned long param_1, rt16 param_2);
float FUN_0021f1dc(float param_1, float param_2);
double FUN_0021f208(double param_1, double param_2);
void FUN_0021f24c( void);
uint32_t FUN_0021f510( void);
void FUN_0021f648( void);
void FUN_0021f7b0(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, code * param_6);
void FUN_00223508( void);
void FUN_00223960( void);
uint32_t FUN_00224114(char param_1, uint32_t param_2, uint32_t param_3);
uint32_t FUN_00224134(char param_1, uint32_t param_2, uint32_t param_3);
rt16 FUN_00224154(uint64_t param_1, uint64_t param_2, unsigned long param_3);
void FUN_00224180(uint64_t param_1, uint64_t param_2, code * param_3, code * param_4, uint64_t param_5);
void FUN_00225cbc( void);
bool FUN_002260b0(unsigned long * param_1, unsigned long param_2, unsigned long param_3);
void FUN_00226320(uint64_t param_1, uint64_t param_2, code * param_3, uint64_t param_4, uint64_t param_5, code * param_6, uint64_t param_7);
void FUN_00228914( void);
void FUN_00228a7c( void);
void FUN_00228bec( void);
void FUN_00228d58(long param_1, uint64_t param_2, code * UNRECOVERED_JUMPTABLE);
void FUN_00228e24( void);
void FUN_00228e28( void);

/* FUN_0021476c @ 0x0021476c   (est. swift_runtime_enable)
 * Ghidra: void FUN_0021476c( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021476c( void){
  rt_00268734();
  return;
}



/* FUN_00214784 @ 0x00214784   (est. swift_vtable_dispatch2)
 * Ghidra: void FUN_00214784( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00214784( void){
  uint64_t *v1;
  long v2;
  long v3;
  uint64_t v6;
  uint64_t v5;
  long v4;
  
  rt_00351da8();
  rt_0034a354();
  rt_00349830();
  rt_00350968();
  rt_00377824();
  rt_00349530();
  (**(code **)(v3 + 0x20))();
  rt_0034e70c();
  v2 = rt_0031bc58();
  v1 = (uint64_t *)(v4 + *(int *)(v2 + 0x24));
  *v1 = v5;
  v1[1] = v6;
  return;
}



/* FUN_002147f8 @ 0x002147f8   (est. swift_runloop_dispatch)
 * Ghidra: void FUN_002147f8( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002147f8( void){
  uint8_t v13;
  uint64_t v3;
  uint64_t v4;
  uint64_t v6;
  code *v1;
  uint64_t v7;
  unsigned long v5;
  uint64_t v11;
  code *v9;
  code *v8;
  long v10;
  long v12;
  code *v2;
  rt16 v14;
  
  v14 = rt_0008e518();
  rt_003520f8();
  rt_00352720();
  rt_003513c0();
  rt_00377824();
  rt_0034e130();
  rt_00310d68();
  v3 = rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aee4();
  rt_00349734();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0d4();
  rt_00352720();
  rt_003513c0();
  v4 = rt_00377824().lo;
  rt_003510dc();
  v6 = rt_00377bec().lo;
  v1 = (code *)rt_000a68f4();
  do {
    v7 = rt_00377dcc(0,v4);
    (*v1)(v7,v6);
    v7 = rt_0034aa54();
    if ((bool)v13) {
      rt_0035152c(v7,v3);
      (*v8)();
      v3 = 1;
LBL_002149a8:
      rt_00351548(v11,v3);
      rt_000839d8();
      rt_0008e500(v14.hi);
      return;
    }
    v2 = *(code **)(v10 + 0x20U);
    rt_00350048();
    (*v2)();
    v5 = (**(code **)(v12 + *(int *)(v14.lo + 0x24)))();
    if ((v5 & 1) != 0) {
      rt_003510ac();
      (*v2)(v10 + 0x20U & 0xffffffffffff | 0x48d8000000000000);
      v3 = 0;
      goto LBL_002149a8;
    }
    rt_003508a8(*(uint64_t *)(v10 + 8));
    (*v9)();
  } while( true );
}



/* FUN_002149d0 @ 0x002149d0   (est. swift_dispatch_next)
 * Ghidra: void FUN_002149d0( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002149d0( void){
  uint64_t *v1;
  uint64_t v2;
  code *v3;
  long v5;
  long v4;
  
  rt_00351cc4();
  rt_00349830();
  rt_003505c4();
  rt_00377824();
  rt_00351f10();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0c4();
  rt_003506b0();
  rt_0034c2a4();
  v2 = (*v3)();
  v1 = (uint64_t *)(v4 + *(int *)(v5 + 0x24));
  rt_00353468(v2,*v1,v1[1]);
  rt_00353b58();
  ((code)FUN_00214784)();
  return;
}



/* FUN_00214a64 @ 0x00214a64   (est. swift_try_dispatch)
 * Ghidra: uint64_t FUN_00214a64( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint64_t FUN_00214a64( void){
  unsigned long v1;
  code *UNRECOVERED_JUMPTABLE;
  uint64_t v2;
  long v3;
  long v5;
  long v4;
  
  rt_0035316c();
  v1 = (**(code **)(v5 + *(int *)(v3 + 0x24)))();
  if ((v1 & 1) != 0) {
    UNRECOVERED_JUMPTABLE = (code *)rt_0031b62c(*(uint64_t *)(v4 + 0x18));
                    /* WARNING: Could not recover jumptable at 0x00214ad0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    v2 = (*UNRECOVERED_JUMPTABLE)();
    return v2;
  }
  return 0;
}



/* FUN_00214af4 @ 0x00214af4   (est. swift_runloop_iter)
 * Ghidra: void FUN_00214af4( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00214af4( void){
  code *v1;
  code *v3;
  unsigned long v5;
  uint64_t v6;
  code *v2;
  uint64_t v13;
  uint64_t v15;
  code *v11;
  long v8;
  code *v10;
  code *v7;
  code *v9;
  code *v12;
  code *v14;
  long v16;
  uint64_t v4;
  uint64_t v17;
  rt16 v19;
  code *v18;
  
  rt_0008e518();
  rt_003518c4();
  rt_00350bd8(v13);
  v4 = *(uint64_t *)(v16 + 0x10);
  v19 = rt_003497a0();
  v4 = rt_00377824(v19.lo,v19.hi,v4).lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034cd54();
  rt_0034cae8();
  rt_003510f4();
  rt_00377824();
  rt_00348cd0();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  rt_003506e8();
  rt_003507bc(v15);
  (*v14)();
  v3 = (code *)rt_00310924();
  rt_0035705c();
  rt_00351ba0();
  rt_00377bec();
  rt_00027754();
  rt_0014ae44();
  rt_003561b8();
  while( true ) {
    rt_003504f4();
    (*v3)();
    rt_00351324();
    rt_00351b20();
    v5 = (*v18)();
    rt_003567ec();
    rt_00350b00();
    (*v11)();
    if ((v5 & 1) != 0) break;
    rt_0035a1b4();
    v1 = *(code **)(v16 + v8);
    v6 = rt_00351b84();
    rt_00352450(v6,v15);
    v2 = (code *)(*v10)();
    v19 = rt_00352b14();
    (*v7)(v19.lo,v19.hi,v4);
    rt_0034cfa4();
    (*v2)();
    v5 = (*v1)();
    rt_00354ab0();
    rt_00350a34();
    (*v9)();
    if ((v5 & 1) != 0) break;
    rt_00027818();
    rt_00350a88();
    rt_00350998();
    (*v12)();
  }
  rt_0008e500(v17);
  return;
}



/* FUN_00214d18 @ 0x00214d18   (est. swift_vtable_call2)
 * Ghidra: void FUN_00214d18( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00214d18( void){
  long v1;
  rt16 v2;
  
  v2 = rt_00349ef4();
  rt_00349748(v2.lo,v2.hi,*(uint64_t *)(v2.hi + 0x10));
  rt_00377824();
  rt_00349530();
  (**(code **)(v1 + 0x10))();
  rt_0034edc8();
  ((code)FUN_00214d80)();
  return;
}



/* FUN_00214d80 @ 0x00214d80   (est. swift_runloop_call)
 * Ghidra: void FUN_00214d80(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00214d80(uint64_t param_1, uint64_t param_2, uint64_t param_3){
  uint64_t v7;
  unsigned long v8;
  code *v5;
  code *v2;
  code *v3;
  code *v1;
  uint64_t v17;
  long v19;
  code *v15;
  code *v11;
  code *v13;
  code *v10;
  code *v12;
  code *v18;
  code *v14;
  code *v4;
  long v16;
  long v22;
  long v21;
  uint64_t v23;
  code *v6;
  uint64_t v9;
  uint64_t v20;
  rt16 av70;
  uint64_t v24;
  
  rt_0008e518();
  rt_0034e73c();
  rt_00350bd8();
  v9 = *(uint64_t *)(v22 + 0x10);
  av70 = rt_003497a0();
  v9 = rt_00377824(av70.lo,av70.hi,v9).lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aa9c();
  rt_0034c108();
  rt_00350210();
  rt_00377824();
  rt_00348e18();
  (*G_00658c00)(*(uint64_t *)(v19 + 0x40));
  rt_00348a34();
  (*G_00658c00)();
  rt_0034b8bc();
  rt_00351d0c();
  rt_00350624();
  (*v18)();
  rt_00310924(param_3);
  rt_00351184();
  rt_0035084c();
  (*v14)();
  rt_00350b78();
  rt_00351238();
  v7 = rt_00377bec().lo;
  rt_00351bec();
  rt_00350adc();
  rt_003516e4();
  rt_00350ac4();
  v8 = (*v15)();
  v6 = *(code **)(v16 + 8);
  rt_003509d4();
  (*v6)();
  if ((v8 & 1) != 0) {
    rt_00350410();
    rt_003488bc();
    rt_0034c220();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  (*v6)(v21);
  v5 = (code *)rt_00027818(param_3);
  v2 = (code *)rt_00310924(param_3);
  rt_00027754(v7);
  v3 = (code *)rt_0014ae44();
  do {
    rt_00352b2c();
    rt_00351420();
    (*v5)();
    rt_003545a0();
    rt_0035084c();
    (*v2)();
    rt_00351414();
    rt_00350ac4();
    v8 = (*v3)();
    rt_00350524();
    (*v6)();
    if ((v8 & 1) != 0) break;
    v4 = *(code **)(v21 + *(int *)(v22 + 0x24));
    v7 = rt_00351b84(param_3);
    rt_00354370(v7,v23);
    v1 = (code *)(*v11)();
    rt_0035457c();
    (*v13)(v24,v17,v9);
    rt_0034cfa4();
    (*v1)();
    v8 = (*v4)(v24);
    rt_00354f8c();
    (*v10)(v24,v9);
  } while ((v8 & 1) == 0);
  rt_00351298(*(uint64_t *)(v16 + 0x20),v21);
  (*v12)();
  rt_0008e500(v20);
  return;
}



/* FUN_002152b8 @ 0x002152b8   (est. swift_init_if_fail)
 * Ghidra: void FUN_002152b8(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002152b8(uint64_t param_1, uint64_t param_2, uint64_t param_3){
  long v2;
  uint64_t v3;
  long v10;
  code *v7;
  code *v9;
  code *v6;
  code *v5;
  long v8;
  long v4;
  code *v1;
  uint64_t v11;
  
  v2 = rt_0008e518().lo;
  rt_00349748();
  rt_00354394();
  rt_00377824();
  rt_00348ce8();
  (*G_00658c00)(*(uint64_t *)(v10 + 0x40));
  rt_00348abc();
  (*G_00658c00)();
  rt_0034b87c();
  rt_00350488();
  rt_00310d68();
  rt_00348cd0();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b2f8();
  if (v2 < 0) {
    rt_00350704();
    rt_00084180();
    (*v9)();
    rt_000277b8(param_3);
    v3 = rt_0034e72c();
    (*v6)(v3,param_3);
    rt_003192d8(param_3);
    rt_0035133c();
    rt_00354d68();
    rt_00352450();
    (*v5)();
    v1 = *(code **)(v8 + 8);
    rt_00350630();
    (*v1)();
    rt_0035084c();
    (*v1)();
    rt_003518b8(*(uint64_t *)(v4 + 8));
    (*v7)();
  }
  rt_0008e500(v11);
  return;
}



/* FUN_00215428 @ 0x00215428   (est. swift_neg_loop_call)
 * Ghidra: void FUN_00215428( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00215428( void){
  long v2;
  bool v6;
  uint64_t v5;
  uint64_t v8;
  unsigned long v7;
  uint64_t v3;
  uint64_t v14;
  long v12;
  code *v10;
  code *v9;
  long v11;
  long v4;
  code *v1;
  rt16 v15;
  uint64_t v13;
  
  v15 = rt_0008e518();
  v3 = (uint64_t)v15.hi;
  rt_00349748();
  rt_00350b84();
  rt_00377824();
  rt_00348d64();
  (*G_00658c00)(*(uint64_t *)(v12 + 0x40));
  rt_00348abc();
  (*G_00658c00)();
  rt_0034b87c();
  rt_00310cd4(v14);
  v5 = rt_00350a88();
  rt_00351f1c(v5,v3);
  (*v10)();
  rt_00350b48(v14);
  v5 = rt_00377bec().lo;
  rt_00310b08();
  v8 = rt_00350a88();
  rt_00350bfc(v8,v3);
  v7 = (*v9)();
  v1 = *(code **)(v11 + 0x10);
  v6 = (v7 & 1) == 0;
  if (v6) {
    v3 = (uint64_t)v15.lo;
  }
  v2 = 1;
  if (!v6) {
    v2 = -1;
  }
  rt_00358df4(v7,v3);
  (*v1)();
  rt_00350ed0();
  (*v1)();
  rt_00352894(v5);
  v1 = (code *)rt_0014ae44();
  rt_000a6e14();
  rt_00350bfc();
  v7 = (*v1)();
  if ((v7 & 1) == 0) {
    v4 = 0;
    do {
      if (SCARRY8(v4,v2)) {
                    /* WARNING: Does not return */
        v1 = (code *)SW_BREAK(0x215600);
        (*v1)();
      }
      ((code)FUN_00214d80)();
      rt_000a6e14();
      rt_00350bfc();
      v7 = (*v1)();
      v4 = v4 + v2;
    } while ((v7 & 1) == 0);
  }
  v1 = *(code **)(v11 + 8);
  rt_00351274();
  (*v1)();
  rt_000e72b0();
  (*v1)();
  v3 = rt_0035a3d0();
  rt_0008e500(v3,v13);
  return;
}



/* FUN_00215600 @ 0x00215600   (est. swift_pos_loop_call)
 * Ghidra: void FUN_00215600( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00215600( void){
  code *v4;
  bool v10;
  uint64_t v8;
  uint64_t v12;
  uint64_t v11;
  code *v5;
  code *v7;
  unsigned long v9;
  code *v1;
  uint64_t v22;
  uint64_t v30;
  uint64_t v24;
  long v19;
  code *v15;
  code *v17;
  code *v13;
  code *v16;
  code *v20;
  code *v23;
  code *v18;
  code *v14;
  long v2;
  long v21;
  long v27;
  uint64_t v26;
  long v25;
  long v6;
  uint64_t v3;
  uint64_t v29;
  uint64_t v28;
  rt16 v32;
  rt16 v33;
  uint64_t v31;
  
  rt_0008e518();
  v32 = rt_0035199c();
  v6 = (uint64_t)v32.hi;
  rt_00350bd8(v30);
  v3 = *(uint64_t *)(v25 + 0x10);
  v33 = rt_003497a0();
  v8 = rt_00377824(v33.lo,v33.hi,v3).lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034a2ac();
  rt_00349748();
  rt_003514dc();
  rt_00377824();
  rt_00348d64();
  (*G_00658c00)(*(uint64_t *)(v19 + 0x40));
  rt_003490d0();
  (*G_00658c00)();
  rt_0034b4c0();
  rt_00350500();
  v12 = rt_00310d68().lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aee4();
  (**(code **)(v21 + 0x10))(v24,v32.lo);
  if (v6 >> 0x3f < 0) {
    rt_00310924();
    rt_00351184();
    rt_003508a8();
    (*v23)();
    rt_003506e8();
    rt_003508a8();
    (*v18)();
    rt_003192d8();
    rt_0034e71c();
    rt_00350c08();
    (*v14)();
    v5 = *(code **)(v21 + 8);
    rt_000e15d8();
    (*v5)();
    rt_00351414();
    (*v5)();
    v11 = rt_0035152c();
    (*v15)(v11,v12);
    v10 = SBORROW8(0,v6);
    v6 = -v6;
    if (v10) {
                    /* WARNING: Does not return */
      v5 = (code *)SW_BREAK(0x2159c4);
      (*v5)();
    }
    if (v6 < 0) {
      rt_00347d60();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
  }
  else if (v6 == 0) goto LBL_00215998;
  v2 = 0;
  do {
    v2 = v2 + 1;
    v5 = (code *)rt_00310924(v26);
    rt_0034c3c4();
    rt_00350b48(v26);
    rt_00377bec();
    rt_00027754();
    v7 = (code *)rt_0014ae44();
    do {
      rt_0035084c();
      rt_003528ac();
      rt_001d30f8();
      rt_003507bc(v29);
      (*v5)();
      rt_00350ea4();
      rt_003516b4();
      v9 = (*v7)();
      rt_00351414(*(uint64_t *)(v21 + 8));
      (*v17)();
      if ((v9 & 1) != 0) break;
      v4 = *(code **)(v27 + *(int *)(v25 + 0x24));
      v12 = rt_00351b84(v26);
      v1 = (code *)(*v13)(v12,v24,v3,v26);
      rt_00354ab0();
      (*v16)(v31,v22,v8);
      rt_0034cfa4();
      (*v1)();
      rt_00355af8();
      v9 = (*v4)();
      v12 = rt_00352bc8();
      (*v20)(v12,v8);
    } while ((v9 & 1) == 0);
  } while (v2 != v6);
LBL_00215998:
  rt_0008e500(v28);
  return;
}



/* FUN_002159d4 @ 0x002159d4   (est. swift_dispatch2)
 * Ghidra: void FUN_002159d4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002159d4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4){
  uint64_t v1;
  long v4;
  unsigned long v2;
  long v18;
  uint64_t v20;
  long v15;
  long v9;
  code *v12;
  code *v7;
  code *v10;
  code *v16;
  code *v19;
  code *v13;
  code *v8;
  code *v14;
  code *v11;
  long v17;
  long v6;
  long v3;
  long v5;
  uint64_t v21;
  rt16 v28;
  uint64_t v26;
  long v24;
  uint64_t v23;
  uint64_t v25;
  long v22;
  uint64_t v27;
  
  rt_0008e518();
  v23 = param_3;
  v25 = v20;
  v27 = rt_00349b3c();
  v5 = *(long *)(v15 + 0x40);
  v22 = v17;
  (*G_00658c00)();
  v24 = (long)&v26 - (v5 + 0xfU & 0xfffffffffffffff0);
  v26 = param_4;
  rt_00350950(param_4);
  rt_0008f6f4();
  rt_00349dfc();
  rt_00351554();
  v1 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b2f8();
  rt_0034bec4();
  rt_00377824();
  rt_00348d4c();
  v3 = *(long *)(v9 + 0x40);
  (*G_00658c00)(v3 + 0xfU & 0xfffffffffffffff0);
  v4 = rt_0034b05c();
  if (v18 == v4) {
    rt_000a6b64();
    rt_00350b30();
    rt_003507e0();
    (*v11)();
    if (v3 != v5) {
      rt_00347e28();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
    rt_003508c0(*(uint64_t *)(v22 + 0x10),v25);
    (*v7)();
    rt_00350618(*(uint64_t *)(v6 + 8));
    (*v10)();
  }
  else {
    rt_0034ad00();
    v28 = rt_003508cc();
    rt_00377bec(v28.lo,v28.hi,v1);
    rt_00349370();
    rt_0034c234();
    (*v19)();
    rt_0034d970();
    rt_00351a2c();
    rt_0034daf8();
    (*v13)();
    rt_00356b20();
    rt_0035044c();
    rt_003559d8();
    rt_0034e014();
    v2 = (*v12)();
    rt_00352870();
    rt_003514e8();
    (*v8)();
    if ((v2 & 1) == 0) {
      rt_003504a0(*(uint64_t *)(v22 + 0x10),v25);
      (*v16)();
    }
    else {
      rt_0031bc70(v26);
      rt_0034f3a4(v25);
      (*v14)();
    }
  }
  rt_0008e500(v21);
  return;
}



/* FUN_00215cd0 @ 0x00215cd0   (est. swift_loop_dispatch)
 * Ghidra: void FUN_00215cd0(uint64_t param_1, uint64_t param_2, uint64_t param_3, long param_4, uint64_t param_5)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00215cd0(uint64_t param_1, uint64_t param_2, uint64_t param_3, long param_4, uint64_t param_5){
  bool v8;
  code *v6;
  bool v9;
  uint64_t v12;
  uint64_t v11;
  uint64_t v7;
  unsigned long v10;
  code *v2;
  code *v1;
  uint64_t v26;
  uint64_t v28;
  long v21;
  code *v16;
  code *v18;
  code *v14;
  code *v17;
  code *v22;
  code *v23;
  code *v24;
  code *v27;
  unsigned long v3;
  code *v19;
  code *v15;
  code *v20;
  long v25;
  long v13;
  uint64_t v4;
  long v5;
  long v31;
  uint64_t v34;
  uint64_t v29;
  long v30;
  uint64_t v33;
  uint64_t v32;
  rt16 v37;
  uint64_t v35;
  uint64_t v36;
  
  rt_0008e518();
  v12 = param_5;
  rt_00359de8();
  rt_00350bd8(v12);
  v4 = *(uint64_t *)(param_4 + 0x10);
  v37 = rt_003497a0();
  v12 = rt_00377824(v37.lo,v37.hi,v4).lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aa9c();
  rt_0034a944();
  rt_0035056c();
  rt_00377824();
  rt_0034e57c();
  rt_00310d68();
  v11 = rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034a760();
  rt_00349c70();
  (*G_00658c00)(*(uint64_t *)(v21 + 0x40));
  rt_00348bbc();
  (*G_00658c00)();
  rt_0034a464();
  (*G_00658c00)();
  rt_0034b4c0();
  rt_003534bc();
  rt_00351e90();
  (*v27)();
  v8 = 0 < v30;
  v3 = v30 >> 0x3f;
  if ((long)v3 < 0) {
    rt_00310924(param_5);
    rt_00350b24();
    rt_0034e50c();
    (*v19)();
    rt_0034f1e0();
    rt_003504ac();
    (*v15)();
    rt_003192d8(param_5);
    rt_0035322c();
    rt_003500f4();
    (*v20)();
    v2 = *(code **)(v13 + 8);
    rt_003507c8();
    (*v2)();
    rt_000a6e14();
    (*v2)();
    (**(code **)(v25 + 8))(v36,v11);
    v9 = SBORROW8(0,v30);
    v30 = -v30;
    if (v9) {
                    /* WARNING: Does not return */
      v2 = (code *)SW_BREAK(0x216114);
      (*v2)();
    }
    if (v30 < 0) {
      rt_00347d60();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
  }
  else if (v30 == 0) goto LBL_00216098;
  rt_0034c3c4();
  rt_00350b78();
  v11 = rt_00377bec().lo;
  v5 = 0;
  do {
    rt_00351ef8(v11);
    rt_0014ae44();
    v7 = rt_00350a7c();
    rt_00351c94(v7,param_3);
    v10 = (*v16)();
    if ((v10 & 1) != 0) {
      rt_00353bf4();
      rt_00350b3c();
      (*v24)();
      v12 = 1;
      goto LBL_002160d8;
    }
    v5 = v5 + 1;
    v2 = (code *)rt_00310924(param_5);
    do {
      rt_00354370(v33,v8 | v3);
      rt_001d30f8();
      rt_0035084c(v29);
      (*v2)();
      rt_00351414();
      rt_00351c94();
      v10 = (*v16)();
      rt_00353bf4();
      rt_003507c8();
      (*v18)();
      if ((v10 & 1) != 0) break;
      v6 = *(code **)(v31 + *(int *)(param_4 + 0x24));
      rt_00352ecc(param_5);
      v37 = rt_00355634();
      v1 = (code *)(*v14)(v37.lo,v37.hi,v4,param_5);
      rt_0035457c();
      (*v17)(v35,v26,v12);
      rt_0034c3b4();
      (*v1)();
      v10 = (*v6)(v35);
      rt_00354f8c();
      (*v22)(v35,v12);
    } while ((v10 & 1) == 0);
  } while (v5 != v30);
LBL_00216098:
  v37 = rt_00351324(*(uint64_t *)(v13 + 0x20));
  (*v23)(v37.lo,v37.hi,v34);
  v12 = 0;
LBL_002160d8:
  rt_000839d8(v28,v12,1,v34);
  rt_0008e500(v32);
  return;
}



/* FUN_00216114 @ 0x00216114   (est. swift_init_dispatch)
 * Ghidra: void FUN_00216114( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216114( void){
  uint32_t v3;
  int v2;
  uint64_t v8;
  uint64_t v5;
  long v13;
  uint64_t v12;
  code *v10;
  code *v6;
  code *v9;
  long v7;
  long v4;
  code *v1;
  uint64_t v11;
  
  rt_0008e518();
  v3 = rt_00357a34();
  v3 = rt_0034a944(v3,v5,*(uint64_t *)(v13 + 0x10));
  rt_00377824(v3,v12);
  rt_0034ee68();
  rt_00310d68();
  rt_00348d4c();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034cff4();
  rt_003499f0();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0d4();
  v3 = rt_00353c18();
  rt_00352e60(v3,v8);
  ((code)FUN_00215cd0)();
  rt_00356224();
  rt_003504ac();
  (*v9)();
  rt_003524b0();
  v2 = rt_0035681c();
  if (v2 == 1) {
    rt_00350c2c(*(uint64_t *)(v7 + 8));
    (*v10)();
    rt_00355d28(*(uint64_t *)(v4 + 0x10));
    (*v6)();
  }
  else {
    v1 = *(code **)(v4 + 0x20);
    rt_003508a8();
    (*v1)();
    rt_0035100c();
    (*v1)();
  }
  v3 = rt_00357fd4();
  rt_0008e500(v3,v11);
  return;
}



/* FUN_00216284 @ 0x00216284   (est. swift_vtable_cleanup)
 * Ghidra: void FUN_00216284( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216284( void){
  uint64_t v1;
  code *v2;
  long v4;
  long v3;
  uint64_t v5;
  
  rt_0008e518();
  rt_0034b318();
  rt_00350a64();
  rt_00351aec();
  rt_00377824();
  rt_0034a450();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0d4();
  rt_00319628();
  rt_0035102c();
  rt_0034ede8();
  (*v2)();
  v1 = *(uint64_t *)(v4 + *(int *)(v3 + 0x24) + 8);
  rt_00350c2c();
  rt_00352ea8();
  rt_00377bec();
  rt_00027754();
  rt_003547f8();
  rt_000dbe70();
  ((code)FUN_0021476c)();
  rt_0036b270(v1);
  rt_0008e500(v5);
  return;
}



/* FUN_00216354 @ 0x00216354   (est. swift_try_call3)
 * Ghidra: void FUN_00216354(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216354(uint64_t param_1, uint64_t param_2, uint64_t param_3){
  code *UNRECOVERED_JUMPTABLE;
  uint64_t v1;
  long v2;
  long v3;
  long v4;
  rt16 v5;
  
  rt_00351a68();
  v5 = rt16_mklo((**(code **)(v3 + *(int *)(v2 + 0x24)))());
  if ((v5.lo & 1) != 0) {
    UNRECOVERED_JUMPTABLE = (code *)rt_0031b110(param_3);
    v5 = rt_00356248(UNRECOVERED_JUMPTABLE,*(uint64_t *)(v4 + 0x10));
                    /* WARNING: Could not recover jumptable at 0x002163c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(v5.lo,v5.hi,param_3);
    return;
  }
  v1 = rt_00349748(v5.lo,v5.hi,*(uint64_t *)(v4 + 0x10));
  rt_00377824(v1,param_3);
  rt_0034c6c4();
  rt_000839d8();
  rt_00350798();
  rt_00356e34();
  rt_0034ba48();
  rt_000839d8();
  return;
}



/* FUN_00216418 @ 0x00216418   (est. swift_box_alloc)
 * Ghidra: void * FUN_00216418(long * param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void * FUN_00216418(long * param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4){
  long v1;
  uint64_t v2;
  
  v1 = rt_0036a908(0x28,0xb433);
  *param_1 = v1;
  v2 = FUN_00216498((long*)v1,param_2,param_3,*(uint64_t *)((param_4 & 0xfffffffffffffffe) - 8)).lo;
  *(uint64_t *)(v1 + 0x20) = v2;
  return &G_003471a4;
}



/* FUN_00216498 @ 0x00216498   (est. swift_box_init)
 * Ghidra: rt16 FUN_00216498(long * param_1, uint64_t param_2, long param_3, uint64_t param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
rt16 FUN_00216498(long * param_1, uint64_t param_2, long param_3, uint64_t param_4){
  uint64_t v1;
  long v2;
  rt16 v3;
  
  v1 = rt_00027754(param_4);
  v2 = rt_00377824(0,v1,*(uint64_t *)(param_3 + 0x10),&G_00611b24,&LBL_00611b34).lo;
  *param_1 = v2;
  v2 = *(long *)(v2 + -8);
  param_1[1] = v2;
  v2 = rt_0036a908(*(uint64_t *)(v2 + 0x40),0x59d5);
  param_1[2] = v2;
  rt_00250904(v2,param_2,param_3,param_4);
  v3.hi = v2;
  v3.lo = (uint64_t)&G_003471a8;
  return v3;
}



/* FUN_002165c0 @ 0x002165c0   (est. swift_vtable_call3)
 * Ghidra: void FUN_002165c0(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002165c0(uint64_t param_1, uint64_t param_2, uint64_t param_3){
  long v1;
  long v2;
  rt16 v3;
  
  rt_00349ef4();
  v3 = rt_00350bd8(param_3);
  rt_00349748(v3.lo,v3.hi,*(uint64_t *)(v2 + 0x10));
  rt_00377824();
  rt_00349530();
  (**(code **)(v1 + 0x10))();
  rt_0034edc8();
  ((code)FUN_0021662c)();
  return;
}



/* FUN_0021662c @ 0x0021662c   (est. swift_loop_dispatch2)
 * Ghidra: void FUN_0021662c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021662c(uint64_t param_1, uint64_t param_2, uint64_t param_3){
  code *v1;
  unsigned long v5;
  code *v4;
  code *v2;
  code *v3;
  long v15;
  code *v12;
  code *v9;
  code *v11;
  long v8;
  code *v10;
  code *v14;
  long v13;
  long v7;
  uint64_t v17;
  long v19;
  long v18;
  uint64_t v16;
  uint64_t v6;
  uint64_t v20;
  rt16 v21;
  uint8_t v22 [32];
  
  rt_0008e518();
  rt_00351a38();
  rt_0035125c(param_3);
  rt_00350bd8();
  v6 = *(uint64_t *)(v18 + 0x10);
  v21 = rt_003497a0();
  rt_00377824(v21.lo,v21.hi,v6);
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aee4();
  rt_00349748();
  rt_003505c4();
  rt_00377824();
  rt_00348d7c();
  (*G_00658c00)(*(uint64_t *)(v15 + 0x40));
  rt_003489c0();
  (*G_00658c00)();
  rt_0034c074();
  rt_00350c8c(*(uint64_t *)(v7 + 0x20));
  (*v12)();
  rt_0034f1e0();
  rt_003504c4();
  (*v14)();
  rt_0034c3c4();
  rt_000e15d8();
  rt_00377bec();
  rt_0034c4fc();
  rt_0035190c();
  rt_00350cb4();
  v5 = (*v9)();
  rt_003508f0(*(uint64_t *)(v7 + 8));
  (*v11)();
  if ((v5 & 1) == 0) {
    v4 = (code *)rt_003196e8(param_3);
    rt_0035a1b4();
    v1 = *(code **)(v19 + v8);
    v2 = (code *)rt_000277e8(v16);
    do {
      (*v4)();
      rt_003513a8(v22);
      v3 = (code *)(*v2)();
      (**(code **)(v13 + 0x10))();
      rt_0034cfa4();
      (*v3)();
      v5 = (*v1)();
      rt_00100c38(*(uint64_t *)(v13 + 8));
      (*v10)();
    } while ((v5 & 1) == 0);
    (*v12)((unsigned long)(v7 + 0x20) & 0xffffffffffff | 0x48d8000000000000,
                      v17);
    rt_0008e500(v20);
    return;
  }
  rt_00350410();
  rt_003488bc();
  rt_0034b9e8();
  rt_0035343c();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}



/* FUN_00216900 @ 0x00216900   (est. swift_enable2)
 * Ghidra: void FUN_00216900( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216900( void){
  code *v1;
  code *v3;
  long v2;
  uint64_t v4;
  
  v1 = FUN_0021476c;
  rt_0008e518();
  rt_00358da0();
  rt_0034ba18();
  rt_003516cc();
  rt_00377824();
  rt_00349e10();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  rt_000a68c4();
  rt_00351184();
  rt_000dbd0c();
  (*v3)();
  rt_0034d140();
  (**(code **)(v2 + 8))();
  rt_00350618();
  rt_00351f40();
  rt_00377bec();
  rt_00077894();
  (*v1)();
  rt_0036b270();
  rt_0008e500(v4);
  return;
}



/* FUN_00216a00 @ 0x00216a00   (est. swift_stack_box)
 * Ghidra: void FUN_00216a00(uint64_t param_1, uint64_t param_2, long param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216a00(uint64_t param_1, uint64_t param_2, long param_3){
  long v2;
  uint64_t v14;
  long v11;
  long v10;
  code *v9;
  unsigned long v3;
  long v12;
  long v13;
  unsigned long v6;
  code *v1;
  unsigned long v8;
  uint64_t v4;
  long v5;
  uint64_t v7;
  uint64_t v15;
  rt16 v17;
  rt16 v16;
  
  v17 = rt_0008e518();
  v2 = param_3;
  rt_00349720();
  v5 = *(long *)(v11 + 0x40);
  (*G_00658c00)();
  v4 = *(uint64_t *)(v2 + 0x10);
  rt_003499c8();
  (*G_00658c00)(*(uint64_t *)(v10 + 0x40));
  rt_0034947c();
  rt_00351494(*(uint64_t *)(v12 + 0x10));
  (*v9)();
  v1 = *(code **)(v13 + 0x20);
  v16 = rt_00350738();
  (*v1)(v16.lo,v16.hi,param_3);
  v3 = (unsigned long)*(uint8_t *)(v13 + 0x50);
  v8 = v3 + 0x20 & (v3 ^ 0xffffffffffffffff);
  v6 = v5 + v8 + 7 & 0xfffffffffffffff8;
  v2 = rt_0036a940(0x66aa88,v6 + 0x10,v3 | 7).lo;
  v7 = *(uint64_t *)(param_3 + 0x18);
  *(uint64_t *)(v2 + 0x10) = v4;
  *(uint64_t *)(v2 + 0x18) = v7;
  rt_00350c08(v2 + v8);
  (*v1)();
  *(rt16*)(v2 + v6) = v17;
  rt_003529b0(v14);
  ((code)FUN_0021476c)();
  rt_0036b270(v17.hi);
  rt_0008e500(v15);
  return;
}



/* FUN_00216b88 @ 0x00216b88   (est. swift_dispatch3)
 * Ghidra: void FUN_00216b88( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216b88( void){
  uint64_t v1;
  uint64_t v3;
  uint64_t v2;
  rt16 v4;
  
  rt_0008e518();
  rt_0034d2b4();
  rt_00353e50();
  rt_00351930();
  v1 = rt_00377824().lo;
  rt_00351160();
  rt_00351dcc();
  rt_00377bec();
  rt_0035113c();
  rt_00319338();
  rt_00349e10();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  rt_000a6e14(v1);
  rt_0034ef08();
  v1 = rt_001f1878();
  v4 = rt_0035319c(v1,0x66cc38);
  ((code)FUN_00216c60)(v4.lo,v4.hi,v3);
  rt_0008e500(v2);
  return;
}



/* FUN_00216c60 @ 0x00216c60   (est. swift_cleanup_dispatch)
 * Ghidra: void FUN_00216c60( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216c60( void){
  uint64_t v1;
  uint64_t v6;
  code *v8;
  code *v4;
  code *v7;
  long v5;
  long v3;
  long v2;
  uint64_t v9;
  rt16 v10;
  
  rt_0008e518();
  rt_00353b10();
  rt_003512f4();
  rt_00377824();
  rt_00348ce8();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b05c();
  rt_0034e52c();
  v10 = rt_00377bec();
  rt_00350488(v10.lo,v10.hi,v10.lo);
  rt_0031be18();
  rt_00348e60();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  rt_000a68c4(v6);
  v1 = rt_0034e72c();
  (*v7)(v1,v6);
  rt_0034b3c8();
  (**(code **)(v2 + 8))();
  rt_00350b3c(*(uint64_t *)(v5 + 0x20));
  (*v8)();
  rt_00354d74();
  rt_00200b38();
  rt_00350ab8(*(uint64_t *)(v3 + 8));
  (*v4)();
  rt_0008e500(v9);
  return;
}



/* FUN_00216dbc @ 0x00216dbc   (est. swift_closure_alloc2)
 * Ghidra: void FUN_00216dbc(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216dbc(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5){
  uint64_t v1;
  long v2;
  uint64_t v5;
  uint64_t v6;
  code *v3;
  long v4;
  uint64_t v9;
  uint64_t v8;
  uint64_t v7;
  rt16 v10;
  
  rt_0008e518();
  rt_00355bb8();
  rt_00351930();
  rt_00377824();
  rt_003542b8();
  rt_00310d68();
  rt_0034d868();
  rt_00377bec();
  rt_0034d8f4();
  rt_00319338();
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0d4();
  rt_0034e2e4();
  rt_00350530();
  rt_0031bc40();
  rt_00348d4c();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  v1 = rt_00353a84();
  rt_00353960(v1,v5);
  rt_001f1878();
  rt_00359018(0x66aab0);
  v10 = rt_0036a940();
  v2 = (uint64_t)v10.lo;
  *(uint64_t *)(v2 + 0x10) = v8;
  *(uint64_t *)(v2 + 0x18) = v9;
  *(uint64_t *)(v2 + 0x20) = param_5;
  rt_00351720(rt_0031be30,v10.hi,param_3,0x66cc38);
  ((code)FUN_00216900)();
  rt_0036b118(v2);
  rt_00359018(0x66aad8);
  v2 = rt_0036a940().lo;
  *(uint64_t *)(v2 + 0x10) = v8;
  *(uint64_t *)(v2 + 0x18) = v9;
  *(uint64_t *)(v2 + 0x20) = param_5;
  rt_0034dbb8(v6,&G_0031be54);
  rt_001f1878();
  rt_0036b118(v2);
  rt_00350c38(*(uint64_t *)(v4 + 8));
  (*v3)();
  rt_0008e500(v7);
  return;
}



/* FUN_00216f9c @ 0x00216f9c   (est. swift_fatal_unwrap)
 * Ghidra: void FUN_00216f9c(uint64_t param_1, uint64_t param_2, uint64_t param_3, long param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216f9c(uint64_t param_1, uint64_t param_2, uint64_t param_3, long param_4){
  uint8_t stack_base[512];
  uint8_t *stack_ptr = stack_base;

  int v3;
  long v2;
  long v5;
  long v4;
  uint8_t *v1;
  rt16 v6;
  uint8_t v7 [8];
  uint64_t uStack_48;
  uint32_t v8 [4];
  
  v6 = rt_00310d68(0,param_4);
  v2 = (uint64_t)v6.lo;
  (*G_00658c00)(*(long *)(*(long *)(v2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0,v2,
                  v6.hi,v2);
  v2 = -v5;
  v1 = &stack_ptr + v2;
  (**(code **)(v4 + 0x10))(v1,param_2);
  v3 = rt_000839f8(v1,1,param_4);
  if (v3 != 1) {
    (**(code **)(*(long *)(param_4 + -8) + 0x20))(param_1,v1,param_4);
    return;
  }
  *(uint32_t *)((long)v8 + v2) = 1;
  *(uint64_t *)((long)&uStack_48 + v2) = 0x31;
  v7[v2] = 2;
                    /* WARNING: Subroutine does not return */
  rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Unexpectedly_found_nil_while_unw_005cd7d0,0x39,2,
               s_Swift_FlatMap_swift_005d3ba0,0x13);
}



/* FUN_00217100 @ 0x00217100   (est. swift_dispatch4)
 * Ghidra: void FUN_00217100( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00217100( void){
  int v2;
  long v1;
  long v3;
  long v4;
  rt16 v5;
  
  rt_00084220();
  rt_0034c2e8();
  rt_0034ed08();
  v1 = rt_0031be60();
  v2 = *(int *)(v1 + 0x2c);
  rt_00355780();
  rt_0034be0c();
  v5 = rt_00377824();
  rt_0034e6dc(v5.lo,v5.hi,v5.lo);
  rt_00377824();
  rt_00350744(v4 + v2);
  rt_000839d8();
  rt_0034ac8c();
  rt_00377824();
  rt_00350404();
                    /* WARNING: Could not recover jumptable at 0x002171a4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(v3 + 0x20))();
  return;
}



/* FUN_002171a8 @ 0x002171a8   (est. swift_string_index_next)
 * Ghidra: uint32_t FUN_002171a8( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_002171a8( void){
  uint8_t v17;
  uint16_t v12;
  uint32_t v14;
  long v15;
  unsigned long v18;
  char *v6;
  uint64_t v16;
  int v11;
  unsigned long v13;
  unsigned long v7;
  uint8_t *v1;
  uint8_t *v2;
  unsigned long *v19;
  unsigned long v8;
  unsigned long v10;
  unsigned long v5;
  unsigned long v9;
  uint32_t v3;
  rt16 v22;
  rt16 v23;
  uint64_t v4;
  unsigned long v21;
  unsigned long uStack_78;
  unsigned long v20;
  unsigned long uStack_68;
  
  v8 = v19[7];
  do {
    if (v8 != 0) {
      v10 = v19[6];
      v5 = v10 & 0xffffffffffff;
      if ((v8 & 0x2000000000000000) != 0) {
        v5 = v8 >> 0x38 & 0xf;
      }
      v9 = v19[8];
      if (v9 >> 0xe != v5 * 4) {
        v14 = (uint32_t)(v10 >> 0x3b) & 1;
        if ((v8 & 0x1000000000000000) == 0) {
          v14 = 1;
        }
        v18 = v9;
        if ((v9 & 0xc) == 4L << (unsigned long)v14) {
          v18 = rt_0001da84(v9,v10,v8);
        }
        v7 = v18 >> 0x10;
        if (v5 <= v7) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                       s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
        }
        if ((v8 >> 0x3c & 1) == 0) {
          if ((v8 >> 0x3d & 1) == 0) {
            if ((v10 >> 0x3c & 1) == 0) goto LBL_00217720;
            v15 = (v8 & 0xfffffffffffffff) + 0x20;
            goto LBL_0021758c;
          }
          v20 = v10;
          uStack_68 = v8 & 0xffffffffffffff;
          v17 = *(uint8_t *)((long)&v20 + v7);
        }
        else {
          rt_002b141c(v18,v10,v8);
LBL_00217720:
          v15 = rt_002a9ba8(v10,v8).lo;
LBL_0021758c:
          v17 = *(uint8_t *)(v15 + v7);
        }
        v3 = (uint32_t)v17;
        if ((v9 & 0xc) == 4L << (unsigned long)v14) {
          v9 = rt_0001da84(v9,v10,v8);
        }
        v11 = 0;
        v19[8] = (unsigned long)(&G_00010004 + (v9 & 0xffffffffffff0000));
        goto LBL_002175d4;
      }
    }
    v8 = v19[2];
    if ((long)v19[3] <= (long)v8) {
      v3 = 0;
      v11 = 1;
LBL_002175d4:
      return v3 | v11 << 8;
    }
    v5 = *v19;
    v10 = v19[1];
    v9 = v10 >> 0x38 & 0xf;
    if ((v10 >> 0x3c & 1) == 0) {
      if ((v10 >> 0x3d & 1) == 0) {
        if ((v5 >> 0x3c & 1) == 0) {
          v22 = rt_002a9ba8(v5,v10);
        }
        else {
          v22.hi = v5 & 0xffffffffffff;
          v22.lo = (v10 & 0xfffffffffffffff) + 0x20;
        }
        v18 = v8 + 1;
        if (v18 != v22.hi) {
          if (v22.lo == 0) {
                    /* WARNING: Subroutine does not return */
            rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_unsafelyUnwrapped_of_nil_optiona_005ce1c0,
                         0x21,2,s_Swift_Optional_swift_005ce1f0,0x14,2,0x179,1);
          }
          v12 = *(uint16_t *)(v22.lo + v8);
LBL_00217268:
          v18 = v8 + 1;
          if (v12 == 0xa0d || (v12 & 0x8080) != 0) goto LBL_0021749c;
        }
      }
      else {
        v20 = v5;
        uStack_68 = v10 & 0xffffffffffffff;
        v18 = v8 + 1;
        if (v18 != v9) {
          v12 = *(uint16_t *)((long)&v20 + v8);
          goto LBL_00217268;
        }
      }
    }
    else {
LBL_0021749c:
      v15 = rt_002c6d00(v8,v5,v10);
      if ((v10 >> 0x3c & 1) != 0) {
        rt_002bbcd8();
LBL_00217734:
        v4 = 0x584;
        v6 = s_UnsafeBufferPointer_has_a_nil_st_005cf020;
        v16 = 0x35;
LBL_002176c0:
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v6,v16,2,
                     s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,v4,1);
      }
      v18 = v15 + v8;
      if ((long)v18 < (long)v8) {
        v4 = 0x2f9;
        v6 = s_Range_requires_lowerBound_005cda00;
        v16 = 0x27;
        goto LBL_0021752c;
      }
    }
    if ((v10 >> 0x3d & 1) != 0) {
      uStack_68 = v10 & 0xffffffffffffff;
      v20 = v5;
      if ((long)v8 < 0) {
LBL_002174e0:
        v4 = 0x7a8;
      }
      else {
        if ((long)v18 <= (long)v9) {
          v5 = v18 - v8;
          if (-1 < (long)v5) {
            v1 = (uint8_t *)((long)&v20 + v8);
            v14 = rt_002a200c(v1,v5);
            if (v18 - v8 == 0) {
LBL_00217388:
              v13 = 0;
              v10 = 0xe000000000000000;
              goto LBL_0021745c;
            }
            if (0xf < v5) goto LBL_00217420;
            v9 = v5 - 8;
            v10 = v5;
            if (7 < v5) {
              v10 = 8;
            }
            v7 = v5;
            if (v10 - 1 <= v5) {
              v7 = v10 - 1;
            }
            if (v10 == v7) {
LBL_002174f0:
              v4 = 0x136;
              v6 = s_Index_out_of_range_005cd940;
              v16 = 0x12;
LBL_0021752c:
                    /* WARNING: Subroutine does not return */
              rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v6,v16,2,s_Swift_Range_swift_005cda30,
                           0x11,2,v4,1);
            }
            v13 = 0;
            v7 = 0;
            do {
              v13 = (unsigned long)*v1 << (v7 & 0x3f) | v13;
              v7 = v7 + 8;
              v1 = v1 + 1;
            } while (v10 * 8 - v7 != 0);
            if (v5 < 9) {
LBL_00217440:
              v10 = 0;
            }
            else {
              if (v9 <= (v18 - v8) - 9) goto LBL_002174f0;
              v10 = 0;
              v7 = 0;
              v1 = (uint8_t *)((long)&uStack_68 + v8);
              do {
                v10 = (unsigned long)*v1 << (v7 & 0x38) | v10;
                v7 = v7 + 8;
                v9 = v9 - 1;
                v1 = v1 + 1;
              } while (v9 != 0);
            }
LBL_00217444:
            v8 = 0xe000000000000000;
            if (((v10 | v13) & 0x8080808080808080) != 0) {
              v8 = 0xa000000000000000;
            }
            v10 = v8 | v5 << 0x38 | v10;
            goto LBL_0021745c;
          }
LBL_00217684:
          v4 = 0x582;
          v6 = s_UnsafeBufferPointer_with_negativ_005cdf60;
          v16 = 0x27;
          goto LBL_002176c0;
        }
LBL_00217644:
        v4 = 0x7a9;
      }
      v6 = &G_005be7c0;
      v16 = 0;
      goto LBL_002176c0;
    }
    if ((v5 >> 0x3c & 1) == 0) {
      v23 = rt_002a9ba8(v5,v10);
    }
    else {
      v23.hi = v5 & 0xffffffffffff;
      v23.lo = (v10 & 0xfffffffffffffff) + 0x20;
    }
    if ((long)v8 < 0) goto LBL_002174e0;
    if (v23.hi < (long)v18) goto LBL_00217644;
    v1 = (uint8_t *)0x0;
    if (v23.lo != 0) {
      v1 = (uint8_t *)(v23.lo + v8);
    }
    v5 = v18 - v8;
    if ((long)v5 < 0) goto LBL_00217684;
    if ((v5 != 0) && (v1 == (uint8_t *)0x0)) goto LBL_00217734;
    v14 = rt_002a200c(v1,v5);
    if (v18 - v8 == 0) goto LBL_00217388;
    if (v5 < 0x10) {
      v9 = v5 - 8;
      v10 = v5;
      if (7 < v5) {
        v10 = 8;
      }
      v7 = v5;
      if (v10 - 1 <= v5) {
        v7 = v10 - 1;
      }
      if (v10 != v7) {
        v13 = 0;
        v7 = 0;
        v2 = v1;
        do {
          v13 = (unsigned long)*v2 << (v7 & 0x3f) | v13;
          v7 = v7 + 8;
          v2 = v2 + 1;
        } while (v10 * 8 - v7 != 0);
        if (v5 < 9) goto LBL_00217440;
        if ((v18 - v8) - 9 < v9) {
          v10 = 0;
          v8 = 0;
          v1 = v1 + 8;
          do {
            v10 = (unsigned long)*v1 << (v8 & 0x38) | v10;
            v8 = v8 + 8;
            v9 = v9 - 1;
            v1 = v1 + 1;
          } while (v9 != 0);
          goto LBL_00217444;
        }
      }
      goto LBL_002174f0;
    }
LBL_00217420:
    v10 = rt_002a4b90(v1,v5,v5,v14 & 1);
    v13 = *(unsigned long *)(v10 + 0x18);
LBL_0021745c:
    v19[2] = v18;
    v20 = v13;
    uStack_68 = v10;
    (*(code *)v19[4])(&v21,&v20);
    rt_003a25d4(v10);
    v8 = uStack_78;
    v5 = v21;
    rt_003a25d4(v19[7]);
    v19[6] = v5;
    v19[7] = v8;
    v19[8] = 0xf;
  } while( true );
}



/* FUN_002177bc @ 0x002177bc   (est. swift_string_advance)
 * Ghidra: uint32_t FUN_002177bc( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_002177bc( void){
  uint8_t v15;
  uint16_t v11;
  uint32_t v12;
  unsigned long v17;
  unsigned long v16;
  uint64_t v13;
  unsigned long v14;
  long v18;
  char *v1;
  int v7;
  uint64_t *v19;
  unsigned long v4;
  unsigned long v8;
  unsigned long v10;
  uint64_t v5;
  unsigned long v9;
  uint32_t v3;
  unsigned long v2;
  rt16 v22;
  rt16 av110;
  rt16 av111;
  uint64_t v21;
  unsigned long uStack_78;
  rt16u v20;
  uint8_t *v6;
  
  v4 = v19[8];
  do {
    if (v4 != 0) {
      v8 = v19[7];
      v9 = v8 & 0xffffffffffff;
      if ((v4 & 0x2000000000000000) != 0) {
        v9 = v4 >> 0x38 & 0xf;
      }
      v10 = v19[9];
      if (v10 >> 0xe != v9 * 4) {
        v12 = (uint32_t)(v8 >> 0x3b) & 1;
        if ((v4 & 0x1000000000000000) == 0) {
          v12 = 1;
        }
        v14 = v10;
        if ((v10 & 0xc) == 4L << (unsigned long)v12) {
          v14 = rt_0001da84(v10,v8,v4);
        }
        v17 = v14 >> 0x10;
        if (v9 <= v17) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                       s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
        }
        if ((v4 >> 0x3c & 1) == 0) {
          if ((v4 >> 0x3d & 1) == 0) {
            if ((v8 >> 0x3c & 1) == 0) goto LBL_00217bc8;
            v18 = (v4 & 0xfffffffffffffff) + 0x20;
            goto LBL_00217a74;
          }
          v20.lo = v8;
          v20.hi = v4 & 0xffffffffffffff;
          v15 = v20.b[v17];
        }
        else {
          rt_002b141c(v14,v8,v4);
LBL_00217bc8:
          v18 = rt_002a9ba8(v8,v4).lo;
LBL_00217a74:
          v15 = *(uint8_t *)(v18 + v17);
        }
        v3 = (uint32_t)v15;
        if ((v10 & 0xc) == 4L << (unsigned long)v12) {
          v10 = rt_0001da84(v10,v8,v4);
        }
        v7 = 0;
        v19[9] = (uint64_t)&G_00010004 + (v10 & 0xffffffffffff0000);
        goto LBL_00217abc;
      }
    }
    v4 = v19[1];
    v9 = v19[4];
    if ((v9 ^ v4) < 0x4000) {
      v3 = 0;
      v7 = 1;
LBL_00217abc:
      return v3 | v7 << 8;
    }
    v5 = *v19;
    v10 = v19[2];
    v14 = v19[3];
    v17 = rt_002ab4d4(v9,v5,v4,v10,v14);
    v16 = v17 >> 8 & 0x3f;
    v17 = v17 >> 0x10;
    v8 = v4 >> 0x10;
    v2 = v14 >> 0x38 & 0xf;
    if (v16 == 0) {
      if (v17 == v8) {
        v16 = 0;
      }
      else if ((v14 >> 0x3c & 1) == 0) {
        if ((v14 >> 0x3d & 1) == 0) {
          if ((v10 >> 0x3c & 1) == 0) {
            av111 = rt_002a9ba8(v10,v14);
          }
          else {
            av111.hi = v10 & 0xffffffffffff;
            av111.lo = (v14 & 0xfffffffffffffff) + 0x20;
          }
          if (v17 + 1 != av111.hi) {
            if (av111.lo == 0) {
                    /* WARNING: Subroutine does not return */
              rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_unsafelyUnwrapped_of_nil_optiona_005ce1c0,
                           0x21,2,s_Swift_Optional_swift_005ce1f0,0x14,2,0x179,1);
            }
            v11 = *(uint16_t *)(av111.lo + v17);
LBL_002178b8:
            if (v11 == 0xa0d || (v11 & 0x8080) != 0) goto LBL_002179f0;
          }
        }
        else {
          v20.hi = v14 & 0xffffffffffffff;
          v20.lo = v10;
          v22.hi = (uint64_t)v20.hi;
          v22.lo = v10;
          if (v17 + 1 != v2) {
            v11 = *(uint16_t *)(v20.b + v17);
            v20.lo = (uint64_t)v22.lo;
            goto LBL_002178b8;
          }
        }
        v16 = 1;
      }
      else {
LBL_002179f0:
        v16 = rt_002c6d00(v17,v10,v14);
      }
    }
    if ((long)(v16 + v17) <= (long)v8) {
      v8 = v16 + v17;
    }
    if ((v14 >> 0x3c & 1) != 0) {
      rt_002bbcd8();
LBL_00217ae4:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Range_requires_lowerBound_005cda00,0x27,2,
                   s_Swift_Range_swift_005cda30,0x11,2,0x2f9,1);
    }
    v18 = v8 - v17;
    if ((long)v8 < (long)v17) goto LBL_00217ae4;
    if ((v14 >> 0x3d & 1) == 0) {
      if ((v10 >> 0x3c & 1) == 0) {
        av110 = rt_002a9ba8(v10,v14);
      }
      else {
        av110.hi = v10 & 0xffffffffffff;
        av110.lo = (v14 & 0xfffffffffffffff) + 0x20;
      }
      if (av110.hi < (long)v8) {
LBL_00217b2c:
        v13 = 0x7a9;
        v1 = &G_005be7c0;
        v5 = 0;
        goto LBL_00217b68;
      }
      v6 = (uint8_t *)0x0;
      if (av110.lo != 0) {
        v6 = (uint8_t *)(av110.lo + v17);
      }
      v18 = v8 - v17;
      if ((v18 != 0) && (v6 == (uint8_t *)0x0)) {
        v13 = 0x584;
        v1 = s_UnsafeBufferPointer_has_a_nil_st_005cf020;
        v5 = 0x35;
LBL_00217b68:
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v1,v5,2,
                     s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,v13,1);
      }
      v12 = rt_002a200c(v6,v18);
    }
    else {
      v20.hi = v14 & 0xffffffffffffff;
      v20.lo = v10;
      if (v2 < v8) goto LBL_00217b2c;
      v12 = rt_002a200c(v20.b + v17,v18);
      v6 = v20.b + v17;
    }
    v22 = rt_002a2698(v6,v18,v12 & 1);
    v13 = rt_002ab6a0(v9,v5,v4,v10,v14);
    v5 = rt_002b3b84(v13,v5,v4,v10,v14);
    v19[4] = v5;
    v20.lo = (uint64_t)v22.lo;
    (*(code *)v19[5])(&v21,v20);
    rt_003a25d4(v22.hi);
    v4 = uStack_78;
    v5 = v21;
    rt_003a25d4(v19[8]);
    v19[7] = v5;
    v19[8] = v4;
    v19[9] = 0xf;
  } while( true );
}



/* FUN_00217c60 @ 0x00217c60   (est. swift_string_element)
 * Ghidra: uint32_t FUN_00217c60( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_00217c60( void){
  long v6;
  code *v5;
  uint8_t v10;
  unsigned long v12;
  unsigned long *v2;
  unsigned long v8;
  uint32_t v11;
  int v7;
  unsigned long v9;
  unsigned long v13;
  unsigned long v3;
  long *v14;
  unsigned long v4;
  unsigned long v1;
  rt16 v17;
  long v16;
  unsigned long uStack_58;
  unsigned long v15;
  unsigned long uStack_48;
  
  v4 = v14[5];
  do {
    if (v4 != 0) {
      v8 = v14[4];
      v3 = v8 & 0xffffffffffff;
      if ((v4 & 0x2000000000000000) != 0) {
        v3 = v4 >> 0x38 & 0xf;
      }
      v12 = v14[6];
      v17.hi = v8;
      v17.lo = v12;
      if (v12 >> 0xe != v3 * 4) {
        v11 = (uint32_t)(v8 >> 0x3b) & 1;
        if ((v4 & 0x1000000000000000) == 0) {
          v11 = 1;
        }
        v1 = v12 & 0xc;
        if (v1 == 4L << v11) {
          v12 = rt_0001da84(v12,v8,v4);
        }
        v9 = v12 >> 0x10;
        if (v3 <= v9) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                       s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
        }
        if ((v4 >> 0x3c & 1) == 0) {
          if ((v4 >> 0x3d & 1) == 0) {
            if ((v8 >> 0x3c & 1) == 0) goto LBL_00217e7c;
            v2 = (unsigned long *)((v4 & 0xfffffffffffffff) + 0x20);
          }
          else {
            v15 = v8;
            uStack_48 = v4 & 0xffffffffffffff;
            v2 = &v15;
          }
        }
        else {
          v17 = rt_002b141c(v12,v8,v4);
          v9 = v13;
LBL_00217e7c:
          v2 = (unsigned long *)rt_002a9ba8(v17.hi,v4).lo;
        }
        v3 = (uint64_t)v17.lo;
        v10 = *(uint8_t *)((long)v2 + v9);
        if (v1 == 4L << v11) {
          v3 = rt_0001da84(v3,v17.hi,v4);
        }
        v11 = (uint32_t)v10;
        v7 = 0;
        v14[6] = (long)(&G_00010004 + (v3 & 0xffffffffffff0000));
        goto LBL_00217e0c;
      }
    }
    v4 = v14[1];
    v3 = *(unsigned long *)(*v14 + 0x10);
    if (v4 == v3) {
      v11 = 0;
      v7 = 1;
LBL_00217e0c:
      return v11 | v7 << 8;
    }
    if (v3 <= v4) {
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Index_out_of_range_005cd940,0x12,2,
                   s_Swift_ContiguousArrayBuffer_swif_005cd960,0x21,2,0x2b4,1);
    }
    v6 = *v14 + v4 * 0x10;
    v15 = *(unsigned long *)(v6 + 0x20);
    v3 = *(unsigned long *)(v6 + 0x28);
    v14[1] = v4 + 1;
    v5 = (code *)v14[2];
    uStack_48 = v3;
    rt_0036b270(v3);
    (*v5)(&v16,&v15);
    rt_003a25d4(v3);
    v4 = uStack_58;
    v6 = v16;
    rt_003a25d4(v14[5]);
    v14[4] = v6;
    v14[5] = v4;
    v14[6] = 0xf;
  } while( true );
}



/* FUN_00217ea0 @ 0x00217ea0   (est. swift_string_pop_first)
 * Ghidra: uint32_t FUN_00217ea0( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_00217ea0( void){
  unsigned long v3;
  uint8_t v10;
  unsigned long v6;
  long v7;
  int v8;
  uint32_t v4;
  uint64_t *v12;
  unsigned long v11;
  unsigned long v9;
  unsigned long v5;
  uint32_t v1;
  unsigned long v2;
  uint64_t v13;
  long lStack_68;
  unsigned long v14;
  unsigned long uStack_58;
  
  v11 = v12[5];
  do {
    if (v11 != 0) {
      v9 = v12[4];
      v3 = v9 & 0xffffffffffff;
      if ((v11 & 0x2000000000000000) != 0) {
        v3 = v11 >> 0x38 & 0xf;
      }
      v5 = v12[6];
      if (v5 >> 0xe != v3 * 4) {
        v4 = (uint32_t)(v9 >> 0x3b) & 1;
        if ((v11 & 0x1000000000000000) == 0) {
          v4 = 1;
        }
        v6 = v5;
        if ((v5 & 0xc) == 4L << (unsigned long)v4) {
          v6 = rt_0001da84(v5,v9,v11);
        }
        v2 = v6 >> 0x10;
        if (v3 <= v2) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                       s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
        }
        if ((v11 >> 0x3c & 1) == 0) {
          if ((v11 >> 0x3d & 1) == 0) {
            if ((v9 >> 0x3c & 1) == 0) goto LBL_00218058;
            v7 = (v11 & 0xfffffffffffffff) + 0x20;
            goto LBL_00217f9c;
          }
          v14 = v9;
          uStack_58 = v11 & 0xffffffffffffff;
          v10 = *(uint8_t *)((long)&v14 + v2);
        }
        else {
          rt_002b141c(v6,v9,v11);
LBL_00218058:
          v7 = rt_002a9ba8(v9,v11).lo;
LBL_00217f9c:
          v10 = *(uint8_t *)(v7 + v2);
        }
        v1 = (uint32_t)v10;
        if ((v5 & 0xc) == 4L << (unsigned long)v4) {
          v5 = rt_0001da84(v5,v9,v11);
        }
        v8 = 0;
        v12[6] = (uint64_t)&G_00010004 + (v5 & 0xffffffffffff0000);
        goto LBL_00217fe4;
      }
    }
    v13 = *v12;
    v7 = v12[1];
    *v12 = 0;
    v12[1] = 0;
    if (v7 == 0) {
      v1 = 0;
      v8 = 1;
LBL_00217fe4:
      return v1 | v8 << 8;
    }
    lStack_68 = v7;
    (*(code *)v12[2])(&v14,&v13);
    rt_003a25d4(v7);
    v11 = uStack_58;
    v3 = v14;
    rt_003a25d4(v12[5]);
    v12[4] = v3;
    v12[5] = v11;
    v12[6] = 0xf;
  } while( true );
}



/* FUN_00218068 @ 0x00218068   (est. swift_string_peek_first)
 * Ghidra: uint32_t FUN_00218068( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_00218068( void){
  unsigned long v3;
  uint8_t v10;
  unsigned long v6;
  long v7;
  int v8;
  uint32_t v4;
  unsigned long v11;
  long v12;
  unsigned long v9;
  unsigned long v5;
  uint32_t v1;
  unsigned long v2;
  unsigned long v13;
  unsigned long uStack_58;
  
  v11 = *(unsigned long *)(v12 + 0x18);
  if (v11 != 0) {
    v9 = *(unsigned long *)(v12 + 0x10);
    v3 = v9 & 0xffffffffffff;
    if ((v11 & 0x2000000000000000) != 0) {
      v3 = v11 >> 0x38 & 0xf;
    }
    v5 = *(unsigned long *)(v12 + 0x20);
    if (v5 >> 0xe != v3 * 4) {
      v4 = (uint32_t)(v9 >> 0x3b) & 1;
      if ((v11 & 0x1000000000000000) == 0) {
        v4 = 1;
      }
      v6 = v5;
      if ((v5 & 0xc) == 4L << (unsigned long)v4) {
        v6 = rt_0001da84(v5,v9,v11);
      }
      v2 = v6 >> 0x10;
      if (v3 <= v2) {
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                     s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
      }
      if ((v11 >> 0x3c & 1) == 0) {
        if ((v11 >> 0x3d & 1) == 0) {
          if ((v9 >> 0x3c & 1) == 0) goto LBL_002181d0;
          v7 = (v11 & 0xfffffffffffffff) + 0x20;
          goto LBL_00218114;
        }
        v13 = v9;
        uStack_58 = v11 & 0xffffffffffffff;
        v10 = *(uint8_t *)((long)&v13 + v2);
      }
      else {
        rt_002b141c(v6,v9,v11);
LBL_002181d0:
        v7 = rt_002a9ba8(v9,v11).lo;
LBL_00218114:
        v10 = *(uint8_t *)(v7 + v2);
      }
      v1 = (uint32_t)v10;
      if ((v5 & 0xc) == 4L << (unsigned long)v4) {
        v5 = rt_0001da84(v5,v9,v11);
      }
      v8 = 0;
      *(void **)(v12 + 0x20) = &G_00010004 + (v5 & 0xffffffffffff0000);
      goto LBL_0021815c;
    }
  }
  v1 = 0;
  v8 = 1;
LBL_0021815c:
  return v1 | v8 << 8;
}



/* FUN_002181e0 @ 0x002181e0   (est. swift_string_loop)
 * Ghidra: void FUN_002181e0( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002181e0( void){
  uint8_t v2;
  code *v1;
  uint64_t v3;
  uint64_t v20;
  uint64_t v12;
  uint64_t v22;
  long v13;
  long v8;
  code *v10;
  code *v7;
  code *v9;
  code *v14;
  code *v15;
  code *v16;
  code *v21;
  code *v11;
  long v17;
  long v6;
  long v19;
  long v18;
  long v24;
  long v4;
  uint64_t v5;
  uint64_t v25;
  uint64_t v23;
  uint64_t v26;
  rt16 v42;
  rt16 v43;
  long v33;
  uint64_t v41;
  long v39;
  uint64_t v34;
  uint64_t v29;
  uint64_t v35;
  long v28;
  uint64_t v30;
  uint64_t v38;
  uint64_t v27;
  uint64_t uStack_40;
  long v31;
  unsigned long v40;
  code *v36;
  uint64_t uStack_20;
  uint64_t v37;
  long v32;
  
  v42 = rt_0008e518();
  v4 = (uint64_t)v42.lo;
  v5 = *(uint64_t *)(v4 + 0x10);
  v41 = v22;
  rt_003520f8(v4,*(uint64_t *)(v4 + 0x18));
  v27 = v5;
  uStack_40 = v20;
  rt_00377824(0xff);
  rt_0034ee68();
  rt_00310d68();
  rt_00348e60();
  (*G_00658c00)(*(uint64_t *)(v13 + 0x40));
  rt_003489c0();
  (*G_00658c00)();
  rt_0034b4c0();
  v5 = *(uint64_t *)(v4 + 0x20);
  rt_0034de44();
  rt_00377824();
  rt_00352efc();
  v35 = v12;
  v29 = rt_00310d68().lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034c330();
  v37 = v5;
  rt_0034eb64(0xff);
  rt_00377824();
  rt_0034f554();
  rt_00310d68();
  rt_00348e00();
  (*G_00658c00)(*(uint64_t *)(v8 + 0x40));
  rt_003503ec();
  rt_0034d244();
  (*G_00658c00)();
  rt_00351c10((long)&v33 - v19);
  v36 = *(code **)(v17 + 0x10);
  v40 = (unsigned long)(v17 + 0x10) & 0xffffffffffff | 0xe3ba000000000000;
  v31 = v17 + 8;
  v4 = (long)*(int *)(v4 + 0x2c);
  v39 = v18 + 8;
  v33 = v18;
  v38 = rt_0035a59c();
  v28 = v6 + 0x18;
  v32 = v4;
  do {
    (*v36)(uStack_20,v24 + v4,v5);
    v43 = rt_00351330();
    rt_0035681c(v43.lo,v43.hi,v25);
    rt_00359c64();
    rt_003507e0();
    (*v10)();
    v2 = (int)v4 == 1;
    if (!(bool)v2) {
      rt_0034c4bc(v24 + v32);
      if ((bool)v2) {
        rt_00350410();
        goto LBL_002185cc;
      }
      rt_0034b278();
      rt_00350b84(v37);
      rt_00377bec();
      rt_00354474();
      v5 = v34;
      rt_003514e8(v34);
      (*v21)();
      v43 = rt_0035172c();
      rt_00350884(v43.lo,v43.hi,v35);
      if (!(bool)v2) {
        (**(code **)(v33 + 0x20))(v41,v5,v29);
        goto LBL_002185a0;
      }
      v5 = rt_00352bc8();
      (*v7)(v5,v29);
    }
    rt_0035454c();
    rt_00352998(0xff,uStack_40);
    rt_00377824();
    rt_003530f4();
    rt_00350a1c();
    v5 = rt_00377bec().lo;
    v1 = (code *)rt_000a68f4();
    rt_003504e8();
    v3 = rt_00377dcc();
    (*v1)(v26,v3,v5);
    rt_0034b2c8(v26);
    if ((bool)v2) {
      rt_00353bf4();
      rt_00350ab8();
      (*v16)();
      rt_00350744(v41);
      rt_000839d8();
LBL_002185a0:
      rt_0008e500(v42.hi);
      return;
    }
    rt_00354bbc();
    rt_003516e4();
    (*v9)();
    rt_0034b2c8(v23);
    if ((bool)v2) {
      rt_00350410();
LBL_002185cc:
      rt_00348898();
      rt_0034a2f8();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
    rt_00357664();
    rt_00352680();
    v3 = v30;
    rt_00358e34();
    rt_000e15d8();
    (*v11)();
    rt_00353bf4();
    rt_00350ab8();
    (*v14)();
    rt_00350750(v3);
    rt_000839d8();
    rt_00354ab0();
    v4 = v32;
    v5 = v38;
    (*v15)(v24 + v32,v3,v38);
  } while( true );
}



/* FUN_002185ec @ 0x002185ec   (est. swift_chain_call)
 * Ghidra: void FUN_002185ec( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002185ec( void){
  code *v1;
  
  rt_00351cc4();
  rt_00349830();
  rt_003505c4();
  rt_00377824();
  rt_00351f10();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0c4();
  rt_003506b0();
  rt_0034c2a4();
  (*v1)();
  rt_00077708();
  ((code)FUN_00217100)();
  return;
}



/* FUN_0021867c @ 0x0021867c   (est. swift_config_store)
 * Ghidra: void FUN_0021867c(uint64_t param_1)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021867c(uint64_t param_1){
  rt_0028c784(param_1,&G_0060e208,&G_0060e230);
  return;
}



/* FUN_0021868c @ 0x0021868c   (est. swift_dispatch5)
 * Ghidra: void FUN_0021868c( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021868c( void){
  uint64_t v2;
  long v3;
  uint64_t v1;
  long v4;
  long v5;
  rt16 v6;
  
  v3 = rt_00351cc4();
  v2 = *(uint64_t *)(v3 + 0x20);
  v6 = rt_00350bd8(*(uint64_t *)(v3 + 0x18));
  rt_00349b14(v6.lo,v6.hi,*(uint64_t *)(v5 + 0x10));
  v6 = rt_00377824();
  v1 = rt_0034a944(v6.lo,v6.hi,v6.lo);
  rt_00377824(v1,v2);
  rt_00352efc();
  rt_00310d68();
  rt_00350404();
                    /* WARNING: Could not recover jumptable at 0x00218710. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(v4 + 0x10))();
  return;
}



/* FUN_00218714 @ 0x00218714   (est. swift_dispatch6)
 * Ghidra: void FUN_00218714( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00218714( void){
  int v3;
  uint64_t v2;
  long v1;
  uint64_t v7;
  long v6;
  long v5;
  long v4;
  rt16 v8;
  
  rt_00084220();
  rt_00351dc0();
  rt_00353fac();
  v2 = rt_0034cae8();
  rt_00377824(v2,v7);
  rt_00349530();
  (**(code **)(v5 + 0x20))(v6);
  rt_0034f614();
  v1 = rt_0031be78();
  v3 = *(int *)(v1 + 0x2c);
  rt_00348f14();
  v8 = rt_00358ff4();
  rt_003519fc(v8.lo,v8.hi,v8.lo);
  rt_00377824();
  rt_00352efc();
  rt_00310d68();
  rt_0034ad10();
                    /* WARNING: Could not recover jumptable at 0x002187dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(v4 + 0x20))(v6 + v3);
  return;
}



/* FUN_002187e0 @ 0x002187e0   (est. swift_dispatch7)
 * Ghidra: void FUN_002187e0( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002187e0( void){
  uint8_t v21;
  int v3;
  uint64_t v2;
  uint64_t v4;
  unsigned long v7;
  long v5;
  uint64_t v14;
  uint64_t v22;
  uint64_t v20;
  code *v16;
  code *v12;
  code *v10;
  code *v11;
  code *v15;
  long v13;
  long v8;
  long v9;
  long v6;
  long v18;
  code *v1;
  long v17;
  rt16 v23;
  rt16 v24;
  uint64_t v19;
  
  v23 = rt_0008e518();
  rt_00348f14(v22);
  v2 = rt_00358ff4().lo;
  v4 = rt_0034c108();
  v4 = rt_00377824(v4,v20).lo;
  rt_000a6f88(v4,v4);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034a760();
  rt_00310d68(0);
  rt_00348e18();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aab0();
  rt_0034d414();
  rt_003515b4();
  rt_003722e4();
  rt_00348e00();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b05c();
  rt_0035113c();
  rt_00352ae4();
  rt_00377824();
  rt_00350c38();
  rt_00351378();
  rt_00377bec();
  rt_003514b8();
  rt_00350adc();
  rt_00350bb4(v23.lo);
  v7 = (*v16)();
  if ((v7 & 1) != 0) {
    v24 = rt_0035050c();
    v5 = rt_0031be78(v24.lo,v24.hi,v22,v20);
    v3 = *(int *)(v5 + 0x2c);
    v6 = (long)*(int *)(v18 + 0x30);
    v1 = *(code **)(v8 + 0x10);
    rt_00353c6c(v5,v23.lo + (long)v3);
    (*v1)();
    (*v1)(v17 + v6,v23.hi + (long)v3,v20);
    v24 = rt_003517a8();
    rt_00350884(v24.lo,v24.hi,v14);
    v5 = v8;
    if ((bool)v21) {
      rt_00353c84(v17 + v6);
      v3 = rt_000839f8();
      if (v3 != 1) {
        v5 = v9;
      }
    }
    else {
      rt_00358db8();
      rt_003508c0();
      (*v1)();
      rt_00353c84(v17 + v6);
      rt_00350884();
      if ((bool)v21) {
        rt_003529a4();
        rt_003509b0();
        (*v12)();
        v5 = v9;
      }
      else {
        v4 = rt_003547ec();
        v24 = rt_00355bc4(v4,v17 + v6);
        (*v15)(v24.lo,v24.hi,v14);
        rt_0034c3c4();
        rt_00377bec(v20,v2,v14);
        rt_003514b8();
        rt_0014ae44();
        v2 = rt_00350a7c();
        rt_00351e78(v2,v23.hi);
        (*v10)();
        v1 = *(code **)(v13 + 8);
        rt_00350a04();
        (*v1)();
        rt_003509b0();
        (*v1)();
      }
    }
    rt_0035060c(*(uint64_t *)(v5 + 8));
    (*v11)();
  }
  v2 = rt_00352980();
  rt_0008e500(v2,v19);
  return;
}



/* FUN_00218ae4 @ 0x00218ae4   (est. swift_dispatch8)
 * Ghidra: void FUN_00218ae4( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00218ae4( void){
  int v13;
  uint8_t v32;
  uint32_t v7;
  uint64_t v10;
  long v11;
  uint64_t v14;
  unsigned long v8;
  long v9;
  unsigned long v12;
  uint64_t v33;
  uint64_t v31;
  long v29;
  long v23;
  long v18;
  code *v20;
  code *v16;
  code *v4;
  code *v19;
  code *v24;
  code *v25;
  code *v26;
  code *v21;
  code *v28;
  code *v22;
  code *v17;
  long v27;
  long v15;
  long v5;
  long v6;
  code *v3;
  code *v1;
  code *v2;
  uint64_t v30;
  rt16 v42;
  uint64_t v35;
  uint64_t v40;
  uint64_t v36;
  uint64_t v37;
  long v38;
  uint64_t v34;
  long v39;
  uint64_t v41;
  
  rt_0008e518();
  v42 = rt_00351dc0();
  v5 = (uint64_t)v42.lo;
  rt_00348f14(v33);
  rt_00358ff4();
  v10 = rt_0034c158();
  v10 = rt_00377824(v10,v31).lo;
  rt_003542b8();
  rt_00310d68();
  rt_0034e57c();
  rt_003515b4();
  v11 = rt_003722e4();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v29 + 0x40));
  rt_00348b5c();
  (*G_00658c00)();
  rt_0034c2b4();
  rt_00349c70();
  (*G_00658c00)(*(uint64_t *)(v23 + 0x40));
  rt_003493c4();
  rt_0034d444();
  (*G_00658c00)();
  rt_0034a62c();
  (*G_00658c00)();
  rt_0034abec();
  (*G_00658c00)();
  rt_00349f5c();
  (*G_00658c00)();
  rt_0034ac14();
  (*G_00658c00)();
  rt_0034b87c();
  rt_003494e8();
  (*G_00658c00)(*(uint64_t *)(v18 + 0x40));
  rt_003493c4();
  rt_0034d294();
  (*G_00658c00)();
  rt_0034a9d4();
  (*G_00658c00)();
  rt_0034aa28();
  rt_0034d3e4();
  rt_00377824();
  rt_00350470();
  rt_00350aac();
  v14 = rt_00377bec().lo;
  rt_0034a30c();
  rt_0034e084(v5);
  v8 = (*v20)();
  if ((v8 & 1) == 0) {
    rt_0016186c(v14);
    rt_0034e054();
    rt_003531e4();
    v7 = (*v16)();
    goto LBL_002190c0;
  }
  rt_0034f614();
  v9 = rt_0031be78();
  v13 = *(int *)(v9 + 0x2c);
  v1 = *(code **)(v27 + 0x10);
  rt_00355b04(v9,v5 + v13);
  (*v1)();
  rt_00349f3c();
  if (!(bool)v32) {
    v4 = *(code **)(v15 + 0x20);
    rt_00350c68(v41);
    (*v4)();
    (*v1)(v36,v42.hi + (long)*(int *)(v9 + 0x2c));
    rt_00349f3c(v36);
    if (!(bool)v32) {
      rt_0034ef28();
      (*v4)();
      rt_0034c3c4();
      rt_00355ad0(v31);
      rt_00377bec();
      rt_0034b4ec();
      rt_003504c4();
      rt_0034beec();
      v7 = (*v25)();
      v1 = *(code **)(v15 + 8);
      rt_003510b8();
      (*v1)();
      rt_00350524();
      (*v1)();
      goto LBL_002190c0;
    }
    rt_003569d8();
    (*v28)();
  }
  v2 = *(code **)(v27 + 8U);
  v8 = (unsigned long)(v27 + 8U) & 0xffffffffffff | 0x4f8000000000000;
  rt_00350b3c();
  (*v2)();
  rt_0034c3f4(v34);
  rt_000839d8();
  v6 = (long)*(int *)(v11 + 0x30);
  (*v1)(v39,v5 + v13);
  v4 = *(code **)(v27 + 0x20);
  (*v4)(v39 + v6,v34);
  rt_00349f3c(v39);
  if ((bool)v32) {
    rt_00349f3c(v39 + v6);
    if ((bool)v32) {
      rt_00350b3c();
      (*v2)(v8);
LBL_00218f50:
      v13 = *(int *)(v9 + 0x2c);
      rt_0034c3f4(v37);
      v14 = rt_000839d8().lo;
      v5 = (long)*(int *)(v11 + 0x30);
      rt_00358dd0(v14,v42.hi + (long)v13);
      (*v1)();
      rt_0035256c(v38 + v5);
      (*v4)();
      rt_00349f3c(v38);
      if ((bool)v32) {
        rt_00349f3c(v38 + v5);
        if (!(bool)v32) {
          v39 = v38;
          goto LBL_00219100;
        }
        rt_003507c8();
        (*v2)(v8);
      }
      else {
        rt_000e15d8();
        (*v1)();
        rt_00349f3c(v38 + v5);
        if ((bool)v32) {
          v40 = v35;
          v39 = v38;
          goto LBL_002190e8;
        }
        v10 = rt_003547ec();
        rt_003543f8(v10,v38 + v5);
        (*v17)();
        rt_0034c3c4();
        rt_00355ad0(v31);
        rt_00377bec();
        rt_0034a30c();
        rt_00350c80();
        rt_0034beec();
        v12 = (*v24)();
        v1 = *(code **)(v15 + 8);
        rt_003508cc();
        (*v1)();
        rt_003510b8();
        (*v1)();
        rt_003507c8();
        (*v2)(v8);
        if ((v12 & 1) == 0) goto LBL_00219118;
      }
      v7 = 0;
LBL_002190c0:
      rt_0008e500(v7 & 1,v30);
      return;
    }
  }
  else {
    rt_00350ea4();
    (*v1)();
    v14 = rt_00349f3c(v39 + v6);
    if (!(bool)v32) {
      rt_003543f8(v14,v39 + v6);
      (*v22)();
      rt_0034c3c4();
      rt_00355ad0(v31);
      rt_00377bec();
      rt_0034a30c();
      rt_00350a04();
      rt_0034beec();
      v12 = (*v19)();
      v3 = *(code **)(v15 + 8);
      rt_003508cc();
      (*v3)();
      rt_003505e8();
      (*v3)();
      rt_00350b3c();
      (*v2)(v8);
      if ((v12 & 1) == 0) goto LBL_00219118;
      goto LBL_00218f50;
    }
LBL_002190e8:
    rt_003529a4();
    (*v26)(v40,v10);
  }
LBL_00219100:
  rt_00359478();
  (*v21)(v39,v11);
LBL_00219118:
  rt_0034b348();
  rt_003486b8(0xc9);
  rt_0034975c();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}



/* FUN_0021914c @ 0x0021914c   (est. swift_dispatch9)
 * Ghidra: void FUN_0021914c(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021914c(uint64_t param_1, uint64_t param_2, uint64_t param_3){
  uint64_t v2;
  code *v1;
  uint64_t v3;
  uint64_t v4;
  long v5;
  uint64_t v6;
  rt16 v7;
  
  rt_0008e518();
  rt_0035128c();
  v1 = (code *)rt_0031945c(param_3);
  v3 = *(uint64_t *)(v5 + 0x10);
  v2 = *(uint64_t *)(v5 + 0x18);
  rt_0034f788();
  rt_0034d404();
  rt_00377824();
  rt_00356b98();
  (*v1)();
  rt_00348f14(v2);
  v7 = rt_00377824(0xff,v4,v3);
  rt_00351930(v7.lo,v7.hi,v7.lo);
  rt_00377824();
  rt_00352efc();
  v3 = rt_00310d68().lo;
  rt_00353fa0(v3,v3);
  rt_002655cc();
  rt_0008e500(v6);
  return;
}



/* FUN_002191fc @ 0x002191fc   (est. swift_emit_char)
 * Ghidra: void FUN_002191fc( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002191fc( void){
  uint8_t v1;
  
  rt_00355684();
  v1 = rt_00348c48();
  rt_0034d264(v1,G_004e7a30[16],
               v1 ^ (uint8_t)G_004e7a30[0]);
  ((code)FUN_0021914c)();
  rt_001a8564();
  return;
}



/* FUN_0021927c @ 0x0021927c   (est. swift_string_find)
 * Ghidra: rt16 FUN_0021927c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
rt16 FUN_0021927c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4){
  unsigned long v1;
  unsigned long v2;
  unsigned long v5;
  uint64_t v4;
  rt16 v7;
  unsigned long v6;
  unsigned long v3;
  
  v2 = rt_002527e8();
  v6 = 0xf;
  if (0x3fff < v2) {
    v4 = 0xf;
    do {
      v5 = v6;
      v7 = rt_00252e24(v6,param_1,param_2,param_3,param_4);
      v3 = (uint64_t)v7.hi;
      rt_003a25d4(v3);
      v1 = v7.lo & 0xffffffffffff;
      if ((v3 & 0x2000000000000000) != 0) {
        v1 = v3 >> 0x38 & 0xf;
      }
      if (v1 != 0) goto LBL_00219348;
      rt_00252b68(&v6,param_1,param_2,param_3,param_4);
    } while ((v6 ^ v2) >> 0xe != 0);
  }
  v4 = 0;
  v5 = v2;
LBL_00219348:
  v7.hi = v4;
  v7.lo = v5;
  return v7;
}



/* FUN_00219370 @ 0x00219370   (est. swift_string_reduce)
 * Ghidra: rt16 FUN_00219370( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
rt16 FUN_00219370( void){
  unsigned long v2;
  unsigned long v3;
  unsigned long v6;
  code *v1;
  unsigned long v9;
  unsigned long v4;
  unsigned long v8;
  uint64_t v7;
  unsigned long v5;
  unsigned long *v10;
  rt16 av20;
  uint8_t v12 [16];
  unsigned long v11;
  unsigned long uStack_68;
  
  v3 = *v10;
  v9 = v10[1];
  if (v9 >> 0xe != v3 >> 0xe) {
    v6 = v10[2];
    v4 = v10[3];
    v1 = (code *)v10[4];
    v5 = v3;
    do {
      av20 = rt_002b439c(v5,v3,v9,v6,v4);
      *(rt16*)v12 = av20;
      (*v1)(&v11,v12);
      rt_003a25d4(av20.hi);
      v8 = uStack_68;
      v2 = v11;
      rt_003a25d4(uStack_68);
      v2 = v2 & 0xffffffffffff;
      if ((v8 & 0x2000000000000000) != 0) {
        v2 = v8 >> 0x38 & 0xf;
      }
      if (v2 != 0) {
        v7 = 0xf;
        goto LBL_00219458;
      }
      v7 = rt_002ab6a0(v5,v3,v9,v6,v4);
      v5 = rt_002b3b84(v7,v3,v9,v6,v4);
    } while (v9 >> 0xe != v5 >> 0xe);
  }
  v7 = 0;
  v5 = v9;
LBL_00219458:
  av20.hi = v7;
  av20.lo = v5;
  return av20;
}



/* FUN_0021947c @ 0x0021947c   (est. swift_array_reduce)
 * Ghidra: rt16 FUN_0021947c(long param_1, code * param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
rt16 FUN_0021947c(long param_1, code * param_2){
  unsigned long v2;
  unsigned long v3;
  uint64_t v4;
  long v5;
  long v6;
  uint64_t *v1;
  rt16 v9;
  uint64_t v7;
  uint64_t uStack_68;
  unsigned long v8;
  unsigned long uStack_58;
  
  v6 = *(long *)(param_1 + 0x10);
  if (v6 == 0) {
    v4 = 0;
    v5 = 0;
  }
  else {
    v5 = 0;
    v1 = (uint64_t *)(param_1 + 0x28);
    do {
      v7 = v1[-1];
      v4 = *v1;
      uStack_68 = v4;
      rt_0036b270(v4);
      (*param_2)(&v8,&v7);
      rt_003a25d4(v4);
      v3 = uStack_58;
      v2 = v8;
      rt_003a25d4(uStack_58);
      v2 = v2 & 0xffffffffffff;
      if ((v3 & 0x2000000000000000) != 0) {
        v2 = v3 >> 0x38 & 0xf;
      }
      if (v2 != 0) {
        v4 = 0xf;
        goto LBL_00219534;
      }
      v1 = v1 + 2;
      v5 = v5 + 1;
    } while (v6 != v5);
    v4 = 0;
    v5 = v6;
  }
LBL_00219534:
  v9.hi = v4;
  v9.lo = v5;
  return v9;
}



/* FUN_00219554 @ 0x00219554   (est. swift_array_all)
 * Ghidra: bool FUN_00219554(uint64_t param_1, uint64_t param_2, code * param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
bool FUN_00219554(uint64_t param_1, uint64_t param_2, code * param_3){
  unsigned long v1;
  uint64_t v3;
  uint64_t uStack_48;
  unsigned long v2;
  unsigned long uStack_38;
  
  v3 = param_1;
  uStack_48 = param_2;
  rt_0036b270(param_2);
  (*param_3)(&v2,&v3);
  rt_003a25d4(param_2);
  rt_003a25d4(uStack_38);
  v1 = v2 & 0xffffffffffff;
  if ((uStack_38 & 0x2000000000000000) != 0) {
    v1 = uStack_38 >> 0x38 & 0xf;
  }
  return v1 == 0;
}



/* FUN_002195e0 @ 0x002195e0   (est. swift_dispatch10)
 * Ghidra: void FUN_002195e0(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002195e0(uint64_t param_1, uint64_t param_2, uint64_t param_3){
  code *v1;
  unsigned long v3;
  code *v2;
  uint64_t v16;
  uint64_t v18;
  long v12;
  code *v8;
  code *v10;
  code *v6;
  code *v9;
  code *v13;
  code *v14;
  code *v17;
  code *v11;
  code *v7;
  long v15;
  long v5;
  long v21;
  uint64_t v20;
  uint64_t v4;
  uint64_t v19;
  rt16 v23;
  uint64_t v22;
  
  rt_0008e518();
  rt_00351a38();
  rt_00350bd8(v16);
  v4 = *(uint64_t *)(v21 + 0x10);
  v23 = rt_00349b14();
  v4 = rt_00377824(v23.lo,v23.hi,v4).lo;
  rt_0034cd7c();
  rt_0035056c();
  rt_00377824();
  rt_00352efc();
  rt_0034d464();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b250();
  rt_003504e8();
  rt_00377dcc();
  rt_00348fd8();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b460();
  rt_003502f8();
  rt_00377824();
  rt_00348e18();
  (*G_00658c00)(*(uint64_t *)(v12 + 0x40));
  rt_00348abc();
  (*G_00658c00)();
  rt_0034b758();
  rt_003512d8();
  rt_003507bc();
  (*v17)();
  rt_003506e8();
  rt_003507bc();
  (*v11)();
  rt_00350c2c();
  rt_00351444();
  rt_00377bec();
  rt_00027754();
  v1 = (code *)rt_0014ae44();
  do {
    v3 = (*v1)();
    if ((v3 & 1) != 0) {
      v1 = *(code **)(v5 + 8);
      (*v1)();
      (*v1)(v20,v4);
      ((code)FUN_002198fc)(v18,v21);
LBL_002198e4:
      rt_0008e500(v19);
      return;
    }
    rt_00351b84();
    rt_003528ac();
    v2 = (code *)(*v8)();
    (**(code **)(v15 + 0x10))(param_3);
    rt_0034cfa4();
    (*v2)();
    rt_003578a8();
    rt_003192a8();
    rt_003514ac();
    rt_00350c38();
    v3 = (*v10)();
    if ((v3 & 1) == 0) {
      rt_00353be8();
      (*v13)(v20,v4);
      rt_0034fe64();
      rt_00351414(v22);
      (*v7)();
      rt_00350bf0(*(uint64_t *)(v15 + 8));
      (*v14)();
      rt_00350750(v22);
      rt_000839d8();
      rt_00350618(v18);
      rt_00350974();
      ((code)FUN_00218714)();
      goto LBL_002198e4;
    }
    rt_00350bf0(*(uint64_t *)(v15 + 8));
    (*v6)();
    rt_00027818();
    rt_003505f4();
    rt_00350878();
    (*v9)();
  } while( true );
}



/* FUN_002198fc @ 0x002198fc   (est. swift_dispatch11)
 * Ghidra: void FUN_002198fc( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002198fc( void){
  uint64_t v3;
  code *v2;
  uint64_t v1;
  uint64_t v4;
  rt16 v5;
  
  rt_00084220();
  v5 = rt_00350b54();
  rt_00350bd8(v5.hi);
  v1 = *(uint64_t *)(v5.lo + 0x10);
  v5 = rt_00349b14();
  v5 = rt_00377824(v5.lo,v5.hi,v1);
  rt_003521d4(v5.lo,v5.hi,v5.lo);
  rt_003542b8();
  rt_00377824();
  rt_0034f554();
  rt_0034d464();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aee4();
  rt_0034e6ec();
  rt_00377824();
  rt_00351f10();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b05c();
  rt_00310924();
  rt_003503a0();
  (*v2)();
  rt_00350eb0();
  rt_000839d8();
  rt_00350738(v3);
  rt_00351584();
  ((code)FUN_00218714)();
  rt_00084234(v4);
  return;
}



/* FUN_00219a00 @ 0x00219a00   (est. swift_dispatch12)
 * Ghidra: void FUN_00219a00(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00219a00(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4){
  uint8_t stack_base[512];
  uint8_t *stack_ptr = stack_base;

  uint8_t v34;
  uint64_t v4;
  uint64_t v5;
  code *v3;
  unsigned long v9;
  uint64_t v8;
  code *v2;
  unsigned long v7;
  uint64_t v30;
  long v22;
  long v15;
  long v18;
  long v13;
  code *v16;
  unsigned long v23;
  code *v24;
  code *v27;
  code *v19;
  code *v25;
  code *v26;
  code *v29;
  code *v20;
  code *v14;
  code *v21;
  code *v17;
  long v28;
  long v11;
  long v12;
  long v10;
  uint64_t v6;
  code *v1;
  uint64_t v31;
  uint64_t v32;
  rt16 av40;
  rt16 av41;
  uint64_t v37;
  uint64_t v38;
  uint64_t v33;
  uint64_t v36;
  uint64_t v35;
  uint8_t v39 [40];
  
  av40 = rt_0008e518();
  v8 = (uint64_t)av40.lo;
  v6 = *(uint64_t *)(av40.hi + 0x10);
  v5 = param_3;
  v4 = rt_0034cae8();
  rt_00351f1c(v4,v5);
  v5 = rt_00377824().lo;
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v22 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034aa14();
  rt_00348f14(param_3);
  v4 = rt_00358ff4().lo;
  rt_00350768(0xff);
  rt_00377824();
  rt_0034ee68();
  rt_00310d68();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v15 + 0x40));
  rt_003493c4();
  rt_0034d254();
  (*G_00658c00)();
  rt_0034b3d8();
  rt_003499f0();
  (*G_00658c00)(*(uint64_t *)(v18 + 0x40));
  rt_003493c4();
  rt_0034d234();
  (*G_00658c00)();
  rt_0034c2b4();
  rt_003504e8();
  rt_00377dcc();
  rt_00348cd0();
  (*G_00658c00)(*(uint64_t *)(v13 + 0x40));
  rt_003493c4();
  rt_0034e6cc();
  (*G_00658c00)();
  rt_0034c2c8();
  rt_00352ecc(param_3);
  rt_003528ac(v39,v8);
  v3 = (code *)(*v16)();
  rt_00351c4c();
  (*v29)(v4);
  rt_0034c3b4();
  (*v3)();
  rt_0031be78(0,v6,param_3,param_4);
  (**(code **)(v11 + 0x10))();
  rt_00357400();
  rt_0034b2c8();
  if ((bool)v34) {
    rt_003489dc(0xfd);
    rt_0034a2f8();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  rt_0035466c();
  rt_00319658();
  rt_0034efa8();
  rt_00351ab0();
  (*v20)();
  v3 = *(code **)(v12 + 8);
  rt_00350630();
  (*v3)();
  rt_00351750(v6);
  rt_00350a34(v33);
  (*v14)();
  rt_003510ac(*(uint64_t *)(v10 + 8));
  (*v24)();
  rt_0034c3c4();
  rt_00350e54();
  rt_00377bec();
  rt_00349fe0();
  rt_003507c8();
  rt_00350db4();
  v9 = (*v27)();
  rt_00350630();
  (*v3)();
  if ((v9 & 1) == 0) {
    v5 = (**(code **)(v28 + 0x10))(v36,v8,v5);
    rt_00358f54(*(uint64_t *)(v12 + 0x20),v5,v35);
    (*v19)();
    rt_0034f474(v38);
    av40 = rt_000839d8();
    rt_0009461c(v30,av40.lo,av40.hi,v6);
LBL_00219d7c:
    ((code)FUN_00218714)();
  }
  else {
    v9 = (unsigned long)(v10 + 8) & 0xffffffffffff | 0x4f8000000000000;
    (*v3)(v35);
    rt_00353d94(param_3);
    rt_00352f48(&stack_ptr);
    rt_003510f4(v8);
    (*v21)();
    v3 = (code *)rt_00310924(param_3);
    rt_0034c3c4();
    av41 = rt_003507bc();
    rt_00377bec(av41.lo,av41.hi,v5);
    v8 = rt_00027754();
    v2 = (code *)rt_0014ae44();
    while( true ) {
      rt_00350c2c(v36);
      (*v3)();
      av41 = rt_003509d4();
      v7 = (*v2)(av41.lo,av41.hi,v5,v8);
      v1 = *(code **)(v28 + 8U);
      rt_0009461c();
      (*v1)();
      if ((v7 & 1) != 0) break;
      rt_00355634();
      rt_00351900();
      av41 = rt16_mklo((*v16)());
      (*v29)(v23 & 0xffffffffffff | 0xe3ba000000000000,v37,av41.hi,
                     v31);
      rt_0034c3b4();
      ((code)(av41.lo))();
      rt_0035466c();
      rt_003192a8();
      v4 = rt_0034e62c();
      v7 = (*v25)(v4,v1);
      if ((v7 & 1) == 0) {
        rt_003578c0();
        rt_0035156c();
        rt_003511a8(v38);
        (*v17)();
        rt_00351450();
        rt_00353148();
        (*v24)();
        rt_0034ba48();
        rt_000839d8();
        rt_00350878(v30,v9);
        rt_00356958();
        goto LBL_00219d7c;
      }
      rt_003505e8();
      rt_00353148();
      (*v24)();
      rt_00027818(param_3);
      rt_00350a7c();
      rt_003510f4();
      (*v26)();
    }
    (*v1)(v28 + 8U & 0xffffffffffff | 0x4f8000000000000,v9,v5);
    ((code)FUN_002198fc)(v30,av40.hi,param_3,param_4);
  }
  rt_0008e500(v32);
  return;
}



/* FUN_00219fcc @ 0x00219fcc   (est. swift_dispatch13)
 * Ghidra: void FUN_00219fcc(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00219fcc(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4){
  uint8_t stack_base[512];
  uint8_t *stack_ptr = stack_base;

  uint8_t v45;
  uint64_t v5;
  unsigned long v6;
  uint64_t v8;
  code *v3;
  long v9;
  code *v2;
  long v37;
  long v25;
  long v16;
  code *v24;
  code *v14;
  unsigned long v11;
  code *v20;
  uint64_t v30;
  code *v33;
  code *v13;
  code *v31;
  code *v32;
  code *v36;
  code *v29;
  code *v22;
  code *v18;
  code *v23;
  code *v26;
  code *v27;
  code *v12;
  uint64_t *v19;
  code *v28;
  code *v17;
  code *v15;
  code *v21;
  code *v34;
  uint64_t *v35;
  uint64_t v10;
  long v40;
  code *v42;
  uint64_t *v1;
  code *v4;
  uint64_t v7;
  uint64_t v41;
  uint64_t v38;
  uint64_t v39;
  uint64_t v44;
  uint64_t v43;
  rt16 av50;
  uint64_t v46;
  uint8_t v47 [40];
  
  rt_0008e518();
  rt_003504d0();
  rt_00354128();
  rt_00350bd8(param_3);
  v7 = *(uint64_t *)(v40 + 0x10);
  av50 = rt_00349b14();
  rt_00377824(av50.lo,av50.hi,v7);
  rt_0034d2a4();
  rt_0034f564(0xff);
  rt_00377824();
  rt_0034e57c();
  rt_00310d68();
  v5 = rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v37 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  rt_003509a4();
  rt_00349c70();
  (*G_00658c00)(*(uint64_t *)(v25 + 0x40));
  rt_00348b5c();
  (*G_00658c00)();
  rt_0034b4c0();
  rt_003504e8();
  rt_00377dcc();
  rt_00348e60();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034cd54();
  rt_00350bfc(0,param_3);
  rt_00377824();
  rt_00348e00();
  (*G_00658c00)(*(uint64_t *)(v16 + 0x40));
  rt_003489c0();
  (*G_00658c00)();
  rt_0034b8bc();
  rt_003510c4();
  (*v36)();
  rt_00350704();
  rt_00350524();
  (*v29)();
  rt_0034c3c4();
  rt_00350600(param_3);
  rt_00377bec();
  rt_00349fe0();
  rt_00351354();
  rt_0034d344();
  v6 = (*v24)();
  rt_00353930(v10);
  (*v22)();
  if ((v6 & 1) != 0) {
    rt_0031afcc(param_3);
    v8 = rt_00353468();
    rt_0035430c(v8,0xffffffffffffffff);
    (*v18)();
    (*v22)();
    rt_003504a0();
    (*v23)();
  }
  rt_00352ecc(param_3);
  rt_0035430c(v47);
  rt_00352b98();
  v3 = (code *)(*v14)();
  rt_00356924();
  (*v26)();
  rt_00351cac();
  (*v3)();
  rt_00350920();
  rt_00351e3c();
  v9 = rt_0031be78();
  av50 = rt_00353124(&stack_ptr,v9,v42 + *(int *)(v9 + 0x2c));
  (*v34)(av50.lo,av50.hi,v5);
  rt_0034e1b0();
  if ((bool)v45) {
    rt_00310924(param_4);
    rt_00351184();
    rt_0035084c();
    (*v27)();
    v1 = v35 + 1;
    rt_003514e8(*v1);
    (*v20)();
  }
  else {
    rt_00350b18();
    (*v12)();
    v1 = v35;
  }
  v3 = (code *)rt_000277b8(param_4);
  rt_0034c3c4();
  rt_00350b78();
  rt_00377bec();
  rt_00027754();
  v2 = (code *)rt_0014ae44();
  rt_00354134();
  rt_00359ca4();
  while( true ) {
    rt_0035084c(v46);
    (*v3)();
    rt_00350c38();
    rt_00351c94();
    v6 = (*v2)();
    v4 = (code *)*v19;
    rt_000dbd0c();
    (*v4)();
    if ((v6 & 1) == 0) break;
    rt_00350b3c();
    (*v4)(v30);
    rt_00356a70();
    rt_003511a8();
    (*v33)();
    rt_00356810();
    rt_0031afcc();
    v5 = rt_00356670(v39);
    rt_00352bec(v5,0xffffffffffffffff);
    (*v28)();
    rt_0035190c();
    (*v22)();
    rt_0034f9ec(&stack_ptr);
    rt_00351ba0();
    (*v13)();
    rt_00351178(v47);
    rt_00353734();
    (*v31)();
    av50 = rt_003519a8();
    rt_00354b74(v11 & 0xffffffffffff | 0xe3ba000000000000,av50.lo,av50.hi,
                 v38);
    (*v17)();
    rt_0034c3b4();
    (*v42)();
    rt_00350704();
    rt_00356230();
    rt_003505e8();
    (*v15)();
  }
  rt_0031afcc(param_4);
  rt_003526b8(&stack_ptr);
  rt_003518a0(v44,0xffffffffffffffff);
  (*v21)();
  rt_00350b3c();
  (*v4)(v30);
  rt_00356a70();
  rt_003511a8();
  (*v32)();
  rt_0034e094();
  rt_000839d8();
  rt_00353148();
  ((code)FUN_00218714)(v41,v1,v7,param_3,param_4);
  rt_0008e500(v43);
  return;
}



/* FUN_0021a5bc @ 0x0021a5bc   (est. swift_dispatch14)
 * Ghidra: void FUN_0021a5bc( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021a5bc( void){
  code *v2;
  code *v1;
  uint64_t v3;
  
  rt_00084220();
  rt_00349a18();
  rt_00356834();
  rt_0031be78();
  rt_00348d4c();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034a2c0();
  rt_003513b4();
  (*v1)();
  rt_00353378();
  rt_0034b358();
  ((code)FUN_00219a00)();
  rt_0034c9f8();
  (*v2)();
  rt_00084234(v3);
  return;
}



/* FUN_0021a660 @ 0x0021a660   (est. swift_string_distance)
 * Ghidra: long FUN_0021a660(unsigned long param_1, unsigned long param_2, char param_3, unsigned long param_4, unsigned long param_5, char param_6, uint64_t param_7, uint64_t param_8, uint64_t param_9, uint64_t param_10)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021a660(unsigned long param_1, unsigned long param_2, char param_3, unsigned long param_4, unsigned long param_5, char param_6, uint64_t param_7, uint64_t param_8, uint64_t param_9, uint64_t param_10){
  code *v3;
  bool v13;
  unsigned long v10;
  long v11;
  unsigned long v14;
  unsigned long v8;
  char *v5;
  uint64_t v12;
  uint32_t v9;
  unsigned long v4;
  unsigned long v6;
  unsigned long v1;
  long v7;
  rt16 v18;
  uint64_t v2;
  unsigned long v17;
  unsigned long v16;
  unsigned long v15;
  
  v1 = param_4 >> 0xe;
  v6 = param_1 >> 0xe;
  v16 = param_2;
  if (v1 == param_1 >> 0xe) {
    if (param_6 == '\x01') {
      if (param_3 == '\x01') {
        return 0;
      }
    }
    else if (param_3 != '\x01') {
      if (param_5 >> 0xe < param_2 >> 0xe) goto LBL_0021a760;
      goto LBL_0021a78c;
    }
    v2 = 0xc9;
    v5 = &G_005be7c0;
    v12 = 0;
    goto LBL_0021ace0;
  }
  if (v1 < v6) {
LBL_0021a760:
    v12 = rt_002527e8(param_7,param_8,param_9,param_10);
    rt_0029e8dc(v12,0xf,param_7,param_8);
    if (v1 == v6) {
LBL_0021a78c:
      if (param_3 == '\x01' || param_6 == '\x01') {
        return 0;
      }
      v18 = rt_00252e24(param_1,param_7,param_8,param_9,param_10);
      v6 = (uint64_t)v18.hi;
      v1 = (uint64_t)v18.lo;
      v9 = v18._hi32 >> 0x1b & 1;
      if ((v6 & 0x1000000000000000) == 0) {
        v9 = 1;
      }
      if ((param_2 & 0xc) == 4L << (unsigned long)v9) {
        param_2 = rt_0001da84(param_2,v1,v6);
      }
      if ((param_5 & 0xc) == 4L << (unsigned long)v9) {
        param_5 = rt_0001da84(param_5,v1,v6);
      }
      if ((v6 >> 0x3c & 1) == 0) {
        rt_003a25d4(v6);
        return (param_5 >> 0x10) - (param_2 >> 0x10);
      }
      v10 = v1 & 0xffffffffffff;
      if ((v6 & 0x2000000000000000) != 0) {
        v10 = v6 >> 0x38 & 0xf;
      }
      if (param_2 >> 0x10 <= v10 && param_5 >> 0x10 <= v10) {
        v11 = rt_002b15d0(param_2,param_5,v1,v6);
        rt_003a25d4(v6);
        return v11;
      }
      goto LBL_0021abec;
    }
    v18 = rt_00252e24(param_4,param_7,param_8,param_9,param_10);
    v8 = (uint64_t)v18.hi;
    v10 = (uint64_t)v18.lo;
    v1 = v10 & 0xffffffffffff;
    if ((v8 & 0x2000000000000000) != 0) {
      v1 = v8 >> 0x38 & 0xf;
    }
    v9 = v18._hi32 >> 0x1b & 1;
    if ((v8 & 0x1000000000000000) == 0) {
      v9 = 1;
    }
    v14 = 7;
    if (v9 == 0) {
      v14 = 0xb;
    }
    if (param_6 == '\x01') {
      v2 = 0x149;
      goto LBL_0021acac;
    }
    v4 = v14 | v1 << 0x10;
    if ((v14 & 0xc) == 4L << (unsigned long)v9) {
      v4 = rt_0001da84(v4,v10,v8);
    }
    if ((param_5 & 0xc) == 4L << (unsigned long)v9) {
      v17 = rt_0001da84(param_5,v10,v8);
      if ((v8 >> 0x3c & 1) == 0) goto LBL_0021a848;
LBL_0021ab80:
      if (v1 < v4 >> 0x10 || v1 < v17 >> 0x10) goto LBL_0021abec;
      v11 = rt_002b15d0(v4,v17,v10,v8);
      rt_003a25d4(v8);
    }
    else {
      v17 = param_5;
      if ((v8 >> 0x3c & 1) != 0) goto LBL_0021ab80;
LBL_0021a848:
      rt_003a25d4(v8);
      v11 = (v17 >> 0x10) - (v4 >> 0x10);
    }
    v7 = -1;
    v10 = param_4;
    v1 = v6;
    v17 = param_1;
    param_6 = param_3;
  }
  else {
    v18 = rt_00252e24(param_1,param_7,param_8,param_9,param_10);
    v10 = (uint64_t)v18.hi;
    v6 = (uint64_t)v18.lo;
    if (param_3 == '\x01') {
      v2 = 0x14f;
LBL_0021acac:
      v5 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
      v12 = 0x39;
LBL_0021ace0:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v5,v12,2,s_Swift_Flatten_swift_005cf8d0,0x13,2
                   ,v2,1);
    }
    v8 = v6 & 0xffffffffffff;
    if ((v10 & 0x2000000000000000) != 0) {
      v8 = v10 >> 0x38 & 0xf;
    }
    v9 = v18._hi32 >> 0x1b & 1;
    if ((v10 & 0x1000000000000000) == 0) {
      v9 = 1;
    }
    if (v9 == 1) {
      v14 = v8 << 0x10 | 7;
      if ((v10 >> 0x3c & 1) != 0) goto LBL_0021a8ec;
      v4 = 1;
    }
    else {
      v14 = v8 << 0x10 | 0xb;
LBL_0021a8ec:
      v4 = (v6 & 0x800000000000000) >> 0x3b;
    }
    if ((param_2 & 0xc) == 4L << v4) {
      v16 = rt_0001da84(param_2,v6,v10);
    }
    if ((v14 & 0xc) == 4L << v9) {
      v14 = rt_0001da84(v14,v6,v10);
      if ((v10 >> 0x3c & 1) == 0) goto LBL_0021a948;
LBL_0021aad4:
      if (v8 < v16 >> 0x10 || v8 < v14 >> 0x10) goto LBL_0021abec;
      v11 = rt_002b15d0(v16,v14,v6,v10);
      rt_003a25d4(v10);
    }
    else {
      if ((v10 >> 0x3c & 1) != 0) goto LBL_0021aad4;
LBL_0021a948:
      rt_003a25d4(v10);
      v11 = (v14 >> 0x10) - (v16 >> 0x10);
    }
    v7 = 1;
    v10 = param_1;
    v17 = param_4;
    v16 = param_5;
  }
  v15 = rt_00252818(v10,param_7,param_8,param_9,param_10);
  while (v15 >> 0xe < v1) {
    v18 = rt_00252e24(v15,param_7,param_8,param_9,param_10);
    v6 = (uint64_t)v18.hi;
    if ((v6 >> 0x3c & 1) == 0) {
      rt_003a25d4(v6);
      v10 = v18.lo & 0xffffffffffff;
      if ((v6 & 0x2000000000000000) != 0) {
        v10 = v6 >> 0x38 & 0xf;
      }
    }
    else {
      v10 = rt_002b24b8(v18.lo,v6);
      rt_003a25d4(v6);
    }
    v13 = SCARRY8(v11,v10 * v7);
    v11 = v11 + v10 * v7;
    if (v13) {
                    /* WARNING: Does not return */
      v3 = (code *)SW_BREAK(0x21aab4);
      (*v3)();
    }
    rt_00252b68(&v15,param_7,param_8,param_9,param_10);
  }
  if (param_6 == '\x01') {
    return v11;
  }
  v18 = rt_00252e24(v17,param_7,param_8,param_9,param_10);
  v6 = (uint64_t)v18.hi;
  v1 = (uint64_t)v18.lo;
  v9 = v18._hi32 >> 0x1b & 1;
  if ((v6 & 0x1000000000000000) == 0) {
    v9 = 1;
  }
  if ((v16 & 0xc) == 4L << v9) {
    v16 = rt_0001da84(v16,v1,v6);
  }
  if ((v6 >> 0x3c & 1) == 0) {
    rt_003a25d4(v6);
    v16 = v16 >> 0x10;
  }
  else {
    v10 = v1 & 0xffffffffffff;
    if ((v6 & 0x2000000000000000) != 0) {
      v10 = v6 >> 0x38 & 0xf;
    }
    if (v10 < v16 >> 0x10) {
LBL_0021abec:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                   s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xcf,1);
    }
    v16 = rt_002b15d0(0xf,v16,v1,v6);
    rt_003a25d4(v6);
  }
  if (SCARRY8(v11,v16 * v7)) {
                    /* WARNING: Does not return */
    v3 = (code *)SW_BREAK(0x21ab60);
    (*v3)();
  }
  return v11 + v16 * v7;
}



/* FUN_0021acec @ 0x0021acec   (est. swift_string_distance_utf8)
 * Ghidra: long FUN_0021acec(unsigned long param_1, long param_2, char param_3, unsigned long param_4, long param_5, char param_6, uint64_t param_7, uint64_t param_8, uint64_t param_9, uint64_t param_10)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021acec(unsigned long param_1, long param_2, char param_3, unsigned long param_4, long param_5, char param_6, uint64_t param_7, uint64_t param_8, uint64_t param_9, uint64_t param_10){
  long v7;
  long v11;
  code *v3;
  bool v12;
  uint32_t v13;
  unsigned long v8;
  char *v2;
  uint64_t v10;
  unsigned long v9;
  long v1;
  unsigned long v4;
  long v6;
  rt16 v17;
  uint64_t v5;
  unsigned long v16;
  long v14;
  unsigned long v15;
  
  v4 = param_4 >> 0xe;
  v9 = param_1 >> 0xe;
  if (v4 == param_1 >> 0xe) {
    if (param_6 == '\x01') {
      if (param_3 == '\x01') {
        return 0;
      }
    }
    else if (param_3 != '\x01') {
      if (param_2 <= param_5) goto LBL_0021ae60;
      goto LBL_0021ae34;
    }
    v5 = 0xc9;
    v2 = &G_005be7c0;
    v10 = 0;
  }
  else {
    if (v4 < v9) {
LBL_0021ae34:
      v10 = rt_002527e8(param_7,param_8,param_9,param_10);
      rt_002a9d64(v10,0xf,param_7,param_8);
      if (v4 == v9) {
LBL_0021ae60:
        if (param_3 == '\x01' || param_6 == '\x01') {
          return 0;
        }
        v13 = rt_002532a8(param_1,param_7,param_8,param_9,param_10);
        v10 = 3;
        if (0xffff < v13) {
          v10 = 4;
        }
        v5 = 2;
        if (0x7ff < v13) {
          v5 = v10;
        }
        v10 = 1;
        if (0x7f < v13) {
          v10 = v5;
        }
        v17 = rt_001dff60(0,v10);
        rt_0019fe7c(param_2,v17.lo,v17.hi);
        v17 = rt_001dff60(0,v10);
        rt_0019fe7c(param_5,v17.lo,v17.hi);
        if (SBORROW8(param_5,param_2)) {
                    /* WARNING: Does not return */
          v3 = (code *)SW_BREAK(0x21b10c);
          (*v3)();
        }
        return param_5 - param_2;
      }
      v13 = rt_002532a8(param_4,param_7,param_8,param_9,param_10);
      v1 = 3;
      if (0xffff < v13) {
        v1 = 4;
      }
      v6 = 2;
      if (0x7ff < v13) {
        v6 = v1;
      }
      v1 = 1;
      if (0x7f < v13) {
        v1 = v6;
      }
      if (param_6 != '\x01') {
        v17 = rt_001dff60(0,v1);
        rt_0019fe7c(v1,v17.lo,v17.hi);
        v17 = rt_001dff60(0,v1);
        rt_0019fe7c(param_5,v17.lo,v17.hi);
        v6 = param_5 - v1;
        if (SBORROW8(param_5,v1)) {
                    /* WARNING: Does not return */
          v3 = (code *)SW_BREAK(0x21b108);
          (*v3)();
        }
        v1 = -1;
        v8 = param_4;
        v4 = v9;
        v16 = param_1;
        v14 = param_2;
        param_6 = param_3;
LBL_0021af20:
        v15 = rt_00252a64(v8,param_7,param_8,param_9,param_10);
        while (v15 >> 0xe < v4) {
          v13 = rt_002532a8(v15,param_7,param_8,param_9,param_10);
          v7 = 3;
          if (0xffff < v13) {
            v7 = 4;
          }
          v11 = 2;
          if (0x7ff < v13) {
            v11 = v7;
          }
          v7 = 1;
          if (0x7f < v13) {
            v7 = v11;
          }
          v12 = SCARRY8(v6,v7 * v1);
          v6 = v6 + v7 * v1;
          if (v12) {
                    /* WARNING: Does not return */
            v3 = (code *)SW_BREAK(0x21b100);
            (*v3)();
          }
          rt_00252d38(&v15,param_7,param_8,param_9,param_10);
        }
        if (param_6 != '\x01') {
          v13 = rt_002532a8(v16,param_7,param_8,param_9,param_10);
          v10 = 3;
          if (0xffff < v13) {
            v10 = 4;
          }
          v5 = 2;
          if (0x7ff < v13) {
            v5 = v10;
          }
          v10 = 1;
          if (0x7f < v13) {
            v10 = v5;
          }
          v17 = rt_001dff60(0,v10);
          rt_0019fe7c(0,v17.lo,v17.hi);
          v17 = rt_001dff60(0,v10);
          rt_0019fe7c(v14,v17.lo,v17.hi);
          v12 = SCARRY8(v6,v14 * v1);
          v6 = v6 + v14 * v1;
          if (v12) {
                    /* WARNING: Does not return */
            v3 = (code *)SW_BREAK(0x21b04c);
            (*v3)();
          }
        }
        return v6;
      }
      v5 = 0x149;
    }
    else {
      v13 = rt_002532a8(param_1,param_7,param_8,param_9,param_10);
      if (param_3 != '\x01') {
        v1 = 3;
        if (0xffff < v13) {
          v1 = 4;
        }
        v6 = 2;
        if (0x7ff < v13) {
          v6 = v1;
        }
        v1 = 1;
        if (0x7f < v13) {
          v1 = v6;
        }
        v17 = rt_001dff60(0,v1);
        rt_0019fe7c(param_2,v17.lo,v17.hi);
        v17 = rt_001dff60(0,v1);
        rt_0019fe7c(v1,v17.lo,v17.hi);
        v6 = v1 - param_2;
        if (SBORROW8(v1,param_2)) {
                    /* WARNING: Does not return */
          v3 = (code *)SW_BREAK(0x21b104);
          (*v3)();
        }
        v1 = 1;
        v8 = param_1;
        v16 = param_4;
        v14 = param_5;
        goto LBL_0021af20;
      }
      v5 = 0x14f;
    }
    v2 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
    v10 = 0x39;
  }
                    /* WARNING: Subroutine does not return */
  rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v2,v10,2,s_Swift_Flatten_swift_005cf8d0,0x13,2,
               v5,1);
}



/* FUN_0021b1a4 @ 0x0021b1a4   (est. swift_string_distance2)
 * Ghidra: long FUN_0021b1a4(unsigned long param_1, unsigned long param_2, char param_3, unsigned long param_4, unsigned long param_5, char param_6)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021b1a4(unsigned long param_1, unsigned long param_2, char param_3, unsigned long param_4, unsigned long param_5, char param_6){
  unsigned long v9;
  uint64_t v10;
  uint64_t v12;
  code *v5;
  bool v13;
  unsigned long v11;
  uint64_t v15;
  unsigned long v14;
  long v16;
  unsigned long v6;
  char *v1;
  uint64_t v3;
  uint32_t v7;
  uint64_t *v17;
  unsigned long v8;
  unsigned long v4;
  rt16 av96;
  uint64_t v2;
  unsigned long v22;
  unsigned long v21;
  unsigned long v20;
  long v23;
  rt16 v19;
  unsigned long v18;
  unsigned long uStack_68;
  
  v3 = *v17;
  v10 = v17[1];
  v2 = v17[2];
  v12 = v17[3];
  v5 = (code *)v17[4];
  v4 = param_4 >> 0xe;
  v8 = param_1 >> 0xe;
  v20 = param_2;
  if (v4 == param_1 >> 0xe) {
    if (param_6 == '\x01') {
      if (param_3 == '\x01') {
        return 0;
      }
    }
    else if (param_3 != '\x01') {
      if (param_5 >> 0xe < param_2 >> 0xe) goto LBL_0021b2d0;
      goto LBL_0021b2f4;
    }
    v2 = 0xc9;
    v1 = &G_005be7c0;
    v3 = 0;
    goto LBL_0021b910;
  }
  if (v4 < v8) {
LBL_0021b2d0:
    rt_002b4120(v10,v3,v3,v10,v2,v12);
    if (v4 == v8) {
LBL_0021b2f4:
      if (param_3 == '\x01' || param_6 == '\x01') {
        return 0;
      }
      v19 = rt_002b439c(param_1,v3,v10,v2,v12);
      v3 = (uint64_t)v19.hi;
      (*v5)(&v18,v19);
      rt_003a25d4(v3);
      v7 = (uint32_t)(v18 >> 0x3b) & 1;
      if ((uStack_68 & 0x1000000000000000) == 0) {
        v7 = 1;
      }
      if ((param_2 & 0xc) == 4L << (unsigned long)v7) {
        param_2 = rt_0001da84(param_2,v18,uStack_68);
      }
      if ((param_5 & 0xc) == 4L << (unsigned long)v7) {
        param_5 = rt_0001da84(param_5,v18,uStack_68);
      }
      if ((uStack_68 >> 0x3c & 1) == 0) {
        rt_003a25d4(uStack_68);
        return (param_5 >> 0x10) - (param_2 >> 0x10);
      }
      v4 = v18 & 0xffffffffffff;
      if ((uStack_68 & 0x2000000000000000) != 0) {
        v4 = uStack_68 >> 0x38 & 0xf;
      }
      if (param_2 >> 0x10 <= v4 && param_5 >> 0x10 <= v4) {
        v16 = rt_002b15d0(param_2,param_5,v18,uStack_68);
        rt_003a25d4(uStack_68);
        return v16;
      }
      goto LBL_0021b81c;
    }
    v19 = rt_002b439c(param_4,v3,v10,v2,v12);
    v15 = (uint64_t)v19.hi;
    (*v5)(&v18,v19);
    rt_003a25d4(v15);
    v9 = uStack_68;
    v14 = v18;
    v4 = v18 & 0xffffffffffff;
    if ((uStack_68 & 0x2000000000000000) != 0) {
      v4 = uStack_68 >> 0x38 & 0xf;
    }
    v7 = (uint32_t)(v18 >> 0x3b) & 1;
    if ((uStack_68 & 0x1000000000000000) == 0) {
      v7 = 1;
    }
    v6 = 7;
    if (v7 == 0) {
      v6 = 0xb;
    }
    if (param_6 == '\x01') {
      v2 = 0x149;
      goto LBL_0021b8dc;
    }
    v11 = v6 | v4 << 0x10;
    if ((v6 & 0xc) == 4L << (unsigned long)v7) {
      v11 = rt_0001da84(v11,v18,uStack_68);
    }
    if ((param_5 & 0xc) == 4L << (unsigned long)v7) {
      v22 = rt_0001da84(param_5,v14,v9);
      if ((v9 >> 0x3c & 1) == 0) goto LBL_0021b3d0;
LBL_0021b7b4:
      if (v4 < v11 >> 0x10 || v4 < v22 >> 0x10) goto LBL_0021b81c;
      v16 = rt_002b15d0(v11,v22,v14,v9);
      rt_003a25d4(v9);
    }
    else {
      v22 = param_5;
      if ((v9 >> 0x3c & 1) != 0) goto LBL_0021b7b4;
LBL_0021b3d0:
      rt_003a25d4(v9);
      v16 = (v22 >> 0x10) - (v11 >> 0x10);
    }
    v23 = -1;
    v14 = param_4;
    v4 = v8;
    v21 = param_1;
    param_6 = param_3;
  }
  else {
    v19 = rt_002b439c(param_1,v3,v10,v2,v12);
    v15 = (uint64_t)v19.hi;
    (*v5)(&v18,v19);
    rt_003a25d4(v15);
    v14 = uStack_68;
    v8 = v18;
    if (param_3 == '\x01') {
      v2 = 0x14f;
LBL_0021b8dc:
      v1 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
      v3 = 0x39;
LBL_0021b910:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v1,v3,2,s_Swift_Flatten_swift_005cf8d0,0x13
                   ,2,v2,1);
    }
    v9 = v18 & 0xffffffffffff;
    if ((uStack_68 & 0x2000000000000000) != 0) {
      v9 = uStack_68 >> 0x38 & 0xf;
    }
    v7 = (uint32_t)(v18 >> 0x3b) & 1;
    if ((uStack_68 & 0x1000000000000000) == 0) {
      v7 = 1;
    }
    if (v7 == 1) {
      v6 = v9 << 0x10 | 7;
      if ((uStack_68 >> 0x3c & 1) != 0) goto LBL_0021b4a0;
      v11 = 1;
    }
    else {
      v6 = v9 << 0x10 | 0xb;
LBL_0021b4a0:
      v11 = (v18 & 0x800000000000000) >> 0x3b;
    }
    if ((param_2 & 0xc) == 4L << v11) {
      v20 = rt_0001da84(param_2,v18,uStack_68);
    }
    if ((v6 & 0xc) == 4L << v7) {
      v6 = rt_0001da84(v6,v8,v14);
      if ((v14 >> 0x3c & 1) == 0) goto LBL_0021b4f4;
LBL_0021b704:
      if (v9 < v20 >> 0x10 || v9 < v6 >> 0x10) goto LBL_0021b81c;
      v16 = rt_002b15d0(v20,v6,v8,v14);
      rt_003a25d4(v14);
    }
    else {
      if ((v14 >> 0x3c & 1) != 0) goto LBL_0021b704;
LBL_0021b4f4:
      rt_003a25d4(v14);
      v16 = (v6 >> 0x10) - (v20 >> 0x10);
    }
    v23 = 1;
    v14 = param_1;
    v21 = param_4;
    v20 = param_5;
  }
  v15 = rt_002ab6a0(v14,v3,v10,v2,v12);
  v8 = rt_002b3b84(v15,v3,v10,v2,v12);
  while (v8 >> 0xe < v4) {
    av96 = rt_002b439c(v8,v3,v10,v2,v12);
    v19 = rt16_mklo(av96.lo);
    (*v5)(&v18,v19);
    rt_003a25d4(av96.hi);
    v9 = uStack_68;
    v14 = v18;
    if ((uStack_68 >> 0x3c & 1) == 0) {
      rt_003a25d4(uStack_68);
      v14 = v14 & 0xffffffffffff;
      if ((v9 & 0x2000000000000000) != 0) {
        v14 = v9 >> 0x38 & 0xf;
      }
    }
    else {
      v14 = rt_002b24b8(v18,uStack_68);
      rt_003a25d4(v9);
    }
    v13 = SCARRY8(v16,v14 * v23);
    v16 = v16 + v14 * v23;
    if (v13) {
                    /* WARNING: Does not return */
      v5 = (code *)SW_BREAK(0x21b6e4);
      (*v5)();
    }
    v15 = rt_002ab6a0(v8,v3,v10,v2,v12);
    v8 = rt_002b3b84(v15,v3,v10,v2,v12);
  }
  if (param_6 == '\x01') {
    return v16;
  }
  av96 = rt_002b439c(v21,v3,v10,v2,v12);
  v19 = rt16_mklo(av96.lo);
  (*v5)(&v18,v19);
  rt_003a25d4(av96.hi);
  v7 = (uint32_t)(v18 >> 0x3b) & 1;
  if ((uStack_68 & 0x1000000000000000) == 0) {
    v7 = 1;
  }
  if ((v20 & 0xc) == 4L << v7) {
    v20 = rt_0001da84(v20,v18,uStack_68);
  }
  if ((uStack_68 >> 0x3c & 1) == 0) {
    rt_003a25d4(uStack_68);
    v20 = v20 >> 0x10;
  }
  else {
    v4 = v18 & 0xffffffffffff;
    if ((uStack_68 & 0x2000000000000000) != 0) {
      v4 = uStack_68 >> 0x38 & 0xf;
    }
    if (v4 < v20 >> 0x10) {
LBL_0021b81c:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                   s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xcf,1);
    }
    v20 = rt_002b15d0(0xf,v20,v18,uStack_68);
    rt_003a25d4(uStack_68);
  }
  if (SCARRY8(v16,v20 * v23)) {
                    /* WARNING: Does not return */
    v5 = (code *)SW_BREAK(0x21b78c);
    (*v5)();
  }
  return v16 + v20 * v23;
}



/* FUN_0021b91c @ 0x0021b91c   (est. swift_string_distance3)
 * Ghidra: long FUN_0021b91c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, long param_7, code * param_8, uint64_t param_9)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021b91c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, long param_7, code * param_8, uint64_t param_9){
  code *v2;
  bool v13;
  unsigned long v10;
  unsigned long v15;
  long v12;
  char *v3;
  uint64_t v14;
  uint32_t v11;
  unsigned long v9;
  unsigned long v4;
  long v5;
  long v8;
  unsigned long v6;
  uint64_t *v1;
  rt16 v19;
  uint64_t v7;
  unsigned long v18;
  uint64_t v17;
  uint64_t uStack_78;
  unsigned long v16;
  unsigned long uStack_68;
  
  if (param_4 == param_1) {
    if (param_6 == '\x01') {
      if (param_3 == '\x01') {
        return 0;
      }
    }
    else if (param_3 != '\x01') {
      v19 = rt_0025346c(param_4,param_7,param_8,param_9);
      v4 = (uint64_t)v19.hi;
      v10 = (uint64_t)v19.lo;
      v11 = v19._hi32 >> 0x1b & 1;
      if ((v4 & 0x1000000000000000) == 0) {
        v11 = 1;
      }
      if ((param_2 & 0xc) == 4L << (unsigned long)v11) {
        param_2 = rt_0001da84(param_2,v10,v4);
      }
      if ((param_5 & 0xc) == 4L << (unsigned long)v11) {
        param_5 = rt_0001da84(param_5,v10,v4);
      }
      if ((v4 >> 0x3c & 1) == 0) {
        rt_003a25d4(v4);
        return (param_5 >> 0x10) - (param_2 >> 0x10);
      }
      v15 = v10 & 0xffffffffffff;
      if ((v4 & 0x2000000000000000) != 0) {
        v15 = v4 >> 0x38 & 0xf;
      }
      if (param_2 >> 0x10 <= v15 && param_5 >> 0x10 <= v15) {
        v12 = rt_002b15d0(param_2,param_5,v10,v4);
        rt_003a25d4(v4);
        return v12;
      }
      goto LBL_0021be08;
    }
    v7 = 0xc9;
    v3 = &G_005be7c0;
    v14 = 0;
    goto LBL_0021bf54;
  }
  v18 = param_2;
  if (param_4 < param_1) {
    v19 = rt_0025346c(param_4,param_7,param_8,param_9);
    v15 = (uint64_t)v19.hi;
    v4 = (uint64_t)v19.lo;
    v10 = v4 & 0xffffffffffff;
    if ((v15 & 0x2000000000000000) != 0) {
      v10 = v15 >> 0x38 & 0xf;
    }
    v11 = v19._hi32 >> 0x1b & 1;
    if ((v15 & 0x1000000000000000) == 0) {
      v11 = 1;
    }
    v6 = 7;
    if (v11 == 0) {
      v6 = 0xb;
    }
    if (param_6 == '\x01') {
      v7 = 0x149;
LBL_0021bf20:
      v3 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
      v14 = 0x39;
LBL_0021bf54:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v3,v14,2,s_Swift_Flatten_swift_005cf8d0,0x13,2
                   ,v7,1);
    }
    v9 = v6 | v10 << 0x10;
    if ((v6 & 0xc) == 4L << (unsigned long)v11) {
      v9 = rt_0001da84(v9,v4,v15);
    }
    if ((param_5 & 0xc) == 4L << (unsigned long)v11) {
      param_5 = rt_0001da84(param_5,v4,v15);
      if ((v15 >> 0x3c & 1) != 0) goto LBL_0021bd40;
LBL_0021ba1c:
      rt_003a25d4(v15);
      v12 = (param_5 >> 0x10) - (v9 >> 0x10);
    }
    else {
      if ((v15 >> 0x3c & 1) == 0) goto LBL_0021ba1c;
LBL_0021bd40:
      if (v10 < v9 >> 0x10 || v10 < param_5 >> 0x10) goto LBL_0021be08;
      v12 = rt_002b15d0(v9,param_5,v4,v15);
      rt_003a25d4(v15);
    }
    v8 = -1;
    v5 = param_1;
    param_1 = param_4;
    param_6 = param_3;
  }
  else {
    v19 = rt_0025346c(param_1,param_7,param_8,param_9);
    v4 = (uint64_t)v19.hi;
    v10 = (uint64_t)v19.lo;
    if (param_3 == '\x01') {
      v7 = 0x14f;
      goto LBL_0021bf20;
    }
    v15 = v10 & 0xffffffffffff;
    if ((v4 & 0x2000000000000000) != 0) {
      v15 = v4 >> 0x38 & 0xf;
    }
    v11 = v19._hi32 >> 0x1b & 1;
    if ((v4 & 0x1000000000000000) == 0) {
      v11 = 1;
    }
    if (v11 == 1) {
      v6 = v15 << 0x10 | 7;
      if ((v4 >> 0x3c & 1) != 0) goto LBL_0021bb18;
      v9 = 1;
    }
    else {
      v6 = v15 << 0x10 | 0xb;
LBL_0021bb18:
      v9 = (v10 & 0x800000000000000) >> 0x3b;
    }
    if ((param_2 & 0xc) == 4L << v9) {
      v18 = rt_0001da84(param_2,v10,v4);
    }
    if ((v6 & 0xc) == 4L << v11) {
      v6 = rt_0001da84(v6,v10,v4);
      if ((v4 >> 0x3c & 1) != 0) goto LBL_0021bdf4;
LBL_0021bb6c:
      rt_003a25d4(v4);
      v12 = (v6 >> 0x10) - (v18 >> 0x10);
    }
    else {
      if ((v4 >> 0x3c & 1) == 0) goto LBL_0021bb6c;
LBL_0021bdf4:
      if (v15 < v18 >> 0x10 || v15 < v6 >> 0x10) goto LBL_0021be08;
      v12 = rt_002b15d0(v18,v6,v10,v4);
      rt_003a25d4(v4);
    }
    v8 = 1;
    v5 = param_4;
    v18 = param_5;
  }
  v10 = param_1 + 1;
  if (SCARRY8(param_1,1)) {
                    /* WARNING: Does not return */
    v2 = (code *)SW_BREAK(0x21bd28);
    (*v2)();
  }
  if ((long)v10 < v5) {
    v1 = (uint64_t *)(param_7 + param_1 * 0x10 + 0x38);
    v4 = v10;
    do {
      if (((long)v10 < 0) || (*(unsigned long *)(param_7 + 0x10) <= v4)) {
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Index_out_of_range_005cd940,0x12,2,
                     s_Swift_ContiguousArrayBuffer_swif_005cd960,0x21,2,0x2b4,1);
      }
      v17 = v1[-1];
      v14 = *v1;
      uStack_78 = v14;
      rt_0036b270(v14);
      (*param_8)(&v16,&v17);
      rt_003a25d4(v14);
      v6 = uStack_68;
      v15 = v16;
      if ((uStack_68 >> 0x3c & 1) == 0) {
        rt_003a25d4(uStack_68);
        v15 = v15 & 0xffffffffffff;
        if ((v6 & 0x2000000000000000) != 0) {
          v15 = v6 >> 0x38 & 0xf;
        }
      }
      else {
        v15 = rt_002b24b8(v16,uStack_68);
        rt_003a25d4(v6);
      }
      v13 = SCARRY8(v12,v15 * v8);
      v12 = v12 + v15 * v8;
      if (v13) {
                    /* WARNING: Does not return */
        v2 = (code *)SW_BREAK(0x21bd24);
        (*v2)();
      }
      v4 = v4 + 1;
      v1 = v1 + 2;
    } while ((long)v4 < v5);
  }
  if (param_6 == '\x01') {
    return v12;
  }
  v19 = rt_0025346c(v5,param_7,param_8,param_9);
  v4 = (uint64_t)v19.hi;
  v10 = (uint64_t)v19.lo;
  v11 = v19._hi32 >> 0x1b & 1;
  if ((v4 & 0x1000000000000000) == 0) {
    v11 = 1;
  }
  if ((v18 & 0xc) == 4L << v11) {
    v18 = rt_0001da84(v18,v10,v4);
  }
  if ((v4 >> 0x3c & 1) == 0) {
    rt_003a25d4(v4);
    v18 = v18 >> 0x10;
  }
  else {
    v15 = v10 & 0xffffffffffff;
    if ((v4 & 0x2000000000000000) != 0) {
      v15 = v4 >> 0x38 & 0xf;
    }
    if (v15 < v18 >> 0x10) {
LBL_0021be08:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                   s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xcf,1);
    }
    v18 = rt_002b15d0(0xf,v18,v10,v4);
    rt_003a25d4(v4);
  }
  if (!SCARRY8(v12,v18 * v8)) {
    return v12 + v18 * v8;
  }
                    /* WARNING: Does not return */
  v2 = (code *)SW_BREAK(0x21bea8);
  (*v2)();
}



/* FUN_0021bf60 @ 0x0021bf60   (est. swift_string_distance_utf8_2)
 * Ghidra: long FUN_0021bf60(long param_1, long param_2, char param_3, long param_4, long param_5, char param_6, uint64_t param_7, code * param_8, uint64_t param_9)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021bf60(long param_1, long param_2, char param_3, long param_4, long param_5, char param_6, uint64_t param_7, code * param_8, uint64_t param_9){
  long v4;
  code *v3;
  bool v6;
  uint32_t v9;
  long v8;
  char *v1;
  uint64_t v7;
  long v5;
  long v10;
  rt16 v14;
  uint64_t v2;
  long v11;
  uint32_t v12;
  uint32_t v13;
  
  if (param_4 == param_1) {
    if (param_6 == '\x01') {
      if (param_3 == '\x01') {
        return 0;
      }
    }
    else if (param_3 != '\x01') {
      if (param_2 <= param_5) goto LBL_0021c0ac;
      goto LBL_0021c084;
    }
    v2 = 0xc9;
    v1 = &G_005be7c0;
    v7 = 0;
    goto LBL_0021c410;
  }
  if (param_4 < param_1) {
LBL_0021c084:
    rt_0019fe7c(1,0,1);
    rt_0019fe7c(0,0,1);
    if (param_4 == param_1) {
LBL_0021c0ac:
      if (param_3 == '\x01' || param_6 == '\x01') {
        return 0;
      }
      v9 = rt_002534e4(param_1,param_7,param_8,param_9);
      v7 = 3;
      if (0xffff < v9) {
        v7 = 4;
      }
      v2 = 2;
      if (0x7ff < v9) {
        v2 = v7;
      }
      v7 = 1;
      if (0x7f < v9) {
        v7 = v2;
      }
      v14 = rt_001dff60(0,v7);
      rt_0019fe7c(param_2,v14.lo,v14.hi);
      v14 = rt_001dff60(0,v7);
      rt_0019fe7c(param_5,v14.lo,v14.hi);
      if (SBORROW8(param_5,param_2)) {
                    /* WARNING: Does not return */
        v3 = (code *)SW_BREAK(0x21c178);
        (*v3)();
      }
      return param_5 - param_2;
    }
    v9 = rt_002534e4(param_4,param_7,param_8,param_9);
    if (v9 < 0x80) {
      if (param_6 == '\x01') {
LBL_0021c3d4:
        v2 = 0x149;
        goto LBL_0021c3dc;
      }
      v8 = 1;
    }
    else {
      if (param_6 == '\x01') goto LBL_0021c3d4;
      v5 = 3;
      if (0xffff < v9) {
        v5 = 4;
      }
      v8 = 2;
      if (0x7ff < v9) {
        v8 = v5;
      }
    }
    v14 = rt_001dff60(0,v8);
    rt_0019fe7c(v8,v14.lo,v14.hi);
    v14 = rt_001dff60(0,v8);
    rt_0019fe7c(param_5,v14.lo,v14.hi);
    v10 = param_5 - v8;
    if (SBORROW8(param_5,v8)) {
                    /* WARNING: Does not return */
      v3 = (code *)SW_BREAK(0x21c388);
      (*v3)();
    }
    v11 = -1;
    param_5 = param_2;
    v5 = param_1;
    param_1 = param_4;
    param_6 = param_3;
LBL_0021c1f4:
    v8 = rt_00252b04(param_1,param_7,param_8,param_9);
    if (v8 < v5) {
      v6 = v8 == 0;
      do {
        if (!v6) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Index_out_of_range_005cd940,0x12,2,
                       s_Swift_CollectionOfOne_swift_005d0d40,0x1b,2,0x84,1);
        }
        v12 = (uint32_t)param_7;
        (*param_8)(&v13,&v12);
        v8 = 3;
        if (0xffff < v13) {
          v8 = 4;
        }
        v4 = 2;
        if (0x7ff < v13) {
          v4 = v8;
        }
        v8 = 1;
        if (0x7f < v13) {
          v8 = v4;
        }
        v6 = SCARRY8(v10,v8 * v11);
        v10 = v10 + v8 * v11;
        if (v6) {
                    /* WARNING: Does not return */
          v3 = (code *)SW_BREAK(0x21c380);
          (*v3)();
        }
        v6 = false;
      } while (1 < v5);
    }
    if (param_6 != '\x01') {
      v9 = rt_002534e4(v5,param_7,param_8,param_9);
      v7 = 3;
      if (0xffff < v9) {
        v7 = 4;
      }
      v2 = 2;
      if (0x7ff < v9) {
        v2 = v7;
      }
      v7 = 1;
      if (0x7f < v9) {
        v7 = v2;
      }
      v14 = rt_001dff60(0,v7);
      rt_0019fe7c(0,v14.lo,v14.hi);
      v14 = rt_001dff60(0,v7);
      rt_0019fe7c(param_5,v14.lo,v14.hi);
      v6 = SCARRY8(v10,param_5 * v11);
      v10 = v10 + param_5 * v11;
      if (v6) {
                    /* WARNING: Does not return */
        v3 = (code *)SW_BREAK(0x21c384);
        (*v3)();
      }
    }
    return v10;
  }
  v9 = rt_002534e4(param_1,param_7,param_8,param_9);
  if (param_3 != '\x01') {
    v5 = 3;
    if (0xffff < v9) {
      v5 = 4;
    }
    v10 = 2;
    if (0x7ff < v9) {
      v10 = v5;
    }
    v5 = 1;
    if (0x7f < v9) {
      v5 = v10;
    }
    v14 = rt_001dff60(0,v5);
    rt_0019fe7c(param_2,v14.lo,v14.hi);
    v14 = rt_001dff60(0,v5);
    rt_0019fe7c(v5,v14.lo,v14.hi);
    v10 = v5 - param_2;
    if (SBORROW8(v5,param_2)) {
                    /* WARNING: Does not return */
      v3 = (code *)SW_BREAK(0x21c334);
      (*v3)();
    }
    v11 = 1;
    v5 = param_4;
    goto LBL_0021c1f4;
  }
  v2 = 0x14f;
LBL_0021c3dc:
  v1 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
  v7 = 0x39;
LBL_0021c410:
                    /* WARNING: Subroutine does not return */
  rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v1,v7,2,s_Swift_Flatten_swift_005cf8d0,0x13,2,
               v2,1);
}



/* FUN_0021c41c @ 0x0021c41c   (est. swift_string_distance4)
 * Ghidra: long FUN_0021c41c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, uint64_t param_7, uint64_t param_8, code * param_9, uint64_t param_10)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021c41c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, uint64_t param_7, uint64_t param_8, code * param_9, uint64_t param_10){
  code *v3;
  bool v13;
  long v9;
  unsigned long v15;
  long v12;
  unsigned long v10;
  unsigned long v14;
  char *v2;
  uint64_t v11;
  uint32_t v4;
  unsigned long v6;
  long v8;
  unsigned long v5;
  long v1;
  rt16 v19;
  uint64_t v7;
  unsigned long v18;
  uint64_t v17;
  uint64_t uStack_78;
  unsigned long v16;
  unsigned long uStack_68;
  
  if (param_4 == param_1) {
    if (param_6 == '\x01') {
      if (param_3 == '\x01') {
        return 0;
      }
    }
    else if (param_3 != '\x01') {
      if (param_5 >> 0xe < param_2 >> 0xe) goto LBL_0021c508;
      goto LBL_0021c530;
    }
    v7 = 0xc9;
    v2 = &G_005be7c0;
    v11 = 0;
    goto LBL_0021cac4;
  }
  if (param_4 < param_1) {
LBL_0021c508:
    rt_0019fe7c(1,0,1);
    rt_0019fe7c(0,0,1);
    if (param_4 == param_1) {
LBL_0021c530:
      if (param_3 == '\x01' || param_6 == '\x01') {
        return 0;
      }
      v19 = rt_00253570(param_1,param_7,param_8,param_9,param_10);
      v10 = (uint64_t)v19.hi;
      v15 = (uint64_t)v19.lo;
      v4 = v19._hi32 >> 0x1b & 1;
      if ((v10 & 0x1000000000000000) == 0) {
        v4 = 1;
      }
      if ((param_2 & 0xc) == 4L << (unsigned long)v4) {
        param_2 = rt_0001da84(param_2,v15,v10);
      }
      if ((param_5 & 0xc) == 4L << (unsigned long)v4) {
        param_5 = rt_0001da84(param_5,v15,v10);
      }
      if ((v10 >> 0x3c & 1) == 0) {
        rt_003a25d4(v10);
        return (param_5 >> 0x10) - (param_2 >> 0x10);
      }
      v14 = v15 & 0xffffffffffff;
      if ((v10 & 0x2000000000000000) != 0) {
        v14 = v10 >> 0x38 & 0xf;
      }
      if (param_2 >> 0x10 <= v14 && param_5 >> 0x10 <= v14) {
        v12 = rt_002b15d0(param_2,param_5,v15,v10);
        rt_003a25d4(v10);
        return v12;
      }
      goto LBL_0021c9cc;
    }
    v19 = rt_00253570(param_4,param_7,param_8,param_9,param_10);
    v14 = (uint64_t)v19.hi;
    v10 = (uint64_t)v19.lo;
    v15 = v10 & 0xffffffffffff;
    if ((v14 & 0x2000000000000000) != 0) {
      v15 = v14 >> 0x38 & 0xf;
    }
    v4 = v19._hi32 >> 0x1b & 1;
    if ((v14 & 0x1000000000000000) == 0) {
      v4 = 1;
    }
    v6 = 7;
    if (v4 == 0) {
      v6 = 0xb;
    }
    if (param_6 == '\x01') {
      v7 = 0x149;
      goto LBL_0021ca90;
    }
    v5 = v6 | v15 << 0x10;
    if ((v6 & 0xc) == 4L << (unsigned long)v4) {
      v5 = rt_0001da84(v5,v10,v14);
    }
    if ((param_5 & 0xc) == 4L << (unsigned long)v4) {
      param_5 = rt_0001da84(param_5,v10,v14);
      if ((v14 >> 0x3c & 1) == 0) goto LBL_0021c5e4;
LBL_0021c960:
      if (v15 < v5 >> 0x10 || v15 < param_5 >> 0x10) goto LBL_0021c9cc;
      v12 = rt_002b15d0(v5,param_5,v10,v14);
      rt_003a25d4(v14);
    }
    else {
      if ((v14 >> 0x3c & 1) != 0) goto LBL_0021c960;
LBL_0021c5e4:
      rt_003a25d4(v14);
      v12 = (param_5 >> 0x10) - (v5 >> 0x10);
    }
    v1 = -1;
    v8 = param_1;
    param_1 = param_4;
    v18 = param_2;
    param_6 = param_3;
  }
  else {
    v19 = rt_00253570(param_1,param_7,param_8,param_9);
    v10 = (uint64_t)v19.hi;
    v15 = (uint64_t)v19.lo;
    if (param_3 == '\x01') {
      v7 = 0x14f;
LBL_0021ca90:
      v2 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
      v11 = 0x39;
LBL_0021cac4:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v2,v11,2,s_Swift_Flatten_swift_005cf8d0,0x13,2
                   ,v7,1);
    }
    v14 = v15 & 0xffffffffffff;
    if ((v10 & 0x2000000000000000) != 0) {
      v14 = v10 >> 0x38 & 0xf;
    }
    v4 = v19._hi32 >> 0x1b & 1;
    if ((v10 & 0x1000000000000000) == 0) {
      v4 = 1;
    }
    if (v4 == 1) {
      v6 = v14 << 0x10 | 7;
      if ((v10 >> 0x3c & 1) != 0) goto LBL_0021c680;
      v5 = 1;
    }
    else {
      v6 = v14 << 0x10 | 0xb;
LBL_0021c680:
      v5 = (v15 & 0x800000000000000) >> 0x3b;
    }
    if ((param_2 & 0xc) == 4L << v5) {
      param_2 = rt_0001da84(param_2,v15,v10);
    }
    if ((v6 & 0xc) == 4L << v4) {
      v6 = rt_0001da84(v6,v15,v10);
      if ((v10 >> 0x3c & 1) == 0) goto LBL_0021c6d0;
LBL_0021c864:
      if (v14 < param_2 >> 0x10 || v14 < v6 >> 0x10) goto LBL_0021c9cc;
      v12 = rt_002b15d0(param_2,v6,v15,v10);
      rt_003a25d4(v10);
    }
    else {
      if ((v10 >> 0x3c & 1) != 0) goto LBL_0021c864;
LBL_0021c6d0:
      rt_003a25d4(v10);
      v12 = (v6 >> 0x10) - (param_2 >> 0x10);
    }
    v1 = 1;
    v8 = param_4;
    v18 = param_5;
  }
  v9 = rt_00252b04(param_1,param_7,param_8,param_9,param_10);
  if (v9 < v8) {
    v13 = v9 == 0;
    do {
      if (!v13) {
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Index_out_of_range_005cd940,0x12,2,
                     s_Swift_CollectionOfOne_swift_005d0d40,0x1b,2,0x84,1);
      }
      v17 = param_7;
      uStack_78 = param_8;
      rt_0036b270(param_8);
      (*param_9)(&v16,&v17);
      rt_003a25d4(param_8);
      v10 = uStack_68;
      v15 = v16;
      if ((uStack_68 >> 0x3c & 1) == 0) {
        rt_003a25d4(uStack_68);
        v15 = v15 & 0xffffffffffff;
        if ((v10 & 0x2000000000000000) != 0) {
          v15 = v10 >> 0x38 & 0xf;
        }
      }
      else {
        v15 = rt_002b24b8(v16,uStack_68);
        rt_003a25d4(v10);
      }
      v13 = SCARRY8(v12,v15 * v1);
      v12 = v12 + v15 * v1;
      if (v13) {
                    /* WARNING: Does not return */
        v3 = (code *)SW_BREAK(0x21c8e8);
        (*v3)();
      }
      v13 = false;
    } while (1 < v8);
  }
  if (param_6 == '\x01') {
    return v12;
  }
  v19 = rt_00253570(v8,param_7,param_8,param_9,param_10);
  v10 = (uint64_t)v19.hi;
  v15 = (uint64_t)v19.lo;
  v4 = v19._hi32 >> 0x1b & 1;
  if ((v10 & 0x1000000000000000) == 0) {
    v4 = 1;
  }
  if ((v18 & 0xc) == 4L << v4) {
    v18 = rt_0001da84(v18,v15,v10);
  }
  if ((v10 >> 0x3c & 1) == 0) {
    rt_003a25d4(v10);
    v18 = v18 >> 0x10;
  }
  else {
    v14 = v15 & 0xffffffffffff;
    if ((v10 & 0x2000000000000000) != 0) {
      v14 = v10 >> 0x38 & 0xf;
    }
    if (v14 < v18 >> 0x10) {
LBL_0021c9cc:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                   s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xcf,1);
    }
    v18 = rt_002b15d0(0xf,v18,v15,v10);
    rt_003a25d4(v10);
  }
  if (SCARRY8(v12,v18 * v1)) {
                    /* WARNING: Does not return */
    v3 = (code *)SW_BREAK(0x21c940);
    (*v3)();
  }
  return v12 + v18 * v1;
}



/* FUN_0021cad0 @ 0x0021cad0   (est. swift_string_build)
 * Ghidra: void FUN_0021cad0(uint64_t param_1, uint64_t param_2, long param_3, long param_4, uint64_t param_5)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021cad0(uint64_t param_1, uint64_t param_2, long param_3, long param_4, uint64_t param_5){
  uint8_t stack_base[512];
  uint8_t *stack_ptr = stack_base;

  uint64_t *v5;
  uint8_t v69;
  bool v13;
  long v10;
  uint64_t v16;
  unsigned long v15;
  uint64_t v12;
  unsigned long v14;
  long v11;
  code *v6;
  long v7;
  uint64_t v59;
  long v61;
  long v41;
  long v28;
  long v40;
  long v27;
  code *v22;
  code *v34;
  code *v52;
  code *v56;
  code *v24;
  code *v54;
  code *v55;
  code *v35;
  code *v29;
  code *v42;
  code *v26;
  code *v30;
  long v46;
  code *v25;
  code *v51;
  code *v32;
  unsigned long v48;
  code *v45;
  code *v38;
  code *v49;
  code *v44;
  code *v21;
  long v53;
  code *v31;
  code *v36;
  code *v60;
  code *v50;
  code *v37;
  code *v33;
  code *v39;
  code *v43;
  code *v47;
  code *v23;
  code *v57;
  code *v19;
  long v58;
  long v20;
  long v18;
  uint64_t v17;
  uint64_t v64;
  long v65;
  code *v3;
  uint64_t v8;
  code *v1;
  code *v2;
  code *v4;
  long v62;
  long v63;
  uint64_t v66;
  rt16 v76;
  long v68;
  uint64_t v75;
  long v73;
  uint64_t v72;
  uint64_t v71;
  long v9;
  uint64_t v67;
  long v70;
  uint64_t v74;
  uint8_t v78 [16];
  uint8_t v77 [16];
  uint8_t v79 [8];
  
  rt_0008e518();
  rt_00359de8();
  v8 = *(uint64_t *)(param_3 + 0x10);
  rt_00350488();
  rt_00352578();
  rt_0031be78();
  rt_00348e60();
  (*G_00658c00)(*(uint64_t *)(v61 + 0x40));
  rt_00348bd8();
  (*G_00658c00)();
  rt_00350464();
  rt_00353e94();
  v76 = rt_00348b94(param_4);
  v10 = rt_00377824(v76.lo,v76.hi,v8).lo;
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v41 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034a9c0();
  (*G_00658c00)();
  rt_0034ac50();
  rt_0034d598();
  rt_00377824(0xff,param_5);
  rt_0034da88();
  rt_00310d68();
  v16 = rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v28 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034a9e8();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034aa14();
  rt_0034e3ac();
  (*G_00658c00)(*(uint64_t *)(v40 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034a1c8();
  (*G_00658c00)();
  rt_0034a4f8();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034bc6c();
  rt_0034c444(0);
  rt_00377824();
  rt_00348fd8();
  (*G_00658c00)(*(uint64_t *)(v27 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034aea8();
  (*G_00658c00)();
  rt_0034b758();
  rt_00352c4c();
  v15 = rt_001b9040();
  if ((v15 & 1) != 0) {
    rt_003512d8();
    rt_00100efc();
    (*v60)();
    rt_000277b8(param_4);
    v12 = rt_0034f644();
    (*v50)(v12,param_4);
    rt_00310cd4(param_4);
    rt_0034b8cc();
    rt_00351b78();
    (*v22)();
    rt_003553d8();
    v3 = *(code **)(v65 + 8);
    rt_003510dc();
    (*v3)();
    rt_0035145c();
    (*v3)();
  }
  rt_0034c3c4();
  rt_000b4390();
  v12 = rt_00377bec().lo;
  rt_00349fe0();
  rt_0034dad8(v65,v63);
  v14 = (*v34)();
  if ((v14 & 1) == 0) {
    rt_00356060();
    v3 = *(code **)(v65 + 0x10);
    v5 = (uint64_t *)(v58 + 0x10);
    if ((v15 & 1) == 0) {
      (*v3)(v72,v65,v62);
      (*v3)(v74,v63,v62);
      rt_00352ecc(param_4);
      rt_00356864();
      rt_00351b78();
      v76 = rt16_mklo((*v35)());
      v1 = (code *)*v5;
      (*v1)(v68,v76.hi,v10);
      rt_00351cac();
      ((code)(v76.lo))();
      rt_00359f28();
      rt_00352698(&stack_ptr);
      (*v19)();
      v3 = (code *)1;
      v76 = rt_0035172c();
      rt_00350884(v76.lo,v76.hi,v64);
      if ((bool)v69) {
        v16 = 0x14f;
        goto LBL_0021d674;
      }
      rt_00351750(param_5);
      rt_003524e0(&stack_ptr);
      rt_00350c2c();
      (*v33)();
      rt_0035647c(param_5);
      rt_00350524();
      rt_00352d40();
      v11 = (*v29)();
      v9 = 1;
      v73 = v68;
    }
    else {
      (*v3)(v72,v63,v62);
      (*v3)(v74,v65,v62);
      rt_00352ecc(param_4);
      v76 = rt_00356864();
      v76 = rt16_mklo((*v56)(v76.lo,v76.hi,v8));
      v3 = (code *)v76.lo;
      v1 = (code *)*v5;
      (*v1)(v73,v76.hi,v10);
      rt_00351cac();
      (*v3)();
      rt_00351750(param_5);
      rt_003524e0(&stack_ptr);
      rt_00350c2c();
      (*v37)();
      rt_00359f28();
      (*v57)(v71);
      v76 = rt_00351d24();
      rt_00350884(v76.lo,v76.hi,v64);
      if ((bool)v69) {
        v16 = 0x149;
LBL_0021d674:
        rt_003489dc(v16);
        rt_0034a2f8();
                    /* WARNING: Subroutine does not return */
        rt_001afe4c();
      }
      rt_00310cd4(param_5);
      rt_0035012c();
      rt_00352d40();
      v11 = (*v24)();
      v9 = -1;
    }
    v2 = (code *)(v18 + 8);
    v4 = *(code **)v2;
    (*v4)(v3,v64);
    rt_00353930(v58);
    rt_003508a8();
    (*v43)();
    rt_0007c1c4();
    (*v4)();
    rt_003520b4(v77);
    rt_00353d94();
    rt_003519b4(&stack_ptr);
    rt_00077894(v72);
    (*v47)();
    rt_00354570(*(uint64_t *)(v65 + 8),v72,v62);
    (*v42)();
    rt_003568e8();
    rt_0035044c();
    rt_00359518(v73);
    rt_0035053c();
    v15 = (*v26)();
    v7 = v73;
    if ((v15 & 1) != 0) {
      v3 = (code *)rt_000277e8(v10);
      v6 = (code *)rt_00027788(param_5);
      v2 = (code *)rt_00027818(v10);
      do {
        rt_00351b78(v78,v73);
        v76 = rt16_mklo((*v3)());
        (*v1)(v5,v70,v76.hi,v10);
        rt_0034c3b4();
        ((code)(v76.lo))();
        v7 = (*v6)(v10,param_5);
        rt_003530f4();
        (*v39)();
        v13 = SCARRY8(v11,v7 * v9);
        v11 = v11 + v7 * v9;
        v69 = v11 == 0;
        if (v13) {
                    /* WARNING: Does not return */
          v3 = (code *)SW_BREAK(0x21d658);
          (*v3)();
        }
        rt_00077894(v73);
        (*v2)();
        v76 = rt_00359518(v73);
        v15 = (*v26)(v76.lo,v76.hi,v66,v12);
        v7 = v10;
      } while ((v15 & 1) != 0);
    }
    rt_00350bc0(&stack_ptr);
    rt_003512c0();
    (*v30)();
    v12 = rt_00353e38();
    v76 = rt_00352698(&stack_ptr,v12,v7 + *(int *)(v46 + 0x2c));
    rt_00353bac(v76.lo,v76.hi,v16);
    (*v25)();
    rt_0035172c();
    rt_00350884();
    if ((bool)v69) {
      rt_00352bbc(v7,v62);
      (*v51)();
      rt_00350524(*(uint64_t *)(v20 + 8));
      (*v32)();
    }
    else {
      rt_00355430();
      rt_00354ac8(v48 & 0xffffffffffff | 0x4f8000000000000);
      rt_0035748c(&stack_ptr);
      (*v45)(v75,v2,v64);
      rt_00352ecc(v10);
      v76 = rt16_mklo((*v38)(v78,v7,v8,v10));
      (*v1)(v5,v70,v76.hi,v10);
      rt_00351cac();
      ((code)(v76.lo))();
      rt_00352bbc(v7,v62);
      (*v49)();
      rt_00354780();
      rt_0035156c();
      rt_00352098(&stack_ptr);
      rt_00350c2c();
      (*v23)();
      rt_00310cd4(v65);
      rt_000dbdf4();
      rt_00350998();
      v10 = (*v44)();
      rt_000e15d8();
      (*v4)();
      rt_0006b6f4();
      (*v39)();
      rt_00351274();
      (*v4)();
      if (SCARRY8(v11,v10 * v9)) {
                    /* WARNING: Does not return */
        v3 = (code *)SW_BREAK(0x21d56c);
        (*v3)();
      }
    }
  }
  else {
    v3 = *(code **)(v20 + 0x10);
    (*v3)(v67,v65 + *(int *)(v62 + 0x2c),v16);
    v76 = rt_00352888();
    rt_00350884(v76.lo,v76.hi,v64);
    if ((bool)v69) {
      rt_00350944(*(uint64_t *)(v20 + 8));
      (*v52)();
    }
    else {
      v12 = rt_0035463c();
      v1 = *(code **)(param_4 + 0x20);
      rt_00356278(v12,v67);
      v12 = (*v1)();
      v76 = rt_00352d64(v79,v12,v63 + *(int *)(v62 + 0x2c));
      (*v3)(v76.lo,v76.hi,v16);
      rt_0034e1b0(v62);
      if ((bool)v69) {
        rt_00350bc0(&stack_ptr);
        rt_003508f0();
        (*v54)();
        rt_0035a4f8();
        rt_00351324();
        (*v55)();
      }
      else {
        v76 = rt_003505e8();
        (*v1)(v76.lo,v76.hi,v64);
        rt_00352ecc(param_4);
        v3 = (code *)(*v21)(v78,v65,v8,param_4);
        rt_00352134();
        (**(code **)(v53 + 0x10))(v70,v59,v10);
        rt_00351cac();
        (*v3)();
        rt_00310cd4(param_5);
        rt_0034ce68();
        rt_00353a18();
        (*v31)();
        rt_00350af4(*(uint64_t *)(param_4 + 8));
        (*v36)();
        rt_003573c0();
        v3 = *(code **)(v70 + 8);
        rt_000a6e14();
        (*v3)();
        rt_003508f0();
        (*v3)();
      }
    }
  }
  v16 = rt_0035a3d0();
  rt_0008e500(v16,v17);
  return;
}



/* FUN_0021d760 @ 0x0021d760   (est. swift_check_flag)
 * Ghidra: uint32_t FUN_0021d760( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021d760( void){
  uint32_t v1;
  uint64_t v3;
  code *v2;
  
  rt_0034a74c();
  rt_0031be90(v3);
  rt_0034c8a0();
  v1 = (*v2)();
  return v1 & 1;
}



/* FUN_0021d7a0 @ 0x0021d7a0   (est. swift_neg_loop2)
 * Ghidra: void FUN_0021d7a0( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021d7a0( void){
  bool v3;
  uint64_t v2;
  uint64_t v14;
  uint64_t v20;
  uint64_t v19;
  long v16;
  uint64_t v12;
  code *v1;
  code *v8;
  code *v9;
  code *v15;
  code *v10;
  code *v7;
  code *v11;
  long v13;
  long v5;
  long v6;
  long v17;
  long v4;
  uint64_t v18;
  rt16 v23;
  uint64_t v21;
  uint64_t v22;
  
  rt_0008e518();
  rt_0034c2e8();
  v23 = rt_0035113c();
  rt_0031be78(v23.lo,v23.hi,v20,v19);
  rt_00348d7c();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aee4();
  rt_00349748();
  v2 = rt_00377824().lo;
  rt_000a6f88(v2,v2);
  (*G_00658c00)(*(uint64_t *)(v16 + 0x40));
  rt_00348bd8();
  (*G_00658c00)();
  rt_00350464();
  rt_00350908();
  rt_00310d68();
  v2 = rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_00355b1c();
  rt_0035399c();
  rt_00351354();
  (*v15)();
  v4 = v17 >> 0x3f;
  if (v4 < 0) {
    rt_003512d8();
    rt_003507e0(v12);
    (*v10)();
    rt_003506e8();
    rt_003507e0(v21);
    (*v7)();
    rt_003192d8();
    rt_003548e8();
    rt_003513c0(v12,v4);
    (*v11)();
    v1 = *(code **)(v5 + 8);
    (*v1)(v21,v14);
    (*v1)(v12,v14);
    (**(code **)(v6 + 8))(v22,v2);
    v3 = SBORROW8(0,v17);
    v17 = -v17;
    if (v3) {
                    /* WARNING: Does not return */
      v1 = (code *)SW_BREAK(0x21da44);
      (*v1)();
    }
    if (v17 < 0) {
      rt_00347d60();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
  }
  else if (v17 == 0) goto LBL_0021da18;
  do {
    rt_0034e474();
    if (v4 < 0) {
      ((code)FUN_00219fcc)();
    }
    else {
      ((code)FUN_00219a00)();
    }
    rt_000dbd0c(*(uint64_t *)(v13 + 8));
    (*v8)();
    rt_00351360(*(uint64_t *)(v13 + 0x20));
    (*v9)();
    v17 = v17 + -1;
  } while (v17 != 0);
LBL_0021da18:
  rt_0008e500(v18);
  return;
}



/* FUN_0021da44 @ 0x0021da44   (est. swift_init_loop)
 * Ghidra: void FUN_0021da44(uint64_t param_1, uint64_t param_2, long param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021da44(uint64_t param_1, uint64_t param_2, long param_3){
  code *v3;
  code *v2;
  long v1;
  uint64_t v4;
  
  rt_0008e518();
  rt_0034b668();
  rt_00352578(0,*(uint64_t *)(param_3 + 0x10));
  rt_0031be78();
  rt_00348d7c();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0d4();
  rt_0035478c();
  rt_00350a34();
  (*v2)();
  rt_00353c60();
  rt_0034eda8();
  ((code)FUN_0021d7a0)();
  rt_003508f0(*(uint64_t *)(v1 + 8));
  (*v3)();
  rt_0008e500(v4);
  return;
}



/* FUN_0021db04 @ 0x0021db04   (est. swift_loop_dispatch3)
 * Ghidra: void FUN_0021db04(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, uint64_t param_6)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021db04(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, uint64_t param_6){
  uint64_t v2;
  unsigned long v3;
  long v16;
  uint64_t v11;
  uint64_t v18;
  long v12;
  long v8;
  code *v9;
  code *v6;
  code *v17;
  code *v10;
  code *v7;
  code *v13;
  long v14;
  long v15;
  long v5;
  code *v1;
  long v4;
  uint64_t v19;
  uint64_t v20;
  uint64_t v22;
  uint64_t v21;
  
  rt_0008e518();
  rt_00349748();
  rt_00350b48();
  v2 = rt_00377824().lo;
  rt_000a6f88(v2,v2);
  (*G_00658c00)(*(uint64_t *)(v12 + 0x40));
  rt_003493c4();
  rt_0034c2f8();
  (*G_00658c00)();
  rt_0034aa28();
  rt_00310d68(0);
  v2 = rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b708();
  rt_0034d3e4();
  rt_0031be78();
  rt_00348cd0();
  (*G_00658c00)(*(uint64_t *)(v8 + 0x40));
  rt_00348a34();
  (*G_00658c00)();
  rt_0034c2c8();
  rt_003507e0();
  (*v17)();
  if (v16 >> 0x3f < 0) {
    rt_00351750(param_5);
    rt_00350470(v21);
    (*v10)();
    rt_0035156c(param_5);
    rt_00350470(v22);
    (*v7)();
    rt_003192d8(param_5);
    rt_00351bd4(v20,v21);
    rt_00351978();
    (*v13)();
    v1 = *(code **)(v15 + 8);
    (*v1)(v22,v11);
    (*v1)(v21,v11);
    (**(code **)(v5 + 8))(v20,v2);
    v4 = -v16;
    if (SBORROW8(0,v16)) {
                    /* WARNING: Does not return */
      v1 = (code *)SW_BREAK(0x21de4c);
      (*v1)();
    }
    if (v4 < 0) {
      rt_00347d60();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
  }
  else {
    v4 = v16;
    if (v16 == 0) {
      v1 = *(code **)(v14 + 0x20);
      goto LBL_0021dde4;
    }
  }
  do {
    rt_00352d40(param_6,param_3);
    v3 = ((code)FUN_002187e0)();
    if ((v3 & 1) != 0) {
      rt_003510ac(*(uint64_t *)(v14 + 8));
      (*v6)();
      v2 = 1;
      goto LBL_0021de10;
    }
    if (v16 >> 0x3f < 0) {
      rt_00351f1c(param_6,param_4);
      ((code)FUN_00219fcc)();
    }
    else {
      rt_00351f1c(param_6,param_4);
      ((code)FUN_00219a00)();
    }
    rt_003510ac(*(uint64_t *)(v14 + 8));
    (*v9)();
    v1 = *(code **)(v14 + 0x20);
    rt_00351324();
    (*v1)();
    v4 = v4 + -1;
  } while (v4 != 0);
LBL_0021dde4:
  rt_0034ee18(v14 + 0x20U & 0xffffffffffff | 0x48d8000000000000);
  (*v1)();
  v2 = 0;
LBL_0021de10:
  rt_000839d8(v18,v2,1);
  rt_0008e500(v19);
  return;
}



/* FUN_0021de4c @ 0x0021de4c   (est. swift_init_dispatch2)
 * Ghidra: void FUN_0021de4c( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021de4c( void){
  int v3;
  uint64_t v2;
  long v9;
  code *v7;
  code *v6;
  long v5;
  long v4;
  code *v1;
  uint64_t v8;
  
  rt_0008e518();
  rt_00357a34();
  rt_00354828(0xff,*(uint64_t *)(v9 + 0x10));
  rt_0031be78();
  rt_0034e130();
  rt_00310d68();
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b460();
  rt_00349734();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b2f8();
  rt_00355d28();
  rt_00354840();
  ((code)FUN_0021db04)();
  rt_00353990();
  rt_003507e0();
  (*v6)();
  rt_003513e4();
  v3 = rt_0035681c();
  if (v3 == 1) {
    (**(code **)(v5 + 8))();
    rt_00355d28(*(uint64_t *)(v4 + 0x10));
    (*v7)();
  }
  else {
    v1 = *(code **)(v4 + 0x20);
    rt_0034b508();
    (*v1)();
    rt_00350600();
    (*v1)();
  }
  v2 = rt_00357fd4();
  rt_0008e500(v2,v8);
  return;
}



/* FUN_0021dfcc @ 0x0021dfcc   (est. swift_dispatch15)
 * Ghidra: void FUN_0021dfcc(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021dfcc(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4){
  uint8_t v16;
  uint64_t v2;
  uint64_t v3;
  code *v1;
  uint64_t v13;
  code *v10;
  code *v8;
  code *v9;
  code *v12;
  long v11;
  long v6;
  long v7;
  long v5;
  long v15;
  uint64_t v4;
  uint64_t v14;
  rt16 v17;
  
  rt_0008e518();
  v2 = rt_00350b54().lo;
  rt_00350bd8(param_3);
  v4 = *(uint64_t *)(v15 + 0x10);
  v17 = rt_00349b14();
  v4 = rt_00377824(v17.lo,v17.hi,v4).lo;
  rt_0034a944();
  rt_0035136c();
  v3 = rt_00377824().lo;
  rt_00310d68(0,v3);
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0c4();
  rt_00350720();
  rt_00377dcc();
  rt_00348d7c();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  v3 = rt_00351b84();
  rt_003515fc(v3,v2);
  v1 = (code *)(*v10)();
  rt_00352474();
  (*v12)();
  rt_0034cfa4();
  (*v1)();
  rt_0034c60c();
  rt_0031be78();
  (**(code **)(v11 + 0x10))();
  rt_0034aa54();
  if (!(bool)v16) {
    rt_00351b84(param_4);
    rt_0035359c();
    (*v8)();
    rt_00351a50();
    v17 = rt_00348b94(param_4);
    rt_00377824(v17.lo,v17.hi,v4);
    rt_00349530();
    (**(code **)(v7 + 0x10))(v13);
    rt_0034cfa4();
    (*(code *)1)();
    rt_00350b3c(*(uint64_t *)(v6 + 8));
    (*v9)();
    rt_0034b3c8();
    (**(code **)(v5 + 8))();
    rt_0008e500(v14);
    return;
  }
  rt_003489dc(0x1b2);
  rt_0034a2f8();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}



/* FUN_0021e254 @ 0x0021e254   (est. swift_dispatch16)
 * Ghidra: void FUN_0021e254( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e254( void){
  uint8_t stack_base[512];
  uint8_t *stack_ptr = stack_base;

  long v6;
  code *v10;
  uint64_t v9;
  uint64_t v7;
  long v3;
  code *v2;
  code *v1;
  long v4;
  long v5;
  uint64_t v8;
  rt16 v11;
  
  rt_0008e518();
  rt_0035215c();
  (*v10)(0xff,*(uint64_t *)(v6 + 0x10));
  v11 = rt_00352efc();
  rt_00310e08(v11.lo,v11.hi,v9);
  rt_00348e60();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  rt_003494e8();
  (*G_00658c00)(*(uint64_t *)(v3 + 0x40));
  rt_0034a1f8();
  rt_00350494(*(uint64_t *)(v4 + 0x10));
  (*v2)();
  v11 = rt_00350c38(*(uint64_t *)(v5 + 0x10));
  v11 = rt16_mklo((*v1)(v11.lo,v11.hi,v9));
  rt_00354648(v11.lo,v11.hi,&stack_ptr);
  rt_00376820();
  rt_00351298(v7);
  rt_001d3fd0();
  rt_0008e500(v8);
  return;
}



/* FUN_0021e3a0 @ 0x0021e3a0   (est. swift_box_alloc2)
 * Ghidra: void * FUN_0021e3a0(long * param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void * FUN_0021e3a0(long * param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4){
  long v1;
  uint64_t v2;
  
  v1 = rt_0036a908(0x28,0xec1e);
  *param_1 = v1;
  v2 = FUN_0021e420((long*)v1,param_2,param_3,*(uint64_t *)((param_4 & 0xfffffffffffffffe) - 8),
                       *(uint64_t *)((param_4 & 0xfffffffffffffffe) - 0x10)).lo;
  *(uint64_t *)(v1 + 0x20) = v2;
  return &G_003471a4;
}



/* FUN_0021e420 @ 0x0021e420   (est. swift_box_init2)
 * Ghidra: rt16 FUN_0021e420(long * param_1, uint64_t param_2, long param_3, uint64_t param_4, uint64_t param_5)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
rt16 FUN_0021e420(long * param_1, uint64_t param_2, long param_3, uint64_t param_4, uint64_t param_5){
  uint64_t v2;
  uint64_t v3;
  long v1;
  rt16 v4;
  
  v2 = rt_00027754(param_5);
  v3 = rt_00027754(param_4);
  v3 = rt_00377824(0xff,v3,*(uint64_t *)(param_3 + 0x10),&G_00611b24,&LBL_00611b34).lo;
  v1 = rt_00377824(0,v2,v3,&G_00611b24,&LBL_00611b34).lo;
  *param_1 = v1;
  v1 = *(long *)(v1 + -8);
  param_1[1] = v1;
  v1 = rt_0036a908(*(uint64_t *)(v1 + 0x40),0x6db8);
  param_1[2] = v1;
  ((code)FUN_0021dfcc)(v1,param_2,param_3,param_4,param_5);
  v4.hi = v1;
  v4.lo = (uint64_t)&G_003471a8;
  return v4;
}



/* FUN_0021e548 @ 0x0021e548   (est. swift_init_dispatch3)
 * Ghidra: void FUN_0021e548( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e548( void){
  long v1;
  long v2;
  
  rt_0035a6f4();
  rt_0031be78(0xff,*(uint64_t *)(v1 + 0x10),*(uint64_t *)(v2 + -8),
               *(uint64_t *)(v2 + -0x10));
  rt_00352efc();
  rt_00310d68();
  rt_0034b690();
  rt_000839d8();
  return;
}



/* FUN_0021e5c4 @ 0x0021e5c4   (est. swift_chain_call2)
 * Ghidra: void FUN_0021e5c4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e5c4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4){
  rt_0034ba18();
  rt_00352894(param_3);
  rt_00356bb0(param_4);
  rt_0034cdd8();
  ((code)FUN_00219fcc)();
  return;
}



/* FUN_0021e614 @ 0x0021e614   (est. swift_dispatch17)
 * Ghidra: void FUN_0021e614(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e614(uint64_t param_1, uint64_t param_2, uint64_t param_3){
  code *v2;
  code *v1;
  uint64_t v3;
  
  rt_00084220();
  rt_00349a18();
  rt_00351bec(param_3);
  rt_00356bb0();
  rt_0034c920();
  rt_0031be78();
  rt_00348d4c();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034a2c0();
  rt_003513b4();
  (*v1)();
  rt_00353378();
  rt_0034b358();
  ((code)FUN_0021e5c4)();
  rt_0034c9f8();
  (*v2)();
  rt_00084234(v3);
  return;
}



/* FUN_0021e6e4 @ 0x0021e6e4   (est. swift_arg_unwrap6)
 * Ghidra: void FUN_0021e6e4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, unsigned long param_5)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e6e4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, unsigned long param_5){
  uint64_t v1;
  uint64_t v2;
  
  v2 = *(uint64_t *)((param_5 & 0xfffffffffffffffe) - 0x10);
  v1 = rt_00027754(*(uint64_t *)((param_5 & 0xfffffffffffffffe) - 8));
  v2 = rt_00027754(v2);
  ((code)FUN_0021d7a0)(param_1,param_2,param_3,param_4,v1,v2);
  return;
}



/* FUN_0021e75c @ 0x0021e75c   (est. swift_arg_unwrap7)
 * Ghidra: void FUN_0021e75c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, unsigned long param_6)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e75c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, unsigned long param_6){
  uint64_t v1;
  uint64_t v2;
  
  v2 = *(uint64_t *)((param_6 & 0xfffffffffffffffe) - 0x10);
  v1 = rt_00027754(*(uint64_t *)((param_6 & 0xfffffffffffffffe) - 8));
  v2 = rt_00027754(v2);
  ((code)FUN_0021db04)(param_1,param_2,param_3,param_4,param_5,v1,v2);
  return;
}



/* FUN_0021e7dc @ 0x0021e7dc   (est. swift_arg_unwrap5)
 * Ghidra: void FUN_0021e7dc(uint64_t param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e7dc(uint64_t param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4){
  uint64_t v1;
  uint64_t v2;
  
  v2 = *(uint64_t *)((param_4 & 0xfffffffffffffffe) - 0x10);
  v1 = rt_00027754(*(uint64_t *)((param_4 & 0xfffffffffffffffe) - 8));
  v2 = rt_00027754(v2);
  FUN_0021cad0(param_1,param_2,param_3,v1,v2);
  return;
}



/* FUN_0021e844 @ 0x0021e844   (est. swift_int_to_grade)
 * Ghidra: uint32_t FUN_0021e844(long param_1)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021e844(long param_1){
  uint32_t v1;
  uint32_t v2;
  
  v2 = 1;
  if (param_1 != 1) {
    v2 = 2;
  }
  v1 = 0;
  if (param_1 != 0) {
    v1 = v2;
  }
  return v1;
}



/* FUN_0021e874 @ 0x0021e874   (est. swift_char_equal)
 * Ghidra: bool FUN_0021e874(uint8_t * param_1, uint8_t * param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
bool FUN_0021e874(uint8_t * param_1, uint8_t * param_2){
  uint8_t v2;
  long v3;
  long v1;
  
  v2 = *param_2;
  v3 = rt_00149368(*param_1);
  v1 = rt_00149368(v2);
  return v3 == v1;
}



/* FUN_0021e8c0 @ 0x0021e8c0   (est. swift_char_grade)
 * Ghidra: void FUN_0021e8c0(uint8_t * param_1, uint64_t * param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e8c0(uint8_t * param_1, uint64_t * param_2){
  uint8_t v1;
  
  v1 = FUN_0021e844(*param_2);
  *param_1 = v1;
  return;
}



/* FUN_0021e8f0 @ 0x0021e8f0   (est. swift_char_load)
 * Ghidra: void FUN_0021e8f0(uint64_t * param_1)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e8f0(uint64_t * param_1){
  uint64_t v1;
  uint8_t *v2;
  
  v1 = rt_00149368(*v2);
  *param_1 = v1;
  return;
}



/* FUN_0021e940 @ 0x0021e940   (est. swift_check_flag2)
 * Ghidra: uint32_t FUN_0021e940( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021e940( void){
  uint32_t v1;
  uint64_t v3;
  code *v2;
  
  rt_0034a74c();
  rt_0031bec0(v3);
  rt_0034c8a0();
  v1 = (*v2)();
  return v1 & 1;
}



/* FUN_0021e980 @ 0x0021e980   (est. swift_check_flag3)
 * Ghidra: uint32_t FUN_0021e980( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021e980( void){
  uint32_t v1;
  uint64_t v3;
  code *v2;
  
  rt_0034a74c();
  rt_0031bef0(v3);
  rt_0034c8a0();
  v1 = (*v2)();
  return v1 & 1;
}



/* FUN_0021e9c0 @ 0x0021e9c0   (est. swift_check_flag4)
 * Ghidra: uint32_t FUN_0021e9c0( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021e9c0( void){
  uint32_t v1;
  uint64_t v3;
  code *v2;
  
  rt_0034a74c();
  rt_0031bf20(v3);
  rt_0034c8a0();
  v1 = (*v2)();
  return v1 & 1;
}



/* FUN_0021ea00 @ 0x0021ea00   (est. swift_check_flag5)
 * Ghidra: uint32_t FUN_0021ea00( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021ea00( void){
  uint32_t v1;
  uint64_t v2;
  uint64_t v4;
  code *v3;
  
  rt_0034a74c();
  v2 = rt_0031bef0(v4);
  rt_0034b778(v2);
  v1 = (*v3)();
  return v1 & 1;
}



/* FUN_0021ea44 @ 0x0021ea44   (est. swift_check_flag6)
 * Ghidra: uint32_t FUN_0021ea44( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021ea44( void){
  uint32_t v1;
  uint64_t v2;
  uint64_t v4;
  code *v3;
  
  rt_0034a74c();
  v2 = rt_0031bf20(v4);
  rt_0034b778(v2);
  v1 = (*v3)();
  return v1 & 1;
}



/* FUN_0021ea88 @ 0x0021ea88   (est. swift_init_dispatch4)
 * Ghidra: void FUN_0021ea88( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021ea88( void){
  uint64_t v1;
  uint64_t v6;
  long v8;
  code *v4;
  code *v7;
  code *v3;
  code *v2;
  long v5;
  uint64_t v9;
  
  rt_0008e518();
  rt_00351a38();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v8 + 0x40));
  rt_00348f38();
  rt_0008f6f4(v6);
  rt_00027754();
  rt_0035a478();
  rt_00349d80();
  rt_003508c0();
  rt_00377824();
  rt_0034a450();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0d4();
  rt_0035060c();
  rt_00353c3c();
  rt_00377bec();
  v1 = rt_0034bc04();
  rt_00351f4c(v1,0x200);
  (*v7)();
  rt_0034d558();
  rt_0034d810();
  (*v3)();
  rt_0031bf50();
  rt_0035133c();
  rt_003507e0();
  (*v2)();
  rt_003514e8(*(uint64_t *)(v5 + 8));
  (*v4)();
  rt_0008e500(v9);
  return;
}



/* FUN_0021ebbc @ 0x0021ebbc   (est. swift_dispatch18)
 * Ghidra: void FUN_0021ebbc( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021ebbc( void){
  uint64_t v1;
  uint64_t v2;
  uint64_t v5;
  code *v3;
  long v4;
  
  v1 = rt_00350b54().lo;
  rt_0034ece8();
  (**(code **)(v4 + 0x10))(v5);
  v2 = rt_0031bf80();
  rt_003504a0(v2,v1);
  (*v3)();
  return;
}



/* FUN_0021ec38 @ 0x0021ec38   (est. swift_dispatch19)
 * Ghidra: void FUN_0021ec38( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021ec38( void){
  code *UNRECOVERED_JUMPTABLE;
  
  rt_0034bd6c();
  UNRECOVERED_JUMPTABLE = (code *)rt_0031bfb0();
  rt_003504a0(0);
                    /* WARNING: Could not recover jumptable at 0x0021ec78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



/* FUN_0021edec @ 0x0021edec   (est. swift_dispatch20)
 * Ghidra: void FUN_0021edec( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021edec( void){
  code *v2;
  long v1;
  code *v3;
  
  rt_00349944();
  rt_0034ece8();
  (**(code **)(v1 + 0x10))();
  (*v3)();
  rt_003505d0();
  rt_00077894();
  (*v2)();
  return;
}



/* FUN_0021ee60 @ 0x0021ee60   (est. swift_dispatch21)
 * Ghidra: void FUN_0021ee60( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021ee60( void){
  code *v2;
  long v1;
  
  rt_0034c084();
  rt_0034ab20();
  (**(code **)(v1 + 0x10))();
  rt_0031c070();
  rt_0034c6a4();
  (*v2)();
  return;
}



/* FUN_0021eec4 @ 0x0021eec4   (est. swift_dispatch22)
 * Ghidra: void FUN_0021eec4( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021eec4( void){
  code *v2;
  long v1;
  
  rt_00349944();
  rt_0034b07c();
  (**(code **)(v1 + 0x10))();
  rt_0031c0a0();
  rt_0034c8b8();
  rt_0035063c();
  (*v2)();
  return;
}



/* FUN_0021ef30 @ 0x0021ef30   (est. half_min)
 * Ghidra: unsigned long FUN_0021ef30(unsigned long param_1, uint8_t param_2 [16])
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
unsigned long FUN_0021ef30(unsigned long param_1, rt16 param_2){
  unsigned long v2;
  float v1;
  
  v1 = param_2._lo16;
  v2 = param_1;
  if (v1 < (float)param_1) {
    if ((((uint32_t)(float)v1 ^ 0xffffffff) & 0x7c00) != 0) {
      return param_2.lo;
    }
    v2 = (unsigned long)(uint16_t)v1;
    if (((uint32_t)(float)v1 & 0x3ff) != 0) {
      v2 = param_1 & 0xffff;
    }
  }
  return v2;
}



/* FUN_0021ef5c @ 0x0021ef5c   (est. float_min)
 * Ghidra: float FUN_0021ef5c(float param_1, float param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
float FUN_0021ef5c(float param_1, float param_2){
  float v1;
  
  if (param_2 < param_1) {
    v1 = param_2;
    if (((uint32_t)param_2 & 0x7fffff) != 0) {
      v1 = param_1;
    }
    param_1 = param_2;
    if ((((uint32_t)param_2 ^ 0xffffffff) & 0x7f800000) == 0) {
      param_1 = v1;
    }
  }
  return param_1;
}



/* FUN_0021ef80 @ 0x0021ef80   (est. double_min)
 * Ghidra: double FUN_0021ef80(double param_1, double param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
double FUN_0021ef80(double param_1, double param_2){
  double v1;
  
  if (param_2 < param_1) {
    v1 = param_2;
    if (((unsigned long)param_2 & 0xfffffffffffff) != 0) {
      v1 = param_1;
    }
    param_1 = param_2;
    if ((((unsigned long)param_2 ^ 0xffffffffffffffff) & 0x7ff0000000000000) == 0) {
      param_1 = v1;
    }
  }
  return param_1;
}



/* FUN_0021efbc @ 0x0021efbc   (est. half_max)
 * Ghidra: unsigned long FUN_0021efbc(unsigned long param_1, uint8_t param_2 [16])
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
unsigned long FUN_0021efbc(unsigned long param_1, rt16 param_2){
  unsigned long v2;
  float v1;
  
  v1 = param_2._lo16;
  v2 = param_1;
  if ((float)param_1 <= v1) {
    if ((((uint32_t)(float)v1 ^ 0xffffffff) & 0x7c00) != 0) {
      return param_2.lo;
    }
    v2 = (unsigned long)(uint16_t)v1;
    if (((uint32_t)(float)v1 & 0x3ff) != 0) {
      v2 = param_1 & 0xffff;
    }
  }
  return v2;
}



/* FUN_0021efe8 @ 0x0021efe8   (est. float_max)
 * Ghidra: float FUN_0021efe8(float param_1, float param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
float FUN_0021efe8(float param_1, float param_2){
  float v1;
  
  if (param_1 <= param_2) {
    v1 = param_2;
    if (((uint32_t)param_2 & 0x7fffff) != 0) {
      v1 = param_1;
    }
    param_1 = param_2;
    if ((((uint32_t)param_2 ^ 0xffffffff) & 0x7f800000) == 0) {
      param_1 = v1;
    }
  }
  return param_1;
}



/* FUN_0021f00c @ 0x0021f00c   (est. double_max)
 * Ghidra: double FUN_0021f00c(double param_1, double param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
double FUN_0021f00c(double param_1, double param_2){
  double v1;
  
  if (param_1 <= param_2) {
    v1 = param_2;
    if (((unsigned long)param_2 & 0xfffffffffffff) != 0) {
      v1 = param_1;
    }
    param_1 = param_2;
    if ((((unsigned long)param_2 ^ 0xffffffffffffffff) & 0x7ff0000000000000) == 0) {
      param_1 = v1;
    }
  }
  return param_1;
}



/* FUN_0021f048 @ 0x0021f048   (est. swift_dispatch23)
 * Ghidra: void FUN_0021f048( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021f048( void){
  uint64_t v1;
  unsigned long v2;
  uint64_t v7;
  code *v6;
  code *v5;
  code *v3;
  long v4;
  
  rt_00084220();
  v1 = v7;
  rt_003515f0();
  rt_0008f6c0(v1);
  rt_00351bec();
  v1 = (*v6)();
  rt_0008e388(v1);
  rt_00350ac4();
  v2 = (*v5)();
  if ((v2 & 1) == 0) {
    rt_0031c0d0(v7);
    v1 = rt_0034bfa4();
    (*v3)(v1,v7);
  }
  rt_00350bcc();
                    /* WARNING: Could not recover jumptable at 0x0021f100. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(v4 + 0x10))();
  return;
}



/* FUN_0021f104 @ 0x0021f104   (est. half_min_abs)
 * Ghidra: unsigned long FUN_0021f104(unsigned long param_1, uint8_t param_2 [16])
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
unsigned long FUN_0021f104(unsigned long param_1, rt16 param_2){
  unsigned long v2;
  float v1;
  
  v1 = param_2._lo16;
  v2 = param_1;
  if (ABS(v1) < ABS((float)param_1)) {
    if ((((uint32_t)(float)v1 ^ 0xffffffff) & 0x7c00) != 0) {
      return param_2.lo;
    }
    v2 = (unsigned long)(uint16_t)v1;
    if (((uint32_t)(float)v1 & 0x3ff) != 0) {
      v2 = param_1 & 0xffff;
    }
  }
  return v2;
}



/* FUN_0021f138 @ 0x0021f138   (est. float_min_abs)
 * Ghidra: float FUN_0021f138(float param_1, float param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
float FUN_0021f138(float param_1, float param_2){
  float v1;
  
  if (ABS(param_2) < ABS(param_1)) {
    v1 = param_2;
    if (((uint32_t)param_2 & 0x7fffff) != 0) {
      v1 = param_1;
    }
    param_1 = param_2;
    if ((((uint32_t)param_2 ^ 0xffffffff) & 0x7f800000) == 0) {
      param_1 = v1;
    }
  }
  return param_1;
}



/* FUN_0021f164 @ 0x0021f164   (est. double_min_abs)
 * Ghidra: double FUN_0021f164(double param_1, double param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
double FUN_0021f164(double param_1, double param_2){
  double v1;
  
  if (ABS(param_2) < ABS(param_1)) {
    v1 = param_2;
    if (((unsigned long)param_2 & 0xfffffffffffff) != 0) {
      v1 = param_1;
    }
    param_1 = param_2;
    if ((((unsigned long)param_2 ^ 0xffffffffffffffff) & 0x7ff0000000000000) == 0) {
      param_1 = v1;
    }
  }
  return param_1;
}



/* FUN_0021f1a8 @ 0x0021f1a8   (est. half_max_abs)
 * Ghidra: unsigned long FUN_0021f1a8(unsigned long param_1, uint8_t param_2 [16])
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
unsigned long FUN_0021f1a8(unsigned long param_1, rt16 param_2){
  unsigned long v2;
  float v1;
  
  v1 = param_2._lo16;
  v2 = param_1;
  if (ABS((float)param_1) <= ABS(v1)) {
    if ((((uint32_t)(float)v1 ^ 0xffffffff) & 0x7c00) != 0) {
      return param_2.lo;
    }
    v2 = (unsigned long)(uint16_t)v1;
    if (((uint32_t)(float)v1 & 0x3ff) != 0) {
      v2 = param_1 & 0xffff;
    }
  }
  return v2;
}



/* FUN_0021f1dc @ 0x0021f1dc   (est. float_max_abs)
 * Ghidra: float FUN_0021f1dc(float param_1, float param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
float FUN_0021f1dc(float param_1, float param_2){
  float v1;
  
  if (ABS(param_1) <= ABS(param_2)) {
    v1 = param_2;
    if (((uint32_t)param_2 & 0x7fffff) != 0) {
      v1 = param_1;
    }
    param_1 = param_2;
    if ((((uint32_t)param_2 ^ 0xffffffff) & 0x7f800000) == 0) {
      param_1 = v1;
    }
  }
  return param_1;
}



/* FUN_0021f208 @ 0x0021f208   (est. double_max_abs)
 * Ghidra: double FUN_0021f208(double param_1, double param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
double FUN_0021f208(double param_1, double param_2){
  double v1;
  
  if (ABS(param_1) <= ABS(param_2)) {
    v1 = param_2;
    if (((unsigned long)param_2 & 0xfffffffffffff) != 0) {
      v1 = param_1;
    }
    param_1 = param_2;
    if ((((unsigned long)param_2 ^ 0xffffffffffffffff) & 0x7ff0000000000000) == 0) {
      param_1 = v1;
    }
  }
  return param_1;
}



/* FUN_0021f24c @ 0x0021f24c   (est. swift_dispatch24)
 * Ghidra: void FUN_0021f24c( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021f24c( void){
  code *v1;
  unsigned long v2;
  uint64_t v3;
  uint64_t v12;
  code *v11;
  uint64_t v9;
  long v7;
  code *v6;
  code *v4;
  code *v5;
  long v8;
  uint64_t v10;
  
  rt_0008e518();
  v3 = v12;
  rt_0035a2d0();
  rt_00349720();
  (*G_00658c00)(*(uint64_t *)(v7 + 0x40));
  rt_003489c0();
  (*G_00658c00)();
  rt_0034b4c0();
  rt_0008f6f4(v3);
  rt_0035125c();
  v1 = (code *)rt_000a6b64();
  rt_0034e50c();
  (*v1)();
  rt_003504ac();
  (*v1)();
  rt_0008f6c0(v12);
  rt_0035125c();
  (*v11)();
  rt_0034f4f4();
  rt_0034df34();
  v2 = (*v6)();
  v1 = *(code **)(v8 + 8);
  rt_003508cc();
  (*v1)();
  rt_003509d4();
  (*v1)();
  if ((v2 & 1) == 0) {
    rt_0031c0d0(v12);
    v3 = rt_0034eee8();
    (*v4)(v3,v12);
  }
  rt_003504a0(*(uint64_t *)(v8 + 0x10),v9);
  (*v5)();
  rt_0008e500(v10);
  return;
}



/* FUN_0021f510 @ 0x0021f510   (est. swift_type_grade)
 * Ghidra: uint32_t FUN_0021f510( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021f510( void){
  char v3;
  unsigned long v2;
  code *v12;
  code *v9;
  code *v6;
  code *v8;
  code *v5;
  code *v7;
  code *v10;
  code *v11;
  uint32_t v1;
  uint32_t v4;
  
  rt_0034f664();
  rt_0031c100();
  rt_0034bcf0();
  v2 = (*v12)();
  if ((v2 & 1) == 0) {
    rt_0031c0d0();
    rt_0034bcf0();
    v2 = (*v9)();
    if ((v2 & 1) == 0) {
      rt_0031c130();
      rt_0034bcf0();
      v2 = (*v6)();
      if ((v2 & 1) == 0) {
        rt_0031c160();
        rt_0034bcf0();
        v2 = (*v5)();
        if ((v2 & 1) == 0) {
          rt_0031c190();
          rt_0034bcf0();
          v2 = (*v10)();
          rt_0031c1c0();
          rt_0034bcf0();
          v3 = (*v11)();
          v4 = 4;
          if (v3 != '\x01') {
            v4 = 7;
          }
          v1 = 5;
          if (v3 != '\x01') {
            v1 = 6;
          }
          if ((v2 & 1) == 0) {
            return v1;
          }
          return v4;
        }
        rt_0031c1c0();
        rt_0034bcf0();
        v3 = (*v7)();
        v1 = 8;
        v4 = 3;
      }
      else {
        rt_0031c1c0();
        rt_0034bcf0();
        v3 = (*v8)();
        v1 = 9;
        v4 = 2;
      }
      if (v3 != '\x01') {
        v4 = v1;
      }
    }
    else {
      v4 = 1;
    }
  }
  else {
    v4 = 0;
  }
  return v4;
}



/* FUN_0021f648 @ 0x0021f648   (est. swift_init_dispatch5)
 * Ghidra: void FUN_0021f648( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021f648( void){
  uint64_t v2;
  uint64_t v3;
  code *v8;
  code *v7;
  code *v5;
  code *v4;
  long v6;
  code *v1;
  uint64_t v9;
  
  rt_0008e518();
  rt_00352c34();
  rt_00353a24();
  rt_00359eb4();
  rt_003516cc();
  rt_00377824();
  rt_00351f10();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b05c();
  rt_0034f604();
  rt_00377824();
  rt_00351f10();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aee4();
  v2 = rt_0008f6f4();
  rt_0031c1c0();
  v3 = rt_000dbdf4();
  v2 = (*v8)(v3,v2);
  rt_0034b804();
  v1 = *(code **)(v6 + 8);
  (*v1)();
  rt_0031d6d8();
  rt_00350b24();
  rt_003510b8();
  (*v7)();
  rt_0031c788();
  rt_0034f644();
  (*v5)();
  rt_00351384();
  (*v1)();
  rt_0031c1f0();
  rt_0035133c();
  rt_003515d8(v2);
  rt_003543c4();
  (*v4)();
  rt_0008e500(v9);
  return;
}



/* FUN_0021f7b0 @ 0x0021f7b0   (est. swift_string_protocol_dispatch)
 * Ghidra: void FUN_0021f7b0(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, code * param_6)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021f7b0(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, code * param_6){
  uint8_t stack_base[512];
  uint8_t *stack_ptr = stack_base;

  code *v12;
  uint8_t v244;
  uint8_t v20;
  char v24;
  uint32_t v23;
  uint32_t v25;
  uint64_t v21;
  uint64_t v22;
  uint64_t v26;
  code *v16;
  uint64_t v13;
  code *v8;
  uint64_t v10;
  uint64_t v14;
  unsigned long v15;
  code *v1;
  long v19;
  unsigned long v17;
  code *v3;
  long v11;
  code *v5;
  code *v7;
  unsigned long v18;
  code *v9;
  uint64_t v239;
  uint64_t v120;
  uint64_t v89;
  code *v152;
  code *v96;
  code *v2;
  long v241;
  long v63;
  long v197;
  uint64_t v219;
  long v137;
  long v126;
  long v210;
  long v181;
  code *v186;
  long v39;
  code *v234;
  code *v81;
  code *v212;
  code *v141;
  code *v221;
  code *v135;
  code *v47;
  code *v117;
  code *v94;
  code *v233;
  code *v203;
  code *v229;
  code *v68;
  code *v160;
  code *v178;
  code *v67;
  code *v33;
  code *v182;
  code *v99;
  code *v214;
  code *v215;
  code *v218;
  code *v101;
  code *v93;
  code *v143;
  code *v123;
  code *v184;
  code *v198;
  code *v153;
  code *v41;
  code *v121;
  code *v191;
  code *v105;
  code *v69;
  code *v104;
  code *v82;
  code *v201;
  code *v138;
  code *v174;
  code *v71;
  code *v84;
  code *v37;
  code *v107;
  code *v45;
  code *v183;
  code *v54;
  code *v157;
  code *v122;
  code *v204;
  code *v36;
  code *v75;
  code *v49;
  code *v42;
  code *v199;
  code *v90;
  code *v50;
  code *v161;
  code *v189;
  code *v92;
  code *v200;
  code *v154;
  code *v59;
  code *v113;
  code *v149;
  code *v129;
  uint64_t v142;
  code *v119;
  code *v166;
  code *v106;
  code *v98;
  code *v103;
  code *v192;
  code *v43;
  code *v179;
  code *v115;
  code *v124;
  code *v195;
  code *v188;
  code *v60;
  code *v194;
  code *v66;
  code *v209;
  long v95;
  code *v140;
  code *v208;
  code *v235;
  code *v225;
  code *v144;
  code *v57;
  code *v177;
  code *v58;
  code *v241_x00100;
  code *v241_x00101;
  code *v241_x00102;
  code *v241_x00103;
  code *v241_x00104;
  code *v241_x00105;
  code *v241_x00106;
  code *v241_x00107;
  code *v241_x00108;
  code *v241_x00109;
  code *v241_x00110;
  code *v241_x00111;
  code *v240;
  code *v76;
  code *v216;
  code *v51;
  code *v108;
  code *v222;
  code *v173;
  code *v34;
  code *v145;
  code *v230;
  code *v48;
  code *v46;
  code *v150;
  code *v116;
  code *v163;
  code *v110;
  code *v118;
  code *v164;
  code *v70;
  code *v202;
  code *v56;
  code *v85;
  code *v72;
  code *v223;
  code *v52;
  code *v61;
  code *v44;
  code *v74;
  code *v78;
  code *v228;
  code *v86;
  code *v77;
  code *v64;
  code *v102;
  code *v133;
  code *v65;
  code *v146;
  code *v187;
  code *v167;
  code *v165;
  code *v220;
  code *v97;
  code *v125;
  code *v80;
  code *v136;
  code *v224;
  code *v73;
  code *v87;
  code *v35;
  code *v207;
  code *v40;
  code *v168;
  code *v114;
  code *v130;
  code *v148;
  code *v151;
  code *v127;
  code *v180;
  code *v38;
  code *v158;
  code *v236;
  code *v217;
  code *v134;
  code *v112;
  code *v55;
  code *v211;
  code *v231;
  code *v196;
  code *v132;
  code *v205;
  code *v185;
  code *v111;
  code *v62;
  code *v193;
  code *v169;
  code *v190;
  code *v91;
  code *v213;
  code *v139;
  code *v128;
  code *v83;
  code *v162;
  code *v100;
  code *v206;
  code *v227;
  code *v79;
  code *v170;
  code *v147;
  code *v226;
  code *v88;
  code *v159;
  code *v53;
  code *v171;
  code *v131;
  code *v155;
  code *v172;
  code *v232;
  code *v156;
  code *v175;
  code *v176;
  code *v109;
  code *v240_x00100;
  code *v240_x00101;
  code *v240_x00102;
  code *v240_x00103;
  code *v240_x00104;
  code *v240_x00105;
  code *v240_x00106;
  code *v240_x00107;
  code *v240_x00108;
  code *v240_x00109;
  code *v240_x00110;
  code *v240_x00111;
  code *v240_x00112;
  code *v240_x00113;
  code *v240_x00114;
  code *v240_x00115;
  code *v240_x00116;
  code *v240_x00117;
  code *v240_x00118;
  code *v240_x00119;
  code *v240_x00120;
  code *v240_x00121;
  code *v240_x00122;
  code *v240_x00123;
  code *v240_x00124;
  code *v240_x00125;
  code *v240_x00126;
  code *v240_x00127;
  code *v240_x00128;
  code *v240_x00129;
  code *v240_x00130;
  code *v240_x00131;
  code *v240_x00132;
  code *v240_x00133;
  code *v240_x00134;
  code *v240_x00135;
  code *v240_x00136;
  code *v240_x00137;
  code *v240_x00138;
  code *v240_x00139;
  code *v240_x00140;
  code *v240_x00141;
  code *v240_x00142;
  code *v240_x00143;
  code *v240_x00144;
  code *v240_x00145;
  code *v240_x00146;
  code *v240_x00147;
  code *v240_x00148;
  code *v240_x00149;
  code *v240_x00150;
  code *v240_x00151;
  code *v240_x00152;
  code *v240_x00153;
  code *v237;
  long v238;
  long v32;
  code *v28;
  code *v27;
  long v30;
  long v31;
  code *v29;
  code *v6;
  code *v242;
  code *v4;
  uint64_t v243;
  rt16 av207;
  uint64_t v246;
  uint64_t v261;
  uint64_t v253;
  code *v274;
  uint64_t v257;
  uint64_t v276;
  code *v247;
  uint64_t v268;
  uint64_t v250;
  uint64_t v254;
  code *v258;
  uint8_t v306 [8];
  uint8_t v305 [8];
  uint8_t v307 [8];
  uint64_t v272;
  uint64_t v275;
  long v252;
  code *v260;
  uint64_t v248;
  code *v259;
  uint64_t v262;
  code *v265;
  uint8_t v271 [8];
  uint64_t v251;
  unsigned long v263;
  uint64_t v269;
  uint64_t v264;
  unsigned long v267;
  uint64_t v249 [2];
  uint64_t v270;
  code *v245;
  code *v255;
  uint64_t v266;
  uint64_t v256;
  code *v273;
  uint64_t v282;
  uint64_t v286;
  uint8_t v309 [8];
  uint8_t v308 [8];
  code *v299;
  uint64_t v287;
  uint64_t v284;
  uint64_t v293;
  uint8_t v301 [8];
  code *v292;
  uint64_t v295;
  uint64_t v281;
  code *v289;
  code *v297;
  long v294;
  code *v285;
  code *v303;
  code *v290;
  code *v278;
  code *v283;
  uint64_t v279;
  uint64_t v302;
  code *v277;
  code *v288;
  code *v298;
  unsigned long v304;
  code *v296;
  uint64_t v280;
  code *v300;
  code *v291;
  uint8_t v310 [8];
  
  av207 = rt_0008e518();
  v304 = (uint64_t)av207.hi;
  v286 = (uint64_t)av207.lo;
  v22 = param_4;
  v3 = param_6;
  rt_00349a68();
  (*G_00658c00)(*(uint64_t *)(v241 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  rt_003509a4();
  v21 = rt_00352968();
  v22 = rt_00377824(v21,v3,v22,&G_0061014c).lo;
  rt_0034e034(param_6);
  rt_00377bec();
  v295 = rt_00027754();
  v21 = rt_0008f6c0();
  rt_00351684();
  v3 = rt_0060e3fc;
  rt_00353f94();
  v256 = v239;
  rt_00352b68();
  rt_00377824();
  rt_00349c44(&v283);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  rt_00352968();
  rt_0035136c();
  rt_00377824();
  rt_003507c8();
  rt_0035053c();
  rt_00377bec();
  v265 = (code *)rt_00027754();
  rt_0034be54();
  rt_00353f94();
  rt_00354840();
  rt_00377824();
  rt_00349c44(&v264);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  v26 = rt_0034c754();
  v281 = rt_00377dcc(v26,v22);
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v63 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034a4f8();
  (*G_00658c00)();
  rt_0034a1b0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034dc9c();
  rt_0035136c(0xff);
  v16 = (code *)rt_00377824().lo;
  rt_0034cf74(param_5);
  rt_00377bec();
  rt_00027754();
  v26 = rt_0008f6c0();
  rt_0034fe08();
  rt_00352e78();
  rt_00377824();
  rt_00349c44(&v245);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  av207 = rt_003509a4();
  rt_00350720(av207.lo,av207.hi,0x672870);
  rt_003515b4();
  rt_003722e4();
  rt_00351f10();
  (*G_00658c00)(*(uint64_t *)(v32 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  rt_003509a4();
  rt_00358d88(param_5);
  rt_0008f6f4();
  rt_00027754();
  rt_0034fe08();
  v272 = v120;
  rt_003569e4();
  rt_00377824();
  rt_00349c44(v301);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  v266 = param_5;
  rt_00350bd8(param_5);
  rt_00377824(0,v89,param_3,&G_0060e458,&G_0060e468);
  rt_00349c44(&v265);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  rt_00351178(0xff);
  v13 = rt_00377824().lo;
  v302 = v22;
  rt_00350494();
  rt_00351238();
  rt_00377bec();
  rt_00351ad4();
  v22 = rt_0008f6c0();
  rt_0034fe08();
  v258 = v152;
  rt_00351e14();
  rt_00377824();
  rt_00349c44(&v299);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  v297 = param_6;
  rt_0035ac58(param_6);
  rt_00351ba0(0xff);
  v8 = (code *)rt_00377824().lo;
  rt_00351354();
  rt_003513f0();
  v10 = rt_00377bec().lo;
  v296 = (code *)rt_00027754();
  v262 = rt_0008f6c0();
  rt_0034fe08();
  v299 = v96;
  rt_00352b68();
  rt_00377824();
  rt_00349c44(&stack_ptr);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  v14 = rt_0034c754();
  rt_00377dcc(v14,v13);
  rt_00348fd8();
  v303 = v28;
  (*G_00658c00)(*(uint64_t *)(v197 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034a9ac();
  (*G_00658c00)();
  rt_0034a400();
  (*G_00658c00)();
  rt_00350464();
  rt_00350798();
  rt_00377dcc();
  rt_003490b8(&v296);
  v245 = v27;
  (*G_00658c00)(*(uint64_t *)(v137 + 0x40));
  rt_003493c4();
  rt_0034d444();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034aadc();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034a4e0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  v13 = rt_0034c754();
  rt_00377dcc(v13,v16);
  rt_003490b8(&v294);
  (*G_00658c00)(*(uint64_t *)(v126 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  rt_003509a4();
  v280 = param_3;
  rt_0007c028();
  v294 = v31;
  (*G_00658c00)(*(uint64_t *)(v210 + 0x40));
  rt_0034ab10();
  rt_0034dfa4();
  (*G_00658c00)();
  rt_0034aac4();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034bc58();
  rt_00350530();
  rt_00377dcc();
  rt_00348ce8();
  v288 = v29;
  (*G_00658c00)(*(uint64_t *)(v181 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00349f5c();
  (*G_00658c00)();
  rt_0034c074();
  rt_0031c220(param_6);
  rt_0034eafc();
  v15 = (*v186)();
  if ((v15 & 1) == 0) {
    rt_00353734();
    v252 = v39;
    rt_0031c250(param_6);
    rt_0034eafc();
    v15 = (*v234)();
    v278 = param_6;
    v279 = param_4;
    if ((v15 & 1) == 0) {
      rt_0031c130(param_6);
      rt_0034eafc();
      v15 = (*v241_x00102)();
      if ((v15 & 1) != 0) {
        rt_0031c1c0(param_6);
        rt_0034eafc();
        v24 = (*v241_x00103)();
        rt_00357a90();
        rt_0031c340();
        if (v24 == '\x01') {
          rt_0006b6f4(v275);
          (*v240_x00131)();
          rt_00352584(&v262);
          rt_0031bc70();
          rt_003523ac();
          rt_0034ba28();
          (*v240_x00132)();
          rt_00353e08();
          rt_003509bc();
          (*v241_x00104)();
        }
        else {
          rt_00353e38();
          (*v240_x00147)(v280,v8);
        }
        goto LBL_00222a2c;
      }
      rt_003584ec();
      v3 = (code *)rt_0031c788();
      rt_00353718();
      rt_00350738();
      (*v3)();
      rt_0031c280(param_6);
      rt_00352f48(&v272);
      rt_00350618();
      (*v240_x00135)();
      rt_00352bbc();
      rt_0034c7f0();
      (*v3)();
      v16 = *(code **)(v238 + 8);
      rt_00350b3c();
      (*v16)();
      rt_0031c2b0(param_6);
      rt_00352f48(&v275);
      rt_00351274();
      (*v240_x00136)();
      rt_0035179c(v307);
      rt_0034c7f0();
      (*v3)();
      rt_00350b3c();
      (*v16)();
      v22 = v295;
      rt_0031c2e0(v295);
      rt_00352098(&v293);
      rt_00350518();
      rt_00352e60();
      (*v240_x00137)();
      v3 = *(code **)(v252 + 8);
      rt_00350aa0();
      (*v3)();
      rt_00351714();
      (*v3)();
      rt_001679cc(v22);
      rt_00351e48(&v302);
      av207 = rt_003509bc();
      (*v240_x00138)(av207.lo,av207.hi,v22);
      rt_003509bc();
      (*v3)();
      rt_003575bc(v22);
      rt_00354134();
      rt_00351160();
      rt_00352e60();
      (*v240_x00139)();
      rt_00351714();
      (*v3)();
      rt_003509bc();
      (*v3)();
      v22 = v302;
      rt_0031c310(v302);
      rt_00351af8(&v281);
      v21 = v280;
      rt_003507c8();
      (*v240_x00140)();
      rt_00352b8c(&v291);
      v3 = (code *)rt_0031c788();
      rt_00353148();
      rt_003504c4();
      (*v3)();
      v16 = *(code **)(v294 + 8U);
      v298 = (code *)((unsigned long)(v294 + 8U) & 0xffffffffffff | 0x4f8000000000000);
      rt_000e72b0();
      (*v16)();
      rt_0031c280(v22);
      rt_00358dc4();
      rt_003507c8();
      v290 = v240_x00141;
      (*v240_x00141)();
      rt_003504c4(v253);
      (*v3)();
      rt_000e72b0();
      (*v16)();
      rt_0031c2b0(v22);
      rt_00353b04();
      rt_003507c8();
      v303 = v240_x00142;
      (*v240_x00142)();
      rt_00351ea8();
      rt_003504c4();
      v300 = v3;
      (*v3)();
      rt_00084174();
      v296 = v16;
      (*v16)();
      rt_00352698(&v290);
      rt_0031c2e0();
      rt_00351e48(v306);
      rt_003509e0();
      rt_0035130c();
      v283 = v240_x00143;
      (*v240_x00143)();
      v16 = v245 + 8;
      v8 = *(code **)v16;
      v277 = (code *)((unsigned long)v16 & 0xffffffffffff | 0x4f8000000000000);
      rt_003504f4();
      (*v8)();
      (*v8)(v253,v270);
      rt_001679cc(v21);
      rt_0035a6e8();
      av207 = rt_003507bc();
      (*v240_x00144)(av207.lo,av207.hi,v21);
      rt_003507bc();
      (*v8)();
      v3 = (code *)rt_001679fc(v21);
      rt_00352ca4(v305);
      rt_00350878(v287);
      (*v3)();
      rt_003507e0();
      (*v8)();
      rt_003515cc();
      (*v8)();
      rt_00350a4c(v21);
      (*v240_x00145)(v287,v284,v281,v295,v270,v21);
      rt_0034d324(v285,v287);
      (*v3)();
      rt_003515cc();
      (*v8)();
      rt_003504f4();
      v288 = v8;
      (*v8)();
      rt_00354abc();
      rt_0031c100();
      rt_003511fc();
      rt_00351384();
      v15 = (*v241_x00105)();
      rt_0031c1c0(v16);
      rt_0034d844();
      v18 = (*v241_x00106)();
      if ((v15 & 1) == 0) {
        rt_00352098(&v281);
        v22 = rt_00350c14();
        v304 = CONCAT44(((v304)>>32),(int)v18);
        (*v290)(v22,v302);
        rt_00352c98(&v291);
        rt_0035764c();
        rt_003507c8(v268);
        (*v240_x00148)();
        rt_000e15d8();
        v3 = v296;
        v16 = v298;
        (*v296)();
        rt_00358dc4();
        rt_0034b88c();
        (*v290)();
        rt_0035a6e8();
        rt_003507c8();
        (*v300)();
        rt_000e72b0();
        (*v3)();
        rt_00352098(&stack_ptr);
        rt_003514e8();
        rt_0035130c();
        (*v283)();
        rt_003507e0();
        v3 = v288;
        (*v288)();
        rt_003507bc();
        (*v3)();
        rt_0031c1f0(v15);
        rt_003523ac();
        v18 = v304 & 0xffffffff;
      }
      else {
        rt_00352098(&v281);
        v22 = rt_00350c14();
        (*v303)(v22,v302);
        rt_00352c98(&v291);
        rt_0035764c();
        rt_003507c8(v268);
        (*v240_x00146)();
        rt_000e15d8();
        v3 = v296;
        v16 = v298;
        (*v296)();
        rt_00358dc4();
        rt_0034b88c();
        (*v303)();
        rt_0035a6e8();
        rt_003507c8();
        (*v300)();
        rt_000e72b0();
        (*v3)();
        rt_00352098(&stack_ptr);
        rt_003514e8();
        rt_0035130c();
        (*v283)();
        rt_003507e0();
        v3 = v288;
        (*v288)();
        rt_003507bc();
        (*v3)();
        rt_0031c1f0(v15);
        rt_003523ac();
      }
      rt_003518f4(v18,v268,v16);
      (*v240_x00149)();
    }
    else {
      rt_0031c370(param_6);
      rt_00351f7c();
      rt_00350618();
      (*v240)();
      v13 = v302;
      rt_0031c3a0(v302);
      rt_003569f0();
      rt_003508cc();
      (*v76)();
      rt_0031c370(v13);
      v300 = v8;
      rt_0035133c();
      rt_003508cc();
      v273 = v216;
      (*v216)();
      rt_00353930(v294);
      rt_00351354();
      v292 = v51;
      (*v51)();
      v9 = v296;
      rt_0035ac40(v296);
      rt_00350b78();
      (*v8)();
      rt_0035a104();
      v285 = (code *)rt_0035305c();
      rt_003509b0();
      v23 = (*v81)();
      v1 = v300;
      v289 = v8;
      if ((((uint32_t)v13 ^ v23) & 1) == 0) {
        rt_0034e140(v9);
        rt_00350b78();
        v15 = (*v221)();
        rt_0034c0b4();
        rt_003509b0();
        v19 = (*v135)();
        if (v19 <= (long)v15) {
          rt_0034d53c();
          rt_003546c0();
          rt_0035145c();
          rt_00351154();
          (*v34)();
          rt_00348c84(v9);
          rt_0034eb64(v1);
          v15 = (*v117)();
          rt_0034d2d4(v288);
          (*v145)();
          goto joined_r0x002205ec;
        }
        av207 = rt_00350494();
        (*v108)(av207.lo,av207.hi,v16);
        rt_00310a74();
        rt_0035034c();
        av207 = rt_000b4390();
        rt_00352a1c(av207.lo,av207.hi,v9);
        (*v222)();
        rt_00348c84();
        rt_00350518();
        rt_003513c0();
        (*v47)();
        rt_003580c4();
        rt_003516e4();
        (*v1)();
        rt_0035145c();
        (*v1)();
        if ((v15 & 1) == 0) goto LBL_002209d4;
LBL_002205f0:
        v26 = v302;
        rt_0031c4f0(v302);
        rt_00351038();
        v13 = v280;
        rt_003505e8();
        (*v202)();
        rt_00358624(v283,v13,v26);
        (*v56)();
        rt_0034ad00();
        rt_0035460c();
        rt_003504ac();
        rt_00351148(&stack_ptr);
        v13 = rt_00377bec().lo;
        rt_0034bc04();
        v10 = rt_0035179c(&stack_ptr);
        v275 = v13;
        (*v85)(v10,0x200,v219,v13);
        rt_0034e784();
        rt_00354cfc();
        rt_0035056c();
        (*v72)();
        rt_0035985c();
        rt_00350780();
        rt_00167a2c();
        rt_00351af8(&v300);
        rt_003511d8(v300);
        v262 = v26;
        (*v223)();
        v8 = *(code **)(v288 + 8);
        v15 = (unsigned long)(v288 + 8) & 0xffffffffffff | 0x4f8000000000000;
        rt_000b4390();
        (*v8)();
        rt_00350c80();
        v1 = v289;
        v26 = (*v289)();
        rt_00350c38();
        v23 = (*v285)();
        v263 = v15;
        v273 = v8;
        if ((((uint32_t)v26 ^ v23) & 1) == 0) {
          rt_00353dfc();
          rt_00310a44();
          v13 = rt_0034c414();
          v15 = (*v67)(v13,v26);
          rt_0034c368();
          v9 = v283;
          rt_00350c38();
          v18 = (*v33)();
          v8 = v290;
          v6 = v303;
          v20 = v15 == v18;
          if ((long)v15 < (long)v18) {
            rt_0034d1fc();
            av207 = rt_0035084c(v8);
            rt_00352a1c(av207.lo,av207.hi,v296);
            (*v44)();
            rt_00348c84(v242);
            rt_00350a70();
            rt_003513c0();
            (*v182)();
            rt_0034e990();
            rt_00350944();
            (*v74)();
            v4 = v259;
            v6 = v1;
            v8 = v273;
            v255 = v242;
            v1 = v303;
          }
          else {
            rt_00351e84();
            av207 = rt_00350a70();
            (*v86)(av207.lo,av207.hi,rt_0060e3fc);
            rt_00353dfc();
            rt_00350a4c();
            rt_00352bf8();
            rt_00350088();
            rt_00351c64();
            (*v77)();
            rt_00348c84(v15);
            rt_00350ea4();
            rt_0035053c();
            (*v214)();
            v26 = rt_00355884();
            v8 = v273;
            (*v273)(v26,v16);
            rt_00351f88();
            (*v8)();
            v4 = v259;
            v255 = v242;
            v1 = v303;
          }
          goto joined_r0x002209c0;
        }
        rt_00351208();
        rt_0035872c();
        v18 = (*v1)();
        rt_00310a44(v26);
        v13 = rt_0034c414();
        v15 = (*v68)(v13,v26);
        rt_0034c368();
        rt_00350c38();
        v17 = (*v160)();
        v2 = v290;
        v4 = v242;
        if ((v18 & 1) != 0) {
          v20 = v17 == v15;
          if ((long)v17 < (long)v15) {
            rt_00354088();
            rt_00351aa4();
            v9 = v283;
            rt_00351df0();
            (*v52)();
            v6 = v296;
            rt_0034d1fc();
            rt_0035404c();
            rt_00351324();
            rt_0034e494();
            (*v61)();
            rt_00348c84(v6);
            rt_0034c290();
            v15 = (*v178)();
            rt_00350630();
            (*v8)();
            v26 = rt_00356aac();
            (*v8)(v26,v16);
            v2 = v8;
LBL_00221078:
            rt_003566d8();
            v6 = v1;
            v8 = v2;
            v1 = v303;
            goto joined_r0x002209c0;
          }
          rt_00350440();
          v26 = rt_003524e0(&stack_ptr);
          rt_00350cc4(v26,0x100);
          (*v125)();
          rt_00352d34();
          rt_00351cb8();
          rt_00355404();
          (*v80)();
          rt_00348c84(v296);
          rt_0034c290();
          v15 = (*v153)();
          rt_00350630();
          (*v8)();
          if ((v15 & 1) == 0) {
            rt_0034d1fc();
            v26 = rt_00352a64();
            rt_00352a1c(v26,v16,v296);
            (*v127)();
            rt_00348c84(v242);
            v26 = rt_0035964c(v2);
            v9 = v283;
            rt_003513c0(v26,v283);
            (*v104)();
            rt_0034e990();
            rt_003516e4();
            (*v180)();
            v255 = v242;
            goto LBL_00221078;
          }
          rt_0035084c();
          (*v8)();
          v9 = v283;
LBL_00221080:
          rt_0035145c(*(uint64_t *)(v303 + 8));
          (*v82)();
          rt_00352118(v298,v280);
          (*v201)();
          rt_003567bc();
          (*v8)();
          v3 = v278;
          v22 = rt_0031c1c0(v278);
          v22 = rt_003586f0(v22);
          (*v138)(v22,v3);
          rt_003594f4();
          if ((bool)v20) {
            rt_00100efc();
            rt_00351148(&v265);
            rt_00377bec();
            rt_0034b8ec();
            rt_0035179c(v271,0x8000000000000000);
            rt_0007c1c4();
            (*v38)();
          }
          else {
            rt_0034ad00();
            rt_00100efc();
            rt_00351148(v301);
            rt_00377bec();
            rt_00348fb4();
            rt_0035179c(&v292);
            rt_0034b9f8();
            (*v158)();
          }
          rt_0034cea8();
          rt_00353e38();
          rt_0034db18(v9);
          (*v236)();
          goto LBL_00222b90;
        }
        v20 = v15 == v17;
        v8 = v2;
        if ((long)v15 < (long)v17) {
          rt_0034d53c();
          rt_0034f394(v2,v255,v16,v296);
          (*v78)();
          rt_00348c84(v242);
          v9 = v283;
          rt_003513c0(v2,v283);
          (*v99)();
          rt_0034e990();
          rt_00350944();
          (*v228)();
          rt_003566d8();
          rt_003557d8();
          v6 = v1;
          v255 = v242;
          v1 = v303;
joined_r0x002209c0:
          v303 = v6;
          v242 = v4;
          v6 = v303;
          v4 = v255;
          v2 = v8;
          if ((v15 & 1) != 0) goto LBL_00221080;
        }
        else {
          rt_0034ad00();
          v6 = v258;
          rt_003514d0();
          rt_00351148(&v299);
          rt_00377bec();
          rt_00348fb4();
          rt_0035179c(&v287);
          rt_0034b9f8();
          (*v136)();
          rt_0034d9cc();
          rt_003530cc();
          rt_00352864();
          (*v224)();
          rt_0034a7c0();
          rt_00351ee0();
          v9 = v283;
          rt_003518b8();
          rt_003513c0();
          (*v41)();
          rt_0034e990();
          rt_00350944();
          (*v73)();
          rt_003566d8();
          if ((v15 & 1) != 0) {
            rt_00351e84();
            av207 = rt_00350a70();
            (*v87)(av207.lo,av207.hi,rt_0060e3fc);
            rt_00353dfc();
            rt_00350a4c();
            rt_00352bf8();
            av207 = rt_003508b4();
            rt_00351c64(av207.lo,av207.hi,v242);
            (*v35)();
            rt_00348c84(v15);
            rt_00350ea4();
            rt_0035053c();
            (*v121)();
            v26 = rt_00355884();
            rt_003557d8(v26,v16);
            (*v2)();
            rt_00356aac();
            v26 = rt_003566d8();
            (*v2)(v26,v16);
            v255 = v255;
            v1 = v303;
            goto joined_r0x002209c0;
          }
          rt_003557d8(v255,v16);
          (*v2)();
          v1 = v303;
        }
        v303 = v1;
        rt_00351a74();
        v26 = rt_003526b8(&stack_ptr);
        rt_00350cc4(v26,0x200);
        (*v217)();
        rt_00351cb8(v277,v6);
        rt_00355404();
        (*v134)();
        rt_00351190(v242,v300);
        (*v223)();
        rt_003504ac();
        (*v2)();
        v1 = v289;
        v23 = (*v289)(v16,v296);
        rt_00350ab8();
        v25 = (*v285)();
        v8 = v3;
        if (((v23 ^ v25) & 1) != 0) {
          rt_00351208();
          rt_0035872c();
          v5 = (code *)(*v1)();
          rt_0034eff8();
          rt_003510b8();
          v9 = (code *)(*v174)();
          rt_0034e15c();
          rt_00350ab8();
          v7 = (code *)(*v71)();
          v6 = v278;
          v12 = v290;
          if (((unsigned long)v5 & 1) == 0) {
            v20 = v9 == v7;
            if ((long)v9 < (long)v7) {
              rt_0034d53c();
              rt_00355f10();
              av207 = rt_00351384();
              v2 = v296;
LBL_00221610:
              rt_0034f394(av207.lo,av207.hi,v2);
              (*v169)();
              rt_00349b64(v4);
              rt_003513c0(v5,v283);
              (*v49)();
              rt_0034e990();
              rt_0035145c();
              (*v190)();
              v8 = v277;
            }
            else {
              rt_0034ad00();
              rt_003514d0();
              rt_00351148(&v299);
              rt_00377bec();
              rt_00348fb4();
              rt_00351e48(&v287);
              rt_0034b9f8();
              (*v213)();
              rt_0034d9cc();
              v3 = v290;
              rt_0035242c();
              rt_00352864();
              (*v139)();
              rt_0034a7c0();
              rt_00352d70();
              rt_003513c0(v283,v3);
              v9 = (code *)(*v161)();
              rt_0035145c();
              (*v128)();
              v2 = v296;
              v1 = v290;
              v3 = v273;
              v5 = v273;
              if (((unsigned long)v9 & 1) == 0) goto LBL_00221f00;
              rt_00351e84();
              (*v83)(v1,v283,rt_0060e3fc);
              rt_00350a4c(v2);
              rt_0034ec1c();
              (*v162)();
              rt_00349b64(v2);
              rt_0034f4a4();
              v9 = (code *)(*v189)();
              rt_00350c38();
              (*v3)();
              rt_00350a34();
              (*v3)();
              v3 = v16;
              v16 = v242;
              v1 = v303;
            }
            goto joined_r0x00221818;
          }
          v20 = v7 == v9;
          if ((long)v7 < (long)v9) {
            rt_00351e84();
            (*v112)(v12,v283,rt_0060e3fc);
            rt_00353dfc();
            rt_00350a4c();
            rt_0034ec1c();
            (*v55)();
            rt_00349b64(v9);
            rt_0034f4a4();
            v9 = (code *)(*v84)();
            rt_00350c38();
            v3 = v273;
            (*v273)();
            rt_00350a34();
            (*v3)();
            v3 = v16;
            v16 = v242;
            v1 = v303;
            v6 = v278;
            goto joined_r0x00221818;
          }
          rt_00350440();
          v26 = rt_003524e0(&stack_ptr);
          rt_00350cc4(v26,0x100);
          (*v62)();
          v1 = v277;
          rt_00353c18();
          rt_00351cb8();
          rt_00355404();
          (*v193)();
          rt_00355e80();
          rt_0034af04();
          rt_00310954();
          rt_0035066c();
          rt_0034eb64();
          v9 = (code *)(*v75)();
          rt_000b4390();
          v5 = v273;
          (*v273)(v263);
          v6 = v278;
          if (((unsigned long)v9 & 1) != 0) {
            rt_0034d53c();
            rt_00355f10();
            av207 = rt_00351384();
            goto LBL_00221610;
          }
LBL_00221f00:
          rt_00351384();
          (*v5)(v263);
          v3 = rt_0060e3fc;
          v1 = v303;
          v8 = v277;
LBL_00221f20:
          rt_0034ad00();
          v26 = rt_00352c98(&v255);
          rt_00351148(&v245,v26,v248);
          rt_00377bec();
          rt_00348fb4();
          rt_0034ae80();
          (*v240_x00107)();
          rt_0034d558();
          rt_00355430();
          av207 = rt_0034f4b4();
          (*v240_x00108)(av207.lo,av207.hi,v6);
          rt_00358cc8();
          (*v119)(v8,v300,v16);
          rt_0035690c(v4);
          v26 = rt_00354834();
          v288 = v16;
          rt_00351154(v26,v16,v296);
          (*v240_x00109)();
          rt_00350780(v22);
          rt_0035614c();
          rt_003519b4(v308);
          rt_003579f4();
          rt_003515fc();
          (*v240_x00110)();
          v8 = *(code **)(v1 + 8);
          rt_00350630();
          (*v8)();
          rt_00350b78();
          v16 = v285;
          v15 = (*v285)();
          v26 = v279;
          if ((v15 & 1) != 0) {
            rt_00355a40(v4);
            rt_0034e444();
            v19 = (*v9)();
            if (0x40 < v19) {
              rt_00350ab8();
              v15 = (*v16)();
              if ((v15 & 1) == 0) {
                rt_00350ab8();
                v15 = (*v16)();
                rt_0034e444();
                v19 = (*v9)();
                if ((v15 & 1) != 0) {
                  if (v19 < 0x41) {
                    rt_0034ad00();
                    rt_00351148(&v299,v258,v3);
                    rt_00377bec();
                    rt_00348fb4();
                    rt_00352098(&v287);
                    rt_0034b9f8();
                    (*v240_x00111)();
                    rt_0034d9cc();
                    rt_00353074();
                    rt_00351298(v3);
                    (*v240_x00112)();
                    rt_00348c84(v4);
                    rt_0034db78();
                    v9 = (code *)(*v98)();
                    rt_003514d0();
                    (*v8)();
                    v16 = v285;
                    if (((unsigned long)v9 & 1) == 0) goto LBL_002221d8;
                  }
                  else {
                    rt_00352944();
                    rt_00351c34(v4);
                    rt_0001df60();
                    rt_00349630();
                    rt_00353074();
                    rt_0034f394();
                    (*v9)();
                    rt_00348c84(v4);
                    rt_0034db78();
                    v9 = (code *)(*v106)();
                    rt_003514d0();
                    (*v8)();
                    v16 = v285;
                    if (((unsigned long)v9 & 1) == 0) goto LBL_002221ec;
                  }
LBL_00222140:
                  rt_003480e4();
                  goto LBL_0022228c;
                }
                v16 = v285;
                if (v19 < 0x40) goto LBL_002221d8;
              }
              else {
                rt_0034e444();
                v19 = (*v9)();
                if (v19 < 0x40) {
LBL_002221d8:
                  rt_0034d520(v4);
                  rt_00350ab8();
                  (*v103)();
                }
                else {
                  rt_00352944();
                  rt_00351c34(v4);
                  rt_0001df60();
                  rt_00349630();
                  rt_0034f394(v290);
                  (*v9)();
                  rt_00348c84(v4);
                  rt_003513c0(v250,v290);
                  (*v166)();
                  v22 = rt_0035a104();
                  (*v8)(v22,v3);
                  v276 = v250;
                  if (((unsigned long)v9 & 1) != 0) goto LBL_00222140;
                }
              }
            }
          }
LBL_002221ec:
          rt_00355a40(v4);
          rt_0034e444();
          v19 = (*v9)();
          if (v19 < 0x41) {
            rt_0034e444();
            v19 = (*v9)();
            if (v19 == 0x40) {
              rt_00350ab8();
              v15 = (*v16)();
              if ((v15 & 1) == 0) goto LBL_0022220c;
            }
          }
          else {
LBL_0022220c:
            rt_00350ab8();
            v15 = (*v16)();
            rt_0034e444();
            v19 = (*v9)();
            if ((v15 & 1) == 0) {
              if (v19 < 0x40) goto LBL_002222cc;
            }
            else if (v19 < 0x41) {
LBL_002222cc:
              rt_0034d520(v4);
              rt_00350ab8();
              (*v43)();
              goto LBL_002222e0;
            }
            rt_00354270();
            rt_00351c34(v4);
            rt_0001df60();
            rt_00349630();
            rt_00353074();
            rt_0034f394();
            (*v9)();
            rt_00348c84(v4);
            rt_0035190c();
            rt_003513c0();
            v15 = (*v192)();
            rt_003514d0();
            (*v8)();
            if ((v15 & 1) != 0) {
              rt_00347fb4();
LBL_0022228c:
              rt_003523f0();
                    /* WARNING: Subroutine does not return */
              rt_001afe4c();
            }
          }
LBL_002222e0:
          (*v8)(v283,v3);
          rt_00352118(v298,v280);
          (*v179)();
          rt_003567bc();
          rt_00352bbc();
          (*v115)();
          rt_0034d520(v4);
          rt_00350ab8();
          v16 = (code *)(*v124)();
          rt_00350944();
          (*v8)();
          rt_0035a590();
          rt_00358a08();
          v15 = v304;
          rt_00351274();
          v19 = (*v195)();
          rt_0031c788(v8);
          rt_0035441c();
          rt_003519b4();
          rt_00351274();
          v288 = v240_x00113;
          (*v240_x00113)();
          rt_0031c3d0(v295);
          rt_003511fc();
          rt_003509d4();
          v11 = (*v188)();
          rt_00350944(*(uint64_t *)(v252 + 8));
          v296 = v60;
          (*v60)();
          v3 = v278;
          v300 = v16 + -(v19 + v11);
          v298 = v16;
          rt_0031c160(v278);
          rt_00350c74();
          rt_003504f4();
          v18 = (*v194)();
          rt_0034ad00();
          rt_003520b4(&v267);
          v22 = rt_00358828();
          rt_00377bec(v22,v26,v257);
          rt_00350654();
          if ((v18 & 1) == 0) {
            av207 = rt_00350440();
            v22 = rt_0035179c(v249,av207.lo,av207.hi,v257);
            (*v240_x00117)(v22,0x100);
            rt_0034d9cc();
            rt_0034f778(v260,v257);
            (*v240_x00118)();
            v3 = v265;
            rt_00357350();
            v16 = v245;
          }
          else {
            rt_00351a74();
            v22 = rt_00351af8(v249);
            rt_003516b4(v22,0x200);
            (*v240_x00114)();
            rt_0034d9cc();
            rt_0035179c(&stack_ptr);
            rt_0034f778(v15);
            (*v240_x00115)();
            v291 = v298;
            rt_003520b4(&v290);
            v16 = (code *)rt_0031c460();
            rt_0001df60();
            rt_0034b67c();
            (*v16)(v260,v257);
            v16 = v245;
            rt_003507c8();
            (*v240_x00116)();
            v276 = v293;
          }
          v8 = v300;
          v22 = v280;
          if ((long)v300 < 0) {
            rt_0035179c(&v302);
            (*v288)(v279,v297);
            if (SBORROW8(0,(long)v8)) {
                    /* WARNING: Does not return */
              v3 = (code *)SW_BREAK(0x223414);
              (*v3)();
            }
            v291 = (code *)-(long)v8;
            v274 = (code *)rt_0031c430(v295);
            rt_0001df60();
            rt_0034b67c();
            rt_003530cc();
            rt_00356140();
            (*v274)();
            rt_00350aa0();
            (*v296)();
            rt_0035690c(v3);
            rt_003524e0(&v269);
            rt_000dbe70(v276);
            rt_0034f1fc();
            (*v240_x00121)();
            rt_00357350();
          }
          else {
            (*v288)(v276,v279,v297);
            rt_0016796c(v3);
            rt_0035133c();
            rt_0034f1fc(v276,v281,v295);
            (*v240_x00119)();
            v291 = v8;
            v8 = (code *)rt_0031c460(v3);
            rt_0001df60();
            rt_0034b67c();
            rt_00351a2c();
            (*v8)();
            rt_00356224();
            rt_003507c8();
            (*v240_x00120)();
          }
          rt_0031c2e0(v3);
          rt_00351e48(&v298);
          rt_003508cc();
          rt_00351c94();
          (*v240_x00122)();
          v3 = *(code **)(v16 + 8);
          (*v3)(v274,v26);
          rt_003508f0();
          (*v3)();
          v3 = v260;
          goto LBL_00222690;
        }
        rt_00354d08();
        rt_003507a4();
        rt_00100efc();
        v19 = (*v37)();
        rt_0034e15c();
        rt_00350ab8();
        v11 = (*v107)();
        v20 = v19 == v11;
        if (v19 < v11) {
          rt_0034d53c();
          rt_00355f10();
          rt_0034e464();
          rt_0034f394();
          (*v211)();
          rt_00349b64(v4);
          rt_003507c8();
          rt_003513c0();
          (*v45)();
          rt_0034e990();
          rt_0035145c();
          (*v231)();
          v8 = v277;
          v9 = v1;
          v6 = v278;
        }
        else {
          rt_00351e84();
          av207 = rt_003524a4();
          (*v196)(av207.lo,av207.hi,rt_0060e3fc);
          rt_00350a4c(v1);
          rt_0034ec1c();
          (*v132)();
          rt_00349b64(v1);
          rt_003510dc();
          rt_00351220();
          v9 = (code *)(*v183)();
          rt_00350c38();
          (*v2)();
          rt_00350618();
          (*v2)();
          v3 = v16;
          v16 = v242;
          v1 = v303;
          v6 = v278;
        }
joined_r0x00221818:
        if (((unsigned long)v9 & 1) == 0) goto LBL_00221f20;
        (**(code **)(v1 + 8))(v283,v3);
        rt_00352bbc(v300,v16);
        (*v42)();
        rt_00357274();
        rt_00358a08();
        rt_00084180();
        v19 = (*v199)();
        if (v19 == 0) {
          rt_00352118(v298,v280);
          (*v241_x00109)();
          v22 = rt_0031c1c0(v6);
          rt_00350494(v22);
          (*v241_x00110)();
          rt_003594f4();
          if ((bool)v20) {
            v22 = rt_00352140();
            rt_00351148(&v265,v22,v280);
            rt_00377bec();
            rt_0034b8ec();
            rt_0035179c(v271,0x8000000000000000);
            rt_0007c1c4();
            (*v240_x00151)();
          }
          else {
            rt_0034ad00();
            rt_0035266c(&v295);
            rt_00351148(v301);
            rt_00377bec();
            rt_00348fb4();
            rt_0035179c(&v292);
            rt_0034b9f8();
            (*v240_x00152)();
          }
          rt_0034cea8();
          rt_00351a2c();
          rt_0034db18();
          (*v240_x00153)();
        }
        else {
          v22 = rt_0031c1c0(v6);
          rt_00350494(v22);
          (*v90)();
          rt_003594f4();
          if ((bool)v20) {
            rt_00352b8c(&v262);
            rt_0031bc70();
            rt_00351e48(&v254);
            rt_00358bc0();
            rt_0034db18();
            (*v91)();
            rt_003507e0();
            rt_00352118();
            (*v50)();
          }
          else {
            (**(code **)(v294 + 0x20))(v261,v298,v280);
          }
        }
        rt_003525f4();
        av207 = rt_003510a0();
        v3 = v241_x00111;
      }
      else {
        rt_00350b78();
        v1 = (code *)(*v8)();
        rt_0034e15c();
        rt_00350b78();
        v15 = (*v212)();
        rt_0034c0b4();
        rt_003509b0();
        v19 = (*v141)();
        if (((unsigned long)v1 & 1) == 0) {
          if (v19 <= (long)v15) {
            rt_0034ad00();
            rt_003516e4();
            rt_00351148(&v299);
            rt_00377bec();
            rt_00348fb4();
            rt_00352ca4(&v287);
            rt_0034b9f8();
            (*v116)();
            rt_0034c7d4();
            rt_00353074();
            rt_003516a8(v1);
            (*v163)();
            rt_0034a7c0();
            rt_00310b08();
            rt_00350164();
            rt_003513c0();
            (*v233)();
            rt_003580c4();
            rt_003514d0();
            (*v1)();
            v9 = v296;
            if ((v15 & 1) == 0) {
              rt_0035145c();
              (*v1)();
              goto LBL_002209d4;
            }
            goto LBL_0022052c;
          }
          rt_00351d0c();
          v13 = rt_00359f6c();
          (*v173)(v13,v300,v16);
          rt_0034d53c();
          av207 = rt_0034f514();
          v9 = v296;
        }
        else {
          if (v19 < (long)v15) {
LBL_0022052c:
            v9 = v296;
            rt_0034d1fc();
            rt_003546c0();
            rt_0035145c();
            rt_0034e494();
            (*v110)();
            rt_00348c84(v9);
            rt_0034eb64(v300);
            (*v203)();
            v13 = rt_0034cbc4();
            (*v118)(v13,v16);
            goto joined_r0x002205ec;
          }
          rt_0034ad00();
          v9 = v299;
          rt_00351384();
          rt_00351148(&stack_ptr);
          rt_00377bec();
          rt_00348fb4();
          rt_00352ca4(&stack_ptr);
          rt_0034b9f8();
          (*v230)();
          rt_0034c7d4();
          rt_003546c0();
          rt_00350b84(v1);
          (*v48)();
          rt_00352c8c();
          rt_00348c84();
          rt_00357508();
          rt_0034eb64();
          (*v94)();
          v13 = rt_0034cbc4();
          (*v46)(v13,v16);
          if ((v15 & 1) != 0) {
            rt_0035145c();
            (*v150)();
            goto LBL_002205f0;
          }
          rt_00351d0c();
          av207 = rt_00350494();
          (*v164)(av207.lo,av207.hi,v16);
          rt_0034d53c();
          av207 = rt_0034f514();
        }
        rt_0034f394(av207.lo,av207.hi,v9);
        (*v70)();
        rt_00348c84();
        rt_00350a70();
        rt_003513c0();
        (*v229)();
        rt_003580c4();
        rt_00350944();
        (*v1)();
        rt_0035145c();
        (*v1)();
joined_r0x002205ec:
        if ((v15 & 1) != 0) goto LBL_002205f0;
LBL_002209d4:
        rt_0031c310(v302);
        rt_0034df84(v298);
        (*v64)();
        rt_003519b4(&v279);
        rt_0008e388();
        rt_00358624();
        (*v102)();
        rt_00350ab8();
        v3 = v285;
        v23 = (*v285)();
        rt_00351160();
        v25 = (*v289)();
        if (((v23 ^ v25) & 1) == 0) {
          rt_0034e15c();
          rt_0034e444();
          v19 = (*v101)();
          rt_0034c368();
          rt_00351160();
          v11 = (*v93)();
          v8 = v288;
          if (v19 < v11) {
            rt_0034d1fc();
            rt_003546c0();
            rt_00350944();
            rt_0034e494();
            (*v133)();
            rt_00348c84(v9);
LBL_00220b40:
            rt_0034cf74(v3);
            v15 = (*v143)();
            rt_0034d2d4(v8);
            (*v146)();
            v3 = v278;
          }
          else {
            rt_00352bb0();
            rt_003537f0();
LBL_00220b70:
            rt_00350c08();
            (*v187)();
            rt_0034d53c();
            rt_00353074();
            av207 = rt_003504ac();
            rt_0034f394(av207.lo,av207.hi,v9);
            (*v167)();
            rt_00348c84(v242);
            rt_0034db78();
            v15 = (*v123)();
            v242 = v303 + 8;
            v3 = *(code **)v242;
            rt_003514d0();
            (*v3)();
            rt_00350944();
            (*v3)();
            v3 = v278;
          }
joined_r0x00221014:
          if ((v15 & 1) != 0) {
LBL_00220be8:
            (*v292)(v298,v280);
            rt_00350630(*(uint64_t *)(v8 + 8));
            (*v184)();
            v22 = rt_0031c1c0(v3);
            v22 = rt_003586f0(v22);
            v24 = (*v198)(v22,v3);
            rt_0031c340(v302);
            if (v24 == '\x01') {
              rt_003526b8(&v281);
              rt_003508b4();
              (*v165)();
              rt_00352584(&v262);
              rt_0031bc70();
              rt_003523ac();
              rt_00351554(v3);
              (*v220)();
              rt_0035190c();
              (*v292)();
            }
            else {
              rt_00353e38();
              rt_003508b4();
              (*v97)();
            }
            goto LBL_00222b90;
          }
        }
        else {
          rt_00350ab8();
          v3 = (code *)(*v3)();
          rt_0034e15c();
          rt_0034e444();
          v19 = (*v215)();
          rt_0034c368();
          rt_00351160();
          v11 = (*v218)();
          v8 = v288;
          if (((unsigned long)v3 & 1) != 0) {
            if (v11 < v19) {
              rt_00352bb0();
              rt_003537f0();
              goto LBL_00220b70;
            }
            rt_0034ad00();
            rt_003510dc();
            rt_00351148(&v299);
            rt_00377bec();
            rt_00348fb4();
            rt_0034ae80();
            (*v207)();
            rt_0034d558();
            rt_00353074();
            v15 = v263;
            rt_0035256c(v254);
            (*v40)();
            rt_00348c84(v242);
            rt_0034db78();
            v18 = (*v191)();
            v16 = *(code **)(v303 + 8);
            rt_003514d0();
            (*v16)();
            v3 = v278;
            if ((v18 & 1) == 0) {
              v22 = rt_0034d1fc();
              rt_00352bf8(v22,rt_0060e3fc);
              rt_0034e494(v15);
              (*v205)();
              rt_00348c84(v9);
              rt_0034cf74(rt_0060e3fc);
              v15 = (*v54)();
              rt_00353384();
              rt_00350b00();
              (*v185)();
              goto joined_r0x00221014;
            }
            rt_00350944();
            (*v16)();
            goto LBL_00220be8;
          }
          if (v19 < v11) {
            rt_0034d1fc();
            rt_003546c0();
            rt_00350944();
            rt_0034e494();
            (*v65)();
            rt_00348c84(v9);
            goto LBL_00220b40;
          }
          rt_0034ad00();
          rt_0035675c();
          rt_0035190c();
          rt_00351148(&stack_ptr);
          rt_00377bec();
          rt_00348fb4();
          rt_00352ca4(&stack_ptr);
          rt_0034b9f8();
          (*v168)();
          rt_0034d9cc();
          rt_00352bf8();
          rt_003514a0(v1);
          (*v114)();
          rt_0034af04(v9);
          rt_00351ee0();
          rt_003510dc();
          rt_00352b08();
          v15 = (*v105)();
          rt_00353384();
          rt_003509b0();
          (*v130)();
          v3 = v278;
          if ((v15 & 1) != 0) {
            v1 = v8 + 0x10;
            av207 = rt_00350b3c();
            (*v148)(av207.lo,av207.hi,v16);
            rt_0034d53c();
            rt_00355f10();
            av207 = rt_003509b0();
            rt_00351154(av207.lo,av207.hi,v9);
            (*v151)();
            rt_00348c84(v242);
            rt_0034f424(v263);
            v15 = (*v69)();
            v8 = v288;
            v242 = v303 + 8;
            v16 = *(code **)v242;
            (*v16)(v1,rt_0060e3fc);
            rt_00350b00();
            (*v16)();
            goto joined_r0x00221014;
          }
          rt_00353db8();
          (*v157)(v263,rt_0060e3fc);
        }
        rt_00351160();
        v16 = v289;
        v15 = (*v289)();
        if ((v15 & 1) == 0) {
          rt_00351160();
          v16 = (code *)(*v16)();
          rt_0034c368();
          rt_00351160();
          v19 = (*v204)();
          v22 = v266;
          if (((unsigned long)v16 & 1) != 0) {
            if (v19 < 0x41) {
              rt_0034ad00();
              rt_00354b68();
              rt_0035084c();
              rt_00351148(&stack_ptr);
              rt_00377bec();
              rt_00348fb4();
              rt_00354064();
              rt_0034ae80();
              (*v100)();
              rt_0034dc20();
              rt_0035319c();
              rt_00351438();
              (*v206)();
              rt_00348c84(v9);
              rt_00355dfc();
              rt_0034eb64();
              v15 = (*v92)();
              rt_0034d2d4(v288);
              (*v227)();
              v3 = v277;
              if ((v15 & 1) == 0) goto LBL_0022189c;
              goto LBL_00221994;
            }
            v291 = (code *)0x0;
            rt_0034efdc();
            rt_0001df60();
            rt_00349630();
            rt_003546c0();
            rt_0034facc();
            (*v16)();
            rt_00348c84(v9);
            v242 = v300;
            goto LBL_00221550;
          }
          v242 = v300;
          if (v19 < 0x40) goto LBL_0022189c;
LBL_002218b8:
          rt_0034ad00();
          v13 = rt_00353dac(&v295);
          rt_00351148(v301,v13,v280);
          rt_00377bec();
          rt_0034b8ec();
          rt_00351a74();
          v13 = rt_003526b8(&v292);
          rt_0035053c(v13,0x200);
          (*v79)();
          rt_0034e74c();
          rt_003524e0(&v281);
          rt_00352b44(v3);
          (*v170)();
          rt_0035764c(v22);
          rt_00352f48(v309);
          rt_00351274();
          (*v147)();
          rt_003509e0();
          rt_00359a78();
          (*v292)();
          rt_00352584(&v273);
          rt_0035690c();
          rt_00350bb4(v242);
          rt_00351c64();
          (*v226)();
          rt_00350780(v26);
          rt_00167a2c();
          v242 = v247;
        }
        else {
          rt_0034c368();
          v242 = v300;
          rt_00351160();
          v19 = (*v122)();
          v22 = v266;
          if (v19 < 0x40) {
LBL_0022189c:
            rt_003109b4(v9);
            v13 = rt_0034c414();
            v19 = (*v200)(v13,v9);
            if (-1 < v19) goto LBL_002218b8;
          }
          else {
            v291 = (code *)0x0;
            rt_0034efdc();
            rt_0001df60();
            rt_00349630();
            rt_003546c0();
            rt_0034facc();
            (*v16)();
            rt_00348c84(v9);
LBL_00221550:
            rt_0034eb64(v242);
            v15 = (*v36)();
            rt_0034d2d4(v288);
            (*v111)();
            if ((v15 & 1) == 0) goto LBL_002218b8;
          }
LBL_00221994:
          rt_0034ad00();
          v13 = rt_00353dac(&v295);
          rt_00351148(v301,v13,v280);
          rt_00377bec();
          rt_0034b8ec();
          rt_00351a74();
          v13 = rt_003526b8(&v292);
          rt_0035053c(v13,0x200);
          (*v88)();
          rt_0034e74c();
          rt_003524e0(&v281);
          rt_00352b44(v3);
          (*v159)();
          rt_0035764c(v22);
          rt_00352f48(v309);
          rt_00351274();
          (*v53)();
          rt_003509e0();
          rt_00359a78();
          (*v292)();
          rt_0008f6f4(v10);
          rt_0031bc70();
          rt_00353f20();
          rt_0035056c();
          (*v171)();
          rt_00354364();
          rt_0035084c();
          (*v154)();
          rt_00352584(&v273);
          rt_0035690c();
          rt_00351af8(&v266);
          av207 = rt_000b4390();
          rt_00351c64(av207.lo,av207.hi,v9);
          (*v131)();
          rt_00350780(v26);
          rt_0016799c();
        }
        rt_00355430();
        rt_00350ab8();
        rt_0035053c();
        (*v155)();
        v3 = *(code **)(v30 + 8);
        rt_00351f88();
        (*v3)();
        rt_00351e90();
        (*v3)();
        rt_00358a08(v22);
        rt_00351274();
        v3 = (code *)(*v59)();
        rt_003524a4();
        (*v292)();
        rt_0035a590();
        rt_00358a08();
        v15 = v304;
        v10 = v279;
        rt_00351274();
        v283 = v113;
        v19 = (*v113)();
        rt_0031c788(v22);
        rt_0035441c();
        rt_00351af8();
        rt_00351274();
        v288 = v172;
        (*v172)();
        v26 = v295;
        rt_0031c3d0(v295);
        rt_00350c74();
        v13 = v281;
        rt_00351324();
        v290 = v149;
        v11 = (*v149)();
        rt_00353930(v252);
        v277 = v237;
        rt_003505e8();
        v296 = v232;
        (*v232)();
        v300 = v3 + (-v11 - v19);
        v298 = v3;
        rt_0031c190(v278);
        rt_003518e8();
        rt_00350618();
        v18 = (*v129)();
        rt_0034ad00();
        v257 = v256;
        rt_00350524();
        rt_00351148(&v283);
        rt_00377bec();
        rt_00350654();
        if ((v18 & 1) == 0) {
          rt_00350440();
          rt_003526b8(&v304);
          rt_00350578();
          (*v176)();
          rt_0034c384();
          rt_00351e48(&v286);
          rt_0034c674(v15);
          (*v109)();
          v22 = v269;
          v3 = v296;
        }
        else {
          rt_00351a74();
          v14 = rt_003519b4(&v304);
          rt_00352a4c(v14,0x200);
          (*v156)();
          rt_0034c384();
          rt_00352e30();
          rt_0034c674();
          (*v175)();
          rt_00350630();
          v19 = (*v283)();
          rt_00355640();
          (*v288)(v10,v22);
          rt_00351324();
          v11 = (*v290)();
          rt_0035060c();
          v3 = v296;
          (*v296)();
          v291 = (code *)(v11 + v19);
          v16 = (code *)rt_0031c460(v26);
          rt_0001df60();
          rt_0034b67c();
          rt_00351e48(&v286);
          (*v16)(v242);
          rt_003505e8();
          (*v3)();
          v22 = v142;
        }
        v16 = v265;
        rt_00357350();
        v8 = v300;
        if ((long)v300 < 0) {
          rt_003524e0(&v293);
          v10 = rt_003586f0();
          (*v240_x00104)(v10,v297);
          rt_0031c400(v26);
          v10 = rt_0034f654();
          rt_00354840(v10,v13);
          (*v240_x00105)();
          rt_0009461c();
          (*v3)();
          rt_00351714();
          (*v3)();
          if (SBORROW8(0,(long)v8)) {
                    /* WARNING: Does not return */
            v3 = (code *)SW_BREAK(0x223410);
            (*v3)();
          }
          v291 = (code *)-(long)v8;
          v8 = (code *)rt_0031c430(v26);
          rt_0001df60();
          rt_0034b67c();
          rt_003526b8(&stack_ptr);
          (*v8)(v22);
          rt_003512c0();
          (*v3)();
          rt_0035690c(v16);
          rt_00351e48(&v298);
          av207 = rt_000b43d0();
          rt_00352d88(av207.lo,av207.hi,v26);
          (*v240_x00106)();
          v16 = v245;
          v22 = v280;
        }
        else {
          (*v240_x00100)(v22,v279,v297);
          rt_0031c400(v26);
          rt_0035441c();
          rt_003524e0();
          rt_000dbd0c();
          rt_00354840();
          (*v240_x00101)();
          rt_003512c0();
          (*v3)();
          rt_00351714();
          (*v3)();
          rt_0035690c(v16);
          rt_00353148();
          av207 = rt_0009461c();
          rt_00352d88(av207.lo,av207.hi,v26);
          (*v240_x00102)();
          v291 = v300;
          v8 = (code *)rt_0031c460(v16);
          rt_0001df60();
          rt_0034b67c();
          rt_00351e48(&v298);
          (*v8)(v287);
          rt_00351af8(&v280);
          rt_003507c8();
          (*v240_x00103)();
          v257 = v287;
          v22 = v280;
        }
LBL_00222690:
        v8 = v278;
        rt_0031c1c0(v278);
        rt_003514ac();
        v26 = v279;
        rt_003507e0();
        v288 = v66;
        v13 = (*v66)();
        rt_00352474();
        rt_0034fe80();
        (*v240_x00123)();
        rt_00355100(&v291);
        rt_0031c1f0();
        rt_003526b8(&v288);
        rt_00352a1c(v13,v282,v257);
        (*v240_x00124)();
        rt_0035a590();
        rt_0031c640();
        rt_003514ac();
        rt_00084174();
        v19 = (*v209)();
        if (v19 <= (long)v298) {
          rt_000dbd0c(*(uint64_t *)(v16 + 8));
          (*v225)();
          v21 = rt_003525f4();
          (*v144)(v21,v8,v22);
          goto LBL_00222a2c;
        }
        rt_0034ad00();
        v13 = rt_00352584(v310);
        v22 = v281;
        v8 = (code *)rt_00377bec(v13,v281,v251).lo;
        v1 = (code *)rt_0008f728();
        rt_00351a74();
        v13 = rt_00351af8(&v304);
        rt_0034df74(v13,0x200);
        (*v1)();
        v9 = (code *)rt_0008f758(v26);
        rt_003519b4(&stack_ptr);
        rt_00351298(v16);
        (*v9)();
        v20 = (code *)-(long)v300 == (code *)0x0;
        if (SBORROW8(0,(long)v300)) {
                    /* WARNING: Does not return */
          v3 = (code *)SW_BREAK(0x22330c);
          (*v3)();
        }
        v298 = v9;
        v291 = (code *)-(long)v300;
        v9 = (code *)rt_0031c460(v295);
        v300 = v1;
        rt_0001df60();
        rt_0034b67c();
        rt_0035a718();
        (*v9)(v3);
        rt_00353734();
        v283 = (code *)(v95 + 8U & 0xffffffffffff | 0x4f8000000000000);
        rt_00350944();
        v1 = v296;
        (*v296)();
        rt_0031c788(v257);
        rt_0035102c();
        v26 = rt_003586f0();
        (*v240_x00125)(v26,v257);
        rt_00351a74();
        rt_0035a540();
        rt_0034df74();
        (*v300)();
        v277 = v8;
        rt_00352098(&v293);
        rt_0035256c(v16);
        (*v298)();
        rt_00352894(v21);
        rt_0035614c();
        rt_003524e0(&v302);
        v21 = v264;
        rt_00350630();
        rt_00353000();
        (*v240_x00126)();
        rt_00350bf0();
        (*v1)();
        v26 = v295;
        rt_003575bc(v295);
        rt_00353df0();
        rt_00350068();
        (*v240_x00127)();
        rt_00351324();
        (*v1)();
        rt_00350944();
        (*v1)();
        rt_003575b0();
        v13 = rt_00352098(&v304);
        rt_0035130c(v13,0x300);
        (*v300)();
        (*v298)(v257,v8,v22,v256);
        rt_0031c490(v26);
        rt_0035102c();
        rt_0035060c();
        rt_00353000();
        v290 = v240_x00128;
        (*v240_x00128)();
        (*v1)(v257,v22);
        rt_0034afc0(v26);
        av207 = rt_003510ac();
        v15 = (*v140)(av207.lo,av207.hi,v22,v21);
        (*v1)(v3,v22);
        if ((v15 & 1) == 0) {
          v22 = rt_003586f0();
          (*v288)(v22,v278);
          rt_003594f4();
          if ((bool)v20) {
            rt_00353390();
            rt_0031c4c0();
          }
          else {
            rt_00353390();
            rt_0031bfe0();
          }
          rt_003589cc();
          rt_0035179c(&v259);
          v22 = v280;
          rt_003509b0();
          (*v240_x00129)();
          v26 = rt_003575b0();
          rt_00350ac4(v8,v26,0x300);
          (*v300)();
          rt_003524e0(&v302);
          rt_000dbe70(v8);
          (*v298)();
          rt_003526b8(&stack_ptr);
          rt_0034d180();
          (*v290)();
          rt_0009461c();
          v3 = v296;
          (*v296)();
          rt_003509bc();
          (*v3)();
          rt_00351ee0(v21);
          rt_0034b768();
          v15 = (*v57)();
          rt_000b43d0();
          (*v3)();
          rt_003509bc();
          (*v3)();
          if ((v15 & 1) == 0) {
            rt_003520b4(&v290);
            v3 = (code *)rt_0031c3d0();
            rt_00358828();
            rt_003504f4();
            v300 = (code *)(*v3)();
            v296 = *(code **)(v245 + 8);
            rt_003524a4();
            (*v241_x00107)();
            rt_00352698(&v291);
            rt_0031c788();
            rt_00351af8(&stack_ptr);
            rt_00351414();
            (*v240_x00150)();
            rt_003504f4();
            v19 = (*v3)();
            rt_000a6e14();
            (*v296)();
            v15 = v95 + 8U;
            if ((long)v300 <= v19) {
              v15 = v267;
            }
            rt_00352118(v15,v22);
            (*v241_x00108)();
            v3 = *(code **)(v294 + 0x20);
            av207 = rt_003510b8();
            (*v3)(av207.lo,av207.hi,v22);
            (*v3)(v286,v246,v22);
            goto LBL_00222b90;
          }
          rt_003516e4();
          rt_00352118();
          (*v177)();
          rt_00350bc0(&v280);
          rt_00357be0(v249[0]);
          (*v58)();
          rt_003525f4();
          av207 = rt_00351df0();
          v3 = v241_x00100;
        }
        else {
          rt_00351324();
          (*v1)();
          (*v1)(v264,v22);
          rt_00350bc0(&v280);
          rt_00357be0(v249[0]);
          (*v208)();
          v22 = rt_003525f4();
          av207.hi = v267;
          av207.lo = v22;
          v3 = v235;
        }
      }
      (*v3)(av207.lo,av207.hi);
    }
LBL_00222b90:
    v22 = 0;
  }
  else {
    rt_0031c1c0(param_6);
    rt_0034eafc();
    (*v241_x00101)();
    rt_003594f4();
    if ((bool)v244) {
      v22 = rt_00352140();
      rt_00351148(&v265,v22,v280);
      rt_00377bec();
      rt_0034b8ec();
      rt_0035179c(v271,0x8000000000000000);
      rt_0007c1c4();
      (*v240_x00130)();
    }
    else {
      rt_0034ad00();
      rt_0035266c(&v295);
      rt_00351148(v301);
      rt_00377bec();
      rt_00348fb4();
      rt_0035179c(&v292);
      rt_0034b9f8();
      (*v240_x00133)();
    }
    rt_0034cea8();
    rt_00353e38();
    rt_0034db18(v219);
    (*v240_x00134)();
LBL_00222a2c:
    v22 = 1;
  }
  rt_0008e500(v22,v243);
  return;
}



/* FUN_00223508 @ 0x00223508   (est. swift_compare_dispatch)
 * Ghidra: void FUN_00223508( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00223508( void){
  uint32_t v2;
  unsigned long v3;
  unsigned long v4;
  unsigned long v8;
  long v5;
  long v7;
  uint64_t v6;
  uint64_t v39;
  uint64_t v44;
  long v41;
  uint64_t v26;
  long v15;
  code *v25;
  code *v14;
  code *v9;
  code *v21;
  code *v35;
  code *v38;
  code *v11;
  code *v36;
  code *v37;
  code *v22;
  code *v16;
  code *v27;
  code *v13;
  code *v17;
  code *v29;
  code *v12;
  code *v34;
  code *v18;
  code *v31;
  code *v1;
  code *v40;
  code *v33;
  code *v23;
  code *v19;
  code *v24;
  code *v28;
  code *v30;
  code *v10;
  code *v20;
  code *v32;
  code *v42;
  uint32_t v43;
  rt16 v45;
  rt16 av20;
  
  rt_0008e518();
  v45 = rt_0034e8a4();
  rt_00349684(v44);
  rt_003523fc();
  v3 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aab0();
  rt_0034a774();
  rt_003513fc();
  v4 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_00349080();
  (*G_00658c00)(*(uint64_t *)(v41 + 0x40));
  rt_003497b4();
  rt_0034911c();
  (*G_00658c00)(*(uint64_t *)(v15 + 0x40));
  rt_003497b4();
  rt_003557a8();
  rt_003564a4();
  rt_0034ba08();
  (*v42)();
  rt_00354cc0();
  rt_0035305c();
  rt_0034b4a0();
  v2 = (*v25)();
  if (((v43 ^ v2) & 1) == 0) {
    rt_0034c368();
    rt_0035072c();
    v5 = (*v35)();
    rt_0034a588();
    v7 = (*v38)();
    if (v7 <= v5) {
      rt_0034eaac();
      (*v16)();
      rt_0034d1fc();
      rt_00353a84();
      rt_00349f8c();
      (*v33)();
      rt_00348e78();
      goto LBL_002238c0;
    }
    rt_0034de24();
    rt_00350c68();
    (*v11)();
    rt_0034cee8();
    rt_00352200();
    rt_00349f74();
    (*v40)();
    rt_00348c84();
    rt_0034c5ac(v5);
    (*v36)();
    v6 = rt_0034cd04();
    v1 = v37;
  }
  else {
    rt_0034ba08();
    v8 = (*v42)();
    rt_0034c368();
    rt_0035072c();
    v5 = (*v14)();
    rt_0034c0d0();
    rt_0034e064();
    v7 = (*v9)();
    if ((v8 & 1) == 0) {
      if (v5 < v7) {
        v6 = rt_0034de24();
        (*v22)(v6,v45.hi);
        goto LBL_002238f8;
      }
      rt_0034ad00();
      rt_0034c694();
      rt_00377bec();
      rt_003493ec();
      rt_0034abd8();
      (*v28)();
      rt_0034c384();
      av20 = rt_0034d2f4(v26);
      (*v30)(av20.lo,av20.hi,v39);
      rt_0034c480();
      rt_00310b08();
      rt_0034eae8();
      rt_003511cc();
      (*v13)();
      rt_0034c888();
      (*v10)();
      if ((v3 & 1) == 0) goto LBL_00223940;
      rt_0034ee08(*(uint64_t *)(v5 + 0x10));
      (*v17)();
    }
    else {
      if (v5 <= v7) {
        rt_0034ad00();
        rt_0034d364();
        rt_00377bec();
        rt_003493ec();
        rt_0034abd8();
        (*v23)();
        rt_0034c384();
        rt_003534f8();
        rt_0034c674();
        (*v19)();
        rt_003496e8();
        rt_003518b8();
        rt_00350a1c();
        (*v27)();
        rt_0034c870();
        (*v24)();
        if ((v4 & 1) != 0) goto LBL_00223940;
        rt_00350768(*(uint64_t *)(v5 + 0x10));
        (*v34)();
LBL_002238f8:
        rt_0034cee8();
        rt_00352e30();
        rt_00349f74();
        (*v32)();
        rt_00348c84();
        rt_0035063c(v26,v45.lo);
        (*v18)();
        rt_0034d820();
        v6 = v26;
        v1 = v31;
        goto LBL_00223934;
      }
      rt_0034e94c();
      (*v21)();
    }
    rt_0034d1fc();
    rt_00352a64();
    rt_00349f8c();
    (*v20)();
    rt_00348e78();
LBL_002238c0:
    rt_00350974(v45.hi);
    (*v29)();
    v6 = rt_0034e33c();
    v1 = v12;
  }
LBL_00223934:
  (*v1)(v6);
LBL_00223940:
  v6 = rt_00352980();
  rt_0008e500(v6,v26);
  return;
}



/* FUN_00223960 @ 0x00223960   (est. swift_float_parse)
 * Ghidra: void FUN_00223960( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00223960( void){
  unsigned long v8;
  char v12;
  uint16_t v11;
  int v10;
  uint32_t v14;
  uint64_t v9;
  uint64_t v13;
  long v7;
  long v15;
  unsigned long v3;
  void *v2;
  code *v1;
  uint64_t v60;
  uint64_t v59;
  uint16_t v5;
  uint32_t v6;
  uint64_t v57;
  long v38;
  uint64_t v25;
  long v37;
  code *v23;
  code *v18;
  code *v32;
  code *v50;
  code *v54;
  code *v20;
  code *v52;
  code *v53;
  code *v33;
  code *v26;
  code *v39;
  code *v22;
  code *v27;
  code *v43;
  code *v21;
  code *v49;
  code *v28;
  code *v45;
  code *v42;
  code *v35;
  code *v46;
  code *v41;
  code *v17;
  code *v51;
  code *v56;
  code *v48;
  code *v34;
  code *v30;
  code *v36;
  code *v40;
  code *v44;
  code *v19;
  code *v31;
  code *v47;
  code *v29;
  code *v24;
  long v55;
  long v16;
  uint64_t v58;
  float v4;
  uint64_t v63;
  float v61;
  float v64;
  unsigned long v62 [2];
  
  rt_00352c10();
  rt_0008f6f4(v60);
  rt_0008f6f4();
  rt_00027754();
  rt_00351684();
  rt_00349dfc();
  v9 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b250();
  rt_0034e3ac();
  (*G_00658c00)(*(uint64_t *)(v38 + 0x40));
  rt_003493c4();
  rt_0034cde8();
  (*G_00658c00)();
  rt_0034b87c();
  v2 = &G_0061014c;
  rt_0034b7b8();
  rt_00377824();
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034cd40();
  rt_0034b7b8();
  rt_00377824();
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_00349618();
  (*G_00658c00)(*(uint64_t *)(v37 + 0x40));
  rt_00348a34();
  (*G_00658c00)();
  rt_0034aea8();
  (*G_00658c00)();
  rt_0034c2c8();
  v13 = rt_0031c520(v59);
  rt_0034ef18(v13);
  v7 = (*v23)();
  rt_0031c550(v59);
  v13 = rt_003505d0();
  v15 = (*v18)(v13,v59);
  if (v7 == 0xb) {
    if (v15 == 0x34) {
      rt_00351d0c();
      rt_003513a8();
      (*v34)();
      rt_003516f0(v62);
      v10 = rt_00365b6c();
      if (v10 == 0) {
        rt_00354780();
        rt_0008f6f4();
        rt_0031c1c0();
        rt_003518e8();
        rt_00350524();
        v12 = (*v27)();
        rt_0035764c(v9);
        rt_00350470(v25);
        (*v31)();
        rt_00359eb4();
        rt_00350518();
        rt_00351cd0();
        rt_00377bec();
        rt_00350780();
        rt_0034dbe8();
        rt_0035060c();
        v2 = (void *)(*v43)();
        rt_003566b4();
        rt_00350b3c();
        (*v21)();
        rt_0031c788(v9);
        rt_00351590();
        rt_00350470();
        (*v47)();
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v49)();
        rt_00350518();
        rt_00353960();
        rt_00377bec();
        rt_00350950();
        rt_0034d054();
        rt_00350560();
        v3 = (*v28)();
        rt_00353e08();
        rt_00351274();
        (*v45)();
        v8 = 0x8000000000000000;
        if (v12 != '\x01') {
          v8 = 0;
        }
        v62[0] = v8 | ((unsigned long)v2 & 0x7ff) << 0x34 | v3 & 0xfffffffffffff;
      }
      else {
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v54)();
      }
      rt_003568e8();
      v1 = (code *)rt_0031c5b0();
      (*v1)(v57,v62[0],v58,v2);
      return;
    }
LBL_00223cac:
    rt_003513f0();
    ((code)FUN_0021f7b0)();
    rt_00084174(*(uint64_t *)(v16 + 8));
    (*v20)();
    rt_0034ad00();
    rt_0034f534();
    rt_00377bec();
    rt_0034b8ec();
    v9 = rt_00351a74();
    rt_0034cfd4(v63,v9,0x200);
    (*v30)();
    rt_0034cea8();
    rt_00352dd0();
    rt_0034db18();
    (*v36)();
    rt_00356078();
    rt_0031c580();
    rt_00353ce4();
    rt_0034c5ac();
    (*v40)();
    v1 = *(code **)(v55 + 8);
    rt_00350560();
    (*v1)();
    rt_003507d4();
    (*v1)();
  }
  else {
    if (v7 == 8) {
      if (v15 != 0x17) goto LBL_00223cac;
      rt_00351984(v16);
      rt_003513a8();
      (*v48)();
      rt_00350ad0(&v64);
      v10 = rt_00365b6c();
      if (v10 == 0) {
        rt_00354780();
        rt_0008f6f4();
        rt_0031c1c0();
        rt_003518e8();
        rt_00350524();
        v12 = (*v52)();
        rt_0035764c(v9);
        rt_00350470(v25);
        (*v44)();
        rt_00359eb4();
        rt_00350518();
        rt_00351cd0();
        rt_00377bec();
        rt_00350780();
        rt_0034dbe8();
        rt_0035060c();
        v2 = (void *)(*v53)();
        rt_003566b4();
        rt_00350b3c();
        (*v33)();
        rt_0031c788(v9);
        rt_00351590();
        rt_00350470();
        (*v19)();
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v26)();
        rt_00350518();
        rt_00353960();
        rt_00377bec();
        rt_00350950();
        rt_0034d054();
        rt_00350560();
        v14 = (*v39)();
        rt_00353e08();
        rt_00351274();
        (*v22)();
        v6 = 0x80000000;
        if (v12 != '\x01') {
          v6 = 0;
        }
        v4 = (float)(v6 | ((uint32_t)v2 & 0xff) << 0x17 | v14 & 0x7fffff);
      }
      else {
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v50)();
        v4 = v64;
      }
    }
    else {
      if (v7 != 5 || v15 != 10) goto LBL_00223cac;
      rt_00351d0c();
      rt_003513a8(&G_0061014c);
      (*v56)();
      rt_00350810(&v61);
      v10 = rt_00365b6c();
      if (v10 == 0) {
        rt_00354780();
        rt_0008f6f4();
        rt_0031c1c0();
        rt_003518e8();
        rt_00350524();
        v12 = (*v42)();
        rt_0035764c(v9);
        rt_00350470(v25);
        (*v29)();
        rt_00359eb4();
        rt_00350518();
        rt_00351cd0();
        rt_00377bec();
        rt_00350780();
        rt_0034dbe8();
        rt_0035060c();
        v2 = (void *)(*v35)();
        rt_003566b4();
        rt_00350b3c();
        (*v46)();
        rt_0031c788(v9);
        rt_00351590();
        rt_00350470();
        (*v24)();
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v41)();
        rt_00350518();
        rt_00353960();
        rt_00377bec();
        rt_00350950();
        rt_0034d054();
        rt_00350560();
        v11 = (*v17)();
        rt_00353e08();
        rt_00351274();
        (*v51)();
        v5 = 0x8000;
        if (v12 != '\x01') {
          v5 = 0;
        }
        v61 = (float)(v5 | (uint16_t)(((uint32_t)v2 & 0x1f) << 10) | v11 & 0x3ff);
      }
      else {
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v32)();
      }
      v4 = (float)v61;
    }
    rt_003568e8();
    v1 = (code *)rt_0031c5e0();
    (*v1)(v57,v4,v58,v2);
  }
  return;
}



/* FUN_00224114 @ 0x00224114   (est. half_bits_from_fields)
 * Ghidra: uint32_t FUN_00224114(char param_1, uint32_t param_2, uint32_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_00224114(char param_1, uint32_t param_2, uint32_t param_3){
  uint32_t v1;
  
  v1 = 0xffff8000;
  if (param_1 != '\x01') {
    v1 = 0;
  }
  return v1 | param_3 & 0x3ff | (param_2 & 0x1f) << 10;
}



/* FUN_00224134 @ 0x00224134   (est. float_bits_from_fields)
 * Ghidra: uint32_t FUN_00224134(char param_1, uint32_t param_2, uint32_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_00224134(char param_1, uint32_t param_2, uint32_t param_3){
  uint32_t v1;
  
  v1 = 0x80000000;
  if (param_1 != '\x01') {
    v1 = 0;
  }
  return v1 | param_3 & 0x7fffff | (param_2 & 0xff) << 0x17;
}



/* FUN_00224154 @ 0x00224154   (est. double_bits_from_fields)
 * Ghidra: rt16 FUN_00224154(uint64_t param_1, uint64_t param_2, unsigned long param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
rt16 FUN_00224154(uint64_t param_1, uint64_t param_2, unsigned long param_3){
  unsigned long v1;
  uint8_t v3;
  unsigned long v2;
  rt16 v4;
  
  rt_003594f4();
  v1 = 0x8000000000000000;
  if (!(bool)v3) {
    v1 = 0;
  }
  v4.hi = 0;
  v4.lo = v1 | (v2 & 0x7ff) << 0x34 | param_3 & 0xfffffffffffff;
  return v4;
}



/* FUN_00224180 @ 0x00224180   (est. swift_string_protocol_dispatch2)
 * Ghidra: void FUN_00224180(uint64_t param_1, uint64_t param_2, code * param_3, code * param_4, uint64_t param_5)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00224180(uint64_t param_1, uint64_t param_2, code * param_3, code * param_4, uint64_t param_5){
  uint8_t stack_base[512];
  uint8_t *stack_ptr = stack_base;

  bool v17;
  uint32_t v13;
  uint32_t v15;
  code *v8;
  code *v9;
  uint64_t v14;
  code *v10;
  unsigned long v16;
  long v18;
  long v7;
  uint64_t v11;
  long v12;
  code *v1;
  code *v4;
  code *v6;
  code *v3;
  code *v144;
  uint64_t v146;
  long v43;
  long v118;
  long v132;
  code *v90;
  code *v85;
  code *v126;
  code *v111;
  code *v115;
  code *v27;
  code *v142;
  code *v59;
  code *v127;
  code *v92;
  code *v134;
  code *v88;
  code *v34;
  code *v79;
  code *v67;
  code *v141;
  code *v123;
  code *v139;
  code *v47;
  code *v101;
  code *v110;
  code *v46;
  code *v22;
  code *v112;
  code *v69;
  code *v128;
  code *v129;
  code *v131;
  code *v70;
  code *v66;
  code *v93;
  code *v83;
  code *v114;
  code *v119;
  code *v99;
  code *v29;
  code *v81;
  code *v117;
  code *v73;
  code *v48;
  code *v72;
  code *v60;
  code *v121;
  code *v91;
  code *v109;
  code *v50;
  code *v61;
  code *v26;
  code *v74;
  code *v32;
  code *v113;
  code *v40;
  code *v100;
  code *v82;
  code *v124;
  code *v25;
  code *v54;
  code *v36;
  code *v30;
  code *v120;
  code *v65;
  code *v37;
  code *v102;
  code *v145;
  code *v55;
  code *v130;
  code *v38;
  code *v75;
  code *v135;
  code *v108;
  code *v23;
  code *v94;
  code *v140;
  code *v35;
  code *v33;
  code *v97;
  code *v78;
  code *v103;
  code *v76;
  code *v80;
  code *v104;
  code *v49;
  code *v122;
  code *v41;
  code *v62;
  code *v51;
  code *v136;
  code *v39;
  code *v42;
  code *v31;
  code *v53;
  code *v57;
  code *v138;
  code *v63;
  code *v56;
  code *v44;
  code *v71;
  code *v87;
  code *v45;
  code *v95;
  code *v116;
  code *v106;
  code *v105;
  code *v133;
  code *v68;
  code *v84;
  code *v58;
  code *v89;
  code *v137;
  code *v52;
  code *v64;
  code *v24;
  code *v125;
  code *v28;
  code *v107;
  code *v77;
  code *v86;
  code *v96;
  code *v98;
  long v143;
  code *v21;
  long v20;
  long v19;
  code *v5;
  uint64_t v147;
  code *v2;
  uint64_t v148;
  rt16 v159;
  code *v149;
  unsigned long v151;
  uint64_t v154;
  uint64_t v152;
  uint64_t v158;
  uint64_t v156;
  code *v150;
  code *v155;
  code *v157;
  uint64_t v153;
  
  v159 = rt_0008e518();
  v3 = (code *)v159.hi;
  v18 = (uint64_t)v159.lo;
  rt_00359338(param_4);
  rt_00352f54();
  rt_0034eda8();
  rt_00377824();
  rt_0035a700();
  rt_0034cf84();
  rt_00377bec();
  v8 = (code *)rt_00027754();
  rt_0008f6c0();
  rt_00351684();
  rt_00352c28(0);
  rt_00377824();
  rt_00349c44(&stack_ptr);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034c8c8();
  rt_0035a478(param_5);
  rt_00352720();
  rt_00352438();
  rt_00377824();
  rt_0034e54c();
  rt_00377bec();
  v9 = (code *)rt_00027754();
  rt_0034be54();
  rt_00353960(0);
  rt_00377824();
  rt_00349c44(&stack_ptr);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_0034c754();
  v14 = rt_00377dcc();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v43 + 0x40));
  rt_003493c4();
  rt_0034d254();
  (*G_00658c00)();
  rt_0034a1c8();
  (*G_00658c00)();
  rt_0034aac4();
  (*G_00658c00)();
  rt_0034aadc();
  (*G_00658c00)();
  rt_0034a400();
  (*G_00658c00)();
  rt_0034c074();
  rt_00350500();
  v10 = (code *)rt_00377dcc();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v118 + 0x40));
  rt_003493c4();
  rt_0034d294();
  (*G_00658c00)();
  rt_0034aa28();
  rt_003499f0();
  (*G_00658c00)(*(uint64_t *)(v132 + 0x40));
  rt_0034926c();
  (*G_00658c00)();
  rt_0034b640();
  (*G_00658c00)();
  rt_0034ba78();
  (*G_00658c00)();
  rt_0034a464();
  (*G_00658c00)();
  rt_0034bc80();
  rt_0031c0d0();
  rt_00351ac8();
  rt_003508f0();
  v16 = (*v90)();
  v1 = param_3;
  if ((v16 & 1) == 0) {
    rt_0031c520(param_5);
    rt_003511fc();
    v7 = (*v85)(param_3,param_5);
    v11 = rt_0031c520(param_4);
    v11 = rt_00351208(v11);
    v12 = (*v126)(v11,param_4);
    v5 = param_4;
    if (v12 < v7) {
LBL_00224568:
      rt_0031c250();
      rt_00351ac8();
      rt_003508f0();
      v16 = (*v27)();
      if ((v16 & 1) != 0) {
        rt_0031c220();
        rt_00351ac8();
        rt_003508f0();
        v16 = (*v142)();
        if ((v16 & 1) == 0) {
          v1 = (code *)rt_0031c370();
          (*v1)(v157);
          rt_003537f0();
          rt_0031c3a0();
          rt_00350b24();
          rt_003510b8();
          (*v55)();
          rt_0031c370(v5);
          rt_00351f7c();
          rt_003510b8();
          (*v130)();
          rt_00353930(v20);
          (*v38)(rt_0060e3fc,v3);
          rt_0035a44c(v9);
          rt_00100c38();
          v13 = (*v5)();
          rt_00354abc();
          rt_0035305c();
          rt_00350b00();
          rt_00355db4();
          v15 = (*v127)();
          v2 = v8;
          v1 = v157;
          if (((v13 ^ v15) & 1) == 0) {
            rt_0034c368();
            rt_00100c38();
            v6 = (code *)(*v34)();
            rt_0034c0ec();
            rt_00350b00();
            v7 = (*v79)();
            if ((long)v6 < v7) {
              rt_00353a00();
              rt_00356924();
              rt_00352c4c();
              (*v108)();
              rt_0034e1d0();
              rt_00350fec(v150);
              rt_0034c3d4();
              (*v23)();
              rt_0034afc0(v3);
              rt_003502d8(v150);
              (*v67)();
              rt_00355c58();
              rt_003508cc();
              (*v10)();
              rt_00084180();
              (*v10)();
              v4 = v21;
              v1 = v150;
            }
            else {
              rt_0034d1fc();
              rt_00358d7c();
              rt_0034d190();
              rt_00353184();
              (*v35)();
              rt_00348e78(v9);
              v159 = rt_003508f0();
              v4 = (code *)(*v123)(v159.lo,v159.hi,v10,&G_0060ff00);
              rt_00350738();
              (*v33)();
            }
            rt_00355424();
            rt_00358690();
            v2 = v3;
            if (((unsigned long)v4 & 1) != 0) goto LBL_00224bb8;
LBL_00224ebc:
            rt_00357710();
            rt_0031c310();
            rt_00351414(v154);
            (*v138)();
            rt_00351414(v156);
            rt_003571ec();
            (*v63)();
            rt_00352744(v154,v3);
            (*v70)();
            rt_00350630();
            v13 = (*v6)();
            rt_00100c38();
            v15 = (*v5)();
            if (((v13 ^ v15) & 1) == 0) {
              rt_0034c0ec();
              rt_0034e50c();
              v7 = (*v114)();
              rt_0034c368();
              rt_00350a04();
              v12 = (*v119)();
              if (v7 < v12) {
                rt_00310a74(v9);
                rt_0035035c();
                v159 = rt_003505e8();
                rt_00352d88(v159.lo,v159.hi,v2);
                (*v44)();
                rt_003492cc(v9);
                rt_00350b18(v156);
                v16 = (*v99)();
                v1 = *(code **)(v21 + 8);
                rt_00350494();
                (*v1)();
                rt_000dbd0c();
                (*v1)();
              }
              else {
                rt_0034e1d0();
                rt_00353074();
                v159 = rt_000dbd0c();
                rt_0034c3d4(v159.lo,v159.hi,v9);
                (*v87)();
                rt_003492cc(v2);
                rt_0034f5d4(v156);
                v16 = (*v81)();
                v1 = *(code **)(v143 + 8);
                rt_00084180();
                (*v1)();
                rt_003505e8();
                (*v1)();
              }
              rt_00355424();
              goto joined_r0x00225550;
            }
            rt_0034c054();
            v16 = (*v6)();
            rt_0034c0ec();
            v11 = rt_00356c48();
            v7 = (*v66)(v11,v2);
            rt_0034c368();
            rt_00100c38();
            v12 = (*v93)();
            if ((v16 & 1) == 0) {
              if (v7 < v12) {
                rt_0034d1fc();
                rt_00350878(v155,v156);
                rt_0034bdcc();
                (*v71)();
                rt_003492cc(v9);
                rt_0034f494(v155);
                v16 = (*v29)();
                v9 = *(code **)(v21 + 8);
                rt_003505e8();
                (*v9)();
                rt_003514e8();
                (*v9)();
                v9 = v1;
                goto joined_r0x00225550;
              }
              rt_0034ad00();
              v11 = rt_00352584(&stack_ptr);
              rt_00351148(&stack_ptr,v11,v10);
              rt_00377bec();
              rt_003494fc();
              rt_0034b100(&stack_ptr);
              (*v89)();
              rt_0008f758(v14);
              rt_0034d934();
              rt_003508c0();
              (*v137)();
              rt_0034bf48(v9);
              rt_00351ee0();
              rt_00351360();
              rt_0035359c();
              v16 = (*v91)();
              v1 = *(code **)(v21 + 8);
              rt_000a6e14();
              (*v1)();
              if ((v16 & 1) != 0) {
                rt_003506cc();
                rt_003589c0();
                v159 = rt_000dbd0c();
                rt_0034cf64(v159.lo,v159.hi,v9);
                (*v52)();
                rt_003492cc(v6);
                rt_003514d0();
                rt_00351238();
                v16 = (*v109)();
                v1 = *(code **)(v143 + 8);
                (*v1)(param_4,v14);
                rt_00084180();
                (*v1)();
                rt_00355424();
                goto joined_r0x00225550;
              }
              rt_00353db8();
              (*v113)(v156,v14);
              rt_000dbd0c();
              (*v1)();
              rt_00355424();
LBL_00225878:
              rt_00358a08(param_5);
              rt_003508b4();
              v7 = (*v40)();
              v14 = rt_00351208(v152);
              (*v138)(v14,v147);
              rt_00358a08(param_4);
              rt_00350bf0();
              v12 = (*v100)();
              rt_003504ac();
              rt_00352744();
              (*v82)();
              v1 = v9;
              if (v12 < v7) goto LBL_00224494;
              goto LBL_002245a0;
            }
            if (v12 < v7) {
              rt_00310a74(v6);
              rt_0035034c();
              rt_0034cf64(v157,v10,v9);
              (*v56)();
              rt_003492cc(v6);
              rt_0034f494(v156);
              v16 = (*v83)();
              v9 = *(code **)(v143 + 8);
              rt_003514e8();
              (*v9)();
              rt_00084180();
              (*v9)();
              v9 = v1;
joined_r0x00225550:
              v1 = v9;
              if ((v16 & 1) == 0) goto LBL_00225878;
            }
            else {
              rt_0034ad00();
              rt_00356060();
              rt_0035060c();
              rt_00351148(&stack_ptr);
              rt_00377bec();
              rt_003494fc();
              rt_00351af8(&stack_ptr);
              rt_0034c9b8();
              (*v84)();
              rt_0034d558();
              rt_003545e8();
              v159 = rt_0034d374();
              (*v58)(v159.lo,v159.hi,v16);
              rt_003492cc(v6);
              rt_003584ec();
              rt_0034f494();
              v16 = (*v60)();
              v9 = *(code **)(v143 + 8);
              rt_003514e8();
              (*v9)();
              if ((v16 & 1) == 0) {
                rt_00356964();
                rt_00350a4c();
                v159 = rt_003505e8(v155);
                rt_0034ce38(v159.lo,v159.hi,v6);
                (*v86)();
                rt_003492cc(v9);
                rt_0034f374();
                v16 = (*v32)();
                v9 = *(code **)(v21 + 8);
                rt_003509d4();
                (*v9)();
                rt_003514e8();
                (*v9)();
                v9 = v1;
                goto joined_r0x00225550;
              }
              rt_003505e8();
              (*v9)();
              v14 = rt_00351a08();
              (*v121)(v14,v10);
            }
            v9 = *(code **)(*(long *)(v1 + -8) + 8);
            goto LBL_002244b0;
          }
          rt_00100c38();
          v4 = (code *)(*v5)();
          rt_0034c368();
          rt_00350618();
          v6 = (code *)(*v92)();
          rt_0034c0ec();
          v16 = 0;
          rt_00350b00();
          v7 = (*v134)();
          if (((unsigned long)v4 & 1) == 0) {
            if (v7 <= (long)v6) {
              rt_0034ad00();
              rt_003505e8();
              rt_00351148(&stack_ptr);
              v16 = rt_00377bec().lo;
              rt_003494fc();
              rt_0034b100(&stack_ptr);
              (*v80)();
              rt_0034dc20();
              rt_003545e8();
              v159 = rt_0034d810();
              (*v104)(v159.lo,v159.hi,v144);
              rt_00310ad4(v3);
              rt_00351bec();
              rt_00310b08();
              rt_0034e64c();
              rt_00351560();
              (*v47)();
              rt_00355c58();
              rt_003514e8();
              (*v144)();
              rt_00355424();
              v6 = (code *)(v16 & 0xffffffffffff | 0x4f8000000000000);
              rt_00084180();
              (*v144)();
              rt_00358690();
              v2 = v3;
              goto LBL_00224ebc;
            }
            v11 = rt_00356924();
            (*v94)(v11,v157,v10);
            rt_0034e1d0();
            rt_003545e8();
            v159 = rt_00352498();
            rt_003505dc(v159.lo,v159.hi,v9);
            (*v140)();
            rt_0034afc0(v3);
            rt_003502d8(v9);
            (*v141)();
            rt_00355c58();
            (*v4)(v9,v14);
            rt_00084180();
            (*v4)();
            v1 = v3;
            v2 = v3;
          }
          else if (v7 < (long)v6) {
            rt_0034d1fc();
            rt_00358d7c();
            rt_0034d190();
            rt_00353184();
            (*v75)();
            rt_00348e78(v9);
            rt_00351214(v157);
            (*v88)();
            rt_0034bdec();
            rt_00350738();
            (*v135)();
            v16 = 0;
            v2 = v3;
          }
          else {
            rt_0034ad00();
            v11 = rt_00353dac(&stack_ptr);
            rt_00351148(&stack_ptr,v11,v10);
            rt_00377bec();
            rt_003494fc();
            rt_0034b100(&stack_ptr);
            (*v97)();
            rt_0034e74c();
            rt_00353050(v157);
            (*v78)();
            rt_0034afc0(v9);
            rt_00351354();
            rt_00352ea8();
            v16 = (*v139)();
            rt_0035a578();
            rt_00350914();
            (*v103)();
            v6 = v21;
            if ((v16 & 1) != 0) {
              rt_00084180();
              (*v76)();
              rt_00358690();
              goto LBL_00224bb8;
            }
            rt_0034ee58();
            rt_00351dfc();
            (*v49)();
            rt_00310a74(v8);
            rt_0035034c();
            rt_0034ee98();
            rt_003505dc();
            (*v122)();
            rt_0034afc0(v8);
            rt_003502d8(v157);
            (*v101)();
            rt_00355c58();
            rt_003514e8();
            (*v10)();
            rt_00084180();
            (*v10)();
            v1 = v155;
          }
          rt_00355424();
          rt_00358690();
          if ((v16 & 1) == 0) goto LBL_00224ebc;
LBL_00224bb8:
          rt_00359f6c();
          rt_0031c4f0();
          rt_0035133c();
          rt_00100efc();
          (*v41)();
          rt_00100efc(v158);
          rt_003571ec();
          (*v62)();
          rt_003504c4();
          rt_00352744();
          (*v110)();
          rt_00100c38();
          v7 = (*v5)();
          v11 = rt_00350554();
          v13 = (*v6)(v11,v2);
          if ((((uint32_t)v7 ^ v13) & 1) != 0) {
            rt_00100c38();
            v16 = (*v5)();
            rt_0034c368();
            rt_00100c38();
            (*v46)();
            rt_00356c30();
            rt_003507a4();
            rt_003514d0();
            v12 = (*v22)();
            if ((v16 & 1) == 0) {
              if (v7 < v12) {
                rt_00351d0c();
                (*v42)(v155,v157,v10);
                rt_00310a74(v2);
                rt_0034efb8();
                rt_00350fec();
                rt_003505dc();
                (*v31)();
                rt_003492cc(v2);
                rt_00350494();
                rt_00351238();
                v16 = (*v129)();
                v1 = *(code **)(v143 + 8);
                rt_00084180();
                (*v1)();
                rt_0035060c();
                v11 = (*v1)();
                v2 = v8;
              }
              else {
                rt_0034ad00();
                rt_00358954();
                rt_003514e8();
                rt_00351148(&stack_ptr);
                rt_00377bec();
                rt_003494fc();
                rt_00352ca4(&stack_ptr);
                rt_0034c9b8();
                (*v106)();
                rt_0034c7d4();
                rt_00353074();
                rt_0034d778(v16);
                (*v105)();
                rt_0034bf48(v2);
                rt_00310b08();
                rt_00350a40();
                rt_0034f5d4();
                v16 = (*v48)();
                v1 = *(code **)(v143 + 8);
                rt_00084180();
                (*v1)();
                if ((v16 & 1) == 0) {
                  rt_003508cc();
                  (*v1)();
                  goto LBL_0022564c;
                }
                rt_00310a74(v9);
                rt_0035035c();
                v159 = rt_003508cc();
                rt_00353184(v159.lo,v159.hi,v2);
                (*v133)();
                rt_003492cc(v9);
                rt_003507bc();
                rt_00351b2c();
                v16 = (*v72)();
                v11 = rt_0034d170();
                v11 = (*v68)(v11,v10);
              }
            }
            else {
              if (v12 < v7) {
                rt_0034d1fc();
                rt_00353bd0();
                rt_00350068();
                rt_00353184();
                (*v51)();
                rt_003492cc(v9);
                goto LBL_00224e68;
              }
              rt_0034ad00();
              v11 = rt_003520b4(&stack_ptr);
              rt_00351148(&stack_ptr,v11,v10);
              rt_00377bec();
              rt_003494fc();
              rt_0034b100(&stack_ptr);
              (*v45)();
              rt_0034d9cc();
              rt_003547f8();
              rt_00351720();
              (*v95)();
              rt_003492cc(v9);
              rt_0035060c();
              rt_00351b2c();
              v16 = (*v117)();
              rt_003516c0();
              rt_003508fc();
              (*v116)();
              if ((v16 & 1) != 0) {
                rt_00353db8();
                v11 = (*v73)(v158,v14);
                goto LBL_002255f0;
              }
              rt_00351d0c();
              v159 = rt_003509e0();
              (*v64)(v159.lo,v159.hi,v10);
              rt_00310a74(v2);
              rt_0034efb8();
              v159 = rt_003508fc();
              rt_003505dc(v159.lo,v159.hi,v9);
              (*v24)();
              rt_003492cc(v2);
              rt_0034f5d4(v14);
              v16 = (*v50)();
              v1 = *(code **)(v143 + 8);
              (*v1)(v150,v14);
              rt_00084180();
              v11 = (*v1)();
              v14 = v158;
              v2 = v8;
            }
joined_r0x00225380:
            if ((v16 & 1) == 0) goto LBL_0022564c;
LBL_002255f0:
            rt_0034ece8(v11,param_3);
            (**(code **)(v19 + 8))(v18);
            rt_00350738(*(uint64_t *)(v21 + 8));
            (*v61)();
            goto LBL_002244bc;
          }
          rt_0034c368();
          rt_00100c38();
          (*v112)();
          rt_00356c30();
          rt_003507a4();
          rt_003514d0();
          v12 = (*v69)();
          if (v12 <= v7) {
            rt_0034d1fc();
            rt_00353bd0();
            rt_00350068();
            rt_00353184();
            (*v53)();
            rt_003492cc(v9);
LBL_00224e68:
            rt_003504f4();
            rt_00351b2c();
            v16 = (*v131)();
            v11 = rt_0034d170();
            v11 = (*v57)(v11,v10);
            goto joined_r0x00225380;
          }
          rt_00351d0c();
          rt_00351214(v155);
          (*v136)();
          rt_00310a74(v2);
          rt_0034efb8();
          rt_00350fec();
          rt_003505dc();
          (*v39)();
          rt_003492cc(v2);
          rt_00351238(v14,v158);
          v13 = (*v128)();
          v1 = *(code **)(v143 + 8);
          rt_00084180();
          (*v1)();
          v11 = (*v1)(v158,v14);
          v2 = v8;
          if ((v13 & 1) != 0) goto LBL_002255f0;
LBL_0022564c:
          rt_00357a90();
          rt_00358a08();
          v7 = (*v26)(param_3,v14);
          rt_00356924();
          rt_00351214();
          (*v125)();
          rt_0016796c(v2);
          rt_0035034c();
          v159 = rt_00351648();
          rt_0034ce38(v159.lo,v159.hi,v9);
          (*v28)();
          v14 = rt_00351208(v152);
          (*v41)(v14,v147);
          rt_003519b4(&stack_ptr);
          rt_00100efc();
          rt_003571ec();
          (*v107)();
          rt_00350630();
          rt_00352744();
          (*v74)();
          rt_000dbedc();
          rt_00350950();
          rt_0035614c();
          rt_00351354(v151);
          rt_0034beec();
          (*v77)();
          v9 = *(code **)(v143 + 8);
          rt_003508cc();
          (*v9)();
          rt_003514e8();
          (*v9)();
          rt_0034df44();
          v16 = (*v149)();
          if ((v16 & 1) != 0) {
            rt_00358d58(v2);
            rt_003509e0();
            v12 = (*v9)();
            if (0x40 < v12) {
              rt_0034db08();
              v16 = (*v149)();
              if ((v16 & 1) == 0) {
                rt_0034db08();
                v16 = (*v149)();
                rt_003509e0();
                v12 = (*v9)();
                if ((v16 & 1) != 0) {
                  if (0x40 < v12) {
                    rt_00352944();
                    v2 = v8;
                    goto LBL_0022592c;
                  }
                  rt_0034ad00();
                  rt_00358948();
                  rt_00350524();
                  rt_00351148(&stack_ptr);
                  rt_00377bec();
                  rt_00349370();
                  rt_0034b100(&stack_ptr);
                  (*v96)();
                  rt_0034c384();
                  rt_00353c60();
                  rt_0034c674();
                  (*v98)();
                  rt_00348e78(v8);
                  rt_0034f374();
                  (*v25)();
                  rt_0034eeb8();
                  (*v9)();
                  v2 = v8;
                  if ((v151 & 1) == 0) goto LBL_002259fc;
LBL_00225974:
                  rt_003480e4();
                  goto LBL_00225ad0;
                }
                v2 = v8;
                if (v12 < 0x40) goto LBL_002259fc;
              }
              else {
                rt_003509e0();
                v12 = (*v9)();
                if (v12 < 0x40) {
LBL_002259fc:
                  rt_0034bfe0();
                  rt_003509e0();
                  (*v54)();
                }
                else {
                  rt_00352944();
LBL_0022592c:
                  rt_00352d4c(v2);
                  rt_0001df60();
                  rt_00349630();
                  rt_003545e8();
                  rt_0034e4dc();
                  (*v9)();
                  rt_00348e78(v2);
                  rt_0034f374();
                  (*v124)();
                  rt_0034eeb8();
                  (*v9)();
                  if ((v151 & 1) != 0) goto LBL_00225974;
                }
              }
            }
          }
          rt_00358d58(v2);
          rt_003509e0();
          v12 = (*v9)();
          if (v12 < 0x41) {
            rt_003509e0();
            v12 = (*v9)();
            if (v12 == 0x40) {
              rt_0034db08();
              rt_003570f0();
              v16 = (*v120)();
              if ((v16 & 1) == 0) goto LBL_00225a44;
            }
          }
          else {
LBL_00225a44:
            rt_0034db08();
            rt_003570f0();
            v16 = (*v36)();
            rt_003509e0();
            v12 = (*v9)();
            if ((v16 & 1) == 0) {
              if (v12 < 0x40) goto LBL_00225b14;
            }
            else if (v12 < 0x41) {
LBL_00225b14:
              rt_0034bfe0();
              rt_003509e0();
              (*v65)();
              v2 = v8;
              goto LBL_00225b30;
            }
            rt_00354270();
            rt_00352d4c(v8);
            rt_0001df60();
            rt_00349630();
            rt_003545e8();
            rt_0034e4dc();
            (*v9)();
            rt_00348e78(v8);
            rt_0034e51c(v16);
            (*v30)();
            rt_0034eeb8();
            (*v9)();
            v2 = v8;
            if ((v151 & 1) != 0) {
              rt_00347fb4();
LBL_00225ad0:
              rt_003523f0();
                    /* WARNING: Subroutine does not return */
              rt_001afe4c();
            }
          }
LBL_00225b30:
          rt_0035336c();
          (*v37)(v157,v10);
          rt_0034bf2c(v2);
          rt_003509e0();
          v12 = (*v102)();
          rt_00350524();
          (*v9)();
          v1 = param_3;
          if (v12 < v7) goto LBL_00224494;
        }
      }
    }
    else {
      rt_0031c550(param_5);
      rt_003511fc();
      rt_003508b4();
      (*v111)();
      rt_00353b88();
      rt_003560a8();
      rt_0031c550();
      rt_003514ac();
      rt_00350c80();
      v12 = (*v115)();
      v17 = v12 < v18;
      v5 = param_3;
      v18 = v7;
      if (v17) goto LBL_00224568;
    }
LBL_002245a0:
    rt_00358d10();
    rt_0031c610();
    v159 = rt_003509b0(v153);
    rt_00351154(v159.lo,v159.hi,param_5);
    (*v145)();
    v159 = rt_0007c1c4(*(uint64_t *)(v20 + 0x20));
    (*v59)(v159.lo,v159.hi,v3);
    v14 = 0;
  }
  else {
LBL_00224494:
    v9 = *(code **)(*(long *)(v1 + -8) + 8);
LBL_002244b0:
    (*v9)(v18,v1);
LBL_002244bc:
    v14 = 1;
  }
  rt_00352480(v146,v14);
  rt_000839d8();
  rt_0008e500(v148);
  return;
}



/* FUN_00225cbc @ 0x00225cbc   (est. swift_dispatch25)
 * Ghidra: void FUN_00225cbc( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00225cbc( void){
  uint8_t v4;
  char v7;
  char v6;
  uint64_t v10;
  uint64_t v9;
  unsigned long v5;
  uint64_t v8;
  code *v3;
  code *v2;
  long v20;
  long v16;
  code *v13;
  code *v15;
  code *v12;
  code *v14;
  code *v17;
  code *v18;
  long v19;
  long v11;
  uint64_t v21;
  code *v1;
  uint64_t v22;
  rt16 av41;
  uint64_t uStack_28;
  uint64_t v23;
  
  rt_0008e518();
  rt_00353ee4();
  rt_0035899c();
  rt_00350a64();
  rt_00350974();
  rt_00377824();
  v10 = rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v20 + 0x40));
  rt_00348a9c();
  (*G_00658c00)();
  rt_00350464();
  rt_00355b1c();
  rt_0034c454();
  rt_00377824();
  rt_00348ce8();
  (*G_00658c00)(*(uint64_t *)(v16 + 0x40));
  rt_003489c0();
  (*G_00658c00)();
  rt_0034b87c();
  v9 = rt_0008f6f4();
  rt_0008f6c0();
  rt_00027754();
  rt_0034b4ec();
  rt_003524a4();
  rt_0034beec();
  v5 = (*v13)();
  if ((v5 & 1) != 0) {
LBL_00225dd8:
    v4 = 1;
    goto LBL_00225f0c;
  }
  rt_00310b08();
  v8 = rt_003505f4();
  rt_0034beec(v8,v21);
  v5 = (*v15)();
  if ((v5 & 1) != 0) {
    v4 = 0;
    goto LBL_00225f0c;
  }
  v3 = (code *)rt_0031c1c0(v9);
  rt_00351324();
  v7 = (*v3)();
  rt_00351324();
  v6 = (*v3)();
  v4 = v7 == v6;
  if ((bool)v4) {
    v2 = (code *)rt_0031d6d8();
    rt_0035a3f4();
    rt_0035072c();
    (*v2)();
    rt_0035072c();
    (*v2)();
    rt_00356840();
    rt_0034ed88();
    rt_00377bec();
    rt_00027754();
    rt_0034bf48();
    rt_00310b08();
    rt_0034f4d4();
    rt_0034f2b4();
    v5 = (*v12)();
    v1 = *(code **)(v11 + 8);
    rt_003508b4();
    (*v1)();
    rt_0035084c();
    (*v1)();
    if ((v5 & 1) == 0) {
      rt_0035a3f4();
      rt_0035072c();
      (*v2)();
      rt_0035072c();
      (*v2)();
      rt_0034c464(v3);
      rt_0034f2b4();
      v5 = (*v14)();
      rt_003508b4();
      (*v1)();
      rt_0035084c();
      (*v1)();
      if ((v5 & 1) == 0) {
        v2 = (code *)rt_0031c788();
        rt_0035072c(v23);
        (*v2)();
        rt_0035072c(uStack_28);
        (*v2)();
        rt_00356840();
        av41 = rt_003514e8();
        rt_00377bec(av41.lo,av41.hi,v10);
        rt_00027754();
        rt_0034bf48();
        rt_00310b08();
        rt_0034d3a4();
        rt_00351b2c();
        v5 = (*v17)();
        v1 = *(code **)(v19 + 8);
        rt_00350b78();
        (*v1)();
        rt_00350738();
        (*v1)();
        if ((v5 & 1) != 0) goto LBL_00225edc;
        rt_0035072c(v23);
        (*v2)();
        rt_0035072c(uStack_28);
        (*v2)();
        rt_0035044c(v3);
        rt_00351384();
        rt_00351b2c();
        v5 = (*v18)();
        rt_00350b78();
        (*v1)();
        rt_00351360();
        (*v1)();
        if ((v5 & 1) == 0) goto LBL_00225dd8;
      }
      rt_00351324();
      v7 = (*v3)();
      v4 = v7 == '\0';
      goto LBL_00225f0c;
    }
LBL_00225edc:
    rt_00351324();
    (*v3)();
  }
  else {
    rt_00351324();
    (*v3)();
  }
  rt_003594f4();
LBL_00225f0c:
  rt_0008e500(v4,v22);
  return;
}



/* FUN_002260b0 @ 0x002260b0   (est. swift_string_compare)
 * Ghidra: bool FUN_002260b0(unsigned long * param_1, unsigned long param_2, unsigned long param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
bool FUN_002260b0(unsigned long * param_1, unsigned long param_2, unsigned long param_3){
  unsigned long v7;
  unsigned long v8;
  uint32_t v12;
  bool v14;
  char *v5;
  uint64_t v9;
  long v11;
  unsigned long v13;
  unsigned long v10;
  unsigned long v3;
  long v4;
  unsigned long v1;
  unsigned long v6;
  rt16 av74;
  uint64_t v2;
  
  if (param_3 == 0 && param_2 == 0) {
    *param_1 = 0;
    return true;
  }
  v6 = -(param_3 + (param_2 != 0));
  v1 = -param_2;
  if (-1 < (long)param_3) {
    v6 = param_3;
    v1 = param_2;
  }
  if (v6 == 0 && v1 == 0) {
    v2 = 0x985;
    v5 = &G_005be7c0;
    v9 = 0;
  }
  else {
    v11 = LZCOUNT(v1);
    v7 = v11 + 0x40;
    if (v6 != 0) {
      v7 = LZCOUNT(v6);
    }
    if (v7 < 0x4b) {
      v10 = 1L << (0x4a - v7 & 0x3f);
      if (v7 < 0xb) {
        v10 = 0;
      }
      v8 = 0;
      if (v7 < 0xb) {
        v8 = 1L << (10 - v7 & 0x3f);
      }
      av74 = rt_002e648c(v10 << 1,v10 >> 0x3f | v8 << 1,1,0);
      v13 = av74.lo & v1;
      v3 = av74.hi & v6;
      if (v7 < 0xc) {
        v6 = v6 >> (0xb - v7 & 0x3f);
      }
      else {
        v12 = (int)v7 - 0xb;
        v6 = v6 << ((unsigned long)v12 & 0x3f) | (v1 >> 1) >> ((unsigned long)~v12 & 0x3f);
      }
      v11 = 0x7f - v7;
      v1 = v6 & 0xfffffffffffff;
      v14 = v10 < v13;
      if (v8 != v3) {
        v14 = v8 < v3;
      }
      v4 = v11;
      if ((v14) || ((v8 == v3 && v13 == v10 && ((v6 & 1) != 0)))) {
        v4 = 0x80 - v7;
        if (v1 != 0xfffffffffffff) {
          v4 = v11;
        }
        v1 = v6 + 1 & 0xfffffffffffff;
      }
      *param_1 = v1 | param_3 & 0x8000000000000000 |
                 (v4 << 0x34) + 0x3ff0000000000000U & 0x7ff0000000000000;
      return v3 == 0 && v13 == 0;
    }
    if (v6 == 0) {
      if (v1 != 0) {
        *param_1 = ((param_3 & 0x8000000000000000) - (v11 << 0x34) |
                   v1 << (v11 - 0xbU & 0x3f) & 0xfffffffffffff) + 0x43e0000000000000;
        return true;
      }
      v2 = 0xcf8;
      v5 = s_Negative_value_is_not_representa_005ce190;
      v9 = 0x23;
    }
    else {
      v2 = 0xcfc;
      v5 = s_Not_enough_bits_to_represent_the_005cd650;
      v9 = 0x2d;
    }
  }
                    /* WARNING: Subroutine does not return */
  rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v5,v9,2,s_Swift_Integers_swift_005cd680,0x14,2,
               v2,1);
}



/* FUN_00226320 @ 0x00226320   (est. swift_dispatch26)
 * Ghidra: void FUN_00226320(uint64_t param_1, uint64_t param_2, code * param_3, uint64_t param_4, uint64_t param_5, code * param_6, uint64_t param_7)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00226320(uint64_t param_1, uint64_t param_2, code * param_3, uint64_t param_4, uint64_t param_5, code * param_6, uint64_t param_7){
  uint8_t stack_base[512];
  uint8_t *stack_ptr = stack_base;

  uint64_t *v14;
  char v21;
  char v19;
  uint8_t v18;
  uint64_t v20;
  uint64_t v15;
  uint64_t v17;
  code *v13;
  uint64_t v16;
  code *v4;
  code *v10;
  unsigned long v11;
  long v12;
  code *v2;
  code *v5;
  code *v1;
  code *v7;
  code *v6;
  uint64_t v198;
  uint64_t v102;
  uint64_t v76;
  long v200;
  long v53;
  long v162;
  long v182;
  long v117;
  code *v108;
  code *v174;
  code *v148;
  code *v153;
  long v31;
  code *v194;
  long v70;
  code *v176;
  code *v120;
  code *v184;
  code *v115;
  code *v39;
  code *v99;
  code *v80;
  code *v193;
  code *v168;
  code *v190;
  code *v58;
  code *v134;
  code *v145;
  code *v57;
  long v25;
  code *v149;
  code *v84;
  code *v177;
  code *v178;
  code *v181;
  code *v85;
  code *v79;
  code *v122;
  code *v105;
  code *v151;
  code *v163;
  code *v131;
  code *v33;
  long v103;
  code *v157;
  code *v89;
  code *v59;
  code *v88;
  code *v71;
  code *v166;
  code *v118;
  code *v143;
  code *v61;
  long v72;
  code *v29;
  code *v91;
  code *v37;
  code *v150;
  code *v45;
  code *v132;
  code *v104;
  code *v169;
  code *v28;
  code *v65;
  code *v41;
  code *v34;
  code *v164;
  code *v77;
  code *v42;
  code *v135;
  code *v156;
  code *v78;
  code *v165;
  long v130;
  long v50;
  code *v95;
  code *v127;
  code *v110;
  code *v121;
  code *v101;
  code *v139;
  code *v90;
  code *v83;
  code *v87;
  code *v158;
  code *v35;
  code *v146;
  code *v97;
  code *v106;
  code *v160;
  code *v155;
  code *v51;
  code *v159;
  code *v56;
  code *v173;
  code *v81;
  code *v119;
  code *v172;
  code *v195;
  code *v188;
  code *v123;
  code *v48;
  code *v144;
  long v49;
  code *v200_x00100;
  long v200_x00101;
  code *v199;
  code *v66;
  code *v179;
  code *v43;
  code *v92;
  code *v185;
  code *v142;
  code *v26;
  code *v124;
  code *v191;
  code *v40;
  code *v38;
  code *v128;
  code *v98;
  code *v136;
  code *v93;
  code *v100;
  code *v137;
  code *v60;
  code *v167;
  code *v47;
  code *v73;
  code *v62;
  code *v186;
  code *v44;
  code *v52;
  code *v3;
  code *v36;
  code *v64;
  code *v68;
  code *v189;
  code *v74;
  code *v67;
  code *v54;
  code *v86;
  code *v113;
  code *v55;
  code *v125;
  code *v154;
  code *v140;
  code *v138;
  code *v183;
  code *v82;
  code *v107;
  code *v69;
  code *v116;
  code *v187;
  code *v63;
  code *v75;
  code *v27;
  code *v171;
  code *v32;
  code *v141;
  code *v96;
  code *v111;
  code *v126;
  code *v129;
  code *v109;
  code *v147;
  code *v30;
  code *v133;
  code *v196;
  code *v180;
  code *v114;
  code *v94;
  code *v46;
  code *v175;
  code *v192;
  code *v161;
  code *v112;
  code *v170;
  code *v152;
  long v197;
  long v24;
  long v23;
  long v22;
  code *v203;
  code *v8;
  code *v9;
  code *v202;
  code *v201;
  rt16 v246;
  uint64_t v219;
  uint64_t v205;
  uint64_t v208;
  uint64_t v210;
  uint64_t v204;
  uint64_t v217;
  uint64_t v209;
  uint64_t v212;
  code *v215;
  uint64_t v214;
  uint8_t v247 [8];
  uint64_t v211;
  uint64_t v216;
  uint64_t *v218;
  code *v206;
  uint64_t v213;
  long v207;
  uint8_t v248 [8];
  uint8_t v224 [8];
  uint8_t v227 [8];
  uint64_t v238;
  code *v239;
  code *v241;
  code *v228;
  uint8_t v233 [8];
  uint64_t v243;
  uint64_t v232;
  code *v236;
  long v223;
  uint64_t v229;
  code *v237;
  code *v235;
  uint64_t v226;
  uint64_t v244;
  code *v230;
  code *pcStack_68;
  uint64_t v225;
  code *v221;
  code *v220;
  code *v240;
  code *v245;
  code *v234;
  uint64_t v222;
  code *v242;
  code *v231;
  uint8_t v249 [8];
  
  rt_0008e518();
  v244 = param_7;
  v220 = param_6;
  v246 = rt_00358a44();
  v234 = (code *)v246.hi;
  v232 = (uint64_t)v246.lo;
  v20 = rt_0008f6c0(param_6);
  rt_00352968();
  rt_00350b84();
  v15 = rt_00377824().lo;
  rt_00351160();
  rt_0035053c();
  rt_00377bec();
  rt_00351684();
  rt_00353f94();
  rt_00354840();
  rt_00377824();
  rt_00349c44(&v229);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  rt_00359338();
  rt_00352968();
  rt_00351e9c();
  v17 = rt_00377824().lo;
  rt_0034e034();
  rt_00377bec();
  v13 = (code *)rt_00027754();
  rt_0034be54();
  rt_00353f94();
  rt_00352b68();
  rt_00377824();
  rt_00349c44(&v218);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  v16 = rt_0034c754();
  rt_00377dcc(v16,v17);
  rt_003490b8(&v230);
  (*G_00658c00)(*(uint64_t *)(v200 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  v16 = rt_0034c754();
  rt_00377dcc(v16,v15);
  rt_003490b8(&v242);
  (*G_00658c00)(*(uint64_t *)(v53 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  rt_003509a4();
  rt_0034fe08(v20);
  v216 = v102;
  rt_00377824();
  rt_00349c44(&v240);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  v207 = *(long *)(v201 + -8);
  (*G_00658c00)(*(uint64_t *)(v207 + 0x40));
  rt_003497b4();
  rt_003509a4();
  v225 = rt_00027754(param_7);
  rt_0008f6c0();
  v242 = (code *)rt_00358d88();
  rt_0035284c(0xff);
  rt_00377824();
  rt_0034bec4();
  v222 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034c330();
  rt_003504e8();
  v240 = (code *)rt_00377dcc();
  rt_000a6f88();
  v223 = v23;
  (*G_00658c00)(*(uint64_t *)(v162 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034a9e8();
  (*G_00658c00)();
  rt_0034a62c();
  (*G_00658c00)();
  rt_0034aa28();
  rt_0034a688();
  (*G_00658c00)(*(uint64_t *)(v182 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034c074();
  rt_0008f6f4();
  rt_00027754();
  v4 = (code *)rt_0008f6f4();
  rt_003508e4();
  rt_00354ca8();
  v10 = (code *)rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  v246 = rt_0035050c();
  rt_00377824(v246.lo,v246.hi,param_3,&G_0061014c);
  rt_003490b8(&stack_ptr);
  (*G_00658c00)(*(uint64_t *)(v117 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034b758();
  rt_0034ad00();
  v246 = rt_00350a04();
  v16 = rt_00377bec(v246.lo,v246.hi,v10).lo;
  v15 = rt_0034bc04();
  v238 = v16;
  v241 = v10;
  (*v199)(rt_0060e3fc,v15,0x200,v10);
  rt_0034dc20();
  v239 = rt_0060e3fc;
  v228 = v4;
  (*v66)(v17,rt_0060e3fc,param_3,v4);
  rt_0035764c(v203);
  rt_003508f0();
  (*v179)();
  v10 = v240;
  v218 = (uint64_t *)(v22 + 8);
  (*(code *)*v218)(v17,param_3);
  rt_0008412c();
  rt_00377bec();
  v237 = (code *)rt_0034d4b8();
  v9 = v235;
  v15 = rt_00351a74(v235);
  rt_00351378(v15,0x200);
  (*v43)();
  v229 = rt_0034cea8();
  v15 = v226;
  rt_0035348c();
  rt_0034db18();
  (*v92)();
  rt_0031c550(v203);
  rt_003511fc();
  v236 = param_3;
  rt_003508f0();
  v231 = (code *)(*v108)();
  v4 = (code *)rt_0031c460(v225);
  rt_0001df60();
  rt_0034b67c();
  v2 = v221;
  v213 = v16;
  (*v4)(v221,v15);
  v8 = *(code **)(v223 + 8);
  v230 = (code *)((unsigned long)(v223 + 8) & 0xffffffffffff | 0x4f8000000000000);
  pcStack_68 = v8;
  rt_003515cc();
  (*v8)();
  v15 = rt_00351a74(v9);
  v4 = v220;
  (*v237)(v15,0x200,v222);
  rt_0035348c();
  rt_00350938();
  rt_0035a08c();
  (*v185)();
  v15 = v244;
  rt_003195c8(v244);
  rt_00350104();
  rt_003513f0();
  (*v174)();
  rt_003515cc();
  (*v8)();
  rt_003507e0();
  (*v8)();
  rt_003549a8(v4);
  rt_0034bf84();
  v11 = (*v9)();
  if ((v11 & 1) == 0) {
    rt_0034bf84();
    v2 = (code *)(*v9)();
    rt_0034c0d0();
    v12 = (*v194)(v201,v4);
    if (((unsigned long)v2 & 1) == 0) {
      v21 = SBORROW8(v12,0x40);
      v19 = v12 + -0x40 < 0;
      v18 = v12 == 0x40;
      if (0x3f < v12) {
        v231 = (code *)0x0;
        rt_00358a68();
        rt_00349abc();
        rt_00352f48(&stack_ptr);
        rt_0034f838();
        (*v128)();
        rt_00349b64(v4);
        rt_0034e5cc();
        v2 = (code *)(*v190)();
        rt_00353bac();
        v15 = rt_00352d04();
        v8 = v98;
        goto LBL_00226f0c;
      }
      rt_00358a68();
      rt_0034d520();
      rt_000e15d8();
      v8 = v115;
LBL_00226cc4:
      v12 = (*v8)();
      v8 = v236;
    }
    else {
      v12 = rt_00353bac();
      v14 = (uint64_t *)(v70 + 8);
      v21 = SBORROW8(v12,0x40);
      v19 = v12 + -0x40 < 0;
      v18 = v12 == 0x40;
      if (0x40 < v12) {
        v231 = (code *)0x0;
        rt_00358a68();
        rt_00349abc();
        rt_0034dc54();
        rt_0034bf94();
        (*v26)();
        rt_00349b64(v4);
        rt_00355e80();
        rt_0034f424();
        v2 = (code *)(*v176)();
        rt_003504c4(*v14);
        (*v120)();
        goto LBL_00226f1c;
      }
      rt_0034ad00();
      rt_00358828();
      rt_00350630();
      rt_00351148(&v240);
      rt_00377bec();
      rt_00348fb4();
      rt_003526b8(&v245);
      rt_0034b9f8();
      (*v124)();
      rt_0034d558();
      rt_00352f48(&stack_ptr);
      rt_003517cc(v10);
      (*v191)();
      rt_00358a68();
      rt_0034af04();
      rt_00352d70();
      rt_0034e5cc();
      v2 = (code *)(*v39)();
      (*(code *)*v14)(v14,v201);
      v8 = v236;
      if (((unsigned long)v2 & 1) == 0) goto LBL_00226da0;
      rt_0034bfe0();
      rt_0009e234();
      v12 = (*v99)();
    }
    if (v12 == 0) {
LBL_00226f24:
      rt_003507bc();
      (*pcStack_68)();
      v15 = rt_0034f9d8(&stack_ptr);
      (*v58)(v15,v243);
      rt_00350440();
      v15 = rt_003524e0(&stack_ptr);
      rt_00352cbc(v15,0x100);
      rt_00355e8c();
      (*v136)();
      rt_00352b80(v232,v2,v8,v228);
      (*v93)();
      goto LBL_00226fa0;
    }
  }
  else {
    rt_0034c0d0();
    v8 = v234;
    rt_0009e234();
    v12 = (*v148)();
    v21 = SBORROW8(v12,0x3f);
    v19 = v12 + -0x3f < 0;
    v18 = v12 == 0x3f;
    if (v12 < 0x40) {
      rt_0034bfe0();
      rt_0009e234();
      v8 = v184;
      goto LBL_00226cc4;
    }
    v231 = (code *)0x0;
    rt_00349abc(v4);
    rt_0034dc54();
    rt_0034bf94();
    (*v142)();
    rt_00349b64(v4);
    rt_0034f424(v8);
    v2 = (code *)(*v153)();
    rt_00353bac();
    v8 = *(code **)(v31 + 8);
LBL_00226f0c:
    (*v8)(v15,v201);
LBL_00226f1c:
    v8 = v236;
    if (((unsigned long)v2 & 1) != 0) goto LBL_00226f24;
  }
LBL_00226da0:
  v11 = (unsigned long)v218 & 0xffffffffffff;
  rt_00352584(&v225);
  rt_00357c88();
  rt_003526b8(&stack_ptr);
  rt_003510b8();
  (*v40)();
  rt_0034f754();
  v246 = rt_00350630();
  v2 = v206;
  v15 = rt_00377bec(v246.lo,v246.hi,v206).lo;
  rt_0031c640();
  rt_003518e8();
  rt_003510ac();
  v5 = (code *)(*v80)();
  rt_00352584(&v220);
  v1 = (code *)rt_0031c310();
  rt_00352098(&v226);
  rt_00350524();
  (*v1)();
  rt_0031c370(v2);
  rt_003526b8(&stack_ptr);
  rt_00350524();
  v241 = v38;
  (*v38)();
  rt_000e15d8();
  rt_00353df0();
  v218 = (uint64_t *)(v11 | 0x4f8000000000000);
  (*v193)();
  rt_00352b8c(&v221);
  rt_0035a44c();
  rt_00350b00();
  v11 = (*v2)();
  v228 = v2;
  if ((v11 & 1) != 0) {
    rt_0034c0ec();
    rt_00350b00();
    v12 = (*v168)();
    v21 = SBORROW8(v12,0x3f);
    v2 = (code *)(v12 + -0x3f);
    v18 = v12 == 0x3f;
    if (0x3f < v12) {
LBL_00227178:
      v19 = (long)v2 < 0;
      v231 = v5;
      rt_00349abc(v201);
      rt_00351e48(&v243);
      rt_00352d94();
      rt_00352a1c();
      (*v167)();
      rt_00348c84(v201);
      rt_00350c2c();
      rt_003513c0();
      v11 = (*v84)();
      v10 = (code *)(v197 + 8);
      v2 = *(code **)v10;
      (*v2)(v5,v212);
      rt_003514d0();
      (*v2)();
      v4 = v5;
      goto LBL_002271f4;
    }
LBL_00227070:
    rt_0034b4d0();
    rt_00350b00();
    v6 = (code *)(*v57)();
    rt_00355ef8();
    v2 = *(code **)(v25 + 8);
    rt_003514d0();
    (*v2)();
    v12 = (long)v6 - (long)v5;
joined_r0x00227410:
    v18 = v6 == v5;
    v19 = v12 < 0;
    v21 = SBORROW8((long)v6,(long)v5);
    if ((long)v5 <= (long)v6) goto LBL_00227434;
LBL_002271fc:
    rt_00350bc0(&v237);
    rt_00359834();
    (*v177)();
    rt_00358cbc();
    (*pcStack_68)();
LBL_00227220:
    v15 = rt_0034f9d8(&stack_ptr);
    (*v178)(v15,v243);
    v4 = v220;
    rt_0034d354();
    v11 = (*v9)();
    if ((v11 & 1) != 0) {
      rt_0034d354();
      v11 = (*v9)();
      if ((v11 & 1) == 0) {
        rt_0034d354();
        (*v9)();
        rt_0034bb94();
        rt_003557b4();
        v12 = (*v122)();
        if (((unsigned long)v4 & 1) != 0) {
          rt_003536dc(v249);
          if ((bool)v18 || v19 != v21) {
            rt_0034ad00();
            v15 = rt_00352b8c(&v234);
            rt_00351148(&v240,v15,v201);
            rt_00377bec();
            rt_00348fb4();
            rt_0034ae80();
            (*v63)();
            rt_0034cea8();
            rt_00351e48(&stack_ptr);
            rt_0035169c(v211);
            (*v75)();
            rt_00348c84(v8);
            rt_003513c0(v234,v5);
            (*v41)();
            rt_00357760();
            rt_003516e4();
            (*v34)();
            if (((unsigned long)v4 & 1) == 0) {
              rt_0034b4d0();
              v246 = rt_00350b00();
              v201 = (code *)v246.lo;
              v8 = (code *)v246.hi;
              v10 = v95;
              goto LBL_002273a0;
            }
          }
          else {
            v231 = (code *)0x0;
            rt_00349abc(v8);
            rt_0034fb3c();
            (*v73)();
            rt_00348c84(v8);
            rt_0034c344(v234);
            (*v105)();
            rt_00357760();
            rt_003509bc();
            (*v151)();
            if (((unsigned long)v4 & 1) == 0) goto LBL_002273ac;
          }
LBL_00227dc4:
          rt_00352584(&v220);
          rt_0031c340();
          rt_003526b8(&v211);
          rt_00350524();
          (*v27)();
          rt_00352584(v247);
          rt_0031bc70();
          rt_00358f9c();
          v246 = rt_0008e388();
          (*v171)(v246.lo,v246.hi,v4);
          rt_0008e388();
          rt_00353df0();
          rt_003571ec();
          (*v164)();
          goto LBL_00226fa0;
        }
        if (v12 < 0x40) {
          rt_0034e104();
          v10 = v131;
          v4 = v8;
          goto LBL_002273a0;
        }
      }
      else {
        rt_0034eff8();
        v10 = v234;
        rt_0034f294();
        v12 = (*v181)();
        if (v12 < 0x40) {
          rt_003109b4(v4);
          v201 = (code *)rt_0034c6a4();
          v8 = v4;
          v10 = v163;
LBL_002273a0:
          v12 = (*v10)(v201,v8);
          if (v12 < 0) goto LBL_00227dc4;
        }
        else {
          v231 = (code *)0x0;
          rt_00349abc(v4);
          rt_0034dc54();
          rt_0034fe38();
          (*v47)();
          rt_00348c84(v4);
          rt_0034c5ac(v10);
          v4 = (code *)(*v85)();
          rt_00350bc0(v249);
          (*v79)(v8,v201);
          if (((unsigned long)v4 & 1) != 0) goto LBL_00227dc4;
        }
      }
    }
LBL_002273ac:
    rt_00352584(&v220);
    rt_0031c340();
    rt_00358f9c();
    rt_00350524();
    (*v62)();
    goto LBL_00226fa0;
  }
  rt_00350b00();
  (*v2)();
  rt_0034bb94();
  rt_00350b00();
  v12 = (*v134)();
  if (((unsigned long)v2 & 1) == 0) {
    if (v12 < 0x40) goto LBL_00227070;
    v21 = SBORROW8((long)v5,1);
    v2 = v5 + -1;
    v18 = v5 == (code *)1;
    if (0 < (long)v5) goto LBL_00227178;
    rt_00355ef8();
    v2 = *(code **)(v103 + 8);
    rt_003514d0();
    (*v2)();
  }
  else {
    rt_003536dc(&v244);
    if ((bool)v18 || v19 != v21) {
      v238 = v15;
      rt_0035955c();
      rt_0034ad00();
      rt_003510dc();
      rt_00351148(&v218);
      rt_00377bec();
      rt_00348fb4();
      rt_0034ae80();
      (*v137)();
      rt_0034d558();
      rt_00351e48(&v243);
      rt_0035256c(v219);
      (*v60)();
      rt_00348c84(v201);
      rt_00350a34();
      rt_003513c0();
      v11 = (*v149)();
      v2 = *(code **)v10;
      rt_003516e4();
      (*v2)();
      if ((v11 & 1) == 0) {
        rt_0034bfe0();
        rt_00350b3c();
        v6 = (code *)(*v33)();
        rt_00350944();
        (*v2)();
        rt_00354058();
        v12 = (long)v6 - (long)v5;
        v4 = v201;
        v15 = v238;
        v10 = v215;
        goto joined_r0x00227410;
      }
      rt_00350944();
      (*v2)();
      goto LBL_002271fc;
    }
    v231 = v5;
    rt_00349abc(v201);
    rt_00352ca4(&v243);
    rt_00352d94();
    rt_00352a1c();
    (*v100)();
    rt_00348c84(v201);
    rt_0009e234();
    rt_003513c0();
    v11 = (*v145)();
    v10 = *(code **)v10;
    rt_003510dc();
    (*v10)();
    (*v10)(v215,v212);
    v2 = v10;
LBL_002271f4:
    if ((v11 & 1) != 0) goto LBL_002271fc;
  }
LBL_00227434:
  v6 = v240;
  v17 = rt_00350c14();
  v7 = (code *)(*v108)(v17,v203);
  v19 = SBORROW8((long)v7,(long)v5);
  v21 = (long)v7 - (long)v5 < 0;
  v18 = v7 == v5;
  if ((long)v7 < (long)v5) {
    v17 = rt_00350c14();
    (*v108)(v17,v203);
    v12 = rt_0035955c();
    v7 = v5 + -v12;
    rt_0034ad00();
    rt_00352c98(v233);
    v17 = rt_00355ea4();
    rt_00351148(&v229,v17,v6);
    v5 = (code *)rt_00377bec().lo;
    rt_0034bc04();
    v17 = rt_003524e0(&v235);
    (*v186)(v17,0x200,v10,v5);
    rt_0034d558();
    rt_00351af8(&v232);
    v246 = rt_0034d1d0();
    (*v44)(v246.lo,v246.hi,v4);
    v21 = SBORROW8((long)v7,1);
    v10 = v7 + -1;
    v19 = (long)v10 < 0;
    v18 = v10 == (code *)0x0;
    if ((bool)v21) {
                    /* WARNING: Does not return */
      v4 = (code *)SW_BREAK(0x228910);
      (*v4)();
    }
    v231 = v10;
    rt_0031c460(v15);
    rt_003516fc();
    v238 = v15;
    rt_00356a08(v209,v1,&v231);
    (*v52)();
    v3 = *(code **)(v24 + 8);
    rt_003507d4();
    (*v36)();
    rt_003575b0();
    v17 = rt_00351e48(&v235);
    rt_00350ac4(v17,0x300);
    rt_00352b80();
    (*v64)();
    rt_003519b4(v248);
    v246 = rt_00350938(v5);
    rt_00355e8c(v246.lo,v246.hi,v4);
    (*v68)();
    rt_00352c98(v227);
    rt_0031c580();
    v17 = rt_0034d934();
    rt_00353cc0(v17,v209);
    (*v189)();
    rt_003508a8();
    rt_003566d8();
    (*v5)();
    rt_00351a74();
    v17 = rt_00351af8(&v235);
    rt_0034df34(v17,0x200);
    rt_00352b80();
    (*v74)();
    rt_00352a64();
    v246 = rt_00350938();
    rt_00355e8c(v246.lo,v246.hi,v198);
    (*v67)();
    rt_00350780(v4);
    rt_0035614c();
    rt_00351af8(v224);
    rt_00355e50();
    rt_0034e034();
    (*v54)();
    rt_003508a8();
    (*v5)();
    rt_003504f4();
    (*v5)();
    rt_00355100(&stack_ptr);
    rt_003575bc();
    rt_003524e0(&v241);
    rt_00350b78();
    rt_00351900();
    (*v86)();
    rt_003507d4();
    (*v5)();
    v231 = v7;
    v15 = rt_0031c430(v15);
    rt_00352d28(v15,&v231);
    rt_003516fc();
    rt_00356a08();
    (*v113)();
    rt_00100efc();
    (*v5)();
    v15 = v225;
    v4 = (code *)rt_00310a74(v225);
    v10 = v221;
    rt_003530a4();
    rt_003514dc();
    rt_00351c64();
    (*v4)();
    v7 = (code *)rt_001679fc(v15);
    rt_0035053c(v217,v10,v245);
    (*v7)();
    rt_003509bc();
    (*pcStack_68)();
    rt_0034cdc8();
    v20 = rt_00377bec(v20,v201,v6).lo;
    rt_00310b08();
    rt_0034c5dc();
    rt_0034df74();
    v11 = (*v157)();
    v214 = v20;
    if ((v11 & 1) == 0) {
      rt_0034c4fc(v20);
      rt_000a6e14();
      rt_0034df74();
      v11 = (*v118)();
      rt_003504f4();
      rt_00355640();
      (*v5)();
      v10 = v240;
      if ((v11 & 1) != 0) {
        rt_00351a74();
        v5 = v235;
        rt_0035a540();
        rt_003538bc();
        (*v82)();
        v6 = v221;
        rt_00353480();
        rt_00350938();
        rt_0035a08c();
        (*v107)();
        rt_00351e48(&stack_ptr);
        rt_0035063c(v217,v6);
        (*v7)();
        rt_003507d4();
        (*pcStack_68)();
        v6 = (code *)rt_00310a14(v15);
        rt_00084180();
        v11 = (*v6)();
        if ((v11 & 1) == 0) {
          rt_0034d354();
          v11 = (*v6)();
          rt_00310a44(v15);
          v20 = rt_0034b814();
          v12 = (*v135)(v20,v15);
          v21 = SBORROW8(v12,0x40);
          v19 = v12 + -0x40 < 0;
          v18 = v12 == 0x40;
          if ((v11 & 1) == 0) goto joined_r0x002280f8;
          if (v12 < 0x41) {
            v20 = rt_00350440().lo;
            rt_003538bc(v235,v20,0x100);
            (*v111)();
            rt_00353c78();
            rt_00350938();
            rt_0035a08c();
            (*v126)();
            rt_0034c61c(v15);
            rt_00310954();
            rt_0034a428();
            v11 = (*v156)();
            rt_003504f4();
            v6 = pcStack_68;
            v4 = v230;
            (*pcStack_68)();
            if ((v11 & 1) == 0) {
              rt_003507bc();
              (*v6)();
              goto LBL_002281a0;
            }
            v20 = rt_0034a034(v15);
            v12 = (*v78)(v20,v15);
            rt_003507bc();
            (*v6)();
            goto LBL_00228120;
          }
        }
        else {
          rt_00310a44(v15);
          v20 = rt_0034b814();
          v12 = (*v143)(v20,v15);
          v21 = SBORROW8(v12,0x3f);
          v19 = v12 + -0x3f < 0;
          v18 = v12 == 0x3f;
joined_r0x002280f8:
          if (v12 < 0x40) {
            v20 = rt_0034a034(v15);
            v12 = (*v121)(v20,v15);
            rt_003507bc();
            (*pcStack_68)();
LBL_00228120:
            v21 = SBORROW8(v12,1);
            v19 = v12 + -1 < 0;
            v18 = v12 == 1;
            v5 = v3;
            if ((bool)v18) goto LBL_002277d4;
            goto LBL_002281a0;
          }
        }
        v231 = (code *)1;
        rt_0035041c();
        rt_0034fe38(v221,&v231,v76,v213);
        (*v4)();
        rt_00349b64(v15);
        rt_00351360();
        rt_0035063c();
        v11 = (*v101)();
        rt_003507d4();
        v6 = pcStack_68;
        (*pcStack_68)();
        rt_003507bc();
        (*v6)();
        rt_003566d8();
        if ((v11 & 1) != 0) goto LBL_002277d4;
      }
LBL_002281a0:
      rt_00358cbc();
      (*pcStack_68)();
    }
    else {
      rt_003504f4();
      rt_00355640();
      (*v5)();
      v10 = v240;
LBL_002277d4:
      v15 = rt_00351a74();
      rt_003538bc(v235,v15,0x200);
      (*v55)();
      rt_0034d1d0(v226);
      rt_0035a08c();
      (*v125)();
      v15 = rt_00310f34(v244);
      rt_000a6e14(v15);
      rt_0035063c();
      v11 = (*v89)();
      rt_003504f4();
      v6 = pcStack_68;
      v4 = v230;
      (*pcStack_68)();
      rt_0006b6f4();
      (*v6)();
      rt_00358720();
      v246 = rt_00351648();
      (*v59)(v246.lo,v246.hi,v10);
      if ((v11 & 1) == 0) {
        rt_0034af04(v225);
        rt_00310b08();
        v15 = rt_00351318();
        rt_0034d344(v15,v245);
        v11 = (*v61)();
        rt_003507d4();
        (*v6)();
        rt_00357250();
        v6 = v245;
        if ((v11 & 1) == 0) goto LBL_002281ac;
      }
      else {
        rt_00358cbc();
        (*v6)();
        rt_00357250();
        v6 = v221;
      }
      rt_00353130();
      v21 = SCARRY8(v72,1);
      v239 = (code *)(v72 + 1);
      v19 = (long)v239 < 0;
      v18 = v239 == (code *)0x0;
      if ((bool)v21) {
                    /* WARNING: Does not return */
        v4 = (code *)SW_BREAK(0x228914);
        (*v4)();
      }
      rt_00351af8(&v214);
      v15 = rt_00350c14();
      (*v1)(v15,v202);
      rt_00350524(v205);
      (*v241)();
      rt_000e72b0();
      rt_00353df0();
      rt_003571ec();
      (*v29)();
      rt_003508b4();
      rt_00356768();
      v11 = (*v202)();
      if ((v11 & 1) == 0) {
        rt_003508b4();
        (*v202)();
        rt_0034bb94();
        rt_003508b4();
        v12 = (*v169)();
        if (((unsigned long)v202 & 1) != 0) {
          rt_003536dc(&v244);
          if ((bool)v18 || v19 != v21) {
            rt_0034ad00();
            rt_003509b0();
            rt_00351148(&v218);
            rt_00377bec();
            rt_00348fb4();
            v242 = v10;
            rt_003526b8(&v216);
            rt_0034b9f8();
            (*v192)();
            rt_0034e74c();
            rt_00351af8(&v243);
            rt_00352b5c(v10);
            (*v161)();
            rt_00348c84(v13);
            rt_00350738();
            rt_00352b08();
            v11 = (*v119)();
            rt_0035a76c(v242);
            rt_00350a04();
            (*v2)();
            if ((v11 & 1) == 0) {
              rt_0034d054(v13);
              rt_00350944();
              v12 = (*v144)();
              rt_00350b6c();
              (*v2)();
              rt_00353130();
              v21 = SBORROW8(v12,v49);
              v19 = v12 - v49 < 0;
              v18 = v12 == v49;
              v10 = v240;
              v4 = v13;
              if (v49 <= v12) goto LBL_002281ac;
            }
            else {
              rt_00350b6c();
              (*v2)();
              v10 = v240;
            }
          }
          else {
            rt_00353130();
            v231 = v28;
            rt_00349abc(v13);
            rt_00352f48(&v243);
            rt_00352d94();
            rt_003569fc();
            (*v187)();
            rt_00348c84(v13);
            rt_003510dc();
            rt_00352b08();
            v11 = (*v65)();
            rt_003509b0();
            (*v2)();
            rt_00350b6c();
            (*v2)();
            v10 = v240;
            if ((v11 & 1) == 0) goto LBL_002281ac;
          }
LBL_00228780:
          (*pcStack_68)(v217,v10);
          rt_00355640(v208,v206);
          (*v5)();
          goto LBL_00227220;
        }
        if (v12 < 0x40) goto LBL_00228004;
        rt_00353130();
        v21 = SBORROW8((long)v172,1);
        v19 = (long)(v172 + -1) < 0;
        v18 = v172 == (code *)1;
        if (0 < (long)v172) {
          v231 = v172;
          rt_00349abc(v13);
          rt_00351af8(&v243);
          rt_00352d94();
          rt_003569fc();
          (*v112)();
          rt_00348c84(v13);
          rt_00350738();
          rt_00352b08();
          v11 = (*v195)();
          rt_00355ef8();
          goto LBL_00228754;
        }
        rt_00355ef8();
        rt_00350b6c(v200_x00101 + 8);
        (*v2)();
      }
      else {
        rt_0034c0ec();
        rt_003508b4();
        v12 = (*v91)();
        v21 = SBORROW8(v12,0x3f);
        v19 = v12 + -0x3f < 0;
        v18 = v12 == 0x3f;
        if (v12 < 0x40) {
LBL_00228004:
          rt_0034b4d0();
          rt_003508b4();
          v12 = (*v165)();
          rt_00355ef8();
          rt_00350b6c(v130 + 8);
          (*v2)();
          rt_00353130();
          v21 = SBORROW8(v12,v50);
          v19 = v12 - v50 < 0;
          v18 = v12 == v50;
          if (v12 < v50) goto LBL_00228780;
        }
        else {
          rt_00353130();
          v231 = v37;
          rt_00349abc(v13);
          rt_00352f48(&v243);
          rt_00352d94();
          rt_003569fc();
          (*v69)();
          rt_00348c84(v13);
          rt_003510dc();
          rt_00352b08();
          v11 = (*v150)();
          rt_00355ef8();
          v6 = v4;
LBL_00228754:
          (*v2)(v6,v7);
          rt_00350b6c();
          (*v2)();
          if ((v11 & 1) != 0) goto LBL_00228780;
        }
      }
    }
LBL_002281ac:
    v2 = v220;
    rt_0034d354();
    (*v9)();
    v11 = rt_00354058();
    v10 = v8;
    if ((v11 & 1) == 0) {
LBL_00228334:
      v13 = (code *)0x0;
      v8 = v10;
    }
    else {
      rt_0034d354();
      v11 = (*v9)();
      if ((v11 & 1) != 0) {
        rt_0034eff8();
        v9 = v234;
        rt_0034f294();
        v12 = (*v139)();
        if (v12 < 0x40) {
          rt_003109b4(v2);
          v13 = (code *)rt_0034c6a4();
          v1 = v146;
          v8 = v2;
          v2 = v9;
LBL_00228324:
          v12 = (*v1)(v13,v8);
          v9 = v2;
          v8 = v10;
          if (v12 < 0) goto LBL_002288d4;
        }
        else {
          v231 = (code *)0x0;
          rt_00349abc(v2);
          rt_0034dc54();
          rt_0034fe38();
          (*v147)();
          rt_00348c84(v2);
          rt_0034c5ac(v9);
          v11 = (*v90)();
          rt_00350bc0(v249);
          (*v83)(v8,v201);
          v2 = v9;
          if ((v11 & 1) != 0) goto LBL_002288d4;
        }
        goto LBL_00228334;
      }
      rt_0034d354();
      (*v9)();
      rt_0034bb94();
      rt_003557b4();
      v12 = (*v87)();
      v10 = v236;
      v9 = v2;
      if (((unsigned long)v2 & 1) == 0) {
        v4 = v201;
        if (v12 < 0x40) {
          rt_0034e104();
          v13 = v201;
          v1 = v97;
          goto LBL_00228324;
        }
        goto LBL_00228334;
      }
      rt_003536dc(v249);
      if ((bool)v18 || v19 != v21) {
        rt_0034ad00();
        v15 = rt_00352b8c(&v234);
        rt_00351148(&v240,v15,v201);
        rt_00377bec();
        rt_00348fb4();
        rt_00351e48(&v245);
        rt_0034b9f8();
        (*v170)();
        rt_0034cea8();
        rt_003519b4(&stack_ptr);
        rt_0035169c(v5);
        (*v152)();
        rt_00348c84(v8);
        v9 = v234;
        rt_00350c80();
        rt_003513c0();
        (*v188)();
        rt_00357760();
        rt_00350944();
        (*v123)();
        if (((unsigned long)v2 & 1) == 0) {
          rt_0034d504(v8);
          rt_00351414();
          (*v200_x00100)();
          rt_003582a8();
          v12 = rt_00354058();
          v2 = v9;
          v10 = v8;
          v4 = v201;
          if (-1 < v12) goto LBL_00228334;
          goto LBL_002288d4;
        }
        v13 = (code *)1;
        rt_003582a8();
        rt_00354058();
        v4 = v201;
      }
      else {
        v231 = (code *)0x0;
        rt_00349abc(v8);
        rt_0034fb3c();
        (*v30)();
        rt_00348c84(v8);
        rt_0034c344(v234);
        (*v158)();
        rt_00357760();
        rt_003509bc();
        (*v35)();
        rt_003582a8();
        v10 = v8;
        if (((unsigned long)v2 & 1) == 0) goto LBL_00228334;
LBL_002288d4:
        v13 = (code *)1;
        v9 = v2;
      }
    }
    v231 = v5;
    rt_00356840();
    rt_00350a70();
    v246 = rt_0035606c();
    rt_00377bec(v246.lo,v246.hi,v9);
    rt_00350950();
    rt_0016796c();
    rt_0034a07c();
    rt_00351e48(&v238);
    rt_0034f838();
    (*v133)();
    rt_0008f6c0(v201);
    rt_00350950();
    rt_00167a2c();
    rt_00352f48(&v239);
    rt_00100c38();
    rt_00351b78();
    (*v196)();
    rt_0035463c();
    v2 = v201 + 8;
    v10 = *(code **)v2;
    rt_00351384();
    (*v10)();
    rt_0035084c();
    (*v10)();
    rt_0031c1f0(v203);
    rt_00358f9c();
    rt_003518f4(v13,v4,v217);
    (*v180)();
    rt_00352698(&stack_ptr);
    rt_0035a44c();
    rt_00355ea4();
    rt_0034df84();
    v11 = (*v13)();
    if ((v11 & 1) == 0) {
      rt_0034df84();
      v11 = (*v13)();
      rt_0034fe48();
      rt_0008e388();
      (*v155)();
      v12 = rt_003566d8();
      if ((v11 & 1) == 0) {
        if (v12 < 0x40) {
          rt_003109b4(v8);
          v15 = rt_0034c5ec();
          (*v173)(v15,v8);
          goto LBL_002285d4;
        }
      }
      else if (v12 < 0x41) {
        rt_00350440();
        rt_003524e0(&v235);
        rt_00350e34();
        rt_00352b80();
        (*v94)();
        v246 = rt_0034d1d0(v204);
        rt_00355e8c(v246.lo,v246.hi,v198);
        (*v46)();
        rt_00352584(&stack_ptr);
        rt_00310954();
        rt_00350648();
        rt_0034b358();
        v11 = (*v51)();
        rt_00100efc();
        (*v5)();
        if ((v11 & 1) == 0) {
          rt_003507d4();
          (*v5)();
        }
        else {
          rt_003109b4(v8);
          v15 = rt_0034c5ec();
          (*v159)(v15,v8);
          rt_003507d4();
          (*v5)();
        }
        goto LBL_00226fa0;
      }
      v231 = (code *)0x0;
      rt_00349abc(v8);
      rt_0034f84c(v204);
      (*v175)();
      rt_00349fe0(v214);
      rt_0034b358(v208);
      (*v81)();
      rt_00100efc();
      (*v5)();
    }
    else {
      rt_0034fe48();
      rt_0008e388();
      v12 = (*v106)();
      if (v12 < 0x40) {
        rt_0034d054(v8);
        rt_0008e388();
        (*v56)();
        v5 = v3;
LBL_002285d4:
        rt_00355640(v208,v2);
        (*v5)();
        goto LBL_00226fa0;
      }
      v231 = (code *)0x0;
      rt_00349abc(v8);
      rt_0034f84c(v204);
      (*v114)();
      rt_00349fe0(v214);
      rt_0034b358(v208);
      (*v160)();
      rt_00100efc();
      (*v3)();
      v5 = v3;
    }
    (*v5)(v208,v2);
    goto LBL_00226fa0;
  }
  rt_00358cbc();
  v10 = pcStack_68;
  v4 = v230;
  (*pcStack_68)();
  v20 = rt_00350c14();
  v12 = (*v108)(v20,v203);
  v20 = v225;
  rt_0035690c(v225);
  v246 = rt_00359834(v221);
  rt_003507ec(v246.lo,v246.hi,v15);
  (*v154)();
  v231 = (code *)(v12 - (long)v5);
  rt_00349abc(v20);
  rt_00352d94(v226);
  (*v140)();
  rt_00319778(v244);
  rt_0034e034(v210,v221);
  (*v138)();
  rt_003508a8();
  (*v10)();
  rt_003515cc();
  (*v10)();
  v10 = v220;
  rt_0034d354();
  v11 = (*v9)();
  if ((v11 & 1) == 0) {
LBL_00227e6c:
    v15 = 0;
  }
  else {
    rt_0034d354();
    v11 = (*v9)();
    if ((v11 & 1) != 0) {
      rt_0034eff8();
      v9 = v234;
      rt_0034f294();
      v12 = (*v88)();
      if (v12 < 0x40) {
        rt_003109b4(v10);
        v2 = (code *)rt_0034c6a4();
        v13 = v77;
        v8 = v10;
        v10 = v9;
LBL_00227e5c:
        v12 = (*v13)(v2,v8);
        v9 = v10;
        if (v12 < 0) goto LBL_00228878;
      }
      else {
        v231 = (code *)0x0;
        rt_00349abc(v10);
        rt_0034dc54();
        rt_0034fe38();
        (*v183)();
        rt_00348c84(v10);
        rt_0034c5ac(v9);
        v11 = (*v71)();
        rt_00350bc0(v249);
        (*v166)(v8,v201);
        v10 = v9;
        v4 = v5;
        if ((v11 & 1) != 0) goto LBL_00228878;
      }
      goto LBL_00227e6c;
    }
    rt_0035955c();
    rt_0034d354();
    (*v9)();
    rt_0034bb94();
    rt_003557b4();
    v12 = (*v45)();
    v5 = v239;
    v9 = v10;
    if (((unsigned long)v10 & 1) == 0) {
      if (v12 < 0x40) {
        rt_0034e104();
        v2 = v201;
        v13 = v42;
        goto LBL_00227e5c;
      }
      goto LBL_00227e6c;
    }
    rt_003536dc(v249);
    v5 = v203;
    if ((bool)v18 || v21 != v19) {
      rt_0034ad00();
      v15 = rt_00352b8c(&v234);
      rt_00351148(&v240,v15,v201);
      rt_00377bec();
      rt_00348fb4();
      rt_0034ae80();
      (*v129)();
      rt_0034cea8();
      rt_00358ad4();
      rt_0035287c();
      rt_0035169c();
      (*v109)();
      rt_00348c84(v8);
      v9 = v234;
      rt_0009e234();
      rt_003513c0();
      (*v127)();
      rt_00357760();
      rt_003510dc();
      (*v110)();
      if (((unsigned long)v10 & 1) == 0) {
        rt_0034d504(v8);
        rt_00351414();
        (*v48)();
        v12 = rt_00354058();
        v10 = v9;
        if (-1 < v12) goto LBL_00227e6c;
        goto LBL_00228878;
      }
      v15 = 1;
      rt_00354058();
    }
    else {
      v231 = (code *)0x0;
      rt_00349abc(v8);
      rt_0034fb3c();
      (*v116)();
      rt_00348c84(v8);
      rt_0034c344(v234);
      (*v132)();
      rt_00357760();
      rt_003509bc();
      (*v104)();
      rt_00354058();
      if (((unsigned long)v10 & 1) == 0) goto LBL_00227e6c;
LBL_00228878:
      v15 = 1;
      v9 = v10;
    }
  }
  v231 = v5;
  rt_00356840();
  rt_00350a70();
  v246 = rt_0035606c();
  rt_00377bec(v246.lo,v246.hi,v9);
  rt_00350950();
  rt_0016796c();
  rt_0034a07c();
  rt_00351af8(&v238);
  rt_0034f838();
  (*v32)();
  rt_0008f6c0(v201);
  rt_00350950();
  rt_00167a2c();
  rt_00352ca4(&v239);
  rt_00351360();
  rt_00351b78();
  (*v141)();
  rt_0035463c();
  v10 = *(code **)(v201 + 8);
  rt_0035084c();
  (*v10)();
  rt_00351384();
  (*v10)();
  rt_0031c1f0(v203);
  rt_00358f9c();
  rt_003518f4(v15,v4,v210);
  (*v96)();
LBL_00226fa0:
  v15 = rt_00353034();
  rt_0008e500(v15,v202);
  return;
}



/* FUN_00228914 @ 0x00228914   (est. swift_dispatch27)
 * Ghidra: void FUN_00228914( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00228914( void){
  uint64_t v2;
  long v1;
  
  rt_00355018();
  rt_0035a080();
  ((code)FUN_00226320)(v2);
  rt_00350bcc();
                    /* WARNING: Could not recover jumptable at 0x0022896c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(v1 + 8))();
  return;
}



/* FUN_00228a7c @ 0x00228a7c   (est. swift_init_dispatch6)
 * Ghidra: void FUN_00228a7c( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00228a7c( void){
  int v2;
  uint64_t v10;
  long v8;
  code *v6;
  code *v7;
  long v9;
  long v4;
  long v5;
  long v3;
  long v1;
  uint64_t v11;
  
  rt_0008e518();
  rt_00356334();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v8 + 0x40));
  rt_0034947c();
  rt_0031c670(0xff);
  rt_0034e130();
  rt_00310d68();
  rt_00348e60();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b460();
  rt_00350ad0(*(uint64_t *)(v9 + 0x10));
  (*v6)();
  rt_00350bf0();
  rt_00351584();
  v2 = rt_00365b6c();
  if (v2 == 0) {
    rt_0034e68c();
    rt_000839d8();
    v1 = v4;
  }
  else {
    rt_0034befc();
    rt_000839d8();
    rt_0034b3e8();
    (**(code **)(v5 + 0x10))(v10);
    rt_003561dc();
    v1 = v3;
  }
  rt_00100efc(*(uint64_t *)(v1 + 8));
  (*v7)();
  rt_00350774(v10,v2 == 0);
  rt_000839d8();
  rt_0008e500(v11);
  return;
}



/* FUN_00228bec @ 0x00228bec   (est. swift_check_flag7)
 * Ghidra: void FUN_00228bec( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00228bec( void){
  uint64_t v2;
  uint64_t v3;
  uint8_t v15;
  uint32_t v1;
  long v12;
  code *v9;
  code *v6;
  code *v7;
  code *v11;
  code *v8;
  long v10;
  long v5;
  uint64_t v13;
  uint64_t v4;
  uint64_t v14;
  rt16 v16;
  
  v16 = rt_0008e518();
  rt_003504e8();
  rt_00310d68();
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_003494b4();
  (*G_00658c00)(*(uint64_t *)(v12 + 0x40));
  rt_00349068();
  v2 = *(uint64_t *)(v16.lo + 0x18);
  v3 = *(uint64_t *)(v16.lo + 0x20);
  rt_00350944();
  rt_000dbcc8();
  rt_00357c88(v3);
  v4 = *(uint64_t *)(v16.hi + 0x18);
  v16 = rt_003510ac();
  (*v11)(v16.lo,v16.hi,v2,v3);
  rt_00349f3c();
  if ((bool)v15) {
    rt_00353f44(*(uint64_t *)(v10 + 8));
    (*v9)();
    v1 = 2;
  }
  else {
    rt_00354810();
    rt_003508c0();
    (*v8)();
    rt_0034a30c(v4);
    rt_0034beec(v13);
    v1 = (*v6)();
    rt_003505e8(*(uint64_t *)(v5 + 8));
    (*v7)();
    v1 = v1 & 1;
  }
  rt_0008e500(v1,v14);
  return;
}



/* FUN_00228d58 @ 0x00228d58   (est. swift_dispatch28)
 * Ghidra: void FUN_00228d58(long param_1, uint64_t param_2, code * UNRECOVERED_JUMPTABLE)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00228d58(long param_1, uint64_t param_2, code * UNRECOVERED_JUMPTABLE){
  rt_00083a18(*(uint64_t *)(param_1 + 0x18));
  rt_00355988();
                    /* WARNING: Could not recover jumptable at 0x00228d94. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



/* FUN_00228e24 @ 0x00228e24   (est. swift_noop)
 * Ghidra: void FUN_00228e24( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00228e24( void){
  rt_00261d60();
  return;
}



/* FUN_00228e28 @ 0x00228e28   (est. swift_noop2)
 * Ghidra: void FUN_00228e28( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00228e28( void){
  rt_00261d60();
  return;
}



/* FUN_002170e0 @ 0x002170e0   (est. swift_vtable_thunk_call)
 * Ghidra: void thunk_FUN_001a29a0(void)
 * Thunk that dispatches through the runtime vtable: it fetches a 16-byte
 * descriptor, then calls the vtable entry at offset 0x20 with the descriptor's
 * lo/hi halves and the trailing register argument. Control then falls through.
 * Confidence: medium
 * Notes: jumptable at 0x001a29d0 not recovered; indirect call via vtable slot. */
void FUN_002170e0(void){
  rt16 d;
  uint64_t r9, v16;

  d = rt_0035a758();
  (**(code **)(v16 + 0x20))(d.lo,r9,d.hi);
  return;
}

/* FUN_0021e870 @ 0x0021e870   (est. swift_hash_mix)
 * Ghidra: void thunk_FUN_00229ebc(void)
 * Core of a 64-bit mixing hash (a ChaCha/SipHash-style round): it combines two
 * 64-bit state words with the constant 0x7465646279746573 ("stbyte..."),
 * applies left/right rotate-xor linear feedback steps, XORs in a fixed high bit,
 * and feeds the mixed result to the runtime continuation rt_00351d4c.
 * Confidence: high
 * Notes: 0x7465646279746573 is a ChaCha/SipHash round constant. */
void FUN_0021e870(void){
  unsigned long v2, v1, v6, v4, v5, v3, e1, e8, e9, e10, e11, regx30;

  rt_0034e2d0();
  rt_0034bed4(regx30);
  v2 = e1 ^ 0x7465646279746573ull ^ e8;
  v1 = e9 + e11;
  v6 = v1 ^ (e11 >> 0x33 | e11 << 0xd);
  v4 = v6 + e10 + v2;
  v2 = e10 + v2 ^ (v2 >> 0x30 | v2 << 0x10);
  v5 = v4 ^ (v6 >> 0x2f | v6 << 0x11);
  v1 = (v1 >> 0x20 | v1 << 0x20) + v2;
  v6 = v1 ^ (v2 >> 0x2b | v2 << 0x15);
  v3 = v6 ^ 0x800000000000000ull;
  v1 = (v1 ^ e1) + v5;
  v5 = v1 ^ (v5 >> 0x33 | v5 << 0xd);
  v4 = v3 + (v4 >> 0x20 | v4 << 0x20);
  v2 = v4 + v5;
  v4 = v4 ^ (v3 >> 0x30 | v6 << 0x10);
  v1 = v4 + (v1 >> 0x20 | v1 << 0x20);
  v4 = v1 ^ (v4 >> 0x2b | v4 << 0x15);
  v1 = (v1 ^ 0x800000000000000ull) + (v2 ^ (v5 >> 0x2f | v5 << 0x11));
  v4 = ((v2 >> 0x20 | v2 << 0x20) ^ 0xff) + v4 ^ (v4 >> 0x30 | v4 << 0x10);
  rt_00351d4c((v1 >> 0x20 | v1 << 0x20) + v4 ^ (v4 >> 0x2b | v4 << 0x15));
  return;
}
