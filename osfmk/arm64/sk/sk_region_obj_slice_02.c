/* Recreated from cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary; estimates unless matched.
 *
 * Region 0x29a820-0x2a4340 (slice 02 of the cL4 object layer; 157 functions, 0x29c058-0x2a70d8).
 *
 * NOTE ON TRANSCRIPTION: this region is the continuation of the cL4 object-graph description /
 * reflection engine begun in sk_region_obj.c. It is dominated by Swift-runtime string and
 * UnsafeBufferPointer handling (StringUTF8View iteration, UTF-8/UTF-16 decode, "Invalid slice",
 * "Not contiguous UTF-16", "UnsafeBufferPointer with negative count", "String index is out of
 * bounds", "Unexpectedly found nil while unwrapping", "Fatal error" strings), plus the object
 * alloc/free/retain path through the large shared cL4 runtime library OUTSIDE this slice. Those
 * callees are out of scope and declared below as externs named rt_<addr> (the FUN_ address is
 * preserved in a trailing comment), using the C "unspecified parameters" form (void f();) because
 * their signatures are outside this slice. 16-byte-returning helpers return sk_u128_t and scalar
 * uses take the .lo word; noreturn Swift fatal errors call rt_001afe4c (FUN_001afe4c).
 *
 * Confidence: medium (Swift-runtime string arithmetic and UnsafeBufferPointer indexing predominate;
 * object-service loops with heavy indirect dispatch appear throughout). */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* 128-bit word-pair used by the 16-byte-return runtime helpers. */
typedef struct sk_u128 { word_t lo; word_t hi; } sk_u128_t;
/* Function pointer to the (unspecified-arity) shared runtime; also the callable type for the code*
 * values the decompiler recovers from method/vtable slots. */
typedef void (*sk_fnptr)();
/* Generic placeholder for the indirect (vtable/closure) dispatches the decompiler
 * recovers through register-based targets that are unrecoverable in this slice. */
extern void rt__indirect();

/* Ghidra "SoftwareBreakpoint(n,pc)" artifacts: unrecoverable in-kernel trap; nulled for analysis. */
#define SoftwareBreakpoint(n,pc) ((void*)0)
/* Ghidra's 32-bit unsigned word type. */
typedef uint32_t uint;

/* ---- global data / labels referenced by this region (FUN_/DAT_ ground truth) ---- */
extern unsigned char DAT_004c4010[];
extern unsigned char DAT_004e80c0[];
extern unsigned char DAT_004e9a4c[];
extern unsigned char DAT_004f1960[];
extern unsigned char DAT_00612b58[];
extern unsigned char DAT_006575f8[];
extern unsigned char DAT_00657778[];   /* grow-register backing buffer */
extern word_t DAT_00657788;            /* grow-register count */
extern word_t DAT_00657790;            /* grow-register size */
extern unsigned int DAT_00657798[];    /* grow-register 32-bit slots */
extern void (*DAT_00658c00)();         /* object/vtable dispatch function pointer */
extern unsigned char DAT_005be7c0[];
extern unsigned char DAT_00010004[];
extern unsigned char DAT_00346964[];
/* String literals recovered by Ghidra (address in the symbol name suffix). */
extern char s_Not_contiguous_UTF_16_005d0690[];
extern char s_Fatal_error_005accd0[];
extern char s_Swift_UnsafeBufferPointer_swift_005cdc10[];
extern char s_UnsafeMutableBufferPointer_with_n_005cdbe0[];
extern char s_UnsafeMutableBufferPointer_has_a_005cdc30[];
extern char s_UnsafeBufferPointer_with_negativ_005cdf60[];
extern char s_Unexpectedly_found_nil_while_unw_005cd7d0[];
extern char s_Swift_String_swift_005ce680[];
extern char s_Invalid_slice_005cfa58[];
extern char s_String_index_is_out_of_bounds_005ce6a0[];
extern char s_Swift_StringUTF8View_swift_005d0670[];
/* Code labels used as closure/indirect targets. */
extern char LAB_000e0fc0;
extern char LAB_0029f9ec;
extern char LAB_002a6794;

/* ---- shared runtime library (out of scope for this slice) ---- */
extern sk_u128_t rt_00002534(); /* FUN_00002534 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00002834(); /* FUN_00002834 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00019858(); /* FUN_00019858 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0001a1c8(); /* FUN_0001a1c8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0001d540(); /* FUN_0001d540 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0001da84(); /* FUN_0001da84 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00027724(); /* FUN_00027724 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00027754(); /* FUN_00027754 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00027788(); /* FUN_00027788 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000277b8(); /* FUN_000277b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00041138(); /* FUN_00041138 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000651bc(); /* FUN_000651bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0006869c(); /* FUN_0006869c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00068e14(); /* FUN_00068e14 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0006b2ec(); /* FUN_0006b2ec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0006b3f4(); /* FUN_0006b3f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0006b42c(); /* FUN_0006b42c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0006b674(); /* FUN_0006b674 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0006b6f4(); /* FUN_0006b6f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0006f768(); /* FUN_0006f768 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00077708(); /* FUN_00077708 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000777d4(); /* FUN_000777d4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00077888(); /* FUN_00077888 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00077894(); /* FUN_00077894 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000778fc(); /* FUN_000778fc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0007c028(); /* FUN_0007c028 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0007c1a4(); /* FUN_0007c1a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0007c1c4(); /* FUN_0007c1c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0008409c(); /* FUN_0008409c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0008412c(); /* FUN_0008412c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00084174(); /* FUN_00084174 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00084180(); /* FUN_00084180 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00084220(); /* FUN_00084220 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00084234(); /* FUN_00084234 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0008e34c(); /* FUN_0008e34c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0008e388(); /* FUN_0008e388 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0008e500(); /* FUN_0008e500 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0008e518(); /* FUN_0008e518 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0009461c(); /* FUN_0009461c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0009e234(); /* FUN_0009e234 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000a0c8c(); /* FUN_000a0c8c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000a6894(); /* FUN_000a6894 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000a68c4(); /* FUN_000a68c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000a68f4(); /* FUN_000a68f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000a6e14(); /* FUN_000a6e14 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000a6f68(); /* FUN_000a6f68 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000a6f88(); /* FUN_000a6f88 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000a6fe0(); /* FUN_000a6fe0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000aa4ec(); /* FUN_000aa4ec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000b4390(); /* FUN_000b4390 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000b43d0(); /* FUN_000b43d0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000b43e8(); /* FUN_000b43e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000bd3a4(); /* FUN_000bd3a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000dbd0c(); /* FUN_000dbd0c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000dbe70(); /* FUN_000dbe70 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000dbf08(); /* FUN_000dbf08 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000e15d8(); /* FUN_000e15d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00100c38(); /* FUN_00100c38 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00100efc(); /* FUN_00100efc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001145b0(); /* FUN_001145b0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00115080(); /* FUN_00115080 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00117d14(); /* FUN_00117d14 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0011aa70(); /* FUN_0011aa70 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0011d7e8(); /* FUN_0011d7e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0011e71c(); /* FUN_0011e71c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00167658(); /* FUN_00167658 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001676cc(); /* FUN_001676cc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0018de98(); /* FUN_0018de98 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0019d40c(); /* FUN_0019d40c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0019e690(); /* FUN_0019e690 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001a05a8(); /* FUN_001a05a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001a0870(); /* FUN_001a0870 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001a09bc(); /* FUN_001a09bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001a157c(); /* FUN_001a157c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001a1648(); /* FUN_001a1648 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001a26e0(); /* FUN_001a26e0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001a89a8(); /* FUN_001a89a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001afa84(); /* FUN_001afa84 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001afe4c(); /* FUN_001afe4c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001b1d5c(); /* FUN_001b1d5c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001b1ff0(); /* FUN_001b1ff0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001b798c(); /* FUN_001b798c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001bbec4(); /* FUN_001bbec4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001d97b4(); /* FUN_001d97b4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001d9840(); /* FUN_001d9840 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001dd374(); /* FUN_001dd374 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001de8a8(); /* FUN_001de8a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001ded00(); /* FUN_001ded00 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001e3f70(); /* FUN_001e3f70 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001e4cbc(); /* FUN_001e4cbc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001eaec4(); /* FUN_001eaec4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001ee030(); /* FUN_001ee030 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001ff1a4(); /* FUN_001ff1a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001ff4e0(); /* FUN_001ff4e0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00200b38(); /* FUN_00200b38 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00216b88(); /* FUN_00216b88 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0021927c(); /* FUN_0021927c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00219370(); /* FUN_00219370 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0021947c(); /* FUN_0021947c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00219554(); /* FUN_00219554 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0021a660(); /* FUN_0021a660 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0021b1a4(); /* FUN_0021b1a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0021b91c(); /* FUN_0021b91c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0021c41c(); /* FUN_0021c41c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0022d2f4(); /* FUN_0022d2f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002509d8(); /* FUN_002509d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002527e8(); /* FUN_002527e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00262e9c(); /* FUN_00262e9c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0026398c(); /* FUN_0026398c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00263e20(); /* FUN_00263e20 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00267510(); /* FUN_00267510 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00268540(); /* FUN_00268540 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0026bd30(); /* FUN_0026bd30 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0026bd5c(); /* FUN_0026bd5c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00271fa0(); /* FUN_00271fa0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00272fc0(); /* FUN_00272fc0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0028e8c0(); /* FUN_0028e8c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00291d70(); /* FUN_00291d70 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00291ee0(); /* FUN_00291ee0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00298530(); /* FUN_00298530 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00298980(); /* FUN_00298980 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0029ac08(); /* FUN_0029ac08 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0029ac60(); /* FUN_0029ac60 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0029ae68(); /* FUN_0029ae68 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a7268(); /* FUN_002a7268 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a74f8(); /* FUN_002a74f8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a88bc(); /* FUN_002a88bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a8954(); /* FUN_002a8954 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a8a88(); /* FUN_002a8a88 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a8ca0(); /* FUN_002a8ca0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a8d04(); /* FUN_002a8d04 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a8e28(); /* FUN_002a8e28 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a919c(); /* FUN_002a919c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a92b8(); /* FUN_002a92b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a93b8(); /* FUN_002a93b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a999c(); /* FUN_002a999c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a9ba8(); /* FUN_002a9ba8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002ab130(); /* FUN_002ab130 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002ab8ac(); /* FUN_002ab8ac (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002acbb8(); /* FUN_002acbb8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002ad480(); /* FUN_002ad480 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002ad4fc(); /* FUN_002ad4fc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002ad608(); /* FUN_002ad608 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002ae028(); /* FUN_002ae028 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002ae098(); /* FUN_002ae098 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002af340(); /* FUN_002af340 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002af4d0(); /* FUN_002af4d0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002af6e4(); /* FUN_002af6e4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002af74c(); /* FUN_002af74c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002af844(); /* FUN_002af844 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002afd38(); /* FUN_002afd38 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002afee0(); /* FUN_002afee0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002afeec(); /* FUN_002afeec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002b1104(); /* FUN_002b1104 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002b141c(); /* FUN_002b141c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002b24b8(); /* FUN_002b24b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002b273c(); /* FUN_002b273c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002b5ba0(); /* FUN_002b5ba0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002b8444(); /* FUN_002b8444 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002bbcd8(); /* FUN_002bbcd8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002bc448(); /* FUN_002bc448 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002c2da4(); /* FUN_002c2da4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002c6aac(); /* FUN_002c6aac (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002c6d00(); /* FUN_002c6d00 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002c7020(); /* FUN_002c7020 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00310924(); /* FUN_00310924 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00310d68(); /* FUN_00310d68 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00319320(); /* FUN_00319320 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00319338(); /* FUN_00319338 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00319688(); /* FUN_00319688 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0031be18(); /* FUN_0031be18 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0031e030(); /* FUN_0031e030 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0031e084(); /* FUN_0031e084 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0031e0d4(); /* FUN_0031e0d4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0031e104(); /* FUN_0031e104 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0031e210(); /* FUN_0031e210 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0031e240(); /* FUN_0031e240 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0031e258(); /* FUN_0031e258 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0031e2ac(); /* FUN_0031e2ac (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00344e54(); /* FUN_00344e54 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00346774(); /* FUN_00346774 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003469d8(); /* FUN_003469d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00347d60(); /* FUN_00347d60 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00347da8(); /* FUN_00347da8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00347de8(); /* FUN_00347de8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00347f2c(); /* FUN_00347f2c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348034(); /* FUN_00348034 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003480ac(); /* FUN_003480ac (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348160(); /* FUN_00348160 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003481fc(); /* FUN_003481fc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348244(); /* FUN_00348244 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348304(); /* FUN_00348304 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003484e4(); /* FUN_003484e4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348548(); /* FUN_00348548 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348614(); /* FUN_00348614 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003486b8(); /* FUN_003486b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003487a4(); /* FUN_003487a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034883c(); /* FUN_0034883c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348898(); /* FUN_00348898 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003488bc(); /* FUN_003488bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003489c0(); /* FUN_003489c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003489dc(); /* FUN_003489dc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348a34(); /* FUN_00348a34 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348b40(); /* FUN_00348b40 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348bbc(); /* FUN_00348bbc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348bd8(); /* FUN_00348bd8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348d64(); /* FUN_00348d64 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348e00(); /* FUN_00348e00 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348e18(); /* FUN_00348e18 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348e48(); /* FUN_00348e48 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00349444(); /* FUN_00349444 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003494e8(); /* FUN_003494e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00349580(); /* FUN_00349580 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003496b0(); /* FUN_003496b0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034975c(); /* FUN_0034975c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003497b4(); /* FUN_003497b4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003497c8(); /* FUN_003497c8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003497ec(); /* FUN_003497ec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00349844(); /* FUN_00349844 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034987c(); /* FUN_0034987c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034998c(); /* FUN_0034998c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003499dc(); /* FUN_003499dc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00349a04(); /* FUN_00349a04 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00349bfc(); /* FUN_00349bfc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00349cbc(); /* FUN_00349cbc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00349db0(); /* FUN_00349db0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00349fcc(); /* FUN_00349fcc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a180(); /* FUN_0034a180 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a210(); /* FUN_0034a210 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a260(); /* FUN_0034a260 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a274(); /* FUN_0034a274 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a2f8(); /* FUN_0034a2f8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a390(); /* FUN_0034a390 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a3b0(); /* FUN_0034a3b0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a3d8(); /* FUN_0034a3d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a69c(); /* FUN_0034a69c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a880(); /* FUN_0034a880 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a9c0(); /* FUN_0034a9c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034aa54(); /* FUN_0034aa54 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ab20(); /* FUN_0034ab20 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ae58(); /* FUN_0034ae58 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ae94(); /* FUN_0034ae94 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034aee4(); /* FUN_0034aee4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b0c4(); /* FUN_0034b0c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b278(); /* FUN_0034b278 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b318(); /* FUN_0034b318 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b3d8(); /* FUN_0034b3d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b3e8(); /* FUN_0034b3e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b430(); /* FUN_0034b430 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b57c(); /* FUN_0034b57c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b730(); /* FUN_0034b730 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b758(); /* FUN_0034b758 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b788(); /* FUN_0034b788 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b7c8(); /* FUN_0034b7c8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b7e4(); /* FUN_0034b7e4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b824(); /* FUN_0034b824 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b85c(); /* FUN_0034b85c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b87c(); /* FUN_0034b87c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b89c(); /* FUN_0034b89c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b918(); /* FUN_0034b918 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ba28(); /* FUN_0034ba28 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ba38(); /* FUN_0034ba38 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ba68(); /* FUN_0034ba68 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034bb84(); /* FUN_0034bb84 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034bd90(); /* FUN_0034bd90 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034bdfc(); /* FUN_0034bdfc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034bf1c(); /* FUN_0034bf1c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034bf64(); /* FUN_0034bf64 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034bfb4(); /* FUN_0034bfb4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c064(); /* FUN_0034c064 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c094(); /* FUN_0034c094 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c0a4(); /* FUN_0034c0a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c1f8(); /* FUN_0034c1f8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c280(); /* FUN_0034c280 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c344(); /* FUN_0034c344 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c5bc(); /* FUN_0034c5bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c694(); /* FUN_0034c694 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c6b4(); /* FUN_0034c6b4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c6d4(); /* FUN_0034c6d4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c818(); /* FUN_0034c818 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034c840(); /* FUN_0034c840 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034cbb0(); /* FUN_0034cbb0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034cbd8(); /* FUN_0034cbd8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ce08(); /* FUN_0034ce08 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034cfb4(); /* FUN_0034cfb4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034cff4(); /* FUN_0034cff4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034d004(); /* FUN_0034d004 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034d090(); /* FUN_0034d090 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034d180(); /* FUN_0034d180 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034d3b4(); /* FUN_0034d3b4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034d3f4(); /* FUN_0034d3f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034d6d8(); /* FUN_0034d6d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034d788(); /* FUN_0034d788 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034da18(); /* FUN_0034da18 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034da28(); /* FUN_0034da28 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034daa8(); /* FUN_0034daa8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034db08(); /* FUN_0034db08 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034db48(); /* FUN_0034db48 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034db78(); /* FUN_0034db78 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034de14(); /* FUN_0034de14 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034de9c(); /* FUN_0034de9c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034dfb4(); /* FUN_0034dfb4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034e0b4(); /* FUN_0034e0b4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034e208(); /* FUN_0034e208 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034e2e4(); /* FUN_0034e2e4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034e314(); /* FUN_0034e314 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034e56c(); /* FUN_0034e56c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034e63c(); /* FUN_0034e63c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034e73c(); /* FUN_0034e73c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034e9e8(); /* FUN_0034e9e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ec0c(); /* FUN_0034ec0c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ed68(); /* FUN_0034ed68 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034eda8(); /* FUN_0034eda8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ee98(); /* FUN_0034ee98 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ef38(); /* FUN_0034ef38 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034f314(); /* FUN_0034f314 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034f414(); /* FUN_0034f414 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034f444(); /* FUN_0034f444 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034fb60(); /* FUN_0034fb60 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034fb74(); /* FUN_0034fb74 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034fb9c(); /* FUN_0034fb9c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034fcac(); /* FUN_0034fcac (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034fdf8(); /* FUN_0034fdf8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034fe90(); /* FUN_0034fe90 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ff3c(); /* FUN_0034ff3c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034ff78(); /* FUN_0034ff78 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003501a8(); /* FUN_003501a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350258(); /* FUN_00350258 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350298(); /* FUN_00350298 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003502a8(); /* FUN_003502a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035037c(); /* FUN_0035037c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350410(); /* FUN_00350410 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350428(); /* FUN_00350428 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350464(); /* FUN_00350464 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350470(); /* FUN_00350470 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035047c(); /* FUN_0035047c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350488(); /* FUN_00350488 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350494(); /* FUN_00350494 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003504a0(); /* FUN_003504a0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003504ac(); /* FUN_003504ac (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003504b8(); /* FUN_003504b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003504c4(); /* FUN_003504c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003504d0(); /* FUN_003504d0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003504f4(); /* FUN_003504f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350500(); /* FUN_00350500 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350518(); /* FUN_00350518 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350524(); /* FUN_00350524 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350530(); /* FUN_00350530 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035053c(); /* FUN_0035053c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350548(); /* FUN_00350548 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350560(); /* FUN_00350560 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003505c4(); /* FUN_003505c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003505e8(); /* FUN_003505e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003505f4(); /* FUN_003505f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350600(); /* FUN_00350600 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350618(); /* FUN_00350618 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350624(); /* FUN_00350624 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035066c(); /* FUN_0035066c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003506b0(); /* FUN_003506b0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350720(); /* FUN_00350720 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350738(); /* FUN_00350738 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350774(); /* FUN_00350774 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003507bc(); /* FUN_003507bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003507e0(); /* FUN_003507e0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350804(); /* FUN_00350804 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035084c(); /* FUN_0035084c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035089c(); /* FUN_0035089c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003508a8(); /* FUN_003508a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003508c0(); /* FUN_003508c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003508d8(); /* FUN_003508d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003508f0(); /* FUN_003508f0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350950(); /* FUN_00350950 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350968(); /* FUN_00350968 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350974(); /* FUN_00350974 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035098c(); /* FUN_0035098c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003509bc(); /* FUN_003509bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003509d4(); /* FUN_003509d4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003509ec(); /* FUN_003509ec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350a04(); /* FUN_00350a04 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350a28(); /* FUN_00350a28 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350a34(); /* FUN_00350a34 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350a64(); /* FUN_00350a64 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350a94(); /* FUN_00350a94 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350af4(); /* FUN_00350af4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350b00(); /* FUN_00350b00 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350b0c(); /* FUN_00350b0c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350b30(); /* FUN_00350b30 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350b3c(); /* FUN_00350b3c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350b48(); /* FUN_00350b48 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350b90(); /* FUN_00350b90 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350bf0(); /* FUN_00350bf0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350bfc(); /* FUN_00350bfc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350c2c(); /* FUN_00350c2c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350c38(); /* FUN_00350c38 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350d14(); /* FUN_00350d14 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350df4(); /* FUN_00350df4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350ed0(); /* FUN_00350ed0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350efc(); /* FUN_00350efc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351088(); /* FUN_00351088 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003510ac(); /* FUN_003510ac (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003510b8(); /* FUN_003510b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003510c4(); /* FUN_003510c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351160(); /* FUN_00351160 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035116c(); /* FUN_0035116c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003511c0(); /* FUN_003511c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003511cc(); /* FUN_003511cc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003511d8(); /* FUN_003511d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351214(); /* FUN_00351214 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035125c(); /* FUN_0035125c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003512c0(); /* FUN_003512c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351330(); /* FUN_00351330 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351354(); /* FUN_00351354 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351360(); /* FUN_00351360 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003513c0(); /* FUN_003513c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003513fc(); /* FUN_003513fc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351414(); /* FUN_00351414 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351438(); /* FUN_00351438 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351488(); /* FUN_00351488 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003514a0(); /* FUN_003514a0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003514b8(); /* FUN_003514b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351554(); /* FUN_00351554 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035156c(); /* FUN_0035156c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003515d8(); /* FUN_003515d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351630(); /* FUN_00351630 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351648(); /* FUN_00351648 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003516cc(); /* FUN_003516cc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003516f0(); /* FUN_003516f0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351714(); /* FUN_00351714 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351750(); /* FUN_00351750 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351774(); /* FUN_00351774 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351790(); /* FUN_00351790 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003517c0(); /* FUN_003517c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003518c4(); /* FUN_003518c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035190c(); /* FUN_0035190c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035193c(); /* FUN_0035193c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035196c(); /* FUN_0035196c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003519e8(); /* FUN_003519e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351a38(); /* FUN_00351a38 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351a44(); /* FUN_00351a44 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351a50(); /* FUN_00351a50 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351a5c(); /* FUN_00351a5c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351a80(); /* FUN_00351a80 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351aec(); /* FUN_00351aec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351b78(); /* FUN_00351b78 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351bec(); /* FUN_00351bec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351c58(); /* FUN_00351c58 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351d18(); /* FUN_00351d18 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351d30(); /* FUN_00351d30 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351da8(); /* FUN_00351da8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351db4(); /* FUN_00351db4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351e20(); /* FUN_00351e20 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351e3c(); /* FUN_00351e3c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351ec0(); /* FUN_00351ec0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351ef8(); /* FUN_00351ef8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351f28(); /* FUN_00351f28 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351f88(); /* FUN_00351f88 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351fd0(); /* FUN_00351fd0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352088(); /* FUN_00352088 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003520dc(); /* FUN_003520dc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003520f8(); /* FUN_003520f8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352108(); /* FUN_00352108 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352314(); /* FUN_00352314 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352330(); /* FUN_00352330 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352350(); /* FUN_00352350 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352438(); /* FUN_00352438 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352480(); /* FUN_00352480 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003524a4(); /* FUN_003524a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003524c8(); /* FUN_003524c8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352738(); /* FUN_00352738 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003527a4(); /* FUN_003527a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035284c(); /* FUN_0035284c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352864(); /* FUN_00352864 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352894(); /* FUN_00352894 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352914(); /* FUN_00352914 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352938(); /* FUN_00352938 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035298c(); /* FUN_0035298c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003529bc(); /* FUN_003529bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352a34(); /* FUN_00352a34 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352af0(); /* FUN_00352af0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352b50(); /* FUN_00352b50 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352b98(); /* FUN_00352b98 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352bd4(); /* FUN_00352bd4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352c80(); /* FUN_00352c80 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352cb0(); /* FUN_00352cb0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352d40(); /* FUN_00352d40 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352e24(); /* FUN_00352e24 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352e54(); /* FUN_00352e54 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352e9c(); /* FUN_00352e9c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352ea8(); /* FUN_00352ea8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035300c(); /* FUN_0035300c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353034(); /* FUN_00353034 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353050(); /* FUN_00353050 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353100(); /* FUN_00353100 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353118(); /* FUN_00353118 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353130(); /* FUN_00353130 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353154(); /* FUN_00353154 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035316c(); /* FUN_0035316c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353238(); /* FUN_00353238 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353274(); /* FUN_00353274 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003532b8(); /* FUN_003532b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353360(); /* FUN_00353360 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003534e0(); /* FUN_003534e0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035351c(); /* FUN_0035351c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353528(); /* FUN_00353528 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353590(); /* FUN_00353590 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035359c(); /* FUN_0035359c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003535a8(); /* FUN_003535a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353724(); /* FUN_00353724 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353878(); /* FUN_00353878 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353888(); /* FUN_00353888 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003538a0(); /* FUN_003538a0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353918(); /* FUN_00353918 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353a30(); /* FUN_00353a30 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353a6c(); /* FUN_00353a6c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353a90(); /* FUN_00353a90 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353b40(); /* FUN_00353b40 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353b70(); /* FUN_00353b70 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353d64(); /* FUN_00353d64 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353e50(); /* FUN_00353e50 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353f14(); /* FUN_00353f14 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353f68(); /* FUN_00353f68 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353f88(); /* FUN_00353f88 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00353ff4(); /* FUN_00353ff4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354040(); /* FUN_00354040 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035407c(); /* FUN_0035407c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354140(); /* FUN_00354140 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003542dc(); /* FUN_003542dc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354404(); /* FUN_00354404 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354410(); /* FUN_00354410 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354458(); /* FUN_00354458 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354474(); /* FUN_00354474 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003544c8(); /* FUN_003544c8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354714(); /* FUN_00354714 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354744(); /* FUN_00354744 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003547c8(); /* FUN_003547c8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354828(); /* FUN_00354828 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035484c(); /* FUN_0035484c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003548d0(); /* FUN_003548d0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003548e8(); /* FUN_003548e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354954(); /* FUN_00354954 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354988(); /* FUN_00354988 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354a00(); /* FUN_00354a00 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354a28(); /* FUN_00354a28 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354a34(); /* FUN_00354a34 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354a58(); /* FUN_00354a58 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354b2c(); /* FUN_00354b2c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354b38(); /* FUN_00354b38 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354ba4(); /* FUN_00354ba4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354be0(); /* FUN_00354be0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354bec(); /* FUN_00354bec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354dc4(); /* FUN_00354dc4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354de8(); /* FUN_00354de8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354e0c(); /* FUN_00354e0c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354ef8(); /* FUN_00354ef8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354f34(); /* FUN_00354f34 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354f64(); /* FUN_00354f64 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003554c4(); /* FUN_003554c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355578(); /* FUN_00355578 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355624(); /* FUN_00355624 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355704(); /* FUN_00355704 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003557c8(); /* FUN_003557c8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003558c4(); /* FUN_003558c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355968(); /* FUN_00355968 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355b1c(); /* FUN_00355b1c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355b48(); /* FUN_00355b48 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355bdc(); /* FUN_00355bdc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355be8(); /* FUN_00355be8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355c10(); /* FUN_00355c10 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355c94(); /* FUN_00355c94 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355cb0(); /* FUN_00355cb0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355d90(); /* FUN_00355d90 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355d9c(); /* FUN_00355d9c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356078(); /* FUN_00356078 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003560a8(); /* FUN_003560a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035611c(); /* FUN_0035611c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356128(); /* FUN_00356128 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356134(); /* FUN_00356134 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356164(); /* FUN_00356164 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356170(); /* FUN_00356170 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035617c(); /* FUN_0035617c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356290(); /* FUN_00356290 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003562d4(); /* FUN_003562d4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356358(); /* FUN_00356358 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356364(); /* FUN_00356364 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356370(); /* FUN_00356370 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035638c(); /* FUN_0035638c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035642c(); /* FUN_0035642c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035646c(); /* FUN_0035646c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356590(); /* FUN_00356590 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003565a8(); /* FUN_003565a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356774(); /* FUN_00356774 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003568a8(); /* FUN_003568a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003568e8(); /* FUN_003568e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356930(); /* FUN_00356930 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035697c(); /* FUN_0035697c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356a20(); /* FUN_00356a20 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356c60(); /* FUN_00356c60 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356d20(); /* FUN_00356d20 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356e4c(); /* FUN_00356e4c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035701c(); /* FUN_0035701c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003573e8(); /* FUN_003573e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357440(); /* FUN_00357440 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357468(); /* FUN_00357468 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035754c(); /* FUN_0035754c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357628(); /* FUN_00357628 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035767c(); /* FUN_0035767c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003576bc(); /* FUN_003576bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003576ec(); /* FUN_003576ec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357794(); /* FUN_00357794 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003577b4(); /* FUN_003577b4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357850(); /* FUN_00357850 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357938(); /* FUN_00357938 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357964(); /* FUN_00357964 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357a00(); /* FUN_00357a00 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357ac0(); /* FUN_00357ac0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357b3c(); /* FUN_00357b3c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357c04(); /* FUN_00357c04 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357c44(); /* FUN_00357c44 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357c74(); /* FUN_00357c74 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357ca0(); /* FUN_00357ca0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357cb4(); /* FUN_00357cb4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357f74(); /* FUN_00357f74 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357fe4(); /* FUN_00357fe4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358004(); /* FUN_00358004 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358014(); /* FUN_00358014 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358034(); /* FUN_00358034 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358044(); /* FUN_00358044 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358074(); /* FUN_00358074 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358084(); /* FUN_00358084 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358308(); /* FUN_00358308 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358344(); /* FUN_00358344 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358374(); /* FUN_00358374 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035847c(); /* FUN_0035847c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003584a8(); /* FUN_003584a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003585e8(); /* FUN_003585e8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358738(); /* FUN_00358738 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358768(); /* FUN_00358768 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035896c(); /* FUN_0035896c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358990(); /* FUN_00358990 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358a80(); /* FUN_00358a80 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358a98(); /* FUN_00358a98 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358abc(); /* FUN_00358abc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358ae0(); /* FUN_00358ae0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358b0c(); /* FUN_00358b0c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358b90(); /* FUN_00358b90 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358be4(); /* FUN_00358be4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358d1c(); /* FUN_00358d1c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358d70(); /* FUN_00358d70 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358e00(); /* FUN_00358e00 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358fb4(); /* FUN_00358fb4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358fc8(); /* FUN_00358fc8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359244(); /* FUN_00359244 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003593a8(); /* FUN_003593a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003593c0(); /* FUN_003593c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359400(); /* FUN_00359400 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359424(); /* FUN_00359424 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359484(); /* FUN_00359484 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003594f4(); /* FUN_003594f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359640(); /* FUN_00359640 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003596d0(); /* FUN_003596d0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003599a0(); /* FUN_003599a0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359af8(); /* FUN_00359af8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359b18(); /* FUN_00359b18 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359c18(); /* FUN_00359c18 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359c84(); /* FUN_00359c84 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359df4(); /* FUN_00359df4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359ed4(); /* FUN_00359ed4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359ee0(); /* FUN_00359ee0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359f54(); /* FUN_00359f54 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359fb4(); /* FUN_00359fb4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a04c(); /* FUN_0035a04c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a080(); /* FUN_0035a080 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a0a4(); /* FUN_0035a0a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a0c4(); /* FUN_0035a0c4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a0d8(); /* FUN_0035a0d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a0f0(); /* FUN_0035a0f0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a104(); /* FUN_0035a104 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a110(); /* FUN_0035a110 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a11c(); /* FUN_0035a11c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a244(); /* FUN_0035a244 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a400(); /* FUN_0035a400 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a560(); /* FUN_0035a560 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a5a8(); /* FUN_0035a5a8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a6c0(); /* FUN_0035a6c0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035a8bc(); /* FUN_0035a8bc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035aaf0(); /* FUN_0035aaf0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035ab14(); /* FUN_0035ab14 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035ab20(); /* FUN_0035ab20 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035ac00(); /* FUN_0035ac00 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035ac1c(); /* FUN_0035ac1c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035ac70(); /* FUN_0035ac70 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035ace8(); /* FUN_0035ace8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00365b6c(); /* FUN_00365b6c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00369584(); /* FUN_00369584 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0036a804(); /* FUN_0036a804 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0036b118(); /* FUN_0036b118 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0036b270(); /* FUN_0036b270 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0036b6ac(); /* FUN_0036b6ac (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00376820(); /* FUN_00376820 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00377824(); /* FUN_00377824 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00377bec(); /* FUN_00377bec (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003a25d4(); /* FUN_003a25d4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003a2610(); /* FUN_003a2610 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003a261c(); /* FUN_003a261c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003d3550(); /* FUN_003d3550 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003d3964(); /* FUN_003d3964 (shared cL4 runtime library, out of scope) */

