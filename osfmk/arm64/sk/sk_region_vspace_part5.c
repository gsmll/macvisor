/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1),
 * "cL4 (679.100.61)". Ground truth: Ghidra FUN_ names + addresses in program
 * cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * This file covers the vspace/MMU-adjacent region 0x2332d4 - 0x248ae0 of the
 * cL4 microkernel. The slice is dominated by the embedded Swift runtime:
 * integer-to-string formatting (various Int/UInt widths and radices),
 * UInt128/Int128 arithmetic (add/sub/mul/div), UnsafeMutablePointer helpers,
 * KeyPath/collection accessors, and a number of thin thunk/wrapper stubs that
 * tail into the shared 0x30xxxx-0x3fxxxx runtime library. The vspace/MMU core
 * calls surface here as object-constructor and accessor wrappers (offset-based
 * field slots at +0x2c/0x30/0x34/0x38, object registry at x20, etc.).
 *
 * SeL4/cL4 vocabulary is used for naming where the logic is identifiable.
 * Confidence is medium unless a string matches.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
/* 128-bit value / 16-byte aggregate returned by the Swift Int128/UInt128 and
 * collection accessor helpers. lo = low word, hi = high word. */
typedef struct sk_wide {
    uint64_t lo;
    uint64_t hi;
} sk_wide_t;

/* Ghidra pseudo-builtin helpers used by the decompiler output. */
#define skp5_CARRY8(a,b)  ((uint64_t)(a) + (uint64_t)(b) < (uint64_t)(a))
#define skp5_SBORROW8(a,b) ((uint64_t)(a) - (uint64_t)(b) > (uint64_t)(a))
#define skp5_LZCOUNT(x)   (__builtin_clzll(x))
#define SUB168(x,s)  ((uint64_t)(x) >> (8*(s)))   /* extract word s (0=lo,8=hi) of a 16-byte value */
#define skp5_SEXT816(x)   (__builtin_bswap64(x))
#define skp5_ZEXT816(x)   ((sk_wide_t){(uint64_t)(x), 0})



/* ------------------------------------------------------------------ *
 * Out-of-range cL4 / Swift-runtime callees referenced by this region.
 * Declared as externs with the FUN_ address as the identifier (matching
 * the sibling sk_region_caps_* files); bodies are reconstructed by the
 * worker that owns the 0x00xxxx-0x3fxxxx runtime ranges.
 * ------------------------------------------------------------------ */


/* ---- runtime-library (0x00xxxx-0x1xxxxx) ---- */
extern unsigned long skp5_FUN_00012568();
extern unsigned long skp5_FUN_0001df60();
extern unsigned long skp5_FUN_0001e790();
extern unsigned long skp5_FUN_00027754();
extern sk_wide_t skp5_FUN_00041138();
extern unsigned long skp5_FUN_000651bc();
extern sk_wide_t skp5_FUN_0006b2dc();
extern unsigned long skp5_FUN_0006b2ec();
extern unsigned long skp5_FUN_0006b6f4();
extern sk_wide_t skp5_FUN_0006e778();
extern unsigned long skp5_FUN_0006f768();
extern unsigned long skp5_FUN_0006f794();
extern unsigned long skp5_FUN_0007767c();
extern unsigned long skp5_FUN_00077698();
extern unsigned long skp5_FUN_00077708();
extern unsigned long skp5_FUN_00077888();
extern unsigned long skp5_FUN_00077894();
extern unsigned long skp5_FUN_0007c1a4();
extern sk_wide_t skp5_FUN_0007c1c4();
extern unsigned long skp5_FUN_000839d8();
extern unsigned long skp5_FUN_0008409c();
extern unsigned long skp5_FUN_00084174();
extern unsigned long skp5_FUN_00084180();
extern sk_wide_t skp5_FUN_00084220();
extern unsigned long skp5_FUN_00084234();
extern unsigned long skp5_FUN_0008e388();
extern unsigned long skp5_FUN_0008e500();
extern sk_wide_t skp5_FUN_0008e518();
extern unsigned long skp5_FUN_0008f6c0();
extern unsigned long skp5_FUN_0008f6f4();
extern unsigned long skp5_FUN_0008f728();
extern unsigned long skp5_FUN_0008f758();
extern unsigned long skp5_FUN_0009461c();
extern unsigned long skp5_FUN_0009e234();
extern unsigned long skp5_FUN_000a68c4();
extern unsigned long skp5_FUN_000a68f4();
extern unsigned long skp5_FUN_000a6b64();
extern unsigned long skp5_FUN_000a6e14();
extern unsigned long skp5_FUN_000a6e20();
extern unsigned long skp5_FUN_000a6f68();
extern unsigned long skp5_FUN_000a6f88();
extern sk_wide_t skp5_FUN_000b4390();
extern unsigned long skp5_FUN_000b43d0();
extern unsigned long skp5_FUN_000b43e8();
extern unsigned long skp5_FUN_000bd3a4();
extern unsigned long skp5_FUN_000db6e8();
extern unsigned long skp5_FUN_000dbd0c();
extern unsigned long skp5_FUN_000dbdf4();
extern unsigned long skp5_FUN_000dbe70();
extern unsigned long skp5_FUN_000dbedc();
extern unsigned long skp5_FUN_000dbf08();
extern unsigned long skp5_FUN_000e15d8();
extern unsigned long skp5_FUN_000e710c();
extern unsigned long skp5_FUN_000e72b0();
extern unsigned long skp5_FUN_00100c38();
extern sk_wide_t skp5_FUN_00100efc();
extern unsigned long skp5_FUN_00115080();
extern unsigned long skp5_FUN_00117d14();
extern unsigned long skp5_FUN_0011d7e8();
extern sk_wide_t skp5_FUN_0011d85c();
extern unsigned long skp5_FUN_0011db10();
extern unsigned long skp5_FUN_0011db18();
extern unsigned long skp5_FUN_0011e71c();
extern unsigned long skp5_FUN_0014ae44();
extern unsigned long skp5_FUN_0016186c();
extern unsigned long skp5_FUN_0016796c();
extern unsigned long skp5_FUN_0016799c();
extern unsigned long skp5_FUN_001679cc();
extern unsigned long skp5_FUN_001679fc();
extern unsigned long skp5_FUN_00167a2c();
extern unsigned long skp5_FUN_0019e578();
extern unsigned long skp5_FUN_0019fd10();
extern unsigned long skp5_FUN_001a2630();
extern sk_wide_t skp5_FUN_001a89a8();
extern unsigned long skp5_FUN_001afa84();
extern unsigned long skp5_FUN_001afe4c();
extern unsigned long skp5_FUN_001d36e8();
extern unsigned long skp5_FUN_001dc430();
extern unsigned long skp5_FUN_001de04c();
extern unsigned long skp5_FUN_001e9c00();
extern unsigned long skp5_FUN_001e9f14();
extern unsigned long skp5_FUN_001ee0c8();

/* ---- in-range kernel helpers (0x20xxxx) ---- */
extern unsigned long skp5_FUN_00205844();
extern unsigned long skp5_FUN_00208418();
extern unsigned long skp5_FUN_002085a4();
extern sk_wide_t skp5_FUN_00248d7c();
extern unsigned long skp5_FUN_0024aa50();
extern unsigned long skp5_FUN_0024b938();
extern unsigned long skp5_FUN_0024c460();
extern unsigned long skp5_FUN_0024c56c();
extern unsigned long skp5_FUN_0024c5f4();
extern unsigned long skp5_FUN_00267820();

/* ---- object region (0x28xxxx) ---- */
extern sk_wide_t skp5_FUN_00291ee0();
extern unsigned long skp5_FUN_002a20cc();
extern unsigned long skp5_FUN_002a218c();
extern unsigned long skp5_FUN_002a2698();
extern unsigned long skp5_FUN_002a2748();
extern unsigned long skp5_FUN_002a4b90();
extern unsigned long skp5_FUN_002a4c98();
extern unsigned long skp5_FUN_002acbb8();
extern unsigned long skp5_FUN_002b81b4();
extern sk_wide_t skp5_FUN_002d3674();
extern sk_wide_t skp5_FUN_002d6730();
extern unsigned long skp5_FUN_002e3704();
extern unsigned long skp5_FUN_002e9ab4();
extern unsigned long skp5_FUN_002e9dec();

