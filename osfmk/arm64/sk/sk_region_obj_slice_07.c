/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 (Apple seL4-derived) microkernel (GL1).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header-matched.
 *
 * This file covers the embedded Swift runtime string/collection region
 * 0x2c6998 - 0x2d07f0 (slice 07).
 *
 * SeL4/cL4 vocabulary and Swift runtime vocabulary (String/Character/Unicode
 * scalar, ValidUTF8Buffer, CollectionOfOne, EmptyCollection, UnsafePointer,
 * dictionary/set, array builder) is used for naming. Confidence is medium
 * unless a Swift runtime string matches (then high) or the function is an
 * opaque object-service dispatch loop (then low).
 */

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
/* Fixed 2-word buffer held in x20 by many Swift small-buffer helpers
 * (ValidUTF8Buffer / scalar-buffer push/pop). Stand-in for the register-held
 * buffer; documented per function. */
static unsigned int sk_swift_fixedbuf[2];


/* 16-byte (two-word) return convention used by many Swift runtime helpers
 * (low 8 bytes returned in x0, high 8 bytes in x1). */
typedef struct { unsigned long lo, hi; } sk_pair_t;

/* Noreturn Swift runtime fatal error: sk_fatal_error(tag0, argCount, args...)
 * e.g. sk_fatal_error(0xb, 2, msg, msgLen, 2, "Swift.Range", 17, 2, code, 1). */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */


/* Data symbols (type descriptors, Swift string literals, function-pointer
 * slots, and 64-bit quads) referenced by this slice. */
extern const unsigned char sk_td_003471a0[];   /* DAT_003471a0 (CollectionOfOne witness) */
extern const unsigned char sk_td_003471a4[];   /* DAT_003471a4 */
extern const unsigned char sk_td_003471a8[];   /* DAT_003471a8 */
extern const unsigned char sk_td_003473a0[];   /* DAT_003473a0 */
extern const char sk_str_005be7c0[];           /* DAT_005be7c0 (generic Swift msg) */
extern const char sk_str_validutf8_005d08c0[]; /* DAT_005d08c0 "Swift.ValidUTF8Buffer" */
extern const char sk_str_index_005cd940[];     /* DAT_005cd940 "Index out of range" */
extern const char sk_str_indexoob_005cdab0[];  /* DAT_005cdab0 "Index out of bounds" */
extern const char sk_str_collection_005cdad0[];/* DAT_005cdad0 "Swift.Collection" */
extern const char sk_str_collectionofone_005d0d40[]; /* DAT_005d0d40 "Swift.CollectionOfOne" */
extern const char sk_str_unsafemutraw_005d3510[];   /* DAT_005d3510 "UnsafeMutableRawPointer.nil" */
extern const char sk_str_unsafeptr_005d34d0[];      /* DAT_005d34d0 "UnsafePointer.nil" */
extern const char sk_str_unsafemutptr_005d3490[];   /* DAT_005d3490 "UnsafeMutablePointer.nil" */
extern const char sk_str_005d3450[];           /* DAT_005d3450 (pointer nil msg) */
extern const char sk_str_005d0d70[];           /* DAT_005d0d70 (pointer nil msg) */
extern const char sk_str_004e7a30[];           /* DAT_004e7a30 (hash key string) */
extern unsigned long sk_q_004baeb0;            /* _DAT_004baeb0 */
extern unsigned long sk_q_004baeb8;            /* uRam_004baeb8 */
extern unsigned long sk_q_004c08a0;            /* _DAT_004c08a0 */
extern unsigned long sk_q_004c08a8;            /* uRam_004c08a8 */
extern const unsigned char sk_td_00611b24[];   /* DAT_00611b24 (object method table) */
extern const unsigned char sk_td_00611b3c[];   /* DAT_00611b3c (object method table) */
extern void (*sk_fp_00658c00)(unsigned long);  /* DAT_00658c00 (indirect-call slot) */