/* ---- in-slice forward declarations (defined below) ---- */
void sk_swift_str_prelude(void);                         /* 0029c058 */
word_t sk_swift_str_index_step(void);                    /* 0029c0b4 */
void sk_swift_str_grow_register(void);                   /* 0029c18c */
void sk_swift_str_append_obj(void);                      /* 0029c2bc */
void sk_swift_str_array_convert(void *a,void *b,long n); /* 0029c3a0 */
sk_u128_t sk_swift_str_array_map(word_t a,word_t b,long n); /* 0029c6bc */
void sk_swift_str_dispatch(void *a,void *b,long n,void *d); /* 0029cb88 */
void sk_swift_str_dispatch2(void);                       /* 0029d2dc */
void sk_swift_str_utf8_emit(void);                       /* 0029d3d8 */
long sk_swift_str_utf8_upper(char *p,long n,void *a,long c); /* 0029d454 */
sk_u128_t sk_swift_str_slice(void *a,long b,long c,long d,long e); /* 0029d4c0 */
word_t sk_swift_str_hash_dispatch(void *a,word_t b);     /* 0029d53c */
void sk_swift_str_append_char(void *a);                  /* 0029d560 */
void sk_swift_str_utf8_emit_lower(void);                 /* 0029d56c */
void sk_swift_str_utf8_encode(void *a,void *b,sk_fnptr c,void *d,void *e); /* 0029d5cc */
long sk_swift_str_utf8_lower(char *p,long n,void *a,long c); /* 0029d9e4 */
void sk_swift_str_append_char0(void *a);                 /* 0029da50 */
void sk_swift_str_finish(void);                          /* 0029da5c */
word_t sk_swift_str_read(void);                          /* 0029dac0 */
void sk_swift_str_fwd_a(void);                           /* 0029db08 */
void sk_swift_str_fwd_b(void);                           /* 0029db0c */
void sk_swift_str_write_escape(void);                    /* 0029db34 */
word_t sk_swift_str_index_next_char(void);               /* 0029dddc */
void sk_swift_str_free_a(void);                          /* 0029dee8 */
void sk_swift_str_free_b(void);                          /* 0029deec */
sk_u128_t sk_swift_str_element_at(long i);               /* 0029df10 */
sk_u128_t sk_swift_str_element_find(word_t i);           /* 0029df64 */
void sk_swift_str_desc(void *a,void *b,void *c);         /* 0029e00c */
void sk_swift_str_desc2(void *a,void *b,void *c);        /* 0029e1a0 */
void sk_swift_str_range_check(void *a,void *b,word_t c); /* 0029e370 */
void sk_swift_str_eq(void *a,void *b,long c,void *d,sk_fnptr e,sk_fnptr f); /* 0029e594 */
void sk_swift_str_compare_ci(void *a,void *b,void *c,void *d,word_t e); /* 0029e688 */
void sk_swift_str_compare_wrap(void);                    /* 0029e7f0 */
void sk_swift_str_is_ascii(void *a,void *b,word_t c,word_t d,word_t e,word_t f); /* 0029e840 */
void sk_swift_str_line_scan(void);                       /* 0029e8dc */
word_t sk_swift_str_has_ascii(void *a,void *b,word_t c); /* 0029ea8c */
bool sk_swift_str_ascii_check(word_t a);                 /* 0029ead8 */
word_t sk_swift_str_next_scalar(void);                   /* 0029eb58 */
void sk_swift_str_advance_line(void *a,void *b,word_t c);/* 0029ec2c */
word_t sk_swift_str_is_newline(word_t a,word_t b,word_t c); /* 0029ee18 */
word_t sk_swift_str_prev_boundary(void *a,void *b,word_t c); /* 0029ef1c */
word_t sk_swift_str_prev_utf8(word_t a,word_t b,word_t c); /* 0029f00c */
void sk_swift_str_scan_lines(void);                      /* 0029f0b0 */
void sk_swift_str_scan_lines2(void *a,void *b,word_t c); /* 0029f368 */
word_t sk_swift_str_is_sep(void *a,void *b,word_t c);    /* 0029f6a8 */
long sk_swift_str_prev_char(long a,word_t b,word_t c);   /* 0029f764 */
void sk_swift_str_replace(void *a,void *b,word_t c,word_t d); /* 0029f7f0 */
void sk_swift_str_map_call(void **a,void **b);           /* 0029f8e4 */
void sk_swift_str_map_call_inplace(void **a);            /* 0029f914 */
void sk_swift_str_store(void);                           /* 0029f944 */
void sk_swift_str_line_run(void);                        /* 0029f984 */
sk_u128_t sk_swift_str_slice_iter(void **a,void **b);    /* 0029f99c */
void sk_swift_str_flush(void);                           /* 0029fa0c */
void sk_swift_str_call(void **a,void **b);               /* 0029faac */
void sk_swift_str_call_inplace(void **a);                /* 0029fadc */
void sk_swift_str_init_empty(void);                      /* 0029fb24 */
void sk_swift_str_iter_call(void **a);                   /* 0029fb40 */
void sk_swift_str_iter_call2(void **a);                  /* 0029fb44 */
sk_u128_t sk_swift_str_next_break(void);                 /* 0029fb80 */
void sk_swift_str_next_break_slot(void **a);             /* 0029fcd8 */
word_t sk_swift_str_eq_sub(void *a,void *b,sk_fnptr c,sk_fnptr d,sk_fnptr e,sk_fnptr f); /* 0029fec0 */
void sk_swift_str_desc3(void);                           /* 002a02e4 */
sk_u128_t sk_swift_str_length(void);                     /* 002a043c */
void sk_swift_str_eq_run(void);                          /* 002a04cc */
word_t sk_swift_str_eq_sub2(void *a,void *b,long c,long d,sk_fnptr e,void *f); /* 002a06c4 */
uint sk_swift_str_bool(void);                            /* 002a0b5c */
void sk_swift_str_bool_run(void);                        /* 002a0b80 */
void sk_swift_str_eq_sub_run(void);                      /* 002a0ba4 */
word_t sk_swift_str_cmp2(void *a,void *b,long c);        /* 002a0c78 */
word_t sk_swift_str_nonempty(void);                      /* 002a0cb0 */
word_t sk_swift_str_cmp_ci(word_t a,word_t b,word_t c,word_t d,char e); /* 002a0cf8 */
word_t sk_swift_str_compare(word_t a,word_t b,word_t c,word_t d); /* 002a0d50 */
word_t sk_swift_str_compare_sub(void *a,long b,void *c,long d,char e,uint f); /* 002a0ed0 */
void sk_swift_str_compare_eq(void);                      /* 002a0f24 */
void sk_swift_str_transform(void *a,void *b,void *c,word_t d,word_t e,word_t f,void *g); /* 002a1120 */
long sk_swift_memcmp_limited(void *a,long b,void *c,long d); /* 002a1278 */
void sk_swift_str_compare_bytes(void);                   /* 002a12b4 */
long sk_swift_utf8_scanback(long a,long b,long c);       /* 002a1574 */
bool sk_swift_utf8_is_valid(uint c);                     /* 002a1598 */
word_t sk_swift_utf8_check(long a,long b,long c);        /* 002a15cc */
long sk_swift_utf8_scanfwd(long a,long b,word_t c);      /* 002a1648 */
void sk_swift_str_compare_slices(void);                  /* 002a177c */                  /* 002a177c */
void sk_swift_str_hash(void);                            /* 002a196c */
bool sk_swift_ascii_valid(char *p,word_t n);             /* 002a200c */
void sk_swift_str_copyin(void *a,long b);                /* 002a20cc */
void sk_swift_str_copy3(void *a,void *b,void *c);        /* 002a216c */
void sk_swift_utf8_decode(void);                         /* 002a218c */
void sk_swift_str_finalize(void *a,long b,uint c);       /* 002a2698 */
void sk_swift_utf8_encode_buf(void);                     /* 002a2748 */
void sk_ubp_alloc(long a,void *b,void *c);               /* 002a28f8 */
long sk_ubp_alloc_run(void);                             /* 002a2978 */
long sk_ubp_alloc_copy(long a,void *b,void *c);          /* 002a2a40 */
long sk_ubp_alloc_gen(long a,sk_fnptr b);                /* 002a2b04 */
void sk_ubp_commit(word_t a,uint b);                     /* 002a2bb0 */
void sk_utf16_encode(void);                              /* 002a2c04 */
void sk_utf8_encode(void);                               /* 002a2f60 */
void sk_latin1_encode(void *a,void *b,word_t c);         /* 002a3134 */
void sk_ascii_encode(void);                              /* 002a3268 */
void sk_utf16_encode2(void *a,void *b,uint c);           /* 002a339c */
void sk_utf8_encode3(void);                              /* 002a376c */
void sk_ubp_build(void *a,long b,void *c,uint d);        /* 002a3d30 */
void sk_ubp_read(void **a,void **b);                     /* 002a3d9c */
void sk_ubp_retain(void *a,void *b);                     /* 002a3e10 */
void sk_ubp_move(void *a,void *b,word_t c,word_t d);     /* 002a3e64 */
void sk_ubp_alloc_n(long a);                             /* 002a3ed4 */
void sk_ubp_alloc_n8(long a);                            /* 002a3f54 */
void sk_ubp_copy(void *a);                               /* 002a3ff0 */
sk_u128_t sk_ubp_slice(long a,long b,long c);            /* 002a401c */
void sk_ubp_slice_call(void *a,long b,long c,sk_fnptr d,void *e,void *f,void *g); /* 002a4148 */
void sk_ubp_transform(void *a,void *b,word_t c,word_t d,void *e); /* 002a421c */
void sk_ubp_with_buffer(long a,long b,sk_fnptr c);       /* 002a4340 */
bool sk_ubp_is_ascii(void *a,void *b,void *c,sk_fnptr d);/* 002a43e0 */
void sk_ubp_destroy_a(void);                               /* 002a4468 */
word_t sk_ubp_count(void *a,void *b,word_t c,word_t d);  /* 002a4528 */
void sk_ubp_fatal(void);                                 /* 002a45bc */
word_t sk_ubp_advance(void);                             /* 002a4614 */
void sk_ubp_advance_check(void);                         /* 002a4784 */
void sk_ubp_validate(word_t a);                          /* 002a4830 */
void sk_ubp_utf16_fatal(void);                           /* 002a487c */
word_t sk_ubp_alloc_cstr(word_t a);                      /* 002a4904 */
void sk_ubp_abort(void);                                 /* 002a49a8 */
sk_u128_t sk_ubp_capacity(word_t a,word_t b);            /* 002a49d4 */
sk_u128_t sk_ubp_endptr(word_t a,word_t b);              /* 002a49fc */
long sk_ubp_count2(void);                                /* 002a4a2c */
word_t sk_ubp_owner(void);                               /* 002a4a7c */
word_t sk_ubp_owner2(void);                              /* 002a4a80 */
void sk_ubp_ensure(long a);                              /* 002a4ab4 */
long sk_ubp_alloc_raw(void *a,void *b,void *c,uint d);   /* 002a4b90 */
void sk_ubp_destroy(void *a);                            /* 002a4be4 */
void sk_ubp_append(void);                                /* 002a4c88 */
void sk_ubp_append2(void);                               /* 002a4c98 */
void sk_ubp_init_short(void);                            /* 002a4f5c */
void sk_ubp_init_short2(word_t a,word_t b);              /* 002a4f80 */
void sk_ubp_finish(void);                                /* 002a507c */
void sk_ubp_append_ci(void *a,void *b,long c,long d);    /* 002a50ac */
void sk_ubp_store(void *a,void *b,void *c);              /* 002a5130 */
void sk_ubp_fill(void **a,uint b);                       /* 002a5178 */
void sk_ubp_reset(void);                                 /* 002a539c */
void sk_ubp_replace(void);                               /* 002a5400 */
void sk_ubp_trim(void);                                  /* 002a5544 */
void sk_ubp_append_idx(word_t a,word_t b,void *c,void *d); /* 002a55a4 */
word_t sk_ubp_append_slice(void *a,void *b,word_t c,word_t d); /* 002a55c0 */
word_t sk_ubp_append_slice2(void *a,void *b,word_t c,word_t d,word_t e,word_t f); /* 002a58b8 */
word_t sk_ubp_append_many(void *a,void *b,long c);       /* 002a5bf0 */
sk_u128_t sk_ubp_append_pair(void *a,void *b,void *c,void *d); /* 002a5e9c */
word_t sk_ubp_append_char(void *a,void *b);              /* 002a6080 */
void sk_ubp_format(void *a,void *b,void *c,void *d,void *e); /* 002a6238 */
void sk_ubp_grow(void);                                  /* 002a66f0 */
sk_u128_t sk_ubp_insert(word_t a,word_t b,void *c,void *d,void *e,void *f); /* 002a67a0 */
sk_u128_t sk_ubp_insert2(word_t a,word_t b,void *c,void *d,void *e,void *f); /* 002a6900 */
sk_u128_t sk_ubp_insert3(word_t a,word_t b,void *c,void *d); /* 002a6a18 */
sk_u128_t sk_ubp_insert4(word_t a,word_t b,void *c);     /* 002a6ad8 */
sk_u128_t sk_ubp_insert5(word_t a,word_t b,void *c,void *d,void *e); /* 002a6be4 */
sk_u128_t sk_ubp_insert6(word_t a,word_t b,void *c,void *d,void *e,void *f); /* 002a6d08 */
sk_u128_t sk_ubp_insert7(word_t a,word_t b,void *c,void *d); /* 002a6e3c */
void sk_ubp_grow2(void);                                 /* 002a6efc */
void sk_ubp_merge(word_t a,word_t b);                    /* 002a70d8 */

/* Helper macro for the "SoftwareBreakpoint(n,pc)" noreturn traps the decompiler
 * recovers (takes the code pointer from the software-breakpoint handler). */
#define SW_BREAK(n,pc) __builtin_trap() /* SoftwareBreakpoint(n,pc) */

/*--------------------------------------------------------------------*/
/* FUN_0029c058 @ 0x0029c058   (est. sk_swift_str_prelude)
 * Ghidra: void FUN_0029c058(void)
 * Starts a Swift string operation: pushes the object/string context, then probes
 * the current character (FUN_00359400). If a continuation (char << 0xe != 0) is
 * pending it drains it (FUN_00350624) and returns via sk_swift_str_prev_boundary
 * (0029ef1c); otherwise it arms the assert context and panics (noreturn).
 * Confidence: medium */
