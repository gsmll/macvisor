/* Recreated from cl4_kernel.raw (cL4 Secure Kernel, arm64e, image base 0) —
 * the cL4 microkernel (GL1), "cL4 (679.100.61)", seL4-derived.
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * All names are estimates unless string/header matched.
 * Slice 09: 0x3442a8-0x348034. This region is the syscall/exception-entry
 * dispatch area: thin per-syscall wrapper stubs that read the saved trap
 * register frame (unaff_x20 = sk_trap) and forward to shared cL4 kernel
 * handlers (IPC, cap, notify, sched) reconstructed in sibling slices. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"
#include "sk_region_syscalls.h"

/* ------------------------------------------------------------------ *
 * Shared 16-byte return pair (Ghidra `undefined1 auVar[16]` returned via
 * x0/x1). lo = _0_8_, hi = _8_8_.
 * ------------------------------------------------------------------ */
typedef struct sk_pair {
    und8_t lo;
    und8_t hi;
} sk_pair_t;

/* ------------------------------------------------------------------ *
 * Syscall trap frame. unaff_x20 in the decompiles is the saved register
 * frame of the current trap/syscall; x19 (sk_ctx) is the companion context
 * register. sk_trap is set by the syscall-entry trampoline before the
 * dispatch wrappers run.
 * ------------------------------------------------------------------ */
extern und8_t *sk_trap;   /* unaff_x20 */
extern und8_t *sk_ctx;    /* unaff_x19 */

/* Byte / half / word / dword frame field readers at byte offset `off`. */
static inline und8_t frq(unsigned long off){ return *(und8_t*)((char*)sk_trap + off); }
static inline und4_t frw(unsigned long off){ return *(und4_t*)((char*)sk_trap + off); }
static inline und1_t frb(unsigned long off){ return *(und1_t*)((char*)sk_trap + off); }
static inline long   frl(unsigned long off){ return *(long*)((char*)sk_trap + off); }
/* Companion context (unaff_x19 / extraout_x16) field readers. */
static inline und8_t crq(unsigned long off){ return *(und8_t*)((char*)sk_ctx + off); }
static inline und4_t crw(unsigned long off){ return *(und4_t*)((char*)sk_ctx + off); }
static inline und1_t crb(unsigned long off){ return *(und1_t*)((char*)sk_ctx + off); }

/* ------------------------------------------------------------------ *
 * Out-of-slice callees. Bodies reconstructed by the range worker that owns
 * each address; the exact Ghidra FUN_ name is in the trailing comment.
 * Signatures are permissive (up to 8 und8_t args); the real call sites pass
 * pointers/caps/words which convert to und8_t. sk_pair_t returners produce
 * a 16-byte pair in x0/x1.
 * ------------------------------------------------------------------ */

/* BEGIN_EXTERN_BLOCK */
extern void sk_f_00002534(und8_t a1, ...);  /* FUN_00002534 */
extern void sk_scope_drop(und8_t a1, ...);  /* FUN_000026E8 */
extern void sk_f_00012568(und8_t a1, ...);  /* FUN_00012568 */
extern void sk_f_00077550(und8_t a1, ...);  /* FUN_00077550 */
extern und8_t sk_f_00077560(und8_t a1, ...);  /* FUN_00077560 */
extern void sk_f_00077570(und8_t a1, ...);  /* FUN_00077570 */
extern void sk_f_00077580(und8_t a1, ...);  /* FUN_00077580 */
extern void sk_f_00077624(und8_t a1, ...);  /* FUN_00077624 */
extern void sk_f_00077708(und8_t a1, ...);  /* FUN_00077708 */
extern void sk_f_000839d8(und8_t a1, ...);  /* FUN_000839D8 */
extern void sk_f_0008409c(und8_t a1, ...);  /* FUN_0008409C */
extern void sk_f_00084180(und8_t a1, ...);  /* FUN_00084180 */
extern void sk_f_000841a0(und8_t a1, ...);  /* FUN_000841A0 */
extern void sk_f_0008e500(und8_t a1, ...);  /* FUN_0008E500 */
extern void sk_f_0008e518(und8_t a1, ...);  /* FUN_0008E518 */
extern void sk_f_000a6f88(und8_t a1, ...);  /* FUN_000A6F88 */
extern und8_t sk_f_000b4594(und8_t a1, ...);  /* FUN_000B4594 */
extern void sk_f_000b45b0(und8_t a1, ...);  /* FUN_000B45B0 */
extern void sk_f_000dbd0c(und8_t a1, ...);  /* FUN_000DBD0C */
extern void sk_f_00106e3c(und8_t a1, ...);  /* FUN_00106E3C */
extern void sk_obj_copy(und8_t a1, ...);  /* FUN_00117CC4 */
extern void sk_f_00154148(und8_t a1, ...);  /* FUN_00154148 */
extern und8_t sk_f_0019c3a4(und8_t a1, ...);  /* FUN_0019C3A4 */
extern void sk_f_0019ccec(und8_t a1, ...);  /* FUN_0019CCEC */
extern void sk_f_0019d498(und8_t a1, ...);  /* FUN_0019D498 */
extern void sk_f_0019d6d0(und8_t a1, ...);  /* FUN_0019D6D0 */
extern void sk_f_0019f63c(und8_t a1, ...);  /* FUN_0019F63C */
extern void sk_f_0019f658(und8_t a1, ...);  /* FUN_0019F658 */
extern und8_t sk_f_001a0d1c(und8_t a1, ...);  /* FUN_001A0D1C */
extern sk_pair_t sk_f_001a26e0(und8_t a1, ...);  /* FUN_001A26E0 */
extern void sk_f_001a79e0(und8_t a1, ...);  /* FUN_001A79E0 */
extern void sk_f_001aa2fc(und8_t a1, ...);  /* FUN_001AA2FC */
extern void sk_f_001aa318(und8_t a1, ...);  /* FUN_001AA318 */
extern void sk_f_001afdbc(und8_t a1, ...);  /* FUN_001AFDBC */
extern void sk_fault(und8_t a1, ...) __attribute__((noreturn));  /* FUN_001AFE4C */
extern void sk_f_001b5894(und8_t a1, ...);  /* FUN_001B5894 */
extern void sk_f_001b58b0(und8_t a1, ...);  /* FUN_001B58B0 */
extern void sk_f_001bf9b0(und8_t a1, ...);  /* FUN_001BF9B0 */
extern void sk_f_001d1e00(und8_t a1, ...);  /* FUN_001D1E00 */
extern void sk_f_001d1e18(und8_t a1, ...);  /* FUN_001D1E18 */
extern void sk_f_001dccb4(und8_t a1, ...);  /* FUN_001DCCB4 */
extern void sk_f_001dccd0(und8_t a1, ...);  /* FUN_001DCCD0 */
extern void sk_f_001df5ec(und8_t a1, ...);  /* FUN_001DF5EC */
extern void sk_f_001df7dc(und8_t a1, ...);  /* FUN_001DF7DC */
extern void sk_f_001e4a30(und8_t a1, ...);  /* FUN_001E4A30 */
extern void sk_f_001e4a48(und8_t a1, ...);  /* FUN_001E4A48 */
extern und8_t sk_f_001ee0fc(und8_t a1, ...);  /* FUN_001EE0FC */
extern void sk_f_001eed8c(und8_t a1, ...);  /* FUN_001EED8C */
extern void sk_f_001f99f4(und8_t a1, ...);  /* FUN_001F99F4 */
extern void sk_f_00212d50(und8_t a1, ...);  /* FUN_00212D50 */
extern void sk_f_00212e74(und8_t a1, ...);  /* FUN_00212E74 */
extern void sk_f_00212e8c(und8_t a1, ...);  /* FUN_00212E8C */
extern void sk_f_00212ea4(und8_t a1, ...);  /* FUN_00212EA4 */
extern void sk_f_00212ec8(und8_t a1, ...);  /* FUN_00212EC8 */
extern void sk_f_002298d4(und8_t a1, ...);  /* FUN_002298D4 */
extern void sk_f_0022f500(void);  /* FUN_0022F500 (fn-pointer value) */
extern void sk_f_002364dc(und8_t a1, ...);  /* FUN_002364DC */
extern void sk_f_00238e1c(und8_t a1, ...);  /* FUN_00238E1C */
extern und8_t sk_yield(und8_t a1, ...);  /* FUN_00248A34 */
extern void sk_f_00249a64(und8_t a1, ...);  /* FUN_00249A64 */
extern und8_t sk_f_00249e20(und8_t a1, ...);  /* FUN_00249E20 */
extern void sk_f_0024a5c0(und8_t a1, ...);  /* FUN_0024A5C0 */
extern void sk_f_0024be2c(und8_t a1, ...);  /* FUN_0024BE2C */
extern void sk_f_0024c0d0(und8_t a1, ...);  /* FUN_0024C0D0 */
extern void sk_f_0024c158(und8_t a1, ...);  /* FUN_0024C158 */
extern void sk_f_0024c250(und8_t a1, ...);  /* FUN_0024C250 */
extern void sk_f_0024c7bc(und8_t a1, ...);  /* FUN_0024C7BC */
extern void sk_f_0024d788(und8_t a1, ...);  /* FUN_0024D788 */
extern void sk_f_00251f6c(und8_t a1, ...);  /* FUN_00251F6C */
extern void sk_f_00255e68(und8_t a1, ...);  /* FUN_00255E68 */
extern void sk_f_00259b64(und8_t a1, ...);  /* FUN_00259B64 */
extern void sk_f_0025e85c(void);  /* FUN_0025E85C (fn-pointer value) */
extern void sk_f_0025ecb8(void);  /* FUN_0025ECB8 (fn-pointer value) */
extern void sk_f_0025f2e4(void);  /* FUN_0025F2E4 (fn-pointer value) */
extern void sk_f_0026001c(und8_t a1, ...);  /* FUN_0026001C */
extern void sk_f_00260690(und8_t a1, ...);  /* FUN_00260690 */
extern void sk_f_00267820(und8_t a1, ...);  /* FUN_00267820 */
extern void sk_f_0026a2ac(und8_t a1, ...);  /* FUN_0026A2AC */
extern void sk_f_0026c2a0(und8_t a1, ...);  /* FUN_0026C2A0 */
extern void sk_f_0026f824(und8_t a1, ...);  /* FUN_0026F824 */
extern void sk_f_00270ae4(und8_t a1, ...);  /* FUN_00270AE4 */
extern sk_pair_t sk_f_0027c7a0(und8_t a1, ...);  /* FUN_0027C7A0 */
extern void sk_f_0027c85c(und8_t a1, ...);  /* FUN_0027C85C */
extern void sk_f_002871b4(und8_t a1, ...);  /* FUN_002871B4 */
extern void sk_f_002a4148(und8_t a1, ...);  /* FUN_002A4148 */
extern und8_t sk_f_002ab5bc(und8_t a1, ...);  /* FUN_002AB5BC */
extern void sk_f_00310f1c(und8_t a1, ...);  /* FUN_00310F1C */
extern void sk_f_00319440(und8_t a1, ...);  /* FUN_00319440 */
extern void sk_f_003194bc(und8_t a1, ...);  /* FUN_003194BC */
extern void sk_f_00319808(und8_t a1, ...);  /* FUN_00319808 */
extern und8_t sk_f_003198cc(und8_t a1, ...);  /* FUN_003198CC */
extern und8_t sk_f_00319a4c(und8_t a1, ...);  /* FUN_00319A4C */
extern und8_t sk_f_0031b098(und8_t a1, ...);  /* FUN_0031B098 */
extern void sk_f_0031b258(und8_t a1, ...);  /* FUN_0031B258 */
extern void sk_f_0031b320(und8_t a1, ...);  /* FUN_0031B320 */
extern void sk_f_0031b348(und8_t a1, ...);  /* FUN_0031B348 */
extern void sk_f_0031b364(und8_t a1, ...);  /* FUN_0031B364 */
extern void sk_f_0031b4cc(und8_t a1, ...);  /* FUN_0031B4CC */
extern und8_t sk_f_0031b6d4(und8_t a1, ...);  /* FUN_0031B6D4 */
extern void sk_f_0031ba24(und8_t a1, ...);  /* FUN_0031BA24 */
extern void sk_f_0031bb34(und8_t a1, ...);  /* FUN_0031BB34 */
extern void sk_f_0031cbe4(und8_t a1, ...);  /* FUN_0031CBE4 */
extern void sk_f_0031d404(und8_t a1, ...);  /* FUN_0031D404 */
extern und8_t sk_f_0031dcbc(und8_t a1, ...);  /* FUN_0031DCBC */
extern und8_t sk_f_0031dce0(und8_t a1, ...);  /* FUN_0031DCE0 */
extern und8_t sk_f_0031dd6c(und8_t a1, ...);  /* FUN_0031DD6C */
extern void sk_f_0031ddc8(und8_t a1, ...);  /* FUN_0031DDC8 */
extern void sk_f_0031e064(und8_t a1, ...);  /* FUN_0031E064 */
extern void sk_f_0031e240(und8_t a1, ...);  /* FUN_0031E240 */
extern void sk_f_0031f668(und8_t a1, ...);  /* FUN_0031F668 */
extern void sk_f_0032156c(und8_t a1, ...);  /* FUN_0032156C */
extern void sk_f_003243b8(und8_t a1, ...);  /* FUN_003243B8 */
extern void sk_f_00324404(und8_t a1, ...);  /* FUN_00324404 */
extern void sk_f_00343b5c(und8_t a1, ...);  /* FUN_00343B5C */
extern und8_t sk_f_00344120(und8_t a1, ...);  /* FUN_00344120 */
extern void sk_f_00344250(und8_t a1, ...);  /* FUN_00344250 */
extern void sk_f_0034426c(und8_t a1, ...);  /* FUN_0034426C */
extern void sk_f_00348074(und8_t a1, ...);  /* FUN_00348074 */
extern void sk_f_00348194(und8_t a1, ...);  /* FUN_00348194 */
extern void sk_f_003482c4(und8_t a1, ...);  /* FUN_003482C4 */
extern void sk_f_003483c4(und8_t a1, ...);  /* FUN_003483C4 */
extern void sk_f_003488bc(und8_t a1, ...);  /* FUN_003488BC */
extern void sk_f_00348f50(und8_t a1, ...);  /* FUN_00348F50 */
extern void sk_f_00349178(und8_t a1, ...);  /* FUN_00349178 */
extern void sk_f_003494e8(und8_t a1, ...);  /* FUN_003494E8 */
extern void sk_f_00349530(und8_t a1, ...);  /* FUN_00349530 */
extern void sk_f_00349644(und8_t a1, ...);  /* FUN_00349644 */
extern void sk_f_00349720(und8_t a1, ...);  /* FUN_00349720 */
extern void sk_f_00349734(und8_t a1, ...);  /* FUN_00349734 */
extern void sk_f_00349a18(und8_t a1, ...);  /* FUN_00349A18 */
extern void sk_f_00349d58(und8_t a1, ...) __attribute__((noreturn));  /* FUN_00349D58 */
extern void sk_f_0034aebc(und8_t a1, ...);  /* FUN_0034AEBC */
extern void sk_f_0034b044(und8_t a1, ...);  /* FUN_0034B044 */
extern void sk_f_0034b07c(und8_t a1, ...);  /* FUN_0034B07C */
extern void sk_f_0034b264(und8_t a1, ...);  /* FUN_0034B264 */
extern void sk_f_0034bb84(und8_t a1, ...);  /* FUN_0034BB84 */
extern void sk_f_0034c2a4(und8_t a1, ...);  /* FUN_0034C2A4 */
extern sk_pair_t sk_f_0034cdb4(und8_t a1, ...);  /* FUN_0034CDB4 */
extern void sk_f_0034d024(und8_t a1, ...);  /* FUN_0034D024 */
extern und8_t sk_f_0034d454(und8_t a1, ...);  /* FUN_0034D454 */
extern und8_t sk_f_0034d49c(und8_t a1, ...);  /* FUN_0034D49C */
extern und8_t sk_f_0034e73c(und8_t a1, ...);  /* FUN_0034E73C */
extern void sk_f_0034ece8(und8_t a1, ...);  /* FUN_0034ECE8 */
extern sk_pair_t sk_f_0034f2f4(und8_t a1, ...);  /* FUN_0034F2F4 */
extern sk_pair_t sk_f_0034f7d8(und8_t a1, ...);  /* FUN_0034F7D8 */
extern void sk_f_0034fbe4(und8_t a1, ...) __attribute__((noreturn));  /* FUN_0034FBE4 */
extern sk_pair_t sk_f_003503e0(und8_t a1, ...);  /* FUN_003503E0 */
extern sk_pair_t sk_f_003504d0(und8_t a1, ...);  /* FUN_003504D0 */
extern void sk_f_003504f4(und8_t a1, ...);  /* FUN_003504F4 */
extern void sk_f_0035056c(und8_t a1, ...);  /* FUN_0035056C */
extern void sk_f_00350678(und8_t a1, ...);  /* FUN_00350678 */
extern void sk_f_00350774(und8_t a1, ...);  /* FUN_00350774 */
extern und8_t sk_f_00350bcc(und8_t a1, ...);  /* FUN_00350BCC */
extern sk_pair_t sk_f_00350e04(und8_t a1, ...);  /* FUN_00350E04 */
extern void sk_f_00350e94(und8_t a1, ...);  /* FUN_00350E94 */
extern void sk_f_00351094(und8_t a1, ...) __attribute__((noreturn));  /* FUN_00351094 */
extern void sk_f_00351790(und8_t a1, ...);  /* FUN_00351790 */
extern void sk_f_00351be0(und8_t a1, ...) __attribute__((noreturn));  /* FUN_00351BE0 */
extern void sk_f_00351c88(und8_t a1, ...);  /* FUN_00351C88 */
extern void sk_f_00351e84(und8_t a1, ...);  /* FUN_00351E84 */
extern void sk_f_00351ef8(und8_t a1, ...);  /* FUN_00351EF8 */
extern void sk_f_00351f40(und8_t a1, ...);  /* FUN_00351F40 */
extern void sk_f_00352028(und8_t a1, ...);  /* FUN_00352028 */
extern und8_t sk_f_0035216c(und8_t a1, ...);  /* FUN_0035216C */
extern void sk_f_003523e0(und8_t a1, ...);  /* FUN_003523E0 */
extern void sk_f_003523f0(und8_t a1, ...) __attribute__((noreturn));  /* FUN_003523F0 */
extern void sk_f_00352800(und8_t a1, ...);  /* FUN_00352800 */
extern void sk_f_003528cc(und8_t a1, ...);  /* FUN_003528CC */
extern void sk_f_00352e54(und8_t a1, ...);  /* FUN_00352E54 */
extern void sk_f_00352efc(und8_t a1, ...);  /* FUN_00352EFC */
extern void sk_f_00353498(und8_t a1, ...);  /* FUN_00353498 */
extern sk_pair_t sk_f_003538f0(und8_t a1, ...);  /* FUN_003538F0 */
extern void sk_f_00353aac(und8_t a1, ...);  /* FUN_00353AAC */
extern void sk_f_00354720(und8_t a1, ...);  /* FUN_00354720 */
extern sk_pair_t sk_f_00355090(und8_t a1, ...);  /* FUN_00355090 */
extern void sk_f_00355190(und8_t a1, ...);  /* FUN_00355190 */
extern void sk_f_003551d8(und8_t a1, ...);  /* FUN_003551D8 */
extern void sk_f_0035556c(und8_t a1, ...);  /* FUN_0035556C */
extern void sk_f_0035578c(und8_t a1, ...);  /* FUN_0035578C */
extern void sk_f_00355ce4(und8_t a1, ...);  /* FUN_00355CE4 */
extern void sk_f_00355d60(und8_t a1, ...);  /* FUN_00355D60 */
extern void sk_f_00356030(und8_t a1, ...);  /* FUN_00356030 */
extern void sk_f_003561a0(und8_t a1, ...);  /* FUN_003561A0 */
extern sk_pair_t sk_f_003563e0(und8_t a1, ...);  /* FUN_003563E0 */
extern void sk_f_00356590(und8_t a1, ...);  /* FUN_00356590 */
extern void sk_f_003565a8(und8_t a1, ...);  /* FUN_003565A8 */
extern und8_t sk_f_00356c6c(und8_t a1, ...);  /* FUN_00356C6C */
extern sk_pair_t sk_f_00357120(und8_t a1, ...);  /* FUN_00357120 */
extern sk_pair_t sk_f_003574b4(und8_t a1, ...);  /* FUN_003574B4 */
extern void sk_f_00357a0c(und8_t a1, ...);  /* FUN_00357A0C */
extern void sk_f_00357b04(und8_t a1, ...);  /* FUN_00357B04 */
extern und8_t sk_f_003580d4(und8_t a1, ...);  /* FUN_003580D4 */
extern void sk_f_003583dc(und8_t a1, ...);  /* FUN_003583DC */
extern void sk_f_00358594(und8_t a1, ...);  /* FUN_00358594 */
extern sk_pair_t sk_f_003586d8(und8_t a1, ...);  /* FUN_003586D8 */
extern sk_pair_t sk_f_003590e4(und8_t a1, ...);  /* FUN_003590E4 */
extern void sk_f_00359208(und8_t a1, ...);  /* FUN_00359208 */
extern void sk_f_003597f0(und8_t a1, ...);  /* FUN_003597F0 */
extern und8_t sk_fetch_result(und8_t a1, ...);  /* FUN_00359810 */
extern void sk_f_003598a0(und8_t a1, ...);  /* FUN_003598A0 */
extern und8_t sk_f_00359920(und8_t a1, ...);  /* FUN_00359920 */
extern void sk_f_00359abc(und8_t a1, ...);  /* FUN_00359ABC */
extern void sk_f_00359b50(und8_t a1, ...);  /* FUN_00359B50 */
extern void sk_f_00359cf8(und8_t a1, ...);  /* FUN_00359CF8 */
extern sk_pair_t sk_f_00359ea0(und8_t a1, ...);  /* FUN_00359EA0 */
extern void sk_f_0035a218(und8_t a1, ...);  /* FUN_0035A218 */
extern void sk_f_0035a2fc(und8_t a1, ...);  /* FUN_0035A2FC */
extern sk_pair_t sk_f_0035a758(und8_t a1, ...);  /* FUN_0035A758 */
extern und8_t sk_f_0035ace8(und8_t a1, ...);  /* FUN_0035ACE8 */
extern und8_t sk_f_003628f0(und8_t a1, ...);  /* FUN_003628F0 */
extern void sk_release(und8_t a1, ...);  /* FUN_0036B118 */
extern void sk_lock_release(und8_t a1, ...);  /* FUN_0036B21C */
extern void sk_retain(und8_t a1, ...);  /* FUN_0036B270 */
extern und8_t sk_f_0039f9e8(und8_t a1, ...);  /* FUN_0039F9E8 */
extern void sk_trace_word(und8_t a1, ...);  /* FUN_003A25D4 */
extern void sk_f_001a0774(und8_t a1, ...);  /* FUN_001A0774 (own-thunk alias target) */
/* END_EXTERN_BLOCK */