extern sk_pair_t sk_h_00002534();  /* FUN_00002534 */
extern sk_pair_t sk_h_000026e8();  /* FUN_000026e8 */
extern sk_pair_t sk_h_000027e8();  /* FUN_000027e8 */
extern sk_pair_t sk_h_00012568();  /* FUN_00012568 */
extern sk_pair_t sk_h_00019850();  /* FUN_00019850 */
extern sk_pair_t sk_h_00019858();  /* FUN_00019858 */
extern sk_pair_t sk_h_0001a1c8();  /* FUN_0001a1c8 */
extern sk_pair_t sk_h_0001df60();  /* FUN_0001df60 */
extern sk_pair_t sk_h_000262fc();  /* FUN_000262fc */
extern sk_pair_t sk_h_00027614();  /* FUN_00027614 */
extern sk_pair_t sk_h_00027754();  /* FUN_00027754 */
extern sk_pair_t sk_h_00027788();  /* FUN_00027788 */
extern sk_pair_t sk_h_00041138();  /* FUN_00041138 */
extern sk_pair_t sk_h_0006a4f0();  /* FUN_0006a4f0 */
extern sk_pair_t sk_h_0006a668();  /* FUN_0006a668 */
extern sk_pair_t sk_h_0006b6f4();  /* FUN_0006b6f4 */
extern sk_pair_t sk_h_0006e778();  /* FUN_0006e778 */
extern sk_pair_t sk_h_0006f768();  /* FUN_0006f768 */
extern sk_pair_t sk_h_00077070();  /* FUN_00077070 */
extern sk_pair_t sk_h_0007c198();  /* FUN_0007c198 */
extern sk_pair_t sk_h_0007c1a4();  /* FUN_0007c1a4 */
extern sk_pair_t sk_h_0007c1c4();  /* FUN_0007c1c4 */
extern sk_pair_t sk_h_000839d8();  /* FUN_000839d8 */
extern sk_pair_t sk_h_000839f8();  /* FUN_000839f8 */
extern sk_pair_t sk_h_0008409c();  /* FUN_0008409c */
extern sk_pair_t sk_h_0008412c();  /* FUN_0008412c */
extern sk_pair_t sk_h_00084180();  /* FUN_00084180 */
extern sk_pair_t sk_h_00084220();  /* FUN_00084220 */
extern sk_pair_t sk_h_00084234();  /* FUN_00084234 */
extern sk_pair_t sk_h_000856ac();  /* FUN_000856ac */
extern sk_pair_t sk_h_000867ec();  /* FUN_000867ec */
extern sk_pair_t sk_h_0008e388();  /* FUN_0008e388 */
extern sk_pair_t sk_h_0008e500();  /* FUN_0008e500 */
extern sk_pair_t sk_h_0008e518();  /* FUN_0008e518 */
extern sk_pair_t sk_h_0008e5d8();  /* FUN_0008e5d8 */
extern sk_pair_t sk_h_0008f6c0();  /* FUN_0008f6c0 */
extern sk_pair_t sk_h_0009461c();  /* FUN_0009461c */
extern sk_pair_t sk_h_0009e234();  /* FUN_0009e234 */
extern sk_pair_t sk_h_000a68c4();  /* FUN_000a68c4 */
extern sk_pair_t sk_h_000a68f4();  /* FUN_000a68f4 */
extern sk_pair_t sk_h_000a6e14();  /* FUN_000a6e14 */
extern sk_pair_t sk_h_000a6f88();  /* FUN_000a6f88 */
extern sk_pair_t sk_h_000b4390();  /* FUN_000b4390 */
extern sk_pair_t sk_h_000b43d0();  /* FUN_000b43d0 */
extern sk_pair_t sk_h_000b43e8();  /* FUN_000b43e8 */
extern sk_pair_t sk_h_000dbcc8();  /* FUN_000dbcc8 */
extern sk_pair_t sk_h_000dbd0c();  /* FUN_000dbd0c */
extern sk_pair_t sk_h_000dbe70();  /* FUN_000dbe70 */
extern sk_pair_t sk_h_000e15d8();  /* FUN_000e15d8 */
extern sk_pair_t sk_h_000e72b0();  /* FUN_000e72b0 */
extern sk_pair_t sk_h_00100efc();  /* FUN_00100efc */
extern sk_pair_t sk_h_00106e3c();  /* FUN_00106e3c */
extern sk_pair_t sk_h_0011aa70();  /* FUN_0011aa70 */
extern sk_pair_t sk_h_0014ae44();  /* FUN_0014ae44 */
extern sk_pair_t sk_h_0017e880();  /* FUN_0017e880 */
extern sk_pair_t sk_h_0019c9cc();  /* FUN_0019c9cc */
extern sk_pair_t sk_h_0019e578();  /* FUN_0019e578 */
extern sk_pair_t sk_h_0019ea20();  /* FUN_0019ea20 */
extern sk_pair_t sk_h_0019eb70();  /* FUN_0019eb70 */
extern sk_pair_t sk_h_0019f1ec();  /* FUN_0019f1ec */
extern sk_pair_t sk_h_0019fa60();  /* FUN_0019fa60 */
extern sk_pair_t sk_h_0019fd10();  /* FUN_0019fd10 */
extern sk_pair_t sk_h_001a00fc();  /* FUN_001a00fc */
extern sk_pair_t sk_h_001a0194();  /* FUN_001a0194 */
extern sk_pair_t sk_h_001a2128();  /* FUN_001a2128 */
extern sk_pair_t sk_h_001a26e0();  /* FUN_001a26e0 */
extern sk_pair_t sk_h_001a7b08();  /* FUN_001a7b08 */
extern sk_pair_t sk_h_001a7b38();  /* FUN_001a7b38 */
extern sk_pair_t sk_h_001a84f4();  /* FUN_001a84f4 */
extern sk_pair_t sk_h_001a8564();  /* FUN_001a8564 */
extern sk_pair_t sk_h_001a89a8();  /* FUN_001a89a8 */
extern sk_pair_t sk_h_001afe4c();  /* FUN_001afe4c */
extern sk_pair_t sk_h_001bcda8();  /* FUN_001bcda8 */
extern sk_pair_t sk_h_001bd768();  /* FUN_001bd768 */
extern sk_pair_t sk_h_001bd858();  /* FUN_001bd858 */
extern sk_pair_t sk_h_001bdb28();  /* FUN_001bdb28 */
extern sk_pair_t sk_h_001c050c();  /* FUN_001c050c */
extern sk_pair_t sk_h_001d2f94();  /* FUN_001d2f94 */
extern sk_pair_t sk_h_001d30f8();  /* FUN_001d30f8 */
extern sk_pair_t sk_h_001d31b0();  /* FUN_001d31b0 */
extern sk_pair_t sk_h_001d39cc();  /* FUN_001d39cc */
extern sk_pair_t sk_h_001d3fd0();  /* FUN_001d3fd0 */
extern sk_pair_t sk_h_001d80e0();  /* FUN_001d80e0 */
extern sk_pair_t sk_h_001d96e0();  /* FUN_001d96e0 */
extern sk_pair_t sk_h_001d974c();  /* FUN_001d974c */
extern sk_pair_t sk_h_001e088c();  /* FUN_001e088c */
extern sk_pair_t sk_h_001e2460();  /* FUN_001e2460 */
extern sk_pair_t sk_h_001e3730();  /* FUN_001e3730 */
extern sk_pair_t sk_h_001e3a28();  /* FUN_001e3a28 */
extern sk_pair_t sk_h_001e4348();  /* FUN_001e4348 */
extern sk_pair_t sk_h_001e664c();  /* FUN_001e664c */
extern sk_pair_t sk_h_001e6be8();  /* FUN_001e6be8 */
extern sk_pair_t sk_h_001ee140();  /* FUN_001ee140 */
extern sk_pair_t sk_h_001ef804();  /* FUN_001ef804 */
extern sk_pair_t sk_h_001f06bc();  /* FUN_001f06bc */
extern sk_pair_t sk_h_001f4084();  /* FUN_001f4084 */
extern sk_pair_t sk_h_001f98a8();  /* FUN_001f98a8 */
extern sk_pair_t sk_h_002060d4();  /* FUN_002060d4 */
extern sk_pair_t sk_h_002298d4();  /* FUN_002298d4 */
extern sk_pair_t sk_h_00229a3c();  /* FUN_00229a3c */
extern sk_pair_t sk_h_00229ebc();  /* FUN_00229ebc */
extern sk_pair_t sk_h_0023560c();  /* FUN_0023560c */
extern sk_pair_t sk_h_002366a0();  /* FUN_002366a0 */
extern sk_pair_t sk_h_00258c60();  /* FUN_00258c60 */
extern sk_pair_t sk_h_002591b4();  /* FUN_002591b4 */
extern sk_pair_t sk_h_0026a9a8();  /* FUN_0026a9a8 */
extern sk_pair_t sk_h_00270d80();  /* FUN_00270d80 */
extern sk_pair_t sk_h_0027195c();  /* FUN_0027195c */
extern sk_pair_t sk_h_00272820();  /* FUN_00272820 */
extern sk_pair_t sk_h_0027675c();  /* FUN_0027675c */
extern sk_pair_t sk_h_00286e40();  /* FUN_00286e40 */
extern sk_pair_t sk_h_0028c754();  /* FUN_0028c754 */
extern sk_pair_t sk_h_0029207c();  /* FUN_0029207c */
extern sk_pair_t sk_h_0029468c();  /* FUN_0029468c */
extern sk_pair_t sk_h_0029bb80();  /* FUN_0029bb80 */
extern sk_pair_t sk_h_002a3e64();  /* FUN_002a3e64 */
extern sk_pair_t sk_h_002a4c98();  /* FUN_002a4c98 */
extern sk_pair_t sk_h_002a9ba8();  /* FUN_002a9ba8 */
extern sk_pair_t sk_h_002ad78c();  /* FUN_002ad78c */
extern sk_pair_t sk_h_002b4fc4();  /* FUN_002b4fc4 */
extern sk_pair_t sk_h_002bb9b8();  /* FUN_002bb9b8 */
extern sk_pair_t sk_h_002bbb64();  /* FUN_002bbb64 */
extern sk_pair_t sk_h_002bf038();  /* FUN_002bf038 */
extern sk_pair_t sk_h_002c2384();  /* FUN_002c2384 */
extern sk_pair_t sk_h_002c2440();  /* FUN_002c2440 */
extern sk_pair_t sk_h_002c55b4();  /* FUN_002c55b4 */
extern sk_pair_t sk_h_002c6918();  /* FUN_002c6918 */
extern sk_pair_t sk_h_00310a14();  /* FUN_00310a14 */
extern sk_pair_t sk_h_00310a44();  /* FUN_00310a44 */
extern sk_pair_t sk_h_00310cd4();  /* FUN_00310cd4 */
extern sk_pair_t sk_h_00310d34();  /* FUN_00310d34 */
extern sk_pair_t sk_h_00310d68();  /* FUN_00310d68 */
extern sk_pair_t sk_h_00310df0();  /* FUN_00310df0 */
extern sk_pair_t sk_h_003191e8();  /* FUN_003191e8 */
extern sk_pair_t sk_h_003192d8();  /* FUN_003192d8 */
extern sk_pair_t sk_h_0031945c();  /* FUN_0031945c */
extern sk_pair_t sk_h_00319808();  /* FUN_00319808 */
extern sk_pair_t sk_h_00319a4c();  /* FUN_00319a4c */
extern sk_pair_t sk_h_0031a29c();  /* FUN_0031a29c */
extern sk_pair_t sk_h_0031afcc();  /* FUN_0031afcc */
extern sk_pair_t sk_h_0031b080();  /* FUN_0031b080 */
extern sk_pair_t sk_h_003246a8();  /* FUN_003246a8 */
extern sk_pair_t sk_h_003246d4();  /* FUN_003246d4 */
extern sk_pair_t sk_h_003246ec();  /* FUN_003246ec */
extern sk_pair_t sk_h_00324704();  /* FUN_00324704 */
extern sk_pair_t sk_h_00324734();  /* FUN_00324734 */
extern sk_pair_t sk_h_0032474c();  /* FUN_0032474c */
extern sk_pair_t sk_h_00324764();  /* FUN_00324764 */
extern sk_pair_t sk_h_003247bc();  /* FUN_003247bc */
extern sk_pair_t sk_h_003247d4();  /* FUN_003247d4 */
extern sk_pair_t sk_h_00324814();  /* FUN_00324814 */
extern sk_pair_t sk_h_00324858();  /* FUN_00324858 */
extern sk_pair_t sk_h_00344120();  /* FUN_00344120 */
extern sk_pair_t sk_h_0034415c();  /* FUN_0034415c */
extern sk_pair_t sk_h_00344e54();  /* FUN_00344e54 */
extern sk_pair_t sk_h_0034789c();  /* FUN_0034789c */
extern sk_pair_t sk_h_00347d60();  /* FUN_00347d60 */
extern sk_pair_t sk_h_00347f2c();  /* FUN_00347f2c */
extern sk_pair_t sk_h_00347fb4();  /* FUN_00347fb4 */
extern sk_pair_t sk_h_003480e4();  /* FUN_003480e4 */
extern sk_pair_t sk_h_003483c4();  /* FUN_003483c4 */
extern sk_pair_t sk_h_003484e4();  /* FUN_003484e4 */
extern sk_pair_t sk_h_00348638();  /* FUN_00348638 */
extern sk_pair_t sk_h_003486b8();  /* FUN_003486b8 */
extern sk_pair_t sk_h_003486fc();  /* FUN_003486fc */
extern sk_pair_t sk_h_00348718();  /* FUN_00348718 */
extern sk_pair_t sk_h_00348730();  /* FUN_00348730 */
extern sk_pair_t sk_h_0034878c();  /* FUN_0034878c */
extern sk_pair_t sk_h_00348898();  /* FUN_00348898 */
extern sk_pair_t sk_h_003488bc();  /* FUN_003488bc */
extern sk_pair_t sk_h_0034895c();  /* FUN_0034895c */
extern sk_pair_t sk_h_003489a8();  /* FUN_003489a8 */
extern sk_pair_t sk_h_003489c0();  /* FUN_003489c0 */
extern sk_pair_t sk_h_00348a18();  /* FUN_00348a18 */
extern sk_pair_t sk_h_00348a34();  /* FUN_00348a34 */
extern sk_pair_t sk_h_00348b7c();  /* FUN_00348b7c */
extern sk_pair_t sk_h_00348c84();  /* FUN_00348c84 */
extern sk_pair_t sk_h_00348d4c();  /* FUN_00348d4c */
extern sk_pair_t sk_h_00348d64();  /* FUN_00348d64 */
extern sk_pair_t sk_h_00348d7c();  /* FUN_00348d7c */
extern sk_pair_t sk_h_00348e00();  /* FUN_00348e00 */
extern sk_pair_t sk_h_00348e18();  /* FUN_00348e18 */
extern sk_pair_t sk_h_00348e60();  /* FUN_00348e60 */
extern sk_pair_t sk_h_00348f38();  /* FUN_00348f38 */
extern sk_pair_t sk_h_00348f50();  /* FUN_00348f50 */
extern sk_pair_t sk_h_00348fb4();  /* FUN_00348fb4 */
extern sk_pair_t sk_h_00348fd8();  /* FUN_00348fd8 */
extern sk_pair_t sk_h_00349134();  /* FUN_00349134 */
extern sk_pair_t sk_h_00349178();  /* FUN_00349178 */
extern sk_pair_t sk_h_003491ec();  /* FUN_003491ec */
extern sk_pair_t sk_h_00349204();  /* FUN_00349204 */
extern sk_pair_t sk_h_0034921c();  /* FUN_0034921c */
extern sk_pair_t sk_h_003492ac();  /* FUN_003492ac */
extern sk_pair_t sk_h_00349370();  /* FUN_00349370 */
extern sk_pair_t sk_h_003493c4();  /* FUN_003493c4 */
extern sk_pair_t sk_h_003493ec();  /* FUN_003493ec */
extern sk_pair_t sk_h_00349424();  /* FUN_00349424 */
extern sk_pair_t sk_h_00349444();  /* FUN_00349444 */
extern sk_pair_t sk_h_00349494();  /* FUN_00349494 */
extern sk_pair_t sk_h_003494e8();  /* FUN_003494e8 */
extern sk_pair_t sk_h_00349580();  /* FUN_00349580 */
extern sk_pair_t sk_h_003495a8();  /* FUN_003495a8 */
extern sk_pair_t sk_h_00349644();  /* FUN_00349644 */
extern sk_pair_t sk_h_003496cc();  /* FUN_003496cc */
extern sk_pair_t sk_h_0034970c();  /* FUN_0034970c */
extern sk_pair_t sk_h_00349720();  /* FUN_00349720 */
extern sk_pair_t sk_h_0034975c();  /* FUN_0034975c */
extern sk_pair_t sk_h_003497b4();  /* FUN_003497b4 */
extern sk_pair_t sk_h_003497c8();  /* FUN_003497c8 */
extern sk_pair_t sk_h_003497ec();  /* FUN_003497ec */
extern sk_pair_t sk_h_00349800();  /* FUN_00349800 */
extern sk_pair_t sk_h_00349830();  /* FUN_00349830 */
extern sk_pair_t sk_h_003498a8();  /* FUN_003498a8 */
extern sk_pair_t sk_h_00349944();  /* FUN_00349944 */
extern sk_pair_t sk_h_0034998c();  /* FUN_0034998c */
extern sk_pair_t sk_h_003499dc();  /* FUN_003499dc */
extern sk_pair_t sk_h_00349a18();  /* FUN_00349a18 */
extern sk_pair_t sk_h_00349a68();  /* FUN_00349a68 */
extern sk_pair_t sk_h_00349b28();  /* FUN_00349b28 */
extern sk_pair_t sk_h_00349b3c();  /* FUN_00349b3c */
extern sk_pair_t sk_h_00349c70();  /* FUN_00349c70 */
extern sk_pair_t sk_h_00349c84();  /* FUN_00349c84 */
extern sk_pair_t sk_h_00349c98();  /* FUN_00349c98 */
extern sk_pair_t sk_h_00349cbc();  /* FUN_00349cbc */
extern sk_pair_t sk_h_00349dcc();  /* FUN_00349dcc */
extern sk_pair_t sk_h_00349de8();  /* FUN_00349de8 */
extern sk_pair_t sk_h_00349dfc();  /* FUN_00349dfc */
extern sk_pair_t sk_h_00349ef4();  /* FUN_00349ef4 */
extern sk_pair_t sk_h_00349fcc();  /* FUN_00349fcc */
extern sk_pair_t sk_h_0034a018();  /* FUN_0034a018 */
extern sk_pair_t sk_h_0034a148();  /* FUN_0034a148 */
extern sk_pair_t sk_h_0034a1f8();  /* FUN_0034a1f8 */
extern sk_pair_t sk_h_0034a2f8();  /* FUN_0034a2f8 */
extern sk_pair_t sk_h_0034a390();  /* FUN_0034a390 */
extern sk_pair_t sk_h_0034a414();  /* FUN_0034a414 */
extern sk_pair_t sk_h_0034a4a4();  /* FUN_0034a4a4 */
extern sk_pair_t sk_h_0034a5c8();  /* FUN_0034a5c8 */
extern sk_pair_t sk_h_0034a618();  /* FUN_0034a618 */
extern sk_pair_t sk_h_0034a688();  /* FUN_0034a688 */
extern sk_pair_t sk_h_0034a798();  /* FUN_0034a798 */
extern sk_pair_t sk_h_0034a7ac();  /* FUN_0034a7ac */
extern sk_pair_t sk_h_0034a96c();  /* FUN_0034a96c */
extern sk_pair_t sk_h_0034aa28();  /* FUN_0034aa28 */
extern sk_pair_t sk_h_0034aa54();  /* FUN_0034aa54 */
extern sk_pair_t sk_h_0034ab20();  /* FUN_0034ab20 */
extern sk_pair_t sk_h_0034ab88();  /* FUN_0034ab88 */
extern sk_pair_t sk_h_0034abec();  /* FUN_0034abec */
extern sk_pair_t sk_h_0034ac50();  /* FUN_0034ac50 */
extern sk_pair_t sk_h_0034ad00();  /* FUN_0034ad00 */
extern sk_pair_t sk_h_0034aee4();  /* FUN_0034aee4 */
extern sk_pair_t sk_h_0034b05c();  /* FUN_0034b05c */
extern sk_pair_t sk_h_0034b07c();  /* FUN_0034b07c */
extern sk_pair_t sk_h_0034b0c4();  /* FUN_0034b0c4 */
extern sk_pair_t sk_h_0034b0d4();  /* FUN_0034b0d4 */
extern sk_pair_t sk_h_0034b128();  /* FUN_0034b128 */
extern sk_pair_t sk_h_0034b18c();  /* FUN_0034b18c */
extern sk_pair_t sk_h_0034b278();  /* FUN_0034b278 */
extern sk_pair_t sk_h_0034b2a8();  /* FUN_0034b2a8 */
extern sk_pair_t sk_h_0034b2f8();  /* FUN_0034b2f8 */
extern sk_pair_t sk_h_0034b3c8();  /* FUN_0034b3c8 */
extern sk_pair_t sk_h_0034b3e8();  /* FUN_0034b3e8 */
extern sk_pair_t sk_h_0034b460();  /* FUN_0034b460 */
extern sk_pair_t sk_h_0034b4c0();  /* FUN_0034b4c0 */
extern sk_pair_t sk_h_0034b508();  /* FUN_0034b508 */
extern sk_pair_t sk_h_0034b518();  /* FUN_0034b518 */
extern sk_pair_t sk_h_0034b550();  /* FUN_0034b550 */
extern sk_pair_t sk_h_0034b5a8();  /* FUN_0034b5a8 */
extern sk_pair_t sk_h_0034b71c();  /* FUN_0034b71c */
extern sk_pair_t sk_h_0034b768();  /* FUN_0034b768 */
extern sk_pair_t sk_h_0034b778();  /* FUN_0034b778 */
extern sk_pair_t sk_h_0034b7c8();  /* FUN_0034b7c8 */
extern sk_pair_t sk_h_0034b7e4();  /* FUN_0034b7e4 */
extern sk_pair_t sk_h_0034b804();  /* FUN_0034b804 */
extern sk_pair_t sk_h_0034b824();  /* FUN_0034b824 */
extern sk_pair_t sk_h_0034b848();  /* FUN_0034b848 */
extern sk_pair_t sk_h_0034b89c();  /* FUN_0034b89c */
extern sk_pair_t sk_h_0034ba38();  /* FUN_0034ba38 */
extern sk_pair_t sk_h_0034ba68();  /* FUN_0034ba68 */
extern sk_pair_t sk_h_0034ba88();  /* FUN_0034ba88 */
extern sk_pair_t sk_h_0034bc58();  /* FUN_0034bc58 */
extern sk_pair_t sk_h_0034bccc();  /* FUN_0034bccc */
extern sk_pair_t sk_h_0034bd90();  /* FUN_0034bd90 */
extern sk_pair_t sk_h_0034bddc();  /* FUN_0034bddc */
extern sk_pair_t sk_h_0034bdfc();  /* FUN_0034bdfc */
extern sk_pair_t sk_h_0034befc();  /* FUN_0034befc */
extern sk_pair_t sk_h_0034bf64();  /* FUN_0034bf64 */
extern sk_pair_t sk_h_0034bfb4();  /* FUN_0034bfb4 */
extern sk_pair_t sk_h_0034bfe0();  /* FUN_0034bfe0 */
extern sk_pair_t sk_h_0034c074();  /* FUN_0034c074 */
extern sk_pair_t sk_h_0034c094();  /* FUN_0034c094 */
extern sk_pair_t sk_h_0034c0a4();  /* FUN_0034c0a4 */
extern sk_pair_t sk_h_0034c2d8();  /* FUN_0034c2d8 */
extern sk_pair_t sk_h_0034c2f8();  /* FUN_0034c2f8 */
extern sk_pair_t sk_h_0034c384();  /* FUN_0034c384 */
extern sk_pair_t sk_h_0034c3a0();  /* FUN_0034c3a0 */
extern sk_pair_t sk_h_0034c3f4();  /* FUN_0034c3f4 */
extern sk_pair_t sk_h_0034c5bc();  /* FUN_0034c5bc */
extern sk_pair_t sk_h_0034c684();  /* FUN_0034c684 */
extern sk_pair_t sk_h_0034c6d4();  /* FUN_0034c6d4 */
extern sk_pair_t sk_h_0034c780();  /* FUN_0034c780 */
extern sk_pair_t sk_h_0034c7d4();  /* FUN_0034c7d4 */
extern sk_pair_t sk_h_0034c7f0();  /* FUN_0034c7f0 */
extern sk_pair_t sk_h_0034c9c8();  /* FUN_0034c9c8 */
extern sk_pair_t sk_h_0034cd90();  /* FUN_0034cd90 */
extern sk_pair_t sk_h_0034ce68();  /* FUN_0034ce68 */
extern sk_pair_t sk_h_0034ce78();  /* FUN_0034ce78 */
extern sk_pair_t sk_h_0034ce98();  /* FUN_0034ce98 */
extern sk_pair_t sk_h_0034cea8();  /* FUN_0034cea8 */
extern sk_pair_t sk_h_0034cec4();  /* FUN_0034cec4 */
extern sk_pair_t sk_h_0034ced8();  /* FUN_0034ced8 */
extern sk_pair_t sk_h_0034cf54();  /* FUN_0034cf54 */
extern sk_pair_t sk_h_0034cff4();  /* FUN_0034cff4 */
extern sk_pair_t sk_h_0034d140();  /* FUN_0034d140 */
extern sk_pair_t sk_h_0034d180();  /* FUN_0034d180 */
extern sk_pair_t sk_h_0034d1b0();  /* FUN_0034d1b0 */
extern sk_pair_t sk_h_0034d234();  /* FUN_0034d234 */
extern sk_pair_t sk_h_0034d264();  /* FUN_0034d264 */
extern sk_pair_t sk_h_0034d364();  /* FUN_0034d364 */
extern sk_pair_t sk_h_0034d3d4();  /* FUN_0034d3d4 */
extern sk_pair_t sk_h_0034d3f4();  /* FUN_0034d3f4 */
extern sk_pair_t sk_h_0034d414();  /* FUN_0034d414 */
extern sk_pair_t sk_h_0034d464();  /* FUN_0034d464 */
extern sk_pair_t sk_h_0034d5ec();  /* FUN_0034d5ec */
extern sk_pair_t sk_h_0034d854();  /* FUN_0034d854 */
extern sk_pair_t sk_h_0034d868();  /* FUN_0034d868 */
extern sk_pair_t sk_h_0034d9ac();  /* FUN_0034d9ac */
extern sk_pair_t sk_h_0034d9cc();  /* FUN_0034d9cc */
extern sk_pair_t sk_h_0034da28();  /* FUN_0034da28 */
extern sk_pair_t sk_h_0034da88();  /* FUN_0034da88 */
extern sk_pair_t sk_h_0034dbb8();  /* FUN_0034dbb8 */
extern sk_pair_t sk_h_0034dc04();  /* FUN_0034dc04 */
extern sk_pair_t sk_h_0034ddd8();  /* FUN_0034ddd8 */
extern sk_pair_t sk_h_0034e208();  /* FUN_0034e208 */
extern sk_pair_t sk_h_0034e3fc();  /* FUN_0034e3fc */
extern sk_pair_t sk_h_0034e484();  /* FUN_0034e484 */
extern sk_pair_t sk_h_0034e4a4();  /* FUN_0034e4a4 */
extern sk_pair_t sk_h_0034e52c();  /* FUN_0034e52c */
extern sk_pair_t sk_h_0034e56c();  /* FUN_0034e56c */
extern sk_pair_t sk_h_0034e66c();  /* FUN_0034e66c */
extern sk_pair_t sk_h_0034e6fc();  /* FUN_0034e6fc */
extern sk_pair_t sk_h_0034e7f4();  /* FUN_0034e7f4 */
extern sk_pair_t sk_h_0034eb54();  /* FUN_0034eb54 */
extern sk_pair_t sk_h_0034eba4();  /* FUN_0034eba4 */
extern sk_pair_t sk_h_0034ecd8();  /* FUN_0034ecd8 */
extern sk_pair_t sk_h_0034edc8();  /* FUN_0034edc8 */
extern sk_pair_t sk_h_0034ede8();  /* FUN_0034ede8 */
extern sk_pair_t sk_h_0034ee68();  /* FUN_0034ee68 */
extern sk_pair_t sk_h_0034eea8();  /* FUN_0034eea8 */
extern sk_pair_t sk_h_0034ef38();  /* FUN_0034ef38 */
extern sk_pair_t sk_h_0034f064();  /* FUN_0034f064 */
extern sk_pair_t sk_h_0034f078();  /* FUN_0034f078 */
extern sk_pair_t sk_h_0034f114();  /* FUN_0034f114 */
extern sk_pair_t sk_h_0034f198();  /* FUN_0034f198 */
extern sk_pair_t sk_h_0034f1a8();  /* FUN_0034f1a8 */
extern sk_pair_t sk_h_0034f1c4();  /* FUN_0034f1c4 */
extern sk_pair_t sk_h_0034f2d4();  /* FUN_0034f2d4 */
extern sk_pair_t sk_h_0034f324();  /* FUN_0034f324 */
extern sk_pair_t sk_h_0034f334();  /* FUN_0034f334 */
extern sk_pair_t sk_h_0034f384();  /* FUN_0034f384 */
extern sk_pair_t sk_h_0034f404();  /* FUN_0034f404 */
extern sk_pair_t sk_h_0034f584();  /* FUN_0034f584 */
extern sk_pair_t sk_h_0034f604();  /* FUN_0034f604 */
extern sk_pair_t sk_h_0034f6a8();  /* FUN_0034f6a8 */
extern sk_pair_t sk_h_0034f798();  /* FUN_0034f798 */
extern sk_pair_t sk_h_0034f7b0();  /* FUN_0034f7b0 */
extern sk_pair_t sk_h_0034f8bc();  /* FUN_0034f8bc */
extern sk_pair_t sk_h_0034f98c();  /* FUN_0034f98c */
extern sk_pair_t sk_h_0034fb28();  /* FUN_0034fb28 */
extern sk_pair_t sk_h_0034fb88();  /* FUN_0034fb88 */
extern sk_pair_t sk_h_0034fbf4();  /* FUN_0034fbf4 */
extern sk_pair_t sk_h_0034fd14();  /* FUN_0034fd14 */
extern sk_pair_t sk_h_0034fd24();  /* FUN_0034fd24 */
extern sk_pair_t sk_h_0034fd5c();  /* FUN_0034fd5c */
extern sk_pair_t sk_h_0034fee0();  /* FUN_0034fee0 */
extern sk_pair_t sk_h_00350038();  /* FUN_00350038 */
extern sk_pair_t sk_h_00350078();  /* FUN_00350078 */
extern sk_pair_t sk_h_00350088();  /* FUN_00350088 */
extern sk_pair_t sk_h_00350104();  /* FUN_00350104 */
extern sk_pair_t sk_h_00350220();  /* FUN_00350220 */
extern sk_pair_t sk_h_00350278();  /* FUN_00350278 */
extern sk_pair_t sk_h_003503d0();  /* FUN_003503d0 */
extern sk_pair_t sk_h_003503ec();  /* FUN_003503ec */
extern sk_pair_t sk_h_00350404();  /* FUN_00350404 */
extern sk_pair_t sk_h_00350410();  /* FUN_00350410 */
extern sk_pair_t sk_h_0035041c();  /* FUN_0035041c */
extern sk_pair_t sk_h_0035047c();  /* FUN_0035047c */
extern sk_pair_t sk_h_00350488();  /* FUN_00350488 */
extern sk_pair_t sk_h_003504a0();  /* FUN_003504a0 */
extern sk_pair_t sk_h_003504c4();  /* FUN_003504c4 */
extern sk_pair_t sk_h_003504e8();  /* FUN_003504e8 */
extern sk_pair_t sk_h_003504f4();  /* FUN_003504f4 */
extern sk_pair_t sk_h_00350500();  /* FUN_00350500 */
extern sk_pair_t sk_h_00350518();  /* FUN_00350518 */
extern sk_pair_t sk_h_00350530();  /* FUN_00350530 */
extern sk_pair_t sk_h_00350560();  /* FUN_00350560 */
extern sk_pair_t sk_h_00350584();  /* FUN_00350584 */
extern sk_pair_t sk_h_0035060c();  /* FUN_0035060c */
extern sk_pair_t sk_h_00350630();  /* FUN_00350630 */
extern sk_pair_t sk_h_00350720();  /* FUN_00350720 */
extern sk_pair_t sk_h_0035072c();  /* FUN_0035072c */
extern sk_pair_t sk_h_00350744();  /* FUN_00350744 */
extern sk_pair_t sk_h_00350780();  /* FUN_00350780 */
extern sk_pair_t sk_h_00350798();  /* FUN_00350798 */
extern sk_pair_t sk_h_003507c8();  /* FUN_003507c8 */
extern sk_pair_t sk_h_003507e0();  /* FUN_003507e0 */
extern sk_pair_t sk_h_00350868();  /* FUN_00350868 */
extern sk_pair_t sk_h_0035089c();  /* FUN_0035089c */
extern sk_pair_t sk_h_003508c0();  /* FUN_003508c0 */
extern sk_pair_t sk_h_003508cc();  /* FUN_003508cc */
extern sk_pair_t sk_h_003508f0();  /* FUN_003508f0 */
extern sk_pair_t sk_h_00350914();  /* FUN_00350914 */
extern sk_pair_t sk_h_00350920();  /* FUN_00350920 */
extern sk_pair_t sk_h_00350944();  /* FUN_00350944 */
extern sk_pair_t sk_h_00350950();  /* FUN_00350950 */
extern sk_pair_t sk_h_00350968();  /* FUN_00350968 */
extern sk_pair_t sk_h_0035098c();  /* FUN_0035098c */
extern sk_pair_t sk_h_003509b0();  /* FUN_003509b0 */
extern sk_pair_t sk_h_003509bc();  /* FUN_003509bc */
extern sk_pair_t sk_h_003509f8();  /* FUN_003509f8 */
extern sk_pair_t sk_h_00350a1c();  /* FUN_00350a1c */
extern sk_pair_t sk_h_00350a34();  /* FUN_00350a34 */
extern sk_pair_t sk_h_00350a64();  /* FUN_00350a64 */
extern sk_pair_t sk_h_00350a70();  /* FUN_00350a70 */
extern sk_pair_t sk_h_00350a88();  /* FUN_00350a88 */
extern sk_pair_t sk_h_00350aac();  /* FUN_00350aac */
extern sk_pair_t sk_h_00350ab8();  /* FUN_00350ab8 */
extern sk_pair_t sk_h_00350ad0();  /* FUN_00350ad0 */
extern sk_pair_t sk_h_00350af4();  /* FUN_00350af4 */
extern sk_pair_t sk_h_00350b18();  /* FUN_00350b18 */
extern sk_pair_t sk_h_00350b3c();  /* FUN_00350b3c */
extern sk_pair_t sk_h_00350b54();  /* FUN_00350b54 */
extern sk_pair_t sk_h_00350b6c();  /* FUN_00350b6c */
extern sk_pair_t sk_h_00350b78();  /* FUN_00350b78 */
extern sk_pair_t sk_h_00350ba8();  /* FUN_00350ba8 */
extern sk_pair_t sk_h_00350bb4();  /* FUN_00350bb4 */
extern sk_pair_t sk_h_00350c08();  /* FUN_00350c08 */
extern sk_pair_t sk_h_00350c2c();  /* FUN_00350c2c */
extern sk_pair_t sk_h_00350c44();  /* FUN_00350c44 */
extern sk_pair_t sk_h_00350cb4();  /* FUN_00350cb4 */
extern sk_pair_t sk_h_00350db4();  /* FUN_00350db4 */
extern sk_pair_t sk_h_00350e84();  /* FUN_00350e84 */
extern sk_pair_t sk_h_00350f3c();  /* FUN_00350f3c */
extern sk_pair_t sk_h_00350f9c();  /* FUN_00350f9c */
extern sk_pair_t sk_h_00350fdc();  /* FUN_00350fdc */
extern sk_pair_t sk_h_00350ffc();  /* FUN_00350ffc */
extern sk_pair_t sk_h_00351094();  /* FUN_00351094 */
extern sk_pair_t sk_h_003510a0();  /* FUN_003510a0 */
extern sk_pair_t sk_h_003510ac();  /* FUN_003510ac */
extern sk_pair_t sk_h_003510b8();  /* FUN_003510b8 */
extern sk_pair_t sk_h_003510dc();  /* FUN_003510dc */
extern sk_pair_t sk_h_003510f4();  /* FUN_003510f4 */
extern sk_pair_t sk_h_00351118();  /* FUN_00351118 */
extern sk_pair_t sk_h_00351130();  /* FUN_00351130 */
extern sk_pair_t sk_h_0035113c();  /* FUN_0035113c */
extern sk_pair_t sk_h_00351160();  /* FUN_00351160 */
extern sk_pair_t sk_h_00351178();  /* FUN_00351178 */
extern sk_pair_t sk_h_003511a8();  /* FUN_003511a8 */
extern sk_pair_t sk_h_003511c0();  /* FUN_003511c0 */
extern sk_pair_t sk_h_003511cc();  /* FUN_003511cc */
extern sk_pair_t sk_h_003511d8();  /* FUN_003511d8 */
extern sk_pair_t sk_h_00351220();  /* FUN_00351220 */
extern sk_pair_t sk_h_0035122c();  /* FUN_0035122c */
extern sk_pair_t sk_h_00351238();  /* FUN_00351238 */
extern sk_pair_t sk_h_00351250();  /* FUN_00351250 */
extern sk_pair_t sk_h_00351274();  /* FUN_00351274 */
extern sk_pair_t sk_h_00351280();  /* FUN_00351280 */
extern sk_pair_t sk_h_003512c0();  /* FUN_003512c0 */
extern sk_pair_t sk_h_0035133c();  /* FUN_0035133c */
extern sk_pair_t sk_h_00351348();  /* FUN_00351348 */
extern sk_pair_t sk_h_00351360();  /* FUN_00351360 */
extern sk_pair_t sk_h_0035136c();  /* FUN_0035136c */
extern sk_pair_t sk_h_00351378();  /* FUN_00351378 */
extern sk_pair_t sk_h_00351384();  /* FUN_00351384 */
extern sk_pair_t sk_h_003513a8();  /* FUN_003513a8 */
extern sk_pair_t sk_h_003513d8();  /* FUN_003513d8 */
extern sk_pair_t sk_h_003513f0();  /* FUN_003513f0 */
extern sk_pair_t sk_h_0035142c();  /* FUN_0035142c */
extern sk_pair_t sk_h_00351444();  /* FUN_00351444 */
extern sk_pair_t sk_h_00351450();  /* FUN_00351450 */
extern sk_pair_t sk_h_003514a0();  /* FUN_003514a0 */
extern sk_pair_t sk_h_003514d0();  /* FUN_003514d0 */
extern sk_pair_t sk_h_003514e8();  /* FUN_003514e8 */
extern sk_pair_t sk_h_0035151c();  /* FUN_0035151c */
extern sk_pair_t sk_h_0035152c();  /* FUN_0035152c */
extern sk_pair_t sk_h_00351584();  /* FUN_00351584 */
extern sk_pair_t sk_h_003515b4();  /* FUN_003515b4 */
extern sk_pair_t sk_h_00351648();  /* FUN_00351648 */
extern sk_pair_t sk_h_003516cc();  /* FUN_003516cc */
extern sk_pair_t sk_h_003516d8();  /* FUN_003516d8 */
extern sk_pair_t sk_h_00351714();  /* FUN_00351714 */
extern sk_pair_t sk_h_0035172c();  /* FUN_0035172c */
extern sk_pair_t sk_h_003517b4();  /* FUN_003517b4 */
extern sk_pair_t sk_h_003517c0();  /* FUN_003517c0 */
extern sk_pair_t sk_h_003517cc();  /* FUN_003517cc */
extern sk_pair_t sk_h_003517d8();  /* FUN_003517d8 */
extern sk_pair_t sk_h_003518a0();  /* FUN_003518a0 */
extern sk_pair_t sk_h_0035190c();  /* FUN_0035190c */
extern sk_pair_t sk_h_00351930();  /* FUN_00351930 */
extern sk_pair_t sk_h_003519d4();  /* FUN_003519d4 */
extern sk_pair_t sk_h_00351a14();  /* FUN_00351a14 */
extern sk_pair_t sk_h_00351a50();  /* FUN_00351a50 */
extern sk_pair_t sk_h_00351a80();  /* FUN_00351a80 */
extern sk_pair_t sk_h_00351a98();  /* FUN_00351a98 */
extern sk_pair_t sk_h_00351aec();  /* FUN_00351aec */
extern sk_pair_t sk_h_00351b60();  /* FUN_00351b60 */
extern sk_pair_t sk_h_00351ba0();  /* FUN_00351ba0 */
extern sk_pair_t sk_h_00351c34();  /* FUN_00351c34 */
extern sk_pair_t sk_h_00351c4c();  /* FUN_00351c4c */
extern sk_pair_t sk_h_00351cd0();  /* FUN_00351cd0 */
extern sk_pair_t sk_h_00351cdc();  /* FUN_00351cdc */
extern sk_pair_t sk_h_00351cf4();  /* FUN_00351cf4 */
extern sk_pair_t sk_h_00351d0c();  /* FUN_00351d0c */
extern sk_pair_t sk_h_00351d18();  /* FUN_00351d18 */
extern sk_pair_t sk_h_00351db4();  /* FUN_00351db4 */
extern sk_pair_t sk_h_00351de4();  /* FUN_00351de4 */
extern sk_pair_t sk_h_00351dfc();  /* FUN_00351dfc */
extern sk_pair_t sk_h_00351e6c();  /* FUN_00351e6c */
extern sk_pair_t sk_h_00351e90();  /* FUN_00351e90 */
extern sk_pair_t sk_h_00351ec0();  /* FUN_00351ec0 */
extern sk_pair_t sk_h_00351ef8();  /* FUN_00351ef8 */
extern sk_pair_t sk_h_00351f28();  /* FUN_00351f28 */
extern sk_pair_t sk_h_00351f40();  /* FUN_00351f40 */
extern sk_pair_t sk_h_00351f88();  /* FUN_00351f88 */
extern sk_pair_t sk_h_00351fc0();  /* FUN_00351fc0 */
extern sk_pair_t sk_h_00352078();  /* FUN_00352078 */
extern sk_pair_t sk_h_003520d0();  /* FUN_003520d0 */
extern sk_pair_t sk_h_00352128();  /* FUN_00352128 */
extern sk_pair_t sk_h_003521b4();  /* FUN_003521b4 */
extern sk_pair_t sk_h_00352250();  /* FUN_00352250 */
extern sk_pair_t sk_h_003522b8();  /* FUN_003522b8 */
extern sk_pair_t sk_h_00352330();  /* FUN_00352330 */
extern sk_pair_t sk_h_0035237c();  /* FUN_0035237c */
extern sk_pair_t sk_h_003523f0();  /* FUN_003523f0 */
extern sk_pair_t sk_h_00352420();  /* FUN_00352420 */
extern sk_pair_t sk_h_0035242c();  /* FUN_0035242c */
extern sk_pair_t sk_h_00352474();  /* FUN_00352474 */
extern sk_pair_t sk_h_003524d4();  /* FUN_003524d4 */
extern sk_pair_t sk_h_00352680();  /* FUN_00352680 */
extern sk_pair_t sk_h_00352720();  /* FUN_00352720 */
extern sk_pair_t sk_h_00352758();  /* FUN_00352758 */
extern sk_pair_t sk_h_003527e0();  /* FUN_003527e0 */
extern sk_pair_t sk_h_00352840();  /* FUN_00352840 */
extern sk_pair_t sk_h_00352858();  /* FUN_00352858 */
extern sk_pair_t sk_h_00352864();  /* FUN_00352864 */
extern sk_pair_t sk_h_00352950();  /* FUN_00352950 */
extern sk_pair_t sk_h_00352998();  /* FUN_00352998 */
extern sk_pair_t sk_h_00352af0();  /* FUN_00352af0 */
extern sk_pair_t sk_h_00352b2c();  /* FUN_00352b2c */
extern sk_pair_t sk_h_00352b5c();  /* FUN_00352b5c */
extern sk_pair_t sk_h_00352bd4();  /* FUN_00352bd4 */
extern sk_pair_t sk_h_00352c4c();  /* FUN_00352c4c */
extern sk_pair_t sk_h_00352c58();  /* FUN_00352c58 */
extern sk_pair_t sk_h_00352c74();  /* FUN_00352c74 */
extern sk_pair_t sk_h_00352c80();  /* FUN_00352c80 */
extern sk_pair_t sk_h_00352db8();  /* FUN_00352db8 */
extern sk_pair_t sk_h_00352dd0();  /* FUN_00352dd0 */
extern sk_pair_t sk_h_00352e78();  /* FUN_00352e78 */
extern sk_pair_t sk_h_00352e9c();  /* FUN_00352e9c */
extern sk_pair_t sk_h_0035300c();  /* FUN_0035300c */
extern sk_pair_t sk_h_00353034();  /* FUN_00353034 */
extern sk_pair_t sk_h_0035305c();  /* FUN_0035305c */
extern sk_pair_t sk_h_003530d8();  /* FUN_003530d8 */
extern sk_pair_t sk_h_00353100();  /* FUN_00353100 */
extern sk_pair_t sk_h_0035310c();  /* FUN_0035310c */
extern sk_pair_t sk_h_00353118();  /* FUN_00353118 */
extern sk_pair_t sk_h_0035316c();  /* FUN_0035316c */
extern sk_pair_t sk_h_00353184();  /* FUN_00353184 */
extern sk_pair_t sk_h_003531cc();  /* FUN_003531cc */
extern sk_pair_t sk_h_003531d8();  /* FUN_003531d8 */
extern sk_pair_t sk_h_00353238();  /* FUN_00353238 */
extern sk_pair_t sk_h_00353468();  /* FUN_00353468 */
extern sk_pair_t sk_h_00353504();  /* FUN_00353504 */
extern sk_pair_t sk_h_00353540();  /* FUN_00353540 */
extern sk_pair_t sk_h_0035359c();  /* FUN_0035359c */
extern sk_pair_t sk_h_003535b4();  /* FUN_003535b4 */
extern sk_pair_t sk_h_0035367c();  /* FUN_0035367c */
extern sk_pair_t sk_h_003537e0();  /* FUN_003537e0 */
extern sk_pair_t sk_h_003539e4();  /* FUN_003539e4 */
extern sk_pair_t sk_h_00353a6c();  /* FUN_00353a6c */
extern sk_pair_t sk_h_00353a90();  /* FUN_00353a90 */
extern sk_pair_t sk_h_00353aa0();  /* FUN_00353aa0 */
extern sk_pair_t sk_h_00353b04();  /* FUN_00353b04 */
extern sk_pair_t sk_h_00353bf4();  /* FUN_00353bf4 */
extern sk_pair_t sk_h_00353c18();  /* FUN_00353c18 */
extern sk_pair_t sk_h_00353c60();  /* FUN_00353c60 */
extern sk_pair_t sk_h_00353cc0();  /* FUN_00353cc0 */
extern sk_pair_t sk_h_00353cd8();  /* FUN_00353cd8 */
extern sk_pair_t sk_h_00353cfc();  /* FUN_00353cfc */
extern sk_pair_t sk_h_00353d14();  /* FUN_00353d14 */
extern sk_pair_t sk_h_00353d64();  /* FUN_00353d64 */
extern sk_pair_t sk_h_00353e7c();  /* FUN_00353e7c */
extern sk_pair_t sk_h_00353ed8();  /* FUN_00353ed8 */
extern sk_pair_t sk_h_00353f2c();  /* FUN_00353f2c */
extern sk_pair_t sk_h_00353f44();  /* FUN_00353f44 */
extern sk_pair_t sk_h_00353ff4();  /* FUN_00353ff4 */
extern sk_pair_t sk_h_00354000();  /* FUN_00354000 */
extern sk_pair_t sk_h_00354010();  /* FUN_00354010 */
extern sk_pair_t sk_h_003540c4();  /* FUN_003540c4 */
extern sk_pair_t sk_h_003542d0();  /* FUN_003542d0 */
extern sk_pair_t sk_h_003542dc();  /* FUN_003542dc */
extern sk_pair_t sk_h_003543b8();  /* FUN_003543b8 */
extern sk_pair_t sk_h_003543d0();  /* FUN_003543d0 */
extern sk_pair_t sk_h_00354410();  /* FUN_00354410 */
extern sk_pair_t sk_h_003544c8();  /* FUN_003544c8 */
extern sk_pair_t sk_h_003545ac();  /* FUN_003545ac */
extern sk_pair_t sk_h_00354690();  /* FUN_00354690 */
extern sk_pair_t sk_h_00354714();  /* FUN_00354714 */
extern sk_pair_t sk_h_00354744();  /* FUN_00354744 */
extern sk_pair_t sk_h_003547b0();  /* FUN_003547b0 */
extern sk_pair_t sk_h_0035481c();  /* FUN_0035481c */
extern sk_pair_t sk_h_00354870();  /* FUN_00354870 */
extern sk_pair_t sk_h_00354888();  /* FUN_00354888 */
extern sk_pair_t sk_h_003548b8();  /* FUN_003548b8 */
extern sk_pair_t sk_h_003549c0();  /* FUN_003549c0 */
extern sk_pair_t sk_h_00354a00();  /* FUN_00354a00 */
extern sk_pair_t sk_h_00354a6c();  /* FUN_00354a6c */
extern sk_pair_t sk_h_00354c9c();  /* FUN_00354c9c */
extern sk_pair_t sk_h_00354ca8();  /* FUN_00354ca8 */
extern sk_pair_t sk_h_00354d14();  /* FUN_00354d14 */
extern sk_pair_t sk_h_00354d94();  /* FUN_00354d94 */
extern sk_pair_t sk_h_00354dc4();  /* FUN_00354dc4 */
extern sk_pair_t sk_h_00354de8();  /* FUN_00354de8 */
extern sk_pair_t sk_h_00354e00();  /* FUN_00354e00 */
extern sk_pair_t sk_h_00354e0c();  /* FUN_00354e0c */
extern sk_pair_t sk_h_00354f70();  /* FUN_00354f70 */
extern sk_pair_t sk_h_003551e8();  /* FUN_003551e8 */
extern sk_pair_t sk_h_003552f0();  /* FUN_003552f0 */
extern sk_pair_t sk_h_003553b8();  /* FUN_003553b8 */
extern sk_pair_t sk_h_00355560();  /* FUN_00355560 */
extern sk_pair_t sk_h_00355660();  /* FUN_00355660 */
extern sk_pair_t sk_h_00355754();  /* FUN_00355754 */
extern sk_pair_t sk_h_00355914();  /* FUN_00355914 */
extern sk_pair_t sk_h_00355a40();  /* FUN_00355a40 */
extern sk_pair_t sk_h_00355bb8();  /* FUN_00355bb8 */
extern sk_pair_t sk_h_00355cd4();  /* FUN_00355cd4 */
extern sk_pair_t sk_h_00355d6c();  /* FUN_00355d6c */
extern sk_pair_t sk_h_00355da8();  /* FUN_00355da8 */
extern sk_pair_t sk_h_00355eb0();  /* FUN_00355eb0 */
extern sk_pair_t sk_h_00355f70();  /* FUN_00355f70 */
extern sk_pair_t sk_h_00355fa0();  /* FUN_00355fa0 */
extern sk_pair_t sk_h_00355fd0();  /* FUN_00355fd0 */
extern sk_pair_t sk_h_00356000();  /* FUN_00356000 */
extern sk_pair_t sk_h_00356024();  /* FUN_00356024 */
extern sk_pair_t sk_h_00356084();  /* FUN_00356084 */
extern sk_pair_t sk_h_003561a0();  /* FUN_003561a0 */
extern sk_pair_t sk_h_003561ac();  /* FUN_003561ac */
extern sk_pair_t sk_h_00356224();  /* FUN_00356224 */
extern sk_pair_t sk_h_003562f8();  /* FUN_003562f8 */
extern sk_pair_t sk_h_00356304();  /* FUN_00356304 */
extern sk_pair_t sk_h_00356334();  /* FUN_00356334 */
extern sk_pair_t sk_h_00356340();  /* FUN_00356340 */
extern sk_pair_t sk_h_0035634c();  /* FUN_0035634c */
extern sk_pair_t sk_h_003563fc();  /* FUN_003563fc */
extern sk_pair_t sk_h_003564d0();  /* FUN_003564d0 */
extern sk_pair_t sk_h_00356524();  /* FUN_00356524 */
extern sk_pair_t sk_h_00356590();  /* FUN_00356590 */
extern sk_pair_t sk_h_003565a8();  /* FUN_003565a8 */
extern sk_pair_t sk_h_00356798();  /* FUN_00356798 */
extern sk_pair_t sk_h_00356900();  /* FUN_00356900 */
extern sk_pair_t sk_h_00356a7c();  /* FUN_00356a7c */
extern sk_pair_t sk_h_00356b38();  /* FUN_00356b38 */
extern sk_pair_t sk_h_00356bb0();  /* FUN_00356bb0 */
extern sk_pair_t sk_h_00356c6c();  /* FUN_00356c6c */
extern sk_pair_t sk_h_00356e1c();  /* FUN_00356e1c */
extern sk_pair_t sk_h_00356e28();  /* FUN_00356e28 */
extern sk_pair_t sk_h_00356e98();  /* FUN_00356e98 */
extern sk_pair_t sk_h_00357044();  /* FUN_00357044 */
extern sk_pair_t sk_h_0035717c();  /* FUN_0035717c */
extern sk_pair_t sk_h_003571a4();  /* FUN_003571a4 */
extern sk_pair_t sk_h_003575a4();  /* FUN_003575a4 */
extern sk_pair_t sk_h_003577c0();  /* FUN_003577c0 */
extern sk_pair_t sk_h_003578e4();  /* FUN_003578e4 */
extern sk_pair_t sk_h_00357a0c();  /* FUN_00357a0c */
extern sk_pair_t sk_h_00357a18();  /* FUN_00357a18 */
extern sk_pair_t sk_h_00357aec();  /* FUN_00357aec */
extern sk_pair_t sk_h_00357c74();  /* FUN_00357c74 */
extern sk_pair_t sk_h_00357cb4();  /* FUN_00357cb4 */
extern sk_pair_t sk_h_00357cec();  /* FUN_00357cec */
extern sk_pair_t sk_h_00357d84();  /* FUN_00357d84 */
extern sk_pair_t sk_h_00357e94();  /* FUN_00357e94 */
extern sk_pair_t sk_h_00357fa4();  /* FUN_00357fa4 */
extern sk_pair_t sk_h_00357ff4();  /* FUN_00357ff4 */
extern sk_pair_t sk_h_00358258();  /* FUN_00358258 */
extern sk_pair_t sk_h_00358288();  /* FUN_00358288 */
extern sk_pair_t sk_h_003582d8();  /* FUN_003582d8 */
extern sk_pair_t sk_h_003582e8();  /* FUN_003582e8 */
extern sk_pair_t sk_h_00358308();  /* FUN_00358308 */
extern sk_pair_t sk_h_00358334();  /* FUN_00358334 */
extern sk_pair_t sk_h_00358344();  /* FUN_00358344 */
extern sk_pair_t sk_h_00358374();  /* FUN_00358374 */
extern sk_pair_t sk_h_0035847c();  /* FUN_0035847c */
extern sk_pair_t sk_h_00358490();  /* FUN_00358490 */
extern sk_pair_t sk_h_0035851c();  /* FUN_0035851c */
extern sk_pair_t sk_h_00358528();  /* FUN_00358528 */
extern sk_pair_t sk_h_00358534();  /* FUN_00358534 */
extern sk_pair_t sk_h_00358870();  /* FUN_00358870 */
extern sk_pair_t sk_h_003588e8();  /* FUN_003588e8 */
extern sk_pair_t sk_h_00358af4();  /* FUN_00358af4 */
extern sk_pair_t sk_h_00358b60();  /* FUN_00358b60 */
extern sk_pair_t sk_h_00358d28();  /* FUN_00358d28 */
extern sk_pair_t sk_h_00358d58();  /* FUN_00358d58 */
extern sk_pair_t sk_h_00358d88();  /* FUN_00358d88 */
extern sk_pair_t sk_h_00358fe8();  /* FUN_00358fe8 */
extern sk_pair_t sk_h_00359338();  /* FUN_00359338 */
extern sk_pair_t sk_h_003593d0();  /* FUN_003593d0 */
extern sk_pair_t sk_h_00359440();  /* FUN_00359440 */
extern sk_pair_t sk_h_003594f4();  /* FUN_003594f4 */
extern sk_pair_t sk_h_00359500();  /* FUN_00359500 */
extern sk_pair_t sk_h_003596a4();  /* FUN_003596a4 */
extern sk_pair_t sk_h_0035976c();  /* FUN_0035976c */
extern sk_pair_t sk_h_00359874();  /* FUN_00359874 */
extern sk_pair_t sk_h_003599a0();  /* FUN_003599a0 */
extern sk_pair_t sk_h_00359a3c();  /* FUN_00359a3c */
extern sk_pair_t sk_h_00359ab0();  /* FUN_00359ab0 */
extern sk_pair_t sk_h_00359b70();  /* FUN_00359b70 */
extern sk_pair_t sk_h_00359b90();  /* FUN_00359b90 */
extern sk_pair_t sk_h_00359c64();  /* FUN_00359c64 */
extern sk_pair_t sk_h_00359ddc();  /* FUN_00359ddc */
extern sk_pair_t sk_h_00359de8();  /* FUN_00359de8 */
extern sk_pair_t sk_h_0035a034();  /* FUN_0035a034 */
extern sk_pair_t sk_h_0035a098();  /* FUN_0035a098 */
extern sk_pair_t sk_h_0035a16c();  /* FUN_0035a16c */
extern sk_pair_t sk_h_0035a200();  /* FUN_0035a200 */
extern sk_pair_t sk_h_0035a244();  /* FUN_0035a244 */
extern sk_pair_t sk_h_0035a250();  /* FUN_0035a250 */
extern sk_pair_t sk_h_0035a310();  /* FUN_0035a310 */
extern sk_pair_t sk_h_0035a31c();  /* FUN_0035a31c */
extern sk_pair_t sk_h_0035a334();  /* FUN_0035a334 */
extern sk_pair_t sk_h_0035a614();  /* FUN_0035a614 */
extern sk_pair_t sk_h_0035a70c();  /* FUN_0035a70c */
extern sk_pair_t sk_h_0035a798();  /* FUN_0035a798 */
extern sk_pair_t sk_h_0035a8e8();  /* FUN_0035a8e8 */
extern sk_pair_t sk_h_0035a9dc();  /* FUN_0035a9dc */
extern sk_pair_t sk_h_0035aa04();  /* FUN_0035aa04 */
extern sk_pair_t sk_h_0035aa2c();  /* FUN_0035aa2c */
extern sk_pair_t sk_h_0035aba4();  /* FUN_0035aba4 */
extern sk_pair_t sk_h_0035ac58();  /* FUN_0035ac58 */
extern sk_pair_t sk_h_0035bc70();  /* FUN_0035bc70 */
extern sk_pair_t sk_h_00365b6c();  /* FUN_00365b6c */
extern sk_pair_t sk_h_00369340();  /* FUN_00369340 */
extern sk_pair_t sk_h_00369584();  /* FUN_00369584 */
extern sk_pair_t sk_h_0036986c();  /* FUN_0036986c */
extern sk_pair_t sk_h_0036a804();  /* FUN_0036a804 */
extern sk_pair_t sk_h_0036a908();  /* FUN_0036a908 */
extern sk_pair_t sk_h_0036b118();  /* FUN_0036b118 */
extern sk_pair_t sk_h_0036b270();  /* FUN_0036b270 */
extern sk_pair_t sk_h_003722e4();  /* FUN_003722e4 */
extern sk_pair_t sk_h_0037233c();  /* FUN_0037233c */
extern sk_pair_t sk_h_00376820();  /* FUN_00376820 */
extern sk_pair_t sk_h_00377824();  /* FUN_00377824 */
extern sk_pair_t sk_h_00377bec();  /* FUN_00377bec */
extern sk_pair_t sk_h_003a25d4();  /* FUN_003a25d4 */
extern sk_pair_t sk_h_003a261c();  /* FUN_003a261c */
extern sk_pair_t sk_h_003d3470();  /* FUN_003d3470 */
extern sk_pair_t sk_h_003d34b8();  /* FUN_003d34b8 */
extern sk_pair_t sk_h_003d351c();  /* FUN_003d351c */

