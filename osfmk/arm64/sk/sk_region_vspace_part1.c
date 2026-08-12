/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Part file (slice 1, 0x208a90..0x20e624): the vspace/MMU object-model layer.
 * A Swift-based class hierarchy (vspace / page-table objects) with a large
 * 'method must be overridden' abstract vtable, Swift runtime glue, and MMU
 * bookkeeping. Names use cL4/seL4 vocabulary; all estimates unless string
 * matched. Callees beyond 0x200000-0x280000 (Swift runtime, kernel helpers)
 * are declared extern; their bodies are owned by other range workers.
 * */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* Ghidra base types used by decompiled signatures/bodies. */
typedef uint8_t  undefined1;
typedef uint16_t undefined2;
typedef uint32_t undefined4;
typedef uint64_t undefined8;
typedef uint8_t  undefined;
typedef uint64_t undefined7;
typedef unsigned long ulong;
typedef unsigned int uint;
typedef uint8_t byte;
typedef uint64_t (*code)();  /* Ghidra 'code *' -> fn-ptr */
/* Swift 16-byte existential container (two words). */
typedef struct { uint64_t _0_8_; uint64_t _8_8_; } sk_ex16;

/* Ghidra pseudo-builtins used by decompiled Swift string/collection code. */
static inline unsigned sk_lzcount(unsigned v){ return v ? (unsigned)__builtin_clz(v) : 32u; }
static inline uint64_t sk_concat71(uint64_t hi, uint64_t lo){ return (hi << 8) | (lo & 0xff); }
static inline uint64_t sk_concat44(uint32_t hi, uint32_t lo){ return ((uint64_t)hi << 32) | (uint32_t)lo; }
static inline uint64_t sk_concat31(uint32_t hi, uint8_t lo){ return ((uint64_t)hi << 8) | lo; }
static inline uint64_t sk_concat43(uint32_t hi, uint32_t lo){ return ((uint64_t)hi << 24) | (lo & 0xffffff); }
static inline bool sk_scarry8(uint64_t a, uint64_t b){ return (a + b) < a; }
static inline uint64_t sk_sw_brk(uint64_t kind, uint64_t pc){ (void)kind; (void)pc; return 0; }