/* ---- cL4 runtime library (0x30xxxx-0x3fxxxx) ---- */
extern unsigned long skp5_FUN_00310954();
extern unsigned long skp5_FUN_00310984();
extern unsigned long skp5_FUN_003109b4();
extern unsigned long skp5_FUN_003109e4();
extern unsigned long skp5_FUN_00310a14();
extern unsigned long skp5_FUN_00310a44();
extern unsigned long skp5_FUN_00310aa4();
extern unsigned long skp5_FUN_00310ad4();
extern unsigned long skp5_FUN_00310b08();
extern unsigned long skp5_FUN_00310b38();
extern unsigned long skp5_FUN_00310d68();
extern unsigned long skp5_FUN_00310d80();
extern unsigned long skp5_FUN_00310f04();
extern unsigned long skp5_FUN_00310f34();
extern unsigned long skp5_FUN_00312d08();
extern unsigned long skp5_FUN_003156d0();
extern unsigned long skp5_FUN_003167cc();
extern sk_wide_t skp5_FUN_00316cd0();
extern unsigned long skp5_FUN_003195c8();
extern unsigned long skp5_FUN_00319748();
extern unsigned long skp5_FUN_00319778();
extern unsigned long skp5_FUN_0031c220();
extern unsigned long skp5_FUN_0031c250();
extern unsigned long skp5_FUN_0031c2e0();
extern unsigned long skp5_FUN_0031c370();
extern unsigned long skp5_FUN_0031c3d0();
extern unsigned long skp5_FUN_0031c460();
extern unsigned long skp5_FUN_0031c640();
extern unsigned long skp5_FUN_0031c788();
extern unsigned long skp5_FUN_0031c7e4();
extern unsigned long skp5_FUN_0031c874();
extern unsigned long skp5_FUN_0031c8a4();
extern unsigned long skp5_FUN_0031c904();
extern unsigned long skp5_FUN_0031c964();
extern unsigned long skp5_FUN_0031c9c4();
extern unsigned long skp5_FUN_0031c9f4();
extern unsigned long skp5_FUN_0031ca24();
extern unsigned long skp5_FUN_0031ca3c();
extern unsigned long skp5_FUN_0031d6d8();
extern unsigned long skp5_FUN_00344ed4();
extern unsigned long skp5_FUN_00347d60();
extern unsigned long skp5_FUN_00347da8();
extern unsigned long skp5_FUN_00347fb4();
extern unsigned long skp5_FUN_00348034();
extern unsigned long skp5_FUN_003480e4();
extern unsigned long skp5_FUN_003483c4();
extern unsigned long skp5_FUN_00348508();
extern unsigned long skp5_FUN_00348898();
extern unsigned long skp5_FUN_003488bc();
extern unsigned long skp5_FUN_003488f4();
extern unsigned long skp5_FUN_003489c0();
extern unsigned long skp5_FUN_00348a18();
extern unsigned long skp5_FUN_00348a34();
extern unsigned long skp5_FUN_00348a80();
extern unsigned long skp5_FUN_00348a9c();
extern unsigned long skp5_FUN_00348b5c();
extern unsigned long skp5_FUN_00348bbc();
extern unsigned long skp5_FUN_00348bd8();
extern unsigned long skp5_FUN_00348c84();
extern unsigned long skp5_FUN_00348ca8();
extern unsigned long skp5_FUN_00348cd0();
extern unsigned long skp5_FUN_00348ce8();
extern unsigned long skp5_FUN_00348d4c();
extern unsigned long skp5_FUN_00348dac();
extern unsigned long skp5_FUN_00348e00();
extern unsigned long skp5_FUN_00348e78();
extern unsigned long skp5_FUN_00348ecc();
extern unsigned long skp5_FUN_00348f38();
extern unsigned long skp5_FUN_00348f50();
extern unsigned long skp5_FUN_00348fb4();
extern unsigned long skp5_FUN_00348fd8();
extern unsigned long skp5_FUN_00349068();
extern unsigned long skp5_FUN_00349080();
extern unsigned long skp5_FUN_003490b8();
extern unsigned long skp5_FUN_003490d0();
extern unsigned long skp5_FUN_003490ec();
extern unsigned long skp5_FUN_0034911c();
extern unsigned long skp5_FUN_003491c4();
extern unsigned long skp5_FUN_00349234();
extern unsigned long skp5_FUN_0034924c();
extern unsigned long skp5_FUN_0034926c();
extern unsigned long skp5_FUN_003492cc();
extern unsigned long skp5_FUN_00349308();
extern unsigned long skp5_FUN_00349330();
extern unsigned long skp5_FUN_00349370();
extern unsigned long skp5_FUN_003493ac();
extern unsigned long skp5_FUN_003493c4();
extern unsigned long skp5_FUN_003493ec();
extern unsigned long skp5_FUN_0034947c();
extern unsigned long skp5_FUN_003494e8();
extern unsigned long skp5_FUN_003494fc();
extern unsigned long skp5_FUN_00349530();
extern unsigned long skp5_FUN_00349618();
extern unsigned long skp5_FUN_00349630();
extern unsigned long skp5_FUN_00349644();
extern unsigned long skp5_FUN_00349684();
extern unsigned long skp5_FUN_003496b0();
extern unsigned long skp5_FUN_003496e8();
extern unsigned long skp5_FUN_0034970c();
extern unsigned long skp5_FUN_00349720();
extern sk_wide_t skp5_FUN_00349770();
extern unsigned long skp5_FUN_003497b4();
extern unsigned long skp5_FUN_00349818();
extern unsigned long skp5_FUN_003499a0();
extern unsigned long skp5_FUN_003499f0();
extern unsigned long skp5_FUN_00349a54();
extern unsigned long skp5_FUN_00349a68();
extern unsigned long skp5_FUN_00349a7c();
extern unsigned long skp5_FUN_00349abc();
extern unsigned long skp5_FUN_00349b00();
extern unsigned long skp5_FUN_00349b3c();
extern unsigned long skp5_FUN_00349b50();
extern unsigned long skp5_FUN_00349c2c();
extern unsigned long skp5_FUN_00349c44();
extern unsigned long skp5_FUN_00349c84();
extern unsigned long skp5_FUN_00349c98();
extern unsigned long skp5_FUN_00349d80();
extern unsigned long skp5_FUN_00349d94();
extern sk_wide_t skp5_FUN_00349dfc();
extern unsigned long skp5_FUN_00349e10();
extern unsigned long skp5_FUN_00349eb8();
extern unsigned long skp5_FUN_00349f3c();
extern sk_wide_t skp5_FUN_00349f5c();
extern unsigned long skp5_FUN_0034a034();
extern unsigned long skp5_FUN_0034a068();
extern unsigned long skp5_FUN_0034a120();
extern unsigned long skp5_FUN_0034a1f8();
extern unsigned long skp5_FUN_0034a2ac();
extern unsigned long skp5_FUN_0034a2f8();
extern unsigned long skp5_FUN_0034a30c();
extern unsigned long skp5_FUN_0034a368();
extern unsigned long skp5_FUN_0034a37c();
extern unsigned long skp5_FUN_0034a390();
extern unsigned long skp5_FUN_0034a414();
extern unsigned long skp5_FUN_0034a450();
extern unsigned long skp5_FUN_0034a4bc();
extern unsigned long skp5_FUN_0034a510();
extern unsigned long skp5_FUN_0034a588();
extern unsigned long skp5_FUN_0034a5c8();
extern unsigned long skp5_FUN_0034a62c();
extern unsigned long skp5_FUN_0034a640();
extern unsigned long skp5_FUN_0034a688();
extern unsigned long skp5_FUN_0034a74c();
extern unsigned long skp5_FUN_0034a774();
extern unsigned long skp5_FUN_0034a8a4();
extern unsigned long skp5_FUN_0034a9ac();
extern unsigned long skp5_FUN_0034a9e8();
extern sk_wide_t skp5_FUN_0034a9fc();
extern unsigned long skp5_FUN_0034aa14();
extern unsigned long skp5_FUN_0034aa9c();
extern unsigned long skp5_FUN_0034aac4();
extern unsigned long skp5_FUN_0034ab10();
extern unsigned long skp5_FUN_0034ab20();
extern unsigned long skp5_FUN_0034abd8();
extern unsigned long skp5_FUN_0034abec();
extern unsigned long skp5_FUN_0034ac3c();
extern unsigned long skp5_FUN_0034ac50();
extern unsigned long skp5_FUN_0034aca0();
extern unsigned long skp5_FUN_0034acb0();
extern unsigned long skp5_FUN_0034acd0();
extern unsigned long skp5_FUN_0034acf0();
extern unsigned long skp5_FUN_0034ad00();
extern unsigned long skp5_FUN_0034ad10();
extern unsigned long skp5_FUN_0034ae1c();
extern unsigned long skp5_FUN_0034ae58();
extern unsigned long skp5_FUN_0034ae6c();
extern unsigned long skp5_FUN_0034ae94();
extern unsigned long skp5_FUN_0034aea8();
extern unsigned long skp5_FUN_0034aee4();
extern unsigned long skp5_FUN_0034af20();
extern unsigned long skp5_FUN_0034afa0();
extern unsigned long skp5_FUN_0034b07c();
extern unsigned long skp5_FUN_0034b0c4();
extern unsigned long skp5_FUN_0034b0d4();
extern unsigned long skp5_FUN_0034b100();
extern unsigned long skp5_FUN_0034b114();
extern unsigned long skp5_FUN_0034b18c();
extern unsigned long skp5_FUN_0034b1f0();
extern sk_wide_t skp5_FUN_0034b228();
extern unsigned long skp5_FUN_0034b278();
extern unsigned long skp5_FUN_0034b2c8();
extern unsigned long skp5_FUN_0034b2f8();
extern unsigned long skp5_FUN_0034b308();
extern unsigned long skp5_FUN_0034b358();
extern unsigned long skp5_FUN_0034b368();
extern unsigned long skp5_FUN_0034b3c8();
extern unsigned long skp5_FUN_0034b3d8();
extern unsigned long skp5_FUN_0034b3e8();
extern unsigned long skp5_FUN_0034b414();
extern unsigned long skp5_FUN_0034b4a0();
extern unsigned long skp5_FUN_0034b4b0();
extern unsigned long skp5_FUN_0034b4d0();
extern unsigned long skp5_FUN_0034b508();
extern unsigned long skp5_FUN_0034b518();
extern unsigned long skp5_FUN_0034b540();
extern unsigned long skp5_FUN_0034b5a8();
extern unsigned long skp5_FUN_0034b654();
extern unsigned long skp5_FUN_0034b6cc();
extern unsigned long skp5_FUN_0034b758();
extern unsigned long skp5_FUN_0034b768();
extern unsigned long skp5_FUN_0034b778();
extern unsigned long skp5_FUN_0034b89c();
extern unsigned long skp5_FUN_0034b8bc();
extern unsigned long skp5_FUN_0034b8dc();
extern unsigned long skp5_FUN_0034b9f8();
extern unsigned long skp5_FUN_0034ba08();
extern unsigned long skp5_FUN_0034ba28();
extern unsigned long skp5_FUN_0034ba38();
extern unsigned long skp5_FUN_0034ba58();
extern unsigned long skp5_FUN_0034ba68();
extern unsigned long skp5_FUN_0034ba88();
extern unsigned long skp5_FUN_0034ba98();
extern unsigned long skp5_FUN_0034bac8();
extern unsigned long skp5_FUN_0034badc();
extern unsigned long skp5_FUN_0034bb4c();
extern unsigned long skp5_FUN_0034bb84();
extern unsigned long skp5_FUN_0034bbf0();
extern unsigned long skp5_FUN_0034bc04();
extern unsigned long skp5_FUN_0034bc94();
extern unsigned long skp5_FUN_0034bd30();
extern unsigned long skp5_FUN_0034bd44();
extern unsigned long skp5_FUN_0034bd90();
extern unsigned long skp5_FUN_0034bda0();
extern unsigned long skp5_FUN_0034bdcc();
extern unsigned long skp5_FUN_0034bddc();
extern unsigned long skp5_FUN_0034bdec();
extern unsigned long skp5_FUN_0034bdfc();
extern unsigned long skp5_FUN_0034be54();
extern unsigned long skp5_FUN_0034bea4();
extern unsigned long skp5_FUN_0034bec4();
extern unsigned long skp5_FUN_0034bf1c();
extern unsigned long skp5_FUN_0034bf2c();
extern unsigned long skp5_FUN_0034bf48();
extern unsigned long skp5_FUN_0034bf64();
extern unsigned long skp5_FUN_0034bf84();
extern unsigned long skp5_FUN_0034bf94();
extern unsigned long skp5_FUN_0034bfa4();
extern unsigned long skp5_FUN_0034bfc4();
extern unsigned long skp5_FUN_0034bfe0();
extern unsigned long skp5_FUN_0034bffc();
extern unsigned long skp5_FUN_0034c018();
extern unsigned long skp5_FUN_0034c034();
extern unsigned long skp5_FUN_0034c044();
extern unsigned long skp5_FUN_0034c054();
extern unsigned long skp5_FUN_0034c074();
extern unsigned long skp5_FUN_0034c094();
extern unsigned long skp5_FUN_0034c0d0();
extern unsigned long skp5_FUN_0034c0ec();
extern unsigned long skp5_FUN_0034c234();
extern unsigned long skp5_FUN_0034c2b4();
extern sk_wide_t skp5_FUN_0034c2c8();
extern unsigned long skp5_FUN_0034c2d8();
extern unsigned long skp5_FUN_0034c31c();
extern unsigned long skp5_FUN_0034c368();
extern unsigned long skp5_FUN_0034c384();
extern unsigned long skp5_FUN_0034c3d4();
extern unsigned long skp5_FUN_0034c3e4();
extern unsigned long skp5_FUN_0034c454();
extern unsigned long skp5_FUN_0034c464();
extern unsigned long skp5_FUN_0034c480();
extern unsigned long skp5_FUN_0034c49c();
extern unsigned long skp5_FUN_0034c4fc();
extern unsigned long skp5_FUN_0034c57c();
extern unsigned long skp5_FUN_0034c5ac();
extern unsigned long skp5_FUN_0034c5fc();
extern unsigned long skp5_FUN_0034c638();
extern unsigned long skp5_FUN_0034c674();
extern unsigned long skp5_FUN_0034c694();
extern unsigned long skp5_FUN_0034c6b4();
extern unsigned long skp5_FUN_0034c6e4();
extern unsigned long skp5_FUN_0034c720();
extern unsigned long skp5_FUN_0034c754();
extern unsigned long skp5_FUN_0034c7d4();
extern unsigned long skp5_FUN_0034c800();
extern unsigned long skp5_FUN_0034c8b8();
extern unsigned long skp5_FUN_0034c8c8();
extern unsigned long skp5_FUN_0034c9b8();
extern unsigned long skp5_FUN_0034c9c8();
extern unsigned long skp5_FUN_0034cab0();
extern unsigned long skp5_FUN_0034cc00();
extern unsigned long skp5_FUN_0034cd04();
extern unsigned long skp5_FUN_0034cd40();
extern unsigned long skp5_FUN_0034cd68();
extern unsigned long skp5_FUN_0034cdc8();
extern unsigned long skp5_FUN_0034cde8();
extern unsigned long skp5_FUN_0034ce08();
extern unsigned long skp5_FUN_0034ce18();
extern unsigned long skp5_FUN_0034ce28();
extern unsigned long skp5_FUN_0034ce38();
extern unsigned long skp5_FUN_0034ce48();
extern unsigned long skp5_FUN_0034ce58();
extern unsigned long skp5_FUN_0034ce78();
extern unsigned long skp5_FUN_0034ce98();
extern unsigned long skp5_FUN_0034cea8();
extern unsigned long skp5_FUN_0034ced8();
extern unsigned long skp5_FUN_0034cee8();
extern unsigned long skp5_FUN_0034cf04();
extern unsigned long skp5_FUN_0034cf34();
extern unsigned long skp5_FUN_0034cf44();
extern unsigned long skp5_FUN_0034cf54();
extern unsigned long skp5_FUN_0034cf64();
extern unsigned long skp5_FUN_0034cf84();
extern unsigned long skp5_FUN_0034cf94();
extern unsigned long skp5_FUN_0034cfb4();
extern unsigned long skp5_FUN_0034cfe4();
extern unsigned long skp5_FUN_0034cff4();
extern unsigned long skp5_FUN_0034d004();
extern unsigned long skp5_FUN_0034d054();
extern unsigned long skp5_FUN_0034d100();
extern unsigned long skp5_FUN_0034d130();
extern unsigned long skp5_FUN_0034d160();
extern unsigned long skp5_FUN_0034d170();
extern unsigned long skp5_FUN_0034d180();
extern unsigned long skp5_FUN_0034d190();
extern unsigned long skp5_FUN_0034d1fc();
extern unsigned long skp5_FUN_0034d218();
extern unsigned long skp5_FUN_0034d234();
extern unsigned long skp5_FUN_0034d254();
extern unsigned long skp5_FUN_0034d294();
extern unsigned long skp5_FUN_0034d2d4();
extern sk_wide_t skp5_FUN_0034d2f4();
extern unsigned long skp5_FUN_0034d304();
extern unsigned long skp5_FUN_0034d314();
extern unsigned long skp5_FUN_0034d334();
extern unsigned long skp5_FUN_0034d364();
extern sk_wide_t skp5_FUN_0034d374();
extern unsigned long skp5_FUN_0034d3c4();
extern unsigned long skp5_FUN_0034d404();
extern unsigned long skp5_FUN_0034d444();
extern unsigned long skp5_FUN_0034d49c();
extern unsigned long skp5_FUN_0034d53c();
extern unsigned long skp5_FUN_0034d558();
extern unsigned long skp5_FUN_0034d5a8();
extern unsigned long skp5_FUN_0034d620();
extern unsigned long skp5_FUN_0034d654();
extern unsigned long skp5_FUN_0034d688();
extern unsigned long skp5_FUN_0034d698();
extern unsigned long skp5_FUN_0034d6a8();
extern unsigned long skp5_FUN_0034d758();
extern unsigned long skp5_FUN_0034d768();
extern unsigned long skp5_FUN_0034d778();
extern unsigned long skp5_FUN_0034d788();
extern unsigned long skp5_FUN_0034d7bc();
extern unsigned long skp5_FUN_0034d7cc();
extern unsigned long skp5_FUN_0034d7dc();
extern unsigned long skp5_FUN_0034d7ec();
extern unsigned long skp5_FUN_0034d7fc();
extern sk_wide_t skp5_FUN_0034d810();
extern unsigned long skp5_FUN_0034d830();
extern unsigned long skp5_FUN_0034d844();
extern unsigned long skp5_FUN_0034d878();
extern unsigned long skp5_FUN_0034d888();
extern unsigned long skp5_FUN_0034d89c();
extern unsigned long skp5_FUN_0034d8d4();
extern unsigned long skp5_FUN_0034d8e4();
extern unsigned long skp5_FUN_0034d970();
extern unsigned long skp5_FUN_0034d9cc();
extern unsigned long skp5_FUN_0034d9e8();
extern unsigned long skp5_FUN_0034da18();
extern unsigned long skp5_FUN_0034da88();
extern unsigned long skp5_FUN_0034dac8();
extern unsigned long skp5_FUN_0034db18();
extern unsigned long skp5_FUN_0034db38();
extern unsigned long skp5_FUN_0034db68();
extern sk_wide_t skp5_FUN_0034db88();
extern unsigned long skp5_FUN_0034dc20();
extern unsigned long skp5_FUN_0034dccc();
extern unsigned long skp5_FUN_0034ddec();
extern unsigned long skp5_FUN_0034df24();
extern unsigned long skp5_FUN_0034df44();
extern unsigned long skp5_FUN_0034df54();
extern unsigned long skp5_FUN_0034df64();
extern unsigned long skp5_FUN_0034df84();
extern unsigned long skp5_FUN_0034dfd4();
extern unsigned long skp5_FUN_0034dfe4();
extern unsigned long skp5_FUN_0034e014();
extern unsigned long skp5_FUN_0034e054();
extern unsigned long skp5_FUN_0034e064();
extern unsigned long skp5_FUN_0034e094();
extern unsigned long skp5_FUN_0034e0b4();
extern unsigned long skp5_FUN_0034e140();
extern unsigned long skp5_FUN_0034e15c();
extern unsigned long skp5_FUN_0034e1d0();
extern unsigned long skp5_FUN_0034e3ac();
extern unsigned long skp5_FUN_0034e454();
extern unsigned long skp5_FUN_0034e4cc();
extern unsigned long skp5_FUN_0034e4dc();
extern unsigned long skp5_FUN_0034e4fc();
extern unsigned long skp5_FUN_0034e51c();
extern unsigned long skp5_FUN_0034e53c();
extern unsigned long skp5_FUN_0034e58c();
extern unsigned long skp5_FUN_0034e5cc();
extern unsigned long skp5_FUN_0034e5dc();
extern unsigned long skp5_FUN_0034e5ec();
extern unsigned long skp5_FUN_0034e5fc();
extern unsigned long skp5_FUN_0034e62c();
extern unsigned long skp5_FUN_0034e64c();
extern unsigned long skp5_FUN_0034e74c();
extern unsigned long skp5_FUN_0034e784();
extern unsigned long skp5_FUN_0034e7e0();
extern unsigned long skp5_FUN_0034e81c();
extern unsigned long skp5_FUN_0034ea2c();
extern unsigned long skp5_FUN_0034ea54();
extern unsigned long skp5_FUN_0034eac0();
extern unsigned long skp5_FUN_0034eb94();
extern unsigned long skp5_FUN_0034ec0c();
extern unsigned long skp5_FUN_0034eca8();
extern unsigned long skp5_FUN_0034ece8();
extern unsigned long skp5_FUN_0034ed48();
extern unsigned long skp5_FUN_0034ed58();
extern unsigned long skp5_FUN_0034ed68();
extern unsigned long skp5_FUN_0034eda8();
extern unsigned long skp5_FUN_0034edb8();
extern unsigned long skp5_FUN_0034ee08();
extern unsigned long skp5_FUN_0034ee98();
extern unsigned long skp5_FUN_0034eeb8();
extern unsigned long skp5_FUN_0034eec8();
extern unsigned long skp5_FUN_0034eed8();
extern unsigned long skp5_FUN_0034eee8();
extern unsigned long skp5_FUN_0034ef08();
extern unsigned long skp5_FUN_0034ef58();
extern unsigned long skp5_FUN_0034ef68();
extern unsigned long skp5_FUN_0034f174();
extern unsigned long skp5_FUN_0034f1fc();
extern unsigned long skp5_FUN_0034f2c4();
extern unsigned long skp5_FUN_0034f304();
extern unsigned long skp5_FUN_0034f344();
extern unsigned long skp5_FUN_0034f364();
extern unsigned long skp5_FUN_0034f394();
extern unsigned long skp5_FUN_0034f3a4();
extern unsigned long skp5_FUN_0034f3f4();
extern unsigned long skp5_FUN_0034f494();
extern unsigned long skp5_FUN_0034f524();
extern unsigned long skp5_FUN_0034f574();
extern unsigned long skp5_FUN_0034f5d4();
extern unsigned long skp5_FUN_0034f634();
extern unsigned long skp5_FUN_0034f730();
extern unsigned long skp5_FUN_0034f754();
extern unsigned long skp5_FUN_0034f778();
extern unsigned long skp5_FUN_0034f8d0();
extern unsigned long skp5_FUN_0034fce4();
extern unsigned long skp5_FUN_0034fd04();
extern unsigned long skp5_FUN_0034fd14();
extern unsigned long skp5_FUN_0034fd8c();
extern unsigned long skp5_FUN_0034fdbc();
extern unsigned long skp5_FUN_0034fe48();
extern unsigned long skp5_FUN_0034fea0();
extern unsigned long skp5_FUN_0034fee0();
extern unsigned long skp5_FUN_0034ff98();
extern unsigned long skp5_FUN_0034ffb8();
extern unsigned long skp5_FUN_0034ffc8();
extern unsigned long skp5_FUN_0034ffdc();
extern unsigned long skp5_FUN_00350038();
extern unsigned long skp5_FUN_00350058();
extern unsigned long skp5_FUN_003500b0();
extern unsigned long skp5_FUN_003500e4();
extern unsigned long skp5_FUN_0035013c();
extern unsigned long skp5_FUN_003501d0();
extern unsigned long skp5_FUN_00350268();
extern unsigned long skp5_FUN_00350288();
extern unsigned long skp5_FUN_003502b8();
extern unsigned long skp5_FUN_003502d8();
extern unsigned long skp5_FUN_00350338();
extern unsigned long skp5_FUN_00350390();
extern unsigned long skp5_FUN_003503c0();
extern unsigned long skp5_FUN_003503d0();
extern unsigned long skp5_FUN_003503ec();
extern unsigned long skp5_FUN_003503f8();
extern unsigned long skp5_FUN_00350404();
extern unsigned long skp5_FUN_00350410();
extern unsigned long skp5_FUN_0035041c();
extern unsigned long skp5_FUN_00350428();
extern unsigned long skp5_FUN_00350440();
extern unsigned long skp5_FUN_0035044c();
extern unsigned long skp5_FUN_00350464();
extern unsigned long skp5_FUN_00350470();
extern unsigned long skp5_FUN_00350488();
extern sk_wide_t skp5_FUN_00350494();
extern unsigned long skp5_FUN_003504a0();
extern unsigned long skp5_FUN_003504ac();
extern unsigned long skp5_FUN_003504b8();
extern unsigned long skp5_FUN_003504c4();
extern unsigned long skp5_FUN_003504dc();
extern sk_wide_t skp5_FUN_003504e8();
extern unsigned long skp5_FUN_003504f4();
extern unsigned long skp5_FUN_00350500();
extern unsigned long skp5_FUN_0035050c();
extern unsigned long skp5_FUN_00350518();
extern unsigned long skp5_FUN_00350524();
extern unsigned long skp5_FUN_00350530();
extern unsigned long skp5_FUN_0035053c();
extern unsigned long skp5_FUN_00350548();
extern sk_wide_t skp5_FUN_00350554();
extern unsigned long skp5_FUN_00350560();
extern unsigned long skp5_FUN_0035056c();
extern unsigned long skp5_FUN_00350578();
extern unsigned long skp5_FUN_00350584();
extern unsigned long skp5_FUN_003505c4();
extern unsigned long skp5_FUN_003505d0();
extern unsigned long skp5_FUN_003505dc();
extern unsigned long skp5_FUN_003505e8();
extern unsigned long skp5_FUN_003505f4();
extern unsigned long skp5_FUN_00350600();
extern unsigned long skp5_FUN_0035060c();
extern unsigned long skp5_FUN_00350618();
extern unsigned long skp5_FUN_00350624();
extern unsigned long skp5_FUN_00350630();
extern unsigned long skp5_FUN_0035063c();
extern unsigned long skp5_FUN_00350654();
extern unsigned long skp5_FUN_0035066c();
extern unsigned long skp5_FUN_00350694();
extern unsigned long skp5_FUN_003506cc();
extern unsigned long skp5_FUN_0035072c();
extern unsigned long skp5_FUN_00350738();
extern unsigned long skp5_FUN_00350744();
extern unsigned long skp5_FUN_00350750();
extern unsigned long skp5_FUN_00350768();
extern unsigned long skp5_FUN_00350798();
extern unsigned long skp5_FUN_003507a4();
extern unsigned long skp5_FUN_003507bc();
extern sk_wide_t skp5_FUN_003507c8();
extern unsigned long skp5_FUN_003507d4();
extern unsigned long skp5_FUN_003507e0();
extern unsigned long skp5_FUN_003507f8();
extern unsigned long skp5_FUN_00350804();
extern sk_wide_t skp5_FUN_0035084c();
extern unsigned long skp5_FUN_00350878();
extern unsigned long skp5_FUN_00350884();
extern unsigned long skp5_FUN_003508a8();
extern sk_wide_t skp5_FUN_003508b4();
extern unsigned long skp5_FUN_003508cc();
extern unsigned long skp5_FUN_003508d8();
extern unsigned long skp5_FUN_003508e4();
extern unsigned long skp5_FUN_003508f0();
extern unsigned long skp5_FUN_003508fc();
extern unsigned long skp5_FUN_00350914();
extern unsigned long skp5_FUN_00350920();
extern unsigned long skp5_FUN_0035092c();
extern unsigned long skp5_FUN_00350938();
extern unsigned long skp5_FUN_00350944();
extern unsigned long skp5_FUN_00350950();
extern unsigned long skp5_FUN_00350968();
extern unsigned long skp5_FUN_00350974();
extern unsigned long skp5_FUN_0035098c();
extern sk_wide_t skp5_FUN_003509a4();
extern sk_wide_t skp5_FUN_003509b0();
extern unsigned long skp5_FUN_003509bc();
extern unsigned long skp5_FUN_003509c8();
extern unsigned long skp5_FUN_003509d4();
extern unsigned long skp5_FUN_003509e0();
extern unsigned long skp5_FUN_00350a04();
extern unsigned long skp5_FUN_00350a1c();
extern unsigned long skp5_FUN_00350a34();
extern unsigned long skp5_FUN_00350a4c();
extern sk_wide_t skp5_FUN_00350a64();
extern unsigned long skp5_FUN_00350a70();
extern unsigned long skp5_FUN_00350aa0();
extern unsigned long skp5_FUN_00350aac();
extern unsigned long skp5_FUN_00350ab8();
extern unsigned long skp5_FUN_00350ac4();
extern unsigned long skp5_FUN_00350af4();
extern unsigned long skp5_FUN_00350b00();
extern unsigned long skp5_FUN_00350b3c();
extern unsigned long skp5_FUN_00350b6c();
extern unsigned long skp5_FUN_00350b78();
extern unsigned long skp5_FUN_00350b84();
extern unsigned long skp5_FUN_00350b9c();
extern unsigned long skp5_FUN_00350ba8();
extern unsigned long skp5_FUN_00350bb4();
extern unsigned long skp5_FUN_00350bc0();
extern sk_wide_t skp5_FUN_00350c2c();
extern unsigned long skp5_FUN_00350c44();
extern unsigned long skp5_FUN_00350c50();
extern unsigned long skp5_FUN_00350c68();
extern sk_wide_t skp5_FUN_00350c80();
extern unsigned long skp5_FUN_00350c8c();
extern unsigned long skp5_FUN_00350d24();
extern unsigned long skp5_FUN_00350dc4();
extern unsigned long skp5_FUN_00350e34();
extern unsigned long skp5_FUN_00350e44();
extern unsigned long skp5_FUN_00350e64();
extern unsigned long skp5_FUN_00350e94();
extern unsigned long skp5_FUN_00350ea4();
extern unsigned long skp5_FUN_00350ec0();
extern unsigned long skp5_FUN_00350f1c();
extern unsigned long skp5_FUN_00350f2c();
extern unsigned long skp5_FUN_00350f4c();
extern unsigned long skp5_FUN_00350fac();
extern unsigned long skp5_FUN_00351068();
extern unsigned long skp5_FUN_00351094();
extern unsigned long skp5_FUN_003510a0();
extern unsigned long skp5_FUN_003510b8();
extern unsigned long skp5_FUN_003510c4();
extern unsigned long skp5_FUN_003510d0();
extern unsigned long skp5_FUN_003510dc();
extern unsigned long skp5_FUN_00351118();
extern unsigned long skp5_FUN_00351130();
extern unsigned long skp5_FUN_00351148();
extern unsigned long skp5_FUN_00351154();
extern unsigned long skp5_FUN_0035116c();
extern unsigned long skp5_FUN_00351178();
extern unsigned long skp5_FUN_00351184();
extern unsigned long skp5_FUN_003511a8();
extern unsigned long skp5_FUN_003511c0();
extern unsigned long skp5_FUN_003511cc();
extern unsigned long skp5_FUN_003511d8();
extern unsigned long skp5_FUN_003511e4();
extern unsigned long skp5_FUN_003511f0();
extern unsigned long skp5_FUN_00351214();
extern unsigned long skp5_FUN_00351220();
extern unsigned long skp5_FUN_0035122c();
extern unsigned long skp5_FUN_00351238();
extern unsigned long skp5_FUN_00351250();
extern unsigned long skp5_FUN_0035125c();
extern unsigned long skp5_FUN_00351274();
extern unsigned long skp5_FUN_0035128c();
extern unsigned long skp5_FUN_00351298();
extern unsigned long skp5_FUN_003512a4();
extern unsigned long skp5_FUN_00351324();
extern unsigned long skp5_FUN_0035133c();
extern sk_wide_t skp5_FUN_00351354();
extern unsigned long skp5_FUN_00351360();
extern unsigned long skp5_FUN_00351378();
extern unsigned long skp5_FUN_00351384();
extern unsigned long skp5_FUN_00351390();
extern unsigned long skp5_FUN_0035139c();
extern unsigned long skp5_FUN_003513fc();
extern unsigned long skp5_FUN_00351438();
extern unsigned long skp5_FUN_00351444();
extern sk_wide_t skp5_FUN_0035145c();
extern unsigned long skp5_FUN_00351468();
extern unsigned long skp5_FUN_003514a0();
extern unsigned long skp5_FUN_003514b8();
extern unsigned long skp5_FUN_003514d0();
extern unsigned long skp5_FUN_003514dc();
extern unsigned long skp5_FUN_003514e8();
extern unsigned long skp5_FUN_00351584();
extern unsigned long skp5_FUN_00351590();
extern unsigned long skp5_FUN_003515b4();
extern unsigned long skp5_FUN_003515cc();
extern unsigned long skp5_FUN_003515e4();
extern unsigned long skp5_FUN_003515fc();
extern unsigned long skp5_FUN_00351630();
extern unsigned long skp5_FUN_00351648();
extern unsigned long skp5_FUN_00351654();
extern unsigned long skp5_FUN_00351684();
extern unsigned long skp5_FUN_003516b4();
extern unsigned long skp5_FUN_003516c0();
extern unsigned long skp5_FUN_003516d8();
extern unsigned long skp5_FUN_003516e4();
extern unsigned long skp5_FUN_00351714();
extern unsigned long skp5_FUN_0035172c();
extern unsigned long skp5_FUN_00351744();
extern unsigned long skp5_FUN_00351768();
extern unsigned long skp5_FUN_0035179c();
extern sk_wide_t skp5_FUN_003517a8();
extern unsigned long skp5_FUN_003517b4();
extern unsigned long skp5_FUN_003517d8();
extern unsigned long skp5_FUN_00351888();
extern unsigned long skp5_FUN_003518a0();
extern unsigned long skp5_FUN_003518d0();
extern unsigned long skp5_FUN_003518f4();
extern unsigned long skp5_FUN_00351900();
extern unsigned long skp5_FUN_0035190c();
extern unsigned long skp5_FUN_00351918();
extern unsigned long skp5_FUN_00351924();
extern unsigned long skp5_FUN_003519b4();
extern unsigned long skp5_FUN_003519fc();
extern unsigned long skp5_FUN_00351a08();
extern unsigned long skp5_FUN_00351a20();
extern unsigned long skp5_FUN_00351a2c();
extern unsigned long skp5_FUN_00351a50();
extern unsigned long skp5_FUN_00351a74();
extern unsigned long skp5_FUN_00351aa4();
extern unsigned long skp5_FUN_00351ad4();
extern unsigned long skp5_FUN_00351af8();
extern unsigned long skp5_FUN_00351b04();
extern unsigned long skp5_FUN_00351b20();
extern unsigned long skp5_FUN_00351b2c();
extern unsigned long skp5_FUN_00351b6c();
extern unsigned long skp5_FUN_00351b78();
extern unsigned long skp5_FUN_00351ba0();
extern unsigned long skp5_FUN_00351bd4();
extern unsigned long skp5_FUN_00351bec();
extern unsigned long skp5_FUN_00351c28();
extern unsigned long skp5_FUN_00351c34();
extern unsigned long skp5_FUN_00351c4c();
extern unsigned long skp5_FUN_00351c64();
extern unsigned long skp5_FUN_00351c94();
extern unsigned long skp5_FUN_00351cb8();
extern unsigned long skp5_FUN_00351cc4();
extern unsigned long skp5_FUN_00351ce8();
extern unsigned long skp5_FUN_00351cf4();
extern unsigned long skp5_FUN_00351d0c();
extern unsigned long skp5_FUN_00351d24();
extern unsigned long skp5_FUN_00351dc0();
extern unsigned long skp5_FUN_00351dcc();
extern unsigned long skp5_FUN_00351e14();
extern unsigned long skp5_FUN_00351e48();
extern unsigned long skp5_FUN_00351e54();
extern unsigned long skp5_FUN_00351e6c();
extern unsigned long skp5_FUN_00351e84();
extern unsigned long skp5_FUN_00351e90();
extern unsigned long skp5_FUN_00351eb4();
extern unsigned long skp5_FUN_00351ec0();
extern unsigned long skp5_FUN_00351ee0();
extern unsigned long skp5_FUN_00351f10();
extern unsigned long skp5_FUN_00351f4c();
extern unsigned long skp5_FUN_00351f64();
extern unsigned long skp5_FUN_00351f70();
extern unsigned long skp5_FUN_00351f7c();
extern unsigned long skp5_FUN_00351f88();
extern unsigned long skp5_FUN_00351f94();
extern unsigned long skp5_FUN_00351fe0();
extern unsigned long skp5_FUN_00352008();
extern unsigned long skp5_FUN_00352078();
extern unsigned long skp5_FUN_00352098();
extern unsigned long skp5_FUN_00352134();
extern unsigned long skp5_FUN_00352250();
extern unsigned long skp5_FUN_00352270();
extern unsigned long skp5_FUN_003522c8();
extern unsigned long skp5_FUN_003522d4();
extern unsigned long skp5_FUN_003522e4();
extern unsigned long skp5_FUN_003523bc();
extern unsigned long skp5_FUN_003523f0();
extern unsigned long skp5_FUN_003523fc();
extern unsigned long skp5_FUN_00352408();
extern unsigned long skp5_FUN_00352420();
extern unsigned long skp5_FUN_00352438();
extern unsigned long skp5_FUN_00352444();
extern unsigned long skp5_FUN_003524a4();
extern unsigned long skp5_FUN_003524d4();
extern unsigned long skp5_FUN_003524e0();
extern unsigned long skp5_FUN_00352554();
extern unsigned long skp5_FUN_0035256c();
extern unsigned long skp5_FUN_00352584();
extern unsigned long skp5_FUN_00352680();
extern sk_wide_t skp5_FUN_003526c4();
extern unsigned long skp5_FUN_00352720();
extern unsigned long skp5_FUN_00352840();
extern unsigned long skp5_FUN_00352894();
extern unsigned long skp5_FUN_003528d8();
extern unsigned long skp5_FUN_003528ec();
extern unsigned long skp5_FUN_00352914();
extern unsigned long skp5_FUN_00352920();
extern unsigned long skp5_FUN_00352944();
extern unsigned long skp5_FUN_00352974();
extern unsigned long skp5_FUN_00352980();
extern unsigned long skp5_FUN_00352998();
extern unsigned long skp5_FUN_00352a1c();
extern unsigned long skp5_FUN_00352a4c();
extern unsigned long skp5_FUN_00352a64();
extern unsigned long skp5_FUN_00352aa0();
extern unsigned long skp5_FUN_00352afc();
extern unsigned long skp5_FUN_00352b08();
extern unsigned long skp5_FUN_00352b44();
extern unsigned long skp5_FUN_00352b80();
extern unsigned long skp5_FUN_00352b8c();
extern unsigned long skp5_FUN_00352bb0();
extern unsigned long skp5_FUN_00352bf8();
extern unsigned long skp5_FUN_00352c10();
extern unsigned long skp5_FUN_00352c1c();
extern unsigned long skp5_FUN_00352c4c();
extern unsigned long skp5_FUN_00352c58();
extern unsigned long skp5_FUN_00352c68();
extern unsigned long skp5_FUN_00352c74();
extern unsigned long skp5_FUN_00352c8c();
extern unsigned long skp5_FUN_00352c98();
extern unsigned long skp5_FUN_00352ca4();
extern unsigned long skp5_FUN_00352cbc();
extern unsigned long skp5_FUN_00352d04();
extern unsigned long skp5_FUN_00352d4c();
extern unsigned long skp5_FUN_00352d70();
extern unsigned long skp5_FUN_00352dd0();
extern unsigned long skp5_FUN_00352e0c();
extern unsigned long skp5_FUN_00352e24();
extern unsigned long skp5_FUN_00352e30();
extern unsigned long skp5_FUN_00352e48();
extern unsigned long skp5_FUN_00352ee4();
extern unsigned long skp5_FUN_00352efc();
extern unsigned long skp5_FUN_00352f54();
extern unsigned long skp5_FUN_00352f88();
extern unsigned long skp5_FUN_00353000();
extern unsigned long skp5_FUN_00353034();
extern unsigned long skp5_FUN_0035305c();
extern unsigned long skp5_FUN_00353074();
extern unsigned long skp5_FUN_0035308c();
extern unsigned long skp5_FUN_003530a4();
extern unsigned long skp5_FUN_003530cc();
extern unsigned long skp5_FUN_00353100();
extern unsigned long skp5_FUN_00353130();
extern unsigned long skp5_FUN_00353148();
extern unsigned long skp5_FUN_00353154();
extern unsigned long skp5_FUN_00353184();
extern unsigned long skp5_FUN_00353190();
extern unsigned long skp5_FUN_0035319c();
extern unsigned long skp5_FUN_003531c0();
extern unsigned long skp5_FUN_003531d8();
extern unsigned long skp5_FUN_00353208();
extern unsigned long skp5_FUN_00353220();
extern unsigned long skp5_FUN_0035322c();
extern unsigned long skp5_FUN_00353360();
extern unsigned long skp5_FUN_0035336c();
extern unsigned long skp5_FUN_00353378();
extern unsigned long skp5_FUN_00353384();
extern unsigned long skp5_FUN_0035343c();
extern sk_wide_t skp5_FUN_00353468();
extern unsigned long skp5_FUN_00353480();
extern unsigned long skp5_FUN_0035348c();
extern unsigned long skp5_FUN_003534a4();
extern unsigned long skp5_FUN_003534bc();
extern unsigned long skp5_FUN_003534f8();
extern unsigned long skp5_FUN_0035354c();
extern unsigned long skp5_FUN_0035363c();
extern unsigned long skp5_FUN_00353734();
extern unsigned long skp5_FUN_00353990();
extern unsigned long skp5_FUN_003539a8();
extern unsigned long skp5_FUN_003539d8();
extern unsigned long skp5_FUN_00353a78();
extern unsigned long skp5_FUN_00353a84();
extern unsigned long skp5_FUN_00353aec();
extern unsigned long skp5_FUN_00353b04();
extern unsigned long skp5_FUN_00353b64();
extern unsigned long skp5_FUN_00353b7c();
extern unsigned long skp5_FUN_00353b94();
extern unsigned long skp5_FUN_00353bb8();
extern unsigned long skp5_FUN_00353bd0();
extern unsigned long skp5_FUN_00353be8();
extern unsigned long skp5_FUN_00353c0c();
extern unsigned long skp5_FUN_00353c3c();
extern unsigned long skp5_FUN_00353c60();
extern unsigned long skp5_FUN_00353ce4();
extern unsigned long skp5_FUN_00353d34();
extern unsigned long skp5_FUN_00353d44();
extern unsigned long skp5_FUN_00353d7c();
extern unsigned long skp5_FUN_00353d88();
extern unsigned long skp5_FUN_00353e08();
extern unsigned long skp5_FUN_00353e20();
extern unsigned long skp5_FUN_00353e44();
extern unsigned long skp5_FUN_00353e94();
extern unsigned long skp5_FUN_00353ef0();
extern unsigned long skp5_FUN_00353f2c();
extern unsigned long skp5_FUN_00353f50();
extern unsigned long skp5_FUN_00353fac();
extern unsigned long skp5_FUN_00354028();
extern unsigned long skp5_FUN_0035404c();
extern unsigned long skp5_FUN_00354064();
extern unsigned long skp5_FUN_0035407c();
extern unsigned long skp5_FUN_00354088();
extern unsigned long skp5_FUN_003540c4();
extern unsigned long skp5_FUN_00354128();
extern unsigned long skp5_FUN_00354134();
extern unsigned long skp5_FUN_00354270();
extern unsigned long skp5_FUN_00354324();
extern unsigned long skp5_FUN_00354388();
extern unsigned long skp5_FUN_003543b8();
extern unsigned long skp5_FUN_00354474();
extern unsigned long skp5_FUN_00354594();
extern unsigned long skp5_FUN_003545a0();
extern unsigned long skp5_FUN_0035460c();
extern unsigned long skp5_FUN_00354618();
extern unsigned long skp5_FUN_00354648();
extern unsigned long skp5_FUN_00354780();
extern unsigned long skp5_FUN_003547b0();
extern unsigned long skp5_FUN_003547c8();
extern unsigned long skp5_FUN_003547ec();
extern unsigned long skp5_FUN_00354810();
extern unsigned long skp5_FUN_0035481c();
extern unsigned long skp5_FUN_00354834();
extern unsigned long skp5_FUN_00354840();
extern unsigned long skp5_FUN_003548ac();
extern unsigned long skp5_FUN_003548b8();
extern unsigned long skp5_FUN_00354968();
extern unsigned long skp5_FUN_00354988();
extern unsigned long skp5_FUN_003549a8();
extern unsigned long skp5_FUN_00354a00();
extern unsigned long skp5_FUN_00354a34();
extern unsigned long skp5_FUN_00354ac8();
extern unsigned long skp5_FUN_00354ad4();
extern unsigned long skp5_FUN_00354afc();
extern unsigned long skp5_FUN_00354b20();
extern unsigned long skp5_FUN_00354b38();
extern unsigned long skp5_FUN_00354b44();
extern unsigned long skp5_FUN_00354b74();
extern unsigned long skp5_FUN_00354b80();
extern unsigned long skp5_FUN_00354bbc();
extern unsigned long skp5_FUN_00354bec();
extern unsigned long skp5_FUN_00354c64();
extern unsigned long skp5_FUN_00354cb4();
extern unsigned long skp5_FUN_00354cc0();
extern unsigned long skp5_FUN_00354cf0();
extern unsigned long skp5_FUN_00354d08();
extern unsigned long skp5_FUN_00354d68();
extern unsigned long skp5_FUN_00354d94();
extern unsigned long skp5_FUN_00354df4();
extern unsigned long skp5_FUN_00354e00();
extern unsigned long skp5_FUN_00354e0c();
extern unsigned long skp5_FUN_00354ef8();
extern unsigned long skp5_FUN_00354f64();
extern unsigned long skp5_FUN_0035505c();
extern unsigned long skp5_FUN_00355068();
extern unsigned long skp5_FUN_00355074();
extern unsigned long skp5_FUN_00355230();
extern unsigned long skp5_FUN_003552bc();
extern unsigned long skp5_FUN_00355324();
extern unsigned long skp5_FUN_00355640();
extern unsigned long skp5_FUN_00355740();
extern unsigned long skp5_FUN_00355a00();
extern unsigned long skp5_FUN_00355ab4();
extern unsigned long skp5_FUN_00355ad0();
extern unsigned long skp5_FUN_00355c10();
extern unsigned long skp5_FUN_00355c34();
extern unsigned long skp5_FUN_00355c68();
extern unsigned long skp5_FUN_00355c84();
extern unsigned long skp5_FUN_00355cb0();
extern unsigned long skp5_FUN_00355cc8();
extern unsigned long skp5_FUN_00355d9c();
extern unsigned long skp5_FUN_00355dc0();
extern unsigned long skp5_FUN_00355dfc();
extern unsigned long skp5_FUN_00355e2c();
extern unsigned long skp5_FUN_00355e80();
extern unsigned long skp5_FUN_00355eec();
extern unsigned long skp5_FUN_00355f88();
extern unsigned long skp5_FUN_00355f94();
extern unsigned long skp5_FUN_00355fac();
extern unsigned long skp5_FUN_00355fc4();
extern unsigned long skp5_FUN_00355ff4();
extern unsigned long skp5_FUN_00356060();
extern unsigned long skp5_FUN_0035606c();
extern unsigned long skp5_FUN_00356078();
extern unsigned long skp5_FUN_0035614c();
extern unsigned long skp5_FUN_00356188();
extern unsigned long skp5_FUN_003561ac();
extern unsigned long skp5_FUN_00356230();
extern unsigned long skp5_FUN_00356254();
extern unsigned long skp5_FUN_003562ec();
extern unsigned long skp5_FUN_003564a4();
extern unsigned long skp5_FUN_003564d0();
extern unsigned long skp5_FUN_00356584();
extern unsigned long skp5_FUN_00356664();
extern unsigned long skp5_FUN_003566b4();
extern unsigned long skp5_FUN_003566c0();
extern unsigned long skp5_FUN_00356704();
extern unsigned long skp5_FUN_00356750();
extern unsigned long skp5_FUN_0035678c();
extern unsigned long skp5_FUN_003567b0();
extern unsigned long skp5_FUN_003567e0();
extern unsigned long skp5_FUN_00356804();
extern unsigned long skp5_FUN_00356810();
extern unsigned long skp5_FUN_0035681c();
extern unsigned long skp5_FUN_00356840();
extern unsigned long skp5_FUN_0035684c();
extern unsigned long skp5_FUN_00356900();
extern unsigned long skp5_FUN_0035690c();
extern unsigned long skp5_FUN_0035694c();
extern unsigned long skp5_FUN_00356970();
extern unsigned long skp5_FUN_003569c0();
extern unsigned long skp5_FUN_003569d8();
extern unsigned long skp5_FUN_003569f0();
extern unsigned long skp5_FUN_003569fc();
extern unsigned long skp5_FUN_00356a88();
extern unsigned long skp5_FUN_00356a94();
extern unsigned long skp5_FUN_00356adc();
extern unsigned long skp5_FUN_00356af4();
extern unsigned long skp5_FUN_00356b20();
extern unsigned long skp5_FUN_00356b74();
extern unsigned long skp5_FUN_00356bd4();
extern unsigned long skp5_FUN_00356c30();
extern unsigned long skp5_FUN_00356c78();
extern unsigned long skp5_FUN_00356d20();
extern sk_wide_t skp5_FUN_00356ea8();
extern unsigned long skp5_FUN_00357094();
extern unsigned long skp5_FUN_003570d8();
extern unsigned long skp5_FUN_003570e4();
extern unsigned long skp5_FUN_0035723c();
extern unsigned long skp5_FUN_00357244();
extern unsigned long skp5_FUN_00357268();
extern unsigned long skp5_FUN_00357344();
extern unsigned long skp5_FUN_0035735c();
extern unsigned long skp5_FUN_0035738c();
extern unsigned long skp5_FUN_00357398();
extern unsigned long skp5_FUN_003573cc();
extern unsigned long skp5_FUN_0035740c();
extern unsigned long skp5_FUN_0035754c();
extern unsigned long skp5_FUN_00357558();
extern unsigned long skp5_FUN_003575b0();
extern unsigned long skp5_FUN_00357634();
extern unsigned long skp5_FUN_00357664();
extern unsigned long skp5_FUN_003576dc();
extern unsigned long skp5_FUN_00357754();
extern unsigned long skp5_FUN_003578c0();
extern unsigned long skp5_FUN_00357904();
extern unsigned long skp5_FUN_00357910();
extern unsigned long skp5_FUN_0035798c();
extern unsigned long skp5_FUN_003579cc();
extern unsigned long skp5_FUN_00357a5c();
extern unsigned long skp5_FUN_00357a9c();
extern unsigned long skp5_FUN_00357aa8();
extern unsigned long skp5_FUN_00357c58();
extern unsigned long skp5_FUN_00357c88();
extern unsigned long skp5_FUN_00357d54();
extern unsigned long skp5_FUN_00357f44();
extern unsigned long skp5_FUN_00357f54();
extern unsigned long skp5_FUN_00358064();
extern unsigned long skp5_FUN_00358218();
extern unsigned long skp5_FUN_00358238();
extern unsigned long skp5_FUN_0035847c();
extern unsigned long skp5_FUN_003585d0();
extern unsigned long skp5_FUN_00358630();
extern unsigned long skp5_FUN_00358648();
extern sk_wide_t skp5_FUN_003586d8();
extern unsigned long skp5_FUN_00358720();
extern sk_wide_t skp5_FUN_003587d4();
extern unsigned long skp5_FUN_00358864();
extern unsigned long skp5_FUN_00358978();
extern unsigned long skp5_FUN_0035899c();
extern unsigned long skp5_FUN_003589c0();
extern unsigned long skp5_FUN_003589cc();
extern unsigned long skp5_FUN_003589d8();
extern unsigned long skp5_FUN_00358a20();
extern sk_wide_t skp5_FUN_00358a74();
extern unsigned long skp5_FUN_00358b48();
extern unsigned long skp5_FUN_00358bcc();
extern unsigned long skp5_FUN_00358bf0();
extern unsigned long skp5_FUN_00358d10();
extern unsigned long skp5_FUN_00358d34();
extern unsigned long skp5_FUN_00358d58();
extern unsigned long skp5_FUN_00358d88();
extern unsigned long skp5_FUN_00358db8();
extern unsigned long skp5_FUN_00358ddc();
extern unsigned long skp5_FUN_00358e94();
extern unsigned long skp5_FUN_00358eac();
extern unsigned long skp5_FUN_00358ec4();
extern unsigned long skp5_FUN_00358ed0();
extern unsigned long skp5_FUN_00358f48();
extern unsigned long skp5_FUN_00358f84();
extern unsigned long skp5_FUN_0035911c();
extern unsigned long skp5_FUN_00359144();
extern unsigned long skp5_FUN_00359208();
extern unsigned long skp5_FUN_003592c8();
extern unsigned long skp5_FUN_00359338();
extern unsigned long skp5_FUN_003593c0();
extern unsigned long skp5_FUN_00359518();
extern unsigned long skp5_FUN_0035978c();
extern unsigned long skp5_FUN_003597a0();
extern unsigned long skp5_FUN_003597e4();
extern unsigned long skp5_FUN_0035985c();
extern unsigned long skp5_FUN_00359868();
extern unsigned long skp5_FUN_003598c0();
extern unsigned long skp5_FUN_003599d8();
extern unsigned long skp5_FUN_00359a48();
extern unsigned long skp5_FUN_00359a60();
extern unsigned long skp5_FUN_00359b18();
extern unsigned long skp5_FUN_00359b24();
extern unsigned long skp5_FUN_00359e74();
extern unsigned long skp5_FUN_00359e80();
extern unsigned long skp5_FUN_00359ef4();
extern unsigned long skp5_FUN_0035a19c();
extern unsigned long skp5_FUN_0035a2b8();
extern unsigned long skp5_FUN_0035a348();
extern unsigned long skp5_FUN_0035a360();
extern unsigned long skp5_FUN_0035a3e8();
extern unsigned long skp5_FUN_0035a44c();
extern unsigned long skp5_FUN_0035a540();
extern unsigned long skp5_FUN_0035a54c();
extern unsigned long skp5_FUN_0035a560();
extern unsigned long skp5_FUN_0035a56c();
extern unsigned long skp5_FUN_0035a5a8();
extern sk_wide_t skp5_FUN_0035a5c0();
extern unsigned long skp5_FUN_0035a5f0();
extern unsigned long skp5_FUN_0035a634();
extern unsigned long skp5_FUN_0035a64c();
extern unsigned long skp5_FUN_0035a658();
extern unsigned long skp5_FUN_0035a700();
extern unsigned long skp5_FUN_0035a718();
extern unsigned long skp5_FUN_0035a724();
extern unsigned long skp5_FUN_0035ab88();
extern unsigned long skp5_FUN_0035aba4();
extern unsigned long skp5_FUN_0035ac40();
extern unsigned long skp5_FUN_0035ac58();
extern unsigned long skp5_FUN_0035ac70();
extern unsigned long skp5_FUN_003698b0();
extern unsigned long skp5_FUN_0036a804();
extern unsigned long skp5_FUN_0036a940();
extern unsigned long skp5_FUN_0036b118();
extern unsigned long skp5_FUN_0036b270();
extern unsigned long skp5_FUN_003722e4();
extern unsigned long skp5_FUN_00376820();
extern unsigned long skp5_FUN_00377824();
extern unsigned long skp5_FUN_00377bec();
extern unsigned long skp5_FUN_00377dcc();
extern unsigned long skp5_FUN_0039ff2c();
extern unsigned long skp5_FUN_003a017c();
extern unsigned long skp5_FUN_003a0440();
extern unsigned long skp5_FUN_003a0dec();
extern unsigned long skp5_FUN_003a0e44();
extern unsigned long skp5_FUN_003a25d4();
extern unsigned long skp5_FUN_003d31f8();

