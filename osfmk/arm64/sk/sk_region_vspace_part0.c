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
 * pure destructors that trap via skp0_sk_abstract_method (must be overridden). */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

typedef struct sk_u128 { word_t lo; word_t hi; } sk_u128_t;
typedef word_t (*sk_fnptr)();

#define skp0_SCARRY8(a,b)  (__builtin_add_overflow((word_t)(a),(word_t)(b),&(word_t){0}))
#define skp0_SBORROW8(a,b) (__builtin_sub_overflow((word_t)(a),(word_t)(b),&(word_t){0}))
#define skp0_SoftwareBreakpoint(n,pc) ((void*)0)

/* ---- shared runtime library (out of scope for this slice) ---- */
extern sk_u128_t skp0_rt_00002534(); /* FUN_00002534 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000026e8(); /* FUN_000026e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000027e8(); /* FUN_000027e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00012568(); /* FUN_00012568 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0001df60(); /* FUN_0001df60 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00027724(); /* FUN_00027724 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00027754(); /* FUN_00027754 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00027788(); /* FUN_00027788 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000277b8(); /* FUN_000277b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000277e8(); /* FUN_000277e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00027818(); /* FUN_00027818 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00041138(); /* FUN_00041138 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0006a4c0(); /* FUN_0006a4c0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0006b6f4(); /* FUN_0006b6f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0006e778(); /* FUN_0006e778 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0006f768(); /* FUN_0006f768 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00077070(); /* FUN_00077070 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000777d4(); /* FUN_000777d4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00077888(); /* FUN_00077888 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00077894(); /* FUN_00077894 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0007b384(); /* FUN_0007b384 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0007c0c4(); /* FUN_0007c0c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0007c1a4(); /* FUN_0007c1a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0007c1c4(); /* FUN_0007c1c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000839d8(); /* FUN_000839d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000839f8(); /* FUN_000839f8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00083a18(); /* FUN_00083a18 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0008409c(); /* FUN_0008409c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00084174(); /* FUN_00084174 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00084180(); /* FUN_00084180 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00084220(); /* FUN_00084220 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00084234(); /* FUN_00084234 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0008da6c(); /* FUN_0008da6c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0008e388(); /* FUN_0008e388 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0008e500(); /* FUN_0008e500 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0008e518(); /* FUN_0008e518 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0009461c(); /* FUN_0009461c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0009e234(); /* FUN_0009e234 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000a68f4(); /* FUN_000a68f4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000a6f88(); /* FUN_000a6f88 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_000b43d0(); /* FUN_000b43d0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000b4594(); /* FUN_000b4594 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000b45b0(); /* FUN_000b45b0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000bd3a4(); /* FUN_000bd3a4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000dbc98(); /* FUN_000dbc98 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000e15d8(); /* FUN_000e15d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000e710c(); /* FUN_000e710c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_000e72b0(); /* FUN_000e72b0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_000ec044(); /* FUN_000ec044 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00100c38(); /* FUN_00100c38 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00100efc(); /* FUN_00100efc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00106e3c(); /* FUN_00106e3c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0014ae44(); /* FUN_0014ae44 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0016186c(); /* FUN_0016186c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0019f1ec(); /* FUN_0019f1ec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0019fa60(); /* FUN_0019fa60 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001a0194(); /* FUN_001a0194 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_001a89a8(); /* FUN_001a89a8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001afa84() __attribute__((noreturn)); /* FUN_001afa84 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001afe4c() __attribute__((noreturn)); /* FUN_001afe4c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001b5784(); /* FUN_001b5784 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001b5a88(); /* FUN_001b5a88 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001b68a0(); /* FUN_001b68a0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001b9040(); /* FUN_001b9040 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001db6b0(); /* FUN_001db6b0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001e088c(); /* FUN_001e088c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001e2460(); /* FUN_001e2460 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001e3048(); /* FUN_001e3048 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001e9f14(); /* FUN_001e9f14 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001edb28(); /* FUN_001edb28 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001ef7ac(); /* FUN_001ef7ac (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001ef808(); /* FUN_001ef808 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001fccf8(); /* FUN_001fccf8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001fd4f4(); /* FUN_001fd4f4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001fe7cc(); /* FUN_001fe7cc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001fe9a8(); /* FUN_001fe9a8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001fea40(); /* FUN_001fea40 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_001fff64(); /* FUN_001fff64 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00210bd4(); /* FUN_00210bd4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_002364dc(); /* FUN_002364dc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00250904(); /* FUN_00250904 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00262b5c(); /* FUN_00262b5c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_002667a8(); /* FUN_002667a8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_002678b4(); /* FUN_002678b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0026c274(); /* FUN_0026c274 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0027743c(); /* FUN_0027743c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00277474(); /* FUN_00277474 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00279568(); /* FUN_00279568 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0027a6e0(); /* FUN_0027a6e0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00280bc4(); /* FUN_00280bc4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00284424(); /* FUN_00284424 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_002a218c(); /* FUN_002a218c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_002a2698(); /* FUN_002a2698 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_002a2748(); /* FUN_002a2748 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_002a4c98(); /* FUN_002a4c98 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00310924(); /* FUN_00310924 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00310b08(); /* FUN_00310b08 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00310cd4(); /* FUN_00310cd4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00310d68(); /* FUN_00310d68 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00310d98(); /* FUN_00310d98 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00310e08(); /* FUN_00310e08 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00310e20(); /* FUN_00310e20 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00310ed4(); /* FUN_00310ed4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00310f04(); /* FUN_00310f04 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00319230(); /* FUN_00319230 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003192d8(); /* FUN_003192d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003194f8(); /* FUN_003194f8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00319658(); /* FUN_00319658 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00319808(); /* FUN_00319808 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003198cc(); /* FUN_003198cc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00319a4c(); /* FUN_00319a4c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031afcc(); /* FUN_0031afcc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b050(); /* FUN_0031b050 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b110(); /* FUN_0031b110 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b2bc(); /* FUN_0031b2bc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b2ec(); /* FUN_0031b2ec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b704(); /* FUN_0031b704 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b71c(); /* FUN_0031b71c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b760(); /* FUN_0031b760 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b778(); /* FUN_0031b778 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b858(); /* FUN_0031b858 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b870(); /* FUN_0031b870 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b8d0(); /* FUN_0031b8d0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b900(); /* FUN_0031b900 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b930(); /* FUN_0031b930 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031b948(); /* FUN_0031b948 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0031e104(); /* FUN_0031e104 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0032d3e0(); /* FUN_0032d3e0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034310c(); /* FUN_0034310c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00344e54(); /* FUN_00344e54 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00347d60(); /* FUN_00347d60 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00347da8(); /* FUN_00347da8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348034(); /* FUN_00348034 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034846c(); /* FUN_0034846c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003484e4(); /* FUN_003484e4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348638(); /* FUN_00348638 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003486b8(); /* FUN_003486b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003488bc(); /* FUN_003488bc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034895c(); /* FUN_0034895c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348a50(); /* FUN_00348a50 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348a80(); /* FUN_00348a80 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348abc(); /* FUN_00348abc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348b5c(); /* FUN_00348b5c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00348b94(); /* FUN_00348b94 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348bbc(); /* FUN_00348bbc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348c30(); /* FUN_00348c30 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348cd0(); /* FUN_00348cd0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348ce8(); /* FUN_00348ce8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348d4c(); /* FUN_00348d4c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348d7c(); /* FUN_00348d7c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348e18(); /* FUN_00348e18 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348e9c(); /* FUN_00348e9c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348f38(); /* FUN_00348f38 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00348fd8(); /* FUN_00348fd8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349080(); /* FUN_00349080 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003490b8(); /* FUN_003490b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034911c(); /* FUN_0034911c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349178(); /* FUN_00349178 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003493c4(); /* FUN_003493c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003494e8(); /* FUN_003494e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349530(); /* FUN_00349530 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349720(); /* FUN_00349720 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349734(); /* FUN_00349734 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349748(); /* FUN_00349748 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034975c(); /* FUN_0034975c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003497a0(); /* FUN_003497a0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003497b4(); /* FUN_003497b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003497ec(); /* FUN_003497ec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349830(); /* FUN_00349830 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003499dc(); /* FUN_003499dc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003499f0(); /* FUN_003499f0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349a68(); /* FUN_00349a68 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349b3c(); /* FUN_00349b3c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349c70(); /* FUN_00349c70 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349db0(); /* FUN_00349db0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349de8(); /* FUN_00349de8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349ef4(); /* FUN_00349ef4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00349f5c(); /* FUN_00349f5c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a120(); /* FUN_0034a120 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a210(); /* FUN_0034a210 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0034a274(); /* FUN_0034a274 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a30c(); /* FUN_0034a30c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a400(); /* FUN_0034a400 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a464(); /* FUN_0034a464 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a4e0(); /* FUN_0034a4e0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a5c8(); /* FUN_0034a5c8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a760(); /* FUN_0034a760 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a8cc(); /* FUN_0034a8cc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a980(); /* FUN_0034a980 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a9ac(); /* FUN_0034a9ac (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a9c0(); /* FUN_0034a9c0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a9d4(); /* FUN_0034a9d4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034a9e8(); /* FUN_0034a9e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034aa28(); /* FUN_0034aa28 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034aa54(); /* FUN_0034aa54 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034aa9c(); /* FUN_0034aa9c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034aadc(); /* FUN_0034aadc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ab20(); /* FUN_0034ab20 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ac14(); /* FUN_0034ac14 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ac3c(); /* FUN_0034ac3c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034acd0(); /* FUN_0034acd0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034acf0(); /* FUN_0034acf0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034aea8(); /* FUN_0034aea8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034aebc(); /* FUN_0034aebc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034aee4(); /* FUN_0034aee4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034af20(); /* FUN_0034af20 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b07c(); /* FUN_0034b07c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b0b4(); /* FUN_0034b0b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b0d4(); /* FUN_0034b0d4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b0e4(); /* FUN_0034b0e4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b150(); /* FUN_0034b150 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b1a0(); /* FUN_0034b1a0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b2a8(); /* FUN_0034b2a8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b2c8(); /* FUN_0034b2c8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b2f8(); /* FUN_0034b2f8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b308(); /* FUN_0034b308 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b348(); /* FUN_0034b348 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b358(); /* FUN_0034b358 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b3d8(); /* FUN_0034b3d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b430(); /* FUN_0034b430 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b440(); /* FUN_0034b440 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b4c0(); /* FUN_0034b4c0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b508(); /* FUN_0034b508 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b540(); /* FUN_0034b540 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b640(); /* FUN_0034b640 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b6f4(); /* FUN_0034b6f4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b708(); /* FUN_0034b708 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b71c(); /* FUN_0034b71c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b758(); /* FUN_0034b758 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b778(); /* FUN_0034b778 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b7b8(); /* FUN_0034b7b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0034b7c8(); /* FUN_0034b7c8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b804(); /* FUN_0034b804 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b824(); /* FUN_0034b824 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b87c(); /* FUN_0034b87c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0034b89c(); /* FUN_0034b89c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034b8cc(); /* FUN_0034b8cc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ba68(); /* FUN_0034ba68 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034bc58(); /* FUN_0034bc58 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034bc6c(); /* FUN_0034bc6c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034bc94(); /* FUN_0034bc94 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034bccc(); /* FUN_0034bccc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034bec4(); /* FUN_0034bec4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034beec(); /* FUN_0034beec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c034(); /* FUN_0034c034 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c074(); /* FUN_0034c074 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c108(); /* FUN_0034c108 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c220(); /* FUN_0034c220 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c2e8(); /* FUN_0034c2e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c354(); /* FUN_0034c354 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c3c4(); /* FUN_0034c3c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c434(); /* FUN_0034c434 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c4fc(); /* FUN_0034c4fc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c54c(); /* FUN_0034c54c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c5cc(); /* FUN_0034c5cc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c60c(); /* FUN_0034c60c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c684(); /* FUN_0034c684 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c694(); /* FUN_0034c694 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c6b4(); /* FUN_0034c6b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c818(); /* FUN_0034c818 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c8c8(); /* FUN_0034c8c8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034c9d8(); /* FUN_0034c9d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ca28(); /* FUN_0034ca28 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034cae8(); /* FUN_0034cae8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034cd54(); /* FUN_0034cd54 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034cd7c(); /* FUN_0034cd7c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034cde8(); /* FUN_0034cde8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ce58(); /* FUN_0034ce58 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ced8(); /* FUN_0034ced8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034cfa4(); /* FUN_0034cfa4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034cff4(); /* FUN_0034cff4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d044(); /* FUN_0034d044 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d234(); /* FUN_0034d234 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d294(); /* FUN_0034d294 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d2a4(); /* FUN_0034d2a4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d2d4(); /* FUN_0034d2d4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d404(); /* FUN_0034d404 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d424(); /* FUN_0034d424 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d434(); /* FUN_0034d434 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d598(); /* FUN_0034d598 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d5a8(); /* FUN_0034d5a8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d654(); /* FUN_0034d654 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d688(); /* FUN_0034d688 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d758(); /* FUN_0034d758 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d7a8(); /* FUN_0034d7a8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d7fc(); /* FUN_0034d7fc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d888(); /* FUN_0034d888 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034d89c(); /* FUN_0034d89c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034dae8(); /* FUN_0034dae8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034db68(); /* FUN_0034db68 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034db88(); /* FUN_0034db88 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034db98(); /* FUN_0034db98 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034dd64(); /* FUN_0034dd64 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ddd8(); /* FUN_0034ddd8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034de44(); /* FUN_0034de44 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034de64(); /* FUN_0034de64 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034de8c(); /* FUN_0034de8c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034df34(); /* FUN_0034df34 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034df64(); /* FUN_0034df64 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e024(); /* FUN_0034e024 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e034(); /* FUN_0034e034 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e044(); /* FUN_0034e044 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e054(); /* FUN_0034e054 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e0c4(); /* FUN_0034e0c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e130(); /* FUN_0034e130 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e54c(); /* FUN_0034e54c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e55c(); /* FUN_0034e55c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e67c(); /* FUN_0034e67c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e6cc(); /* FUN_0034e6cc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034e70c(); /* FUN_0034e70c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ecb8(); /* FUN_0034ecb8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ece8(); /* FUN_0034ece8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ee08(); /* FUN_0034ee08 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ee38(); /* FUN_0034ee38 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ee68(); /* FUN_0034ee68 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ee98(); /* FUN_0034ee98 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034eeb8(); /* FUN_0034eeb8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034eef8(); /* FUN_0034eef8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ef68(); /* FUN_0034ef68 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ef78(); /* FUN_0034ef78 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ef88(); /* FUN_0034ef88 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034efc8(); /* FUN_0034efc8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f014(); /* FUN_0034f014 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f030(); /* FUN_0034f030 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f064(); /* FUN_0034f064 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f3b4(); /* FUN_0034f3b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f3d4(); /* FUN_0034f3d4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f3f4(); /* FUN_0034f3f4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f4c4(); /* FUN_0034f4c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f4e4(); /* FUN_0034f4e4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f514(); /* FUN_0034f514 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f534(); /* FUN_0034f534 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f5b4(); /* FUN_0034f5b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f5e4(); /* FUN_0034f5e4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f604(); /* FUN_0034f604 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f634(); /* FUN_0034f634 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f674(); /* FUN_0034f674 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f714(); /* FUN_0034f714 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f730(); /* FUN_0034f730 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0034f98c(); /* FUN_0034f98c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f9ec(); /* FUN_0034f9ec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034f9fc(); /* FUN_0034f9fc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034fb28(); /* FUN_0034fb28 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034fd6c(); /* FUN_0034fd6c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034fdbc(); /* FUN_0034fdbc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034feb0(); /* FUN_0034feb0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0034ff88(); /* FUN_0034ff88 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350048(); /* FUN_00350048 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350288(); /* FUN_00350288 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003502a8(); /* FUN_003502a8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003502e8(); /* FUN_003502e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003502f8(); /* FUN_003502f8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350308(); /* FUN_00350308 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350318(); /* FUN_00350318 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003503c0(); /* FUN_003503c0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350410(); /* FUN_00350410 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035041c(); /* FUN_0035041c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350428(); /* FUN_00350428 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350434(); /* FUN_00350434 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035044c(); /* FUN_0035044c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350464(); /* FUN_00350464 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350470(); /* FUN_00350470 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350488(); /* FUN_00350488 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00350494(); /* FUN_00350494 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003504a0(); /* FUN_003504a0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003504ac(); /* FUN_003504ac (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003504b8(); /* FUN_003504b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003504c4(); /* FUN_003504c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003504d0(); /* FUN_003504d0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003504e8(); /* FUN_003504e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003504f4(); /* FUN_003504f4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0035050c(); /* FUN_0035050c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350518(); /* FUN_00350518 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00350524(); /* FUN_00350524 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350530(); /* FUN_00350530 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035053c(); /* FUN_0035053c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350548(); /* FUN_00350548 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350560(); /* FUN_00350560 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035056c(); /* FUN_0035056c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003505d0(); /* FUN_003505d0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003505e8(); /* FUN_003505e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035060c(); /* FUN_0035060c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350618(); /* FUN_00350618 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350624(); /* FUN_00350624 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350630(); /* FUN_00350630 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035063c(); /* FUN_0035063c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003506e8(); /* FUN_003506e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350704(); /* FUN_00350704 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00350720(); /* FUN_00350720 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035072c(); /* FUN_0035072c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350744(); /* FUN_00350744 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350768(); /* FUN_00350768 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350774(); /* FUN_00350774 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350780(); /* FUN_00350780 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350798(); /* FUN_00350798 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003507bc(); /* FUN_003507bc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003507c8(); /* FUN_003507c8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003507e0(); /* FUN_003507e0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350804(); /* FUN_00350804 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350810(); /* FUN_00350810 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350834(); /* FUN_00350834 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035084c(); /* FUN_0035084c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350878(); /* FUN_00350878 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350884(); /* FUN_00350884 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035089c(); /* FUN_0035089c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003508b4(); /* FUN_003508b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003508c0(); /* FUN_003508c0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003508cc(); /* FUN_003508cc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003508d8(); /* FUN_003508d8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003508e4(); /* FUN_003508e4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350914(); /* FUN_00350914 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00350944(); /* FUN_00350944 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350974(); /* FUN_00350974 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350998(); /* FUN_00350998 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003509a4(); /* FUN_003509a4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003509b0(); /* FUN_003509b0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003509bc(); /* FUN_003509bc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003509e0(); /* FUN_003509e0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350a1c(); /* FUN_00350a1c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350a28(); /* FUN_00350a28 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350a34(); /* FUN_00350a34 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00350a70(); /* FUN_00350a70 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350a7c(); /* FUN_00350a7c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350a88(); /* FUN_00350a88 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350aac(); /* FUN_00350aac (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350ac4(); /* FUN_00350ac4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350ad0(); /* FUN_00350ad0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350af4(); /* FUN_00350af4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00350b00(); /* FUN_00350b00 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350b18(); /* FUN_00350b18 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350b24(); /* FUN_00350b24 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00350b3c(); /* FUN_00350b3c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350b48(); /* FUN_00350b48 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350b54(); /* FUN_00350b54 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00350b78(); /* FUN_00350b78 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350b84(); /* FUN_00350b84 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350b90(); /* FUN_00350b90 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350b9c(); /* FUN_00350b9c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350bc0(); /* FUN_00350bc0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350bd8(); /* FUN_00350bd8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350bf0(); /* FUN_00350bf0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350bfc(); /* FUN_00350bfc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350c50(); /* FUN_00350c50 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350cb4(); /* FUN_00350cb4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350d94(); /* FUN_00350d94 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350e74(); /* FUN_00350e74 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00350ea4(); /* FUN_00350ea4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350edc(); /* FUN_00350edc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00350fdc(); /* FUN_00350fdc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035100c(); /* FUN_0035100c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035102c(); /* FUN_0035102c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003510ac(); /* FUN_003510ac (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003510d0(); /* FUN_003510d0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003510dc(); /* FUN_003510dc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003510f4(); /* FUN_003510f4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351100(); /* FUN_00351100 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351118(); /* FUN_00351118 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351124(); /* FUN_00351124 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351130(); /* FUN_00351130 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351160(); /* FUN_00351160 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035116c(); /* FUN_0035116c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035119c(); /* FUN_0035119c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003511c0(); /* FUN_003511c0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351238(); /* FUN_00351238 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035125c(); /* FUN_0035125c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00351274(); /* FUN_00351274 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003512c0(); /* FUN_003512c0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003512d8(); /* FUN_003512d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003512f4(); /* FUN_003512f4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351300(); /* FUN_00351300 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351318(); /* FUN_00351318 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351324(); /* FUN_00351324 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035136c(); /* FUN_0035136c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351378(); /* FUN_00351378 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351384(); /* FUN_00351384 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035139c(); /* FUN_0035139c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003513b4(); /* FUN_003513b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003513d8(); /* FUN_003513d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351438(); /* FUN_00351438 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0035145c(); /* FUN_0035145c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003514a0(); /* FUN_003514a0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003514b8(); /* FUN_003514b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003514d0(); /* FUN_003514d0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035152c(); /* FUN_0035152c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351548(); /* FUN_00351548 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035156c(); /* FUN_0035156c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351584(); /* FUN_00351584 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003515fc(); /* FUN_003515fc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351648(); /* FUN_00351648 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035166c(); /* FUN_0035166c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003516e4(); /* FUN_003516e4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003516f0(); /* FUN_003516f0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003516fc(); /* FUN_003516fc (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00351714(); /* FUN_00351714 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351744(); /* FUN_00351744 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351750(); /* FUN_00351750 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035179c(); /* FUN_0035179c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003518a0(); /* FUN_003518a0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003518b8(); /* FUN_003518b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003518c4(); /* FUN_003518c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351978(); /* FUN_00351978 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351a20(); /* FUN_00351a20 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351a50(); /* FUN_00351a50 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351abc(); /* FUN_00351abc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351ad4(); /* FUN_00351ad4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351af8(); /* FUN_00351af8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351b20(); /* FUN_00351b20 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351b2c(); /* FUN_00351b2c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351b38(); /* FUN_00351b38 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351b78(); /* FUN_00351b78 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351b84(); /* FUN_00351b84 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351ba0(); /* FUN_00351ba0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351bd4(); /* FUN_00351bd4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351bec(); /* FUN_00351bec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351c28(); /* FUN_00351c28 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351c4c(); /* FUN_00351c4c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351c88(); /* FUN_00351c88 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351c94(); /* FUN_00351c94 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351cc4(); /* FUN_00351cc4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351cd0(); /* FUN_00351cd0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351d00(); /* FUN_00351d00 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351d18(); /* FUN_00351d18 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351d24(); /* FUN_00351d24 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351d9c(); /* FUN_00351d9c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351db4(); /* FUN_00351db4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351dcc(); /* FUN_00351dcc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351de4(); /* FUN_00351de4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351e08(); /* FUN_00351e08 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351e48(); /* FUN_00351e48 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351e78(); /* FUN_00351e78 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351e84(); /* FUN_00351e84 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351ef8(); /* FUN_00351ef8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351f10(); /* FUN_00351f10 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351f40(); /* FUN_00351f40 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351f4c(); /* FUN_00351f4c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351f58(); /* FUN_00351f58 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351f7c(); /* FUN_00351f7c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351f88(); /* FUN_00351f88 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00351fb0(); /* FUN_00351fb0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352018(); /* FUN_00352018 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352350(); /* FUN_00352350 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035238c(); /* FUN_0035238c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035242c(); /* FUN_0035242c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352450(); /* FUN_00352450 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352474(); /* FUN_00352474 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352480(); /* FUN_00352480 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003524a4(); /* FUN_003524a4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003524b0(); /* FUN_003524b0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352554(); /* FUN_00352554 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352590(); /* FUN_00352590 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003525cc(); /* FUN_003525cc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003526b8(); /* FUN_003526b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352800(); /* FUN_00352800 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003528b8(); /* FUN_003528b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352920(); /* FUN_00352920 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352968(); /* FUN_00352968 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003529a4(); /* FUN_003529a4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352a28(); /* FUN_00352a28 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352a40(); /* FUN_00352a40 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352a4c(); /* FUN_00352a4c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352a8c(); /* FUN_00352a8c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352abc(); /* FUN_00352abc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352afc(); /* FUN_00352afc (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00352b14(); /* FUN_00352b14 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352b98(); /* FUN_00352b98 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352bb0(); /* FUN_00352bb0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352bbc(); /* FUN_00352bbc (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00352c68(); /* FUN_00352c68 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352ca4(); /* FUN_00352ca4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352ce0(); /* FUN_00352ce0 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00352dc4(); /* FUN_00352dc4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352e3c(); /* FUN_00352e3c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352e78(); /* FUN_00352e78 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352ea8(); /* FUN_00352ea8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352eb4(); /* FUN_00352eb4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352ecc(); /* FUN_00352ecc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352efc(); /* FUN_00352efc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00352f54(); /* FUN_00352f54 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003530b0(); /* FUN_003530b0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003530bc(); /* FUN_003530bc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003530d8(); /* FUN_003530d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353100(); /* FUN_00353100 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353130(); /* FUN_00353130 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035313c(); /* FUN_0035313c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353148(); /* FUN_00353148 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353154(); /* FUN_00353154 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353190(); /* FUN_00353190 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353214(); /* FUN_00353214 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035336c(); /* FUN_0035336c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353390(); /* FUN_00353390 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003534ec(); /* FUN_003534ec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035351c(); /* FUN_0035351c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353534(); /* FUN_00353534 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353540(); /* FUN_00353540 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0035354c(); /* FUN_0035354c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035359c(); /* FUN_0035359c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353718(); /* FUN_00353718 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353734(); /* FUN_00353734 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353758(); /* FUN_00353758 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003537d4(); /* FUN_003537d4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353960(); /* FUN_00353960 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003539d8(); /* FUN_003539d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353a00(); /* FUN_00353a00 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353ad8(); /* FUN_00353ad8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353b34(); /* FUN_00353b34 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353b70(); /* FUN_00353b70 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353bac(); /* FUN_00353bac (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353bc4(); /* FUN_00353bc4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353c00(); /* FUN_00353c00 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353c6c(); /* FUN_00353c6c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353d64(); /* FUN_00353d64 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353e88(); /* FUN_00353e88 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00353fa0(); /* FUN_00353fa0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354000(); /* FUN_00354000 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354064(); /* FUN_00354064 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003540dc(); /* FUN_003540dc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354128(); /* FUN_00354128 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354134(); /* FUN_00354134 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00354264(); /* FUN_00354264 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035433c(); /* FUN_0035433c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354388(); /* FUN_00354388 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354394(); /* FUN_00354394 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354410(); /* FUN_00354410 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354474(); /* FUN_00354474 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354570(); /* FUN_00354570 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035457c(); /* FUN_0035457c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035460c(); /* FUN_0035460c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035463c(); /* FUN_0035463c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354708(); /* FUN_00354708 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003548e8(); /* FUN_003548e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354930(); /* FUN_00354930 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354ab0(); /* FUN_00354ab0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354ae8(); /* FUN_00354ae8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354afc(); /* FUN_00354afc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354bb0(); /* FUN_00354bb0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354d80(); /* FUN_00354d80 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354da0(); /* FUN_00354da0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00354f1c(); /* FUN_00354f1c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00355018(); /* FUN_00355018 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355418(); /* FUN_00355418 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355674(); /* FUN_00355674 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355754(); /* FUN_00355754 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355884(); /* FUN_00355884 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355a2c(); /* FUN_00355a2c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355a64(); /* FUN_00355a64 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355aa0(); /* FUN_00355aa0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355adc(); /* FUN_00355adc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355bd0(); /* FUN_00355bd0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355bdc(); /* FUN_00355bdc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355bf4(); /* FUN_00355bf4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355c78(); /* FUN_00355c78 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355ca4(); /* FUN_00355ca4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355d78(); /* FUN_00355d78 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355d9c(); /* FUN_00355d9c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355db4(); /* FUN_00355db4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355dc0(); /* FUN_00355dc0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355e50(); /* FUN_00355e50 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355fa0(); /* FUN_00355fa0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00355fac(); /* FUN_00355fac (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003561a0(); /* FUN_003561a0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003561b8(); /* FUN_003561b8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0035620c(); /* FUN_0035620c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00356278(); /* FUN_00356278 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003562d4(); /* FUN_003562d4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00356304(); /* FUN_00356304 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035631c(); /* FUN_0035631c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00356340(); /* FUN_00356340 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00356578(); /* FUN_00356578 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035675c(); /* FUN_0035675c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035678c(); /* FUN_0035678c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003567bc(); /* FUN_003567bc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003567ec(); /* FUN_003567ec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003567f8(); /* FUN_003567f8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035694c(); /* FUN_0035694c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003569b4(); /* FUN_003569b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003569e4(); /* FUN_003569e4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00356c84(); /* FUN_00356c84 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00356e34(); /* FUN_00356e34 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00356f44(); /* FUN_00356f44 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00356fb8(); /* FUN_00356fb8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00356fcc(); /* FUN_00356fcc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00356fd8(); /* FUN_00356fd8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035705c(); /* FUN_0035705c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00357338(); /* FUN_00357338 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00357350(); /* FUN_00357350 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035748c(); /* FUN_0035748c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003578a8(); /* FUN_003578a8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00357998(); /* FUN_00357998 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003579e8(); /* FUN_003579e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00357be0(); /* FUN_00357be0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00357c74(); /* FUN_00357c74 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00357cb4(); /* FUN_00357cb4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00357cc8(); /* FUN_00357cc8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358174(); /* FUN_00358174 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003581c4(); /* FUN_003581c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358374(); /* FUN_00358374 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035847c(); /* FUN_0035847c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003584ec(); /* FUN_003584ec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358684(); /* FUN_00358684 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035869c(); /* FUN_0035869c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0035881c(); /* FUN_0035881c (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00358a74(); /* FUN_00358a74 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358ac8(); /* FUN_00358ac8 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00358bd8(); /* FUN_00358bd8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358c2c(); /* FUN_00358c2c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358c74(); /* FUN_00358c74 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358db8(); /* FUN_00358db8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358dd0(); /* FUN_00358dd0 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358de8(); /* FUN_00358de8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00358fdc(); /* FUN_00358fdc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00359000(); /* FUN_00359000 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035921c(); /* FUN_0035921c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035940c(); /* FUN_0035940c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00359478(); /* FUN_00359478 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035949c(); /* FUN_0035949c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003594bc(); /* FUN_003594bc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00359530(); /* FUN_00359530 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00359568(); /* FUN_00359568 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00359a60(); /* FUN_00359a60 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00359a78(); /* FUN_00359a78 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00359b24(); /* FUN_00359b24 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00359c0c(); /* FUN_00359c0c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00359e28(); /* FUN_00359e28 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a19c(); /* FUN_0035a19c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a1b4(); /* FUN_0035a1b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a1e8(); /* FUN_0035a1e8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a2b8(); /* FUN_0035a2b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a2c4(); /* FUN_0035a2c4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a3b8(); /* FUN_0035a3b8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a4ec(); /* FUN_0035a4ec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a4f8(); /* FUN_0035a4f8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a518(); /* FUN_0035a518 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a5d8(); /* FUN_0035a5d8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a5e4(); /* FUN_0035a5e4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a6b4(); /* FUN_0035a6b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035a9c8(); /* FUN_0035a9c8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035aa90(); /* FUN_0035aa90 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0035abd8(); /* FUN_0035abd8 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0035ac70(); /* FUN_0035ac70 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00361528(); /* FUN_00361528 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003625e4(); /* FUN_003625e4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003629b4(); /* FUN_003629b4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00365b6c(); /* FUN_00365b6c (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0036a908(); /* FUN_0036a908 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_0036b118(); /* FUN_0036b118 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_0036b270(); /* FUN_0036b270 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003722e4(); /* FUN_003722e4 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00376820(); /* FUN_00376820 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_00377824(); /* FUN_00377824 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00377bec(); /* FUN_00377bec (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_00377dcc(); /* FUN_00377dcc (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003a0b04(); /* FUN_003a0b04 (shared cL4 runtime library, out of scope) */
extern sk_u128_t skp0_rt_003a25d4(); /* FUN_003a25d4 (shared cL4 runtime library, out of scope) */
extern word_t skp0_rt_003a261c(); /* FUN_003a261c (shared cL4 runtime library, out of scope) */

