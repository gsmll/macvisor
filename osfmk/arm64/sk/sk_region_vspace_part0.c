/* Recreated from ringminus1/sk/cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary; estimates unless matched.
 *
 * Region 0x200150-0x208a70 (slice 0 of the cL4 vspace/page-table + object-description layer).
 *
 * NOTE ON TRANSCRIPTION: this region is dominated by calls into the large shared cL4/seL4 runtime
 * library OUTSIDE 0x200000-0x280000 (the FUN_0034xxxx/0035xxxx/0037xxxx/000xxxxx callees). Those are
 * out of scope for this slice and are declared below as externs named rt_<addr> (the FUN_ address is
 * preserved in a trailing comment). The bodies are faithful mechanical transcriptions of the Ghidra
 * decompiler output: every call, branch, slot offset, string and panic path is preserved; Ghidra
 * locals were mechanically renamed to readable forms and all raw Ghidra identifiers were removed from
 * the bodies (they survive only in the header comments). Runtime externs use the C "unspecified
 * parameters" form (void f();) because the shared-library signatures are outside this slice; call
 * arity is therefore not type-checked against them. 16-byte-returning helpers return sk_u128_t and
 * scalar uses take the .lo word. A few in-slice callees had their parameters dropped by the
 * decompiler; they are declared with unspecified parameters, and cross-calls are padded to the
 * definition parameter count and each argument cast to its parameter type so that call-site
 * arity/pointer-vs-integer discrepancies introduced by the decompiler's own type recovery do not
 * fail the build.
 *
 * Dominant theme (Swift-style strings: "N children"/"1 child"/"elements"/"members"/"key-value pairs"/
 * "super", "Fatal error", "Index out of bounds", "Method must be overridden") is the cL4 object-graph
 * description / reflection dump engine plus its invariant-assert helpers and the object-table
 * walk/insert/lookup layer. The 002087xx-00208axx tail is a family of base-class virtual methods and
 * pure destructors that trap via sk_abstract_method (must be overridden). */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

typedef struct sk_u128 { word_t lo; word_t hi; } sk_u128_t;
typedef word_t (*sk_fnptr)();

#define SCARRY8(a,b)  (__builtin_add_overflow((word_t)(a),(word_t)(b),&(word_t){0}))
#define SBORROW8(a,b) (__builtin_sub_overflow((word_t)(a),(word_t)(b),&(word_t){0}))
#define SoftwareBreakpoint(n,pc) ((void*)0)

/* ---- shared runtime library (out of scope for this slice) ---- */
extern sk_u128_t rt_00002534(); /* FUN_00002534 (shared cL4 runtime library, out of scope) */
extern word_t rt_000026e8(); /* FUN_000026e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_000027e8(); /* FUN_000027e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00012568(); /* FUN_00012568 (shared cL4 runtime library, out of scope) */
extern word_t rt_0001df60(); /* FUN_0001df60 (shared cL4 runtime library, out of scope) */
extern word_t rt_00027724(); /* FUN_00027724 (shared cL4 runtime library, out of scope) */
extern word_t rt_00027754(); /* FUN_00027754 (shared cL4 runtime library, out of scope) */
extern word_t rt_00027788(); /* FUN_00027788 (shared cL4 runtime library, out of scope) */
extern word_t rt_000277b8(); /* FUN_000277b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_000277e8(); /* FUN_000277e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00027818(); /* FUN_00027818 (shared cL4 runtime library, out of scope) */
extern word_t rt_00041138(); /* FUN_00041138 (shared cL4 runtime library, out of scope) */
extern word_t rt_0006a4c0(); /* FUN_0006a4c0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0006b6f4(); /* FUN_0006b6f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0006e778(); /* FUN_0006e778 (shared cL4 runtime library, out of scope) */
extern word_t rt_0006f768(); /* FUN_0006f768 (shared cL4 runtime library, out of scope) */
extern word_t rt_00077070(); /* FUN_00077070 (shared cL4 runtime library, out of scope) */
extern word_t rt_000777d4(); /* FUN_000777d4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00077888(); /* FUN_00077888 (shared cL4 runtime library, out of scope) */
extern word_t rt_00077894(); /* FUN_00077894 (shared cL4 runtime library, out of scope) */
extern word_t rt_0007b384(); /* FUN_0007b384 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0007c0c4(); /* FUN_0007c0c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0007c1a4(); /* FUN_0007c1a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0007c1c4(); /* FUN_0007c1c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_000839d8(); /* FUN_000839d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_000839f8(); /* FUN_000839f8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00083a18(); /* FUN_00083a18 (shared cL4 runtime library, out of scope) */
extern word_t rt_0008409c(); /* FUN_0008409c (shared cL4 runtime library, out of scope) */
extern word_t rt_00084174(); /* FUN_00084174 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00084180(); /* FUN_00084180 (shared cL4 runtime library, out of scope) */
extern word_t rt_00084220(); /* FUN_00084220 (shared cL4 runtime library, out of scope) */
extern word_t rt_00084234(); /* FUN_00084234 (shared cL4 runtime library, out of scope) */
extern word_t rt_0008da6c(); /* FUN_0008da6c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0008e388(); /* FUN_0008e388 (shared cL4 runtime library, out of scope) */
extern word_t rt_0008e500(); /* FUN_0008e500 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0008e518(); /* FUN_0008e518 (shared cL4 runtime library, out of scope) */
extern word_t rt_0009461c(); /* FUN_0009461c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0009e234(); /* FUN_0009e234 (shared cL4 runtime library, out of scope) */
extern word_t rt_000a68f4(); /* FUN_000a68f4 (shared cL4 runtime library, out of scope) */
extern word_t rt_000a6f88(); /* FUN_000a6f88 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000b43d0(); /* FUN_000b43d0 (shared cL4 runtime library, out of scope) */
extern word_t rt_000b4594(); /* FUN_000b4594 (shared cL4 runtime library, out of scope) */
extern word_t rt_000b45b0(); /* FUN_000b45b0 (shared cL4 runtime library, out of scope) */
extern word_t rt_000bd3a4(); /* FUN_000bd3a4 (shared cL4 runtime library, out of scope) */
extern word_t rt_000dbc98(); /* FUN_000dbc98 (shared cL4 runtime library, out of scope) */
extern word_t rt_000e15d8(); /* FUN_000e15d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_000e710c(); /* FUN_000e710c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_000e72b0(); /* FUN_000e72b0 (shared cL4 runtime library, out of scope) */
extern word_t rt_000ec044(); /* FUN_000ec044 (shared cL4 runtime library, out of scope) */
extern word_t rt_00100c38(); /* FUN_00100c38 (shared cL4 runtime library, out of scope) */
extern word_t rt_00100efc(); /* FUN_00100efc (shared cL4 runtime library, out of scope) */
extern word_t rt_00106e3c(); /* FUN_00106e3c (shared cL4 runtime library, out of scope) */
extern word_t rt_0014ae44(); /* FUN_0014ae44 (shared cL4 runtime library, out of scope) */
extern word_t rt_0016186c(); /* FUN_0016186c (shared cL4 runtime library, out of scope) */
extern word_t rt_0019f1ec(); /* FUN_0019f1ec (shared cL4 runtime library, out of scope) */
extern word_t rt_0019fa60(); /* FUN_0019fa60 (shared cL4 runtime library, out of scope) */
extern word_t rt_001a0194(); /* FUN_001a0194 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_001a89a8(); /* FUN_001a89a8 (shared cL4 runtime library, out of scope) */
extern word_t rt_001afa84() __attribute__((noreturn)); /* FUN_001afa84 (shared cL4 runtime library, out of scope) */
extern word_t rt_001afe4c() __attribute__((noreturn)); /* FUN_001afe4c (shared cL4 runtime library, out of scope) */
extern word_t rt_001b5784(); /* FUN_001b5784 (shared cL4 runtime library, out of scope) */
extern word_t rt_001b5a88(); /* FUN_001b5a88 (shared cL4 runtime library, out of scope) */
extern word_t rt_001b68a0(); /* FUN_001b68a0 (shared cL4 runtime library, out of scope) */
extern word_t rt_001b9040(); /* FUN_001b9040 (shared cL4 runtime library, out of scope) */
extern word_t rt_001db6b0(); /* FUN_001db6b0 (shared cL4 runtime library, out of scope) */
extern word_t rt_001e088c(); /* FUN_001e088c (shared cL4 runtime library, out of scope) */
extern word_t rt_001e2460(); /* FUN_001e2460 (shared cL4 runtime library, out of scope) */
extern word_t rt_001e3048(); /* FUN_001e3048 (shared cL4 runtime library, out of scope) */
extern word_t rt_001e9f14(); /* FUN_001e9f14 (shared cL4 runtime library, out of scope) */
extern word_t rt_001edb28(); /* FUN_001edb28 (shared cL4 runtime library, out of scope) */
extern word_t rt_001ef7ac(); /* FUN_001ef7ac (shared cL4 runtime library, out of scope) */
extern word_t rt_001ef808(); /* FUN_001ef808 (shared cL4 runtime library, out of scope) */
extern word_t rt_001fccf8(); /* FUN_001fccf8 (shared cL4 runtime library, out of scope) */
extern word_t rt_001fd4f4(); /* FUN_001fd4f4 (shared cL4 runtime library, out of scope) */
extern word_t rt_001fe7cc(); /* FUN_001fe7cc (shared cL4 runtime library, out of scope) */
extern word_t rt_001fe9a8(); /* FUN_001fe9a8 (shared cL4 runtime library, out of scope) */
extern word_t rt_001fea40(); /* FUN_001fea40 (shared cL4 runtime library, out of scope) */
extern word_t rt_001fff64(); /* FUN_001fff64 (shared cL4 runtime library, out of scope) */
extern word_t rt_00210bd4(); /* FUN_00210bd4 (shared cL4 runtime library, out of scope) */
extern word_t rt_002364dc(); /* FUN_002364dc (shared cL4 runtime library, out of scope) */
extern word_t rt_00250904(); /* FUN_00250904 (shared cL4 runtime library, out of scope) */
extern word_t rt_00262b5c(); /* FUN_00262b5c (shared cL4 runtime library, out of scope) */
extern word_t rt_002667a8(); /* FUN_002667a8 (shared cL4 runtime library, out of scope) */
extern word_t rt_002678b4(); /* FUN_002678b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0026c274(); /* FUN_0026c274 (shared cL4 runtime library, out of scope) */
extern word_t rt_0027743c(); /* FUN_0027743c (shared cL4 runtime library, out of scope) */
extern word_t rt_00277474(); /* FUN_00277474 (shared cL4 runtime library, out of scope) */
extern word_t rt_00279568(); /* FUN_00279568 (shared cL4 runtime library, out of scope) */
extern word_t rt_0027a6e0(); /* FUN_0027a6e0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00280bc4(); /* FUN_00280bc4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00284424(); /* FUN_00284424 (shared cL4 runtime library, out of scope) */
extern word_t rt_002a218c(); /* FUN_002a218c (shared cL4 runtime library, out of scope) */
extern word_t rt_002a2698(); /* FUN_002a2698 (shared cL4 runtime library, out of scope) */
extern word_t rt_002a2748(); /* FUN_002a2748 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_002a4c98(); /* FUN_002a4c98 (shared cL4 runtime library, out of scope) */
extern word_t rt_00310924(); /* FUN_00310924 (shared cL4 runtime library, out of scope) */
extern word_t rt_00310b08(); /* FUN_00310b08 (shared cL4 runtime library, out of scope) */
extern word_t rt_00310cd4(); /* FUN_00310cd4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00310d68(); /* FUN_00310d68 (shared cL4 runtime library, out of scope) */
extern word_t rt_00310d98(); /* FUN_00310d98 (shared cL4 runtime library, out of scope) */
extern word_t rt_00310e08(); /* FUN_00310e08 (shared cL4 runtime library, out of scope) */
extern word_t rt_00310e20(); /* FUN_00310e20 (shared cL4 runtime library, out of scope) */
extern word_t rt_00310ed4(); /* FUN_00310ed4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00310f04(); /* FUN_00310f04 (shared cL4 runtime library, out of scope) */
extern word_t rt_00319230(); /* FUN_00319230 (shared cL4 runtime library, out of scope) */
extern word_t rt_003192d8(); /* FUN_003192d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_003194f8(); /* FUN_003194f8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00319658(); /* FUN_00319658 (shared cL4 runtime library, out of scope) */
extern word_t rt_00319808(); /* FUN_00319808 (shared cL4 runtime library, out of scope) */
extern word_t rt_003198cc(); /* FUN_003198cc (shared cL4 runtime library, out of scope) */
extern word_t rt_00319a4c(); /* FUN_00319a4c (shared cL4 runtime library, out of scope) */
extern word_t rt_0031afcc(); /* FUN_0031afcc (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b050(); /* FUN_0031b050 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b110(); /* FUN_0031b110 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b2bc(); /* FUN_0031b2bc (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b2ec(); /* FUN_0031b2ec (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b704(); /* FUN_0031b704 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b71c(); /* FUN_0031b71c (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b760(); /* FUN_0031b760 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b778(); /* FUN_0031b778 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b858(); /* FUN_0031b858 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b870(); /* FUN_0031b870 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b8d0(); /* FUN_0031b8d0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b900(); /* FUN_0031b900 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b930(); /* FUN_0031b930 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031b948(); /* FUN_0031b948 (shared cL4 runtime library, out of scope) */
extern word_t rt_0031e104(); /* FUN_0031e104 (shared cL4 runtime library, out of scope) */
extern word_t rt_0032d3e0(); /* FUN_0032d3e0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034310c(); /* FUN_0034310c (shared cL4 runtime library, out of scope) */
extern word_t rt_00344e54(); /* FUN_00344e54 (shared cL4 runtime library, out of scope) */
extern word_t rt_00347d60(); /* FUN_00347d60 (shared cL4 runtime library, out of scope) */
extern word_t rt_00347da8(); /* FUN_00347da8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348034(); /* FUN_00348034 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034846c(); /* FUN_0034846c (shared cL4 runtime library, out of scope) */
extern word_t rt_003484e4(); /* FUN_003484e4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348638(); /* FUN_00348638 (shared cL4 runtime library, out of scope) */
extern word_t rt_003486b8(); /* FUN_003486b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_003488bc(); /* FUN_003488bc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034895c(); /* FUN_0034895c (shared cL4 runtime library, out of scope) */
extern word_t rt_00348a50(); /* FUN_00348a50 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348a80(); /* FUN_00348a80 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348abc(); /* FUN_00348abc (shared cL4 runtime library, out of scope) */
extern word_t rt_00348b5c(); /* FUN_00348b5c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00348b94(); /* FUN_00348b94 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348bbc(); /* FUN_00348bbc (shared cL4 runtime library, out of scope) */
extern word_t rt_00348c30(); /* FUN_00348c30 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348cd0(); /* FUN_00348cd0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348ce8(); /* FUN_00348ce8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348d4c(); /* FUN_00348d4c (shared cL4 runtime library, out of scope) */
extern word_t rt_00348d7c(); /* FUN_00348d7c (shared cL4 runtime library, out of scope) */
extern word_t rt_00348e18(); /* FUN_00348e18 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348e9c(); /* FUN_00348e9c (shared cL4 runtime library, out of scope) */
extern word_t rt_00348f38(); /* FUN_00348f38 (shared cL4 runtime library, out of scope) */
extern word_t rt_00348fd8(); /* FUN_00348fd8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349080(); /* FUN_00349080 (shared cL4 runtime library, out of scope) */
extern word_t rt_003490b8(); /* FUN_003490b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034911c(); /* FUN_0034911c (shared cL4 runtime library, out of scope) */
extern word_t rt_00349178(); /* FUN_00349178 (shared cL4 runtime library, out of scope) */
extern word_t rt_003493c4(); /* FUN_003493c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003494e8(); /* FUN_003494e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349530(); /* FUN_00349530 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349720(); /* FUN_00349720 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349734(); /* FUN_00349734 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349748(); /* FUN_00349748 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034975c(); /* FUN_0034975c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003497a0(); /* FUN_003497a0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003497b4(); /* FUN_003497b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003497ec(); /* FUN_003497ec (shared cL4 runtime library, out of scope) */
extern word_t rt_00349830(); /* FUN_00349830 (shared cL4 runtime library, out of scope) */
extern word_t rt_003499dc(); /* FUN_003499dc (shared cL4 runtime library, out of scope) */
extern word_t rt_003499f0(); /* FUN_003499f0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349a68(); /* FUN_00349a68 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349b3c(); /* FUN_00349b3c (shared cL4 runtime library, out of scope) */
extern word_t rt_00349c70(); /* FUN_00349c70 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349db0(); /* FUN_00349db0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349de8(); /* FUN_00349de8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349ef4(); /* FUN_00349ef4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00349f5c(); /* FUN_00349f5c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a120(); /* FUN_0034a120 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a210(); /* FUN_0034a210 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034a274(); /* FUN_0034a274 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a30c(); /* FUN_0034a30c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a400(); /* FUN_0034a400 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a464(); /* FUN_0034a464 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a4e0(); /* FUN_0034a4e0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a5c8(); /* FUN_0034a5c8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a760(); /* FUN_0034a760 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a8cc(); /* FUN_0034a8cc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a980(); /* FUN_0034a980 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a9ac(); /* FUN_0034a9ac (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a9c0(); /* FUN_0034a9c0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a9d4(); /* FUN_0034a9d4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034a9e8(); /* FUN_0034a9e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034aa28(); /* FUN_0034aa28 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034aa54(); /* FUN_0034aa54 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034aa9c(); /* FUN_0034aa9c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034aadc(); /* FUN_0034aadc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ab20(); /* FUN_0034ab20 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ac14(); /* FUN_0034ac14 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ac3c(); /* FUN_0034ac3c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034acd0(); /* FUN_0034acd0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034acf0(); /* FUN_0034acf0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034aea8(); /* FUN_0034aea8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034aebc(); /* FUN_0034aebc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034aee4(); /* FUN_0034aee4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034af20(); /* FUN_0034af20 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b07c(); /* FUN_0034b07c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b0b4(); /* FUN_0034b0b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b0d4(); /* FUN_0034b0d4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b0e4(); /* FUN_0034b0e4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b150(); /* FUN_0034b150 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b1a0(); /* FUN_0034b1a0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b2a8(); /* FUN_0034b2a8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b2c8(); /* FUN_0034b2c8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b2f8(); /* FUN_0034b2f8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b308(); /* FUN_0034b308 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b348(); /* FUN_0034b348 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b358(); /* FUN_0034b358 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b3d8(); /* FUN_0034b3d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b430(); /* FUN_0034b430 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b440(); /* FUN_0034b440 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b4c0(); /* FUN_0034b4c0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b508(); /* FUN_0034b508 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b540(); /* FUN_0034b540 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b640(); /* FUN_0034b640 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b6f4(); /* FUN_0034b6f4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b708(); /* FUN_0034b708 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b71c(); /* FUN_0034b71c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b758(); /* FUN_0034b758 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b778(); /* FUN_0034b778 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b7b8(); /* FUN_0034b7b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b7c8(); /* FUN_0034b7c8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b804(); /* FUN_0034b804 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b824(); /* FUN_0034b824 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b87c(); /* FUN_0034b87c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034b89c(); /* FUN_0034b89c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034b8cc(); /* FUN_0034b8cc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ba68(); /* FUN_0034ba68 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034bc58(); /* FUN_0034bc58 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034bc6c(); /* FUN_0034bc6c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034bc94(); /* FUN_0034bc94 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034bccc(); /* FUN_0034bccc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034bec4(); /* FUN_0034bec4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034beec(); /* FUN_0034beec (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c034(); /* FUN_0034c034 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c074(); /* FUN_0034c074 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c108(); /* FUN_0034c108 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c220(); /* FUN_0034c220 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c2e8(); /* FUN_0034c2e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c354(); /* FUN_0034c354 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c3c4(); /* FUN_0034c3c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c434(); /* FUN_0034c434 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c4fc(); /* FUN_0034c4fc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c54c(); /* FUN_0034c54c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c5cc(); /* FUN_0034c5cc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c60c(); /* FUN_0034c60c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c684(); /* FUN_0034c684 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c694(); /* FUN_0034c694 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c6b4(); /* FUN_0034c6b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c818(); /* FUN_0034c818 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c8c8(); /* FUN_0034c8c8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034c9d8(); /* FUN_0034c9d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ca28(); /* FUN_0034ca28 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034cae8(); /* FUN_0034cae8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034cd54(); /* FUN_0034cd54 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034cd7c(); /* FUN_0034cd7c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034cde8(); /* FUN_0034cde8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ce58(); /* FUN_0034ce58 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ced8(); /* FUN_0034ced8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034cfa4(); /* FUN_0034cfa4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034cff4(); /* FUN_0034cff4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d044(); /* FUN_0034d044 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d234(); /* FUN_0034d234 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d294(); /* FUN_0034d294 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d2a4(); /* FUN_0034d2a4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d2d4(); /* FUN_0034d2d4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d404(); /* FUN_0034d404 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d424(); /* FUN_0034d424 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d434(); /* FUN_0034d434 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d598(); /* FUN_0034d598 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d5a8(); /* FUN_0034d5a8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d654(); /* FUN_0034d654 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d688(); /* FUN_0034d688 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d758(); /* FUN_0034d758 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d7a8(); /* FUN_0034d7a8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d7fc(); /* FUN_0034d7fc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d888(); /* FUN_0034d888 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034d89c(); /* FUN_0034d89c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034dae8(); /* FUN_0034dae8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034db68(); /* FUN_0034db68 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034db88(); /* FUN_0034db88 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034db98(); /* FUN_0034db98 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034dd64(); /* FUN_0034dd64 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ddd8(); /* FUN_0034ddd8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034de44(); /* FUN_0034de44 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034de64(); /* FUN_0034de64 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034de8c(); /* FUN_0034de8c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034df34(); /* FUN_0034df34 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034df64(); /* FUN_0034df64 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e024(); /* FUN_0034e024 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e034(); /* FUN_0034e034 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e044(); /* FUN_0034e044 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e054(); /* FUN_0034e054 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e0c4(); /* FUN_0034e0c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e130(); /* FUN_0034e130 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e54c(); /* FUN_0034e54c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e55c(); /* FUN_0034e55c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e67c(); /* FUN_0034e67c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e6cc(); /* FUN_0034e6cc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034e70c(); /* FUN_0034e70c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ecb8(); /* FUN_0034ecb8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ece8(); /* FUN_0034ece8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ee08(); /* FUN_0034ee08 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ee38(); /* FUN_0034ee38 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ee68(); /* FUN_0034ee68 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ee98(); /* FUN_0034ee98 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034eeb8(); /* FUN_0034eeb8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034eef8(); /* FUN_0034eef8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ef68(); /* FUN_0034ef68 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ef78(); /* FUN_0034ef78 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ef88(); /* FUN_0034ef88 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034efc8(); /* FUN_0034efc8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f014(); /* FUN_0034f014 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f030(); /* FUN_0034f030 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f064(); /* FUN_0034f064 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f3b4(); /* FUN_0034f3b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f3d4(); /* FUN_0034f3d4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f3f4(); /* FUN_0034f3f4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f4c4(); /* FUN_0034f4c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f4e4(); /* FUN_0034f4e4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f514(); /* FUN_0034f514 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f534(); /* FUN_0034f534 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f5b4(); /* FUN_0034f5b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f5e4(); /* FUN_0034f5e4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f604(); /* FUN_0034f604 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f634(); /* FUN_0034f634 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f674(); /* FUN_0034f674 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f714(); /* FUN_0034f714 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f730(); /* FUN_0034f730 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0034f98c(); /* FUN_0034f98c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f9ec(); /* FUN_0034f9ec (shared cL4 runtime library, out of scope) */
extern word_t rt_0034f9fc(); /* FUN_0034f9fc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034fb28(); /* FUN_0034fb28 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034fd6c(); /* FUN_0034fd6c (shared cL4 runtime library, out of scope) */
extern word_t rt_0034fdbc(); /* FUN_0034fdbc (shared cL4 runtime library, out of scope) */
extern word_t rt_0034feb0(); /* FUN_0034feb0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0034ff88(); /* FUN_0034ff88 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350048(); /* FUN_00350048 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350288(); /* FUN_00350288 (shared cL4 runtime library, out of scope) */
extern word_t rt_003502a8(); /* FUN_003502a8 (shared cL4 runtime library, out of scope) */
extern word_t rt_003502e8(); /* FUN_003502e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_003502f8(); /* FUN_003502f8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350308(); /* FUN_00350308 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350318(); /* FUN_00350318 (shared cL4 runtime library, out of scope) */
extern word_t rt_003503c0(); /* FUN_003503c0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350410(); /* FUN_00350410 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035041c(); /* FUN_0035041c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350428(); /* FUN_00350428 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350434(); /* FUN_00350434 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035044c(); /* FUN_0035044c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350464(); /* FUN_00350464 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350470(); /* FUN_00350470 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350488(); /* FUN_00350488 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350494(); /* FUN_00350494 (shared cL4 runtime library, out of scope) */
extern word_t rt_003504a0(); /* FUN_003504a0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003504ac(); /* FUN_003504ac (shared cL4 runtime library, out of scope) */
extern word_t rt_003504b8(); /* FUN_003504b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_003504c4(); /* FUN_003504c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003504d0(); /* FUN_003504d0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003504e8(); /* FUN_003504e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_003504f4(); /* FUN_003504f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035050c(); /* FUN_0035050c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350518(); /* FUN_00350518 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350524(); /* FUN_00350524 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350530(); /* FUN_00350530 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035053c(); /* FUN_0035053c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350548(); /* FUN_00350548 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350560(); /* FUN_00350560 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035056c(); /* FUN_0035056c (shared cL4 runtime library, out of scope) */
extern word_t rt_003505d0(); /* FUN_003505d0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003505e8(); /* FUN_003505e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035060c(); /* FUN_0035060c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350618(); /* FUN_00350618 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350624(); /* FUN_00350624 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350630(); /* FUN_00350630 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035063c(); /* FUN_0035063c (shared cL4 runtime library, out of scope) */
extern word_t rt_003506e8(); /* FUN_003506e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350704(); /* FUN_00350704 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350720(); /* FUN_00350720 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035072c(); /* FUN_0035072c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350744(); /* FUN_00350744 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350768(); /* FUN_00350768 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350774(); /* FUN_00350774 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350780(); /* FUN_00350780 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350798(); /* FUN_00350798 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003507bc(); /* FUN_003507bc (shared cL4 runtime library, out of scope) */
extern word_t rt_003507c8(); /* FUN_003507c8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003507e0(); /* FUN_003507e0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350804(); /* FUN_00350804 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350810(); /* FUN_00350810 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350834(); /* FUN_00350834 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035084c(); /* FUN_0035084c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350878(); /* FUN_00350878 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350884(); /* FUN_00350884 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035089c(); /* FUN_0035089c (shared cL4 runtime library, out of scope) */
extern word_t rt_003508b4(); /* FUN_003508b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003508c0(); /* FUN_003508c0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003508cc(); /* FUN_003508cc (shared cL4 runtime library, out of scope) */
extern word_t rt_003508d8(); /* FUN_003508d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003508e4(); /* FUN_003508e4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350914(); /* FUN_00350914 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350944(); /* FUN_00350944 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350974(); /* FUN_00350974 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350998(); /* FUN_00350998 (shared cL4 runtime library, out of scope) */
extern word_t rt_003509a4(); /* FUN_003509a4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003509b0(); /* FUN_003509b0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003509bc(); /* FUN_003509bc (shared cL4 runtime library, out of scope) */
extern word_t rt_003509e0(); /* FUN_003509e0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350a1c(); /* FUN_00350a1c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350a28(); /* FUN_00350a28 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350a34(); /* FUN_00350a34 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350a70(); /* FUN_00350a70 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350a7c(); /* FUN_00350a7c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350a88(); /* FUN_00350a88 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350aac(); /* FUN_00350aac (shared cL4 runtime library, out of scope) */
extern word_t rt_00350ac4(); /* FUN_00350ac4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350ad0(); /* FUN_00350ad0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350af4(); /* FUN_00350af4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350b00(); /* FUN_00350b00 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350b18(); /* FUN_00350b18 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350b24(); /* FUN_00350b24 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350b3c(); /* FUN_00350b3c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350b48(); /* FUN_00350b48 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350b54(); /* FUN_00350b54 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350b78(); /* FUN_00350b78 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350b84(); /* FUN_00350b84 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350b90(); /* FUN_00350b90 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350b9c(); /* FUN_00350b9c (shared cL4 runtime library, out of scope) */
extern word_t rt_00350bc0(); /* FUN_00350bc0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350bd8(); /* FUN_00350bd8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350bf0(); /* FUN_00350bf0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350bfc(); /* FUN_00350bfc (shared cL4 runtime library, out of scope) */
extern word_t rt_00350c50(); /* FUN_00350c50 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350cb4(); /* FUN_00350cb4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350d94(); /* FUN_00350d94 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350e74(); /* FUN_00350e74 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00350ea4(); /* FUN_00350ea4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00350edc(); /* FUN_00350edc (shared cL4 runtime library, out of scope) */
extern word_t rt_00350fdc(); /* FUN_00350fdc (shared cL4 runtime library, out of scope) */
extern word_t rt_0035100c(); /* FUN_0035100c (shared cL4 runtime library, out of scope) */
extern word_t rt_0035102c(); /* FUN_0035102c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003510ac(); /* FUN_003510ac (shared cL4 runtime library, out of scope) */
extern word_t rt_003510d0(); /* FUN_003510d0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003510dc(); /* FUN_003510dc (shared cL4 runtime library, out of scope) */
extern word_t rt_003510f4(); /* FUN_003510f4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351100(); /* FUN_00351100 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351118(); /* FUN_00351118 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351124(); /* FUN_00351124 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351130(); /* FUN_00351130 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351160(); /* FUN_00351160 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035116c(); /* FUN_0035116c (shared cL4 runtime library, out of scope) */
extern word_t rt_0035119c(); /* FUN_0035119c (shared cL4 runtime library, out of scope) */
extern word_t rt_003511c0(); /* FUN_003511c0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351238(); /* FUN_00351238 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035125c(); /* FUN_0035125c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351274(); /* FUN_00351274 (shared cL4 runtime library, out of scope) */
extern word_t rt_003512c0(); /* FUN_003512c0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003512d8(); /* FUN_003512d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_003512f4(); /* FUN_003512f4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351300(); /* FUN_00351300 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351318(); /* FUN_00351318 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351324(); /* FUN_00351324 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035136c(); /* FUN_0035136c (shared cL4 runtime library, out of scope) */
extern word_t rt_00351378(); /* FUN_00351378 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351384(); /* FUN_00351384 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035139c(); /* FUN_0035139c (shared cL4 runtime library, out of scope) */
extern word_t rt_003513b4(); /* FUN_003513b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003513d8(); /* FUN_003513d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351438(); /* FUN_00351438 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035145c(); /* FUN_0035145c (shared cL4 runtime library, out of scope) */
extern word_t rt_003514a0(); /* FUN_003514a0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003514b8(); /* FUN_003514b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_003514d0(); /* FUN_003514d0 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035152c(); /* FUN_0035152c (shared cL4 runtime library, out of scope) */
extern word_t rt_00351548(); /* FUN_00351548 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035156c(); /* FUN_0035156c (shared cL4 runtime library, out of scope) */
extern word_t rt_00351584(); /* FUN_00351584 (shared cL4 runtime library, out of scope) */
extern word_t rt_003515fc(); /* FUN_003515fc (shared cL4 runtime library, out of scope) */
extern word_t rt_00351648(); /* FUN_00351648 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035166c(); /* FUN_0035166c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003516e4(); /* FUN_003516e4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003516f0(); /* FUN_003516f0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003516fc(); /* FUN_003516fc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00351714(); /* FUN_00351714 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351744(); /* FUN_00351744 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351750(); /* FUN_00351750 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035179c(); /* FUN_0035179c (shared cL4 runtime library, out of scope) */
extern word_t rt_003518a0(); /* FUN_003518a0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003518b8(); /* FUN_003518b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_003518c4(); /* FUN_003518c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351978(); /* FUN_00351978 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351a20(); /* FUN_00351a20 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351a50(); /* FUN_00351a50 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351abc(); /* FUN_00351abc (shared cL4 runtime library, out of scope) */
extern word_t rt_00351ad4(); /* FUN_00351ad4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351af8(); /* FUN_00351af8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351b20(); /* FUN_00351b20 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351b2c(); /* FUN_00351b2c (shared cL4 runtime library, out of scope) */
extern word_t rt_00351b38(); /* FUN_00351b38 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351b78(); /* FUN_00351b78 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351b84(); /* FUN_00351b84 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351ba0(); /* FUN_00351ba0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351bd4(); /* FUN_00351bd4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351bec(); /* FUN_00351bec (shared cL4 runtime library, out of scope) */
extern word_t rt_00351c28(); /* FUN_00351c28 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351c4c(); /* FUN_00351c4c (shared cL4 runtime library, out of scope) */
extern word_t rt_00351c88(); /* FUN_00351c88 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351c94(); /* FUN_00351c94 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351cc4(); /* FUN_00351cc4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351cd0(); /* FUN_00351cd0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351d00(); /* FUN_00351d00 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351d18(); /* FUN_00351d18 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351d24(); /* FUN_00351d24 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351d9c(); /* FUN_00351d9c (shared cL4 runtime library, out of scope) */
extern word_t rt_00351db4(); /* FUN_00351db4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351dcc(); /* FUN_00351dcc (shared cL4 runtime library, out of scope) */
extern word_t rt_00351de4(); /* FUN_00351de4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351e08(); /* FUN_00351e08 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351e48(); /* FUN_00351e48 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351e78(); /* FUN_00351e78 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351e84(); /* FUN_00351e84 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351ef8(); /* FUN_00351ef8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351f10(); /* FUN_00351f10 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351f40(); /* FUN_00351f40 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351f4c(); /* FUN_00351f4c (shared cL4 runtime library, out of scope) */
extern word_t rt_00351f58(); /* FUN_00351f58 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351f7c(); /* FUN_00351f7c (shared cL4 runtime library, out of scope) */
extern word_t rt_00351f88(); /* FUN_00351f88 (shared cL4 runtime library, out of scope) */
extern word_t rt_00351fb0(); /* FUN_00351fb0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352018(); /* FUN_00352018 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352350(); /* FUN_00352350 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035238c(); /* FUN_0035238c (shared cL4 runtime library, out of scope) */
extern word_t rt_0035242c(); /* FUN_0035242c (shared cL4 runtime library, out of scope) */
extern word_t rt_00352450(); /* FUN_00352450 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352474(); /* FUN_00352474 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352480(); /* FUN_00352480 (shared cL4 runtime library, out of scope) */
extern word_t rt_003524a4(); /* FUN_003524a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003524b0(); /* FUN_003524b0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352554(); /* FUN_00352554 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352590(); /* FUN_00352590 (shared cL4 runtime library, out of scope) */
extern word_t rt_003525cc(); /* FUN_003525cc (shared cL4 runtime library, out of scope) */
extern word_t rt_003526b8(); /* FUN_003526b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352800(); /* FUN_00352800 (shared cL4 runtime library, out of scope) */
extern word_t rt_003528b8(); /* FUN_003528b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352920(); /* FUN_00352920 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352968(); /* FUN_00352968 (shared cL4 runtime library, out of scope) */
extern word_t rt_003529a4(); /* FUN_003529a4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352a28(); /* FUN_00352a28 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352a40(); /* FUN_00352a40 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352a4c(); /* FUN_00352a4c (shared cL4 runtime library, out of scope) */
extern word_t rt_00352a8c(); /* FUN_00352a8c (shared cL4 runtime library, out of scope) */
extern word_t rt_00352abc(); /* FUN_00352abc (shared cL4 runtime library, out of scope) */
extern word_t rt_00352afc(); /* FUN_00352afc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352b14(); /* FUN_00352b14 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352b98(); /* FUN_00352b98 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352bb0(); /* FUN_00352bb0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352bbc(); /* FUN_00352bbc (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352c68(); /* FUN_00352c68 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352ca4(); /* FUN_00352ca4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352ce0(); /* FUN_00352ce0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00352dc4(); /* FUN_00352dc4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352e3c(); /* FUN_00352e3c (shared cL4 runtime library, out of scope) */
extern word_t rt_00352e78(); /* FUN_00352e78 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352ea8(); /* FUN_00352ea8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352eb4(); /* FUN_00352eb4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00352ecc(); /* FUN_00352ecc (shared cL4 runtime library, out of scope) */
extern word_t rt_00352efc(); /* FUN_00352efc (shared cL4 runtime library, out of scope) */
extern word_t rt_00352f54(); /* FUN_00352f54 (shared cL4 runtime library, out of scope) */
extern word_t rt_003530b0(); /* FUN_003530b0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003530bc(); /* FUN_003530bc (shared cL4 runtime library, out of scope) */
extern word_t rt_003530d8(); /* FUN_003530d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353100(); /* FUN_00353100 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353130(); /* FUN_00353130 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035313c(); /* FUN_0035313c (shared cL4 runtime library, out of scope) */
extern word_t rt_00353148(); /* FUN_00353148 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353154(); /* FUN_00353154 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353190(); /* FUN_00353190 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353214(); /* FUN_00353214 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035336c(); /* FUN_0035336c (shared cL4 runtime library, out of scope) */
extern word_t rt_00353390(); /* FUN_00353390 (shared cL4 runtime library, out of scope) */
extern word_t rt_003534ec(); /* FUN_003534ec (shared cL4 runtime library, out of scope) */
extern word_t rt_0035351c(); /* FUN_0035351c (shared cL4 runtime library, out of scope) */
extern word_t rt_00353534(); /* FUN_00353534 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353540(); /* FUN_00353540 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035354c(); /* FUN_0035354c (shared cL4 runtime library, out of scope) */
extern word_t rt_0035359c(); /* FUN_0035359c (shared cL4 runtime library, out of scope) */
extern word_t rt_00353718(); /* FUN_00353718 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353734(); /* FUN_00353734 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353758(); /* FUN_00353758 (shared cL4 runtime library, out of scope) */
extern word_t rt_003537d4(); /* FUN_003537d4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353960(); /* FUN_00353960 (shared cL4 runtime library, out of scope) */
extern word_t rt_003539d8(); /* FUN_003539d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353a00(); /* FUN_00353a00 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353ad8(); /* FUN_00353ad8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353b34(); /* FUN_00353b34 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353b70(); /* FUN_00353b70 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353bac(); /* FUN_00353bac (shared cL4 runtime library, out of scope) */
extern word_t rt_00353bc4(); /* FUN_00353bc4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353c00(); /* FUN_00353c00 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353c6c(); /* FUN_00353c6c (shared cL4 runtime library, out of scope) */
extern word_t rt_00353d64(); /* FUN_00353d64 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353e88(); /* FUN_00353e88 (shared cL4 runtime library, out of scope) */
extern word_t rt_00353fa0(); /* FUN_00353fa0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354000(); /* FUN_00354000 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354064(); /* FUN_00354064 (shared cL4 runtime library, out of scope) */
extern word_t rt_003540dc(); /* FUN_003540dc (shared cL4 runtime library, out of scope) */
extern word_t rt_00354128(); /* FUN_00354128 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354134(); /* FUN_00354134 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00354264(); /* FUN_00354264 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035433c(); /* FUN_0035433c (shared cL4 runtime library, out of scope) */
extern word_t rt_00354388(); /* FUN_00354388 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354394(); /* FUN_00354394 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354410(); /* FUN_00354410 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354474(); /* FUN_00354474 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354570(); /* FUN_00354570 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035457c(); /* FUN_0035457c (shared cL4 runtime library, out of scope) */
extern word_t rt_0035460c(); /* FUN_0035460c (shared cL4 runtime library, out of scope) */
extern word_t rt_0035463c(); /* FUN_0035463c (shared cL4 runtime library, out of scope) */
extern word_t rt_00354708(); /* FUN_00354708 (shared cL4 runtime library, out of scope) */
extern word_t rt_003548e8(); /* FUN_003548e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354930(); /* FUN_00354930 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354ab0(); /* FUN_00354ab0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354ae8(); /* FUN_00354ae8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354afc(); /* FUN_00354afc (shared cL4 runtime library, out of scope) */
extern word_t rt_00354bb0(); /* FUN_00354bb0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354d80(); /* FUN_00354d80 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354da0(); /* FUN_00354da0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00354f1c(); /* FUN_00354f1c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00355018(); /* FUN_00355018 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355418(); /* FUN_00355418 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355674(); /* FUN_00355674 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355754(); /* FUN_00355754 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355884(); /* FUN_00355884 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355a2c(); /* FUN_00355a2c (shared cL4 runtime library, out of scope) */
extern word_t rt_00355a64(); /* FUN_00355a64 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355aa0(); /* FUN_00355aa0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355adc(); /* FUN_00355adc (shared cL4 runtime library, out of scope) */
extern word_t rt_00355bd0(); /* FUN_00355bd0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355bdc(); /* FUN_00355bdc (shared cL4 runtime library, out of scope) */
extern word_t rt_00355bf4(); /* FUN_00355bf4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355c78(); /* FUN_00355c78 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355ca4(); /* FUN_00355ca4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355d78(); /* FUN_00355d78 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355d9c(); /* FUN_00355d9c (shared cL4 runtime library, out of scope) */
extern word_t rt_00355db4(); /* FUN_00355db4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355dc0(); /* FUN_00355dc0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355e50(); /* FUN_00355e50 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355fa0(); /* FUN_00355fa0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00355fac(); /* FUN_00355fac (shared cL4 runtime library, out of scope) */
extern word_t rt_003561a0(); /* FUN_003561a0 (shared cL4 runtime library, out of scope) */
extern word_t rt_003561b8(); /* FUN_003561b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035620c(); /* FUN_0035620c (shared cL4 runtime library, out of scope) */
extern word_t rt_00356278(); /* FUN_00356278 (shared cL4 runtime library, out of scope) */
extern word_t rt_003562d4(); /* FUN_003562d4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00356304(); /* FUN_00356304 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035631c(); /* FUN_0035631c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00356340(); /* FUN_00356340 (shared cL4 runtime library, out of scope) */
extern word_t rt_00356578(); /* FUN_00356578 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035675c(); /* FUN_0035675c (shared cL4 runtime library, out of scope) */
extern word_t rt_0035678c(); /* FUN_0035678c (shared cL4 runtime library, out of scope) */
extern word_t rt_003567bc(); /* FUN_003567bc (shared cL4 runtime library, out of scope) */
extern word_t rt_003567ec(); /* FUN_003567ec (shared cL4 runtime library, out of scope) */
extern word_t rt_003567f8(); /* FUN_003567f8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035694c(); /* FUN_0035694c (shared cL4 runtime library, out of scope) */
extern word_t rt_003569b4(); /* FUN_003569b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003569e4(); /* FUN_003569e4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00356c84(); /* FUN_00356c84 (shared cL4 runtime library, out of scope) */
extern word_t rt_00356e34(); /* FUN_00356e34 (shared cL4 runtime library, out of scope) */
extern word_t rt_00356f44(); /* FUN_00356f44 (shared cL4 runtime library, out of scope) */
extern word_t rt_00356fb8(); /* FUN_00356fb8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00356fcc(); /* FUN_00356fcc (shared cL4 runtime library, out of scope) */
extern word_t rt_00356fd8(); /* FUN_00356fd8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035705c(); /* FUN_0035705c (shared cL4 runtime library, out of scope) */
extern word_t rt_00357338(); /* FUN_00357338 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00357350(); /* FUN_00357350 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035748c(); /* FUN_0035748c (shared cL4 runtime library, out of scope) */
extern word_t rt_003578a8(); /* FUN_003578a8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00357998(); /* FUN_00357998 (shared cL4 runtime library, out of scope) */
extern word_t rt_003579e8(); /* FUN_003579e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00357be0(); /* FUN_00357be0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00357c74(); /* FUN_00357c74 (shared cL4 runtime library, out of scope) */
extern word_t rt_00357cb4(); /* FUN_00357cb4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00357cc8(); /* FUN_00357cc8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00358174(); /* FUN_00358174 (shared cL4 runtime library, out of scope) */
extern word_t rt_003581c4(); /* FUN_003581c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00358374(); /* FUN_00358374 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035847c(); /* FUN_0035847c (shared cL4 runtime library, out of scope) */
extern word_t rt_003584ec(); /* FUN_003584ec (shared cL4 runtime library, out of scope) */
extern word_t rt_00358684(); /* FUN_00358684 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035869c(); /* FUN_0035869c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035881c(); /* FUN_0035881c (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358a74(); /* FUN_00358a74 (shared cL4 runtime library, out of scope) */
extern word_t rt_00358ac8(); /* FUN_00358ac8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00358bd8(); /* FUN_00358bd8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00358c2c(); /* FUN_00358c2c (shared cL4 runtime library, out of scope) */
extern word_t rt_00358c74(); /* FUN_00358c74 (shared cL4 runtime library, out of scope) */
extern word_t rt_00358db8(); /* FUN_00358db8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00358dd0(); /* FUN_00358dd0 (shared cL4 runtime library, out of scope) */
extern word_t rt_00358de8(); /* FUN_00358de8 (shared cL4 runtime library, out of scope) */
extern word_t rt_00358fdc(); /* FUN_00358fdc (shared cL4 runtime library, out of scope) */
extern word_t rt_00359000(); /* FUN_00359000 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035921c(); /* FUN_0035921c (shared cL4 runtime library, out of scope) */
extern word_t rt_0035940c(); /* FUN_0035940c (shared cL4 runtime library, out of scope) */
extern word_t rt_00359478(); /* FUN_00359478 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035949c(); /* FUN_0035949c (shared cL4 runtime library, out of scope) */
extern word_t rt_003594bc(); /* FUN_003594bc (shared cL4 runtime library, out of scope) */
extern word_t rt_00359530(); /* FUN_00359530 (shared cL4 runtime library, out of scope) */
extern word_t rt_00359568(); /* FUN_00359568 (shared cL4 runtime library, out of scope) */
extern word_t rt_00359a60(); /* FUN_00359a60 (shared cL4 runtime library, out of scope) */
extern word_t rt_00359a78(); /* FUN_00359a78 (shared cL4 runtime library, out of scope) */
extern word_t rt_00359b24(); /* FUN_00359b24 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00359c0c(); /* FUN_00359c0c (shared cL4 runtime library, out of scope) */
extern word_t rt_00359e28(); /* FUN_00359e28 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a19c(); /* FUN_0035a19c (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a1b4(); /* FUN_0035a1b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a1e8(); /* FUN_0035a1e8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a2b8(); /* FUN_0035a2b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a2c4(); /* FUN_0035a2c4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a3b8(); /* FUN_0035a3b8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a4ec(); /* FUN_0035a4ec (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a4f8(); /* FUN_0035a4f8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a518(); /* FUN_0035a518 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a5d8(); /* FUN_0035a5d8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a5e4(); /* FUN_0035a5e4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a6b4(); /* FUN_0035a6b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035a9c8(); /* FUN_0035a9c8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035aa90(); /* FUN_0035aa90 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0035abd8(); /* FUN_0035abd8 (shared cL4 runtime library, out of scope) */
extern word_t rt_0035ac70(); /* FUN_0035ac70 (shared cL4 runtime library, out of scope) */
extern word_t rt_00361528(); /* FUN_00361528 (shared cL4 runtime library, out of scope) */
extern word_t rt_003625e4(); /* FUN_003625e4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003629b4(); /* FUN_003629b4 (shared cL4 runtime library, out of scope) */
extern word_t rt_00365b6c(); /* FUN_00365b6c (shared cL4 runtime library, out of scope) */
extern word_t rt_0036a908(); /* FUN_0036a908 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_0036b118(); /* FUN_0036b118 (shared cL4 runtime library, out of scope) */
extern word_t rt_0036b270(); /* FUN_0036b270 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003722e4(); /* FUN_003722e4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00376820(); /* FUN_00376820 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_00377824(); /* FUN_00377824 (shared cL4 runtime library, out of scope) */
extern word_t rt_00377bec(); /* FUN_00377bec (shared cL4 runtime library, out of scope) */
extern word_t rt_00377dcc(); /* FUN_00377dcc (shared cL4 runtime library, out of scope) */
extern word_t rt_003a0b04(); /* FUN_003a0b04 (shared cL4 runtime library, out of scope) */
extern sk_u128_t rt_003a25d4(); /* FUN_003a25d4 (shared cL4 runtime library, out of scope) */
extern word_t rt_003a261c(); /* FUN_003a261c (shared cL4 runtime library, out of scope) */