/* ------------------------------------------------------------------ *
 * Out-of-range shared callees (extern; FUN_ address in comment). Most are the
 * Swift runtime / stdlib used by the object model; a few are kernel helpers.
 * FUN_002085a4 is the in-kernel 'method must be overridden' fatal panic.
 * ------------------------------------------------------------------ */
  extern uint64_t sk_rt_00002534();  /* FUN_00002534 */
  extern uint64_t sk_rt_000027e8();  /* FUN_000027e8 */
  extern uint64_t sk_rt_000262fc();  /* FUN_000262fc */
  extern uint64_t sk_rt_00027754();  /* FUN_00027754 */
  extern uint64_t sk_rt_00027788();  /* FUN_00027788 */
  extern uint64_t sk_rt_000277b8();  /* FUN_000277b8 */
  extern uint64_t sk_rt_00027818();  /* FUN_00027818 */
  extern uint64_t sk_rt_0006f6b4();  /* FUN_0006f6b4 */
  extern uint64_t sk_rt_00077894();  /* FUN_00077894 */
  extern uint64_t sk_rt_0007c0c4();  /* FUN_0007c0c4 */
  extern uint64_t sk_rt_0007c1a4();  /* FUN_0007c1a4 */
  extern uint64_t sk_rt_0007c1c4();  /* FUN_0007c1c4 */
  extern uint64_t sk_rt_0008409c();  /* FUN_0008409c */
  extern uint64_t sk_rt_000841a0();  /* FUN_000841a0 */
  extern uint64_t sk_rt_00084220();  /* FUN_00084220 */
  extern uint64_t sk_rt_00084234();  /* FUN_00084234 */
  extern uint64_t sk_rt_0008e388();  /* FUN_0008e388 */
  extern uint64_t sk_rt_0008e500();  /* FUN_0008e500 */
  extern uint64_t sk_rt_0008e518();  /* FUN_0008e518 */
  extern uint64_t sk_rt_000a0c8c();  /* FUN_000a0c8c */
  extern uint64_t sk_rt_000a6894();  /* FUN_000a6894 */
  extern uint64_t sk_rt_000a68c4();  /* FUN_000a68c4 */
  extern uint64_t sk_rt_000a68f4();  /* FUN_000a68f4 */
  extern uint64_t sk_rt_000a6e14();  /* FUN_000a6e14 */
  extern uint64_t sk_rt_000a6f68();  /* FUN_000a6f68 */
  extern uint64_t sk_rt_000a6f88();  /* FUN_000a6f88 */
  extern uint64_t sk_rt_000aa47c();  /* FUN_000aa47c */
  extern uint64_t sk_rt_000b4390();  /* FUN_000b4390 */
  extern uint64_t sk_rt_000bd3a4();  /* FUN_000bd3a4 */
  extern uint64_t sk_rt_000dbd0c();  /* FUN_000dbd0c */
  extern uint64_t sk_rt_000dbe0c();  /* FUN_000dbe0c */
  extern uint64_t sk_rt_000dbf08();  /* FUN_000dbf08 */
  extern uint64_t sk_rt_000e15d8();  /* FUN_000e15d8 */
  extern uint64_t sk_rt_00100efc();  /* FUN_00100efc */
  extern uint64_t sk_rt_00167404();  /* FUN_00167404 */
  extern uint64_t sk_rt_0018de98();  /* FUN_0018de98 */
  extern uint64_t sk_rt_0019e410();  /* FUN_0019e410 */
  extern uint64_t sk_rt_0019e538();  /* FUN_0019e538 */
  extern uint64_t sk_rt_0019e578();  /* FUN_0019e578 */
  extern uint64_t sk_rt_0019e728();  /* FUN_0019e728 */
  extern uint64_t sk_rt_001a0414();  /* FUN_001a0414 */
  extern uint64_t sk_rt_001afa84() __attribute__((noreturn));  /* FUN_001afa84 */
  extern uint64_t sk_rt_001afe4c() __attribute__((noreturn));  /* FUN_001afe4c */
  extern uint64_t sk_rt_001d30f8();  /* FUN_001d30f8 */
  extern uint64_t sk_rt_001d31b0();  /* FUN_001d31b0 */
  extern uint64_t sk_rt_001d88fc();  /* FUN_001d88fc */
  extern uint64_t sk_rt_001dc298();  /* FUN_001dc298 */
  extern uint64_t sk_rt_001dc430();  /* FUN_001dc430 */
  extern uint64_t sk_rt_001dc554();  /* FUN_001dc554 */
  extern uint64_t sk_rt_001ee030();  /* FUN_001ee030 */
  extern uint64_t sk_rt_002085a4();  /* FUN_002085a4 */
  extern uint64_t sk_rt_002085fc();  /* FUN_002085fc */
  extern uint64_t sk_rt_0020eabc();  /* FUN_0020eabc */
  extern uint64_t sk_rt_00210bd4();  /* FUN_00210bd4 */
  extern uint64_t sk_rt_00213460();  /* FUN_00213460 */
  extern uint64_t sk_rt_002527e8();  /* FUN_002527e8 */
  extern uint64_t sk_rt_00275780();  /* FUN_00275780 */
  extern uint64_t sk_rt_002805b8();  /* FUN_002805b8 */
  extern uint64_t sk_rt_00280ad8();  /* FUN_00280ad8 */
  extern uint64_t sk_rt_00281128();  /* FUN_00281128 */
  extern uint64_t sk_rt_002a9ba8();  /* FUN_002a9ba8 */
  extern uint64_t sk_rt_002a9d64();  /* FUN_002a9d64 */
  extern uint64_t sk_rt_002ab4d4();  /* FUN_002ab4d4 */
  extern uint64_t sk_swift_00310924();  /* FUN_00310924 */
  extern uint64_t sk_swift_00310cd4();  /* FUN_00310cd4 */
  extern uint64_t sk_swift_00310d68();  /* FUN_00310d68 */
  extern uint64_t sk_swift_00310d80();  /* FUN_00310d80 */
  extern uint64_t sk_swift_00310da8();  /* FUN_00310da8 */
  extern uint64_t sk_swift_00310df0();  /* FUN_00310df0 */
  extern uint64_t sk_swift_00310e08();  /* FUN_00310e08 */
  extern uint64_t sk_swift_00310e20();  /* FUN_00310e20 */
  extern uint64_t sk_swift_003191e8();  /* FUN_003191e8 */
  extern uint64_t sk_swift_003192d8();  /* FUN_003192d8 */
  extern uint64_t sk_swift_003193f4();  /* FUN_003193f4 */
  extern uint64_t sk_swift_0031afcc();  /* FUN_0031afcc */
  extern uint64_t sk_swift_0031b62c();  /* FUN_0031b62c */
  extern uint64_t sk_swift_0031b978();  /* FUN_0031b978 */
  extern uint64_t sk_swift_0031b990();  /* FUN_0031b990 */
  extern uint64_t sk_swift_0031b9c0();  /* FUN_0031b9c0 */
  extern uint64_t sk_swift_0031b9d8();  /* FUN_0031b9d8 */
  extern uint64_t sk_swift_0031ba08();  /* FUN_0031ba08 */
  extern uint64_t sk_swift_0031ba24();  /* FUN_0031ba24 */
  extern uint64_t sk_swift_0031ba3c();  /* FUN_0031ba3c */
  extern uint64_t sk_swift_00346ff4();  /* FUN_00346ff4 */
  extern uint64_t sk_swift_00347d60();  /* FUN_00347d60 */
  extern uint64_t sk_swift_00347ef4();  /* FUN_00347ef4 */
  extern uint64_t sk_swift_003488bc();  /* FUN_003488bc */
  extern uint64_t sk_swift_003488f4();  /* FUN_003488f4 */
  extern uint64_t sk_swift_003489c0();  /* FUN_003489c0 */
  extern uint64_t sk_swift_00348a18();  /* FUN_00348a18 */
  extern uint64_t sk_swift_00348a9c();  /* FUN_00348a9c */
  extern uint64_t sk_swift_00348abc();  /* FUN_00348abc */
  extern uint64_t sk_swift_00348b1c();  /* FUN_00348b1c */
  extern uint64_t sk_swift_00348cd0();  /* FUN_00348cd0 */
  extern uint64_t sk_swift_00348ce8();  /* FUN_00348ce8 */
  extern uint64_t sk_swift_00348d4c();  /* FUN_00348d4c */
  extern uint64_t sk_swift_00348d64();  /* FUN_00348d64 */
  extern uint64_t sk_swift_00348d7c();  /* FUN_00348d7c */
  extern uint64_t sk_swift_00348e00();  /* FUN_00348e00 */
  extern uint64_t sk_swift_00348e60();  /* FUN_00348e60 */
  extern uint64_t sk_swift_00348fd8();  /* FUN_00348fd8 */
  extern uint64_t sk_swift_00349068();  /* FUN_00349068 */
  extern uint64_t sk_swift_003490ec();  /* FUN_003490ec */
  extern uint64_t sk_swift_0034911c();  /* FUN_0034911c */
  extern uint64_t sk_swift_00349190();  /* FUN_00349190 */
  extern uint64_t sk_swift_003494e8();  /* FUN_003494e8 */
  extern uint64_t sk_swift_00349618();  /* FUN_00349618 */
  extern uint64_t sk_swift_00349734();  /* FUN_00349734 */
  extern uint64_t sk_swift_00349748();  /* FUN_00349748 */
  extern uint64_t sk_swift_003498f4();  /* FUN_003498f4 */
  extern uint64_t sk_swift_0034998c();  /* FUN_0034998c */
  extern uint64_t sk_swift_003499b4();  /* FUN_003499b4 */
  extern uint64_t sk_swift_003499f0();  /* FUN_003499f0 */
  extern uint64_t sk_swift_00349a18();  /* FUN_00349a18 */
  extern uint64_t sk_swift_00349c14();  /* FUN_00349c14 */
  extern uint64_t sk_swift_00349c58();  /* FUN_00349c58 */
  extern uint64_t sk_swift_00349c70();  /* FUN_00349c70 */
  extern uint64_t sk_swift_00349db0();  /* FUN_00349db0 */
  extern uint64_t sk_swift_00349e10();  /* FUN_00349e10 */
  extern uint64_t sk_swift_0034a210();  /* FUN_0034a210 */
  extern uint64_t sk_swift_0034a37c();  /* FUN_0034a37c */
  extern uint64_t sk_swift_0034a3ec();  /* FUN_0034a3ec */
  extern uint64_t sk_swift_0034a450();  /* FUN_0034a450 */
  extern uint64_t sk_swift_0034a5c8();  /* FUN_0034a5c8 */
  extern uint64_t sk_swift_0034a654();  /* FUN_0034a654 */
  extern uint64_t sk_swift_0034a868();  /* FUN_0034a868 */
  extern uint64_t sk_swift_0034aa54();  /* FUN_0034aa54 */
  extern uint64_t sk_swift_0034aab0();  /* FUN_0034aab0 */
  extern uint64_t sk_swift_0034ab20();  /* FUN_0034ab20 */
  extern uint64_t sk_swift_0034ab9c();  /* FUN_0034ab9c */
  extern uint64_t sk_swift_0034abc4();  /* FUN_0034abc4 */
  extern uint64_t sk_swift_0034ac64();  /* FUN_0034ac64 */
  extern uint64_t sk_swift_0034ad8c();  /* FUN_0034ad8c */
  extern uint64_t sk_swift_0034aee4();  /* FUN_0034aee4 */
  extern uint64_t sk_swift_0034af20();  /* FUN_0034af20 */
  extern uint64_t sk_swift_0034b014();  /* FUN_0034b014 */
  extern uint64_t sk_swift_0034b05c();  /* FUN_0034b05c */
  extern uint64_t sk_swift_0034b07c();  /* FUN_0034b07c */
  extern uint64_t sk_swift_0034b0c4();  /* FUN_0034b0c4 */
  extern uint64_t sk_swift_0034b0d4();  /* FUN_0034b0d4 */
  extern uint64_t sk_swift_0034b278();  /* FUN_0034b278 */
  extern uint64_t sk_swift_0034b2c8();  /* FUN_0034b2c8 */
  extern uint64_t sk_swift_0034b2f8();  /* FUN_0034b2f8 */
  extern uint64_t sk_swift_0034b328();  /* FUN_0034b328 */
  extern uint64_t sk_swift_0034b348();  /* FUN_0034b348 */
  extern uint64_t sk_swift_0034b3d8();  /* FUN_0034b3d8 */
  extern uint64_t sk_swift_0034b460();  /* FUN_0034b460 */
  extern uint64_t sk_swift_0034b5bc();  /* FUN_0034b5bc */
  extern uint64_t sk_swift_0034b5fc();  /* FUN_0034b5fc */
  extern uint64_t sk_swift_0034b7b8();  /* FUN_0034b7b8 */
  extern uint64_t sk_swift_0034b7e4();  /* FUN_0034b7e4 */
  extern uint64_t sk_swift_0034b8bc();  /* FUN_0034b8bc */
  extern uint64_t sk_swift_0034ba38();  /* FUN_0034ba38 */
  extern uint64_t sk_swift_0034bab8();  /* FUN_0034bab8 */
  extern uint64_t sk_swift_0034bdfc();  /* FUN_0034bdfc */
  extern uint64_t sk_swift_0034beb4();  /* FUN_0034beb4 */
  extern uint64_t sk_swift_0034bec4();  /* FUN_0034bec4 */
  extern uint64_t sk_swift_0034c1bc();  /* FUN_0034c1bc */
  extern uint64_t sk_swift_0034c1e4();  /* FUN_0034c1e4 */
  extern uint64_t sk_swift_0034c20c();  /* FUN_0034c20c */
  extern uint64_t sk_swift_0034c2d8();  /* FUN_0034c2d8 */
  extern uint64_t sk_swift_0034c354();  /* FUN_0034c354 */
  extern uint64_t sk_swift_0034c444();  /* FUN_0034c444 */
  extern uint64_t sk_swift_0034c454();  /* FUN_0034c454 */
  extern uint64_t sk_swift_0034c4bc();  /* FUN_0034c4bc */
  extern uint64_t sk_swift_0034c55c();  /* FUN_0034c55c */
  extern uint64_t sk_swift_0034c56c();  /* FUN_0034c56c */
  extern uint64_t sk_swift_0034c58c();  /* FUN_0034c58c */
  extern uint64_t sk_swift_0034c6a4();  /* FUN_0034c6a4 */
  extern uint64_t sk_swift_0034c704();  /* FUN_0034c704 */
  extern uint64_t sk_swift_0034c8f8();  /* FUN_0034c8f8 */
  extern uint64_t sk_swift_0034c930();  /* FUN_0034c930 */
  extern uint64_t sk_swift_0034c998();  /* FUN_0034c998 */
  extern uint64_t sk_swift_0034ca28();  /* FUN_0034ca28 */
  extern uint64_t sk_swift_0034cca8();  /* FUN_0034cca8 */
  extern uint64_t sk_swift_0034cd2c();  /* FUN_0034cd2c */
  extern uint64_t sk_swift_0034cd7c();  /* FUN_0034cd7c */
  extern uint64_t sk_swift_0034cf04();  /* FUN_0034cf04 */
  extern uint64_t sk_swift_0034d014();  /* FUN_0034d014 */
  extern uint64_t sk_swift_0034d070();  /* FUN_0034d070 */
  extern uint64_t sk_swift_0034d080();  /* FUN_0034d080 */
  extern uint64_t sk_swift_0034d130();  /* FUN_0034d130 */
  extern uint64_t sk_swift_0034d284();  /* FUN_0034d284 */
  extern uint64_t sk_swift_0034d394();  /* FUN_0034d394 */
  extern uint64_t sk_swift_0034d3c4();  /* FUN_0034d3c4 */
  extern uint64_t sk_swift_0034d464();  /* FUN_0034d464 */
  extern uint64_t sk_swift_0034d598();  /* FUN_0034d598 */
  extern uint64_t sk_swift_0034d634();  /* FUN_0034d634 */
  extern uint64_t sk_swift_0034d758();  /* FUN_0034d758 */
  extern uint64_t sk_swift_0034d7dc();  /* FUN_0034d7dc */
  extern uint64_t sk_swift_0034d8d4();  /* FUN_0034d8d4 */
  extern uint64_t sk_swift_0034da48();  /* FUN_0034da48 */
  extern uint64_t sk_swift_0034db58();  /* FUN_0034db58 */
  extern uint64_t sk_swift_0034de8c();  /* FUN_0034de8c */
  extern uint64_t sk_swift_0034dfe4();  /* FUN_0034dfe4 */
  extern uint64_t sk_swift_0034e0a4();  /* FUN_0034e0a4 */
  extern uint64_t sk_swift_0034e1b0();  /* FUN_0034e1b0 */
  extern uint64_t sk_swift_0034e3cc();  /* FUN_0034e3cc */
  extern uint64_t sk_swift_0034e3e4();  /* FUN_0034e3e4 */
  extern uint64_t sk_swift_0034e414();  /* FUN_0034e414 */
  extern uint64_t sk_swift_0034e57c();  /* FUN_0034e57c */
  extern uint64_t sk_swift_0034e5cc();  /* FUN_0034e5cc */
  extern uint64_t sk_swift_0034e6fc();  /* FUN_0034e6fc */
  extern uint64_t sk_swift_0034e924();  /* FUN_0034e924 */
  extern uint64_t sk_swift_0034ea18();  /* FUN_0034ea18 */
  extern uint64_t sk_swift_0034eb84();  /* FUN_0034eb84 */
  extern uint64_t sk_swift_0034eb94();  /* FUN_0034eb94 */
  extern uint64_t sk_swift_0034ecb8();  /* FUN_0034ecb8 */
  extern uint64_t sk_swift_0034ece8();  /* FUN_0034ece8 */
  extern uint64_t sk_swift_0034ed28();  /* FUN_0034ed28 */
  extern uint64_t sk_swift_0034ed78();  /* FUN_0034ed78 */
  extern uint64_t sk_swift_0034ee18();  /* FUN_0034ee18 */
  extern uint64_t sk_swift_0034ee68();  /* FUN_0034ee68 */
  extern uint64_t sk_swift_0034f274();  /* FUN_0034f274 */
  extern uint64_t sk_swift_0034f344();  /* FUN_0034f344 */
  extern uint64_t sk_swift_0034f4a4();  /* FUN_0034f4a4 */
  extern uint64_t sk_swift_0034f5b4();  /* FUN_0034f5b4 */
  extern uint64_t sk_swift_0034f644();  /* FUN_0034f644 */
  extern uint64_t sk_swift_0034f788();  /* FUN_0034f788 */
  extern uint64_t sk_swift_0034f860();  /* FUN_0034f860 */
  extern uint64_t sk_swift_0034f9c8();  /* FUN_0034f9c8 */
  extern uint64_t sk_swift_0034fc34();  /* FUN_0034fc34 */
  extern uint64_t sk_swift_0034ff98();  /* FUN_0034ff98 */
  extern uint64_t sk_swift_003500c0();  /* FUN_003500c0 */
  extern uint64_t sk_swift_003502e8();  /* FUN_003502e8 */
  extern uint64_t sk_swift_00350410();  /* FUN_00350410 */
  extern uint64_t sk_swift_00350428();  /* FUN_00350428 */
  extern uint64_t sk_swift_00350464();  /* FUN_00350464 */
  extern uint64_t sk_swift_00350470();  /* FUN_00350470 */
  extern uint64_t sk_swift_00350488();  /* FUN_00350488 */
  extern uint64_t sk_swift_003504a0();  /* FUN_003504a0 */
  extern uint64_t sk_swift_003504ac();  /* FUN_003504ac */
  extern uint64_t sk_swift_003504c4();  /* FUN_003504c4 */
  extern uint64_t sk_swift_00350500();  /* FUN_00350500 */
  extern uint64_t sk_swift_0035050c();  /* FUN_0035050c */
  extern uint64_t sk_swift_00350518();  /* FUN_00350518 */
  extern uint64_t sk_swift_00350524();  /* FUN_00350524 */
  extern uint64_t sk_swift_00350530();  /* FUN_00350530 */
  extern uint64_t sk_swift_0035056c();  /* FUN_0035056c */
  extern uint64_t sk_swift_003505e8();  /* FUN_003505e8 */
  extern uint64_t sk_swift_003505f4();  /* FUN_003505f4 */
  extern uint64_t sk_swift_0035060c();  /* FUN_0035060c */
  extern uint64_t sk_swift_00350618();  /* FUN_00350618 */
  extern uint64_t sk_swift_00350630();  /* FUN_00350630 */
  extern uint64_t sk_swift_0035063c();  /* FUN_0035063c */
  extern uint64_t sk_swift_0035066c();  /* FUN_0035066c */
  extern uint64_t sk_swift_003506b0();  /* FUN_003506b0 */
  extern uint64_t sk_swift_0035072c();  /* FUN_0035072c */
  extern uint64_t sk_swift_00350738();  /* FUN_00350738 */
  extern uint64_t sk_swift_00350780();  /* FUN_00350780 */
  extern uint64_t sk_swift_00350798();  /* FUN_00350798 */
  extern uint64_t sk_swift_003507d4();  /* FUN_003507d4 */
  extern uint64_t sk_swift_00350804();  /* FUN_00350804 */
  extern uint64_t sk_swift_0035084c();  /* FUN_0035084c */
  extern uint64_t sk_swift_003508a8();  /* FUN_003508a8 */
  extern uint64_t sk_swift_003508b4();  /* FUN_003508b4 */
  extern uint64_t sk_swift_003508c0();  /* FUN_003508c0 */
  extern uint64_t sk_swift_003508cc();  /* FUN_003508cc */
  extern uint64_t sk_swift_003508d8();  /* FUN_003508d8 */
  extern uint64_t sk_swift_003508e4();  /* FUN_003508e4 */
  extern uint64_t sk_swift_003508f0();  /* FUN_003508f0 */
  extern uint64_t sk_swift_00350920();  /* FUN_00350920 */
  extern uint64_t sk_swift_00350944();  /* FUN_00350944 */
  extern uint64_t sk_swift_00350950();  /* FUN_00350950 */
  extern uint64_t sk_swift_00350974();  /* FUN_00350974 */
  extern uint64_t sk_swift_003509b0();  /* FUN_003509b0 */
  extern uint64_t sk_swift_003509e0();  /* FUN_003509e0 */
  extern uint64_t sk_swift_00350a64();  /* FUN_00350a64 */
  extern uint64_t sk_swift_00350a70();  /* FUN_00350a70 */
  extern uint64_t sk_swift_00350a88();  /* FUN_00350a88 */
  extern uint64_t sk_swift_00350ab8();  /* FUN_00350ab8 */
  extern uint64_t sk_swift_00350af4();  /* FUN_00350af4 */
  extern uint64_t sk_swift_00350b00();  /* FUN_00350b00 */
  extern uint64_t sk_swift_00350b24();  /* FUN_00350b24 */
  extern uint64_t sk_swift_00350b60();  /* FUN_00350b60 */
  extern uint64_t sk_swift_00350b6c();  /* FUN_00350b6c */
  extern uint64_t sk_swift_00350b9c();  /* FUN_00350b9c */
  extern uint64_t sk_swift_00350c08();  /* FUN_00350c08 */
  extern uint64_t sk_swift_00350c20();  /* FUN_00350c20 */
  extern uint64_t sk_swift_00350c50();  /* FUN_00350c50 */
  extern uint64_t sk_swift_00350c68();  /* FUN_00350c68 */
  extern uint64_t sk_swift_00350c80();  /* FUN_00350c80 */
  extern uint64_t sk_swift_00350c8c();  /* FUN_00350c8c */
  extern uint64_t sk_swift_00350c98();  /* FUN_00350c98 */
  extern uint64_t sk_swift_00350ca4();  /* FUN_00350ca4 */
  extern uint64_t sk_swift_00350de4();  /* FUN_00350de4 */
  extern uint64_t sk_swift_00350e24();  /* FUN_00350e24 */
  extern uint64_t sk_swift_003510a0();  /* FUN_003510a0 */
  extern uint64_t sk_swift_00351118();  /* FUN_00351118 */
  extern uint64_t sk_swift_00351190();  /* FUN_00351190 */
  extern uint64_t sk_swift_003511d8();  /* FUN_003511d8 */
  extern uint64_t sk_swift_003511f0();  /* FUN_003511f0 */
  extern uint64_t sk_swift_00351238();  /* FUN_00351238 */
  extern uint64_t sk_swift_0035125c();  /* FUN_0035125c */
  extern uint64_t sk_swift_0035133c();  /* FUN_0035133c */
  extern uint64_t sk_swift_00351348();  /* FUN_00351348 */
  extern uint64_t sk_swift_00351384();  /* FUN_00351384 */
  extern uint64_t sk_swift_003513c0();  /* FUN_003513c0 */
  extern uint64_t sk_swift_00351408();  /* FUN_00351408 */
  extern uint64_t sk_swift_00351414();  /* FUN_00351414 */
  extern uint64_t sk_swift_00351444();  /* FUN_00351444 */
  extern uint64_t sk_swift_0035147c();  /* FUN_0035147c */
  extern uint64_t sk_swift_003514e8();  /* FUN_003514e8 */
  extern uint64_t sk_swift_00351560();  /* FUN_00351560 */
  extern uint64_t sk_swift_003515a8();  /* FUN_003515a8 */
  extern uint64_t sk_swift_003516cc();  /* FUN_003516cc */
  extern uint64_t sk_swift_003518b8();  /* FUN_003518b8 */
  extern uint64_t sk_swift_00351900();  /* FUN_00351900 */
  extern uint64_t sk_swift_00351a44();  /* FUN_00351a44 */
  extern uint64_t sk_swift_00351a68();  /* FUN_00351a68 */
  extern uint64_t sk_swift_00351a98();  /* FUN_00351a98 */
  extern uint64_t sk_swift_00351ad4();  /* FUN_00351ad4 */
  extern uint64_t sk_swift_00351c1c();  /* FUN_00351c1c */
  extern uint64_t sk_swift_00351d9c();  /* FUN_00351d9c */
  extern uint64_t sk_swift_00351dcc();  /* FUN_00351dcc */
  extern uint64_t sk_swift_00351dd8();  /* FUN_00351dd8 */
  extern uint64_t sk_swift_00351eb4();  /* FUN_00351eb4 */
  extern uint64_t sk_swift_00351ecc();  /* FUN_00351ecc */
  extern uint64_t sk_swift_00351f40();  /* FUN_00351f40 */
  extern uint64_t sk_swift_00351f64();  /* FUN_00351f64 */
  extern uint64_t sk_swift_00351fb0();  /* FUN_00351fb0 */
  extern uint64_t sk_swift_00352188();  /* FUN_00352188 */
  extern uint64_t sk_swift_003521a4();  /* FUN_003521a4 */
  extern uint64_t sk_swift_00352260();  /* FUN_00352260 */
  extern uint64_t sk_swift_0035238c();  /* FUN_0035238c */
  extern uint64_t sk_swift_003523f0();  /* FUN_003523f0 */
  extern uint64_t sk_swift_00352420();  /* FUN_00352420 */
  extern uint64_t sk_swift_00352680();  /* FUN_00352680 */
  extern uint64_t sk_swift_00352758();  /* FUN_00352758 */
  extern uint64_t sk_swift_00352894();  /* FUN_00352894 */
  extern uint64_t sk_swift_00352980();  /* FUN_00352980 */
  extern uint64_t sk_swift_00352b74();  /* FUN_00352b74 */
  extern uint64_t sk_swift_00352ba4();  /* FUN_00352ba4 */
  extern uint64_t sk_swift_00352dc4();  /* FUN_00352dc4 */
  extern uint64_t sk_swift_00352df4();  /* FUN_00352df4 */
  extern uint64_t sk_swift_00352e18();  /* FUN_00352e18 */
  extern uint64_t sk_swift_00352eb4();  /* FUN_00352eb4 */
  extern uint64_t sk_swift_00352ff4();  /* FUN_00352ff4 */
  extern uint64_t sk_swift_00353100();  /* FUN_00353100 */
  extern uint64_t sk_swift_0035313c();  /* FUN_0035313c */
  extern uint64_t sk_swift_00353160();  /* FUN_00353160 */
  extern uint64_t sk_swift_0035316c();  /* FUN_0035316c */
  extern uint64_t sk_swift_0035336c();  /* FUN_0035336c */
  extern uint64_t sk_swift_00353474();  /* FUN_00353474 */
  extern uint64_t sk_swift_0035359c();  /* FUN_0035359c */
  extern uint64_t sk_swift_003536ac();  /* FUN_003536ac */
  extern uint64_t sk_swift_003536d0();  /* FUN_003536d0 */
  extern uint64_t sk_swift_003537c4();  /* FUN_003537c4 */
  extern uint64_t sk_swift_00353860();  /* FUN_00353860 */
  extern uint64_t sk_swift_0035399c();  /* FUN_0035399c */
  extern uint64_t sk_swift_003539d8();  /* FUN_003539d8 */
  extern uint64_t sk_swift_00353a6c();  /* FUN_00353a6c */
  extern uint64_t sk_swift_00353aac();  /* FUN_00353aac */
  extern uint64_t sk_swift_00353bdc();  /* FUN_00353bdc */
  extern uint64_t sk_swift_00353be8();  /* FUN_00353be8 */
  extern uint64_t sk_swift_00353c24();  /* FUN_00353c24 */
  extern uint64_t sk_swift_00353c6c();  /* FUN_00353c6c */
  extern uint64_t sk_swift_00353c78();  /* FUN_00353c78 */
  extern uint64_t sk_swift_00353cfc();  /* FUN_00353cfc */
  extern uint64_t sk_swift_00353d14();  /* FUN_00353d14 */
  extern uint64_t sk_swift_00353f38();  /* FUN_00353f38 */
  extern uint64_t sk_swift_0035407c();  /* FUN_0035407c */
  extern uint64_t sk_swift_00354264();  /* FUN_00354264 */
  extern uint64_t sk_swift_003542f4();  /* FUN_003542f4 */
  extern uint64_t sk_swift_00354324();  /* FUN_00354324 */
  extern uint64_t sk_swift_00354330();  /* FUN_00354330 */
  extern uint64_t sk_swift_00354370();  /* FUN_00354370 */
  extern uint64_t sk_swift_00354388();  /* FUN_00354388 */
  extern uint64_t sk_swift_0035454c();  /* FUN_0035454c */
  extern uint64_t sk_swift_00354594();  /* FUN_00354594 */
  extern uint64_t sk_swift_00354804();  /* FUN_00354804 */
  extern uint64_t sk_swift_003548b8();  /* FUN_003548b8 */
  extern uint64_t sk_swift_003549d8();  /* FUN_003549d8 */
  extern uint64_t sk_swift_00354b5c();  /* FUN_00354b5c */
  extern uint64_t sk_swift_00354cfc();  /* FUN_00354cfc */
  extern uint64_t sk_swift_00354dd0();  /* FUN_00354dd0 */
  extern uint64_t sk_swift_0035525c();  /* FUN_0035525c */
  extern uint64_t sk_swift_00355604();  /* FUN_00355604 */
  extern uint64_t sk_swift_00355684();  /* FUN_00355684 */
  extern uint64_t sk_swift_003558d8();  /* FUN_003558d8 */
  extern uint64_t sk_swift_00355908();  /* FUN_00355908 */
  extern uint64_t sk_swift_00355b04();  /* FUN_00355b04 */
  extern uint64_t sk_swift_00355b10();  /* FUN_00355b10 */
  extern uint64_t sk_swift_00355b74();  /* FUN_00355b74 */
  extern uint64_t sk_swift_00355bb8();  /* FUN_00355bb8 */
  extern uint64_t sk_swift_00355c1c();  /* FUN_00355c1c */
  extern uint64_t sk_swift_00355c84();  /* FUN_00355c84 */
  extern uint64_t sk_swift_00355e68();  /* FUN_00355e68 */
  extern uint64_t sk_swift_00355f04();  /* FUN_00355f04 */
  extern uint64_t sk_swift_00356090();  /* FUN_00356090 */
  extern uint64_t sk_swift_00356194();  /* FUN_00356194 */
  extern uint64_t sk_swift_00356218();  /* FUN_00356218 */
  extern uint64_t sk_swift_00356230();  /* FUN_00356230 */
  extern uint64_t sk_swift_00356278();  /* FUN_00356278 */
  extern uint64_t sk_swift_00356310();  /* FUN_00356310 */
  extern uint64_t sk_swift_00356a14();  /* FUN_00356a14 */
  extern uint64_t sk_swift_00356b8c();  /* FUN_00356b8c */
  extern uint64_t sk_swift_00356c54();  /* FUN_00356c54 */
  extern uint64_t sk_swift_00356ce0();  /* FUN_00356ce0 */
  extern uint64_t sk_swift_00356f6c();  /* FUN_00356f6c */
  extern uint64_t sk_swift_00357050();  /* FUN_00357050 */
  extern uint64_t sk_swift_00357944();  /* FUN_00357944 */
  extern uint64_t sk_swift_00357a0c();  /* FUN_00357a0c */
  extern uint64_t sk_swift_00357a9c();  /* FUN_00357a9c */
  extern uint64_t sk_swift_00357aa8();  /* FUN_00357aa8 */
  extern uint64_t sk_swift_00357b48();  /* FUN_00357b48 */
  extern uint64_t sk_swift_00357c20();  /* FUN_00357c20 */
  extern uint64_t sk_swift_00357cc8();  /* FUN_00357cc8 */
  extern uint64_t sk_swift_00357e44();  /* FUN_00357e44 */
  extern uint64_t sk_swift_00358114();  /* FUN_00358114 */
  extern uint64_t sk_swift_00358490();  /* FUN_00358490 */
  extern uint64_t sk_swift_003586cc();  /* FUN_003586cc */
  extern uint64_t sk_swift_00358aa4();  /* FUN_00358aa4 */
  extern uint64_t sk_swift_00358ba8();  /* FUN_00358ba8 */
  extern uint64_t sk_swift_00358ce0();  /* FUN_00358ce0 */
  extern uint64_t sk_swift_00358cec();  /* FUN_00358cec */
  extern uint64_t sk_swift_00358eb8();  /* FUN_00358eb8 */
  extern uint64_t sk_swift_00358f54();  /* FUN_00358f54 */
  extern uint64_t sk_swift_00358fb4();  /* FUN_00358fb4 */
  extern uint64_t sk_swift_00358fc8();  /* FUN_00358fc8 */
  extern uint64_t sk_swift_00359388();  /* FUN_00359388 */
  extern uint64_t sk_swift_003593c0();  /* FUN_003593c0 */
  extern uint64_t sk_swift_00359628();  /* FUN_00359628 */
  extern uint64_t sk_swift_00359bec();  /* FUN_00359bec */
  extern uint64_t sk_swift_00359c70();  /* FUN_00359c70 */
  extern uint64_t sk_swift_00359f3c();  /* FUN_00359f3c */
  extern uint64_t sk_swift_0035a128();  /* FUN_0035a128 */
  extern uint64_t sk_swift_0035a140();  /* FUN_0035a140 */
  extern uint64_t sk_swift_0035a1f4();  /* FUN_0035a1f4 */
  extern uint64_t sk_swift_0035a298();  /* FUN_0035a298 */
  extern uint64_t sk_swift_0035a3f4();  /* FUN_0035a3f4 */
  extern uint64_t sk_swift_0035a42c();  /* FUN_0035a42c */
  extern uint64_t sk_swift_0035a4d4();  /* FUN_0035a4d4 */
  extern uint64_t sk_swift_0035a7c0();  /* FUN_0035a7c0 */
  extern uint64_t sk_swift_0035a7d4();  /* FUN_0035a7d4 */
  extern uint64_t sk_swift_00362acc();  /* FUN_00362acc */
  extern uint64_t sk_swift_0036a940();  /* FUN_0036a940 */
  extern uint64_t sk_swift_0036b118();  /* FUN_0036b118 */
  extern uint64_t sk_swift_0036b270();  /* FUN_0036b270 */
  extern uint64_t sk_swift_0036b6ac();  /* FUN_0036b6ac */
  extern uint64_t sk_swift_00376820();  /* FUN_00376820 */
  extern uint64_t sk_swift_00377824();  /* FUN_00377824 */
  extern uint64_t sk_swift_00377bec();  /* FUN_00377bec */

/* Out-of-range data globals (DAT_*). sk_data_00658c00 is a Swift runtime
   dispatch (function-pointer) slot. */
