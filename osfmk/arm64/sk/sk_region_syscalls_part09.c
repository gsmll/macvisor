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
/* END_EXTERN_BLOCK */