/* ---- opaque kernel data globals referenced by this slice ---- */
extern word_t skp0_g_0000fc9d; /* DAT/LAB_0000fc9d */
extern word_t skp0_g_002039f4; /* DAT/LAB_002039f4 */
extern word_t skp0_g_003471a4; /* DAT/LAB_003471a4 */
extern word_t skp0_g_003471a8; /* DAT/LAB_003471a8 */
extern word_t skp0_g_004e9518; /* DAT/LAB_004e9518 */
extern word_t skp0_g_004e9550; /* DAT/LAB_004e9550 */
extern word_t skp0_g_004e956c; /* DAT/LAB_004e956c */
extern word_t skp0_g_004e9634; /* DAT/LAB_004e9634 */
extern word_t skp0_g_005d021c; /* DAT/LAB_005d021c */
extern word_t skp0_g_005d3bbc; /* DAT/LAB_005d3bbc */
extern word_t skp0_g_005d3bc0; /* DAT/LAB_005d3bc0 */
extern word_t skp0_g_005d3bdd; /* DAT/LAB_005d3bdd */
extern word_t skp0_g_005d3be0; /* DAT/LAB_005d3be0 */
extern word_t skp0_g_005d3be4; /* DAT/LAB_005d3be4 */
extern word_t skp0_g_0060e208; /* DAT/LAB_0060e208 */
extern word_t skp0_g_0060e218; /* DAT/LAB_0060e218 */
extern word_t skp0_g_0060e230; /* DAT/LAB_0060e230 */
extern word_t skp0_g_00611b24; /* DAT/LAB_00611b24 */
extern word_t skp0_g_00611b34; /* DAT/LAB_00611b34 */
extern word_t skp0_g_00611b3c; /* DAT/LAB_00611b3c */
extern sk_fnptr skp0_g_00658c00; /* skp0_DAT_00658c00: primary runtime dispatch entry */
extern word_t skp0_g_tls_magic; /* __thread_bss.magic: TLS sentinel compared by the description layer */

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
void skp0_sk_object_describe_root();
word_t skp0_sk_dump_check();
void skp0_sk_dump_finish();
void skp0_sk_object_handle();
uint32_t skp0_sk_object_has_refs();
word_t sk_cleanup_thunk();
void skp0_sk_common_cleanup();
void skp0_sk_error_panic();
void skp0_sk_retain_increment();
void skp0_sk_vspace_walk();
void skp0_sk_dispatch_jump();
void skp0_sk_lookup_install();
void skp0_sk_lookup_install2();
void skp0_sk_map_region_core();
word_t * skp0_sk_node_alloc();
sk_u128_t skp0_sk_node_init();
void skp0_sk_unmap_region();
void skp0_sk_node_config();
void skp0_sk_node_release();
void skp0_sk_node_alloc4();
void skp0_sk_sub_release();
void skp0_sk_sub_alloc();
word_t skp0_sk_sub_init();
void skp0_sk_iterate_children();
void skp0_sk_iterate_walk();
void skp0_sk_find_child();
word_t * skp0_sk_node_alloc2();
sk_u128_t skp0_sk_node_init2();
void skp0_sk_find_slot();
void skp0_sk_rec_descend();
void skp0_sk_desc_node();
void skp0_sk_desc_dispatch();
void skp0_sk_desc_elements();
void skp0_sk_desc_sub();
void skp0_sk_desc_children();
void skp0_sk_desc_slot();
void skp0_sk_desc_recurse();
void skp0_sk_vt_overridden_a();
void skp0_sk_vt_overridden_b();
void skp0_sk_vt_overridden_c();
void skp0_sk_vt_overridden_d();
void skp0_sk_vt_overridden_e();
void skp0_sk_vt_overridden_f();
void skp0_sk_assert_fmt_a();
void skp0_sk_assert_fmt_b();
void skp0_sk_assert_fail();
void skp0_sk_assert_fail2();
sk_u128_t skp0_sk_assert_empty();
void skp0_sk_assert_empty2();
word_t skp0_sk_assert_both();
void skp0_sk_assert_ze_pair();
void skp0_sk_assert_ze_pair2();
sk_fnptr * skp0_sk_pair_store();
void skp0_sk_pair_check_a();
void skp0_sk_pair_check_b();
word_t skp0_sk_assert_nz_pair();
sk_u128_t skp0_sk_assert_nz_triple();
word_t skp0_sk_assert_eq_case();
void skp0_sk_assert_pair_eq();
void skp0_sk_node_validate();
void skp0_sk_assert_pairs_eq();
void skp0_sk_assert_empty3();
void skp0_sk_assert_empty4();
void skp0_sk_pair_check_c();
sk_fnptr * skp0_sk_pair_store2();
void skp0_sk_pair_check_d();
void skp0_sk_pair_check_e();
void skp0_sk_assert_fmt_c();
void skp0_sk_assert_clear_a();
void skp0_sk_assert_clear_b();
void skp0_sk_assert_clear_c();
word_t skp0_sk_assert_clear_d();
word_t skp0_sk_assert_clear_e();
word_t * skp0_sk_pair_alloc();
void skp0_sk_assert_fmt_d();
void skp0_sk_slot_clear_a();
void skp0_sk_slot_clear_b();
void skp0_sk_table_iter();
void skp0_sk_table_method();
word_t skp0_sk_table_lookup();
word_t skp0_sk_table_range();
void skp0_sk_table_insert1();
void skp0_sk_table_insert_n();
void skp0_sk_table_update();
word_t skp0_sk_index_lookup();
void skp0_sk_index_clear_a();
void skp0_sk_index_clear_b();
void skp0_sk_index_clear_c();
sk_u128_t skp0_sk_table_alloc();
void skp0_sk_table_free();
sk_u128_t skp0_sk_table_alloc_node();
void skp0_sk_table_free_node();
uint32_t skp0_sk_index_test();
uint32_t skp0_sk_index_test2();
void skp0_sk_index_decr();
void skp0_sk_index_decr2();
void skp0_sk_rt_wrap_a();
void skp0_sk_rt_wrap_b();
void skp0_sk_rt_wrap_c();
void skp0_sk_boot_cold();
void skp0_sk_boot_cpu();
void skp0_sk_dispatch_mux();
void skp0_sk_abstract_method();
void skp0_sk_vt_init();
void skp0_sk_vt_install();
void skp0_sk_vt_setup();
void skp0_sk_vt_teardown();
void skp0_sk_vt_call();
void skp0_sk_vt_abstract_a();
void skp0_sk_vt_abstract_b();
void skp0_sk_vt_hook_a();
void skp0_sk_vt_hook_b();
void skp0_sk_vt_hook_c();
void skp0_sk_vt_hook_d();
void skp0_sk_vt_hook_e();
void skp0_sk_dtor_pure_a();
void skp0_sk_dtor_pure_b();
void skp0_sk_dtor_pure_c();
void skp0_sk_dtor_pure_d();
void skp0_sk_dtor_pure_e();
void skp0_sk_dtor_pure_f();

/* FUN_00200150 @ 0x00200150   (est. skp0_sk_object_describe_root)
 * Ghidra: void FUN_00200150(void)
 * Entry point of the object-description engine. Performs the standard runtime prologue (save thread context via skp0_rt_0008e518, resolve object fields), then drives two sub-walkers (skp0_sk_dump_check, skp0_sk_dump_finish) and the table iterator; the else path is an unrecoverable panic. Faithful mechanical transcription of the decompiler output.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_object_describe_root(void)
{

  int idx1;
  word_t tmpL2;
  word_t tmp3;
  word_t tmp4;
  word_t tmp5;
  word_t tmpL6;
  word_t tmpL7;
  word_t tmpL8;
  word_t tmp9;
  word_t tmp10;
  word_t outx1;
  word_t outx1_00;
  word_t outx8;
  word_t outx8_00;
  word_t outx8_01;
  word_t outx8_02;
  word_t outx8_03;
  word_t outx8_04;
  word_t outx8_05;
  word_t outx8_06;
  sk_fnptr outx8_07;
  sk_fnptr outx8_08;
  sk_fnptr outx8_09;
  sk_fnptr outx8_10;
  sk_fnptr outx8_11;
  sk_fnptr outx8_12;
  sk_fnptr outx8_13;
  sk_fnptr outx8_14;
  sk_fnptr outx9;
  sk_fnptr outx9_00;
  sk_fnptr outx9_01;
  sk_fnptr outx9_02;
  word_t outx16;
  word_t outx16_00;
  word_t outx16_01;
  word_t tmp11;
  sk_fnptr fnp12;
  word_t tmp13;
  sk_fnptr fnp14;
  word_t savx23;
  word_t savx25;
  word_t savx30;
  sk_u128_t pair15;
  word_t loc98;
  word_t loc88;
  word_t loc80;
  word_t loc70;
  word_t loc68;
  word_t loc58;
  word_t loc20;
  
  tmpL2 = skp0_rt_0008e518().lo;
  skp0_rt_00352b98();
  tmp11 = *(word_t *)(outx1 + 0x10);
  skp0_rt_003494e8();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_003497b4();
  tmp13 = *(word_t *)(outx1_00 + 0x18);
  skp0_rt_0034c60c();
  tmp3 = skp0_rt_00377824().lo;
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034f3d4();
  skp0_rt_0035056c(0xff);
  tmp4 = skp0_rt_00377824().lo;
  tmp5 = skp0_rt_0034b0b4();
  tmpL6 = skp0_rt_003722e4(tmp5,tmp4,tmp4).lo;
  skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8_01 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034d234();
  (*skp0_g_00658c00)();
  skp0_rt_0034d7fc();
  skp0_rt_0034a5c8();
  (*skp0_g_00658c00)(*(word_t *)(outx8_02 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034cde8();
  (*skp0_g_00658c00)();
  skp0_rt_0034a9e8();
  (*skp0_g_00658c00)();
  skp0_rt_0034aadc();
  (*skp0_g_00658c00)();
  skp0_rt_00350464();
  skp0_rt_0034f604();
  tmpL7 = skp0_rt_0031b704();
  skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8_04 + 0x40));
  skp0_rt_00348abc();
  (*skp0_g_00658c00)();
  skp0_rt_0034b758();
  skp0_rt_00350b9c(tmp13);
  tmp5 = skp0_rt_00377bec();
  pair15 = skp0_rt_003508e4();
  tmpL8 = skp0_rt_00310e08(pair15.lo,pair15.hi,tmp5);
  skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8_05 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_0034ac3c();
  fnp12 = *(sk_fnptr *)(outx16_01 + 0x10);
  skp0_rt_0034c694();
  (*fnp12)();
  fnp14 = *(sk_fnptr *)(outx16_00 + 0x20);
  (*fnp14)(outx8_03,savx23 + *(int32_t *)(tmpL7 + 0x24),tmp4);
  tmp9 = skp0_rt_0034b0e4();
  tmp9 = skp0_rt_00355d78(tmp9,tmpL7);
  skp0_rt_003579e8(tmp9,tmpL2 + outx8_06);
  (*fnp12)();
  (*fnp14)(loc98,savx25 + *(int32_t *)(tmpL7 + 0x24),tmp4);
  skp0_rt_0035166c(tmp5);
  skp0_rt_00350524();
  skp0_rt_00351f4c();
  tmp10 = (*outx8_07)();
  if ((tmp10 & 1) != 0) {
    skp0_rt_0034ff88();
    (*fnp14)();
    skp0_rt_00350b9c(loc68 + *(int32_t *)(tmpL6 + 0x30));
    (*fnp14)();
    skp0_rt_00353a00();
    pair15 = skp0_rt_00350494();
    (*outx9)(pair15.lo,pair15.hi,tmpL6);
    idx1 = *(int32_t *)(tmpL6 + 0x30);
    skp0_rt_00351bd4(loc20);
    (*fnp14)();
    fnp12 = *(sk_fnptr *)(outx16_00 + 8);
    (*fnp12)(loc88 + idx1,tmp4);
    pair15 = skp0_rt_00350494(*(word_t *)(outx16 + 0x20));
    skp0_rt_00353b70(pair15.lo,pair15.hi,tmpL6);
    (*outx8_08)();
    (*fnp14)(loc20 + *(int32_t *)(tmpL8 + 0x24),loc88 + *(int32_t *)(tmpL6 + 0x30),tmp4);
    skp0_rt_00351130();
    (*fnp12)();
    skp0_rt_0026c274(outx8_00,outx1_00);
    skp0_rt_00352eb4(tmp13);
    skp0_rt_00350810(loc58,loc20);
    (*outx9_00)();
    skp0_rt_00354afc();
    skp0_rt_0035060c();
    (*outx8_09)();
    skp0_rt_0034de8c();
    pair15 = skp0_rt_00350524();
    skp0_rt_00377bec(pair15.lo,pair15.hi,tmp3);
    skp0_rt_0035156c();
    skp0_rt_00350524(loc80);
    (*outx9_01)();
    skp0_rt_00350704();
    skp0_rt_00350524(loc70);
    (*outx9_02)();
    skp0_rt_0034f014();
    skp0_rt_00350494();
    skp0_rt_003518a0();
    tmp10 = (*outx8_10)();
    if ((tmp10 & 1) != 0) {
      skp0_rt_0035460c();
      skp0_rt_00350bc0(&sk_stack_00000040);
      (*outx8_11)(loc58,tmp3);
      skp0_rt_00350bc0(&sk_stack_00000030);
      (*outx8_12)(loc20,tmpL8);
      (*fnp14)(loc68,loc80,tmp4);
      tmp3 = skp0_rt_00359e28();
      (*fnp14)(tmp3,loc70,tmp4);
      skp0_rt_003511c0(loc88);
      skp0_rt_00353130();
      (*outx8_13)();
      idx1 = *(int32_t *)(tmpL6 + 0x30);
      skp0_rt_00359a78();
      pair15 = skp0_rt_003507bc();
      (*fnp14)(pair15.lo,pair15.hi,tmp4);
      (*fnp12)(loc88 + idx1,tmp4);
      skp0_rt_003511c0(loc88);
      skp0_rt_000ec044();
      (*outx8_14)();
      (*fnp14)(((word_t)(outx16_00 + 0x20) & 0xffffffffffff | 0x48d8000000000000) +
                 (word_t)*(int32_t *)(tmpL8 + 0x24),loc88 + *(int32_t *)(tmpL6 + 0x30),tmp4);
      skp0_rt_003514d0();
      (*fnp12)();
      skp0_rt_0035aa90((word_t)*(int32_t *)(outx1_00 + 0x24));
      pair15 = skp0_rt_003516e4();
      tmp3 = skp0_sk_dump_check(pair15.lo,pair15.hi,tmp5);
      skp0_rt_0035116c();
      skp0_sk_dump_finish();
      skp0_rt_0036b118(tmp3);
      skp0_rt_00353190();
      skp0_rt_0026c274();
      skp0_rt_00353734();
      pair15 = skp0_rt_00084180();
      skp0_rt_001fccf8(pair15.lo,pair15.hi,tmp11,tmp13);
      skp0_rt_0008e500(savx30);
      return;
    }
  }
  skp0_rt_00347d60();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_002007c0 @ 0x002007c0   (est. skp0_sk_dump_check)
 * Ghidra: word_t FUN_002007c0()
 * Object-description helper: runs a runtime branch check (skp0_rt_001e3048 bit 0); on the taken path performs the finish sequence and returns, else falls into the alternate teardown. Wraps shared-runtime calls.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_dump_check()
{

  word_t tmp1;
  word_t outx16;
  
  skp0_rt_0034c034();
  skp0_rt_00310e08(0);
  tmp1 = skp0_rt_001e3048();
  if ((tmp1 & 1) != 0) {
    skp0_rt_0034b804();
    (**(sk_fnptr *)(outx16 + 8))();
    skp0_rt_00084180();
    skp0_rt_0027743c();
    return 0;
  }
  skp0_rt_0034ef68();
  skp0_rt_00277474();
  return 0;
}

/* FUN_0020083c @ 0x0020083c   (est. skp0_sk_dump_finish)
 * Ghidra: void FUN_0020083c(void)
 * Small object-description finalizer: calls the vector-table teardown (skp0_rt_0027a6e0), a runtime release and an object refcount drop.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_dump_finish(void)
{

  skp0_rt_0027a6e0();
  skp0_rt_00351d18();
  skp0_rt_0036b118();
  return;
}

/* FUN_0020086c @ 0x0020086c   (est. skp0_sk_object_handle)
 * Ghidra: void FUN_0020086c(void)
 * Object-handling routine: loads an object slot (offset 0x18), retains it, builds a 4-word frame, walks it, then releases. Ends on an event predicate.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_object_handle(void)
{

  int idx1;
  word_t tmp2;
  word_t tmp3;
  word_t tmp4;
  word_t tmp5;
  word_t tmpL6;
  word_t outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx8_01;
  sk_fnptr outx8_02;
  sk_fnptr outx8_03;
  sk_fnptr outx8_04;
  word_t outx16;
  word_t outx16_00;
  word_t savx20;
  word_t tmp7;
  word_t savx27;
  word_t savx28;
  word_t savx30;
  sk_u128_t pair8;
  sk_u128_t astk40;
  word_t loc30;
  word_t stk28;
  word_t loc20;
  word_t loc10;
  
  pair8 = skp0_rt_0008e518();
  tmpL6 = pair8.hi;
  tmp4 = *(word_t *)(tmpL6 + 0x18);
  tmp3 = *(word_t *)(tmpL6 + 0x10);
  skp0_rt_0034c54c();
  skp0_rt_0034b7b8();
  skp0_rt_00377824();
  skp0_rt_00348d7c();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034aa9c();
  skp0_rt_000e15d8();
  skp0_rt_00351de4();
  tmp2 = skp0_rt_00377bec();
  skp0_rt_0034d404();
  skp0_rt_00310e08();
  skp0_rt_00348fd8();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034b0d4();
  tmp7 = *(word_t *)(savx20 + *(int32_t *)(tmpL6 + 0x24));
  skp0_rt_0036b270(tmp7);
  loc30 = tmp3;
  stk28 = tmp4;
  loc20 = pair8.lo;
  loc10 = tmp7;
  skp0_rt_0034d404();
  tmp3 = skp0_rt_0031b71c();
  tmp4 = skp0_rt_00348c30();
  skp0_rt_00376820(tmp4,tmp3);
  tmp3 = skp0_rt_0035a4ec();
  skp0_rt_00355ca4(tmp3,astk40);
  skp0_rt_001db6b0();
  skp0_rt_0036b118(tmp7);
  skp0_rt_0036b270(tmp7);
  skp0_rt_0034f514();
  skp0_rt_00351cd0();
  skp0_rt_001fea40();
  skp0_rt_0036b118(tmp7);
  skp0_rt_0035166c(tmp2);
  skp0_rt_00350a34();
  skp0_rt_00351c94();
  tmp5 = (*outx8_00)();
  if ((tmp5 & 1) == 0) {
    skp0_rt_00350944(*(word_t *)(outx16_00 + 8));
    (*outx8_04)();
  }
  else {
    idx1 = *(int32_t *)(savx28 + 0x24);
    skp0_rt_0035044c(tmp2);
    skp0_rt_00351c94(pair8.lo,savx27 + idx1);
    tmp5 = (*outx8_01)();
    skp0_rt_00350944(*(word_t *)(outx16_00 + 8));
    (*outx8_02)();
    if ((tmp5 & 1) != 0) {
      skp0_rt_0035072c(*(word_t *)(outx16 + 0x10));
      (*outx8_03)();
      skp0_rt_0034ca28(outx8);
      skp0_rt_001fd4f4();
    }
  }
  skp0_rt_0034f5e4();
  skp0_rt_0031b704();
  pair8 = skp0_rt_0007c1c4();
  skp0_rt_000839d8(pair8.lo,pair8.hi,1);
  skp0_rt_0008e500(savx30);
  return;
}

/* FUN_00200abc @ 0x00200abc   (est. skp0_sk_object_has_refs)
 * Ghidra: uint32_t FUN_00200abc(void)
 * Boolean predicate returning (rt_0 branch & 1): tests a runtime condition, on success loads field 0x18 and returns the branch result, else 0. Likely a "has refs"/"is busy" test.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
uint32_t skp0_sk_object_has_refs(void)
{

  word_t tmp1;
  uint32_t tmp2;
  word_t tmp3;
  word_t outx1;
  sk_fnptr outx8;
  sk_fnptr outx8_00;
  
  skp0_rt_00354708();
  tmp1 = *(word_t *)(outx1 + 0x18);
  skp0_rt_0034f014();
  skp0_rt_0034aebc();
  tmp3 = (*outx8)();
  if ((tmp3 & 1) == 0) {
    tmp2 = 0;
  }
  else {
    skp0_rt_0035044c(tmp1);
    skp0_rt_0035053c();
    tmp2 = (*outx8_00)();
    tmp2 = tmp2 & 1;
  }
  return tmp2;
}

/* FUN_00200b34 @ 0x00200b34   (est. sk_cleanup_thunk)
 * Ghidra: void skp0_thunk_FUN_00200b38(void)
 * Thunk for skp0_sk_common_cleanup (FUN_00200b38): runtime dispatch preamble + cleanup branch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_thunk_FUN_00200b38(void)
{

  word_t outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx9;
  word_t outx16;
  
  skp0_rt_00352800();
  skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_00349178();
  skp0_rt_00351e84();
  skp0_rt_00351c88();
  (*outx9)();
  skp0_rt_0035056c(*(word_t *)(outx16 + 0x20));
  (*outx8_00)();
  return;
}

/* FUN_00200b38 @ 0x00200b38   (est. skp0_sk_common_cleanup)
 * Ghidra: void FUN_00200b38()
 * Common cleanup/teardown: dispatches through skp0_g_00658c00 then runs the standard cleanup sequence.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_common_cleanup()
{

  word_t outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx9;
  word_t outx16;
  
  skp0_rt_00352800();
  skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_00349178();
  skp0_rt_00351e84();
  skp0_rt_00351c88();
  (*outx9)();
  skp0_rt_0035056c(*(word_t *)(outx16 + 0x20));
  (*outx8_00)();
  return;
}

/* FUN_00200bd0 @ 0x00200bd0   (est. skp0_sk_error_panic)
 * Ghidra: void FUN_00200bd0(word_t param_1)
 * Registers an error/panic descriptor: calls skp0_rt_00262b5c with three metadata addresses (skp0_g_00611b24, skp0_g_00611b3c) and the return site 0x206bbc. Likely a failed-assertion/abort registrar.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_error_panic(word_t param_1)
{

  skp0_rt_00262b5c(param_1,&skp0_g_00611b24,&skp0_g_00611b3c,0x206bbc);
  return;
}

/* FUN_00200bf4 @ 0x00200bf4   (est. skp0_sk_retain_increment)
 * Ghidra: void FUN_00200bf4(word_t param_1,word_t param_2,word_t param_3)
 * Retain/increment helper: resolves an object, and under a runtime branch either performs a setup+dispatch or increments a slot counter (offset via g field), trapping (skp0_SoftwareBreakpoint) on carry overflow.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_retain_increment(word_t param_1,word_t param_2,word_t param_3)
{

  int idx1;
  uint8_t inpZR;
  word_t tmp2;
  sk_fnptr fnp3;
  word_t tmp4;
  word_t tmpL5;
  word_t *outx8;
  sk_fnptr outx8_00;
  word_t outx16;
  word_t outx16_00;
  word_t savx20;
  word_t tmpL6;
  sk_u128_t pair7;
  sk_u128_t pair8;
  
  pair7 = skp0_rt_0008e518();
  tmp2 = *(word_t *)(pair7.lo + 0x18);
  skp0_rt_00351fb0();
  skp0_rt_00351238(0xff,tmp2);
  skp0_rt_00377824();
  skp0_rt_0034e130();
  skp0_rt_00310d68();
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034aee4();
  skp0_rt_00349734();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034b0d4();
  skp0_rt_00351238(0xff,tmp2);
  skp0_rt_00377824();
  skp0_rt_00350288(tmp2);
  tmp2 = skp0_rt_00377bec();
  fnp3 = (sk_fnptr)skp0_rt_000a68f4();
  skp0_rt_00350488();
  tmp4 = skp0_rt_00377dcc();
  (*fnp3)(tmp4,tmp2);
  skp0_rt_0034aa54();
  if ((bool)inpZR) {
    skp0_rt_00358de8(*(word_t *)(outx16 + 8));
    (*outx8_00)();
    skp0_rt_0035041c();
    skp0_rt_003594bc();
    skp0_rt_003512f4();
    pair8 = skp0_rt_003722e4();
    skp0_rt_00350744(outx8,pair8.hi,param_3,pair8.lo);
  }
  else {
    fnp3 = *(sk_fnptr *)(outx16_00 + 0x20);
    skp0_rt_00350048();
    (*fnp3)();
    skp0_rt_0035041c();
    skp0_rt_003594bc();
    skp0_rt_003512f4();
    tmpL5 = skp0_rt_003722e4().lo;
    idx1 = *(int32_t *)(tmpL5 + 0x30);
    tmpL5 = (word_t)*(int32_t *)(pair7.lo + 0x24);
    tmpL6 = *(word_t *)(savx20 + tmpL5);
    *outx8 = tmpL6;
    skp0_rt_003514a0((word_t)outx8 + (word_t)idx1);
    (*fnp3)();
    if (skp0_SCARRY8(tmpL6,1)) {
                    /* WARNING: Does not return */
      fnp3 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x200dc8);
      (*fnp3)();
    }
    *(word_t *)(savx20 + tmpL5) = tmpL6 + 1;
    skp0_rt_0034bc94(outx8);
  }
  skp0_rt_000839d8();
  skp0_rt_0008e500(pair7.hi);
  return;
}