extern uint64_t sk_data_004f2110;  /* DAT_004f2110 */
extern uint64_t sk_data_004f2148;  /* DAT_004f2148 */
extern uint64_t sk_data_0060e208;  /* DAT_0060e208 */
extern uint64_t sk_data_0060e22c;  /* DAT_0060e22c */
extern uint64_t sk_data_0060e230;  /* DAT_0060e230 */
extern uint64_t sk_data_0060e218;  /* DAT_0060e218 */
extern uint64_t sk_data_00657630;  /* DAT_00657630 */
extern uint64_t sk_data_00657668;  /* DAT_00657668 */
extern uint64_t sk_data_00657778;  /* DAT_00657778 */
extern uint64_t sk_data_00657788;  /* DAT_00657788 */
extern uint64_t sk_data_00657790;  /* DAT_00657790 */
extern uint64_t sk_data_00657798;  /* DAT_00657798 */
extern void (*sk_data_00658c00)();  /* DAT_00658c00 (fn ptr) */

/* Out-of-range string literals (s_*; used by Swift fatal-error paths). */
extern const char sk_str_Fatal_error_005accd0[];  /* s_Fatal_error_005accd0 */
extern const char sk_str_Index_out_of_range_005cd940[];  /* s_Index_out_of_range_005cd940 */
extern const char sk_str_Range_requires_lowerBound____upp_005cda00[];  /* s_Range_requires_lowerBound_<__upp_005cda00 */
extern const char sk_str_Swift_ExistentialCollection_swif_005cf680[];  /* s_Swift_ExistentialCollection_swif_005cf680 */
extern const char sk_str_Swift_Range_swift_005cda30[];  /* s_Swift_Range_swift_005cda30 */
extern const char sk_str_Swift_Sequence_swift_005cf730[];  /* s_Swift_Sequence_swift_005cf730 */
extern const char sk_str_Swift_UnicodeHelpers_swift_005ce730[];  /* s_Swift_UnicodeHelpers_swift_005ce730 */
extern const char sk_str_Unexpectedly_found_nil_while_unw_005cd7d0[];  /* s_Unexpectedly_found_nil_while_unw_005cd7d0 */

/* In-slice forward declarations (K&R unspecified-arity so flattened call sites
   with dropped arguments still compile against the typed definitions). */
void sk_vspace_00208a90();
void sk_vspace_00208ab0();
void sk_vspace_00208ad0();
void sk_vspace_00208af0();
void sk_vspace_00208b10();
void sk_vspace_00208b30();
void sk_vspace_00208b50();
void sk_vspace_00208b70();
void sk_vspace_00208b90();
void sk_vspace_00208bb0();
void sk_vspace_00208bd0();
void sk_vspace_00208bf8();
void sk_vspace_00208bfc();
void sk_vspace_00208c18();
void sk_vspace_00208c1c();
void sk_vspace_00208c3c();
void sk_vspace_00208c5c();
void sk_vspace_00208c7c();
void sk_vspace_00208c9c();
void sk_vspace_00208cbc();
void sk_vspace_00208cdc();
void sk_vspace_00208cfc();
void sk_vspace_00208d1c();
void sk_vspace_00208d3c();
void sk_vspace_00208d5c();
void sk_vspace_00208d7c();
void sk_vspace_00208d9c();
void sk_vspace_00208dbc();
void sk_vspace_00208ddc();
void sk_vspace_00208e38();
void sk_vspace_00208e60();
void sk_vspace_00208e88();
void sk_vspace_00208e8c();
void sk_vspace_00208eac();
void sk_vspace_00208ecc();
void sk_vspace_00208eec();
void sk_vspace_00208f0c();
void sk_vspace_00208f2c();
void sk_vspace_00208f4c();
void sk_vspace_00208f6c();
void sk_vspace_00208f8c();
void sk_vspace_00208fac();
void sk_vspace_00208fcc();
void sk_vspace_00208fd0();
void sk_vspace_00208ff0();
void sk_vspace_00209010();
void sk_vspace_00209030();
void sk_vspace_00209050();
void sk_vspace_00209070();
void sk_vspace_00209090();
void sk_vspace_002091d0();
void sk_vspace_002092a8();
undefined * sk_vspace_002093d4();
undefined * sk_vspace_00209928();
void sk_vspace_00209f18();
void sk_vspace_0020a058();
void sk_vspace_0020a05c();
void sk_vspace_0020a084();
void sk_vspace_0020a2d8();
void sk_vspace_0020a3b0();
undefined8 sk_vspace_0020a5c0();
void sk_vspace_0020a6ac();
void sk_vspace_0020a770();
void sk_vspace_0020a8fc();
void sk_vspace_0020a918();
void sk_vspace_0020a930();
void sk_vspace_0020aa80();
void sk_vspace_0020aabc();
void sk_vspace_0020adfc();
void sk_vspace_0020af20();
void sk_vspace_0020af3c();
void sk_vspace_0020af40();
void sk_vspace_0020af68();
void sk_vspace_0020b044();
void sk_vspace_0020b28c();
void sk_vspace_0020b358();
void sk_vspace_0020b7e8();
void sk_vspace_0020b844();
void sk_vspace_0020b8b0();
void sk_vspace_0020b8b4();
void sk_vspace_0020b9f4();
void sk_vspace_0020bb18();
void sk_vspace_0020bbf0();
void sk_vspace_0020bd1c();
void sk_vspace_0020bde4();
undefined8 sk_vspace_0020bec4();
void sk_vspace_0020bfb0();
void sk_vspace_0020c074();
void sk_vspace_0020c1a0();
void sk_vspace_0020c1a4();
void sk_vspace_0020c1bc();
void sk_vspace_0020c204();
void sk_vspace_0020c34c();
void sk_vspace_0020c350();
void sk_vspace_0020c368();
void sk_vspace_0020c4d4();
void sk_vspace_0020c5b0();
void sk_vspace_0020c634();
void sk_vspace_0020c6c8();
void sk_vspace_0020c7fc();
void sk_vspace_0020c814();
void sk_vspace_0020cb24();
void sk_vspace_0020d0c4();
void sk_vspace_0020d3b0();
void sk_vspace_0020d620();
void sk_vspace_0020d75c();
void sk_vspace_0020dc18();
void sk_vspace_0020ddd8();
void sk_vspace_0020df00();
void sk_vspace_0020dfdc();
void sk_vspace_0020e114();
void sk_vspace_0020e1d8();
undefined8 sk_vspace_0020e2c0();
void sk_vspace_0020e3b0();
void sk_vspace_0020e478();
void sk_vspace_0020e5a4();
void sk_vspace_0020e5a8();
void sk_vspace_0020e5c0();
void sk_vspace_0020e608();
void sk_vspace_0020e60c();
void sk_vspace_0020e624();
/* FUN_00208a90 @ 0x00208a90   (est. sk_vspace_00208a90)
 * Ghidra: void FUN_00208a90(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208a90(void)
{
    /* Abstract vtable slot (method index 0xd3): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0xd3);
}


/* FUN_00208ab0 @ 0x00208ab0   (est. sk_vspace_00208ab0)
 * Ghidra: void FUN_00208ab0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208ab0(void)
{
    /* Abstract vtable slot (method index 0xd8): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0xd8);
}


/* FUN_00208ad0 @ 0x00208ad0   (est. sk_vspace_00208ad0)
 * Ghidra: void FUN_00208ad0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208ad0(void)
{
    /* Abstract vtable slot (method index 0xdf): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0xdf);
}


/* FUN_00208af0 @ 0x00208af0   (est. sk_vspace_00208af0)
 * Ghidra: void FUN_00208af0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208af0(void)
{
    /* Abstract vtable slot (method index 0xea): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0xea);
}


/* FUN_00208b10 @ 0x00208b10   (est. sk_vspace_00208b10)
 * Ghidra: void FUN_00208b10(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208b10(void)
{
    /* Abstract vtable slot (method index 0xef): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0xef);
}


/* FUN_00208b30 @ 0x00208b30   (est. sk_vspace_00208b30)
 * Ghidra: void FUN_00208b30(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208b30(void)
{
    /* Abstract vtable slot (method index 0xf4): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0xf4);
}


/* FUN_00208b50 @ 0x00208b50   (est. sk_vspace_00208b50)
 * Ghidra: void FUN_00208b50(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208b50(void)
{
    /* Abstract vtable slot (method index 0xf9): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0xf9);
}


/* FUN_00208b70 @ 0x00208b70   (est. sk_vspace_00208b70)
 * Ghidra: void FUN_00208b70(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208b70(void)
{
    /* Abstract vtable slot (method index 0x100): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x100);
}


/* FUN_00208b90 @ 0x00208b90   (est. sk_vspace_00208b90)
 * Ghidra: void FUN_00208b90(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208b90(void)
{
    /* Abstract vtable slot (method index 0x105): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x105);
}


/* FUN_00208bb0 @ 0x00208bb0   (est. sk_vspace_00208bb0)
 * Ghidra: void FUN_00208bb0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208bb0(void)

{
  long rxx20;
  
  sk_swift_0036b118(*(undefined8 *)(rxx20 + 0x10));
  sk_swift_0036b118(*(undefined8 *)(rxx20 + 0x20));
  return;
}

/* FUN_00208bd0 @ 0x00208bd0   (est. sk_vspace_00208bd0)
 * Ghidra: void FUN_00208bd0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208bd0(void)

{
  long rxx20;
  
  sk_swift_0036b118(*(undefined8 *)(rxx20 + 0x10));
  sk_swift_0036b118(*(undefined8 *)(rxx20 + 0x20));
  return;
}

/* FUN_00208bf8 @ 0x00208bf8   (est. sk_vspace_00208bf8)
 * Ghidra: void FUN_00208bf8(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208bf8(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_00208bfc @ 0x00208bfc   (est. sk_vspace_00208bfc)
 * Ghidra: void FUN_00208bfc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208bfc(void)

{
  sk_vspace_00208bd0();
  sk_swift_00353aac();
  sk_swift_0036b6ac();
  return;
}

/* FUN_00208c18 @ 0x00208c18   (est. sk_vspace_00208c18)
 * Ghidra: void FUN_00208c18(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208c18(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_00208c1c @ 0x00208c1c   (est. sk_vspace_00208c1c)
 * Ghidra: void FUN_00208c1c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208c1c(void)
{
    /* Abstract vtable slot (method index 0x118): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x118);
}


/* FUN_00208c3c @ 0x00208c3c   (est. sk_vspace_00208c3c)
 * Ghidra: void FUN_00208c3c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208c3c(void)
{
    /* Abstract vtable slot (method index 0x11d): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x11d);
}


/* FUN_00208c5c @ 0x00208c5c   (est. sk_vspace_00208c5c)
 * Ghidra: void FUN_00208c5c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208c5c(void)
{
    /* Abstract vtable slot (method index 0x122): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x122);
}


/* FUN_00208c7c @ 0x00208c7c   (est. sk_vspace_00208c7c)
 * Ghidra: void FUN_00208c7c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208c7c(void)
{
    /* Abstract vtable slot (method index 0x129): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x129);
}


/* FUN_00208c9c @ 0x00208c9c   (est. sk_vspace_00208c9c)
 * Ghidra: void FUN_00208c9c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208c9c(void)
{
    /* Abstract vtable slot (method index 0x130): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x130);
}


/* FUN_00208cbc @ 0x00208cbc   (est. sk_vspace_00208cbc)
 * Ghidra: void FUN_00208cbc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208cbc(void)
{
    /* Abstract vtable slot (method index 0x135): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x135);
}


/* FUN_00208cdc @ 0x00208cdc   (est. sk_vspace_00208cdc)
 * Ghidra: void FUN_00208cdc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208cdc(void)
{
    /* Abstract vtable slot (method index 0x139): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x139);
}


/* FUN_00208cfc @ 0x00208cfc   (est. sk_vspace_00208cfc)
 * Ghidra: void FUN_00208cfc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208cfc(void)
{
    /* Abstract vtable slot (method index 0x13c): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x13c);
}


/* FUN_00208d1c @ 0x00208d1c   (est. sk_vspace_00208d1c)
 * Ghidra: void FUN_00208d1c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208d1c(void)
{
    /* Abstract vtable slot (method index 0x13f): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x13f);
}


/* FUN_00208d3c @ 0x00208d3c   (est. sk_vspace_00208d3c)
 * Ghidra: void FUN_00208d3c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208d3c(void)
{
    /* Abstract vtable slot (method index 0x146): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x146);
}


/* FUN_00208d5c @ 0x00208d5c   (est. sk_vspace_00208d5c)
 * Ghidra: void FUN_00208d5c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208d5c(void)
{
    /* Abstract vtable slot (method index 0x14f): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x14f);
}


/* FUN_00208d7c @ 0x00208d7c   (est. sk_vspace_00208d7c)
 * Ghidra: void FUN_00208d7c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208d7c(void)
{
    /* Abstract vtable slot (method index 0x154): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x154);
}


/* FUN_00208d9c @ 0x00208d9c   (est. sk_vspace_00208d9c)
 * Ghidra: void FUN_00208d9c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208d9c(void)
{
    /* Abstract vtable slot (method index 0x15d): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x15d);
}


/* FUN_00208dbc @ 0x00208dbc   (est. sk_vspace_00208dbc)
 * Ghidra: void FUN_00208dbc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208dbc(void)
{
    /* Abstract vtable slot (method index 0x165): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x165);
}


/* FUN_00208ddc @ 0x00208ddc   (est. sk_vspace_00208ddc)
 * Ghidra: void FUN_00208ddc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208ddc(void)
{
    /* Abstract vtable slot (method index 0x176): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x176);
}


/* FUN_00208e38 @ 0x00208e38   (est. sk_vspace_00208e38)
 * Ghidra: void FUN_00208e38(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208e38(void)

{
  long rxx20;
  
  sk_swift_0036b270(*(undefined8 *)(rxx20 + 0x10));
  return;
}

/* FUN_00208e60 @ 0x00208e60   (est. sk_vspace_00208e60)
 * Ghidra: void FUN_00208e60(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208e60(void)

{
  long rxx20;
  
  sk_swift_0036b270(*(undefined8 *)(rxx20 + 0x20));
  return;
}

/* FUN_00208e88 @ 0x00208e88   (est. sk_vspace_00208e88)
 * Ghidra: void FUN_00208e88(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208e88(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_00208e8c @ 0x00208e8c   (est. sk_vspace_00208e8c)
 * Ghidra: void FUN_00208e8c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208e8c(void)
{
    /* Abstract vtable slot (method index 0x191): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x191);
}


/* FUN_00208eac @ 0x00208eac   (est. sk_vspace_00208eac)
 * Ghidra: void FUN_00208eac(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208eac(void)
{
    /* Abstract vtable slot (method index 0x1a0): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1a0);
}


/* FUN_00208ecc @ 0x00208ecc   (est. sk_vspace_00208ecc)
 * Ghidra: void FUN_00208ecc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208ecc(void)
{
    /* Abstract vtable slot (method index 0x1a7): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1a7);
}


/* FUN_00208eec @ 0x00208eec   (est. sk_vspace_00208eec)
 * Ghidra: void FUN_00208eec(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208eec(void)
{
    /* Abstract vtable slot (method index 0x1ae): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1ae);
}


/* FUN_00208f0c @ 0x00208f0c   (est. sk_vspace_00208f0c)
 * Ghidra: void FUN_00208f0c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208f0c(void)
{
    /* Abstract vtable slot (method index 0x1b5): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1b5);
}


/* FUN_00208f2c @ 0x00208f2c   (est. sk_vspace_00208f2c)
 * Ghidra: void FUN_00208f2c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208f2c(void)
{
    /* Abstract vtable slot (method index 0x1bc): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1bc);
}


/* FUN_00208f4c @ 0x00208f4c   (est. sk_vspace_00208f4c)
 * Ghidra: void FUN_00208f4c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208f4c(void)
{
    /* Abstract vtable slot (method index 0x1c3): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1c3);
}


/* FUN_00208f6c @ 0x00208f6c   (est. sk_vspace_00208f6c)
 * Ghidra: void FUN_00208f6c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208f6c(void)
{
    /* Abstract vtable slot (method index 0x1ca): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1ca);
}


/* FUN_00208f8c @ 0x00208f8c   (est. sk_vspace_00208f8c)
 * Ghidra: void FUN_00208f8c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208f8c(void)
{
    /* Abstract vtable slot (method index 0x1cd): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1cd);
}


/* FUN_00208fac @ 0x00208fac   (est. sk_vspace_00208fac)
 * Ghidra: void FUN_00208fac(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208fac(void)
{
    /* Abstract vtable slot (method index 0x1d0): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1d0);
}


/* FUN_00208fcc @ 0x00208fcc   (est. sk_vspace_00208fcc)
 * Ghidra: void FUN_00208fcc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208fcc(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_00208fd0 @ 0x00208fd0   (est. sk_vspace_00208fd0)
 * Ghidra: void FUN_00208fd0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208fd0(void)
{
    /* Abstract vtable slot (method index 0x1df): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1df);
}


/* FUN_00208ff0 @ 0x00208ff0   (est. sk_vspace_00208ff0)
 * Ghidra: void FUN_00208ff0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00208ff0(void)
{
    /* Abstract vtable slot (method index 0x1e6): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1e6);
}


/* FUN_00209010 @ 0x00209010   (est. sk_vspace_00209010)
 * Ghidra: void FUN_00209010(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00209010(void)
{
    /* Abstract vtable slot (method index 0x1ed): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1ed);
}


/* FUN_00209030 @ 0x00209030   (est. sk_vspace_00209030)
 * Ghidra: void FUN_00209030(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00209030(void)
{
    /* Abstract vtable slot (method index 0x1f4): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1f4);
}


/* FUN_00209050 @ 0x00209050   (est. sk_vspace_00209050)
 * Ghidra: void FUN_00209050(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00209050(void)
{
    /* Abstract vtable slot (method index 0x1fb): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x1fb);
}


/* FUN_00209070 @ 0x00209070   (est. sk_vspace_00209070)
 * Ghidra: void FUN_00209070(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00209070(void)
{
    /* Abstract vtable slot (method index 0x202): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x202);
}


/* FUN_00209090 @ 0x00209090   (est. sk_vspace_00209090)
 * Ghidra: void FUN_00209090(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00209090(void)
{
    /* Abstract vtable slot (method index 0x209): base-class virtual
       method that the concrete subclass must override. Loads Swift
       type metadata, then raises the 'method must be overridden'
       fatal error. */
    (void)sk_swift_00357cc8();
    sk_rt_002085a4(0x209);
}