/* ---- opaque kernel data globals referenced by this slice ---- */
extern word_t g_0000fc9d; /* DAT/LAB_0000fc9d */
extern word_t g_002039f4; /* DAT/LAB_002039f4 */
extern word_t g_003471a4; /* DAT/LAB_003471a4 */
extern word_t g_003471a8; /* DAT/LAB_003471a8 */
extern word_t g_004e9518; /* DAT/LAB_004e9518 */
extern word_t g_004e9550; /* DAT/LAB_004e9550 */
extern word_t g_004e956c; /* DAT/LAB_004e956c */
extern word_t g_004e9634; /* DAT/LAB_004e9634 */
extern word_t g_005d021c; /* DAT/LAB_005d021c */
extern word_t g_005d3bbc; /* DAT/LAB_005d3bbc */
extern word_t g_005d3bc0; /* DAT/LAB_005d3bc0 */
extern word_t g_005d3bdd; /* DAT/LAB_005d3bdd */
extern word_t g_005d3be0; /* DAT/LAB_005d3be0 */
extern word_t g_005d3be4; /* DAT/LAB_005d3be4 */
extern word_t g_0060e208; /* DAT/LAB_0060e208 */
extern word_t g_0060e218; /* DAT/LAB_0060e218 */
extern word_t g_0060e230; /* DAT/LAB_0060e230 */
extern word_t g_00611b24; /* DAT/LAB_00611b24 */
extern word_t g_00611b34; /* DAT/LAB_00611b34 */
extern word_t g_00611b3c; /* DAT/LAB_00611b3c */
extern sk_fnptr g_00658c00; /* DAT_00658c00: primary runtime dispatch entry */
extern word_t g_tls_magic; /* __thread_bss.magic: TLS sentinel compared by the description layer */

/* ---- diagnostic/format strings (Swift-style reflection layer) ---- */
extern char sk_str_1_element[];
extern char sk_str_1_key_value_pair[];
extern char sk_str_1_member[];
extern char sk_str_Fatal_error[];
extern char sk_str_Index_out_of_bounds[];
extern char sk_str_Method_must_be_overridden[];
extern char sk_str_Swift_EnumeratedSequence_swift[];
extern char sk_str__1_element_[];
extern char sk_str_child_[];
extern char sk_str_children_[];
extern char sk_str_elements[];
extern char sk_str_elements_[];
extern char sk_str_key_value_pairs[];
extern char sk_str_members[];
extern char sk_str_offset_element[];
extern char sk_str_super_[];

/* ---- decompiler stack-slot artifacts (word-sized placeholders) ---- */
static word_t sk_stack_00000000;
static word_t sk_stack_00000010;
static word_t sk_stack_00000020;
static word_t sk_stack_00000030;
static word_t sk_stack_00000038;
static word_t sk_stack_00000040;
static word_t sk_stack_00000048;
static word_t sk_stack_ffffffffffffffa0;
static word_t sk_stack_ffffffffffffffb0;
static word_t sk_stack_ffffffffffffffc0;
static word_t sk_stack_ffffffffffffffd0;
static word_t sk_stack_ffffffffffffffd8;

/* ---- in-slice forward declarations (unspecified params; see header note) ---- */
void sk_object_describe_root();
word_t sk_dump_check();
void sk_dump_finish();
void sk_object_handle();
uint32_t sk_object_has_refs();
word_t sk_cleanup_thunk();
void sk_common_cleanup();
void sk_error_panic();
void sk_retain_increment();
void sk_vspace_walk();
void sk_dispatch_jump();
void sk_lookup_install();
void sk_lookup_install2();
void sk_map_region_core();
word_t * sk_node_alloc();
sk_u128_t sk_node_init();
void sk_unmap_region();
void sk_node_config();
void sk_node_release();
void sk_node_alloc4();
void sk_sub_release();
void sk_sub_alloc();
word_t sk_sub_init();
void sk_iterate_children();
void sk_iterate_walk();
void sk_find_child();
word_t * sk_node_alloc2();
sk_u128_t sk_node_init2();
void sk_find_slot();
void sk_rec_descend();
void sk_desc_node();
void sk_desc_dispatch();
void sk_desc_elements();
void sk_desc_sub();
void sk_desc_children();
void sk_desc_slot();
void sk_desc_recurse();
void sk_vt_overridden_a();
void sk_vt_overridden_b();
void sk_vt_overridden_c();
void sk_vt_overridden_d();
void sk_vt_overridden_e();
void sk_vt_overridden_f();
void sk_assert_fmt_a();
void sk_assert_fmt_b();
void sk_assert_fail();
void sk_assert_fail2();
sk_u128_t sk_assert_empty();
void sk_assert_empty2();
word_t sk_assert_both();
void sk_assert_ze_pair();
void sk_assert_ze_pair2();
sk_fnptr * sk_pair_store();
void sk_pair_check_a();
void sk_pair_check_b();
word_t sk_assert_nz_pair();
sk_u128_t sk_assert_nz_triple();
word_t sk_assert_eq_case();
void sk_assert_pair_eq();
void sk_node_validate();
void sk_assert_pairs_eq();
void sk_assert_empty3();
void sk_assert_empty4();
void sk_pair_check_c();
sk_fnptr * sk_pair_store2();
void sk_pair_check_d();
void sk_pair_check_e();
void sk_assert_fmt_c();
void sk_assert_clear_a();
void sk_assert_clear_b();
void sk_assert_clear_c();
word_t sk_assert_clear_d();
word_t sk_assert_clear_e();
word_t * sk_pair_alloc();
void sk_assert_fmt_d();
void sk_slot_clear_a();
void sk_slot_clear_b();
void sk_table_iter();
void sk_table_method();
word_t sk_table_lookup();
word_t sk_table_range();
void sk_table_insert1();
void sk_table_insert_n();
void sk_table_update();
word_t sk_index_lookup();
void sk_index_clear_a();
void sk_index_clear_b();
void sk_index_clear_c();
sk_u128_t sk_table_alloc();
void sk_table_free();
sk_u128_t sk_table_alloc_node();
void sk_table_free_node();
uint32_t sk_index_test();
uint32_t sk_index_test2();
void sk_index_decr();
void sk_index_decr2();
void sk_rt_wrap_a();
void sk_rt_wrap_b();
void sk_rt_wrap_c();
void sk_boot_cold();
void sk_boot_cpu();
void sk_dispatch_mux();
void sk_abstract_method();
void sk_vt_init();
void sk_vt_install();
void sk_vt_setup();
void sk_vt_teardown();
void sk_vt_call();
void sk_vt_abstract_a();
void sk_vt_abstract_b();
void sk_vt_hook_a();
void sk_vt_hook_b();
void sk_vt_hook_c();
void sk_vt_hook_d();
void sk_vt_hook_e();
void sk_dtor_pure_a();
void sk_dtor_pure_b();
void sk_dtor_pure_c();
void sk_dtor_pure_d();
void sk_dtor_pure_e();
void sk_dtor_pure_f();