/* FUN_00200dc8 @ 0x00200dc8   (est. skp0_sk_vspace_walk)
 * Ghidra: void FUN_00200dc8(void)
 * Table walker: iterates a collection via skp0_rt_0035881c/skp0_rt_00350b00, tests each entry with skp0_sk_index_test (00207ca0), on miss performs lookup (skp0_sk_index_decr 00207e0c + skp0_sk_index_lookup 002075e0) and stores to a slot; recursion and release paths. Ends in a conditional return or panic.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vspace_walk(void)
{

  bool flg1;
  word_t tmp2;
  int idx3;
  bool flg4;
  uint8_t inpZR;
  word_t tmp5;
  word_t tmp6;
  word_t tmpL7;
  word_t tmp8;
  word_t tmp9;
  word_t tmp10;
  word_t tmp11;
  word_t tmp12;
  word_t tmp13;
  word_t tmp14;
  word_t tmpL15;
  word_t outx1;
  word_t tmp16;
  word_t outx8;
  word_t outx8_00;
  word_t outx8_01;
  word_t outx8_02;
  sk_fnptr outx8_03;
  sk_fnptr outx8_04;
  sk_fnptr outx8_05;
  sk_fnptr outx8_06;
  sk_fnptr outx8_07;
  sk_fnptr outx8_08;
  sk_fnptr outx9;
  sk_fnptr outx9_00;
  word_t outx16;
  word_t outx16_00;
  word_t outx16_01;
  sk_fnptr fnp17;
  word_t *savx23;
  word_t *savx25;
  word_t *savx26;
  word_t savx30;
  sk_u128_t pair18;
  sk_u128_t pair19;
  word_t loc140;
  word_t loc118;
  word_t loce8;
  word_t locc8;
  word_t locb0;
  word_t loca8;
  word_t loc80;
  word_t loc40;
  word_t stk38;
  word_t loc30;
  uint8_t astk28[8];
  word_t loc20;
  word_t stk18;
  word_t loc10;
  uint8_t astk8[8];
  
  pair18 = skp0_rt_0008e518();
  tmpL15 = pair18.hi;
  skp0_rt_00355db4();
  tmp16 = *(word_t *)(outx1 + 0x10);
  tmp2 = *(word_t *)(outx1 + 0x18);
  skp0_rt_0034c108();
  skp0_rt_00077894();
  skp0_rt_00377824();
  skp0_rt_00348d4c();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_00350428();
  skp0_rt_003509a4();
  skp0_rt_0034d424();
  tmp5 = skp0_rt_00377824().lo;
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034d89c();
  skp0_rt_00310d68(0xff);
  skp0_rt_0034e67c();
  skp0_rt_00310d68();
  skp0_rt_003490b8(astk28);
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034b0d4();
  skp0_rt_0034a5c8();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_00350464();
  skp0_rt_003509a4();
  skp0_rt_0034f534();
  tmp6 = skp0_rt_00377bec();
  pair19 = skp0_rt_0035050c();
  tmp6 = skp0_rt_00310e08(pair19.lo,pair19.hi,tmp6);
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_00350428();
  skp0_rt_00355fac();
  skp0_rt_0035041c();
  skp0_rt_003594bc();
  tmpL7 = skp0_rt_003722e4(0).lo;
  skp0_rt_0034ab20();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034d888();
  skp0_rt_00350530();
  tmp8 = skp0_rt_00310d68();
  skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8_00 + 0x40));
  skp0_rt_00348bbc();
  (*skp0_g_00658c00)();
  skp0_rt_0034b3d8();
  skp0_rt_0035aa90((word_t)*(int32_t *)(tmpL15 + 0x24));
  loc40 = tmpL15;
  skp0_rt_0035678c(0);
  skp0_rt_0035139c();
  tmp9 = skp0_rt_0031b71c();
  skp0_sk_common_cleanup(astk28);
  pair19 = skp0_rt_0036b118(tmpL15);
  skp0_rt_00350488(pair19.lo,pair19.hi,0x66d5d8);
  tmp10 = skp0_rt_0031b760();
  tmp11 = skp0_rt_00348a50();
  tmp11 = skp0_rt_00376820(tmp11,tmp9).lo;
  loc30 = tmp11;
  skp0_rt_00376820(&skp0_g_004e9634,tmp10,&loc30);
  skp0_rt_0034dae8();
  (**(sk_fnptr *)(outx16_01 + 0x20))(&loc40,astk28,tmp10);
  loc10 = loc40;
  tmp12 = skp0_rt_00348c30();
  pair19 = skp0_rt_00376820(tmp12,tmp9);
  tmp12 = pair19.lo;
  skp0_rt_00350b00(&loc20,tmp12,pair19.hi,skp0_rt_00310924);
  skp0_sk_table_iter();
  skp0_rt_00352b98(outx16_00 + 8);
  skp0_rt_00353718();
  skp0_rt_00352554(outx8_01 + 8);
  skp0_rt_00353bac();
  skp0_rt_00355dc0(outx8_02 + 8);
  skp0_rt_00352bbc();
  flg4 = true;
  pair19 = skp0_rt_0035881c();
  while( true ) {
    skp0_rt_00350b00(&loc40,pair19.lo,pair19.hi,skp0_rt_000277b8);
    skp0_sk_table_iter();
    tmp13 = skp0_sk_index_test((word_t)(&loc20),(word_t)(&loc40),(word_t)(tmp9),(word_t)(tmp12));
    flg1 = (tmp13 & 1) != 0;
    if (!flg1) {
      stk38 = stk18;
      loc40 = loc20;
      skp0_sk_index_decr((word_t)(&loc20),(word_t)(&loc40),(word_t)(tmp10),(word_t)(tmp11));
      idx3 = *(int32_t *)(tmpL7 + 0x30);
      tmp14 = skp0_sk_index_lookup((word_t)(loc80 + idx3),(word_t)(&loc20),(word_t)(tmp10),(word_t)(tmp12));
      *savx23 = tmp14;
      (**(sk_fnptr *)(outx16_00 + 0x20))
                ((word_t)savx23 + (word_t)*(int32_t *)(tmpL7 + 0x30),loc80 + idx3,tmp6);
    }
    skp0_rt_00351548(savx23,flg1);
    skp0_rt_000839d8();
    skp0_rt_0035457c();
    pair19 = skp0_rt_00351274();
    (*outx8_03)(pair19.lo,pair19.hi,tmp8);
    skp0_rt_0034aa54(savx25);
    if ((bool)inpZR) break;
    skp0_rt_00354570(*savx25);
    (**(sk_fnptr *)(outx16_00 + 0x20))
              (locb0,(word_t)savx25 + (word_t)*(int32_t *)(tmpL7 + 0x30),tmp6);
    skp0_rt_00352eb4(tmp2);
    skp0_rt_00350b9c(loca8,locb0);
    (*outx9)();
    skp0_rt_0034d688();
    skp0_rt_003510dc();
    (*outx8_04)();
    skp0_rt_0034de8c();
    pair19 = skp0_rt_003505e8();
    skp0_rt_00377bec(pair19.lo,pair19.hi,tmp5);
    skp0_rt_0031b110();
    skp0_rt_0035102c();
    skp0_rt_00350b9c(pair18.lo);
    (*outx9_00)();
    tmp14 = skp0_rt_0034f9ec(&sk_stack_00000040);
    (*outx8_05)(tmp14,tmp5);
    skp0_rt_0034b2a8();
    savx23 = savx26;
    if ((bool)inpZR) {
      skp0_rt_003510d0(&loc30);
      skp0_rt_00357be0();
      (*outx8_07)();
      flg4 = false;
      skp0_rt_0035675c();
      pair19 = skp0_rt_00357350();
      tmpL7 = loca8;
    }
    else {
      skp0_rt_00354bb0();
      fnp17 = (sk_fnptr)*savx26;
      pair19 = skp0_rt_003510ac();
      (*fnp17)(pair19.lo,pair19.hi,savx26);
      pair19 = skp0_rt_00084180();
      (*fnp17)(pair19.lo,pair19.hi,savx26);
      pair19 = skp0_rt_003524b0();
      skp0_rt_00350884(pair19.lo,pair19.hi,locc8);
      if (!(bool)inpZR) {
        skp0_rt_00358ac8();
        skp0_rt_0036b118();
        skp0_rt_0035748c(&stk38);
        pair19 = skp0_rt_003507e0();
        (*outx8_08)(pair19.lo,pair19.hi,locc8);
        skp0_rt_00357338(&stk18);
        skp0_rt_0035063c(outx16,loc140);
        skp0_rt_001fd4f4();
        skp0_rt_0034bec4();
        skp0_rt_0031b704();
        skp0_rt_00352c68();
L_002014d4:
        skp0_rt_00350774();
        skp0_rt_000839d8();
        skp0_rt_003504e8();
        skp0_rt_00356e34();
        pair19 = skp0_rt_00352c68();
        tmp16 = pair19.hi;
        loc118 = pair19.lo;
L_0020150c:
        skp0_rt_000839d8(loc118,tmp16,1);
        skp0_rt_0008e500(savx30);
        return;
      }
      tmp14 = skp0_rt_0034f9ec(astk8);
      (*outx8_06)(tmp14,savx26);
      skp0_rt_0035675c();
      pair19 = skp0_rt_00357350();
      tmpL7 = loce8;
    }
  }
  skp0_rt_00358ac8();
  skp0_rt_0036b118();
  if (!flg4) {
    skp0_rt_0031b704(0xff,tmp16,tmp2);
    skp0_rt_00352efc();
    skp0_rt_00356e34();
    tmp16 = 1;
    goto L_0020150c;
  }
  skp0_rt_0031b704(0,tmp16,tmp2);
  skp0_rt_00351d24();
  goto L_002014d4;
}

/* FUN_0020152c @ 0x0020152c   (est. skp0_sk_dispatch_jump)
 * Ghidra: void FUN_0020152c(void)
 * Dispatch jump: resolves a vtable slot (offset 0x10), calls through it, then falls into an unrecovered jumptable (indirect call) — decompiler artifact.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_dispatch_jump(void)
{

  word_t tmpL1;
  sk_fnptr fnp2;
  word_t outx8;
  word_t savx19;
  word_t savx21;
  sk_fnptr UNRECOVERED_JUMPTABLE;
  
  skp0_rt_00357cb4();
  tmpL1 = skp0_rt_00351cc4();
  UNRECOVERED_JUMPTABLE = *(sk_fnptr *)(tmpL1 + 0x10);
  skp0_rt_003499f0();
  (**(sk_fnptr *)(outx8 + 0x10))();
  skp0_rt_003514b8(*(word_t *)(savx19 + 0x18));
  fnp2 = (sk_fnptr)skp0_rt_00310924();
  skp0_rt_0034c60c();
  tmpL1 = skp0_rt_0031b858();
  skp0_rt_000e15d8(savx21 + *(int32_t *)(tmpL1 + 0x24));
  (*fnp2)();
  skp0_rt_0035631c();
  skp0_rt_00350af4();
  skp0_rt_00357c74();
                    /* WARNING: Could not recover jumptable at 0x002015d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}

/* FUN_00201788 @ 0x00201788   (est. skp0_sk_lookup_install)
 * Ghidra: void FUN_00201788(word_t param_1,word_t param_2,word_t param_3)
 * Lookup-and-install: resolves an object range, walks via skp0_rt_0031b2ec, validates a slot within bounds; on range match records the node; else panics with error codes 0x108/0x10a/0x10c. Returns via the standard epilogue or noreturn panic.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_lookup_install(word_t param_1,word_t param_2,word_t param_3)
{

  word_t tmp1;
  int idx2;
  int idx3;
  word_t *ptl4;
  word_t tmp5;
  word_t tmp6;
  word_t tmpL7;
  word_t tmpL8;
  word_t tmp9;
  word_t tmpL10;
  word_t tmp11;
  word_t *ptl12;
  word_t outx8;
  word_t outx8_00;
  word_t outx8_01;
  word_t outx8_02;
  sk_fnptr outx8_03;
  sk_fnptr outx8_04;
  word_t tmp13;
  sk_fnptr outx8_05;
  sk_fnptr outx8_06;
  sk_fnptr outx8_07;
  sk_fnptr outx8_08;
  sk_fnptr outx8_09;
  sk_fnptr outx8_10;
  sk_fnptr outx8_11;
  sk_fnptr outx9;
  sk_fnptr outx9_00;
  word_t outx16;
  word_t outx16_00;
  word_t outx16_01;
  word_t outx16_02;
  word_t savx19;
  word_t savx20;
  sk_fnptr fnp14;
  word_t tmpL15;
  word_t tmpL16;
  sk_fnptr fnp17;
  word_t savx28;
  word_t savx30;
  sk_u128_t pair18;
  word_t locb8;
  word_t *loca0;
  word_t loc60;
  word_t lStack_50;
  word_t loc18;
  
  pair18 = skp0_rt_0008e518();
  ptl12 = (word_t *)pair18.hi;
  ptl4 = (word_t *)pair18.lo;
  tmp13 = *(word_t *)(param_3 + 0x10);
  tmp1 = *(word_t *)(param_3 + 0x18);
  skp0_rt_0034d598();
  skp0_rt_003510f4(0xff);
  tmp5 = skp0_rt_00377824().lo;
  tmp6 = skp0_rt_0034b0b4();
  tmpL7 = skp0_rt_003722e4(tmp6,tmp5,tmp5).lo;
  skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_00348b5c();
  (*skp0_g_00658c00)();
  skp0_rt_0034bc6c();
  skp0_rt_0034a5c8();
  (*skp0_g_00658c00)(*(word_t *)(outx8_00 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_00350434();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_0034a120();
  (*skp0_g_00658c00)();
  skp0_rt_0034bc58();
  skp0_rt_0034e0c4();
  skp0_rt_0031b704();
  skp0_rt_00348e18();
  (*skp0_g_00658c00)(*(word_t *)(outx8_01 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034e6cc();
  (*skp0_g_00658c00)();
  skp0_rt_0034f730();
  (*skp0_g_00658c00)();
  skp0_rt_0034b4c0();
  skp0_rt_00351b2c(tmp1,tmp13);
  tmp6 = skp0_rt_00377bec();
  skp0_rt_00350308();
  tmpL8 = skp0_rt_00310e08();
  skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8_02 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_00350464();
  skp0_rt_0035a2b8();
  fnp14 = *(sk_fnptr *)(outx16_01 + 0x10);
  skp0_rt_0035056c();
  tmp9 = (*fnp14)();
  fnp17 = *(sk_fnptr *)(outx16_00 + 0x20);
  pair18 = skp0_rt_00358bd8(tmp9,savx28 + *(int32_t *)(savx19 + 0x24));
  (*fnp17)(pair18.lo,pair18.hi,tmp5);
  skp0_rt_0034b0e4();
  tmpL10 = skp0_rt_00310e08();
  idx2 = *(int32_t *)(tmpL10 + 0x24);
  skp0_rt_00356304(tmpL10,(word_t)ptl12 + (word_t)idx2);
  (*fnp14)();
  pair18 = skp0_rt_00352dc4((word_t)*(int32_t *)(savx19 + 0x24));
  (*fnp17)(pair18.lo,pair18.hi,tmp5);
  skp0_rt_00310e20(tmp6);
  skp0_rt_0034e054();
  skp0_rt_00351f4c();
  tmp11 = (*outx8_03)();
  if ((tmp11 & 1) != 0) {
    pair18 = skp0_rt_0035145c();
    (*fnp17)(pair18.lo,pair18.hi,tmp5);
    skp0_rt_00351438(loc60 + *(int32_t *)(tmpL7 + 0x30));
    (*fnp17)();
    skp0_rt_00351c4c();
    skp0_rt_0034c9d8();
    (*outx9)();
    idx3 = *(int32_t *)(tmpL7 + 0x30);
    pair18 = skp0_rt_0009e234();
    (*fnp17)(pair18.lo,pair18.hi,tmp5);
    fnp14 = *(sk_fnptr *)(outx16_00 + 8);
    (*fnp14)(lStack_50 + idx3,tmp5);
    skp0_rt_0034c9d8(*(word_t *)(outx16 + 0x20));
    (*outx8_04)();
    (*fnp17)(loc18 + *(int32_t *)(tmpL8 + 0x24),lStack_50 + *(int32_t *)(tmpL7 + 0x30),tmp5);
    (*fnp14)(lStack_50,tmp5);
    tmpL7 = *ptl12;
    tmpL10 = *(word_t *)((word_t)ptl12 + (word_t)idx2);
    if (tmpL7 <= tmpL10) {
      tmpL16 = (word_t)*(int32_t *)(savx19 + 0x24);
      fnp17 = (sk_fnptr)skp0_rt_0031b2ec(tmp1);
      (*fnp17)((word_t)ptl4 + tmpL16,loc18,tmp13,tmp1);
      tmpL15 = *ptl4;
      if (tmpL15 < tmpL7 || tmpL10 <= tmpL15) {
        skp0_rt_0034b348();
        tmp13 = 0x108;
      }
      else {
        skp0_rt_003584ec(loca0);
        skp0_rt_001fe9a8();
        tmpL7 = *loca0;
        skp0_rt_00359478();
        skp0_rt_000e15d8();
        (*outx8_05)();
        if (tmpL15 == tmpL7) {
          skp0_rt_00351750(tmp1);
          skp0_rt_0035179c(&sk_stack_00000040);
          (*outx9_00)(tmp13,tmp1);
          skp0_rt_0034a30c(tmp6);
          skp0_rt_0034beec((word_t)ptl4 + tmpL16,savx19);
          tmp11 = (*outx8_06)();
          skp0_rt_00350524();
          (*fnp14)();
          if ((tmp11 & 1) != 0) {
            skp0_rt_00354afc();
            (*outx8_07)(loc18,tmpL8);
L_00201d3c:
            skp0_rt_0008e500(savx30);
            return;
          }
          skp0_rt_0034b348();
          tmp13 = 0x10a;
        }
        else {
          tmp13 = *(word_t *)(savx20 + *(int32_t *)(tmpL10 + 0x24));
          skp0_rt_0036b270(tmp13);
          skp0_rt_00352ca4(&sk_stack_00000038);
          pair18 = skp0_rt_000b43d0();
          skp0_rt_001fea40(pair18.lo,pair18.hi,tmp5,tmp6);
          tmp13 = skp0_rt_0036b118(tmp13).lo;
          skp0_rt_00353fa0(*(word_t *)(outx16_00 + 0x10),tmp13,(word_t)ptl4 + tmpL16);
          (*outx8_08)();
          skp0_rt_00310e20(tmp6);
          skp0_rt_0034eef8();
          skp0_rt_0034fdbc();
          tmp11 = (*outx8_09)();
          if ((tmp11 & 1) == 0) {
            skp0_rt_00084180();
            (*fnp14)();
            tmp13 = skp0_rt_00351c28();
            (*outx8_11)(tmp13,tmpL8);
          }
          else {
            idx2 = *(int32_t *)(tmpL8 + 0x24);
            skp0_rt_0035044c(tmp6);
            skp0_rt_0034fdbc(locb8,tmpL7 + idx2);
            tmp11 = (*outx8_10)();
            skp0_rt_00084180();
            (*fnp14)();
            fnp14 = *(sk_fnptr *)(outx16_02 + 8);
            skp0_rt_00350630();
            (*fnp14)();
            if ((tmp11 & 1) != 0) {
              skp0_rt_003567bc();
              (*fnp14)();
              goto L_00201d3c;
            }
          }
          skp0_rt_0034b348();
          tmp13 = 0x10c;
        }
      }
      skp0_rt_003486b8(tmp13);
      skp0_rt_0034975c();
      goto L_00201bb0;
    }
  }
  skp0_rt_00347d60();
L_00201bb0:
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_00201d9c @ 0x00201d9c   (est. skp0_sk_lookup_install2)
 * Ghidra: void FUN_00201d9c(word_t param_1,word_t param_2,word_t param_3)
 * Second lookup-and-install variant (parallel to 00201788): same range/slot validation with panic codes 0x115/0x117/0x119.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_lookup_install2(word_t param_1,word_t param_2,word_t param_3)
{

  word_t tmp1;
  int idx2;
  int idx3;
  word_t *ptl4;
  word_t tmp5;
  word_t tmp6;
  word_t tmpL7;
  word_t tmpL8;
  word_t tmp9;
  word_t tmp10;
  word_t tmpL11;
  word_t tmp12;
  word_t outx8;
  word_t outx8_00;
  word_t outx8_01;
  sk_fnptr outx8_02;
  sk_fnptr outx8_03;
  word_t tmp13;
  sk_fnptr outx8_04;
  sk_fnptr outx8_05;
  sk_fnptr outx8_06;
  sk_fnptr outx8_07;
  sk_fnptr outx8_08;
  sk_fnptr outx8_09;
  sk_fnptr outx8_10;
  sk_fnptr outx8_11;
  sk_fnptr outx9;
  sk_fnptr outx9_00;
  word_t outx16;
  word_t outx16_00;
  word_t outx16_01;
  sk_fnptr fnp14;
  word_t savx20;
  word_t tmpL15;
  sk_fnptr fnp16;
  word_t savx23;
  word_t tmpL17;
  word_t savx24;
  word_t savx30;
  sk_u128_t pair18;
  sk_u128_t pair19;
  word_t locc8;
  word_t *loca0;
  word_t loc68;
  word_t loc60;
  word_t loc48;
  word_t loc28;
  
  pair18 = skp0_rt_0008e518();
  ptl4 = (word_t *)pair18.lo;
  tmp13 = *(word_t *)(param_3 + 0x10);
  tmp1 = *(word_t *)(param_3 + 0x18);
  skp0_rt_0034de64();
  skp0_rt_0034de44();
  tmp5 = skp0_rt_00377824().lo;
  skp0_rt_0034f5b4();
  tmp6 = skp0_rt_00377bec();
  skp0_rt_0034d404();
  tmpL7 = skp0_rt_00310e08();
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034c8c8();
  skp0_rt_0034b0b4();
  skp0_rt_00355adc();
  skp0_rt_003722e4();
  tmpL8 = skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034d294();
  (*skp0_g_00658c00)();
  skp0_rt_0034d7fc();
  skp0_rt_00349c70();
  (*skp0_g_00658c00)(*(word_t *)(outx8_00 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_0034a4e0();
  (*skp0_g_00658c00)();
  skp0_rt_00349f5c();
  (*skp0_g_00658c00)();
  skp0_rt_0034ba68();
  skp0_rt_00077894(0);
  skp0_rt_0031b704();
  skp0_rt_00348d4c();
  (*skp0_g_00658c00)(*(word_t *)(outx8_01 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034e6cc();
  (*skp0_g_00658c00)();
  skp0_rt_0034f730();
  (*skp0_g_00658c00)();
  skp0_rt_0034b758();
  skp0_rt_0034d404();
  tmp9 = skp0_rt_00310f04();
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034b71c();
  fnp16 = *(sk_fnptr *)(outx16_01 + 0x10);
  skp0_rt_00351118();
  tmp10 = (*fnp16)();
  fnp14 = *(sk_fnptr *)(outx16_00 + 0x20);
  skp0_rt_00358dd0(tmp10,savx23 + *(int32_t *)(savx24 + 0x24));
  (*fnp14)();
  skp0_rt_0034b0e4();
  tmpL11 = skp0_rt_00310f04();
  idx2 = *(int32_t *)(tmpL11 + 0x24);
  (*fnp16)();
  pair19 = skp0_rt_00354264((word_t)*(int32_t *)(savx24 + 0x24));
  (*fnp14)(pair19.lo,pair19.hi,tmp5);
  skp0_rt_00352afc();
  skp0_rt_00310e20();
  tmp10 = skp0_rt_003505d0();
  skp0_rt_00350cb4(tmp10,loc48);
  tmp12 = (*outx8_02)();
  if ((tmp12 & 1) != 0) {
    pair19 = skp0_rt_000e72b0();
    (*fnp14)(pair19.lo,pair19.hi,tmp5);
    skp0_rt_00351abc(loc68 + *(int32_t *)(tmpL8 + 0x30));
    (*fnp14)();
    skp0_rt_00352bb0();
    pair19 = skp0_rt_00350b78();
    (*outx9)(pair19.lo,pair19.hi,tmpL8);
    idx3 = *(int32_t *)(tmpL8 + 0x30);
    pair19 = skp0_rt_003504ac();
    (*fnp14)(pair19.lo,pair19.hi,tmp5);
    fnp16 = *(sk_fnptr *)(outx16_00 + 8);
    (*fnp16)(loc60 + idx3,tmp5);
    pair19 = skp0_rt_00350b78(*(word_t *)(outx16 + 0x20));
    (*outx8_03)(pair19.lo,pair19.hi,tmpL8);
    pair19 = skp0_rt_00359c0c((word_t)*(int32_t *)(tmpL8 + 0x30));
    (*fnp14)(pair19.lo,pair19.hi,tmp5);
    (*fnp16)(loc60,tmp5);
    tmpL8 = *(word_t *)pair18.hi;
    tmpL11 = *(word_t *)((word_t)pair18.hi + (word_t)idx2);
    if (tmpL8 <= tmpL11) {
      tmpL17 = (word_t)*(int32_t *)(savx24 + 0x24);
      fnp14 = (sk_fnptr)skp0_rt_0031b2bc(tmp1);
      (*fnp14)((word_t)ptl4 + tmpL17,loc28,tmp13,tmp1);
      tmpL15 = *ptl4;
      if (tmpL15 < tmpL8 || tmpL11 < tmpL15) {
        skp0_rt_0034b348();
        tmp13 = 0x115;
      }
      else {
        skp0_rt_003584ec(loca0);
        skp0_rt_001fe9a8();
        tmpL8 = *loca0;
        skp0_rt_00359478();
        skp0_rt_00351160();
        (*outx8_04)();
        if (tmpL15 == tmpL8) {
          skp0_rt_003512d8();
          skp0_rt_00351e48(&sk_stack_00000030);
          (*outx9_00)(tmp13,tmp1);
          skp0_rt_0034a30c(tmp6);
          skp0_rt_0034beec((word_t)ptl4 + tmpL17,savx24);
          (*outx8_05)();
          skp0_rt_0034eeb8();
          (*fnp16)();
          if ((savx20 & 1) != 0) {
L_00202344:
            skp0_rt_0035a4f8();
            (*outx8_10)(loc28,tmp9);
            skp0_rt_0008e500(savx30);
            return;
          }
          skp0_rt_0034b348();
          tmp13 = 0x117;
        }
        else {
          tmp13 = *(word_t *)(savx20 + (word_t)*(int32_t *)(tmpL11 + 0x24));
          skp0_rt_0036b270(tmp13);
          skp0_rt_00351e48(&sk_stack_00000040);
          pair18 = skp0_rt_000b43d0();
          skp0_rt_001fea40(pair18.lo,pair18.hi,tmp5,tmp6);
          tmp13 = skp0_rt_0036b118(tmp13).lo;
          skp0_rt_00353c6c(*(word_t *)(outx16_00 + 0x10),tmp13,(word_t)ptl4 + tmpL17);
          (*outx8_06)();
          skp0_rt_00310e20(tmp6);
          skp0_rt_0034bccc();
          skp0_rt_0034beec();
          tmp12 = (*outx8_07)();
          if ((tmp12 & 1) == 0) {
            skp0_rt_0035060c();
            (*fnp16)();
            skp0_rt_00350bc0(&sk_stack_00000048);
            (*outx8_11)(savx24,tmpL7);
          }
          else {
            idx2 = *(int32_t *)(tmpL7 + 0x24);
            skp0_rt_0035044c(tmp6);
            skp0_rt_0034beec(locc8,savx24 + idx2);
            (*outx8_08)();
            skp0_rt_0034f4c4();
            (*fnp16)();
            skp0_rt_00350bc0(&sk_stack_00000048);
            skp0_rt_00350518();
            (*outx8_09)();
            if (((word_t)idx2 & 1U) != 0) goto L_00202344;
          }
          skp0_rt_0034b348();
          tmp13 = 0x119;
        }
      }
      skp0_rt_003486b8(tmp13);
      skp0_rt_0034975c();
      goto L_002021e4;
    }
  }
  skp0_rt_00350410();
  skp0_rt_003484e4();
  skp0_rt_003499dc();
L_002021e4:
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_002023c4 @ 0x002023c4   (est. skp0_sk_map_region_core)
 * Ghidra: void FUN_002023c4(word_t param_1,word_t param_2,word_t param_3)
 * Region map core: large object-map routine. Resolves ranges, iterates entries via skp0_rt_0031b050, validates containment (panic codes 0x126/0x127/0x12a/0x131/0x133/300), installs and releases nodes.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_map_region_core(word_t param_1,word_t param_2,word_t param_3)
{

  int idx1;
  word_t *ptl2;
  word_t *ptu3;
  word_t tmpL4;
  word_t tmp5;
  word_t tmp6;
  word_t tmpL7;
  word_t tmp8;
  word_t outx8;
  word_t outx8_00;
  word_t outx8_01;
  word_t outx8_02;
  word_t outx8_03;
  sk_fnptr outx8_04;
  sk_fnptr outx8_05;
  sk_fnptr outx8_06;
  sk_fnptr outx8_07;
  sk_fnptr outx8_08;
  word_t outx8_09;
  sk_fnptr outx8_10;
  sk_fnptr outx8_11;
  sk_fnptr outx8_12;
  sk_fnptr outx8_13;
  sk_fnptr outx8_14;
  sk_fnptr outx8_15;
  sk_fnptr outx8_16;
  sk_fnptr outx8_17;
  sk_fnptr outx8_18;
  sk_fnptr outx8_19;
  sk_fnptr outx9;
  word_t outx9_00;
  sk_fnptr outx9_01;
  sk_fnptr outx9_02;
  sk_fnptr outx9_03;
  sk_fnptr outx9_04;
  sk_fnptr outx9_05;
  sk_fnptr outx9_06;
  sk_fnptr outx9_07;
  sk_fnptr outx9_08;
  sk_fnptr outx9_09;
  sk_fnptr outx9_10;
  word_t *outx16;
  word_t outx16_00;
  word_t outx16_01;
  word_t outx16_02;
  word_t *ptu9;
  word_t savx20;
  sk_fnptr fnp10;
  word_t savx21;
  sk_fnptr fnp11;
  sk_fnptr fnp12;
  word_t tmpL13;
  word_t tmpL14;
  word_t *ptl15;
  word_t savx25;
  word_t savx30;
  sk_u128_t pair16;
  sk_u128_t pair17;
  word_t loc120;
  word_t lStack_a0;
  word_t loc98;
  word_t loc90;
  word_t loc88;
  word_t loc68;
  word_t loc60;
  word_t *loc48;
  word_t loc30;
  word_t loc28;
  word_t loc20;
  word_t *loc18;
  word_t *loc10;
  uint8_t astk8[8];
  
  pair16 = skp0_rt_0008e518();
  ptl2 = (word_t *)pair16.lo;
  tmp5 = *(word_t *)(param_3 + 0x18);
  skp0_rt_0034cd7c();
  skp0_rt_00350b84();
  ptu3 = (word_t *)skp0_rt_00377824().lo;
  skp0_rt_0034b0b4();
  skp0_rt_00353534();
  tmpL4 = skp0_rt_003722e4().lo;
  skp0_rt_000a6f88();
  loc18 = outx16;
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034c684();
  (*skp0_g_00658c00)();
  skp0_rt_00350464();
  skp0_rt_0034911c();
  loc28 = outx16_00;
  (*skp0_g_00658c00)(*(word_t *)(outx8_01 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_00350434();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_00350434();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_0034a9d4();
  (*skp0_g_00658c00)();
  skp0_rt_0034a9c0();
  (*skp0_g_00658c00)();
  skp0_rt_0034a400();
  (*skp0_g_00658c00)();
  skp0_rt_0034b758();
  pair17 = skp0_rt_0035050c();
  skp0_rt_0031b704(pair17.lo,pair17.hi,tmp5);
  skp0_rt_00348d7c();
  (*skp0_g_00658c00)(*(word_t *)(outx8_02 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_0034aadc();
  (*skp0_g_00658c00)();
  skp0_rt_0034b640();
  (*skp0_g_00658c00)();
  skp0_rt_0034a9ac();
  (*skp0_g_00658c00)();
  skp0_rt_0034c074();
  skp0_rt_00359568(tmp5);
  skp0_rt_003508d8();
  tmp5 = skp0_rt_00377bec();
  pair17 = skp0_rt_003504e8();
  loc20 = skp0_rt_00310e08(pair17.lo,pair17.hi,tmp5);
  skp0_rt_000a6f88();
  (*skp0_g_00658c00)(*(word_t *)(outx8_03 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_00350434();
  skp0_rt_0034acf0();
  (*skp0_g_00658c00)();
  skp0_rt_0034ac14();
  (*skp0_g_00658c00)();
  skp0_rt_0034aa28();
  fnp10 = *(sk_fnptr *)(outx16_01 + 0x10);
  skp0_rt_00351abc();
  tmp6 = (*fnp10)();
  fnp11 = *(sk_fnptr *)(loc28 + 0x20);
  skp0_rt_00352a28(tmp6,savx21 + *(int32_t *)(savx25 + 0x24));
  (*fnp11)();
  skp0_rt_0034b0e4();
  tmpL7 = skp0_rt_00310e08();
  skp0_rt_00356278(tmpL7,(word_t)pair16.hi + (word_t)*(int32_t *)(tmpL7 + 0x24));
  loc10 = (word_t *)(outx16_01 + 0x10);
  tmp6 = (*fnp10)();
  skp0_rt_00353c6c(tmp6,loc60 + *(int32_t *)(savx25 + 0x24));
  (*fnp11)();
  skp0_rt_00310e20(tmp5);
  skp0_rt_0034b8cc();
  skp0_rt_00350ac4();
  tmp8 = (*outx8_04)();
  if ((tmp8 & 1) != 0) {
    loc10 = (word_t *)((word_t)loc10 & 0xffffffffffff | 0xe3ba000000000000);
    skp0_rt_00353390();
    skp0_rt_00350768();
    (*fnp11)();
    skp0_rt_00359e28();
    skp0_rt_003508c0();
    (*fnp11)();
    skp0_rt_00352474();
    skp0_rt_0034e54c();
    (*outx9)();
    idx1 = *(int32_t *)(tmpL4 + 0x30);
    skp0_rt_00358db8();
    skp0_rt_003508c0();
    (*fnp11)();
    ptu9 = (word_t *)(loc28 + 8);
    fnp12 = (sk_fnptr)*ptu9;
    (*fnp12)((word_t)loc48 + (word_t)idx1,ptu3);
    skp0_rt_0034e54c(loc18[4]);
    loc18 = loc18 + 4;
    skp0_rt_00354128();
    (*outx8_05)();
    skp0_rt_0035a518((word_t)*(int32_t *)(tmpL4 + 0x30));
    (*fnp11)();
    skp0_rt_003512c0();
    (*fnp12)();
    (*fnp10)(lStack_a0,ptl2,savx25);
    tmp6 = (*fnp11)(loc90,lStack_a0 + *(int32_t *)(savx25 + 0x24),ptu3);
    idx1 = *(int32_t *)(tmpL7 + 0x24);
    skp0_rt_00358dd0(tmp6,(word_t)ptl2 + (word_t)idx1);
    tmp6 = (*fnp10)();
    skp0_rt_003579e8(tmp6,loc98 + *(int32_t *)(savx25 + 0x24));
    (*fnp11)();
    skp0_rt_003540dc();
    skp0_rt_00310e20();
    tmp6 = skp0_rt_00350a7c();
    skp0_rt_00351378(tmp6,loc88);
    tmp8 = (*outx8_06)();
    if ((tmp8 & 1) != 0) {
      loc10 = (word_t *)(word_t)idx1;
      skp0_rt_0035463c();
      ptu9 = (word_t *)((word_t)ptu9 & 0xffffffffffff | 0x4f8000000000000);
      pair17 = skp0_rt_00350944();
      (*fnp11)(pair17.lo,pair17.hi,ptu3);
      skp0_rt_00359e28();
      skp0_rt_00351a20();
      (*fnp11)();
      skp0_rt_0034e54c();
      skp0_rt_00354134();
      (*outx8_07)();
      idx1 = *(int32_t *)(tmpL4 + 0x30);
      pair17 = skp0_rt_00350b3c();
      (*fnp11)(pair17.lo,pair17.hi,ptu3);
      (*fnp12)((word_t)loc48 + (word_t)idx1,ptu3);
      skp0_rt_0034e54c();
      skp0_rt_00353148();
      (*outx8_08)();
      tmpL7 = (word_t)*(int32_t *)(loc20 + 0x24);
      (*fnp11)(loc68 + tmpL7,(word_t)loc48 + (word_t)*(int32_t *)(tmpL4 + 0x30),ptu3);
      loc18 = ptu3;
      (*fnp12)(loc48,ptu3);
      ptl15 = *(word_t **)pair16.hi;
      skp0_rt_00355418();
      tmpL4 = *(word_t *)(outx8_09 + outx9_00);
      if ((word_t)ptl15 <= tmpL4) {
        tmpL13 = *ptl2;
        tmpL14 = *(word_t *)((word_t)ptl2 + (word_t)loc10);
        if (tmpL13 <= tmpL14) {
          loc10 = ptu9;
          skp0_rt_00354064();
          skp0_rt_0031b050(outx8_00);
          tmp6 = skp0_rt_00350a7c();
          skp0_rt_00351dcc(tmp6,loc30);
          (*outx8_10)();
          if (tmpL13 < (word_t)ptl15 || tmpL4 <= tmpL13) {
            skp0_rt_0034b348();
            tmp5 = 0x126;
          }
          else if (tmpL4 < tmpL14) {
            skp0_rt_0034b348();
            tmp5 = 0x127;
          }
          else {
            skp0_rt_00351e48(&sk_stack_00000010);
            skp0_rt_001fe9a8(param_3);
            tmpL4 = *ptl15;
            fnp10 = *(sk_fnptr *)(outx16_01 + 8);
            (*fnp10)(ptl15,savx25);
            if (tmpL13 == tmpL4) {
              skp0_rt_00351750(outx8_00);
              skp0_rt_00352ca4(astk8);
              skp0_rt_003509b0();
              (*outx9_01)();
              skp0_rt_0034c4fc(tmp5);
              skp0_rt_0034df34(loc68,loc48);
              (*outx8_11)();
              skp0_rt_0034f4c4();
              skp0_rt_00357998();
              (*outx9_02)();
              if ((savx20 & 1) == 0) {
                skp0_rt_0034b348();
                tmp5 = 0x12a;
              }
              else {
L_00202b98:
                skp0_rt_00359a60();
                skp0_rt_00351f58();
                skp0_rt_001fe9a8();
                tmpL4 = *loc48;
                skp0_rt_00350618();
                (*fnp10)();
                if (tmpL14 == tmpL4) {
                  skp0_rt_00351750(outx8_00);
                  skp0_rt_003526b8(astk8);
                  skp0_rt_003509b0();
                  (*outx9_06)();
                  skp0_rt_0034c4fc(tmp5);
                  skp0_rt_0034df34(loc68 + tmpL7,param_3);
                  tmp8 = (*outx8_14)();
                  skp0_rt_00084180();
                  skp0_rt_00357998();
                  (*outx9_07)();
                  tmpL4 = loc20;
                  if ((tmp8 & 1) != 0) {
                    fnp10 = *(sk_fnptr *)(outx16_02 + 8);
                    (*fnp10)(loc68,loc20);
                    (*fnp10)(loc30,tmpL4);
L_00202d48:
                    skp0_rt_0008e500(savx30);
                    return;
                  }
                  skp0_rt_0034b348();
                  tmp5 = 0x131;
                }
                else {
                  tmp6 = *(word_t *)(savx20 + (word_t)*(int32_t *)(param_3 + 0x24));
                  skp0_rt_0036b270(tmp6);
                  skp0_rt_00351af8(&loc28);
                  skp0_rt_0034c818();
                  skp0_rt_001fea40();
                  tmp6 = skp0_rt_0036b118(tmp6).lo;
                  skp0_rt_00353fa0(*(word_t *)(loc28 + 0x10),tmp6,loc68 + tmpL7);
                  (*outx8_15)();
                  skp0_rt_00310e20(tmp5);
                  skp0_rt_0034f4e4();
                  skp0_rt_00350ac4();
                  tmp8 = (*outx8_16)();
                  tmpL4 = loc20;
                  if ((tmp8 & 1) == 0) {
                    skp0_rt_00084180();
                    skp0_rt_00357998();
                    (*outx9_10)();
                    skp0_rt_00350bc0(&sk_stack_00000000);
                    (*outx8_19)(savx20,loc20);
                  }
                  else {
                    idx1 = *(int32_t *)(loc20 + 0x24);
                    skp0_rt_0035044c(tmp5);
                    skp0_rt_00350ac4(loc120,savx20 + (word_t)idx1);
                    tmp8 = (*outx8_17)();
                    skp0_rt_00084180();
                    skp0_rt_00357998();
                    (*outx9_08)();
                    fnp10 = *(sk_fnptr *)(outx16_02 + 8);
                    skp0_rt_0035084c();
                    (*fnp10)();
                    if ((tmp8 & 1) != 0) {
                      skp0_rt_003504c4();
                      (*fnp10)();
                      (*fnp10)(loc30,tmpL4);
                      goto L_00202d48;
                    }
                  }
                  skp0_rt_0034b348();
                  tmp5 = 0x133;
                }
              }
            }
            else {
              tmp6 = *(word_t *)(savx20 + (word_t)*(int32_t *)(param_3 + 0x24));
              skp0_rt_0036b270(tmp6);
              skp0_rt_003526b8(&loc18);
              skp0_rt_003509bc();
              skp0_rt_00358684();
              skp0_rt_001fea40();
              skp0_rt_0036b118(tmp6);
              skp0_rt_0035a3b8();
              tmp6 = skp0_rt_00355e50();
              (*outx9_03)(tmp6,loc68,ptu9);
              skp0_rt_00310e20(tmp5);
              skp0_rt_00350804();
              skp0_rt_0034f3f4();
              tmp8 = (*outx8_12)();
              if ((tmp8 & 1) == 0) {
                skp0_rt_0035060c();
                skp0_rt_00357998();
                (*outx9_09)();
                skp0_rt_00350bc0(&sk_stack_00000000);
                (*outx8_18)(param_3,loc20);
              }
              else {
                idx1 = *(int32_t *)(loc20 + 0x24);
                skp0_rt_0035044c(tmp5);
                skp0_rt_00350ac4(loc48,param_3 + idx1);
                (*outx8_13)();
                skp0_rt_0034f4c4();
                skp0_rt_00357998();
                (*outx9_04)();
                skp0_rt_00352bbc();
                skp0_rt_0034d2d4();
                (*outx9_05)();
                if (((word_t)idx1 & 1U) != 0) goto L_00202b98;
              }
              skp0_rt_0034b348();
              tmp5 = 300;
            }
          }
          skp0_rt_003486b8(tmp5);
          skp0_rt_0034975c();
          goto L_00202a10;
        }
      }
    }
  }
  skp0_rt_00347d60();
L_00202a10:
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_00202df4 @ 0x00202df4   (est. skp0_sk_node_alloc)
 * Ghidra: word_t * FUN_00202df4(word_t *param_1,word_t param_2,word_t param_3)
 * Allocates a 0x28-byte node (skp0_rt_0036a908 tag 0xd183), initializes it via skp0_sk_node_init (00202e68), stores the result at +0x20, returns the metadata descriptor &skp0_g_003471a4. Constructor pattern.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t * skp0_sk_node_alloc(word_t *param_1,word_t param_2,word_t param_3)
{

  word_t tmpL1;
  word_t tmp2;
  
  tmpL1 = skp0_rt_0036a908(0x28,0xd183);
  *param_1 = tmpL1;
  tmp2 = skp0_sk_node_init((word_t *)(tmpL1),(word_t)(param_2),(word_t)(param_3)).lo;
  *(word_t *)(tmpL1 + 0x20) = tmp2;
  return (word_t *)&skp0_g_003471a4;
}

/* FUN_00202e68 @ 0x00202e68   (est. skp0_sk_node_init)
 * Ghidra: sk_u128_t FUN_00202e68(word_t *param_1,word_t param_2,word_t param_3)
 * Node constructor: resolves object, builds an object via skp0_rt_00377824, allocates a child table (skp0_rt_0036a908 tag 0x9b0d) and calls skp0_rt_001fff64 to initialize it. Returns sk_u128_t descriptor (lo=&skp0_g_003471a8).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t skp0_sk_node_init(word_t *param_1,word_t param_2,word_t param_3)
{

  word_t tmp1;
  word_t tmpL2;
  sk_u128_t pair3;
  
  tmp1 = skp0_rt_00027754(*(word_t *)(param_3 + 0x18));
  tmpL2 = skp0_rt_00377824(0,tmp1,*(word_t *)(param_3 + 0x10),&skp0_g_00611b24,&skp0_g_00611b34).lo;
  *param_1 = tmpL2;
  tmpL2 = *(word_t *)(tmpL2 + -8);
  param_1[1] = tmpL2;
  tmpL2 = skp0_rt_0036a908(*(word_t *)(tmpL2 + 0x40),0x9b0d);
  param_1[2] = tmpL2;
  skp0_rt_001fff64(tmpL2,param_2,param_3);
  pair3.hi = tmpL2;
  pair3.lo = (word_t)&skp0_g_003471a8;
  return pair3;
}

/* FUN_00202f84 @ 0x00202f84   (est. skp0_sk_unmap_region)
 * Ghidra: void FUN_00202f84(word_t param_1,word_t param_2,word_t param_3)
 * Unmap region: resolves ranges, runs a first-entry check (skp0_rt_001b9040); on failure panics; on success walks and releases entries, calling sk_cleanup_thunk and finishing with runtime release.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_unmap_region(word_t param_1,word_t param_2,word_t param_3)
{

  int idx1;
  word_t *ptl2;
  word_t tmp3;
  word_t tmp4;
  word_t tmpL5;
  word_t tmp6;
  sk_fnptr fnp7;
  word_t tmpL8;
  word_t outx8;
  word_t outx8_00;
  word_t outx8_01;
  sk_fnptr outx8_02;
  sk_fnptr fnp9;
  sk_fnptr outx8_03;
  sk_fnptr outx8_04;
  sk_fnptr outx8_05;
  sk_fnptr outx8_06;
  sk_fnptr outx8_07;
  word_t outx8_08;
  sk_fnptr outx8_09;
  sk_fnptr outx9;
  sk_fnptr outx9_00;
  sk_fnptr outx9_01;
  sk_fnptr outx9_02;
  sk_fnptr outx9_03;
  word_t outx16;
  word_t outx16_00;
  word_t outx16_01;
  word_t outx16_02;
  word_t *ptu10;
  word_t savx20;
  word_t tmp11;
  word_t savx22;
  word_t savx24;
  word_t tmpL12;
  word_t tmp13;
  sk_fnptr fnp14;
  word_t savx30;
  sk_u128_t pair15;
  word_t loc60;
  word_t loc40;
  
  pair15 = skp0_rt_0008e518();
  tmpL8 = pair15.hi;
  ptl2 = (word_t *)pair15.lo;
  skp0_rt_00351ef8(param_3);
  tmp11 = *(word_t *)(tmpL8 + 0x10);
  skp0_rt_0034e034(0);
  skp0_rt_00377824();
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034cd54();
  skp0_rt_00352968();
  skp0_rt_0034e034();
  tmp3 = skp0_rt_00377824().lo;
  skp0_rt_0034e024();
  tmp4 = skp0_rt_00377bec();
  pair15 = skp0_rt_00350720();
  tmpL5 = skp0_rt_00310e08(pair15.lo,pair15.hi,tmp4);
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034a760();
  skp0_rt_00349c70();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_00350428();
  skp0_rt_00349080();
  (*skp0_g_00658c00)(*(word_t *)(outx8_01 + 0x40));
  skp0_rt_00349178();
  skp0_rt_003502e8();
  skp0_rt_0031b704();
  skp0_rt_00348d4c();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034b2f8();
  skp0_rt_001fe7cc(tmpL8);
  skp0_rt_003513b4(ptl2);
  tmp6 = skp0_rt_001b9040();
  skp0_rt_00350470(*(word_t *)(outx16_02 + 8));
  (*outx8_02)();
  if ((tmp6 & 1) == 0) {
    skp0_rt_00350410();
    skp0_rt_003488bc();
    skp0_rt_0006f768();
                    /* WARNING: Subroutine does not return */
    skp0_rt_001afe4c();
  }
  tmpL12 = (word_t)*(int32_t *)(savx24 + 0x24);
  skp0_rt_0026c274(tmpL8);
  skp0_rt_00351750();
  skp0_rt_00355bd0();
  (*outx9)(tmp11);
  ptu10 = (word_t *)(outx16_01 + 8);
  fnp9 = (sk_fnptr)*ptu10;
  skp0_rt_00100efc();
  (*outx8_03)();
  skp0_rt_00350780(tmp4);
  fnp7 = (sk_fnptr)skp0_rt_0014ae44();
  skp0_rt_00351c94((word_t)ptl2 + tmpL12);
  tmp6 = (*fnp7)();
  fnp14 = *(sk_fnptr *)(outx16_00 + 8);
  skp0_rt_003507c8();
  (*fnp14)();
  if ((tmp6 & 1) == 0) {
    tmp13 = *(word_t *)(savx20 + *(int32_t *)(tmpL8 + 0x24));
    skp0_rt_0036b270(tmp13);
    skp0_rt_00350b18(loc40);
    skp0_rt_001fea40();
    skp0_rt_0036b118(tmp13);
    pair15 = skp0_rt_00350b00(*(word_t *)(outx16_00 + 0x10));
    (*outx8_04)(pair15.lo,pair15.hi,tmp3);
    skp0_rt_0035a6b4(*(word_t *)(outx16 + 8));
    (*outx8_05)();
    skp0_rt_00351c94((word_t)ptl2 + tmpL12,outx8_00);
    (*fnp7)();
    tmp4 = skp0_rt_00355884();
    (*fnp14)(tmp4,tmp3);
    if (((word_t)ptu10 & 1) == 0) {
      skp0_rt_0036b270(tmp13);
      skp0_rt_00100c38(loc40);
      skp0_rt_003569e4();
      skp0_rt_001fea40();
      skp0_rt_0036b118(tmp13);
      skp0_rt_0026c274(savx22,tmpL8);
      skp0_rt_00352abc();
      skp0_rt_00350998(loc60,loc40);
      (*outx9_02)();
      skp0_rt_0009e234();
      (*fnp9)();
      (*outx8_05)(loc40,tmpL5);
      skp0_rt_0035238c();
      skp0_rt_0035a19c(param_3,tmp11);
      skp0_rt_00377bec();
      skp0_rt_0031e104();
      skp0_rt_003548e8();
      skp0_rt_00350768(outx8_00,outx8_08 + tmpL12);
      (*outx9_03)();
      skp0_rt_0035336c();
      skp0_rt_00350518();
      fnp7 = outx8_09;
      goto L_0020348c;
    }
  }
  if (skp0_SBORROW8(*ptl2,1)) {
                    /* WARNING: Does not return */
    fnp7 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x2034f8);
    (*fnp7)();
  }
  skp0_rt_0035aa90((word_t)*(int32_t *)(tmpL8 + 0x24));
  skp0_rt_00350524(loc40);
  skp0_rt_003569e4();
  skp0_rt_001fea40();
  skp0_rt_0036b118(ptu10);
  skp0_rt_0026c274(savx22,tmpL8);
  skp0_rt_00352abc();
  skp0_rt_003530b0(loc60);
  skp0_rt_00350998();
  (*outx9_00)();
  skp0_rt_003509e0();
  (*fnp9)();
  idx1 = *(int32_t *)(tmpL5 + 0x24);
  skp0_rt_0035238c();
  skp0_rt_0035a19c(param_3,tmp11);
  skp0_rt_00377bec();
  skp0_rt_00354930();
  skp0_rt_00350768(outx8_00,loc40 + idx1);
  (*outx9_01)();
  skp0_rt_0035336c();
  skp0_rt_00350518();
  (*outx8_06)();
  skp0_rt_00353154();
  skp0_rt_00350914();
  fnp7 = outx8_07;