/* FUN_002091d0 @ 0x002091d0   (est. sk_vspace_002091d0)
 * Ghidra: void FUN_002091d0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_002091d0(void)

{
  code *eox8;
  code *eox8_00;
  code *eox10;
  long eox16;
  long eox16_00;
  long eox16_01;
  undefined8 u1;
  undefined8 u2;
  sk_ex16 au3;
  
  sk_swift_0034c998();
  u2 = *(undefined8 *)(eox16 + 0xb8);
  sk_swift_00349734();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b2f8();
  sk_swift_0035147c();
  au3 = (sk_ex16){ (uint64_t)sk_swift_0034b5bc(*(undefined8 *)(eox16_00 + 200)), 0 };
  (*eox10)(au3._0_8_,au3._8_8_,u2);
  sk_swift_0035147c();
  u1 = *(undefined8 *)(eox16_01 + 0xc0);
  sk_rt_000a6894(u1);
  u2 = sk_swift_0034b328();
  (*eox8)(u2,u1);
  sk_swift_0034ea18();
  (*eox8_00)();
  sk_swift_00356c54();
  return;
}

/* FUN_002092a8 @ 0x002092a8   (est. sk_vspace_002092a8)
 * Ghidra: void FUN_002092a8(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_002092a8(void)

{
  undefined8 u1;
  code *eox8;
  code *eox10;
  long eox16;
  long eox16_00;
  undefined8 is00000018;
  uint8_t auStack_40[32];
  undefined8 l20;
  
  sk_swift_00353cfc();
  sk_swift_0034d634();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_00352ff4();
  sk_swift_0034c1bc(*(undefined8 *)(eox16 + 200));
  (*eox10)();
  sk_swift_0035a1f4();
  l20 = *(undefined8 *)(eox16_00 + 0xc0);
  sk_swift_0034a210();
  sk_rt_00002534();
  sk_swift_00351560(sk_swift_00346ff4,auStack_40);
  sk_swift_00358eb8();
  sk_rt_000a0c8c();
  sk_swift_00354dd0();
  sk_swift_0034f9c8();
  (*eox8)();
  u1 = sk_swift_00352df4();
  sk_swift_00353d14(u1,is00000018);
  return;
}

/* FUN_002093d4 @ 0x002093d4   (est. sk_vspace_002093d4)
 * Ghidra: undefined * FUN_002093d4(ulong param_1,ulong param_2)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
undefined * sk_vspace_002093d4(ulong p1,ulong p2)

{
  long lVar1;
  ulong u2;
  ulong u3;
  ulong u4;
  bool bVar5;
  ulong u6;
  long lVar7;
  char *pcVar8;
  undefined8 u9;
  byte *pbVar10;
  uint u11;
  long lVar12;
  undefined8 isffffffffffffff40;
  undefined7 u13;
  undefined8 isffffffffffffff48;
  undefined4 u15;
  undefined8 u14;
  ulong l70;
  ulong l68;
  
  u6 = sk_rt_001ee030(p1,p2,sk_rt_002a9d64);
  sk_rt_0018de98(0,u6 & ((long)u6 >> 0x3f ^ 0xffffffffffffffffU),0);
  u3 = p1 & 0xffffffffffff;
  if ((p2 & 0x2000000000000000) != 0) {
    u3 = p2 >> 0x38 & 0xf;
  }
  if ((long)u6 < 0) {
    u14 = 0x2f9;
    u13 = (undefined7)((ulong)isffffffffffffff40 >> 8);
    pcVar8 = sk_str_Range_requires_lowerBound____upp_005cda00;
    u9 = 0x27;
L_00209648:
                    /* WARNING: Subroutine does not return */
    sk_rt_001afe4c(sk_str_Fatal_error_005accd0,0xb,2,pcVar8,u9,2,sk_str_Swift_Range_swift_005cda30,0x11,
                 sk_concat71(u13,2),u14,1);
  }
  lVar12 = 0;
  lVar1 = (p2 & 0xfffffffffffffff) + 0x20;
  if (u6 == 0) {
    bVar5 = (p2 & 0x1000000000000000) == 0;
  }
  else {
    do {
      u15 = (undefined4)((ulong)isffffffffffffff48 >> 0x20);
      u13 = (undefined7)((ulong)isffffffffffffff40 >> 8);
      if (u6 == 0) {
        u14 = 0x136;
        pcVar8 = sk_str_Index_out_of_range_005cd940;
        u9 = 0x12;
        goto L_00209648;
      }
      if ((long)u3 <= lVar12) {
                    /* WARNING: Subroutine does not return */
        sk_rt_001afe4c(sk_str_Fatal_error_005accd0,0xb,2,sk_str_Unexpectedly_found_nil_while_unw_005cd7d0,0x39,2
                     ,sk_str_Swift_Sequence_swift_005cf730,0x14,sk_concat71(u13,2),699,1);
      }
      if ((p2 >> 0x3c & 1) != 0) goto L_002097e4;
      if ((p2 >> 0x3d & 1) == 0) {
        lVar7 = lVar1;
        if ((p1 & 0x1000000000000000) == 0) {
          lVar7 = sk_rt_002a9ba8(p1,p2);
        }
        pbVar10 = (byte *)(lVar7 + lVar12);
        u11 = (uint)*pbVar10;
        if (-1 < (char)*pbVar10) goto cd_00209504_1;
        switch((int)sk_lzcount(u11 << 0x18 ^ 0xffffffff)) {
        default:
          goto cd_00209504_1;
        case 2:
cd_00209504_2:
          u11 = pbVar10[1] & 0x3f | (u11 & 0x1f) << 6;
          lVar7 = 2;
          break;
        case 3:
cd_00209504_3:
          u11 = (u11 & 0xf) << 0xc | (pbVar10[1] & 0x3f) << 6 | pbVar10[2] & 0x3f;
          lVar7 = 3;
          break;
        case 4:
cd_00209504_4:
          u11 = (u11 & 0xf) << 0x12 | (pbVar10[1] & 0x3f) << 0xc | (pbVar10[2] & 0x3f) << 6 |
                   pbVar10[3] & 0x3f;
          lVar7 = 4;
        }
      }
      else {
        l70 = p1;
        l68 = p2 & 0xffffffffffffff;
        pbVar10 = (byte *)((long)&l70 + lVar12);
        u11 = (uint)*pbVar10;
        if ((char)*pbVar10 < '\0') {
          switch((int)sk_lzcount(u11 << 0x18 ^ 0xffffffff)) {
          case 2:
            goto cd_00209504_2;
          case 3:
            goto cd_00209504_3;
          case 4:
            goto cd_00209504_4;
          }
        }
cd_00209504_1:
        lVar7 = 1;
      }
      u4 = sk_data_00657788;
      u2 = sk_data_00657788 + 1;
      if (sk_data_00657790 >> 1 <= sk_data_00657788) {
        sk_rt_0018de98(1 < sk_data_00657790,u2,1);
      }
      lVar12 = lVar7 + lVar12;
      sk_data_00657788 = u2;
      *(uint *)((long)&sk_data_00657798 + u4 * 4) = u11;
      u6 = u6 - 1;
    } while (u6 != 0);
    bVar5 = true;
  }
  do {
    u15 = (undefined4)((ulong)isffffffffffffff48 >> 0x20);
    if ((long)u3 <= lVar12) {
      return &sk_data_00657778;
    }
    if (!bVar5) {
L_002097e4:
                    /* WARNING: Subroutine does not return */
      sk_rt_001afa84(sk_str_Fatal_error_005accd0,0xb,2,0xd000000000000034,0x80000000005ce6d0,
                   sk_str_Swift_UnicodeHelpers_swift_005ce730,0x1a,2,0xfd,sk_concat44(u15,1));
    }
    if ((p2 >> 0x3d & 1) == 0) {
      lVar7 = lVar1;
      if ((p1 & 0x1000000000000000) == 0) {
        lVar7 = sk_rt_002a9ba8(p1,p2);
      }
      pbVar10 = (byte *)(lVar7 + lVar12);
      u11 = (uint)*pbVar10;
      if (-1 < (char)*pbVar10) goto cd_002096e8_1;
      switch((int)sk_lzcount(u11 << 0x18 ^ 0xffffffff)) {
      default:
        goto cd_002096e8_1;
      case 2:
cd_002096e8_2:
        u11 = pbVar10[1] & 0x3f | (u11 & 0x1f) << 6;
        lVar7 = 2;
        break;
      case 3:
cd_002096e8_3:
        u11 = (u11 & 0xf) << 0xc | (pbVar10[1] & 0x3f) << 6 | pbVar10[2] & 0x3f;
        lVar7 = 3;
        break;
      case 4:
cd_002096e8_4:
        u11 = (u11 & 0xf) << 0x12 | (pbVar10[1] & 0x3f) << 0xc | (pbVar10[2] & 0x3f) << 6 |
                 pbVar10[3] & 0x3f;
        lVar7 = 4;
      }
    }
    else {
      l70 = p1;
      l68 = p2 & 0xffffffffffffff;
      pbVar10 = (byte *)((long)&l70 + lVar12);
      u11 = (uint)*pbVar10;
      if ((char)*pbVar10 < '\0') {
        switch((int)sk_lzcount(u11 << 0x18 ^ 0xffffffff)) {
        case 2:
          goto cd_002096e8_2;
        case 3:
          goto cd_002096e8_3;
        case 4:
          goto cd_002096e8_4;
        }
      }
cd_002096e8_1:
      lVar7 = 1;
    }
    u2 = sk_data_00657788;
    u6 = sk_data_00657788 + 1;
    if (sk_data_00657790 >> 1 <= sk_data_00657788) {
      sk_rt_0018de98(1 < sk_data_00657790,u6,1);
    }
    lVar12 = lVar7 + lVar12;
    sk_data_00657788 = u6;
    *(uint *)((long)&sk_data_00657798 + u2 * 4) = u11;
  } while( true );
}

/* FUN_00209928 @ 0x00209928   (est. sk_vspace_00209928)
 * Ghidra: undefined * FUN_00209928(ulong param_1,ulong param_2,ulong param_3,ulong param_4)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
undefined * sk_vspace_00209928(ulong p1,ulong p2,ulong p3,ulong p4)

{
  ulong u1;
  byte bVar2;
  bool bVar3;
  ulong u4;
  ulong u5;
  long lVar6;
  ulong u7;
  char *pcVar8;
  undefined8 u9;
  uint u10;
  ulong u11;
  byte *pbVar12;
  uint u13;
  ulong u14;
  undefined8 isffffffffffffff40;
  undefined7 u15;
  undefined8 isffffffffffffff48;
  undefined4 u17;
  undefined8 u16;
  long la0;
  ulong uStack_98;
  ulong l70;
  ulong uStack_68;
  
  u4 = sk_rt_002a9d64();
  sk_rt_0018de98(0,u4 & ((long)u4 >> 0x3f ^ 0xffffffffffffffffU),0);
  if ((long)u4 < 0) {
    u16 = 0x2f9;
    u15 = (undefined7)((ulong)isffffffffffffff40 >> 8);
    pcVar8 = sk_str_Range_requires_lowerBound____upp_005cda00;
    u9 = 0x27;
L_00209be0:
                    /* WARNING: Subroutine does not return */
    sk_rt_001afe4c(sk_str_Fatal_error_005accd0,0xb,2,pcVar8,u9,2,sk_str_Swift_Range_swift_005cda30,0x11,
                 sk_concat71(u15,2),u16,1);
  }
  u14 = p4 & 0x2000000000000000;
  u11 = p4 & 0xffffffffffffff;
  u7 = p1;
  if (u4 == 0) {
    la0 = (p4 & 0xfffffffffffffff) + 0x20;
    bVar3 = (p4 & 0x1000000000000000) == 0;
  }
  else {
    la0 = (p4 & 0xfffffffffffffff) + 0x20;
    do {
      u15 = (undefined7)((ulong)isffffffffffffff40 >> 8);
      if (u4 == 0) {
        u16 = 0x136;
        pcVar8 = sk_str_Index_out_of_range_005cd940;
        u9 = 0x12;
        goto L_00209be0;
      }
      if ((u7 ^ p2) < 0x4000) {
                    /* WARNING: Subroutine does not return */
        sk_rt_001afe4c(sk_str_Fatal_error_005accd0,0xb,2,sk_str_Unexpectedly_found_nil_while_unw_005cd7d0,0x39,2
                     ,sk_str_Swift_Sequence_swift_005cf730,0x14,sk_concat71(u15,2),699,1);
      }
      u5 = sk_rt_002ab4d4(u7,p1,p2,p3,p4);
      u17 = (undefined4)((ulong)isffffffffffffff48 >> 0x20);
      if ((p4 >> 0x3c & 1) != 0) goto L_00209e04;
      if (u14 != 0) {
        l70 = p3;
        uStack_68 = u11;
        pbVar12 = (byte *)((long)&l70 + (u5 >> 0x10));
        u13 = (uint)*pbVar12;
        if ((char)*pbVar12 < '\0') {
          switch((int)sk_lzcount(u13 << 0x18 ^ 0xffffffff)) {
          case 2:
            goto cd_00209a40_2;
          case 3:
            goto cd_00209a40_3;
          case 4:
            goto cd_00209a40_4;
          }
        }
        goto cd_00209a40_1;
      }
      lVar6 = la0;
      if ((p3 & 0x1000000000000000) == 0) {
        lVar6 = sk_rt_002a9ba8(p3,p4);
      }
      pbVar12 = (byte *)(lVar6 + (u5 >> 0x10));
      u13 = (uint)*pbVar12;
      if (-1 < (char)*pbVar12) goto cd_00209a40_1;
      switch((int)sk_lzcount(u13 << 0x18 ^ 0xffffffff)) {
      case 2:
cd_00209a40_2:
        u13 = pbVar12[1] & 0x3f | (u13 & 0x1f) << 6;
        break;
      case 3:
cd_00209a40_3:
        bVar2 = pbVar12[2];
        u13 = (u13 & 0xf) << 0xc | (pbVar12[1] & 0x3f) << 6;
        goto L_00209ad0;
      case 4:
cd_00209a40_4:
        bVar2 = pbVar12[3];
        u13 = (u13 & 0xf) << 0x12 | (pbVar12[1] & 0x3f) << 0xc | (pbVar12[2] & 0x3f) << 6;
L_00209ad0:
        u13 = u13 | bVar2 & 0x3f;
      }
cd_00209a40_1:
      u7 = sk_rt_00167404(u7,p3,p4);
      u7 = u7 >> 0x10;
      if (u14 == 0) {
        lVar6 = la0;
        if ((p3 & 0x1000000000000000) == 0) {
          lVar6 = sk_rt_002a9ba8(p3,p4);
        }
        bVar2 = *(byte *)(lVar6 + u7);
      }
      else {
        l70 = p3;
        uStack_68 = u11;
        bVar2 = *(byte *)((long)&l70 + u7);
      }
      u5 = sk_data_00657788;
      u10 = (uint)sk_lzcount((uint)bVar2 << 0x18 ^ 0xffffffff);
      if (-1 < (char)bVar2) {
        u10 = 1;
      }
      u1 = sk_data_00657788 + 1;
      if (sk_data_00657790 >> 1 <= sk_data_00657788) {
        sk_rt_0018de98(1 < sk_data_00657790,u1,1);
      }
      u7 = (u7 + u10) * 0x10000 | 5;
      sk_data_00657788 = u1;
      *(uint *)((long)&sk_data_00657798 + u5 * 4) = u13;
      u4 = u4 - 1;
    } while (u4 != 0);
    bVar3 = true;
  }
  uStack_98 = p3 & 0x1000000000000000;
  do {
    if ((u7 ^ p2) >> 0xe == 0) {
      return &sk_data_00657778;
    }
    u4 = sk_rt_002ab4d4(u7,p1,p2,p3,p4);
    u17 = (undefined4)((ulong)isffffffffffffff48 >> 0x20);
    if (!bVar3) {
L_00209e04:
                    /* WARNING: Subroutine does not return */
      sk_rt_001afa84(sk_str_Fatal_error_005accd0,0xb,2,0xd000000000000034,0x80000000005ce6d0,
                   sk_str_Swift_UnicodeHelpers_swift_005ce730,0x1a,2,0xfd,sk_concat44(u17,1));
    }
    if (u14 == 0) {
      lVar6 = la0;
      if (uStack_98 == 0) {
        lVar6 = sk_rt_002a9ba8(p3,p4);
      }
      pbVar12 = (byte *)(lVar6 + (u4 >> 0x10));
      u13 = (uint)*pbVar12;
      if ((char)*pbVar12 < '\0') {
        switch((int)sk_lzcount(u13 << 0x18 ^ 0xffffffff)) {
        case 2:
          goto cd_00209c90_2;
        case 3:
          goto cd_00209c90_3;
        case 4:
          goto cd_00209c90_4;
        }
      }
      goto cd_00209c90_1;
    }
    l70 = p3;
    uStack_68 = u11;
    pbVar12 = (byte *)((long)&l70 + (u4 >> 0x10));
    u13 = (uint)*pbVar12;
    if (-1 < (char)*pbVar12) goto cd_00209c90_1;
    switch((int)sk_lzcount(u13 << 0x18 ^ 0xffffffff)) {
    case 2:
cd_00209c90_2:
      u13 = pbVar12[1] & 0x3f | (u13 & 0x1f) << 6;
      break;
    case 3:
cd_00209c90_3:
      bVar2 = pbVar12[2];
      u13 = (u13 & 0xf) << 0xc | (pbVar12[1] & 0x3f) << 6;
      goto L_00209d28;
    case 4:
cd_00209c90_4:
      bVar2 = pbVar12[3];
      u13 = (u13 & 0xf) << 0x12 | (pbVar12[1] & 0x3f) << 0xc | (pbVar12[2] & 0x3f) << 6;
L_00209d28:
      u13 = u13 | bVar2 & 0x3f;
    }
cd_00209c90_1:
    u4 = sk_rt_00167404(u7,p3,p4);
    u4 = u4 >> 0x10;
    if (u14 == 0) {
      lVar6 = la0;
      if (uStack_98 == 0) {
        lVar6 = sk_rt_002a9ba8(p3,p4);
      }
      bVar2 = *(byte *)(lVar6 + u4);
    }
    else {
      l70 = p3;
      uStack_68 = u11;
      bVar2 = *(byte *)((long)&l70 + u4);
    }
    u5 = sk_data_00657788;
    u10 = (uint)sk_lzcount((uint)bVar2 << 0x18 ^ 0xffffffff);
    if (-1 < (char)bVar2) {
      u10 = 1;
    }
    u1 = sk_data_00657788 + 1;
    if (sk_data_00657790 >> 1 <= sk_data_00657788) {
      sk_rt_0018de98(1 < sk_data_00657790,u1,1);
    }
    u7 = (u4 + u10) * 0x10000 | 5;
    sk_data_00657788 = u1;
    *(uint *)((long)&sk_data_00657798 + u5 * 4) = u13;
  } while( true );
}

/* FUN_00209f18 @ 0x00209f18   (est. sk_vspace_00209f18)
 * Ghidra: void FUN_00209f18(ulong param_1,undefined4 param_2)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_00209f18(ulong p1,undefined4 p2)

{
  ulong u1;
  ulong u2;
  char *pcVar3;
  undefined8 u4;
  undefined8 u5;
  
  sk_rt_0018de98(0,p1 & ((long)p1 >> 0x3f ^ 0xffffffffffffffffU),0);
  if ((long)p1 < 0) {
    u5 = 0x2f9;
    pcVar3 = sk_str_Range_requires_lowerBound____upp_005cda00;
    u4 = 0x27;
  }
  else {
    while( true ) {
      u2 = sk_data_00657788;
      if (p1 == 0) {
        return;
      }
      if (p1 == 0) break;
      u1 = sk_data_00657788 + 1;
      if (sk_data_00657790 >> 1 <= sk_data_00657788) {
        sk_rt_0018de98(1 < sk_data_00657790,u1,1);
      }
      sk_data_00657788 = u1;
      *(undefined4 *)((long)&sk_data_00657798 + u2 * 4) = p2;
      p1 = p1 - 1;
    }
    u5 = 0x136;
    pcVar3 = sk_str_Index_out_of_range_005cd940;
    u4 = 0x12;
  }
                    /* WARNING: Subroutine does not return */
  sk_rt_001afe4c(sk_str_Fatal_error_005accd0,0xb,2,pcVar3,u4,2,sk_str_Swift_Range_swift_005cda30,0x11,2,u5
               ,1);
}