/* FUN_00200150 @ 0x00200150   (est. sk_object_describe_root)
 * Ghidra: void FUN_00200150(void)
 * Entry point of the object-description engine. Performs the standard runtime prologue (save thread context via rt_0008e518, resolve object fields), then drives two sub-walkers (sk_dump_check, sk_dump_finish) and the table iterator; the else path is an unrecoverable panic. Faithful mechanical transcription of the decompiler output.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_object_describe_root(void)
{

  int iVar1;
  word_t lVar2;
  word_t uVar3;
  word_t uVar4;
  word_t uVar5;
  word_t lVar6;
  word_t lVar7;
  word_t lVar8;
  word_t uVar9;
  word_t uVar10;
  word_t extraout_x1;
  word_t extraout_x1_00;
  word_t extraout_x8;
  word_t extraout_x8_00;
  word_t extraout_x8_01;
  word_t extraout_x8_02;
  word_t extraout_x8_03;
  word_t extraout_x8_04;
  word_t extraout_x8_05;
  word_t extraout_x8_06;
  sk_fnptr extraout_x8_07;
  sk_fnptr extraout_x8_08;
  sk_fnptr extraout_x8_09;
  sk_fnptr extraout_x8_10;
  sk_fnptr extraout_x8_11;
  sk_fnptr extraout_x8_12;
  sk_fnptr extraout_x8_13;
  sk_fnptr extraout_x8_14;
  sk_fnptr extraout_x9;
  sk_fnptr extraout_x9_00;
  sk_fnptr extraout_x9_01;
  sk_fnptr extraout_x9_02;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t extraout_x16_01;
  word_t uVar11;
  sk_fnptr pcVar12;
  word_t uVar13;
  sk_fnptr pcVar14;
  word_t unaff_x23;
  word_t unaff_x25;
  word_t unaff_x30;
  sk_u128_t auVar15;
  word_t local_98;
  word_t local_88;
  word_t local_80;
  word_t local_70;
  word_t local_68;
  word_t local_58;
  word_t local_20;
  
  lVar2 = rt_0008e518().lo;
  rt_00352b98();
  uVar11 = *(word_t *)(extraout_x1 + 0x10);
  rt_003494e8();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_003497b4();
  uVar13 = *(word_t *)(extraout_x1_00 + 0x18);
  rt_0034c60c();
  uVar3 = rt_00377824().lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034f3d4();
  rt_0035056c(0xff);
  uVar4 = rt_00377824().lo;
  uVar5 = rt_0034b0b4();
  lVar6 = rt_003722e4(uVar5,uVar4,uVar4).lo;
  rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
  rt_003493c4();
  rt_0034d234();
  (*g_00658c00)();
  rt_0034d7fc();
  rt_0034a5c8();
  (*g_00658c00)(*(word_t *)(extraout_x8_02 + 0x40));
  rt_003493c4();
  rt_0034cde8();
  (*g_00658c00)();
  rt_0034a9e8();
  (*g_00658c00)();
  rt_0034aadc();
  (*g_00658c00)();
  rt_00350464();
  rt_0034f604();
  lVar7 = rt_0031b704();
  rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8_04 + 0x40));
  rt_00348abc();
  (*g_00658c00)();
  rt_0034b758();
  rt_00350b9c(uVar13);
  uVar5 = rt_00377bec();
  auVar15 = rt_003508e4();
  lVar8 = rt_00310e08(auVar15.lo,auVar15.hi,uVar5);
  rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8_05 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*g_00658c00)();
  rt_0034ac3c();
  pcVar12 = *(sk_fnptr *)(extraout_x16_01 + 0x10);
  rt_0034c694();
  (*pcVar12)();
  pcVar14 = *(sk_fnptr *)(extraout_x16_00 + 0x20);
  (*pcVar14)(extraout_x8_03,unaff_x23 + *(int32_t *)(lVar7 + 0x24),uVar4);
  uVar9 = rt_0034b0e4();
  uVar9 = rt_00355d78(uVar9,lVar7);
  rt_003579e8(uVar9,lVar2 + extraout_x8_06);
  (*pcVar12)();
  (*pcVar14)(local_98,unaff_x25 + *(int32_t *)(lVar7 + 0x24),uVar4);
  rt_0035166c(uVar5);
  rt_00350524();
  rt_00351f4c();
  uVar10 = (*extraout_x8_07)();
  if ((uVar10 & 1) != 0) {
    rt_0034ff88();
    (*pcVar14)();
    rt_00350b9c(local_68 + *(int32_t *)(lVar6 + 0x30));
    (*pcVar14)();
    rt_00353a00();
    auVar15 = rt_00350494();
    (*extraout_x9)(auVar15.lo,auVar15.hi,lVar6);
    iVar1 = *(int32_t *)(lVar6 + 0x30);
    rt_00351bd4(local_20);
    (*pcVar14)();
    pcVar12 = *(sk_fnptr *)(extraout_x16_00 + 8);
    (*pcVar12)(local_88 + iVar1,uVar4);
    auVar15 = rt_00350494(*(word_t *)(extraout_x16 + 0x20));
    rt_00353b70(auVar15.lo,auVar15.hi,lVar6);
    (*extraout_x8_08)();
    (*pcVar14)(local_20 + *(int32_t *)(lVar8 + 0x24),local_88 + *(int32_t *)(lVar6 + 0x30),uVar4);
    rt_00351130();
    (*pcVar12)();
    rt_0026c274(extraout_x8_00,extraout_x1_00);
    rt_00352eb4(uVar13);
    rt_00350810(local_58,local_20);
    (*extraout_x9_00)();
    rt_00354afc();
    rt_0035060c();
    (*extraout_x8_09)();
    rt_0034de8c();
    auVar15 = rt_00350524();
    rt_00377bec(auVar15.lo,auVar15.hi,uVar3);
    rt_0035156c();
    rt_00350524(local_80);
    (*extraout_x9_01)();
    rt_00350704();
    rt_00350524(local_70);
    (*extraout_x9_02)();
    rt_0034f014();
    rt_00350494();
    rt_003518a0();
    uVar10 = (*extraout_x8_10)();
    if ((uVar10 & 1) != 0) {
      rt_0035460c();
      rt_00350bc0(&sk_stack_00000040);
      (*extraout_x8_11)(local_58,uVar3);
      rt_00350bc0(&sk_stack_00000030);
      (*extraout_x8_12)(local_20,lVar8);
      (*pcVar14)(local_68,local_80,uVar4);
      uVar3 = rt_00359e28();
      (*pcVar14)(uVar3,local_70,uVar4);
      rt_003511c0(local_88);
      rt_00353130();
      (*extraout_x8_13)();
      iVar1 = *(int32_t *)(lVar6 + 0x30);
      rt_00359a78();
      auVar15 = rt_003507bc();
      (*pcVar14)(auVar15.lo,auVar15.hi,uVar4);
      (*pcVar12)(local_88 + iVar1,uVar4);
      rt_003511c0(local_88);
      rt_000ec044();
      (*extraout_x8_14)();
      (*pcVar14)(((word_t)(extraout_x16_00 + 0x20) & 0xffffffffffff | 0x48d8000000000000) +
                 (word_t)*(int32_t *)(lVar8 + 0x24),local_88 + *(int32_t *)(lVar6 + 0x30),uVar4);
      rt_003514d0();
      (*pcVar12)();
      rt_0035aa90((word_t)*(int32_t *)(extraout_x1_00 + 0x24));
      auVar15 = rt_003516e4();
      uVar3 = sk_dump_check(auVar15.lo,auVar15.hi,uVar5);
      rt_0035116c();
      sk_dump_finish();
      rt_0036b118(uVar3);
      rt_00353190();
      rt_0026c274();
      rt_00353734();
      auVar15 = rt_00084180();
      rt_001fccf8(auVar15.lo,auVar15.hi,uVar11,uVar13);
      rt_0008e500(unaff_x30);
      return;
    }
  }
  rt_00347d60();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_002007c0 @ 0x002007c0   (est. sk_dump_check)
 * Ghidra: word_t FUN_002007c0()
 * Object-description helper: runs a runtime branch check (rt_001e3048 bit 0); on the taken path performs the finish sequence and returns, else falls into the alternate teardown. Wraps shared-runtime calls.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_dump_check()
{

  word_t uVar1;
  word_t extraout_x16;
  
  rt_0034c034();
  rt_00310e08(0);
  uVar1 = rt_001e3048();
  if ((uVar1 & 1) != 0) {
    rt_0034b804();
    (**(sk_fnptr *)(extraout_x16 + 8))();
    rt_00084180();
    rt_0027743c();
    return 0;
  }
  rt_0034ef68();
  rt_00277474();
  return 0;
}

/* FUN_0020083c @ 0x0020083c   (est. sk_dump_finish)
 * Ghidra: void FUN_0020083c(void)
 * Small object-description finalizer: calls the vector-table teardown (rt_0027a6e0), a runtime release and an object refcount drop.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_dump_finish(void)
{

  rt_0027a6e0();
  rt_00351d18();
  rt_0036b118();
  return;
}

/* FUN_0020086c @ 0x0020086c   (est. sk_object_handle)
 * Ghidra: void FUN_0020086c(void)
 * Object-handling routine: loads an object slot (offset 0x18), retains it, builds a 4-word frame, walks it, then releases. Ends on an event predicate.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_object_handle(void)
{

  int iVar1;
  word_t uVar2;
  word_t uVar3;
  word_t uVar4;
  word_t uVar5;
  word_t lVar6;
  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x8_01;
  sk_fnptr extraout_x8_02;
  sk_fnptr extraout_x8_03;
  sk_fnptr extraout_x8_04;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t unaff_x20;
  word_t uVar7;
  word_t unaff_x27;
  word_t unaff_x28;
  word_t unaff_x30;
  sk_u128_t auVar8;
  sk_u128_t auStack_40;
  word_t local_30;
  word_t uStack_28;
  word_t local_20;
  word_t local_10;
  
  auVar8 = rt_0008e518();
  lVar6 = auVar8.hi;
  uVar4 = *(word_t *)(lVar6 + 0x18);
  uVar3 = *(word_t *)(lVar6 + 0x10);
  rt_0034c54c();
  rt_0034b7b8();
  rt_00377824();
  rt_00348d7c();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034aa9c();
  rt_000e15d8();
  rt_00351de4();
  uVar2 = rt_00377bec();
  rt_0034d404();
  rt_00310e08();
  rt_00348fd8();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034b0d4();
  uVar7 = *(word_t *)(unaff_x20 + *(int32_t *)(lVar6 + 0x24));
  rt_0036b270(uVar7);
  local_30 = uVar3;
  uStack_28 = uVar4;
  local_20 = auVar8.lo;
  local_10 = uVar7;
  rt_0034d404();
  uVar3 = rt_0031b71c();
  uVar4 = rt_00348c30();
  rt_00376820(uVar4,uVar3);
  uVar3 = rt_0035a4ec();
  rt_00355ca4(uVar3,auStack_40);
  rt_001db6b0();
  rt_0036b118(uVar7);
  rt_0036b270(uVar7);
  rt_0034f514();
  rt_00351cd0();
  rt_001fea40();
  rt_0036b118(uVar7);
  rt_0035166c(uVar2);
  rt_00350a34();
  rt_00351c94();
  uVar5 = (*extraout_x8_00)();
  if ((uVar5 & 1) == 0) {
    rt_00350944(*(word_t *)(extraout_x16_00 + 8));
    (*extraout_x8_04)();
  }
  else {
    iVar1 = *(int32_t *)(unaff_x28 + 0x24);
    rt_0035044c(uVar2);
    rt_00351c94(auVar8.lo,unaff_x27 + iVar1);
    uVar5 = (*extraout_x8_01)();
    rt_00350944(*(word_t *)(extraout_x16_00 + 8));
    (*extraout_x8_02)();
    if ((uVar5 & 1) != 0) {
      rt_0035072c(*(word_t *)(extraout_x16 + 0x10));
      (*extraout_x8_03)();
      rt_0034ca28(extraout_x8);
      rt_001fd4f4();
    }
  }
  rt_0034f5e4();
  rt_0031b704();
  auVar8 = rt_0007c1c4();
  rt_000839d8(auVar8.lo,auVar8.hi,1);
  rt_0008e500(unaff_x30);
  return;
}

/* FUN_00200abc @ 0x00200abc   (est. sk_object_has_refs)
 * Ghidra: uint32_t FUN_00200abc(void)
 * Boolean predicate returning (rt_0 branch & 1): tests a runtime condition, on success loads field 0x18 and returns the branch result, else 0. Likely a "has refs"/"is busy" test.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
uint32_t sk_object_has_refs(void)
{

  word_t uVar1;
  uint32_t uVar2;
  word_t uVar3;
  word_t extraout_x1;
  sk_fnptr extraout_x8;
  sk_fnptr extraout_x8_00;
  
  rt_00354708();
  uVar1 = *(word_t *)(extraout_x1 + 0x18);
  rt_0034f014();
  rt_0034aebc();
  uVar3 = (*extraout_x8)();
  if ((uVar3 & 1) == 0) {
    uVar2 = 0;
  }
  else {
    rt_0035044c(uVar1);
    rt_0035053c();
    uVar2 = (*extraout_x8_00)();
    uVar2 = uVar2 & 1;
  }
  return uVar2;
}

/* FUN_00200b34 @ 0x00200b34   (est. sk_cleanup_thunk)
 * Ghidra: void thunk_FUN_00200b38(void)
 * Thunk for sk_common_cleanup (FUN_00200b38): runtime dispatch preamble + cleanup branch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void thunk_FUN_00200b38(void)
{

  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x9;
  word_t extraout_x16;
  
  rt_00352800();
  rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_00349178();
  rt_00351e84();
  rt_00351c88();
  (*extraout_x9)();
  rt_0035056c(*(word_t *)(extraout_x16 + 0x20));
  (*extraout_x8_00)();
  return;
}

/* FUN_00200b38 @ 0x00200b38   (est. sk_common_cleanup)
 * Ghidra: void FUN_00200b38()
 * Common cleanup/teardown: dispatches through g_00658c00 then runs the standard cleanup sequence.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_common_cleanup()
{

  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x9;
  word_t extraout_x16;
  
  rt_00352800();
  rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_00349178();
  rt_00351e84();
  rt_00351c88();
  (*extraout_x9)();
  rt_0035056c(*(word_t *)(extraout_x16 + 0x20));
  (*extraout_x8_00)();
  return;
}

/* FUN_00200bd0 @ 0x00200bd0   (est. sk_error_panic)
 * Ghidra: void FUN_00200bd0(word_t param_1)
 * Registers an error/panic descriptor: calls rt_00262b5c with three metadata addresses (g_00611b24, g_00611b3c) and the return site 0x206bbc. Likely a failed-assertion/abort registrar.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_error_panic(word_t param_1)
{

  rt_00262b5c(param_1,&g_00611b24,&g_00611b3c,0x206bbc);
  return;
}

/* FUN_00200bf4 @ 0x00200bf4   (est. sk_retain_increment)
 * Ghidra: void FUN_00200bf4(word_t param_1,word_t param_2,word_t param_3)
 * Retain/increment helper: resolves an object, and under a runtime branch either performs a setup+dispatch or increments a slot counter (offset via g field), trapping (SoftwareBreakpoint) on carry overflow.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_retain_increment(word_t param_1,word_t param_2,word_t param_3)
{

  int iVar1;
  uint8_t in_ZR;
  word_t uVar2;
  sk_fnptr pcVar3;
  word_t uVar4;
  word_t lVar5;
  word_t *extraout_x8;
  sk_fnptr extraout_x8_00;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t unaff_x20;
  word_t lVar6;
  sk_u128_t auVar7;
  sk_u128_t auVar8;
  
  auVar7 = rt_0008e518();
  uVar2 = *(word_t *)(auVar7.lo + 0x18);
  rt_00351fb0();
  rt_00351238(0xff,uVar2);
  rt_00377824();
  rt_0034e130();
  rt_00310d68();
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034aee4();
  rt_00349734();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034b0d4();
  rt_00351238(0xff,uVar2);
  rt_00377824();
  rt_00350288(uVar2);
  uVar2 = rt_00377bec();
  pcVar3 = (sk_fnptr)rt_000a68f4();
  rt_00350488();
  uVar4 = rt_00377dcc();
  (*pcVar3)(uVar4,uVar2);
  rt_0034aa54();
  if ((bool)in_ZR) {
    rt_00358de8(*(word_t *)(extraout_x16 + 8));
    (*extraout_x8_00)();
    rt_0035041c();
    rt_003594bc();
    rt_003512f4();
    auVar8 = rt_003722e4();
    rt_00350744(extraout_x8,auVar8.hi,param_3,auVar8.lo);
  }
  else {
    pcVar3 = *(sk_fnptr *)(extraout_x16_00 + 0x20);
    rt_00350048();
    (*pcVar3)();
    rt_0035041c();
    rt_003594bc();
    rt_003512f4();
    lVar5 = rt_003722e4().lo;
    iVar1 = *(int32_t *)(lVar5 + 0x30);
    lVar5 = (word_t)*(int32_t *)(auVar7.lo + 0x24);
    lVar6 = *(word_t *)(unaff_x20 + lVar5);
    *extraout_x8 = lVar6;
    rt_003514a0((word_t)extraout_x8 + (word_t)iVar1);
    (*pcVar3)();
    if (SCARRY8(lVar6,1)) {
                    /* WARNING: Does not return */
      pcVar3 = (sk_fnptr)SoftwareBreakpoint(1,0x200dc8);
      (*pcVar3)();
    }
    *(word_t *)(unaff_x20 + lVar5) = lVar6 + 1;
    rt_0034bc94(extraout_x8);
  }
  rt_000839d8();
  rt_0008e500(auVar7.hi);
  return;
}