L_0020348c:
  (*fnp7)();
  skp0_rt_0035084c(outx8);
  skp0_rt_00352450();
  skp0_rt_001fd4f4();
  skp0_rt_0008e500(savx30);
  return;
}

/* FUN_0020353c @ 0x0020353c   (est. skp0_sk_node_config)
 * Ghidra: void FUN_0020353c(word_t param_1,word_t param_2,word_t param_3)
 * Node configuration: builds an object frame, resolves a slot, retains/releases, and invokes a table update via runtime dispatch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_node_config(word_t param_1,word_t param_2,word_t param_3)
{

  int idx1;
  word_t tmp2;
  word_t tmp3;
  word_t tmpL4;
  sk_fnptr fnp5;
  word_t outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx8_01;
  sk_fnptr outx8_02;
  sk_fnptr outx9;
  word_t outx16;
  word_t outx16_00;
  word_t savx20;
  word_t tmp6;
  word_t savx30;
  sk_u128_t pair7;
  sk_u128_t pair8;
  word_t loc48;
  
  pair7 = skp0_rt_0008e518();
  skp0_rt_00351bec(param_3);
  tmp6 = *(word_t *)(pair7.hi + 0x10);
  skp0_rt_003525cc();
  skp0_rt_0034df64();
  skp0_rt_00377824();
  tmp2 = skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034b708();
  skp0_rt_00352f54();
  skp0_rt_0034df64();
  skp0_rt_00377824();
  skp0_rt_0034db68();
  tmp3 = skp0_rt_00377bec();
  pair8 = skp0_rt_003504e8();
  skp0_rt_00310e08(pair8.lo,pair8.hi,tmp3);
  skp0_rt_00348ce8();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034af20();
  tmp3 = *(word_t *)(savx20 + *(int32_t *)(pair7.hi + 0x24));
  skp0_rt_0036b270(tmp3);
  skp0_rt_00350624(*(word_t *)pair7.lo);
  skp0_rt_001fea40();
  skp0_rt_0036b118(tmp3);
  skp0_rt_00352eb4();
  skp0_rt_00352e3c();
  skp0_rt_0035136c();
  (*outx9)();
  skp0_rt_00350b00(*(word_t *)(outx16 + 8));
  (*outx8_00)();
  skp0_rt_00350318();
  tmpL4 = skp0_rt_0031b704();
  idx1 = *(int32_t *)(tmpL4 + 0x24);
  skp0_rt_0034de8c();
  pair8 = skp0_rt_00351274();
  fnp5 = (sk_fnptr)skp0_rt_00377bec(pair8.lo,pair8.hi,tmp2);
  skp0_rt_00352ecc();
  tmp2 = skp0_rt_0035949c();
  skp0_rt_003515fc(tmp2,(word_t)pair7.lo + (word_t)idx1);
  (*outx8_01)();
  skp0_rt_00351a50();
  pair7 = skp0_rt_00348b94();
  skp0_rt_00377824(pair7.lo,pair7.hi,tmp6);
  skp0_rt_00349530();
  (**(sk_fnptr *)(outx16_00 + 0x10))(outx8,loc48);
  skp0_rt_00351d00();
  (*fnp5)();
  skp0_rt_0035313c();
  skp0_rt_0035084c();
  (*outx8_02)();
  skp0_rt_0008e500(savx30);
  return;
}

/* FUN_0020373c @ 0x0020373c   (est. skp0_sk_node_release)
 * Ghidra: void FUN_0020373c(void)
 * Node release helper: runtime prologue, resolves object slots, calls the table-update dispatch, ends with a cleanup.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_node_release(void)
{

  int idx1;
  word_t tmpL2;
  word_t tmp3;
  sk_fnptr fnp4;
  word_t tmp5;
  word_t inpx3;
  sk_fnptr outx8;
  word_t outx16;
  sk_fnptr savx19;
  word_t savx30;
  sk_u128_t pair6;
  uint8_t astk20 [32];
  
  skp0_rt_0008e518();
  pair6 = skp0_rt_00358a74();
  skp0_rt_00351ad4(inpx3);
  skp0_rt_0034d2a4();
  skp0_rt_00350bfc(0xff);
  skp0_rt_00377824();
  skp0_rt_0034ee08();
  skp0_rt_00377bec();
  skp0_rt_003502f8();
  skp0_rt_00310e08();
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034af20();
  skp0_rt_0035aa90((word_t)*(int32_t *)(savx19 + 0x24));
  skp0_rt_00350878(*(word_t *)pair6.hi);
  skp0_rt_001fea40();
  skp0_rt_0036b118();
  skp0_rt_0034ef88();
  tmpL2 = skp0_rt_0031b704();
  idx1 = *(int32_t *)(tmpL2 + 0x24);
  tmp3 = skp0_rt_0031b870();
  skp0_rt_003516f0(tmp3,astk20);
  (*outx8)();
  skp0_rt_00351a50();
  skp0_rt_003513d8(0xff);
  skp0_rt_00377824();
  skp0_rt_0034c6b4();
  tmp3 = skp0_rt_00377bec();
  fnp4 = (sk_fnptr)skp0_rt_00310ed4();
  skp0_rt_00350530();
  tmp5 = skp0_rt_00377dcc();
  (*fnp4)(pair6.lo,(word_t)pair6.hi + (word_t)idx1,tmp5,tmp3);
  skp0_rt_0034cfa4();
  (*savx19)();
  (**(sk_fnptr *)(outx16 + 8))();
  skp0_rt_0008e500(savx30);
  return;
}

/* FUN_002038d4 @ 0x002038d4   (est. skp0_sk_node_alloc4)
 * Ghidra: void FUN_002038d4(void)
 * Node allocation (4-slot): allocates four tables (skp0_rt_0036a908 tag 0x4d96), stores into +0x18/0x20/0x28/0x30/0x38, then calls skp0_sk_node_config (0020353c). Returns via skp0_rt_0008e500 with a data label.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_node_alloc4(void)
{

  word_t tmp1;
  word_t outx8;
  word_t outx8_00;
  sk_fnptr outx8_01;
  word_t outx16;
  word_t outx16_00;
  word_t savx22;
  word_t savx24;
  word_t tmp2;
  word_t savx30;
  sk_u128_t pair3;
  
  skp0_rt_0008e518();
  skp0_rt_0034c2e8();
  tmp1 = skp0_rt_00358c2c();
  skp0_rt_0036a908(tmp1,0x4d96);
  skp0_rt_003528b8();
  skp0_rt_00351bec();
  skp0_rt_00350bd8();
  tmp1 = *(word_t *)(savx22 + 0x10);
  pair3 = skp0_rt_003497a0();
  tmp1 = skp0_rt_00377824(pair3.lo,pair3.hi,tmp1).lo;
  *(word_t *)(savx24 + 0x18) = tmp1;
  skp0_rt_00352018();
  *(word_t *)(savx24 + 0x20) = outx16;
  tmp2 = *(word_t *)(outx8 + 0x40);
  tmp1 = skp0_rt_0036a908(tmp2,0x4d96);
  *(word_t *)(savx24 + 0x28) = tmp1;
  tmp1 = skp0_rt_0036a908(tmp2,0x4d96);
  *(word_t *)(savx24 + 0x30) = tmp1;
  skp0_rt_003508e4();
  skp0_rt_0031b704();
  skp0_rt_00348d7c();
  tmp2 = skp0_rt_0036a908(*(word_t *)(outx8_00 + 0x40),0x4d96);
  *(word_t *)(savx24 + 0x38) = tmp2;
  skp0_rt_0035136c(*(word_t *)(outx16_00 + 0x10));
  (*outx8_01)();
  skp0_rt_0034b508(tmp1);
  skp0_sk_node_config((word_t)(0),(word_t)(0),(word_t)(0));
  skp0_rt_0008e500(&skp0_g_002039f4,tmp1,savx30);
  return;
}

/* FUN_00203a0c @ 0x00203a0c   (est. skp0_sk_sub_release)
 * Ghidra: void FUN_00203a0c(void)
 * Sub-node release: runtime calls to release a child table and drop a reference.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_sub_release(void)
{

  word_t outx8;
  sk_fnptr outx8_00;
  word_t outx12;
  
  skp0_rt_00349ef4();
  skp0_rt_00349b3c();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_00348f38();
  skp0_rt_00350e74(*(word_t *)(outx12 + 0x10));
  (*outx8_00)();
  skp0_rt_0035242c();
  skp0_rt_0034b358();
  skp0_rt_001fccf8();
  skp0_rt_0036b270();
  return;
}

/* FUN_00203aa4 @ 0x00203aa4   (est. skp0_sk_sub_alloc)
 * Ghidra: void FUN_00203aa4(void)
 * Sub-node alloc wrapper: builds via skp0_rt_00377824, calls skp0_sk_sub_init (00203b08) then skp0_sk_sub_release (00203a0c), releases the node.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_sub_alloc(void)
{

  word_t tmp1;
  sk_u128_t pair2;
  
  skp0_rt_00349ef4();
  skp0_rt_00349748();
  skp0_rt_00354394();
  pair2 = skp0_rt_00377824();
  skp0_rt_00350af4(pair2.lo,pair2.hi,pair2.lo);
  skp0_rt_00352920();
  tmp1 = skp0_sk_sub_init((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
  skp0_rt_003504a0();
  skp0_sk_sub_release();
  skp0_rt_0036b118(tmp1);
  return;
}

/* FUN_00203b08 @ 0x00203b08   (est. skp0_sk_sub_init)
 * Ghidra: word_t FUN_00203b08(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
 * Sub-node initializer: runtime prologue, resolves object, runs a branch check; on success installs a child and returns, else panics (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_sub_init(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
{

  int idx1;
  word_t tmp2;
  word_t tmpL3;
  word_t tmp4;
  word_t tmp5;
  word_t outx8;
  word_t outx8_00;
  sk_fnptr outx8_01;
  sk_fnptr outx8_02;
  sk_fnptr outx8_03;
  sk_fnptr outx9;
  sk_fnptr outx9_00;
  sk_fnptr outx9_01;
  word_t outx16;
  word_t outx16_00;
  word_t savx21;
  word_t savx22;
  word_t savx24;
  word_t savx26;
  sk_fnptr fnp6;
  sk_fnptr fnp7;
  sk_u128_t pair8;
  word_t inpstack_00000018;
  
  skp0_rt_0008e518();
  skp0_rt_0034b0b4();
  skp0_rt_00359000();
  skp0_rt_00348ce8();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_00349db0();
  (*skp0_g_00658c00)();
  skp0_rt_0034b87c();
  skp0_rt_003494e8();
  (*skp0_g_00658c00)(*(word_t *)(outx8_00 + 0x40));
  skp0_rt_00348a80();
  (*skp0_g_00658c00)();
  skp0_rt_0034b4c0();
  skp0_rt_0034c3c4();
  skp0_rt_00350768(param_5);
  tmp2 = skp0_rt_00377bec();
  pair8 = skp0_rt_003504e8();
  skp0_rt_00310e08(pair8.lo,pair8.hi,tmp2);
  tmpL3 = skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034b6f4();
  skp0_rt_000277b8(param_5);
  tmp4 = skp0_rt_0034d434();
  (*outx9)(tmp4,param_5);
  skp0_rt_00310924(param_5);
  tmp4 = skp0_rt_0034f634();
  (*outx9_00)(tmp4,param_5);
  skp0_rt_00310e20(tmp2);
  skp0_rt_0034db98();
  skp0_rt_00350ac4();
  tmp5 = (*outx8_01)();
  if ((tmp5 & 1) != 0) {
    fnp6 = *(sk_fnptr *)(outx16_00 + 0x20);
    pair8 = skp0_rt_00350ea4();
    (*fnp6)(pair8.lo,pair8.hi,param_3);
    skp0_rt_003508d8(savx26 + *(int32_t *)(savx22 + 0x30));
    (*fnp6)();
    skp0_rt_00352a40();
    skp0_rt_0034ef78();
    (*outx9_01)();
    idx1 = *(int32_t *)(savx22 + 0x30);
    skp0_rt_003578a8();
    skp0_rt_003504a0();
    (*fnp6)();
    fnp7 = *(sk_fnptr *)(outx16_00 + 8);
    (*fnp7)(savx21 + idx1,param_3);
    skp0_rt_0034ef78(*(word_t *)(outx16 + 0x20));
    (*outx8_02)();
    (*fnp6)(savx24 + *(int32_t *)(tmpL3 + 0x24),savx21 + *(int32_t *)(savx22 + 0x30),param_3);
    skp0_rt_00084180();
    (*fnp7)();
    pair8 = skp0_rt_0035620c();
    skp0_rt_00279568(pair8.lo,pair8.hi,param_3,tmp2);
    skp0_rt_003529a4();
    skp0_rt_00351384();
    (*outx8_03)();
    tmp2 = skp0_rt_00353100();
    skp0_rt_0008e500(tmp2,inpstack_00000018);
    return 0;
  }
  skp0_rt_00347d60();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_00203e0c @ 0x00203e0c   (est. skp0_sk_iterate_children)
 * Ghidra: void FUN_00203e0c(void)
 * Child iterator: loops over children via a vtable method (offset into +0x28), collects up to one (sets flag byte 1), emits the frame and returns. State-machine loop.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_iterate_children(void)
{

  char cVar1;
  uint8_t tmp2;
  word_t tmp3;
  word_t tmp4;
  sk_fnptr fnp5;
  word_t tmp6;
  word_t tmp7;
  word_t tmp8;
  word_t outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx8_01;
  word_t outx16;
  char *savx20;
  sk_fnptr fnp9;
  sk_u128_t pair10;
  sk_u128_t pair11;
  
  pair10 = skp0_rt_0008e518();
  skp0_rt_00352590();
  skp0_rt_00350878();
  skp0_rt_00377824();
  skp0_rt_0034ee68();
  skp0_rt_00310d68();
  tmp3 = skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034aee4();
  skp0_rt_003499f0();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034b0d4();
  cVar1 = *savx20;
  skp0_rt_00359530();
  skp0_rt_00350878();
  pair11 = skp0_rt_00377824();
  tmp8 = pair11.lo;
  skp0_rt_003507e0(tmp8,pair11.hi,tmp8);
  tmp4 = skp0_rt_00377bec();
  fnp5 = (sk_fnptr)skp0_rt_000a68f4();
  tmp2 = cVar1 == '\x01';
  if ((bool)tmp2) {
    skp0_rt_00350530();
    tmp3 = skp0_rt_00377dcc();
    (*fnp5)(outx8,tmp3,tmp4);
  }
  else {
    while( true ) {
      tmp6 = skp0_rt_00377dcc(0,tmp8);
      (*fnp5)(tmp6,tmp4);
      tmp6 = skp0_rt_0034b2c8();
      if ((bool)tmp2) break;
      fnp9 = *(sk_fnptr *)(outx16 + 0x20);
      skp0_rt_0034ee98();
      (*fnp9)();
      tmp7 = (**(sk_fnptr *)(savx20 + *(int32_t *)(pair10.lo + 0x28)))();
      if ((tmp7 & 1) == 0) {
        *savx20 = '\x01';
        skp0_rt_0035100c();
        (*fnp9)();
        pair11 = skp0_rt_0035354c();
        goto L_00204004;
      }
      skp0_rt_003508b4(*(word_t *)(outx16 + 8));
      (*outx8_00)();
    }
    skp0_rt_0035152c(tmp6,tmp3);
    (*outx8_01)();
    pair11.hi = 1;
    pair11.lo = outx8;
L_00204004:
    skp0_rt_00352480(pair11.lo,pair11.hi);
    skp0_rt_000839d8();
  }
  skp0_rt_0008e500(pair10.hi);
  return;
}

/* FUN_0020405c @ 0x0020405c   (est. skp0_sk_iterate_walk)
 * Ghidra: void FUN_0020405c(void)
 * Iteration walker: while-loop over entries via skp0_rt_0035a1b4/skp0_rt_00351324, dispatching a vtable slot; breaks on runtime branch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_iterate_walk(void)
{

  sk_fnptr fnp1;
  sk_fnptr fnp2;
  word_t tmp3;
  word_t tmp4;
  sk_fnptr fnp5;
  word_t outx1;
  word_t outx8;
  sk_fnptr outx8_00;
  word_t outx8_01;
  sk_fnptr outx8_02;
  sk_fnptr outx8_03;
  sk_fnptr outx8_04;
  sk_fnptr outx8_05;
  sk_fnptr outx9;
  word_t savx20;
  word_t tmp6;
  word_t savx30;
  sk_u128_t pair7;
  word_t loc40;
  
  skp0_rt_0008e518();
  skp0_rt_003518c4();
  skp0_rt_00350bd8(outx1);
  tmp6 = *(word_t *)(savx20 + 0x10);
  pair7 = skp0_rt_003497a0();
  tmp6 = skp0_rt_00377824(pair7.lo,pair7.hi,tmp6).lo;
  skp0_rt_000a6f88();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034cd54();
  skp0_rt_0034cae8();
  skp0_rt_003510f4();
  skp0_rt_00377824();
  skp0_rt_00348cd0();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034af20();
  skp0_rt_003506e8();
  skp0_rt_003507bc(outx8);
  (*outx9)();
  fnp2 = (sk_fnptr)skp0_rt_00310924();
  skp0_rt_0035705c();
  skp0_rt_00351ba0();
  skp0_rt_00377bec();
  skp0_rt_00027754();
  skp0_rt_0014ae44();
  skp0_rt_003561b8();
  while( true ) {
    skp0_rt_003504f4();
    (*fnp2)();
    skp0_rt_00351324();
    skp0_rt_00351b20();
    tmp3 = ((sk_fnptr)loc40)();
    skp0_rt_003567ec();
    skp0_rt_00350b00();
    (*outx8_00)();
    if ((tmp3 & 1) != 0) break;
    skp0_rt_0035a1b4();
    fnp1 = *(sk_fnptr *)(savx20 + outx8_01);
    tmp4 = skp0_rt_00351b84();
    skp0_rt_00352450(tmp4,outx8);
    fnp5 = (sk_fnptr)(*outx8_02)();
    pair7 = skp0_rt_00352b14();
    (*outx8_03)(pair7.lo,pair7.hi,tmp6);
    skp0_rt_0034cfa4();
    (*fnp5)();
    tmp3 = (*fnp1)();
    skp0_rt_00354ab0();
    skp0_rt_00350a34();
    (*outx8_04)();
    if ((tmp3 & 1) == 0) break;
    skp0_rt_00027818();
    skp0_rt_00350a88();
    skp0_rt_00350998();
    (*outx8_05)();
  }
  skp0_rt_0008e500(savx30);
  return;
}

/* FUN_00204280 @ 0x00204280   (est. skp0_sk_find_child)
 * Ghidra: void FUN_00204280(word_t param_1,word_t param_2,word_t param_3)
 * Find child: resolves object, checks a branch; on success finds via skp0_rt_00319658 and returns, else panics (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_find_child(word_t param_1,word_t param_2,word_t param_3)
{

  word_t tmp1;
  word_t tmp2;
  sk_fnptr outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx9;
  sk_fnptr outx9_00;
  word_t outx16;
  word_t savx30;
  
  skp0_rt_0008e518();
  skp0_rt_0035a2c4();
  tmp1 = skp0_rt_0034c354();
  skp0_rt_00353960(tmp1,param_3);
  skp0_rt_00377824();
  skp0_rt_00348d7c();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034af20();
  skp0_rt_00310924();
  skp0_rt_0034d434();
  (*outx9)();
  skp0_rt_00084174();
  skp0_rt_00351cd0();
  skp0_rt_00377bec();
  skp0_rt_0035044c();
  skp0_rt_00350bf0();
  skp0_rt_00351c94();
  tmp2 = (*outx8)();
  skp0_rt_00350b3c(*(word_t *)(outx16 + 8));
  (*outx8_00)();
  if ((tmp2 & 1) != 0) {
    skp0_rt_00319658();
    skp0_rt_00350c50();
    skp0_rt_00350768();
    (*outx9_00)();
    skp0_rt_0008e500(savx30);
    return;
  }
  skp0_rt_00350410();
  skp0_rt_003488bc();
  skp0_rt_0034c220();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_002043c4 @ 0x002043c4   (est. skp0_sk_node_alloc2)
 * Ghidra: word_t * FUN_002043c4(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Node allocator variant (0x28 bytes, tag 0x1edb): initializes via skp0_sk_node_init2 (00204444) and returns metadata descriptor &skp0_g_003471a4.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t * skp0_sk_node_alloc2(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t tmpL1;
  word_t tmp2;
  
  tmpL1 = skp0_rt_0036a908(0x28,0x1edb);
  *param_1 = tmpL1;
  tmp2 = skp0_sk_node_init2((word_t *)(tmpL1),(word_t)(param_2),(word_t)(param_3),(word_t)(*(word_t *)((param_4 & 0xfffffffffffffffe) - 8))).lo;
  *(word_t *)(tmpL1 + 0x20) = tmp2;
  return (word_t *)&skp0_g_003471a4;
}

/* FUN_00204444 @ 0x00204444   (est. skp0_sk_node_init2)
 * Ghidra: sk_u128_t FUN_00204444(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Node constructor variant: builds object, allocates a child table (tag 0xaee8), calls rt thunk 00250904. Returns sk_u128_t (lo=&skp0_g_003471a8).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t skp0_sk_node_init2(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t tmp1;
  word_t tmpL2;
  sk_u128_t pair3;
  
  tmp1 = skp0_rt_00027754(param_4);
  tmpL2 = skp0_rt_00377824(0,tmp1,*(word_t *)(param_3 + 0x10),&skp0_g_00611b24,&skp0_g_00611b34).lo;
  *param_1 = tmpL2;
  tmpL2 = *(word_t *)(tmpL2 + -8);
  param_1[1] = tmpL2;
  tmpL2 = skp0_rt_0036a908(*(word_t *)(tmpL2 + 0x40),0xaee8);
  param_1[2] = tmpL2;
  skp0_rt_00250904(tmpL2,param_2,param_3,param_4);
  pair3.hi = tmpL2;
  pair3.lo = (word_t)&skp0_g_003471a8;
  return pair3;
}

/* FUN_00204540 @ 0x00204540   (est. skp0_sk_find_slot)
 * Ghidra: void FUN_00204540(word_t param_1,word_t param_2,word_t param_3)
 * Find slot: runtime prologue, resolves object, walks with skp0_sk_iterate_walk (0020405c), checks branch; success returns, failure panics.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_find_slot(word_t param_1,word_t param_2,word_t param_3)
{

  word_t tmp1;
  word_t tmp2;
  word_t outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx8_01;
  sk_fnptr outx9;
  word_t outx16;
  word_t savx30;
  
  skp0_rt_0008e518();
  tmp1 = skp0_rt_00350a28();
  skp0_rt_00351bec(param_3);
  skp0_rt_0034c354();
  skp0_rt_00351300();
  skp0_rt_00377824();
  skp0_rt_00348cd0();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034b2f8();
  skp0_rt_003524a4();
  skp0_sk_iterate_walk();
  skp0_rt_00350618();
  skp0_rt_00351f40();
  skp0_rt_00377bec();
  skp0_rt_00310b08();
  skp0_rt_0034c5cc();
  skp0_rt_00351e78();
  tmp2 = (*outx8_00)();
  skp0_rt_003518b8(*(word_t *)(outx16 + 8));
  (*outx8_01)();
  if ((tmp2 & 1) != 0) {
    skp0_rt_00354930();
    skp0_rt_003508d8(outx8,tmp1);
    (*outx9)();
    skp0_rt_0008e500(savx30);
    return;
  }
  skp0_rt_00350410();
  skp0_rt_003488bc();
  skp0_rt_0006f768();
                    /* WARNING: Subroutine does not return */
  skp0_rt_00356578();
}