/* Forward declarations (full prototypes derived from the definitions). */
void sk_swift_vcall(void *ignored, void (*fn)(void));
void sk_swift_tailcall_a(void);
void sk_swift_tailcall_b(void);
void sk_swift_peek_byte(unsigned char *out);
bool sk_swift_utf8_category(unsigned int scalar);
void sk_swift_string_index_back(unsigned long s, unsigned long e, unsigned long flags);
void sk_swift_string_index_back_ascii(void);
long sk_swift_utf8_decode_scalar(unsigned long p1, unsigned long p2, unsigned long flags);
void sk_swift_throw(void);
long sk_swift_string_char_width(long base, unsigned long buf, unsigned long flags);
void sk_swift_throw_b(void);
void sk_swift_throw_c(void);
bool sk_swift_is_join_control(int scalar);
void sk_swift_string_lowercased(unsigned long p1);
unsigned int sk_swift_utf8buf_push_scalar(unsigned long scalar);
void sk_swift_utf8_decode_forward(unsigned long p1, unsigned long p2, long len);
void sk_swift_string_uppercased(void);
void sk_swift_count_leading_graphemes(void);
void sk_swift_count_leading(void);
unsigned int sk_swift_utf8buf_pop(void);
void sk_swift_utf8buf_pop_store(unsigned short *out);
unsigned int sk_swift_utf8buf_pop_validate(unsigned int v);
void sk_swift_string_slice_ascii(unsigned int *out, unsigned long *p2);
void sk_swift_string_slice(unsigned int *out);
long sk_swift_bytes_to_index(unsigned int a, unsigned int b, unsigned int c);
void sk_swift_bytes_to_index_store(unsigned int *out, unsigned int *src);
void sk_swift_validutf8_fatal(void);
unsigned int sk_swift_utf8buf_shift(unsigned int v, unsigned int src);
void sk_swift_validutf8_fatal_b(void);
void sk_swift_utf8buf_shift_store(unsigned int *out, unsigned int *src);
void sk_swift_utf8buf_shift_fatal(unsigned int *buf);
bool sk_swift_bitset_contains(unsigned int value, unsigned int bits);
void sk_swift_index_from_bytes(unsigned int *out, unsigned int *src, long off);
void sk_swift_utf8_slice_store(unsigned int *p1, unsigned long p2, unsigned int *p3);
long sk_swift_index_distance(unsigned int *a, unsigned int *b);
void sk_swift_utf8buf_push(int value);
int sk_swift_utf8buf_pop_scalar(void);
void sk_swift_string_index_bounds(unsigned int *out, unsigned long idx, long str, unsigned long extra);
void sk_swift_scalar_from_byte(unsigned int *out, unsigned char *b);
void sk_swift_utf8buf_push_byte(unsigned char *b);
void sk_swift_char_from_utf8(unsigned char *out, unsigned int *src);
void sk_swift_byte_peek(unsigned short *out);
void sk_swift_utf8buf_pop_byte(char *out);
void sk_swift_char_width_a(void);
void sk_swift_char_width_b(void);
void sk_swift_utf8buf_push4(int v);
void sk_object_dispatch(void);
void sk_object_alloc_pages_glue(void);
void sk_swift_array_store(unsigned long *src, unsigned int withRelease);
void sk_object_vcall(void);
void sk_object_alloc_call(void);
void sk_swift_array_store4(void);
void sk_swift_array_init(void);
void sk_swift_array_move(void);
void sk_swift_range_init(sk_pair_t *out);
void sk_object_method_loop_a(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5, unsigned long p6);
void sk_object_method_loop_b(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5, unsigned long p6);
void sk_object_method_loop_c(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5, unsigned long p6, unsigned long p7);
void sk_object_method_loop_d(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5, unsigned long p6, unsigned long p7);
void sk_object_dispatch_a(void);
void sk_object_count_get(void);
void sk_object_service_loop(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5);
sk_pair_t sk_swift_pointer_adopt(void);
void sk_swift_pointer_adopt_store(sk_pair_t *out);
void sk_swift_unsafe_mutrawptr_nil(void);
void sk_swift_unsafe_ptr_nil(void);
void sk_swift_unsafe_mutptr_nil(void);
void sk_object_method_loop_e(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5);
void sk_swift_alloc_checked(long n);
void sk_swift_alloc_checked_size(long n, long size);
void sk_swift_memcmp_range(long p1, long p2, long p3, long p4);
void sk_swift_wrap_1d80e0_a(void);
void sk_swift_wrap_1d80e0_b(void);
void sk_swift_dictionary_init(void);
void sk_swift_string_transform(void);
unsigned long sk_object_read_slot(void);
void sk_object_call_slot(void);
sk_pair_t sk_object_read_pair(void);
bool sk_object_compare(void);
void sk_object_dispatch_b(void);
sk_pair_t sk_swift_sort_partition(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4);
void sk_swift_sort_merge(unsigned long p1, unsigned long p2, long p3, unsigned long p4);
void sk_object_method_loop_f(unsigned long p1, unsigned long p2, unsigned long p3);
void sk_swift_sort_entry(unsigned long p1, unsigned long p2, unsigned long p3);
void sk_object_read_slot2(void);
long sk_swift_checked_add(long a, long b);
void sk_swift_checked_sub(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5);
void sk_swift_checked_add_store(unsigned long *out);
void * sk_swift_array_builder(long *out, unsigned long *src, long p3);
sk_pair_t sk_swift_array_builder_init(long *out, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5);
void sk_swift_array_builder_snapshot(unsigned long *out);
void sk_object_method_loop_g(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4);
void sk_swift_spin_check(void);
void sk_object_method_loop_h(unsigned long p1, unsigned long p2, unsigned long p3);
void sk_swift_hash(unsigned long p1, unsigned long p2, unsigned long p3);
void sk_swift_hash_update(void);
void sk_swift_hash_b(void);
void sk_swift_hash_wrap(unsigned long p1, long p2, unsigned long p3);
void sk_swift_hash_set(unsigned long p1, unsigned long p2, unsigned long p3);
void sk_swift_sequence_zip(void);
void sk_swift_sequence_zip_b(void);
void sk_object_method_loop_i(void);
unsigned long sk_swift_buf_capacity_clamp(void);
sk_pair_t sk_swift_collection_label(unsigned char which);
void sk_swift_label_wrap_a(void);
void sk_swift_label_wrap_b(sk_pair_t *out);
void sk_swift_label_wrap_c(void);
void sk_object_describe(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4);
void sk_object_debug_desc(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4);
unsigned int sk_swift_elem_count_check(void);
sk_pair_t sk_swift_optional_label(void);
void sk_swift_debug_wrap_a(unsigned long p1, unsigned long p2, unsigned long p3);
void sk_swift_debug_wrap_b(unsigned long p1, unsigned long p2, unsigned long p3);
void sk_swift_describe_wrap_a(unsigned long p1, long p2, unsigned long p3);
void sk_swift_describe_wrap_b(unsigned long p1, long p2, unsigned long p3);
void sk_swift_elem_wrap_a(void);
void sk_swift_elem_wrap_b(sk_pair_t *out);
void sk_swift_elem_wrap_c(void);
sk_pair_t sk_swift_collection_description(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4);
void sk_object_error(long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5, unsigned long p6);
void sk_swift_error_wrap_a(unsigned long p1, long p2, unsigned long p3);
void sk_swift_error_wrap_b(unsigned long p1, long p2, unsigned long p3);
void sk_swift_error_wrap_c(sk_pair_t *out, unsigned long p2, long p3, unsigned long p4);
void sk_object_dispatch_c(void);
unsigned long sk_swift_count_zero(long n);
unsigned long sk_swift_count_one(long n);
void sk_object_call_c(unsigned long p1);
void * sk_swift_collectionofone_peek(unsigned long p1, long n);
void * sk_swift_collectionofone_peek_b(unsigned long p1, long n);
void sk_swift_collectionofone_call(unsigned long p1, long n, long p3);
void sk_swift_collectionofone_call_b(unsigned long p1, long n, long p3);
void sk_swift_copy_into(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4);
void sk_swift_range_equal(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4);
void sk_object_release_wrap(void);
void sk_swift_collectionofone_trap(unsigned long p1, long *idx, long p3);
void * sk_swift_collectionofone_make(long *out, unsigned long *src);
void sk_swift_collectionofone_dtor(long *self);
sk_pair_t sk_swift_emptycollection_make(long *out, unsigned long *src, unsigned long p3);
void sk_object_release_wrap2(void);
void sk_swift_append(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4, unsigned long p5);
void sk_swift_count_one_pop_a(unsigned long *out, unsigned long *src);
void sk_swift_count_one_pop_b(unsigned long *src);
void sk_swift_insert_a(unsigned long p1, unsigned long p2, unsigned long p3);
void sk_swift_insert_b(void);
void sk_swift_insert_c(unsigned long p1, unsigned long p2, unsigned long p3);
void * sk_swift_collection_make(long *out, unsigned long *src);
void sk_swift_append_b(unsigned long p1, unsigned long p2);
void sk_swift_count_zero_pop_a(unsigned long *out, unsigned long *src);
void sk_swift_count_zero_pop_b(unsigned long *src);
void sk_swift_append_c(unsigned long p1);
void sk_swift_append_d(unsigned long p1);
void sk_swift_pointer_unwrap(void);
void sk_swift_string_build(unsigned long *out);
void sk_swift_string_build_store(unsigned long *out);
void sk_swift_sequence_concat(unsigned long p1, unsigned long p2, long p3, long p4);
void sk_swift_wrap_2c55b4_a(void);
void sk_swift_wrap_2c55b4_b(void);

