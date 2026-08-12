/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * Slice 09: addresses 0x2dd890 - 0x2e6e84 (157 functions). This region is
 * dominated by the embedded Swift stdlib / runtime: Int128 & UInt128
 * arithmetic (shifts, division/modulo, from-string parsing), IEEE-754
 * Float16/float/double formatting and conversion helpers, Unsafe*Pointer
 * bounds-check/fatal-error paths, and a family of Swift object-service
 * dispatch loops (heavy indirect dispatch through a shared method slot).
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

typedef unsigned short sk_f16_t;             /* IEEE-754 binary16 (Swift Float16) */
typedef struct { unsigned long lo, hi; } sk_u128_t;  /* Swift Int128/UInt128 */
typedef unsigned long (*sk_fn)();          /* Swift method-dispatch slot / code * */
typedef unsigned long undefined7;          /* 7-byte half of a CONCAT value */

/* Noreturn Swift fatal-error raiser (module/message/file/line encoded). */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */

/* Data / string constants referenced by this region (address in comment). */
extern unsigned char sk_dat_004c1010[256];
extern unsigned long sk_dat_004e7b60;
extern unsigned long sk_dat_004e7b68;
extern unsigned char sk_dat_004e8108[];
extern unsigned char sk_dat_004e8110[];
extern unsigned char sk_dat_004e8118[];
extern unsigned char sk_dat_004ec5ac[256];
extern unsigned char sk_dat_004ec600[256];
extern const unsigned long sk_tab_004f1998[64];
extern const unsigned long sk_tab_004f19a0[64];
extern const unsigned long sk_tab_004f1b68[64];
extern const unsigned long sk_tab_004f1b70[64];
extern const unsigned long sk_tab_004f1fc0[64];
extern const unsigned char sk_tab_004f1ee8[16];
extern const unsigned short sk_tab_004f1ef8[128];
extern const unsigned char sk_tab_005be7c0[16];
extern const unsigned char sk_tab_005d0fa9[16];
extern char sk_str_005cd680[];   /* "Swift.Integers" */
extern char sk_str_005cd710[];   /* "Division by zero" */
extern char sk_str_005cd650[];   /* "Not enough bits to represent the ..." */
extern char sk_str_005cd6a0[];   /* "Not enough bits to represent a ..." */
extern char sk_str_005cfb40[];   /* "Distance is not representable in ..." */
extern char sk_str_005ce4a0[];   /* "Division by zero in remainder operation" */
extern char sk_str_005cfa58[];   /* "Invalid slice" */
extern char sk_str_005ce190[];   /* "Negative value is not representable ..." */
extern char sk_str_005cf3f0[];   /* "UnsafeMutablePointer.update ..." */
extern char sk_str_005ce1c0[];   /* "unsafelyUnwrapped of nil optional" */
extern char sk_str_005ce1f0[];   /* "Swift.Optional" */
extern char sk_str_005d0570[];   /* "buffer cannot contain every element ..." */
extern char sk_str_005d1010[];   /* "Swift.UInt128" */
extern char sk_str_005cdc10[];   /* "Swift.UnsafeBufferPointer" */
extern char sk_str_005cdc30[];   /* "UnsafeMutableBufferPointer has a ..." */
extern char sk_str_005cdbe0[];   /* "UnsafeMutableBufferPointer with ..." */
extern char sk_str_005cde40[];   /* "Swift.UnsafeRawBufferPointer" */
extern char sk_str_005cde70[];   /* "UnsafeMutableRawBufferPointer wi..." */
extern char sk_str_005d3070[];   /* "Value is outside the representable ..." */
extern char sk_str_005d0fb0[];   /* "value cannot be converted to UIn..." */
extern char sk_str_005accd0[];   /* "Fatal error" */
extern char sk_str_004e7a30[];   /* obfuscated 25-char string */
extern sk_fn sk_g_dispatch;      /* DAT_00658c00 — shared Swift method-dispatch slot */

/* Out-of-range kernel/Swift helpers referenced by this region (FUN_ addr in
 * comment). Reconstructed by sibling SK range workers. Declared with
 * unspecified-parameter lists since exact prototypes vary. */
extern unsigned long sk_h_00002534();  /* FUN_00002534 */
extern unsigned long sk_h_000026e8();  /* FUN_000026e8 */
extern unsigned long sk_h_00007d00();  /* FUN_00007d00 */
extern unsigned long sk_h_00012568();  /* FUN_00012568 */
extern unsigned long sk_h_00019858();  /* FUN_00019858 */
extern unsigned long sk_h_0001a1c8();  /* FUN_0001a1c8 */
extern unsigned long sk_h_0001df60();  /* FUN_0001df60 */
extern unsigned long sk_h_0001e790();  /* FUN_0001e790 */
extern unsigned long sk_h_00027754();  /* FUN_00027754 */
extern unsigned long sk_h_000651bc();  /* FUN_000651bc */
extern unsigned long sk_h_0006b2ec();  /* FUN_0006b2ec */
extern unsigned long sk_h_0006b6f4();  /* FUN_0006b6f4 */
extern unsigned long sk_h_0006f768();  /* FUN_0006f768 */
extern unsigned long sk_h_00077070();  /* FUN_00077070 */
extern unsigned long sk_h_000778b4();  /* FUN_000778b4 */
extern unsigned long sk_h_0007c028();  /* FUN_0007c028 */
extern unsigned long sk_h_0007c1a4();  /* FUN_0007c1a4 */
extern unsigned long sk_h_000839d8();  /* FUN_000839d8 */
extern unsigned long sk_h_000839f8();  /* FUN_000839f8 */
extern unsigned long sk_h_0008409c();  /* FUN_0008409c */
extern unsigned long sk_h_00084180();  /* FUN_00084180 */
extern unsigned long sk_h_00084220();  /* FUN_00084220 */
extern unsigned long sk_h_00084234();  /* FUN_00084234 */
extern unsigned long sk_h_0008e388();  /* FUN_0008e388 */
extern unsigned long sk_h_0008e500();  /* FUN_0008e500 */
extern unsigned long sk_h_0008e518();  /* FUN_0008e518 */
extern unsigned long sk_h_0008f6c0();  /* FUN_0008f6c0 */
extern unsigned long sk_h_0008f6f4();  /* FUN_0008f6f4 */
extern unsigned long sk_h_0008f728();  /* FUN_0008f728 */
extern unsigned long sk_h_0008f758();  /* FUN_0008f758 */
extern unsigned long sk_h_0009461c();  /* FUN_0009461c */
extern unsigned long sk_h_000a6f68();  /* FUN_000a6f68 */
extern unsigned long sk_h_000b4390();  /* FUN_000b4390 */
extern unsigned long sk_h_000b43d0();  /* FUN_000b43d0 */
extern unsigned long sk_h_000dbd0c();  /* FUN_000dbd0c */
extern unsigned long sk_h_000dbe0c();  /* FUN_000dbe0c */
extern unsigned long sk_h_000e15d8();  /* FUN_000e15d8 */
extern unsigned long sk_h_00100efc();  /* FUN_00100efc */
extern unsigned long sk_h_0010d2a8();  /* FUN_0010d2a8 */
extern unsigned long sk_h_0010d6b4();  /* FUN_0010d6b4 */
extern unsigned long sk_h_00117cc4();  /* FUN_00117cc4 */
extern unsigned long sk_h_00117d14();  /* FUN_00117d14 */
extern unsigned long sk_h_0011d7e8();  /* FUN_0011d7e8 */
extern unsigned long sk_h_0011db10();  /* FUN_0011db10 */
extern unsigned long sk_h_0011db18();  /* FUN_0011db18 */
extern unsigned long sk_h_0011e71c();  /* FUN_0011e71c */
extern unsigned long sk_h_0016186c();  /* FUN_0016186c */
extern unsigned long sk_h_0016791c();  /* FUN_0016791c */
extern unsigned long sk_h_0017e880();  /* FUN_0017e880 */
extern unsigned long sk_h_0019cc64();  /* FUN_0019cc64 */
extern unsigned long sk_h_001a0194();  /* FUN_001a0194 */
extern unsigned long sk_h_001a0354();  /* FUN_001a0354 */
extern unsigned long sk_h_001a15c4();  /* FUN_001a15c4 */
extern unsigned long sk_h_001a168c();  /* FUN_001a168c */
extern unsigned long sk_h_001a26e0();  /* FUN_001a26e0 */
extern unsigned long sk_h_001a5ff8();  /* FUN_001a5ff8 */
extern unsigned long sk_h_001a84f4();  /* FUN_001a84f4 */
extern unsigned long sk_h_001a8564();  /* FUN_001a8564 */
extern unsigned long sk_h_001a89a8();  /* FUN_001a89a8 */
extern unsigned long sk_h_001afe4c();  /* FUN_001afe4c */
extern unsigned long sk_h_001b4748();  /* FUN_001b4748 */
extern unsigned long sk_h_001b4d10();  /* FUN_001b4d10 */
extern unsigned long sk_h_001bb69c();  /* FUN_001bb69c */
extern unsigned long sk_h_001d3b98();  /* FUN_001d3b98 */
extern unsigned long sk_h_001d7bb0();  /* FUN_001d7bb0 */
extern unsigned long sk_h_001d9840();  /* FUN_001d9840 */
extern unsigned long sk_h_001e3430();  /* FUN_001e3430 */
extern unsigned long sk_h_001e4cbc();  /* FUN_001e4cbc */
extern unsigned long sk_h_001e64ec();  /* FUN_001e64ec */
extern unsigned long sk_h_001e695c();  /* FUN_001e695c */
extern unsigned long sk_h_001e7664();  /* FUN_001e7664 */
extern unsigned long sk_h_001e9cd0();  /* FUN_001e9cd0 */
extern unsigned long sk_h_001ee030();  /* FUN_001ee030 */
extern unsigned long sk_h_00200b38();  /* FUN_00200b38 */
extern unsigned long sk_h_00200bd0();  /* FUN_00200bd0 */
extern unsigned long sk_h_00200bf4();  /* FUN_00200bf4 */
extern unsigned long sk_h_00223960();  /* FUN_00223960 */
extern unsigned long sk_h_00224114();  /* FUN_00224114 */
extern unsigned long sk_h_0022a4a8();  /* FUN_0022a4a8 */
extern unsigned long sk_h_0022a5cc();  /* FUN_0022a5cc */
extern unsigned long sk_h_0022aaac();  /* FUN_0022aaac */
extern unsigned long sk_h_0022b21c();  /* FUN_0022b21c */
extern unsigned long sk_h_0022cde0();  /* FUN_0022cde0 */
extern unsigned long sk_h_00231c18();  /* FUN_00231c18 */
extern unsigned long sk_h_002322fc();  /* FUN_002322fc */
extern unsigned long sk_h_00235398();  /* FUN_00235398 */
extern unsigned long sk_h_002366a0();  /* FUN_002366a0 */
extern unsigned long sk_h_0023b254();  /* FUN_0023b254 */
extern unsigned long sk_h_0024304c();  /* FUN_0024304c */
extern unsigned long sk_h_002450ec();  /* FUN_002450ec */
extern unsigned long sk_h_002514f0();  /* FUN_002514f0 */
extern unsigned long sk_h_002943ec();  /* FUN_002943ec */
extern unsigned long sk_h_00294468();  /* FUN_00294468 */
extern unsigned long sk_h_002944e4();  /* FUN_002944e4 */
extern unsigned long sk_h_0029468c();  /* FUN_0029468c */
extern unsigned long sk_h_0029ac08();  /* FUN_0029ac08 */
extern unsigned long sk_h_0029ad14();  /* FUN_0029ad14 */
extern unsigned long sk_h_0029e8dc();  /* FUN_0029e8dc */
extern unsigned long sk_h_002a3e64();  /* FUN_002a3e64 */
extern unsigned long sk_h_002a55c0();  /* FUN_002a55c0 */
extern unsigned long sk_h_002a9ba8();  /* FUN_002a9ba8 */
extern unsigned long sk_h_002ab8ac();  /* FUN_002ab8ac */
extern unsigned long sk_h_002b141c();  /* FUN_002b141c */
extern unsigned long sk_h_002b24b8();  /* FUN_002b24b8 */
extern unsigned long sk_h_002b3978();  /* FUN_002b3978 */
extern unsigned long sk_h_002b39b4();  /* FUN_002b39b4 */
extern unsigned long sk_h_002dc748();  /* FUN_002dc748 */
extern unsigned long sk_h_003109b4();  /* FUN_003109b4 */
extern unsigned long sk_h_00310a14();  /* FUN_00310a14 */
extern unsigned long sk_h_00310a44();  /* FUN_00310a44 */
extern unsigned long sk_h_00310a74();  /* FUN_00310a74 */
extern unsigned long sk_h_00310ad4();  /* FUN_00310ad4 */
extern unsigned long sk_h_00310c44();  /* FUN_00310c44 */
extern unsigned long sk_h_00310d68();  /* FUN_00310d68 */
extern unsigned long sk_h_00311cf8();  /* FUN_00311cf8 */
extern unsigned long sk_h_0031b760();  /* FUN_0031b760 */
extern unsigned long sk_h_0031b778();  /* FUN_0031b778 */
extern unsigned long sk_h_0031bfb0();  /* FUN_0031bfb0 */
extern unsigned long sk_h_0031c430();  /* FUN_0031c430 */
extern unsigned long sk_h_0031c580();  /* FUN_0031c580 */
extern unsigned long sk_h_0031d910();  /* FUN_0031d910 */
extern unsigned long sk_h_0031d928();  /* FUN_0031d928 */
extern unsigned long sk_h_0031f4e4();  /* FUN_0031f4e4 */
extern unsigned long sk_h_003249ac();  /* FUN_003249ac */
extern unsigned long sk_h_00324c34();  /* FUN_00324c34 */
extern unsigned long sk_h_00324c4c();  /* FUN_00324c4c */
extern unsigned long sk_h_00324c80();  /* FUN_00324c80 */
extern unsigned long sk_h_00324ca0();  /* FUN_00324ca0 */
extern unsigned long sk_h_00343d48();  /* FUN_00343d48 */
extern unsigned long sk_h_00343d78();  /* FUN_00343d78 */
extern unsigned long sk_h_00343da8();  /* FUN_00343da8 */
extern unsigned long sk_h_00344d4c();  /* FUN_00344d4c */
extern unsigned long sk_h_00344e54();  /* FUN_00344e54 */
extern unsigned long sk_h_00347d60();  /* FUN_00347d60 */
extern unsigned long sk_h_00347da8();  /* FUN_00347da8 */
extern unsigned long sk_h_00347fb4();  /* FUN_00347fb4 */
extern unsigned long sk_h_00348034();  /* FUN_00348034 */
extern unsigned long sk_h_00348074();  /* FUN_00348074 */
extern unsigned long sk_h_0034834c();  /* FUN_0034834c */
extern unsigned long sk_h_00348404();  /* FUN_00348404 */
extern unsigned long sk_h_003484e4();  /* FUN_003484e4 */
extern unsigned long sk_h_003485f0();  /* FUN_003485f0 */
extern unsigned long sk_h_003487a4();  /* FUN_003487a4 */
extern unsigned long sk_h_003487f8();  /* FUN_003487f8 */
extern unsigned long sk_h_0034887c();  /* FUN_0034887c */
extern unsigned long sk_h_00348898();  /* FUN_00348898 */
extern unsigned long sk_h_003488bc();  /* FUN_003488bc */
extern unsigned long sk_h_00348a18();  /* FUN_00348a18 */
extern unsigned long sk_h_00348b7c();  /* FUN_00348b7c */
extern unsigned long sk_h_00348bd8();  /* FUN_00348bd8 */
extern unsigned long sk_h_00348d64();  /* FUN_00348d64 */
extern unsigned long sk_h_00348e00();  /* FUN_00348e00 */
extern unsigned long sk_h_00348e78();  /* FUN_00348e78 */
extern unsigned long sk_h_00348f38();  /* FUN_00348f38 */
extern unsigned long sk_h_00348f50();  /* FUN_00348f50 */
extern unsigned long sk_h_003490ec();  /* FUN_003490ec */
extern unsigned long sk_h_00349178();  /* FUN_00349178 */
extern unsigned long sk_h_003492cc();  /* FUN_003492cc */
extern unsigned long sk_h_00349370();  /* FUN_00349370 */
extern unsigned long sk_h_003493ac();  /* FUN_003493ac */
extern unsigned long sk_h_003494b4();  /* FUN_003494b4 */
extern unsigned long sk_h_003494e8();  /* FUN_003494e8 */
extern unsigned long sk_h_003494fc();  /* FUN_003494fc */
extern unsigned long sk_h_00349530();  /* FUN_00349530 */
extern unsigned long sk_h_00349644();  /* FUN_00349644 */
extern unsigned long sk_h_003496b0();  /* FUN_003496b0 */
extern unsigned long sk_h_00349830();  /* FUN_00349830 */
extern unsigned long sk_h_0034987c();  /* FUN_0034987c */
extern unsigned long sk_h_003499dc();  /* FUN_003499dc */
extern unsigned long sk_h_00349a04();  /* FUN_00349a04 */
extern unsigned long sk_h_00349b3c();  /* FUN_00349b3c */
extern unsigned long sk_h_00349b50();  /* FUN_00349b50 */
extern unsigned long sk_h_00349d58();  /* FUN_00349d58 */
extern unsigned long sk_h_00349e8c();  /* FUN_00349e8c */
extern unsigned long sk_h_00349f3c();  /* FUN_00349f3c */
extern unsigned long sk_h_00349fa4();  /* FUN_00349fa4 */
extern unsigned long sk_h_0034a000();  /* FUN_0034a000 */
extern unsigned long sk_h_0034a224();  /* FUN_0034a224 */
extern unsigned long sk_h_0034a2f8();  /* FUN_0034a2f8 */
extern unsigned long sk_h_0034a37c();  /* FUN_0034a37c */
extern unsigned long sk_h_0034a464();  /* FUN_0034a464 */
extern unsigned long sk_h_0034a478();  /* FUN_0034a478 */
extern unsigned long sk_h_0034a4a4();  /* FUN_0034a4a4 */
extern unsigned long sk_h_0034a5c8();  /* FUN_0034a5c8 */
extern unsigned long sk_h_0034aa3c();  /* FUN_0034aa3c */
extern unsigned long sk_h_0034ab20();  /* FUN_0034ab20 */
extern unsigned long sk_h_0034ad00();  /* FUN_0034ad00 */
extern unsigned long sk_h_0034ae94();  /* FUN_0034ae94 */
extern unsigned long sk_h_0034af20();  /* FUN_0034af20 */
extern unsigned long sk_h_0034b05c();  /* FUN_0034b05c */
extern unsigned long sk_h_0034b07c();  /* FUN_0034b07c */
extern unsigned long sk_h_0034b0d4();  /* FUN_0034b0d4 */
extern unsigned long sk_h_0034b13c();  /* FUN_0034b13c */
extern unsigned long sk_h_0034b368();  /* FUN_0034b368 */
extern unsigned long sk_h_0034b3e8();  /* FUN_0034b3e8 */
extern unsigned long sk_h_0034b460();  /* FUN_0034b460 */
extern unsigned long sk_h_0034b518();  /* FUN_0034b518 */
extern unsigned long sk_h_0034b730();  /* FUN_0034b730 */
extern unsigned long sk_h_0034b758();  /* FUN_0034b758 */
extern unsigned long sk_h_0034b778();  /* FUN_0034b778 */
extern unsigned long sk_h_0034b918();  /* FUN_0034b918 */
extern unsigned long sk_h_0034b9e8();  /* FUN_0034b9e8 */
extern unsigned long sk_h_0034ba18();  /* FUN_0034ba18 */
extern unsigned long sk_h_0034ba38();  /* FUN_0034ba38 */
extern unsigned long sk_h_0034be54();  /* FUN_0034be54 */
extern unsigned long sk_h_0034c034();  /* FUN_0034c034 */
extern unsigned long sk_h_0034c2d8();  /* FUN_0034c2d8 */
extern unsigned long sk_h_0034c308();  /* FUN_0034c308 */
extern unsigned long sk_h_0034c3f4();  /* FUN_0034c3f4 */
extern unsigned long sk_h_0034c434();  /* FUN_0034c434 */
extern unsigned long sk_h_0034c5ac();  /* FUN_0034c5ac */
extern unsigned long sk_h_0034c60c();  /* FUN_0034c60c */
extern unsigned long sk_h_0034c818();  /* FUN_0034c818 */
extern unsigned long sk_h_0034c9e8();  /* FUN_0034c9e8 */
extern unsigned long sk_h_0034ce18();  /* FUN_0034ce18 */
extern unsigned long sk_h_0034ce78();  /* FUN_0034ce78 */
extern unsigned long sk_h_0034cea8();  /* FUN_0034cea8 */
extern unsigned long sk_h_0034cf84();  /* FUN_0034cf84 */
extern unsigned long sk_h_0034cf94();  /* FUN_0034cf94 */
extern unsigned long sk_h_0034d150();  /* FUN_0034d150 */
extern unsigned long sk_h_0034d180();  /* FUN_0034d180 */
extern unsigned long sk_h_0034d264();  /* FUN_0034d264 */
extern unsigned long sk_h_0034d2b4();  /* FUN_0034d2b4 */
extern unsigned long sk_h_0034d384();  /* FUN_0034d384 */
extern unsigned long sk_h_0034d504();  /* FUN_0034d504 */
extern unsigned long sk_h_0034d558();  /* FUN_0034d558 */
extern unsigned long sk_h_0034d5ec();  /* FUN_0034d5ec */
extern unsigned long sk_h_0034d9ac();  /* FUN_0034d9ac */
extern unsigned long sk_h_0034da18();  /* FUN_0034da18 */
extern unsigned long sk_h_0034db28();  /* FUN_0034db28 */
extern unsigned long sk_h_0034dcb4();  /* FUN_0034dcb4 */
extern unsigned long sk_h_0034ded4();  /* FUN_0034ded4 */
extern unsigned long sk_h_0034e0b4();  /* FUN_0034e0b4 */
extern unsigned long sk_h_0034e50c();  /* FUN_0034e50c */
extern unsigned long sk_h_0034e51c();  /* FUN_0034e51c */
extern unsigned long sk_h_0034e53c();  /* FUN_0034e53c */
extern unsigned long sk_h_0034e5dc();  /* FUN_0034e5dc */
extern unsigned long sk_h_0034e6ec();  /* FUN_0034e6ec */
extern unsigned long sk_h_0034e73c();  /* FUN_0034e73c */
extern unsigned long sk_h_0034ea2c();  /* FUN_0034ea2c */
extern unsigned long sk_h_0034eb54();  /* FUN_0034eb54 */
extern unsigned long sk_h_0034ec0c();  /* FUN_0034ec0c */
extern unsigned long sk_h_0034ed18();  /* FUN_0034ed18 */
extern unsigned long sk_h_0034ed98();  /* FUN_0034ed98 */
extern unsigned long sk_h_0034f364();  /* FUN_0034f364 */
extern unsigned long sk_h_0034f414();  /* FUN_0034f414 */
extern unsigned long sk_h_0034fa9c();  /* FUN_0034fa9c */
extern unsigned long sk_h_0034fbd4();  /* FUN_0034fbd4 */
extern unsigned long sk_h_0034fef4();  /* FUN_0034fef4 */
extern unsigned long sk_h_0034ff18();  /* FUN_0034ff18 */
extern unsigned long sk_h_00350258();  /* FUN_00350258 */
extern unsigned long sk_h_003503ec();  /* FUN_003503ec */
extern unsigned long sk_h_00350404();  /* FUN_00350404 */
extern unsigned long sk_h_00350410();  /* FUN_00350410 */
extern unsigned long sk_h_00350470();  /* FUN_00350470 */
extern unsigned long sk_h_00350488();  /* FUN_00350488 */
extern unsigned long sk_h_003504ac();  /* FUN_003504ac */
extern unsigned long sk_h_003504b8();  /* FUN_003504b8 */
extern unsigned long sk_h_003504d0();  /* FUN_003504d0 */
extern unsigned long sk_h_003504dc();  /* FUN_003504dc */
extern unsigned long sk_h_003504e8();  /* FUN_003504e8 */
extern unsigned long sk_h_003504f4();  /* FUN_003504f4 */
extern unsigned long sk_h_0035050c();  /* FUN_0035050c */
extern unsigned long sk_h_00350524();  /* FUN_00350524 */
extern unsigned long sk_h_0035053c();  /* FUN_0035053c */
extern unsigned long sk_h_00350548();  /* FUN_00350548 */
extern unsigned long sk_h_003505dc();  /* FUN_003505dc */
extern unsigned long sk_h_003505e8();  /* FUN_003505e8 */
extern unsigned long sk_h_0035060c();  /* FUN_0035060c */
extern unsigned long sk_h_00350624();  /* FUN_00350624 */
extern unsigned long sk_h_00350630();  /* FUN_00350630 */
extern unsigned long sk_h_00350654();  /* FUN_00350654 */
extern unsigned long sk_h_00350774();  /* FUN_00350774 */
extern unsigned long sk_h_003507e0();  /* FUN_003507e0 */
extern unsigned long sk_h_00350858();  /* FUN_00350858 */
extern unsigned long sk_h_003508c0();  /* FUN_003508c0 */
extern unsigned long sk_h_003508d8();  /* FUN_003508d8 */
extern unsigned long sk_h_003508e4();  /* FUN_003508e4 */
extern unsigned long sk_h_00350950();  /* FUN_00350950 */
extern unsigned long sk_h_00350974();  /* FUN_00350974 */
extern unsigned long sk_h_0035098c();  /* FUN_0035098c */
extern unsigned long sk_h_003509b0();  /* FUN_003509b0 */
extern unsigned long sk_h_003509bc();  /* FUN_003509bc */
extern unsigned long sk_h_003509c8();  /* FUN_003509c8 */
extern unsigned long sk_h_003509f8();  /* FUN_003509f8 */
extern unsigned long sk_h_00350a1c();  /* FUN_00350a1c */
extern unsigned long sk_h_00350a70();  /* FUN_00350a70 */
extern unsigned long sk_h_00350af4();  /* FUN_00350af4 */
extern unsigned long sk_h_00350b24();  /* FUN_00350b24 */
extern unsigned long sk_h_00350b78();  /* FUN_00350b78 */
extern unsigned long sk_h_00350b90();  /* FUN_00350b90 */
extern unsigned long sk_h_00350c20();  /* FUN_00350c20 */
extern unsigned long sk_h_00350c5c();  /* FUN_00350c5c */
extern unsigned long sk_h_00350c8c();  /* FUN_00350c8c */
extern unsigned long sk_h_00350eec();  /* FUN_00350eec */
extern unsigned long sk_h_00350f3c();  /* FUN_00350f3c */
extern unsigned long sk_h_00351048();  /* FUN_00351048 */
extern unsigned long sk_h_00351088();  /* FUN_00351088 */
extern unsigned long sk_h_00351094();  /* FUN_00351094 */
extern unsigned long sk_h_003510ac();  /* FUN_003510ac */
extern unsigned long sk_h_003510b8();  /* FUN_003510b8 */
extern unsigned long sk_h_003510c4();  /* FUN_003510c4 */
extern unsigned long sk_h_00351190();  /* FUN_00351190 */
extern unsigned long sk_h_0035122c();  /* FUN_0035122c */
extern unsigned long sk_h_00351238();  /* FUN_00351238 */
extern unsigned long sk_h_0035125c();  /* FUN_0035125c */
extern unsigned long sk_h_003512cc();  /* FUN_003512cc */
extern unsigned long sk_h_0035133c();  /* FUN_0035133c */
extern unsigned long sk_h_00351378();  /* FUN_00351378 */
extern unsigned long sk_h_003514e8();  /* FUN_003514e8 */
extern unsigned long sk_h_00351554();  /* FUN_00351554 */
extern unsigned long sk_h_003515b4();  /* FUN_003515b4 */
extern unsigned long sk_h_00351648();  /* FUN_00351648 */
extern unsigned long sk_h_003516cc();  /* FUN_003516cc */
extern unsigned long sk_h_00351774();  /* FUN_00351774 */
extern unsigned long sk_h_003517c0();  /* FUN_003517c0 */
extern unsigned long sk_h_00351894();  /* FUN_00351894 */
extern unsigned long sk_h_003518d0();  /* FUN_003518d0 */
extern unsigned long sk_h_0035193c();  /* FUN_0035193c */
extern unsigned long sk_h_003519a8();  /* FUN_003519a8 */
extern unsigned long sk_h_00351a5c();  /* FUN_00351a5c */
extern unsigned long sk_h_00351be0();  /* FUN_00351be0 */
extern unsigned long sk_h_00351d30();  /* FUN_00351d30 */
extern unsigned long sk_h_00351dc0();  /* FUN_00351dc0 */
extern unsigned long sk_h_00351e20();  /* FUN_00351e20 */
extern unsigned long sk_h_00351e60();  /* FUN_00351e60 */
extern unsigned long sk_h_00351e84();  /* FUN_00351e84 */
extern unsigned long sk_h_00351ee0();  /* FUN_00351ee0 */
extern unsigned long sk_h_00351f28();  /* FUN_00351f28 */
extern unsigned long sk_h_00352194();  /* FUN_00352194 */
extern unsigned long sk_h_003523f0();  /* FUN_003523f0 */
extern unsigned long sk_h_0035242c();  /* FUN_0035242c */
extern unsigned long sk_h_003524b0();  /* FUN_003524b0 */
extern unsigned long sk_h_003524c8();  /* FUN_003524c8 */
extern unsigned long sk_h_00352630();  /* FUN_00352630 */
extern unsigned long sk_h_0035272c();  /* FUN_0035272c */
extern unsigned long sk_h_0035280c();  /* FUN_0035280c */
extern unsigned long sk_h_00352894();  /* FUN_00352894 */
extern unsigned long sk_h_003528d8();  /* FUN_003528d8 */
extern unsigned long sk_h_0035292c();  /* FUN_0035292c */
extern unsigned long sk_h_00352974();  /* FUN_00352974 */
extern unsigned long sk_h_00352a64();  /* FUN_00352a64 */
extern unsigned long sk_h_00352ae4();  /* FUN_00352ae4 */
extern unsigned long sk_h_00352d28();  /* FUN_00352d28 */
extern unsigned long sk_h_00352d4c();  /* FUN_00352d4c */
extern unsigned long sk_h_00352da0();  /* FUN_00352da0 */
extern unsigned long sk_h_00352ddc();  /* FUN_00352ddc */
extern unsigned long sk_h_003530e8();  /* FUN_003530e8 */
extern unsigned long sk_h_0035310c();  /* FUN_0035310c */
extern unsigned long sk_h_00353160();  /* FUN_00353160 */
extern unsigned long sk_h_003532a8();  /* FUN_003532a8 */
extern unsigned long sk_h_00353474();  /* FUN_00353474 */
extern unsigned long sk_h_003534ec();  /* FUN_003534ec */
extern unsigned long sk_h_00353888();  /* FUN_00353888 */
extern unsigned long sk_h_00353a00();  /* FUN_00353a00 */
extern unsigned long sk_h_00353a54();  /* FUN_00353a54 */
extern unsigned long sk_h_00353abc();  /* FUN_00353abc */
extern unsigned long sk_h_00353aec();  /* FUN_00353aec */
extern unsigned long sk_h_00353bb8();  /* FUN_00353bb8 */
extern unsigned long sk_h_00353d5c();  /* FUN_00353d5c */
extern unsigned long sk_h_00353fac();  /* FUN_00353fac */
extern unsigned long sk_h_00354010();  /* FUN_00354010 */
extern unsigned long sk_h_003540e8();  /* FUN_003540e8 */
extern unsigned long sk_h_003543a0();  /* FUN_003543a0 */
extern unsigned long sk_h_00354404();  /* FUN_00354404 */
extern unsigned long sk_h_00354474();  /* FUN_00354474 */
extern unsigned long sk_h_00354648();  /* FUN_00354648 */
extern unsigned long sk_h_00354714();  /* FUN_00354714 */
extern unsigned long sk_h_003547b0();  /* FUN_003547b0 */
extern unsigned long sk_h_003548b8();  /* FUN_003548b8 */
extern unsigned long sk_h_00354988();  /* FUN_00354988 */
extern unsigned long sk_h_00354b38();  /* FUN_00354b38 */
extern unsigned long sk_h_00354bec();  /* FUN_00354bec */
extern unsigned long sk_h_00354cf0();  /* FUN_00354cf0 */
extern unsigned long sk_h_00354dc4();  /* FUN_00354dc4 */
extern unsigned long sk_h_00354f34();  /* FUN_00354f34 */
extern unsigned long sk_h_003552f0();  /* FUN_003552f0 */
extern unsigned long sk_h_00355448();  /* FUN_00355448 */
extern unsigned long sk_h_00355b48();  /* FUN_00355b48 */
extern unsigned long sk_h_00355c10();  /* FUN_00355c10 */
extern unsigned long sk_h_00355cb0();  /* FUN_00355cb0 */
extern unsigned long sk_h_00355ce4();  /* FUN_00355ce4 */
extern unsigned long sk_h_00355ebc();  /* FUN_00355ebc */
extern unsigned long sk_h_0035603c();  /* FUN_0035603c */
extern unsigned long sk_h_00356048();  /* FUN_00356048 */
extern unsigned long sk_h_00356110();  /* FUN_00356110 */
extern unsigned long sk_h_0035614c();  /* FUN_0035614c */
extern unsigned long sk_h_00356358();  /* FUN_00356358 */
extern unsigned long sk_h_00356408();  /* FUN_00356408 */
extern unsigned long sk_h_003564d0();  /* FUN_003564d0 */
extern unsigned long sk_h_00356704();  /* FUN_00356704 */
extern unsigned long sk_h_00356bec();  /* FUN_00356bec */
extern unsigned long sk_h_00356fcc();  /* FUN_00356fcc */
extern unsigned long sk_h_003570d8();  /* FUN_003570d8 */
extern unsigned long sk_h_0035723c();  /* FUN_0035723c */
extern unsigned long sk_h_00357400();  /* FUN_00357400 */
extern unsigned long sk_h_003578cc();  /* FUN_003578cc */
extern unsigned long sk_h_00357c04();  /* FUN_00357c04 */
extern unsigned long sk_h_00357c44();  /* FUN_00357c44 */
extern unsigned long sk_h_00357ca0();  /* FUN_00357ca0 */
extern unsigned long sk_h_00358144();  /* FUN_00358144 */
extern unsigned long sk_h_00358154();  /* FUN_00358154 */
extern unsigned long sk_h_003582d8();  /* FUN_003582d8 */
extern unsigned long sk_h_003582e8();  /* FUN_003582e8 */
extern unsigned long sk_h_00358318();  /* FUN_00358318 */
extern unsigned long sk_h_00358324();  /* FUN_00358324 */
extern unsigned long sk_h_00358564();  /* FUN_00358564 */
extern unsigned long sk_h_00358768();  /* FUN_00358768 */
extern unsigned long sk_h_00358a44();  /* FUN_00358a44 */
extern unsigned long sk_h_00358b9c();  /* FUN_00358b9c */
extern unsigned long sk_h_00358c5c();  /* FUN_00358c5c */
extern unsigned long sk_h_00358e88();  /* FUN_00358e88 */
extern unsigned long sk_h_00358fa8();  /* FUN_00358fa8 */
extern unsigned long sk_h_00359018();  /* FUN_00359018 */
extern unsigned long sk_h_00359024();  /* FUN_00359024 */
extern unsigned long sk_h_003591d0();  /* FUN_003591d0 */
extern unsigned long sk_h_003593c0();  /* FUN_003593c0 */
extern unsigned long sk_h_00359424();  /* FUN_00359424 */
extern unsigned long sk_h_00359550();  /* FUN_00359550 */
extern unsigned long sk_h_00359640();  /* FUN_00359640 */
extern unsigned long sk_h_0035976c();  /* FUN_0035976c */
extern unsigned long sk_h_0035990c();  /* FUN_0035990c */
extern unsigned long sk_h_003599c0();  /* FUN_003599c0 */
extern unsigned long sk_h_00359dd0();  /* FUN_00359dd0 */
extern unsigned long sk_h_00359e08();  /* FUN_00359e08 */
extern unsigned long sk_h_0035a504();  /* FUN_0035a504 */
extern unsigned long sk_h_0035a5f0();  /* FUN_0035a5f0 */
extern unsigned long sk_h_0035a658();  /* FUN_0035a658 */
extern unsigned long sk_h_0035a690();  /* FUN_0035a690 */
extern unsigned long sk_h_0035a844();  /* FUN_0035a844 */
extern unsigned long sk_h_0035ac40();  /* FUN_0035ac40 */
extern unsigned long sk_h_0035ac58();  /* FUN_0035ac58 */
extern unsigned long sk_h_0035ac70();  /* FUN_0035ac70 */
extern unsigned long sk_h_0036a804();  /* FUN_0036a804 */
extern unsigned long sk_h_0036a940();  /* FUN_0036a940 */
extern unsigned long sk_h_0036a9a0();  /* FUN_0036a9a0 */
extern unsigned long sk_h_0036b118();  /* FUN_0036b118 */
extern unsigned long sk_h_0036b270();  /* FUN_0036b270 */
extern unsigned long sk_h_0036b6ac();  /* FUN_0036b6ac */
extern unsigned long sk_h_003722e4();  /* FUN_003722e4 */
extern unsigned long sk_h_00376820();  /* FUN_00376820 */
extern unsigned long sk_h_00377824();  /* FUN_00377824 */
extern unsigned long sk_h_00377bec();  /* FUN_00377bec */
extern unsigned long sk_h_0039a030();  /* FUN_0039a030 */
extern unsigned long sk_h_003a25d4();  /* FUN_003a25d4 */
extern unsigned long sk_h_003d30c4();  /* FUN_003d30c4 */
extern unsigned long sk_h_003d3130();  /* FUN_003d3130 */
extern unsigned long sk_h_003d319c();  /* FUN_003d319c */
extern unsigned long sk_h_0060e3fc();  /* FUN_0060e3fc */
extern unsigned long sk_h_0060e40c();  /* FUN_0060e40c */