/* FUN_0020a058 @ 0x0020a058   (est. sk_vspace_0020a058)
 * Ghidra: void FUN_0020a058(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a058(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_0020a05c @ 0x0020a05c   (est. sk_vspace_0020a05c)
 * Ghidra: void FUN_0020a05c(undefined8 param_1,undefined8 param_2)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a05c(undefined8 p1,undefined8 p2)

{
  sk_vspace_0020af68(p1,p2,sk_vspace_0020a084);
  return;
}

/* FUN_0020a084 @ 0x0020a084   (est. sk_vspace_0020a084)
 * Ghidra: void FUN_0020a084(undefined8 param_1,undefined8 param_2,undefined8 *param_3,undefined8 *param_4)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a084(undefined8 p1,undefined8 p2,undefined8 *p3,undefined8 *p4)

{
    uint64_t scratch_0[2]={0};
  undefined1 ir_ZR;
  undefined8 u1;
  undefined8 u2;
  code *pcVar3;
  ulong u4;
  code *eox8;
  code *eox8_00;
  code *eox8_01;
  code *eox8_02;
  code *eox8_03;
  code *eox8_04;
  code *eox8_05;
  code *eox9;
  long rxx21;
  undefined8 rxx23;
  sk_ex16 au5;
  undefined8 is00000008;
  undefined8 is00000018;
  
  sk_swift_00353cfc();
  sk_swift_00351fb0();
  sk_swift_00353160();
  sk_swift_00377824();
  sk_swift_0034ee68();
  sk_swift_00310d68();
  u1 = sk_rt_000a6f88();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0d4();
  sk_swift_003499f0();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034af20();
  sk_swift_003508e4();
  sk_swift_0035359c();
  sk_swift_00377824();
  sk_swift_00348d64();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_003521a4();
  sk_swift_00352680(p4);
  sk_swift_00350738();
  (*eox9)();
  sk_swift_0034b278();
  sk_rt_000a6e14();
  u2 = sk_swift_00377bec();
  pcVar3 = (code *)sk_rt_000a68f4();
  sk_swift_00357e44();
  do {
    (*pcVar3)(rxx23,u2);
    sk_swift_0034b2c8();
    if ((bool)ir_ZR) {
      sk_swift_00352260();
      u2 = (*eox8_02)();
      sk_swift_00351a98(u2,u1);
      (*eox8_03)();
      sk_swift_00350488();
      au5 = (sk_ex16){ (uint64_t)sk_swift_00310d80(), 0 };
      sk_swift_003488f4(au5._0_8_,au5._8_8_,au5._0_8_);
      sk_rt_0019e578(scratch_0);
L_0020a2c0:
      u1 = sk_swift_00351348();
      sk_swift_00353d14(u1,is00000018);
      return;
    }
    sk_swift_003509b0(*p4);
    (*eox8)();
    sk_swift_00357050();
    u4 = (*eox8_00)();
    if (rxx21 != 0) {
      sk_swift_00350b00(*p3);
      (*eox8_04)();
      sk_swift_00352260();
      (*eox8_05)();
      sk_swift_0036b118(is00000008);
      goto L_0020a2c0;
    }
    if ((u4 & 1) == 0) {
      sk_swift_00350b00(*p3);
      (*eox8_01)();
    }
    else {
      sk_swift_00350488();
      sk_swift_00310d80();
      sk_swift_00355c1c();
      sk_rt_0019e538();
    }
  } while( true );
}

/* FUN_0020a2d8 @ 0x0020a2d8   (est. sk_vspace_0020a2d8)
 * Ghidra: void FUN_0020a2d8(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a2d8(void)

{
  code *eox8;
  code *eox10;
  long eox16;
  undefined8 rxx30;
  
  sk_swift_0035a7c0();
  sk_swift_0034c704();
  sk_swift_00349c70();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0d4();
  sk_swift_00352188();
  sk_swift_00350b60(*(undefined8 *)(eox16 + 200));
  sk_swift_00356278();
  (*eox10)();
  sk_swift_00352188();
  sk_swift_0034d130();
  ((void(*)(void))sk_vspace_0020a3b0)();
  sk_swift_00359628();
  sk_swift_003508f0();
  (*eox8)();
  sk_swift_00355f04();
  sk_swift_0035a7d4(rxx30);
  return;
}

/* FUN_0020a3b0 @ 0x0020a3b0   (est. sk_vspace_0020a3b0)
 * Ghidra: void FUN_0020a3b0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a3b0(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)

{
  undefined1 ir_ZR;
  code *pcVar1;
  undefined8 u2;
  undefined8 u3;
  long eox8;
  code *eox8_00;
  code *eox8_01;
  code *eox8_02;
  code *eox8_03;
  code *eox9;
  long eox16;
  long rxx19;
  code *rxx23;
  undefined8 rxx28;
  undefined8 is00000028;
  
  sk_swift_00353cfc();
  pcVar1 = (code *)sk_swift_00355e68();
  u3 = p4;
  u2 = sk_swift_0034f860();
  sk_swift_00377824(u2,u3);
  sk_swift_00348d4c();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b05c();
  sk_swift_0035050c();
  sk_swift_0034d464();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034aee4();
  sk_swift_003499f0();
  (*sk_data_00658c00)(*(undefined8 *)(eox8 + 0x40));
  sk_swift_003490ec();
  sk_swift_0034d8d4();
  sk_swift_00377824();
  sk_swift_00348fd8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034d3c4();
  sk_swift_00358aa4();
  (*eox8_00)();
  sk_swift_00352680(p4);
  sk_swift_00359bec();
  sk_swift_00350c80();
  (*eox9)();
  sk_swift_0034b278();
  sk_swift_003508b4();
  sk_swift_00377bec();
  sk_swift_00355b74();
  do {
    sk_swift_0035a3f4();
    (*rxx23)(rxx28,p3);
    sk_swift_0034c4bc();
    if ((bool)ir_ZR) break;
    sk_swift_00350738(*(undefined8 *)(eox16 + 0x20));
    (*eox8_01)();
    (*pcVar1)();
    sk_swift_00350618(*(undefined8 *)(eox16 + 8));
    (*eox8_02)();
  } while (rxx19 == 0);
  sk_swift_0034ed28();
  (*eox8_03)();
  sk_swift_00351348();
  sk_swift_00353d14(is00000028);
  return;
}

/* FUN_0020a5c0 @ 0x0020a5c0   (est. sk_vspace_0020a5c0)
 * Ghidra: undefined8 FUN_0020a5c0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
undefined8 sk_vspace_0020a5c0(void)

{
  undefined8 u1;
  code *eox8;
  code *eox8_00;
  code *eox10;
  long eox16;
  long eox16_00;
  long eox16_01;
  
  sk_swift_0034ecb8();
  sk_swift_003499f0();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_00351d9c();
  sk_swift_0034c58c(*(undefined8 *)(eox16_00 + 200));
  sk_swift_00353c24();
  (*eox10)();
  sk_swift_00351d9c();
  sk_swift_0031b62c(*(undefined8 *)(eox16_01 + 0xc0));
  sk_swift_00350a88();
  sk_rt_00077894();
  u1 = (*eox8)();
  sk_swift_00351384(*(undefined8 *)(eox16 + 8));
  (*eox8_00)();
  return u1;
}

/* FUN_0020a6ac @ 0x0020a6ac   (est. sk_vspace_0020a6ac)
 * Ghidra: void FUN_0020a6ac(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a6ac(void)

{
  code *eox8;
  code *eox9;
  long eox16;
  long eox16_00;
  long eox16_01;
  undefined8 u1;
  undefined8 u2;
  sk_ex16 au3;
  
  sk_swift_0034c998();
  u2 = *(undefined8 *)(eox16 + 0xb8);
  sk_swift_00349734();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b460();
  sk_swift_0035147c();
  au3 = (sk_ex16){ (uint64_t)sk_swift_00352dc4(*(undefined8 *)(eox16_00 + 200)), 0 };
  (*eox9)(au3._0_8_,au3._8_8_,u2);
  sk_swift_0035147c();
  u1 = *(undefined8 *)(eox16_01 + 0xc0);
  sk_swift_00310da8(u1);
  u2 = sk_swift_0034c6a4();
  (*eox8)(u2,u1);
  return;
}

/* FUN_0020a770 @ 0x0020a770   (est. sk_vspace_0020a770)
 * Ghidra: void FUN_0020a770(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a770(void)

{
  code *eox8;
  code *eox9;
  long eox16;
  long eox16_00;
  long eox16_01;
  undefined8 u1;
  undefined8 u2;
  sk_ex16 au3;
  sk_ex16 au4;
  undefined8 is00000048;
  
  au3 = (sk_ex16){ (uint64_t)sk_rt_0008e518(), 0 };
  sk_swift_00354330();
  u1 = *(undefined8 *)(eox16 + 0xb8);
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0d4();
  sk_swift_00354330();
  u2 = *(undefined8 *)(eox16_00 + 0xc0);
  sk_swift_0035454c();
  sk_swift_0034e6fc();
  sk_swift_00377824();
  sk_swift_0034a37c();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_00354330();
  au4 = (sk_ex16){ (uint64_t)sk_swift_00354264(*(undefined8 *)(eox16_01 + 200)), 0 };
  (*eox9)(au4._0_8_,au4._8_8_,u1);
  sk_swift_003191e8(u2);
  u1 = sk_swift_0035066c();
  sk_swift_00351f64(u1,au3._0_8_,au3._8_8_);
  (*eox8)();
  sk_swift_00350524();
  sk_swift_00377bec();
  sk_rt_002085fc();
  au3 = (sk_ex16){ (uint64_t)sk_swift_00354804(), 0 };
  sk_rt_0008e500(au3._0_8_,au3._8_8_,is00000048);
  return;
}

/* FUN_0020a8fc @ 0x0020a8fc   (est. sk_vspace_0020a8fc)
 * Ghidra: void FUN_0020a8fc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a8fc(void)

{
  sk_swift_00355684();
  sk_rt_002805b8();
  return;
}

/* FUN_0020a918 @ 0x0020a918   (est. sk_vspace_0020a918)
 * Ghidra: void FUN_0020a918(undefined8 param_1)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a918(undefined8 p1)

{
  sk_rt_00210bd4(p1,sk_vspace_0020b8b0);
  return;
}

/* FUN_0020a930 @ 0x0020a930   (est. sk_vspace_0020a930)
 * Ghidra: void FUN_0020a930(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020a930(void)

{
  undefined8 u1;
  undefined8 eox1;
  long eox16;
  long rxx21;
  sk_ex16 au2;
  undefined8 is00000048;
  
  sk_swift_00353cfc();
  sk_swift_003499f0();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034bdfc();
  sk_swift_0034b7b8();
  sk_swift_0031b990();
  sk_swift_0034ab20();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b05c();
  (**(code **)(eox16 + 0x10))();
  u1 = sk_swift_00353c78();
  sk_swift_003511f0(u1,eox1);
  sk_vspace_0020aa80();
  au2 = (sk_ex16){ 0, 0 };
  if (rxx21 == 0) {
    sk_swift_0035050c(au2._0_8_,au2._8_8_,0x66da48);
    sk_swift_0031b978();
    sk_swift_003515a8();
    ((void(*)(void))sk_vspace_0020a918)();
  }
  u1 = sk_swift_00351348();
  sk_swift_00353d14(u1,is00000048);
  return;
}

/* FUN_0020aa80 @ 0x0020aa80   (est. sk_vspace_0020aa80)
 * Ghidra: void FUN_0020aa80(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020aa80(void)

{
  sk_swift_00355684();
  sk_rt_00281128();
  return;
}

/* FUN_0020aabc @ 0x0020aabc   (est. sk_vspace_0020aabc)
 * Ghidra: void FUN_0020aabc(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020aabc(undefined8 p1,undefined8 p2,undefined8 p3)

{
  undefined1 ir_ZR;
  bool bVar1;
  code *pcVar2;
  undefined8 u3;
  long eox8;
  code *eox8_00;
  code *eox8_01;
  code *eox8_02;
  long eox16;
  long rxx19;
  undefined8 rxx30;
  sk_ex16 au4;
  undefined8 is00000018;
  undefined8 l28;
  long l18;
  undefined *puStack_8;
  
  sk_rt_0008e518();
  sk_swift_00352758();
  sk_swift_00351fb0();
  sk_swift_00350a64();
  sk_swift_003511f0();
  sk_swift_00377824();
  sk_swift_00348e00();
  (*sk_data_00658c00)(*(undefined8 *)(eox8 + 0x40));
  sk_swift_00348a9c();
  (*sk_data_00658c00)();
  sk_swift_0034b8bc();
  sk_swift_00350530();
  sk_swift_0034d464();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b05c();
  sk_swift_0034d8d4();
  sk_swift_00377824();
  sk_swift_00348e60();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034af20();
  if (rxx19 < 0) {
    sk_swift_00350410();
    sk_swift_003488bc();
    sk_swift_0034a3ec();
                    /* WARNING: Subroutine does not return */
    sk_rt_001afe4c();
  }
  if (rxx19 == 0) {
    u3 = sk_swift_00351eb4();
    sk_rt_0008e500(u3,rxx30);
    sk_rt_0019e578();
    return;
  }
  puStack_8 = &sk_data_00657778;
  pcVar2 = (code *)sk_rt_000a68c4(p3);
  sk_swift_0036b270(&sk_data_00657778);
  sk_swift_003518b8();
  (*pcVar2)();
  sk_swift_0034b278();
  sk_swift_00350a70();
  sk_swift_00377bec();
  pcVar2 = (code *)sk_rt_000a68f4();
  l18 = 0;
  while( true ) {
    while( true ) {
      sk_swift_0035084c();
      (*pcVar2)();
      sk_swift_0034aa54();
      if ((bool)ir_ZR) {
        sk_swift_0035313c();
        sk_swift_00350ab8();
        (*eox8_02)();
        sk_swift_00350530();
        au4 = (sk_ex16){ (uint64_t)sk_swift_00310d80(), 0 };
        sk_swift_003488f4(au4._0_8_,au4._8_8_,au4._0_8_);
        sk_rt_0019e578(&puStack_8);
        sk_swift_0036b118(&sk_data_00657778);
        u3 = sk_swift_00353100();
        sk_rt_0008e500(u3,is00000018);
        return;
      }
      sk_rt_000dbd0c(*(undefined8 *)(eox16 + 0x20));
      (*eox8_00)();
      ir_ZR = sk_data_00657788 == rxx19;
      if (rxx19 <= sk_data_00657788) break;
      sk_swift_00350530();
      sk_swift_00310d80();
      sk_swift_00357aa8();
      sk_rt_0019e538();
    }
    sk_rt_001dc430(l28,l18);
    sk_swift_00350530();
    u3 = sk_swift_00310d80();
    sk_rt_0019e538(l28,u3);
    sk_rt_001dc298(u3);
    sk_rt_0019e728(l18);
    sk_swift_00357c20(*(undefined1 *)(eox16 + 0x50));
    sk_swift_00359c70();
    sk_swift_003510a0();
    (*eox8_01)();
    bVar1 = sk_scarry8(l18,1);
    l18 = l18 + 1;
    if (bVar1) break;
    ir_ZR = l18 == rxx19;
    if (rxx19 <= l18) {
      l18 = 0;
    }
  }
                    /* WARNING: Does not return */
  pcVar2 = (code *)(uintptr_t)sk_sw_brk(1,0x20adbc);
  (*pcVar2)();
}