/* ==================================================================== *
 * FUNCTION BODIES (address order)
 * ==================================================================== */

/* In-slice forward declarations (functions referenced before their own
 * definition below, or cross-referenced across the dispatch wrappers). */
void sk_dispatch_3443d0(und8_t p1, und8_t p2, void (*handler)(void));
void sk_dispatch_34435c(und8_t p1, und8_t p2);
void sk_dispatch_344a98(void);
void sk_dispatch_344ab0(und8_t p1);
void sk_dispatch_344ca8(und8_t *frame, und8_t *out);
void sk_dispatch_344dc8(und8_t p1, und8_t p2, void (*h)(void));
sk_pair_t sk_dispatch_347f2c(void);
void sk_dispatch_347208(und8_t p1);


/* FUN_003442a8 @ 0x003442a8   (est. sk_dispatch_3442a8)
 * Ghidra: void FUN_003442a8(undefined8, undefined8)
 * Syscall dispatch wrapper: forwards the two explicit syscall args plus seven
 * trap-frame words (offsets 0x30,0x38,0x40,0x10,0x18,0x20,0x28) to the shared
 * object-syscall handler FUN_0026001c. Faithful arg order preserved.
 * Confidence: medium (dispatch thunk)
 * Notes: FUN_0026001C shared handler in sibling slice. */
void sk_dispatch_3442a8(und8_t p1, und8_t p2)
{
    sk_f_0026001c(p1, p2, frq(0x30), frq(0x38), frq(0x40),
                  frq(0x10), frq(0x18), frq(0x20), frq(0x28));
}

/* FUN_003442dc @ 0x003442dc   (est. sk_dispatch_3442dc)
 * Ghidra: void FUN_003442dc(void)
 * Dispatches an exception-completion: enters the lock helper FUN_0034bb84,
 * loads a completion callback from trap frame +0x28, forwards frame words
 * +0x18/+0x20 to FUN_0019d498, runs FUN_0034c2a4, then invokes the callback.
 * Confidence: low (indirect tail call)
 * Notes: callback loaded from *(code**)(x20+0x28); FUN_0019D498/FUN_0034C2A4. */
void sk_dispatch_3442dc(void)
{
    void (*cb)(void) = (void (*)(void))frq(0x28);
    sk_f_0034bb84(0);
    sk_f_0019d498(frq(0x18), frq(0x20));
    sk_f_0034c2a4(0);
    cb();
}

/* FUN_00344330 @ 0x00344330   (est. sk_dispatch_344330)
 * Ghidra: void FUN_00344330(undefined8, undefined8)
 * Wraps the generic frame forwarder FUN_003443d0 with handler FUN_0025f2e4.
 * Confidence: low (dispatch thunk) */
void sk_dispatch_344330(und8_t p1, und8_t p2)
{
    sk_dispatch_3443d0(p1, p2, sk_f_0025f2e4);
}

/* FUN_00344334 @ 0x00344334   (est. sk_dispatch_344334) — alias of 00344330. */
void sk_dispatch_344334(und8_t p1, und8_t p2)
{
    sk_dispatch_3443d0(p1, p2, sk_f_0025f2e4);
}

/* FUN_0034435c @ 0x0034435c   (est. sk_dispatch_34435c)
 * Ghidra: void FUN_0034435c(undefined8, undefined8)
 * Forwards the two syscall args plus trap-frame words +0x10/+0x18 to the
 * shared handler FUN_00324404. Confidence: low (dispatch thunk). */
void sk_dispatch_34435c(und8_t p1, und8_t p2)
{
    sk_f_00324404(p1, p2, frq(0x10), frq(0x18));
}

/* FUN_00344378 @ 0x00344378   (est. sk_dispatch_344378) — FUN_0025ecb8 variant. */
void sk_dispatch_344378(und8_t p1, und8_t p2)
{
    sk_dispatch_3443d0(p1, p2, sk_f_0025ecb8);
}

/* FUN_0034437c @ 0x0034437c   (est. sk_dispatch_34437c) — alias of 00344378. */
void sk_dispatch_34437c(und8_t p1, und8_t p2)
{
    sk_dispatch_3443d0(p1, p2, sk_f_0025ecb8);
}

/* FUN_003443a4 @ 0x003443a4   (est. sk_dispatch_3443a4) — FUN_0025e85c variant. */
void sk_dispatch_3443a4(und8_t p1, und8_t p2)
{
    sk_dispatch_3443d0(p1, p2, sk_f_0025e85c);
}

/* FUN_003443a8 @ 0x003443a8   (est. sk_dispatch_3443a8) — alias of 003443a4. */
void sk_dispatch_3443a8(und8_t p1, und8_t p2)
{
    sk_dispatch_3443d0(p1, p2, sk_f_0025e85c);
}

/* FUN_003443d0 @ 0x003443d0   (est. sk_dispatch_3443d0)
 * Ghidra: void FUN_003443d0(undefined8, undefined8, code*)
 * Generic syscall forwarder: runs the pre-dispatch hook FUN_003551d8, which
 * selects the final handler, then tail-branches to it through x9 (extraout_x9).
 * Confidence: low (indirect tail jump; register-passed target)
 * Notes: (*(code*)extraout_x9)() after FUN_003551D8. */
void sk_dispatch_3443d0(und8_t p1, und8_t p2, void (*handler)(void))
{
    (void)p1; (void)p2; (void)handler;
    sk_f_003551d8(0);
    /* tail: (*extraout_x9)() — indirect branch to handler chosen by FUN_003551D8 */
}

/* FUN_003443f4 @ 0x003443f4   (est. sk_dispatch_3443f4)
 * Ghidra: void FUN_003443f4(undefined8, undefined8)
 * Forwards the two syscall args plus six trap-frame words (+0x20,+0x28,+0x30,
 * +0x10,+0x18) to shared handler FUN_00260690. Confidence: low (dispatch thunk). */
void sk_dispatch_3443f4(und8_t p1, und8_t p2)
{
    sk_f_00260690(p1, p2, frq(0x20), frq(0x28), frq(0x30), frq(0x10), frq(0x18));
}

/* FUN_003443f8 @ 0x003443f8   (est. sk_dispatch_3443f8) — alias of 003443f4. */
void sk_dispatch_3443f8(und8_t p1, und8_t p2)
{
    sk_f_00260690(p1, p2, frq(0x20), frq(0x28), frq(0x30), frq(0x10), frq(0x18));
}

/* FUN_00344418 @ 0x00344418   (est. sk_dispatch_344418)
 * Ghidra: void FUN_00344418(undefined8, undefined8)
 * Forwards syscall args + trap-frame words (+0x18,+0x20,+0x28,+0x10) to shared
 * handler FUN_00255e68 (p2 passed last). Confidence: low (dispatch thunk). */
void sk_dispatch_344418(und8_t p1, und8_t p2)
{
    sk_f_00255e68(p1, frq(0x18), frq(0x20), frq(0x28), frq(0x10), p2);
}

/* FUN_0034441c @ 0x0034441c   (est. sk_dispatch_34441c) — alias of 00344418. */
void sk_dispatch_34441c(und8_t p1, und8_t p2)
{
    sk_f_00255e68(p1, frq(0x18), frq(0x20), frq(0x28), frq(0x10), p2);
}

/* FUN_0034443c @ 0x0034443c   (est. sk_dispatch_34443c)
 * Ghidra: void FUN_0034443c(undefined8, undefined8, undefined8)
 * Forwards the three explicit args plus six trap-frame words (+0x38,+0x40,
 * +0x10,+0x18,+0x20,+0x28,+0x30) to shared handler FUN_00251f6c.
 * Confidence: low (dispatch thunk). */
void sk_dispatch_34443c(und8_t p1, und8_t p2, und8_t p3)
{
    sk_f_00251f6c(p1, p2, frq(0x38), frq(0x40), frq(0x10), frq(0x18),
                  frq(0x20), frq(0x28), frq(0x30), p3);
}