/* FUN_002c6998 @ 0x002c6998   (est. sk_swift_vcall)
 * Ghidra: void FUN_002c6998(...)
 * See function-local comments for behavior.
 */
void sk_swift_vcall(void *ignored, void (*fn)(void))
{
    (void)ignored;
    fn();
}

/* FUN_002c69c0 @ 0x002c69c0   (est. sk_swift_tailcall_a)
 * Ghidra: void FUN_002c69c0(...)
 * See function-local comments for behavior.
 */
void sk_swift_tailcall_a(void)
{
    sk_h_002c6918();
}

/* FUN_002c69c4 @ 0x002c69c4   (est. sk_swift_tailcall_b)
 * Ghidra: void FUN_002c69c4(...)
 * See function-local comments for behavior.
 */
void sk_swift_tailcall_b(void)
{
    sk_h_002c6918();
}

/* FUN_002c69f8 @ 0x002c69f8   (est. sk_swift_peek_byte)
 * Ghidra: void FUN_002c69f8(...)
 * See function-local comments for behavior.
 */
void sk_swift_peek_byte(unsigned char *out)
{
    *out = (unsigned char)sk_h_0001a1c8().lo;
}

/* FUN_002c6a20 @ 0x002c6a20   (est. sk_swift_utf8_category)
 * Ghidra: bool FUN_002c6a20(...)
 * See function-local comments for behavior.
 */
bool sk_swift_utf8_category(unsigned int scalar)
{
    long v = (long)sk_h_003593d0((unsigned long)(scalar - 0x3400), 0, 0).lo;
    /* 8-way vector "below bound" reduction over the Unicode range table
     * (DAT_004e7c60/68/50/58); only its low bit is observed (summary). */
    unsigned int m = 0xffffffffu;
    bool r = true;
    if ((m & 1) == 0) {
        r = true;
        if (0x29u < (unsigned)(v - 0x3000))
            r = ((unsigned)(v - 0xff01) < 0x9d);
    }
    return r;
}

/* FUN_002c6aac @ 0x002c6aac   (est. sk_swift_string_index_back)
 * Ghidra: void FUN_002c6aac(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_index_back(unsigned long s, unsigned long e, unsigned long flags)
{
    sk_h_00041138();
    unsigned long u = sk_h_0008409c().lo;
    unsigned long off = u >> 16;
    unsigned long n;
    if (u > 0x1ffff) {
        if ((flags >> 0x3c & 1) != 0) {
            sk_h_0034d180();
            n = (unsigned long)sk_swift_string_char_width((long)off, flags, u);
        } else {
            if ((flags >> 0x3d & 1) == 0) {
                sk_h_0009461c();
                if ((long)sk_h_002a9ba8().lo == 0) {
                    sk_h_00347f2c();
                    sk_fatal_error(0xb, 2, "", 0, 2, "Swift.Range", 0x11, 2, 0, 1);
                }
                n = 1;
            } else {
                sk_h_003599a0(flags & 0xffffffffffffff);
                n = 1;
            }
            if (u != 0x20000) n = 1;
        }
    } else {
        n = off;
    }
    long d = (long)off - (long)n;
    if (d < 0) __builtin_trap();
    if (d != 0)
        sk_h_0035847c((unsigned long)(d * 0x10000) | 3, e);
    (void)s;
}

/* FUN_002c6c04 @ 0x002c6c04   (est. sk_swift_string_index_back_ascii)
 * Ghidra: void FUN_002c6c04(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_index_back_ascii(void)
{
    sk_h_00041138();
    sk_pair_t a = sk_h_0035316c();
    unsigned long u = a.lo >> 16;
    long l = (long)sk_h_002b4fc4(u, a.hi >> 16).lo;
    long off = (long)u - l;
    if (off < 0) __builtin_trap();
    if (off != 0)
        sk_h_0035847c((unsigned long)(off * 0x10000) | 1, (void *)0);
}

/* FUN_002c6d00 @ 0x002c6d00   (est. sk_swift_utf8_decode_scalar)
 * Ghidra: void FUN_002c6d00(...)
 * See function-local comments for behavior.
 */
long sk_swift_utf8_decode_scalar(unsigned long p1, unsigned long p2, unsigned long flags)
{
    (void)p1; (void)p2; (void)flags;
    sk_h_00348898(1);
    sk_h_0034a2f8();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift.Range", 0x11, 2, 0, 1);
    return 0;
}

/* FUN_002c6ffc @ 0x002c6ffc   (est. sk_swift_throw)
 * Ghidra: void FUN_002c6ffc(...)
 * See function-local comments for behavior.
 */
void sk_swift_throw(void)
{
    sk_h_0034e208();
    sk_h_0034f6a8();
    __builtin_trap();
}

/* FUN_002c7020 @ 0x002c7020   (est. sk_swift_string_char_width)
 * Ghidra: long FUN_002c7020(...)
 * See function-local comments for behavior.
 */
long sk_swift_string_char_width(long base, unsigned long buf, unsigned long flags)
{
    unsigned long p = (unsigned long)base;
    unsigned long prev = 0;
    (void)buf; (void)flags;
    while (p > 0) {
        unsigned char c = ((unsigned char *)base)[p - 1];
        unsigned long sc;
        if (c < 0x80) {
            sc = c; p -= 1;
        } else {
            sk_h_0034f7b0((unsigned int)((c << 0x18) ^ 0xffffffff));
            sc = (unsigned long)c;
            p -= 1;
        }
        if (sc == 0xd && prev == 0xa) return base - p;
        if (sk_swift_utf8_category((unsigned int)sc) && sk_swift_utf8_category((unsigned int)prev))
            return base - p;
        if (sk_swift_is_join_control((int)sc)) continue;
        prev = sc;
    }
    return base - (long)p;
}

/* FUN_002c7b44 @ 0x002c7b44   (est. sk_swift_throw_b)
 * Ghidra: void FUN_002c7b44(...)
 * See function-local comments for behavior.
 */
void sk_swift_throw_b(void)
{
    sk_h_0034e208();
    sk_h_0034f6a8();
    __builtin_trap();
}

/* FUN_002c7b68 @ 0x002c7b68   (est. sk_swift_throw_c)
 * Ghidra: void FUN_002c7b68(...)
 * See function-local comments for behavior.
 */
void sk_swift_throw_c(void)
{
    sk_h_0034e208();
    sk_h_0034f6a8();
    __builtin_trap();
}

/* FUN_002c7b8c @ 0x002c7b8c   (est. sk_swift_is_join_control)
 * Ghidra: bool FUN_002c7b8c(...)
 * See function-local comments for behavior.
 */
bool sk_swift_is_join_control(int scalar)
{
    unsigned long r = sk_h_003d351c().lo;
    bool b;
    if ((r & 1) == 0) {
        b = scalar != 0x94d && (scalar != 0x9cd && (scalar != 0xacd &&
            (scalar != 0xb4d && (scalar != 0xc4d && (scalar != 0xd4d && scalar != 0x200c)))));
    } else {
        b = false;
    }
    return b;
}

/* FUN_002c7c80 @ 0x002c7c80   (est. sk_swift_string_lowercased)
 * Ghidra: void FUN_002c7c80(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_lowercased(unsigned long p1)
{
    sk_pair_t a = sk_h_00354744();
    (void)p1;
    sk_h_00359ab0();
    sk_h_00350744();
    sk_pair_t v = sk_h_001a89a8();
    sk_h_00350744();
    sk_h_001a89a8();
    sk_h_0035aba4();
    sk_h_00349cbc(v.lo);
    sk_h_003a25d4();
    sk_h_00350744();
    sk_h_001a89a8();
    sk_h_00352c80();
    sk_h_00349cbc(0);
    sk_h_00350744();
    sk_h_001a89a8();
    sk_h_00352c80();
    sk_h_00349cbc(0);
    sk_pair_t z = sk_h_00084180();
    sk_h_003544c8(z.lo, z.hi, a.hi);
}

/* FUN_002c8070 @ 0x002c8070   (est. sk_swift_utf8buf_push_scalar)
 * Ghidra: uint FUN_002c8070(...)
 * See function-local comments for behavior.
 */
unsigned int sk_swift_utf8buf_push_scalar(unsigned long scalar)
{
    unsigned int r = (unsigned int)sk_h_0029bb80(sk_swift_fixedbuf[0], scalar).lo;
    if (r & 1) sk_swift_fixedbuf[1] = 0;
    sk_swift_fixedbuf[0] = (unsigned int)scalar;
    return r & 1;
}

/* FUN_002c80b8 @ 0x002c80b8   (est. sk_swift_utf8_decode_forward)
 * Ghidra: void FUN_002c80b8(...)
 * See function-local comments for behavior.
 */
void sk_swift_utf8_decode_forward(unsigned long p1, unsigned long p2, long len)
{
    /* Forward UTF-8 decoder consuming `len` bytes: decodes a scalar at the
     * buffer position, pushes it into the fixed buffer, and advances. */
    sk_h_00084220();
    sk_h_0035089c();
    long i = 0;
    while (i < len) {
        unsigned char b = ((unsigned char *)p1)[i];
        unsigned int sc = b;
        long width = 1;
        if ((char)b < 0) {
            sk_h_00352af0();
            switch (sk_h_00352af0().hi) {
            case 1: width = 2; break;
            case 2: width = 3; break;
            case 3: width = 4; break;
            }
        }
        unsigned long r = sk_h_0029bb80(sk_swift_fixedbuf[0], sc).lo;
        sk_swift_fixedbuf[0] = sc;
        if (r & 1) {
            sk_swift_fixedbuf[1] = 0;
            sk_h_00084234(i + width, (unsigned long)(i + width));
            return;
        }
        i += width;
    }
    (void)p2;
}

/* FUN_002c8284 @ 0x002c8284   (est. sk_swift_string_uppercased)
 * Ghidra: void FUN_002c8284(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_uppercased(void)
{
    /* Uppercasing entry mirroring sk_swift_string_lowercased: pulls the
     * receiver buffer (FUN_00354744/001a89a8), applies Unicode case-mapping
     * via the tables at DAT_005d0c71 etc., releases temporaries, and re-emits
     * through FUN_003544c8. */
    sk_pair_t a = sk_h_00354744();
    sk_h_003497ec();
    sk_h_001a89a8();
    sk_h_00354410();
    sk_h_003a25d4(0xe000000000000000);
    sk_swift_string_lowercased(a.lo & 0x1010101);
    sk_h_00352c74();
    sk_h_0034b824(0);
    sk_h_003a25d4();
    sk_h_0034c9c8();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_h_00355fa0();
    sk_h_00356e28();
    sk_h_0034b18c();
    sk_h_003a25d4();
    sk_h_002366a0(0x10, 1, (void *)a.lo);
    sk_h_00352c80();
    sk_h_0034c094(0);
    sk_h_003a25d4();
    sk_h_003497ec();
    sk_h_001a89a8();
    sk_h_003496cc();
    sk_h_003a25d4();
    sk_pair_t z = sk_h_003504c4();
    sk_h_003544c8(z.lo, z.hi, a.hi);
}

/* FUN_002c8568 @ 0x002c8568   (est. sk_swift_count_leading_graphemes)
 * Ghidra: void FUN_002c8568(...)
 * See function-local comments for behavior.
 */
void sk_swift_count_leading_graphemes(void)
{
    /* Counts leading grapheme clusters / scalars: walks backward over the
     * buffer, decoding scalars (FUN_0007c1c4/FUN_002c2384) and stopping at
     * whitespace/format or ZWJ boundaries (probe FUN_003593d0/FUN_0034e7f4),
     * accumulating the count and reporting its parity via FUN_00358344. */
    sk_h_00358374();
    sk_h_002c2440();
    long count = 0;
    long i = (long)sk_h_002c2440().lo;
    while (i > 0) {
        i -= 1;
        sk_h_0007c1c4();
        unsigned int sc = (unsigned int)sk_h_002c2384().lo;
        long probe = (long)sk_h_003593d0(sc - 0x1100, 0, 0, sc).lo;
        int cat = (int)sk_h_0034e7f4(probe, 0, 0).lo;
        if (cat == 0x200d) break;
        if (0x19 < (unsigned)(cat - 0x1f1e6)) {
            if (0xe0f < (unsigned)(cat - 0xe01f0)) {
                sk_h_003d34b8();
            }
            break;
        }
        count += 1;
    }
    sk_h_00358344((unsigned int)count & 1, (void *)0);
}

/* FUN_002c868c @ 0x002c868c   (est. sk_swift_count_leading)
 * Ghidra: void FUN_002c868c(...)
 * See function-local comments for behavior.
 */
void sk_swift_count_leading(void)
{
    sk_h_0035300c();
    int start = (int)sk_h_002c2440().lo;
    sk_h_0034ecd8(start - 0x94d);
    long i = (long)sk_h_002c2440().lo;
    unsigned int flag = 0;
    bool done = false;
    while (i > 0 && !done) {
        i -= 1;
        sk_h_0007c1c4();
        unsigned int sc = (unsigned int)sk_h_002c2384().lo;
        if (sk_h_003d351c().lo & 1) { flag = 1; break; }
        if (sc < 0x7f) break;
        if (sc != 0x200d) {
            unsigned long r = sk_h_0035a334(0, 0, 0, 0, 0).lo;
            if ((r & 1) || (unsigned)(sc - 0xe01f0) < 0xe10) { flag = 1; break; }
            if (sk_h_003d34b8(sc).lo != 1) break;
        }
        if (sk_h_003d351c(sc).lo & 1) {
            sk_h_003577c0(sc - 0x94d);
            flag = 1;
            break;
        }
        if (sc == 0x94d || sc == 0x9cd || sc == 0xacd || sc == 0xb4d ||
            sc == 0xc4d || sc == 0xd4d) flag = 1;
        else if (sc == 0x200c) flag = 1;
    }
    sk_h_00353238(flag & 1, (void *)0);
}

/* FUN_002c8834 @ 0x002c8834   (est. sk_swift_utf8buf_pop)
 * Ghidra: uint FUN_002c8834(...)
 * See function-local comments for behavior.
 */
unsigned int sk_swift_utf8buf_pop(void)
{
    unsigned int u = sk_swift_fixedbuf[0];
    unsigned int r;
    if (u == 0) r = 0;
    else { r = u - 1; sk_swift_fixedbuf[0] = u >> 8; }
    return r & 0xff | (unsigned int)(u == 0) << 8;
}

/* FUN_002c8864 @ 0x002c8864   (est. sk_swift_utf8buf_pop_store)
 * Ghidra: void FUN_002c8864(...)
 * See function-local comments for behavior.
 */
void sk_swift_utf8buf_pop_store(unsigned short *out)
{
    *out = (unsigned short)sk_swift_utf8buf_pop();
}

/* FUN_002c88f8 @ 0x002c88f8   (est. sk_swift_utf8buf_pop_validate)
 * Ghidra: uint FUN_002c88f8(...)
 * See function-local comments for behavior.
 */
unsigned int sk_swift_utf8buf_pop_validate(unsigned int v)
{
    if (v != 0) return v >> 8;
    sk_h_0035047c();
    sk_h_003486b8(0x69);
    sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0x69, 1);
    return 0;
}

/* FUN_002c8958 @ 0x002c8958   (est. sk_swift_string_slice_ascii)
 * Ghidra: void FUN_002c8958(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_slice_ascii(unsigned int *out, unsigned long *p2)
{
    sk_pair_t a = sk_h_001d39cc(*p2, sk_swift_fixedbuf[0]);
    out[0] = (unsigned int)a.lo;
    out[1] = (unsigned int)(a.lo >> 32);
    out[2] = (unsigned int)a.hi;
}

/* FUN_002c8990 @ 0x002c8990   (est. sk_swift_string_slice)
 * Ghidra: void FUN_002c8990(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_slice(unsigned int *out)
{
    sk_pair_t a = sk_h_001bcda8(sk_swift_fixedbuf[0]);
    out[0] = (unsigned int)a.lo;
    out[1] = (unsigned int)(a.lo >> 32);
    out[2] = (unsigned int)a.hi;
}

/* FUN_002c89dc @ 0x002c89dc   (est. sk_swift_bytes_to_index)
 * Ghidra: long FUN_002c89dc(...)
 * See function-local comments for behavior.
 */
long sk_swift_bytes_to_index(unsigned int a, unsigned int b, unsigned int c)
{
    if (a == 0) goto lzero;
    {
        unsigned int u = c;
        while (u != 0) {
            if (u == a) goto lzero;
            if (!(0xff < u)) break;
            u >>= 8;
        }
    }
    sk_h_0035047c();
    sk_h_003486b8(0x82);
    goto lfatal;
lzero:
    if (b == 0) return (__builtin_clzll(a) - __builtin_clzll(b)) >> 3;
    if (c != 0) {
        do {
            if (c == b) return (__builtin_clzll(a) - __builtin_clzll(b)) >> 3;
            if (!(0xff < c)) break;
            c >>= 8;
        } while (1);
    }
    sk_h_0035047c();
    sk_h_003486b8(0x83);
lfatal:
    sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0x82, 1);
    return 0;
}

/* FUN_002c8a88 @ 0x002c8a88   (est. sk_swift_bytes_to_index_store)
 * Ghidra: void FUN_002c8a88(...)
 * See function-local comments for behavior.
 */
void sk_swift_bytes_to_index_store(unsigned int *out, unsigned int *src)
{
    *out = sk_swift_utf8buf_pop_validate(*src);
}

/* FUN_002c8ac8 @ 0x002c8ac8   (est. sk_swift_validutf8_fatal)
 * Ghidra: void FUN_002c8ac8(...)
 * See function-local comments for behavior.
 */
void sk_swift_validutf8_fatal(void)
{
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0x69, 1);
    __builtin_trap();
}

/* FUN_002c8b20 @ 0x002c8b20   (est. sk_swift_utf8buf_shift)
 * Ghidra: uint FUN_002c8b20(...)
 * See function-local comments for behavior.
 */
unsigned int sk_swift_utf8buf_shift(unsigned int v, unsigned int src)
{
    unsigned int s = (unsigned int)__builtin_clzll(v) & 0x38;
    if (s != 0x20) return src >> (0x18 - s & 0x1f);
    sk_h_0035047c();
    sk_h_003486b8(0x77);
    sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0x77, 1);
    return 0;
}

/* FUN_002c8b40 @ 0x002c8b40   (est. sk_swift_validutf8_fatal_b)
 * Ghidra: void FUN_002c8b40(...)
 * See function-local comments for behavior.
 */
void sk_swift_validutf8_fatal_b(void)
{
    sk_h_0035047c();
    sk_h_003486b8(0x77);
    sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0x77, 1);
    __builtin_trap();
}

/* FUN_002c8b64 @ 0x002c8b64   (est. sk_swift_utf8buf_shift_store)
 * Ghidra: void FUN_002c8b64(...)
 * See function-local comments for behavior.
 */
void sk_swift_utf8buf_shift_store(unsigned int *out, unsigned int *src)
{
    *out = sk_swift_utf8buf_shift(*src, sk_swift_fixedbuf[0]);
}

/* FUN_002c8b94 @ 0x002c8b94   (est. sk_swift_utf8buf_shift_fatal)
 * Ghidra: void FUN_002c8b94(...)
 * See function-local comments for behavior.
 */
void sk_swift_utf8buf_shift_fatal(unsigned int *buf)
{
    unsigned int s = (unsigned int)__builtin_clzll(*buf) & 0x38;
    if (s != 0x20) {
        *buf = sk_swift_fixedbuf[0] >> (0x18 - s & 0x1f);
        return;
    }
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0x77, 1);
    __builtin_trap();
}

/* FUN_002c8c2c @ 0x002c8c2c   (est. sk_swift_bitset_contains)
 * Ghidra: bool FUN_002c8c2c(...)
 * See function-local comments for behavior.
 */
bool sk_swift_bitset_contains(unsigned int value, unsigned int bits)
{
    if (value == 0) return true;
    if (bits != 0) {
        do {
            bool hit = (bits == value);
            if (bits == value) return hit;
            if (!(0xff < bits)) return hit;
            bits >>= 8;
        } while (1);
    }
    return false;
}

/* FUN_002c8c64 @ 0x002c8c64   (est. sk_swift_index_from_bytes)
 * Ghidra: void FUN_002c8c64(...)
 * See function-local comments for behavior.
 */
void sk_swift_index_from_bytes(unsigned int *out, unsigned int *src, long off)
{
    unsigned int v = *src;
    unsigned int s = sk_swift_fixedbuf[0];
    if (!sk_swift_bitset_contains(s, s)) { sk_h_0035047c(); sk_h_003486b8(0x82); goto fatal; }
    if (!sk_swift_bitset_contains(v, s))  { sk_h_0035047c(); sk_h_003486b8(0x83); goto fatal; }
    {
        long l = (__builtin_clzll(s) - __builtin_clzll(v)) >> 3;
        long u = off + l;
        if (u < 0) { sk_h_0035047c(); sk_h_003486b8(0x8e); goto fatal; }
        unsigned long cap = sk_h_001a00fc(s).lo;
        if (u <= (long)cap) {
            unsigned int sh = (unsigned int)u << 2;
            *out = (s >> (sh & 0x1f)) >> (sh & 0x1f);
            return;
        }
        sk_h_0035047c(); sk_h_003486b8(0x8f);
    }
fatal:
    sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0x82, 1);
    __builtin_trap();
}

/* FUN_002c8d34 @ 0x002c8d34   (est. sk_swift_utf8_slice_store)
 * Ghidra: void FUN_002c8d34(...)
 * See function-local comments for behavior.
 */
void sk_swift_utf8_slice_store(unsigned int *p1, unsigned long p2, unsigned int *p3)
{
    sk_h_001e3730(*p1, p2, *p3, sk_swift_fixedbuf[0]);
    sk_h_00351fc0();
}

/* FUN_002c8d68 @ 0x002c8d68   (est. sk_swift_index_distance)
 * Ghidra: long FUN_002c8d68(...)
 * See function-local comments for behavior.
 */
long sk_swift_index_distance(unsigned int *a, unsigned int *b)
{
    unsigned int va = *a;
    unsigned int vb = *b;
    unsigned int s = sk_swift_fixedbuf[0];
    if (!sk_swift_bitset_contains(va, s)) { sk_h_0035047c(); sk_h_003486b8(0x82); goto fatal; }
    if (sk_swift_bitset_contains(vb, s))
        return (__builtin_clzll(va) - __builtin_clzll(vb)) >> 3;
    sk_h_0035047c(); sk_h_003486b8(0x83);
fatal:
    sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0x82, 1);
    return 0;
}

/* FUN_002c8df4 @ 0x002c8df4   (est. sk_swift_utf8buf_push)
 * Ghidra: void FUN_002c8df4(...)
 * See function-local comments for behavior.
 */
void sk_swift_utf8buf_push(int value)
{
    unsigned int u = sk_swift_fixedbuf[0];
    if ((u & 0xff000000) == 0) {
        sk_swift_fixedbuf[0] = ((unsigned int)(value + 1) & 0xff) <<
            (-((unsigned int)__builtin_clzll(u) & 0x18) & 0x18) | u;
        return;
    }
    sk_h_0035047c(); sk_h_003486b8(0xa7); sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0xa7, 1);
    __builtin_trap();
}

/* FUN_002c8e54 @ 0x002c8e54   (est. sk_swift_utf8buf_pop_scalar)
 * Ghidra: int FUN_002c8e54(...)
 * See function-local comments for behavior.
 */
int sk_swift_utf8buf_pop_scalar(void)
{
    unsigned int u = sk_swift_fixedbuf[0];
    if (u != 0) {
        sk_swift_fixedbuf[0] = u >> 8;
        return (int)(u - 1);
    }
    sk_h_0035047c(); sk_h_003486b8(0xb1); sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0xb1, 1);
    __builtin_trap();
}