/* FUN_0020adfc @ 0x0020adfc   (est. sk_vspace_0020adfc)
 * Ghidra: void FUN_0020adfc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020adfc(void)

{
  undefined8 eox1;
  code *eox8;
  code *eox9;
  long eox16;
  long eox16_00;
  code *rxx19;
  undefined8 u1;
  undefined8 rxx30;
  sk_ex16 au2;
  
  sk_rt_0008e518();
  sk_swift_00355bb8();
  sk_swift_0034f274(eox1);
  u1 = *(undefined8 *)(eox16 + 0xb8);
  sk_swift_0034b7e4();
  sk_swift_00351408();
  (*sk_data_00658c00)();
  sk_swift_0034bab8();
  sk_swift_00352188();
  sk_swift_003502e8();
  (*eox8)();
  sk_rt_000841a0();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034af20();
  sk_swift_00351ecc();
  sk_swift_0031b978();
  sk_swift_00352188();
  au2 = (sk_ex16){ (uint64_t)sk_swift_00352ba4(*(undefined8 *)(eox16_00 + 200)), 0 };
  (*eox9)(au2._0_8_,au2._8_8_,u1);
  sk_swift_0034d7dc();
  (*rxx19)();
  u1 = ((uint64_t(*)(void))sk_vspace_0020a918)();
  sk_rt_0008e500(u1,rxx30);
  return;
}

/* FUN_0020af20 @ 0x0020af20   (est. sk_vspace_0020af20)
 * Ghidra: void FUN_0020af20(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020af20(void)

{
  sk_swift_00355684();
  sk_rt_00280ad8();
  return;
}

/* FUN_0020af3c @ 0x0020af3c   (est. sk_vspace_0020af3c)
 * Ghidra: void FUN_0020af3c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020af3c(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_0020af40 @ 0x0020af40   (est. sk_vspace_0020af40)
 * Ghidra: void FUN_0020af40(undefined8 param_1,undefined8 param_2)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020af40(undefined8 p1,undefined8 p2)

{
  sk_vspace_0020af68(p1,p2,sk_vspace_0020b044);
  return;
}

/* FUN_0020af68 @ 0x0020af68   (est. sk_vspace_0020af68)
 * Ghidra: void FUN_0020af68(undefined8 param_1,undefined8 param_2,code *param_3)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020af68(undefined8 p1,undefined8 p2,code *p3)

{
  code *eox9;
  long eox16;
  long eox16_00;
  undefined8 u1;
  undefined8 rxx30;
  sk_ex16 au2;
  
  sk_swift_0035a7c0();
  sk_swift_00351a68();
  sk_swift_00354330();
  u1 = *(undefined8 *)(eox16 + 0xb8);
  sk_swift_0034a5c8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0d4();
  sk_swift_00354330();
  au2 = (sk_ex16){ (uint64_t)sk_swift_00354264(*(undefined8 *)(eox16_00 + 200)), 0 };
  (*eox9)(au2._0_8_,au2._8_8_,u1);
  sk_swift_00354330();
  au2 = (sk_ex16){ (uint64_t)sk_swift_00350518(), 0 };
  u1 = (*p3)(au2._0_8_,au2._8_8_,u1);
  sk_swift_0035a7d4(u1,rxx30);
  return;
}

/* FUN_0020b044 @ 0x0020b044   (est. sk_vspace_0020b044)
 * Ghidra: void FUN_0020b044(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020b044(void)

{
    uint64_t scratch_0[2]={0};
  undefined1 ir_ZR;
  code *pcVar1;
  code *pcVar2;
  ulong u3;
  undefined8 u4;
  undefined8 ir_x3;
  code *eox8;
  code *eox8_00;
  code *eox8_01;
  code *eox8_02;
  code *eox8_03;
  code *eox9;
  long eox16;
  long rxx21;
  sk_ex16 au5;
  undefined8 is00000008;
  undefined8 is00000028;
  
  pcVar1 = (code *)sk_swift_00353cfc();
  sk_swift_00351fb0();
  sk_swift_003516cc();
  sk_swift_00377824();
  sk_swift_00348ce8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034aee4();
  sk_swift_00350488();
  sk_swift_0034d464();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b05c();
  sk_swift_00350920();
  sk_swift_00355908();
  sk_swift_00377824();
  sk_swift_00348d64();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_003521a4();
  sk_swift_00352680(ir_x3);
  sk_swift_003509b0();
  (*eox9)();
  sk_swift_0034b278();
  sk_swift_00350944();
  sk_swift_00377bec();
  pcVar2 = (code *)sk_rt_000a68f4();
  do {
    sk_swift_00351414();
    (*pcVar2)();
    sk_swift_0034b2c8();
    if ((bool)ir_ZR) {
L_0020b230:
      sk_swift_00350e24();
      (*eox8_03)();
      sk_swift_00350488();
      au5 = (sk_ex16){ (uint64_t)sk_swift_00310d80(), 0 };
      sk_swift_003488f4(au5._0_8_,au5._8_8_,au5._0_8_);
      sk_rt_0019e578(scratch_0);
L_0020b25c:
      u4 = sk_swift_00351348();
      sk_swift_00353d14(u4,is00000028);
      return;
    }
    sk_swift_0034db58(*(undefined8 *)(eox16 + 0x20));
    (*eox8)();
    u3 = (*pcVar1)();
    if (rxx21 != 0) {
      sk_swift_00352420();
      sk_swift_0035084c();
      (*eox8_00)();
      sk_swift_00350e24();
      (*eox8_01)();
      sk_swift_0036b118(is00000008);
      goto L_0020b25c;
    }
    if ((u3 & 1) == 0) {
      sk_swift_00352420();
      sk_swift_0035084c();
      (*eox8_02)();
      goto L_0020b230;
    }
    sk_swift_00350488();
    sk_swift_00310d80();
    sk_swift_00355c1c();
    sk_rt_0019e538();
  } while( true );
}

/* FUN_0020b28c @ 0x0020b28c   (est. sk_vspace_0020b28c)
 * Ghidra: void FUN_0020b28c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020b28c(void)

{
  undefined8 u1;
  code *eox9;
  long eox16;
  long eox16_00;
  code *rxx19;
  long rxx20;
  sk_ex16 au2;
  
  sk_rt_0008409c();
  sk_swift_003542f4();
  sk_swift_0034998c();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  u1 = sk_swift_003542f4();
  sk_swift_00356a14(u1,rxx20 + *(long *)(eox16 + 200));
  (*eox9)();
  au2 = (sk_ex16){ (uint64_t)sk_swift_003542f4(), 0 };
  sk_rt_0008e388(au2._0_8_,au2._8_8_,*(undefined8 *)(eox16_00 + 0xc0));
  (*rxx19)();
  return;
}

/* FUN_0020b358 @ 0x0020b358   (est. sk_vspace_0020b358)
 * Ghidra: void FUN_0020b358(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020b358(undefined8 p1,undefined8 p2,undefined8 p3)

{
  undefined *puVar1;
  bool bVar2;
  undefined1 u3;
  undefined8 u4;
  code *pcVar5;
  long lVar6;
  undefined8 u7;
  undefined8 eox1;
  undefined8 eox1_00;
  undefined8 eox1_01;
  undefined8 u8;
  long eox8;
  code *eox8_00;
  code *eox8_01;
  code *eox8_02;
  code *eox8_03;
  code *eox8_04;
  code *eox9;
  code *eox9_00;
  long eox16;
  long eox16_00;
  undefined8 rxx19;
  undefined8 rxx20;
  long rxx21;
  undefined8 rxx26;
  sk_ex16 au9;
  sk_ex16 l30;
  undefined8 l20;
  undefined1 l10 [8];
  undefined *l8;
  
  sk_rt_0008e518();
  sk_rt_0008409c();
  sk_swift_00351fb0();
  sk_swift_00350a64();
  sk_swift_00351238();
  sk_swift_00377824();
  sk_swift_00348ce8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0d4();
  sk_swift_00350488();
  sk_swift_0034d464();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034af20();
  sk_swift_003494e8();
  (*sk_data_00658c00)(*(undefined8 *)(eox8 + 0x40));
  sk_swift_00349068();
  sk_swift_0034e0a4();
  u4 = sk_swift_00377824();
  sk_rt_000a6f88();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b2f8();
  if (rxx21 < 0) {
    sk_swift_00350410();
    sk_swift_003488bc();
    sk_swift_0034c56c();
    sk_swift_003523f0();
L_0020b7dc:
                    /* WARNING: Subroutine does not return */
    sk_rt_001afe4c();
  }
  if (rxx21 == 0) {
    sk_rt_0007c1c4(*(undefined8 *)(eox16_00 + 8));
    (*eox8_03)();
    sk_swift_00350488();
    sk_rt_001a0414();
  }
  else {
    l8 = &sk_data_00657778;
    pcVar5 = (code *)sk_rt_000a6894(p3);
    sk_swift_0036b270(&sk_data_00657778);
    sk_swift_003509e0();
    lVar6 = (*pcVar5)();
    u3 = lVar6 == rxx21;
    if (rxx21 <= lVar6) {
      lVar6 = rxx21;
    }
    sk_swift_00350488();
    sk_swift_00310d80();
    sk_swift_00357a9c();
    sk_rt_0019e410(lVar6);
    sk_swift_00351118(rxx26);
    (*eox9)();
    sk_rt_000a68c4(p3);
    sk_swift_0035133c();
    sk_swift_003514e8();
    (*eox9_00)();
    sk_swift_0034b278();
    u8 = u4;
    sk_swift_00377bec(p3);
    pcVar5 = (code *)sk_rt_000a68f4();
    lVar6 = 0;
    while( true ) {
      sk_swift_00356230();
      sk_swift_00354594();
      (*pcVar5)();
      sk_swift_0034b2c8();
      if ((bool)u3) break;
      sk_swift_0034e5cc(*(undefined8 *)(eox16 + 0x20));
      (*eox8_00)();
      u3 = *(long *)(l8 + 0x10) == rxx21;
      if (*(long *)(l8 + 0x10) < rxx21) {
        sk_swift_003508a8();
        sk_rt_0019e538();
      }
      else {
        sk_rt_001dc298(eox1);
        sk_swift_00358f54();
        sk_rt_0019e728();
        sk_swift_00357c20(*(undefined1 *)(eox16 + 0x50));
        sk_swift_00359c70();
        sk_rt_000dbf08();
        (*eox8_01)();
        bVar2 = sk_scarry8(lVar6,1);
        lVar6 = lVar6 + 1;
        if (bVar2) {
                    /* WARNING: Does not return */
          pcVar5 = (code *)(uintptr_t)sk_sw_brk(1,0x20b7e8);
          (*pcVar5)();
        }
        u3 = lVar6 == rxx21;
        if (rxx21 <= lVar6) {
          lVar6 = 0;
        }
      }
    }
    u7 = sk_swift_00351dd8();
    (*eox8_02)(u7,u4);
    puVar1 = l8;
    if (lVar6 != 0) {
      sk_rt_000a6f68();
      sk_rt_0019e410(*(undefined8 *)(puVar1 + 0x10),eox1);
      if (lVar6 <= *(long *)(puVar1 + 0x10)) {
        sk_swift_00354370(lVar6);
        l30 = (sk_ex16){ (uint64_t)sk_rt_001dc554(), 0 };
        u4 = l30._0_8_;
        l20 = u8;
        sk_swift_00350488();
        sk_swift_00310df0();
        u7 = sk_swift_0034b5fc();
        sk_swift_00376820(u7,eox1);
        sk_swift_0035063c(l10,l30);
        sk_rt_00275780();
        sk_swift_0036b118(u4);
        if (-1 < lVar6) {
          (**(code **)(eox16_00 + 8))(rxx20,rxx19);
          sk_swift_00350920();
          sk_swift_00354370();
          au9 = (sk_ex16){ (uint64_t)sk_rt_001dc554(), 0 };
          l20 = u8;
          l30 = au9;
          sk_swift_0035063c(l10,l30);
          sk_rt_00275780();
          sk_swift_0036b118(au9._0_8_);
          sk_swift_003488f4();
          sk_rt_0019e578(l10,eox1_00,eox1);
          sk_swift_0036b118(puVar1);
          goto L_0020b794;
        }
      }
      sk_swift_00347d60();
      goto L_0020b7dc;
    }
    sk_rt_0006f6b4();
    sk_swift_0036b118();
    sk_swift_00354324();
    (*eox8_04)(rxx20,rxx19);
    l30._0_8_ = (uint64_t)puVar1;
    sk_swift_003488f4();
    sk_rt_0019e578(l30,eox1_01,eox1);
  }
L_0020b794:
  u4 = sk_swift_00353100();
  sk_rt_0008e500(u4,l30._8_8_);
  return;
}

/* FUN_0020b7e8 @ 0x0020b7e8   (est. sk_vspace_0020b7e8)
 * Ghidra: void FUN_0020b7e8(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020b7e8(void)

{
  long eox8;
  long eox16;
  long rxx20;
  
  sk_rt_0007c0c4();
                    /* WARNING: Could not recover jumptable at 0x0020b83c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)(*(long *)(eox8 + 0xb8) + -8) + 8))
            (rxx20 + *(long *)(eox16 + 200));
  return;
}

/* FUN_0020b844 @ 0x0020b844   (est. sk_vspace_0020b844)
 * Ghidra: void FUN_0020b844(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020b844(void)

{
  undefined8 u1;
  long eox8;
  long eox9;
  long eox16;
  long rxx20;
  
  u1 = sk_rt_0007c0c4();
  sk_swift_0034ece8(u1,*(undefined8 *)(eox8 + 0xb8));
  (**(code **)(eox16 + 8))(rxx20 + eox9);
  return;
}

/* FUN_0020b8b0 @ 0x0020b8b0   (est. sk_vspace_0020b8b0)
 * Ghidra: void FUN_0020b8b0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020b8b0(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_0020b8b4 @ 0x0020b8b4   (est. sk_vspace_0020b8b4)
 * Ghidra: void FUN_0020b8b4(undefined8 param_1)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020b8b4(undefined8 p1)

{
  long eox8;
  long eox9;
  long eox16;
  long rxx20;
  sk_ex16 au1;
  
  au1 = (sk_ex16){ (uint64_t)sk_rt_0007c0c4(p1,p1), 0 };
  sk_swift_0034b07c(au1._0_8_,au1._8_8_,*(undefined8 *)(eox8 + 0xb8));
  (**(code **)(eox16 + 0x20))(rxx20 + eox9);
  return;
}

/* FUN_0020b9f4 @ 0x0020b9f4   (est. sk_vspace_0020b9f4)
 * Ghidra: void FUN_0020b9f4(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020b9f4(void)

{
  undefined8 u1;
  undefined8 u2;
  code *eox9;
  code *eox9_00;
  long eox16;
  long eox16_00;
  long rxx20;
  
  u1 = sk_rt_00084220();
  sk_rt_0007c0c4();
  sk_swift_003499b4();
  sk_swift_00351408();
  (*sk_data_00658c00)();
  sk_swift_0034b014();
  sk_swift_0035125c(*(undefined8 *)(eox16 + 0x148));
  sk_swift_0035525c();
  sk_swift_0034ba38();
  sk_swift_00377824();
  sk_swift_0034ab20();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034aee4();
  u2 = sk_rt_000027e8();
  sk_swift_00353474(u2,rxx20 + *(long *)(eox16_00 + 0x150));
  (*eox9)();
  sk_swift_003506b0();
  sk_swift_003504ac();
  (*eox9_00)();
  sk_swift_00350c8c();
  sk_swift_00377bec();
  sk_swift_00355b04();
  u2 = sk_rt_002085fc();
  sk_rt_00084234(u2,u1);
  return;
}

/* FUN_0020bb18 @ 0x0020bb18   (est. sk_vspace_0020bb18)
 * Ghidra: void FUN_0020bb18(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020bb18(void)

{
  code *eox8;
  code *eox8_00;
  code *eox10;
  long eox16;
  long eox16_00;
  
  sk_swift_0034ecb8();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b2f8();
  sk_swift_00351d9c();
  sk_swift_0034ad8c(*(undefined8 *)(eox16 + 0x150));
  (*eox10)();
  sk_swift_00351d9c();
  sk_swift_00350950(*(undefined8 *)(eox16_00 + 0x148));
  sk_rt_000a6894();
  sk_swift_0034ac64();
  (*eox8)();
  sk_swift_0034da48();
  (*eox8_00)();
  sk_swift_00356310();
  return;
}

/* FUN_0020bbf0 @ 0x0020bbf0   (est. sk_vspace_0020bbf0)
 * Ghidra: void FUN_0020bbf0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020bbf0(void)

{
  undefined8 u1;
  code *eox8;
  code *eox10;
  long eox16;
  long eox16_00;
  undefined8 is00000018;
  uint8_t auStack_40[32];
  undefined8 l20;
  
  sk_swift_00353cfc();
  sk_swift_0034d634();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_00352ff4();
  sk_swift_0034c1bc(*(undefined8 *)(eox16 + 0x150));
  (*eox10)();
  sk_swift_0035a1f4();
  l20 = *(undefined8 *)(eox16_00 + 0x148);
  sk_swift_0034a210();
  sk_rt_00002534();
  sk_swift_00351560(sk_swift_00346ff4,auStack_40);
  sk_swift_00358eb8();
  sk_rt_000262fc();
  sk_swift_00354dd0();
  sk_swift_0034f9c8();
  (*eox8)();
  u1 = sk_swift_00352df4();
  sk_swift_00353d14(u1,is00000018);
  return;
}

/* FUN_0020bd1c @ 0x0020bd1c   (est. sk_vspace_0020bd1c)
 * Ghidra: void FUN_0020bd1c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020bd1c(void)

{
  code *eox9;
  long eox16;
  long eox16_00;
  long eox16_01;
  undefined8 u1;
  undefined8 rxx30;
  sk_ex16 au2;
  
  sk_swift_00358fb4();
  sk_swift_0034c704();
  u1 = *(undefined8 *)(eox16 + 0x140);
  sk_swift_00349c70();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034aee4();
  sk_swift_00352188();
  au2 = (sk_ex16){ (uint64_t)sk_swift_00352ba4(*(undefined8 *)(eox16_00 + 0x150)), 0 };
  (*eox9)(au2._0_8_,au2._8_8_,u1);
  sk_swift_00352188();
  sk_rt_00027754(*(undefined8 *)(eox16_01 + 0x148));
  sk_swift_0034d130();
  sk_swift_00358cec();
  u1 = ((uint64_t(*)(void))sk_vspace_0020a084)();
  sk_swift_00358fc8(u1,rxx30);
  return;
}

/* FUN_0020bde4 @ 0x0020bde4   (est. sk_vspace_0020bde4)
 * Ghidra: void FUN_0020bde4(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020bde4(void)

{
  code *eox8;
  code *eox10;
  long eox16;
  long eox16_00;
  undefined8 rxx30;
  
  sk_swift_0035a7c0();
  sk_swift_0034c704();
  sk_swift_00349c70();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0d4();
  sk_swift_00352188();
  sk_swift_00350b60(*(undefined8 *)(eox16 + 0x150));
  sk_swift_00356278();
  (*eox10)();
  sk_swift_00352188();
  sk_rt_00027754(*(undefined8 *)(eox16_00 + 0x148));
  sk_swift_0034d130();
  ((void(*)(void))sk_vspace_0020a3b0)();
  sk_swift_00359628();
  sk_swift_003508f0();
  (*eox8)();
  sk_swift_00355f04();
  sk_swift_0035a7d4(rxx30);
  return;
}

/* FUN_0020bec4 @ 0x0020bec4   (est. sk_vspace_0020bec4)
 * Ghidra: undefined8 FUN_0020bec4(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
undefined8 sk_vspace_0020bec4(void)

{
  undefined8 u1;
  code *eox8;
  code *eox8_00;
  code *eox10;
  long eox16;
  long eox16_00;
  
  sk_swift_003542f4();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_003542f4();
  sk_swift_0034c1bc(*(undefined8 *)(eox16 + 0x150));
  (*eox10)();
  sk_swift_003542f4();
  sk_swift_0035125c(*(undefined8 *)(eox16_00 + 0x148));
  sk_swift_0031b62c();
  sk_swift_00350804();
  sk_swift_00351190();
  u1 = (*eox8)();
  sk_swift_0034f9c8();
  (*eox8_00)();
  return u1;
}

/* FUN_0020bfb0 @ 0x0020bfb0   (est. sk_vspace_0020bfb0)
 * Ghidra: void FUN_0020bfb0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020bfb0(void)

{
  code *eox8;
  code *eox9;
  long eox16;
  long eox16_00;
  long eox16_01;
  undefined8 u1;
  sk_ex16 au2;
  
  sk_swift_0034c998();
  u1 = *(undefined8 *)(eox16 + 0x140);
  sk_swift_00349734();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b460();
  sk_swift_0035147c();
  au2 = (sk_ex16){ (uint64_t)sk_swift_00352dc4(*(undefined8 *)(eox16_00 + 0x150)), 0 };
  (*eox9)(au2._0_8_,au2._8_8_,u1);
  sk_swift_0035147c();
  sk_swift_00350780(*(undefined8 *)(eox16_01 + 0x148));
  sk_swift_00310da8();
  sk_swift_0034c6a4();
  (*eox8)();
  return;
}

/* FUN_0020c074 @ 0x0020c074   (est. sk_vspace_0020c074)
 * Ghidra: void FUN_0020c074(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c074(void)

{
  undefined8 u1;
  code *eox8;
  code *eox9;
  long eox16;
  long eox16_00;
  long rxx20;
  undefined8 rxx30;
  sk_ex16 au2;
  
  sk_rt_0008e518();
  sk_swift_0035316c();
  sk_rt_0007c0c4();
  sk_swift_003499b4();
  sk_swift_00351408();
  (*sk_data_00658c00)();
  sk_swift_0034beb4();
  sk_swift_003549d8();
  sk_swift_00352894(*(undefined8 *)(eox16 + 0x148));
  sk_swift_00350ca4();
  sk_swift_0034c454();
  sk_swift_00377824();
  sk_swift_00349e10();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034af20();
  u1 = sk_rt_000027e8();
  sk_swift_00353c6c(u1,rxx20 + *(long *)(eox16_00 + 0x150));
  (*eox9)();
  sk_swift_003191e8();
  sk_swift_0034cd2c();
  (*eox8)();
  sk_swift_0034f344();
  sk_swift_00377bec();
  sk_swift_00359388();
  au2 = (sk_ex16){ (uint64_t)sk_swift_00354804(), 0 };
  sk_rt_0008e500(au2._0_8_,au2._8_8_,rxx30);
  return;
}

/* FUN_0020c1a0 @ 0x0020c1a0   (est. sk_vspace_0020c1a0)
 * Ghidra: void FUN_0020c1a0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c1a0(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_0020c1a4 @ 0x0020c1a4   (est. sk_vspace_0020c1a4)
 * Ghidra: void FUN_0020c1a4(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c1a4(void)

{
  sk_swift_0034e3e4();
  ((void(*)(void))sk_vspace_0020c368)();
  return;
}

/* FUN_0020c1bc @ 0x0020c1bc   (est. sk_vspace_0020c1bc)
 * Ghidra: void FUN_0020c1bc(undefined8 param_1)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c1bc(undefined8 p1)

{
  sk_rt_00210bd4(p1,sk_vspace_0020c6c8);
  return;
}

/* FUN_0020c204 @ 0x0020c204   (est. sk_vspace_0020c204)
 * Ghidra: void FUN_0020c204(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c204(void)

{
  undefined8 u1;
  code *eox1;
  code *eox9;
  long eox16;
  long eox16_00;
  long rxx20;
  undefined8 u2;
  undefined8 rxx30;
  sk_ex16 au3;
  
  sk_rt_0008e518();
  sk_swift_0034f274();
  sk_swift_00349734();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b05c();
  sk_swift_00352188();
  u2 = *(undefined8 *)(eox16 + 0x148);
  sk_swift_003508e4();
  sk_swift_00351900();
  sk_swift_00377824();
  sk_swift_0034a37c();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034bdfc();
  sk_swift_003507d4();
  sk_swift_00351dcc();
  sk_swift_00377bec();
  sk_swift_00350c98();
  sk_swift_003193f4();
  u1 = sk_swift_00352188();
  sk_swift_00357a0c(u1,rxx20 + *(long *)(eox16_00 + 0x150));
  (*eox9)();
  au3 = (sk_ex16){ (uint64_t)sk_rt_00100efc(), 0 };
  (*eox1)(au3._0_8_,au3._8_8_,u2);
  u1 = ((uint64_t(*)(void))sk_vspace_0020c1bc)();
  sk_rt_0008e500(u1,rxx30);
  return;
}

/* FUN_0020c34c @ 0x0020c34c   (est. sk_vspace_0020c34c)
 * Ghidra: void FUN_0020c34c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c34c(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_0020c350 @ 0x0020c350   (est. sk_vspace_0020c350)
 * Ghidra: void FUN_0020c350(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c350(void)

{
  sk_swift_0034e3cc();
  ((void(*)(void))sk_vspace_0020c368)();
  return;
}

/* FUN_0020c368 @ 0x0020c368   (est. sk_vspace_0020c368)
 * Ghidra: void FUN_0020c368(undefined8 param_1,undefined8 param_2,code *param_3)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c368(undefined8 p1,undefined8 p2,code *p3)

{
  undefined8 u1;
  undefined8 eox1;
  long eox16;
  long rxx21;
  undefined8 is00000048;
  
  sk_swift_00353cfc();
  sk_swift_0034f274();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034af20();
  sk_swift_00352188();
  sk_swift_0034c20c();
  sk_swift_003508c0();
  sk_swift_00377824();
  sk_swift_00349e10();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b460();
  sk_swift_00352188();
  (**(code **)(eox16 + 0x10))();
  u1 = sk_swift_003539d8();
  sk_swift_00351560(u1,eox1);
  (*p3)();
  if (rxx21 == 0) {
    sk_swift_0034de8c();
    sk_swift_0034ff98();
    sk_swift_00377bec();
    sk_swift_0034c55c();
    sk_swift_003193f4();
    sk_swift_00351a44();
    ((void(*)(void))sk_vspace_0020c1bc)();
  }
  u1 = sk_swift_00358490();
  sk_swift_00353d14(u1,is00000048);
  return;
}

/* FUN_0020c4d4 @ 0x0020c4d4   (est. sk_vspace_0020c4d4)
 * Ghidra: void FUN_0020c4d4(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c4d4(void)

{
  long eox8;
  long eox16;
  long rxx20;
  
  sk_rt_0007c0c4();
                    /* WARNING: Could not recover jumptable at 0x0020c528. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(long *)(*(long *)(eox8 + 0x140) + -8) + 8))
            (rxx20 + *(long *)(eox16 + 0x150));
  return;
}

/* FUN_0020c5b0 @ 0x0020c5b0   (est. sk_vspace_0020c5b0)
 * Ghidra: void FUN_0020c5b0(undefined8 param_1,undefined8 param_2)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c5b0(undefined8 p1,undefined8 p2)

{
  undefined8 u1;
  long lVar2;
  long lVar3;
  long rxx20;
  
  *(undefined8 *)(rxx20 + 0x30) = p1;
  *(undefined8 *)(rxx20 + 0x38) = p2;
  u1 = sk_rt_00002534(&sk_data_00657630,&sk_data_004f2110);
  lVar2 = sk_swift_0036a940(u1,0x18,7);
  *(undefined8 *)(lVar2 + 0x10) = 0;
  lVar3 = sk_swift_0036a940(u1,0x18,7);
  *(undefined8 *)(lVar3 + 0x10) = 0;
  *(long *)(rxx20 + 0x10) = lVar2;
  *(undefined8 *)(rxx20 + 0x18) = 0x66c280;
  *(long *)(rxx20 + 0x20) = lVar3;
  *(undefined8 *)(rxx20 + 0x28) = 0x66c280;
  return;
}

/* FUN_0020c634 @ 0x0020c634   (est. sk_vspace_0020c634)
 * Ghidra: void FUN_0020c634(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c634(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)

{
  undefined8 u1;
  long lVar2;
  undefined8 u3;
  long lVar4;
  long rxx20;
  sk_ex16 au5;
  
  sk_rt_00084220();
  au5 = (sk_ex16){ (uint64_t)sk_swift_00349a18(), 0 };
  *(sk_ex16 *)(rxx20 + 0x30) = au5;
  *(undefined8 *)(rxx20 + 0x40) = p3;
  *(undefined8 *)(rxx20 + 0x48) = p4;
  u1 = sk_rt_00002534(&sk_data_00657668,&sk_data_004f2148);
  lVar2 = sk_rt_000dbe0c();
  *(undefined8 *)(lVar2 + 0x10) = 0xf;
  sk_rt_000aa47c();
  u3 = sk_rt_002527e8();
  lVar4 = sk_rt_000dbe0c(u1);
  *(undefined8 *)(lVar4 + 0x10) = u3;
  *(long *)(rxx20 + 0x10) = lVar2;
  *(undefined8 *)(rxx20 + 0x18) = 0x66c280;
  *(long *)(rxx20 + 0x20) = lVar4;
  *(undefined8 *)(rxx20 + 0x28) = 0x66c280;
  sk_rt_00084234();
  return;
}

/* FUN_0020c6c8 @ 0x0020c6c8   (est. sk_vspace_0020c6c8)
 * Ghidra: void FUN_0020c6c8(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c6c8(void)

{
  undefined8 u1;
  undefined8 eox1;
  long eox8;
  code *eox8_00;
  code *eox9;
  code *eox9_00;
  code *eox10;
  long eox16;
  long eox16_00;
  undefined8 eox16_01;
  long rxx19;
  undefined8 rxx27;
  
  sk_rt_0008e518();
  sk_swift_00353860();
  sk_swift_0034c354();
  sk_rt_000bd3a4();
  sk_swift_00377824();
  sk_swift_00349e10();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_00356194();
  sk_swift_003537c4(*(undefined8 *)(eox16 + 0x150));
  sk_swift_003511d8(rxx19 + eox8);
  (*eox10)();
  sk_swift_003504c4();
  sk_swift_00351f40();
  sk_swift_00377bec();
  sk_swift_0034c55c();
  sk_swift_0031b9c0();
  sk_swift_00357b48();
  sk_rt_000277b8();
  sk_swift_0034c930();
  (*eox9)();
  sk_swift_00356218();
  sk_vspace_0020c7fc();
  sk_swift_0035a42c();
  sk_swift_00310924();
  sk_swift_0034c930();
  (*eox9_00)();
  sk_rt_000b4390(*(undefined8 *)(eox16_00 + 8));
  (*eox8_00)();
  sk_swift_00356218();
  u1 = sk_swift_00348b1c();
  *(undefined8 *)(rxx19 + 0x10) = rxx27;
  *(undefined8 *)(rxx19 + 0x18) = eox16_01;
  *(undefined8 *)(rxx19 + 0x20) = u1;
  *(undefined8 *)(rxx19 + 0x28) = eox16_01;
  u1 = sk_swift_00353100();
  sk_rt_0008e500(u1,eox1);
  return;
}

/* FUN_0020c7fc @ 0x0020c7fc   (est. sk_vspace_0020c7fc)
 * Ghidra: void FUN_0020c7fc(undefined8 param_1)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c7fc(undefined8 p1)

{
  sk_rt_00210bd4(p1,sk_rt_00213460);
  return;
}

/* FUN_0020c814 @ 0x0020c814   (est. sk_vspace_0020c814)
 * Ghidra: void FUN_0020c814(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020c814(void)

{
  undefined1 ir_ZR;
  undefined8 u1;
  code *pcVar2;
  undefined8 u3;
  undefined8 eox1;
  undefined8 eox8;
  code *eox8_00;
  long eox16;
  undefined8 rxx30;
  
  sk_rt_0008e518();
  sk_swift_00358114();
  sk_rt_0007c0c4();
  sk_swift_0034d598();
  sk_swift_0034c444(0xff);
  sk_swift_00377824();
  sk_swift_0034e57c();
  sk_swift_00310d68();
  u1 = sk_rt_000a6f88();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034bdfc();
  pcVar2 = (code *)sk_swift_0031b9d8(eox1);
  sk_swift_0034f5b4();
  sk_swift_00377bec();
  sk_swift_00353a6c();
  (*pcVar2)();
  u3 = sk_swift_0034e1b0();
  if (!(bool)ir_ZR) {
    sk_swift_0034dfe4();
    (**(code **)(eox16 + 0x20))(eox8);
    sk_rt_0008e500(rxx30);
    return;
  }
  sk_swift_00352e18(u3,u1);
  (*eox8_00)();
  sk_swift_0034abc4();
  sk_swift_003593c0();
  sk_swift_00349c58();
                    /* WARNING: Subroutine does not return */
  sk_rt_001afa84();
}