/* FUN_00200dc8 @ 0x00200dc8   (est. sk_vspace_walk)
 * Ghidra: void FUN_00200dc8(void)
 * Table walker: iterates a collection via rt_0035881c/rt_00350b00, tests each entry with sk_index_test (00207ca0), on miss performs lookup (sk_index_decr 00207e0c + sk_index_lookup 002075e0) and stores to a slot; recursion and release paths. Ends in a conditional return or panic.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vspace_walk(void)
{

  bool bVar1;
  word_t uVar2;
  int iVar3;
  bool bVar4;
  uint8_t in_ZR;
  word_t uVar5;
  word_t uVar6;
  word_t lVar7;
  word_t uVar8;
  word_t uVar9;
  word_t uVar10;
  word_t uVar11;
  word_t uVar12;
  word_t uVar13;
  word_t uVar14;
  word_t lVar15;
  word_t extraout_x1;
  word_t uVar16;
  word_t extraout_x8;
  word_t extraout_x8_00;
  word_t extraout_x8_01;
  word_t extraout_x8_02;
  sk_fnptr extraout_x8_03;
  sk_fnptr extraout_x8_04;
  sk_fnptr extraout_x8_05;
  sk_fnptr extraout_x8_06;
  sk_fnptr extraout_x8_07;
  sk_fnptr extraout_x8_08;
  sk_fnptr extraout_x9;
  sk_fnptr extraout_x9_00;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t extraout_x16_01;
  sk_fnptr pcVar17;
  word_t *unaff_x23;
  word_t *unaff_x25;
  word_t *unaff_x26;
  word_t unaff_x30;
  sk_u128_t auVar18;
  sk_u128_t auVar19;
  word_t local_140;
  word_t local_118;
  word_t local_e8;
  word_t local_c8;
  word_t local_b0;
  word_t local_a8;
  word_t local_80;
  word_t local_40;
  word_t uStack_38;
  word_t local_30;
  uint8_t auStack_28[8];
  word_t local_20;
  word_t uStack_18;
  word_t local_10;
  uint8_t auStack_8[8];
  
  auVar18 = rt_0008e518();
  lVar15 = auVar18.hi;
  rt_00355db4();
  uVar16 = *(word_t *)(extraout_x1 + 0x10);
  uVar2 = *(word_t *)(extraout_x1 + 0x18);
  rt_0034c108();
  rt_00077894();
  rt_00377824();
  rt_00348d4c();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_00350428();
  rt_003509a4();
  rt_0034d424();
  uVar5 = rt_00377824().lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034d89c();
  rt_00310d68(0xff);
  rt_0034e67c();
  rt_00310d68();
  rt_003490b8(auStack_28);
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034b0d4();
  rt_0034a5c8();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*g_00658c00)();
  rt_00350464();
  rt_003509a4();
  rt_0034f534();
  uVar6 = rt_00377bec();
  auVar19 = rt_0035050c();
  uVar6 = rt_00310e08(auVar19.lo,auVar19.hi,uVar6);
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_00350428();
  rt_00355fac();
  rt_0035041c();
  rt_003594bc();
  lVar7 = rt_003722e4(0).lo;
  rt_0034ab20();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034d888();
  rt_00350530();
  uVar8 = rt_00310d68();
  rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
  rt_00348bbc();
  (*g_00658c00)();
  rt_0034b3d8();
  rt_0035aa90((word_t)*(int32_t *)(lVar15 + 0x24));
  local_40 = lVar15;
  rt_0035678c(0);
  rt_0035139c();
  uVar9 = rt_0031b71c();
  sk_common_cleanup(auStack_28);
  auVar19 = rt_0036b118(lVar15);
  rt_00350488(auVar19.lo,auVar19.hi,0x66d5d8);
  uVar10 = rt_0031b760();
  uVar11 = rt_00348a50();
  uVar11 = rt_00376820(uVar11,uVar9).lo;
  local_30 = uVar11;
  rt_00376820(&g_004e9634,uVar10,&local_30);
  rt_0034dae8();
  (**(sk_fnptr *)(extraout_x16_01 + 0x20))(&local_40,auStack_28,uVar10);
  local_10 = local_40;
  uVar12 = rt_00348c30();
  auVar19 = rt_00376820(uVar12,uVar9);
  uVar12 = auVar19.lo;
  rt_00350b00(&local_20,uVar12,auVar19.hi,rt_00310924);
  sk_table_iter();
  rt_00352b98(extraout_x16_00 + 8);
  rt_00353718();
  rt_00352554(extraout_x8_01 + 8);
  rt_00353bac();
  rt_00355dc0(extraout_x8_02 + 8);
  rt_00352bbc();
  bVar4 = true;
  auVar19 = rt_0035881c();
  while( true ) {
    rt_00350b00(&local_40,auVar19.lo,auVar19.hi,rt_000277b8);
    sk_table_iter();
    uVar13 = sk_index_test((word_t)(&local_20),(word_t)(&local_40),(word_t)(uVar9),(word_t)(uVar12));
    bVar1 = (uVar13 & 1) != 0;
    if (!bVar1) {
      uStack_38 = uStack_18;
      local_40 = local_20;
      sk_index_decr((word_t)(&local_20),(word_t)(&local_40),(word_t)(uVar10),(word_t)(uVar11));
      iVar3 = *(int32_t *)(lVar7 + 0x30);
      uVar14 = sk_index_lookup((word_t)(local_80 + iVar3),(word_t)(&local_20),(word_t)(uVar10),(word_t)(uVar12));
      *unaff_x23 = uVar14;
      (**(sk_fnptr *)(extraout_x16_00 + 0x20))
                ((word_t)unaff_x23 + (word_t)*(int32_t *)(lVar7 + 0x30),local_80 + iVar3,uVar6);
    }
    rt_00351548(unaff_x23,bVar1);
    rt_000839d8();
    rt_0035457c();
    auVar19 = rt_00351274();
    (*extraout_x8_03)(auVar19.lo,auVar19.hi,uVar8);
    rt_0034aa54(unaff_x25);
    if ((bool)in_ZR) break;
    rt_00354570(*unaff_x25);
    (**(sk_fnptr *)(extraout_x16_00 + 0x20))
              (local_b0,(word_t)unaff_x25 + (word_t)*(int32_t *)(lVar7 + 0x30),uVar6);
    rt_00352eb4(uVar2);
    rt_00350b9c(local_a8,local_b0);
    (*extraout_x9)();
    rt_0034d688();
    rt_003510dc();
    (*extraout_x8_04)();
    rt_0034de8c();
    auVar19 = rt_003505e8();
    rt_00377bec(auVar19.lo,auVar19.hi,uVar5);
    rt_0031b110();
    rt_0035102c();
    rt_00350b9c(auVar18.lo);
    (*extraout_x9_00)();
    uVar14 = rt_0034f9ec(&sk_stack_00000040);
    (*extraout_x8_05)(uVar14,uVar5);
    rt_0034b2a8();
    unaff_x23 = unaff_x26;
    if ((bool)in_ZR) {
      rt_003510d0(&local_30);
      rt_00357be0();
      (*extraout_x8_07)();
      bVar4 = false;
      rt_0035675c();
      auVar19 = rt_00357350();
      lVar7 = local_a8;
    }
    else {
      rt_00354bb0();
      pcVar17 = (sk_fnptr)*unaff_x26;
      auVar19 = rt_003510ac();
      (*pcVar17)(auVar19.lo,auVar19.hi,unaff_x26);
      auVar19 = rt_00084180();
      (*pcVar17)(auVar19.lo,auVar19.hi,unaff_x26);
      auVar19 = rt_003524b0();
      rt_00350884(auVar19.lo,auVar19.hi,local_c8);
      if (!(bool)in_ZR) {
        rt_00358ac8();
        rt_0036b118();
        rt_0035748c(&uStack_38);
        auVar19 = rt_003507e0();
        (*extraout_x8_08)(auVar19.lo,auVar19.hi,local_c8);
        rt_00357338(&uStack_18);
        rt_0035063c(extraout_x16,local_140);
        rt_001fd4f4();
        rt_0034bec4();
        rt_0031b704();
        rt_00352c68();
L_002014d4:
        rt_00350774();
        rt_000839d8();
        rt_003504e8();
        rt_00356e34();
        auVar19 = rt_00352c68();
        uVar16 = auVar19.hi;
        local_118 = auVar19.lo;
L_0020150c:
        rt_000839d8(local_118,uVar16,1);
        rt_0008e500(unaff_x30);
        return;
      }
      uVar14 = rt_0034f9ec(auStack_8);
      (*extraout_x8_06)(uVar14,unaff_x26);
      rt_0035675c();
      auVar19 = rt_00357350();
      lVar7 = local_e8;
    }
  }
  rt_00358ac8();
  rt_0036b118();
  if (!bVar4) {
    rt_0031b704(0xff,uVar16,uVar2);
    rt_00352efc();
    rt_00356e34();
    uVar16 = 1;
    goto L_0020150c;
  }
  rt_0031b704(0,uVar16,uVar2);
  rt_00351d24();
  goto L_002014d4;
}

/* FUN_0020152c @ 0x0020152c   (est. sk_dispatch_jump)
 * Ghidra: void FUN_0020152c(void)
 * Dispatch jump: resolves a vtable slot (offset 0x10), calls through it, then falls into an unrecovered jumptable (indirect call) — decompiler artifact.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_dispatch_jump(void)
{

  word_t lVar1;
  sk_fnptr pcVar2;
  word_t extraout_x8;
  word_t unaff_x19;
  word_t unaff_x21;
  sk_fnptr UNRECOVERED_JUMPTABLE;
  
  rt_00357cb4();
  lVar1 = rt_00351cc4();
  UNRECOVERED_JUMPTABLE = *(sk_fnptr *)(lVar1 + 0x10);
  rt_003499f0();
  (**(sk_fnptr *)(extraout_x8 + 0x10))();
  rt_003514b8(*(word_t *)(unaff_x19 + 0x18));
  pcVar2 = (sk_fnptr)rt_00310924();
  rt_0034c60c();
  lVar1 = rt_0031b858();
  rt_000e15d8(unaff_x21 + *(int32_t *)(lVar1 + 0x24));
  (*pcVar2)();
  rt_0035631c();
  rt_00350af4();
  rt_00357c74();
                    /* WARNING: Could not recover jumptable at 0x002015d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

/* FUN_00201788 @ 0x00201788   (est. sk_lookup_install)
 * Ghidra: void FUN_00201788(word_t param_1,word_t param_2,word_t param_3)
 * Lookup-and-install: resolves an object range, walks via rt_0031b2ec, validates a slot within bounds; on range match records the node; else panics with error codes 0x108/0x10a/0x10c. Returns via the standard epilogue or noreturn panic.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_lookup_install(word_t param_1,word_t param_2,word_t param_3)
{

  word_t uVar1;
  int iVar2;
  int iVar3;
  word_t *plVar4;
  word_t uVar5;
  word_t uVar6;
  word_t lVar7;
  word_t lVar8;
  word_t uVar9;
  word_t lVar10;
  word_t uVar11;
  word_t *plVar12;
  word_t extraout_x8;
  word_t extraout_x8_00;
  word_t extraout_x8_01;
  word_t extraout_x8_02;
  sk_fnptr extraout_x8_03;
  sk_fnptr extraout_x8_04;
  word_t uVar13;
  sk_fnptr extraout_x8_05;
  sk_fnptr extraout_x8_06;
  sk_fnptr extraout_x8_07;
  sk_fnptr extraout_x8_08;
  sk_fnptr extraout_x8_09;
  sk_fnptr extraout_x8_10;
  sk_fnptr extraout_x8_11;
  sk_fnptr extraout_x9;
  sk_fnptr extraout_x9_00;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t extraout_x16_01;
  word_t extraout_x16_02;
  word_t unaff_x19;
  word_t unaff_x20;
  sk_fnptr pcVar14;
  word_t lVar15;
  word_t lVar16;
  sk_fnptr pcVar17;
  word_t unaff_x28;
  word_t unaff_x30;
  sk_u128_t auVar18;
  word_t local_b8;
  word_t *local_a0;
  word_t local_60;
  word_t lStack_50;
  word_t local_18;
  
  auVar18 = rt_0008e518();
  plVar12 = (word_t *)auVar18.hi;
  plVar4 = (word_t *)auVar18.lo;
  uVar13 = *(word_t *)(param_3 + 0x10);
  uVar1 = *(word_t *)(param_3 + 0x18);
  rt_0034d598();
  rt_003510f4(0xff);
  uVar5 = rt_00377824().lo;
  uVar6 = rt_0034b0b4();
  lVar7 = rt_003722e4(uVar6,uVar5,uVar5).lo;
  rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_00348b5c();
  (*g_00658c00)();
  rt_0034bc6c();
  rt_0034a5c8();
  (*g_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*g_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*g_00658c00)();
  rt_0034a120();
  (*g_00658c00)();
  rt_0034bc58();
  rt_0034e0c4();
  rt_0031b704();
  rt_00348e18();
  (*g_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
  rt_003493c4();
  rt_0034e6cc();
  (*g_00658c00)();
  rt_0034f730();
  (*g_00658c00)();
  rt_0034b4c0();
  rt_00351b2c(uVar1,uVar13);
  uVar6 = rt_00377bec();
  rt_00350308();
  lVar8 = rt_00310e08();
  rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8_02 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*g_00658c00)();
  rt_00350464();
  rt_0035a2b8();
  pcVar14 = *(sk_fnptr *)(extraout_x16_01 + 0x10);
  rt_0035056c();
  uVar9 = (*pcVar14)();
  pcVar17 = *(sk_fnptr *)(extraout_x16_00 + 0x20);
  auVar18 = rt_00358bd8(uVar9,unaff_x28 + *(int32_t *)(unaff_x19 + 0x24));
  (*pcVar17)(auVar18.lo,auVar18.hi,uVar5);
  rt_0034b0e4();
  lVar10 = rt_00310e08();
  iVar2 = *(int32_t *)(lVar10 + 0x24);
  rt_00356304(lVar10,(word_t)plVar12 + (word_t)iVar2);
  (*pcVar14)();
  auVar18 = rt_00352dc4((word_t)*(int32_t *)(unaff_x19 + 0x24));
  (*pcVar17)(auVar18.lo,auVar18.hi,uVar5);
  rt_00310e20(uVar6);
  rt_0034e054();
  rt_00351f4c();
  uVar11 = (*extraout_x8_03)();
  if ((uVar11 & 1) != 0) {
    auVar18 = rt_0035145c();
    (*pcVar17)(auVar18.lo,auVar18.hi,uVar5);
    rt_00351438(local_60 + *(int32_t *)(lVar7 + 0x30));
    (*pcVar17)();
    rt_00351c4c();
    rt_0034c9d8();
    (*extraout_x9)();
    iVar3 = *(int32_t *)(lVar7 + 0x30);
    auVar18 = rt_0009e234();
    (*pcVar17)(auVar18.lo,auVar18.hi,uVar5);
    pcVar14 = *(sk_fnptr *)(extraout_x16_00 + 8);
    (*pcVar14)(lStack_50 + iVar3,uVar5);
    rt_0034c9d8(*(word_t *)(extraout_x16 + 0x20));
    (*extraout_x8_04)();
    (*pcVar17)(local_18 + *(int32_t *)(lVar8 + 0x24),lStack_50 + *(int32_t *)(lVar7 + 0x30),uVar5);
    (*pcVar14)(lStack_50,uVar5);
    lVar7 = *plVar12;
    lVar10 = *(word_t *)((word_t)plVar12 + (word_t)iVar2);
    if (lVar7 <= lVar10) {
      lVar16 = (word_t)*(int32_t *)(unaff_x19 + 0x24);
      pcVar17 = (sk_fnptr)rt_0031b2ec(uVar1);
      (*pcVar17)((word_t)plVar4 + lVar16,local_18,uVar13,uVar1);
      lVar15 = *plVar4;
      if (lVar15 < lVar7 || lVar10 <= lVar15) {
        rt_0034b348();
        uVar13 = 0x108;
      }
      else {
        rt_003584ec(local_a0);
        rt_001fe9a8();
        lVar7 = *local_a0;
        rt_00359478();
        rt_000e15d8();
        (*extraout_x8_05)();
        if (lVar15 == lVar7) {
          rt_00351750(uVar1);
          rt_0035179c(&sk_stack_00000040);
          (*extraout_x9_00)(uVar13,uVar1);
          rt_0034a30c(uVar6);
          rt_0034beec((word_t)plVar4 + lVar16,unaff_x19);
          uVar11 = (*extraout_x8_06)();
          rt_00350524();
          (*pcVar14)();
          if ((uVar11 & 1) != 0) {
            rt_00354afc();
            (*extraout_x8_07)(local_18,lVar8);
L_00201d3c:
            rt_0008e500(unaff_x30);
            return;
          }
          rt_0034b348();
          uVar13 = 0x10a;
        }
        else {
          uVar13 = *(word_t *)(unaff_x20 + *(int32_t *)(lVar10 + 0x24));
          rt_0036b270(uVar13);
          rt_00352ca4(&sk_stack_00000038);
          auVar18 = rt_000b43d0();
          rt_001fea40(auVar18.lo,auVar18.hi,uVar5,uVar6);
          uVar13 = rt_0036b118(uVar13).lo;
          rt_00353fa0(*(word_t *)(extraout_x16_00 + 0x10),uVar13,(word_t)plVar4 + lVar16);
          (*extraout_x8_08)();
          rt_00310e20(uVar6);
          rt_0034eef8();
          rt_0034fdbc();
          uVar11 = (*extraout_x8_09)();
          if ((uVar11 & 1) == 0) {
            rt_00084180();
            (*pcVar14)();
            uVar13 = rt_00351c28();
            (*extraout_x8_11)(uVar13,lVar8);
          }
          else {
            iVar2 = *(int32_t *)(lVar8 + 0x24);
            rt_0035044c(uVar6);
            rt_0034fdbc(local_b8,lVar7 + iVar2);
            uVar11 = (*extraout_x8_10)();
            rt_00084180();
            (*pcVar14)();
            pcVar14 = *(sk_fnptr *)(extraout_x16_02 + 8);
            rt_00350630();
            (*pcVar14)();
            if ((uVar11 & 1) != 0) {
              rt_003567bc();
              (*pcVar14)();
              goto L_00201d3c;
            }
          }
          rt_0034b348();
          uVar13 = 0x10c;
        }
      }
      rt_003486b8(uVar13);
      rt_0034975c();
      goto L_00201bb0;
    }
  }
  rt_00347d60();
L_00201bb0:
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_00201d9c @ 0x00201d9c   (est. sk_lookup_install2)
 * Ghidra: void FUN_00201d9c(word_t param_1,word_t param_2,word_t param_3)
 * Second lookup-and-install variant (parallel to 00201788): same range/slot validation with panic codes 0x115/0x117/0x119.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_lookup_install2(word_t param_1,word_t param_2,word_t param_3)
{

  word_t uVar1;
  int iVar2;
  int iVar3;
  word_t *plVar4;
  word_t uVar5;
  word_t uVar6;
  word_t lVar7;
  word_t lVar8;
  word_t uVar9;
  word_t uVar10;
  word_t lVar11;
  word_t uVar12;
  word_t extraout_x8;
  word_t extraout_x8_00;
  word_t extraout_x8_01;
  sk_fnptr extraout_x8_02;
  sk_fnptr extraout_x8_03;
  word_t uVar13;
  sk_fnptr extraout_x8_04;
  sk_fnptr extraout_x8_05;
  sk_fnptr extraout_x8_06;
  sk_fnptr extraout_x8_07;
  sk_fnptr extraout_x8_08;
  sk_fnptr extraout_x8_09;
  sk_fnptr extraout_x8_10;
  sk_fnptr extraout_x8_11;
  sk_fnptr extraout_x9;
  sk_fnptr extraout_x9_00;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t extraout_x16_01;
  sk_fnptr pcVar14;
  word_t unaff_x20;
  word_t lVar15;
  sk_fnptr pcVar16;
  word_t unaff_x23;
  word_t lVar17;
  word_t unaff_x24;
  word_t unaff_x30;
  sk_u128_t auVar18;
  sk_u128_t auVar19;
  word_t local_c8;
  word_t *local_a0;
  word_t local_68;
  word_t local_60;
  word_t local_48;
  word_t local_28;
  
  auVar18 = rt_0008e518();
  plVar4 = (word_t *)auVar18.lo;
  uVar13 = *(word_t *)(param_3 + 0x10);
  uVar1 = *(word_t *)(param_3 + 0x18);
  rt_0034de64();
  rt_0034de44();
  uVar5 = rt_00377824().lo;
  rt_0034f5b4();
  uVar6 = rt_00377bec();
  rt_0034d404();
  lVar7 = rt_00310e08();
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034c8c8();
  rt_0034b0b4();
  rt_00355adc();
  rt_003722e4();
  lVar8 = rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_003493c4();
  rt_0034d294();
  (*g_00658c00)();
  rt_0034d7fc();
  rt_00349c70();
  (*g_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*g_00658c00)();
  rt_0034a4e0();
  (*g_00658c00)();
  rt_00349f5c();
  (*g_00658c00)();
  rt_0034ba68();
  rt_00077894(0);
  rt_0031b704();
  rt_00348d4c();
  (*g_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
  rt_003493c4();
  rt_0034e6cc();
  (*g_00658c00)();
  rt_0034f730();
  (*g_00658c00)();
  rt_0034b758();
  rt_0034d404();
  uVar9 = rt_00310f04();
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034b71c();
  pcVar16 = *(sk_fnptr *)(extraout_x16_01 + 0x10);
  rt_00351118();
  uVar10 = (*pcVar16)();
  pcVar14 = *(sk_fnptr *)(extraout_x16_00 + 0x20);
  rt_00358dd0(uVar10,unaff_x23 + *(int32_t *)(unaff_x24 + 0x24));
  (*pcVar14)();
  rt_0034b0e4();
  lVar11 = rt_00310f04();
  iVar2 = *(int32_t *)(lVar11 + 0x24);
  (*pcVar16)();
  auVar19 = rt_00354264((word_t)*(int32_t *)(unaff_x24 + 0x24));
  (*pcVar14)(auVar19.lo,auVar19.hi,uVar5);
  rt_00352afc();
  rt_00310e20();
  uVar10 = rt_003505d0();
  rt_00350cb4(uVar10,local_48);
  uVar12 = (*extraout_x8_02)();
  if ((uVar12 & 1) != 0) {
    auVar19 = rt_000e72b0();
    (*pcVar14)(auVar19.lo,auVar19.hi,uVar5);
    rt_00351abc(local_68 + *(int32_t *)(lVar8 + 0x30));
    (*pcVar14)();
    rt_00352bb0();
    auVar19 = rt_00350b78();
    (*extraout_x9)(auVar19.lo,auVar19.hi,lVar8);
    iVar3 = *(int32_t *)(lVar8 + 0x30);
    auVar19 = rt_003504ac();
    (*pcVar14)(auVar19.lo,auVar19.hi,uVar5);
    pcVar16 = *(sk_fnptr *)(extraout_x16_00 + 8);
    (*pcVar16)(local_60 + iVar3,uVar5);
    auVar19 = rt_00350b78(*(word_t *)(extraout_x16 + 0x20));
    (*extraout_x8_03)(auVar19.lo,auVar19.hi,lVar8);
    auVar19 = rt_00359c0c((word_t)*(int32_t *)(lVar8 + 0x30));
    (*pcVar14)(auVar19.lo,auVar19.hi,uVar5);
    (*pcVar16)(local_60,uVar5);
    lVar8 = *(word_t *)auVar18.hi;
    lVar11 = *(word_t *)((word_t)auVar18.hi + (word_t)iVar2);
    if (lVar8 <= lVar11) {
      lVar17 = (word_t)*(int32_t *)(unaff_x24 + 0x24);
      pcVar14 = (sk_fnptr)rt_0031b2bc(uVar1);
      (*pcVar14)((word_t)plVar4 + lVar17,local_28,uVar13,uVar1);
      lVar15 = *plVar4;
      if (lVar15 < lVar8 || lVar11 < lVar15) {
        rt_0034b348();
        uVar13 = 0x115;
      }
      else {
        rt_003584ec(local_a0);
        rt_001fe9a8();
        lVar8 = *local_a0;
        rt_00359478();
        rt_00351160();
        (*extraout_x8_04)();
        if (lVar15 == lVar8) {
          rt_003512d8();
          rt_00351e48(&sk_stack_00000030);
          (*extraout_x9_00)(uVar13,uVar1);
          rt_0034a30c(uVar6);
          rt_0034beec((word_t)plVar4 + lVar17,unaff_x24);
          (*extraout_x8_05)();
          rt_0034eeb8();
          (*pcVar16)();
          if ((unaff_x20 & 1) != 0) {
L_00202344:
            rt_0035a4f8();
            (*extraout_x8_10)(local_28,uVar9);
            rt_0008e500(unaff_x30);
            return;
          }
          rt_0034b348();
          uVar13 = 0x117;
        }
        else {
          uVar13 = *(word_t *)(unaff_x20 + (word_t)*(int32_t *)(lVar11 + 0x24));
          rt_0036b270(uVar13);
          rt_00351e48(&sk_stack_00000040);
          auVar18 = rt_000b43d0();
          rt_001fea40(auVar18.lo,auVar18.hi,uVar5,uVar6);
          uVar13 = rt_0036b118(uVar13).lo;
          rt_00353c6c(*(word_t *)(extraout_x16_00 + 0x10),uVar13,(word_t)plVar4 + lVar17);
          (*extraout_x8_06)();
          rt_00310e20(uVar6);
          rt_0034bccc();
          rt_0034beec();
          uVar12 = (*extraout_x8_07)();
          if ((uVar12 & 1) == 0) {
            rt_0035060c();
            (*pcVar16)();
            rt_00350bc0(&sk_stack_00000048);
            (*extraout_x8_11)(unaff_x24,lVar7);
          }
          else {
            iVar2 = *(int32_t *)(lVar7 + 0x24);
            rt_0035044c(uVar6);
            rt_0034beec(local_c8,unaff_x24 + iVar2);
            (*extraout_x8_08)();
            rt_0034f4c4();
            (*pcVar16)();
            rt_00350bc0(&sk_stack_00000048);
            rt_00350518();
            (*extraout_x8_09)();
            if (((word_t)iVar2 & 1U) != 0) goto L_00202344;
          }
          rt_0034b348();
          uVar13 = 0x119;
        }
      }
      rt_003486b8(uVar13);
      rt_0034975c();
      goto L_002021e4;
    }
  }
  rt_00350410();
  rt_003484e4();
  rt_003499dc();
L_002021e4:
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_002023c4 @ 0x002023c4   (est. sk_map_region_core)
 * Ghidra: void FUN_002023c4(word_t param_1,word_t param_2,word_t param_3)
 * Region map core: large object-map routine. Resolves ranges, iterates entries via rt_0031b050, validates containment (panic codes 0x126/0x127/0x12a/0x131/0x133/300), installs and releases nodes.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_map_region_core(word_t param_1,word_t param_2,word_t param_3)
{

  int iVar1;
  word_t *plVar2;
  word_t *puVar3;
  word_t lVar4;
  word_t uVar5;
  word_t uVar6;
  word_t lVar7;
  word_t uVar8;
  word_t extraout_x8;
  word_t extraout_x8_00;
  word_t extraout_x8_01;
  word_t extraout_x8_02;
  word_t extraout_x8_03;
  sk_fnptr extraout_x8_04;
  sk_fnptr extraout_x8_05;
  sk_fnptr extraout_x8_06;
  sk_fnptr extraout_x8_07;
  sk_fnptr extraout_x8_08;
  word_t extraout_x8_09;
  sk_fnptr extraout_x8_10;
  sk_fnptr extraout_x8_11;
  sk_fnptr extraout_x8_12;
  sk_fnptr extraout_x8_13;
  sk_fnptr extraout_x8_14;
  sk_fnptr extraout_x8_15;
  sk_fnptr extraout_x8_16;
  sk_fnptr extraout_x8_17;
  sk_fnptr extraout_x8_18;
  sk_fnptr extraout_x8_19;
  sk_fnptr extraout_x9;
  word_t extraout_x9_00;
  sk_fnptr extraout_x9_01;
  sk_fnptr extraout_x9_02;
  sk_fnptr extraout_x9_03;
  sk_fnptr extraout_x9_04;
  sk_fnptr extraout_x9_05;
  sk_fnptr extraout_x9_06;
  sk_fnptr extraout_x9_07;
  sk_fnptr extraout_x9_08;
  sk_fnptr extraout_x9_09;
  sk_fnptr extraout_x9_10;
  word_t *extraout_x16;
  word_t extraout_x16_00;
  word_t extraout_x16_01;
  word_t extraout_x16_02;
  word_t *puVar9;
  word_t unaff_x20;
  sk_fnptr pcVar10;
  word_t unaff_x21;
  sk_fnptr pcVar11;
  sk_fnptr pcVar12;
  word_t lVar13;
  word_t lVar14;
  word_t *plVar15;
  word_t unaff_x25;
  word_t unaff_x30;
  sk_u128_t auVar16;
  sk_u128_t auVar17;
  word_t local_120;
  word_t lStack_a0;
  word_t local_98;
  word_t local_90;
  word_t local_88;
  word_t local_68;
  word_t local_60;
  word_t *local_48;
  word_t local_30;
  word_t local_28;
  word_t local_20;
  word_t *local_18;
  word_t *local_10;
  uint8_t auStack_8[8];
  
  auVar16 = rt_0008e518();
  plVar2 = (word_t *)auVar16.lo;
  uVar5 = *(word_t *)(param_3 + 0x18);
  rt_0034cd7c();
  rt_00350b84();
  puVar3 = (word_t *)rt_00377824().lo;
  rt_0034b0b4();
  rt_00353534();
  lVar4 = rt_003722e4().lo;
  rt_000a6f88();
  local_18 = extraout_x16;
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_003493c4();
  rt_0034c684();
  (*g_00658c00)();
  rt_00350464();
  rt_0034911c();
  local_28 = extraout_x16_00;
  (*g_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*g_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*g_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*g_00658c00)();
  rt_0034a9d4();
  (*g_00658c00)();
  rt_0034a9c0();
  (*g_00658c00)();
  rt_0034a400();
  (*g_00658c00)();
  rt_0034b758();
  auVar17 = rt_0035050c();
  rt_0031b704(auVar17.lo,auVar17.hi,uVar5);
  rt_00348d7c();
  (*g_00658c00)(*(word_t *)(extraout_x8_02 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*g_00658c00)();
  rt_0034aadc();
  (*g_00658c00)();
  rt_0034b640();
  (*g_00658c00)();
  rt_0034a9ac();
  (*g_00658c00)();
  rt_0034c074();
  rt_00359568(uVar5);
  rt_003508d8();
  uVar5 = rt_00377bec();
  auVar17 = rt_003504e8();
  local_20 = rt_00310e08(auVar17.lo,auVar17.hi,uVar5);
  rt_000a6f88();
  (*g_00658c00)(*(word_t *)(extraout_x8_03 + 0x40));
  rt_003493c4();
  rt_0034acf0();
  (*g_00658c00)();
  rt_00350434();
  rt_0034acf0();
  (*g_00658c00)();
  rt_0034ac14();
  (*g_00658c00)();
  rt_0034aa28();
  pcVar10 = *(sk_fnptr *)(extraout_x16_01 + 0x10);
  rt_00351abc();
  uVar6 = (*pcVar10)();
  pcVar11 = *(sk_fnptr *)(local_28 + 0x20);
  rt_00352a28(uVar6,unaff_x21 + *(int32_t *)(unaff_x25 + 0x24));
  (*pcVar11)();
  rt_0034b0e4();
  lVar7 = rt_00310e08();
  rt_00356278(lVar7,(word_t)auVar16.hi + (word_t)*(int32_t *)(lVar7 + 0x24));
  local_10 = (word_t *)(extraout_x16_01 + 0x10);
  uVar6 = (*pcVar10)();
  rt_00353c6c(uVar6,local_60 + *(int32_t *)(unaff_x25 + 0x24));
  (*pcVar11)();
  rt_00310e20(uVar5);
  rt_0034b8cc();
  rt_00350ac4();
  uVar8 = (*extraout_x8_04)();
  if ((uVar8 & 1) != 0) {
    local_10 = (word_t *)((word_t)local_10 & 0xffffffffffff | 0xe3ba000000000000);
    rt_00353390();
    rt_00350768();
    (*pcVar11)();
    rt_00359e28();
    rt_003508c0();
    (*pcVar11)();
    rt_00352474();
    rt_0034e54c();
    (*extraout_x9)();
    iVar1 = *(int32_t *)(lVar4 + 0x30);
    rt_00358db8();
    rt_003508c0();
    (*pcVar11)();
    puVar9 = (word_t *)(local_28 + 8);
    pcVar12 = (sk_fnptr)*puVar9;
    (*pcVar12)((word_t)local_48 + (word_t)iVar1,puVar3);
    rt_0034e54c(local_18[4]);
    local_18 = local_18 + 4;
    rt_00354128();
    (*extraout_x8_05)();
    rt_0035a518((word_t)*(int32_t *)(lVar4 + 0x30));
    (*pcVar11)();
    rt_003512c0();
    (*pcVar12)();
    (*pcVar10)(lStack_a0,plVar2,unaff_x25);
    uVar6 = (*pcVar11)(local_90,lStack_a0 + *(int32_t *)(unaff_x25 + 0x24),puVar3);
    iVar1 = *(int32_t *)(lVar7 + 0x24);
    rt_00358dd0(uVar6,(word_t)plVar2 + (word_t)iVar1);
    uVar6 = (*pcVar10)();
    rt_003579e8(uVar6,local_98 + *(int32_t *)(unaff_x25 + 0x24));
    (*pcVar11)();
    rt_003540dc();
    rt_00310e20();
    uVar6 = rt_00350a7c();
    rt_00351378(uVar6,local_88);
    uVar8 = (*extraout_x8_06)();
    if ((uVar8 & 1) != 0) {
      local_10 = (word_t *)(word_t)iVar1;
      rt_0035463c();
      puVar9 = (word_t *)((word_t)puVar9 & 0xffffffffffff | 0x4f8000000000000);
      auVar17 = rt_00350944();
      (*pcVar11)(auVar17.lo,auVar17.hi,puVar3);
      rt_00359e28();
      rt_00351a20();
      (*pcVar11)();
      rt_0034e54c();
      rt_00354134();
      (*extraout_x8_07)();
      iVar1 = *(int32_t *)(lVar4 + 0x30);
      auVar17 = rt_00350b3c();
      (*pcVar11)(auVar17.lo,auVar17.hi,puVar3);
      (*pcVar12)((word_t)local_48 + (word_t)iVar1,puVar3);
      rt_0034e54c();
      rt_00353148();
      (*extraout_x8_08)();
      lVar7 = (word_t)*(int32_t *)(local_20 + 0x24);
      (*pcVar11)(local_68 + lVar7,(word_t)local_48 + (word_t)*(int32_t *)(lVar4 + 0x30),puVar3);
      local_18 = puVar3;
      (*pcVar12)(local_48,puVar3);
      plVar15 = *(word_t **)auVar16.hi;
      rt_00355418();
      lVar4 = *(word_t *)(extraout_x8_09 + extraout_x9_00);
      if ((word_t)plVar15 <= lVar4) {
        lVar13 = *plVar2;
        lVar14 = *(word_t *)((word_t)plVar2 + (word_t)local_10);
        if (lVar13 <= lVar14) {
          local_10 = puVar9;
          rt_00354064();
          rt_0031b050(extraout_x8_00);
          uVar6 = rt_00350a7c();
          rt_00351dcc(uVar6,local_30);
          (*extraout_x8_10)();
          if (lVar13 < (word_t)plVar15 || lVar4 <= lVar13) {
            rt_0034b348();
            uVar5 = 0x126;
          }
          else if (lVar4 < lVar14) {
            rt_0034b348();
            uVar5 = 0x127;
          }
          else {
            rt_00351e48(&sk_stack_00000010);
            rt_001fe9a8(param_3);
            lVar4 = *plVar15;
            pcVar10 = *(sk_fnptr *)(extraout_x16_01 + 8);
            (*pcVar10)(plVar15,unaff_x25);
            if (lVar13 == lVar4) {
              rt_00351750(extraout_x8_00);
              rt_00352ca4(auStack_8);
              rt_003509b0();
              (*extraout_x9_01)();
              rt_0034c4fc(uVar5);
              rt_0034df34(local_68,local_48);
              (*extraout_x8_11)();
              rt_0034f4c4();
              rt_00357998();
              (*extraout_x9_02)();
              if ((unaff_x20 & 1) == 0) {
                rt_0034b348();
                uVar5 = 0x12a;
              }
              else {
L_00202b98:
                rt_00359a60();
                rt_00351f58();
                rt_001fe9a8();
                lVar4 = *local_48;
                rt_00350618();
                (*pcVar10)();
                if (lVar14 == lVar4) {
                  rt_00351750(extraout_x8_00);
                  rt_003526b8(auStack_8);
                  rt_003509b0();
                  (*extraout_x9_06)();
                  rt_0034c4fc(uVar5);
                  rt_0034df34(local_68 + lVar7,param_3);
                  uVar8 = (*extraout_x8_14)();
                  rt_00084180();
                  rt_00357998();
                  (*extraout_x9_07)();
                  lVar4 = local_20;
                  if ((uVar8 & 1) != 0) {
                    pcVar10 = *(sk_fnptr *)(extraout_x16_02 + 8);
                    (*pcVar10)(local_68,local_20);
                    (*pcVar10)(local_30,lVar4);
L_00202d48:
                    rt_0008e500(unaff_x30);
                    return;
                  }
                  rt_0034b348();
                  uVar5 = 0x131;
                }
                else {
                  uVar6 = *(word_t *)(unaff_x20 + (word_t)*(int32_t *)(param_3 + 0x24));
                  rt_0036b270(uVar6);
                  rt_00351af8(&local_28);
                  rt_0034c818();
                  rt_001fea40();
                  uVar6 = rt_0036b118(uVar6).lo;
                  rt_00353fa0(*(word_t *)(local_28 + 0x10),uVar6,local_68 + lVar7);
                  (*extraout_x8_15)();
                  rt_00310e20(uVar5);
                  rt_0034f4e4();
                  rt_00350ac4();
                  uVar8 = (*extraout_x8_16)();
                  lVar4 = local_20;
                  if ((uVar8 & 1) == 0) {
                    rt_00084180();
                    rt_00357998();
                    (*extraout_x9_10)();
                    rt_00350bc0(&sk_stack_00000000);
                    (*extraout_x8_19)(unaff_x20,local_20);
                  }
                  else {
                    iVar1 = *(int32_t *)(local_20 + 0x24);
                    rt_0035044c(uVar5);
                    rt_00350ac4(local_120,unaff_x20 + (word_t)iVar1);
                    uVar8 = (*extraout_x8_17)();
                    rt_00084180();
                    rt_00357998();
                    (*extraout_x9_08)();
                    pcVar10 = *(sk_fnptr *)(extraout_x16_02 + 8);
                    rt_0035084c();
                    (*pcVar10)();
                    if ((uVar8 & 1) != 0) {
                      rt_003504c4();
                      (*pcVar10)();
                      (*pcVar10)(local_30,lVar4);
                      goto L_00202d48;
                    }
                  }
                  rt_0034b348();
                  uVar5 = 0x133;
                }
              }
            }
            else {
              uVar6 = *(word_t *)(unaff_x20 + (word_t)*(int32_t *)(param_3 + 0x24));
              rt_0036b270(uVar6);
              rt_003526b8(&local_18);
              rt_003509bc();
              rt_00358684();
              rt_001fea40();
              rt_0036b118(uVar6);
              rt_0035a3b8();
              uVar6 = rt_00355e50();
              (*extraout_x9_03)(uVar6,local_68,puVar9);
              rt_00310e20(uVar5);
              rt_00350804();
              rt_0034f3f4();
              uVar8 = (*extraout_x8_12)();
              if ((uVar8 & 1) == 0) {
                rt_0035060c();
                rt_00357998();
                (*extraout_x9_09)();
                rt_00350bc0(&sk_stack_00000000);
                (*extraout_x8_18)(param_3,local_20);
              }
              else {
                iVar1 = *(int32_t *)(local_20 + 0x24);
                rt_0035044c(uVar5);
                rt_00350ac4(local_48,param_3 + iVar1);
                (*extraout_x8_13)();
                rt_0034f4c4();
                rt_00357998();
                (*extraout_x9_04)();
                rt_00352bbc();
                rt_0034d2d4();
                (*extraout_x9_05)();
                if (((word_t)iVar1 & 1U) != 0) goto L_00202b98;
              }
              rt_0034b348();
              uVar5 = 300;
            }
          }
          rt_003486b8(uVar5);
          rt_0034975c();
          goto L_00202a10;
        }
      }
    }
  }
  rt_00347d60();
L_00202a10:
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_00202df4 @ 0x00202df4   (est. sk_node_alloc)
 * Ghidra: word_t * FUN_00202df4(word_t *param_1,word_t param_2,word_t param_3)
 * Allocates a 0x28-byte node (rt_0036a908 tag 0xd183), initializes it via sk_node_init (00202e68), stores the result at +0x20, returns the metadata descriptor &g_003471a4. Constructor pattern.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t * sk_node_alloc(word_t *param_1,word_t param_2,word_t param_3)
{

  word_t lVar1;
  word_t uVar2;
  
  lVar1 = rt_0036a908(0x28,0xd183);
  *param_1 = lVar1;
  uVar2 = sk_node_init((word_t *)(lVar1),(word_t)(param_2),(word_t)(param_3)).lo;
  *(word_t *)(lVar1 + 0x20) = uVar2;
  return (word_t *)&g_003471a4;
}

/* FUN_00202e68 @ 0x00202e68   (est. sk_node_init)
 * Ghidra: sk_u128_t FUN_00202e68(word_t *param_1,word_t param_2,word_t param_3)
 * Node constructor: resolves object, builds an object via rt_00377824, allocates a child table (rt_0036a908 tag 0x9b0d) and calls rt_001fff64 to initialize it. Returns sk_u128_t descriptor (lo=&g_003471a8).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t sk_node_init(word_t *param_1,word_t param_2,word_t param_3)
{

  word_t uVar1;
  word_t lVar2;
  sk_u128_t auVar3;
  
  uVar1 = rt_00027754(*(word_t *)(param_3 + 0x18));
  lVar2 = rt_00377824(0,uVar1,*(word_t *)(param_3 + 0x10),&g_00611b24,&g_00611b34).lo;
  *param_1 = lVar2;
  lVar2 = *(word_t *)(lVar2 + -8);
  param_1[1] = lVar2;
  lVar2 = rt_0036a908(*(word_t *)(lVar2 + 0x40),0x9b0d);
  param_1[2] = lVar2;
  rt_001fff64(lVar2,param_2,param_3);
  auVar3.hi = lVar2;
  auVar3.lo = (word_t)&g_003471a8;
  return auVar3;
}

/* FUN_00202f84 @ 0x00202f84   (est. sk_unmap_region)
 * Ghidra: void FUN_00202f84(word_t param_1,word_t param_2,word_t param_3)
 * Unmap region: resolves ranges, runs a first-entry check (rt_001b9040); on failure panics; on success walks and releases entries, calling sk_cleanup_thunk and finishing with runtime release.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_unmap_region(word_t param_1,word_t param_2,word_t param_3)
{

  int iVar1;
  word_t *plVar2;
  word_t uVar3;
  word_t uVar4;
  word_t lVar5;
  word_t uVar6;
  sk_fnptr pcVar7;
  word_t lVar8;
  word_t extraout_x8;
  word_t extraout_x8_00;
  word_t extraout_x8_01;
  sk_fnptr extraout_x8_02;
  sk_fnptr pcVar9;
  sk_fnptr extraout_x8_03;
  sk_fnptr extraout_x8_04;
  sk_fnptr extraout_x8_05;
  sk_fnptr extraout_x8_06;
  sk_fnptr extraout_x8_07;
  word_t extraout_x8_08;
  sk_fnptr extraout_x8_09;
  sk_fnptr extraout_x9;
  sk_fnptr extraout_x9_00;
  sk_fnptr extraout_x9_01;
  sk_fnptr extraout_x9_02;
  sk_fnptr extraout_x9_03;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t extraout_x16_01;
  word_t extraout_x16_02;
  word_t *puVar10;
  word_t unaff_x20;
  word_t uVar11;
  word_t unaff_x22;
  word_t unaff_x24;
  word_t lVar12;
  word_t uVar13;
  sk_fnptr pcVar14;
  word_t unaff_x30;
  sk_u128_t auVar15;
  word_t local_60;
  word_t local_40;
  
  auVar15 = rt_0008e518();
  lVar8 = auVar15.hi;
  plVar2 = (word_t *)auVar15.lo;
  rt_00351ef8(param_3);
  uVar11 = *(word_t *)(lVar8 + 0x10);
  rt_0034e034(0);
  rt_00377824();
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034cd54();
  rt_00352968();
  rt_0034e034();
  uVar3 = rt_00377824().lo;
  rt_0034e024();
  uVar4 = rt_00377bec();
  auVar15 = rt_00350720();
  lVar5 = rt_00310e08(auVar15.lo,auVar15.hi,uVar4);
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034a760();
  rt_00349c70();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_00350428();
  rt_00349080();
  (*g_00658c00)(*(word_t *)(extraout_x8_01 + 0x40));
  rt_00349178();
  rt_003502e8();
  rt_0031b704();
  rt_00348d4c();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034b2f8();
  rt_001fe7cc(lVar8);
  rt_003513b4(plVar2);
  uVar6 = rt_001b9040();
  rt_00350470(*(word_t *)(extraout_x16_02 + 8));
  (*extraout_x8_02)();
  if ((uVar6 & 1) == 0) {
    rt_00350410();
    rt_003488bc();
    rt_0006f768();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  lVar12 = (word_t)*(int32_t *)(unaff_x24 + 0x24);
  rt_0026c274(lVar8);
  rt_00351750();
  rt_00355bd0();
  (*extraout_x9)(uVar11);
  puVar10 = (word_t *)(extraout_x16_01 + 8);
  pcVar9 = (sk_fnptr)*puVar10;
  rt_00100efc();
  (*extraout_x8_03)();
  rt_00350780(uVar4);
  pcVar7 = (sk_fnptr)rt_0014ae44();
  rt_00351c94((word_t)plVar2 + lVar12);
  uVar6 = (*pcVar7)();
  pcVar14 = *(sk_fnptr *)(extraout_x16_00 + 8);
  rt_003507c8();
  (*pcVar14)();
  if ((uVar6 & 1) == 0) {
    uVar13 = *(word_t *)(unaff_x20 + *(int32_t *)(lVar8 + 0x24));
    rt_0036b270(uVar13);
    rt_00350b18(local_40);
    rt_001fea40();
    rt_0036b118(uVar13);
    auVar15 = rt_00350b00(*(word_t *)(extraout_x16_00 + 0x10));
    (*extraout_x8_04)(auVar15.lo,auVar15.hi,uVar3);
    rt_0035a6b4(*(word_t *)(extraout_x16 + 8));
    (*extraout_x8_05)();
    rt_00351c94((word_t)plVar2 + lVar12,extraout_x8_00);
    (*pcVar7)();
    uVar4 = rt_00355884();
    (*pcVar14)(uVar4,uVar3);
    if (((word_t)puVar10 & 1) == 0) {
      rt_0036b270(uVar13);
      rt_00100c38(local_40);
      rt_003569e4();
      rt_001fea40();
      rt_0036b118(uVar13);
      rt_0026c274(unaff_x22,lVar8);
      rt_00352abc();
      rt_00350998(local_60,local_40);
      (*extraout_x9_02)();
      rt_0009e234();
      (*pcVar9)();
      (*extraout_x8_05)(local_40,lVar5);
      rt_0035238c();
      rt_0035a19c(param_3,uVar11);
      rt_00377bec();
      rt_0031e104();
      rt_003548e8();
      rt_00350768(extraout_x8_00,extraout_x8_08 + lVar12);
      (*extraout_x9_03)();
      rt_0035336c();
      rt_00350518();
      pcVar7 = extraout_x8_09;
      goto L_0020348c;
    }
  }
  if (SBORROW8(*plVar2,1)) {
                    /* WARNING: Does not return */
    pcVar7 = (sk_fnptr)SoftwareBreakpoint(1,0x2034f8);
    (*pcVar7)();
  }
  rt_0035aa90((word_t)*(int32_t *)(lVar8 + 0x24));
  rt_00350524(local_40);
  rt_003569e4();
  rt_001fea40();
  rt_0036b118(puVar10);
  rt_0026c274(unaff_x22,lVar8);
  rt_00352abc();
  rt_003530b0(local_60);
  rt_00350998();
  (*extraout_x9_00)();
  rt_003509e0();
  (*pcVar9)();
  iVar1 = *(int32_t *)(lVar5 + 0x24);
  rt_0035238c();
  rt_0035a19c(param_3,uVar11);
  rt_00377bec();
  rt_00354930();
  rt_00350768(extraout_x8_00,local_40 + iVar1);
  (*extraout_x9_01)();
  rt_0035336c();
  rt_00350518();
  (*extraout_x8_06)();
  rt_00353154();
  rt_00350914();
  pcVar7 = extraout_x8_07;
L_0020348c:
  (*pcVar7)();
  rt_0035084c(extraout_x8);
  rt_00352450();
  rt_001fd4f4();
  rt_0008e500(unaff_x30);
  return;
}