/* FUN_0034447c @ 0x0034447c   (est. sk_dispatch_34447c)
 * Ghidra: long FUN_0034447c(long param_1)
 * Releases the object stored at param_1+0x30 (sk_release / FUN_0036B118) and
 * returns param_1 unchanged. Confidence: medium (object teardown step). */
long sk_dispatch_34447c(long obj)
{
    sk_release(*(und8_t *)(obj + 0x30));
    return obj;
}

/* FUN_003444a8 @ 0x003444a8   (est. sk_dispatch_3444a8)
 * Ghidra: void FUN_003444a8(undefined8 param_1)
 * Copies a 24-byte object payload from trap-frame +0x10 into param_1 when the
 * frame word at +0x18 is non-negative; otherwise enters the error/abort path
 * (FUN_003482C4 then the noreturn FUN_003523F0 / FUN_001AFE4C chain).
 * Confidence: medium
 * Notes: copy via FUN_00117CC4 (sk_obj_copy); abort path does not return. */
void sk_dispatch_3444a8(und8_t p1)
{
    if (frl(0x18) >= 0) {
        sk_obj_copy(frq(0x10), p1);
        return;
    }
    sk_f_003482c4(0);
    sk_f_003523f0(0);
    sk_fault(0);
}

/* FUN_003444e4 @ 0x003444e4   (est. sk_dispatch_3444e4)
 * Ghidra: long FUN_003444e4(long param_1)
 * Releases the object stored at param_1+0x40 and returns param_1 unchanged.
 * Confidence: medium (object teardown step). */
long sk_dispatch_3444e4(long obj)
{
    sk_release(*(und8_t *)(obj + 0x40));
    return obj;
}

/* FUN_00344510 @ 0x00344510   (est. sk_dispatch_344510)
 * Ghidra: void FUN_00344510(undefined8, undefined8, uint param_3)
 * Resolves a 16-byte descriptor via FUN_003586d8, then forwards the two halves,
 * param_3 (masked by a condition-flag word, extraout_w9), and four trap-frame
 * words (+0x18,+0x20,+0x28,+0x30,+0x10) to shared handler FUN_0024d788.
 * Confidence: low (dispatch thunk; extraout_w9 register artifact). */
void sk_dispatch_344510(und8_t p1, und8_t p2, und4_t p3)
{
    sk_pair_t pr = sk_f_003586d8(0);
    sk_f_0024d788(pr.lo, pr.hi, (und8_t)(p3 & 0xffffffffu),
                  frq(0x18), frq(0x20), frq(0x28), frq(0x30), frq(0x10));
}

/* FUN_0034454c @ 0x0034454c   (est. sk_dispatch_34454c)
 * Ghidra: void FUN_0034454c(void)
 * Long-lived syscall handler that walks two object/notification lists stored in
 * the trap frame (+0x40 tag, +0x48/+0x50 list heads, +0x38/+0x28/+0x30
 * descriptors) and drains them into per-object work queues. It first resolves
 * the target slot (extraout_x10 sign from FUN_003503e0); if the frame base at
 * +0x30 is negative it faults. It then runs two drain loops: each yields
 * (FUN_00248A34), resolves the current element (FUN_003580d4 / FUN_0024c0d0 /
 * FUN_0024c158), pushes it into the element list (FUN_0024be2c / FUN_003590e4)
 * and commits. The second loop rebinds the list base (FUN_001ee0fc) and
 * preserves the maximum extent (lVar6/lVar5) across the tail. On completion it
 * commits the final list length and returns via FUN_00356590. An exhausted or
 * mis-sized element list faults (FUN_003488bc(1)/FUN_00349644, then noreturn).
 * Confidence: low (dense register artifacts extraout_x8/x10/x16, __thread_bss
 *   element bound, branch flags bVar3 derived from in_x3/cVar4)
 * Notes: FUN_0024C0D0/FUN_0024C158 = per-element op; FUN_003590E4 = list pop;
 *   FUN_003488BC/FUN_00349644 = element-list overflow fault. */
void sk_dispatch_34454c(void)
{
    sk_pair_t pr;
    und8_t u12 = frq(0x40);
    long l8 = frl(0x48);
    long l6 = frl(0x50);
    long l5, l9;
    long lv5 = 0, lv8 = 0;
    bool sign;

    sk_f_003565a8(0);
    pr = sk_f_003503e0(**(und8_t **)frq(0x38));   /* resolves frame+0x38 slot */
    l5 = (long)pr.hi;
    sign = (pr.lo != 0);                           /* 0 < extraout_x10 */
    if (sign) {
        l9 = frl(0x30);
        l5 = l9 + (long)pr.lo;
        **(long **)frq(0x28) = l5;                 /* publish resolved slot */
        if (l9 < 0) {                              /* negative base: fault */
            sk_f_003483c4(0);
            goto fault_path;
        }
    }
    lv8 = l5;
    sk_f_003503e0(0);
    /* cVar4: per-element dispatch tag from (*extraout_x8+0x78)() */
    if ((frb(l8 + 0x10) & 1) == 0) {
        if (frb(l8 + 0x11) == 1) {
            if ((long)u12 < 0) goto fail;
            if (u12 >> 0x20 == 0) goto two;
        } else {
            if ((long)u12 < 0) goto fail;
            if (u12 >> 0x20 == 0) goto one;
        }
      merge:
        sk_f_003583dc(0);
        sk_f_00348194(0);
        goto drain;
    }
    if (frb(l8 + 0x11) == 1) {
        if ((long)u12 < 0) { fail: sk_f_003482c4(0); drain: sk_f_003523f0(0); sk_fault(0); }
        if (u12 >> 0x20 != 0) goto merge;
        if (frb(l6 + 0x10) != 0) u12 = (u12 | 0x80000000ull);
    } else {
        if ((long)u12 < 0) goto fail;
        if (u12 >> 0x20 != 0) goto merge;
        if (frb(l6 + 0x10) != 0) u12 = (u12 | 0x80000000ull);
      one:
        if (0) { two: u12 = (u12 | 0x40000000ull); }
    }
    sk_f_00355190(0);
    sk_f_00351790(0);
    sk_f_0024c0d0(u12, 0);
    sk_f_00355190(0);
    sk_f_0024c7bc(frq(l8 + 8));
    sk_f_00352efc(0);
    lv5 = (long)sk_f_001ee0fc(0);
    while (true) {
        sk_yield(0);
        sk_f_003580d4(0);
        lv8 = 0;                                   /* extraout_x8_00 */
        sk_f_0024be2c((und8_t)(uintptr_t)&l8, false, 0);              /* bVar3: flags-derived */
        if (0) break;                              /* in_x3 == 0 */
        pr = sk_f_003590e4(0);
        if (pr.lo == 0 || ((long)pr.hi - (long)pr.lo) < 8) goto elist_fault;
        *(long *)pr.lo = 0;                        /* *plVar7 = in_x3 */
    }
    sk_f_0024c158(sk_fetch_result(0), 0);
    sk_f_0024c7bc(frq(l6 + 8));
    sk_f_00352efc(0);
    l6 = (long)sk_f_001ee0fc(0);
    while (true) {
        sk_yield(0);
        u12 = sk_f_003580d4(0);
        sk_f_0024be2c((und8_t)(uintptr_t)&l8, (u12 >> 0x1f) & 1, 0);
        sk_f_003590e4(0);
        sk_f_00351790(0);
        if (0) {                                  /* lVar8 == 0 */
            if (l6 <= lv5) l6 = lv5;
            sk_f_0024c158((und8_t)l6, 0);
            sk_f_00356590(frq(0));
            return;
        }
        if (0) break;                             /* element list empty */
        *(long *)pr.lo = 0;                       /* *plVar7 = lVar8 */
    }
  elist_fault:
    sk_f_003488bc(1);
    sk_f_00349644(0);
  fault_path:
    sk_f_00351094(0);
    sk_fault(0);
}

/* FUN_003447c0 @ 0x003447c0   (est. sk_dispatch_3447c0)
 * Ghidra: void FUN_003447c0(void)
 * Drains a per-syscall work list: fetches the head via FUN_0035ace8 and, while
 * non-empty, yield-schedules (FUN_00248A34), releases the current element to
 * FUN_0035a218 and advances to the next (FUN_00249E20). The result head is
 * returned via x8. If the initial head is NULL it faults (FUN_00347F2C desc +
 * noreturn FUN_001AFE4C).
 * Confidence: low (in_x3 loop-flag register artifact; x8 result write) */
void sk_dispatch_3447c0(void)
{
    und8_t cur = sk_f_0035ace8(0);
    if (cur != 0) {
        do {
            sk_yield(0);
            sk_f_0035a218(cur);
            cur = sk_f_00249e20(0);
        } while (0);                              /* in_x3 != 0 */
        return;                                   /* *extraout_x8 = cur */
    }
    sk_dispatch_347f2c();
    sk_fault(0);
}

/* FUN_003448a4 @ 0x003448a4   (est. sk_dispatch_3448a4)
 * Ghidra: void FUN_003448a4(undefined8 param_1)
 * Forwards syscall arg plus trap-frame words (+0x28,+0x30,+0x18) to shared
 * handler FUN_0024c250. Confidence: low (dispatch thunk). */
void sk_dispatch_3448a4(und8_t p1)
{
    sk_f_0024c250(p1, frq(0x28), frq(0x30), frq(0x18));
}

/* FUN_003448d4 @ 0x003448d4   (est. sk_dispatch_3448d4)
 * Ghidra: void FUN_003448d4(void)
 * Resolves an object range from the trap frame and drains it into the
 * per-object cache. Resolves via FUN_003563e0: when the base is non-null it
 * validates the object header (permission word at header+0x50 AND'd with the
 * low tag) and element stride (header+0x48), computing an element count
 * (range/stride) and materializing the slice with FUN_001a26e0. It then
 * iterates the range with FUN_0024a5c0 / FUN_000dbd0c / FUN_00249a64, and
 * commits via FUN_00353498 (empty case) or FUN_0034d024 (populated case)
 * before FUN_00154148/FUN_0035578c. Any permission/stride violation faults
 * (FUN_003488bc(1)+FUN_00349644, or FUN_00348074(1)+FUN_00351be0, then
 * noreturn FUN_0034fbe4/FUN_001afe4c).
 * Confidence: low (extraout_x8/x9, in_x3 loop flag register artifacts) */
void sk_dispatch_3448d4(void)
{
    sk_pair_t pr = sk_f_003563e0(0);
    sk_pair_t slice = { 0, 0 };
    und8_t base = pr.lo;
    long l7 = frl(0x18);
    und8_t u5 = frq(0);
    long stride, count;

    if (base != 0) {
        long hdr = *(long *)(*(long *)frq(0x10) - 8);
        if ((frw(hdr + 0x50) & frw(pr.lo) & 0xffu) != 0) goto perm_fault;
        stride = *(long *)(hdr + 0x48);
        if (stride == 0) goto stride_fault;
        count = stride != 0 ? (long)(pr.hi - base) / stride : 0;
        slice = sk_f_001a26e0(base, (und8_t)count);
    }
    sk_f_00351f40(slice.lo, slice.hi);
    sk_f_0024a5c0(0);
    do {
        sk_yield(0);
        sk_f_000dbd0c(u5);
        sk_f_00249a64(0);
    } while (0);                                  /* in_x3 != 0 */
    if (base == 0) {
        sk_f_00353498(0, 0);                      /* extraout_x8 */
    } else {
        long hdr = *(long *)(l7 - 8);
        if ((frw(hdr + 0x50) & frw(pr.lo) & 0xffu) != 0) {
          perm_fault:
            sk_f_003488bc(1);
            sk_f_00349644(0);
            sk_f_0034fbe4(0);
            sk_fault(0);
        }
        stride = *(long *)(hdr + 0x48);
        if (stride == 0) {
          stride_fault:
            sk_f_00348074(1);
            sk_f_00351be0(0);
            sk_fault(0);
        }
        count = stride != 0 ? (long)(pr.hi - base) / stride : 0;
        sk_f_001a26e0(base, (und8_t)count);
        sk_f_00351790(0);
        sk_f_0034d024(0);                         /* extraout_x8 */
    }
    sk_f_00154148(0);
    sk_f_0035578c(u5);
}

/* FUN_00344a68 @ 0x00344a68   (est. sk_dispatch_344a68)
 * Ghidra: long FUN_00344a68(unsigned long param_1)
 * Dereferences a tagged pointer: if the low bit is set, follows the pointer at
 * param_1&~1; otherwise uses param_1 directly. Returns end-of-entry = base+0x20
 * plus the 32-bit length stored at base+0x20 (a table/entry iterator).
 * Confidence: medium (iterator over a tag-terminated entry table). */
long sk_dispatch_344a68(unsigned long p)
{
    if ((p & 1) != 0) p = *(unsigned long *)(p & 0xfffffffffffffffeull);
    return (long)(p + 0x20) + (long)*(int *)(p + 0x20);
}

/* FUN_00344a98 @ 0x00344a98   (est. sk_dispatch_344a98)
 * Ghidra: void FUN_00344a98(void)
 * Thunk to FUN_00344ab0 (the real dispatch wrapper below).
 * Confidence: medium. */
void sk_dispatch_344a98(void)
{
    sk_dispatch_344ab0(frq(0));
}

/* FUN_00344ab0 @ 0x00344ab0   (est. sk_dispatch_344ab0)
 * Ghidra: void FUN_00344ab0(undefined8 param_1)
 * Forwards syscall arg plus six trap-frame words (+0x30,+0x38,+0x10,+0x18,
 * +0x20,+0x28) to shared handler FUN_00212d50. Confidence: low (dispatch thunk). */
void sk_dispatch_344ab0(und8_t p1)
{
    sk_f_00212d50(p1, frq(0x30), frq(0x38), frq(0x10), frq(0x18), frq(0x20), frq(0x28));
}

/* FUN_00344ad4 @ 0x00344ad4   (est. sk_dispatch_344ad4)
 * Ghidra: void FUN_00344ad4(undefined8, undefined8)
 * Forwards the two syscall args plus six trap-frame words (+0x28,+0x30,+0x38,
 * +0x10,+0x18,+0x20) to shared handler FUN_00259b64. Confidence: low (thunk). */
void sk_dispatch_344ad4(und8_t p1, und8_t p2)
{
    sk_f_00259b64(p1, p2, frq(0x28), frq(0x30), frq(0x38), frq(0x10), frq(0x18), frq(0x20));
}

/* FUN_00344ad8 @ 0x00344ad8   (est. sk_dispatch_344ad8) — alias of 00344ad4. */
void sk_dispatch_344ad8(und8_t p1, und8_t p2)
{
    sk_f_00259b64(p1, p2, frq(0x28), frq(0x30), frq(0x38), frq(0x10), frq(0x18), frq(0x20));
}

/* FUN_00344af8 @ 0x00344af8   (est. sk_dispatch_344af8)
 * Ghidra: void FUN_00344af8(void)
 * Scope-teardown wrapper: drops the operation scope anchored at trap frame
 * +0x10 (FUN_000026E8), then runs FUN_00355ce4 and releases the op lock
 * (FUN_0036B21C). Confidence: medium. */
void sk_dispatch_344af8(void)
{
    sk_scope_drop((und8_t)(uintptr_t)(sk_trap + 0x10));
    sk_f_00355ce4(0);
    sk_lock_release(0);
}

/* FUN_00344afc @ 0x00344afc   (est. sk_dispatch_344afc) — alias of 00344af8. */
void sk_dispatch_344afc(void)
{
    sk_scope_drop((und8_t)(uintptr_t)(sk_trap + 0x10));
    sk_f_00355ce4(0);
    sk_lock_release(0);
}

