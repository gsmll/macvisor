/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0). Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary; estimates unless matched.
 * Slice 3: 0x21476c - 0x228e28. This is the Swift standard-library runtime support layer
 * embedded in the cL4 kernel (String/UTF8 indexing, Flatten distance, UnsafeBufferPointer,
 * ContiguousArrayBuffer, Float/Float16/Double min-max and bit-pattern parse, fatal-error traps).
 * All rt_* helpers are the shared cL4/Swift runtime OUTSIDE this slice; declared extern. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

typedef uint64_t (*code)();
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
  s_Range_requires_lowerBound_005cda00[], s_uespemosmodnarodarenegylsetybdet_004e7a30[];


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

/* ---- forward declarations for in-slice functions (unspecified args, so calls the
     decompiler left arg-less still type-check) ---- */
void FUN_0021476c();
void FUN_00214784();
void FUN_002147f8();
void FUN_002149d0();
uint64_t FUN_00214a64();
void FUN_00214af4();
void FUN_00214d18();
void FUN_00214d80();
void FUN_002152b8();
void FUN_00215428();
void FUN_00215600();
void FUN_002159d4();
void FUN_00215cd0();
void FUN_00216114();
void FUN_00216284();
void FUN_00216354();
void * FUN_00216418();
rt16 FUN_00216498();
void FUN_002165c0();
void FUN_0021662c();
void FUN_00216900();
void FUN_00216a00();
void FUN_00216b88();
void FUN_00216c60();
void FUN_00216dbc();
void FUN_00216f9c();
void FUN_002170e0();
void FUN_00217100();
uint32_t FUN_002171a8();
uint32_t FUN_002177bc();
uint32_t FUN_00217c60();
uint32_t FUN_00217ea0();
uint32_t FUN_00218068();
void FUN_002181e0();
void FUN_002185ec();
void FUN_0021867c();
void FUN_0021868c();
void FUN_00218714();
void FUN_002187e0();
void FUN_00218ae4();
void FUN_0021914c();
void FUN_002191fc();
rt16 FUN_0021927c();
rt16 FUN_00219370();
rt16 FUN_0021947c();
bool FUN_00219554();
void FUN_002195e0();
void FUN_002198fc();
void FUN_00219a00();
void FUN_00219fcc();
void FUN_0021a5bc();
long FUN_0021a660();
long FUN_0021acec();
long FUN_0021b1a4();
long FUN_0021b91c();
long FUN_0021bf60();
long FUN_0021c41c();
void FUN_0021cad0();
uint32_t FUN_0021d760();
void FUN_0021d7a0();
void FUN_0021da44();
void FUN_0021db04();
void FUN_0021de4c();
void FUN_0021dfcc();
void FUN_0021e254();
void * FUN_0021e3a0();
rt16 FUN_0021e420();
void FUN_0021e548();
void FUN_0021e5c4();
void FUN_0021e614();
void FUN_0021e6e4();
void FUN_0021e75c();
void FUN_0021e7dc();
uint32_t FUN_0021e844();
void FUN_0021e870();
bool FUN_0021e874();
void FUN_0021e8c0();
void FUN_0021e8f0();
uint32_t FUN_0021e940();
uint32_t FUN_0021e980();
uint32_t FUN_0021e9c0();
uint32_t FUN_0021ea00();
uint32_t FUN_0021ea44();
void FUN_0021ea88();
void FUN_0021ebbc();
void FUN_0021ec38();
void FUN_0021edec();
void FUN_0021ee60();
void FUN_0021eec4();
unsigned long FUN_0021ef30();
float FUN_0021ef5c();
double FUN_0021ef80();
unsigned long FUN_0021efbc();
float FUN_0021efe8();
double FUN_0021f00c();
void FUN_0021f048();
unsigned long FUN_0021f104();
float FUN_0021f138();
double FUN_0021f164();
unsigned long FUN_0021f1a8();
float FUN_0021f1dc();
double FUN_0021f208();
void FUN_0021f24c();
uint32_t FUN_0021f510();
void FUN_0021f648();
void FUN_0021f7b0();
void FUN_00223508();
void FUN_00223960();
uint32_t FUN_00224114();
uint32_t FUN_00224134();
rt16 FUN_00224154();
void FUN_00224180();
void FUN_00225cbc();
bool FUN_002260b0();
void FUN_00226320();
void FUN_00228914();
void FUN_00228a7c();
void FUN_00228bec();
void FUN_00228d58();
void FUN_00228e24();
void FUN_00228e28();

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
  uint64_t v4;
  uint64_t v6;
  long v5;
  
  rt_00351da8();
  rt_0034a354();
  rt_00349830();
  rt_00350968();
  rt_00377824();
  rt_00349530();
  (**(code **)(v3 + 0x20))();
  rt_0034e70c();
  v2 = rt_0031bc58();
  v1 = (uint64_t *)(v5 + *(int *)(v2 + 0x24));
  *v1 = v6;
  v1[1] = v4;
  return;
}



/* FUN_002147f8 @ 0x002147f8   (est. swift_runloop_dispatch)
 * Ghidra: void FUN_002147f8( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002147f8( void){
  uint8_t v13;
  uint64_t v6;
  uint64_t v5;
  uint64_t v4;
  code *v2;
  uint64_t v3;
  unsigned long v7;
  uint64_t v11;
  code *v9;
  code *v8;
  long v10;
  long v12;
  code *v1;
  rt16 v14;
  
  v14 = rt_0008e518();
  rt_003520f8();
  rt_00352720();
  rt_003513c0();
  rt_00377824();
  rt_0034e130();
  rt_00310d68();
  v6 = rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aee4();
  rt_00349734();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b0d4();
  rt_00352720();
  rt_003513c0();
  v5 = rt_00377824().lo;
  rt_003510dc();
  v4 = rt_00377bec().lo;
  v2 = (code *)rt_000a68f4();
  do {
    v3 = rt_00377dcc(0,v5);
    (*v2)(v3,v4);
    v3 = rt_0034aa54();
    if ((bool)v13) {
      rt_0035152c(v3,v6);
      (*v8)();
      v6 = 1;
LBL_002149a8:
      rt_00351548(v11,v6);
      rt_000839d8();
      rt_0008e500(v14.hi);
      return;
    }
    v1 = *(code **)(v10 + 0x20U);
    rt_00350048();
    (*v1)();
    v7 = (**(code **)(v12 + *(int *)(v14.lo + 0x24)))();
    if ((v7 & 1) != 0) {
      rt_003510ac();
      (*v1)(v10 + 0x20U & 0xffffffffffff | 0x48d8000000000000);
      v6 = 0;
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
  long v4;
  long v5;
  
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
  v1 = (uint64_t *)(v5 + *(int *)(v4 + 0x24));
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
  unsigned long v2;
  code *UNRECOVERED_JUMPTABLE;
  uint64_t v1;
  long v3;
  long v4;
  long v5;
  
  rt_0035316c();
  v2 = (**(code **)(v4 + *(int *)(v3 + 0x24)))();
  if ((v2 & 1) != 0) {
    UNRECOVERED_JUMPTABLE = (code *)rt_0031b62c(*(uint64_t *)(v5 + 0x18));
                    /* WARNING: Could not recover jumptable at 0x00214ad0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    v1 = (*UNRECOVERED_JUMPTABLE)();
    return v1;
  }
  return 0;
}



/* FUN_00214af4 @ 0x00214af4   (est. swift_runloop_iter)
 * Ghidra: void FUN_00214af4( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00214af4( void){
  code *v2;
  code *v1;
  unsigned long v5;
  uint64_t v4;
  code *v3;
  uint64_t v15;
  uint64_t v14;
  code *v11;
  long v9;
  code *v7;
  code *v10;
  code *v8;
  code *v12;
  code *v13;
  long v17;
  uint64_t v6;
  uint64_t v16;
  rt16 v19;
  code *v18;
  
  rt_0008e518();
  rt_003518c4();
  rt_00350bd8(v15);
  v6 = *(uint64_t *)(v17 + 0x10);
  v19 = rt_003497a0();
  v6 = rt_00377824(v19.lo,v19.hi,v6).lo;
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
  rt_003507bc(v14);
  (*v13)();
  v1 = (code *)rt_00310924();
  rt_0035705c();
  rt_00351ba0();
  rt_00377bec();
  rt_00027754();
  rt_0014ae44();
  rt_003561b8();
  while( true ) {
    rt_003504f4();
    (*v1)();
    rt_00351324();
    rt_00351b20();
    v5 = (*v18)();
    rt_003567ec();
    rt_00350b00();
    (*v11)();
    if ((v5 & 1) != 0) break;
    rt_0035a1b4();
    v2 = *(code **)(v17 + v9);
    v4 = rt_00351b84();
    rt_00352450(v4,v14);
    v3 = (code *)(*v7)();
    v19 = rt_00352b14();
    (*v10)(v19.lo,v19.hi,v6);
    rt_0034cfa4();
    (*v3)();
    v5 = (*v2)();
    rt_00354ab0();
    rt_00350a34();
    (*v8)();
    if ((v5 & 1) != 0) break;
    rt_00027818();
    rt_00350a88();
    rt_00350998();
    (*v12)();
  }
  rt_0008e500(v16);
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
  uint64_t v9;
  unsigned long v8;
  code *v3;
  code *v4;
  code *v6;
  code *v1;
  uint64_t v19;
  long v18;
  code *v14;
  code *v12;
  code *v10;
  code *v13;
  code *v11;
  code *v17;
  code *v15;
  code *v2;
  long v16;
  long v21;
  long v22;
  uint64_t v20;
  code *v5;
  uint64_t v7;
  uint64_t v23;
  rt16 av90;
  uint64_t v24;
  
  rt_0008e518();
  rt_0034e73c();
  rt_00350bd8();
  v7 = *(uint64_t *)(v21 + 0x10);
  av90 = rt_003497a0();
  v7 = rt_00377824(av90.lo,av90.hi,v7).lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aa9c();
  rt_0034c108();
  rt_00350210();
  rt_00377824();
  rt_00348e18();
  (*G_00658c00)(*(uint64_t *)(v18 + 0x40));
  rt_00348a34();
  (*G_00658c00)();
  rt_0034b8bc();
  rt_00351d0c();
  rt_00350624();
  (*v17)();
  rt_00310924(param_3);
  rt_00351184();
  rt_0035084c();
  (*v15)();
  rt_00350b78();
  rt_00351238();
  v9 = rt_00377bec().lo;
  rt_00351bec();
  rt_00350adc();
  rt_003516e4();
  rt_00350ac4();
  v8 = (*v14)();
  v5 = *(code **)(v16 + 8);
  rt_003509d4();
  (*v5)();
  if ((v8 & 1) != 0) {
    rt_00350410();
    rt_003488bc();
    rt_0034c220();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  (*v5)(v22);
  v3 = (code *)rt_00027818(param_3);
  v4 = (code *)rt_00310924(param_3);
  rt_00027754(v9);
  v6 = (code *)rt_0014ae44();
  do {
    rt_00352b2c();
    rt_00351420();
    (*v3)();
    rt_003545a0();
    rt_0035084c();
    (*v4)();
    rt_00351414();
    rt_00350ac4();
    v8 = (*v6)();
    rt_00350524();
    (*v5)();
    if ((v8 & 1) != 0) break;
    v2 = *(code **)(v22 + *(int *)(v21 + 0x24));
    v9 = rt_00351b84(param_3);
    rt_00354370(v9,v20);
    v1 = (code *)(*v12)();
    rt_0035457c();
    (*v10)(v24,v19,v7);
    rt_0034cfa4();
    (*v1)();
    v8 = (*v2)(v24);
    rt_00354f8c();
    (*v13)(v24,v7);
  } while ((v8 & 1) == 0);
  rt_00351298(*(uint64_t *)(v16 + 0x20),v22);
  (*v11)();
  rt_0008e500(v23);
  return;
}



/* FUN_002152b8 @ 0x002152b8   (est. swift_init_if_fail)
 * Ghidra: void FUN_002152b8(uint64_t param_1, uint64_t param_2, uint64_t param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002152b8(uint64_t param_1, uint64_t param_2, uint64_t param_3){
  long v3;
  uint64_t v2;
  long v10;
  code *v6;
  code *v9;
  code *v7;
  code *v5;
  long v8;
  long v4;
  code *v1;
  uint64_t v11;
  
  v3 = rt_0008e518().lo;
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
  if (v3 < 0) {
    rt_00350704();
    rt_00084180();
    (*v9)();
    rt_000277b8(param_3);
    v2 = rt_0034e72c();
    (*v7)(v2,param_3);
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
    (*v6)();
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
  long v3;
  bool v6;
  uint64_t v7;
  uint64_t v4;
  unsigned long v2;
  uint64_t v8;
  uint64_t v14;
  long v12;
  code *v10;
  code *v9;
  long v11;
  long v5;
  code *v1;
  rt16 v15;
  uint64_t v13;
  
  v15 = rt_0008e518();
  v8 = v15.hi;
  rt_00349748();
  rt_00350b84();
  rt_00377824();
  rt_00348d64();
  (*G_00658c00)(*(uint64_t *)(v12 + 0x40));
  rt_00348abc();
  (*G_00658c00)();
  rt_0034b87c();
  rt_00310cd4(v14);
  v7 = rt_00350a88();
  rt_00351f1c(v7,v8);
  (*v10)();
  rt_00350b48(v14);
  v7 = rt_00377bec().lo;
  rt_00310b08();
  v4 = rt_00350a88();
  rt_00350bfc(v4,v8);
  v2 = (*v9)();
  v1 = *(code **)(v11 + 0x10);
  v6 = (v2 & 1) == 0;
  if (v6) {
    v8 = v15.lo;
  }
  v3 = 1;
  if (!v6) {
    v3 = -1;
  }
  rt_00358df4(v2,v8);
  (*v1)();
  rt_00350ed0();
  (*v1)();
  rt_00352894(v7);
  v1 = (code *)rt_0014ae44();
  rt_000a6e14();
  rt_00350bfc();
  v2 = (*v1)();
  if ((v2 & 1) == 0) {
    v5 = 0;
    do {
      if (SCARRY8(v5,v3)) {
                    /* WARNING: Does not return */
        v1 = (code *)SW_BREAK(0x215600);
        (*v1)();
      }
      ((code)FUN_00214d80)();
      rt_000a6e14();
      rt_00350bfc();
      v2 = (*v1)();
      v5 = v5 + v3;
    } while ((v2 & 1) == 0);
  }
  v1 = *(code **)(v11 + 8);
  rt_00351274();
  (*v1)();
  rt_000e72b0();
  (*v1)();
  v8 = rt_0035a3d0();
  rt_0008e500(v8,v13);
  return;
}



/* FUN_00215600 @ 0x00215600   (est. swift_pos_loop_call)
 * Ghidra: void FUN_00215600( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00215600( void){
  code *v6;
  bool v10;
  uint64_t v11;
  uint64_t v9;
  uint64_t v8;
  code *v2;
  code *v3;
  unsigned long v12;
  code *v7;
  uint64_t v24;
  uint64_t v30;
  uint64_t v23;
  long v18;
  code *v15;
  code *v13;
  code *v16;
  code *v14;
  code *v19;
  code *v22;
  code *v20;
  code *v17;
  long v1;
  long v21;
  long v27;
  uint64_t v25;
  long v26;
  long v4;
  uint64_t v5;
  uint64_t v28;
  uint64_t v29;
  rt16 v32;
  rt16 v33;
  uint64_t v31;
  
  rt_0008e518();
  v32 = rt_0035199c();
  v4 = v32.hi;
  rt_00350bd8(v30);
  v5 = *(uint64_t *)(v26 + 0x10);
  v33 = rt_003497a0();
  v11 = rt_00377824(v33.lo,v33.hi,v5).lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034a2ac();
  rt_00349748();
  rt_003514dc();
  rt_00377824();
  rt_00348d64();
  (*G_00658c00)(*(uint64_t *)(v18 + 0x40));
  rt_003490d0();
  (*G_00658c00)();
  rt_0034b4c0();
  rt_00350500();
  v9 = rt_00310d68().lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aee4();
  (**(code **)(v21 + 0x10))(v23,v32.lo);
  if (v4 >> 0x3f < 0) {
    rt_00310924();
    rt_00351184();
    rt_003508a8();
    (*v22)();
    rt_003506e8();
    rt_003508a8();
    (*v20)();
    rt_003192d8();
    rt_0034e71c();
    rt_00350c08();
    (*v17)();
    v2 = *(code **)(v21 + 8);
    rt_000e15d8();
    (*v2)();
    rt_00351414();
    (*v2)();
    v8 = rt_0035152c();
    (*v15)(v8,v9);
    v10 = SBORROW8(0,v4);
    v4 = -v4;
    if (v10) {
                    /* WARNING: Does not return */
      v2 = (code *)SW_BREAK(0x2159c4);
      (*v2)();
    }
    if (v4 < 0) {
      rt_00347d60();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
  }
  else if (v4 == 0) goto LBL_00215998;
  v1 = 0;
  do {
    v1 = v1 + 1;
    v2 = (code *)rt_00310924(v25);
    rt_0034c3c4();
    rt_00350b48(v25);
    rt_00377bec();
    rt_00027754();
    v3 = (code *)rt_0014ae44();
    do {
      rt_0035084c();
      rt_003528ac();
      rt_001d30f8();
      rt_003507bc(v28);
      (*v2)();
      rt_00350ea4();
      rt_003516b4();
      v12 = (*v3)();
      rt_00351414(*(uint64_t *)(v21 + 8));
      (*v13)();
      if ((v12 & 1) != 0) break;
      v6 = *(code **)(v27 + *(int *)(v26 + 0x24));
      v9 = rt_00351b84(v25);
      v7 = (code *)(*v16)(v9,v23,v5,v25);
      rt_00354ab0();
      (*v14)(v31,v24,v11);
      rt_0034cfa4();
      (*v7)();
      rt_00355af8();
      v12 = (*v6)();
      v9 = rt_00352bc8();
      (*v19)(v9,v11);
    } while ((v12 & 1) == 0);
  } while (v1 != v4);
LBL_00215998:
  rt_0008e500(v29);
  return;
}



/* FUN_002159d4 @ 0x002159d4   (est. swift_dispatch2)
 * Ghidra: void FUN_002159d4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002159d4(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4){
  uint64_t v4;
  long v2;
  unsigned long v1;
  long v20;
  uint64_t v19;
  long v14;
  long v9;
  code *v7;
  code *v10;
  code *v8;
  code *v15;
  code *v18;
  code *v16;
  code *v13;
  code *v11;
  code *v12;
  long v17;
  long v6;
  long v5;
  long v3;
  uint64_t v21;
  rt16 v28;
  uint64_t v22;
  long v23;
  uint64_t v26;
  uint64_t v24;
  long v25;
  uint64_t v27;
  
  rt_0008e518();
  v26 = param_3;
  v24 = v19;
  v27 = rt_00349b3c();
  v3 = *(long *)(v14 + 0x40);
  v25 = v17;
  (*G_00658c00)();
  v23 = (long)&v22 - (v3 + 0xfU & 0xfffffffffffffff0);
  v22 = param_4;
  rt_00350950(param_4);
  rt_0008f6f4();
  rt_00349dfc();
  rt_00351554();
  v4 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b2f8();
  rt_0034bec4();
  rt_00377824();
  rt_00348d4c();
  v5 = *(long *)(v9 + 0x40);
  (*G_00658c00)(v5 + 0xfU & 0xfffffffffffffff0);
  v2 = rt_0034b05c();
  if (v20 == v2) {
    rt_000a6b64();
    rt_00350b30();
    rt_003507e0();
    (*v12)();
    if (v5 != v3) {
      rt_00347e28();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
    rt_003508c0(*(uint64_t *)(v25 + 0x10),v24);
    (*v10)();
    rt_00350618(*(uint64_t *)(v6 + 8));
    (*v8)();
  }
  else {
    rt_0034ad00();
    v28 = rt_003508cc();
    rt_00377bec(v28.lo,v28.hi,v4);
    rt_00349370();
    rt_0034c234();
    (*v18)();
    rt_0034d970();
    rt_00351a2c();
    rt_0034daf8();
    (*v16)();
    rt_00356b20();
    rt_0035044c();
    rt_003559d8();
    rt_0034e014();
    v1 = (*v7)();
    rt_00352870();
    rt_003514e8();
    (*v13)();
    if ((v1 & 1) == 0) {
      rt_003504a0(*(uint64_t *)(v25 + 0x10),v24);
      (*v15)();
    }
    else {
      rt_0031bc70(v22);
      rt_0034f3a4(v24);
      (*v11)();
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
  code *v4;
  bool v10;
  uint64_t v9;
  uint64_t v7;
  uint64_t v12;
  unsigned long v11;
  code *v3;
  code *v5;
  uint64_t v28;
  uint64_t v27;
  long v20;
  code *v16;
  code *v14;
  code *v17;
  code *v15;
  code *v21;
  code *v24;
  code *v22;
  code *v26;
  unsigned long v1;
  code *v23;
  code *v19;
  code *v18;
  long v25;
  long v13;
  uint64_t v6;
  long v2;
  long v30;
  uint64_t v29;
  uint64_t v34;
  long v33;
  uint64_t v31;
  uint64_t v32;
  rt16 v37;
  uint64_t v36;
  uint64_t v35;
  
  rt_0008e518();
  v9 = param_5;
  rt_00359de8();
  rt_00350bd8(v9);
  v6 = *(uint64_t *)(param_4 + 0x10);
  v37 = rt_003497a0();
  v9 = rt_00377824(v37.lo,v37.hi,v6).lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aa9c();
  rt_0034a944();
  rt_0035056c();
  rt_00377824();
  rt_0034e57c();
  rt_00310d68();
  v7 = rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034a760();
  rt_00349c70();
  (*G_00658c00)(*(uint64_t *)(v20 + 0x40));
  rt_00348bbc();
  (*G_00658c00)();
  rt_0034a464();
  (*G_00658c00)();
  rt_0034b4c0();
  rt_003534bc();
  rt_00351e90();
  (*v26)();
  v8 = 0 < v33;
  v1 = v33 >> 0x3f;
  if ((long)v1 < 0) {
    rt_00310924(param_5);
    rt_00350b24();
    rt_0034e50c();
    (*v23)();
    rt_0034f1e0();
    rt_003504ac();
    (*v19)();
    rt_003192d8(param_5);
    rt_0035322c();
    rt_003500f4();
    (*v18)();
    v3 = *(code **)(v13 + 8);
    rt_003507c8();
    (*v3)();
    rt_000a6e14();
    (*v3)();
    (**(code **)(v25 + 8))(v35,v7);
    v10 = SBORROW8(0,v33);
    v33 = -v33;
    if (v10) {
                    /* WARNING: Does not return */
      v3 = (code *)SW_BREAK(0x216114);
      (*v3)();
    }
    if (v33 < 0) {
      rt_00347d60();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
  }
  else if (v33 == 0) goto LBL_00216098;
  rt_0034c3c4();
  rt_00350b78();
  v7 = rt_00377bec().lo;
  v2 = 0;
  do {
    rt_00351ef8(v7);
    rt_0014ae44();
    v12 = rt_00350a7c();
    rt_00351c94(v12,param_3);
    v11 = (*v16)();
    if ((v11 & 1) != 0) {
      rt_00353bf4();
      rt_00350b3c();
      (*v22)();
      v9 = 1;
      goto LBL_002160d8;
    }
    v2 = v2 + 1;
    v3 = (code *)rt_00310924(param_5);
    do {
      rt_00354370(v31,v8 | v1);
      rt_001d30f8();
      rt_0035084c(v34);
      (*v3)();
      rt_00351414();
      rt_00351c94();
      v11 = (*v16)();
      rt_00353bf4();
      rt_003507c8();
      (*v14)();
      if ((v11 & 1) != 0) break;
      v4 = *(code **)(v30 + *(int *)(param_4 + 0x24));
      rt_00352ecc(param_5);
      v37 = rt_00355634();
      v5 = (code *)(*v17)(v37.lo,v37.hi,v6,param_5);
      rt_0035457c();
      (*v15)(v36,v28,v9);
      rt_0034c3b4();
      (*v5)();
      v11 = (*v4)(v36);
      rt_00354f8c();
      (*v21)(v36,v9);
    } while ((v11 & 1) == 0);
  } while (v2 != v33);
LBL_00216098:
  v37 = rt_00351324(*(uint64_t *)(v13 + 0x20));
  (*v24)(v37.lo,v37.hi,v29);
  v9 = 0;
LBL_002160d8:
  rt_000839d8(v27,v9,1,v29);
  rt_0008e500(v32);
  return;
}



/* FUN_00216114 @ 0x00216114   (est. swift_init_dispatch)
 * Ghidra: void FUN_00216114( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00216114( void){
  uint32_t v2;
  int v3;
  uint64_t v10;
  uint64_t v6;
  long v12;
  uint64_t v13;
  code *v9;
  code *v5;
  code *v8;
  long v7;
  long v4;
  code *v1;
  uint64_t v11;
  
  rt_0008e518();
  v2 = rt_00357a34();
  v2 = rt_0034a944(v2,v6,*(uint64_t *)(v12 + 0x10));
  rt_00377824(v2,v13);
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
  v2 = rt_00353c18();
  rt_00352e60(v2,v10);
  ((code)FUN_00215cd0)();
  rt_00356224();
  rt_003504ac();
  (*v8)();
  rt_003524b0();
  v3 = rt_0035681c();
  if (v3 == 1) {
    rt_00350c2c(*(uint64_t *)(v7 + 8));
    (*v9)();
    rt_00355d28(*(uint64_t *)(v4 + 0x10));
    (*v5)();
  }
  else {
    v1 = *(code **)(v4 + 0x20);
    rt_003508a8();
    (*v1)();
    rt_0035100c();
    (*v1)();
  }
  v2 = rt_00357fd4();
  rt_0008e500(v2,v11);
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
  long v5;
  uint64_t v3;
  
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
  v1 = *(uint64_t *)(v4 + *(int *)(v5 + 0x24) + 8);
  rt_00350c2c();
  rt_00352ea8();
  rt_00377bec();
  rt_00027754();
  rt_003547f8();
  rt_000dbe70();
  ((code)FUN_0021476c)();
  rt_0036b270(v1);
  rt_0008e500(v3);
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
  long v4;
  long v3;
  rt16 v5;
  
  rt_00351a68();
  v5 = rt16_mklo((**(code **)(v4 + *(int *)(v2 + 0x24)))());
  if ((v5.lo & 1) != 0) {
    UNRECOVERED_JUMPTABLE = (code *)rt_0031b110(param_3);
    v5 = rt_00356248(UNRECOVERED_JUMPTABLE,*(uint64_t *)(v3 + 0x10));
                    /* WARNING: Could not recover jumptable at 0x002163c4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)(v5.lo,v5.hi,param_3);
    return;
  }
  v1 = rt_00349748(v5.lo,v5.hi,*(uint64_t *)(v3 + 0x10));
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
  long v2;
  uint64_t v1;
  
  v2 = rt_0036a908(0x28,0xb433);
  *param_1 = v2;
  v1 = FUN_00216498(v2,param_2,param_3,*(uint64_t *)((param_4 & 0xfffffffffffffffe) - 8)).lo;
  *(uint64_t *)(v2 + 0x20) = v1;
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
  code *v3;
  unsigned long v5;
  code *v1;
  code *v2;
  code *v4;
  long v15;
  code *v12;
  code *v10;
  code *v8;
  long v11;
  code *v9;
  code *v14;
  long v13;
  long v7;
  uint64_t v17;
  long v19;
  long v16;
  uint64_t v18;
  uint64_t v6;
  uint64_t v20;
  rt16 v21;
  uint8_t v22 [32];
  
  rt_0008e518();
  rt_00351a38();
  rt_0035125c(param_3);
  rt_00350bd8();
  v6 = *(uint64_t *)(v16 + 0x10);
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
  v5 = (*v10)();
  rt_003508f0(*(uint64_t *)(v7 + 8));
  (*v8)();
  if ((v5 & 1) == 0) {
    v1 = (code *)rt_003196e8(param_3);
    rt_0035a1b4();
    v3 = *(code **)(v19 + v11);
    v2 = (code *)rt_000277e8(v18);
    do {
      (*v1)();
      rt_003513a8(v22);
      v4 = (code *)(*v2)();
      (**(code **)(v13 + 0x10))();
      rt_0034cfa4();
      (*v4)();
      v5 = (*v3)();
      rt_00100c38(*(uint64_t *)(v13 + 8));
      (*v9)();
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
  long v3;
  uint64_t v14;
  long v10;
  long v9;
  code *v11;
  unsigned long v7;
  long v12;
  long v13;
  unsigned long v5;
  code *v1;
  unsigned long v2;
  uint64_t v8;
  long v4;
  uint64_t v6;
  uint64_t v15;
  rt16 v17;
  rt16 v16;
  
  v17 = rt_0008e518();
  v3 = param_3;
  rt_00349720();
  v4 = *(long *)(v10 + 0x40);
  (*G_00658c00)();
  v8 = *(uint64_t *)(v3 + 0x10);
  rt_003499c8();
  (*G_00658c00)(*(uint64_t *)(v9 + 0x40));
  rt_0034947c();
  rt_00351494(*(uint64_t *)(v12 + 0x10));
  (*v11)();
  v1 = *(code **)(v13 + 0x20);
  v16 = rt_00350738();
  (*v1)(v16.lo,v16.hi,param_3);
  v7 = (unsigned long)*(uint8_t *)(v13 + 0x50);
  v2 = v7 + 0x20 & (v7 ^ 0xffffffffffffffff);
  v5 = v4 + v2 + 7 & 0xfffffffffffffff8;
  v3 = rt_0036a940(0x66aa88,v5 + 0x10,v7 | 7).lo;
  v6 = *(uint64_t *)(param_3 + 0x18);
  *(uint64_t *)(v3 + 0x10) = v8;
  *(uint64_t *)(v3 + 0x18) = v6;
  rt_00350c08(v3 + v2);
  (*v1)();
  *(rt16*)(v3 + v5) = v17;
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
  FUN_00216c60(v4.lo,v4.hi,v3);
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
  uint64_t v8;
  code *v7;
  code *v4;
  code *v6;
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
  rt_000a68c4(v8);
  v1 = rt_0034e72c();
  (*v6)(v1,v8);
  rt_0034b3c8();
  (**(code **)(v2 + 8))();
  rt_00350b3c(*(uint64_t *)(v5 + 0x20));
  (*v7)();
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
  uint64_t v6;
  uint64_t v5;
  code *v3;
  long v4;
  uint64_t v8;
  uint64_t v7;
  uint64_t v9;
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
  rt_00353960(v1,v6);
  rt_001f1878();
  rt_00359018(0x66aab0);
  v10 = rt_0036a940();
  v2 = v10.lo;
  *(uint64_t *)(v2 + 0x10) = v7;
  *(uint64_t *)(v2 + 0x18) = v8;
  *(uint64_t *)(v2 + 0x20) = param_5;
  rt_00351720(rt_0031be30,v10.hi,param_3,0x66cc38);
  ((code)FUN_00216900)();
  rt_0036b118(v2);
  rt_00359018(0x66aad8);
  v2 = rt_0036a940().lo;
  *(uint64_t *)(v2 + 0x10) = v7;
  *(uint64_t *)(v2 + 0x18) = v8;
  *(uint64_t *)(v2 + 0x20) = param_5;
  rt_0034dbb8(v5,&G_0031be54);
  rt_001f1878();
  rt_0036b118(v2);
  rt_00350c38(*(uint64_t *)(v4 + 8));
  (*v3)();
  rt_0008e500(v9);
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
  uint8_t v8 [8];
  uint64_t uStack_48;
  uint32_t v7 [4];
  
  v6 = rt_00310d68(0,param_4);
  v2 = v6.lo;
  (*G_00658c00)(*(long *)(*(long *)(v2 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0,v2,
                  v6.hi,v2);
  v2 = -v5;
  v1 = stack_ptr + v2;
  (**(code **)(v4 + 0x10))(v1,param_2);
  v3 = rt_000839f8(v1,1,param_4);
  if (v3 != 1) {
    (**(code **)(*(long *)(param_4 + -8) + 0x20))(param_1,v1,param_4);
    return;
  }
  *(uint32_t *)((long)v7 + v2) = 1;
  *(uint64_t *)((long)&uStack_48 + v2) = 0x31;
  v8[v2] = 2;
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
  uint8_t v12;
  uint16_t v17;
  uint32_t v14;
  long v18;
  unsigned long v11;
  char *v5;
  uint64_t v13;
  int v16;
  unsigned long v15;
  unsigned long v10;
  uint8_t *v2;
  uint8_t *v1;
  unsigned long *v19;
  unsigned long v4;
  unsigned long v3;
  unsigned long v8;
  unsigned long v6;
  uint32_t v9;
  rt16 v22;
  rt16 v23;
  uint64_t v7;
  unsigned long v20;
  unsigned long uStack_78;
  unsigned long v21;
  unsigned long uStack_68;
  
  v4 = v19[7];
  do {
    if (v4 != 0) {
      v3 = v19[6];
      v8 = v3 & 0xffffffffffff;
      if ((v4 & 0x2000000000000000) != 0) {
        v8 = v4 >> 0x38 & 0xf;
      }
      v6 = v19[8];
      if (v6 >> 0xe != v8 * 4) {
        v14 = (uint32_t)(v3 >> 0x3b) & 1;
        if ((v4 & 0x1000000000000000) == 0) {
          v14 = 1;
        }
        v11 = v6;
        if ((v6 & 0xc) == 4L << (unsigned long)v14) {
          v11 = rt_0001da84(v6,v3,v4);
        }
        v10 = v11 >> 0x10;
        if (v8 <= v10) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                       s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
        }
        if ((v4 >> 0x3c & 1) == 0) {
          if ((v4 >> 0x3d & 1) == 0) {
            if ((v3 >> 0x3c & 1) == 0) goto LBL_00217720;
            v18 = (v4 & 0xfffffffffffffff) + 0x20;
            goto LBL_0021758c;
          }
          v21 = v3;
          uStack_68 = v4 & 0xffffffffffffff;
          v12 = *(uint8_t *)((long)&v21 + v10);
        }
        else {
          rt_002b141c(v11,v3,v4);
LBL_00217720:
          v18 = rt_002a9ba8(v3,v4).lo;
LBL_0021758c:
          v12 = *(uint8_t *)(v18 + v10);
        }
        v9 = (uint32_t)v12;
        if ((v6 & 0xc) == 4L << (unsigned long)v14) {
          v6 = rt_0001da84(v6,v3,v4);
        }
        v16 = 0;
        v19[8] = (unsigned long)(&G_00010004 + (v6 & 0xffffffffffff0000));
        goto LBL_002175d4;
      }
    }
    v4 = v19[2];
    if ((long)v19[3] <= (long)v4) {
      v9 = 0;
      v16 = 1;
LBL_002175d4:
      return v9 | v16 << 8;
    }
    v8 = *v19;
    v3 = v19[1];
    v6 = v3 >> 0x38 & 0xf;
    if ((v3 >> 0x3c & 1) == 0) {
      if ((v3 >> 0x3d & 1) == 0) {
        if ((v8 >> 0x3c & 1) == 0) {
          v22 = rt_002a9ba8(v8,v3);
        }
        else {
          v22.hi = v8 & 0xffffffffffff;
          v22.lo = (v3 & 0xfffffffffffffff) + 0x20;
        }
        v11 = v4 + 1;
        if (v11 != v22.hi) {
          if (v22.lo == 0) {
                    /* WARNING: Subroutine does not return */
            rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_unsafelyUnwrapped_of_nil_optiona_005ce1c0,
                         0x21,2,s_Swift_Optional_swift_005ce1f0,0x14,2,0x179,1);
          }
          v17 = *(uint16_t *)(v22.lo + v4);
LBL_00217268:
          v11 = v4 + 1;
          if (v17 == 0xa0d || (v17 & 0x8080) != 0) goto LBL_0021749c;
        }
      }
      else {
        v21 = v8;
        uStack_68 = v3 & 0xffffffffffffff;
        v11 = v4 + 1;
        if (v11 != v6) {
          v17 = *(uint16_t *)((long)&v21 + v4);
          goto LBL_00217268;
        }
      }
    }
    else {
LBL_0021749c:
      v18 = rt_002c6d00(v4,v8,v3);
      if ((v3 >> 0x3c & 1) != 0) {
        rt_002bbcd8();
LBL_00217734:
        v7 = 0x584;
        v5 = s_UnsafeBufferPointer_has_a_nil_st_005cf020;
        v13 = 0x35;
LBL_002176c0:
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v5,v13,2,
                     s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,v7,1);
      }
      v11 = v18 + v4;
      if ((long)v11 < (long)v4) {
        v7 = 0x2f9;
        v5 = s_Range_requires_lowerBound_005cda00;
        v13 = 0x27;
        goto LBL_0021752c;
      }
    }
    if ((v3 >> 0x3d & 1) != 0) {
      uStack_68 = v3 & 0xffffffffffffff;
      v21 = v8;
      if ((long)v4 < 0) {
LBL_002174e0:
        v7 = 0x7a8;
      }
      else {
        if ((long)v11 <= (long)v6) {
          v8 = v11 - v4;
          if (-1 < (long)v8) {
            v2 = (uint8_t *)((long)&v21 + v4);
            v14 = rt_002a200c(v2,v8);
            if (v11 - v4 == 0) {
LBL_00217388:
              v15 = 0;
              v3 = 0xe000000000000000;
              goto LBL_0021745c;
            }
            if (0xf < v8) goto LBL_00217420;
            v6 = v8 - 8;
            v3 = v8;
            if (7 < v8) {
              v3 = 8;
            }
            v10 = v8;
            if (v3 - 1 <= v8) {
              v10 = v3 - 1;
            }
            if (v3 == v10) {
LBL_002174f0:
              v7 = 0x136;
              v5 = s_Index_out_of_range_005cd940;
              v13 = 0x12;
LBL_0021752c:
                    /* WARNING: Subroutine does not return */
              rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v5,v13,2,s_Swift_Range_swift_005cda30,
                           0x11,2,v7,1);
            }
            v15 = 0;
            v10 = 0;
            do {
              v15 = (unsigned long)*v2 << (v10 & 0x3f) | v15;
              v10 = v10 + 8;
              v2 = v2 + 1;
            } while (v3 * 8 - v10 != 0);
            if (v8 < 9) {
LBL_00217440:
              v3 = 0;
            }
            else {
              if (v6 <= (v11 - v4) - 9) goto LBL_002174f0;
              v3 = 0;
              v10 = 0;
              v2 = (uint8_t *)((long)&uStack_68 + v4);
              do {
                v3 = (unsigned long)*v2 << (v10 & 0x38) | v3;
                v10 = v10 + 8;
                v6 = v6 - 1;
                v2 = v2 + 1;
              } while (v6 != 0);
            }
LBL_00217444:
            v4 = 0xe000000000000000;
            if (((v3 | v15) & 0x8080808080808080) != 0) {
              v4 = 0xa000000000000000;
            }
            v3 = v4 | v8 << 0x38 | v3;
            goto LBL_0021745c;
          }
LBL_00217684:
          v7 = 0x582;
          v5 = s_UnsafeBufferPointer_with_negativ_005cdf60;
          v13 = 0x27;
          goto LBL_002176c0;
        }
LBL_00217644:
        v7 = 0x7a9;
      }
      v5 = &G_005be7c0;
      v13 = 0;
      goto LBL_002176c0;
    }
    if ((v8 >> 0x3c & 1) == 0) {
      v23 = rt_002a9ba8(v8,v3);
    }
    else {
      v23.hi = v8 & 0xffffffffffff;
      v23.lo = (v3 & 0xfffffffffffffff) + 0x20;
    }
    if ((long)v4 < 0) goto LBL_002174e0;
    if (v23.hi < (long)v11) goto LBL_00217644;
    v2 = (uint8_t *)0x0;
    if (v23.lo != 0) {
      v2 = (uint8_t *)(v23.lo + v4);
    }
    v8 = v11 - v4;
    if ((long)v8 < 0) goto LBL_00217684;
    if ((v8 != 0) && (v2 == (uint8_t *)0x0)) goto LBL_00217734;
    v14 = rt_002a200c(v2,v8);
    if (v11 - v4 == 0) goto LBL_00217388;
    if (v8 < 0x10) {
      v6 = v8 - 8;
      v3 = v8;
      if (7 < v8) {
        v3 = 8;
      }
      v10 = v8;
      if (v3 - 1 <= v8) {
        v10 = v3 - 1;
      }
      if (v3 != v10) {
        v15 = 0;
        v10 = 0;
        v1 = v2;
        do {
          v15 = (unsigned long)*v1 << (v10 & 0x3f) | v15;
          v10 = v10 + 8;
          v1 = v1 + 1;
        } while (v3 * 8 - v10 != 0);
        if (v8 < 9) goto LBL_00217440;
        if ((v11 - v4) - 9 < v6) {
          v3 = 0;
          v4 = 0;
          v2 = v2 + 8;
          do {
            v3 = (unsigned long)*v2 << (v4 & 0x38) | v3;
            v4 = v4 + 8;
            v6 = v6 - 1;
            v2 = v2 + 1;
          } while (v6 != 0);
          goto LBL_00217444;
        }
      }
      goto LBL_002174f0;
    }
LBL_00217420:
    v3 = rt_002a4b90(v2,v8,v8,v14 & 1);
    v15 = *(unsigned long *)(v3 + 0x18);
LBL_0021745c:
    v19[2] = v11;
    v21 = v15;
    uStack_68 = v3;
    (*(code *)v19[4])(&v20,&v21);
    rt_003a25d4(v3);
    v4 = uStack_78;
    v8 = v20;
    rt_003a25d4(v19[7]);
    v19[6] = v8;
    v19[7] = v4;
    v19[8] = 0xf;
  } while( true );
}



/* FUN_002177bc @ 0x002177bc   (est. swift_string_advance)
 * Ghidra: uint32_t FUN_002177bc( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_002177bc( void){
  uint8_t v12;
  uint16_t v18;
  uint32_t v15;
  unsigned long v13;
  unsigned long v11;
  uint64_t v14;
  unsigned long v17;
  long v16;
  char *v1;
  int v8;
  uint64_t *v19;
  unsigned long v6;
  unsigned long v3;
  unsigned long v2;
  uint64_t v5;
  unsigned long v4;
  uint32_t v7;
  unsigned long v9;
  rt16 v22;
  rt16 av180;
  rt16 av181;
  uint64_t v20;
  unsigned long uStack_78;
  rt16u v21;
  uint8_t *v10;
  
  v6 = v19[8];
  do {
    if (v6 != 0) {
      v3 = v19[7];
      v4 = v3 & 0xffffffffffff;
      if ((v6 & 0x2000000000000000) != 0) {
        v4 = v6 >> 0x38 & 0xf;
      }
      v2 = v19[9];
      if (v2 >> 0xe != v4 * 4) {
        v15 = (uint32_t)(v3 >> 0x3b) & 1;
        if ((v6 & 0x1000000000000000) == 0) {
          v15 = 1;
        }
        v17 = v2;
        if ((v2 & 0xc) == 4L << (unsigned long)v15) {
          v17 = rt_0001da84(v2,v3,v6);
        }
        v13 = v17 >> 0x10;
        if (v4 <= v13) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                       s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
        }
        if ((v6 >> 0x3c & 1) == 0) {
          if ((v6 >> 0x3d & 1) == 0) {
            if ((v3 >> 0x3c & 1) == 0) goto LBL_00217bc8;
            v16 = (v6 & 0xfffffffffffffff) + 0x20;
            goto LBL_00217a74;
          }
          v21.lo = v3;
          v21.hi = v6 & 0xffffffffffffff;
          v12 = v21.b[v13];
        }
        else {
          rt_002b141c(v17,v3,v6);
LBL_00217bc8:
          v16 = rt_002a9ba8(v3,v6).lo;
LBL_00217a74:
          v12 = *(uint8_t *)(v16 + v13);
        }
        v7 = (uint32_t)v12;
        if ((v2 & 0xc) == 4L << (unsigned long)v15) {
          v2 = rt_0001da84(v2,v3,v6);
        }
        v8 = 0;
        v19[9] = (uint64_t)&G_00010004 + (v2 & 0xffffffffffff0000);
        goto LBL_00217abc;
      }
    }
    v6 = v19[1];
    v4 = v19[4];
    if ((v4 ^ v6) < 0x4000) {
      v7 = 0;
      v8 = 1;
LBL_00217abc:
      return v7 | v8 << 8;
    }
    v5 = *v19;
    v2 = v19[2];
    v17 = v19[3];
    v13 = rt_002ab4d4(v4,v5,v6,v2,v17);
    v11 = v13 >> 8 & 0x3f;
    v13 = v13 >> 0x10;
    v3 = v6 >> 0x10;
    v9 = v17 >> 0x38 & 0xf;
    if (v11 == 0) {
      if (v13 == v3) {
        v11 = 0;
      }
      else if ((v17 >> 0x3c & 1) == 0) {
        if ((v17 >> 0x3d & 1) == 0) {
          if ((v2 >> 0x3c & 1) == 0) {
            av181 = rt_002a9ba8(v2,v17);
          }
          else {
            av181.hi = v2 & 0xffffffffffff;
            av181.lo = (v17 & 0xfffffffffffffff) + 0x20;
          }
          if (v13 + 1 != av181.hi) {
            if (av181.lo == 0) {
                    /* WARNING: Subroutine does not return */
              rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_unsafelyUnwrapped_of_nil_optiona_005ce1c0,
                           0x21,2,s_Swift_Optional_swift_005ce1f0,0x14,2,0x179,1);
            }
            v18 = *(uint16_t *)(av181.lo + v13);
LBL_002178b8:
            if (v18 == 0xa0d || (v18 & 0x8080) != 0) goto LBL_002179f0;
          }
        }
        else {
          v21.hi = v17 & 0xffffffffffffff;
          v21.lo = v2;
          v22.hi = v21.hi;
          v22.lo = v2;
          if (v13 + 1 != v9) {
            v18 = *(uint16_t *)(v21.b + v13);
            v21 = rt16_mklo(v22);
            goto LBL_002178b8;
          }
        }
        v11 = 1;
      }
      else {
LBL_002179f0:
        v11 = rt_002c6d00(v13,v2,v17);
      }
    }
    if ((long)(v11 + v13) <= (long)v3) {
      v3 = v11 + v13;
    }
    if ((v17 >> 0x3c & 1) != 0) {
      rt_002bbcd8();
LBL_00217ae4:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Range_requires_lowerBound_005cda00,0x27,2,
                   s_Swift_Range_swift_005cda30,0x11,2,0x2f9,1);
    }
    v16 = v3 - v13;
    if ((long)v3 < (long)v13) goto LBL_00217ae4;
    if ((v17 >> 0x3d & 1) == 0) {
      if ((v2 >> 0x3c & 1) == 0) {
        av180 = rt_002a9ba8(v2,v17);
      }
      else {
        av180.hi = v2 & 0xffffffffffff;
        av180.lo = (v17 & 0xfffffffffffffff) + 0x20;
      }
      if (av180.hi < (long)v3) {
LBL_00217b2c:
        v14 = 0x7a9;
        v1 = &G_005be7c0;
        v5 = 0;
        goto LBL_00217b68;
      }
      v10 = (uint8_t *)0x0;
      if (av180.lo != 0) {
        v10 = (uint8_t *)(av180.lo + v13);
      }
      v16 = v3 - v13;
      if ((v16 != 0) && (v10 == (uint8_t *)0x0)) {
        v14 = 0x584;
        v1 = s_UnsafeBufferPointer_has_a_nil_st_005cf020;
        v5 = 0x35;
LBL_00217b68:
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v1,v5,2,
                     s_Swift_UnsafeBufferPointer_swift_005cdc10,0x1f,2,v14,1);
      }
      v15 = rt_002a200c(v10,v16);
    }
    else {
      v21.hi = v17 & 0xffffffffffffff;
      v21.lo = v2;
      if (v9 < v3) goto LBL_00217b2c;
      v15 = rt_002a200c(v21.b + v13,v16);
      v10 = v21.b + v13;
    }
    v22 = rt_002a2698(v10,v16,v15 & 1);
    v14 = rt_002ab6a0(v4,v5,v6,v2,v17);
    v5 = rt_002b3b84(v14,v5,v6,v2,v17);
    v19[4] = v5;
    v21 = rt16_mklo(v22);
    (*(code *)v19[5])(&v20,v21);
    rt_003a25d4(v22.hi);
    v6 = uStack_78;
    v5 = v20;
    rt_003a25d4(v19[8]);
    v19[7] = v5;
    v19[8] = v6;
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
  code *v4;
  uint8_t v8;
  unsigned long v7;
  unsigned long *v5;
  unsigned long v12;
  uint32_t v9;
  int v11;
  unsigned long v10;
  unsigned long v13;
  unsigned long v3;
  long *v14;
  unsigned long v1;
  unsigned long v2;
  rt16 v17;
  long v15;
  unsigned long uStack_58;
  unsigned long v16;
  unsigned long uStack_48;
  
  v1 = v14[5];
  do {
    if (v1 != 0) {
      v12 = v14[4];
      v3 = v12 & 0xffffffffffff;
      if ((v1 & 0x2000000000000000) != 0) {
        v3 = v1 >> 0x38 & 0xf;
      }
      v7 = v14[6];
      v17.hi = v12;
      v17.lo = v7;
      if (v7 >> 0xe != v3 * 4) {
        v9 = (uint32_t)(v12 >> 0x3b) & 1;
        if ((v1 & 0x1000000000000000) == 0) {
          v9 = 1;
        }
        v2 = v7 & 0xc;
        if (v2 == 4L << v9) {
          v7 = rt_0001da84(v7,v12,v1);
        }
        v10 = v7 >> 0x10;
        if (v3 <= v10) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                       s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
        }
        if ((v1 >> 0x3c & 1) == 0) {
          if ((v1 >> 0x3d & 1) == 0) {
            if ((v12 >> 0x3c & 1) == 0) goto LBL_00217e7c;
            v5 = (unsigned long *)((v1 & 0xfffffffffffffff) + 0x20);
          }
          else {
            v16 = v12;
            uStack_48 = v1 & 0xffffffffffffff;
            v5 = &v16;
          }
        }
        else {
          v17 = rt_002b141c(v7,v12,v1);
          v10 = v13;
LBL_00217e7c:
          v5 = (unsigned long *)rt_002a9ba8(v17.hi,v1);
        }
        v3 = v17.lo;
        v8 = *(uint8_t *)((long)v5 + v10);
        if (v2 == 4L << v9) {
          v3 = rt_0001da84(v3,v17.hi,v1);
        }
        v9 = (uint32_t)v8;
        v11 = 0;
        v14[6] = (long)(&G_00010004 + (v3 & 0xffffffffffff0000));
        goto LBL_00217e0c;
      }
    }
    v1 = v14[1];
    v3 = *(unsigned long *)(*v14 + 0x10);
    if (v1 == v3) {
      v9 = 0;
      v11 = 1;
LBL_00217e0c:
      return v9 | v11 << 8;
    }
    if (v3 <= v1) {
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Index_out_of_range_005cd940,0x12,2,
                   s_Swift_ContiguousArrayBuffer_swif_005cd960,0x21,2,0x2b4,1);
    }
    v6 = *v14 + v1 * 0x10;
    v16 = *(unsigned long *)(v6 + 0x20);
    v3 = *(unsigned long *)(v6 + 0x28);
    v14[1] = v1 + 1;
    v4 = (code *)v14[2];
    uStack_48 = v3;
    rt_0036b270(v3);
    (*v4)(&v15,&v16);
    rt_003a25d4(v3);
    v1 = uStack_58;
    v6 = v15;
    rt_003a25d4(v14[5]);
    v14[4] = v6;
    v14[5] = v1;
    v14[6] = 0xf;
  } while( true );
}



/* FUN_00217ea0 @ 0x00217ea0   (est. swift_string_pop_first)
 * Ghidra: uint32_t FUN_00217ea0( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_00217ea0( void){
  unsigned long v10;
  uint8_t v4;
  unsigned long v6;
  long v11;
  int v3;
  uint32_t v9;
  uint64_t *v12;
  unsigned long v5;
  unsigned long v7;
  unsigned long v8;
  uint32_t v1;
  unsigned long v2;
  uint64_t v14;
  long lStack_68;
  unsigned long v13;
  unsigned long uStack_58;
  
  v5 = v12[5];
  do {
    if (v5 != 0) {
      v7 = v12[4];
      v10 = v7 & 0xffffffffffff;
      if ((v5 & 0x2000000000000000) != 0) {
        v10 = v5 >> 0x38 & 0xf;
      }
      v8 = v12[6];
      if (v8 >> 0xe != v10 * 4) {
        v9 = (uint32_t)(v7 >> 0x3b) & 1;
        if ((v5 & 0x1000000000000000) == 0) {
          v9 = 1;
        }
        v6 = v8;
        if ((v8 & 0xc) == 4L << (unsigned long)v9) {
          v6 = rt_0001da84(v8,v7,v5);
        }
        v2 = v6 >> 0x10;
        if (v10 <= v2) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                       s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
        }
        if ((v5 >> 0x3c & 1) == 0) {
          if ((v5 >> 0x3d & 1) == 0) {
            if ((v7 >> 0x3c & 1) == 0) goto LBL_00218058;
            v11 = (v5 & 0xfffffffffffffff) + 0x20;
            goto LBL_00217f9c;
          }
          v13 = v7;
          uStack_58 = v5 & 0xffffffffffffff;
          v4 = *(uint8_t *)((long)&v13 + v2);
        }
        else {
          rt_002b141c(v6,v7,v5);
LBL_00218058:
          v11 = rt_002a9ba8(v7,v5).lo;
LBL_00217f9c:
          v4 = *(uint8_t *)(v11 + v2);
        }
        v1 = (uint32_t)v4;
        if ((v8 & 0xc) == 4L << (unsigned long)v9) {
          v8 = rt_0001da84(v8,v7,v5);
        }
        v3 = 0;
        v12[6] = (uint64_t)&G_00010004 + (v8 & 0xffffffffffff0000);
        goto LBL_00217fe4;
      }
    }
    v14 = *v12;
    v11 = v12[1];
    *v12 = 0;
    v12[1] = 0;
    if (v11 == 0) {
      v1 = 0;
      v3 = 1;
LBL_00217fe4:
      return v1 | v3 << 8;
    }
    lStack_68 = v11;
    (*(code *)v12[2])(&v13,&v14);
    rt_003a25d4(v11);
    v5 = uStack_58;
    v10 = v13;
    rt_003a25d4(v12[5]);
    v12[4] = v10;
    v12[5] = v5;
    v12[6] = 0xf;
  } while( true );
}



/* FUN_00218068 @ 0x00218068   (est. swift_string_peek_first)
 * Ghidra: uint32_t FUN_00218068( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_00218068( void){
  unsigned long v10;
  uint8_t v4;
  unsigned long v6;
  long v11;
  int v3;
  uint32_t v9;
  unsigned long v5;
  long v12;
  unsigned long v7;
  unsigned long v8;
  uint32_t v1;
  unsigned long v2;
  unsigned long v13;
  unsigned long uStack_58;
  
  v5 = *(unsigned long *)(v12 + 0x18);
  if (v5 != 0) {
    v7 = *(unsigned long *)(v12 + 0x10);
    v10 = v7 & 0xffffffffffff;
    if ((v5 & 0x2000000000000000) != 0) {
      v10 = v5 >> 0x38 & 0xf;
    }
    v8 = *(unsigned long *)(v12 + 0x20);
    if (v8 >> 0xe != v10 * 4) {
      v9 = (uint32_t)(v7 >> 0x3b) & 1;
      if ((v5 & 0x1000000000000000) == 0) {
        v9 = 1;
      }
      v6 = v8;
      if ((v8 & 0xc) == 4L << (unsigned long)v9) {
        v6 = rt_0001da84(v8,v7,v5);
      }
      v2 = v6 >> 0x10;
      if (v10 <= v2) {
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                     s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xe4,1);
      }
      if ((v5 >> 0x3c & 1) == 0) {
        if ((v5 >> 0x3d & 1) == 0) {
          if ((v7 >> 0x3c & 1) == 0) goto LBL_002181d0;
          v11 = (v5 & 0xfffffffffffffff) + 0x20;
          goto LBL_00218114;
        }
        v13 = v7;
        uStack_58 = v5 & 0xffffffffffffff;
        v4 = *(uint8_t *)((long)&v13 + v2);
      }
      else {
        rt_002b141c(v6,v7,v5);
LBL_002181d0:
        v11 = rt_002a9ba8(v7,v5).lo;
LBL_00218114:
        v4 = *(uint8_t *)(v11 + v2);
      }
      v1 = (uint32_t)v4;
      if ((v8 & 0xc) == 4L << (unsigned long)v9) {
        v8 = rt_0001da84(v8,v7,v5);
      }
      v3 = 0;
      *(void **)(v12 + 0x20) = &G_00010004 + (v8 & 0xffffffffffff0000);
      goto LBL_0021815c;
    }
  }
  v1 = 0;
  v3 = 1;
LBL_0021815c:
  return v1 | v3 << 8;
}



/* FUN_002181e0 @ 0x002181e0   (est. swift_string_loop)
 * Ghidra: void FUN_002181e0( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002181e0( void){
  uint8_t v4;
  code *v1;
  uint64_t v3;
  uint64_t v20;
  uint64_t v12;
  uint64_t v22;
  long v11;
  long v9;
  code *v7;
  code *v10;
  code *v8;
  code *v13;
  code *v16;
  code *v14;
  code *v21;
  code *v15;
  long v18;
  long v6;
  long v19;
  long v17;
  long v25;
  long v5;
  uint64_t v2;
  uint64_t v23;
  uint64_t v24;
  uint64_t v26;
  rt16 v42;
  rt16 v43;
  long v41;
  uint64_t v29;
  long v40;
  uint64_t v37;
  uint64_t v27;
  uint64_t v38;
  long v36;
  uint64_t v33;
  uint64_t v31;
  uint64_t v39;
  uint64_t uStack_40;
  long v34;
  unsigned long v28;
  code *v30;
  uint64_t uStack_20;
  uint64_t v32;
  long v35;
  
  v42 = rt_0008e518();
  v5 = v42.lo;
  v2 = *(uint64_t *)(v5 + 0x10);
  v29 = v22;
  rt_003520f8(v5,*(uint64_t *)(v5 + 0x18));
  v39 = v2;
  uStack_40 = v20;
  rt_00377824(0xff);
  rt_0034ee68();
  rt_00310d68();
  rt_00348e60();
  (*G_00658c00)(*(uint64_t *)(v11 + 0x40));
  rt_003489c0();
  (*G_00658c00)();
  rt_0034b4c0();
  v2 = *(uint64_t *)(v5 + 0x20);
  rt_0034de44();
  rt_00377824();
  rt_00352efc();
  v38 = v12;
  v27 = rt_00310d68().lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034c330();
  v32 = v2;
  rt_0034eb64(0xff);
  rt_00377824();
  rt_0034f554();
  rt_00310d68();
  rt_00348e00();
  (*G_00658c00)(*(uint64_t *)(v9 + 0x40));
  rt_003503ec();
  rt_0034d244();
  (*G_00658c00)();
  rt_00351c10((long)&v41 - v19);
  v30 = *(code **)(v18 + 0x10);
  v28 = (unsigned long)(v18 + 0x10) & 0xffffffffffff | 0xe3ba000000000000;
  v34 = v18 + 8;
  v5 = (long)*(int *)(v5 + 0x2c);
  v40 = v17 + 8;
  v41 = v17;
  v31 = rt_0035a59c();
  v36 = v6 + 0x18;
  v35 = v5;
  do {
    (*v30)(uStack_20,v25 + v5,v2);
    v43 = rt_00351330();
    rt_0035681c(v43.lo,v43.hi,v23);
    rt_00359c64();
    rt_003507e0();
    (*v7)();
    v4 = (int)v5 == 1;
    if (!(bool)v4) {
      rt_0034c4bc(v25 + v35);
      if ((bool)v4) {
        rt_00350410();
        goto LBL_002185cc;
      }
      rt_0034b278();
      rt_00350b84(v32);
      rt_00377bec();
      rt_00354474();
      v2 = v37;
      rt_003514e8(v37);
      (*v21)();
      v43 = rt_0035172c();
      rt_00350884(v43.lo,v43.hi,v38);
      if (!(bool)v4) {
        (**(code **)(v41 + 0x20))(v29,v2,v27);
        goto LBL_002185a0;
      }
      v2 = rt_00352bc8();
      (*v10)(v2,v27);
    }
    rt_0035454c();
    rt_00352998(0xff,uStack_40);
    rt_00377824();
    rt_003530f4();
    rt_00350a1c();
    v2 = rt_00377bec().lo;
    v1 = (code *)rt_000a68f4();
    rt_003504e8();
    v3 = rt_00377dcc();
    (*v1)(v26,v3,v2);
    rt_0034b2c8(v26);
    if ((bool)v4) {
      rt_00353bf4();
      rt_00350ab8();
      (*v14)();
      rt_00350744(v29);
      rt_000839d8();
LBL_002185a0:
      rt_0008e500(v42.hi);
      return;
    }
    rt_00354bbc();
    rt_003516e4();
    (*v8)();
    rt_0034b2c8(v24);
    if ((bool)v4) {
      rt_00350410();
LBL_002185cc:
      rt_00348898();
      rt_0034a2f8();
                    /* WARNING: Subroutine does not return */
      rt_001afe4c();
    }
    rt_00357664();
    rt_00352680();
    v3 = v33;
    rt_00358e34();
    rt_000e15d8();
    (*v15)();
    rt_00353bf4();
    rt_00350ab8();
    (*v13)();
    rt_00350750(v3);
    rt_000839d8();
    rt_00354ab0();
    v5 = v35;
    v2 = v31;
    (*v16)(v25 + v35,v3,v31);
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
  uint64_t v1;
  long v2;
  uint64_t v3;
  long v4;
  long v5;
  rt16 v6;
  
  v2 = rt_00351cc4();
  v1 = *(uint64_t *)(v2 + 0x20);
  v6 = rt_00350bd8(*(uint64_t *)(v2 + 0x18));
  rt_00349b14(v6.lo,v6.hi,*(uint64_t *)(v5 + 0x10));
  v6 = rt_00377824();
  v3 = rt_0034a944(v6.lo,v6.hi,v6.lo);
  rt_00377824(v3,v1);
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
  int v2;
  uint64_t v1;
  long v3;
  uint64_t v7;
  long v6;
  long v5;
  long v4;
  rt16 v8;
  
  rt_00084220();
  rt_00351dc0();
  rt_00353fac();
  v1 = rt_0034cae8();
  rt_00377824(v1,v7);
  rt_00349530();
  (**(code **)(v5 + 0x20))(v6);
  rt_0034f614();
  v3 = rt_0031be78();
  v2 = *(int *)(v3 + 0x2c);
  rt_00348f14();
  v8 = rt_00358ff4();
  rt_003519fc(v8.lo,v8.hi,v8.lo);
  rt_00377824();
  rt_00352efc();
  rt_00310d68();
  rt_0034ad10();
                    /* WARNING: Could not recover jumptable at 0x002187dc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(v4 + 0x20))(v6 + v2);
  return;
}



/* FUN_002187e0 @ 0x002187e0   (est. swift_dispatch7)
 * Ghidra: void FUN_002187e0( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_002187e0( void){
  uint8_t v22;
  int v3;
  uint64_t v7;
  uint64_t v5;
  unsigned long v2;
  long v6;
  uint64_t v16;
  uint64_t v20;
  uint64_t v21;
  code *v15;
  code *v12;
  code *v11;
  code *v10;
  code *v14;
  long v13;
  long v8;
  long v9;
  long v4;
  long v17;
  code *v1;
  long v18;
  rt16 v23;
  rt16 v24;
  uint64_t v19;
  
  v23 = rt_0008e518();
  rt_00348f14(v20);
  v7 = rt_00358ff4().lo;
  v5 = rt_0034c108();
  v5 = rt_00377824(v5,v21).lo;
  rt_000a6f88(v5,v5);
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
  v2 = (*v15)();
  if ((v2 & 1) != 0) {
    v24 = rt_0035050c();
    v6 = rt_0031be78(v24.lo,v24.hi,v20,v21);
    v3 = *(int *)(v6 + 0x2c);
    v4 = (long)*(int *)(v17 + 0x30);
    v1 = *(code **)(v8 + 0x10);
    rt_00353c6c(v6,v23.lo + (long)v3);
    (*v1)();
    (*v1)(v18 + v4,v23.hi + (long)v3,v21);
    v24 = rt_003517a8();
    rt_00350884(v24.lo,v24.hi,v16);
    v6 = v8;
    if ((bool)v22) {
      rt_00353c84(v18 + v4);
      v3 = rt_000839f8();
      if (v3 != 1) {
        v6 = v9;
      }
    }
    else {
      rt_00358db8();
      rt_003508c0();
      (*v1)();
      rt_00353c84(v18 + v4);
      rt_00350884();
      if ((bool)v22) {
        rt_003529a4();
        rt_003509b0();
        (*v12)();
        v6 = v9;
      }
      else {
        v5 = rt_003547ec();
        v24 = rt_00355bc4(v5,v18 + v4);
        (*v14)(v24.lo,v24.hi,v16);
        rt_0034c3c4();
        rt_00377bec(v21,v7,v16);
        rt_003514b8();
        rt_0014ae44();
        v7 = rt_00350a7c();
        rt_00351e78(v7,v23.hi);
        (*v11)();
        v1 = *(code **)(v13 + 8);
        rt_00350a04();
        (*v1)();
        rt_003509b0();
        (*v1)();
      }
    }
    rt_0035060c(*(uint64_t *)(v6 + 8));
    (*v10)();
  }
  v7 = rt_00352980();
  rt_0008e500(v7,v19);
  return;
}



/* FUN_00218ae4 @ 0x00218ae4   (est. swift_dispatch8)
 * Ghidra: void FUN_00218ae4( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00218ae4( void){
  int v9;
  uint8_t v33;
  uint32_t v13;
  uint64_t v10;
  long v14;
  uint64_t v7;
  unsigned long v12;
  long v8;
  unsigned long v11;
  uint64_t v31;
  uint64_t v32;
  long v29;
  long v22;
  long v19;
  code *v17;
  code *v20;
  code *v6;
  code *v18;
  code *v23;
  code *v26;
  code *v24;
  code *v16;
  code *v28;
  code *v25;
  code *v21;
  long v27;
  long v15;
  long v4;
  long v5;
  code *v1;
  code *v2;
  code *v3;
  uint64_t v30;
  rt16 v42;
  uint64_t v34;
  uint64_t v39;
  uint64_t v38;
  uint64_t v37;
  long v41;
  uint64_t v40;
  long v36;
  uint64_t v35;
  
  rt_0008e518();
  v42 = rt_00351dc0();
  v4 = v42.lo;
  rt_00348f14(v31);
  rt_00358ff4();
  v10 = rt_0034c158();
  v10 = rt_00377824(v10,v32).lo;
  rt_003542b8();
  rt_00310d68();
  rt_0034e57c();
  rt_003515b4();
  v14 = rt_003722e4();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v29 + 0x40));
  rt_00348b5c();
  (*G_00658c00)();
  rt_0034c2b4();
  rt_00349c70();
  (*G_00658c00)(*(uint64_t *)(v22 + 0x40));
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
  (*G_00658c00)(*(uint64_t *)(v19 + 0x40));
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
  v7 = rt_00377bec().lo;
  rt_0034a30c();
  rt_0034e084(v4);
  v12 = (*v17)();
  if ((v12 & 1) == 0) {
    rt_0016186c(v7);
    rt_0034e054();
    rt_003531e4();
    v13 = (*v20)();
    goto LBL_002190c0;
  }
  rt_0034f614();
  v8 = rt_0031be78();
  v9 = *(int *)(v8 + 0x2c);
  v2 = *(code **)(v27 + 0x10);
  rt_00355b04(v8,v4 + v9);
  (*v2)();
  rt_00349f3c();
  if (!(bool)v33) {
    v6 = *(code **)(v15 + 0x20);
    rt_00350c68(v35);
    (*v6)();
    (*v2)(v38,v42.hi + (long)*(int *)(v8 + 0x2c));
    rt_00349f3c(v38);
    if (!(bool)v33) {
      rt_0034ef28();
      (*v6)();
      rt_0034c3c4();
      rt_00355ad0(v32);
      rt_00377bec();
      rt_0034b4ec();
      rt_003504c4();
      rt_0034beec();
      v13 = (*v26)();
      v2 = *(code **)(v15 + 8);
      rt_003510b8();
      (*v2)();
      rt_00350524();
      (*v2)();
      goto LBL_002190c0;
    }
    rt_003569d8();
    (*v28)();
  }
  v3 = *(code **)(v27 + 8U);
  v12 = (unsigned long)(v27 + 8U) & 0xffffffffffff | 0x4f8000000000000;
  rt_00350b3c();
  (*v3)();
  rt_0034c3f4(v40);
  rt_000839d8();
  v5 = (long)*(int *)(v14 + 0x30);
  (*v2)(v36,v4 + v9);
  v6 = *(code **)(v27 + 0x20);
  (*v6)(v36 + v5,v40);
  rt_00349f3c(v36);
  if ((bool)v33) {
    rt_00349f3c(v36 + v5);
    if ((bool)v33) {
      rt_00350b3c();
      (*v3)(v12);
LBL_00218f50:
      v9 = *(int *)(v8 + 0x2c);
      rt_0034c3f4(v37);
      v7 = rt_000839d8().lo;
      v4 = (long)*(int *)(v14 + 0x30);
      rt_00358dd0(v7,v42.hi + (long)v9);
      (*v2)();
      rt_0035256c(v41 + v4);
      (*v6)();
      rt_00349f3c(v41);
      if ((bool)v33) {
        rt_00349f3c(v41 + v4);
        if (!(bool)v33) {
          v36 = v41;
          goto LBL_00219100;
        }
        rt_003507c8();
        (*v3)(v12);
      }
      else {
        rt_000e15d8();
        (*v2)();
        rt_00349f3c(v41 + v4);
        if ((bool)v33) {
          v39 = v34;
          v36 = v41;
          goto LBL_002190e8;
        }
        v10 = rt_003547ec();
        rt_003543f8(v10,v41 + v4);
        (*v21)();
        rt_0034c3c4();
        rt_00355ad0(v32);
        rt_00377bec();
        rt_0034a30c();
        rt_00350c80();
        rt_0034beec();
        v11 = (*v23)();
        v2 = *(code **)(v15 + 8);
        rt_003508cc();
        (*v2)();
        rt_003510b8();
        (*v2)();
        rt_003507c8();
        (*v3)(v12);
        if ((v11 & 1) == 0) goto LBL_00219118;
      }
      v13 = 0;
LBL_002190c0:
      rt_0008e500(v13 & 1,v30);
      return;
    }
  }
  else {
    rt_00350ea4();
    (*v2)();
    v7 = rt_00349f3c(v36 + v5);
    if (!(bool)v33) {
      rt_003543f8(v7,v36 + v5);
      (*v25)();
      rt_0034c3c4();
      rt_00355ad0(v32);
      rt_00377bec();
      rt_0034a30c();
      rt_00350a04();
      rt_0034beec();
      v11 = (*v18)();
      v1 = *(code **)(v15 + 8);
      rt_003508cc();
      (*v1)();
      rt_003505e8();
      (*v1)();
      rt_00350b3c();
      (*v3)(v12);
      if ((v11 & 1) == 0) goto LBL_00219118;
      goto LBL_00218f50;
    }
LBL_002190e8:
    rt_003529a4();
    (*v24)(v39,v10);
  }
LBL_00219100:
  rt_00359478();
  (*v16)(v36,v14);
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
  rt_0034d264(v1,s_uespemosmodnarodarenegylsetybdet_004e7a30[16],
               v1 ^ (uint8_t)s_uespemosmodnarodarenegylsetybdet_004e7a30.lo);
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
  unsigned long v5;
  unsigned long v4;
  unsigned long v2;
  uint64_t v1;
  rt16 v7;
  unsigned long v6;
  unsigned long v3;
  
  v4 = rt_002527e8();
  v6 = 0xf;
  if (0x3fff < v4) {
    v1 = 0xf;
    do {
      v2 = v6;
      v7 = rt_00252e24(v6,param_1,param_2,param_3,param_4);
      v3 = v7.hi;
      rt_003a25d4(v3);
      v5 = v7.lo & 0xffffffffffff;
      if ((v3 & 0x2000000000000000) != 0) {
        v5 = v3 >> 0x38 & 0xf;
      }
      if (v5 != 0) goto LBL_00219348;
      rt_00252b68(&v6,param_1,param_2,param_3,param_4);
    } while ((v6 ^ v4) >> 0xe != 0);
  }
  v1 = 0;
  v2 = v4;
LBL_00219348:
  v7.hi = v1;
  v7.lo = v2;
  return v7;
}



/* FUN_00219370 @ 0x00219370   (est. swift_string_reduce)
 * Ghidra: rt16 FUN_00219370( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
rt16 FUN_00219370( void){
  unsigned long v8;
  unsigned long v7;
  unsigned long v4;
  code *v1;
  unsigned long v2;
  unsigned long v9;
  unsigned long v3;
  uint64_t v5;
  unsigned long v6;
  unsigned long *v10;
  rt16 av80;
  uint8_t v11 [16];
  unsigned long v12;
  unsigned long uStack_68;
  
  v7 = *v10;
  v2 = v10[1];
  if (v2 >> 0xe != v7 >> 0xe) {
    v4 = v10[2];
    v9 = v10[3];
    v1 = (code *)v10[4];
    v6 = v7;
    do {
      av80 = rt_002b439c(v6,v7,v2,v4,v9);
      v11 = av80;
      (*v1)(&v12,v11);
      rt_003a25d4(av80.hi);
      v3 = uStack_68;
      v8 = v12;
      rt_003a25d4(uStack_68);
      v8 = v8 & 0xffffffffffff;
      if ((v3 & 0x2000000000000000) != 0) {
        v8 = v3 >> 0x38 & 0xf;
      }
      if (v8 != 0) {
        v5 = 0xf;
        goto LBL_00219458;
      }
      v5 = rt_002ab6a0(v6,v7,v2,v4,v9);
      v6 = rt_002b3b84(v5,v7,v2,v4,v9);
    } while (v2 >> 0xe != v6 >> 0xe);
  }
  v5 = 0;
  v6 = v2;
LBL_00219458:
  av80.hi = v5;
  av80.lo = v6;
  return av80;
}



/* FUN_0021947c @ 0x0021947c   (est. swift_array_reduce)
 * Ghidra: rt16 FUN_0021947c(long param_1, code * param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
rt16 FUN_0021947c(long param_1, code * param_2){
  unsigned long v5;
  unsigned long v4;
  uint64_t v2;
  long v6;
  long v3;
  uint64_t *v1;
  rt16 v9;
  uint64_t v8;
  uint64_t uStack_68;
  unsigned long v7;
  unsigned long uStack_58;
  
  v3 = *(long *)(param_1 + 0x10);
  if (v3 == 0) {
    v2 = 0;
    v6 = 0;
  }
  else {
    v6 = 0;
    v1 = (uint64_t *)(param_1 + 0x28);
    do {
      v8 = v1[-1];
      v2 = *v1;
      uStack_68 = v2;
      rt_0036b270(v2);
      (*param_2)(&v7,&v8);
      rt_003a25d4(v2);
      v4 = uStack_58;
      v5 = v7;
      rt_003a25d4(uStack_58);
      v5 = v5 & 0xffffffffffff;
      if ((v4 & 0x2000000000000000) != 0) {
        v5 = v4 >> 0x38 & 0xf;
      }
      if (v5 != 0) {
        v2 = 0xf;
        goto LBL_00219534;
      }
      v1 = v1 + 2;
      v6 = v6 + 1;
    } while (v3 != v6);
    v2 = 0;
    v6 = v3;
  }
LBL_00219534:
  v9.hi = v2;
  v9.lo = v6;
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
  uint64_t v18;
  uint64_t v17;
  long v11;
  code *v8;
  code *v6;
  code *v9;
  code *v7;
  code *v12;
  code *v14;
  code *v16;
  code *v13;
  code *v10;
  long v15;
  long v5;
  long v20;
  uint64_t v19;
  uint64_t v4;
  uint64_t v21;
  rt16 v23;
  uint64_t v22;
  
  rt_0008e518();
  rt_00351a38();
  rt_00350bd8(v18);
  v4 = *(uint64_t *)(v20 + 0x10);
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
  (*G_00658c00)(*(uint64_t *)(v11 + 0x40));
  rt_00348abc();
  (*G_00658c00)();
  rt_0034b758();
  rt_003512d8();
  rt_003507bc();
  (*v16)();
  rt_003506e8();
  rt_003507bc();
  (*v13)();
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
      (*v1)(v19,v4);
      FUN_002198fc(v17,v20);
LBL_002198e4:
      rt_0008e500(v21);
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
    v3 = (*v6)();
    if ((v3 & 1) == 0) {
      rt_00353be8();
      (*v12)(v19,v4);
      rt_0034fe64();
      rt_00351414(v22);
      (*v10)();
      rt_00350bf0(*(uint64_t *)(v15 + 8));
      (*v14)();
      rt_00350750(v22);
      rt_000839d8();
      rt_00350618(v17);
      rt_00350974();
      ((code)FUN_00218714)();
      goto LBL_002198e4;
    }
    rt_00350bf0(*(uint64_t *)(v15 + 8));
    (*v9)();
    rt_00027818();
    rt_003505f4();
    rt_00350878();
    (*v7)();
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
  uint64_t v9;
  uint64_t v8;
  code *v2;
  unsigned long v5;
  uint64_t v4;
  code *v1;
  unsigned long v6;
  uint64_t v30;
  long v23;
  long v17;
  long v15;
  long v18;
  code *v16;
  unsigned long v24;
  code *v27;
  code *v25;
  code *v14;
  code *v21;
  code *v13;
  code *v29;
  code *v26;
  code *v22;
  code *v19;
  code *v20;
  long v28;
  long v10;
  long v12;
  long v11;
  uint64_t v7;
  code *v3;
  uint64_t v32;
  uint64_t v31;
  rt16 av90;
  rt16 av91;
  uint64_t v38;
  uint64_t v35;
  uint64_t v33;
  uint64_t v37;
  uint64_t v36;
  uint8_t v39 [40];
  
  av90 = rt_0008e518();
  v4 = av90.lo;
  v7 = *(uint64_t *)(av90.hi + 0x10);
  v8 = param_3;
  v9 = rt_0034cae8();
  rt_00351f1c(v9,v8);
  v8 = rt_00377824().lo;
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v23 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034aa14();
  rt_00348f14(param_3);
  v9 = rt_00358ff4().lo;
  rt_00350768(0xff);
  rt_00377824();
  rt_0034ee68();
  rt_00310d68();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v17 + 0x40));
  rt_003493c4();
  rt_0034d254();
  (*G_00658c00)();
  rt_0034b3d8();
  rt_003499f0();
  (*G_00658c00)(*(uint64_t *)(v15 + 0x40));
  rt_003493c4();
  rt_0034d234();
  (*G_00658c00)();
  rt_0034c2b4();
  rt_003504e8();
  rt_00377dcc();
  rt_00348cd0();
  (*G_00658c00)(*(uint64_t *)(v18 + 0x40));
  rt_003493c4();
  rt_0034e6cc();
  (*G_00658c00)();
  rt_0034c2c8();
  rt_00352ecc(param_3);
  rt_003528ac(v39,v4);
  v2 = (code *)(*v16)();
  rt_00351c4c();
  (*v29)(v9);
  rt_0034c3b4();
  (*v2)();
  rt_0031be78(0,v7,param_3,param_4);
  (**(code **)(v10 + 0x10))();
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
  (*v26)();
  v2 = *(code **)(v12 + 8);
  rt_00350630();
  (*v2)();
  rt_00351750(v7);
  rt_00350a34(v33);
  (*v22)();
  rt_003510ac(*(uint64_t *)(v11 + 8));
  (*v27)();
  rt_0034c3c4();
  rt_00350e54();
  rt_00377bec();
  rt_00349fe0();
  rt_003507c8();
  rt_00350db4();
  v5 = (*v25)();
  rt_00350630();
  (*v2)();
  if ((v5 & 1) == 0) {
    v8 = (**(code **)(v28 + 0x10))(v37,v4,v8);
    rt_00358f54(*(uint64_t *)(v12 + 0x20),v8,v36);
    (*v14)();
    rt_0034f474(v35);
    av90 = rt_000839d8();
    rt_0009461c(v30,av90.lo,av90.hi,v7);
LBL_00219d7c:
    ((code)FUN_00218714)();
  }
  else {
    v5 = (unsigned long)(v11 + 8) & 0xffffffffffff | 0x4f8000000000000;
    (*v2)(v36);
    rt_00353d94(param_3);
    rt_00352f48(stack_ptr);
    rt_003510f4(v4);
    (*v19)();
    v2 = (code *)rt_00310924(param_3);
    rt_0034c3c4();
    av91 = rt_003507bc();
    rt_00377bec(av91.lo,av91.hi,v8);
    v4 = rt_00027754();
    v1 = (code *)rt_0014ae44();
    while( true ) {
      rt_00350c2c(v37);
      (*v2)();
      av91 = rt_003509d4();
      v6 = (*v1)(av91.lo,av91.hi,v8,v4);
      v3 = *(code **)(v28 + 8U);
      rt_0009461c();
      (*v3)();
      if ((v6 & 1) != 0) break;
      rt_00355634();
      rt_00351900();
      av91 = rt16_mklo((*v16)());
      (*v29)(v24 & 0xffffffffffff | 0xe3ba000000000000,v38,av91.hi,
                     v32);
      rt_0034c3b4();
      (*av91.lo)();
      rt_0035466c();
      rt_003192a8();
      v9 = rt_0034e62c();
      v6 = (*v21)(v9,v3);
      if ((v6 & 1) == 0) {
        rt_003578c0();
        rt_0035156c();
        rt_003511a8(v35);
        (*v20)();
        rt_00351450();
        rt_00353148();
        (*v27)();
        rt_0034ba48();
        rt_000839d8();
        rt_00350878(v30,v5);
        rt_00356958();
        goto LBL_00219d7c;
      }
      rt_003505e8();
      rt_00353148();
      (*v27)();
      rt_00027818(param_3);
      rt_00350a7c();
      rt_003510f4();
      (*v13)();
    }
    (*v3)(v28 + 8U & 0xffffffffffff | 0x4f8000000000000,v5,v8);
    FUN_002198fc(v30,av90.hi,param_3,param_4);
  }
  rt_0008e500(v31);
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
  uint64_t v9;
  unsigned long v8;
  uint64_t v5;
  code *v3;
  long v7;
  code *v1;
  long v37;
  long v30;
  long v11;
  code *v18;
  code *v29;
  unsigned long v21;
  code *v31;
  uint64_t v27;
  code *v25;
  code *v17;
  code *v13;
  code *v16;
  code *v36;
  code *v26;
  code *v33;
  code *v22;
  code *v12;
  code *v28;
  code *v14;
  code *v15;
  uint64_t *v23;
  code *v24;
  code *v32;
  code *v19;
  code *v20;
  code *v34;
  uint64_t *v35;
  uint64_t v10;
  long v38;
  code *v40;
  uint64_t *v2;
  code *v4;
  uint64_t v6;
  uint64_t v39;
  uint64_t v44;
  uint64_t v43;
  uint64_t v41;
  uint64_t v42;
  rt16 av90;
  uint64_t v46;
  uint8_t v47 [40];
  
  rt_0008e518();
  rt_003504d0();
  rt_00354128();
  rt_00350bd8(param_3);
  v6 = *(uint64_t *)(v38 + 0x10);
  av90 = rt_00349b14();
  rt_00377824(av90.lo,av90.hi,v6);
  rt_0034d2a4();
  rt_0034f564(0xff);
  rt_00377824();
  rt_0034e57c();
  rt_00310d68();
  v9 = rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v37 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  rt_003509a4();
  rt_00349c70();
  (*G_00658c00)(*(uint64_t *)(v30 + 0x40));
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
  (*G_00658c00)(*(uint64_t *)(v11 + 0x40));
  rt_003489c0();
  (*G_00658c00)();
  rt_0034b8bc();
  rt_003510c4();
  (*v36)();
  rt_00350704();
  rt_00350524();
  (*v26)();
  rt_0034c3c4();
  rt_00350600(param_3);
  rt_00377bec();
  rt_00349fe0();
  rt_00351354();
  rt_0034d344();
  v8 = (*v18)();
  rt_00353930(v10);
  (*v33)();
  if ((v8 & 1) != 0) {
    rt_0031afcc(param_3);
    v5 = rt_00353468();
    rt_0035430c(v5,0xffffffffffffffff);
    (*v22)();
    (*v33)();
    rt_003504a0();
    (*v12)();
  }
  rt_00352ecc(param_3);
  rt_0035430c(v47);
  rt_00352b98();
  v3 = (code *)(*v29)();
  rt_00356924();
  (*v28)();
  rt_00351cac();
  (*v3)();
  rt_00350920();
  rt_00351e3c();
  v7 = rt_0031be78();
  av90 = rt_00353124(stack_ptr,v7,v40 + *(int *)(v7 + 0x2c));
  (*v34)(av90.lo,av90.hi,v9);
  rt_0034e1b0();
  if ((bool)v45) {
    rt_00310924(param_4);
    rt_00351184();
    rt_0035084c();
    (*v14)();
    v2 = v35 + 1;
    rt_003514e8(*v2);
    (*v31)();
  }
  else {
    rt_00350b18();
    (*v15)();
    v2 = v35;
  }
  v3 = (code *)rt_000277b8(param_4);
  rt_0034c3c4();
  rt_00350b78();
  rt_00377bec();
  rt_00027754();
  v1 = (code *)rt_0014ae44();
  rt_00354134();
  rt_00359ca4();
  while( true ) {
    rt_0035084c(v46);
    (*v3)();
    rt_00350c38();
    rt_00351c94();
    v8 = (*v1)();
    v4 = (code *)*v23;
    rt_000dbd0c();
    (*v4)();
    if ((v8 & 1) == 0) break;
    rt_00350b3c();
    (*v4)(v27);
    rt_00356a70();
    rt_003511a8();
    (*v25)();
    rt_00356810();
    rt_0031afcc();
    v9 = rt_00356670(v43);
    rt_00352bec(v9,0xffffffffffffffff);
    (*v24)();
    rt_0035190c();
    (*v33)();
    rt_0034f9ec(stack_ptr);
    rt_00351ba0();
    (*v17)();
    rt_00351178(v47);
    rt_00353734();
    (*v13)();
    av90 = rt_003519a8();
    rt_00354b74(v21 & 0xffffffffffff | 0xe3ba000000000000,av90.lo,av90.hi,
                 v44);
    (*v32)();
    rt_0034c3b4();
    (*v40)();
    rt_00350704();
    rt_00356230();
    rt_003505e8();
    (*v19)();
  }
  rt_0031afcc(param_4);
  rt_003526b8(stack_ptr);
  rt_003518a0(v41,0xffffffffffffffff);
  (*v20)();
  rt_00350b3c();
  (*v4)(v27);
  rt_00356a70();
  rt_003511a8();
  (*v16)();
  rt_0034e094();
  rt_000839d8();
  rt_00353148();
  FUN_00218714(v39,v2,v6,param_3,param_4);
  rt_0008e500(v42);
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
  code *v6;
  bool v9;
  unsigned long v10;
  long v14;
  unsigned long v8;
  unsigned long v13;
  char *v1;
  uint64_t v11;
  uint32_t v12;
  unsigned long v5;
  unsigned long v7;
  unsigned long v4;
  long v2;
  rt16 v18;
  uint64_t v3;
  unsigned long v17;
  unsigned long v15;
  unsigned long v16;
  
  v4 = param_4 >> 0xe;
  v7 = param_1 >> 0xe;
  v15 = param_2;
  if (v4 == param_1 >> 0xe) {
    if (param_6 == '\x01') {
      if (param_3 == '\x01') {
        return 0;
      }
    }
    else if (param_3 != '\x01') {
      if (param_5 >> 0xe < param_2 >> 0xe) goto LBL_0021a760;
      goto LBL_0021a78c;
    }
    v3 = 0xc9;
    v1 = &G_005be7c0;
    v11 = 0;
    goto LBL_0021ace0;
  }
  if (v4 < v7) {
LBL_0021a760:
    v11 = rt_002527e8(param_7,param_8,param_9,param_10);
    rt_0029e8dc(v11,0xf,param_7,param_8);
    if (v4 == v7) {
LBL_0021a78c:
      if (param_3 == '\x01' || param_6 == '\x01') {
        return 0;
      }
      v18 = rt_00252e24(param_1,param_7,param_8,param_9,param_10);
      v7 = v18.hi;
      v4 = v18.lo;
      v12 = v18._hi32 >> 0x1b & 1;
      if ((v7 & 0x1000000000000000) == 0) {
        v12 = 1;
      }
      if ((param_2 & 0xc) == 4L << (unsigned long)v12) {
        param_2 = rt_0001da84(param_2,v4,v7);
      }
      if ((param_5 & 0xc) == 4L << (unsigned long)v12) {
        param_5 = rt_0001da84(param_5,v4,v7);
      }
      if ((v7 >> 0x3c & 1) == 0) {
        rt_003a25d4(v7);
        return (param_5 >> 0x10) - (param_2 >> 0x10);
      }
      v10 = v4 & 0xffffffffffff;
      if ((v7 & 0x2000000000000000) != 0) {
        v10 = v7 >> 0x38 & 0xf;
      }
      if (param_2 >> 0x10 <= v10 && param_5 >> 0x10 <= v10) {
        v14 = rt_002b15d0(param_2,param_5,v4,v7);
        rt_003a25d4(v7);
        return v14;
      }
      goto LBL_0021abec;
    }
    v18 = rt_00252e24(param_4,param_7,param_8,param_9,param_10);
    v13 = v18.hi;
    v10 = v18.lo;
    v4 = v10 & 0xffffffffffff;
    if ((v13 & 0x2000000000000000) != 0) {
      v4 = v13 >> 0x38 & 0xf;
    }
    v12 = v18._hi32 >> 0x1b & 1;
    if ((v13 & 0x1000000000000000) == 0) {
      v12 = 1;
    }
    v8 = 7;
    if (v12 == 0) {
      v8 = 0xb;
    }
    if (param_6 == '\x01') {
      v3 = 0x149;
      goto LBL_0021acac;
    }
    v5 = v8 | v4 << 0x10;
    if ((v8 & 0xc) == 4L << (unsigned long)v12) {
      v5 = rt_0001da84(v5,v10,v13);
    }
    if ((param_5 & 0xc) == 4L << (unsigned long)v12) {
      v17 = rt_0001da84(param_5,v10,v13);
      if ((v13 >> 0x3c & 1) == 0) goto LBL_0021a848;
LBL_0021ab80:
      if (v4 < v5 >> 0x10 || v4 < v17 >> 0x10) goto LBL_0021abec;
      v14 = rt_002b15d0(v5,v17,v10,v13);
      rt_003a25d4(v13);
    }
    else {
      v17 = param_5;
      if ((v13 >> 0x3c & 1) != 0) goto LBL_0021ab80;
LBL_0021a848:
      rt_003a25d4(v13);
      v14 = (v17 >> 0x10) - (v5 >> 0x10);
    }
    v2 = -1;
    v10 = param_4;
    v4 = v7;
    v17 = param_1;
    param_6 = param_3;
  }
  else {
    v18 = rt_00252e24(param_1,param_7,param_8,param_9,param_10);
    v10 = v18.hi;
    v7 = v18.lo;
    if (param_3 == '\x01') {
      v3 = 0x14f;
LBL_0021acac:
      v1 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
      v11 = 0x39;
LBL_0021ace0:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v1,v11,2,s_Swift_Flatten_swift_005cf8d0,0x13,2
                   ,v3,1);
    }
    v13 = v7 & 0xffffffffffff;
    if ((v10 & 0x2000000000000000) != 0) {
      v13 = v10 >> 0x38 & 0xf;
    }
    v12 = v18._hi32 >> 0x1b & 1;
    if ((v10 & 0x1000000000000000) == 0) {
      v12 = 1;
    }
    if (v12 == 1) {
      v8 = v13 << 0x10 | 7;
      if ((v10 >> 0x3c & 1) != 0) goto LBL_0021a8ec;
      v5 = 1;
    }
    else {
      v8 = v13 << 0x10 | 0xb;
LBL_0021a8ec:
      v5 = (v7 & 0x800000000000000) >> 0x3b;
    }
    if ((param_2 & 0xc) == 4L << v5) {
      v15 = rt_0001da84(param_2,v7,v10);
    }
    if ((v8 & 0xc) == 4L << v12) {
      v8 = rt_0001da84(v8,v7,v10);
      if ((v10 >> 0x3c & 1) == 0) goto LBL_0021a948;
LBL_0021aad4:
      if (v13 < v15 >> 0x10 || v13 < v8 >> 0x10) goto LBL_0021abec;
      v14 = rt_002b15d0(v15,v8,v7,v10);
      rt_003a25d4(v10);
    }
    else {
      if ((v10 >> 0x3c & 1) != 0) goto LBL_0021aad4;
LBL_0021a948:
      rt_003a25d4(v10);
      v14 = (v8 >> 0x10) - (v15 >> 0x10);
    }
    v2 = 1;
    v10 = param_1;
    v17 = param_4;
    v15 = param_5;
  }
  v16 = rt_00252818(v10,param_7,param_8,param_9,param_10);
  while (v16 >> 0xe < v4) {
    v18 = rt_00252e24(v16,param_7,param_8,param_9,param_10);
    v7 = v18.hi;
    if ((v7 >> 0x3c & 1) == 0) {
      rt_003a25d4(v7);
      v10 = v18.lo & 0xffffffffffff;
      if ((v7 & 0x2000000000000000) != 0) {
        v10 = v7 >> 0x38 & 0xf;
      }
    }
    else {
      v10 = rt_002b24b8(v18.lo,v7);
      rt_003a25d4(v7);
    }
    v9 = SCARRY8(v14,v10 * v2);
    v14 = v14 + v10 * v2;
    if (v9) {
                    /* WARNING: Does not return */
      v6 = (code *)SW_BREAK(0x21aab4);
      (*v6)();
    }
    rt_00252b68(&v16,param_7,param_8,param_9,param_10);
  }
  if (param_6 == '\x01') {
    return v14;
  }
  v18 = rt_00252e24(v17,param_7,param_8,param_9,param_10);
  v7 = v18.hi;
  v4 = v18.lo;
  v12 = v18._hi32 >> 0x1b & 1;
  if ((v7 & 0x1000000000000000) == 0) {
    v12 = 1;
  }
  if ((v15 & 0xc) == 4L << v12) {
    v15 = rt_0001da84(v15,v4,v7);
  }
  if ((v7 >> 0x3c & 1) == 0) {
    rt_003a25d4(v7);
    v15 = v15 >> 0x10;
  }
  else {
    v10 = v4 & 0xffffffffffff;
    if ((v7 & 0x2000000000000000) != 0) {
      v10 = v7 >> 0x38 & 0xf;
    }
    if (v10 < v15 >> 0x10) {
LBL_0021abec:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                   s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xcf,1);
    }
    v15 = rt_002b15d0(0xf,v15,v4,v7);
    rt_003a25d4(v7);
  }
  if (SCARRY8(v14,v15 * v2)) {
                    /* WARNING: Does not return */
    v6 = (code *)SW_BREAK(0x21ab60);
    (*v6)();
  }
  return v14 + v15 * v2;
}



/* FUN_0021acec @ 0x0021acec   (est. swift_string_distance_utf8)
 * Ghidra: long FUN_0021acec(unsigned long param_1, long param_2, char param_3, unsigned long param_4, long param_5, char param_6, uint64_t param_7, uint64_t param_8, uint64_t param_9, uint64_t param_10)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021acec(unsigned long param_1, long param_2, char param_3, unsigned long param_4, long param_5, char param_6, uint64_t param_7, uint64_t param_8, uint64_t param_9, uint64_t param_10){
  long v8;
  long v11;
  code *v4;
  bool v9;
  uint32_t v7;
  unsigned long v13;
  char *v3;
  uint64_t v10;
  unsigned long v12;
  long v2;
  unsigned long v6;
  long v5;
  rt16 v17;
  uint64_t v1;
  unsigned long v16;
  long v14;
  unsigned long v15;
  
  v6 = param_4 >> 0xe;
  v12 = param_1 >> 0xe;
  if (v6 == param_1 >> 0xe) {
    if (param_6 == '\x01') {
      if (param_3 == '\x01') {
        return 0;
      }
    }
    else if (param_3 != '\x01') {
      if (param_2 <= param_5) goto LBL_0021ae60;
      goto LBL_0021ae34;
    }
    v1 = 0xc9;
    v3 = &G_005be7c0;
    v10 = 0;
  }
  else {
    if (v6 < v12) {
LBL_0021ae34:
      v10 = rt_002527e8(param_7,param_8,param_9,param_10);
      rt_002a9d64(v10,0xf,param_7,param_8);
      if (v6 == v12) {
LBL_0021ae60:
        if (param_3 == '\x01' || param_6 == '\x01') {
          return 0;
        }
        v7 = rt_002532a8(param_1,param_7,param_8,param_9,param_10);
        v10 = 3;
        if (0xffff < v7) {
          v10 = 4;
        }
        v1 = 2;
        if (0x7ff < v7) {
          v1 = v10;
        }
        v10 = 1;
        if (0x7f < v7) {
          v10 = v1;
        }
        v17 = rt_001dff60(0,v10);
        rt_0019fe7c(param_2,v17.lo,v17.hi);
        v17 = rt_001dff60(0,v10);
        rt_0019fe7c(param_5,v17.lo,v17.hi);
        if (SBORROW8(param_5,param_2)) {
                    /* WARNING: Does not return */
          v4 = (code *)SW_BREAK(0x21b10c);
          (*v4)();
        }
        return param_5 - param_2;
      }
      v7 = rt_002532a8(param_4,param_7,param_8,param_9,param_10);
      v2 = 3;
      if (0xffff < v7) {
        v2 = 4;
      }
      v5 = 2;
      if (0x7ff < v7) {
        v5 = v2;
      }
      v2 = 1;
      if (0x7f < v7) {
        v2 = v5;
      }
      if (param_6 != '\x01') {
        v17 = rt_001dff60(0,v2);
        rt_0019fe7c(v2,v17.lo,v17.hi);
        v17 = rt_001dff60(0,v2);
        rt_0019fe7c(param_5,v17.lo,v17.hi);
        v5 = param_5 - v2;
        if (SBORROW8(param_5,v2)) {
                    /* WARNING: Does not return */
          v4 = (code *)SW_BREAK(0x21b108);
          (*v4)();
        }
        v2 = -1;
        v13 = param_4;
        v6 = v12;
        v16 = param_1;
        v14 = param_2;
        param_6 = param_3;
LBL_0021af20:
        v15 = rt_00252a64(v13,param_7,param_8,param_9,param_10);
        while (v15 >> 0xe < v6) {
          v7 = rt_002532a8(v15,param_7,param_8,param_9,param_10);
          v8 = 3;
          if (0xffff < v7) {
            v8 = 4;
          }
          v11 = 2;
          if (0x7ff < v7) {
            v11 = v8;
          }
          v8 = 1;
          if (0x7f < v7) {
            v8 = v11;
          }
          v9 = SCARRY8(v5,v8 * v2);
          v5 = v5 + v8 * v2;
          if (v9) {
                    /* WARNING: Does not return */
            v4 = (code *)SW_BREAK(0x21b100);
            (*v4)();
          }
          rt_00252d38(&v15,param_7,param_8,param_9,param_10);
        }
        if (param_6 != '\x01') {
          v7 = rt_002532a8(v16,param_7,param_8,param_9,param_10);
          v10 = 3;
          if (0xffff < v7) {
            v10 = 4;
          }
          v1 = 2;
          if (0x7ff < v7) {
            v1 = v10;
          }
          v10 = 1;
          if (0x7f < v7) {
            v10 = v1;
          }
          v17 = rt_001dff60(0,v10);
          rt_0019fe7c(0,v17.lo,v17.hi);
          v17 = rt_001dff60(0,v10);
          rt_0019fe7c(v14,v17.lo,v17.hi);
          v9 = SCARRY8(v5,v14 * v2);
          v5 = v5 + v14 * v2;
          if (v9) {
                    /* WARNING: Does not return */
            v4 = (code *)SW_BREAK(0x21b04c);
            (*v4)();
          }
        }
        return v5;
      }
      v1 = 0x149;
    }
    else {
      v7 = rt_002532a8(param_1,param_7,param_8,param_9,param_10);
      if (param_3 != '\x01') {
        v2 = 3;
        if (0xffff < v7) {
          v2 = 4;
        }
        v5 = 2;
        if (0x7ff < v7) {
          v5 = v2;
        }
        v2 = 1;
        if (0x7f < v7) {
          v2 = v5;
        }
        v17 = rt_001dff60(0,v2);
        rt_0019fe7c(param_2,v17.lo,v17.hi);
        v17 = rt_001dff60(0,v2);
        rt_0019fe7c(v2,v17.lo,v17.hi);
        v5 = v2 - param_2;
        if (SBORROW8(v2,param_2)) {
                    /* WARNING: Does not return */
          v4 = (code *)SW_BREAK(0x21b104);
          (*v4)();
        }
        v2 = 1;
        v13 = param_1;
        v16 = param_4;
        v14 = param_5;
        goto LBL_0021af20;
      }
      v1 = 0x14f;
    }
    v3 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
    v10 = 0x39;
  }
                    /* WARNING: Subroutine does not return */
  rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v3,v10,2,s_Swift_Flatten_swift_005cf8d0,0x13,2,
               v1,1);
}



/* FUN_0021b1a4 @ 0x0021b1a4   (est. swift_string_distance2)
 * Ghidra: long FUN_0021b1a4(unsigned long param_1, unsigned long param_2, char param_3, unsigned long param_4, unsigned long param_5, char param_6)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021b1a4(unsigned long param_1, unsigned long param_2, char param_3, unsigned long param_4, unsigned long param_5, char param_6){
  unsigned long v15;
  uint64_t v14;
  uint64_t v11;
  code *v5;
  bool v9;
  unsigned long v16;
  uint64_t v10;
  unsigned long v13;
  long v12;
  unsigned long v6;
  char *v1;
  uint64_t v7;
  uint32_t v3;
  uint64_t *v17;
  unsigned long v2;
  unsigned long v4;
  rt16 av156;
  uint64_t v8;
  unsigned long v19;
  unsigned long v21;
  unsigned long v23;
  long v22;
  rt16 v18;
  unsigned long v20;
  unsigned long uStack_68;
  
  v7 = *v17;
  v14 = v17[1];
  v8 = v17[2];
  v11 = v17[3];
  v5 = (code *)v17[4];
  v4 = param_4 >> 0xe;
  v2 = param_1 >> 0xe;
  v23 = param_2;
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
    v8 = 0xc9;
    v1 = &G_005be7c0;
    v7 = 0;
    goto LBL_0021b910;
  }
  if (v4 < v2) {
LBL_0021b2d0:
    rt_002b4120(v14,v7,v7,v14,v8,v11);
    if (v4 == v2) {
LBL_0021b2f4:
      if (param_3 == '\x01' || param_6 == '\x01') {
        return 0;
      }
      v18 = rt_002b439c(param_1,v7,v14,v8,v11);
      v7 = v18.hi;
      (*v5)(&v20,v18);
      rt_003a25d4(v7);
      v3 = (uint32_t)(v20 >> 0x3b) & 1;
      if ((uStack_68 & 0x1000000000000000) == 0) {
        v3 = 1;
      }
      if ((param_2 & 0xc) == 4L << (unsigned long)v3) {
        param_2 = rt_0001da84(param_2,v20,uStack_68);
      }
      if ((param_5 & 0xc) == 4L << (unsigned long)v3) {
        param_5 = rt_0001da84(param_5,v20,uStack_68);
      }
      if ((uStack_68 >> 0x3c & 1) == 0) {
        rt_003a25d4(uStack_68);
        return (param_5 >> 0x10) - (param_2 >> 0x10);
      }
      v4 = v20 & 0xffffffffffff;
      if ((uStack_68 & 0x2000000000000000) != 0) {
        v4 = uStack_68 >> 0x38 & 0xf;
      }
      if (param_2 >> 0x10 <= v4 && param_5 >> 0x10 <= v4) {
        v12 = rt_002b15d0(param_2,param_5,v20,uStack_68);
        rt_003a25d4(uStack_68);
        return v12;
      }
      goto LBL_0021b81c;
    }
    v18 = rt_002b439c(param_4,v7,v14,v8,v11);
    v10 = v18.hi;
    (*v5)(&v20,v18);
    rt_003a25d4(v10);
    v15 = uStack_68;
    v13 = v20;
    v4 = v20 & 0xffffffffffff;
    if ((uStack_68 & 0x2000000000000000) != 0) {
      v4 = uStack_68 >> 0x38 & 0xf;
    }
    v3 = (uint32_t)(v20 >> 0x3b) & 1;
    if ((uStack_68 & 0x1000000000000000) == 0) {
      v3 = 1;
    }
    v6 = 7;
    if (v3 == 0) {
      v6 = 0xb;
    }
    if (param_6 == '\x01') {
      v8 = 0x149;
      goto LBL_0021b8dc;
    }
    v16 = v6 | v4 << 0x10;
    if ((v6 & 0xc) == 4L << (unsigned long)v3) {
      v16 = rt_0001da84(v16,v20,uStack_68);
    }
    if ((param_5 & 0xc) == 4L << (unsigned long)v3) {
      v19 = rt_0001da84(param_5,v13,v15);
      if ((v15 >> 0x3c & 1) == 0) goto LBL_0021b3d0;
LBL_0021b7b4:
      if (v4 < v16 >> 0x10 || v4 < v19 >> 0x10) goto LBL_0021b81c;
      v12 = rt_002b15d0(v16,v19,v13,v15);
      rt_003a25d4(v15);
    }
    else {
      v19 = param_5;
      if ((v15 >> 0x3c & 1) != 0) goto LBL_0021b7b4;
LBL_0021b3d0:
      rt_003a25d4(v15);
      v12 = (v19 >> 0x10) - (v16 >> 0x10);
    }
    v22 = -1;
    v13 = param_4;
    v4 = v2;
    v21 = param_1;
    param_6 = param_3;
  }
  else {
    v18 = rt_002b439c(param_1,v7,v14,v8,v11);
    v10 = v18.hi;
    (*v5)(&v20,v18);
    rt_003a25d4(v10);
    v13 = uStack_68;
    v2 = v20;
    if (param_3 == '\x01') {
      v8 = 0x14f;
LBL_0021b8dc:
      v1 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
      v7 = 0x39;
LBL_0021b910:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v1,v7,2,s_Swift_Flatten_swift_005cf8d0,0x13
                   ,2,v8,1);
    }
    v15 = v20 & 0xffffffffffff;
    if ((uStack_68 & 0x2000000000000000) != 0) {
      v15 = uStack_68 >> 0x38 & 0xf;
    }
    v3 = (uint32_t)(v20 >> 0x3b) & 1;
    if ((uStack_68 & 0x1000000000000000) == 0) {
      v3 = 1;
    }
    if (v3 == 1) {
      v6 = v15 << 0x10 | 7;
      if ((uStack_68 >> 0x3c & 1) != 0) goto LBL_0021b4a0;
      v16 = 1;
    }
    else {
      v6 = v15 << 0x10 | 0xb;
LBL_0021b4a0:
      v16 = (v20 & 0x800000000000000) >> 0x3b;
    }
    if ((param_2 & 0xc) == 4L << v16) {
      v23 = rt_0001da84(param_2,v20,uStack_68);
    }
    if ((v6 & 0xc) == 4L << v3) {
      v6 = rt_0001da84(v6,v2,v13);
      if ((v13 >> 0x3c & 1) == 0) goto LBL_0021b4f4;
LBL_0021b704:
      if (v15 < v23 >> 0x10 || v15 < v6 >> 0x10) goto LBL_0021b81c;
      v12 = rt_002b15d0(v23,v6,v2,v13);
      rt_003a25d4(v13);
    }
    else {
      if ((v13 >> 0x3c & 1) != 0) goto LBL_0021b704;
LBL_0021b4f4:
      rt_003a25d4(v13);
      v12 = (v6 >> 0x10) - (v23 >> 0x10);
    }
    v22 = 1;
    v13 = param_1;
    v21 = param_4;
    v23 = param_5;
  }
  v10 = rt_002ab6a0(v13,v7,v14,v8,v11);
  v2 = rt_002b3b84(v10,v7,v14,v8,v11);
  while (v2 >> 0xe < v4) {
    av156 = rt_002b439c(v2,v7,v14,v8,v11);
    v18 = rt16_mklo(av156);
    (*v5)(&v20,v18);
    rt_003a25d4(av156.hi);
    v15 = uStack_68;
    v13 = v20;
    if ((uStack_68 >> 0x3c & 1) == 0) {
      rt_003a25d4(uStack_68);
      v13 = v13 & 0xffffffffffff;
      if ((v15 & 0x2000000000000000) != 0) {
        v13 = v15 >> 0x38 & 0xf;
      }
    }
    else {
      v13 = rt_002b24b8(v20,uStack_68);
      rt_003a25d4(v15);
    }
    v9 = SCARRY8(v12,v13 * v22);
    v12 = v12 + v13 * v22;
    if (v9) {
                    /* WARNING: Does not return */
      v5 = (code *)SW_BREAK(0x21b6e4);
      (*v5)();
    }
    v10 = rt_002ab6a0(v2,v7,v14,v8,v11);
    v2 = rt_002b3b84(v10,v7,v14,v8,v11);
  }
  if (param_6 == '\x01') {
    return v12;
  }
  av156 = rt_002b439c(v21,v7,v14,v8,v11);
  v18 = rt16_mklo(av156);
  (*v5)(&v20,v18);
  rt_003a25d4(av156.hi);
  v3 = (uint32_t)(v20 >> 0x3b) & 1;
  if ((uStack_68 & 0x1000000000000000) == 0) {
    v3 = 1;
  }
  if ((v23 & 0xc) == 4L << v3) {
    v23 = rt_0001da84(v23,v20,uStack_68);
  }
  if ((uStack_68 >> 0x3c & 1) == 0) {
    rt_003a25d4(uStack_68);
    v23 = v23 >> 0x10;
  }
  else {
    v4 = v20 & 0xffffffffffff;
    if ((uStack_68 & 0x2000000000000000) != 0) {
      v4 = uStack_68 >> 0x38 & 0xf;
    }
    if (v4 < v23 >> 0x10) {
LBL_0021b81c:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                   s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xcf,1);
    }
    v23 = rt_002b15d0(0xf,v23,v20,uStack_68);
    rt_003a25d4(uStack_68);
  }
  if (SCARRY8(v12,v23 * v22)) {
                    /* WARNING: Does not return */
    v5 = (code *)SW_BREAK(0x21b78c);
    (*v5)();
  }
  return v12 + v23 * v22;
}



/* FUN_0021b91c @ 0x0021b91c   (est. swift_string_distance3)
 * Ghidra: long FUN_0021b91c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, long param_7, code * param_8, uint64_t param_9)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021b91c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, long param_7, code * param_8, uint64_t param_9){
  code *v8;
  bool v10;
  unsigned long v12;
  unsigned long v9;
  long v15;
  char *v3;
  uint64_t v11;
  uint32_t v13;
  unsigned long v14;
  unsigned long v7;
  long v5;
  long v6;
  unsigned long v2;
  uint64_t *v1;
  rt16 v19;
  uint64_t v4;
  unsigned long v18;
  uint64_t v16;
  uint64_t uStack_78;
  unsigned long v17;
  unsigned long uStack_68;
  
  if (param_4 == param_1) {
    if (param_6 == '\x01') {
      if (param_3 == '\x01') {
        return 0;
      }
    }
    else if (param_3 != '\x01') {
      v19 = rt_0025346c(param_4,param_7,param_8,param_9);
      v7 = v19.hi;
      v12 = v19.lo;
      v13 = v19._hi32 >> 0x1b & 1;
      if ((v7 & 0x1000000000000000) == 0) {
        v13 = 1;
      }
      if ((param_2 & 0xc) == 4L << (unsigned long)v13) {
        param_2 = rt_0001da84(param_2,v12,v7);
      }
      if ((param_5 & 0xc) == 4L << (unsigned long)v13) {
        param_5 = rt_0001da84(param_5,v12,v7);
      }
      if ((v7 >> 0x3c & 1) == 0) {
        rt_003a25d4(v7);
        return (param_5 >> 0x10) - (param_2 >> 0x10);
      }
      v9 = v12 & 0xffffffffffff;
      if ((v7 & 0x2000000000000000) != 0) {
        v9 = v7 >> 0x38 & 0xf;
      }
      if (param_2 >> 0x10 <= v9 && param_5 >> 0x10 <= v9) {
        v15 = rt_002b15d0(param_2,param_5,v12,v7);
        rt_003a25d4(v7);
        return v15;
      }
      goto LBL_0021be08;
    }
    v4 = 0xc9;
    v3 = &G_005be7c0;
    v11 = 0;
    goto LBL_0021bf54;
  }
  v18 = param_2;
  if (param_4 < param_1) {
    v19 = rt_0025346c(param_4,param_7,param_8,param_9);
    v9 = v19.hi;
    v7 = v19.lo;
    v12 = v7 & 0xffffffffffff;
    if ((v9 & 0x2000000000000000) != 0) {
      v12 = v9 >> 0x38 & 0xf;
    }
    v13 = v19._hi32 >> 0x1b & 1;
    if ((v9 & 0x1000000000000000) == 0) {
      v13 = 1;
    }
    v2 = 7;
    if (v13 == 0) {
      v2 = 0xb;
    }
    if (param_6 == '\x01') {
      v4 = 0x149;
LBL_0021bf20:
      v3 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
      v11 = 0x39;
LBL_0021bf54:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v3,v11,2,s_Swift_Flatten_swift_005cf8d0,0x13,2
                   ,v4,1);
    }
    v14 = v2 | v12 << 0x10;
    if ((v2 & 0xc) == 4L << (unsigned long)v13) {
      v14 = rt_0001da84(v14,v7,v9);
    }
    if ((param_5 & 0xc) == 4L << (unsigned long)v13) {
      param_5 = rt_0001da84(param_5,v7,v9);
      if ((v9 >> 0x3c & 1) != 0) goto LBL_0021bd40;
LBL_0021ba1c:
      rt_003a25d4(v9);
      v15 = (param_5 >> 0x10) - (v14 >> 0x10);
    }
    else {
      if ((v9 >> 0x3c & 1) == 0) goto LBL_0021ba1c;
LBL_0021bd40:
      if (v12 < v14 >> 0x10 || v12 < param_5 >> 0x10) goto LBL_0021be08;
      v15 = rt_002b15d0(v14,param_5,v7,v9);
      rt_003a25d4(v9);
    }
    v6 = -1;
    v5 = param_1;
    param_1 = param_4;
    param_6 = param_3;
  }
  else {
    v19 = rt_0025346c(param_1,param_7,param_8,param_9);
    v7 = v19.hi;
    v12 = v19.lo;
    if (param_3 == '\x01') {
      v4 = 0x14f;
      goto LBL_0021bf20;
    }
    v9 = v12 & 0xffffffffffff;
    if ((v7 & 0x2000000000000000) != 0) {
      v9 = v7 >> 0x38 & 0xf;
    }
    v13 = v19._hi32 >> 0x1b & 1;
    if ((v7 & 0x1000000000000000) == 0) {
      v13 = 1;
    }
    if (v13 == 1) {
      v2 = v9 << 0x10 | 7;
      if ((v7 >> 0x3c & 1) != 0) goto LBL_0021bb18;
      v14 = 1;
    }
    else {
      v2 = v9 << 0x10 | 0xb;
LBL_0021bb18:
      v14 = (v12 & 0x800000000000000) >> 0x3b;
    }
    if ((param_2 & 0xc) == 4L << v14) {
      v18 = rt_0001da84(param_2,v12,v7);
    }
    if ((v2 & 0xc) == 4L << v13) {
      v2 = rt_0001da84(v2,v12,v7);
      if ((v7 >> 0x3c & 1) != 0) goto LBL_0021bdf4;
LBL_0021bb6c:
      rt_003a25d4(v7);
      v15 = (v2 >> 0x10) - (v18 >> 0x10);
    }
    else {
      if ((v7 >> 0x3c & 1) == 0) goto LBL_0021bb6c;
LBL_0021bdf4:
      if (v9 < v18 >> 0x10 || v9 < v2 >> 0x10) goto LBL_0021be08;
      v15 = rt_002b15d0(v18,v2,v12,v7);
      rt_003a25d4(v7);
    }
    v6 = 1;
    v5 = param_4;
    v18 = param_5;
  }
  v12 = param_1 + 1;
  if (SCARRY8(param_1,1)) {
                    /* WARNING: Does not return */
    v8 = (code *)SW_BREAK(0x21bd28);
    (*v8)();
  }
  if ((long)v12 < v5) {
    v1 = (uint64_t *)(param_7 + param_1 * 0x10 + 0x38);
    v7 = v12;
    do {
      if (((long)v12 < 0) || (*(unsigned long *)(param_7 + 0x10) <= v7)) {
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Index_out_of_range_005cd940,0x12,2,
                     s_Swift_ContiguousArrayBuffer_swif_005cd960,0x21,2,0x2b4,1);
      }
      v16 = v1[-1];
      v11 = *v1;
      uStack_78 = v11;
      rt_0036b270(v11);
      (*param_8)(&v17,&v16);
      rt_003a25d4(v11);
      v2 = uStack_68;
      v9 = v17;
      if ((uStack_68 >> 0x3c & 1) == 0) {
        rt_003a25d4(uStack_68);
        v9 = v9 & 0xffffffffffff;
        if ((v2 & 0x2000000000000000) != 0) {
          v9 = v2 >> 0x38 & 0xf;
        }
      }
      else {
        v9 = rt_002b24b8(v17,uStack_68);
        rt_003a25d4(v2);
      }
      v10 = SCARRY8(v15,v9 * v6);
      v15 = v15 + v9 * v6;
      if (v10) {
                    /* WARNING: Does not return */
        v8 = (code *)SW_BREAK(0x21bd24);
        (*v8)();
      }
      v7 = v7 + 1;
      v1 = v1 + 2;
    } while ((long)v7 < v5);
  }
  if (param_6 == '\x01') {
    return v15;
  }
  v19 = rt_0025346c(v5,param_7,param_8,param_9);
  v7 = v19.hi;
  v12 = v19.lo;
  v13 = v19._hi32 >> 0x1b & 1;
  if ((v7 & 0x1000000000000000) == 0) {
    v13 = 1;
  }
  if ((v18 & 0xc) == 4L << v13) {
    v18 = rt_0001da84(v18,v12,v7);
  }
  if ((v7 >> 0x3c & 1) == 0) {
    rt_003a25d4(v7);
    v18 = v18 >> 0x10;
  }
  else {
    v9 = v12 & 0xffffffffffff;
    if ((v7 & 0x2000000000000000) != 0) {
      v9 = v7 >> 0x38 & 0xf;
    }
    if (v9 < v18 >> 0x10) {
LBL_0021be08:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                   s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xcf,1);
    }
    v18 = rt_002b15d0(0xf,v18,v12,v7);
    rt_003a25d4(v7);
  }
  if (!SCARRY8(v15,v18 * v6)) {
    return v15 + v18 * v6;
  }
                    /* WARNING: Does not return */
  v8 = (code *)SW_BREAK(0x21bea8);
  (*v8)();
}



/* FUN_0021bf60 @ 0x0021bf60   (est. swift_string_distance_utf8_2)
 * Ghidra: long FUN_0021bf60(long param_1, long param_2, char param_3, long param_4, long param_5, char param_6, uint64_t param_7, code * param_8, uint64_t param_9)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021bf60(long param_1, long param_2, char param_3, long param_4, long param_5, char param_6, uint64_t param_7, code * param_8, uint64_t param_9){
  long v4;
  code *v2;
  bool v6;
  uint32_t v5;
  long v9;
  char *v1;
  uint64_t v7;
  long v10;
  long v8;
  rt16 v14;
  uint64_t v3;
  long v12;
  uint32_t v13;
  uint32_t v11;
  
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
    v3 = 0xc9;
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
      v5 = rt_002534e4(param_1,param_7,param_8,param_9);
      v7 = 3;
      if (0xffff < v5) {
        v7 = 4;
      }
      v3 = 2;
      if (0x7ff < v5) {
        v3 = v7;
      }
      v7 = 1;
      if (0x7f < v5) {
        v7 = v3;
      }
      v14 = rt_001dff60(0,v7);
      rt_0019fe7c(param_2,v14.lo,v14.hi);
      v14 = rt_001dff60(0,v7);
      rt_0019fe7c(param_5,v14.lo,v14.hi);
      if (SBORROW8(param_5,param_2)) {
                    /* WARNING: Does not return */
        v2 = (code *)SW_BREAK(0x21c178);
        (*v2)();
      }
      return param_5 - param_2;
    }
    v5 = rt_002534e4(param_4,param_7,param_8,param_9);
    if (v5 < 0x80) {
      if (param_6 == '\x01') {
LBL_0021c3d4:
        v3 = 0x149;
        goto LBL_0021c3dc;
      }
      v9 = 1;
    }
    else {
      if (param_6 == '\x01') goto LBL_0021c3d4;
      v10 = 3;
      if (0xffff < v5) {
        v10 = 4;
      }
      v9 = 2;
      if (0x7ff < v5) {
        v9 = v10;
      }
    }
    v14 = rt_001dff60(0,v9);
    rt_0019fe7c(v9,v14.lo,v14.hi);
    v14 = rt_001dff60(0,v9);
    rt_0019fe7c(param_5,v14.lo,v14.hi);
    v8 = param_5 - v9;
    if (SBORROW8(param_5,v9)) {
                    /* WARNING: Does not return */
      v2 = (code *)SW_BREAK(0x21c388);
      (*v2)();
    }
    v12 = -1;
    param_5 = param_2;
    v10 = param_1;
    param_1 = param_4;
    param_6 = param_3;
LBL_0021c1f4:
    v9 = rt_00252b04(param_1,param_7,param_8,param_9);
    if (v9 < v10) {
      v6 = v9 == 0;
      do {
        if (!v6) {
                    /* WARNING: Subroutine does not return */
          rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Index_out_of_range_005cd940,0x12,2,
                       s_Swift_CollectionOfOne_swift_005d0d40,0x1b,2,0x84,1);
        }
        v13 = (uint32_t)param_7;
        (*param_8)(&v11,&v13);
        v9 = 3;
        if (0xffff < v11) {
          v9 = 4;
        }
        v4 = 2;
        if (0x7ff < v11) {
          v4 = v9;
        }
        v9 = 1;
        if (0x7f < v11) {
          v9 = v4;
        }
        v6 = SCARRY8(v8,v9 * v12);
        v8 = v8 + v9 * v12;
        if (v6) {
                    /* WARNING: Does not return */
          v2 = (code *)SW_BREAK(0x21c380);
          (*v2)();
        }
        v6 = false;
      } while (1 < v10);
    }
    if (param_6 != '\x01') {
      v5 = rt_002534e4(v10,param_7,param_8,param_9);
      v7 = 3;
      if (0xffff < v5) {
        v7 = 4;
      }
      v3 = 2;
      if (0x7ff < v5) {
        v3 = v7;
      }
      v7 = 1;
      if (0x7f < v5) {
        v7 = v3;
      }
      v14 = rt_001dff60(0,v7);
      rt_0019fe7c(0,v14.lo,v14.hi);
      v14 = rt_001dff60(0,v7);
      rt_0019fe7c(param_5,v14.lo,v14.hi);
      v6 = SCARRY8(v8,param_5 * v12);
      v8 = v8 + param_5 * v12;
      if (v6) {
                    /* WARNING: Does not return */
        v2 = (code *)SW_BREAK(0x21c384);
        (*v2)();
      }
    }
    return v8;
  }
  v5 = rt_002534e4(param_1,param_7,param_8,param_9);
  if (param_3 != '\x01') {
    v10 = 3;
    if (0xffff < v5) {
      v10 = 4;
    }
    v8 = 2;
    if (0x7ff < v5) {
      v8 = v10;
    }
    v10 = 1;
    if (0x7f < v5) {
      v10 = v8;
    }
    v14 = rt_001dff60(0,v10);
    rt_0019fe7c(param_2,v14.lo,v14.hi);
    v14 = rt_001dff60(0,v10);
    rt_0019fe7c(v10,v14.lo,v14.hi);
    v8 = v10 - param_2;
    if (SBORROW8(v10,param_2)) {
                    /* WARNING: Does not return */
      v2 = (code *)SW_BREAK(0x21c334);
      (*v2)();
    }
    v12 = 1;
    v10 = param_4;
    goto LBL_0021c1f4;
  }
  v3 = 0x14f;
LBL_0021c3dc:
  v1 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
  v7 = 0x39;
LBL_0021c410:
                    /* WARNING: Subroutine does not return */
  rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v1,v7,2,s_Swift_Flatten_swift_005cf8d0,0x13,2,
               v3,1);
}



/* FUN_0021c41c @ 0x0021c41c   (est. swift_string_distance4)
 * Ghidra: long FUN_0021c41c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, uint64_t param_7, uint64_t param_8, code * param_9, uint64_t param_10)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
long FUN_0021c41c(long param_1, unsigned long param_2, char param_3, long param_4, unsigned long param_5, char param_6, uint64_t param_7, uint64_t param_8, code * param_9, uint64_t param_10){
  code *v7;
  bool v11;
  long v9;
  unsigned long v10;
  long v14;
  unsigned long v15;
  unsigned long v12;
  char *v5;
  uint64_t v13;
  uint32_t v6;
  unsigned long v8;
  long v4;
  unsigned long v1;
  long v3;
  rt16 v19;
  uint64_t v2;
  unsigned long v18;
  uint64_t v16;
  uint64_t uStack_78;
  unsigned long v17;
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
    v2 = 0xc9;
    v5 = &G_005be7c0;
    v13 = 0;
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
      v15 = v19.hi;
      v10 = v19.lo;
      v6 = v19._hi32 >> 0x1b & 1;
      if ((v15 & 0x1000000000000000) == 0) {
        v6 = 1;
      }
      if ((param_2 & 0xc) == 4L << (unsigned long)v6) {
        param_2 = rt_0001da84(param_2,v10,v15);
      }
      if ((param_5 & 0xc) == 4L << (unsigned long)v6) {
        param_5 = rt_0001da84(param_5,v10,v15);
      }
      if ((v15 >> 0x3c & 1) == 0) {
        rt_003a25d4(v15);
        return (param_5 >> 0x10) - (param_2 >> 0x10);
      }
      v12 = v10 & 0xffffffffffff;
      if ((v15 & 0x2000000000000000) != 0) {
        v12 = v15 >> 0x38 & 0xf;
      }
      if (param_2 >> 0x10 <= v12 && param_5 >> 0x10 <= v12) {
        v14 = rt_002b15d0(param_2,param_5,v10,v15);
        rt_003a25d4(v15);
        return v14;
      }
      goto LBL_0021c9cc;
    }
    v19 = rt_00253570(param_4,param_7,param_8,param_9,param_10);
    v12 = v19.hi;
    v15 = v19.lo;
    v10 = v15 & 0xffffffffffff;
    if ((v12 & 0x2000000000000000) != 0) {
      v10 = v12 >> 0x38 & 0xf;
    }
    v6 = v19._hi32 >> 0x1b & 1;
    if ((v12 & 0x1000000000000000) == 0) {
      v6 = 1;
    }
    v8 = 7;
    if (v6 == 0) {
      v8 = 0xb;
    }
    if (param_6 == '\x01') {
      v2 = 0x149;
      goto LBL_0021ca90;
    }
    v1 = v8 | v10 << 0x10;
    if ((v8 & 0xc) == 4L << (unsigned long)v6) {
      v1 = rt_0001da84(v1,v15,v12);
    }
    if ((param_5 & 0xc) == 4L << (unsigned long)v6) {
      param_5 = rt_0001da84(param_5,v15,v12);
      if ((v12 >> 0x3c & 1) == 0) goto LBL_0021c5e4;
LBL_0021c960:
      if (v10 < v1 >> 0x10 || v10 < param_5 >> 0x10) goto LBL_0021c9cc;
      v14 = rt_002b15d0(v1,param_5,v15,v12);
      rt_003a25d4(v12);
    }
    else {
      if ((v12 >> 0x3c & 1) != 0) goto LBL_0021c960;
LBL_0021c5e4:
      rt_003a25d4(v12);
      v14 = (param_5 >> 0x10) - (v1 >> 0x10);
    }
    v3 = -1;
    v4 = param_1;
    param_1 = param_4;
    v18 = param_2;
    param_6 = param_3;
  }
  else {
    v19 = rt_00253570(param_1,param_7,param_8,param_9);
    v15 = v19.hi;
    v10 = v19.lo;
    if (param_3 == '\x01') {
      v2 = 0x14f;
LBL_0021ca90:
      v5 = s_Unexpectedly_found_nil_while_unw_005cd7d0;
      v13 = 0x39;
LBL_0021cac4:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v5,v13,2,s_Swift_Flatten_swift_005cf8d0,0x13,2
                   ,v2,1);
    }
    v12 = v10 & 0xffffffffffff;
    if ((v15 & 0x2000000000000000) != 0) {
      v12 = v15 >> 0x38 & 0xf;
    }
    v6 = v19._hi32 >> 0x1b & 1;
    if ((v15 & 0x1000000000000000) == 0) {
      v6 = 1;
    }
    if (v6 == 1) {
      v8 = v12 << 0x10 | 7;
      if ((v15 >> 0x3c & 1) != 0) goto LBL_0021c680;
      v1 = 1;
    }
    else {
      v8 = v12 << 0x10 | 0xb;
LBL_0021c680:
      v1 = (v10 & 0x800000000000000) >> 0x3b;
    }
    if ((param_2 & 0xc) == 4L << v1) {
      param_2 = rt_0001da84(param_2,v10,v15);
    }
    if ((v8 & 0xc) == 4L << v6) {
      v8 = rt_0001da84(v8,v10,v15);
      if ((v15 >> 0x3c & 1) == 0) goto LBL_0021c6d0;
LBL_0021c864:
      if (v12 < param_2 >> 0x10 || v12 < v8 >> 0x10) goto LBL_0021c9cc;
      v14 = rt_002b15d0(param_2,v8,v10,v15);
      rt_003a25d4(v15);
    }
    else {
      if ((v15 >> 0x3c & 1) != 0) goto LBL_0021c864;
LBL_0021c6d0:
      rt_003a25d4(v15);
      v14 = (v8 >> 0x10) - (param_2 >> 0x10);
    }
    v3 = 1;
    v4 = param_4;
    v18 = param_5;
  }
  v9 = rt_00252b04(param_1,param_7,param_8,param_9,param_10);
  if (v9 < v4) {
    v11 = v9 == 0;
    do {
      if (!v11) {
                    /* WARNING: Subroutine does not return */
        rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_Index_out_of_range_005cd940,0x12,2,
                     s_Swift_CollectionOfOne_swift_005d0d40,0x1b,2,0x84,1);
      }
      v16 = param_7;
      uStack_78 = param_8;
      rt_0036b270(param_8);
      (*param_9)(&v17,&v16);
      rt_003a25d4(param_8);
      v15 = uStack_68;
      v10 = v17;
      if ((uStack_68 >> 0x3c & 1) == 0) {
        rt_003a25d4(uStack_68);
        v10 = v10 & 0xffffffffffff;
        if ((v15 & 0x2000000000000000) != 0) {
          v10 = v15 >> 0x38 & 0xf;
        }
      }
      else {
        v10 = rt_002b24b8(v17,uStack_68);
        rt_003a25d4(v15);
      }
      v11 = SCARRY8(v14,v10 * v3);
      v14 = v14 + v10 * v3;
      if (v11) {
                    /* WARNING: Does not return */
        v7 = (code *)SW_BREAK(0x21c8e8);
        (*v7)();
      }
      v11 = false;
    } while (1 < v4);
  }
  if (param_6 == '\x01') {
    return v14;
  }
  v19 = rt_00253570(v4,param_7,param_8,param_9,param_10);
  v15 = v19.hi;
  v10 = v19.lo;
  v6 = v19._hi32 >> 0x1b & 1;
  if ((v15 & 0x1000000000000000) == 0) {
    v6 = 1;
  }
  if ((v18 & 0xc) == 4L << v6) {
    v18 = rt_0001da84(v18,v10,v15);
  }
  if ((v15 >> 0x3c & 1) == 0) {
    rt_003a25d4(v15);
    v18 = v18 >> 0x10;
  }
  else {
    v12 = v10 & 0xffffffffffff;
    if ((v15 & 0x2000000000000000) != 0) {
      v12 = v15 >> 0x38 & 0xf;
    }
    if (v12 < v18 >> 0x10) {
LBL_0021c9cc:
                    /* WARNING: Subroutine does not return */
      rt_001afe4c(s_Fatal_error_005accd0,0xb,2,s_String_index_is_out_of_bounds_005ce6a0,0x1d,2,
                   s_Swift_StringUTF8View_swift_005d0670,0x1a,2,0xcf,1);
    }
    v18 = rt_002b15d0(0xf,v18,v10,v15);
    rt_003a25d4(v15);
  }
  if (SCARRY8(v14,v18 * v3)) {
                    /* WARNING: Does not return */
    v7 = (code *)SW_BREAK(0x21c940);
    (*v7)();
  }
  return v14 + v18 * v3;
}



/* FUN_0021cad0 @ 0x0021cad0   (est. swift_string_build)
 * Ghidra: void FUN_0021cad0(uint64_t param_1, uint64_t param_2, long param_3, long param_4, uint64_t param_5)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021cad0(uint64_t param_1, uint64_t param_2, long param_3, long param_4, uint64_t param_5){
  uint8_t stack_base[512];
  uint8_t *stack_ptr = stack_base;

  uint64_t *v9;
  uint8_t v69;
  bool v13;
  long v11;
  uint64_t v12;
  unsigned long v10;
  uint64_t v16;
  unsigned long v14;
  long v15;
  code *v8;
  long v5;
  uint64_t v59;
  long v61;
  long v50;
  long v23;
  long v35;
  long v49;
  code *v37;
  code *v51;
  code *v44;
  code *v39;
  code *v34;
  code *v27;
  code *v33;
  code *v56;
  code *v24;
  code *v41;
  code *v53;
  code *v25;
  long v40;
  code *v42;
  code *v22;
  code *v30;
  unsigned long v28;
  code *v54;
  code *v43;
  code *v36;
  code *v32;
  code *v47;
  long v52;
  code *v21;
  code *v48;
  code *v60;
  code *v45;
  code *v55;
  code *v38;
  code *v26;
  code *v46;
  code *v29;
  code *v31;
  code *v57;
  code *v19;
  long v58;
  long v20;
  long v18;
  uint64_t v17;
  uint64_t v62;
  long v63;
  code *v1;
  uint64_t v6;
  code *v3;
  code *v4;
  code *v2;
  long v66;
  long v65;
  uint64_t v64;
  rt16 v76;
  long v67;
  uint64_t v74;
  long v75;
  uint64_t v72;
  uint64_t v70;
  long v7;
  uint64_t v68;
  long v73;
  uint64_t v71;
  uint8_t v78 [16];
  uint8_t v77 [16];
  uint8_t v79 [8];
  
  rt_0008e518();
  rt_00359de8();
  v6 = *(uint64_t *)(param_3 + 0x10);
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
  v11 = rt_00377824(v76.lo,v76.hi,v6).lo;
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v50 + 0x40));
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
  v12 = rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v23 + 0x40));
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
  (*G_00658c00)(*(uint64_t *)(v35 + 0x40));
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
  (*G_00658c00)(*(uint64_t *)(v49 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034aea8();
  (*G_00658c00)();
  rt_0034b758();
  rt_00352c4c();
  v10 = rt_001b9040();
  if ((v10 & 1) != 0) {
    rt_003512d8();
    rt_00100efc();
    (*v60)();
    rt_000277b8(param_4);
    v16 = rt_0034f644();
    (*v45)(v16,param_4);
    rt_00310cd4(param_4);
    rt_0034b8cc();
    rt_00351b78();
    (*v37)();
    rt_003553d8();
    v1 = *(code **)(v63 + 8);
    rt_003510dc();
    (*v1)();
    rt_0035145c();
    (*v1)();
  }
  rt_0034c3c4();
  rt_000b4390();
  v16 = rt_00377bec().lo;
  rt_00349fe0();
  rt_0034dad8(v63,v65);
  v14 = (*v51)();
  if ((v14 & 1) == 0) {
    rt_00356060();
    v1 = *(code **)(v63 + 0x10);
    v9 = (uint64_t *)(v58 + 0x10);
    if ((v10 & 1) == 0) {
      (*v1)(v72,v63,v66);
      (*v1)(v71,v65,v66);
      rt_00352ecc(param_4);
      rt_00356864();
      rt_00351b78();
      v76 = rt16_mklo((*v56)());
      v3 = (code *)*v9;
      (*v3)(v67,v76.hi,v11);
      rt_00351cac();
      (*v76.lo)();
      rt_00359f28();
      rt_00352698(sp0x);
      (*v19)();
      v1 = (code *)((long)&__thread_bss_magic + 1);
      v76 = rt_0035172c();
      rt_00350884(v76.lo,v76.hi,v62);
      if ((bool)v69) {
        v12 = 0x14f;
        goto LBL_0021d674;
      }
      rt_00351750(param_5);
      rt_003524e0(sp0x);
      rt_00350c2c();
      (*v38)();
      rt_0035647c(param_5);
      rt_00350524();
      rt_00352d40();
      v15 = (*v24)();
      v7 = 1;
      v75 = v67;
    }
    else {
      (*v1)(v72,v65,v66);
      (*v1)(v71,v63,v66);
      rt_00352ecc(param_4);
      v76 = rt_00356864();
      v76 = rt16_mklo((*v39)(v76.lo,v76.hi,v6));
      v1 = v76.lo;
      v3 = (code *)*v9;
      (*v3)(v75,v76.hi,v11);
      rt_00351cac();
      (*v1)();
      rt_00351750(param_5);
      rt_003524e0(sp0x);
      rt_00350c2c();
      (*v55)();
      rt_00359f28();
      (*v57)(v70);
      v76 = rt_00351d24();
      rt_00350884(v76.lo,v76.hi,v62);
      if ((bool)v69) {
        v12 = 0x149;
LBL_0021d674:
        rt_003489dc(v12);
        rt_0034a2f8();
                    /* WARNING: Subroutine does not return */
        rt_001afe4c();
      }
      rt_00310cd4(param_5);
      rt_0035012c();
      rt_00352d40();
      v15 = (*v34)();
      v7 = -1;
    }
    v4 = (code *)(v18 + 8);
    v2 = *(code **)v4;
    (*v2)(v1,v62);
    rt_00353930(v58);
    rt_003508a8();
    (*v46)();
    rt_0007c1c4();
    (*v2)();
    rt_003520b4(v77);
    rt_00353d94();
    rt_003519b4(sp0x);
    rt_00077894(v72);
    (*v29)();
    rt_00354570(*(uint64_t *)(v63 + 8),v72,v66);
    (*v41)();
    rt_003568e8();
    rt_0035044c();
    rt_00359518(v75);
    rt_0035053c();
    v10 = (*v53)();
    v5 = v75;
    if ((v10 & 1) != 0) {
      v1 = (code *)rt_000277e8(v11);
      v8 = (code *)rt_00027788(param_5);
      v4 = (code *)rt_00027818(v11);
      do {
        rt_00351b78(v78,v75);
        v76 = rt16_mklo((*v1)());
        (*v3)(v9,v73,v76.hi,v11);
        rt_0034c3b4();
        (*v76.lo)();
        v5 = (*v8)(v11,param_5);
        rt_003530f4();
        (*v26)();
        v13 = SCARRY8(v15,v5 * v7);
        v15 = v15 + v5 * v7;
        v69 = v15 == 0;
        if (v13) {
                    /* WARNING: Does not return */
          v1 = (code *)SW_BREAK(0x21d658);
          (*v1)();
        }
        rt_00077894(v75);
        (*v4)();
        v76 = rt_00359518(v75);
        v10 = (*v53)(v76.lo,v76.hi,v64,v16);
        v5 = v11;
      } while ((v10 & 1) != 0);
    }
    rt_00350bc0(sp0x);
    rt_003512c0();
    (*v25)();
    v16 = rt_00353e38();
    v76 = rt_00352698(sp0x,v16,v5 + *(int *)(v40 + 0x2c));
    rt_00353bac(v76.lo,v76.hi,v12);
    (*v42)();
    rt_0035172c();
    rt_00350884();
    if ((bool)v69) {
      rt_00352bbc(v5,v66);
      (*v22)();
      rt_00350524(*(uint64_t *)(v20 + 8));
      (*v30)();
    }
    else {
      rt_00355430();
      rt_00354ac8(v28 & 0xffffffffffff | 0x4f8000000000000);
      rt_0035748c(sp0x);
      (*v54)(v74,v4,v62);
      rt_00352ecc(v11);
      v76 = rt16_mklo((*v43)(v78,v5,v6,v11));
      (*v3)(v9,v73,v76.hi,v11);
      rt_00351cac();
      (*v76.lo)();
      rt_00352bbc(v5,v66);
      (*v36)();
      rt_00354780();
      rt_0035156c();
      rt_00352098(sp0x);
      rt_00350c2c();
      (*v31)();
      rt_00310cd4(v63);
      rt_000dbdf4();
      rt_00350998();
      v11 = (*v32)();
      rt_000e15d8();
      (*v2)();
      rt_0006b6f4();
      (*v26)();
      rt_00351274();
      (*v2)();
      if (SCARRY8(v15,v11 * v7)) {
                    /* WARNING: Does not return */
        v1 = (code *)SW_BREAK(0x21d56c);
        (*v1)();
      }
    }
  }
  else {
    v1 = *(code **)(v20 + 0x10);
    (*v1)(v68,v63 + *(int *)(v66 + 0x2c),v12);
    v76 = rt_00352888();
    rt_00350884(v76.lo,v76.hi,v62);
    if ((bool)v69) {
      rt_00350944(*(uint64_t *)(v20 + 8));
      (*v44)();
    }
    else {
      v16 = rt_0035463c();
      v3 = *(code **)(param_4 + 0x20);
      rt_00356278(v16,v68);
      v16 = (*v3)();
      v76 = rt_00352d64(v79,v16,v65 + *(int *)(v66 + 0x2c));
      (*v1)(v76.lo,v76.hi,v12);
      rt_0034e1b0(v66);
      if ((bool)v69) {
        rt_00350bc0(sp0x);
        rt_003508f0();
        (*v27)();
        rt_0035a4f8();
        rt_00351324();
        (*v33)();
      }
      else {
        v76 = rt_003505e8();
        (*v3)(v76.lo,v76.hi,v62);
        rt_00352ecc(param_4);
        v1 = (code *)(*v47)(v78,v63,v6,param_4);
        rt_00352134();
        (**(code **)(v52 + 0x10))(v73,v59,v11);
        rt_00351cac();
        (*v1)();
        rt_00310cd4(param_5);
        rt_0034ce68();
        rt_00353a18();
        (*v21)();
        rt_00350af4(*(uint64_t *)(param_4 + 8));
        (*v48)();
        rt_003573c0();
        v1 = *(code **)(v73 + 8);
        rt_000a6e14();
        (*v1)();
        rt_003508f0();
        (*v1)();
      }
    }
  }
  v12 = rt_0035a3d0();
  rt_0008e500(v12,v17);
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
  bool v4;
  uint64_t v2;
  uint64_t v16;
  uint64_t v19;
  uint64_t v20;
  long v15;
  uint64_t v11;
  code *v1;
  code *v8;
  code *v7;
  code *v14;
  code *v12;
  code *v10;
  code *v9;
  long v13;
  long v5;
  long v6;
  long v17;
  long v3;
  uint64_t v18;
  rt16 v23;
  uint64_t v21;
  uint64_t v22;
  
  rt_0008e518();
  rt_0034c2e8();
  v23 = rt_0035113c();
  rt_0031be78(v23.lo,v23.hi,v19,v20);
  rt_00348d7c();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aee4();
  rt_00349748();
  v2 = rt_00377824().lo;
  rt_000a6f88(v2,v2);
  (*G_00658c00)(*(uint64_t *)(v15 + 0x40));
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
  (*v14)();
  v3 = v17 >> 0x3f;
  if (v3 < 0) {
    rt_003512d8();
    rt_003507e0(v11);
    (*v12)();
    rt_003506e8();
    rt_003507e0(v21);
    (*v10)();
    rt_003192d8();
    rt_003548e8();
    rt_003513c0(v11,v3);
    (*v9)();
    v1 = *(code **)(v5 + 8);
    (*v1)(v21,v16);
    (*v1)(v11,v16);
    (**(code **)(v6 + 8))(v22,v2);
    v4 = SBORROW8(0,v17);
    v17 = -v17;
    if (v4) {
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
    if (v3 < 0) {
      ((code)FUN_00219fcc)();
    }
    else {
      ((code)FUN_00219a00)();
    }
    rt_000dbd0c(*(uint64_t *)(v13 + 8));
    (*v8)();
    rt_00351360(*(uint64_t *)(v13 + 0x20));
    (*v7)();
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
  uint64_t v3;
  unsigned long v2;
  long v16;
  uint64_t v12;
  uint64_t v18;
  long v11;
  long v7;
  code *v6;
  code *v8;
  code *v17;
  code *v13;
  code *v10;
  code *v9;
  long v15;
  long v14;
  long v5;
  code *v1;
  long v4;
  uint64_t v19;
  uint64_t v21;
  uint64_t v22;
  uint64_t v20;
  
  rt_0008e518();
  rt_00349748();
  rt_00350b48();
  v3 = rt_00377824().lo;
  rt_000a6f88(v3,v3);
  (*G_00658c00)(*(uint64_t *)(v11 + 0x40));
  rt_003493c4();
  rt_0034c2f8();
  (*G_00658c00)();
  rt_0034aa28();
  rt_00310d68(0);
  v3 = rt_000a6f88();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b708();
  rt_0034d3e4();
  rt_0031be78();
  rt_00348cd0();
  (*G_00658c00)(*(uint64_t *)(v7 + 0x40));
  rt_00348a34();
  (*G_00658c00)();
  rt_0034c2c8();
  rt_003507e0();
  (*v17)();
  if (v16 >> 0x3f < 0) {
    rt_00351750(param_5);
    rt_00350470(v20);
    (*v13)();
    rt_0035156c(param_5);
    rt_00350470(v22);
    (*v10)();
    rt_003192d8(param_5);
    rt_00351bd4(v21,v20);
    rt_00351978();
    (*v9)();
    v1 = *(code **)(v14 + 8);
    (*v1)(v22,v12);
    (*v1)(v20,v12);
    (**(code **)(v5 + 8))(v21,v3);
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
      v1 = *(code **)(v15 + 0x20);
      goto LBL_0021dde4;
    }
  }
  do {
    rt_00352d40(param_6,param_3);
    v2 = ((code)FUN_002187e0)();
    if ((v2 & 1) != 0) {
      rt_003510ac(*(uint64_t *)(v15 + 8));
      (*v8)();
      v3 = 1;
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
    rt_003510ac(*(uint64_t *)(v15 + 8));
    (*v6)();
    v1 = *(code **)(v15 + 0x20);
    rt_00351324();
    (*v1)();
    v4 = v4 + -1;
  } while (v4 != 0);
LBL_0021dde4:
  rt_0034ee18(v15 + 0x20U & 0xffffffffffff | 0x48d8000000000000);
  (*v1)();
  v3 = 0;
LBL_0021de10:
  rt_000839d8(v18,v3,1);
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
  uint64_t v3;
  uint64_t v2;
  code *v1;
  uint64_t v13;
  code *v10;
  code *v9;
  code *v8;
  code *v12;
  long v11;
  long v5;
  long v7;
  long v6;
  long v14;
  uint64_t v4;
  uint64_t v15;
  rt16 v17;
  
  rt_0008e518();
  v3 = rt_00350b54().lo;
  rt_00350bd8(param_3);
  v4 = *(uint64_t *)(v14 + 0x10);
  v17 = rt_00349b14();
  v4 = rt_00377824(v17.lo,v17.hi,v4).lo;
  rt_0034a944();
  rt_0035136c();
  v2 = rt_00377824().lo;
  rt_00310d68(0,v2);
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
  v2 = rt_00351b84();
  rt_003515fc(v2,v3);
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
    (*v9)();
    rt_00351a50();
    v17 = rt_00348b94(param_4);
    rt_00377824(v17.lo,v17.hi,v4);
    rt_00349530();
    (**(code **)(v7 + 0x10))(v13);
    rt_0034cfa4();
    (*(code *)((long)&__thread_bss_magic + 1))();
    rt_00350b3c(*(uint64_t *)(v5 + 8));
    (*v8)();
    rt_0034b3c8();
    (**(code **)(v6 + 8))();
    rt_0008e500(v15);
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

  long v7;
  code *v9;
  uint64_t v10;
  uint64_t v6;
  long v2;
  code *v1;
  code *v3;
  long v4;
  long v5;
  uint64_t v8;
  rt16 v11;
  
  rt_0008e518();
  rt_0035215c();
  (*v9)(0xff,*(uint64_t *)(v7 + 0x10));
  v11 = rt_00352efc();
  rt_00310e08(v11.lo,v11.hi,v10);
  rt_00348e60();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  rt_003494e8();
  (*G_00658c00)(*(uint64_t *)(v2 + 0x40));
  rt_0034a1f8();
  rt_00350494(*(uint64_t *)(v4 + 0x10));
  (*v1)();
  v11 = rt_00350c38(*(uint64_t *)(v5 + 0x10));
  v11 = rt16_mklo((*v3)(v11.lo,v11.hi,v10));
  rt_00354648(v11.lo,v11.hi,sp0x);
  rt_00376820();
  rt_00351298(v6);
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
  long v2;
  uint64_t v1;
  
  v2 = rt_0036a908(0x28,0xec1e);
  *param_1 = v2;
  v1 = FUN_0021e420(v2,param_2,param_3,*(uint64_t *)((param_4 & 0xfffffffffffffffe) - 8),
                       *(uint64_t *)((param_4 & 0xfffffffffffffffe) - 0x10));
  *(uint64_t *)(v2 + 0x20) = v1;
  return &G_003471a4;
}



/* FUN_0021e420 @ 0x0021e420   (est. swift_box_init2)
 * Ghidra: rt16 FUN_0021e420(long * param_1, uint64_t param_2, long param_3, uint64_t param_4, uint64_t param_5)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
rt16 FUN_0021e420(long * param_1, uint64_t param_2, long param_3, uint64_t param_4, uint64_t param_5){
  uint64_t v2;
  uint64_t v1;
  long v3;
  rt16 v4;
  
  v2 = rt_00027754(param_5);
  v1 = rt_00027754(param_4);
  v1 = rt_00377824(0xff,v1,*(uint64_t *)(param_3 + 0x10),&G_00611b24,&LBL_00611b34).lo;
  v3 = rt_00377824(0,v2,v1,&G_00611b24,&LBL_00611b34).lo;
  *param_1 = v3;
  v3 = *(long *)(v3 + -8);
  param_1[1] = v3;
  v3 = rt_0036a908(*(uint64_t *)(v3 + 0x40),0x6db8);
  param_1[2] = v3;
  FUN_0021dfcc(v3,param_2,param_3,param_4,param_5);
  v4.hi = v3;
  v4.lo = (uint64_t)&G_003471a8;
  return v4;
}



/* FUN_0021e548 @ 0x0021e548   (est. swift_init_dispatch3)
 * Ghidra: void FUN_0021e548( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e548( void){
  long v2;
  long v1;
  
  rt_0035a6f4();
  rt_0031be78(0xff,*(uint64_t *)(v2 + 0x10),*(uint64_t *)(v1 + -8),
               *(uint64_t *)(v1 + -0x10));
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
  uint64_t v2;
  uint64_t v1;
  
  v1 = *(uint64_t *)((param_5 & 0xfffffffffffffffe) - 0x10);
  v2 = rt_00027754(*(uint64_t *)((param_5 & 0xfffffffffffffffe) - 8));
  v1 = rt_00027754(v1);
  FUN_0021d7a0(param_1,param_2,param_3,param_4,v2,v1);
  return;
}



/* FUN_0021e75c @ 0x0021e75c   (est. swift_arg_unwrap7)
 * Ghidra: void FUN_0021e75c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, unsigned long param_6)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e75c(uint64_t param_1, uint64_t param_2, uint64_t param_3, uint64_t param_4, uint64_t param_5, unsigned long param_6){
  uint64_t v2;
  uint64_t v1;
  
  v1 = *(uint64_t *)((param_6 & 0xfffffffffffffffe) - 0x10);
  v2 = rt_00027754(*(uint64_t *)((param_6 & 0xfffffffffffffffe) - 8));
  v1 = rt_00027754(v1);
  FUN_0021db04(param_1,param_2,param_3,param_4,param_5,v2,v1);
  return;
}



/* FUN_0021e7dc @ 0x0021e7dc   (est. swift_arg_unwrap5)
 * Ghidra: void FUN_0021e7dc(uint64_t param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021e7dc(uint64_t param_1, uint64_t param_2, uint64_t param_3, unsigned long param_4){
  uint64_t v2;
  uint64_t v1;
  
  v1 = *(uint64_t *)((param_4 & 0xfffffffffffffffe) - 0x10);
  v2 = rt_00027754(*(uint64_t *)((param_4 & 0xfffffffffffffffe) - 8));
  v1 = rt_00027754(v1);
  FUN_0021cad0(param_1,param_2,param_3,v2,v1);
  return;
}



/* FUN_0021e844 @ 0x0021e844   (est. swift_int_to_grade)
 * Ghidra: uint32_t FUN_0021e844(long param_1)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021e844(long param_1){
  uint32_t v2;
  uint32_t v1;
  
  v1 = 1;
  if (param_1 != 1) {
    v1 = 2;
  }
  v2 = 0;
  if (param_1 != 0) {
    v2 = v1;
  }
  return v2;
}



/* FUN_0021e874 @ 0x0021e874   (est. swift_char_equal)
 * Ghidra: bool FUN_0021e874(uint8_t * param_1, uint8_t * param_2)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: high
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
bool FUN_0021e874(uint8_t * param_1, uint8_t * param_2){
  uint8_t v1;
  long v2;
  long v3;
  
  v1 = *param_2;
  v2 = rt_00149368(*param_1);
  v3 = rt_00149368(v1);
  return v2 == v3;
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
  uint32_t v2;
  uint64_t v1;
  uint64_t v4;
  code *v3;
  
  rt_0034a74c();
  v1 = rt_0031bef0(v4);
  rt_0034b778(v1);
  v2 = (*v3)();
  return v2 & 1;
}



/* FUN_0021ea44 @ 0x0021ea44   (est. swift_check_flag6)
 * Ghidra: uint32_t FUN_0021ea44( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021ea44( void){
  uint32_t v2;
  uint64_t v1;
  uint64_t v4;
  code *v3;
  
  rt_0034a74c();
  v1 = rt_0031bf20(v4);
  rt_0034b778(v1);
  v2 = (*v3)();
  return v2 & 1;
}



/* FUN_0021ea88 @ 0x0021ea88   (est. swift_init_dispatch4)
 * Ghidra: void FUN_0021ea88( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021ea88( void){
  uint64_t v1;
  uint64_t v8;
  long v7;
  code *v3;
  code *v6;
  code *v4;
  code *v2;
  long v5;
  uint64_t v9;
  
  rt_0008e518();
  rt_00351a38();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v7 + 0x40));
  rt_00348f38();
  rt_0008f6f4(v8);
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
  (*v6)();
  rt_0034d558();
  rt_0034d810();
  (*v4)();
  rt_0031bf50();
  rt_0035133c();
  rt_003507e0();
  (*v2)();
  rt_003514e8(*(uint64_t *)(v5 + 8));
  (*v3)();
  rt_0008e500(v9);
  return;
}



/* FUN_0021ebbc @ 0x0021ebbc   (est. swift_dispatch18)
 * Ghidra: void FUN_0021ebbc( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021ebbc( void){
  uint64_t v2;
  uint64_t v1;
  uint64_t v5;
  code *v3;
  long v4;
  
  v2 = rt_00350b54().lo;
  rt_0034ece8();
  (**(code **)(v4 + 0x10))(v5);
  v1 = rt_0031bf80();
  rt_003504a0(v1,v2);
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
  unsigned long v1;
  float v2;
  
  v2 = param_2._lo16;
  v1 = param_1;
  if (v2 < (float)param_1) {
    if ((((uint32_t)(float)v2 ^ 0xffffffff) & 0x7c00) != 0) {
      return param_2.lo;
    }
    v1 = (unsigned long)(uint16_t)v2;
    if (((uint32_t)(float)v2 & 0x3ff) != 0) {
      v1 = param_1 & 0xffff;
    }
  }
  return v1;
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
  unsigned long v1;
  float v2;
  
  v2 = param_2._lo16;
  v1 = param_1;
  if ((float)param_1 <= v2) {
    if ((((uint32_t)(float)v2 ^ 0xffffffff) & 0x7c00) != 0) {
      return param_2.lo;
    }
    v1 = (unsigned long)(uint16_t)v2;
    if (((uint32_t)(float)v2 & 0x3ff) != 0) {
      v1 = param_1 & 0xffff;
    }
  }
  return v1;
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
  uint64_t v2;
  unsigned long v1;
  uint64_t v6;
  code *v7;
  code *v5;
  code *v3;
  long v4;
  
  rt_00084220();
  v2 = v6;
  rt_003515f0();
  rt_0008f6c0(v2);
  rt_00351bec();
  v2 = (*v7)();
  rt_0008e388(v2);
  rt_00350ac4();
  v1 = (*v5)();
  if ((v1 & 1) == 0) {
    rt_0031c0d0(v6);
    v2 = rt_0034bfa4();
    (*v3)(v2,v6);
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
  unsigned long v1;
  float v2;
  
  v2 = param_2._lo16;
  v1 = param_1;
  if (ABS(v2) < ABS((float)param_1)) {
    if ((((uint32_t)(float)v2 ^ 0xffffffff) & 0x7c00) != 0) {
      return param_2.lo;
    }
    v1 = (unsigned long)(uint16_t)v2;
    if (((uint32_t)(float)v2 & 0x3ff) != 0) {
      v1 = param_1 & 0xffff;
    }
  }
  return v1;
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
  unsigned long v1;
  float v2;
  
  v2 = param_2._lo16;
  v1 = param_1;
  if (ABS((float)param_1) <= ABS(v2)) {
    if ((((uint32_t)(float)v2 ^ 0xffffffff) & 0x7c00) != 0) {
      return param_2.lo;
    }
    v1 = (unsigned long)(uint16_t)v2;
    if (((uint32_t)(float)v2 & 0x3ff) != 0) {
      v1 = param_1 & 0xffff;
    }
  }
  return v1;
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
  uint64_t v11;
  code *v12;
  uint64_t v9;
  long v5;
  code *v4;
  code *v6;
  code *v7;
  long v8;
  uint64_t v10;
  
  rt_0008e518();
  v3 = v11;
  rt_0035a2d0();
  rt_00349720();
  (*G_00658c00)(*(uint64_t *)(v5 + 0x40));
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
  rt_0008f6c0(v11);
  rt_0035125c();
  (*v12)();
  rt_0034f4f4();
  rt_0034df34();
  v2 = (*v4)();
  v1 = *(code **)(v8 + 8);
  rt_003508cc();
  (*v1)();
  rt_003509d4();
  (*v1)();
  if ((v2 & 1) == 0) {
    rt_0031c0d0(v11);
    v3 = rt_0034eee8();
    (*v6)(v3,v11);
  }
  rt_003504a0(*(uint64_t *)(v8 + 0x10),v9);
  (*v7)();
  rt_0008e500(v10);
  return;
}



/* FUN_0021f510 @ 0x0021f510   (est. swift_type_grade)
 * Ghidra: uint32_t FUN_0021f510( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
uint32_t FUN_0021f510( void){
  char v1;
  unsigned long v3;
  code *v12;
  code *v9;
  code *v7;
  code *v5;
  code *v8;
  code *v6;
  code *v10;
  code *v11;
  uint32_t v4;
  uint32_t v2;
  
  rt_0034f664();
  rt_0031c100();
  rt_0034bcf0();
  v3 = (*v12)();
  if ((v3 & 1) == 0) {
    rt_0031c0d0();
    rt_0034bcf0();
    v3 = (*v9)();
    if ((v3 & 1) == 0) {
      rt_0031c130();
      rt_0034bcf0();
      v3 = (*v7)();
      if ((v3 & 1) == 0) {
        rt_0031c160();
        rt_0034bcf0();
        v3 = (*v8)();
        if ((v3 & 1) == 0) {
          rt_0031c190();
          rt_0034bcf0();
          v3 = (*v10)();
          rt_0031c1c0();
          rt_0034bcf0();
          v1 = (*v11)();
          v2 = 4;
          if (v1 != '\x01') {
            v2 = 7;
          }
          v4 = 5;
          if (v1 != '\x01') {
            v4 = 6;
          }
          if ((v3 & 1) == 0) {
            return v4;
          }
          return v2;
        }
        rt_0031c1c0();
        rt_0034bcf0();
        v1 = (*v6)();
        v4 = 8;
        v2 = 3;
      }
      else {
        rt_0031c1c0();
        rt_0034bcf0();
        v1 = (*v5)();
        v4 = 9;
        v2 = 2;
      }
      if (v1 != '\x01') {
        v2 = v4;
      }
    }
    else {
      v2 = 1;
    }
  }
  else {
    v2 = 0;
  }
  return v2;
}



/* FUN_0021f648 @ 0x0021f648   (est. swift_init_dispatch5)
 * Ghidra: void FUN_0021f648( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_0021f648( void){
  uint64_t v3;
  uint64_t v2;
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
  v3 = rt_0008f6f4();
  rt_0031c1c0();
  v2 = rt_000dbdf4();
  v3 = (*v8)(v2,v3);
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
  rt_003515d8(v3);
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

  code *v17;
  uint8_t v244;
  uint8_t v23;
  char v25;
  uint32_t v22;
  uint32_t v21;
  uint64_t v26;
  uint64_t v24;
  uint64_t v20;
  code *v12;
  uint64_t v16;
  code *v1;
  uint64_t v15;
  uint64_t v10;
  unsigned long v14;
  code *v6;
  long v13;
  unsigned long v18;
  code *v9;
  long v19;
  code *v4;
  code *v3;
  unsigned long v11;
  code *v5;
  uint64_t v239;
  uint64_t v115;
  uint64_t v64;
  code *v66;
  code *v222;
  code *v7;
  long v241;
  long v224;
  long v36;
  uint64_t v155;
  long v223;
  long v157;
  long v116;
  long v105;
  code *v58;
  long v47;
  code *v145;
  code *v88;
  code *v132;
  code *v196;
  code *v103;
  code *v70;
  code *v81;
  code *v59;
  code *v163;
  code *v141;
  code *v42;
  code *v200;
  code *v230;
  code *v164;
  code *v154;
  code *v206;
  code *v218;
  code *v118;
  code *v139;
  code *v168;
  code *v189;
  code *v131;
  code *v135;
  code *v159;
  code *v106;
  code *v85;
  code *v127;
  code *v150;
  code *v45;
  code *v182;
  code *v43;
  code *v79;
  code *v108;
  code *v183;
  code *v215;
  code *v193;
  code *v51;
  code *v94;
  code *v205;
  code *v124;
  code *v210;
  code *v180;
  code *v37;
  code *v186;
  code *v73;
  code *v48;
  code *v173;
  code *v227;
  code *v117;
  code *v129;
  code *v212;
  code *v89;
  code *v178;
  code *v76;
  code *v148;
  code *v235;
  code *v228;
  code *v126;
  code *v120;
  code *v192;
  code *v195;
  code *v125;
  code *v62;
  code *v174;
  code *v226;
  uint64_t v188;
  code *v82;
  code *v137;
  code *v38;
  code *v87;
  code *v138;
  code *v199;
  code *v202;
  code *v95;
  code *v80;
  code *v179;
  code *v98;
  code *v107;
  code *v185;
  code *v50;
  code *v104;
  code *v96;
  long v140;
  code *v236;
  code *v52;
  code *v133;
  code *v136;
  code *v203;
  code *v162;
  code *v209;
  code *v91;
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
  code *v165;
  code *v72;
  code *v53;
  code *v144;
  code *v167;
  code *v201;
  code *v153;
  code *v97;
  code *v213;
  code *v121;
  code *v208;
  code *v90;
  code *v99;
  code *v177;
  code *v77;
  code *v83;
  code *v214;
  code *v149;
  code *v34;
  code *v122;
  code *v35;
  code *v56;
  code *v114;
  code *v119;
  code *v229;
  code *v100;
  code *v101;
  code *v160;
  code *v143;
  code *v54;
  code *v175;
  code *v198;
  code *v233;
  code *v234;
  code *v220;
  code *v112;
  code *v169;
  code *v33;
  code *v75;
  code *v231;
  code *v111;
  code *v156;
  code *v176;
  code *v67;
  code *v123;
  code *v93;
  code *v39;
  code *v151;
  code *v109;
  code *v74;
  code *v197;
  code *v41;
  code *v232;
  code *v65;
  code *v134;
  code *v92;
  code *v61;
  code *v84;
  code *v221;
  code *v161;
  code *v172;
  code *v152;
  code *v191;
  code *v128;
  code *v147;
  code *v187;
  code *v40;
  code *v78;
  code *v113;
  code *v166;
  code *v204;
  code *v158;
  code *v57;
  code *v68;
  code *v216;
  code *v49;
  code *v60;
  code *v55;
  code *v181;
  code *v44;
  code *v217;
  code *v130;
  code *v211;
  code *v219;
  code *v170;
  code *v207;
  code *v146;
  code *v86;
  code *v190;
  code *v71;
  code *v46;
  code *v110;
  code *v63;
  code *v142;
  code *v69;
  code *v194;
  code *v171;
  code *v102;
  code *v225;
  code *v184;
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
  long v28;
  code *v27;
  code *v29;
  long v30;
  long v31;
  code *v32;
  code *v2;
  code *v243;
  code *v8;
  uint64_t v242;
  rt16 av237;
  uint64_t v247;
  uint64_t v274;
  uint64_t v265;
  code *v248;
  uint64_t v264;
  uint64_t v254;
  code *v269;
  uint64_t v251;
  uint64_t v255;
  uint64_t v267;
  code *v276;
  uint8_t v305 [8];
  uint8_t v306 [8];
  uint8_t v307 [8];
  uint64_t v256;
  uint64_t v252;
  long v273;
  code *v266;
  uint64_t v253;
  code *v268;
  uint64_t v250;
  code *v262;
  uint8_t v257 [8];
  uint64_t v261;
  unsigned long v259;
  uint64_t v260;
  uint64_t v263;
  unsigned long v249;
  uint64_t v271 [2];
  uint64_t v245;
  code *v270;
  code *v275;
  uint64_t v258;
  uint64_t v272;
  code *v246;
  uint64_t v280;
  uint64_t v294;
  uint8_t v308 [8];
  uint8_t v309 [8];
  code *v287;
  uint64_t v298;
  uint64_t v277;
  uint64_t v291;
  uint8_t v278 [8];
  code *v281;
  uint64_t v302;
  uint64_t v284;
  code *v299;
  code *v292;
  long v283;
  code *v293;
  code *v303;
  code *v301;
  code *v296;
  code *v295;
  uint64_t v297;
  uint64_t v304;
  code *v290;
  code *v285;
  code *v288;
  unsigned long v279;
  code *v300;
  uint64_t v289;
  code *v286;
  code *v282;
  uint8_t v310 [8];
  
  av237 = rt_0008e518();
  v279 = av237.hi;
  v294 = av237.lo;
  v24 = param_4;
  v9 = param_6;
  rt_00349a68();
  (*G_00658c00)(*(uint64_t *)(v241 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  rt_003509a4();
  v26 = rt_00352968();
  v24 = rt_00377824(v26,v9,v24,&G_0061014c).lo;
  rt_0034e034(param_6);
  rt_00377bec();
  v302 = rt_00027754();
  v26 = rt_0008f6c0();
  rt_00351684();
  v9 = rt_0060e3fc;
  rt_00353f94();
  v272 = v239;
  rt_00352b68();
  rt_00377824();
  rt_00349c44(&v295);
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
  v262 = (code *)rt_00027754();
  rt_0034be54();
  rt_00353f94();
  rt_00354840();
  rt_00377824();
  rt_00349c44(&v263);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  v20 = rt_0034c754();
  v284 = rt_00377dcc(v20,v24);
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v224 + 0x40));
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
  v12 = (code *)rt_00377824();
  rt_0034cf74(param_5);
  rt_00377bec();
  rt_00027754();
  v20 = rt_0008f6c0();
  rt_0034fe08();
  rt_00352e78();
  rt_00377824();
  rt_00349c44(&v270);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  av237 = rt_003509a4();
  rt_00350720(av237.lo,av237.hi,0x672870);
  rt_003515b4();
  rt_003722e4();
  rt_00351f10();
  (*G_00658c00)(*(uint64_t *)(v28 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  rt_003509a4();
  rt_00358d88(param_5);
  rt_0008f6f4();
  rt_00027754();
  rt_0034fe08();
  v256 = v115;
  rt_003569e4();
  rt_00377824();
  rt_00349c44(v278);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  v258 = param_5;
  rt_00350bd8(param_5);
  rt_00377824(0,v64,param_3,&G_0060e458,&G_0060e468);
  rt_00349c44(&v262);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  rt_00351178(0xff);
  v16 = rt_00377824().lo;
  v304 = v24;
  rt_00350494();
  rt_00351238();
  rt_00377bec();
  rt_00351ad4();
  v24 = rt_0008f6c0();
  rt_0034fe08();
  v276 = v66;
  rt_00351e14();
  rt_00377824();
  rt_00349c44(&v287);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  v292 = param_6;
  rt_0035ac58(param_6);
  rt_00351ba0(0xff);
  v1 = (code *)rt_00377824();
  rt_00351354();
  rt_003513f0();
  v15 = rt_00377bec().lo;
  v300 = (code *)rt_00027754();
  v250 = rt_0008f6c0();
  rt_0034fe08();
  v287 = v222;
  rt_00352b68();
  rt_00377824();
  rt_00349c44(sp0x);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  v10 = rt_0034c754();
  rt_00377dcc(v10,v16);
  rt_00348fd8();
  v303 = v27;
  (*G_00658c00)(*(uint64_t *)(v36 + 0x40));
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
  rt_003490b8(&v300);
  v270 = v29;
  (*G_00658c00)(*(uint64_t *)(v223 + 0x40));
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
  v16 = rt_0034c754();
  rt_00377dcc(v16,v12);
  rt_003490b8(&v283);
  (*G_00658c00)(*(uint64_t *)(v157 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  rt_003509a4();
  v289 = param_3;
  rt_0007c028();
  v283 = v31;
  (*G_00658c00)(*(uint64_t *)(v116 + 0x40));
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
  v285 = v32;
  (*G_00658c00)(*(uint64_t *)(v105 + 0x40));
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
  v14 = (*v58)();
  if ((v14 & 1) == 0) {
    rt_00353734();
    v273 = v47;
    rt_0031c250(param_6);
    rt_0034eafc();
    v14 = (*v145)();
    v296 = param_6;
    v297 = param_4;
    if ((v14 & 1) == 0) {
      rt_0031c130(param_6);
      rt_0034eafc();
      v14 = (*v241_x00102)();
      if ((v14 & 1) != 0) {
        rt_0031c1c0(param_6);
        rt_0034eafc();
        v25 = (*v241_x00103)();
        rt_00357a90();
        rt_0031c340();
        if (v25 == '\x01') {
          rt_0006b6f4(v252);
          (*v240_x00131)();
          rt_00352584(&v250);
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
          (*v240_x00147)(v289,v1);
        }
        goto LBL_00222a2c;
      }
      rt_003584ec();
      v9 = (code *)rt_0031c788();
      rt_00353718();
      rt_00350738();
      (*v9)();
      rt_0031c280(param_6);
      rt_00352f48(&v256);
      rt_00350618();
      (*v240_x00135)();
      rt_00352bbc();
      rt_0034c7f0();
      (*v9)();
      v12 = *(code **)(v238 + 8);
      rt_00350b3c();
      (*v12)();
      rt_0031c2b0(param_6);
      rt_00352f48(&v252);
      rt_00351274();
      (*v240_x00136)();
      rt_0035179c(v307);
      rt_0034c7f0();
      (*v9)();
      rt_00350b3c();
      (*v12)();
      v24 = v302;
      rt_0031c2e0(v302);
      rt_00352098(&v291);
      rt_00350518();
      rt_00352e60();
      (*v240_x00137)();
      v9 = *(code **)(v273 + 8);
      rt_00350aa0();
      (*v9)();
      rt_00351714();
      (*v9)();
      rt_001679cc(v24);
      rt_00351e48(&v304);
      av237 = rt_003509bc();
      (*v240_x00138)(av237.lo,av237.hi,v24);
      rt_003509bc();
      (*v9)();
      rt_003575bc(v24);
      rt_00354134();
      rt_00351160();
      rt_00352e60();
      (*v240_x00139)();
      rt_00351714();
      (*v9)();
      rt_003509bc();
      (*v9)();
      v24 = v304;
      rt_0031c310(v304);
      rt_00351af8(&v284);
      v26 = v289;
      rt_003507c8();
      (*v240_x00140)();
      rt_00352b8c(&v282);
      v9 = (code *)rt_0031c788();
      rt_00353148();
      rt_003504c4();
      (*v9)();
      v12 = *(code **)(v283 + 8U);
      v288 = (code *)((unsigned long)(v283 + 8U) & 0xffffffffffff | 0x4f8000000000000);
      rt_000e72b0();
      (*v12)();
      rt_0031c280(v24);
      rt_00358dc4();
      rt_003507c8();
      v301 = v240_x00141;
      (*v240_x00141)();
      rt_003504c4(v265);
      (*v9)();
      rt_000e72b0();
      (*v12)();
      rt_0031c2b0(v24);
      rt_00353b04();
      rt_003507c8();
      v303 = v240_x00142;
      (*v240_x00142)();
      rt_00351ea8();
      rt_003504c4();
      v286 = v9;
      (*v9)();
      rt_00084174();
      v300 = v12;
      (*v12)();
      rt_00352698(&v301);
      rt_0031c2e0();
      rt_00351e48(v305);
      rt_003509e0();
      rt_0035130c();
      v295 = v240_x00143;
      (*v240_x00143)();
      v12 = v270 + 8;
      v1 = *(code **)v12;
      v290 = (code *)((unsigned long)v12 & 0xffffffffffff | 0x4f8000000000000);
      rt_003504f4();
      (*v1)();
      (*v1)(v265,v245);
      rt_001679cc(v26);
      rt_0035a6e8();
      av237 = rt_003507bc();
      (*v240_x00144)(av237.lo,av237.hi,v26);
      rt_003507bc();
      (*v1)();
      v9 = (code *)rt_001679fc(v26);
      rt_00352ca4(v306);
      rt_00350878(v298);
      (*v9)();
      rt_003507e0();
      (*v1)();
      rt_003515cc();
      (*v1)();
      rt_00350a4c(v26);
      (*v240_x00145)(v298,v277,v284,v302,v245,v26);
      rt_0034d324(v293,v298);
      (*v9)();
      rt_003515cc();
      (*v1)();
      rt_003504f4();
      v285 = v1;
      (*v1)();
      rt_00354abc();
      rt_0031c100();
      rt_003511fc();
      rt_00351384();
      v14 = (*v241_x00105)();
      rt_0031c1c0(v12);
      rt_0034d844();
      v11 = (*v241_x00106)();
      if ((v14 & 1) == 0) {
        rt_00352098(&v284);
        v24 = rt_00350c14();
        v279 = CONCAT44(v279._hi32,(int)v11);
        (*v301)(v24,v304);
        rt_00352c98(&v282);
        rt_0035764c();
        rt_003507c8(v251);
        (*v240_x00148)();
        rt_000e15d8();
        v9 = v300;
        v12 = v288;
        (*v300)();
        rt_00358dc4();
        rt_0034b88c();
        (*v301)();
        rt_0035a6e8();
        rt_003507c8();
        (*v286)();
        rt_000e72b0();
        (*v9)();
        rt_00352098(sp0x);
        rt_003514e8();
        rt_0035130c();
        (*v295)();
        rt_003507e0();
        v9 = v285;
        (*v285)();
        rt_003507bc();
        (*v9)();
        rt_0031c1f0(v14);
        rt_003523ac();
        v11 = v279 & 0xffffffff;
      }
      else {
        rt_00352098(&v284);
        v24 = rt_00350c14();
        (*v303)(v24,v304);
        rt_00352c98(&v282);
        rt_0035764c();
        rt_003507c8(v251);
        (*v240_x00146)();
        rt_000e15d8();
        v9 = v300;
        v12 = v288;
        (*v300)();
        rt_00358dc4();
        rt_0034b88c();
        (*v303)();
        rt_0035a6e8();
        rt_003507c8();
        (*v286)();
        rt_000e72b0();
        (*v9)();
        rt_00352098(sp0x);
        rt_003514e8();
        rt_0035130c();
        (*v295)();
        rt_003507e0();
        v9 = v285;
        (*v285)();
        rt_003507bc();
        (*v9)();
        rt_0031c1f0(v14);
        rt_003523ac();
      }
      rt_003518f4(v11,v251,v12);
      (*v240_x00149)();
    }
    else {
      rt_0031c370(param_6);
      rt_00351f7c();
      rt_00350618();
      (*v240)();
      v16 = v304;
      rt_0031c3a0(v304);
      rt_003569f0();
      rt_003508cc();
      (*v165)();
      rt_0031c370(v16);
      v286 = v1;
      rt_0035133c();
      rt_003508cc();
      v246 = v72;
      (*v72)();
      rt_00353930(v283);
      rt_00351354();
      v281 = v53;
      (*v53)();
      v5 = v300;
      rt_0035ac40(v300);
      rt_00350b78();
      (*v1)();
      rt_0035a104();
      v293 = (code *)rt_0035305c();
      rt_003509b0();
      v22 = (*v88)();
      v6 = v286;
      v299 = v1;
      if ((((uint32_t)v16 ^ v22) & 1) == 0) {
        rt_0034e140(v5);
        rt_00350b78();
        v14 = (*v103)();
        rt_0034c0b4();
        rt_003509b0();
        v13 = (*v70)();
        if (v13 <= (long)v14) {
          rt_0034d53c();
          rt_003546c0();
          rt_0035145c();
          rt_00351154();
          (*v153)();
          rt_00348c84(v5);
          rt_0034eb64(v6);
          v14 = (*v59)();
          rt_0034d2d4(v285);
          (*v97)();
          goto joined_r0x002205ec;
        }
        av237 = rt_00350494();
        (*v144)(av237.lo,av237.hi,v12);
        rt_00310a74();
        rt_0035034c();
        av237 = rt_000b4390();
        rt_00352a1c(av237.lo,av237.hi,v5);
        (*v167)();
        rt_00348c84();
        rt_00350518();
        rt_003513c0();
        (*v81)();
        rt_003580c4();
        rt_003516e4();
        (*v6)();
        rt_0035145c();
        (*v6)();
        if ((v14 & 1) == 0) goto LBL_002209d4;
LBL_002205f0:
        v20 = v304;
        rt_0031c4f0(v304);
        rt_00351038();
        v16 = v289;
        rt_003505e8();
        (*v34)();
        rt_00358624(v295,v16,v20);
        (*v122)();
        rt_0034ad00();
        rt_0035460c();
        rt_003504ac();
        rt_00351148(sp0x);
        v16 = rt_00377bec().lo;
        rt_0034bc04();
        v15 = rt_0035179c(sp0x);
        v252 = v16;
        (*v35)(v15,0x200,v155,v16);
        rt_0034e784();
        rt_00354cfc();
        rt_0035056c();
        (*v56)();
        rt_0035985c();
        rt_00350780();
        rt_00167a2c();
        rt_00351af8(&v286);
        rt_003511d8(v286);
        v250 = v20;
        (*v114)();
        v1 = *(code **)(v285 + 8);
        v14 = (unsigned long)(v285 + 8) & 0xffffffffffff | 0x4f8000000000000;
        rt_000b4390();
        (*v1)();
        rt_00350c80();
        v6 = v299;
        v20 = (*v299)();
        rt_00350c38();
        v22 = (*v293)();
        v259 = v14;
        v246 = v1;
        if ((((uint32_t)v20 ^ v22) & 1) == 0) {
          rt_00353dfc();
          rt_00310a44();
          v16 = rt_0034c414();
          v14 = (*v206)(v16,v20);
          rt_0034c368();
          v5 = v295;
          rt_00350c38();
          v11 = (*v218)();
          v1 = v301;
          v2 = v303;
          v23 = v14 == v11;
          if ((long)v14 < (long)v11) {
            rt_0034d1fc();
            av237 = rt_0035084c(v1);
            rt_00352a1c(av237.lo,av237.hi,v300);
            (*v100)();
            rt_00348c84(v243);
            rt_00350a70();
            rt_003513c0();
            (*v118)();
            rt_0034e990();
            rt_00350944();
            (*v101)();
            v8 = v268;
            v2 = v6;
            v1 = v246;
            v275 = v243;
            v6 = v303;
          }
          else {
            rt_00351e84();
            av237 = rt_00350a70();
            (*v54)(av237.lo,av237.hi,rt_0060e3fc);
            rt_00353dfc();
            rt_00350a4c();
            rt_00352bf8();
            rt_00350088();
            rt_00351c64();
            (*v175)();
            rt_00348c84(v14);
            rt_00350ea4();
            rt_0035053c();
            (*v168)();
            v20 = rt_00355884();
            v1 = v246;
            (*v246)(v20,v12);
            rt_00351f88();
            (*v1)();
            v8 = v268;
            v275 = v243;
            v6 = v303;
          }
          goto joined_r0x002209c0;
        }
        rt_00351208();
        rt_0035872c();
        v11 = (*v6)();
        rt_00310a44(v20);
        v16 = rt_0034c414();
        v14 = (*v230)(v16,v20);
        rt_0034c368();
        rt_00350c38();
        v18 = (*v164)();
        v7 = v301;
        v8 = v243;
        if ((v11 & 1) != 0) {
          v23 = v18 == v14;
          if ((long)v18 < (long)v14) {
            rt_00354088();
            rt_00351aa4();
            v5 = v295;
            rt_00351df0();
            (*v119)();
            v2 = v300;
            rt_0034d1fc();
            rt_0035404c();
            rt_00351324();
            rt_0034e494();
            (*v229)();
            rt_00348c84(v2);
            rt_0034c290();
            v14 = (*v154)();
            rt_00350630();
            (*v1)();
            v20 = rt_00356aac();
            (*v1)(v20,v12);
            v7 = v1;
LBL_00221078:
            rt_003566d8();
            v2 = v6;
            v1 = v7;
            v6 = v303;
            goto joined_r0x002209c0;
          }
          rt_00350440();
          v20 = rt_003524e0(sp0x);
          rt_00350cc4(v20,0x100);
          (*v156)();
          rt_00352d34();
          rt_00351cb8();
          rt_00355404();
          (*v176)();
          rt_00348c84(v300);
          rt_0034c290();
          v14 = (*v45)();
          rt_00350630();
          (*v1)();
          if ((v14 & 1) == 0) {
            rt_0034d1fc();
            v20 = rt_00352a64();
            rt_00352a1c(v20,v12,v300);
            (*v92)();
            rt_00348c84(v243);
            v20 = rt_0035964c(v7);
            v5 = v295;
            rt_003513c0(v20,v295);
            (*v215)();
            rt_0034e990();
            rt_003516e4();
            (*v61)();
            v275 = v243;
            goto LBL_00221078;
          }
          rt_0035084c();
          (*v1)();
          v5 = v295;
LBL_00221080:
          rt_0035145c(*(uint64_t *)(v303 + 8));
          (*v193)();
          rt_00352118(v288,v289);
          (*v51)();
          rt_003567bc();
          (*v1)();
          v9 = v296;
          v24 = rt_0031c1c0(v296);
          v24 = rt_003586f0(v24);
          (*v94)(v24,v9);
          rt_003594f4();
          if ((bool)v23) {
            rt_00100efc();
            rt_00351148(&v262);
            rt_00377bec();
            rt_0034b8ec();
            rt_0035179c(v257,0x8000000000000000);
            rt_0007c1c4();
            (*v84)();
          }
          else {
            rt_0034ad00();
            rt_00100efc();
            rt_00351148(v278);
            rt_00377bec();
            rt_00348fb4();
            rt_0035179c(&v281);
            rt_0034b9f8();
            (*v221)();
          }
          rt_0034cea8();
          rt_00353e38();
          rt_0034db18(v5);
          (*v161)();
          goto LBL_00222b90;
        }
        v23 = v14 == v18;
        v1 = v7;
        if ((long)v14 < (long)v18) {
          rt_0034d53c();
          rt_0034f394(v7,v275,v12,v300);
          (*v160)();
          rt_00348c84(v243);
          v5 = v295;
          rt_003513c0(v7,v295);
          (*v139)();
          rt_0034e990();
          rt_00350944();
          (*v143)();
          rt_003566d8();
          rt_003557d8();
          v2 = v6;
          v275 = v243;
          v6 = v303;
joined_r0x002209c0:
          v303 = v2;
          v243 = v8;
          v2 = v303;
          v8 = v275;
          v7 = v1;
          if ((v14 & 1) != 0) goto LBL_00221080;
        }
        else {
          rt_0034ad00();
          v2 = v276;
          rt_003514d0();
          rt_00351148(&v287);
          rt_00377bec();
          rt_00348fb4();
          rt_0035179c(&v298);
          rt_0034b9f8();
          (*v67)();
          rt_0034d9cc();
          rt_003530cc();
          rt_00352864();
          (*v123)();
          rt_0034a7c0();
          rt_00351ee0();
          v5 = v295;
          rt_003518b8();
          rt_003513c0();
          (*v182)();
          rt_0034e990();
          rt_00350944();
          (*v93)();
          rt_003566d8();
          if ((v14 & 1) != 0) {
            rt_00351e84();
            av237 = rt_00350a70();
            (*v39)(av237.lo,av237.hi,rt_0060e3fc);
            rt_00353dfc();
            rt_00350a4c();
            rt_00352bf8();
            av237 = rt_003508b4();
            rt_00351c64(av237.lo,av237.hi,v243);
            (*v151)();
            rt_00348c84(v14);
            rt_00350ea4();
            rt_0035053c();
            (*v43)();
            v20 = rt_00355884();
            rt_003557d8(v20,v12);
            (*v7)();
            rt_00356aac();
            v20 = rt_003566d8();
            (*v7)(v20,v12);
            v275 = v275;
            v6 = v303;
            goto joined_r0x002209c0;
          }
          rt_003557d8(v275,v12);
          (*v7)();
          v6 = v303;
        }
        v303 = v6;
        rt_00351a74();
        v20 = rt_003526b8(stack_ptr);
        rt_00350cc4(v20,0x200);
        (*v172)();
        rt_00351cb8(v290,v2);
        rt_00355404();
        (*v152)();
        rt_00351190(v243,v286);
        (*v114)();
        rt_003504ac();
        (*v7)();
        v6 = v299;
        v22 = (*v299)(v12,v300);
        rt_00350ab8();
        v21 = (*v293)();
        v1 = v9;
        if (((v22 ^ v21) & 1) != 0) {
          rt_00351208();
          rt_0035872c();
          v4 = (code *)(*v6)();
          rt_0034eff8();
          rt_003510b8();
          v5 = (code *)(*v205)();
          rt_0034e15c();
          rt_00350ab8();
          v3 = (code *)(*v124)();
          v2 = v296;
          v17 = v301;
          if (((unsigned long)v4 & 1) == 0) {
            v23 = v5 == v3;
            if ((long)v5 < (long)v3) {
              rt_0034d53c();
              rt_00355f10();
              av237 = rt_00351384();
              v7 = v300;
LBL_00221610:
              rt_0034f394(av237.lo,av237.hi,v7);
              (*v68)();
              rt_00349b64(v8);
              rt_003513c0(v4,v295);
              (*v89)();
              rt_0034e990();
              rt_0035145c();
              (*v216)();
              v1 = v290;
            }
            else {
              rt_0034ad00();
              rt_003514d0();
              rt_00351148(&v287);
              rt_00377bec();
              rt_00348fb4();
              rt_00351e48(&v298);
              rt_0034b9f8();
              (*v60)();
              rt_0034d9cc();
              v9 = v301;
              rt_0035242c();
              rt_00352864();
              (*v55)();
              rt_0034a7c0();
              rt_00352d70();
              rt_003513c0(v295,v9);
              v5 = (code *)(*v228)();
              rt_0035145c();
              (*v181)();
              v7 = v300;
              v6 = v301;
              v9 = v246;
              v4 = v246;
              if (((unsigned long)v5 & 1) == 0) goto LBL_00221f00;
              rt_00351e84();
              (*v44)(v6,v295,rt_0060e3fc);
              rt_00350a4c(v7);
              rt_0034ec1c();
              (*v217)();
              rt_00349b64(v7);
              rt_0034f4a4();
              v5 = (code *)(*v126)();
              rt_00350c38();
              (*v9)();
              rt_00350a34();
              (*v9)();
              v9 = v12;
              v12 = v243;
              v6 = v303;
            }
            goto joined_r0x00221818;
          }
          v23 = v3 == v5;
          if ((long)v3 < (long)v5) {
            rt_00351e84();
            (*v191)(v17,v295,rt_0060e3fc);
            rt_00353dfc();
            rt_00350a4c();
            rt_0034ec1c();
            (*v128)();
            rt_00349b64(v5);
            rt_0034f4a4();
            v5 = (code *)(*v210)();
            rt_00350c38();
            v9 = v246;
            (*v246)();
            rt_00350a34();
            (*v9)();
            v9 = v12;
            v12 = v243;
            v6 = v303;
            v2 = v296;
            goto joined_r0x00221818;
          }
          rt_00350440();
          v20 = rt_003524e0(sp0x);
          rt_00350cc4(v20,0x100);
          (*v158)();
          v6 = v290;
          rt_00353c18();
          rt_00351cb8();
          rt_00355404();
          (*v57)();
          rt_00355e80();
          rt_0034af04();
          rt_00310954();
          rt_0035066c();
          rt_0034eb64();
          v5 = (code *)(*v212)();
          rt_000b4390();
          v4 = v246;
          (*v246)(v259);
          v2 = v296;
          if (((unsigned long)v5 & 1) != 0) {
            rt_0034d53c();
            rt_00355f10();
            av237 = rt_00351384();
            goto LBL_00221610;
          }
LBL_00221f00:
          rt_00351384();
          (*v4)(v259);
          v9 = rt_0060e3fc;
          v6 = v303;
          v1 = v290;
LBL_00221f20:
          rt_0034ad00();
          v20 = rt_00352c98(&v275);
          rt_00351148(&v270,v20,v253);
          rt_00377bec();
          rt_00348fb4();
          rt_0034ae80();
          (*v240_x00107)();
          rt_0034d558();
          rt_00355430();
          av237 = rt_0034f4b4();
          (*v240_x00108)(av237.lo,av237.hi,v2);
          rt_00358cc8();
          (*v82)(v1,v286,v12);
          rt_0035690c(v8);
          v20 = rt_00354834();
          v285 = v12;
          rt_00351154(v20,v12,v300);
          (*v240_x00109)();
          rt_00350780(v24);
          rt_0035614c();
          rt_003519b4(v309);
          rt_003579f4();
          rt_003515fc();
          (*v240_x00110)();
          v1 = *(code **)(v6 + 8);
          rt_00350630();
          (*v1)();
          rt_00350b78();
          v12 = v293;
          v14 = (*v293)();
          v20 = v297;
          if ((v14 & 1) != 0) {
            rt_00355a40(v8);
            rt_0034e444();
            v13 = (*v5)();
            if (0x40 < v13) {
              rt_00350ab8();
              v14 = (*v12)();
              if ((v14 & 1) == 0) {
                rt_00350ab8();
                v14 = (*v12)();
                rt_0034e444();
                v13 = (*v5)();
                if ((v14 & 1) != 0) {
                  if (v13 < 0x41) {
                    rt_0034ad00();
                    rt_00351148(&v287,v276,v9);
                    rt_00377bec();
                    rt_00348fb4();
                    rt_00352098(&v298);
                    rt_0034b9f8();
                    (*v240_x00111)();
                    rt_0034d9cc();
                    rt_00353074();
                    rt_00351298(v9);
                    (*v240_x00112)();
                    rt_00348c84(v8);
                    rt_0034db78();
                    v5 = (code *)(*v87)();
                    rt_003514d0();
                    (*v1)();
                    v12 = v293;
                    if (((unsigned long)v5 & 1) == 0) goto LBL_002221d8;
                  }
                  else {
                    rt_00352944();
                    rt_00351c34(v8);
                    rt_0001df60();
                    rt_00349630();
                    rt_00353074();
                    rt_0034f394();
                    (*v5)();
                    rt_00348c84(v8);
                    rt_0034db78();
                    v5 = (code *)(*v38)();
                    rt_003514d0();
                    (*v1)();
                    v12 = v293;
                    if (((unsigned long)v5 & 1) == 0) goto LBL_002221ec;
                  }
LBL_00222140:
                  rt_003480e4();
                  goto LBL_0022228c;
                }
                v12 = v293;
                if (v13 < 0x40) goto LBL_002221d8;
              }
              else {
                rt_0034e444();
                v13 = (*v5)();
                if (v13 < 0x40) {
LBL_002221d8:
                  rt_0034d520(v8);
                  rt_00350ab8();
                  (*v138)();
                }
                else {
                  rt_00352944();
                  rt_00351c34(v8);
                  rt_0001df60();
                  rt_00349630();
                  rt_0034f394(v301);
                  (*v5)();
                  rt_00348c84(v8);
                  rt_003513c0(v255,v301);
                  (*v137)();
                  v24 = rt_0035a104();
                  (*v1)(v24,v9);
                  v254 = v255;
                  if (((unsigned long)v5 & 1) != 0) goto LBL_00222140;
                }
              }
            }
          }
LBL_002221ec:
          rt_00355a40(v8);
          rt_0034e444();
          v13 = (*v5)();
          if (v13 < 0x41) {
            rt_0034e444();
            v13 = (*v5)();
            if (v13 == 0x40) {
              rt_00350ab8();
              v14 = (*v12)();
              if ((v14 & 1) == 0) goto LBL_0022220c;
            }
          }
          else {
LBL_0022220c:
            rt_00350ab8();
            v14 = (*v12)();
            rt_0034e444();
            v13 = (*v5)();
            if ((v14 & 1) == 0) {
              if (v13 < 0x40) goto LBL_002222cc;
            }
            else if (v13 < 0x41) {
LBL_002222cc:
              rt_0034d520(v8);
              rt_00350ab8();
              (*v202)();
              goto LBL_002222e0;
            }
            rt_00354270();
            rt_00351c34(v8);
            rt_0001df60();
            rt_00349630();
            rt_00353074();
            rt_0034f394();
            (*v5)();
            rt_00348c84(v8);
            rt_0035190c();
            rt_003513c0();
            v14 = (*v199)();
            rt_003514d0();
            (*v1)();
            if ((v14 & 1) != 0) {
              rt_00347fb4();
LBL_0022228c:
              rt_003523f0();
                    /* WARNING: Subroutine does not return */
              rt_001afe4c();
            }
          }
LBL_002222e0:
          (*v1)(v295,v9);
          rt_00352118(v288,v289);
          (*v95)();
          rt_003567bc();
          rt_00352bbc();
          (*v80)();
          rt_0034d520(v8);
          rt_00350ab8();
          v12 = (code *)(*v179)();
          rt_00350944();
          (*v1)();
          rt_0035a590();
          rt_00358a08();
          v14 = v279;
          rt_00351274();
          v13 = (*v98)();
          rt_0031c788(v1);
          rt_0035441c();
          rt_003519b4();
          rt_00351274();
          v285 = v240_x00113;
          (*v240_x00113)();
          rt_0031c3d0(v302);
          rt_003511fc();
          rt_003509d4();
          v19 = (*v107)();
          rt_00350944(*(uint64_t *)(v273 + 8));
          v300 = v185;
          (*v185)();
          v9 = v296;
          v286 = v12 + -(v13 + v19);
          v288 = v12;
          rt_0031c160(v296);
          rt_00350c74();
          rt_003504f4();
          v11 = (*v50)();
          rt_0034ad00();
          rt_003520b4(&v249);
          v24 = rt_00358828();
          rt_00377bec(v24,v20,v264);
          rt_00350654();
          if ((v11 & 1) == 0) {
            av237 = rt_00350440();
            v24 = rt_0035179c(v271,av237.lo,av237.hi,v264);
            (*v240_x00117)(v24,0x100);
            rt_0034d9cc();
            rt_0034f778(v266,v264);
            (*v240_x00118)();
            v9 = v262;
            rt_00357350();
            v12 = v270;
          }
          else {
            rt_00351a74();
            v24 = rt_00351af8(v271);
            rt_003516b4(v24,0x200);
            (*v240_x00114)();
            rt_0034d9cc();
            rt_0035179c(sp0x);
            rt_0034f778(v14);
            (*v240_x00115)();
            v282 = v288;
            rt_003520b4(&v301);
            v12 = (code *)rt_0031c460();
            rt_0001df60();
            rt_0034b67c();
            (*v12)(v266,v264);
            v12 = v270;
            rt_003507c8();
            (*v240_x00116)();
            v254 = v291;
          }
          v1 = v286;
          v24 = v289;
          if ((long)v286 < 0) {
            rt_0035179c(&v304);
            (*v285)(v297,v292);
            if (SBORROW8(0,(long)v1)) {
                    /* WARNING: Does not return */
              v9 = (code *)SW_BREAK(0x223414);
              (*v9)();
            }
            v282 = (code *)-(long)v1;
            v248 = (code *)rt_0031c430(v302);
            rt_0001df60();
            rt_0034b67c();
            rt_003530cc();
            rt_00356140();
            (*v248)();
            rt_00350aa0();
            (*v300)();
            rt_0035690c(v9);
            rt_003524e0(&v260);
            rt_000dbe70(v254);
            rt_0034f1fc();
            (*v240_x00121)();
            rt_00357350();
          }
          else {
            (*v285)(v254,v297,v292);
            rt_0016796c(v9);
            rt_0035133c();
            rt_0034f1fc(v254,v284,v302);
            (*v240_x00119)();
            v282 = v1;
            v1 = (code *)rt_0031c460(v9);
            rt_0001df60();
            rt_0034b67c();
            rt_00351a2c();
            (*v1)();
            rt_00356224();
            rt_003507c8();
            (*v240_x00120)();
          }
          rt_0031c2e0(v9);
          rt_00351e48(&v288);
          rt_003508cc();
          rt_00351c94();
          (*v240_x00122)();
          v9 = *(code **)(v12 + 8);
          (*v9)(v248,v20);
          rt_003508f0();
          (*v9)();
          v9 = v266;
          goto LBL_00222690;
        }
        rt_00354d08();
        rt_003507a4();
        rt_00100efc();
        v13 = (*v180)();
        rt_0034e15c();
        rt_00350ab8();
        v19 = (*v37)();
        v23 = v13 == v19;
        if (v13 < v19) {
          rt_0034d53c();
          rt_00355f10();
          rt_0034e464();
          rt_0034f394();
          (*v147)();
          rt_00349b64(v8);
          rt_003507c8();
          rt_003513c0();
          (*v186)();
          rt_0034e990();
          rt_0035145c();
          (*v187)();
          v1 = v290;
          v5 = v6;
          v2 = v296;
        }
        else {
          rt_00351e84();
          av237 = rt_003524a4();
          (*v40)(av237.lo,av237.hi,rt_0060e3fc);
          rt_00350a4c(v6);
          rt_0034ec1c();
          (*v78)();
          rt_00349b64(v6);
          rt_003510dc();
          rt_00351220();
          v5 = (code *)(*v73)();
          rt_00350c38();
          (*v7)();
          rt_00350618();
          (*v7)();
          v9 = v12;
          v12 = v243;
          v6 = v303;
          v2 = v296;
        }
joined_r0x00221818:
        if (((unsigned long)v5 & 1) == 0) goto LBL_00221f20;
        (**(code **)(v6 + 8))(v295,v9);
        rt_00352bbc(v286,v12);
        (*v178)();
        rt_00357274();
        rt_00358a08();
        rt_00084180();
        v13 = (*v76)();
        if (v13 == 0) {
          rt_00352118(v288,v289);
          (*v241_x00109)();
          v24 = rt_0031c1c0(v2);
          rt_00350494(v24);
          (*v241_x00110)();
          rt_003594f4();
          if ((bool)v23) {
            v24 = rt_00352140();
            rt_00351148(&v262,v24,v289);
            rt_00377bec();
            rt_0034b8ec();
            rt_0035179c(v257,0x8000000000000000);
            rt_0007c1c4();
            (*v240_x00151)();
          }
          else {
            rt_0034ad00();
            rt_0035266c(&v302);
            rt_00351148(v278);
            rt_00377bec();
            rt_00348fb4();
            rt_0035179c(&v281);
            rt_0034b9f8();
            (*v240_x00152)();
          }
          rt_0034cea8();
          rt_00351a2c();
          rt_0034db18();
          (*v240_x00153)();
        }
        else {
          v24 = rt_0031c1c0(v2);
          rt_00350494(v24);
          (*v148)();
          rt_003594f4();
          if ((bool)v23) {
            rt_00352b8c(&v250);
            rt_0031bc70();
            rt_00351e48(&v267);
            rt_00358bc0();
            rt_0034db18();
            (*v49)();
            rt_003507e0();
            rt_00352118();
            (*v235)();
          }
          else {
            (**(code **)(v283 + 0x20))(v274,v288,v289);
          }
        }
        rt_003525f4();
        av237 = rt_003510a0();
        v9 = v241_x00111;
      }
      else {
        rt_00350b78();
        v6 = (code *)(*v1)();
        rt_0034e15c();
        rt_00350b78();
        v14 = (*v132)();
        rt_0034c0b4();
        rt_003509b0();
        v13 = (*v196)();
        if (((unsigned long)v6 & 1) == 0) {
          if (v13 <= (long)v14) {
            rt_0034ad00();
            rt_003516e4();
            rt_00351148(&v287);
            rt_00377bec();
            rt_00348fb4();
            rt_00352ca4(&v298);
            rt_0034b9f8();
            (*v99)();
            rt_0034c7d4();
            rt_00353074();
            rt_003516a8(v6);
            (*v177)();
            rt_0034a7c0();
            rt_00310b08();
            rt_00350164();
            rt_003513c0();
            (*v141)();
            rt_003580c4();
            rt_003514d0();
            (*v6)();
            v5 = v300;
            if ((v14 & 1) == 0) {
              rt_0035145c();
              (*v6)();
              goto LBL_002209d4;
            }
            goto LBL_0022052c;
          }
          rt_00351d0c();
          v16 = rt_00359f6c();
          (*v201)(v16,v286,v12);
          rt_0034d53c();
          av237 = rt_0034f514();
          v5 = v300;
        }
        else {
          if (v13 < (long)v14) {
LBL_0022052c:
            v5 = v300;
            rt_0034d1fc();
            rt_003546c0();
            rt_0035145c();
            rt_0034e494();
            (*v77)();
            rt_00348c84(v5);
            rt_0034eb64(v286);
            (*v42)();
            v16 = rt_0034cbc4();
            (*v83)(v16,v12);
            goto joined_r0x002205ec;
          }
          rt_0034ad00();
          v5 = v287;
          rt_00351384();
          rt_00351148(sp0x);
          rt_00377bec();
          rt_00348fb4();
          rt_00352ca4(sp0x);
          rt_0034b9f8();
          (*v213)();
          rt_0034c7d4();
          rt_003546c0();
          rt_00350b84(v6);
          (*v121)();
          rt_00352c8c();
          rt_00348c84();
          rt_00357508();
          rt_0034eb64();
          (*v163)();
          v16 = rt_0034cbc4();
          (*v208)(v16,v12);
          if ((v14 & 1) != 0) {
            rt_0035145c();
            (*v90)();
            goto LBL_002205f0;
          }
          rt_00351d0c();
          av237 = rt_00350494();
          (*v214)(av237.lo,av237.hi,v12);
          rt_0034d53c();
          av237 = rt_0034f514();
        }
        rt_0034f394(av237.lo,av237.hi,v5);
        (*v149)();
        rt_00348c84();
        rt_00350a70();
        rt_003513c0();
        (*v200)();
        rt_003580c4();
        rt_00350944();
        (*v6)();
        rt_0035145c();
        (*v6)();
joined_r0x002205ec:
        if ((v14 & 1) != 0) goto LBL_002205f0;
LBL_002209d4:
        rt_0031c310(v304);
        rt_0034df84(v288);
        (*v198)();
        rt_003519b4(&v297);
        rt_0008e388();
        rt_00358624();
        (*v233)();
        rt_00350ab8();
        v9 = v293;
        v22 = (*v293)();
        rt_00351160();
        v21 = (*v299)();
        if (((v22 ^ v21) & 1) == 0) {
          rt_0034e15c();
          rt_0034e444();
          v13 = (*v135)();
          rt_0034c368();
          rt_00351160();
          v19 = (*v159)();
          v1 = v285;
          if (v13 < v19) {
            rt_0034d1fc();
            rt_003546c0();
            rt_00350944();
            rt_0034e494();
            (*v234)();
            rt_00348c84(v5);
LBL_00220b40:
            rt_0034cf74(v9);
            v14 = (*v106)();
            rt_0034d2d4(v1);
            (*v112)();
            v9 = v296;
          }
          else {
            rt_00352bb0();
            rt_003537f0();
LBL_00220b70:
            rt_00350c08();
            (*v169)();
            rt_0034d53c();
            rt_00353074();
            av237 = rt_003504ac();
            rt_0034f394(av237.lo,av237.hi,v5);
            (*v33)();
            rt_00348c84(v243);
            rt_0034db78();
            v14 = (*v85)();
            v243 = v303 + 8;
            v9 = *(code **)v243;
            rt_003514d0();
            (*v9)();
            rt_00350944();
            (*v9)();
            v9 = v296;
          }
joined_r0x00221014:
          if ((v14 & 1) != 0) {
LBL_00220be8:
            (*v281)(v288,v289);
            rt_00350630(*(uint64_t *)(v1 + 8));
            (*v127)();
            v24 = rt_0031c1c0(v9);
            v24 = rt_003586f0(v24);
            v25 = (*v150)(v24,v9);
            rt_0031c340(v304);
            if (v25 == '\x01') {
              rt_003526b8(&v284);
              rt_003508b4();
              (*v75)();
              rt_00352584(&v250);
              rt_0031bc70();
              rt_003523ac();
              rt_00351554(v9);
              (*v231)();
              rt_0035190c();
              (*v281)();
            }
            else {
              rt_00353e38();
              rt_003508b4();
              (*v111)();
            }
            goto LBL_00222b90;
          }
        }
        else {
          rt_00350ab8();
          v9 = (code *)(*v9)();
          rt_0034e15c();
          rt_0034e444();
          v13 = (*v189)();
          rt_0034c368();
          rt_00351160();
          v19 = (*v131)();
          v1 = v285;
          if (((unsigned long)v9 & 1) != 0) {
            if (v19 < v13) {
              rt_00352bb0();
              rt_003537f0();
              goto LBL_00220b70;
            }
            rt_0034ad00();
            rt_003510dc();
            rt_00351148(&v287);
            rt_00377bec();
            rt_00348fb4();
            rt_0034ae80();
            (*v109)();
            rt_0034d558();
            rt_00353074();
            v14 = v259;
            rt_0035256c(v267);
            (*v74)();
            rt_00348c84(v243);
            rt_0034db78();
            v11 = (*v79)();
            v12 = *(code **)(v303 + 8);
            rt_003514d0();
            (*v12)();
            v9 = v296;
            if ((v11 & 1) == 0) {
              v24 = rt_0034d1fc();
              rt_00352bf8(v24,rt_0060e3fc);
              rt_0034e494(v14);
              (*v113)();
              rt_00348c84(v5);
              rt_0034cf74(rt_0060e3fc);
              v14 = (*v48)();
              rt_00353384();
              rt_00350b00();
              (*v166)();
              goto joined_r0x00221014;
            }
            rt_00350944();
            (*v12)();
            goto LBL_00220be8;
          }
          if (v13 < v19) {
            rt_0034d1fc();
            rt_003546c0();
            rt_00350944();
            rt_0034e494();
            (*v220)();
            rt_00348c84(v5);
            goto LBL_00220b40;
          }
          rt_0034ad00();
          rt_0035675c();
          rt_0035190c();
          rt_00351148(sp0x);
          rt_00377bec();
          rt_00348fb4();
          rt_00352ca4(sp0x);
          rt_0034b9f8();
          (*v197)();
          rt_0034d9cc();
          rt_00352bf8();
          rt_003514a0(v6);
          (*v41)();
          rt_0034af04(v5);
          rt_00351ee0();
          rt_003510dc();
          rt_00352b08();
          v14 = (*v108)();
          rt_00353384();
          rt_003509b0();
          (*v232)();
          v9 = v296;
          if ((v14 & 1) != 0) {
            v6 = v1 + 0x10;
            av237 = rt_00350b3c();
            (*v65)(av237.lo,av237.hi,v12);
            rt_0034d53c();
            rt_00355f10();
            av237 = rt_003509b0();
            rt_00351154(av237.lo,av237.hi,v5);
            (*v134)();
            rt_00348c84(v243);
            rt_0034f424(v259);
            v14 = (*v183)();
            v1 = v285;
            v243 = v303 + 8;
            v12 = *(code **)v243;
            (*v12)(v6,rt_0060e3fc);
            rt_00350b00();
            (*v12)();
            goto joined_r0x00221014;
          }
          rt_00353db8();
          (*v173)(v259,rt_0060e3fc);
        }
        rt_00351160();
        v12 = v299;
        v14 = (*v299)();
        if ((v14 & 1) == 0) {
          rt_00351160();
          v12 = (code *)(*v12)();
          rt_0034c368();
          rt_00351160();
          v13 = (*v117)();
          v24 = v258;
          if (((unsigned long)v12 & 1) != 0) {
            if (v13 < 0x41) {
              rt_0034ad00();
              rt_00354b68();
              rt_0035084c();
              rt_00351148(sp0x);
              rt_00377bec();
              rt_00348fb4();
              rt_00354064();
              rt_0034ae80();
              (*v130)();
              rt_0034dc20();
              rt_0035319c();
              rt_00351438();
              (*v211)();
              rt_00348c84(v5);
              rt_00355dfc();
              rt_0034eb64();
              v14 = (*v120)();
              rt_0034d2d4(v285);
              (*v219)();
              v9 = v290;
              if ((v14 & 1) == 0) goto LBL_0022189c;
              goto LBL_00221994;
            }
            v282 = (code *)0x0;
            rt_0034efdc();
            rt_0001df60();
            rt_00349630();
            rt_003546c0();
            rt_0034facc();
            (*v12)();
            rt_00348c84(v5);
            v243 = v286;
            goto LBL_00221550;
          }
          v243 = v286;
          if (v13 < 0x40) goto LBL_0022189c;
LBL_002218b8:
          rt_0034ad00();
          v16 = rt_00353dac(&v302);
          rt_00351148(v278,v16,v289);
          rt_00377bec();
          rt_0034b8ec();
          rt_00351a74();
          v16 = rt_003526b8(&v281);
          rt_0035053c(v16,0x200);
          (*v170)();
          rt_0034e74c();
          rt_003524e0(&v284);
          rt_00352b44(v9);
          (*v207)();
          rt_0035764c(v24);
          rt_00352f48(v308);
          rt_00351274();
          (*v146)();
          rt_003509e0();
          rt_00359a78();
          (*v281)();
          rt_00352584(&v246);
          rt_0035690c();
          rt_00350bb4(v243);
          rt_00351c64();
          (*v86)();
          rt_00350780(v20);
          rt_00167a2c();
          v243 = v269;
        }
        else {
          rt_0034c368();
          v243 = v286;
          rt_00351160();
          v13 = (*v227)();
          v24 = v258;
          if (v13 < 0x40) {
LBL_0022189c:
            rt_003109b4(v5);
            v16 = rt_0034c414();
            v13 = (*v192)(v16,v5);
            if (-1 < v13) goto LBL_002218b8;
          }
          else {
            v282 = (code *)0x0;
            rt_0034efdc();
            rt_0001df60();
            rt_00349630();
            rt_003546c0();
            rt_0034facc();
            (*v12)();
            rt_00348c84(v5);
LBL_00221550:
            rt_0034eb64(v243);
            v14 = (*v129)();
            rt_0034d2d4(v285);
            (*v204)();
            if ((v14 & 1) == 0) goto LBL_002218b8;
          }
LBL_00221994:
          rt_0034ad00();
          v16 = rt_00353dac(&v302);
          rt_00351148(v278,v16,v289);
          rt_00377bec();
          rt_0034b8ec();
          rt_00351a74();
          v16 = rt_003526b8(&v281);
          rt_0035053c(v16,0x200);
          (*v190)();
          rt_0034e74c();
          rt_003524e0(&v284);
          rt_00352b44(v9);
          (*v71)();
          rt_0035764c(v24);
          rt_00352f48(v308);
          rt_00351274();
          (*v46)();
          rt_003509e0();
          rt_00359a78();
          (*v281)();
          rt_0008f6f4(v15);
          rt_0031bc70();
          rt_00353f20();
          rt_0035056c();
          (*v110)();
          rt_00354364();
          rt_0035084c();
          (*v195)();
          rt_00352584(&v246);
          rt_0035690c();
          rt_00351af8(&v258);
          av237 = rt_000b4390();
          rt_00351c64(av237.lo,av237.hi,v5);
          (*v63)();
          rt_00350780(v20);
          rt_0016799c();
        }
        rt_00355430();
        rt_00350ab8();
        rt_0035053c();
        (*v142)();
        v9 = *(code **)(v30 + 8);
        rt_00351f88();
        (*v9)();
        rt_00351e90();
        (*v9)();
        rt_00358a08(v24);
        rt_00351274();
        v9 = (code *)(*v125)();
        rt_003524a4();
        (*v281)();
        rt_0035a590();
        rt_00358a08();
        v14 = v279;
        v15 = v297;
        rt_00351274();
        v295 = v62;
        v13 = (*v62)();
        rt_0031c788(v24);
        rt_0035441c();
        rt_00351af8();
        rt_00351274();
        v285 = v69;
        (*v69)();
        v20 = v302;
        rt_0031c3d0(v302);
        rt_00350c74();
        v16 = v284;
        rt_00351324();
        v301 = v174;
        v19 = (*v174)();
        rt_00353930(v273);
        v290 = v237;
        rt_003505e8();
        v300 = v194;
        (*v194)();
        v286 = v9 + (-v19 - v13);
        v288 = v9;
        rt_0031c190(v296);
        rt_003518e8();
        rt_00350618();
        v11 = (*v226)();
        rt_0034ad00();
        v264 = v272;
        rt_00350524();
        rt_00351148(&v295);
        rt_00377bec();
        rt_00350654();
        if ((v11 & 1) == 0) {
          rt_00350440();
          rt_003526b8(&v279);
          rt_00350578();
          (*v225)();
          rt_0034c384();
          rt_00351e48(&v294);
          rt_0034c674(v14);
          (*v184)();
          v24 = v260;
          v9 = v300;
        }
        else {
          rt_00351a74();
          v10 = rt_003519b4(&v279);
          rt_00352a4c(v10,0x200);
          (*v171)();
          rt_0034c384();
          rt_00352e30();
          rt_0034c674();
          (*v102)();
          rt_00350630();
          v13 = (*v295)();
          rt_00355640();
          (*v285)(v15,v24);
          rt_00351324();
          v19 = (*v301)();
          rt_0035060c();
          v9 = v300;
          (*v300)();
          v282 = (code *)(v19 + v13);
          v12 = (code *)rt_0031c460(v20);
          rt_0001df60();
          rt_0034b67c();
          rt_00351e48(&v294);
          (*v12)(v243);
          rt_003505e8();
          (*v9)();
          v24 = v188;
        }
        v12 = v262;
        rt_00357350();
        v1 = v286;
        if ((long)v286 < 0) {
          rt_003524e0(&v291);
          v15 = rt_003586f0();
          (*v240_x00104)(v15,v292);
          rt_0031c400(v20);
          v15 = rt_0034f654();
          rt_00354840(v15,v16);
          (*v240_x00105)();
          rt_0009461c();
          (*v9)();
          rt_00351714();
          (*v9)();
          if (SBORROW8(0,(long)v1)) {
                    /* WARNING: Does not return */
            v9 = (code *)SW_BREAK(0x223410);
            (*v9)();
          }
          v282 = (code *)-(long)v1;
          v1 = (code *)rt_0031c430(v20);
          rt_0001df60();
          rt_0034b67c();
          rt_003526b8(stack_ptr);
          (*v1)(v24);
          rt_003512c0();
          (*v9)();
          rt_0035690c(v12);
          rt_00351e48(&v288);
          av237 = rt_000b43d0();
          rt_00352d88(av237.lo,av237.hi,v20);
          (*v240_x00106)();
          v12 = v270;
          v24 = v289;
        }
        else {
          (*v240_x00100)(v24,v297,v292);
          rt_0031c400(v20);
          rt_0035441c();
          rt_003524e0();
          rt_000dbd0c();
          rt_00354840();
          (*v240_x00101)();
          rt_003512c0();
          (*v9)();
          rt_00351714();
          (*v9)();
          rt_0035690c(v12);
          rt_00353148();
          av237 = rt_0009461c();
          rt_00352d88(av237.lo,av237.hi,v20);
          (*v240_x00102)();
          v282 = v286;
          v1 = (code *)rt_0031c460(v12);
          rt_0001df60();
          rt_0034b67c();
          rt_00351e48(&v288);
          (*v1)(v298);
          rt_00351af8(&v289);
          rt_003507c8();
          (*v240_x00103)();
          v264 = v298;
          v24 = v289;
        }
LBL_00222690:
        v1 = v296;
        rt_0031c1c0(v296);
        rt_003514ac();
        v20 = v297;
        rt_003507e0();
        v285 = v104;
        v16 = (*v104)();
        rt_00352474();
        rt_0034fe80();
        (*v240_x00123)();
        rt_00355100(&v282);
        rt_0031c1f0();
        rt_003526b8(&v285);
        rt_00352a1c(v16,v280,v264);
        (*v240_x00124)();
        rt_0035a590();
        rt_0031c640();
        rt_003514ac();
        rt_00084174();
        v13 = (*v96)();
        if (v13 <= (long)v288) {
          rt_000dbd0c(*(uint64_t *)(v12 + 8));
          (*v136)();
          v26 = rt_003525f4();
          (*v203)(v26,v1,v24);
          goto LBL_00222a2c;
        }
        rt_0034ad00();
        v16 = rt_00352584(v310);
        v24 = v284;
        v1 = (code *)rt_00377bec(v16,v284,v261);
        v6 = (code *)rt_0008f728();
        rt_00351a74();
        v16 = rt_00351af8(&v279);
        rt_0034df74(v16,0x200);
        (*v6)();
        v5 = (code *)rt_0008f758(v20);
        rt_003519b4(sp0x);
        rt_00351298(v12);
        (*v5)();
        v23 = (code *)-(long)v286 == (code *)0x0;
        if (SBORROW8(0,(long)v286)) {
                    /* WARNING: Does not return */
          v9 = (code *)SW_BREAK(0x22330c);
          (*v9)();
        }
        v288 = v5;
        v282 = (code *)-(long)v286;
        v5 = (code *)rt_0031c460(v302);
        v286 = v6;
        rt_0001df60();
        rt_0034b67c();
        rt_0035a718();
        (*v5)(v9);
        rt_00353734();
        v295 = (code *)(v140 + 8U & 0xffffffffffff | 0x4f8000000000000);
        rt_00350944();
        v6 = v300;
        (*v300)();
        rt_0031c788(v264);
        rt_0035102c();
        v20 = rt_003586f0();
        (*v240_x00125)(v20,v264);
        rt_00351a74();
        rt_0035a540();
        rt_0034df74();
        (*v286)();
        v290 = v1;
        rt_00352098(&v291);
        rt_0035256c(v12);
        (*v288)();
        rt_00352894(v26);
        rt_0035614c();
        rt_003524e0(&v304);
        v26 = v263;
        rt_00350630();
        rt_00353000();
        (*v240_x00126)();
        rt_00350bf0();
        (*v6)();
        v20 = v302;
        rt_003575bc(v302);
        rt_00353df0();
        rt_00350068();
        (*v240_x00127)();
        rt_00351324();
        (*v6)();
        rt_00350944();
        (*v6)();
        rt_003575b0();
        v16 = rt_00352098(&v279);
        rt_0035130c(v16,0x300);
        (*v286)();
        (*v288)(v264,v1,v24,v272);
        rt_0031c490(v20);
        rt_0035102c();
        rt_0035060c();
        rt_00353000();
        v301 = v240_x00128;
        (*v240_x00128)();
        (*v6)(v264,v24);
        rt_0034afc0(v20);
        av237 = rt_003510ac();
        v14 = (*v236)(av237.lo,av237.hi,v24,v26);
        (*v6)(v9,v24);
        if ((v14 & 1) == 0) {
          v24 = rt_003586f0();
          (*v285)(v24,v296);
          rt_003594f4();
          if ((bool)v23) {
            rt_00353390();
            rt_0031c4c0();
          }
          else {
            rt_00353390();
            rt_0031bfe0();
          }
          rt_003589cc();
          rt_0035179c(&v268);
          v24 = v289;
          rt_003509b0();
          (*v240_x00129)();
          v20 = rt_003575b0();
          rt_00350ac4(v1,v20,0x300);
          (*v286)();
          rt_003524e0(&v304);
          rt_000dbe70(v1);
          (*v288)();
          rt_003526b8(stack_ptr);
          rt_0034d180();
          (*v301)();
          rt_0009461c();
          v9 = v300;
          (*v300)();
          rt_003509bc();
          (*v9)();
          rt_00351ee0(v26);
          rt_0034b768();
          v14 = (*v162)();
          rt_000b43d0();
          (*v9)();
          rt_003509bc();
          (*v9)();
          if ((v14 & 1) == 0) {
            rt_003520b4(&v301);
            v9 = (code *)rt_0031c3d0();
            rt_00358828();
            rt_003504f4();
            v286 = (code *)(*v9)();
            v300 = *(code **)(v270 + 8);
            rt_003524a4();
            (*v241_x00107)();
            rt_00352698(&v282);
            rt_0031c788();
            rt_00351af8(sp0x);
            rt_00351414();
            (*v240_x00150)();
            rt_003504f4();
            v13 = (*v9)();
            rt_000a6e14();
            (*v300)();
            v14 = v140 + 8U;
            if ((long)v286 <= v13) {
              v14 = v249;
            }
            rt_00352118(v14,v24);
            (*v241_x00108)();
            v9 = *(code **)(v283 + 0x20);
            av237 = rt_003510b8();
            (*v9)(av237.lo,av237.hi,v24);
            (*v9)(v294,v247,v24);
            goto LBL_00222b90;
          }
          rt_003516e4();
          rt_00352118();
          (*v209)();
          rt_00350bc0(&v289);
          rt_00357be0(v271[0]);
          (*v91)();
          rt_003525f4();
          av237 = rt_00351df0();
          v9 = v241_x00100;
        }
        else {
          rt_00351324();
          (*v6)();
          (*v6)(v263,v24);
          rt_00350bc0(&v289);
          rt_00357be0(v271[0]);
          (*v52)();
          v24 = rt_003525f4();
          av237.hi = v249;
          av237.lo = v24;
          v9 = v133;
        }
      }
      (*v9)(av237.lo,av237.hi);
    }
LBL_00222b90:
    v24 = 0;
  }
  else {
    rt_0031c1c0(param_6);
    rt_0034eafc();
    (*v241_x00101)();
    rt_003594f4();
    if ((bool)v244) {
      v24 = rt_00352140();
      rt_00351148(&v262,v24,v289);
      rt_00377bec();
      rt_0034b8ec();
      rt_0035179c(v257,0x8000000000000000);
      rt_0007c1c4();
      (*v240_x00130)();
    }
    else {
      rt_0034ad00();
      rt_0035266c(&v302);
      rt_00351148(v278);
      rt_00377bec();
      rt_00348fb4();
      rt_0035179c(&v281);
      rt_0034b9f8();
      (*v240_x00133)();
    }
    rt_0034cea8();
    rt_00353e38();
    rt_0034db18(v155);
    (*v240_x00134)();
LBL_00222a2c:
    v24 = 1;
  }
  rt_0008e500(v24,v242);
  return;
}



/* FUN_00223508 @ 0x00223508   (est. swift_compare_dispatch)
 * Ghidra: void FUN_00223508( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00223508( void){
  uint32_t v8;
  unsigned long v7;
  unsigned long v5;
  unsigned long v2;
  long v6;
  long v3;
  uint64_t v4;
  uint64_t v41;
  uint64_t v44;
  long v40;
  uint64_t v34;
  long v10;
  code *v21;
  code *v33;
  code *v22;
  code *v35;
  code *v31;
  code *v26;
  code *v20;
  code *v14;
  code *v19;
  code *v38;
  code *v11;
  code *v28;
  code *v36;
  code *v12;
  code *v27;
  code *v29;
  code *v9;
  code *v17;
  code *v15;
  code *v1;
  code *v39;
  code *v30;
  code *v37;
  code *v23;
  code *v13;
  code *v32;
  code *v16;
  code *v18;
  code *v24;
  code *v25;
  code *v42;
  uint32_t v43;
  rt16 v45;
  rt16 av80;
  
  rt_0008e518();
  v45 = rt_0034e8a4();
  rt_00349684(v44);
  rt_003523fc();
  v7 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034aab0();
  rt_0034a774();
  rt_003513fc();
  v5 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_00349080();
  (*G_00658c00)(*(uint64_t *)(v40 + 0x40));
  rt_003497b4();
  rt_0034911c();
  (*G_00658c00)(*(uint64_t *)(v10 + 0x40));
  rt_003497b4();
  rt_003557a8();
  rt_003564a4();
  rt_0034ba08();
  (*v42)();
  rt_00354cc0();
  rt_0035305c();
  rt_0034b4a0();
  v8 = (*v21)();
  if (((v43 ^ v8) & 1) == 0) {
    rt_0034c368();
    rt_0035072c();
    v6 = (*v31)();
    rt_0034a588();
    v3 = (*v26)();
    if (v3 <= v6) {
      rt_0034eaac();
      (*v11)();
      rt_0034d1fc();
      rt_00353a84();
      rt_00349f8c();
      (*v30)();
      rt_00348e78();
      goto LBL_002238c0;
    }
    rt_0034de24();
    rt_00350c68();
    (*v20)();
    rt_0034cee8();
    rt_00352200();
    rt_00349f74();
    (*v39)();
    rt_00348c84();
    rt_0034c5ac(v6);
    (*v14)();
    v4 = rt_0034cd04();
    v1 = v19;
  }
  else {
    rt_0034ba08();
    v2 = (*v42)();
    rt_0034c368();
    rt_0035072c();
    v6 = (*v33)();
    rt_0034c0d0();
    rt_0034e064();
    v3 = (*v22)();
    if ((v2 & 1) == 0) {
      if (v6 < v3) {
        v4 = rt_0034de24();
        (*v38)(v4,v45.hi);
        goto LBL_002238f8;
      }
      rt_0034ad00();
      rt_0034c694();
      rt_00377bec();
      rt_003493ec();
      rt_0034abd8();
      (*v32)();
      rt_0034c384();
      av80 = rt_0034d2f4(v34);
      (*v16)(av80.lo,av80.hi,v41);
      rt_0034c480();
      rt_00310b08();
      rt_0034eae8();
      rt_003511cc();
      (*v36)();
      rt_0034c888();
      (*v18)();
      if ((v7 & 1) == 0) goto LBL_00223940;
      rt_0034ee08(*(uint64_t *)(v6 + 0x10));
      (*v12)();
    }
    else {
      if (v6 <= v3) {
        rt_0034ad00();
        rt_0034d364();
        rt_00377bec();
        rt_003493ec();
        rt_0034abd8();
        (*v37)();
        rt_0034c384();
        rt_003534f8();
        rt_0034c674();
        (*v23)();
        rt_003496e8();
        rt_003518b8();
        rt_00350a1c();
        (*v28)();
        rt_0034c870();
        (*v13)();
        if ((v5 & 1) != 0) goto LBL_00223940;
        rt_00350768(*(uint64_t *)(v6 + 0x10));
        (*v9)();
LBL_002238f8:
        rt_0034cee8();
        rt_00352e30();
        rt_00349f74();
        (*v25)();
        rt_00348c84();
        rt_0035063c(v34,v45.lo);
        (*v17)();
        rt_0034d820();
        v4 = v34;
        v1 = v15;
        goto LBL_00223934;
      }
      rt_0034e94c();
      (*v35)();
    }
    rt_0034d1fc();
    rt_00352a64();
    rt_00349f8c();
    (*v24)();
    rt_00348e78();
LBL_002238c0:
    rt_00350974(v45.hi);
    (*v27)();
    v4 = rt_0034e33c();
    v1 = v29;
  }
LBL_00223934:
  (*v1)(v4);
LBL_00223940:
  v4 = rt_00352980();
  rt_0008e500(v4,v34);
  return;
}



/* FUN_00223960 @ 0x00223960   (est. swift_float_parse)
 * Ghidra: void FUN_00223960( void)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
void FUN_00223960( void){
  unsigned long v14;
  char v12;
  uint16_t v10;
  int v8;
  uint32_t v7;
  uint64_t v15;
  uint64_t v9;
  long v13;
  long v11;
  unsigned long v6;
  void *v2;
  code *v1;
  uint64_t v59;
  uint64_t v60;
  uint16_t v4;
  uint32_t v3;
  uint64_t v57;
  long v47;
  uint64_t v18;
  long v30;
  code *v46;
  code *v33;
  code *v48;
  code *v42;
  code *v37;
  code *v29;
  code *v22;
  code *v28;
  code *v54;
  code *v19;
  code *v39;
  code *v50;
  code *v20;
  code *v38;
  code *v40;
  code *v17;
  code *v25;
  code *v23;
  code *v52;
  code *v41;
  code *v31;
  code *v27;
  code *v45;
  code *v49;
  code *v56;
  code *v43;
  code *v53;
  code *v34;
  code *v21;
  code *v44;
  code *v24;
  code *v26;
  code *v35;
  code *v36;
  code *v51;
  code *v32;
  long v55;
  long v16;
  uint64_t v58;
  float v5;
  uint64_t v64;
  float v62;
  float v63;
  unsigned long v61 [2];
  
  rt_00352c10();
  rt_0008f6f4(v59);
  rt_0008f6f4();
  rt_00027754();
  rt_00351684();
  rt_00349dfc();
  v15 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034b250();
  rt_0034e3ac();
  (*G_00658c00)(*(uint64_t *)(v47 + 0x40));
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
  (*G_00658c00)(*(uint64_t *)(v30 + 0x40));
  rt_00348a34();
  (*G_00658c00)();
  rt_0034aea8();
  (*G_00658c00)();
  rt_0034c2c8();
  v9 = rt_0031c520(v60);
  rt_0034ef18(v9);
  v13 = (*v46)();
  rt_0031c550(v60);
  v9 = rt_003505d0();
  v11 = (*v33)(v9,v60);
  if (v13 == 0xb) {
    if (v11 == 0x34) {
      rt_00351d0c();
      rt_003513a8();
      (*v53)();
      rt_003516f0(v61);
      v8 = rt_00365b6c();
      if (v8 == 0) {
        rt_00354780();
        rt_0008f6f4();
        rt_0031c1c0();
        rt_003518e8();
        rt_00350524();
        v12 = (*v20)();
        rt_0035764c(v15);
        rt_00350470(v18);
        (*v35)();
        rt_00359eb4();
        rt_00350518();
        rt_00351cd0();
        rt_00377bec();
        rt_00350780();
        rt_0034dbe8();
        rt_0035060c();
        v2 = (void *)(*v38)();
        rt_003566b4();
        rt_00350b3c();
        (*v40)();
        rt_0031c788(v15);
        rt_00351590();
        rt_00350470();
        (*v36)();
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v17)();
        rt_00350518();
        rt_00353960();
        rt_00377bec();
        rt_00350950();
        rt_0034d054();
        rt_00350560();
        v6 = (*v25)();
        rt_00353e08();
        rt_00351274();
        (*v23)();
        v14 = 0x8000000000000000;
        if (v12 != '\x01') {
          v14 = 0;
        }
        v61[0] = v14 | ((unsigned long)v2 & 0x7ff) << 0x34 | v6 & 0xfffffffffffff;
      }
      else {
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v37)();
      }
      rt_003568e8();
      v1 = (code *)rt_0031c5b0();
      (*v1)(v57,v61[0],v58,v2);
      return;
    }
LBL_00223cac:
    rt_003513f0();
    ((code)FUN_0021f7b0)();
    rt_00084174(*(uint64_t *)(v16 + 8));
    (*v29)();
    rt_0034ad00();
    rt_0034f534();
    rt_00377bec();
    rt_0034b8ec();
    v15 = rt_00351a74();
    rt_0034cfd4(v64,v15,0x200);
    (*v34)();
    rt_0034cea8();
    rt_00352dd0();
    rt_0034db18();
    (*v21)();
    rt_00356078();
    rt_0031c580();
    rt_00353ce4();
    rt_0034c5ac();
    (*v44)();
    v1 = *(code **)(v55 + 8);
    rt_00350560();
    (*v1)();
    rt_003507d4();
    (*v1)();
  }
  else {
    if (v13 == 8) {
      if (v11 != 0x17) goto LBL_00223cac;
      rt_00351984(v16);
      rt_003513a8();
      (*v43)();
      rt_00350ad0(&v63);
      v8 = rt_00365b6c();
      if (v8 == 0) {
        rt_00354780();
        rt_0008f6f4();
        rt_0031c1c0();
        rt_003518e8();
        rt_00350524();
        v12 = (*v22)();
        rt_0035764c(v15);
        rt_00350470(v18);
        (*v24)();
        rt_00359eb4();
        rt_00350518();
        rt_00351cd0();
        rt_00377bec();
        rt_00350780();
        rt_0034dbe8();
        rt_0035060c();
        v2 = (void *)(*v28)();
        rt_003566b4();
        rt_00350b3c();
        (*v54)();
        rt_0031c788(v15);
        rt_00351590();
        rt_00350470();
        (*v26)();
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v19)();
        rt_00350518();
        rt_00353960();
        rt_00377bec();
        rt_00350950();
        rt_0034d054();
        rt_00350560();
        v7 = (*v39)();
        rt_00353e08();
        rt_00351274();
        (*v50)();
        v3 = 0x80000000;
        if (v12 != '\x01') {
          v3 = 0;
        }
        v5 = (float)(v3 | ((uint32_t)v2 & 0xff) << 0x17 | v7 & 0x7fffff);
      }
      else {
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v42)();
        v5 = v63;
      }
    }
    else {
      if (v13 != 5 || v11 != 10) goto LBL_00223cac;
      rt_00351d0c();
      rt_003513a8(&G_0061014c);
      (*v56)();
      rt_00350810(&v62);
      v8 = rt_00365b6c();
      if (v8 == 0) {
        rt_00354780();
        rt_0008f6f4();
        rt_0031c1c0();
        rt_003518e8();
        rt_00350524();
        v12 = (*v52)();
        rt_0035764c(v15);
        rt_00350470(v18);
        (*v51)();
        rt_00359eb4();
        rt_00350518();
        rt_00351cd0();
        rt_00377bec();
        rt_00350780();
        rt_0034dbe8();
        rt_0035060c();
        v2 = (void *)(*v41)();
        rt_003566b4();
        rt_00350b3c();
        (*v31)();
        rt_0031c788(v15);
        rt_00351590();
        rt_00350470();
        (*v32)();
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v27)();
        rt_00350518();
        rt_00353960();
        rt_00377bec();
        rt_00350950();
        rt_0034d054();
        rt_00350560();
        v10 = (*v45)();
        rt_00353e08();
        rt_00351274();
        (*v49)();
        v4 = 0x8000;
        if (v12 != '\x01') {
          v4 = 0;
        }
        v62 = (float)(v4 | (uint16_t)(((uint32_t)v2 & 0x1f) << 10) | v10 & 0x3ff);
      }
      else {
        rt_0008e388(*(uint64_t *)(v16 + 8));
        (*v48)();
      }
      v5 = (float)v62;
    }
    rt_003568e8();
    v1 = (code *)rt_0031c5e0();
    (*v1)(v57,v5,v58,v2);
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

  bool v13;
  uint32_t v17;
  uint32_t v14;
  code *v9;
  code *v11;
  uint64_t v18;
  code *v8;
  unsigned long v16;
  long v15;
  long v7;
  uint64_t v12;
  long v10;
  code *v5;
  code *v6;
  code *v2;
  code *v4;
  code *v146;
  uint64_t v145;
  long v133;
  long v25;
  long v95;
  code *v132;
  code *v97;
  code *v70;
  code *v63;
  code *v38;
  code *v32;
  code *v88;
  code *v53;
  code *v81;
  code *v117;
  code *v62;
  code *v42;
  code *v50;
  code *v39;
  code *v100;
  code *v85;
  code *v29;
  code *v120;
  code *v137;
  code *v101;
  code *v94;
  code *v123;
  code *v130;
  code *v72;
  code *v84;
  code *v104;
  code *v115;
  code *v80;
  code *v83;
  code *v98;
  code *v64;
  code *v52;
  code *v78;
  code *v91;
  code *v31;
  code *v112;
  code *v30;
  code *v49;
  code *v65;
  code *v113;
  code *v129;
  code *v116;
  code *v34;
  code *v57;
  code *v122;
  code *v77;
  code *v125;
  code *v111;
  code *v26;
  code *v114;
  code *v44;
  code *v33;
  code *v106;
  code *v134;
  code *v71;
  code *v79;
  code *v126;
  code *v54;
  code *v110;
  code *v47;
  code *v89;
  code *v142;
  code *v135;
  code *v144;
  code *v102;
  code *v43;
  code *v35;
  code *v87;
  code *v103;
  code *v121;
  code *v93;
  code *v58;
  code *v127;
  code *v74;
  code *v124;
  code *v55;
  code *v60;
  code *v109;
  code *v48;
  code *v51;
  code *v128;
  code *v90;
  code *v23;
  code *v75;
  code *v24;
  code *v37;
  code *v69;
  code *v73;
  code *v136;
  code *v59;
  code *v61;
  code *v99;
  code *v86;
  code *v36;
  code *v107;
  code *v119;
  code *v140;
  code *v141;
  code *v131;
  code *v68;
  code *v105;
  code *v22;
  code *v46;
  code *v138;
  code *v67;
  code *v96;
  code *v108;
  code *v41;
  code *v76;
  code *v56;
  code *v27;
  code *v92;
  code *v66;
  code *v45;
  code *v118;
  code *v28;
  code *v139;
  code *v40;
  code *v82;
  long v143;
  code *v20;
  long v19;
  long v21;
  code *v1;
  uint64_t v147;
  code *v3;
  uint64_t v148;
  rt16 v159;
  code *v149;
  unsigned long v153;
  uint64_t v156;
  uint64_t v158;
  uint64_t v157;
  uint64_t v154;
  code *v155;
  code *v152;
  code *v150;
  uint64_t v151;
  
  v159 = rt_0008e518();
  v4 = v159.hi;
  v15 = v159.lo;
  rt_00359338(param_4);
  rt_00352f54();
  rt_0034eda8();
  rt_00377824();
  rt_0035a700();
  rt_0034cf84();
  rt_00377bec();
  v9 = (code *)rt_00027754();
  rt_0008f6c0();
  rt_00351684();
  rt_00352c28(0);
  rt_00377824();
  rt_00349c44(sp0x);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034c8c8();
  rt_0035a478(param_5);
  rt_00352720();
  rt_00352438();
  rt_00377824();
  rt_0034e54c();
  rt_00377bec();
  v11 = (code *)rt_00027754();
  rt_0034be54();
  rt_00353960(0);
  rt_00377824();
  rt_00349c44(sp0x);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_0034c754();
  v18 = rt_00377dcc();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v133 + 0x40));
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
  v8 = (code *)rt_00377dcc();
  rt_000a6f88();
  (*G_00658c00)(*(uint64_t *)(v25 + 0x40));
  rt_003493c4();
  rt_0034d294();
  (*G_00658c00)();
  rt_0034aa28();
  rt_003499f0();
  (*G_00658c00)(*(uint64_t *)(v95 + 0x40));
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
  v16 = (*v132)();
  v5 = param_3;
  if ((v16 & 1) == 0) {
    rt_0031c520(param_5);
    rt_003511fc();
    v7 = (*v97)(param_3,param_5);
    v12 = rt_0031c520(param_4);
    v12 = rt_00351208(v12);
    v10 = (*v70)(v12,param_4);
    v1 = param_4;
    if (v10 < v7) {
LBL_00224568:
      rt_0031c250();
      rt_00351ac8();
      rt_003508f0();
      v16 = (*v32)();
      if ((v16 & 1) != 0) {
        rt_0031c220();
        rt_00351ac8();
        rt_003508f0();
        v16 = (*v88)();
        if ((v16 & 1) == 0) {
          v5 = (code *)rt_0031c370();
          (*v5)(v150);
          rt_003537f0();
          rt_0031c3a0();
          rt_00350b24();
          rt_003510b8();
          (*v102)();
          rt_0031c370(v1);
          rt_00351f7c();
          rt_003510b8();
          (*v43)();
          rt_00353930(v19);
          (*v35)(rt_0060e3fc,v4);
          rt_0035a44c(v11);
          rt_00100c38();
          v17 = (*v1)();
          rt_00354abc();
          rt_0035305c();
          rt_00350b00();
          rt_00355db4();
          v14 = (*v81)();
          v3 = v9;
          v5 = v150;
          if (((v17 ^ v14) & 1) == 0) {
            rt_0034c368();
            rt_00100c38();
            v2 = (code *)(*v50)();
            rt_0034c0ec();
            rt_00350b00();
            v7 = (*v39)();
            if ((long)v2 < v7) {
              rt_00353a00();
              rt_00356924();
              rt_00352c4c();
              (*v121)();
              rt_0034e1d0();
              rt_00350fec(v155);
              rt_0034c3d4();
              (*v93)();
              rt_0034afc0(v4);
              rt_003502d8(v155);
              (*v100)();
              rt_00355c58();
              rt_003508cc();
              (*v8)();
              rt_00084180();
              (*v8)();
              v6 = v20;
              v5 = v155;
            }
            else {
              rt_0034d1fc();
              rt_00358d7c();
              rt_0034d190();
              rt_00353184();
              (*v74)();
              rt_00348e78(v11);
              v159 = rt_003508f0();
              v6 = (code *)(*v29)(v159.lo,v159.hi,v8,&G_0060ff00);
              rt_00350738();
              (*v124)();
            }
            rt_00355424();
            rt_00358690();
            v3 = v4;
            if (((unsigned long)v6 & 1) != 0) goto LBL_00224bb8;
LBL_00224ebc:
            rt_00357710();
            rt_0031c310();
            rt_00351414(v156);
            (*v86)();
            rt_00351414(v154);
            rt_003571ec();
            (*v36)();
            rt_00352744(v156,v4);
            (*v83)();
            rt_00350630();
            v17 = (*v2)();
            rt_00100c38();
            v14 = (*v1)();
            if (((v17 ^ v14) & 1) == 0) {
              rt_0034c0ec();
              rt_0034e50c();
              v7 = (*v78)();
              rt_0034c368();
              rt_00350a04();
              v10 = (*v91)();
              if (v7 < v10) {
                rt_00310a74(v11);
                rt_0035035c();
                v159 = rt_003505e8();
                rt_00352d88(v159.lo,v159.hi,v3);
                (*v119)();
                rt_003492cc(v11);
                rt_00350b18(v154);
                v16 = (*v31)();
                v5 = *(code **)(v20 + 8);
                rt_00350494();
                (*v5)();
                rt_000dbd0c();
                (*v5)();
              }
              else {
                rt_0034e1d0();
                rt_00353074();
                v159 = rt_000dbd0c();
                rt_0034c3d4(v159.lo,v159.hi,v11);
                (*v141)();
                rt_003492cc(v3);
                rt_0034f5d4(v154);
                v16 = (*v30)();
                v5 = *(code **)(v143 + 8);
                rt_00084180();
                (*v5)();
                rt_003505e8();
                (*v5)();
              }
              rt_00355424();
              goto joined_r0x00225550;
            }
            rt_0034c054();
            v16 = (*v2)();
            rt_0034c0ec();
            v12 = rt_00356c48();
            v7 = (*v98)(v12,v3);
            rt_0034c368();
            rt_00100c38();
            v10 = (*v64)();
            if ((v16 & 1) == 0) {
              if (v7 < v10) {
                rt_0034d1fc();
                rt_00350878(v152,v154);
                rt_0034bdcc();
                (*v140)();
                rt_003492cc(v11);
                rt_0034f494(v152);
                v16 = (*v112)();
                v11 = *(code **)(v20 + 8);
                rt_003505e8();
                (*v11)();
                rt_003514e8();
                (*v11)();
                v11 = v5;
                goto joined_r0x00225550;
              }
              rt_0034ad00();
              v12 = rt_00352584(sp0x);
              rt_00351148(sp0x,v12,v8);
              rt_00377bec();
              rt_003494fc();
              rt_0034b100(sp0x);
              (*v41)();
              rt_0008f758(v18);
              rt_0034d934();
              rt_003508c0();
              (*v76)();
              rt_0034bf48(v11);
              rt_00351ee0();
              rt_00351360();
              rt_0035359c();
              v16 = (*v57)();
              v5 = *(code **)(v20 + 8);
              rt_000a6e14();
              (*v5)();
              if ((v16 & 1) != 0) {
                rt_003506cc();
                rt_003589c0();
                v159 = rt_000dbd0c();
                rt_0034cf64(v159.lo,v159.hi,v11);
                (*v56)();
                rt_003492cc(v2);
                rt_003514d0();
                rt_00351238();
                v16 = (*v122)();
                v5 = *(code **)(v143 + 8);
                (*v5)(param_4,v18);
                rt_00084180();
                (*v5)();
                rt_00355424();
                goto joined_r0x00225550;
              }
              rt_00353db8();
              (*v44)(v154,v18);
              rt_000dbd0c();
              (*v5)();
              rt_00355424();
LBL_00225878:
              rt_00358a08(param_5);
              rt_003508b4();
              v7 = (*v33)();
              v18 = rt_00351208(v158);
              (*v86)(v18,v147);
              rt_00358a08(param_4);
              rt_00350bf0();
              v10 = (*v106)();
              rt_003504ac();
              rt_00352744();
              (*v134)();
              v5 = v11;
              if (v10 < v7) goto LBL_00224494;
              goto LBL_002245a0;
            }
            if (v10 < v7) {
              rt_00310a74(v2);
              rt_0035034c();
              rt_0034cf64(v150,v8,v11);
              (*v107)();
              rt_003492cc(v2);
              rt_0034f494(v154);
              v16 = (*v52)();
              v11 = *(code **)(v143 + 8);
              rt_003514e8();
              (*v11)();
              rt_00084180();
              (*v11)();
              v11 = v5;
joined_r0x00225550:
              v5 = v11;
              if ((v16 & 1) == 0) goto LBL_00225878;
            }
            else {
              rt_0034ad00();
              rt_00356060();
              rt_0035060c();
              rt_00351148(sp0x);
              rt_00377bec();
              rt_003494fc();
              rt_00351af8(sp0x);
              rt_0034c9b8();
              (*v96)();
              rt_0034d558();
              rt_003545e8();
              v159 = rt_0034d374();
              (*v108)(v159.lo,v159.hi,v16);
              rt_003492cc(v2);
              rt_003584ec();
              rt_0034f494();
              v16 = (*v116)();
              v11 = *(code **)(v143 + 8);
              rt_003514e8();
              (*v11)();
              if ((v16 & 1) == 0) {
                rt_00356964();
                rt_00350a4c();
                v159 = rt_003505e8(v152);
                rt_0034ce38(v159.lo,v159.hi,v2);
                (*v139)();
                rt_003492cc(v11);
                rt_0034f374();
                v16 = (*v114)();
                v11 = *(code **)(v20 + 8);
                rt_003509d4();
                (*v11)();
                rt_003514e8();
                (*v11)();
                v11 = v5;
                goto joined_r0x00225550;
              }
              rt_003505e8();
              (*v11)();
              v18 = rt_00351a08();
              (*v34)(v18,v8);
            }
            v11 = *(code **)(*(long *)(v5 + -8) + 8);
            goto LBL_002244b0;
          }
          rt_00100c38();
          v6 = (code *)(*v1)();
          rt_0034c368();
          rt_00350618();
          v2 = (code *)(*v117)();
          rt_0034c0ec();
          v16 = 0;
          rt_00350b00();
          v7 = (*v62)();
          if (((unsigned long)v6 & 1) == 0) {
            if (v7 <= (long)v2) {
              rt_0034ad00();
              rt_003505e8();
              rt_00351148(sp0x);
              v16 = rt_00377bec().lo;
              rt_003494fc();
              rt_0034b100(sp0x);
              (*v51)();
              rt_0034dc20();
              rt_003545e8();
              v159 = rt_0034d810();
              (*v128)(v159.lo,v159.hi,v146);
              rt_00310ad4(v4);
              rt_00351bec();
              rt_00310b08();
              rt_0034e64c();
              rt_00351560();
              (*v137)();
              rt_00355c58();
              rt_003514e8();
              (*v146)();
              rt_00355424();
              v2 = (code *)(v16 & 0xffffffffffff | 0x4f8000000000000);
              rt_00084180();
              (*v146)();
              rt_00358690();
              v3 = v4;
              goto LBL_00224ebc;
            }
            v12 = rt_00356924();
            (*v58)(v12,v150,v8);
            rt_0034e1d0();
            rt_003545e8();
            v159 = rt_00352498();
            rt_003505dc(v159.lo,v159.hi,v11);
            (*v127)();
            rt_0034afc0(v4);
            rt_003502d8(v11);
            (*v85)();
            rt_00355c58();
            (*v6)(v11,v18);
            rt_00084180();
            (*v6)();
            v5 = v4;
            v3 = v4;
          }
          else if (v7 < (long)v2) {
            rt_0034d1fc();
            rt_00358d7c();
            rt_0034d190();
            rt_00353184();
            (*v87)();
            rt_00348e78(v11);
            rt_00351214(v150);
            (*v42)();
            rt_0034bdec();
            rt_00350738();
            (*v103)();
            v16 = 0;
            v3 = v4;
          }
          else {
            rt_0034ad00();
            v12 = rt_00353dac(sp0x);
            rt_00351148(sp0x,v12,v8);
            rt_00377bec();
            rt_003494fc();
            rt_0034b100(sp0x);
            (*v55)();
            rt_0034e74c();
            rt_00353050(v150);
            (*v60)();
            rt_0034afc0(v11);
            rt_00351354();
            rt_00352ea8();
            v16 = (*v120)();
            rt_0035a578();
            rt_00350914();
            (*v109)();
            v2 = v20;
            if ((v16 & 1) != 0) {
              rt_00084180();
              (*v48)();
              rt_00358690();
              goto LBL_00224bb8;
            }
            rt_0034ee58();
            rt_00351dfc();
            (*v90)();
            rt_00310a74(v9);
            rt_0035034c();
            rt_0034ee98();
            rt_003505dc();
            (*v23)();
            rt_0034afc0(v9);
            rt_003502d8(v150);
            (*v101)();
            rt_00355c58();
            rt_003514e8();
            (*v8)();
            rt_00084180();
            (*v8)();
            v5 = v152;
          }
          rt_00355424();
          rt_00358690();
          if ((v16 & 1) == 0) goto LBL_00224ebc;
LBL_00224bb8:
          rt_00359f6c();
          rt_0031c4f0();
          rt_0035133c();
          rt_00100efc();
          (*v75)();
          rt_00100efc(v157);
          rt_003571ec();
          (*v24)();
          rt_003504c4();
          rt_00352744();
          (*v94)();
          rt_00100c38();
          v7 = (*v1)();
          v12 = rt_00350554();
          v17 = (*v2)(v12,v3);
          if ((((uint32_t)v7 ^ v17) & 1) != 0) {
            rt_00100c38();
            v16 = (*v1)();
            rt_0034c368();
            rt_00100c38();
            (*v123)();
            rt_00356c30();
            rt_003507a4();
            rt_003514d0();
            v10 = (*v130)();
            if ((v16 & 1) == 0) {
              if (v7 < v10) {
                rt_00351d0c();
                (*v136)(v152,v150,v8);
                rt_00310a74(v3);
                rt_0034efb8();
                rt_00350fec();
                rt_003505dc();
                (*v59)();
                rt_003492cc(v3);
                rt_00350494();
                rt_00351238();
                v16 = (*v115)();
                v5 = *(code **)(v143 + 8);
                rt_00084180();
                (*v5)();
                rt_0035060c();
                v12 = (*v5)();
                v3 = v9;
              }
              else {
                rt_0034ad00();
                rt_00358954();
                rt_003514e8();
                rt_00351148(sp0x);
                rt_00377bec();
                rt_003494fc();
                rt_00352ca4(sp0x);
                rt_0034c9b8();
                (*v22)();
                rt_0034c7d4();
                rt_00353074();
                rt_0034d778(v16);
                (*v46)();
                rt_0034bf48(v3);
                rt_00310b08();
                rt_00350a40();
                rt_0034f5d4();
                v16 = (*v113)();
                v5 = *(code **)(v143 + 8);
                rt_00084180();
                (*v5)();
                if ((v16 & 1) == 0) {
                  rt_003508cc();
                  (*v5)();
                  goto LBL_0022564c;
                }
                rt_00310a74(v11);
                rt_0035035c();
                v159 = rt_003508cc();
                rt_00353184(v159.lo,v159.hi,v3);
                (*v138)();
                rt_003492cc(v11);
                rt_003507bc();
                rt_00351b2c();
                v16 = (*v129)();
                v12 = rt_0034d170();
                v12 = (*v67)(v12,v8);
              }
            }
            else {
              if (v10 < v7) {
                rt_0034d1fc();
                rt_00353bd0();
                rt_00350068();
                rt_00353184();
                (*v37)();
                rt_003492cc(v11);
                goto LBL_00224e68;
              }
              rt_0034ad00();
              v12 = rt_003520b4(sp0x);
              rt_00351148(sp0x,v12,v8);
              rt_00377bec();
              rt_003494fc();
              rt_0034b100(sp0x);
              (*v131)();
              rt_0034d9cc();
              rt_003547f8();
              rt_00351720();
              (*v68)();
              rt_003492cc(v11);
              rt_0035060c();
              rt_00351b2c();
              v16 = (*v49)();
              rt_003516c0();
              rt_003508fc();
              (*v105)();
              if ((v16 & 1) != 0) {
                rt_00353db8();
                v12 = (*v65)(v157,v18);
                goto LBL_002255f0;
              }
              rt_00351d0c();
              v159 = rt_003509e0();
              (*v27)(v159.lo,v159.hi,v8);
              rt_00310a74(v3);
              rt_0034efb8();
              v159 = rt_003508fc();
              rt_003505dc(v159.lo,v159.hi,v11);
              (*v92)();
              rt_003492cc(v3);
              rt_0034f5d4(v18);
              v16 = (*v77)();
              v5 = *(code **)(v143 + 8);
              (*v5)(v155,v18);
              rt_00084180();
              v12 = (*v5)();
              v18 = v157;
              v3 = v9;
            }
joined_r0x00225380:
            if ((v16 & 1) == 0) goto LBL_0022564c;
LBL_002255f0:
            rt_0034ece8(v12,param_3);
            (**(code **)(v21 + 8))(v15);
            rt_00350738(*(uint64_t *)(v20 + 8));
            (*v125)();
            goto LBL_002244bc;
          }
          rt_0034c368();
          rt_00100c38();
          (*v72)();
          rt_00356c30();
          rt_003507a4();
          rt_003514d0();
          v10 = (*v84)();
          if (v10 <= v7) {
            rt_0034d1fc();
            rt_00353bd0();
            rt_00350068();
            rt_00353184();
            (*v61)();
            rt_003492cc(v11);
LBL_00224e68:
            rt_003504f4();
            rt_00351b2c();
            v16 = (*v80)();
            v12 = rt_0034d170();
            v12 = (*v99)(v12,v8);
            goto joined_r0x00225380;
          }
          rt_00351d0c();
          rt_00351214(v152);
          (*v69)();
          rt_00310a74(v3);
          rt_0034efb8();
          rt_00350fec();
          rt_003505dc();
          (*v73)();
          rt_003492cc(v3);
          rt_00351238(v18,v157);
          v17 = (*v104)();
          v5 = *(code **)(v143 + 8);
          rt_00084180();
          (*v5)();
          v12 = (*v5)(v157,v18);
          v3 = v9;
          if ((v17 & 1) != 0) goto LBL_002255f0;
LBL_0022564c:
          rt_00357a90();
          rt_00358a08();
          v7 = (*v111)(param_3,v18);
          rt_00356924();
          rt_00351214();
          (*v66)();
          rt_0016796c(v3);
          rt_0035034c();
          v159 = rt_00351648();
          rt_0034ce38(v159.lo,v159.hi,v11);
          (*v45)();
          v18 = rt_00351208(v158);
          (*v75)(v18,v147);
          rt_003519b4(sp0x);
          rt_00100efc();
          rt_003571ec();
          (*v118)();
          rt_00350630();
          rt_00352744();
          (*v26)();
          rt_000dbedc();
          rt_00350950();
          rt_0035614c();
          rt_00351354(v153);
          rt_0034beec();
          (*v28)();
          v11 = *(code **)(v143 + 8);
          rt_003508cc();
          (*v11)();
          rt_003514e8();
          (*v11)();
          rt_0034df44();
          v16 = (*v149)();
          if ((v16 & 1) != 0) {
            rt_00358d58(v3);
            rt_003509e0();
            v10 = (*v11)();
            if (0x40 < v10) {
              rt_0034db08();
              v16 = (*v149)();
              if ((v16 & 1) == 0) {
                rt_0034db08();
                v16 = (*v149)();
                rt_003509e0();
                v10 = (*v11)();
                if ((v16 & 1) != 0) {
                  if (0x40 < v10) {
                    rt_00352944();
                    v3 = v9;
                    goto LBL_0022592c;
                  }
                  rt_0034ad00();
                  rt_00358948();
                  rt_00350524();
                  rt_00351148(sp0x);
                  rt_00377bec();
                  rt_00349370();
                  rt_0034b100(sp0x);
                  (*v40)();
                  rt_0034c384();
                  rt_00353c60();
                  rt_0034c674();
                  (*v82)();
                  rt_00348e78(v9);
                  rt_0034f374();
                  (*v79)();
                  rt_0034eeb8();
                  (*v11)();
                  v3 = v9;
                  if ((v153 & 1) == 0) goto LBL_002259fc;
LBL_00225974:
                  rt_003480e4();
                  goto LBL_00225ad0;
                }
                v3 = v9;
                if (v10 < 0x40) goto LBL_002259fc;
              }
              else {
                rt_003509e0();
                v10 = (*v11)();
                if (v10 < 0x40) {
LBL_002259fc:
                  rt_0034bfe0();
                  rt_003509e0();
                  (*v126)();
                }
                else {
                  rt_00352944();
LBL_0022592c:
                  rt_00352d4c(v3);
                  rt_0001df60();
                  rt_00349630();
                  rt_003545e8();
                  rt_0034e4dc();
                  (*v11)();
                  rt_00348e78(v3);
                  rt_0034f374();
                  (*v71)();
                  rt_0034eeb8();
                  (*v11)();
                  if ((v153 & 1) != 0) goto LBL_00225974;
                }
              }
            }
          }
          rt_00358d58(v3);
          rt_003509e0();
          v10 = (*v11)();
          if (v10 < 0x41) {
            rt_003509e0();
            v10 = (*v11)();
            if (v10 == 0x40) {
              rt_0034db08();
              rt_003570f0();
              v16 = (*v47)();
              if ((v16 & 1) == 0) goto LBL_00225a44;
            }
          }
          else {
LBL_00225a44:
            rt_0034db08();
            rt_003570f0();
            v16 = (*v54)();
            rt_003509e0();
            v10 = (*v11)();
            if ((v16 & 1) == 0) {
              if (v10 < 0x40) goto LBL_00225b14;
            }
            else if (v10 < 0x41) {
LBL_00225b14:
              rt_0034bfe0();
              rt_003509e0();
              (*v89)();
              v3 = v9;
              goto LBL_00225b30;
            }
            rt_00354270();
            rt_00352d4c(v9);
            rt_0001df60();
            rt_00349630();
            rt_003545e8();
            rt_0034e4dc();
            (*v11)();
            rt_00348e78(v9);
            rt_0034e51c(v16);
            (*v110)();
            rt_0034eeb8();
            (*v11)();
            v3 = v9;
            if ((v153 & 1) != 0) {
              rt_00347fb4();
LBL_00225ad0:
              rt_003523f0();
                    /* WARNING: Subroutine does not return */
              rt_001afe4c();
            }
          }
LBL_00225b30:
          rt_0035336c();
          (*v142)(v150,v8);
          rt_0034bf2c(v3);
          rt_003509e0();
          v10 = (*v135)();
          rt_00350524();
          (*v11)();
          v5 = param_3;
          if (v10 < v7) goto LBL_00224494;
        }
      }
    }
    else {
      rt_0031c550(param_5);
      rt_003511fc();
      rt_003508b4();
      (*v63)();
      rt_00353b88();
      rt_003560a8();
      rt_0031c550();
      rt_003514ac();
      rt_00350c80();
      v10 = (*v38)();
      v13 = v10 < v15;
      v1 = param_3;
      v15 = v7;
      if (v13) goto LBL_00224568;
    }
LBL_002245a0:
    rt_00358d10();
    rt_0031c610();
    v159 = rt_003509b0(v151);
    rt_00351154(v159.lo,v159.hi,param_5);
    (*v144)();
    v159 = rt_0007c1c4(*(uint64_t *)(v19 + 0x20));
    (*v53)(v159.lo,v159.hi,v4);
    v18 = 0;
  }
  else {
LBL_00224494:
    v11 = *(code **)(*(long *)(v5 + -8) + 8);
LBL_002244b0:
    (*v11)(v15,v5);
LBL_002244bc:
    v18 = 1;
  }
  rt_00352480(v145,v18);
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
  uint8_t v9;
  char v8;
  char v5;
  uint64_t v6;
  uint64_t v4;
  unsigned long v10;
  uint64_t v7;
  code *v2;
  code *v3;
  long v20;
  long v16;
  code *v14;
  code *v12;
  code *v15;
  code *v13;
  code *v17;
  code *v18;
  long v19;
  long v11;
  uint64_t v22;
  code *v1;
  uint64_t v21;
  rt16 av91;
  uint64_t uStack_28;
  uint64_t v23;
  
  rt_0008e518();
  rt_00353ee4();
  rt_0035899c();
  rt_00350a64();
  rt_00350974();
  rt_00377824();
  v6 = rt_000a6f88();
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
  v4 = rt_0008f6f4();
  rt_0008f6c0();
  rt_00027754();
  rt_0034b4ec();
  rt_003524a4();
  rt_0034beec();
  v10 = (*v14)();
  if ((v10 & 1) != 0) {
LBL_00225dd8:
    v9 = 1;
    goto LBL_00225f0c;
  }
  rt_00310b08();
  v7 = rt_003505f4();
  rt_0034beec(v7,v22);
  v10 = (*v12)();
  if ((v10 & 1) != 0) {
    v9 = 0;
    goto LBL_00225f0c;
  }
  v2 = (code *)rt_0031c1c0(v4);
  rt_00351324();
  v8 = (*v2)();
  rt_00351324();
  v5 = (*v2)();
  v9 = v8 == v5;
  if ((bool)v9) {
    v3 = (code *)rt_0031d6d8();
    rt_0035a3f4();
    rt_0035072c();
    (*v3)();
    rt_0035072c();
    (*v3)();
    rt_00356840();
    rt_0034ed88();
    rt_00377bec();
    rt_00027754();
    rt_0034bf48();
    rt_00310b08();
    rt_0034f4d4();
    rt_0034f2b4();
    v10 = (*v15)();
    v1 = *(code **)(v11 + 8);
    rt_003508b4();
    (*v1)();
    rt_0035084c();
    (*v1)();
    if ((v10 & 1) == 0) {
      rt_0035a3f4();
      rt_0035072c();
      (*v3)();
      rt_0035072c();
      (*v3)();
      rt_0034c464(v2);
      rt_0034f2b4();
      v10 = (*v13)();
      rt_003508b4();
      (*v1)();
      rt_0035084c();
      (*v1)();
      if ((v10 & 1) == 0) {
        v3 = (code *)rt_0031c788();
        rt_0035072c(v23);
        (*v3)();
        rt_0035072c(uStack_28);
        (*v3)();
        rt_00356840();
        av91 = rt_003514e8();
        rt_00377bec(av91.lo,av91.hi,v6);
        rt_00027754();
        rt_0034bf48();
        rt_00310b08();
        rt_0034d3a4();
        rt_00351b2c();
        v10 = (*v17)();
        v1 = *(code **)(v19 + 8);
        rt_00350b78();
        (*v1)();
        rt_00350738();
        (*v1)();
        if ((v10 & 1) != 0) goto LBL_00225edc;
        rt_0035072c(v23);
        (*v3)();
        rt_0035072c(uStack_28);
        (*v3)();
        rt_0035044c(v2);
        rt_00351384();
        rt_00351b2c();
        v10 = (*v18)();
        rt_00350b78();
        (*v1)();
        rt_00351360();
        (*v1)();
        if ((v10 & 1) == 0) goto LBL_00225dd8;
      }
      rt_00351324();
      v8 = (*v2)();
      v9 = v8 == '\0';
      goto LBL_00225f0c;
    }
LBL_00225edc:
    rt_00351324();
    (*v2)();
  }
  else {
    rt_00351324();
    (*v2)();
  }
  rt_003594f4();
LBL_00225f0c:
  rt_0008e500(v9,v21);
  return;
}



/* FUN_002260b0 @ 0x002260b0   (est. swift_string_compare)
 * Ghidra: bool FUN_002260b0(unsigned long * param_1, unsigned long param_2, unsigned long param_3)
 * Swift stdlib runtime support embedded in the cL4 kernel.
 * Confidence: medium
 * Notes: out-of-slice runtime callees declared as rt_* externs (FUN_ addr in comment). */
bool FUN_002260b0(unsigned long * param_1, unsigned long param_2, unsigned long param_3){
  unsigned long v13;
  unsigned long v12;
  uint32_t v9;
  bool v7;
  char *v6;
  uint64_t v14;
  long v8;
  unsigned long v10;
  unsigned long v11;
  unsigned long v4;
  long v3;
  unsigned long v5;
  unsigned long v1;
  rt16 av134;
  uint64_t v2;
  
  if (param_3 == 0 && param_2 == 0) {
    *param_1 = 0;
    return true;
  }
  v1 = -(param_3 + (param_2 != 0));
  v5 = -param_2;
  if (-1 < (long)param_3) {
    v1 = param_3;
    v5 = param_2;
  }
  if (v1 == 0 && v5 == 0) {
    v2 = 0x985;
    v6 = &G_005be7c0;
    v14 = 0;
  }
  else {
    v8 = LZCOUNT(v5);
    v13 = v8 + 0x40;
    if (v1 != 0) {
      v13 = LZCOUNT(v1);
    }
    if (v13 < 0x4b) {
      v11 = 1L << (0x4a - v13 & 0x3f);
      if (v13 < 0xb) {
        v11 = 0;
      }
      v12 = 0;
      if (v13 < 0xb) {
        v12 = 1L << (10 - v13 & 0x3f);
      }
      av134 = rt_002e648c(v11 << 1,v11 >> 0x3f | v12 << 1,1,0);
      v10 = av134.lo & v5;
      v4 = av134.hi & v1;
      if (v13 < 0xc) {
        v1 = v1 >> (0xb - v13 & 0x3f);
      }
      else {
        v9 = (int)v13 - 0xb;
        v1 = v1 << ((unsigned long)v9 & 0x3f) | (v5 >> 1) >> ((unsigned long)~v9 & 0x3f);
      }
      v8 = 0x7f - v13;
      v5 = v1 & 0xfffffffffffff;
      v7 = v11 < v10;
      if (v12 != v4) {
        v7 = v12 < v4;
      }
      v3 = v8;
      if ((v7) || ((v12 == v4 && v10 == v11 && ((v1 & 1) != 0)))) {
        v3 = 0x80 - v13;
        if (v5 != 0xfffffffffffff) {
          v3 = v8;
        }
        v5 = v1 + 1 & 0xfffffffffffff;
      }
      *param_1 = v5 | param_3 & 0x8000000000000000 |
                 (v3 << 0x34) + 0x3ff0000000000000U & 0x7ff0000000000000;
      return v4 == 0 && v10 == 0;
    }
    if (v1 == 0) {
      if (v5 != 0) {
        *param_1 = ((param_3 & 0x8000000000000000) - (v8 << 0x34) |
                   v5 << (v8 - 0xbU & 0x3f) & 0xfffffffffffff) + 0x43e0000000000000;
        return true;
      }
      v2 = 0xcf8;
      v6 = s_Negative_value_is_not_representa_005ce190;
      v14 = 0x23;
    }
    else {
      v2 = 0xcfc;
      v6 = s_Not_enough_bits_to_represent_the_005cd650;
      v14 = 0x2d;
    }
  }
                    /* WARNING: Subroutine does not return */
  rt_001afe4c(s_Fatal_error_005accd0,0xb,2,v6,v14,2,s_Swift_Integers_swift_005cd680,0x14,2,
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

  uint64_t *v11;
  char v15;
  char v19;
  uint8_t v17;
  uint64_t v16;
  uint64_t v21;
  uint64_t v18;
  code *v14;
  uint64_t v20;
  code *v2;
  code *v3;
  unsigned long v13;
  long v12;
  code *v1;
  code *v7;
  code *v10;
  code *v9;
  code *v8;
  uint64_t v200;
  uint64_t v93;
  uint64_t v49;
  long v199;
  long v185;
  long v28;
  long v130;
  long v184;
  code *v132;
  code *v94;
  code *v84;
  code *v45;
  long v37;
  code *v121;
  long v68;
  code *v109;
  code *v164;
  code *v82;
  code *v52;
  code *v62;
  code *v46;
  code *v137;
  code *v118;
  code *v34;
  code *v168;
  code *v190;
  code *v138;
  code *v129;
  code *v173;
  long v181;
  code *v96;
  code *v116;
  code *v142;
  code *v159;
  code *v108;
  code *v112;
  code *v133;
  code *v85;
  code *v66;
  code *v105;
  code *v125;
  code *v36;
  code *v153;
  long v35;
  code *v60;
  code *v87;
  code *v154;
  code *v180;
  code *v162;
  code *v40;
  code *v74;
  code *v172;
  code *v102;
  long v176;
  code *v152;
  code *v29;
  code *v156;
  code *v54;
  code *v38;
  code *v145;
  code *v187;
  code *v95;
  code *v107;
  code *v177;
  code *v69;
  code *v150;
  code *v57;
  code *v123;
  code *v195;
  code *v188;
  code *v104;
  code *v98;
  code *v161;
  long v163;
  long v103;
  code *v48;
  code *v146;
  code *v186;
  code *v158;
  code *v63;
  code *v114;
  code *v30;
  code *v67;
  code *v115;
  code *v167;
  code *v170;
  code *v75;
  code *v61;
  code *v151;
  code *v78;
  code *v86;
  code *v155;
  code *v39;
  code *v83;
  code *v76;
  code *v117;
  code *v196;
  code *v41;
  code *v110;
  code *v113;
  code *v171;
  code *v136;
  code *v175;
  long v71;
  code *v199_x00100;
  long v199_x00101;
  code *v198;
  code *v139;
  code *v53;
  code *v42;
  code *v120;
  code *v141;
  code *v169;
  code *v128;
  code *v77;
  code *v178;
  code *v99;
  code *v174;
  code *v70;
  code *v79;
  code *v149;
  code *v58;
  code *v64;
  code *v179;
  code *v124;
  code *v26;
  code *v100;
  code *v27;
  code *v44;
  code *v92;
  code *v97;
  code *v189;
  code *v5;
  code *v80;
  code *v81;
  code *v134;
  code *v119;
  code *v43;
  code *v147;
  code *v166;
  code *v193;
  code *v194;
  code *v182;
  code *v90;
  code *v143;
  code *v25;
  code *v56;
  code *v191;
  code *v89;
  code *v131;
  code *v148;
  code *v51;
  code *v101;
  code *v73;
  code *v31;
  code *v126;
  code *v88;
  code *v55;
  code *v165;
  code *v33;
  code *v192;
  code *v50;
  code *v111;
  code *v72;
  code *v47;
  code *v65;
  code *v183;
  code *v135;
  code *v144;
  code *v127;
  code *v160;
  code *v106;
  code *v122;
  code *v157;
  code *v32;
  code *v59;
  code *v91;
  code *v140;
  long v197;
  long v23;
  long v22;
  long v24;
  code *v201;
  code *v6;
  code *v4;
  code *v202;
  code *v203;
  rt16 v246;
  uint64_t v208;
  uint64_t v214;
  uint64_t v204;
  uint64_t v219;
  uint64_t v218;
  uint64_t v209;
  uint64_t v207;
  uint64_t v213;
  code *v212;
  uint64_t v206;
  uint8_t v247 [8];
  uint64_t v210;
  uint64_t v205;
  uint64_t *v215;
  code *v217;
  uint64_t v211;
  long v216;
  uint8_t v248 [8];
  uint8_t v222 [8];
  uint8_t v236 [8];
  uint64_t v239;
  code *v233;
  code *v228;
  code *v240;
  uint8_t v232 [8];
  uint64_t v220;
  uint64_t v223;
  code *v244;
  long v226;
  uint64_t v241;
  code *v234;
  code *v225;
  uint64_t v235;
  uint64_t v245;
  code *v243;
  code *pcStack_68;
  uint64_t v237;
  code *v238;
  code *v231;
  code *v229;
  code *v221;
  code *v242;
  uint64_t v230;
  code *v227;
  code *v224;
  uint8_t v249 [8];
  
  rt_0008e518();
  v245 = param_7;
  v231 = param_6;
  v246 = rt_00358a44();
  v242 = v246.hi;
  v223 = v246.lo;
  v16 = rt_0008f6c0(param_6);
  rt_00352968();
  rt_00350b84();
  v21 = rt_00377824().lo;
  rt_00351160();
  rt_0035053c();
  rt_00377bec();
  rt_00351684();
  rt_00353f94();
  rt_00354840();
  rt_00377824();
  rt_00349c44(&v241);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  rt_00359338();
  rt_00352968();
  rt_00351e9c();
  v18 = rt_00377824().lo;
  rt_0034e034();
  rt_00377bec();
  v14 = (code *)rt_00027754();
  rt_0034be54();
  rt_00353f94();
  rt_00352b68();
  rt_00377824();
  rt_00349c44(&v215);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  v20 = rt_0034c754();
  rt_00377dcc(v20,v18);
  rt_003490b8(&v243);
  (*G_00658c00)(*(uint64_t *)(v199 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350464();
  v20 = rt_0034c754();
  rt_00377dcc(v20,v21);
  rt_003490b8(&v227);
  (*G_00658c00)(*(uint64_t *)(v185 + 0x40));
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
  rt_0034fe08(v16);
  v205 = v93;
  rt_00377824();
  rt_00349c44(&v229);
  rt_0007c1a4();
  (*G_00658c00)();
  rt_00350428();
  rt_003509a4();
  v216 = *(long *)(v203 + -8);
  (*G_00658c00)(*(uint64_t *)(v216 + 0x40));
  rt_003497b4();
  rt_003509a4();
  v237 = rt_00027754(param_7);
  rt_0008f6c0();
  v227 = (code *)rt_00358d88();
  rt_0035284c(0xff);
  rt_00377824();
  rt_0034bec4();
  v230 = rt_00377824().lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034c330();
  rt_003504e8();
  v229 = (code *)rt_00377dcc();
  rt_000a6f88();
  v226 = v22;
  (*G_00658c00)(*(uint64_t *)(v28 + 0x40));
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
  (*G_00658c00)(*(uint64_t *)(v130 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034c074();
  rt_0008f6f4();
  rt_00027754();
  v2 = (code *)rt_0008f6f4();
  rt_003508e4();
  rt_00354ca8();
  v3 = (code *)rt_00377824();
  rt_0034ab20();
  rt_0007c1a4();
  (*G_00658c00)();
  rt_0034af20();
  v246 = rt_0035050c();
  rt_00377824(v246.lo,v246.hi,param_3,&G_0061014c);
  rt_003490b8(sp0x);
  (*G_00658c00)(*(uint64_t *)(v184 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*G_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*G_00658c00)();
  rt_0034b758();
  rt_0034ad00();
  v246 = rt_00350a04();
  v20 = rt_00377bec(v246.lo,v246.hi,v3).lo;
  v21 = rt_0034bc04();
  v239 = v20;
  v228 = v3;
  (*v198)(rt_0060e3fc,v21,0x200,v3);
  rt_0034dc20();
  v233 = rt_0060e3fc;
  v240 = v2;
  (*v139)(v18,rt_0060e3fc,param_3,v2);
  rt_0035764c(v201);
  rt_003508f0();
  (*v53)();
  v3 = v229;
  v215 = (uint64_t *)(v24 + 8);
  (*(code *)*v215)(v18,param_3);
  rt_0008412c();
  rt_00377bec();
  v234 = (code *)rt_0034d4b8();
  v4 = v225;
  v21 = rt_00351a74(v225);
  rt_00351378(v21,0x200);
  (*v42)();
  v241 = rt_0034cea8();
  v21 = v235;
  rt_0035348c();
  rt_0034db18();
  (*v120)();
  rt_0031c550(v201);
  rt_003511fc();
  v244 = param_3;
  rt_003508f0();
  v224 = (code *)(*v132)();
  v2 = (code *)rt_0031c460(v237);
  rt_0001df60();
  rt_0034b67c();
  v1 = v238;
  v211 = v20;
  (*v2)(v238,v21);
  v6 = *(code **)(v226 + 8);
  v243 = (code *)((unsigned long)(v226 + 8) & 0xffffffffffff | 0x4f8000000000000);
  pcStack_68 = v6;
  rt_003515cc();
  (*v6)();
  v21 = rt_00351a74(v4);
  v2 = v231;
  (*v234)(v21,0x200,v230);
  rt_0035348c();
  rt_00350938();
  rt_0035a08c();
  (*v141)();
  v21 = v245;
  rt_003195c8(v245);
  rt_00350104();
  rt_003513f0();
  (*v94)();
  rt_003515cc();
  (*v6)();
  rt_003507e0();
  (*v6)();
  rt_003549a8(v2);
  rt_0034bf84();
  v13 = (*v4)();
  if ((v13 & 1) == 0) {
    rt_0034bf84();
    v1 = (code *)(*v4)();
    rt_0034c0d0();
    v12 = (*v121)(v203,v2);
    if (((unsigned long)v1 & 1) == 0) {
      v15 = SBORROW8(v12,0x40);
      v19 = v12 + -0x40 < 0;
      v17 = v12 == 0x40;
      if (0x3f < v12) {
        v224 = (code *)0x0;
        rt_00358a68();
        rt_00349abc();
        rt_00352f48(stack_ptr);
        rt_0034f838();
        (*v70)();
        rt_00349b64(v2);
        rt_0034e5cc();
        v1 = (code *)(*v168)();
        rt_00353bac();
        v21 = rt_00352d04();
        v6 = v79;
        goto LBL_00226f0c;
      }
      rt_00358a68();
      rt_0034d520();
      rt_000e15d8();
      v6 = v52;
LBL_00226cc4:
      v12 = (*v6)();
      v6 = v244;
    }
    else {
      v12 = rt_00353bac();
      v11 = (uint64_t *)(v68 + 8);
      v15 = SBORROW8(v12,0x40);
      v19 = v12 + -0x40 < 0;
      v17 = v12 == 0x40;
      if (0x40 < v12) {
        v224 = (code *)0x0;
        rt_00358a68();
        rt_00349abc();
        rt_0034dc54();
        rt_0034bf94();
        (*v128)();
        rt_00349b64(v2);
        rt_00355e80();
        rt_0034f424();
        v1 = (code *)(*v109)();
        rt_003504c4(*v11);
        (*v164)();
        goto LBL_00226f1c;
      }
      rt_0034ad00();
      rt_00358828();
      rt_00350630();
      rt_00351148(&v229);
      rt_00377bec();
      rt_00348fb4();
      rt_003526b8(&v221);
      rt_0034b9f8();
      (*v77)();
      rt_0034d558();
      rt_00352f48(stack_ptr);
      rt_003517cc(v3);
      (*v178)();
      rt_00358a68();
      rt_0034af04();
      rt_00352d70();
      rt_0034e5cc();
      v1 = (code *)(*v62)();
      (*(code *)*v11)(v11,v203);
      v6 = v244;
      if (((unsigned long)v1 & 1) == 0) goto LBL_00226da0;
      rt_0034bfe0();
      rt_0009e234();
      v12 = (*v46)();
    }
    if (v12 == 0) {
LBL_00226f24:
      rt_003507bc();
      (*pcStack_68)();
      v21 = rt_0034f9d8(sp0x);
      (*v190)(v21,v220);
      rt_00350440();
      v21 = rt_003524e0(sp0x);
      rt_00352cbc(v21,0x100);
      rt_00355e8c();
      (*v149)();
      rt_00352b80(v223,v1,v6,v240);
      (*v58)();
      goto LBL_00226fa0;
    }
  }
  else {
    rt_0034c0d0();
    v6 = v242;
    rt_0009e234();
    v12 = (*v84)();
    v15 = SBORROW8(v12,0x3f);
    v19 = v12 + -0x3f < 0;
    v17 = v12 == 0x3f;
    if (v12 < 0x40) {
      rt_0034bfe0();
      rt_0009e234();
      v6 = v82;
      goto LBL_00226cc4;
    }
    v224 = (code *)0x0;
    rt_00349abc(v2);
    rt_0034dc54();
    rt_0034bf94();
    (*v169)();
    rt_00349b64(v2);
    rt_0034f424(v6);
    v1 = (code *)(*v45)();
    rt_00353bac();
    v6 = *(code **)(v37 + 8);
LBL_00226f0c:
    (*v6)(v21,v203);
LBL_00226f1c:
    v6 = v244;
    if (((unsigned long)v1 & 1) != 0) goto LBL_00226f24;
  }
LBL_00226da0:
  v13 = (unsigned long)v215 & 0xffffffffffff;
  rt_00352584(&v237);
  rt_00357c88();
  rt_003526b8(stack_ptr);
  rt_003510b8();
  (*v99)();
  rt_0034f754();
  v246 = rt_00350630();
  v1 = v217;
  v21 = rt_00377bec(v246.lo,v246.hi,v217).lo;
  rt_0031c640();
  rt_003518e8();
  rt_003510ac();
  v7 = (code *)(*v137)();
  rt_00352584(&v231);
  v10 = (code *)rt_0031c310();
  rt_00352098(&v235);
  rt_00350524();
  (*v10)();
  rt_0031c370(v1);
  rt_003526b8(stack_ptr);
  rt_00350524();
  v228 = v174;
  (*v174)();
  rt_000e15d8();
  rt_00353df0();
  v215 = (uint64_t *)(v13 | 0x4f8000000000000);
  (*v118)();
  rt_00352b8c(&v238);
  rt_0035a44c();
  rt_00350b00();
  v13 = (*v1)();
  v240 = v1;
  if ((v13 & 1) != 0) {
    rt_0034c0ec();
    rt_00350b00();
    v12 = (*v34)();
    v15 = SBORROW8(v12,0x3f);
    v1 = (code *)(v12 + -0x3f);
    v17 = v12 == 0x3f;
    if (0x3f < v12) {
LBL_00227178:
      v19 = (long)v1 < 0;
      v224 = v7;
      rt_00349abc(v203);
      rt_00351e48(&v220);
      rt_00352d94();
      rt_00352a1c();
      (*v26)();
      rt_00348c84(v203);
      rt_00350c2c();
      rt_003513c0();
      v13 = (*v116)();
      v3 = (code *)(v197 + 8);
      v1 = *(code **)v3;
      (*v1)(v7,v213);
      rt_003514d0();
      (*v1)();
      v2 = v7;
      goto LBL_002271f4;
    }
LBL_00227070:
    rt_0034b4d0();
    rt_00350b00();
    v8 = (code *)(*v173)();
    rt_00355ef8();
    v1 = *(code **)(v181 + 8);
    rt_003514d0();
    (*v1)();
    v12 = (long)v8 - (long)v7;
joined_r0x00227410:
    v17 = v8 == v7;
    v19 = v12 < 0;
    v15 = SBORROW8((long)v8,(long)v7);
    if ((long)v7 <= (long)v8) goto LBL_00227434;
LBL_002271fc:
    rt_00350bc0(&v234);
    rt_00359834();
    (*v142)();
    rt_00358cbc();
    (*pcStack_68)();
LBL_00227220:
    v21 = rt_0034f9d8(sp0x);
    (*v159)(v21,v220);
    v2 = v231;
    rt_0034d354();
    v13 = (*v4)();
    if ((v13 & 1) != 0) {
      rt_0034d354();
      v13 = (*v4)();
      if ((v13 & 1) == 0) {
        rt_0034d354();
        (*v4)();
        rt_0034bb94();
        rt_003557b4();
        v12 = (*v85)();
        if (((unsigned long)v2 & 1) != 0) {
          rt_003536dc(v249);
          if ((bool)v17 || v19 != v15) {
            rt_0034ad00();
            v21 = rt_00352b8c(&v242);
            rt_00351148(&v229,v21,v203);
            rt_00377bec();
            rt_00348fb4();
            rt_0034ae80();
            (*v73)();
            rt_0034cea8();
            rt_00351e48(sp0x);
            rt_0035169c(v210);
            (*v31)();
            rt_00348c84(v6);
            rt_003513c0(v242,v7);
            (*v69)();
            rt_00357760();
            rt_003516e4();
            (*v150)();
            if (((unsigned long)v2 & 1) == 0) {
              rt_0034b4d0();
              v246 = rt_00350b00();
              v203 = v246.lo;
              v6 = v246.hi;
              v3 = v48;
              goto LBL_002273a0;
            }
          }
          else {
            v224 = (code *)0x0;
            rt_00349abc(v6);
            rt_0034fb3c();
            (*v27)();
            rt_00348c84(v6);
            rt_0034c344(v242);
            (*v66)();
            rt_00357760();
            rt_003509bc();
            (*v105)();
            if (((unsigned long)v2 & 1) == 0) goto LBL_002273ac;
          }
LBL_00227dc4:
          rt_00352584(&v231);
          rt_0031c340();
          rt_003526b8(&v210);
          rt_00350524();
          (*v126)();
          rt_00352584(v247);
          rt_0031bc70();
          rt_00358f9c();
          v246 = rt_0008e388();
          (*v88)(v246.lo,v246.hi,v2);
          rt_0008e388();
          rt_00353df0();
          rt_003571ec();
          (*v57)();
          goto LBL_00226fa0;
        }
        if (v12 < 0x40) {
          rt_0034e104();
          v3 = v36;
          v2 = v6;
          goto LBL_002273a0;
        }
      }
      else {
        rt_0034eff8();
        v3 = v242;
        rt_0034f294();
        v12 = (*v108)();
        if (v12 < 0x40) {
          rt_003109b4(v2);
          v203 = (code *)rt_0034c6a4();
          v6 = v2;
          v3 = v125;
LBL_002273a0:
          v12 = (*v3)(v203,v6);
          if (v12 < 0) goto LBL_00227dc4;
        }
        else {
          v224 = (code *)0x0;
          rt_00349abc(v2);
          rt_0034dc54();
          rt_0034fe38();
          (*v100)();
          rt_00348c84(v2);
          rt_0034c5ac(v3);
          v2 = (code *)(*v112)();
          rt_00350bc0(v249);
          (*v133)(v6,v203);
          if (((unsigned long)v2 & 1) != 0) goto LBL_00227dc4;
        }
      }
    }
LBL_002273ac:
    rt_00352584(&v231);
    rt_0031c340();
    rt_00358f9c();
    rt_00350524();
    (*v44)();
    goto LBL_00226fa0;
  }
  rt_00350b00();
  (*v1)();
  rt_0034bb94();
  rt_00350b00();
  v12 = (*v138)();
  if (((unsigned long)v1 & 1) == 0) {
    if (v12 < 0x40) goto LBL_00227070;
    v15 = SBORROW8((long)v7,1);
    v1 = v7 + -1;
    v17 = v7 == (code *)((long)&__thread_bss_magic + 1);
    if (0 < (long)v7) goto LBL_00227178;
    rt_00355ef8();
    v1 = *(code **)(v35 + 8);
    rt_003514d0();
    (*v1)();
  }
  else {
    rt_003536dc(&v245);
    if ((bool)v17 || v19 != v15) {
      v239 = v21;
      rt_0035955c();
      rt_0034ad00();
      rt_003510dc();
      rt_00351148(&v215);
      rt_00377bec();
      rt_00348fb4();
      rt_0034ae80();
      (*v179)();
      rt_0034d558();
      rt_00351e48(&v220);
      rt_0035256c(v208);
      (*v124)();
      rt_00348c84(v203);
      rt_00350a34();
      rt_003513c0();
      v13 = (*v96)();
      v1 = *(code **)v3;
      rt_003516e4();
      (*v1)();
      if ((v13 & 1) == 0) {
        rt_0034bfe0();
        rt_00350b3c();
        v8 = (code *)(*v153)();
        rt_00350944();
        (*v1)();
        rt_00354058();
        v12 = (long)v8 - (long)v7;
        v2 = v203;
        v21 = v239;
        v3 = v212;
        goto joined_r0x00227410;
      }
      rt_00350944();
      (*v1)();
      goto LBL_002271fc;
    }
    v224 = v7;
    rt_00349abc(v203);
    rt_00352ca4(&v220);
    rt_00352d94();
    rt_00352a1c();
    (*v64)();
    rt_00348c84(v203);
    rt_0009e234();
    rt_003513c0();
    v13 = (*v129)();
    v3 = *(code **)v3;
    rt_003510dc();
    (*v3)();
    (*v3)(v212,v213);
    v1 = v3;
LBL_002271f4:
    if ((v13 & 1) != 0) goto LBL_002271fc;
  }
LBL_00227434:
  v8 = v229;
  v18 = rt_00350c14();
  v9 = (code *)(*v132)(v18,v201);
  v19 = SBORROW8((long)v9,(long)v7);
  v15 = (long)v9 - (long)v7 < 0;
  v17 = v9 == v7;
  if ((long)v9 < (long)v7) {
    v18 = rt_00350c14();
    (*v132)(v18,v201);
    v12 = rt_0035955c();
    v9 = v7 + -v12;
    rt_0034ad00();
    rt_00352c98(v232);
    v18 = rt_00355ea4();
    rt_00351148(&v241,v18,v8);
    v7 = (code *)rt_00377bec();
    rt_0034bc04();
    v18 = rt_003524e0(&v225);
    (*v92)(v18,0x200,v3,v7);
    rt_0034d558();
    rt_00351af8(&v223);
    v246 = rt_0034d1d0();
    (*v97)(v246.lo,v246.hi,v2);
    v15 = SBORROW8((long)v9,1);
    v3 = v9 + -1;
    v19 = (long)v3 < 0;
    v17 = v3 == (code *)0x0;
    if ((bool)v15) {
                    /* WARNING: Does not return */
      v2 = (code *)SW_BREAK(0x228910);
      (*v2)();
    }
    v224 = v3;
    rt_0031c460(v21);
    rt_003516fc();
    v239 = v21;
    rt_00356a08(v207,v10,&v224);
    (*v189)();
    v5 = *(code **)(v23 + 8);
    rt_003507d4();
    (*v80)();
    rt_003575b0();
    v18 = rt_00351e48(&v225);
    rt_00350ac4(v18,0x300);
    rt_00352b80();
    (*v81)();
    rt_003519b4(v248);
    v246 = rt_00350938(v7);
    rt_00355e8c(v246.lo,v246.hi,v2);
    (*v134)();
    rt_00352c98(v236);
    rt_0031c580();
    v18 = rt_0034d934();
    rt_00353cc0(v18,v207);
    (*v119)();
    rt_003508a8();
    rt_003566d8();
    (*v7)();
    rt_00351a74();
    v18 = rt_00351af8(&v225);
    rt_0034df34(v18,0x200);
    rt_00352b80();
    (*v43)();
    rt_00352a64();
    v246 = rt_00350938();
    rt_00355e8c(v246.lo,v246.hi,v200);
    (*v147)();
    rt_00350780(v2);
    rt_0035614c();
    rt_00351af8(v222);
    rt_00355e50();
    rt_0034e034();
    (*v166)();
    rt_003508a8();
    (*v7)();
    rt_003504f4();
    (*v7)();
    rt_00355100(sp0x);
    rt_003575bc();
    rt_003524e0(&v228);
    rt_00350b78();
    rt_00351900();
    (*v193)();
    rt_003507d4();
    (*v7)();
    v224 = v9;
    v21 = rt_0031c430(v21);
    rt_00352d28(v21,&v224);
    rt_003516fc();
    rt_00356a08();
    (*v194)();
    rt_00100efc();
    (*v7)();
    v21 = v237;
    v2 = (code *)rt_00310a74(v237);
    v3 = v238;
    rt_003530a4();
    rt_003514dc();
    rt_00351c64();
    (*v2)();
    v9 = (code *)rt_001679fc(v21);
    rt_0035053c(v209,v3,v221);
    (*v9)();
    rt_003509bc();
    (*pcStack_68)();
    rt_0034cdc8();
    v16 = rt_00377bec(v16,v203,v8).lo;
    rt_00310b08();
    rt_0034c5dc();
    rt_0034df74();
    v13 = (*v60)();
    v206 = v16;
    if ((v13 & 1) == 0) {
      rt_0034c4fc(v16);
      rt_000a6e14();
      rt_0034df74();
      v13 = (*v74)();
      rt_003504f4();
      rt_00355640();
      (*v7)();
      v3 = v229;
      if ((v13 & 1) != 0) {
        rt_00351a74();
        v7 = v225;
        rt_0035a540();
        rt_003538bc();
        (*v89)();
        v8 = v238;
        rt_00353480();
        rt_00350938();
        rt_0035a08c();
        (*v131)();
        rt_00351e48(sp0x);
        rt_0035063c(v209,v8);
        (*v9)();
        rt_003507d4();
        (*pcStack_68)();
        v8 = (code *)rt_00310a14(v21);
        rt_00084180();
        v13 = (*v8)();
        if ((v13 & 1) == 0) {
          rt_0034d354();
          v13 = (*v8)();
          rt_00310a44(v21);
          v16 = rt_0034b814();
          v12 = (*v188)(v16,v21);
          v15 = SBORROW8(v12,0x40);
          v19 = v12 + -0x40 < 0;
          v17 = v12 == 0x40;
          if ((v13 & 1) == 0) goto joined_r0x002280f8;
          if (v12 < 0x41) {
            v16 = rt_00350440().lo;
            rt_003538bc(v225,v16,0x100);
            (*v192)();
            rt_00353c78();
            rt_00350938();
            rt_0035a08c();
            (*v50)();
            rt_0034c61c(v21);
            rt_00310954();
            rt_0034a428();
            v13 = (*v104)();
            rt_003504f4();
            v8 = pcStack_68;
            v2 = v243;
            (*pcStack_68)();
            if ((v13 & 1) == 0) {
              rt_003507bc();
              (*v8)();
              goto LBL_002281a0;
            }
            v16 = rt_0034a034(v21);
            v12 = (*v98)(v16,v21);
            rt_003507bc();
            (*v8)();
            goto LBL_00228120;
          }
        }
        else {
          rt_00310a44(v21);
          v16 = rt_0034b814();
          v12 = (*v172)(v16,v21);
          v15 = SBORROW8(v12,0x3f);
          v19 = v12 + -0x3f < 0;
          v17 = v12 == 0x3f;
joined_r0x002280f8:
          if (v12 < 0x40) {
            v16 = rt_0034a034(v21);
            v12 = (*v158)(v16,v21);
            rt_003507bc();
            (*pcStack_68)();
LBL_00228120:
            v15 = SBORROW8(v12,1);
            v19 = v12 + -1 < 0;
            v17 = v12 == 1;
            v7 = v5;
            if ((bool)v17) goto LBL_002277d4;
            goto LBL_002281a0;
          }
        }
        v224 = (code *)((long)&__thread_bss_magic + 1);
        rt_0035041c();
        rt_0034fe38(v238,&v224,v49,v211);
        (*v2)();
        rt_00349b64(v21);
        rt_00351360();
        rt_0035063c();
        v13 = (*v63)();
        rt_003507d4();
        v8 = pcStack_68;
        (*pcStack_68)();
        rt_003507bc();
        (*v8)();
        rt_003566d8();
        if ((v13 & 1) != 0) goto LBL_002277d4;
      }
LBL_002281a0:
      rt_00358cbc();
      (*pcStack_68)();
    }
    else {
      rt_003504f4();
      rt_00355640();
      (*v7)();
      v3 = v229;
LBL_002277d4:
      v21 = rt_00351a74();
      rt_003538bc(v225,v21,0x200);
      (*v182)();
      rt_0034d1d0(v235);
      rt_0035a08c();
      (*v90)();
      v21 = rt_00310f34(v245);
      rt_000a6e14(v21);
      rt_0035063c();
      v13 = (*v87)();
      rt_003504f4();
      v8 = pcStack_68;
      v2 = v243;
      (*pcStack_68)();
      rt_0006b6f4();
      (*v8)();
      rt_00358720();
      v246 = rt_00351648();
      (*v154)(v246.lo,v246.hi,v3);
      if ((v13 & 1) == 0) {
        rt_0034af04(v237);
        rt_00310b08();
        v21 = rt_00351318();
        rt_0034d344(v21,v221);
        v13 = (*v102)();
        rt_003507d4();
        (*v8)();
        rt_00357250();
        v8 = v221;
        if ((v13 & 1) == 0) goto LBL_002281ac;
      }
      else {
        rt_00358cbc();
        (*v8)();
        rt_00357250();
        v8 = v238;
      }
      rt_00353130();
      v15 = SCARRY8(v176,1);
      v233 = (code *)(v176 + 1);
      v19 = (long)v233 < 0;
      v17 = v233 == (code *)0x0;
      if ((bool)v15) {
                    /* WARNING: Does not return */
        v2 = (code *)SW_BREAK(0x228914);
        (*v2)();
      }
      rt_00351af8(&v206);
      v21 = rt_00350c14();
      (*v10)(v21,v202);
      rt_00350524(v214);
      (*v228)();
      rt_000e72b0();
      rt_00353df0();
      rt_003571ec();
      (*v152)();
      rt_003508b4();
      rt_00356768();
      v13 = (*v202)();
      if ((v13 & 1) == 0) {
        rt_003508b4();
        (*v202)();
        rt_0034bb94();
        rt_003508b4();
        v12 = (*v95)();
        if (((unsigned long)v202 & 1) != 0) {
          rt_003536dc(&v245);
          if ((bool)v17 || v19 != v15) {
            rt_0034ad00();
            rt_003509b0();
            rt_00351148(&v215);
            rt_00377bec();
            rt_00348fb4();
            v227 = v3;
            rt_003526b8(&v205);
            rt_0034b9f8();
            (*v157)();
            rt_0034e74c();
            rt_00351af8(&v220);
            rt_00352b5c(v3);
            (*v32)();
            rt_00348c84(v14);
            rt_00350738();
            rt_00352b08();
            v13 = (*v196)();
            rt_0035a76c(v227);
            rt_00350a04();
            (*v1)();
            if ((v13 & 1) == 0) {
              rt_0034d054(v14);
              rt_00350944();
              v12 = (*v175)();
              rt_00350b6c();
              (*v1)();
              rt_00353130();
              v15 = SBORROW8(v12,v71);
              v19 = v12 - v71 < 0;
              v17 = v12 == v71;
              v3 = v229;
              v2 = v14;
              if (v71 <= v12) goto LBL_002281ac;
            }
            else {
              rt_00350b6c();
              (*v1)();
              v3 = v229;
            }
          }
          else {
            rt_00353130();
            v224 = v107;
            rt_00349abc(v14);
            rt_00352f48(&v220);
            rt_00352d94();
            rt_003569fc();
            (*v101)();
            rt_00348c84(v14);
            rt_003510dc();
            rt_00352b08();
            v13 = (*v177)();
            rt_003509b0();
            (*v1)();
            rt_00350b6c();
            (*v1)();
            v3 = v229;
            if ((v13 & 1) == 0) goto LBL_002281ac;
          }
LBL_00228780:
          (*pcStack_68)(v209,v3);
          rt_00355640(v204,v217);
          (*v7)();
          goto LBL_00227220;
        }
        if (v12 < 0x40) goto LBL_00228004;
        rt_00353130();
        v15 = SBORROW8((long)v41,1);
        v19 = (long)(v41 + -1) < 0;
        v17 = v41 == (code *)((long)&__thread_bss_magic + 1);
        if (0 < (long)v41) {
          v224 = v41;
          rt_00349abc(v14);
          rt_00351af8(&v220);
          rt_00352d94();
          rt_003569fc();
          (*v59)();
          rt_00348c84(v14);
          rt_00350738();
          rt_00352b08();
          v13 = (*v110)();
          rt_00355ef8();
          goto LBL_00228754;
        }
        rt_00355ef8();
        rt_00350b6c(v199_x00101 + 8);
        (*v1)();
      }
      else {
        rt_0034c0ec();
        rt_003508b4();
        v12 = (*v29)();
        v15 = SBORROW8(v12,0x3f);
        v19 = v12 + -0x3f < 0;
        v17 = v12 == 0x3f;
        if (v12 < 0x40) {
LBL_00228004:
          rt_0034b4d0();
          rt_003508b4();
          v12 = (*v161)();
          rt_00355ef8();
          rt_00350b6c(v163 + 8);
          (*v1)();
          rt_00353130();
          v15 = SBORROW8(v12,v103);
          v19 = v12 - v103 < 0;
          v17 = v12 == v103;
          if (v12 < v103) goto LBL_00228780;
        }
        else {
          rt_00353130();
          v224 = v156;
          rt_00349abc(v14);
          rt_00352f48(&v220);
          rt_00352d94();
          rt_003569fc();
          (*v148)();
          rt_00348c84(v14);
          rt_003510dc();
          rt_00352b08();
          v13 = (*v54)();
          rt_00355ef8();
          v8 = v2;
LBL_00228754:
          (*v1)(v8,v9);
          rt_00350b6c();
          (*v1)();
          if ((v13 & 1) != 0) goto LBL_00228780;
        }
      }
    }
LBL_002281ac:
    v1 = v231;
    rt_0034d354();
    (*v4)();
    v13 = rt_00354058();
    v3 = v6;
    if ((v13 & 1) == 0) {
LBL_00228334:
      v14 = (code *)0x0;
      v6 = v3;
    }
    else {
      rt_0034d354();
      v13 = (*v4)();
      if ((v13 & 1) != 0) {
        rt_0034eff8();
        v4 = v242;
        rt_0034f294();
        v12 = (*v114)();
        if (v12 < 0x40) {
          rt_003109b4(v1);
          v14 = (code *)rt_0034c6a4();
          v10 = v75;
          v6 = v1;
          v1 = v4;
LBL_00228324:
          v12 = (*v10)(v14,v6);
          v4 = v1;
          v6 = v3;
          if (v12 < 0) goto LBL_002288d4;
        }
        else {
          v224 = (code *)0x0;
          rt_00349abc(v1);
          rt_0034dc54();
          rt_0034fe38();
          (*v47)();
          rt_00348c84(v1);
          rt_0034c5ac(v4);
          v13 = (*v30)();
          rt_00350bc0(v249);
          (*v67)(v6,v203);
          v1 = v4;
          if ((v13 & 1) != 0) goto LBL_002288d4;
        }
        goto LBL_00228334;
      }
      rt_0034d354();
      (*v4)();
      rt_0034bb94();
      rt_003557b4();
      v12 = (*v115)();
      v3 = v244;
      v4 = v1;
      if (((unsigned long)v1 & 1) == 0) {
        v2 = v203;
        if (v12 < 0x40) {
          rt_0034e104();
          v14 = v203;
          v10 = v61;
          goto LBL_00228324;
        }
        goto LBL_00228334;
      }
      rt_003536dc(v249);
      if ((bool)v17 || v19 != v15) {
        rt_0034ad00();
        v21 = rt_00352b8c(&v242);
        rt_00351148(&v229,v21,v203);
        rt_00377bec();
        rt_00348fb4();
        rt_00351e48(&v221);
        rt_0034b9f8();
        (*v91)();
        rt_0034cea8();
        rt_003519b4(sp0x);
        rt_0035169c(v7);
        (*v140)();
        rt_00348c84(v6);
        v4 = v242;
        rt_00350c80();
        rt_003513c0();
        (*v113)();
        rt_00357760();
        rt_00350944();
        (*v171)();
        if (((unsigned long)v1 & 1) == 0) {
          rt_0034d504(v6);
          rt_00351414();
          (*v199_x00100)();
          rt_003582a8();
          v12 = rt_00354058();
          v1 = v4;
          v3 = v6;
          v2 = v203;
          if (-1 < v12) goto LBL_00228334;
          goto LBL_002288d4;
        }
        v14 = (code *)((long)&__thread_bss_magic + 1);
        rt_003582a8();
        rt_00354058();
        v2 = v203;
      }
      else {
        v224 = (code *)0x0;
        rt_00349abc(v6);
        rt_0034fb3c();
        (*v65)();
        rt_00348c84(v6);
        rt_0034c344(v242);
        (*v167)();
        rt_00357760();
        rt_003509bc();
        (*v170)();
        rt_003582a8();
        v3 = v6;
        if (((unsigned long)v1 & 1) == 0) goto LBL_00228334;
LBL_002288d4:
        v14 = (code *)((long)&__thread_bss_magic + 1);
        v4 = v1;
      }
    }
    v224 = v7;
    rt_00356840();
    rt_00350a70();
    v246 = rt_0035606c();
    rt_00377bec(v246.lo,v246.hi,v4);
    rt_00350950();
    rt_0016796c();
    rt_0034a07c();
    rt_00351e48(&v239);
    rt_0034f838();
    (*v183)();
    rt_0008f6c0(v203);
    rt_00350950();
    rt_00167a2c();
    rt_00352f48(&v233);
    rt_00100c38();
    rt_00351b78();
    (*v135)();
    rt_0035463c();
    v1 = v203 + 8;
    v3 = *(code **)v1;
    rt_00351384();
    (*v3)();
    rt_0035084c();
    (*v3)();
    rt_0031c1f0(v201);
    rt_00358f9c();
    rt_003518f4(v14,v2,v209);
    (*v144)();
    rt_00352698(sp0x);
    rt_0035a44c();
    rt_00355ea4();
    rt_0034df84();
    v13 = (*v14)();
    if ((v13 & 1) == 0) {
      rt_0034df84();
      v13 = (*v14)();
      rt_0034fe48();
      rt_0008e388();
      (*v86)();
      v12 = rt_003566d8();
      if ((v13 & 1) == 0) {
        if (v12 < 0x40) {
          rt_003109b4(v6);
          v21 = rt_0034c5ec();
          (*v76)(v21,v6);
          goto LBL_002285d4;
        }
      }
      else if (v12 < 0x41) {
        rt_00350440();
        rt_003524e0(&v225);
        rt_00350e34();
        rt_00352b80();
        (*v160)();
        v246 = rt_0034d1d0(v218);
        rt_00355e8c(v246.lo,v246.hi,v200);
        (*v106)();
        rt_00352584(sp0x);
        rt_00310954();
        rt_00350648();
        rt_0034b358();
        v13 = (*v155)();
        rt_00100efc();
        (*v7)();
        if ((v13 & 1) == 0) {
          rt_003507d4();
          (*v7)();
        }
        else {
          rt_003109b4(v6);
          v21 = rt_0034c5ec();
          (*v39)(v21,v6);
          rt_003507d4();
          (*v7)();
        }
        goto LBL_00226fa0;
      }
      v224 = (code *)0x0;
      rt_00349abc(v6);
      rt_0034f84c(v218);
      (*v122)();
      rt_00349fe0(v206);
      rt_0034b358(v204);
      (*v117)();
      rt_00100efc();
      (*v7)();
    }
    else {
      rt_0034fe48();
      rt_0008e388();
      v12 = (*v151)();
      if (v12 < 0x40) {
        rt_0034d054(v6);
        rt_0008e388();
        (*v83)();
        v7 = v5;
LBL_002285d4:
        rt_00355640(v204,v1);
        (*v7)();
        goto LBL_00226fa0;
      }
      v224 = (code *)0x0;
      rt_00349abc(v6);
      rt_0034f84c(v218);
      (*v127)();
      rt_00349fe0(v206);
      rt_0034b358(v204);
      (*v78)();
      rt_00100efc();
      (*v5)();
      v7 = v5;
    }
    (*v7)(v204,v1);
    goto LBL_00226fa0;
  }
  rt_00358cbc();
  v3 = pcStack_68;
  v2 = v243;
  (*pcStack_68)();
  v16 = rt_00350c14();
  v12 = (*v132)(v16,v201);
  v16 = v237;
  rt_0035690c(v237);
  v246 = rt_00359834(v238);
  rt_003507ec(v246.lo,v246.hi,v21);
  (*v143)();
  v224 = (code *)(v12 - (long)v7);
  rt_00349abc(v16);
  rt_00352d94(v235);
  (*v25)();
  rt_00319778(v245);
  rt_0034e034(v219,v238);
  (*v56)();
  rt_003508a8();
  (*v3)();
  rt_003515cc();
  (*v3)();
  v3 = v231;
  rt_0034d354();
  v13 = (*v4)();
  if ((v13 & 1) == 0) {
LBL_00227e6c:
    v21 = 0;
  }
  else {
    rt_0034d354();
    v13 = (*v4)();
    if ((v13 & 1) != 0) {
      rt_0034eff8();
      v4 = v242;
      rt_0034f294();
      v12 = (*v180)();
      if (v12 < 0x40) {
        rt_003109b4(v3);
        v1 = (code *)rt_0034c6a4();
        v14 = v123;
        v6 = v3;
        v3 = v4;
LBL_00227e5c:
        v12 = (*v14)(v1,v6);
        v4 = v3;
        if (v12 < 0) goto LBL_00228878;
      }
      else {
        v224 = (code *)0x0;
        rt_00349abc(v3);
        rt_0034dc54();
        rt_0034fe38();
        (*v191)();
        rt_00348c84(v3);
        rt_0034c5ac(v4);
        v13 = (*v162)();
        rt_00350bc0(v249);
        (*v40)(v6,v203);
        v3 = v4;
        v2 = v7;
        if ((v13 & 1) != 0) goto LBL_00228878;
      }
      goto LBL_00227e6c;
    }
    rt_0035955c();
    rt_0034d354();
    (*v4)();
    rt_0034bb94();
    rt_003557b4();
    v12 = (*v38)();
    v7 = v233;
    v4 = v3;
    if (((unsigned long)v3 & 1) == 0) {
      if (v12 < 0x40) {
        rt_0034e104();
        v1 = v203;
        v14 = v195;
        goto LBL_00227e5c;
      }
      goto LBL_00227e6c;
    }
    rt_003536dc(v249);
    v7 = v201;
    if ((bool)v17 || v15 != v19) {
      rt_0034ad00();
      v21 = rt_00352b8c(&v242);
      rt_00351148(&v229,v21,v203);
      rt_00377bec();
      rt_00348fb4();
      rt_0034ae80();
      (*v111)();
      rt_0034cea8();
      rt_00358ad4();
      rt_0035287c();
      rt_0035169c();
      (*v72)();
      rt_00348c84(v6);
      v4 = v242;
      rt_0009e234();
      rt_003513c0();
      (*v146)();
      rt_00357760();
      rt_003510dc();
      (*v186)();
      if (((unsigned long)v3 & 1) == 0) {
        rt_0034d504(v6);
        rt_00351414();
        (*v136)();
        v12 = rt_00354058();
        v3 = v4;
        if (-1 < v12) goto LBL_00227e6c;
        goto LBL_00228878;
      }
      v21 = 1;
      rt_00354058();
    }
    else {
      v224 = (code *)0x0;
      rt_00349abc(v6);
      rt_0034fb3c();
      (*v51)();
      rt_00348c84(v6);
      rt_0034c344(v242);
      (*v145)();
      rt_00357760();
      rt_003509bc();
      (*v187)();
      rt_00354058();
      if (((unsigned long)v3 & 1) == 0) goto LBL_00227e6c;
LBL_00228878:
      v21 = 1;
      v4 = v3;
    }
  }
  v224 = v7;
  rt_00356840();
  rt_00350a70();
  v246 = rt_0035606c();
  rt_00377bec(v246.lo,v246.hi,v4);
  rt_00350950();
  rt_0016796c();
  rt_0034a07c();
  rt_00351af8(&v239);
  rt_0034f838();
  (*v55)();
  rt_0008f6c0(v203);
  rt_00350950();
  rt_00167a2c();
  rt_00352ca4(&v233);
  rt_00351360();
  rt_00351b78();
  (*v165)();
  rt_0035463c();
  v3 = *(code **)(v203 + 8);
  rt_0035084c();
  (*v3)();
  rt_00351384();
  (*v3)();
  rt_0031c1f0(v201);
  rt_00358f9c();
  rt_003518f4(v21,v2,v219);
  (*v33)();
LBL_00226fa0:
  v21 = rt_00353034();
  rt_0008e500(v21,v202);
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
  FUN_00226320(v2);
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
  code *v7;
  code *v6;
  long v9;
  long v3;
  long v5;
  long v4;
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
  (*v7)();
  rt_00350bf0();
  rt_00351584();
  v2 = rt_00365b6c();
  if (v2 == 0) {
    rt_0034e68c();
    rt_000839d8();
    v1 = v3;
  }
  else {
    rt_0034befc();
    rt_000839d8();
    rt_0034b3e8();
    (**(code **)(v5 + 0x10))(v10);
    rt_003561dc();
    v1 = v4;
  }
  rt_00100efc(*(uint64_t *)(v1 + 8));
  (*v6)();
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
  uint64_t v1;
  uint8_t v15;
  uint32_t v4;
  long v12;
  code *v8;
  code *v7;
  code *v6;
  code *v11;
  code *v9;
  long v10;
  long v5;
  uint64_t v14;
  uint64_t v3;
  uint64_t v13;
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
  v1 = *(uint64_t *)(v16.lo + 0x20);
  rt_00350944();
  rt_000dbcc8();
  rt_00357c88(v1);
  v3 = *(uint64_t *)(v16.hi + 0x18);
  v16 = rt_003510ac();
  (*v11)(v16.lo,v16.hi,v2,v1);
  rt_00349f3c();
  if ((bool)v15) {
    rt_00353f44(*(uint64_t *)(v10 + 8));
    (*v8)();
    v4 = 2;
  }
  else {
    rt_00354810();
    rt_003508c0();
    (*v9)();
    rt_0034a30c(v3);
    rt_0034beec(v14);
    v4 = (*v7)();
    rt_003505e8(*(uint64_t *)(v5 + 8));
    (*v6)();
    v4 = v4 & 1;
  }
  rt_0008e500(v4,v13);
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