/* FUN_0020cb24 @ 0x0020cb24   (est. sk_vspace_0020cb24)
 * Ghidra: void FUN_0020cb24(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020cb24(undefined8 p1,undefined8 p2,undefined8 p3,undefined8 p4)

{
  int iVar1;
  undefined8 u2;
  long lVar3;
  undefined8 u4;
  ulong u5;
  long eox8;
  long eox8_00;
  long eox8_01;
  long eox8_02;
  code *eox8_03;
  code *eox8_04;
  code *eox8_05;
  code *eox8_06;
  code *eox9;
  code *eox9_00;
  code *eox10;
  long eox16;
  long eox16_00;
  long eox16_01;
  code *pcVar6;
  long rxx26;
  undefined8 rxx30;
  sk_ex16 au7;
  sk_ex16 au8;
  undefined8 l30;
  
  au7 = (sk_ex16){ (uint64_t)sk_rt_0008e518(), 0 };
  sk_swift_0034f274();
  sk_swift_0034bec4();
  u2 = sk_swift_00377824();
  sk_swift_0034ab20();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034aab0();
  sk_swift_003504a0(0xff);
  sk_swift_00377824();
  lVar3 = sk_swift_0034a654();
  sk_rt_000a6f88();
  (*sk_data_00658c00)(*(undefined8 *)(eox8 + 0x40));
  sk_swift_00348a18();
  (*sk_data_00658c00)();
  sk_swift_00350464();
  sk_swift_00349618();
  (*sk_data_00658c00)(*(undefined8 *)(eox8_01 + 0x40));
  sk_swift_00348abc();
  (*sk_data_00658c00)();
  sk_swift_0034c2d8();
  sk_swift_0034ca28();
  u4 = sk_swift_00377bec();
  au8 = (sk_ex16){ (uint64_t)sk_swift_00350500(), 0 };
  sk_swift_00310e08(au8._0_8_,au8._8_8_,u4);
  sk_swift_00348cd0();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_00350428();
  sk_swift_0034911c();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_00355c84();
  sk_swift_00352188();
  sk_swift_003558d8(*(undefined8 *)(eox16_01 + 0x150));
  (*eox10)();
  sk_swift_00351c1c(au7._0_8_,au7._8_8_,sk_str_Swift_ExistentialCollection_swif_005cf680);
  sk_vspace_0020c814();
  sk_swift_00351c1c(p3,p4,sk_str_Swift_ExistentialCollection_swif_005cf680);
  sk_vspace_0020c814();
  sk_swift_00310e20(u4);
  sk_swift_0034d394();
  sk_swift_00354388();
  u5 = (*eox8_03)();
  if ((u5 & 1) != 0) {
    sk_swift_0034de8c();
    au7 = (sk_ex16){ (uint64_t)sk_swift_00355b10(), 0 };
    au7 = (sk_ex16){ (uint64_t)sk_swift_00377bec(au7._0_8_,au7._8_8_,u2), 0 };
    sk_swift_00350798(au7._0_8_,au7._8_8_,au7._0_8_);
    sk_swift_003193f4();
    sk_swift_00358ce0();
    sk_swift_00350b00();
    (*(code *)sk_str_Swift_ExistentialCollection_swif_005cf680)();
    sk_swift_00350c08(eox8_00 + *(int *)(lVar3 + 0x30));
    (*(code *)sk_str_Swift_ExistentialCollection_swif_005cf680)();
    sk_swift_0035399c();
    sk_swift_0034f4a4();
    (*eox9)();
    iVar1 = *(int *)(lVar3 + 0x30);
    sk_rt_000dbf08(eox8_02);
    (*(code *)sk_str_Swift_ExistentialCollection_swif_005cf680)();
    pcVar6 = *(code **)(eox16_00 + 8);
    (*pcVar6)(rxx26 + iVar1);
    sk_swift_0034f4a4(*(undefined8 *)(eox16 + 0x20));
    (*eox8_04)();
    (*(code *)sk_str_Swift_ExistentialCollection_swif_005cf680)
              (eox8_02 + sk_data_0060e22c,rxx26 + *(int *)(lVar3 + 0x30));
    sk_swift_003508b4();
    (*pcVar6)();
    sk_swift_00355604();
    sk_swift_00352eb4();
    sk_swift_00354cfc();
    sk_swift_0035056c();
    (*eox9_00)();
    sk_swift_0035336c();
    sk_swift_00350470();
    (*eox8_05)();
    sk_swift_00353be8();
    sk_swift_00350af4();
    (*eox8_06)();
    u2 = ((uint64_t(*)(undefined8))sk_vspace_0020c1bc)(l30);
    sk_rt_0008e500(u2,rxx30);
    return;
  }
  sk_swift_0034b348();
  sk_swift_0035a4d4();
  sk_swift_00347ef4();
                    /* WARNING: Subroutine does not return */
  sk_rt_001afe4c();
}