/* FUN_00344b1c @ 0x00344b1c   (est. sk_dispatch_344b1c)
 * Ghidra: void FUN_00344b1c(undefined1 (*param_1)[16], undefined8* param_2)
 * Builds a 16-byte descriptor via FUN_0027c7a0 (from trap frame +0x10/+0x30 and
 * *param_2) and stores it back into *param_1. Confidence: medium (descriptor
 * builder). */
void sk_dispatch_344b1c(sk_pair_t *out, und8_t *in)
{
    *out = sk_f_0027c7a0((und8_t)(uintptr_t)(sk_trap + 0x10), frq(0x30), *in);
}

/* FUN_00344b54 @ 0x00344b54   (est. sk_dispatch_344b54)
 * Ghidra: void FUN_00344b54(void)
 * Teardown wrapper: if the trap-frame word at +0x18 is non-null, releases the
 * objects at +0x20 and +0x38 (sk_release); then drops the scope at +0x48
 * (FUN_000026E8) and releases the op lock. Confidence: medium. */
void sk_dispatch_344b54(void)
{
    if (frl(0x18) != 0) {
        sk_release(frq(0x20));
        sk_release(frq(0x38));
    }
    sk_scope_drop((und8_t)(uintptr_t)(sk_trap + 0x48));
    sk_lock_release(0);
}

/* FUN_00344b58 @ 0x00344b58   (est. sk_dispatch_344b58) — alias of 00344b54. */
void sk_dispatch_344b58(void)
{
    if (frl(0x18) != 0) {
        sk_release(frq(0x20));
        sk_release(frq(0x38));
    }
    sk_scope_drop((und8_t)(uintptr_t)(sk_trap + 0x48));
    sk_lock_release(0);
}

/* FUN_00344b98 @ 0x00344b98   (est. sk_dispatch_344b98)
 * Ghidra: void FUN_00344b98(void)
 * Syscall handler that resolves a capability/object from the trap frame and,
 * when found, either (a) retains it directly, or (b) when the resolved object
 * differs and the mode byte (frame+0x40) is 1, retains both the old refs
 * (+0x20,+0x38) and returns the new object; otherwise it converts the frame
 * request through the per-object resolve chain (FUN_00319808 / FUN_00344ca8 /
 * FUN_003597f0 / FUN_0027c85c / FUN_00359810) and re-reads the six result words.
 * Runs under a refcount snapshot (FUN_000b4594/FUN_000b45b0) and writes the
 * 6-word result record (object, two refs, tag, byte mode). Empty resolve
 * zeroes the record.
 * Confidence: low (6-word record via extraout_x8; stack spill in_stack_*). */
void sk_dispatch_344b98(void)
{
    und8_t u1 = sk_f_000b4594(0);
    und8_t r2 = frq(0x20), r4 = frq(0x38);
    und8_t o = sk_f_003198cc(frq(0x10), frq(0x10));
    und8_t lv2 = 0, lv5 = 0, lv7 = 0, lv4 = 0; und1_t cv8 = 0;

    if (o != 0) {
        o = sk_f_003628f0(0);
        if (o != 0) {
            und8_t l9 = frq(0x18);
            if (l9 != 0) {
                lv7 = frq(0x30);
                cv8 = frb(0x40);
                if (o == l9) {
                    sk_retain(r2);
                    sk_retain(r4);
                    goto done;
                }
                if (cv8 == 1) {
                    sk_retain(r2);
                    sk_retain(r4);
                    o = l9;
                    goto done;
                }
            }
            sk_f_00319808((und8_t)(uintptr_t)(sk_trap + 0x48));
            sk_f_003597f0(0);
            sk_dispatch_344ca8(sk_trap + 0x18, &r2);
            sk_f_0027c85c(sk_fetch_result(0), o, sk_trap + 0x18);
            cv8 = frb(0x48); o = frq(0x20); r4 = frq(0x40); r2 = frq(0x28); lv7 = frq(0x38);
            goto done;
        }
    }
    r2 = 0; lv7 = 0; r4 = 0; cv8 = 0; o = 0;
  done:
    sk_f_000b45b0(u1);
    (void)lv2; (void)lv5;
    /* result record at extraout_x8: [0]=o [1]=r2 [2]=tag [3]=lv7 [4]=r4 [5]=cv8 */
}

/* FUN_00344ca8 @ 0x00344ca8   (est. sk_dispatch_344ca8)
 * Ghidra: void FUN_00344ca8(void)  [register-passed 2 args]
 * Converts/resolves the current frame request into a result record: fetches a
 * token via FUN_0034e73c, runs the error/status sink FUN_00002534, the object
 * method step FUN_00349530, then calls the context method table slot
 * (ctx+0x10) to finalize. Called with (frame, out-record) from 00344b98.
 * Confidence: low (args register-passed; indirect ctx+0x10 call) */
void sk_dispatch_344ca8(und8_t *frame, und8_t *out)
{
    und8_t u;
    (void)frame; (void)out;
    u = sk_f_0034e73c(0);
    sk_f_00002534(u, 0);                         /* in_x3 */
    sk_f_00349530(0);
    (*(void (**)(void))(sk_ctx + 0x10))();       /* (*extraout_x16+0x10)() */
}

/* FUN_00344cf4 @ 0x00344cf4   (est. sk_dispatch_344cf4)
 * Ghidra: void FUN_00344cf4(undefined8, undefined8)
 * Forwards the two syscall args plus trap-frame word +0x18 to shared handler
 * FUN_00359abc, then runs FUN_002a4148. Confidence: low (dispatch thunk). */
void sk_dispatch_344cf4(und8_t p1, und8_t p2)
{
    sk_f_00359abc(p1, p2, frq(0x18));
    sk_f_002a4148(0);
}

/* FUN_00344d14 @ 0x00344d14   (est. sk_dispatch_344d14)
 * Ghidra: void FUN_00344d14(undefined8 param_1)
 * Loads a callback from trap frame +0x20 and invokes it with (param_1, frame
 * word +0x18). If the preserved aux register (unaff_x21) is non-zero, runs the
 * notify step FUN_00354720. Confidence: low (unaff_x21 register artifact). */
void sk_dispatch_344d14(und8_t p1)
{
    void (*cb)(und8_t, und8_t) = (void (*)(und8_t, und8_t))frq(0x20);
    cb(p1, frq(0x18));
    if (0) sk_f_00354720(0);                     /* unaff_x21 != 0 */
}

/* FUN_00344d4c @ 0x00344d4c   (est. sk_dispatch_344d4c)
 * Ghidra: void FUN_00344d4c(void)
 * Copies the two context words at +0x18/+0x20 from the object resolved by
 * FUN_00356c6c into sk_ctx, runs the enter step FUN_0034b07c, then tail-calls
 * the context method at *sk_ctx. Confidence: low (indirect ctx call). */
void sk_dispatch_344d4c(void)
{
    und8_t p = sk_f_00356c6c(0);
    *(und8_t *)(sk_ctx + 0x18) = *(und8_t *)(p + 0x18);
    *(und8_t *)(sk_ctx + 0x20) = *(und8_t *)(p + 0x20);
    sk_f_0034b07c(0);
    (*(void (**)(void))(*(und8_t **)sk_ctx))();  /* (*(code*)*extraout_x16)() */
}

/* FUN_00344d9c @ 0x00344d9c   (est. sk_dispatch_344d9c) — FUN_0022f500 variant. */
void sk_dispatch_344d9c(und8_t p1, und8_t p2)
{
    sk_dispatch_344dc8(p1, p2, sk_f_0022f500);
}

/* FUN_00344da0 @ 0x00344da0   (est. sk_dispatch_344da0) — alias of 00344d9c. */
void sk_dispatch_344da0(und8_t p1, und8_t p2)
{
    sk_dispatch_344dc8(p1, p2, sk_f_0022f500);
}

/* FUN_00344dc8 @ 0x00344dc8   (est. sk_dispatch_344dc8)
 * Ghidra: void FUN_00344dc8(undefined8, undefined8, code*)
 * Generic frame forwarder: invokes the supplied handler with the two explicit
 * syscall args plus five trap-frame words (+0x30,+0x10,+0x18,+0x20,+0x28).
 * Confidence: low (dispatch thunk). */
void sk_dispatch_344dc8(und8_t p1, und8_t p2, void (*h)(void))
{
    ((void (*)(und8_t, und8_t, und8_t, und8_t, und8_t, und8_t, und8_t))h)
        (p1, p2, frq(0x30), frq(0x10), frq(0x18), frq(0x20), frq(0x28));
}

/* FUN_00344df4 @ 0x00344df4   (est. sk_dispatch_344df4)
 * Ghidra: void FUN_00344df4(void)
 * Runs the enter hook FUN_0035a2fc then the shared handler FUN_003243b8.
 * Confidence: low (dispatch thunk). */
void sk_dispatch_344df4(void)
{
    sk_f_0035a2fc(0);
    sk_f_003243b8(0);
}

/* FUN_00344df8 @ 0x00344df8   (est. sk_dispatch_344df8) — alias of 00344df4. */
void sk_dispatch_344df8(void)
{
    sk_f_0035a2fc(0);
    sk_f_003243b8(0);
}

/* FUN_00344e24 @ 0x00344e24   (est. sk_dispatch_344e24) — alias of 00344df4. */
void sk_dispatch_344e24(void)
{
    sk_f_0035a2fc(0);
    sk_f_003243b8(0);
}

/* FUN_00344e28 @ 0x00344e28   (est. sk_dispatch_344e28) — alias of 00344df4. */
void sk_dispatch_344e28(void)
{
    sk_f_0035a2fc(0);
    sk_f_003243b8(0);
}

/* FUN_00344e54 @ 0x00344e54   (est. sk_dispatch_344e54)
 * Ghidra: undefined8 FUN_00344e54(undefined8 param_1)
 * Runs the three-step begin sequence FUN_00106e3c / FUN_00002534 /
 * FUN_000841a0, then invokes the context method at (ctx+8) with param_1 and
 * returns param_1 unchanged. Confidence: low (indirect ctx+8 call). */
und8_t sk_dispatch_344e54(und8_t p1)
{
    sk_f_00106e3c(0);
    sk_f_00002534(0);
    sk_f_000841a0(0);
    (*(void (**)(und8_t))(sk_ctx + 8))(p1);
    return p1;
}

/* FUN_00344e9c @ 0x00344e9c   (est. sk_dispatch_344e9c)
 * Ghidra: void FUN_00344e9c(undefined8 param_1)
 * Forwards syscall arg plus six trap-frame fields (+0x20,+0x28,+0x30,+0x38,
 * +0x10,+0x18) to shared handler FUN_00238e1c. Confidence: low (thunk). */
void sk_dispatch_344e9c(und8_t p1)
{
    sk_f_00238e1c(p1, frq(0x20), frq(0x28), frq(0x30), frb(0x38), frq(0x10), frq(0x18));
}

/* FUN_00344ed4 @ 0x00344ed4   (est. sk_dispatch_344ed4)
 * Ghidra: long FUN_00344ed4(unsigned long param_1)
 * Like 00344a68 but at offset 0x50: dereferences a tagged pointer (low bit set
 * -> follow param_1&~1) and returns base+0x50 plus the 32-bit length stored at
 * base+0x50. Table/entry iterator over a 0x50-based entry header.
 * Confidence: medium. */
long sk_dispatch_344ed4(unsigned long p)
{
    if ((p & 1) != 0) p = *(unsigned long *)(p & 0xfffffffffffffffeull);
    return (long)(p + 0x50) + (long)*(int *)(p + 0x50);
}

/* FUN_00344f04 @ 0x00344f04   (est. sk_dispatch_344f04)
 * Ghidra: void FUN_00344f04(void)
 * Teardown wrapper: if the frame word at +0x28 is non-null, drops the scope at
 * +0x10 (FUN_000026E8); then runs FUN_00353aac and releases the op lock.
 * Confidence: medium. */
void sk_dispatch_344f04(void)
{
    if (frl(0x28) != 0) sk_scope_drop((und8_t)(uintptr_t)(sk_trap + 0x10));
    sk_f_00353aac(0);
    sk_lock_release(0);
}

/* FUN_00344f08 @ 0x00344f08   (est. sk_dispatch_344f08) — alias of 00344f04. */
void sk_dispatch_344f08(void)
{
    if (frl(0x28) != 0) sk_scope_drop((und8_t)(uintptr_t)(sk_trap + 0x10));
    sk_f_00353aac(0);
    sk_lock_release(0);
}

/* FUN_00344f30 @ 0x00344f30   (est. sk_dispatch_344f30)
 * Ghidra: void FUN_00344f30(void)
 * Releases the object at frame +0x20 (sk_release) and invokes the context
 * method at (ctx+8) with a computed frame pointer (sk_trap + ((b+0x30)&~b),
 * where b = ctx+0x50) and the frame word +0x10, then releases the op lock.
 * Confidence: low (computed-frame indirect call; ctx+0x50 byte). */
void sk_dispatch_344f30(void)
{
    und8_t u2 = frq(0x10);
    und1_t b = crb(0x50);
    sk_f_003494e8(0);
    sk_release(frq(0x20));
    (*(void (**)(void *, und8_t))(sk_ctx + 8))
        ((void *)((char *)sk_trap + ((b + 0x30) & ~b)), u2);
    sk_lock_release(0);
}

/* FUN_00344fc0 @ 0x00344fc0   (est. sk_dispatch_344fc0)
 * Ghidra: void FUN_00344fc0(long *param_1)
 * Builds a 6-word capability/region record into param_1. Reads the tag from
 * frame +0x10, enters FUN_00356030, and resolves the region via FUN_00319a4c
 * from the frame +0x28 target: when the target differs and mode (frame local
 * c8) is not 1, it remaps the record through FUN_0027c85c /
 * FUN_00319a4c (frame-local descriptor). The final 6 words (base, two refs,
 * tag, two bounds, mode byte) are stored into param_1[0..5].
 * Confidence: low (frame-local stack spill lStack_/local_ register
 *   artifacts; indirect ctx+0x10 / x9 calls). */
void sk_dispatch_344fc0(long *out)
{
    und8_t u1 = frq(0x10);
    und8_t tgt = frq(0x28);
    und8_t res;
    und8_t lf0 = 0, lb0 = 0;

    (void)u1;
    sk_f_00356030(0);
    if (tgt != lf0) {
        res = sk_f_00319a4c((und8_t)(uintptr_t)&lf0);
        (void)res;
        (*(void (**)(void))(sk_ctx + 0x10))();   /* ctx+0x10 method */
        sk_f_0027c85c((und8_t)(uintptr_t)&lf0, &res, tgt, &lb0);
    }
    out[1] = 0; out[0] = (long)lf0; out[2] = 0; out[4] = 0; out[3] = 0;
    *(char *)(out + 5) = 0;
}

/* FUN_003450e8 @ 0x003450e8   (est. sk_dispatch_3450e8)
 * Ghidra: void FUN_003450e8(undefined8 param_1)
 * Forwards (param_1, frame word +0x10) to FUN_0034ece8, then invokes the
 * context method at (ctx+8) with the computed frame pointer
 * sk_trap + ((b+0x18)&~b), b = ctx+0x50, and releases the op lock.
 * Confidence: low (computed-frame indirect call). */
void sk_dispatch_3450e8(und8_t p1)
{
    und1_t b;
    sk_f_0034ece8(p1, frq(0x10));
    b = crb(0x50);
    (*(void (**)(void *))(sk_ctx + 8))
        ((void *)((char *)sk_trap + ((b + 0x18) & ~b)));
    sk_lock_release(0);
}