/* FUN_002046a8 @ 0x002046a8   (est. skp0_sk_rec_descend)
 * Ghidra: void FUN_002046a8()
 * Recursive descend: runtime prologue, saves stack args, calls skp0_sk_desc_node (00204798), then the runtime epilogue. Ends with release.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_rec_descend()
{

  word_t inpx6;
  word_t inpx7;
  word_t outx8;
  word_t outx8_00;
  sk_fnptr outx8_01;
  sk_fnptr outx8_02;
  word_t outx9;
  word_t outx16;
  sk_fnptr fnp1;
  word_t inpstack_00000038;
  word_t inpstack_00000040;
  word_t inpstack_00000048;
  word_t inpstack_000000b8;
  
  skp0_rt_000b4594();
  skp0_rt_00359b24();
  skp0_rt_0035694c();
  inpstack_00000048 = inpx6;
  skp0_rt_0035869c();
  inpstack_00000040 = outx8_00;
  skp0_rt_0031b8d0(inpstack_000000b8);
  skp0_rt_000777d4();
  (*outx8_01)();
  inpstack_00000038 = inpx7;
  skp0_rt_00319a4c(&sk_stack_00000020);
  skp0_rt_0034b804();
  fnp1 = *(sk_fnptr *)(outx16 + 0x10);
  (*fnp1)();
  skp0_rt_00351dcc(&sk_stack_00000020);
  skp0_sk_desc_node((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
  skp0_rt_003a25d4(inpstack_00000040);
  skp0_rt_000026e8(&sk_stack_00000020);
  skp0_rt_000bd3a4(outx8);
  (*fnp1)();
  skp0_rt_0034310c(inpstack_000000b8);
  skp0_rt_000777d4();
  (*outx8_02)();
  skp0_rt_000b45b0(outx9);
  return;
}

/* FUN_00204798 @ 0x00204798   (est. skp0_sk_desc_node)
 * Ghidra: void FUN_00204798(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5,
                 word_t param_6,word_t *param_7,word_t *param_8,word_t param_9,word_t param_10)
 * Object-description walker (core): iterates object children via vtable methods (+0x128), emits "N children"/"1 child" strings, recursively walks sub-nodes via skp0_sk_desc_children (00205bd0) and skp0_sk_desc_sub (00205844). Traps (skp0_SoftwareBreakpoint) on depth/carry overflow; panic path noreturn.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_desc_node(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5,
                 word_t param_6,word_t *param_7,word_t *param_8,word_t param_9,word_t param_10)
{

  uint8_t tmp1;
  int idx2;
  word_t tmpL3;
  word_t *ptu4;
  sk_fnptr fnp5;
  word_t tmp6;
  word_t tmpL7;
  char *fnp8;
  word_t outx1;
  word_t outx1_00;
  word_t outx1_01;
  word_t outx1_02;
  word_t outx1_03;
  word_t outx1_04;
  word_t outx1_05;
  word_t outx1_06;
  word_t outx1_07;
  word_t outx1_08;
  sk_fnptr outx8;
  word_t *savx19;
  word_t tmp9;
  word_t *ptl10;
  word_t tmpL11;
  sk_u128_t pair12;
  sk_u128_t loc158;
  uint8_t astk148 [32];
  uint8_t astk128 [32];
  uint8_t astk108[8];
  word_t *loc100;
  sk_fnptr locf0;
  word_t loce8;
  word_t locd8;
  word_t locd0;
  word_t stkc8;
  word_t locc0;
  word_t stkb8;
  uint8_t locb0;
  word_t loca8;
  word_t loca0;
  word_t stk98;
  word_t loc90;
  word_t stk88;
  uint8_t loc80;
  word_t loc78;
  word_t *loc70 [2];
  
  tmpL3 = *param_7 + -1;
  tmp1 = tmpL3 == 0;
  if (*param_7 < 1) {
    return;
  }
  *param_7 = tmpL3;
  if (-1 < param_5) {
    tmpL3 = param_5;
    if (param_5 != 0) {
      do {
        if (tmpL3 == 0) goto L_00204e68;
        skp0_rt_00350744(&skp0_g_005d021c);
        skp0_rt_001a89a8();
        skp0_rt_00354da0(param_10);
        skp0_rt_00350af4();
        skp0_rt_0035359c();
        (*outx8)();
        skp0_rt_003a25d4(outx1);
        tmp1 = tmpL3 + -1 == 0;
        savx19 = param_8;
        tmpL3 = tmpL3 + -1;
      } while (!(bool)tmp1);
    }
    skp0_rt_00319808(param_1,loc158);
    skp0_rt_001edb28(astk108,loc158);
    loc70[0] = loc100;
    tmpL3 = (**(sk_fnptr *)(*loc100 + 0x128))(*loc100 + 0x128);
    if (tmpL3 == 0) {
      skp0_rt_00350744(&skp0_g_005d3be4);
      skp0_rt_001a89a8();
      skp0_rt_00351e08();
    }
    else {
      tmp1 = param_6 == 0;
      if (param_6 < 1) {
        ptu4 = &skp0_g_005d3be0;
      }
      else {
        ptu4 = &skp0_g_005d3bbc;
      }
      skp0_rt_001a89a8(ptu4,3,0);
      skp0_rt_00351e08();
    }
    fnp5 = (sk_fnptr)skp0_rt_0031b900(param_10);
    skp0_rt_0007c1c4();
    skp0_rt_00352e78();
    (*fnp5)();
    skp0_rt_003a25d4(savx19);
    skp0_rt_0034f030();
    skp0_rt_00352e78();
    (*fnp5)();
    skp0_rt_003a25d4(outx1_00);
    if (param_4 != 0) {
      skp0_rt_000bd3a4(param_3);
      (*fnp5)();
      skp0_rt_00354ae8();
      skp0_rt_00352e78();
      (*fnp5)();
      skp0_rt_003a25d4(outx1_01);
    }
    skp0_sk_desc_elements((word_t)(param_1),(word_t)(astk108),(word_t)(param_2),(word_t)(0x67b1e8),(word_t)(param_9),(word_t)(param_10));
    tmp9 = *(word_t *)(param_1 + 0x18);
    skp0_rt_003508cc();
    tmp6 = skp0_rt_0006a4c0();
    tmp6 = skp0_rt_003625e4(tmp6,tmp9,1);
    tmpL7 = skp0_rt_003198cc(tmp6,tmp6);
    if (tmpL7 == 0) {
      skp0_rt_00319808(param_1,loc158);
      tmp6 = skp0_rt_00354d80();
      idx2 = skp0_rt_00365b6c(&loca8,loc158,0x67b1e8,tmp6,6);
      if (idx2 != 0) goto L_00204a38;
    }
    else {
      tmp9 = *(word_t *)(param_1 + 0x18);
      skp0_rt_003508cc();
      tmp6 = skp0_rt_0006a4c0();
      skp0_rt_001b68a0(tmp6,tmp9);
      skp0_rt_0036b118();
L_00204a38:
      tmpL7 = *param_8;
      skp0_rt_00350af4();
      skp0_rt_001ef7ac();
      loc158.lo = skp0_rt_00351db4();
      if (!(bool)tmp1) {
        skp0_rt_0034b150();
        skp0_rt_00344e54(loc70);
        skp0_rt_0036b118(loce8);
        skp0_rt_00355fa0(&skp0_g_005d3bdd);
        skp0_rt_00354388();
        (*fnp5)();
        skp0_rt_003a25d4(outx1_03);
        skp0_rt_003516fc();
        skp0_rt_0035a9c8();
        skp0_rt_00350744(&skp0_g_005d3bc0);
        skp0_rt_001a89a8();
        skp0_rt_00354388();
        (*fnp5)();
        tmp6 = outx1_04;
L_00204b08:
        skp0_rt_003a25d4(tmp6);
        return;
      }
      tmp6 = *(word_t *)(tmpL7 + 0x10);
      skp0_rt_0009461c();
      skp0_rt_001ef808();
      skp0_rt_00355fa0(&skp0_g_005d3bdd);
      skp0_rt_00354388();
      (*fnp5)();
      skp0_rt_003a25d4(outx1_02);
      loc158.lo = tmp6;
      skp0_rt_003516fc();
      skp0_rt_0035a9c8();
    }
    skp0_rt_00350744(&skp0_g_005d3bc0);
    skp0_rt_001a89a8();
    skp0_rt_00352e78();
    (*fnp5)();
    skp0_rt_003a25d4(outx1_05);
    if (param_6 < 1) {
      skp0_rt_0034b150();
      skp0_rt_00344e54(loc70);
L_00204d3c:
      skp0_rt_0036b118(loce8);
      return;
    }
    (*locf0)(&locd8);
    if (locd8 != 0) {
      loca8 = locd8;
      stk98 = stkc8;
      loca0 = locd0;
      stk88 = stkb8;
      loc90 = locc0;
      loc80 = locb0;
      if (skp0_SCARRY8(param_5,2)) {
                    /* WARNING: Does not return */
        fnp5 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x204ebc);
        (*fnp5)();
      }
      skp0_sk_desc_children((word_t)(&loca8),(word_t)(param_2),(word_t)(param_5 + 2),(word_t)(param_6 + -1),(word_t)(param_7),(word_t)(param_8),(word_t)(param_9),(word_t)(param_10));
      loc78 = loca0;
      skp0_rt_0034b150();
      skp0_rt_00344e54(&loc78);
      skp0_rt_0036b118(stk88);
    }
    if (-1 < tmpL3) {
      ptl10 = (word_t *)loc100[2];
      if (tmpL3 == 0) {
        skp0_rt_0036b270(ptl10);
      }
      else {
        tmpL11 = loc100[3];
        skp0_rt_0036b270(ptl10);
        tmpL7 = 0;
        do {
          if (*param_7 < 1) {
            skp0_rt_0034b150();
            skp0_rt_00344e54(loc70);
            skp0_rt_0036b118(loce8);
            tmpL11 = param_5 + 4;
            if (skp0_SCARRY8(param_5,4)) {
                    /* WARNING: Does not return */
              fnp5 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x204ec0);
              (*fnp5)();
            }
            if (tmpL11 < 0) goto L_00204eb0;
            goto L_00204d98;
          }
          (**(sk_fnptr *)(*loc100 + 0xe8))(loc158,ptl10,tmpL11);
          tmp6 = loc158.hi;
          skp0_rt_00310d98(astk148,astk128);
          idx2 = skp0_rt_003a261c(ptl10);
          if (idx2 == 0) {
            (**(sk_fnptr *)(*loc100 + 0xf0))(ptl10,tmpL11);
            skp0_rt_00350fdc();
            skp0_rt_0036b118();
            ptl10 = loc100;
          }
          else {
            (**(sk_fnptr *)(*loc100 + 0xf8))(ptl10,tmpL11);
          }
          if (skp0_SCARRY8(param_5,2)) {
                    /* WARNING: Does not return */
            fnp5 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x204e78);
            (*fnp5)();
          }
          tmpL7 = tmpL7 + 1;
          skp0_rt_00350a1c(astk128,param_2);
          skp0_sk_desc_node((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
          skp0_rt_003a25d4(tmp6);
          skp0_rt_000026e8(astk128);
        } while (tmpL3 != tmpL7);
      }
      skp0_rt_0034b150();
      skp0_rt_00344e54(loc70);
      skp0_rt_0036b118(ptl10);
      goto L_00204d3c;
    }
  }
L_00204eb0:
  skp0_rt_00347da8();