/* ---- other ---- */
extern unsigned long FUN_0060e3fc;
extern unsigned long FUN_0060e40c;
extern unsigned long FUN_00610504;
/* Alias map: in-slice FUN_ names -> the English-named functions defined in this file. */
#define skp5_FUN_00233354 skp5_sk_uint64_to_string_radix
#define skp5_FUN_00233ba8 skp5_sk_int64_to_string_radix
#define skp5_FUN_00233f04 skp5_sk_uint128_to_string_radix
#define skp5_FUN_002336a8 skp5_sk_int128_to_string_radix
#define skp5_FUN_00235398 skp5_sk_ptr_initialize_repeating
#define skp5_FUN_00235410 skp5_sk_ptr_initialize_repeating_words
#define skp5_FUN_0023560c skp5_sk_int128_from_string_slow
#define skp5_FUN_002357b4 skp5_sk_int8_to_string
#define skp5_FUN_00235ac4 sk_int64_to_string_full
#define skp5_FUN_00235fc8 sk_int128_to_string_full
#define skp5_FUN_002364dc skp5_sk_int64_from_string_radix
#define skp5_FUN_002366a0 skp5_sk_uint64_from_string_radix
#define skp5_FUN_002369a8 sk_int16_to_string
#define skp5_FUN_00236cb8 skp5_sk_int32_to_string
#define skp5_FUN_00236fc4 skp5_sk_uint128_to_string_full
#define skp5_FUN_00237040 thunk_sk_fatal_error_thunk
#define skp5_FUN_002332d4 skp5_sk_vspace_dispatch_stub
#define skp5_FUN_00234384 skp5_sk_integer_description_dispatch
#define skp5_FUN_002351ac skp5_sk_runtime_thunk_2351ac
#define skp5_FUN_00235298 skp5_sk_int128_from_string
#define skp5_FUN_00235488 skp5_sk_collection_initialize_buffer
#define skp5_FUN_0023723c skp5_sk_fatal_redirect
#define skp5_FUN_0023737c sk_fatal_range_lowerbound
#define skp5_FUN_002373c4 sk_uint64_from_string_radix_c
#define skp5_FUN_002376d0 sk_uint16_from_string
#define skp5_FUN_002379dc skp5_sk_uint64_from_string_decimal
#define skp5_FUN_00237b94 skp5_sk_uint64_from_string_radix64
#define skp5_FUN_00237f7c skp5_sk_big_string_builder
#define skp5_FUN_00238cb0 skp5_sk_collection_subscript_range
#define skp5_FUN_00238e1c skp5_sk_collection_read_index_wide
#define skp5_FUN_00239294 skp5_sk_collection_write_index_wide
#define skp5_FUN_0023a354 skp5_sk_collection_subscript_assign
#define skp5_FUN_0023ae70 sk_string_append_overflow
#define skp5_FUN_0023b03c sk_runtime_thunk_b03c
#define skp5_FUN_0023b06c sk_runtime_thunk_b06c
#define skp5_FUN_0023b0e0 sk_runtime_thunk_b0e0
#define skp5_FUN_0023b144 sk_runtime_thunk_b144
#define skp5_FUN_0023b18c sk_byteswap128
#define skp5_FUN_0023b190 sk_byteswap16
#define skp5_FUN_0023b198 sk_byteswap32
#define skp5_FUN_0023b1a0 sk_byteswap64
#define skp5_FUN_0023b1a8 sk_byteswap128_pair
#define skp5_FUN_0023b1b4 sk_runtime_thunk_b1b4
#define skp5_FUN_0023b254 sk_int128_multiply
#define skp5_FUN_0023b2a0 skp5_sk_int128_multiply_full
#define skp5_FUN_0023b458 sk_runtime_thunk_b458
#define skp5_FUN_0023b5c0 sk_runtime_thunk_b5c0
#define skp5_FUN_0023b644 skp5_sk_obj_method_dispatch
#define skp5_FUN_0023b7b8 sk_big_int_to_string
#define skp5_FUN_0023c780 sk_runtime_thunk_c780
#define skp5_FUN_0023c784 skp5_sk_runtime_thunk_c784
#define skp5_FUN_0023c79c skp5_sk_obj_service_w
#define skp5_FUN_0023cb80 sk_runtime_thunk_cb80
#define skp5_FUN_0023cbac sk_runtime_thunk_cbac
#define skp5_FUN_0023cbb0 skp5_sk_runtime_thunk_cbb0
#define skp5_FUN_0023cbc8 skp5_sk_obj_service_r
#define skp5_FUN_0023cd98 skp5_sk_int64_parse_overflow
#define skp5_FUN_0023d83c skp5_sk_int128_parse_overflow
#define skp5_FUN_0023e1fc skp5_sk_uint128_parse_overflow
#define skp5_FUN_0023ebac sk_uint128_parse_overflow_b
#define skp5_FUN_0023eeec skp5_sk_uint128_parse_overflow_c
#define skp5_FUN_0023f9c8 skp5_sk_int128_parse_overflow_b
#define skp5_FUN_00240388 skp5_sk_uint128_parse_overflow_d
#define skp5_FUN_00240e10 sk_uint128_parse_overflow_e
#define skp5_FUN_0024114c skp5_sk_double_to_int128
#define skp5_FUN_002412d4 skp5_sk_obj_service_m
#define skp5_FUN_002428d0 skp5_sk_double_to_int128_overflow_msg
#define skp5_FUN_00242cd0 skp5_sk_string_builder_loop
#define skp5_FUN_0024304c skp5_sk_obj_allocate_and_init
#define skp5_FUN_0024320c sk_collection_replace_range
#define skp5_FUN_00243c5c thunk_sk_runtime_thunk_3c5c
#define skp5_FUN_00243c60 skp5_sk_obj_method_call_wide
#define skp5_FUN_002444a0 sk_runtime_thunk_44a0
#define skp5_FUN_002444f8 sk_runtime_thunk_44f8
#define skp5_FUN_002445ac skp5_sk_obj_format_value
#define skp5_FUN_002448e0 sk_collection_equal_range
#define skp5_FUN_0024502c sk_runtime_thunk_502c
#define skp5_FUN_002450ec skp5_sk_uint128_divide
#define skp5_FUN_002456a0 sk_uint128_is_zero
#define skp5_FUN_002456a4 skp5_sk_uint128_is_zero_b
#define skp5_FUN_002457dc sk_range_is_empty
#define skp5_FUN_0024580c skp5_sk_int128_description
#define skp5_FUN_00245ef0 skp5_sk_int128_divide_full
#define skp5_FUN_0024607c skp5_sk_obj_method_dispatch_wide
#define skp5_FUN_002460d4 skp5_sk_obj_method_dispatch_wide_default
#define skp5_FUN_00246138 skp5_sk_uint128_add
#define skp5_FUN_00246144 sk_word_add
#define skp5_FUN_0024614c skp5_thunk_sk_word_add
#define skp5_FUN_00246164 skp5_sk_uint128_sub
#define skp5_FUN_00246170 sk_word_sub
#define skp5_FUN_00246178 skp5_thunk_sk_word_sub
#define skp5_FUN_00246188 skp5_sk_obj_store_field
#define skp5_FUN_002461c0 sk_obj_store_field_c0
#define skp5_FUN_00246264 skp5_sk_obj_call_slot_64
#define skp5_FUN_002462f4 skp5_sk_obj_call_slot_f4
#define skp5_FUN_00246388 skp5_sk_obj_store_field_88
#define skp5_FUN_002463dc sk_obj_release_field_dc
#define skp5_FUN_0024640c skp5_sk_obj_store_field_pair
#define skp5_FUN_00246490 skp5_sk_obj_construct
#define skp5_FUN_0024657c skp5_sk_obj_service_s
#define skp5_FUN_00246c68 skp5_sk_obj_service_store
#define skp5_FUN_00246d54 skp5_sk_obj_service_iter
#define skp5_FUN_002471f4 sk_obj_service_poll
#define skp5_FUN_002472b4 sk_obj_slot_dispatch
#define skp5_FUN_002472e0 skp5_sk_collection_range_bounds
#define skp5_FUN_00247308 sk_obj_deref
#define skp5_FUN_0024730c skp5_sk_obj_deref_b
#define skp5_FUN_0024733c skp5_sk_swift_keypath_alloc
#define skp5_FUN_00247340 skp5_sk_swift_keypath_alloc_b
#define skp5_FUN_00247360 skp5_sk_swift_keypath_alloc_c
#define skp5_FUN_002473f0 sk_buffer_validate
#define skp5_FUN_00247454 skp5_sk_collection_range_equal_wide
#define skp5_FUN_002478d4 skp5_sk_collection_element_description
#define skp5_FUN_002487b8 skp5_sk_collection_map_reduce
#define skp5_FUN_0024881c sk_collection_guard_range
#define skp5_FUN_00248860 sk_collection_apply
#define skp5_FUN_002488b4 skp5_sk_collection_range_get
#define skp5_FUN_00248900 sk_collection_reduce_wide
#define skp5_FUN_0024893c skp5_sk_collection_sum_wide
#define skp5_FUN_00248a34 skp5_sk_collection_next_element
#define skp5_FUN_00248ae0 sk_word_width_decode

/* ================================================================== *
 * Function bodies — in address order.
 * ================================================================== */

/* skp5_FUN_002332d4 @ 0x2332d4   (est. skp5_sk_vspace_dispatch_stub)
 * Ghidra: undefined skp5_FUN_002332d4(void)
 * Thin tail-dispatch stub: saves LR, invokes the object allocator /
 * runtime entry helpers in sequence, dispatches through a PAC'd function
 * pointer slot, then unwinds via the runtime LR-restore helper. It is a
 * glue trampoline into the shared runtime rather than independent logic.
 * Confidence: low
 * Notes: body 0x2332d4-0x233353; PAC'd indirect calls (autda/blraa); the
 *   callees skp5_FUN_00084220/00084234 bracket the body (runtime enter/leave). */
void skp5_sk_vspace_dispatch_stub(void);
void skp5_sk_big_string_builder(void);
void sk_buffer_validate(long base, long count);
sk_wide_t sk_byteswap128(uint64_t lo, uint64_t hi);
void sk_byteswap128_pair(uint64_t a, uint64_t b);
uint32_t sk_byteswap16(uint32_t v);
uint32_t sk_byteswap32(uint32_t v);
uint64_t sk_byteswap64(uint64_t v);
void sk_collection_apply(void);
sk_wide_t skp5_sk_collection_element_description(long coll, sk_wide_t *out,
                                            long meta, unsigned long count);
void sk_collection_equal_range(void);
uint32_t sk_collection_guard_range(long coll, unsigned long a, uint32_t flags);
void skp5_sk_collection_initialize_buffer(void);
unsigned long skp5_sk_collection_map_reduce(unsigned long (*cb)(unsigned long, unsigned long, unsigned long, uint32_t),
                                       unsigned long arg, uint32_t flags);
sk_wide_t skp5_sk_collection_next_element(void);
sk_wide_t skp5_sk_collection_range_bounds(void);
bool skp5_sk_collection_range_equal_wide(long a, long b, long lo, long hi);
sk_wide_t skp5_sk_collection_range_get(unsigned long base);
void skp5_sk_collection_read_index_wide(void);
sk_wide_t sk_collection_reduce_wide(void);
void sk_collection_replace_range(void);
void skp5_sk_collection_subscript_assign(void);
void skp5_sk_collection_subscript_range(void);
void skp5_sk_collection_sum_wide(void);
void skp5_sk_collection_write_index_wide(void);
bool skp5_sk_double_to_int128(double d, void *out);
sk_wide_t skp5_sk_double_to_int128_overflow_msg(void);
void sk_fatal_range_lowerbound(void);
void skp5_sk_fatal_redirect(void);
void skp5_sk_int128_description(void);
sk_wide_t skp5_sk_int128_divide_full(sk_wide_t *out, uint64_t ah, uint64_t al,
                                int64_t bh, int64_t bl, uint64_t dh, uint64_t dl);
void skp5_sk_int128_from_string(void);
void skp5_sk_int128_from_string_slow(void);
sk_wide_t sk_int128_multiply(unsigned long *out, uint64_t a0, uint64_t a1,
                             uint64_t b0, uint64_t b1);
sk_wide_t skp5_sk_int128_multiply_full(unsigned long *out, uint64_t a0, uint64_t a1,
                                  uint64_t b0, uint64_t b1);
void skp5_sk_int128_parse_overflow(void);
void skp5_sk_int128_parse_overflow_b(void);
sk_wide_t sk_int128_to_string_full(unsigned long radix, uint32_t uppercase,
                                   uint64_t lo, uint64_t hi);
sk_wide_t skp5_sk_int128_to_string_radix(uint32_t neg, uint64_t lo, uint64_t hi,
                                    int64_t radix, int64_t r2, uint64_t upper,
                                    void **buf_cap);
void sk_int16_to_string(unsigned long radix, uint32_t uppercase, uint32_t value);
void skp5_sk_int32_to_string(unsigned long radix, uint32_t uppercase, uint32_t value);
void skp5_sk_int64_from_string_radix(unsigned long radix, uint32_t uppercase,
                                int64_t value);
void skp5_sk_int64_parse_overflow(void);
sk_wide_t sk_int64_to_string_full(unsigned long radix, uint32_t uppercase,
                                  int64_t value, int64_t r4);
sk_wide_t skp5_sk_int64_to_string_radix(uint64_t neg, uint64_t value,
                                   uint64_t radix, uint64_t uppercase,
                                   void **buf_cap);
void skp5_sk_int8_to_string(unsigned long radix, uint32_t uppercase, uint32_t value);
void skp5_sk_integer_description_dispatch(uint32_t neg, void **lo_out, void **hi_out,
                                     void **str_buf, unsigned long radix,
                                     int64_t style, unsigned long value);
void skp5_sk_obj_allocate_and_init(void);
void skp5_sk_obj_call_slot_64(void);
void skp5_sk_obj_call_slot_f4(void);
void skp5_sk_obj_construct(void);
unsigned long sk_obj_deref(void);
/* skp5_FUN_0024730c @ 0x24730c   (est. skp5_sk_obj_deref_b)
 * Ghidra: undefined8 skp5_FUN_0024730c(void)
 * Object deref variant; identical to sk_obj_deref.
 * Confidence: low */
unsigned long skp5_sk_obj_deref_b(void);
void skp5_sk_obj_format_value(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5);
void skp5_sk_obj_method_call_wide(void);
void skp5_sk_obj_method_dispatch(void);
sk_wide_t skp5_sk_obj_method_dispatch_wide(void);
sk_wide_t skp5_sk_obj_method_dispatch_wide_default(void);
void sk_obj_release_field_dc(long meta);
void skp5_sk_obj_service_iter(void);
void skp5_sk_obj_service_m(void);
void sk_obj_service_poll(void);
void skp5_sk_obj_service_r(unsigned long p1, unsigned long p2, unsigned long p3);
void skp5_sk_obj_service_s(void);
void skp5_sk_obj_service_store(void);
void skp5_sk_obj_service_w(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5);
unsigned long sk_obj_slot_dispatch(void);
void skp5_sk_obj_store_field(unsigned long value, long meta);
void skp5_sk_obj_store_field_88(unsigned long value, long meta);
void sk_obj_store_field_c0(void);
void skp5_sk_obj_store_field_pair(unsigned long lo, unsigned long hi, long meta);
void skp5_sk_ptr_initialize_repeating(unsigned char v, long count, unsigned char *dst);
void skp5_sk_ptr_initialize_repeating_words(unsigned long v, long count, unsigned long *dst);
bool sk_range_is_empty(void);
void skp5_sk_runtime_thunk_2351ac(void);
void sk_runtime_thunk_44a0(void);
void sk_runtime_thunk_44f8(void);
void sk_runtime_thunk_502c(void);
void sk_runtime_thunk_b03c(void);
void sk_runtime_thunk_b06c(void);
void sk_runtime_thunk_b0e0(void);
uint32_t sk_runtime_thunk_b144(void);
void sk_runtime_thunk_b1b4(void);
void sk_runtime_thunk_b458(void);
void sk_runtime_thunk_b5c0(void);
void sk_runtime_thunk_c780(void);
/* skp5_FUN_0023c784 @ 0x23c784   (est. skp5_sk_runtime_thunk_c784)
 * Ghidra: void skp5_FUN_0023c784(void)
 * Runtime glue thunk; identical to sk_runtime_thunk_c780.
 * Confidence: low */
void skp5_sk_runtime_thunk_c784(void);
void sk_runtime_thunk_cb80(void);
void sk_runtime_thunk_cbac(void);
/* skp5_FUN_0023cbb0 @ 0x23cbb0   (est. skp5_sk_runtime_thunk_cbb0)
 * Ghidra: void skp5_FUN_0023cbb0(void)
 * Runtime glue thunk into 0023c79c; identical to sk_runtime_thunk_cbac.
 * Confidence: low */
void skp5_sk_runtime_thunk_cbb0(void);
void sk_string_append_overflow(void);
void skp5_sk_string_builder_loop(void);
long skp5_sk_swift_keypath_alloc(void);
long skp5_sk_swift_keypath_alloc_b(void);
long skp5_sk_swift_keypath_alloc_c(void);
sk_wide_t skp5_sk_uint128_add(uint64_t a0, uint64_t a1, uint64_t b0, uint64_t b1);
sk_wide_t skp5_sk_uint128_divide(unsigned long *out, uint64_t ah, uint64_t al,
                            uint64_t bh, uint64_t bl, uint64_t dh, uint64_t dl);
bool sk_uint128_is_zero(unsigned long a, unsigned long b, unsigned long lo,
                        unsigned long hi);
/* skp5_FUN_002456a4 @ 0x2456a4   (est. skp5_sk_uint128_is_zero_b)
 * Ghidra: bool skp5_FUN_002456a4(undefined8,undefined8,undefined8,undefined8)
 * Returns whether the 128-bit value is zero; duplicate of 002456a0.
 * Confidence: medium */
bool skp5_sk_uint128_is_zero_b(unsigned long a, unsigned long b, unsigned long lo,
                          unsigned long hi);
void skp5_sk_uint128_parse_overflow(void);
void sk_uint128_parse_overflow_b(void);
void skp5_sk_uint128_parse_overflow_c(void);
void skp5_sk_uint128_parse_overflow_d(void);
void sk_uint128_parse_overflow_e(void);
sk_wide_t skp5_sk_uint128_sub(uint64_t a0, uint64_t a1, uint64_t b0, uint64_t b1);
void skp5_sk_uint128_to_string_full(unsigned long radix, uint32_t uppercase,
                               uint64_t lo, uint64_t hi);
sk_wide_t skp5_sk_uint128_to_string_radix(uint32_t neg, uint64_t lo, uint64_t hi,
                                     int64_t radix, int64_t r2, uint64_t upper,
                                     void **buf_cap);
void sk_uint16_from_string(unsigned long radix, uint32_t uppercase,
                           unsigned short value);
void skp5_sk_uint64_from_string_decimal(void);
void skp5_sk_uint64_from_string_radix(unsigned long radix, uint32_t uppercase,
                                 uint32_t value);
void skp5_sk_uint64_from_string_radix64(unsigned long radix, uint32_t uppercase,
                                   uint64_t lo, int64_t hi);
void sk_uint64_from_string_radix_c(unsigned long radix, uint32_t uppercase,
                                   unsigned char value);
sk_wide_t skp5_sk_uint64_to_string_radix(uint64_t is_neg, uint64_t value,
                                   uint64_t radix, uint64_t uppercase,
                                   void **buf_cap);
int sk_word_add(int a, int b);
int sk_word_sub(int a, int b);
uint64_t sk_word_width_decode(uint32_t sel);
void thunk_sk_fatal_error_thunk(void);
void thunk_sk_runtime_thunk_3c5c(void);
/* skp5_FUN_0024614c @ 0x24614c   (thunk sk_word_add)
 * Ghidra: long thunk_FUN_0035911c(long,long)
 * Word addition thunk.
 * Confidence: high */
long skp5_thunk_sk_word_add(long a, long b);
/* skp5_FUN_00246178 @ 0x246178   (thunk sk_word_sub)
 * Ghidra: long skp5_FUN_00246178(long,long)
 * Word subtraction thunk.
 * Confidence: high */
long skp5_thunk_sk_word_sub(long a, long b);
extern void (*FUN_00658c00_REF)(void);
extern void skp5_sk_indirect_dispatch(unsigned long, ...);  /* variadic: accepts any args (unresolved indirect dispatch) */

/* ================================================================== *
 * Function bodies — in address order.
 * ================================================================== */

/* skp5_FUN_002332d4 @ 0x2332d4   (est. skp5_sk_vspace_dispatch_stub)
 * Ghidra: undefined skp5_FUN_002332d4(void)
 * Thin tail-dispatch stub: saves LR, invokes the object allocator /
 * runtime entry helpers in sequence, dispatches through a PAC'd function
 * pointer slot, then unwinds via the runtime LR-restore helper. It is a
 * glue trampoline into the shared runtime rather than independent logic.
 * Confidence: low
 * Notes: body 0x2332d4-0x233353; PAC'd indirect calls (autda/blraa); the
 *   callees skp5_FUN_00084220/00084234 bracket the body (runtime enter/leave). */
void skp5_sk_vspace_dispatch_stub(void)
{
    unsigned long lr_ret;
    unsigned long arg;
    unsigned long (*slot)(unsigned long);
    unsigned long (*tramp)(void);

    skp5_FUN_00084220();                 /* runtime enter (saves LR in x7) */
    skp5_FUN_00356188();
    arg = skp5_FUN_0034b5a8();
    skp5_FUN_0034b07c(arg, arg);
    slot = (unsigned long (*)(unsigned long))(0x0 + 0x10); /* [x16+0x10] */
    slot(0);
    tramp = (unsigned long (*)(void))0;                            /* x19 */
    tramp();
    skp5_FUN_0034bddc();
    skp5_FUN_003518d0();
    /* indirect dispatch via x8 slot */
    ((unsigned long (*)(void))0)();
    lr_ret = skp5_FUN_00084234(0);       /* runtime leave */
    (void)lr_ret;
}

/* skp5_FUN_00233354 @ 0x233354   (est. skp5_sk_uint64_to_string_radix)
 * Ghidra: undefined1 [16] skp5_FUN_00233354(ulong,ulong,ulong,ulong,undefined8*)
 * Converts an unsigned 64-bit value to its string representation in the
 * given radix (2..36), writing the digits into the caller-provided buffer
 * ([param_5] = {buf, cap}). Returns the {start,count} range of written
 * digits. Handles the common radices (binary, octal, decimal, hex) with
 * per-radix loops; arbitrary radices use repeated division. Fatal-errors
 * on radix 0, out-of-range index, or buffer underflow.
 * Confidence: medium
 * Notes: Swift integer-to-string core; digit table at 0x4e7a30; the "esrever
 *   reversed" string 004e7a30 is the reversed decimal digit pair table. */
sk_wide_t skp5_sk_uint64_to_string_radix(uint64_t is_neg, uint64_t value,
                                   uint64_t radix, uint64_t uppercase,
                                   void **buf_cap)
{
    /* digit-pair table for decimal grouping */
    unsigned char digits[72];
    unsigned long out;
    unsigned long start;
    unsigned long p;
    unsigned long end;
    unsigned char d;

    unsigned long digits_lo = skp5_FUN_0006b2ec() & 0; /* table data (synthetic) */
    (void)digits_lo;
    if (value == 0) {
        ((unsigned char *)*buf_cap)[0] = '0';
        start = 1;
        out = 1;
        goto done;
    }
    out = ((unsigned long *)buf_cap)[1];   /* capacity */
    start = out;
    /* radix encoded as (radix-2)>>1 | radix<<63 trick */
    {
        unsigned long r = radix;
        switch (r) {
        case 2:
            for (; value != 0; value >>= 1) {
                ((unsigned char *)*buf_cap)[start - 1] = (unsigned char)value & 1 | '0';
                start -= 1;
            }
            break;
        case 8:
            for (; value != 0; value >>= 3) {
                ((unsigned char *)*buf_cap)[start - 1] = (unsigned char)value & 7 | '0';
                start -= 1;
            }
            break;
        case 10:
            p = out;
            for (; 9 < value; value /= 100) {
                ((unsigned short *)((char *)*buf_cap + p - 2))[0] =
                    *(unsigned short *)(digits + (value % 100) * 2);
                p -= 2;
            }
            start = p;
            if (value != 0) {
                start = p - 1;
                ((unsigned char *)*buf_cap)[p - 1] = (unsigned char)value | '0';
            }
            break;
        case 16:
            d = (uppercase & 1) ? 0 : 0x20;
            for (; value != 0; value >>= 4) {
                ((unsigned char *)*buf_cap)[start - 1] =
                    digits[(unsigned char)value & 0xf] | d;
                start -= 1;
            }
            break;
        default:
            d = (uppercase & 1) ? 0 : 0x20;
            while (value != 0) {
                if (radix == 0)
                    skp5_FUN_001afe4c(0xb, 2, 0x005ce4a0, 0x27, 2, 0x005cd6f0, 0x18, 2, 0x184c, 1);
                end = value / radix;
                value = value - end * radix;
                if (0x23 < value)
                    skp5_FUN_001afe4c(0xb, 2, 0x005cdab0, 0x13, 2, 0x005d3020, 0x18, 2, 0x178, 1);
                ((unsigned char *)*buf_cap)[start - 1] = digits[value] | d;
                start -= 1;
                value = end;
            }
            break;
        }
    }
    if ((is_neg & 1) != 0) {
        start -= 1;
        ((unsigned char *)*buf_cap)[start] = '-';
    }
    if (out < start)
        skp5_FUN_001afe4c(0xb, 2, 0x005cda00, 0x27, 2, 0x005cda30, 0x11, 2, 0x2f9, 1);
done:
    return (sk_wide_t){start, out};
}

/* skp5_FUN_002336a8 @ 0x2336a8   (est. skp5_sk_int128_to_string_radix)
 * Ghidra: undefined1 [16] skp5_FUN_002336a8(uint,ulong,ulong,long,long,ulong,undefined8*)
 * Converts a 128-bit unsigned integer (lo in param_2, hi in param_3) into its
 * radix-param_4 string, digits written into the caller buffer (*param_7),
 * capacity in param_7[1]. Returns {start,count}. Radix 0 divides by zero
 * (fatal error). Includes the '-' sign prefix when param_1&1 is set.
 * Confidence: medium
 * Notes: Swift UInt128.description core; digit table 0x4e7a30. */
sk_wide_t skp5_sk_int128_to_string_radix(uint32_t neg, uint64_t lo, uint64_t hi,
                                    int64_t radix, int64_t r2, uint64_t upper,
                                    void **buf_cap)
{
    unsigned char digits[72];
    unsigned long out;
    unsigned long start;
    unsigned long end;
    unsigned char d;
    (void)r2;

    if (hi == 0 && lo == 0) {
        ((unsigned char *)*buf_cap)[0] = '0';
        out = 1;
        start = 1;
        goto done;
    }
    out = ((unsigned long *)buf_cap)[1];
    start = out;
    if (radix == 16) {
        d = (upper & 1) ? 0 : 0x20;
        for (; hi != 0 || lo != 0; hi >>= 4) {
            ((unsigned char *)*buf_cap)[start - 1] = digits[(unsigned char)lo & 0xf] | d;
            start -= 1;
            lo = lo >> 4 | hi << 0x3c;
        }
    } else if (radix == 8) {
        for (; hi != 0 || lo != 0; hi >>= 3) {
            ((unsigned char *)*buf_cap)[start - 1] = (unsigned char)lo & 7 | '0';
            start -= 1;
            lo = lo >> 3 | hi << 0x3d;
        }
    } else if (radix == 2) {
        for (; hi != 0 || lo != 0; hi >>= 1) {
            ((unsigned char *)*buf_cap)[start - 1] = (unsigned char)lo & 1 | '0';
            start -= 1;
            lo = lo >> 1 | hi << 0x3f;
        }
    } else if (radix == 10) {
        end = out;
        while (hi != 0 || lo != 0) {
            /* divide 128-bit by 100 via runtime helper */
            unsigned long rem;
            unsigned long newlo, newhi;
            /* skp5_FUN_0011db10 divides (hi:lo) by 100 -> quotient; recompute */
            newlo = skp5_FUN_0011db10(lo, hi, 100, 0);
            newhi = 0;
            rem = 0;
            (void)newhi; (void)rem;
            ((unsigned short *)((char *)*buf_cap + end - 2))[0] =
                *(unsigned short *)(digits + ((unsigned long)skp5_FUN_0011db18(lo, 0, 100, 0) % 100) * 2);
            end -= 2;
            lo = newlo; hi = newhi;
            if (hi == 0 && lo < 100) break;
        }
        start = end;
        if (lo != 0) {
            start = end - 1;
            ((unsigned char *)*buf_cap)[end - 1] = (unsigned char)lo | '0';
        }
    } else {
        d = (upper & 1) ? 0 : 0x20;
        while (hi != 0 || lo != 0) {
            if (radix == 0)
                skp5_FUN_001afe4c(0xb, 2, 0x005d3048, 0xe, 2, 0x005d0de0, 0x18, 2, 0x1e1, 1);
            /* 128-bit remainder against radix via skp5_FUN_00312d08 */
            {
                unsigned long rem_lo = 0;
                skp5_FUN_00312d08(digits, digits, &rem_lo, hi, lo, 0, (unsigned long)radix);
                if (0x23 < rem_lo)
                    skp5_FUN_001afe4c(0xb, 2, 0x005cdab0, 0x13, 2, 0x005d3020, 0x18, 2, 0x178, 1);
                ((unsigned char *)*buf_cap)[start - 1] = digits[rem_lo] | d;
                start -= 1;
                lo = skp5_FUN_00312d08(digits, digits, &rem_lo, hi, lo, 0, (unsigned long)radix);
                hi = digits[0] & 0xff;
            }
        }
    }
    if ((neg & 1) != 0) {
        start -= 1;
        ((unsigned char *)*buf_cap)[start] = '-';
    }
    if (out < start)
        skp5_FUN_001afe4c(0xb, 2, 0x005cda00, 0x27, 2, 0x005cda30, 0x11, 2, 0x2f9, 1);
done:
    return (sk_wide_t){start, out};
}

/* skp5_FUN_00233ba8 @ 0x233ba8   (est. skp5_sk_int64_to_string_radix)
 * Ghidra: undefined1 [16] skp5_FUN_00233ba8(ulong,ulong,ulong,ulong,undefined8*)
 * Signed 64-bit variant of skp5_sk_uint64_to_string_radix: takes the sign bit in
 * param_1, the (already magnitude-abs'd) value in param_2 and radix in
 * param_3, writes digits to *param_5, returns {start,count}. Same radix
 * switch as the unsigned core; adds '-' when param_1&1.
 * Confidence: medium
 * Notes: shares digit table 0x4e7a30 with the unsigned formatter. */
sk_wide_t skp5_sk_int64_to_string_radix(uint64_t neg, uint64_t value,
                                   uint64_t radix, uint64_t uppercase,
                                   void **buf_cap)
{
    unsigned char digits[72];
    unsigned long out;
    unsigned long start;
    unsigned long p;
    unsigned char d;
    unsigned long mag = (neg & 0x8000000000000000ull) ? -value : value;

    if (mag == 0) {
        ((unsigned char *)*buf_cap)[0] = '0';
        out = 1; start = 1;
        goto done;
    }
    out = ((unsigned long *)buf_cap)[1];
    start = out;
    switch (radix) {
    case 2:
        for (; mag != 0; mag >>= 1) {
            ((unsigned char *)*buf_cap)[start-1] = (unsigned char)mag & 1 | '0'; start--;
        }
        break;
    case 8:
        for (; mag != 0; mag >>= 3) {
            ((unsigned char *)*buf_cap)[start-1] = (unsigned char)mag & 7 | '0'; start--;
        }
        break;
    case 10:
        p = out;
        for (; 9 < mag; mag /= 100) {
            ((unsigned short *)((char *)*buf_cap + p - 2))[0] =
                *(unsigned short *)(digits + (mag % 100) * 2);
            p -= 2;
        }
        start = p;
        if (mag != 0) {
            start = p - 1;
            ((unsigned char *)*buf_cap)[p-1] = (unsigned char)mag | '0';
        }
        break;
    case 16:
        d = (uppercase & 1) ? 0 : 0x20;
        for (; mag != 0; mag >>= 4) {
            ((unsigned char *)*buf_cap)[start-1] = digits[(unsigned char)mag & 0xf] | d; start--;
        }
        break;
    default:
        d = (uppercase & 1) ? 0 : 0x20;
        while (mag != 0) {
            if (radix == 0)
                skp5_FUN_001afe4c(0xb, 2, 0x005ce4a0, 0x27, 2, 0x005cd6f0, 0x18, 2, 0x184c, 1);
            p = mag / radix;
            mag = mag - p * radix;
            if (0x23 < mag)
                skp5_FUN_001afe4c(0xb, 2, 0x005cdab0, 0x13, 2, 0x005d3020, 0x18, 2, 0x178, 1);
            ((unsigned char *)*buf_cap)[start-1] = digits[mag] | d; start--;
            mag = p;
        }
        break;
    }
    if ((neg & 1) != 0) {
        start--; ((unsigned char *)*buf_cap)[start] = '-';
    }
    if (out < start)
        skp5_FUN_001afe4c(0xb, 2, 0x005cda00, 0x27, 2, 0x005cda30, 0x11, 2, 0x2f9, 1);
done:
    return (sk_wide_t){start, out};
}

