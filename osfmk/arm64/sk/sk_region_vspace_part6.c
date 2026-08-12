/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary;
 * estimates unless matched. This slice covers the vspace/MMU layer
 * (0x00248b48..0x0024f23c, 121 functions). The cL4 kernel is written in Swift,
 * so a large share of these bodies are UnsafeRawBufferPointer/UnsafeBufferPointer
 * accessors and page-table descriptor encoders/decoders over that Swift runtime.
 *
 * All out-of-range callees (FUN_0034xxxx/0035xxxx/0036xxxx/0008xxxx/etc., the
 * shared cL4/seL4 runtime library) are declared extern below as sk_rt_<addr>
 * with the FUN_ address in a comment. K&R empty-paren declarations are used so
 * the exact (often variadic / Swift-metadata-laden) arities compile cleanly. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* 16-byte pair (x0/x1) returned by many Swift helpers (base+count, lo+hi). */
typedef struct sk_pair {
    uint64_t lo;
    uint64_t hi;
} sk_pair_t;

typedef uint8_t byte;
typedef unsigned int uint;
typedef unsigned long ulong;

/* ------------------------------------------------------------------------- */
/* Out-of-range shared cL4/seL4 runtime library (FUN_ addr in comment).      */
/* ------------------------------------------------------------------------- */
extern long sk_rt_000026e8();  /* FUN_000026e8 */
extern sk_pair_t sk_rt_000027e8();  /* FUN_000027e8 */
extern long sk_rt_00002834();  /* FUN_00002834 */
extern long sk_rt_00012568();  /* FUN_00012568 */
extern long sk_rt_00041138();  /* FUN_00041138 */
extern sk_pair_t sk_rt_000651bc();  /* FUN_000651bc */
extern sk_pair_t sk_rt_0006a4c0();  /* FUN_0006a4c0 */
extern sk_pair_t sk_rt_0006b2ec();  /* FUN_0006b2ec */
extern long sk_rt_0006b6f4();  /* FUN_0006b6f4 */
extern long sk_rt_0006e778();  /* FUN_0006e778 */
extern long sk_rt_0006f768();  /* FUN_0006f768 */
extern long sk_rt_00077888();  /* FUN_00077888 */
extern long sk_rt_0007c028();  /* FUN_0007c028 */
extern sk_pair_t sk_rt_0007c0c4();  /* FUN_0007c0c4 */
extern long sk_rt_0007c198();  /* FUN_0007c198 */
extern long sk_rt_0007c1a4();  /* FUN_0007c1a4 */
extern long sk_rt_0007c1c4();  /* FUN_0007c1c4 */
extern long sk_rt_000839d8();  /* FUN_000839d8 */
extern long sk_rt_00084180();  /* FUN_00084180 */
extern long sk_rt_00084220();  /* FUN_00084220 */
extern long sk_rt_00084234();  /* FUN_00084234 */
extern long sk_rt_000867a8();  /* FUN_000867a8 */
extern long sk_rt_000867ec();  /* FUN_000867ec */
extern long sk_rt_0008e500();  /* FUN_0008e500 */
extern sk_pair_t sk_rt_0008e518();  /* FUN_0008e518 */
extern long sk_rt_0009461c();  /* FUN_0009461c */
extern sk_pair_t sk_rt_000a6f68();  /* FUN_000a6f68 */
extern sk_pair_t sk_rt_000dbd0c();  /* FUN_000dbd0c */
extern long sk_rt_000dbdf4();  /* FUN_000dbdf4 */
extern long sk_rt_000dbe0c();  /* FUN_000dbe0c */
extern sk_pair_t sk_rt_000e15d8();  /* FUN_000e15d8 */
extern long sk_rt_00100efc();  /* FUN_00100efc */
extern long sk_rt_00115080();  /* FUN_00115080 */
extern long sk_rt_00117cc4();  /* FUN_00117cc4 */
extern long sk_rt_0011aa70();  /* FUN_0011aa70 */
extern long sk_rt_0011d7e8();  /* FUN_0011d7e8 */
extern long sk_rt_00154148();  /* FUN_00154148 */
extern long sk_rt_001a0be4();  /* FUN_001a0be4 */
extern sk_pair_t sk_rt_001a26e0();  /* FUN_001a26e0 */
extern long sk_rt_001a84f4();  /* FUN_001a84f4 */
extern long sk_rt_001a8564();  /* FUN_001a8564 */
extern long sk_rt_001a89a8();  /* FUN_001a89a8 */
extern long sk_rt_001afa84();  /* FUN_001afa84 */
extern long sk_rt_001afe4c();  /* FUN_001afe4c */
extern long sk_rt_001dbffc();  /* FUN_001dbffc */
extern sk_pair_t sk_rt_001ee0c8();  /* FUN_001ee0c8 */
extern sk_pair_t sk_rt_001ee0fc();  /* FUN_001ee0fc */
extern long sk_rt_001ee130();  /* FUN_001ee130 */
extern long sk_rt_002298d4();  /* FUN_002298d4 */
extern sk_pair_t sk_rt_0022a474();  /* FUN_0022a474 */
extern long sk_rt_0022bd00();  /* FUN_0022bd00 */
extern long sk_rt_00247360();  /* FUN_00247360 */
extern sk_pair_t sk_rt_00247454();  /* FUN_00247454 */
extern long sk_rt_002487b8();  /* FUN_002487b8 */
extern long sk_rt_00248860();  /* FUN_00248860 */
extern long sk_rt_002488b4();  /* FUN_002488b4 */
extern sk_pair_t sk_rt_00248a34();  /* FUN_00248a34 */
extern sk_pair_t sk_rt_00248ae0();  /* FUN_00248ae0 */
extern long sk_rt_0024f2a0();  /* FUN_0024f2a0 */
extern long sk_rt_0024f498();  /* FUN_0024f498 */
extern long sk_rt_002514f0();  /* FUN_002514f0 */
extern long sk_rt_0027ed08();  /* FUN_0027ed08 */
extern long sk_rt_0027ed7c();  /* FUN_0027ed7c */
extern long sk_rt_00291d70();  /* FUN_00291d70 */
extern sk_pair_t sk_rt_002a218c();  /* FUN_002a218c */
extern long sk_rt_002a2698();  /* FUN_002a2698 */
extern long sk_rt_002a2748();  /* FUN_002a2748 */
extern long sk_rt_002a4c98();  /* FUN_002a4c98 */
extern sk_pair_t sk_rt_00310ad4();  /* FUN_00310ad4 */
extern long sk_rt_00310ca4();  /* FUN_00310ca4 */
extern long sk_rt_00310d04();  /* FUN_00310d04 */
extern long sk_rt_00310d68();  /* FUN_00310d68 */
extern long sk_rt_00310fc4();  /* FUN_00310fc4 */
extern sk_pair_t sk_rt_00319a4c();  /* FUN_00319a4c */
extern long sk_rt_0031bc70();  /* FUN_0031bc70 */
extern long sk_rt_0031ca54();  /* FUN_0031ca54 */
extern long sk_rt_0031cbbc();  /* FUN_0031cbbc */
extern long sk_rt_0031cc3c();  /* FUN_0031cc3c */
extern sk_pair_t sk_rt_0031cc54();  /* FUN_0031cc54 */
extern long sk_rt_0031cc6c();  /* FUN_0031cc6c */
extern long sk_rt_0031cd00();  /* FUN_0031cd00 */
extern long sk_rt_0031cd18();  /* FUN_0031cd18 */
extern sk_pair_t sk_rt_0031dc0c();  /* FUN_0031dc0c */
extern long sk_rt_00331f28();  /* FUN_00331f28 */
extern long sk_rt_00331fdc();  /* FUN_00331fdc */
extern long sk_rt_003320b8();  /* FUN_003320b8 */
extern long sk_rt_0034447c();  /* FUN_0034447c */
extern long sk_rt_003444e4();  /* FUN_003444e4 */
extern long sk_rt_0034454c();  /* FUN_0034454c */
extern long sk_rt_003448a4();  /* FUN_003448a4 */
extern long sk_rt_00347f2c();  /* FUN_00347f2c */
extern long sk_rt_00347ff4();  /* FUN_00347ff4 */
extern long sk_rt_00348074();  /* FUN_00348074 */
extern long sk_rt_00348128();  /* FUN_00348128 */
extern long sk_rt_00348194();  /* FUN_00348194 */
extern long sk_rt_00348284();  /* FUN_00348284 */
extern long sk_rt_003482c4();  /* FUN_003482c4 */
extern long sk_rt_00348304();  /* FUN_00348304 */
extern long sk_rt_003483c4();  /* FUN_003483c4 */
extern long sk_rt_00348404();  /* FUN_00348404 */
extern long sk_rt_0034846c();  /* FUN_0034846c */
extern long sk_rt_00348508();  /* FUN_00348508 */
extern long sk_rt_0034865c();  /* FUN_0034865c */
extern long sk_rt_00348898();  /* FUN_00348898 */
extern long sk_rt_003488bc();  /* FUN_003488bc */
extern long sk_rt_003489c0();  /* FUN_003489c0 */
extern long sk_rt_003489dc();  /* FUN_003489dc */
extern long sk_rt_00348a34();  /* FUN_00348a34 */
extern long sk_rt_00348b7c();  /* FUN_00348b7c */
extern long sk_rt_00348c18();  /* FUN_00348c18 */
extern long sk_rt_00348c48();  /* FUN_00348c48 */
extern long sk_rt_00348d4c();  /* FUN_00348d4c */
extern long sk_rt_00348d64();  /* FUN_00348d64 */
extern long sk_rt_00348e60();  /* FUN_00348e60 */
extern long sk_rt_00348f50();  /* FUN_00348f50 */
extern long sk_rt_00349068();  /* FUN_00349068 */
extern long sk_rt_00349098();  /* FUN_00349098 */
extern long sk_rt_00349178();  /* FUN_00349178 */
extern long sk_rt_003493ac();  /* FUN_003493ac */
extern long sk_rt_0034947c();  /* FUN_0034947c */
extern long sk_rt_003494e8();  /* FUN_003494e8 */
extern long sk_rt_003495a8();  /* FUN_003495a8 */
extern long sk_rt_00349644();  /* FUN_00349644 */
extern long sk_rt_003496cc();  /* FUN_003496cc */
extern long sk_rt_003497b4();  /* FUN_003497b4 */
extern long sk_rt_003497c8();  /* FUN_003497c8 */
extern long sk_rt_00349844();  /* FUN_00349844 */
extern long sk_rt_003499b4();  /* FUN_003499b4 */
extern long sk_rt_00349a54();  /* FUN_00349a54 */
extern long sk_rt_00349a68();  /* FUN_00349a68 */
extern long sk_rt_00349b00();  /* FUN_00349b00 */
extern long sk_rt_00349eb8();  /* FUN_00349eb8 */
extern long sk_rt_00349ef4();  /* FUN_00349ef4 */
extern long sk_rt_0034a2f8();  /* FUN_0034a2f8 */
extern long sk_rt_0034a368();  /* FUN_0034a368 */
extern long sk_rt_0034a688();  /* FUN_0034a688 */
extern long sk_rt_0034a6b0();  /* FUN_0034a6b0 */
extern long sk_rt_0034a798();  /* FUN_0034a798 */
extern long sk_rt_0034a7ac();  /* FUN_0034a7ac */
extern long sk_rt_0034a900();  /* FUN_0034a900 */
extern long sk_rt_0034aaf4();  /* FUN_0034aaf4 */
extern long sk_rt_0034ab20();  /* FUN_0034ab20 */
extern long sk_rt_0034b014();  /* FUN_0034b014 */
extern long sk_rt_0034b07c();  /* FUN_0034b07c */
extern long sk_rt_0034b0c4();  /* FUN_0034b0c4 */
extern long sk_rt_0034b0d4();  /* FUN_0034b0d4 */
extern long sk_rt_0034b2c8();  /* FUN_0034b2c8 */
extern long sk_rt_0034b318();  /* FUN_0034b318 */
extern long sk_rt_0034b3e8();  /* FUN_0034b3e8 */
extern long sk_rt_0034b430();  /* FUN_0034b430 */
extern sk_pair_t sk_rt_0034b518();  /* FUN_0034b518 */
extern long sk_rt_0034b540();  /* FUN_0034b540 */
extern long sk_rt_0034b5a8();  /* FUN_0034b5a8 */
extern long sk_rt_0034b730();  /* FUN_0034b730 */
extern long sk_rt_0034b758();  /* FUN_0034b758 */
extern long sk_rt_0034b7b8();  /* FUN_0034b7b8 */
extern long sk_rt_0034b7e4();  /* FUN_0034b7e4 */
extern long sk_rt_0034b804();  /* FUN_0034b804 */
extern long sk_rt_0034b8bc();  /* FUN_0034b8bc */
extern long sk_rt_0034baa8();  /* FUN_0034baa8 */
extern long sk_rt_0034bc94();  /* FUN_0034bc94 */
extern sk_pair_t sk_rt_0034bccc();  /* FUN_0034bccc */
extern long sk_rt_0034bd90();  /* FUN_0034bd90 */
extern long sk_rt_0034bdfc();  /* FUN_0034bdfc */
extern long sk_rt_0034beb4();  /* FUN_0034beb4 */
extern long sk_rt_0034c084();  /* FUN_0034c084 */
extern long sk_rt_0034c0a4();  /* FUN_0034c0a4 */
extern long sk_rt_0034c3f4();  /* FUN_0034c3f4 */
extern long sk_rt_0034c5ac();  /* FUN_0034c5ac */
extern long sk_rt_0034c5bc();  /* FUN_0034c5bc */
extern long sk_rt_0034c5fc();  /* FUN_0034c5fc */
extern long sk_rt_0034c664();  /* FUN_0034c664 */
extern sk_pair_t sk_rt_0034c828();  /* FUN_0034c828 */
extern long sk_rt_0034c8e0();  /* FUN_0034c8e0 */
extern long sk_rt_0034c920();  /* FUN_0034c920 */
extern long sk_rt_0034cc94();  /* FUN_0034cc94 */
extern long sk_rt_0034cdd8();  /* FUN_0034cdd8 */
extern long sk_rt_0034ce78();  /* FUN_0034ce78 */
extern long sk_rt_0034d024();  /* FUN_0034d024 */
extern long sk_rt_0034d264();  /* FUN_0034d264 */
extern long sk_rt_0034da88();  /* FUN_0034da88 */
extern long sk_rt_0034e0d4();  /* FUN_0034e0d4 */
extern long sk_rt_0034e55c();  /* FUN_0034e55c */
extern long sk_rt_0034e6fc();  /* FUN_0034e6fc */
extern long sk_rt_0034eb94();  /* FUN_0034eb94 */
extern long sk_rt_0034ec48();  /* FUN_0034ec48 */
extern long sk_rt_0034ece8();  /* FUN_0034ece8 */
extern long sk_rt_0034ed18();  /* FUN_0034ed18 */
extern long sk_rt_0034edf8();  /* FUN_0034edf8 */
extern long sk_rt_0034ee78();  /* FUN_0034ee78 */
extern long sk_rt_0034f198();  /* FUN_0034f198 */
extern long sk_rt_0034f374();  /* FUN_0034f374 */
extern long sk_rt_0034f614();  /* FUN_0034f614 */
extern long sk_rt_0034fbc4();  /* FUN_0034fbc4 */
extern long sk_rt_0034fbe4();  /* FUN_0034fbe4 */
extern long sk_rt_003500d4();  /* FUN_003500d4 */
extern long sk_rt_00350278();  /* FUN_00350278 */
extern long sk_rt_003502c8();  /* FUN_003502c8 */
extern long sk_rt_00350410();  /* FUN_00350410 */
extern sk_pair_t sk_rt_00350488();  /* FUN_00350488 */
extern sk_pair_t sk_rt_003504c4();  /* FUN_003504c4 */
extern long sk_rt_003504d0();  /* FUN_003504d0 */
extern sk_pair_t sk_rt_003504e8();  /* FUN_003504e8 */
extern long sk_rt_00350518();  /* FUN_00350518 */
extern long sk_rt_00350524();  /* FUN_00350524 */
extern long sk_rt_00350530();  /* FUN_00350530 */
extern long sk_rt_00350560();  /* FUN_00350560 */
extern long sk_rt_0035056c();  /* FUN_0035056c */
extern long sk_rt_003505e8();  /* FUN_003505e8 */
extern sk_pair_t sk_rt_0035060c();  /* FUN_0035060c */
extern long sk_rt_00350618();  /* FUN_00350618 */
extern long sk_rt_00350630();  /* FUN_00350630 */
extern long sk_rt_00350744();  /* FUN_00350744 */
extern long sk_rt_00350768();  /* FUN_00350768 */
extern long sk_rt_00350798();  /* FUN_00350798 */
extern long sk_rt_003507d4();  /* FUN_003507d4 */
extern long sk_rt_003507e0();  /* FUN_003507e0 */
extern long sk_rt_00350804();  /* FUN_00350804 */
extern long sk_rt_00350810();  /* FUN_00350810 */
extern long sk_rt_0035089c();  /* FUN_0035089c */
extern long sk_rt_003508cc();  /* FUN_003508cc */
extern long sk_rt_003508fc();  /* FUN_003508fc */
extern long sk_rt_003509d4();  /* FUN_003509d4 */
extern sk_pair_t sk_rt_00350a28();  /* FUN_00350a28 */
extern long sk_rt_00350a34();  /* FUN_00350a34 */
extern long sk_rt_00350a7c();  /* FUN_00350a7c */
extern long sk_rt_00350a88();  /* FUN_00350a88 */
extern long sk_rt_00350a94();  /* FUN_00350a94 */
extern long sk_rt_00350aa0();  /* FUN_00350aa0 */
extern long sk_rt_00350aac();  /* FUN_00350aac */
extern long sk_rt_00350ab8();  /* FUN_00350ab8 */
extern long sk_rt_00350b18();  /* FUN_00350b18 */
extern long sk_rt_00350d94();  /* FUN_00350d94 */
extern long sk_rt_0035102c();  /* FUN_0035102c */
extern long sk_rt_00351094();  /* FUN_00351094 */
extern long sk_rt_003510b8();  /* FUN_003510b8 */
extern long sk_rt_0035119c();  /* FUN_0035119c */
extern long sk_rt_003511c0();  /* FUN_003511c0 */
extern long sk_rt_00351250();  /* FUN_00351250 */
extern long sk_rt_00351384();  /* FUN_00351384 */
extern long sk_rt_00351408();  /* FUN_00351408 */
extern long sk_rt_00351488();  /* FUN_00351488 */
extern long sk_rt_003514dc();  /* FUN_003514dc */
extern long sk_rt_003514e8();  /* FUN_003514e8 */
extern long sk_rt_00351554();  /* FUN_00351554 */
extern long sk_rt_003515b4();  /* FUN_003515b4 */
extern long sk_rt_003515e4();  /* FUN_003515e4 */
extern sk_pair_t sk_rt_003516e4();  /* FUN_003516e4 */
extern long sk_rt_00351714();  /* FUN_00351714 */
extern long sk_rt_00351774();  /* FUN_00351774 */
extern long sk_rt_00351790();  /* FUN_00351790 */
extern sk_pair_t sk_rt_003517b4();  /* FUN_003517b4 */
extern long sk_rt_003517c0();  /* FUN_003517c0 */
extern long sk_rt_003517cc();  /* FUN_003517cc */
extern sk_pair_t sk_rt_0035193c();  /* FUN_0035193c */
extern sk_pair_t sk_rt_00351984();  /* FUN_00351984 */
extern long sk_rt_00351a38();  /* FUN_00351a38 */
extern long sk_rt_00351a44();  /* FUN_00351a44 */
extern long sk_rt_00351aec();  /* FUN_00351aec */
extern long sk_rt_00351b04();  /* FUN_00351b04 */
extern long sk_rt_00351be0();  /* FUN_00351be0 */
extern long sk_rt_00351c88();  /* FUN_00351c88 */
extern long sk_rt_00351d24();  /* FUN_00351d24 */
extern sk_pair_t sk_rt_00351d9c();  /* FUN_00351d9c */
extern long sk_rt_00351df0();  /* FUN_00351df0 */
extern long sk_rt_00351dfc();  /* FUN_00351dfc */
extern sk_pair_t sk_rt_00351e6c();  /* FUN_00351e6c */
extern sk_pair_t sk_rt_00351e84();  /* FUN_00351e84 */
extern long sk_rt_00351f40();  /* FUN_00351f40 */
extern sk_pair_t sk_rt_00352188();  /* FUN_00352188 */
extern sk_pair_t sk_rt_00352230();  /* FUN_00352230 */
extern long sk_rt_003523f0();  /* FUN_003523f0 */
extern long sk_rt_00352474();  /* FUN_00352474 */
extern long sk_rt_00352578();  /* FUN_00352578 */
extern long sk_rt_00352738();  /* FUN_00352738 */
extern long sk_rt_00352758();  /* FUN_00352758 */
extern long sk_rt_003528cc();  /* FUN_003528cc */
extern long sk_rt_00352ae4();  /* FUN_00352ae4 */
extern long sk_rt_00352b08();  /* FUN_00352b08 */
extern long sk_rt_00352b50();  /* FUN_00352b50 */
extern sk_pair_t sk_rt_00352bb0();  /* FUN_00352bb0 */
extern long sk_rt_00352c80();  /* FUN_00352c80 */
extern long sk_rt_00352cc8();  /* FUN_00352cc8 */
extern long sk_rt_00352e0c();  /* FUN_00352e0c */
extern long sk_rt_00352efc();  /* FUN_00352efc */
extern sk_pair_t sk_rt_0035300c();  /* FUN_0035300c */
extern long sk_rt_0035316c();  /* FUN_0035316c */
extern long sk_rt_00353208();  /* FUN_00353208 */
extern long sk_rt_00353238();  /* FUN_00353238 */
extern long sk_rt_00353474();  /* FUN_00353474 */
extern long sk_rt_00353498();  /* FUN_00353498 */
extern long sk_rt_00353540();  /* FUN_00353540 */
extern long sk_rt_00353918();  /* FUN_00353918 */
extern long sk_rt_00353a0c();  /* FUN_00353a0c */
extern long sk_rt_00353a30();  /* FUN_00353a30 */
extern long sk_rt_00353a90();  /* FUN_00353a90 */
extern long sk_rt_00353abc();  /* FUN_00353abc */
extern long sk_rt_00353b10();  /* FUN_00353b10 */
extern long sk_rt_00353b4c();  /* FUN_00353b4c */
extern long sk_rt_00353b58();  /* FUN_00353b58 */
extern long sk_rt_00353ba0();  /* FUN_00353ba0 */
extern sk_pair_t sk_rt_00353cfc();  /* FUN_00353cfc */
extern long sk_rt_00353d14();  /* FUN_00353d14 */
extern long sk_rt_00353d70();  /* FUN_00353d70 */
extern long sk_rt_00353eac();  /* FUN_00353eac */
extern long sk_rt_00354010();  /* FUN_00354010 */
extern long sk_rt_003542a8();  /* FUN_003542a8 */
extern long sk_rt_00354410();  /* FUN_00354410 */
extern long sk_rt_00354708();  /* FUN_00354708 */
extern sk_pair_t sk_rt_00354714();  /* FUN_00354714 */
extern long sk_rt_0035481c();  /* FUN_0035481c */
extern sk_pair_t sk_rt_003548b8();  /* FUN_003548b8 */
extern sk_pair_t sk_rt_003549d8();  /* FUN_003549d8 */
extern long sk_rt_00354a6c();  /* FUN_00354a6c */
extern long sk_rt_00354b2c();  /* FUN_00354b2c */
extern long sk_rt_00354cb4();  /* FUN_00354cb4 */
extern long sk_rt_00354d44();  /* FUN_00354d44 */
extern sk_pair_t sk_rt_00354d5c();  /* FUN_00354d5c */
extern long sk_rt_00354e00();  /* FUN_00354e00 */
extern long sk_rt_00354f28();  /* FUN_00354f28 */
extern long sk_rt_0035503c();  /* FUN_0035503c */
extern sk_pair_t sk_rt_003551c4();  /* FUN_003551c4 */
extern long sk_rt_00355458();  /* FUN_00355458 */
extern long sk_rt_003558fc();  /* FUN_003558fc */
extern sk_pair_t sk_rt_00355b38();  /* FUN_00355b38 */
extern long sk_rt_00355b90();  /* FUN_00355b90 */
extern long sk_rt_00355cbc();  /* FUN_00355cbc */
extern long sk_rt_00355f70();  /* FUN_00355f70 */
extern long sk_rt_00356018();  /* FUN_00356018 */
extern long sk_rt_00356200();  /* FUN_00356200 */
extern long sk_rt_00356260();  /* FUN_00356260 */
extern long sk_rt_00356310();  /* FUN_00356310 */
extern long sk_rt_00356370();  /* FUN_00356370 */
extern long sk_rt_0035638c();  /* FUN_0035638c */
extern long sk_rt_00356590();  /* FUN_00356590 */
extern long sk_rt_003565a8();  /* FUN_003565a8 */
extern long sk_rt_003567c8();  /* FUN_003567c8 */
extern long sk_rt_00356a50();  /* FUN_00356a50 */
extern long sk_rt_00356b98();  /* FUN_00356b98 */
extern sk_pair_t sk_rt_00357198();  /* FUN_00357198 */
extern long sk_rt_00357584();  /* FUN_00357584 */
extern long sk_rt_00357b60();  /* FUN_00357b60 */
extern long sk_rt_00357bc4();  /* FUN_00357bc4 */
extern long sk_rt_00357c44();  /* FUN_00357c44 */
extern long sk_rt_00357ca0();  /* FUN_00357ca0 */
extern long sk_rt_00357dc4();  /* FUN_00357dc4 */
extern long sk_rt_00357e64();  /* FUN_00357e64 */
extern long sk_rt_003581d4();  /* FUN_003581d4 */
extern sk_pair_t sk_rt_00358228();  /* FUN_00358228 */
extern long sk_rt_00358278();  /* FUN_00358278 */
extern long sk_rt_00358298();  /* FUN_00358298 */
extern long sk_rt_003583dc();  /* FUN_003583dc */
extern long sk_rt_00358470();  /* FUN_00358470 */
extern long sk_rt_0035847c();  /* FUN_0035847c */
extern long sk_rt_0035849c();  /* FUN_0035849c */
extern long sk_rt_0035854c();  /* FUN_0035854c */
extern long sk_rt_00359024();  /* FUN_00359024 */
extern sk_pair_t sk_rt_00359290();  /* FUN_00359290 */
extern long sk_rt_003594f4();  /* FUN_003594f4 */
extern long sk_rt_00359bd4();  /* FUN_00359bd4 */
extern long sk_rt_00359c58();  /* FUN_00359c58 */
extern long sk_rt_00359f3c();  /* FUN_00359f3c */
extern long sk_rt_0035a218();  /* FUN_0035a218 */
extern long sk_rt_0035a7c0();  /* FUN_0035a7c0 */
extern long sk_rt_0035a7d4();  /* FUN_0035a7d4 */
extern long sk_rt_0035a7e8();  /* FUN_0035a7e8 */
extern sk_pair_t sk_rt_0035a808();  /* FUN_0035a808 */
extern long sk_rt_0035aa18();  /* FUN_0035aa18 */
extern long sk_rt_0035aa9c();  /* FUN_0035aa9c */
extern sk_pair_t sk_rt_0035abb0();  /* FUN_0035abb0 */
extern long sk_rt_0035ace8();  /* FUN_0035ace8 */
extern long sk_rt_00362acc();  /* FUN_00362acc */
extern long sk_rt_00362bc0();  /* FUN_00362bc0 */
extern long sk_rt_00365b6c();  /* FUN_00365b6c */
extern long sk_rt_0036a1a0();  /* FUN_0036a1a0 */
extern long sk_rt_0036a20c();  /* FUN_0036a20c */
extern sk_pair_t sk_rt_0036a804();  /* FUN_0036a804 */
extern long sk_rt_0036a940();  /* FUN_0036a940 */
extern long sk_rt_0036b118();  /* FUN_0036b118 */
extern long sk_rt_0036b270();  /* FUN_0036b270 */
extern long sk_rt_0036b340();  /* FUN_0036b340 */
extern long sk_rt_0036b6ac();  /* FUN_0036b6ac */
extern long sk_rt_003704f4();  /* FUN_003704f4 */
extern long sk_rt_003705b0();  /* FUN_003705b0 */
extern long sk_rt_003722e4();  /* FUN_003722e4 */
extern sk_pair_t sk_rt_003743d0();  /* FUN_003743d0 */
extern long sk_rt_00377824();  /* FUN_00377824 */
extern long sk_rt_00377bec();  /* FUN_00377bec */
extern long sk_rt_003893d0();  /* FUN_003893d0 */
extern long sk_rt_00389b4c();  /* FUN_00389b4c */
extern long sk_rt_003a25d4();  /* FUN_003a25d4 */
extern sk_pair_t sk_rt_003a261c();  /* FUN_003a261c */
extern sk_pair_t sk_rt_003d31f8();  /* FUN_003d31f8 */