L_00204e6c:
  skp0_rt_003504b8();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
  while( true ) {
    skp0_rt_00350744(&skp0_g_005d021c);
    pair12 = skp0_rt_001a89a8();
    loc158 = pair12;
    skp0_rt_00351744(loc158);
    skp0_sk_desc_sub((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
    skp0_rt_003a25d4(pair12.hi);
    tmpL11 = tmpL11 + -1;
    if (tmpL11 == 0) break;
L_00204d98:
    if (tmpL11 == 0) goto L_00204e68;
  }
  skp0_rt_003567f8();
  skp0_rt_00350744();
  skp0_rt_001a89a8();
  skp0_rt_00352ea8();
  (*fnp5)();
  skp0_rt_003a25d4(outx1_06);
  loc158.lo = tmpL3 - tmpL7;
  skp0_rt_003516fc();
  skp0_sk_desc_sub((word_t)(&loc158),(word_t)(param_2),(word_t)(0),(word_t)(0),(word_t)(0));
  if (tmpL7 != 0) {
    skp0_rt_00356f44();
    skp0_rt_00352ea8();
    (*fnp5)();
    skp0_rt_003a25d4(outx1_07);
  }
  if (tmpL3 + -1 == tmpL7) {
    fnp8 = sk_str_child_;
    tmp6 = 8;
  }
  else {
    fnp8 = sk_str_children_;
    tmp6 = 0xb;
  }
  skp0_rt_001a89a8(fnp8,tmp6,1);
  skp0_rt_00352ea8();
  (*fnp5)();
  skp0_rt_0036b118(ptl10);
  tmp6 = outx1_08;
  goto L_00204b08;
L_00204e68:
  skp0_rt_00348034();
  goto L_00204e6c;
}

/* FUN_00204ec0 @ 0x00204ec0   (est. skp0_sk_desc_dispatch)
 * Ghidra: void FUN_00204ec0(word_t param_1,word_t param_2,word_t param_3)
 * Description dispatch: builds a frame via skp0_rt_00355018 and calls skp0_sk_rec_descend (002046a8) with the frame fields.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_desc_dispatch(word_t param_1,word_t param_2,word_t param_3)
{

  sk_u128_t pair1;
  
  pair1 = skp0_rt_00355018();
  skp0_sk_rec_descend(pair1.lo,pair1.hi,pair1.hi,param_3);
  return;
}

/* FUN_00204f0c @ 0x00204f0c   (est. skp0_sk_desc_elements)
 * Ghidra: void FUN_00204f0c(word_t param_1,word_t param_2,uint8_t *param_3,word_t param_4,
                 word_t param_5,word_t param_6)
 * Description element printer: switch on element-count kind (byte at +0x10): case 4/others and 5/6/7 emit "elements", "1 element", "key-value pairs", "members"/"1 member" strings and resolve counts via vtable +0x128. Faithful to the Swift-style reflection dump layer.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_desc_elements(word_t param_1,word_t param_2,uint8_t *param_3,word_t param_4,
                 word_t param_5,word_t param_6)
{

  uint8_t flg1;
  uint8_t tmp2;
  int idx3;
  uint8_t *ptu4;
  word_t tmp5;
  char *fnp6;
  word_t tmpL7;
  word_t outx1;
  uint8_t *outx1_00;
  word_t outx1_01;
  word_t outx1_02;
  word_t outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx8_01;
  word_t outx8_02;
  word_t outx8_03;
  word_t outx8_04;
  word_t outx8_05;
  sk_fnptr outx8_06;
  word_t outx8_07;
  word_t outx8_08;
  sk_fnptr outx8_09;
  word_t outx8_10;
  sk_fnptr outx8_11;
  uint8_t *outx16;
  word_t outx16_00;
  word_t outx16_01;
  word_t outx16_02;
  word_t outx16_03;
  word_t *savx20;
  uint8_t *ptu8;
  uint32_t tmp9;
  sk_fnptr fnp10;
  uint8_t *savx23;
  uint8_t *savx24;
  uint8_t *savx25;
  uint8_t *savx27;
  word_t savx30;
  sk_u128_t pair11;
  sk_u128_t pair12;
  uint8_t astk50 [40];
  
  skp0_rt_0008e518();
  skp0_rt_00352ce0();
  ptu4 = param_3;
  skp0_rt_003561a0();
  skp0_rt_00349a68();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_00348abc();
  (*skp0_g_00658c00)();
  skp0_rt_0034b308();
  (*skp0_g_00658c00)();
  skp0_rt_0034b4c0();
  flg1 = *(uint8_t *)(outx1 + 0x10);
  tmp9 = (uint32_t)flg1;
  if ((tmp9 == 9) || (4 < tmp9 - 3)) {
L_switch4:
    fnp10 = *(sk_fnptr *)(outx16 + 0x10);
    skp0_rt_00350b48();
    (*fnp10)();
    skp0_rt_00352a8c();
    skp0_rt_0035a5e4();
    skp0_rt_003516f0();
    idx3 = skp0_rt_00365b6c();
    if (idx3 == 0) {
      skp0_rt_00355674();
      skp0_rt_00355aa0();
      skp0_rt_00344e54(astk50);
      skp0_rt_00350a34();
      (*fnp10)();
      skp0_rt_00353758();
      skp0_rt_0035a5e4();
      skp0_rt_003511c0();
      idx3 = skp0_rt_00365b6c();
      ptu4 = savx23;
      if (idx3 != 0) goto L_0020501c;
      skp0_rt_00355674();
      skp0_rt_00355a64();
      skp0_rt_00344e54(astk50);
      skp0_rt_0034e55c();
      (*fnp10)();
      skp0_rt_00356fb8();
      skp0_rt_0035a5e4();
      skp0_rt_00350ad0();
      idx3 = skp0_rt_00365b6c();
      if (idx3 == 0) {
        skp0_rt_00355674();
        skp0_rt_00355a2c();
        skp0_rt_00344e54(astk50);
        if (flg1 == 9) {
L_00205238:
          pair11 = skp0_rt_00351714();
          skp0_rt_002667a8(pair11.lo,pair11.hi,param_3,1);
          goto L_00205068;
        }
        if (flg1 < 2) {
L_00205384:
          skp0_sk_boot_cpu(*savx20,1);
          skp0_rt_00354f1c();
          skp0_rt_0031b900(param_6);
          skp0_rt_00351318();
          skp0_rt_00350974();
          (*outx8_06)();
        }
        else {
          if (flg1 != 2) {
            if (flg1 != 8) goto L_00205238;
            goto L_00205384;
          }
          skp0_sk_boot_cpu(*savx20,1);
          skp0_rt_0035351c();
          fnp10 = (sk_fnptr)skp0_rt_0031b900(param_6);
          skp0_rt_00351648();
          skp0_rt_00350974();
          (*fnp10)();
          skp0_rt_003a25d4((word_t)(outx16 + 0x10) & 0xffffffffffff | 0xe3ba000000000000);
          skp0_rt_00350518();
          tmpL7 = skp0_rt_003a0b04();
          if ((tmpL7 == 0) || (skp0_rt_001e9f14(), outx1_01 == 0)) goto L_00205068;
          skp0_rt_003562d4();
          skp0_rt_0034fb28();
          skp0_rt_001a89a8();
          (*fnp10)();
          skp0_rt_003a25d4(outx1_02);
          skp0_rt_0034d758();
          (*fnp10)();
        }
        skp0_rt_003a25d4();
        goto L_00205068;
      }
      skp0_rt_00077070(astk50,&sk_stack_ffffffffffffffd8);
      skp0_rt_0034b440(&sk_stack_ffffffffffffffd8);
      tmp5 = skp0_rt_003194f8();
      skp0_rt_00351978(tmp5,param_3);
      (*outx8_01)();
    }
    else {
L_0020501c:
      skp0_rt_00077070(astk50,&sk_stack_ffffffffffffffd8);
      skp0_rt_0034b440(&sk_stack_ffffffffffffffd8);
      skp0_rt_00027724();
      skp0_rt_0034ce58();
      (*outx8_00)();
      skp0_rt_003569b4();
      skp0_rt_0035053c(param_3,ptu4);
      skp0_rt_002678b4();
      skp0_rt_003a25d4();
    }
    skp0_rt_000026e8(&sk_stack_ffffffffffffffd8);
L_00205068:
    skp0_rt_0008e500(savx30);
    return;
  }
  switch(tmp9) {
  default:
    ptu8 = (uint8_t *)savx20[1];
    skp0_rt_000027e8();
    ptu4 = (uint8_t *)(**(sk_fnptr *)(outx16_00 + 0x128))();
    tmp2 = ptu4 == (uint8_t *)((word_t)&skp0_g_tls_magic + 1);
    if (!(bool)tmp2) {
      skp0_rt_003567f8();
      skp0_rt_00350744();
      skp0_rt_001a89a8();
      skp0_rt_00354410();
      skp0_rt_003a25d4(0xe000000000000000);
      pair11 = skp0_rt_00356340();
      skp0_rt_002364dc(pair11.lo,pair11.hi,ptu4);
      skp0_rt_00354000();
      skp0_rt_0034b824();
      if ((outx8_03 == 0) &&
         ((((word_t)savx24 & ((word_t)ptu8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        skp0_rt_003a25d4(ptu8);
        ptu8 = ptu4;
      }
      else {
        if (((word_t)ptu8 >> 0x3d & 1) == 0) {
          skp0_rt_0034efc8();
        }
        else if (((word_t)ptu4 >> 0x3d & 1) != 0) {
          skp0_rt_00351714();
          skp0_rt_0035359c();
          skp0_rt_0034b7c8();
          if (!(bool)tmp2) {
            skp0_rt_00352350();
            skp0_rt_003a25d4();
            skp0_rt_003a25d4(ptu4);
            skp0_rt_003581c4();
            goto L_00205548;
          }
        }
        pair11 = skp0_rt_00351274();
        skp0_rt_002a4c98(pair11.lo,pair11.hi,0);
        skp0_rt_003a25d4(ptu4);
        ptu4 = ptu8;
        savx25 = savx24;
      }
L_00205548:
      fnp6 = sk_str_elements_;
      tmp5 = 10;
      break;
    }
    fnp6 = sk_str__1_element_;
    tmp5 = 0xb;
L_0020520c:
    skp0_rt_001a89a8(fnp6,tmp5,1);
    skp0_rt_00355c78();
    goto L_00205634;
  case 4:
    goto L_switch4;
  case 5:
    ptu8 = (uint8_t *)savx20[1];
    skp0_rt_000027e8();
    ptu4 = (uint8_t *)(**(sk_fnptr *)(outx16_02 + 0x128))();
    tmp2 = ptu4 == (uint8_t *)((word_t)&skp0_g_tls_magic + 1);
    if ((bool)tmp2) {
      fnp6 = sk_str_1_element;
      tmp5 = 9;
      goto L_0020520c;
    }
    skp0_rt_003497ec();
    skp0_rt_001a89a8();
    skp0_rt_00354410();
    skp0_rt_003a25d4(0xe000000000000000);
    pair11 = skp0_rt_00356340();
    skp0_rt_002364dc(pair11.lo,pair11.hi,ptu4);
    skp0_rt_00354000();
    skp0_rt_0034b824();
    if ((outx8_04 == 0) &&
       ((((word_t)savx24 & ((word_t)ptu8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      skp0_rt_003a25d4(ptu8);
      ptu8 = ptu4;
    }
    else {
      if (((word_t)ptu8 >> 0x3d & 1) == 0) {
        skp0_rt_0034efc8();
      }
      else if (((word_t)ptu4 >> 0x3d & 1) != 0) {
        skp0_rt_00351714();
        skp0_rt_0035359c();
        skp0_rt_0034b7c8();
        if (!(bool)tmp2) {
          skp0_rt_00352350();
          skp0_rt_003a25d4();
          skp0_rt_003a25d4(ptu4);
          skp0_rt_003581c4();
          goto L_00205588;
        }
      }
      pair11 = skp0_rt_00351274();
      skp0_rt_002a4c98(pair11.lo,pair11.hi,0);
      skp0_rt_003a25d4(ptu4);
      ptu4 = ptu8;
      savx25 = savx24;
    }
L_00205588:
    fnp6 = sk_str_elements;
    tmp5 = 9;
    break;
  case 6:
    ptu4 = (uint8_t *)savx20[1];
    skp0_rt_000027e8();
    ptu8 = (uint8_t *)(**(sk_fnptr *)(outx16_01 + 0x128))();
    tmp2 = ptu8 == (uint8_t *)((word_t)&skp0_g_tls_magic + 1);
    if ((bool)tmp2) {
      skp0_rt_00355754(sk_str_1_key_value_pair);
      skp0_rt_001a89a8();
      savx24 = outx1_00;
    }
    else {
      skp0_rt_0006e778(0x12);
      pair11 = skp0_rt_0035abd8();
      skp0_rt_003497ec();
      skp0_rt_001a89a8();
      skp0_rt_00356fd8();
      skp0_rt_0034b824();
      if ((outx8_02 == 0) &&
         ((((word_t)outx16 & ((word_t)ptu4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        skp0_rt_003a25d4(ptu4);
        savx24 = savx23;
      }
      else {
        if (((word_t)ptu4 >> 0x3d & 1) == 0) {
          skp0_rt_0034efc8();
        }
        else if (((word_t)savx23 >> 0x3d & 1) != 0) {
          skp0_rt_00351f88();
          skp0_rt_0035359c();
          skp0_rt_0034b7c8();
          if (!(bool)tmp2) {
            skp0_rt_003530bc();
            skp0_rt_003a25d4();
            skp0_rt_003a25d4();
            savx25 = outx16;
            savx24 = savx27;
            goto L_00205424;
          }
        }
        ptu4 = &sk_stack_ffffffffffffffd8;
        pair12 = skp0_rt_00351274();
        skp0_rt_002a4c98(pair12.lo,pair12.hi,0);
        skp0_rt_003a25d4();
        savx25 = (uint8_t *)pair11.lo;
        savx24 = (uint8_t *)pair11.hi;
      }
L_00205424:
      pair11 = skp0_rt_00356340();
      skp0_rt_002364dc(pair11.lo,pair11.hi,ptu8);
      skp0_rt_00355c78();
      skp0_rt_0034ddd8();
      if ((outx8_07 == 0) &&
         ((((word_t)savx25 & ((word_t)savx24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        skp0_rt_003a25d4(savx24);
        ptu4 = outx16;
      }
      else {
        if (((word_t)savx24 >> 0x3d & 1) == 0) {
          skp0_rt_0034dd64();
        }
        else if (((word_t)ptu8 >> 0x3d & 1) != 0) {
          skp0_rt_0034ff88();
          skp0_rt_0034b1a0();
          if (!(bool)tmp2) {
            skp0_rt_003530d8();
            skp0_rt_003a25d4();
            skp0_rt_003a25d4(ptu8);
            ptu8 = savx25;
            goto L_00205488;
          }
        }
        skp0_rt_0034ee38();
        skp0_rt_002a4c98();
        skp0_rt_003a25d4(ptu8);
        ptu4 = savx25;
        ptu8 = savx24;
      }
L_00205488:
      skp0_rt_00355754(sk_str_key_value_pairs);
      skp0_rt_001a89a8();
      skp0_rt_00356fd8();
      skp0_rt_0034d044();
      if ((outx8_08 == 0) &&
         ((((word_t)ptu4 & ((word_t)ptu8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
        skp0_rt_003a25d4(ptu8);
      }
      else {
        if (((word_t)ptu8 >> 0x3d & 1) == 0) {
          skp0_rt_0034efc8();
        }
        else if (((word_t)savx24 >> 0x3d & 1) != 0) {
          skp0_rt_00100c38();
          skp0_rt_0035359c();
          skp0_rt_0034b7c8();
          if (!(bool)tmp2) {
            skp0_rt_0035351c();
            skp0_rt_003a25d4(ptu8);
            skp0_rt_003a25d4(savx24);
            savx24 = ptu4;
            goto L_002054f4;
          }
        }
        pair11 = skp0_rt_00351274();
        skp0_rt_002a4c98(pair11.lo,pair11.hi,0);
        skp0_rt_003a25d4(savx24);
        savx24 = ptu8;
      }
    }
L_002054f4:
    skp0_rt_0031b900(param_6);
    skp0_rt_0034e044();
    skp0_rt_003515fc();
    (*outx8_09)();
    goto L_00205654;
  case 7:
    ptu8 = (uint8_t *)savx20[1];
    skp0_rt_000027e8();
    ptu4 = (uint8_t *)(**(sk_fnptr *)(outx16_03 + 0x128))();
    tmp2 = ptu4 == (uint8_t *)((word_t)&skp0_g_tls_magic + 1);
    if ((bool)tmp2) {
      fnp6 = sk_str_1_member;
      tmp5 = 8;
      goto L_0020520c;
    }
    skp0_rt_003497ec();
    skp0_rt_001a89a8();
    skp0_rt_00354410();
    skp0_rt_003a25d4(0xe000000000000000);
    pair11 = skp0_rt_00356340();
    skp0_rt_002364dc(pair11.lo,pair11.hi,ptu4);
    skp0_rt_00354000();
    skp0_rt_0034b824();
    if ((outx8_05 == 0) &&
       ((((word_t)savx24 & ((word_t)ptu8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      skp0_rt_003a25d4(ptu8);
      ptu8 = ptu4;
    }
    else {
      if (((word_t)ptu8 >> 0x3d & 1) == 0) {
        skp0_rt_0034efc8();
      }
      else if (((word_t)ptu4 >> 0x3d & 1) != 0) {
        skp0_rt_00351714();
        skp0_rt_0035359c();
        skp0_rt_0034b7c8();
        if (!(bool)tmp2) {
          skp0_rt_00352350();
          skp0_rt_003a25d4();
          skp0_rt_003a25d4(ptu4);
          skp0_rt_003581c4();
          goto L_002055c8;
        }
      }
      pair11 = skp0_rt_00351274();
      skp0_rt_002a4c98(pair11.lo,pair11.hi,0);
      skp0_rt_003a25d4(ptu4);
      ptu4 = ptu8;
      savx25 = savx24;
    }
L_002055c8:
    fnp6 = sk_str_members;
    tmp5 = 8;
  }
  skp0_rt_001a89a8(fnp6,tmp5,1);
  skp0_rt_00355c78();
  skp0_rt_0034ddd8();
  if ((outx8_10 == 0) &&
     ((((word_t)savx25 & ((word_t)ptu4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    skp0_rt_003a25d4(ptu4);
  }
  else {
    if (((word_t)ptu4 >> 0x3d & 1) == 0) {
      skp0_rt_0034dd64();
    }
    else if (((word_t)savx24 >> 0x3d & 1) != 0) {
      skp0_rt_0034ff88();
      skp0_rt_0034b1a0();
      if (!(bool)tmp2) {
        skp0_rt_003530d8();
        skp0_rt_003a25d4();
        skp0_rt_003a25d4();
        savx24 = savx25;
        goto L_00205634;
      }
    }
    skp0_rt_0034ee38();
    skp0_rt_002a4c98();
    skp0_rt_003a25d4();
    savx24 = ptu8;
  }
L_00205634:
  skp0_rt_0031b900(param_6);
  skp0_rt_0034db88();
  skp0_rt_003515fc();
  (*outx8_11)();
L_00205654:
  skp0_rt_0008e500(savx24,savx30);
  skp0_rt_003a25d4();
  return;
}

/* FUN_00205844 @ 0x00205844   (est. skp0_sk_desc_sub)
 * Ghidra: void FUN_00205844(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
 * Description sub-walker: resolves a child list, loops with skp0_rt_00365b6c branches, builds a frame and emits; fallback releases.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_desc_sub(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
{

  int idx1;
  word_t tmp2;
  word_t tmp3;
  word_t outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx8_01;
  sk_fnptr outx8_02;
  sk_fnptr outx8_03;
  sk_fnptr outx8_04;
  word_t outx16;
  sk_fnptr fnp4;
  word_t savx24;
  word_t savx30;
  sk_u128_t pair5;
  word_t loc60 [3];
  word_t loc48;
  uint8_t loc30[8];
  word_t loc28;
  word_t loc18;
  word_t loc10;
  
  skp0_rt_0008e518();
  tmp2 = param_3;
  skp0_rt_00355bdc();
  skp0_rt_00349720();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_003493c4();
  skp0_rt_0034d5a8();
  (*skp0_g_00658c00)();
  skp0_rt_0034aea8();
  (*skp0_g_00658c00)();
  skp0_rt_0034a464();
  (*skp0_g_00658c00)();
  skp0_rt_0034b540();
  (*skp0_g_00658c00)();
  skp0_rt_0034ba68();
  loc18 = tmp2;
  skp0_rt_00319a4c(loc30);
  fnp4 = *(sk_fnptr *)(outx16 + 0x10);
  skp0_rt_0035119c();
  (*fnp4)();
  skp0_rt_0006a4c0(loc30,loc18);
  skp0_rt_000dbc98();
  skp0_rt_003625e4();
  idx1 = skp0_rt_003629b4();
  skp0_rt_000026e8(loc30);
  if (idx1 == 0) {
    skp0_rt_0035119c();
    (*fnp4)();
    skp0_rt_00353d64();
    idx1 = skp0_rt_00356fcc(loc30);
    if (idx1 != 0) {
      skp0_rt_0031b900(param_5);
      tmp2 = skp0_rt_00351318();
      skp0_rt_003534ec(tmp2,loc28);
      (*outx8_01)();
      skp0_rt_003a25d4(loc28);
      goto L_00205a18;
    }
    skp0_rt_0034feb0();
    (*fnp4)();
    skp0_rt_00356fb8();
    skp0_rt_00355bf4();
    skp0_rt_00351b38();
    idx1 = skp0_rt_00365b6c();
    if (idx1 == 0) {
      skp0_rt_0034fd6c();
      skp0_rt_00355a2c();
      skp0_rt_00344e54(loc60);
      skp0_rt_00350edc();
      (*fnp4)();
      skp0_rt_00353758();
      skp0_rt_00355bf4();
      skp0_rt_00351a20();
      idx1 = skp0_rt_00365b6c();
      if (idx1 == 0) {
        skp0_rt_0034fd6c();
        skp0_rt_00355a64();
        skp0_rt_00344e54(loc60);
        pair5 = skp0_rt_0008e388();
        tmp2 = param_3;
        (*fnp4)(pair5.lo,pair5.hi,param_3);
        skp0_rt_00352a8c();
        skp0_rt_00355bf4();
        skp0_rt_00350548();
        idx1 = skp0_rt_00365b6c();
        if (idx1 == 0) {
          skp0_rt_0034fd6c();
          skp0_rt_00355aa0();
          skp0_rt_00344e54(loc60);
          loc48 = param_3;
          skp0_rt_00319a4c(loc60);
          skp0_rt_0035119c();
          (*fnp4)();
          skp0_rt_0035a1e8();
          tmp2 = skp0_rt_001edb28();
          skp0_rt_00358dd0(tmp2,loc30);
          skp0_rt_002667a8();
          loc60[0] = loc28;
          skp0_rt_0034b150();
          skp0_rt_00344e54(loc60);
          skp0_rt_0036b118(loc10);
          goto L_00205a18;
        }
        skp0_rt_00358fdc();
        skp0_rt_0034f714(loc30);
        tmp3 = skp0_rt_00027724(loc10);
        skp0_rt_0008e388(tmp3);
        (*outx8_04)();
        skp0_rt_003569b4();
      }
      else {
        skp0_rt_00358fdc();
        skp0_rt_0034f714(loc30);
        tmp3 = skp0_rt_00027724(loc10);
        skp0_rt_0008e388(tmp3);
        (*outx8_03)();
        skp0_rt_003569b4();
      }
      skp0_rt_00352a4c(savx24,tmp2);
      goto L_002059ac;
    }
    skp0_rt_00358fdc();
    skp0_rt_0034f714(loc30);
    tmp2 = skp0_rt_003194f8(loc10);
    skp0_rt_00351ba0(tmp2,savx24);
    (*outx8_02)();
  }
  else {
    pair5 = skp0_rt_00350a70();
    (*fnp4)(pair5.lo,pair5.hi,param_3);
    skp0_rt_00352a8c();
    skp0_rt_0035a5d8();
    skp0_rt_00353214();
    skp0_rt_00365b6c();
    skp0_rt_0034f714(loc30);
    tmp2 = skp0_rt_00027724(loc10);
    skp0_rt_0008e388(tmp2);
    (*outx8_00)();
    skp0_rt_003569b4();
L_002059ac:
    skp0_rt_002678b4();
    skp0_rt_003a25d4(param_3);
  }
  skp0_rt_000026e8(loc30);
L_00205a18:
  skp0_rt_0008e500(savx30);
  return;
}

/* FUN_00205bd0 @ 0x00205bd0   (est. skp0_sk_desc_children)
 * Ghidra: void FUN_00205bd0(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t *param_5,
                 word_t param_6,word_t param_7,word_t param_8)
 * Description children walker: recursively describes object children; decrements a depth budget (*param_5), emits "child"/"children"/"super" strings, recurses via skp0_sk_desc_children (itself) and skp0_sk_desc_sub (00205844). Traps on carry overflow; panic path noreturn.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_desc_children(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t *param_5,
                 word_t param_6,word_t param_7,word_t param_8)
{

  int idx1;
  word_t tmpL2;
  word_t *ptu3;
  sk_fnptr fnp4;
  word_t tmp5;
  char *fnp6;
  word_t outx1;
  word_t outx1_00;
  word_t outx1_01;
  word_t outx1_02;
  word_t outx1_03;
  word_t outx1_04;
  word_t outx1_05;
  sk_fnptr outx8;
  word_t tmpL7;
  word_t *savx21;
  word_t savx22;
  word_t *savx23;
  word_t *ptl8;
  word_t tmpL9;
  word_t *ptl10;
  sk_u128_t pair11;
  word_t loc120;
  word_t stk118;
  uint8_t astk110 [32];
  uint8_t astkf0 [32];
  word_t locd0;
  word_t locc8;
  word_t stkc0;
  word_t locb8;
  word_t stkb0;
  uint8_t loca8;
  word_t loca0;
  word_t loc98;
  word_t stk90;
  word_t loc88;
  word_t stk80;
  uint8_t loc78;
  word_t loc70 [2];
  
  if (*param_5 < 1) {
    return;
  }
  *param_5 = *param_5 + -1;
  if (-1 < param_3) {
    skp0_rt_0035089c();
    if (param_3 != 0) {
      savx21 = &skp0_g_005d021c;
      tmpL2 = param_3;
      do {
        if (tmpL2 == 0) goto L_00206044;
        skp0_rt_00350744(&skp0_g_005d021c);
        skp0_rt_001a89a8();
        skp0_rt_00354da0(param_8);
        skp0_rt_003508b4();
        skp0_rt_0035433c();
        (*outx8)();
        skp0_rt_003a25d4(outx1);
        tmpL2 = tmpL2 + -1;
      } while (tmpL2 != 0);
    }
    ptl10 = (word_t *)savx23[1];
    tmpL2 = (**(sk_fnptr *)(*ptl10 + 0x128))();
    if (tmpL2 == 0) {
      pair11 = (sk_u128_t){ .lo = skp0_rt_00350744(&skp0_g_005d3be4), .hi = 0 };
    }
    else {
      if (param_4 < 1) {
        ptu3 = &skp0_g_005d3be0;
      }
      else {
        ptu3 = &skp0_g_005d3bbc;
      }
      pair11.hi = 3;
      pair11.lo = (word_t)ptu3;
    }
    skp0_rt_001a89a8(pair11.lo,pair11.hi);
    skp0_rt_00350b90();
    fnp4 = (sk_fnptr)skp0_rt_0031b900(param_8);
    skp0_rt_0006b6f4();
    skp0_rt_0035433c();
    (*fnp4)();
    skp0_rt_003a25d4(savx21);
    skp0_rt_0035940c(sk_str_super_);
    skp0_rt_0035433c();
    (*fnp4)();
    skp0_rt_003a25d4(outx1_00);
    loc120 = *savx23;
    tmp5 = skp0_rt_00354d80();
    skp0_rt_00353bc4(&loc120,savx22,tmp5);
    skp0_sk_desc_recurse();
    skp0_rt_00350744(&skp0_g_005d3bc0);
    skp0_rt_001a89a8();
    skp0_rt_0035433c();
    (*fnp4)();
    skp0_rt_003a25d4(outx1_01);
    if (param_4 < 1) {
      return;
    }
    (*(sk_fnptr)savx23[3])(&locd0);
    if (locd0 != 0) {
      loca0 = locd0;
      stk90 = stkc0;
      loc98 = locc8;
      stk80 = stkb0;
      loc88 = locb8;
      loc78 = loca8;
      if (skp0_SCARRY8(param_3,2)) {
                    /* WARNING: Does not return */
        fnp4 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x20609c);
        (*fnp4)();
      }
      skp0_sk_desc_children((word_t)(&loca0),(word_t)(savx22),(word_t)(param_3 + 2),(word_t)(param_4 + -1),(word_t *)(param_5),(word_t)(param_6),(word_t)(param_7),(word_t)(param_8));
      loc70[0] = loc98;
      skp0_rt_0034b150();
      skp0_rt_00344e54(loc70);
      skp0_rt_0036b118(stk80);
    }
    if (-1 < tmpL2) {
      if (tmpL2 == 0) {
        return;
      }
      ptl8 = (word_t *)ptl10[2];
      tmpL9 = ptl10[3];
      skp0_rt_0036b270(ptl8);
      tmpL7 = 0;
      while (0 < *param_5) {
        (**(sk_fnptr *)(*ptl10 + 0xe8))(&loc120,ptl8,tmpL9);
        tmp5 = stk118;
        skp0_rt_00310d98(astk110,astkf0);
        idx1 = skp0_rt_003a261c(ptl8);
        if (idx1 == 0) {
          (**(sk_fnptr *)(*ptl10 + 0xf0))(ptl8,tmpL9);
          skp0_rt_0035351c();
          skp0_rt_0036b118(ptl8);
          ptl8 = ptl10;
        }
        else {
          (**(sk_fnptr *)(*ptl10 + 0xf8))(ptl8,tmpL9);
        }
        if (skp0_SCARRY8(param_3,2)) {
                    /* WARNING: Does not return */
          fnp4 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x206054);
          (*fnp4)();
        }
        tmpL7 = tmpL7 + 1;
        skp0_rt_00351b78(astkf0,savx22);
        skp0_sk_desc_node((word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0),(word_t)(0));
        skp0_rt_003a25d4(tmp5);
        skp0_rt_000026e8(astkf0);
        if (tmpL2 == tmpL7) {
          skp0_rt_0036b118(ptl8);
          return;
        }
      }
      tmpL9 = param_3 + 4;
      if (skp0_SCARRY8(param_3,4)) {
                    /* WARNING: Does not return */
        fnp4 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x2060a0);
        (*fnp4)();
      }
      if (-1 < tmpL9) {
        while (tmpL9 != 0) {
          skp0_rt_00350744(&skp0_g_005d021c);
          skp0_rt_001a89a8();
          skp0_rt_00352ea8();
          (*fnp4)();
          skp0_rt_003a25d4(outx1_02);
          tmpL9 = tmpL9 + -1;
          if (tmpL9 == 0) {
            skp0_rt_003567f8();
            skp0_rt_00350744();
            skp0_rt_001a89a8();
            skp0_rt_00352ea8();
            (*fnp4)();
            skp0_rt_003a25d4(outx1_03);
            loc120 = tmpL2 - tmpL7;
            skp0_rt_003516fc();
            skp0_sk_desc_sub((word_t)(&loc120),(word_t)(savx22),(word_t)(0),(word_t)(0),(word_t)(0));
            if (tmpL7 != 0) {
              skp0_rt_00356f44();
              skp0_rt_00352ea8();
              (*fnp4)();
              skp0_rt_003a25d4(outx1_04);
            }
            if (tmpL2 + -1 == tmpL7) {
              fnp6 = sk_str_child_;
              tmp5 = 8;
            }
            else {
              fnp6 = sk_str_children_;
              tmp5 = 0xb;
            }
            skp0_rt_001a89a8(fnp6,tmp5,1);
            skp0_rt_00352ea8();
            (*fnp4)();
            skp0_rt_0036b118(ptl8);
            skp0_rt_003a25d4(outx1_05);
            return;
          }
        }
L_00206044:
        skp0_rt_00348034();
        goto L_00206048;
      }
    }
  }
  skp0_rt_00347da8();
L_00206048:
  skp0_rt_003504b8();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_002060a0 @ 0x002060a0   (est. skp0_sk_desc_slot)
 * Ghidra: void FUN_002060a0(word_t param_1)
 * Description slot helper: releases the value at object+0x10 (skp0_rt_0036b270).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_desc_slot(word_t param_1)
{

  skp0_rt_0036b270(*(word_t *)(param_1 + 0x10));
  return;
}

/* FUN_002060d4 @ 0x002060d4   (est. skp0_sk_desc_recurse)
 * Ghidra: void FUN_002060d4()
 * Description recursion helper: a three-branch runtime walk (skp0_rt_00365b6c == 0 sequence) building frames and choosing tail paths; invoked by skp0_sk_desc_children and skp0_sk_boot_cold.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_desc_recurse()
{

  int idx1;
  word_t tmp2;
  word_t outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx8_01;
  word_t outx16;
  sk_fnptr fnp3;
  word_t savx30;
  word_t loc60 [3];
  uint8_t astk30[8];
  word_t loc28;
  word_t loc10;
  
  skp0_rt_0008e518();
  tmp2 = skp0_rt_0034d654();
  skp0_rt_00349720();
  (*skp0_g_00658c00)(*(word_t *)(outx8 + 0x40));
  skp0_rt_00348abc();
  (*skp0_g_00658c00)();
  skp0_rt_0034a464();
  (*skp0_g_00658c00)();
  skp0_rt_0034ba68();
  fnp3 = *(sk_fnptr *)(outx16 + 0x10);
  skp0_rt_00350a70();
  (*fnp3)();
  skp0_rt_00352a8c();
  skp0_rt_00355bf4();
  skp0_rt_00353214();
  idx1 = skp0_rt_00365b6c();
  if (idx1 == 0) {
    skp0_rt_0034fd6c();
    skp0_rt_00355aa0();
    skp0_rt_00344e54(loc60);
    skp0_rt_0034feb0();
    (*fnp3)();
    skp0_rt_00353758();
    skp0_rt_00355bf4();
    skp0_rt_00351b38();
    idx1 = skp0_rt_00365b6c();
    if (idx1 != 0) goto L_002061bc;
    skp0_rt_0034fd6c();
    skp0_rt_00355a64();
    skp0_rt_00344e54(loc60);
    skp0_rt_00350edc();
    (*fnp3)();
    skp0_rt_00356fb8();
    skp0_rt_00355bf4();
    skp0_rt_00351a20();
    idx1 = skp0_rt_00365b6c();
    if (idx1 == 0) {
      skp0_rt_0034fd6c();
      skp0_rt_00355a2c();
      skp0_rt_00344e54(loc60);
      skp0_rt_00319a4c(loc60);
      skp0_rt_0035119c();
      (*fnp3)();
      skp0_rt_0035a1e8();
      skp0_rt_001edb28();
      skp0_rt_002667a8(tmp2,astk30);
      loc60[0] = loc28;
      skp0_rt_0034b150();
      skp0_rt_00344e54(loc60);
      skp0_rt_0036b118(loc10);
      goto L_00206204;
    }
    skp0_rt_00358fdc();
    skp0_rt_0034b440(astk30);
    tmp2 = skp0_rt_003194f8();
    skp0_rt_0034b778(tmp2);
    skp0_rt_00351978();
    (*outx8_01)();
  }
  else {
L_002061bc:
    skp0_rt_00358fdc();
    skp0_rt_0034b440(astk30);
    skp0_rt_00027724();
    skp0_rt_0034ce58();
    (*outx8_00)();
    skp0_rt_003569b4();
    skp0_rt_00350aac();
    skp0_rt_002678b4();
    skp0_rt_003a25d4();
  }
  skp0_rt_000026e8(astk30);
L_00206204:
  skp0_rt_0008e500(savx30);
  return;
}

/* FUN_002062e4 @ 0x002062e4   (est. skp0_sk_vt_overridden_a)
 * Ghidra: void FUN_002062e4(void)
 * Vtable override stub A: jumps to shared vt teardown skp0_rt_001b5a88.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_overridden_a(void)
{

  skp0_rt_001b5a88();
  return;
}

/* FUN_002062e8 @ 0x002062e8   (est. skp0_sk_vt_overridden_b)
 * Ghidra: void FUN_002062e8(void)
 * Vtable override stub B: jumps to shared vt teardown skp0_rt_001b5a88.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_overridden_b(void)
{

  skp0_rt_001b5a88();
  return;
}

/* FUN_002062fc @ 0x002062fc   (est. skp0_sk_vt_overridden_c)
 * Ghidra: void FUN_002062fc(void)
 * Vtable override stub C: jumps to shared vt teardown skp0_rt_001b5784.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_overridden_c(void)
{

  skp0_rt_001b5784();
  return;
}

/* FUN_00206300 @ 0x00206300   (est. skp0_sk_vt_overridden_d)
 * Ghidra: void FUN_00206300(void)
 * Vtable override stub D: jumps to shared vt teardown skp0_rt_001b5784.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_overridden_d(void)
{

  skp0_rt_001b5784();
  return;
}

/* FUN_00206314 @ 0x00206314   (est. skp0_sk_vt_overridden_e)
 * Ghidra: void FUN_00206314(void)
 * Vtable override stub E: jumps to thunk skp0_rt_00284424.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_overridden_e(void)
{

  skp0_rt_00284424();
  return;
}

/* FUN_00206318 @ 0x00206318   (est. skp0_sk_vt_overridden_f)
 * Ghidra: void FUN_00206318(void)
 * Vtable override stub F: jumps to thunk skp0_rt_00284424.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_overridden_f(void)
{

  skp0_rt_00284424();
  return;
}

/* FUN_0020632c @ 0x0020632c   (est. skp0_sk_assert_fmt_a)
 * Ghidra: void FUN_0020632c(word_t param_1)
 * Assertion helper: resolves a diagnostic (skp0_rt_00376820 with skp0_g_004e956c) and calls skp0_rt_001a0194. Likely assert-failure registration.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_fmt_a(word_t param_1)
{

  word_t tmp1;
  
  tmp1 = skp0_rt_00376820(&skp0_g_004e956c,param_1).lo;
  skp0_rt_001a0194(param_1,tmp1);
  return;
}

/* FUN_00206374 @ 0x00206374   (est. skp0_sk_assert_fmt_b)
 * Ghidra: void FUN_00206374(word_t param_1)
 * Assertion helper variant: resolves diagnostic and calls skp0_rt_001e088c.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_fmt_b(word_t param_1)
{

  word_t tmp1;
  
  tmp1 = skp0_rt_00376820(&skp0_g_004e956c,param_1).lo;
  skp0_rt_001e088c(param_1,tmp1);
  return;
}

/* FUN_002063bc @ 0x002063bc   (est. skp0_sk_assert_fail)
 * Ghidra: void FUN_002063bc(void)
 * Assertion failure (noreturn): enables assert context (skp0_rt_003488bc(1)), then panics via skp0_rt_00353b34 + skp0_rt_001afe4c.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_fail(void)
{

  word_t outx1;
  word_t tmp1;
  
  skp0_rt_003488bc(1);
  tmp1 = outx1;
  skp0_rt_0034f674();
  skp0_rt_00353b34(tmp1);
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_00206408 @ 0x00206408   (est. skp0_sk_assert_fail2)
 * Ghidra: void FUN_00206408(void)
 * Assertion failure variant (noreturn): skp0_rt_003488bc(1) + panic.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_fail2(void)
{

  word_t outx1;
  word_t tmp1;
  
  skp0_rt_003488bc(1);
  tmp1 = outx1;
  skp0_rt_0034f674();
  skp0_rt_00353b34(tmp1);
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_00206454 @ 0x00206454   (est. skp0_sk_assert_empty)
 * Ghidra: sk_u128_t FUN_00206454(void)
 * Assertion failure variant (noreturn): skp0_rt_00348638(1) + panic (skp0_rt_001afe4c).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t skp0_sk_assert_empty(void)
{

  skp0_rt_00348638(1);
  skp0_rt_00349de8();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_00206494 @ 0x00206494   (est. skp0_sk_assert_empty2)
 * Ghidra: void FUN_00206494(void)
 * Assertion failure variant (noreturn): skp0_rt_00348638(1) + panic.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_empty2(void)
{

  skp0_rt_00348638(1);
  skp0_rt_00349de8();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_002064d4 @ 0x002064d4   (est. skp0_sk_assert_both)
 * Ghidra: word_t FUN_002064d4()
 * Assert both-zero check: calls skp0_sk_assert_empty (00206454); if the returned pair is nonzero, panics (noreturn); else returns.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_assert_both()
{

  sk_u128_t pair1;
  
  pair1 = skp0_sk_assert_empty();
  if (pair1.lo != 0 || pair1.hi != 0) {
    skp0_rt_00348638(1);
    skp0_rt_00349de8();
                    /* WARNING: Subroutine does not return */
    skp0_rt_001afe4c();
  }
  return 0;
}

/* FUN_002064e4 @ 0x002064e4   (est. skp0_sk_assert_ze_pair)
 * Ghidra: void FUN_002064e4(word_t param_1,word_t param_2)
 * Assert zero-pair: if either param is nonzero, panic (noreturn). Invariant guard.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_ze_pair(word_t param_1,word_t param_2)
{

  if (param_1 != 0 || param_2 != 0) {
    skp0_rt_00348638(1);
    skp0_rt_00349de8();
                    /* WARNING: Subroutine does not return */
    skp0_rt_001afe4c();
  }
  return;
}

/* FUN_00206520 @ 0x00206520   (est. skp0_sk_assert_ze_pair2)
 * Ghidra: void FUN_00206520(word_t param_1,word_t param_2)
 * Assert zero-pair variant: if either param is nonzero, panic (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_ze_pair2(word_t param_1,word_t param_2)
{

  if (param_1 != 0 || param_2 != 0) {
    skp0_rt_00348638(1);
    skp0_rt_00349de8();
                    /* WARNING: Subroutine does not return */
    skp0_rt_001afe4c();
  }
  return;
}