/* FUN_0020353c @ 0x0020353c   (est. sk_node_config)
 * Ghidra: void FUN_0020353c(word_t param_1,word_t param_2,word_t param_3)
 * Node configuration: builds an object frame, resolves a slot, retains/releases, and invokes a table update via runtime dispatch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_node_config(word_t param_1,word_t param_2,word_t param_3)
{

  int iVar1;
  word_t uVar2;
  word_t uVar3;
  word_t lVar4;
  sk_fnptr pcVar5;
  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x8_01;
  sk_fnptr extraout_x8_02;
  sk_fnptr extraout_x9;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t unaff_x20;
  word_t uVar6;
  word_t unaff_x30;
  sk_u128_t auVar7;
  sk_u128_t auVar8;
  word_t local_48;
  
  auVar7 = rt_0008e518();
  rt_00351bec(param_3);
  uVar6 = *(word_t *)(auVar7.hi + 0x10);
  rt_003525cc();
  rt_0034df64();
  rt_00377824();
  uVar2 = rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034b708();
  rt_00352f54();
  rt_0034df64();
  rt_00377824();
  rt_0034db68();
  uVar3 = rt_00377bec();
  auVar8 = rt_003504e8();
  rt_00310e08(auVar8.lo,auVar8.hi,uVar3);
  rt_00348ce8();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034af20();
  uVar3 = *(word_t *)(unaff_x20 + *(int32_t *)(auVar7.hi + 0x24));
  rt_0036b270(uVar3);
  rt_00350624(*(word_t *)auVar7.lo);
  rt_001fea40();
  rt_0036b118(uVar3);
  rt_00352eb4();
  rt_00352e3c();
  rt_0035136c();
  (*extraout_x9)();
  rt_00350b00(*(word_t *)(extraout_x16 + 8));
  (*extraout_x8_00)();
  rt_00350318();
  lVar4 = rt_0031b704();
  iVar1 = *(int32_t *)(lVar4 + 0x24);
  rt_0034de8c();
  auVar8 = rt_00351274();
  pcVar5 = (sk_fnptr)rt_00377bec(auVar8.lo,auVar8.hi,uVar2);
  rt_00352ecc();
  uVar2 = rt_0035949c();
  rt_003515fc(uVar2,(word_t)auVar7.lo + (word_t)iVar1);
  (*extraout_x8_01)();
  rt_00351a50();
  auVar7 = rt_00348b94();
  rt_00377824(auVar7.lo,auVar7.hi,uVar6);
  rt_00349530();
  (**(sk_fnptr *)(extraout_x16_00 + 0x10))(extraout_x8,local_48);
  rt_00351d00();
  (*pcVar5)();
  rt_0035313c();
  rt_0035084c();
  (*extraout_x8_02)();
  rt_0008e500(unaff_x30);
  return;
}

/* FUN_0020373c @ 0x0020373c   (est. sk_node_release)
 * Ghidra: void FUN_0020373c(void)
 * Node release helper: runtime prologue, resolves object slots, calls the table-update dispatch, ends with a cleanup.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_node_release(void)
{

  int iVar1;
  word_t lVar2;
  word_t uVar3;
  sk_fnptr pcVar4;
  word_t uVar5;
  word_t in_x3;
  sk_fnptr extraout_x8;
  word_t extraout_x16;
  sk_fnptr unaff_x19;
  word_t unaff_x30;
  sk_u128_t auVar6;
  uint8_t auStack_20 [32];
  
  rt_0008e518();
  auVar6 = rt_00358a74();
  rt_00351ad4(in_x3);
  rt_0034d2a4();
  rt_00350bfc(0xff);
  rt_00377824();
  rt_0034ee08();
  rt_00377bec();
  rt_003502f8();
  rt_00310e08();
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034af20();
  rt_0035aa90((word_t)*(int32_t *)(unaff_x19 + 0x24));
  rt_00350878(*(word_t *)auVar6.hi);
  rt_001fea40();
  rt_0036b118();
  rt_0034ef88();
  lVar2 = rt_0031b704();
  iVar1 = *(int32_t *)(lVar2 + 0x24);
  uVar3 = rt_0031b870();
  rt_003516f0(uVar3,auStack_20);
  (*extraout_x8)();
  rt_00351a50();
  rt_003513d8(0xff);
  rt_00377824();
  rt_0034c6b4();
  uVar3 = rt_00377bec();
  pcVar4 = (sk_fnptr)rt_00310ed4();
  rt_00350530();
  uVar5 = rt_00377dcc();
  (*pcVar4)(auVar6.lo,(word_t)auVar6.hi + (word_t)iVar1,uVar5,uVar3);
  rt_0034cfa4();
  (*unaff_x19)();
  (**(sk_fnptr *)(extraout_x16 + 8))();
  rt_0008e500(unaff_x30);
  return;
}

/* FUN_002038d4 @ 0x002038d4   (est. sk_node_alloc4)
 * Ghidra: void FUN_002038d4(void)
 * Node allocation (4-slot): allocates four tables (rt_0036a908 tag 0x4d96), stores into +0x18/0x20/0x28/0x30/0x38, then calls sk_node_config (0020353c). Returns via rt_0008e500 with a data label.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_node_alloc4(void)
{

  word_t uVar1;
  word_t extraout_x8;
  word_t extraout_x8_00;
  sk_fnptr extraout_x8_01;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t unaff_x22;
  word_t unaff_x24;
  word_t uVar2;
  word_t unaff_x30;
  sk_u128_t auVar3;
  
  rt_0008e518();
  rt_0034c2e8();
  uVar1 = rt_00358c2c();
  rt_0036a908(uVar1,0x4d96);
  rt_003528b8();
  rt_00351bec();
  rt_00350bd8();
  uVar1 = *(word_t *)(unaff_x22 + 0x10);
  auVar3 = rt_003497a0();
  uVar1 = rt_00377824(auVar3.lo,auVar3.hi,uVar1).lo;
  *(word_t *)(unaff_x24 + 0x18) = uVar1;
  rt_00352018();
  *(word_t *)(unaff_x24 + 0x20) = extraout_x16;
  uVar2 = *(word_t *)(extraout_x8 + 0x40);
  uVar1 = rt_0036a908(uVar2,0x4d96);
  *(word_t *)(unaff_x24 + 0x28) = uVar1;
  uVar1 = rt_0036a908(uVar2,0x4d96);
  *(word_t *)(unaff_x24 + 0x30) = uVar1;
  rt_003508e4();
  rt_0031b704();
  rt_00348d7c();
  uVar2 = rt_0036a908(*(word_t *)(extraout_x8_00 + 0x40),0x4d96);
  *(word_t *)(unaff_x24 + 0x38) = uVar2;
  rt_0035136c(*(word_t *)(extraout_x16_00 + 0x10));
  (*extraout_x8_01)();
  rt_0034b508(uVar1);
  sk_node_config((word_t)(0),(word_t)(0),(word_t)(0));
  rt_0008e500(&g_002039f4,uVar1,unaff_x30);
  return;
}

/* FUN_00203a0c @ 0x00203a0c   (est. sk_sub_release)
 * Ghidra: void FUN_00203a0c(void)
 * Sub-node release: runtime calls to release a child table and drop a reference.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_sub_release(void)
{

  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  word_t extraout_x12;
  
  rt_00349ef4();
  rt_00349b3c();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_00348f38();
  rt_00350e74(*(word_t *)(extraout_x12 + 0x10));
  (*extraout_x8_00)();
  rt_0035242c();
  rt_0034b358();
  rt_001fccf8();
  rt_0036b270();
  return;
}

/* FUN_00203aa4 @ 0x00203aa4   (est. sk_sub_alloc)
 * Ghidra: void FUN_00203aa4(void)
 * Sub-node alloc wrapper: builds via rt_00377824, calls sk_sub_init (00203b08) then sk_sub_release (00203a0c), releases the node.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_sub_alloc(void)
{

  word_t uVar1;
  sk_u128_t auVar2;
  
  rt_00349ef4();
  rt_00349748();
  rt_00354394();
  auVar2 = rt_00377824();
  rt_00350af4(auVar2.lo,auVar2.hi,auVar2.lo);
  rt_00352920();
  uVar1 = sk_sub_init((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
  rt_003504a0();
  sk_sub_release();
  rt_0036b118(uVar1);
  return;
}

/* FUN_00203b08 @ 0x00203b08   (est. sk_sub_init)
 * Ghidra: word_t FUN_00203b08(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
 * Sub-node initializer: runtime prologue, resolves object, runs a branch check; on success installs a child and returns, else panics (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_sub_init(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
{

  int iVar1;
  word_t uVar2;
  word_t lVar3;
  word_t uVar4;
  word_t uVar5;
  word_t extraout_x8;
  word_t extraout_x8_00;
  sk_fnptr extraout_x8_01;
  sk_fnptr extraout_x8_02;
  sk_fnptr extraout_x8_03;
  sk_fnptr extraout_x9;
  sk_fnptr extraout_x9_00;
  sk_fnptr extraout_x9_01;
  word_t extraout_x16;
  word_t extraout_x16_00;
  word_t unaff_x21;
  word_t unaff_x22;
  word_t unaff_x24;
  word_t unaff_x26;
  sk_fnptr pcVar6;
  sk_fnptr pcVar7;
  sk_u128_t auVar8;
  word_t in_stack_00000018;
  
  rt_0008e518();
  rt_0034b0b4();
  rt_00359000();
  rt_00348ce8();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_00349db0();
  (*g_00658c00)();
  rt_0034b87c();
  rt_003494e8();
  (*g_00658c00)(*(word_t *)(extraout_x8_00 + 0x40));
  rt_00348a80();
  (*g_00658c00)();
  rt_0034b4c0();
  rt_0034c3c4();
  rt_00350768(param_5);
  uVar2 = rt_00377bec();
  auVar8 = rt_003504e8();
  rt_00310e08(auVar8.lo,auVar8.hi,uVar2);
  lVar3 = rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034b6f4();
  rt_000277b8(param_5);
  uVar4 = rt_0034d434();
  (*extraout_x9)(uVar4,param_5);
  rt_00310924(param_5);
  uVar4 = rt_0034f634();
  (*extraout_x9_00)(uVar4,param_5);
  rt_00310e20(uVar2);
  rt_0034db98();
  rt_00350ac4();
  uVar5 = (*extraout_x8_01)();
  if ((uVar5 & 1) != 0) {
    pcVar6 = *(sk_fnptr *)(extraout_x16_00 + 0x20);
    auVar8 = rt_00350ea4();
    (*pcVar6)(auVar8.lo,auVar8.hi,param_3);
    rt_003508d8(unaff_x26 + *(int32_t *)(unaff_x22 + 0x30));
    (*pcVar6)();
    rt_00352a40();
    rt_0034ef78();
    (*extraout_x9_01)();
    iVar1 = *(int32_t *)(unaff_x22 + 0x30);
    rt_003578a8();
    rt_003504a0();
    (*pcVar6)();
    pcVar7 = *(sk_fnptr *)(extraout_x16_00 + 8);
    (*pcVar7)(unaff_x21 + iVar1,param_3);
    rt_0034ef78(*(word_t *)(extraout_x16 + 0x20));
    (*extraout_x8_02)();
    (*pcVar6)(unaff_x24 + *(int32_t *)(lVar3 + 0x24),unaff_x21 + *(int32_t *)(unaff_x22 + 0x30),param_3);
    rt_00084180();
    (*pcVar7)();
    auVar8 = rt_0035620c();
    rt_00279568(auVar8.lo,auVar8.hi,param_3,uVar2);
    rt_003529a4();
    rt_00351384();
    (*extraout_x8_03)();
    uVar2 = rt_00353100();
    rt_0008e500(uVar2,in_stack_00000018);
    return 0;
  }
  rt_00347d60();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_00203e0c @ 0x00203e0c   (est. sk_iterate_children)
 * Ghidra: void FUN_00203e0c(void)
 * Child iterator: loops over children via a vtable method (offset into +0x28), collects up to one (sets flag byte 1), emits the frame and returns. State-machine loop.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_iterate_children(void)
{

  char cVar1;
  uint8_t uVar2;
  word_t uVar3;
  word_t uVar4;
  sk_fnptr pcVar5;
  word_t uVar6;
  word_t uVar7;
  word_t uVar8;
  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x8_01;
  word_t extraout_x16;
  char *unaff_x20;
  sk_fnptr pcVar9;
  sk_u128_t auVar10;
  sk_u128_t auVar11;
  
  auVar10 = rt_0008e518();
  rt_00352590();
  rt_00350878();
  rt_00377824();
  rt_0034ee68();
  rt_00310d68();
  uVar3 = rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034aee4();
  rt_003499f0();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034b0d4();
  cVar1 = *unaff_x20;
  rt_00359530();
  rt_00350878();
  auVar11 = rt_00377824();
  uVar8 = auVar11.lo;
  rt_003507e0(uVar8,auVar11.hi,uVar8);
  uVar4 = rt_00377bec();
  pcVar5 = (sk_fnptr)rt_000a68f4();
  uVar2 = cVar1 == '\x01';
  if ((bool)uVar2) {
    rt_00350530();
    uVar3 = rt_00377dcc();
    (*pcVar5)(extraout_x8,uVar3,uVar4);
  }
  else {
    while( true ) {
      uVar6 = rt_00377dcc(0,uVar8);
      (*pcVar5)(uVar6,uVar4);
      uVar6 = rt_0034b2c8();
      if ((bool)uVar2) break;
      pcVar9 = *(sk_fnptr *)(extraout_x16 + 0x20);
      rt_0034ee98();
      (*pcVar9)();
      uVar7 = (**(sk_fnptr *)(unaff_x20 + *(int32_t *)(auVar10.lo + 0x28)))();
      if ((uVar7 & 1) == 0) {
        *unaff_x20 = '\x01';
        rt_0035100c();
        (*pcVar9)();
        auVar11 = rt_0035354c();
        goto L_00204004;
      }
      rt_003508b4(*(word_t *)(extraout_x16 + 8));
      (*extraout_x8_00)();
    }
    rt_0035152c(uVar6,uVar3);
    (*extraout_x8_01)();
    auVar11.hi = 1;
    auVar11.lo = extraout_x8;
L_00204004:
    rt_00352480(auVar11.lo,auVar11.hi);
    rt_000839d8();
  }
  rt_0008e500(auVar10.hi);
  return;
}

/* FUN_0020405c @ 0x0020405c   (est. sk_iterate_walk)
 * Ghidra: void FUN_0020405c(void)
 * Iteration walker: while-loop over entries via rt_0035a1b4/rt_00351324, dispatching a vtable slot; breaks on runtime branch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_iterate_walk(void)
{

  sk_fnptr pcVar1;
  sk_fnptr pcVar2;
  word_t uVar3;
  word_t uVar4;
  sk_fnptr pcVar5;
  word_t extraout_x1;
  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  word_t extraout_x8_01;
  sk_fnptr extraout_x8_02;
  sk_fnptr extraout_x8_03;
  sk_fnptr extraout_x8_04;
  sk_fnptr extraout_x8_05;
  sk_fnptr extraout_x9;
  word_t unaff_x20;
  word_t uVar6;
  word_t unaff_x30;
  sk_u128_t auVar7;
  word_t local_40;
  
  rt_0008e518();
  rt_003518c4();
  rt_00350bd8(extraout_x1);
  uVar6 = *(word_t *)(unaff_x20 + 0x10);
  auVar7 = rt_003497a0();
  uVar6 = rt_00377824(auVar7.lo,auVar7.hi,uVar6).lo;
  rt_000a6f88();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034cd54();
  rt_0034cae8();
  rt_003510f4();
  rt_00377824();
  rt_00348cd0();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034af20();
  rt_003506e8();
  rt_003507bc(extraout_x8);
  (*extraout_x9)();
  pcVar2 = (sk_fnptr)rt_00310924();
  rt_0035705c();
  rt_00351ba0();
  rt_00377bec();
  rt_00027754();
  rt_0014ae44();
  rt_003561b8();
  while( true ) {
    rt_003504f4();
    (*pcVar2)();
    rt_00351324();
    rt_00351b20();
    uVar3 = ((sk_fnptr)local_40)();
    rt_003567ec();
    rt_00350b00();
    (*extraout_x8_00)();
    if ((uVar3 & 1) != 0) break;
    rt_0035a1b4();
    pcVar1 = *(sk_fnptr *)(unaff_x20 + extraout_x8_01);
    uVar4 = rt_00351b84();
    rt_00352450(uVar4,extraout_x8);
    pcVar5 = (sk_fnptr)(*extraout_x8_02)();
    auVar7 = rt_00352b14();
    (*extraout_x8_03)(auVar7.lo,auVar7.hi,uVar6);
    rt_0034cfa4();
    (*pcVar5)();
    uVar3 = (*pcVar1)();
    rt_00354ab0();
    rt_00350a34();
    (*extraout_x8_04)();
    if ((uVar3 & 1) == 0) break;
    rt_00027818();
    rt_00350a88();
    rt_00350998();
    (*extraout_x8_05)();
  }
  rt_0008e500(unaff_x30);
  return;
}

/* FUN_00204280 @ 0x00204280   (est. sk_find_child)
 * Ghidra: void FUN_00204280(word_t param_1,word_t param_2,word_t param_3)
 * Find child: resolves object, checks a branch; on success finds via rt_00319658 and returns, else panics (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_find_child(word_t param_1,word_t param_2,word_t param_3)
{

  word_t uVar1;
  word_t uVar2;
  sk_fnptr extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x9;
  sk_fnptr extraout_x9_00;
  word_t extraout_x16;
  word_t unaff_x30;
  
  rt_0008e518();
  rt_0035a2c4();
  uVar1 = rt_0034c354();
  rt_00353960(uVar1,param_3);
  rt_00377824();
  rt_00348d7c();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034af20();
  rt_00310924();
  rt_0034d434();
  (*extraout_x9)();
  rt_00084174();
  rt_00351cd0();
  rt_00377bec();
  rt_0035044c();
  rt_00350bf0();
  rt_00351c94();
  uVar2 = (*extraout_x8)();
  rt_00350b3c(*(word_t *)(extraout_x16 + 8));
  (*extraout_x8_00)();
  if ((uVar2 & 1) != 0) {
    rt_00319658();
    rt_00350c50();
    rt_00350768();
    (*extraout_x9_00)();
    rt_0008e500(unaff_x30);
    return;
  }
  rt_00350410();
  rt_003488bc();
  rt_0034c220();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_002043c4 @ 0x002043c4   (est. sk_node_alloc2)
 * Ghidra: word_t * FUN_002043c4(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Node allocator variant (0x28 bytes, tag 0x1edb): initializes via sk_node_init2 (00204444) and returns metadata descriptor &g_003471a4.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t * sk_node_alloc2(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t lVar1;
  word_t uVar2;
  
  lVar1 = rt_0036a908(0x28,0x1edb);
  *param_1 = lVar1;
  uVar2 = sk_node_init2((word_t *)(lVar1),(word_t)(param_2),(word_t)(param_3),(word_t)(*(word_t *)((param_4 & 0xfffffffffffffffe) - 8))).lo;
  *(word_t *)(lVar1 + 0x20) = uVar2;
  return (word_t *)&g_003471a4;
}

/* FUN_00204444 @ 0x00204444   (est. sk_node_init2)
 * Ghidra: sk_u128_t FUN_00204444(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Node constructor variant: builds object, allocates a child table (tag 0xaee8), calls rt thunk 00250904. Returns sk_u128_t (lo=&g_003471a8).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t sk_node_init2(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t uVar1;
  word_t lVar2;
  sk_u128_t auVar3;
  
  uVar1 = rt_00027754(param_4);
  lVar2 = rt_00377824(0,uVar1,*(word_t *)(param_3 + 0x10),&g_00611b24,&g_00611b34).lo;
  *param_1 = lVar2;
  lVar2 = *(word_t *)(lVar2 + -8);
  param_1[1] = lVar2;
  lVar2 = rt_0036a908(*(word_t *)(lVar2 + 0x40),0xaee8);
  param_1[2] = lVar2;
  rt_00250904(lVar2,param_2,param_3,param_4);
  auVar3.hi = lVar2;
  auVar3.lo = (word_t)&g_003471a8;
  return auVar3;
}

/* FUN_00204540 @ 0x00204540   (est. sk_find_slot)
 * Ghidra: void FUN_00204540(word_t param_1,word_t param_2,word_t param_3)
 * Find slot: runtime prologue, resolves object, walks with sk_iterate_walk (0020405c), checks branch; success returns, failure panics.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_find_slot(word_t param_1,word_t param_2,word_t param_3)
{

  word_t uVar1;
  word_t uVar2;
  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x8_01;
  sk_fnptr extraout_x9;
  word_t extraout_x16;
  word_t unaff_x30;
  
  rt_0008e518();
  uVar1 = rt_00350a28();
  rt_00351bec(param_3);
  rt_0034c354();
  rt_00351300();
  rt_00377824();
  rt_00348cd0();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034b2f8();
  rt_003524a4();
  sk_iterate_walk();
  rt_00350618();
  rt_00351f40();
  rt_00377bec();
  rt_00310b08();
  rt_0034c5cc();
  rt_00351e78();
  uVar2 = (*extraout_x8_00)();
  rt_003518b8(*(word_t *)(extraout_x16 + 8));
  (*extraout_x8_01)();
  if ((uVar2 & 1) != 0) {
    rt_00354930();
    rt_003508d8(extraout_x8,uVar1);
    (*extraout_x9)();
    rt_0008e500(unaff_x30);
    return;
  }
  rt_00350410();
  rt_003488bc();
  rt_0006f768();
                    /* WARNING: Subroutine does not return */
  rt_00356578();
}