/* FUN_002c9110 @ 0x002c9110   (est. sk_swift_string_index_bounds)
 * Ghidra: void FUN_002c9110(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_index_bounds(unsigned int *out, unsigned long idx, long str, unsigned long extra)
{
    long smeta = *(long *)(str - 8);
    sk_fp_00658c00(*(unsigned long *)(smeta + 0x40));
    unsigned long v = sk_h_00027754(extra).lo;
    long h = (long)sk_h_00377824(0, v, str, sk_td_00611b24, sk_td_00611b3c).lo;
    long hmeta = *(long *)(h - 8);
    sk_fp_00658c00((*(unsigned long *)(hmeta + 0x40) + 0xf) & ~0xfULL);
    unsigned int va = out[0];
    unsigned int vb = out[1];
    unsigned int s = sk_swift_fixedbuf[0];
    if (!sk_swift_bitset_contains(va, s)) { sk_h_0035047c(); sk_h_003486b8(0xc1); goto fatal; }
    if (!sk_swift_bitset_contains(vb, s)) { sk_h_0035047c(); sk_h_003486b8(0xc2); goto fatal; }
    {
        unsigned long dv = sk_h_001d96e0(va, s).lo;
        unsigned int dlo = (unsigned int)dv, dhi = (unsigned int)(dv >> 32);
        unsigned int acc = 0;
        if (dlo != dhi) {
            while (1) {
                unsigned int t = (unsigned int)dv;
                if (dlo < t || t <= dhi) { sk_h_0035047c(); sk_h_003486b8(0x2ca); goto fatal2; }
                if (acc & 0xff000000) goto fatal3;
                acc = (t & 0xff) << (-((unsigned int)__builtin_clzll(acc) & 0x18) & 0x18) | acc;
                if ((t >> 8) == dhi) break;
                dv = (unsigned long)(t >> 8);
            }
        }
        /* walk the validated range via the object method table */
        (*(void (**)(void))(smeta + 0x10))();
        (*(void (**)(void))((void *)sk_h_000a68c4(v).lo))();
        sk_h_00377bec(v, str, h, sk_td_00611b24, sk_td_00611b3c);
        sk_swift_fixedbuf[0] = acc;
        return;
    }
fatal3:
    sk_h_0035047c(); sk_h_003486b8(0xa7); goto fatal;
fatal2:
    sk_h_0035047c(); sk_h_003486b8(0x2ca);
fatal:
    sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_indexoob_005cdab0, 0x13, 2, sk_str_collection_005cdad0, 0x16);
    __builtin_trap();
}

/* FUN_002c94e4 @ 0x002c94e4   (est. sk_swift_scalar_from_byte)
 * Ghidra: void FUN_002c94e4(...)
 * See function-local comments for behavior.
 */
void sk_swift_scalar_from_byte(unsigned int *out, unsigned char *b)
{
    *out = (unsigned int)sk_h_0027195c(*b).lo;
}

/* FUN_002c9510 @ 0x002c9510   (est. sk_swift_utf8buf_push_byte)
 * Ghidra: void FUN_002c9510(...)
 * See function-local comments for behavior.
 */
void sk_swift_utf8buf_push_byte(unsigned char *b)
{
    unsigned int u = sk_swift_fixedbuf[0];
    if (u >> 0x18 == 0) {
        sk_swift_fixedbuf[0] = ((unsigned int)(*b + 1) & 0xff) <<
            (-((unsigned int)__builtin_clzll(u) & 0x18) & 0x18) | u;
        return;
    }
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0xa7, 1);
    __builtin_trap();
}

/* FUN_002c95b4 @ 0x002c95b4   (est. sk_swift_char_from_utf8)
 * Ghidra: void FUN_002c95b4(...)
 * See function-local comments for behavior.
 */
void sk_swift_char_from_utf8(unsigned char *out, unsigned int *src)
{
    *out = (unsigned char)sk_h_00272820(*src).lo;
}

/* FUN_002c95e8 @ 0x002c95e8   (est. sk_swift_byte_peek)
 * Ghidra: void FUN_002c95e8(...)
 * See function-local comments for behavior.
 */
void sk_swift_byte_peek(unsigned short *out)
{
    *out = (unsigned short)sk_h_000856ac().lo;
}

/* FUN_002c9610 @ 0x002c9610   (est. sk_swift_utf8buf_pop_byte)
 * Ghidra: void FUN_002c9610(...)
 * See function-local comments for behavior.
 */
void sk_swift_utf8buf_pop_byte(char *out)
{
    unsigned int u = sk_swift_fixedbuf[0];
    if (u != 0) {
        sk_swift_fixedbuf[0] = u >> 8;
        *out = (char)(u - 1);
        return;
    }
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0xb1, 1);
    __builtin_trap();
}

/* FUN_002c9694 @ 0x002c9694   (est. sk_swift_char_width_a)
 * Ghidra: void FUN_002c9694(...)
 * See function-local comments for behavior.
 */
void sk_swift_char_width_a(void)
{
    sk_h_0027675c();
}

/* FUN_002c9698 @ 0x002c9698   (est. sk_swift_char_width_b)
 * Ghidra: void FUN_002c9698(...)
 * See function-local comments for behavior.
 */
void sk_swift_char_width_b(void)
{
    sk_h_0027675c();
}

/* FUN_002c96ac @ 0x002c96ac   (est. sk_swift_utf8buf_push4)
 * Ghidra: void FUN_002c96ac(...)
 * See function-local comments for behavior.
 */
void sk_swift_utf8buf_push4(int v)
{
    unsigned int u = sk_swift_fixedbuf[0];
    unsigned long free = 4 - ((unsigned long)__builtin_clzll(u) >> 3);
    if (free <= (unsigned long)(__builtin_clzll((unsigned int)v) >> 3)) {
        sk_swift_fixedbuf[0] = (unsigned int)v << ((((unsigned int)free & 3) << 3)) | u;
        return;
    }
    sk_h_0035047c(); sk_h_003486b8(0xcf); sk_h_00349424();
    sk_fatal_error(0xb, 2, sk_str_005be7c0, 0, 2, sk_str_validutf8_005d08c0, 0x1b, 2, 0xcf, 1);
    __builtin_trap();
}

/* FUN_002c9740 @ 0x002c9740   (est. sk_object_dispatch)
 * Ghidra: void FUN_002c9740(...)
 * See function-local comments for behavior.
 */
void sk_object_dispatch(void)
{
    /* Object method dispatch: enters the object-service prologue and performs
     * an indirect call through the method table (+0x20). */
    sk_h_0035098c();
    sk_h_00354e00();
    sk_h_003549c0();
    sk_h_00350798();
    sk_h_00350404();
    /* indirect jump via table (too many branches, unrecoverable) */
    __builtin_trap();
}

/* FUN_002c97ac @ 0x002c97ac   (est. sk_object_alloc_pages_glue)
 * Ghidra: void FUN_002c97ac(...)
 * See function-local comments for behavior.
 */
void sk_object_alloc_pages_glue(void)
{
    sk_h_00355914();
    sk_h_0036b270();
    sk_h_0007c1c4();
}

/* FUN_002c97f0 @ 0x002c97f0   (est. sk_swift_array_store)
 * Ghidra: void FUN_002c97f0(...)
 * See function-local comments for behavior.
 */
void sk_swift_array_store(unsigned long *src, unsigned int withRelease)
{
    unsigned long a = src[0], b = src[1];
    unsigned long *dst = (unsigned long *)src[2];
    unsigned long d = src[3];
    if (withRelease & 1) {
        sk_h_0036b270(b);
        sk_h_003a25d4(d);
        dst[0] = a; dst[1] = b;
        sk_h_003a25d4(b);
        return;
    }
    sk_h_003a25d4(d);
    dst[0] = a; dst[1] = b;
}

/* FUN_002c9858 @ 0x002c9858   (est. sk_object_vcall)
 * Ghidra: void FUN_002c9858(...)
 * See function-local comments for behavior.
 */
void sk_object_vcall(void)
{
    sk_h_003562f8();
    __builtin_trap();
}

/* FUN_002c9884 @ 0x002c9884   (est. sk_object_alloc_call)
 * Ghidra: void FUN_002c9884(...)
 * See function-local comments for behavior.
 */
void sk_object_alloc_call(void)
{
    sk_h_00349fcc();
    sk_h_0036b270(0);
    sk_h_0008412c();
}

/* FUN_002c98b8 @ 0x002c98b8   (est. sk_swift_array_store4)
 * Ghidra: void FUN_002c98b8(...)
 * See function-local comments for behavior.
 */
void sk_swift_array_store4(void)
{
    unsigned long *dst = (unsigned long *)0;
    sk_h_00349a18();
    sk_h_003a25d4(dst[3]);
    dst[0] = 0; dst[1] = 0; dst[2] = 0; dst[3] = 0;
}

/* FUN_002c98f8 @ 0x002c98f8   (est. sk_swift_array_init)
 * Ghidra: void FUN_002c98f8(...)
 * See function-local comments for behavior.
 */
void sk_swift_array_init(void)
{
    unsigned long u = sk_h_0035a250().lo;
    sk_h_0036a908(u, 0x1722);
    sk_h_0034cd90();
    sk_h_0036b270();
    sk_h_003507e0();
}

/* FUN_002c9950 @ 0x002c9950   (est. sk_swift_array_move)
 * Ghidra: void FUN_002c9950(...)
 * See function-local comments for behavior.
 */
void sk_swift_array_move(void)
{
    sk_pair_t a = sk_h_00084220();
    unsigned long *src = (unsigned long *)*((unsigned long *)a.lo);
    unsigned long v0 = src[0], v1 = src[1], v2 = src[2], v3 = src[3];
    unsigned long *dst = (unsigned long *)src[4];
    unsigned long v5 = src[5];
    if ((a.hi & 1) == 0) {
        sk_h_003a25d4(v5);
        dst[0] = v0; dst[1] = v1; dst[2] = v2; dst[3] = v3;
    } else {
        sk_h_0036b270(v3);
        sk_h_003a25d4(v5);
        dst[0] = v0; dst[1] = v1; dst[2] = v2; dst[3] = v3;
        sk_h_003a25d4(src[3]);
    }
    sk_h_00084234(src, 0);
    sk_h_00012568();
}

/* FUN_002c99cc @ 0x002c99cc   (est. sk_swift_range_init)
 * Ghidra: void FUN_002c99cc(...)
 * See function-local comments for behavior.
 */
void sk_swift_range_init(sk_pair_t *out)
{
    sk_pair_t a = sk_h_002a3e64();
    *out = a;
    ((unsigned char *)out)[16] = 0;
    ((unsigned char *)out)[17] = 0;
}

/* FUN_002c9a04 @ 0x002c9a04   (est. sk_object_method_loop_a)
 * Ghidra: void FUN_002c9a04(...)
 * See function-local comments for behavior.
 */
void sk_object_method_loop_a(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4, unsigned long p5, unsigned long p6)
{
    /* Object-iteration service loop: acquires the target object (FUN_00377824)
     * and iterates its elements through opaque method-table closures (the
     * extraout_x8_01 / x19 / pcVar4 predicate and element-read calls), selecting
     * reset / advance / fatal sinks based on the iteration outcome, then
     * re-emits the result and releases via sk_h_0008e500.  All helper calls and
     * their ordering are preserved; the exact branch predicates are unresolved
     * indirect calls (see Notes). */
    sk_h_0008e518();
    sk_h_0008f6c0(p6);
    sk_h_00359338(); sk_h_00349dfc(); sk_h_0035136c();
    sk_h_00377824(); sk_h_0034ab20(); sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034bdfc(); sk_h_00349c70();
    sk_fp_00658c00(0);
    sk_h_003493c4(); sk_h_0034c2f8();
    sk_fp_00658c00(0);
    sk_h_0034b4c0(); sk_h_00351d0c();
    sk_pair_t v = sk_h_00351e90();
    (void)v;
    sk_h_0035305c(p6);
    sk_h_0034eba4();
    sk_h_00310a44(p6); sk_h_0034c7f0();
    /* reset/reload path (predicate true) */
    sk_h_0034eba4(); sk_h_0034ad00(); sk_h_003507c8();
    sk_h_00377bec(0, 0, 0); sk_h_00349370(); sk_h_00350f3c(0, 0x100);
    sk_h_0034c384(); sk_h_00353c18(); sk_h_00350ad0();
    sk_h_00348c84(p6); sk_h_00350ffc(); sk_h_0034c780();
    sk_h_003480e4(); sk_h_003523f0();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    __builtin_trap();
}

/* FUN_002c9da0 @ 0x002c9da0   (est. sk_object_method_loop_b)
 * Ghidra: void FUN_002c9da0(...)
 * See function-local comments for behavior.
 */
void sk_object_method_loop_b(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4, unsigned long p5, unsigned long p6)
{
    /* Object-iteration service loop (variant B): same structure as
     * sk_object_method_loop_a but with a different element-transform and
     * sink-selection helper set (FUN_003508cc / 00358d58 / 0031afcc /
     * FUN_001d30f8).  Helper sequence preserved; predicates are opaque
     * method-table calls. */
    sk_pair_t v = sk_h_0008e518();
    sk_h_0008f6c0(p6);
    sk_h_00358d88(); sk_h_00349dfc(); sk_h_003510f4();
    sk_h_00377824(); sk_h_0034ab20(); sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_00349494();
    sk_fp_00658c00(0);
    sk_h_003492ac();
    sk_fp_00658c00(0);
    sk_h_0034ba68(); sk_h_00352474();
    sk_pair_t q = sk_h_003508cc();
    (void)q;
    sk_h_00310a14(p6); sk_h_00350c44(); sk_h_000dbd0c();
    sk_h_00355a40(p6); sk_h_0034f334();
    sk_h_0034ad00(); sk_h_00350c2c(); sk_h_00377bec(0, 0, 0);
    sk_h_00348fb4(); sk_h_00350db4(0, 0x100);
    sk_h_0034d9cc(); sk_h_00354d94(); sk_h_003510a0();
    sk_h_00348c84(p6); sk_h_00350088(); sk_h_00356224(); sk_h_00351160();
    sk_h_003480e4(); sk_h_003523f0();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    __builtin_trap();
    sk_h_0034bfe0(); sk_h_0034f334();
    sk_h_00350a34(0); sk_h_001d30f8(v.lo, 0, p3, p5);
    sk_h_0008e500(0);
}

/* FUN_002ca154 @ 0x002ca154   (est. sk_object_method_loop_c)
 * Ghidra: void FUN_002ca154(...)
 * See function-local comments for behavior.
 */
void sk_object_method_loop_c(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4, unsigned long p5, unsigned long p6, unsigned long p7)
{
    /* Object-iteration service loop (variant C): 7-arg form; helper sequence
     * (FUN_00351e90 / 00355a40 / 0031afcc / FUN_0008e500) preserved; element
     * predicates are opaque method-table calls. */
    sk_h_0008e518();
    sk_h_0008f6c0(p7);
    sk_h_0035ac58(); sk_h_00349dfc(); sk_h_00351dfc();
    sk_h_00377824(); sk_h_0034ab20(); sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034bdfc(); sk_h_0034a5c8();
    sk_fp_00658c00(0);
    sk_h_003493c4(); sk_h_0034c684();
    sk_fp_00658c00(0);
    sk_h_0034c074(); sk_h_00351c4c();
    sk_pair_t q = sk_h_000b43d0();
    (void)q;
    sk_h_0035305c(p7); sk_h_0034fd14();
    sk_h_003547b0(p7); sk_h_0034f404();
    sk_h_0034ad00(); sk_h_00351360(); sk_h_00377bec(0, 0, 0);
    sk_h_003493ec(); sk_h_00350cb4(0, 0x100);
    sk_h_0034c7d4(); sk_h_003540c4(); sk_h_00351118();
    sk_h_00348c84(p7); sk_h_000b4390(); sk_h_003518a0();
    sk_h_00351cdc(); sk_h_00350b78();
    sk_h_003480e4(); sk_h_003523f0();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    __builtin_trap();
    sk_h_00350584(p7); sk_h_0034f404();
    sk_h_00351130(0); sk_h_003192d8(); sk_h_0008e500(0);
}

/* FUN_002ca524 @ 0x002ca524   (est. sk_object_method_loop_d)
 * Ghidra: void FUN_002ca524(...)
 * See function-local comments for behavior.
 */
void sk_object_method_loop_d(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4, unsigned long p5, unsigned long p6, unsigned long p7)
{
    /* Object-iteration service loop (variant D): 7-arg form; preserves the
     * helper sequence (FUN_00351e90 / 00355a40 / 0031afcc) and ends by
     * dispatching through FUN_001d31b0 and releasing via FUN_0008e500. */
    unsigned long v = sk_h_0008e518().lo;
    sk_h_0008f6c0(p7);
    sk_h_003564d0(); sk_h_00349dfc(); sk_h_003517cc();
    sk_h_00377824(); sk_h_0034ab20(); sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b0c4(); sk_h_00349c70();
    sk_fp_00658c00(0);
    sk_h_003493c4(); sk_h_0034c2f8();
    sk_fp_00658c00(0);
    sk_h_0034b4c0(); sk_h_00351d0c();
    sk_pair_t q = sk_h_00351e90();
    (void)q;
    sk_h_0035305c(p7); sk_h_0034eba4();
    sk_h_00358d58(p7); sk_h_0034c7f0();
    sk_h_0034ad00(); sk_h_0009e234(); sk_h_00377bec(0, 0, 0);
    sk_h_00348fb4(); sk_h_0034fee0();
    sk_h_0034cea8(); sk_h_00353468(); sk_h_00350c08();
    sk_h_00348c84(p7); sk_h_00350ffc(); sk_h_0034c780();
    sk_h_003480e4(); sk_h_003523f0();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    __builtin_trap();
    sk_h_0034dc04(); sk_h_0034c7f0();
    sk_h_00350b3c(0); sk_h_001d31b0(v, 0, p3, p4, p6);
    sk_h_0008e500(0);
}

/* FUN_002ca8ac @ 0x002ca8ac   (est. sk_object_dispatch_a)
 * Ghidra: void FUN_002ca8ac(...)
 * See function-local comments for behavior.
 */
void sk_object_dispatch_a(void)
{
    sk_h_00354744();
    sk_h_0034b5a8();
    sk_h_00310cd4();
    sk_h_0034bddc();
    sk_h_00351584();
    sk_h_0001df60();
    sk_h_0035041c();
    sk_h_001e2460(0, 0);
    sk_h_003544c8(0);
}

/* FUN_002ca928 @ 0x002ca928   (est. sk_object_count_get)
 * Ghidra: void FUN_002ca928(...)
 * See function-local comments for behavior.
 */
void sk_object_count_get(void)
{
    unsigned long u = sk_h_00353ed8().lo;
    sk_h_0035bc70(u, 1);
}

/* FUN_002ca95c @ 0x002ca95c   (est. sk_object_service_loop)
 * Ghidra: void FUN_002ca95c(...)
 * See function-local comments for behavior.
 */
void sk_object_service_loop(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4, unsigned long p5)
{
    /* Object service loop with a 2-word stack frame (local_10/local_8): saves
     * the target (param_3), runs the object-service prologue (FUN_00377824),
     * dispatches element operations through the method table (extraout_x8_01/02
     * and the closure at extraout_x9), and on the success path releases and
     * returns; on failure emits a fatal error. */
    unsigned long target = p3;
    sk_h_0008e518();
    sk_h_00356900();
    sk_h_00350a64();
    sk_h_00310d68();
    sk_h_000a6f88();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_00349494();
    sk_fp_00658c00(0);
    sk_h_00349178();
    sk_h_00350950(p5);
    sk_h_00349830();
    sk_h_003510f4();
    sk_h_00377824();
    sk_h_00348d7c();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b0d4();
    sk_h_00027788(p5);
    sk_h_00350104();
    sk_h_001a26e0();
    sk_pair_t a = sk_h_003509bc(0);
    (void)a;
    sk_h_003191e8();
    sk_pair_t b = sk_h_0034ce68();
    (void)b;
    sk_h_0034b278();
    sk_h_00350b18();
    sk_h_00377bec();
    sk_h_000a68f4();
    sk_h_0035133c();
    sk_h_003504f4();
    sk_pair_t c = sk_h_0035172c();
    sk_h_000839f8(c.lo, c.hi, target);
    sk_h_0034eea8();
    sk_h_00352420();
    sk_h_003508f0();
    sk_h_0008e500(0);
}

/* FUN_002caba4 @ 0x002caba4   (est. sk_swift_pointer_adopt)
 * Ghidra: void FUN_002caba4(...)
 * See function-local comments for behavior.
 */
sk_pair_t sk_swift_pointer_adopt(void)
{
    sk_pair_t a = sk_h_00354744();
    unsigned long p = a.lo;
    if (p != 0) {
        sk_pair_t v = sk_h_0006e778(0x16);
        sk_h_0034f064();
        sk_h_003a25d4();
        sk_h_003563fc(0xd000000000000013);
        sk_h_00355754(p);
        sk_h_0023560c();
        sk_h_00354a00();
        sk_h_0034f98c(0);
        sk_h_003a25d4();
        sk_h_0034bf64(0);
        sk_h_003a25d4();
        (void)v;
    }
    sk_pair_t z = sk_h_0006b6f4();
    sk_h_003544c8(z.lo, z.hi, a.hi);
    return z;
}

/* FUN_002cad70 @ 0x002cad70   (est. sk_swift_pointer_adopt_store)
 * Ghidra: void FUN_002cad70(...)
 * See function-local comments for behavior.
 */
void sk_swift_pointer_adopt_store(sk_pair_t *out)
{
    sk_pair_t a = sk_swift_pointer_adopt();
    *out = a;
    ((unsigned char *)out)[16] = 0;
    ((unsigned char *)out)[17] = 0;
}

/* FUN_002cada4 @ 0x002cada4   (est. sk_swift_unsafe_mutrawptr_nil)
 * Ghidra: void FUN_002cada4(...)
 * See function-local comments for behavior.
 */
void sk_swift_unsafe_mutrawptr_nil(void)
{
    /* UnsafeMutableRawPointer forced-unwrap: adopts the buffer (FUN_0006e778)
     * and stores the (ptr, owner) pair plus flags into the caller out-param;
     * traps with "UnsafeMutableRawPointer.nil" when the pointer is null. */
    sk_pair_t a = sk_h_00354744();
    unsigned long p = a.lo;
    if (p == 0) {
        sk_h_00358334(sk_str_unsafemutraw_005d3510);
        goto out;
    }
    sk_h_0006e778(0x1d);
    sk_h_0035a098();
    sk_h_0034f064();
    sk_h_0035a034();
    sk_h_00356e98(0);
    sk_h_003524d4(0xd00000000000001a);
    sk_h_002a4c98();
    sk_h_00350fdc();
    sk_h_003a25d4();
    sk_h_00355754(p);
    sk_h_0023560c();
    sk_h_00352c74();
    sk_h_0034c094(0);
    sk_h_003a25d4();
    sk_h_0034a618();
    sk_h_0034c9c8();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_h_0034b18c();
    sk_h_003a25d4();
    sk_h_00350560();
    sk_h_00355560();
    sk_h_0034b7c8();
    sk_h_0034f584();
    sk_h_003a25d4();
out:
    sk_h_003544c8(a.hi);
}

/* FUN_002caf6c @ 0x002caf6c   (est. sk_swift_unsafe_ptr_nil)
 * Ghidra: void FUN_002caf6c(...)
 * See function-local comments for behavior.
 */
void sk_swift_unsafe_ptr_nil(void)
{
    /* UnsafePointer forced-unwrap mirroring sk_swift_unsafe_mutrawptr_nil but
     * with the "UnsafePointer.nil" message and 0x13 buffer tag. */
    sk_pair_t a = sk_h_00354744();
    unsigned long p = a.lo;
    if (p == 0) {
        sk_h_00358334(sk_str_unsafeptr_005d34d0);
        goto out;
    }
    sk_h_0006e778(0x13);
    sk_h_0035a098();
    sk_h_0034f064();
    sk_h_0035a034();
    sk_h_00356e98(0);
    sk_h_003524d4(0xd000000000000010);
    sk_h_002a4c98();
    sk_h_00350fdc();
    sk_h_003a25d4();
    sk_h_00355754(p);
    sk_h_0023560c();
    sk_h_00352c74();
    sk_h_0034c094(0);
    sk_h_003a25d4();
    sk_h_0034a618();
    sk_h_0034c9c8();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_h_0034b18c();
    sk_h_003a25d4();
    sk_h_00350560();
    sk_h_00355560();
    sk_h_0034b7c8();
    sk_h_0034f584();
    sk_h_003a25d4();
out:
    sk_h_003544c8(a.hi);
}

/* FUN_002cb134 @ 0x002cb134   (est. sk_swift_unsafe_mutptr_nil)
 * Ghidra: void FUN_002cb134(...)
 * See function-local comments for behavior.
 */
void sk_swift_unsafe_mutptr_nil(void)
{
    /* UnsafeMutablePointer forced-unwrap: "UnsafeMutablePointer.nil" message,
     * 0x1a buffer tag. */
    sk_pair_t a = sk_h_00354744();
    unsigned long p = a.lo;
    if (p == 0) {
        sk_h_00358334(sk_str_unsafemutptr_005d3490);
        goto out;
    }
    sk_h_0006e778(0x1a);
    sk_h_0035a098();
    sk_h_0034f064();
    sk_h_0035a034();
    sk_h_00356e98(0);
    sk_h_003524d4(0xd000000000000017);
    sk_h_002a4c98();
    sk_h_00350fdc();
    sk_h_003a25d4();
    sk_h_00355754(p);
    sk_h_0023560c();
    sk_h_00352c74();
    sk_h_0034c094(0);
    sk_h_003a25d4();
    sk_h_0034a618();
    sk_h_0034c9c8();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_h_0034b18c();
    sk_h_003a25d4();
    sk_h_00350560();
    sk_h_00355560();
    sk_h_0034b7c8();
    sk_h_0034f584();
    sk_h_003a25d4();
out:
    sk_h_003544c8(a.hi);
}