/* Global per-operation hook (Swift metadata/vtable dispatcher). Returns the
 * current operation descriptor in x0/x1; callers index offsets off it. */
extern sk_pair_t (*sk_hook_00658c00)();  /* DAT_00658c00 */
extern long sk_rt_fatal_001afe4c();  /* FUN_001afe4c (Swift fatal-error trampoline, noreturn) */

/* Key-material constant referenced by the PAC/key-slot init functions
 * (bytes at DAT_004e7a30, the obfuscated phrase "uespemos..."; two 8-byte LE
 * words: "uespemos" and "arenegyl"). */
#define SK_KEYM_LO 0x736f6d6570736575ull
#define SK_KEYM_HI 0x6c7967656e657261ull

/* Forward declarations for functions reconstructed in this file. */
void sk_vspace_key_init_a(void);
void sk_vspace_op_dispatch(void);
void sk_pt_descriptor_build(void);
uint sk_vspace_pte_compare(long a, long b);
void sk_vspace_key_init_fwd_a(void);
void sk_vspace_op_dispatch_fwd(void);
void sk_vspace_key_init_wrap(void);
uint sk_vspace_pte_cmp_ref(uint64_t *a, uint64_t *b);
uint sk_vspace_pte_cmp_ref2(uint64_t *a, uint64_t *b);
void sk_vspace_ctx_free_a(void);
void sk_vspace_ctx_free_b(void);
void sk_vspace_ctx_state_merge(long other);
void sk_vspace_ctx_commit(void);
void sk_vspace_ctx_commit2(void);
void sk_alloc_ctx(void);
void sk_vspace_map_dispatch(void);
void sk_vspace_perm_check_a(void);
void sk_vspace_iterate_regions(void);
void sk_vspace_map_dispatch2(void);
void sk_iterate_fwd_a(void);
void sk_iterate_fwd_b(void);
void sk_vspace_ctx_create(void);
void sk_alloc_ctx2(void);
void sk_vspace_ctx_mutate(void);
void sk_vspace_ctx_prepare(void);
void sk_vspace_perm_check_b(void);
void sk_vspace_ctx_alloc_commit(void);
void sk_vspace_ctx_signal(void);
void sk_vspace_key_init_b(void);
void sk_vspace_ctx_forward(void);
long sk_vspace_ctx_reserve(void);
void sk_vspace_ctx_lock_a(void);
void sk_vspace_ctx_lock_b(long p);
void sk_vspace_ctx_lock_c(long p);
long sk_vspace_ctx_ref_a(long p);
long sk_vspace_ctx_ref_b(long p);
long sk_vspace_ctx_ref_c(long p);
ulong sk_vspace_region_compare(long *a, long *b);
void sk_vspace_region_build(void);
void sk_vspace_key_init_c(void);
void sk_vspace_key_init_wrap2(void);
long sk_vspace_ctx_alloc_obj(void);
void sk_vspace_ctx_free_obj(void);
void sk_vspace_ctx_free_fwd_a(void);
void sk_vspace_ctx_free_fwd_b(void);
void sk_vspace_ctx_teardown(void);
void sk_vspace_ctx_commit_a(void);
void sk_vspace_ctx_store_fields(void);
void sk_vspace_ctx_teardown2(void);
void sk_vspace_ctx_commit_b(void);
void sk_vspace_ctx_store_fields2(void);
void sk_vspace_ctx_forward2(void);
uint sk_pte_attr_nibble(uint flags);
ulong sk_pte_size_a(uint flags);
ulong sk_pte_size_b(uint flags);
long sk_pte_size_c(ulong flags, long base);
uint64_t sk_pte_next_region(ulong flags, long base);
uint sk_buf_load_u32(long off, long base, long end);
sk_pair_t sk_buf_load_u64(long off, long base, long end);
void sk_buf_store_range(long a, long b, long c, long d);
uint sk_buf_load_u32_at4(void);
long sk_pte_next_region_off(ulong flags, long base);
void sk_pte_build_region(void);
void sk_pte_store_u32(long off, long base, long end, uint val);
void sk_pte_store_u64(long off, long base, long end, uint64_t val);
void sk_buf_set_ptr(long a, uint64_t b, long c);
void sk_vspace_ctx_op_commit_a(void);
void sk_vspace_ctx_perm_mod(void);
void sk_buf_drop8(long *buf, long n);
void sk_buf_advance4(void);
long sk_buf_consume4(long *buf, long n);
sk_pair_t sk_buf_align8(ulong p, long len);
sk_pair_t sk_buf_align4(ulong p, long len);
ulong sk_align_up8(ulong n);
ulong sk_alloc_aligned(long a, long b);
void sk_attr_reserved_check(uint flags);
void sk_vspace_ctx_op_dispatch_a(void);
void sk_vspace_dispatch_fwd(void);
void sk_vspace_ctx_op_dispatch_b(void);
void sk_vspace_op_dispatch_main(void);
void sk_vspace_ctx_create_fwd(void);
void sk_vspace_ctx_op_commit_c(void);
void sk_vspace_ctx_op_prepare2(void);
void sk_vspace_op_forward(void);
uint64_t sk_vspace_region_match(long *a, long *b);
uint64_t sk_vspace_region_match_tcb(void);
void sk_vspace_ctx_signal_a(void);
void sk_vspace_ctx_signal_b(void);
void sk_vspace_ctx_signal_c(void);
void sk_vspace_ctx_signal_d(long *p, long obj);
void sk_vspace_ctx_counter_merge(void);
void sk_vspace_ctx_signal_e(void);
void sk_vspace_ctx_signal_f(void);
void sk_vspace_ctx_signal_g(void);
void sk_vspace_ctx_signal_h(void);
void sk_vspace_ctx_merge_dispatch(void);
void sk_buf_size_calc(void);
void sk_buf_stringify(void);
void sk_thunk_ctx_0024d9a8(void);
void sk_vspace_ctx_inject(void);
void sk_vspace_ctx_decode(void);
ulong sk_pte_flag_build(void);
long sk_utf8_len(byte *s);
void sk_utf8_encode_fwd(void);
void sk_region_decode(void);
void sk_vspace_ctx_op_commit_b(void);
void sk_vspace_ctx_op_commit_c2(void);
long sk_ptr_follow(long p, uint off);
long sk_ptr_load32(long p, long off);
void sk_pte_encode_table(long src, ulong *dst, long flags, long keep);
void sk_pte_encode_table2(long src, uint64_t *dst, long flags, long keep);
void sk_pte_emit_desc_a(void);
void sk_pte_emit_desc_b(void);
void sk_pte_follow_index(void);
void sk_pte_chain_walk(void);
void sk_pte_store_head(char a, uint flags, uint64_t b, char c);
long sk_ptr_align_offset(uint64_t a, long p);
void sk_buf_store_aligned32(uint32_t v);
void sk_buf_finalize(void);
void sk_buf_trim(void);
void sk_buf_finalize2(void);

/* ========================================================================= */
/* FUN_00248b48 @ 0x00248b48   (est. sk_vspace_key_init_a)
 * Ghidra: undefined FUN_00248b48(void)
 * PAC/key-slot init: samples a random byte, folds it against the constant
 * key-material word pair through the shared key-derivation helper FUN_0034d264,
 * then runs the main op-dispatch and the Swift epilogue. Side effect: establishes
 * the derived key material for the caller's vspace operation context.
 * Confidence: low (no string identity; behavior inferred from the constant).
 */
void sk_vspace_key_init_a(void)
{
    byte rand_byte;

    rand_byte = (byte)sk_rt_00348c48();                    /* FUN_00348c48 */
    sk_rt_0034d264(rand_byte, SK_KEYM_HI, rand_byte ^ SK_KEYM_LO); /* FUN_0034d264 */
    sk_vspace_op_dispatch();                               /* FUN_00248b94 */
    sk_rt_001a8564();                                      /* FUN_001a8564 */
}

/* ========================================================================= */
/* FUN_00248b94 @ 0x00248b94   (est. sk_vspace_op_dispatch)
 * Ghidra: undefined FUN_00248b94(void)
 * Central vspace operation dispatcher. Reads the operation kind from the top
 * three bits of the incoming descriptor word (stack arg 0x40>>61) and, per kind,
 * validates an associated region (FUN_0024acec) and calls the shared unmapping
 * helper (FUN_000dbdf4) with the computed range, or asserts canonical zeros for
 * the "unmap all" pseudo-region (0xa000000000000000). Loops while a follow-up
 * op word is pending (FUN_00353abc). Never returns on validation failure.
 * Confidence: low (decompiler-inlined stack/extraout state).
 */
void sk_vspace_op_dispatch(void)
{
    long r1, r2, r3, r4, r8;
    ulong kind_word, op_hi;
    long r9;

    sk_rt_0035638c();                                      /* FUN_0035638c */
    sk_rt_002298d4(*(long *)((long)&op_hi));               /* thunk_FUN_002298d4 */
    sk_rt_002488b4((void *)((long)&op_hi) + 3);            /* FUN_002488b4 */
    {
        /* FUN_003551c4 returns {base,end}; iterate while non-empty. */
        sk_pair_t rng = sk_rt_003551c4();                  /* FUN_003551c4 */
        while (rng.lo != 0 && rng.hi != rng.lo) {
            sk_rt_00248a34();                              /* FUN_00248a34 */
            r9 = 0;
            sk_pt_descriptor_build();                      /* FUN_00248d7c */
            /* r4/r3/r2/r1/r8 = stacked descriptor words (0x68/0x60/0x58/0x50/0x38) */
            r4 = 0; r3 = 0; r2 = 0; r1 = 0; r8 = 0;
            kind_word = (ulong)0 >> 0x3d;
            switch (kind_word) {
            case 1:
                kind_word = 1;
                /* fallthrough */
            default:
                sk_rt_002298d4(kind_word);                 /* thunk_FUN_002298d4 */
                sk_rt_002298d4(r8);                        /* thunk_FUN_002298d4 */
                break;
            case 2:
                sk_rt_003581d4(5);                         /* FUN_003581d4 */
                if (r3 != 0) {
                    /* note: r1<0 -> fatal via FUN_001afe4c */
                    r8 = (r2 - r1) - r4;
                    sk_rt_000dbdf4(0, r8);                 /* FUN_000dbdf4 */
                    r8 = (long)(*((long (*)())0))();       /* extraout_x8 */
                    if (r8 != 0) {
                        sk_rt_002298d4(r8);                /* thunk_FUN_002298d4 */
                        break;
                    }
                }
                break;
            case 3:
                sk_rt_003581d4(6);                         /* FUN_003581d4 */
                if (r3 != 0) {
                    r8 = (r2 - r1) - r4;
                    sk_rt_000dbdf4(0, r8);                 /* FUN_000dbdf4 */
                    r8 = (long)(*((long (*)())0))();
                    if (r8 != 0) {
                        sk_rt_002298d4(r8);
                        break;
                    }
                }
                break;
            case 4:
                sk_rt_003581d4(7);                         /* FUN_003581d4 */
                if (r3 != 0) {
                    r8 = (r2 - r1) - r4;
                    sk_rt_000dbdf4(0, r8);                 /* FUN_000dbdf4 */
                    r8 = (long)(*((long (*)())0))();
                    if (r8 != 0) {
                        sk_rt_002298d4(r8);
                        break;
                    }
                }
                break;
            case 5:
                /* "unmap all": canonical empty region 0xa000000000000000 with
                 * the 7 descriptor words all zero except 0x38==1. */
                r1 = 3;
                if (op_hi != 0xa000000000000000ull ||
                    ((r2 | r3 | r4 | 0) != 0)) {
                    r1 = 4;
                }
                r8 = 2;
                if (op_hi != 0xa000000000000000ull || 1 != 0) {
                    r8 = r1;
                }
                sk_rt_002298d4(r8);                        /* thunk_FUN_002298d4 */
                break;
            }
            if (r9 == 0) break;
            sk_rt_00353abc();                              /* FUN_00353abc */
            sk_rt_002298d4();                              /* thunk_FUN_002298d4 */
        }
    }
    sk_rt_00356370(0);                                     /* FUN_00356370 */
}

/* ========================================================================= */
/* FUN_00248d7c @ 0x00248d7c   (est. sk_pt_descriptor_build)
 * Ghidra: void FUN_00248d7c(void)
 * Builds a 7-word page-table descriptor struct (output via the caller's
 * x8 base). Starts from the per-CPU state (FUN_0008e518) and, keyed off the
 * descriptor kind byte (FUN_00248ae0), computes: index/attr words, a region
 * payload pointer, bounds, and attribute flags (0x6xxx / 0x8xxx / 0x4xxx
 * top bits). Handles the 0x7fffff "final" marker by re-reading FUN_0024ba38
 * and refreshing the ASID/PTE source. Writes the 7 words then restores the
 * per-CPU frame (FUN_0008e500).
 * Confidence: low (extraout_* register-merge artifacts from the decompiler).
 */
void sk_pt_descriptor_build(void)
{
    uint w13;
    long r7;
    ulong r4, r5;
    uint w1;
    ulong r10, r11, r8, r12;
    ulong r9;
    sk_pair_t cpu;

    cpu = sk_rt_0008e518();               /* FUN_0008e518 */
    r7 = (long)cpu.hi;
    r4 = cpu.lo;
    {
        byte kind = (byte)sk_rt_00248ae0().lo;  /* FUN_00248ae0 */
        r10 = 0; r11 = 0; r12 = 0; r5 = 0; r8 = 0;
        w13 = (uint)cpu.lo;
        r9 = 0xa000000000000000ull;
        switch (kind) {
        default:
            r10 = (ulong)(w13 & 0x7fffff);
            if ((w13 & 0x7fffff) != 0x7fffff) {
                r5 = sk_rt_0034c828().lo; /* FUN_0034c828 */
                r8 = 0; r9 = 0;
                break;
            }
            sk_rt_0034c920();             /* FUN_0034c920 */
            sk_buf_load_u32(0,0,0);        /* FUN_0024ba38 */
            r5 = sk_rt_0034c828(0).lo;    /* FUN_0034c828 */
            r10 = 0;
            r8 = 0;
            r9 = 0;
            r10 &= 0xffffffff;
            break;
        case 2:
            r10 = (ulong)(w13 & 0x7fffff);
            if ((w13 & 0x7fffff) != 0x7fffff) {
                r5 = sk_rt_0034c828().lo; /* FUN_0034c828 */
                r8 = 0;
                r9 = 0x2000000000000000ull;
                break;
            }
            sk_rt_0034c920();             /* FUN_0034c920 */
            sk_buf_load_u32(0,0,0);        /* FUN_0024ba38 */
            r5 = sk_rt_0034c828(0).lo;    /* FUN_0034c828 */
            r9 = 0x2000000000000000ull;
            r10 = 0;
            r8 = 0;
            r10 &= 0xffffffff;
            break;
        case 3:
            sk_rt_00350b18();             /* FUN_00350b18 */
            r10 = sk_buf_load_u32_at4();  /* FUN_0024bdbc */
            w1 = w13 >> 0x13 & 2;
            if ((r4 & 0x200000) != 0) w1 = 1;
            r11 = (ulong)w1;
            r12 = r7 + 0xc;
            if ((w13 >> 0x13 & 1) == 0) {
                r8 = 0; r5 = 0;
            } else {
                r11 = sk_pte_next_region_off(r4, r7); /* FUN_0024bddc */
                r8 = sk_pte_next_region(r4, r7); /* FUN_0024b9f0 */
                /* r12 = FUN_001ee0fc(8, r7 + (0x10|0x18) + 4) */
                r12 = sk_rt_001ee0fc(8, 0).lo; /* FUN_001ee0fc */
                if ((w13 >> 4 & 1) == 0) r5 = 0;
                else {
                    sk_pte_next_region_off(r4, r7);  /* FUN_0024bddc */
                    r5 = sk_rt_0035abb0().lo; /* FUN_0035abb0 */
                }
                r8 = r11 + (r8 & 0x3fffffffffffffff);
            }
            r9 = r11 | 0x6000000000000000ull;
            if ((r4 & 0x800000) == 0) r9 = r11 | 0x8000000000000000ull;
            if ((r4 & 0x400000) == 0) r9 = r11 | 0x4000000000000000ull;
            break;
        case 4:
            break;
        case 5:
            r5 = sk_rt_0034c828().lo;     /* FUN_0034c828 */
            r10 = 1;
            r8 = 0; r9 = 0;
            break;
        case 6:
            r5 = sk_rt_0034c828().lo;     /* FUN_0034c828 */
            r10 = 2;
            r8 = 0; r9 = 0;
            break;
        }
        /* Output the 7-word descriptor struct via the caller's base. */
        {
            ulong *out = (ulong *)0;
            out[0] = r10;
            out[1] = r9;
            out[2] = r12;
            out[3] = r11;
            out[4] = r8;
            out[5] = r12;
            out[6] = r5;
        }
    }
    sk_rt_0008e500(0);                    /* FUN_0008e500 */
}

/* ========================================================================= */
/* FUN_00248f64 @ 0x00248f64   (est. sk_vspace_pte_compare)
 * Ghidra: uint FUN_00248f64(long param_1,long param_2)
 * Returns 1 if the two vspace/PTE identifiers are equal; otherwise locks,
 * compares a per-context word against a table entry, and on a fresh ASID
 * allocates a context (FUN_0036b270) and validates it (FUN_00247454).
 * Confidence: low.
 */
uint sk_vspace_pte_compare(long a, long b)
{
    uint u;
    if (a == b) {
        u = 1;
    } else {
        sk_rt_003504d0();                 /* FUN_003504d0 */
        sk_rt_0007c198();                 /* FUN_0007c198 */
        if (0 == *(long *)0) {            /* extraout_x16 == *extraout_x1 */
            sk_rt_0036b270();             /* FUN_0036b270 */
            sk_rt_0007c1c4();             /* FUN_0007c1c4 */
            u = (uint)sk_rt_00247454().lo; /* FUN_00247454 */
        } else {
            u = 0;
        }
    }
    return u & 1;
}

/* ========================================================================= */
/* FUN_00248ff0 @ 0x00248ff0   (est. sk_vspace_key_init_fwd_a)
 * Ghidra: void FUN_00248ff0(void)
 * Forwarder to sk_vspace_key_init_a (FUN_00248b48).
 * Confidence: medium (trivial forwarder).
 */
void sk_vspace_key_init_fwd_a(void)
{
    sk_vspace_key_init_a();               /* FUN_00248b48 */
}

/* ========================================================================= */
/* FUN_00249014 @ 0x00249014   (est. sk_vspace_op_dispatch_fwd)
 * Ghidra: void FUN_00249014(void)
 * Forwarder to sk_vspace_op_dispatch (FUN_00248b94).
 * Confidence: medium (trivial forwarder).
 */
void sk_vspace_op_dispatch_fwd(void)
{
    sk_vspace_op_dispatch();              /* FUN_00248b94 */
}

/* ========================================================================= */
/* FUN_00249038 @ 0x00249038   (est. sk_vspace_key_init_wrap)
 * Ghidra: void FUN_00249038(void)
 * Wrapper: opens a Swift scope (FUN_001a84f4), runs the op dispatch, then the
 * Swift epilogue (FUN_001a8564).
 * Confidence: low.
 */
void sk_vspace_key_init_wrap(void)
{
    uint64_t stack_buf[9];
    sk_rt_001a84f4(stack_buf);            /* FUN_001a84f4 */
    sk_vspace_op_dispatch();     /* FUN_00248b94 */
    sk_rt_001a8564();                     /* FUN_001a8564 */
}

/* ========================================================================= */
/* FUN_00249078 @ 0x00249078   (est. sk_vspace_pte_cmp_ref)
 * Ghidra: uint FUN_00249078(undefined8 *param_1,undefined8 *param_2)
 * Dereferences both capability words and compares them (FUN_00248f64).
 * Confidence: low.
 */
uint sk_vspace_pte_cmp_ref(uint64_t *a, uint64_t *b)
{
    return sk_vspace_pte_compare(*a, *b) & 1;
}

/* ========================================================================= */
/* FUN_0024907c @ 0x0024907c   (est. sk_vspace_pte_cmp_ref2)
 * Ghidra: uint FUN_0024907c(undefined8 *param_1,undefined8 *param_2)
 * Same comparison as sk_vspace_pte_cmp_ref.
 * Confidence: low.
 */
uint sk_vspace_pte_cmp_ref2(uint64_t *a, uint64_t *b)
{
    return sk_vspace_pte_compare(*a, *b) & 1;
}

/* ========================================================================= */
/* FUN_002490a0 @ 0x002490a0   (est. sk_vspace_ctx_free_a)
 * Ghidra: void FUN_002490a0(void)
 * Calls FUN_001dbffc with the current x20 payload; frees a context.
 * Confidence: low.
 */
void sk_vspace_ctx_free_a(void)
{
    sk_rt_001dbffc(*(void **)0);          /* FUN_001dbffc (arg = *unaff_x20) */
}

/* ========================================================================= */
/* FUN_002490a4 @ 0x002490a4   (est. sk_vspace_ctx_free_b)
 * Ghidra: void FUN_002490a4(void)
 * Same as sk_vspace_ctx_free_a.
 * Confidence: low.
 */
void sk_vspace_ctx_free_b(void)
{
    sk_rt_001dbffc(*(void **)0);          /* FUN_001dbffc */
}

/* ========================================================================= */
/* FUN_002490c8 @ 0x002490c8   (est. sk_vspace_ctx_state_merge)
 * Ghidra: void FUN_002490c8(long param_1)
 * Merges the state byte returned by the vtable+0x78 selector of the current
 * object (x20) and of param_1; dispatches 3x3 combos to 0031cd00/0031cc6c/
 * 0031cc54 (all preceded by FUN_00357e64) to fold the two contexts together.
 * Confidence: low.
 */
void sk_vspace_ctx_state_merge(long other)
{
    char mine = (char)((*(long (**)(void))(*(long *)0 + 0x78))());
    char theirs = (char)((*(long (**)(void))(other + 0x78))());
    if (theirs != '\0') {
        if (theirs == '\x01') {
            if (mine == '\0') return;
            if (mine == '\x01') {
                sk_rt_00357e64();         /* FUN_00357e64 */
                sk_rt_0031cd00();         /* FUN_0031cd00 */
                return;
            }
        }
        sk_rt_00357e64();                 /* FUN_00357e64 */
        sk_rt_0031cc6c();                 /* FUN_0031cc6c */
        return;
    }
    sk_rt_00357e64();                     /* FUN_00357e64 */
    sk_rt_0031cc54();                     /* FUN_0031cc54 */
}