/* FUN_00345158 @ 0x00345158   (est. sk_dispatch_345158)
 * Ghidra: void FUN_00345158(undefined8 *param_1)
 * Builds a 6-word result record into param_1. Enters FUN_00349734, computes a
 * frame pointer from (ctx+0x50) and passes it to FUN_00355d60 (with a base
 * field from extraout_x8+0x40). Reads a capability word from the frame at an
 * offset given by extraout_x8_00, resolves a descriptor via FUN_00319a4c,
 * calls the ctx+0x10 method, and finalizes the record via FUN_0027c85c /
 * FUN_00359810. The six words (base, two refs, tag, two bounds, mode byte)
 * are stored to param_1[0..5].
 * Confidence: low (extraout_x8/x8_00/x16 register artifacts, zeroed locals). */
void sk_dispatch_345158(und8_t *out)
{
    und8_t u2 = frq(0x10);
    und1_t b;
    und8_t cap;
    und8_t rec[6] = { 0, 0, 0, 0, 0, 0 };

    (void)u2;
    sk_f_00349734(0);
    b = crb(0x50);
    sk_f_00355d60(crq(0x40) + ((b + 0x18) & ~b));
    cap = frq(0);                                /* extraout_x8_00 offset */
    sk_f_00319a4c((und8_t)(uintptr_t)&rec);
    (*(void (**)(void))(sk_ctx + 0x10))();       /* ctx+0x10 method */
    sk_f_0027c85c(sk_fetch_result(0), cap, (void *)&rec);
    out[1] = rec[1]; out[0] = rec[0]; out[2] = rec[2];
    out[4] = rec[4]; out[3] = rec[3];
    *(und1_t *)(out + 5) = (und1_t)rec[5];
}

/* FUN_00345264 @ 0x00345264   (est. sk_dispatch_345264)
 * Ghidra: void FUN_00345264(void)
 * Copies the 16-bit field at +0x10 between the two descriptors resolved by
 * FUN_00350e04, runs FUN_00357120, copies the +0x40 word into sk_ctx+0x40,
 * and retains the result. Confidence: low (register-passed extraout_x1). */
void sk_dispatch_345264(void)
{
    sk_pair_t pr = sk_f_00350e04(0);
    *(und2_t *)(pr.lo + 0x10) = *(und2_t *)(pr.hi + 0x10);
    sk_f_00357120(0);
    *(und8_t *)(sk_ctx + 0x40) = *(und8_t *)(pr.hi + 0x40);   /* extraout_x1 */
    sk_retain(0);
}

/* FUN_003452a0 @ 0x003452a0   (est. sk_dispatch_3452a0)
 * Ghidra: void FUN_003452a0(void)
 * Resolves a descriptor pair via FUN_0034f2f4 and FUN_00359ea0 and copies the
 * five fields at +0x18/+0x20/+0x28/+0x30/+0x38 from the source (pr.hi) into the
 * destination (pr.lo). Then swaps the +0x40 word in sk_ctx, retaining the new
 * and releasing the old. Confidence: low (pair-register artifacts). */
void sk_dispatch_3452a0(void)
{
    sk_pair_t p1 = sk_f_0034f2f4(0);
    sk_pair_t p2;
    und8_t u3;
    *(und8_t *)(p1.lo + 8) = *(und8_t *)(p1.hi + 8);
    p2 = sk_f_00359ea0(0);
    *(und8_t *)(p2.lo + 0x18) = *(und8_t *)(p2.hi + 0x18);
    *(und8_t *)(p2.lo + 0x20) = *(und8_t *)(p2.hi + 0x20);
    *(und8_t *)(p2.lo + 0x28) = *(und8_t *)(p2.hi + 0x28);
    *(und8_t *)(p2.lo + 0x30) = *(und8_t *)(p2.hi + 0x30);
    *(und4_t *)(p2.lo + 0x38) = *(und4_t *)(p2.hi + 0x38);
    u3 = crq(0x40);
    *(und8_t *)(sk_ctx + 0x40) = *(und8_t *)(p2.hi + 0x40);
    sk_retain(0);
    sk_release(u3);
}

/* FUN_00345310 @ 0x00345310   (est. sk_dispatch_345310)
 * Ghidra: void FUN_00345310(void)
 * Resolves descriptors via FUN_00350e04/FUN_00359ea0 and FUN_00357120, swaps
 * the +0x40 word in sk_ctx (retaining the new, releasing the old).
 * Confidence: low. */
void sk_dispatch_345310(void)
{
    sk_pair_t p2;
    und8_t u1;
    sk_f_00350e04(0);
    sk_f_00359ea0(0);
    p2 = sk_f_00357120(0);
    u1 = *(und8_t *)(p2.lo + 0x40);
    *(und8_t *)(sk_ctx + 0x40) = *(und8_t *)(p2.hi + 0x40);
    sk_release(u1);
}

/* FUN_003453f8 @ 0x003453f8   (est. sk_dispatch_3453f8)
 * Ghidra: undefined8* FUN_003453f8(undefined8* param_1, undefined8* param_2)
 * Copies the first four words of param_2 into param_1, then fills words 6..10
 * and the byte at +8 from the object resolved by FUN_00355090 (fields +0x30,
 * +0x38, +0x40 byte, +0x48, +0x50), retains the object, and returns param_1.
 * Confidence: low (extraout_x1 resolved-object pointer). */
und8_t *sk_dispatch_3453f8(und8_t *dst, und8_t *src)
{
    und8_t u1, u2, u3;
    sk_pair_t pr;
    u1 = src[0]; u3 = src[3]; u2 = src[2];
    dst[1] = src[1]; dst[0] = u1; dst[3] = u3; dst[2] = u2;
    pr = sk_f_00355090(0);
    dst[6] = *(und8_t *)(pr.hi + 0x30);          /* extraout_x1 */
    dst[7] = *(und8_t *)(pr.hi + 0x38);
    *(und1_t *)(dst + 8) = *(und1_t *)(pr.hi + 0x40);
    dst[10] = *(und8_t *)(pr.hi + 0x50);
    dst[9] = *(und8_t *)(pr.hi + 0x48);
    sk_retain(0);
    return dst;
}

/* FUN_00345444 @ 0x00345444   (est. sk_dispatch_345444)
 * Ghidra: void FUN_00345444(void)
 * Enters FUN_0034b264, resolves a descriptor via FUN_0034f7d8, copies the
 * +0x18 field, resolves via FUN_00355090 and swaps the +0x30 word in the trap
 * frame (retaining new, releasing old). Then runs FUN_00359b50 and copies the
 * +0x48/+0x50 words from sk_ctx into the trap frame.
 * Confidence: low (extraout_x1/x16 register artifacts). */
void sk_dispatch_345444(void)
{
    sk_pair_t pr;
    und8_t u1;
    sk_f_0034b264(0);
    pr = sk_f_0034f7d8(0);
    *(und8_t *)(pr.lo + 0x18) = *(und8_t *)(pr.hi + 0x18);
    sk_f_00355090(0);
    u1 = frq(0x30);
    *(und8_t *)(sk_trap + 0x30) = crq(0x30);     /* extraout_x1 */
    sk_retain(0);
    sk_release(u1);
    sk_f_00359b50(0);
    *(und8_t *)(sk_trap + 0x48) = crq(0x48);
    *(und8_t *)(sk_trap + 0x50) = crq(0x50);
}

/* FUN_003454ac @ 0x003454ac   (est. sk_dispatch_3454ac)
 * Ghidra: void FUN_003454ac(void)
 * Resolves a descriptor via FUN_003504d0, copies its first four words into the
 * destination half, then resolves via FUN_00355090 and swaps the +0x30 word in
 * the trap frame (retaining new, releasing old), runs FUN_00359b50 and copies
 * the +0x48/+0x50 words from sk_ctx into the trap frame.
 * Confidence: low. */
void sk_dispatch_3454ac(void)
{
    sk_pair_t pr = sk_f_003504d0(0);
    und8_t u2;
    pr = sk_f_00355090(0);
    u2 = *(und8_t *)(pr.lo + 0x30);
    *(und8_t *)(sk_trap + 0x30) = *(und8_t *)(pr.hi + 0x30);
    sk_release(u2);
    sk_f_00359b50(0);
    u2 = crq(0x48);
    *(und8_t *)(sk_trap + 0x50) = crq(0x50);
    *(und8_t *)(sk_trap + 0x48) = u2;
}

/* FUN_003458d8 @ 0x003458d8   (est. sk_dispatch_3458d8)
 * Ghidra: void FUN_003458d8(long param_1)
 * Releases the objects at param_1+0x10 and param_1+0x28 (sk_release).
 * Confidence: medium (object teardown). */
void sk_dispatch_3458d8(long obj)
{
    sk_release(*(und8_t *)(obj + 0x10));
    sk_release(*(und8_t *)(obj + 0x28));
}

/* FUN_00345908 @ 0x00345908   (est. sk_dispatch_345908)
 * Ghidra: void FUN_00345908(void)
 * Copies a 0x3c-byte object record from the object resolved by FUN_003538f0
 * into sk_ctx, field by field (bytes/halves/words at +1,+8,+0x10,+0x18,+0x1c,
 * +0x1f,+0x23,+0x28,+0x30,+0x34,+0x38), retaining the copied payload (uVar2)
 * and the source object. Confidence: low (byte-granular field copy). */
void sk_dispatch_345908(void)
{
    sk_pair_t pr = sk_f_003538f0(0);
    und8_t src = pr.hi, dst = pr.lo, u2;
    *(und2_t *)(dst + 1) = *(und2_t *)(src + 1);
    *(und1_t *)(dst + 8) = *(und1_t *)(src + 8);
    *(und8_t *)(sk_ctx + 0x10) = *(und8_t *)(src + 0x10);
    *(und1_t *)(sk_ctx + 0x18) = *(und1_t *)(src + 0x18);
    *(und4_t *)(sk_ctx + 0x1c) = *(und4_t *)(src + 0x1c);
    *(und4_t *)(sk_ctx + 0x1f) = *(und4_t *)(src + 0x1f);
    *(und1_t *)(sk_ctx + 0x23) = *(und1_t *)(src + 0x23);
    u2 = *(und8_t *)(src + 0x28);
    *(und8_t *)(sk_ctx + 0x28) = u2;
    *(und1_t *)(sk_ctx + 0x30) = *(und1_t *)(src + 0x30);
    *(und4_t *)(sk_ctx + 0x34) = *(und4_t *)(src + 0x34);
    *(und1_t *)(sk_ctx + 0x38) = *(und1_t *)(src + 0x38);
    sk_retain(0);
    sk_retain(u2);
}

/* FUN_00345990 @ 0x00345990   (est. sk_dispatch_345990)
 * Ghidra: void FUN_00345990(void)
 * Updates a 0x3c-byte object record in the trap frame from the source resolved
 * by FUN_0034cdb4/FUN_003574b4: swaps the +0x10 word (retaining new, releasing
 * old), copies the +0x18..+0x38 byte/word fields from sk_ctx, and swaps the
 * +0x28 word. Confidence: low (extraout_x1 register artifact). */
void sk_dispatch_345990(void)
{
    sk_pair_t pr;
    und8_t u2;
    und4_t u1;
    sk_f_0034cdb4(0);
    pr = sk_f_003574b4(0);
    u2 = frq(0x10);
    *(und8_t *)(sk_trap + 0x10) = *(und8_t *)(pr.hi + 0x10);   /* extraout_x1 */
    sk_retain(0);
    sk_release(u2);
    *(und1_t *)(sk_trap + 0x18) = crb(0x18);
    u1 = crw(0x1c);
    *(und4_t *)(sk_trap + 0x1f) = crw(0x1f);
    *(und4_t *)(sk_trap + 0x1c) = u1;
    *(und1_t *)(sk_trap + 0x23) = crb(0x23);
    u2 = frq(0x28);
    *(und8_t *)(sk_trap + 0x28) = crq(0x28);
    sk_retain(0);
    sk_release(u2);
    *(und1_t *)(sk_trap + 0x30) = crb(0x30);
    u1 = crw(0x34);
    *(und1_t *)(sk_trap + 0x38) = crb(0x38);
    *(und4_t *)(sk_trap + 0x34) = u1;
}

/* FUN_00345a28 @ 0x00345a28   (est. sk_dispatch_345a28)
 * Ghidra: void FUN_00345a28(void)
 * Updates the trap-frame 0x3c-byte record from the source resolved by
 * FUN_003574b4: swaps +0x10 and +0x28 words (releasing old) and copies the
 * +0x18..+0x38 fields from sk_ctx. Confidence: low. */
void sk_dispatch_345a28(void)
{
    sk_pair_t pr;
    und8_t u1;
    sk_f_0034cdb4(0);
    pr = sk_f_003574b4(0);
    u1 = *(und8_t *)(pr.lo + 0x10);
    *(und8_t *)(sk_trap + 0x10) = *(und8_t *)(pr.hi + 0x10);
    sk_release(u1);
    *(und1_t *)(sk_trap + 0x18) = crb(0x18);
    *(und4_t *)(sk_trap + 0x1c) = crw(0x1c);
    *(und4_t *)(sk_trap + 0x1f) = crw(0x1f);
    *(und1_t *)(sk_trap + 0x23) = crb(0x23);
    u1 = frq(0x28);
    *(und8_t *)(sk_trap + 0x28) = crq(0x28);
    sk_release(u1);
    *(und1_t *)(sk_trap + 0x30) = crb(0x30);
    *(und4_t *)(sk_trap + 0x34) = crw(0x34);
    *(und1_t *)(sk_trap + 0x38) = crb(0x38);
}

/* FUN_00345b4c @ 0x00345b4c   (est. sk_dispatch_345b4c)
 * Ghidra: void FUN_00345b4c(void)
 * Copies the 0x1c-byte record at +8..+0x1b from the object resolved by
 * FUN_003538f0 into sk_ctx and retains it. Confidence: low. */
void sk_dispatch_345b4c(void)
{
    sk_pair_t pr = sk_f_003538f0(0);
    und8_t src = pr.hi;
    *(und8_t *)(sk_ctx + 8) = *(und8_t *)(src + 8);
    *(und1_t *)(sk_ctx + 0x10) = *(und1_t *)(src + 0x10);
    *(und4_t *)(sk_ctx + 0x14) = *(und4_t *)(src + 0x14);
    *(und4_t *)(sk_ctx + 0x17) = *(und4_t *)(src + 0x17);
    *(und1_t *)(sk_ctx + 0x1b) = *(und1_t *)(src + 0x1b);
    sk_retain(0);
}

/* FUN_00345b9c @ 0x00345b9c   (est. sk_dispatch_345b9c)
 * Ghidra: void FUN_00345b9c(void)
 * Runs the enter steps FUN_0034cdb4/FUN_00352028/FUN_00359cf8 with
 * retain/release, then copies the +0x14/+0x17/+0x1b fields from sk_ctx into
 * the trap frame. Confidence: low. */
void sk_dispatch_345b9c(void)
{
    und4_t u1;
    sk_f_0034cdb4(0);
    sk_f_00352028(0);
    sk_retain(0);
    sk_release(0);
    sk_f_00359cf8(0);
    u1 = crw(0x14);
    *(und4_t *)(sk_trap + 0x17) = crw(0x17);
    *(und4_t *)(sk_trap + 0x14) = u1;
    *(und1_t *)(sk_trap + 0x1b) = crb(0x1b);
}