/* FUN_002046a8 @ 0x002046a8   (est. sk_rec_descend)
 * Ghidra: void FUN_002046a8()
 * Recursive descend: runtime prologue, saves stack args, calls sk_desc_node (00204798), then the runtime epilogue. Ends with release.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_rec_descend()
{

  word_t in_x6;
  word_t in_x7;
  word_t extraout_x8;
  word_t extraout_x8_00;
  sk_fnptr extraout_x8_01;
  sk_fnptr extraout_x8_02;
  word_t extraout_x9;
  word_t extraout_x16;
  sk_fnptr pcVar1;
  word_t in_stack_00000038;
  word_t in_stack_00000040;
  word_t in_stack_00000048;
  word_t in_stack_000000b8;
  
  rt_000b4594();
  rt_00359b24();
  rt_0035694c();
  in_stack_00000048 = in_x6;
  rt_0035869c();
  in_stack_00000040 = extraout_x8_00;
  rt_0031b8d0(in_stack_000000b8);
  rt_000777d4();
  (*extraout_x8_01)();
  in_stack_00000038 = in_x7;
  rt_00319a4c(&sk_stack_00000020);
  rt_0034b804();
  pcVar1 = *(sk_fnptr *)(extraout_x16 + 0x10);
  (*pcVar1)();
  rt_00351dcc(&sk_stack_00000020);
  sk_desc_node((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
  rt_003a25d4(in_stack_00000040);
  rt_000026e8(&sk_stack_00000020);
  rt_000bd3a4(extraout_x8);
  (*pcVar1)();
  rt_0034310c(in_stack_000000b8);
  rt_000777d4();
  (*extraout_x8_02)();
  rt_000b45b0(extraout_x9);
  return;
}

/* FUN_00204798 @ 0x00204798   (est. sk_desc_node)
 * Ghidra: void FUN_00204798(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5,
                 word_t param_6,word_t *param_7,word_t *param_8,word_t param_9,word_t param_10)
 * Object-description walker (core): iterates object children via vtable methods (+0x128), emits "N children"/"1 child" strings, recursively walks sub-nodes via sk_desc_children (00205bd0) and sk_desc_sub (00205844). Traps (SoftwareBreakpoint) on depth/carry overflow; panic path noreturn.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_desc_node(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5,
                 word_t param_6,word_t *param_7,word_t *param_8,word_t param_9,word_t param_10)
{

  uint8_t uVar1;
  int iVar2;
  word_t lVar3;
  word_t *puVar4;
  sk_fnptr pcVar5;
  word_t uVar6;
  word_t lVar7;
  char *pcVar8;
  word_t extraout_x1;
  word_t extraout_x1_00;
  word_t extraout_x1_01;
  word_t extraout_x1_02;
  word_t extraout_x1_03;
  word_t extraout_x1_04;
  word_t extraout_x1_05;
  word_t extraout_x1_06;
  word_t extraout_x1_07;
  word_t extraout_x1_08;
  sk_fnptr extraout_x8;
  word_t *unaff_x19;
  word_t uVar9;
  word_t *plVar10;
  word_t lVar11;
  sk_u128_t auVar12;
  sk_u128_t local_158;
  uint8_t auStack_148 [32];
  uint8_t auStack_128 [32];
  uint8_t auStack_108[8];
  word_t *local_100;
  sk_fnptr local_f0;
  word_t local_e8;
  word_t local_d8;
  word_t local_d0;
  word_t uStack_c8;
  word_t local_c0;
  word_t uStack_b8;
  uint8_t local_b0;
  word_t local_a8;
  word_t local_a0;
  word_t uStack_98;
  word_t local_90;
  word_t uStack_88;
  uint8_t local_80;
  word_t local_78;
  word_t *local_70 [2];
  
  lVar3 = *param_7 + -1;
  uVar1 = lVar3 == 0;
  if (*param_7 < 1) {
    return;
  }
  *param_7 = lVar3;
  if (-1 < param_5) {
    lVar3 = param_5;
    if (param_5 != 0) {
      do {
        if (lVar3 == 0) goto L_00204e68;
        rt_00350744(&g_005d021c);
        rt_001a89a8();
        rt_00354da0(param_10);
        rt_00350af4();
        rt_0035359c();
        (*extraout_x8)();
        rt_003a25d4(extraout_x1);
        uVar1 = lVar3 + -1 == 0;
        unaff_x19 = param_8;
        lVar3 = lVar3 + -1;
      } while (!(bool)uVar1);
    }
    rt_00319808(param_1,local_158);
    rt_001edb28(auStack_108,local_158);
    local_70[0] = local_100;
    lVar3 = (**(sk_fnptr *)(*local_100 + 0x128))(*local_100 + 0x128);
    if (lVar3 == 0) {
      rt_00350744(&g_005d3be4);
      rt_001a89a8();
      rt_00351e08();
    }
    else {
      uVar1 = param_6 == 0;
      if (param_6 < 1) {
        puVar4 = &g_005d3be0;
      }
      else {
        puVar4 = &g_005d3bbc;
      }
      rt_001a89a8(puVar4,3,0);
      rt_00351e08();
    }
    pcVar5 = (sk_fnptr)rt_0031b900(param_10);
    rt_0007c1c4();
    rt_00352e78();
    (*pcVar5)();
    rt_003a25d4(unaff_x19);
    rt_0034f030();
    rt_00352e78();
    (*pcVar5)();
    rt_003a25d4(extraout_x1_00);
    if (param_4 != 0) {
      rt_000bd3a4(param_3);
      (*pcVar5)();
      rt_00354ae8();
      rt_00352e78();
      (*pcVar5)();
      rt_003a25d4(extraout_x1_01);
    }
    sk_desc_elements((word_t)(param_1),(word_t)(auStack_108),(word_t)(param_2),(word_t)(0x67b1e8),(word_t)(param_9),(word_t)(param_10));
    uVar9 = *(word_t *)(param_1 + 0x18);
    rt_003508cc();
    uVar6 = rt_0006a4c0();
    uVar6 = rt_003625e4(uVar6,uVar9,1);
    lVar7 = rt_003198cc(uVar6,uVar6);
    if (lVar7 == 0) {
      rt_00319808(param_1,local_158);
      uVar6 = rt_00354d80();
      iVar2 = rt_00365b6c(&local_a8,local_158,0x67b1e8,uVar6,6);
      if (iVar2 != 0) goto L_00204a38;
    }
    else {
      uVar9 = *(word_t *)(param_1 + 0x18);
      rt_003508cc();
      uVar6 = rt_0006a4c0();
      rt_001b68a0(uVar6,uVar9);
      rt_0036b118();
L_00204a38:
      lVar7 = *param_8;
      rt_00350af4();
      rt_001ef7ac();
      local_158.lo = rt_00351db4();
      if (!(bool)uVar1) {
        rt_0034b150();
        rt_00344e54(local_70);
        rt_0036b118(local_e8);
        rt_00355fa0(&g_005d3bdd);
        rt_00354388();
        (*pcVar5)();
        rt_003a25d4(extraout_x1_03);
        rt_003516fc();
        rt_0035a9c8();
        rt_00350744(&g_005d3bc0);
        rt_001a89a8();
        rt_00354388();
        (*pcVar5)();
        uVar6 = extraout_x1_04;
L_00204b08:
        rt_003a25d4(uVar6);
        return;
      }
      uVar6 = *(word_t *)(lVar7 + 0x10);
      rt_0009461c();
      rt_001ef808();
      rt_00355fa0(&g_005d3bdd);
      rt_00354388();
      (*pcVar5)();
      rt_003a25d4(extraout_x1_02);
      local_158.lo = uVar6;
      rt_003516fc();
      rt_0035a9c8();
    }
    rt_00350744(&g_005d3bc0);
    rt_001a89a8();
    rt_00352e78();
    (*pcVar5)();
    rt_003a25d4(extraout_x1_05);
    if (param_6 < 1) {
      rt_0034b150();
      rt_00344e54(local_70);
L_00204d3c:
      rt_0036b118(local_e8);
      return;
    }
    (*local_f0)(&local_d8);
    if (local_d8 != 0) {
      local_a8 = local_d8;
      uStack_98 = uStack_c8;
      local_a0 = local_d0;
      uStack_88 = uStack_b8;
      local_90 = local_c0;
      local_80 = local_b0;
      if (SCARRY8(param_5,2)) {
                    /* WARNING: Does not return */
        pcVar5 = (sk_fnptr)SoftwareBreakpoint(1,0x204ebc);
        (*pcVar5)();
      }
      sk_desc_children((word_t)(&local_a8),(word_t)(param_2),(word_t)(param_5 + 2),(word_t)(param_6 + -1),(word_t)(param_7),(word_t)(param_8),(word_t)(param_9),(word_t)(param_10));
      local_78 = local_a0;
      rt_0034b150();
      rt_00344e54(&local_78);
      rt_0036b118(uStack_88);
    }
    if (-1 < lVar3) {
      plVar10 = (word_t *)local_100[2];
      if (lVar3 == 0) {
        rt_0036b270(plVar10);
      }
      else {
        lVar11 = local_100[3];
        rt_0036b270(plVar10);
        lVar7 = 0;
        do {
          if (*param_7 < 1) {
            rt_0034b150();
            rt_00344e54(local_70);
            rt_0036b118(local_e8);
            lVar11 = param_5 + 4;
            if (SCARRY8(param_5,4)) {
                    /* WARNING: Does not return */
              pcVar5 = (sk_fnptr)SoftwareBreakpoint(1,0x204ec0);
              (*pcVar5)();
            }
            if (lVar11 < 0) goto L_00204eb0;
            goto L_00204d98;
          }
          (**(sk_fnptr *)(*local_100 + 0xe8))(local_158,plVar10,lVar11);
          uVar6 = local_158.hi;
          rt_00310d98(auStack_148,auStack_128);
          iVar2 = rt_003a261c(plVar10);
          if (iVar2 == 0) {
            (**(sk_fnptr *)(*local_100 + 0xf0))(plVar10,lVar11);
            rt_00350fdc();
            rt_0036b118();
            plVar10 = local_100;
          }
          else {
            (**(sk_fnptr *)(*local_100 + 0xf8))(plVar10,lVar11);
          }
          if (SCARRY8(param_5,2)) {
                    /* WARNING: Does not return */
            pcVar5 = (sk_fnptr)SoftwareBreakpoint(1,0x204e78);
            (*pcVar5)();
          }
          lVar7 = lVar7 + 1;
          rt_00350a1c(auStack_128,param_2);
          sk_desc_node((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
          rt_003a25d4(uVar6);
          rt_000026e8(auStack_128);
        } while (lVar3 != lVar7);
      }
      rt_0034b150();
      rt_00344e54(local_70);
      rt_0036b118(plVar10);
      goto L_00204d3c;
    }
  }
L_00204eb0:
  rt_00347da8();
L_00204e6c:
  rt_003504b8();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
  while( true ) {
    rt_00350744(&g_005d021c);
    auVar12 = rt_001a89a8();
    local_158 = auVar12;
    rt_00351744(local_158);
    sk_desc_sub((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
    rt_003a25d4(auVar12.hi);
    lVar11 = lVar11 + -1;
    if (lVar11 == 0) break;
L_00204d98:
    if (lVar11 == 0) goto L_00204e68;
  }
  rt_003567f8();
  rt_00350744();
  rt_001a89a8();
  rt_00352ea8();
  (*pcVar5)();
  rt_003a25d4(extraout_x1_06);
  local_158.lo = lVar3 - lVar7;
  rt_003516fc();
  sk_desc_sub((word_t)(&local_158),(word_t)(param_2),(word_t)(0),(word_t)(0),(word_t)(0));
  if (lVar7 != 0) {
    rt_00356f44();
    rt_00352ea8();
    (*pcVar5)();
    rt_003a25d4(extraout_x1_07);
  }
  if (lVar3 + -1 == lVar7) {
    pcVar8 = sk_str_child_;
    uVar6 = 8;
  }
  else {
    pcVar8 = sk_str_children_;
    uVar6 = 0xb;
  }
  rt_001a89a8(pcVar8,uVar6,1);
  rt_00352ea8();
  (*pcVar5)();
  rt_0036b118(plVar10);
  uVar6 = extraout_x1_08;
  goto L_00204b08;
L_00204e68:
  rt_00348034();
  goto L_00204e6c;
}

/* FUN_00204ec0 @ 0x00204ec0   (est. sk_desc_dispatch)
 * Ghidra: void FUN_00204ec0(word_t param_1,word_t param_2,word_t param_3)
 * Description dispatch: builds a frame via rt_00355018 and calls sk_rec_descend (002046a8) with the frame fields.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_desc_dispatch(word_t param_1,word_t param_2,word_t param_3)
{

  sk_u128_t auVar1;
  
  auVar1 = rt_00355018();
  sk_rec_descend(auVar1.lo,auVar1.hi,auVar1.hi,param_3);
  return;
}

/* FUN_00204f0c @ 0x00204f0c   (est. sk_desc_elements)
 * Ghidra: void FUN_00204f0c(word_t param_1,word_t param_2,uint8_t *param_3,word_t param_4,
                 word_t param_5,word_t param_6)
 * Description element printer: switch on element-count kind (byte at +0x10): case 4/others and 5/6/7 emit "elements", "1 element", "key-value pairs", "members"/"1 member" strings and resolve counts via vtable +0x128. Faithful to the Swift-style reflection dump layer.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_desc_elements(word_t param_1,word_t param_2,uint8_t *param_3,word_t param_4,
                 word_t param_5,word_t param_6)
{

  uint8_t bVar1;
  uint8_t uVar2;
  int iVar3;
  uint8_t *puVar4;
  word_t uVar5;
  char *pcVar6;
  word_t lVar7;
  word_t extraout_x1;
  uint8_t *extraout_x1_00;
  word_t extraout_x1_01;
  word_t extraout_x1_02;
  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x8_01;
  word_t extraout_x8_02;
  word_t extraout_x8_03;
  word_t extraout_x8_04;
  word_t extraout_x8_05;
  sk_fnptr extraout_x8_06;
  word_t extraout_x8_07;
  word_t extraout_x8_08;
  sk_fnptr extraout_x8_09;
  word_t extraout_x8_10;
  sk_fnptr extraout_x8_11;
  uint8_t *extraout_x16;
  word_t extraout_x16_00;
  word_t extraout_x16_01;
  word_t extraout_x16_02;
  word_t extraout_x16_03;
  word_t *unaff_x20;
  uint8_t *puVar8;
  uint32_t uVar9;
  sk_fnptr pcVar10;
  uint8_t *unaff_x23;
  uint8_t *unaff_x24;
  uint8_t *unaff_x25;
  uint8_t *unaff_x27;
  word_t unaff_x30;
  sk_u128_t auVar11;
  sk_u128_t auVar12;
  uint8_t auStack_50 [40];
  
  rt_0008e518();
  rt_00352ce0();
  puVar4 = param_3;
  rt_003561a0();
  rt_00349a68();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_00348abc();
  (*g_00658c00)();
  rt_0034b308();
  (*g_00658c00)();
  rt_0034b4c0();
  bVar1 = *(uint8_t *)(extraout_x1 + 0x10);
  uVar9 = (uint32_t)bVar1;
  if ((uVar9 == 9) || (4 < uVar9 - 3)) {
L_switch4:
    pcVar10 = *(sk_fnptr *)(extraout_x16 + 0x10);
    rt_00350b48();
    (*pcVar10)();
    rt_00352a8c();
    rt_0035a5e4();
    rt_003516f0();
    iVar3 = rt_00365b6c();
    if (iVar3 == 0) {
      rt_00355674();
      rt_00355aa0();
      rt_00344e54(auStack_50);
      rt_00350a34();
      (*pcVar10)();
      rt_00353758();
      rt_0035a5e4();
      rt_003511c0();
      iVar3 = rt_00365b6c();
      puVar4 = unaff_x23;
      if (iVar3 != 0) goto L_0020501c;
      rt_00355674();
      rt_00355a64();
      rt_00344e54(auStack_50);
      rt_0034e55c();
      (*pcVar10)();
      rt_00356fb8();
      rt_0035a5e4();
      rt_00350ad0();
      iVar3 = rt_00365b6c();
      if (iVar3 == 0) {
        rt_00355674();
        rt_00355a2c();
        rt_00344e54(auStack_50);
        if (bVar1 == 9) {
L_00205238:
          auVar11 = rt_00351714();
          rt_002667a8(auVar11.lo,auVar11.hi,param_3,1);
          goto L_00205068;
        }
        if (bVar1 < 2) {
L_00205384:
          sk_boot_cpu(*unaff_x20,1);
          rt_00354f1c();
          rt_0031b900(param_6);
          rt_00351318();
          rt_00350974();
          (*extraout_x8_06)();
        }
        else {
          if (bVar1 != 2) {
            if (bVar1 != 8) goto L_00205238;
            goto L_00205384;
          }
          sk_boot_cpu(*unaff_x20,1);
          rt_0035351c();
          pcVar10 = (sk_fnptr)rt_0031b900(param_6);
          rt_00351648();
          rt_00350974();
          (*pcVar10)();
          rt_003a25d4((word_t)(extraout_x16 + 0x10) & 0xffffffffffff | 0xe3ba000000000000);
          rt_00350518();
          lVar7 = rt_003a0b04();
          if ((lVar7 == 0) || (rt_001e9f14(), extraout_x1_01 == 0)) goto L_00205068;
          rt_003562d4();
          rt_0034fb28();
          rt_001a89a8();
          (*pcVar10)();
          rt_003a25d4(extraout_x1_02);
          rt_0034d758();
          (*pcVar10)();
        }
        rt_003a25d4();
        goto L_00205068;
      }
      rt_00077070(auStack_50,&sk_stack_ffffffffffffffd8);
      rt_0034b440(&sk_stack_ffffffffffffffd8);
      uVar5 = rt_003194f8();
      rt_00351978(uVar5,param_3);
      (*extraout_x8_01)();
    }
    else {
L_0020501c:
      rt_00077070(auStack_50,&sk_stack_ffffffffffffffd8);
      rt_0034b440(&sk_stack_ffffffffffffffd8);
      rt_00027724();
      rt_0034ce58();
      (*extraout_x8_00)();
      rt_003569b4();
      rt_0035053c(param_3,puVar4);
      rt_002678b4();
      rt_003a25d4();
    }
    rt_000026e8(&sk_stack_ffffffffffffffd8);
L_00205068:
    rt_0008e500(unaff_x30);
    return;
  }
  switch(uVar9) {
  default:
    puVar8 = (uint8_t *)unaff_x20[1];
    rt_000027e8();
    puVar4 = (uint8_t *)(**(sk_fnptr *)(extraout_x16_00 + 0x128))();
    uVar2 = puVar4 == (uint8_t *)((word_t)&g_tls_magic + 1);
    if (!(bool)uVar2) {
      rt_003567f8();
      rt_00350744();
      rt_001a89a8();
      rt_00354410();
      rt_003a25d4(0xe000000000000000);
      auVar11 = rt_00356340();
      rt_002364dc(auVar11.lo,auVar11.hi,puVar4);
      rt_00354000();
      rt_0034b824();
      if ((extraout_x8_03 == 0) &&
         ((((word_t)unaff_x24 & ((word_t)puVar8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        rt_003a25d4(puVar8);
        puVar8 = puVar4;
      }
      else {
        if (((word_t)puVar8 >> 0x3d & 1) == 0) {
          rt_0034efc8();
        }
        else if (((word_t)puVar4 >> 0x3d & 1) != 0) {
          rt_00351714();
          rt_0035359c();
          rt_0034b7c8();
          if (!(bool)uVar2) {
            rt_00352350();
            rt_003a25d4();
            rt_003a25d4(puVar4);
            rt_003581c4();
            goto L_00205548;
          }
        }
        auVar11 = rt_00351274();
        rt_002a4c98(auVar11.lo,auVar11.hi,0);
        rt_003a25d4(puVar4);
        puVar4 = puVar8;
        unaff_x25 = unaff_x24;
      }
L_00205548:
      pcVar6 = sk_str_elements_;
      uVar5 = 10;
      break;
    }
    pcVar6 = sk_str__1_element_;
    uVar5 = 0xb;
L_0020520c:
    rt_001a89a8(pcVar6,uVar5,1);
    rt_00355c78();
    goto L_00205634;
  case 4:
    goto L_switch4;
  case 5:
    puVar8 = (uint8_t *)unaff_x20[1];
    rt_000027e8();
    puVar4 = (uint8_t *)(**(sk_fnptr *)(extraout_x16_02 + 0x128))();
    uVar2 = puVar4 == (uint8_t *)((word_t)&g_tls_magic + 1);
    if ((bool)uVar2) {
      pcVar6 = sk_str_1_element;
      uVar5 = 9;
      goto L_0020520c;
    }
    rt_003497ec();
    rt_001a89a8();
    rt_00354410();
    rt_003a25d4(0xe000000000000000);
    auVar11 = rt_00356340();
    rt_002364dc(auVar11.lo,auVar11.hi,puVar4);
    rt_00354000();
    rt_0034b824();
    if ((extraout_x8_04 == 0) &&
       ((((word_t)unaff_x24 & ((word_t)puVar8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      rt_003a25d4(puVar8);
      puVar8 = puVar4;
    }
    else {
      if (((word_t)puVar8 >> 0x3d & 1) == 0) {
        rt_0034efc8();
      }
      else if (((word_t)puVar4 >> 0x3d & 1) != 0) {
        rt_00351714();
        rt_0035359c();
        rt_0034b7c8();
        if (!(bool)uVar2) {
          rt_00352350();
          rt_003a25d4();
          rt_003a25d4(puVar4);
          rt_003581c4();
          goto L_00205588;
        }
      }
      auVar11 = rt_00351274();
      rt_002a4c98(auVar11.lo,auVar11.hi,0);
      rt_003a25d4(puVar4);
      puVar4 = puVar8;
      unaff_x25 = unaff_x24;
    }
L_00205588:
    pcVar6 = sk_str_elements;
    uVar5 = 9;
    break;
  case 6:
    puVar4 = (uint8_t *)unaff_x20[1];
    rt_000027e8();
    puVar8 = (uint8_t *)(**(sk_fnptr *)(extraout_x16_01 + 0x128))();
    uVar2 = puVar8 == (uint8_t *)((word_t)&g_tls_magic + 1);
    if ((bool)uVar2) {
      rt_00355754(sk_str_1_key_value_pair);
      rt_001a89a8();
      unaff_x24 = extraout_x1_00;
    }
    else {
      rt_0006e778(0x12);
      auVar11 = rt_0035abd8();
      rt_003497ec();
      rt_001a89a8();
      rt_00356fd8();
      rt_0034b824();
      if ((extraout_x8_02 == 0) &&
         ((((word_t)extraout_x16 & ((word_t)puVar4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        rt_003a25d4(puVar4);
        unaff_x24 = unaff_x23;
      }
      else {
        if (((word_t)puVar4 >> 0x3d & 1) == 0) {
          rt_0034efc8();
        }
        else if (((word_t)unaff_x23 >> 0x3d & 1) != 0) {
          rt_00351f88();
          rt_0035359c();
          rt_0034b7c8();
          if (!(bool)uVar2) {
            rt_003530bc();
            rt_003a25d4();
            rt_003a25d4();
            unaff_x25 = extraout_x16;
            unaff_x24 = unaff_x27;
            goto L_00205424;
          }
        }
        puVar4 = &sk_stack_ffffffffffffffd8;
        auVar12 = rt_00351274();
        rt_002a4c98(auVar12.lo,auVar12.hi,0);
        rt_003a25d4();
        unaff_x25 = (uint8_t *)auVar11.lo;
        unaff_x24 = (uint8_t *)auVar11.hi;
      }
L_00205424:
      auVar11 = rt_00356340();
      rt_002364dc(auVar11.lo,auVar11.hi,puVar8);
      rt_00355c78();
      rt_0034ddd8();
      if ((extraout_x8_07 == 0) &&
         ((((word_t)unaff_x25 & ((word_t)unaff_x24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        rt_003a25d4(unaff_x24);
        puVar4 = extraout_x16;
      }
      else {
        if (((word_t)unaff_x24 >> 0x3d & 1) == 0) {
          rt_0034dd64();
        }
        else if (((word_t)puVar8 >> 0x3d & 1) != 0) {
          rt_0034ff88();
          rt_0034b1a0();
          if (!(bool)uVar2) {
            rt_003530d8();
            rt_003a25d4();
            rt_003a25d4(puVar8);
            puVar8 = unaff_x25;
            goto L_00205488;
          }
        }
        rt_0034ee38();
        rt_002a4c98();
        rt_003a25d4(puVar8);
        puVar4 = unaff_x25;
        puVar8 = unaff_x24;
      }
L_00205488:
      rt_00355754(sk_str_key_value_pairs);
      rt_001a89a8();
      rt_00356fd8();
      rt_0034d044();
      if ((extraout_x8_08 == 0) &&
         ((((word_t)puVar4 & ((word_t)puVar8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        rt_003a25d4(puVar8);
      }
      else {
        if (((word_t)puVar8 >> 0x3d & 1) == 0) {
          rt_0034efc8();
        }
        else if (((word_t)unaff_x24 >> 0x3d & 1) != 0) {
          rt_00100c38();
          rt_0035359c();
          rt_0034b7c8();
          if (!(bool)uVar2) {
            rt_0035351c();
            rt_003a25d4(puVar8);
            rt_003a25d4(unaff_x24);
            unaff_x24 = puVar4;
            goto L_002054f4;
          }
        }
        auVar11 = rt_00351274();
        rt_002a4c98(auVar11.lo,auVar11.hi,0);
        rt_003a25d4(unaff_x24);
        unaff_x24 = puVar8;
      }
    }
L_002054f4:
    rt_0031b900(param_6);
    rt_0034e044();
    rt_003515fc();
    (*extraout_x8_09)();
    goto L_00205654;
  case 7:
    puVar8 = (uint8_t *)unaff_x20[1];
    rt_000027e8();
    puVar4 = (uint8_t *)(**(sk_fnptr *)(extraout_x16_03 + 0x128))();
    uVar2 = puVar4 == (uint8_t *)((word_t)&g_tls_magic + 1);
    if ((bool)uVar2) {
      pcVar6 = sk_str_1_member;
      uVar5 = 8;
      goto L_0020520c;
    }
    rt_003497ec();
    rt_001a89a8();
    rt_00354410();
    rt_003a25d4(0xe000000000000000);
    auVar11 = rt_00356340();
    rt_002364dc(auVar11.lo,auVar11.hi,puVar4);
    rt_00354000();
    rt_0034b824();
    if ((extraout_x8_05 == 0) &&
       ((((word_t)unaff_x24 & ((word_t)puVar8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      rt_003a25d4(puVar8);
      puVar8 = puVar4;
    }
    else {
      if (((word_t)puVar8 >> 0x3d & 1) == 0) {
        rt_0034efc8();
      }
      else if (((word_t)puVar4 >> 0x3d & 1) != 0) {
        rt_00351714();
        rt_0035359c();
        rt_0034b7c8();
        if (!(bool)uVar2) {
          rt_00352350();
          rt_003a25d4();
          rt_003a25d4(puVar4);
          rt_003581c4();
          goto L_002055c8;
        }
      }
      auVar11 = rt_00351274();
      rt_002a4c98(auVar11.lo,auVar11.hi,0);
      rt_003a25d4(puVar4);
      puVar4 = puVar8;
      unaff_x25 = unaff_x24;
    }
L_002055c8:
    pcVar6 = sk_str_members;
    uVar5 = 8;
  }
  rt_001a89a8(pcVar6,uVar5,1);
  rt_00355c78();
  rt_0034ddd8();
  if ((extraout_x8_10 == 0) &&
     ((((word_t)unaff_x25 & ((word_t)puVar4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    rt_003a25d4(puVar4);
  }
  else {
    if (((word_t)puVar4 >> 0x3d & 1) == 0) {
      rt_0034dd64();
    }
    else if (((word_t)unaff_x24 >> 0x3d & 1) != 0) {
      rt_0034ff88();
      rt_0034b1a0();
      if (!(bool)uVar2) {
        rt_003530d8();
        rt_003a25d4();
        rt_003a25d4();
        unaff_x24 = unaff_x25;
        goto L_00205634;
      }
    }
    rt_0034ee38();
    rt_002a4c98();
    rt_003a25d4();
    unaff_x24 = puVar8;
  }
L_00205634:
  rt_0031b900(param_6);
  rt_0034db88();
  rt_003515fc();
  (*extraout_x8_11)();
L_00205654:
  rt_0008e500(unaff_x24,unaff_x30);
  rt_003a25d4();
  return;
}

/* FUN_00205844 @ 0x00205844   (est. sk_desc_sub)
 * Ghidra: void FUN_00205844(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
 * Description sub-walker: resolves a child list, loops with rt_00365b6c branches, builds a frame and emits; fallback releases.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_desc_sub(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
{

  int iVar1;
  word_t uVar2;
  word_t uVar3;
  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x8_01;
  sk_fnptr extraout_x8_02;
  sk_fnptr extraout_x8_03;
  sk_fnptr extraout_x8_04;
  word_t extraout_x16;
  sk_fnptr pcVar4;
  word_t unaff_x24;
  word_t unaff_x30;
  sk_u128_t auVar5;
  word_t local_60 [3];
  word_t local_48;
  uint8_t local_30[8];
  word_t local_28;
  word_t local_18;
  word_t local_10;
  
  rt_0008e518();
  uVar2 = param_3;
  rt_00355bdc();
  rt_00349720();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_003493c4();
  rt_0034d5a8();
  (*g_00658c00)();
  rt_0034aea8();
  (*g_00658c00)();
  rt_0034a464();
  (*g_00658c00)();
  rt_0034b540();
  (*g_00658c00)();
  rt_0034ba68();
  local_18 = uVar2;
  rt_00319a4c(local_30);
  pcVar4 = *(sk_fnptr *)(extraout_x16 + 0x10);
  rt_0035119c();
  (*pcVar4)();
  rt_0006a4c0(local_30,local_18);
  rt_000dbc98();
  rt_003625e4();
  iVar1 = rt_003629b4();
  rt_000026e8(local_30);
  if (iVar1 == 0) {
    rt_0035119c();
    (*pcVar4)();
    rt_00353d64();
    iVar1 = rt_00356fcc(local_30);
    if (iVar1 != 0) {
      rt_0031b900(param_5);
      uVar2 = rt_00351318();
      rt_003534ec(uVar2,local_28);
      (*extraout_x8_01)();
      rt_003a25d4(local_28);
      goto L_00205a18;
    }
    rt_0034feb0();
    (*pcVar4)();
    rt_00356fb8();
    rt_00355bf4();
    rt_00351b38();
    iVar1 = rt_00365b6c();
    if (iVar1 == 0) {
      rt_0034fd6c();
      rt_00355a2c();
      rt_00344e54(local_60);
      rt_00350edc();
      (*pcVar4)();
      rt_00353758();
      rt_00355bf4();
      rt_00351a20();
      iVar1 = rt_00365b6c();
      if (iVar1 == 0) {
        rt_0034fd6c();
        rt_00355a64();
        rt_00344e54(local_60);
        auVar5 = rt_0008e388();
        uVar2 = param_3;
        (*pcVar4)(auVar5.lo,auVar5.hi,param_3);
        rt_00352a8c();
        rt_00355bf4();
        rt_00350548();
        iVar1 = rt_00365b6c();
        if (iVar1 == 0) {
          rt_0034fd6c();
          rt_00355aa0();
          rt_00344e54(local_60);
          local_48 = param_3;
          rt_00319a4c(local_60);
          rt_0035119c();
          (*pcVar4)();
          rt_0035a1e8();
          uVar2 = rt_001edb28();
          rt_00358dd0(uVar2,local_30);
          rt_002667a8();
          local_60[0] = local_28;
          rt_0034b150();
          rt_00344e54(local_60);
          rt_0036b118(local_10);
          goto L_00205a18;
        }
        rt_00358fdc();
        rt_0034f714(local_30);
        uVar3 = rt_00027724(local_10);
        rt_0008e388(uVar3);
        (*extraout_x8_04)();
        rt_003569b4();
      }
      else {
        rt_00358fdc();
        rt_0034f714(local_30);
        uVar3 = rt_00027724(local_10);
        rt_0008e388(uVar3);
        (*extraout_x8_03)();
        rt_003569b4();
      }
      rt_00352a4c(unaff_x24,uVar2);
      goto L_002059ac;
    }
    rt_00358fdc();
    rt_0034f714(local_30);
    uVar2 = rt_003194f8(local_10);
    rt_00351ba0(uVar2,unaff_x24);
    (*extraout_x8_02)();
  }
  else {
    auVar5 = rt_00350a70();
    (*pcVar4)(auVar5.lo,auVar5.hi,param_3);
    rt_00352a8c();
    rt_0035a5d8();
    rt_00353214();
    rt_00365b6c();
    rt_0034f714(local_30);
    uVar2 = rt_00027724(local_10);
    rt_0008e388(uVar2);
    (*extraout_x8_00)();
    rt_003569b4();
L_002059ac:
    rt_002678b4();
    rt_003a25d4(param_3);
  }
  rt_000026e8(local_30);
L_00205a18:
  rt_0008e500(unaff_x30);
  return;
}

/* FUN_00205bd0 @ 0x00205bd0   (est. sk_desc_children)
 * Ghidra: void FUN_00205bd0(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t *param_5,
                 word_t param_6,word_t param_7,word_t param_8)
 * Description children walker: recursively describes object children; decrements a depth budget (*param_5), emits "child"/"children"/"super" strings, recurses via sk_desc_children (itself) and sk_desc_sub (00205844). Traps on carry overflow; panic path noreturn.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_desc_children(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t *param_5,
                 word_t param_6,word_t param_7,word_t param_8)
{

  int iVar1;
  word_t lVar2;
  word_t *puVar3;
  sk_fnptr pcVar4;
  word_t uVar5;
  char *pcVar6;
  word_t extraout_x1;
  word_t extraout_x1_00;
  word_t extraout_x1_01;
  word_t extraout_x1_02;
  word_t extraout_x1_03;
  word_t extraout_x1_04;
  word_t extraout_x1_05;
  sk_fnptr extraout_x8;
  word_t lVar7;
  word_t *unaff_x21;
  word_t unaff_x22;
  word_t *unaff_x23;
  word_t *plVar8;
  word_t lVar9;
  word_t *plVar10;
  sk_u128_t auVar11;
  word_t local_120;
  word_t uStack_118;
  uint8_t auStack_110 [32];
  uint8_t auStack_f0 [32];
  word_t local_d0;
  word_t local_c8;
  word_t uStack_c0;
  word_t local_b8;
  word_t uStack_b0;
  uint8_t local_a8;
  word_t local_a0;
  word_t local_98;
  word_t uStack_90;
  word_t local_88;
  word_t uStack_80;
  uint8_t local_78;
  word_t local_70 [2];
  
  if (*param_5 < 1) {
    return;
  }
  *param_5 = *param_5 + -1;
  if (-1 < param_3) {
    rt_0035089c();
    if (param_3 != 0) {
      unaff_x21 = &g_005d021c;
      lVar2 = param_3;
      do {
        if (lVar2 == 0) goto L_00206044;
        rt_00350744(&g_005d021c);
        rt_001a89a8();
        rt_00354da0(param_8);
        rt_003508b4();
        rt_0035433c();
        (*extraout_x8)();
        rt_003a25d4(extraout_x1);
        lVar2 = lVar2 + -1;
      } while (lVar2 != 0);
    }
    plVar10 = (word_t *)unaff_x23[1];
    lVar2 = (**(sk_fnptr *)(*plVar10 + 0x128))();
    if (lVar2 == 0) {
      auVar11 = (sk_u128_t){ .lo = rt_00350744(&g_005d3be4), .hi = 0 };
    }
    else {
      if (param_4 < 1) {
        puVar3 = &g_005d3be0;
      }
      else {
        puVar3 = &g_005d3bbc;
      }
      auVar11.hi = 3;
      auVar11.lo = (word_t)puVar3;
    }
    rt_001a89a8(auVar11.lo,auVar11.hi);
    rt_00350b90();
    pcVar4 = (sk_fnptr)rt_0031b900(param_8);
    rt_0006b6f4();
    rt_0035433c();
    (*pcVar4)();
    rt_003a25d4(unaff_x21);
    rt_0035940c(sk_str_super_);
    rt_0035433c();
    (*pcVar4)();
    rt_003a25d4(extraout_x1_00);
    local_120 = *unaff_x23;
    uVar5 = rt_00354d80();
    rt_00353bc4(&local_120,unaff_x22,uVar5);
    sk_desc_recurse();
    rt_00350744(&g_005d3bc0);
    rt_001a89a8();
    rt_0035433c();
    (*pcVar4)();
    rt_003a25d4(extraout_x1_01);
    if (param_4 < 1) {
      return;
    }
    (*(sk_fnptr)unaff_x23[3])(&local_d0);
    if (local_d0 != 0) {
      local_a0 = local_d0;
      uStack_90 = uStack_c0;
      local_98 = local_c8;
      uStack_80 = uStack_b0;
      local_88 = local_b8;
      local_78 = local_a8;
      if (SCARRY8(param_3,2)) {
                    /* WARNING: Does not return */
        pcVar4 = (sk_fnptr)SoftwareBreakpoint(1,0x20609c);
        (*pcVar4)();
      }
      sk_desc_children((word_t)(&local_a0),(word_t)(unaff_x22),(word_t)(param_3 + 2),(word_t)(param_4 + -1),(word_t *)(param_5),(word_t)(param_6),(word_t)(param_7),(word_t)(param_8));
      local_70[0] = local_98;
      rt_0034b150();
      rt_00344e54(local_70);
      rt_0036b118(uStack_80);
    }
    if (-1 < lVar2) {
      if (lVar2 == 0) {
        return;
      }
      plVar8 = (word_t *)plVar10[2];
      lVar9 = plVar10[3];
      rt_0036b270(plVar8);
      lVar7 = 0;
      while (0 < *param_5) {
        (**(sk_fnptr *)(*plVar10 + 0xe8))(&local_120,plVar8,lVar9);
        uVar5 = uStack_118;
        rt_00310d98(auStack_110,auStack_f0);
        iVar1 = rt_003a261c(plVar8);
        if (iVar1 == 0) {
          (**(sk_fnptr *)(*plVar10 + 0xf0))(plVar8,lVar9);
          rt_0035351c();
          rt_0036b118(plVar8);
          plVar8 = plVar10;
        }
        else {
          (**(sk_fnptr *)(*plVar10 + 0xf8))(plVar8,lVar9);
        }
        if (SCARRY8(param_3,2)) {
                    /* WARNING: Does not return */
          pcVar4 = (sk_fnptr)SoftwareBreakpoint(1,0x206054);
          (*pcVar4)();
        }
        lVar7 = lVar7 + 1;
        rt_00351b78(auStack_f0,unaff_x22);
        sk_desc_node((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
        rt_003a25d4(uVar5);
        rt_000026e8(auStack_f0);
        if (lVar2 == lVar7) {
          rt_0036b118(plVar8);
          return;
        }
      }
      lVar9 = param_3 + 4;
      if (SCARRY8(param_3,4)) {
                    /* WARNING: Does not return */
        pcVar4 = (sk_fnptr)SoftwareBreakpoint(1,0x2060a0);
        (*pcVar4)();
      }
      if (-1 < lVar9) {
        while (lVar9 != 0) {
          rt_00350744(&g_005d021c);
          rt_001a89a8();
          rt_00352ea8();
          (*pcVar4)();
          rt_003a25d4(extraout_x1_02);
          lVar9 = lVar9 + -1;
          if (lVar9 == 0) {
            rt_003567f8();
            rt_00350744();
            rt_001a89a8();
            rt_00352ea8();
            (*pcVar4)();
            rt_003a25d4(extraout_x1_03);
            local_120 = lVar2 - lVar7;
            rt_003516fc();
            sk_desc_sub((word_t)(&local_120),(word_t)(unaff_x22),(word_t)(0),(word_t)(0),(word_t)(0));
            if (lVar7 != 0) {
              rt_00356f44();
              rt_00352ea8();
              (*pcVar4)();
              rt_003a25d4(extraout_x1_04);
            }
            if (lVar2 + -1 == lVar7) {
              pcVar6 = sk_str_child_;
              uVar5 = 8;
            }
            else {
              pcVar6 = sk_str_children_;
              uVar5 = 0xb;
            }
            rt_001a89a8(pcVar6,uVar5,1);
            rt_00352ea8();
            (*pcVar4)();
            rt_0036b118(plVar8);
            rt_003a25d4(extraout_x1_05);
            return;
          }
        }
L_00206044:
        rt_00348034();
        goto L_00206048;
      }
    }
  }
  rt_00347da8();
L_00206048:
  rt_003504b8();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_002060a0 @ 0x002060a0   (est. sk_desc_slot)
 * Ghidra: void FUN_002060a0(word_t param_1)
 * Description slot helper: releases the value at object+0x10 (rt_0036b270).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_desc_slot(word_t param_1)
{

  rt_0036b270(*(word_t *)(param_1 + 0x10));
  return;
}

/* FUN_002060d4 @ 0x002060d4   (est. sk_desc_recurse)
 * Ghidra: void FUN_002060d4()
 * Description recursion helper: a three-branch runtime walk (rt_00365b6c == 0 sequence) building frames and choosing tail paths; invoked by sk_desc_children and sk_boot_cold.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_desc_recurse()
{

  int iVar1;
  word_t uVar2;
  word_t extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x8_01;
  word_t extraout_x16;
  sk_fnptr pcVar3;
  word_t unaff_x30;
  word_t local_60 [3];
  uint8_t auStack_30[8];
  word_t local_28;
  word_t local_10;
  
  rt_0008e518();
  uVar2 = rt_0034d654();
  rt_00349720();
  (*g_00658c00)(*(word_t *)(extraout_x8 + 0x40));
  rt_00348abc();
  (*g_00658c00)();
  rt_0034a464();
  (*g_00658c00)();
  rt_0034ba68();
  pcVar3 = *(sk_fnptr *)(extraout_x16 + 0x10);
  rt_00350a70();
  (*pcVar3)();
  rt_00352a8c();
  rt_00355bf4();
  rt_00353214();
  iVar1 = rt_00365b6c();
  if (iVar1 == 0) {
    rt_0034fd6c();
    rt_00355aa0();
    rt_00344e54(local_60);
    rt_0034feb0();
    (*pcVar3)();
    rt_00353758();
    rt_00355bf4();
    rt_00351b38();
    iVar1 = rt_00365b6c();
    if (iVar1 != 0) goto L_002061bc;
    rt_0034fd6c();
    rt_00355a64();
    rt_00344e54(local_60);
    rt_00350edc();
    (*pcVar3)();
    rt_00356fb8();
    rt_00355bf4();
    rt_00351a20();
    iVar1 = rt_00365b6c();
    if (iVar1 == 0) {
      rt_0034fd6c();
      rt_00355a2c();
      rt_00344e54(local_60);
      rt_00319a4c(local_60);
      rt_0035119c();
      (*pcVar3)();
      rt_0035a1e8();
      rt_001edb28();
      rt_002667a8(uVar2,auStack_30);
      local_60[0] = local_28;
      rt_0034b150();
      rt_00344e54(local_60);
      rt_0036b118(local_10);
      goto L_00206204;
    }
    rt_00358fdc();
    rt_0034b440(auStack_30);
    uVar2 = rt_003194f8();
    rt_0034b778(uVar2);
    rt_00351978();
    (*extraout_x8_01)();
  }
  else {
L_002061bc:
    rt_00358fdc();
    rt_0034b440(auStack_30);
    rt_00027724();
    rt_0034ce58();
    (*extraout_x8_00)();
    rt_003569b4();
    rt_00350aac();
    rt_002678b4();
    rt_003a25d4();
  }
  rt_000026e8(auStack_30);
L_00206204:
  rt_0008e500(unaff_x30);
  return;
}

/* FUN_002062e4 @ 0x002062e4   (est. sk_vt_overridden_a)
 * Ghidra: void FUN_002062e4(void)
 * Vtable override stub A: jumps to shared vt teardown rt_001b5a88.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_overridden_a(void)
{

  rt_001b5a88();
  return;
}

/* FUN_002062e8 @ 0x002062e8   (est. sk_vt_overridden_b)
 * Ghidra: void FUN_002062e8(void)
 * Vtable override stub B: jumps to shared vt teardown rt_001b5a88.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_overridden_b(void)
{

  rt_001b5a88();
  return;
}

/* FUN_002062fc @ 0x002062fc   (est. sk_vt_overridden_c)
 * Ghidra: void FUN_002062fc(void)
 * Vtable override stub C: jumps to shared vt teardown rt_001b5784.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_overridden_c(void)
{

  rt_001b5784();
  return;
}

/* FUN_00206300 @ 0x00206300   (est. sk_vt_overridden_d)
 * Ghidra: void FUN_00206300(void)
 * Vtable override stub D: jumps to shared vt teardown rt_001b5784.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_overridden_d(void)
{

  rt_001b5784();
  return;
}

/* FUN_00206314 @ 0x00206314   (est. sk_vt_overridden_e)
 * Ghidra: void FUN_00206314(void)
 * Vtable override stub E: jumps to thunk rt_00284424.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_overridden_e(void)
{

  rt_00284424();
  return;
}

/* FUN_00206318 @ 0x00206318   (est. sk_vt_overridden_f)
 * Ghidra: void FUN_00206318(void)
 * Vtable override stub F: jumps to thunk rt_00284424.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_overridden_f(void)
{

  rt_00284424();
  return;
}

/* FUN_0020632c @ 0x0020632c   (est. sk_assert_fmt_a)
 * Ghidra: void FUN_0020632c(word_t param_1)
 * Assertion helper: resolves a diagnostic (rt_00376820 with g_004e956c) and calls rt_001a0194. Likely assert-failure registration.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_fmt_a(word_t param_1)
{

  word_t uVar1;
  
  uVar1 = rt_00376820(&g_004e956c,param_1).lo;
  rt_001a0194(param_1,uVar1);
  return;
}

/* FUN_00206374 @ 0x00206374   (est. sk_assert_fmt_b)
 * Ghidra: void FUN_00206374(word_t param_1)
 * Assertion helper variant: resolves diagnostic and calls rt_001e088c.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_fmt_b(word_t param_1)
{

  word_t uVar1;
  
  uVar1 = rt_00376820(&g_004e956c,param_1).lo;
  rt_001e088c(param_1,uVar1);
  return;
}

/* FUN_002063bc @ 0x002063bc   (est. sk_assert_fail)
 * Ghidra: void FUN_002063bc(void)
 * Assertion failure (noreturn): enables assert context (rt_003488bc(1)), then panics via rt_00353b34 + rt_001afe4c.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_fail(void)
{

  word_t extraout_x1;
  word_t uVar1;
  
  rt_003488bc(1);
  uVar1 = extraout_x1;
  rt_0034f674();
  rt_00353b34(uVar1);
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_00206408 @ 0x00206408   (est. sk_assert_fail2)
 * Ghidra: void FUN_00206408(void)
 * Assertion failure variant (noreturn): rt_003488bc(1) + panic.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_fail2(void)
{

  word_t extraout_x1;
  word_t uVar1;
  
  rt_003488bc(1);
  uVar1 = extraout_x1;
  rt_0034f674();
  rt_00353b34(uVar1);
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_00206454 @ 0x00206454   (est. sk_assert_empty)
 * Ghidra: sk_u128_t FUN_00206454(void)
 * Assertion failure variant (noreturn): rt_00348638(1) + panic (rt_001afe4c).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t sk_assert_empty(void)
{

  rt_00348638(1);
  rt_00349de8();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_00206494 @ 0x00206494   (est. sk_assert_empty2)
 * Ghidra: void FUN_00206494(void)
 * Assertion failure variant (noreturn): rt_00348638(1) + panic.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_empty2(void)
{

  rt_00348638(1);
  rt_00349de8();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_002064d4 @ 0x002064d4   (est. sk_assert_both)
 * Ghidra: word_t FUN_002064d4()
 * Assert both-zero check: calls sk_assert_empty (00206454); if the returned pair is nonzero, panics (noreturn); else returns.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_assert_both()
{

  sk_u128_t auVar1;
  
  auVar1 = sk_assert_empty();
  if (auVar1.lo != 0 || auVar1.hi != 0) {
    rt_00348638(1);
    rt_00349de8();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  return 0;
}

/* FUN_002064e4 @ 0x002064e4   (est. sk_assert_ze_pair)
 * Ghidra: void FUN_002064e4(word_t param_1,word_t param_2)
 * Assert zero-pair: if either param is nonzero, panic (noreturn). Invariant guard.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_ze_pair(word_t param_1,word_t param_2)
{

  if (param_1 != 0 || param_2 != 0) {
    rt_00348638(1);
    rt_00349de8();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  return;
}

/* FUN_00206520 @ 0x00206520   (est. sk_assert_ze_pair2)
 * Ghidra: void FUN_00206520(word_t param_1,word_t param_2)
 * Assert zero-pair variant: if either param is nonzero, panic (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_ze_pair2(word_t param_1,word_t param_2)
{

  if (param_1 != 0 || param_2 != 0) {
    rt_00348638(1);
    rt_00349de8();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  return;
}

/* FUN_0020655c @ 0x0020655c   (est. sk_pair_store)
 * Ghidra: sk_fnptr * FUN_0020655c(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Pair store: writes a 4-word record (params into [0..3]) and returns the callback sk_pair_check_a (002065a4). Constructor/accessor pattern.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_fnptr * sk_pair_store(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t unaff_x20;
  
  param_1[2] = param_4;
  param_1[3] = unaff_x20;
  *param_1 = param_2;
  param_1[1] = param_3;
  rt_00106e3c();
  sk_assert_ze_pair((word_t)(0),(word_t)(0));
  return sk_pair_check_a;
}

/* FUN_002065a4 @ 0x002065a4   (est. sk_pair_check_a)
 * Ghidra: void FUN_002065a4(word_t *param_1)
 * Pair check: asserts both record words are zero via sk_assert_ze_pair2 (00206520).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_pair_check_a(word_t *param_1)
{

  sk_assert_ze_pair2((word_t)(*param_1),(word_t)(param_1[1]));
  return;
}

/* FUN_002065a8 @ 0x002065a8   (est. sk_pair_check_b)
 * Ghidra: void FUN_002065a8(word_t *param_1)
 * Pair check variant: asserts both record words zero.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_pair_check_b(word_t *param_1)
{

  sk_assert_ze_pair2((word_t)(*param_1),(word_t)(param_1[1]));
  return;
}

/* FUN_002065c0 @ 0x002065c0   (est. sk_assert_nz_pair)
 * Ghidra: word_t FUN_002065c0(word_t param_1,word_t param_2)
 * Assert nonzero-pair: panics if either param nonzero (noreturn), else returns 0.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_assert_nz_pair(word_t param_1,word_t param_2)
{

  if (param_1 != 0 || param_2 != 0) {
    rt_00348638(1);
    rt_00349de8();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  return 0;
}

/* FUN_00206600 @ 0x00206600   (est. sk_assert_nz_triple)
 * Ghidra: sk_u128_t FUN_00206600()
 * Assert nonzero-triple: panics if param_1 or param_3 nonzero; returns sk_u128_t encoding (param_2 != 0) in the hi word.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t sk_assert_nz_triple(word_t param_1,word_t param_2,word_t param_3)
{

  if (param_1 != 0 || param_3 != 0) {
    rt_00348638(1);
    rt_00349de8();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  return (sk_u128_t){ .lo=0, .hi=(word_t)(param_2 != 0) };
}

/* FUN_00206648 @ 0x00206648   (est. sk_assert_eq_case)
 * Ghidra: word_t FUN_00206648(word_t param_1,word_t param_2)
 * Assert equal-case: panics unless both params are zero (noreturn); returns 0 when both zero.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_assert_eq_case(word_t param_1,word_t param_2)
{

  if (param_1 == 0) {
    if (param_2 == 0) {
      return 0;
    }
    rt_003488bc(1);
    rt_0034f674();
  }
  else {
    rt_003488bc(1);
    rt_0034f674();
  }
  rt_00353b34();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_002066b4 @ 0x002066b4   (est. sk_assert_pair_eq)
 * Ghidra: void FUN_002066b4(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Assert pair-equal: computes a pair via rt_00319230/rt_00376820 and compares against saved regs; mismatch panics (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_pair_eq(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t uVar1;
  word_t uVar2;
  word_t unaff_x19;
  word_t unaff_x20;
  word_t local_40;
  word_t local_38;
  
  if (param_1 == 0) {
    uVar1 = rt_00350a28();
    uVar1 = rt_00319230(uVar1,param_4);
    uVar2 = rt_00350834();
    uVar2 = rt_00376820(uVar2,uVar1).lo;
    rt_00348e9c(uVar2,uVar2);
    rt_0019fa60(&local_40,uVar1);
    if ((unaff_x20 == local_40) && (unaff_x19 == local_38)) {
      return;
    }
    rt_003488bc(1);
    rt_0034f674();
  }
  else {
    rt_003488bc(1);
    rt_0034f674();
  }
  rt_00353b34();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_00206770 @ 0x00206770   (est. sk_node_validate)
 * Ghidra: void FUN_00206770(void)
 * Node validate: runtime prologue, runs a branch check (rt_0014ae44), on success validates a node via sk code path and returns the branch bit; ends with runtime call.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_node_validate(void)
{

  uint32_t uVar1;
  sk_fnptr pcVar2;
  word_t uVar3;
  word_t lVar4;
  word_t in_x3;
  word_t unaff_x19;
  word_t unaff_x21;
  sk_fnptr unaff_x23;
  word_t unaff_x30;
  
  rt_00084220();
  rt_00356c84();
  rt_0008409c();
  rt_0035125c(in_x3);
  pcVar2 = (sk_fnptr)rt_0014ae44();
  rt_003502a8();
  uVar3 = (*pcVar2)();
  if ((uVar3 & 1) == 0) {
    uVar1 = 0;
  }
  else {
    rt_00350798();
    lVar4 = (*unaff_x23)();
    rt_00351100(unaff_x21 + *(int32_t *)(lVar4 + 0x24),unaff_x19 + *(int32_t *)(lVar4 + 0x24));
    uVar1 = (*pcVar2)();
    uVar1 = uVar1 & 1;
  }
  rt_00084234(uVar1,unaff_x30);
  return;
}

/* FUN_00206818 @ 0x00206818   (est. sk_assert_pairs_eq)
 * Ghidra: void FUN_00206818(void)
 * Assert pairs-equal: builds two pairs via rt_00319230/rt_00376820/rt_0019fa60, compares to saved regs; mismatch panics (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_pairs_eq(void)
{

  word_t uVar1;
  word_t uVar2;
  word_t unaff_x19;
  word_t unaff_x20;
  word_t unaff_x22;
  word_t unaff_x24;
  word_t unaff_x30;
  word_t in_stack_00000020;
  word_t in_stack_00000028;
  
  rt_00041138();
  rt_00077888();
  rt_00355d9c();
  rt_00353540();
  uVar1 = rt_00319230();
  uVar2 = rt_00350834();
  rt_00376820(uVar2,uVar1);
  rt_00348e9c();
  rt_0008e388(&sk_stack_00000020);
  rt_0019fa60();
  if ((unaff_x24 == in_stack_00000020) && (unaff_x22 == in_stack_00000028)) {
    rt_00348e9c();
    rt_0008e388(&sk_stack_00000020);
    rt_0019fa60();
    if ((unaff_x20 == in_stack_00000020) && (unaff_x19 == in_stack_00000028)) {
      rt_0035847c(unaff_x30);
      return;
    }
    rt_003488bc(1);
    rt_0034f674();
  }
  else {
    rt_003488bc(1);
    rt_0034f674();
  }
  rt_00353b34();
                    /* WARNING: Subroutine does not return */
  rt_001afe4c();
}