/* FUN_002cb360 @ 0x002cb360   (est. sk_object_method_loop_e)
 * Ghidra: void FUN_002cb360(...)
 * See function-local comments for behavior.
 */
void sk_object_method_loop_e(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4, unsigned long p5)
{
    /* Object-iteration loop (variant E): acquires the object twice
     * (FUN_00377824), iterates via the method table closure (extraout_x8_00/01
     * and the x9 closure) comparing/releasing, then re-emits and releases. */
    unsigned long v = sk_h_0008e518().lo;
    sk_h_00351ef8(p5);
    sk_h_00352078();
    sk_h_00350920();
    sk_h_00351cd0();
    sk_h_00377824();
    sk_h_00348e00();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b2f8();
    sk_h_00350530();
    sk_h_0034d464();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b0c4();
    sk_h_00349c70();
    sk_fp_00658c00(0);
    sk_h_003491ec();
    sk_h_00350920();
    sk_h_00351cd0();
    sk_h_00377824();
    sk_h_00348fd8();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034aee4();
    sk_h_00356024(0);
    sk_h_00352680();
    sk_h_00350b6c();
    sk_h_0034b278();
    sk_h_003508f0();
    sk_h_00377bec();
    sk_h_000a68f4();
    sk_h_0034aa54();
    sk_h_0034ede8(0);
    sk_h_0029468c();
    sk_h_00350560(0);
    sk_h_00352420();
    sk_h_0008e500(p3, v);
}

/* FUN_002cb588 @ 0x002cb588   (est. sk_swift_alloc_checked)
 * Ghidra: void FUN_002cb588(...)
 * See function-local comments for behavior.
 */
void sk_swift_alloc_checked(long n)
{
    sk_h_0036a804(n, 0xffffffffffffffff);
    if (n >= 0) return;
    sk_h_003483c4();
    sk_h_00351094();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    __builtin_trap();
}

/* FUN_002cb5cc @ 0x002cb5cc   (est. sk_swift_alloc_checked_size)
 * Ghidra: void FUN_002cb5cc(...)
 * See function-local comments for behavior.
 */
void sk_swift_alloc_checked_size(long n, long size)
{
    long cap = (size < 0x11) ? -1 : (size - 1);
    sk_h_0036a804(n, cap);
    if (n >= 0) return;
    sk_h_003483c4();
    sk_h_00351094();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    __builtin_trap();
}

/* FUN_002cb61c @ 0x002cb61c   (est. sk_swift_memcmp_range)
 * Ghidra: void FUN_002cb61c(...)
 * See function-local comments for behavior.
 */
void sk_swift_memcmp_range(long p1, long p2, long p3, long p4)
{
    unsigned long u = 0;
    if (p1 != 0) u = (unsigned long)(p2 - p1);
    if (p3 == 0) {
        if (u != 0) goto bad;
    } else {
        if ((unsigned long)(p4 - p3) < u) goto bad;
        if (p1 != 0) { sk_h_002bf038(); return; }
    }
    return;
bad:
    sk_h_003488bc(1);
    sk_h_00349644();
    sk_h_00351094();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    __builtin_trap();
}

/* FUN_002cb968 @ 0x002cb968   (est. sk_swift_wrap_1d80e0_a)
 * Ghidra: void FUN_002cb968(...)
 * See function-local comments for behavior.
 */
void sk_swift_wrap_1d80e0_a(void)
{
    sk_h_001d80e0();
}

/* FUN_002cb96c @ 0x002cb96c   (est. sk_swift_wrap_1d80e0_b)
 * Ghidra: void FUN_002cb96c(...)
 * See function-local comments for behavior.
 */
void sk_swift_wrap_1d80e0_b(void)
{
    sk_h_001d80e0();
}

/* FUN_002cb984 @ 0x002cb984   (est. sk_swift_dictionary_init)
 * Ghidra: void FUN_002cb984(...)
 * See function-local comments for behavior.
 */
void sk_swift_dictionary_init(void)
{
    /* Dictionary literal initializer: builds the value via FUN_00319808 /
     * FUN_00365b6c, retrying the alternative key path (FUN_003582d8) on
     * failure, and finally stores the (0, owner) empty-key representation. */
    unsigned long u = sk_h_00353aa0().lo;
    sk_h_00319808(u, 0);
    u = sk_h_00002534(0x656280, 0).lo;
    unsigned long r = sk_h_00365b6c(0, 0, 0x67b1e8, u, 6).lo;
    if (r & 1) {
        sk_h_003582e8();
        sk_h_00344e54(0, 0x656288, 0);
        sk_h_00319808();
        sk_h_00002534(0x656290, 0);
        sk_pair_t a = sk_h_003582d8();
        r = sk_h_00365b6c(a.lo, a.hi, 0x67b1e8).lo;
        if (r & 1) {
            sk_h_003582e8();
            sk_h_00344e54(0, 0x656298, 0);
            sk_h_00353d64();
            sk_pair_t b = sk_h_0034895c();
            sk_h_0007c1c4(b.lo, b.hi, 0x67b1e8);
            sk_h_002060d4();
            sk_h_000026e8();
            return;
        }
    }
    sk_h_000026e8();
    sk_h_00077070(0, 0);
    sk_h_0034d9ac(0);
    sk_h_0008e5d8();
    sk_h_00353b04();
    sk_h_000b4390();
    sk_h_000026e8(0);
}

/* FUN_002cbae0 @ 0x002cbae0   (est. sk_swift_string_transform)
 * Ghidra: void FUN_002cbae0(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_transform(void)
{
    /* String transform (mapping) loop over the receiver buffer: iterates the
     * code units (FUN_00354744 / 001a89a8 / 00356340 / 002366a0), applies the
     * transform table for each, releasing temporaries, and re-emits through
     * FUN_003544c8.  Helper sequence preserved. */
    sk_pair_t a = sk_h_00354744();
    (void)a;
    sk_h_003497ec();
    sk_pair_t v = sk_h_001a89a8();
    (void)v;
    sk_h_003a25d4(0xe000000000000000);
    sk_pair_t b = sk_h_00356340();
    sk_h_002366a0(b.lo, b.hi, (void *)a.lo);
    sk_h_00356e28();
    sk_h_0034b824(0);
    sk_h_003a25d4();
    sk_h_0034fd5c();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_h_0034fb28();
    sk_h_001a89a8();
    sk_h_00354000();
    sk_h_0034c094();
    sk_h_003a25d4();
    sk_h_00351274();
    sk_h_00352db8();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_pair_t c = sk_h_00356340();
    sk_h_002366a0(c.lo, c.hi, (void *)(a.lo >> 8));
    sk_h_00356e28();
    sk_h_0034ddd8();
    sk_h_003a25d4();
    sk_h_0034fd5c();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_h_0034fb28();
    sk_h_001a89a8();
    sk_h_00352c74();
    sk_h_0034c094(0);
    sk_h_003a25d4();
    sk_h_0034c9c8();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_pair_t d = sk_h_00356340();
    sk_h_002366a0(d.lo, d.hi, (void *)(a.lo & 0xff));
    sk_h_00354a00();
    sk_h_0034b18c();
    sk_h_003a25d4();
    sk_h_0034ef38();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_h_003497ec();
    sk_h_001a89a8();
    sk_h_00349dcc();
    sk_h_003a25d4();
    sk_h_0034c9c8();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_pair_t z = sk_h_00350560();
    sk_h_003544c8(z.lo, z.hi, a.hi);
}

/* FUN_002cbea0 @ 0x002cbea0   (est. sk_object_read_slot)
 * Ghidra: undefined8 FUN_002cbea0(...)
 * See function-local comments for behavior.
 */
unsigned long sk_object_read_slot(void)
{
    /* Reads the element at the current slot: enters the object method prologue
     * and returns the slot value (word 0 of x20). */
    sk_h_00348e18();
    sk_fp_00658c00(0);
    sk_h_003491ec();
    sk_h_00356304(0);
    unsigned long r = 0;
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_00349134();
    long base = (long)sk_h_00359440().lo;
    sk_h_003522b8(*(int *)(base + 0x30));
    return r;
}

/* FUN_002cbf5c @ 0x002cbf5c   (est. sk_object_call_slot)
 * Ghidra: void FUN_002cbf5c(...)
 * See function-local comments for behavior.
 */
void sk_object_call_slot(void)
{
    sk_h_00353aa0();
    sk_h_000a6f88();
    sk_fp_00658c00(0);
    sk_h_0034a1f8();
    sk_h_00353cd8(0);
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_00349134();
    sk_h_00356b38();
    long base = (long)sk_h_0037233c().lo;
    sk_h_00354010(*(int *)(base + 0x30));
    /* indirect call through method table +0x20 */
}

/* FUN_002cc020 @ 0x002cc020   (est. sk_object_read_pair)
 * Ghidra: undefined1 [16] FUN_002cc020(...)
 * See function-local comments for behavior.
 */
sk_pair_t sk_object_read_pair(void)
{
    sk_pair_t r;
    sk_h_00348e18();
    sk_fp_00658c00(0);
    sk_h_003491ec();
    sk_h_00356304(0);
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_00349134();
    sk_h_00359440();
    sk_h_00355eb0();
    unsigned long lo = sk_h_003571a4().lo;
    unsigned long hi = 0;
    r.lo = lo; r.hi = hi;
    return r;
}

/* FUN_002cc0ec @ 0x002cc0ec   (est. sk_object_compare)
 * Ghidra: bool FUN_002cc0ec(...)
 * See function-local comments for behavior.
 */
bool sk_object_compare(void)
{
    /* Compares the current slot: returns whether the predicate result == 1. */
    sk_h_00348e18();
    sk_fp_00658c00(0);
    sk_h_003491ec();
    sk_h_00356304(0);
    sk_h_0007c1c4();
    int r = (int)sk_h_00369584().lo;
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_00349134();
    long base = (long)sk_h_00359440().lo;
    sk_h_003522b8(*(int *)(base + 0x30));
    return r == 1;
}

/* FUN_002cc1b4 @ 0x002cc1b4   (est. sk_object_dispatch_b)
 * Ghidra: void FUN_002cc1b4(...)
 * See function-local comments for behavior.
 */
void sk_object_dispatch_b(void)
{
    sk_h_003531d8();
    sk_h_003542d0();
    unsigned long r = sk_swift_sort_partition(0,0,0,0).lo;
    if ((r & 1) == 0) {
        sk_h_0034b3e8();
        sk_h_00019858();
    } else {
        sk_h_0034ba38();
        sk_swift_sort_merge(0,0,0,0);
    }
}

/* FUN_002cc21c @ 0x002cc21c   (est. sk_swift_sort_partition)
 * Ghidra: void FUN_002cc21c(...)
 * See function-local comments for behavior.
 */
sk_pair_t sk_swift_sort_partition(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4)
{
    /* Sort-partition core (the sorting loop body): acquires the object
     * (FUN_00377824), iterates elements reading each slot (sk_object_read_slot),
     * classifies with the comparator (FUN_00369584) and, based on the low/right
     * partition bookkeeping (locals local_18/local_10 and the large local_98/
     * local_90 stacks), either extends a run, reorders elements, or restarts.
     * Traps (SoftwareBreakpoint) on index/count overflow. */
    sk_h_0008e518();
    sk_h_003517b4();
    sk_h_003246ec();
    sk_h_00348d64();
    sk_fp_00658c00(0);
    sk_h_003493c4();
    sk_h_0034d234();
    sk_fp_00658c00(0);
    sk_h_0034abec();
    sk_fp_00658c00(0);
    sk_h_0034aa28();
    sk_h_00350500();
    sk_h_0034d464();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b71c();
    sk_h_0034a688();
    sk_fp_00658c00(0);
    sk_h_0034a1f8();
    sk_h_00350780(p4);
    sk_h_00349444();
    sk_h_00350ba8();
    sk_h_00377824();
    sk_h_00348e60();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b460();
    sk_h_00356000(p4);
    sk_h_00350944();
    sk_pair_t a = sk_h_000b43d0(0);
    (void)a;
    sk_h_000a68c4();
    sk_h_00351250();
    sk_h_003508cc();
    sk_h_003553b8();
    sk_h_003510ac();
    sk_h_00377bec();
    sk_h_000a68f4();
    sk_h_0034b2a8(0);
    sk_h_003511c0(0);
    sk_object_read_slot();                      /* read slot */
    sk_h_003561ac();
    sk_h_0034e484();
    sk_h_00350518();
    sk_h_00369584();                     /* comparator */
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_003543d0();
    sk_pair_t b = sk_h_0035041c();
    sk_h_00357fa4(b.lo, b.hi, 0);
    long base = (long)sk_h_0037233c().lo;
    (void)base;
    sk_h_0026a9a8(0, 0);
    sk_object_read_pair();
    sk_h_00351db4();
    sk_h_00358534(0x48d8000000000000);
    sk_h_003513d8();
    sk_h_00351450();
    sk_h_00369584();
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_003543d0();
    sk_pair_t c = sk_h_0035041c();
    sk_h_00357fa4(c.lo, c.hi, 0);
    sk_h_0037233c();
    sk_h_0035a8e8();
    sk_h_00258c60(0, 0, 0);
    sk_h_001f98a8(0);
    sk_h_002591b4(0x677880);             /* internal consistency fatal */
    sk_h_00352b5c();
    sk_h_001f06bc();
    sk_h_00352b2c();
    sk_h_00351b60();
    sk_h_00357ff4();
    sk_h_00353118();
    sk_h_00350ab8();
    sk_h_000b4390();
    sk_h_001f4084();
    sk_h_003a25d4();
    sk_h_003a25d4();
    sk_h_003a25d4();
    sk_h_00353034();
    sk_h_0008e500(0, 0);
    return (sk_pair_t){0, 0};
}

/* FUN_002cc98c @ 0x002cc98c   (est. sk_swift_sort_merge)
 * Ghidra: void FUN_002cc98c(...)
 * See function-local comments for behavior.
 */
void sk_swift_sort_merge(unsigned long p1, unsigned long p2, long p3, unsigned long p4)
{
    /* Sort-merge / index-lookup finaliser: enters the object prologue, runs a
     * binary search over the sorted buffer (FUN_0019fd10 / comparator
     * FUN_00369584) adjusting the range, then either re-emits the merged result
     * through FUN_0019e578 and releases, or traps on inconsistency. */
    sk_pair_t a = sk_h_0008e518();
    (void)a;
    sk_h_003246ec(0);
    sk_h_0034ab20();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b05c();
    sk_h_00356bb0(p4);
    long h = (long)sk_h_0029207c(0, 0).lo;
    sk_h_00350488();
    sk_h_00310d34();
    sk_h_00348718();
    sk_h_00376820(0, 0);
    unsigned long r = sk_h_0019fd10(0, 0).lo;
    if ((r & 1) != 0) {
        unsigned long cnt = *(unsigned long *)(h + 0x10);
        if (cnt != 0) {
            unsigned long lo = 0, hi = cnt, mid = 0;
            do {
                unsigned long mid = (lo + hi) / 2;
                sk_h_003511d8(mid);
                sk_h_0019ea20();
                sk_h_00350630();
                int cmp = (int)sk_h_00369584().lo;
                if (cmp == 1) {
                    if (hi <= mid) goto bad;
                    lo = mid + 1;
                } else if (mid < lo) goto bad;
                sk_h_00349b28();
                sk_h_00027614();
                sk_h_0035113c();
                long base = (long)sk_h_0037233c().lo;
                (void)base;
                hi = mid;
            } while (lo != mid);
            if ((long)mid < 0) goto bad;
        }
    }
    sk_h_0034ce98();
    sk_h_00350488();
    sk_h_00310df0();
    sk_h_0034e3fc();
    sk_h_0019e578(0);
    sk_h_0034f384();
    sk_h_0034bfb4();
    sk_h_0019eb70();
    sk_h_00351a50();
    sk_h_0036b118(h);
    sk_h_0019e578(0, 0, 0);
    sk_h_0008e500(0, 0, 0);
    return;
bad:
    sk_h_00350410();
    sk_h_003484e4();
    sk_h_003499dc();
    sk_h_00347d60();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    __builtin_trap();
}

/* FUN_002ccc10 @ 0x002ccc10   (est. sk_object_method_loop_f)
 * Ghidra: void FUN_002ccc10(...)
 * See function-local comments for behavior.
 */
void sk_object_method_loop_f(unsigned long p1, unsigned long p2, unsigned long p3)
{
    /* Object-iteration loop (variant F): 3-arg form; helper sequence preserved
     * (FUN_00377824 / 00369584 comparator / 0011aa70 closure / FUN_0008e500). */
    sk_h_0008e518();
    unsigned long v = sk_h_003517b4().lo;
    sk_h_003246ec(v, p3);
    sk_h_00348e18();
    sk_fp_00658c00(0);
    sk_h_00348a34();
    sk_fp_00658c00(0);
    sk_h_0034c2d8();
    sk_h_0034d414();
    sk_h_003515b4();
    sk_h_003722e4();
    sk_h_000a6f88();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    long base = (long)sk_h_0034cff4().lo;
    (void)base;
    sk_h_0011aa70();
    sk_h_003508c0(0);
    sk_h_00084180();
    int cmp = (int)sk_h_00369584().lo;
    sk_h_0034b778();
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_00349134();
    sk_h_00356b38();
    sk_h_0037233c();
    sk_h_003508cc();
    sk_h_00369584();
    sk_h_0034b518();
    sk_h_003509bc();
    sk_object_read_slot();
    sk_h_00354dc4();
    sk_object_read_slot();
    sk_h_00084180(0);
    unsigned long out = sk_h_003548b8().lo;
    sk_h_0008e500(out, 0);
    (void)cmp;
}

/* FUN_002cce8c @ 0x002cce8c   (est. sk_swift_sort_entry)
 * Ghidra: void FUN_002cce8c(...)
 * See function-local comments for behavior.
 */
void sk_swift_sort_entry(unsigned long p1, unsigned long p2, unsigned long p3)
{
    /* Sort entry point: builds the 3-word stack frame, installs the comparator
     * closure (FUN_003246a8), and dispatches to sk_swift_sort_merge. */
    sk_h_00350a64();
    sk_h_003246d4();
    sk_h_003504e8();
    sk_h_003246ec();
    sk_h_00354714();
    sk_h_003511cc(0, 0);
    sk_h_000262fc();
    sk_h_00350488();
    sk_h_00310d34();
    sk_h_00348718();
    sk_h_00376820(0, 0);
    sk_h_00350968(0);
    sk_swift_sort_merge(0,0,0,0);
}

/* FUN_002ccf5c @ 0x002ccf5c   (est. sk_object_read_slot2)
 * Ghidra: void FUN_002ccf5c(...)
 * See function-local comments for behavior.
 */
void sk_object_read_slot2(void)
{
    /* Object slot reader (variant): returns the element word plus flags via the
     * method table (+0x20) and re-emits through FUN_00369340. */
    sk_h_0008e518();
    sk_h_00351a80();
    sk_h_003246ec(0);
    sk_h_00348e00();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b2f8();
    sk_h_0034b508(0);
    sk_h_00350560();
    int cmp = (int)sk_h_00369584().lo;
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_00349134();
    sk_h_00356b38();
    sk_h_0037233c();
    sk_h_00355eb0();
    sk_h_00354010();
    sk_pair_t z = sk_h_003507e0();
    sk_h_00369340(z.lo, z.hi, cmp != 1);
    sk_h_0008e500(0);
}

/* FUN_002cd068 @ 0x002cd068   (est. sk_swift_checked_add)
 * Ghidra: long FUN_002cd068(...)
 * See function-local comments for behavior.
 */
long sk_swift_checked_add(long a, long b)
{
    long x = *(long *)(b + 0x10);
    long y = *(long *)(a + 0x10);
    if ((unsigned long)(x + y) >= (unsigned long)x)
        return x + y;
    __builtin_trap();
    return 0;
}

/* FUN_002cd080 @ 0x002cd080   (est. sk_swift_checked_sub)
 * Ghidra: void FUN_002cd080(...)
 * See function-local comments for behavior.
 */
void sk_swift_checked_sub(unsigned long p1, unsigned long p2, unsigned long p3,
                          unsigned long p4, unsigned long p5)
{
    sk_h_000867ec();
    sk_h_003516cc();
    sk_h_003246ec();
    sk_h_0019ea20(0, 0);
    (void)p1; (void)p2; (void)p3; (void)p4; (void)p5;
}

/* FUN_002cd0ec @ 0x002cd0ec   (est. sk_swift_checked_add_store)
 * Ghidra: void FUN_002cd0ec(...)
 * See function-local comments for behavior.
 */
void sk_swift_checked_add_store(unsigned long *out)
{
    *out = sk_swift_checked_add(sk_swift_fixedbuf[0], sk_swift_fixedbuf[1]);
}

/* FUN_002cd118 @ 0x002cd118   (est. sk_swift_array_builder)
 * Ghidra: undefined * FUN_002cd118(...)
 * See function-local comments for behavior.
 */
void *sk_swift_array_builder(long *out, unsigned long *src, long p3)
{
    long p = (long)sk_h_0036a908(0x28, 0xb5ba).lo;
    *out = p;
    unsigned long u = sk_swift_array_builder_init((long *)p, *src, sk_swift_fixedbuf[0], sk_swift_fixedbuf[1],
                                    *(unsigned long *)(p3 + 0x10)).lo;
    *(unsigned long *)(p + 0x20) = u;
    return (void *)sk_td_003471a4;
}

/* FUN_002cd190 @ 0x002cd190   (est. sk_swift_array_builder_init)
 * Ghidra: undefined1 [16] FUN_002cd190(...)
 * See function-local comments for behavior.
 */
sk_pair_t sk_swift_array_builder_init(long *out, unsigned long p2, unsigned long p3,
                            unsigned long p4, unsigned long p5)
{
    sk_pair_t r;
    long p = (long)sk_h_003246ec(0, p5).lo;
    *out = p;
    long meta = *(long *)(p - 8);
    out[1] = meta;
    long buf = (long)sk_h_0036a908(*(unsigned long *)(meta + 0x40), 0x577f).lo;
    out[2] = buf;
    sk_swift_checked_sub(buf, p2, p3, p4, p5);
    r.lo = (unsigned long)sk_td_003471a8;
    r.hi = (unsigned long)buf;
    return r;
}

/* FUN_002cd250 @ 0x002cd250   (est. sk_swift_array_builder_snapshot)
 * Ghidra: void FUN_002cd250(...)
 * See function-local comments for behavior.
 */
void sk_swift_array_builder_snapshot(unsigned long *out)
{
    out[0] = sk_swift_fixedbuf[0];
    out[1] = sk_swift_fixedbuf[1];
    out[2] = sk_h_00019850().lo;
}

/* FUN_002cd2bc @ 0x002cd2bc   (est. sk_object_method_loop_g)
 * Ghidra: void FUN_002cd2bc(...)
 * See function-local comments for behavior.
 */
void sk_object_method_loop_g(unsigned long p1, unsigned long p2, unsigned long p3,
                              unsigned long p4)
{
    /* Object-iteration loop (variant G): 4-arg form; helper sequence preserved
     * (FUN_00377824 / 00369584 / 0037233c / FUN_0008e500). */
    sk_h_0008e518();
    sk_h_00349720();
    sk_fp_00658c00(0);
    sk_h_003493c4();
    sk_h_0034c2f8();
    sk_fp_00658c00(0);
    sk_h_0034a414();
    sk_fp_00658c00(0);
    sk_h_00349c84();
    sk_fp_00658c00(0);
    sk_h_0034ac50();
    sk_h_00350a64();
    sk_h_003246ec();
    sk_h_00348e18();
    sk_fp_00658c00(0);
    sk_h_003489c0();
    sk_fp_00658c00(0);
    sk_h_0034c074();
    sk_h_0034d414();
    sk_h_003515b4();
    sk_h_003722e4();
    sk_h_00348d4c();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    long base = (long)sk_h_0034b460().lo;
    (void)base;
    sk_h_00353f44();
    sk_h_003510b8();
    int cmp = (int)sk_h_00369584().lo;
    sk_h_00350078();
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_00349134();
    sk_h_00356b38();
    sk_h_0037233c();
    sk_h_0035060c();
    sk_h_00369584();
    sk_h_00350038();
    sk_pair_t a = sk_h_00356a7c(0, 0);
    (void)a;
    sk_h_0014ae44(p4);
    sk_h_0034e66c();
    sk_h_00350aac();
    sk_h_003512c0();
    sk_h_00351ec0();
    sk_h_0035152c();
    sk_h_0034f324();
    unsigned long out = sk_h_003548b8().lo;
    sk_h_0008e500(out, 0);
    (void)cmp;
}