/* FUN_00345bf4 @ 0x00345bf4   (est. sk_dispatch_345bf4)
 * Ghidra: void FUN_00345bf4(void)
 * Swaps the +8 word in the trap frame with the object resolved by FUN_0034cdb4
 * (releasing the old), runs FUN_00359cf8, and copies the +0x14/+0x17/+0x1b
 * fields from sk_ctx. Confidence: low. */
void sk_dispatch_345bf4(void)
{
    sk_pair_t pr = sk_f_0034cdb4(0);
    und8_t u1 = *(und8_t *)(pr.lo + 8);
    *(und8_t *)(sk_trap + 8) = *(und8_t *)(pr.hi + 8);
    sk_release(u1);
    sk_f_00359cf8(0);
    *(und4_t *)(sk_trap + 0x14) = crw(0x14);
    *(und4_t *)(sk_trap + 0x17) = crw(0x17);
    *(und1_t *)(sk_trap + 0x1b) = crb(0x1b);
}

/* FUN_003460e4 @ 0x003460e4   (est. sk_dispatch_3460e4)
 * Ghidra: long FUN_003460e4(long param_1)
 * Runs FUN_0035556c, copies the +8 byte from the resolved object into
 * param_1+8, retains the object, and returns param_1.
 * Confidence: low (extraout_x1 register artifact). */
long sk_dispatch_3460e4(long obj)
{
    sk_f_0035556c(0);
    *(und1_t *)(obj + 8) = crb(8);   /* extraout_x1 (resolved object) +8 */
    sk_retain(0);
    return obj;
}

/* FUN_00346118 @ 0x00346118   (est. sk_dispatch_346118)
 * Ghidra: void FUN_00346118(void)
 * Runs FUN_0034b044 with retain/release, then copies the +8 byte from sk_ctx
 * into the trap frame. Confidence: low. */
void sk_dispatch_346118(void)
{
    sk_f_0034b044(0);
    sk_retain(0);
    sk_release(0);
    *(und1_t *)(sk_trap + 8) = crb(8);
}

/* FUN_00346158 @ 0x00346158   (est. sk_dispatch_346158)
 * Ghidra: void FUN_00346158(void)
 * Resolves an object via FUN_0034d454, releases its first word, writes the
 * resolved value into the trap frame head, and copies the +8 byte from sk_ctx
 * into frame+8. Confidence: low (extraout_x8 register artifact). */
void sk_dispatch_346158(void)
{
    und8_t *p = (und8_t *)sk_f_0034d454(0);
    und8_t u2 = *p;
    *sk_trap = 0;                                  /* extraout_x8 */
    sk_release(u2);
    *(und1_t *)(sk_trap + 1) = crb(8);
}

/* FUN_003463f0 @ 0x003463f0   (est. thunk_FUN_0001612c)
 * Ghidra: undefined8 thunk_FUN_0001612c(long param_1)
 * Loads and returns the object/slot word at param_1+0x10.
 * Confidence: medium (direct field accessor). */
und8_t sk_dispatch_3463f0(long p)
{
    return *(und8_t *)(p + 0x10);
}

/* FUN_0034648c @ 0x0034648c   (est. sk_dispatch_34648c)
 * Ghidra: void FUN_0034648c(void)
 * Thunk to the shared handler FUN_0031b320. Confidence: low. */
void sk_dispatch_34648c(void)
{
    sk_f_0031b320(0);
}

/* FUN_00346490 @ 0x00346490   (est. sk_dispatch_346490) — alias of 0034648c. */
void sk_dispatch_346490(void)
{
    sk_f_0031b320(0);
}

/* FUN_00346560 @ 0x00346560   (est. thunk_FUN_002d738c)
 * Ghidra: void thunk_FUN_002d738c(undefined8, undefined8, undefined8)
 * Runs the hash init FUN_003528cc and the shared hash-compress FUN_002298d4,
 * feeding it arg param_3. Confidence: low (hash feed thunk). */
void sk_dispatch_346560(und8_t p1, und8_t p2, und8_t p3)
{
    (void)p1; (void)p2;
    sk_f_003528cc(0);
    sk_f_002298d4(0);
    sk_f_002298d4(p3);
}

/* FUN_00346580 @ 0x00346580   (est. sk_dispatch_346580)
 * Ghidra: void FUN_00346580(void)
 * Thunk to shared handler FUN_0031ddc8. Confidence: low. */
void sk_dispatch_346580(void)
{
    sk_f_0031ddc8(0);
}

/* FUN_00346584 @ 0x00346584   (est. sk_dispatch_346584) — alias of 00346580. */
void sk_dispatch_346584(void)
{
    sk_f_0031ddc8(0);
}

/* FUN_00346598 @ 0x00346598   (est. sk_dispatch_346598)
 * Ghidra: void FUN_00346598(void)
 * Thunk to in-slice FUN_0034435c (sk_dispatch_34435c). Confidence: medium. */
void sk_dispatch_346598(void)
{
    sk_dispatch_34435c(0, 0);
}

/* FUN_0034659c @ 0x0034659c   (est. sk_dispatch_34659c) — alias of 00346598. */
void sk_dispatch_34659c(void)
{
    sk_dispatch_34435c(0, 0);
}

/* FUN_003465b8 @ 0x003465b8   (est. sk_dispatch_3465b8)
 * Ghidra: uint FUN_003465b8(void)
 * Returns bit 0 of the shared flag FUN_0031b098. Confidence: low. */
und4_t sk_dispatch_3465b8(void)
{
    return (und4_t)(sk_f_0031b098(0) & 1);
}

/* FUN_003465bc @ 0x003465bc   (est. sk_dispatch_3465bc) — alias of 003465b8. */
und4_t sk_dispatch_3465bc(void)
{
    return (und4_t)(sk_f_0031b098(0) & 1);
}

/* FUN_003465d4 @ 0x003465d4   (est. sk_dispatch_3465d4)
 * Ghidra: uint FUN_003465d4(void)
 * Returns bit 0 of the shared flag FUN_0031dcbc. Confidence: low. */
und4_t sk_dispatch_3465d4(void)
{
    return (und4_t)(sk_f_0031dcbc(0) & 1);
}

/* FUN_003465d8 @ 0x003465d8   (est. sk_dispatch_3465d8) — alias of 003465d4. */
und4_t sk_dispatch_3465d8(void)
{
    return (und4_t)(sk_f_0031dcbc(0) & 1);
}

/* FUN_00346674 @ 0x00346674   (est. thunk_FUN_001ef804)
 * Ghidra: void thunk_FUN_001ef804(undefined8, undefined8, long, undefined8, undefined8)
 * Completes a capability/object op with a bound region. When the region at
 * param_3+0x10 is non-null, it retains it, runs the enter/validate helpers
 * (FUN_003561a0 / FUN_00077708 / FUN_001f99f4) and, if the validation flag
 * clears, invokes the ctx+0x10 method with (param_1, frame+0x38 + ctx+0x48 *
 * resolved-index, param_5) before releasing. It then publishes the completion
 * state via FUN_00350774(param_1, ok) and FUN_000839d8.
 * Confidence: low (extraout_x1/x16 register artifacts). */
void sk_dispatch_346674(und8_t p1, und8_t p2, long p3, und8_t p4, und8_t p5)
{
    bool ok;
    (void)p2; (void)p4;
    if (*(long *)(p3 + 0x10) == 0) {
        ok = true;
    } else {
        sk_f_003561a0(0);
        sk_retain(0);                            /* thunk_FUN_0036B270(extraout_x1) */
        sk_f_00077708(0);
        sk_f_001f99f4(0);
        ok = (0 & 1) == 0;                       /* extraout_x1_00 */
        if (!ok) {
            long lv = (long)sk_f_00350bcc(0);
            (*(void (**)(und8_t, und8_t, und8_t))(sk_ctx + 0x10))
                (p1, (und8_t)(frl(0x38) + (long)crq(0x48) * lv), p5);
        }
        sk_release(0);
    }
    sk_f_00350774(p1, ok);
    sk_f_000839d8(0);
}

/* FUN_0034668c @ 0x0034668c   (est. sk_dispatch_34668c)
 * Ghidra: void FUN_0034668c(void)
 * Thunk to shared handler FUN_00212e74. Confidence: low. */
void sk_dispatch_34668c(void){ sk_f_00212e74(0); }
/* FUN_00346690 @ 0x00346690   (est. sk_dispatch_346690) — alias. */
void sk_dispatch_346690(void){ sk_f_00212e74(0); }
/* FUN_003466a4 @ 0x003466a4   (est. sk_dispatch_3466a4) — FUN_00212e8c thunk. */
void sk_dispatch_3466a4(void){ sk_f_00212e8c(0); }
/* FUN_003466a8 @ 0x003466a8   (est. sk_dispatch_3466a8) — alias. */
void sk_dispatch_3466a8(void){ sk_f_00212e8c(0); }
/* FUN_003466bc @ 0x003466bc   (est. sk_dispatch_3466bc) — FUN_00212ea4 thunk. */
void sk_dispatch_3466bc(void){ sk_f_00212ea4(0); }
/* FUN_003466c0 @ 0x003466c0   (est. sk_dispatch_3466c0) — alias. */
void sk_dispatch_3466c0(void){ sk_f_00212ea4(0); }
/* FUN_003466d4 @ 0x003466d4   (est. sk_dispatch_3466d4) — FUN_00212ec8 thunk. */
void sk_dispatch_3466d4(void){ sk_f_00212ec8(0); }
/* FUN_003466d8 @ 0x003466d8   (est. sk_dispatch_3466d8) — alias. */
void sk_dispatch_3466d8(void){ sk_f_00212ec8(0); }

/* FUN_00346718 @ 0x00346718   (est. thunk_FUN_002b74c0)
 * Ghidra: void thunk_FUN_002b74c0(void)
 * Runs a dispatch sequence: takes the address of the shared handler FUN_002ab5bc,
 * runs FUN_00352e54, invokes that handler, runs FUN_003523e0 and retains, then
 * FUN_0034aebc. Confidence: low (function-pointer value + indirect call). */
void sk_dispatch_346718(void)
{
    void (*pc)(void) = (void (*)(void))sk_f_002ab5bc;
    sk_f_00352e54(0);
    pc();
    sk_f_003523e0(0);
    sk_retain(0);
    sk_f_0034aebc(0);
}

/* FUN_00346744 @ 0x00346744   (est. sk_dispatch_346744) — FUN_00310f1c thunk. */
void sk_dispatch_346744(void){ sk_f_00310f1c(0); }
/* FUN_00346748 @ 0x00346748   (est. sk_dispatch_346748) — alias. */
void sk_dispatch_346748(void){ sk_f_00310f1c(0); }
/* FUN_0034675c @ 0x0034675c   (est. sk_dispatch_34675c) — FUN_00319440 thunk. */
void sk_dispatch_34675c(void){ sk_f_00319440(0); }
/* FUN_00346760 @ 0x00346760   (est. sk_dispatch_346760) — alias. */
void sk_dispatch_346760(void){ sk_f_00319440(0); }
/* FUN_00346774 @ 0x00346774   (est. sk_dispatch_346774) — FUN_0031b364 thunk. */
void sk_dispatch_346774(void){ sk_f_0031b364(0); }
/* FUN_00346778 @ 0x00346778   (est. sk_dispatch_346778) — alias. */
void sk_dispatch_346778(void){ sk_f_0031b364(0); }
/* FUN_0034678c @ 0x0034678c   (est. sk_dispatch_34678c) — FUN_00343b5c thunk. */
void sk_dispatch_34678c(void){ sk_f_00343b5c(0); }
/* FUN_00346790 @ 0x00346790   (est. sk_dispatch_346790) — alias. */
void sk_dispatch_346790(void){ sk_f_00343b5c(0); }
/* FUN_00346874 @ 0x00346874   (est. sk_dispatch_346874) — FUN_001df7dc thunk. */
void sk_dispatch_346874(void){ sk_f_001df7dc(0); }
/* FUN_00346878 @ 0x00346878   (est. sk_dispatch_346878) — alias. */
void sk_dispatch_346878(void){ sk_f_001df7dc(0); }
/* FUN_0034688c @ 0x0034688c   (est. sk_dispatch_34688c) — FUN_001b5894 thunk. */
void sk_dispatch_34688c(void){ sk_f_001b5894(0); }
/* FUN_00346890 @ 0x00346890   (est. sk_dispatch_346890) — alias. */
void sk_dispatch_346890(void){ sk_f_001b5894(0); }
/* FUN_003468a4 @ 0x003468a4   (est. sk_dispatch_3468a4) — FUN_001b58b0 thunk. */
void sk_dispatch_3468a4(void){ sk_f_001b58b0(0); }
/* FUN_003469a8 @ 0x003469a8   (est. sk_dispatch_3469a8) — FUN_0031b258 thunk. */
void sk_dispatch_3469a8(void){ sk_f_0031b258(0); }
/* FUN_003469ac @ 0x003469ac   (est. sk_dispatch_3469ac) — alias. */
void sk_dispatch_3469ac(void){ sk_f_0031b258(0); }
/* FUN_003469c0 @ 0x003469c0   (est. sk_dispatch_3469c0) — FUN_0031d404 thunk. */
void sk_dispatch_3469c0(void){ sk_f_0031d404(0); }
/* FUN_003469c4 @ 0x003469c4   (est. sk_dispatch_3469c4) — alias. */
void sk_dispatch_3469c4(void){ sk_f_0031d404(0); }
/* FUN_003469d8 @ 0x003469d8   (est. sk_dispatch_3469d8) — FUN_0031b348 thunk. */
void sk_dispatch_3469d8(void){ sk_f_0031b348(0); }
/* FUN_003469dc @ 0x003469dc   (est. sk_dispatch_3469dc) — alias. */
void sk_dispatch_3469dc(void){ sk_f_0031b348(0); }
/* FUN_003469f0 @ 0x003469f0   (est. sk_dispatch_3469f0) — FUN_00344250 thunk. */
void sk_dispatch_3469f0(void){ sk_f_00344250(0); }
/* FUN_003469f4 @ 0x003469f4   (est. sk_dispatch_3469f4) — alias. */
void sk_dispatch_3469f4(void){ sk_f_00344250(0); }
/* FUN_00346a0c @ 0x00346a0c   (est. sk_dispatch_346a0c)
 * Ghidra: void FUN_00346a0c(void)  [unreachable block removed at 0x346a54]
 * Thunk to shared handler FUN_002364dc. Confidence: low. */
void sk_dispatch_346a0c(void){ sk_f_002364dc(0); }

/* FUN_00346a60 @ 0x00346a60   (est. thunk_FUN_002d49f4)
 * Ghidra: bool thunk_FUN_002d49f4(unsigned long, long, unsigned long, long)
 * Lexicographic 128-bit comparison: returns (a_lo,a_hi) < (b_lo,b_hi), where
 * the hi words decide only when the lo words compare equal.
 * Confidence: medium (128-bit ordering helper). */
bool sk_dispatch_346a60(unsigned long a_lo, long a_hi, unsigned long b_lo, long b_hi)
{
    bool r = a_lo < b_lo;
    if (a_hi != b_hi) r = a_hi < b_hi;
    return r;
}

/* FUN_00346acc @ 0x00346acc   (est. sk_dispatch_346acc) — FUN_0031dce0 bit0. */
und4_t sk_dispatch_346acc(void){ return (und4_t)(sk_f_0031dce0(0) & 1); }
/* FUN_00346ad0 @ 0x00346ad0   (est. sk_dispatch_346ad0) — alias. */
und4_t sk_dispatch_346ad0(void){ return (und4_t)(sk_f_0031dce0(0) & 1); }