/* ---- 128-bit / overflow helper macros for transcribed Swift arithmetic ---- */
static inline sk_u128_t sk_mul_u128(sk_u128_t a, sk_u128_t b)
{
    unsigned long alo=a.lo, ahi=a.hi, blo=b.lo;
    sk_u128_t r;
    r.lo = alo*blo;
    r.hi = (unsigned long)((__uint128_t)alo*b.lo >> 64)
         + (unsigned long)((__uint128_t)alo*b.hi)
         + (unsigned long)((__uint128_t)ahi*blo)
         + (unsigned long)((__uint128_t)ahi*b.hi >> 64);
    return r;
}
static inline sk_u128_t sk_add_u128(sk_u128_t a, sk_u128_t b)
{ sk_u128_t r; r.lo=a.lo+b.lo; r.hi=a.hi+b.hi+(r.lo<a.lo); return r; }
static inline int sk_cmp_u128(sk_u128_t a, sk_u128_t b)
{ if (a.hi!=b.hi) return a.hi<b.hi?-1:1; if (a.lo!=b.lo) return a.lo<b.lo?-1:1; return 0; }
static inline sk_u128_t sk_zext(unsigned long v){ sk_u128_t r; r.lo=v; r.hi=0; return r; }
static inline sk_u128_t sk_shl_u128(sk_u128_t a, unsigned int n)
{ sk_u128_t r; if(n>=64){ r.lo=0; r.hi=a.lo<<(n-64); } else { r.lo=a.lo<<n; r.hi=(a.hi<<n)|(a.lo>>(64-n)); } return r; }
#define CARRY8(a,b)   ((unsigned long)(a) > (unsigned long)(~0ULL - (unsigned long)(b)))
#define SBORROW8(a,b) (((long)(a) < (long)(b)) || ((long)(a)-(long)(b) < (long)(a)))
#define SCARRY8(a,b)  (((long)(a)+(long)(b)) < (long)(a))
#define SUB168(x,y)   ((x).lo)
#define ZEXT816(v)    sk_zext((unsigned long)(v))
#define ZEXT216(v)    ((unsigned short)(unsigned long)(v))
#define ABS(x)        ((x)<0?-(x):(x))
#define INFINITY      (1.0e300*1.0e300)
#define NAN(x)        ((x)!=(x))
#define FLOAT_UNKNOWN (0.0f)
#define SUB42(a,b) ((unsigned int)(a))
#define CONCAT71(h,l)  (((unsigned long)(h)<<8)|((unsigned long)(l)&0xff))
#define CONCAT17(l,h)  (((unsigned long)(l))|((unsigned long)(h)<<8))
#define CONCAT44(h,l)  ((((unsigned long)(h)&0xffffffff)<<32)|((unsigned long)(l)&0xffffffff))
#define SoftwareBreakpoint(...) __builtin_trap()

static void sk_slice_002dd890();
static void sk_slice_002dd918();
static void sk_slice_002dd964();
static unsigned long sk_slice_002ddac8();
static long sk_slice_002ddb50();
static void sk_slice_002ddbb0();
static void sk_slice_002ddd74();
static void sk_slice_002ddef4();
static void sk_slice_002ddfec();
static void sk_slice_002de020();
static unsigned long sk_slice_002de068();
static unsigned long sk_slice_002de43c();
static unsigned long sk_slice_002de514();
static void sk_slice_002de640();
static unsigned long sk_slice_002de774();
static unsigned long sk_slice_002deae4();
static void sk_slice_002dec50();
static void sk_slice_002decc8();
static sk_u128_t sk_slice_002ded3c();
static sk_u128_t sk_slice_002ded88();
static void sk_slice_002deee4();
static void sk_slice_002def2c();
static void sk_slice_002def88();
static void sk_slice_002defd0();
static void sk_slice_002df02c();
static void sk_slice_002df130();
static void sk_slice_002df15c();
static void sk_slice_002df184();
static void sk_slice_002df1ac();
static void sk_slice_002df1dc();
static void sk_slice_002df268();
static void sk_slice_002df2f4();
static void sk_slice_002df380();
static void sk_slice_002df40c();
static void sk_slice_002dfdd4();
static void sk_slice_002e079c();
static void sk_slice_002e1164();
static void sk_slice_002e1b2c();
static void sk_slice_002e1b74();
static void sk_slice_002e1ba8();
static unsigned long sk_slice_002e1c9c();
static void sk_slice_002e1d08();
static void sk_slice_002e1d30();
static void sk_slice_002e1d5c();
static sk_u128_t sk_slice_002e1d74();
static void sk_slice_002e1dc0();
static bool sk_slice_002e1ee4();
static bool sk_slice_002e1f28();
static void sk_slice_002e1f6c();
static void sk_slice_002e1fa8();
static void sk_slice_002e2058();
static void sk_slice_002e25f8();
static void sk_slice_002e278c();
static void sk_slice_002e2a04();
static void sk_slice_002e2aa4();
static void sk_slice_002e2b84();
static void sk_slice_002e2bbc();
static void sk_slice_002e2d24();
static void sk_slice_002e2f18();
static void sk_slice_002e347c();
static void sk_slice_002e34a0();
static unsigned long sk_slice_002e3584();
static void sk_slice_002e3704();
static void sk_slice_002e3774();
static void sk_slice_002e3840();
static void sk_slice_002e3844();
static void sk_slice_002e3870();
static void sk_slice_002e39cc();
static unsigned long sk_slice_002e3a20();
static void sk_slice_002e3b64();
static void sk_slice_002e3be4();
static void sk_slice_002e3c18();
static void sk_slice_002e3c48();
static void sk_slice_002e3c78();
static void sk_slice_002e3ca8();
static void sk_slice_002e3cd8();
static void sk_slice_002e3d08();
static void sk_slice_002e3d78();
static void sk_slice_002e3dbc();
static void sk_slice_002e3df4();
static void sk_slice_002e3e50();
static void sk_slice_002e3fe4();
static void sk_slice_002e4028();
static void sk_slice_002e402c();
static void sk_slice_002e4058();
static void sk_slice_002e4110();
static void sk_slice_002e416c();
static void sk_slice_002e4290();
static long sk_slice_002e4358();
static long sk_slice_002e43c8();
static void sk_slice_002e4444();
static unsigned long sk_slice_002e4584();
static void sk_slice_002e45a0();
static unsigned int sk_slice_002e45d0();
static void sk_slice_002e466c();
static unsigned long sk_slice_002e469c();
static unsigned long sk_slice_002e4720();
static void sk_slice_002e47a8();
static unsigned long sk_slice_002e4838();
static void sk_slice_002e48c8();
static sk_u128_t sk_slice_002e48f8();
static sk_u128_t sk_slice_002e4980();
static void sk_slice_002e4a04();
static void sk_slice_002e4a94();
static sk_u128_t sk_slice_002e4b00();
static void sk_slice_002e4b94();
static long sk_slice_002e4bc0();
static unsigned long sk_slice_002e4c1c();
static unsigned int sk_slice_002e507c();
static sk_u128_t sk_slice_002e5094();
static unsigned int sk_slice_002e5118();
static unsigned long sk_slice_002e513c();
static sk_u128_t sk_slice_002e52d4();
static long sk_slice_002e5370();
static unsigned long sk_slice_002e53cc();
static unsigned int sk_slice_002e57b0();
static unsigned int sk_slice_002e57e0();
static void sk_slice_002e5804();
static unsigned long sk_slice_002e5828();
static long sk_slice_002e5a1c();
static unsigned long sk_slice_002e5a78();
static unsigned long sk_slice_002e62a0();
static unsigned long sk_slice_002e62c4();
static unsigned long sk_slice_002e62d0();
static void sk_slice_002e62f0();
static void sk_slice_002e6330();
static unsigned long sk_slice_002e6410();
static bool sk_slice_002e6474();
static void sk_slice_002e648c();
static unsigned long sk_slice_002e64f0();
static void sk_slice_002e6580();
static void sk_slice_002e65b8();
static void sk_slice_002e6638();
static sk_u128_t sk_slice_002e6670();
static void sk_slice_002e66dc();
static void sk_slice_002e6728();
static void sk_slice_002e6750();
static void sk_slice_002e682c();
static void sk_slice_002e68dc();
static void sk_slice_002e68e4();
static void sk_slice_002e6914();
static void sk_slice_002e694c();
static void sk_slice_002e6954();
static sk_u128_t sk_slice_002e6964();
static long sk_slice_002e69e8();
static unsigned int sk_slice_002e6a58();
static sk_f16_t sk_slice_002e6af0();
static unsigned int sk_slice_002e6bac();
static sk_f16_t sk_slice_002e6be4();
static sk_f16_t sk_slice_002e6be8();
static void sk_slice_002e6cc8();
static void sk_slice_002e6ccc();
static void sk_slice_002e6cf8();
static void sk_slice_002e6cfc();
static unsigned int sk_slice_002e6d80();
static void sk_slice_002e6e3c();
static void sk_slice_002e6e84();

/*--------------------------------------------------------------------*/
/* FUN_002dd890 @ 0x002dd890  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002dd890(undefined8 param_1,undefined8 arg2,undefined8 arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002dd890()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long tmp1;
    {
      tmp1 = sk_h_00376820(&sk_dat_004ec5ac);
      sk_h_001e7664(arg1,arg2,arg3,tmp1,0x6720e8);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002dd918 @ 0x002dd918  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002dd918(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002dd918()
{
    sk_fn regx19;
    {
      sk_h_00350858();
      sk_h_00358b9c();
      sk_h_0034a000();
      sk_h_00376820();
      sk_h_0034887c();
      sk_h_00355448();
      regx19();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002dd964 @ 0x002dd964  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002dd964(undefined8 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002dd964()
{
    unsigned long arg1;
    unsigned long tmp1;
    {
      tmp1 = sk_h_00376820(&sk_dat_004ec600,arg1);
      sk_h_001a0194(arg1,tmp1);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002ddac8 @ 0x002ddac8  (est. sk_swift_runtime) */
/* Ghidra: undefined8 FUN_002ddac8(undefined8 *param_1,undefined8 arg2,undefined8 arg3,long param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002ddac8()
{
    unsigned long * arg1;
    unsigned long arg2;
    unsigned long arg3;
    long arg4;
    unsigned long * regx20;
    unsigned long var50;
    unsigned long stack48;
    unsigned long stack40;
    unsigned long stack38;
    unsigned long var30;
    unsigned long stack28;
    {
      sk_h_002dc748(&var50,arg2,arg3,*regx20,regx20[1],regx20[2],regx20[3],
                   *(unsigned long *)(arg4 + 0x10));
      arg1[1] = stack48;
      *arg1 = var50;
      arg1[3] = stack38;
      arg1[2] = stack40;
      arg1[4] = var30;
      return stack28;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002ddb50 @ 0x002ddb50  (est. sk_swift_runtime) */