/* ========================================================================= */
/* FUN_0024917c @ 0x0024917c   (est. sk_vspace_ctx_commit)
 * Ghidra: void FUN_0024917c(void)
 * Commits the current context: reads state fields off two vtable-derived
 * objects (+0x70/+0x68), then either installs the commit frame and schedules
 * FUN_0031ca54, or builds an alternate frame with FUN_0031cc54 fields and
 * continues via sk_vspace_ctx_commit (FUN_00249294).
 * Confidence: low.
 */
void sk_vspace_ctx_commit(void)
{
    uint64_t f1, f2, f3;

    sk_rt_00353b10();                     /* FUN_00353b10 */
    sk_rt_0007c0c4();                     /* FUN_0007c0c4 */
    sk_rt_003549d8();                     /* FUN_003549d8 */
    f2 = *(uint64_t *)(0 + 0x70);         /* extraout_x16+0x70 */
    f1 = *(uint64_t *)(0 + 0x70);         /* extraout_x9+0x70 */
    f3 = *(uint64_t *)(0 + 0x68);         /* extraout_x9+0x68 */
    sk_rt_00351b04();                     /* FUN_00351b04 */
    {
        /* branch on ZR flag set by preceding call */
        long cb = 0;
        if (cb) {
            (*sk_hook_00658c00)();        /* DAT_00658c00 */
            sk_rt_00358298();             /* FUN_00358298 */
            *(uint64_t *)(0 - 0x28) = f1;
            *(uint64_t *)(0 - 0x30) = f3;
            *(uint64_t *)(0 - 0x20) = 0;
            *(uint64_t *)(0 - 0x18) = f3;
            *(uint64_t *)(0 - 0x10) = f2;
            sk_rt_00248860(sk_rt_0031ca54); /* FUN_00248860(FUN_0031ca54) */
        } else {
            (*sk_hook_00658c00)();        /* DAT_00658c00 */
            f1 = sk_rt_00355b38().lo;     /* FUN_00355b38 */
            *(uint64_t *)(0 - 0x20) = f3;
            *(uint64_t *)(0 - 0x18) = f2;
            *(uint64_t *)(0 - 0x10) = f1;
            sk_rt_00354714();             /* FUN_00354714 */
            sk_vspace_ctx_commit2();      /* FUN_00249294 */
        }
    }
}

/* ========================================================================= */
/* FUN_00249294 @ 0x00249294   (est. sk_vspace_ctx_commit2)
 * Ghidra: void FUN_00249294(void)
 * Finishes a Swift buffer-pointer commit: computes an aligned scratch region
 * from the current descriptor (+0x40 length) and either calls the buffer
 * handler (vtable+0x20 of the object) to advance it, or traps a negative-size
 * UnsafeRawBufferPointer with a Swift fatal error.
 * Confidence: low.
 */
void sk_vspace_ctx_commit2(void)
{
    long obj_base, len, sp;
    long *frame;

    obj_base = *(long *)(0 - 8);          /* in_x4-8 */
    len = (*sk_hook_00658c00)().lo;       /* DAT_00658c00 */
    sp = 0 - (uint64_t)(0 + 0xf & ~0xfffffffffffffff0ull);
    {
        long hdr = *(long *)(*(long *)(0 - 8) + 0x40);  /* *(in_x3-8)+0x40 */
        if (-1 < hdr) {
            (*(long (**)(long, long, long))0)(len, len + hdr, (long)(0xffffffffffffffc0 + sp));
            if (0 != 0) {                  /* unaff_x21 */
                (*(long (**)(long, long, long))(obj_base + 0x20))(
                    0, (long)(0xffffffffffffffc0 + sp), 0);
            }
            return;
        }
        /* negative-size buffer: Swift fatal error, never returns */
        *(uint32_t *)((char *)0 + sp) = 1;
        *(uint64_t *)((char *)0 + sp) = 0x4c1;
        *(char *)((char *)0 + sp) = 2;
        sk_rt_fatal_001afe4c(0);          /* FUN_001afe4c "Fatal error"/0x4c1 */
    }
}

/* ========================================================================= */
/* FUN_002493c8 @ 0x002493c8   (est. sk_alloc_ctx)
 * Ghidra: void FUN_002493c8(undefined8 param_1,undefined8 param_2,uint param_3,
 *                           undefined8 param_4)
 * Allocates a new vspace context. Pulls the current op descriptor, and either
 * forwards through the empty-region path (dispatch to vtable+0x10), or sizes
 * and allocates (FUN_0036a804 / FUN_003d31f8) a block and links it, or takes
 * the shared/expand path via sk_vspace_map_dispatch (FUN_0024963c) when the
 * param_3 "expand" bit (bit 16) is set.
 * Confidence: low.
 */
void sk_alloc_ctx(void)
{
    sk_pair_t d;
    uint64_t u1;
    long l4;

    d = sk_rt_00353cfc();                 /* FUN_00353cfc */
    u1 = sk_rt_0031dc0c(0, 0, 0x674330, 0x66d208).lo;  /* FUN_0031dc0c */
    sk_rt_0034ab20();                     /* FUN_0034ab20 */
    sk_rt_0007c1a4();                     /* FUN_0007c1a4 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034b0c4();                     /* FUN_0034b0c4 */
    if (d.lo == 0 || d.hi == d.lo) {
        sk_rt_0034c664();                 /* FUN_0034c664 */
        (*(long (**)(uint64_t, uint64_t, uint64_t))(0 + 0x10))(0, 0, 0);
    } else {
        /* param_3 >> 16 & 1 == 0 -> sized allocation path */
        sk_vspace_ctx_lock_c(d.hi);       /* FUN_0024c7bc */
        sk_rt_00352efc();                 /* FUN_00352efc */
        sk_rt_001ee0fc();                 /* FUN_001ee0fc */
        (*sk_hook_00658c00)(1);           /* DAT_00658c00 */
        if (0 == 0x3f) {                  /* extraout_x13 == 0x3f */
            sk_rt_00348c18();             /* FUN_00348c18 */
            sk_rt_0034a2f8();             /* FUN_0034a2f8 */
            sk_rt_fatal_001afe4c();       /* FUN_001afe4c */
        }
        l4 = 0;
        if (l4 < 0x401) {
            (*sk_hook_00658c00)();        /* DAT_00658c00 */
            sk_rt_00358278();             /* FUN_00358278 */
            sk_rt_00353eac();             /* FUN_00353eac */
            sk_rt_0035aa18();             /* FUN_0035aa18 */
        } else {
            sk_rt_0036a804(l4, 0xffffffffffffffff); /* FUN_0036a804 */
            sk_rt_00353eac();             /* FUN_00353eac */
            sk_rt_0035aa18();             /* FUN_0035aa18 */
            sk_rt_00012568(0, 0xffffffffffffffff, 0xffffffffffffffff); /* thunk */
        }
        sk_rt_0027ed7c(0, u1);            /* FUN_0027ed7c */
    }
    sk_rt_00353d14(0);                    /* FUN_00353d14 */
}

/* ========================================================================= */
/* FUN_0024963c @ 0x0024963c   (est. sk_vspace_map_dispatch)
 * Ghidra: void FUN_0024963c(void)
 * Per-CPU vspace map dispatch. Loads the per-CPU state (FUN_0008e518), locks,
 * builds a descriptor (FUN_00248d7c) and switches on the operation kind
 * (stack word 0x30>>61): kind 1 walks the per-CPU table (FUN_000867a8) and
 * calls the page-table walker; kinds 2-4 look up a region (FUN_0024aa50) and
 * invoke its vtable handler; kind 5 validates an empty/one-region special
 * mapping and faults via the region handler (FUN_0024c2ec) on success or
 * panics on mismatch. Restores the per-CPU frame at exit.
 * Confidence: low.
 */
void sk_vspace_map_dispatch(void)
{
    sk_pair_t cpu;
    long *pcpu;
    long lvar;

    cpu = sk_rt_0008e518();               /* FUN_0008e518 */
    pcpu = (long *)cpu.lo;
    sk_rt_0007c028(pcpu, 0, 0);           /* FUN_0007c028 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    sk_rt_003489c0();                     /* FUN_003489c0 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034b540();                     /* FUN_0034b540 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034b758();                     /* FUN_0034b758 */
    sk_pt_descriptor_build();             /* FUN_00248d7c */
    {
        ulong kind = (ulong)0 >> 0x3d;
        switch (kind) {
        case 1:
            sk_rt_000867a8(*pcpu + 0);    /* FUN_000867a8 */
            sk_rt_0036a1a0();             /* FUN_0036a1a0 */
            sk_rt_00351e84();             /* FUN_00351e84 */
            break;
        case 2: case 3: case 4:
            {
                sk_pair_t r = sk_rt_0035060c();  /* FUN_0035060c */
                long h = sk_vspace_ctx_reserve(); /* FUN_0024aa50 */
                (*(long (**)(long *, long, long))(h))(pcpu, 0, 0);
                (*(long (**)(long))(0 + 0x20))(0);
                break;
            }
        case 5:
            /* empty/one-page special map */
            sk_rt_0034b3e8();             /* FUN_0034b3e8 */
            {
                int ok = (int)((*(long (**)(long *, uint64_t))(0 + 0x58))(pcpu, 0));
                if (ok != 0) {
                    *(char *)0 = 1;       /* *in_x3 = 1 */
                    (*sk_hook_00658c00)();/* DAT_00658c00 */
                    sk_rt_00358228();     /* FUN_00358228 */
                    sk_rt_00359024();     /* FUN_00359024 */
                    sk_vspace_ctx_perm_mod(); /* FUN_0024c2ec */
                    break;
                }
            }
            /* mismatch path -> panic (noreturn) */
            sk_rt_00351e84();             /* FUN_00351e84 */
            sk_rt_00350aa0();             /* FUN_00350aa0 */
            break;
        default:
            (*sk_hook_00658c00)();        /* DAT_00658c00 */
            sk_rt_00359024(pcpu);         /* FUN_00359024 */
            sk_rt_00354714();             /* FUN_00354714 */
            sk_vspace_ctx_commit2();      /* FUN_00249294 */
            break;
        }
    }
    sk_rt_0008e500(cpu.hi);               /* FUN_0008e500 */
}

/* ========================================================================= */
/* FUN_00249a64 @ 0x00249a64   (est. sk_vspace_perm_check_a)
 * Ghidra: void FUN_00249a64(void)
 * Permission gate for the map path: checks the per-CPU id against the owner
 * mask at object+0x50 and the presence bit at +0x48; on a live owned object
 * recurses into sk_vspace_map_dispatch (FUN_0024963c) and records the result
 * word; on a missing/foreign object raises the deny+panic sequence. Never
 * returns on the deny path.
 * Confidence: low.
 */
void sk_vspace_perm_check_a(void)
{
    uint cpu;
    long ctx;

    cpu = (uint)sk_rt_0008e518().lo;      /* FUN_0008e518 */
    sk_rt_00349b00();                     /* FUN_00349b00 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    ctx = sk_rt_003493ac();               /* FUN_003493ac */
    if (ctx == 0) {
        sk_rt_00353498();                 /* FUN_00353498 */
        sk_rt_00154148();                 /* FUN_00154148 */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c (brk 0x249c08) */
    }
    if ((*(uint *)(0 + 0x50) & cpu & 0xff) == 0) {
        if (*(long *)(0 + 0x48) != 0) {
            sk_rt_0035aa9c();             /* FUN_0035aa9c */
            sk_rt_00351790();             /* FUN_00351790 */
            sk_rt_0034d024();             /* FUN_0034d024 */
            sk_rt_00154148();             /* FUN_00154148 */
            if ((*(uint *)(*(long *)(0 - 8) + 0x50) & cpu & 0xff) != 0) {
                goto deny;
            }
            if (*(long *)(*(long *)(0 - 8) + 0x48) != 0) {
                sk_rt_0035aa9c();         /* FUN_0035aa9c */
                sk_vspace_map_dispatch(); /* FUN_0024963c */
                sk_rt_003508cc(*(uint64_t *)(0 + 8)); /* FUN_003508cc */
                (*(long (**)(void))(0))();/* extraout_x8_01 */
                sk_rt_0008e500(0);        /* FUN_0008e500 */
                return;
            }
        }
        sk_rt_00350410();                 /* FUN_00350410 */
        sk_rt_00348074();                 /* FUN_00348074 */
        sk_rt_00351be0();                 /* FUN_00351be0 */
    } else {
deny:
        sk_rt_00350410();                 /* FUN_00350410 */
        sk_rt_003488bc();                 /* FUN_003488bc */
        sk_rt_00349644();                 /* FUN_00349644 */
        sk_rt_0034fbe4();                 /* FUN_0034fbe4 */
    }
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c (noreturn) */
}

/* ========================================================================= */
/* FUN_00249c08 @ 0x00249c08   (est. sk_vspace_iterate_regions)
 * Ghidra: void FUN_00249c08(undefined8 param_1,undefined8 param_2,uint param_3,
 *                           long param_4)
 * Iterates the vspace region list (guard FUN_00041138, lock FUN_002488b4);
 * while a next-region descriptor (FUN_00248a34) matches the "present + mapped"
 * tag, computes the payload pointer (offset by 0x10/0x18 per flags), validates
 * alignment, and invokes the region's vtable handler with (payload, size).
 * Continues while param_4 stays non-zero.
 * Confidence: low.
 */
void sk_vspace_iterate_regions(void)
{
    long next;

    sk_rt_00041138();                     /* FUN_00041138 */
    sk_rt_002488b4((void *)0);            /* FUN_002488b4 */
    {
        sk_pair_t d = sk_rt_00248a34();   /* FUN_00248a34 */
        next = 0;
        do {
            if ((d.lo & 0x7f080000) == 0x2080000) {
                long sz = 0x10;
                if ((d.lo & 0x400000) != 0) sz = 0x18;
                long payload = (long)d.hi + sz;
                if ((((ulong)(payload + 0xc) & 7) != 0) ||
                    ((*(uint64_t *)(payload + 0xc)) & 7) != 0) {
                    sk_rt_003488bc(1);    /* FUN_003488bc */
                    sk_rt_00349eb8();     /* FUN_00349eb8 */
                }
                uint64_t *pp = (uint64_t *)(payload + 0xc);
                long (*fn)(void) = (long (*)(void))*pp;
                if (fn != (long (*)(void))0) {
                    if ((ulong)(payload + 4) & 7) {
                        sk_rt_003488bc(1);
                        sk_rt_00349eb8();
                    }
                    uint64_t meta = *(uint64_t *)(payload + 4);
                    long argp = payload + 0x14;
                    if ((d.lo & 0x10) != 0) argp = payload + 0x1c;
                    long skip = meta >> 0x3b & 8;
                    long size = (meta & 0x3fffffffffffffff);
                    if ((d.lo >> 4 & 1) != 0)
                        size -= *(long *)(payload + 0x1c + skip + -8);
                    (*(long (**)(long, long))(fn))(argp + skip, size);
                }
            }
            next = next;   /* param_4 kept while non-zero */
        } while (0);
    }
    sk_rt_0035847c();                     /* FUN_0035847c */
}

/* ========================================================================= */
/* FUN_00249e20 @ 0x00249e20   (est. sk_vspace_map_dispatch2)
 * Ghidra: void FUN_00249e20(void)
 * Second map dispatch: takes per-CPU state, builds the descriptor, and
 * switches on the kind word. Kind 1 frees and re-reserves the head pointer;
 * kind 3 rebuilds via sk_pt_region_build2 (FUN_0024ab58) + sk_vspace_ctx_reserve
 * and advances; kind 4 walks a range via sk_pt_region_build3 (FUN_0024aad8)
 * and commits the new head (FUN_0024b64c); kind 5 faults with code 0x8b5 if a
 * "final" empty descriptor is present. Restores per-CPU frame at exit.
 * Confidence: low.
 */
void sk_vspace_map_dispatch2(void)
{
    sk_pair_t cpu;
    long *pcpu;

    cpu = sk_rt_0008e518();               /* FUN_0008e518 */
    pcpu = (long *)cpu.lo;
    sk_rt_00350488();                     /* FUN_00350488 */
    sk_rt_00310d68();                     /* FUN_00310d68 */
    sk_rt_00348e60();                     /* FUN_00348e60 */
    sk_rt_0007c1a4();                     /* FUN_0007c1a4 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034bdfc();                     /* FUN_0034bdfc */
    sk_rt_00349b00();                     /* FUN_00349b00 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    sk_rt_00348a34();                     /* FUN_00348a34 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034b8bc();                     /* FUN_0034b8bc */
    sk_rt_0034b804();                     /* FUN_0034b804 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    sk_rt_003497b4();                     /* FUN_003497b4 */
    sk_rt_00352738();                     /* FUN_00352738 */
    sk_rt_003511c0(0, 0);                 /* FUN_003511c0 */
    sk_pt_descriptor_build();             /* FUN_00248d7c */
    {
        ulong kind = (ulong)0 >> 0x3d;
        switch (kind) {
        case 1:
            pcpu = (long *)((long)pcpu + 0);
            sk_rt_00350488();             /* FUN_00350488 */
            sk_rt_00331f28();             /* FUN_00331f28 */
            sk_rt_0034c5fc();             /* FUN_0034c5fc */
            sk_vspace_ctx_alloc_obj();    /* FUN_0024b1d8 */
            sk_rt_0036b118(*(uint64_t *)0); /* FUN_0036b118 */
            break;
        case 2:
            sk_rt_fatal_001afe4c();       /* brk 0x24a1ac, noreturn */
            break;
        case 3:
            sk_rt_0034e0d4();             /* FUN_0034e0d4 */
            sk_rt_00331fdc();             /* FUN_00331fdc */
            sk_rt_0034edf8();             /* FUN_0034edf8 */
            sk_vspace_ctx_lock_c(0);      /* FUN_0024ab58 */
            sk_rt_0034edf8();             /* FUN_0034edf8 */
            sk_vspace_ctx_reserve();      /* FUN_0024aa50 */
            sk_rt_00352474();             /* FUN_00352474 */
            sk_rt_0035119c();             /* FUN_0035119c */
            sk_rt_00351714(*(uint64_t *)(0 + 8)); /* FUN_00351714 */
            sk_rt_00351df0(0);            /* FUN_00351df0 */
            pcpu = (long *)(sk_vspace_ctx_alloc_obj() + 0); /* FUN_0024b3bc->commit */
            break;
        case 4:
            sk_rt_0034e0d4();             /* FUN_0034e0d4 */
            sk_rt_003320b8();             /* FUN_003320b8 */
            sk_rt_0034edf8();             /* FUN_0034edf8 */
            sk_vspace_ctx_lock_b(0);      /* FUN_0024aad8 */
            sk_rt_0034edf8();             /* FUN_0034edf8 */
            sk_vspace_ctx_reserve();      /* FUN_0024aa50 */
            sk_rt_0035481c();             /* FUN_0035481c */
            sk_rt_003514dc();             /* FUN_003514dc */
            sk_rt_00351e6c();             /* FUN_00351e6c */
            sk_rt_00351dfc(0);            /* FUN_00351dfc */
            sk_vspace_ctx_commit_b(); /* FUN_0024b64c */
            break;
        case 5:
            sk_rt_00351e84();             /* FUN_00351e84 */
            sk_rt_003515e4();             /* FUN_003515e4 */
            sk_rt_0034b2c8();             /* FUN_0034b2c8 */
            if (0) {                       /* uVar1 (kind==5) */
                sk_rt_003489dc(0x8b5);    /* FUN_003489dc */
                sk_rt_0034a2f8();         /* FUN_0034a2f8 */
                sk_rt_fatal_001afe4c();   /* FUN_001afe4c */
            }
            sk_rt_003508fc(*(uint64_t *)(0 + 8)); /* FUN_003508fc */
            break;
        default:
            pcpu = (long *)((long)pcpu + 0);
            break;
        }
    }
    sk_rt_0008e500(0, cpu.hi);            /* FUN_0008e500 */
}

/* ========================================================================= */
/* FUN_0024a1c8 @ 0x0024a1c8   (est. sk_iterate_fwd_a)
 * Ghidra: void FUN_0024a1c8(void)
 * Forwarder: iterates regions then FUN_0036b6ac.
 * Confidence: low.
 */
void sk_iterate_fwd_a(void)
{
    sk_vspace_iterate_regions();          /* FUN_00249c08 */
    sk_rt_0036b6ac();                     /* FUN_0036b6ac */
}

/* ========================================================================= */
/* FUN_0024a1cc @ 0x0024a1cc   (est. sk_iterate_fwd_b)
 * Ghidra: void FUN_0024a1cc(void)
 * Forwarder: iterates regions then FUN_0036b6ac.
 * Confidence: low.
 */
void sk_iterate_fwd_b(void)
{
    sk_vspace_iterate_regions();          /* FUN_00249c08 */
    sk_rt_0036b6ac();                     /* FUN_0036b6ac */
}

/* ========================================================================= */
/* FUN_0024a1f0 @ 0x0024a1f0   (est. sk_vspace_ctx_create)
 * Ghidra: void FUN_0024a1f0(undefined8 param_1)
 * Creates a vspace context object: allocates it via FUN_000dbe0c, zeroes the
 * ref slot, captures two vtable fields (+0xa0/+0x98), installs the object via
 * FUN_00248860(FUN_0031cbbc), refs it (FUN_0036b270) and frees the temp
 * (FUN_0036b118).
 * Confidence: low.
 */
void sk_vspace_ctx_create(void)
{
    long obj;

    sk_rt_000027e8();                     /* FUN_000027e8 */
    obj = sk_rt_000dbe0c(0x66ab28);       /* FUN_000dbe0c */
    *(uint64_t *)(obj + 0x10) = 0;
    {
        uint64_t f98 = *(uint64_t *)(0 + 0x98);  /* extraout_x16+0x98 */
        uint64_t fa0 = *(uint64_t *)(0 + 0xa0);  /* extraout_x16+0xa0 */
        sk_rt_00248860(0, sk_rt_0031cbbc, 0);    /* FUN_00248860(FUN_0031cbbc) */
        (void)f98; (void)fa0;
    }
    sk_rt_0036b270(*(uint64_t *)(obj + 0x10));   /* FUN_0036b270 */
    sk_rt_0036b118(obj);                  /* FUN_0036b118 */
    sk_rt_0009461c();                     /* FUN_0009461c */
}

/* ========================================================================= */
/* FUN_0024a290 @ 0x0024a290   (est. sk_alloc_ctx2)
 * Ghidra: void FUN_0024a290(undefined8 param_1,undefined8 param_2,
 *                           undefined4 param_3)
 * Sizes and allocates a fresh context block: computes the aligned size from
 * param_3 (via FUN_0024c7bc), allocates with FUN_0036a804 / FUN_003d31f8,
 * links it through FUN_0027ed08/FUN_0006a4c0 and commits the new head via
 * sk_vspace_ctx_alloc_commit (FUN_0024a804).
 * Confidence: low.
 */