/* FUN_00346aec @ 0x00346aec   (est. thunk_FUN_001a0754)
 * Ghidra: void thunk_FUN_001a0754(void)
 * Resolves a value via FUN_001a0d1c and stores it at the trap-frame head.
 * Confidence: low. */
void sk_dispatch_346aec(void)
{
    *sk_trap = sk_f_001a0d1c(0);
}

/* FUN_00346af0 @ 0x00346af0   (est. thunk_FUN_001a0774)
 * Ghidra: void thunk_FUN_001a0774(void)
 * Thunk to FUN_001a0774. Confidence: low. */
void sk_dispatch_346af0(void){ sk_f_001a0774(0); }

/* FUN_00346b64 @ 0x00346b64   (est. sk_dispatch_346b64) — FUN_001eed8c thunk. */
void sk_dispatch_346b64(void){ sk_f_001eed8c(0); }
/* FUN_00346b68 @ 0x00346b68   (est. sk_dispatch_346b68) — alias. */
void sk_dispatch_346b68(void){ sk_f_001eed8c(0); }

/* FUN_00346bdc @ 0x00346bdc   (est. thunk_FUN_0036b270)
 * Ghidra: unsigned long thunk_FUN_0036b270(unsigned long param_1)
 * Atomic reference-count retain on a tagged object: for a positive tag, clears
 * the low 3 bits to get the object base, then compare-and-swaps the refcount
 * slot (+8), adding the 0x200000000 increment quantum per attempt. If the slot
 * holds -1 (freed) or the CAS detects a concurrent change, it falls back to the
 * slow path FUN_0039f9e8. Returns the object base on success, else param_1.
 * Confidence: high (classic cL4/seL4 refcount retain).
 * Notes: FUN_0039F9E8 = slow-path CAS (realloc/lock). */
unsigned long sk_dispatch_346bdc(unsigned long p)
{
    if (0 < (long)p) {
        unsigned long base = p & ~7ul;
        long *slot = (long *)(base + 8);
        long cur = *slot;
        for (;;) {
            long nxt = cur + 0x200000000;
            if (nxt < 0) {
                if ((int)cur == -1) return base;
                return sk_f_0039f9e8((und8_t)(uintptr_t)slot, (und8_t)cur, 1);
            }
            if (*slot == cur) { *slot = nxt; return base; }
            cur = *slot;
        }
    }
    return p;
}

/* FUN_00346bf0 @ 0x00346bf0   (est. thunk_FUN_00200b38)
 * Ghidra: void thunk_FUN_00200b38(void)
 * Runs a dispatch chain: FUN_00352800, FUN_000a6f88, an indirect call through
 * the global dispatch table DAT_00658c00 (with the ctx+0x40 word), then
 * FUN_00349178 / FUN_00351e84 / FUN_00351c88, an indirect tail call, and the
 * context methods FUN_0035056c(ctx+0x20) and the x8-selected handler.
 * Confidence: low (indirect DAT_00658c00 global table; register artifacts). */
void sk_dispatch_346bf0(void)
{
    sk_f_00352800(0);
    sk_f_000a6f88(0);
    /* (*DAT_00658c00)(ctx+0x40) — global dispatch-table indirect call */
    /* (*DAT_00658c00)(crq(0x40)): global dispatch-table indirect call */
    sk_f_00349178(0);
    sk_f_00351e84(0);
    sk_f_00351c88(0);
    /* (*extraout_x9)() — indirect tail call */
    sk_f_0035056c(crq(0x20));
    /* (*extraout_x8_00)() */
}

/* FUN_00346bf8 @ 0x00346bf8   (est. thunk_FUN_001a29a0)
 * Ghidra: void thunk_FUN_001a29a0(void)
 * Resolves a 16-byte descriptor via FUN_0035a758 and dispatches it through the
 * context method at (ctx+0x20) (an indirect jump table that Ghidra could not
 * recover at 0x1a29d0). Confidence: low (unrecoverable jumptable). */
void sk_dispatch_346bf8(void)
{
    sk_pair_t pr = sk_f_0035a758(0);
    /* (**(code**)(ctx+0x20))(pr.lo, extraout_x9, pr.hi) — jumptable at 0x1a29d0 */
    (*(void (**)(und8_t, und8_t, und8_t))(sk_ctx + 0x20))(pr.lo, 0, pr.hi);
}

/* FUN_00346c38 @ 0x00346c38   (est. thunk_FUN_0025bca4)
 * Ghidra: void thunk_FUN_0025bca4(void)
 * Drains a notification/pending set from the aux register (unaff_x22): enters
 * the seq FUN_0008e518/FUN_00349a18/FUN_00349720/FUN_00348f50, and while the
 * pending bitmap (x22+0x38 bit vector) is non-empty for the current index
 * (uVar4 from FUN_0035216c), delivers each pending entry to FUN_00357a0c with
 * a slot address (x22+0x30 + ctx+0x48*index), then advances via FUN_00357b04 /
 * FUN_003504f4 until the count flag (x22+0x28 bit 0) clears. Finalizes via
 * FUN_00359920/FUN_0008e500. Confidence: low (unaff_x22 register; dense
 *   extraout_x8/x16 artifacts; global DAT_00658c00 indirect call). */
void sk_dispatch_346c38(void)
{
    und8_t u1, u4;
    sk_f_0008e518(0);
    sk_f_00349a18(0);
    sk_f_00349720(0);
    /* (*DAT_00658c00)(ctx+0x40) */
    /* (*DAT_00658c00)(crq(0x40)): global dispatch-table indirect call */
    sk_f_00348f50(0);
    if (crq(0x10) != 0) {
        u1 = frq(0x28);                          /* unaff_x22 + 0x28 */
        sk_f_00350678(0);
        sk_f_00358594(0);
        /* (*extraout_x8_00)() */
        u1 = sk_f_0035216c(0);
        do {
            u4 = u1 & ~0ull;
            if ((1ull << (u4 & 0x3f) & (*(unsigned long *)(0 + 0x38 + (u4 >> 6) * 8))) == 0) break;
            sk_f_00357a0c(crq(0x10), u1, (und8_t)(frl(0x30) + (long)crq(0x48) * (long)u4));
            /* (*extraout_x8_02)() */
            sk_f_00351ef8(0);
            u1 = sk_f_0034d49c(0);
            sk_f_00350e94(u1, 0);
            /* (*extraout_x8_03)() */
            sk_f_00357b04(0);
            sk_f_003504f4(0);
            /* (*extraout_x8_04)() */
            u1 = u4 + 1;
        } while ((u1 & 1) == 0);
    }
    sk_f_00359920(0);
    sk_f_0008e500(sk_fetch_result(0), frq(0));
}

/* FUN_00346c5c @ 0x00346c5c   (est. thunk_FUN_002d3c28)
 * Ghidra: void thunk_FUN_002d3c28(unsigned long, long, unsigned long, long)
 * 128-bit checked add: faults (FUN_003488bc(1, lo+lo) then noreturn
 * FUN_00349d58/FUN_001afe4c) when the add overflows (signed carry on the hi
 * words, or unsigned carry on the lo words with a non-wrapping hi sum).
 * Otherwise returns silently. Confidence: high (checked arithmetic helper).
 * Notes: SCARRY8/CARRY8 flags per seL4 fail_low/overflow discipline. */
void sk_dispatch_346c5c(unsigned long a_lo, long a_hi, unsigned long b_lo, long b_hi)
{
    unsigned long lo, hi;
    bool carry = __builtin_add_overflow(a_lo, b_lo, &lo);
    bool scarry = __builtin_add_overflow(a_hi, b_hi, &hi);
    if (!scarry && (!carry || (a_hi + b_hi) != 0x7fffffffffffffffL)) return;
    sk_f_003488bc(1, (und8_t)(a_lo + b_lo));
    sk_f_00349d58(0);
    sk_fault(0);
}

/* FUN_00346c60 @ 0x00346c60   (est. thunk_FUN_002d4a64)
 * Ghidra: void thunk_FUN_002d4a64(unsigned long, long, unsigned long, long)
 * 128-bit checked subtract: faults when the subtraction would underflow
 * (signed borrow on the hi words, respecting the lo-word ordering).
 * Confidence: high (checked arithmetic helper).
 * Notes: SBORROW8 = signed-borrow flag; -0x8000000000000000 sentinel. */
void sk_dispatch_346c60(unsigned long a_lo, long a_hi, unsigned long b_lo, long b_hi)
{
    unsigned long lo;
    bool sborrow;
    if (a_lo < b_lo) {
        sborrow = __builtin_sub_overflow(a_hi, b_hi, &lo);
        if ((a_hi - b_hi) != INT64_MIN && !sborrow) return;
    } else {
        sborrow = __builtin_sub_overflow(a_hi, b_hi, &lo);
        if (!sborrow) return;
    }
    sk_f_003488bc(1, (und8_t)(a_lo - b_lo));
    sk_f_00349d58(0);
    sk_fault(0);
}

/* FUN_00346c6c @ 0x00346c6c   (est. sk_dispatch_346c6c) — FUN_0031b6d4 bit0. */
und4_t sk_dispatch_346c6c(void){ return (und4_t)(sk_f_0031b6d4(0) & 1); }
/* FUN_00346c70 @ 0x00346c70   (est. sk_dispatch_346c70) — alias. */
und4_t sk_dispatch_346c70(void){ return (und4_t)(sk_f_0031b6d4(0) & 1); }
/* FUN_00346cf0 @ 0x00346cf0   (est. sk_dispatch_346cf0) — in-slice FUN_00344a98 thunk. */
void sk_dispatch_346cf0(void){ sk_dispatch_344a98(); }
/* FUN_00346cf4 @ 0x00346cf4   (est. sk_dispatch_346cf4) — alias. */
void sk_dispatch_346cf4(void){ sk_dispatch_344a98(); }
/* FUN_00346d38 @ 0x00346d38   (est. sk_dispatch_346d38) — FUN_0031b4cc thunk. */
void sk_dispatch_346d38(void){ sk_f_0031b4cc(0); }
/* FUN_00346d3c @ 0x00346d3c   (est. sk_dispatch_346d3c) — alias. */
void sk_dispatch_346d3c(void){ sk_f_0031b4cc(0); }

/* FUN_00346d5c @ 0x00346d5c   (est. thunk_FUN_001a0d1c)
 * Ghidra: undefined8 thunk_FUN_001a0d1c(undefined8, undefined8, unsigned long param_3)
 * Resolves/allocates an object under a scope (unaff_x19): begins via
 * FUN_00077570; when param_3 bit 0 is set and the sign check
 * (FUN_00077560/FUN_00077624) flags a fault, it software-breaks (0x1a0dac);
 * otherwise runs FUN_00077550. Then resolves through FUN_0019c3a4 with two
 * globals (DAT_0064c040, DAT_004bbf40), commits via FUN_00077580, and either
 * enters FUN_0019d6d0 (flag clear) or finalizes FUN_0019ccec and clears the
 * ctx+0x10 slot (flag set), then releases. Returns the resolved object.
 * Confidence: low (SoftwareBreakpoint, global DAT refs, register artifacts). */
und8_t sk_dispatch_346d5c(und8_t p1, und8_t p2, unsigned long p3)
{
    und8_t u2;
    (void)p1; (void)p2;
    sk_f_00077570(0);
    u2 = 0;                                      /* extraout_x8 */
    if ((p3 & 1) != 0 && (sk_f_00077560(0), u2 = 0, /* in_NG != in_OV */ 0)) {
        sk_f_00077624(0);
        if (/* in_NG */ 0) {
            /* SoftwareBreakpoint(1, 0x1a0dac) */
            __builtin_trap();
        }
        sk_f_00077550(0);
        u2 = 0;                                  /* extraout_x1_00 */
    }
    u2 = sk_f_0019c3a4(crq(0x10), u2, 0, 0);     /* DAT_0064c040, DAT_004bbf40 */
    sk_f_00077580(0);
    if ((/* unaff_x20 */ 0 & 1) == 0) {
        sk_f_0019d6d0(0);
    } else {
        sk_f_0019ccec(0);
        *(und8_t *)(sk_ctx + 0x10) = 0;
    }
    sk_release(0);
    return u2;
}

/* FUN_00346e10 @ 0x00346e10   (est. sk_dispatch_346e10) — FUN_003194bc thunk. */
void sk_dispatch_346e10(void){ sk_f_003194bc(0); }
/* FUN_00346e14 @ 0x00346e14   (est. sk_dispatch_346e14) — alias. */
void sk_dispatch_346e14(void){ sk_f_003194bc(0); }
/* FUN_00346eb4 @ 0x00346eb4   (est. sk_dispatch_346eb4) — FUN_001d1e00 thunk. */
void sk_dispatch_346eb4(void){ sk_f_001d1e00(0); }
/* FUN_00346eb8 @ 0x00346eb8   (est. sk_dispatch_346eb8) — alias. */
void sk_dispatch_346eb8(void){ sk_f_001d1e00(0); }
/* FUN_00346ecc @ 0x00346ecc   (est. sk_dispatch_346ecc) — FUN_001d1e18 thunk. */
void sk_dispatch_346ecc(void){ sk_f_001d1e18(0); }
/* FUN_00346ed0 @ 0x00346ed0   (est. sk_dispatch_346ed0) — alias. */
void sk_dispatch_346ed0(void){ sk_f_001d1e18(0); }
/* FUN_00346f5c @ 0x00346f5c   (est. sk_dispatch_346f5c) — FUN_001e4a30 thunk. */
void sk_dispatch_346f5c(void){ sk_f_001e4a30(0); }
/* FUN_00346f60 @ 0x00346f60   (est. sk_dispatch_346f60) — alias. */
void sk_dispatch_346f60(void){ sk_f_001e4a30(0); }
/* FUN_00346f74 @ 0x00346f74   (est. sk_dispatch_346f74) — FUN_00270ae4 thunk. */
void sk_dispatch_346f74(void){ sk_f_00270ae4(0); }
/* FUN_00346f78 @ 0x00346f78   (est. sk_dispatch_346f78) — alias. */
void sk_dispatch_346f78(void){ sk_f_00270ae4(0); }
/* FUN_00346ff4 @ 0x00346ff4   (est. sk_dispatch_346ff4) — FUN_0031ba24 thunk. */
void sk_dispatch_346ff4(void){ sk_f_0031ba24(0); }
/* FUN_00346ff8 @ 0x00346ff8   (est. sk_dispatch_346ff8) — alias. */
void sk_dispatch_346ff8(void){ sk_f_0031ba24(0); }
/* FUN_0034700c @ 0x0034700c   (est. sk_dispatch_34700c) — FUN_0031bb34 thunk. */
void sk_dispatch_34700c(void){ sk_f_0031bb34(0); }
/* FUN_00347010 @ 0x00347010   (est. sk_dispatch_347010) — alias. */
void sk_dispatch_347010(void){ sk_f_0031bb34(0); }
/* FUN_00347024 @ 0x00347024   (est. sk_dispatch_347024) — FUN_0031cbe4 thunk. */
void sk_dispatch_347024(void){ sk_f_0031cbe4(0); }
/* FUN_00347028 @ 0x00347028   (est. sk_dispatch_347028) — alias. */
void sk_dispatch_347028(void){ sk_f_0031cbe4(0); }
/* FUN_00347040 @ 0x00347040   (est. sk_dispatch_347040) — FUN_0031e240 thunk. */
void sk_dispatch_347040(void){ sk_f_0031e240(0); }
/* FUN_00347044 @ 0x00347044   (est. sk_dispatch_347044) — alias. */
void sk_dispatch_347044(void){ sk_f_0031e240(0); }