/* FUN_002cd77c @ 0x002cd77c   (est. sk_swift_spin_check)
 * Ghidra: void FUN_002cd77c(...)
 * See function-local comments for behavior.
 */
void sk_swift_spin_check(void)
{
    sk_h_00357cb4();
    sk_h_00355bb8();
    sk_h_003561a0();
    sk_h_00353540();
    unsigned long v = sk_h_003246ec().lo;
    sk_h_0035142c();
    sk_h_00376820(0, v);
    sk_h_0034cf54();
    unsigned long r = sk_h_001a7b08().lo;
    if (r & 1) {
        sk_h_00350278();
        r = sk_h_001a7b08().lo;
    }
    sk_h_00357c74(r & 1, 0);
}

/* FUN_002cd830 @ 0x002cd830   (est. sk_object_method_loop_h)
 * Ghidra: void FUN_002cd830(...)
 * See function-local comments for behavior.
 */
void sk_object_method_loop_h(unsigned long p1, unsigned long p2, unsigned long p3)
{
    /* Object-iteration loop (variant H): 3-arg form; helper sequence preserved
     * (FUN_00369584 comparator / 0037233c / FUN_0008e500). */
    sk_h_0008e518();
    sk_h_00354de8();
    sk_h_0034b7e4();
    sk_fp_00658c00(0);
    sk_h_00352330();
    sk_fp_00658c00(0);
    sk_h_00358308();
    sk_h_0034b7e4();
    sk_fp_00658c00(0);
    sk_h_00350f9c();
    sk_h_00350a34();
    int cmp = (int)sk_h_00369584().lo;
    sk_h_00349b28();
    sk_h_00027614();
    sk_pair_t a = sk_h_00349134();
    sk_h_0037233c(a.lo, a.hi, 0);
    sk_h_00355eb0();
    sk_h_00353f2c();
    sk_h_00357a0c(0, 0);
    sk_h_0031945c(p3);
    sk_h_00350a88();
    sk_h_00351178();
    sk_h_003513a8();
    sk_h_00229a3c(0);
    sk_h_0008e500(0);
    (void)cmp;
}

/* FUN_002cda6c @ 0x002cda6c   (est. sk_swift_hash)
 * Ghidra: void FUN_002cda6c(...)
 * See function-local comments for behavior.
 */
void sk_swift_hash(unsigned long p1, unsigned long p2, unsigned long p3)
{
    /* Hashing step: feeds the buffer key (sk_str_004e7a30) through the hash
     * state machine (FUN_003552f0 / FUN_0034d264) and mixes with FUN_001a8564. */
    sk_h_0034a4a4(p3);
    unsigned char b = (unsigned char)sk_h_003552f0().lo;
    sk_h_0034d264(b, *(unsigned long *)(sk_str_004e7a30 + 16), b ^ (unsigned char)sk_str_004e7a30[0]);
    sk_h_001a8564();
}

/* FUN_002cdaf4 @ 0x002cdaf4   (est. sk_swift_hash_update)
 * Ghidra: void FUN_002cdaf4(...)
 * See function-local comments for behavior.
 */
void sk_swift_hash_update(void)
{
    sk_h_00357cb4();
    sk_h_0034ba88();
    sk_h_003516cc();
    unsigned long v = sk_h_003246ec().lo;
    sk_h_0035142c();
    sk_h_00376820(0, v);
    sk_h_0034d854();
    sk_h_001a7b38();
    sk_h_003509bc();
    sk_h_00351280();
    sk_h_001a7b38();
    sk_h_00357c74(0);
}

/* FUN_002cdb84 @ 0x002cdb84   (est. sk_swift_hash_b)
 * Ghidra: void FUN_002cdb84(...)
 * See function-local comments for behavior.
 */
void sk_swift_hash_b(void)
{
    /* Hashing step (variant, hidden first argument): same as sk_swift_hash. */
    sk_h_0034a4a4(0);
    unsigned char b = (unsigned char)sk_h_003552f0().lo;
    sk_h_0034d264(b, *(unsigned long *)(sk_str_004e7a30 + 16), b ^ (unsigned char)sk_str_004e7a30[0]);
    sk_h_001a8564();
}

/* FUN_002cdc14 @ 0x002cdc14   (est. sk_swift_hash_wrap)
 * Ghidra: void FUN_002cdc14(...)
 * See function-local comments for behavior.
 */
void sk_swift_hash_wrap(unsigned long p1, long p2, unsigned long p3)
{
    sk_h_001a84f4(0);
    sk_swift_hash_update();
    sk_h_001a8564();
    (void)p3;
}

/* FUN_002cdc70 @ 0x002cdc70   (est. sk_swift_hash_set)
 * Ghidra: void FUN_002cdc70(...)
 * See function-local comments for behavior.
 */
void sk_swift_hash_set(unsigned long p1, unsigned long p2, unsigned long p3)
{
    /* Hashed set build: adopts a set buffer (FUN_00350b54), zips the source
     * sequences (sk_swift_sequence_zip / sk_swift_sequence_zip_b), installs the
     * hash closure (FUN_00324704), and finalises via sk_swift_sort_merge. */
    sk_h_00350b54();
    sk_swift_sequence_zip();
    sk_h_0034edc8();
    sk_swift_sequence_zip_b();
    sk_h_003504e8();
    sk_h_003246d4();
    sk_h_003504e8();
    sk_h_003246ec();
    sk_h_00354714();
    sk_h_003513f0(0, 0);
    sk_h_000262fc();
    sk_h_0035122c();
    sk_h_003a25d4();
    sk_h_003a25d4();
    sk_h_00350500();
    sk_h_00310d34();
    sk_h_00348718();
    sk_pair_t a = sk_h_00376820(0, 0);
    sk_h_00350968(0, a.hi, p3, a.lo);
    sk_swift_sort_merge(0,0,0,0);
}

/* FUN_002cdd7c @ 0x002cdd7c   (est. sk_swift_sequence_zip)
 * Ghidra: void FUN_002cdd7c(...)
 * See function-local comments for behavior.
 */
void sk_swift_sequence_zip(void)
{
    /* Sequence zip: iterates two sequences of min length (FUN_00355bb8),
     * reading both current slots (sk_object_read_slot via sk_object_read_slot /
     * sk_object_call_slot), pairing them with the sentinel marker, and emitting the
     * zipped buffer through the result object (extraout_x8_03 frame).  The loop
     * advances per element and traps on count overflow. */
    sk_h_0008e518();
    sk_h_00355bb8();
    sk_h_00359de8();
    sk_h_0034b07c();
    sk_fp_00658c00(0);
    sk_h_00348f38();
    sk_h_00350a64();
    sk_h_003246ec();
    sk_h_00348d7c();
    sk_fp_00658c00(0);
    sk_h_00348a18();
    sk_fp_00658c00(0);
    sk_h_0034bc58();
    sk_h_00349b28();
    sk_h_00002534();
    sk_h_00351450();
    sk_h_001ee140();
    long n = 0;
    /* iterate both sequences */
    sk_h_003509b0(0);
    sk_h_0019ea20();
    sk_h_0035a31c();
    sk_h_00351f88();
    sk_h_003531cc();
    sk_object_call_slot();
    sk_h_00351280(0);
    sk_h_001ef804();
    sk_h_0035976c();
    sk_h_0035aa2c();
    sk_h_000a6e14(0);
    sk_h_003596a4();
    sk_h_0034e6fc();
    sk_h_0031a29c();
    sk_h_0035a9dc();
    n += 1;
    sk_h_00357a18();
    sk_fp_00658c00(0);
    sk_h_00358258();
    sk_h_0036b270(0);
    sk_h_00350bb4(0);
    sk_h_0035aa04();
    sk_h_0035310c();
    sk_h_003a25d4();
    unsigned long out = sk_h_00353100().lo;
    sk_h_0008e500(out, 0);
}

/* FUN_002cdfd0 @ 0x002cdfd0   (est. sk_swift_sequence_zip_b)
 * Ghidra: void FUN_002cdfd0(...)
 * See function-local comments for behavior.
 */
void sk_swift_sequence_zip_b(void)
{
    /* Sequence zip (variant B): same pairing loop as sk_swift_sequence_zip but
     * reading the source from the return of FUN_00355bb8 directly. */
    sk_h_0008e518();
    sk_pair_t a = sk_h_00355bb8();
    (void)a;
    sk_h_0034b07c();
    sk_fp_00658c00(0);
    sk_h_00348f38();
    sk_h_00350a64();
    sk_h_003246ec();
    sk_h_00348d7c();
    sk_fp_00658c00(0);
    sk_h_00348a18();
    sk_fp_00658c00(0);
    sk_h_0034bc58();
    sk_h_00349b28();
    sk_h_00002534();
    sk_h_00351450();
    sk_h_001ee140();
    sk_h_003509b0(0);
    sk_h_0019ea20();
    sk_h_0035a31c();
    sk_h_00351f88();
    sk_h_003531cc();
    sk_object_call_slot();
    sk_h_00351280(0);
    sk_h_001ef804();
    sk_h_0035976c();
    sk_h_0035aa2c();
    sk_h_000a6e14(0);
    sk_h_003596a4();
    sk_h_0034e6fc();
    sk_h_0031a29c();
    sk_h_0035a9dc();
    sk_h_00357a18();
    sk_fp_00658c00(0);
    sk_h_00358258();
    sk_h_0036b270(0);
    sk_h_00350bb4(0);
    sk_h_0035aa04();
    sk_h_0035310c();
    sk_h_003a25d4();
    unsigned long out = sk_h_00353100().lo;
    sk_h_0008e500(out, 0);
}

/* FUN_002ce228 @ 0x002ce228   (est. sk_object_method_loop_i)
 * Ghidra: void FUN_002ce228(...)
 * See function-local comments for behavior.
 */
void sk_object_method_loop_i(void)
{
    /* Object-iteration loop (variant I): reads the current slot (via the x16+8
     * method-table slot), classifies with the comparator (FUN_00369584), and
     * on the selected path re-emits through FUN_00369340. */
    unsigned long v = sk_h_0008e518().lo;
    sk_h_00349a68();
    sk_fp_00658c00(0);
    sk_h_003489c0();
    sk_fp_00658c00(0);
    sk_h_0034b4c0();
    sk_h_003516cc();
    sk_h_003246ec();
    sk_h_000a6f88();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034aee4();
    sk_h_00350968(0);
    sk_h_00351f88();
    int cmp = (int)sk_h_00369584().lo;
    sk_h_00349b28();
    sk_h_00027614();
    sk_h_00349800();
    sk_h_00353cc0();
    long base = (long)sk_h_0037233c().lo;
    (void)base;
    sk_h_00353cc0(0);
    sk_h_003578e4();
    sk_h_003509b0(0);
    sk_h_00355fd0();
    sk_h_00352864();
    sk_h_003512c0();
    sk_h_00357aec(0, 0);
    sk_h_00350944(0);
    sk_h_003514a0();
    sk_h_00351e6c();
    sk_h_00351a98();
    sk_pair_t z = sk_h_003512c0();
    sk_h_00369340(z.lo, z.hi, (unsigned long)(cmp != 1));
    sk_h_0008e500(0);
    (void)v;
}

/* FUN_002ce480 @ 0x002ce480   (est. sk_swift_buf_capacity_clamp)
 * Ghidra: ulong FUN_002ce480(...)
 * See function-local comments for behavior.
 */
unsigned long sk_swift_buf_capacity_clamp(void)
{
    /* Returns the buffer capacity, clamped to the 0..4 range used by the
     * small fixed buffers. */
    sk_h_00356c6c();
    unsigned long cap = sk_h_002ad78c(0x678bd0).lo;
    sk_h_00351d18();
    sk_h_003a25d4();
    if (cap > 3) cap = 4;
    return cap;
}

/* FUN_002ce4c8 @ 0x002ce4c8   (est. sk_swift_collection_label)
 * Ghidra: undefined1 [16] FUN_002ce4c8(...)
 * See function-local comments for behavior.
 */
sk_pair_t sk_swift_collection_label(unsigned char which)
{
    /* Selects the descriptive label string for a collection view:
     * "offset" (0), "element" (1), "Element" metadata (2), "isReverse" (3). */
    sk_pair_t r;
    switch (which) {
    case 1:
        r.lo = 0x746e656d656c65; r.hi = 0xe700000000000000; return r;
    case 2:
        r.lo = 0xd000000000000010; r.hi = 0x80000000005d2f50; return r;
    case 3:
        r.lo = 0x65766f6d65527369; r.hi = 0xe800000000000000; return r;
    default:
        r.lo = 0x74657366666f; r.hi = 0xe600000000000000; return r;
    }
}

/* FUN_002ce590 @ 0x002ce590   (est. sk_swift_label_wrap_a)
 * Ghidra: void FUN_002ce590(...)
 * See function-local comments for behavior.
 */
void sk_swift_label_wrap_a(void)
{
    sk_h_0035237c();
    sk_swift_buf_capacity_clamp();
    sk_h_00357044();
}

/* FUN_002ce5b8 @ 0x002ce5b8   (est. sk_swift_label_wrap_b)
 * Ghidra: void FUN_002ce5b8(...)
 * See function-local comments for behavior.
 */
void sk_swift_label_wrap_b(sk_pair_t *out)
{
    sk_pair_t a = sk_swift_collection_label((unsigned char)sk_swift_fixedbuf[0]);
    *out = a;
}

/* FUN_002ce5ec @ 0x002ce5ec   (est. sk_swift_label_wrap_c)
 * Ghidra: void FUN_002ce5ec(...)
 * See function-local comments for behavior.
 */
void sk_swift_label_wrap_c(void)
{
    sk_swift_buf_capacity_clamp();
    sk_h_00357044();
}

/* FUN_002ce64c @ 0x002ce64c   (est. sk_object_describe)
 * Ghidra: void FUN_002ce64c(...)
 * See function-local comments for behavior.
 */
void sk_object_describe(unsigned long p1, unsigned long p2, unsigned long p3,
                            unsigned long p4)
{
    /* Object describe/append to a string: builds the description by acquiring
     * the object (FUN_00377824), appending its error/type info through the
     * method-table slot (+0x80 / +0x60), writing the message fields into the
     * result buffer (unaff_x27), and re-emitting via FUN_00369340. */
    sk_h_00353cfc();
    sk_h_00356334();
    sk_h_00349b3c();
    sk_fp_00658c00(0);
    sk_h_00348f38();
    sk_h_003246ec(0);
    sk_h_00348d7c();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b0d4();
    sk_h_003511a8();
    sk_h_000dbcc8();
    sk_pair_t a = sk_h_003504e8();
    sk_h_00324734(a.lo, a.hi, p3, p4);
    sk_h_0006a668(0);
    sk_h_00354870();
    sk_h_0034edc8();
    sk_h_0034fb28();
    sk_h_00352c74();
    sk_h_0034c094(0);
    sk_h_0034a618();
    sk_h_0034c9c8();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_h_0007c198();
    sk_h_0035a200();
    sk_h_00353c60(0, 0);
    sk_h_00354ca8();
    sk_h_00349b28();
    sk_h_00002534();
    sk_h_00324764(0x6562a0, 0x66b358, 0);
    sk_h_0035a200();
    sk_h_00352e78(0, 0, 0);
    sk_h_0036b118(0);
    sk_h_00349800();
    sk_h_00352998();
    sk_h_0037233c();
    sk_h_00355eb0();
    sk_h_00351ba0(0);
    sk_h_00369340(0, 0, 0);
    sk_h_00350bb4(0, 0);
    sk_h_000026e8();
    sk_h_00353d14(0);
}

/* FUN_002ce9bc @ 0x002ce9bc   (est. sk_object_debug_desc)
 * Ghidra: void FUN_002ce9bc(...)
 * See function-local comments for behavior.
 */
void sk_object_debug_desc(unsigned long p1, unsigned long p2, unsigned long p3,
                          unsigned long p4)
{
    /* Object debugDescription: builds the debug description string via
     * FUN_00324734 / FUN_0032474c and the element-read helpers
     * (sk_object_read_slot / sk_object_call_slot), appending "count" and element
     * fields, then releases the temporary buffer. */
    sk_h_00353cfc();
    sk_h_00351cf4();
    sk_h_0034998c();
    sk_fp_00658c00(0);
    sk_h_003497b4();
    long base = (long)sk_h_00352128().lo;
    sk_h_000dbcc8(base, *(unsigned long *)(base + 0x18));
    sk_h_0034d3f4();
    sk_h_00324734();
    sk_h_0006a4f0(0);
    sk_h_00354870();
    sk_h_00353504(0, 0, 0);
    unsigned long cmp = (unsigned long)sk_object_compare();
    sk_pair_t a = sk_h_00350488();
    sk_h_0032474c(a.lo, a.hi, 0);
    sk_h_001bd768(cmp & 1, 0, 0);
    sk_object_read_slot();
    sk_h_001bd858(0, 0, 0);
    sk_h_0035481c();
    sk_object_call_slot();
    sk_h_00351238(0, 0);
    sk_h_001bdb28();
    sk_h_000e72b0(0);
    sk_object_read_pair();
    sk_h_00349b28();
    sk_h_00002534();
    sk_h_00324764(0x6562a8, 0x66b350, 0);
    sk_h_00350a1c(0, 0);
    sk_h_001bdb28();
    sk_h_0036b118(0);
    sk_h_00353e7c();
    sk_h_00353d14(0);
    (void)p1; (void)p2; (void)p3; (void)p4;
}

/* FUN_002cebf0 @ 0x002cebf0   (est. sk_swift_elem_count_check)
 * Ghidra: undefined4 FUN_002cebf0(...)
 * See function-local comments for behavior.
 */
unsigned int sk_swift_elem_count_check(void)
{
    /* Returns the element count discriminant: 0 for empty, 1 for single, 2 for
     * many. */
    sk_h_00356c6c();
    unsigned int n = (unsigned int)sk_h_002ad78c(0x678c50).lo;
    sk_h_00351d18();
    sk_h_003a25d4();
    unsigned int t = (n != 1) ? 2 : 1;
    return (n != 0) ? t : 0;
}

/* FUN_002cec40 @ 0x002cec40   (est. sk_swift_optional_label)
 * Ghidra: undefined1 [16] FUN_002cec40(...)
 * See function-local comments for behavior.
 */
sk_pair_t sk_swift_optional_label(void)
{
    /* Selects the optional-description label based on the presence flag
     * returned by FUN_003594f4. */
    sk_pair_t r;
    unsigned long f = sk_h_003594f4().lo;
    if (f != 0) {
        r.lo = 0x736c61766f6d6572; r.hi = 0xe800000000000000;
    } else {
        r.lo = 0x6f69747265736e69; r.hi = 0xea0000000000736e;
    }
    return r;
}

/* FUN_002cec8c @ 0x002cec8c   (est. sk_swift_debug_wrap_a)
 * Ghidra: void FUN_002cec8c(...)
 * See function-local comments for behavior.
 */
void sk_swift_debug_wrap_a(unsigned long p1, unsigned long p2, unsigned long p3)
{
    sk_object_debug_desc(p1, p2, *(unsigned long *)((p3 & 0xfffffffffffffffe) - 8),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 0x10));
}

/* FUN_002cec90 @ 0x002cec90   (est. sk_swift_debug_wrap_b)
 * Ghidra: void FUN_002cec90(...)
 * See function-local comments for behavior.
 */
void sk_swift_debug_wrap_b(unsigned long p1, unsigned long p2, unsigned long p3)
{
    sk_object_debug_desc(p1, p2, *(unsigned long *)((p3 & 0xfffffffffffffffe) - 8),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 0x10));
}

/* FUN_002cecac @ 0x002cecac   (est. sk_swift_describe_wrap_a)
 * Ghidra: void FUN_002cecac(...)
 * See function-local comments for behavior.
 */
void sk_swift_describe_wrap_a(unsigned long p1, long p2, unsigned long p3)
{
    sk_object_describe(p1, *(unsigned long *)(p2 + 0x10),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 8),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 0x10));
}

/* FUN_002cecb0 @ 0x002cecb0   (est. sk_swift_describe_wrap_b)
 * Ghidra: void FUN_002cecb0(...)
 * See function-local comments for behavior.
 */
void sk_swift_describe_wrap_b(unsigned long p1, long p2, unsigned long p3)
{
    sk_object_describe(p1, *(unsigned long *)(p2 + 0x10),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 8),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 0x10));
}

/* FUN_002cecfc @ 0x002cecfc   (est. sk_swift_elem_wrap_a)
 * Ghidra: void FUN_002cecfc(...)
 * See function-local comments for behavior.
 */
void sk_swift_elem_wrap_a(void)
{
    sk_h_0035237c();
    sk_swift_elem_count_check();
    sk_h_00357044();
}

/* FUN_002ced24 @ 0x002ced24   (est. sk_swift_elem_wrap_b)
 * Ghidra: void FUN_002ced24(...)
 * See function-local comments for behavior.
 */
void sk_swift_elem_wrap_b(sk_pair_t *out)
{
    sk_pair_t a = sk_swift_optional_label();
    *out = a;
}

/* FUN_002ced58 @ 0x002ced58   (est. sk_swift_elem_wrap_c)
 * Ghidra: void FUN_002ced58(...)
 * See function-local comments for behavior.
 */
void sk_swift_elem_wrap_c(void)
{
    sk_swift_elem_count_check();
    sk_h_00357044();
}

/* FUN_002cedb8 @ 0x002cedb8   (est. sk_swift_collection_description)
 * Ghidra: void FUN_002cedb8(...)
 * See function-local comments for behavior.
 */
sk_pair_t sk_swift_collection_description(unsigned long p1, unsigned long p2,
                                          unsigned long p3, unsigned long p4)
{
    /* Collection description builder: acquires the object (FUN_00352758),
     * appends the description fields through the method-table slot (+0xe0) and
     * the element buffer, then stores the resulting "description" string into
     * the caller buffer (unaff_x22) and re-emits via FUN_00358490. */
    sk_h_00353cfc();
    sk_h_003545ac();
    long p = (long)sk_h_00352758().lo;
    sk_h_000dbcc8(p, *(unsigned long *)(p + 0x18));
    sk_h_00350488();
    sk_h_003516d8();
    sk_h_003247bc();
    sk_h_0006a668(*(unsigned long *)(p + 0x20));
    sk_h_00354888();
    sk_h_00353504(0, 0, 0);
    sk_h_00351930();
    sk_h_003246ec();
    sk_h_0034ee68();
    sk_h_00310d34();
    sk_h_00376820(0);
    sk_h_00376820(0, 0, 0);
    sk_h_000027e8();
    sk_h_0036b118(0);
    sk_h_0034921c();
    sk_h_001a2128(0, 0, 0);
    sk_h_00002534(0x6562b0, 0);
    sk_h_00354690();
    sk_h_00376820(0, 0);
    sk_h_00352c4c(0, 0);
    sk_h_00270d80();
    sk_fp_00658c00(0);
    sk_h_00358288();
    sk_h_00310df0(0, 0);
    sk_h_00352840(0);
    unsigned long r = sk_h_00286e40().lo;
    sk_h_0036b118(0);
    if (r & 1) {
        sk_h_0034f8bc();
        sk_pair_t a = sk_h_00002534();
        sk_h_003489a8(a.lo, a.hi, a.lo);
        sk_h_00270d80(0, 0, 0);
        sk_fp_00658c00(0);
        sk_h_003539e4();
        unsigned long r2 = sk_h_00286e40(0, 0, 0, 0x66aec8).lo;
        sk_h_0036b118(0);
        if (r2 & 1) {
            unsigned long u = sk_h_00348718().lo;
            u = sk_h_00376820(u, 0).lo;
            sk_h_00350220(0);
            unsigned long r3 = sk_swift_sort_partition(0,0,0,0).lo;
            if (r3 & 1) {
                sk_swift_sort_merge(0, 0, 0, u);
                sk_h_0034eb54();
                sk_h_000026e8();
                goto out;
            }
        }
    }
    sk_h_00348730();
    sk_h_00351f28();
    sk_h_0035072c();
    sk_h_0034f1a8();
    sk_h_0017e880();
    sk_h_0034bccc();
    sk_h_0036986c();
    sk_h_0036b118(0);
out:
    sk_h_000026e8();
    sk_h_00350af4();
    sk_pair_t z = sk_h_00358490();
    sk_h_00353d14(z.lo, z.hi, 0);
    (void)p1; (void)p2; (void)p3; (void)p4;
    return z;
}

/* FUN_002cf1e4 @ 0x002cf1e4   (est. sk_object_error)
 * Ghidra: void FUN_002cf1e4(...)
 * See function-local comments for behavior.
 */