/* Ghidra: long FUN_002ddb50(ulong param_1,long arg2,ulong arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
long sk_slice_002ddb50()
{
    unsigned long arg1;
    long arg2;
    unsigned long arg3;
    {
      if ((long)arg1 < 0) {
        sk_h_003488bc(1);
        sk_h_00355ebc();
        sk_h_00349b50();
                        /* WARNING: Subroutine does not return */
        sk_h_001afe4c();
      }
      if ((arg1 >> 0x39 == 0) && ((long)arg1 * 0x40 < (long)(arg3 >> 8))) {
        return *(long *)(arg2 + arg1 * 8);
      }
      return -(arg3 & 1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002ddbb0 @ 0x002ddbb0  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002ddbb0(undefined8 param_1,ulong arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002ddbb0()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long tmp1;
    unsigned long tmp2;
    unsigned long tmp3;
    bool bval4;
    unsigned char tmp5;
    unsigned int outw1;
    unsigned long outx1;
    unsigned long outx8;
    unsigned long outx8_00;
    unsigned long outx9;
    unsigned long tmp6;
    unsigned long regx22;
    sk_u128_t buf7;
    unsigned long var78;
    unsigned long stack70;
    unsigned long var60;
    unsigned long stack58;
    unsigned long var48;
    {
      sk_h_0006b2ec();
      tmp2 = 0x78302d;
      if ((arg2 & 1) == 0) {
        tmp2 = 0x78302b;
      }
      tmp1 = ((outx1 >> 8) + 2 >> 2) + 3;
      tmp6 = outx1 >> 9;
      var48 = outx8;
      if (tmp6 < 0x19) {
        stack58 = sk_dat_004e7b68;
        var60 = sk_dat_004e7b60;
        sk_slice_002ddd74(&var60,tmp1,tmp1,(unsigned int)arg2 & 1);
        tmp3 = tmp1;
        if (7 < tmp1) {
          tmp3 = 0;
        }
        bval4 = tmp6 == 0xb;
        sk_h_00353888(0xffffffffffffffff >> ((unsigned long)(unsigned int)((int)tmp3 * -8) & 0x38));
        tmp3 = 0xe000000000000000;
        if (!bval4) {
          tmp3 = outx9;
        }
        regx22 = tmp3 | tmp1 << 0x38 | outx8_00;
        if ((regx22 >> 0x3e & 1) == 0) {
          stack58 = outx8_00 & 0xffffffffffffff;
          var60 = tmp6;
          sk_h_0029ac08(&var78,&var60,regx22 >> 0x38 & 0xf);
          tmp6 = var78;
          regx22 = stack70;
        }
      }
      else {
        sk_h_00356358(tmp1,tmp1,(unsigned int)arg2 & 1);
        sk_h_0029ad14();
        sk_h_00351a5c();
      }
      var60 = tmp6;
      stack58 = regx22;
      sk_h_0036b270(regx22);
      sk_h_00350af4();
      sk_h_001d7bb0();
      sk_h_003a25d4(regx22);
      tmp5 = (outw1 & 0xff) == 1;
      if ((bool)tmp5) {
        sk_h_003a25d4(0xe300000000000000);
        sk_h_003a25d4(regx22);
        buf7 = sk_zext((unsigned long)sk_h_001a89a8(&sk_tab_005d0fa9,4,1));
      }
      else {
        sk_h_00350548(0xf);
        sk_h_00354404();
        buf7 = sk_zext((unsigned long)sk_h_002ab8ac());
        sk_h_002a55c0(buf7.lo,buf7.hi,tmp2,0xe300000000000000);
        sk_h_003a25d4(0xe300000000000000);
        buf7.hi = stack58;
        buf7.lo = var60;
      }
      sk_h_000651bc(var48,buf7.lo,buf7.hi);
      if ((bool)tmp5) {
        return;
      }
                        /* WARNING: Subroutine does not return */
      sk_h_0011d7e8();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002ddd74 @ 0x002ddd74  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002ddd74(undefined8 param_1,undefined8 arg2,undefined8 arg3,ulong param_4, undefined8 param_5,ulong param_6) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002ddd74()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
    unsigned long arg5;
    unsigned long arg6;
    unsigned long tmp1;
    long lval2;
    unsigned int tmp3;
    bool bval4;
    unsigned long tmp5;
    long lval6;
    unsigned long tmp7;
    unsigned long outx1;
    unsigned long outx8;
    unsigned int tmp8;
    unsigned long tmp9;
    unsigned long tmp10;
    unsigned long regx28;
    unsigned long regx30;
    sk_u128_t buf11;
    {
      sk_h_0035193c();
      sk_h_00358fa8(arg3);
      sk_h_001bb69c(outx8);
      sk_h_003517c0();
      sk_h_0034db28(0x30);
      sk_slice_002ddef4();
      tmp9 = arg4;
      tmp10 = 0;
      while( true ) {
        if ((long)(arg6 >> 8) <= (long)tmp10) {
          sk_h_00351774(outx8,regx30);
          return;
        }
        tmp1 = 0x7fffffffffffffff;
        if (!SCARRY8(tmp10,0x20)) {
          tmp1 = tmp10 + 0x20;
        }
        tmp5 = sk_slice_002ddb50((long)tmp10 >> 6,arg5,arg6);
        tmp5 = tmp5 >> (tmp10 & 0x3f);
        if ((arg4 & 1) != 0) {
          tmp3 = ~(unsigned int)tmp5;
          tmp8 = tmp3 + 1;
          bval4 = (tmp9 & 1) == 0;
          if (bval4) {
            tmp8 = ~(unsigned int)tmp5;
          }
          tmp5 = (unsigned long)tmp8;
          tmp8 = 0;
          if (!bval4) {
            tmp8 = (unsigned int)(0xfffffffe < tmp3);
          }
          tmp9 = (unsigned long)tmp8;
        }
        sk_h_002366a0(0x10,1);
        sk_h_003578cc();
        if ((outx1 >> 0x3c & 1) == 0) {
          tmp7 = regx28 & 0xffffffffffff;
          if ((tmp10 & 0x2000000000000000) != 0) {
            tmp7 = tmp10 >> 0x38 & 0xf;
          }
        }
        else {
          sk_h_003509b0();
          tmp7 = sk_h_002b24b8();
        }
        sk_h_0034db28(tmp7);
        buf11 = sk_zext((unsigned long)sk_h_001b4d10());
        lval6 = buf11.lo;
        lval2 = 0;
        if (tmp5 != 0) {
          lval2 = tmp5 + lval6;
        }
        if (buf11.hi - lval6 < 0) break;
        if ((buf11.hi != lval6) && (lval2 == 0)) {
          sk_h_003488bc(1);
          sk_h_00349a04();
          goto L002ddd74_002ddecc;
        }
        sk_h_003509b0();
        sk_slice_002e3584();
        sk_h_003a25d4(tmp10);
        sk_h_0034db28(8);
        sk_h_001b4748();
        sk_h_003517c0();
        tmp10 = tmp1;
      }
      sk_h_00351088(1);
      sk_h_003487a4();
    L002ddd74_002ddecc:
      sk_h_003524c8();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002ddef4 @ 0x002ddef4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002ddef4(undefined8 param_1,long arg2,long arg3,long param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002ddef4()
{
    unsigned long arg1;
    long arg2;
    long arg3;
    long arg4;
    long lval1;
    char * fptr2;
    unsigned long tmp3;
    unsigned long tmp4;
    {
      lval1 = 0;
      if (arg4 != 0) {
        lval1 = arg4 + arg2;
      }
      arg3 = arg3 - arg2;
      if (-1 < arg3) {
        if (arg3 == 0) {
          if (lval1 == 0) {
            return;
          }
        }
        else if (lval1 == 0) {
          tmp4 = 0x4c;
          fptr2 = sk_str_005cdc30;
          tmp3 = 0x3c;
          goto L002ddef4_002ddf80;
        }
        sk_h_00235398(arg1,arg3);
        return;
      }
      tmp4 = 0x4a;
      fptr2 = sk_str_005cdbe0;
      tmp3 = 0x2e;
    L002ddef4_002ddf80:
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c(sk_str_005accd0,0xb,2,fptr2,tmp3,2,
                   sk_str_005cdc10,0x1f,2,tmp4,1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002ddfec @ 0x002ddfec  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002ddfec(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002ddfec()
{
    {
      sk_h_00356bec();
      sk_h_0034d5ec();
      sk_h_001a5ff8();
      sk_h_0034a224();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002de020 @ 0x002de020  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002de020(undefined8 *param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002de020()
{
    unsigned long * arg1;
    unsigned long * regx20;
    unsigned long var50;
    unsigned long stack48;
    unsigned long stack40;
    unsigned char stack38;
    unsigned char stack30;
    unsigned long stack2f;
    unsigned long var37;
    {
      undefined7 var37;
      sk_slice_002ddfec(&var50,*regx20,regx20[1]);
      arg1[1] = stack48;
      *arg1 = var50;
      arg1[3] = CONCAT71(var37,stack38);
      arg1[2] = stack40;
      *(unsigned long *)((long)arg1 + 0x21) = stack2f;
      *(unsigned long *)((long)arg1 + 0x19) = CONCAT17(stack30,var37);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002de068 @ 0x002de068  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002de068(undefined8 param_1,undefined8 arg2,undefined8 arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002de068()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long tmp1;
    sk_fn fptr2;
    unsigned long tmp3;
    long lval4;
    unsigned long tmp5;
    unsigned long outx1;
    long outx8;
    sk_fn outx8_00;
    sk_fn outx8_01;
    sk_fn outx8_02;
    sk_fn outx8_03;
    sk_fn outx8_04;
    sk_fn outx9;
    sk_fn outx9_00;
    sk_fn outx9_01;
    sk_fn outx9_02;
    sk_fn outx9_03;
    long outx16;
    unsigned long regx19;
    unsigned long regx22;
    sk_fn regx23;
    sk_fn fptr6;
    sk_u128_t buf7;
    {
      sk_h_0008e518();
      sk_h_0034e73c();
      sk_h_0034be54();
      sk_h_003528d8();
      sk_h_00351238();
      tmp1 = sk_h_00377824();
      sk_h_0034ab20();
      sk_h_0007c1a4();
      sk_g_dispatch();
      sk_h_0034af20();
      sk_h_003494e8();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_00348a18();
      sk_g_dispatch();
      sk_h_0034c2d8();
      sk_h_003540e8();
      fptr2 = (sk_fn)sk_h_0031c430(arg3);
      sk_h_0001df60();
      sk_h_0034c308();
      fptr2();
      sk_h_0035ac40(arg3);
      sk_h_003510ac();
      tmp3 = fptr2();
      if ((tmp3 & 1) == 0) {
    L002de068_002de1f4:
        sk_h_003547b0(arg3);
        sk_h_003510ac();
        lval4 = regx23();
        if (0x3f < lval4) {
          tmp5 = sk_h_003504dc();
          fptr2 = (sk_fn)fptr2(tmp5,arg3);
          sk_h_003510ac();
          lval4 = regx23();
          if (((unsigned long)fptr2 & 1) == 0) {
            if (0x40 < lval4) {
              sk_h_00354cf0();
              sk_h_00352d4c(arg3);
              sk_h_0001e790();
              sk_h_0034ea2c();
              sk_h_003505dc();
              fptr2();
              sk_h_00348e78(arg3);
              sk_h_0034ba38();
              outx8_02();
              sk_h_0035a658();
              fptr6 = *(sk_fn *)(regx23 + 8);
              goto L002de068_002de2fc;
            }
    L002de068_002de3a8:
            sk_h_0034d504(arg3);
            sk_h_003510ac();
            outx8_04();
          }
          else if (lval4 < 0x41) {
            sk_h_0034ad00();
            buf7 = sk_zext((unsigned long)sk_h_0035060c());
            sk_h_00377bec(buf7.lo,buf7.hi,tmp1);
            tmp1 = sk_h_00349370();
            sk_h_00350f3c(tmp1,0x100);
            outx9_01();
            sk_h_0034d558();
            buf7 = sk_zext((unsigned long)sk_h_0034ce18());
            outx9_02(buf7.lo,buf7.hi,outx1);
            sk_h_0034b368(arg3);
            sk_h_00351ee0();
            sk_h_00355cb0();
            sk_h_0034e51c();
            outx8_03();
            sk_h_0034e5dc();
            sk_h_00350524();
            outx9_03();
            if ((regx22 & 1) != 0) goto L002de068_002de3a8;
          }
          else {
            sk_h_00354cf0();
            sk_h_00352d4c(arg3);
            sk_h_0001e790();
            sk_h_0034ea2c();
            sk_h_003505dc();
            fptr2();
            sk_h_00348e78(arg3);
            sk_h_0034ba38();
            outx8_01();
            sk_h_003519a8();
            fptr6 = *(sk_fn *)(outx16 + 8);
    L002de068_002de2fc:
            fptr6();
            if ((regx22 & 1) != 0) goto L002de068_002de310;
          }
        }
        fptr2 = (sk_fn)sk_h_003109b4(arg3);
        sk_h_003510ac();
        fptr2();
        fptr6 = *(sk_fn *)(outx16 + 8);
        sk_h_003510b8();
        fptr6();
        sk_h_003510ac();
        fptr2();
        sk_h_0035122c();
        buf7 = sk_zext((unsigned long)fptr6());
        tmp1 = 0;
      }
      else {
        sk_h_0035060c();
        sk_h_00352ae4();
        lval4 = sk_h_00377bec();
        tmp5 = sk_h_003494fc();
        sk_h_003512cc(tmp5,0x100);
        outx9();
        sk_h_0034d558();
        buf7 = sk_zext((unsigned long)sk_h_0034ce18());
        outx9_00(buf7.lo,buf7.hi,outx1);
        sk_h_003492cc(arg3);
        sk_h_00350b78();
        sk_h_00351238();
        outx8_00();
        sk_h_0035a658();
        regx23 = (sk_fn)(lval4 + 8);
        fptr6 = *(sk_fn *)regx23;
        sk_h_003505e8();
        fptr6();
        if ((regx19 & 1) == 0) goto L002de068_002de1f4;
    L002de068_002de310:
        fptr6(regx22);
        sk_h_00353bb8();
        fptr6();
        buf7 = sk_zext((unsigned long)sk_h_00356110());
        tmp1 = 1;
      }
      sk_h_0006b6f4(buf7.lo,buf7.hi,tmp1);
      sk_h_0008e500();
      return 0;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002de43c @ 0x002de43c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002de43c(void) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002de43c()
{
    unsigned char inregZR;
    long outx8;
    sk_fn outx8_00;
    sk_fn outx9;
    {
      sk_h_0034ed98();
      sk_h_00349b3c();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_003490ec();
      sk_h_00351e84();
      sk_h_0034c818();
      outx9();
      sk_h_0034e53c();
      sk_slice_002de068();
      sk_h_0035292c();
      if (!(bool)inregZR) {
        sk_h_0034dcb4();
        outx8_00();
        sk_h_000e15d8();
        return 0;
      }
      sk_h_0034a478(sk_str_005d0fb0);
      sk_h_003593c0();
      sk_h_0006f768();
                        /* WARNING: Subroutine does not return */
      sk_h_003532a8();
    }
    return 0;

    return 0;}

/*--------------------------------------------------------------------*/
/* FUN_002de514 @ 0x002de514  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002de514(undefined8 param_1,undefined8 arg2,undefined8 arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002de514()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned char inregZR;
    long outx8;
    sk_fn outx8_00;
    sk_fn outx8_01;
    sk_fn outx9;
    sk_fn outx9_00;
    long outx16;
    sk_fn fptr1;
    unsigned long regx30;
    sk_u128_t buf2;
    {
      sk_h_00084220();
      sk_h_00350c5c();
      sk_h_00349b3c();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_00349178();
      sk_h_00351e84();
      sk_h_0034d180();
      outx9();
      buf2 = sk_zext((unsigned long)sk_h_003509bc());
      sk_slice_002de068(buf2.lo,buf2.hi,arg3);
      sk_h_0035292c();
      if ((bool)inregZR) {
        sk_h_0008f6c0(arg3);
        sk_h_00352894();
        sk_h_0016791c();
        sk_h_00351048();
        outx9_00();
        sk_h_003492cc(arg3);
        sk_h_003504ac();
        sk_h_00351378();
        outx8_00();
        fptr1 = *(sk_fn *)(outx16 + 8);
        sk_h_003509bc();
        fptr1();
        sk_h_0009461c();
        fptr1();
      }
      else {
        sk_h_000778b4();
        sk_h_0009461c(*(unsigned long *)(outx16 + 8));
        outx8_01();
      }
      buf2 = sk_zext((unsigned long)sk_h_000dbd0c());
      sk_h_00084234(buf2.lo,buf2.hi,regx30);
      return 0;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002de640 @ 0x002de640  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002de640(undefined8 param_1,undefined8 arg2,undefined8 arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002de640()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    sk_fn fptr1;
    long outx8;
    long outx16;
    sk_fn fptr2;
    unsigned long regx30;
    sk_u128_t buf3;
    {
      sk_h_0008e518();
      sk_h_0034f414();
      sk_h_00349b3c();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_00348f38();
      sk_h_003540e8();
      fptr1 = (sk_fn)sk_h_0031c430(arg3);
      sk_h_0001df60();
      sk_h_0034c308();
      sk_h_00353abc();
      fptr1();
      fptr1 = (sk_fn)sk_h_003109b4();
      sk_h_003504ac();
      fptr1();
      fptr2 = *(sk_fn *)(outx16 + 8);
      sk_h_003514e8();
      fptr2();
      sk_h_0034e50c();
      fptr1();
      sk_h_00084180();
      fptr2();
      buf3 = sk_zext((unsigned long)sk_h_00351648());
      sk_h_0008e500(buf3.lo,buf3.hi,regx30);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002de774 @ 0x002de774  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002de774(undefined8 param_1,undefined8 arg2,undefined8 arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002de774()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned char inregZR;
    unsigned long tmp1;
    unsigned long tmp2;
    long outx8;
    sk_fn outx9;
    sk_fn outx9_00;
    sk_fn outx9_01;
    sk_fn outx9_02;
    sk_fn outx9_03;
    long outx16;
    sk_fn fptr3;
    unsigned long regx22;
    unsigned long regx24;
    sk_fn fptr4;
    unsigned long regx28;
    sk_u128_t buf5;
    sk_u128_t buf6;
    long var10 [2];
    {
      buf5 = sk_zext((unsigned long)sk_h_0008e518());
      sk_h_0035125c(arg3);
      sk_h_0034c60c();
      tmp1 = sk_h_00377824();
      sk_h_0034ab20();
      sk_h_0007c1a4();
      sk_g_dispatch();
      sk_h_0034af20();
      sk_h_003494e8();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_00348bd8();
      sk_g_dispatch();
      sk_h_0034ae94();
      sk_g_dispatch();
      sk_h_0034a464();
      sk_g_dispatch();
      sk_h_0034b758();
      sk_h_00350c8c();
      tmp2 = sk_h_00377bec();
      sk_h_00350654();
      outx9(0x3bf0000000000000,tmp1,tmp2);
      sk_h_0034cea8();
      sk_h_0034ce18();
      outx9_00();
      sk_h_003570d8();
      sk_h_003564d0();
      sk_h_0008f6f4();
      sk_h_00350950();
      sk_h_0031c580();
      sk_h_00350b24();
      sk_h_003508d8(buf5.lo);
      outx9_01();
      fptr4 = *(sk_fn *)(outx16 + 8);
      fptr4();
      sk_h_0031bfb0();
      sk_h_0035133c();
      sk_h_00351190(4);
      outx9_02();
      sk_h_003505e8();
      fptr4();
      fptr3 = *(sk_fn *)(outx16 + 0x10);
      sk_h_0034cf94();
      fptr3();
      sk_h_003249ac();
      sk_h_00352da0();
      sk_h_00350a1c(var10);
      sk_h_0024304c();
      sk_h_00359550();
      if ((bool)inregZR) {
        sk_h_00354648();
        fptr4();
        sk_h_00350524();
        fptr4();
      }
      else {
        if (var10[0] == 0) {
          sk_h_0034ce78();
          fptr3();
        }
        else {
          outx9(regx28,0x43f0000000000000,tmp1,tmp2);
          buf6 = sk_zext((unsigned long)sk_h_0034f364(regx24));
          outx9_00(buf6.lo,buf6.hi,regx22);
          buf6 = sk_zext((unsigned long)sk_h_0008e388());
          outx9_01(buf6.lo,buf6.hi,buf5.hi,tmp2);
          sk_h_00084180();
          fptr4();
          sk_h_00350950(tmp2);
          sk_h_0035614c();
          sk_h_00354bec();
          sk_h_00350b78();
          sk_h_00350974();
          outx9_03();
          sk_h_003505e8();
          fptr4();
        }
        sk_h_00352da0();
        sk_h_00353474(var10);
        sk_h_0024304c();
        sk_h_00359550();
        if (!(bool)inregZR) {
          sk_h_003510b8();
          fptr4();
          sk_h_00350524();
          tmp1 = fptr4();
          buf5.hi = var10[0];
          buf5.lo = tmp1;
          goto L002de774_002deacc;
        }
        sk_h_003510b8();
        fptr4();
        sk_h_00350524();
        fptr4();
      }
      buf5 = sk_zext((unsigned long)sk_h_003509f8());
    L002de774_002deacc:
      sk_h_003548b8(buf5.lo,buf5.hi);
      sk_h_0008e500();
      return 0;
    }
    return 0;
}

/*--------------------------------------------------------------------*/
/* FUN_002deae4 @ 0x002deae4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002deae4(undefined8 param_1,undefined8 arg2,undefined8 arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002deae4()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned char inregZR;
    long outx8;
    sk_fn outx8_00;
    sk_fn outx9;
    {
      sk_h_0034ed98();
      sk_h_00349b3c();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_003490ec();
      sk_h_0035ac58(arg3);
      sk_h_0031bfb0();
      sk_h_0035133c();
      sk_h_00350c20(4);
      outx9();
      sk_h_0034e53c();
      sk_slice_002de774();
      sk_h_0035292c();
      if (!(bool)inregZR) {
        sk_h_0034dcb4();
        outx8_00();
        sk_h_000e15d8();
        return 0;
      }
      sk_h_0034a478(sk_str_005d0fb0);
      sk_h_003593c0();
      sk_h_0006f768();
                        /* WARNING: Subroutine does not return */
      sk_h_003532a8();
    }
    return 0;

    return 0;}

/*--------------------------------------------------------------------*/
/* FUN_002dec50 @ 0x002dec50  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002dec50(undefined8 param_1,undefined8 arg2,undefined8 arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002dec50()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    sk_fn outx8;
    unsigned char bval1;
    {
      sk_h_0034a4a4(arg3);
      bval1 = sk_h_003552f0();
      sk_h_0034d264(bval1,(*(unsigned long *)(sk_str_004e7a30 + 16)),
                   bval1 ^ (unsigned char)(*(unsigned long *)(sk_str_004e7a30 + 0)));
      outx8();
      sk_h_001a8564();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002decc8 @ 0x002decc8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002decc8(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002decc8()
{
    sk_fn inregx3;
    unsigned char buf78 [72];
    {
      sk_h_001a84f4(buf78);
      sk_h_003510c4(buf78);
      inregx3();
      sk_h_001a8564();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002ded3c @ 0x002ded3c  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002ded3c(long param_1,long arg2,undefined8 arg3,undefined8 param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002ded3c()
{
    long arg1;
    long arg2;
    unsigned long arg3;
    unsigned long arg4;
    unsigned long outx10;
    sk_u128_t buf1;
    {
      if (arg1 != 0 || arg2 != 0) {
        sk_h_00352630(arg2);
        sk_h_0011db10();
        sk_h_00359dd0();
        arg3 = outx10;
      }
      buf1.hi = arg4;
      buf1.lo = arg3;
      return buf1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002ded88 @ 0x002ded88  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002ded88(long param_1,long arg2,undefined8 arg3,undefined8 param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002ded88()
{
    long arg1;
    long arg2;
    unsigned long arg3;
    unsigned long arg4;
    unsigned long outx10;
    sk_u128_t buf1;
    {
      if (arg1 != 0 || arg2 != 0) {
        sk_h_00352630(arg2);
        sk_h_0011db18();
        sk_h_00359dd0();
        arg3 = outx10;
      }
      buf1.hi = arg4;
      buf1.lo = arg3;
      return buf1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002deee4 @ 0x002deee4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002deee4(undefined8 param_1,undefined8 arg2,long arg3,long param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002deee4()
{
    unsigned long arg1;
    unsigned long arg2;
    long arg3;
    long arg4;
    {
      if (arg3 != 0 || arg4 != 0) {
        sk_h_0011db10();
        return;
      }
      sk_h_003485f0(1);
      sk_h_00349fa4();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002def2c @ 0x002def2c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002def2c(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002def2c()
{
    unsigned long tmp1;
    long outx8;
    sk_u128_t * regx19;
    sk_u128_t buf2;
    {
      sk_h_00359e08();
      if (outx8 != 0) {
        tmp1 = sk_h_00352194();
        buf2 = sk_zext((unsigned long)sk_h_0011db10(tmp1,*(unsigned long *)(((unsigned char *)regx19 + 8))));
        *regx19 = buf2;
        return;
      }
      sk_h_003485f0(1);
      sk_h_00349fa4();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002def88 @ 0x002def88  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002def88(undefined8 param_1,undefined8 arg2,long arg3,long param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002def88()
{
    unsigned long arg1;
    unsigned long arg2;
    long arg3;
    long arg4;
    {
      if (arg3 != 0 || arg4 != 0) {
        sk_h_0011db18();
        return;
      }
      sk_h_003487f8(1);
      sk_h_003499dc();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002defd0 @ 0x002defd0  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002defd0(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002defd0()
{
    unsigned long tmp1;
    long outx8;
    sk_u128_t * regx19;
    sk_u128_t buf2;
    {
      sk_h_00359e08();
      if (outx8 != 0) {
        tmp1 = sk_h_00352194();
        buf2 = sk_zext((unsigned long)sk_h_0011db18(tmp1,*(unsigned long *)(((unsigned char *)regx19 + 8))));
        *regx19 = buf2;
        return;
      }
      sk_h_003487f8(1);
      sk_h_003499dc();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df02c @ 0x002df02c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df02c(undefined1 (*param_1) [16],undefined8 arg2,undefined8 arg3, undefined1 param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df02c()
{
    sk_u128_t * arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned char arg4;
    sk_u128_t buf1;
    {
      buf1 = sk_zext((unsigned long)sk_slice_002de068());
      *arg1 = buf1;
      ((unsigned char *)arg1)[16] = arg4;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df130 @ 0x002df130  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df130(undefined1 (*param_1) [16],undefined8 arg2,undefined8 arg3, undefined1 param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df130()
{
    sk_u128_t * arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned char arg4;
    sk_u128_t buf1;
    {
      buf1 = sk_zext((unsigned long)sk_slice_002de774());
      *arg1 = buf1;
      ((unsigned char *)arg1)[16] = arg4;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df15c @ 0x002df15c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df15c(undefined1 (*param_1) [16]) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df15c()
{
    sk_u128_t * arg1;
    sk_u128_t buf1;
    {
      buf1 = sk_zext((unsigned long)sk_slice_002deae4());
      *arg1 = buf1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df184 @ 0x002df184  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df184(undefined1 (*param_1) [16]) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df184()
{
    sk_u128_t * arg1;
    sk_u128_t buf1;
    {
      buf1 = sk_zext((unsigned long)sk_slice_002de43c());
      *arg1 = buf1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df1ac @ 0x002df1ac  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df1ac(undefined1 (*param_1) [16]) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df1ac()
{
    sk_u128_t * arg1;
    sk_u128_t buf1;
    {
      buf1 = sk_zext((unsigned long)sk_slice_002de514());
      *arg1 = buf1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df1dc @ 0x002df1dc  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df1dc(undefined1 (*param_1) [16],undefined8 *arg2,long *arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df1dc()
{
    sk_u128_t * arg1;
    unsigned long * arg2;
    long * arg3;
    sk_u128_t buf1;
    {
      if (*arg3 != 0 || arg3[1] != 0) {
        buf1 = sk_zext((unsigned long)sk_h_0011db10(*arg2,arg2[1]));
        *arg1 = buf1;
        return;
      }
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c(sk_str_005accd0,0xb,2,sk_str_005cd710,0x10,2,
                   sk_str_005d1010,0x13,2,0x165,1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df268 @ 0x002df268  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df268(undefined1 (*param_1) [16],long *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df268()
{
    sk_u128_t * arg1;
    long * arg2;
    sk_u128_t buf1;
    {
      if (*arg2 != 0 || arg2[1] != 0) {
        buf1 = sk_zext((unsigned long)sk_h_0011db10(*(unsigned long *)arg1,*(unsigned long *)(((unsigned char *)arg1 + 8))));
        *arg1 = buf1;
        return;
      }
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c(sk_str_005accd0,0xb,2,sk_str_005cd710,0x10,2,
                   sk_str_005d1010,0x13,2,0x165,1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df2f4 @ 0x002df2f4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df2f4(undefined1 (*param_1) [16],undefined8 *arg2,long *arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df2f4()
{
    sk_u128_t * arg1;
    unsigned long * arg2;
    long * arg3;
    sk_u128_t buf1;
    {
      if (*arg3 != 0 || arg3[1] != 0) {
        buf1 = sk_zext((unsigned long)sk_h_0011db18(*arg2,arg2[1]));
        *arg1 = buf1;
        return;
      }
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c(sk_str_005accd0,0xb,2,sk_str_005ce4a0,0x27,2,
                   sk_str_005d1010,0x13,2,0x175,1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df380 @ 0x002df380  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df380(undefined1 (*param_1) [16],long *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df380()
{
    sk_u128_t * arg1;
    long * arg2;
    sk_u128_t buf1;
    {
      if (*arg2 != 0 || arg2[1] != 0) {
        buf1 = sk_zext((unsigned long)sk_h_0011db18(*(unsigned long *)arg1,*(unsigned long *)(((unsigned char *)arg1 + 8))));
        *arg1 = buf1;
        return;
      }
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c(sk_str_005accd0,0xb,2,sk_str_005ce4a0,0x27,2,
                   sk_str_005d1010,0x13,2,0x175,1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002df40c @ 0x002df40c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002df40c(ulong *param_1,ulong *arg2,undefined8 arg3,long param_4,undefined8 param_5) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002df40c()
{
    unsigned long * arg1;
    unsigned long * arg2;
    unsigned long arg3;
    long arg4;
    unsigned long arg5;
    unsigned char * pval1;
    bool bval2;
    unsigned long tmp3;
    long lval4;
    sk_fn fptr5;
    unsigned long tmp6;
    sk_fn fptr7;
    long lval8;
    unsigned long tmp9;
    char * fptr10;
    long outx8;
    long outx8_00;
    unsigned long tmp11;
    unsigned long tmp12;
    unsigned long tmp13;
    long outx12;
    long lval14;
    long lval15;
    unsigned char bufc0 [8];
    unsigned long stackb8;
    unsigned int bufb0 [4];
    unsigned char bufa0 [8];
    long var98;
    unsigned char * var90;
    unsigned long var88;
    unsigned long stack80;
    unsigned long * var78;
    long var70;
    unsigned long var68;
    {
      var78 = arg1;
      sk_h_0008f6c0(arg5);
      tmp3 = sk_h_0008f6f4();
      lval4 = sk_h_00377824(0,tmp3,arg4,sk_h_0060e3fc,sk_h_0060e40c);
      sk_g_dispatch(*(long *)(*(long *)(lval4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
      var70 = *(long *)(arg4 + -8);
      var90 = bufa0 + -outx8;
      sk_g_dispatch(*(unsigned long *)(var70 + 0x40));
      lval14 = (long)(bufa0 + -outx8) - (outx8_00 + 0xfU & 0xfffffffffffffff0);
      sk_g_dispatch();
      lval15 = lval14 - outx12;
      var88 = *arg2;
      stack80 = arg2[1];
      fptr5 = (sk_fn)sk_h_00310a14(arg5);
      tmp6 = fptr5(arg4,arg5);
      if ((tmp6 & 1) == 0) {
        tmp6 = fptr5(arg4,arg5);
        fptr7 = (sk_fn)sk_h_00310a44(arg5);
        lval8 = fptr7(arg4,arg5);
        if ((tmp6 & 1) == 0) {
          if (0x3f < lval8) goto L002df40c_002df690;
          goto L002df40c_002df668;
        }
        if (0x40 < lval8) goto L002df40c_002df5cc;
        var98 = lval14;
        tmp9 = sk_h_00377bec(tmp3,arg4,lval4,sk_h_0060e3fc,((unsigned long)0));
        fptr7 = (sk_fn)sk_h_0008f728();
        pval1 = var90;
        fptr7(var90,&sk_dat_004c1010,0x100,lval4,tmp9);
        fptr7 = (sk_fn)sk_h_0008f758(tmp3);
        fptr7(lval15,pval1,arg4,tmp3);
        sk_h_00310ad4(arg5);
        tmp9 = sk_h_00027754();
        fptr7 = (sk_fn)sk_h_0016186c();
        tmp6 = fptr7(arg3,lval15,arg4,tmp9);
        ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
        if ((tmp6 & 1) == 0) {
          fptr7 = (sk_fn)sk_h_003109b4(arg5);
          lval8 = fptr7(arg4,arg5);
          lval14 = var98;
          if (-0x81 < lval8) goto L002df40c_002df690;
        }
      }
      else {
        fptr7 = (sk_fn)sk_h_00310a44(arg5);
        lval8 = fptr7(arg4,arg5);
        if (lval8 < 0x40) {
    L002df40c_002df668:
          fptr7 = (sk_fn)sk_h_003109b4(arg5);
          lval8 = fptr7(arg4,arg5);
          if (lval8 < -0x80) goto L002df40c_002df93c;
        }
        else {
    L002df40c_002df5cc:
          var68 = 0xffffffffffffff80;
          fptr7 = (sk_fn)sk_h_00310a74(arg5);
          tmp9 = sk_h_0001df60();
          fptr7(lval15,&var68,0x677880,tmp9,arg4,arg5);
          sk_h_00310ad4(arg5);
          tmp9 = sk_h_00027754();
          fptr7 = (sk_fn)sk_h_0016186c();
          tmp6 = fptr7(arg3,lval15,arg4,tmp9);
          ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
          if ((tmp6 & 1) != 0) goto L002df40c_002df93c;
        }
    L002df40c_002df690:
        tmp6 = fptr5(arg4,arg5);
        fptr7 = (sk_fn)sk_h_00310a44(arg5);
        lval8 = fptr7(arg4,arg5);
        if ((tmp6 & 1) == 0) {
          if (lval8 < 0x40) goto L002df40c_002df6d4;
    L002df40c_002df708:
          var68 = 0x80;
          fptr7 = (sk_fn)sk_h_00310a74(arg5);
          tmp9 = sk_h_0001df60();
          fptr7(lval15,&var68,0x677880,tmp9,arg4,arg5);
          sk_h_00310ad4(arg5);
          tmp9 = sk_h_00027754();
          fptr7 = (sk_fn)sk_h_0016186c();
          tmp6 = fptr7(lval15,arg3,arg4,tmp9);
          ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
          if ((tmp6 & 1) != 0) goto L002df40c_002df93c;
        }
        else {
          if (0x40 < lval8) goto L002df40c_002df708;
    L002df40c_002df6d4:
          fptr7 = (sk_fn)sk_h_003109b4(arg5);
          lval8 = fptr7(arg4,arg5);
          if (0x80 < lval8) goto L002df40c_002df93c;
        }
        ((sk_fn)*(void **)(var70 + 0x10))(lval14,arg3,arg4);
        tmp6 = fptr5(arg4,arg5);
        if ((tmp6 & 1) != 0) {
          fptr7 = (sk_fn)sk_h_00310a44(arg5);
          lval8 = fptr7(arg4,arg5);
          if (0x40 < lval8) {
            tmp6 = fptr5(arg4,arg5);
            if ((tmp6 & 1) == 0) {
              tmp6 = fptr5(arg4,arg5);
              lval8 = fptr7(arg4,arg5);
              if ((tmp6 & 1) != 0) {
                if (0x40 < lval8) goto L002df40c_002df980;
                tmp9 = sk_h_00377bec(tmp3,arg4,lval4,sk_h_0060e3fc,((unsigned long)0));
                fptr7 = (sk_fn)sk_h_0008f728();
                pval1 = var90;
                fptr7(var90,&sk_dat_004c1010,0x100,lval4,tmp9);
                fptr7 = (sk_fn)sk_h_0008f758(tmp3);
                fptr7(lval15,pval1,arg4,tmp3);
                sk_h_00310ad4(arg5);
                tmp3 = sk_h_00027754();
                fptr7 = (sk_fn)sk_h_0016186c();
                tmp6 = fptr7(lval14,lval15,arg4,tmp3);
                ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
                if ((tmp6 & 1) == 0) goto L002df40c_002dfb30;
    L002df40c_002dfa14:
                *(unsigned int *)(lval15 + -0x10) = 1;
                *(unsigned long *)(lval15 + -0x18) = 0xdcd;
                *(unsigned char *)(lval15 + -0x20) = 2;
                fptr10 = sk_str_005cd6a0;
                tmp3 = 0x2b;
                goto L002df40c_002dfc84;
              }
              if (lval8 < 0x40) goto L002df40c_002dfb30;
            }
            else {
              lval4 = fptr7(arg4,arg5);
              if (lval4 < 0x40) {
    L002df40c_002dfb30:
                fptr7 = (sk_fn)sk_h_003109b4(arg5);
                fptr7(arg4,arg5);
              }
              else {
    L002df40c_002df980:
                var68 = 0x8000000000000000;
                fptr7 = (sk_fn)sk_h_00310a74(arg5);
                tmp3 = sk_h_0001df60();
                fptr7(lval15,&var68,0x677880,tmp3,arg4,arg5);
                sk_h_00310ad4(arg5);
                tmp3 = sk_h_00027754();
                fptr7 = (sk_fn)sk_h_0016186c();
                tmp6 = fptr7(lval14,lval15,arg4,tmp3);
                ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
                if ((tmp6 & 1) != 0) goto L002df40c_002dfa14;
              }
            }
          }
        }
        fptr7 = (sk_fn)sk_h_00310a44(arg5);
        lval4 = fptr7(arg4,arg5);
        if ((0x40 < lval4) ||
           ((lval4 = fptr7(arg4,arg5), lval4 == 0x40 &&
            (tmp6 = fptr5(arg4,arg5), (tmp6 & 1) == 0)))) {
          tmp6 = fptr5(arg4,arg5);
          lval4 = fptr7(arg4,arg5);
          if ((tmp6 & 1) == 0) {
            if (lval4 < 0x40) goto L002df40c_002dfcd4;
          }
          else if (lval4 < 0x41) {
    L002df40c_002dfcd4:
            fptr5 = (sk_fn)sk_h_003109b4(arg5);
            fptr5(arg4,arg5);
            goto L002df40c_002dfcf4;
          }
          var68 = 0x7fffffffffffffff;
          fptr5 = (sk_fn)sk_h_00310a74(arg5);
          tmp3 = sk_h_0001df60();
          fptr5(lval15,&var68,0x677880,tmp3,arg4,arg5);
          sk_h_00310ad4(arg5);
          tmp3 = sk_h_00027754();
          fptr5 = (sk_fn)sk_h_0016186c();
          tmp6 = fptr5(lval15,lval14,arg4,tmp3);
          ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
          if ((tmp6 & 1) != 0) {
            *(unsigned int *)(lval15 + -0x10) = 1;
            *(unsigned long *)(lval15 + -0x18) = 0xdd3;
            *(unsigned char *)(lval15 + -0x20) = 2;
            fptr10 = sk_str_005cd650;
            tmp3 = 0x2d;
    L002df40c_002dfc84:
                        /* WARNING: Subroutine does not return */
            sk_h_001afe4c(sk_str_005accd0,0xb,2,fptr10,tmp3,2,sk_str_005cd680,
                         0x14);
          }
        }
    L002df40c_002dfcf4:
        fptr5 = (sk_fn)sk_h_003109b4(arg5);
        tmp6 = fptr5(arg4,arg5);
        ((sk_fn)*(void **)(var70 + 8))(lval14,arg4);
        if ((long)tmp6 < 0) {
          if (0xffffffffffffff80 < tmp6) {
            tmp6 = -tmp6;
            tmp13 = var88 << (tmp6 & 0x3f);
            bval2 = (tmp6 & 0x40) == 0;
            tmp11 = 0;
            if (bval2) {
              tmp11 = tmp13;
            }
            if (bval2) {
              tmp13 = stack80 << (tmp6 & 0x3f) | (var88 >> 1) >> ((unsigned long)~(unsigned int)tmp6 & 0x3f);
            }
            goto L002df40c_002dfd74;
          }
        }
        else if (tmp6 < 0x80) {
          tmp6 = sk_h_0035723c(tmp6);
          tmp12 = stack80 >> (tmp6 & 0x3f);
          bval2 = (tmp6 & 0x40) == 0;
          tmp11 = tmp12;
          if (bval2) {
            tmp11 = (stack80 << 1) << ((unsigned long)~(unsigned int)tmp6 & 0x3f) | var88 >> (tmp6 & 0x3f);
          }
          tmp13 = 0;
          if (bval2) {
            tmp13 = tmp12;
          }
          goto L002df40c_002dfd74;
        }
      }
    L002df40c_002df93c:
      tmp11 = 0;
      tmp13 = 0;
    L002df40c_002dfd74:
      *var78 = tmp11;
      var78[1] = tmp13;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002dfdd4 @ 0x002dfdd4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002dfdd4(ulong *param_1,undefined8 arg2,long arg3,undefined8 param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002dfdd4()
{
    unsigned long * arg1;
    unsigned long arg2;
    long arg3;
    unsigned long arg4;
    unsigned long tmp1;
    unsigned char * pval2;
    bool bval3;
    unsigned long tmp4;
    long lval5;
    sk_fn fptr6;
    unsigned long tmp7;
    sk_fn fptr8;
    long lval9;
    unsigned long tmp10;
    unsigned long tmp11;
    char * fptr12;
    long outx8;
    long outx8_00;
    unsigned long tmp13;
    unsigned long tmp14;
    unsigned long tmp15;
    long outx12;
    unsigned long * pval16;
    long lval17;
    long lval18;
    unsigned char bufb0 [8];
    unsigned long stacka8;
    unsigned int bufa0 [4];
    unsigned char buf90 [8];
    long var88;
    unsigned char * var80;
    unsigned long * var78;
    long var70;
    unsigned long var68;
    {
      var78 = arg1;
      sk_h_0008f6c0(arg4);
      tmp4 = sk_h_0008f6f4();
      lval5 = sk_h_00377824(0,tmp4,arg3,sk_h_0060e3fc,sk_h_0060e40c);
      sk_g_dispatch(*(long *)(*(long *)(lval5 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
      var70 = *(long *)(arg3 + -8);
      var80 = buf90 + -outx8;
      sk_g_dispatch(*(unsigned long *)(var70 + 0x40));
      lval17 = (long)(buf90 + -outx8) - (outx8_00 + 0xfU & 0xfffffffffffffff0);
      sk_g_dispatch();
      lval18 = lval17 - outx12;
      fptr6 = (sk_fn)sk_h_00310a14(arg4);
      tmp7 = fptr6(arg3,arg4);
      if ((tmp7 & 1) == 0) {
        tmp7 = fptr6(arg3,arg4);
        fptr8 = (sk_fn)sk_h_00310a44(arg4);
        lval9 = fptr8(arg3,arg4);
        if ((tmp7 & 1) == 0) {
          if (0x3f < lval9) goto L002dfdd4_002e004c;
          goto L002dfdd4_002e0024;
        }
        if (0x40 < lval9) goto L002dfdd4_002dff88;
        var88 = lval17;
        tmp10 = sk_h_00377bec(tmp4,arg3,lval5,sk_h_0060e3fc,((unsigned long)0));
        fptr8 = (sk_fn)sk_h_0008f728();
        pval2 = var80;
        fptr8(var80,&sk_dat_004c1010,0x100,lval5,tmp10);
        fptr8 = (sk_fn)sk_h_0008f758(tmp4);
        fptr8(lval18,pval2,arg3,tmp4);
        sk_h_00310ad4(arg4);
        tmp10 = sk_h_00027754();
        fptr8 = (sk_fn)sk_h_0016186c();
        tmp7 = fptr8(arg2,lval18,arg3,tmp10);
        ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
        if ((tmp7 & 1) == 0) {
          fptr8 = (sk_fn)sk_h_003109b4(arg4);
          lval9 = fptr8(arg3,arg4);
          lval17 = var88;
          if (-0x81 < lval9) goto L002dfdd4_002e004c;
        }
      }
      else {
        fptr8 = (sk_fn)sk_h_00310a44(arg4);
        lval9 = fptr8(arg3,arg4);
        if (lval9 < 0x40) {
    L002dfdd4_002e0024:
          fptr8 = (sk_fn)sk_h_003109b4(arg4);
          lval9 = fptr8(arg3,arg4);
          if (lval9 < -0x80) goto L002dfdd4_002e02f8;
        }
        else {
    L002dfdd4_002dff88:
          var68 = 0xffffffffffffff80;
          fptr8 = (sk_fn)sk_h_00310a74(arg4);
          tmp10 = sk_h_0001df60();
          fptr8(lval18,&var68,0x677880,tmp10,arg3,arg4);
          sk_h_00310ad4(arg4);
          tmp10 = sk_h_00027754();
          fptr8 = (sk_fn)sk_h_0016186c();
          tmp7 = fptr8(arg2,lval18,arg3,tmp10);
          ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
          if ((tmp7 & 1) != 0) goto L002dfdd4_002e02f8;
        }
    L002dfdd4_002e004c:
        tmp7 = fptr6(arg3,arg4);
        fptr8 = (sk_fn)sk_h_00310a44(arg4);
        lval9 = fptr8(arg3,arg4);
        if ((tmp7 & 1) == 0) {
          if (lval9 < 0x40) goto L002dfdd4_002e0090;
    L002dfdd4_002e00c4:
          var68 = 0x80;
          fptr8 = (sk_fn)sk_h_00310a74(arg4);
          tmp10 = sk_h_0001df60();
          fptr8(lval18,&var68,0x677880,tmp10,arg3,arg4);
          sk_h_00310ad4(arg4);
          tmp10 = sk_h_00027754();
          fptr8 = (sk_fn)sk_h_0016186c();
          tmp7 = fptr8(lval18,arg2,arg3,tmp10);
          ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
          if ((tmp7 & 1) != 0) goto L002dfdd4_002e02f8;
        }
        else {
          if (0x40 < lval9) goto L002dfdd4_002e00c4;
    L002dfdd4_002e0090:
          fptr8 = (sk_fn)sk_h_003109b4(arg4);
          lval9 = fptr8(arg3,arg4);
          if (0x80 < lval9) goto L002dfdd4_002e02f8;
        }
        ((sk_fn)*(void **)(var70 + 0x10))(lval17,arg2,arg3);
        tmp7 = fptr6(arg3,arg4);
        if ((tmp7 & 1) != 0) {
          fptr8 = (sk_fn)sk_h_00310a44(arg4);
          lval9 = fptr8(arg3,arg4);
          if (0x40 < lval9) {
            tmp7 = fptr6(arg3,arg4);
            if ((tmp7 & 1) == 0) {
              tmp7 = fptr6(arg3,arg4);
              lval9 = fptr8(arg3,arg4);
              if ((tmp7 & 1) != 0) {
                if (0x40 < lval9) goto L002dfdd4_002e0340;
                tmp10 = sk_h_00377bec(tmp4,arg3,lval5,sk_h_0060e3fc,((unsigned long)0));
                fptr8 = (sk_fn)sk_h_0008f728();
                pval2 = var80;
                fptr8(var80,&sk_dat_004c1010,0x100,lval5,tmp10);
                fptr8 = (sk_fn)sk_h_0008f758(tmp4);
                fptr8(lval18,pval2,arg3,tmp4);
                sk_h_00310ad4(arg4);
                tmp4 = sk_h_00027754();
                fptr8 = (sk_fn)sk_h_0016186c();
                tmp7 = fptr8(lval17,lval18,arg3,tmp4);
                ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
                if ((tmp7 & 1) == 0) goto L002dfdd4_002e04f0;
    L002dfdd4_002e03d4:
                *(unsigned int *)(lval18 + -0x10) = 1;
                *(unsigned long *)(lval18 + -0x18) = 0xdcd;
                *(unsigned char *)(lval18 + -0x20) = 2;
                fptr12 = sk_str_005cd6a0;
                tmp4 = 0x2b;
                goto L002dfdd4_002e0644;
              }
              if (lval9 < 0x40) goto L002dfdd4_002e04f0;
            }
            else {
              lval5 = fptr8(arg3,arg4);
              if (lval5 < 0x40) {
    L002dfdd4_002e04f0:
                fptr8 = (sk_fn)sk_h_003109b4(arg4);
                fptr8(arg3,arg4);
              }
              else {
    L002dfdd4_002e0340:
                var68 = 0x8000000000000000;
                fptr8 = (sk_fn)sk_h_00310a74(arg4);
                tmp4 = sk_h_0001df60();
                fptr8(lval18,&var68,0x677880,tmp4,arg3,arg4);
                sk_h_00310ad4(arg4);
                tmp4 = sk_h_00027754();
                fptr8 = (sk_fn)sk_h_0016186c();
                tmp7 = fptr8(lval17,lval18,arg3,tmp4);
                ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
                if ((tmp7 & 1) != 0) goto L002dfdd4_002e03d4;
              }
            }
          }
        }
        fptr8 = (sk_fn)sk_h_00310a44(arg4);
        lval5 = fptr8(arg3,arg4);
        if ((0x40 < lval5) ||
           ((lval5 = fptr8(arg3,arg4), lval5 == 0x40 &&
            (tmp7 = fptr6(arg3,arg4), (tmp7 & 1) == 0)))) {
          tmp7 = fptr6(arg3,arg4);
          lval5 = fptr8(arg3,arg4);
          if ((tmp7 & 1) == 0) {
            if (lval5 < 0x40) goto L002dfdd4_002e0694;
          }
          else if (lval5 < 0x41) {
    L002dfdd4_002e0694:
            fptr6 = (sk_fn)sk_h_003109b4(arg4);
            fptr6(arg3,arg4);
            goto L002dfdd4_002e06b4;
          }
          var68 = 0x7fffffffffffffff;
          fptr6 = (sk_fn)sk_h_00310a74(arg4);
          tmp4 = sk_h_0001df60();
          fptr6(lval18,&var68,0x677880,tmp4,arg3,arg4);
          sk_h_00310ad4(arg4);
          tmp4 = sk_h_00027754();
          fptr6 = (sk_fn)sk_h_0016186c();
          tmp7 = fptr6(lval18,lval17,arg3,tmp4);
          ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
          if ((tmp7 & 1) != 0) {
            *(unsigned int *)(lval18 + -0x10) = 1;
            *(unsigned long *)(lval18 + -0x18) = 0xdd3;
            *(unsigned char *)(lval18 + -0x20) = 2;
            fptr12 = sk_str_005cd650;
            tmp4 = 0x2d;
    L002dfdd4_002e0644:
                        /* WARNING: Subroutine does not return */
            sk_h_001afe4c(sk_str_005accd0,0xb,2,fptr12,tmp4,2,sk_str_005cd680,
                         0x14);
          }
        }
    L002dfdd4_002e06b4:
        fptr6 = (sk_fn)sk_h_003109b4(arg4);
        tmp11 = fptr6(arg3,arg4);
        ((sk_fn)*(void **)(var70 + 8))(lval17,arg3);
        pval16 = var78;
        tmp7 = *var78;
        tmp1 = var78[1];
        if (-1 < (long)tmp11) {
          if (tmp11 < 0x80) {
            tmp11 = sk_h_0035723c(tmp11);
            tmp14 = tmp1 >> (tmp11 & 0x3f);
            bval3 = (tmp11 & 0x40) == 0;
            tmp13 = tmp14;
            if (bval3) {
              tmp13 = (tmp1 << 1) << ((unsigned long)~(unsigned int)tmp11 & 0x3f) | tmp7 >> (tmp11 & 0x3f);
            }
            tmp15 = 0;
            if (bval3) {
              tmp15 = tmp14;
            }
          }
          else {
            tmp13 = 0;
            tmp15 = 0;
          }
          goto L002dfdd4_002e0738;
        }
        if (0xffffffffffffff80 < tmp11) {
          tmp11 = -tmp11;
          tmp15 = tmp7 << (tmp11 & 0x3f);
          bval3 = (tmp11 & 0x40) == 0;
          tmp13 = 0;
          if (bval3) {
            tmp13 = tmp15;
          }
          if (bval3) {
            tmp15 = tmp1 << (tmp11 & 0x3f) | (tmp7 >> 1) >> ((unsigned long)~(unsigned int)tmp11 & 0x3f);
          }
          goto L002dfdd4_002e0738;
        }
      }
    L002dfdd4_002e02f8:
      tmp13 = 0;
      tmp15 = 0;
      pval16 = var78;
    L002dfdd4_002e0738:
      *pval16 = tmp13;
      pval16[1] = tmp15;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e079c @ 0x002e079c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e079c(ulong *param_1,ulong *arg2,undefined8 arg3,long param_4,undefined8 param_5) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e079c()
{
    unsigned long * arg1;
    unsigned long * arg2;
    unsigned long arg3;
    long arg4;
    unsigned long arg5;
    unsigned char * pval1;
    bool bval2;
    unsigned long tmp3;
    long lval4;
    sk_fn fptr5;
    unsigned long tmp6;
    sk_fn fptr7;
    long lval8;
    unsigned long tmp9;
    char * fptr10;
    long outx8;
    long outx8_00;
    unsigned long tmp11;
    unsigned long tmp12;
    unsigned long tmp13;
    long outx12;
    long lval14;
    long lval15;
    unsigned char bufc0 [8];
    unsigned long stackb8;
    unsigned int bufb0 [4];
    unsigned char bufa0 [8];
    long var98;
    unsigned char * var90;
    unsigned long var88;
    unsigned long stack80;
    unsigned long * var78;
    long var70;
    unsigned long var68;
    {
      var78 = arg1;
      sk_h_0008f6c0(arg5);
      tmp3 = sk_h_0008f6f4();
      lval4 = sk_h_00377824(0,tmp3,arg4,sk_h_0060e3fc,sk_h_0060e40c);
      sk_g_dispatch(*(long *)(*(long *)(lval4 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
      var70 = *(long *)(arg4 + -8);
      var90 = bufa0 + -outx8;
      sk_g_dispatch(*(unsigned long *)(var70 + 0x40));
      lval14 = (long)(bufa0 + -outx8) - (outx8_00 + 0xfU & 0xfffffffffffffff0);
      sk_g_dispatch();
      lval15 = lval14 - outx12;
      stack80 = *arg2;
      var88 = arg2[1];
      fptr5 = (sk_fn)sk_h_00310a14(arg5);
      tmp6 = fptr5(arg4,arg5);
      if ((tmp6 & 1) == 0) {
        tmp6 = fptr5(arg4,arg5);
        fptr7 = (sk_fn)sk_h_00310a44(arg5);
        lval8 = fptr7(arg4,arg5);
        if ((tmp6 & 1) == 0) {
          if (0x3f < lval8) goto L002e079c_002e0a20;
          goto L002e079c_002e09f8;
        }
        if (0x40 < lval8) goto L002e079c_002e095c;
        var98 = lval14;
        tmp9 = sk_h_00377bec(tmp3,arg4,lval4,sk_h_0060e3fc,((unsigned long)0));
        fptr7 = (sk_fn)sk_h_0008f728();
        pval1 = var90;
        fptr7(var90,&sk_dat_004c1010,0x100,lval4,tmp9);
        fptr7 = (sk_fn)sk_h_0008f758(tmp3);
        fptr7(lval15,pval1,arg4,tmp3);
        sk_h_00310ad4(arg5);
        tmp9 = sk_h_00027754();
        fptr7 = (sk_fn)sk_h_0016186c();
        tmp6 = fptr7(arg3,lval15,arg4,tmp9);
        ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
        if ((tmp6 & 1) == 0) {
          fptr7 = (sk_fn)sk_h_003109b4(arg5);
          lval8 = fptr7(arg4,arg5);
          lval14 = var98;
          if (-0x81 < lval8) goto L002e079c_002e0a20;
        }
      }
      else {
        fptr7 = (sk_fn)sk_h_00310a44(arg5);
        lval8 = fptr7(arg4,arg5);
        if (lval8 < 0x40) {
    L002e079c_002e09f8:
          fptr7 = (sk_fn)sk_h_003109b4(arg5);
          lval8 = fptr7(arg4,arg5);
          if (lval8 < -0x80) goto L002e079c_002e0ccc;
        }
        else {
    L002e079c_002e095c:
          var68 = 0xffffffffffffff80;
          fptr7 = (sk_fn)sk_h_00310a74(arg5);
          tmp9 = sk_h_0001df60();
          fptr7(lval15,&var68,0x677880,tmp9,arg4,arg5);
          sk_h_00310ad4(arg5);
          tmp9 = sk_h_00027754();
          fptr7 = (sk_fn)sk_h_0016186c();
          tmp6 = fptr7(arg3,lval15,arg4,tmp9);
          ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
          if ((tmp6 & 1) != 0) goto L002e079c_002e0ccc;
        }
    L002e079c_002e0a20:
        tmp6 = fptr5(arg4,arg5);
        fptr7 = (sk_fn)sk_h_00310a44(arg5);
        lval8 = fptr7(arg4,arg5);
        if ((tmp6 & 1) == 0) {
          if (lval8 < 0x40) goto L002e079c_002e0a64;
    L002e079c_002e0a98:
          var68 = 0x80;
          fptr7 = (sk_fn)sk_h_00310a74(arg5);
          tmp9 = sk_h_0001df60();
          fptr7(lval15,&var68,0x677880,tmp9,arg4,arg5);
          sk_h_00310ad4(arg5);
          tmp9 = sk_h_00027754();
          fptr7 = (sk_fn)sk_h_0016186c();
          tmp6 = fptr7(lval15,arg3,arg4,tmp9);
          ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
          if ((tmp6 & 1) != 0) goto L002e079c_002e0ccc;
        }
        else {
          if (0x40 < lval8) goto L002e079c_002e0a98;
    L002e079c_002e0a64:
          fptr7 = (sk_fn)sk_h_003109b4(arg5);
          lval8 = fptr7(arg4,arg5);
          if (0x80 < lval8) goto L002e079c_002e0ccc;
        }
        ((sk_fn)*(void **)(var70 + 0x10))(lval14,arg3,arg4);
        tmp6 = fptr5(arg4,arg5);
        if ((tmp6 & 1) != 0) {
          fptr7 = (sk_fn)sk_h_00310a44(arg5);
          lval8 = fptr7(arg4,arg5);
          if (0x40 < lval8) {
            tmp6 = fptr5(arg4,arg5);
            if ((tmp6 & 1) == 0) {
              tmp6 = fptr5(arg4,arg5);
              lval8 = fptr7(arg4,arg5);
              if ((tmp6 & 1) != 0) {
                if (0x40 < lval8) goto L002e079c_002e0d10;
                tmp9 = sk_h_00377bec(tmp3,arg4,lval4,sk_h_0060e3fc,((unsigned long)0));
                fptr7 = (sk_fn)sk_h_0008f728();
                pval1 = var90;
                fptr7(var90,&sk_dat_004c1010,0x100,lval4,tmp9);
                fptr7 = (sk_fn)sk_h_0008f758(tmp3);
                fptr7(lval15,pval1,arg4,tmp3);
                sk_h_00310ad4(arg5);
                tmp3 = sk_h_00027754();
                fptr7 = (sk_fn)sk_h_0016186c();
                tmp6 = fptr7(lval14,lval15,arg4,tmp3);
                ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
                if ((tmp6 & 1) == 0) goto L002e079c_002e0ec0;
    L002e079c_002e0da4:
                *(unsigned int *)(lval15 + -0x10) = 1;
                *(unsigned long *)(lval15 + -0x18) = 0xdcd;
                *(unsigned char *)(lval15 + -0x20) = 2;
                fptr10 = sk_str_005cd6a0;
                tmp3 = 0x2b;
                goto L002e079c_002e1014;
              }
              if (lval8 < 0x40) goto L002e079c_002e0ec0;
            }
            else {
              lval4 = fptr7(arg4,arg5);
              if (lval4 < 0x40) {
    L002e079c_002e0ec0:
                fptr7 = (sk_fn)sk_h_003109b4(arg5);
                fptr7(arg4,arg5);
              }
              else {
    L002e079c_002e0d10:
                var68 = 0x8000000000000000;
                fptr7 = (sk_fn)sk_h_00310a74(arg5);
                tmp3 = sk_h_0001df60();
                fptr7(lval15,&var68,0x677880,tmp3,arg4,arg5);
                sk_h_00310ad4(arg5);
                tmp3 = sk_h_00027754();
                fptr7 = (sk_fn)sk_h_0016186c();
                tmp6 = fptr7(lval14,lval15,arg4,tmp3);
                ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
                if ((tmp6 & 1) != 0) goto L002e079c_002e0da4;
              }
            }
          }
        }
        fptr7 = (sk_fn)sk_h_00310a44(arg5);
        lval4 = fptr7(arg4,arg5);
        if ((0x40 < lval4) ||
           ((lval4 = fptr7(arg4,arg5), lval4 == 0x40 &&
            (tmp6 = fptr5(arg4,arg5), (tmp6 & 1) == 0)))) {
          tmp6 = fptr5(arg4,arg5);
          lval4 = fptr7(arg4,arg5);
          if ((tmp6 & 1) == 0) {
            if (lval4 < 0x40) goto L002e079c_002e1064;
          }
          else if (lval4 < 0x41) {
    L002e079c_002e1064:
            fptr5 = (sk_fn)sk_h_003109b4(arg5);
            fptr5(arg4,arg5);
            goto L002e079c_002e1084;
          }
          var68 = 0x7fffffffffffffff;
          fptr5 = (sk_fn)sk_h_00310a74(arg5);
          tmp3 = sk_h_0001df60();
          fptr5(lval15,&var68,0x677880,tmp3,arg4,arg5);
          sk_h_00310ad4(arg5);
          tmp3 = sk_h_00027754();
          fptr5 = (sk_fn)sk_h_0016186c();
          tmp6 = fptr5(lval15,lval14,arg4,tmp3);
          ((sk_fn)*(void **)(var70 + 8))(lval15,arg4);
          if ((tmp6 & 1) != 0) {
            *(unsigned int *)(lval15 + -0x10) = 1;
            *(unsigned long *)(lval15 + -0x18) = 0xdd3;
            *(unsigned char *)(lval15 + -0x20) = 2;
            fptr10 = sk_str_005cd650;
            tmp3 = 0x2d;
    L002e079c_002e1014:
                        /* WARNING: Subroutine does not return */
            sk_h_001afe4c(sk_str_005accd0,0xb,2,fptr10,tmp3,2,sk_str_005cd680,
                         0x14);
          }
        }
    L002e079c_002e1084:
        fptr5 = (sk_fn)sk_h_003109b4(arg5);
        tmp6 = fptr5(arg4,arg5);
        ((sk_fn)*(void **)(var70 + 8))(lval14,arg4);
        if ((long)tmp6 < 0) {
          if (0xffffffffffffff80 < tmp6) {
            tmp6 = -tmp6;
            tmp13 = var88 >> (tmp6 & 0x3f);
            bval2 = (tmp6 & 0x40) == 0;
            tmp11 = 0;
            if (bval2) {
              tmp11 = tmp13;
            }
            if (bval2) {
              tmp13 = (var88 << 1) << ((unsigned long)~(unsigned int)tmp6 & 0x3f) | stack80 >> (tmp6 & 0x3f);
            }
            goto L002e079c_002e1104;
          }
        }
        else if (tmp6 < 0x80) {
          tmp6 = sk_h_0035723c(tmp6);
          tmp12 = stack80 << (tmp6 & 0x3f);
          bval2 = (tmp6 & 0x40) == 0;
          tmp11 = tmp12;
          if (bval2) {
            tmp11 = var88 << (tmp6 & 0x3f) | (stack80 >> 1) >> ((unsigned long)~(unsigned int)tmp6 & 0x3f);
          }
          tmp13 = 0;
          if (bval2) {
            tmp13 = tmp12;
          }
          goto L002e079c_002e1104;
        }
      }
    L002e079c_002e0ccc:
      tmp11 = 0;
      tmp13 = 0;
    L002e079c_002e1104:
      *var78 = tmp13;
      var78[1] = tmp11;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1164 @ 0x002e1164  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1164(ulong *param_1,undefined8 arg2,long arg3,undefined8 param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1164()
{
    unsigned long * arg1;
    unsigned long arg2;
    long arg3;
    unsigned long arg4;
    unsigned long tmp1;
    unsigned char * pval2;
    bool bval3;
    unsigned long tmp4;
    long lval5;
    sk_fn fptr6;
    unsigned long tmp7;
    sk_fn fptr8;
    long lval9;
    unsigned long tmp10;
    unsigned long tmp11;
    char * fptr12;
    long outx8;
    long outx8_00;
    unsigned long tmp13;
    unsigned long tmp14;
    unsigned long tmp15;
    long outx12;
    unsigned long * pval16;
    long lval17;
    long lval18;
    unsigned char bufb0 [8];
    unsigned long stacka8;
    unsigned int bufa0 [4];
    unsigned char buf90 [8];
    long var88;
    unsigned char * var80;
    unsigned long * var78;
    long var70;
    unsigned long var68;
    {
      var78 = arg1;
      sk_h_0008f6c0(arg4);
      tmp4 = sk_h_0008f6f4();
      lval5 = sk_h_00377824(0,tmp4,arg3,sk_h_0060e3fc,sk_h_0060e40c);
      sk_g_dispatch(*(long *)(*(long *)(lval5 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
      var70 = *(long *)(arg3 + -8);
      var80 = buf90 + -outx8;
      sk_g_dispatch(*(unsigned long *)(var70 + 0x40));
      lval17 = (long)(buf90 + -outx8) - (outx8_00 + 0xfU & 0xfffffffffffffff0);
      sk_g_dispatch();
      lval18 = lval17 - outx12;
      fptr6 = (sk_fn)sk_h_00310a14(arg4);
      tmp7 = fptr6(arg3,arg4);
      if ((tmp7 & 1) == 0) {
        tmp7 = fptr6(arg3,arg4);
        fptr8 = (sk_fn)sk_h_00310a44(arg4);
        lval9 = fptr8(arg3,arg4);
        if ((tmp7 & 1) == 0) {
          if (0x3f < lval9) goto L002e1164_002e13dc;
          goto L002e1164_002e13b4;
        }
        if (0x40 < lval9) goto L002e1164_002e1318;
        var88 = lval17;
        tmp10 = sk_h_00377bec(tmp4,arg3,lval5,sk_h_0060e3fc,((unsigned long)0));
        fptr8 = (sk_fn)sk_h_0008f728();
        pval2 = var80;
        fptr8(var80,&sk_dat_004c1010,0x100,lval5,tmp10);
        fptr8 = (sk_fn)sk_h_0008f758(tmp4);
        fptr8(lval18,pval2,arg3,tmp4);
        sk_h_00310ad4(arg4);
        tmp10 = sk_h_00027754();
        fptr8 = (sk_fn)sk_h_0016186c();
        tmp7 = fptr8(arg2,lval18,arg3,tmp10);
        ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
        if ((tmp7 & 1) == 0) {
          fptr8 = (sk_fn)sk_h_003109b4(arg4);
          lval9 = fptr8(arg3,arg4);
          lval17 = var88;
          if (-0x81 < lval9) goto L002e1164_002e13dc;
        }
      }
      else {
        fptr8 = (sk_fn)sk_h_00310a44(arg4);
        lval9 = fptr8(arg3,arg4);
        if (lval9 < 0x40) {
    L002e1164_002e13b4:
          fptr8 = (sk_fn)sk_h_003109b4(arg4);
          lval9 = fptr8(arg3,arg4);
          if (lval9 < -0x80) goto L002e1164_002e1688;
        }
        else {
    L002e1164_002e1318:
          var68 = 0xffffffffffffff80;
          fptr8 = (sk_fn)sk_h_00310a74(arg4);
          tmp10 = sk_h_0001df60();
          fptr8(lval18,&var68,0x677880,tmp10,arg3,arg4);
          sk_h_00310ad4(arg4);
          tmp10 = sk_h_00027754();
          fptr8 = (sk_fn)sk_h_0016186c();
          tmp7 = fptr8(arg2,lval18,arg3,tmp10);
          ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
          if ((tmp7 & 1) != 0) goto L002e1164_002e1688;
        }
    L002e1164_002e13dc:
        tmp7 = fptr6(arg3,arg4);
        fptr8 = (sk_fn)sk_h_00310a44(arg4);
        lval9 = fptr8(arg3,arg4);
        if ((tmp7 & 1) == 0) {
          if (lval9 < 0x40) goto L002e1164_002e1420;
    L002e1164_002e1454:
          var68 = 0x80;
          fptr8 = (sk_fn)sk_h_00310a74(arg4);
          tmp10 = sk_h_0001df60();
          fptr8(lval18,&var68,0x677880,tmp10,arg3,arg4);
          sk_h_00310ad4(arg4);
          tmp10 = sk_h_00027754();
          fptr8 = (sk_fn)sk_h_0016186c();
          tmp7 = fptr8(lval18,arg2,arg3,tmp10);
          ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
          if ((tmp7 & 1) != 0) goto L002e1164_002e1688;
        }
        else {
          if (0x40 < lval9) goto L002e1164_002e1454;
    L002e1164_002e1420:
          fptr8 = (sk_fn)sk_h_003109b4(arg4);
          lval9 = fptr8(arg3,arg4);
          if (0x80 < lval9) goto L002e1164_002e1688;
        }
        ((sk_fn)*(void **)(var70 + 0x10))(lval17,arg2,arg3);
        tmp7 = fptr6(arg3,arg4);
        if ((tmp7 & 1) != 0) {
          fptr8 = (sk_fn)sk_h_00310a44(arg4);
          lval9 = fptr8(arg3,arg4);
          if (0x40 < lval9) {
            tmp7 = fptr6(arg3,arg4);
            if ((tmp7 & 1) == 0) {
              tmp7 = fptr6(arg3,arg4);
              lval9 = fptr8(arg3,arg4);
              if ((tmp7 & 1) != 0) {
                if (0x40 < lval9) goto L002e1164_002e16d0;
                tmp10 = sk_h_00377bec(tmp4,arg3,lval5,sk_h_0060e3fc,((unsigned long)0));
                fptr8 = (sk_fn)sk_h_0008f728();
                pval2 = var80;
                fptr8(var80,&sk_dat_004c1010,0x100,lval5,tmp10);
                fptr8 = (sk_fn)sk_h_0008f758(tmp4);
                fptr8(lval18,pval2,arg3,tmp4);
                sk_h_00310ad4(arg4);
                tmp4 = sk_h_00027754();
                fptr8 = (sk_fn)sk_h_0016186c();
                tmp7 = fptr8(lval17,lval18,arg3,tmp4);
                ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
                if ((tmp7 & 1) == 0) goto L002e1164_002e1880;
    L002e1164_002e1764:
                *(unsigned int *)(lval18 + -0x10) = 1;
                *(unsigned long *)(lval18 + -0x18) = 0xdcd;
                *(unsigned char *)(lval18 + -0x20) = 2;
                fptr12 = sk_str_005cd6a0;
                tmp4 = 0x2b;
                goto L002e1164_002e19d4;
              }
              if (lval9 < 0x40) goto L002e1164_002e1880;
            }
            else {
              lval5 = fptr8(arg3,arg4);
              if (lval5 < 0x40) {
    L002e1164_002e1880:
                fptr8 = (sk_fn)sk_h_003109b4(arg4);
                fptr8(arg3,arg4);
              }
              else {
    L002e1164_002e16d0:
                var68 = 0x8000000000000000;
                fptr8 = (sk_fn)sk_h_00310a74(arg4);
                tmp4 = sk_h_0001df60();
                fptr8(lval18,&var68,0x677880,tmp4,arg3,arg4);
                sk_h_00310ad4(arg4);
                tmp4 = sk_h_00027754();
                fptr8 = (sk_fn)sk_h_0016186c();
                tmp7 = fptr8(lval17,lval18,arg3,tmp4);
                ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
                if ((tmp7 & 1) != 0) goto L002e1164_002e1764;
              }
            }
          }
        }
        fptr8 = (sk_fn)sk_h_00310a44(arg4);
        lval5 = fptr8(arg3,arg4);
        if ((0x40 < lval5) ||
           ((lval5 = fptr8(arg3,arg4), lval5 == 0x40 &&
            (tmp7 = fptr6(arg3,arg4), (tmp7 & 1) == 0)))) {
          tmp7 = fptr6(arg3,arg4);
          lval5 = fptr8(arg3,arg4);
          if ((tmp7 & 1) == 0) {
            if (lval5 < 0x40) goto L002e1164_002e1a24;
          }
          else if (lval5 < 0x41) {
    L002e1164_002e1a24:
            fptr6 = (sk_fn)sk_h_003109b4(arg4);
            fptr6(arg3,arg4);
            goto L002e1164_002e1a44;
          }
          var68 = 0x7fffffffffffffff;
          fptr6 = (sk_fn)sk_h_00310a74(arg4);
          tmp4 = sk_h_0001df60();
          fptr6(lval18,&var68,0x677880,tmp4,arg3,arg4);
          sk_h_00310ad4(arg4);
          tmp4 = sk_h_00027754();
          fptr6 = (sk_fn)sk_h_0016186c();
          tmp7 = fptr6(lval18,lval17,arg3,tmp4);
          ((sk_fn)*(void **)(var70 + 8))(lval18,arg3);
          if ((tmp7 & 1) != 0) {
            *(unsigned int *)(lval18 + -0x10) = 1;
            *(unsigned long *)(lval18 + -0x18) = 0xdd3;
            *(unsigned char *)(lval18 + -0x20) = 2;
            fptr12 = sk_str_005cd650;
            tmp4 = 0x2d;
    L002e1164_002e19d4:
                        /* WARNING: Subroutine does not return */
            sk_h_001afe4c(sk_str_005accd0,0xb,2,fptr12,tmp4,2,sk_str_005cd680,
                         0x14);
          }
        }
    L002e1164_002e1a44:
        fptr6 = (sk_fn)sk_h_003109b4(arg4);
        tmp11 = fptr6(arg3,arg4);
        ((sk_fn)*(void **)(var70 + 8))(lval17,arg3);
        pval16 = var78;
        tmp7 = *var78;
        tmp1 = var78[1];
        if (-1 < (long)tmp11) {
          if (tmp11 < 0x80) {
            tmp11 = sk_h_0035723c(tmp11);
            tmp14 = tmp7 << (tmp11 & 0x3f);
            bval3 = (tmp11 & 0x40) == 0;
            tmp13 = tmp14;
            if (bval3) {
              tmp13 = tmp1 << (tmp11 & 0x3f) | (tmp7 >> 1) >> ((unsigned long)~(unsigned int)tmp11 & 0x3f);
            }
            tmp15 = 0;
            if (bval3) {
              tmp15 = tmp14;
            }
          }
          else {
            tmp13 = 0;
            tmp15 = 0;
          }
          goto L002e1164_002e1ac8;
        }
        if (0xffffffffffffff80 < tmp11) {
          tmp11 = -tmp11;
          tmp15 = tmp1 >> (tmp11 & 0x3f);
          bval3 = (tmp11 & 0x40) == 0;
          tmp13 = 0;
          if (bval3) {
            tmp13 = tmp15;
          }
          if (bval3) {
            tmp15 = (tmp1 << 1) << ((unsigned long)~(unsigned int)tmp11 & 0x3f) | tmp7 >> (tmp11 & 0x3f);
          }
          goto L002e1164_002e1ac8;
        }
      }
    L002e1164_002e1688:
      tmp13 = 0;
      tmp15 = 0;
      pval16 = var78;
    L002e1164_002e1ac8:
      *pval16 = tmp15;
      pval16[1] = tmp13;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1b2c @ 0x002e1b2c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1b2c(undefined1 (*param_1) [16],undefined8 arg2,undefined8 *arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1b2c()
{
    sk_u128_t * arg1;
    unsigned long arg2;
    unsigned long * arg3;
    unsigned long * regx20;
    sk_u128_t buf1;
    {
      buf1 = sk_zext((unsigned long)sk_h_002322fc(arg2,*arg3,arg3[1],*regx20,regx20[1]));
      *arg1 = buf1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1b74 @ 0x002e1b74  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1b74(undefined1 (*param_1) [16]) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1b74()
{
    sk_u128_t * arg1;
    unsigned long * regx20;
    sk_u128_t buf1;
    {
      buf1 = sk_zext((unsigned long)sk_h_00231c18(*regx20,regx20[1]));
      *arg1 = buf1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1ba8 @ 0x002e1ba8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1ba8(long *param_1,ulong *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1ba8()
{
    long * arg1;
    unsigned long * arg2;
    unsigned long tmp1;
    unsigned long tmp2;
    unsigned long tmp3;
    unsigned long tmp4;
    long lval5;
    unsigned long * regx20;
    {
      tmp1 = *arg2;
      tmp3 = arg2[1];
      tmp2 = *regx20;
      tmp4 = regx20[1];
      if (CARRY8(tmp3,~tmp4) || CARRY8(tmp3 + ~tmp4,(unsigned long)(tmp2 <= tmp1))) {
        lval5 = tmp1 - tmp2;
        if (tmp3 != tmp4 + (tmp1 < tmp2) || lval5 < 0) goto L002e1ba8_002e1c04;
      }
      else {
        if (tmp4 != tmp3 + (tmp2 < tmp1) || (long)(tmp2 - tmp1) < 0) {
    L002e1ba8_002e1c04:
                        /* WARNING: Subroutine does not return */
          sk_h_001afe4c(sk_str_005accd0,0xb,2,sk_str_005cfb40,0x24,2,
                       sk_str_005cd680,0x14,2,0x6e4,1);
        }
        lval5 = -(tmp2 - tmp1);
      }
      *arg1 = lval5;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1c9c @ 0x002e1c9c  (est. sk_swift_runtime) */
/* Ghidra: undefined8 FUN_002e1c9c(ulong param_1,undefined8 arg2,undefined8 arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e1c9c()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long var20 [2];
    {
      if (1 < arg1) {
        sk_h_003488bc(1);
        sk_h_00352974();
        sk_h_00349b50();
                        /* WARNING: Subroutine does not return */
        sk_h_001afe4c();
      }
      var20[0] = arg2;
      var20[1] = arg3;
      return var20[arg1];
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1d08 @ 0x002e1d08  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1d08(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1d08()
{
    unsigned long tmp1;
    unsigned long * regx19;
    {
      sk_h_00350258();
      tmp1 = sk_h_001e64ec();
      *regx19 = tmp1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1d30 @ 0x002e1d30  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1d30(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1d30()
{
    {
      sk_h_0034c434();
      sk_h_001e3430();
      sk_h_0035272c();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1d5c @ 0x002e1d5c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1d5c(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1d5c()
{
    {
      sk_h_00359424();
      sk_h_001e695c();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1d74 @ 0x002e1d74  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002e1d74(undefined8 *param_1,undefined8 *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002e1d74()
{
    unsigned long * arg1;
    unsigned long * arg2;
    unsigned long tmp1;
    unsigned long * regx20;
    sk_u128_t buf2;
    {
      tmp1 = sk_slice_002e1c9c(*arg2,*regx20,regx20[1]);
      *arg1 = tmp1;
      buf2.hi = (unsigned long)arg1;
      buf2.lo = (unsigned long)sk_h_0001a1c8;
      return buf2;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1dc0 @ 0x002e1dc0  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1dc0(undefined1 (*param_1) [16],undefined8 *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1dc0()
{
    sk_u128_t * arg1;
    unsigned long * arg2;
    unsigned long tmp1;
    unsigned long tmp2;
    unsigned long * regx20;
    sk_u128_t buf3;
    {
      tmp1 = *regx20;
      tmp2 = regx20[1];
      buf3 = sk_zext((unsigned long)sk_h_001d3b98(*arg2,arg2[1]));
      *arg1 = buf3;
      *(unsigned long *)((unsigned char *)arg1 + 16) = tmp1;
      *(unsigned long *)((unsigned char *)arg1 + 24) = tmp2;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1ee4 @ 0x002e1ee4  (est. sk_swift_runtime) */
/* Ghidra: bool FUN_002e1ee4(undefined1 (*param_1) [16],long *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
bool sk_slice_002e1ee4()
{
    sk_u128_t * arg1;
    long * arg2;
    long lval1;
    long lval2;
    sk_u128_t * regx20;
    sk_u128_t buf3;
    {
      lval1 = *arg2;
      lval2 = arg2[1];
      buf3 = *regx20;
      if (lval1 != 0 || lval2 != 0) {
        buf3 = sk_zext((unsigned long)sk_h_0011db10());
      }
      *arg1 = buf3;
      return lval1 == 0 && lval2 == 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1f28 @ 0x002e1f28  (est. sk_swift_runtime) */
/* Ghidra: bool FUN_002e1f28(undefined1 (*param_1) [16],long *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
bool sk_slice_002e1f28()
{
    sk_u128_t * arg1;
    long * arg2;
    long lval1;
    long lval2;
    sk_u128_t * regx20;
    sk_u128_t buf3;
    {
      lval1 = *arg2;
      lval2 = arg2[1];
      buf3 = *regx20;
      if (lval1 != 0 || lval2 != 0) {
        buf3 = sk_zext((unsigned long)sk_h_0011db18());
      }
      *arg1 = buf3;
      return lval1 == 0 && lval2 == 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1f6c @ 0x002e1f6c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1f6c(undefined1 (*param_1) [16],undefined8 arg2,undefined8 *arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1f6c()
{
    sk_u128_t * arg1;
    unsigned long arg2;
    unsigned long * arg3;
    unsigned long * regx20;
    sk_u128_t buf1;
    {
      buf1 = sk_zext((unsigned long)sk_h_0023b254(arg2,*arg3,arg3[1],*regx20,regx20[1]));
      *arg1 = buf1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e1fa8 @ 0x002e1fa8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e1fa8(undefined1 (*param_1) [16],undefined8 arg2,undefined8 *arg3, undefined8 *param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e1fa8()
{
    sk_u128_t * arg1;
    unsigned long arg2;
    unsigned long * arg3;
    unsigned long * arg4;
    unsigned long * regx20;
    sk_u128_t buf1;
    {
      buf1 = sk_zext((unsigned long)sk_h_002450ec(arg2,*arg3,arg3[1],*arg4,arg4[1],*regx20,regx20[1]));
      *arg1 = buf1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e2058 @ 0x002e2058  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e2058(undefined1 (*param_1) [16],ulong arg2,ulong arg3,undefined8 param_4, long param_5) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e2058()
{
    sk_u128_t * arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
    long arg5;
    unsigned long tmp1;
    long lval2;
    unsigned int tmp3;
    sk_u128_t buf4;
    sk_u128_t buf5;
    sk_u128_t buf6;
    sk_u128_t buf7;
    sk_u128_t buf8;
    sk_u128_t buf9;
    sk_u128_t buf10;
    sk_u128_t buf11;
    sk_u128_t buf12;
    sk_u128_t buf13;
    sk_u128_t buf14;
    sk_u128_t buf15;
    sk_u128_t buf16;
    sk_u128_t buf17;
    unsigned char * pbuf18;
    long lval19;
    long lval20;
    char * fptr21;
    unsigned long tmp22;
    unsigned char tmp23;
    unsigned long tmp24;
    unsigned long tmp25;
    unsigned long tmp26;
    unsigned long tmp27;
    unsigned long * pval28;
    unsigned long tmp29;
    unsigned long tmp30;
    unsigned long tmp31;
    unsigned int tmp32;
    sk_u128_t buf33;
    sk_u128_t buf34;
    sk_u128_t buf35;
    sk_u128_t buf36;
    sk_u128_t buf37;
    sk_u128_t buf38;
    unsigned long tmp39;
    unsigned long var50;
    unsigned long stack48;
    {
      tmp24 = arg3 >> 0x38 & 0xf;
      tmp25 = arg2 & 0xffffffffffff;
      if ((arg3 & 0x2000000000000000) != 0) {
        tmp25 = tmp24;
      }
      if (tmp25 == 0) {
        sk_h_003a25d4(arg3);
        buf33 = ZEXT816(0);
        tmp23 = 1;
        goto L002e2058_002e2520;
      }
      if ((arg3 >> 0x3c & 1) == 0) {
        if ((arg3 >> 0x3d & 1) == 0) {
          if ((arg2 >> 0x3c & 1) == 0) {
            buf38 = sk_zext((unsigned long)sk_h_002a9ba8(arg2,arg3));
          }
          else {
            buf38.hi = arg2 & 0xffffffffffff;
            buf38.lo = (arg3 & 0xfffffffffffffff) + 0x20;
          }
          lval20 = buf38.hi;
          fptr21 = (sk_fn)buf38.lo;
          if (lval20 < 1) {
    L002e2058_002e25a4:
            tmp39 = 0x75e;
            fptr21 = &sk_tab_005be7c0;
            tmp22 = 0;
    L002e2058_002e23e8:
                        /* WARNING: Subroutine does not return */
            sk_h_001afe4c(sk_str_005accd0,0xb,2,fptr21,tmp22,2,
                         sk_str_005cdc10,0x1f,2,tmp39,1);
          }
          if (*fptr21 == '+') {
            buf33 = sk_zext((unsigned long)sk_h_001d9840(1,fptr21));
            lval19 = buf33.lo;
            if ((lval19 < 0) || (arg5 < buf33.hi)) {
    L002e2058_002e23b0:
              tmp39 = 0x7db;
              fptr21 = sk_str_005cfa58;
              tmp22 = 0xd;
              goto L002e2058_002e23e8;
            }
            lval2 = 0;
            if (lval20 != 0) {
              lval2 = lval20 + lval19;
            }
            buf36 = sk_zext((unsigned long)sk_h_001e4cbc(lval2,buf33.hi - lval19));
            if (buf36.hi == 0) {
    L002e2058_002e24fc:
              tmp32 = 1;
              buf33 = ZEXT816(0);
            }
            else {
              if (buf36.lo != 0) {
                tmp25 = 0;
                tmp24 = 0;
                tmp32 = 1;
                while( true ) {
                  pbuf18 = (unsigned char *)buf36.lo;
                  if (buf36.hi == 0) break;
                  tmp3 = *pbuf18 - 0x30;
                  if (9 < tmp3) goto L002e2058_002e24fc;
                  buf8.hi = 0;
                  buf8.lo = tmp24;
                  buf9.hi = 0;
                  buf9.lo = tmp25;
                  tmp30 = SUB168(sk_mul_u128(buf9, sk_zext(10)),8);
                  tmp27 = tmp24 * 10;
                  tmp26 = tmp30 + tmp27;
                  tmp29 = tmp25 * 10;
                  tmp1 = (unsigned long)(unsigned char)tmp3;
                  tmp25 = tmp29 + tmp1;
                  tmp24 = tmp26 + CARRY8(tmp29,tmp1);
                  if (CARRY8(tmp30,tmp27) || SUB168(sk_mul_u128(buf8, sk_zext(10)),8) != 0) goto L002e2058_002e2560;
                  buf33 = ZEXT816(0);
                  if (CARRY8(tmp26,(unsigned long)CARRY8(tmp29,tmp1))) goto L002e2058_002e2500;
                  buf36.hi = buf36.hi + -1;
                  buf36.lo = (unsigned long)(pbuf18 + 1);
                }
                goto L002e2058_002e22e4;
              }
    L002e2058_002e2540:
              tmp32 = 0;
              buf33 = ZEXT816(0);
            }
          }
          else if (*fptr21 == '-') {
            buf33 = sk_zext((unsigned long)sk_h_001d9840(1,fptr21));
            lval19 = buf33.lo;
            if ((lval19 < 0) || (arg5 < buf33.hi)) goto L002e2058_002e23b0;
            lval2 = 0;
            if (lval20 != 0) {
              lval2 = lval20 + lval19;
            }
            buf34 = sk_zext((unsigned long)sk_h_001e4cbc(lval2,buf33.hi - lval19));
            lval20 = buf34.hi;
            if (lval20 == 0) goto L002e2058_002e24fc;
            if (buf34.lo == 0) goto L002e2058_002e2540;
            tmp25 = 0;
            tmp24 = 0;
            tmp32 = 1;
            while (lval20 != 0) {
              pbuf18 = (unsigned char *)buf34.lo;
              tmp3 = *pbuf18 - 0x30;
              if (9 < tmp3) goto L002e2058_002e24fc;
              buf4.hi = 0;
              buf4.lo = tmp24;
              buf5.hi = 0;
              buf5.lo = tmp25;
              tmp29 = SUB168(sk_mul_u128(buf5, sk_zext(10)),8);
              tmp27 = tmp24 * 10;
              lval20 = tmp29 + tmp27;
              tmp26 = tmp25 * 10;
              tmp1 = (unsigned long)(unsigned char)tmp3;
              tmp25 = tmp26 - tmp1;
              tmp24 = lval20 - (unsigned long)(tmp1 > tmp26);
              if (CARRY8(tmp29,tmp27) || SUB168(sk_mul_u128(buf4, sk_zext(10)),8) != 0) goto L002e2058_002e2560;
              buf33 = ZEXT816(0);
              if (lval20 == 0 && !CARRY8(lval20 - 1,(unsigned long)(tmp1 <= tmp26))) goto L002e2058_002e2500;
              lval20 = buf34.hi + -1;
              buf34.hi = lval20;
              buf34.lo = (unsigned long)(pbuf18 + 1);
            }
    L002e2058_002e22e4:
            buf33.hi = tmp24;
            buf33.lo = tmp25;
            tmp32 = 0;
          }
          else {
            tmp25 = 0;
            tmp24 = 0;
            tmp32 = 1;
            do {
              pbuf18 = (unsigned char *)buf38.lo;
              tmp3 = *pbuf18 - 0x30;
              if (9 < tmp3) goto L002e2058_002e24fc;
              buf12.hi = 0;
              buf12.lo = tmp24;
              buf13.hi = 0;
              buf13.lo = tmp25;
              tmp30 = SUB168(sk_mul_u128(buf13, sk_zext(10)),8);
              tmp27 = tmp24 * 10;
              tmp26 = tmp30 + tmp27;
              tmp29 = tmp25 * 10;
              tmp1 = (unsigned long)(unsigned char)tmp3;
              tmp25 = tmp29 + tmp1;
              tmp24 = tmp26 + CARRY8(tmp29,tmp1);
              buf16.hi = tmp24;
              buf16.lo = tmp25;
              if (CARRY8(tmp30,tmp27) || SUB168(sk_mul_u128(buf12, sk_zext(10)),8) != 0) goto L002e2058_002e2560;
              buf33 = ZEXT816(0);
              if (CARRY8(tmp26,(unsigned long)CARRY8(tmp29,tmp1))) goto L002e2058_002e2500;
              lval20 = buf38.hi + -1;
              buf38.hi = lval20;
              buf38.lo = (unsigned long)(pbuf18 + 1);
            } while (lval20 != 0);
            tmp32 = 0;
            buf33 = buf16;
          }
        }
        else {
          var50 = arg2;
          stack48 = arg3 & 0xffffffffffffff;
          if (tmp24 == 0) goto L002e2058_002e25a4;
          tmp32 = (unsigned int)arg2 & 0xff;
          if (tmp32 == 0x2b) {
            buf33 = sk_zext((unsigned long)sk_h_001d9840(1,&var50));
            lval20 = buf33.lo;
            if ((lval20 < 0) || (arg5 < buf33.hi)) goto L002e2058_002e23b0;
            lval19 = 0;
            if (tmp24 != 0) {
              lval19 = tmp24 + lval20;
            }
            buf37 = sk_zext((unsigned long)sk_h_001e4cbc(lval19,buf33.hi - lval20));
            if (buf37.hi == 0) goto L002e2058_002e24fc;
            if (buf37.lo != 0) {
              tmp25 = 0;
              tmp24 = 0;
              tmp32 = 1;
              while( true ) {
                pbuf18 = (unsigned char *)buf37.lo;
                if (buf37.hi == 0) break;
                tmp3 = *pbuf18 - 0x30;
                if (9 < tmp3) goto L002e2058_002e24fc;
                buf10.hi = 0;
                buf10.lo = tmp24;
                buf11.hi = 0;
                buf11.lo = tmp25;
                tmp30 = SUB168(sk_mul_u128(buf11, sk_zext(10)),8);
                tmp27 = tmp24 * 10;
                tmp26 = tmp30 + tmp27;
                tmp29 = tmp25 * 10;
                tmp1 = (unsigned long)(unsigned char)tmp3;
                tmp25 = tmp29 + tmp1;
                tmp24 = tmp26 + CARRY8(tmp29,tmp1);
                if (CARRY8(tmp30,tmp27) || SUB168(sk_mul_u128(buf10, sk_zext(10)),8) != 0) goto L002e2058_002e2568;
                buf33 = ZEXT816(0);
                if (CARRY8(tmp26,(unsigned long)CARRY8(tmp29,tmp1))) goto L002e2058_002e2500;
                buf37.hi = buf37.hi + -1;
                buf37.lo = (unsigned long)(pbuf18 + 1);
              }
              goto L002e2058_002e23a0;
            }
    L002e2058_002e2550:
            tmp32 = 0;
            buf33 = ZEXT816(0);
          }
          else if (tmp32 == 0x2d) {
            buf33 = sk_zext((unsigned long)sk_h_001d9840(1,&var50));
            lval20 = buf33.lo;
            if ((lval20 < 0) || (arg5 < buf33.hi)) goto L002e2058_002e23b0;
            lval19 = 0;
            if (tmp24 != 0) {
              lval19 = tmp24 + lval20;
            }
            buf35 = sk_zext((unsigned long)sk_h_001e4cbc(lval19,buf33.hi - lval20));
            lval20 = buf35.hi;
            if (lval20 == 0) goto L002e2058_002e24fc;
            if (buf35.lo == 0) goto L002e2058_002e2550;
            tmp25 = 0;
            tmp24 = 0;
            tmp32 = 1;
            while (lval20 != 0) {
              pbuf18 = (unsigned char *)buf35.lo;
              tmp3 = *pbuf18 - 0x30;
              if (9 < tmp3) goto L002e2058_002e24fc;
              buf6.hi = 0;
              buf6.lo = tmp24;
              buf7.hi = 0;
              buf7.lo = tmp25;
              tmp29 = SUB168(sk_mul_u128(buf7, sk_zext(10)),8);
              tmp27 = tmp24 * 10;
              lval20 = tmp29 + tmp27;
              tmp26 = tmp25 * 10;
              tmp1 = (unsigned long)(unsigned char)tmp3;
              tmp25 = tmp26 - tmp1;
              tmp24 = lval20 - (unsigned long)(tmp1 > tmp26);
              if (CARRY8(tmp29,tmp27) || SUB168(sk_mul_u128(buf6, sk_zext(10)),8) != 0) goto L002e2058_002e2568;
              buf33 = ZEXT816(0);
              if (lval20 == 0 && !CARRY8(lval20 - 1,(unsigned long)(tmp1 <= tmp26))) goto L002e2058_002e2500;
              lval20 = buf35.hi + -1;
              buf35.hi = lval20;
              buf35.lo = (unsigned long)(pbuf18 + 1);
            }
    L002e2058_002e23a0:
            buf33.hi = tmp24;
            buf33.lo = tmp25;
            tmp32 = 0;
          }
          else {
            tmp25 = 0;
            tmp27 = 0;
            tmp32 = 1;
            pval28 = &var50;
            do {
              tmp3 = (unsigned char)*pval28 - 0x30;
              if (9 < tmp3) goto L002e2058_002e24fc;
              buf14.hi = 0;
              buf14.lo = tmp27;
              buf15.hi = 0;
              buf15.lo = tmp25;
              tmp31 = SUB168(sk_mul_u128(buf15, sk_zext(10)),8);
              tmp1 = tmp27 * 10;
              tmp29 = tmp31 + tmp1;
              tmp30 = tmp25 * 10;
              tmp26 = (unsigned long)(unsigned char)tmp3;
              tmp25 = tmp30 + tmp26;
              tmp27 = tmp29 + CARRY8(tmp30,tmp26);
              buf17.hi = tmp27;
              buf17.lo = tmp25;
              if (CARRY8(tmp31,tmp1) || SUB168(sk_mul_u128(buf14, sk_zext(10)),8) != 0) goto L002e2058_002e2568;
              buf33 = ZEXT816(0);
              if (CARRY8(tmp29,(unsigned long)CARRY8(tmp30,tmp26))) goto L002e2058_002e2500;
              tmp24 = tmp24 - 1;
              pval28 = (unsigned long *)((long)pval28 + 1);
            } while (tmp24 != 0);
            tmp32 = 0;
            buf33 = buf17;
          }
        }
      }
      else {
        tmp32 = 10;
        buf33 = sk_zext((unsigned long)sk_h_0022cde0(arg2,arg3));
      }
    L002e2058_002e2500:
      tmp23 = (unsigned char)tmp32;
      sk_h_003a25d4(arg3);
      if ((tmp32 & 0xff) == 1) {
        tmp23 = 1;
        buf33 = ZEXT816(0);
      }
    L002e2058_002e2520:
      *arg1 = buf33;
      ((unsigned char *)arg1)[16] = tmp23;
      return;
    L002e2058_002e2568:
      tmp32 = 1;
      buf33 = ZEXT816(0);
      goto L002e2058_002e2500;
    L002e2058_002e2560:
      tmp32 = 1;
      buf33 = ZEXT816(0);
      goto L002e2058_002e2500;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e25f8 @ 0x002e25f8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e25f8(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e25f8()
{
    long lval2;
    unsigned long outx1;
    unsigned long outx8;
    sk_fn outx8_00;
    sk_fn outx8_01;
    long outx16;
    long outx16_00;
    long outx16_01;
    unsigned long regx19;
    unsigned long regx20;
    long regx21;
    long regx25;
    unsigned long regx30;
    sk_u128_t buf3;
    sk_u128_t buf4;
    unsigned long ival1;
    {
      int ival1;
      sk_h_0008e518();
      sk_h_00356048();
      sk_h_00353160();
      buf3 = sk_zext((unsigned long)sk_h_00310d68());
      sk_h_003508e4(buf3.lo,buf3.hi,0x672870);
      sk_h_003515b4();
      sk_h_003722e4();
      sk_h_00348e00();
      sk_h_0007c1a4();
      sk_g_dispatch();
      sk_h_0034b05c();
      sk_h_0034a5c8();
      sk_h_0007c1a4();
      sk_g_dispatch();
      sk_h_0034b460();
      sk_h_0034b518();
      ((sk_fn)*(void **)(outx16_01 + 0x10))();
      sk_h_0034c9e8();
      sk_h_000839d8();
      ival1 = *(int *)(regx21 + 0x30);
      buf4 = sk_zext((unsigned long)sk_h_00350630(*(unsigned long *)(outx16_00 + 0x20)));
      outx8_00(buf4.lo,buf4.hi,buf3.lo);
      *(unsigned char *)(regx25 + ival1) = 1;
      sk_h_00359018(0x66abc8);
      lval2 = sk_h_0036a940();
      *(unsigned long *)(lval2 + 0x10) = regx20;
      *(unsigned long *)(lval2 + 0x18) = outx1;
      *(unsigned long *)(lval2 + 0x20) = regx19;
      sk_h_003518d0(outx8);
      sk_slice_002e2a04();
      sk_h_0036b270();
      sk_h_0036b118(lval2);
      sk_h_003504f4(*(unsigned long *)(outx16 + 8));
      outx8_01();
      sk_h_0008e500(regx30);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e278c @ 0x002e278c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e278c(undefined8 param_1,long arg2,code *arg3,undefined8 param_4,long param_5) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e278c()
{
    unsigned long arg1;
    long arg2;
    sk_fn arg3;
    unsigned long arg4;
    long arg5;
    char cval1;
    char * fptr2;
    unsigned long tmp3;
    long lval5;
    long lval6;
    long outx8;
    long outx8_00;
    long outx12;
    long outx13;
    long lval7;
    long lval8;
    sk_fn fptr9;
    long lval10;
    char acStack_90 [8];
    char * var88;
    long var80;
    unsigned long var78;
    sk_fn pcStack_70;
    unsigned long var68;
    unsigned long ival4;
    {
      int ival4;
      var80 = *(long *)(arg5 + -8);
      lval5 = arg5;
      var78 = arg4;
      pcStack_70 = arg3;
      var68 = arg1;
      sk_g_dispatch(*(unsigned long *)(var80 + 0x40));
      var88 = acStack_90 + -(outx8 + 0xfU & 0xfffffffffffffff0);
      lval5 = sk_h_00310d68(0xff,lval5);
      lval6 = sk_h_003722e4(0,lval5,0x672870,0,0);
      sk_g_dispatch(*(unsigned long *)(*(long *)(lval6 + -8) + 0x40));
      lval10 = (long)(acStack_90 + -(outx8 + 0xfU & 0xfffffffffffffff0)) -
               (outx8_00 + 0xfU & 0xfffffffffffffff0);
      sk_g_dispatch();
      lval8 = lval10 - outx13;
      ((sk_fn)*(void **)(outx12 + 0x10))(lval8,arg2,lval6);
      cval1 = *(char *)(lval8 + *(int *)(lval6 + 0x30));
      lval7 = *(long *)(lval5 + -8);
      fptr9 = *(sk_fn *)(lval7 + 0x20);
      fptr9(lval10,lval8,lval5);
      tmp3 = var68;
      if (cval1 == '\x01') {
        *(unsigned char *)(arg2 + *(int *)(lval6 + 0x30)) = 0;
        fptr9(var68,lval10,lval5);
      }
      else {
        ival4 = sk_h_000839f8(lval10,1,arg5);
        lval6 = var80;
        fptr2 = var88;
        if (ival4 == 1) {
          sk_h_000839d8(tmp3,1,1,arg5);
        }
        else {
          ((sk_fn)*(void **)(var80 + 0x20))(var88,lval10,arg5);
          pcStack_70(tmp3,fptr2);
          ((sk_fn)*(void **)(lval6 + 8))(fptr2,arg5);
          ((sk_fn)*(void **)(lval7 + 0x18))(arg2,tmp3,lval5);
        }
      }
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e2a04 @ 0x002e2a04  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e2a04(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e2a04()
{
    unsigned long inregx4;
    long outx8;
    sk_fn outx8_00;
    sk_u128_t buf1;
    {
      sk_h_0034b13c();
      sk_h_0035a5f0();
      sk_h_0007c028();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_00348f38();
      buf1 = sk_zext((unsigned long)sk_h_0035603c());
      outx8_00(buf1.lo,buf1.hi,inregx4);
      sk_h_0035242c();
      sk_h_0034b730();
      sk_slice_002e2aa4();
      sk_h_0036b270();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e2aa4 @ 0x002e2aa4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e2aa4(undefined8 param_1,undefined8 arg2,undefined8 arg3,undefined8 param_4, undefined8 param_5) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e2aa4()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
    unsigned long arg5;
    unsigned long * pval1;
    long lval2;
    long outx16;
    unsigned long regx21;
    long regx23;
    sk_u128_t buf3;
    {
      sk_h_0034ba18();
      buf3 = sk_zext((unsigned long)sk_h_003516cc());
      lval2 = sk_h_00324c34(buf3.lo,buf3.hi,arg5);
      *(unsigned char *)(regx23 + *(int *)(lval2 + 0x28)) = 0;
      sk_h_0034b3e8();
      ((sk_fn)*(void **)(outx16 + 0x20))();
      pval1 = (unsigned long *)(regx23 + *(int *)(lval2 + 0x24));
      *pval1 = regx21;
      pval1[1] = arg3;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e2b84 @ 0x002e2b84  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e2b84(long param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e2b84()
{
    long arg1;
    {
      sk_h_003591d0((long)*(int *)(arg1 + 0x24));
      sk_h_0009461c();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e2bbc @ 0x002e2bbc  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e2bbc(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e2bbc()
{
    unsigned long tmp1;
    unsigned char inregZR;
    unsigned long outx1;
    long outx8;
    sk_fn outx8_00;
    sk_fn outx9;
    long outx16;
    long regx20;
    sk_fn fptr3;
    unsigned long ival2;
    {
      int ival2;
      sk_h_0008e518();
      sk_h_003530e8();
      sk_h_003504e8();
      sk_h_00310d68();
      sk_h_00348d64();
      sk_h_0007c1a4();
      sk_g_dispatch();
      sk_h_003494b4();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_003493ac();
      ival2 = *(int *)(regx20 + 0x28);
      if ((*(unsigned char *)(regx20 + ival2) & 1) != 0) {
        sk_h_0034c3f4();
        sk_h_0008e500();
        sk_h_000839d8();
        return;
      }
      tmp1 = *(unsigned long *)(regx20 + *(int *)(regx20 + 0x24) + 8);
      sk_h_00352d28();
      outx9();
      sk_h_00357400();
      sk_h_00349f3c();
      if ((bool)inregZR) {
        sk_h_0034ded4();
        outx8_00();
        *(char *)(regx20 + ival2) = (char)tmp1;
        sk_h_003524b0();
      }
      else {
        fptr3 = *(sk_fn *)(outx16 + 0x20);
        sk_h_003508c0();
        fptr3();
        sk_h_00351554();
        fptr3();
      }
      sk_h_00350774();
      sk_h_000839d8();
      sk_h_0008e500(outx1);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e2d24 @ 0x002e2d24  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e2d24(undefined8 param_1,undefined8 arg2,long arg3,undefined8 param_4, undefined8 param_5) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e2d24()
{
    unsigned long arg1;
    unsigned long arg2;
    long arg3;
    unsigned long arg4;
    unsigned long arg5;
    long lval1;
    unsigned char tmp2;
    long outx1;
    sk_fn outx8;
    sk_fn outx9;
    long outx10;
    long outx16;
    unsigned long regx25;
    unsigned long regx30;
    sk_u128_t buf80;
    unsigned char buf40 [8];
    unsigned char * var38;
    char var18;
    unsigned char var10;
    unsigned long stack17;
    {
      undefined7 stack17;
      sk_h_0008e518();
      sk_h_00358a44();
      sk_h_0035125c(arg5);
      sk_h_0035050c();
      sk_h_0031b760();
      sk_h_0034a37c();
      sk_h_0007c1a4();
      sk_g_dispatch();
      sk_h_0034b05c();
      sk_h_0035050c();
      sk_h_0031b778();
      sk_h_00348d64();
      sk_h_0007c1a4();
      sk_g_dispatch();
      sk_h_0034b0d4();
      if (outx1 != 0) {
        var38 = buf40;
        sk_g_dispatch();
        sk_h_00310c44();
        sk_h_00358324();
        outx9(&var18,sk_h_00324c4c,buf80,outx10 + 8);
        tmp2 = var18 == '\x01';
        if ((bool)tmp2) {
          sk_h_00200b38(regx25);
          sk_h_00352a64();
          sk_h_00200bd0();
          while( true ) {
            sk_h_00200bf4(&var18);
            sk_h_0035976c();
            if ((bool)tmp2) break;
            lval1 = CONCAT71(stack17,var18);
            tmp2 = lval1 == arg3 - outx1;
            if (arg3 - outx1 <= lval1) {
              sk_h_00350410();
              sk_h_003488bc();
              sk_h_00349644();
              sk_h_00351094();
                        /* WARNING: Subroutine does not return */
              sk_h_001afe4c();
            }
            *(unsigned char *)(outx1 + lval1) = var10;
          }
          sk_h_00350a70(*(unsigned long *)(outx16 + 8));
          outx8();
        }
      }
      sk_h_0008e500(regx30);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e2f18 @ 0x002e2f18  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e2f18(undefined8 param_1,undefined8 arg2,long arg3,long param_4,undefined8 param_5 ) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e2f18()
{
    unsigned long arg1;
    unsigned long arg2;
    long arg3;
    long arg4;
    unsigned long arg5;
    long outx16;
    {
      if (arg3 == 0) {
        sk_h_00019858();
        return;
      }
      sk_h_003509c8(arg5);
      if (*(long *)(outx16 + 0x48) == 0) {
        sk_h_00348074(1);
      }
      else {
        if (arg4 - arg3 != -0x8000000000000000 || *(long *)(outx16 + 0x48) != -1) {
          sk_h_0035053c();
          sk_h_0029468c();
          sk_h_0009461c();
          sk_h_001a26e0();
          return;
        }
        sk_h_0034834c(1);
      }
      sk_h_00351be0();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e347c @ 0x002e347c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e347c(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e347c()
{
    {
      sk_h_00348074(1);
      sk_h_00351be0();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e34a0 @ 0x002e34a0  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e34a0(long param_1,undefined8 arg2,long arg3,long param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e34a0()
{
    long arg1;
    unsigned long arg2;
    long arg3;
    long arg4;
    long lval1;
    sk_fn fptr2;
    long lval3;
    long outx16;
    {
      if (arg1 < 0) {
        sk_h_003488bc(1);
        sk_h_00349644();
      }
      else {
        lval3 = sk_h_00354010();
        if (SCARRY8(lval3,*(long *)(outx16 + 0x40))) {
                        /* WARNING: Does not return */
          fptr2 = ((sk_fn)0);
          fptr2();
        }
        lval1 = 0;
        if (arg3 != 0) {
          lval1 = arg4 - arg3;
        }
        if (lval1 < lval3 + *(long *)(outx16 + 0x40)) {
          sk_h_003488bc(1);
          sk_h_00349644();
        }
        else {
          if (arg3 != 0) {
            sk_h_0022a4a8();
            return;
          }
          sk_h_00348898(1);
          sk_h_00349644();
        }
      }
      sk_h_00351094();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3584 @ 0x002e3584  (est. sk_swift_runtime) */
/* Ghidra: ulong FUN_002e3584(ulong param_1,ulong arg2,long arg3,long param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e3584()
{
    unsigned long arg1;
    unsigned long arg2;
    long arg3;
    long arg4;
    unsigned long tmp1;
    unsigned long outx1;
    unsigned long tmp2;
    sk_u128_t buf3;
    unsigned long var48;
    unsigned long stack40;
    {
      if ((arg2 >> 0x3c & 1) == 0) {
        if ((arg2 >> 0x3d & 1) != 0) {
          tmp1 = arg2 >> 0x38 & 0xf;
          stack40 = arg2 & 0xffffffffffffff;
          var48 = arg1;
          if ((long)tmp1 <= arg4) {
            if (arg3 != 0) {
              sk_h_0022b21c(&var48,tmp1,arg3,sk_str_005cf3f0,0x2f,
                           0x3ed);
              return tmp1;
            }
                        /* WARNING: Subroutine does not return */
            sk_h_001afe4c(sk_str_005accd0,0xb,2,sk_str_005ce1c0,0x21,2
                         ,sk_str_005ce1f0,0x14,2,0x179,1);
          }
          tmp2 = 0x3d1;
    L002e3584_002e3664:
                        /* WARNING: Subroutine does not return */
          sk_h_001afe4c(sk_str_005accd0,0xb,2,sk_str_005d0570,0x30,2,
                       sk_str_005cdc10,0x1f,2,tmp2,1);
        }
        if ((arg1 >> 0x3c & 1) == 0) {
    L002e3584_002e364c:
          buf3 = sk_zext((unsigned long)sk_h_002a9ba8(arg1,arg2));
        }
        else {
          buf3.hi = arg1 & 0xffffffffffff;
          buf3.lo = (arg2 & 0xfffffffffffffff) + 0x20;
        }
        tmp1 = sk_h_0031f4e4(buf3.lo,buf3.hi,arg3,arg4);
      }
      else {
        tmp1 = arg1 & 0xffffffffffff;
        if ((arg2 & 0x2000000000000000) != 0) {
          tmp1 = arg2 >> 0x38 & 0xf;
        }
        if (arg4 == 0) {
          if (tmp1 != 0) {
            tmp2 = 0x3dd;
            goto L002e3584_002e3664;
          }
        }
        else if (tmp1 != 0) {
          sk_h_002b141c(0xf);
          arg1 = outx1;
          goto L002e3584_002e364c;
        }
        tmp1 = 0;
      }
      return tmp1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3704 @ 0x002e3704  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3704(long param_1,long arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3704()
{
    long arg1;
    long arg2;
    {
      if (arg1 == 0) {
        return;
      }
      if (-1 < arg2) {
        return;
      }
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c(sk_str_005accd0,0xb,2,sk_str_005cde70,0x31,2,
                   sk_str_005cde40,0x22,2,0x74,1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3774 @ 0x002e3774  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3774(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3774()
{
    long lval1;
    long lval2;
    unsigned long outx8;
    unsigned long outx8_00;
    sk_fn regx19;
    long regx20;
    long lval3;
    unsigned char bufb0 [40];
    unsigned char buf88 [56];
    {
      sk_h_0034fbd4();
      lval1 = sk_h_0036a9a0(0x657418,buf88);
      *(unsigned long *)(lval1 + 0x10) = 8;
      *(unsigned long *)(lval1 + 0x18) = 0;
      *(unsigned long *)(lval1 + 0x20) = 0;
      *(unsigned long *)(lval1 + 0x28) = 0;
      lval2 = sk_h_000a6f68();
      *(unsigned long *)(lval2 + 0x30) = outx8_00;
      lval2 = *(long *)(regx20 + 0x10);
      if (lval2 != 0) {
        lval3 = regx20 + 0x20;
        do {
          sk_h_00344d4c(lval3,bufb0);
          sk_slice_002e3870(bufb0);
          sk_h_000026e8(bufb0);
          lval3 = lval3 + 0x28;
          lval2 = lval2 + -1;
        } while (lval2 != 0);
        lval2 = *(long *)(lval1 + 0x28);
        if (lval2 != 0) goto L002e3774_002e380c;
      }
      lval2 = 0x6ade80;
    L002e3774_002e380c:
      regx19(outx8,lval2);
      sk_h_0036b118(lval1);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3840 @ 0x002e3840  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3840(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3840()
{
    long lval1;
    unsigned long outx8;
    {
      sk_h_00355ce4();
      lval1 = sk_h_0036a940();
      *(unsigned long *)(lval1 + 0x10) = 8;
      *(unsigned long *)(lval1 + 0x18) = 0;
      *(unsigned long *)(lval1 + 0x20) = 0;
      *(unsigned long *)(lval1 + 0x28) = 0;
      lval1 = sk_h_000a6f68();
      *(unsigned long *)(lval1 + 0x30) = outx8;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3844 @ 0x002e3844  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3844(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3844()
{
    long lval1;
    unsigned long outx8;
    {
      sk_h_00355ce4();
      lval1 = sk_h_0036a940();
      *(unsigned long *)(lval1 + 0x10) = 8;
      *(unsigned long *)(lval1 + 0x18) = 0;
      *(unsigned long *)(lval1 + 0x20) = 0;
      *(unsigned long *)(lval1 + 0x28) = 0;
      lval1 = sk_h_000a6f68();
      *(unsigned long *)(lval1 + 0x30) = outx8;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3870 @ 0x002e3870  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3870(undefined8 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3870()
{
    unsigned long arg1;
    unsigned long tmp1;
    unsigned long tmp2;
    sk_fn outx8;
    sk_fn outx9;
    long regx20;
    long lval3;
    long lval4;
    unsigned char bufd0 [40];
    unsigned char bufa8 [40];
    unsigned char buf80 [40];
    unsigned char buf58 [40];
    {
      sk_h_00344d4c(arg1,buf58);
      sk_h_00344d4c(buf58,bufa8);
      sk_h_00002534(0x6562f8,&sk_dat_004e8108);
      sk_h_00002534(0x656300,&sk_dat_004e8110);
      sk_h_003582d8();
      tmp1 = sk_h_00356fcc();
      if ((tmp1 & 1) == 0) {
        sk_h_003582e8();
        sk_h_00344e54(bufd0,0x656308,&sk_dat_004e8118);
      }
      else {
        sk_h_00077070(bufd0,buf80);
        sk_h_0034d9ac(buf80);
        sk_h_00354474();
        sk_h_000b4390(bufa8);
        outx9();
        sk_h_000026e8(buf58);
        sk_h_00077070(bufa8,buf58);
        sk_h_001a15c4();
        lval4 = *(long *)(*(long *)(regx20 + 0x30) + 0x10);
        sk_h_001a168c(lval4);
        lval3 = *(long *)(regx20 + 0x30);
        *(long *)(lval3 + 0x10) = lval4 + 1;
        sk_h_00344d4c(buf58,lval3 + lval4 * 0x28 + 0x20);
        *(long *)(regx20 + 0x30) = lval3;
        sk_h_000026e8(buf80);
      }
      sk_h_0034d9ac(buf58);
      sk_h_0017e880();
      sk_h_0034d150();
      tmp2 = outx8();
      sk_slice_002e3e50();
      sk_h_0036b118(tmp2);
      sk_h_000026e8(buf58);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e39cc @ 0x002e39cc  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e39cc(long param_1,code *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e39cc()
{
    long arg1;
    sk_fn arg2;
    long lval1;
    {
      lval1 = 0x6ade80;
      if (*(long *)(arg1 + 0x28) != 0) {
        lval1 = *(long *)(arg1 + 0x28);
      }
      arg2(lval1);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3a20 @ 0x002e3a20  (est. sk_swift_runtime) */
/* Ghidra: undefined8 FUN_002e3a20(void) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e3a20()
{
    sk_fn fptr1;
    unsigned long tmp2;
    long outx8;
    long outx8_00;
    long outx8_01;
    sk_fn outx8_02;
    long outx9;
    sk_fn outx9_00;
    unsigned long outx10;
    long outx16;
    unsigned long regx19;
    long lval3;
    {
      sk_h_0008409c();
      sk_h_00349b3c();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_003503ec();
      lval3 = outx9 - (outx10 & 0xfffffffffffffff0);
      if (SCARRY8(outx8_00,8)) {
                        /* WARNING: Does not return */
        fptr1 = ((sk_fn)0);
        fptr1();
      }
      tmp2 = sk_h_001a0354(0,(outx8_00 + 7) / 8);
      sk_h_00353a00();
      sk_h_0034b778();
      outx9_00();
      sk_g_dispatch();
      sk_h_00355b48();
      *(unsigned long *)(outx8_01 + -0x10) = regx19;
      *(unsigned long *)(outx8_01 + -8) = tmp2;
      *(unsigned long *)(lval3 + -0x10) = 0x3e42;
      sk_h_00359024();
      sk_h_00354714();
      sk_h_002514f0(lval3,sk_h_00324c80);
      sk_h_003510b8(*(unsigned long *)(outx16 + 8));
      outx8_02();
      return tmp2;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3b64 @ 0x002e3b64  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3b64(undefined8 param_1,long arg2,long arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3b64()
{
    unsigned long arg1;
    long arg2;
    long arg3;
    {
      if (-1 < *(long *)(*(long *)(arg3 + -8) + 0x40)) {
        sk_h_00117cc4(arg2 + 0x20,arg1);
        return;
      }
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c(sk_str_005accd0,0xb,2,sk_str_005ce190,0x23,2,
                   sk_str_005cd680,0x14,2,0xcf8,1);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3be4 @ 0x002e3be4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3be4(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3be4()
{
    unsigned long tmp1;
    long lval2;
    unsigned long regx19;
    {
      tmp1 = sk_h_00351894();
      lval2 = sk_h_001a0354(tmp1,1);
      *(unsigned long *)(lval2 + 0x20) = regx19;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3c18 @ 0x002e3c18  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3c18(uint param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3c18()
{
    unsigned int arg1;
    long lval1;
    {
      lval1 = sk_h_00358318();
      *(unsigned int *)(lval1 + 0x20) = arg1 & 1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3c48 @ 0x002e3c48  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3c48(undefined4 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3c48()
{
    unsigned int arg1;
    long lval1;
    {
      lval1 = sk_h_00358318();
      *(unsigned int *)(lval1 + 0x20) = arg1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3c78 @ 0x002e3c78  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3c78(short param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3c78()
{
    short arg1;
    long lval1;
    {
      lval1 = sk_h_00358318();
      *(int *)(lval1 + 0x20) = (int)arg1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3ca8 @ 0x002e3ca8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3ca8(char param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3ca8()
{
    char arg1;
    long lval1;
    {
      lval1 = sk_h_00358318();
      *(int *)(lval1 + 0x20) = (int)arg1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3cd8 @ 0x002e3cd8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3cd8(uint param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3cd8()
{
    unsigned int arg1;
    long lval1;
    {
      lval1 = sk_h_00358318();
      *(unsigned int *)(lval1 + 0x20) = arg1 & 0xffff;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3d08 @ 0x002e3d08  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3d08(uint param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3d08()
{
    unsigned int arg1;
    long lval1;
    {
      lval1 = sk_h_00358318();
      *(unsigned int *)(lval1 + 0x20) = arg1 & 0xff;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3d78 @ 0x002e3d78  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3d78(undefined8 param_1,undefined8 arg2,code *arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3d78()
{
    unsigned long arg1;
    unsigned long arg2;
    sk_fn arg3;
    unsigned long tmp1;
    unsigned char buf18 [8];
    {
      sk_h_00352ddc();
      tmp1 = arg3();
      sk_slice_002e3a20(buf18,tmp1);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3dbc @ 0x002e3dbc  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3dbc(float param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3dbc()
{
    float arg1;
    long lval1;
    {
      lval1 = sk_h_00358318();
      *(double *)(lval1 + 0x20) = (double)arg1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3df4 @ 0x002e3df4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3df4(undefined8 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3df4()
{
    unsigned long arg1;
    long lval1;
    {
      lval1 = sk_h_00358318();
      *(unsigned long *)(lval1 + 0x20) = arg1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3e50 @ 0x002e3e50  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3e50(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3e50()
{
    unsigned long tmp1;
    sk_fn fptr2;
    bool bval3;
    long lval4;
    long lval5;
    long outx8;
    unsigned long tmp6;
    unsigned long * pval7;
    long regx20;
    long lval8;
    long lval9;
    long lval10;
    sk_u128_t buf11;
    sk_u128_t buf12;
    {
      buf11 = sk_zext((unsigned long)sk_h_00357ca0());
      lval4 = buf11.lo;
      lval9 = *(long *)(lval4 + 0x10);
      tmp1 = *(long *)(regx20 + 0x18) + lval9;
      if (SCARRY8(*(long *)(regx20 + 0x18),lval9)) {
                        /* WARNING: Does not return */
        fptr2 = ((sk_fn)0);
        fptr2();
      }
      lval10 = *(long *)(regx20 + 0x20);
      lval5 = lval4;
      if (lval10 < (long)tmp1) {
        if (lval10 + 0x4000000000000000 < 0) {
                        /* WARNING: Does not return */
          fptr2 = ((sk_fn)0);
          fptr2();
        }
        lval8 = *(long *)(regx20 + 0x28);
        tmp6 = lval10 * 2;
        bval3 = tmp1 <= tmp6;
        if (tmp6 - tmp1 == 0 || (long)tmp6 < (long)tmp1) {
          tmp6 = tmp1;
        }
        *(unsigned long *)(regx20 + 0x20) = tmp6;
        sk_h_0035a504();
        if (!bval3) {
                        /* WARNING: Does not return */
          fptr2 = ((sk_fn)0);
          fptr2();
        }
        buf12 = sk_zext((unsigned long)sk_h_0036a804(outx8 << 3,7));
        lval5 = buf12.lo;
        *(long *)(regx20 + 0x28) = lval5;
        if (lval8 != 0) {
          sk_h_00100efc(lval5,buf12.hi,lval5);
          sk_h_0019cc64();
          if (lval10 + 0xf000000000000000U >> 0x3d < 7) {
                        /* WARNING: Does not return */
            fptr2 = ((sk_fn)0);
            fptr2();
          }
          lval5 = sk_h_00012568(lval8,lval10 << 3,7);
        }
      }
      lval10 = *(long *)(regx20 + 0x28);
      if (lval10 == 0) {
        sk_h_00348898(1);
        sk_h_0034a2f8();
                        /* WARNING: Subroutine does not return */
        sk_h_001afe4c();
      }
      if (lval9 != 0) {
        lval8 = *(long *)(regx20 + 0x18);
        pval7 = (unsigned long *)(lval4 + 0x20);
        do {
          *(unsigned long *)(lval10 + lval8 * 8) = *pval7;
          lval8 = *(long *)(regx20 + 0x18) + 1;
          if (SCARRY8(*(long *)(regx20 + 0x18),1)) {
                        /* WARNING: Does not return */
            fptr2 = ((sk_fn)0);
            fptr2();
          }
          *(long *)(regx20 + 0x18) = lval8;
          lval9 = lval9 + -1;
          pval7 = pval7 + 1;
        } while (lval9 != 0);
      }
      sk_h_00357c44(lval5,buf11.hi);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e3fe4 @ 0x002e3fe4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e3fe4(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e3fe4()
{
    sk_fn fptr1;
    unsigned char inregCY;
    unsigned long tmp2;
    long outx8;
    long regx20;
    {
      if (*(long *)(regx20 + 0x28) != 0) {
        tmp2 = sk_h_0035a504(*(unsigned long *)(regx20 + 0x20));
        if (!(bool)inregCY) {
                        /* WARNING: Does not return */
          fptr1 = ((sk_fn)0);
          fptr1();
        }
        sk_h_00012568(tmp2,outx8 << 3,7);
      }
      sk_h_0036b118(*(unsigned long *)(regx20 + 0x30));
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4028 @ 0x002e4028  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4028(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e4028()
{
    {
      sk_slice_002e3fe4();
      sk_h_00355ce4();
      sk_h_0036b6ac();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e402c @ 0x002e402c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e402c(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e402c()
{
    {
      sk_slice_002e3fe4();
      sk_h_00355ce4();
      sk_h_0036b6ac();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4058 @ 0x002e4058  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4058(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e4058()
{
    long lval1;
    long outx8;
    long outx16;
    long outx16_00;
    long regx24;
    unsigned long regx30;
    {
      sk_h_00357ca0();
      sk_h_0034aa3c();
      sk_h_00358e88();
      sk_h_0034b07c();
      ((sk_fn)*(void **)(outx16 + 0x20))();
      sk_h_0035990c();
      lval1 = sk_h_0031d910();
      sk_h_00354010((long)*(int *)(lval1 + 0x34));
      ((sk_fn)*(void **)(outx16_00 + 0x20))(regx24 + outx8);
      sk_h_00357c44(regx30);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4110 @ 0x002e4110  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4110(undefined8 param_1,long arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e4110()
{
    unsigned long arg1;
    long arg2;
    long outx16;
    {
      sk_h_00349830(arg2,*(unsigned long *)(arg2 + 0x20),*(unsigned long *)(arg2 + 0x10));
      sk_h_00377824();
      sk_h_00350404();
                        /* WARNING: Could not recover jumptable at 0x002e4164. Too many branches */
                        /* WARNING: Treating indirect jump as call */
      ((sk_fn)*(void **)(outx16 + 0x10))(arg1);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e416c @ 0x002e416c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e416c(undefined8 param_1,long arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e416c()
{
    unsigned long arg1;
    long arg2;
    unsigned long tmp1;
    unsigned long outx8;
    long outx16;
    {
      tmp1 = sk_h_00349830(*(unsigned long *)(arg2 + 0x20),arg1,arg2,
                           *(unsigned long *)(arg2 + 0x10));
      sk_h_00377824(tmp1,outx8);
      sk_h_00350404();
                        /* WARNING: Could not recover jumptable at 0x002e41c4. Too many branches */
                        /* WARNING: Treating indirect jump as call */
      ((sk_fn)*(void **)(outx16 + 0x28))();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4290 @ 0x002e4290  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4290(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e4290()
{
    long lval2;
    long outx8;
    long outx16;
    long outx16_00;
    unsigned long regx30;
    unsigned long ival1;
    {
      int ival1;
      sk_h_00351e20();
      sk_h_0034d2b4();
      sk_h_00353fac();
      lval2 = sk_h_0031d928(0);
      *(unsigned char *)(outx8 + *(int *)(lval2 + 0x38)) = 0;
      sk_h_00358c5c();
      sk_h_00350488();
      sk_h_003534ec();
      sk_h_00377824();
      sk_h_00349530();
      ((sk_fn)*(void **)(outx16 + 0x20))(outx8);
      ival1 = *(int *)(lval2 + 0x34);
      sk_h_0034e6ec();
      sk_h_00377824();
      sk_h_00349530();
      ((sk_fn)*(void **)(outx16_00 + 0x20))(outx8 + ival1);
      sk_h_00351d30(regx30);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4358 @ 0x002e4358  (est. sk_swift_runtime) */
/* Ghidra: long FUN_002e4358(void) */
/* Confidence: low (Swift stdlib / object-service region). */
long sk_slice_002e4358()
{
    unsigned long tmp1;
    unsigned long tmp2;
    unsigned long tmp3;
    unsigned long tmp4;
    long lval5;
    long lval6;
    unsigned long * regx20;
    {
      tmp1 = regx20[2];
      tmp3 = regx20[3];
      tmp2 = regx20[4];
      tmp4 = regx20[5];
      lval5 = sk_h_001ee030(*regx20,regx20[1],sk_h_0029e8dc);
      lval6 = sk_h_0029e8dc(tmp2,tmp4,tmp1,tmp3);
      if (lval5 <= lval6) {
        lval6 = lval5;
      }
      return lval6;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e43c8 @ 0x002e43c8  (est. sk_swift_runtime) */
/* Ghidra: long FUN_002e43c8(void) */
/* Confidence: low (Swift stdlib / object-service region). */
long sk_slice_002e43c8()
{
    long lval1;
    long lval2;
    sk_fn outx8;
    sk_fn outx8_00;
    long regx19;
    unsigned long tmp3;
    {
      sk_h_00358144();
      sk_h_00354f34();
      lval1 = outx8(*(unsigned long *)(regx19 + 0x10));
      tmp3 = *(unsigned long *)(regx19 + 0x28);
      sk_h_00354f34(tmp3);
      lval2 = outx8_00(*(unsigned long *)(regx19 + 0x18),tmp3);
      if (lval1 <= lval2) {
        lval2 = lval1;
      }
      return lval2;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4444 @ 0x002e4444  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4444(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e4444()
{
    long lval1;
    unsigned long regx19;
    {
      sk_h_0035310c();
      lval1 = sk_h_000dbe0c();
      *(unsigned long *)(lval1 + 0x10) = regx19;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4584 @ 0x002e4584  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4584(void) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e4584()
{
    {
      sk_h_002b3978();
      sk_slice_002e45d0();
      return 0;
    }

    return 0;
    return 0;}

/*--------------------------------------------------------------------*/
/* FUN_002e45a0 @ 0x002e45a0  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e45a0(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e45a0()
{
    {
      sk_h_0034e73c();
      sk_h_00357c04();
      sk_h_0034ed18();
      sk_h_002b39b4();
      sk_slice_002e45d0();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e45d0 @ 0x002e45d0  (est. sk_swift_runtime) */
/* Ghidra: uint FUN_002e45d0(void) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned int sk_slice_002e45d0()
{
    unsigned long inregx3;
    unsigned int tmp1;
    sk_u128_t buf2;
    unsigned short var32;
    {
      var32 = 0;
      sk_h_002a3e64();
      sk_h_0034eb54();
      buf2 = sk_zext((unsigned long)sk_h_003a25d4());
      sk_h_00350af4(buf2.lo,buf2.hi,&var32,sk_h_003d319c,sk_h_003d319c);
      sk_h_001e9cd0();
      sk_h_00351e60();
      sk_h_003a25d4();
      tmp1 = (unsigned int)var32;
      if ((inregx3 & 1) == 0) {
        tmp1 = 0x10000;
      }
      return tmp1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e466c @ 0x002e466c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e466c(undefined2 *param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e466c()
{
    unsigned short * arg1;
    unsigned int tmp1;
    {
      tmp1 = sk_slice_002e4584();
      *arg1 = (short)tmp1;
      *(char *)(arg1 + 1) = (char)((unsigned int)tmp1 >> 0x10);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e469c @ 0x002e469c  (est. sk_swift_runtime) */
/* Ghidra: ulong FUN_002e469c(undefined8 param_1,undefined8 arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e469c()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long tmp1;
    unsigned long tmp2;
    unsigned int var34;
    {
      var34 = 0;
      tmp1 = sk_h_001e9cd0(arg1,arg2,&var34,sk_h_003d3130,sk_h_003d3130);
      sk_h_003a25d4(arg2);
      tmp2 = (unsigned long)var34;
      if ((tmp1 & 1) == 0) {
        tmp2 = 0x100000000;
      }
      return tmp2;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4720 @ 0x002e4720  (est. sk_swift_runtime) */
/* Ghidra: ulong FUN_002e4720(void) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e4720()
{
    long outx16;
    unsigned long tmp1;
    char var35;
    unsigned int var34;
    {
      sk_h_003504d0();
      var34 = 0;
      sk_h_00350624(&var35,&var34);
      sk_slice_002e47a8();
      tmp1 = (unsigned long)var34;
      sk_h_0034b3e8();
      ((sk_fn)*(void **)(outx16 + 8))();
      if (var35 == '\0') {
        tmp1 = 0x100000000;
      }
      return tmp1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e47a8 @ 0x002e47a8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e47a8(undefined8 param_1,undefined8 arg2,undefined8 arg3,undefined8 param_4, undefined8 param_5) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e47a8()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
    unsigned long arg5;
    sk_fn fptr1;
    sk_u128_t buf60;
    unsigned long var50;
    {
      var50 = arg2;
      fptr1 = (sk_fn)sk_h_00343d78(arg5);
      fptr1(arg1,sk_h_00343da8,buf60,0x672870,arg4,arg5);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4838 @ 0x002e4838  (est. sk_swift_runtime) */
/* Ghidra: ulong FUN_002e4838(void) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e4838()
{
    unsigned long inregx3;
    unsigned long tmp1;
    sk_u128_t buf2;
    unsigned int var34;
    {
      var34 = 0;
      sk_h_002a3e64();
      sk_h_0034eb54();
      buf2 = sk_zext((unsigned long)sk_h_003a25d4());
      sk_h_00350af4(buf2.lo,buf2.hi,&var34,sk_h_003d3130,sk_h_003d3130);
      sk_h_001e9cd0();
      sk_h_00351e60();
      sk_h_003a25d4();
      tmp1 = (unsigned long)var34;
      if ((inregx3 & 1) == 0) {
        tmp1 = 0x100000000;
      }
      return tmp1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e48c8 @ 0x002e48c8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e48c8(undefined4 *param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e48c8()
{
    unsigned int * arg1;
    unsigned int tmp1;
    unsigned char outvar;
    {
      tmp1 = sk_slice_002e469c();
      *arg1 = tmp1;
      *(unsigned char *)(arg1 + 1) = outvar;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e48f8 @ 0x002e48f8  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002e48f8(undefined8 param_1,undefined8 arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002e48f8()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned int tmp1;
    sk_u128_t buf2;
    unsigned long var38;
    {
      var38 = 0;
      tmp1 = sk_h_001e9cd0(arg1,arg2,&var38,sk_h_003d30c4,sk_h_003d30c4);
      sk_h_003a25d4(arg2);
      if ((tmp1 & 1) == 0) {
        var38 = 0;
      }
      buf2.hi = (tmp1 ^ 0xffffffff) & 1;
      buf2.lo = var38;
      buf2.lo = 0;
      return buf2;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4980 @ 0x002e4980  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002e4980(void) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002e4980()
{
    unsigned long tmp1;
    long outx16;
    sk_u128_t buf2;
    unsigned char var39;
    unsigned long var38;
    {
      sk_h_003504d0();
      var38 = 0;
      sk_h_00350624(&var39,&var38);
      sk_slice_002e4a04();
      tmp1 = var38;
      if (var39 == 0) {
        tmp1 = 0;
      }
      sk_h_0034b3e8();
      ((sk_fn)*(void **)(outx16 + 8))();
      buf2.hi = var39 ^ 1;
      buf2.lo = tmp1;
      buf2.lo = 0;
      return buf2;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4a04 @ 0x002e4a04  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4a04(undefined8 param_1,undefined8 arg2,undefined8 arg3,undefined8 param_4, undefined8 param_5) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e4a04()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
    unsigned long arg5;
    sk_fn fptr1;
    sk_u128_t buf60;
    unsigned long var50;
    {
      var50 = arg2;
      fptr1 = (sk_fn)sk_h_00343d78(arg5);
      fptr1(arg1,sk_h_00343d48,buf60,0x672870,arg4,arg5);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4a94 @ 0x002e4a94  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4a94(undefined8 param_1,undefined8 arg2,code *arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e4a94()
{
    unsigned long arg1;
    unsigned long arg2;
    sk_fn arg3;
    bool bval1;
    unsigned char * pbuf2;
    char * fptr3;
    unsigned long regx20;
    {
      pbuf2 = (unsigned char *)sk_h_00359640();
      if ((*pbuf2 < 0x21 && (1L << ((unsigned long)*pbuf2 & 0x3f) & 0x100003e01U) != 0) ||
         (fptr3 = (char *)arg3(), fptr3 == (char *)0x0)) {
        bval1 = false;
      }
      else {
        bval1 = *fptr3 == '\0';
      }
      *(bool *)regx20 = bval1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4b00 @ 0x002e4b00  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002e4b00(void) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002e4b00()
{
    unsigned int inregw3;
    sk_u128_t buf1;
    unsigned long var38;
    {
      var38 = 0;
      sk_h_002a3e64();
      sk_h_0034eb54();
      buf1 = sk_zext((unsigned long)sk_h_003a25d4());
      sk_h_00350af4(buf1.lo,buf1.hi,&var38,sk_h_003d30c4,sk_h_003d30c4);
      sk_h_001e9cd0();
      sk_h_00351e60();
      sk_h_003a25d4();
      if ((inregw3 & 1) == 0) {
        var38 = 0;
      }
      buf1.hi = (inregw3 ^ 0xffffffff) & 1;
      buf1.lo = var38;
      buf1.lo = 0;
      return buf1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4b94 @ 0x002e4b94  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4b94(undefined8 *param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e4b94()
{
    unsigned long * arg1;
    unsigned long tmp1;
    unsigned char outw1;
    {
      tmp1 = sk_slice_002e48f8().lo;
      *arg1 = tmp1;
      *(unsigned char *)(arg1 + 1) = outw1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4bc0 @ 0x002e4bc0  (est. sk_swift_runtime) */
/* Ghidra: long FUN_002e4bc0(undefined8 param_1,long arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
long sk_slice_002e4bc0()
{
    unsigned long arg1;
    long arg2;
    sk_fn fptr1;
    long lval2;
    long regx19;
    sk_u128_t buf3;
    {
      if (arg2 < 0) {
        sk_h_00347fb4();
        sk_h_003523f0();
                        /* WARNING: Subroutine does not return */
        sk_h_001afe4c();
      }
      sk_h_00358154();
      buf3 = sk_zext((unsigned long)sk_slice_002e4c1c());
      lval2 = buf3.lo;
      if (!SBORROW8(buf3.hi,lval2)) {
        if (lval2 != 0) {
          sk_h_00353aec(lval2,regx19 + lval2);
          sk_h_00117d14();
        }
        return buf3.hi - lval2;
      }
                        /* WARNING: Does not return */
      fptr1 = ((sk_fn)0);
      fptr1();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e4c1c @ 0x002e4c1c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e4c1c(float2 param_1,long *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e4c1c()
{
    sk_f16_t arg1;
    long * arg2;
    unsigned char * pbuf1;
    unsigned int tmp2;
    unsigned int tmp3;
    unsigned int tmp4;
    unsigned long tmp5;
    long lval6;
    long outx8;
    long outx8_00;
    unsigned int tmp7;
    unsigned int outw9;
    unsigned int outw9_00;
    unsigned long tmp8;
    unsigned int tmp9;
    unsigned int outw10;
    unsigned int tmp10;
    long lval12;
    unsigned int tmp13;
    unsigned int outw12;
    unsigned long tmp14;
    long lval15;
    long var40;
    unsigned long stack38;
    unsigned long outw11;
    unsigned long outw11_00;
    unsigned long ival11;
    {
      int ival11;
      int outw11;
      int outw11_00;
      tmp8 = arg2[1];
      if (tmp8 < 0x20) {
        sk_h_0034fa9c(0xc0);
        goto L002e4c1c_002e5074;
      }
      lval6 = *arg2;
      tmp3 = (unsigned int)SUB42((float)arg1,0);
      tmp9 = (unsigned int)(float)arg1 >> 10 & 0x1f;
      var40 = lval6;
      stack38 = tmp8;
      if (tmp9 == 0) {
        if ((tmp3 & 0x3ff) == 0) {
          sk_slice_002e52d4(&var40,tmp3 >> 0xf & 1);
          goto L002e4c1c_002e504c;
        }
        tmp7 = (tmp3 & 0x3ff) << 2;
        tmp9 = (tmp3 & 0x3ff) << 2 | 2;
        lval12 = -0xd;
    L002e4c1c_002e4cbc:
        tmp13 = tmp7 - 2 & 0xffff;
      }
      else {
        if (tmp9 == 0x1f) {
          if ((tmp3 & 0x3ff) == 0) {
            sk_slice_002e5094(&var40,tmp3 >> 0xf & 1);
          }
          else {
            sk_slice_002e513c(&var40,tmp3 >> 0xf & 1,0x1ff < (tmp3 & 0x3ff),tmp3 & 0xff);
          }
          goto L002e4c1c_002e504c;
        }
        lval12 = (unsigned long)tmp9 - 0xe;
        tmp7 = (tmp3 & 0x3ff) << 2 | 0x1000;
        tmp9 = (tmp3 & 0x3ff) << 2 | 0x1002;
        if ((tmp3 & 0x3ff) != 0) goto L002e4c1c_002e4cbc;
        tmp13 = 0xfff;
      }
      if ((lval12 == -0xd) && (tmp7 >> 3 < 0x347)) {
        if (tmp7 < 0x44) {
          tmp9 = tmp9 * 40000000;
          tmp13 = tmp13 * 40000000;
          ival11 = tmp7 * 40000000;
          if (tmp7 < 7) {
            tmp5 = 0x38;
    L002e4c1c_002e4e28:
            tmp9 = tmp9 * 10;
            tmp13 = tmp13 * 10;
            ival11 = ival11 * 10;
          }
          else {
            tmp5 = 0x37;
          }
        }
        else {
          ival11 = tmp7 * 400000;
          tmp13 = tmp13 * 400000;
          tmp9 = tmp9 * 400000;
          if (tmp7 < 0x2a0) {
            tmp5 = 0x36;
            goto L002e4c1c_002e4e28;
          }
          tmp5 = 0x35;
        }
        if (tmp9 >> 0x1c == tmp13 >> 0x1c) {
          *(unsigned char *)(lval6 + 1) = (unsigned char)(tmp9 >> 0x1c) | 0x30;
          *(unsigned char *)(lval6 + 2) = 0x2e;
          tmp5 = sk_h_00358564(tmp5);
          tmp9 = outw10 >> 0x1b & 0xf;
          if (tmp9 == outw9 >> 0x1c) {
            lval15 = 3;
            lval6 = outx8;
            do {
              *(unsigned char *)(lval6 + lval15) = (unsigned char)tmp9 | 0x30;
              lval15 = lval15 + 1;
              tmp5 = sk_h_00358564();
              tmp9 = outw12 >> 0x1b & 0xf;
              lval6 = outx8_00;
              ival11 = outw11_00;
            } while (tmp9 == outw9_00 >> 0x1c);
          }
          else {
            lval15 = 3;
            lval6 = outx8;
            ival11 = outw11;
          }
        }
        else {
          lval15 = 1;
        }
        pbuf1 = (unsigned char *)(lval6 + lval15);
        *pbuf1 = (unsigned char)((unsigned int)(ival11 + 0x8000000) >> 0x1c) | 0x30;
        pbuf1[1] = 0x65;
        pbuf1[2] = 0x2d;
        pbuf1[3] = 0x30;
        sk_h_002943ec(tmp5,lval15 + 4);
        lval15 = lval15 + 5;
        lval12 = 1;
      }
      else {
        ival11 = (int)lval12;
        tmp10 = tmp7 << (unsigned long)(ival11 - 0xdU & 0x1f);
        tmp2 = 0;
        if (-3 < lval12) {
          tmp2 = tmp7 >> (unsigned long)(0xdU - ival11 & 0x1f);
        }
        tmp4 = (tmp10 & 0xffff) >> (unsigned long)(ival11 - 0xdU & 0x1f);
        if (lval12 < 0xd) {
          tmp10 = tmp2;
          tmp4 = tmp2 << (unsigned long)(0xdU - ival11 & 0xf);
        }
        tmp2 = tmp10 & 0xffff;
        lval12 = CONCAT44((tmp2 / 10000) * -10000 + (tmp10 & 0xffff),tmp2 / 10000);
        tmp8 = (unsigned long)lval12 * 0x28f6 >> 0x14 & 0x7f0000007f;
        tmp8 = tmp8 | (lval12 + tmp8 * 0xffffffffff9c) * 0x10000;
        tmp14 = tmp8 * 0x67 >> 10 & 0xf000f000f000f;
        *(unsigned long *)(lval6 + 1) =
             (tmp14 | (tmp8 + tmp14 * 0xfffffffffffff6) * 0x100) + 0x3030303030303030;
        if (tmp2 < 10) {
          lval12 = 8;
        }
        else if (tmp2 < 100) {
          lval12 = 7;
        }
        else if ((tmp10 & 0xffff) < 1000) {
          lval12 = 6;
        }
        else {
          lval12 = 4;
          if ((tmp10 >> 4 & 0xfff) < 0x271) {
            lval12 = 5;
          }
        }
        *(unsigned char *)(lval6 + 9) = 0x2e;
        if (tmp7 == (tmp4 & 0xffff)) {
          lval15 = 0xb;
        }
        else {
          tmp2 = ival11 + 0xf;
          tmp10 = (tmp7 - tmp4 & 0xffff) << (unsigned long)(tmp2 & 0x1f);
          tmp7 = tmp9 << (unsigned long)(tmp2 & 0x1f) & 0xfffffff;
          tmp9 = tmp13 << (unsigned long)(tmp2 & 0x1f) & 0xfffffff;
          tmp2 = tmp9 * 5;
          tmp9 = tmp9 * 10;
          tmp13 = tmp7 * 5 >> 0x1b;
          if (tmp13 == tmp2 >> 0x1b) {
            lval15 = 10;
            do {
              tmp10 = tmp10 * 10;
              *(unsigned char *)(lval6 + lval15) = (unsigned char)tmp13 | 0x30;
              lval15 = lval15 + 1;
              tmp7 = tmp7 * 10 & 0xffffffe;
              tmp2 = (tmp9 & 0xffffffe) * 5;
              tmp9 = (tmp9 & 0xffffffe) * 10;
              tmp13 = tmp7 * 5 >> 0x1b;
            } while (tmp13 == tmp2 >> 0x1b);
          }
          else {
            lval15 = 10;
          }
          tmp10 = (tmp10 & 0xfffffff) * 10 + 0x8000000;
          tmp13 = tmp10 >> 0x1c;
          tmp7 = tmp13;
          if (((tmp10 & 0xffffffe) == 0) &&
             ((tmp7 = tmp13 & 0xe, tmp7 < tmp2 >> 0x1b || ((tmp9 != 0 && (tmp7 == tmp2 >> 0x1b)))
              ))) {
            tmp7 = tmp13 | 1;
          }
          sk_h_002943ec(tmp7 | 0x30,lval15);
          lval15 = lval15 + 1;
        }
      }
      if ((int)tmp3 < 0) {
        lval12 = lval12 + -1;
        sk_h_002943ec(0x2d,lval12);
      }
      if (lval12 <= lval15) {
    L002e4c1c_002e504c:
        sk_h_003507e0();
        return 0;
      }
    L002e4c1c_002e5074:
      sk_h_00347d60();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
    return 0;

    return 0;}

/*--------------------------------------------------------------------*/
/* FUN_002e507c @ 0x002e507c  (est. sk_swift_runtime) */
/* Ghidra: uint FUN_002e507c(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned int sk_slice_002e507c()
{
    sk_f16_t arg1;
    {
      return (unsigned int)(float)arg1 >> 10 & 0x1f;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e5094 @ 0x002e5094  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002e5094(undefined8 *param_1,char arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002e5094()
{
    unsigned long * arg1;
    char arg2;
    sk_u128_t buf1;
    unsigned long tmp2;
    unsigned int tmp3;
    {
      if (arg2 == '\0') {
        if ((long)arg1[1] < 4) goto L002e5094_002e50f4;
        tmp3 = 0x666e69;
        tmp2 = 3;
      }
      else {
        if ((long)arg1[1] < 4) {
    L002e5094_002e50f4:
          sk_h_003488bc(1);
          sk_h_0034b9e8();
                        /* WARNING: Subroutine does not return */
          sk_h_00356408();
        }
        tmp3 = 0x666e692d;
        tmp2 = 4;
      }
      *(unsigned int *)*arg1 = tmp3;
      buf1.hi = 0;
      buf1.lo = tmp2;
      return sk_shl_u128(buf1, 0x40);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e5118 @ 0x002e5118  (est. sk_swift_runtime) */
/* Ghidra: uint FUN_002e5118(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned int sk_slice_002e5118()
{
    sk_f16_t arg1;
    {
      return (unsigned int)(float)arg1 & 0x3ff;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e513c @ 0x002e513c  (est. sk_swift_runtime) */
/* Ghidra: undefined8 FUN_002e513c(long *param_1,char arg2,ulong arg3,ulong param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e513c()
{
    long * arg1;
    char arg2;
    unsigned long arg3;
    unsigned long arg4;
    sk_fn fptr1;
    bool bval2;
    unsigned long tmp3;
    long lval4;
    unsigned long tmp5;
    unsigned long tmp6;
    {
      if (arg2 != '\0') {
        sk_h_002943ec(0x2d,0);
      }
      tmp5 = (unsigned long)(arg2 != '\0');
      if ((arg3 & 1) == 0) {
        sk_h_002943ec(0x73,tmp5);
        tmp5 = tmp5 + 1;
      }
      sk_h_002943ec(0x6e,tmp5);
      sk_h_002943ec(0x61,tmp5 + 1);
      sk_h_002943ec(0x6e,tmp5 + 2);
      if (arg4 != 0) {
        sk_h_002943ec(0x28,tmp5 + 3);
        sk_h_002943ec(0x30,tmp5 | 4);
        sk_h_002943ec(0x78,tmp5 + 5);
        tmp6 = tmp5 + 6;
        tmp3 = 0x3c;
        do {
          if ((arg4 >> (tmp3 & 0x3f) & 0xf) != 0) {
            if ((long)tmp3 < 0) goto L002e513c_002e5264;
            goto L002e513c_002e520c;
          }
          bval2 = 3 < tmp3;
          tmp3 = tmp3 - 4;
        } while (bval2 && tmp3 != 0);
        tmp3 = 0;
    L002e513c_002e520c:
        lval4 = -6 - tmp5;
        tmp5 = tmp6;
        do {
          if ((unsigned long)arg1[1] < tmp5 || lval4 + arg1[1] < 1) {
            sk_h_003488bc(1);
            sk_h_0034b9e8();
                        /* WARNING: Subroutine does not return */
            sk_h_00356408();
          }
          *(unsigned char *)(*arg1 + tmp5) = sk_tab_004f1ee8[arg4 >> (tmp3 & 0x3f) & 0xf];
          tmp6 = tmp5 + 1;
          if (SCARRY8(tmp5,1)) {
                        /* WARNING: Does not return */
            fptr1 = ((sk_fn)0);
            fptr1();
          }
          tmp3 = tmp3 - 4;
          tmp5 = tmp5 + 1;
          lval4 = lval4 + -1;
        } while (tmp3 != 0xfffffffffffffffc);
    L002e513c_002e5264:
        sk_h_002943ec(0x29,tmp6);
        if (SCARRY8(tmp6,1)) {
                        /* WARNING: Does not return */
          fptr1 = ((sk_fn)0);
          fptr1();
        }
        if ((long)(tmp6 + 1) < 0) {
          sk_h_00347d60();
                        /* WARNING: Subroutine does not return */
          sk_h_001afe4c();
        }
      }
      return 0;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e52d4 @ 0x002e52d4  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002e52d4(undefined8 *param_1,char arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002e52d4()
{
    unsigned long * arg1;
    char arg2;
    sk_u128_t buf1;
    unsigned long tmp2;
    unsigned int tmp3;
    {
      if (arg2 == '\0') {
        if ((long)arg1[1] < 4) goto L002e52d4_002e5334;
        tmp3 = 0x302e30;
        tmp2 = 3;
      }
      else {
        if ((long)arg1[1] < 4) {
    L002e52d4_002e5334:
          sk_h_003488bc(1);
          sk_h_0034b9e8();
                        /* WARNING: Subroutine does not return */
          sk_h_00356408();
        }
        tmp3 = 0x302e302d;
        tmp2 = 4;
      }
      *(unsigned int *)*arg1 = tmp3;
      buf1.hi = 0;
      buf1.lo = tmp2;
      return sk_shl_u128(buf1, 0x40);
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e5370 @ 0x002e5370  (est. sk_swift_runtime) */
/* Ghidra: long FUN_002e5370(undefined8 param_1,long arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
long sk_slice_002e5370()
{
    unsigned long arg1;
    long arg2;
    sk_fn fptr1;
    long lval2;
    long regx19;
    sk_u128_t buf3;
    {
      if (arg2 < 0) {
        sk_h_00347fb4();
        sk_h_003523f0();
                        /* WARNING: Subroutine does not return */
        sk_h_001afe4c();
      }
      sk_h_00358154();
      buf3 = sk_zext((unsigned long)sk_slice_002e53cc());
      lval2 = buf3.lo;
      if (!SBORROW8(buf3.hi,lval2)) {
        if (lval2 != 0) {
          sk_h_00353aec(lval2,regx19 + lval2);
          sk_h_00117d14();
        }
        return buf3.hi - lval2;
      }
                        /* WARNING: Does not return */
      fptr1 = ((sk_fn)0);
      fptr1();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e53cc @ 0x002e53cc  (est. sk_swift_runtime) */
/* Ghidra: undefined8 FUN_002e53cc(uint param_1,long *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e53cc()
{
    unsigned int arg1;
    long * arg2;
    unsigned int tmp1;
    unsigned char bval2;
    char cval3;
    bool bval4;
    unsigned int tmp5;
    unsigned long tmp6;
    long lval7;
    unsigned long tmp8;
    unsigned long tmp9;
    unsigned long outx8;
    long lval10;
    long outx9;
    long lval11;
    long outx10;
    unsigned int tmp12;
    unsigned int outw11;
    unsigned int tmp13;
    unsigned long tmp14;
    long lval15;
    unsigned long outx12;
    unsigned long outx13;
    unsigned long tmp17;
    unsigned long outx14;
    unsigned long tmp18;
    unsigned long tmp19;
    unsigned long outx15;
    unsigned long tmp20;
    long var20;
    unsigned long stack18;
    unsigned long ival16;
    {
      int ival16;
      tmp8 = arg2[1];
      if (tmp8 < 0x20) {
        sk_h_0034fa9c(0x1e5);
        tmp9 = outx8;
        lval10 = outx9;
        lval11 = outx10;
        tmp14 = outx12;
        tmp19 = outx13;
        tmp8 = outx14;
        tmp17 = outx15;
        tmp12 = outw11;
    L002e53cc_002e5798:
        tmp18 = tmp8 << (tmp17 & 0x3f);
    L002e53cc_002e57a4:
        tmp8 = 0;
        if (tmp19 < 0x4b) {
          tmp8 = tmp18;
        }
    L002e53cc_002e55e8:
        tmp18 = tmp14;
        if (tmp14 >> 0x35 == 0) goto L002e53cc_002e5600;
      }
      else {
        lval11 = *arg2;
        tmp9 = (unsigned long)arg1;
        tmp13 = arg1 >> 0x17 & 0xff;
        var20 = lval11;
        stack18 = tmp8;
        if (tmp13 == 0) {
          if ((arg1 & 0x7fffff) == 0) {
            sk_slice_002e52d4(&var20,arg1 >> 0x1f);
            return 0;
          }
          tmp13 = (arg1 & 0x7fffff) << 8;
          lval10 = -0x7d;
          tmp12 = 1;
        }
        else {
          if (tmp13 == 0xff) {
            if ((arg1 & 0x7fffff) == 0) {
              sk_slice_002e5094(&var20,arg1 >> 0x1f);
            }
            else {
              sk_slice_002e513c(&var20,arg1 >> 0x1f,(arg1 & 0x7fffff) >> 0x16,arg1 & 0x1fffff);
            }
            return 0;
          }
          lval10 = (unsigned long)tmp13 - 0x7e;
          tmp13 = arg1 << 8 | 0x80000000;
          tmp12 = arg1 & 0x7fffff;
        }
        ival16 = -0x40;
        if (tmp12 != 0) {
          ival16 = -0x80;
        }
        lval7 = (long)(int)lval10 * 0x1344135 >> 0x1a;
        if (lval7 < 1) {
          tmp18 = *(unsigned long *)(&sk_tab_004f1b70 + lval7 * -0x10);
          tmp8 = tmp18;
          if (lval7 < -0x1b) {
            tmp8 = tmp18 + 1;
          }
        }
        else {
          tmp18 = *(unsigned long *)(&sk_tab_004f1fc0 + (0x28 - lval7) * 8);
          tmp8 = tmp18 + 1;
        }
        tmp1 = tmp13 + 0x80;
        tmp13 = tmp13 + ival16;
        lval7 = lval10 + ((long)(int)lval7 * -0x35269e1 >> 0x18);
        tmp19 = lval7 + 1;
        if ((arg1 & 1) == 0) {
          tmp5 = 0xbU - (int)tmp19 & 0x3f;
          if (lval7 - 0x4bU < 0xffffffffffffff7f) {
            tmp14 = 0;
          }
          else {
            tmp8 = ~(-1L << tmp5) + (tmp8 >> 0x20) * (unsigned long)tmp1 +
                    ((tmp8 & 0xffffffff) * (unsigned long)tmp1 + 0xffffffff >> 0x20);
            tmp14 = 0;
            if (tmp19 < 0x4b) {
              tmp14 = tmp8 << (lval7 - 10U & 0x3f);
            }
            tmp8 = tmp8 >> tmp5;
            if ((long)tmp19 < -0x34) {
              tmp8 = 0;
            }
            if ((long)tmp19 < 0xc) {
              tmp14 = tmp8;
            }
          }
          if (0xffffffffffffff7e < lval7 - 0x4bU) {
            tmp8 = ((tmp18 & 0xffffffff) * (unsigned long)tmp13 >> 0x20) + (tmp18 >> 0x20) * (unsigned long)tmp13;
            if ((long)tmp19 < 0xc) {
              tmp8 = tmp8 >> tmp5;
              goto L002e53cc_002e55e0;
            }
            tmp18 = tmp8 << (lval7 - 10U & 0x3f);
            goto L002e53cc_002e57a4;
          }
          tmp8 = 0;
          goto L002e53cc_002e55e8;
        }
        if (0xffffffffffffff7e < lval7 - 0x4bU) {
          tmp18 = ((tmp18 & 0xffffffff) * (unsigned long)tmp1 >> 0x20) + (tmp18 >> 0x20) * (unsigned long)tmp1;
          tmp17 = lval7 - 10;
          tmp20 = 0xb - tmp19;
          tmp14 = 0;
          if (tmp19 < 0x4b) {
            tmp14 = tmp18 << (tmp17 & 0x3f);
          }
          tmp18 = tmp18 >> (tmp20 & 0x3f);
          if ((long)tmp19 < -0x34) {
            tmp18 = 0;
          }
          if ((long)tmp19 < 0xc) {
            tmp14 = tmp18;
          }
          tmp8 = ~(-1L << (tmp20 & 0x3f)) + (tmp8 >> 0x20) * (unsigned long)tmp13 +
                  ((tmp8 & 0xffffffff) * (unsigned long)tmp13 + 0xffffffff >> 0x20);
          if (0xb < (long)tmp19) goto L002e53cc_002e5798;
          tmp8 = tmp8 >> (tmp20 & 0x3f);
    L002e53cc_002e55e0:
          if ((long)tmp19 < -0x34) {
            tmp8 = 0;
          }
          goto L002e53cc_002e55e8;
        }
        tmp8 = 0;
        tmp18 = 0;
    L002e53cc_002e5600:
        do {
          tmp8 = tmp8 * 10;
          tmp14 = tmp18 * 10;
          bval4 = tmp18 < 0x3333333333334;
          tmp18 = tmp14;
        } while (bval4);
      }
      tmp8 = tmp14 - tmp8;
      tmp18 = tmp14 & 0x1fffffffffffff;
      *(char *)(lval11 + 7) = (char)(unsigned int)(tmp14 >> 0x35) + '0';
      tmp19 = tmp8 * 10;
      tmp17 = tmp18 * 10;
      tmp14 = tmp17 & 0x1ffffffffffffe;
      lval7 = 8;
      if (tmp19 < tmp14) {
        do {
          tmp19 = tmp8 * 1000;
          tmp8 = tmp8 * 100;
          *(unsigned short *)(lval11 + lval7) = sk_tab_004f1ef8[tmp18 * 100 >> 0x35];
          lval7 = lval7 + 2;
          tmp18 = tmp18 * 100 & 0x1ffffffffffffc;
          tmp17 = tmp18 * 10;
          tmp14 = tmp17 & 0x1ffffffffffff8;
        } while (tmp19 < tmp14);
        if (tmp18 <= tmp8) goto L002e53cc_002e56cc;
      }
      else if (tmp18 <= tmp8) goto L002e53cc_002e56cc;
      *(unsigned char *)(lval11 + lval7) = (unsigned char)(unsigned int)(tmp17 >> 0x35) | 0x30;
      lval7 = lval7 + 1;
      tmp18 = tmp14;
      tmp8 = tmp19;
    L002e53cc_002e56cc:
      if ((tmp18 | 0x20000000000000) < tmp8) {
        if (tmp12 == 0) {
          lval15 = (tmp8 - tmp18) - tmp8 / 3;
        }
        else {
          lval15 = (tmp8 >> 1) - tmp18;
        }
        cval3 = *(char *)(lval11 + lval7 + -1);
        bval2 = cval3 - (char)(unsigned int)((unsigned long)(lval15 + 0x10000000000000) >> 0x35);
        if ((lval15 + 0x800000U & 0x1fffffff000000) == 0x10000000000000) {
          bval2 = cval3 - (char)(unsigned int)((unsigned long)lval15 >> 0x35) & 0xfe;
        }
        *(unsigned char *)(lval11 + lval7 + -1) = bval2;
      }
      tmp6 = sk_slice_002e5828(&var20,tmp9 >> 0x1f & 1,7,lval7,
                           0x19 < lval10 || tmp12 != 0 && lval10 == 0x19);
      return tmp6;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e57b0 @ 0x002e57b0  (est. sk_swift_runtime) */
/* Ghidra: uint FUN_002e57b0(uint param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned int sk_slice_002e57b0()
{
    unsigned int arg1;
    {
      return arg1 >> 0x17 & 0xff;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e57e0 @ 0x002e57e0  (est. sk_swift_runtime) */
/* Ghidra: uint FUN_002e57e0(uint param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned int sk_slice_002e57e0()
{
    unsigned int arg1;
    {
      return arg1 & 0x7fffff;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e5804 @ 0x002e5804  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e5804(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e5804()
{
    {
      sk_h_00348074(1);
      sk_h_00351be0();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e5828 @ 0x002e5828  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e5828(undefined8 param_1,undefined8 arg2,long arg3,long param_4,uint param_5, ulong param_6) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e5828()
{
    unsigned long arg1;
    unsigned long arg2;
    long arg3;
    long arg4;
    unsigned int arg5;
    unsigned long arg6;
    sk_fn fptr1;
    bool bval2;
    unsigned int tmp3;
    long lval4;
    unsigned long tmp5;
    long lval6;
    unsigned char * pval7;
    long lval8;
    unsigned char tmp9;
    char regw19;
    long * regx20;
    long regx21;
    long regx23;
    unsigned long regx30;
    sk_u128_t buf10;
    {
      sk_h_00357ca0();
      sk_h_003543a0();
      sk_h_003504d0();
      if (((long)arg6 < -4) || ((arg5 & 1) != 0)) {
        if (1 < arg4 - arg3) {
          lval4 = *regx20;
          tmp9 = *(unsigned char *)(lval4 + regx23);
          *(unsigned char *)(lval4 + regx23) = 0x2e;
          regx23 = regx23 + -1;
          *(unsigned char *)(lval4 + regx23) = tmp9;
        }
        lval4 = *regx20;
        *(unsigned char *)(lval4 + regx21) = 0x65;
        tmp5 = -arg6;
        if (-1 < (long)arg6) {
          tmp5 = arg6;
        }
        tmp9 = 0x2d;
        if (-1 < (long)arg6) {
          tmp9 = 0x2b;
        }
        ((unsigned char *)(lval4 + regx21))[1] = tmp9;
        lval8 = regx21 + 2;
        if (99 < (long)tmp5) {
          tmp3 = (unsigned int)tmp5;
          if (tmp5 < 1000) {
            *(unsigned char *)(lval4 + lval8) = (unsigned char)((tmp3 & 0xffff) / 100) | 0x30;
            lval8 = 3;
          }
          else {
            if (0x270 < tmp5 >> 4) {
              sk_h_003488bc(1);
              sk_h_00352974();
              sk_h_00349b50();
                        /* WARNING: Subroutine does not return */
              sk_h_001afe4c();
            }
            *(unsigned short *)(lval4 + lval8) = sk_tab_004f1ef8[(tmp3 & 0xffff) / 100];
            lval8 = 4;
          }
          lval8 = regx21 + lval8;
          tmp5 = (unsigned long)((tmp3 & 0xffff) % 100);
        }
        sk_h_00294468(sk_tab_004f1ef8[tmp5],lval8);
      }
      else {
        if ((long)arg6 < 0) {
          lval4 = arg6 + regx23;
        }
        else {
          lval8 = arg6 + 1;
          if (arg4 - arg3 <= lval8) {
            sk_h_002943ec(0x2e,arg6 + regx23 + 1);
            goto L002e5828_002e59cc;
          }
          if (lval8 < 0) {
            sk_h_003484e4(1);
            sk_h_003499dc();
                        /* WARNING: Subroutine does not return */
            sk_h_001afe4c();
          }
          lval6 = 0;
          pval7 = (unsigned char *)(*regx20 + regx23);
          while (pval7[-1] = *pval7, lval4 = regx23, lval8 != lval6) {
            pval7 = pval7 + 1;
            bval2 = SCARRY8(lval6,1);
            lval6 = lval6 + 1;
            if (bval2) {
                        /* WARNING: Does not return */
              fptr1 = ((sk_fn)0);
              fptr1();
            }
          }
        }
        lval8 = arg6 + regx23;
        regx23 = lval4 + -1;
        sk_h_002943ec(0x2e,lval8);
      }
    L002e5828_002e59cc:
      if (regw19 != '\0') {
        sk_h_002943ec(0x2d,regx23 + -1);
      }
      buf10 = sk_zext((unsigned long)sk_h_00100efc());
      sk_h_00357c44(buf10.lo,buf10.hi,regx30);
      return 0;
    }

    return 0;}

/*--------------------------------------------------------------------*/
/* FUN_002e5a1c @ 0x002e5a1c  (est. sk_swift_runtime) */
/* Ghidra: long FUN_002e5a1c(undefined8 param_1,long arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
long sk_slice_002e5a1c()
{
    unsigned long arg1;
    long arg2;
    sk_fn fptr1;
    long lval2;
    long regx19;
    sk_u128_t buf3;
    {
      if (arg2 < 0) {
        sk_h_00347fb4();
        sk_h_003523f0();
                        /* WARNING: Subroutine does not return */
        sk_h_001afe4c();
      }
      sk_h_00358154();
      buf3 = sk_zext((unsigned long)sk_slice_002e5a78());
      lval2 = buf3.lo;
      if (!SBORROW8(buf3.hi,lval2)) {
        if (lval2 != 0) {
          sk_h_00353aec(lval2,regx19 + lval2);
          sk_h_00117d14();
        }
        return buf3.hi - lval2;
      }
                        /* WARNING: Does not return */
      fptr1 = ((sk_fn)0);
      fptr1();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e5a78 @ 0x002e5a78  (est. sk_swift_runtime) */
/* Ghidra: undefined8 FUN_002e5a78(double param_1,long *arg2) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e5a78()
{
    double arg1;
    long * arg2;
    unsigned int tmp1;
    unsigned int tmp2;
    sk_u128_t buf3;
    sk_u128_t buf4;
    sk_u128_t buf5;
    sk_u128_t buf6;
    sk_u128_t buf7;
    sk_u128_t buf8;
    sk_u128_t buf9;
    sk_u128_t buf10;
    sk_u128_t buf11;
    sk_u128_t buf12;
    sk_u128_t buf13;
    sk_u128_t buf14;
    sk_u128_t buf15;
    sk_u128_t buf16;
    sk_u128_t buf17;
    sk_u128_t buf18;
    sk_u128_t buf19;
    sk_u128_t buf20;
    sk_u128_t buf21;
    sk_u128_t buf22;
    sk_u128_t buf23;
    sk_u128_t buf24;
    sk_u128_t buf25;
    sk_u128_t buf26;
    sk_u128_t buf27;
    sk_u128_t buf28;
    sk_u128_t buf29;
    sk_fn fptr30;
    bool bval31;
    bool bval32;
    unsigned long tmp33;
    long lval34;
    unsigned long tmp35;
    unsigned long tmp36;
    unsigned long outx8;
    unsigned long outx8_00;
    unsigned long outx8_01;
    unsigned int tmp37;
    unsigned long tmp38;
    long lval39;
    unsigned long outx9;
    unsigned long outx9_00;
    unsigned long outx9_01;
    unsigned long tmp41;
    unsigned long outx11;
    unsigned long outx11_00;
    unsigned long outx11_01;
    unsigned int tmp42;
    long lval43;
    unsigned long tmp44;
    long regx19;
    double regx20;
    unsigned long regx21;
    unsigned long regx22;
    unsigned long regx23;
    unsigned int tmp45;
    unsigned long tmp46;
    unsigned long regx26;
    long regx27;
    double dval47;
    double regd8;
    sk_u128_t buf48;
    sk_u128_t buf49;
    sk_u128_t buf50;
    unsigned long vara8;
    unsigned long vara0;
    double var98;
    unsigned long var90;
    long var80;
    unsigned long stack78;
    unsigned long ival40;
    {
      int ival40;
      tmp35 = arg2[1];
      if (tmp35 < 0x20) {
        buf49 = sk_zext((unsigned long)sk_h_0034fa9c(0x2d8));
    L002e5a78_002e61dc:
        if (regx26 < 0xa0) {
          if (vara8 < 0x40) {
            lval39 = sk_h_00353a54(buf49.lo,buf49.hi);
            regx22 = outx8 | outx9;
            regx23 = lval39 << (outx11 & 0x3f);
          }
          else {
            regx23 = 0;
            regx22 = buf49.lo << (regx26 - 0x60 & 0x3f);
          }
        }
        else {
    L002e5a78_002e5d68:
          sk_h_003599c0();
        }
      }
      else {
        regx27 = *arg2;
        tmp36 = (unsigned long)arg1 >> 0x34 & 0x7ff;
        var80 = regx27;
        stack78 = tmp35;
        if (tmp36 == 0) {
          if (arg1 == 0.0) {
            sk_slice_002e52d4(&var80,(unsigned long)arg1 >> 0x3f);
            return 0;
          }
          tmp35 = ((unsigned long)arg1 & 0xfffffffffffff) << 0xb;
          vara0 = 0xfffffffffffffc03;
        }
        else {
          if (tmp36 == 0x7ff) {
            if (ABS(arg1) == INFINITY) {
              sk_slice_002e5094(&var80,(unsigned long)arg1 >> 0x3f);
            }
            else {
              sk_slice_002e513c(&var80,(unsigned long)arg1 >> 0x3f,(unsigned long)arg1 >> 0x33 & 1,
                           (unsigned long)arg1 & 0x3ffffffffffff);
            }
            return 0;
          }
          vara0 = tmp36 - 0x3fe;
          tmp35 = (long)arg1 << 0xb | 0x8000000000000000;
        }
        var90 = (unsigned long)arg1 & 0xfffffffffffff;
        lval39 = -0x200;
        if (var90 != 0) {
          lval39 = -0x400;
        }
        regx19 = (long)(int)vara0 * 0x1344135 >> 0x1a;
        ival40 = (int)(6 - regx19);
        if (regx19 + 0x31U < 0x38) {
          lval34 = (6 - regx19) * 0x10;
          tmp36 = *(unsigned long *)(&sk_tab_004f1b68 + lval34);
          regx22 = *(unsigned long *)(&sk_tab_004f1b70 + lval34);
          lval34 = ((unsigned long)((long)ival40 * 0x35269e1) >> 0x18) + 1;
          tmp41 = regx22;
          tmp46 = tmp36;
        }
        else {
          tmp37 = ((unsigned int)(0x196 - regx19) & 0xffff) / 0x1c;
          tmp36 = sk_tab_004f1998[(unsigned long)tmp37 * 2];
          regx22 = sk_tab_004f19a0[(unsigned long)tmp37 * 2];
          lval43 = (0x196 - regx19) + (long)(int)tmp37 * -0x1c;
          lval34 = ((long)(ival40 - (int)lval43) * 0x35269e1 >> 0x18) + 1;
          if (lval43 == 0) {
            tmp46 = tmp36 + 1;
            tmp41 = regx22;
            if (tmp36 == 0xffffffffffffffff) {
              tmp41 = regx22 + 1;
            }
          }
          else {
            if ((lval43 < 0) || (tmp46 = lval43 * 2 | 1, 0x6f < (long)tmp46)) {
              sk_h_00348b7c(0x178);
              sk_h_00352974();
              sk_h_0006f768();
              goto L002e5a78_002e5ff0;
            }
            tmp46 = *(unsigned long *)(&sk_tab_004f1b68 + tmp46 * 8);
            tmp44 = tmp46 * regx22;
            buf48.hi = 0;
            buf48.lo = tmp46;
            buf19.hi = 0;
            buf19.lo = regx22;
            tmp38 = sk_mul_u128(buf48, sk_zext(buf19.lo)).lo;
            buf3.hi = 0;
            buf3.lo = tmp46;
            buf20.hi = 0;
            buf20.lo = tmp36;
            tmp41 = sk_mul_u128(buf3, sk_zext(buf20.lo)).lo;
            tmp36 = tmp44 + tmp41;
            regx22 = tmp38;
            if (CARRY8(tmp44,tmp41)) {
              regx22 = tmp38 + 1;
            }
            tmp46 = tmp36 + 2;
            lval34 = lval34 + ((unsigned long)((long)(int)lval43 * 0x35269e1) >> 0x18) + 1;
            tmp41 = CARRY8(tmp44,tmp41) + tmp38 + (unsigned long)(0xfffffffffffffffd < tmp36);
          }
        }
        tmp44 = tmp35 + 0x400;
        tmp35 = tmp35 + lval39;
        regx26 = lval34 + vara0;
        tmp38 = 0x20 - regx26;
        vara8 = regx26 - 0x20;
        regx23 = ~(-1L << (tmp38 & 0x3f));
        regx20 = arg1;
        regx21 = vara0;
        if (((unsigned long)arg1 & 1) == 0) {
          buf4.hi = 0;
          buf4.lo = tmp41;
          buf21.hi = 0;
          buf21.lo = tmp44;
          buf5.hi = 0;
          buf5.lo = tmp46;
          buf22.hi = 0;
          buf22.lo = tmp44;
          lval39 = sk_mul_u128(buf5, sk_zext(buf22.lo)).lo;
          if (tmp46 * tmp44 != 0) {
            lval39 = lval39 + 1;
          }
          buf48 = sk_zext((unsigned long)sk_slice_002e6410(tmp41 * tmp44,sk_mul_u128(buf4, sk_zext(buf21.lo)),lval39,0));
          lval34 = buf48.hi;
          lval39 = buf48.lo + regx23;
          if (CARRY8(buf48.lo,regx23)) {
            lval34 = lval34 + 1;
          }
          regx23 = regx26 - 0xa1;
          if (regx23 < 0xfffffffffffffeff) {
    L002e5a78_002e5ca8:
            sk_h_00356110();
          }
          else if ((long)regx26 < 0x21) {
            if ((long)regx26 < -0x5f) goto L002e5a78_002e5ca8;
            sk_slice_002e6670(lval39,lval34,tmp38);
            sk_h_00350b90();
          }
          else {
            if (0x9f < regx26) goto L002e5a78_002e5ca8;
            if (vara8 < 0x40) {
              lval39 = sk_h_00353a54(lval39,lval34);
              regx21 = outx8_00 | outx9_00;
              regx20 = (double)(lval39 << (outx11_00 & 0x3f));
            }
            else {
              regx20 = 0.0;
              regx21 = lval39 << (regx26 - 0x60 & 0x3f);
            }
          }
          buf8.hi = 0;
          buf8.lo = regx22;
          buf25.hi = 0;
          buf25.lo = tmp35;
          lval39 = sk_mul_u128(buf8, sk_zext(buf25.lo)).lo;
          buf9.hi = 0;
          buf9.lo = tmp36;
          buf26.hi = 0;
          buf26.lo = tmp35;
          tmp36 = sk_mul_u128(buf9, sk_zext(buf26.lo)).lo;
          if (CARRY8(regx22 * tmp35,tmp36)) {
            lval39 = lval39 + 1;
          }
          buf49.hi = lval39;
          buf49.lo = regx22 * tmp35 + tmp36;
        }
        else {
          buf6.hi = 0;
          buf6.lo = regx22;
          buf23.hi = 0;
          buf23.lo = tmp44;
          lval34 = sk_mul_u128(buf6, sk_zext(buf23.lo)).lo;
          buf7.hi = 0;
          buf7.lo = tmp36;
          buf24.hi = 0;
          buf24.lo = tmp44;
          tmp36 = sk_mul_u128(buf7, sk_zext(buf24.lo)).lo;
          lval39 = regx22 * tmp44 + tmp36;
          if (CARRY8(regx22 * tmp44,tmp36)) {
            lval34 = lval34 + 1;
          }
          regx22 = regx26 - 0xa1;
          if (regx22 < 0xfffffffffffffeff) {
    L002e5a78_002e5cd0:
            sk_h_00356110();
          }
          else if ((long)regx26 < 0x21) {
            if ((long)regx26 < -0x5f) goto L002e5a78_002e5cd0;
            sk_slice_002e6670(lval39,lval34,tmp38);
            sk_h_00350b90();
          }
          else {
            lval39 = sk_h_00353a54(lval39,lval34);
            dval47 = (double)(lval39 << (outx11_01 & 0x3f));
            tmp36 = outx8_01 | outx9_01;
            if (0x3f < outx11_01) {
              dval47 = 0.0;
              tmp36 = lval39 << (regx26 - 0x60 & 0x3f);
            }
            regx20 = 0.0;
            if (regx26 < 0xa0) {
              regx20 = dval47;
            }
            regx21 = 0;
            if (regx26 < 0xa0) {
              regx21 = tmp36;
            }
          }
          buf10.hi = 0;
          buf10.lo = tmp41;
          buf27.hi = 0;
          buf27.lo = tmp35;
          buf11.hi = 0;
          buf11.lo = tmp46;
          buf28.hi = 0;
          buf28.lo = tmp35;
          lval39 = sk_mul_u128(buf11, sk_zext(buf28.lo)).lo;
          if (tmp46 * tmp35 != 0) {
            lval39 = lval39 + 1;
          }
          buf48 = sk_zext((unsigned long)sk_slice_002e6410(tmp41 * tmp35,sk_mul_u128(buf10, sk_zext(buf27.lo)),lval39,0));
          buf49 = sk_zext((unsigned long)sk_slice_002e6410(buf48.lo,buf48.hi,regx23,0));
        }
        regd8 = arg1;
        var98 = arg1;
        if (regx26 - 0xa1 < 0xfffffffffffffeff) goto L002e5a78_002e5d68;
        if (0x20 < (long)regx26) goto L002e5a78_002e61dc;
        if ((long)regx26 < -0x5f) goto L002e5a78_002e5d68;
        sk_slice_002e6670(buf49.lo,buf49.hi,tmp38);
        sk_h_00351f28();
      }
      for (; regx21 < 0xf424000000000; regx21 = SUB168(sk_mul_u128(buf13, sk_zext(10)),8) + regx21 * 10)
      {
        bval31 = SBORROW8(regx19,1);
        regx19 = regx19 + -1;
        if (bval31) {
                        /* WARNING: Does not return */
          fptr30 = ((sk_fn)0);
          fptr30();
        }
        buf12.hi = 0;
        buf12.lo = regx23;
        regx23 = regx23 * 10;
        regx22 = SUB168(sk_mul_u128(buf12, sk_zext(10)),8) + regx22 * 10;
        buf13.hi = 0;
        buf13.lo = regx20;
        regx20 = (double)((long)regx20 * 10);
      }
      sk_h_0034cf84();
      buf50 = sk_zext((unsigned long)sk_h_00311cf8());
      tmp35 = buf50.hi;
      dval47 = buf50.lo;
      tmp46 = regx21 >> 0x20;
      tmp36 = regx21 & 0xffffffff;
      bval31 = (unsigned long)dval47 < (unsigned long)regx20;
      if (tmp35 != (regx21 & 0xffffffff)) {
        bval31 = tmp35 < (regx21 & 0xffffffff);
      }
      if (bval31) {
        tmp37 = (unsigned int)(regx21 >> 0x20);
        lval39 = CONCAT44(tmp37 % 10000,tmp37 / 10000);
        tmp46 = (unsigned long)lval39 * 0x28f6 >> 0x14 & 0x7f0000007f;
        tmp46 = tmp46 | (lval39 + tmp46 * 0xffffffffff9c) * 0x10000;
        tmp41 = tmp46 * 0x67 >> 10 & 0xf000f000f000f;
        *(unsigned long *)(regx27 + 5) =
             (tmp41 | (tmp46 + tmp41 * 0xfffffffffffff6) * 0x100) + 0x3030303030303030;
        buf14.hi = 0;
        buf14.lo = tmp35;
        buf15.hi = 0;
        buf15.lo = dval47;
        tmp41 = SUB168(sk_mul_u128(buf15, sk_zext(100000000)),8);
        tmp46 = tmp35 * 100000000 + tmp41;
        if ((SUB168(sk_mul_u128(buf14, sk_zext(100000000)),8) != 0) || (CARRY8(tmp35 * 100000000,tmp41))) {
          sk_h_003488bc(1);
          sk_h_00349e8c();
    L002e5a78_002e5ff0:
          sk_h_00351be0();
                        /* WARNING: Subroutine does not return */
          sk_h_001afe4c();
        }
        buf29.hi = tmp46;
        buf29.lo = (long)dval47 * 100000000;
        buf16.hi = 0;
        buf16.lo = regx20;
        tmp35 = SUB168(sk_mul_u128(buf16, sk_zext(100000000)),8) + tmp36 * 100000000;
        bval31 = (unsigned long)((long)dval47 * 100000000) < (unsigned long)((long)regx20 * 100000000);
        if (tmp46 != (tmp35 & 0xffffffff)) {
          bval31 = tmp46 < (tmp35 & 0xffffffff);
        }
        if (bval31) {
          tmp36 = tmp35 & 0xffffffff;
          tmp37 = (unsigned int)(tmp35 >> 0x20);
          lval39 = CONCAT44(tmp37 % 10000,tmp37 / 10000);
          tmp35 = (unsigned long)lval39 * 0x28f6 >> 0x14 & 0x7f0000007f;
          tmp35 = tmp35 | (lval39 + tmp35 * 0xffffffffff9c) * 0x10000;
          tmp46 = tmp35 * 0x67 >> 10 & 0xf000f000f000f;
          *(unsigned long *)(regx27 + 0xd) =
               (tmp46 | (tmp35 + tmp46 * 0xfffffffffffff6) * 0x100) + 0x3030303030303030;
          lval39 = 0x15;
          regx20 = (double)((long)regx20 * 100000000);
          buf50 = buf29;
        }
        else {
          lval39 = 0xd;
        }
        while( true ) {
          tmp35 = buf50.hi;
          dval47 = buf50.lo;
          bval31 = (unsigned long)dval47 < (unsigned long)regx20;
          if (tmp35 != tmp36) {
            bval31 = tmp35 < tmp36;
          }
          if (!bval31) break;
          buf17.hi = 0;
          buf17.lo = dval47;
          buf50.hi = SUB168(sk_mul_u128(buf17, sk_zext(10)),8) + tmp35 * 10;
          buf50.lo = (long)dval47 * 10;
          buf18.hi = 0;
          buf18.lo = regx20;
          tmp36 = SUB168(sk_mul_u128(buf18, sk_zext(10)),8) + tmp36 * 10;
          *(char *)(regx27 + lval39) = (char)(tmp36 >> 0x20) + '0';
          lval39 = lval39 + 1;
          tmp36 = tmp36 & 0xffffffff;
          regx20 = (double)((long)regx20 * 10);
        }
        tmp35 = (unsigned long)dval47 >> 0x24 | tmp35 << 0x1c;
        tmp36 = (unsigned long)regx20 >> 0x24 | tmp36 << 0x1c;
        if ((tmp36 | 0x1000000000000000) <= tmp35) {
          if (var90 == 0) {
            tmp36 = (tmp35 - tmp36) - tmp35 / 3;
          }
          else {
            tmp36 = (tmp35 >> 1) - tmp36;
          }
          if (SBORROW8(lval39,1)) {
                        /* WARNING: Does not return */
            fptr30 = ((sk_fn)0);
            fptr30();
          }
          tmp37 = (unsigned int)*(unsigned char *)(regx27 + lval39 + -1);
          if ((tmp36 & 0xfffffffffffffff) == 0x800000000000000) {
            tmp37 = tmp37 - (unsigned int)(tmp36 >> 0x3c) & 0xfffffffe;
          }
          else {
            if (0xf7ffffffffffffff < tmp36) {
                        /* WARNING: Does not return */
              fptr30 = ((sk_fn)0);
              fptr30();
            }
            tmp37 = tmp37 - (unsigned int)(tmp36 + 0x800000000000000 >> 0x3c);
          }
          sk_h_002943ec(tmp37);
        }
        lval34 = 6;
        goto L002e5a78_002e616c;
      }
      if (regx23 != 0) {
        regx22 = regx22 + 1;
      }
      dval47 = (double)sk_slice_002e64f0(regd8);
      if (dval47 == 0.0) {
        tmp35 = (regx21 + regx22 * 2) / 3;
      }
      else {
        tmp35 = regx21 + regx22 >> 1;
      }
      tmp37 = (unsigned int)(regx22 >> 0x20);
      if ((int)regx22 != 0) {
        tmp37 = tmp37 + 1;
      }
      bval31 = tmp36 == 0 && regx20 == 0.0;
      lval34 = 8;
      tmp36 = tmp35 * 5 >> 0x1f & 0xffffffff;
      tmp35 = tmp35 >> 0x20;
      while( true ) {
        tmp42 = (unsigned int)tmp35;
        tmp1 = (unsigned int)tmp36 % 10;
        tmp45 = (unsigned int)tmp46;
        tmp2 = tmp45 / 10;
        tmp46 = (unsigned long)tmp2;
        tmp37 = (tmp37 + 9) / 10;
        if (tmp45 < 10 || tmp2 < tmp37) break;
        bval32 = SBORROW8(lval34,1);
        lval34 = lval34 + -1;
        if (bval32) {
                        /* WARNING: Does not return */
          fptr30 = ((sk_fn)0);
          fptr30();
        }
        bval31 = (bool)(bval31 & tmp1 == 0);
        tmp36 = tmp35;
        tmp35 = (unsigned long)(tmp42 / 10);
      }
      if (tmp1 < 6) {
        if (tmp1 == 5) {
          if (!bval31) goto L002e5a78_002e607c;
          tmp42 = tmp42 + 1 & 0xfffffffe;
        }
      }
      else {
    L002e5a78_002e607c:
        tmp42 = tmp42 + 1;
      }
      lval39 = CONCAT44(tmp42 % 10000,tmp42 / 10000);
      tmp35 = (unsigned long)lval39 * 0x28f6 >> 0x14 & 0x7f0000007f;
      tmp35 = tmp35 | (lval39 + tmp35 * 0xffffffffff9c) * 0x10000;
      tmp36 = tmp35 * 0x67 >> 10 & 0xf000f000f000f;
      sk_h_002944e4((tmp36 | (tmp35 + tmp36 * 0xfffffffffffff6) * 0x100) + 0x3030303030303030,5);
      if (SBORROW8(9,lval34)) {
                        /* WARNING: Does not return */
        fptr30 = ((sk_fn)0);
        fptr30();
      }
      lval34 = 0xe - lval34;
      lval39 = 0xd;
    L002e5a78_002e616c:
      tmp33 = sk_slice_002e5828(&var80,(unsigned long)var98 >> 0x3f,lval34,lval39,
                            0x36 < (long)vara0 || var90 != 0 && vara0 == 0x36,regx19);
      return tmp33;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e62a0 @ 0x002e62a0  (est. sk_swift_runtime) */
/* Ghidra: ulong FUN_002e62a0(ulong param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e62a0()
{
    unsigned long arg1;
    {
      return arg1 >> 0x34 & 0x7ff;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e62c4 @ 0x002e62c4  (est. sk_swift_runtime) */
/* Ghidra: ulong FUN_002e62c4(ulong param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e62c4()
{
    unsigned long arg1;
    {
      return arg1 >> 0x3f;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e62d0 @ 0x002e62d0  (est. sk_swift_runtime) */
/* Ghidra: ulong FUN_002e62d0(ulong param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e62d0()
{
    unsigned long arg1;
    {
      return arg1 & 0xfffffffffffff;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e62f0 @ 0x002e62f0  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e62f0(long param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e62f0()
{
    long arg1;
    {
      if (-1 < arg1) {
        return;
      }
      sk_h_0035ac70(sk_str_005d3070);
      sk_h_0035280c();
      sk_h_0006f768();
                        /* WARNING: Subroutine does not return */
      sk_h_0035a844();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6330 @ 0x002e6330  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6330(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6330()
{
    unsigned char inregZR;
    long outx8;
    sk_fn outx8_00;
    sk_fn outx9;
    long outx16;
    sk_fn regx23;
    unsigned long regx30;
    sk_u128_t buf1;
    {
      sk_h_00084220();
      sk_h_00351dc0();
      sk_h_0035098c();
      sk_h_00349b3c();
      sk_g_dispatch(*(unsigned long *)(outx8 + 0x40));
      sk_h_00348f50();
      sk_h_0034d384();
      sk_h_00350548();
      outx9();
      sk_h_00350eec();
      regx23();
      sk_h_0035292c();
      if (!(bool)inregZR) {
        sk_h_003517c0();
        sk_h_000b43d0(*(unsigned long *)(outx16 + 8));
        outx8_00();
        buf1 = sk_zext((unsigned long)sk_h_00350470());
        sk_h_00084234(buf1.lo,buf1.hi,regx30);
        return;
      }
      sk_h_0034a478(sk_str_005d3070);
      sk_h_0035280c();
      sk_h_0006f768();
                        /* WARNING: Subroutine does not return */
      sk_h_0035a844();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6410 @ 0x002e6410  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6410(ulong param_1,ulong arg2,ulong arg3,ulong param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e6410()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
    {
      if ((!CARRY8(arg2,arg4)) && (!CARRY8(arg1,arg3) || arg2 + arg4 != -1)) {
        return 0;
      }
      sk_h_003488bc(1,arg1 + arg3);
      sk_h_00349d58();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }

    return 0;}

/*--------------------------------------------------------------------*/
/* FUN_002e6474 @ 0x002e6474  (est. sk_swift_runtime) */
/* Ghidra: bool FUN_002e6474(ulong param_1,ulong arg2,ulong arg3,ulong param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
bool sk_slice_002e6474()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
    bool bval1;
    {
      bval1 = arg1 < arg3;
      if (arg2 != arg4) {
        bval1 = arg2 < arg4;
      }
      return bval1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e648c @ 0x002e648c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e648c(ulong param_1,ulong arg2,ulong arg3,ulong param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e648c()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
    {
      if (arg1 < arg3) {
        if (arg4 < arg2) {
          return;
        }
      }
      else if (arg4 <= arg2) {
        return;
      }
      sk_h_003488bc(1,arg1 - arg3);
      sk_h_00349d58();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e64f0 @ 0x002e64f0  (est. sk_swift_runtime) */
/* Ghidra: ulong FUN_002e64f0(ulong param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned long sk_slice_002e64f0()
{
    unsigned long arg1;
    unsigned long tmp1;
    sk_fn fptr2;
    long lval3;
    unsigned long tmp4;
    {
      tmp4 = arg1 >> 0x34 & 0x7ff;
      tmp1 = arg1 & 0xfffffffffffff;
      if ((tmp1 == 0) || (tmp4 != 0x7ff)) {
        if ((tmp4 == 0) || (tmp4 == 0x7ff)) {
          if ((tmp1 == 0) || (tmp4 != 0)) {
            arg1 = tmp4 << 0x34;
          }
          else {
            lval3 = sk_h_0022aaac();
            if (SBORROW8(0x34,lval3)) {
                        /* WARNING: Does not return */
              fptr2 = ((sk_fn)0);
              fptr2();
            }
            arg1 = arg1 << (0x34U - lval3 & 0x3f) & 0xfffffffffffff | 0x3ff0000000000000;
          }
        }
        else {
          arg1 = tmp1 | 0x3ff0000000000000;
        }
      }
      return arg1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6580 @ 0x002e6580  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6580(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6580()
{
    {
      sk_h_00348404(1);
      sk_h_00351be0();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e65b8 @ 0x002e65b8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e65b8(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e65b8()
{
    {
      sk_h_00348074(1);
      sk_h_00351be0();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6638 @ 0x002e6638  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6638(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6638()
{
    {
      sk_h_003488bc(1);
      sk_h_00349d58();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6670 @ 0x002e6670  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002e6670(ulong param_1,ulong arg2,ulong arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002e6670()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long tmp1;
    unsigned long tmp2;
    unsigned long tmp3;
    unsigned long tmp4;
    sk_u128_t buf5;
    {
      tmp4 = arg3 & 0x7f;
      tmp2 = arg2;
      if (tmp4 != 0) {
        arg1 = arg2 << (-tmp4 & 0x3f) | arg1 >> (arg3 & 0x3f);
        tmp2 = arg2 >> (arg3 & 0x3f);
      }
      tmp1 = arg2 >> (arg3 & 0x3f);
      tmp3 = 0;
      if (tmp4 < 0x40) {
        tmp1 = arg1;
        tmp3 = tmp2;
      }
      buf5.hi = tmp3;
      buf5.lo = tmp1;
      return buf5;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e66dc @ 0x002e66dc  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e66dc(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e66dc()
{
    {
      sk_h_003488bc(1);
      sk_h_00349e8c();
      sk_h_00351be0();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6728 @ 0x002e6728  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6728(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6728()
{
    {
      sk_slice_002e6750();
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6750 @ 0x002e6750  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6750(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6750()
{
    unsigned long tmp1;
    sk_fn fptr2;
    char cval3;
    char cval4;
    unsigned char tmp5;
    long lval6;
    long lval7;
    long outx1;
    long outx1_00;
    unsigned long outx8;
    unsigned long outx9;
    sk_u128_t buf8;
    unsigned long var28;
    {
      sk_h_0006b2ec();
      sk_h_0034ff18();
      buf8 = sk_zext((unsigned long)sk_slice_002e4c1c());
      lval7 = buf8.hi;
      lval6 = buf8.lo;
      cval3 = SBORROW8(lval7,lval6);
      cval4 = lval7 - lval6 < 0;
      tmp5 = lval7 == lval6;
      if ((bool)cval3) {
                        /* WARNING: Does not return */
        fptr2 = ((sk_fn)0);
        fptr2();
      }
      if (lval7 == lval6) {
        sk_h_0011e71c();
      }
      else {
        sk_h_00356704();
        if ((bool)tmp5 || cval4 != cval3) {
          sk_h_00358768();
          if (outx1 < 0) {
            sk_h_00347da8();
    L002e6750_002e67b0:
            sk_h_003504b8();
                        /* WARNING: Subroutine does not return */
            sk_h_001afe4c();
          }
          sk_h_0034e0b4();
          do {
            sk_h_003496b0();
          } while (!(bool)tmp5);
          tmp5 = outx1_00 == 9;
          if (8 < outx1_00) {
            tmp5 = outx9 == outx1_00 - 9U;
            if (outx9 <= outx1_00 - 9U) {
              sk_h_00348034();
              goto L002e6750_002e67b0;
            }
            sk_h_0034da18();
            do {
              sk_h_0034b918();
            } while (!(bool)tmp5);
          }
          sk_h_0034ec0c();
          tmp1 = 0xe000000000000000;
          if (!(bool)tmp5) {
            tmp1 = outx8;
          }
          sk_h_00354b38(tmp1);
        }
        else {
          sk_h_00354988();
          sk_h_00355c10();
        }
      }
      sk_h_000651bc(var28);
      if ((bool)tmp5) {
        return;
      }
                        /* WARNING: Subroutine does not return */
      sk_h_0011d7e8();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e682c @ 0x002e682c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e682c(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e682c()
{
    sk_fn fptr1;
    unsigned char tmp2;
    sk_fn outx8;
    sk_u128_t buf3;
    unsigned long var48;
    {
      sk_h_0034c034();
      sk_h_0006b2ec();
      sk_h_0034fef4();
      buf3 = sk_zext((unsigned long)sk_slice_002e4c1c());
      tmp2 = buf3.hi == buf3.lo;
      if (SBORROW8(buf3.hi,buf3.lo)) {
                        /* WARNING: Does not return */
        fptr1 = ((sk_fn)0);
        fptr1();
      }
      sk_h_00354dc4();
      sk_h_00324ca0();
      sk_h_0035a690();
      sk_h_0034c5ac();
      outx8();
      sk_h_000651bc(var48);
      if ((bool)tmp2) {
        return;
      }
                        /* WARNING: Subroutine does not return */
      sk_h_0011d7e8();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e68dc @ 0x002e68dc  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e68dc(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e68dc()
{
    {
      sk_h_00353d5c(0x7c00);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e68e4 @ 0x002e68e4  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e68e4(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e68e4()
{
    {
      sk_h_00353d5c(0x7e00);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6914 @ 0x002e6914  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6914(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6914()
{
    {
      sk_h_003488bc(1);
      sk_h_0034987c();
                        /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e694c @ 0x002e694c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e694c(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e694c()
{
    {
      sk_h_00353d5c(sk_h_00007d00);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6954 @ 0x002e6954  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6954(void) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6954()
{
    {
      sk_h_00353d5c(0x7bff);
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6964 @ 0x002e6964  (est. sk_swift_runtime) */
/* Ghidra: undefined1  [16] FUN_002e6964(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_u128_t sk_slice_002e6964()
{
    sk_f16_t arg1;
    unsigned int tmp1;
    unsigned long tmp2;
    unsigned short outh0;
    unsigned short outvar;
    unsigned int outvar_00;
    unsigned long outvar_01;
    sk_u128_t buf3;
    {
      tmp1 = (unsigned int)(float)arg1 >> 10 & 0x1f;
      if (tmp1 == 0) {
        tmp2 = 1;
      }
      else {
        if (tmp1 != 0x1f) {
          return sk_zext((unsigned long)ZEXT216((unsigned short)((sk_f16_t)(SUB42((float)arg1,0) & 0x7c00) * (sk_f16_t)7.17465e-42)));
        }
        tmp2 = 0x7e00;
      }
      sk_h_00353d5c(tmp2);
      buf3.hi = outvar;
      buf3.lo = outh0;
      buf3.hi = outvar_00;
      buf3.hi = outvar_01;
      return buf3;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e69e8 @ 0x002e69e8  (est. sk_swift_runtime) */
/* Ghidra: long FUN_002e69e8(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
long sk_slice_002e69e8()
{
    sk_f16_t arg1;
    unsigned int tmp1;
    sk_fn fptr2;
    long lval3;
    {
      tmp1 = (unsigned int)(float)arg1 >> 10 & 0x1f;
      if (tmp1 == 0x1f) {
        return 0x7fffffffffffffff;
      }
      if (tmp1 != 0) {
        return (unsigned long)tmp1 - 0xf;
      }
      tmp1 = (unsigned int)(float)arg1 & 0x3ff;
      if (tmp1 == 0) {
        return -0x8000000000000000;
      }
      lval3 = sk_h_0022a5cc(tmp1);
      if (!SBORROW8(10,lval3)) {
        if (!SBORROW8(-0xe,10 - lval3)) {
          return -0xe - (10 - lval3);
        }
                        /* WARNING: Does not return */
        fptr2 = ((sk_fn)0);
        fptr2();
      }
                        /* WARNING: Does not return */
      fptr2 = ((sk_fn)0);
      fptr2();
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6a58 @ 0x002e6a58  (est. sk_swift_runtime) */
/* Ghidra: uint FUN_002e6a58(uint param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned int sk_slice_002e6a58()
{
    unsigned int arg1;
    unsigned int tmp1;
    unsigned int tmp2;
    sk_fn fptr3;
    long lval4;
    float fval5;
    {
      fval5 = (float)(sk_f16_t)arg1;
      tmp2 = (unsigned int)fval5 >> 10 & 0x1f;
      tmp1 = (unsigned int)fval5 & 0x3ff;
      if (tmp1 == 0 || tmp2 != 0x1f) {
        if (tmp2 == 0) {
          if (tmp1 != 0) {
            lval4 = sk_h_0022a5cc();
            if (!SBORROW8(10,lval4)) {
              return (int)fval5 << (10U - lval4 & 0xf) & 0x3ffU | 0x3c00;
            }
                        /* WARNING: Does not return */
            fptr3 = ((sk_fn)0);
            fptr3();
          }
        }
        else if (tmp2 != 0x1f) {
          return tmp1 | 0x3c00;
        }
        arg1 = tmp2 << 10;
      }
      return arg1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6af0 @ 0x002e6af0  (est. sk_swift_runtime) */
/* Ghidra: float2 FUN_002e6af0(float2 param_1,char arg2,ulong arg3) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_f16_t sk_slice_002e6af0()
{
    sk_f16_t arg1;
    char arg2;
    unsigned long arg3;
    unsigned int tmp1;
    bool bval2;
    unsigned long tmp3;
    sk_f16_t fval4;
    {
      fval4 = -arg1;
      if (arg2 != '\x01') {
        fval4 = arg1;
      }
      tmp1 = (unsigned int)(float)arg1 >> 10 & 0x1f;
      if ((tmp1 != 0x1f) && ((tmp1 != 0 || (((unsigned int)(float)arg1 & 0x3ff) != 0)))) {
        if ((long)arg3 < -0xe) {
          if (arg3 < 0xffffffffffffffd7) {
            arg3 = 0xffffffffffffffd6;
          }
          tmp3 = arg3;
          do {
            arg3 = tmp3 + 0xe;
            fval4 = fval4 * (sk_f16_t)1.43493e-42;
            bval2 = tmp3 < 0xffffffffffffffe4;
            tmp3 = arg3;
          } while (bval2);
        }
        else if (0xf < (long)arg3) {
          if (0x2c < arg3) {
            arg3 = 0x2d;
          }
          do {
            arg3 = arg3 - 0xf;
            fval4 = fval4 * (sk_f16_t)4.30479e-41;
          } while (0xf < arg3);
        }
        fval4 = fval4 * (sk_f16_t)((short)arg3 * 0x400 + 0x3c00U & 0x7c00);
      }
      return fval4;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6bac @ 0x002e6bac  (est. sk_swift_runtime) */
/* Ghidra: uint FUN_002e6bac(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned int sk_slice_002e6bac()
{
    sk_f16_t arg1;
    float fval1;
    unsigned int tmp2;
    {
      tmp2 = (unsigned int)(unsigned short)(arg1 + FLOAT_UNKNOWN);
      if ((arg1 != (sk_f16_t)4.44828e-41) && (!NAN(arg1) && !NAN((sk_f16_t)4.44828e-41))) {
        fval1 = (float)(arg1 + FLOAT_UNKNOWN);
        tmp2 = (-((unsigned int)fval1 >> 0xf & 1) | 1) + (int)fval1;
      }
      return tmp2;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6be4 @ 0x002e6be4  (est. sk_swift_runtime) */
/* Ghidra: float2 FUN_002e6be4(void) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_f16_t sk_slice_002e6be4()
{
    float fval1;
    {
      fval1 = (float)sk_h_0039a030();
      return (sk_f16_t)fval1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6be8 @ 0x002e6be8  (est. sk_swift_runtime) */
/* Ghidra: float2 FUN_002e6be8(void) */
/* Confidence: low (Swift stdlib / object-service region). */
sk_f16_t sk_slice_002e6be8()
{
    float fval1;
    {
      fval1 = (float)sk_h_0039a030();
      return (sk_f16_t)fval1;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6cc8 @ 0x002e6cc8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6cc8(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6cc8()
{
    sk_f16_t arg1;
    sk_f16_t * regx20;
    float fval1;
    {
      fval1 = (float)sk_h_0010d6b4((float)*regx20,SUB42((float)arg1,0));
      *regx20 = (sk_f16_t)fval1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6ccc @ 0x002e6ccc  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6ccc(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6ccc()
{
    sk_f16_t arg1;
    sk_f16_t * regx20;
    float fval1;
    {
      fval1 = (float)sk_h_0010d6b4((float)*regx20,SUB42((float)arg1,0));
      *regx20 = (sk_f16_t)fval1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6cf8 @ 0x002e6cf8  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6cf8(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6cf8()
{
    sk_f16_t arg1;
    float fval1;
    sk_f16_t * regx20;
    {
      fval1 = (float)sk_h_0010d2a8(SUB42((float)*regx20,0),(float)arg1);
      *regx20 = (sk_f16_t)fval1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6cfc @ 0x002e6cfc  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6cfc(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6cfc()
{
    sk_f16_t arg1;
    float fval1;
    sk_f16_t * regx20;
    {
      fval1 = (float)sk_h_0010d2a8(SUB42((float)*regx20,0),(float)arg1);
      *regx20 = (sk_f16_t)fval1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6d80 @ 0x002e6d80  (est. sk_swift_runtime) */
/* Ghidra: uint FUN_002e6d80(float2 param_1) */
/* Confidence: low (Swift stdlib / object-service region). */
unsigned int sk_slice_002e6d80()
{
    sk_f16_t arg1;
    unsigned int tmp1;
    float fval2;
    {
      fval2 = (float)arg1;
      tmp1 = (unsigned int)fval2 >> 10 & 0x1f;
      if (tmp1 == 0) {
        if (((unsigned int)fval2 & 0x3ff) != 0) {
          return (unsigned int)(unsigned short)((sk_f16_t)(SUB42((float)(arg1 * (sk_f16_t)3.58732e-41),0) & 0xfc00) *
                               (sk_f16_t)7.17465e-42);
        }
      }
      else if (tmp1 == 0x1f) {
        return (unsigned int)(unsigned short)(sk_f16_t)4.52003e-41;
      }
      return (unsigned int)fval2 & 0xfc00;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6e3c @ 0x002e6e3c  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6e3c(undefined2 *param_1,undefined8 arg2,undefined8 *arg3,undefined2 *param_4) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6e3c()
{
    unsigned short * arg1;
    unsigned long arg2;
    unsigned long * arg3;
    unsigned short * arg4;
    unsigned short tmp1;
    {
      tmp1 = sk_h_00224114(arg2,*arg3,*arg4);
      *arg1 = tmp1;
      return;
    }
}

/*--------------------------------------------------------------------*/
/* FUN_002e6e84 @ 0x002e6e84  (est. sk_swift_runtime) */
/* Ghidra: void FUN_002e6e84(undefined8 param_1,undefined8 arg2,undefined8 arg3,undefined8 param_4, undefined8 param_5) */
/* Confidence: low (Swift stdlib / object-service region). */
void sk_slice_002e6e84()
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
    unsigned long arg5;
    {
      sk_h_00223960(arg1,arg4,arg2,arg5,arg3);
      return;
    }
}