void sk_alloc_ctx2(void)
{
    uint64_t u1;
    ulong sz;

    sk_rt_0035a7c0();                     /* FUN_0035a7c0 */
    {
        sk_pair_t k = sk_rt_00357198();   /* FUN_00357198 */
        (void)k;
    }
    sk_vspace_ctx_lock_c(0);              /* FUN_0024c7bc */
    sk_rt_00352efc();                     /* FUN_00352efc */
    u1 = sk_rt_001ee0fc().lo;             /* FUN_001ee0fc */
    if ((((uint)(-(int)__builtin_clz((uint)u1)) & 0x3f)) == 0x3f) {
        sk_rt_00348c18();                 /* FUN_00348c18 */
        sk_rt_0034a2f8();                 /* FUN_0034a2f8 */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
    sz = 1ull << ((uint)(-(int)__builtin_clz((uint)u1)) & 0x3f);
    if (0x400 < sz) {
        sk_pair_t chk = sk_rt_003d31f8(sz, 0x10); /* FUN_003d31f8 */
        if ((chk.lo & 1) == 0) {
            sk_rt_0036a804(sz, 0xffffffffffffffff); /* FUN_0036a804 */
            sk_rt_00357584();             /* FUN_00357584 */
            sk_rt_00012568(0, 0xffffffffffffffff, 0xffffffffffffffff); /* thunk */
            goto linked;
        }
    }
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_00357584();                     /* FUN_00357584 */
linked:
    sk_rt_0027ed08(0, 0);                 /* FUN_0027ed08 */
    u1 = sk_rt_0006a4c0(0, 0).lo;         /* FUN_0006a4c0 */
    sk_rt_00352ae4(u1, (sk_pair_t){0,0}); /* FUN_00352ae4 */
    sk_vspace_ctx_alloc_commit(); /* FUN_0024a804 */
    *(uint64_t *)0 = u1;                  /* *extraout_x8 = u1 */
    sk_rt_000026e8(0);                    /* FUN_000026e8 */
    sk_rt_00359f3c();                     /* FUN_00359f3c */
    sk_rt_0035a7d4(0);                    /* FUN_0035a7d4 */
}

/* ========================================================================= */
/* FUN_0024a428 @ 0x0024a428   (est. sk_vspace_ctx_mutate)
 * Ghidra: void FUN_0024a428(void)
 * Mutates the current vspace context: takes a region descriptor, prepares the
 * operation (FUN_00354708), and while the per-region "active" byte (x3+0x11)
 * is set, walks regions (FUN_00248a34, FUN_0024a648) accumulating offsets.
 * Writes the final cursor, and commits through FUN_00319a4c; on a missing
 * foreign owner it panics (noreturn).
 * Confidence: low.
 */
void sk_vspace_ctx_mutate(void)
{
    long r;

    sk_rt_0035ace8();                     /* FUN_0035ace8 */
    r = sk_rt_00354708();                 /* FUN_00354708 */
    if (r == 0) {
        /* ZEXT816(0): empty region pair */
    } else {
        if ((*(uint *)(*(long *)(0 - 8) + 0x50) & 0 & 0xff) != 0) {
            sk_rt_003488bc(1);            /* FUN_003488bc */
            sk_rt_00349644();             /* FUN_00349644 */
            sk_rt_0034fbe4();             /* FUN_0034fbe4 */
            sk_rt_fatal_001afe4c();       /* FUN_001afe4c */
        }
        if (*(long *)(*(long *)(0 - 8) + 0x48) == 0) {
            sk_rt_00348074(1);            /* FUN_00348074 */
            sk_rt_00351be0();             /* FUN_00351be0 */
            sk_rt_fatal_001afe4c();       /* FUN_001afe4c */
        }
        sk_rt_001a26e0();                 /* FUN_001a26e0 */
        sk_rt_00351790();                 /* FUN_00351790 */
        sk_rt_0034d024();                 /* FUN_0034d024 */
    }
    sk_rt_00351f40(0, 0);                 /* FUN_00351f40 */
    sk_vspace_ctx_prepare();              /* FUN_0024a5c0 */
    {
        /* iterate while active */
        sk_pair_t d = sk_rt_00248a34();   /* FUN_00248a34 */
        (void)d;
        sk_rt_0035a218();                 /* FUN_0035a218 */
        sk_rt_000e15d8(0);                /* FUN_000e15d8 */
        sk_vspace_perm_check_b(); /* FUN_0024a648 */
    }
    sk_rt_00319a4c(0);                    /* FUN_00319a4c */
    sk_rt_00154148();                     /* FUN_00154148 */
}

/* ========================================================================= */
/* FUN_0024a5c0 @ 0x0024a5c0   (est. sk_vspace_ctx_prepare)
 * Ghidra: void FUN_0024a5c0(void)
 * Prepares the vspace op: grabs the op descriptor via the global hook and the
 * lock helpers, then enables the operation and advances the program counter
 * (FUN_0022bd00).
 * Confidence: low.
 */
void sk_vspace_ctx_prepare(void)
{
    sk_rt_0034ee78();                     /* FUN_0034ee78 */
    sk_rt_00349a68();                     /* FUN_00349a68 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    sk_rt_00349178();                     /* FUN_00349178 */
    sk_rt_00353ba0();                     /* FUN_00353ba0 */
    sk_rt_00351488();                     /* FUN_00351488 */
    (*(long (**)(void))0)();              /* extraout_x8_00 */
    sk_rt_0034b730(0);                    /* FUN_0034b730 */
    sk_rt_0022bd00();                     /* FUN_0022bd00 */
}

/* ========================================================================= */
/* FUN_0024a648 @ 0x0024a648   (est. sk_vspace_perm_check_b)
 * Ghidra: void FUN_0024a648(void)
 * Second permission gate (mirror of sk_vspace_perm_check_a): checks owner mask
 * at +0x50 / presence at +0x48 of the current op object, recurses into
 * sk_vspace_map_dispatch on a live owned object, records the result word, else
 * raises the deny+panic sequence. Never returns on the deny path.
 * Confidence: low.
 */
void sk_vspace_perm_check_b(void)
{
    uint cpu;
    long ctx;

    cpu = (uint)sk_rt_0008e518().lo;      /* FUN_0008e518 */
    sk_rt_003494e8();                     /* FUN_003494e8 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    ctx = sk_rt_00349068();               /* FUN_00349068 */
    if (ctx == 0) {
        sk_rt_00352cc8(0, 0);             /* FUN_00352cc8 */
        sk_rt_00154148();                 /* FUN_00154148 */
        sk_rt_fatal_001afe4c();           /* brk 0x24a804 */
    }
    if ((*(uint *)(0 + 0x50) & cpu & 0xff) == 0) {
        if (*(long *)(0 + 0x48) != 0) {
            sk_rt_0035aa9c();             /* FUN_0035aa9c */
            sk_rt_00351790();             /* FUN_00351790 */
            sk_rt_0034d024();             /* FUN_0034d024 */
            sk_rt_00154148();             /* FUN_00154148 */
            if ((*(uint *)(*(long *)(0 - 8) + 0x50) & cpu & 0xff) != 0) goto deny;
            if (*(long *)(*(long *)(0 - 8) + 0x48) != 0) {
                sk_rt_0035aa9c();         /* FUN_0035aa9c */
                sk_vspace_map_dispatch(); /* FUN_0024963c */
                *(uint64_t *)0 = 0;       /* *in_x5 = in_x6 */
                sk_rt_003505e8(*(uint64_t *)(0 + 8)); /* FUN_003505e8 */
                (*(long (**)(void))0)();  /* extraout_x8_01 */
                sk_rt_0008e500(0);        /* FUN_0008e500 */
                return;
            }
        }
        sk_rt_00350410();                 /* FUN_00350410 */
        sk_rt_00348074();                 /* FUN_00348074 */
        sk_rt_00351be0();                 /* FUN_00351be0 */
    } else {
deny:
        sk_rt_00350410();                 /* FUN_00350410 */
        sk_rt_003488bc();                 /* FUN_003488bc */
        sk_rt_00349644();                 /* FUN_00349644 */
        sk_rt_0034fbe4();                 /* FUN_0034fbe4 */
    }
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c (noreturn) */
}

/* ========================================================================= */
/* FUN_0024a804 @ 0x0024a804   (est. sk_vspace_ctx_alloc_commit)
 * Ghidra: void FUN_0024a804(void)
 * Commits a freshly allocated context: locks, pushes the op frame, computes a
 * region range (FUN_00291d70) and reports it (FUN_000651bc). On success restores
 * the caller frame; otherwise traps (noreturn FUN_0011d7e8).
 * Confidence: low.
 */
void sk_vspace_ctx_alloc_commit(void)
{
    uint64_t u1;
    uint64_t loc[3];

    sk_rt_00084220();                     /* FUN_00084220 */
    u1 = sk_rt_0034b5a8();                /* FUN_0034b5a8 */
    sk_rt_0006b2ec(u1, u1);               /* FUN_0006b2ec */
    sk_rt_0007c028();                     /* FUN_0007c028 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    sk_rt_00348f50();                     /* FUN_00348f50 */
    {
        sk_pair_t r = sk_rt_00351984(0);  /* FUN_00351984 */
        (void)r;
    }
    sk_rt_00350530();                     /* FUN_00350530 */
    sk_rt_00310d04();                     /* FUN_00310d04 */
    sk_rt_00354714();                     /* FUN_00354714 */
    sk_rt_00291d70(loc);                  /* FUN_00291d70 */
    sk_rt_0035060c(*(uint64_t *)(0 + 8)); /* FUN_0035060c */
    u1 = sk_rt_000651bc(0, loc[0]).lo;    /* FUN_000651bc */
    sk_rt_00084234(u1, 0);                /* FUN_00084234 */
}

/* ========================================================================= */
/* FUN_0024a940 @ 0x0024a940   (est. sk_vspace_ctx_signal)
 * Ghidra: void FUN_0024a940(undefined8 param_1,undefined8 param_2,
 *                           undefined1 param_3)
 * Signals a context transition: FUN_003528cc then two dispatch calls with
 * param_3.
 * Confidence: low.
 */
void sk_vspace_ctx_signal(void)
{
    sk_rt_003528cc();                     /* FUN_003528cc */
    sk_rt_002298d4();                     /* thunk_FUN_002298d4 */
    sk_rt_002298d4(0);                    /* thunk_FUN_002298d4(param_3) */
}

/* ========================================================================= */
/* FUN_0024a970 @ 0x0024a970   (est. sk_vspace_key_init_b)
 * Ghidra: void FUN_0024a970(undefined8 param_1,undefined1 param_2)
 * PAC/key-slot init (variant B): samples a random byte, folds it with the
 * constant key-material pair through FUN_0034ec48, then the dispatch tail.
 * Confidence: low.
 */
void sk_vspace_key_init_b(void)
{
    byte rb = (byte)sk_rt_00348c48();     /* FUN_00348c48 */
    sk_rt_0034ec48(rb, SK_KEYM_HI, rb ^ SK_KEYM_LO); /* FUN_0034ec48 */
    sk_rt_002298d4();                     /* thunk_FUN_002298d4 */
    sk_rt_002298d4(0);                    /* thunk_FUN_002298d4(param_2) */
    sk_rt_001a8564();                     /* FUN_001a8564 */
}

/* ========================================================================= */
/* FUN_0024a9e4 @ 0x0024a9e4   (est. sk_vspace_ctx_forward)
 * Ghidra: void FUN_0024a9e4(void)
 * Opens a Swift scope, forwards the context through FUN_003567c8, and closes.
 * Confidence: low.
 */
void sk_vspace_ctx_forward(void)
{
    uint64_t stack_buf[9];
    sk_rt_001a84f4(stack_buf);            /* FUN_001a84f4 */
    sk_rt_003567c8();                     /* FUN_003567c8 */
    sk_rt_002298d4();                     /* thunk_FUN_002298d4 */
    sk_rt_00355458();                     /* FUN_00355458 */
    sk_rt_002298d4();                     /* thunk_FUN_002298d4 */
    sk_rt_001a8564();                     /* FUN_001a8564 */
}

/* ========================================================================= */
/* FUN_0024aa50 @ 0x0024aa50   (est. sk_vspace_ctx_reserve)
 * Ghidra: long FUN_0024aa50(void)
 * Reserves a context index: FUN_0034b430, lock FUN_00350530, asks the Swift
 * allocator (FUN_001ee0fc) for a slot and, if it came back non-zero, verifies
 * it via FUN_003705b0(&DAT_00020003). Returns the slot or traps.
 * Confidence: low.
 */
long sk_vspace_ctx_reserve(void)
{
    long slot;
    sk_rt_0034b430();                     /* FUN_0034b430 */
    sk_rt_00350530();                     /* FUN_00350530 */
    slot = sk_rt_001ee0fc().lo;           /* FUN_001ee0fc */
    sk_rt_003705b0(&(uint32_t){0x00020003}); /* FUN_003705b0 */
    if (slot != 0) return slot;
    sk_rt_00347f2c();                     /* FUN_00347f2c */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c (noreturn) */
}

/* ========================================================================= */
/* FUN_0024aad8 @ 0x0024aad8   (est. sk_vspace_ctx_lock_a)
 * Ghidra: void FUN_0024aad8(void)
 * Locks a context slot (LAB_00020004 selector via FUN_003704f4), trapping on
 * failure. unlock_x22==0 -> return; else fatal.
 * Confidence: low.
 */
void sk_vspace_ctx_lock_a(void)
{
    long slot = sk_rt_0034b430();         /* FUN_0034b430 */
    sk_rt_001ee0fc(0, slot + 8);          /* FUN_001ee0fc */
    sk_rt_00355b90();                     /* FUN_00355b90 */
    sk_rt_003704f4((void *)0x20004, 0, 0, 0); /* FUN_003704f4(LAB_00020004) */
    if (0 != 0) return;                    /* unaff_x22 */
    sk_rt_00347f2c();                     /* FUN_00347f2c */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024ab58 @ 0x0024ab58   (est. sk_vspace_ctx_lock_b)
 * Ghidra: void FUN_0024ab58(void)
 * Locks a context slot (0x2020004 selector, DAT_004f21b8 table via
 * FUN_003704f4), trapping on failure.
 * Confidence: low.
 */
void sk_vspace_ctx_lock_b(long p)
{
    long slot = sk_rt_0034b430();         /* FUN_0034b430 */
    sk_rt_001ee0fc(0, slot + 8);          /* FUN_001ee0fc */
    sk_rt_00355b90();                     /* FUN_00355b90 */
    sk_rt_003704f4((void *)0x2020004, 0, (void *)0x4f21b8, 0); /* FUN_003704f4 */
    if (0 != 0) return;                    /* unaff_x22 */
    sk_rt_00347f2c();                     /* FUN_00347f2c */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024abdc @ 0x0024abdc   (est. sk_vspace_ctx_lock_c)
 * Ghidra: void FUN_0024abdc(void)
 * Locks a context; traps if the slot is non-zero and also zero (unreachable
 * in practice). Mostly a no-op guard.
 * Confidence: low.
 */
void sk_vspace_ctx_lock_c(long p)
{
    long slot;
    sk_rt_0034da88();                     /* FUN_0034da88 */
    slot = sk_rt_001ee0fc().lo;           /* FUN_001ee0fc */
    if (slot != 0 && slot == 0) {
        sk_rt_00347f2c(0);                /* FUN_00347f2c */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
}

/* ========================================================================= */
/* FUN_0024ac34 @ 0x0024ac34   (est. sk_vspace_ctx_ref_a)
 * Ghidra: long FUN_0024ac34(long param_1)
 * Takes a reference to context field at +8 (FUN_001ee0fc), trapping if null.
 * Confidence: low.
 */
long sk_vspace_ctx_ref_a(long p)
{
    long ref = sk_rt_001ee0fc(0, p + 8).lo;  /* FUN_001ee0fc */
    if (ref != 0) return ref;
    sk_rt_00347f2c();                     /* FUN_00347f2c */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024ac90 @ 0x0024ac90   (est. sk_vspace_ctx_ref_b)
 * Ghidra: long FUN_0024ac90(long param_1)
 * Takes a reference to context field at +0x10, trapping if null.
 * Confidence: low.
 */
long sk_vspace_ctx_ref_b(long p)
{
    long ref = sk_rt_001ee0fc(0, p + 0x10).lo;  /* FUN_001ee0fc */
    if (ref != 0) return ref;
    sk_rt_00347f2c();                     /* FUN_00347f2c */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024acec @ 0x0024acec   (est. sk_vspace_ctx_ref_c)
 * Ghidra: long FUN_0024acec(long param_1)
 * Takes a reference to context field at +0x18, trapping if null.
 * Confidence: low.
 */
long sk_vspace_ctx_ref_c(long p)
{
    long ref = sk_rt_001ee0fc(0, p + 0x18).lo;  /* FUN_001ee0fc */
    if (ref != 0) return ref;
    sk_rt_00347f2c();                     /* FUN_00347f2c */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024ad48 @ 0x0024ad48   (est. sk_vspace_region_compare)
 * Ghidra: ulong FUN_0024ad48(long *param_1,long *param_2)
 * Compares two 7-word vspace region descriptors for equality. Keys off the
 * descriptor kind (word1>>61): kinds 0/1 compare the base word and kind;
 * kinds 2-4 compare base+kind plus (if a range is present) the end word and
 * the range-subsystem compare (FUN_0024ac90 / jumptable handler); kind 5
 * handles the canonical "empty" (0xa000000000000000, all words zero) and
 * "single-page" (0xa000000000000000, base==1) pseudo-descriptors by resolving
 * the region through FUN_00357dc4 and verifying the payload words (indices
 * 0,2,5,6) are all zero. Returns 1 on match, 0 otherwise; traps on malformed
 * overlapping ranges.
 * Confidence: low (decompiler NEON/CONCAT byte-merge artifacts simplified to
 *   the equivalent "words 5 and 6 are zero" checks).
 */
ulong sk_vspace_region_compare(long *a, long *b)
{
    long base = *a;
    ulong kind = (ulong)a[1];
    long w3 = a[3], w4 = a[4], w5 = a[5], w6 = a[6];
    ulong bkind;
    long *res;

    switch (kind >> 0x3d) {
    case 0:
    case 1:
        if ((ulong)b[1] >> 0x3d != (kind >> 0x3d)) return 0;
        return (ulong)(base == *b);
    case 2: case 3:
        bkind = (ulong)b[1];
        if (bkind >> 0x3d != (kind >> 0x3d)) return 0;
        break;
    case 4:
        bkind = (ulong)b[1];
        if (-0x6000000000000001 < (long)bkind) return 0;
        break;
    case 5:
        /* canonical empty region: base 0xa000000000000000, all other words 0 */
        if (kind == 0xa000000000000000ull && w3 == 0 && w4 == 0 &&
            base == 0 && w5 == 0 && w6 == 0 && a[2] == 0) {
            sk_rt_00357dc4();             /* FUN_00357dc4 */
            res = (long *)0;              /* extraout_x1_00 */
            if ((long)sk_rt_00357dc4() != -0x6000000000000000ull) return 0;
            /* payload words 5,6,0,2 must all be zero */
            if (res[5] != 0 || res[6] != 0 || res[0] != 0 || res[2] != 0) return 0;
            return 1;
        }
        /* canonical single-page region: base 0xa000000000000000, base==1 */
        if (kind == 0xa000000000000000ull && base == 1 &&
            w3 == 0 && w4 == 0 && w5 == 0 && a[2] == 0 && w6 == 0) {
            sk_rt_00357dc4();             /* FUN_00357dc4 */
            res = (long *)0;
            if ((long)sk_rt_00357dc4() != -0x6000000000000000ull || res[0] != 1) return 0;
        } else {
            sk_rt_00357dc4();             /* FUN_00357dc4 */
            res = (long *)0;
            if ((long)sk_rt_00357dc4() != -0x6000000000000000ull || res[0] != 2) return 0;
        }
        if (res[5] != 0 || res[6] != 0 || res[2] != 0) return 0;
        return 1;
    default:
        return 0;
    }

    /* kinds 2-4: base and kind must match, then range compare */
    if (base != *b || ((uint)bkind ^ (uint)kind) & 0xff) return 0;
    if (w5 == 0) return 1;
    if (b[5] == 0) return 1;
    {
        long bend = b[3];
        (void)bend;
        /* range-subsystem compare via FUN_0024ac90, then handler */
        sk_vspace_ctx_ref_b(0);           /* FUN_0024ac90 */
        if (w3 != 0 && b[3] != 0) {
            if (!__builtin_sub_overflow(w4 - w3, w6, (long *)0)) {
                long (*fn)(void) = (long (*)(void))0;
                sk_rt_0009461c(fn, 0, (w4 - w3) - w6); /* FUN_0009461c */
                return (ulong)fn();
            }
            sk_rt_fatal_001afe4c();       /* brk 0x24af78 */
        }
    }
    sk_rt_00347f2c();                     /* FUN_00347f2c */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024af98 @ 0x0024af98   (est. sk_vspace_region_build)
 * Ghidra: void FUN_0024af98(undefined8 param_1,undefined8 param_2,long param_3)
 * Builds a vspace region from the current 7-word descriptor: dispatches on the
 * kind (0/1 canonical, 2/3/4 mapped) to emit the region header via the lock
 * helpers, then for the mapped kinds resolves the payload and, when a follow-up
 * param_3 is present, computes the sub-range and calls the unmap helper
 * (FUN_00350a88), trapping on an empty base.
 * Confidence: low.
 */
void sk_vspace_region_build(void)
{
    ulong k = (ulong)0 >> 0x3d;
    long base = 0;

    sk_rt_00084220();                     /* FUN_00084220 */
    switch (k) {
    case 0: case 1:
        sk_rt_002298d4(k);                /* thunk_FUN_002298d4 */
        sk_rt_002298d4(base);             /* thunk_FUN_002298d4 */
        sk_rt_00084234(0);                /* FUN_00084234 */
        return;
    case 2: k = 5; break;
    case 3: k = 6; break;
    case 4: k = 7; break;
    case 5:
        if (0 == 0xa000000000000000ull) base = 2;   /* empty */
        else if (0 == 0xa000000000000000ull) base = 3; /* single */
        else base = 4;                              /* mapped */
        sk_rt_002298d4(k);
        sk_rt_002298d4(base);
        sk_rt_002298d4(k & 0xff);
        sk_rt_0034c5ac(0);                /* FUN_0034c5ac */
        sk_rt_00084234();                 /* FUN_00084234 */
        if (0 != 0) {                     /* param_3 */
            sk_rt_00353d70();             /* FUN_00353d70 */
            sk_rt_00352758();             /* FUN_00352758 */
            {
                long payload = sk_vspace_ctx_ref_c(0); /* FUN_0024acec */
                long sz = (0 - 0) - 0;
                sk_rt_00350a88(payload, sz);   /* FUN_00350a88 */
            }
            if (0 != 0) {
                sk_rt_002298d4();         /* thunk_FUN_002298d4 */
            }
        }
        return;
    default:
        k = 0;
        break;
    }
    sk_rt_002298d4(k);                    /* thunk_FUN_002298d4 */
    sk_rt_002298d4(base);                 /* thunk_FUN_002298d4 */
    sk_rt_002298d4(k & 0xff);             /* thunk_FUN_002298d4 */
    sk_rt_0034c5ac(0);                    /* FUN_0034c5ac */
    sk_rt_00084234();                     /* FUN_00084234 */
    if (0 != 0) {                         /* param_3 */
        sk_rt_00353d70();                 /* FUN_00353d70 */
        sk_rt_00352758();                 /* FUN_00352758 */
        {
            long payload = sk_vspace_ctx_ref_c(0);
            long sz = (0 - 0) - 0;
            sk_rt_00350a88(payload, sz);  /* FUN_00350a88 */
        }
        if (0 != 0) {
            sk_rt_002298d4();
        }
    }
}

/* ========================================================================= */
/* FUN_0024b144 @ 0x0024b144   (est. sk_vspace_key_init_c)
 * Ghidra: void FUN_0024b144(void)
 * PAC/key-slot init (variant C): random byte folded with the key-material pair
 * via FUN_0034d264, then sk_vspace_region_build + Swift epilogue.
 * Confidence: low.
 */
void sk_vspace_key_init_c(void)
{
    byte rb = (byte)sk_rt_00348c48();     /* FUN_00348c48 */
    sk_rt_0034d264(rb, SK_KEYM_HI, rb ^ SK_KEYM_LO); /* FUN_0034d264 */
    sk_vspace_region_build();             /* FUN_0024af98 */
    sk_rt_001a8564();                     /* FUN_001a8564 */
}

/* ========================================================================= */
/* FUN_0024b198 @ 0x0024b198   (est. sk_vspace_key_init_wrap2)
 * Ghidra: void FUN_0024b198(void)
 * Swift-scope wrapper over sk_vspace_region_build.
 * Confidence: low.
 */
void sk_vspace_key_init_wrap2(void)
{
    uint64_t stack_buf[9];
    sk_rt_001a84f4(stack_buf);            /* FUN_001a84f4 */
    sk_vspace_region_build();    /* FUN_0024af98 */
    sk_rt_001a8564();                     /* FUN_001a8564 */
}

/* ========================================================================= */
/* FUN_0024b1d8 @ 0x0024b1d8   (est. sk_vspace_ctx_alloc_obj)
 * Ghidra: long FUN_0024b1d8(void)
 * Allocates a vspace context object via FUN_0036a940, stores the two caller
 * words at +0x10/+0x18, and refs it twice.
 * Confidence: low.
 */
long sk_vspace_ctx_alloc_obj(void)
{
    long obj;
    sk_rt_0034b318();                     /* FUN_0034b318 */
    obj = sk_rt_0036a940();               /* FUN_0036a940 */
    *(uint64_t *)(obj + 0x10) = 0;        /* unaff_x23 */
    *(uint64_t *)(obj + 0x18) = 0;        /* unaff_x22 */
    sk_rt_0036a1a0();                     /* FUN_0036a1a0 */
    sk_rt_0036b270();                     /* FUN_0036b270 */
    sk_rt_0036b270();                     /* FUN_0036b270 */
    return obj;
}

/* ========================================================================= */
/* FUN_0024b260 @ 0x0024b260   (est. sk_vspace_ctx_free_obj)
 * Ghidra: void FUN_0024b260(void)
 * Releases a vspace context object: detaches its two payload words (+0x10/+0x18).
 * Confidence: low.
 */
void sk_vspace_ctx_free_obj(void)
{
    sk_rt_0036a20c(0 + 0x20);             /* FUN_0036a20c */
    sk_rt_0036b118(*(uint64_t *)(0 + 0x10)); /* FUN_0036b118 */
    sk_rt_0036b118(*(uint64_t *)(0 + 0x18)); /* FUN_0036b118 */
}

/* ========================================================================= */
/* FUN_0024b290 @ 0x0024b290   (est. sk_vspace_ctx_free_fwd_a)
 * Ghidra: void FUN_0024b290(void)
 * Forwarder: free obj, FUN_00002834, FUN_0036b6ac.
 * Confidence: low.
 */
void sk_vspace_ctx_free_fwd_a(void)
{
    sk_vspace_ctx_free_obj();             /* FUN_0024b260 */
    sk_rt_00002834();                     /* FUN_00002834 */
    sk_rt_0036b6ac();                     /* FUN_0036b6ac */
}

/* ========================================================================= */
/* FUN_0024b294 @ 0x0024b294   (est. sk_vspace_ctx_free_fwd_b)
 * Ghidra: void FUN_0024b294(void)
 * Forwarder: free obj, FUN_00002834, FUN_0036b6ac.
 * Confidence: low.
 */
void sk_vspace_ctx_free_fwd_b(void)
{
    sk_vspace_ctx_free_obj();             /* FUN_0024b260 */
    sk_rt_00002834();                     /* FUN_00002834 */
    sk_rt_0036b6ac();                     /* FUN_0036b6ac */
}

/* ========================================================================= */
/* FUN_0024b2b4 @ 0x0024b2b4   (est. sk_vspace_ctx_teardown)
 * Ghidra: void FUN_0024b2b4(void)
 * Tears down the current context: walks the op object, runs the two region
 * teardown passes (FUN_00351c88/FUN_0034baa8 via vtable handlers), frees the
 * object payload (+0x10), and re-links the head.
 * Confidence: low.
 */
void sk_vspace_ctx_teardown(void)
{
    uint64_t u2;
    long off;

    sk_rt_0007c0c4();                     /* FUN_0007c0c4 */
    u2 = *(uint64_t *)(0 + 0x40);         /* extraout_x16+0x40 */
    sk_rt_003499b4();                     /* FUN_003499b4 */
    sk_rt_00351408();                     /* FUN_00351408 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034baa8();                     /* FUN_0034baa8 */
    off = *(long *)(0 + 0x70);            /* extraout_x8+0x70 */
    sk_rt_00351e84();                     /* FUN_00351e84 */
    sk_rt_00351c88(0, (void *)(0 + off)); /* FUN_00351c88 */
    (*(long (**)(void))0)();              /* extraout_x9 */
    (*(long (**)(void))(0 + 0x20))();     /* vtable+0x20 */
    sk_rt_003510b8();                     /* FUN_003510b8 */
    sk_rt_0036b118(*(uint64_t *)(0 + 0x10)); /* FUN_0036b118 */
    (*(long (**)(void *))(0 + 8))((void *)(0 + off)); /* vtable+8 */
    sk_rt_00356310();                     /* FUN_00356310 */
}

/* ========================================================================= */
/* FUN_0024b3bc @ 0x0024b3bc   (est. sk_vspace_ctx_commit_a)
 * Ghidra: void FUN_0024b3bc(void)
 * Commits the vspace op (first phase): FUN_00084220, FUN_0034b5a8, computes a
 * descriptor (FUN_00359290), runs two pass helpers and the region store
 * (FUN_0024b410), then restores the caller frame.
 * Confidence: low.
 */
void sk_vspace_ctx_commit_a(void)
{
    uint64_t u1;
    sk_rt_00084220();                     /* FUN_00084220 */
    sk_rt_0034b5a8();                     /* FUN_0034b5a8 */
    u1 = sk_rt_00359290().lo;             /* FUN_00359290 */
    sk_rt_0034e55c();                     /* FUN_0034e55c */
    sk_rt_00353208();                     /* FUN_00353208 */
    sk_vspace_ctx_store_fields();         /* FUN_0024b410 */
    sk_rt_00084234(u1, 0);                /* FUN_00084234 */
}

/* ========================================================================= */
/* FUN_0024b410 @ 0x0024b410   (est. sk_vspace_ctx_store_fields)
 * Ghidra: void FUN_0024b410(undefined8 param_1..param_6)
 * Stores six caller words into the current context object (x20) at offsets
 * +2..+6, then emits the descriptor through the vtable+0x20 handler.
 * Confidence: low.
 */
void sk_vspace_ctx_store_fields(void)
{
    /* unaff_x20[2..6] = params 1..5 */
    sk_rt_003549d8();                     /* FUN_003549d8 */
    sk_rt_0034b07c(0, 0, *(uint64_t *)(0 + 0x40)); /* FUN_0034b07c */
    (*(long (**)(void *))(0 + 0x20))((void *)0);   /* vtable+0x20 */
}

/* ========================================================================= */
/* FUN_0024b47c @ 0x0024b47c   (est. sk_vspace_ctx_teardown2)
 * Ghidra: void FUN_0024b47c(void)
 * Full context teardown: takes per-CPU state, walks the op object, runs both
 * region teardown passes via the vtable handlers, frees the two payload words,
 * and restores the per-CPU frame.
 * Confidence: low.
 */
void sk_vspace_ctx_teardown2(void)
{
    uint64_t u1, u3, u4;
    long off50, off58, off70, off60;

    u1 = (uint64_t)sk_rt_0008e518().lo;   /* FUN_0008e518 */
    sk_rt_0007c0c4();                     /* FUN_0007c0c4 */
    u3 = *(uint64_t *)(0 + 0x38);         /* extraout_x16+0x38 */
    sk_rt_003499b4();                     /* FUN_003499b4 */
    sk_rt_00351408();                     /* FUN_00351408 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034b014();                     /* FUN_0034b014 */
    u4 = *(uint64_t *)(0 + 0x40);         /* extraout_x16_01+0x40 */
    sk_rt_0034b7e4();                     /* FUN_0034b7e4 */
    sk_rt_00351408();                     /* FUN_00351408 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034beb4();                     /* FUN_0034beb4 */
    sk_rt_003549d8();                     /* FUN_003549d8 */
    off58 = *(long *)(0 + 0x58);          /* extraout_x16_03+0x58 */
    sk_rt_003549d8();                     /* FUN_003549d8 */
    off70 = *(long *)(0 + 0x70);          /* extraout_x16_04+0x70 */
    sk_rt_00352bb0();                     /* FUN_00352bb0 */
    sk_rt_00356260(0, (void *)(0 + off70)); /* FUN_00356260 */
    (*(long (**)(void))0)();              /* extraout_x9 */
    sk_rt_000027e8();                     /* FUN_000027e8 */
    off50 = *(long *)(0 + 0x50);          /* extraout_x16_05+0x50 */
    sk_rt_00351e84();                     /* FUN_00351e84 */
    sk_rt_00353474(0, (void *)(0 + off50)); /* FUN_00353474 */
    (*(long (**)(void))0)();              /* extraout_x9_00 */
    {
        sk_pair_t r = sk_rt_0007c0c4();   /* FUN_0007c0c4 */
        (void)r;
    }
    sk_rt_003549d8();                     /* FUN_003549d8 */
    off60 = *(long *)(0 + 0x60);          /* extraout_x16_06+0x60 */
    sk_rt_00350618();                     /* FUN_00350618 */
    (*(long (**)(void))(0 + 0x58))();     /* vtable+0x58 */
    sk_rt_003514e8();                     /* FUN_003514e8 */
    (*(long (**)(void))(0 + 8))();        /* vtable+8 */
    sk_rt_00350630();                     /* FUN_00350630 */
    sk_rt_0036b118(*(uint64_t *)(0 + 0x10)); /* FUN_0036b118 */
    (*(long (**)(void *))(0 + 8))((void *)(0 + off50)); /* vtable+8 */
    (*(long (**)(void *))(0 + 8))((void *)(0 + off70)); /* vtable+8 */
    sk_rt_003548b8();                     /* FUN_003548b8 */
    sk_rt_0008e500(0, u1);                /* FUN_0008e500 */
}

/* ========================================================================= */
/* FUN_0024b64c @ 0x0024b64c   (est. sk_vspace_ctx_commit_b)
 * Ghidra: void FUN_0024b64c(void)
 * Commits the vspace op (second phase): same shape as sk_vspace_ctx_commit_a
 * but ends in sk_vspace_ctx_store_fields2 (FUN_0024b6a0).
 * Confidence: low.
 */
void sk_vspace_ctx_commit_b(void)
{
    uint64_t u1;
    sk_rt_00084220();                     /* FUN_00084220 */
    sk_rt_0034b5a8();                     /* FUN_0034b5a8 */
    u1 = sk_rt_00359290().lo;             /* FUN_00359290 */
    sk_rt_0034e55c();                     /* FUN_0034e55c */
    sk_rt_00353208();                     /* FUN_00353208 */
    sk_vspace_ctx_store_fields2();        /* FUN_0024b6a0 */
    sk_rt_00084234(u1, 0);                /* FUN_00084234 */
}

/* ========================================================================= */
/* FUN_0024b6a0 @ 0x0024b6a0   (est. sk_vspace_ctx_store_fields2)
 * Ghidra: void FUN_0024b6a0(void)
 * Stores the region payload and three owner words into the context object at
 * +2 and the two vtable-mapped offsets, emitting through vtable+0x20.
 * Confidence: low.
 */
void sk_vspace_ctx_store_fields2(void)
{
    long base;
    sk_pair_t d;

    base = 0;                             /* unaff_x20 */
    sk_rt_0034cc94();                     /* FUN_0034cc94 */
    d = sk_rt_00352188();                 /* FUN_00352188 */
    sk_rt_0034fbc4(*(uint64_t *)(0 + 0x50), d.lo, d.hi, *(uint64_t *)(0 + 0x38)); /* FUN_0034fbc4 */
    (*(long (**)(void *))(0 + 0x20))((void *)0); /* vtable+0x20 */
    sk_rt_000027e8();                     /* FUN_000027e8 */
    sk_rt_000027e8();                     /* FUN_000027e8 */
    sk_rt_000027e8();                     /* FUN_000027e8 */
    d = sk_rt_000027e8();                 /* FUN_000027e8 */
    sk_rt_0034fbc4(*(uint64_t *)(0 + 0x70), d.lo, d.hi, *(uint64_t *)(0 + 0x40)); /* FUN_0034fbc4 */
    (*(long (**)(void *))(0 + 0x20))((void *)0); /* vtable+0x20 */
    (void)base;
}

/* ========================================================================= */
/* FUN_0024b79c @ 0x0024b79c   (est. sk_vspace_ctx_forward2)
 * Ghidra: void FUN_0024b79c(void)
 * Swift-scope forwarder: FUN_001a84f4, FUN_003567c8, dispatch, epilogue.
 * Confidence: low.
 */
void sk_vspace_ctx_forward2(void)
{
    uint64_t stack_buf[9];
    sk_rt_001a84f4(stack_buf);            /* FUN_001a84f4 */
    sk_rt_003567c8();                     /* FUN_003567c8 */
    sk_rt_002298d4();                     /* thunk_FUN_002298d4 */
    sk_rt_001a8564();                     /* FUN_001a8564 */
}

/* ========================================================================= */
/* FUN_0024b7e4 @ 0x0024b7e4   (est. sk_pte_attr_nibble)
 * Ghidra: uint FUN_0024b7e4(uint param_1)
 * Maps the low two bits of the attribute word through a 4-nibble lookup table
 * 0x1020300, selecting one of 4 nibble values. Pure attribute selector.
 * Confidence: medium (deterministic table select, no external calls).
 */
uint sk_pte_attr_nibble(uint flags)
{
    return 0x1020300u >> (uint)((flags & 3) << 3);
}

/* ========================================================================= */
/* FUN_0024b7f8 @ 0x0024b7f8   (est. sk_pte_size_a)
 * Ghidra: ulong FUN_0024b7f8(uint param_1)
 * Computes the encoded size/payload of a PTE descriptor given its flags and the
 * current descriptor kind byte (FUN_00248ae0). Kind 3 (block) sizes 0x8/0xc/
 * 0x14/0x18 by the 0x400000/0x80000 bits; other kinds scale with the low 24
 * bits. Pure size computation.
 * Confidence: medium.
 */
ulong sk_pte_size_a(uint flags)
{
    byte kind = (byte)sk_rt_00248ae0().lo;   /* FUN_00248ae0 */
    ulong sz = 0;
    switch (kind) {
    case 1: case 2:
        sk_rt_0035854c(0);                /* FUN_0035854c */
        sz = 0;
        if (5 < kind) sz = 0;
        break;
    case 3:
        sz = 8;
        if ((flags & 0x400000) != 0) sz = 0xc;
        if ((flags & 0x80000) != 0) sz = (flags & 0x400000) ? 0x18 : 0x14;
        break;
    case 4: case 5: case 6:
        break;
    default:
        sz = (ulong)((flags & 0xffffff) * 4 + 4);
        break;
    }
    return sz;
}

/* ========================================================================= */
/* FUN_0024b89c @ 0x0024b89c   (est. sk_pte_size_b)
 * Ghidra: ulong FUN_0024b89c(uint param_1)
 * Same shape as sk_pte_size_a but returns 0 for a zero flags word and omits the
 * 0x80000 case. Pure size computation.
 * Confidence: medium.
 */
ulong sk_pte_size_b(uint flags)
{
    if (flags == 0) return 0;
    {
        byte kind = (byte)sk_rt_00248ae0().lo;   /* FUN_00248ae0 */
        ulong sz = 0;
        switch (kind) {
        case 1: case 2:
            sk_rt_0035854c(0);            /* FUN_0035854c */
            sz = 0;
            if (5 < kind) sz = 0;
            break;
        case 3:
            sz = 8;
            if ((flags & 0x400000) != 0) sz = 0xc;
            break;
        case 4: case 5: case 6:
            break;
        default:
            sz = (ulong)((flags & 0xffffff) * 4 + 4);
            break;
        }
        return sz;
    }
}

/* ========================================================================= */
/* FUN_0024b938 @ 0x0024b938   (est. sk_pte_size_c)
 * Ghidra: long FUN_0024b938(ulong param_1,undefined8 param_2)
 * Computes the encoded size of a PTE descriptor from its flags word: 0 for the
 * final marker kinds, 4/0 for the "empty index" kind, else 0x14/0x1c plus the
 * nested payload contribution (FUN_0024b9f0 and flags-derived offsets) for the
 * leaf/block kinds. Pure size computation over the descriptor flags.
 * Confidence: medium.
 */
long sk_pte_size_c(ulong flags, long base)
{
    uint kind = (uint)sk_rt_00248ae0().lo;   /* FUN_00248ae0 */
    if ((kind & 0xff) - 4 < 3) return 0;
    {
        uint w = (uint)flags;
        if ((kind & 0xff) - 1 < 2) {
            long sz = 4;
            if (((w ^ 0xffffffff) & 0x7fffff) != 0) sz = 0;
            return sz;
        }
        {
            long sz = 0x14;
            if ((flags & 0x400000) != 0) sz = 0x1c;
            if ((w >> 0x13 & 1) != 0) {
                sz = 0x24;
                if ((flags & 0x400000) != 0) sz = 0x2c;
                uint64_t nested = sk_pte_next_region(flags, base); /* FUN_0024b9f0 */
                sz = sz + (nested & 0x3fffffffffffffff)
                       + (nested >> 0x3b & 8) + (uint64_t)(w >> 1 & 8);
            }
            return sz;
        }
    }
}

/* ========================================================================= */
/* FUN_0024b9f0 @ 0x0024b9f0   (est. sk_pte_next_region)
 * Ghidra: undefined8 FUN_0024b9f0(ulong param_1,long param_2)
 * Reads the "next region" payload word at the descriptor body offset
 * (base + 0x10/0x18 + 4), 8-byte aligned, else traps (FUN_00349eb8).
 * Confidence: low.
 */
uint64_t sk_pte_next_region(ulong flags, long base)
{
    long off = 0x10;
    if ((flags & 0x400000) != 0) off = 0x18;
    uint64_t *p = (uint64_t *)(base + off + 4);
    if (((ulong)p & 7) == 0) return *p;
    sk_rt_003488bc(1);                    /* FUN_003488bc */
    sk_rt_00349eb8();                     /* FUN_00349eb8 (noreturn) */
}

/* ========================================================================= */
/* FUN_0024ba38 @ 0x0024ba38   (est. sk_buf_load_u32)
 * Ghidra: undefined4 FUN_0024ba38(long param_1,long param_2,long param_3)
 * Swift UnsafeRawBufferPointer load32: bounds-checks offset+4 against the
 * (base,end) range and alignment, returning the u32 or trapping on negative/
 * out-of-range/misaligned/unexpected-nil.
 * Confidence: medium (Swift stdlib accessor pattern).
 */
uint sk_buf_load_u32(long off, long base, long end)
{
    if (off < 0) {
        sk_rt_fatal_001afe4c(0);          /* "load(withNegative)" 0x5a5 */
    }
    {
        long len = 0;
        if (base != 0) len = end - base;
        if (len < off + 4) {
            sk_rt_fatal_001afe4c(0);      /* "load(outOfBounds)" 0x5a6 */
        }
        if (base != 0) {
            if (((ulong)(base + off) & 3) == 0) return *(uint *)(base + off);
            sk_rt_fatal_001afe4c(0);      /* "misaligned raw pointer" 0x1c1 */
        }
        sk_rt_fatal_001afe4c(0);          /* "unexpectedly found nil" 0x5a8 */
    }
}

/* ========================================================================= */
/* FUN_0024bb9c @ 0x0024bb9c   (est. sk_buf_load_u64)
 * Ghidra: undefined8 FUN_0024bb9c(long param_1,long param_2,long param_3)
 * Swift UnsafeRawBufferPointer load64: bounds-checks offset+8, returns the u64
 * or traps (same fatal-error family as sk_buf_load_u32).
 * Confidence: medium.
 */
sk_pair_t sk_buf_load_u64(long off, long base, long end)
{
    sk_pair_t r;
    if (off < 0) {
        sk_rt_fatal_001afe4c(0);          /* "load(withNegative)" */
    }
    {
        long len = 0;
        if (base != 0) len = end - base;
        if (len < off + 8) {
            sk_rt_fatal_001afe4c(0);      /* "load(outOfBounds)" */
        }
        if (base != 0) {
            if (((ulong)(base + off) & 7) == 0) {
                r.lo = *(uint64_t *)(base + off);
                r.hi = 0;
                return r;
            }
            sk_rt_fatal_001afe4c(0);      /* "misaligned raw pointer" */
        }
        sk_rt_fatal_001afe4c(0);          /* "unexpectedly found nil" */
    }
}

/* ========================================================================= */
/* FUN_0024bd00 @ 0x0024bd00   (est. sk_buf_store_range)
 * Ghidra: void FUN_0024bd00(long param_1,undefined8 param_2,long param_3,
 *                           long param_4)
 * Swift buffer store of a range: validates offset+len (from FUN_00354010 and
 * the op descriptor +0x40) against (base,end) and, when base is present,
 * stores via FUN_001ee130; else traps.
 * Confidence: low.
 */
void sk_buf_store_range(long off, long a, long base, long end)
{
    if (off < 0) {
        sk_rt_003488bc(1);                /* FUN_003488bc */
        sk_rt_00349644();                 /* FUN_00349644 */
    } else {
        long extra = sk_rt_00354010();    /* FUN_00354010 */
        long len = 0;
        if (base != 0) len = end - base;
        if (len < extra + *(long *)(0 + 0x40)) {
            sk_rt_003488bc(1);            /* FUN_003488bc */
            sk_rt_00349644();             /* FUN_00349644 */
        } else {
            if (base != 0) {
                sk_rt_001ee130();         /* FUN_001ee130 */
                return;
            }
            sk_rt_00348898(1);            /* FUN_00348898 */
            sk_rt_00349644();             /* FUN_00349644 */
        }
    }
    sk_rt_00351094();                     /* FUN_00351094 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024bdbc @ 0x0024bdbc   (est. sk_buf_load_u32_at4)
 * Ghidra: void FUN_0024bdbc(void)
 * Convenience wrapper: sk_buf_load_u64(4,...).
 * Confidence: low.
 */
uint sk_buf_load_u32_at4(void)
{
    return (uint)sk_buf_load_u64(4, 0, 0).lo;
}

/* ========================================================================= */
/* FUN_0024bddc @ 0x0024bddc   (est. sk_pte_next_region_off)
 * Ghidra: long FUN_0024bddc(ulong param_1,long param_2)
 * Computes the byte offset of the next region payload given the descriptor
 * flags and base: base + 0x10/0x18 + 0x10/0x18 + (payload's index bit<<3) + 4.
 * Pure offset computation.
 * Confidence: medium.
 */
long sk_pte_next_region_off(ulong flags, long base)
{
    long off = 0x10;
    if ((flags & 0x400000) != 0) off = 0x18;
    long off2 = 0x10;
    if ((flags & 0x10) != 0) off2 = 0x18;
    uint64_t p = sk_pte_next_region(flags, base); /* FUN_0024b9f0 */
    return base + off + off2 + (p >> 0x3b & 8) + 4;
}

/* ========================================================================= */
/* FUN_0024be2c @ 0x0024be2c   (est. sk_pte_build_region)
 * Ghidra: void FUN_0024be2c(...)
 * Builds a PTE region descriptor into the current output buffer: parses the
 * source descriptor word pair (param_4), sizes the entry from its kind, and
 * for the leaf/block kinds emits the header, index, nested payload and the
 * memory-attribute store via sk_pte_store_u32/u64 (FUN_0024c0d0/0024c158) and
 * FUN_0024c1e0. Updates the buffer cursor. Traps on short buffer.
 * Confidence: low (large, many inlined register artifacts).
 */
void sk_pte_build_region(void)
{
    sk_pair_t rng;
    uint hi, lo;
    long base, end;

    hi = (uint)(0 >> 0x20);
    lo = (uint)0;
    rng = sk_rt_0035193c();               /* FUN_0035193c */
    base = (long)rng.lo;
    end = (long)rng.hi;
    {
        uint sel = 0x80000000;
        if ((rng.hi & 1) == 0) sel = 0;
        sk_rt_00350aac(sel | lo & 0x7fffffff, 0); /* FUN_00350aac */
        sk_pte_store_u32(0, 0, 0, 0);     /* FUN_0024c0d0 */
    }
    {
        uint kind = (uint)sk_rt_00248ae0().lo; /* FUN_00248ae0 */
        if ((kind & 0xff) - 4 < 3) {
            /* empty/final kind: header only */
            if (base != 0) {
                if (-1 < (end - base) - 4) {
                    *(long *)0 = base + 4;  /* cursor advance */
                    sk_rt_00351774(0);    /* FUN_00351774 */
                    return;
                }
                sk_rt_003483c4();         /* FUN_003483c4 */
                sk_rt_00351094();         /* FUN_00351094 */
                sk_rt_fatal_001afe4c();   /* FUN_001afe4c */
            }
        } else if ((kind & 0xff) - 1 < 2) {
            if (((lo ^ 0xffffffff) & 0x7fffff) != 0) {
                /* empty index */
            } else {
                sk_rt_00350488();         /* FUN_00350488 */
                sk_buf_load_u64(0, 0, 0); /* FUN_0024ba38 */
                sk_rt_00350aac(0, 4);     /* FUN_00350aac */
                sk_pte_store_u32(0, 0, 0, 0); /* FUN_0024c0d0 */
                if (base != 0) {
                    if (-1 < (end - base) - 8) {
                        *(long *)0 = base + 8;
                        sk_rt_00351774(0);
                        return;
                    }
                    sk_rt_003483c4();
                    sk_rt_00351094();
                    sk_rt_fatal_001afe4c();
                }
            }
        } else {
            /* leaf/block: emit full region */
            sk_rt_003517cc();             /* FUN_003517cc */
            sk_buf_load_u32_at4();        /* FUN_0024bdbc */
            sk_rt_00350aac(0, 8);         /* FUN_00350aac */
            sk_pte_store_u32(0, 0, 0, 0); /* FUN_0024c158 */
            if (base != 0) {
                sk_buf_set_ptr(0, 0x6f72, base + 0x10); /* FUN_0024c1e0 */
                /* nested payload + attributes via store helpers */
                sk_pte_store_u64(0, 0, 0, 0); /* FUN_0024c158 */
                sk_pte_next_region(0, 0); /* FUN_0024bddc */
                sk_pte_next_region(0, 0); /* FUN_0024b9f0 */
                sk_rt_00350aac(0, 8);     /* FUN_00350aac */
                sk_pte_store_u32(0, 0, 0, 0); /* FUN_0024c158 */
                sk_pte_next_region_off(0, 0); /* FUN_0024bddc */
                sk_pte_next_region(0, 0); /* FUN_0024b9f0 */
                if (base != 0) {
                    if (-1 < (end - base) - 0x18) {
                        *(long *)0 = base + 0x18;
                        sk_rt_00351774(0);
                        return;
                    }
                    sk_rt_003483c4();
                    sk_rt_00351094();
                    sk_rt_fatal_001afe4c();
                }
            }
        }
    }
    sk_rt_00347ff4();                     /* FUN_00347ff4 */
    sk_rt_003523f0();                     /* FUN_003523f0 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
    (void)hi; (void)lo; (void)end;
}

/* ========================================================================= */
/* FUN_0024c0d0 @ 0x0024c0d0   (est. sk_pte_store_u32)
 * Ghidra: void FUN_0024c0d0(undefined4 param_1,long param_2,long param_3,
 *                           long param_4)
 * Bounds-checked u32 store into a Swift buffer at offset param_2 within
 * (param_3,param_4); traps on negative/out-of-range offsets.
 * Confidence: medium (Swift UnsafeMutableRawBufferPointer.storeBytes).
 */
void sk_pte_store_u32(long off, long base, long end, uint val)
{
    if (off < 0) {
        sk_rt_003488bc(1);                /* FUN_003488bc */
        sk_rt_00349644();                 /* FUN_00349644 */
    } else {
        long len = 0;
        if (base != 0) len = end - base;
        if (off + 4 <= len) {
            *(uint *)(base + off) = val;
            return;
        }
        sk_rt_003488bc(1);                /* FUN_003488bc */
        sk_rt_00349644();                 /* FUN_00349644 */
    }
    sk_rt_00351094();                     /* FUN_00351094 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024c158 @ 0x0024c158   (est. sk_pte_store_u64)
 * Ghidra: void FUN_0024c158(undefined8 param_1,long param_2,long param_3,
 *                           long param_4)
 * Bounds-checked u64 store into a Swift buffer at offset param_2.
 * Confidence: medium.
 */
void sk_pte_store_u64(long off, long base, long end, uint64_t val)
{
    if (off < 0) {
        sk_rt_003488bc(1);                /* FUN_003488bc */
        sk_rt_00349644();                 /* FUN_00349644 */
    } else {
        long len = 0;
        if (base != 0) len = end - base;
        if (off + 8 <= len) {
            *(uint64_t *)(base + off) = val;
            return;
        }
        sk_rt_003488bc(1);                /* FUN_003488bc */
        sk_rt_00349644();                 /* FUN_00349644 */
    }
    sk_rt_00351094();                     /* FUN_00351094 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024c1e0 @ 0x0024c1e0   (est. sk_buf_set_ptr)
 * Ghidra: void FUN_0024c1e0(long param_1,undefined8 param_2,long param_3)
 * If param_1 != param_3, resolves a slot via FUN_00350a28/FUN_001ee0fc and
 * stores it into the caller's x19; traps if unresolved.
 * Confidence: low.
 */
void sk_buf_set_ptr(long a, uint64_t b, long c)
{
    if (a != c) {
        long slot = sk_rt_001ee0fc(0, sk_rt_00350a28().lo).lo; /* FUN_00350a28/001ee0fc */
        if (slot == 0) {
            sk_rt_00347f2c();             /* FUN_00347f2c */
            sk_rt_fatal_001afe4c();       /* FUN_001afe4c */
        }
        *(long *)0 = slot;                /* *unaff_x19 = slot */
    }
}

/* ========================================================================= */
/* FUN_0024c250 @ 0x0024c250   (est. sk_vspace_ctx_op_commit_a)
 * Ghidra: void FUN_0024c250(void)
 * Commits the op frame: FUN_00077888, descriptor lock, vtable+0x20 dispatch,
 * release (FUN_0035056c).
 * Confidence: low.
 */
void sk_vspace_ctx_op_commit_a(void)
{
    sk_rt_00077888();                     /* FUN_00077888 */
    sk_rt_00349a68();                     /* FUN_00349a68 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    sk_rt_00349178();                     /* FUN_00349178 */
    sk_rt_00351e84();                     /* FUN_00351e84 */
    (*(long (**)(void))0)();              /* extraout_x9 */
    sk_rt_0035056c(*(uint64_t *)(0 + 0x20)); /* FUN_0035056c */
    (*(long (**)(void))0)();              /* extraout_x8_00 */
}

/* ========================================================================= */
/* FUN_0024c2ec @ 0x0024c2ec   (est. sk_vspace_ctx_perm_mod)
 * Ghidra: void FUN_0024c2ec(...)
 * Modifies a region's permission: runs the permission-change helper
 * (FUN_0034b7e4 + FUN_0034c8e0), then checks the owner mask at +0x50; on a
 * mismatch it either calls the region handler (param_3) if the two objects'
 * sizes divide cleanly, or panics. Also flushes on success (FUN_00350768).
 * Confidence: low.
 */
void sk_vspace_ctx_perm_mod(void)
{
    sk_rt_0034b7e4();                     /* FUN_0034b7e4 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034c8e0();                     /* FUN_0034c8e0 */
    if ((*(uint *)(*(long *)(0 - 8) + 0x50) & 0 & 0xff) != 0) {
        sk_rt_00348b7c(0);                /* FUN_00348b7c */
        sk_rt_0034a368();                 /* FUN_0034a368 */
        sk_rt_00352e0c();                 /* FUN_00352e0c */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
    {
        long o1 = *(long *)(*(long *)(0 - 8) + 0x48);
        long o2 = *(long *)(*(long *)(0 - 8) + 0x48);
        if (o2 < o1) {
            if (o2 != 0) {
                long q = (o1 != 0) ? o1 / o2 : 0;
                o1 = o1 - q * o2;
            }
            if (o1 == 0) {
                /* call region handler */
                (*(long (**)(uint64_t))(0))(0);
                if (0 != 0) {              /* unaff_x21 */
                    sk_rt_00350768(*(uint64_t *)(0 + 0x20), 0); /* FUN_00350768 */
                    (*(long (**)(void))0)();
                }
                return;
            }
            sk_rt_00348b7c(0);
            sk_rt_0034a368();
            sk_rt_00352e0c();
            sk_rt_fatal_001afe4c();
        } else {
            if (o1 == 0) {
                sk_rt_00350410();         /* FUN_00350410 */
                sk_rt_00348404();         /* FUN_00348404 */
            } else if (o1 != -1 || o2 != (long)-0x8000000000000000ull) {
                long q = (o1 != 0) ? o2 / o1 : 0;
                o2 = o2 - q * o1;
                if (o2 == 0) {
                    (*(long (**)(uint64_t))(0))(0);
                    if (0 != 0) {
                        sk_rt_00350768(*(uint64_t *)(0 + 0x20), 0);
                        (*(long (**)(void))0)();
                    }
                    return;
                }
                sk_rt_00348b7c(0);
                sk_rt_0034a368();
                sk_rt_00352e0c();
                sk_rt_fatal_001afe4c();
            }
            sk_rt_00350410();             /* FUN_00350410 */
            sk_rt_003488bc();             /* FUN_003488bc */
            sk_rt_00349098();             /* FUN_00349098 */
            sk_rt_00351be0();             /* FUN_00351be0 */
            sk_rt_fatal_001afe4c();       /* FUN_001afe4c */
        }
    }
}

/* ========================================================================= */
/* FUN_0024c460 @ 0x0024c460   (est. sk_buf_drop8)
 * Ghidra: void FUN_0024c460(long *param_1,long param_2)
 * Swift UnsafeBufferPointer dropFirst(count) over 8-byte elements: bounds-
 * checks param_2 against the aligned range and advances the (base,count)
 * pointer pair; traps on negative/overflowing counts.
 * Confidence: medium.
 */
void sk_buf_drop8(long *buf, long n)
{
    sk_pair_t r = sk_buf_align8((ulong)buf[0], buf[1]); /* FUN_0024c648 */
    if (n < 0) {
        sk_rt_fatal_001afe4c(0);          /* "withNegative" */
    }
    {
        long avail = (long)r.hi - (long)r.lo;
        long rem = avail - n * 8;
        if (rem >= 0) {
            buf[0] = (long)r.lo + n * 8;
            buf[1] = buf[0] + rem;
            return;
        }
    }
    sk_rt_fatal_001afe4c(0);              /* "withNegative" 0x4c1 */
}

/* ========================================================================= */
/* FUN_0024c56c @ 0x0024c56c   (est. sk_buf_advance4)
 * Ghidra: void FUN_0024c56c(void)
 * Swift UnsafeRawBufferPointer.dropFirst over 4-byte elements: aligns the
 * current base (FUN_0024c73c), bounds-checks the advance count, and commits
 * the new cursor via FUN_00359bd4; traps on overflow/short buffer.
 * Confidence: medium.
 */
void sk_buf_advance4(void)
{
    long base = (long)sk_rt_003504d0();   /* FUN_003504d0 */
    sk_pair_t r = sk_buf_align4((ulong)base, 0); /* FUN_0024c73c */
    long n = 0;                           /* unaff_x19 */
    if (n < 0) {
        sk_rt_0034846c();                 /* FUN_0034846c */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
    {
        long avail = (long)r.hi - (long)r.lo;
        if (avail >= n * 4) {
            sk_rt_00359bd4((void *)((long)r.lo + n * 4)); /* FUN_00359bd4 */
            return;
        }
    }
    sk_rt_00348284();                     /* FUN_00348284 */
    sk_rt_00351094();                     /* FUN_00351094 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024c5f4 @ 0x0024c5f4   (est. sk_buf_consume4)
 * Ghidra: long FUN_0024c5f4(long *param_1,long param_2)
 * Consumes param_2 4-byte elements from a Swift buffer (param_1 = {base,end}):
 * returns the old base and advances; traps on short buffer.
 * Confidence: medium.
 */
long sk_buf_consume4(long *buf, long n)
{
    if (n < 0) {
        sk_rt_0034846c();                 /* FUN_0034846c */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
    {
        long base = buf[0];
        if (n <= buf[1] - base) {
            buf[0] = base + n;
            return base;
        }
    }
    sk_rt_00348284();                     /* FUN_00348284 */
    sk_rt_00351094();                     /* FUN_00351094 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024c648 @ 0x0024c648   (est. sk_buf_align8)
 * Ghidra: undefined1[16] FUN_0024c648(ulong param_1,long param_2)
 * Swift UnsafeRawBufferPointer alignment: rounds the base up to 8-byte
 * alignment, shrinking the count; traps on negative/overflowing results and
 * on a nil base with a non-zero count. Returns {aligned_base, new_count}.
 * Confidence: medium.
 */
sk_pair_t sk_buf_align8(ulong p, long len)
{
    sk_pair_t r;
    if (p != 0 && (p & 7) != 0) {
        ulong up = (ulong)(uint)(-(int)p) & 7;
        ulong b = p + up;
        len = (len - (long)p) - (long)up;
        if (len < 0) {
            sk_rt_fatal_001afe4c(0);      /* "withNegative" 0x4c1 */
        }
        p = b;
        if (len == 0) {
            if (b == 0) {
                len = 0;
                goto done;
            }
        } else if (b == 0) {
            sk_rt_fatal_001afe4c(0);      /* "has a nil base" 0x4c2 */
        }
        len = (long)b + len;
    }
done:
    r.lo = p;
    r.hi = (uint64_t)len;
    return r;
}

/* ========================================================================= */
/* FUN_0024c73c @ 0x0024c73c   (est. sk_buf_align4)
 * Ghidra: undefined1[16] FUN_0024c73c(ulong param_1,long param_2)
 * Same as sk_buf_align8 but 4-byte alignment. Returns {aligned_base, count}.
 * Confidence: medium.
 */
sk_pair_t sk_buf_align4(ulong p, long len)
{
    sk_pair_t r;
    if (p != 0 && (p & 3) != 0) {
        ulong up = (ulong)(uint)(-(int)p) & 3;
        ulong b = p + up;
        len = (len - (long)p) - (long)up;
        if (len < 0) {
            sk_rt_00348284();             /* FUN_00348284 */
            sk_rt_fatal_001afe4c();       /* FUN_001afe4c */
        }
        p = b;
        if (len == 0) {
            if (b == 0) {
                len = 0;
                goto done;
            }
        } else if (b == 0) {
            sk_rt_00348508();             /* FUN_00348508 */
            sk_rt_fatal_001afe4c();       /* FUN_001afe4c */
        }
        len = (long)b + len;
    }
done:
    r.lo = p;
    r.hi = (uint64_t)len;
    return r;
}

/* ========================================================================= */
/* FUN_0024c7bc @ 0x0024c7bc   (est. sk_align_up8)
 * Ghidra: ulong FUN_0024c7bc(ulong param_1)
 * Rounds param_1 up to 8; traps (unwraps nil) if the result is zero.
 * Confidence: medium.
 */
ulong sk_align_up8(ulong n)
{
    ulong up = n + 7 & 0xfffffffffffffff8;
    if (up != 0) return up;
    sk_rt_fatal_001afe4c(0);              /* "unsafelyUnwrapped of nil optional" */
}

/* ========================================================================= */
/* FUN_0024c82c @ 0x0024c82c   (est. sk_alloc_aligned)
 * Ghidra: ulong FUN_0024c82c(long param_1,long param_2)
 * Allocates a param_2-aligned sub-range from the buffer allocator (x20):
 * rounds the base up to alignment, bounds-checks param_1, commits the new
 * {base,end} and returns the old aligned base; traps on short buffer.
 * Confidence: medium.
 */
ulong sk_alloc_aligned(long a, long b)
{
    uint64_t base = *(uint64_t *)0;       /* *unaff_x20 */
    ulong start = base & (b - 1);
    ulong r;
    long pad = 0;
    if (start == 0) {
        r = base;
    } else {
        pad = b - (long)start;
        r = base + pad;
    }
    if (a >= 0) {
        long avail = *(long *)((char *)0 + 8) - (base + a); /* unaff_x20[1] */
        long rem = avail - pad;
        if (rem >= 0) {
            *(uint64_t *)0 = r + a;
            *(uint64_t *)((char *)0 + 8) = r + a + rem;
            return r;
        }
    }
    sk_rt_003483c4();                     /* FUN_003483c4 */
    sk_rt_00351094();                     /* FUN_00351094 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024c8bc @ 0x0024c8bc   (est. sk_attr_reserved_check)
 * Ghidra: void FUN_0024c8bc(uint param_1)
 * Rejects descriptors with any of the reserved attribute bits (0x1f000000) set.
 * Confidence: medium.
 */
void sk_attr_reserved_check(uint flags)
{
    if ((flags & 0x1f000000) == 0) return;
    sk_rt_003488bc(1);                    /* FUN_003488bc */
    sk_rt_0034a6b0();                     /* FUN_0034a6b0 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024c900 @ 0x0024c900   (est. sk_vspace_ctx_op_dispatch_a)
 * Ghidra: void FUN_0024c900(void)
 * Op dispatch (first variant): locks the descriptor, invokes vtable+0x50,
 * emits the region via FUN_0031cc54, and either commits through
 * sk_vspace_ctx_commit (FUN_0024917c) or panics (noreturn) on a stale owner.
 * Confidence: low.
 */
void sk_vspace_ctx_op_dispatch_a(void)
{
    sk_rt_0034c084();                     /* FUN_0034c084 */
    sk_rt_0035503c();                     /* FUN_0035503c */
    (*(long (**)(void))(0 + 0x50))();     /* vtable+0x50 */
    sk_rt_0031cc54(0, *(uint64_t *)(*((long *)0) + 0x60), 0); /* FUN_0031cc54 */
    sk_rt_00353a30();                     /* FUN_00353a30 */
    if (sk_rt_00362acc() != 0) {          /* FUN_00362acc */
        *(uint64_t *)(0 + 0x18) = 0;      /* store extraout_x1 */
        sk_rt_00319a4c();                 /* FUN_00319a4c */
        sk_rt_00350804();                 /* FUN_00350804 */
        sk_vspace_ctx_commit();           /* FUN_0024917c */
        return;
    }
    sk_rt_0034865c();                     /* FUN_0034865c */
    sk_rt_00349844();                     /* FUN_00349844 */
    sk_rt_00350a94();                     /* FUN_00350a94 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024c9c0 @ 0x0024c9c0   (est. sk_vspace_dispatch_fwd)
 * Ghidra: void FUN_0024c9c0(void)
 * Forwarder to sk_vspace_ctx_commit.
 * Confidence: low.
 */
void sk_vspace_dispatch_fwd(void)
{
    sk_vspace_ctx_commit();               /* FUN_0024917c */
}

/* ========================================================================= */
/* FUN_0024c9e4 @ 0x0024c9e4   (est. sk_vspace_ctx_op_dispatch_b)
 * Ghidra: void FUN_0024c9e4(void)
 * Op dispatch (second variant): locks, invokes vtable+0x50, emits the region
 * through FUN_0034cdd8, then continues via FUN_0024ca54.
 * Confidence: low.
 */
void sk_vspace_ctx_op_dispatch_b(void)
{
    sk_rt_00349ef4();                     /* FUN_00349ef4 */
    sk_rt_0035503c();                     /* FUN_0035503c */
    {
        sk_pair_t r = (sk_pair_t)(*(sk_pair_t (**)(void))(0 + 0x50))(); /* vtable+0x50 */
        sk_rt_0034cdd8(r.lo, r.hi, r.hi); /* FUN_0034cdd8 */
    }
    sk_vspace_op_dispatch_main();         /* FUN_0024ca54 */
}

/* ========================================================================= */
/* FUN_0024ca54 @ 0x0024ca54   (est. sk_vspace_op_dispatch_main)
 * Ghidra: void FUN_0024ca54(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3)
 * Main op dispatcher: takes per-CPU state, resolves the op descriptor and, on
 * an empty owner set, zeroes the descriptor; otherwise commits it through
 * sk_vspace_ctx_commit and reports it, panicking (noreturn) if the owner is
 * stale.
 * Confidence: low.
 */
void sk_vspace_op_dispatch_main(void)
{
    int owned;

    sk_rt_0008e518();                     /* FUN_0008e518 */
    sk_rt_00359c58();                     /* FUN_00359c58 */
    sk_rt_00353540();                     /* FUN_00353540 */
    sk_rt_00310d68();                     /* FUN_00310d68 */
    sk_rt_00348d64();                     /* FUN_00348d64 */
    sk_rt_0007c1a4();                     /* FUN_0007c1a4 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034b0c4();                     /* FUN_0034b0c4 */
    sk_rt_0034a688();                     /* FUN_0034a688 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    sk_rt_00349178();                     /* FUN_00349178 */
    sk_rt_003494e8();                     /* FUN_003494e8 */
    (*sk_hook_00658c00)(*(uint64_t *)(0 + 0x40));  /* DAT_00658c00 */
    sk_rt_0034947c();                     /* FUN_0034947c */
    sk_rt_00100efc(*(uint64_t *)(0 + 0x10)); /* FUN_00100efc */
    (*(long (**)(void))0)();              /* extraout_x8_02 */
    sk_rt_00351384();                     /* FUN_00351384 */
    sk_rt_00352b08();                     /* FUN_00352b08 */
    owned = (int)sk_rt_00365b6c();        /* FUN_00365b6c */
    if (owned == 0) {
        sk_rt_0034c3f4();                 /* FUN_0034c3f4 */
        sk_rt_000839d8();                 /* FUN_000839d8 */
        sk_rt_00350518(*(uint64_t *)(0 + 8)); /* FUN_00350518 */
        (*(long (**)(void))0)();          /* extraout_x8_04 */
        /* zero the descriptor words */
        *(uint64_t *)(0) = 0;
        *(uint64_t *)(8) = 0;
        *(uint64_t *)(0x18) = 0;
        *(uint64_t *)(0x10) = 0;
    } else {
        sk_rt_0034bc94();                 /* FUN_0034bc94 */
        sk_rt_000839d8();                 /* FUN_000839d8 */
        sk_rt_00352b50();                 /* FUN_00352b50 */
        sk_rt_0034f374();                 /* FUN_0034f374 */
        (*(long (**)(void))0)();          /* extraout_x9 */
        {
            sk_pair_t r = sk_rt_003504e8();  /* FUN_003504e8 */
            uint64_t u2 = sk_rt_0031cc54(r.lo, r.hi, 0).lo; /* FUN_0031cc54 */
            sk_rt_00354cb4(u2, u2);       /* FUN_00354cb4 */
        }
        if (sk_rt_00362acc() == 0) {      /* FUN_00362acc */
            sk_rt_00348b7c(0x136);        /* FUN_00348b7c */
            sk_rt_00349844();             /* FUN_00349844 */
            sk_rt_00350a94();             /* FUN_00350a94 */
            sk_rt_fatal_001afe4c();       /* FUN_001afe4c */
        }
        *(uint64_t *)(0x18) = 0;          /* store param_3 */
        sk_rt_00319a4c();                 /* FUN_00319a4c */
        sk_rt_00350a7c();                 /* FUN_00350a7c */
        sk_vspace_ctx_commit();           /* FUN_0024917c */
        sk_rt_003509d4(*(uint64_t *)(0 + 8)); /* FUN_003509d4 */
        (*(long (**)(void))0)();          /* extraout_x8_03 */
    }
    sk_rt_0008e500(0);                    /* FUN_0008e500 */
}

/* ========================================================================= */
/* FUN_0024cd84 @ 0x0024cd84   (est. sk_vspace_ctx_create_fwd)
 * Ghidra: void FUN_0024cd84(void)
 * Forwarder to sk_vspace_ctx_create.
 * Confidence: low.
 */
void sk_vspace_ctx_create_fwd(void)
{
    sk_vspace_ctx_create();               /* FUN_0024a1f0 */
}

/* ========================================================================= */
/* FUN_0024cda8 @ 0x0024cda8   (est. sk_vspace_ctx_op_commit_c)
 * Ghidra: void FUN_0024cda8(undefined8 param_1,undefined8 param_2,
 *                           undefined8 param_3)
 * Commit path: locks, invokes vtable+0x78; if the merge flag is clear it
 * commits (FUN_0034ce78) and continues via FUN_0024cf30; otherwise it resolves
 * the owner, builds the region and forwards through vtable+0x28.
 * Confidence: low.
 */
void sk_vspace_ctx_op_commit_c(void)
{
    sk_rt_00084220();                     /* FUN_00084220 */
    sk_rt_0035316c();                     /* FUN_0035316c */
    sk_rt_0035503c();                     /* FUN_0035503c */
    (*(long (**)(void))(0 + 0x78))();     /* vtable+0x78 */
    sk_rt_00354a6c();                     /* FUN_00354a6c */
    {
        long cb = 0;                       /* ZR flag */
        if (cb) {
            sk_rt_0034ce78();             /* FUN_0034ce78 */
            sk_rt_00084234();             /* FUN_00084234 */
            sk_vspace_ctx_op_prepare2();  /* FUN_0024cf30 */
            return;
        }
        (*sk_hook_00658c00)();            /* DAT_00658c00 */
        {
            uint64_t owner = *(uint64_t *)(0 + 0x88); /* extraout_x16+0x88 */
            sk_rt_00310d04(0xff, owner);  /* FUN_00310d04 */
            sk_rt_0035a808();             /* FUN_0035a808 */
            sk_rt_00350488();             /* FUN_00350488 */
            sk_rt_003515b4();             /* FUN_003515b4 */
            sk_rt_003722e4();             /* FUN_003722e4 */
            sk_rt_00354714();             /* FUN_00354714 */
            sk_rt_002514f0(&(uint64_t){0}); /* FUN_002514f0 */
            {
                uint64_t u1 = sk_rt_0034b518(0).lo; /* FUN_0034b518 */
                (*(long (**)(uint64_t, uint64_t, uint64_t))(0 + 0x28))(u1, 0, owner); /* vtable+0x28 */
            }
            sk_rt_0036b118(0);            /* FUN_0036b118 */
        }
        sk_rt_00084234(0);                /* FUN_00084234 */
    }
}

/* ========================================================================= */
/* FUN_0024cf30 @ 0x0024cf30   (est. sk_vspace_ctx_op_prepare2)
 * Ghidra: void FUN_0024cf30(void)
 * Region prepare: resolves the owner, creates the context, emits the region
 * via vtable+0x28 and releases the temp.
 * Confidence: low.
 */
void sk_vspace_ctx_op_prepare2(void)
{
    sk_rt_00350a28();                     /* FUN_00350a28 */
    sk_vspace_ctx_create();               /* FUN_0024a1f0 */
    {
        sk_pair_t r = sk_rt_00351d9c();   /* FUN_00351d9c */
        sk_rt_0034b07c(r.lo, r.hi, *(uint64_t *)(0 + 0xa0)); /* FUN_0034b07c */
    }
    (*(long (**)(void))(0 + 0x28))();     /* vtable+0x28 */
    sk_rt_0036b118(0);                    /* FUN_0036b118 */
}

/* ========================================================================= */
/* FUN_0024cf98 @ 0x0024cf98   (est. sk_vspace_op_forward)
 * Ghidra: void FUN_0024cf98(void)
 * Forwarder: FUN_0035a7e8 then FUN_0024cfb0.
 * Confidence: low.
 */
void sk_vspace_op_forward(void)
{
    sk_rt_0035a7e8();                     /* FUN_0035a7e8 */
    sk_vspace_region_match(0, 0);         /* FUN_0024cfb0 */
}

/* ========================================================================= */
/* FUN_0024cfb0 @ 0x0024cfb0   (est. sk_vspace_region_match)
 * Ghidra: undefined8 FUN_0024cfb0(long *param_1,long *param_2)
 * Compares the two regions' vtable+0x50 ranges (base/end); if they overlap
 * (end of one == base of the other) merges via FUN_0024d478, else returns 0.
 * Confidence: low.
 */
uint64_t sk_vspace_region_match(long *a, long *b)
{
    sk_pair_t ra = (sk_pair_t)(*(sk_pair_t (**)(void))(*a + 0x50))();
    sk_pair_t rb = (sk_pair_t)(*(sk_pair_t (**)(void))(*b + 0x50))();
    if (ra.hi == rb.lo) {
        sk_vspace_ctx_merge_dispatch(); return 1; /* FUN_0024d478 */
    }
    return 0;
}

/* ========================================================================= */
/* FUN_0024d084 @ 0x0024d084   (est. sk_vspace_region_match_tcb)
 * Ghidra: undefined8 FUN_0024d084(void)
 * Region-match against the current TCB (FUN_000867ec): compares the TCB's
 * range (vtable+0x50) with the x21 object's range; merges via FUN_0024d478.
 * Confidence: low.
 */
uint64_t sk_vspace_region_match_tcb(void)
{
    sk_rt_00354f28(*((uint64_t *)sk_rt_000867ec())); /* FUN_00354f28 */
    (*(long (**)(void))(0 + 0x50))();     /* vtable+0x50 */
    sk_rt_003517c0();                     /* FUN_003517c0 */
    {
        sk_pair_t r = (sk_pair_t)(*(sk_pair_t (**)(void))(0 + 0x50))(); /* *unaff_x21+0x50 */
        if (0 == r.lo) {                  /* unaff_x24 == r.lo */
            sk_rt_00100efc(r.lo, r.hi, r.hi); /* FUN_00100efc */
            sk_rt_003558fc();             /* FUN_003558fc */
            sk_vspace_ctx_merge_dispatch(); return 1; /* FUN_0024d478 */
        }
    }
    return 0;
}

/* ========================================================================= */
/* FUN_0024d140 @ 0x0024d140   (est. sk_vspace_ctx_signal_a)
 * Ghidra: void FUN_0024d140(void)
 * Signal path: FUN_000027e8, emit via FUN_0031cc3c, then resolve + merge.
 * Confidence: low.
 */
void sk_vspace_ctx_signal_a(void)
{
    sk_rt_000027e8();                     /* FUN_000027e8 */
    sk_rt_0031cc3c(0, *(uint64_t *)(0 + 0x60)); /* FUN_0031cc3c */
    sk_rt_0034ed18();                     /* FUN_0034ed18 */
    sk_vspace_region_match_tcb();         /* FUN_0024d084 */
}

/* ========================================================================= */
/* FUN_0024d180 @ 0x0024d180   (est. sk_vspace_ctx_signal_b)
 * Ghidra: void FUN_0024d180(void)
 * Signal path variant: FUN_00352230, emit via FUN_0031cc54, resolve + merge.
 * Confidence: low.
 */
void sk_vspace_ctx_signal_b(void)
{
    uint64_t u = sk_rt_00352230().lo;     /* FUN_00352230 */
    sk_rt_00354f28(u, *(uint64_t *)(0 + 0x60)); /* FUN_00354f28 */
    sk_rt_0031cc54(0, 0, *(uint64_t *)(0 + 0x70)); /* FUN_0031cc54 */
    sk_rt_0034ed18();                     /* FUN_0034ed18 */
    sk_vspace_region_match_tcb();         /* FUN_0024d084 */
}

/* ========================================================================= */
/* FUN_0024d1d0 @ 0x0024d1d0   (est. sk_vspace_ctx_signal_c)
 * Ghidra: void FUN_0024d1d0(void)
 * Signal path variant (FUN_0031cc6c).
 * Confidence: low.
 */
void sk_vspace_ctx_signal_c(void)
{
    uint64_t u = sk_rt_00352230().lo;     /* FUN_00352230 */
    sk_rt_00354f28(u, *(uint64_t *)(0 + 0x60)); /* FUN_00354f28 */
    sk_rt_0031cc6c(0, 0, *(uint64_t *)(0 + 0xa0)); /* FUN_0031cc6c */
    sk_rt_0034ed18();                     /* FUN_0034ed18 */
    sk_vspace_region_match_tcb();         /* FUN_0024d084 */
}

/* ========================================================================= */
/* FUN_0024d220 @ 0x0024d220   (est. sk_vspace_ctx_signal_d)
 * Ghidra: void FUN_0024d220(long *param_1,long param_2)
 * Emits a region signal from param_2+0x68 with the object's vtable+0x70 field,
 * then continues to the counter-merge path (FUN_0024d268).
 * Confidence: low.
 */
void sk_vspace_ctx_signal_d(long *obj, long param2)
{
    sk_rt_0031cc54(0, *(uint64_t *)(param2 + 0x68), *(uint64_t *)(*obj + 0x70)); /* FUN_0031cc54 */
    sk_rt_0034ed18();                     /* FUN_0034ed18 */
    sk_vspace_ctx_counter_merge();        /* FUN_0024d268 */
}

/* ========================================================================= */
/* FUN_0024d268 @ 0x0024d268   (est. sk_vspace_ctx_counter_merge)
 * Ghidra: void FUN_0024d268(void)
 * Merges two counter/range values (FUN_00351b04) and stores the negated sum at
 * obj+0x10; refreshes the TLB context (FUN_0034c0a4, FUN_00362bc0).
 * Confidence: low.
 */
void sk_vspace_ctx_counter_merge(void)
{
    long obj;
    long a, b;

    sk_rt_0035089c();                     /* FUN_0035089c */
    sk_rt_0007c198();                     /* FUN_0007c198 */
    sk_vspace_ctx_state_merge(0);         /* FUN_002490c8 */
    sk_rt_00354d44();                     /* FUN_00354d44 */
    obj = sk_rt_002487b8();               /* FUN_002487b8 */
    a = sk_rt_00351b04();                 /* FUN_00351b04 */
    b = sk_rt_00351b04();                 /* FUN_00351b04 */
    if (!(a < 0 || b < 0)) {
        if (a + b >= 0) {
            *(long *)(obj + 0x10) = ~(a + b);
        }
    }
    sk_rt_0034c0a4();                     /* FUN_0034c0a4 */
    sk_rt_00362bc0();                     /* FUN_00362bc0 */
}

/* ========================================================================= */
/* FUN_0024d338 @ 0x0024d338   (est. sk_vspace_ctx_signal_e)
 * Ghidra: void FUN_0024d338(void)
 * Signal path variant (offset 0x68 / FUN_0031cc6c).
 * Confidence: low.
 */
void sk_vspace_ctx_signal_e(void)
{
    uint64_t u = sk_rt_00352230().lo;     /* FUN_00352230 */
    sk_rt_00354f28(u, *(uint64_t *)(0 + 0x68)); /* FUN_00354f28 */
    sk_rt_0031cc6c(0, 0, *(uint64_t *)(0 + 0xa0)); /* FUN_0031cc6c */
    sk_rt_0034ed18();                     /* FUN_0034ed18 */
    sk_vspace_ctx_counter_merge();        /* FUN_0024d268 */
}

/* ========================================================================= */
/* FUN_0024d388 @ 0x0024d388   (est. sk_vspace_ctx_signal_f)
 * Ghidra: void FUN_0024d388(void)
 * Signal path variant (offset 0x80 / FUN_0031cd00).
 * Confidence: low.
 */
void sk_vspace_ctx_signal_f(void)
{
    uint64_t u = sk_rt_00352230().lo;     /* FUN_00352230 */
    sk_rt_00354f28(u, *(uint64_t *)(0 + 0x80)); /* FUN_00354f28 */
    sk_rt_0031cd00(0, 0, *(uint64_t *)(0 + 0x88)); /* FUN_0031cd00 */
    sk_rt_0034ed18();                     /* FUN_0034ed18 */
    sk_vspace_ctx_counter_merge();        /* FUN_0024d268 */
}

/* ========================================================================= */
/* FUN_0024d3d8 @ 0x0024d3d8   (est. sk_vspace_ctx_signal_g)
 * Ghidra: void FUN_0024d3d8(void)
 * Signal path variant (offset 0x80 / FUN_0031cc6c).
 * Confidence: low.
 */
void sk_vspace_ctx_signal_g(void)
{
    uint64_t u = sk_rt_00352230().lo;     /* FUN_00352230 */
    sk_rt_00354f28(u, *(uint64_t *)(0 + 0x80)); /* FUN_00354f28 */
    sk_rt_0031cc6c(0, 0, *(uint64_t *)(0 + 0xa0)); /* FUN_0031cc6c */
    sk_rt_0034ed18();                     /* FUN_0034ed18 */
    sk_vspace_ctx_counter_merge();        /* FUN_0024d268 */
}

/* ========================================================================= */
/* FUN_0024d428 @ 0x0024d428   (est. sk_vspace_ctx_signal_h)
 * Ghidra: void FUN_0024d428(void)
 * Signal path variant (offset 0x98 / FUN_0031cc6c).
 * Confidence: low.
 */
void sk_vspace_ctx_signal_h(void)
{
    uint64_t u = sk_rt_00352230().lo;     /* FUN_00352230 */
    sk_rt_00354f28(u, *(uint64_t *)(0 + 0x98)); /* FUN_00354f28 */
    sk_rt_0031cc6c(0, 0, *(uint64_t *)(0 + 0x88)); /* FUN_0031cc6c */
    sk_rt_0034ed18();                     /* FUN_0034ed18 */
    sk_vspace_ctx_counter_merge();        /* FUN_0024d268 */
}

/* ========================================================================= */
/* FUN_0024d478 @ 0x0024d478   (est. sk_vspace_ctx_merge_dispatch)
 * Ghidra: void FUN_0024d478(void)
 * Merges two vspace contexts: resolves both owner objects (FUN_003517b4,
 * FUN_0031cc54), and when both are present folds the region, merges the two
 * counters (negated sum at +0x10), and reports the merged region via
 * FUN_00357c44; otherwise panics (noreturn).
 * Confidence: low.
 */
void sk_vspace_ctx_merge_dispatch(void)
{
    sk_rt_00357ca0();                     /* FUN_00357ca0 */
    sk_rt_00354b2c();                     /* FUN_00354b2c */
    {
        uint64_t u = sk_rt_003517b4().lo; /* FUN_003517b4 */
        sk_rt_0031cc54(u, 0, 0);          /* FUN_0031cc54 */
    }
    sk_rt_0035a7e8();                     /* FUN_0035a7e8 */
    if (sk_rt_00362acc() != 0) {          /* FUN_00362acc */
        sk_rt_0034f614();                 /* FUN_0034f614 */
        sk_rt_0031cc54();                 /* FUN_0031cc54 */
        sk_rt_00356b98();                 /* FUN_00356b98 */
        if (sk_rt_00362acc() != 0) {
            sk_rt_0034b7b8();             /* FUN_0034b7b8 */
            {
                sk_pair_t r = sk_rt_0031cc54(); /* FUN_0031cc54 */
                sk_rt_0006b6f4(r.lo, r.hi, r.lo); /* FUN_0006b6f4 */
            }
            {
                sk_vspace_ctx_counter_merge(); long obj = 0; /* FUN_0024d268 */
                long a = sk_rt_00351b04(); /* FUN_00351b04 */
                long b = sk_rt_00351b04(); /* FUN_00351b04 */
                if (!(a < 0 || b < 0) && a + b >= 0) {
                    *(long *)(obj + 0x10) = ~(a + b);
                }
            }
            sk_rt_003510b8();             /* FUN_003510b8 */
            if (sk_rt_00362acc() != 0) {  /* FUN_00362acc */
                sk_rt_00357c44(0, 0);     /* FUN_00357c44 */
                return;
            }
        }
    }
    sk_rt_0034865c();                     /* FUN_0034865c */
    sk_rt_00349844();                     /* FUN_00349844 */
    sk_rt_00350a94();                     /* FUN_00350a94 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024d558 @ 0x0024d558   (est. sk_buf_size_calc)
 * Ghidra: void FUN_0024d558(undefined8 param_1,undefined8 param_2,
 *                           long param_3,long param_4)
 * Computes the on-disk byte size of a PTE region from its descriptors
 * (FUN_00248a34 walk): sums header + per-entry payload (size via the same
 * rule as sk_pte_size_c), then emits a 6-word allocation descriptor
 * {aligned_size, base+count, size, extra...} via FUN_00353238. Handles the
 * string-payload extra term. Pure size computation over the region buffer.
 * Confidence: low.
 */
void sk_buf_size_calc(void)
{
    sk_pair_t d = sk_rt_0035300c();       /* FUN_0035300c */
    long total = 0;
    long saved = 0;
    {
        uint16_t mode = (uint16_t)(0 >> 8);
        long len = 0;
        if (0 != 0) len = 0 - 0;          /* param_4 - param_3 */
        len = (len + 7 & ~7) + 0x10;
        do {
            d = sk_rt_00248a34();         /* FUN_00248a34 */
            {
                uint64_t w0 = d.lo;
                uint32_t k = (uint32_t)d.lo;
                uint64_t entry = 0;
                switch (k >> 0x18 & 0x7f) {
                default:
                    entry = 4;
                    if (((k ^ 0xffffffff) & 0x7fffff) != 0) entry = 0;
                    break;
                case 2:
                    if ((k >> 0x13 & 1) == 0) {
                        entry = 0x14;
                        if ((w0 & 0x400000) != 0) entry = 0x1c;
                    } else {
                        long off = 0x10;
                        if ((w0 & 0x400000) != 0) off = 0x18;
                        uint64_t p = *(uint64_t *)((long)d.hi + off + 4);
                        if ((long)p < 0) {
                            long o2 = 0x10;
                            if ((w0 & 0x10) != 0) o2 = 0x18;
                            entry = (uint64_t)((off + len + 8 + o2 + 0x11) & ~7ull);
                            if (((off + len + 8 + o2) & 8) != 0)
                                entry = (uint64_t)(off + len + 8 + o2);
                        } else {
                            long base = 0x24;
                            if ((w0 & 0x400000) != 0) base = 0x2c;
                            entry = (uint64_t)base + (k >> 1 & 8)
                                  + (p & 0x3fffffffffffffff) + (p >> 0x3b & 8);
                        }
                    }
                    break;
                case 4:
                    break;
                }
                len = (long)entry + (long)(len + 4);
            }
            {
                /* string-payload term when param_4==0 */
                if (0 == 0) {              /* param_4 == 0 */
                    long l2 = (len + 7 & ~7) + 8;
                    long s = 0, sp = 0, sc = 0;
                    if (d.lo != 0 && (long)d.hi != 0) { /* string present */
                        /* FUN_00351b04 / thunk_FUN_00115080 checks */
                    }
                    /* emit 6-word allocation descriptor */
                    *(long *)0 = l2;
                    *(long *)((char *)0 + 8) = (l2 + 3) & ~3;
                    *(long *)((char *)0 + 0x10) = len + -8;
                    *(long *)((char *)0 + 0x18) = sc;
                    *(long *)((char *)0 + 0x20) = sp;
                    *(long *)((char *)0 + 0x28) = s;
                    sk_rt_00353238(0);     /* FUN_00353238 */
                    return;
                }
                len = (len + 7 & ~7) + 8;
            }
        } while (1);
    }
    (void)total; (void)saved;
}

/* ========================================================================= */
/* FUN_0024d788 @ 0x0024d788   (est. sk_buf_stringify)
 * Ghidra: void FUN_0024d788(undefined8 param_1..param_6)
 * Builds a dotted key-path string for a region: takes per-CPU state
 * (FUN_0008e518) and the region's string payload (FUN_0024d558), then either
 * links it directly or appends a ".N" suffix with the counter words, storing
 * the resulting string into the object via FUN_00247360. Panics on stale owner.
 * Confidence: low.
 */
void sk_buf_stringify(void)
{
    sk_pair_t cpu = sk_rt_0008e518();     /* FUN_0008e518 */
    if (cpu.lo == 0 || cpu.hi == cpu.lo) {
        sk_rt_00350560();                 /* FUN_00350560 */
        if (sk_rt_00362acc() != 0) {
            *(long *)0 = 0;               /* *extraout_x8 = param_4 */
            sk_rt_0008e500(0, 0);         /* FUN_0008e500 */
            sk_rt_0036b270();             /* FUN_0036b270 */
            return;
        }
    } else {
        {
            long l3 = *(long *)0;          /* *param_5 */
            int empty = (l3 == 0 || *(long *)((char *)0 + 8) == l3);
            if (empty) {
                sk_rt_00100efc();         /* FUN_00100efc */
                if (sk_rt_00362acc() != 0) {
                    *(long *)0 = 0;       /* *extraout_x8 = param_6 */
                    sk_rt_0008e500(0, 0);
                    sk_rt_0036b270();
                    return;
                }
            } else {
                sk_rt_003504c4();         /* FUN_003504c4 */
                sk_buf_size_calc();       /* FUN_0024d558 */
                sk_rt_00351b04();         /* FUN_00351b04 */
                /* string assembly + suffix */
                sk_rt_003507d4();         /* FUN_003507d4 */
                if (sk_rt_00362acc() != 0) {
                    *(long *)0 = 0;       /* *extraout_x8 = lVar3 */
                    sk_rt_0008e500(0);
                    return;
                }
            }
        }
    }
    sk_rt_0034865c();                     /* FUN_0034865c */
    sk_rt_00349844();                     /* FUN_00349844 */
    sk_rt_00350a94();                     /* FUN_00350a94 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024d9a8 @ 0x0024d9a8   (thunk to FUN_0024d9ac)   (est. sk_thunk_ctx)
 * Ghidra: thunk_FUN_0024d9ac(void)
 * 4-byte branch thunk into sk_vspace_ctx_inject (FUN_0024d9ac).
 * Confidence: medium (trivial thunk).
 */
void sk_thunk_ctx_0024d9a8(void)
{
    sk_vspace_ctx_inject();               /* FUN_0024d9ac */
}

/* ========================================================================= */
/* FUN_0024d9ac @ 0x0024d9ac   (est. sk_vspace_ctx_inject)
 * Ghidra: void FUN_0024d9ac(void)
 * Injects a context into a cache/slot: computes a hash bucket (FUN_00351a38,
 * FUN_0022a474, FUN_0024c8bc) and either reuses an existing slot or builds and
 * links a new one (FUN_00247360 with the FUN_0031cd18 handler), storing the
 * bucket pointer. Handles the empty/used cases.
 * Confidence: low.
 */
void sk_vspace_ctx_inject(void)
{
    long key = sk_rt_00351a38();          /* FUN_00351a38 */
    long *slot;
    sk_pair_t d;

    sk_rt_0022a474(0x10, key + 4);        /* FUN_0022a474 */
    sk_attr_reserved_check(0);            /* FUN_0024c8bc */
    sk_rt_003504e8();                     /* FUN_003504e8 */
    {
        long idx = sk_rt_0022a474().lo;   /* FUN_0022a474 */
        if (idx == 0) {
            slot = (long *)0;
        } else {
            slot = (long *)(0 + idx);      /* unaff_x19 + idx */
            if (*slot != 0) {
                sk_rt_0036b270(*slot);    /* FUN_0036b270 */
                sk_rt_00356310();         /* FUN_00356310 */
                return;
            }
        }
    }
    sk_rt_00100efc();                     /* FUN_00100efc */
    sk_vspace_ctx_decode();               /* FUN_0024daf8 */
    sk_rt_00355cbc();                     /* FUN_00355cbc */
    {
        uint32_t local = 0;
        char flag = '\x01';
        d = (*sk_hook_00658c00)();        /* DAT_00658c00 */
        sk_rt_00247360(d.lo, sk_rt_0031cd18, 0); /* FUN_00247360(FUN_0031cd18) */
        sk_rt_003504e8();                 /* FUN_003504e8 */
        {
            long idx = sk_rt_0022a474().lo; /* FUN_0022a474 */
            if (idx == 0) {
                *(uint64_t *)(0 + 0x10) = 0;
                if (flag != '\x01') {
                    /* store ~local */
                }
            } else {
                /* store unaff_x19 + 0x10 + idx */
            }
        }
    }
    if (slot != (long *)0) {
        sk_rt_0036b270(0);                /* FUN_0036b270 */
        if (*slot == 0) {
            *slot = 0;
        } else {
            sk_rt_0036b270(*slot);        /* FUN_0036b270 */
            sk_rt_0036b340(0, 2);         /* FUN_0036b340 */
        }
    }
    sk_rt_00356310();                     /* FUN_00356310 */
}

/* ========================================================================= */
/* FUN_0024daf8 @ 0x0024daf8   (est. sk_vspace_ctx_decode)
 * Ghidra: void FUN_0024daf8(undefined8 param_1,undefined8 param_2)
 * Decodes a packed region record (FUN_000a6f68 + FUN_0024e2b8) into a Swift
 * string/selector; switches on the record mode byte (0/1/other) to emit the
 * matching selector, and faults on a missing owner.
 * Confidence: low.
 */
void sk_vspace_ctx_decode(void)
{
    uint64_t u = sk_rt_000a6f68().lo;     /* FUN_000a6f68 */
    {
        uint64_t rec[16] = {0};
        rec[1] = 0;                        /* local_90 = 1 (mode) */
        sk_pte_encode_table(u, rec, 0, 0); /* FUN_0024e2b8 */
        if (rec[3] == 1) {                 /* local_90 mode byte */
            /* mode dispatch */
        }
        if (rec[5] != 0 && rec[7] != 0) {  /* two payload words non-zero */
            switch ((char)rec[3]) {
            case 0:
                sk_rt_003504e8();         /* FUN_003504e8 */
                sk_rt_0031cc54();         /* FUN_0031cc54 */
                break;
            case 1:
                sk_rt_003504e8();         /* FUN_003504e8 */
                sk_rt_0031cd00();         /* FUN_0031cd00 */
                break;
            default:
                sk_rt_003504e8();         /* FUN_003504e8 */
                sk_rt_0031cc6c();         /* FUN_0031cc6c */
                break;
            }
            sk_rt_003444e4(rec);          /* FUN_003444e4 */
            sk_rt_00350278();             /* FUN_00350278 */
            return;
        }
        sk_rt_00348898(1);                /* FUN_00348898 */
        sk_rt_0034a2f8();                 /* FUN_0034a2f8 */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
}

/* ========================================================================= */
/* FUN_0024dbfc @ 0x0024dbfc   (est. sk_pte_flag_build)
 * Ghidra: ulong FUN_0024dbfc(...)
 * Builds the page-table descriptor flag word from an encoded record
 * (FUN_000a6f68 + FUN_0024e7a4): sets the "leaf/block" bits (0x20000000/
 * 0x40000000/0x60000000) and the "present" high bit (0x80000000) from the
 * record's owner flag, appends the size/offset field, then folds in the
 * refcount word. Returns the combined flags; traps on short input.
 * Confidence: low.
 */
ulong sk_pte_flag_build(void)
{
    uint64_t *rec;
    uint64_t result;
    long rc;

    if (0 - (long)0 < 8) {                /* param_3 - param_2 < 8 */
        sk_rt_003483c4();                 /* FUN_003483c4 */
        sk_rt_00351094();                 /* FUN_00351094 */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
    sk_rt_00354010();                     /* FUN_00354010 */
    rec = (uint64_t *)0;                  /* local_a0 */
    {
        uint64_t u = sk_rt_000a6f68().lo; /* FUN_000a6f68 */
        char owner = '\x01';
        sk_pte_encode_table2(u, rec, 0, 0); /* FUN_0024e7a4 */
        result = 0 - 8;                    /* param_6 - 8 */
        if ((long)result < 0) {
            sk_rt_00348b7c(0xcf8);        /* FUN_00348b7c */
            sk_rt_00349a54();             /* FUN_00349a54 */
        } else {
            if (result >> 0x20 == 0) {
                rc = *(long *)(0 + 0x10);  /* local_70+0x10 */
                if (rec[0] == 0) {
                    result = (uint64_t)((uint)result | 0x80000000);
                    if (rc != 1) result = (uint64_t)((uint)result);
                }
                /* fold owner into high flag bits */
                if (rec[0] != 0) {
                    result = (uint64_t)((uint)result | 0x40000000);
                    sk_rt_00350798();     /* FUN_00350798 */
                }
                {
                    /* refcount word walk */
                    long n = *(long *)(0 + 0x10);
                    if (n != 0) {
                        byte *p = (byte *)(0 + 0x20);
                        byte b = 1;
                        do {
                            if (n == 0) {
                                sk_rt_00348304(); /* FUN_00348304 */
                                sk_rt_fatal_001afe4c();
                            }
                            if ((b & 1) == 0) {
                                if (n == 1) break;
                                b = 0;
                            } else {
                                b = *p;
                                if (n == 1) {
                                    if (b != 0) break;
                                    result = 0x100000000;
                                    goto out;
                                }
                            }
                            n = n - 1;
                            p = p + 1;
                        } while (1);
                    }
                    result = 0;            /* local_78 */
                }
out:
                sk_rt_0034447c(rec);      /* FUN_0034447c */
                return result;
            }
            sk_rt_003583dc();             /* FUN_003583dc */
            sk_rt_00348194();             /* FUN_00348194 */
        }
        sk_rt_003523f0();                 /* FUN_003523f0 */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
}

/* ========================================================================= */
/* FUN_0024dda0 @ 0x0024dda0   (est. sk_utf8_len)
 * Ghidra: long FUN_0024dda0(byte *param_1)
 * Walks a NUL-terminated string, skipping 5 bytes for a 0x18-prefixed (UTF-8
 * multi-byte) continuation else 1 byte per ASCII char, returning the byte
 * length. Pure string walker.
 * Confidence: medium.
 */
long sk_utf8_len(byte *s)
{
    byte *p = s;
    byte c = *s;
    while (c != 0) {
        long n = 9;
        if ((c & 0xf8) != 0x18) n = 1;
        long adv = 5;
        if (c <= 0x17) adv = n;
        p = p + adv;
        c = *p;
    }
    return (long)p - (long)s;
}

/* ========================================================================= */
/* FUN_0024dde0 @ 0x0024dde0   (est. sk_utf8_encode_fwd)
 * Ghidra: void FUN_0024dde0(undefined8 param_1,undefined8 param_2,ulong param_3)
 * Forwards to one of two UTF-8 encode helpers keyed on the low bit of param_3.
 * Confidence: low.
 */
void sk_utf8_encode_fwd(void)
{
    if ((0 & 1) == 0) {                   /* param_3 & 1 */
        sk_rt_003893d0();                 /* FUN_003893d0 */
        return;
    }
    sk_rt_00389b4c(0, 0, 0 & 0xfffffffffffffffe); /* FUN_00389b4c */
}

/* ========================================================================= */
/* FUN_0024ddf0 @ 0x0024ddf0   (est. sk_region_decode)
 * Ghidra: undefined8 FUN_0024ddf0(undefined8 param_1,undefined8 param_2,
 *                                 undefined8 *param_3)
 * Decodes a packed region header: resolves the two "next" pointer words
 * (FUN_0024e248) and walks the region descriptor (FUN_0024ddf0 recursion via
 * the string keypath demangler FUN_0024dde0). On a canonical 0xa000000000000000
 * marker with a "dot" payload, forwards through FUN_00356590; otherwise emits
 * the key-path and commits. Traps on malformed input.
 * Confidence: low.
 */
void sk_region_decode(void)
{
    sk_pair_t lo;
    uint64_t u = sk_rt_0006b2ec().lo;     /* FUN_0006b2ec */
    if ((u & 1) != 0) {
        char *p = (char *)sk_rt_00352758(); /* FUN_00352758 */
        char *s = (char *)(0 - 1);          /* unaff_x19-1 */
        if (*s == (char)-1 && *p == '\t') {
            p = (char *)(*(int *)(p + 1) + (long)(p + 1));
            if (p == (char *)0) {
                sk_rt_00347ff4();         /* FUN_00347ff4 */
                sk_rt_003523f0();         /* FUN_003523f0 */
                sk_rt_fatal_001afe4c();   /* FUN_001afe4c */
            }
            if (0 == (long)-0x2c8502b44bfffed6) {  /* extraout_x8 */
                sk_rt_00356590(0, p);     /* FUN_00356590 */
                return;
            }
            sk_rt_fatal_001afe4c();       /* FUN_0011d7e8 (noreturn) */
        }
        {
            long n = sk_utf8_len(s);      /* FUN_0024dda0 */
            if (n < 0) {
                sk_rt_003482c4();         /* FUN_003482c4 */
                sk_rt_003523f0();         /* FUN_003523f0 */
                sk_rt_fatal_001afe4c();   /* FUN_001afe4c */
            }
            sk_rt_003502c8(s);            /* FUN_003502c8 */
            sk_utf8_encode_fwd();         /* FUN_0024dde0 */
            /* keypath demangling + emit; falls through to trap on failure */
        }
    }
    {
        sk_pair_t r = sk_rt_000651bc(0);  /* FUN_000651bc */
        if (0) {                           /* ZR flag */
            sk_rt_00356590(r.lo, 0);      /* FUN_00356590 */
            return;
        }
    }
    sk_rt_fatal_001afe4c();               /* FUN_0011d7e8 (noreturn) */
    (void)lo;
}

/* ========================================================================= */
/* FUN_0024e0e8 @ 0x0024e0e8   (est. sk_vspace_ctx_op_commit_b)
 * Ghidra: void FUN_0024e0e8(void)
 * Op commit (second variant): per-CPU state, lock FUN_00377824/00377bec,
 * descriptor, emit via the vtable+8 handler, restore per-CPU frame.
 * Confidence: low.
 */
void sk_vspace_ctx_op_commit_b(void)
{
    uint64_t u1;
    sk_rt_0008e518();                     /* FUN_0008e518 */
    sk_rt_0034b430();                     /* FUN_0034b430 */
    sk_rt_00357bc4();                     /* FUN_00357bc4 */
    u1 = sk_rt_00310ad4().lo;             /* FUN_00310ad4 */
    sk_rt_0034e6fc();                     /* FUN_0034e6fc */
    sk_rt_00377824();                     /* FUN_00377824 */
    sk_rt_00348d4c();                     /* FUN_00348d4c */
    sk_rt_0007c1a4();                     /* FUN_0007c1a4 */
    (*sk_hook_00658c00)();                /* DAT_00658c00 */
    sk_rt_0034b0d4();                     /* FUN_0034b0d4 */
    sk_rt_00350524();                     /* FUN_00350524 */
    sk_rt_00351aec();                     /* FUN_00351aec */
    sk_rt_00377bec();                     /* FUN_00377bec */
    sk_rt_0031bc70();                     /* FUN_0031bc70 */
    sk_rt_0035102c();                     /* FUN_0035102c */
    sk_rt_003500d4();                     /* FUN_003500d4 */
    (*(long (**)(void))0)();              /* extraout_x9 */
    sk_rt_00310ca4(u1);                   /* FUN_00310ca4 */
    sk_rt_00351250();                     /* FUN_00351250 */
    sk_rt_00350810();                     /* FUN_00350810 */
    (*(long (**)(void))0)();              /* extraout_x9_00 */
    sk_rt_00350a34(*(uint64_t *)(0 + 8)); /* FUN_00350a34 */
    (*(long (**)(void))0)();              /* extraout_x8 */
    sk_rt_0008e500(0);                    /* FUN_0008e500 */
}

/* ========================================================================= */
/* FUN_0024e1dc @ 0x0024e1dc   (est. sk_vspace_ctx_op_commit_c2)
 * Ghidra: void FUN_0024e1dc(void)
 * Op commit (third variant): lock, emit via FUN_0011aa70.
 * Confidence: low.
 */
void sk_vspace_ctx_op_commit_c2(void)
{
    sk_rt_0034b430();                     /* FUN_0034b430 */
    sk_rt_00354e00();                     /* FUN_00354e00 */
    sk_rt_00310fc4();                     /* FUN_00310fc4 */
    sk_rt_00351250();                     /* FUN_00351250 */
    sk_rt_0011aa70();                     /* FUN_0011aa70 */
    (*(long (**)(void))0)();              /* extraout_x9 */
}

/* ========================================================================= */
/* FUN_0024e21c @ 0x0024e21c   (est. sk_ptr_follow)
 * Ghidra: long FUN_0024e21c(long param_1,uint param_2)
 * Returns param_1 + param_2 for an even offset; for an odd (relocatable/
 * tagged) offset, resolves the target via FUN_001ee0fc. Pointer chasing.
 * Confidence: medium.
 */
long sk_ptr_follow(long p, uint off)
{
    if ((off & 1) == 0) {
        return p + (int)off;
    }
    return sk_rt_001ee0fc(0, p + (int)(off - 1)).lo; /* FUN_001ee0fc */
}

/* ========================================================================= */
/* FUN_0024e248 @ 0x0024e248   (est. sk_ptr_load32)
 * Ghidra: long FUN_0024e248(long param_1,long param_2)
 * Loads the int32 at param_1+param_2 and returns it as a pointer (relocatable
 * encoding: value + address). Traps on misalignment.
 * Confidence: medium.
 */
long sk_ptr_load32(long p, long off)
{
    int *pi = (int *)(p + off);
    if (((ulong)pi & 3) == 0) {
        return (long)*pi + (long)pi;
    }
    sk_rt_fatal_001afe4c(0);              /* "load from misaligned raw pointer" */
}

/* ========================================================================= */
/* FUN_0024e2b8 @ 0x0024e2b8   (est. sk_pte_encode_table)
 * Ghidra: void FUN_0024e2b8(long param_1,ulong *param_2,undefined8 param_3,
 *                           long param_4)
 * Encodes a PTE table into a 12-word output record (param_2): resolves the
 * header words (FUN_0024e248), emits the region via sk_region_decode, then
 * walks the index entries (FUN_001ee0c8), encoding each leaf/block descriptor
 * via sk_pte_emit_desc_a/b and the region/sub-region helpers. Advances the
 * record cursor; handles the multi-level sub-table case with FUN_0024eed4/
 * FUN_0024ef54. Traps on short buffer.
 * Confidence: low (large, Swift-buffer heavy).
 */
void sk_pte_encode_table(long src, ulong *dst, long flags, long keep)
{
    long cursor;
    uint32_t *entries;
    uint32_t *end;

    /* header words */
    sk_ptr_load32(src, 0);                /* FUN_0024e248 */
    sk_ptr_load32(src, 4);
    sk_ptr_load32(src, 8);
    sk_ptr_load32(src, 0xc);
    {
        uint64_t w5 = 0;
        dst[5] = w5;                      /* dst[5] = first header word */
        sk_region_decode();               /* FUN_0024ddf0 */
        sk_region_decode();               /* FUN_0024ddf0 */
        dst[3] = 0;
        dst[4] = 0;
    }
    {
        uint32_t n = (uint32_t)sk_rt_001ee0c8(0, src + 0x10).lo; /* FUN_001ee0c8 */
        entries = (uint32_t *)(src + 0x14);
        end = entries + (n & 0xffffff);
        while (entries != end) {
            uint32_t *cur = (uint32_t *)sk_buf_consume4((long *)&entries, 1); /* FUN_0024c56c */
            uint32_t tag = *cur;
            uint32_t idx = tag & 0xffffff;
            switch (tag >> 0x18 & 0x7f) {
            case 1: case 3:
                sk_pte_emit_desc_b(); /* FUN_0024ee1c */
                break;
            case 2:
                sk_pte_follow_index();   /* FUN_0024eed4 */
                {
                    sk_pte_chain_walk(); uint64_t meta = 0; /* FUN_0024ef54 */
                    sk_pte_emit_desc_a(); /* FUN_0024ed74 */
                    (void)meta;
                }
                break;
            case 4:
                /* string/symbol entry */
                if (idx == 2 || idx == 1) {
                    dst[6] = (ulong)(*dst + 4);
                } else {
                    *(uint16_t *)(dst + 2) = 0x100;
                    dst[6] = (ulong)(*dst + 4);
                }
                break;
            default:
                {
                    int *rel = (int *)sk_buf_consume4((long *)&entries, 1); /* FUN_0024c56c */
                    uint64_t relv = (ulong)*rel;
                    uint32_t *target = (uint32_t *)((relv & 1) == 0
                        ? ((long)cur + relv) : sk_rt_001ee0fc(0, (long)cur + (relv - 1)).lo);
                    uint32_t meta = *target;
                    sk_buf_consume4((long *)&entries, idx);   /* FUN_0024c56c */
                    if (meta != 0) {
                        uint32_t attr = *(uint32_t *)sk_buf_consume4((long *)&entries, 1);
                        long sz = (long)sk_pte_size_a(attr);  /* FUN_0024b7f8 */
                        uint32_t *base = target + 1;
                        long len = sk_pte_size_b(meta);       /* FUN_0024b89c */
                        base = (uint32_t *)((long)base + len);
                        uint8_t k2 = (uint8_t)sk_rt_00248ae0(meta).lo; /* FUN_00248ae0 */
                        if ((k2 & 0xff) - 1 < 2) {
                            sk_buf_consume4((long *)&entries, sz); /* FUN_0024c5f4 */
                            sk_pte_emit_desc_b(); /* FUN_0024ee1c */
                        } else {
                            sk_pte_follow_index();  /* FUN_0024eed4 */
                            {
                                uint8_t k3 = (uint8_t)sk_rt_00248ae0(attr).lo; /* FUN_00248ae0 */
                                uint64_t sub = 0;
                                if (k3 == 3 && (attr >> 0x13 & 1) != 0) {
                                    sk_pte_follow_index();
                                    sk_pte_chain_walk();
                                } else {
                                    sk_buf_consume4((long *)&entries, sz);
                                }
                                /* emit attribute + size; advance cursor */
                                sk_pte_emit_desc_a();
                                (void)sub;
                            }
                        }
                        {
                            uint64_t cur2 = *dst;
                            *dst = (cur2 + 4);
                            *dst = (cur2 + 0xb) & ~7ull;
                            *dst = *dst + 0x10;
                            if (keep != 0) *dst = *dst + 8;
                        }
                        if (0 != 0) {       /* pcVar4 != 0 (sub-table) */
                            /* align + advance with sub-table payload */
                        }
                    }
                    break;
                }
            }
            if (entries == (uint32_t *)0 || end == entries) break;
            sk_buf_consume4((long *)&entries, 1);  /* FUN_0024c56c */
            *dst = (*dst + 7) & ~7ull;
            *dst = *dst + 8;
        }
    }
    if (*dst + 7 & ~7ull) {}               /* final align */
    dst[1] = (*dst + 7 & ~7ull) + 8;
    (void)cursor; (void)flags;
}

/* ========================================================================= */
/* FUN_0024e7a4 @ 0x0024e7a4   (est. sk_pte_encode_table2)
 * Ghidra: void FUN_0024e7a4(long param_1,undefined8 *param_2,...)
 * Second table encoder: like sk_pte_encode_table but writes a compact flag
 * record (dst[2]=base, dst[7]=max) and, per entry, builds the descriptor via
 * FUN_0024f498, handling the string/symbol (kind 4) grow-on-append case.
 * Traps on short buffer.
 * Confidence: low.
 */
void sk_pte_encode_table2(long src, uint64_t *dst, long flags, long keep)
{
    uint64_t w0 = sk_ptr_load32(src, 0);  /* FUN_0024e248 */
    sk_ptr_load32(src, 4);
    uint64_t w8 = sk_ptr_load32(src, 8);  /* FUN_0024e248 */
    sk_ptr_load32(src, 0xc);
    dst[2] = w0;
    {
        uint64_t u14 = dst[3];
        sk_region_decode(); long r = 0; /* FUN_0024ddf0 */
        long max = *(long *)(*(long *)(r + -8) + 0x40);
        if (max <= (long)dst[7]) max = (long)dst[7];
        dst[7] = (uint64_t)max;
    }
    {
        uint32_t n = (uint32_t)sk_rt_001ee0c8(0, src + 0x10).lo; /* FUN_001ee0c8 */
        uint32_t *entries = (uint32_t *)(src + 0x14);
        uint32_t *end = entries + (n & 0xffffff);
        while (entries != end) {
            uint32_t *cur = (uint32_t *)sk_buf_consume4((long *)&entries, 1); /* FUN_0024c56c */
            uint32_t tag = *cur;
            uint32_t idx = tag & 0xffffff;
            switch (tag >> 0x18 & 0x7f) {
            case 1: case 3:
                sk_pte_emit_desc_b(); /* FUN_0024ee1c */
                break;
            case 2:
                sk_pte_follow_index();   /* FUN_0024eed4 */
                sk_pte_chain_walk();                  /* FUN_0024ef54 */
                sk_pte_emit_desc_a(); /* FUN_0024ed74 */
                break;
            case 4:
                {
                    /* grow-on-append string entry */
                    uint64_t *str = (uint64_t *)dst[6];
                    uint64_t cnt = sk_rt_003a261c(str).lo; /* FUN_003a261c */
                    if ((cnt & 1) == 0) {
                        str = (uint64_t *)sk_rt_001a0be4(0, *(long *)((long)str + 0x10) + 1, 1, str); /* FUN_001a0be4 */
                        dst[6] = (uint64_t)str;
                    }
                    uint64_t n = *(uint64_t *)((long)str + 0x10);
                    if (*(uint64_t *)((long)str + 0x18) >> 1 <= n) {
                        str = (uint64_t *)sk_rt_001a0be4(1 < *(uint64_t *)((long)str + 0x18), n + 1, 1, str);
                    }
                    *(uint64_t *)((long)str + 0x10) = n + 1;
                    *(char *)((long)str + n + 0x20) = 0;
                    dst[6] = (uint64_t)str;
                    dst[10] = *dst;
                }
                break;
            default:
                {
                    int *rel = (int *)sk_buf_consume4((long *)&entries, 1);
                    uint64_t relv = (ulong)*rel;
                    uint32_t *target = (uint32_t *)((relv & 1) == 0
                        ? ((long)cur + relv) : sk_rt_001ee0fc(0, (long)cur + (relv - 1)).lo);
                    uint32_t meta = *target;
                    sk_buf_consume4((long *)&entries, idx);
                    if (meta != 0) {
                        uint32_t attr = *(uint32_t *)sk_buf_consume4((long *)&entries, 1);
                        long sz = (long)sk_pte_size_a(attr);   /* FUN_0024b7f8 */
                        uint32_t *base = target + 1;
                        long len = sk_pte_size_b(meta);        /* FUN_0024b89c */
                        base = (uint32_t *)((long)base + len);
                        uint8_t k2 = (uint8_t)sk_rt_00248ae0(meta).lo;
                        if ((k2 & 0xff) - 1 < 2) {
                            sk_buf_consume4((long *)&entries, sz);
                            sk_pte_emit_desc_b();
                        } else {
                            sk_pte_follow_index();
                            {
                                uint8_t k3 = (uint8_t)sk_rt_00248ae0(attr).lo;
                                uint64_t sub = 0;
                                if (k3 == 3 && (attr >> 0x13 & 1) != 0) {
                                    sk_pte_follow_index();
                                    sk_pte_chain_walk();
                                } else {
                                    sk_buf_consume4((long *)&entries, sz);
                                }
                                sk_pte_emit_desc_a();
                                (void)sub;
                            }
                        }
                    }
                    break;
                }
            }
            if (entries == (uint32_t *)0 || end == entries) break;
            sk_buf_consume4((long *)&entries, 1);
            *dst = (*dst + 7) & ~7ull;
            *dst = *dst + 8;
        }
    }
    sk_vspace_ctx_ref_a((long)dst[7]);    /* FUN_0024f114 */
    (void)w8; (void)flags;
}

/* ========================================================================= */
/* FUN_0024ed74 @ 0x0024ed74   (est. sk_pte_emit_desc_a)
 * Ghidra: void FUN_0024ed74(undefined8 param_1,undefined8 *param_2)
 * Emits one PTE descriptor: dispatches on the special index values
 * 0x7ffffd/0x7ffffe/0x7fffff (single/empty markers) to resolve the target
 * (FUN_00358470 + sk_ptr_follow), then stamps the "present" flag and writes
 * the descriptor via sk_pte_store_head (FUN_0024f02c).
 * Confidence: low.
 */
void sk_pte_emit_desc_a(void)
{
    uint32_t idx = (uint32_t)0 & 0x7fffff; /* param_1 */
    char special = (char)(idx == 0x7ffffd);
    if (special) {
        sk_rt_00358470();                 /* FUN_00358470 */
        sk_ptr_follow(*(long *)0, *(uint32_t *)0); /* FUN_0024e21c */
    } else if (idx == 0x7ffffe || idx == 0x7fffff) {
        sk_rt_00358470();                 /* FUN_00358470 */
    }
    sk_rt_00248ae0(0);                    /* FUN_00248ae0 */
    sk_rt_003594f4();                     /* FUN_003594f4 */
    sk_pte_store_head(!special, 0 >> 0x17 & 1, 0, 0); /* FUN_0024f02c */
}

/* ========================================================================= */
/* FUN_0024ee1c @ 0x0024ee1c   (est. sk_pte_emit_desc_b)
 * Ghidra: void FUN_0024ee1c(undefined8 param_1,undefined8 *param_2)
 * Emits one PTE descriptor (variant B): same special-index dispatch but also
 * records the resolved word and a 2-bit kind (1/2/3) for the three special
 * markers, then writes via sk_pte_store_head with the extra words
 * (FUN_0024f2a0).
 * Confidence: low.
 */
void sk_pte_emit_desc_b(void)
{
    uint32_t idx = (uint32_t)0 & 0x7fffff;
    uint64_t word = 0;
    uint64_t kind = 0;
    char special = (char)(idx == 0x7ffffd);
    if (special) {
        sk_rt_00358470();                 /* FUN_00358470 */
        word = sk_ptr_follow(*(long *)0, *(uint32_t *)0); /* FUN_0024e21c */
        kind = 3;
    } else if (idx == 0x7ffffe) {
        sk_rt_00358470();                 /* FUN_00358470 */
        word = *(uint32_t *)sk_rt_00358470(); /* FUN_00358470 */
        kind = 2;
    } else if (idx == 0x7fffff) {
        kind = 1;
        sk_rt_00358470();                 /* FUN_00358470 */
        word = *(uint32_t *)sk_rt_00358470();
    } else {
        kind = 0;
    }
    sk_rt_00248ae0(0);                    /* FUN_00248ae0 */
    sk_rt_003594f4();                     /* FUN_003594f4 */
    sk_rt_0024f2a0(!special, 0 >> 0x17 & 1, word, kind); /* FUN_0024f2a0 */
}

/* ========================================================================= */
/* FUN_0024eed4 @ 0x0024eed4   (est. sk_pte_follow_index)
 * Ghidra: void FUN_0024eed4(uint param_1,long *param_2)
 * Follows an indexed pointer in a PTE entry: emits the relative offset, then
 * (when bit 22 is set) the sub-table offset, via FUN_0009461c. Advances the
 * buffer.
 * Confidence: low.
 */
void sk_pte_follow_index(void)
{
    sk_rt_00358470();                     /* FUN_00358470 */
    {
        long base = 0;
        (void)base;
        sk_buf_advance4();                /* FUN_0024c56c */
        int32_t rel = 0;
        long sub = 0;
        sk_rt_0009461c(0, 0, base + rel, sub); /* FUN_0009461c */
    }
}

/* ========================================================================= */
/* FUN_0024ef54 @ 0x0024ef54   (est. sk_pte_chain_walk)
 * Ghidra: void FUN_0024ef54(void)
 * Walks a relocatable PTE chain, following relative pointers until the running
 * offset reaches zero; emits each hop via FUN_003507e0 and FUN_00357c44.
 * Traps if the chain does not terminate.
 * Confidence: low.
 */
void sk_pte_chain_walk(void)
{
    uint32_t tag = (uint32_t)sk_rt_00357ca0(); /* FUN_00357ca0 */
    long acc = 0;
    if ((tag >> 0x13 & 1) == 0) {
        sk_rt_003507e0(tag, (long *)0, 0); /* FUN_003507e0 */
        sk_rt_00357c44();                 /* FUN_00357c44 */
        return;
    }
    acc = *(long *)0;                     /* *extraout_x1 */
    {
        int *rel = (int *)sk_rt_00358470(); /* FUN_00358470 */
        if (acc + *rel != 0) {
            do {
                sk_rt_00351d24();         /* FUN_00351d24 */
                sk_buf_advance4();        /* FUN_0024c56c */
                acc = *(long *)0;
                sk_rt_00351d24();         /* FUN_00351d24 */
                sk_buf_advance4(); /* FUN_0024c56c */
                acc = acc + 0;
            } while (acc != 0);
        }
    }
    sk_rt_00348128();                     /* FUN_00348128 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024f02c @ 0x0024f02c   (est. sk_pte_store_head)
 * Ghidra: void FUN_0024f02c(char param_1,uint param_2,undefined8 param_3,
 *                           char param_4)
 * Stores a PTE head word into the output buffer (x20): writes the 2-bit type
 * tag (0/2 by the "present" flag), then advances the cursor by 4 (or 8 when
 * param_4 is set) via FUN_003542a8.
 * Confidence: medium.
 */
void sk_pte_store_head(char present, uint flags, uint64_t word, char wide)
{
    char tag = 0;
    if ((flags & 1) != 0) {
        if (present == '\0') tag = 0;
        else tag = 2;
    }
    *(char *)(0 + 2) = tag;               /* unaff_x20+2 */
    {
        long cur = *(long *)0;            /* *unaff_x20 */
        long adv = (wide == '\0') ? cur + 4 : cur + 8;
        sk_rt_003542a8(adv);              /* FUN_003542a8 */
    }
    (void)word;
}

/* ========================================================================= */
/* FUN_0024f070 @ 0x0024f070   (est. sk_ptr_align_offset)
 * Ghidra: long FUN_0024f070(undefined8 param_1,long param_2)
 * Returns the buffer base advanced to the next multiple of the owner's byte
 * at +0x50. Align-up helper.
 * Confidence: medium.
 */
long sk_ptr_align_offset(uint64_t a, long p)
{
    ulong m = *(byte *)(*(long *)(p + -8) + 0x50);
    ulong base = *(ulong *)0;             /* *unaff_x20 */
    long pad = 0;
    if ((base & m) != 0) {
        pad = (long)((m - (base & m)) + 1);
    }
    (void)a;
    return (long)(base + pad);
}

/* ========================================================================= */
/* FUN_0024f0a0 @ 0x0024f0a0   (est. sk_buf_store_aligned32)
 * Ghidra: void FUN_0024f0a0(undefined4 param_1)
 * Stores a u32 into the output buffer aligned to 4; advances the cursor via
 * FUN_00359bd4; traps on short buffer.
 * Confidence: medium.
 */
void sk_buf_store_aligned32(uint32_t v)
{
    uint64_t base = *(uint64_t *)0;       /* *unaff_x20 */
    long pad = 0;
    if ((base & 3) != 0) pad = 4 - (base & 3);
    *(uint32_t *)(base + pad) = v;
    {
        long avail = -4;
        if (base != 0) avail = (*(long *)((char *)0 + 8) - base) + -4;
        if (avail >= pad) {
            sk_rt_00359bd4();             /* FUN_00359bd4 */
            return;
        }
        sk_rt_003483c4();                 /* FUN_003483c4 */
        sk_rt_00351094();                 /* FUN_00351094 */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
}

/* ========================================================================= */
/* FUN_0024f114 @ 0x0024f114   (est. sk_buf_finalize)
 * Ghidra: void FUN_0024f114(void)
 * Finalizes the output buffer: records the final base (FUN_00356a50), writes
 * the count (FUN_00357b60) and commits via FUN_00359bd4; traps if the new
 * range is negative.
 * Confidence: medium.
 */
void sk_buf_finalize(void)
{
    uint64_t u = sk_rt_00356a50();        /* FUN_00356a50 */
    *(uint64_t *)0 = u;                   /* *extraout_x8 */
    sk_rt_00357b60((void *)((char *)0 + 8)); /* FUN_00357b60 */
    if (0 >= 0) {                         /* extraout_x10 - extraout_x9 */
        sk_rt_00359bd4();                 /* FUN_00359bd4 */
        return;
    }
    sk_rt_003483c4();                     /* FUN_003483c4 */
    sk_rt_00351094();                     /* FUN_00351094 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}

/* ========================================================================= */
/* FUN_0024f15c @ 0x0024f15c   (est. sk_buf_trim)
 * Ghidra: void FUN_0024f15c(void)
 * Trims the output buffer to the descriptor length (vtable+0x40) minus a
 * caller word (x22), committing the new {base,end} via the align helpers;
 * traps on short buffer.
 * Confidence: medium.
 */
void sk_buf_trim(void)
{
    long hdr;
    sk_rt_00353a0c();                     /* FUN_00353a0c */
    sk_rt_0034ece8();                     /* FUN_0034ece8 */
    hdr = *(long *)(0 + 0x40);            /* extraout_x16+0x40 */
    sk_ptr_align_offset(0, 0);            /* FUN_0024f070 */
    sk_rt_00353918();                     /* FUN_00353918 */
    sk_rt_00359024();                     /* FUN_00359024 */
    sk_rt_00354714();                     /* FUN_00354714 */
    sk_vspace_ctx_commit2();              /* FUN_00249294 */
    {
        long avail = 0;
        if (*(long *)0 != 0) avail = *(long *)((char *)0 + 8) - *(long *)0;
        long rem = (avail - hdr) - 0;     /* - unaff_x22 */
        if (rem >= 0) {
            *(long *)0 = 0 + hdr;          /* unaff_x19 + hdr */
            *(long *)((char *)0 + 8) = 0 + hdr + rem;
            return;
        }
        sk_rt_003483c4();                 /* FUN_003483c4 */
        sk_rt_00351094();                 /* FUN_00351094 */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
}

/* ========================================================================= */
/* FUN_0024f23c @ 0x0024f23c   (est. sk_buf_finalize2)
 * Ghidra: void FUN_0024f23c(void)
 * Finalizes the output buffer (variant B): like sk_buf_finalize but traps on
 * a zero base (FUN_00347f2c) before committing.
 * Confidence: medium.
 */
void sk_buf_finalize2(void)
{
    uint64_t u = sk_rt_00356a50();        /* FUN_00356a50 */
    if (u == 0) {
        sk_rt_00347f2c();                 /* FUN_00347f2c */
        sk_rt_fatal_001afe4c();           /* FUN_001afe4c */
    }
    *(uint64_t *)0 = u;                   /* *extraout_x8 */
    sk_rt_00357b60((void *)((char *)0 + 8)); /* FUN_00357b60 */
    if (0 >= 0) {                         /* extraout_x10 - extraout_x9 */
        sk_rt_00359bd4();                 /* FUN_00359bd4 */
        return;
    }
    sk_rt_003483c4();                     /* FUN_003483c4 */
    sk_rt_00351094();                     /* FUN_00351094 */
    sk_rt_fatal_001afe4c();               /* FUN_001afe4c */
}