/* FUN_0020655c @ 0x0020655c   (est. skp0_sk_pair_store)
 * Ghidra: sk_fnptr * FUN_0020655c(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Pair store: writes a 4-word record (params into [0..3]) and returns the callback skp0_sk_pair_check_a (002065a4). Constructor/accessor pattern.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_fnptr * skp0_sk_pair_store(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t savx20;
  
  param_1[2] = param_4;
  param_1[3] = savx20;
  *param_1 = param_2;
  param_1[1] = param_3;
  skp0_rt_00106e3c();
  skp0_sk_assert_ze_pair((word_t)(0),(word_t)(0));
  return skp0_sk_pair_check_a;
}

/* FUN_002065a4 @ 0x002065a4   (est. skp0_sk_pair_check_a)
 * Ghidra: void FUN_002065a4(word_t *param_1)
 * Pair check: asserts both record words are zero via skp0_sk_assert_ze_pair2 (00206520).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_pair_check_a(word_t *param_1)
{

  skp0_sk_assert_ze_pair2((word_t)(*param_1),(word_t)(param_1[1]));
  return;
}

/* FUN_002065a8 @ 0x002065a8   (est. skp0_sk_pair_check_b)
 * Ghidra: void FUN_002065a8(word_t *param_1)
 * Pair check variant: asserts both record words zero.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_pair_check_b(word_t *param_1)
{

  skp0_sk_assert_ze_pair2((word_t)(*param_1),(word_t)(param_1[1]));
  return;
}

/* FUN_002065c0 @ 0x002065c0   (est. skp0_sk_assert_nz_pair)
 * Ghidra: word_t FUN_002065c0(word_t param_1,word_t param_2)
 * Assert nonzero-pair: panics if either param nonzero (noreturn), else returns 0.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_assert_nz_pair(word_t param_1,word_t param_2)
{

  if (param_1 != 0 || param_2 != 0) {
    skp0_rt_00348638(1);
    skp0_rt_00349de8();
                    /* WARNING: Subroutine does not return */
    skp0_rt_001afe4c();
  }
  return 0;
}

/* FUN_00206600 @ 0x00206600   (est. skp0_sk_assert_nz_triple)
 * Ghidra: sk_u128_t FUN_00206600()
 * Assert nonzero-triple: panics if param_1 or param_3 nonzero; returns sk_u128_t encoding (param_2 != 0) in the hi word.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t skp0_sk_assert_nz_triple(word_t param_1,word_t param_2,word_t param_3)
{

  if (param_1 != 0 || param_3 != 0) {
    skp0_rt_00348638(1);
    skp0_rt_00349de8();
                    /* WARNING: Subroutine does not return */
    skp0_rt_001afe4c();
  }
  return (sk_u128_t){ .lo=0, .hi=(word_t)(param_2 != 0) };
}

/* FUN_00206648 @ 0x00206648   (est. skp0_sk_assert_eq_case)
 * Ghidra: word_t FUN_00206648(word_t param_1,word_t param_2)
 * Assert equal-case: panics unless both params are zero (noreturn); returns 0 when both zero.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_assert_eq_case(word_t param_1,word_t param_2)
{

  if (param_1 == 0) {
    if (param_2 == 0) {
      return 0;
    }
    skp0_rt_003488bc(1);
    skp0_rt_0034f674();
  }
  else {
    skp0_rt_003488bc(1);
    skp0_rt_0034f674();
  }
  skp0_rt_00353b34();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_002066b4 @ 0x002066b4   (est. skp0_sk_assert_pair_eq)
 * Ghidra: void FUN_002066b4(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Assert pair-equal: computes a pair via skp0_rt_00319230/skp0_rt_00376820 and compares against saved regs; mismatch panics (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_pair_eq(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t tmp1;
  word_t tmp2;
  word_t savx19;
  word_t savx20;
  word_t loc40;
  word_t loc38;
  
  if (param_1 == 0) {
    tmp1 = skp0_rt_00350a28();
    tmp1 = skp0_rt_00319230(tmp1,param_4);
    tmp2 = skp0_rt_00350834();
    tmp2 = skp0_rt_00376820(tmp2,tmp1).lo;
    skp0_rt_00348e9c(tmp2,tmp2);
    skp0_rt_0019fa60(&loc40,tmp1);
    if ((savx20 == loc40) && (savx19 == loc38)) {
      return;
    }
    skp0_rt_003488bc(1);
    skp0_rt_0034f674();
  }
  else {
    skp0_rt_003488bc(1);
    skp0_rt_0034f674();
  }
  skp0_rt_00353b34();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_00206770 @ 0x00206770   (est. skp0_sk_node_validate)
 * Ghidra: void FUN_00206770(void)
 * Node validate: runtime prologue, runs a branch check (skp0_rt_0014ae44), on success validates a node via sk code path and returns the branch bit; ends with runtime call.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_node_validate(void)
{

  uint32_t tmp1;
  sk_fnptr fnp2;
  word_t tmp3;
  word_t tmpL4;
  word_t inpx3;
  word_t savx19;
  word_t savx21;
  sk_fnptr savx23;
  word_t savx30;
  
  skp0_rt_00084220();
  skp0_rt_00356c84();
  skp0_rt_0008409c();
  skp0_rt_0035125c(inpx3);
  fnp2 = (sk_fnptr)skp0_rt_0014ae44();
  skp0_rt_003502a8();
  tmp3 = (*fnp2)();
  if ((tmp3 & 1) == 0) {
    tmp1 = 0;
  }
  else {
    skp0_rt_00350798();
    tmpL4 = (*savx23)();
    skp0_rt_00351100(savx21 + *(int32_t *)(tmpL4 + 0x24),savx19 + *(int32_t *)(tmpL4 + 0x24));
    tmp1 = (*fnp2)();
    tmp1 = tmp1 & 1;
  }
  skp0_rt_00084234(tmp1,savx30);
  return;
}

/* FUN_00206818 @ 0x00206818   (est. skp0_sk_assert_pairs_eq)
 * Ghidra: void FUN_00206818(void)
 * Assert pairs-equal: builds two pairs via skp0_rt_00319230/skp0_rt_00376820/skp0_rt_0019fa60, compares to saved regs; mismatch panics (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_pairs_eq(void)
{

  word_t tmp1;
  word_t tmp2;
  word_t savx19;
  word_t savx20;
  word_t savx22;
  word_t savx24;
  word_t savx30;
  word_t inpstack_00000020;
  word_t inpstack_00000028;
  
  skp0_rt_00041138();
  skp0_rt_00077888();
  skp0_rt_00355d9c();
  skp0_rt_00353540();
  tmp1 = skp0_rt_00319230();
  tmp2 = skp0_rt_00350834();
  skp0_rt_00376820(tmp2,tmp1);
  skp0_rt_00348e9c();
  skp0_rt_0008e388(&sk_stack_00000020);
  skp0_rt_0019fa60();
  if ((savx24 == inpstack_00000020) && (savx22 == inpstack_00000028)) {
    skp0_rt_00348e9c();
    skp0_rt_0008e388(&sk_stack_00000020);
    skp0_rt_0019fa60();
    if ((savx20 == inpstack_00000020) && (savx19 == inpstack_00000028)) {
      skp0_rt_0035847c(savx30);
      return;
    }
    skp0_rt_003488bc(1);
    skp0_rt_0034f674();
  }
  else {
    skp0_rt_003488bc(1);
    skp0_rt_0034f674();
  }
  skp0_rt_00353b34();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c();
}

/* FUN_002068fc @ 0x002068fc   (est. skp0_sk_assert_empty3)
 * Ghidra: void FUN_002068fc(void)
 * Assert failure forwarding (noreturn): jumps to skp0_sk_assert_empty2 (00206494).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_empty3(void)
{

                    /* WARNING: Subroutine does not return */
  skp0_sk_assert_empty2();
}

/* FUN_00206900 @ 0x00206900   (est. skp0_sk_assert_empty4)
 * Ghidra: void FUN_00206900(void)
 * Assert failure forwarding (noreturn): jumps to skp0_sk_assert_empty2 (00206494).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_empty4(void)
{

                    /* WARNING: Subroutine does not return */
  skp0_sk_assert_empty2();
}

/* FUN_00206910 @ 0x00206910   (est. skp0_sk_pair_check_c)
 * Ghidra: void FUN_00206910(word_t param_1,word_t *param_2)
 * Pair check: asserts the two record words are zero via skp0_sk_assert_ze_pair2 (00206520).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_pair_check_c(word_t param_1,word_t *param_2)
{

  skp0_sk_assert_ze_pair2((word_t)(*param_2),(word_t)(param_2[1]));
  return;
}

/* FUN_00206928 @ 0x00206928   (est. skp0_sk_pair_store2)
 * Ghidra: sk_fnptr * FUN_00206928(word_t *param_1,word_t *param_2,word_t param_3)
 * Pair store variant: writes a 4-word record from a source pair and returns callback skp0_sk_pair_check_d (00206970).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_fnptr * skp0_sk_pair_store2(word_t *param_1,word_t *param_2,word_t param_3)
{

  word_t tmp1;
  word_t savx20;
  
  *param_1 = savx20;
  param_1[1] = param_3;
  tmp1 = param_2[1];
  param_1[2] = *param_2;
  param_1[3] = tmp1;
  skp0_sk_assert_ze_pair((word_t)(0),(word_t)(0));
  return skp0_sk_pair_check_d;
}

/* FUN_00206970 @ 0x00206970   (est. skp0_sk_pair_check_d)
 * Ghidra: void FUN_00206970(word_t param_1)
 * Pair check: asserts record words at +0x10/+0x18 are zero via skp0_sk_assert_ze_pair2.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_pair_check_d(word_t param_1)
{

  skp0_sk_assert_ze_pair2((word_t)(*(word_t *)(param_1 + 0x10)),(word_t)(*(word_t *)(param_1 + 0x18)));
  return;
}

/* FUN_00206974 @ 0x00206974   (est. skp0_sk_pair_check_e)
 * Ghidra: void FUN_00206974(word_t param_1)
 * Pair check variant: asserts record words at +0x10/+0x18 are zero.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_pair_check_e(word_t param_1)
{

  skp0_sk_assert_ze_pair2((word_t)(*(word_t *)(param_1 + 0x10)),(word_t)(*(word_t *)(param_1 + 0x18)));
  return;
}

/* FUN_0020698c @ 0x0020698c   (est. skp0_sk_assert_fmt_c)
 * Ghidra: void FUN_0020698c(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
 * Assertion helper: resolves diagnostic (skp0_g_004e9550) and calls skp0_rt_0019f1ec.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_fmt_c(word_t param_1,word_t param_2,word_t param_3,word_t param_4,
                 word_t param_5)
{

  word_t tmp1;
  
  tmp1 = skp0_rt_00376820(&skp0_g_004e9550,param_4).lo;
  skp0_rt_0019f1ec(param_1,param_2,param_3,param_4,tmp1,param_5);
  return;
}

/* FUN_00206a0c @ 0x00206a0c   (est. skp0_sk_assert_clear_a)
 * Ghidra: void FUN_00206a0c(void)
 * Assert-clear helper: runs skp0_sk_assert_fail2 (00206408), a runtime call, skp0_sk_assert_nz_pair (002065c0), then clears the object slot (*x19=0).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_clear_a(void)
{

  word_t *savx19;
  
  skp0_sk_assert_fail2();
  skp0_rt_00351124();
  skp0_sk_assert_nz_pair((word_t)(0),(word_t)(0));
  *savx19 = 0;
  return;
}

/* FUN_00206a10 @ 0x00206a10   (est. skp0_sk_assert_clear_b)
 * Ghidra: void FUN_00206a10(void)
 * Assert-clear helper variant: same as 00206a0c.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_clear_b(void)
{

  word_t *savx19;
  
  skp0_sk_assert_fail2();
  skp0_rt_00351124();
  skp0_sk_assert_nz_pair((word_t)(0),(word_t)(0));
  *savx19 = 0;
  return;
}

/* FUN_00206a44 @ 0x00206a44   (est. skp0_sk_assert_clear_c)
 * Ghidra: void FUN_00206a44(void)
 * Assert-clear helper variant: runtime call + skp0_sk_assert_nz_triple (00206600), clears slot and byte.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_clear_c(void)
{

  uint8_t outw1;
  word_t *savx19;
  
  skp0_rt_0034c434();
  skp0_sk_assert_nz_triple((word_t)(0),(word_t)(0),(word_t)(0));
  *savx19 = 0;
  *(uint8_t *)(savx19 + 1) = outw1;
  return;
}

/* FUN_00206a70 @ 0x00206a70   (est. skp0_sk_assert_clear_d)
 * Ghidra: word_t FUN_00206a70(word_t *param_1,word_t *param_2)
 * Assert-clear: asserts the two record words via skp0_sk_assert_eq_case (00206648), returns 0.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_assert_clear_d(word_t *param_1,word_t *param_2)
{

  skp0_sk_assert_eq_case((word_t)(*param_1),(word_t)(*param_2));
  return 0;
}

/* FUN_00206a74 @ 0x00206a74   (est. skp0_sk_assert_clear_e)
 * Ghidra: word_t FUN_00206a74(word_t *param_1,word_t *param_2)
 * Assert-clear variant: same as 00206a70.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_assert_clear_e(word_t *param_1,word_t *param_2)
{

  skp0_sk_assert_eq_case((word_t)(*param_1),(word_t)(*param_2));
  return 0;
}

/* FUN_00206a94 @ 0x00206a94   (est. skp0_sk_pair_alloc)
 * Ghidra: word_t * FUN_00206a94(word_t *param_1,word_t *param_2,word_t param_3)
 * Pair-node allocator (0x28 bytes, tag 0x23bc): initializes via skp0_sk_assert_both (002064d4) and returns metadata descriptor &skp0_g_003471a4.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t * skp0_sk_pair_alloc(word_t *param_1,word_t *param_2,word_t param_3)
{

  word_t tmpL1;
  word_t tmp2;
  
  tmpL1 = skp0_rt_0036a908(0x28,0x23bc);
  *param_1 = tmpL1;
  tmp2 = skp0_sk_assert_both(tmpL1,*param_2,*(word_t *)(param_3 + 0x10));
  *(word_t *)(tmpL1 + 0x20) = tmp2;
  return &skp0_g_003471a4;
}

/* FUN_00206b0c @ 0x00206b0c   (est. skp0_sk_assert_fmt_d)
 * Ghidra: void FUN_00206b0c(word_t param_1,word_t param_2)
 * Assertion helper: resolves diagnostic (skp0_g_004e9518) and calls skp0_rt_0019fa60 with a return site 0x6720e8.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_assert_fmt_d(word_t param_1,word_t param_2)
{

  word_t tmp1;
  
  tmp1 = skp0_rt_00376820(&skp0_g_004e9518,param_2).lo;
  skp0_rt_0019fa60(param_1,param_2,tmp1,0x6720e8);
  return;
}

/* FUN_00206bac @ 0x00206bac   (est. skp0_sk_slot_clear_a)
 * Ghidra: void FUN_00206bac(word_t param_1,word_t param_2,word_t param_3)
 * Slot clear: runtime preamble (skp0_sk_assert_fail 002063bc), builds via skp0_rt_00349830, dispatches, then clears a slot (offset via skp0_rt_0031b778).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_slot_clear_a(word_t param_1,word_t param_2,word_t param_3)
{

  word_t tmp1;
  word_t tmpL2;
  word_t outx8;
  word_t outx16;
  
  skp0_sk_assert_fail();
  skp0_rt_0034b430();
  tmp1 = skp0_rt_00349830();
  skp0_rt_00377824(tmp1,param_3);
  skp0_rt_00349530();
  (**(sk_fnptr *)(outx16 + 0x20))(outx8);
  skp0_rt_0034e70c();
  tmpL2 = skp0_rt_0031b778();
  *(word_t *)(outx8 + *(int32_t *)(tmpL2 + 0x24)) = 0;
  return;
}

/* FUN_00206bb0 @ 0x00206bb0   (est. skp0_sk_slot_clear_b)
 * Ghidra: void FUN_00206bb0(word_t param_1,word_t param_2,word_t param_3)
 * Slot clear variant: same structure as 00206bac.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_slot_clear_b(word_t param_1,word_t param_2,word_t param_3)
{

  word_t tmp1;
  word_t tmpL2;
  word_t outx8;
  word_t outx16;
  
  skp0_sk_assert_fail();
  skp0_rt_0034b430();
  tmp1 = skp0_rt_00349830();
  skp0_rt_00377824(tmp1,param_3);
  skp0_rt_00349530();
  (**(sk_fnptr *)(outx16 + 0x20))(outx8);
  skp0_rt_0034e70c();
  tmpL2 = skp0_rt_0031b778();
  *(word_t *)(outx8 + *(int32_t *)(tmpL2 + 0x24)) = 0;
  return;
}

/* FUN_00206c30 @ 0x00206c30   (est. skp0_sk_table_iter)
 * Ghidra: void FUN_00206c30()
 * Table iterator: runtime preamble, calls a callback (via savx19), resolves, then calls skp0_rt_00280bc4 (object walk) and finishes.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_table_iter()
{

  word_t tmp1;
  sk_fnptr outx9;
  sk_fnptr savx19;
  word_t savx30;
  
  skp0_rt_00084220();
  skp0_rt_00350b54();
  skp0_rt_0034f3b4(0);
  skp0_rt_00377824();
  skp0_rt_00351f10();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034aee4();
  (*savx19)();
  skp0_rt_00350b24();
  skp0_rt_00350560();
  (*outx9)();
  tmp1 = skp0_rt_003539d8();
  skp0_rt_00351584(tmp1,0);
  skp0_rt_00280bc4();
  skp0_rt_00084234(savx30);
  return;
}

/* FUN_00206cf8 @ 0x00206cf8   (est. skp0_sk_table_method)
 * Ghidra: void FUN_00206cf8(word_t param_1,word_t param_2)
 * Table method call: resolves a method pointer via skp0_rt_00027788 and calls it with object+0x10 and param_2 (unrecovered jumptable artifact).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_table_method(word_t param_1,word_t param_2)
{

  sk_fnptr UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = (sk_fnptr)skp0_rt_00027788(param_2);
                    /* WARNING: Could not recover jumptable at 0x00206d3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(*(word_t *)(param_1 + 0x10),param_2);
  return;
}

/* FUN_00206d88 @ 0x00206d88   (est. skp0_sk_table_lookup)
 * Ghidra: word_t FUN_00206d88(word_t param_1,word_t param_2,word_t param_3)
 * Table lookup: resolves object via skp0_rt_00377824/skp0_rt_00377bec, walks with skp0_rt_0014ae44, on miss reads a slot via skp0_rt_0032d3e0, else dispatches via skp0_rt_00027788. Returns the resolved value.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_table_lookup(word_t param_1,word_t param_2,word_t param_3)
{

  word_t tmpL1;
  sk_fnptr fnp2;
  word_t tmp3;
  word_t tmp4;
  word_t tmpL5;
  word_t outx8;
  word_t tmp6;
  uint8_t *ptu7;
  
  tmp6 = *(word_t *)(param_2 + 0x10);
  tmpL1 = skp0_rt_00377824(0,param_3,tmp6,&skp0_g_0060e208,&skp0_g_0060e230).lo;
  tmpL5 = *(word_t *)(tmpL1 + -8);
  (*skp0_g_00658c00)(*(word_t *)(tmpL5 + 0x40) + 0xfU & 0xfffffffffffffff0);
  ptu7 = &sk_stack_ffffffffffffffa0 + -outx8;
  fnp2 = (sk_fnptr)skp0_rt_00310924(param_3);
  (*fnp2)(ptu7,tmp6,param_3);
  skp0_rt_00377bec(param_3,tmp6,tmpL1,&skp0_g_0060e208,&skp0_g_0060e218);
  tmp3 = skp0_rt_00027754();
  fnp2 = (sk_fnptr)skp0_rt_0014ae44();
  tmp4 = (*fnp2)(param_1,ptu7,tmpL1,tmp3);
  (**(sk_fnptr *)(tmpL5 + 8))(ptu7,tmpL1);
  if ((tmp4 & 1) == 0) {
    tmpL1 = skp0_rt_0032d3e0(0,tmp6,param_3);
    tmp3 = *(word_t *)(param_1 + *(int32_t *)(tmpL1 + 0x24));
  }
  else {
    fnp2 = (sk_fnptr)skp0_rt_00027788(param_3);
    tmp3 = (*fnp2)(tmp6,param_3);
  }
  return tmp3;
}

/* FUN_00206f18 @ 0x00206f18   (est. skp0_sk_table_range)
 * Ghidra: word_t FUN_00206f18(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Table range check: walks two objects with skp0_rt_0014ae44, on both-miss computes a signed difference (skp0_rt_0032d3e0 slot), trapping on borrow overflow; else dispatches via skp0_rt_00310cd4. Returns the delta.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_table_range(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t tmpL1;
  sk_fnptr fnp2;
  word_t tmp3;
  sk_fnptr fnp4;
  word_t tmp5;
  word_t tmpL6;
  word_t outx8;
  word_t tmp7;
  sk_fnptr fnp8;
  uint8_t *ptu9;
  uint8_t astk80[8];
  word_t loc78;
  
  tmp7 = *(word_t *)(param_3 + 0x10);
  tmpL1 = skp0_rt_00377824(0,param_4,tmp7,&skp0_g_0060e208,&skp0_g_0060e230).lo;
  tmpL6 = *(word_t *)(tmpL1 + -8);
  (*skp0_g_00658c00)(*(word_t *)(tmpL6 + 0x40) + 0xfU & 0xfffffffffffffff0);
  ptu9 = astk80 + -outx8;
  fnp2 = (sk_fnptr)skp0_rt_00310924(param_4);
  (*fnp2)(ptu9,tmp7,param_4);
  skp0_rt_00377bec(param_4,tmp7,tmpL1,&skp0_g_0060e208,&skp0_g_0060e218);
  tmp3 = skp0_rt_00027754();
  fnp4 = (sk_fnptr)skp0_rt_0014ae44();
  loc78 = param_1;
  tmp5 = (*fnp4)(param_1,ptu9,tmpL1,tmp3);
  fnp8 = *(sk_fnptr *)(tmpL6 + 8);
  (*fnp8)(ptu9,tmpL1);
  if ((tmp5 & 1) == 0) {
    (*fnp2)(ptu9,tmp7,param_4);
    tmp5 = (*fnp4)(param_2,ptu9,tmpL1,tmp3);
    (*fnp8)(ptu9,tmpL1);
    if ((tmp5 & 1) == 0) {
      tmpL1 = skp0_rt_0032d3e0(0,tmp7,param_4);
      tmpL6 = *(word_t *)(param_2 + *(int32_t *)(tmpL1 + 0x24));
      tmpL1 = *(word_t *)(loc78 + *(int32_t *)(tmpL1 + 0x24));
      if (!skp0_SBORROW8(tmpL6,tmpL1)) {
        return tmpL6 - tmpL1;
      }
                    /* WARNING: Does not return */
      fnp2 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x20711c);
      (*fnp2)();
    }
  }
  fnp2 = (sk_fnptr)skp0_rt_00310cd4(param_4);
  tmpL1 = (*fnp2)(loc78,param_2,tmp7,param_4);
  return tmpL1;
}

/* FUN_0020711c @ 0x0020711c   (est. skp0_sk_table_insert1)
 * Ghidra: void FUN_0020711c(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Table insert (single): resolves object, walks via skp0_rt_00319658, reads slot via skp0_rt_0032d3e0, calls skp0_rt_00280bc4 with value+1; traps on carry overflow.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_table_insert1(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t tmpL1;
  sk_fnptr fnp2;
  word_t outx8;
  word_t tmp3;
  
  tmp3 = *(word_t *)(param_3 + 0x10);
  tmpL1 = skp0_rt_00377824(0,param_4,tmp3,&skp0_g_0060e208,&skp0_g_0060e230).lo;
  (*skp0_g_00658c00)(*(word_t *)(*(word_t *)(tmpL1 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  fnp2 = (sk_fnptr)skp0_rt_00319658(param_4);
  (*fnp2)(&sk_stack_ffffffffffffffc0 + -outx8,param_2,tmp3,param_4);
  tmpL1 = skp0_rt_0032d3e0(0,tmp3,param_4);
  tmpL1 = *(word_t *)(param_2 + *(int32_t *)(tmpL1 + 0x24));
  if (!skp0_SCARRY8(tmpL1,1)) {
    skp0_rt_00280bc4(param_1,&sk_stack_ffffffffffffffc0 + -outx8,tmpL1 + 1,tmp3,param_4,
                 &skp0_g_0060e208,&skp0_g_0060e230,skp0_rt_0032d3e0);
    return;
  }
                    /* WARNING: Does not return */
  fnp2 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x207234);
  (*fnp2)();
}

/* FUN_00207234 @ 0x00207234   (est. skp0_sk_table_insert_n)
 * Ghidra: void FUN_00207234(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5)
 * Table insert (n): resolves object, walks via skp0_rt_0031afcc, reads slot, adds param_3, calls skp0_rt_00280bc4; traps on carry overflow.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_table_insert_n(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5)
{

  word_t tmpL1;
  sk_fnptr fnp2;
  word_t outx8;
  word_t tmp3;
  
  tmp3 = *(word_t *)(param_4 + 0x10);
  tmpL1 = skp0_rt_00377824(0,param_5,tmp3,&skp0_g_0060e208,&skp0_g_0060e230).lo;
  (*skp0_g_00658c00)(*(word_t *)(*(word_t *)(tmpL1 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  fnp2 = (sk_fnptr)skp0_rt_0031afcc(param_5);
  (*fnp2)(&sk_stack_ffffffffffffffb0 + -outx8,param_2,param_3,tmp3,param_5);
  if (param_3 < 0) {
    tmpL1 = skp0_sk_table_lookup((word_t)(param_2),(word_t)(param_4),(word_t)(param_5));
  }
  else {
    tmpL1 = skp0_rt_0032d3e0(0,tmp3,param_5);
    tmpL1 = *(word_t *)(param_2 + *(int32_t *)(tmpL1 + 0x24));
  }
  if (!skp0_SCARRY8(tmpL1,param_3)) {
    skp0_rt_00280bc4(param_1,&sk_stack_ffffffffffffffb0 + -outx8,tmpL1 + param_3,tmp3,param_5,
                 &skp0_g_0060e208,&skp0_g_0060e230,skp0_rt_0032d3e0);
    return;
  }
                    /* WARNING: Does not return */
  fnp2 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x207378);
  (*fnp2)();
}

/* FUN_00207378 @ 0x00207378   (est. skp0_sk_table_update)
 * Ghidra: void FUN_00207378(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5,
                 word_t param_6)
 * Table update: builds two object frames, compares via skp0_rt_000839f8; on match dispatches and returns 1, else updates via skp0_rt_00280bc4 and returns 0.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_table_update(word_t param_1,word_t param_2,word_t param_3,word_t param_4,word_t param_5,
                 word_t param_6)
{

  int idx1;
  word_t tmpL2;
  word_t tmpL3;
  sk_fnptr fnp4;
  word_t tmpL5;
  word_t outx8;
  word_t tmpL6;
  word_t outx8_00;
  word_t tmp7;
  word_t tmp8;
  uint8_t *ptu9;
  uint8_t astk90[8];
  word_t loc88;
  word_t loc80;
  word_t loc78;
  
  tmp8 = *(word_t *)(param_5 + 0x10);
  loc88 = param_5;
  loc78 = param_4;
  tmpL2 = skp0_rt_00377824(0xff,param_6,tmp8,&skp0_g_0060e208,&skp0_g_0060e230).lo;
  tmpL3 = skp0_rt_00310d68(0,tmpL2);
  tmpL5 = *(word_t *)(tmpL3 + -8);
  (*skp0_g_00658c00)(*(word_t *)(tmpL5 + 0x40) + 0xfU & 0xfffffffffffffff0);
  ptu9 = astk90 + -outx8;
  tmpL6 = *(word_t *)(tmpL2 + -8);
  (*skp0_g_00658c00)(*(word_t *)(tmpL6 + 0x40) + 0xfU & 0xfffffffffffffff0);
  fnp4 = (sk_fnptr)skp0_rt_003192d8(param_6);
  loc80 = param_2;
  (*fnp4)(ptu9,param_2,param_3,loc78,tmp8,param_6);
  idx1 = skp0_rt_000839f8(ptu9,1,tmpL2);
  if (idx1 == 1) {
    (**(sk_fnptr *)(tmpL5 + 8))(ptu9,tmpL3);
    tmp7 = 1;
  }
  else {
    (**(sk_fnptr *)(tmpL6 + 0x20))((word_t)ptu9 - outx8_00,ptu9,tmpL2);
    if (param_3 < 0) {
      tmpL2 = skp0_sk_table_lookup((word_t)(loc80),(word_t)(loc88),(word_t)(param_6));
    }
    else {
      tmpL2 = skp0_rt_0032d3e0(0,tmp8,param_6);
      tmpL2 = *(word_t *)(loc80 + *(int32_t *)(tmpL2 + 0x24));
    }
    if (skp0_SCARRY8(tmpL2,param_3)) {
                    /* WARNING: Does not return */
      fnp4 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x2075e0);
      (*fnp4)();
    }
    skp0_rt_00280bc4(param_1,(word_t)ptu9 - outx8_00,tmpL2 + param_3,tmp8,param_6,&skp0_g_0060e208,
                 &skp0_g_0060e230,skp0_rt_0032d3e0);
    tmp7 = 0;
  }
  tmp8 = skp0_rt_0032d3e0(0,tmp8,param_6);
  skp0_rt_000839d8(param_1,tmp7,1,tmp8);
  return;
}