void sk_object_error(long p1, unsigned long p2, unsigned long p3, unsigned long p4,
                        unsigned long p5, unsigned long p6)
{
    /* Object error-reporting entry: acquires the error object (FUN_003247bc),
     * composes the "Error.localizedDescription" string via the message fields
     * (FUN_00376820 / FUN_00351aec / FUN_001bdb28), and releases the temporary
     * buffer. */
    unsigned long v2 = *(unsigned long *)(p1 + 0x18);
    unsigned long v3 = *(unsigned long *)(p1 + 0x20);
    sk_h_000dbcc8(p1, v2);
    sk_h_00350720();
    sk_h_00351f40();
    unsigned long u = sk_h_003247bc().lo;
    sk_h_0006a4f0(v3);
    sk_h_00354888();
    sk_h_0034f604();
    sk_h_0032474c();
    sk_h_00352720();
    sk_h_003246ec();
    sk_h_0034da88();
    sk_h_00310d34();
    sk_h_00376820(0, u, 0);
    sk_h_00376820(0, 0, 0);
    sk_h_00351aec(0, 0);
    sk_h_001bdb28();
    sk_h_00351aec(0, 0);
    sk_h_001bdb28();
    sk_h_0036b118(u);
    (void)v2;
}

/* FUN_002cf360 @ 0x002cf360   (est. sk_swift_error_wrap_a)
 * Ghidra: void FUN_002cf360(...)
 * See function-local comments for behavior.
 */
void sk_swift_error_wrap_a(unsigned long p1, long p2, unsigned long p3)
{
    sk_object_error(p1, sk_swift_fixedbuf[0], sk_swift_fixedbuf[1],
                  *(unsigned long *)(p2 + 0x10),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 8),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 0x10));
}

/* FUN_002cf364 @ 0x002cf364   (est. sk_swift_error_wrap_b)
 * Ghidra: void FUN_002cf364(...)
 * See function-local comments for behavior.
 */
void sk_swift_error_wrap_b(unsigned long p1, long p2, unsigned long p3)
{
    sk_object_error(p1, sk_swift_fixedbuf[0], sk_swift_fixedbuf[1],
                  *(unsigned long *)(p2 + 0x10),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 8),
                  *(unsigned long *)((p3 & 0xfffffffffffffffe) - 0x10));
}

/* FUN_002cf38c @ 0x002cf38c   (est. sk_swift_error_wrap_c)
 * Ghidra: void FUN_002cf38c(...)
 * See function-local comments for behavior.
 */
void sk_swift_error_wrap_c(sk_pair_t *out, unsigned long p2, long p3, unsigned long p4)
{
    sk_pair_t a = sk_swift_collection_description(p2, *(unsigned long *)(p3 + 0x10),
                                *(unsigned long *)((p4 & 0xfffffffffffffffe) - 8),
                                *(unsigned long *)((p4 & 0xfffffffffffffffe) - 0x10));
    *out = a;
}

/* FUN_002cf494 @ 0x002cf494   (est. sk_object_dispatch_c)
 * Ghidra: void FUN_002cf494(...)
 * See function-local comments for behavior.
 */
void sk_object_dispatch_c(void)
{
    /* Object method dispatch (jumptable variant): enters the object-service
     * prologue and performs an indirect call through the method table (+0x28). */
    sk_h_003503d0();
    sk_h_0034c3f4(0);
    sk_h_000839d8();
    sk_h_003504e8();
    sk_h_00310d68();
    sk_h_00350404();
    /* indirect jump via table (too many branches, unrecoverable) */
    __builtin_trap();
}

/* FUN_002cf55c @ 0x002cf55c   (est. sk_swift_count_zero)
 * Ghidra: undefined8 FUN_002cf55c(...)
 * See function-local comments for behavior.
 */
unsigned long sk_swift_count_zero(long n)
{
    if (n == 0) return 1;
    sk_h_0035047c();
    sk_h_003486b8(0x67);
    sk_h_0034975c();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    return 0;
}

/* FUN_002cf598 @ 0x002cf598   (est. sk_swift_count_one)
 * Ghidra: undefined8 FUN_002cf598(...)
 * See function-local comments for behavior.
 */
unsigned long sk_swift_count_one(long n)
{
    if (n == 1) return 0;
    sk_h_0035047c();
    sk_h_003486b8(0x71);
    sk_h_0034975c();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    return 0;
}

/* FUN_002cf5d8 @ 0x002cf5d8   (est. sk_object_call_c)
 * Ghidra: void FUN_002cf5d8(...)
 * See function-local comments for behavior.
 */
void sk_object_call_c(unsigned long p1)
{
    sk_h_00350530();
    sk_h_0034d464();
    sk_h_0007c1a4();
    sk_fp_00658c00(0);
    sk_h_0034b460();
    sk_h_0034b3c8();
    sk_h_0034befc();
    sk_h_000839d8();
    sk_h_00100efc(p1);
    sk_object_dispatch_c();
}

/* FUN_002cf670 @ 0x002cf670   (est. sk_swift_collectionofone_peek)
 * Ghidra: code * FUN_002cf670(...)
 * See function-local comments for behavior.
 */
void *sk_swift_collectionofone_peek(unsigned long p1, long n)
{
    if (n == 0) return (void *)sk_h_0001a1c8().lo;
    sk_h_00348638(1);
    sk_h_00349de8();
    sk_fatal_error(0xb, 2, sk_str_indexoob_005cdab0, 0x13, 2, sk_str_collectionofone_005d0d40,
                   0x1b, 2, 0x88, 1);
    return 0;
}

/* FUN_002cf6cc @ 0x002cf6cc   (est. sk_swift_collectionofone_peek_b)
 * Ghidra: code * FUN_002cf6cc(...)
 * See function-local comments for behavior.
 */
void *sk_swift_collectionofone_peek_b(unsigned long p1, long n)
{
    if (n == 0) return (void *)sk_h_0001a1c8().lo;
    sk_h_00348638(1);
    sk_h_00349de8();
    sk_fatal_error(0xb, 2, sk_str_indexoob_005cdab0, 0x13, 2, sk_str_collectionofone_005d0d40,
                   0x1b, 2, 0x88, 1);
    return 0;
}

/* FUN_002cf728 @ 0x002cf728   (est. sk_swift_collectionofone_call)
 * Ghidra: void FUN_002cf728(...)
 * See function-local comments for behavior.
 */
void sk_swift_collectionofone_call(unsigned long p1, long n, long p3)
{
    if (n == 0) {
        (*(void (**)(unsigned long))(*(long *)(*(long *)(p3 + 0x10) - 8) + 0x10))(p1);
        return;
    }
    sk_h_00348638(1);
    sk_h_00349de8();
    sk_fatal_error(0xb, 2, sk_str_indexoob_005cdab0, 0x13, 2, sk_str_collectionofone_005d0d40,
                   0x1b, 2, 0x88, 1);
    __builtin_trap();
}

/* FUN_002cf794 @ 0x002cf794   (est. sk_swift_collectionofone_call_b)
 * Ghidra: void FUN_002cf794(...)
 * See function-local comments for behavior.
 */
void sk_swift_collectionofone_call_b(unsigned long p1, long n, long p3)
{
    if (n == 0) {
        (*(void (**)(void))(*(long *)(*(long *)(p3 + 0x10) - 8) + 0x28))();
        return;
    }
    sk_h_00348638(1);
    sk_h_00349de8();
    sk_fatal_error(0xb, 2, sk_str_indexoob_005cdab0, 0x13, 2, sk_str_collectionofone_005d0d40,
                   0x1b, 2, 0x88, 1);
    __builtin_trap();
}

/* FUN_002cf804 @ 0x002cf804   (est. sk_swift_copy_into)
 * Ghidra: void FUN_002cf804(...)
 * See function-local comments for behavior.
 */
void sk_swift_copy_into(unsigned long p1, unsigned long p2, unsigned long p3, unsigned long p4)
{
    sk_h_00084220();
    sk_h_00349ef4();
    sk_h_00349720();
    sk_fp_00658c00(0);
    sk_h_00348f50();
    sk_h_00349204();
    sk_h_00376820(0, p3);
    sk_h_00351444(0, 0);
    sk_h_001d2f94();
    sk_h_0034e56c(0);
    sk_h_00352dd0(0, 0);
    sk_h_00351444();
    sk_h_001d3fd0();
    sk_h_00084234(0);
    (void)p1; (void)p2; (void)p4;
}

/* FUN_002cf8d0 @ 0x002cf8d0   (est. sk_swift_range_equal)
 * Ghidra: void FUN_002cf8d0(...)
 * See function-local comments for behavior.
 */
void sk_swift_range_equal(unsigned long p1, unsigned long p2, unsigned long p3,
                            unsigned long p4)
{
    sk_pair_t a = sk_h_00351a14();
    sk_h_00349204();
    sk_h_00376820(0, p4);
    sk_h_003511cc(0, 0);
    sk_h_001d2f94();
    sk_h_0034d1b0();
    unsigned long u = sk_h_0031b080().lo;
    sk_h_0034878c();
    long d = (long)sk_h_0019c9cc().lo;
    long lo = 0, hi = 0;
    if (hi - lo == d) {
        if (d == 1) {
            sk_h_0034b3c8();
            sk_h_0028c754(u);
        }
        sk_h_0034b804();
        return;
    }
    sk_h_003488bc(1);
    sk_h_0034a96c();
    sk_fatal_error(0xb, 2, "", 0, 2, "Swift", 5, 2, 0, 1);
    __builtin_trap();
    (void)a; (void)p1; (void)p2; (void)p3;
}

/* FUN_002cfab8 @ 0x002cfab8   (est. sk_object_release_wrap)
 * Ghidra: void FUN_002cfab8(...)
 * See function-local comments for behavior.
 */
void sk_object_release_wrap(void)
{
    sk_pair_t a = sk_h_0008e518();
    unsigned long *p = (unsigned long *)*((unsigned long *)a.lo);
    unsigned long u1 = p[6], u2 = p[7];
    if ((a.hi & 1) == 0) {
        sk_swift_range_equal(u2, p[0], p[1], p[2]);
    } else {
        long l = (long)p[5];
        sk_h_00351d0c();
        sk_h_0034d3d4();
        sk_h_00350e84(u1);
        sk_swift_range_equal(0,0,0,0);
        sk_h_000e15d8(*(unsigned long *)(l + 8));
    }
    sk_h_00012568(u2);
    sk_h_00012568(u1);
    sk_h_0008e500(p, 0);
    sk_h_00012568();
}

/* FUN_002cfb5c @ 0x002cfb5c   (est. sk_swift_collectionofone_trap)
 * Ghidra: void FUN_002cfb5c(...)
 * See function-local comments for behavior.
 */
void sk_swift_collectionofone_trap(unsigned long p1, long *idx, long p3)
{
    if (*idx == 0) {
        (*(void (**)(void))(*(long *)(*(long *)(p3 + 0x10) - 8) + 0x28))();
        return;
    }
    sk_fatal_error(0xb, 2, sk_str_index_005cd940, 0x12, 2, sk_str_collectionofone_005d0d40,
                   0x1b, 2, 0x88, 1);
    __builtin_trap();
}

/* FUN_002cfbf8 @ 0x002cfbf8   (est. sk_swift_collectionofone_make)
 * Ghidra: undefined * FUN_002cfbf8(...)
 * See function-local comments for behavior.
 */
void *sk_swift_collectionofone_make(long *out, unsigned long *src)
{
    long p = (long)sk_h_0036a908(0x28, 0xe285).lo;
    *out = p;
    unsigned long u = (unsigned long)sk_swift_collectionofone_peek_b(p, *src);
    *(unsigned long *)(p + 0x20) = u;
    return (void *)sk_td_003471a0;
}

/* FUN_002cfc5c @ 0x002cfc5c   (est. sk_swift_collectionofone_dtor)
 * Ghidra: void FUN_002cfc5c(...)
 * See function-local comments for behavior.
 */
void sk_swift_collectionofone_dtor(long *self)
{
    long p = *self;
    (*(void (**)(long))(p + 0x20))(p);
    sk_h_00012568(p);
}

/* FUN_002cfca8 @ 0x002cfca8   (est. sk_swift_emptycollection_make)
 * Ghidra: undefined1 [16] FUN_002cfca8(...)
 * See function-local comments for behavior.
 */
sk_pair_t sk_swift_emptycollection_make(long *out, unsigned long *src, unsigned long p3)
{
    sk_pair_t r;
    unsigned long *buf = (unsigned long *)sk_h_0036a908(0x40, 0xc49).lo;
    *out = (long)buf;
    buf[0] = sk_swift_fixedbuf[0];
    buf[1] = p3;
    unsigned long u = sk_h_00376820(0, p3).lo;
    long b = (long)sk_h_0031b080(0, p3, u).lo;
    buf[2] = b;
    long meta = *(long *)(b - 8);
    buf[3] = meta;
    unsigned long sz = *(unsigned long *)(meta + 0x40);
    buf[4] = (unsigned long)sk_h_0036a908(sz, 0xc49).lo;
    buf[5] = (unsigned long)sk_h_0036a908(sz, 0xc49).lo;
    buf[6] = src[0];
    buf[7] = src[1];
    sk_swift_copy_into(buf[4], src[0], src[1], p3);
    r.lo = (unsigned long)sk_object_release_wrap2;
    r.hi = buf[4];
    return r;
}

/* FUN_002cfda8 @ 0x002cfda8   (est. sk_object_release_wrap2)
 * Ghidra: void FUN_002cfda8(...)
 * See function-local comments for behavior.
 */
void sk_object_release_wrap2(void)
{
    sk_pair_t a = sk_h_0008e518();
    long p = (long)*((unsigned long *)a.lo);
    unsigned long u1 = *(unsigned long *)(p + 0x20);
    unsigned long u2 = *(unsigned long *)(p + 0x28);
    if ((a.hi & 1) == 0) {
        sk_h_0034d868();
        sk_swift_range_equal(0,0,0,0);
    } else {
        unsigned long v = *(unsigned long *)(p + 0x10);
        long m = *(long *)(p + 0x18);
        sk_pair_t q = sk_h_0034e4a4(m);
        (void)q;
        sk_h_0008e388();
        sk_h_00353a6c();
        sk_swift_range_equal(0,0,0,0);
        sk_h_0009e234(*(unsigned long *)(m + 8));
        (void)v;
    }
    sk_h_00012568(u2);
    sk_h_00012568(u1);
    sk_h_0008e500(p, 0);
    sk_h_00012568();
}

/* FUN_002cfe4c @ 0x002cfe4c   (est. sk_swift_append)
 * Ghidra: void FUN_002cfe4c(...)
 * See function-local comments for behavior.
 */
void sk_swift_append(unsigned long p1, unsigned long p2, unsigned long p3,
                        unsigned long p4, unsigned long p5)
{
    unsigned long u = sk_h_00376820(0, p4).lo;
    sk_h_0019f1ec(p1, p2, p3, p4, u, p5);
}

/* FUN_002cfecc @ 0x002cfecc   (est. sk_swift_count_one_pop_a)
 * Ghidra: void FUN_002cfecc(...)
 * See function-local comments for behavior.
 */
void sk_swift_count_one_pop_a(unsigned long *out, unsigned long *src)
{
    sk_swift_count_one(*src);
    *out = 0;
}

/* FUN_002cfef8 @ 0x002cfef8   (est. sk_swift_count_one_pop_b)
 * Ghidra: void FUN_002cfef8(...)
 * See function-local comments for behavior.
 */
void sk_swift_count_one_pop_b(unsigned long *src)
{
    sk_swift_count_one(*src);
    *src = 0;
}

/* FUN_002cff24 @ 0x002cff24   (est. sk_swift_insert_a)
 * Ghidra: void FUN_002cff24(...)
 * See function-local comments for behavior.
 */
void sk_swift_insert_a(unsigned long p1, unsigned long p2, unsigned long p3)
{
    sk_h_00349ef4();
    unsigned long u = sk_h_0034b550().lo;
    sk_h_00376820(u, p3);
    sk_h_003486fc();
    sk_h_0034b128();
    sk_h_001e664c();
}

/* FUN_002cff6c @ 0x002cff6c   (est. sk_swift_insert_b)
 * Ghidra: void FUN_002cff6c(...)
 * See function-local comments for behavior.
 */
void sk_swift_insert_b(void)
{
    sk_h_00349944();
    unsigned long u = sk_h_0034b550().lo;
    sk_h_00376820(u, 0);
    sk_h_003498a8();
    sk_h_001e3a28();
}

/* FUN_002cffb0 @ 0x002cffb0   (est. sk_swift_insert_c)
 * Ghidra: void FUN_002cffb0(...)
 * See function-local comments for behavior.
 */
void sk_swift_insert_c(unsigned long p1, unsigned long p2, unsigned long p3)
{
    sk_h_000867ec();
    unsigned long u = sk_h_0034b550().lo;
    sk_h_00376820(u, p3);
    sk_h_003486fc();
    sk_h_0034b778();
    sk_h_001e6be8();
}

/* FUN_002cfff0 @ 0x002cfff0   (est. sk_swift_collection_make)
 * Ghidra: undefined * FUN_002cfff0(...)
 * See function-local comments for behavior.
 */
void *sk_swift_collection_make(long *out, unsigned long *src)
{
    long p = (long)sk_h_0036a908(0x28, 0x8e5d).lo;
    *out = p;
    unsigned long u = (unsigned long)sk_swift_collectionofone_peek(p, *src);
    *(unsigned long *)(p + 0x20) = u;
    return (void *)sk_td_003471a4;
}

/* FUN_002d0064 @ 0x002d0064   (est. sk_swift_append_b)
 * Ghidra: void FUN_002d0064(...)
 * See function-local comments for behavior.
 */
void sk_swift_append_b(unsigned long p1, unsigned long p2)
{
    unsigned long u = sk_h_00376820(0, p2).lo;
    sk_h_0019fa60(p1, p2, u, 0x6720e8);
}

/* FUN_002d00d0 @ 0x002d00d0   (est. sk_swift_count_zero_pop_a)
 * Ghidra: void FUN_002d00d0(...)
 * See function-local comments for behavior.
 */
void sk_swift_count_zero_pop_a(unsigned long *out, unsigned long *src)
{
    sk_swift_count_zero(*src);
    *out = 1;
}

/* FUN_002d0100 @ 0x002d0100   (est. sk_swift_count_zero_pop_b)
 * Ghidra: void FUN_002d0100(...)
 * See function-local comments for behavior.
 */
void sk_swift_count_zero_pop_b(unsigned long *src)
{
    sk_swift_count_zero(*src);
    *src = 1;
}

/* FUN_002d0134 @ 0x002d0134   (est. sk_swift_append_c)
 * Ghidra: void FUN_002d0134(...)
 * See function-local comments for behavior.
 */
void sk_swift_append_c(unsigned long p1)
{
    unsigned long u = sk_h_00376820(0, p1).lo;
    sk_h_001a0194(p1, u);
}

/* FUN_002d017c @ 0x002d017c   (est. sk_swift_append_d)
 * Ghidra: void FUN_002d017c(...)
 * See function-local comments for behavior.
 */
void sk_swift_append_d(unsigned long p1)
{
    unsigned long u = sk_h_00376820(0, p1).lo;
    sk_h_001e088c(p1, u);
}

/* FUN_002d01c4 @ 0x002d01c4   (est. sk_swift_pointer_unwrap)
 * Ghidra: void FUN_002d01c4(...)
 * See function-local comments for behavior.
 */
void sk_swift_pointer_unwrap(void)
{
    sk_pair_t a = sk_h_0008e518();
    unsigned long p = *(unsigned long *)(a.lo + 0x10);
    sk_h_003494e8();
    sk_fp_00658c00(0);
    sk_h_00348f38();
    sk_pair_t v = sk_h_0006e778(0x13);
    (void)v;
    sk_h_0034f064();
    sk_h_003a25d4();
    sk_h_003524d4(0xd000000000000010);
    sk_h_002a4c98();
    sk_h_003504a0(0);
    sk_h_003514e8();
    sk_h_001c050c();
    sk_h_00352c80();
    sk_h_0034c094(0);
    sk_h_003a25d4();
    sk_h_0034a798();
    sk_h_0034c0a4();
    sk_h_002a4c98();
    sk_h_003a25d4();
    sk_h_0034ab88();
    sk_h_003a25d4();
    sk_h_0035a798();
    sk_h_00350868(0x29);
    sk_h_002a4c98();
    sk_pair_t z = sk_h_000b43d0();
    sk_h_0008e500(z.lo, z.hi, a.hi);
    (void)p;
}

/* FUN_002d03e8 @ 0x002d03e8   (est. sk_swift_string_build)
 * Ghidra: void FUN_002d03e8(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_build(unsigned long *out)
{
    /* Builds a small "element"-labelled string object: sets up the string
     * buffer (FUN_00358fe8), fills the two-word owner/offset fields and the
     * tagged "element" value, and stores the result into the caller buffer. */
    sk_h_00353aa0();
    sk_h_000a6f88();
    sk_fp_00658c00(0);
    sk_h_00349178();
    sk_h_0034b768(0);
    sk_h_003519d4();
    long p = (long)sk_h_00358fe8().lo;
    *(unsigned long *)(p + 0x10) = sk_q_004baeb0;
    *(unsigned long *)(p + 0x18) = sk_q_004baeb8;
    *(unsigned long *)(p + 0x20) = 0x746e656d656c65;
    *(unsigned long *)(p + 0x28) = 0xe700000000000000;
    *(unsigned long *)(p + 0x48) = *(unsigned long *)(0 + 0x10);
    sk_h_00319a4c(p + 0x30);
    sk_h_0034d140();
    sk_h_000e15d8(0);
    sk_h_0034d5ec();
    sk_h_001e4348();
    sk_h_00358870();
    out[0] = 0; out[1] = 0;
}

/* FUN_002d04e8 @ 0x002d04e8   (est. sk_swift_string_build_store)
 * Ghidra: void FUN_002d04e8(...)
 * See function-local comments for behavior.
 */
void sk_swift_string_build_store(unsigned long *out)
{
    sk_swift_string_build(out);
    out[0] = 0; out[1] = 0; out[2] = 0; out[3] = 0;
}

/* FUN_002d0528 @ 0x002d0528   (est. sk_swift_sequence_concat)
 * Ghidra: void FUN_002d0528(...)
 * See function-local comments for behavior.
 */
void sk_swift_sequence_concat(unsigned long p1, unsigned long p2, long p3, long p4)
{
    /* Sequence concatenation: iterates the two source sequences reading each
     * slot (sk_object_read_slot via sk_object_read_slot), appending the chosen
     * element to the destination buffer, advancing per element, and trapping on
     * index overflow. */
    sk_h_00353cfc();
    sk_h_003516cc();
    sk_h_003246ec();
    sk_h_00348e60();
    sk_fp_00658c00(0);
    sk_h_003503ec();
    sk_fp_00658c00(0);
    sk_h_0034c2f8();
    sk_fp_00658c00(0);
    long i = 0, j = 0;
    long n1 = *(long *)(p3 + 0x10);
    long n2 = 0;
    (void)n2;
    while (1) {
        if (j < n1) {
            sk_h_003510dc(0);
            sk_h_0019ea20();
            long a = (long)sk_object_read_slot();
            sk_h_00351648();
            sk_h_00354d14(0);
            sk_h_0019ea20();
            long b = (long)sk_object_read_slot();
            sk_h_00351648();
            sk_h_0035242c();
            sk_h_0019ea20(0, 0);
            sk_h_00352dd0();
            sk_h_00352858();
            sk_h_0019ea20();
            (void)a; (void)b;
        } else {
            sk_h_0035242c();
            sk_h_0019ea20(0, 0);
        }
        sk_h_00324858(0);
        sk_h_00359c64();
        sk_h_003511a8();
        sk_h_00351348();
        sk_h_00353d14(0);
        return;
        sk_h_00350a70(0);
        sk_h_00350914();
        int cmp = (int)sk_h_00369584().lo;
        if (cmp == 1) i += 1; else j += 1;
        sk_h_00349b28();
        sk_h_00027614();
        sk_h_003543d0();
        sk_pair_t c = sk_h_0035041c();
        sk_h_00357fa4(c.lo, c.hi, p4);
        long base = (long)sk_h_0037233c().lo;
        (void)base;
    }
}

/* FUN_002d07ec @ 0x002d07ec   (est. sk_swift_wrap_2c55b4_a)
 * Ghidra: void FUN_002d07ec(...)
 * See function-local comments for behavior.
 */
void sk_swift_wrap_2c55b4_a(void)
{
    sk_h_002c55b4();
}

/* FUN_002d07f0 @ 0x002d07f0   (est. sk_swift_wrap_2c55b4_b)
 * Ghidra: void FUN_002d07f0(...)
 * See function-local comments for behavior.
 */
void sk_swift_wrap_2c55b4_b(void)
{
    sk_h_002c55b4();
}