void sk_swift_str_prelude(void)
{
    word_t ch;
    rt_00350a28();
    ch = rt_00359400().lo;
    if (ch >> 0xe != 0) {
        rt_00350624();
        sk_swift_str_prev_boundary(0,0,0);
        return;
    }
    rt_00348614(1);
    rt_0034987c();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029c0b4 @ 0x0029c0b4   (est. sk_swift_str_index_step)
 * Ghidra: word_t FUN_0029c0b4(void)
 * Advances a Swift String index by one character (UTF-8/16 scalar width). Reads the
 * current scalar, validates, and returns a packed index word (next char count in
 * bits 16.., low flags 0x5). On a fatal condition it arms the assert path and panics.
 * Confidence: medium */
word_t sk_swift_str_index_step(void)
{
    word_t u, sc;
    long st;
    uint b;

    rt_00350b0c();
    u = rt_002ab130().lo;
    if (u >> 0xe == 0) {
        rt_00348614(1);
        rt_0034987c();
        /* WARNING: does not return */
        rt_001afe4c();
    }
    /* decode next scalar from the inline/utf8 buffer */
    if ((0 >> 0x3c & 1) == 0) {
        if ((0 >> 0x3d & 1) != 0) {
            rt_00353878();
            b = (uint)*(unsigned char *)(0 + (u >> 0x10) + -1);
            rt_00358004();
            do {
                rt_00355624();
                st = 0;
            } while (0 != 0);
            goto step_done;
        }
        if ((0 >> 0x3c & 1) == 0) goto conv;
        rt_003542dc();
    }
    else {
        rt_0034bf1c();
        rt_002ae098();
conv:
        rt_000b43d0();
        rt_002a9ba8();
    }
    do {
        rt_00356930();
    } while (0 != 0);
    st = -0;
step_done:
    return u + st * -0x10000 & 0xffffffffffff0000 | 5;
}

/*--------------------------------------------------------------------*/
/* FUN_0029c18c @ 0x0029c18c   (est. sk_swift_str_grow_register)
 * Ghidra: void FUN_0029c18c(undefined4 param_1)
 * Appends a 32-bit value to the global 32-bit grow-register array (DAT_00657798,
 * size DAT_00657790, count DAT_00657788), growing it via the string-slot builder
 * (002a2f60). On growth failure it releases the old buffer and stores the new one
 * into the caller context; else panics with "Unexpectedly found nil while
 * unwrapping an Optional value" / "Swift.String".
 * Confidence: medium */
void sk_swift_str_grow_register(void)
{
    word_t idx, cnt;
    long h;
    sk_u128_t t;

    rt_0018de98(0,1,0);
    idx = DAT_00657788;
    cnt = DAT_00657788 + 1;
    if (DAT_00657790 >> 1 <= DAT_00657788) {
        rt_0018de98(1 < DAT_00657790,cnt,1);
    }
    DAT_00657788 = cnt;
    *(unsigned int *)((long)&DAT_00657798 + idx * 4) = 0; /* param_1 (value dropped; register slot) */
    sk_ubp_init_short2((word_t)&DAT_00657778,1); t.lo = 0; t.hi = 0;
    h = t.hi;
    if (h != 0) {
        rt_0036b118(&DAT_00657778);
        sk_swift_str_append_obj(); t.lo = 0; t.hi = 0;
        *((word_t *)0) = t.lo;  /* [INFERENCE] store new buffer into caller string context */
        return;
    }
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029c2bc @ 0x0029c2bc   (est. sk_swift_str_append_obj)
 * Ghidra: void FUN_0029c2bc(void)
 * Appends the object/string value (from the "static" metadata LAB_000e0fc0) into the
 * caller context. On nil it panics (noreturn); otherwise it rebuilds the buffer with
 * FUN_001e3f70 and stores the new pair back.
 * Confidence: low (register artifact heavy; shape preserved) */
void sk_swift_str_append_obj(void)
{
    rt_00357ca0();
    rt_0035a080();
    rt_00354714();
    rt_000a0c8c(&LAB_000e0fc0,0);
    sk_ubp_init_short2(0,1);
    if (0 != 0) {
        rt_00354e0c();
        rt_0036b118(0);
        rt_0034d004(0);
        rt_001e3f70();
        rt_00354954();
        rt_003a25d4();
        rt_003a25d4(0);
        *(word_t *)0 = 0;
        *(word_t *)(0 + 8) = 1;
        rt_00357c44(0);
        return;
    }
    rt_003489dc(0x1c2);
    rt_0034a2f8();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029c3a0 @ 0x0029c3a0   (est. sk_swift_str_array_convert)
 * Ghidra: void FUN_0029c3a0(undefined8 param_1,undefined8 param_2,long param_3)
 * Converts a Swift array of element descriptors (at param_3) into the receiver
 * String/object. Walks the descriptor run, retaining/refcounting each element pair
 * (thunk_FUN_0036b270 + FUN_003a25d4) and merging via 002a4c98, preserving the
 * 16-byte result in the caller context. Shape preserved; register artifacts nulled.
 * Confidence: low */
void sk_swift_str_array_convert(void *a, void *b, long n)
{
    word_t e0, e1;
    sk_u128_t acc, t;
    void *ptr;
    long i;

    rt_00351e20();
    rt_0034f414();
    rt_003532b8();
    ptr = (void *)0; /* [INFERENCE] derived from builder result */
    rt_003497ec();
    acc = rt_001a89a8();
    if (0xf < (long)ptr) {
        sk_ubp_count2();
        sk_ubp_ensure((long)ptr);
    }
    for (i = n; i != 0; i--) {
        e0 = 0;
        e1 = 0;
        if (0 == 0) {
            rt_0036b270(e1);
            rt_003a25d4(e0);
        } else {
            rt_0036b270(e1);
            sk_ubp_append2();
            rt_003a25d4(e1);
        }
    }
    rt_00351d30(acc.lo,acc.hi,0);
    /* [INFERENCE] result left in caller context */
}

/*--------------------------------------------------------------------*/
/* FUN_0029c6bc @ 0x0029c6bc   (est. sk_swift_str_array_map)
 * Ghidra: undefined1 [16] FUN_0029c6bc(word_t param_1,word_t param_2,long param_3)
 * Maps an array of element descriptors (param_3) onto a 16-byte String result,
 * refcounting each element and normalizing surrogate pairs via 002a4c98 /
 * FUN_00291ee0. Returns the accumulated String value.
 * Confidence: low */
sk_u128_t sk_swift_str_array_map(word_t a, word_t b, long n)
{
    sk_u128_t acc, t;
    long i;
    word_t e0,e1,e2,e3;

    acc.lo = a; acc.hi = b;
    if (n != 0) {
        if (0 == 0) {
            for (i = 0; i < n; i++) {
                t.lo = 0; t.hi = 0;
                if (0 != 0 || 0 != 0) {
                    t = rt_0001d540(0,0,0,0);
                    rt_003a25d4(0);
                }
                acc = t;
            }
        } else {
            for (i = 0; i < n; i++) {
                t.lo = 0; t.hi = 0;
                rt_0036b270(0);
                sk_ubp_append2(); t.lo = 0; t.hi = 0;
                rt_003a25d4(0);
            }
        }
    }
    return acc;
}

/*--------------------------------------------------------------------*/
/* FUN_0029cb88 @ 0x0029cb88   (est. sk_swift_str_dispatch)
 * Ghidra: void FUN_0029cb88(undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4)
 * Dispatch entry that pushes the object context (via the DAT_00658c00 vtable), then
 * selects an operation on param_3: matching a Swift-runtime type it converts via
 * 0029c6bc; matching FUN_000778fc it uses 0029c3a0; otherwise it builds a descriptor
 * iterator and merges elements via 0029d2dc/002a4c98. Ends by committing the result
 * through FUN_0008e500.
 * Confidence: low */
void sk_swift_str_dispatch(void *a, void *b, long n, void *d)
{
    word_t cnt, u;
    sk_u128_t acc, t;
    long l;

    rt_0008e518();
    rt_00354ba4();
    rt_003520f8();
    rt_003516cc();
    rt_00377824();
    rt_00348e00();
    (*DAT_00658c00)(0);
    rt_003489c0();
    (*DAT_00658c00)();
    rt_0034ae94();
    (*DAT_00658c00)();
    rt_00350464();
    rt_00350530();
    rt_00310d68();
    rt_000a6f88();
    (*DAT_00658c00)(0);
    rt_00348bbc();
    (*DAT_00658c00)();
    rt_0034a9c0();
    (*DAT_00658c00)();
    rt_0034b87c();
    rt_0007c028();
    (*DAT_00658c00)(0);
    rt_003497b4();
    rt_00352738();
    rt_00350488();
    rt_003513c0();
    rt_00377824();
    rt_000a6f88();
    (*DAT_00658c00)(0);
    rt_00348bd8();
    (*DAT_00658c00)();
    rt_0034ae58();
    acc = rt_00002534(0x656268,&DAT_004e80c0);
    if (n == acc.lo) {
        rt_003524a4(acc.lo,acc.hi,0);
        rt_0008e500();
        sk_swift_str_array_map(0,0,0);
        return;
    }
    l = rt_000778fc().lo;
    if (n == l) {
        acc = (sk_u128_t){0,0};
        sk_swift_str_array_convert(0,0,0);
        goto commit;
    }
    cnt = 0;
    rt_00354f34(d);
    rt_00350b00();
    rt__indirect(); l = 0; /\* [INFERENCE] vtable char-count fn */
    rt_003497ec();
    acc = rt_001a89a8();
    if (0xf < l) {
        sk_ubp_count2();
        sk_ubp_ensure(l);
    }
    u = rt_00352e24().lo;
    rt__indirect(u,0,n);
    rt_003506b0();
    if (cnt == 0) {
        rt_00350b00(0);
        rt__indirect();
        rt_0034b278();
        u = rt_00377bec(0,n,0).lo;
        while (1) {
            rt__indirect(0,u);
            rt_0034aa54();
            if (0) break;
            rt_00351360(0);
            rt__indirect();
            sk_swift_str_dispatch2();
            rt_00358d70();
            rt_003507bc(0);
            rt__indirect();
            u = rt_00349bfc().lo;
            if (0 == 0) {
                rt_003a25d4();
                acc.lo = 0; acc.hi = 0;
            } else {
                rt_0036b270(0);
                t = rt_003508f0();
                sk_ubp_append2();
                rt_00357a00();
                rt_003a2610();
            }
        }
        u = rt_00351630().lo;
        rt__indirect(u,0);
        goto commit;
    }
    rt_00354bec();
    rt_00350b00();
    rt__indirect();
    rt_0034b278();
    t = rt_00350bf0();
    rt_00377bec(t.lo,t.hi,0);
    rt_00354474();
    rt__indirect(0,0,0);
    rt_0034aa54(0);
    if (0) {
        while (1) {
            acc.lo = 0; acc.hi = 0;
            rt__indirect(0,0);
            rt_0034aa54();
            if (0) break;
            rt_0034cfb4();
            rt__indirect(0);
            u = rt_0034bf64(0).lo;
            if (0 == 0) {
                rt_0036b270(0);
                rt_003a25d4(0);
                t.lo = 0; t.hi = 0;
            } else {
                rt_00350c38();
                sk_ubp_append2();
                t.lo = 0; t.hi = 0;
            }
            sk_swift_str_dispatch2(); acc.lo = 0; acc.hi = 0;
            rt_003508a8();
            rt__indirect();
            rt_0034c094(0);
            if (0 == 0) {
                rt_003a25d4(0);
            } else {
                rt_0036b270(0);
                rt_003509d4();
                rt_00353b40();
                sk_ubp_append2();
                rt_00356c60();
                rt_003a2610();
            }
        }
    }
    (*(void (**)())(0 + 8))(0,0);
    rt_003505e8(0);
    rt__indirect();
commit:
    rt_0008e500(acc.lo,acc.hi,0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029d2dc @ 0x0029d2dc   (est. sk_swift_str_dispatch2)
 * Ghidra: void FUN_0029d2dc(void)
 * Continuation helper used by the dispatch loop: pushes context, and if the current
 * element type matches a Swift-runtime tag it forwards the four element words via
 * 002a3e64, else it runs the common merge sequence and commits via FUN_0009461c.
 * Confidence: low */
void sk_swift_str_dispatch2(void)
{
    long l;
    rt_00351a38();
    rt_0034b57c();
    (*DAT_00658c00)(0);
    l = rt_0034d3b4().lo;
    if (l == 0x6753a0) {
        rt_0035aaf0();
    } else {
        if (0 == 0x675c68) {
            sk_ubp_move(0,0,0,0);
            return;
        }
        rt_0034ba28();
        rt__indirect();
        rt_0031e030();
        rt_00353528();
        rt_00357c04();
        rt_0034d180();
        rt_0022d2f4();
        rt_00351a50();
    }
    rt_0009461c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029d3d8 @ 0x0029d3d8   (est. sk_swift_str_utf8_emit)
 * Ghidra: void FUN_0029d3d8(void)
 * Emits the current scalar as UTF-8: if the pending type tag matches, calls
 * sk_swift_str_utf8_upper (0029d454) with a shared emit callback; else traps
 * (noreturn) via FUN_0011d7e8.
 * Confidence: medium */
void sk_swift_str_utf8_emit(void)
{
    sk_u128_t t;
    t = rt_0006b2ec();
    if (0 == -0x2c8502b44bfffed6) {
        sk_swift_str_utf8_upper((char *)0,0,0,0);
        return;
    }
    /* WARNING: does not return */
    rt_0011d7e8();
}

/*--------------------------------------------------------------------*/
/* FUN_0029d454 @ 0x0029d454   (est. sk_swift_str_utf8_upper)
 * Ghidra: long FUN_0029d454(char *param_1,long param_2,undefined8 param_3,long param_4)
 * UTF-8 upper-case emitter: writes param_4 characters into the destination, decoding
 * each via FUN_0035a0f0 and lower-casing ASCII (extraout_w10 | (w11&0x20)). Panics
 * (noreturn) on a negative count or when the destination runs out.
 * Confidence: medium */
long sk_swift_str_utf8_upper(char *p, long n, void *a, long c)
{
    sk_u128_t t;
    if (c < 0) {
        rt_00347d60();
        /* WARNING: does not return */
        rt_001afe4c();
    }
    if (c != 0) {
        do {
            if (n == 0) {
                rt_0035047c(p);
                rt_003480ac();
                /* WARNING: does not return */
                rt_001afe4c();
            }
            t = rt_0035a0f0();
            p = (char *)(t.lo + 1);
            *(unsigned char *)(uintptr_t)t.lo = (unsigned char)(0 & 0x20) + 0;
            n = t.hi + -1;
        } while (0 != 1);
    }
    return c;
}

/*--------------------------------------------------------------------*/
/* FUN_0029d4c0 @ 0x0029d4c0   (est. sk_swift_str_slice)
 * Ghidra: undefined1 [16] FUN_0029d4c0(undefined8 param_1,long param_2,long param_3,long param_4,long param_5)
 * Builds a 16-byte String slice spanning [param_2,param_4) of the storage whose
 * stride is *(param_5-8)+0x48. On invalid bounds panics (noreturn) with the
 * UnsafeBufferPointer fatal message.
 * Confidence: medium */
sk_u128_t sk_swift_str_slice(void *a, long b, long c, long d, long e)
{
    sk_u128_t out;
    if (b < 0) {
        rt_0035047c();
    } else {
        if (b < d) {
            out.hi = c + *(long *)(*(long *)(e + -8) + 0x48) * b;
            out.lo = rt_0001a1c8().lo;
            return out;
        }
        rt_0035047c();
    }
    rt_003480ac();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029d53c @ 0x0029d53c   (est. sk_swift_str_hash_dispatch)
 * Ghidra: undefined8 FUN_0029d53c(undefined8 param_1,word_t param_2)
 * Hash dispatch: for an object/indirect string (bit 0x3c set) routes to
 * FUN_002b24b8; otherwise builds the hash via the 0029d5cc family. Returns the
 * hash word.
 * Confidence: low */
word_t sk_swift_str_hash_dispatch(void *a, word_t b)
{
    word_t u;
    if ((b >> 0x3c & 1) == 0) {
        rt_003532b8();
        u = 0;
        return u;
    }
    return rt_002b24b8().lo;
}

/*--------------------------------------------------------------------*/
/* FUN_0029d560 @ 0x0029d560   (est. sk_swift_str_append_char)
 * Ghidra: void FUN_0029d560(undefined8 param_1)
 * Appends one character via FUN_002bc448.
 * Confidence: medium */
void sk_swift_str_append_char(void *a)
{
    rt_002bc448(1,a);
}

/*--------------------------------------------------------------------*/
/* FUN_0029d56c @ 0x0029d56c   (est. sk_swift_str_utf8_emit_lower)
 * Ghidra: void FUN_0029d56c(void)
 * Emits the current scalar as UTF-8 lower-case: on the matching type tag calls
 * sk_swift_str_utf8_lower (0029d9e4) with the shared emit callback, else traps.
 * Confidence: medium */
void sk_swift_str_utf8_emit_lower(void)
{
    sk_u128_t t;
    t = rt_0006b2ec();
    if (0 == -0x2c8502b44bfffed6) {
        sk_swift_str_utf8_lower((char *)0,0,0,0);
        return;
    }
    /* WARNING: does not return */
    rt_0011d7e8();
}

/*--------------------------------------------------------------------*/
/* FUN_0029d5cc @ 0x0029d5cc   (est. sk_swift_str_utf8_encode)
 * Ghidra: void FUN_0029d5cc(undefined8 param_1,undefined8 param_2,code *param_3,undefined8 param_4,undefined8 param_5)
 * UTF-8 encoder over the string buffer: decodes each scalar (via FUN_002a9ba8 /
 * inline forms), computes the UTF-8 byte count (2/3/4 continuation cases), emits
 * each byte through the caller callback param_3 (FUN_002bc448), and updates the
 * string storage. Ends by committing through FUN_0006b6f4. Complex register
 * artifacts nulled; structure preserved.
 * Confidence: low */
void sk_swift_str_utf8_encode(void *a, void *b, sk_fnptr c, void *d, void *e)
{
    word_t cnt, sc;
    long pos, adv;
    sk_u128_t t;
    int kind;

    rt_0035638c();
    rt_0008409c();
    rt_0006b2ec();
    sc = 0;
    if (0 != 0) {
        if ((0 >> 0x3d & 1) == 0) {
            if ((0 >> 0x3c & 1) == 0) {
                rt_00084180();
                rt_002a9ba8();
                rt_00351f28();
            }
            cnt = 0;
            if (0xf < (long)cnt) {
                rt_0036b270();
                rt_0034eda8(cnt);
                rt_0029ae68();
                rt_00350b90();
                goto done;
            }
            rt_0036b270();
            rt_003505c4(0);
            (*c)();
            if (cnt != 0) {
                rt_0035a0a4(8 - cnt);
                rt_00353888();
                sc = 0xe000000000000000;
                if (0) sc = 0;
                sc = sc | cnt << 0x38 | 0;
                if ((sc >> 0x3e & 1) == 0) {
                    rt_0029ac08(0,0,sc >> 0x38 & 0xf);
                    rt_003a25d4();
                    goto done;
                }
            }
        } else {
            rt_0036b270();
            (*c)(0,sc,0,sc);
            if (sc != 0) {
                rt_0035a0a4(8 - sc);
                rt_00353888();
                sc = 0xe000000000000000;
                if (0) sc = 0;
                sc = sc | sc << 0x38 | 0;
                if ((sc >> 0x3e & 1) == 0) {
                    rt_0029ac08(0,0,sc >> 0x38 & 0xf);
                    rt_003a25d4();
                    goto done;
                }
            }
        }
        rt_003a25d4();
        goto done;
    }
    rt_003497ec();
    t = rt_001a89a8();
    rt_00084180();
    sc = rt_002b24b8().lo;
    if (0xf < (long)sc) {
        sk_ubp_count2();
        if (0 || 0 < (long)sc) {
            sk_ubp_ensure((long)sc);
        }
    }
    cnt = 0;
    if (cnt != 0) {
        pos = 0;
        do {
            t.lo = 0; t.hi = 0;
            if ((0 >> 0x3d & 1) == 0) {
                rt_00084180();
                pos = rt_002a9ba8().lo;
                rt_0035617c(pos + cnt);
                adv = 0;
                if (0 < 0) {
                    rt_0034cbd8();
                    switch (0) {
                    case 1:
                        rt_003527a4(); adv = 2; break;
                    case 2:
                        rt_0034fb9c(); adv = 3; break;
                    case 3:
                        rt_0034c6d4(); rt_003538a0(); adv = 4;
                    }
                } else {
                    adv = 1;
                }
            } else {
                rt_0035617c(0 + cnt);
                adv = 0;
                if (0 < 0) {
                    rt_0034cbd8();
                    switch (0) {
                    case 1: adv = 2; break;
                    case 2: adv = 3; break;
                    case 3: adv = 4;
                    }
                } else {
                    adv = 1;
                }
            }
            rt_002bc448(e,adv);
            rt_003562d4();
            if (0 == 0) {
                rt_003a25d4(0);
            } else {
                rt_00350518();
                rt_00352938();
                sk_ubp_append2();
                rt_003a25d4(0);
            }
            cnt = adv + cnt;
        } while ((long)cnt < (long)cnt);
    }
done:
    rt_000651bc(0);
    if (0) {
        /* WARNING: does not return */
        rt_0011d7e8();
    }
    t = rt_0006b6f4();
    rt_00356370(t.lo,t.hi,0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029d9e4 @ 0x0029d9e4   (est. sk_swift_str_utf8_lower)
 * Ghidra: long FUN_0029d9e4(char *param_1,long param_2,undefined8 param_3,long param_4)
 * UTF-8 lower-case emitter: writes param_4 characters, decoding each and lower-casing
 * (extraout_w10 + (w11&1)*-0x20). Panics on negative count or full destination.
 * Confidence: medium */
long sk_swift_str_utf8_lower(char *p, long n, void *a, long c)
{
    sk_u128_t t;
    if (c < 0) {
        rt_00347d60();
        /* WARNING: does not return */
        rt_001afe4c();
    }
    if (c != 0) {
        do {
            if (n == 0) {
                rt_0035047c(p);
                rt_003480ac();
                /* WARNING: does not return */
                rt_001afe4c();
            }
            t = rt_0035a0f0();
            p = (char *)(t.lo + 1);
            *(char *)(uintptr_t)t.lo = (char)(0 + (0 & 1) * -0x20);
            n = t.hi + -1;
        } while (0 != 1);
    }
    return c;
}

/*--------------------------------------------------------------------*/
/* FUN_0029da50 @ 0x0029da50   (est. sk_swift_str_append_char0)
 * Ghidra: void FUN_0029da50(undefined8 param_1)
 * Appends one character via FUN_002bc448.
 * Confidence: medium */
void sk_swift_str_append_char0(void *a)
{
    rt_002bc448(0,a);
}

/*--------------------------------------------------------------------*/
/* FUN_0029da5c @ 0x0029da5c   (est. sk_swift_str_finish)
 * Ghidra: void FUN_0029da5c(void)
 * Finalizes a string build: runs the intermediate helpers and dispatches through the
 * caller vtable slot, committing via FUN_000b4390.
 * Confidence: low */
void sk_swift_str_finish(void)
{
    rt_0034e73c();
    rt_00350950();
    rt_00027724();
    rt_000777d4();
    rt__indirect();
    rt_000b43e8();
    rt_0034b3e8();
    (*(void (**)())(0 + 8))();
    rt_000b4390();
}

/*--------------------------------------------------------------------*/
/* FUN_0029dac0 @ 0x0029dac0   (est. sk_swift_str_read)
 * Ghidra: undefined8 FUN_0029dac0(void)
 * Reads the current string value: pulls the descriptor, normalizes via 0029d53c-style
 * build, and stores the result through FUN_00298530 into a local slot.
 * Confidence: low */
word_t sk_swift_str_read(void)
{
    sk_u128_t t;
    word_t out;
    rt_000a6f68();
    t = rt_003532b8();
    out = 0;
    rt_00298530(t.lo,t.hi,0,0,&out);
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_0029db08 @ 0x0029db08   (est. sk_swift_str_fwd_a) */
void sk_swift_str_fwd_a(void)
{
    rt_00298980();
}

/*--------------------------------------------------------------------*/
/* FUN_0029db0c @ 0x0029db0c   (est. sk_swift_str_fwd_b) */
void sk_swift_str_fwd_b(void)
{
    rt_00298980();
}

/*--------------------------------------------------------------------*/
/* FUN_0029db34 @ 0x0029db34   (est. sk_swift_str_write_escape)
 * Ghidra: void FUN_0029db34(void)
 * Writes the escape/expanded form of the current string into the growth buffer: it
 * grows the backing array (FUN_003a261c / FUN_001a09bc), decodes each scalar and
 * stores its UTF-8 byte width, and finally stores the produced count. Register
 * artifacts nulled; the growth-loop structure is preserved.
 * Confidence: low */
void sk_swift_str_write_escape(void)
{
    word_t cnt, sc, i;
    long buf, w;

    rt_00355578();
    rt_000a6f68();
    buf = 0;
    cnt = rt_003532b8().lo;
    if (cnt == 0) {
        rt_003a25d4(0);
        cnt = 0;
    } else {
        rt_001a05a8(cnt / 0xc0);
        rt_0036b270(0);
        i = 0;
        sc = 0xf;
        while (cnt * 4 - (sc >> 0xe) != 0) {
            if ((i & 0x3f) == 0) {
                w = 0;
                if ((rt_003a261c(w).lo & 1) == 0) {
                    rt_0006b3f4(*(void **)(w + 0x10));
                    w = rt_001a09bc().lo;
                }
                buf = w;
                w = *(long *)(w + 0x10);
                if (*(word_t *)(buf + 0x18) >> 1 <= (word_t)w) {
                    rt_0006b42c();
                    rt_00355be8(0,w + 1);
                    buf = rt_001a09bc().lo;
                }
                *(word_t *)(buf + 0x10) = (word_t)w + 1;
                *(word_t *)(buf + (word_t)w * 8 + 0x20) = sc;
            }
            if ((sc & 0xc) == 4L << 0) {
                rt_0034c064();
                sc = rt_0001da84().lo;
            }
            if (cnt <= sc >> 0x10) {
                rt_00348614(1);
                rt_0034987c();
                /* WARNING: does not return */
                rt_001afe4c();
            }
            if ((0 >> 0x3c & 1) == 0) {
                if (0 == 0) {
                    if ((sc & 0xc001) == 0) {
                        rt_0034c064();
                        sc = rt_001676cc().lo;
                        if ((0 >> 0x3d & 1) != 0) goto indirect;
                        buf = 0 + 0x20;
                        if (*(char *)(buf + (sc >> 0x10)) < '\0') goto utf16;
                        adv1:
                        buf = 1;
                        goto adv_done;
                    }
                    if ((0 >> 0x3d & 1) == 0) goto conv;
indirect:
                    if (-1 < *(char *)(0 + (sc >> 0x10))) goto adv1;
utf16:
                    rt_003558c4();
                    buf = 0;
                    if (0) goto adv_done;
                    if ((sc & 0xc000) != 0) {
                        buf = 4;
                        goto adv_done;
                    }
                    sc = sc & 0xffffffffffff0000 | 0x4004;
                } else {
                    sc = (sc & 0xffffffffffff0000) + 0x1000d;
                }
            } else {
                sc = rt_002af4d0(sc).lo;
            }
conv:
            sc = sc + buf * 0x10000;
adv_done:
            i = i + 1;
        }
        rt_0035ac1c();
        if ((i & 0x3f) == 0) {
            rt_001a157c(0);
            rt_001a1648(0,0);
            rt_00357fe4(0);
            *(word_t *)(0 + 0x20) = (0 | cnt << 0x10);
        }
    }
    *(word_t *)(0 + 0x10) = i;
    rt_00354458(0,0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029dddc @ 0x0029dddc   (est. sk_swift_str_index_next_char)
 * Ghidra: word_t FUN_0029dddc(void)
 * Returns the next character's packed index word. Reads the current scalar width,
 * handles ASCII/continuation flag bits, and returns the advanced index (char count
 * in bits 16.., trailing flags). Panics on overflow past the end.
 * Confidence: low */
word_t sk_swift_str_index_next_char(void)
{
    uint w;
    word_t sc, cur;
    long adv;

    rt_0034c840();
    w = 0;
    rt_0034a3b0(w);
    if (0) {
        rt_0034bf1c();
        sc = rt_0001da84().lo;
    }
    rt_0034a260();
    if (sc >> 0x10 < 0) {
        if ((0 >> 0x3c & 1) == 0) {
            cur = rt_00358990().lo;
            if (0 == 1) {
                cur = (sc & 0xffffffffffff0000) + 0x1000d;
            } else {
                if ((sc & 0xc001) == 0) {
                    rt_0034bf1c();
                    sc = rt_001676cc().lo;
                    cur = sc >> 0x10;
                }
                rt_00350548(cur);
                adv = rt_002ae028().lo;
                if ((adv == 4) && ((sc & 0xc000) == 0)) {
                    cur = 0x4004;
                } else {
                    sc = sc + adv * 0x10000;
                    cur = 5;
                }
                cur = sc & 0xffffffffffff0000 | cur;
            }
            return cur;
        }
        cur = rt_002af4d0(sc).lo;
        return cur;
    }
    rt_00348614(1);
    rt_0034987c();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029dee8 @ 0x0029dee8   (est. sk_swift_str_free_a)
 * Ghidra: void FUN_0029dee8(void)
 * Frees the string's backing buffer at *(ctx+0x18) and tears down.
 * Confidence: medium */
void sk_swift_str_free_a(void)
{
    rt_0036b118(*(void **)(0 + 0x18));
    rt_00002834();
    rt_0036b6ac();
}

/*--------------------------------------------------------------------*/
/* FUN_0029deec @ 0x0029deec   (est. sk_swift_str_free_b)
 * Ghidra: void FUN_0029deec(void)
 * Same as sk_swift_str_free_a.
 * Confidence: medium */
void sk_swift_str_free_b(void)
{
    rt_0036b118(*(void **)(0 + 0x18));
    rt_00002834();
    rt_0036b6ac();
}

/*--------------------------------------------------------------------*/
/* FUN_0029df10 @ 0x0029df10   (est. sk_swift_str_element_at)
 * Ghidra: undefined1 [16] FUN_0029df10(long param_1)
 * Returns the 16-byte element at 64-byte-stride index param_1/0x40 of the string's
 * backing element array (*(ctx+0x18)). Panics (noreturn) on out-of-range index.
 * Confidence: medium */
sk_u128_t sk_swift_str_element_at(long i)
{
    sk_u128_t out;
    if (-0x40 < i) {
        if (i / 0x40 < *(long *)(*(long *)(0 + 0x18) + 0x10)) {
            out.hi = i % 0x40;
            out.lo = *(word_t *)(*(long *)(0 + 0x18) + (i / 0x40) * 8 + 0x20);
            return out;
        }
    }
    rt_00348304();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029df64 @ 0x0029df64   (est. sk_swift_str_element_find)
 * Ghidra: undefined1 [16] FUN_0029df64(word_t param_1)
 * Binary search over the string's element array for the element containing byte
 * offset param_1 (elements are 0xc00000-byte blocks with 64-byte alignment). Returns
 * the element's base word and sub-offset. Panics (noreturn) on out-of-range.
 * Confidence: low */
sk_u128_t sk_swift_str_element_find(word_t off)
{
    word_t base, hi, lo, mid, cnt;
    long buf;
    sk_u128_t out;

    base = off / 0xc00000;
    buf = *(long *)(0 + 0x18);
    cnt = *(word_t *)(buf + 0x10);
    hi = cnt;
    if ((off >> 0x16) + 1 <= cnt) {
        hi = (off >> 0x16) + 1;
    }
    lo = hi - base;
    if (1 < (long)lo) {
        do {
            mid = base + (lo >> 1);
            if (SW_BREAK(1,0x29e00c)) {}
            if (cnt <= mid) {
                rt_00348304();
                /* WARNING: does not return */
                rt_001afe4c();
            }
            hi = mid;
            if (*(word_t *)(buf + 0x20 + mid * 8) >> 0xe <= off >> 0xe) {
                hi = base + (lo >> 1);
                base = mid;
            }
            lo = hi - base;
        } while (1 < (long)lo);
    }
    out = rt_00351330();
    rt_0019e690(out.lo,out.hi,buf);
    out.lo = *(word_t *)(buf + base * 8 + 0x20);
    out.hi = base << 6;
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_0029e00c @ 0x0029e00c   (est. sk_swift_str_desc)
 * Ghidra: void FUN_0029e00c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Descriptor helper: pushes the string context and, depending on the current element
 * tag, either commits a scalar (0xf) or dispatches the element callback through the
 * vtable, ending in FUN_0008e500.
 * Confidence: low */
void sk_swift_str_desc(void *a, void *b, void *c)
{
    word_t u;
    rt_0008e518();
    rt_00354de8();
    rt_00350a64();
    rt_00353a6c();
    rt_00377824();
    rt_00348e00();
    (*DAT_00658c00)(0);
    rt_003489c0();
    (*DAT_00658c00)();
    rt_0034b758();
    rt_00352cb0();
    if (0 == 0) {
        u = 0xf;
    } else {
        rt_00354140();
        if (0 != 0) {
            u = rt_00377bec().lo;
            rt_00351bec();
            rt_0035156c();
            rt_0034ce08(0);
            rt__indirect();
            rt_003508a8();
            rt__indirect();
            rt_0035a0d8(u);
            rt_00352d40(0,0);
            rt__indirect();
            rt_00350560();
            rt__indirect();
            u = rt_00353100().lo;
            rt_0008e500(u,0);
            return;
        }
        u = 0;
    }
    rt_0008e500(u);
    rt_002afd38();
}

/*--------------------------------------------------------------------*/
/* FUN_0029e1a0 @ 0x0029e1a0   (est. sk_swift_str_desc2)
 * Ghidra: void FUN_0029e1a0(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Desc2 variant of sk_swift_str_desc: same dispatch, ends via sk_ubp_advance
 * (002a4614) and FUN_0008e500.
 * Confidence: low */
void sk_swift_str_desc2(void *a, void *b, void *c)
{
    word_t u;
    rt_0008e518();
    rt_00354de8();
    rt_00350a64();
    rt_00353a6c();
    rt_00377824();
    rt_00348e00();
    (*DAT_00658c00)(0);
    rt_003489c0();
    (*DAT_00658c00)();
    rt_0034b758();
    rt_00352cb0();
    if (0 == 0) {
        u = 0xf;
    } else {
        rt_00354140();
        if (0 != 0) {
            u = rt_00377bec().lo;
            rt_00351bec();
            rt_0035156c();
            rt_0034ce08(0);
            rt__indirect();
            rt_003508a8();
            rt__indirect();
            rt_00356e4c(u);
            rt_00352d40(0,0);
            rt__indirect();
            rt_00350560();
            rt__indirect();
            u = rt_0035a560().lo;
            rt_0008e500(u,0);
            return;
        }
        u = 0;
    }
    rt_0008e500(u);
    sk_ubp_advance();
}

/*--------------------------------------------------------------------*/
/* FUN_0029e370 @ 0x0029e370   (est. sk_swift_str_range_check)
 * Ghidra: void FUN_0029e370(undefined8 param_1,undefined8 param_2,word_t param_3)
 * Computes the [start,end) character range of a string relative to param_3 and
 * commits it. Handles both UTF-16 (via 002a4614/002af74c) and UTF-8 scalar-width
 * forms. Panics (noreturn) when the range exceeds the string length.
 * Confidence: low */
void sk_swift_str_range_check(void *a, void *b, word_t p)
{
    word_t s1, s2, u;
    long l0, l1, l2;

    rt_00354a34();
    rt_00351da8();
    rt_003509ec();
    rt_00354a28();
    rt_00353590(0);
    u = 0;
    if (0 == u) {
        rt_0034ba28();
        s2 = rt_0001da84().lo;
    }
    if ((0 & 0xc) == u) {
        rt_0011aa70();
        s2 = rt_0001da84().lo;
    }
    rt_0034a274();
    if ((0 < s2 >> 0x10) || (0 < s2 >> 0x10)) {
        rt_00348614(1);
        rt_0034987c();
        /* WARNING: does not return */
        rt_001afe4c();
    }
    if ((0 >> 0x3c & 1) == 0) {
        s1 = s2 >> 0x10;
        if (0 == 1) {
            l0 = s1 - (p >> 0x10);
            l1 = (s2 >> 0x10) - (p >> 0x10);
        } else {
            u = (s2 >> 0x10) - s1;
            if ((s2 >> 0x10) - s1 < 0x21) {
                rt_0035a04c();
                if (0) {
                    rt_0034ba28();
                    rt_001676cc();
                    rt_0034c1f8();
                }
                if ((s2 & 0xc001) == 0) {
                    rt_0011aa70();
                    rt_001676cc();
                    rt_0034fb60();
                }
                rt_0034c344(p);
                l0 = rt_002afd38().lo;
                rt_0008412c();
                l1 = rt_002afeec().lo;
                l0 = l0 + l1;
                if (SW_BREAK(1,0x29e53c)) {}
            } else {
                rt_0034c818();
                l1 = rt_002af74c().lo;
                if ((s1 - (p >> 0x10)) < 0x21) {
                    rt_0034c344(p);
                    l0 = rt_002afeec().lo;
                } else {
                    rt_0034ba28();
                    l0 = rt_002af74c().lo;
                    l0 = l0 - l1;
                    if (SW_BREAK(1,0x29e544)) {}
                }
                rt_0011aa70();
                l2 = rt_002af74c().lo;
                l0 = l2 - l1;
                if (SW_BREAK(1,0x29e540)) {}
            }
        }
        u = rt_0026bd30(l0,l1).lo;
    } else {
        rt_003504c4();
        l1 = rt_002afee0().lo;
        rt_00100efc();
        l0 = rt_002afee0().lo;
        if (l0 < 0) {
            rt_00347de8(1);
            /* WARNING: does not return */
            rt_001afe4c();
        }
        l1 = l0 + l1;
    }
    rt_00354ef8(u,u,0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029e594 @ 0x0029e594   (est. sk_swift_str_eq)
 * Ghidra: void FUN_0029e594(undefined8 param_1,undefined8 param_2,long param_3,undefined8 param_4,code *param_5,code *param_6,code *UNRECOVERED_JUMPTABLE)
 * String-equality dispatch: retains the relevant element based on the current tag,
 * then runs both element callbacks (param_5/param_6) and commits via FUN_003544c8.
 * The final jumptable dispatch is unrecoverable and treated as a call.
 * Confidence: low */
void sk_swift_str_eq(void *a, void *b, long c, void *d, sk_fnptr e, sk_fnptr f)
{
    word_t u;
    sk_u128_t t;
    rt_00354744();
    rt_003509ec();
    rt_00352cb0();
    if (c == 0) {
        u = 0;
        rt_0036b270(u);
        rt_00100efc();
    } else {
        rt_00354140();
        if (c != 0) {
            t = rt_0009e234();
            (*f)(t.lo,t.hi,d);
            t = rt_00350494();
            (*f)(t.lo,t.hi,d);
            rt_00353a30();
            rt_003544c8();
            /* WARNING: unrecovered jumptable; treated as call */
            (*e)();
            return;
        }
        u = 0;
        rt_0036b270(u);
        rt_00100efc();
        rt_00350bfc();
    }
    (*e)();
    rt_0006b674();
    rt_003a25d4(u);
    t = rt_003507e0();
    rt_003544c8(t.lo,t.hi,0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029e688 @ 0x0029e688   (est. sk_swift_str_compare_ci)
 * Ghidra: void FUN_0029e688(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,word_t param_5)
 * Case-insensitive string comparison helper: computes the scalar difference of two
 * substrings using the scalar-width primitives (002a4614, 002af74c, 002af844) and
 * commits the result. Handles both UTF-16 and UTF-8 scalar-width paths. Panics
 * (noreturn) on an invalid UTF-16 length.
 * Confidence: low */
void sk_swift_str_compare_ci(void *a, void *b, void *c, void *d, word_t p)
{
    word_t x, y;
    long l;
    sk_u128_t t;
    rt_00357ca0();
    rt_00351da8();
    rt_003509ec();
    if ((p >> 0x3c & 1) == 0) {
        rt_0034fb74();
        if (0 == 1) {
            rt_0034c344(c);
            x = sk_ubp_advance();
            if (SW_BREAK(1,0x29e7dc)) {}
            rt_0035053c(x,0 - 0);
            x = sk_ubp_advance();
            t = rt_00357ac0();
        } else {
            if (SW_BREAK(1,0x29e7e0)) {}
            if (0 - 0 < 0x20) {
                rt_0034c344(c);
                x = sk_ubp_advance();
                rt_0035053c(x,0 - 0);
                y = rt_001b1d5c().lo;
                t.hi = y | 4;
                t.lo = x;
            } else {
                rt_0034c818();
                l = rt_002af74c().lo;
                if (SW_BREAK(1,0x29e7e4)) {}
                if (0 - l < 0x21) {
                    rt_0034c344(c);
                    x = rt_001b1d5c().lo;
                } else {
                    if (SW_BREAK(1,0x29e7ec)) {}
                    rt_00350624(l + 0);
                    x = rt_002af844().lo;
                }
                if (SW_BREAK(1,0x29e7e8)) {}
                rt_00350624(l + 0);
                y = rt_002af844().lo;
                t.hi = y;
                t.lo = x;
            }
        }
        t = rt_0026bd5c(t.lo,t.hi);
    } else {
        rt_0034c344(c);
        x = sk_ubp_advance();
        if (SW_BREAK(1,0x29e7f0)) {}
        rt_0035053c(x,0 - 0);
        y = rt_002af6e4().lo;
        t.hi = y;
        t.lo = x;
        if (y >> 0xe < x >> 0xe) {
            rt_00347de8(1,y,y);
            /* WARNING: does not return */
            rt_001afe4c();
        }
    }
    rt_00357c44(t.lo,t.hi,0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029e7f0 @ 0x0029e7f0   (est. sk_swift_str_compare_wrap)
 * Ghidra: void FUN_0029e7f0(void)
 * Wraps sk_swift_str_compare_ci with the UTF-8 case-fold result and runs the
 * continuation chain (0029e688, 0029e840).
 * Confidence: low */
void sk_swift_str_compare_wrap(void)
{
    sk_u128_t t;
    rt_00352e54();
    rt_003509ec();
    t = rt_00355968();
    rt_00356358(t.lo,t.hi,0xf);
    sk_swift_str_compare_ci(0,0,0,0,0);
    rt_00351790();
    rt_00100efc();
    sk_swift_str_is_ascii(0,0,0,0,0,0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029e840 @ 0x0029e840   (est. sk_swift_str_is_ascii)
 * Ghidra: void FUN_0029e840(undefined8 param_1,undefined8 param_2,word_t param_3,word_t param_4,word_t param_5,word_t param_6)
 * ASCII fast-path check: if the scalar widths differ in the high nibble it runs the
 * ASCII/UTF-8 buffer test (002a9ba8) and commits; else commits via FUN_002b1104.
 * Confidence: low */
void sk_swift_str_is_ascii(void *a, void *b, word_t c, word_t d, word_t e, word_t f)
{
    long l;
    rt_00357cb4();
    if (0x3fff < (d ^ c)) {
        rt_00349fcc();
        if ((f >> 0x3d & 1) == 0) {
            if ((e >> 0x3c & 1) == 0) {
                l = rt_002a9ba8(e,f).lo;
            } else {
                l = (f & 0xfffffffffffffff) + 0x20;
            }
            rt_0034b730(l);
            rt_00357c74();
            rt_002b1104();
            return;
        }
        rt_0034b730(f >> 0x3e & 1);
        rt_002b1104();
    }
    rt_00357c74(0);
}

/*--------------------------------------------------------------------*/
/* FUN_0029e8dc @ 0x0029e8dc   (est. sk_swift_str_line_scan)
 * Ghidra: void FUN_0029e8dc(void)
 * Scans a string's character run for newline/0xa0d boundaries and commits the line
 * count. Handles both forward (0xa0d / 0x8080 test via FUN_00358a98) and backward
 * (FUN_002c6d00/002c7020) scans.
 * Confidence: low */
void sk_swift_str_line_scan(void)
{
    word_t a, b, u;
    long n;
    rt_0035193c();
    rt_0034b85c();
    rt_00351488();
    a = rt_00359400().lo;
    rt_0011aa70();
    b = rt_00359400().lo;
    u = a >> 0x10;
    if (a >> 0xe < b >> 0xe) {
        if (u < b >> 0x10) {
            n = 1;
            if ((0 >> 0x3c & 1) != 0) goto fwd_utf16;
            do {
                if ((0 >> 0x3d & 1) == 0) {
                    rt_00350a04();
                    if ((0 >> 0x3c & 1) == 0) {
                        rt_0007c1c4();
                        rt_002a9ba8();
                    }
                    u = rt_00358a98().lo;
                    if (0) {
                        if (u == 0) goto nil_panic;
                        if (*(unsigned short *)(u + (a >> 0x10)) == 0xa0d) goto fwd_utf16;
                        if ((*(unsigned short *)(u + (a >> 0x10)) & 0x8080) != 0) goto fwd_utf16;
                    }
                } else {
                    a = (a >> 0x10) + 1;
                    if ((a != (0 >> 0x38 & 0xf)) &&
                       (*(unsigned short *)(0 + (a >> 0x10)) == 0xa0d ||
                        (*(unsigned short *)(0 + (a >> 0x10)) & 0x8080) != 0)) goto fwd_utf16;
                }
                while (1) {
                    if ((long)(b >> 0x10) <= (long)(a >> 0x10)) goto commit;
                    n = n + 1;
                    a = a >> 0x10;
                    if ((0 >> 0x3c & 1) == 0) break;
fwd_utf16:
                    rt_0034ba28();
                    a = rt_002c6d00().lo + (a >> 0x10);
                }
            } while (1);
        }
    } else if ((b >> 0xe < a >> 0xe) && (b >> 0x10 < u)) {
        n = -1;
        do {
            if ((long)(a >> 0x10) < 2) {
                a = 1;
bwd_neg:
                a = -a;
            } else {
                if ((0 >> 0x3c & 1) != 0) {
bwd_utf16:
                    rt_0034ba28();
                    a = rt_002c7020().lo;
                    goto bwd_neg;
                }
                if ((0 >> 0x3d & 1) == 0) {
                    a = (0 & 0xfffffffffffffff) + 0x20;
                    if ((0 >> 0x3c & 1) == 0) {
                        rt_0007c1c4();
                        a = rt_002a9ba8().lo;
                        if (a == 0) goto nil_panic;
                    }
                    u = *(unsigned short *)(a + (a >> 0x10) + -2);
                } else {
                    u = *(unsigned short *)(0 + (a >> 0x10));
                }
                rt_00352bd4(u);
                if (0 || 0 != 0) goto bwd_utf16;
                a = -1;
            }
            a = (a >> 0x10) + a;
            if ((long)(a >> 0x10) <= (long)(b >> 0x10)) goto commit;
            n = n + -1;
        } while (1);
    }
    n = 0;
commit:
    rt_00351774(n,0);
    return;
nil_panic:
    rt_00347f2c();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029ea8c @ 0x0029ea8c   (est. sk_swift_str_has_ascii)
 * Ghidra: undefined8 FUN_0029ea8c(undefined8 param_1,undefined8 param_2,word_t param_3)
 * Returns nonzero if the string is pure ASCII: fast path checks the character count
 * and delegates to sk_swift_str_ascii_check (0029ead8).
 * Confidence: low */
word_t sk_swift_str_has_ascii(void *a, void *b, word_t c)
{
    word_t u;
    rt_0034a3b0(1);
    if (1 && (u = rt_00358ae0().lo, u >> 0x10 <= 0)) {
        return sk_swift_str_ascii_check(u);
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_0029ead8 @ 0x0029ead8   (est. sk_swift_str_ascii_check)
 * Ghidra: bool FUN_0029ead8(word_t param_1)
 * ASCII validity check of a packed index/scalar word: rejects surrogate/continuation
 * flag bits and verifies the byte count via FUN_002c6aac.
 * Confidence: medium */
bool sk_swift_str_ascii_check(word_t a)
{
    word_t u;
    if (((uint)a >> 1 & 1) == 0) {
        if ((a & 0xc000) != 0) {
            return false;
        }
        if (0xffff < a) {
            rt_00350b0c();
            rt_00358ae0();
            if (0 != a >> 0x10) {
                rt_0034bf1c();
                u = rt_002af340().lo;
                if ((u & 1) == 0) {
                    return false;
                }
                rt_00350548(a | 1);
                u = rt_002c6aac().lo;
                return (u ^ a) < 0x4000;
            }
        }
    }
    return true;
}

/*--------------------------------------------------------------------*/
/* FUN_0029eb58 @ 0x0029eb58   (est. sk_swift_str_next_scalar)
 * Ghidra: word_t FUN_0029eb58(void)
 * Reads the next scalar from the string, normalizing continuation bits
 * (FUN_001676cc / FUN_00357938), and returns its packed form. Panics (noreturn)
 * past the end.
 * Confidence: low */
word_t sk_swift_str_next_scalar(void)
{
    word_t u;
    if (0) {
        rt_00350624();
        u = rt_00167658().lo;
        if ((u & 1) == 0) {
            rt_00350624();
            u = rt_001676cc().lo;
            u = rt_00357938(u & 0xfffffffffffffff3).lo;
        }
        if (((uint)u >> 1 & 1) == 0) {
            if ((0xffff < u) && (u = rt_0034cbb0(u >> 0x10), 0 != 0)) {
                rt_00350624();
                u = rt_002c6aac().lo;
                return u;
            }
            u = u | 3;
        }
    } else {
        u = rt_0034a274().lo;
        if (0 <= u >> 0x10) {
            rt_00348614(1);
            rt_0034987c();
            /* WARNING: does not return */
            rt_001afe4c();
        }
    }
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_0029ec2c @ 0x0029ec2c   (est. sk_swift_str_advance_line)
 * Ghidra: void FUN_0029ec2c(undefined8 param_1,undefined8 param_2,word_t param_3)
 * Advances a string index by one line, handling newline (0xa0d) and 0x8080 marker
 * scanning in both UTF-8 and inline forms, and commits the advanced index.
 * Confidence: low */
void sk_swift_str_advance_line(void *a, void *b, word_t c)
{
    word_t u, cnt, f, w;
    sk_u128_t t;
    rt_003565a8();
    u = c;
    t = rt_00352914();
    f = t.lo >> 8 & 0x3f;
    w = t.hi & 0xffffffffffff;
    c = c >> 0x38 & 0xf;
    if (f == 0) {
        f = w;
        if (0 != 0) f = c;
        if (0 >> 0xe == f * 4) {
            f = 0;
        } else if ((u >> 0x3c & 1) == 0) {
            if (0 == 0) {
                if ((0 >> 0x3c & 1) == 0) {
                    rt_0009461c();
                    rt_002a9ba8();
                    t = rt_003505f4();
                } else {
                    t.lo = rt_0008e34c().lo;
                    t.hi = w;
                }
                if (t.lo + 1 != t.hi) {
                    if (0 == 0) goto nl_panic;
                    if (*(unsigned short *)(0 + t.lo) == 0xa0d ||
                        (*(unsigned short *)(0 + t.lo) & 0x8080) != 0) goto nl_utf16;
                }
                cnt = 0;
            } else {
                if ((0 >> 0x10) + 1 != c &&
                   (*(unsigned short *)(0 + (0 >> 0x10)) == 0xa0d ||
                    (*(unsigned short *)(0 + (0 >> 0x10)) & 0x8080) != 0)) goto nl_utf16;
                cnt = 1;
            }
            f = 1;
        } else {
nl_utf16:
            rt_00350968();
            f = rt_002c6d00().lo;
        }
    }
    u = (0 >> 0x10) + f * 0x10000;
    w = u & 0xffffffffffff0000;
    u = u >> 0x10;
    if (w >> 0xe == 0 * 4) {
        f = 0;
    } else {
        if ((0 & 0x1000000000000000) == 0) {
            if (0 == 0) {
                if ((0 >> 0x3c & 1) == 0) {
                    rt_0009461c();
                    t = rt_002a9ba8();
                } else {
                    t.lo = rt_003542dc().lo;
                    t.hi = w;
                }
                if (u + 1 != t.hi) {
                    if (t.lo == 0) goto nl_panic;
                    if (*(unsigned short *)(t.lo + u) == 0xa0d ||
                        (*(unsigned short *)(t.lo + u) & 0x8080) != 0) goto nl_utf16b;
                }
            } else {
                if ((!0) && (rt_00352bd4(*(unsigned short *)(0 + u)), 0 || 0 != 0))
                    goto nl_utf16b;
            }
            cnt = 0;
            f = 1;
        } else {
nl_utf16b:
            rt_0034d180();
            f = rt_002c6d00().lo;
            if (0x3f < f) goto nl_done;
        }
    }
    w = w | f << 8;
nl_done:
    rt_00356590(w | 0xb,0);
    return;
nl_panic:
    rt_00347f2c();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029ee18 @ 0x0029ee18   (est. sk_swift_str_is_newline)
 * Ghidra: word_t FUN_0029ee18(word_t param_1,word_t param_2,word_t param_3)
 * Tests whether the character at the packed index is a newline (0xa0d) or an
 * 0x8080-marker byte; returns 1 if it is a plain separator boundary, 0 if it is the
 * line terminator, or the UTF-16 width.
 * Confidence: low */
word_t sk_swift_str_is_newline(word_t a, word_t b, word_t c)
{
    word_t u, f;
    unsigned short ch;
    if ((a >> 8 & 0x3f) != 0) {
        return a >> 8 & 0x3f;
    }
    f = c >> 0x38 & 0xf;
    u = b & 0xffffffffffff;
    if ((c & 0x2000000000000000) != 0) {
        u = f;
    }
    if (a >> 0xe == u * 4) {
        return 0;
    }
    a = a >> 0x10;
    if ((c >> 0x3c & 1) == 0) {
        if ((c >> 0x3d & 1) == 0) {
            if ((b >> 0x3c & 1) == 0) {
                u = rt_002a9ba8(b,c).lo;
            } else {
                u = (c & 0xfffffffffffffff) + 0x20;
            }
            if (a + 1 == 0) {
                return 1;
            }
            if (u == 0) {
                rt_00347f2c(a,b,c);
                /* WARNING: does not return */
                rt_001afe4c();
            }
            ch = *(unsigned short *)(u + a);
        } else {
            if (a + 1 == f) {
                return 1;
            }
            ch = *(unsigned short *)(0 + a);
        }
        if ((ch != 0xa0d) && ((ch & 0x8080) == 0)) {
            return 1;
        }
    }
    return rt_002c6d00().lo;
}

/*--------------------------------------------------------------------*/
/* FUN_0029ef1c @ 0x0029ef1c   (est. sk_swift_str_prev_boundary)
 * Ghidra: word_t FUN_0029ef1c(undefined8 param_1,undefined8 param_2,word_t param_3)
 * Moves a string index back to the previous character/scalar boundary, examining the
 * UTF-16 byte at (idx-2) via FUN_002c7020, and returns the packed index. Panics on
 * a nil buffer.
 * Confidence: low */
word_t sk_swift_str_prev_boundary(void *a, void *b, word_t c)
{
    word_t u, w, f;
    long l;
    if (rt_0008409c().lo < 0x4000) {
        u = 0;
    } else {
        u = 0 >> 0x10;
        if (0x1ffff < 0) {
            if ((c >> 0x3c & 1) == 0) {
                if ((c >> 0x3d & 1) == 0) {
                    if ((0 >> 0x3c & 1) == 0) {
                        rt_0009461c();
                        l = rt_002a9ba8().lo;
                        if (l == 0) {
                            rt_00347f2c();
                            /* WARNING: does not return */
                            rt_001afe4c();
                        }
                    } else {
                        u = rt_0008e34c().lo;
                        l = 0;
                    }
                } else {
                    u = rt_003599a0(c & 0xffffffffffffff).lo;
                    l = 0;
                }
                rt_00352bd4(*(unsigned short *)(l + u + -2));
                if ((0 != 0) || 0 == 0) {
                    rt_00350968();
                    u = rt_002c7020().lo;
                }
            } else {
                rt_00350968();
                u = rt_002c7020().lo;
            }
        }
        w = u << 8;
        if (0x3f < (long)u) {
            w = 0;
        }
    }
    f = 0xb;
    return (0 >> 0x10) + u * -0x10000 & 0xffffffffffff0000 | w | f;
}

/*--------------------------------------------------------------------*/
/* FUN_0029f00c @ 0x0029f00c   (est. sk_swift_str_prev_utf8)
 * Ghidra: word_t FUN_0029f00c(word_t param_1,word_t param_2,word_t param_3)
 * Steps one UTF-8 character backward and returns the byte width (or 1 if the byte at
 * idx-2 is an ASCII separator).
 * Confidence: low */
word_t sk_swift_str_prev_utf8(word_t a, word_t b, word_t c)
{
    word_t u, f;
    if (a < 0x4000) {
        u = 0;
    } else {
        u = a >> 0x10;
        if (0x1ffff < a) {
            if ((c >> 0x3c & 1) == 0) {
                if ((c >> 0x3d & 1) == 0) {
                    if ((b >> 0x3c & 1) == 0) {
                        u = rt_0035a8bc().lo;
                        if (u == 0) {
                            rt_00347f2c(0,0,0);
                            /* WARNING: does not return */
                            rt_001afe4c();
                        }
                    } else {
                        u = (c & 0xfffffffffffffff) + 0x20;
                    }
                } else {
                    u = 0;
                }
                rt_00352bd4(*(unsigned short *)((long)u + (u - 2)));
                if (0 != 0 || 0 == 0) {
                    return 1;
                }
            }
            u = rt_002c7020().lo;
            return u;
        }
    }
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_0029f0b0 @ 0x0029f0b0   (est. sk_swift_str_scan_lines)
 * Ghidra: void FUN_0029f0b0(void)
 * Scans a string forward/backward across line boundaries and commits the advanced
 * index. Mirrors sk_swift_str_scan_lines2 with the newline/0x8080 checks.
 * Confidence: low */
void sk_swift_str_scan_lines(void)
{
    word_t u, w, e;
    long l;
    unsigned short ch;
    rt_0035193c();
    rt_0034b85c();
    rt_00351488();
    u = rt_00359400().lo;
    if (0 < 0) {
        for (l = 0; 0 < l; l = l + -1) {
            if (u >> 0xe == 0) goto fwd_panic;
            if (u < 0x20000) goto fwd_cont;
            if ((0 >> 0x3c & 1) == 0) {
                if ((0 >> 0x3d & 1) == 0) {
                    w = (0 & 0xfffffffffffffff) + 0x20;
                    if ((0 >> 0x3c & 1) == 0) {
                        rt_0007c1c4();
                        w = rt_002a9ba8().lo;
                        if (w == 0) goto nil_panic;
                    }
                    ch = *(unsigned short *)(w + (u >> 0x10) + -2);
                    if ((ch == 0xa0d) || ((ch & 0x8080) != 0)) goto nl_scan;
                } else {
                    rt_00352bd4(*(unsigned short *)(0 + (u >> 0x10) + 6));
                    if (0 || 0 != 0) goto nl_scan;
                }
            } else {
nl_scan:
                rt_0034c818();
                rt_002c7020();
            }
fwd_cont:
            rt_003568a8();
        }
    } else {
        for (; 0 != 0; ) {
            e = 0 * 4;
            if (e < u >> 0xe || e - (u >> 0xe) == 0) {
fwd_panic:
                rt_00348614(1);
                rt_0034987c();
                /* WARNING: does not return */
                rt_001afe4c();
            }
            w = u >> 8 & 0x3f;
            if (w == 0) {
                w = u >> 0x10;
                if ((0 >> 0x3c & 1) == 0) {
                    if ((0 >> 0x3d & 1) == 0) {
                        rt_00350c38();
                        if ((0 >> 0x3c & 1) == 0) {
                            rt_0007c1c4();
                            rt_002a9ba8();
                        }
                        l = rt_0035a244().lo;
                        if (0) {
                            if (l == 0) goto nil_panic;
                            ch = *(unsigned short *)(l + w);
                            if ((ch == 0xa0d) || ((ch & 0x8080) != 0)) goto nl_scan2;
                        }
                    } else {
                        if (w + 1 != 0) {
                            ch = *(unsigned short *)(0 + w);
                            if ((ch == 0xa0d) || ((ch & 0x8080) != 0)) goto nl_scan2;
                        }
                    }
                    w = 1;
                } else {
nl_scan2:
                    rt_0034c818();
                    w = rt_002c6d00().lo;
                }
            }
            u = u + w * 0x10000;
            w = u & 0xffffffffffff0000;
            if (e - (w >> 0xe) == 0) {
                l = 0;
            } else {
                u = u >> 0x10;
                if ((0 >> 0x3c & 1) == 0) {
                    if ((0 >> 0x3d & 1) == 0) {
                        rt_00350c38();
                        if ((0 >> 0x3c & 1) == 0) {
                            rt_0007c1c4();
                            rt_002a9ba8();
                        }
                        l = rt_00358a98().lo;
                        if (0) {
                            if (l == 0) goto nil_panic;
                            if (*(unsigned short *)(l + u) == 0xa0d ||
                               (*(unsigned short *)(l + u) & 0x8080) != 0) goto nl_scan3;
                        }
                    } else {
                        if ((!0) && (rt_00352bd4(*(unsigned short *)(0 + u)), 0 || 0 != 0))
                            goto nl_scan3;
                    }
                    l = 1;
                } else {
nl_scan3:
                    rt_0034ba28();
                    l = rt_002c6d00().lo;
                    if (l >= 0x40) continue;
                }
                w = w | l << 8;
            }
            u = w | 0xb;
        }
    }
    rt_00351774(u,0);
    return;
nil_panic:
    rt_00347f2c();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029f368 @ 0x0029f368   (est. sk_swift_str_scan_lines2)
 * Ghidra: void FUN_0029f368(undefined8 param_1,undefined8 param_2,word_t param_3)
 * Second line-scan variant (used by the UTF-16 path) mirroring sk_swift_str_scan_lines.
 * Confidence: low */
void sk_swift_str_scan_lines2(void *a, void *b, word_t c)
{
    word_t u, w, e;
    long l;
    unsigned short ch;
    rt_0035300c();
    rt_00351da8();
    rt_003509ec();
    rt_00354a28();
    if ((c & 0xc) == 0) {
        rt_0034c818();
        c = rt_0001da84().lo;
    }
    if ((0 & 0xc) == 0) {
        rt_0034ba28();
        c = rt_0001da84().lo;
    }
    rt_0034ba28();
    u = rt_00359400().lo;
    e = 0 >> 0xe;
    if (0 < 0) {
        rt_00359ee0(0);
        for (l = 0; u >> 0xe, 0 < l; l = l + -1) {
            if (e <= c && u >> 0xe <= c) goto commit;
            if (u >> 0xe == 0) goto range_panic;
            if (0x1ffff < u) {
                if ((0 >> 0x3c & 1) == 0) {
                    if ((0 >> 0x3d & 1) == 0) {
                        if ((0 >> 0x3c & 1) == 0) {
                            rt_0007c1c4();
                            l = rt_002a9ba8().lo;
                            if (l == 0) goto nil_panic;
                        }
                        ch = *(unsigned short *)(l + (u >> 0x10) + -2);
                    } else {
                        ch = *(unsigned short *)(0 + (u >> 0x10));
                    }
                    if ((ch != 0xa0d) && ((ch & 0x8080) == 0)) goto fwd_cont;
                }
                rt_0034c818();
                rt_002c7020();
            }
fwd_cont:
            rt_003568a8();
        }
        if (e < c || c <= u >> 0xe) goto bwd_done;
    } else {
        w = (0 & 0xffffffffffff) * 4;
        rt_00359ee0();
        for (; u >> 0xe, 0 != 0; ) {
            if (e <= c && c <= u >> 0xe) goto commit;
            if (w <= u >> 0xe) {
range_panic:
                rt_00348614(1);
                rt_0034987c();
                /* WARNING: does not return */
                rt_001afe4c();
            }
            w = u >> 8 & 0x3f;
            if (w == 0) {
                w = u >> 0x10;
                if ((0 >> 0x3c & 1) == 0) {
                    if ((0 >> 0x3d & 1) == 0) {
                        rt_00359ed4();
                        if ((0 >> 0x3c & 1) == 0) {
                            rt_0007c1c4();
                            rt_002a9ba8();
                            rt_00358084();
                        }
                        l = rt_0035a244().lo;
                        if (0) {
                            if (l == 0) goto nil_panic;
                            ch = *(unsigned short *)(l + w);
                            if ((ch == 0xa0d) || ((ch & 0x8080) != 0)) goto nl_scan;
                        }
                    } else {
                        if (w + 1 != 0) {
                            ch = *(unsigned short *)(0 + w);
                            if ((ch == 0xa0d) || ((ch & 0x8080) != 0)) goto nl_scan;
                        }
                    }
                    w = 1;
                } else {
nl_scan:
                    rt_0034c818();
                    rt_002c6d00();
                    w = rt_00358abc().lo;
                }
            }
            u = u + w * 0x10000;
            w = u & 0xffffffffffff0000;
            if (0 * 4 - (w >> 0xe) == 0) {
                l = 0;
            } else {
                u = u >> 0x10;
                if ((0 >> 0x3c & 1) == 0) {
                    if ((0 >> 0x3d & 1) == 0) {
                        rt_00359ed4();
                        if ((0 >> 0x3c & 1) == 0) {
                            rt_0007c1c4();
                            rt_002a9ba8();
                            rt_00358084();
                        }
                        l = rt_00358a98().lo;
                        if (0) {
                            if (l == 0) goto nil_panic;
                            ch = *(unsigned short *)(l + u);
                            if ((ch == 0xa0d) || ((ch & 0x8080) != 0)) goto nl_scan2;
                        }
                    } else {
                        rt_00358074();
                        if ((!0) && (rt_00352bd4(*(unsigned short *)(0 + u)), 0 || 0 != 0))
                            goto nl_scan2;
                    }
                    l = 1;
                } else {
nl_scan2:
                    rt_0034ba28();
                    rt_002c6d00();
                    l = rt_00358abc().lo;
                    if (l >= 0x40) continue;
                }
                w = w | l << 8;
            }
            u = w | 0xb;
        }
        if (c < e || u >> 0xe <= c) {
bwd_done:
            u = 0;
            w = 0;
            goto commit;
        }
    }
commit:
    rt_00353238(u,w,0);
    return;
nil_panic:
    rt_00347f2c();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029f6a8 @ 0x0029f6a8   (est. sk_swift_str_is_sep)
 * Ghidra: undefined8 FUN_0029f6a8(undefined8 param_1,undefined8 param_2,word_t param_3)
 * Tests whether the character at the current index is an ASCII separator (not a
 * newline/0x8080 marker); returns 1 for a plain separator.
 * Confidence: low */
word_t sk_swift_str_is_sep(void *a, void *b, word_t c)
{
    unsigned short ch;
    word_t u;
    rt_0034b430();
    if ((c >> 0x3c & 1) == 0) {
        if ((0 >> 0x3d & 1) == 0) {
            if ((0 >> 0x3c & 1) == 0) {
                rt_0007c1c4();
                u = rt_002a9ba8().lo;
            } else {
                u = rt_00356364().lo;
            }
            if (0 + 1 == 0) {
                return 1;
            }
            if (u == 0) {
                rt_00347f2c();
                /* WARNING: does not return */
                rt_001afe4c();
            }
            ch = *(unsigned short *)(u + 0);
        } else {
            if (0 + 1U == (0 >> 0x38 & 0xf)) {
                return 1;
            }
            ch = *(unsigned short *)(0 + 0);
        }
        rt_00352bd4(ch);
        if (0 == 0) {
            return 1;
        }
    }
    rt_0011aa70();
    return rt_002c6d00().lo;
}

/*--------------------------------------------------------------------*/
/* FUN_0029f764 @ 0x0029f764   (est. sk_swift_str_prev_char)
 * Ghidra: long FUN_0029f764(long param_1,word_t param_2,word_t param_3)
 * Steps one character backward in a UTF-8 string and returns the new byte offset
 * (or 1 if the preceding byte is an ASCII separator).
 * Confidence: low */
long sk_swift_str_prev_char(long a, word_t b, word_t c)
{
    long l;
    if (a < 2) {
        return a;
    }
    if ((c >> 0x3c & 1) == 0) {
        if ((c >> 0x3d & 1) == 0) {
            if ((b >> 0x3c & 1) == 0) {
                a = rt_0035a8bc().lo;
                if (a == 0) {
                    rt_00347f2c(0,0,0);
                    /* WARNING: does not return */
                    rt_001afe4c();
                }
            } else {
                a = (c & 0xfffffffffffffff) + 0x20;
            }
        } else {
            a = 0;
        }
        rt_00352bd4(*(unsigned short *)((long)a + a + -2));
        if (0 != 0 || 0 == 0) {
            return 1;
        }
    }
    return rt_002c7020().lo;
}

/*--------------------------------------------------------------------*/
/* FUN_0029f7f0 @ 0x0029f7f0   (est. sk_swift_str_replace)
 * Ghidra: void FUN_0029f7f0(undefined8 param_1,undefined8 param_2,word_t param_3,word_t param_4)
 * Replaces the string with the contents of a UTF-8/16 buffer: validates the buffer
 * bounds (FUN_0028e8c0) and, if valid, runs the replace sequence and returns;
 * otherwise panics (noreturn) with the "UnsafeBufferPointer" fatal message.
 * Confidence: low */
void sk_swift_str_replace(void *a, void *b, word_t c, word_t d)
{
    sk_u128_t t;
    long l;
    if ((d >> 0x3c & 1) == 0) {
        t = rt_003504d0();
        if (t.lo <= t.hi) {
            if ((d >> 0x3d & 1) == 0) {
                if ((c >> 0x3c & 1) == 0) {
                    rt_00355968();
                    t = rt_002a9ba8();
                } else {
                    t.lo = (d & 0xfffffffffffffff) + 0x20;
                }
                l = t.hi;
                t = rt_0007c1c4(t.lo);
                rt_003520dc(t.lo,t.hi,0);
                t = rt_0028e8c0();
                if ((-1 < t.lo) && (t.hi <= (word_t)l)) {
                    rt_00348e48();
                    rt_001e4cbc();
                    rt_0034de9c();
                    sk_swift_str_finalize(0,0,0);
                    return;
                }
            } else {
                t = rt_0035701c();
                rt_0007c1c4(t.lo,t.hi,0);
                l = 0;
                rt_003520dc();
                t = rt_0028e8c0();
                if ((-1 < t.lo) && (t.hi <= (word_t)l)) {
                    rt_00348e48();
                    rt_001e4cbc();
                    rt_0034de9c();
                    sk_swift_str_finalize(0,0,0);
                    return;
                }
            }
            rt_003481fc();
            /* WARNING: does not return */
            rt_001afe4c();
        }
    } else {
        rt_002bbcd8();
    }
    rt_00347d60();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029f8e4 @ 0x0029f8e4   (est. sk_swift_str_map_call) */
void sk_swift_str_map_call(void **a, void **b)
{
    a[0] = (void *)sk_swift_str_prelude();
}

/*--------------------------------------------------------------------*/
/* FUN_0029f914 @ 0x0029f914   (est. sk_swift_str_map_call_inplace) */
void sk_swift_str_map_call_inplace(void **a)
{
    a[0] = (void *)sk_swift_str_prelude();
}

/*--------------------------------------------------------------------*/
/* FUN_0029f944 @ 0x0029f944   (est. sk_swift_str_store)
 * Ghidra: void FUN_0029f944(void)
 * Runs the line scan and stores the produced index into the caller slot.
 * Confidence: medium */
void sk_swift_str_store(void)
{
    rt_00350258();
    *(word_t *)0 = sk_swift_str_scan_lines();
}

/*--------------------------------------------------------------------*/
/* FUN_0029f984 @ 0x0029f984   (est. sk_swift_str_line_run) */
void sk_swift_str_line_run(void)
{
    rt_00359424();
    sk_swift_str_line_scan();
}

/*--------------------------------------------------------------------*/
/* FUN_0029f99c @ 0x0029f99c   (est. sk_swift_str_slice_iter)
 * Ghidra: undefined1 [16] FUN_0029f99c(undefined8 *param_1,undefined8 *param_2)
 * Builds a Swift Slice iterator over the string: fills param_1[0..2] from the buffer
 * (FUN_00267510) and returns a 16-byte iterator {param_1, code LAB_0029f9ec}.
 * Confidence: medium */
sk_u128_t sk_swift_str_slice_iter(void **a, void **b)
{
    sk_u128_t t;
    t = rt_00267510(0,0,0);
    a[1] = (void *)t.hi;
    a[2] = (void *)t.hi;
    a[0] = (void *)t.lo;
    t.hi = (word_t)a;
    t.lo = (word_t)&LAB_0029f9ec;
    return t;
}

/*--------------------------------------------------------------------*/
/* FUN_0029fa0c @ 0x0029fa0c   (est. sk_swift_str_flush)
 * Ghidra: void FUN_0029fa0c(void)
 * Flushes the pending string state through the UTF-8/16 commit chain.
 * Confidence: low */
void sk_swift_str_flush(void)
{
    rt_00077888();
    rt_00354404();
    rt_002ab8ac();
    rt_00356290();
    rt_0036b270();
    rt_0008412c();
}

/*--------------------------------------------------------------------*/
/* FUN_0029faac @ 0x0029faac   (est. sk_swift_str_call) */
void sk_swift_str_call(void **a, void **b)
{
    a[0] = (void *)rt_001b798c(0,0,0).lo;
}

/*--------------------------------------------------------------------*/
/* FUN_0029fadc @ 0x0029fadc   (est. sk_swift_str_call_inplace) */
void sk_swift_str_call_inplace(void **a)
{
    a[0] = (void *)rt_001b798c(0,0,0).lo;
}

/*--------------------------------------------------------------------*/
/* FUN_0029fb24 @ 0x0029fb24   (est. sk_swift_str_init_empty)
 * Ghidra: void FUN_0029fb24(void)
 * Initializes the string to empty via the builder.
 * Confidence: medium */
void sk_swift_str_init_empty(void)
{
    rt_003532b8();
    rt_002c2da4();
}

/*--------------------------------------------------------------------*/
/* FUN_0029fb40 @ 0x0029fb40   (est. sk_swift_str_iter_call)
 * Ghidra: void FUN_0029fb40(void)
 * Runs the line-scan iterator callback (0029e8dc) over the string words.
 * Confidence: medium */
void sk_swift_str_iter_call(void **a)
{
    rt_001ee030(0,0,sk_swift_str_line_scan);
}

/*--------------------------------------------------------------------*/
/* FUN_0029fb44 @ 0x0029fb44   (est. sk_swift_str_iter_call2)
 * Ghidra: void FUN_0029fb44(void)
 * Identical to sk_swift_str_iter_call.
 * Confidence: medium */
void sk_swift_str_iter_call2(void **a)
{
    rt_001ee030(0,0,sk_swift_str_line_scan);
}

/*--------------------------------------------------------------------*/
/* FUN_0029fb80 @ 0x0029fb80   (est. sk_swift_str_next_break)
 * Ghidra: void FUN_0029fb80(void)
 * Finds the next word-boundary (break) in the string, refcounting the element and
 * committing the advanced index through FUN_002a200c / FUN_0028e8c0. Panics on a
 * nil buffer.
 * Confidence: low */
sk_u128_t sk_swift_str_next_break(void)
{
    sk_u128_t t, r;
    word_t idx, cnt, u;
    unsigned short ch;

    t = rt_00041138();
    idx = t.lo;
    cnt = 0;
    if ((long)0 <= (long)idx) {
        rt_00019858();
        goto commit;
    }
    rt_00351160();
    t = rt_002a9ba8();
    u = idx + 1;
    if (u == t.hi) {
        r.lo = idx + 1;
    } else {
        if (t.lo == 0) goto nil_panic;
        ch = *(unsigned short *)(t.lo + idx);
        rt_00352bd4(ch);
        if (0 || 0 != 0) goto utf16;
    }
    if ((0 >> 0x3d & 1) == 0) {
        if ((0 >> 0x3c & 1) == 0) {
            rt_00351160();
            rt_002a9ba8();
            rt_00351790();
            u = 0;
        } else {
            u = 0;
        }
        rt_00084180();
    } else {
        rt_00084180(0,0,0);
    }
    rt_003520dc();
    t = rt_0028e8c0();
    if ((t.lo < 0) || ((long)u < t.hi)) {
        rt_003481fc();
        /* WARNING: does not return */
        rt_001afe4c();
    }
    rt_00348e48();
    rt_001e4cbc();
    rt_000b43e8();
    sk_swift_ascii_valid((char *)0,0);   /* 002a200c */
    rt_000b4390(0,0,0 & 1);
    sk_swift_str_finalize(0,0,0);        /* 002a2698 */
    idx = idx + 1;
commit:
    rt_0035847c(t.lo,t.hi,idx);
    return t;
utf16:
    t = rt_000b4390();
    t = rt_002c6d00(t.lo,t.hi,0);
    if ((0 >> 0x3c & 1) != 0) {
        rt_002bbcd8();
nil_panic:
        rt_00347f2c();
        /* WARNING: does not return */
        rt_001afe4c();
    }
    r.lo = t.lo + idx;
    if ((long)r.lo < (long)idx) {
        rt_00347d60();
        /* WARNING: does not return */
        rt_001afe4c();
    }
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_0029fcd8 @ 0x0029fcd8   (est. sk_swift_str_next_break_slot)
 * Ghidra: void FUN_0029fcd8(undefined1 (*param_1) [16])
 * Stores the next-break result into the 16-byte caller slot.
 * Confidence: medium */
void sk_swift_str_next_break_slot(void **a)
{
    *a = (void *)sk_swift_str_next_break();
}

/*--------------------------------------------------------------------*/
/* FUN_0029fec0 @ 0x0029fec0   (est. sk_swift_str_eq_sub)
 * Ghidra: word_t FUN_0029fec0(undefined8 param_1,undefined8 param_2,code *param_3,code *param_4,code *param_5,code *param_6)
 * Substring equality dispatch: compares two Swift string values (by pointer and
 * scalar count) through the 002a0f24 string-compare helper, returning 1 if equal.
 * Handles the various stored-representation tags (utf8/utf16/object).
 * Confidence: low */
word_t sk_swift_str_eq_sub(void *a, void *b, sk_fnptr c, sk_fnptr d, sk_fnptr e, sk_fnptr f)
{
    sk_u128_t t, u;
    word_t r, x;
    t = rt_0008e518();
    rt_0034b7e4();
    (*DAT_00658c00)();
    rt_00352330();
    (*DAT_00658c00)();
    rt_0035a6c0();
    (*DAT_00658c00)();
    rt_0034b7e4();
    (*DAT_00658c00)();
    rt_00352330();
    (*DAT_00658c00)();
    rt_00358308();
    rt_00358a80();
    if (0) {
        if (d == 0) {
            u = rt_0008e500(0,0);
            r = u.lo & 0xffffffffffff;
            if ((u.hi & 0x2000000000000000) != 0) {
                r = u.hi >> 0x38 & 0xf;
            }
            x = 0 & 0xffffffffffff;
            if ((0 & 0x2000000000000000) != 0) {
                x = 0 >> 0x38 & 0xf;
            }
            if (u.lo == 0 && r == x) {
                return 1;
            }
            return rt_002a0f24().lo & 1;
        }
        if (d == 0) {
            u = rt_0008e500(0,0);
            r = u.lo & 0xffffffffffff;
            if ((u.hi & 0x2000000000000000) != 0) {
                r = u.hi >> 0x38 & 0xf;
            }
            if ((u.lo == 0) && (0 >> 0x10 == 0) && (r == 0 >> 0x10)) {
                return 1;
            }
            return rt_002a0f24(u.lo,u.hi,0).lo & 1;
        }
    }
    if (c == 0) {
        if (d == 0) {
            rt_003596d0();
            u = rt_0008e500();
            if (((0 == 0 && 0 == 0) && ((u.lo >> 0x10) == 0)) && ((u.hi >> 0x10) == 0)) {
                return 1;
            }
            return rt_002a0f24(0,0,u.lo >> 0x10,u.hi >> 0x10).lo & 1;
        }
        if (d == 0) {
            rt_003596d0();
            u = rt_0008e500(0);
            if (((0 == 0 && 0 == 0) && (u.lo >> 0x10 == 0)) && (u.hi >> 0x10 == 0)) {
                return 1;
            }
            return rt_002a0f24(0,0,u.lo >> 0x10,u.hi >> 0x10,0,0,0,0).lo & 1;
        }
    }
    rt_003512c0();
    rt__indirect(0,0,c);
    rt_00350d14();
    rt_00351214();
    if (rt_00365b6c().lo == 0) {
        rt_003509bc();
        rt__indirect(0,0,c);
        rt_00350efc();
        rt_00351438();
        if ((rt_00365b6c().lo & 1) == 0) {
            rt_00351ec0();
            rt__indirect(0,0,c);
            rt_003568e8();
            rt_0031e030();
            rt_00354dc4();
            rt_00357c04();
            rt_0034ee98();
            rt_0022d2f4();
            e = 0;
        }
    }
    rt_00027754(e);
    rt_0035125c();
    rt_0035156c();
    rt_0035084c(0);
    rt__indirect();
    rt_00351750(0);
    rt_0035084c(0);
    rt__indirect();
    rt_003510c4(0);
    rt__indirect();
    rt_00350d14();
    rt_00352864();
    if ((rt_00365b6c().lo & 1) == 0) {
        rt_0034fe90();
        rt__indirect();
        rt_00350efc();
        rt_00350600();
        if ((rt_00365b6c().lo & 1) == 0) {
            rt_0034fe90();
            rt__indirect();
            rt_0035a5a8();
            rt_0031e030();
            rt_00351d18();
            rt_00357c04();
            rt_0034c694();
            rt_0022d2f4();
            rt_003562d4();
            f = 0;
        }
    }
    rt_00027754(f);
    rt_00351bec();
    rt_0035156c();
    rt_00350494(0);
    rt__indirect();
    rt_00351750();
    rt_00350494(0);
    rt__indirect();
    if (0) {
        rt_003a25d4(0);
        rt_003a25d4(0);
    } else {
        *(unsigned char *)(0 - 0x10) = 0;
        rt_000dbf08();
        rt_0035767c();
        rt_002a0f24();
        rt_0035a104();
        rt_003a25d4();
        rt_003a25d4(0);
    }
    r = rt_00353034().lo;
    return rt_0008e500(r,*(void **)(0 + 0x58)).lo;
}

/*--------------------------------------------------------------------*/
/* FUN_002a02e4 @ 0x002a02e4   (est. sk_swift_str_desc3)
 * Ghidra: void FUN_002a02e4(void)
 * Third descriptor helper: pushes the context and dispatches through the vtable,
 * committing via FUN_0009461c / FUN_00084234.
 * Confidence: low */
void sk_swift_str_desc3(void)
{
    word_t u;
    rt_00084220();
    rt_00348e18();
    (*DAT_00658c00)(0);
    rt_00349db0();
    (*DAT_00658c00)();
    rt_0034ae94();
    (*DAT_00658c00)();
    rt_0034b3d8();
    rt_00352cb0();
    if (0 == 0) {
        u = 0;
    } else {
        rt_00354140();
        if (0 != 0) {
            rt_0034e56c();
            rt__indirect();
            rt_00353d64();
            rt_003508c0(0);
            if (rt_00365b6c().lo == 0) {
                rt_00350624();
                rt__indirect();
                rt_0035484c();
                rt_003508d8(0);
                if (rt_00365b6c().lo == 0) {
                    rt_0011aa70();
                    rt__indirect();
                    rt_0031e030(0);
                    rt_00351a44();
                    rt_00357c04();
                    rt_003502a8();
                    rt_0022d2f4();
                    rt_00351a50();
                }
            }
            goto commit;
        }
        u = 0;
    }
    rt_0036b270(u);
commit:
    rt_0009461c();
    rt_00084234(0,0,0);
}

/*--------------------------------------------------------------------*/
/* FUN_002a043c @ 0x002a043c   (est. sk_swift_str_length)
 * Ghidra: undefined1 [16] FUN_002a043c(void)
 * Returns the string's scalar length as a 16-byte {lo,hi} pair (both halves hold the
 * count).
 * Confidence: low */
sk_u128_t sk_swift_str_length(void)
{
    sk_u128_t t;
    word_t len;
    rt_0035697c();
    rt_00027754();
    rt_00350950();
    rt_000277b8();
    rt_0035037c();
    rt__indirect();
    rt_00310924();
    rt_0035037c();
    rt__indirect();
    len = 0 >> 0x10;
    t.lo = len;
    t.hi = len;
    return t;
}

/*--------------------------------------------------------------------*/
/* FUN_002a04cc @ 0x002a04cc   (est. sk_swift_str_eq_run) */
void sk_swift_str_eq_run(void)
{
    sk_swift_str_eq_sub(0,0,0,0,0,0);
    rt_00356d20();
}

/*--------------------------------------------------------------------*/
/* FUN_002a06c4 @ 0x002a06c4   (est. sk_swift_str_eq_sub2)
 * Ghidra: word_t FUN_002a06c4(undefined8 param_1,undefined8 param_2,long param_3,long param_4,code *param_5,undefined8 param_6)
 * Second substring-equality dispatch (returns 0 on equal, 1 on not): compares the
 * receiver string words with the argument string words via 002a0f24, handling all
 * stored-representation tags. Ends via FUN_0008e500.
 * Confidence: low */
word_t sk_swift_str_eq_sub2(void *a, void *b, long c, long d, sk_fnptr e, void *f)
{
    sk_u128_t t, u;
    word_t r;
    rt_0008e518();
    rt_003504d0();
    rt_0034b7e4();
    (*DAT_00658c00)();
    rt_00352330();
    (*DAT_00658c00)();
    rt_0035a6c0();
    (*DAT_00658c00)();
    rt_0034b7e4();
    (*DAT_00658c00)();
    rt_00352330();
    (*DAT_00658c00)();
    (*DAT_00658c00)();
    rt_00358a80();
    if (0) {
        if (d == 0) {
            u = rt_0008e500(0,0);
            r = u.lo & 0xffffffffffff;
            if ((u.hi & 0x2000000000000000) != 0) {
                r = u.hi >> 0x38 & 0xf;
            }
            if (u.lo == 0 && r == 0) {
                return 0;
            }
            return rt_002a0f24(u.lo,u.hi,0,r,0,0,0).lo & 1;
        }
        if (d == 0) {
            u = rt_0008e500(0,0);
            r = u.lo & 0xffffffffffff;
            if ((u.hi & 0x2000000000000000) != 0) {
                r = u.hi >> 0x38 & 0xf;
            }
            if ((u.lo == 0) && (0 >> 0x10 == 0) && (r == 0 >> 0x10)) {
                return 0;
            }
            return rt_002a0f24(u.lo,u.hi,0).lo & 1;
        }
    } else {
        if (c == 0) {
            if (d == 0) {
                u = rt_0008e500(0,0);
                r = 0;
                if (((0 == 0 && 0 == 0) && (u.lo >> 0x10 == 0)) && (u.hi >> 0x10 == r)) {
                    return 0;
                }
                return rt_002a0f24(0,0,u.lo >> 0x10,u.hi >> 0x10).lo & 1;
            }
            if (d == 0) {
                u = rt_0008e500(0,0,0);
                if (((0 == 0 && 0 == 0) && (u.lo >> 0x10 == 0)) && (u.hi >> 0x10 == 0)) {
                    return 0;
                }
                return rt_002a0f24(0,0,u.lo >> 0x10,u.hi >> 0x10,0,0,0,0).lo & 1;
            }
        }
    }
    rt_00351f88();
    rt__indirect(0,0,c);
    rt_00350d14();
    rt_00353050();
    if (rt_00365b6c().lo == 0) {
        rt_00351714();
        rt__indirect(0,0,c);
        rt_00350efc();
        rt_00352314();
        if (rt_00365b6c().lo == 0) {
            rt_003512c0();
            rt__indirect(0,0,c);
            rt_003560a8();
            rt_0031e030();
            rt_00357c04(0);
            rt_0034ff78();
            rt_0022d2f4();
            e = 0;
        }
    }
    rt_00027754(e);
    rt_003514b8();
    rt_0035156c();
    rt_00351414(0);
    rt__indirect();
    rt_00351750(0);
    rt_00351414(0);
    rt__indirect();
    rt_00352cb0();
    if (d == 0) {
        rt_0036b270(0);
    } else {
        rt_00354140();
        if (d != 0) {
            rt_003501a8();
            rt__indirect();
            rt_00350d14();
            rt_00077894();
            if (rt_00365b6c().lo == 0) {
                rt_003501a8();
                rt__indirect();
                rt_00350efc();
                rt_00077894();
                if (rt_00365b6c().lo == 0) {
                    rt_00350524();
                    rt__indirect(0,0,d);
                    rt_00355cb0();
                    rt_0031e030();
                    rt_00351a44();
                    rt_00357c04();
                    rt_0034c694();
                    rt_0022d2f4();
                    rt_00351f28();
                }
            }
            goto commit2;
        }
        rt_0036b270(0);
    }
commit2:
    rt_00027754(f);
    rt_00352894();
    rt_0035156c();
    rt_00350c2c(0);
    rt__indirect();
    rt_00351750(0);
    rt_00350c2c(0);
    rt__indirect();
    if (0) {
        rt_003a25d4(0);
        rt_003a25d4(0);
    } else {
        *(unsigned char *)(0 - 0x10) = 1;
        rt_0035284c();
        rt_00356170();
        rt_002a0f24();
        rt_003a25d4(0);
        rt_003a25d4(0);
    }
    r = rt_00353034().lo;
    return rt_0008e500(r,*(void **)(0 + 0x58)).lo;
}

/*--------------------------------------------------------------------*/
/* FUN_002a0b5c @ 0x002a0b5c   (est. sk_swift_str_bool) */
uint sk_swift_str_bool(void)
{
    return rt_0035642c().lo & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002a0b80 @ 0x002a0b80   (est. sk_swift_str_bool_run) */
void sk_swift_str_bool_run(void)
{
    rt_0035642c();
    rt_00356d20();
}

/*--------------------------------------------------------------------*/
/* FUN_002a0ba4 @ 0x002a0ba4   (est. sk_swift_str_eq_sub_run) */
void sk_swift_str_eq_sub_run(void)
{
    sk_swift_str_eq_sub2(0,0,0,0,0,0);
    rt_00356d20();
}

/*--------------------------------------------------------------------*/
/* FUN_002a0c78 @ 0x002a0c78   (est. sk_swift_str_cmp2)
 * Ghidra: undefined4 FUN_002a0c78(undefined8 param_1,undefined8 param_2,long param_3)
 * Two-way character comparison helper; returns the comparison result word.
 * Confidence: low */
word_t sk_swift_str_cmp2(void *a, void *b, long c)
{
    word_t u;
    rt_003576ec();
    u = 0;
    if (0 != c) {
        u = 0;
    }
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_002a0cb0 @ 0x002a0cb0   (est. sk_swift_str_nonempty)
 * Ghidra: undefined8 FUN_002a0cb0(void)
 * Returns 1 if the string is non-empty, else 0.
 * Confidence: medium */
word_t sk_swift_str_nonempty(void)
{
    rt_003594f4();
    if (0) {
        if ((0 & 0xff) == 0) {
            return 0;
        }
    } else {
        rt_00351db4(0);
        if (0) {
            return 0;
        }
    }
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002a0cf8 @ 0x002a0cf8   (est. sk_swift_str_cmp_ci)
 * Ghidra: word_t FUN_002a0cf8(word_t param_1,word_t param_2,word_t param_3,word_t param_4,char param_5)
 * Byte-swapped (endianness-normalized) case-insensitive comparison of two 8-byte
 * scalar pairs; falls back to sk_swift_str_compare (002a0d50) for non-ASCII.
 * Confidence: medium */
word_t sk_swift_str_cmp_ci(word_t a, word_t b, word_t c, word_t d, char e)
{
    word_t u, v;
    bool r;
    if ((((b ^ 0xffffffffffffffff) & 0x6000000000000000) == 0) &&
       (((d ^ 0xffffffffffffffff) & 0x6000000000000000) == 0)) {
        v = (b & 0xff00ff00ff00ff00) >> 8 | (b & 0xff00ff00ff00ff) << 8;
        v = (v & 0xffff0000ffff0000) >> 0x10 | (v & 0xffff0000ffff) << 0x10;
        u = (d & 0xff00ff00ff00ff00) >> 8 | (d & 0xff00ff00ff00ff) << 8;
        u = (u & 0xffff0000ffff0000) >> 0x10 | (u & 0xffff0000ffff) << 0x10;
        r = (v >> 0x20 | v << 0x20) < (u >> 0x20 | u << 0x20);
        if (e != '\x01') {
            r = b == d;
        }
        v = (a & 0xff00ff00ff00ff00) >> 8 | (a & 0xff00ff00ff00ff) << 8;
        v = (v & 0xffff0000ffff0000) >> 0x10 | (v & 0xffff0000ffff) << 0x10;
        u = (c & 0xff00ff00ff00ff00) >> 8 | (c & 0xff00ff00ff00ff) << 8;
        u = (u & 0xffff0000ffff0000) >> 0x10 | (u & 0xffff0000ffff) << 0x10;
        if (a != c) {
            r = e == '\x01' && (v >> 0x20 | v << 0x20) < (u >> 0x20 | u << 0x20);
        }
        return (word_t)r;
    }
    return sk_swift_str_compare(a,b,c,d);
}

/*--------------------------------------------------------------------*/
/* FUN_002a0d50 @ 0x002a0d50   (est. sk_swift_str_compare)
 * Ghidra: word_t FUN_002a0d50(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Full string comparison: for UTF-16/object strings delegates to FUN_002a177c, else
 * compares the two buffers via 002a0ed0 and returns (result & 1).
 * Confidence: low */
word_t sk_swift_str_compare(word_t a, word_t b, word_t c, word_t d)
{
    word_t u;
    sk_u128_t t;
    if (((b | d) >> 0x3c & 1) != 0) {
        rt_0034da28(c & 0xffffffffffff);
        t = rt_000b4390();
        sk_swift_str_compare_slices();
        u = 0;
        goto out;
    }
    if ((b & 0x2000000000000000) != 0) {
        u = b;
    } else {
        u = a;
    }
    if ((u >> 0x3e & 1) == 0) {
        if ((b >> 0x3d & 1) == 0) goto ascii;
        goto utf16;
    } else {
        if ((b >> 0x3d & 1) != 0) goto utf16;
ascii:
        if ((a >> 0x3c & 1) == 0) {
            t = rt_002a9ba8(a,b);
        } else {
            t.lo = a & 0xffffffffffff;
            t.hi = (b & 0xfffffffffffffff) + 0x20;
        }
        if ((d >> 0x3d & 1) == 0) {
            if ((c >> 0x3c & 1) == 0) {
                rt_002a9ba8(c,d);
            } else {
                t = rt_00358044();
            }
            rt_00359484(t.lo,t.hi);
            u = sk_swift_str_compare_sub(0,0,0,0,0,0);
            goto out;
        }
        t = rt_003584a8();
    }
    rt_00359484(t.lo,t.hi);
    u = sk_swift_str_compare_sub(0,0,0,0,0,0);
utf16:
    u = 0;
out:
    return u & 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002a0ed0 @ 0x002a0ed0   (est. sk_swift_str_compare_sub)
 * Ghidra: word_t FUN_002a0ed0(undefined8 param_1,long param_2,undefined8 param_3,long param_4,char param_5,uint param_6)
 * Compares two byte runs [param_2]/[param_4] via memcmp (002a1278), returning
 * less/equal/greater; when the casefold flag param_6&1 is clear it uses the
 * scalar compare 002a12b4.
 * Confidence: medium */
word_t sk_swift_str_compare_sub(void *a, long b, void *c, long d, char e, uint f)
{
    long l;
    bool r;
    if ((f & 1) != 0) {
        if (e == '\x01' || b == d) {
            l = sk_swift_memcmp_limited(a,b,c,d);
            r = l == 0;
            if (e == '\x01') {
                r = l < 0;
            }
            return (word_t)r;
        }
        return 0;
    }
    return sk_swift_str_compare_bytes().lo;
}

/*--------------------------------------------------------------------*/
/* FUN_002a0f24 @ 0x002a0f24   (est. sk_swift_str_compare_eq)
 * Ghidra: void FUN_002a0f24(void)
 * Equality comparison of two strings: normalizes both buffers (FUN_002a9ba8 /
 * inline forms), checks bounds via FUN_0028e8c0, and returns (result&1) through
 * 002a0ed0 / FUN_00358344. Panics (noreturn) on an invalid range.
 * Confidence: low */
void sk_swift_str_compare_eq(void)
{
    sk_u128_t t;
    word_t u, len;
    rt_00358374();
    t = rt_00359df4();
    u = t.hi;
    if (((u >> 0x3c & 1) != 0) || ((0 >> 0x3c & 1) != 0)) {
        rt_00350470();
        rt_00351b78();
        sk_swift_str_compare_slices();
        u = 0;
        rt_00358344(u & 1,0);
        return;
    }
    len = t.lo & 0xffffffffffff;
    if ((u & 0x2000000000000000) != 0) {
        len = u;
    }
    if ((len >> 0x3e & 1) == 0) {
        if ((u >> 0x3d & 1) != 0) goto utf16;
        if ((t.lo >> 0x3c & 1) == 0) {
            rt_002a9ba8(len,t.lo,u);
            rt_00351790();
        } else {
            len = t.lo & 0xffffffffffff;
        }
        rt_00350738();
        rt_003520dc();
        t = rt_0028e8c0();
        if ((t.lo < 0) || ((long)len < t.hi)) goto range_panic;
        rt_00348e48();
        rt_001e4cbc();
        rt_00357b3c();
        if ((0 >> 0x3d & 1) == 0) {
            if ((0 >> 0x3c & 1) == 0) {
                rt_00350470();
                rt_002a9ba8();
                rt_00351790();
            } else {
                len = 0 & 0xffffffffffff;
            }
            rt_00100efc();
            rt_003520dc();
            t = rt_0028e8c0();
            if ((-1 < t.lo) && (t.hi <= (long)len)) {
                rt_00348e48();
                rt_001e4cbc();
                rt_00351790();
                rt_000a6e14();
                rt_00359484();
                rt_00358344();
                sk_swift_str_compare_sub(0,0,0,0,0,0);
                return;
            }
            goto range_panic;
        }
        rt_00359f54();
    } else {
        if ((u >> 0x3d & 1) == 0) goto ascii;
utf16:
        len = u >> 0x38 & 0xf;
        rt_00350738(0,0,0);
        rt_003520dc();
        t = rt_0028e8c0();
        if ((t.lo < 0) || ((long)len < t.hi)) goto range_panic;
        rt_00348e48();
        rt_001e4cbc();
        rt_00357b3c();
        if ((0 >> 0x3d & 1) == 0) {
            if ((0 >> 0x3c & 1) == 0) {
                rt_00350470();
                rt_002a9ba8();
                rt_00351790();
            } else {
                len = 0 & 0xffffffffffff;
            }
        } else {
            rt_00359f54();
        }
    }
ascii:
    rt_00100efc();
    rt_003520dc();
    t = rt_0028e8c0();
    if ((-1 < t.lo) && (t.hi <= (long)len)) {
        rt_00348e48();
        rt_001e4cbc();
        rt_00351790();
        rt_000a6e14();
        rt_00359484();
        u = sk_swift_str_compare_sub(0,0,0,0,0,0);
        rt_00358344(u & 1,0);
        return;
    }
range_panic:
    rt_003481fc();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a1120 @ 0x002a1120   (est. sk_swift_str_transform)
 * Ghidra: void FUN_002a1120(undefined8 param_1,undefined8 param_2,undefined8 param_3,word_t param_4,word_t param_5,word_t param_6,undefined8 param_7)
 * String transform helper: normalizes the second string buffer, checks its range, and
 * runs the transform closure; the UTF-16 path sets up a stack frame with callbacks
 * FUN_0031e240 / FUN_00346774. Commits via FUN_00358fc8.
 * Confidence: low */
void sk_swift_str_transform(void *a, void *b, void *c, word_t d, word_t e, word_t f, void *g)
{
    sk_u128_t t;
    word_t len;
    rt_00358fb4();
    rt_00359640();
    if ((f >> 0x3d & 1) == 0) {
        rt_00354b2c();
        rt_00353e50();
        if ((e >> 0x3c & 1) == 0) {
            rt_002a9ba8(e,f);
            rt_00351790();
        } else {
            len = e & 0xffffffffffff;
        }
        rt_000a6e14();
        rt_003520dc();
        t = rt_0028e8c0();
        if ((t.lo < 0) || ((long)len < t.hi)) {
            rt_003481fc();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_00348e48();
        rt_001e4cbc();
        rt_00353f88();
        rt__indirect();
    } else {
        (*DAT_00658c00)(f >> 0x38 & 0xf);
        rt_00355c94();
        rt_003519e8();
        rt_0034a210();
        rt_00002534();
        rt_00355704(0,rt_00346774);
        rt_00350bfc();
        rt_003576bc();
        rt_00291d70();
    }
    rt_00358fc8(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002a1278 @ 0x002a1278   (est. sk_swift_memcmp_limited)
 * Ghidra: long FUN_002a1278(undefined8 param_1,long param_2,undefined8 param_3,long param_4)
 * memcmp over the shorter of the two run lengths; returns the byte difference or the
 * length difference when equal.
 * Confidence: medium */
long sk_swift_memcmp_limited(void *a, long b, void *c, long d)
{
    long l, n;
    int r;
    l = d;
    if (b - d == 0 || b < d) {
        l = b;
    }
    r = rt_001145b0(a,c,l).lo;
    n = b - d;
    if (r != 0) {
        n = (long)r;
    }
    return n;
}

/*--------------------------------------------------------------------*/
/* FUN_002a12b4 @ 0x002a12b4   (est. sk_swift_str_compare_bytes)
 * Ghidra: void FUN_002a12b4(void)
 * Byte-wise UTF-8 string comparison with scalar decoding: scans the two runs,
 * decoding UTF-8 scalars (via sk_swift_utf8_is_valid / sk_swift_utf8_check),
 * and commits the ordering through FUN_00351d30. Panics on an invalid slice.
 * Confidence: low */
void sk_swift_str_compare_bytes(void)
{
    word_t n, len, u, v;
    long l;
    unsigned char b0, b1;
    uint c0, c1;
    sk_u128_t t;

    rt_00351e20();
    rt_0034b318();
    n = 0;
    len = 0;
    if (0 <= 0) {
        len = 0;
    }
    do {
        if ((len & ((long)len >> 0x3f ^ 0xffffffffffffffffU)) == n) {
            rt_00351d30(0,0);
            return;
        }
        if (*(char *)(0 + n) != *(char *)(0 + n)) {
            rt_0034db48();
            l = sk_swift_utf8_scanback(0,0,0);
            b0 = *(unsigned char *)(0 + l);
            c0 = (uint)b0;
            if ((char)b0 < '\0') {
                rt_00352af0();
                switch (0) {
                default: l = 1; break;
                case 1: rt_00353ff4(); c0 = (b0 & 0x1f) << 6; l = 2; break;
                case 2: rt_00352e9c(); c0 = (b0 & 0xf) << 0xc | (0 & 0x3f) << 6 | 0 & 0x3f; l = 3; break;
                case 3: rt_0034c6d4(); c0 = (b0 & 0xf) << 0x12 | (0 & 0x3f) << 0xc | (0 & 0x3f) << 6 | 0 & 0x3f; l = 4;
                }
            } else {
                l = 1;
            }
            b1 = *(unsigned char *)(0 + l);
            c1 = (uint)b1;
            if ((char)b1 < '\0') {
                rt_00352af0();
                switch (0) {
                default: n = 1; break;
                case 1: rt_00353ff4(); c1 = (b1 & 0x1f) << 6; n = 2; break;
                case 2: rt_00352e9c(); c1 = (b1 & 0xf) << 0xc | (0 & 0x3f) << 6 | 0 & 0x3f; n = 3; break;
                case 3: rt_0034c6d4(); rt_0035a0c4(); n = 4;
                }
            } else {
                n = 1;
            }
            u = sk_swift_utf8_is_valid(c0);
            if (((u & 1) != 0) && ((u = sk_swift_utf8_is_valid(c1), (u & 1) != 0))) {
                rt_000bd3a4(l + l);
                u = sk_swift_utf8_check(0,0,0);
                if ((u & 1) != 0) {
                    rt_00350548(n + l);
                    u = sk_swift_utf8_check(0,0,0);
                    if ((u & 1) != 0) {
                        rt_00351d30(0 == 1 && c0 < c1,0);
                        return;
                    }
                }
            }
            rt_0034db48();
            sk_swift_utf8_scanfwd(0,0,0);
            t = rt_000b43d0();
            sk_swift_utf8_scanfwd(t.lo,t.hi,n);
            rt_00077708();
            t = rt_001d9840();
            if ((-1 < t.lo) && (t.hi <= len)) {
                rt_00348e48();
                rt_001e4cbc();
                rt_00351f28();
                rt_0034ed68();
                t = rt_001d9840();
                if ((-1 < t.lo) && (t.hi <= len)) {
                    rt_00348e48();
                    t = rt_001e4cbc();
                    n = t.lo + 0x7fffffffffffffe0;
                    u = t.hi & 0xffffffffffff;
                    if ((n & 0x2000000000000000) != 0) {
                        u = n >> 0x38 & 0xf;
                    }
                    sk_swift_str_compare_slices();
                    rt_00351d30(0,0);
                    return;
                }
            }
            rt_003481fc();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        n = n + 1;
    } while (1);
}

/*--------------------------------------------------------------------*/
/* FUN_002a1574 @ 0x002a1574   (est. sk_swift_utf8_scanback)
 * Ghidra: long FUN_002a1574(long param_1,long param_2,long param_3)
 * Scans backward from param_3 to the start of the current UTF-8 scalar.
 * Confidence: medium */
long sk_swift_utf8_scanback(long a, long b, long c)
{
    long l;
    l = c;
    if (c != b) {
        do {
            c = l;
            l = c + -1;
        } while (*(char *)(a + c) < -0x40);
    }
    return c;
}

/*--------------------------------------------------------------------*/
/* FUN_002a1598 @ 0x002a1598   (est. sk_swift_utf8_is_valid)
 * Ghidra: bool FUN_002a1598(uint param_1)
 * Returns true if the scalar is below 0x300 or not a surrogate/overlong form.
 * Confidence: medium */
bool sk_swift_utf8_is_valid(uint c)
{
    word_t u;
    if (c < 0x300) {
        return true;
    }
    u = rt_003d3550().lo;
    return (u & 0x7fe) == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002a15cc @ 0x002a15cc   (est. sk_swift_utf8_check)
 * Ghidra: undefined8 FUN_002a15cc(long param_1,long param_2,long param_3)
 * Validates a multi-byte UTF-8 scalar starting at offset param_1 of param_2,
 * decoding its width and checking the scalar via sk_swift_utf8_is_valid.
 * Confidence: medium */
word_t sk_swift_utf8_check(long a, long b, long c)
{
    unsigned char *p, b0;
    uint v;
    int w;
    if ((a != 0) && (a != c)) {
        p = (unsigned char *)(b + a);
        b0 = *p;
        if (0xcb < b0) {
            w = (int)LZCOUNT((uint)b0 << 0x18 ^ 0xffffffff);
            v = (uint)b0;
            if (w == 2) {
                v = (v & 0x1f) << 6;
            } else if (w == 3) {
                v = (v & 0xf) << 0xc | (p[1] & 0x3f) << 6;
            } else {
                v = (v & 0xf) << 0x12 | (p[1] & 0x3f) << 0xc | (p[2] & 0x3f) << 6;
            }
            return sk_swift_utf8_is_valid(v | p[w] & 0x3f);
        }
    }
    return 1;
}

/*--------------------------------------------------------------------*/
/* FUN_002a1648 @ 0x002a1648   (est. sk_swift_utf8_scanfwd)
 * Ghidra: long FUN_002a1648(long param_1,long param_2,word_t param_3)
 * Scans forward to the start of the next UTF-8 scalar from offset param_3 of
 * param_1, skipping continuation bytes; returns the new offset.
 * Confidence: medium */
long sk_swift_utf8_scanfwd(long a, long b, word_t c)
{
    unsigned char *p, b0;
    uint v;
    word_t u;
    long off;
    if ((long)c < b) {
        u = ~c;
        p = (unsigned char *)(a + c);
        do {
            b0 = *p;
            u = u + 1;
            p = p - 1;
        } while ((char)b0 < -0x40);
        if (u == 0) {
            off = 0;
        } else {
            off = -(long)u;
            while (1) {
                p = (unsigned char *)(a + off);
                b0 = *p;
                if (-1 < (char)b0) break;
                v = (uint)b0;
                switch ((int)LZCOUNT((int)b0 << 0x18 ^ 0xffffffff)) {
                default: goto skip;
                case 2: v = (v & 0x1f) << 6; break;
                case 3: v = (v & 0xf) << 0xc | (p[1] & 0x3f) << 6; break;
                case 4: v = (v & 0xf) << 0x12 | (p[1] & 0x3f) << 0xc | (p[2] & 0x3f) << 6;
                }
                if (v < 0x300) {
                    return off;
                }
                u = rt_003d3550(v | *p & 0x3f).lo;
                if ((u & 0x7fe) == 0) {
                    return off;
                }
                off = off - 1;
                if (*(char *)(a + off) < -0x40) {
                    do {
                        off = off;
                        off = off - 1;
                    } while (*(char *)(a - 2 + off) < -0x40);
                    off = off + -2;
                }
                if (off == 0) {
                    return 0;
                }
            }
        }
    }
skip:
    return off;
}

/*--------------------------------------------------------------------*/
/* FUN_002a177c @ 0x002a177c   (est. sk_swift_str_compare_slices)
 * Ghidra: void FUN_002a177c(void)
 * Compares two string slices: normalizes both, checks ranges, and computes the
 * ordering via sk_swift_memcmp_limited, committing through FUN_00353238. Panics
 * on an invalid range.
 * Confidence: low */
void sk_swift_str_compare_slices(void)
{
    sk_u128_t t;
    word_t len;
    long l;
    rt_0035300c();
    t = rt_0034d6d8();
    if (0 == 0) {
        if ((0 >> 0x3d & 1) == 0) {
            if ((0 >> 0x3c & 1) == 0) {
                rt_000b43d0();
                rt_002a9ba8();
                rt_00351790();
            } else {
                len = 0 & 0xffffffffffff;
            }
            rt_003510ac();
            rt_003520dc();
            t = rt_0028e8c0();
            if ((t.lo < 0) || ((long)len < t.hi)) goto range_panic;
            rt_00348e48();
            t = rt_001e4cbc();
        } else {
            len = 0 >> 0x38 & 0xf;
            rt_003510ac(t.lo,t.hi,0);
            rt_003520dc();
            t = rt_0028e8c0();
            if ((t.lo < 0) || ((long)len < t.hi)) goto range_panic;
            rt_00348e48();
            t = rt_001e4cbc();
        }
        rt_00350518();
        rt_003520dc();
        t = rt_0028e8c0();
        if ((t.lo < 0) || ((long)len < t.hi)) {
range_panic:
            rt_003481fc();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_00348e48();
        rt_001e4cbc();
        rt_00351790();
        l = sk_swift_memcmp_limited(t.lo,t.hi,0,0);
        if (l == 0) {
            rt_00353238(0 ^ 1,0);
            return;
        }
    }
    rt_0034f444();
    sk_swift_str_hash();
    rt_00353238(0 & 1,0);
}

/*--------------------------------------------------------------------*/
/* FUN_002a196c @ 0x002a196c   (est. sk_swift_str_hash)
 * Ghidra: void FUN_002a196c(void)
 * String hashing: iterates the characters, maintaining a pair of growth stacks
 * (local_48/local_b0 tagged with local_46/local_ae), folding each UTF-8 scalar into
 * the running hash, and commits the result via FUN_0008e500. Heavily register-
 * artifact-laden; structure preserved.
 * Confidence: low */
void sk_swift_str_hash(void)
{
    word_t c, u;
    rt_0008e518();
    rt_00359b18();
    rt_0035089c();
    rt_00353b70(0,0);
    rt_00354404(0,0,0,0);
    rt_002ab8ac();
    rt_00356290();
    rt_000a6fe0();
    rt_00351e3c(0,0);
    rt_00354404();
    rt_002ab8ac();
    rt_00356290();
    rt_00353360(0);
    rt_00352b98();
    rt_0036b270(0);
    rt_0036b270();
    do {
        (*DAT_00658c00)();
        rt_00355b48();
        c = 0;
        if (c) {
            if ((0 & 1) != 0) {
                c = 0;
            } else {
                c = rt_0026398c(0).lo;
                rt_0035a110();
                if (c) {
                    rt_0036b270(0);
                    sk_ubp_append2();
                    rt_003a25d4(0);
                }
            }
        }
        rt_00355b48();
        if (0) {
            rt_00358034();
            rt_003511d8();
            rt_00344e54();
            rt_003511d8(0);
            rt_00344e54();
            rt_00353130();
            rt_00353238(0 & 0,0);
            rt_0008e500(0 & 1,0);
            return;
        }
        rt_00358034();
        rt_003511d8();
        rt_00344e54();
        rt_003511d8(0);
        rt_00344e54();
        rt_00353238(0,0);
        rt_0008e500(0 & 1,0);
        return;
    } while (1);
}

/*--------------------------------------------------------------------*/
/* FUN_002a200c @ 0x002a200c   (est. sk_swift_ascii_valid)
 * Ghidra: bool FUN_002a200c(char *param_1,word_t param_2)
 * ASCII validity check over param_2 bytes: word-wise tests with the 0x8080... high
 * bit mask; returns true if all bytes are ASCII (high bit clear).
 * Confidence: medium */
bool sk_swift_ascii_valid(char *p, word_t n)
{
    word_t u;
    char c;
    if ((long)n < 8) {
        if (p == (char *)0x0) {
            return true;
        }
        do {
            if (n == 0) {
                return true;
            }
            c = *p;
            n = n - 1;
            p = p + 1;
        } while (-1 < c);
        return false;
    }
    if (n < 0x20) {
        for (u = 0; ; ) {
            if ((long)(n - 8) <= (long)u) {
                u = *(unsigned long *)(p + (n - 8));
                goto word_check;
            }
            if ((*(unsigned long *)(p + u) & 0x8080808080808080) != 0) {
                return false;
            }
            u = u + 8;
        }
    }
    for (u = 0; ; ) {
        if ((long)(n - 0x20) <= (long)u) {
            u = *(unsigned long *)(p + (n - 0x20));
            goto word_check;
        }
        if ((*(unsigned long *)(p + u) | (*(unsigned long *)(p + u + 8))) == 0) {
            /* loop continues */
        }
        if ((*(unsigned long *)(p + u) & 0x8080808080808080) != 0) {
            return false;
        }
        u = u + 0x20;
    }
word_check:
    return (u & 0x8080808080808080) == 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002a20cc @ 0x002a20cc   (est. sk_swift_str_copyin)
 * Ghidra: void FUN_002a20cc(undefined8 param_1,long param_2)
 * Copies param_2 bytes into the small-string storage: for short (<16) inline forms it
 * runs the byte store; for longer forms it uses FUN_00354988/FUN_00355c10.
 * Confidence: low */
void sk_swift_str_copyin(void *a, long b)
{
    word_t u;
    if (b == 0) {
        rt_0011e71c();
    } else if (b < 0x10) {
        rt_00358768();
        if (0 < 0) {
            rt_00347da8();
            rt_003504b8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_0034e0b4();
        do {
            rt_003496b0();
        } while (!0);
        if (8 < 0) {
            rt_00348034();
            rt_003504b8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_0034da18();
        do {
            rt_0034b918();
        } while (!0);
        rt_0034ec0c();
        u = 0xe000000000000000;
        rt_00354b38(u);
    } else {
        rt_00354988(a);
        rt_00355c10();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a216c @ 0x002a216c   (est. sk_swift_str_copy3) */
void sk_swift_str_copy3(void *a, void *b, void *c)
{
    sk_ubp_alloc_raw(a,b,b,c);
}

/*--------------------------------------------------------------------*/
/* FUN_002a218c @ 0x002a218c   (est. sk_swift_utf8_decode)
 * Ghidra: void FUN_002a218c(void)
 * UTF-8 decoder over the string buffer: scans scalars (validating leading-byte
 * classes), handles malformed sequences via FUN_0034a880, and commits the decoded
 * scalar through FUN_001bbec4/FUN_001ff1a4. Panics (noreturn) on overflow.
 * Confidence: low */
void sk_swift_utf8_decode(void)
{
    sk_u128_t t;
    word_t len, u;
    long off;
    rt_00357ca0();
    rt_003504d0();
    t = sk_swift_ascii_valid((char *)0,0);
    off = 0;
    if (0) {
        rt_0034a880();
        rt_0011aa70();
        rt_001d9840();
        t = rt_00351a50();
        rt_00350298();
        rt_001ff1a4();
    }
    rt_003513fc();
    rt_001ff4e0();
    rt_00352c80();
    rt_003504a0(2);
    rt_003547c8();
    t = rt_001bbec4();
    u = t.hi;
    if (u != t.hi) {
        rt_00356358(u,u,t.hi);
        u = rt_001ff1a4().lo;
        u = (u & 0xff) << 8;
    }
    rt_003504a0(1);
    rt_003547c8();
    t = rt_001bbec4();
    u = t.hi;
    if (u != t.hi) {
        rt_00356358(u,u,t.hi);
        u = (u | rt_001ff1a4().lo & 0xff) << 8;
    }
    rt_003504a0(off);
    rt_003547c8();
    t = rt_001ff1a4();
    u = u | t.lo & 0xff;
    if ((u & 0xc0f0) == 0x80e0) {
        off = 1;
        if ((u & 0x200f) != 0x200d && (u & 0x200f) != 0) {
            off = 2;
        }
    } else if ((u & 0xc0f8) == 0x80f0) {
        off = 1;
        if (((u & 0x3007) != 0) && (((u & 0x3007) >> 8 | (t.lo & 7) << 8) < 0x401)) {
            off = 2;
            if ((u & 0xc00000) == 0x800000) {
                off = 3;
            }
        }
    } else {
        off = 1;
    }
    rt_00100efc(t.lo,t.hi,off);
    rt_00357c44();
}

/*--------------------------------------------------------------------*/
/* FUN_002a2698 @ 0x002a2698   (est. sk_swift_str_finalize)
 * Ghidra: void FUN_002a2698(undefined8 param_1,long param_2,uint param_3)
 * Finalizes a Swift String into its inline/small representation: for 8-byte (and
 * short) forms runs the inline byte-store; for longer forms uses 002a4b90 +
 * FUN_00355c10. Panics (noreturn) on a negative count.
 * Confidence: low */
void sk_swift_str_finalize(void *a, long b, uint c)
{
    word_t u;
    if (b == 0) {
        rt_0011e71c();
    } else if (b < 0x10) {
        rt_00347da8();
        rt_0034e0b4();
        do {
            rt_003496b0();
        } while (!0);
        if (8 < 0) {
            rt_00348034();
            rt_003504b8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_0034da18();
        do {
            rt_0034b918();
        } while (!0);
        rt_0034ec0c();
        u = 0xe000000000000000;
        rt_00354b38(u);
    } else {
        sk_ubp_alloc_raw(a,b,b,c & 1);
        rt_00355c10();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a2748 @ 0x002a2748   (est. sk_swift_utf8_encode_buf)
 * Ghidra: void FUN_002a2748(void)
 * UTF-8 encoder into the caller's string buffer: grows the buffer, decodes each
 * scalar via sk_swift_utf8_decode (002a218c), and appends bytes with the
 * scalar-width primitives. Panics (noreturn) on negative/invalid ranges.
 * Confidence: low */
void sk_swift_utf8_encode_buf(void)
{
    word_t len, u;
    long l;
    sk_u128_t t;
    rt_003565a8();
    l = 0 + 0xf;
    if (SW_BREAK(1,0x2a28d8)) {}
    rt_00353274();
    rt_0008409c();
    if (0xf < l) {
        sk_ubp_count2();
        if (0 || 0 < l) {
            sk_ubp_ensure(l);
        }
    }
    do {
        if (0 < 0) {
            rt_00347d60();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        if (0 < 0) {
            rt_0035047c();
            rt_00348160(0x7a9);
            rt_003524c8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_00358014(0);
        l = 0;
        if (SW_BREAK(1,0x2a28b4)) {}
        l = l + 0 + 3;
        if (SW_BREAK(1,0x2a28b8)) {}
        if (0xf < l) {
            sk_ubp_count2();
            if (0 || 0 < l) {
                sk_ubp_ensure(l);
            }
        }
        if (0 != 0 && 0 == 0) {
            rt_003488bc(1);
            rt_00349a04();
            rt_003524c8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        t = rt_0008e388();
        sk_ubp_store(t.lo,t.hi,0);
        l = 0;
        sk_ubp_store(&l,3);
        if (0 < 0) {
            rt_0035047c();
            rt_00348160(0x7a8);
            rt_003524c8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        l = 0;
        if (0 < 0) {
            rt_00348548();
            rt_003524c8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_00084180();
        t = sk_swift_utf8_decode().lo ? (sk_u128_t){0,0} : t;
        if (-1 < t.lo) {
            t = rt_00084180();
            sk_ubp_store(t.lo,t.hi,0);
            goto commit;
        }
        if (0 == 0) {
commit:
            t = rt_00350618();
            rt_00356590(t.lo,t.hi,0);
            return;
        }
    } while (1);
}

/*--------------------------------------------------------------------*/
/* FUN_002a28f8 @ 0x002a28f8   (est. sk_ubp_alloc)
 * Ghidra: void FUN_002a28f8(long param_1,undefined8 param_2,undefined8 param_3)
 * Allocates an UnsafeMutableBufferPointer of param_1 elements (32-byte stride),
 * copying via sk_ubp_alloc_raw (002a4c88) into slot+0x20. Panics (noreturn) with
 * the "UnsafeMutableBufferPointer with negative count" fatal message on bad size.
 * Confidence: medium */
void sk_ubp_alloc(long a, void *b, void *c)
{
    long l;
    l = rt_002ad4fc(a,0x3000000000000000).lo;
    if (-1 < a) {
        sk_ubp_append();
        return;
    }
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a2978 @ 0x002a2978   (est. sk_ubp_alloc_run)
 * Ghidra: long FUN_002a2978(void)
 * Allocates an UnsafeMutableBufferPointer and fills it by running the caller's
 * generator closure (in_x6). Panics (noreturn) on a negative count.
 * Confidence: low */
long sk_ubp_alloc_run(void)
{
    long l, cap;
    word_t cnt;
    rt_0035ace8();
    l = rt_003585e8().lo;
    cap = rt_002ad4fc(l,0x3000000000000000).lo;
    if (-1 < l) {
        rt_00350a04();
        rt_0035359c();
        rt__indirect();
        if (0 == 0) {
            *(word_t *)(cap + 0x18) = 0 | 0x3000000000000000;
            *(unsigned char *)(cap + 0x20 + (0 & 0xffffffffffff)) = 0;
            rt_003a25d4();
        } else {
            rt_003a25d4();
            rt_0036b118(cap);
        }
        return cap;
    }
    rt_003a25d4();
    rt_00351088(1);
    rt_003487a4();
    rt_003524c8();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a2a40 @ 0x002a2a40   (est. sk_ubp_alloc_copy)
 * Ghidra: long FUN_002a2a40(long param_1,undefined8 param_2,undefined8 param_3)
 * Allocates an UnsafeMutableBufferPointer of param_1 elements and copies param_3
 * into the payload (FUN_003d3964). Panics on a negative count.
 * Confidence: medium */
long sk_ubp_alloc_copy(long a, void *b, void *c)
{
    long l;
    word_t u;
    l = rt_002ad4fc(a,0x3000000000000000).lo;
    if (-1 < a) {
        u = rt_003d3964(c,l + 0x20,a).lo;
        *(word_t *)(l + 0x18) = u | 0x3000000000000000;
        *(unsigned char *)(l + 0x20 + (u & 0xffffffffffff)) = 0;
        return l;
    }
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a2b04 @ 0x002a2b04   (est. sk_ubp_alloc_gen)
 * Ghidra: long FUN_002a2b04(long param_1,code *param_2)
 * Allocates an UnsafeMutableBufferPointer and fills it by invoking the generator
 * callback param_2. Panics (noreturn) on a negative count.
 * Confidence: medium */
long sk_ubp_alloc_gen(long a, sk_fnptr b)
{
    long l;
    word_t u;
    l = rt_002ad4fc(a,0x3000000000000000).lo;
    if (-1 < a) {
        rt_000dbd0c();
        u = (*b)().lo;
        if (0 == 0) {
            *(word_t *)(l + 0x18) = u | 0x3000000000000000;
            *(unsigned char *)(l + 0x20 + (u & 0xffffffffffff)) = 0;
        } else {
            rt_0036b118(l);
        }
        return l;
    }
    rt_00351088(1);
    rt_003487a4();
    rt_003524c8();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a2bb0 @ 0x002a2bb0   (est. sk_ubp_commit)
 * Ghidra: void FUN_002a2bb0(word_t param_1,uint param_2)
 * Commits the buffer's final count (param_1) and clears the trailing byte; if the
 * element count underflows it drains the free list via FUN_002ad480.
 * Confidence: medium */
void sk_ubp_commit(word_t a, uint b)
{
    word_t u;
    word_t *p;
    u = a | 0xc000000000000000;
    if ((b & 1) == 0) {
        u = a;
    }
    *(word_t *)(0 + 0x18) = u | 0x3000000000000000;
    rt_00359c84();
    *(unsigned char *)(0 + 0x20) = 0;
    if (-1 < *(long *)(0 + 0x10)) {
        return;
    }
    p = rt_002ad480().lo;
    rt_0036b118(*p);
}

/*--------------------------------------------------------------------*/
/* FUN_002a2c04 @ 0x002a2c04   (est. sk_utf16_encode)
 * Ghidra: void FUN_002a2c04(void)
 * UTF-16 encoder: iterates the source code units, combining surrogate pairs into
 * scalars and emitting them (FUN_00357468). Finalizes the buffer via 002a2698 and
 * commits through FUN_0006b6f4 / FUN_00354458. Panics on a surrogate-pair overflow.
 * Confidence: low */
void sk_utf16_encode(void)
{
    sk_u128_t t;
    word_t u, acc;
    long buf;
    rt_00355578();
    t = rt_0035098c();
    t = rt_0034fdf8(t.lo,t.hi & ((long)t.hi >> 0x3f ^ 0xffffffffffffffffU));
    buf = rt_001a0870(t.lo,t.hi,0).lo;
    rt_00354be0(0);
    do {
        if (0 == 0) {
            if (0 != 0) {
                rt_00353724();
                rt_00359244();
                rt_00356164(buf + 0x20);
                sk_swift_str_finalize(0,0,0);
                rt_0034bd90();
                rt_0036b118();
                t = rt_0006b6f4();
                rt_00354458(t.lo,t.hi,0);
                return;
            }
            u = *(unsigned short *)0;
            if ((u & 0xf800) != 0xd800) {
                rt_00357468();
            } else {
                acc = (word_t)((uint)acc & 0xffff0000 | (uint)u);
                u = 0x10;
                do {
                    if (0) break;
                    if (0x1f < (uint)u) {
                        rt_0035047c();
                        rt_003486b8(0xbe);
                        rt_0034975c();
                        /* WARNING: does not return */
                        rt_001afe4c();
                    }
                    acc = (word_t)((uint)*(unsigned short *)0 << ((uint)u & 0x1f) |
                                   (-0xffff << ((uint)u & 0x1f)) - 1U & (uint)acc);
                    u = (word_t)((uint)u + 0x10);
                } while ((uint)u < 0x10);
            }
            rt_00357468();
        } else {
            rt_00357468();
        }
    } while (1);
}

/*--------------------------------------------------------------------*/
/* FUN_002a2f60 @ 0x002a2f60   (est. sk_utf8_encode)
 * Ghidra: void FUN_002a2f60(void)
 * UTF-8 encoder: iterates the scalar source (array at auVar13._0_8_+0x20, count
 * at +0x10), encoding each scalar's UTF-8 bytes, and finalizes via 002a2698.
 * Confidence: low */
void sk_utf8_encode(void)
{
    sk_u128_t t;
    word_t n, u, cnt;
    long buf;
    rt_00353274();
    t = rt_0008e518();
    cnt = *(long *)(t.lo + 0x10);
    buf = rt_001a0870(rt_0034fdf8().lo,cnt,0).lo;
    for (n = 0; n != cnt; n++) {
        u = *(uint *)(t.lo + 0x20 + n * 4);
        if (u >> 0x10 < 0x11 && (u & 0xfffff800) != 0xd800) {
            if (u < 0x80) {
                u = u + 1;
            } else {
                u = (u & 0x3f) * 0x100;
                u = (u | u >> 6 & 0x3f) * 0x100;
                if (u >> 0x10 == 0) {
                    u = (u >> 0xc) + (u & 0xffff) * 0x100 + 0x8181e1;
                }
                u = (u >> 6) + (u & 0x3f) * 0x100 + 0x81c1;
                if (0x7ff < u) {
                    u = u;
                }
            }
            rt_0036b270();
            do {
                *(char *)(buf + 0) = (char)u + -1;
                u = u >> 8;
            } while (0xff < u);
        } else {
            rt_0034e9e8();
        }
    }
    rt_00353724();
    rt_00359244();
    rt_00356164(buf + 0x20);
    sk_swift_str_finalize(0,0,0);
    rt_0034bd90();
    rt_0036b118();
    rt_0006b6f4();
    rt_0008e500();
}

/*--------------------------------------------------------------------*/
/* FUN_002a3134 @ 0x002a3134   (est. sk_latin1_encode)
 * Ghidra: void FUN_002a3134(undefined8 param_1,undefined8 param_2,word_t param_3)
 * Latin-1 (8-bit) encoder: copies each byte, expanding high bytes to two UTF-8
 * bytes, and finalizes. Commits via FUN_0006b6f4 / FUN_00084234.
 * Confidence: low */
void sk_latin1_encode(void *a, void *b, word_t c)
{
    long buf;
    word_t n, u;
    char *p;
    rt_00084220();
    rt_0035316c();
    buf = rt_001a0870(rt_0034fdf8().lo,rt_0034fdf8().hi,0).lo;
    for (p = (char *)0; p != (char *)0; ) {
        u = *(word_t *)(buf + 0x10);
        if (*(char *)p < '\0') {
            rt_0034e9e8();
            p = p + 1;
            u = 0xbec0f0;
            do {
                *(char *)(buf + 0x20 + (u & 0xffff)) = (char)u + -1;
                u = u >> 8;
            } while (0xff < u);
        } else {
            rt_0036b270();
            *(char *)(buf + 0x20 + (u & 0xffff)) = *(char *)p;
            p = p + 1;
        }
    }
    rt_00353724();
    rt_00359244();
    rt_00356164(buf + 0x20);
    sk_swift_str_finalize(0,0,0);
    rt_0034bd90();
    rt_0036b118();
    rt_0006b6f4();
    rt_00084234();
}

/*--------------------------------------------------------------------*/
/* FUN_002a3268 @ 0x002a3268   (est. sk_ascii_encode)
 * Ghidra: void FUN_002a3268(void)
 * ASCII encoder: copies bytes, expanding high bytes to 2-byte UTF-8, and finalizes.
 * Confidence: low */
void sk_ascii_encode(void)
{
    sk_u128_t t;
    word_t n, u;
    long buf;
    t = rt_0008e518();
    n = *(long *)(t.lo + 0x10);
    buf = rt_001a0870(rt_0034fdf8().lo,n,0).lo;
    for (u = 0; u != n; u++) {
        rt_0034e9e8();
    }
    rt_00353724();
    rt_00359244();
    rt_00356164(buf + 0x20);
    sk_swift_str_finalize(0,0,0);
    rt_0034bd90();
    rt_0036b118();
    rt_0006b6f4();
    rt_0008e500();
}

/*--------------------------------------------------------------------*/
/* FUN_002a339c @ 0x002a339c   (est. sk_utf16_encode2)
 * Ghidra: void FUN_002a339c(undefined8 param_1,undefined8 param_2,uint param_3)
 * UTF-16 encoder variant: combines surrogate pairs into scalars, emits their UTF-8
 * form, and finalizes with the 002a2698 path. Panics on a pair overflow.
 * Confidence: low */
void sk_utf16_encode2(void *a, void *b, uint c)
{
    sk_u128_t t;
    word_t u, acc;
    long buf;
    rt_0035638c();
    t = rt_00351a80();
    t = rt_0034fdf8(t.lo,t.hi & ((long)t.hi >> 0x3f ^ 0xffffffffffffffffU));
    buf = rt_001a0870(t.lo,t.hi,0).lo;
    rt_00354be0(0);
    do {
        if (0 == 0) {
            if (0 != 0) {
                rt_00353724();
                rt_00359244();
                rt_00356164(buf + 0x20);
                sk_swift_str_finalize(0,0,0);
                rt_0034bd90();
                rt_0036b118();
                rt_0006b6f4();
                rt_00356370();
                return;
            }
            u = *(unsigned short *)0;
            if ((u & 0xf800) != 0xd800) {
                rt_00357468();
            } else {
                acc = (word_t)((uint)acc & 0xffff0000 | (uint)u);
                u = 0x10;
                do {
                    if (0) break;
                    if (0x1f < (uint)u) {
                        rt_0035047c();
                        rt_003486b8(0xbe);
                        rt_0034975c();
                        /* WARNING: does not return */
                        rt_001afe4c();
                    }
                    acc = (word_t)((uint)*(unsigned short *)0 << ((uint)u & 0x1f) |
                                   (-0xffff << ((uint)u & 0x1f)) - 1U & (uint)acc);
                    u = (word_t)((uint)u + 0x10);
                } while ((uint)u < 0x10);
            }
            rt_00357468();
        } else {
            rt_00357468();
        }
    } while (1);
}

/*--------------------------------------------------------------------*/
/* FUN_002a376c @ 0x002a376c   (est. sk_utf8_encode3)
 * Ghidra: void FUN_002a376c(void)
 * Third UTF-8 encoder: decodes each scalar via the UTF-8 codec and emits its bytes;
 * finalizes through 002a2698 / FUN_0009461c / FUN_0008e500.
 * Confidence: low */
void sk_utf8_encode3(void)
{
    sk_u128_t t;
    word_t u;
    long buf;
    rt_0008e518();
    t = rt_003548d0();
    rt_00377824(t.lo,t.hi,0,&DAT_00612b58);
    rt_00348d64();
    rt_0007c1a4();
    (*DAT_00658c00)();
    rt_0034b0c4();
    rt_00350500();
    rt_0031e084();
    rt_0034ab20();
    rt_0007c1a4();
    (*DAT_00658c00)();
    rt_0034aee4();
    rt_00350720();
    rt_00352438();
    rt_00377824();
    rt_000a6f88();
    rt_0007c1a4();
    (*DAT_00658c00)();
    rt_00350428();
    rt_00355b1c();
    rt_003494e8();
    (*DAT_00658c00)(0);
    rt_000aa4ec();
    rt_0035196c();
    rt_00351ef8(0);
    rt_00349444();
    rt_003514a0();
    rt_00377824();
    rt_000a6f88();
    (*DAT_00658c00)(0);
    rt_00348a34();
    (*DAT_00658c00)();
    rt_0034b3d8();
    rt_000a6894(0);
    u = rt_00350804().lo;
    u = rt__indirect(u,0).lo;
    t = rt_0034fdf8(u,u & ((long)u >> 0x3f ^ 0xffffffffffffffffU));
    buf = rt_001a0870(t.lo,t.hi,0).lo;
    rt_0034bfb4(0);
    rt__indirect();
    rt_000a68c4(0);
    rt_00350b30();
    rt_0035190c();
    rt__indirect();
    t = rt_00350b3c();
    rt__indirect(t.lo,t.hi,0);
    rt_0035754c(0,0);
    rt_00358be4();
    rt_00377bec();
    rt_0031e0d4();
    rt_003548e8();
    rt_0034db08();
    rt__indirect();
    rt_0031e104(0);
    rt_00356774();
    rt_0034db78();
    rt_00377bec();
    do {
        rt__indirect(0,0,0,0,0);
        rt_00358e00();
        if (rt_00369584().lo == 0) break;
        if (rt_00369584().lo == 2) {
            rt_0035407c();
            rt__indirect(0,0);
            rt_00353154();
            rt__indirect(0,0);
            rt_00359244(0,0);
            sk_swift_str_finalize(0,0,0);
            rt_00350df4();
            rt_0036b118();
            rt_0009461c(0,0,0);
            rt_0008e500();
            return;
        }
        rt_0036b270();
        do {
            *(char *)(buf + 0) = (char)0xbec0f0 + -1;
            u = u >> 8;
        } while (0xff < u);
    } while (1);
    rt_00351360(0);
    rt__indirect();
    rt_00350410();
    rt_003488bc();
    rt_00349844();
    rt_00350a94();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a3d30 @ 0x002a3d30   (est. sk_ubp_build)
 * Ghidra: void FUN_002a3d30(undefined8 param_1,long param_2,undefined8 param_3,uint param_4)
 * Builds a buffer: for zero elements initializes via FUN_00354828 and runs the UTF-8
 * encoder, else retains the element (thunk) and frees.
 * Confidence: medium */
void sk_ubp_build(void *a, long b, void *c, uint d)
{
    if (b == 0) {
        rt_00354828(c,d & 1);
        sk_utf8_encode3();
        rt_00351a5c();
    }
    rt_0036b270(b);
    rt_00350af4();
}

/*--------------------------------------------------------------------*/
/* FUN_002a3d9c @ 0x002a3d9c   (est. sk_ubp_read)
 * Ghidra: void FUN_002a3d9c(void)
 * Reads the current buffer into the caller slot, normalizing via 002a20cc /
 * FUN_00019858.
 * Confidence: low */
void sk_ubp_read(void **a, void **b)
{
    long l, n;
    word_t u;
    l = rt_00359640().lo;
    n = 0;
    if (l != 0) {
        n = 0 - l;
    }
    rt_001e4cbc((int)l,n);
    rt_003535a8();
    u = sk_swift_ascii_valid((char *)0,0);
    if ((u & 1) == 0) {
        a[0] = (void *)rt_00019858().lo;
        a[1] = (void *)0;
    } else {
        rt_000e15d8();
        a[0] = (void *)sk_swift_str_copyin(0,0);
        a[1] = (void *)0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a3e10 @ 0x002a3e10   (est. sk_ubp_retain)
 * Ghidra: void FUN_002a3e10(undefined8 param_1,undefined8 param_2)
 * Retains the buffer via FUN_001eaec4; panics (noreturn) on failure.
 * Confidence: medium */
void sk_ubp_retain(void *a, void *b)
{
    rt_001eaec4(a,b,1);
    if (0 != 0) {
        return;
    }
    rt_003489dc(0x166);
    rt_0034a2f8();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a3e64 @ 0x002a3e64   (est. sk_ubp_move)
 * Ghidra: void FUN_002a3e64(undefined8 param_1,undefined8 param_2,word_t param_3,word_t param_4)
 * Moves/reparents a 16-byte buffer value, refcounting when the element count
 * matches.
 * Confidence: medium */
void sk_ubp_move(void *a, void *b, word_t c, word_t d)
{
    sk_u128_t t;
    word_t u;
    t = rt_00077888();
    u = c & 0xffffffffffff;
    if ((d & 0x2000000000000000) != 0) {
        u = d >> 0x38 & 0xf;
    }
    if ((t.lo >> 0x10 == 0) && (t.hi >> 0x10 == u)) {
        rt_0036b270();
        rt_0007c1c4();
        return;
    }
    rt_0035053c();
    rt_0001d540();
}

/*--------------------------------------------------------------------*/
/* FUN_002a3ed4 @ 0x002a3ed4   (est. sk_ubp_alloc_n)
 * Ghidra: void FUN_002a3ed4(long param_1)
 * Allocates param_1 elements; panics (noreturn) with the negative-count fatal.
 * Confidence: medium */
void sk_ubp_alloc_n(long a)
{
    rt_0036a804(a,0xffffffffffffffff);
    if (-1 < a) {
        return;
    }
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a3f54 @ 0x002a3f54   (est. sk_ubp_alloc_n8)
 * Ghidra: void FUN_002a3f54(long param_1)
 * Allocates param_1 elements of 8-byte stride; panics on a negative count.
 * Confidence: medium */
void sk_ubp_alloc_n8(long a)
{
    if ((word_t)(a + 0xf000000000000000U) >> 0x3d < 7) {
        SW_BREAK(1,0x2a3fa8);
    }
    rt_0036a804(a << 3,0xffffffffffffffff);
    if (-1 < a) {
        return;
    }
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a3ff0 @ 0x002a3ff0   (est. sk_ubp_copy)
 * Ghidra: void FUN_002a3ff0(undefined8 param_1)
 * Copies the buffer via FUN_002b8444 / FUN_001a26e0.
 * Confidence: medium */
void sk_ubp_copy(void *a)
{
    rt_001a26e0(rt_002b8444().lo,a);
}

/*--------------------------------------------------------------------*/
/* FUN_002a401c @ 0x002a401c   (est. sk_ubp_slice)
 * Ghidra: undefined1 [16] FUN_002a401c(long param_1,long param_2,long param_3)
 * Builds a 16-byte buffer slice spanning [param_1,param_2) with base param_3.
 * Panics (noreturn) with the "UnsafeMutableBufferPointer ... negative count"/"has
 * an invalid pointer" fatal messages on bad bounds.
 * Confidence: medium */
sk_u128_t sk_ubp_slice(long a, long b, long c)
{
    sk_u128_t out;
    long base, len;
    base = c + a;
    len = 0;
    if (c != 0) {
        len = base;
    }
    b = b - a;
    if (b < 0) {
        rt_001afe4c();
    }
    if (b == 0) {
        if (len == 0) {
            base = 0;
            len = 0;
            goto out;
        }
    } else if (len == 0) {
        rt_001afe4c();
    }
    len = len + b;
out:
    out.hi = len;
    out.lo = base;
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_002a4148 @ 0x002a4148   (est. sk_ubp_slice_call)
 * Ghidra: void FUN_002a4148(undefined8 param_1,long param_2,long param_3,code *param_4,undefined8 param_5,undefined8 param_6,undefined8 param_7)
 * Bounds-checks a slice [param_2,param_3) via FUN_0028e8c0 and calls param_4 with
 * the valid slice; panics (noreturn) with the "Invalid slice" fatal message.
 * Confidence: medium */
void sk_ubp_slice_call(void *a, long b, long c, sk_fnptr d, void *e, void *f, void *g)
{
    sk_u128_t t;
    long l;
    t = rt_0028e8c0(f,g,b,c,0x7a8,0x7a9);
    l = t.lo;
    if ((-1 < l) && (t.hi <= (word_t)c)) {
        b = 0;
        if (b != 0) {
            b = b + l;
        }
        rt_001e4cbc(b,t.hi - l);
        (*d)(a);
        return;
    }
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a421c @ 0x002a421c   (est. sk_ubp_transform)
 * Ghidra: void FUN_002a421c(undefined8 param_1,undefined8 param_2,word_t param_3,word_t param_4,undefined8 param_5)
 * Transform helper: normalizes the source buffer and runs the transform closure;
 * the UTF-16 path sets up a stack frame with FUN_003469d8 / FUN_00346774.
 * Confidence: low */
void sk_ubp_transform(void *a, void *b, word_t c, word_t d, void *e)
{
    sk_u128_t t;
    rt_00359640();
    if ((d >> 0x3d & 1) == 0) {
        rt_00355bdc();
        if ((c >> 0x3c & 1) == 0) {
            rt_00355968();
            t = rt_002a9ba8();
            if (t.lo == 0) {
                t.lo = 0;
                t.hi = 0;
            }
        } else {
            t.lo = rt_00357628().lo;
            t.hi = c & 0xffffffffffff;
        }
        rt_00353f88(t.lo,t.hi);
        rt__indirect();
    } else {
        rt_0035701c();
        (*DAT_00658c00)();
        rt_00355c94();
        rt_003519e8();
        rt_0034a210();
        rt_00002534();
        rt_00350bfc(0,rt_00346774);
        rt_003576bc();
        rt_00291d70();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a4340 @ 0x002a4340   (est. sk_ubp_with_buffer)
 * Ghidra: void FUN_002a4340(long param_1,long param_2,code *param_3)
 * Runs the closure param_3 over the buffer [param_1,param_1+param_2); panics
 * (noreturn) with the "UnsafeBufferPointer with negative count" fatal on bad size.
 * Confidence: medium */
void sk_ubp_with_buffer(long a, long b, sk_fnptr c)
{
    if (a == 0) {
        b = 0;
    } else if (b < 0) {
        /* WARNING: does not return */
        rt_001afe4c();
    }
    (*c)(a,b);
}

/*--------------------------------------------------------------------*/
/* FUN_002a43e0 @ 0x002a43e0   (est. sk_ubp_is_ascii)
 * Ghidra: bool FUN_002a43e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,code *param_4)
 * Tests whether the buffer is pure ASCII: checks the first byte class, else runs the
 * callback param_4 over the buffer and tests for a NUL terminator. Frees the buffer.
 * Confidence: medium */
bool sk_ubp_is_ascii(void *a, void *b, void *c, sk_fnptr d)
{
    bool r;
    long buf;
    char *p;
    word_t u;
    buf = rt_00268540().lo;
    u = (word_t)*(unsigned char *)(buf + 0x20);
    if (((u < 0x21) && ((0x100003e01U >> (u & 0x3f) & 1) != 0)) ||
       (p = (char *)(*d)((unsigned char *)(buf + 0x20),c), p == (char *)0x0)) {
        r = false;
    } else {
        r = *p == '\0';
    }
    rt_0036b118(buf);
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002a4468 @ 0x002a4468   (est. sk_ubp_destroy_a)
 * Ghidra: void FUN_002a4468(void)
 * Destroys a buffer: sets up a destroy closure (FUN_0031e2ac) over the buffer and
 * frees it.
 * Confidence: low */
void sk_ubp_destroy_a(void)
{
    word_t buf;
    rt_0034bb84();
    rt_00355968();
    buf = rt_00268540().lo;
    rt_0034a210();
    rt_00002534();
    rt_00359fb4(rt_0031e2ac,0,buf,0x677600);
    rt_001de8a8();
    rt_0036b118(buf);
}

/*--------------------------------------------------------------------*/
/* FUN_002a4528 @ 0x002a4528   (est. sk_ubp_count)
 * Ghidra: word_t FUN_002a4528(undefined8 param_1,undefined8 param_2,word_t param_3,word_t param_4)
 * Returns the buffer's element count (from the 16-byte value in param_3/param_4),
 * checking against the current position.
 * Confidence: low */
word_t sk_ubp_count(void *a, void *b, word_t c, word_t d)
{
    word_t u;
    if ((d >> 0x3c & 1) == 0) {
        rt_003518c4();
        if ((d >> 0x3d & 1) != 0) {
            u = d >> 0x38 & 0xf;
            return u;
        }
        if ((c >> 0x3c & 1) == 0) {
            u = rt_00357628().lo;
            return u;
        }
        u = c & 0xffffffffffff;
    } else {
        sk_ubp_fatal();
        rt_00355968();
        u = rt_002a9ba8().lo;
    }
    if (0 < (long)u) {
        rt_00358b90();
    } else {
        rt_00350968(0);
        rt_0019d40c();
    }
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_002a45bc @ 0x002a45bc   (est. sk_ubp_fatal)
 * Ghidra: void FUN_002a45bc(void)
 * Aborts with the fatal "Not contiguous UTF-16"/overlap message (noreturn).
 * Confidence: low */
void sk_ubp_fatal(void)
{
    rt_0034e208();
    rt_003593c0(0,0);
    rt_0006f768();
    /* WARNING: does not return */
    rt_001afa84();
}

/*--------------------------------------------------------------------*/
/* FUN_002a4614 @ 0x002a4614   (est. sk_ubp_advance)
 * Ghidra: word_t FUN_002a4614(void)
 * Advances the buffer index by one element, computing the new packed index word.
 * Panics (noreturn) on overflow past the end.
 * Confidence: low */
word_t sk_ubp_advance(void)
{
    word_t u, cur;
    long l;
    rt_0034b85c();
    rt_00357794();
    rt_0034a3b0(0);
    if (0) {
        rt_00350624();
        u = rt_0001da84().lo;
    }
    u = rt_0034a274().lo;
    if ((word_t)(0 << 2) < u >> 0xe) {
        rt_00348614(1);
        rt_0034987c();
        /* WARNING: does not return */
        rt_001afe4c();
    }
    if ((0 >> 0x3c & 1) != 0) {
        rt_0034b788();
        return rt_002af6e4().lo;
    }
    u = rt_0034fb74().lo;
    if (0 == 1) {
        if (!SW_BREAK(1,0x2a476c)) {
            return (0 + (u >> 0x10)) * 0x10000 | 0xd;
        }
    }
    if ((u & 0xc001) == 0) {
        rt_00350624();
        u = rt_001676cc().lo;
        u = rt_00357938(u & 0xfffffffffffffff3).lo;
    }
    if (u < 0x4000) {
        if (-1 < (long)0) {
            if (0 < 0x20) goto ascii_small;
            goto utf16_large;
        }
        u = 0x20;
    } else {
        if (-1 < (long)0) {
            if (0x3f < 0) goto utf16_large;
            goto ascii_small;
        }
        u = 0x40;
    }
    if (u <= -0) {
utf16_large:
        rt_00350624();
        l = rt_002af74c().lo;
        if (!SW_BREAK(1,0x2a4770)) {
            rt_00350624(l + 0);
            return rt_002af844().lo;
        }
    }
ascii_small:
    rt_0034b788();
    return rt_001b1d5c().lo | 4;
}

/*--------------------------------------------------------------------*/
/* FUN_002a4784 @ 0x002a4784   (est. sk_ubp_advance_check)
 * Ghidra: void FUN_002a4784(void)
 * Checks that advancing by one element stays in bounds; panics (noreturn) otherwise.
 * Confidence: low */
void sk_ubp_advance_check(void)
{
    word_t u;
    rt_0034b85c();
    rt_00357794();
    u = rt_0034a3b0(0).lo;
    if (0) {
        rt_00350624();
        u = rt_0001da84().lo;
    }
    if ((0 >> 0x3c & 1) != 0) {
        rt_0034b788();
        rt_001b1ff0();
        return;
    }
    if (SW_BREAK(1,0x2a4820)) {}
    if ((-1 < (long)(0 + (u >> 0x10))) && (rt_0034cbb0(), 0 <= 0)) {
        rt_00357850();
        return;
    }
    rt_00348244(1);
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a4830 @ 0x002a4830   (est. sk_ubp_validate)
 * Ghidra: void FUN_002a4830(word_t param_1)
 * Validates a string buffer pointer; panics (noreturn) on a nil buffer.
 * Confidence: medium */
void sk_ubp_validate(word_t a)
{
    long l;
    if ((a >> 0x3c & 1) == 0) {
        l = rt_002a9ba8().lo;
        if (l == 0) {
            rt_00348898(1);
            rt_0034a2f8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
    } else {
        rt_0035ab14();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a487c @ 0x002a487c   (est. sk_ubp_utf16_fatal)
 * Ghidra: void FUN_002a487c(void)
 * Aborts with the "Not contiguous UTF-16" fatal message (noreturn).
 * Confidence: low */
void sk_ubp_utf16_fatal(void)
{
    rt_0035ac70(s_Not_contiguous_UTF_16_005d0690);
    rt_003593c0(0,0);
    rt_0006f768();
    /* WARNING: does not return */
    rt_001afa84();
}

/*--------------------------------------------------------------------*/
/* FUN_002a4904 @ 0x002a4904   (est. sk_ubp_alloc_cstr)
 * Ghidra: undefined8 FUN_002a4904(word_t param_1)
 * Allocates a buffer for a NUL-terminated C string of length param_1, copying the
 * contents via FUN_001ded00. Panics (noreturn) on a negative count.
 * Confidence: medium */
word_t sk_ubp_alloc_cstr(word_t a)
{
    sk_u128_t t;
    long l, buf;
    word_t out, cnt;
    out = 0;
    if (a != 0) {
        l = rt_00115080().lo + 1;
        if (SW_BREAK(1,0x2a4990)) {}
        t = rt_001dd374(l);
        cnt = t.hi;
        out = t.lo;
        if (l < 0) {
            rt_00351088(1);
            rt_003487a4();
            rt_003524c8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        if (cnt != a || a + l <= cnt) {
            rt_00350624(cnt);
            rt_00117d14();
            cnt = t.hi;
        }
        t.hi = cnt;
        t.lo = out;
        rt_001ded00(&buf,l,&t,&cnt,&out);
    }
    return out;
}

/*--------------------------------------------------------------------*/
/* FUN_002a49a8 @ 0x002a49a8   (est. sk_ubp_abort)
 * Ghidra: void FUN_002a49a8(void)
 * Aborts (noreturn) with the abstract-method fatal.
 * Confidence: low */
void sk_ubp_abort(void)
{
    rt_0035646c();
    rt_0034883c();
    /* WARNING: does not return */
    rt_001afa84();
}

/*--------------------------------------------------------------------*/
/* FUN_002a49d4 @ 0x002a49d4   (est. sk_ubp_capacity)
 * Ghidra: undefined1 [16] FUN_002a49d4(word_t param_1,word_t param_2)
 * Returns the buffer's capacity: for an owned object buffer, (count-1); else via
 * FUN_00068e14.
 * Confidence: medium */
sk_u128_t sk_ubp_capacity(word_t a, word_t b)
{
    sk_u128_t out;
    if (((a & (b ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0) {
        out.lo = (*(word_t *)((b & 0xfffffffffffffff) + 0x10) & 0xffffffffffff) - 1;
        out.hi = 0;
        return out;
    }
    return rt_00068e14();
}

/*--------------------------------------------------------------------*/
/* FUN_002a49fc @ 0x002a49fc   (est. sk_ubp_endptr)
 * Ghidra: undefined1 [16] FUN_002a49fc(word_t param_1,word_t param_2)
 * Returns the buffer's end pointer (base + capacity) as a 16-byte pair.
 * Confidence: medium */
sk_u128_t sk_ubp_endptr(word_t a, word_t b)
{
    sk_u128_t out;
    if (((a & (b ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0) {
        out.hi = 0;
        out.lo = (*(word_t *)((b & 0xfffffffffffffff) + 0x10) & 0xffffffffffff) +
                 (~*(word_t *)((b & 0xfffffffffffffff) + 0x18) | 0xffff000000000000);
        return out;
    }
    return rt_00068e14();
}

/*--------------------------------------------------------------------*/
/* FUN_002a4a2c @ 0x002a4a2c   (est. sk_ubp_count2)
 * Ghidra: long FUN_002a4a2c(void)
 * Returns the owned buffer's element count (count-1), else via FUN_00068e14.
 * Confidence: medium */
long sk_ubp_count2(void)
{
    word_t obj;
    if (((0 & (0 ^ 0xffffffffffffffff)) >> 0x3d & 1) != 0) {
        obj = 0 & 0xfffffffffffffff;
        if (rt_003a261c(obj).lo != 0) {
            return (*(word_t *)(obj + 0x10) & 0xffffffffffff) - 1;
        }
    }
    return rt_00068e14().lo;
}

/*--------------------------------------------------------------------*/
/* FUN_002a4a7c @ 0x002a4a7c   (est. sk_ubp_owner) */
word_t sk_ubp_owner(void)
{
    word_t u;
    if (((0 & (0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0) {
        u = 0;
    } else {
        u = rt_003a261c(0 & 0xfffffffffffffff).lo;
    }
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_002a4a80 @ 0x002a4a80   (est. sk_ubp_owner2) */
word_t sk_ubp_owner2(void)
{
    word_t u;
    if (((0 & (0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0) {
        u = 0;
    } else {
        u = rt_003a261c(0 & 0xfffffffffffffff).lo;
    }
    return u;
}

/*--------------------------------------------------------------------*/
/* FUN_002a4ab4 @ 0x002a4ab4   (est. sk_ubp_ensure)
 * Ghidra: void FUN_002a4ab4(long param_1)
 * Ensures the buffer has capacity for param_1 elements, growing and relocating if
 * needed; commits the new base/count into the buffer words.
 * Confidence: low */
void sk_ubp_ensure(long a)
{
    long l, buf;
    word_t u, cap;
    rt_00351db4();
    if (0) {
        rt_003532b8();
        l = 0;
    } else {
        l = 0;
    }
    if (l <= a) {
        l = a;
    }
    u = 0;
    if ((u >> 0x3c & 1) != 0) {
        sk_ubp_destroy(a);
        return;
    }
    if ((u >> 0x3d & 1) == 0) {
        rt_003510b8();
        cap = rt_002a9ba8().lo;
    } else {
        cap = rt_00351fd0().lo;
    }
    buf = sk_ubp_alloc_raw(cap,0,l,0);
    u = *(word_t *)(buf + 0x18);
    rt_003a25d4(0);
    *(word_t *)0 = u;
    *(word_t *)(0 + 8) = buf;
}

/*--------------------------------------------------------------------*/
/* FUN_002a4b90 @ 0x002a4b90   (est. sk_ubp_alloc_raw)
 * Ghidra: long FUN_002a4b90(undefined8 param_1,undefined8 param_2,undefined8 param_3,uint param_4)
 * Raw buffer allocation of param_3 elements (owned flag from param_4), returning
 * the buffer handle and copying the initial bytes via FUN_0007c1c4.
 * Confidence: medium */
long sk_ubp_alloc_raw(void *a, void *b, void *c, uint d)
{
    long l;
    word_t u;
    sk_u128_t t;
    rt_003504d0();
    u = 0 | 0xc000000000000000;
    if ((d & 1) == 0) {
        u = 0;
    }
    t = rt_002ad4fc(c,u | 0x3000000000000000);
    l = t.lo;
    rt_0007c1c4(l,t.hi,l + 0x20);
    rt_0019d40c();
    return l;
}

/*--------------------------------------------------------------------*/
/* FUN_002a4be4 @ 0x002a4be4   (est. sk_ubp_destroy)
 * Ghidra: void FUN_002a4be4(undefined8 param_1)
 * Destroys an owned buffer, releasing its backing object and resetting the buffer
 * words.
 * Confidence: medium */
void sk_ubp_destroy(void *a)
{
    sk_u128_t t;
    t = rt_0006b2ec(a,a);
    if (t.lo < 0x10) {
        if (t.hi < 0) {
            rt_00351088(1);
            rt_003487a4();
            rt_003524c8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        sk_ubp_append();
    }
    rt_0029ac60(t.hi);
    rt_0006b674();
    rt_003a25d4(0);
    *(word_t *)0 = 0;
    *(word_t *)(0 + 8) = 0;
    rt_000651bc(0);
    if (t.lo == 0xf) {
        return;
    }
    /* WARNING: does not return */
    rt_0011d7e8();
}

/*--------------------------------------------------------------------*/
/* FUN_002a4c88 @ 0x002a4c88   (est. sk_ubp_append)
 * Ghidra: void FUN_002a4c88(void)
 * Appends one element to the buffer: computes the new size (old+1), grows via
 * sk_ubp_ensure (002a4ab4), copies the element, and stores the result. Panics
 * (noreturn) on overflow.
 * Confidence: low */
void sk_ubp_append(void)
{
    word_t u, cnt, n;
    long l;
    sk_u128_t t;
    rt_0035193c();
    rt_00353274();
    rt_00351a38();
    if (0) {
        u = 0;
        if (SW_BREAK(1,0x2a4f1c)) {}
    } else {
        rt_00350974(0,0);
        rt_00354404();
        rt_002ab8ac();
        rt_00356290();
        rt_00350974(0);
        u = rt_002a999c().lo;
    }
    cnt = 0;
    if ((0 >> 0x3c & 1) == 0) {
        n = 0 & 0xffffffffffff;
    } else {
        rt_00350a34();
        n = rt_002b24b8().lo;
    }
    n = n + u;
    if (SW_BREAK(1,0x2a4f18)) {}
    if (0) {
        rt_00350a34();
        sk_ubp_endptr(0,0);
        l = rt_00351db4().lo;
        if (0) {
            rt_00351088();
            goto fatal;
        }
        rt_00350a34();
        sk_ubp_init_short2(0,0);
        rt_003534e0();
        rt_00350974(0,0);
        rt_00354404();
        rt_002ab8ac();
        rt_00356290();
        rt_0036b270();
        rt_0034ba38(0);
        sk_ubp_move(0,0,0,0);
        rt_00353918();
        rt_003a25d4();
        rt_003504ac();
        sk_ubp_init_short2(0,0);
        rt_0006b674();
        rt_003a25d4(0);
        rt_00350738();
        rt_0034b89c();
        if (0) {
fatal:
            rt_00348b40();
            rt_0034a2f8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_0006b674();
        rt_003a25d4(0);
        *(word_t *)0 = 0;
        *(word_t *)(0 + 8) = 0;
        goto store;
    }
    rt_00351354();
    sk_ubp_endptr(0,0);
    l = rt_00351db4().lo;
    if (0) {
        u = n;
        if (0 || l < (long)u) goto grow;
    } else if (0 || l < (long)u) {
grow:
        rt_00351354();
        t = sk_ubp_capacity(0,0);
        u = 0;
        if ((t.lo & 0xff) != 1) {
            u = t.lo << 1;
        }
        if ((long)u <= (long)n) {
            u = n;
        }
        sk_ubp_ensure(u);
    }
    if (0) {
        rt_003507e0();
        rt_00351e3c();
        rt_00351774();
        sk_ubp_append_ci(0,0,0,0);
        return;
    }
    if ((0 >> 0x3d & 1) == 0) {
        rt_003507e0();
        rt_002a9ba8();
        rt_00351790();
        rt_003504c4();
        rt_003520dc();
        t = rt_0028e8c0();
        if ((-1 < t.lo) && (t.hi <= 0)) {
            rt_00348e48();
            t = rt_001e4cbc();
            rt_00351774(t.lo,t.hi,0,0);
            sk_ubp_finish();
            return;
        }
    } else {
        rt_003504c4(0,0,0);
        rt_003520dc();
        t = rt_0028e8c0();
        if ((-1 < t.lo) && (t.hi <= 0)) {
            rt_00348e48();
            t = rt_001e4cbc();
            sk_ubp_finish();
store:
            rt_00351774(0);
            return;
        }
    }
    rt_003481fc();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a4c98 @ 0x002a4c98   (est. sk_ubp_append2)
 * Ghidra: void FUN_002a4c98(void)
 * Second append variant: identical growth/size logic to sk_ubp_append (002a4c88)
 * but takes the incoming element words from the caller context. Commits via
 * sk_ubp_finish (002a507c).
 * Confidence: low */
void sk_ubp_append2(void)
{
    word_t u, cnt, n;
    long l;
    sk_u128_t t;
    rt_0035193c();
    rt_00353274();
    rt_00351a38();
    if (0) {
        u = 0;
        if (SW_BREAK(1,0x2a4f1c)) {}
    } else {
        rt_00350974(0,0);
        rt_00354404();
        rt_002ab8ac();
        rt_00356290();
        rt_00350974(0);
        u = rt_002a999c().lo;
    }
    cnt = 0;
    if ((0 >> 0x3c & 1) == 0) {
        n = 0 & 0xffffffffffff;
    } else {
        rt_00350a34();
        n = rt_002b24b8().lo;
    }
    n = n + u;
    if (SW_BREAK(1,0x2a4f18)) {}
    if (0) {
        rt_00350a34();
        sk_ubp_endptr(0,0);
        l = rt_00351db4().lo;
        if (0) {
            rt_00351088();
            goto fatal;
        }
        rt_00350a34();
        sk_ubp_init_short2(0,0);
        rt_003534e0();
        rt_00350974(0,0);
        rt_00354404();
        rt_002ab8ac();
        rt_00356290();
        rt_0036b270();
        rt_0034ba38(0);
        sk_ubp_move(0,0,0,0);
        rt_00353918();
        rt_003a25d4();
        rt_003504ac();
        sk_ubp_init_short2(0,0);
        rt_0006b674();
        rt_003a25d4(0);
        rt_00350738();
        rt_0034b89c();
        if (0) {
fatal:
            rt_00348b40();
            rt_0034a2f8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_0006b674();
        rt_003a25d4(0);
        *(word_t *)0 = 0;
        *(word_t *)(0 + 8) = 0;
        goto store;
    }
    rt_00351354();
    sk_ubp_endptr(0,0);
    l = rt_00351db4().lo;
    if (0) {
        n = n;
        if (0 || l < (long)u) goto grow;
    } else if (0 || l < (long)u) {
grow:
        rt_00351354();
        t = sk_ubp_capacity(0,0);
        n = 0;
        if ((t.lo & 0xff) != 1) {
            n = t.lo << 1;
        }
        if ((long)n <= (long)u) {
            n = u;
        }
        sk_ubp_ensure(n);
    }
    if (0) {
        rt_003507e0();
        rt_00351e3c();
        rt_00351774();
        sk_ubp_append_ci(0,0,0,0);
        return;
    }
    if ((0 >> 0x3d & 1) == 0) {
        rt_003507e0();
        rt_002a9ba8();
        rt_00351790();
        rt_003504c4();
        rt_003520dc();
        t = rt_0028e8c0();
        if ((-1 < t.lo) && (t.hi <= 0)) {
            rt_00348e48();
            t = rt_001e4cbc();
            rt_00351774(t.lo,t.hi,0,0);
            sk_ubp_finish();
            return;
        }
    } else {
        rt_003504c4(0,0,0);
        rt_003520dc();
        t = rt_0028e8c0();
        if ((-1 < t.lo) && (t.hi <= 0)) {
            rt_00348e48();
            t = rt_001e4cbc();
            sk_ubp_finish();
store:
            rt_00351774(0);
            return;
        }
    }
    rt_003481fc();
    /* WARNING: does not return */
    rt_001afe4c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a4f5c @ 0x002a4f5c   (est. sk_ubp_init_short)
 * Ghidra: void FUN_002a4f5c(void)
 * Initializes a short (inline) buffer from the current string value: normalizes the
 * buffer and stores the UTF-8 scalar. Panics on an oversized (>15) count.
 * Confidence: low */
void sk_ubp_init_short(void)
{
    sk_u128_t t;
    word_t u, w;
    rt_0006b2ec();
    t = sk_ubp_fatal().lo ? (sk_u128_t){0,0} : t;
    u = t.hi;
    if ((u >> 0x3d & 1) != 0) {
        return;
    }
    if ((u >> 0x3c & 1) == 0) {
        if ((t.lo >> 0x3c & 1) != 0) {
            t.lo = t.lo & 0xffffffffffff;
            t.hi = (u & 0xfffffffffffffff) + 0x20;
            goto norm;
        }
    } else {
        sk_ubp_init_short();
    }
    t = rt_002a9ba8();
norm:
    u = t.hi;
    if (u == 0) {
        rt_0011e71c(t.lo);
    } else {
        if (0xf < u) {
            rt_00348898(1);
            rt_0034a2f8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        w = u;
        if (7 < u) {
            w = 8;
        }
        if (w - 1 <= u) {
            u = w - 1;
        }
        if (w == u) {
            rt_00348034();
            rt_003504b8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_00356134(0);
        do {
            u = rt_00356128().lo;
            t = rt_0035611c(0 | u);
            u = t.lo;
        } while (!0);
        w = 0;
        if (8 < t.hi) {
            do {
                u = rt_00358738().lo;
                w = 0;
            } while (!0);
        }
        rt_00354f64(w | u);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a4f80 @ 0x002a4f80   (est. sk_ubp_init_short2)
 * Ghidra: void FUN_002a4f80(word_t param_1,word_t param_2)
 * Short-buffer initializer taking an explicit 16-byte value; same logic as
 * sk_ubp_init_short.
 * Confidence: low */
void sk_ubp_init_short2(word_t a, word_t b)
{
    sk_u128_t t;
    word_t u, w;
    if ((b >> 0x3d & 1) != 0) {
        return;
    }
    if ((b >> 0x3c & 1) == 0) {
        if ((a >> 0x3c & 1) != 0) {
            t.lo = a & 0xffffffffffff;
            t.hi = (b & 0xfffffffffffffff) + 0x20;
            goto norm;
        }
    } else {
        sk_ubp_init_short();
    }
    t = rt_002a9ba8();
norm:
    u = t.hi;
    if (u == 0) {
        rt_0011e71c(t.lo);
    } else {
        if (0xf < u) {
            rt_00348898(1);
            rt_0034a2f8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        w = u;
        if (7 < u) {
            w = 8;
        }
        if (w - 1 <= u) {
            u = w - 1;
        }
        if (w == u) {
            rt_00348034();
            rt_003504b8();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_00356134(0);
        do {
            u = rt_00356128().lo;
            t = rt_0035611c(0 | u);
            u = t.lo;
        } while (!0);
        w = 0;
        if (8 < t.hi) {
            do {
                u = rt_00358738().lo;
                w = 0;
            } while (!0);
        }
        rt_00354f64(w | u);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a507c @ 0x002a507c   (est. sk_ubp_finish)
 * Ghidra: void FUN_002a507c(void)
 * Finalizes a buffer: stores the element and commits via FUN_00358d1c.
 * Confidence: medium */
void sk_ubp_finish(void)
{
    sk_ubp_store(*(void **)(0 + 8),0,0);
    rt_00358d1c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a50ac @ 0x002a50ac   (est. sk_ubp_append_ci)
 * Ghidra: void FUN_002a50ac(undefined8 param_1,undefined8 param_2,long param_3,long param_4)
 * Appends an element with the character-index [param_3,param_4), normalizing the
 * scalar and committing via sk_ubp_fill (002a5178).
 * Confidence: low */
void sk_ubp_append_ci(void *a, void *b, long c, long d)
{
    sk_u128_t t;
    word_t u;
    rt_0035316c();
    rt_003511cc(c << 0x10 | 1,d << 0x10 | 1);
    rt_00354404();
    rt_002ab8ac();
    t = rt_00356290();
    rt_00358990(*(void **)(0 + 8));
    u = 0;
    if ((0 & 0x2000000000000000) != 0) {
        u = (word_t)((0 >> 0x3e) & 1);
    }
    sk_ubp_fill(&t.lo,u);
    rt_00358d1c();
}

/*--------------------------------------------------------------------*/
/* FUN_002a5130 @ 0x002a5130   (est. sk_ubp_store)
 * Ghidra: void FUN_002a5130(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Stores an element into the buffer at the current offset and advances.
 * Confidence: low */
void sk_ubp_store(void *a, void *b, void *c)
{
    sk_u128_t t;
    t = rt_00359c84(*(void **)(0 + 0x18));
    rt_0019d40c(t.lo,t.hi,0 + 0x20);
    rt_002ad608(b,c);
}

/*--------------------------------------------------------------------*/
/* FUN_002a5178 @ 0x002a5178   (est. sk_ubp_fill)
 * Ghidra: void FUN_002a5178(undefined8 *param_1,uint param_2)
 * Fills the buffer with scalars from the descriptor at param_1: iterates elements,
 * bounds-checks the target (panic "String index is out of bounds"/"StringUTF8View"
 * / "UnsafeMutableBufferPointer" on error), and stores each. Ends via FUN_002ad608.
 * Confidence: low */
void sk_ubp_fill(void **a, uint b)
{
    word_t off, cap, u;
    unsigned char v;
    rt_00351db4();
    /* [INFERENCE] descriptor-walk; scalar at *a, count at a[1], flags at a[3] */
    off = 0;
    u = 0;
    do {
        v = 0;
        if ((u & 0xc) == 0) {
            u = rt_0001da84().lo;
        }
        if ((0 >> 0x3c & 1) != 0) {
            if (0 <= (word_t)u >> 0x10) {
                rt_001afe4c();
            }
            rt_002b141c(0,0,0);
        }
        if (0 < (long)off) {
            rt_001afe4c();
        }
        if (off <= u) {
            rt_001afe4c();
        }
        *(unsigned char *)(0 + 0x20 + 0 + off) = v;
        off = off + 1;
    } while (u != (word_t)u >> 0xe);
    rt_002ad608(off,b & 1);
}

/*--------------------------------------------------------------------*/
/* FUN_002a539c @ 0x002a539c   (est. sk_ubp_reset)
 * Ghidra: void FUN_002a539c(void)
 * Resets the buffer to empty, releasing the backing object if owned.
 * Confidence: medium */
void sk_ubp_reset(void)
{
    word_t u;
    u = 0;
    if (0) {
        rt_003a25d4(u);
        *(word_t *)0 = 0;
        *(word_t *)(0 + 8) = 0xe000000000000000;
    } else {
        rt_00068e14();
        sk_ubp_commit(0,0);
        rt_00358d1c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a5400 @ 0x002a5400   (est. sk_ubp_replace)
 * Ghidra: void FUN_002a5400(void)
 * Replaces the buffer contents: grows to the new element count, appends the
 * replacement elements via sk_ubp_append2 (002a4c98), and stores the result.
 * Confidence: low */
void sk_ubp_replace(void)
{
    word_t u, v;
    long l;
    sk_u128_t t;
    rt_00354744();
    t = rt_00355d9c();
    if (0) {
        rt_003524a4();
        sk_ubp_trim();
        *(word_t *)0 = *(word_t *)((0 & 0xfffffffffffffff) + 0x18);
        goto commit;
    }
    rt_0035896c();
    rt_00350560();
    t = sk_ubp_capacity(0,0);
    l = t.lo;
    if ((t.lo & 0xff) == 1) {
        l = 0;
    }
    if (0xf < l) {
        sk_ubp_count2();
        if (0 || 0 < l) {
            sk_ubp_ensure(l);
        }
    }
    rt_00350b48(0xf);
    rt_00354404();
    rt_002ab8ac();
    rt_0036b270(0);
    rt_00350560();
    rt_00351aec();
    sk_ubp_append2();
    rt_003a25d4(0);
    rt_0034c6b4();
    t = rt_001d97b4();
    sk_ubp_append_slice(0,0,t.lo >> 0x10,t.hi >> 0x10);
    rt_003a25d4(0);
    rt_003a25d4(0);
    *(word_t *)0 = 0;
    *(word_t *)(0 + 8) = 0;
commit:
    rt_003544c8(0);
}

/*--------------------------------------------------------------------*/
/* FUN_002a5544 @ 0x002a5544   (est. sk_ubp_trim)
 * Ghidra: void FUN_002a5544(void)
 * Trims the buffer down to its logical element count via FUN_003577b4 and commits.
 * Confidence: low */
void sk_ubp_trim(void)
{
    sk_u128_t t;
    t = rt_0008409c();
    rt_003577b4(0 + 0x20,t.lo,(*(word_t *)(0 + 0x18) & 0xffffffffffff) - t.hi);
    rt_0035ab20(0 + 0,0,0 + 0);
    sk_ubp_commit((0 - 0) + (*(word_t *)(0 + 0x18) & 0xffffffffffff),
                  *(word_t *)(0 + 0x18) >> 0x3f);
}

/*--------------------------------------------------------------------*/
/* FUN_002a55a4 @ 0x002a55a4   (est. sk_ubp_append_idx)
 * Ghidra: void FUN_002a55a4(word_t param_1,word_t param_2,undefined8 param_3,undefined8 param_4)
 * Appends the scalar range [param_1,param_2) (character counts) from the value in
 * param_3/param_4.
 * Confidence: low */
void sk_ubp_append_idx(word_t a, word_t b, void *c, void *d)
{
    sk_ubp_append_slice(c,d,a >> 0x10,b >> 0x10);
}

/*--------------------------------------------------------------------*/
/* FUN_002a55c0 @ 0x002a55c0   (est. sk_ubp_append_slice)
 * Ghidra: word_t FUN_002a55c0(undefined8 param_1,undefined8 param_2,word_t param_3,word_t param_4)
 * Appends the slice [param_3,param_4) (scalar counts) of the current buffer value,
 * growing via sk_ubp_insert (002a67a0/002a66f0 family), and stores the result.
 * Confidence: low */
word_t sk_ubp_append_slice(void *a, void *b, word_t c, word_t d)
{
    word_t u, v, n;
    long l;
    sk_u128_t t, r;
    u = 0;
    v = 0;
    if (0) {
        if ((d >> 0x3c & 1) != 0) {
            return sk_ubp_insert(a,b,c,d,&LAB_002a6794,0).lo;
        }
        if ((d >> 0x3d & 1) != 0) {
            r.lo = c;
            r.hi = d & 0xffffffffffffff;
            return sk_ubp_insert4(a,b,r,d >> 0x38 & 0xf,0).lo;
        }
        if ((c >> 0x3c & 1) == 0) {
            t = rt_002a9ba8(c,d);
        } else {
            t.lo = c & 0xffffffffffff;
            t.hi = (d & 0xfffffffffffffff) + 0x20;
        }
        return sk_ubp_insert4(a,b,t.lo,t.hi,0).lo;
    }
    r.lo = 0;
    r.hi = 0xe000000000000000;
    t = sk_ubp_capacity(u,v);
    l = t.lo;
    if (((t.lo & 0xff) != 1 && 0xf < l) &&
       (t = sk_ubp_count2(), (t.lo & 0xff) == 1 || t.lo < (word_t)l)) {
        sk_ubp_ensure(l);
    }
    t = rt_002ab8ac(0xf,a,u,v,0xd2,0x50);
    n = t.hi >> 0x10;
    rt_0036b270(v);
    sk_ubp_append_slice(u,v,t.lo >> 0x10,n);
    rt_003a25d4(v);
    u = r.hi;
    v = r.lo & 0xffffffffffff;
    if ((r.hi & 0x2000000000000000) != 0) {
        v = r.hi >> 0x38 & 0xf;
    }
    if ((v == 0) && (((r.lo & (r.hi ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        rt_0036b270(d);
        rt_003a25d4(u);
    } else {
        if ((r.hi >> 0x3d & 1) == 0) {
            n = c & 0xffffffffffff;
            if ((d & 0x2000000000000000) != 0) {
                n = d >> 0x38 & 0xf;
            }
        } else if ((d >> 0x3d & 1) == 0) {
            n = c & 0xffffffffffff;
        } else {
            r = rt_00291ee0(r.lo,r.hi,c,d);
            if (((uint)c & 0xff) != 1) {
                rt_003a25d4(u);
                goto store;
            }
            n = d >> 0x38 & 0xf;
        }
        sk_ubp_append_slice(c,d,0,n);
        r.lo = 0;
        r.hi = 0;
    }
store:
    n = v;
    r = rt_001d97b4(b,u,v);
    sk_ubp_append_slice(n,n,r.lo >> 0x10,r.hi >> 0x10);
    rt_003a25d4(v);
    rt_003a25d4(n);
    *(word_t *)0 = r.lo;
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_002a58b8 @ 0x002a58b8   (est. sk_ubp_append_slice2)
 * Ghidra: word_t FUN_002a58b8(undefined8 param_1,undefined8 param_2,word_t param_3,word_t param_4,word_t param_5,word_t param_6)
 * Appends the explicit slice [param_3,param_4) of the value in param_5/param_6,
 * validating the range via FUN_0028e8c0 (panic "Invalid slice" on error) and
 * delegating to sk_ubp_insert (002a66f0).
 * Confidence: low */
word_t sk_ubp_append_slice2(void *a, void *b, word_t c, word_t d, word_t e, word_t f)
{
    word_t u, v;
    long l;
    sk_u128_t t, r;
    u = 0;
    v = 0;
    if (0) {
        t.lo = 0;
        t.hi = 0xe000000000000000;
        r = sk_ubp_capacity(u,v);
        l = r.lo;
        if (((r.lo & 0xff) != 1 && 0xf < l) &&
           (r = sk_ubp_count2(), (r.lo & 0xff) == 1 || r.lo < (word_t)l)) {
            sk_ubp_ensure(l);
        }
        r = rt_002ab8ac(0xf,a,u,v,0xd2,0x50);
        rt_0036b270(v);
        sk_ubp_append_slice(u,v,r.lo >> 0x10,r.hi >> 0x10);
        rt_003a25d4(v);
        v = t.lo & 0xffffffffffff;
        if ((t.hi & 0x2000000000000000) != 0) {
            v = t.hi >> 0x38 & 0xf;
        }
        d = d >> 0x10;
        sk_ubp_append_slice(e,f,c >> 0x10,d);
        rt_001d97b4(b,u,v);
        sk_ubp_append_slice(0,d,0,0);
        rt_003a25d4(v);
        rt_003a25d4(d);
        *(word_t *)0 = t.lo;
        *(word_t *)(0 + 8) = t.hi;
    } else {
        if ((f >> 0x3c & 1) == 0) {
            if ((f >> 0x3d & 1) == 0) {
                if ((e >> 0x3c & 1) == 0) {
                    t = rt_002a9ba8(e,f);
                } else {
                    t.lo = e & 0xffffffffffff;
                    t.hi = (f & 0xfffffffffffffff) + 0x20;
                }
                r = rt_0028e8c0(c >> 0x10,d >> 0x10,t.lo,t.hi,0x7a8,0x7a9);
                l = r.lo;
                if ((-1 < l) && (r.hi <= t.hi)) {
                    e = 0;
                    if (t.lo != 0) {
                        e = t.lo + l;
                    }
                    t = rt_001e4cbc(e,r.hi - l);
                    return sk_ubp_insert4(a,b,t.lo,t.hi,0).lo;
                }
            } else {
                v = f >> 0x38 & 0xf;
                r = rt_0028e8c0(c >> 0x10,d >> 0x10,&e,v,0x7a8,0x7a9);
                l = r.lo;
                if ((-1 < l) && (r.hi <= (word_t)v)) {
                    e = 0;
                    if (0 != 0) {
                        e = 0 + l;
                    }
                    t = rt_001e4cbc(e,r.hi - l);
                    return sk_ubp_insert4(a,b,t.lo,t.hi,0).lo;
                }
            }
            /* WARNING: does not return */
            rt_001afe4c();
        }
        u = c;
        v = d;
        r = rt_002a6ad8(a,b,&u);
    }
    return v;
}

/*--------------------------------------------------------------------*/
/* FUN_002a5bf0 @ 0x002a5bf0   (est. sk_ubp_append_many)
 * Ghidra: undefined8 FUN_002a5bf0(undefined8 param_1,undefined8 param_2,long param_3)
 * Appends many elements from the descriptor array at param_3 (element pairs at
 * param_3+0x28), refcounting each and merging via sk_ubp_append_slice; stores the
 * result. Returns 0.
 * Confidence: low */
word_t sk_ubp_append_many(void *a, void *b, long c)
{
    word_t u, v, n;
    long l;
    sk_u128_t t, r;
    u = 0;
    v = 0;
    if (0) {
        return sk_ubp_insert5(a,b,c,&LAB_002a6794,0).lo;
    }
    t.lo = 0;
    t.hi = 0xe000000000000000;
    r = sk_ubp_capacity(u,v);
    l = r.lo;
    if (((r.lo & 0xff) != 1 && 0xf < l) &&
       (r = sk_ubp_count2(), (r.lo & 0xff) == 1 || r.lo < (word_t)l)) {
        sk_ubp_ensure(l);
    }
    t = rt_002ab8ac(0xf,a,u,v,0xd2,0x50);
    n = t.hi >> 0x10;
    rt_0036b270(v);
    sk_ubp_append_slice(u,v,t.lo >> 0x10,n);
    rt_003a25d4(v);
    l = *(long *)(c + 0x10);
    if (l != 0) {
        u = c + 0x28;
        t.lo = 0;
        t.hi = 0xe000000000000000;
        do {
            v = *(word_t *)(u - 8);
            n = *(word_t *)*u;
            t.lo = n;
            t.hi = v;
            if (0) {
                rt_0036b270(n);
                rt_003a25d4(0);
            } else {
                if ((0 >> 0x3d & 1) == 0) {
                    rt_0036b270(n);
                    sk_ubp_append_slice(v,n,0,0);
                    rt_003a25d4(n);
                    t.lo = 0;
                    t.hi = 0;
                } else {
                    r = rt_00291ee0(0,0,v,n);
                    rt_003a25d4(0);
                    t.lo = 0;
                    t.hi = 0;
                }
            }
            u = u + 2;
            l = l - 1;
        } while (l != 0);
    }
    n = v;
    t = rt_001d97b4(b,u,v);
    sk_ubp_append_slice(n,n,t.lo >> 0x10,t.hi >> 0x10);
    rt_003a25d4(v);
    rt_003a25d4(n);
    *(word_t *)0 = t.lo;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002a5e9c @ 0x002a5e9c   (est. sk_ubp_append_pair)
 * Ghidra: undefined1 [16] FUN_002a5e9c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Appends a pair (surrogate/scalar) value from param_3/param_4, growing and merging
 * via sk_ubp_append_slice, and stores the result. Returns the accumulated pair.
 * Confidence: low */
sk_u128_t sk_ubp_append_pair(void *a, void *b, void *c, void *d)
{
    word_t u, v, n;
    long l;
    sk_u128_t t, r;
    u = 0;
    v = 0;
    if (0) {
        rt_0036b270(d);
        t = sk_ubp_insert6(a,b,c,d,&LAB_002a6794,0);
        rt_003a25d4(d);
        return t;
    }
    t = sk_ubp_capacity(u,v);
    l = t.lo;
    if (((t.lo & 0xff) != 1 && 0xf < l) &&
       (t = sk_ubp_count2(), (t.lo & 0xff) == 1 || t.lo < (word_t)l)) {
        sk_ubp_ensure(l);
    }
    t = rt_002ab8ac(0xf,a,u,v,0xd2,0x50);
    n = t.hi >> 0x10;
    rt_0036b270(v);
    sk_ubp_append_slice(u,v,t.lo >> 0x10,n);
    rt_003a25d4(v);
    sk_ubp_merge(0,0);
    t.lo = 0;
    t.hi = 0;
    r = rt_001d97b4(b,u,v);
    sk_ubp_append_slice(0,n,r.lo >> 0x10,r.hi >> 0x10);
    rt_003a25d4(v);
    rt_003a25d4(n);
    *(word_t *)0 = 0;
    *(word_t *)(0 + 8) = 0xe000000000000000;
    return t;
}

/*--------------------------------------------------------------------*/
/* FUN_002a6080 @ 0x002a6080   (est. sk_ubp_append_char)
 * Ghidra: undefined8 FUN_002a6080(undefined8 param_1,undefined8 param_2)
 * Appends a single character to the buffer and stores the result; returns 0.
 * Confidence: low */
word_t sk_ubp_append_char(void *a, void *b)
{
    word_t u, v, n;
    long l;
    sk_u128_t t, r;
    u = 0;
    v = 0;
    if (0) {
        return sk_ubp_insert7(a,b,&LAB_002a6794,0).lo;
    }
    t = sk_ubp_capacity(u,v);
    l = t.lo;
    if (((t.lo & 0xff) != 1 && 0xf < l) &&
       (t = sk_ubp_count2(), (t.lo & 0xff) == 1 || t.lo < (word_t)l)) {
        sk_ubp_ensure(l);
    }
    t = rt_002ab8ac(0xf,a,u,v,0xd2,0x50);
    n = t.hi >> 0x10;
    rt_0036b270(v);
    sk_ubp_append_slice(u,v,t.lo >> 0x10,n);
    rt_003a25d4(v);
    sk_ubp_merge(0,0);
    r = rt_001d97b4(b,u,v);
    sk_ubp_append_slice(0,n,r.lo >> 0x10,r.hi >> 0x10);
    rt_003a25d4(v);
    rt_003a25d4(n);
    *(word_t *)0 = 0;
    *(word_t *)(0 + 8) = 0xe000000000000000;
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002a6238 @ 0x002a6238   (est. sk_ubp_format)
 * Ghidra: void FUN_002a6238(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Formatted build: pushes the context, and either appends the literal elements
 * (via sk_ubp_append_slice) or runs the object-formatting closures (FUN_00376820
 * with the format strings), committing via FUN_0008e500.
 * Confidence: low */
void sk_ubp_format(void *a, void *b, void *c, void *d, void *e)
{
    sk_u128_t t;
    word_t u, v;
    long l;
    rt_0008e518();
    rt_0035125c(e);
    rt_0034d3f4();
    rt_00319320();
    rt_000a6f88();
    rt_0007c1a4();
    (*DAT_00658c00)();
    t = rt_0034bdfc();
    rt_0035298c(t.lo,t.hi,0x675ad0);
    rt_00319338();
    rt_0034e2e4(0,0);
    rt_0031be18(0xff);
    rt_00353f68();
    rt_00319320();
    rt_000a6f88();
    rt_0007c1a4();
    (*DAT_00658c00)();
    rt_0034cff4();
    rt_0034998c();
    (*DAT_00658c00)(0);
    rt_00348a34();
    (*DAT_00658c00)();
    rt_0034ba68();
    u = 0;
    v = 0;
    if (0) {
        rt_000a6e14();
        sk_ubp_capacity(0,0);
        l = rt_00351db4().lo;
        if (0) {
            sk_ubp_count2();
            if (0 || 0 < l) {
                sk_ubp_ensure(l);
            }
        }
        rt_00352ea8(0xf,u);
        rt_00354404();
        rt_002ab8ac();
        rt_0036b270(v);
        rt_0034d788(u);
        sk_ubp_append_slice(0,0,0,0);
        rt_003a25d4(v);
        rt_00358014(0);
        rt_000bd3a4(c);
        rt_002a74f8();
        rt_00358014(0);
        rt_003515d8(0);
        t = rt_001d97b4();
        sk_ubp_append_slice(0,0,t.lo >> 0x10,t.hi >> 0x10);
        rt_003a25d4(v);
        rt_003a25d4(0);
        *(word_t *)0 = 0;
        *(word_t *)(0 + 8) = 0xe000000000000000;
        goto commit;
    }
    rt_00350ed0();
    rt__indirect();
    rt_00353d64();
    rt_003511c0(0);
    if (rt_00365b6c().lo == 0) {
        rt_00350ed0();
        rt__indirect();
        rt_0035484c();
        rt_003516f0(0);
        if ((rt_00365b6c().lo & 1) == 0) goto obj_fmt;
        if (0) goto obj_fmt;
        if ((0 >> 0x3d & 1) == 0) {
            rt_002a9ba8(0,0);
            rt_00351790();
        }
        rt_0009461c();
        rt_003520dc();
        t = rt_0028e8c0();
        if ((t.lo < 0) || (0 < t.hi)) {
            rt_003481fc();
            /* WARNING: does not return */
            rt_001afe4c();
        }
        rt_00348e48();
        rt_001e4cbc();
        rt_00351790();
        goto commit;
    }
    if ((0 >> 0x3c & 1) != 0) {
obj_fmt:
        rt_003a25d4(0);
        rt_00200b38(d);
        rt_00216b88(&LAB_002a6794,0,0,0x675ad0,0x66cbe0,0x66e558);
        rt_00357964();
        rt_003504ac();
        rt__indirect();
        rt_0034a180();
        rt_00376820(0,0,0);
        rt_00376820(&DAT_004e9a4c,0,0);
        rt_0034e314();
        rt_00376820(0,0,0);
        rt_003511cc(u,v);
        sk_ubp_grow2();
        rt_00353118();
        rt_000b4390();
        rt__indirect();
        goto commit;
    }
    rt_003584a8();
    rt_0034a180();
    u = 0;
    v = 0;
    sk_ubp_append_slice(u,v,0,0);
    rt_003a25d4(0);
commit:
    t = rt_00084174();
    rt_0008e500(t.lo,t.hi,0);
}

/*--------------------------------------------------------------------*/
/* FUN_002a66f0 @ 0x002a66f0   (est. sk_ubp_grow)
 * Ghidra: void FUN_002a66f0(void)
 * Grows the buffer to accommodate the appended slice: computes the new size, grows
 * via sk_ubp_ensure, and commits through FUN_00084234.
 * Confidence: low */
void sk_ubp_grow(void)
{
    long l, n;
    sk_u128_t t;
    l = rt_00084220().lo >> 0x10 + 0;
    if (SW_BREAK(1,0x2a6790)) {}
    rt_00359af8(*(void **)(0 + 8));
    n = 0 - (0 >> 0x10);
    l = l + n;
    if (!SW_BREAK(1,0x2a6794)) {
        rt_00353274();
        if (0xf < l) {
            sk_ubp_count2();
            if (0 || 0 < l) {
                sk_ubp_ensure(l);
            }
        }
        rt_000dbd0c(*(void **)(0 + 8));
        rt_00351e3c();
        rt_002a88bc();
        rt_00358d1c();
        t = rt_003507bc();
        rt_00084234(t.lo,t.hi,0);
        return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a67a0 @ 0x002a67a0   (est. sk_ubp_insert)
 * Ghidra: undefined1 [16] FUN_002a67a0(word_t param_1,word_t param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6)
 * Inserts the substring (param_3..param_6) at the scalar offset param_1, growing the
 * buffer via sk_ubp_ensure and storing the result. Returns the 16-byte range.
 * Confidence: low */
sk_u128_t sk_ubp_insert(word_t a, word_t b, void *c, void *d, void *e, void *f)
{
    sk_u128_t t, r;
    long l, n;
    word_t u;
    t = rt_0021927c(c,d,e,f);
    u = rt_002527e8(c,d,e,f).lo;
    l = rt_0021a660(t.lo,t.hi,e,u,0,1,c,d,e,f).lo;
    l = l + (a >> 0x10);
    if (SW_BREAK(1,0x2a68fc)) {}
    n = (0 & 0xffffffffffff) - (b >> 0x10);
    n = l + n;
    if (!SW_BREAK(1,0x2a6900)) {
        if ((0xf < n) && (r = sk_ubp_count2(), (r.lo & 0xff) == 1 || r.lo < (word_t)n)) {
            sk_ubp_ensure(n);
        }
        rt_002a8954(a >> 0x10,b >> 0x10,c,d,e,f,l);
        *(word_t *)0 = *(word_t *)((0 & 0xfffffffffffffff) + 0x18);
        r.lo = a >> 0x10;
        r.hi = l;
        return r;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a6900 @ 0x002a6900   (est. sk_ubp_insert2)
 * Ghidra: undefined1 [16] FUN_002a6900(word_t param_1,word_t param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6)
 * Insert variant 2 (uses FUN_002509d8); same shape as sk_ubp_insert.
 * Confidence: low */
sk_u128_t sk_ubp_insert2(word_t a, word_t b, void *c, void *d, void *e, void *f)
{
    sk_u128_t r;
    long l, n;
    word_t u;
    l = rt_002509d8(c,d,e,f).lo;
    l = l + (a >> 0x10);
    if (SW_BREAK(1,0x2a6a14)) {}
    n = (0 & 0xffffffffffff) - (b >> 0x10);
    n = l + n;
    if (!SW_BREAK(1,0x2a6a18)) {
        if ((0xf < n) && (r = sk_ubp_count2(), (r.lo & 0xff) == 1 || r.lo < (word_t)n)) {
            sk_ubp_ensure(n);
        }
        rt_002a8a88(a >> 0x10,b >> 0x10,c,d,e,f,l);
        *(word_t *)0 = *(word_t *)((0 & 0xfffffffffffffff) + 0x18);
        r.lo = a >> 0x10;
        r.hi = l;
        return r;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a6a18 @ 0x002a6a18   (est. sk_ubp_insert3)
 * Ghidra: undefined1 [16] FUN_002a6a18(word_t param_1,word_t param_2,undefined8 param_3,undefined8 param_4)
 * Insert variant 3: computes the size and grows; stores the result.
 * Confidence: low */
sk_u128_t sk_ubp_insert3(word_t a, word_t b, void *c, void *d)
{
    sk_u128_t r;
    long l;
    word_t u;
    u = a >> 0x10;
    l = (0 & 0xffffffffffff) - (b >> 0x10);
    l = (a >> 0x10) + l;
    if ((0xf < l) && (r = sk_ubp_count2(), (r.lo & 0xff) == 1 || r.lo < (word_t)l)) {
        sk_ubp_ensure(l);
    }
    rt_002a8ca0(u,b >> 0x10,c,d,0);
    *(word_t *)0 = *(word_t *)((0 & 0xfffffffffffffff) + 0x18);
    r.lo = u;
    r.hi = u;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002a6ad8 @ 0x002a6ad8   (est. sk_ubp_insert4)
 * Ghidra: undefined1 [16] FUN_002a6ad8(word_t param_1,word_t param_2,undefined8 param_3)
 * Insert variant 4 (uses FUN_00219370/FUN_0021b1a4); same shape as sk_ubp_insert.
 * Confidence: low */
sk_u128_t sk_ubp_insert4(word_t a, word_t b, void *c)
{
    sk_u128_t r;
    long l, n;
    word_t u;
    rt_00219370();
    l = rt_0021b1a4().lo;
    l = l + (a >> 0x10);
    if (SW_BREAK(1,0x2a6be0)) {}
    n = (0 & 0xffffffffffff) - (b >> 0x10);
    n = l + n;
    if (!SW_BREAK(1,0x2a6be4)) {
        if ((0xf < n) && (r = sk_ubp_count2(), (r.lo & 0xff) == 1 || r.lo < (word_t)n)) {
            sk_ubp_ensure(n);
        }
        rt_002a8d04(a >> 0x10,b >> 0x10,c,l);
        *(word_t *)0 = *(word_t *)((0 & 0xfffffffffffffff) + 0x18);
        r.lo = a >> 0x10;
        r.hi = l;
        return r;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a6be4 @ 0x002a6be4   (est. sk_ubp_insert5)
 * Ghidra: undefined1 [16] FUN_002a6be4(word_t param_1,word_t param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5)
 * Insert variant 5 (uses FUN_0021947c/FUN_0021b91c); same shape.
 * Confidence: low */
sk_u128_t sk_ubp_insert5(word_t a, word_t b, void *c, void *d, void *e)
{
    sk_u128_t r;
    long l, n;
    word_t u;
    rt_0021947c(c,d,e);
    l = rt_0021b91c().lo;
    l = l + (a >> 0x10);
    if (SW_BREAK(1,0x2a6d04)) {}
    n = (0 & 0xffffffffffff) - (b >> 0x10);
    n = l + n;
    if (!SW_BREAK(1,0x2a6d08)) {
        if ((0xf < n) && (r = sk_ubp_count2(), (r.lo & 0xff) == 1 || r.lo < (word_t)n)) {
            sk_ubp_ensure(n);
        }
        rt_002a8e28(a >> 0x10,b >> 0x10,c,d,e,l);
        *(word_t *)0 = *(word_t *)((0 & 0xfffffffffffffff) + 0x18);
        r.lo = a >> 0x10;
        r.hi = l;
        return r;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a6d08 @ 0x002a6d08   (est. sk_ubp_insert6)
 * Ghidra: undefined1 [16] FUN_002a6d08(word_t param_1,word_t param_2,undefined8 param_3,undefined8 param_4,undefined8 param_5,undefined8 param_6)
 * Insert variant 6 (uses FUN_00219554/FUN_0021c41c); same shape.
 * Confidence: low */
sk_u128_t sk_ubp_insert6(word_t a, word_t b, void *c, void *d, void *e, void *f)
{
    sk_u128_t r;
    long l, n;
    word_t u;
    rt_00219554(c,d,e,f);
    l = rt_0021c41c().lo;
    l = l + (a >> 0x10);
    if (SW_BREAK(1,0x2a6e38)) {}
    n = (0 & 0xffffffffffff) - (b >> 0x10);
    n = l + n;
    if (!SW_BREAK(1,0x2a6e3c)) {
        if ((0xf < n) && (r = sk_ubp_count2(), (r.lo & 0xff) == 1 || r.lo < (word_t)n)) {
            sk_ubp_ensure(n);
        }
        rt_002a919c(a >> 0x10,b >> 0x10,c,d,e,f,l);
        *(word_t *)0 = *(word_t *)((0 & 0xfffffffffffffff) + 0x18);
        r.lo = a >> 0x10;
        r.hi = l;
        return r;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a6e3c @ 0x002a6e3c   (est. sk_ubp_insert7)
 * Ghidra: undefined1 [16] FUN_002a6e3c(word_t param_1,word_t param_2,undefined8 param_3,undefined8 param_4)
 * Insert variant 7 (single element); same shape as sk_ubp_insert3.
 * Confidence: low */
sk_u128_t sk_ubp_insert7(word_t a, word_t b, void *c, void *d)
{
    sk_u128_t r;
    long l;
    word_t u;
    u = a >> 0x10;
    l = (0 & 0xffffffffffff) - (b >> 0x10);
    l = (a >> 0x10) + l;
    if ((0xf < l) && (r = sk_ubp_count2(), (r.lo & 0xff) == 1 || r.lo < (word_t)l)) {
        sk_ubp_ensure(l);
    }
    rt_002a92b8(u,b >> 0x10,c,d,0);
    *(word_t *)0 = *(word_t *)((0 & 0xfffffffffffffff) + 0x18);
    r.lo = u;
    r.hi = u;
    return r;
}

/*--------------------------------------------------------------------*/
/* FUN_002a6efc @ 0x002a6efc   (est. sk_ubp_grow2)
 * Ghidra: void FUN_002a6efc(void)
 * Second growth helper (uses FUN_0034d090); computes the new size and commits via
 * FUN_0008e500.
 * Confidence: low */
void sk_ubp_grow2(void)
{
    sk_u128_t t;
    long l, n;
    rt_0008e518();
    t = rt_0034d090();
    rt_00027788(0);
    rt_0034e63c();
    l = rt__indirect().lo;
    l = l + (t.lo >> 0x10);
    if (SW_BREAK(1,0x2a6fc4)) {}
    rt_00359af8(*(void **)(0 + 8));
    n = 0 - (t.hi >> 0x10);
    l = l + n;
    if (!SW_BREAK(1,0x2a6fc8)) {
        if (0xf < l) {
            sk_ubp_count2();
            if (0 || 0 < l) {
                sk_ubp_ensure(l);
            }
        }
        rt_00350a04(*(void **)(0 + 8));
        rt_00351c58();
        rt_00356a20();
        rt_002a93b8();
        rt_00358d1c();
        t = rt_00100c38();
        rt_0008e500(t.lo,t.hi,0);
        return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002a70d8 @ 0x002a70d8   (est. sk_ubp_merge)
 * Ghidra: void FUN_002a70d8(word_t param_1,word_t param_2)
 * Merges a 16-byte buffer value (param_1/param_2) into the current buffer: for the
 * simple case it refcounts and stores directly; otherwise it merges the element
 * pairs via sk_ubp_append_slice and 002a4c98. Commits via FUN_0036b118/002a4c98.
 * Confidence: low */
void sk_ubp_merge(word_t a, word_t b)
{
    word_t u, v, n;
    sk_u128_t t;
    long l;
    if (rt_00002534(&DAT_006575f8,&DAT_004f1960).lo == 0x6753a0) {
        rt_002acbb8(a,b);
        return;
    }
    if (rt_00002534(&DAT_006575f8,&DAT_004f1960).lo == 0x675c68) {
        SW_BREAK(1,0x2a7268);
    }
    if (rt_00002534(0x652b30,&DAT_004c4010).lo != 0x6753a0) {
        u = *(word_t *)0;
        v = *(word_t *)(0 + 8);
        n = u & 0xffffffffffff;
        if ((v & 0x2000000000000000) != 0) {
            n = v >> 0x38 & 0xf;
        }
        if ((n == 0) && (((u & (v ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            rt_0036b270(b);
            rt_003a25d4(v);
            *(word_t *)0 = a;
            *(word_t *)(0 + 8) = b;
            return;
        }
        if ((v >> 0x3d & 1) == 0) {
            n = a & 0xffffffffffff;
            if ((b & 0x2000000000000000) != 0) {
                n = b >> 0x38 & 0xf;
            }
        } else if ((b >> 0x3d & 1) == 0) {
            n = a & 0xffffffffffff;
        } else {
            t = rt_00291ee0(u,v,a,b);
            if (((uint)a & 0xff) != 1) {
                rt_003a25d4(v);
                *(word_t *)0 = t.lo;
                return;
            }
            n = b >> 0x38 & 0xf;
        }
        rt_0036b270(b);
        sk_ubp_append_slice(a,b,0,n);
        rt_003a25d4(b);
        return;
    }
    l = *(long *)(a + 0x10);
    if (l != 0) {
        a = a + 0x28;
        do {
            u = *(word_t *)(a - 8);
            v = *(word_t *)*a;
            if ((0 & (0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0) {
                n = u & 0xffffffffffff;
                if ((v & 0x2000000000000000) != 0) {
                    n = v >> 0x38 & 0xf;
                }
                if ((n == 0) && (((0 & (0 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
                    rt_0036b270(v);
                    rt_003a25d4(0);
                    *(word_t *)0 = u;
                    *(word_t *)(0 + 8) = v;
                } else {
                    rt_0036b270(v);
                    sk_ubp_append_slice(u,v,0,n);
                    rt_003a25d4(v);
                }
            }
            a = a + 2;
            l = l - 1;
        } while (l != 0);
    }
}