/* FUN_002068fc @ 0x002068fc   (est. sk_assert_empty3)
 * Ghidra: void FUN_002068fc(void)
 * Assert failure forwarding (noreturn): jumps to sk_assert_empty2 (00206494).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_empty3(void)
{

                    /* WARNING: Subroutine does not return */
  sk_assert_empty2();
}

/* FUN_00206900 @ 0x00206900   (est. sk_assert_empty4)
 * Ghidra: void FUN_00206900(void)
 * Assert failure forwarding (noreturn): jumps to sk_assert_empty2 (00206494).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_empty4(void)
{

                    /* WARNING: Subroutine does not return */
  sk_assert_empty2();
}

/* FUN_00206910 @ 0x00206910   (est. sk_pair_check_c)
 * Ghidra: void FUN_00206910(word_t param_1,word_t *param_2)
 * Pair check: asserts the two record words are zero via sk_assert_ze_pair2 (00206520).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_pair_check_c(word_t param_1,word_t *param_2)
{

  sk_assert_ze_pair2((word_t)(*param_2),(word_t)(param_2[1]));
  return;
}

/* FUN_00206928 @ 0x00206928   (est. sk_pair_store2)
 * Ghidra: sk_fnptr * FUN_00206928(word_t *param_1,word_t *param_2,word_t param_3)
 * Pair store variant: writes a 4-word record from a source pair and returns callback sk_pair_check_d (00206970).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_fnptr * sk_pair_store2(word_t *param_1,word_t *param_2,word_t param_3)
{

  word_t uVar1;
  word_t unaff_x20;
  
  *param_1 = unaff_x20;
  param_1[1] = param_3;
  uVar1 = param_2[1];
  param_1[2] = *param_2;
  param_1[3] = uVar1;
  sk_assert_ze_pair((word_t)(0),(word_t)(0));
  return sk_pair_check_d;
}

/* FUN_00206970 @ 0x00206970   (est. sk_pair_check_d)
 * Ghidra: void FUN_00206970(word_t param_1)
 * Pair check: asserts record words at +0x10/+0x18 are zero via sk_assert_ze_pair2.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_pair_check_d(word_t param_1)
{

  sk_assert_ze_pair2((word_t)(*(word_t *)(param_1 + 0x10)),(word_t)(*(word_t *)(param_1 + 0x18)));
  return;
}

/* FUN_00206974 @ 0x00206974   (est. sk_pair_check_e)
 * Ghidra: void FUN_00206974(word_t param_1)
 * Pair check variant: asserts record words at +0x10/+0x18 are zero.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_pair_check_e(word_t param_1)
{

  sk_assert_ze_pair2((word_t)(*(word_t *)(param_1 + 0x10)),(word_t)(*(word_t *)(param_1 + 0x18)));
  return;
}

/* FUN_0020698c @ 0x0020698c   (est. sk_assert_fmt_c)
 * Ghidra: void FUN_0020698c(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
 * Assertion helper: resolves diagnostic (g_004e9550) and calls rt_0019f1ec.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_fmt_c(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
{

  word_t uVar1;
  
  uVar1 = rt_00376820(&g_004e9550,param_4).lo;
  rt_0019f1ec(param_1,param_2,param_3,param_4,uVar1,param_5);
  return;
}

/* FUN_00206a0c @ 0x00206a0c   (est. sk_assert_clear_a)
 * Ghidra: void FUN_00206a0c(void)
 * Assert-clear helper: runs sk_assert_fail2 (00206408), a runtime call, sk_assert_nz_pair (002065c0), then clears the object slot (*x19=0).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_clear_a(void)
{

  word_t *unaff_x19;
  
  sk_assert_fail2();
  rt_00351124();
  sk_assert_nz_pair((word_t)(0),(word_t)(0));
  *unaff_x19 = 0;
  return;
}

/* FUN_00206a10 @ 0x00206a10   (est. sk_assert_clear_b)
 * Ghidra: void FUN_00206a10(void)
 * Assert-clear helper variant: same as 00206a0c.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_clear_b(void)
{

  word_t *unaff_x19;
  
  sk_assert_fail2();
  rt_00351124();
  sk_assert_nz_pair((word_t)(0),(word_t)(0));
  *unaff_x19 = 0;
  return;
}

/* FUN_00206a44 @ 0x00206a44   (est. sk_assert_clear_c)
 * Ghidra: void FUN_00206a44(void)
 * Assert-clear helper variant: runtime call + sk_assert_nz_triple (00206600), clears slot and byte.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_clear_c(void)
{

  uint8_t extraout_w1;
  word_t *unaff_x19;
  
  rt_0034c434();
  sk_assert_nz_triple((word_t)(0),(word_t)(0),(word_t)(0));
  *unaff_x19 = 0;
  *(uint8_t *)(unaff_x19 + 1) = extraout_w1;
  return;
}

/* FUN_00206a70 @ 0x00206a70   (est. sk_assert_clear_d)
 * Ghidra: word_t FUN_00206a70(word_t *param_1,word_t *param_2)
 * Assert-clear: asserts the two record words via sk_assert_eq_case (00206648), returns 0.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_assert_clear_d(word_t *param_1,word_t *param_2)
{

  sk_assert_eq_case((word_t)(*param_1),(word_t)(*param_2));
  return 0;
}

/* FUN_00206a74 @ 0x00206a74   (est. sk_assert_clear_e)
 * Ghidra: word_t FUN_00206a74(word_t *param_1,word_t *param_2)
 * Assert-clear variant: same as 00206a70.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_assert_clear_e(word_t *param_1,word_t *param_2)
{

  sk_assert_eq_case((word_t)(*param_1),(word_t)(*param_2));
  return 0;
}

/* FUN_00206a94 @ 0x00206a94   (est. sk_pair_alloc)
 * Ghidra: word_t * FUN_00206a94(word_t *param_1,word_t *param_2,word_t param_3)
 * Pair-node allocator (0x28 bytes, tag 0x23bc): initializes via sk_assert_both (002064d4) and returns metadata descriptor &g_003471a4.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t * sk_pair_alloc(word_t *param_1,word_t *param_2,word_t param_3)
{

  word_t lVar1;
  word_t uVar2;
  
  lVar1 = rt_0036a908(0x28,0x23bc);
  *param_1 = lVar1;
  uVar2 = sk_assert_both(lVar1,*param_2,*(word_t *)(param_3 + 0x10));
  *(word_t *)(lVar1 + 0x20) = uVar2;
  return &g_003471a4;
}

/* FUN_00206b0c @ 0x00206b0c   (est. sk_assert_fmt_d)
 * Ghidra: void FUN_00206b0c(word_t param_1,word_t param_2)
 * Assertion helper: resolves diagnostic (g_004e9518) and calls rt_0019fa60 with a return site 0x6720e8.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_assert_fmt_d(word_t param_1,word_t param_2)
{

  word_t uVar1;
  
  uVar1 = rt_00376820(&g_004e9518,param_2).lo;
  rt_0019fa60(param_1,param_2,uVar1,0x6720e8);
  return;
}

/* FUN_00206bac @ 0x00206bac   (est. sk_slot_clear_a)
 * Ghidra: void FUN_00206bac(word_t param_1,word_t param_2,word_t param_3)
 * Slot clear: runtime preamble (sk_assert_fail 002063bc), builds via rt_00349830, dispatches, then clears a slot (offset via rt_0031b778).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_slot_clear_a(word_t param_1,word_t param_2,word_t param_3)
{

  word_t uVar1;
  word_t lVar2;
  word_t extraout_x8;
  word_t extraout_x16;
  
  sk_assert_fail();
  rt_0034b430();
  uVar1 = rt_00349830();
  rt_00377824(uVar1,param_3);
  rt_00349530();
  (**(sk_fnptr *)(extraout_x16 + 0x20))(extraout_x8);
  rt_0034e70c();
  lVar2 = rt_0031b778();
  *(word_t *)(extraout_x8 + *(int32_t *)(lVar2 + 0x24)) = 0;
  return;
}

/* FUN_00206bb0 @ 0x00206bb0   (est. sk_slot_clear_b)
 * Ghidra: void FUN_00206bb0(word_t param_1,word_t param_2,word_t param_3)
 * Slot clear variant: same structure as 00206bac.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_slot_clear_b(word_t param_1,word_t param_2,word_t param_3)
{

  word_t uVar1;
  word_t lVar2;
  word_t extraout_x8;
  word_t extraout_x16;
  
  sk_assert_fail();
  rt_0034b430();
  uVar1 = rt_00349830();
  rt_00377824(uVar1,param_3);
  rt_00349530();
  (**(sk_fnptr *)(extraout_x16 + 0x20))(extraout_x8);
  rt_0034e70c();
  lVar2 = rt_0031b778();
  *(word_t *)(extraout_x8 + *(int32_t *)(lVar2 + 0x24)) = 0;
  return;
}

/* FUN_00206c30 @ 0x00206c30   (est. sk_table_iter)
 * Ghidra: void FUN_00206c30()
 * Table iterator: runtime preamble, calls a callback (via unaff_x19), resolves, then calls rt_00280bc4 (object walk) and finishes.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_table_iter()
{

  word_t uVar1;
  sk_fnptr extraout_x9;
  sk_fnptr unaff_x19;
  word_t unaff_x30;
  
  rt_00084220();
  rt_00350b54();
  rt_0034f3b4(0);
  rt_00377824();
  rt_00351f10();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034aee4();
  (*unaff_x19)();
  rt_00350b24();
  rt_00350560();
  (*extraout_x9)();
  uVar1 = rt_003539d8();
  rt_00351584(uVar1,0);
  rt_00280bc4();
  rt_00084234(unaff_x30);
  return;
}

/* FUN_00206cf8 @ 0x00206cf8   (est. sk_table_method)
 * Ghidra: void FUN_00206cf8(word_t param_1,word_t param_2)
 * Table method call: resolves a method pointer via rt_00027788 and calls it with object+0x10 and param_2 (unrecovered jumptable artifact).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_table_method(word_t param_1,word_t param_2)
{

  sk_fnptr UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = (sk_fnptr)rt_00027788(param_2);
                    /* WARNING: Could not recover jumptable at 0x00206d3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(*(word_t *)(param_1 + 0x10),param_2);
  return;
}

/* FUN_00206d88 @ 0x00206d88   (est. sk_table_lookup)
 * Ghidra: word_t FUN_00206d88(word_t param_1,word_t param_2,word_t param_3)
 * Table lookup: resolves object via rt_00377824/rt_00377bec, walks with rt_0014ae44, on miss reads a slot via rt_0032d3e0, else dispatches via rt_00027788. Returns the resolved value.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_table_lookup(word_t param_1,word_t param_2,word_t param_3)
{

  word_t lVar1;
  sk_fnptr pcVar2;
  word_t uVar3;
  word_t uVar4;
  word_t lVar5;
  word_t extraout_x8;
  word_t uVar6;
  uint8_t *puVar7;
  
  uVar6 = *(word_t *)(param_2 + 0x10);
  lVar1 = rt_00377824(0,param_3,uVar6,&g_0060e208,&g_0060e230).lo;
  lVar5 = *(word_t *)(lVar1 + -8);
  (*g_00658c00)(*(word_t *)(lVar5 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar7 = &sk_stack_ffffffffffffffa0 + -extraout_x8;
  pcVar2 = (sk_fnptr)rt_00310924(param_3);
  (*pcVar2)(puVar7,uVar6,param_3);
  rt_00377bec(param_3,uVar6,lVar1,&g_0060e208,&g_0060e218);
  uVar3 = rt_00027754();
  pcVar2 = (sk_fnptr)rt_0014ae44();
  uVar4 = (*pcVar2)(param_1,puVar7,lVar1,uVar3);
  (**(sk_fnptr *)(lVar5 + 8))(puVar7,lVar1);
  if ((uVar4 & 1) == 0) {
    lVar1 = rt_0032d3e0(0,uVar6,param_3);
    uVar3 = *(word_t *)(param_1 + *(int32_t *)(lVar1 + 0x24));
  }
  else {
    pcVar2 = (sk_fnptr)rt_00027788(param_3);
    uVar3 = (*pcVar2)(uVar6,param_3);
  }
  return uVar3;
}

/* FUN_00206f18 @ 0x00206f18   (est. sk_table_range)
 * Ghidra: word_t FUN_00206f18(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Table range check: walks two objects with rt_0014ae44, on both-miss computes a signed difference (rt_0032d3e0 slot), trapping on borrow overflow; else dispatches via rt_00310cd4. Returns the delta.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_table_range(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t lVar1;
  sk_fnptr pcVar2;
  word_t uVar3;
  sk_fnptr pcVar4;
  word_t uVar5;
  word_t lVar6;
  word_t extraout_x8;
  word_t uVar7;
  sk_fnptr pcVar8;
  uint8_t *puVar9;
  uint8_t auStack_80[8];
  word_t local_78;
  
  uVar7 = *(word_t *)(param_3 + 0x10);
  lVar1 = rt_00377824(0,param_4,uVar7,&g_0060e208,&g_0060e230).lo;
  lVar6 = *(word_t *)(lVar1 + -8);
  (*g_00658c00)(*(word_t *)(lVar6 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar9 = auStack_80 + -extraout_x8;
  pcVar2 = (sk_fnptr)rt_00310924(param_4);
  (*pcVar2)(puVar9,uVar7,param_4);
  rt_00377bec(param_4,uVar7,lVar1,&g_0060e208,&g_0060e218);
  uVar3 = rt_00027754();
  pcVar4 = (sk_fnptr)rt_0014ae44();
  local_78 = param_1;
  uVar5 = (*pcVar4)(param_1,puVar9,lVar1,uVar3);
  pcVar8 = *(sk_fnptr *)(lVar6 + 8);
  (*pcVar8)(puVar9,lVar1);
  if ((uVar5 & 1) == 0) {
    (*pcVar2)(puVar9,uVar7,param_4);
    uVar5 = (*pcVar4)(param_2,puVar9,lVar1,uVar3);
    (*pcVar8)(puVar9,lVar1);
    if ((uVar5 & 1) == 0) {
      lVar1 = rt_0032d3e0(0,uVar7,param_4);
      lVar6 = *(word_t *)(param_2 + *(int32_t *)(lVar1 + 0x24));
      lVar1 = *(word_t *)(local_78 + *(int32_t *)(lVar1 + 0x24));
      if (!SBORROW8(lVar6,lVar1)) {
        return lVar6 - lVar1;
      }
                    /* WARNING: Does not return */
      pcVar2 = (sk_fnptr)SoftwareBreakpoint(1,0x20711c);
      (*pcVar2)();
    }
  }
  pcVar2 = (sk_fnptr)rt_00310cd4(param_4);
  lVar1 = (*pcVar2)(local_78,param_2,uVar7,param_4);
  return lVar1;
}

/* FUN_0020711c @ 0x0020711c   (est. sk_table_insert1)
 * Ghidra: void FUN_0020711c(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Table insert (single): resolves object, walks via rt_00319658, reads slot via rt_0032d3e0, calls rt_00280bc4 with value+1; traps on carry overflow.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_table_insert1(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t lVar1;
  sk_fnptr pcVar2;
  word_t extraout_x8;
  word_t uVar3;
  
  uVar3 = *(word_t *)(param_3 + 0x10);
  lVar1 = rt_00377824(0,param_4,uVar3,&g_0060e208,&g_0060e230).lo;
  (*g_00658c00)(*(word_t *)(*(word_t *)(lVar1 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  pcVar2 = (sk_fnptr)rt_00319658(param_4);
  (*pcVar2)(&sk_stack_ffffffffffffffc0 + -extraout_x8,param_2,uVar3,param_4);
  lVar1 = rt_0032d3e0(0,uVar3,param_4);
  lVar1 = *(word_t *)(param_2 + *(int32_t *)(lVar1 + 0x24));
  if (!SCARRY8(lVar1,1)) {
    rt_00280bc4(param_1,&sk_stack_ffffffffffffffc0 + -extraout_x8,lVar1 + 1,uVar3,param_4,
                 &g_0060e208,&g_0060e230,rt_0032d3e0);
    return;
  }
                    /* WARNING: Does not return */
  pcVar2 = (sk_fnptr)SoftwareBreakpoint(1,0x207234);
  (*pcVar2)();
}

/* FUN_00207234 @ 0x00207234   (est. sk_table_insert_n)
 * Ghidra: void FUN_00207234(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5)
 * Table insert (n): resolves object, walks via rt_0031afcc, reads slot, adds param_3, calls rt_00280bc4; traps on carry overflow.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_table_insert_n(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5)
{

  word_t lVar1;
  sk_fnptr pcVar2;
  word_t extraout_x8;
  word_t uVar3;
  
  uVar3 = *(word_t *)(param_4 + 0x10);
  lVar1 = rt_00377824(0,param_5,uVar3,&g_0060e208,&g_0060e230).lo;
  (*g_00658c00)(*(word_t *)(*(word_t *)(lVar1 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  pcVar2 = (sk_fnptr)rt_0031afcc(param_5);
  (*pcVar2)(&sk_stack_ffffffffffffffb0 + -extraout_x8,param_2,param_3,uVar3,param_5);
  if (param_3 < 0) {
    lVar1 = sk_table_lookup((word_t)(param_2),(word_t)(param_4),(word_t)(param_5));
  }
  else {
    lVar1 = rt_0032d3e0(0,uVar3,param_5);
    lVar1 = *(word_t *)(param_2 + *(int32_t *)(lVar1 + 0x24));
  }
  if (!SCARRY8(lVar1,param_3)) {
    rt_00280bc4(param_1,&sk_stack_ffffffffffffffb0 + -extraout_x8,lVar1 + param_3,uVar3,param_5,
                 &g_0060e208,&g_0060e230,rt_0032d3e0);
    return;
  }
                    /* WARNING: Does not return */
  pcVar2 = (sk_fnptr)SoftwareBreakpoint(1,0x207378);
  (*pcVar2)();
}

/* FUN_00207378 @ 0x00207378   (est. sk_table_update)
 * Ghidra: void FUN_00207378(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5,
                 word_t param_6)
 * Table update: builds two object frames, compares via rt_000839f8; on match dispatches and returns 1, else updates via rt_00280bc4 and returns 0.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_table_update(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5,
                 word_t param_6)
{

  int iVar1;
  word_t lVar2;
  word_t lVar3;
  sk_fnptr pcVar4;
  word_t lVar5;
  word_t extraout_x8;
  word_t lVar6;
  word_t extraout_x8_00;
  word_t uVar7;
  word_t uVar8;
  uint8_t *puVar9;
  uint8_t auStack_90[8];
  word_t local_88;
  word_t local_80;
  word_t local_78;
  
  uVar8 = *(word_t *)(param_5 + 0x10);
  local_88 = param_5;
  local_78 = param_4;
  lVar2 = rt_00377824(0xff,param_6,uVar8,&g_0060e208,&g_0060e230).lo;
  lVar3 = rt_00310d68(0,lVar2);
  lVar5 = *(word_t *)(lVar3 + -8);
  (*g_00658c00)(*(word_t *)(lVar5 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar9 = auStack_90 + -extraout_x8;
  lVar6 = *(word_t *)(lVar2 + -8);
  (*g_00658c00)(*(word_t *)(lVar6 + 0x40) + 0xfU & 0xfffffffffffffff0);
  pcVar4 = (sk_fnptr)rt_003192d8(param_6);
  local_80 = param_2;
  (*pcVar4)(puVar9,param_2,param_3,local_78,uVar8,param_6);
  iVar1 = rt_000839f8(puVar9,1,lVar2);
  if (iVar1 == 1) {
    (**(sk_fnptr *)(lVar5 + 8))(puVar9,lVar3);
    uVar7 = 1;
  }
  else {
    (**(sk_fnptr *)(lVar6 + 0x20))((word_t)puVar9 - extraout_x8_00,puVar9,lVar2);
    if (param_3 < 0) {
      lVar2 = sk_table_lookup((word_t)(local_80),(word_t)(local_88),(word_t)(param_6));
    }
    else {
      lVar2 = rt_0032d3e0(0,uVar8,param_6);
      lVar2 = *(word_t *)(local_80 + *(int32_t *)(lVar2 + 0x24));
    }
    if (SCARRY8(lVar2,param_3)) {
                    /* WARNING: Does not return */
      pcVar4 = (sk_fnptr)SoftwareBreakpoint(1,0x2075e0);
      (*pcVar4)();
    }
    rt_00280bc4(param_1,(word_t)puVar9 - extraout_x8_00,lVar2 + param_3,uVar8,param_6,&g_0060e208,
                 &g_0060e230,rt_0032d3e0);
    uVar7 = 0;
  }
  uVar8 = rt_0032d3e0(0,uVar8,param_6);
  rt_000839d8(param_1,uVar7,1,uVar8);
  return;
}