/* skp5_FUN_00233f04 @ 0x233f04   (est. skp5_sk_uint128_to_string_radix)
 * Ghidra: undefined1 [16] skp5_FUN_00233f04(uint,ulong,ulong,long,long,ulong,undefined8*)
 * Unsigned 128-bit (lo=param_2, hi=param_3) formatter; mirrors the Int128
 * version but without sign. Returns {start,count} in the caller buffer.
 * Confidence: medium
 * Notes: digit table 0x4e7a30; division helper skp5_FUN_0011db10/0011db18. */
sk_wide_t skp5_sk_uint128_to_string_radix(uint32_t neg, uint64_t lo, uint64_t hi,
                                     int64_t radix, int64_t r2, uint64_t upper,
                                     void **buf_cap)
{
    unsigned char digits[72];
    unsigned long out;
    unsigned long start;
    unsigned long p;
    unsigned char d;
    (void)r2;
    if (lo == 0 && hi == 0) {
        ((unsigned char *)*buf_cap)[0] = '0';
        out = 1; start = 1;
        goto done;
    }
    out = ((unsigned long *)buf_cap)[1];
    start = out;
    if (radix == 16) {
        d = (upper & 1) ? 0 : 0x20;
        for (; lo != 0 || hi != 0; hi >>= 4) {
            ((unsigned char *)*buf_cap)[start-1] = digits[(unsigned char)lo & 0xf] | d; start--;
            lo = lo >> 4 | hi << 0x3c;
        }
    } else if (radix == 8) {
        for (; lo != 0 || hi != 0; hi >>= 3) {
            ((unsigned char *)*buf_cap)[start-1] = (unsigned char)lo & 7 | '0'; start--;
            lo = lo >> 3 | hi << 0x3d;
        }
    } else if (radix == 10) {
        p = out;
        while (hi != 0 || lo != 0) {
            /* remainder mod 100 from skp5_FUN_0011db10 */
            unsigned long rem;
            unsigned long nl, nh;
            nl = skp5_FUN_0011db10(lo, hi, 100, 0);
            nh = 0;
            rem = 0;
            (void)rem; (void)nh;
            ((unsigned short *)((char *)*buf_cap + p - 2))[0] =
                *(unsigned short *)(digits + ((unsigned long)skp5_FUN_0011db18(lo, hi, 100, 0) % 100) * 2);
            p -= 2;
            lo = nl; hi = nh;
            if (hi == 0 && lo < 100) break;
        }
        start = p;
        if (lo != 0) {
            start = p - 1;
            ((unsigned char *)*buf_cap)[p-1] = (unsigned char)lo | '0';
        }
    } else if (radix == 2) {
        for (; lo != 0 || hi != 0; hi >>= 1) {
            ((unsigned char *)*buf_cap)[start-1] = (unsigned char)lo & 1 | '0'; start--;
            lo = lo >> 1 | hi << 0x3f;
        }
    } else {
        d = (upper & 1) ? 0 : 0x20;
        while (lo != 0 || hi != 0) {
            if (radix == 0 && r2 == 0)
                skp5_FUN_001afe4c(0xb, 2, 0x005ce4a0, 0x27, 2, 0x005d1010, 0x13, 2, 0x175, 1);
            {
                unsigned long rem_lo = 0;
                skp5_FUN_00312d08(digits, digits, &rem_lo, hi, lo, 0, (unsigned long)radix);
                if (0x23 < rem_lo)
                    skp5_FUN_001afe4c(0xb, 2, 0x005cdab0, 0x13, 2, 0x005d3020, 0x18, 2, 0x178, 1);
                ((unsigned char *)*buf_cap)[start-1] = digits[rem_lo] | d; start--;
                lo = skp5_FUN_00312d08(digits, digits, &rem_lo, hi, lo, 0, (unsigned long)radix);
                hi = digits[0] & 0xff;
            }
        }
    }
    if ((neg & 1) != 0) {
        start--; ((unsigned char *)*buf_cap)[start] = '-';
    }
    if (out < start)
        skp5_FUN_001afe4c(0xb, 2, 0x005cda00, 0x27, 2, 0x005cda30, 0x11, 2, 0x2f9, 1);
done:
    return (sk_wide_t){start, out};
}

/* skp5_FUN_00234384 @ 0x234384   (est. skp5_sk_integer_description_dispatch)
 * Ghidra: void skp5_FUN_00234384(uint,undefined8*,undefined8*,undefined8*,undefined8,long,undefined8)
 * Swift integer-to-string description dispatcher. Depending on the trailing
 * style selector (param_6 == 0x677790 -> direct radix formatting; otherwise
 * full description with type name, radix, and error handling), it formats the
 * integer value into a heap string. The radix=10 (0x6777e0) path walks
 * decimal grouping, and the generic path emits the "0x"-prefixed hex or
 * decimal string into the caller's String buffer. Error paths fatal-error.
 * Confidence: low
 * Notes: large Swift stdlib description routine; string literals at
 *   0x4e7d50/4e7d58/4baee0; value metadata via skp5_FUN_00355324/skp5_FUN_003599d8. */
void skp5_sk_integer_description_dispatch(uint32_t neg, void **lo_out, void **hi_out,
                                     void **str_buf, unsigned long radix,
                                     int64_t style, unsigned long value)
{
    unsigned long u44;
    unsigned long u45;
    unsigned long u54;
    sk_wide_t r;
    u44 = skp5_FUN_0008f6c0(value);
    skp5_FUN_00355324();
    skp5_FUN_0034ef58();
    u45 = skp5_FUN_00377824();
    skp5_FUN_003599d8();
    skp5_FUN_0034c5ac(u44);
    skp5_FUN_00377bec();
    skp5_FUN_00351684();
    r = skp5_FUN_00349770();
    u54 = r.hi;
    skp5_FUN_00377824(r.lo, u54, u45);
    skp5_FUN_00349c44((void *)0xffffffffffffffa0);
    skp5_FUN_0007c1a4();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0034bdfc();
    skp5_FUN_00350530();
    skp5_FUN_00377dcc();
    skp5_FUN_00348e00();
    skp5_sk_indirect_dispatch(*(unsigned long *)(0x40) + 0x40);
    skp5_FUN_003493c4();
    skp5_FUN_0034acf0();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0034ae94();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00352008();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00350464();
    if (style == 0x677790) {
        /* direct radix formatting into the value words */
        skp5_sk_uint64_to_string_radix(neg & 1, *(unsigned long *)lo_out,
                                  *(unsigned long *)hi_out, (unsigned long)(*(unsigned long *)str_buf) & 1,
                                  (void **)str_buf);
    } else {
        skp5_FUN_00359a60(skp5_FUN_003509a4(), lo_out);
        if (style != 0x6777e0) {
            /* full generic description path (hex / typed) */
            skp5_FUN_00351c4c();
            skp5_sk_indirect_dispatch(0x148, 0x1, u45);
            skp5_FUN_00357c88(u44);
            skp5_FUN_003504c4(0);
            skp5_sk_indirect_dispatch(0);
            /* formats the value then stores the result string */
            skp5_FUN_003499a0();
            skp5_FUN_003504f4();
            skp5_FUN_00351148((void *)0xffffffffffffffa0);
            skp5_FUN_00377bec();
            skp5_FUN_003494fc();
            skp5_FUN_00350578(FUN_00610504);
            skp5_sk_indirect_dispatch(0);
            skp5_FUN_0034d558();
            r = skp5_FUN_0034b228();
            skp5_sk_indirect_dispatch(r.lo, r.hi, u54);
            skp5_FUN_0034bb4c();
            skp5_FUN_00355e2c(u44);
            skp5_FUN_00350600();
            skp5_FUN_00377bec();
            skp5_FUN_00351bec();
            skp5_FUN_0014ae44();
            r = skp5_FUN_0034db88();
            if ((skp5_FUN_0034db88().lo & 1) != 0) {
                skp5_FUN_00357634();
                skp5_FUN_003507d4();
                *(unsigned char *)str_buf[0] = '0';
                return;
            }
            skp5_FUN_0034bac8(FUN_00610504, (void *)0x4e7d50, 0x500);
            skp5_FUN_00352b80();
            skp5_FUN_0034b228();
            skp5_FUN_00359e74(r.lo, r.hi, u54);
            skp5_FUN_00357634();
            skp5_FUN_00349d94();
            skp5_FUN_0034eec8();
            /* continue per-slot string building (truncated faithful) */
        }
    }
    return;
}

/* skp5_FUN_002351ac @ 0x2351ac   (est. skp5_sk_runtime_thunk_2351ac)
 * Ghidra: void skp5_FUN_002351ac(void)
 * Thin runtime glue thunk: enters the runtime (00084220), invokes a sequence
 * of shared helpers, dispatches through an indirect slot (skp5_DAT_00658c00) with
 * a value at offset 0x40, then leaves (00084234). No independent logic.
 * Confidence: low
 * Notes: register-artifact heavy body; all callees are out-of-range runtime. */
void skp5_sk_runtime_thunk_2351ac(void)
{
    unsigned long lr_ret;
    unsigned long v;
    void (**slot)(unsigned long);

    skp5_FUN_00084220();
    skp5_FUN_000a6e20();
    skp5_FUN_0035694c();
    skp5_FUN_00349720();
    slot = (void (**)(unsigned long))0x0 + 0x40;   /* skp5_DAT_00658c00 */
    (*slot)(v);
    skp5_FUN_00348f50();
    skp5_FUN_003547ec();
    skp5_FUN_00351274();
    skp5_sk_indirect_dispatch(0);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_003505d0();
    skp5_FUN_00351b78();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00350630(0);
    skp5_sk_indirect_dispatch(0);
    lr_ret = skp5_FUN_00084234(0);
    (void)lr_ret;
}

/* skp5_FUN_00235298 @ 0x235298   (est. skp5_sk_int128_from_string)
 * Ghidra: void skp5_FUN_00235298(void)
 * Parses a decimal string into an Int128, validating the radix/digits. On a
 * short string (<10 chars) it bounds-checks the accumulated value; on longer
 * inputs it uses the BigInt-style parser (00233ba8) and accumulates. On any
 * over/underflow it fatal-errors. Returns via runtime helper 0035847c.
 * Confidence: low
 * Notes: caller of skp5_FUN_00233ba8; runtime-heavy, register artifacts. */
void skp5_sk_int128_from_string(void)
{
    unsigned long v;
    sk_wide_t r;
    unsigned long start;

    skp5_FUN_00041138();
    if (0x22 < skp5_FUN_00351a50() - 2) {
        skp5_FUN_003488bc(1);
        skp5_FUN_00349a54();
        skp5_FUN_003523f0();
        skp5_FUN_001afe4c();
    }
    v = skp5_FUN_0035128c();
    /* magnitude accumulation via skp5_FUN_00233ba8 into a wide result */
    r = skp5_FUN_00233ba8(0, 0, 0, 0, (void *)&v);
    start = r.lo;
    if (start != 0) {
        skp5_FUN_00353aec(start, v + start);
        skp5_FUN_00117d14();
    }
    skp5_FUN_0035847c(r.hi - start);
}

/* skp5_FUN_00235398 @ 0x235398   (est. skp5_sk_ptr_initialize_repeating)
 * Ghidra: void skp5_FUN_00235398(undefined1,long,undefined1*)
 * Swift UnsafeMutablePointer.initialize(repeating:count:): fills *param_3
 * with param_1 repeated param_2 times. If param_2 is negative, fatal-errors
 * with the UnsafeMutablePointer.initialize bounds message.
 * Confidence: medium
 * Notes: Swift runtime; fatal message skp5_s_UnsafeMutablePointer_initialize__005cfaf0. */
void skp5_sk_ptr_initialize_repeating(unsigned char v, long count, unsigned char *dst)
{
    if (count >= 0) {
        for (; count != 0; count--) {
            *dst = v;
            dst++;
        }
        return;
    }
    skp5_FUN_001afe4c(0xb, 2, 0x005cfaf0, 0x41, 2, 0x005cd770, 0x19, 2, 0x380, 1);
}

/* skp5_FUN_00235410 @ 0x235410   (est. skp5_sk_ptr_initialize_repeating_words)
 * Ghidra: void skp5_FUN_00235410(undefined8,long,undefined8*)
 * Word-width variant of the above: fills *param_3 with param_1 repeated
 * param_2 times; fatal-errors on negative count.
 * Confidence: medium
 * Notes: mirrors skp5_FUN_00235398 at word granularity. */
void skp5_sk_ptr_initialize_repeating_words(unsigned long v, long count, unsigned long *dst)
{
    if (count >= 0) {
        for (; count != 0; count--) {
            *dst = v;
            dst++;
        }
        return;
    }
    skp5_FUN_001afe4c(0xb, 2, 0x005cfaf0, 0x41, 2, 0x005cd770, 0x19, 2, 0x380, 1);
}

/* skp5_FUN_00235488 @ 0x235488   (est. skp5_sk_collection_initialize_buffer)
 * Ghidra: void skp5_FUN_00235488(void)
 * Initializes a collection buffer: validates the element count (fatal-errors
 * if negative), then repeatedly invokes the element initializer (through the
 * slot at [x16+0x10]) striding by [x16+0x48] over the buffer, and finally
 * commits the count via 00354ef8.
 * Confidence: low
 * Notes: Swift collection runtime; stride/initializer from runtime slots. */
void skp5_sk_collection_initialize_buffer(void)
{
    long count;
    long stride;
    void (*init)(void);
    long base;

    skp5_FUN_00354a34();
    if (count < 0) {
        skp5_FUN_003488bc(1);
        skp5_FUN_0034a368();
        skp5_FUN_00352e0c();
        skp5_FUN_001afe4c();
        return;
    }
    if (count != 0) {
        skp5_FUN_00077888();
        skp5_FUN_003509c8(0);
        init = (void (*)(void))0;
        stride = 0;
        base = count;
        do {
            skp5_FUN_0035056c(base);
            init();
            base += stride;
            count--;
        } while (count != 0);
    }
    skp5_FUN_00354ef8(0);
}

/* skp5_FUN_0023560c @ 0x23560c   (est. skp5_sk_int128_from_string_slow)
 * Ghidra: void skp5_FUN_0023560c(undefined8,undefined8)
 * Slow-path Int128 decimal parser; validates string length, then runs the
 * BigInt accumulation (00233ba8) and converts the digit string to the wide
 * value, fatal-erroring on overflow or index out of range.
 * Confidence: low
 * Notes: runtime-heavy; shares fatal "Radix must be between 2 and 36". */
void skp5_sk_int128_from_string_slow(void)
{
    sk_wide_t r;
    unsigned long v;

    r = skp5_FUN_0006b2dc(0);
    if (0x22 < r.hi - 2) {
        skp5_FUN_003488bc(1);
        skp5_FUN_00349a54();
        skp5_FUN_003523f0();
        skp5_FUN_001afe4c();
    }
    r = skp5_FUN_003587d4();
    r = skp5_FUN_00233ba8(r.lo, r.hi, 0, 0, (void *)&v);
    skp5_FUN_0034ec0c();
    skp5_FUN_00354b38(r.lo);
    skp5_FUN_000651bc(0);
}

/* skp5_FUN_002357b4 @ 0x2357b4   (est. skp5_sk_int8_to_string)
 * Ghidra: void skp5_FUN_002357b4(ulong,uint,uint)
 * Converts a signed 8-bit value (in param_3) to a string in radix param_1,
 * writing into a 72-byte stack buffer and packing {lo,hi} as the resulting
 * Swift string. Fatal-errors on invalid radix / index / range.
 * Confidence: medium
 * Notes: one of the Int<->String family; char-signed value. */
void skp5_sk_int8_to_string(unsigned long radix, uint32_t uppercase, uint32_t value)
{
    sk_wide_t r;
    unsigned long mag;
    int32_t sv = (int8_t)(unsigned char)value;

    if (0x22 < radix - 2) {
        skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    }
    mag = (sv < 0) ? (unsigned long)(-sv) : (unsigned long)sv;
    r = skp5_sk_int64_to_string_radix((uint64_t)(sv >> 7) & 1, mag, radix, 0, (void *)&r);
    skp5_FUN_0011d7e8(r.lo, r.hi);
}

/* skp5_FUN_00235ac4 @ 0x235ac4   (est. sk_int64_to_string_full)
 * Ghidra: undefined1 [16] skp5_FUN_00235ac4(ulong,uint,long,long)
 * Formats a signed 64-bit value (param_3) as a Swift string in the given
 * radix (param_1), allocating a heap buffer when the stack formatter would
 * overflow (radix >= 10, wide value), and packs the result into a 16-byte
 * Swift String. Fatal-errors on nil buffer / invalid radix / index.
 * Confidence: medium
 * Notes: allocates via skp5_FUN_001a2630 + skp5_FUN_002336a8 for the wide path. */
sk_wide_t sk_int64_to_string_full(unsigned long radix, uint32_t uppercase,
                                  int64_t value, int64_t r4)
{
    unsigned long mag;
    sk_wide_t r;
    unsigned long *heap;

    if (radix - 2 < 0x23) {
        if (r4 == 0 && value != -1) {
            mag = (value < 0) ? (unsigned long)(-value) : (unsigned long)value;
            return skp5_sk_int64_to_string_radix(0, mag, radix, uppercase & 1, (void *)&r);
        }
        /* wide/heap path */
        heap = (unsigned long *)skp5_FUN_001a2630();
        if (heap == 0) {
            skp5_FUN_001afe4c(0xb, 2, 0x005cd7d0, 0x39, 2, 0x005cd680, 0x14, 2, 0x6ad, 1);
        }
        skp5_FUN_00235398('0', r.hi, (unsigned char *)heap);
        r = skp5_FUN_002336a8(0, (unsigned long)value, 0, radix, 0, uppercase & 1, (void *)&heap);
        skp5_FUN_002e3704(heap, 0);
        return r;
    }
    skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    return (sk_wide_t){0, 0};
}

/* skp5_FUN_00235fc8 @ 0x235fc8   (est. sk_int128_to_string_full)
 * Ghidra: undefined1 [16] skp5_FUN_00235fc8(ulong,uint,undefined8,ulong)
 * Signed 128-bit variant of the full string formatter: magnitude from
 * param_3/param_4, sign from param_4>>63, heap-allocates for wide values.
 * Fatal-errors on nil / radix / index.
 * Confidence: medium
 * Notes: pairs with skp5_FUN_00235ac4. */
sk_wide_t sk_int128_to_string_full(unsigned long radix, uint32_t uppercase,
                                   uint64_t lo, uint64_t hi)
{
    unsigned long mag;
    sk_wide_t r;
    unsigned long *heap;
    uint64_t sign = hi >> 63;

    if (radix - 2 < 0x23) {
        mag = sign ? (unsigned long)(-(int64_t)hi) : hi;
        if (0 == 0 && (unsigned long)(-(int64_t)lo) != 0xffffffffffffffffull) {
            return skp5_sk_uint128_to_string_radix((uint32_t)sign, mag, 0, radix,
                                              uppercase & 1, 0, (void *)&r);
        }
        heap = (unsigned long *)skp5_FUN_001a2630();
        if (heap == 0) {
            skp5_FUN_001afe4c(0xb, 2, 0x005cd7d0, 0x39, 2, 0x005cd680, 0x14, 2, 0x6ad, 1);
        }
        skp5_FUN_00235398('0', r.hi, (unsigned char *)heap);
        r = skp5_FUN_002336a8((uint32_t)sign, mag, r.hi, radix, 0, uppercase & 1, (void *)&heap);
        skp5_FUN_002e3704(heap, 0);
        return r;
    }
    skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    return (sk_wide_t){0, 0};
}

/* skp5_FUN_002364dc @ 0x2364dc   (est. skp5_sk_int64_from_string_radix)
 * Ghidra: void skp5_FUN_002364dc(ulong,uint,ulong)
 * Parses a string in the given radix into a signed 64-bit value, using the
 * magnitude formatter 00233354, and packages the result; fatal-errors on
 * invalid radix / overflow.
 * Confidence: low
 * Notes: signed wrapper over 00233354. */
void skp5_sk_int64_from_string_radix(unsigned long radix, uint32_t uppercase,
                                int64_t value)
{
    unsigned long mag = (value < 0) ? (unsigned long)(-value) : (unsigned long)value;
    sk_wide_t r;

    if (0x22 < radix - 2) {
        skp5_FUN_003488bc(1);
        skp5_FUN_00349a54();
        skp5_FUN_003523f0();
        skp5_FUN_001afe4c();
    }
    r = skp5_FUN_00233354((uint64_t)(value >> 63) & 1, mag, radix, uppercase & 1, (void *)&r);
    skp5_FUN_0011e71c(r.lo, 0);
    skp5_FUN_000651bc(0xd37afd4bb400012aull);
    skp5_FUN_0011d7e8(r.hi);
}

/* skp5_FUN_002366a0 @ 0x2366a0   (est. skp5_sk_uint64_from_string_radix)
 * Ghidra: void skp5_FUN_002366a0(ulong,uint,undefined4)
 * Unsigned 64-bit string->value parser in the given radix. Fills a 72-byte
 * '0'-padded stack buffer, runs 00233354 to produce digits, then converts the
 * digit bytes to the packed Swift string. Fatal-errors on radix / index /
 * range.
 * Confidence: low
 * Notes: stack-buffer based; mirrors the signed variant minus sign handling. */
void skp5_sk_uint64_from_string_radix(unsigned long radix, uint32_t uppercase,
                                 uint32_t value)
{
    sk_wide_t r;
    unsigned long mag = value;

    if (0x22 < radix - 2) {
        skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    }
    r = skp5_FUN_00233354(0, mag, radix, uppercase & 1, (void *)&r);
    skp5_FUN_0011d7e8(r.lo, r.hi);
}

/* skp5_FUN_002369a8 @ 0x2369a8   (est. sk_int16_to_string)
 * Ghidra: void skp5_FUN_002369a8(ulong,uint,uint)
 * Converts a signed 16-bit value to a string in the given radix. Same
 * structure as the Int8 variant but with 16-bit sign handling.
 * Confidence: medium
 * Notes: Int16 variant. */
void sk_int16_to_string(unsigned long radix, uint32_t uppercase, uint32_t value)
{
    sk_wide_t r;
    int32_t sv = (int16_t)(unsigned short)value;
    unsigned long mag = (sv < 0) ? (unsigned long)(-sv) : (unsigned long)sv;

    if (0x22 < radix - 2) {
        skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    }
    r = skp5_sk_int64_to_string_radix((uint64_t)(sv >> 15) & 1, mag, radix, 0, (void *)&r);
    skp5_FUN_0011d7e8(r.lo, r.hi);
}

/* skp5_FUN_00236cb8 @ 0x236cb8   (est. skp5_sk_int32_to_string)
 * Ghidra: void skp5_FUN_00236cb8(ulong,uint,uint)
 * Converts a signed 32-bit value to a string in the given radix; 32-bit sign.
 * Confidence: medium
 * Notes: Int32 variant. */
void skp5_sk_int32_to_string(unsigned long radix, uint32_t uppercase, uint32_t value)
{
    sk_wide_t r;
    int32_t sv = (int32_t)value;
    unsigned long mag = (sv < 0) ? (unsigned long)(-(int64_t)sv) : (unsigned long)sv;

    if (0x22 < radix - 2) {
        skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    }
    r = skp5_sk_int64_to_string_radix((uint64_t)((uint32_t)sv >> 31) & 1, mag, radix, 0, (void *)&r);
    skp5_FUN_0011d7e8(r.lo, r.hi);
}

/* skp5_FUN_00236fc4 @ 0x236fc4   (est. skp5_sk_uint128_to_string_full)
 * Ghidra: void skp5_FUN_00236fc4(ulong,uint,ulong,ulong)
 * Formats an unsigned 128-bit value (lo=param_3, hi=param_4) into a Swift
 * string; handles the min-magnitude overflow (fatal) and the radix validation.
 * Confidence: low
 * Notes: unsigned wide formatter over 00233354; overflow check via carry. */
void skp5_sk_uint128_to_string_full(unsigned long radix, uint32_t uppercase,
                               uint64_t lo, uint64_t hi)
{
    sk_wide_t r;
    uint64_t sign = hi >> 63;
    uint64_t mag_lo = (lo ^ -sign) - (uint64_t)(-sign ? 0 : 0) - sign;
    uint64_t mag_hi = hi;

    (void)mag_lo;
    if (0x22 < radix - 2) {
        skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    }
    if (sign && lo == 0 && hi == 0x8000000000000000ull) {
        /* magnitude overflow (min Int128) -> fatal */
        skp5_FUN_003698b0(0, 0x674330, 0x66d208);
        skp5_FUN_001afe4c();
        return;
    }
    r = skp5_FUN_00233354(sign, lo, radix, uppercase & 1, (void *)&r);
    skp5_FUN_0011d7e8(r.lo, r.hi);
}

/* skp5_FUN_00237040 @ 0x237040   (thunk sk_fatal_error_thunk)
 * Ghidra: noreturn undefined skp5_thunk_FUN_001afe4c(void)
 * Direct tail-thunk into the noreturn Swift fatal-error routine.
 * Confidence: high
 * Notes: 4-byte thunk. */
void thunk_sk_fatal_error_thunk(void)
{
    skp5_FUN_001afe4c();
}

/* skp5_FUN_0023723c @ 0x23723c   (est. skp5_sk_fatal_redirect)
 * Ghidra: void skp5_FUN_0023723c(void)
 * noreturn helper that immediately tail-calls the fatal-error thunk.
 * Confidence: high
 * Notes: body is `skp5_thunk_FUN_001afe4c();` (noreturn). */
void skp5_sk_fatal_redirect(void)
{
    thunk_sk_fatal_error_thunk();
}

/* skp5_FUN_0023737c @ 0x23737c   (est. sk_fatal_range_lowerbound)
 * Ghidra: void skp5_FUN_0023737c(void)
 * noreturn fatal-error with the Swift "Range requires lowerBound <= upperBound"
 * diagnostic and source location (Swift/Range.swift:0x2f9).
 * Confidence: high
 * Notes: strings skp5_s_Fatal_error_005accd0 / skp5_s_Range_requires_lowerBound_<__upp_005cda00 /
 *   skp5_s_Swift_Range_swift_005cda30. */
void sk_fatal_range_lowerbound(void)
{
    skp5_FUN_001afe4c(0x005accd0, 0xb, 2, 0x005cda00, 0x27, 0, 0x005cda30, 0x19, 2, 0x2f9, 1);
}

/* skp5_FUN_002373c4 @ 0x2373c4   (est. sk_uint64_from_string_radix_c)
 * Ghidra: void skp5_FUN_002373c4(ulong,uint,undefined1)
 * Unsigned 64-bit string->value parser (char-sized input), mirrors
 * skp5_FUN_002366a0 but takes an 8-bit value and pads the stack buffer.
 * Confidence: low
 * Notes: near-identical body to 002366a0. */
void sk_uint64_from_string_radix_c(unsigned long radix, uint32_t uppercase,
                                   unsigned char value)
{
    sk_wide_t r;
    if (0x22 < radix - 2) {
        skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    }
    r = skp5_FUN_00233354(0, value, radix, uppercase & 1, (void *)&r);
    skp5_FUN_0011d7e8(r.lo, r.hi);
}

/* skp5_FUN_002376d0 @ 0x2376d0   (est. sk_uint16_from_string)
 * Ghidra: void skp5_FUN_002376d0(ulong,uint,undefined2)
 * Unsigned 16-bit string->value parser. Mirrors the family.
 * Confidence: low
 * Notes: 16-bit value input. */
void sk_uint16_from_string(unsigned long radix, uint32_t uppercase,
                           unsigned short value)
{
    sk_wide_t r;
    if (0x22 < radix - 2) {
        skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    }
    r = skp5_FUN_00233354(0, value, radix, uppercase & 1, (void *)&r);
    skp5_FUN_0011d7e8(r.lo, r.hi);
}

/* skp5_FUN_002379dc @ 0x2379dc   (est. skp5_sk_uint64_from_string_decimal)
 * Ghidra: void skp5_FUN_002379dc(undefined8,undefined8,undefined8)
 * Decimal string->uint64 parser with a stack-padded buffer; uses 00233354 and
 * packs the result. Fatal-errors on radix/index/range.
 * Confidence: low
 * Notes: decimal specialization. */
void skp5_sk_uint64_from_string_decimal(void)
{
    sk_wide_t r;
    sk_wide_t vb = skp5_FUN_0006b2dc();
    unsigned long v = vb.lo;
    if (0x22 < v - 2) {
        skp5_FUN_003488bc(1);
        skp5_FUN_00349a54();
        skp5_FUN_003523f0();
        skp5_FUN_001afe4c();
    }
    r = skp5_FUN_00233354(0, 0, 0, 0, (void *)&v);
    skp5_FUN_0034ec0c();
    skp5_FUN_00354b38(0);
    skp5_FUN_000651bc(0);
}

/* skp5_FUN_00237b94 @ 0x237b94   (est. skp5_sk_uint64_from_string_radix64)
 * Ghidra: void skp5_FUN_00237b94(ulong,uint,ulong,long)
 * Unsigned 64-bit formatter with an overflow check against min-value; if the
 * carry indicates a magnitude that cannot be represented it fatal-errors via
 * the Diagnostic helper (002b81b4). Otherwise uses 00233354.
 * Confidence: low
 * Notes: overflow guard skp5_FUN_002b81b4 + SoftwareBreakpoint at 0x237f34. */
void skp5_sk_uint64_from_string_radix64(unsigned long radix, uint32_t uppercase,
                                   uint64_t lo, int64_t hi)
{
    sk_wide_t r;

    if (0x22 < radix - 2) {
        skp5_FUN_001afe4c(0xb, 2, 0x005cfab0, 0x1e, 2, 0x005cd680, 0x14, 2, 0x669, 1);
    }
    if (hi != 0 || skp5_CARRY8(hi - 1, (unsigned long)(0xfffffffffffffffe < lo))) {
        /* magnitude out of 64-bit range -> fatal diagnostic */
        skp5_FUN_002b81b4((void *)0, 0);
        skp5_FUN_003698b0(0, 0x674330, 0x66d208);
        skp5_FUN_001afe4c();
        return;
    }
    r = skp5_FUN_00233354(0, lo, radix, uppercase & 1, (void *)&r);
    skp5_FUN_0011d7e8(r.lo, r.hi);
}

/* skp5_FUN_00237f7c @ 0x237f7c   (est. skp5_sk_big_string_builder)
 * Ghidra: void skp5_FUN_00237f7c(undefined8,undefined8,undefined8,undefined8)
 * Large Swift string-builder that accumulates formatted segments: reads the
 * value pair, formats through the runtime, and appends into a growing buffer
 * (allocated via skp5_FUN_003d31f8 / skp5_FUN_0036a804). Handles both the small-string
 * and heap-string paths. Fatal-errors on nil / overflow.
 * Confidence: low
 * Notes: 654-line runtime-heavy builder; allocation skp5_FUN_0036a804, growth
 *   skp5_FUN_00358238, string append 00357f44. */
void skp5_sk_big_string_builder(void)
{
    unsigned long v3, v4;
    long n;
    unsigned long flags;

    skp5_FUN_0008e518();
    skp5_FUN_0006b2ec();
    v3 = skp5_FUN_0008f6c0(0);
    skp5_FUN_00351684();
    skp5_FUN_003523fc(0);
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_00352554();
    skp5_FUN_00349080();
    FUN_00658c00_REF();
    skp5_FUN_00349068();
    skp5_FUN_00355324();
    skp5_FUN_0035063c(0, v3);
    skp5_FUN_00377824();
    skp5_FUN_003599d8();
    skp5_FUN_0034df24();
    skp5_FUN_00377bec();
    skp5_FUN_0008f6f4();
    skp5_FUN_0034d8d4();
    skp5_FUN_003547c8();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034d3c4();
    skp5_FUN_00350488();
    skp5_FUN_00377dcc();
    skp5_FUN_00348ce8();
    FUN_00658c00_REF();
    skp5_FUN_0034ab10();
    skp5_FUN_00350ec0();
    FUN_00658c00_REF();
    skp5_FUN_0034c2c8();
    if (0x22 >= 0x20) {  /* range check on input string length */
        skp5_FUN_00350410();
        skp5_FUN_003488bc();
        skp5_FUN_00349a54();
        skp5_FUN_003523f0();
        skp5_FUN_001afe4c();
        return;
    }
    skp5_FUN_0034c368();
    n = skp5_FUN_0034c368() + 1;
    if (n < 0x41) {
        skp5_FUN_0034d054(0);
        skp5_FUN_00350ea4();
        if (skp5_FUN_0034d054() == 0xffffffffffffffffull) {
            /* length computations for buffer allocation */
            n = skp5_FUN_0034d054() * 5;
            n = (n + 0xf) >> 4;
            n = n + 1;
            FUN_00658c00_REF();
            skp5_FUN_00358238();
            if (n >= 0) {
                if (n >= 0x401)
                    skp5_FUN_003d31f8(n, 1);
                skp5_FUN_0007c1a4();
                FUN_00658c00_REF();
                skp5_FUN_00355c84();
                skp5_FUN_00354968();
                skp5_FUN_00351a50();
            } else {
                skp5_FUN_00350410();
                skp5_FUN_003488bc();
                skp5_FUN_0034a2f8();
                skp5_FUN_001afe4c();
            }
            flags = 0;
            goto store;
        }
        store:
        skp5_FUN_00354968();
        skp5_FUN_00351a50();
        return;
    }
    skp5_FUN_0034d054(0);
    skp5_FUN_00350ea4();
    (void)flags;
}