/* FUN_003471d8 @ 0x003471d8   (est. thunk_FUN_002298d4)
 * Ghidra: void thunk_FUN_002298d4(unsigned long param_1)
 * Hash-state compression update (Skein/Threefish-style 64-bit block mixer):
 * folds param_1 into the 5-word hash state at sk_trap with a per-block counter
 * increment (0x800000000000000) and 64-bit rotations/xors. The counter low
 * byte selects the inject shift; words 1..4 are mixed with ROTR/ROTL ops and
 * the XOR of the injected word. The updated state is written back to
 * sk_trap[0..4]. Confidence: medium (recognizable hash-mixer core).
 * Notes: state base = unaff_x20 (sk_trap); counter add per block = 0x800000000000000. */
void sk_dispatch_3471d8(unsigned long w)
{
    unsigned long s0, s1, s2, s3, s4;
    unsigned long u1, u3, u4, u5, u6;
    s0 = sk_trap[0]; s1 = sk_trap[1]; s2 = sk_trap[2]; s3 = sk_trap[3]; s4 = sk_trap[4];
    u4 = (s0 >> 0x38) & 7;
    u1 = (w << (u4 * 8)) | (s0 & 0xffffffffffffffull);
    u3 = (w >> ((u4 * -8) & 0x3f)) | ((s0 & 0xff00000000000000ull) + 0x800000000000000ull);
    if (u4 == 0) { u1 = w; u3 = s0 + 0x800000000000000ull; }
    u5 = s4 ^ u1;
    u4 = s2;
    u6 = (s2 + s1) ^ ((s2 >> 0x33) | (s2 << 0xd));
    u4 = s3 + u5 + u6;
    u5 = (s3 + u5) ^ ((u5 >> 0x30) | (u5 << 0x10));
    s4 = u5 + ((s2 + s1) >> 0x20 | (s2 + s1) << 0x20);
    sk_trap[4] = s4 ^ ((u5 >> 0x2b) | (u5 << 0x15));
    sk_trap[2] = u4 ^ ((u6 >> 0x2f) | (u6 << 0x11));
    sk_trap[3] = (u4 >> 0x20) | (u4 << 0x20);
    sk_trap[0] = u3;
    sk_trap[1] = s4 ^ u1;
}

/* FUN_00347200 @ 0x00347200   (est. thunk_FUN_002b3978)
 * Ghidra: undefined1[16] thunk_FUN_002b3978(unsigned long, unsigned long)
 * Extracts a capability descriptor pair from (param_1, param_2): the type
 * field is param_2 bits 56-59 when param_2 bit 61 is set (else param_1), and
 * the mode selects 0xb (if bit 60 of param_2 clear and bit 59 of param_1 set)
 * else 0x7. Returns { lo = 0xf, hi = mode | type<<16 }.
 * Confidence: medium (cap type/rights extraction).
 * Notes: bits 0x2000000000000000/0x1000000000000000 selectors. */
sk_pair_t sk_dispatch_347200(unsigned long p1, unsigned long p2)
{
    unsigned long typ = p1;
    unsigned long mode;
    if ((p2 & 0x2000000000000000ull) != 0) typ = (p2 >> 0x38) & 0xf;
    if ((p2 & 0x1000000000000000ull) == 0) {
        mode = 0x7ull;
    } else {
        mode = ((p1 >> 0x3b) & 1) ? 0x7ull : 0xbull;
    }
    return (sk_pair_t){ .lo = 0xf, .hi = mode | (typ << 0x10) };
}

/* FUN_00347208 @ 0x00347208   (est. thunk_FUN_00359208)
 * Ghidra: void thunk_FUN_00359208(undefined8 param_1)
 * Resolves/releases a capability slot: calls thunk_FUN_00012568 with
 * (param_1, -1, -1) — a full wildcard lookup/retain. Confidence: low. */
void sk_dispatch_347208(und8_t p1)
{
    sk_f_00012568(p1, 0xffffffffffffffffull, 0xffffffffffffffffull);
}

/* FUN_00347348 @ 0x00347348   (est. sk_dispatch_347348) — FUN_0034426c thunk. */
void sk_dispatch_347348(void){ sk_f_0034426c(0); }
/* FUN_0034734c @ 0x0034734c   (est. sk_dispatch_34734c) — alias. */
void sk_dispatch_34734c(void){ sk_f_0034426c(0); }
/* FUN_00347380 @ 0x00347380   (est. sk_dispatch_347380) — FUN_0031e064 thunk. */
void sk_dispatch_347380(void){ sk_f_0031e064(0); }
/* FUN_00347384 @ 0x00347384   (est. sk_dispatch_347384) — alias. */
void sk_dispatch_347384(void){ sk_f_0031e064(0); }
/* FUN_003473a4 @ 0x003473a4   (est. sk_dispatch_3473a4) — FUN_0032156c thunk. */
void sk_dispatch_3473a4(void){ sk_f_0032156c(0); }
/* FUN_003473a8 @ 0x003473a8   (est. sk_dispatch_3473a8) — alias. */
void sk_dispatch_3473a8(void){ sk_f_0032156c(0); }
/* FUN_00347400 @ 0x00347400   (est. sk_dispatch_347400) — FUN_001e4a48 thunk. */
void sk_dispatch_347400(void){ sk_f_001e4a48(0); }
/* FUN_00347404 @ 0x00347404   (est. sk_dispatch_347404) — alias. */
void sk_dispatch_347404(void){ sk_f_001e4a48(0); }
/* FUN_00347418 @ 0x00347418   (est. sk_dispatch_347418) — FUN_0026f824 thunk. */
void sk_dispatch_347418(void){ sk_f_0026f824(0); }
/* FUN_0034741c @ 0x0034741c   (est. sk_dispatch_34741c) — alias. */
void sk_dispatch_34741c(void){ sk_f_0026f824(0); }

/* FUN_00347480 @ 0x00347480   (est. thunk_FUN_002acbb8)
 * Ghidra: void thunk_FUN_002acbb8(void)
 * Commits a completed object/log op: enters FUN_0008409c, forwards the trap
 * head to FUN_003598a0 and, when the state tag (extraout_x8) and the high bits
 * of frame[1] permit, retains, logs the frame[1] word (FUN_003A25D4), stores
 * the two aux words into the frame head, and returns; otherwise runs the
 * abort path FUN_00084180 / FUN_00267820. Confidence: low (register
 *   artifacts; thunk_FUN_0036B270 retain; FUN_003A25D4 trace word). */
void sk_dispatch_347480(void)
{
    und8_t u1;
    sk_f_0008409c(0);
    u1 = sk_trap[1];
    sk_f_003598a0(sk_trap[0]);
    if (0 && (((0 & (u1 ^ ~0ull)) >> 0x3d & 1) == 0)) {
        sk_retain(0);
        sk_trace_word(u1);
        sk_trap[0] = 0;                          /* unaff_x21 */
        sk_trap[1] = 0;                          /* unaff_x19 */
        return;
    }
    sk_f_00084180(0);
    sk_f_00267820(0);
}

/* FUN_003474f8 @ 0x003474f8   (est. sk_dispatch_3474f8)
 * Ghidra: void FUN_003474f8(void)
 * Runs FUN_0026a2ac then the shared handler thunk_FUN_0026c2a0.
 * Confidence: low (dispatch pair). */
void sk_dispatch_3474f8(void)
{
    sk_f_0026a2ac(0);
    sk_f_0026c2a0(0);
}

/* FUN_003474fc @ 0x003474fc   (est. sk_dispatch_3474fc) — alias of 003474f8. */
void sk_dispatch_3474fc(void)
{
    sk_f_0026a2ac(0);
    sk_f_0026c2a0(0);
}

/* FUN_0034789c @ 0x0034789c   (est. sk_dispatch_34789c) — FUN_00344120 bit0. */
und4_t sk_dispatch_34789c(void){ return (und4_t)(sk_f_00344120(0) & 1); }
/* FUN_003478a0 @ 0x003478a0   (est. sk_dispatch_3478a0) — alias. */
und4_t sk_dispatch_3478a0(void){ return (und4_t)(sk_f_00344120(0) & 1); }
/* FUN_003478f4 @ 0x003478f4   (est. sk_dispatch_3478f4) — FUN_0019f658 thunk. */
void sk_dispatch_3478f4(void){ sk_f_0019f658(0); }
/* FUN_003478f8 @ 0x003478f8   (est. sk_dispatch_3478f8) — alias. */
void sk_dispatch_3478f8(void){ sk_f_0019f658(0); }
/* FUN_0034790c @ 0x0034790c   (est. sk_dispatch_34790c) — FUN_001aa318 thunk. */
void sk_dispatch_34790c(void){ sk_f_001aa318(0); }
/* FUN_00347910 @ 0x00347910   (est. sk_dispatch_347910) — alias. */
void sk_dispatch_347910(void){ sk_f_001aa318(0); }
/* FUN_00347924 @ 0x00347924   (est. sk_dispatch_347924) — FUN_001dccd0 thunk. */
void sk_dispatch_347924(void){ sk_f_001dccd0(0); }
/* FUN_00347928 @ 0x00347928   (est. sk_dispatch_347928) — alias. */
void sk_dispatch_347928(void){ sk_f_001dccd0(0); }
/* FUN_003479a0 @ 0x003479a0   (est. sk_dispatch_3479a0) — FUN_002871b4 thunk. */
void sk_dispatch_3479a0(void){ sk_f_002871b4(0); }
/* FUN_003479a4 @ 0x003479a4   (est. sk_dispatch_3479a4) — alias. */
void sk_dispatch_3479a4(void){ sk_f_002871b4(0); }
/* FUN_00347a10 @ 0x00347a10   (est. sk_dispatch_347a10)
 * Ghidra: uint FUN_00347a10(void)
 * Runs FUN_001afdbc then returns bit 0 of FUN_0031dd6c. Confidence: low. */
und4_t sk_dispatch_347a10(void){ sk_f_001afdbc(0); return (und4_t)(sk_f_0031dd6c(0) & 1); }
/* FUN_00347a14 @ 0x00347a14   (est. sk_dispatch_347a14) — alias. */
und4_t sk_dispatch_347a14(void){ sk_f_001afdbc(0); return (und4_t)(sk_f_0031dd6c(0) & 1); }
/* FUN_00347a24 @ 0x00347a24   (est. sk_dispatch_347a24) — FUN_0031dd6c bit0. */
und4_t sk_dispatch_347a24(void){ return (und4_t)(sk_f_0031dd6c(0) & 1); }
/* FUN_00347a78 @ 0x00347a78   (est. sk_dispatch_347a78)
 * Ghidra: void FUN_00347a78(void)
 * Runs the pair FUN_001a79e0 / FUN_001bf9b0. Confidence: low. */
void sk_dispatch_347a78(void){ sk_f_001a79e0(0); sk_f_001bf9b0(0); }
/* FUN_00347a7c @ 0x00347a7c   (est. sk_dispatch_347a7c) — alias. */
void sk_dispatch_347a7c(void){ sk_f_001a79e0(0); sk_f_001bf9b0(0); }
/* FUN_00347af4 @ 0x00347af4   (est. thunk_FUN_00320078)
 * Ghidra: void thunk_FUN_00320078(long param_1)
 * When param_1 is non-null, resolves/releases via thunk_FUN_00359208
 * (sk_dispatch_347208); otherwise does nothing. Confidence: low. */
void sk_dispatch_347af4(long p)
{
    if (p != 0) sk_dispatch_347208(0);
}
/* FUN_00347b04 @ 0x00347b04   (est. sk_dispatch_347b04) — FUN_001df5ec thunk. */
void sk_dispatch_347b04(void){ sk_f_001df5ec(0); }
/* FUN_00347b08 @ 0x00347b08   (est. sk_dispatch_347b08) — alias. */
void sk_dispatch_347b08(void){ sk_f_001df5ec(0); }
/* FUN_00347b20 @ 0x00347b20   (est. sk_dispatch_347b20) — FUN_0031f668 thunk. */
void sk_dispatch_347b20(void){ sk_f_0031f668(0); }
/* FUN_00347b24 @ 0x00347b24   (est. sk_dispatch_347b24) — alias. */
void sk_dispatch_347b24(void){ sk_f_0031f668(0); }
/* FUN_00347cb4 @ 0x00347cb4   (est. sk_dispatch_347cb4) — FUN_0019f63c thunk. */
void sk_dispatch_347cb4(void){ sk_f_0019f63c(0); }
/* FUN_00347cb8 @ 0x00347cb8   (est. sk_dispatch_347cb8) — alias. */
void sk_dispatch_347cb8(void){ sk_f_0019f63c(0); }
/* FUN_00347ccc @ 0x00347ccc   (est. sk_dispatch_347ccc) — FUN_001aa2fc thunk. */
void sk_dispatch_347ccc(void){ sk_f_001aa2fc(0); }
/* FUN_00347cd0 @ 0x00347cd0   (est. sk_dispatch_347cd0) — alias. */
void sk_dispatch_347cd0(void){ sk_f_001aa2fc(0); }
/* FUN_00347ce4 @ 0x00347ce4   (est. sk_dispatch_347ce4) — FUN_001dccb4 thunk. */
void sk_dispatch_347ce4(void){ sk_f_001dccb4(0); }
/* FUN_00347ce8 @ 0x00347ce8   (est. sk_dispatch_347ce8) — alias. */
void sk_dispatch_347ce8(void){ sk_f_001dccb4(0); }

/* ---- 0x347d60-0x348034: identical fatal-error descriptor builders ----
 * Each returns the 16-byte descriptor { lo = &s_Fatal_error (0x5accd0),
 * hi = 0xb } — the fatal-error tag/kind for a distinct fault class. The
 * 0xb kind (FATAL_ERROR) selects the generic fatal-error log path in the
 * caller. Confidence: medium (string ref s_Fatal_error_005accd0). */

/* FUN_00347d60 @ 0x00347d60   (est. sk_fatal_error_desc_0) */
sk_pair_t sk_dispatch_347d60(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347da8 @ 0x00347da8   (est. sk_fatal_error_desc_1) */
sk_pair_t sk_dispatch_347da8(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347de8 @ 0x00347de8   (est. sk_fatal_error_desc_2) */
sk_pair_t sk_dispatch_347de8(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347e28 @ 0x00347e28   (est. sk_fatal_error_desc_3) */
sk_pair_t sk_dispatch_347e28(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347e74 @ 0x00347e74   (est. sk_fatal_error_desc_4) */
sk_pair_t sk_dispatch_347e74(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347ebc @ 0x00347ebc   (est. sk_fatal_error_desc_5) */
sk_pair_t sk_dispatch_347ebc(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347ef4 @ 0x00347ef4   (est. sk_fatal_error_desc_6) */
sk_pair_t sk_dispatch_347ef4(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347f2c @ 0x00347f2c   (est. sk_fatal_error_desc_7) */
sk_pair_t sk_dispatch_347f2c(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347f74 @ 0x00347f74   (est. sk_fatal_error_desc_8) */
sk_pair_t sk_dispatch_347f74(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347fb4 @ 0x00347fb4   (est. sk_fatal_error_desc_9) */
sk_pair_t sk_dispatch_347fb4(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00347ff4 @ 0x00347ff4   (est. sk_fatal_error_desc_a) */
sk_pair_t sk_dispatch_347ff4(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }
/* FUN_00348034 @ 0x00348034   (est. sk_fatal_error_desc_b) */
sk_pair_t sk_dispatch_348034(void){ return (sk_pair_t){ .lo = 0x005accd0, .hi = 0xb }; }