/* FUN_002075e0 @ 0x002075e0   (est. skp0_sk_index_lookup)
 * Ghidra: word_t FUN_002075e0(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Index lookup: walks object via skp0_rt_000277b8/skp0_rt_00310e20, on success resolves slot via skp0_rt_0032d3e0 and returns it; else panics (noreturn) with "Fatal error"/"Index out of bounds"/"Swift EnumeratedSequence" strings.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
word_t skp0_sk_index_lookup(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t tmpL1;
  sk_fnptr fnp2;
  word_t tmp3;
  word_t tmp4;
  sk_fnptr fnp5;
  word_t tmpL6;
  word_t tmpL7;
  word_t outx8;
  word_t tmp8;
  word_t tmp9;
  uint8_t *ptu10;
  sk_u128_t pair11;
  uint8_t astkb0[8];
  word_t stka8;
  uint32_t astka0 [4];
  uint8_t astk90[8];
  word_t loc88;
  uint8_t astk80 [32];
  
  tmp8 = *(word_t *)(param_3 + 0x10);
  loc88 = param_1;
  tmpL1 = skp0_rt_00377824(0,param_4,tmp8,&skp0_g_0060e208,&skp0_g_0060e230).lo;
  tmpL7 = *(word_t *)(tmpL1 + -8);
  (*skp0_g_00658c00)(*(word_t *)(tmpL7 + 0x40) + 0xfU & 0xfffffffffffffff0);
  tmpL6 = -outx8;
  ptu10 = astk90 + tmpL6;
  fnp2 = (sk_fnptr)skp0_rt_000277b8(param_4);
  (*fnp2)(ptu10,tmp8,param_4);
  tmp3 = skp0_rt_00377bec(param_4,tmp8,tmpL1,&skp0_g_0060e208,&skp0_g_0060e218);
  fnp2 = (sk_fnptr)skp0_rt_00310e20();
  tmp4 = (*fnp2)(ptu10,param_2,tmpL1,tmp3);
  fnp2 = *(sk_fnptr *)(tmpL7 + 8);
  (*fnp2)(ptu10,tmpL1);
  if ((tmp4 & 1) != 0) {
    fnp5 = (sk_fnptr)skp0_rt_00310924(param_4);
    (*fnp5)(ptu10,tmp8,param_4);
    fnp5 = (sk_fnptr)skp0_rt_0016186c(tmp3);
    tmp4 = (*fnp5)(param_2,ptu10,tmpL1,tmp3);
    (*fnp2)(ptu10,tmpL1);
    if ((tmp4 & 1) != 0) {
      tmpL6 = skp0_rt_0032d3e0(0,tmp8,param_4);
      tmp9 = *(word_t *)(param_2 + *(int32_t *)(tmpL6 + 0x24));
      fnp2 = (sk_fnptr)skp0_rt_000277e8(param_4);
      pair11 = (sk_u128_t){ .lo = (*fnp2)(astk80,param_2,tmp8,param_4), .hi = 0 };
      tmp3 = skp0_rt_00027754(param_4);
      tmpL6 = skp0_rt_00377824(0,tmp3,tmp8,&skp0_g_00611b24,&skp0_g_00611b34).lo;
      (**(sk_fnptr *)(*(word_t *)(tmpL6 + -8) + 0x10))(loc88,pair11.hi,tmpL6);
      ((sk_fnptr)pair11.lo)(astk80,0);
      return tmp9;
    }
  }
  *(uint32_t *)((word_t)astka0 + tmpL6) = 1;
  *(word_t *)((word_t)&stka8 + tmpL6) = 0xca;
  astkb0[tmpL6] = 2;
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afe4c(sk_str_Fatal_error,0xb,2,sk_str_Index_out_of_bounds,0x13,2,
               sk_str_Swift_EnumeratedSequence_swift,0x1e);
}

/* FUN_002078a8 @ 0x002078a8   (est. skp0_sk_index_clear_a)
 * Ghidra: void FUN_002078a8(word_t param_1,word_t param_2)
 * Index clear: calls skp0_sk_table_iter (00206c30) with resolved object and callback skp0_rt_000277b8.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_index_clear_a(word_t param_1,word_t param_2)
{

  skp0_sk_table_iter(param_1,*(word_t *)((param_2 & 0xfffffffffffffffe) - 8),skp0_rt_000277b8);
  return;
}

/* FUN_002078d8 @ 0x002078d8   (est. skp0_sk_index_clear_b)
 * Ghidra: void FUN_002078d8(word_t param_1,word_t param_2)
 * Index clear variant: skp0_sk_table_iter with callback skp0_rt_00310924.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_index_clear_b(word_t param_1,word_t param_2)
{

  skp0_sk_table_iter(param_1,*(word_t *)((param_2 & 0xfffffffffffffffe) - 8),skp0_rt_00310924);
  return;
}

/* FUN_002078dc @ 0x002078dc   (est. skp0_sk_index_clear_c)
 * Ghidra: void FUN_002078dc(word_t param_1,word_t param_2)
 * Index clear variant: skp0_sk_table_iter with callback skp0_rt_00310924.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_index_clear_c(word_t param_1,word_t param_2)
{

  skp0_sk_table_iter(param_1,*(word_t *)((param_2 & 0xfffffffffffffffe) - 8),skp0_rt_00310924);
  return;
}

/* FUN_0020790c @ 0x0020790c   (est. skp0_sk_table_alloc)
 * Ghidra: sk_u128_t FUN_0020790c(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Table allocator (0x40 bytes, tag 0xad9a): builds an object, allocates a child table, initializes via skp0_sk_table_alloc_node (00207ac8), stores, returns sk_u128_t with destructor skp0_sk_table_free (00207a70).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t skp0_sk_table_alloc(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t tmpL1;
  word_t tmp2;
  word_t tmpL3;
  word_t tmpL4;
  word_t *ptu5;
  word_t tmpL6;
  word_t tmp7;
  sk_u128_t pair8;
  
  tmpL1 = skp0_rt_0036a908(0x40,0xad9a);
  *param_1 = tmpL1;
  tmp7 = *(word_t *)((param_4 & 0xfffffffffffffffe) - 8);
  tmp2 = skp0_rt_00027754(tmp7);
  tmpL3 = skp0_rt_00377824(0xff,tmp2,*(word_t *)(param_3 + 0x10),&skp0_g_00611b24,&skp0_g_00611b34).lo;
  tmpL4 = skp0_rt_003722e4(0,0x677880,tmpL3,sk_str_offset_element,0).lo;
  *(word_t *)(tmpL1 + 0x20) = tmpL4;
  tmpL6 = *(word_t *)(tmpL4 + -8);
  *(word_t *)(tmpL1 + 0x28) = tmpL6;
  ptu5 = (word_t *)skp0_rt_0036a908(*(word_t *)(tmpL6 + 0x40),0xad9a);
  *(word_t **)(tmpL1 + 0x30) = ptu5;
  pair8 = skp0_sk_table_alloc_node((word_t)(tmpL1),(word_t)(param_2),(word_t)(param_3),(word_t)(tmp7));
  *(word_t *)(tmpL1 + 0x38) = pair8.lo;
  *ptu5 = pair8.hi;
  (**(sk_fnptr *)(*(word_t *)(tmpL3 + -8) + 0x10))
            ((word_t)ptu5 + (word_t)*(int32_t *)(tmpL4 + 0x30),param_3,tmpL3);
  pair8.hi = (word_t)ptu5;
  pair8.lo = (word_t)skp0_sk_table_free;
  return pair8;
}

/* FUN_00207a70 @ 0x00207a70   (est. skp0_sk_table_free)
 * Ghidra: void FUN_00207a70(void)
 * Table destructor: releases the table child and object (skp0_rt_0007c1c4, thunk skp0_rt_00012568).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_table_free(void)
{

  word_t tmp1;
  sk_fnptr outx8;
  sk_fnptr outx9;
  word_t savx20;
  
  skp0_rt_00358c74();
  (*outx9)();
  tmp1 = *(word_t *)(savx20 + 0x30);
  skp0_rt_0007c1c4(*(word_t *)(savx20 + 0x38));
  (*outx8)();
  skp0_rt_00012568(tmp1);
  skp0_rt_00012568();
  return;
}

/* FUN_00207ac8 @ 0x00207ac8   (est. skp0_sk_table_alloc_node)
 * Ghidra: sk_u128_t FUN_00207ac8(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
 * Table-node allocator: builds object, allocates a child slot (skp0_rt_0036a908), initializes via skp0_sk_index_lookup (002075e0), returns sk_u128_t with destructor skp0_sk_table_free_node (00207bd8).
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
sk_u128_t skp0_sk_table_alloc_node(word_t *param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t tmp1;
  word_t tmpL2;
  word_t *ptu3;
  word_t tmpL4;
  sk_u128_t pair5;
  
  tmp1 = skp0_rt_00027754(param_4);
  tmp1 = skp0_rt_00377824(0xff,tmp1,*(word_t *)(param_3 + 0x10),&skp0_g_00611b24,&skp0_g_00611b34).lo;
  tmpL2 = skp0_rt_003722e4(0,0x677880,tmp1,sk_str_offset_element,0).lo;
  *param_1 = tmpL2;
  tmpL4 = *(word_t *)(tmpL2 + -8);
  param_1[1] = tmpL4;
  ptu3 = (word_t *)skp0_rt_0036a908(*(word_t *)(tmpL4 + 0x40),&skp0_g_0000fc9d);
  param_1[2] = (word_t)ptu3;
  tmp1 = skp0_sk_index_lookup((word_t)((word_t)ptu3 + (word_t)*(int32_t *)(tmpL2 + 0x30)),(word_t)(param_2),(word_t)(param_3),(word_t)(param_4));
  *ptu3 = tmp1;
  pair5.hi = tmp1;
  pair5.lo = (word_t)skp0_sk_table_free_node;
  return pair5;
}

/* FUN_00207bd8 @ 0x00207bd8   (est. skp0_sk_table_free_node)
 * Ghidra: void FUN_00207bd8(word_t *param_1)
 * Table-node destructor: releases record (skp0_rt_00353c00), thunk release.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_table_free_node(word_t *param_1)
{

  word_t tmp1;
  sk_fnptr outx9;
  
  tmp1 = param_1[2];
  skp0_rt_00353c00(param_1[1],param_1,*param_1);
  (*outx9)();
  skp0_rt_00012568(tmp1);
  return;
}

/* FUN_00207ca0 @ 0x00207ca0   (est. skp0_sk_index_test)
 * Ghidra: uint32_t FUN_00207ca0(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Index test: builds object via skp0_rt_00377824/skp0_rt_00377bec and tests via skp0_rt_0014ae44, returning the branch bit & 1.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
uint32_t skp0_sk_index_test(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  uint32_t tmp1;
  word_t tmp2;
  word_t tmp3;
  sk_fnptr fnp4;
  
  tmp2 = skp0_rt_00377824(0,param_4,param_3,&skp0_g_0060e208,&skp0_g_0060e230).lo;
  skp0_rt_00377bec(param_4,param_3,tmp2,&skp0_g_0060e208,&skp0_g_0060e218);
  tmp3 = skp0_rt_00027754();
  fnp4 = (sk_fnptr)skp0_rt_0014ae44();
  tmp1 = (*fnp4)(param_1,param_2,tmp2,tmp3);
  return tmp1 & 1;
}

/* FUN_00207d4c @ 0x00207d4c   (est. skp0_sk_index_test2)
 * Ghidra: uint32_t FUN_00207d4c(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Index test variant: tests via skp0_rt_0016186c, returns bit & 1.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
uint32_t skp0_sk_index_test2(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  uint32_t tmp1;
  word_t tmp2;
  word_t tmp3;
  sk_fnptr fnp4;
  
  tmp2 = skp0_rt_00377824(0,param_4,param_3,&skp0_g_0060e208,&skp0_g_0060e230).lo;
  tmp3 = skp0_rt_00377bec(param_4,param_3,tmp2,&skp0_g_0060e208,&skp0_g_0060e218);
  fnp4 = (sk_fnptr)skp0_rt_0016186c();
  tmp1 = (*fnp4)(param_1,param_2,tmp2,tmp3);
  return tmp1 & 1;
}

/* FUN_00207e0c @ 0x00207e0c   (est. skp0_sk_index_decr)
 * Ghidra: void FUN_00207e0c(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
 * Index decrement: builds object, walks via skp0_rt_0031e104, reads slot, calls skp0_rt_00280bc4 with value-1; traps on borrow overflow (noreturn).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_index_decr(word_t param_1,word_t param_2,word_t param_3,word_t param_4)
{

  word_t tmp1;
  word_t tmp2;
  word_t tmpL3;
  sk_fnptr fnp4;
  word_t outx8;
  word_t tmp5;
  
  tmp1 = skp0_rt_00027754(param_4);
  tmp2 = skp0_rt_00027754();
  tmp5 = *(word_t *)(param_3 + 0x10);
  tmpL3 = skp0_rt_00377824(0,tmp2,tmp5,&skp0_g_0060e208,&skp0_g_0060e230).lo;
  (*skp0_g_00658c00)(*(word_t *)(*(word_t *)(tmpL3 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  fnp4 = (sk_fnptr)skp0_rt_0031e104(tmp1);
  (*fnp4)(&sk_stack_ffffffffffffffb0 + -outx8,param_2,tmp5,tmp1);
  tmpL3 = skp0_sk_table_lookup((word_t)(param_2),(word_t)(param_3),(word_t)(tmp2));
  if (!skp0_SBORROW8(tmpL3,1)) {
    skp0_rt_00280bc4(param_1,&sk_stack_ffffffffffffffb0 + -outx8,tmpL3 + -1,tmp5,tmp2,
                 &skp0_g_0060e208,&skp0_g_0060e230,skp0_rt_0032d3e0);
    return;
  }
                    /* WARNING: Does not return */
  fnp4 = (sk_fnptr)skp0_SoftwareBreakpoint(1,0x207f38);
  (*fnp4)();
}

/* FUN_00207f44 @ 0x00207f44   (est. skp0_sk_index_decr2)
 * Ghidra: void FUN_00207f44(word_t param_1,word_t param_2,word_t param_3)
 * Index decrement wrapper: builds object via skp0_rt_0032d3e0, calls skp0_sk_index_decr (00207e0c).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_index_decr2(word_t param_1,word_t param_2,word_t param_3)
{

  word_t tmp1;
  word_t tmpL2;
  word_t tmpL3;
  word_t outx8;
  word_t tmp4;
  word_t tmp5;
  uint8_t *ptu6;
  
  tmp4 = *(word_t *)((param_3 & 0xfffffffffffffffe) - 8);
  tmp5 = *(word_t *)(param_2 + 0x10);
  skp0_rt_00027754(tmp4);
  tmp1 = skp0_rt_00027754();
  tmpL2 = skp0_rt_0032d3e0(0,tmp5,tmp1);
  tmpL3 = *(word_t *)(tmpL2 + -8);
  (*skp0_g_00658c00)(*(word_t *)(tmpL3 + 0x40) + 0xfU & 0xfffffffffffffff0);
  ptu6 = &sk_stack_ffffffffffffffb0 + -outx8;
  (**(sk_fnptr *)(tmpL3 + 0x20))(ptu6,param_1,tmpL2);
  skp0_sk_index_decr((word_t)(param_1),(word_t)(ptu6),(word_t)(param_2),(word_t)(tmp4));
  (**(sk_fnptr *)(tmpL3 + 8))(ptu6,tmpL2);
  return;
}

/* FUN_002080a8 @ 0x002080a8   (est. skp0_sk_rt_wrap_a)
 * Ghidra: void FUN_002080a8(void)
 * Runtime wrap A: sequence of runtime calls ending in an indirect dispatch. Low-semantic-value shim.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_rt_wrap_a(void)
{

  sk_fnptr outx8;
  
  skp0_rt_0035921c();
  skp0_rt_00358174();
  skp0_rt_00027724();
  skp0_rt_000777d4();
  (*outx8)();
  return;
}

/* FUN_002080ec @ 0x002080ec   (est. skp0_sk_rt_wrap_b)
 * Ghidra: void FUN_002080ec(void)
 * Runtime wrap B: runtime call sequence + indirect dispatch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_rt_wrap_b(void)
{

  sk_fnptr outx8;
  
  skp0_rt_0035921c();
  skp0_rt_00358174();
  skp0_rt_00083a18();
  skp0_rt_000777d4();
  (*outx8)();
  return;
}

/* FUN_00208130 @ 0x00208130   (est. skp0_sk_rt_wrap_c)
 * Ghidra: void FUN_00208130(void)
 * Runtime wrap C: runtime call sequence + indirect dispatch.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_rt_wrap_c(void)
{

  sk_fnptr outx8;
  
  skp0_rt_0035921c();
  skp0_rt_00358174();
  skp0_rt_0008da6c();
  skp0_rt_000777d4();
  (*outx8)();
  return;
}

/* FUN_00208174 @ 0x00208174   (est. skp0_sk_boot_cold)
 * Ghidra: void FUN_00208174(void)
 * Boot cold path: resolves boot configuration (skp0_rt_00358374), selects an entry path (skp0_rt_003a25d4 / skp0_rt_002a4c98) based on a branch, dispatches skp0_sk_desc_recurse (002060d4), then runs a runtime finalize and panics (noreturn via skp0_rt_001afa84). Decompiler lost several unreachable blocks; reconstructed from the recovered flow.
 * Confidence: low
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_boot_cold(void)
{

  word_t tmp1;
  uint8_t inpZR;
  word_t tmp2;
  word_t tmp3;
  word_t tmp4;
  word_t tmp5;
  word_t outx8;
  word_t outx8_00;
  word_t outx8_01;
  word_t savx23;
  word_t tmp6;
  sk_u128_t pair7;
  sk_u128_t pair8;
  word_t loc78;
  word_t loc70;
  word_t stk68;
  word_t loc60;
  word_t tmp9;
  
  tmp2 = skp0_rt_00358374();
  pair7 = skp0_rt_0006e778(0x1d);
  tmp9 = pair7.hi;
  loc60 = pair7.lo;
  tmp3 = skp0_rt_0034f064();
  if ((outx8 == 0) && (((tmp3 & (tmp9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    tmp6 = 0x2081dc;
    pair7 = skp0_rt_003a25d4(tmp9);
    loc60 = 0xd00000000000001b;
    tmp9 = 0x80000000005cf600;
  }
  else {
    inpZR = 1;
    tmp6 = 0x208234;
    pair7 = skp0_rt_002a4c98(0xd00000000000001b,0x80000000005cf600,0,0x1b);
  }
  tmp5 = loc60;
  loc78 = 0;
  loc70 = 0xe000000000000000;
  stk68 = tmp2;
  skp0_rt_0034a210(pair7.lo,pair7.hi,tmp6);
  pair7 = skp0_rt_00002534();
  tmp2 = skp0_rt_00353d64(0x208270,pair7.hi,pair7.lo);
  skp0_rt_0034895c(tmp2);
  skp0_sk_desc_recurse(&stk68,&loc78);
  tmp1 = loc70;
  tmp3 = loc78;
  pair7 = skp0_rt_0034a274(0x208298);
  tmp4 = pair7.lo;
  if ((outx8_00 == 0) && (((tmp5 & (tmp9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    tmp2 = 0x2082bc;
    skp0_rt_003a25d4(tmp9);
    loc60 = tmp3;
    savx23 = tmp1;
  }
  else {
    if ((tmp9 >> 0x3d & 1) == 0) {
      pair7 = (sk_u128_t){ .lo = skp0_rt_0034ced8(tmp3 & 0xffffffffffff,tmp4), .hi = 0 };
      tmp4 = pair7.lo;
    }
    else if ((tmp1 >> 0x3d & 1) != 0) {
      tmp5 = tmp4;
      pair7 = skp0_rt_0007c1c4();
      pair8 = skp0_rt_0034b89c(pair7.lo,pair7.hi,tmp3);
      pair7.hi = pair8.hi;
      pair7.lo = tmp5;
      tmp4 = pair8.lo;
      if (!(bool)inpZR) {
        skp0_rt_00354f1c(tmp4,pair8.hi,tmp5);
        skp0_rt_003a25d4(tmp9);
        tmp2 = 0x208408;
        skp0_rt_003a25d4(tmp1);
        loc60 = tmp5;
        goto L_00208330;
      }
    }
    pair7 = (sk_u128_t){ .lo = skp0_rt_00100efc(tmp4,pair7.hi,pair7.lo), .hi = 0 };
    skp0_rt_002a4c98(pair7.lo,pair7.hi,0);
    tmp2 = 0x20832c;
    skp0_rt_003a25d4(tmp1);
    savx23 = tmp9;
  }
L_00208330:
  tmp3 = loc60;
  pair7 = skp0_rt_0034f98c(loc60 & 0xffffffffffff,tmp2);
  tmp2 = pair7.lo;
  if ((outx8_01 == 0) && (((tmp3 & (savx23 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    tmp6 = 0x208354;
    tmp2 = skp0_rt_003a25d4(savx23).lo;
  }
  else {
    if ((savx23 >> 0x3d & 1) != 0) {
      pair7 = (sk_u128_t){ .lo = skp0_rt_00100efc(tmp2,pair7.hi,tmp2), .hi = 0 };
      pair7 = skp0_rt_0034b7c8(pair7.lo,pair7.hi,0,0xe000000000000000);
      if (!(bool)inpZR) {
        skp0_rt_00351a50(pair7.lo,pair7.hi,tmp2);
        tmp6 = 0x2083ac;
        tmp2 = skp0_rt_003a25d4(savx23).lo;
        goto L_002083ac;
      }
    }
    tmp6 = 0x208390;
    tmp2 = skp0_rt_00353ad8();
  }
L_002083ac:
  skp0_rt_00350d94(0xfe,tmp2,tmp6);
  skp0_rt_0006f768();
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afa84();
}

/* FUN_00208418 @ 0x00208418   (est. skp0_sk_boot_cpu)
 * Ghidra: void FUN_00208418()
 * Boot per-CPU path: runtime check (skp0_rt_00361528), on error panics; resolves via skp0_rt_002a218c and branches to one of two teardown continuations.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_boot_cpu()
{

  word_t tmpL1;
  word_t outx1;
  
  skp0_rt_00361528();
  if (outx1 < 0) {
    skp0_rt_0034846c();
                    /* WARNING: Subroutine does not return */
    skp0_rt_001afe4c();
  }
  skp0_rt_00351e08();
  tmpL1 = skp0_rt_002a218c();
  if (-1 < tmpL1) {
    skp0_rt_0034f9fc();
    skp0_rt_002a2698();
    return;
  }
  skp0_rt_0034a8cc();
  skp0_rt_002a2748();
  return;
}

/* FUN_00208478 @ 0x00208478   (est. skp0_sk_dispatch_mux)
 * Ghidra: void FUN_00208478(word_t param_1,word_t param_2,word_t param_3)
 * Dispatch mux: resolves two runtime functions, runs a branch check, dispatches one of two continuations, returns via epilogue.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_dispatch_mux(word_t param_1,word_t param_2,word_t param_3)
{

  word_t tmp1;
  word_t tmp2;
  word_t tmp3;
  word_t outx1;
  sk_fnptr outx8;
  sk_fnptr outx8_00;
  sk_fnptr outx9;
  sk_fnptr outx9_00;
  word_t outx16;
  word_t loc8;
  
  skp0_rt_00084220();
  tmp1 = skp0_rt_00353e88();
  tmp2 = skp0_rt_0034a980();
  skp0_rt_00377824(tmp2,param_3,tmp1);
  skp0_rt_00348e18();
  skp0_rt_0007c1a4();
  (*skp0_g_00658c00)();
  skp0_rt_0034cff4();
  skp0_rt_00351bec();
  skp0_rt_0034acd0();
  tmp3 = (*outx8)();
  if ((tmp3 & 1) == 0) {
    skp0_rt_0007b384();
    skp0_rt_00351f7c();
    skp0_rt_00351384();
    (*outx9_00)();
    skp0_rt_000e710c();
  }
  else {
    skp0_rt_0007b384();
    skp0_rt_00351f7c();
    skp0_rt_00351384();
    (*outx9)();
    skp0_rt_0001df60();
    skp0_rt_003516fc();
  }
  skp0_rt_00084180(&loc8);
  skp0_rt_001e2460();
  skp0_rt_00084180(*(word_t *)(outx16 + 8));
  (*outx8_00)();
  skp0_rt_00084234(loc8,outx1);
  return;
}

/* FUN_002085a4 @ 0x002085a4   (est. skp0_sk_abstract_method)
 * Ghidra: void FUN_002085a4(void)
 * Abstract method trap (noreturn): logs "Method must be overridden" (sk_str_Method_must_be_overridden) then "Fatal error" and panics via skp0_rt_001afa84. Base-class virtual that concrete types must override.
 * Confidence: high
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_abstract_method(void)
{

  skp0_rt_0035ac70(sk_str_Method_must_be_overridden);
  skp0_rt_0006f768(sk_str_Fatal_error);
                    /* WARNING: Subroutine does not return */
  skp0_rt_001afa84();
}

/* FUN_002085fc @ 0x002085fc   (est. skp0_sk_vt_init)
 * Ghidra: void FUN_002085fc(void)
 * Vtable init: runtime prologue, then calls skp0_sk_vt_install (00208628).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_init(void)
{

  skp0_rt_0034d7a8();
  skp0_rt_0031b930();
  skp0_rt_00351d18();
  skp0_sk_vt_install((word_t)(0));
  return;
}

/* FUN_00208628 @ 0x00208628   (est. skp0_sk_vt_install)
 * Ghidra: void FUN_00208628()
 * Vtable install: calls skp0_rt_00210bd4 with the hook skp0_sk_vt_hook_c (00208760).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_install(word_t param_1)
{

  skp0_rt_00210bd4(param_1,skp0_sk_vt_hook_a);
  return;
}

/* FUN_00208640 @ 0x00208640   (est. skp0_sk_vt_setup)
 * Ghidra: void FUN_00208640(void)
 * Vtable setup: builds a descriptor via skp0_rt_0031b948/skp0_rt_0031b930 and calls skp0_sk_vt_install (00208628).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_setup(void)
{

  word_t tmp1;
  
  skp0_rt_003504d0();
  skp0_rt_003537d4();
  tmp1 = skp0_rt_0031b948();
  tmp1 = skp0_rt_0031b930(0,tmp1,0x66c210);
  skp0_sk_vt_install((word_t)(&sk_stack_ffffffffffffffd0));
  return;
}

/* FUN_002086ac @ 0x002086ac   (est. skp0_sk_vt_teardown)
 * Ghidra: void FUN_002086ac(void)
 * Vtable teardown: runtime calls to release the vtable object.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_teardown(void)
{

  skp0_rt_003503c0();
  skp0_rt_0036b270();
  skp0_rt_0007c1c4();
  return;
}

/* FUN_002086d4 @ 0x002086d4   (est. skp0_sk_vt_call)
 * Ghidra: void FUN_002086d4(sk_fnptr *param_1)
 * Vtable call: invokes the passed function pointer.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_call(sk_fnptr *param_1)
{

  (*param_1)();
  return;
}

/* FUN_00208704 @ 0x00208704   (est. skp0_sk_vt_abstract_a)
 * Ghidra: void FUN_00208704(void)
 * Abstract vtable method A: enters skp0_rt_00357cc8, calls skp0_sk_abstract_method (002085a4, noreturn), then dispatches +0x48.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_abstract_a(void)
{

  word_t *savx20;
  
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  (**(sk_fnptr *)(*(word_t *)*savx20 + 0x48))();
  return;
}

/* FUN_00208708 @ 0x00208708   (est. skp0_sk_vt_abstract_b)
 * Ghidra: void FUN_00208708(void)
 * Abstract vtable method B: same pattern as 00208704.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_abstract_b(void)
{

  word_t *savx20;
  
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  (**(sk_fnptr *)(*(word_t *)*savx20 + 0x48))();
  return;
}

/* FUN_00208760 @ 0x00208760   (est. skp0_sk_vt_hook_a)
 * Ghidra: void FUN_00208760(word_t param_1)
 * Vtable hook: builds a frame via skp0_rt_0007c0c4, calls runtime, dispatches +0x20.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_hook_a(word_t param_1)
{

  word_t outx8;
  word_t outx9;
  word_t outx16;
  word_t savx20;
  sk_u128_t pair1;
  
  pair1 = skp0_rt_0007c0c4(param_1,param_1);
  skp0_rt_0034b07c(pair1.lo,pair1.hi,*(word_t *)(outx8 + 0x50));
  (**(sk_fnptr *)(outx16 + 0x20))(savx20 + outx9);
  return;
}

/* FUN_00208764 @ 0x00208764   (est. skp0_sk_vt_hook_b)
 * Ghidra: void FUN_00208764(word_t param_1)
 * Vtable hook variant: same as 00208760.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_hook_b(word_t param_1)
{

  word_t outx8;
  word_t outx9;
  word_t outx16;
  word_t savx20;
  sk_u128_t pair1;
  
  pair1 = skp0_rt_0007c0c4(param_1,param_1);
  skp0_rt_0034b07c(pair1.lo,pair1.hi,*(word_t *)(outx8 + 0x50));
  (**(sk_fnptr *)(outx16 + 0x20))(savx20 + outx9);
  return;
}

/* FUN_002087bc @ 0x002087bc   (est. skp0_sk_vt_hook_c)
 * Ghidra: void FUN_002087bc(void)
 * Vtable hook: builds frame, indirect dispatch (unrecovered jumptable artifact) via +0x50/+0x60.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_hook_c(void)
{

  word_t outx8;
  word_t outx16;
  word_t savx20;
  
  skp0_rt_0007c0c4();
                    /* WARNING: Could not recover jumptable at 0x00208810. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(sk_fnptr *)(*(word_t *)(*(word_t *)(outx8 + 0x50) + -8) + 8))
            (savx20 + *(word_t *)(outx16 + 0x60));
  return;
}

/* FUN_00208818 @ 0x00208818   (est. skp0_sk_vt_hook_d)
 * Ghidra: void FUN_00208818(void)
 * Vtable hook: builds frame via skp0_rt_0007c0c4, calls runtime, dispatches +0x50.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_hook_d(void)
{

  word_t tmp1;
  word_t outx8;
  word_t outx9;
  word_t outx16;
  word_t savx20;
  
  tmp1 = skp0_rt_0007c0c4().lo;
  skp0_rt_0034ece8(tmp1,*(word_t *)(outx8 + 0x50));
  (**(sk_fnptr *)(outx16 + 8))(savx20 + outx9);
  return;
}

/* FUN_00208884 @ 0x00208884   (est. skp0_sk_vt_hook_e)
 * Ghidra: void FUN_00208884(word_t param_1)
 * Vtable hook: runtime preamble, loads +0x58, resolves, indirect call.
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_vt_hook_e(word_t param_1)
{

  sk_fnptr outx9;
  word_t outx16;
  word_t savx21;
  word_t tmp1;
  
  skp0_rt_0034ecb8();
  tmp1 = *(word_t *)(savx21 + 0x58);
  skp0_rt_00354474(tmp1);
  skp0_rt_00351d9c();
  (*outx9)(param_1,*(word_t *)(outx16 + 0x50),tmp1);
  return;
}

/* FUN_002089ec @ 0x002089ec   (est. skp0_sk_dtor_pure_a)
 * Ghidra: void FUN_002089ec(void)
 * Pure-destructor stub A: emits 14 abstract-method traps then releases object +0x10/+0x20. Base-class destructor (must be overridden).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_dtor_pure_a(void)
{

  word_t savx20;
  
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x10));
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x20));
  return;
}

/* FUN_002089f0 @ 0x002089f0   (est. skp0_sk_dtor_pure_b)
 * Ghidra: void FUN_002089f0(void)
 * Pure-destructor stub B: same as A (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_dtor_pure_b(void)
{

  word_t savx20;
  
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x10));
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x20));
  return;
}

/* FUN_00208a10 @ 0x00208a10   (est. skp0_sk_dtor_pure_c)
 * Ghidra: void FUN_00208a10(void)
 * Pure-destructor stub C: same (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_dtor_pure_c(void)
{

  word_t savx20;
  
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x10));
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x20));
  return;
}

/* FUN_00208a30 @ 0x00208a30   (est. skp0_sk_dtor_pure_d)
 * Ghidra: void FUN_00208a30(void)
 * Pure-destructor stub D: same (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_dtor_pure_d(void)
{

  word_t savx20;
  
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x10));
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x20));
  return;
}

/* FUN_00208a50 @ 0x00208a50   (est. skp0_sk_dtor_pure_e)
 * Ghidra: void FUN_00208a50(void)
 * Pure-destructor stub E: same (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_dtor_pure_e(void)
{

  word_t savx20;
  
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x10));
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x20));
  return;
}

/* FUN_00208a70 @ 0x00208a70   (est. skp0_sk_dtor_pure_f)
 * Ghidra: void FUN_00208a70(void)
 * Pure-destructor stub F: same (14 traps + release).
 * Confidence: medium
 * Notes: mechanical decompiler transcription; out-of-scope runtime calls are rt_<addr> externs.
 *   Check for skp0_SoftwareBreakpoint traps / unrecovered-jumptable artifacts in the body. */
void skp0_sk_dtor_pure_f(void)
{

  word_t savx20;
  
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_00357cc8();
  skp0_sk_abstract_method();
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x10));
  skp0_rt_0036b118(*(word_t *)(savx20 + 0x20));
  return;
}