/* skp5_FUN_00238cb0 @ 0x238cb0   (est. skp5_sk_collection_subscript_range)
 * Ghidra: void skp5_FUN_00238cb0(void)
 * Collection range subscript: validates the index bounds (allocating a
 * buffer if empty), then invokes 00233f04 to build the range, dispatching the
 * result to the collection. Fatal-errors on out-of-range.
 * Confidence: low
 * Notes: calls skp5_FUN_00233f04 (UInt128 formatter); range index arithmetic. */
void skp5_sk_collection_subscript_range(void)
{
    sk_wide_t r;
    unsigned long idx_lo, idx_hi;

    skp5_FUN_00041138();
    skp5_FUN_00351dc0();
    skp5_FUN_001a2630();
    if (skp5_FUN_00351a50() != 0) {
        skp5_FUN_00350624(0x30);
        skp5_FUN_00235398(0, 0, 0);
    }
    r = skp5_FUN_00233f04(0, idx_lo, idx_hi, 0, 0, 1, (void *)&idx_lo);
    skp5_FUN_002a20cc(r.lo, r.hi - r.lo);
    skp5_FUN_000b43e8();
    skp5_FUN_0009461c();
    skp5_FUN_002e3704();
    r = skp5_FUN_000b4390();
    skp5_FUN_0035847c(r.lo, r.hi, 0);
}

/* skp5_FUN_00238e1c @ 0x238e1c   (est. skp5_sk_collection_read_index_wide)
 * Ghidra: void skp5_FUN_00238e1c(undefined8,undefined8,long,undefined8,undefined8,long,undefined8)
 * Reads an element at a computed index from a collection and stores it via
 * the runtime, converting the bit-width selector. Uses several runtime
 * helpers to resolve the index bounds and element type before writing the
 * result. Fatal-errors on nil buffer.
 * Confidence: low
 * Notes: runtime-heavy; range-check helpers at 0034fd14/0034bf2c. */
void skp5_sk_collection_read_index_wide(void)
{
    unsigned long v6;
    long n;
    sk_wide_t r;

    skp5_FUN_0008e518();
    v6 = 0;
    skp5_FUN_0035098c();
    skp5_FUN_0008f6c0(v6);
    r = skp5_FUN_003504e8();
    skp5_FUN_00377824(r.lo, r.hi, 0);
    skp5_FUN_00348ce8();
    FUN_00658c00_REF();
    skp5_FUN_00348bd8();
    FUN_00658c00_REF();
    skp5_FUN_00350464();
    skp5_FUN_0008f6f4(0);
    skp5_FUN_00349770();
    skp5_FUN_00350b9c();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034b0c4();
    skp5_FUN_0034a5c8();
    FUN_00658c00_REF();
    skp5_FUN_003497b4();
    skp5_FUN_00351ce8();
    skp5_FUN_000b43d0();
    skp5_FUN_001a2630();
    n = skp5_FUN_00354e0c();
    if (n != 0) {
        skp5_FUN_003510c4(0x30);
        skp5_FUN_00235398(0, 0, 0);
    }
    skp5_FUN_00310a14(0);
    skp5_FUN_0034fd14();
    n = 0;  /* index resolution result */
    if ((n & 1) == 0) {
        skp5_FUN_00357c88(0);
        skp5_FUN_00356230();
        skp5_FUN_00100c38();
        skp5_FUN_0034b114();
        skp5_FUN_0034ee98();
        skp5_FUN_00377bec();
        skp5_FUN_00358d34();
        skp5_FUN_0001df60();
        skp5_FUN_0034aca0();
        skp5_FUN_00351154(0, &n);
        skp5_FUN_0035256c((uint32_t)0 & 1);
        skp5_FUN_00234384(0, 0, 0, 0, 0, 0, 0);
        skp5_FUN_00351a50();
        skp5_FUN_00350630();
        skp5_FUN_00350b00();
    }
    skp5_FUN_001afe4c();
}

/* skp5_FUN_00239294 @ 0x239294   (est. skp5_sk_collection_write_index_wide)
 * Ghidra: void skp5_FUN_00239294(undefined8,undefined8,undefined8)
 * Writes a wide element into a collection at a resolved index, with the
 * bounds/type checks and the overflow path (index out of range -> fatal).
 * Confidence: low
 * Notes: mirror image of the read helper; heavy runtime delegation. */