/* FUN_002075e0 @ 0x002075e0   (est. sk_index_lookup)
 * Ghidra: word_t FUN_002075e0(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Index lookup: walks object via rt_000277b8/rt_00310e20, on success resolves slot via rt_0032d3e0 and returns it; else panics (noreturn) with "Fatal error"/"Index out of bounds"/"Swift EnumeratedSequence" strings.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t sk_index_lookup(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t lVar1;
  sk_fnptr pcVar2;
  word_t uVar3;
  word_t uVar4;
  sk_fnptr pcVar5;
  word_t lVar6;
  word_t lVar7;
  word_t extraout_x8;
  word_t uVar8;
  word_t uVar9;
  uint8_t *puVar10;
  sk_u128_t auVar11;
  uint8_t auStack_b0[8];
  word_t uStack_a8;
  uint32_t auStack_a0 [4];
  uint8_t auStack_90[8];
  word_t local_88;
  uint8_t auStack_80 [32];
  
  uVar8 = *(word_t *)(param_3 + 0x10);
  local_88 = param_1;
  lVar1 = rt_00377824(0,param_4,uVar8,&g_0060e208,&g_0060e230).lo;
  lVar7 = *(word_t *)(lVar1 + -8);
  (*g_00658c00)(*(word_t *)(lVar7 + 0x40) + 0xfU & 0xfffffffffffffff0);
  lVar6 = -extraout_x8;
  puVar10 = auStack_90 + lVar6;
  pcVar2 = (sk_fnptr)rt_000277b8(param_4);
  (*pcVar2)(puVar10,uVar8,param_4);
  uVar3 = rt_00377bec(param_4,uVar8,lVar1,&g_0060e208,&g_0060e218);
  pcVar2 = (sk_fnptr)rt_00310e20();
  uVar4 = (*pcVar2)(puVar10,param_2,lVar1,uVar3);
  pcVar2 = *(sk_fnptr *)(lVar7 + 8);
  (*pcVar2)(puVar10,lVar1);
  if ((uVar4 & 1) != 0) {
    pcVar5 = (sk_fnptr)rt_00310924(param_4);
    (*pcVar5)(puVar10,uVar8,param_4);
    pcVar5 = (sk_fnptr)rt_0016186c(uVar3);
    uVar4 = (*pcVar5)(param_2,puVar10,lVar1,uVar3);
    (*pcVar2)(puVar10,lVar1);
    if ((uVar4 & 1) != 0) {
      lVar6 = rt_0032d3e0(0,uVar8,param_4);
      uVar9 = *(word_t *)(param_2 + *(int32_t *)(lVar6 + 0x24));
      pcVar2 = (sk_fnptr)rt_000277e8(param_4);
      auVar11 = (*pcVar2)(auStack_80,param_2,uVar8,param_4);
      uVar3 = rt_00027754(param_4);
      lVar6 = rt_00377824(0,uVar3,uVar8,&g_00611b24,&g_00611b34).lo;
      (**(sk_fnptr *)(*(word_t *)(lVar6 + -8) + 0x10))(local_88,auVar11.hi,lVar6);
      (*auVar11.lo)(auStack_80,0);
      return uVar9;
    }
  }
  *(uint32_t *)((word_t)auStack_a0 + lVar6) = 1;
  *(word_t *)((word_t)&uStack_a8 + lVar6) = 0xca;
  auStack_b0[lVar6] = 2;
                    /* WARNING: Subroutine does not return */
  rt_001afe4c(sk_str_Fatal_error,0xb,2,sk_str_Index_out_of_bounds,0x13,2,
               sk_str_Swift_EnumeratedSequence_swift,0x1e);
}

/* FUN_002078a8 @ 0x002078a8   (est. sk_index_clear_a)
 * Ghidra: void FUN_002078a8(word_t param_1,word_t param_2)
 * Index clear: calls sk_table_iter (00206c30) with resolved object and callback rt_000277b8.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_index_clear_a(word_t param_1,word_t param_2)
{

  sk_table_iter(param_1,*(word_t *)((param_2 & 0xfffffffffffffffe) - 8),rt_000277b8);
  return;
}

/* FUN_002078d8 @ 0x002078d8   (est. sk_index_clear_b)
 * Ghidra: void FUN_002078d8(word_t param_1,word_t param_2)
 * Index clear variant: sk_table_iter with callback rt_00310924.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_index_clear_b(word_t param_1,word_t param_2)
{

  sk_table_iter(param_1,*(word_t *)((param_2 & 0xfffffffffffffffe) - 8),rt_00310924);
  return;
}

/* FUN_002078dc @ 0x002078dc   (est. sk_index_clear_c)
 * Ghidra: void FUN_002078dc(word_t param_1,word_t param_2)
 * Index clear variant: sk_table_iter with callback rt_00310924.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_index_clear_c(word_t param_1,word_t param_2)
{

  sk_table_iter(param_1,*(word_t *)((param_2 & 0xfffffffffffffffe) - 8),rt_00310924);
  return;
}

/* FUN_0020790c @ 0x0020790c   (est. sk_table_alloc)
 * Ghidra: sk_u128_t FUN_0020790c(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Table allocator (0x40 bytes, tag 0xad9a): builds an object, allocates a child table, initializes via sk_table_alloc_node (00207ac8), stores, returns sk_u128_t with destructor sk_table_free (00207a70).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t sk_table_alloc(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t lVar1;
  word_t uVar2;
  word_t lVar3;
  word_t lVar4;
  word_t *puVar5;
  word_t lVar6;
  word_t uVar7;
  sk_u128_t auVar8;
  
  lVar1 = rt_0036a908(0x40,0xad9a);
  *param_1 = lVar1;
  uVar7 = *(word_t *)((param_4 & 0xfffffffffffffffe) - 8);
  uVar2 = rt_00027754(uVar7);
  lVar3 = rt_00377824(0xff,uVar2,*(word_t *)(param_3 + 0x10),&g_00611b24,&g_00611b34).lo;
  lVar4 = rt_003722e4(0,0x677880,lVar3,sk_str_offset_element,0).lo;
  *(word_t *)(lVar1 + 0x20) = lVar4;
  lVar6 = *(word_t *)(lVar4 + -8);
  *(word_t *)(lVar1 + 0x28) = lVar6;
  puVar5 = (word_t *)rt_0036a908(*(word_t *)(lVar6 + 0x40),0xad9a);
  *(word_t **)(lVar1 + 0x30) = puVar5;
  auVar8 = sk_table_alloc_node((word_t)(lVar1),(word_t)(param_2),(word_t)(param_3),(word_t)(uVar7));
  *(word_t *)(lVar1 + 0x38) = auVar8.lo;
  *puVar5 = auVar8.hi;
  (**(sk_fnptr *)(*(word_t *)(lVar3 + -8) + 0x10))
            ((word_t)puVar5 + (word_t)*(int32_t *)(lVar4 + 0x30),param_3,lVar3);
  auVar8.hi = (word_t)puVar5;
  auVar8.lo = sk_table_free;
  return auVar8;
}

/* FUN_00207a70 @ 0x00207a70   (est. sk_table_free)
 * Ghidra: void FUN_00207a70(void)
 * Table destructor: releases the table child and object (rt_0007c1c4, thunk rt_00012568).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_table_free(void)
{

  word_t uVar1;
  sk_fnptr extraout_x8;
  sk_fnptr extraout_x9;
  word_t unaff_x20;
  
  rt_00358c74();
  (*extraout_x9)();
  uVar1 = *(word_t *)(unaff_x20 + 0x30);
  rt_0007c1c4(*(word_t *)(unaff_x20 + 0x38));
  (*extraout_x8)();
  rt_00012568(uVar1);
  rt_00012568();
  return;
}

/* FUN_00207ac8 @ 0x00207ac8   (est. sk_table_alloc_node)
 * Ghidra: sk_u128_t FUN_00207ac8(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Table-node allocator: builds object, allocates a child slot (rt_0036a908), initializes via sk_index_lookup (002075e0), returns sk_u128_t with destructor sk_table_free_node (00207bd8).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t sk_table_alloc_node(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t uVar1;
  word_t lVar2;
  word_t *puVar3;
  word_t lVar4;
  sk_u128_t auVar5;
  
  uVar1 = rt_00027754(param_4);
  uVar1 = rt_00377824(0xff,uVar1,*(word_t *)(param_3 + 0x10),&g_00611b24,&g_00611b34).lo;
  lVar2 = rt_003722e4(0,0x677880,uVar1,sk_str_offset_element,0).lo;
  *param_1 = lVar2;
  lVar4 = *(word_t *)(lVar2 + -8);
  param_1[1] = lVar4;
  puVar3 = (word_t *)rt_0036a908(*(word_t *)(lVar4 + 0x40),&g_0000fc9d);
  param_1[2] = (word_t)puVar3;
  uVar1 = sk_index_lookup((word_t)((word_t)puVar3 + (word_t)*(int32_t *)(lVar2 + 0x30)),(word_t)(param_2),(word_t)(param_3),(word_t)(param_4));
  *puVar3 = uVar1;
  auVar5.hi = uVar1;
  auVar5.lo = sk_table_free_node;
  return auVar5;
}

/* FUN_00207bd8 @ 0x00207bd8   (est. sk_table_free_node)
 * Ghidra: void FUN_00207bd8(word_t *param_1)
 * Table-node destructor: releases record (rt_00353c00), thunk release.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_table_free_node(word_t *param_1)
{

  word_t uVar1;
  sk_fnptr extraout_x9;
  
  uVar1 = param_1[2];
  rt_00353c00(param_1[1],param_1,*param_1);
  (*extraout_x9)();
  rt_00012568(uVar1);
  return;
}

/* FUN_00207ca0 @ 0x00207ca0   (est. sk_index_test)
 * Ghidra: uint32_t FUN_00207ca0(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Index test: builds object via rt_00377824/rt_00377bec and tests via rt_0014ae44, returning the branch bit & 1.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
uint32_t sk_index_test(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  uint32_t uVar1;
  word_t uVar2;
  word_t uVar3;
  sk_fnptr pcVar4;
  
  uVar2 = rt_00377824(0,param_4,param_3,&g_0060e208,&g_0060e230).lo;
  rt_00377bec(param_4,param_3,uVar2,&g_0060e208,&g_0060e218);
  uVar3 = rt_00027754();
  pcVar4 = (sk_fnptr)rt_0014ae44();
  uVar1 = (*pcVar4)(param_1,param_2,uVar2,uVar3);
  return uVar1 & 1;
}

/* FUN_00207d4c @ 0x00207d4c   (est. sk_index_test2)
 * Ghidra: uint32_t FUN_00207d4c(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Index test variant: tests via rt_0016186c, returns bit & 1.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
uint32_t sk_index_test2(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  uint32_t uVar1;
  word_t uVar2;
  word_t uVar3;
  sk_fnptr pcVar4;
  
  uVar2 = rt_00377824(0,param_4,param_3,&g_0060e208,&g_0060e230).lo;
  uVar3 = rt_00377bec(param_4,param_3,uVar2,&g_0060e208,&g_0060e218);
  pcVar4 = (sk_fnptr)rt_0016186c();
  uVar1 = (*pcVar4)(param_1,param_2,uVar2,uVar3);
  return uVar1 & 1;
}

/* FUN_00207e0c @ 0x00207e0c   (est. sk_index_decr)
 * Ghidra: void FUN_00207e0c(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Index decrement: builds object, walks via rt_0031e104, reads slot, calls rt_00280bc4 with value-1; traps on borrow overflow (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_index_decr(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t uVar1;
  word_t uVar2;
  word_t lVar3;
  sk_fnptr pcVar4;
  word_t extraout_x8;
  word_t uVar5;
  
  uVar1 = rt_00027754(param_4);
  uVar2 = rt_00027754();
  uVar5 = *(word_t *)(param_3 + 0x10);
  lVar3 = rt_00377824(0,uVar2,uVar5,&g_0060e208,&g_0060e230).lo;
  (*g_00658c00)(*(word_t *)(*(word_t *)(lVar3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  pcVar4 = (sk_fnptr)rt_0031e104(uVar1);
  (*pcVar4)(&sk_stack_ffffffffffffffb0 + -extraout_x8,param_2,uVar5,uVar1);
  lVar3 = sk_table_lookup((word_t)(param_2),(word_t)(param_3),(word_t)(uVar2));
  if (!SBORROW8(lVar3,1)) {
    rt_00280bc4(param_1,&sk_stack_ffffffffffffffb0 + -extraout_x8,lVar3 + -1,uVar5,uVar2,
                 &g_0060e208,&g_0060e230,rt_0032d3e0);
    return;
  }
                    /* WARNING: Does not return */
  pcVar4 = (sk_fnptr)SoftwareBreakpoint(1,0x207f38);
  (*pcVar4)();
}

/* FUN_00207f44 @ 0x00207f44   (est. sk_index_decr2)
 * Ghidra: void FUN_00207f44(word_t param_1,word_t param_2,word_t param_3)
 * Index decrement wrapper: builds object via rt_0032d3e0, calls sk_index_decr (00207e0c).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_index_decr2(word_t param_1,word_t param_2,word_t param_3)
{

  word_t uVar1;
  word_t lVar2;
  word_t lVar3;
  word_t extraout_x8;
  word_t uVar4;
  word_t uVar5;
  uint8_t *puVar6;
  
  uVar4 = *(word_t *)((param_3 & 0xfffffffffffffffe) - 8);
  uVar5 = *(word_t *)(param_2 + 0x10);
  rt_00027754(uVar4);
  uVar1 = rt_00027754();
  lVar2 = rt_0032d3e0(0,uVar5,uVar1);
  lVar3 = *(word_t *)(lVar2 + -8);
  (*g_00658c00)(*(word_t *)(lVar3 + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar6 = &sk_stack_ffffffffffffffb0 + -extraout_x8;
  (**(sk_fnptr *)(lVar3 + 0x20))(puVar6,param_1,lVar2);
  sk_index_decr((word_t)(param_1),(word_t)(puVar6),(word_t)(param_2),(word_t)(uVar4));
  (**(sk_fnptr *)(lVar3 + 8))(puVar6,lVar2);
  return;
}

/* FUN_002080a8 @ 0x002080a8   (est. sk_rt_wrap_a)
 * Ghidra: void FUN_002080a8(void)
 * Runtime wrap A: sequence of runtime calls ending in an indirect dispatch. Low-semantic-value shim.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_rt_wrap_a(void)
{

  sk_fnptr extraout_x8;
  
  rt_0035921c();
  rt_00358174();
  rt_00027724();
  rt_000777d4();
  (*extraout_x8)();
  return;
}

/* FUN_002080ec @ 0x002080ec   (est. sk_rt_wrap_b)
 * Ghidra: void FUN_002080ec(void)
 * Runtime wrap B: runtime call sequence + indirect dispatch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_rt_wrap_b(void)
{

  sk_fnptr extraout_x8;
  
  rt_0035921c();
  rt_00358174();
  rt_00083a18();
  rt_000777d4();
  (*extraout_x8)();
  return;
}

/* FUN_00208130 @ 0x00208130   (est. sk_rt_wrap_c)
 * Ghidra: void FUN_00208130(void)
 * Runtime wrap C: runtime call sequence + indirect dispatch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_rt_wrap_c(void)
{

  sk_fnptr extraout_x8;
  
  rt_0035921c();
  rt_00358174();
  rt_0008da6c();
  rt_000777d4();
  (*extraout_x8)();
  return;
}

/* FUN_00208174 @ 0x00208174   (est. sk_boot_cold)
 * Ghidra: void FUN_00208174(void)
 * Boot cold path: resolves boot configuration (rt_00358374), selects an entry path (rt_003a25d4 / rt_002a4c98) based on a branch, dispatches sk_desc_recurse (002060d4), then runs a runtime finalize and panics (noreturn via rt_001afa84). Decompiler lost several unreachable blocks; reconstructed from the recovered flow.
 * Confidence: low
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_boot_cold(void)
{

  word_t uVar1;
  uint8_t in_ZR;
  word_t uVar2;
  word_t uVar3;
  word_t uVar4;
  word_t uVar5;
  word_t extraout_x8;
  word_t extraout_x8_00;
  word_t extraout_x8_01;
  word_t unaff_x23;
  word_t uVar6;
  sk_u128_t auVar7;
  sk_u128_t auVar8;
  word_t local_78;
  word_t local_70;
  word_t uStack_68;
  word_t local_60;
  word_t uVar9;
  
  uVar2 = rt_00358374();
  auVar7 = rt_0006e778(0x1d);
  uVar9 = auVar7.hi;
  local_60 = auVar7.lo;
  uVar3 = rt_0034f064();
  if ((extraout_x8 == 0) && (((uVar3 & (uVar9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    uVar6 = 0x2081dc;
    auVar7 = rt_003a25d4(uVar9);
    local_60 = 0xd00000000000001b;
    uVar9 = 0x80000000005cf600;
  }
  else {
    in_ZR = 1;
    uVar6 = 0x208234;
    auVar7 = rt_002a4c98(0xd00000000000001b,0x80000000005cf600,0,0x1b);
  }
  uVar5 = local_60;
  local_78 = 0;
  local_70 = 0xe000000000000000;
  uStack_68 = uVar2;
  rt_0034a210(auVar7.lo,auVar7.hi,uVar6);
  auVar7 = rt_00002534();
  uVar2 = rt_00353d64(0x208270,auVar7.hi,auVar7.lo);
  rt_0034895c(uVar2);
  sk_desc_recurse(&uStack_68,&local_78);
  uVar1 = local_70;
  uVar3 = local_78;
  auVar7 = rt_0034a274(0x208298);
  uVar4 = auVar7.lo;
  if ((extraout_x8_00 == 0) && (((uVar5 & (uVar9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    uVar2 = 0x2082bc;
    rt_003a25d4(uVar9);
    local_60 = uVar3;
    unaff_x23 = uVar1;
  }
  else {
    if ((uVar9 >> 0x3d & 1) == 0) {
      auVar7 = rt_0034ced8(uVar3 & 0xffffffffffff,uVar4);
      uVar4 = auVar7.lo;
    }
    else if ((uVar1 >> 0x3d & 1) != 0) {
      uVar5 = uVar4;
      auVar7 = rt_0007c1c4();
      auVar8 = rt_0034b89c(auVar7.lo,auVar7.hi,uVar3);
      auVar7.hi = auVar8.hi;
      auVar7.lo = uVar5;
      uVar4 = auVar8.lo;
      if (!(bool)in_ZR) {
        rt_00354f1c(uVar4,auVar8.hi,uVar5);
        rt_003a25d4(uVar9);
        uVar2 = 0x208408;
        rt_003a25d4(uVar1);
        local_60 = uVar5;
        goto L_00208330;
      }
    }
    auVar7 = rt_00100efc(uVar4,auVar7.hi,auVar7.lo);
    rt_002a4c98(auVar7.lo,auVar7.hi,0);
    uVar2 = 0x20832c;
    rt_003a25d4(uVar1);
    unaff_x23 = uVar9;
  }
L_00208330:
  uVar3 = local_60;
  auVar7 = rt_0034f98c(local_60 & 0xffffffffffff,uVar2);
  uVar2 = auVar7.lo;
  if ((extraout_x8_01 == 0) && (((uVar3 & (unaff_x23 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    uVar6 = 0x208354;
    uVar2 = rt_003a25d4(unaff_x23).lo;
  }
  else {
    if ((unaff_x23 >> 0x3d & 1) != 0) {
      auVar7 = rt_00100efc(uVar2,auVar7.hi,uVar2);
      auVar7 = rt_0034b7c8(auVar7.lo,auVar7.hi,0,0xe000000000000000);
      if (!(bool)in_ZR) {
        rt_00351a50(auVar7.lo,auVar7.hi,uVar2);
        uVar6 = 0x2083ac;
        uVar2 = rt_003a25d4(unaff_x23).lo;
        goto L_002083ac;
      }
    }
    uVar6 = 0x208390;
    uVar2 = rt_00353ad8();
  }
L_002083ac:
  rt_00350d94(0xfe,uVar2,uVar6);
  rt_0006f768();
                    /* WARNING: Subroutine does not return */
  rt_001afa84();
}

/* FUN_00208418 @ 0x00208418   (est. sk_boot_cpu)
 * Ghidra: void FUN_00208418()
 * Boot per-CPU path: runtime check (rt_00361528), on error panics; resolves via rt_002a218c and branches to one of two teardown continuations.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_boot_cpu()
{

  word_t lVar1;
  word_t extraout_x1;
  
  rt_00361528();
  if (extraout_x1 < 0) {
    rt_0034846c();
                    /* WARNING: Subroutine does not return */
    rt_001afe4c();
  }
  rt_00351e08();
  lVar1 = rt_002a218c();
  if (-1 < lVar1) {
    rt_0034f9fc();
    rt_002a2698();
    return;
  }
  rt_0034a8cc();
  rt_002a2748();
  return;
}

/* FUN_00208478 @ 0x00208478   (est. sk_dispatch_mux)
 * Ghidra: void FUN_00208478(word_t param_1,word_t param_2,word_t param_3)
 * Dispatch mux: resolves two runtime functions, runs a branch check, dispatches one of two continuations, returns via epilogue.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_dispatch_mux(word_t param_1,word_t param_2,word_t param_3)
{

  word_t uVar1;
  word_t uVar2;
  word_t uVar3;
  word_t extraout_x1;
  sk_fnptr extraout_x8;
  sk_fnptr extraout_x8_00;
  sk_fnptr extraout_x9;
  sk_fnptr extraout_x9_00;
  word_t extraout_x16;
  word_t local_8;
  
  rt_00084220();
  uVar1 = rt_00353e88();
  uVar2 = rt_0034a980();
  rt_00377824(uVar2,param_3,uVar1);
  rt_00348e18();
  rt_0007c1a4();
  (*g_00658c00)();
  rt_0034cff4();
  rt_00351bec();
  rt_0034acd0();
  uVar3 = (*extraout_x8)();
  if ((uVar3 & 1) == 0) {
    rt_0007b384();
    rt_00351f7c();
    rt_00351384();
    (*extraout_x9_00)();
    rt_000e710c();
  }
  else {
    rt_0007b384();
    rt_00351f7c();
    rt_00351384();
    (*extraout_x9)();
    rt_0001df60();
    rt_003516fc();
  }
  rt_00084180(&local_8);
  rt_001e2460();
  rt_00084180(*(word_t *)(extraout_x16 + 8));
  (*extraout_x8_00)();
  rt_00084234(local_8,extraout_x1);
  return;
}

/* FUN_002085a4 @ 0x002085a4   (est. sk_abstract_method)
 * Ghidra: void FUN_002085a4(void)
 * Abstract method trap (noreturn): logs "Method must be overridden" (sk_str_Method_must_be_overridden) then "Fatal error" and panics via rt_001afa84. Base-class virtual that concrete types must override.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_abstract_method(void)
{

  rt_0035ac70(sk_str_Method_must_be_overridden);
  rt_0006f768(sk_str_Fatal_error);
                    /* WARNING: Subroutine does not return */
  rt_001afa84();
}

/* FUN_002085fc @ 0x002085fc   (est. sk_vt_init)
 * Ghidra: void FUN_002085fc(void)
 * Vtable init: runtime prologue, then calls sk_vt_install (00208628).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_init(void)
{

  rt_0034d7a8();
  rt_0031b930();
  rt_00351d18();
  sk_vt_install((word_t)());
  return;
}

/* FUN_00208628 @ 0x00208628   (est. sk_vt_install)
 * Ghidra: void FUN_00208628()
 * Vtable install: calls rt_00210bd4 with the hook sk_vt_hook_c (00208760).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_install()
{

  rt_00210bd4(param_1,sk_vt_hook_a);
  return;
}

/* FUN_00208640 @ 0x00208640   (est. sk_vt_setup)
 * Ghidra: void FUN_00208640(void)
 * Vtable setup: builds a descriptor via rt_0031b948/rt_0031b930 and calls sk_vt_install (00208628).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_setup(void)
{

  word_t uVar1;
  
  rt_003504d0();
  rt_003537d4();
  uVar1 = rt_0031b948();
  uVar1 = rt_0031b930(0,uVar1,0x66c210);
  sk_vt_install((word_t)(&sk_stack_ffffffffffffffd0));
  return;
}

/* FUN_002086ac @ 0x002086ac   (est. sk_vt_teardown)
 * Ghidra: void FUN_002086ac(void)
 * Vtable teardown: runtime calls to release the vtable object.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_teardown(void)
{

  rt_003503c0();
  rt_0036b270();
  rt_0007c1c4();
  return;
}

/* FUN_002086d4 @ 0x002086d4   (est. sk_vt_call)
 * Ghidra: void FUN_002086d4(sk_fnptr *param_1)
 * Vtable call: invokes the passed function pointer.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_call(sk_fnptr *param_1)
{

  (*param_1)();
  return;
}

/* FUN_00208704 @ 0x00208704   (est. sk_vt_abstract_a)
 * Ghidra: void FUN_00208704(void)
 * Abstract vtable method A: enters rt_00357cc8, calls sk_abstract_method (002085a4, noreturn), then dispatches +0x48.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_abstract_a(void)
{

  word_t *unaff_x20;
  
  rt_00357cc8();
  sk_abstract_method();
  (**(sk_fnptr *)(*(word_t *)*unaff_x20 + 0x48))();
  return;
}

/* FUN_00208708 @ 0x00208708   (est. sk_vt_abstract_b)
 * Ghidra: void FUN_00208708(void)
 * Abstract vtable method B: same pattern as 00208704.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_abstract_b(void)
{

  word_t *unaff_x20;
  
  rt_00357cc8();
  sk_abstract_method();
  (**(sk_fnptr *)(*(word_t *)*unaff_x20 + 0x48))();
  return;
}

/* FUN_00208760 @ 0x00208760   (est. sk_vt_hook_a)
 * Ghidra: void FUN_00208760(word_t param_1)
 * Vtable hook: builds a frame via rt_0007c0c4, calls runtime, dispatches +0x20.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_hook_a(word_t param_1)
{

  word_t extraout_x8;
  word_t extraout_x9;
  word_t extraout_x16;
  word_t unaff_x20;
  sk_u128_t auVar1;
  
  auVar1 = rt_0007c0c4(param_1,param_1);
  rt_0034b07c(auVar1.lo,auVar1.hi,*(word_t *)(extraout_x8 + 0x50));
  (**(sk_fnptr *)(extraout_x16 + 0x20))(unaff_x20 + extraout_x9);
  return;
}

/* FUN_00208764 @ 0x00208764   (est. sk_vt_hook_b)
 * Ghidra: void FUN_00208764(word_t param_1)
 * Vtable hook variant: same as 00208760.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_hook_b(word_t param_1)
{

  word_t extraout_x8;
  word_t extraout_x9;
  word_t extraout_x16;
  word_t unaff_x20;
  sk_u128_t auVar1;
  
  auVar1 = rt_0007c0c4(param_1,param_1);
  rt_0034b07c(auVar1.lo,auVar1.hi,*(word_t *)(extraout_x8 + 0x50));
  (**(sk_fnptr *)(extraout_x16 + 0x20))(unaff_x20 + extraout_x9);
  return;
}

/* FUN_002087bc @ 0x002087bc   (est. sk_vt_hook_c)
 * Ghidra: void FUN_002087bc(void)
 * Vtable hook: builds frame, indirect dispatch (unrecovered jumptable artifact) via +0x50/+0x60.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_hook_c(void)
{

  word_t extraout_x8;
  word_t extraout_x16;
  word_t unaff_x20;
  
  rt_0007c0c4();
                    /* WARNING: Could not recover jumptable at 0x00208810. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(sk_fnptr *)(*(word_t *)(*(word_t *)(extraout_x8 + 0x50) + -8) + 8))
            (unaff_x20 + *(word_t *)(extraout_x16 + 0x60));
  return;
}

/* FUN_00208818 @ 0x00208818   (est. sk_vt_hook_d)
 * Ghidra: void FUN_00208818(void)
 * Vtable hook: builds frame via rt_0007c0c4, calls runtime, dispatches +0x50.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_hook_d(void)
{

  word_t uVar1;
  word_t extraout_x8;
  word_t extraout_x9;
  word_t extraout_x16;
  word_t unaff_x20;
  
  uVar1 = rt_0007c0c4().lo;
  rt_0034ece8(uVar1,*(word_t *)(extraout_x8 + 0x50));
  (**(sk_fnptr *)(extraout_x16 + 8))(unaff_x20 + extraout_x9);
  return;
}

/* FUN_00208884 @ 0x00208884   (est. sk_vt_hook_e)
 * Ghidra: void FUN_00208884(word_t param_1)
 * Vtable hook: runtime preamble, loads +0x58, resolves, indirect call.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_vt_hook_e(word_t param_1)
{

  sk_fnptr extraout_x9;
  word_t extraout_x16;
  word_t unaff_x21;
  word_t uVar1;
  
  rt_0034ecb8();
  uVar1 = *(word_t *)(unaff_x21 + 0x58);
  rt_00354474(uVar1);
  rt_00351d9c();
  (*extraout_x9)(param_1,*(word_t *)(extraout_x16 + 0x50),uVar1);
  return;
}

/* FUN_002089ec @ 0x002089ec   (est. sk_dtor_pure_a)
 * Ghidra: void FUN_002089ec(void)
 * Pure-destructor stub A: emits 14 abstract-method traps then releases object +0x10/+0x20. Base-class destructor (must be overridden).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_dtor_pure_a(void)
{

  word_t unaff_x20;
  
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_0036b118(*(word_t *)(unaff_x20 + 0x10));
  rt_0036b118(*(word_t *)(unaff_x20 + 0x20));
  return;
}

/* FUN_002089f0 @ 0x002089f0   (est. sk_dtor_pure_b)
 * Ghidra: void FUN_002089f0(void)
 * Pure-destructor stub B: same as A (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_dtor_pure_b(void)
{

  word_t unaff_x20;
  
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_0036b118(*(word_t *)(unaff_x20 + 0x10));
  rt_0036b118(*(word_t *)(unaff_x20 + 0x20));
  return;
}

/* FUN_00208a10 @ 0x00208a10   (est. sk_dtor_pure_c)
 * Ghidra: void FUN_00208a10(void)
 * Pure-destructor stub C: same (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_dtor_pure_c(void)
{

  word_t unaff_x20;
  
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_0036b118(*(word_t *)(unaff_x20 + 0x10));
  rt_0036b118(*(word_t *)(unaff_x20 + 0x20));
  return;
}

/* FUN_00208a30 @ 0x00208a30   (est. sk_dtor_pure_d)
 * Ghidra: void FUN_00208a30(void)
 * Pure-destructor stub D: same (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_dtor_pure_d(void)
{

  word_t unaff_x20;
  
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_0036b118(*(word_t *)(unaff_x20 + 0x10));
  rt_0036b118(*(word_t *)(unaff_x20 + 0x20));
  return;
}

/* FUN_00208a50 @ 0x00208a50   (est. sk_dtor_pure_e)
 * Ghidra: void FUN_00208a50(void)
 * Pure-destructor stub E: same (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_dtor_pure_e(void)
{

  word_t unaff_x20;
  
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_0036b118(*(word_t *)(unaff_x20 + 0x10));
  rt_0036b118(*(word_t *)(unaff_x20 + 0x20));
  return;
}

/* FUN_00208a70 @ 0x00208a70   (est. sk_dtor_pure_f)
 * Ghidra: void FUN_00208a70(void)
 * Pure-destructor stub F: same (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void sk_dtor_pure_f(void)
{

  word_t unaff_x20;
  
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_00357cc8();
  sk_abstract_method();
  rt_0036b118(*(word_t *)(unaff_x20 + 0x10));
  rt_0036b118(*(word_t *)(unaff_x20 + 0x20));
  return;
}