/* FUN_0020d0c4 @ 0x0020d0c4   (est. sk_vspace_0020d0c4)
 * Ghidra: void FUN_0020d0c4(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020d0c4(void)

{
  long lVar1;
  undefined8 eox1;
  code *eox8;
  code *eox8_00;
  long eox8_01;
  code *eox8_02;
  code *eox8_03;
  code *eox9;
  code *eox10;
  code *eox10_00;
  long eox16;
  long eox16_00;
  long eox16_01;
  long eox16_02;
  long eox16_03;
  long eox16_04;
  long eox16_05;
  long lVar2;
  undefined8 u3;
  undefined8 u4;
  sk_ex16 au5;
  undefined8 is00000048;
  
  sk_rt_0008e518();
  sk_swift_0034cca8();
  sk_swift_003499b4();
  sk_swift_00351408();
  (*sk_data_00658c00)();
  sk_swift_00349c14();
  u3 = *(undefined8 *)(eox16_00 + 0x148);
  sk_swift_0034cd7c();
  sk_swift_003508d8();
  sk_swift_00377824();
  sk_swift_00357944();
  sk_swift_0034f344();
  sk_swift_00377bec();
  sk_swift_0034c55c();
  sk_swift_0031b9c0();
  lVar1 = sk_swift_00362acc();
  if (lVar1 != 0) {
    sk_swift_0034a868(*(undefined8 *)(eox16 + 0x150));
    (*eox10)();
    sk_swift_0035a140();
    lVar2 = *(long *)(eox16_01 + 0x48);
    u3 = sk_rt_00027818(u3);
    sk_swift_00350c20(u3,lVar1 + lVar2);
    (*eox8)();
    sk_swift_0034eb84();
    (*eox8_00)();
    sk_rt_0008e500(eox1);
    return;
  }
  sk_swift_003498f4();
  sk_swift_00349190();
  au5 = (sk_ex16){ (uint64_t)sk_rt_0008e518(), 0 };
  sk_swift_003542f4();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b2f8();
  sk_swift_003542f4();
  u4 = *(undefined8 *)(eox16_03 + 0x148);
  sk_swift_0034d070();
  sk_swift_0034d014();
  sk_swift_00377824();
  sk_swift_00348cd0();
  (*sk_data_00658c00)(*(undefined8 *)(eox8_01 + 0x40));
  sk_swift_00348abc();
  (*sk_data_00658c00)();
  sk_swift_0034b8bc();
  sk_swift_0034ee18();
  sk_swift_00377bec();
  sk_swift_0034c55c();
  sk_swift_0031b9c0();
  sk_swift_003542f4();
  sk_swift_0034ad8c(*(undefined8 *)(eox16_05 + 0x150));
  (*eox10_00)();
  sk_swift_00353bdc();
  sk_swift_00351c1c(au5._0_8_,au5._8_8_);
  sk_vspace_0020c814();
  sk_swift_0031afcc(u4);
  sk_swift_00350c50();
  sk_swift_00353f38();
  sk_swift_00351444();
  (*eox9)();
  sk_swift_00350b6c(*(undefined8 *)(eox16_04 + 8));
  (*eox8_02)();
  sk_swift_00350524(*(undefined8 *)(eox16_02 + 8));
  (*eox8_03)();
  sk_swift_00348b1c(u3);
  au5 = (sk_ex16){ (uint64_t)sk_swift_00356090(), 0 };
  sk_rt_0008e500(au5._0_8_,au5._8_8_,is00000048);
  return;
}

/* FUN_0020d3b0 @ 0x0020d3b0   (est. sk_vspace_0020d3b0)
 * Ghidra: void FUN_0020d3b0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020d3b0(void)

{
  undefined8 u1;
  undefined8 ir_x3;
  undefined8 ir_x4;
  long eox8;
  long eox8_00;
  code *eox8_01;
  code *eox8_02;
  code *eox9;
  code *eox10;
  long eox16;
  long eox16_00;
  long eox16_01;
  long eox16_02;
  undefined8 *rxx20;
  code *pcVar2;
  undefined8 rxx30;
  undefined8 u3;
  sk_ex16 au4;
  sk_ex16 au5;
  undefined8 l10;
  undefined8 uStack_8;
  
  au4 = (sk_ex16){ (uint64_t)sk_rt_0008e518(), 0 };
  sk_swift_00352ff4(*rxx20);
  u1 = *(undefined8 *)(eox16 + 0x148);
  u3 = *(undefined8 *)(eox8 + 0x140);
  au5 = (sk_ex16){ (uint64_t)sk_swift_00349748(), 0 };
  sk_swift_00377824(au5._0_8_,au5._8_8_,u3);
  sk_swift_00348d64();
  (*sk_data_00658c00)(*(undefined8 *)(eox8_00 + 0x40));
  sk_swift_00349db0();
  (*sk_data_00658c00)();
  sk_swift_0034c2d8();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034aee4();
  sk_swift_00350500();
  sk_swift_00310d68();
  sk_rt_000a6f88();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b05c();
  sk_swift_00352ff4();
  sk_swift_0034ab9c(*(undefined8 *)(eox16_02 + 0x150));
  (*eox10)();
  sk_swift_0035a128();
  sk_swift_0034fc34(au4._0_8_,au4._8_8_);
  sk_vspace_0020c814();
  sk_swift_0034fc34(ir_x3,ir_x4);
  sk_vspace_0020c814();
  sk_swift_003192d8(u1);
  sk_swift_0034f644();
  sk_swift_00358ba8();
  (*eox9)();
  pcVar2 = *(code **)(eox16_00 + 8);
  sk_rt_0008e388();
  (*pcVar2)();
  sk_rt_000e15d8();
  (*pcVar2)();
  sk_swift_003505e8(*(undefined8 *)(eox16_01 + 8));
  (*eox8_01)();
  sk_swift_00356f6c();
  sk_swift_003536ac();
  sk_swift_0035a298(sk_swift_0031ba08);
  sk_rt_001d88fc();
  sk_swift_0035407c();
  sk_swift_0035060c();
  (*eox8_02)();
  sk_rt_0008e500(l10,uStack_8,rxx30);
  return;
}

/* FUN_0020d620 @ 0x0020d620   (est. sk_vspace_0020d620)
 * Ghidra: void FUN_0020d620(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020d620(undefined8 *p1,undefined8 p2,undefined8 p3,undefined8 p4)

{
    uint64_t scratch_0[2]={0};
  long lVar1;
  undefined8 u2;
  long lVar3;
  long eox8;
  
  lVar1 = sk_swift_00377824(0,p4,p3,&sk_data_0060e208,&sk_data_0060e230);
  lVar3 = *(long *)(lVar1 + -8);
  (*sk_data_00658c00)(*(long *)(lVar3 + 0x40) + 0xfU & 0xfffffffffffffff0);
  u2 = sk_swift_00377bec(p4,p3,lVar1,&sk_data_0060e208,&sk_data_0060e218);
  sk_swift_0031b9c0(0,lVar1,u2);
  (**(code **)(lVar3 + 0x10))(scratch_0 + -eox8,p2,lVar1);
  u2 = ((uint64_t(*)(uintptr_t))sk_vspace_0020c7fc)((uintptr_t)scratch_0);
  *p1 = u2;
  p1[1] = 0x66c280;
  return;
}

/* FUN_0020d75c @ 0x0020d75c   (est. sk_vspace_0020d75c)
 * Ghidra: void FUN_0020d75c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020d75c(void)

{
    uint64_t scratch_0[2]={0}; uint64_t scratch_1[2]={0};
  undefined8 *puVar1;
  undefined8 u2;
  undefined8 u3;
  long *plVar4;
  undefined8 u5;
  undefined8 eox1;
  code *eox8;
  long lVar6;
  code *eox8_00;
  code *eox8_01;
  long eox8_02;
  code *eox8_03;
  code *eox8_04;
  code *eox10;
  code *eox10_00;
  code *eox10_01;
  long eox16;
  long eox16_00;
  long eox16_01;
  long eox16_02;
  long eox16_03;
  long eox16_04;
  long eox16_05;
  long *rxx20;
  code *pcVar7;
  undefined8 u8;
  undefined8 u9;
  undefined8 rxx27;
  undefined8 rxx30;
  undefined8 is00000038;
  undefined8 is00000048;
  undefined8 *is00000050;
  undefined8 *is00000060;
  undefined8 is00000068;
  undefined8 l20;
  undefined8 uStack_18;
  
  sk_rt_0008e518();
  u5 = rxx30;
  sk_rt_0007c0c4();
  sk_swift_003499b4();
  sk_swift_00351408();
  (*sk_data_00658c00)();
  puVar1 = (undefined8 *)sk_swift_0034c8f8();
  u9 = *puVar1;
  sk_swift_003549d8();
  u8 = *(undefined8 *)(eox16_00 + 0x148);
  sk_swift_0034f788();
  sk_swift_003508c0(0xff);
  u2 = sk_swift_00377824();
  sk_swift_0035060c();
  sk_swift_00351dcc();
  sk_swift_00377bec();
  u3 = sk_swift_00350c98();
  u3 = sk_swift_0031b9c0(u3,u2);
  plVar4 = (long *)sk_swift_00362acc(u9,u3);
  if (plVar4 != (long *)0x0) {
    sk_swift_0034ad8c(*(undefined8 *)(eox16 + 0x150));
    (*eox10)();
    sk_swift_0035056c((long)plVar4 + *(long *)(*plVar4 + 0x48));
    sk_rt_001d30f8();
    sk_swift_0034eb94();
    (*eox8)();
    sk_rt_0008e500(rxx30);
    return;
  }
  sk_swift_003498f4();
  sk_swift_00349190();
  u3 = 0x20d8a8;
  sk_rt_0008e518();
  lVar6 = *rxx20;
  u9 = *(undefined8 *)(lVar6 + 0x148);
  is00000060 = scratch_0;
  is00000068 = u3;
  sk_swift_0034d070();
  sk_swift_0034ba38(0);
  sk_swift_00377824();
  sk_swift_00348d7c();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034af20();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b2f8();
  sk_swift_00350c8c(u9);
  sk_swift_00377bec();
  sk_swift_0034e414();
  sk_swift_0031b9c0();
  sk_swift_00356b8c();
  plVar4 = (long *)sk_swift_00362acc();
  if (plVar4 != (long *)0x0) {
    sk_swift_0034ad8c(*(undefined8 *)(lVar6 + 0x150));
    (*eox10_00)();
    sk_swift_00353bdc();
    sk_swift_00351c1c(u2,u5,rxx27);
    sk_vspace_0020c814();
    sk_swift_003513c0((long)plVar4 + *(long *)(*plVar4 + 0x48),eox1);
    sk_rt_001d31b0();
    sk_swift_003500c0();
    (*eox8_00)();
    sk_swift_00350524(*(undefined8 *)(eox16_01 + 8));
    (*eox8_01)();
    u5 = sk_swift_00352980();
    sk_rt_0008e500(u5,is00000048);
    return;
  }
  sk_swift_003498f4();
  sk_swift_00349190();
  sk_rt_0008e518();
  is00000050 = scratch_1;
  sk_swift_003586cc();
  sk_swift_00350de4();
  u2 = *(undefined8 *)(eox16_02 + 0x148);
  sk_swift_00349748();
  sk_swift_003504a0();
  sk_swift_00377824();
  sk_swift_00348ce8();
  (*sk_data_00658c00)(*(undefined8 *)(eox8_02 + 0x40));
  sk_swift_003489c0();
  (*sk_data_00658c00)();
  sk_swift_0034b3d8();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034aee4();
  sk_swift_00352ff4();
  sk_swift_0034ab9c(*(undefined8 *)(eox16_05 + 0x150));
  (*eox10_01)();
  sk_swift_0035a128();
  sk_swift_0034fc34(u8,l20,uStack_18);
  sk_vspace_0020c814();
  sk_swift_0034fc34(eox16_01,lVar6,u5);
  sk_vspace_0020c814();
  sk_swift_00310cd4(u2);
  u5 = sk_swift_003505f4();
  sk_swift_00350974(u5,eox16_01);
  (*eox8_03)();
  pcVar7 = *(code **)(eox16_03 + 8);
  sk_swift_003508b4();
  (*pcVar7)();
  sk_swift_00350630();
  (*pcVar7)();
  sk_swift_003505e8(*(undefined8 *)(eox16_04 + 8));
  (*eox8_04)();
  u5 = sk_swift_003548b8();
  sk_rt_0008e500(u5,is00000038);
  return;
}

/* FUN_0020dc18 @ 0x0020dc18   (est. sk_vspace_0020dc18)
 * Ghidra: void FUN_0020dc18(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020dc18(void)

{
  code *eox8;
  code *eox8_00;
  code *eox10;
  long eox16;
  long eox16_00;
  long eox16_01;
  undefined8 u1;
  undefined8 u2;
  sk_ex16 au3;
  
  sk_swift_0034c998();
  u2 = *(undefined8 *)(eox16 + 0x140);
  sk_swift_00349734();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b2f8();
  sk_swift_0035147c();
  au3 = (sk_ex16){ (uint64_t)sk_swift_0034b5bc(*(undefined8 *)(eox16_00 + 0x150)), 0 };
  (*eox10)(au3._0_8_,au3._8_8_,u2);
  sk_swift_0035147c();
  u1 = *(undefined8 *)(eox16_01 + 0x148);
  sk_rt_00027788(u1);
  u2 = sk_swift_0034b328();
  (*eox8)(u2,u1);
  sk_swift_0034ea18();
  (*eox8_00)();
  sk_swift_00356c54();
  return;
}

/* FUN_0020ddd8 @ 0x0020ddd8   (est. sk_vspace_0020ddd8)
 * Ghidra: void FUN_0020ddd8(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020ddd8(void)

{
  undefined8 u1;
  undefined8 u2;
  code *eox9;
  code *eox9_00;
  long eox16;
  long eox16_00;
  
  u1 = sk_rt_00084220();
  sk_rt_0007c0c4();
  sk_swift_003499b4();
  sk_swift_00351408();
  (*sk_data_00658c00)();
  sk_swift_00349c14();
  sk_rt_00027754(*(undefined8 *)(eox16 + 0x160));
  sk_swift_00352894();
  sk_swift_00350ca4();
  sk_swift_0034c454();
  sk_swift_00377824();
  sk_swift_0034ab20();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034aee4();
  sk_rt_000027e8();
  sk_swift_0034d284(*(undefined8 *)(eox16_00 + 0x168));
  (*eox9)();
  sk_rt_000a68c4();
  sk_swift_00350b24();
  sk_swift_0035072c();
  (*eox9_00)();
  sk_swift_0034ed78();
  sk_swift_00377bec();
  sk_swift_00355b04();
  u2 = sk_rt_002085fc();
  sk_rt_00084234(u2,u1);
  return;
}

/* FUN_0020df00 @ 0x0020df00   (est. sk_vspace_0020df00)
 * Ghidra: void FUN_0020df00(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020df00(void)

{
  code *eox8;
  code *eox8_00;
  code *eox10;
  long eox16;
  long eox16_00;
  
  sk_swift_0034ecb8();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b2f8();
  sk_swift_00351d9c();
  sk_swift_0034ad8c(*(undefined8 *)(eox16 + 0x168));
  (*eox10)();
  sk_swift_00351d9c();
  sk_rt_00027754(*(undefined8 *)(eox16_00 + 0x160));
  sk_swift_00350950();
  sk_rt_000a6894();
  sk_swift_0034ac64();
  (*eox8)();
  sk_swift_0034da48();
  (*eox8_00)();
  sk_swift_00356310();
  return;
}

/* FUN_0020dfdc @ 0x0020dfdc   (est. sk_vspace_0020dfdc)
 * Ghidra: void FUN_0020dfdc(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020dfdc(void)

{
  code *eox8;
  code *eox10;
  long eox16;
  long eox16_00;
  undefined8 u1;
  undefined8 is00000018;
  uint8_t auStack_40[32];
  undefined8 l20;
  
  sk_swift_00353cfc();
  sk_swift_0034d634();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_00352ff4();
  sk_swift_0034c1bc(*(undefined8 *)(eox16 + 0x168));
  (*eox10)();
  sk_swift_0035a1f4();
  u1 = *(undefined8 *)(eox16_00 + 0x160);
  l20 = u1;
  sk_swift_0034a210();
  sk_rt_00002534();
  sk_rt_00027754(u1);
  sk_swift_00351560(sk_swift_0031ba24,auStack_40);
  sk_swift_00358eb8();
  sk_rt_000262fc();
  sk_swift_00354dd0();
  sk_swift_0034f9c8();
  (*eox8)();
  u1 = sk_swift_00352df4();
  sk_swift_00353d14(u1,is00000018);
  return;
}

/* FUN_0020e114 @ 0x0020e114   (est. sk_vspace_0020e114)
 * Ghidra: void FUN_0020e114(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e114(void)

{
  code *eox9;
  long eox16;
  long eox16_00;
  long eox16_01;
  undefined8 u1;
  undefined8 rxx30;
  sk_ex16 au2;
  
  sk_swift_00358fb4();
  sk_swift_0034c704();
  u1 = *(undefined8 *)(eox16 + 0x158);
  sk_swift_00349c70();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034aee4();
  sk_swift_00352188();
  au2 = (sk_ex16){ (uint64_t)sk_swift_00352ba4(*(undefined8 *)(eox16_00 + 0x168)), 0 };
  (*eox9)(au2._0_8_,au2._8_8_,u1);
  sk_swift_00352188();
  sk_swift_00356ce0(*(undefined8 *)(eox16_01 + 0x160));
  sk_swift_0034d130();
  sk_swift_00358cec();
  u1 = ((uint64_t(*)(void))sk_vspace_0020a084)();
  sk_swift_00358fc8(u1,rxx30);
  return;
}

/* FUN_0020e1d8 @ 0x0020e1d8   (est. sk_vspace_0020e1d8)
 * Ghidra: void FUN_0020e1d8(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e1d8(void)

{
  code *eox8;
  code *eox10;
  long eox16;
  long eox16_00;
  long eox16_01;
  undefined8 rxx30;
  
  sk_swift_0035a7c0();
  sk_swift_00351a68();
  sk_swift_00354330();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0d4();
  sk_swift_00354330();
  sk_swift_0034e924(*(undefined8 *)(eox16_00 + 0x168));
  (*eox10)();
  sk_swift_00354330();
  sk_swift_00356ce0(*(undefined8 *)(eox16_01 + 0x160));
  sk_swift_0034d758();
  ((void(*)(void))sk_vspace_0020a3b0)();
  sk_swift_003508cc(*(undefined8 *)(eox16 + 8));
  (*eox8)();
  sk_swift_00359f3c();
  sk_swift_0035a7d4(rxx30);
  return;
}

/* FUN_0020e2c0 @ 0x0020e2c0   (est. sk_vspace_0020e2c0)
 * Ghidra: undefined8 FUN_0020e2c0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
undefined8 sk_vspace_0020e2c0(void)

{
  undefined8 u1;
  code *eox8;
  code *eox8_00;
  code *eox10;
  long eox16;
  long eox16_00;
  
  sk_swift_003542f4();
  sk_swift_003494e8();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b0c4();
  sk_swift_003542f4();
  sk_swift_0034c1bc(*(undefined8 *)(eox16 + 0x168));
  (*eox10)();
  sk_swift_003542f4();
  sk_rt_00027754(*(undefined8 *)(eox16_00 + 0x160));
  sk_swift_0035125c();
  sk_swift_0031b62c();
  sk_swift_00350804();
  sk_swift_00351190();
  u1 = (*eox8)();
  sk_swift_0034f9c8();
  (*eox8_00)();
  return u1;
}

/* FUN_0020e3b0 @ 0x0020e3b0   (est. sk_vspace_0020e3b0)
 * Ghidra: void FUN_0020e3b0(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e3b0(void)

{
  code *eox8;
  code *eox9;
  long eox16;
  long eox16_00;
  long eox16_01;
  undefined8 u1;
  sk_ex16 au2;
  
  sk_swift_0034c998();
  u1 = *(undefined8 *)(eox16 + 0x158);
  sk_swift_00349734();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034b460();
  sk_swift_0035147c();
  au2 = (sk_ex16){ (uint64_t)sk_swift_00352dc4(*(undefined8 *)(eox16_00 + 0x168)), 0 };
  (*eox9)(au2._0_8_,au2._8_8_,u1);
  sk_swift_0035147c();
  sk_rt_00027754(*(undefined8 *)(eox16_01 + 0x160));
  sk_swift_00350780();
  sk_swift_00310da8();
  sk_swift_0034c6a4();
  (*eox8)();
  return;
}

/* FUN_0020e478 @ 0x0020e478   (est. sk_vspace_0020e478)
 * Ghidra: void FUN_0020e478(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e478(void)

{
  code *eox8;
  code *eox9;
  long eox16;
  long eox16_00;
  undefined8 rxx30;
  sk_ex16 au1;
  
  sk_rt_0008e518();
  sk_swift_0035316c();
  sk_rt_0007c0c4();
  sk_swift_003499b4();
  sk_swift_00351408();
  (*sk_data_00658c00)();
  sk_swift_0034c8f8();
  sk_swift_003549d8();
  sk_rt_00027754(*(undefined8 *)(eox16 + 0x160));
  sk_swift_00351ad4();
  sk_swift_0034c1e4();
  sk_swift_00350c68();
  sk_swift_00377824();
  sk_swift_00349e10();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034af20();
  sk_rt_000027e8();
  sk_swift_0034d080(*(undefined8 *)(eox16_00 + 0x168));
  (*eox9)();
  sk_swift_003191e8();
  sk_swift_0034cd2c();
  (*eox8)();
  sk_swift_0034ee18();
  sk_swift_00377bec();
  sk_swift_00359388();
  au1 = (sk_ex16){ (uint64_t)sk_swift_00354804(), 0 };
  sk_rt_0008e500(au1._0_8_,au1._8_8_,rxx30);
  return;
}

/* FUN_0020e5a4 @ 0x0020e5a4   (est. sk_vspace_0020e5a4)
 * Ghidra: void FUN_0020e5a4(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e5a4(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_0020e5a8 @ 0x0020e5a8   (est. sk_vspace_0020e5a8)
 * Ghidra: void FUN_0020e5a8(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e5a8(void)

{
  sk_swift_0034e3e4();
  sk_vspace_0020e624();
  return;
}

/* FUN_0020e5c0 @ 0x0020e5c0   (est. sk_vspace_0020e5c0)
 * Ghidra: void FUN_0020e5c0(undefined8 param_1)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e5c0(undefined8 p1)

{
  sk_rt_00210bd4(p1,sk_rt_0020eabc);
  return;
}

/* FUN_0020e608 @ 0x0020e608   (est. sk_vspace_0020e608)
 * Ghidra: void FUN_0020e608(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e608(void)
{
    /* Trivial leaf (pacibsp only): no-op. */
}


/* FUN_0020e60c @ 0x0020e60c   (est. sk_vspace_0020e60c)
 * Ghidra: void FUN_0020e60c(void)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e60c(void)

{
  sk_swift_0034e3cc();
  sk_vspace_0020e624();
  return;
}

/* FUN_0020e624 @ 0x0020e624   (est. sk_vspace_0020e624)
 * Ghidra: void FUN_0020e624(undefined8 param_1,undefined8 param_2,code *param_3)
 * Confidence: medium
 * Notes: Swift-object-model vspace/page-table method. See part-file header.
 */
void sk_vspace_0020e624(undefined8 p1,undefined8 p2,code *p3)

{
  undefined8 u1;
  code *eox9;
  long eox16;
  long eox16_00;
  long rxx21;
  undefined8 is00000048;
  
  sk_swift_00353cfc();
  sk_swift_0034cca8();
  sk_swift_003499b4();
  sk_swift_00351408();
  (*sk_data_00658c00)();
  sk_swift_0034c8f8();
  sk_swift_003549d8();
  sk_swift_00351ad4(*(undefined8 *)(eox16 + 0x160));
  sk_swift_0034c20c();
  sk_swift_00350c68();
  sk_swift_00377824();
  sk_swift_00349e10();
  sk_rt_0007c1a4();
  (*sk_data_00658c00)();
  sk_swift_0034af20();
  sk_rt_000027e8();
  sk_swift_0034d080(*(undefined8 *)(eox16_00 + 0x168));
  (*eox9)();
  sk_swift_00351444();
  (*p3)();
  if (rxx21 == 0) {
    sk_swift_0035238c();
    sk_swift_0034f344();
    sk_swift_00377bec();
    sk_swift_0034c55c();
    sk_swift_0031ba3c();
    sk_swift_00352b74();
    ((void(*)(void))sk_vspace_0020e5c0)();
  }
  u1 = sk_swift_00354b5c();
  sk_swift_00353d14(u1,is00000048);
  return;
}