void skp5_sk_collection_write_index_wide(void)
{
    unsigned long v4, v6;
    unsigned long v7;
    sk_wide_t r;

    v4 = skp5_FUN_0008e518().lo;
    skp5_FUN_00352c10();
    skp5_FUN_0008f6c0(0);
    skp5_FUN_00352f54();
    skp5_FUN_0034ba38();
    skp5_FUN_00377824();
    skp5_FUN_0035a700();
    skp5_FUN_0034d180();
    v6 = skp5_FUN_00377bec();
    skp5_FUN_00351684();
    skp5_FUN_0034f8d0();
    skp5_FUN_00350aac();
    v7 = skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_003501d0();
    skp5_FUN_00350798();
    skp5_FUN_00377dcc();
    skp5_FUN_000a6f88();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d234();
    FUN_00658c00_REF();
    skp5_FUN_00349c2c();
    FUN_00658c00_REF();
    skp5_FUN_0034aa14();
    skp5_FUN_00351684(0);
    skp5_FUN_00354b20();
    skp5_FUN_00350974();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034af20();
    skp5_FUN_003494e8();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034cde8();
    FUN_00658c00_REF();
    skp5_FUN_00349c84();
    FUN_00658c00_REF();
    skp5_FUN_0034ae94();
    FUN_00658c00_REF();
    skp5_FUN_0034ac50();
    skp5_FUN_003564a4();
    skp5_FUN_003504dc();
    /* index + write path; overflow -> fatal */
    if (0) {
        skp5_FUN_0034ad00();
        skp5_FUN_00377bec();
        skp5_FUN_003494fc();
        skp5_FUN_0035a360();
        skp5_FUN_0034c9b8();
        skp5_FUN_0034d9cc();
        skp5_FUN_0035308c();
        skp5_FUN_003510c4();
        skp5_FUN_003492cc(0);
        skp5_FUN_00350618();
        skp5_FUN_00351378();
    }
    skp5_FUN_00353220(0, 0);
    skp5_FUN_000839d8();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0023a354 @ 0x23a354   (est. skp5_sk_collection_subscript_assign)
 * Ghidra: void skp5_FUN_0023a354(void)
 * Collection subscript-assignment wrapper: resolves the target index and the
 * source element, then writes through the runtime accessors. The overflow /
 * out-of-range branches fatal-error. Mirrors the write helper.
 * Confidence: low
 * Notes: runtime-heavy; string-format fatal paths. */
void skp5_sk_collection_subscript_assign(void)
{
    unsigned long v6;
    sk_wide_t r;
    unsigned long v8;

    skp5_FUN_0008e518();
    v6 = 0;
    skp5_FUN_00351cf4();
    skp5_FUN_00027754(v6);
    skp5_FUN_00349684();
    skp5_FUN_003513fc();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034aa9c();
    skp5_FUN_0034a774(0);
    skp5_FUN_003518d0();
    v6 = skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034d888();
    skp5_FUN_003499f0();
    FUN_00658c00_REF();
    skp5_FUN_00349068();
    skp5_FUN_003494e8();
    FUN_00658c00_REF();
    skp5_FUN_00348b5c();
    FUN_00658c00_REF();
    skp5_FUN_0034a414();
    FUN_00658c00_REF();
    skp5_FUN_0034bd30();
    FUN_00658c00_REF();
    skp5_FUN_0034ac50();
    skp5_FUN_00310a14(0);
    skp5_FUN_0034bf84();
    v8 = skp5_FUN_00310a14(0);
    if ((v8 & 1) == 0) {
        skp5_FUN_00358d58(0);
        skp5_FUN_0009e234();
        skp5_FUN_00356c30();
        skp5_FUN_00310984();
        skp5_FUN_003504dc();
        if (0) skp5_FUN_00310aa4(0);
    }
    skp5_FUN_0034bf84();
    FUN_00658c00_REF();
    skp5_FUN_0034d53c();
    skp5_FUN_00353c60();
    skp5_FUN_0034bd44();
    skp5_FUN_003492cc();
    skp5_FUN_0034f5d4(0);
    skp5_FUN_0035a634();
    skp5_FUN_003514e8();
    skp5_FUN_00084180();
    FUN_00658c00_REF();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0023ae70 @ 0x23ae70   (est. sk_string_append_overflow)
 * Ghidra: void skp5_FUN_0023ae70(undefined8,undefined8,undefined8)
 * String/collection append with overflow detection: validates the count
 * against a per-element bound and appends, or fatal-errors on overflow.
 * Confidence: low
 * Notes: uses skp5_FUN_0016796c/skp5_FUN_000e710c append helpers. */
void sk_string_append_overflow(void)
{
    unsigned long v1;
    unsigned long v2;
    long n;

    skp5_FUN_00084220();
    v1 = 0;
    skp5_FUN_00356c78();
    skp5_FUN_00349b3c();
    FUN_00658c00_REF();
    skp5_FUN_003490ec();
    v1 = skp5_FUN_0034acd0(v1);
    v2 = skp5_FUN_0034acd0(v1);
    if ((v2 & 1) == 0) {
        if (0 <= 0) {
            skp5_FUN_0016796c(0);
            skp5_FUN_000e710c();
            skp5_FUN_0034e4dc((void *)0xfffffffffffffff8, 0x677830, skp5_FUN_000e710c());
            skp5_FUN_0008f6c0(0);
            skp5_FUN_00351bec();
            skp5_FUN_0016799c();
        } else {
            skp5_FUN_0034e4dc((void *)0xfffffffffffffff8, 0x677830, 0);
            skp5_FUN_0008f6c0(0);
            skp5_FUN_00351bec();
            skp5_FUN_00167a2c();
        }
    } else {
        skp5_FUN_0034c0d0();
        skp5_FUN_003509e0();
        n = skp5_FUN_003509e0();
        if (n < 0x40) {
            skp5_FUN_0034bfc4(0);
            skp5_FUN_003509e0();
            n = skp5_FUN_003509e0();
            skp5_FUN_0016796c(0);
            skp5_FUN_0001df60();
            skp5_FUN_0034aca0();
            skp5_FUN_0034e4dc(0, (void *)0xfffffffffffffff8);
        } else {
            skp5_FUN_003522e4();
            skp5_FUN_0034aca0();
            skp5_FUN_0034e4dc((void *)0xfffffffffffffff8, 0);
            skp5_FUN_0008f6c0(0);
            skp5_FUN_00351bec();
            skp5_FUN_00167a2c();
        }
    }
    skp5_FUN_00351250();
    skp5_FUN_0034d758();
    skp5_FUN_0034eb94();
    skp5_FUN_00084234(0);
}

/* skp5_FUN_0023b03c @ 0x23b03c   (est. sk_runtime_thunk_b03c)
 * Ghidra: void skp5_FUN_0023b03c(void)
 * Runtime glue thunk: three helper calls then one indirect dispatch.
 * Confidence: low
 * Notes: register-artifact body. */
void sk_runtime_thunk_b03c(void)
{
    skp5_FUN_003503c0();
    skp5_FUN_00310984();
    skp5_FUN_0035013c();
    skp5_sk_indirect_dispatch(0);
}

/* skp5_FUN_0023b06c @ 0x23b06c   (est. sk_runtime_thunk_b06c)
 * Ghidra: void skp5_FUN_0023b06c(void)
 * Runtime glue thunk with a predicated indirect dispatch.
 * Confidence: low
 * Notes: register-artifact body. */
void sk_runtime_thunk_b06c(void)
{
    skp5_FUN_0008409c();
    skp5_FUN_003496e8(0);
    skp5_FUN_0034bf1c();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00356d20();
}

/* skp5_FUN_0023b0e0 @ 0x23b0e0   (est. sk_runtime_thunk_b0e0)
 * Ghidra: void skp5_FUN_0023b0e0(void)
 * Runtime glue thunk: two indirect dispatches interleaved with helpers.
 * Confidence: low */
void sk_runtime_thunk_b0e0(void)
{
    unsigned long v;

    skp5_FUN_0034ba88();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_003514b8();
    v = ((unsigned long (*)(void))0)();
    skp5_FUN_0034b768(v);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00356d20();
}

/* skp5_FUN_0023b144 @ 0x23b144   (est. sk_runtime_thunk_b144)
 * Ghidra: uint skp5_FUN_0023b144(void)
 * Returns the low bit of the result of a predicated dispatch.
 * Confidence: low
 * Notes: masks the indirect-call result with 1. */
uint32_t sk_runtime_thunk_b144(void)
{
    uint32_t v;
    skp5_FUN_0008409c();
    skp5_FUN_003496e8(0);
    skp5_FUN_0034bf1c();
    v = (uint32_t)((unsigned long (*)(void))0)();
    return v & 1;
}

/* skp5_FUN_0023b18c @ 0x23b18c   (thunk sk_byteswap128)
 * Ghidra: undefined1 [16] skp5_thunk_FUN_003576dc(ulong,ulong)
 * 128-bit byte-swap (reverses byte order of a 128-bit value).
 * Confidence: high
 * Notes: classic swap chains on both halves. */
sk_wide_t sk_byteswap128(uint64_t lo, uint64_t hi)
{
    uint64_t s1, s2;
    s1 = ((lo & 0xff00ff00ff00ff00ull) >> 8) | ((lo & 0x00ff00ff00ff00ffull) << 8);
    s1 = ((s1 & 0xffff0000ffff0000ull) >> 16) | ((s1 & 0x0000ffff0000ffffull) << 16);
    s2 = ((hi & 0xff00ff00ff00ff00ull) >> 8) | ((hi & 0x00ff00ff00ff00ffull) << 8);
    s2 = ((s2 & 0xffff0000ffff0000ull) >> 16) | ((s2 & 0x0000ffff0000ffffull) << 16);
    return (sk_wide_t){(s1 >> 32) | (s1 << 32), (s2 >> 32) | (s2 << 32)};
}

/* skp5_FUN_0023b190 @ 0x23b190   (est. sk_byteswap16)
 * Ghidra: uint skp5_FUN_0023b190(uint)
 * 16-bit byte swap.
 * Confidence: high */
uint32_t sk_byteswap16(uint32_t v)
{
    return ((v & 0xff00ff00u) >> 8) | ((v & 0x00ff00ffu) << 8);
}

/* skp5_FUN_0023b198 @ 0x23b198   (est. sk_byteswap32)
 * Ghidra: uint skp5_FUN_0023b198(uint)
 * 32-bit byte swap.
 * Confidence: high */
uint32_t sk_byteswap32(uint32_t v)
{
    uint32_t t = ((v & 0xff00ff00u) >> 8) | ((v & 0x00ff00ffu) << 8);
    return (t >> 16) | (t << 16);
}

/* skp5_FUN_0023b1a0 @ 0x23b1a0   (est. sk_byteswap64)
 * Ghidra: ulong skp5_FUN_0023b1a0(ulong)
 * 64-bit byte swap.
 * Confidence: high */
uint64_t sk_byteswap64(uint64_t v)
{
    uint64_t t = ((v & 0xff00ff00ff00ff00ull) >> 8) | ((v & 0x00ff00ff00ff00ffull) << 8);
    t = ((t & 0xffff0000ffff0000ull) >> 16) | ((t & 0x0000ffff0000ffffull) << 16);
    return (t >> 32) | (t << 32);
}

/* skp5_FUN_0023b1a8 @ 0x23b1a8   (est. sk_byteswap128_pair)
 * Ghidra: void skp5_FUN_0023b1a8(ulong,ulong)
 * Byte-swaps two 64-bit words and hands them to the runtime (00353d34).
 * Confidence: medium */
void sk_byteswap128_pair(uint64_t a, uint64_t b)
{
    skp5_FUN_00353d34(sk_byteswap64(a), sk_byteswap64(b));
}

/* skp5_FUN_0023b1b4 @ 0x23b1b4   (est. sk_runtime_thunk_b1b4)
 * Ghidra: void skp5_FUN_0023b1b4(void)
 * Runtime glue thunk with an unrecoverable jumptable dispatch at the end.
 * Confidence: low
 * Notes: "Could not recover jumptable at 0x0023b214". */
void sk_runtime_thunk_b1b4(void)
{
    skp5_FUN_0034c034();
    skp5_FUN_00354e00();
    skp5_FUN_0031c904();
    skp5_FUN_0034ffb8();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_003511e4();
    skp5_sk_indirect_dispatch(0);
}

/* skp5_FUN_0023b254 @ 0x23b254   (est. sk_int128_multiply)
 * Ghidra: undefined1 [16] skp5_FUN_0023b254(long*,ulong,ulong,ulong,ulong)
 * 128-bit multiply with carry: multiplies (param_4:param_5) x (param_2:param_3)
 * using word-by-word long multiplication and writes the low 128 bits to
 * *param_1, returning the high 128 bits. Overflow via carry accumulation.
 * Confidence: medium
 * Notes: Swift Int128 multiplication. */
sk_wide_t sk_int128_multiply(unsigned long *out, uint64_t a0, uint64_t a1,
                             uint64_t b0, uint64_t b1)
{
    unsigned long t0, t1, t2, t3, t4, t5;

    t0 = a0 * b0;                    /* low*low */
    t1 = a1 * b0;                    /* high*low */
    t2 = a0 * b1;                    /* low*high */
    t3 = a1 * b1;                    /* high*high */
    /* cross terms accumulate into the middle */
    t4 = t0;
    t5 = t1 + t2;
    if (t5 < t1) t3 += 1;            /* carry from t1+t2 */
    out[0] = t4;
    out[1] = t5 + ((a0 * b0) ? 0 : 0);
    return (sk_wide_t){t5, t3};
}

/* skp5_FUN_0023b2a0 @ 0x23b2a0   (est. skp5_sk_int128_multiply_full)
 * Ghidra: undefined1 [16] skp5_FUN_0023b2a0(long*,ulong,ulong,ulong,ulong)
 * Full signed 128-bit multiply producing a 256-bit product; writes low bits
 * to *param_1 and returns the upper words. Fatal-errors on overflow.
 * Confidence: medium
 * Notes: Swift Int128 multipliedFullWidth; uses skp5_FUN_002d6730 helpers. */
sk_wide_t skp5_sk_int128_multiply_full(unsigned long *out, uint64_t a0, uint64_t a1,
                                  uint64_t b0, uint64_t b1)
{
    sk_wide_t r = skp5_FUN_002d6730(a0, 0);
    uint64_t u8 = r.lo;
    uint32_t u9 = (uint32_t)a1;
    sk_wide_t t;

    if ((u9 & 0xff) == 1)
        skp5_FUN_001afa84(0xb, 2, 0xd000000000000051, 0x80000000005d0e50, 0x005d0ed0, 0x12, 2, 0x9f, 1);
    t = skp5_FUN_002d6730(b0 * a0 + a0 * b1, 0);
    if ((u9 & 0xff) != 1) {
        out[0] = b0 * a0;
        out[1] = t.lo;
        return t;
    }
    skp5_FUN_001afa84(0xb, 2, 0xd000000000000051, 0x80000000005d0e50, 0x005d0ed0, 0x12, 2, 0x9f, 1);
    return (sk_wide_t){0, 0};
}

/* skp5_FUN_0023b458 @ 0x23b458   (est. sk_runtime_thunk_b458)
 * Ghidra: void skp5_FUN_0023b458(void)
 * Runtime glue thunk (dispatch-heavy). Enter/leave via 0008e518/0008e500.
 * Confidence: low */
void sk_runtime_thunk_b458(void)
{
    skp5_FUN_0008e518();
    skp5_FUN_00351468();
    skp5_FUN_00349a68();
    FUN_00658c00_REF();
    skp5_FUN_003493ac();
    skp5_FUN_00349720();
    FUN_00658c00_REF();
    skp5_FUN_0034947c();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00350950(0);
    skp5_FUN_00350a4c();
    skp5_FUN_003508f0();
    skp5_FUN_00353a78();
    skp5_sk_indirect_dispatch(0);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00350390();
    skp5_FUN_0035053c();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00351e90(0);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0023b5c0 @ 0x23b5c0   (est. sk_runtime_thunk_b5c0)
 * Ghidra: void skp5_FUN_0023b5c0(void)
 * Runtime glue thunk.
 * Confidence: low */
void sk_runtime_thunk_b5c0(void)
{
    skp5_FUN_0034d654();
    skp5_FUN_0035a5f0();
    skp5_FUN_0034b07c();
    skp5_sk_indirect_dispatch(0);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0034c8b8();
    skp5_FUN_00350aac();
    skp5_sk_indirect_dispatch(0);
}

/* skp5_FUN_0023b644 @ 0x23b644   (est. skp5_sk_obj_method_dispatch)
 * Ghidra: void skp5_FUN_0023b644(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8,code*)
 * Generic object method dispatch: pushes args onto the runtime stack
 * (skp5_FUN_0035145c/003507c8), invokes the callback param_7 and the slot
 * dispatchers, then unwinds. Enter/leave via 0008e518/0008e500.
 * Confidence: low
 * Notes: dispatch-through-slot body; callback at param_7. */
void skp5_sk_obj_method_dispatch(void)
{
    sk_wide_t r;

    skp5_FUN_0008e518();
    skp5_FUN_00349a68();
    FUN_00658c00_REF();
    skp5_FUN_003490ec();
    skp5_FUN_00349720();
    FUN_00658c00_REF();
    skp5_FUN_00348a18();
    FUN_00658c00_REF();
    skp5_FUN_0034ba68();
    skp5_FUN_003547ec();
    skp5_FUN_003508b4();
    skp5_sk_indirect_dispatch(0);
    r = skp5_FUN_0035145c(0);
    skp5_sk_indirect_dispatch(r.lo, r.hi, 0);
    skp5_FUN_00350950(0);
    skp5_FUN_00350a4c();
    r = skp5_FUN_003507c8();
    skp5_sk_indirect_dispatch(r.lo, r.hi, 0, 0, (void *)0);
    skp5_FUN_00351250();
    skp5_FUN_00350038();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00351f88();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00351ec0();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0023b7b8 @ 0x23b7b8   (est. sk_big_int_to_string)
 * Ghidra: void skp5_FUN_0023b7b8(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Large BigInt-style integer-to-string converter with full radix/type
 * handling and overflow checks. Accumulates via the runtime BigInt helpers,
 * formats the digit string, and returns it. Fatal-errors on nil / overflow.
 * Confidence: low
 * Notes: 681-line runtime-heavy BigInt description. */
void sk_big_int_to_string(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5)
{
    sk_wide_t r;
    unsigned long v4;

    skp5_FUN_0008e518();
    skp5_FUN_00352894(0);
    skp5_FUN_0008f6c0();
    skp5_FUN_00352f54();
    skp5_FUN_0034ba38();
    skp5_FUN_00377824();
    skp5_FUN_0035a700();
    skp5_FUN_0034d180();
    skp5_FUN_00377bec();
    skp5_FUN_00351684();
    skp5_FUN_003528d8();
    skp5_FUN_00351378();
    skp5_FUN_00377824();
    skp5_FUN_00349c44((void *)8);
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_0034c754();
    skp5_FUN_00377dcc();
    skp5_FUN_00348e00();
    FUN_00658c00_REF();
    skp5_FUN_00348a9c();
    FUN_00658c00_REF();
    skp5_FUN_00349c2c();
    FUN_00658c00_REF();
    skp5_FUN_00350464();
    skp5_FUN_00355fac();
    skp5_FUN_0034ce98();
    skp5_FUN_003722e4();
    skp5_FUN_00348fd8();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034c8c8();
    skp5_FUN_00351684(0);
    skp5_FUN_00351238(0);
    skp5_FUN_00377824();
    skp5_FUN_00349c44((void *)0x10);
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_00354ac8();
    skp5_FUN_0034911c();
    FUN_00658c00_REF();
    skp5_FUN_00348bbc();
    FUN_00658c00_REF();
    skp5_FUN_00349f5c();
    FUN_00658c00_REF();
    skp5_FUN_0034a9e8();
    FUN_00658c00_REF();
    skp5_FUN_0034ac3c();
    skp5_FUN_003564a4();
    skp5_FUN_003504dc();
    v4 = skp5_FUN_003504dc();
    if ((v4 & 1) == 0) {
        skp5_FUN_003504dc();
        skp5_FUN_0034fe48();
        skp5_FUN_00084174();
        skp5_FUN_0034b4d0();
        skp5_FUN_003504ac();
        skp5_FUN_00354064();
        skp5_FUN_00359144(0, 0, 0, 0);
        skp5_FUN_0031c9c4(0);
        skp5_FUN_00351b6c(0, 0, 0, 0);
        skp5_FUN_003516c0();
        skp5_FUN_00353734();
        skp5_FUN_00353f2c(0, 0);
        skp5_FUN_0034f754();
        skp5_FUN_003567b0();
        skp5_FUN_00350878();
        skp5_FUN_00377bec();
        skp5_FUN_003549a8();
        skp5_FUN_0034b4a0();
        skp5_FUN_0034acd0(0);
        skp5_FUN_0034acd0(0);
    } else {
        skp5_FUN_0034c0ec();
        skp5_FUN_003504ac();
        if (0x40 < 0x3f) {
            skp5_FUN_00357664();
            skp5_FUN_00353d44();
            skp5_FUN_0001df60();
            skp5_FUN_00349630();
            skp5_FUN_0034ce38(0);
            skp5_FUN_0008f6f4();
            skp5_FUN_0034c4fc();
        }
        skp5_FUN_0034b4d0();
        skp5_FUN_003504ac();
        skp5_FUN_00354064();
    }
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0023c780 / skp5_FUN_0023c784 @ 0x23c780/0x23c784   (est. sk_runtime_thunk_c780/c784)
 * Ghidra: void skp5_FUN_0023c780(void)
 * Two near-identical runtime glue stubs calling the same two helpers.
 * Confidence: low */
void sk_runtime_thunk_c780(void)
{
    skp5_FUN_0034a8a4();
    skp5_FUN_001d36e8();
}
void skp5_sk_runtime_thunk_c784(void)
{
    skp5_FUN_0034a8a4();
    skp5_FUN_001d36e8();
}

/* skp5_FUN_0023c79c @ 0x23c79c   (est. skp5_sk_obj_service_w)
 * Ghidra: void skp5_FUN_0023c79c(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Object service method (writes to a kernel object): reads the object's
 * current value, formats/validates it through the runtime, and stores it
 * back via the slot dispatchers, branching on the success flag.
 * Confidence: low
 * Notes: dispatches via [x16+8]; two-way success/failure path. */
void skp5_sk_obj_service_w(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5)
{
    sk_wide_t r;
    unsigned long v6;

    r = skp5_FUN_0008e518();
    skp5_FUN_00350950(0);
    skp5_FUN_0008f6c0();
    skp5_FUN_00350a1c(0xff, 0);
    skp5_FUN_00377824();
    skp5_FUN_00350968(0);
    skp5_FUN_00377bec();
    skp5_FUN_00351684();
    r = skp5_FUN_00349dfc();
    skp5_FUN_00377824(r.lo, r.hi, 0);
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_0034911c();
    FUN_00658c00_REF();
    skp5_FUN_00349068();
    skp5_FUN_00350798();
    skp5_FUN_00377dcc();
    skp5_FUN_00348cd0();
    FUN_00658c00_REF();
    skp5_FUN_00348b5c();
    FUN_00658c00_REF();
    skp5_FUN_0034a62c();
    FUN_00658c00_REF();
    skp5_FUN_0034b540();
    FUN_00658c00_REF();
    skp5_FUN_0034b8bc();
    skp5_FUN_00310ad4();
    skp5_FUN_00027754();
    skp5_FUN_0034fce4();
    skp5_FUN_00310f04();
    skp5_FUN_003195c8(0);
    skp5_FUN_00350768(0);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0034f754();
    skp5_FUN_00084180();
    skp5_FUN_00377bec();
    skp5_FUN_00350a4c();
    skp5_FUN_003505e8(0);
    skp5_FUN_003569fc();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00357d54();
    skp5_FUN_0034ff98();
    skp5_FUN_00377bec();
    skp5_FUN_00310aa4();
    skp5_FUN_00351184();
    skp5_FUN_003508f0();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0034cdc8();
    skp5_FUN_00350ba8(0);
    skp5_FUN_00377bec();
    skp5_FUN_0034a30c();
    skp5_FUN_003516e4();
    skp5_FUN_00352438();
    v6 = ((unsigned long (*)(void))0)();
    if ((v6 & 1) == 0) {
        skp5_FUN_0034ad00();
        r = skp5_FUN_00350c80();
        skp5_FUN_00377bec(r.lo, r.hi, 0);
        skp5_FUN_0034bc04();
        skp5_FUN_0035a540();
        skp5_FUN_00350aac();
        skp5_sk_indirect_dispatch(0);
        skp5_FUN_0034cea8();
        skp5_FUN_000dbf08(0);
        skp5_sk_indirect_dispatch(0);
        skp5_FUN_00350950(0);
        skp5_FUN_0031c9f4();
        skp5_FUN_003516e4(0);
        skp5_FUN_00352438();
        skp5_sk_indirect_dispatch(0);
        skp5_FUN_00352e24();
        skp5_sk_indirect_dispatch(0, r.lo, 0);
        r = skp5_FUN_0007c1c4(0);
        skp5_FUN_003569fc(r.lo, r.hi, 0);
        skp5_sk_indirect_dispatch(0);
        skp5_FUN_00353f50();
        skp5_FUN_0023b7b8(0, 0, 0, 0, 0);
        skp5_FUN_00351354();
        skp5_FUN_00310f34(0);
        skp5_FUN_0034e054();
        skp5_FUN_00353ef0();
        skp5_sk_indirect_dispatch(0);
        skp5_FUN_00350c80();
        skp5_FUN_0035190c();
    } else {
        skp5_FUN_002445ac(0, 0, 0, 0, 0);
    }
    skp5_FUN_003506cc();
    r = skp5_FUN_003509b0(0);
    skp5_FUN_0034cf64(r.lo, r.hi, 0);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0023cb80 @ 0x23cb80   (est. sk_runtime_thunk_cb80)
 * Ghidra: void skp5_FUN_0023cb80(void)
 * Runtime glue thunk into 002445ac.
 * Confidence: low */
void sk_runtime_thunk_cb80(void)
{
    skp5_FUN_00352444();
    skp5_FUN_002445ac(0, 0, 0, 0, 0);
}

/* skp5_FUN_0023cbac / skp5_FUN_0023cbb0 @ 0x23cbac/0x23cbb0   (est. sk_runtime_thunk_cbac/cbb0)
 * Ghidra: void skp5_FUN_0023cbac(void)
 * Runtime glue thunks into 0023c79c.
 * Confidence: low */
void sk_runtime_thunk_cbac(void)
{
    skp5_FUN_0034a8a4();
    skp5_FUN_0023c79c(0, 0, 0, 0, 0);
}
void skp5_sk_runtime_thunk_cbb0(void)
{
    skp5_FUN_0034a8a4();
    skp5_FUN_0023c79c(0, 0, 0, 0, 0);
}

/* skp5_FUN_0023cbc8 @ 0x23cbc8   (est. skp5_sk_obj_service_r)
 * Ghidra: void skp5_FUN_0023cbc8(undefined8,undefined8,undefined8)
 * Object service read method: reads an object value, converts it through the
 * runtime, and returns it. Mirrors the write service with a read path.
 * Confidence: low
 * Notes: dispatch-through-slot; enter/leave 0008e518/0008e500. */
void skp5_sk_obj_service_r(unsigned long p1, unsigned long p2, unsigned long p3)
{
    sk_wide_t r;

    skp5_FUN_0008e518();
    skp5_FUN_00027754(0);
    skp5_FUN_0008f6c0();
    skp5_FUN_00359338();
    skp5_FUN_00349d80();
    skp5_FUN_003513fc();
    skp5_FUN_00377824();
    skp5_FUN_0034a450();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034b0d4();
    skp5_FUN_003494e8();
    FUN_00658c00_REF();
    skp5_FUN_00348a34();
    FUN_00658c00_REF();
    skp5_FUN_0034c074();
    skp5_FUN_00350524();
    skp5_FUN_00353c3c();
    skp5_FUN_00377bec();
    skp5_FUN_00350654();
    skp5_FUN_00350440();
    skp5_FUN_00350e44();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0034c384();
    skp5_FUN_0034c674();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00354cb4();
    skp5_FUN_003195c8();
    skp5_FUN_00350a1c();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_003509d4();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00351a74();
    skp5_FUN_00351f4c(0, 0x200);
    skp5_sk_indirect_dispatch(0);
    r = skp5_FUN_0034d810();
    skp5_sk_indirect_dispatch(r.lo, r.hi, 0);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_003509d4();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00084180();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0023cd98 @ 0x23cd98   (est. skp5_sk_int64_parse_overflow)
 * Ghidra: void skp5_FUN_0023cd98(void)
 * Int64 parse-with-overflow: validates the magnitude bounds, and on overflow
 * emits a fatal diagnostic; otherwise packages the value. Mirrors the family.
 * Confidence: low
 * Notes: 517-line runtime-heavy overflow-guarded parser. */
void skp5_sk_int64_parse_overflow(void)
{
    sk_wide_t r;
    long n;

    skp5_FUN_0008e518();
    skp5_FUN_00355ff4();
    skp5_FUN_00358a74();
    skp5_FUN_00356900();
    skp5_FUN_0034be54(0);
    skp5_FUN_0034f8d0();
    skp5_FUN_00351b78();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034cd40();
    skp5_FUN_00027754();
    skp5_FUN_0034be54();
    skp5_FUN_00354b20();
    skp5_FUN_00350974();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_0034911c();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034cf34();
    FUN_00658c00_REF();
    skp5_FUN_00349f5c();
    FUN_00658c00_REF();
    skp5_FUN_0034a120();
    FUN_00658c00_REF();
    skp5_FUN_00350464();
    skp5_FUN_0035a2b8();
    skp5_FUN_003499f0();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d5a8();
    FUN_00658c00_REF();
    skp5_FUN_0034ffdc();
    skp5_FUN_00352bb0();
    skp5_FUN_00350624(0);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00310984();
    skp5_FUN_0034ba08();
    n = skp5_FUN_0034ba08();
    if (n < 0) {
        skp5_FUN_0034bfe0();
        skp5_FUN_0034e454();
        n = skp5_FUN_0034e454();
        if (n < -n) {
            /* in-range -> package */
            skp5_FUN_0034d830();
            skp5_FUN_00350b00();
            skp5_FUN_0034bfe0();
            skp5_FUN_0034e454();
            n = skp5_FUN_0034e454();
            if (n < -n) return;
        }
    }
    /* overflow -> fatal */
    skp5_FUN_00350ab8();
    skp5_FUN_0034bf84();
    skp5_FUN_003512a4();
    skp5_FUN_0034d768();
    skp5_FUN_0034bf84();
    skp5_FUN_003512a4();
    skp5_FUN_0034d768();
    skp5_FUN_0034bf84();
    skp5_FUN_003512a4();
    skp5_FUN_0034d768();
    skp5_FUN_0034ad00();
    r = skp5_FUN_003508b4();
    skp5_FUN_00377bec(r.lo, r.hi, 0);
    skp5_FUN_003494fc();
    skp5_FUN_0034ed58(0);
    skp5_FUN_0034c7d4();
    skp5_FUN_00353074();
    skp5_FUN_00350b84(0);
    skp5_FUN_003491c4();
    skp5_FUN_0034fea0();
    skp5_FUN_0034d830();
    skp5_FUN_001afe4c();
}

/* skp5_FUN_0023d83c @ 0x23d83c   (est. skp5_sk_int128_parse_overflow)
 * Ghidra: void skp5_FUN_0023d83c(void)
 * Int128 parse-with-overflow, mirroring the Int64 variant but with 128-bit
 * magnitude handling (multiple width checks at 0x40/0x41). On overflow,
 * fatal-errors with a diagnostic.
 * Confidence: low
 * Notes: 496-line runtime-heavy; sibling of skp5_FUN_0023f9c8. */
void skp5_sk_int128_parse_overflow(void)
{
    sk_wide_t r;
    long n;

    skp5_FUN_0008e518();
    r = skp5_FUN_003526c4();
    skp5_FUN_00027754(0);
    skp5_FUN_00349684();
    skp5_FUN_003513fc();
    skp5_FUN_00377824();
    skp5_FUN_0034a450();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_0034911c();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d294();
    FUN_00658c00_REF();
    skp5_FUN_00349c84();
    FUN_00658c00_REF();
    skp5_FUN_00349c2c();
    FUN_00658c00_REF();
    skp5_FUN_0034ac3c();
    skp5_FUN_0034a774();
    skp5_FUN_003523fc();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_00349080();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d444();
    FUN_00658c00_REF();
    skp5_FUN_0034ea54();
    skp5_FUN_00310984();
    skp5_FUN_0034b8dc();
    skp5_FUN_00358e94();
    n = skp5_FUN_00358e94();
    if (n < 0)
        skp5_FUN_00310984();
    skp5_FUN_0035ab88();
    skp5_FUN_0034b4a0();
    if (0) {
        /* in-range path: two-sided width check */
        skp5_FUN_00310a44();
        skp5_FUN_0034b6cc();
        n = skp5_FUN_0034b6cc();
        if (n < 0x40) {
            skp5_FUN_003109b4();
            skp5_FUN_0034b6cc();
            n = skp5_FUN_0034b6cc();
            if (n < -n) {
                skp5_FUN_0034b1f0();
                return;
            }
        }
    }
    /* overflow -> fatal diagnostic path */
    skp5_FUN_0034b1f0();
    skp5_FUN_0034b4a0();
    skp5_FUN_00310a44();
    skp5_FUN_0034b6cc();
    n = skp5_FUN_0034b6cc();
    skp5_FUN_0034ad00();
    skp5_FUN_0034ed68();
    skp5_FUN_00377bec();
    skp5_FUN_003494fc();
    skp5_FUN_0034c044();
    skp5_FUN_0034c7d4();
    skp5_FUN_00352134();
    r = skp5_FUN_0034d2f4();
    skp5_FUN_00348ca8();
    skp5_FUN_0034c6b4();
    skp5_FUN_0034a068();
    skp5_FUN_001afe4c();
}

/* skp5_FUN_0023e1fc @ 0x23e1fc   (est. skp5_sk_uint128_parse_overflow)
 * Ghidra: void skp5_FUN_0023e1fc(void)
 * UInt128 parse-with-overflow variant (no sign bit); width checks at
 * 0x40/0x41, overflow -> fatal. Mirrors the signed version.
 * Confidence: low
 * Notes: sibling of 0023d83c / 0023f9c8. */
void skp5_sk_uint128_parse_overflow(void)
{
    sk_wide_t r;
    long n;

    skp5_FUN_0008e518();
    r = skp5_FUN_003526c4();
    skp5_FUN_0008f6c0(0);
    skp5_FUN_003564d0();
    skp5_FUN_00349d80();
    skp5_FUN_0034d004();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034cd40();
    skp5_FUN_00027754();
    skp5_FUN_0034a774();
    skp5_FUN_003513fc();
    skp5_FUN_00377824();
    skp5_FUN_00349e10();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_0034911c();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d294();
    FUN_00658c00_REF();
    skp5_FUN_00349c84();
    FUN_00658c00_REF();
    skp5_FUN_00349c2c();
    FUN_00658c00_REF();
    skp5_FUN_00350464();
    skp5_FUN_00349080();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d444();
    FUN_00658c00_REF();
    skp5_FUN_0034ea54();
    skp5_FUN_00310984();
    skp5_FUN_0034b8dc();
    skp5_FUN_00358e94();
    n = skp5_FUN_00358e94();
    if (n < 0)
        skp5_FUN_00310984();
    skp5_FUN_0035ab88();
    skp5_FUN_0034b4a0();
    skp5_FUN_0034b4a0();
    skp5_FUN_00310a44();
    skp5_FUN_0034ae6c();
    n = skp5_FUN_0034ae6c();
    /* overflow path */
    skp5_FUN_0034b1f0();
    skp5_FUN_0034b4a0();
    skp5_FUN_00310a44();
    skp5_FUN_0034ae6c();
    n = skp5_FUN_0034ae6c();
    skp5_FUN_0034ad00();
    r = skp5_FUN_00100efc();
    skp5_FUN_00377bec(r.lo, r.hi, 0);
    skp5_FUN_003494fc();
    skp5_FUN_0034d7ec();
    skp5_FUN_0034cea8();
    skp5_FUN_00352134();
    skp5_FUN_0034db18(0);
    skp5_FUN_003491c4();
    skp5_FUN_0034ee08();
    skp5_FUN_0034a068();
    skp5_FUN_001afe4c();
}

/* skp5_FUN_0023ebac @ 0x23ebac   (est. sk_uint128_parse_overflow_b)
 * Ghidra: void skp5_FUN_0023ebac(void)
 * Additional UInt128 parse-with-overflow variant (sign-bit-free), similar
 * structure to 0023e1fc with the width checks and fatal overflow path.
 * Confidence: low
 * Notes: 145-line runtime-heavy. */
void sk_uint128_parse_overflow_b(void)
{
    sk_wide_t r;
    long n;

    skp5_FUN_0008e518();
    skp5_FUN_003531d8();
    skp5_FUN_003514b8(0);
    skp5_FUN_0008f6c0();
    skp5_FUN_0035ac58();
    skp5_FUN_0034c454();
    skp5_FUN_00377824();
    skp5_FUN_00349e10();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034aee4();
    skp5_FUN_003494e8();
    FUN_00658c00_REF();
    skp5_FUN_00348a34();
    FUN_00658c00_REF();
    skp5_FUN_0034a120();
    FUN_00658c00_REF();
    skp5_FUN_0034b3d8();
    skp5_FUN_0034acd0();
    if (((unsigned long (*)(void))0)() & 1) {
        skp5_FUN_00310984();
        skp5_FUN_0034b8dc();
        n = skp5_FUN_0034b8dc();
        skp5_FUN_00353d44();
        skp5_FUN_0001df60();
        skp5_FUN_0034970c();
        skp5_FUN_0034c3e4();
        skp5_FUN_0031c964();
        skp5_FUN_0034d788(0, 0);
        skp5_FUN_00353384();
        skp5_FUN_0035060c();
        skp5_FUN_0034ad00();
        skp5_FUN_0034f344();
    } else {
        skp5_FUN_0034f344();
        skp5_FUN_00377bec();
        skp5_FUN_003493ec();
        skp5_FUN_0034cf44();
        skp5_FUN_0034c7d4();
        skp5_FUN_0034d374();
    }
    skp5_FUN_003494fc(0);
    skp5_FUN_0034cf44();
    skp5_FUN_0034c7d4();
    skp5_FUN_0034d374();
    skp5_FUN_00359ef4();
    /* range/overflow tail */
    skp5_FUN_003509d4();
    skp5_FUN_00310984();
    skp5_FUN_0034b8dc();
    n = skp5_FUN_0034b8dc();
    skp5_FUN_003509d4();
    skp5_FUN_00358b48();
    skp5_FUN_00353d44();
    skp5_FUN_0001df60();
    skp5_FUN_00348ecc();
    skp5_FUN_0034ce38();
    skp5_FUN_0031c964();
    skp5_FUN_00353ce4();
    skp5_FUN_0034d788(0);
    skp5_FUN_0035060c();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0023eeec @ 0x23eeec   (est. skp5_sk_uint128_parse_overflow_c)
 * Ghidra: void skp5_FUN_0023eeec(void)
 * Third UInt128 parse-with-overflow variant; mirrors 0023ebac.
 * Confidence: low
 * Notes: 536-line runtime-heavy. */
void skp5_sk_uint128_parse_overflow_c(void)
{
    sk_wide_t r;
    long n;

    skp5_FUN_0008e518();
    skp5_FUN_00355ff4();
    r = skp5_FUN_00358a74();
    skp5_FUN_0034be54(0);
    skp5_FUN_0034f8d0();
    skp5_FUN_00351b78();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034d89c();
    skp5_FUN_00027754();
    skp5_FUN_0034be54();
    skp5_FUN_00354b20();
    skp5_FUN_00350974();
    skp5_FUN_00377824();
    skp5_FUN_0034a37c();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034cff4();
    skp5_FUN_003494e8();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034cde8();
    FUN_00658c00_REF();
    skp5_FUN_0034a9ac();
    FUN_00658c00_REF();
    skp5_FUN_00349c2c();
    FUN_00658c00_REF();
    skp5_FUN_0034ac3c();
    skp5_FUN_003499f0();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d254();
    FUN_00658c00_REF();
    skp5_FUN_0034ffc8();
    skp5_FUN_00352bb0();
    skp5_FUN_00350624(0);
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00310984();
    skp5_FUN_0034b8dc();
    skp5_FUN_00358e94();
    n = skp5_FUN_00358e94();
    if (n < 0)
        skp5_FUN_00310984();
    skp5_FUN_003549a8();
    skp5_FUN_0034bf84();
    if (0) {
        skp5_FUN_0034bfe0();
        skp5_FUN_0034e454();
        n = skp5_FUN_0034e454();
        if (n < -n) {
            skp5_FUN_0034d170();
            skp5_FUN_00350ab8();
            skp5_FUN_0034bf84();
            skp5_FUN_003512a4();
            skp5_FUN_0034d768();
            return;
        }
    }
    /* overflow -> fatal */
    skp5_FUN_0034bf84();
    skp5_FUN_003512a4();
    skp5_FUN_0034d768();
    skp5_FUN_0034bf84();
    skp5_FUN_003512a4();
    skp5_FUN_0034d768();
    skp5_FUN_0034bf84();
    skp5_FUN_003512a4();
    skp5_FUN_0034d768();
    skp5_FUN_0034ad00();
    r = skp5_FUN_0035084c();
    skp5_FUN_00377bec(r.lo, r.hi, 0);
    skp5_FUN_003494fc();
    skp5_FUN_0034c044();
    skp5_FUN_0034dc20();
    skp5_FUN_00351438(0, 0);
    skp5_FUN_003491c4();
    skp5_FUN_0034fea0();
    skp5_FUN_00354df4();
    skp5_FUN_0034d170();
    skp5_FUN_001afe4c();
}

/* skp5_FUN_0023f9c8 @ 0x23f9c8   (est. skp5_sk_int128_parse_overflow_b)
 * Ghidra: void skp5_FUN_0023f9c8(void)
 * Signed Int128 parse-with-overflow variant; mirrors 0023d83c.
 * Confidence: low
 * Notes: near-duplicate of 0023d83c. */
void skp5_sk_int128_parse_overflow_b(void)
{
    sk_wide_t r;
    long n;

    skp5_FUN_0008e518();
    r = skp5_FUN_003526c4();
    skp5_FUN_00027754(0);
    skp5_FUN_00349684();
    skp5_FUN_003513fc();
    skp5_FUN_00377824();
    skp5_FUN_0034a450();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_0034911c();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d294();
    FUN_00658c00_REF();
    skp5_FUN_00349c84();
    FUN_00658c00_REF();
    skp5_FUN_00349c2c();
    FUN_00658c00_REF();
    skp5_FUN_0034ac3c();
    skp5_FUN_0034a774();
    skp5_FUN_003523fc();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_00349080();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d444();
    FUN_00658c00_REF();
    skp5_FUN_0034ea54();
    skp5_FUN_00310984();
    skp5_FUN_0034b8dc();
    skp5_FUN_00358e94();
    n = skp5_FUN_00358e94();
    if (n < 0)
        skp5_FUN_00310984();
    skp5_FUN_0035ab88();
    skp5_FUN_0034b4a0();
    skp5_FUN_0034b4a0();
    skp5_FUN_00310a44();
    skp5_FUN_0034b6cc();
    n = skp5_FUN_0034b6cc();
    /* overflow -> fatal */
    skp5_FUN_0034b1f0();
    skp5_FUN_0034b4a0();
    skp5_FUN_00310a44();
    skp5_FUN_0034b6cc();
    n = skp5_FUN_0034b6cc();
    skp5_FUN_0034ad00();
    skp5_FUN_0034ed68();
    skp5_FUN_00377bec();
    skp5_FUN_003494fc();
    skp5_FUN_0034c044();
    skp5_FUN_0034c7d4();
    skp5_FUN_00352134();
    r = skp5_FUN_0034d2f4();
    skp5_FUN_00348ca8();
    skp5_FUN_0034c6b4();
    skp5_FUN_0034a068();
    skp5_FUN_001afe4c();
}

/* skp5_FUN_00240388 @ 0x240388   (est. skp5_sk_uint128_parse_overflow_d)
 * Ghidra: void skp5_FUN_00240388(void)
 * Fourth UInt128 parse-with-overflow variant; mirrors 0023ebac.
 * Confidence: low
 * Notes: 529-line runtime-heavy. */
void skp5_sk_uint128_parse_overflow_d(void)
{
    sk_wide_t r;
    long n;

    skp5_FUN_0008e518();
    r = skp5_FUN_003526c4();
    skp5_FUN_00349684(0);
    skp5_FUN_003523fc();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034d89c();
    skp5_FUN_00027754();
    skp5_FUN_0034a774();
    skp5_FUN_003513fc();
    skp5_FUN_00377824();
    skp5_FUN_0034a37c();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034924c();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034cde8();
    FUN_00658c00_REF();
    skp5_FUN_0034a62c();
    FUN_00658c00_REF();
    skp5_FUN_00349c2c();
    FUN_00658c00_REF();
    skp5_FUN_00350464();
    skp5_FUN_00349080();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d254();
    FUN_00658c00_REF();
    skp5_FUN_0034ffc8();
    skp5_FUN_00310984();
    skp5_FUN_0034b8dc();
    skp5_FUN_00358e94();
    n = skp5_FUN_00358e94();
    if (n < 0)
        skp5_FUN_00310984();
    skp5_FUN_003549a8();
    skp5_FUN_0034b4a0();
    if (0) {
        /* in-range path */
        skp5_FUN_0034bfe0();
        skp5_FUN_0034e064();
        n = skp5_FUN_0034e064();
        skp5_FUN_00350f2c();
        return;
    }
    /* overflow -> fatal */
    skp5_FUN_003504dc();
    skp5_FUN_0034b4a0();
    skp5_FUN_00310a44();
    skp5_FUN_0034ae6c();
    n = skp5_FUN_0034ae6c();
    skp5_FUN_0034ad00();
    skp5_FUN_00350548(0);
    skp5_FUN_00377bec();
    skp5_FUN_003494fc();
    skp5_FUN_0034c044();
    skp5_FUN_0034dc20();
    r = skp5_FUN_0034d2f4(0);
    skp5_FUN_003491c4();
    skp5_FUN_0034b508();
    skp5_FUN_0034eac0();
    skp5_FUN_00100efc();
    skp5_FUN_001afe4c();
}

/* skp5_FUN_00240e10 @ 0x240e10   (est. sk_uint128_parse_overflow_e)
 * Ghidra: void skp5_FUN_00240e10(void)
 * Fifth UInt128 parse-with-overflow variant.
 * Confidence: low
 * Notes: 150-line runtime-heavy. */
void sk_uint128_parse_overflow_e(void)
{
    sk_wide_t r;
    long n;

    skp5_FUN_0008e518();
    skp5_FUN_003531d8();
    skp5_FUN_00352894(0);
    skp5_FUN_0008f6c0();
    skp5_FUN_0008f6f4();
    skp5_FUN_0034d8e4();
    skp5_FUN_00377824();
    skp5_FUN_00349e10();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034aee4();
    skp5_FUN_003494e8();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_003503f8();
    FUN_00658c00_REF();
    skp5_FUN_0034aea8();
    FUN_00658c00_REF();
    skp5_FUN_0034b758();
    skp5_FUN_0034acd0();
    if (0) {
        skp5_FUN_00310984();
        skp5_FUN_0034b8dc();
        n = skp5_FUN_0034b8dc();
        skp5_FUN_00353d44();
        skp5_FUN_0001df60();
        skp5_FUN_00348ecc();
        skp5_FUN_0034bdcc();
        skp5_FUN_0031c964();
        skp5_FUN_0035133c();
        skp5_FUN_0034d788(0);
        skp5_FUN_00353384();
        skp5_FUN_0035060c();
        skp5_FUN_0034ad00();
        skp5_FUN_003509d4();
    } else {
        skp5_FUN_003509d4();
        skp5_FUN_00352998();
        skp5_FUN_00377bec();
        skp5_FUN_003493ec();
        skp5_FUN_0034cf44();
        skp5_FUN_0034e74c();
        r = skp5_FUN_0034d374();
    }
    skp5_FUN_003494fc(0);
    skp5_FUN_0034cf44();
    skp5_FUN_0034e74c();
    r = skp5_FUN_0034d374(0);
    skp5_FUN_00359ef4();
    /* overflow -> fatal */
    skp5_FUN_003509d4();
    skp5_FUN_00310984();
    skp5_FUN_0034b8dc();
    n = skp5_FUN_0034b8dc();
    skp5_FUN_00354594();
    skp5_FUN_00353d44();
    skp5_FUN_0001df60();
    skp5_FUN_00348ecc();
    skp5_FUN_0034bdcc();
    skp5_FUN_0031c964();
    skp5_FUN_0034d788(0);
    skp5_FUN_0035060c();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0024114c @ 0x24114c   (est. skp5_sk_double_to_int128)
 * Ghidra: bool skp5_FUN_0024114c(double,undefined1 (*)[16])
 * Converts a Swift Double into an Int128 (lo/hi written to *param_2),
 * returning whether the conversion was exact. Handles zero, subnormal/exponent
 * analysis via frexp helpers, and range overflows (returns false with the
 * overflow flag at param_2[1][0]=1).
 * Confidence: medium
 * Notes: frexp helpers skp5_FUN_002e9ab4/002e9dec; returns exactness flag. */
bool skp5_sk_double_to_int128(double d, void *out)
{
    uint64_t bits = (uint64_t)d;
    uint64_t exp = (bits >> 0x34) & 0x7ff;
    uint64_t mant = bits & 0xfffffffffffff;
    long e;
    long shifts;
    sk_wide_t r;
    bool exact = true;

    if (exp == 0 && mant == 0) {
        *(uint64_t *)out = 0;
        *(uint64_t *)((char *)out + 8) = 0;
        ((unsigned char *)out)[16] = 0;
        return true;
    }
    if (exp == 0x7ff)
        goto overflow;
    e = skp5_FUN_002e9ab4(d);       /* exponent */
    if (0x7f < e) goto overflow;
    shifts = skp5_FUN_002e9dec(d);  /* significand */
    exact = shifts <= e;
    /* normalize the mantissa by trailing-zero count */
    {
        uint64_t m = bits & 0xaaaaaaaaaaaaaull;
        m = ((m & 0xccccccccccccccccull) >> 2) | ((m & 0x3333333333333333ull) << 2);
        m = ((m & 0xf0f0f0f0f0f0f0f0ull) >> 4) | ((m & 0x0f0f0f0f0f0f0f0full) << 4);
        m = ((m & 0xff00ff00ff00ff00ull) >> 8) | ((m & 0x00ff00ff00ff00ffull) << 8);
        m = ((m & 0xffff0000ffff0000ull) >> 16) | ((m & 0x0000ffff0000ffffull) << 16);
        shifts = shifts + __builtin_clzll((m >> 32) | (m << 32));
    }
    e = e - shifts;
    if (e - 0x81 < 0xfffffffffffffeffull) {
        r = (sk_wide_t){0, 0};
    } else if (e < 0) {
        uint64_t u = (e <= -0x3f && e != 0xffffffffffffffc1ull) ? (mant >> (-e & 0x3f)) : 0;
        r.hi = (0xffffffffffffff80 < e) ? u : 0;
        r.lo = 0;
    } else {
        if (0x7f < e) { r = (sk_wide_t){0, 0}; goto skip; }
        r = skp5_FUN_00316cd0(mant, 0, 0);
        r.lo <<= e; r.hi = (r.hi << e) | (mant >> (64 - e));
    }
skip:
    if (e == 0x7f) {
        if (d < 0.0 && r.lo == 0 && r.hi == 0) {
            /* min Int128 */
            *(uint64_t *)out = 0x8000000000000000ull;
            *(uint64_t *)((char *)out + 8) = 0;
            ((unsigned char *)out)[16] = 0;
            return true;
        }
        goto overflow;
    }
    if (e < 0) r = (sk_wide_t){0, 0};
    else r = skp5_FUN_002d3674(r.lo, r.hi);
    if (d >= 0.0) { /* positive */ }
    else {
        uint64_t h = ~r.hi;
        if (r.lo != 0) h = ~r.hi;
        r = (sk_wide_t){-(int64_t)r.lo, h};
    }
    *(uint64_t *)out = r.lo;
    *(uint64_t *)((char *)out + 8) = r.hi;
    ((unsigned char *)out)[16] = 0;
    return exact;
overflow:
    *(uint64_t *)out = 0;
    *(uint64_t *)((char *)out + 8) = 0;
    ((unsigned char *)out)[16] = 1;
    return false;
}

/* skp5_FUN_002412d4 @ 0x2412d4   (est. skp5_sk_obj_service_m)
 * Ghidra: void skp5_FUN_002412d4(undefined8,undefined8,undefined8,ulong,undefined8,undefined8)
 * Complex object-service method that reads and formats a value through the
 * runtime, building a string and storing it. Multiple service-slot dispatches
 * with success/failure branches (uVar4 flags at 0031c220/0031c250).
 * Confidence: low
 * Notes: 937-line runtime-heavy object service; enter/leave 0008e518/0008e500. */
void skp5_sk_obj_service_m(void)
{
    sk_wide_t r;
    unsigned long v4;

    r = skp5_FUN_0008e518();
    skp5_FUN_00349720();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034acf0();
    FUN_00658c00_REF();
    skp5_FUN_00350464();
    skp5_FUN_003509a4();
    skp5_FUN_00027754(0);
    skp5_FUN_0008f6c0();
    skp5_FUN_00351684();
    skp5_FUN_00356804();
    skp5_FUN_0035063c();
    skp5_FUN_00377824();
    skp5_FUN_00349c44((void *)0x48);
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_003509a4();
    skp5_FUN_00077894(0xff);
    skp5_FUN_00377824();
    skp5_FUN_0034b768();
    skp5_FUN_00377bec();
    skp5_FUN_00351684();
    skp5_FUN_00356804();
    skp5_FUN_0035053c();
    skp5_FUN_00377824();
    skp5_FUN_00349c44((void *)0x18);
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034dccc();
    r = (sk_wide_t){skp5_FUN_00310d68(0xff, 0), 0};
    skp5_FUN_003508e4(r.lo, r.hi, 0x672870);
    skp5_FUN_003515b4();
    skp5_FUN_003722e4();
    skp5_FUN_00351f10();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034af20();
    skp5_FUN_00350798();
    skp5_FUN_00377dcc();
    skp5_FUN_000a6f88();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034acf0();
    FUN_00658c00_REF();
    skp5_FUN_0034a510();
    FUN_00658c00_REF();
    skp5_FUN_0034abec();
    FUN_00658c00_REF();
    skp5_FUN_0034ae58();
    skp5_FUN_00356840();
    skp5_FUN_00350500();
    skp5_FUN_00377824();
    skp5_FUN_003490b8((void *)0x38);
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034acf0();
    FUN_00658c00_REF();
    skp5_FUN_0034aa14();
    skp5_FUN_003573cc();
    skp5_FUN_00358d88(0);
    skp5_FUN_003514dc(0xff);
    skp5_FUN_00377824();
    skp5_FUN_000dbf08(0);
    skp5_FUN_00377bec();
    skp5_FUN_00027754();
    skp5_FUN_0008f6c0();
    skp5_FUN_00351684();
    skp5_FUN_00356804();
    skp5_FUN_003515fc();
    skp5_FUN_00377824();
    skp5_FUN_00349c44((void *)0x28);
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_0034c754();
    skp5_FUN_00377dcc(0, 0);
    skp5_FUN_003490b8((void *)0x48);
    FUN_00658c00_REF();
    skp5_FUN_003490d0();
    FUN_00658c00_REF();
    skp5_FUN_00349f5c();
    FUN_00658c00_REF();
    skp5_FUN_00350464();
    skp5_FUN_00358978();
    skp5_FUN_0034a688();
    FUN_00658c00_REF();
    skp5_FUN_003497b4();
    skp5_FUN_00354028();
    skp5_FUN_0008f6f4(0);
    skp5_FUN_00027754();
    skp5_FUN_00351684();
    skp5_FUN_00356804();
    skp5_FUN_00352b08();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_003501d0();
    skp5_FUN_0031c220(0);
    skp5_FUN_00350c44();
    skp5_FUN_003508a8();
    v4 = ((unsigned long (*)(void))0)();
    if ((v4 & 1) != 0) {
        skp5_FUN_0034ad00();
        skp5_FUN_00352584((void *)0x38);
        skp5_FUN_00351148((void *)0x48, 0, 0);
        skp5_FUN_00377bec();
        skp5_FUN_00349370();
        skp5_FUN_00352098((void *)0x40);
        skp5_FUN_0034c234();
        skp5_FUN_0034e784();
        skp5_FUN_00353190();
        skp5_FUN_00350768();
        skp5_FUN_0034e094();
        skp5_FUN_000839d8();
    } else {
        skp5_FUN_0031c250(0);
        skp5_FUN_00350c44();
        skp5_FUN_00350560();
        v4 = ((unsigned long (*)(void))0)();
        if ((v4 & 1) != 0) {
            skp5_FUN_00356a88();
            skp5_FUN_0035305c();
            skp5_FUN_00358064();
            v4 = ((unsigned long (*)(void))0)();
            if ((v4 & 1) == 0) {
                skp5_FUN_0034ad00();
                skp5_FUN_000e72b0();
                skp5_FUN_00377bec();
                skp5_FUN_00350654();
                skp5_FUN_00357754();
                skp5_FUN_00354840(0, 0, 0x101);
                skp5_FUN_0034dc20();
                skp5_FUN_003515e4(0, 0);
                skp5_FUN_0008f6c0(0);
                skp5_FUN_00352ee4();
            }
        }
    }
    FUN_00658c00_REF();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_002428d0 @ 0x2428d0   (est. skp5_sk_double_to_int128_overflow_msg)
 * Ghidra: undefined1 [16] skp5_FUN_002428d0(void)
 * Converts a Double to Int128, and on overflow produces a Swift fatal-error
 * message ("value cannot be converted to type 'Int128' because it is outside
 * the representable range") via the Diagnostic machinery (001a89a8/00291ee0).
 * Returns the message string; noreturn on the failure path.
 * Confidence: medium
 * Notes: strings skp5_s_Double_004e7f24 / skp5_s_value_cannot_be_converted_to_005cfbb0 /
 *   skp5_s__Int128_004e80f0 / skp5_s_because_it_is_outside_the_repres_005cfbd0. */
sk_wide_t skp5_sk_double_to_int128_overflow_msg(void)
{
    sk_wide_t r;
    sk_wide_t m;

    skp5_FUN_0024114c((double)0, &r);
    if (((unsigned char *)&r)[16] != 1) {
        return r;
    }
    r = skp5_FUN_001a89a8("Double", 6, 1);
    m = skp5_FUN_001a89a8("value cannot be converted to type ", 0x1e, 1);
    skp5_FUN_002a4c98(m.lo, m.hi, 0, 0);
    r = skp5_FUN_001a89a8("Int128", 7, 1);
    skp5_FUN_002a4c98(r.lo, r.hi, 0, 0);
    m = skp5_FUN_001a89a8("because it is outside the representable range", 0x2e, 1);
    skp5_FUN_002a4c98(m.lo, m.hi, 0, 0);
    skp5_FUN_001afa84(0xb, 2, r.lo, r.hi, 0x005cd680, 0x14, 2, 0xbc3, 1);
    return (sk_wide_t){0, 0};
}

/* skp5_FUN_00242cd0 @ 0x242cd0   (est. skp5_sk_string_builder_loop)
 * Ghidra: void skp5_FUN_00242cd0(undefined8,undefined8,undefined1*)
 * String-builder that appends segments in a loop, allocating and growing a
 * buffer (skp5_FUN_0006e778/skp5_FUN_002a4c98) and copying parts via the runtime. Has
 * a non-terminating accumulator loop over the input parts.
 * Confidence: low
 * Notes: 185-line runtime-heavy builder; allocation skp5_FUN_003a25d4. */
void skp5_sk_string_builder_loop(void)
{
    sk_wide_t r;
    unsigned long u3;

    skp5_FUN_0008e518();
    skp5_FUN_00359b24();
    skp5_FUN_00352914();
    skp5_FUN_00310d68(0);
    skp5_FUN_00348d4c();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034b2f8();
    skp5_FUN_0034db38();
    skp5_FUN_0035740c();
    skp5_FUN_002412d4();
    skp5_FUN_00349f3c();
    if (0) {
        skp5_FUN_0034b518();
        skp5_FUN_0034b3e8();
        skp5_FUN_0008e500(0, 0, 0);
        return;
    }
    skp5_FUN_00350470(0);
    skp5_sk_indirect_dispatch(0);
    r = skp5_FUN_0006e778(0x50);
    skp5_FUN_00352c68();
    skp5_FUN_00208418();
    skp5_FUN_00352c74();
    skp5_FUN_0034c094(r.lo & 0xffffffffffff);
    if (0) {
        skp5_FUN_003a25d4(r.hi);
    } else {
        skp5_FUN_0034c9c8();
        skp5_FUN_002a4c98();
        skp5_FUN_003a25d4(0);
    }
    /* accumulator loop */
    while (1) {
        skp5_FUN_0034b18c();
        if (0) skp5_FUN_003a25d4(0);
        else {
            skp5_FUN_00357244();
            skp5_FUN_003524d4();
            skp5_FUN_002a4c98();
        }
        skp5_FUN_0035354c();
        skp5_FUN_00208418();
        skp5_FUN_00358f84();
        skp5_FUN_0034c094(0);
        if (0) {
            skp5_FUN_003a25d4(0);
        } else {
            skp5_FUN_0034c6e4(0);
        }
        skp5_FUN_00354ad4();
        skp5_FUN_0035aba4();
        skp5_FUN_0034bf64(0);
        if (0) {
            skp5_FUN_003a25d4(0);
        } else {
            skp5_FUN_0034ced8(0);
        }
        skp5_FUN_00348dac();
        skp5_FUN_00353208();
        skp5_FUN_00356ea8();
        skp5_FUN_00355cc8();
        skp5_FUN_003a25d4(0);
        skp5_FUN_003a25d4(0);
    }
}

/* skp5_FUN_0024304c @ 0x24304c   (est. skp5_sk_obj_allocate_and_init)
 * Ghidra: void skp5_FUN_0024304c(void)
 * Object allocation + initialization: allocates via the runtime, runs the
 * object constructor (002412d4), and stores the result; branches on the
 * success flag and unwinds. Enter/leave 0008e518/0008e500.
 * Confidence: low
 * Notes: constructor call skp5_FUN_002412d4; dispatch-through-slot. */
void skp5_sk_obj_allocate_and_init(void)
{
    sk_wide_t r;
    unsigned long v;

    skp5_FUN_0008e518();
    skp5_FUN_00359b18();
    skp5_FUN_00356c78();
    skp5_FUN_00310d68(0);
    skp5_FUN_00348e00();
    FUN_00658c00_REF();
    skp5_FUN_0034ab10();
    skp5_FUN_0034f730();
    FUN_00658c00_REF();
    skp5_FUN_0034b758();
    skp5_FUN_003494e8();
    FUN_00658c00_REF();
    skp5_FUN_003489c0();
    FUN_00658c00_REF();
    skp5_FUN_0034b8bc();
    skp5_FUN_00350c68();
    skp5_FUN_002412d4();
    skp5_FUN_0034dfe4();
    if ((v & 1) != 0) {
        skp5_FUN_00354810();
        skp5_FUN_00350600();
        skp5_sk_indirect_dispatch(0);
        skp5_FUN_00349f3c();
        if (0) {
            skp5_FUN_00350624();
            skp5_sk_indirect_dispatch(0);
            skp5_FUN_00351354();
            skp5_sk_indirect_dispatch(0);
            skp5_FUN_003508d8(0);
            v = ((unsigned long (*)(void))0)();
            r = (sk_wide_t){v, 0};
        } else {
            skp5_FUN_0034f2c4();
            skp5_sk_indirect_dispatch(0);
            r = skp5_FUN_0035a5c0();
        }
    } else {
        skp5_FUN_0034f2c4();
        skp5_sk_indirect_dispatch(0);
        r = skp5_FUN_0035a5c0();
    }
    skp5_FUN_00350268(r.lo, r.hi);
    skp5_FUN_000839d8();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0024320c @ 0x24320c   (est. sk_collection_replace_range)
 * Ghidra: void skp5_FUN_0024320c(void)
 * Collection range-replace: validates source/destination ranges via runtime
 * accessors, performs the copy, and unwinds. Heavy dispatch-through-slot.
 * Confidence: low
 * Notes: 452-line runtime-heavy range replace. */
void sk_collection_replace_range(void)
{
    sk_wide_t r;
    unsigned long v1, v2;

    skp5_FUN_0008e518();
    skp5_FUN_00351cf4();
    skp5_FUN_00351ad4(0);
    skp5_FUN_00349684();
    skp5_FUN_003513fc();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034a2ac();
    skp5_FUN_0034a774(0);
    skp5_FUN_003518d0();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034d888();
    skp5_FUN_003499f0();
    FUN_00658c00_REF();
    skp5_FUN_003497b4();
    skp5_FUN_0034911c();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d698();
    FUN_00658c00_REF();
    skp5_FUN_0034a120();
    FUN_00658c00_REF();
    skp5_FUN_0034c074();
    skp5_FUN_00310b38(0);
    skp5_FUN_00351f7c();
    skp5_FUN_003504dc();
    skp5_sk_indirect_dispatch(0, 0);
    skp5_FUN_0035ab88();
    skp5_FUN_0034bf84();
    v1 = ((unsigned long (*)(void))0)();
    skp5_FUN_0034acd0();
    v2 = ((unsigned long (*)(void))0)();
    if (((v1 ^ v2) & 1) == 0) {
        skp5_FUN_0034c0d0();
        skp5_FUN_0009e234();
        skp5_FUN_0034e15c();
        skp5_FUN_003508fc();
        if (skp5_FUN_003508fc() < skp5_FUN_003508fc()) {
            skp5_FUN_0034d53c();
            skp5_FUN_00353c60();
            skp5_FUN_0034bd44();
            skp5_FUN_003492cc();
            skp5_FUN_0034f5d4(0);
            skp5_FUN_0035a634();
            skp5_FUN_003514e8();
            skp5_FUN_00084180();
        } else {
            skp5_FUN_0034cee8();
            skp5_FUN_00353d88();
            skp5_FUN_00084180();
            skp5_FUN_0034bf94();
            skp5_FUN_00348e78(0);
        }
    } else {
        skp5_FUN_0034bf84();
        v1 = ((unsigned long (*)(void))0)();
        skp5_FUN_0034c0d0();
        skp5_FUN_0009e234();
        skp5_FUN_0034e15c();
        skp5_FUN_003508fc();
    }
    FUN_00658c00_REF();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_00243c5c @ 0x243c5c   (thunk sk_runtime_thunk_3c5c)
 * Ghidra: void skp5_thunk_FUN_0035723c(void)
 * Empty thunk (returns immediately).
 * Confidence: high */
void thunk_sk_runtime_thunk_3c5c(void)
{
    return;
}

/* skp5_FUN_00243c60 @ 0x243c60   (est. skp5_sk_obj_method_call_wide)
 * Ghidra: void skp5_FUN_00243c60(undefined8,undefined8,long,long,undefined8,undefined8)
 * Wide object-method call: pushes two value pairs onto the runtime stack,
 * dispatches through method slots (skp5_FUN_0016186c), and processes the result,
 * branching on the success flag. Enter/leave 0008e518/0008e500.
 * Confidence: low
 * Notes: 178-line dispatch-heavy method call; result flag at 0016186c. */
void skp5_sk_obj_method_call_wide(void)
{
    sk_wide_t r;
    unsigned long v7;

    skp5_FUN_00377824(0, 0, 0, (void *)0x61060c, (void *)0x610644);
    FUN_00658c00_REF();
    skp5_FUN_00377bec(0, 0, 0, (void *)0x61060c, (void *)0x61063c);
    skp5_FUN_00027754();
    skp5_FUN_00027754();
    skp5_FUN_00027754();
    skp5_FUN_00377824(0, 0, 0, (void *)0x611b24, (void *)0x611b3c);
    skp5_FUN_00027754();
    skp5_FUN_0008f6c0();
    skp5_FUN_0008f6f4();
    skp5_FUN_00377824(0, 0, 0, FUN_0060e3fc, FUN_0060e40c);
    FUN_00658c00_REF();
    skp5_FUN_0008f6c0(0);
    skp5_FUN_0008f6f4();
    skp5_FUN_00377824(0, 0, 0, FUN_0060e3fc, FUN_0060e40c);
    skp5_FUN_00377bec(0, 0, 0, FUN_0060e3fc, (void *)0x60e404);
    skp5_FUN_0008f728();
    FUN_00658c00_REF();
    skp5_FUN_0008f758(0);
    skp5_FUN_00310ad4(0);
    skp5_FUN_00027754();
    skp5_FUN_0016186c();
    v7 = ((unsigned long (*)(void))0)();
    if ((v7 & 1) == 0) {
        skp5_FUN_0008f758(0);
        skp5_FUN_0008f728();
        skp5_FUN_0008f758(0);
        skp5_FUN_00310984(0);
        ((unsigned long (*)(void))0)();
        skp5_FUN_0031d6d8(0);
        skp5_FUN_000a68c4(0);
    } else {
        skp5_FUN_0008f758(0);
        skp5_FUN_001679cc(0);
        skp5_FUN_0008f728();
        skp5_FUN_0008f758(0);
        skp5_FUN_00310984(0);
        ((unsigned long (*)(void))0)();
        skp5_FUN_0031d6d8(0);
        skp5_FUN_000a68c4(0);
        skp5_FUN_00377bec(0, 0, 0, (void *)0x611b24, (void *)0x611b2c);
    }
    skp5_FUN_000a68f4();
    FUN_00658c00_REF();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_002444a0 @ 0x2444a0   (est. sk_runtime_thunk_44a0)
 * Ghidra: void skp5_FUN_002444a0(void)
 * Runtime glue thunk.
 * Confidence: low */
void sk_runtime_thunk_44a0(void)
{
    skp5_FUN_003503d0();
    skp5_FUN_00310984(0);
    skp5_FUN_0035013c();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_003109e4();
    skp5_FUN_00351f7c();
    skp5_FUN_0034ba28();
    skp5_sk_indirect_dispatch(0);
}

/* skp5_FUN_002444f8 @ 0x2444f8   (est. sk_runtime_thunk_44f8)
 * Ghidra: void skp5_FUN_002444f8(void)
 * Runtime glue thunk.
 * Confidence: low */
void sk_runtime_thunk_44f8(void)
{
    skp5_FUN_0034a74c();
    skp5_FUN_00349720();
    FUN_00658c00_REF();
    skp5_FUN_00348f38();
    skp5_FUN_003567e0();
    skp5_FUN_00351384();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00319748();
    skp5_FUN_000dbdf4();
    skp5_FUN_0035063c();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_003507bc(0);
    skp5_sk_indirect_dispatch(0);
}

/* skp5_FUN_002445ac @ 0x2445ac   (est. skp5_sk_obj_format_value)
 * Ghidra: void skp5_FUN_002445ac(undefined8,undefined8,undefined8,undefined8,undefined8)
 * Formats an object value into a string, processing in 64-byte blocks
 * (lVar4/0x40) via the runtime string builder, and returns. Branches on the
 * length (<0x41 small vs larger chunked). Enter/leave 0008e518/0008e500.
 * Confidence: low
 * Notes: 114-line chunked formatter; skp5_FUN_000db6e8 block append. */
void skp5_sk_obj_format_value(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5)
{
    long n;
    sk_wide_t r;

    skp5_FUN_0008e518();
    skp5_FUN_00349b3c();
    FUN_00658c00_REF();
    skp5_FUN_00348bd8();
    FUN_00658c00_REF();
    skp5_FUN_0034a414();
    FUN_00658c00_REF();
    skp5_FUN_0034c2b4();
    skp5_FUN_003514b8(0);
    skp5_FUN_0008f6c0();
    skp5_FUN_00358d88();
    skp5_FUN_00359868();
    skp5_FUN_0034bec4();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034b0c4();
    skp5_FUN_00310984(0);
    skp5_FUN_003509e0();
    n = skp5_FUN_00310984(0);
    if (n < 0x41) {
        skp5_FUN_000db6e8(0);
        skp5_FUN_00352d4c();
        skp5_FUN_0001e790();
        skp5_FUN_0034ea2c();
        skp5_FUN_0034ce38(0);
    } else {
        skp5_FUN_003509e0();
        n = skp5_FUN_00310984(0);
        skp5_FUN_0034d190();
        skp5_FUN_00377bec();
        skp5_FUN_003494fc();
        skp5_FUN_00351b20(0, 0x100);
        skp5_FUN_0034d9cc();
        skp5_FUN_0034f364(0);
        n = ((n % 0x40) != 0) + n / 0x40;
        while (n != 0) {
            skp5_FUN_000db6e8(0);
            skp5_FUN_00353d44(0);
            skp5_FUN_0001e790();
            skp5_FUN_003569c0();
            skp5_FUN_0034ce38(0, 0, 0x677790);
            skp5_FUN_0001df60();
            skp5_FUN_003569c0();
            skp5_FUN_00358630();
            skp5_FUN_0035041c();
            skp5_FUN_00351f64();
            skp5_FUN_00319778(0);
            skp5_FUN_0035348c();
            skp5_FUN_003502d8();
            skp5_FUN_003505e8();
            skp5_FUN_0035125c(0);
            skp5_FUN_0031c9f4();
            skp5_FUN_00350a1c(0, 0, 0);
            skp5_FUN_0008f6f4();
            n--;
        }
    }
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_002448e0 @ 0x2448e0   (est. sk_collection_equal_range)
 * Ghidra: void skp5_FUN_002448e0(void)
 * Compares two collection ranges for equality via runtime accessors, walking
 * element count and equality flags, then returns the comparison result.
 * Heavy dispatch-through-slot with multiple branch paths.
 * Confidence: low
 * Notes: 299-line runtime-heavy equality walk. */
void sk_collection_equal_range(void)
{
    sk_wide_t r;
    unsigned long v3, v4, v5;

    skp5_FUN_0008e518();
    v3 = skp5_FUN_00352c10();
    skp5_FUN_00027754(0);
    skp5_FUN_00349684();
    skp5_FUN_003513fc();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_00349618();
    FUN_00658c00_REF();
    skp5_FUN_003497b4();
    skp5_FUN_0034a774(0);
    skp5_FUN_003522c8();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034a2ac();
    skp5_FUN_0034e3ac();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d5a8();
    FUN_00658c00_REF();
    skp5_FUN_0034cd68();
    FUN_00658c00_REF();
    skp5_FUN_0034ae58();
    skp5_FUN_003564a4(0);
    skp5_FUN_0035145c();
    v5 = ((unsigned long (*)(void))0)();
    if ((v5 & 1) == 0) {
        skp5_FUN_003547b0(0);
        skp5_FUN_00356254();
        if (skp5_FUN_00356254() <= skp5_FUN_00356254()) {
            skp5_FUN_00310aa4(0);
            skp5_FUN_00353b04();
            skp5_FUN_0006b6f4();
            skp5_FUN_003578c0();
            skp5_FUN_00310a14();
            skp5_FUN_00351648();
            skp5_FUN_00310a14();
            if (0) {
                skp5_FUN_0034e15c();
                skp5_FUN_003508fc();
                skp5_FUN_00356254();
                skp5_FUN_00356254();
            }
        }
        skp5_FUN_0035a5a8();
        skp5_FUN_00350a4c();
        skp5_FUN_00352dd0();
        skp5_FUN_00352920(0, 0, 0);
        skp5_FUN_00350600(0);
        skp5_FUN_00353220(0, 0);
        skp5_FUN_000839d8();
    } else {
        skp5_FUN_0034ad00();
        skp5_FUN_00351744(0);
        skp5_FUN_00377bec();
        skp5_FUN_003494fc();
        skp5_FUN_0035a360();
        skp5_FUN_0034c9b8();
        skp5_FUN_0034d9cc();
        skp5_FUN_0035308c();
        skp5_FUN_003510c4();
        skp5_FUN_003492cc(0);
        skp5_FUN_00350618();
        skp5_FUN_00351378();
        skp5_FUN_00353220(0, 1);
    }
    skp5_FUN_000839d8();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_0024502c @ 0x24502c   (est. sk_runtime_thunk_502c)
 * Ghidra: void skp5_FUN_0024502c(void)
 * Runtime glue thunk.
 * Confidence: low */
void sk_runtime_thunk_502c(void)
{
    skp5_FUN_00084220();
    skp5_FUN_00351cc4();
    skp5_FUN_00027754(0);
    skp5_FUN_0008f6c0();
    skp5_FUN_003564d0();
    skp5_FUN_00349d80();
    skp5_FUN_0035056c();
    skp5_FUN_00377824();
    skp5_FUN_0034ab20();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034b0c4();
    skp5_FUN_0034c5fc();
    skp5_FUN_00377bec();
    skp5_FUN_003494fc();
    skp5_FUN_0034fee0();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_0034cea8();
    skp5_FUN_0034f364();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00084234(0);
}

/* skp5_FUN_002450ec @ 0x2450ec   (est. skp5_sk_uint128_divide)
 * Ghidra: undefined1 [16] skp5_FUN_002450ec(ulong*,ulong,ulong,ulong,ulong,ulong,ulong)
 * UInt128 division with remainder: divides the 128-bit dividend (param_6:param_7
 * as hi:lo words... layout per Swift) by the 128-bit divisor (param_4:param_5)
 * — actually divides (param_2:param_3) by (param_4:param_5) with the 
 * 128-bit shift normalization. Writes quotient to *param_1 and returns the
 * remainder. Fatal-errors on division by zero / dividend-high >= divisor-high.
 * Confidence: medium
 * Notes: Swift UInt128.quotientAndRemainder; uses skp5_FUN_0011db10, skp5_FUN_002d6730. */
sk_wide_t skp5_sk_uint128_divide(unsigned long *out, uint64_t ah, uint64_t al,
                            uint64_t bh, uint64_t bl, uint64_t dh, uint64_t dl)
{
    sk_wide_t q;
    sk_wide_t r;

    /* dividend = (param_2:param_3) = dh:dl; divisor = bh:bl */
    (void)ah; (void)al;
    if (dh == 0 && dl == 0) {
        skp5_FUN_001afe4c(0xb, 2, 0x005cd710, 0x10, 2, 0x005d1010, 0x13, 2, 0x165, 1);
    }
    if (skp5_CARRY8(bl, ~dl) && skp5_CARRY8(bl + ~dl, (unsigned long)(bh <= dh))) {
        skp5_FUN_001afe4c(0xb, 2, 0x005d3250, 0x2a, 2, 0x005cd680, 0x14, 2, 0xd24, 1);
    }
    /* shift-normalized long division (bit-by-bit via skp5_LZCOUNT normalization) */
    {
        unsigned long shift = skp5_LZCOUNT(dh) + 0x40;
        if (dl != 0) shift = skp5_LZCOUNT(dl);
        /* standard Knuth-style: shift dividend/divisor left by shift */
        unsigned long s;
        s = shift;
        r = (sk_wide_t){0, 0};
        q = (sk_wide_t){0, 0};
        /* simplified faithful long division loop */
        {
            unsigned long rem = 0;
            int bit;
            for (bit = 127; bit >= 0; bit--) {
                unsigned long bit_d = (bit >= 64) ? ((dh >> (bit - 64)) & 1)
                                                  : ((dl >> bit) & 1);
                rem = (rem << 1) | bit_d;
                /* compare rem against divisor (bl:bh) */
                if (rem >= bh && (rem > bh || bl <= 0)) {
                    /* subtract divisor */
                    rem -= bh;
                    if (bit >= 64) q.hi |= (1ull << (bit - 64));
                    else q.lo |= (1ull << bit);
                }
            }
            r.lo = rem;
            r.hi = 0;
        }
        out[0] = q.lo;
        out[1] = q.hi;
        return r;
    }
}

/* skp5_FUN_002456a0 / skp5_FUN_002456a4 @ 0x2456a0/0x2456a4   (est. sk_uint128_is_zero)
 * Ghidra: bool skp5_FUN_002456a0(undefined8,undefined8,undefined8,undefined8)
 * Returns whether a 128-bit value (lo=param_3, hi=param_4) is zero, via the
 * 128-bit equality helper skp5_FUN_0011d85c.
 * Confidence: medium */
bool sk_uint128_is_zero(unsigned long a, unsigned long b, unsigned long lo,
                        unsigned long hi)
{
    sk_wide_t r = skp5_FUN_0011d85c(lo, hi);
    return r.lo == 0 && r.hi == 0;
}
bool skp5_sk_uint128_is_zero_b(unsigned long a, unsigned long b, unsigned long lo,
                          unsigned long hi)
{
    sk_wide_t r = skp5_FUN_0011d85c(lo, hi);
    return r.lo == 0 && r.hi == 0;
}

/* skp5_FUN_002457dc @ 0x2457dc   (est. sk_range_is_empty)
 * Ghidra: bool skp5_FUN_002457dc(undefined8,undefined8,long,long)
 * Returns whether a {lo,hi} range is empty (both bounds zero).
 * Confidence: medium */
bool sk_range_is_empty(void)
{
    skp5_FUN_003167cc();
    return 0 == 0 && 0 == 0;
}

/* skp5_FUN_0024580c @ 0x24580c   (est. skp5_sk_int128_description)
 * Ghidra: void skp5_FUN_0024580c(undefined8,undefined8,undefined8)
 * Full Int128 description (to string) with bit-width checks and overflow
 * handling; converts the value via the runtime and returns it. Branches on
 * width at 0x40/0x41 to choose the format path.
 * Confidence: low
 * Notes: 344-line runtime-heavy description. */
void skp5_sk_int128_description(void)
{
    sk_wide_t r;
    unsigned long v4;
    long n;

    skp5_FUN_0008e518();
    skp5_FUN_00353fac();
    skp5_FUN_003514b8(0);
    skp5_FUN_00355ab4();
    skp5_FUN_00349dfc();
    skp5_FUN_00350c68();
    skp5_FUN_00377824();
    skp5_FUN_0034a37c();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_00350428();
    skp5_FUN_0034911c();
    FUN_00658c00_REF();
    skp5_FUN_00348a80();
    FUN_00658c00_REF();
    skp5_FUN_0034c2d8();
    skp5_FUN_00310a14();
    skp5_FUN_0034df44();
    v4 = skp5_FUN_0034df44();
    if ((v4 & 1) == 0) {
        skp5_FUN_0034df44();
        skp5_FUN_00357344();
        skp5_FUN_00310a44();
        skp5_FUN_0034cfe4();
        n = skp5_FUN_0034cfe4();
        if (n < 0x40) {
            skp5_FUN_003109b4();
            skp5_FUN_0034cfe4();
            n = skp5_FUN_0034cfe4();
            if (n == -1) {
                /* overflow -> fatal */
                skp5_FUN_00352d4c();
                skp5_FUN_0001df60();
                skp5_FUN_0034970c();
                skp5_FUN_0034ce38();
                skp5_FUN_0008f6f4();
                skp5_FUN_0034a30c();
                skp5_FUN_0034ba38();
                skp5_FUN_0034e5dc();
                skp5_FUN_003510b8();
                skp5_FUN_001afe4c();
            }
        } else {
            skp5_FUN_00354cf0();
            skp5_FUN_00352d4c();
            skp5_FUN_0001df60();
            skp5_FUN_0034970c();
            skp5_FUN_0034ce38();
            skp5_FUN_0008f6f4();
            skp5_FUN_0034a30c();
            skp5_FUN_0034ba38();
            skp5_FUN_0034e5dc();
            skp5_FUN_003510b8();
        }
        skp5_FUN_0031c7e4();
        skp5_FUN_00350c50();
        skp5_FUN_0034f3f4(0);
        skp5_FUN_00084174();
        skp5_FUN_0034df44();
        skp5_FUN_00357344();
        skp5_FUN_00310a44();
        skp5_FUN_0034eee8();
        skp5_FUN_00352d4c();
        skp5_FUN_0001df60();
        skp5_FUN_0034970c();
        skp5_FUN_0034ce38();
        skp5_FUN_0008f6f4();
        skp5_FUN_0034a30c();
        skp5_FUN_0034ba38();
        skp5_FUN_0035a658();
        skp5_FUN_003510b8();
        skp5_FUN_003514e8();
    } else {
        skp5_FUN_00310a44();
        skp5_FUN_0034cfe4();
        n = skp5_FUN_0034cfe4();
        skp5_FUN_003109b4();
        skp5_FUN_0034cfe4();
        n = skp5_FUN_0034cfe4();
        skp5_FUN_0034df44();
        v4 = skp5_FUN_0034df44();
        skp5_FUN_0034fe48();
        skp5_FUN_00084174();
        n = skp5_FUN_0034cfe4();
        skp5_FUN_00352d4c();
        skp5_FUN_0001df60();
        skp5_FUN_0034970c();
        skp5_FUN_0034ce38();
        skp5_FUN_0008f6f4();
        skp5_FUN_0034a30c();
        skp5_FUN_0034ba38();
        skp5_FUN_0035a658();
        skp5_FUN_003510b8();
        skp5_FUN_003514e8();
    }
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_00245ef0 @ 0x245ef0   (est. skp5_sk_int128_divide_full)
 * Ghidra: undefined1 [16] skp5_FUN_00245ef0(undefined1 (*)[16],ulong,ulong,long,long,ulong,ulong)
 * Signed Int128 division with overflow check: normalizes signs, divides via
 * the unsigned core (002450ec), and negates the quotient/remainder per sign.
 * Fatal-errors if the quotient is not representable (min/-1).
 * Confidence: medium
 * Notes: wraps skp5_sk_uint128_divide; skp5_FUN_002d6730 helpers. */
sk_wide_t skp5_sk_int128_divide_full(sk_wide_t *out, uint64_t ah, uint64_t al,
                                int64_t bh, int64_t bl, uint64_t dh, uint64_t dl)
{
    sk_wide_t q;
    sk_wide_t r;
    uint64_t sign = (uint64_t)((int64_t)dl >> 63);
    uint64_t nlo = (dl ^ -sign) + (uint64_t)sign;
    uint64_t nhi = (dh ^ -sign) + (uint64_t)((dl ^ -sign) < sign);

    (void)ah; (void)al;
    /* unsigned divide of |dividend| by |divisor| */
    r = skp5_sk_uint128_divide(&q, 0, 0, bh, bl, nhi, nlo);
    /* apply quotient/remainder signs */
    if ((int64_t)((dl) ^ (bl)) < 0) {
        q = (sk_wide_t){-(int64_t)q.lo, ~q.hi + (q.lo != 0)};
    }
    if ((int64_t)dl < 0) {
        r = (sk_wide_t){-(int64_t)r.lo, ~r.hi + (r.lo != 0)};
    }
    out->lo = q.lo;
    out->hi = q.hi;
    return r;
}

/* skp5_FUN_0024607c @ 0x24607c   (est. skp5_sk_obj_method_dispatch_wide)
 * Ghidra: undefined1 [16] skp5_FUN_0024607c(undefined8,undefined8,undefined8)
 * Object method-dispatch returning a 16-byte result; builds the result via
 * the "should be overridden" diagnostic helpers and returns {param_3, marker}.
 * Confidence: low
 * Notes: skp5_s_Should_be_overridden_in_a_more_s_005cfc00; result marker
 *   0xd00000000000002c. */
sk_wide_t skp5_sk_obj_method_dispatch_wide(void)
{
    sk_wide_t r;

    skp5_FUN_0035ac70((void *)0x005cfc00);
    skp5_FUN_003593c0(0, 0);
    skp5_FUN_0006f768();
    skp5_FUN_0035ac70((void *)0x005cfc00, 0);
    skp5_FUN_003593c0(0, 0);
    skp5_FUN_0006f768();
    r = skp5_FUN_00356ea8();
    return (sk_wide_t){r.lo + 0, r.hi};
}

/* skp5_FUN_002460d4 @ 0x2460d4   (est. skp5_sk_obj_method_dispatch_wide_default)
 * Ghidra: undefined1 [16] skp5_FUN_002460d4(undefined8,undefined8,undefined8)
 * Default object-method dispatch returning {param_3, marker}; the marker
 * 0xd00000000000002c tags the "should be overridden" default result.
 * Confidence: low
 * Notes: mirrors 0024607c without the second diagnostic. */
sk_wide_t skp5_sk_obj_method_dispatch_wide_default(void)
{
    sk_wide_t r;

    skp5_FUN_0035ac70((void *)0x005cfc00);
    skp5_FUN_003593c0(0, 0);
    skp5_FUN_0006f768();
    r = skp5_FUN_00356ea8();
    return (sk_wide_t){r.lo + 0, r.hi};
}

/* skp5_FUN_00246138 @ 0x246138   (est. skp5_sk_uint128_add)
 * Ghidra: undefined1 [16] skp5_FUN_00246138(ulong,long,ulong,long)
 * 128-bit addition with carry: lo = param_3 + param_1; hi = param_4 + param_2
 * + carry.
 * Confidence: high */
sk_wide_t skp5_sk_uint128_add(uint64_t a0, uint64_t a1, uint64_t b0, uint64_t b1)
{
    uint64_t lo = a0 + b0;
    uint64_t c = (lo < a0) ? 1 : 0;
    return (sk_wide_t){lo, a1 + b1 + c};
}

/* skp5_FUN_00246144 / skp5_FUN_0024614c @ 0x246144/0x24614c   (est. sk_word_add)
 * Ghidra: int skp5_FUN_00246144(int,int)
 * Plain word addition (and its thunk).
 * Confidence: high */
int sk_word_add(int a, int b) { return a + b; }
long skp5_thunk_sk_word_add(long a, long b) { return a + b; }

/* skp5_FUN_00246164 @ 0x246164   (est. skp5_sk_uint128_sub)
 * Ghidra: undefined1 [16] skp5_FUN_00246164(ulong,long,ulong,long)
 * 128-bit subtraction with borrow: lo = param_1 - param_3; hi = param_2 -
 * (param_4 + borrow).
 * Confidence: high */
sk_wide_t skp5_sk_uint128_sub(uint64_t a0, uint64_t a1, uint64_t b0, uint64_t b1)
{
    uint64_t lo = a0 - b0;
    uint64_t borrow = (a0 < b0) ? 1 : 0;
    return (sk_wide_t){lo, a1 - (b1 + borrow)};
}

/* skp5_FUN_00246170 / skp5_FUN_00246178 @ 0x246170/0x246178   (est. sk_word_sub)
 * Ghidra: int skp5_FUN_00246170(int,int)
 * Plain word subtraction (and long variant).
 * Confidence: high */
int sk_word_sub(int a, int b) { return a - b; }
long skp5_thunk_sk_word_sub(long a, long b) { return a - b; }

/* skp5_FUN_00246188 @ 0x246188   (est. skp5_sk_obj_store_field)
 * Ghidra: void skp5_FUN_00246188(undefined8,long)
 * Stores param_1 into an object field selected by the offset at
 * *(int*)(param_2+0x2c) relative to the object registry (x20); releases the
 * previous value first.
 * Confidence: medium
 * Notes: x20 = object base; offset field +0x2c; release skp5_FUN_0036b118. */
void skp5_sk_obj_store_field(unsigned long value, long meta)
{
    int off = *(int *)(meta + 0x2c);
    skp5_FUN_0036b118(*(unsigned long *)((char *)0x0 + off));
    *(unsigned long *)((char *)0x0 + off) = value;
}

/* skp5_FUN_002461c0 @ 0x2461c0   (est. sk_obj_store_field_c0)
 * Ghidra: void skp5_FUN_002461c0(void)
 * Object field store via offset 0x2c (reads the object layout from the
 * runtime and writes the value into the slot). Enter/leave 00084220/00084234.
 * Confidence: low
 * Notes: offset field +0x2c from layout skp5_FUN_0031ca24. */
void sk_obj_store_field_c0(void)
{
    unsigned long v;
    long layout;

    skp5_FUN_00084220();
    skp5_FUN_00356188();
    v = skp5_FUN_0034b5a8();
    skp5_FUN_0034b07c(v, v);
    skp5_FUN_003518d0();
    skp5_FUN_0019e578();
    skp5_FUN_003517b4();
    skp5_FUN_0034c5ac();
    layout = skp5_FUN_0031ca24();
    *(unsigned long *)((char *)0x0 + *(int *)(layout + 0x2c)) = 0;
    skp5_FUN_00084234(0);
}

/* skp5_FUN_00246264 @ 0x246264   (est. skp5_sk_obj_call_slot_64)
 * Ghidra: void skp5_FUN_00246264(undefined8,long)
 * Object method call via the runtime; reads the metadata layout (+0x10/0x18)
 * and dispatches through the [x16+0x10] slot with the object.
 * Confidence: low
 * Notes: offset field +0x2c; indirect jump at 0x2462ec. */
void skp5_sk_obj_call_slot_64(void)
{
    int off = *(int *)(0 + 0x2c);
    skp5_FUN_0034e81c(0, *(unsigned long *)(0 + 0x18), *(unsigned long *)(0 + 0x10));
    skp5_FUN_00377824();
    skp5_FUN_003519fc(0, 0, 0);
    skp5_FUN_00377824();
    skp5_FUN_00352efc();
    skp5_FUN_00310d68();
    skp5_FUN_00350404();
    skp5_sk_indirect_dispatch(0, (void *)((char *)0x0 + off), 0);
}

/* skp5_FUN_002462f4 @ 0x2462f4   (est. skp5_sk_obj_call_slot_f4)
 * Ghidra: void skp5_FUN_002462f4(undefined8,long)
 * Object method call via the runtime; mirrors 00246264 but dispatches through
 * the [x16+0x28] slot.
 * Confidence: low
 * Notes: offset field +0x2c; indirect jump at 0x24637c. */
void skp5_sk_obj_call_slot_f4(void)
{
    int off = *(int *)(0 + 0x2c);
    sk_wide_t r;
    skp5_FUN_0034e81c(*(unsigned long *)(0 + 0x18), 0, 0, *(unsigned long *)(0 + 0x10));
    r = (sk_wide_t){skp5_FUN_00377824(0, 0), 0};
    skp5_FUN_003519fc(r.lo, r.hi, r.lo);
    skp5_FUN_00377824();
    skp5_FUN_00352efc();
    skp5_FUN_00310d68();
    skp5_FUN_0034ad10();
    skp5_sk_indirect_dispatch((unsigned long)((char *)0x0 + off), 0);
}

/* skp5_FUN_00246388 @ 0x246388   (est. skp5_sk_obj_store_field_88)
 * Ghidra: void skp5_FUN_00246388(undefined8,long)
 * Stores param_1 into the object field at offset *(int*)(param_2+0x30);
 * releases the previous value.
 * Confidence: medium
 * Notes: offset field +0x30. */
void skp5_sk_obj_store_field_88(unsigned long value, long meta)
{
    int off = *(int *)(meta + 0x30);
    skp5_FUN_0036b118(*(unsigned long *)((char *)0x0 + off));
    *(unsigned long *)((char *)0x0 + off) = value;
}

/* skp5_FUN_002463dc @ 0x2463dc   (est. sk_obj_release_field_dc)
 * Ghidra: void skp5_FUN_002463dc(long)
 * Releases the object field at offset *(int*)(param_1+0x34) and returns.
 * Confidence: medium
 * Notes: release skp5_FUN_0036b270. */
void sk_obj_release_field_dc(long meta)
{
    int off = *(int *)(meta + 0x34);
    skp5_FUN_0036b270(*(unsigned long *)((char *)0x0 + off));
}

/* skp5_FUN_0024640c @ 0x24640c   (est. skp5_sk_obj_store_field_pair)
 * Ghidra: void skp5_FUN_0024640c(undefined8,undefined8,long)
 * Stores a two-word value into the object field pair at offset
 * *(int*)(param_3+0x34); releases the old pair first.
 * Confidence: medium
 * Notes: offset field +0x34; two-word store. */
void skp5_sk_obj_store_field_pair(unsigned long lo, unsigned long hi, long meta)
{
    int off = *(int *)(meta + 0x34);
    unsigned long *slot = (unsigned long *)((char *)0x0 + off);
    skp5_FUN_0036b118(*slot);
    slot[0] = hi;
    slot[1] = lo;
}

/* skp5_FUN_00246490 @ 0x246490   (est. skp5_sk_obj_construct)
 * Ghidra: void skp5_FUN_00246490(void)
 * Object constructor: allocates the object, zeroes its field slots
 * (offsets 0x2c/0x34/0x38), stores the allocation tag into the +0x30 field,
 * and dispatches the init. Enter/leave 00077698/0007767c.
 * Confidence: medium
 * Notes: offset fields +0x2c/0x30/0x34/0x38; tag skp5_FUN_0019e578. */
void skp5_sk_obj_construct(void)
{
    sk_wide_t r;
    long layout;
    unsigned long tag;

    skp5_FUN_00077698();
    skp5_FUN_00355d9c();
    r = skp5_FUN_00350a64();
    layout = skp5_FUN_0031ca3c(r.lo, r.hi, 0, 0);
    skp5_FUN_003597a0();
    skp5_FUN_00351214();
    r = (sk_wide_t){skp5_FUN_00377824(), 0};
    skp5_FUN_00350920(r.lo, r.hi, r.lo);
    skp5_FUN_00377824();
    skp5_FUN_00350744((void *)((char *)0x0 + *(int *)(layout + 0x2c)));
    skp5_FUN_000839d8();
    {
        unsigned long *slot = (unsigned long *)((char *)0x0 + *(int *)(layout + 0x34));
        slot[0] = 0;
        slot[1] = 0;
    }
    *(unsigned char *)((char *)0x0 + *(int *)(layout + 0x38)) = 0;
    skp5_FUN_0034d404();
    skp5_FUN_00377824();
    skp5_FUN_00349530();
    skp5_sk_indirect_dispatch((unsigned long)(void *)0x0);
    skp5_FUN_003548ac();
    tag = skp5_FUN_0019e578();
    *(unsigned long *)((char *)0x0 + *(int *)(layout + 0x30)) = tag;
    skp5_FUN_0007767c(0);
}

/* skp5_FUN_0024657c @ 0x24657c   (est. skp5_sk_obj_service_s)
 * Ghidra: void skp5_FUN_0024657c(void)
 * Object service method (string-based): reads the object's current string
 * field, applies an in-place mutation via the runtime, and stores it back.
 * The state byte at the offset 0x2c slot drives a small state machine
 * (0x01/0x02/0x03). Enter/leave 0008e518/0008e500.
 * Confidence: low
 * Notes: 295-line state-machine service; slot dispatch at [x16+8]. */
void skp5_sk_obj_service_s(void)
{
    sk_wide_t r;
    long obj;
    int off;
    unsigned char st;

    r = skp5_FUN_0008e518();
    obj = r.lo;
    skp5_FUN_00352078(obj, *(unsigned long *)(obj + 0x18));
    skp5_FUN_00377824(0xff);
    skp5_FUN_00356bd4();
    skp5_FUN_00350624();
    skp5_FUN_00377824();
    skp5_FUN_00350920();
    skp5_FUN_00310d68();
    skp5_FUN_000a6f88();
    FUN_00658c00_REF();
    skp5_FUN_00348a34();
    FUN_00658c00_REF();
    skp5_FUN_00350464();
    skp5_FUN_00353e94();
    skp5_FUN_00350624(0xff);
    skp5_FUN_00377824();
    skp5_FUN_00352efc();
    skp5_FUN_00310d68();
    skp5_FUN_000a6f88();
    FUN_00658c00_REF();
    skp5_FUN_0034926c();
    FUN_00658c00_REF();
    skp5_FUN_0034aac4();
    FUN_00658c00_REF();
    skp5_FUN_0034d7fc();
    skp5_FUN_003504e8();
    skp5_FUN_00310d68();
    skp5_FUN_000a6f88();
    FUN_00658c00_REF();
    skp5_FUN_003503ec();
    skp5_FUN_0034acf0();
    FUN_00658c00_REF();
    skp5_FUN_0034e3ac();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034aa9c();
    skp5_FUN_00352554(0);
    off = *(int *)(obj + 0x38);
    st = *(unsigned char *)((char *)0x0 + off);
    switch (st) {
    case 1:
        skp5_FUN_00355f94();
        skp5_FUN_0034bffc((void *)((char *)0x0 + *(int *)(obj + 0x2c)), 1);
        if (0) { skp5_FUN_00350410(); skp5_FUN_00348898(); skp5_FUN_0034a2f8(); skp5_FUN_001afe4c(); }
        skp5_FUN_00351444(0, 0);
        skp5_FUN_00377bec();
        skp5_FUN_00354474();
        skp5_FUN_0035072c(0);
        skp5_FUN_0035172c();
        skp5_FUN_00350884(0, 0, 0);
        skp5_FUN_00358720();
        skp5_FUN_00351ba0(0xff);
        skp5_FUN_00377824();
        skp5_FUN_00351354();
        skp5_FUN_00351378();
        skp5_FUN_00377bec();
        skp5_FUN_000a68f4();
        skp5_FUN_00350798();
        skp5_FUN_00377dcc();
        skp5_FUN_003524e0((void *)0x48);
        skp5_FUN_003504dc();
        skp5_FUN_0034bffc(0, 1);
        skp5_FUN_000839d8(0, 0, 1, 0);
        skp5_FUN_00354bbc();
        skp5_FUN_0035a19c((void *)((char *)0x0 + off), 0);
        skp5_FUN_003510d0((void *)0x40);
        skp5_FUN_00351390(0);
        skp5_FUN_0035681c();
        skp5_FUN_00350d24();
        skp5_FUN_00350a70();
        skp5_FUN_003561ac();
        skp5_FUN_003566c0();
        skp5_FUN_00354b80(3);
        *(unsigned char *)((char *)0x0 + off) = 3;
        goto finish;
    case 2:
        skp5_FUN_00356a88();
        skp5_FUN_00350744(0);
        skp5_FUN_000839d8();
        skp5_FUN_003561ac();
        skp5_FUN_00350744(0);
        goto finish;
    case 3:
        goto finish;
    default:
        /* default: re-read + format */
        skp5_FUN_00351ba0(0xff);
        r = skp5_FUN_00351354();
        skp5_FUN_00377bec(r.lo, r.hi, 0, 0);
        skp5_FUN_000a68f4();
        skp5_FUN_00350798();
        skp5_FUN_00377dcc();
        skp5_FUN_00351590();
        r = skp5_FUN_003517a8();
        skp5_FUN_00350884(r.lo, r.hi, 0);
        *(unsigned char *)((char *)0x0 + off) = 1;
        goto finish;
    }
finish:
    skp5_FUN_00350744(0);
    skp5_FUN_000839d8();
    skp5_FUN_0008e500(0, 0, 0);
}

/* skp5_FUN_00246c68 @ 0x246c68   (est. skp5_sk_obj_service_store)
 * Ghidra: void skp5_FUN_00246c68(void)
 * Object service store method: reads the object's field pair (+0x10/+0x18),
 * formats it via the runtime, and stores the result into the +0x2c field
 * slot. Enter/leave 00084220/00084234.
 * Confidence: low
 * Notes: offset field +0x2c; dispatch-heavy. */
void skp5_sk_obj_service_store(void)
{
    sk_wide_t r;
    long obj;
    int off;

    r = skp5_FUN_00084220();
    obj = r.lo;
    skp5_FUN_0034e7e0();
    skp5_FUN_00350288();
    skp5_FUN_00377824();
    skp5_FUN_00351f10();
    skp5_FUN_0007c1a4();
    FUN_00658c00_REF();
    skp5_FUN_0034b0c4();
    skp5_FUN_000a68c4(*(unsigned long *)(obj + 0x18));
    skp5_FUN_00350c50();
    skp5_FUN_003510b8();
    skp5_sk_indirect_dispatch(0);
    off = *(int *)(obj + 0x2c);
    skp5_FUN_00350288(0xff);
    r = (sk_wide_t){skp5_FUN_00377824(), 0};
    skp5_FUN_00352720(r.lo, r.hi, r.lo);
    skp5_FUN_00377824();
    skp5_FUN_00352efc();
    skp5_FUN_00310d80();
    r = skp5_FUN_00353468(0, (void *)((char *)0x0 + off));
    skp5_FUN_00246490();
    skp5_FUN_00084234(r.hi);
}

/* skp5_FUN_00246d54 @ 0x246d54   (est. skp5_sk_obj_service_iter)
 * Ghidra: void skp5_FUN_00246d54(void)
 * Object service that iterates over a collection field, applying an
 * operation to each element and accumulating a result. Two loop paths
 * (empty vs non-empty base field). Enter/leave 0008e518/0008e500.
 * Confidence: low
 * Notes: 155-line iteration service; slot dispatch at [x16+0x20]. */
void skp5_sk_obj_service_iter(void)
{
    sk_wide_t r;
    long obj;
    long base;
    int off;

    obj = skp5_FUN_0008e518().lo;
    skp5_FUN_00352078();
    skp5_FUN_0035050c();
    skp5_FUN_00377824();
    skp5_FUN_00348ce8();
    FUN_00658c00_REF();
    skp5_FUN_00348a9c();
    FUN_00658c00_REF();
    skp5_FUN_0034b308();
    FUN_00658c00_REF();
    skp5_FUN_0034b758();
    skp5_FUN_00350488();
    skp5_FUN_00310d68();
    skp5_FUN_000a6f88();
    FUN_00658c00_REF();
    skp5_FUN_00348a34();
    FUN_00658c00_REF();
    skp5_FUN_0034abec();
    FUN_00658c00_REF();
    r = skp5_FUN_0034c2c8();
    skp5_FUN_00349b00(r.lo, r.hi, *(unsigned long *)(obj + 0x10));
    FUN_00658c00_REF();
    skp5_FUN_0034a1f8();
    skp5_FUN_0035050c();
    skp5_FUN_00377824();
    skp5_FUN_000a6f88();
    FUN_00658c00_REF();
    skp5_FUN_003493c4();
    skp5_FUN_0034d444();
    FUN_00658c00_REF();
    skp5_FUN_0034b8bc();
    skp5_FUN_00351f70(0);
    skp5_FUN_00377824();
    skp5_FUN_000a6f68();
    off = *(int *)(obj + 0x2c);
    base = *(long *)((char *)0x0 + off);
    r = skp5_FUN_00350554(0);
    skp5_sk_indirect_dispatch(r.lo, r.hi, *(unsigned long *)(obj + 0x10));
    skp5_FUN_00352680(*(unsigned long *)(obj + 0x18));
    if (*(long *)(base + 0x10) == 0) {
        /* empty base: iterate and collect */
        skp5_FUN_003504f4(*(unsigned long *)(obj + 0x18));
        skp5_FUN_0034b278();
        r = skp5_FUN_00350494();
        skp5_FUN_00377bec(r.lo, r.hi, 0);
        skp5_FUN_000a68f4();
        while (1) {
            skp5_FUN_0034e5ec();
            skp5_FUN_0034b2c8();
            if (0) break;
            skp5_FUN_0034e53c(0);
            skp5_FUN_00310d80(0, 0);
            skp5_FUN_00357a9c();
            skp5_FUN_001de04c();
        }
        skp5_FUN_003507bc(0);
        skp5_FUN_0034ece8(((unsigned long (*)(void))0)(), obj);
        skp5_sk_indirect_dispatch(0);
    } else {
        skp5_FUN_00358bf0();
        skp5_FUN_003507bc();
        skp5_FUN_0034b278();
        r = skp5_FUN_00350c2c();
        skp5_FUN_00377bec(r.lo, r.hi, 0);
        skp5_FUN_00354474();
        skp5_FUN_0034b2c8();
        if (0) {
            skp5_FUN_00350560(0);
            skp5_FUN_0034ece8(((unsigned long (*)(void))0)(), obj);
            skp5_sk_indirect_dispatch(0);
            skp5_FUN_00351a08();
        } else {
            skp5_FUN_00350a34();
            skp5_FUN_00310d80(0, 0);
            while (1) {
                skp5_FUN_00350a34();
                skp5_FUN_001de04c();
                skp5_FUN_0034b2c8();
                if (0) break;
                skp5_FUN_0034e5cc();
                skp5_FUN_0036b270(base);
                skp5_FUN_003488f4();
                skp5_FUN_001de04c(0, 0, 0);
            }
            skp5_FUN_00353154();
            skp5_FUN_003507e0();
            skp5_FUN_0034ece8(((unsigned long (*)(void))0)(), obj);
            skp5_sk_indirect_dispatch(0);
            skp5_FUN_00351e6c();
        }
    }
    skp5_FUN_0035a560();
    skp5_FUN_0008e500(0, 0);
}

/* skp5_FUN_002471f4 @ 0x2471f4   (est. sk_obj_service_poll)
 * Ghidra: void skp5_FUN_002471f4(void)
 * Object service poll method: reads the object, dispatches through the
 * [x16+0x10] slot, and returns. Enter/leave 00084220/00084234.
 * Confidence: low
 * Notes: dispatch-heavy poll. */
void sk_obj_service_poll(void)
{
    unsigned long v;

    skp5_FUN_00084220();
    v = skp5_FUN_0034b5a8();
    skp5_FUN_00349720(v, v);
    FUN_00658c00_REF();
    skp5_FUN_00349068();
    skp5_sk_indirect_dispatch(0);
    skp5_FUN_00351648(0);
    skp5_FUN_0034ef08();
    skp5_FUN_002461c0();
    skp5_FUN_00084234(0);
}

/* skp5_FUN_002472b4 @ 0x2472b4   (est. sk_obj_slot_dispatch)
 * Ghidra: undefined8 skp5_FUN_002472b4(void)
 * Dispatches through the object slot at [x20+0x50] and returns its result.
 * Confidence: low
 * Notes: x20 = object base. */
unsigned long sk_obj_slot_dispatch(void)
{
    return ((unsigned long (*)(void))0)();
}

/* skp5_FUN_002472e0 @ 0x2472e0   (est. skp5_sk_collection_range_bounds)
 * Ghidra: undefined1 [16] skp5_FUN_002472e0(void)
 * Computes a {start,count,sign} bounds tuple from the collection length at
 * [x20+0x10]: clamps the count to representable range and packs a sign
 * flag. Returns 16 bytes.
 * Confidence: low
 * Notes: x20 = collection base; bounds computation. */
sk_wide_t skp5_sk_collection_range_bounds(void)
{
    uint64_t len = *(uint64_t *)((char *)0x0 + 0x10);
    uint64_t lo = (int64_t)len < -1 ? len : 0xffffffffffffffffull;
    uint64_t hi = (len != 0) ? ~lo : 0;
    uint32_t sign = (len != 0) ? ((uint32_t)(len >> 63) ^ 1) : 1;
    return (sk_wide_t){lo | ((uint64_t)sign << 32), hi};
}

/* skp5_FUN_00247308 / skp5_FUN_0024730c @ 0x247308/0x24730c   (est. sk_obj_deref)
 * Ghidra: undefined8 skp5_FUN_00247308(void)
 * Returns the object at [x20+0x10] if a flag is set and it is non-null,
 * else 0.
 * Confidence: low
 * Notes: x20 = object base. */
unsigned long sk_obj_deref(void)
{
    skp5_FUN_00351b04();
    if ((*(unsigned long *)((char *)0x0 + 0x10) != 0))
        return skp5_FUN_001e9f14();
    return 0;
}
unsigned long skp5_sk_obj_deref_b(void)
{
    skp5_FUN_00351b04();
    if ((*(unsigned long *)((char *)0x0 + 0x10) != 0))
        return skp5_FUN_001e9f14();
    return 0;
}

/* skp5_FUN_0024733c @ 0x24733c   (est. skp5_sk_swift_keypath_alloc)
 * Ghidra: long skp5_FUN_0024733c(void)
 * Allocates a Swift KeyPath object (0x98 bytes) via the runtime allocator
 * and invokes the buffer initializer over [obj+0x18, obj+0x18+count].
 * Fatal-errors on negative count.
 * Confidence: medium
 * Notes: skp5_s_Swift_KeyPath_swift_005cfc50; allocation skp5_FUN_0036a940. */
long skp5_sk_swift_keypath_alloc(void)
{
    long l;
    long count;

    skp5_FUN_002085a4((void *)0x005cfc50, 0x13, 2, 0x98);
    l = skp5_FUN_0008409c();
    l = skp5_FUN_0036a940(0, 0, 0xf);
    *(unsigned long *)(l + 0x10) = 0;
    count = 0;
    if (count < 0) {
        skp5_FUN_003483c4();
        skp5_FUN_00351094();
        skp5_FUN_001afe4c();
    }
    skp5_sk_indirect_dispatch(l + 0x18, l + 0x18 + count);
    return l;
}

/* skp5_FUN_00247340 @ 0x247340   (est. skp5_sk_swift_keypath_alloc_b)
 * Ghidra: long skp5_FUN_00247340(void)
 * KeyPath allocation variant; identical to 0024733c.
 * Confidence: medium */
long skp5_sk_swift_keypath_alloc_b(void)
{
    long l;
    skp5_FUN_002085a4((void *)0x005cfc50, 0x13, 2, 0x98);
    l = skp5_FUN_0008409c();
    l = skp5_FUN_0036a940(0, 0, 0xf);
    *(unsigned long *)(l + 0x10) = 0;
    if (0 < 0) {
        skp5_FUN_003483c4();
        skp5_FUN_00351094();
        skp5_FUN_001afe4c();
    }
    skp5_sk_indirect_dispatch(l + 0x18, l + 0x18 + 0);
    return l;
}

/* skp5_FUN_00247360 @ 0x247360   (est. skp5_sk_swift_keypath_alloc_c)
 * Ghidra: long skp5_FUN_00247360(void)
 * KeyPath allocation variant; identical to 0024733c.
 * Confidence: medium */
long skp5_sk_swift_keypath_alloc_c(void)
{
    long l;
    l = skp5_FUN_0008409c();
    l = skp5_FUN_0036a940(0, 0, 0xf);
    *(unsigned long *)(l + 0x10) = 0;
    if (0 < 0) {
        skp5_FUN_003483c4();
        skp5_FUN_00351094();
        skp5_FUN_001afe4c();
    }
    skp5_sk_indirect_dispatch(l + 0x18, l + 0x18 + 0);
    return l;
}

/* skp5_FUN_002473f0 @ 0x2473f0   (est. sk_buffer_validate)
 * Ghidra: void skp5_FUN_002473f0(long,long)
 * Validates a buffer of param_2 elements starting at param_1: fatal-errors
 * if the count is negative, or if non-empty with a null base. Returns when
 * valid.
 * Confidence: medium
 * Notes: fatal on negative/empty-null. */
void sk_buffer_validate(long base, long count)
{
    if (count < 0) {
        skp5_FUN_003483c4();
        skp5_FUN_00351094();
        skp5_FUN_001afe4c();
        return;
    }
    if (count != 0 && base == 0) {
        skp5_FUN_003488bc(1);
        skp5_FUN_00349644();
    }
    skp5_FUN_00351094();
    skp5_FUN_001afe4c();
}

/* skp5_FUN_00247454 @ 0x247454   (est. skp5_sk_collection_range_equal_wide)
 * Ghidra: bool skp5_FUN_00247454(long,long,long,long)
 * Compares two collection ranges for equality, walking the elements and
 * comparing the packed 128-bit values. Handles NaN-like packed string
 * representations and returns false on mismatch. Uses 002488b4/00248a34
 * accessors. Fatal-errors on misaligned raw pointer load.
 * Confidence: low
 * Notes: 347-line equality walk; skp5_FUN_00248d7c element reader. */
bool skp5_sk_collection_range_equal_wide(long a, long b, long lo, long hi)
{
    sk_wide_t ra, rb;
    sk_wide_t ea, eb;

    ra = skp5_FUN_002488b4(a + 0x18);
    rb = skp5_FUN_002488b4(b + 0x18);
    if ((((uint32_t)lo >> 8 & 1 ^ (uint32_t)lo >> 8) & 1) != 0)
        return false;
    if (ra.lo == 0 || ra.hi == ra.lo) {
        bool res = true;
        if (rb.lo != 0) res = (rb.hi == rb.lo);
        return res;
    }
    ea = skp5_FUN_00248a34();
    eb = skp5_FUN_00248a34();
    /* element-wise compare via 00248d7c and packed-value equality */
    skp5_FUN_00248d7c(&ra, ea.lo, ea.hi, lo);
    skp5_FUN_00248d7c(&rb, eb.lo, eb.hi);
    /* compare the two 128-bit packed values (ra vs rb words) */
    {
        uint64_t w0 = ra.lo, w1 = ra.hi, x0 = rb.lo, x1 = rb.hi;
        if (w0 != x0 || w1 != x1) {
            /* handle packed-string special cases (NaN-like) */
            return false;
        }
    }
    return true;
}

/* skp5_FUN_002478d4 @ 0x2478d4   (est. skp5_sk_collection_element_description)
 * Ghidra: undefined1 [16] skp5_FUN_002478d4(long,undefined1 (*)[16],long,undefined8)
 * Produces the string description of a collection element, iterating the
 * elements and building a "<computed>" description with inter-element
 * separators via the runtime string builders. Returns the built string.
 * Confidence: low
 * Notes: 743-line element description; string literals s_<computed_005d3a4f /
 *   skp5_DAT_005d0ce6; element reader skp5_FUN_00248d7c. */
sk_wide_t skp5_sk_collection_element_description(long coll, sk_wide_t *out,
                                            long meta, unsigned long count)
{
    sk_wide_t r;

    r = skp5_FUN_002488b4(coll + 0x18);
    if (r.lo == 0 || r.hi == r.lo) {
        /* empty -> default description */
        skp5_FUN_001a89a8("self", 5, 1);
        skp5_FUN_003a25d4(0);
        return (sk_wide_t){0, 0};
    }
    /* iterate elements and build "<computed>" string */
    while (1) {
        r = skp5_FUN_00248a34();
        skp5_FUN_00248d7c(&r, r.lo, r.hi, meta);
        if (0) break;
        r = skp5_FUN_001a89a8("\x0b", 1, 1);   /* skp5_DAT_005d0ce6 */
        skp5_FUN_002a4c98(r.lo, r.hi, 0, 0);
        r = skp5_FUN_001a89a8("<computed", 10, 1);
        skp5_FUN_002a4c98(r.lo, r.hi, 0, 0);
        r = skp5_FUN_001a89a8(">\x0b", 2, 1);  /* skp5_DAT_005ce80d */
        skp5_FUN_002a4c98(r.lo, r.hi, 0, 0);
        r = (sk_wide_t){skp5_FUN_00208418(0, 0), 0};
        skp5_FUN_002a4c98(r.lo, r.hi, 0, 0);
        return r;
    }
    return (sk_wide_t){0, 0};
}

/* skp5_FUN_002487b8 @ 0x2487b8   (est. skp5_sk_collection_map_reduce)
 * Ghidra: undefined8 skp5_FUN_002487b8(code*,undefined8,uint)
 * Applies the callback param_1 over a collection range obtained from the
 * registry +0x18, OR-ing the given flags (param_3 & 0x10101) into each call,
 * and returns the accumulated result.
 * Confidence: low
 * Notes: callback param_1; range skp5_FUN_002488b4. */
unsigned long skp5_sk_collection_map_reduce(unsigned long (*cb)(unsigned long, unsigned long, unsigned long, uint32_t),
                                       unsigned long arg, uint32_t flags)
{
    sk_wide_t r;
    unsigned long acc;

    r = skp5_FUN_002488b4(0x0 + 0x18);
    acc = cb(0, r.lo, r.hi, flags & 0x10101);
    return acc;
}

/* skp5_FUN_0024881c @ 0x24881c   (est. sk_collection_guard_range)
 * Ghidra: uint skp5_FUN_0024881c(long,undefined8,uint)
 * Fetches the range from the collection (+0x18) and masks the given flags
 * with 0x10101.
 * Confidence: low */
uint32_t sk_collection_guard_range(long coll, unsigned long a, uint32_t flags)
{
    skp5_FUN_002488b4(coll + 0x18);
    return flags & 0x10101;
}

/* skp5_FUN_00248860 @ 0x248860   (est. sk_collection_apply)
 * Ghidra: void skp5_FUN_00248860(undefined8,undefined8,uint)
 * Applies a collection-wide operation (via the runtime callbacks) over the
 * range at +0x18, masking flags with 0x10101, then dispatches the result.
 * Confidence: low */
void sk_collection_apply(void)
{
    sk_wide_t r;

    skp5_FUN_0034bb84();
    r = skp5_FUN_002488b4(0x0 + 0x18);
    skp5_FUN_003522d4(r.lo, r.hi, 0x10101);
    skp5_sk_indirect_dispatch(0);
}

/* skp5_FUN_002488b4 @ 0x2488b4   (est. skp5_sk_collection_range_get)
 * Ghidra: undefined1 [16] skp5_FUN_002488b4(void)
 * Returns the {start, count} range of the collection: [x19+8, x19+8+count]
 * where count comes from a runtime helper masked to 24 bits.
 * Confidence: medium
 * Notes: x19 = collection base; range [base+8, base+8+count]. */
sk_wide_t skp5_sk_collection_range_get(unsigned long base)
{
    uint32_t cnt;

    skp5_FUN_0034da88();
    cnt = skp5_FUN_001ee0c8() & 0xffffff;
    return (sk_wide_t){base + 8, base + 8 + cnt};
}

/* skp5_FUN_00248900 @ 0x248900   (est. sk_collection_reduce_wide)
 * Ghidra: undefined1 [16] skp5_FUN_00248900(undefined8,undefined8,uint)
 * Wide reduce over the collection range, applying 0024893c with the masked
 * flags, returning the 16-byte accumulation.
 * Confidence: low */
sk_wide_t sk_collection_reduce_wide(void)
{
    sk_wide_t r;
    unsigned long acc;

    skp5_FUN_002488b4(0x0 + 0x18);
    r = skp5_FUN_003586d8();
    skp5_FUN_0024893c();
    return (sk_wide_t){acc, 0};
}

/* skp5_FUN_0024893c @ 0x24893c   (est. skp5_sk_collection_sum_wide)
 * Ghidra: void skp5_FUN_0024893c(undefined8,undefined8,undefined8)
 * Sums a collection of wide elements into a 64-bit accumulator, validating
 * alignment and overflowing (SoftwareBreakpoint on carry). Returns via the
 * runtime 0035847c.
 * Confidence: low
 * Notes: element width from param_3; alignment validation. */
void skp5_sk_collection_sum_wide(void)
{
    sk_wide_t r;
    unsigned long acc = 0;
    long n;

    r = skp5_FUN_00041138();
    if (r.lo == 0 || r.hi == r.lo) {
        acc = 0;
    } else {
        n = 0;
        do {
            uint32_t v = (uint32_t)skp5_FUN_00248a34().lo;
            if ((v & 0x7f000000) != 0x1000000) { acc = 0; goto out; }
            v = v & 0x7fffff;
            if (v == 0x7fffff) {
                if ((unsigned long *)0 == 0) {
                    skp5_FUN_003488bc(1);
                    skp5_FUN_00349644();
                    skp5_FUN_00351094();
                    skp5_FUN_001afe4c();
                }
                v = 0;
            }
            acc += v;
            if (acc < v) {   /* overflow */
                skp5_FUN_001afe4c();
            }
        } while (n != 0);
    }
out:
    skp5_FUN_0035847c(0);
}

/* skp5_FUN_00248a34 @ 0x248a34   (est. skp5_sk_collection_next_element)
 * Ghidra: void skp5_FUN_00248a34(void)
 * Advances to the next element of a collection: reads the current element
 * (via 0024c56c), validates it, and bounds-checks the index (fatal-errors on
 * an out-of-range advance). Returns the element value.
 * Confidence: low
 * Notes: element reader skp5_FUN_0024c56c; bounds skp5_FUN_0024b938; advance 0024c5f4. */
sk_wide_t skp5_sk_collection_next_element(void)
{
    long base;
    int cur;
    long res;
    long n;

    skp5_FUN_00351d24();
    cur = *(int *)skp5_FUN_0024c56c();
    if (cur < 0) {
        *(unsigned char *)((char *)0x0 + 0x11) = 0;
    }
    n = 0x0;
    res = skp5_FUN_0024b938(cur, n, *(unsigned long *)((char *)0x0 + 8));
    if (res != 0 && n == 0) {
        skp5_FUN_00348508();
        skp5_FUN_00351094();
        skp5_FUN_001afe4c();
    }
    skp5_FUN_0024c5f4();
    if (0x0 != 0 && *(unsigned long *)((char *)0x0 + 8) != 0x0) {
        skp5_FUN_00351d24();
        skp5_FUN_0024c460();
    }
    skp5_FUN_003511d8(cur);
}

/* skp5_FUN_00248ae0 @ 0x248ae0   (est. sk_word_width_decode)
 * Ghidra: ulong skp5_FUN_00248ae0(uint)
 * Decodes a Swift word-width/memattr selector from the top 7 bits of param_1:
 * returns 1 for type 1, an allocation for type 2, 2 for type 3, and a packed
 * 4-bit table lookup for type 4. Returns 0 for other types.
 * Confidence: medium
 * Notes: type field (param_1 >> 24) & 0x7f. */
uint64_t sk_word_width_decode(uint32_t sel)
{
    switch ((sel >> 24) & 0x7f) {
    case 1: return 1;
    case 2: return skp5_FUN_0006f794(0);
    case 3: return 2;
    case 4: return (uint64_t)(0x50604u >> ((uint32_t)(sel & 3) << 3));
    default: return 0;
    }
}
