/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1, arm64e, image
 * base 0) — the cL4 microkernel (cL4 (679.100.61)), seL4-derived. Ground truth: Ghidra FUN_ names
 * + addresses. All names are estimates unless string-matched.
 *
 * Slice 4: 0x1c0000 - 0x1d0000. This is the Swift-runtime-heavy scheduler/thread machinery of
 * the cL4 kernel: mostly thin thunks into shared runtime helpers, no-op Swift runtime hooks
 * (retain/release/access hooks), fatalError traps, and a few larger dispatch/decode routines.
 * Each function body is a faithful transcription of the Ghidra decompile (helper calls, control
 * flow, and constants preserved). seL4/cL4 vocabulary is used for naming.
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "sk_internal.h"

/* 16-byte value pair used by the many Swift-runtime routines that return two
 * registers' worth of data (the classic cL4 {error,status} or {ptr,len} pair). */
typedef struct sk_r4_u128 {
    uint64_t lo;
    uint64_t hi;
} sk_r4_u128_t;

/* Ghidra type aliases used throughout the mechanical transcription. */
typedef uint64_t undefined8;
typedef uint8_t undefined1;
typedef uint64_t undefined;
typedef uint64_t undefined7;
typedef uint8_t byte;
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint64_t ulong;
typedef float float2;
typedef void (*code)(void);        /* Ghidra `code` = function pointer */

/* Ghidra ABS / CONCAT builtins used in the transcription. */
#define ABS(x)      ((x) < 0 ? -(x) : (x))
#define CONCAT71(a,b) ((((uint64_t)(a) & 0x00ffffffffffffffULL) << 8) | ((uint8_t)(b)))
#define CONCAT44(a,b) ((((uint64_t)(a) & 0xffffffffULL) << 32) | ((uint32_t)(b)))
#define CONCAT62(a,b) ((((uint64_t)(a) & 0x0000ffffffffffffULL) << 16) | ((uint16_t)(b)))

/*------------------------------------------------------------------*/
/* Shared runtime helpers referenced from this region (out-of-slice: FUN_ address in the
 * comment). Reconstructed by sibling SK range workers. Many of these are no-op Swift runtime
 * hooks (empty bodies in the binary). */

extern void sk_rt_hook_a();   /* FUN_00354440 no-op */
extern void sk_rt_hook_b();   /* FUN_00354428 no-op */
extern sk_r4_u128_t sk_rt_hook_c();   /* FUN_00353cfc no-op */
extern void sk_rt_hook_d();   /* FUN_00353d14 no-op */
extern void sk_rt_hook_e();   /* FUN_0034b2f8 no-op */
extern void sk_rt_hook_f();   /* FUN_00348fd8 no-op */
extern void sk_rt_hook_g();   /* FUN_0034b908 no-op */
extern void sk_rt_hook_h();   /* FUN_0034c908 no-op */
extern void sk_rt_hook_i();   /* FUN_00349c70 no-op */
extern uint64_t sk_rt_hook_j();   /* FUN_00357e14 no-op */
extern void sk_rt_hook_k();   /* FUN_003517b4 no-op */
extern uint64_t sk_rt_hook_l();   /* FUN_0007c0c4 no-op */
extern sk_r4_u128_t sk_rt_hook_m();   /* FUN_000b43d0 no-op */
extern void sk_rt_hook_n();   /* FUN_0034b07c no-op */
extern uint64_t sk_rt_hook_o();   /* FUN_0034b328 no-op */
extern sk_r4_u128_t sk_rt_hook_p();   /* FUN_0034b5bc no-op */
extern void sk_rt_hook_q();   /* FUN_0034c998 no-op */
extern void sk_rt_hook_r();   /* FUN_0034dae8 no-op */
extern void sk_rt_hook_s();   /* FUN_0034f4d4 no-op */
extern void sk_rt_hook_t();   /* FUN_0034bccc no-op */
extern void sk_rt_hook_u();   /* FUN_0034a260 no-op */
extern void sk_rt_hook_v();   /* FUN_0034a274 no-op */
extern void sk_rt_hook_w();   /* FUN_0034a2f8 no-op */
extern void sk_rt_hook_x();   /* FUN_0034ce58 no-op */
extern void sk_rt_hook_y();   /* FUN_0034ce78 no-op */
extern void sk_rt_hook_z();   /* FUN_00343a30 no-op */

/* Swift runtime fatalError and tag machinery. */
extern void sk_fatal_error(void *msg, unsigned long len, unsigned long n,
                           unsigned long a, unsigned long b, void *file,
                           unsigned long flen, unsigned long m) __attribute__((noreturn)); /* FUN_001afa84 */
extern sk_r4_u128_t sk_fatal_msg_tag(void);                          /* FUN_003495cc */

/* Allocator / lock / refcount primitives. */
extern void *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void sk_free(void *ptr);                                      /* FUN_0036b118 */
extern unsigned long sk_alloc_pages(unsigned long size, unsigned long tag); /* FUN_0036b270 */
extern unsigned long sk_object_lock(unsigned long a, unsigned long b, unsigned long c,
                                    void *d1, void *d2);             /* FUN_00377824 */
extern unsigned long sk_lock_ref(unsigned long a);                   /* FUN_00377bec */
extern void *sk_current_tcb(void);                                   /* FUN_000867ec */
extern void *sk_cpu(void);                                           /* FUN_0008e518 */
extern void sk_swift_release(void *obj);                             /* FUN_000026e8 */
extern void sk_masked_free(unsigned long ptr);                       /* FUN_003a25d4 */
extern uint64_t sk_enum_err();                            /* FUN_0006e778 */
extern uint64_t sk_rt_dispatch();                                    /* FUN_00310d68 */
extern void *sk_rt_desc(void);                                       /* FUN_00002534 */
extern void sk_rt_slot(void);                                        /* FUN_0007c1a4 */
extern void sk_rt_slot2(void);                                       /* FUN_0034b7c8 */
extern void sk_rt_slot3(void);                                       /* FUN_0034a390 */

/* Remaining out-of-slice helpers (one-line extern each; FUN_ address in comment). */
extern void sk_h_00019858(void);  /* FUN_00019858 out-of-slice */
extern void sk_h_0006a4c0(uint64_t a1, uint64_t a2);  /* FUN_0006a4c0 out-of-slice */
extern void sk_h_0006a4f0(void);  /* FUN_0006a4f0 out-of-slice */
extern void sk_h_0006a668(uint64_t a1);  /* FUN_0006a668 out-of-slice */
extern void sk_h_0006b42c(void);  /* FUN_0006b42c out-of-slice */
extern void sk_h_0006b6f4(void);  /* FUN_0006b6f4 out-of-slice */
extern void sk_h_0006f6b4(void);  /* FUN_0006f6b4 out-of-slice */
extern void sk_h_00077070(uint64_t a1, uint64_t a2);  /* FUN_00077070 out-of-slice */
extern void sk_h_0007767c(uint64_t a1);  /* FUN_0007767c out-of-slice */
extern sk_r4_u128_t sk_h_00077698();  /* FUN_00077698 out-of-slice */
extern void sk_h_0007b384(uint64_t a1);  /* FUN_0007b384 out-of-slice */
extern long sk_h_0007c198();  /* FUN_0007c198 out-of-slice */
extern sk_r4_u128_t sk_h_0007c1c4();  /* FUN_0007c1c4 out-of-slice */
extern void sk_h_000836a4(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_000836a4 out-of-slice */
extern void sk_h_000839d8(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);  /* FUN_000839d8 out-of-slice */
extern int sk_h_000839f8();  /* FUN_000839f8 out-of-slice */
extern void sk_h_0008409c(void);  /* FUN_0008409c out-of-slice */
extern void sk_h_00084174(uint64_t a1);  /* FUN_00084174 out-of-slice */
extern void sk_h_00084180(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00084180 out-of-slice */
extern sk_r4_u128_t sk_h_0008dae4();  /* FUN_0008dae4 out-of-slice */
extern sk_r4_u128_t sk_h_0008e388();  /* FUN_0008e388 out-of-slice */
extern void sk_h_0008e500(uint64_t a1, uint64_t a2);  /* FUN_0008e500 out-of-slice */
extern void sk_h_0008e5d8(void);  /* FUN_0008e5d8 out-of-slice */
extern void sk_h_0009461c(void);  /* FUN_0009461c out-of-slice */
extern void sk_h_0009e234(uint64_t a1);  /* FUN_0009e234 out-of-slice */
extern void sk_h_000a649c(uint64_t a1);  /* FUN_000a649c out-of-slice */
extern void sk_h_000a6bb8(uint64_t a1);  /* FUN_000a6bb8 out-of-slice */
extern sk_r4_u128_t sk_h_000a6e14();  /* FUN_000a6e14 out-of-slice */
extern void sk_h_000a6f88(void);  /* FUN_000a6f88 out-of-slice */
extern void sk_h_000b077c(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_000b077c out-of-slice */
extern void sk_h_000b43e8(void);  /* FUN_000b43e8 out-of-slice */
extern void sk_h_000b4594(void);  /* FUN_000b4594 out-of-slice */
extern void sk_h_000b45b0(uint64_t a1);  /* FUN_000b45b0 out-of-slice */
extern void sk_h_000bd3a4(uint64_t a1);  /* FUN_000bd3a4 out-of-slice */
extern void sk_h_000dbc54(uint64_t a1);  /* FUN_000dbc54 out-of-slice */
extern void sk_h_000dbcc8(uint64_t a1, uint64_t a2);  /* FUN_000dbcc8 out-of-slice */
extern void sk_h_000dbd0c(uint64_t a1);  /* FUN_000dbd0c out-of-slice */
extern uint64_t sk_h_000dbdf4();  /* FUN_000dbdf4 out-of-slice */
extern void sk_h_000dbe70(uint64_t a1);  /* FUN_000dbe70 out-of-slice */
extern void sk_h_000e15d8(void);  /* FUN_000e15d8 out-of-slice */
extern sk_r4_u128_t sk_h_000e72b0();  /* FUN_000e72b0 out-of-slice */
extern void sk_h_000ec044(void);  /* FUN_000ec044 out-of-slice */
extern void sk_h_000f5e08(void);  /* FUN_000f5e08 out-of-slice */
extern void sk_h_00100c38(uint64_t a1);  /* FUN_00100c38 out-of-slice */
extern void sk_h_0011aa70(void);  /* FUN_0011aa70 out-of-slice */
extern void sk_h_00163418(uint64_t a1);  /* FUN_00163418 out-of-slice */
extern void sk_h_0017e880(void);  /* FUN_0017e880 out-of-slice */
extern void sk_h_0019de9c(void);  /* FUN_0019de9c out-of-slice */
extern void sk_h_0019dfc4(void);  /* FUN_0019dfc4 out-of-slice */
extern void sk_h_0019ea20(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_0019ea20 out-of-slice */
extern void sk_h_001a0a70(void);  /* FUN_001a0a70 out-of-slice */
extern void sk_h_001a18f8(uint64_t a1);  /* FUN_001a18f8 out-of-slice */
extern sk_r4_u128_t sk_h_001a89a8();  /* FUN_001a89a8 out-of-slice */
extern void sk_h_001afe4c(void);  /* FUN_001afe4c out-of-slice */
extern void sk_h_001ba83c(void);  /* FUN_001ba83c out-of-slice */
extern void sk_h_001bb234(uint64_t a1);  /* FUN_001bb234 out-of-slice */
extern void sk_h_001bdb28(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5);  /* FUN_001bdb28 out-of-slice */
extern sk_r4_u128_t sk_h_001d9840();  /* FUN_001d9840 out-of-slice */
extern void sk_h_001dc430(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_001dc430 out-of-slice */
extern sk_r4_u128_t sk_h_001e4cbc();  /* FUN_001e4cbc out-of-slice */
extern void sk_h_001efdc4(void);  /* FUN_001efdc4 out-of-slice */
extern uint64_t sk_h_001efe44();  /* FUN_001efe44 out-of-slice */
extern void sk_h_001f6b30(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5);  /* FUN_001f6b30 out-of-slice */
extern void sk_h_001fca54(uint64_t a1, uint64_t a2);  /* FUN_001fca54 out-of-slice */
extern void sk_h_00205844(uint64_t a1, uint64_t a2);  /* FUN_00205844 out-of-slice */
extern void sk_h_00208418(uint64_t a1, uint64_t a2);  /* FUN_00208418 out-of-slice */
extern void sk_h_00229464(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00229464 out-of-slice */
extern void sk_h_0022d1b4(uint64_t a1, uint64_t a2);  /* FUN_0022d1b4 out-of-slice */
extern void sk_h_002364dc(void);  /* FUN_002364dc out-of-slice */
extern void sk_h_00267820(void);  /* FUN_00267820 out-of-slice */
extern void sk_h_0026aa7c(void);  /* FUN_0026aa7c out-of-slice */
extern void sk_h_0028adc4(void);  /* FUN_0028adc4 out-of-slice */
extern long sk_h_002a218c();  /* FUN_002a218c out-of-slice */
extern void sk_h_002a2698(void);  /* FUN_002a2698 out-of-slice */
extern void sk_h_002a2748(void);  /* FUN_002a2748 out-of-slice */
extern void sk_h_002a4c98(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);  /* FUN_002a4c98 out-of-slice */
extern sk_r4_u128_t sk_h_002a9ba8();  /* FUN_002a9ba8 out-of-slice */
extern void sk_h_002b2078(void);  /* FUN_002b2078 out-of-slice */
extern void sk_h_002e7eb4(uint64_t a1, uint64_t a2);  /* FUN_002e7eb4 out-of-slice */
extern void sk_h_002e9850(uint64_t a1, uint64_t a2);  /* FUN_002e9850 out-of-slice */
extern void sk_h_003198fc(uint64_t a1);  /* FUN_003198fc out-of-slice */
extern void sk_h_00319a14(void);  /* FUN_00319a14 out-of-slice */
extern uint64_t sk_h_00319a4c();  /* FUN_00319a4c out-of-slice */
extern void sk_h_00319a90(uint64_t a1);  /* FUN_00319a90 out-of-slice */
extern uint64_t sk_h_00319aec();  /* FUN_00319aec out-of-slice */
extern void sk_h_00319b1c(uint64_t a1);  /* FUN_00319b1c out-of-slice */
extern uint64_t sk_h_00319b4c();  /* FUN_00319b4c out-of-slice */
extern uint64_t sk_h_00319b7c();  /* FUN_00319b7c out-of-slice */
extern uint64_t sk_h_00319bac();  /* FUN_00319bac out-of-slice */
extern void sk_h_00319bdc(void);  /* FUN_00319bdc out-of-slice */
extern uint64_t sk_h_00319c0c();  /* FUN_00319c0c out-of-slice */
extern void sk_h_00319c3c(void);  /* FUN_00319c3c out-of-slice */
extern void sk_h_0031a0ec(void);  /* FUN_0031a0ec out-of-slice */
extern void sk_h_0031a11c(void);  /* FUN_0031a11c out-of-slice */
extern uint64_t sk_h_0031a14c();  /* FUN_0031a14c out-of-slice */
extern void sk_h_0031a17c(uint64_t a1);  /* FUN_0031a17c out-of-slice */
extern void sk_h_0031a1ac(void);  /* FUN_0031a1ac out-of-slice */
extern sk_r4_u128_t sk_h_0031a1dc();  /* FUN_0031a1dc out-of-slice */
extern void sk_h_0031a1f4(uint64_t a1, uint64_t a2);  /* FUN_0031a1f4 out-of-slice */
extern void sk_h_0031a26c(uint64_t a1);  /* FUN_0031a26c out-of-slice */
extern void sk_h_0031a2b4(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_0031a2b4 out-of-slice */
extern uint64_t sk_h_0031a2cc();  /* FUN_0031a2cc out-of-slice */
extern void sk_h_0031a2fc(uint64_t a1);  /* FUN_0031a2fc out-of-slice */
extern void sk_h_0031a32c(uint64_t a1);  /* FUN_0031a32c out-of-slice */
extern void sk_h_0031a35c(uint64_t a1);  /* FUN_0031a35c out-of-slice */
extern void sk_h_0031a38c(void);  /* FUN_0031a38c out-of-slice */
extern void sk_h_0031a44c(void);  /* FUN_0031a44c out-of-slice */
extern void sk_h_0031a4ac(void);  /* FUN_0031a4ac out-of-slice */
extern void sk_h_0031a56c(void);  /* FUN_0031a56c out-of-slice */
extern void sk_h_0031a5dc(uint64_t a1);  /* FUN_0031a5dc out-of-slice */
extern void sk_h_0031a60c(uint64_t a1);  /* FUN_0031a60c out-of-slice */
extern void sk_h_0031a6cc(uint64_t a1);  /* FUN_0031a6cc out-of-slice */
extern void sk_h_0031b2bc(uint64_t a1);  /* FUN_0031b2bc out-of-slice */
extern void sk_h_0031b46c(void);  /* FUN_0031b46c out-of-slice */
extern void sk_h_0031bc70(uint64_t a1);  /* FUN_0031bc70 out-of-slice */
extern uint64_t sk_h_0034310c();  /* FUN_0034310c out-of-slice */
extern void sk_h_00343250(uint64_t a1);  /* FUN_00343250 out-of-slice */
extern void sk_h_00343640(uint64_t a1);  /* FUN_00343640 out-of-slice */
extern void sk_h_00344d4c(uint64_t a1, uint64_t a2);  /* FUN_00344d4c out-of-slice */
extern void sk_h_00347e28(void);  /* FUN_00347e28 out-of-slice */
extern void sk_h_00348160(void);  /* FUN_00348160 out-of-slice */
extern void sk_h_00348304(void);  /* FUN_00348304 out-of-slice */
extern void sk_h_0034846c(void);  /* FUN_0034846c out-of-slice */
extern void sk_h_003484b4(void);  /* FUN_003484b4 out-of-slice */
extern sk_r4_u128_t sk_h_00348730();  /* FUN_00348730 out-of-slice */
extern uint64_t sk_h_00348758();  /* FUN_00348758 out-of-slice */
extern void sk_h_00348898(uint64_t a1);  /* FUN_00348898 out-of-slice */
extern void sk_h_003489c0(void);  /* FUN_003489c0 out-of-slice */
extern void sk_h_00348a18(void);  /* FUN_00348a18 out-of-slice */
extern void sk_h_00348a34(void);  /* FUN_00348a34 out-of-slice */
extern void sk_h_00348a80(void);  /* FUN_00348a80 out-of-slice */
extern void sk_h_00348abc(void);  /* FUN_00348abc out-of-slice */
extern void sk_h_00348cd0(void);  /* FUN_00348cd0 out-of-slice */
extern void sk_h_00348ce8(void);  /* FUN_00348ce8 out-of-slice */
extern void sk_h_00348d4c(void);  /* FUN_00348d4c out-of-slice */
extern void sk_h_00348d64(void);  /* FUN_00348d64 out-of-slice */
extern void sk_h_00348d7c(void);  /* FUN_00348d7c out-of-slice */
extern void sk_h_00348e18(void);  /* FUN_00348e18 out-of-slice */
extern void sk_h_00348e48(void);  /* FUN_00348e48 out-of-slice */
extern void sk_h_00348e60(void);  /* FUN_00348e60 out-of-slice */
extern long sk_h_00348f50();  /* FUN_00348f50 out-of-slice */
extern void sk_h_00349068(void);  /* FUN_00349068 out-of-slice */
extern void sk_h_00349150(void);  /* FUN_00349150 out-of-slice */
extern void sk_h_003493ac(void);  /* FUN_003493ac out-of-slice */
extern void sk_h_003493c4(void);  /* FUN_003493c4 out-of-slice */
extern void sk_h_0034945c(void);  /* FUN_0034945c out-of-slice */
extern long sk_h_0034947c();  /* FUN_0034947c out-of-slice */
extern void sk_h_00349494(void);  /* FUN_00349494 out-of-slice */
extern void sk_h_003494e8(void);  /* FUN_003494e8 out-of-slice */
extern void sk_h_00349580(uint64_t a1);  /* FUN_00349580 out-of-slice */
extern void sk_h_00349600(void);  /* FUN_00349600 out-of-slice */
extern void sk_h_00349658(void);  /* FUN_00349658 out-of-slice */
extern void sk_h_00349720(void);  /* FUN_00349720 out-of-slice */
extern void sk_h_00349734(void);  /* FUN_00349734 out-of-slice */
extern void sk_h_00349788(void);  /* FUN_00349788 out-of-slice */
extern long sk_h_003497b4();  /* FUN_003497b4 out-of-slice */
extern void sk_h_003497c8(uint64_t a1, uint64_t a2);  /* FUN_003497c8 out-of-slice */
extern void sk_h_003497ec(void);  /* FUN_003497ec out-of-slice */
extern void sk_h_0034995c(uint64_t a1);  /* FUN_0034995c out-of-slice */
extern void sk_h_003499b4(void);  /* FUN_003499b4 out-of-slice */
extern void sk_h_003499c8(void);  /* FUN_003499c8 out-of-slice */
extern void sk_h_003499f0(void);  /* FUN_003499f0 out-of-slice */
extern void sk_h_00349a68(void);  /* FUN_00349a68 out-of-slice */
extern void sk_h_00349b00(void);  /* FUN_00349b00 out-of-slice */
extern void sk_h_00349b3c(void);  /* FUN_00349b3c out-of-slice */
extern void sk_h_00349c14(void);  /* FUN_00349c14 out-of-slice */
extern uint64_t sk_h_00349cbc();  /* FUN_00349cbc out-of-slice */
extern void sk_h_00349e54(void);  /* FUN_00349e54 out-of-slice */
extern void sk_h_00349f3c(void);  /* FUN_00349f3c out-of-slice */
extern void sk_h_0034a0e0(void);  /* FUN_0034a0e0 out-of-slice */
extern void sk_h_0034a100(void);  /* FUN_0034a100 out-of-slice */
extern void sk_h_0034a1e0(uint64_t a1);  /* FUN_0034a1e0 out-of-slice */
extern void sk_h_0034a1f8(void);  /* FUN_0034a1f8 out-of-slice */
extern void sk_h_0034a210(void);  /* FUN_0034a210 out-of-slice */
extern sk_r4_u128_t sk_h_0034a540();  /* FUN_0034a540 out-of-slice */
extern void sk_h_0034a558(void);  /* FUN_0034a558 out-of-slice */
extern void sk_h_0034a570(void);  /* FUN_0034a570 out-of-slice */
extern void sk_h_0034a674(void);  /* FUN_0034a674 out-of-slice */
extern void sk_h_0034a798(void);  /* FUN_0034a798 out-of-slice */
extern void sk_h_0034a7ac(void);  /* FUN_0034a7ac out-of-slice */
extern void sk_h_0034a848(void);  /* FUN_0034a848 out-of-slice */
extern void sk_h_0034a868(uint64_t a1);  /* FUN_0034a868 out-of-slice */
extern void sk_h_0034a8cc(void);  /* FUN_0034a8cc out-of-slice */
extern void sk_h_0034a900(void);  /* FUN_0034a900 out-of-slice */
extern void sk_h_0034aa9c(void);  /* FUN_0034aa9c out-of-slice */
extern void sk_h_0034ab10(void);  /* FUN_0034ab10 out-of-slice */
extern void sk_h_0034ab30(void);  /* FUN_0034ab30 out-of-slice */
extern void sk_h_0034ac64(void);  /* FUN_0034ac64 out-of-slice */
extern void sk_h_0034ad20(uint64_t a1);  /* FUN_0034ad20 out-of-slice */
extern void sk_h_0034ad8c(uint64_t a1);  /* FUN_0034ad8c out-of-slice */
extern void sk_h_0034aed0(void);  /* FUN_0034aed0 out-of-slice */
extern void sk_h_0034aee4(void);  /* FUN_0034aee4 out-of-slice */
extern void sk_h_0034af30(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_0034af30 out-of-slice */
extern void sk_h_0034b014(void);  /* FUN_0034b014 out-of-slice */
extern void sk_h_0034b05c(void);  /* FUN_0034b05c out-of-slice */
extern void sk_h_0034b1a0(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_0034b1a0 out-of-slice */
extern void sk_h_0034b2c8(uint64_t a1);  /* FUN_0034b2c8 out-of-slice */
extern void sk_h_0034b3c8(void);  /* FUN_0034b3c8 out-of-slice */
extern void sk_h_0034b3d8(void);  /* FUN_0034b3d8 out-of-slice */
extern void sk_h_0034b440(uint64_t a1);  /* FUN_0034b440 out-of-slice */
extern sk_r4_u128_t sk_h_0034b480();  /* FUN_0034b480 out-of-slice */
extern void sk_h_0034b4c0(void);  /* FUN_0034b4c0 out-of-slice */
extern void sk_h_0034b5e8(void);  /* FUN_0034b5e8 out-of-slice */
extern void sk_h_0034b690(void);  /* FUN_0034b690 out-of-slice */
extern void sk_h_0034b758(void);  /* FUN_0034b758 out-of-slice */
extern void sk_h_0034b778(void);  /* FUN_0034b778 out-of-slice */
extern void sk_h_0034b824(uint64_t a1);  /* FUN_0034b824 out-of-slice */
extern void sk_h_0034b87c(void);  /* FUN_0034b87c out-of-slice */
extern void sk_h_0034b8bc(void);  /* FUN_0034b8bc out-of-slice */
extern sk_r4_u128_t sk_h_0034b8cc();  /* FUN_0034b8cc out-of-slice */
extern void sk_h_0034b960(void);  /* FUN_0034b960 out-of-slice */
extern void sk_h_0034b980(void);  /* FUN_0034b980 out-of-slice */
extern void sk_h_0034ba48(void);  /* FUN_0034ba48 out-of-slice */
extern void sk_h_0034ba68(void);  /* FUN_0034ba68 out-of-slice */
extern void sk_h_0034ba78(void);  /* FUN_0034ba78 out-of-slice */
extern void sk_h_0034baa8(void);  /* FUN_0034baa8 out-of-slice */
extern void sk_h_0034bab8(void);  /* FUN_0034bab8 out-of-slice */
extern void sk_h_0034bbc8(void);  /* FUN_0034bbc8 out-of-slice */
extern void sk_h_0034bc24(void);  /* FUN_0034bc24 out-of-slice */
extern void sk_h_0034bc38(uint64_t a1);  /* FUN_0034bc38 out-of-slice */
extern void sk_h_0034bc6c(void);  /* FUN_0034bc6c out-of-slice */
extern void sk_h_0034bc94(uint64_t a1);  /* FUN_0034bc94 out-of-slice */
extern void sk_h_0034bcf0(void);  /* FUN_0034bcf0 out-of-slice */
extern void sk_h_0034bd30(void);  /* FUN_0034bd30 out-of-slice */
extern void sk_h_0034bd90(void);  /* FUN_0034bd90 out-of-slice */
extern void sk_h_0034bddc(void);  /* FUN_0034bddc out-of-slice */
extern void sk_h_0034beb4(void);  /* FUN_0034beb4 out-of-slice */
extern uint64_t sk_h_0034bf64();  /* FUN_0034bf64 out-of-slice */
extern void sk_h_0034c034(void);  /* FUN_0034c034 out-of-slice */
extern void sk_h_0034c094(uint64_t a1);  /* FUN_0034c094 out-of-slice */
extern void sk_h_0034c0a4(void);  /* FUN_0034c0a4 out-of-slice */
extern void sk_h_0034c130(void);  /* FUN_0034c130 out-of-slice */
extern void sk_h_0034c1a8(void);  /* FUN_0034c1a8 out-of-slice */
extern void sk_h_0034c1bc(uint64_t a1);  /* FUN_0034c1bc out-of-slice */
extern void sk_h_0034c1d0(void);  /* FUN_0034c1d0 out-of-slice */
extern void sk_h_0034c290(void);  /* FUN_0034c290 out-of-slice */
extern void sk_h_0034c2c8(void);  /* FUN_0034c2c8 out-of-slice */
extern void sk_h_0034c330(void);  /* FUN_0034c330 out-of-slice */
extern void sk_h_0034c3a0(void);  /* FUN_0034c3a0 out-of-slice */
extern void sk_h_0034c4bc(void);  /* FUN_0034c4bc out-of-slice */
extern void sk_h_0034c51c(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_0034c51c out-of-slice */
extern void sk_h_0034c58c(uint64_t a1);  /* FUN_0034c58c out-of-slice */
extern void sk_h_0034c5bc(void);  /* FUN_0034c5bc out-of-slice */
extern void sk_h_0034c5dc(void);  /* FUN_0034c5dc out-of-slice */
extern void sk_h_0034c6e4(uint64_t a1);  /* FUN_0034c6e4 out-of-slice */
extern void sk_h_0034c8b8(void);  /* FUN_0034c8b8 out-of-slice */
extern void sk_h_0034c8f8(void);  /* FUN_0034c8f8 out-of-slice */
extern void sk_h_0034c960(void);  /* FUN_0034c960 out-of-slice */
extern void sk_h_0034c9f8(void);  /* FUN_0034c9f8 out-of-slice */
extern void sk_h_0034ca18(uint64_t a1);  /* FUN_0034ca18 out-of-slice */
extern void sk_h_0034ca38(void);  /* FUN_0034ca38 out-of-slice */
extern void sk_h_0034cb24(void);  /* FUN_0034cb24 out-of-slice */
extern void sk_h_0034cb38(void);  /* FUN_0034cb38 out-of-slice */
extern void sk_h_0034cb4c(void);  /* FUN_0034cb4c out-of-slice */
extern void sk_h_0034cb74(void);  /* FUN_0034cb74 out-of-slice */
extern void sk_h_0034cca8(void);  /* FUN_0034cca8 out-of-slice */
extern void sk_h_0034cd68(void);  /* FUN_0034cd68 out-of-slice */
extern void sk_h_0034ce68(void);  /* FUN_0034ce68 out-of-slice */
extern void sk_h_0034cf94(void);  /* FUN_0034cf94 out-of-slice */
extern void sk_h_0034cfb4(void);  /* FUN_0034cfb4 out-of-slice */
extern void sk_h_0034cfc4(void);  /* FUN_0034cfc4 out-of-slice */
extern void sk_h_0034d044(uint64_t a1);  /* FUN_0034d044 out-of-slice */
extern uint sk_h_0034d0d0();  /* FUN_0034d0d0 out-of-slice */
extern void sk_h_0034d0e0(uint64_t a1);  /* FUN_0034d0e0 out-of-slice */
extern void sk_h_0034d1b0(void);  /* FUN_0034d1b0 out-of-slice */
extern void sk_h_0034d1e0(uint64_t a1, uint64_t a2);  /* FUN_0034d1e0 out-of-slice */
extern void sk_h_0034d2b4(void);  /* FUN_0034d2b4 out-of-slice */
extern void sk_h_0034d384(void);  /* FUN_0034d384 out-of-slice */
extern void sk_h_0034d394(void);  /* FUN_0034d394 out-of-slice */
extern sk_r4_u128_t sk_h_0034d3a4();  /* FUN_0034d3a4 out-of-slice */
extern void sk_h_0034d464(void);  /* FUN_0034d464 out-of-slice */
extern void sk_h_0034d4e8(uint64_t a1);  /* FUN_0034d4e8 out-of-slice */
extern void sk_h_0034d610(void);  /* FUN_0034d610 out-of-slice */
extern void sk_h_0034d6c8(uint64_t a1);  /* FUN_0034d6c8 out-of-slice */
extern uint64_t sk_h_0034d6d8();  /* FUN_0034d6d8 out-of-slice */
extern void sk_h_0034d708(void);  /* FUN_0034d708 out-of-slice */
extern void sk_h_0034d868(void);  /* FUN_0034d868 out-of-slice */
extern void sk_h_0034d914(void);  /* FUN_0034d914 out-of-slice */
extern void sk_h_0034d9f8(void);  /* FUN_0034d9f8 out-of-slice */
extern void sk_h_0034da08(uint64_t a1);  /* FUN_0034da08 out-of-slice */
extern void sk_h_0034da28(uint64_t a1);  /* FUN_0034da28 out-of-slice */
extern void sk_h_0034da48(void);  /* FUN_0034da48 out-of-slice */
extern void sk_h_0034da78(void);  /* FUN_0034da78 out-of-slice */
extern void sk_h_0034daa8(void);  /* FUN_0034daa8 out-of-slice */
extern void sk_h_0034db48(void);  /* FUN_0034db48 out-of-slice */
extern void sk_h_0034db58(void);  /* FUN_0034db58 out-of-slice */
extern void sk_h_0034dba8(uint64_t a1, uint64_t a2);  /* FUN_0034dba8 out-of-slice */
extern void sk_h_0034dbc8(void);  /* FUN_0034dbc8 out-of-slice */
extern void sk_h_0034dc3c(void);  /* FUN_0034dc3c out-of-slice */
extern void sk_h_0034dce4(uint64_t a1, uint64_t a2);  /* FUN_0034dce4 out-of-slice */
extern void sk_h_0034dcfc(void);  /* FUN_0034dcfc out-of-slice */
extern void sk_h_0034dd4c(void);  /* FUN_0034dd4c out-of-slice */
extern void sk_h_0034dd84(uint64_t a1);  /* FUN_0034dd84 out-of-slice */
extern sk_r4_u128_t sk_h_0034dda0();  /* FUN_0034dda0 out-of-slice */
extern void sk_h_0034de14(uint64_t a1);  /* FUN_0034de14 out-of-slice */
extern void sk_h_0034dec4(void);  /* FUN_0034dec4 out-of-slice */
extern void sk_h_0034dfe4(void);  /* FUN_0034dfe4 out-of-slice */
extern sk_r4_u128_t sk_h_0034e044();  /* FUN_0034e044 out-of-slice */
extern void sk_h_0034e0d4(void);  /* FUN_0034e0d4 out-of-slice */
extern void sk_h_0034e0e4(void);  /* FUN_0034e0e4 out-of-slice */
extern void sk_h_0034e120(uint64_t a1);  /* FUN_0034e120 out-of-slice */
extern void sk_h_0034e1ec(uint64_t a1);  /* FUN_0034e1ec out-of-slice */
extern void sk_h_0034e374(uint64_t a1);  /* FUN_0034e374 out-of-slice */
extern void sk_h_0034e3ac(void);  /* FUN_0034e3ac out-of-slice */
extern void sk_h_0034e56c(void);  /* FUN_0034e56c out-of-slice */
extern void sk_h_0034e69c(void);  /* FUN_0034e69c out-of-slice */
extern void sk_h_0034e6ac(void);  /* FUN_0034e6ac out-of-slice */
extern void sk_h_0034e6fc(void);  /* FUN_0034e6fc out-of-slice */
extern void sk_h_0034e7a0(uint64_t a1, uint64_t a2);  /* FUN_0034e7a0 out-of-slice */
extern void sk_h_0034e8d4(void);  /* FUN_0034e8d4 out-of-slice */
extern void sk_h_0034e8e8(void);  /* FUN_0034e8e8 out-of-slice */
extern void sk_h_0034e910(void);  /* FUN_0034e910 out-of-slice */
extern void sk_h_0034ea18(void);  /* FUN_0034ea18 out-of-slice */
extern void sk_h_0034eb54(void);  /* FUN_0034eb54 out-of-slice */
extern void sk_h_0034eb74(uint64_t a1);  /* FUN_0034eb74 out-of-slice */
extern void sk_h_0034eb84(void);  /* FUN_0034eb84 out-of-slice */
extern void sk_h_0034ec58(uint64_t a1);  /* FUN_0034ec58 out-of-slice */
extern void sk_h_0034ec68(uint64_t a1);  /* FUN_0034ec68 out-of-slice */
extern void sk_h_0034ec78(void);  /* FUN_0034ec78 out-of-slice */
extern void sk_h_0034ec98(void);  /* FUN_0034ec98 out-of-slice */
extern void sk_h_0034ecb8(void);  /* FUN_0034ecb8 out-of-slice */
extern void sk_h_0034ecc8(void);  /* FUN_0034ecc8 out-of-slice */
extern void sk_h_0034ece8(uint64_t a1, uint64_t a2);  /* FUN_0034ece8 out-of-slice */
extern void sk_h_0034ecf8(void);  /* FUN_0034ecf8 out-of-slice */
extern void sk_h_0034ed18(void);  /* FUN_0034ed18 out-of-slice */
extern void sk_h_0034ed78(void);  /* FUN_0034ed78 out-of-slice */
extern void sk_h_0034ee68(void);  /* FUN_0034ee68 out-of-slice */
extern void sk_h_0034ee88(uint64_t a1);  /* FUN_0034ee88 out-of-slice */
extern void sk_h_0034eef8(void);  /* FUN_0034eef8 out-of-slice */
extern void sk_h_0034ef28(void);  /* FUN_0034ef28 out-of-slice */
extern void sk_h_0034ef38(void);  /* FUN_0034ef38 out-of-slice */
extern void sk_h_0034ef48(void);  /* FUN_0034ef48 out-of-slice */
extern void sk_h_0034ef98(void);  /* FUN_0034ef98 out-of-slice */
extern uint64_t sk_h_0034f064();  /* FUN_0034f064 out-of-slice */
extern void sk_h_0034f078(void);  /* FUN_0034f078 out-of-slice */
extern void sk_h_0034f198(void);  /* FUN_0034f198 out-of-slice */
extern void sk_h_0034f1a8(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_0034f1a8 out-of-slice */
extern void sk_h_0034f21c(uint64_t a1);  /* FUN_0034f21c out-of-slice */
extern void sk_h_0034f23c(void);  /* FUN_0034f23c out-of-slice */
extern long sk_h_0034f264();  /* FUN_0034f264 out-of-slice */
extern void sk_h_0034f354(void);  /* FUN_0034f354 out-of-slice */
extern void sk_h_0034f444(void);  /* FUN_0034f444 out-of-slice */
extern void sk_h_0034f454(void);  /* FUN_0034f454 out-of-slice */
extern void sk_h_0034f484(void);  /* FUN_0034f484 out-of-slice */
extern void sk_h_0034f554(void);  /* FUN_0034f554 out-of-slice */
extern void sk_h_0034f688(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_0034f688 out-of-slice */
extern void sk_h_0034f884(uint64_t a1);  /* FUN_0034f884 out-of-slice */
extern void sk_h_0034f8a8(void);  /* FUN_0034f8a8 out-of-slice */
extern void sk_h_0034f938(void);  /* FUN_0034f938 out-of-slice */
extern void sk_h_0034f948(void);  /* FUN_0034f948 out-of-slice */
extern void sk_h_0034f958(void);  /* FUN_0034f958 out-of-slice */
extern void sk_h_0034f96c(void);  /* FUN_0034f96c out-of-slice */
extern void sk_h_0034f97c(void);  /* FUN_0034f97c out-of-slice */
extern void sk_h_0034f9fc(void);  /* FUN_0034f9fc out-of-slice */
extern void sk_h_0034fa4c(void);  /* FUN_0034fa4c out-of-slice */
extern void sk_h_0034fd5c(void);  /* FUN_0034fd5c out-of-slice */
extern void sk_h_0034ffa8(void);  /* FUN_0034ffa8 out-of-slice */
extern void sk_h_00350028(uint64_t a1);  /* FUN_00350028 out-of-slice */
extern void sk_h_00350058(void);  /* FUN_00350058 out-of-slice */
extern void sk_h_003500d4(void);  /* FUN_003500d4 out-of-slice */
extern void sk_h_0035014c(void);  /* FUN_0035014c out-of-slice */
extern void sk_h_00350210(uint64_t a1);  /* FUN_00350210 out-of-slice */
extern void sk_h_00350288(uint64_t a1);  /* FUN_00350288 out-of-slice */
extern void sk_h_003503d0(void);  /* FUN_003503d0 out-of-slice */
extern void sk_h_003503f8(void);  /* FUN_003503f8 out-of-slice */
extern void sk_h_0035041c(void);  /* FUN_0035041c out-of-slice */
extern void sk_h_00350434(void);  /* FUN_00350434 out-of-slice */
extern void sk_h_00350464(void);  /* FUN_00350464 out-of-slice */
extern void sk_h_00350470(uint64_t a1);  /* FUN_00350470 out-of-slice */
extern void sk_h_003504a0(void);  /* FUN_003504a0 out-of-slice */
extern void sk_h_003504ac(uint64_t a1);  /* FUN_003504ac out-of-slice */
extern sk_r4_u128_t sk_h_003504c4();  /* FUN_003504c4 out-of-slice */
extern sk_r4_u128_t sk_h_003504d0();  /* FUN_003504d0 out-of-slice */
extern sk_r4_u128_t sk_h_003504e8();  /* FUN_003504e8 out-of-slice */
extern sk_r4_u128_t sk_h_0035050c();  /* FUN_0035050c out-of-slice */
extern void sk_h_00350518(uint64_t a1);  /* FUN_00350518 out-of-slice */
extern void sk_h_00350524(uint64_t a1);  /* FUN_00350524 out-of-slice */
extern void sk_h_0035056c(void);  /* FUN_0035056c out-of-slice */
extern sk_r4_u128_t sk_h_0035059c();  /* FUN_0035059c out-of-slice */
extern void sk_h_003505b0(void);  /* FUN_003505b0 out-of-slice */
extern void sk_h_003505c4(void);  /* FUN_003505c4 out-of-slice */
extern void sk_h_003505d0(void);  /* FUN_003505d0 out-of-slice */
extern sk_r4_u128_t sk_h_003505e8();  /* FUN_003505e8 out-of-slice */
extern void sk_h_0035060c(uint64_t a1);  /* FUN_0035060c out-of-slice */
extern void sk_h_00350618(void);  /* FUN_00350618 out-of-slice */
extern void sk_h_00350624(uint64_t a1);  /* FUN_00350624 out-of-slice */
extern void sk_h_00350630(uint64_t a1);  /* FUN_00350630 out-of-slice */
extern uint64_t sk_h_00350648();  /* FUN_00350648 out-of-slice */
extern uint64_t sk_h_0035066c();  /* FUN_0035066c out-of-slice */
extern void sk_h_00350720(void);  /* FUN_00350720 out-of-slice */
extern sk_r4_u128_t sk_h_0035072c();  /* FUN_0035072c out-of-slice */
extern void sk_h_00350738(uint64_t a1);  /* FUN_00350738 out-of-slice */
extern void sk_h_00350750(uint64_t a1);  /* FUN_00350750 out-of-slice */
extern void sk_h_00350768(void);  /* FUN_00350768 out-of-slice */
extern void sk_h_00350774(uint64_t a1, uint64_t a2);  /* FUN_00350774 out-of-slice */
extern sk_r4_u128_t sk_h_00350798();  /* FUN_00350798 out-of-slice */
extern void sk_h_003507c8(uint64_t a1);  /* FUN_003507c8 out-of-slice */
extern void sk_h_0035084c(uint64_t a1);  /* FUN_0035084c out-of-slice */
extern void sk_h_00350884(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00350884 out-of-slice */
extern void sk_h_003508b4(void);  /* FUN_003508b4 out-of-slice */
extern void sk_h_003508cc(uint64_t a1);  /* FUN_003508cc out-of-slice */
extern void sk_h_003508d8(uint64_t a1);  /* FUN_003508d8 out-of-slice */
extern void sk_h_003508e4(void);  /* FUN_003508e4 out-of-slice */
extern void sk_h_003508fc(void);  /* FUN_003508fc out-of-slice */
extern sk_r4_u128_t sk_h_00350914();  /* FUN_00350914 out-of-slice */
extern void sk_h_00350944(uint64_t a1);  /* FUN_00350944 out-of-slice */
extern void sk_h_00350968(uint64_t a1);  /* FUN_00350968 out-of-slice */
extern sk_r4_u128_t sk_h_003509b0();  /* FUN_003509b0 out-of-slice */
extern void sk_h_003509bc(void);  /* FUN_003509bc out-of-slice */
extern void sk_h_003509d4(uint64_t a1);  /* FUN_003509d4 out-of-slice */
extern sk_r4_u128_t sk_h_003509e0();  /* FUN_003509e0 out-of-slice */
extern void sk_h_00350a04(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00350a04 out-of-slice */
extern void sk_h_00350a28(void);  /* FUN_00350a28 out-of-slice */
extern void sk_h_00350a34(uint64_t a1);  /* FUN_00350a34 out-of-slice */
extern void sk_h_00350a40(void);  /* FUN_00350a40 out-of-slice */
extern void sk_h_00350a70(uint64_t a1);  /* FUN_00350a70 out-of-slice */
extern void sk_h_00350a7c(void);  /* FUN_00350a7c out-of-slice */
extern uint64_t sk_h_00350a88();  /* FUN_00350a88 out-of-slice */
extern sk_r4_u128_t sk_h_00350ab8();  /* FUN_00350ab8 out-of-slice */
extern sk_r4_u128_t sk_h_00350af4();  /* FUN_00350af4 out-of-slice */
extern void sk_h_00350b18(void);  /* FUN_00350b18 out-of-slice */
extern void sk_h_00350b48(void);  /* FUN_00350b48 out-of-slice */
extern void sk_h_00350b54(void);  /* FUN_00350b54 out-of-slice */
extern void sk_h_00350b60(uint64_t a1);  /* FUN_00350b60 out-of-slice */
extern void sk_h_00350b6c(uint64_t a1);  /* FUN_00350b6c out-of-slice */
extern void sk_h_00350b78(uint64_t a1);  /* FUN_00350b78 out-of-slice */
extern void sk_h_00350b90(void);  /* FUN_00350b90 out-of-slice */
extern void sk_h_00350b9c(void);  /* FUN_00350b9c out-of-slice */
extern void sk_h_00350bc0(uint64_t a1);  /* FUN_00350bc0 out-of-slice */
extern void sk_h_00350bcc(void);  /* FUN_00350bcc out-of-slice */
extern sk_r4_u128_t sk_h_00350bf0();  /* FUN_00350bf0 out-of-slice */
extern void sk_h_00350bfc(void);  /* FUN_00350bfc out-of-slice */
extern void sk_h_00350c20(uint64_t a1);  /* FUN_00350c20 out-of-slice */
extern void sk_h_00350c38(void);  /* FUN_00350c38 out-of-slice */
extern void sk_h_00350c50(void);  /* FUN_00350c50 out-of-slice */
extern void sk_h_00350c68(uint64_t a1);  /* FUN_00350c68 out-of-slice */
extern void sk_h_00350c8c(uint64_t a1);  /* FUN_00350c8c out-of-slice */
extern void sk_h_00350cf4(uint64_t a1);  /* FUN_00350cf4 out-of-slice */
extern void sk_h_00350df4(void);  /* FUN_00350df4 out-of-slice */
extern void sk_h_00350e54(void);  /* FUN_00350e54 out-of-slice */
extern void sk_h_00350ea4(uint64_t a1);  /* FUN_00350ea4 out-of-slice */
extern void sk_h_00350ec0(void);  /* FUN_00350ec0 out-of-slice */
extern void sk_h_00350ed0(uint64_t a1);  /* FUN_00350ed0 out-of-slice */
extern void sk_h_0035100c(void);  /* FUN_0035100c out-of-slice */
extern void sk_h_0035101c(void);  /* FUN_0035101c out-of-slice */
extern void sk_h_0035102c(void);  /* FUN_0035102c out-of-slice */
extern sk_r4_u128_t sk_h_003510ac();  /* FUN_003510ac out-of-slice */
extern void sk_h_003510d0(uint64_t a1);  /* FUN_003510d0 out-of-slice */
extern void sk_h_003510dc(uint64_t a1);  /* FUN_003510dc out-of-slice */
extern void sk_h_00351118(void);  /* FUN_00351118 out-of-slice */
extern sk_r4_u128_t sk_h_00351160();  /* FUN_00351160 out-of-slice */
extern void sk_h_0035116c(void);  /* FUN_0035116c out-of-slice */
extern sk_r4_u128_t sk_h_003511a8();  /* FUN_003511a8 out-of-slice */
extern void sk_h_003511e4(void);  /* FUN_003511e4 out-of-slice */
extern void sk_h_00351214(uint64_t a1, uint64_t a2);  /* FUN_00351214 out-of-slice */
extern void sk_h_00351220(void);  /* FUN_00351220 out-of-slice */
extern void sk_h_0035122c(void);  /* FUN_0035122c out-of-slice */
extern void sk_h_00351250(void);  /* FUN_00351250 out-of-slice */
extern void sk_h_00351274(uint64_t a1);  /* FUN_00351274 out-of-slice */
extern long sk_h_0035128c();  /* FUN_0035128c out-of-slice */
extern void sk_h_00351298(void);  /* FUN_00351298 out-of-slice */
extern void sk_h_003512c0(void);  /* FUN_003512c0 out-of-slice */
extern void sk_h_00351318(void);  /* FUN_00351318 out-of-slice */
extern void sk_h_00351348(void);  /* FUN_00351348 out-of-slice */
extern sk_r4_u128_t sk_h_00351354();  /* FUN_00351354 out-of-slice */
extern void sk_h_00351360(uint64_t a1);  /* FUN_00351360 out-of-slice */
extern void sk_h_00351384(uint64_t a1);  /* FUN_00351384 out-of-slice */
extern void sk_h_00351390(uint64_t a1);  /* FUN_00351390 out-of-slice */
extern void sk_h_003513a8(void);  /* FUN_003513a8 out-of-slice */
extern void sk_h_003513b4(uint64_t a1, uint64_t a2);  /* FUN_003513b4 out-of-slice */
extern void sk_h_00351408(void);  /* FUN_00351408 out-of-slice */
extern sk_r4_u128_t sk_h_00351450();  /* FUN_00351450 out-of-slice */
extern void sk_h_0035145c(uint64_t a1);  /* FUN_0035145c out-of-slice */
extern void sk_h_0035147c(void);  /* FUN_0035147c out-of-slice */
extern void sk_h_00351494(uint64_t a1);  /* FUN_00351494 out-of-slice */
extern void sk_h_003514e8(uint64_t a1);  /* FUN_003514e8 out-of-slice */
extern void sk_h_00351500(uint64_t a1);  /* FUN_00351500 out-of-slice */
extern void sk_h_00351554(uint64_t a1);  /* FUN_00351554 out-of-slice */
extern void sk_h_0035159c(void);  /* FUN_0035159c out-of-slice */
extern void sk_h_003515a8(void);  /* FUN_003515a8 out-of-slice */
extern void sk_h_003515d8(void);  /* FUN_003515d8 out-of-slice */
extern void sk_h_003515e4(void);  /* FUN_003515e4 out-of-slice */
extern void sk_h_003515f0(void);  /* FUN_003515f0 out-of-slice */
extern void sk_h_003515fc(uint64_t a1, uint64_t a2);  /* FUN_003515fc out-of-slice */
extern void sk_h_0035163c(uint64_t a1);  /* FUN_0035163c out-of-slice */
extern void sk_h_00351660(void);  /* FUN_00351660 out-of-slice */
extern void sk_h_003516cc(void);  /* FUN_003516cc out-of-slice */
extern void sk_h_003516fc(uint64_t a1);  /* FUN_003516fc out-of-slice */
extern sk_r4_u128_t sk_h_0035172c();  /* FUN_0035172c out-of-slice */
extern sk_r4_u128_t sk_h_00351738();  /* FUN_00351738 out-of-slice */
extern sk_r4_u128_t sk_h_003517a8();  /* FUN_003517a8 out-of-slice */
extern void sk_h_0035187c(void);  /* FUN_0035187c out-of-slice */
extern sk_r4_u128_t sk_h_00351888();  /* FUN_00351888 out-of-slice */
extern void sk_h_003518a0(void);  /* FUN_003518a0 out-of-slice */
extern void sk_h_00351978(void);  /* FUN_00351978 out-of-slice */
extern void sk_h_003519a8(void);  /* FUN_003519a8 out-of-slice */
extern uint64_t sk_h_00351a14();  /* FUN_00351a14 out-of-slice */
extern void sk_h_00351a44(void);  /* FUN_00351a44 out-of-slice */
extern void sk_h_00351a50(void);  /* FUN_00351a50 out-of-slice */
extern void sk_h_00351a5c(void);  /* FUN_00351a5c out-of-slice */
extern void sk_h_00351aec(void);  /* FUN_00351aec out-of-slice */
extern void sk_h_00351ba0(uint64_t a1);  /* FUN_00351ba0 out-of-slice */
extern void sk_h_00351c70(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00351c70 out-of-slice */
extern void sk_h_00351cd0(uint64_t a1, uint64_t a2);  /* FUN_00351cd0 out-of-slice */
extern void sk_h_00351d0c(void);  /* FUN_00351d0c out-of-slice */
extern void sk_h_00351d18(void);  /* FUN_00351d18 out-of-slice */
extern sk_r4_u128_t sk_h_00351d24();  /* FUN_00351d24 out-of-slice */
extern void sk_h_00351d9c(void);  /* FUN_00351d9c out-of-slice */
extern uint64_t sk_h_00351db4();  /* FUN_00351db4 out-of-slice */
extern void sk_h_00351dcc(void);  /* FUN_00351dcc out-of-slice */
extern uint64_t sk_h_00351dd8();  /* FUN_00351dd8 out-of-slice */
extern void sk_h_00351de4(void);  /* FUN_00351de4 out-of-slice */
extern void sk_h_00351dfc(void);  /* FUN_00351dfc out-of-slice */
extern sk_r4_u128_t sk_h_00351e08();  /* FUN_00351e08 out-of-slice */
extern void sk_h_00351e3c(uint64_t a1, uint64_t a2);  /* FUN_00351e3c out-of-slice */
extern void sk_h_00351f1c(void);  /* FUN_00351f1c out-of-slice */
extern void sk_h_00351f28(void);  /* FUN_00351f28 out-of-slice */
extern void sk_h_00351f64(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);  /* FUN_00351f64 out-of-slice */
extern void sk_h_00351f70(void);  /* FUN_00351f70 out-of-slice */
extern void sk_h_00352008(void);  /* FUN_00352008 out-of-slice */
extern void sk_h_00352038(uint64_t a1);  /* FUN_00352038 out-of-slice */
extern void sk_h_00352048(uint64_t a1, uint64_t a2);  /* FUN_00352048 out-of-slice */
extern void sk_h_00352058(void);  /* FUN_00352058 out-of-slice */
extern void sk_h_00352068(void);  /* FUN_00352068 out-of-slice */
extern long sk_h_003521a4();  /* FUN_003521a4 out-of-slice */
extern void sk_h_00352370(uint64_t a1);  /* FUN_00352370 out-of-slice */
extern void sk_h_00352474(void);  /* FUN_00352474 out-of-slice */
extern void sk_h_00352480(uint64_t a1, uint64_t a2);  /* FUN_00352480 out-of-slice */
extern sk_r4_u128_t sk_h_003524a4();  /* FUN_003524a4 out-of-slice */
extern void sk_h_003524c8(void);  /* FUN_003524c8 out-of-slice */
extern void sk_h_00352554(uint64_t a1);  /* FUN_00352554 out-of-slice */
extern void sk_h_00352658(void);  /* FUN_00352658 out-of-slice */
extern void sk_h_00352680(uint64_t a1);  /* FUN_00352680 out-of-slice */
extern void sk_h_003527e0(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_003527e0 out-of-slice */
extern void sk_h_0035292c(void);  /* FUN_0035292c out-of-slice */
extern void sk_h_00352938(void);  /* FUN_00352938 out-of-slice */
extern uint64_t sk_h_00352980();  /* FUN_00352980 out-of-slice */
extern void sk_h_00352a34(void);  /* FUN_00352a34 out-of-slice */
extern void sk_h_00352a40(void);  /* FUN_00352a40 out-of-slice */
extern void sk_h_00352a58(void);  /* FUN_00352a58 out-of-slice */
extern void sk_h_00352a70(uint64_t a1);  /* FUN_00352a70 out-of-slice */
extern void sk_h_00352ae4(uint64_t a1, uint64_t a2);  /* FUN_00352ae4 out-of-slice */
extern void sk_h_00352b44(uint64_t a1);  /* FUN_00352b44 out-of-slice */
extern void sk_h_00352b68(uint64_t a1);  /* FUN_00352b68 out-of-slice */
extern void sk_h_00352b74(void);  /* FUN_00352b74 out-of-slice */
extern void sk_h_00352b98(uint64_t a1);  /* FUN_00352b98 out-of-slice */
extern void sk_h_00352c34(void);  /* FUN_00352c34 out-of-slice */
extern void sk_h_00352c80(void);  /* FUN_00352c80 out-of-slice */
extern void sk_h_00352cb0(void);  /* FUN_00352cb0 out-of-slice */
extern void sk_h_00352cc8(void);  /* FUN_00352cc8 out-of-slice */
extern void sk_h_00352cd4(void);  /* FUN_00352cd4 out-of-slice */
extern void sk_h_00352cf8(uint64_t a1);  /* FUN_00352cf8 out-of-slice */
extern void sk_h_00352d88(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);  /* FUN_00352d88 out-of-slice */
extern void sk_h_00352db8(void);  /* FUN_00352db8 out-of-slice */
extern void sk_h_00352de8(void);  /* FUN_00352de8 out-of-slice */
extern void sk_h_00352df4(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00352df4 out-of-slice */
extern void sk_h_00352e00(void);  /* FUN_00352e00 out-of-slice */
extern void sk_h_00352e6c(void);  /* FUN_00352e6c out-of-slice */
extern void sk_h_00352e78(void);  /* FUN_00352e78 out-of-slice */
extern void sk_h_00352f48(uint64_t a1);  /* FUN_00352f48 out-of-slice */
extern long sk_h_00352fd4();  /* FUN_00352fd4 out-of-slice */
extern void sk_h_0035310c(void);  /* FUN_0035310c out-of-slice */
extern void sk_h_00353154(void);  /* FUN_00353154 out-of-slice */
extern void sk_h_003531fc(void);  /* FUN_003531fc out-of-slice */
extern uint64_t sk_h_00353378();  /* FUN_00353378 out-of-slice */
extern long sk_h_00353430();  /* FUN_00353430 out-of-slice */
extern void sk_h_0035345c(void);  /* FUN_0035345c out-of-slice */
extern void sk_h_003534bc(void);  /* FUN_003534bc out-of-slice */
extern void sk_h_003534ec(void);  /* FUN_003534ec out-of-slice */
extern void sk_h_0035351c(void);  /* FUN_0035351c out-of-slice */
extern void sk_h_003535a8(void);  /* FUN_003535a8 out-of-slice */
extern uint64_t sk_h_0035361c();  /* FUN_0035361c out-of-slice */
extern void sk_h_0035368c(void);  /* FUN_0035368c out-of-slice */
extern void sk_h_0035369c(void);  /* FUN_0035369c out-of-slice */
extern void sk_h_003536d0(void);  /* FUN_003536d0 out-of-slice */
extern void sk_h_003536ec(void);  /* FUN_003536ec out-of-slice */
extern void sk_h_003536fc(void);  /* FUN_003536fc out-of-slice */
extern void sk_h_0035370c(void);  /* FUN_0035370c out-of-slice */
extern void sk_h_003537d4(void);  /* FUN_003537d4 out-of-slice */
extern void sk_h_003537fc(void);  /* FUN_003537fc out-of-slice */
extern void sk_h_00353820(void);  /* FUN_00353820 out-of-slice */
extern void sk_h_00353918(void);  /* FUN_00353918 out-of-slice */
extern void sk_h_00353948(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00353948 out-of-slice */
extern void sk_h_0035399c(void);  /* FUN_0035399c out-of-slice */
extern void sk_h_003539e4(void);  /* FUN_003539e4 out-of-slice */
extern void sk_h_00353a24(void);  /* FUN_00353a24 out-of-slice */
extern void sk_h_00353ad8(void);  /* FUN_00353ad8 out-of-slice */
extern void sk_h_00353b40(void);  /* FUN_00353b40 out-of-slice */
extern void sk_h_00353b58(void);  /* FUN_00353b58 out-of-slice */
extern void sk_h_00353b70(uint64_t a1);  /* FUN_00353b70 out-of-slice */
extern void sk_h_00353c30(void);  /* FUN_00353c30 out-of-slice */
extern void sk_h_00353c6c(void);  /* FUN_00353c6c out-of-slice */
extern uint64_t sk_h_00353c78();  /* FUN_00353c78 out-of-slice */
extern void sk_h_00353ccc(void);  /* FUN_00353ccc out-of-slice */
extern void sk_h_00353cf0(void);  /* FUN_00353cf0 out-of-slice */
extern void sk_h_00353dac(uint64_t a1);  /* FUN_00353dac out-of-slice */
extern void sk_h_00353e50(void);  /* FUN_00353e50 out-of-slice */
extern sk_r4_u128_t sk_h_00353e7c();  /* FUN_00353e7c out-of-slice */
extern uint sk_h_00353ee4();  /* FUN_00353ee4 out-of-slice */
extern void sk_h_00353f88(void);  /* FUN_00353f88 out-of-slice */
extern void sk_h_003540ac(uint64_t a1);  /* FUN_003540ac out-of-slice */
extern void sk_h_0035414c(void);  /* FUN_0035414c out-of-slice */
extern void sk_h_00354168(void);  /* FUN_00354168 out-of-slice */
extern void sk_h_00354184(void);  /* FUN_00354184 out-of-slice */
extern void sk_h_003541a0(void);  /* FUN_003541a0 out-of-slice */
extern void sk_h_003541bc(void);  /* FUN_003541bc out-of-slice */
extern void sk_h_003541d8(void);  /* FUN_003541d8 out-of-slice */
extern void sk_h_003541f4(void);  /* FUN_003541f4 out-of-slice */
extern void sk_h_00354210(void);  /* FUN_00354210 out-of-slice */
extern void sk_h_0035422c(void);  /* FUN_0035422c out-of-slice */
extern void sk_h_00354248(void);  /* FUN_00354248 out-of-slice */
extern void sk_h_003542c4(void);  /* FUN_003542c4 out-of-slice */
extern void sk_h_00354318(void);  /* FUN_00354318 out-of-slice */
extern void sk_h_00354324(void);  /* FUN_00354324 out-of-slice */
extern void sk_h_0035437c(void);  /* FUN_0035437c out-of-slice */
extern void sk_h_003543f8(void);  /* FUN_003543f8 out-of-slice */
extern void sk_h_00354570(uint64_t a1);  /* FUN_00354570 out-of-slice */
extern void sk_h_003545d0(void);  /* FUN_003545d0 out-of-slice */
extern void sk_h_00354624(uint64_t a1);  /* FUN_00354624 out-of-slice */
extern void sk_h_00354654(void);  /* FUN_00354654 out-of-slice */
extern void sk_h_003546a8(void);  /* FUN_003546a8 out-of-slice */
extern void sk_h_00354774(void);  /* FUN_00354774 out-of-slice */
extern void sk_h_003547ec(void);  /* FUN_003547ec out-of-slice */
extern void sk_h_00354858(void);  /* FUN_00354858 out-of-slice */
extern void sk_h_003548e8(void);  /* FUN_003548e8 out-of-slice */
extern void sk_h_00354948(uint64_t a1);  /* FUN_00354948 out-of-slice */
extern void sk_h_003549d8(void);  /* FUN_003549d8 out-of-slice */
extern void sk_h_003549e4(void);  /* FUN_003549e4 out-of-slice */
extern void sk_h_00354a00(void);  /* FUN_00354a00 out-of-slice */
extern void sk_h_00354a0c(uint64_t a1);  /* FUN_00354a0c out-of-slice */
extern void sk_h_00354a6c(void);  /* FUN_00354a6c out-of-slice */
extern void sk_h_00354a78(void);  /* FUN_00354a78 out-of-slice */
extern void sk_h_00354ac8(uint64_t a1);  /* FUN_00354ac8 out-of-slice */
extern uint64_t sk_h_00354b5c();  /* FUN_00354b5c out-of-slice */
extern void sk_h_00354b74(void);  /* FUN_00354b74 out-of-slice */
extern void sk_h_00354b8c(void);  /* FUN_00354b8c out-of-slice */
extern void sk_h_00354b98(void);  /* FUN_00354b98 out-of-slice */
extern void sk_h_00354ba4(void);  /* FUN_00354ba4 out-of-slice */
extern void sk_h_00354bd4(void);  /* FUN_00354bd4 out-of-slice */
extern void sk_h_00354c38(void);  /* FUN_00354c38 out-of-slice */
extern void sk_h_00354cd8(void);  /* FUN_00354cd8 out-of-slice */
extern void sk_h_00354d5c(void);  /* FUN_00354d5c out-of-slice */
extern void sk_h_00354ddc(void);  /* FUN_00354ddc out-of-slice */
extern sk_r4_u128_t sk_h_00354e0c();  /* FUN_00354e0c out-of-slice */
extern void sk_h_00354f1c(void);  /* FUN_00354f1c out-of-slice */
extern void sk_h_0035512c(void);  /* FUN_0035512c out-of-slice */
extern void sk_h_003552ac(void);  /* FUN_003552ac out-of-slice */
extern void sk_h_00355374(void);  /* FUN_00355374 out-of-slice */
extern void sk_h_00355384(void);  /* FUN_00355384 out-of-slice */
extern void sk_h_003553a8(void);  /* FUN_003553a8 out-of-slice */
extern void sk_h_003553e4(void);  /* FUN_003553e4 out-of-slice */
extern void sk_h_00355418(uint64_t a1);  /* FUN_00355418 out-of-slice */
extern void sk_h_0035543c(void);  /* FUN_0035543c out-of-slice */
extern void sk_h_0035578c(uint64_t a1);  /* FUN_0035578c out-of-slice */
extern void sk_h_003558a8(void);  /* FUN_003558a8 out-of-slice */
extern void sk_h_00355a14(void);  /* FUN_00355a14 out-of-slice */
extern void sk_h_00355a58(void);  /* FUN_00355a58 out-of-slice */
extern void sk_h_00355bc4(void);  /* FUN_00355bc4 out-of-slice */
extern void sk_h_00355be8(uint64_t a1, uint64_t a2);  /* FUN_00355be8 out-of-slice */
extern void sk_h_00355c1c(void);  /* FUN_00355c1c out-of-slice */
extern void sk_h_00355cc8(void);  /* FUN_00355cc8 out-of-slice */
extern void sk_h_00355d40(void);  /* FUN_00355d40 out-of-slice */
extern void sk_h_00355d6c(void);  /* FUN_00355d6c out-of-slice */
extern void sk_h_00355d90(void);  /* FUN_00355d90 out-of-slice */
extern void sk_h_00355e50(void);  /* FUN_00355e50 out-of-slice */
extern void sk_h_00355e68(void);  /* FUN_00355e68 out-of-slice */
extern void sk_h_00355e74(void);  /* FUN_00355e74 out-of-slice */
extern void sk_h_00355eec(void);  /* FUN_00355eec out-of-slice */
extern void sk_h_00355f04(void);  /* FUN_00355f04 out-of-slice */
extern void sk_h_00355ff4(void);  /* FUN_00355ff4 out-of-slice */
extern void sk_h_003560b4(void);  /* FUN_003560b4 out-of-slice */
extern void sk_h_00356104(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00356104 out-of-slice */
extern void sk_h_003561e8(void);  /* FUN_003561e8 out-of-slice */
extern void sk_h_00356200(void);  /* FUN_00356200 out-of-slice */
extern void sk_h_00356284(void);  /* FUN_00356284 out-of-slice */
extern void sk_h_003562d4(void);  /* FUN_003562d4 out-of-slice */
extern void sk_h_003562e0(void);  /* FUN_003562e0 out-of-slice */
extern sk_r4_u128_t sk_h_00356340();  /* FUN_00356340 out-of-slice */
extern void sk_h_00356370(uint64_t a1);  /* FUN_00356370 out-of-slice */
extern void sk_h_0035638c(void);  /* FUN_0035638c out-of-slice */
extern void sk_h_003563e0(void);  /* FUN_003563e0 out-of-slice */
extern void sk_h_00356454(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00356454 out-of-slice */
extern void sk_h_003564e8(void);  /* FUN_003564e8 out-of-slice */
extern void sk_h_00356508(void);  /* FUN_00356508 out-of-slice */
extern void sk_h_003567d4(void);  /* FUN_003567d4 out-of-slice */
extern void sk_h_003567e0(void);  /* FUN_003567e0 out-of-slice */
extern void sk_h_00356858(void);  /* FUN_00356858 out-of-slice */
extern void sk_h_0035694c(void);  /* FUN_0035694c out-of-slice */
extern void sk_h_00356a38(void);  /* FUN_00356a38 out-of-slice */
extern void sk_h_00356aa0(uint64_t a1);  /* FUN_00356aa0 out-of-slice */
extern sk_r4_u128_t sk_h_00356b44();  /* FUN_00356b44 out-of-slice */
extern void sk_h_00356b50(void);  /* FUN_00356b50 out-of-slice */
extern void sk_h_00356b68(void);  /* FUN_00356b68 out-of-slice */
extern void sk_h_00356c54(void);  /* FUN_00356c54 out-of-slice */
extern void sk_h_00356c84(void);  /* FUN_00356c84 out-of-slice */
extern void sk_h_00356cd4(void);  /* FUN_00356cd4 out-of-slice */
extern void sk_h_00356e1c(void);  /* FUN_00356e1c out-of-slice */
extern void sk_h_00356e28(void);  /* FUN_00356e28 out-of-slice */
extern uint64_t sk_h_00356e84();  /* FUN_00356e84 out-of-slice */
extern void sk_h_00357068(void);  /* FUN_00357068 out-of-slice */
extern void sk_h_003570a0(uint64_t a1);  /* FUN_003570a0 out-of-slice */
extern void sk_h_00357198(void);  /* FUN_00357198 out-of-slice */
extern void sk_h_0035725c(void);  /* FUN_0035725c out-of-slice */
extern void sk_h_00357280(void);  /* FUN_00357280 out-of-slice */
extern void sk_h_003572c4(void);  /* FUN_003572c4 out-of-slice */
extern void sk_h_00357374(void);  /* FUN_00357374 out-of-slice */
extern void sk_h_00357380(void);  /* FUN_00357380 out-of-slice */
extern void sk_h_00357540(uint64_t a1);  /* FUN_00357540 out-of-slice */
extern void sk_h_00357564(uint64_t a1, uint64_t a2, uint64_t a3);  /* FUN_00357564 out-of-slice */
extern void sk_h_00357688(void);  /* FUN_00357688 out-of-slice */
extern void sk_h_0035780c(void);  /* FUN_0035780c out-of-slice */
extern void sk_h_0035785c(void);  /* FUN_0035785c out-of-slice */
extern void sk_h_00357868(void);  /* FUN_00357868 out-of-slice */
extern void sk_h_00357b10(void);  /* FUN_00357b10 out-of-slice */
extern void sk_h_00357b20(void);  /* FUN_00357b20 out-of-slice */
extern void sk_h_00357b3c(void);  /* FUN_00357b3c out-of-slice */
extern void sk_h_00357c2c(void);  /* FUN_00357c2c out-of-slice */
extern void sk_h_00357c74(uint64_t a1);  /* FUN_00357c74 out-of-slice */
extern void sk_h_00357cb4(void);  /* FUN_00357cb4 out-of-slice */
extern void sk_h_00357e34(uint64_t a1, uint64_t a2, uint64_t a3, uint64_t a4);  /* FUN_00357e34 out-of-slice */
extern void sk_h_00358268(void);  /* FUN_00358268 out-of-slice */
extern void sk_h_003584f8(void);  /* FUN_003584f8 out-of-slice */
extern void sk_h_003585e8(void);  /* FUN_003585e8 out-of-slice */
extern void sk_h_0035860c(void);  /* FUN_0035860c out-of-slice */
extern void sk_h_00358618(void);  /* FUN_00358618 out-of-slice */
extern uint64_t sk_h_0035866c();  /* FUN_0035866c out-of-slice */
extern void sk_h_0035869c(void);  /* FUN_0035869c out-of-slice */
extern void sk_h_00358828(void);  /* FUN_00358828 out-of-slice */
extern void sk_h_00358834(void);  /* FUN_00358834 out-of-slice */
extern void sk_h_00358840(uint64_t a1);  /* FUN_00358840 out-of-slice */
extern void sk_h_00358858(void);  /* FUN_00358858 out-of-slice */
extern void sk_h_0035893c(void);  /* FUN_0035893c out-of-slice */
extern void sk_h_00358984(uint64_t a1);  /* FUN_00358984 out-of-slice */
extern void sk_h_00358dd0(void);  /* FUN_00358dd0 out-of-slice */
extern void sk_h_00358de8(void);  /* FUN_00358de8 out-of-slice */
extern void sk_h_00358e00(uint64_t a1);  /* FUN_00358e00 out-of-slice */
extern void sk_h_00358e18(void);  /* FUN_00358e18 out-of-slice */
extern void sk_h_00358e58(void);  /* FUN_00358e58 out-of-slice */
extern void sk_h_00358edc(void);  /* FUN_00358edc out-of-slice */
extern uint64_t sk_h_00358fb4();  /* FUN_00358fb4 out-of-slice */
extern void sk_h_00358fc8(uint64_t a1);  /* FUN_00358fc8 out-of-slice */
extern void sk_h_0035900c(void);  /* FUN_0035900c out-of-slice */
extern void sk_h_00359178(uint64_t a1);  /* FUN_00359178 out-of-slice */
extern void sk_h_003591b4(void);  /* FUN_003591b4 out-of-slice */
extern void sk_h_003593a8(void);  /* FUN_003593a8 out-of-slice */
extern void sk_h_0035940c(uint64_t a1);  /* FUN_0035940c out-of-slice */
extern void sk_h_00359524(void);  /* FUN_00359524 out-of-slice */
extern void sk_h_00359658(uint64_t a1);  /* FUN_00359658 out-of-slice */
extern void sk_h_003596c4(void);  /* FUN_003596c4 out-of-slice */
extern void sk_h_003596f8(void);  /* FUN_003596f8 out-of-slice */
extern void sk_h_0035972c(void);  /* FUN_0035972c out-of-slice */
extern void sk_h_00359760(void);  /* FUN_00359760 out-of-slice */
extern void sk_h_003597c0(void);  /* FUN_003597c0 out-of-slice */
extern long sk_h_00359874();  /* FUN_00359874 out-of-slice */
extern void sk_h_003599cc(void);  /* FUN_003599cc out-of-slice */
extern void sk_h_003599e4(void);  /* FUN_003599e4 out-of-slice */
extern void sk_h_003599f8(void);  /* FUN_003599f8 out-of-slice */
extern void sk_h_00359a84(uint64_t a1);  /* FUN_00359a84 out-of-slice */
extern void sk_h_00359aa4(void);  /* FUN_00359aa4 out-of-slice */
extern sk_r4_u128_t sk_h_00359b18();  /* FUN_00359b18 out-of-slice */
extern void sk_h_00359b64(void);  /* FUN_00359b64 out-of-slice */
extern void sk_h_00359c4c(void);  /* FUN_00359c4c out-of-slice */
extern void sk_h_00359c90(void);  /* FUN_00359c90 out-of-slice */
extern void sk_h_00359cd8(uint64_t a1);  /* FUN_00359cd8 out-of-slice */
extern void sk_h_00359ce4(void);  /* FUN_00359ce4 out-of-slice */
extern void sk_h_00359d38(uint64_t a1);  /* FUN_00359d38 out-of-slice */
extern void sk_h_0035a20c(void);  /* FUN_0035a20c out-of-slice */
extern void sk_h_0035a238(void);  /* FUN_0035a238 out-of-slice */
extern void sk_h_0035a25c(void);  /* FUN_0035a25c out-of-slice */
extern void sk_h_0035a578(void);  /* FUN_0035a578 out-of-slice */
extern void sk_h_0035a5b4(void);  /* FUN_0035a5b4 out-of-slice */
extern void sk_h_0035a608(void);  /* FUN_0035a608 out-of-slice */
extern void sk_h_0035a684(void);  /* FUN_0035a684 out-of-slice */
extern void sk_h_0035a69c(void);  /* FUN_0035a69c out-of-slice */
extern void sk_h_0035a6a8(void);  /* FUN_0035a6a8 out-of-slice */
extern sk_r4_u128_t sk_h_0035a6f4();  /* FUN_0035a6f4 out-of-slice */
extern sk_r4_u128_t sk_h_0035a86c();  /* FUN_0035a86c out-of-slice */
extern void sk_h_0035a924(void);  /* FUN_0035a924 out-of-slice */
extern void sk_h_0035a938(void);  /* FUN_0035a938 out-of-slice */
extern void sk_h_0035aaa8(void);  /* FUN_0035aaa8 out-of-slice */
extern void sk_h_0035aab4(void);  /* FUN_0035aab4 out-of-slice */
extern void sk_h_0035aaf0(void);  /* FUN_0035aaf0 out-of-slice */
extern void sk_h_0035aafc(void);  /* FUN_0035aafc out-of-slice */
extern void sk_h_0035acfc(void);  /* FUN_0035acfc out-of-slice */
extern void sk_h_00361528(void);  /* FUN_00361528 out-of-slice */
extern uint64_t sk_h_00365b6c();  /* FUN_00365b6c out-of-slice */
extern void sk_h_0036986c(void);  /* FUN_0036986c out-of-slice */
extern long sk_h_0036a940();  /* FUN_0036a940 out-of-slice */
extern long sk_h_0036a9a0();  /* FUN_0036a9a0 out-of-slice */
extern void sk_h_0036b6ac(void);  /* FUN_0036b6ac out-of-slice */
extern void sk_h_003722e4(uint64_t a1, uint64_t a2);  /* FUN_003722e4 out-of-slice */
extern void sk_h_003a25e0(uint64_t a1, uint64_t a2);  /* FUN_003a25e0 out-of-slice */
extern uint64_t sk_h_003a261c();  /* FUN_003a261c out-of-slice */


extern void sk_h_00319f3c(uint64_t, ...);  /* FUN_00319f3c fn-ptr */
extern void sk_h_0031a20c(uint64_t, ...);  /* FUN_0031a20c fn-ptr */

/* Global data references (Ghidra data symbols / DAT_ & uRam_ addresses). */
extern uint64_t _DAT_004baeb0;
extern uint64_t uRam00000000004baeb8;
extern uint64_t datum_004e7f10;
extern uint64_t datum_004e7f18;
extern uint64_t datum_004e7f80;
extern uint64_t datum_004e7f90;
extern uint64_t datum_004f1878;
extern uint64_t datum_004f18a8;
extern uint64_t datum_00657798;
extern uint64_t datum_006577e0;
extern void (*datum_00658c00)(...);        /* function-pointer global */

/* Out-of-slice helper referenced as a value (function address passed as argument). */
extern void sk_h_002060d4(void);           /* FUN_002060d4 out-of-slice */

/* Functions defined later in this file but referenced (as values) before their
 * definition.  Forward declarations matching the bodies defined below. */
extern void sk_r4_001c050c(uint64_t, uint64_t);
extern sk_r4_u128_t sk_r4_001c0528(void);
extern void sk_r4_001c11b4(uint64_t, uint64_t);
extern void sk_r4_001c11d8(void);
extern void sk_r4_001c12dc(void);
extern void sk_r4_001c1300(uint64_t *p1);
extern void sk_r4_001c133c(long);
extern void sk_r4_001c1388(uint64_t *p1, uint64_t, uint64_t, uint64_t, uint8_t, long *p6, uint64_t, uint64_t);
extern void sk_r4_001c14ac(void);
extern void sk_r4_001c1574(uint64_t, uint64_t, uint64_t);
extern void sk_r4_001c169c(void);
extern void sk_r4_001c1700(void);
extern void sk_r4_001c1730(void);
extern void sk_r4_001c1754(void);
extern void sk_r4_001c1778(void);
extern void sk_r4_001c179c(void);
extern void sk_r4_001c17c0(void);
extern void sk_r4_001c17e4(void);
extern void sk_r4_001c1808(void);
extern void sk_r4_001c182c(void);
extern void sk_r4_001c1850(void);
extern void sk_r4_001c1874(void);
extern void sk_r4_001c1898(void);
extern void sk_r4_001c18bc(void);
extern void sk_r4_001c18e0(void);
extern void sk_r4_001c1904(void);
extern void sk_r4_001c1928(void);
extern void sk_r4_001c194c(void);
extern void sk_r4_001c1970(void);
extern void sk_r4_001c1994(void);
extern void sk_r4_001c19b8(void);
extern void sk_r4_001c19dc(void);
extern void sk_r4_001c1a00(void);
extern void sk_r4_001c1a24(void);
extern void sk_r4_001c1a48(void);
extern void sk_r4_001c1a6c(void);
extern void sk_r4_001c1a90(void);
extern void sk_r4_001c1ab4(void);
extern void sk_r4_001c1ad8(void);
extern void sk_r4_001c1afc(void);
extern void sk_r4_001c1b20(void);
extern void sk_r4_001c1b44(void);
extern void sk_r4_001c1b68(void);
extern void sk_r4_001c1b8c(void);
extern void sk_r4_001c1bb0(void);
extern void sk_r4_001c1bd4(void);
extern void sk_r4_001c1bf8(void);
extern void sk_r4_001c1c1c(void);
extern void sk_r4_001c1c40(void);
extern void sk_r4_001c1c70(void);
extern void sk_r4_001c1ca0(void);
extern void sk_r4_001c1cd0(void);
extern void sk_r4_001c1d00(uint64_t);
extern void sk_r4_001c1d04(uint64_t);
extern void sk_r4_001c1d5c(void);
extern void sk_r4_001c1e34(void);
extern void sk_r4_001c2074(void);
extern void sk_r4_001c20a0(void);
extern void sk_r4_001c22c4(void);
extern void sk_r4_001c22f0(void);
extern void sk_r4_001c22f4(void);
extern void sk_r4_001c2320(void);
extern void sk_r4_001c2324(void);
extern void sk_r4_001c2350(void);
extern void sk_r4_001c2354(void);
extern void sk_r4_001c236c(void);
extern void sk_r4_001c2370(void);
extern void sk_r4_001c239c(void);
extern void sk_r4_001c23a0(void);
extern void sk_r4_001c23cc(void);
extern void sk_r4_001c23d0(void);
extern void sk_r4_001c23fc(void);
extern void sk_r4_001c2400(void);
extern void sk_r4_001c242c(void);
extern void sk_r4_001c2430(void);
extern void sk_r4_001c245c(void);
extern void sk_r4_001c2460(void);
extern void sk_r4_001c2478(void);
extern void sk_r4_001c2584(void);
extern void sk_r4_001c25b0(void);
extern void sk_r4_001c26d0(void);
extern void sk_r4_001c26fc(void);
extern void sk_r4_001c2a6c(void);
extern void sk_r4_001c2a98(void);
extern void sk_r4_001c2ba4(void);
extern void sk_r4_001c2bd0(void);
extern void sk_r4_001c2d08(void);
extern void sk_r4_001c2d34(void);
extern void sk_r4_001c2d38(void);
extern void sk_r4_001c2d64(void);
extern void sk_r4_001c2d68(void);
extern void sk_r4_001c2d94(void);
extern void sk_r4_001c2d98(void);
extern void sk_r4_001c2dc4(void);
extern void sk_r4_001c2dc8(void);
extern void sk_r4_001c2df4(void);
extern void sk_r4_001c2df8(void);
extern void sk_r4_001c2e24(void);
extern void sk_r4_001c2e28(void);
extern void sk_r4_001c2e54(void);
extern void sk_r4_001c2e58(void);
extern void sk_r4_001c2e84(void);
extern void sk_r4_001c2e88(void);
extern void sk_r4_001c2eb4(void);
extern void sk_r4_001c2eb8(void);
extern void sk_r4_001c2ee4(void);
extern void sk_r4_001c2ff0(void);
extern void sk_r4_001c301c(void);
extern void sk_r4_001c3140(void);
extern void sk_r4_001c316c(void);
extern void sk_r4_001c328c(void);
extern void sk_r4_001c32b8(void);
extern void sk_r4_001c33f8(void);
extern void sk_r4_001c3424(uint64_t, uint64_t, uint32_t, uint64_t, long, uint64_t, code *p7);
extern void sk_r4_001c37cc(uint64_t);
extern void sk_r4_001c3868(void);
extern void sk_r4_001c39dc(void);
extern void sk_r4_001c3a48(void);
extern void sk_r4_001c3a78(void);
extern void sk_r4_001c3aa8(void);
extern void sk_r4_001c3ad8(void);
extern void sk_r4_001c3afc(void);
extern void sk_r4_001c3b20(void);
extern void sk_r4_001c3b44(void);
extern void sk_r4_001c3b68(void);
extern void sk_r4_001c3b8c(void);
extern void sk_r4_001c3bb0(void);
extern void sk_r4_001c3bd4(void);
extern void sk_r4_001c3bf8(void);
extern void sk_r4_001c3c1c(void);
extern void sk_r4_001c3c40(void);
extern void sk_r4_001c3c64(void);
extern void sk_r4_001c3c88(void);
extern void sk_r4_001c3cac(void);
extern void sk_r4_001c3cd0(void);
extern void sk_r4_001c3cf4(void);
extern void sk_r4_001c3d18(void);
extern void sk_r4_001c3d3c(void);
extern void sk_r4_001c3d60(void);
extern void sk_r4_001c3d84(void);
extern void sk_r4_001c3da8(void);
extern void sk_r4_001c3dcc(void);
extern void sk_r4_001c3df0(void);
extern void sk_r4_001c3e14(void);
extern void sk_r4_001c3e38(void);
extern void sk_r4_001c3e5c(void);
extern void sk_r4_001c3e80(void);
extern void sk_r4_001c3ea4(void);
extern void sk_r4_001c3ec8(void);
extern void sk_r4_001c3eec(void);
extern void sk_r4_001c3f10(void);
extern void sk_r4_001c3f34(void);
extern void sk_r4_001c3f58(void);
extern void sk_r4_001c3f7c(void);
extern void sk_r4_001c3fa0(void);
extern void sk_r4_001c3fc4(void);
extern void sk_r4_001c3fe8(void);
extern void sk_r4_001c400c(void);
extern void sk_r4_001c4030(void);
extern void sk_r4_001c4058(uint64_t);
extern void sk_r4_001c40b0(void);
extern void sk_r4_001c4188(void);
extern void sk_r4_001c4284(void);
extern uint sk_r4_001c43f4(void);
extern uint sk_r4_001c4424(void);
extern uint sk_r4_001c4428(void);
extern void sk_r4_001c4458(void);
extern void sk_r4_001c45b8(void);
extern void sk_r4_001c45e4(void);
extern void sk_r4_001c4910(void);
extern void sk_r4_001c4928(void);
extern void sk_r4_001c492c(void);
extern void sk_r4_001c4958(void);
extern void sk_r4_001c495c(void);
extern void sk_r4_001c4988(void);
extern void sk_r4_001c498c(void);
extern void sk_r4_001c49a4(void);
extern void sk_r4_001c49a8(void);
extern void sk_r4_001c49c0(void);
extern void sk_r4_001c49c4(void);
extern void sk_r4_001c49dc(void);
extern void sk_r4_001c49e0(void);
extern void sk_r4_001c49f8(void);
extern void sk_r4_001c49fc(void);
extern void sk_r4_001c4a28(void);
extern void sk_r4_001c4a2c(void);
extern void sk_r4_001c4a58(void);
extern void sk_r4_001c4a5c(void);
extern void sk_r4_001c4a74(void);
extern void sk_r4_001c4bd4(void);
extern void sk_r4_001c4bec(void);
extern void sk_r4_001c4d4c(void);
extern void sk_r4_001c4d64(void);
extern void sk_r4_001c4ed8(void);
extern void sk_r4_001c4f00(void);
extern void sk_r4_001c4f04(void);
extern void sk_r4_001c4f30(void);
extern void sk_r4_001c5090(void);
extern void sk_r4_001c50bc(void);
extern void sk_r4_001c5238(void);
extern void sk_r4_001c5264(void);
extern void sk_r4_001c5268(void);
extern void sk_r4_001c5294(void);
extern void sk_r4_001c5298(void);
extern void sk_r4_001c52c4(void);
extern void sk_r4_001c52c8(void);
extern void sk_r4_001c52f4(void);
extern void sk_r4_001c52f8(void);
extern void sk_r4_001c5324(void);
extern void sk_r4_001c5328(void);
extern void sk_r4_001c5354(void);
extern void sk_r4_001c5358(void);
extern void sk_r4_001c5384(void);
extern void sk_r4_001c5388(void);
extern void sk_r4_001c53b4(void);
extern void sk_r4_001c53b8(void);
extern void sk_r4_001c53e4(void);
extern void sk_r4_001c53e8(void);
extern void sk_r4_001c5414(void);
extern void sk_r4_001c5574(void);
extern void sk_r4_001c55a0(void);
extern void sk_r4_001c5700(void);
extern void sk_r4_001c572c(void);
extern void sk_r4_001c588c(void);
extern void sk_r4_001c58b8(void);
extern void sk_r4_001c5a38(void);
extern void sk_r4_001c5a64(void);
extern void sk_r4_001c5c58(void);
extern void sk_r4_001c5c80(void);
extern void sk_r4_001c5fdc(void);
extern void sk_r4_001c6004(void);
extern void sk_r4_001c60f4(void);
extern void sk_r4_001c60f8(void);
extern void sk_r4_001c6120(void);
extern void sk_r4_001c6310(void);
extern void sk_r4_001c637c(code *p1);
extern void sk_r4_001c6380(code *p1);
extern uint sk_r4_001c63b8(void);
extern void sk_r4_001c6454(uint64_t, uint64_t);
extern void sk_r4_001c64e0(uint64_t);
extern void sk_r4_001c64e4(uint64_t);
extern void sk_r4_001c64fc(byte *p1);
extern void sk_r4_001c652c(void);
extern void sk_r4_001c65d0(void);
extern void sk_r4_001c6c48(void);
extern void sk_r4_001c6ce8(void);
extern void sk_r4_001c6d74(uint64_t);
extern void sk_r4_001c6d78(uint64_t);
extern void sk_r4_001c6d90(uint8_t (*p1) [16]);
extern void sk_r4_001c6dbc(void);
extern void sk_r4_001c6e84(void);
extern sk_r4_u128_t sk_r4_001c7534(void);
extern void sk_r4_001c75dc(long);
extern void sk_r4_001c766c(void);
extern void sk_r4_001c7670(void);
extern void sk_r4_001c7688(uint64_t *p1);
extern void sk_r4_001c76b4(void);
extern void sk_r4_001c7768(void);
extern sk_r4_u128_t sk_r4_001c7d10(void);
extern void sk_r4_001c7db8(long);
extern void sk_r4_001c7e48(void);
extern void sk_r4_001c7e4c(void);
extern void sk_r4_001c7e64(uint32_t *p1);
extern void sk_r4_001c7e90(void);
extern void sk_r4_001c7f48(void);
extern sk_r4_u128_t sk_r4_001c84fc(uint64_t);
extern void sk_r4_001c877c(float2);
extern void sk_r4_001c87a0(void);
extern void sk_r4_001c87a4(void);
extern void sk_r4_001c87bc(uint16_t *p1);
extern void sk_r4_001c87e8(uint64_t);
extern void sk_r4_001c8818(uint64_t, uint64_t);
extern void sk_r4_001c8848(uint64_t);
extern void sk_r4_001c884c(uint64_t);
extern void sk_r4_001c8864(uint64_t *p1);
extern void sk_r4_001c8890(void);
extern void sk_r4_001c8894(void);
extern void sk_r4_001c88c0(void);
extern void sk_r4_001c8918(uint64_t);
extern void sk_r4_001c8948(uint64_t, uint64_t);
extern void sk_r4_001c8978(uint64_t);
extern void sk_r4_001c897c(uint64_t);
extern void sk_r4_001c8994(uint8_t *p1);
extern void sk_r4_001c89c0(void);
extern void sk_r4_001c89c4(void);
extern void sk_r4_001c89f0(void);
extern void sk_r4_001c8a48(uint64_t);
extern void sk_r4_001c8a78(uint64_t, uint64_t);
extern void sk_r4_001c8aa8(uint64_t);
extern void sk_r4_001c8aac(uint64_t);
extern void sk_r4_001c8ac4(uint16_t *p1);
extern void sk_r4_001c8af0(void);
extern void sk_r4_001c8af4(void);
extern void sk_r4_001c8b20(void);
extern void sk_r4_001c8b78(uint64_t);
extern void sk_r4_001c8ba8(uint64_t, uint64_t);
extern void sk_r4_001c8bd8(uint64_t);
extern void sk_r4_001c8bdc(uint64_t);
extern void sk_r4_001c8bf4(uint32_t *p1);
extern void sk_r4_001c8c20(void);
extern void sk_r4_001c8c24(void);
extern void sk_r4_001c8c50(void);
extern void sk_r4_001c8ca8(uint64_t);
extern void sk_r4_001c8cd8(void);
extern void sk_r4_001c8d70(uint64_t, uint64_t);
extern void sk_r4_001c8da0(void);
extern void sk_r4_001c8e18(uint64_t);
extern void sk_r4_001c8e1c(uint64_t);
extern void sk_r4_001c8e34(uint64_t *p1);
extern void sk_r4_001c8e60(void);
extern void sk_r4_001c8e64(void);
extern void sk_r4_001c8e90(void);
extern void sk_r4_001c8f24(void);
extern void sk_r4_001c8f7c(void);
extern void sk_r4_001c9550(uint64_t);
extern void sk_r4_001c9580(void);
extern void sk_r4_001c95b0(uint64_t);
extern void sk_r4_001c95b4(uint64_t);
extern void sk_r4_001c95cc(uint8_t (*p1) [16]);
extern void sk_r4_001c95f8(void);
extern void sk_r4_001c95fc(void);
extern void sk_r4_001c9628(void);
extern void sk_r4_001c9680(uint64_t);
extern void sk_r4_001c96b0(uint64_t, uint64_t);
extern void sk_r4_001c96e0(uint64_t);
extern void sk_r4_001c96e4(uint64_t);
extern void sk_r4_001c96fc(uint64_t *p1);
extern void sk_r4_001c9728(void);
extern void sk_r4_001c972c(void);
extern void sk_r4_001c9758(void);
extern void sk_r4_001c97a0(uint64_t);
extern void sk_r4_001c97d0(void);
extern void sk_r4_001c9864(uint64_t, uint64_t);
extern void sk_r4_001c9894(void);
extern void sk_r4_001c9910(uint64_t);
extern void sk_r4_001c9914(uint64_t);
extern void sk_r4_001c992c(uint8_t *p1);
extern void sk_r4_001c9958(void);
extern void sk_r4_001c995c(void);
extern void sk_r4_001c9988(void);
extern void sk_r4_001c9a1c(void);
extern void sk_r4_001c9a74(void);
extern void sk_r4_001ca040(uint64_t);
extern void sk_r4_001ca070(void);
extern void sk_r4_001ca104(uint64_t, uint64_t);
extern void sk_r4_001ca134(void);
extern void sk_r4_001ca1b0(uint64_t);
extern void sk_r4_001ca1b4(uint64_t);
extern void sk_r4_001ca1cc(uint16_t *p1);
extern void sk_r4_001ca1f8(void);
extern void sk_r4_001ca1fc(void);
extern void sk_r4_001ca228(void);
extern void sk_r4_001ca2bc(void);
extern void sk_r4_001ca314(void);
extern void sk_r4_001ca8e0(uint64_t);
extern void sk_r4_001ca910(void);
extern void sk_r4_001ca9a4(uint64_t, uint64_t);
extern void sk_r4_001ca9d4(void);
extern void sk_r4_001caa50(uint64_t);
extern void sk_r4_001caa54(uint64_t);
extern void sk_r4_001caa6c(uint32_t *p1);
extern void sk_r4_001caa98(void);
extern void sk_r4_001caa9c(void);
extern void sk_r4_001caac8(void);
extern void sk_r4_001cab5c(void);
extern void sk_r4_001cabb4(void);
extern void sk_r4_001cb180(uint64_t);
extern void sk_r4_001cb1b0(uint64_t, uint64_t);
extern void sk_r4_001cb1e0(uint64_t);
extern void sk_r4_001cb1e4(uint64_t);
extern void sk_r4_001cb1fc(uint64_t *p1);
extern void sk_r4_001cb228(void);
extern void sk_r4_001cb22c(void);
extern void sk_r4_001cb258(void);
extern void sk_r4_001cb2a0(uint64_t);
extern void sk_r4_001cb2d0(void);
extern void sk_r4_001cb368(void);
extern void sk_r4_001cb398(void);
extern void sk_r4_001cb43c(uint64_t);
extern void sk_r4_001cb440(uint64_t);
extern void sk_r4_001cb458(uint8_t (*p1) [16]);
extern void sk_r4_001cb484(void);
extern void sk_r4_001cb488(void);
extern void sk_r4_001cb4b4(void);
extern void sk_r4_001cb570(void);
extern void sk_r4_001cb5c8(void);
extern void sk_r4_001cbcb4(uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cbe48(uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cbe4c(uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cbe68(uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cc030(uint64_t, long, uint64_t);
extern void sk_r4_001cc034(uint64_t, long, uint64_t);
extern void sk_r4_001cc054(uint64_t, uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cc198(uint64_t, long, uint64_t);
extern void sk_r4_001cc19c(uint64_t, long, uint64_t);
extern void sk_r4_001cc1c4(void);
extern void sk_r4_001cc1c8(void);
extern void sk_r4_001cc204(void);
extern void sk_r4_001cc208(void);
extern void sk_r4_001cc230(uint64_t, uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cc354(uint64_t, long, uint64_t);
extern void sk_r4_001cc358(uint64_t, long, uint64_t);
extern void sk_r4_001cc380(void);
extern void sk_r4_001cc384(void);
extern void sk_r4_001cc3c0(void);
extern void sk_r4_001cc520(void);
extern void sk_r4_001cc524(void);
extern void sk_r4_001cc54c(void);
extern void sk_r4_001cc584(uint64_t, uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cc764(uint64_t, long, uint64_t);
extern void sk_r4_001cc768(uint64_t, long, uint64_t);
extern void sk_r4_001cc790(void);
extern void sk_r4_001cc94c(uint64_t, uint64_t, long);
extern void sk_r4_001cc98c(uint64_t *p1, uint64_t, long, uint64_t);
extern void sk_r4_001cc9c8(void);
extern void sk_r4_001ccd1c(uint64_t, uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cd0b8(void);
extern void sk_r4_001cd168(long);
extern void sk_r4_001cd194(long);
extern void sk_r4_001cd1e0(uint64_t, uint64_t, uint64_t, uint8_t);
extern void sk_r4_001cd260(void);
extern void sk_r4_001cd3fc(uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cd478(void);
extern void sk_r4_001cd618(long *p1, uint64_t, uint64_t, uint64_t);
extern sk_r4_u128_t sk_r4_001cd66c(uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cd6e0(uint64_t *p1);
extern void sk_r4_001cd70c(uint64_t, uint64_t, uint64_t, uint8_t);
extern void sk_r4_001cd778(uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cd7e4(uint8_t (*p1) [16]);
extern void sk_r4_001cd80c(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
extern void sk_r4_001ce58c(void);
extern void sk_r4_001ce6d4(uint64_t, long, uint64_t);
extern void sk_r4_001ce6d8(uint64_t, long, uint64_t);
extern void sk_r4_001ce704(void);
extern void sk_r4_001cf6f4(uint64_t, uint64_t, long);
extern void sk_r4_001cf8b8(uint64_t *p1, uint64_t, long, uint64_t);
extern void sk_r4_001cf8f8(void);
extern void sk_r4_001cf964(void);
extern void sk_r4_001cf9d0(uint64_t, long, uint64_t, uint64_t, uint64_t);
extern void sk_r4_001cfa34(void);
extern void sk_r4_001cfa94(void);
extern void sk_r4_001cfaf4(void);
extern void sk_r4_001cfb54(void);
extern void sk_r4_001cfb58(void);
extern void sk_r4_001cfb84(void);
extern void sk_r4_001cfb88(void);
extern void sk_r4_001cfbb4(void);
extern void sk_r4_001cfbb8(void);
extern void sk_r4_001cfbd0(void);
extern void sk_r4_001cfc30(void);
extern void sk_r4_001cfc34(void);
extern void sk_r4_001cfc60(void);
extern void sk_r4_001cfcc0(void);
extern void sk_r4_001cfcc4(void);
extern void sk_r4_001cfcf0(uint, uint64_t, uint64_t, uint64_t, code *p5);
extern void sk_r4_001cfd64(void);
extern void sk_r4_001cfd68(void);
extern void sk_r4_001cfd94(uint, uint64_t, uint64_t, uint64_t, code *p5);
extern void sk_r4_001cfe08(void);
extern void sk_r4_001cfe0c(void);
extern void sk_r4_001cfe24(void);
extern void sk_r4_001cfe94(void);
extern void sk_r4_001cfef4(void);
extern void sk_r4_001cfef8(void);
extern void sk_r4_001cff24(void);
extern void sk_r4_001cff9c(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

/* FUN_001c050c @ 0x001c050c   (est. sk_r4_001c050c)
 * Ghidra: void FUN_001c050c(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c050c(uint64_t p1,uint64_t p2)

{
  sk_h_00229464(p1,p2,sk_h_002060d4);
  return;
}



/* FUN_001c0528 @ 0x001c0528   (est. sk_r4_001c0528)
 * Ghidra: undefined1  [16] FUN_001c0528(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Type propagation algorithm not settling */

sk_r4_u128_t sk_r4_001c0528(void)

{
  sk_r4_u128_t av1;
  sk_r4_u128_t av2;
  sk_r4_u128_t av3;
  sk_r4_u128_t av4;
  sk_r4_u128_t av5;
  sk_r4_u128_t av6;
  sk_r4_u128_t av7;
  sk_r4_u128_t av8;
  sk_r4_u128_t av9;
  sk_r4_u128_t av10;
  sk_r4_u128_t av11;
  sk_r4_u128_t av12;
  sk_r4_u128_t av13;
  uint8_t v14;
  uint64_t **v15;
  long r16;
  uint64_t v17;
  uint64_t v18;
  long xo1;
  long xo1_00;
  long xo8;
  long xo8_00;
  long xo8_01;
  long xo8_02;
  long xo8_03;
  long xo8_04;
  long xo8_05;
  long xo8_06;
  long xo8_07;
  long xo8_08;
  uint64_t **xo8_09;
  long xo8_10;
  uint64_t **xo8_11;
  long xo8_12;
  long xo8_13;
  long xo8_14;
  long xo8_15;
  long xo8_16;
  uint64_t **xo8_17;
  long xo8_18;
  long xo8_19;
  long xo8_20;
  uint64_t ax19;
  uint64_t **v19;
  uint64_t **v20;
  uint64_t **ax20;
  uint64_t **ax21;
  uint64_t ax22;
  uint64_t **ax23;
  uint64_t **v21;
  uint64_t **ax24;
  uint64_t **ax25;
  uint64_t **ax26;
  uint64_t **ax27;
  uint64_t **v22;
  uint64_t **ax28;
  sk_r4_u128_t av23;
  sk_r4_u128_t av24;
  sk_r4_u128_t av25;
  sk_r4_u128_t av26;
  sk_r4_u128_t av27;
  uint64_t **stk_f8;
  uint64_t v28;
  uint64_t stk_c8;
  uint64_t **stk_b8;
  uint64_t **pppppppuStack_b0;
  uint64_t stk_a8;
  uint64_t **pppppppuStack_a0;
  uint64_t **stk_90;
  uint64_t **ppppppuStack_88;
  uint64_t stk_80;
  uint64_t **pppppppuStack_78;
  char stk_70;
  
  av13.hi = ax21;
  av13.lo = ax20;
  av23.hi = ax24;
  av23.lo = ax25;
  av24.hi = ax24;
  av24.lo = ax25;
  sk_h_00319a14();
  v14 = stk_70 == '\x03';
  switch(stk_70) {
  default:
    sk_h_00359c90();
    sk_enum_err(0x35);
    av23 = sk_h_00354e0c();
    av24 = sk_h_001a89a8((const char *)0x005ce950 /* DecodingError_typeMismatch__expe */,0x33,1);
    v22 = av24.hi;
    ax25 = av24.lo;
    sk_rt_hook_u();
    if ((xo8 == 0) &&
       ((((uint64_t)ax21 & ((uint64_t)ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free();
      v15 = ax25;
    }
    else {
      ax26 = (uint64_t *******)((uint64_t)v22 >> 0x38 & 0xf);
      if (((uint64_t)ax20 >> 0x3d & 1) == 0) {
        v14 = ((uint64_t)v22 & 0x2000000000000000) == 0;
        v19 = (uint64_t *******)((uint64_t)ax25 & 0xffffffffffff);
        if (!(bool)v14) {
          v19 = ax26;
        }
      }
      else if (((uint64_t)v22 >> 0x3d & 1) == 0) {
        v19 = (uint64_t *******)((uint64_t)ax25 & 0xffffffffffff);
      }
      else {
        av24 = sk_rt_hook_m();
        v15 = (uint64_t *******)sk_rt_slot3(av24.lo,av24.hi,ax25);
        v19 = ax26;
        if (!(bool)v14) {
          sk_h_00355d90();
          sk_masked_free();
          sk_masked_free(v22);
          ax21 = v15;
          v22 = ax27;
          goto LAB_001c082c;
        }
      }
      sk_h_0035060c();
      sk_h_00352db8();
      sk_h_002a4c98();
      sk_masked_free(v22);
      ax26 = v19;
      v15 = av23.lo;
      v22 = av23.hi;
    }
LAB_001c082c:
    sk_h_00354774();
    sk_h_00361528();
    if (xo1 < 0) {
LAB_001c1198:
      sk_h_0034846c();
                    /* WARNING: Subroutine does not return */
      sk_h_001afe4c();
    }
    sk_h_00351e08();
    r16 = sk_h_002a218c();
    if (r16 < 0) {
      sk_h_0034a8cc();
      sk_h_002a2748();
    }
    else {
      sk_h_0034f9fc();
      sk_h_002a2698();
    }
    sk_h_00355a58();
    v17 = sk_h_00349cbc(v15);
    ax20 = v22;
    if ((xo8_04 == 0) &&
       (((v17 & ((uint64_t)v22 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(v22);
    }
    else {
      if (((uint64_t)v22 >> 0x3d & 1) == 0) {
        sk_h_003558a8();
      }
      else if (((uint64_t)ax26 >> 0x3d & 1) != 0) {
        sk_h_00352a34();
        sk_h_0034c51c();
        if (!(bool)v14) {
          sk_h_00356508();
          sk_masked_free(ax26);
          ax27 = ax21;
          ax26 = ax24;
          goto LAB_001c0940;
        }
      }
      sk_alloc_pages(ax26);
      sk_h_00350914();
      sk_h_00352cc8();
      sk_h_002a4c98();
      sk_h_0035900c();
      ax20 = (uint64_t *******)&stack0xffffffffffffff20;
      ax27 = v15;
      ax26 = v22;
    }
LAB_001c0940:
    av26 = sk_h_0034b480();
    goto LAB_001c0980;
  case '\x01':
    sk_h_00359c90();
    sk_enum_err(0x4d);
    av23 = sk_h_00354e0c();
    av24 = sk_h_001a89a8((const char *)0x005ce8f0 /* DecodingError_valueNotFound__Exp */,0x34,1);
    v22 = av24.hi;
    ax25 = av24.lo;
    sk_rt_hook_u();
    if ((xo8_01 == 0) &&
       ((((uint64_t)ax21 & ((uint64_t)ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free();
      v15 = ax25;
    }
    else {
      ax26 = (uint64_t *******)((uint64_t)v22 >> 0x38 & 0xf);
      if (((uint64_t)ax20 >> 0x3d & 1) == 0) {
        v14 = ((uint64_t)v22 & 0x2000000000000000) == 0;
        v19 = (uint64_t *******)((uint64_t)ax25 & 0xffffffffffff);
        if (!(bool)v14) {
          v19 = ax26;
        }
      }
      else if (((uint64_t)v22 >> 0x3d & 1) == 0) {
        v19 = (uint64_t *******)((uint64_t)ax25 & 0xffffffffffff);
      }
      else {
        av24 = sk_rt_hook_m();
        v15 = (uint64_t *******)sk_rt_slot3(av24.lo,av24.hi,ax25);
        v19 = ax26;
        if (!(bool)v14) {
          sk_h_00355d90();
          sk_masked_free();
          sk_masked_free(v22);
          ax21 = v15;
          v22 = ax27;
          goto LAB_001c08b4;
        }
      }
      sk_h_0035060c();
      sk_h_00352db8();
      sk_h_002a4c98();
      sk_masked_free(v22);
      ax26 = v19;
      v15 = av23.lo;
      v22 = av23.hi;
    }
LAB_001c08b4:
    sk_h_00354774();
    sk_h_00361528();
    if (xo1_00 < 0) goto LAB_001c1198;
    sk_h_00351e08();
    r16 = sk_h_002a218c();
    if (r16 < 0) {
      sk_h_0034a8cc();
      sk_h_002a2748();
    }
    else {
      sk_h_0034f9fc();
      sk_h_002a2698();
    }
    sk_h_00355a58();
    v17 = sk_h_00349cbc(v15);
    ax20 = v22;
    if ((xo8_05 == 0) &&
       (((v17 & ((uint64_t)v22 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(v22);
    }
    else {
      if (((uint64_t)v22 >> 0x3d & 1) == 0) {
        sk_h_003558a8();
      }
      else if (((uint64_t)ax26 >> 0x3d & 1) != 0) {
        sk_h_00352a34();
        sk_h_0034c51c();
        if (!(bool)v14) {
          sk_h_00356508();
          sk_masked_free(ax26);
          ax27 = ax21;
          ax26 = ax24;
          goto LAB_001c0974;
        }
      }
      sk_alloc_pages(ax26);
      sk_h_00350914();
      sk_h_00352cc8();
      sk_h_002a4c98();
      sk_h_0035900c();
      ax20 = (uint64_t *******)&stack0xffffffffffffff20;
      ax27 = v15;
      ax26 = v22;
    }
LAB_001c0974:
    av26.hi = 0x17;
    av26.lo = (const char *)0x005ce930 /* but_found_null_instead */;
LAB_001c0980:
    sk_h_001a89a8(av26.lo,av26.hi,1);
    sk_h_00354ddc();
    sk_h_0034d0e0((uint64_t)ax27 & 0xffffffffffff);
    v22 = ax28;
    if ((xo8_06 == 0) &&
       ((((uint64_t)ax27 & ((uint64_t)ax26 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(ax26);
    }
    else {
      if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
        sk_h_003553a8();
      }
      else if (((uint64_t)ax24 >> 0x3d & 1) != 0) {
        av23 = sk_h_00350914();
        sk_h_0034b1a0(av23.lo,av23.hi,ax25);
        if (!(bool)v14) {
          sk_h_00350b90();
          sk_masked_free(ax26);
          sk_masked_free();
          ax24 = ax21;
          ax25 = ax20;
          break;
        }
      }
      ax20 = (uint64_t *******)&stack0xffffffffffffff20;
      sk_h_0034f454();
      sk_h_002a4c98();
      sk_masked_free();
      ax24 = ax26;
      ax25 = ax27;
    }
    break;
  case '\x02':
    sk_h_00077070(&stk_b8,&stack0xffffffffffffff20);
    sk_enum_err(0x49);
    av25 = sk_h_00351e08();
    sk_h_001a89a8((const char *)0x005ce890 /* DecodingError_keyNotFound__Key__ */,0x20,1);
    sk_h_00354ddc();
    sk_rt_hook_v();
    if ((xo8_00 == 0) &&
       ((((uint64_t)ax20 & (ax19 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free();
      av13 = av23;
    }
    else {
      ax26 = (uint64_t *******)((uint64_t)ax24 >> 0x38 & 0xf);
      if ((ax19 >> 0x3d & 1) == 0) {
        sk_h_00359a84((uint64_t)ax25 & 0xffffffffffff);
      }
      else if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
        ax26 = (uint64_t *******)((uint64_t)ax25 & 0xffffffffffff);
      }
      else {
        sk_h_0007c1c4();
        sk_h_0034b1a0();
        if (!(bool)v14) {
          sk_h_0034bd90();
          sk_masked_free();
          sk_masked_free();
          sk_h_0035a238();
          av23 = av24;
          goto LAB_001c0704;
        }
      }
      sk_h_0034f454();
      sk_h_002a4c98();
      sk_masked_free();
      av23 = av25;
      av13 = av25;
    }
LAB_001c0704:
    v17 = av23.hi;
    v18 = av23.lo;
    ax20 = (uint64_t *******)sk_h_0006a4c0(&stack0xffffffffffffff20,stk_c8);
    sk_h_00350968(1);
    sk_h_001ba83c();
    sk_h_00355a58();
    sk_h_0034d044(v18 & 0xffffffffffff);
    if ((xo8_02 == 0) && (((v18 & (v17 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(v17);
    }
    else {
      if ((v17 >> 0x3d & 1) == 0) {
        sk_h_003558a8();
      }
      else if (((uint64_t)ax26 >> 0x3d & 1) != 0) {
        sk_h_00350618();
        sk_h_0034c51c();
        if (!(bool)v14) {
          sk_h_00350b90();
          sk_masked_free(v17);
          sk_masked_free(ax26);
          ax27 = ax20;
          ax26 = ax21;
          goto LAB_001c0788;
        }
      }
      ax20 = (uint64_t *******)&stack0xffffffffffffff10;
      sk_h_00350914();
      sk_h_00352cc8();
      sk_h_002a4c98();
      sk_masked_free(ax26);
      ax27 = av13.lo;
      ax26 = av13.hi;
    }
LAB_001c0788:
    av25.hi = ax26;
    av25.lo = ax27;
    sk_h_001a89a8((const char *)0x005ce8c0 /* __not_found_in_keyed_decoding_co */,0x27,1);
    sk_h_00354ddc();
    sk_h_0034d0e0((uint64_t)ax27 & 0xffffffffffff);
    if ((xo8_03 == 0) &&
       ((((uint64_t)ax27 & ((uint64_t)ax26 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(ax26);
    }
    else {
      if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
        sk_h_003553a8();
      }
      else if ((v17 >> 0x3d & 1) != 0) {
        av24 = sk_h_00350914();
        sk_h_0034b1a0(av24.lo,av24.hi,v18);
        if (!(bool)v14) {
          sk_h_00350b90();
          sk_masked_free(ax26);
          sk_masked_free(v17);
          sk_h_0035a238();
          goto LAB_001c0ae8;
        }
      }
      ax20 = (uint64_t *******)&stack0xffffffffffffff10;
      sk_h_0034f454();
      sk_h_002a4c98();
      sk_masked_free(v17);
      av23 = av25;
    }
LAB_001c0ae8:
    sk_swift_release(&stack0xffffffffffffff20);
    stk_f8 = pppppppuStack_78;
    ax22 = stk_80;
    ax23 = (uint64_t *******)ppppppuStack_88;
    ax24 = av23.hi;
    ax25 = av23.lo;
    v22 = stk_90;
    ax28 = stk_90;
    break;
  case '\x03':
    sk_h_001a89a8((const char *)0x005ce860 /* DecodingError_dataCorrupted__Dat */,0x2f,1);
    sk_h_00354ddc();
    stk_f8 = pppppppuStack_a0;
    ax22 = stk_a8;
    ax23 = pppppppuStack_b0;
    v22 = stk_b8;
  }
  av6.hi = ax22;
  av6.lo = ax23;
  av27.hi = ax24;
  av27.lo = ax28;
  v19 = stk_f8;
  stk_b8 = ax25;
  if (v22[2] != (uint64_t ******)0x0) {
    pppppppuStack_b0 = ax24;
    sk_h_0035940c((const char *)0x005ce810 /* __Path_ */);
    sk_h_00354e0c();
    sk_masked_free(0xe000000000000000);
    sk_h_001bb234(v22);
    sk_h_00357868();
    sk_rt_hook_u();
    v15 = ax20;
    if ((xo8_07 == 0) &&
       ((((uint64_t)ax21 & ((uint64_t)ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(ax20);
      ax28 = v22;
    }
    else {
      if (((uint64_t)ax20 >> 0x3d & 1) == 0) {
        sk_h_00357380();
      }
      else if (((uint64_t)v22 >> 0x3d & 1) != 0) {
        sk_h_0011aa70();
        v19 = (uint64_t *******)sk_rt_slot2();
        if (!(bool)v14) {
          sk_h_003542c4();
          sk_masked_free();
          sk_masked_free(v22);
          ax21 = v19;
          goto LAB_001c0b94;
        }
      }
      sk_h_003510ac();
      sk_h_00352db8();
      sk_h_002a4c98();
      sk_masked_free(v22);
      v15 = (uint64_t *******)&stack0xffffffffffffff20;
      v19 = ax21;
      ax28 = ax20;
    }
LAB_001c0b94:
    ax20 = v15;
    av2.hi = ax20;
    av2.lo = v19;
    av1.hi = ax28;
    av1.lo = v19;
    sk_h_003497ec();
    av27 = sk_h_001a89a8();
    v17 = av27.hi;
    sk_h_0034d6c8((uint64_t)v19 & 0xffffffffffff);
    if ((xo8_08 == 0) &&
       ((((uint64_t)v19 & ((uint64_t)ax28 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(ax28);
    }
    else {
      ax21 = (uint64_t *******)(v17 >> 0x38 & 0xf);
      if (((uint64_t)ax28 >> 0x3d & 1) == 0) {
        sk_h_00358858();
        v15 = xo8_09;
        if (!(bool)v14) {
          v15 = ax21;
        }
      }
      else if ((v17 >> 0x3d & 1) == 0) {
        v15 = (uint64_t *******)(av27.lo & 0xffffffffffff);
      }
      else {
        av23 = sk_h_003510ac();
        sk_h_0034c51c(av23.lo,av23.hi,av27.lo);
        v15 = ax21;
        if (!(bool)v14) {
          sk_h_0034ecf8();
          sk_masked_free();
          sk_masked_free(v17);
          av27 = av2;
          goto LAB_001c0c00;
        }
      }
      ax20 = (uint64_t *******)&stack0xffffffffffffff20;
      sk_h_00350ab8();
      sk_h_00356cd4();
      sk_masked_free(v17);
      ax21 = v15;
      av27 = av1;
    }
LAB_001c0c00:
    v17 = av27.hi;
    v15 = av27.lo;
    av3.hi = ax21;
    av3.lo = v15;
    sk_h_0034d044((uint64_t)ax25 & 0xffffffffffff);
    if ((xo8_10 == 0) &&
       ((((uint64_t)ax25 & ((uint64_t)ax24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(ax24);
      stk_b8 = v15;
    }
    else {
      v19 = (uint64_t *******)(v17 >> 0x38 & 0xf);
      if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
        sk_h_00358858();
        v20 = xo8_11;
        if (!(bool)v14) {
          v20 = v19;
        }
      }
      else if ((v17 >> 0x3d & 1) == 0) {
        v20 = (uint64_t *******)((uint64_t)v15 & 0xffffffffffff);
      }
      else {
        sk_h_0034ffa8();
        sk_h_0034c51c();
        v20 = v19;
        if (!(bool)v14) {
          sk_h_00350b90();
          sk_masked_free(ax24);
          sk_masked_free(v17);
          stk_b8 = ax20;
          av27 = av3;
          goto LAB_001c0c54;
        }
      }
      ax20 = &stk_b8;
      sk_h_00350ab8();
      sk_h_00352cc8();
      sk_h_002a4c98();
      sk_masked_free(v17);
      av27.hi = pppppppuStack_b0;
      av27.lo = v15;
      v19 = v20;
    }
  }
LAB_001c0c54:
  av4.hi = ax25;
  av4.lo = v19;
  pppppppuStack_b0 = av27.hi;
  v15 = av27.lo;
  sk_h_00359ce4();
  av7.hi = pppppppuStack_b0;
  av7.lo = v19;
  if (xo8_12 != 0) {
    sk_alloc_pages(ax22);
    sk_enum_err(0x17);
    av23 = sk_h_00354e0c();
    sk_h_0035a924();
    sk_h_0035a25c();
    sk_rt_hook_u();
    if ((xo8_13 == 0) &&
       ((((uint64_t)ax21 & ((uint64_t)ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(ax20);
    }
    else {
      if (((uint64_t)ax20 >> 0x3d & 1) == 0) {
        sk_h_00359aa4();
      }
      else if (((uint64_t)ax25 >> 0x3d & 1) != 0) {
        sk_h_0011aa70();
        v19 = (uint64_t *******)sk_rt_slot2();
        av4.hi = v22;
        av4.lo = v19;
        if (!(bool)v14) {
          sk_h_00355d90();
          sk_masked_free();
          sk_masked_free(ax25);
          ax21 = v19;
          goto LAB_001c0d1c;
        }
      }
      ax20 = (uint64_t *******)&stack0xffffffffffffff20;
      sk_h_003509e0();
      sk_h_00352db8();
      sk_h_002a4c98();
      sk_masked_free(ax25);
      av4 = av23;
    }
LAB_001c0d1c:
    v17 = av4.hi;
    v21 = av4.lo;
    av5.hi = ax20;
    av5.lo = v21;
    sk_h_0034de14((uint64_t)v21 & 0xffffffffffff);
    if ((xo8_14 == 0) &&
       ((((uint64_t)v21 & (v17 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(v17);
    }
    else {
      if ((v17 >> 0x3d & 1) == 0) {
        if ((ax22 >> 0x3d & 1) != 0) {
          v15 = ax24;
        }
      }
      else if ((ax22 >> 0x3d & 1) != 0) {
        sk_h_003509e0();
        sk_h_003497c8();
        v15 = ax24;
        if (!(bool)v14) {
          sk_h_00351a50();
          sk_masked_free(v17);
          sk_masked_free(ax22);
          av6 = av5;
          goto LAB_001c0d64;
        }
      }
      sk_alloc_pages(ax22);
      sk_h_0034c5bc();
      sk_h_002a4c98();
      sk_h_003593a8();
      ax24 = v15;
      av6 = av4;
    }
LAB_001c0d64:
    av7.hi = ax24;
    av7.lo = v21;
    ax23 = av6.lo;
    sk_h_003497ec();
    sk_h_001a89a8();
    sk_h_00354cd8();
    sk_h_0034b5e8();
    if ((xo8_15 == 0) &&
       ((((uint64_t)ax23 & (av6.hi ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(av6.hi);
    }
    else {
      sk_h_0035072c();
      sk_h_00267820();
      sk_masked_free(ax24);
      av7 = av6;
    }
    ax20 = pppppppuStack_b0;
    v18 = av7.hi;
    v19 = av7.lo;
    v17 = sk_h_00349cbc(stk_b8);
    if ((xo8_16 == 0) &&
       (((v17 & ((uint64_t)ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(ax20);
      stk_b8 = v19;
    }
    else {
      ax23 = (uint64_t *******)(v18 >> 0x38 & 0xf);
      if (((uint64_t)ax20 >> 0x3d & 1) == 0) {
        sk_h_00354b8c();
        v21 = xo8_17;
        if (!(bool)v14) {
          v21 = ax23;
        }
      }
      else if ((v18 >> 0x3d & 1) == 0) {
        v21 = (uint64_t ******)((uint64_t)v19 & 0xffffffffffff);
      }
      else {
        sk_h_00350624();
        av23 = sk_h_0034b1a0();
        av7.hi = av23.hi;
        av7.lo = v19;
        v21 = ax23;
        if (!(bool)v14) {
          sk_masked_free(ax20);
          sk_masked_free(v18);
          ax21 = av23.lo;
          stk_b8 = av23.lo;
          goto LAB_001c0e1c;
        }
      }
      ax20 = &stk_b8;
      sk_h_0035072c();
      sk_h_00356e1c();
      sk_h_002a4c98();
      sk_masked_free(v18);
      av7.hi = pppppppuStack_b0;
      av7.lo = v19;
      ax23 = (uint64_t *******)v21;
    }
  }
LAB_001c0e1c:
  av11.hi = ax23;
  av11.lo = ax22;
  av10.hi = ax23;
  av10.lo = ax22;
  av8.hi = ax23;
  av8.lo = ax22;
  pppppppuStack_b0 = av7.hi;
  v17 = av7.lo;
  av9.hi = v17;
  av9.lo = ax21;
  if (stk_f8 == (uint64_t *******)0x0) {
    sk_masked_free(ax22);
    sk_free(v22);
    av12.hi = pppppppuStack_b0;
    av12.lo = stk_b8;
    return av12;
  }
  sk_masked_free(ax22);
  sk_free(v22);
  sk_enum_err(0x16);
  av23 = sk_h_00356b44();
  sk_h_00359cd8((const char *)0x005ce840 /* __Underlying_error_ */);
  sk_h_001a89a8();
  sk_h_00352c80();
  sk_h_0034b824(ax22 & 0xffffffffffff);
  if ((xo8_18 == 0) &&
     (((ax22 & ((uint64_t)ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax20);
    av8 = av9;
  }
  else {
    if (((uint64_t)ax20 >> 0x3d & 1) == 0) {
      sk_h_0034a798();
    }
    else if (((v17 >> 0x3d & 1) != 0) && (sk_h_00349580(ax22), !(bool)v14)) {
      sk_h_0034f078();
      sk_masked_free();
      sk_masked_free(v17);
      goto LAB_001c0ebc;
    }
    sk_h_0034c0a4();
    sk_h_002a4c98();
    sk_masked_free(v17);
    av8 = av23;
  }
LAB_001c0ebc:
  v28 = av8.hi;
  sk_h_0034a210();
  av23 = sk_rt_desc();
  sk_h_0034f688(av23.lo,av23.hi,av23.lo);
  sk_h_00205844(&stack0xffffffffffffff10,&stack0xffffffffffffff20);
  sk_free(stk_f8);
  sk_h_003497ec();
  sk_h_001a89a8();
  sk_h_00352c80();
  v18 = sk_h_00349cbc(av8.lo);
  if ((xo8_19 == 0) && (((v18 & (v28 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v28);
  }
  else {
    if ((v28 >> 0x3d & 1) == 0) {
      sk_h_0034a798();
    }
    else if (((v17 >> 0x3d & 1) != 0) && (sk_h_00349580(), !(bool)v14)) {
      sk_h_0034f078();
      sk_masked_free();
      sk_masked_free(v17);
      av9 = av10;
      goto LAB_001c0f40;
    }
    sk_h_0034c0a4();
    sk_h_002a4c98();
    sk_masked_free(v17);
    av9 = av8;
  }
LAB_001c0f40:
  v22 = pppppppuStack_b0;
  v18 = av9.hi;
  v17 = sk_h_00349cbc(stk_b8);
  if ((xo8_20 == 0) &&
     (((v17 & ((uint64_t)v22 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v22);
  }
  else {
    if (((uint64_t)v22 >> 0x3d & 1) == 0) {
      sk_h_0034a798();
    }
    else if (((v18 >> 0x3d & 1) != 0) && (sk_h_00349580(), !(bool)v14)) {
      sk_h_0034f078();
      sk_masked_free();
      sk_masked_free(v18);
      return av11;
    }
    sk_h_0034c0a4();
    sk_h_002a4c98();
    sk_masked_free(v18);
    av9.hi = pppppppuStack_b0;
    av9.lo = stk_b8;
  }
  return av9;
}



/* FUN_001c11b4 @ 0x001c11b4   (est. sk_r4_001c11b4)
 * Ghidra: void FUN_001c11b4(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c11b4(uint64_t p1,uint64_t p2)

{
  sk_masked_free(p2);
  sk_h_00019858();
  sk_h_0035187c();
  return;
}



/* FUN_001c11d8 @ 0x001c11d8   (est. sk_r4_001c11d8)
 * Ghidra: void FUN_001c11d8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c11d8(void)

{
  uint8_t zf;
  uint64_t xo1;
  long xo8;
  uint64_t v1;
  uint64_t ax21;
  sk_r4_u128_t av2;
  
  sk_h_00357cb4();
  v1 = 0x207865646e49;
  sk_masked_free(0xe000000000000000);
  sk_h_00353820();
  sk_h_002364dc();
  sk_h_00351f28();
  if (((xo1 >> 0x3d & 1) == 0) ||
     (sk_h_003497c8(0x207865646e49,0xe600000000000000), (bool)zf)) {
    sk_h_0034a7ac();
    sk_h_0034c5bc();
    sk_h_002a4c98();
    sk_masked_free();
    ax21 = 0;
    v1 = 0xe600000000000000;
  }
  else {
    sk_h_00354e0c();
    sk_masked_free(0xe600000000000000);
    sk_masked_free();
  }
  sk_rt_hook_u();
  if ((xo8 == 0) && (((ax21 & (v1 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v1);
  }
  else {
    if ((v1 >> 0x3d & 1) != 0) {
      av2 = sk_rt_hook_m();
      sk_rt_slot2(av2.lo,av2.hi,0,0xe000000000000000);
      if (!(bool)zf) {
        sk_h_000b43e8();
        sk_masked_free(v1);
        goto LAB_001c12c0;
      }
    }
    sk_h_00353ad8();
  }
LAB_001c12c0:
  sk_rt_hook_y();
  sk_h_00357c74();
  return;
}



/* FUN_001c12dc @ 0x001c12dc   (est. sk_r4_001c12dc)
 * Ghidra: void FUN_001c12dc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c12dc(void)

{
  sk_h_0035aaf0();
  sk_h_0009461c();
  return;
}



/* FUN_001c1300 @ 0x001c1300   (est. sk_r4_001c1300)
 * Ghidra: void FUN_001c1300(undefined8 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1300(uint64_t *p1)

{
  sk_r4_001c11b4();
  p1[1] = 0;
  p1[2] = 0;
  *p1 = 0;
  *(uint8_t *)(p1 + 3) = 0;
  return;
}



/* FUN_001c133c @ 0x001c133c   (est. sk_r4_001c133c)
 * Ghidra: void FUN_001c133c(long param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c133c(long p1)

{
  sk_r4_001c11d8();
  sk_h_00359c4c();
  *(uint8_t *)(p1 + 0x18) = 0;
  return;
}



/* FUN_001c1388 @ 0x001c1388   (est. sk_r4_001c1388)
 * Ghidra: void FUN_001c1388(undefined8 *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sk_r4_001c1388(uint64_t *p1,uint64_t p2,uint64_t p3,uint64_t p4,
                 uint8_t p5,long *p6,uint64_t p7,uint64_t p8)

{
  uint64_t v1;
  uint64_t v2;
  long r3;
  long r4;
  uint8_t auStack_a8 [72];
  
  v1 = (**(code **)(*p6 + 0x40))();
  v2 = sk_rt_desc(0x656120,&datum_004e7f10);
  r3 = sk_h_0036a9a0(v2,auStack_a8);
  v2 = _DAT_004baeb0;
  *(uint64_t *)(r3 + 0x18) = uRam00000000004baeb8;
  *(uint64_t *)(r3 + 0x10) = v2;
  *(uint64_t *)(r3 + 0x38) = 0x678560;
  *(void **)(r3 + 0x40) = &datum_004f1878;
  r4 = sk_h_0036a940(0x66a9e8,0x29,7);
  *(long *)(r3 + 0x20) = r4;
  *(uint64_t *)(r4 + 0x10) = p2;
  *(uint64_t *)(r4 + 0x18) = p3;
  *(uint64_t *)(r4 + 0x20) = p4;
  *(uint8_t *)(r4 + 0x28) = p5;
  sk_alloc_pages(p3);
  sk_h_001a18f8(r3);
  *p1 = v1;
  p1[1] = p7;
  p1[2] = p8;
  p1[3] = 0;
  *(uint8_t *)(p1 + 9) = 3;
  sk_alloc_pages(p8);
  return;
}



/* FUN_001c14ac @ 0x001c14ac   (est. sk_r4_001c14ac)
 * Ghidra: void FUN_001c14ac(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sk_r4_001c14ac(void)

{
  uint64_t v1;
  long r2;
  uint64_t ix5;
  code *xo8;
  long xo16;
  uint64_t ax20;
  uint64_t ax30;
  
  sk_h_000b4594();
  sk_h_00355ff4();
  sk_h_00352c34();
  sk_h_0035694c();
  sk_h_0031a5dc(ix5);
  sk_rt_hook_t();
  (*xo8)();
  sk_h_0034dcfc();
  v1 = sk_rt_desc();
  r2 = sk_h_0036a9a0(v1,&stack0x00000008);
  v1 = _DAT_004baeb0;
  *(uint64_t *)(r2 + 0x18) = uRam00000000004baeb8;
  *(uint64_t *)(r2 + 0x10) = v1;
  sk_h_0034dc3c();
  sk_object_lock();
  sk_h_0034b960();
  sk_lock_ref();
  sk_h_0035893c();
  sk_h_00319a4c();
  sk_rt_hook_r();
  (**(code **)(xo16 + 0x10))();
  sk_h_001a18f8(r2);
  sk_h_00359178(ax20);
  sk_h_000b45b0(ax30);
  return;
}



/* FUN_001c1574 @ 0x001c1574   (est. sk_r4_001c1574)
 * Ghidra: void FUN_001c1574(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sk_r4_001c1574(uint64_t p1,uint64_t p2,uint64_t p3)

{
  uint64_t v1;
  long r2;
  uint64_t v3;
  uint64_t v4;
  long r5;
  long xo1;
  code *xo8;
  code *xo8_00;
  uint64_t ax20;
  uint64_t ax30;
  
  sk_h_0035638c();
  r2 = sk_h_00353430();
  sk_h_0034b440();
  sk_h_0017e880();
  sk_rt_hook_x();
  v3 = (*xo8)();
  v4 = sk_rt_desc(0x656120,&datum_004e7f10);
  r5 = sk_h_0036a9a0(v4,&stack0x00000028);
  v4 = _DAT_004baeb0;
  *(uint64_t *)(r5 + 0x18) = uRam00000000004baeb8;
  *(uint64_t *)(r5 + 0x10) = v4;
  v4 = *(uint64_t *)(r2 + 0x18);
  v1 = *(uint64_t *)(r2 + 0x20);
  sk_h_00350738();
  sk_h_000dbcc8();
  sk_h_00319a90(v1);
  sk_rt_hook_s();
  (*xo8_00)();
  sk_r4_001c11d8();
  if (xo1 != 0) {
    sk_h_0035351c();
    *(uint64_t *)(r5 + 0x38) = 0x6785e0;
    *(void **)(r5 + 0x40) = &datum_004f18a8;
    r2 = sk_h_0036a940(0x66a9c0,0x29,7);
    *(long *)(r5 + 0x20) = r2;
    *(uint64_t *)(r2 + 0x10) = ax20;
    *(uint64_t *)(r2 + 0x18) = v4;
    *(uint64_t *)(r2 + 0x20) = p3;
    *(uint8_t *)(r2 + 0x28) = 0;
    sk_h_001a18f8(r5);
    sk_h_00359178(v3);
    sk_h_00356370(ax30);
    return;
  }
  sk_h_00348898(1);
  sk_rt_hook_w();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c169c @ 0x001c169c   (est. sk_r4_001c169c)
 * Ghidra: void FUN_001c169c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c169c(void)

{
  uint64_t v1;
  uint64_t *xo8;
  code *xo8_00;
  uint64_t ax19;
  uint64_t ax21;
  
  sk_h_00350b54();
  sk_h_0034b440();
  sk_h_0017e880();
  sk_rt_hook_x();
  v1 = (*xo8_00)();
  *xo8 = v1;
  xo8[1] = ax21;
  xo8[2] = ax19;
  xo8[3] = 0;
  *(uint8_t *)(xo8 + 9) = 3;
  sk_alloc_pages();
  return;
}



/* FUN_001c1700 @ 0x001c1700   (est. sk_r4_001c1700)
 * Ghidra: void FUN_001c1700(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1700(void)

{
  sk_rt_hook_a();
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1730 @ 0x001c1730   (est. sk_r4_001c1730)
 * Ghidra: void FUN_001c1730(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1730(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1754);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1778);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c179c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c17c0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c17e4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1808);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c182c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1850);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1874);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1754 @ 0x001c1754   (est. sk_r4_001c1754)
 * Ghidra: void FUN_001c1754(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1754(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1778);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c179c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c17c0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c17e4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1808);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c182c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1850);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1874);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1778 @ 0x001c1778   (est. sk_r4_001c1778)
 * Ghidra: void FUN_001c1778(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1778(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c179c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c17c0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c17e4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1808);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c182c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1850);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1874);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c179c @ 0x001c179c   (est. sk_r4_001c179c)
 * Ghidra: void FUN_001c179c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c179c(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c17c0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c17e4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1808);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c182c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1850);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1874);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c17c0 @ 0x001c17c0   (est. sk_r4_001c17c0)
 * Ghidra: void FUN_001c17c0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c17c0(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c17e4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1808);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c182c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1850);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1874);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c17e4 @ 0x001c17e4   (est. sk_r4_001c17e4)
 * Ghidra: void FUN_001c17e4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c17e4(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1808);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c182c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1850);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1874);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1808 @ 0x001c1808   (est. sk_r4_001c1808)
 * Ghidra: void FUN_001c1808(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1808(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c182c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1850);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1874);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c182c @ 0x001c182c   (est. sk_r4_001c182c)
 * Ghidra: void FUN_001c182c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c182c(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1850);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1874);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1850 @ 0x001c1850   (est. sk_r4_001c1850)
 * Ghidra: void FUN_001c1850(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1850(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1874);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1874 @ 0x001c1874   (est. sk_r4_001c1874)
 * Ghidra: void FUN_001c1874(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1874(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1898);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1898 @ 0x001c1898   (est. sk_r4_001c1898)
 * Ghidra: void FUN_001c1898(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1898(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18bc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c18bc @ 0x001c18bc   (est. sk_r4_001c18bc)
 * Ghidra: void FUN_001c18bc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c18bc(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c18e0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c18e0 @ 0x001c18e0   (est. sk_r4_001c18e0)
 * Ghidra: void FUN_001c18e0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c18e0(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1904);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1904 @ 0x001c1904   (est. sk_r4_001c1904)
 * Ghidra: void FUN_001c1904(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1904(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1928);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1928 @ 0x001c1928   (est. sk_r4_001c1928)
 * Ghidra: void FUN_001c1928(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1928(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c194c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c194c @ 0x001c194c   (est. sk_r4_001c194c)
 * Ghidra: void FUN_001c194c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c194c(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1970);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1970 @ 0x001c1970   (est. sk_r4_001c1970)
 * Ghidra: void FUN_001c1970(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1970(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1994);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1994 @ 0x001c1994   (est. sk_r4_001c1994)
 * Ghidra: void FUN_001c1994(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1994(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19b8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c19b8 @ 0x001c19b8   (est. sk_r4_001c19b8)
 * Ghidra: void FUN_001c19b8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c19b8(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c19dc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c19dc @ 0x001c19dc   (est. sk_r4_001c19dc)
 * Ghidra: void FUN_001c19dc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c19dc(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a00);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1a00 @ 0x001c1a00   (est. sk_r4_001c1a00)
 * Ghidra: void FUN_001c1a00(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1a00(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a24);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1a24 @ 0x001c1a24   (est. sk_r4_001c1a24)
 * Ghidra: void FUN_001c1a24(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1a24(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a48);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1a48 @ 0x001c1a48   (est. sk_r4_001c1a48)
 * Ghidra: void FUN_001c1a48(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1a48(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a6c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1a6c @ 0x001c1a6c   (est. sk_r4_001c1a6c)
 * Ghidra: void FUN_001c1a6c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1a6c(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1a90);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1a90 @ 0x001c1a90   (est. sk_r4_001c1a90)
 * Ghidra: void FUN_001c1a90(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1a90(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ab4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1ab4 @ 0x001c1ab4   (est. sk_r4_001c1ab4)
 * Ghidra: void FUN_001c1ab4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1ab4(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1ad8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1ad8 @ 0x001c1ad8   (est. sk_r4_001c1ad8)
 * Ghidra: void FUN_001c1ad8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1ad8(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1afc);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1afc @ 0x001c1afc   (est. sk_r4_001c1afc)
 * Ghidra: void FUN_001c1afc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1afc(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b20);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1b20 @ 0x001c1b20   (est. sk_r4_001c1b20)
 * Ghidra: void FUN_001c1b20(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1b20(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b44);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1b44 @ 0x001c1b44   (est. sk_r4_001c1b44)
 * Ghidra: void FUN_001c1b44(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1b44(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b68);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1b68 @ 0x001c1b68   (est. sk_r4_001c1b68)
 * Ghidra: void FUN_001c1b68(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1b68(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1b8c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1b8c @ 0x001c1b8c   (est. sk_r4_001c1b8c)
 * Ghidra: void FUN_001c1b8c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1b8c(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bb0);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1bb0 @ 0x001c1bb0   (est. sk_r4_001c1bb0)
 * Ghidra: void FUN_001c1bb0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1bb0(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bd4);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1bd4 @ 0x001c1bd4   (est. sk_r4_001c1bd4)
 * Ghidra: void FUN_001c1bd4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1bd4(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1bf8);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1bf8 @ 0x001c1bf8   (est. sk_r4_001c1bf8)
 * Ghidra: void FUN_001c1bf8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1bf8(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c1c);
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1c1c @ 0x001c1c1c   (est. sk_r4_001c1c1c)
 * Ghidra: void FUN_001c1c1c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1c1c(void)

{
  sk_rt_hook_a();
  sk_h_00348758();
  sk_rt_hook_a(sk_r4_001c1c40);
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1c40 @ 0x001c1c40   (est. sk_r4_001c1c40)
 * Ghidra: void FUN_001c1c40(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1c40(void)

{
  sk_rt_hook_a();
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1c70 @ 0x001c1c70   (est. sk_r4_001c1c70)
 * Ghidra: void FUN_001c1c70(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1c70(void)

{
  sk_rt_hook_a();
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1ca0 @ 0x001c1ca0   (est. sk_r4_001c1ca0)
 * Ghidra: void FUN_001c1ca0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1ca0(void)

{
  sk_rt_hook_a();
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1cd0 @ 0x001c1cd0   (est. sk_r4_001c1cd0)
 * Ghidra: void FUN_001c1cd0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1cd0(void)

{
  sk_rt_hook_a();
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c1d00 @ 0x001c1d00   (est. sk_r4_001c1d00)
 * Ghidra: void FUN_001c1d00(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1d00(uint64_t p1)

{
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av1;
  
  av1 = sk_rt_hook_l(p1,p1);
  sk_rt_hook_n(av1.lo,av1.hi,*(uint64_t *)(xo8 + 0x188));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c1d04 @ 0x001c1d04   (est. sk_r4_001c1d04)
 * Ghidra: void FUN_001c1d04(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1d04(uint64_t p1)

{
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av1;
  
  av1 = sk_rt_hook_l(p1,p1);
  sk_rt_hook_n(av1.lo,av1.hi,*(uint64_t *)(xo8 + 0x188));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c1d5c @ 0x001c1d5c   (est. sk_r4_001c1d5c)
 * Ghidra: void FUN_001c1d5c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1d5c(void)

{
  code *xo8;
  code *xo8_00;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t v1;
  uint64_t v2;
  sk_r4_u128_t av3;
  
  sk_rt_hook_q();
  v2 = *(uint64_t *)(xo16 + 0x188);
  sk_h_00349734();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_rt_hook_e();
  sk_h_0035147c();
  av3 = sk_rt_hook_p(*(uint64_t *)(xo16_00 + 0x198));
  (*xo10)(av3.lo,av3.hi,v2);
  sk_h_0035147c();
  v1 = *(uint64_t *)(xo16_01 + 400);
  sk_h_0031a5dc(v1);
  v2 = sk_rt_hook_o();
  (*xo8)(v2,v1);
  sk_h_0034ea18();
  (*xo8_00)();
  sk_h_00356c54();
  return;
}



/* FUN_001c1e34 @ 0x001c1e34   (est. sk_r4_001c1e34)
 * Ghidra: void FUN_001c1e34(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c1e34(void)

{
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  uint64_t v1;
  uint64_t ax30;
  
  sk_rt_hook_c();
  sk_rt_hook_j();
  sk_rt_hook_l();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_003505c4();
  sk_object_lock();
  sk_h_00348d4c();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_rt_hook_h();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034b980();
    (*xo9)();
    sk_h_003561e8();
    sk_rt_hook_z(v1);
    sk_h_0035a69c();
    sk_h_0034da08();
    (*xo8_01)();
    sk_h_00358618();
    sk_h_00350a34();
    (*xo8_02)();
    sk_h_00351348();
    sk_rt_hook_d(ax30);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c2074 @ 0x001c2074   (est. sk_r4_001c2074)
 * Ghidra: void FUN_001c2074(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2074(void)

{
  sk_r4_001c2bd0();
  return;
}



/* FUN_001c20a0 @ 0x001c20a0   (est. sk_r4_001c20a0)
 * Ghidra: void FUN_001c20a0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c20a0(void)

{
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  uint64_t v1;
  uint64_t ax30;
  uint64_t v2;
  
  sk_h_003549e4();
  v2 = sk_rt_hook_j();
  sk_rt_hook_l();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_003505c4();
  sk_object_lock();
  sk_h_00348d4c();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_rt_hook_h();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034b980();
    (*xo9)();
    sk_h_003561e8();
    sk_h_0031a32c(v1);
    sk_h_0035a69c();
    sk_h_0034da08(v2);
    (*xo8_01)();
    sk_h_00358618();
    sk_h_00350a34();
    (*xo8_02)();
    sk_h_00351348();
    sk_h_00354a0c(ax30);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c22c4 @ 0x001c22c4   (est. sk_r4_001c22c4)
 * Ghidra: void FUN_001c22c4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c22c4(void)

{
  sk_r4_001c25b0();
  return;
}



/* FUN_001c22f0 @ 0x001c22f0   (est. sk_r4_001c22f0)
 * Ghidra: void FUN_001c22f0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c22f0(void)

{
  sk_r4_001c2a98();
  return;
}



/* FUN_001c22f4 @ 0x001c22f4   (est. sk_r4_001c22f4)
 * Ghidra: void FUN_001c22f4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c22f4(void)

{
  sk_r4_001c2a98();
  return;
}



/* FUN_001c2320 @ 0x001c2320   (est. sk_r4_001c2320)
 * Ghidra: void FUN_001c2320(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2320(void)

{
  sk_r4_001c2ee4();
  return;
}



/* FUN_001c2324 @ 0x001c2324   (est. sk_r4_001c2324)
 * Ghidra: void FUN_001c2324(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2324(void)

{
  sk_r4_001c2ee4();
  return;
}



/* FUN_001c2350 @ 0x001c2350   (est. sk_r4_001c2350)
 * Ghidra: void FUN_001c2350(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2350(void)

{
  sk_h_00354248();
  sk_r4_001c2478();
  return;
}



/* FUN_001c2354 @ 0x001c2354   (est. sk_r4_001c2354)
 * Ghidra: void FUN_001c2354(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2354(void)

{
  sk_h_00354248();
  sk_r4_001c2478();
  return;
}



/* FUN_001c236c @ 0x001c236c   (est. sk_r4_001c236c)
 * Ghidra: void FUN_001c236c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c236c(void)

{
  sk_r4_001c25b0();
  return;
}



/* FUN_001c2370 @ 0x001c2370   (est. sk_r4_001c2370)
 * Ghidra: void FUN_001c2370(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2370(void)

{
  sk_r4_001c25b0();
  return;
}



/* FUN_001c239c @ 0x001c239c   (est. sk_r4_001c239c)
 * Ghidra: void FUN_001c239c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c239c(void)

{
  sk_r4_001c26fc();
  return;
}



/* FUN_001c23a0 @ 0x001c23a0   (est. sk_r4_001c23a0)
 * Ghidra: void FUN_001c23a0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c23a0(void)

{
  sk_r4_001c26fc();
  return;
}



/* FUN_001c23cc @ 0x001c23cc   (est. sk_r4_001c23cc)
 * Ghidra: void FUN_001c23cc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c23cc(void)

{
  sk_r4_001c25b0();
  return;
}



/* FUN_001c23d0 @ 0x001c23d0   (est. sk_r4_001c23d0)
 * Ghidra: void FUN_001c23d0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c23d0(void)

{
  sk_r4_001c25b0();
  return;
}



/* FUN_001c23fc @ 0x001c23fc   (est. sk_r4_001c23fc)
 * Ghidra: void FUN_001c23fc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c23fc(void)

{
  sk_r4_001c2a98();
  return;
}



/* FUN_001c2400 @ 0x001c2400   (est. sk_r4_001c2400)
 * Ghidra: void FUN_001c2400(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2400(void)

{
  sk_r4_001c2a98();
  return;
}



/* FUN_001c242c @ 0x001c242c   (est. sk_r4_001c242c)
 * Ghidra: void FUN_001c242c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c242c(void)

{
  sk_r4_001c2ee4();
  return;
}



/* FUN_001c2430 @ 0x001c2430   (est. sk_r4_001c2430)
 * Ghidra: void FUN_001c2430(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2430(void)

{
  sk_r4_001c2ee4();
  return;
}



/* FUN_001c245c @ 0x001c245c   (est. sk_r4_001c245c)
 * Ghidra: void FUN_001c245c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c245c(void)

{
  sk_h_0035422c();
  sk_r4_001c2478();
  return;
}



/* FUN_001c2460 @ 0x001c2460   (est. sk_r4_001c2460)
 * Ghidra: void FUN_001c2460(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2460(void)

{
  sk_h_0035422c();
  sk_r4_001c2478();
  return;
}



/* FUN_001c2478 @ 0x001c2478   (est. sk_r4_001c2478)
 * Ghidra: void FUN_001c2478(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2478(void)

{
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  uint64_t v1;
  code *ax25;
  uint64_t arg;
  uint32_t stk_c;
  
  sk_rt_hook_c();
  sk_h_0034f23c();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_003515e4();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034baa8();
  sk_h_00352cd4();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a848();
    (*xo9)();
    sk_h_00352e00();
    (*ax25)(v1);
    sk_h_00356284();
    sk_h_0034dce4(stk_c);
    (*xo8_01)();
    sk_h_0034c130();
    (*xo8_02)();
    sk_h_00351348();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c2584 @ 0x001c2584   (est. sk_r4_001c2584)
 * Ghidra: void FUN_001c2584(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2584(void)

{
  sk_r4_001c25b0();
  return;
}



/* FUN_001c25b0 @ 0x001c25b0   (est. sk_r4_001c25b0)
 * Ghidra: void FUN_001c25b0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c25b0(void)

{
  uint64_t v1;
  code *ix4;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  uint64_t v2;
  uint64_t arg;
  
  v1 = sk_rt_hook_c();
  sk_h_00353ee4();
  sk_rt_hook_l();
  v2 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_003515e4();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034baa8();
  sk_h_00352cd4();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a848();
    (*xo9)();
    sk_h_00352e00();
    (*ix4)(v2);
    sk_h_00356284();
    sk_h_00350210(v1);
    (*xo8_01)();
    sk_h_0034c130();
    (*xo8_02)();
    sk_h_00351348();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c26d0 @ 0x001c26d0   (est. sk_r4_001c26d0)
 * Ghidra: void FUN_001c26d0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c26d0(void)

{
  sk_r4_001c26fc();
  return;
}



/* FUN_001c26fc @ 0x001c26fc   (est. sk_r4_001c26fc)
 * Ghidra: void FUN_001c26fc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c26fc(void)

{
  uint64_t xo1;
  code *ix5;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t v1;
  uint64_t arg;
  uint64_t stk_18;
  
  sk_rt_hook_c();
  sk_h_0034a674();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_00351dfc();
  sk_object_lock();
  sk_rt_hook_f();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034c8f8();
  sk_h_003597c0();
  if (*(long *)(xo16_01 + 0x40) == xo8_00) {
    sk_h_00359524();
    sk_h_0035399c();
    sk_h_003504c4();
    (*xo9)();
    sk_h_0035a20c();
    v1 = (*ix5)(v1);
    sk_h_00353948(v1,stk_18,xo1);
    (*xo8_01)();
    sk_h_0035145c(*(uint64_t *)(xo16_00 + 8));
    (*xo8_02)();
    sk_h_00352df4();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c2a6c @ 0x001c2a6c   (est. sk_r4_001c2a6c)
 * Ghidra: void FUN_001c2a6c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2a6c(void)

{
  sk_r4_001c2a98();
  return;
}



/* FUN_001c2a98 @ 0x001c2a98   (est. sk_r4_001c2a98)
 * Ghidra: void FUN_001c2a98(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2a98(void)

{
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  uint64_t v1;
  code *ax25;
  uint64_t arg;
  uint32_t stk_c;
  
  sk_rt_hook_c();
  sk_h_0034f23c();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_003515e4();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034baa8();
  sk_h_00352cd4();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a848();
    (*xo9)();
    sk_h_00352e00();
    (*ax25)(v1);
    sk_h_00356284();
    sk_h_0034dce4(stk_c);
    (*xo8_01)();
    sk_h_0034c130();
    (*xo8_02)();
    sk_h_00351348();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c2ba4 @ 0x001c2ba4   (est. sk_r4_001c2ba4)
 * Ghidra: void FUN_001c2ba4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2ba4(void)

{
  sk_r4_001c2bd0();
  return;
}



/* FUN_001c2bd0 @ 0x001c2bd0   (est. sk_r4_001c2bd0)
 * Ghidra: void FUN_001c2bd0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2bd0(void)

{
  uint64_t xo1;
  code *ix5;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t v1;
  uint64_t arg;
  uint64_t stk_18;
  
  sk_rt_hook_c();
  sk_h_0034a674();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_00351dfc();
  sk_object_lock();
  sk_rt_hook_f();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034c8f8();
  sk_h_003597c0();
  if (*(long *)(xo16_01 + 0x40) == xo8_00) {
    sk_h_00359524();
    sk_h_0035399c();
    sk_h_003504c4();
    (*xo9)();
    sk_h_0035a20c();
    v1 = (*ix5)(v1);
    sk_h_00353948(v1,stk_18,xo1);
    (*xo8_01)();
    sk_h_0035145c(*(uint64_t *)(xo16_00 + 8));
    (*xo8_02)();
    sk_h_00352df4();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c2d08 @ 0x001c2d08   (est. sk_r4_001c2d08)
 * Ghidra: void FUN_001c2d08(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2d08(void)

{
  sk_r4_001c32b8();
  return;
}



/* FUN_001c2d34 @ 0x001c2d34   (est. sk_r4_001c2d34)
 * Ghidra: void FUN_001c2d34(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2d34(void)

{
  sk_r4_001c316c();
  return;
}



/* FUN_001c2d38 @ 0x001c2d38   (est. sk_r4_001c2d38)
 * Ghidra: void FUN_001c2d38(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2d38(void)

{
  sk_r4_001c316c();
  return;
}



/* FUN_001c2d64 @ 0x001c2d64   (est. sk_r4_001c2d64)
 * Ghidra: void FUN_001c2d64(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2d64(void)

{
  sk_r4_001c32b8();
  return;
}



/* FUN_001c2d68 @ 0x001c2d68   (est. sk_r4_001c2d68)
 * Ghidra: void FUN_001c2d68(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2d68(void)

{
  sk_r4_001c32b8();
  return;
}



/* FUN_001c2d94 @ 0x001c2d94   (est. sk_r4_001c2d94)
 * Ghidra: void FUN_001c2d94(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2d94(void)

{
  sk_r4_001c2ee4();
  return;
}



/* FUN_001c2d98 @ 0x001c2d98   (est. sk_r4_001c2d98)
 * Ghidra: void FUN_001c2d98(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2d98(void)

{
  sk_r4_001c2ee4();
  return;
}



/* FUN_001c2dc4 @ 0x001c2dc4   (est. sk_r4_001c2dc4)
 * Ghidra: void FUN_001c2dc4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2dc4(void)

{
  sk_r4_001c301c();
  return;
}



/* FUN_001c2dc8 @ 0x001c2dc8   (est. sk_r4_001c2dc8)
 * Ghidra: void FUN_001c2dc8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2dc8(void)

{
  sk_r4_001c301c();
  return;
}



/* FUN_001c2df4 @ 0x001c2df4   (est. sk_r4_001c2df4)
 * Ghidra: void FUN_001c2df4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2df4(void)

{
  sk_r4_001c316c();
  return;
}



/* FUN_001c2df8 @ 0x001c2df8   (est. sk_r4_001c2df8)
 * Ghidra: void FUN_001c2df8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2df8(void)

{
  sk_r4_001c316c();
  return;
}



/* FUN_001c2e24 @ 0x001c2e24   (est. sk_r4_001c2e24)
 * Ghidra: void FUN_001c2e24(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2e24(void)

{
  sk_r4_001c32b8();
  return;
}



/* FUN_001c2e28 @ 0x001c2e28   (est. sk_r4_001c2e28)
 * Ghidra: void FUN_001c2e28(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2e28(void)

{
  sk_r4_001c32b8();
  return;
}



/* FUN_001c2e54 @ 0x001c2e54   (est. sk_r4_001c2e54)
 * Ghidra: void FUN_001c2e54(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2e54(void)

{
  sk_r4_001c3424();
  return;
}



/* FUN_001c2e58 @ 0x001c2e58   (est. sk_r4_001c2e58)
 * Ghidra: void FUN_001c2e58(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2e58(void)

{
  sk_r4_001c3424();
  return;
}



/* FUN_001c2e84 @ 0x001c2e84   (est. sk_r4_001c2e84)
 * Ghidra: void FUN_001c2e84(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2e84(void)

{
  sk_r4_001c32b8();
  return;
}



/* FUN_001c2e88 @ 0x001c2e88   (est. sk_r4_001c2e88)
 * Ghidra: void FUN_001c2e88(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2e88(void)

{
  sk_r4_001c32b8();
  return;
}



/* FUN_001c2eb4 @ 0x001c2eb4   (est. sk_r4_001c2eb4)
 * Ghidra: void FUN_001c2eb4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2eb4(void)

{
  sk_r4_001c2ee4();
  return;
}



/* FUN_001c2eb8 @ 0x001c2eb8   (est. sk_r4_001c2eb8)
 * Ghidra: void FUN_001c2eb8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2eb8(void)

{
  sk_r4_001c2ee4();
  return;
}



/* FUN_001c2ee4 @ 0x001c2ee4   (est. sk_r4_001c2ee4)
 * Ghidra: void FUN_001c2ee4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2ee4(void)

{
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  uint64_t v1;
  code *ax25;
  uint64_t arg;
  uint32_t stk_c;
  
  sk_rt_hook_c();
  sk_h_0034f23c();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_003515e4();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034baa8();
  sk_h_00352cd4();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a848();
    (*xo9)();
    sk_h_00352e00();
    (*ax25)(v1);
    sk_h_00356284();
    sk_h_0034dce4(stk_c);
    (*xo8_01)();
    sk_h_0034c130();
    (*xo8_02)();
    sk_h_00351348();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c2ff0 @ 0x001c2ff0   (est. sk_r4_001c2ff0)
 * Ghidra: void FUN_001c2ff0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c2ff0(void)

{
  sk_r4_001c301c();
  return;
}



/* FUN_001c301c @ 0x001c301c   (est. sk_r4_001c301c)
 * Ghidra: void FUN_001c301c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c301c(void)

{
  uint v1;
  code *ix4;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  uint64_t v2;
  uint64_t arg;
  
  sk_rt_hook_c();
  v1 = sk_h_00353ee4();
  sk_rt_hook_l();
  v2 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_003515e4();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034baa8();
  sk_h_00352cd4();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a848();
    (*xo9)();
    sk_h_00352e00();
    v2 = (*ix4)(v2);
    sk_h_0034dce4(v2,v1 & 0xffffff);
    (*xo8_01)();
    sk_h_0034c130();
    (*xo8_02)();
    sk_h_00351348();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c3140 @ 0x001c3140   (est. sk_r4_001c3140)
 * Ghidra: void FUN_001c3140(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3140(void)

{
  sk_r4_001c316c();
  return;
}



/* FUN_001c316c @ 0x001c316c   (est. sk_r4_001c316c)
 * Ghidra: void FUN_001c316c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c316c(void)

{
  code *ix4;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  uint64_t v1;
  uint64_t ax25;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_00353ee4();
  sk_h_0034cca8();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_003515e4();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034baa8();
  sk_h_00352cd4();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a848();
    (*xo9)();
    sk_h_00352e00();
    v1 = (*ix4)(v1);
    sk_h_0034dce4(v1,ax25 & 0xffffffffff);
    (*xo8_01)();
    sk_h_0034c130();
    (*xo8_02)();
    sk_h_00351348();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c328c @ 0x001c328c   (est. sk_r4_001c328c)
 * Ghidra: void FUN_001c328c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c328c(void)

{
  sk_r4_001c32b8();
  return;
}



/* FUN_001c32b8 @ 0x001c32b8   (est. sk_r4_001c32b8)
 * Ghidra: void FUN_001c32b8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c32b8(void)

{
  uint32_t extraout_w1;
  code *ix5;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t v1;
  uint64_t arg;
  uint64_t stk_18;
  
  sk_rt_hook_c();
  sk_h_0034a674();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_00351dfc();
  sk_object_lock();
  sk_rt_hook_f();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034c8f8();
  sk_h_003597c0();
  if (*(long *)(xo16_01 + 0x40) == xo8_00) {
    sk_h_00359524();
    sk_h_0035399c();
    sk_h_003504c4();
    (*xo9)();
    sk_h_0035a20c();
    v1 = (*ix5)(v1);
    sk_h_00353948(v1,stk_18,extraout_w1);
    (*xo8_01)();
    sk_h_0035145c(*(uint64_t *)(xo16_00 + 8));
    (*xo8_02)();
    sk_h_00352df4();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c33f8 @ 0x001c33f8   (est. sk_r4_001c33f8)
 * Ghidra: void FUN_001c33f8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c33f8(void)

{
  sk_r4_001c3424();
  return;
}



/* FUN_001c3424 @ 0x001c3424   (est. sk_r4_001c3424)
 * Ghidra: void FUN_001c3424(undefined8 param_1,undefined8 param_2,undefined4 param_3,undefined8 param_4,
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3424(uint64_t p1,uint64_t p2,uint32_t p3,uint64_t p4,
                 long p5,uint64_t p6,code *p7)

{
  code *pc1;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo9;
  long xo16;
  long xo16_00;
  uint64_t v2;
  sk_r4_u128_t av3;
  uint64_t arg;
  
  av3 = sk_rt_hook_c();
  sk_rt_hook_l();
  v2 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_00351ba0();
  sk_object_lock();
  sk_h_00348e18();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034beb4();
  if (*(long *)(*(long *)(p5 + -8) + 0x40) == xo8_00) {
    sk_h_0034d384();
    sk_h_00350768();
    (*xo9)();
    pc1 = (code *)(*p7)(v2);
    (*pc1)(av3.lo,av3.hi,p3);
    sk_h_0035060c(*(uint64_t *)(xo16_00 + 8));
    (*xo8_01)();
    sk_h_00352df4();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c37cc @ 0x001c37cc   (est. sk_r4_001c37cc)
 * Ghidra: void FUN_001c37cc(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c37cc(uint64_t p1)

{
  code *xo9;
  long xo16;
  long ax21;
  uint64_t v1;
  
  sk_h_0034ecb8();
  v1 = *(uint64_t *)(ax21 + 400);
  sk_h_00343640(v1);
  sk_h_00351d9c();
  (*xo9)(p1,*(uint64_t *)(xo16 + 0x188),v1);
  return;
}



/* FUN_001c3868 @ 0x001c3868   (est. sk_r4_001c3868)
 * Ghidra: void FUN_001c3868(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3868(void)

{
  code *ix3;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo9;
  code *xo9_00;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t v1;
  uint64_t ax30;
  
  sk_cpu();
  sk_h_0035a6a8();
  sk_rt_hook_l();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_00349600();
  sk_h_003513a8();
  sk_object_lock();
  sk_h_00348d4c();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_rt_hook_h();
  if (*(long *)(xo16_01 + 0x40) == xo8_00) {
    sk_h_0034b980();
    (*xo9)();
    sk_h_003561e8();
    (*ix3)(v1);
    sk_h_0034cfb4();
    (*xo9_00)();
    sk_h_00350a34(*(uint64_t *)(xo16_00 + 8));
    (*xo8_01)();
    sk_h_0008e500(ax30);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c39dc @ 0x001c39dc   (est. sk_r4_001c39dc)
 * Ghidra: void FUN_001c39dc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c39dc(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  
  v1 = sk_rt_hook_l();
  sk_h_0034ece8(v1,*(uint64_t *)(xo8 + 0x188));
  (**(code **)(xo16 + 8))(ax20 + xo9);
  return;
}



/* FUN_001c3a48 @ 0x001c3a48   (est. sk_r4_001c3a48)
 * Ghidra: void FUN_001c3a48(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3a48(void)

{
  sk_rt_hook_b();
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c3a78 @ 0x001c3a78   (est. sk_r4_001c3a78)
 * Ghidra: void FUN_001c3a78(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3a78(void)

{
  sk_rt_hook_b();
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c3aa8 @ 0x001c3aa8   (est. sk_r4_001c3aa8)
 * Ghidra: void FUN_001c3aa8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3aa8(void)

{
  sk_rt_hook_b();
  sk_fatal_msg_tag();
                    /* WARNING: Subroutine does not return */
  sk_fatal_error();
}



/* FUN_001c3ad8 @ 0x001c3ad8   (est. sk_r4_001c3ad8)
 * Ghidra: void FUN_001c3ad8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3ad8(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3afc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b20);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b44);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b68);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b8c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bb0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bd4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bf8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c1c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3afc @ 0x001c3afc   (est. sk_r4_001c3afc)
 * Ghidra: void FUN_001c3afc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3afc(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b20);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b44);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b68);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b8c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bb0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bd4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bf8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c1c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3b20 @ 0x001c3b20   (est. sk_r4_001c3b20)
 * Ghidra: void FUN_001c3b20(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3b20(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b44);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b68);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b8c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bb0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bd4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bf8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c1c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3b44 @ 0x001c3b44   (est. sk_r4_001c3b44)
 * Ghidra: void FUN_001c3b44(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3b44(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b68);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b8c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bb0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bd4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bf8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c1c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3b68 @ 0x001c3b68   (est. sk_r4_001c3b68)
 * Ghidra: void FUN_001c3b68(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3b68(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3b8c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bb0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bd4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bf8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c1c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3b8c @ 0x001c3b8c   (est. sk_r4_001c3b8c)
 * Ghidra: void FUN_001c3b8c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3b8c(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bb0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bd4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bf8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c1c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3bb0 @ 0x001c3bb0   (est. sk_r4_001c3bb0)
 * Ghidra: void FUN_001c3bb0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3bb0(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bd4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bf8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c1c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3bd4 @ 0x001c3bd4   (est. sk_r4_001c3bd4)
 * Ghidra: void FUN_001c3bd4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3bd4(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3bf8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c1c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3bf8 @ 0x001c3bf8   (est. sk_r4_001c3bf8)
 * Ghidra: void FUN_001c3bf8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3bf8(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c1c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3c1c @ 0x001c3c1c   (est. sk_r4_001c3c1c)
 * Ghidra: void FUN_001c3c1c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3c1c(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c40);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3c40 @ 0x001c3c40   (est. sk_r4_001c3c40)
 * Ghidra: void FUN_001c3c40(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3c40(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c64);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3c64 @ 0x001c3c64   (est. sk_r4_001c3c64)
 * Ghidra: void FUN_001c3c64(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3c64(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3c88);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3c88 @ 0x001c3c88   (est. sk_r4_001c3c88)
 * Ghidra: void FUN_001c3c88(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3c88(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cac);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3cac @ 0x001c3cac   (est. sk_r4_001c3cac)
 * Ghidra: void FUN_001c3cac(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3cac(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cd0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3cd0 @ 0x001c3cd0   (est. sk_r4_001c3cd0)
 * Ghidra: void FUN_001c3cd0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3cd0(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3cf4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3cf4 @ 0x001c3cf4   (est. sk_r4_001c3cf4)
 * Ghidra: void FUN_001c3cf4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3cf4(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d18);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3d18 @ 0x001c3d18   (est. sk_r4_001c3d18)
 * Ghidra: void FUN_001c3d18(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3d18(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d3c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3d3c @ 0x001c3d3c   (est. sk_r4_001c3d3c)
 * Ghidra: void FUN_001c3d3c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3d3c(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d60);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3d60 @ 0x001c3d60   (est. sk_r4_001c3d60)
 * Ghidra: void FUN_001c3d60(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3d60(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3d84);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3d84 @ 0x001c3d84   (est. sk_r4_001c3d84)
 * Ghidra: void FUN_001c3d84(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3d84(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3da8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3da8 @ 0x001c3da8   (est. sk_r4_001c3da8)
 * Ghidra: void FUN_001c3da8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3da8(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3dcc);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3dcc @ 0x001c3dcc   (est. sk_r4_001c3dcc)
 * Ghidra: void FUN_001c3dcc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3dcc(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3df0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3df0 @ 0x001c3df0   (est. sk_r4_001c3df0)
 * Ghidra: void FUN_001c3df0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3df0(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e14);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3e14 @ 0x001c3e14   (est. sk_r4_001c3e14)
 * Ghidra: void FUN_001c3e14(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3e14(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e38);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3e38 @ 0x001c3e38   (est. sk_r4_001c3e38)
 * Ghidra: void FUN_001c3e38(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3e38(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e5c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3e5c @ 0x001c3e5c   (est. sk_r4_001c3e5c)
 * Ghidra: void FUN_001c3e5c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3e5c(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3e80);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3e80 @ 0x001c3e80   (est. sk_r4_001c3e80)
 * Ghidra: void FUN_001c3e80(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3e80(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ea4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3ea4 @ 0x001c3ea4   (est. sk_r4_001c3ea4)
 * Ghidra: void FUN_001c3ea4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3ea4(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3ec8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3ec8 @ 0x001c3ec8   (est. sk_r4_001c3ec8)
 * Ghidra: void FUN_001c3ec8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3ec8(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3eec);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3eec @ 0x001c3eec   (est. sk_r4_001c3eec)
 * Ghidra: void FUN_001c3eec(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3eec(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f10);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3f10 @ 0x001c3f10   (est. sk_r4_001c3f10)
 * Ghidra: void FUN_001c3f10(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3f10(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f34);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3f34 @ 0x001c3f34   (est. sk_r4_001c3f34)
 * Ghidra: void FUN_001c3f34(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3f34(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f58);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3f58 @ 0x001c3f58   (est. sk_r4_001c3f58)
 * Ghidra: void FUN_001c3f58(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3f58(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3f7c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3f7c @ 0x001c3f7c   (est. sk_r4_001c3f7c)
 * Ghidra: void FUN_001c3f7c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3f7c(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fa0);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3fa0 @ 0x001c3fa0   (est. sk_r4_001c3fa0)
 * Ghidra: void FUN_001c3fa0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3fa0(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fc4);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3fc4 @ 0x001c3fc4   (est. sk_r4_001c3fc4)
 * Ghidra: void FUN_001c3fc4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3fc4(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c3fe8);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c3fe8 @ 0x001c3fe8   (est. sk_r4_001c3fe8)
 * Ghidra: void FUN_001c3fe8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c3fe8(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c400c);
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c400c @ 0x001c400c   (est. sk_r4_001c400c)
 * Ghidra: void FUN_001c400c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c400c(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  sk_h_00348758();
  sk_rt_hook_b(sk_r4_001c4030);
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c4030 @ 0x001c4030   (est. sk_r4_001c4030)
 * Ghidra: void FUN_001c4030(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4030(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av2;
  
  sk_rt_hook_b();
  v1 = sk_h_00348758();
  av2 = sk_rt_hook_l(v1,v1);
  sk_rt_hook_n(av2.lo,av2.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c4058 @ 0x001c4058   (est. sk_r4_001c4058)
 * Ghidra: void FUN_001c4058(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4058(uint64_t p1)

{
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  sk_r4_u128_t av1;
  
  av1 = sk_rt_hook_l(p1,p1);
  sk_rt_hook_n(av1.lo,av1.hi,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 0x20))(ax20 + xo9);
  return;
}



/* FUN_001c40b0 @ 0x001c40b0   (est. sk_r4_001c40b0)
 * Ghidra: void FUN_001c40b0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c40b0(void)

{
  code *xo8;
  code *xo8_00;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t v1;
  uint64_t v2;
  sk_r4_u128_t av3;
  
  sk_rt_hook_q();
  v2 = *(uint64_t *)(xo16 + 400);
  sk_h_00349734();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_rt_hook_e();
  sk_h_0035147c();
  av3 = sk_rt_hook_p(*(uint64_t *)(xo16_00 + 0x1a0));
  (*xo10)(av3.lo,av3.hi,v2);
  sk_h_0035147c();
  v1 = *(uint64_t *)(xo16_01 + 0x198);
  sk_h_0031a5dc(v1);
  v2 = sk_rt_hook_o();
  (*xo8)(v2,v1);
  sk_h_0034ea18();
  (*xo8_00)();
  sk_h_00356c54();
  return;
}



/* FUN_001c4188 @ 0x001c4188   (est. sk_r4_001c4188)
 * Ghidra: void FUN_001c4188(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4188(void)

{
  code *xo8;
  code *xo8_00;
  code *xo10;
  long xo16;
  long xo16_00;
  
  sk_h_0034ecb8();
  sk_h_003494e8();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_rt_hook_e();
  sk_h_00351d9c();
  sk_h_0034ad8c(*(uint64_t *)(xo16 + 0x1a0));
  (*xo10)();
  sk_h_00351d9c();
  sk_h_00163418(*(uint64_t *)(xo16_00 + 0x198));
  sk_h_0034ac64();
  (*xo8)();
  sk_h_0034da48();
  (*xo8_00)();
  sk_h_00349788();
  sk_h_003504a0();
  sk_object_lock();
  sk_h_0035a938();
  sk_h_0034ed18();
  sk_h_0019dfc4();
  sk_h_0035310c();
  sk_free();
  sk_h_00356c54();
  return;
}



/* FUN_001c4284 @ 0x001c4284   (est. sk_r4_001c4284)
 * Ghidra: void FUN_001c4284(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4284(void)

{
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  uint64_t v1;
  uint64_t ax30;
  
  sk_cpu();
  sk_h_0034cca8();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_00349c14();
  v1 = *(uint64_t *)(xo16 + 0x198);
  sk_h_00349788();
  sk_h_003508d8();
  sk_object_lock();
  sk_h_00348d64();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_rt_hook_h();
  if (*(long *)(xo16_01 + 0x40) == xo8_00) {
    sk_h_00352474();
    sk_h_0034cfc4();
    (*xo9)();
    sk_h_003561e8();
    sk_h_0034a868(*(uint64_t *)(xo16_02 + 0x1a0));
    (*xo10)();
    sk_h_0031a60c(v1);
    sk_h_00350a40();
    sk_h_00350c20();
    (*xo8_01)();
    sk_h_0034eb84();
    (*xo8_02)();
    sk_h_00350a70(*(uint64_t *)(xo16_00 + 8));
    (*xo8_03)();
    v1 = sk_h_00352980();
    sk_h_0008e500(v1,ax30);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c43f4 @ 0x001c43f4   (est. sk_r4_001c43f4)
 * Ghidra: uint FUN_001c43f4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


uint sk_r4_001c43f4(void)

{
  uint v1;
  
  v1 = sk_r4_001c4458();
  return v1 & 1;
}



/* FUN_001c4424 @ 0x001c4424   (est. sk_r4_001c4424)
 * Ghidra: uint FUN_001c4424(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


uint sk_r4_001c4424(void)

{
  uint v1;
  
  v1 = sk_r4_001c4458();
  return v1 & 1;
}



/* FUN_001c4428 @ 0x001c4428   (est. sk_r4_001c4428)
 * Ghidra: uint FUN_001c4428(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


uint sk_r4_001c4428(void)

{
  uint v1;
  
  v1 = sk_r4_001c4458();
  return v1 & 1;
}



/* FUN_001c4458 @ 0x001c4458   (est. sk_r4_001c4458)
 * Ghidra: void FUN_001c4458(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4458(void)

{
  uint v1;
  uint64_t v2;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  sk_h_00349788();
  sk_h_00351298();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a0e0();
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034a1e0(*(uint64_t *)(xo16_01 + 0x1a0));
    (*xo10)();
    sk_h_00356a38();
    (*xo8_01)();
    sk_h_0034a100();
    v1 = (*xo8_02)();
    sk_h_0034bbc8();
    (*xo8_03)();
    sk_h_00350b6c(*(uint64_t *)(xo16 + 8));
    (*xo8_04)();
    v2 = sk_h_00353e7c(v1 & 1);
    sk_rt_hook_d(v2,arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c45b8 @ 0x001c45b8   (est. sk_r4_001c45b8)
 * Ghidra: void FUN_001c45b8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c45b8(void)

{
  sk_r4_001c50bc();
  return;
}



/* FUN_001c45e4 @ 0x001c45e4   (est. sk_r4_001c45e4)
 * Ghidra: void FUN_001c45e4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c45e4(void)

{
  long xo1;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  uint64_t v1;
  uint64_t arg;
  
  sk_h_003549e4();
  sk_rt_hook_l();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034b014();
  v1 = *(uint64_t *)(xo16_00 + 0x198);
  sk_h_00349788();
  sk_h_00350c68();
  sk_object_lock();
  sk_h_00348d7c();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034c8f8();
  if (*(long *)(*(long *)(xo1 + -8) + 0x40) == xo8_00) {
    sk_h_00351d0c();
    sk_h_00356aa0();
    (*xo9)();
    sk_h_003561e8();
    sk_h_0034c1bc(*(uint64_t *)(xo16_02 + 0x1a0));
    (*xo10)();
    sk_h_0031a6cc(v1);
    sk_h_003505d0();
    sk_h_00350b9c();
    v1 = (*xo8_01)();
    sk_h_003514e8(*(uint64_t *)(xo16 + 8));
    (*xo8_02)();
    sk_h_003507c8(*(uint64_t *)(xo16_01 + 8));
    (*xo8_03)();
    sk_h_00352df4(v1);
    sk_h_00354a0c(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c4910 @ 0x001c4910   (est. sk_r4_001c4910)
 * Ghidra: void FUN_001c4910(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4910(void)

{
  sk_h_00354210();
  sk_r4_001c4bec();
  return;
}



/* FUN_001c4928 @ 0x001c4928   (est. sk_r4_001c4928)
 * Ghidra: void FUN_001c4928(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4928(void)

{
  sk_r4_001c4f30();
  return;
}



/* FUN_001c492c @ 0x001c492c   (est. sk_r4_001c492c)
 * Ghidra: void FUN_001c492c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c492c(void)

{
  sk_r4_001c4f30();
  return;
}



/* FUN_001c4958 @ 0x001c4958   (est. sk_r4_001c4958)
 * Ghidra: void FUN_001c4958(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4958(void)

{
  sk_r4_001c5414();
  return;
}



/* FUN_001c495c @ 0x001c495c   (est. sk_r4_001c495c)
 * Ghidra: void FUN_001c495c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c495c(void)

{
  sk_r4_001c5414();
  return;
}



/* FUN_001c4988 @ 0x001c4988   (est. sk_r4_001c4988)
 * Ghidra: void FUN_001c4988(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4988(void)

{
  sk_h_003541f4();
  sk_r4_001c4a74();
  return;
}



/* FUN_001c498c @ 0x001c498c   (est. sk_r4_001c498c)
 * Ghidra: void FUN_001c498c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c498c(void)

{
  sk_h_003541f4();
  sk_r4_001c4a74();
  return;
}



/* FUN_001c49a4 @ 0x001c49a4   (est. sk_r4_001c49a4)
 * Ghidra: void FUN_001c49a4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c49a4(void)

{
  sk_h_003541d8();
  sk_r4_001c4bec();
  return;
}



/* FUN_001c49a8 @ 0x001c49a8   (est. sk_r4_001c49a8)
 * Ghidra: void FUN_001c49a8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c49a8(void)

{
  sk_h_003541d8();
  sk_r4_001c4bec();
  return;
}



/* FUN_001c49c0 @ 0x001c49c0   (est. sk_r4_001c49c0)
 * Ghidra: void FUN_001c49c0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c49c0(void)

{
  sk_h_003541bc();
  sk_r4_001c4d64();
  return;
}



/* FUN_001c49c4 @ 0x001c49c4   (est. sk_r4_001c49c4)
 * Ghidra: void FUN_001c49c4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c49c4(void)

{
  sk_h_003541bc();
  sk_r4_001c4d64();
  return;
}



/* FUN_001c49dc @ 0x001c49dc   (est. sk_r4_001c49dc)
 * Ghidra: void FUN_001c49dc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c49dc(void)

{
  sk_h_003541a0();
  sk_r4_001c4bec();
  return;
}



/* FUN_001c49e0 @ 0x001c49e0   (est. sk_r4_001c49e0)
 * Ghidra: void FUN_001c49e0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c49e0(void)

{
  sk_h_003541a0();
  sk_r4_001c4bec();
  return;
}



/* FUN_001c49f8 @ 0x001c49f8   (est. sk_r4_001c49f8)
 * Ghidra: void FUN_001c49f8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c49f8(void)

{
  sk_r4_001c4f30();
  return;
}



/* FUN_001c49fc @ 0x001c49fc   (est. sk_r4_001c49fc)
 * Ghidra: void FUN_001c49fc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c49fc(void)

{
  sk_r4_001c4f30();
  return;
}



/* FUN_001c4a28 @ 0x001c4a28   (est. sk_r4_001c4a28)
 * Ghidra: void FUN_001c4a28(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4a28(void)

{
  sk_r4_001c5414();
  return;
}



/* FUN_001c4a2c @ 0x001c4a2c   (est. sk_r4_001c4a2c)
 * Ghidra: void FUN_001c4a2c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4a2c(void)

{
  sk_r4_001c5414();
  return;
}



/* FUN_001c4a58 @ 0x001c4a58   (est. sk_r4_001c4a58)
 * Ghidra: void FUN_001c4a58(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4a58(void)

{
  sk_h_00354184();
  sk_r4_001c4a74();
  return;
}



/* FUN_001c4a5c @ 0x001c4a5c   (est. sk_r4_001c4a5c)
 * Ghidra: void FUN_001c4a5c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4a5c(void)

{
  sk_h_00354184();
  sk_r4_001c4a74();
  return;
}



/* FUN_001c4a74 @ 0x001c4a74   (est. sk_r4_001c4a74)
 * Ghidra: void FUN_001c4a74(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4a74(void)

{
  uint64_t v1;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  sk_h_00349788();
  sk_h_00351298();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a0e0();
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034a1e0(*(uint64_t *)(xo16_01 + 0x1a0));
    (*xo10)();
    sk_h_00356a38();
    (*xo8_01)();
    sk_h_0034a100();
    v1 = (*xo8_02)();
    sk_h_0034bbc8();
    (*xo8_03)();
    sk_h_00350b6c(*(uint64_t *)(xo16 + 8));
    (*xo8_04)();
    v1 = sk_h_00353e7c(v1);
    sk_rt_hook_d(v1,arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c4bd4 @ 0x001c4bd4   (est. sk_r4_001c4bd4)
 * Ghidra: void FUN_001c4bd4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4bd4(void)

{
  sk_h_00354168();
  sk_r4_001c4bec();
  return;
}



/* FUN_001c4bec @ 0x001c4bec   (est. sk_r4_001c4bec)
 * Ghidra: void FUN_001c4bec(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4bec(void)

{
  uint64_t v1;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  sk_h_00349788();
  sk_h_00351298();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a0e0();
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034a1e0(*(uint64_t *)(xo16_01 + 0x1a0));
    (*xo10)();
    sk_h_00356a38();
    (*xo8_01)();
    sk_h_0034a100();
    v1 = (*xo8_02)();
    sk_h_0034bbc8();
    (*xo8_03)();
    sk_h_00350b6c(*(uint64_t *)(xo16 + 8));
    (*xo8_04)();
    v1 = sk_h_00353e7c(v1);
    sk_rt_hook_d(v1,arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c4d4c @ 0x001c4d4c   (est. sk_r4_001c4d4c)
 * Ghidra: void FUN_001c4d4c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4d4c(void)

{
  sk_h_0035414c();
  sk_r4_001c4d64();
  return;
}



/* FUN_001c4d64 @ 0x001c4d64   (est. sk_r4_001c4d64)
 * Ghidra: void FUN_001c4d64(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4d64(void)

{
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  uint64_t v1;
  sk_r4_u128_t av2;
  uint64_t arg;
  uint64_t stk_10;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  v1 = *(uint64_t *)(xo16 + 0x198);
  sk_h_00349788();
  sk_h_0035056c();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_01 + 0x40) == xo8_00) {
    sk_h_00352de8();
    sk_h_0034bc38(xo16_00);
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034a1e0(*(uint64_t *)(xo16_02 + 0x1a0));
    (*xo10)();
    (*stk_10)(v1);
    av2 = sk_h_0034a540();
    (*xo8_01)(av2.lo,av2.hi,v1);
    sk_h_00351a5c();
    sk_h_0034bbc8();
    (*xo8_02)();
    sk_h_00350b6c(*(uint64_t *)(xo16_00 + 8));
    (*xo8_03)();
    sk_h_00350af4();
    av2 = sk_h_00353e7c();
    sk_rt_hook_d(av2.lo,av2.hi,arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c4ed8 @ 0x001c4ed8   (est. sk_r4_001c4ed8)
 * Ghidra: void FUN_001c4ed8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4ed8(void)

{
  sk_r4_001c5c80();
  return;
}



/* FUN_001c4f00 @ 0x001c4f00   (est. sk_r4_001c4f00)
 * Ghidra: void FUN_001c4f00(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4f00(void)

{
  sk_r4_001c4f30();
  return;
}



/* FUN_001c4f04 @ 0x001c4f04   (est. sk_r4_001c4f04)
 * Ghidra: void FUN_001c4f04(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4f04(void)

{
  sk_r4_001c4f30();
  return;
}



/* FUN_001c4f30 @ 0x001c4f30   (est. sk_r4_001c4f30)
 * Ghidra: void FUN_001c4f30(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c4f30(void)

{
  uint64_t v1;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  sk_h_00349788();
  sk_h_00351298();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a0e0();
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034a1e0(*(uint64_t *)(xo16_01 + 0x1a0));
    (*xo10)();
    sk_h_00356a38();
    (*xo8_01)();
    sk_h_0034a100();
    v1 = (*xo8_02)();
    sk_h_0034bbc8();
    (*xo8_03)();
    sk_h_00350b6c(*(uint64_t *)(xo16 + 8));
    (*xo8_04)();
    v1 = sk_h_00353e7c(v1);
    sk_rt_hook_d(v1,arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c5090 @ 0x001c5090   (est. sk_r4_001c5090)
 * Ghidra: void FUN_001c5090(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5090(void)

{
  sk_r4_001c50bc();
  return;
}



/* FUN_001c50bc @ 0x001c50bc   (est. sk_r4_001c50bc)
 * Ghidra: void FUN_001c50bc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c50bc(void)

{
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  uint64_t xo8_04;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  uint64_t ax20;
  uint64_t v1;
  long ax24;
  sk_r4_u128_t av2;
  uint64_t arg;
  uint64_t stk_10;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  v1 = *(uint64_t *)(xo16 + 0x198);
  sk_h_00349788();
  sk_h_0035056c();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_01 + 0x40) != xo8_00) {
    sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
    sk_h_001afe4c();
  }
  sk_h_00352de8();
  sk_h_0034bc38(xo16_00);
  (*xo9)();
  sk_h_00352e00();
  sk_h_0034a1e0(*(uint64_t *)(xo16_02 + 0x1a0));
  (*xo10)();
  (*stk_10)(v1);
  av2 = sk_h_0034a540();
  (*xo8_01)(av2.lo,av2.hi,v1);
  sk_h_00351a5c();
  sk_h_0034bbc8();
  (*xo8_02)();
  sk_h_00350b6c(*(uint64_t *)(xo16_00 + 8));
  (*xo8_03)();
  if (ax24 != 0) {
    v1 = xo8_04;
    ax20 = xo8_04;
  }
  av2 = sk_h_00353e7c(ax20,v1);
  sk_rt_hook_d(av2.lo,av2.hi,arg);
  return;
}



/* FUN_001c5238 @ 0x001c5238   (est. sk_r4_001c5238)
 * Ghidra: void FUN_001c5238(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5238(void)

{
  sk_r4_001c58b8();
  return;
}



/* FUN_001c5264 @ 0x001c5264   (est. sk_r4_001c5264)
 * Ghidra: void FUN_001c5264(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5264(void)

{
  sk_r4_001c572c();
  return;
}



/* FUN_001c5268 @ 0x001c5268   (est. sk_r4_001c5268)
 * Ghidra: void FUN_001c5268(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5268(void)

{
  sk_r4_001c572c();
  return;
}



/* FUN_001c5294 @ 0x001c5294   (est. sk_r4_001c5294)
 * Ghidra: void FUN_001c5294(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5294(void)

{
  sk_r4_001c58b8();
  return;
}



/* FUN_001c5298 @ 0x001c5298   (est. sk_r4_001c5298)
 * Ghidra: void FUN_001c5298(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5298(void)

{
  sk_r4_001c58b8();
  return;
}



/* FUN_001c52c4 @ 0x001c52c4   (est. sk_r4_001c52c4)
 * Ghidra: void FUN_001c52c4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c52c4(void)

{
  sk_r4_001c5414();
  return;
}



/* FUN_001c52c8 @ 0x001c52c8   (est. sk_r4_001c52c8)
 * Ghidra: void FUN_001c52c8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c52c8(void)

{
  sk_r4_001c5414();
  return;
}



/* FUN_001c52f4 @ 0x001c52f4   (est. sk_r4_001c52f4)
 * Ghidra: void FUN_001c52f4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c52f4(void)

{
  sk_r4_001c55a0();
  return;
}



/* FUN_001c52f8 @ 0x001c52f8   (est. sk_r4_001c52f8)
 * Ghidra: void FUN_001c52f8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c52f8(void)

{
  sk_r4_001c55a0();
  return;
}



/* FUN_001c5324 @ 0x001c5324   (est. sk_r4_001c5324)
 * Ghidra: void FUN_001c5324(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5324(void)

{
  sk_r4_001c572c();
  return;
}



/* FUN_001c5328 @ 0x001c5328   (est. sk_r4_001c5328)
 * Ghidra: void FUN_001c5328(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5328(void)

{
  sk_r4_001c572c();
  return;
}



/* FUN_001c5354 @ 0x001c5354   (est. sk_r4_001c5354)
 * Ghidra: void FUN_001c5354(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5354(void)

{
  sk_r4_001c58b8();
  return;
}



/* FUN_001c5358 @ 0x001c5358   (est. sk_r4_001c5358)
 * Ghidra: void FUN_001c5358(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5358(void)

{
  sk_r4_001c58b8();
  return;
}



/* FUN_001c5384 @ 0x001c5384   (est. sk_r4_001c5384)
 * Ghidra: void FUN_001c5384(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5384(void)

{
  sk_r4_001c5a64();
  return;
}



/* FUN_001c5388 @ 0x001c5388   (est. sk_r4_001c5388)
 * Ghidra: void FUN_001c5388(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5388(void)

{
  sk_r4_001c5a64();
  return;
}



/* FUN_001c53b4 @ 0x001c53b4   (est. sk_r4_001c53b4)
 * Ghidra: void FUN_001c53b4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c53b4(void)

{
  sk_r4_001c58b8();
  return;
}



/* FUN_001c53b8 @ 0x001c53b8   (est. sk_r4_001c53b8)
 * Ghidra: void FUN_001c53b8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c53b8(void)

{
  sk_r4_001c58b8();
  return;
}



/* FUN_001c53e4 @ 0x001c53e4   (est. sk_r4_001c53e4)
 * Ghidra: void FUN_001c53e4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c53e4(void)

{
  sk_r4_001c5414();
  return;
}



/* FUN_001c53e8 @ 0x001c53e8   (est. sk_r4_001c53e8)
 * Ghidra: void FUN_001c53e8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c53e8(void)

{
  sk_r4_001c5414();
  return;
}



/* FUN_001c5414 @ 0x001c5414   (est. sk_r4_001c5414)
 * Ghidra: void FUN_001c5414(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5414(void)

{
  uint64_t v1;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  sk_h_00349788();
  sk_h_00351298();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a0e0();
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034a1e0(*(uint64_t *)(xo16_01 + 0x1a0));
    (*xo10)();
    sk_h_00356a38();
    (*xo8_01)();
    sk_h_0034a100();
    v1 = (*xo8_02)();
    sk_h_0034bbc8();
    (*xo8_03)();
    sk_h_00350b6c(*(uint64_t *)(xo16 + 8));
    (*xo8_04)();
    v1 = sk_h_00353e7c(v1);
    sk_rt_hook_d(v1,arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c5574 @ 0x001c5574   (est. sk_r4_001c5574)
 * Ghidra: void FUN_001c5574(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5574(void)

{
  sk_r4_001c55a0();
  return;
}



/* FUN_001c55a0 @ 0x001c55a0   (est. sk_r4_001c55a0)
 * Ghidra: void FUN_001c55a0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c55a0(void)

{
  uint v1;
  uint64_t v2;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  sk_h_00349788();
  sk_h_00351298();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a0e0();
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034a1e0(*(uint64_t *)(xo16_01 + 0x1a0));
    (*xo10)();
    sk_h_00356a38();
    (*xo8_01)();
    sk_h_0034a100();
    v1 = (*xo8_02)();
    sk_h_0034bbc8();
    (*xo8_03)();
    sk_h_00350b6c(*(uint64_t *)(xo16 + 8));
    (*xo8_04)();
    v2 = sk_h_00353e7c(v1 & 0xffffff);
    sk_rt_hook_d(v2,arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c5700 @ 0x001c5700   (est. sk_r4_001c5700)
 * Ghidra: void FUN_001c5700(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5700(void)

{
  sk_r4_001c572c();
  return;
}



/* FUN_001c572c @ 0x001c572c   (est. sk_r4_001c572c)
 * Ghidra: void FUN_001c572c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c572c(void)

{
  uint64_t v1;
  uint64_t v2;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  sk_h_00349788();
  sk_h_00351298();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_00 + 0x40) == xo8_00) {
    sk_h_0034a0e0();
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034a1e0(*(uint64_t *)(xo16_01 + 0x1a0));
    (*xo10)();
    sk_h_00356a38();
    (*xo8_01)();
    sk_h_0034a100();
    v1 = (*xo8_02)();
    sk_h_0034bbc8();
    (*xo8_03)();
    sk_h_00350b6c(*(uint64_t *)(xo16 + 8));
    (*xo8_04)();
    v2 = sk_h_00353e7c(v1 & 0xffffffffff);
    sk_rt_hook_d(v2,arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c588c @ 0x001c588c   (est. sk_r4_001c588c)
 * Ghidra: void FUN_001c588c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c588c(void)

{
  sk_r4_001c58b8();
  return;
}



/* FUN_001c58b8 @ 0x001c58b8   (est. sk_r4_001c58b8)
 * Ghidra: void FUN_001c58b8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c58b8(void)

{
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  uint64_t xo8_04;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  uint64_t v1;
  long ax24;
  sk_r4_u128_t av2;
  uint64_t arg;
  uint64_t stk_10;
  
  sk_rt_hook_c();
  sk_h_0034945c();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034a570();
  v1 = *(uint64_t *)(xo16 + 0x198);
  sk_h_00349788();
  sk_h_0035056c();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034a558();
  if (*(long *)(xo16_01 + 0x40) == xo8_00) {
    sk_h_00352de8();
    sk_h_0034bc38(xo16_00);
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034a1e0(*(uint64_t *)(xo16_02 + 0x1a0));
    (*xo10)();
    (*stk_10)(v1);
    av2 = sk_h_0034a540();
    av2 = (*xo8_01)(av2.lo,av2.hi,v1);
    v1 = av2.lo;
    sk_h_0034bbc8();
    (*xo8_02)();
    sk_h_00350b6c(*(uint64_t *)(xo16_00 + 8));
    (*xo8_03)();
    if (ax24 != 0) {
      v1 = xo8_04;
    }
    av2 = sk_h_00353e7c(v1,av2.hi);
    sk_rt_hook_d(av2.lo,av2.hi,arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c5a38 @ 0x001c5a38   (est. sk_r4_001c5a38)
 * Ghidra: void FUN_001c5a38(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5a38(void)

{
  sk_r4_001c5a64();
  return;
}



/* FUN_001c5a64 @ 0x001c5a64   (est. sk_r4_001c5a64)
 * Ghidra: void FUN_001c5a64(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5a64(void)

{
  long xo1;
  code *ix3;
  uint64_t ix4;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo8_05;
  code *xo9;
  code *xo10;
  uint64_t xo13;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  long xo16_03;
  uint64_t v1;
  long ax21;
  uint64_t v2;
  sk_r4_u128_t av3;
  
  sk_rt_hook_c();
  sk_rt_hook_l();
  v1 = *(uint64_t *)(xo16 + 400);
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034ef48();
  sk_h_003549d8();
  v2 = *(uint64_t *)(xo16_01 + 0x198);
  sk_h_00349788();
  sk_h_003508d8();
  sk_object_lock();
  sk_h_000a6f88();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034c8f8();
  if (*(long *)(*(long *)(xo1 + -8) + 0x40) == xo8_00) {
    sk_h_00359524();
    sk_h_00351d0c();
    av3 = sk_h_00356aa0();
    (*xo9)(av3.lo,av3.hi,xo13);
    sk_h_0035a20c();
    sk_h_00350b60(*(uint64_t *)(xo16_03 + 0x1a0));
    (*xo10)();
    (*ix3)(v2);
    sk_h_003505d0();
    sk_h_00350c20();
    (*xo8_01)();
    if (ax21 == 0) {
      sk_h_003509d4(*(uint64_t *)(xo16_00 + 8));
      (*xo8_04)();
      sk_h_00356aa0(*(uint64_t *)(xo16_02 + 8));
      (*xo8_05)();
    }
    else {
      sk_h_003509d4(*(uint64_t *)(xo16_00 + 8));
      (*xo8_02)();
      sk_h_00356aa0(*(uint64_t *)(xo16_02 + 8));
      (*xo8_03)();
      v1 = ix4;
    }
    av3 = sk_h_00351360();
    sk_h_00352df4(av3.lo,av3.hi,v1);
    sk_rt_hook_d();
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c5c58 @ 0x001c5c58   (est. sk_r4_001c5c58)
 * Ghidra: void FUN_001c5c58(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5c58(void)

{
  sk_r4_001c5c80();
  return;
}



/* FUN_001c5c80 @ 0x001c5c80   (est. sk_r4_001c5c80)
 * Ghidra: void FUN_001c5c80(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5c80(void)

{
  code *pc1;
  code *ix6;
  uint64_t xo8;
  long xo8_00;
  long xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo9;
  code *xo10;
  long xo12;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  long xo16_03;
  uint64_t v2;
  
  sk_rt_hook_c();
  sk_rt_hook_l();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_003549d8();
  v2 = *(uint64_t *)(xo16_00 + 0x198);
  sk_h_00349788();
  sk_h_00351298();
  sk_object_lock();
  sk_h_00348ce8();
  sk_rt_hook_g(*(uint64_t *)(xo8_00 + 0x40));
  (*datum_00658c00)();
  sk_h_0034bab8();
  sk_h_00352cd4();
  if (*(long *)(xo16_02 + 0x40) == xo8_01) {
    sk_h_00352de8();
    sk_h_00352a40();
    sk_h_00358e00();
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034c58c(*(uint64_t *)(xo16_03 + 0x1a0));
    sk_h_003543f8();
    (*xo10)();
    pc1 = (code *)(*ix6)(v2);
    (*pc1)(xo8);
    sk_h_003508cc(*(uint64_t *)(xo16 + 8));
    (*xo8_02)();
    sk_h_0035084c(*(uint64_t *)(xo16_01 + 8));
    (*xo8_03)();
    sk_h_00352df4();
    sk_rt_hook_d(*(uint64_t *)(&stack0x00000028 + -xo12));
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c5fdc @ 0x001c5fdc   (est. sk_r4_001c5fdc)
 * Ghidra: void FUN_001c5fdc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c5fdc(void)

{
  sk_r4_001c6120();
  return;
}



/* FUN_001c6004 @ 0x001c6004   (est. sk_r4_001c6004)
 * Ghidra: void FUN_001c6004(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6004(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  code *xo10;
  long xo16;
  long xo16_00;
  
  v1 = sk_h_00358fb4();
  sk_h_0035860c();
  sk_h_003536d0();
  sk_h_003499c8();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_0034aee4();
  sk_h_003536d0();
  sk_h_00350b60(*(uint64_t *)(xo16 + 0x1a0));
  (*xo10)();
  sk_h_003536d0();
  sk_h_00343250(*(uint64_t *)(xo16_00 + 0x198));
  sk_h_00351250();
  sk_h_0034d9f8();
  (*xo9)();
  sk_h_0034c9f8();
  (*xo8)();
  sk_h_00355f04();
  sk_h_00358fc8(v1);
  return;
}



/* FUN_001c60f4 @ 0x001c60f4   (est. sk_r4_001c60f4)
 * Ghidra: void FUN_001c60f4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c60f4(void)

{
  sk_r4_001c6120();
  return;
}



/* FUN_001c60f8 @ 0x001c60f8   (est. sk_r4_001c60f8)
 * Ghidra: void FUN_001c60f8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c60f8(void)

{
  sk_r4_001c6120();
  return;
}



/* FUN_001c6120 @ 0x001c6120   (est. sk_r4_001c6120)
 * Ghidra: void FUN_001c6120(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6120(void)

{
  code *ix3;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  code *xo9_00;
  code *xo10;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  long xo16_03;
  uint64_t v1;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_0034a674();
  sk_h_003499b4();
  sk_h_00351408();
  (*datum_00658c00)();
  sk_h_0034beb4();
  sk_h_003549d8();
  v1 = *(uint64_t *)(xo16_00 + 0x198);
  sk_h_00349788();
  sk_h_00351298();
  sk_object_lock();
  sk_h_00348cd0();
  sk_rt_hook_g(*(uint64_t *)(xo8 + 0x40));
  (*datum_00658c00)();
  sk_h_0034bab8();
  sk_h_00352cd4();
  if (*(long *)(xo16_02 + 0x40) == xo8_00) {
    sk_h_0034c1d0();
    sk_h_00358de8();
    (*xo9)();
    sk_h_00352e00();
    sk_h_0034c58c(*(uint64_t *)(xo16_03 + 0x1a0));
    sk_h_00353c6c();
    (*xo10)();
    (*ix3)(v1);
    sk_h_003548e8();
    sk_h_0035116c();
    (*xo9_00)();
    sk_h_0035060c(*(uint64_t *)(xo16 + 8));
    (*xo8_01)();
    sk_h_00350a04(*(uint64_t *)(xo16_01 + 8));
    (*xo8_02)();
    sk_h_00352df4();
    sk_rt_hook_d(arg);
    return;
  }
  sk_h_00347e28();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001c6310 @ 0x001c6310   (est. sk_r4_001c6310)
 * Ghidra: void FUN_001c6310(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6310(void)

{
  uint64_t v1;
  long xo8;
  long xo9;
  long xo16;
  long ax20;
  
  v1 = sk_rt_hook_l();
  sk_h_0034ece8(v1,*(uint64_t *)(xo8 + 400));
  (**(code **)(xo16 + 8))(ax20 + xo9);
  return;
}



/* FUN_001c637c @ 0x001c637c   (est. sk_r4_001c637c)
 * Ghidra: void FUN_001c637c(code *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c637c(code *p1)

{
  (*p1)();
  sk_h_0036b6ac();
  return;
}



/* FUN_001c6380 @ 0x001c6380   (est. sk_r4_001c6380)
 * Ghidra: void FUN_001c6380(code *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6380(code *p1)

{
  (*p1)();
  sk_h_0036b6ac();
  return;
}



/* FUN_001c63b8 @ 0x001c63b8   (est. sk_r4_001c63b8)
 * Ghidra: uint FUN_001c63b8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


uint sk_r4_001c63b8(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  uint unaff_w20;
  long ax21;
  uint8_t auStack_68 [40];
  
  sk_h_00354bd4();
  sk_h_0034b440();
  sk_h_000a649c();
  sk_h_0034dd4c();
  (*xo9)();
  if (ax21 == 0) {
    sk_h_0034b440(auStack_68);
    v1 = sk_h_00319aec();
    sk_h_0034ec58(v1);
    (*xo8)();
    sk_h_00357b10();
    sk_swift_release();
  }
  else {
    sk_swift_release();
  }
  return unaff_w20 & 1;
}



/* FUN_001c6454 @ 0x001c6454   (est. sk_r4_001c6454)
 * Ghidra: void FUN_001c6454(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6454(uint64_t p1,uint64_t p2)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  uint8_t auStack_68 [40];
  
  sk_h_0034b440();
  sk_h_000a649c();
  sk_h_00351660();
  sk_h_00350470();
  (*xo9)();
  sk_h_0034f96c();
  sk_h_000836a4();
  sk_h_0035122c();
  v1 = sk_h_00319b1c();
  sk_h_003513b4(v1,p2);
  (*xo8)();
  sk_h_00354624(auStack_68);
  return;
}



/* FUN_001c64e0 @ 0x001c64e0   (est. sk_r4_001c64e0)
 * Ghidra: void FUN_001c64e0(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c64e0(uint64_t p1)

{
  uint8_t *ax20;
  
  sk_r4_001c6454(p1,*ax20);
  return;
}



/* FUN_001c64e4 @ 0x001c64e4   (est. sk_r4_001c64e4)
 * Ghidra: void FUN_001c64e4(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c64e4(uint64_t p1)

{
  uint8_t *ax20;
  
  sk_r4_001c6454(p1,*ax20);
  return;
}



/* FUN_001c64fc @ 0x001c64fc   (est. sk_r4_001c64fc)
 * Ghidra: void FUN_001c64fc(byte *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c64fc(byte *p1)

{
  byte bVar1;
  long ax21;
  
  bVar1 = sk_r4_001c63b8();
  if (ax21 == 0) {
    *p1 = bVar1 & 1;
  }
  return;
}



/* FUN_001c652c @ 0x001c652c   (est. sk_r4_001c652c)
 * Ghidra: void FUN_001c652c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c652c(void)

{
  uint64_t v1;
  uint64_t ix3;
  code *xo8;
  code *xo9;
  code *xo9_00;
  uint64_t ax30;
  uint64_t arg;
  
  sk_h_003564e8();
  sk_h_00355e74();
  sk_h_00349658();
  sk_h_0034ec78();
  (*xo9)();
  sk_h_0007b384(ix3);
  sk_h_00350518(&stack0x0000003f);
  (*xo9_00)();
  v1 = arg;
  sk_h_00354654();
  sk_h_000836a4();
  sk_h_00319b1c(v1);
  sk_h_00351318();
  sk_h_00353f88();
  sk_h_003505c4();
  (*xo8)();
  sk_h_00354624(&stack0x00000008);
  sk_h_00356454(ax30);
  return;
}



/* FUN_001c65d0 @ 0x001c65d0   (est. sk_r4_001c65d0)
 * Ghidra: void FUN_001c65d0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001c67ec) */
/* WARNING: Removing unreachable block (ram,0x001c6b64) */
/* WARNING: Removing unreachable block (ram,0x001c6800) */

void sk_r4_001c65d0(void)

{
  sk_r4_u128_t av1;
  uint64_t **v2;
  uint8_t zf;
  byte bVar3;
  uint64_t v4;
  uint64_t v5;
  uint64_t **v6;
  char *pc7;
  uint64_t *xo1;
  uint64_t v8;
  uint64_t ix3;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  long xo8_04;
  uint64_t **xo8_05;
  long xo8_06;
  long xo8_07;
  long xo8_08;
  long xo8_09;
  long xo8_10;
  long xo8_11;
  code *xo9;
  code *xo9_00;
  long xo16;
  uint64_t **ax20;
  code *pc9;
  uint64_t **v10;
  long ax21;
  uint64_t **v11;
  uint64_t **v12;
  uint64_t **ax26;
  sk_r4_u128_t av13;
  uint64_t **stk_28;
  uint64_t **arg;
  uint64_t uStack_8;
  
  sk_rt_hook_c();
  sk_rt_hook_k();
  sk_rt_dispatch();
  sk_h_00348e60();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_00349494();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_00348a34();
  (*datum_00658c00)();
  sk_h_0034c2c8();
  sk_h_00350af4();
  sk_h_0034e7a0();
  sk_h_0009e234(&stk_28);
  (*xo9)();
  if (ax21 != 0) goto LAB_001c6ad8;
  sk_h_00356858();
  sk_h_0034f1a8();
  v4 = sk_h_00319aec();
  sk_h_0009e234(v4);
  bVar3 = (*xo8_01)();
  sk_swift_release(&stk_28);
  stk_28 = (uint64_t **)(CONCAT71(stk_28._1_7_,bVar3) & 0xffffffffffffff01);
  sk_h_0031bc70(ix3);
  sk_h_0035101c();
  sk_h_003500d4();
  (*xo9_00)();
  sk_h_0034c4bc();
  if (!(bool)zf) {
    pc9 = *(code **)(xo16 + 0x20);
    sk_h_0034d868();
    (*pc9)();
    sk_h_0034db48();
    (*pc9)();
    sk_h_003513b4(xo8);
    (*pc9)();
    goto LAB_001c6ad8;
  }
  sk_h_00353154();
  sk_h_003511a8();
  (*xo8_02)();
  sk_h_00348730();
  v12 = (uint64_t ***)ax20[3];
  v11 = (uint64_t ***)ax20[4];
  sk_h_0034995c();
  v4 = (*xo8_03)();
  v5 = sk_enum_err(0x2d);
  sk_h_0034d708();
  sk_h_00357868();
  sk_h_0034b824(v5 & 0xffffffffffff);
  if ((xo8_04 == 0) &&
     (((v5 & ((uint64_t)ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free();
    arg = (uint64_t ***)0x0;
    v10 = ax20;
    stk_28 = v12;
  }
  else {
    if (((uint64_t)ax20 >> 0x3d & 1) == 0) {
      sk_h_00357380();
      v11 = xo8_05;
      if (!(bool)zf) {
        v11 = (uint64_t ***)0x0;
      }
    }
    else {
      v11 = (uint64_t ***)((uint64_t)v12 & 0xffffffffffff);
    }
    sk_h_003510ac();
    sk_h_0035370c();
    sk_h_002a4c98();
    sk_masked_free();
    v10 = &stk_28;
  }
  v2 = stk_28;
  sk_h_00354774();
  sk_h_00208418();
  sk_h_00356b50();
  sk_h_0034d6c8((uint64_t)v2 & 0xffffffffffff);
  if ((xo8_06 == 0) &&
     ((((uint64_t)v2 & ((uint64_t)arg ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)
     ) {
    sk_masked_free(arg);
    stk_28 = v11;
    v12 = ax26;
  }
  else {
    v12 = arg;
    if (((uint64_t)arg >> 0x3d & 1) == 0) {
      sk_h_003536ec();
    }
    else if (((uint64_t)ax26 >> 0x3d & 1) != 0) {
      sk_h_0035100c();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034ecf8();
        sk_masked_free();
        sk_masked_free(ax26);
        sk_h_0035368c();
        goto LAB_001c6884;
      }
    }
    sk_h_0034e8d4();
    sk_h_002a4c98();
    sk_masked_free(ax26);
    v11 = (uint64_t ***)stk_28;
    ax26 = arg;
  }
LAB_001c6884:
  v6 = (uint64_t ***)sk_h_003505b0();
  sk_h_003560b4();
  sk_h_0034d0e0();
  if ((xo8_07 == 0) &&
     ((((uint64_t)v11 & ((uint64_t)ax26 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax26);
    stk_28 = v6;
  }
  else {
    if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      zf = ((uint64_t)arg & 0x2000000000000000) == 0;
    }
    else if (((uint64_t)arg >> 0x3d & 1) != 0) {
      sk_h_00350b78();
      sk_h_0035345c();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ax26);
        sk_masked_free(arg);
        stk_28 = v10;
        arg = v11;
        goto LAB_001c68f0;
      }
    }
    v10 = &stk_28;
    sk_h_00350b6c();
    sk_h_00352cc8();
    sk_h_002a4c98();
    sk_masked_free(arg);
    arg = v12;
  }
LAB_001c68f0:
  v2 = stk_28;
  sk_h_001a89a8(&datum_004e7f18,4,1);
  sk_h_00356b50();
  sk_h_0034d6c8((uint64_t)v2 & 0xffffffffffff);
  if ((xo8_08 == 0) &&
     ((((uint64_t)v2 & ((uint64_t)arg ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)
     ) {
    sk_masked_free(arg);
    stk_28 = v11;
  }
  else {
    if (((uint64_t)arg >> 0x3d & 1) == 0) {
      zf = ((uint64_t)ax26 & 0x2000000000000000) == 0;
    }
    else if (((uint64_t)ax26 >> 0x3d & 1) != 0) {
      sk_h_00350b6c();
      sk_h_00351f70();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00355cc8();
        sk_masked_free(arg);
        sk_masked_free(ax26);
        stk_28 = v10;
        ax26 = (uint64_t ***)v2;
        goto LAB_001c6968;
      }
    }
    sk_h_0034e8d4();
    sk_h_002a4c98();
    sk_masked_free(ax26);
    ax26 = arg;
  }
LAB_001c6968:
  v12 = (uint64_t ***)stk_28;
  av1.hi = stk_28;
  av1.lo = v10;
  av13 = sk_h_0035059c();
  v5 = av13.hi;
  v11 = av13.lo;
  sk_h_0034d0e0((uint64_t)v12 & 0xffffffffffff);
  if ((xo8_09 == 0) &&
     ((((uint64_t)v12 & ((uint64_t)ax26 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax26);
  }
  else {
    if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      sk_h_0034c6e4((uint64_t)v11 & 0xffffffffffff);
    }
    else if ((v5 >> 0x3d & 1) != 0) {
      sk_h_00350b78();
      sk_h_00351de4();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ax26);
        sk_masked_free(v5);
        av13 = av1;
        goto LAB_001c69d4;
      }
    }
    v10 = &stk_28;
    av13 = sk_h_0035060c();
    sk_h_002a4c98(av13.lo,av13.hi,0);
    sk_masked_free(v5);
    av13.hi = ax26;
    av13.lo = stk_28;
  }
LAB_001c69d4:
  v6 = av13.hi;
  stk_28 = av13.lo;
  if ((bVar3 & 1) == 0) {
    pc7 = (const char *)0x005ce9da /* false */;
    v8 = 5;
  }
  else {
    pc7 = &LAB_005ce9e0;
    v8 = 4;
  }
  sk_h_001a89a8(pc7,v8,1);
  sk_h_00357b3c();
  v5 = sk_h_0034bf64((uint64_t)stk_28 & 0xffffffffffff);
  if ((xo8_10 == 0) && (((v5 & ((uint64_t)v6 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)
     ) {
    sk_masked_free(v6);
    stk_28 = ax26;
  }
  else {
    if (((uint64_t)v6 >> 0x3d & 1) == 0) {
      sk_h_00351500((uint64_t)ax26 & 0xffffffffffff);
    }
    else if (((uint64_t)v11 >> 0x3d & 1) != 0) {
      sk_h_00350b9c();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034eb54();
        sk_masked_free();
        sk_masked_free(v11);
        v11 = v12;
        stk_28 = v10;
        goto LAB_001c6a68;
      }
    }
    v10 = &stk_28;
    av13 = sk_h_000a6e14();
    sk_h_002a4c98(av13.lo,av13.hi,0);
    sk_masked_free(v11);
    v11 = v6;
  }
LAB_001c6a68:
  v2 = stk_28;
  sk_h_003497ec();
  sk_h_001a89a8();
  sk_h_00354a00();
  sk_h_0034de14((uint64_t)v2 & 0xffffffffffff);
  if ((xo8_11 == 0) &&
     ((((uint64_t)v2 & ((uint64_t)v11 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v11);
  }
  else {
    if (((uint64_t)v11 >> 0x3d & 1) == 0) {
      sk_h_0034c3a0();
    }
    else if (((uint64_t)v6 >> 0x3d & 1) != 0) {
      sk_h_0034c290();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0035351c();
        sk_masked_free(v11);
        sk_masked_free(v6);
        v12 = v10;
        goto LAB_001c6ac8;
      }
    }
    sk_h_0034ef38();
    sk_h_002a4c98();
    sk_masked_free(v6);
    v12 = (uint64_t ***)stk_28;
  }
LAB_001c6ac8:
  *xo1 = v4;
  xo1[1] = v12;
  sk_h_0034f948();
  sk_h_0036986c();
LAB_001c6ad8:
  sk_swift_release(ax20);
  sk_h_00359b64();
  sk_rt_hook_d(uStack_8);
  return;
}



/* FUN_001c6c48 @ 0x001c6c48   (est. sk_r4_001c6c48)
 * Ghidra: void FUN_001c6c48(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6c48(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  long ax21;
  uint8_t auStack_68 [40];
  
  sk_h_00354bd4();
  sk_h_0034b440();
  sk_h_000a649c();
  sk_h_0034dd4c();
  (*xo9)();
  if (ax21 == 0) {
    sk_h_0034b440(auStack_68);
    v1 = sk_h_00319b4c();
    sk_h_0034ec58(v1);
    (*xo8)();
    sk_h_00354f1c();
    sk_h_00357c2c();
    sk_swift_release();
  }
  else {
    sk_swift_release();
  }
  sk_h_00351450();
  return;
}



/* FUN_001c6ce8 @ 0x001c6ce8   (est. sk_r4_001c6ce8)
 * Ghidra: void FUN_001c6ce8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6ce8(void)

{
  long r1;
  code *xo8;
  code *xo9;
  uint8_t auStack_68 [40];
  
  r1 = sk_h_0035128c();
  sk_h_0034e7a0(r1,*(uint64_t *)(r1 + 0x18));
  sk_h_000dbd0c(auStack_68);
  (*xo9)();
  sk_h_0035543c();
  sk_h_000836a4();
  sk_h_003515a8();
  sk_h_00319b7c();
  sk_h_0034c8b8();
  sk_h_00351aec();
  (*xo8)();
  sk_h_00354624(auStack_68);
  return;
}



/* FUN_001c6d74 @ 0x001c6d74   (est. sk_r4_001c6d74)
 * Ghidra: void FUN_001c6d74(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6d74(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c6ce8(p1,*ax20,ax20[1]);
  return;
}



/* FUN_001c6d78 @ 0x001c6d78   (est. sk_r4_001c6d78)
 * Ghidra: void FUN_001c6d78(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6d78(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c6ce8(p1,*ax20,ax20[1]);
  return;
}



/* FUN_001c6d90 @ 0x001c6d90   (est. sk_r4_001c6d90)
 * Ghidra: void FUN_001c6d90(undefined1 (*param_1) [16])
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6d90(uint8_t (*p1) [16])

{
  long ax21;
  sk_r4_u128_t av1;
  
  av1 = sk_r4_001c6c48();
  if (ax21 == 0) {
    *p1 = av1;
  }
  return;
}



/* FUN_001c6dbc @ 0x001c6dbc   (est. sk_r4_001c6dbc)
 * Ghidra: void FUN_001c6dbc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6dbc(void)

{
  uint64_t v1;
  uint64_t ix3;
  code *xo8;
  code *xo9;
  code *xo9_00;
  uint64_t uStack_80;
  uint8_t auStack_78 [24];
  uint64_t stk_60;
  uint64_t uStack_58;
  
  sk_h_00355e74();
  sk_h_00349658();
  sk_h_00350738(auStack_78);
  (*xo9)();
  sk_h_0007b384(ix3);
  sk_h_00351660();
  sk_h_00350518();
  (*xo9_00)();
  sk_h_000836a4(auStack_78,stk_60);
  v1 = sk_h_00319b7c(uStack_58);
  sk_h_00350af4(v1);
  sk_h_00350bfc();
  (*xo8)();
  sk_masked_free(uStack_80);
  sk_h_00354624(auStack_78);
  return;
}



/* FUN_001c6e84 @ 0x001c6e84   (est. sk_r4_001c6e84)
 * Ghidra: void FUN_001c6e84(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c6e84(void)

{
  uint8_t zf;
  uint64_t v1;
  code *pc2;
  uint8_t *xo1;
  uint64_t *xo1_00;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  long xo8_03;
  long xo8_04;
  uint8_t *xo8_05;
  long xo8_06;
  long xo8_07;
  uint8_t *xo8_08;
  long xo8_09;
  long xo8_10;
  long xo8_11;
  code *xo9;
  long xo16;
  long xo16_00;
  uint8_t *ax20;
  uint8_t *v3;
  long ax21;
  uint8_t *v4;
  uint8_t *ax23;
  uint8_t *v5;
  uint8_t *v6;
  uint8_t *v7;
  sk_r4_u128_t av8;
  uint8_t *v9;
  uint8_t *v10;
  uint8_t *v11;
  uint64_t uStack_18;
  uint8_t *puStack_8;
  
  sk_rt_hook_c();
  sk_rt_hook_k();
  sk_rt_dispatch();
  sk_h_00348cd0();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_rt_hook_e();
  sk_rt_hook_i();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_00348a34();
  (*datum_00658c00)();
  sk_h_0034c2c8();
  sk_h_00350af4();
  sk_h_0034d1e0();
  sk_h_00352a70();
  sk_h_00350b78();
  (*xo9)();
  if (ax21 != 0) goto LAB_001c73c0;
  sk_h_000dbc54(&stack0xffffffffffffffd8);
  v1 = sk_h_00319b4c(puStack_8);
  sk_h_00351160(v1);
  (*xo8_01)();
  sk_h_00355d6c();
  sk_swift_release(&stack0xffffffffffffffd8);
  sk_h_00355a14();
  pc2 = (code *)sk_h_0031bc70();
  sk_alloc_pages(puStack_8);
  sk_h_00351214(&stack0xffffffffffffffd8);
  (*pc2)();
  av8 = sk_h_0035172c();
  sk_h_00350884(av8.lo,av8.hi,xo1);
  if (!(bool)zf) {
    sk_masked_free(puStack_8);
    pc2 = *(code **)(xo16_00 + 0x20);
    av8 = sk_h_0035145c();
    (*pc2)(av8.lo,av8.hi,xo1);
    av8 = sk_h_00350518();
    (*pc2)(av8.lo,av8.hi,xo1);
    sk_h_00351ba0(xo8);
    (*pc2)();
    goto LAB_001c73c0;
  }
  (**(code **)(xo16 + 8))();
  sk_h_00348730();
  v7 = *(uint8_t **)(ax20 + 0x18);
  v4 = *(uint8_t **)(ax20 + 0x20);
  sk_h_0034995c(ax20);
  v1 = (*xo8_02)();
  sk_enum_err(0x2d);
  av8 = sk_h_00351e08();
  sk_h_0034f958();
  sk_h_00356b68();
  sk_rt_hook_v();
  if ((xo8_03 == 0) &&
     ((((uint64_t)xo1 & ((uint64_t)v7 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v7);
    v5 = puStack_8;
  }
  else {
    v5 = (uint8_t *)((uint64_t)ax23 >> 0x38 & 0xf);
    if (((uint64_t)v7 >> 0x3d & 1) == 0) {
      zf = ((uint64_t)ax23 & 0x2000000000000000) == 0;
      v4 = (uint8_t *)((uint64_t)v4 & 0xffffffffffff);
      if (!(bool)zf) {
        v4 = v5;
      }
    }
    else if (((uint64_t)ax23 >> 0x3d & 1) == 0) {
      v4 = (uint8_t *)((uint64_t)v4 & 0xffffffffffff);
    }
    else {
      sk_h_0007c1c4();
      sk_h_00352e78();
      sk_rt_slot2();
      v4 = v5;
      if (!(bool)zf) {
        sk_h_0035351c();
        sk_masked_free(v7);
        sk_masked_free();
        v4 = xo1;
        ax23 = ax20;
        goto LAB_001c7124;
      }
    }
    sk_h_0034e8e8();
    sk_h_002a4c98();
    sk_masked_free();
    v5 = v4;
    v4 = av8.lo;
    ax23 = av8.hi;
  }
LAB_001c7124:
  sk_h_00208418(xo1,0);
  sk_h_00357868();
  sk_h_0034e910();
  v3 = xo1;
  if ((xo8_04 == 0) &&
     ((((uint64_t)v4 & ((uint64_t)ax23 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax23);
    v11 = xo1;
  }
  else {
    v5 = (uint8_t *)((uint64_t)xo1 >> 0x38 & 0xf);
    if (((uint64_t)ax23 >> 0x3d & 1) == 0) {
      sk_h_00357380();
      v7 = xo8_05;
      if (!(bool)zf) {
        v7 = v5;
      }
    }
    else if (((uint64_t)xo1 >> 0x3d & 1) == 0) {
      v7 = (uint8_t *)((uint64_t)v7 & 0xffffffffffff);
    }
    else {
      sk_h_0034ef28();
      sk_rt_slot2();
      v7 = v5;
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ax23);
        sk_masked_free(xo1);
        v7 = xo1;
        v11 = v4;
        goto LAB_001c7190;
      }
    }
    v3 = &stack0xffffffffffffffd8;
    sk_h_003510ac();
    sk_h_00353b40();
    sk_h_002a4c98();
    sk_masked_free(xo1);
    v5 = v7;
    v7 = v4;
    v11 = ax23;
  }
LAB_001c7190:
  sk_h_003505b0();
  sk_h_00356b68();
  sk_h_0034d6c8((uint64_t)v7 & 0xffffffffffff);
  if ((xo8_06 == 0) &&
     ((((uint64_t)v7 & ((uint64_t)v11 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v11);
    v9 = v4;
    v10 = ax23;
  }
  else {
    v5 = (uint8_t *)((uint64_t)ax23 >> 0x38 & 0xf);
    v9 = v7;
    v10 = v11;
    if (((uint64_t)v11 >> 0x3d & 1) == 0) {
      zf = ((uint64_t)ax23 & 0x2000000000000000) == 0;
      v6 = (uint8_t *)((uint64_t)v4 & 0xffffffffffff);
      if (!(bool)zf) {
        v6 = v5;
      }
    }
    else if (((uint64_t)ax23 >> 0x3d & 1) == 0) {
      v6 = (uint8_t *)((uint64_t)v4 & 0xffffffffffff);
    }
    else {
      sk_h_0035100c();
      sk_rt_slot2();
      v6 = v5;
      if (!(bool)zf) {
        sk_h_0034ecf8();
        sk_masked_free();
        sk_masked_free(ax23);
        sk_h_0035369c();
        goto LAB_001c71f8;
      }
    }
    sk_h_0034e8e8();
    sk_h_002a4c98();
    sk_masked_free(ax23);
    v4 = v7;
    v5 = v6;
    ax23 = v11;
  }
LAB_001c71f8:
  sk_h_001a89a8((const char *)0x004e7f1d /* String */,6,1);
  sk_h_00357868();
  sk_h_0034e910();
  if ((xo8_07 == 0) &&
     ((((uint64_t)v4 & ((uint64_t)ax23 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax23);
  }
  else {
    v5 = (uint8_t *)((uint64_t)v11 >> 0x38 & 0xf);
    if (((uint64_t)ax23 >> 0x3d & 1) == 0) {
      sk_h_00357380();
      v7 = xo8_08;
      if (!(bool)zf) {
        v7 = v5;
      }
    }
    else if (((uint64_t)v11 >> 0x3d & 1) == 0) {
      v7 = (uint8_t *)((uint64_t)v7 & 0xffffffffffff);
    }
    else {
      sk_h_0034ef28();
      sk_rt_slot2();
      v7 = v5;
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ax23);
        sk_masked_free(v11);
        v7 = v3;
        v11 = v4;
        goto LAB_001c726c;
      }
    }
    v3 = &stack0xffffffffffffffd8;
    sk_h_003510ac();
    sk_h_00353b40();
    sk_h_002a4c98();
    sk_masked_free(v11);
    v5 = v7;
    v7 = v9;
    v11 = v10;
  }
LAB_001c726c:
  sk_h_0035059c();
  sk_h_00356e28();
  sk_h_0034d6c8((uint64_t)v7 & 0xffffffffffff);
  if ((xo8_09 == 0) &&
     ((((uint64_t)v7 & ((uint64_t)v11 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v11);
  }
  else {
    if (((uint64_t)v11 >> 0x3d & 1) == 0) {
      sk_h_0034da28((uint64_t)v5 & 0xffffffffffff);
    }
    else if (((uint64_t)v4 >> 0x3d & 1) != 0) {
      sk_h_003510ac();
      sk_h_00351f1c();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034ecf8();
        sk_masked_free();
        sk_masked_free(v4);
        v5 = v7;
        v4 = v3;
        goto LAB_001c72d4;
      }
    }
    v3 = &stack0xffffffffffffffd8;
    sk_h_0034fd5c();
    sk_h_002a4c98();
    sk_masked_free(v4);
    v5 = v7;
    v4 = v11;
  }
LAB_001c72d4:
  sk_h_0034c094((uint64_t)v5 & 0xffffffffffff);
  if ((xo8_10 == 0) &&
     ((((uint64_t)v5 & ((uint64_t)v4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v4);
    v5 = ax20;
  }
  else {
    if (((uint64_t)v4 >> 0x3d & 1) == 0) {
      zf = ((uint64_t)puStack_8 & 0x2000000000000000) == 0;
    }
    else if (((uint64_t)puStack_8 >> 0x3d & 1) != 0) {
      sk_h_00351384();
      sk_h_00351dcc();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00350df4();
        sk_masked_free();
        sk_masked_free(puStack_8);
        puStack_8 = v3;
        v5 = v7;
        goto LAB_001c7344;
      }
    }
    v3 = &stack0xffffffffffffffd8;
    av8 = sk_h_003509b0();
    sk_h_002a4c98(av8.lo,av8.hi,0);
    sk_masked_free(puStack_8);
    puStack_8 = v4;
  }
LAB_001c7344:
  sk_h_003497ec();
  sk_h_001a89a8();
  sk_h_00354a00();
  sk_h_0034d044((uint64_t)v5 & 0xffffffffffff);
  if ((xo8_11 == 0) &&
     ((((uint64_t)v5 & ((uint64_t)puStack_8 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(puStack_8);
  }
  else {
    if (((uint64_t)puStack_8 >> 0x3d & 1) == 0) {
      sk_h_0034c3a0();
    }
    else if (((uint64_t)v7 >> 0x3d & 1) != 0) {
      sk_h_00350c38();
      sk_h_003515fc();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0035122c();
        sk_masked_free();
        sk_masked_free(v7);
        v4 = v3;
        goto LAB_001c73a8;
      }
    }
    sk_h_0034ef38();
    sk_h_002a4c98();
    sk_masked_free(v7);
    v4 = v5;
  }
LAB_001c73a8:
  *xo1_00 = v1;
  xo1_00[1] = v4;
  sk_h_0034f948();
  sk_h_0036986c();
LAB_001c73c0:
  sk_swift_release(ax20);
  sk_h_00354b5c();
  sk_rt_hook_d(uStack_18);
  return;
}



/* FUN_001c7534 @ 0x001c7534   (est. sk_r4_001c7534)
 * Ghidra: undefined1  [16] FUN_001c7534(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


sk_r4_u128_t sk_r4_001c7534(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  long ax21;
  sk_r4_u128_t av2;
  uint64_t unaff_d8;
  uint64_t ireg;
  uint8_t auStack_68 [40];
  
  sk_h_00354bd4();
  sk_h_0034b440();
  sk_h_000a649c();
  sk_h_0034dd4c();
  (*xo9)();
  if (ax21 == 0) {
    sk_h_0034b440(auStack_68);
    v1 = sk_h_00319bac();
    sk_h_0034ec58(v1);
    av2 = (*xo8)();
    ireg = av2.hi;
    unaff_d8 = av2.lo;
    sk_h_00357c2c();
    sk_swift_release();
  }
  else {
    sk_swift_release();
  }
  av2.hi = ireg;
  av2.lo = unaff_d8;
  return av2;
}



/* FUN_001c75dc @ 0x001c75dc   (est. sk_r4_001c75dc)
 * Ghidra: void FUN_001c75dc(long param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c75dc(long p1)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  uint8_t auStack_68 [40];
  
  v1 = *(uint64_t *)(p1 + 0x20);
  sk_h_000dbc54();
  sk_h_000a649c(v1);
  sk_h_00351660();
  sk_h_000e15d8();
  (*xo9)();
  sk_h_00354654();
  sk_h_000836a4();
  sk_h_003519a8();
  sk_h_00319bdc();
  sk_h_0035a684();
  sk_h_000e15d8();
  (*xo8)();
  sk_h_00354624(auStack_68);
  return;
}



/* FUN_001c766c @ 0x001c766c   (est. sk_r4_001c766c)
 * Ghidra: void FUN_001c766c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c766c(void)

{
  uint64_t *ax20;
  
  sk_r4_001c75dc(*ax20);
  return;
}



/* FUN_001c7670 @ 0x001c7670   (est. sk_r4_001c7670)
 * Ghidra: void FUN_001c7670(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c7670(void)

{
  uint64_t *ax20;
  
  sk_r4_001c75dc(*ax20);
  return;
}



/* FUN_001c7688 @ 0x001c7688   (est. sk_r4_001c7688)
 * Ghidra: void FUN_001c7688(undefined8 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c7688(uint64_t *p1)

{
  long ax21;
  uint64_t v1;
  
  v1 = sk_r4_001c7534();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c76b4 @ 0x001c76b4   (est. sk_r4_001c76b4)
 * Ghidra: void FUN_001c76b4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c76b4(void)

{
  uint64_t ix3;
  code *xo8;
  code *xo9;
  code *xo9_00;
  uint8_t auStack_78 [40];
  
  sk_h_00355e74();
  sk_h_00349658();
  sk_h_0034ec78();
  (*xo9)();
  sk_h_0007b384(ix3);
  sk_h_00355d40();
  sk_h_00350518();
  (*xo9_00)();
  sk_h_00354654();
  sk_h_000836a4();
  sk_h_003519a8();
  sk_h_00319bdc();
  sk_h_0035a684();
  sk_h_000e15d8();
  (*xo8)();
  sk_h_00354624(auStack_78);
  return;
}



/* FUN_001c7768 @ 0x001c7768   (est. sk_r4_001c7768)
 * Ghidra: void FUN_001c7768(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c7768(void)

{
  uint64_t **v1;
  uint8_t zf;
  uint64_t v2;
  uint64_t v3;
  uint64_t **v4;
  uint64_t **xo1;
  uint64_t *xo1_00;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  long xo8_04;
  uint64_t **xo8_05;
  long xo8_06;
  long xo8_07;
  long xo8_08;
  long xo8_09;
  long xo8_10;
  code *xo9;
  code *xo9_00;
  long xo16;
  long ax20;
  code *pc5;
  uint64_t **v6;
  long ax21;
  uint64_t **v7;
  uint64_t **v8;
  uint64_t **ax25;
  uint64_t **v9;
  uint64_t **v10;
  sk_r4_u128_t av11;
  uint64_t **stk_28;
  uint64_t **arg;
  uint64_t **ppuStack_8;
  
  sk_h_003549e4();
  sk_rt_hook_k();
  sk_rt_dispatch();
  sk_h_00348d7c();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_00349494();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_003489c0();
  (*datum_00658c00)();
  sk_h_0034c2c8();
  v2 = *(uint64_t *)(ax20 + 0x20);
  sk_h_000dbc54();
  sk_h_00352a70(v2);
  sk_h_00350bf0();
  (*xo9)();
  if (ax21 != 0) goto LAB_001c7be4;
  sk_h_00356858();
  sk_h_0034d1e0();
  v2 = sk_h_00319bac();
  sk_h_00350b78(v2);
  v10 = (uint64_t ***)(*xo8_01)();
  sk_swift_release(&stk_28);
  stk_28 = v10;
  sk_h_00355bc4();
  sk_h_0031bc70();
  sk_h_0035101c();
  sk_h_00351dfc();
  (*xo9_00)();
  sk_h_0034c4bc();
  if (!(bool)zf) {
    pc5 = *(code **)(xo16 + 0x20);
    av11 = sk_h_00351274();
    (*pc5)(av11.lo,av11.hi,xo1);
    av11 = sk_h_003507c8();
    (*pc5)(av11.lo,av11.hi,xo1);
    sk_h_003513b4(xo8);
    (*pc5)();
    goto LAB_001c7be4;
  }
  sk_h_00354324();
  sk_h_003507c8();
  (*xo8_02)();
  sk_h_00348730();
  v4 = *(uint64_t ****)(ax20 + 0x18);
  v7 = *(uint64_t ****)(ax20 + 0x20);
  sk_h_0034995c(ax20);
  v2 = (*xo8_03)();
  v3 = sk_enum_err(0x2d);
  sk_h_0034d708();
  sk_h_0035785c();
  sk_h_0034b824(v3 & 0xffffffffffff);
  v6 = xo1;
  v9 = (uint64_t ***)ppuStack_8;
  if ((xo8_04 == 0) &&
     (((v3 & ((uint64_t)xo1 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(xo1);
    stk_28 = v4;
    arg = (uint64_t ***)ppuStack_8;
  }
  else {
    v7 = (uint64_t ***)((uint64_t)ppuStack_8 >> 0x38 & 0xf);
    if (((uint64_t)xo1 >> 0x3d & 1) == 0) {
      sk_h_00357374();
      v8 = xo8_05;
      if (!(bool)zf) {
        v8 = v7;
      }
    }
    else if (((uint64_t)ppuStack_8 >> 0x3d & 1) == 0) {
      v8 = (uint64_t ***)((uint64_t)v4 & 0xffffffffffff);
    }
    else {
      sk_h_00350624(v3);
      sk_rt_slot2();
      v8 = v7;
      if (!(bool)zf) {
        sk_h_003542c4();
        sk_masked_free();
        sk_masked_free(ppuStack_8);
        sk_h_003599e4();
        goto LAB_001c79cc;
      }
    }
    v6 = &stk_28;
    sk_h_003508fc();
    sk_h_0035370c();
    sk_h_002a4c98();
    sk_masked_free(ppuStack_8);
    v4 = (uint64_t ***)stk_28;
    v7 = v8;
    v9 = arg;
  }
LAB_001c79cc:
  sk_h_00354774();
  sk_h_00208418();
  sk_h_00354858();
  sk_h_0034d0e0((uint64_t)v4 & 0xffffffffffff);
  if ((xo8_06 == 0) &&
     ((((uint64_t)v4 & ((uint64_t)v9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v9);
    stk_28 = v7;
    arg = ax25;
  }
  else {
    if (((uint64_t)v9 >> 0x3d & 1) == 0) {
      sk_h_00358840((uint64_t)v7 & 0xffffffffffff);
    }
    else if (((uint64_t)ax25 >> 0x3d & 1) != 0) {
      sk_h_003508fc();
      sk_h_00352a58();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a50();
        sk_masked_free(v9);
        sk_masked_free();
        sk_h_0034f938();
        goto LAB_001c7a34;
      }
    }
    sk_h_0034cb38();
    sk_h_002a4c98();
    sk_masked_free();
    v7 = (uint64_t ***)stk_28;
    ax25 = arg;
  }
LAB_001c7a34:
  sk_h_003505b0();
  sk_h_0035785c();
  sk_h_0034cb74();
  if ((xo8_07 == 0) &&
     ((((uint64_t)v7 & ((uint64_t)ax25 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax25);
    stk_28 = v4;
  }
  else {
    if (((uint64_t)ax25 >> 0x3d & 1) == 0) {
      sk_h_00357374();
    }
    else if (((uint64_t)v9 >> 0x3d & 1) != 0) {
      sk_h_0034e6ac();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ax25);
        sk_masked_free(v9);
        stk_28 = v6;
        v9 = v7;
        goto LAB_001c7a98;
      }
    }
    v6 = &stk_28;
    sk_h_003508fc();
    sk_h_00354b98();
    sk_h_002a4c98();
    sk_masked_free(v9);
    v9 = arg;
  }
LAB_001c7a98:
  v1 = stk_28;
  sk_h_00352658();
  sk_h_001a89a8();
  sk_h_00354858();
  sk_h_0034d0e0((uint64_t)v1 & 0xffffffffffff);
  if ((xo8_08 == 0) &&
     ((((uint64_t)v1 & ((uint64_t)v9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v9);
    stk_28 = v7;
    v9 = ax25;
  }
  else {
    if (((uint64_t)v9 >> 0x3d & 1) == 0) {
      sk_h_0034d610();
    }
    else if (((uint64_t)ax25 >> 0x3d & 1) != 0) {
      sk_h_003508fc();
      sk_h_00352a58();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a50();
        sk_masked_free(v9);
        sk_masked_free(ax25);
        sk_h_0034f938();
        goto LAB_001c7afc;
      }
    }
    sk_h_0034cb38();
    sk_h_002a4c98();
    sk_masked_free(ax25);
    v7 = (uint64_t ***)stk_28;
    ax25 = v9;
  }
LAB_001c7afc:
  v4 = (uint64_t ***)sk_h_0035059c();
  sk_h_0034c960();
  if ((xo8_09 == 0) &&
     ((((uint64_t)v7 & ((uint64_t)ax25 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax25);
    stk_28 = v4;
    v9 = (uint64_t ***)v1;
  }
  else {
    if (((uint64_t)ax25 >> 0x3d & 1) == 0) {
      sk_h_0034c6e4((uint64_t)v4 & 0xffffffffffff);
    }
    else if (((uint64_t)v1 >> 0x3d & 1) != 0) {
      sk_h_0009e234();
      sk_h_003518a0();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ax25);
        sk_masked_free(v1);
        stk_28 = v6;
        v9 = v7;
        goto LAB_001c7b5c;
      }
    }
    av11 = sk_h_003505e8();
    sk_h_002a4c98(av11.lo,av11.hi,0);
    sk_masked_free(v1);
  }
LAB_001c7b5c:
  sk_h_002e9850(v10,&stk_28);
  sk_h_003497ec();
  sk_h_001a89a8();
  sk_h_00354a00();
  v3 = sk_h_00349cbc(stk_28);
  if ((xo8_10 == 0) && (((v3 & ((uint64_t)v9 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)
     ) {
    sk_masked_free(v9);
  }
  else {
    if (((uint64_t)v9 >> 0x3d & 1) == 0) {
      sk_h_0034c3a0();
    }
    else if (((uint64_t)v1 >> 0x3d & 1) != 0) {
      sk_h_003515fc(v3,v9);
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034f484();
        sk_masked_free();
        sk_masked_free(v1);
        v7 = ax25;
        goto LAB_001c7bcc;
      }
    }
    sk_h_0034ef38();
    sk_h_002a4c98();
    sk_masked_free(v1);
    v7 = (uint64_t ***)stk_28;
  }
LAB_001c7bcc:
  *xo1_00 = v2;
  xo1_00[1] = v7;
  sk_h_0034f948();
  sk_h_0036986c();
LAB_001c7be4:
  sk_swift_release(ax20);
  sk_h_00354b5c();
  sk_h_00354a0c(ppuStack_8);
  return;
}



/* FUN_001c7d10 @ 0x001c7d10   (est. sk_r4_001c7d10)
 * Ghidra: undefined1  [16] FUN_001c7d10(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


sk_r4_u128_t sk_r4_001c7d10(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  long ax21;
  sk_r4_u128_t av2;
  uint64_t unaff_d8;
  uint64_t ireg;
  uint8_t auStack_68 [40];
  
  sk_h_00354bd4();
  sk_h_0034b440();
  sk_h_000a649c();
  sk_h_0034dd4c();
  (*xo9)();
  if (ax21 == 0) {
    sk_h_0034b440(auStack_68);
    v1 = sk_h_00319c0c();
    sk_h_0034ec58(v1);
    av2 = (*xo8)();
    ireg = av2.hi;
    unaff_d8 = av2.lo;
    sk_h_00357c2c();
    sk_swift_release();
  }
  else {
    sk_swift_release();
  }
  av2.hi = ireg;
  av2.lo = unaff_d8;
  return av2;
}



/* FUN_001c7db8 @ 0x001c7db8   (est. sk_r4_001c7db8)
 * Ghidra: void FUN_001c7db8(long param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c7db8(long p1)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  uint8_t auStack_68 [40];
  
  v1 = *(uint64_t *)(p1 + 0x20);
  sk_h_000dbc54();
  sk_h_000a649c(v1);
  sk_h_00351660();
  sk_h_000e15d8();
  (*xo9)();
  sk_h_00354654();
  sk_h_000836a4();
  sk_h_003519a8();
  sk_h_00319c3c();
  sk_h_0035a684();
  sk_h_000e15d8();
  (*xo8)();
  sk_h_00354624(auStack_68);
  return;
}



/* FUN_001c7e48 @ 0x001c7e48   (est. sk_r4_001c7e48)
 * Ghidra: void FUN_001c7e48(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c7e48(void)

{
  uint32_t *ax20;
  
  sk_r4_001c7db8(*ax20);
  return;
}



/* FUN_001c7e4c @ 0x001c7e4c   (est. sk_r4_001c7e4c)
 * Ghidra: void FUN_001c7e4c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c7e4c(void)

{
  uint32_t *ax20;
  
  sk_r4_001c7db8(*ax20);
  return;
}



/* FUN_001c7e64 @ 0x001c7e64   (est. sk_r4_001c7e64)
 * Ghidra: void FUN_001c7e64(undefined4 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c7e64(uint32_t *p1)

{
  long ax21;
  uint32_t v1;
  
  v1 = sk_r4_001c7d10();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c7e90 @ 0x001c7e90   (est. sk_r4_001c7e90)
 * Ghidra: void FUN_001c7e90(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c7e90(void)

{
  uint64_t ix3;
  code *xo8;
  code *xo9;
  code *xo9_00;
  uint8_t stk_7c [4];
  uint8_t auStack_78 [40];
  
  sk_h_00355e74();
  sk_h_00349658();
  sk_h_0034ec78();
  (*xo9)();
  sk_h_0007b384(ix3);
  sk_h_00350518(stk_7c);
  (*xo9_00)();
  sk_h_00354654();
  sk_h_000836a4();
  sk_h_003519a8();
  sk_h_00319c3c();
  sk_h_0035a684();
  sk_h_000e15d8();
  (*xo8)();
  sk_h_00354624(auStack_78);
  return;
}



/* FUN_001c7f48 @ 0x001c7f48   (est. sk_r4_001c7f48)
 * Ghidra: void FUN_001c7f48(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c7f48(void)

{
  uint64_t **v1;
  uint8_t zf;
  uint64_t v2;
  uint64_t v3;
  uint64_t v4;
  uint64_t **v5;
  uint64_t **xo1;
  uint64_t *xo1_00;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  long xo8_04;
  uint64_t **xo8_05;
  long xo8_06;
  long xo8_07;
  long xo8_08;
  long xo8_09;
  long xo8_10;
  code *xo9;
  code *xo9_00;
  long xo16;
  long ax20;
  code *pc6;
  uint64_t **v7;
  long ax21;
  uint64_t **v8;
  uint64_t **v9;
  uint64_t **ax25;
  uint64_t **v10;
  sk_r4_u128_t av11;
  uint64_t **stk_28;
  uint64_t **arg;
  uint64_t **ppuStack_8;
  
  sk_h_003549e4();
  sk_rt_hook_k();
  sk_rt_dispatch();
  sk_h_00348d7c();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_00349494();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_003489c0();
  (*datum_00658c00)();
  sk_h_0034c2c8();
  v2 = *(uint64_t *)(ax20 + 0x20);
  sk_h_000dbc54();
  sk_h_00352a70(v2);
  sk_h_00350bf0();
  (*xo9)();
  if (ax21 != 0) goto LAB_001c83d0;
  sk_h_00356858();
  sk_h_0034d1e0();
  v2 = sk_h_00319c0c();
  sk_h_00350b78(v2);
  v2 = (*xo8_01)();
  sk_swift_release(&stk_28);
  stk_28 = (uint64_t **)CONCAT44(stk_28._4_4_,(int)v2);
  sk_h_00355bc4();
  sk_h_0031bc70();
  sk_h_0035101c();
  sk_h_00351dfc();
  (*xo9_00)();
  sk_h_0034c4bc();
  if (!(bool)zf) {
    pc6 = *(code **)(xo16 + 0x20);
    av11 = sk_h_00351274();
    (*pc6)(av11.lo,av11.hi,xo1);
    av11 = sk_h_003507c8();
    (*pc6)(av11.lo,av11.hi,xo1);
    sk_h_003513b4(xo8);
    (*pc6)();
    goto LAB_001c83d0;
  }
  sk_h_00354324();
  sk_h_003507c8();
  (*xo8_02)();
  sk_h_00348730();
  v5 = *(uint64_t ****)(ax20 + 0x18);
  v8 = *(uint64_t ****)(ax20 + 0x20);
  sk_h_0034995c(ax20);
  v3 = (*xo8_03)();
  v4 = sk_enum_err(0x2d);
  sk_h_0034d708();
  sk_h_0035785c();
  sk_h_0034b824(v4 & 0xffffffffffff);
  v7 = xo1;
  v10 = (uint64_t ***)ppuStack_8;
  if ((xo8_04 == 0) &&
     (((v4 & ((uint64_t)xo1 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(xo1);
    stk_28 = v5;
    arg = (uint64_t ***)ppuStack_8;
  }
  else {
    v8 = (uint64_t ***)((uint64_t)ppuStack_8 >> 0x38 & 0xf);
    if (((uint64_t)xo1 >> 0x3d & 1) == 0) {
      sk_h_00357374();
      v9 = xo8_05;
      if (!(bool)zf) {
        v9 = v8;
      }
    }
    else if (((uint64_t)ppuStack_8 >> 0x3d & 1) == 0) {
      v9 = (uint64_t ***)((uint64_t)v5 & 0xffffffffffff);
    }
    else {
      sk_h_00350624(v4);
      sk_rt_slot2();
      v9 = v8;
      if (!(bool)zf) {
        sk_h_003542c4();
        sk_masked_free();
        sk_masked_free(ppuStack_8);
        sk_h_003599e4();
        goto LAB_001c81ac;
      }
    }
    v7 = &stk_28;
    sk_h_003508fc();
    sk_h_0035370c();
    sk_h_002a4c98();
    sk_masked_free(ppuStack_8);
    v5 = (uint64_t ***)stk_28;
    v8 = v9;
    v10 = arg;
  }
LAB_001c81ac:
  sk_h_00354774();
  sk_h_00208418();
  sk_h_00354858();
  sk_h_0034d0e0((uint64_t)v5 & 0xffffffffffff);
  if ((xo8_06 == 0) &&
     ((((uint64_t)v5 & ((uint64_t)v10 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v10);
    stk_28 = v8;
    arg = ax25;
  }
  else {
    if (((uint64_t)v10 >> 0x3d & 1) == 0) {
      sk_h_00358840((uint64_t)v8 & 0xffffffffffff);
    }
    else if (((uint64_t)ax25 >> 0x3d & 1) != 0) {
      sk_h_003508fc();
      sk_h_00352a58();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a50();
        sk_masked_free(v10);
        sk_masked_free();
        sk_h_0034f938();
        goto LAB_001c8214;
      }
    }
    sk_h_0034cb38();
    sk_h_002a4c98();
    sk_masked_free();
    v8 = (uint64_t ***)stk_28;
    ax25 = arg;
  }
LAB_001c8214:
  sk_h_003505b0();
  sk_h_0035785c();
  sk_h_0034cb74();
  if ((xo8_07 == 0) &&
     ((((uint64_t)v8 & ((uint64_t)ax25 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax25);
    stk_28 = v5;
  }
  else {
    if (((uint64_t)ax25 >> 0x3d & 1) == 0) {
      sk_h_00357374();
    }
    else if (((uint64_t)v10 >> 0x3d & 1) != 0) {
      sk_h_0034e6ac();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ax25);
        sk_masked_free(v10);
        stk_28 = v7;
        v10 = v8;
        goto LAB_001c8278;
      }
    }
    v7 = &stk_28;
    sk_h_003508fc();
    sk_h_00354b98();
    sk_h_002a4c98();
    sk_masked_free(v10);
    v10 = arg;
  }
LAB_001c8278:
  v1 = stk_28;
  sk_h_001a89a8((const char *)0x004e7f2b /* Float */,5,1);
  sk_h_00354858();
  sk_h_0034d0e0((uint64_t)v1 & 0xffffffffffff);
  if ((xo8_08 == 0) &&
     ((((uint64_t)v1 & ((uint64_t)v10 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v10);
    stk_28 = v8;
    v10 = ax25;
  }
  else {
    if (((uint64_t)v10 >> 0x3d & 1) == 0) {
      sk_h_0034d610();
    }
    else if (((uint64_t)ax25 >> 0x3d & 1) != 0) {
      sk_h_003508fc();
      sk_h_00352a58();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a50();
        sk_masked_free(v10);
        sk_masked_free(ax25);
        sk_h_0034f938();
        goto LAB_001c82e8;
      }
    }
    sk_h_0034cb38();
    sk_h_002a4c98();
    sk_masked_free(ax25);
    v8 = (uint64_t ***)stk_28;
    ax25 = v10;
  }
LAB_001c82e8:
  v5 = (uint64_t ***)sk_h_0035059c();
  sk_h_0034c960();
  if ((xo8_09 == 0) &&
     ((((uint64_t)v8 & ((uint64_t)ax25 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax25);
    stk_28 = v5;
    v10 = (uint64_t ***)v1;
  }
  else {
    if (((uint64_t)ax25 >> 0x3d & 1) == 0) {
      sk_h_0034c6e4((uint64_t)v5 & 0xffffffffffff);
    }
    else if (((uint64_t)v1 >> 0x3d & 1) != 0) {
      sk_h_0009e234();
      sk_h_003518a0();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ax25);
        sk_masked_free(v1);
        stk_28 = v7;
        v10 = v8;
        goto LAB_001c8348;
      }
    }
    av11 = sk_h_003505e8();
    sk_h_002a4c98(av11.lo,av11.hi,0);
    sk_masked_free(v1);
  }
LAB_001c8348:
  sk_h_002e7eb4(v2,&stk_28);
  sk_h_003497ec();
  sk_h_001a89a8();
  sk_h_00354a00();
  v4 = sk_h_00349cbc(stk_28);
  if ((xo8_10 == 0) &&
     (((v4 & ((uint64_t)v10 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(v10);
  }
  else {
    if (((uint64_t)v10 >> 0x3d & 1) == 0) {
      sk_h_0034c3a0();
    }
    else if (((uint64_t)v1 >> 0x3d & 1) != 0) {
      sk_h_003515fc(v4,v10);
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034f484();
        sk_masked_free();
        sk_masked_free(v1);
        v8 = ax25;
        goto LAB_001c83b8;
      }
    }
    sk_h_0034ef38();
    sk_h_002a4c98();
    sk_masked_free(v1);
    v8 = (uint64_t ***)stk_28;
  }
LAB_001c83b8:
  *xo1_00 = v3;
  xo1_00[1] = v8;
  sk_h_0034f948();
  sk_h_0036986c();
LAB_001c83d0:
  sk_swift_release(ax20);
  sk_h_00354b5c();
  sk_h_00354a0c(ppuStack_8);
  return;
}



/* FUN_001c84fc @ 0x001c84fc   (est. sk_r4_001c84fc)
 * Ghidra: undefined1  [16] FUN_001c84fc(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001c868c) */
/* WARNING: Removing unreachable block (ram,0x001c86d4) */
/* WARNING: Removing unreachable block (ram,0x001c85e0) */
/* WARNING: Removing unreachable block (ram,0x001c8630) */
/* WARNING: Removing unreachable block (ram,0x001c8604) */
/* WARNING: Removing unreachable block (ram,0x001c86b0) */

sk_r4_u128_t sk_r4_001c84fc(uint64_t p1)

{
  sk_r4_u128_t av1;
  uint64_t v2;
  uint64_t v3;
  uint64_t v4;
  code *xo8;
  long xo8_00;
  uint64_t xo8_01;
  long xo8_02;
  long xo8_03;
  long xo8_04;
  long ax21;
  uint64_t *ax23;
  uint64_t v5;
  sk_r4_u128_t av6;
  float2 fVar7;
  uint64_t unaff_d9;
  uint64_t ireg;
  uint8_t stk_98 [2] [16];
  
  sk_h_00344d4c(p1,stk_98);
  v5 = sk_r4_001c7d10(stk_98);
  if (ax21 == 0) {
    fVar7 = (float2)(float)v5;
    unaff_d9 = (uint64_t)(ushort)fVar7;
    ireg = 0;
    if ((ABS(fVar7) != (float2)4.44828e-41) || (0x7f7fffff < (uint)ABS((float)v5))) {
      sk_swift_release(p1);
      goto LAB_001c8718;
    }
    sk_h_00348730();
    sk_h_003535a8();
    sk_h_0035072c();
    sk_h_0034f1a8();
    sk_h_0017e880();
    sk_rt_hook_t();
    v2 = (*xo8)();
    stk_98[0] = sk_enum_err(0x2e);
    v4 = stk_98[0].hi;
    v3 = sk_h_0034f064();
    if ((xo8_00 == 0) && (((v3 & (v4 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(v4);
      sk_h_003599cc();
      stk_98[0].hi = 0x80000000005ce9d0;
      stk_98[0].lo = xo8_01;
    }
    else {
      sk_h_002a4c98(0xd000000000000013,0x80000000005ce9d0,0,0x13);
    }
    sk_h_002e7eb4(v5,stk_98);
    v5 = stk_98[0].hi;
    v3 = sk_h_00349cbc(stk_98[0].lo);
    if ((xo8_02 == 0) && (((v3 & (v5 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
      sk_masked_free(v5);
      sk_h_003599cc();
      av1.hi = 0x80000000005ce9f0;
      av1.lo = xo8_04 + 6;
    }
    else {
      sk_h_003599cc();
      sk_h_002a4c98(xo8_03 + 6,0x80000000005ce9f0,0);
      av1 = stk_98[0];
    }
    *ax23 = v2;
    *(uint8_t (*) [16])(ax23 + 1) = av1;
    ax23[3] = 0;
    *(uint8_t *)(ax23 + 9) = 3;
    sk_h_0036986c();
  }
  sk_swift_release(p1);
LAB_001c8718:
  av6.hi = ireg;
  av6.lo = unaff_d9;
  return av6;
}



/* FUN_001c877c @ 0x001c877c   (est. sk_r4_001c877c)
 * Ghidra: void FUN_001c877c(float2 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c877c(float2 p1)

{
  sk_r4_001c7db8((float)p1);
  return;
}



/* FUN_001c87a0 @ 0x001c87a0   (est. sk_r4_001c87a0)
 * Ghidra: void FUN_001c87a0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c87a0(void)

{
  uint16_t *ax20;
  
  sk_r4_001c877c(*ax20);
  return;
}



/* FUN_001c87a4 @ 0x001c87a4   (est. sk_r4_001c87a4)
 * Ghidra: void FUN_001c87a4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c87a4(void)

{
  uint16_t *ax20;
  
  sk_r4_001c877c(*ax20);
  return;
}



/* FUN_001c87bc @ 0x001c87bc   (est. sk_r4_001c87bc)
 * Ghidra: void FUN_001c87bc(undefined2 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c87bc(uint16_t *p1)

{
  long ax21;
  uint16_t v1;
  
  v1 = sk_r4_001c84fc();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c87e8 @ 0x001c87e8   (est. sk_r4_001c87e8)
 * Ghidra: void FUN_001c87e8(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c87e8(uint64_t p1)

{
  sk_r4_001c8cd8(p1,&LAB_00319c6c,0x66d5);
  return;
}



/* FUN_001c8818 @ 0x001c8818   (est. sk_r4_001c8818)
 * Ghidra: void FUN_001c8818(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8818(uint64_t p1,uint64_t p2)

{
  sk_r4_001c8da0(p1,p2,&LAB_00319c9c,0x7e8e);
  return;
}



/* FUN_001c8848 @ 0x001c8848   (est. sk_r4_001c8848)
 * Ghidra: void FUN_001c8848(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8848(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c8818(p1,*ax20);
  return;
}



/* FUN_001c884c @ 0x001c884c   (est. sk_r4_001c884c)
 * Ghidra: void FUN_001c884c(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c884c(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c8818(p1,*ax20);
  return;
}



/* FUN_001c8864 @ 0x001c8864   (est. sk_r4_001c8864)
 * Ghidra: void FUN_001c8864(undefined8 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8864(uint64_t *p1)

{
  uint64_t v1;
  long ax21;
  
  v1 = sk_r4_001c87e8();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c8890 @ 0x001c8890   (est. sk_r4_001c8890)
 * Ghidra: void FUN_001c8890(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8890(void)

{
  sk_r4_001c8e90();
  return;
}



/* FUN_001c8894 @ 0x001c8894   (est. sk_r4_001c8894)
 * Ghidra: void FUN_001c8894(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8894(void)

{
  sk_r4_001c8e90();
  return;
}



/* FUN_001c88c0 @ 0x001c88c0   (est. sk_r4_001c88c0)
 * Ghidra: void FUN_001c88c0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c88c0(void)

{
  sk_r4_001c8f7c();
  return;
}



/* FUN_001c8918 @ 0x001c8918   (est. sk_r4_001c8918)
 * Ghidra: void FUN_001c8918(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8918(uint64_t p1)

{
  sk_r4_001c97d0(p1,&LAB_00319ccc,0x46be);
  return;
}



/* FUN_001c8948 @ 0x001c8948   (est. sk_r4_001c8948)
 * Ghidra: void FUN_001c8948(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8948(uint64_t p1,uint64_t p2)

{
  sk_r4_001c9894(p1,p2,&LAB_00319cfc,0xdd24);
  return;
}



/* FUN_001c8978 @ 0x001c8978   (est. sk_r4_001c8978)
 * Ghidra: void FUN_001c8978(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8978(uint64_t p1)

{
  uint8_t *ax20;
  
  sk_r4_001c8948(p1,*ax20);
  return;
}



/* FUN_001c897c @ 0x001c897c   (est. sk_r4_001c897c)
 * Ghidra: void FUN_001c897c(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c897c(uint64_t p1)

{
  uint8_t *ax20;
  
  sk_r4_001c8948(p1,*ax20);
  return;
}



/* FUN_001c8994 @ 0x001c8994   (est. sk_r4_001c8994)
 * Ghidra: void FUN_001c8994(undefined1 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8994(uint8_t *p1)

{
  uint8_t v1;
  long ax21;
  
  v1 = sk_r4_001c8918();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c89c0 @ 0x001c89c0   (est. sk_r4_001c89c0)
 * Ghidra: void FUN_001c89c0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c89c0(void)

{
  sk_r4_001c9988();
  return;
}



/* FUN_001c89c4 @ 0x001c89c4   (est. sk_r4_001c89c4)
 * Ghidra: void FUN_001c89c4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c89c4(void)

{
  sk_r4_001c9988();
  return;
}



/* FUN_001c89f0 @ 0x001c89f0   (est. sk_r4_001c89f0)
 * Ghidra: void FUN_001c89f0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c89f0(void)

{
  sk_r4_001c9a74();
  return;
}



/* FUN_001c8a48 @ 0x001c8a48   (est. sk_r4_001c8a48)
 * Ghidra: void FUN_001c8a48(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8a48(uint64_t p1)

{
  sk_r4_001ca070(p1,&LAB_00319d2c,0x630c);
  return;
}



/* FUN_001c8a78 @ 0x001c8a78   (est. sk_r4_001c8a78)
 * Ghidra: void FUN_001c8a78(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8a78(uint64_t p1,uint64_t p2)

{
  sk_r4_001ca134(p1,p2,&LAB_00319d5c,0x9f8b);
  return;
}



/* FUN_001c8aa8 @ 0x001c8aa8   (est. sk_r4_001c8aa8)
 * Ghidra: void FUN_001c8aa8(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8aa8(uint64_t p1)

{
  uint16_t *ax20;
  
  sk_r4_001c8a78(p1,*ax20);
  return;
}



/* FUN_001c8aac @ 0x001c8aac   (est. sk_r4_001c8aac)
 * Ghidra: void FUN_001c8aac(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8aac(uint64_t p1)

{
  uint16_t *ax20;
  
  sk_r4_001c8a78(p1,*ax20);
  return;
}



/* FUN_001c8ac4 @ 0x001c8ac4   (est. sk_r4_001c8ac4)
 * Ghidra: void FUN_001c8ac4(undefined2 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8ac4(uint16_t *p1)

{
  uint16_t v1;
  long ax21;
  
  v1 = sk_r4_001c8a48();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c8af0 @ 0x001c8af0   (est. sk_r4_001c8af0)
 * Ghidra: void FUN_001c8af0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8af0(void)

{
  sk_r4_001ca228();
  return;
}



/* FUN_001c8af4 @ 0x001c8af4   (est. sk_r4_001c8af4)
 * Ghidra: void FUN_001c8af4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8af4(void)

{
  sk_r4_001ca228();
  return;
}



/* FUN_001c8b20 @ 0x001c8b20   (est. sk_r4_001c8b20)
 * Ghidra: void FUN_001c8b20(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8b20(void)

{
  sk_r4_001ca314();
  return;
}



/* FUN_001c8b78 @ 0x001c8b78   (est. sk_r4_001c8b78)
 * Ghidra: void FUN_001c8b78(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8b78(uint64_t p1)

{
  sk_r4_001ca910(p1,&LAB_00319d8c,0xf7d5);
  return;
}



/* FUN_001c8ba8 @ 0x001c8ba8   (est. sk_r4_001c8ba8)
 * Ghidra: void FUN_001c8ba8(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8ba8(uint64_t p1,uint64_t p2)

{
  sk_r4_001ca9d4(p1,p2,&LAB_00319dbc,0x9dd2);
  return;
}



/* FUN_001c8bd8 @ 0x001c8bd8   (est. sk_r4_001c8bd8)
 * Ghidra: void FUN_001c8bd8(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8bd8(uint64_t p1)

{
  uint32_t *ax20;
  
  sk_r4_001c8ba8(p1,*ax20);
  return;
}



/* FUN_001c8bdc @ 0x001c8bdc   (est. sk_r4_001c8bdc)
 * Ghidra: void FUN_001c8bdc(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8bdc(uint64_t p1)

{
  uint32_t *ax20;
  
  sk_r4_001c8ba8(p1,*ax20);
  return;
}



/* FUN_001c8bf4 @ 0x001c8bf4   (est. sk_r4_001c8bf4)
 * Ghidra: void FUN_001c8bf4(undefined4 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8bf4(uint32_t *p1)

{
  uint32_t v1;
  long ax21;
  
  v1 = sk_r4_001c8b78();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c8c20 @ 0x001c8c20   (est. sk_r4_001c8c20)
 * Ghidra: void FUN_001c8c20(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8c20(void)

{
  sk_r4_001caac8();
  return;
}



/* FUN_001c8c24 @ 0x001c8c24   (est. sk_r4_001c8c24)
 * Ghidra: void FUN_001c8c24(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8c24(void)

{
  sk_r4_001caac8();
  return;
}



/* FUN_001c8c50 @ 0x001c8c50   (est. sk_r4_001c8c50)
 * Ghidra: void FUN_001c8c50(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8c50(void)

{
  sk_r4_001cabb4();
  return;
}



/* FUN_001c8ca8 @ 0x001c8ca8   (est. sk_r4_001c8ca8)
 * Ghidra: void FUN_001c8ca8(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8ca8(uint64_t p1)

{
  sk_r4_001c8cd8(p1,&LAB_00319dec,0xed02);
  return;
}



/* FUN_001c8cd8 @ 0x001c8cd8   (est. sk_r4_001c8cd8)
 * Ghidra: void FUN_001c8cd8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8cd8(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  uint64_t ax20;
  long ax21;
  code *ax24;
  uint64_t ax30;
  
  sk_h_003564e8();
  sk_h_00351a14();
  sk_h_00354bd4();
  sk_h_00349658();
  sk_h_0034ec68(&stack0x00000008);
  (*xo9)();
  if (ax21 == 0) {
    sk_h_0034ad20(&stack0x00000008);
    v1 = (*ax24)();
    sk_h_0034ec68(v1);
    ax20 = (*xo8)();
    sk_h_00357c2c();
    sk_swift_release();
  }
  else {
    sk_swift_release();
  }
  sk_h_00356454(ax20,ax30);
  return;
}



/* FUN_001c8d70 @ 0x001c8d70   (est. sk_r4_001c8d70)
 * Ghidra: void FUN_001c8d70(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8d70(uint64_t p1,uint64_t p2)

{
  sk_r4_001c8da0(p1,p2,&LAB_00319e1c,0x536c);
  return;
}



/* FUN_001c8da0 @ 0x001c8da0   (est. sk_r4_001c8da0)
 * Ghidra: void FUN_001c8da0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8da0(void)

{
  code *xo8;
  code *xo9;
  code *ax22;
  uint64_t ax30;
  
  sk_h_003564e8();
  sk_h_00352c34();
  sk_h_00349658();
  sk_h_0034ec78();
  (*xo9)();
  sk_h_0034ec98();
  sk_h_000836a4();
  sk_h_0035159c();
  (*ax22)();
  sk_h_0035066c();
  sk_h_00351214();
  (*xo8)();
  sk_h_00354624(&stack0x00000008);
  sk_h_00356454(ax30);
  return;
}



/* FUN_001c8e18 @ 0x001c8e18   (est. sk_r4_001c8e18)
 * Ghidra: void FUN_001c8e18(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8e18(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c8d70(p1,*ax20);
  return;
}



/* FUN_001c8e1c @ 0x001c8e1c   (est. sk_r4_001c8e1c)
 * Ghidra: void FUN_001c8e1c(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8e1c(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c8d70(p1,*ax20);
  return;
}



/* FUN_001c8e34 @ 0x001c8e34   (est. sk_r4_001c8e34)
 * Ghidra: void FUN_001c8e34(undefined8 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8e34(uint64_t *p1)

{
  uint64_t v1;
  long ax21;
  
  v1 = sk_r4_001c8ca8();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c8e60 @ 0x001c8e60   (est. sk_r4_001c8e60)
 * Ghidra: void FUN_001c8e60(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8e60(void)

{
  sk_r4_001c8e90();
  return;
}



/* FUN_001c8e64 @ 0x001c8e64   (est. sk_r4_001c8e64)
 * Ghidra: void FUN_001c8e64(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8e64(void)

{
  sk_r4_001c8e90();
  return;
}



/* FUN_001c8e90 @ 0x001c8e90   (est. sk_r4_001c8e90)
 * Ghidra: void FUN_001c8e90(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8e90(void)

{
  code *xo8;
  code *xo9;
  code *xo9_00;
  code *ax22;
  uint64_t ax30;
  
  sk_h_003563e0();
  sk_h_0034ab30();
  sk_h_00350944(&stack0x00000008);
  (*xo9)();
  sk_h_00358e18();
  sk_h_000a6e14(&stack0x00000038);
  (*xo9_00)();
  sk_h_0035543c();
  sk_h_000836a4();
  sk_h_00358edc();
  (*ax22)();
  sk_h_00351318();
  sk_h_00350b18();
  (*xo8)();
  sk_h_00354624(&stack0x00000008);
  sk_h_0035578c(ax30);
  return;
}



/* FUN_001c8f24 @ 0x001c8f24   (est. sk_r4_001c8f24)
 * Ghidra: void FUN_001c8f24(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c8f24(void)

{
  sk_r4_001c8f7c();
  return;
}



/* FUN_001c8f7c @ 0x001c8f7c   (est. sk_r4_001c8f7c)
 * Ghidra: void FUN_001c8f7c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001c91dc) */
/* WARNING: Removing unreachable block (ram,0x001c9394) */

void sk_r4_001c8f7c(void)

{
  uint8_t zf;
  uint64_t v1;
  uint64_t v2;
  code *pc3;
  uint64_t v4;
  uint64_t ix4;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  long xo8_05;
  uint64_t xo8_06;
  long xo8_07;
  long xo8_08;
  long xo8_09;
  long xo8_10;
  long xo8_11;
  long xo8_12;
  code *xo9;
  code *xo9_00;
  long xo16;
  uint64_t ax20;
  long ax21;
  uint64_t ax22;
  uint64_t v5;
  uint64_t v6;
  code *ax24;
  code *ax26;
  code *pc7;
  sk_r4_u128_t av8;
  sk_r4_u128_t av9;
  long arg;
  uint64_t stk_28;
  code *arg;
  code *pc10;
  
  sk_rt_hook_c();
  sk_h_00353a24();
  sk_rt_dispatch(0);
  sk_h_00348ce8();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_00349494();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_00348a18();
  (*datum_00658c00)();
  sk_h_0034c2c8();
  sk_h_0034ca38();
  (*xo9)();
  if (ax21 != 0) goto LAB_001c94e0;
  sk_h_0034d4e8(&stk_28);
  sk_h_0035a608();
  (*xo8_01)();
  sk_h_0035014c();
  v1 = (*xo8_02)();
  sk_swift_release(&stk_28);
  stk_28 = v1;
  sk_h_00354a78();
  sk_h_0031bc70();
  sk_h_0034d914();
  (*xo9_00)();
  sk_h_0034c4bc();
  if (!(bool)zf) {
    pc3 = *(code **)(xo16 + 0x20);
    sk_h_0034d868();
    (*pc3)();
    sk_h_0034db48();
    (*pc3)();
    sk_h_003513b4(xo8);
    (*pc3)();
    goto LAB_001c94e0;
  }
  v2 = sk_h_00351dd8();
  (*xo8_03)(v2,ax22);
  av8 = sk_h_00348730();
  pc7 = av8.lo;
  v4 = *(uint64_t *)(arg + 0x18);
  v5 = *(uint64_t *)(arg + 0x20);
  sk_h_0034995c();
  (*xo8_04)();
  pc3 = (code *)sk_h_0035aab4();
  sk_h_0034d708();
  sk_h_00354cd8();
  sk_h_0034b824((uint64_t)pc3 & 0xffffffffffff);
  if ((xo8_05 == 0) &&
     ((((uint64_t)pc3 & (ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free();
    stk_28 = v4;
    arg = ax24;
  }
  else {
    v5 = (uint64_t)ax24 >> 0x38 & 0xf;
    if ((ax20 >> 0x3d & 1) == 0) {
      sk_h_00354b8c();
      v6 = xo8_06;
      if (!(bool)zf) {
        v6 = v5;
      }
    }
    else if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      v6 = v4 & 0xffffffffffff;
    }
    else {
      sk_h_0034e56c();
      sk_rt_slot2();
      v6 = v5;
      if (!(bool)zf) {
        sk_h_0034f484();
        sk_masked_free();
        sk_masked_free();
        sk_h_003552ac();
        goto LAB_001c91a8;
      }
    }
    sk_h_0034cb4c();
    sk_h_002a4c98();
    sk_masked_free();
    v4 = stk_28;
    v5 = v6;
    ax24 = arg;
  }
LAB_001c91a8:
  sk_h_0035aaa8();
  sk_h_00356b68();
  sk_h_0034c1a8();
  if ((xo8_07 == 0) &&
     (((v4 & ((uint64_t)ax24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax24);
    arg = (code *)0x0;
    stk_28 = v5;
  }
  else {
    pc3 = (code *)0x0;
    if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      sk_h_003553e4();
    }
    else {
      pc3 = (code *)(v5 & 0xffffffffffff);
    }
    sk_h_0034e8e8();
    sk_h_002a4c98();
    sk_masked_free();
  }
  v5 = stk_28;
  sk_h_003505b0();
  sk_h_00354cd8();
  sk_h_0034e910();
  if ((xo8_08 == 0) &&
     (((v5 & ((uint64_t)arg ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(arg);
    stk_28 = v4;
    pc10 = ax24;
  }
  else {
    pc3 = (code *)((uint64_t)ax24 >> 0x38 & 0xf);
    pc10 = arg;
    if (((uint64_t)arg >> 0x3d & 1) == 0) {
      sk_h_003536fc();
    }
    else if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      pc3 = (code *)(v4 & 0xffffffffffff);
    }
    else {
      sk_h_0034ef28();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(arg);
        sk_masked_free(ax24);
        sk_h_00355374();
        goto LAB_001c9260;
      }
    }
    sk_h_0034cb4c();
    sk_h_002a4c98();
    sk_masked_free(ax24);
    v4 = stk_28;
    ax24 = arg;
  }
LAB_001c9260:
  sk_h_003572c4();
  sk_h_00356b50();
  sk_h_0034c1a8();
  if ((xo8_09 == 0) &&
     (((v4 & ((uint64_t)ax24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax24);
    stk_28 = v5;
    pc10 = ax26;
  }
  else {
    pc3 = (code *)((uint64_t)ax26 >> 0x38 & 0xf);
    if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      sk_h_003536ec();
    }
    else if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      pc3 = (code *)(v5 & 0xffffffffffff);
    }
    else {
      sk_h_0034e120();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034dec4();
        sk_masked_free();
        sk_masked_free();
        sk_h_0035368c();
        goto LAB_001c92bc;
      }
    }
    sk_h_0034e8d4();
    sk_h_002a4c98();
    sk_masked_free();
    v5 = stk_28;
    ax26 = pc10;
  }
LAB_001c92bc:
  v4 = sk_h_0035059c();
  sk_h_003560b4();
  sk_h_0034d0e0();
  if ((xo8_10 == 0) &&
     (((v5 & ((uint64_t)ax26 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax26);
    stk_28 = v4;
    pc10 = pc7;
  }
  else {
    if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      sk_h_0034f97c();
    }
    else if (((uint64_t)pc7 >> 0x3d & 1) != 0) {
      sk_h_00350b78();
      sk_h_003534ec();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a50();
        sk_masked_free(ax26);
        sk_masked_free(pc7);
        sk_h_00355384();
        goto LAB_001c93fc;
      }
    }
    av9 = sk_h_00351354();
    sk_h_002a4c98(av9.lo,av9.hi,0);
    sk_masked_free(pc7);
    v4 = stk_28;
    pc7 = pc10;
  }
LAB_001c93fc:
  sk_h_00353820();
  (*arg)();
  sk_h_00354858();
  sk_h_0034d6c8(v4 & 0xffffffffffff);
  if ((xo8_11 == 0) && (((v4 & ((uint64_t)pc7 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
  {
    sk_masked_free(pc7);
    sk_h_003599f8();
  }
  else {
    if (((uint64_t)pc7 >> 0x3d & 1) == 0) {
      sk_h_0034d610();
    }
    else if (((uint64_t)pc3 >> 0x3d & 1) != 0) {
      sk_h_00350e54();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034ecf8();
        sk_masked_free();
        sk_masked_free(pc3);
        sk_h_0034f938();
        goto LAB_001c9468;
      }
    }
    sk_h_0034cb38();
    sk_h_002a4c98();
    sk_masked_free(pc3);
    v5 = stk_28;
    pc3 = pc10;
  }
LAB_001c9468:
  sk_h_003497ec();
  v4 = sk_h_001a89a8();
  sk_h_0034c960();
  if ((xo8_12 == 0) && (((v5 & ((uint64_t)pc3 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
  {
    sk_masked_free(pc3);
  }
  else {
    if (((uint64_t)pc3 >> 0x3d & 1) == 0) {
      sk_h_0034c6e4(v4 & 0xffffffffffff);
    }
    else if ((v1 >> 0x3d & 1) != 0) {
      sk_h_0009e234();
      sk_h_00351220();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(pc3);
        sk_masked_free(v1);
        sk_h_0035a5b4();
        goto LAB_001c94cc;
      }
    }
    sk_h_0034f354();
    sk_h_002a4c98();
    sk_masked_free(v1);
    v4 = stk_28;
  }
LAB_001c94cc:
  *av8.hi = ix4;
  av8.hi[1] = v4;
  sk_h_0034f948();
  sk_h_0036986c();
LAB_001c94e0:
  sk_swift_release(arg);
  sk_h_0035725c();
  sk_rt_hook_d(ix4);
  return;
}



/* FUN_001c9550 @ 0x001c9550   (est. sk_r4_001c9550)
 * Ghidra: void FUN_001c9550(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9550(uint64_t p1)

{
  sk_r4_001cb2d0(p1,&LAB_00319e4c,0x9678);
  return;
}



/* FUN_001c9580 @ 0x001c9580   (est. sk_r4_001c9580)
 * Ghidra: void FUN_001c9580(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9580(void)

{
  sk_r4_001cb398();
  return;
}



/* FUN_001c95b0 @ 0x001c95b0   (est. sk_r4_001c95b0)
 * Ghidra: void FUN_001c95b0(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c95b0(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c9580(p1,*ax20,ax20[1]);
  return;
}



/* FUN_001c95b4 @ 0x001c95b4   (est. sk_r4_001c95b4)
 * Ghidra: void FUN_001c95b4(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c95b4(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c9580(p1,*ax20,ax20[1]);
  return;
}



/* FUN_001c95cc @ 0x001c95cc   (est. sk_r4_001c95cc)
 * Ghidra: void FUN_001c95cc(undefined1 (*param_1) [16])
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c95cc(uint8_t (*p1) [16])

{
  long ax21;
  sk_r4_u128_t av1;
  
  av1 = sk_r4_001c9550();
  if (ax21 == 0) {
    *p1 = av1;
  }
  return;
}



/* FUN_001c95f8 @ 0x001c95f8   (est. sk_r4_001c95f8)
 * Ghidra: void FUN_001c95f8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c95f8(void)

{
  sk_r4_001cb4b4();
  return;
}



/* FUN_001c95fc @ 0x001c95fc   (est. sk_r4_001c95fc)
 * Ghidra: void FUN_001c95fc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c95fc(void)

{
  sk_r4_001cb4b4();
  return;
}



/* FUN_001c9628 @ 0x001c9628   (est. sk_r4_001c9628)
 * Ghidra: void FUN_001c9628(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9628(void)

{
  sk_r4_001cb5c8();
  return;
}



/* FUN_001c9680 @ 0x001c9680   (est. sk_r4_001c9680)
 * Ghidra: void FUN_001c9680(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9680(uint64_t p1)

{
  sk_r4_001c8cd8(p1,&LAB_00319eac,0x5a17);
  return;
}



/* FUN_001c96b0 @ 0x001c96b0   (est. sk_r4_001c96b0)
 * Ghidra: void FUN_001c96b0(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c96b0(uint64_t p1,uint64_t p2)

{
  sk_r4_001c8da0(p1,p2,&LAB_00319edc,0x3def);
  return;
}



/* FUN_001c96e0 @ 0x001c96e0   (est. sk_r4_001c96e0)
 * Ghidra: void FUN_001c96e0(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c96e0(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c96b0(p1,*ax20);
  return;
}



/* FUN_001c96e4 @ 0x001c96e4   (est. sk_r4_001c96e4)
 * Ghidra: void FUN_001c96e4(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c96e4(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001c96b0(p1,*ax20);
  return;
}



/* FUN_001c96fc @ 0x001c96fc   (est. sk_r4_001c96fc)
 * Ghidra: void FUN_001c96fc(undefined8 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c96fc(uint64_t *p1)

{
  uint64_t v1;
  long ax21;
  
  v1 = sk_r4_001c9680();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c9728 @ 0x001c9728   (est. sk_r4_001c9728)
 * Ghidra: void FUN_001c9728(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9728(void)

{
  sk_r4_001c8e90();
  return;
}



/* FUN_001c972c @ 0x001c972c   (est. sk_r4_001c972c)
 * Ghidra: void FUN_001c972c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c972c(void)

{
  sk_r4_001c8e90();
  return;
}



/* FUN_001c9758 @ 0x001c9758   (est. sk_r4_001c9758)
 * Ghidra: void FUN_001c9758(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9758(void)

{
  sk_h_003545d0();
  sk_r4_001c8f7c();
  return;
}



/* FUN_001c97a0 @ 0x001c97a0   (est. sk_r4_001c97a0)
 * Ghidra: void FUN_001c97a0(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c97a0(uint64_t p1)

{
  sk_r4_001c97d0(p1,&LAB_00319f0c,0xae16);
  return;
}



/* FUN_001c97d0 @ 0x001c97d0   (est. sk_r4_001c97d0)
 * Ghidra: void FUN_001c97d0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c97d0(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  long ax21;
  code *ax24;
  
  sk_h_003564e8();
  sk_h_00351a14();
  sk_h_00354bd4();
  sk_h_00349658();
  sk_h_0034ec68(&stack0x00000008);
  (*xo9)();
  if (ax21 == 0) {
    sk_h_0034ad20(&stack0x00000008);
    v1 = (*ax24)();
    sk_h_0034ec68(v1);
    (*xo8)();
    sk_h_00357b10();
    sk_swift_release();
  }
  else {
    sk_swift_release();
  }
  sk_h_00356454();
  return;
}



/* FUN_001c9864 @ 0x001c9864   (est. sk_r4_001c9864)
 * Ghidra: void FUN_001c9864(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9864(uint64_t p1,uint64_t p2)

{
  sk_r4_001c9894(p1,p2,sk_h_00319f3c,0x3724);
  return;
}



/* FUN_001c9894 @ 0x001c9894   (est. sk_r4_001c9894)
 * Ghidra: void FUN_001c9894(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9894(void)

{
  uint64_t v1;
  uint64_t xo1;
  code *xo8;
  code *xo9;
  code *ax22;
  uint64_t ax30;
  
  sk_h_003564e8();
  sk_h_00352c34();
  sk_h_00349658();
  sk_h_0034ec78();
  (*xo9)();
  sk_h_0034ec98();
  sk_h_000836a4();
  sk_h_0035159c();
  v1 = (*ax22)();
  sk_h_00351214(v1,xo1);
  (*xo8)();
  sk_h_00354624(&stack0x00000008);
  sk_h_00356454(ax30);
  return;
}



/* FUN_001c9910 @ 0x001c9910   (est. sk_r4_001c9910)
 * Ghidra: void FUN_001c9910(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9910(uint64_t p1)

{
  uint8_t *ax20;
  
  sk_r4_001c9864(p1,*ax20);
  return;
}



/* FUN_001c9914 @ 0x001c9914   (est. sk_r4_001c9914)
 * Ghidra: void FUN_001c9914(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9914(uint64_t p1)

{
  uint8_t *ax20;
  
  sk_r4_001c9864(p1,*ax20);
  return;
}



/* FUN_001c992c @ 0x001c992c   (est. sk_r4_001c992c)
 * Ghidra: void FUN_001c992c(undefined1 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c992c(uint8_t *p1)

{
  uint8_t v1;
  long ax21;
  
  v1 = sk_r4_001c97a0();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001c9958 @ 0x001c9958   (est. sk_r4_001c9958)
 * Ghidra: void FUN_001c9958(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9958(void)

{
  sk_r4_001c9988();
  return;
}



/* FUN_001c995c @ 0x001c995c   (est. sk_r4_001c995c)
 * Ghidra: void FUN_001c995c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c995c(void)

{
  sk_r4_001c9988();
  return;
}



/* FUN_001c9988 @ 0x001c9988   (est. sk_r4_001c9988)
 * Ghidra: void FUN_001c9988(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9988(void)

{
  code *xo8;
  code *xo9;
  code *xo9_00;
  code *ax22;
  uint64_t ax30;
  
  sk_h_003563e0();
  sk_h_0034ab30();
  sk_h_00350944(&stack0x00000008);
  (*xo9)();
  sk_h_00358e18();
  sk_h_000a6e14(&stack0x0000003f);
  (*xo9_00)();
  sk_h_0035543c();
  sk_h_000836a4();
  sk_h_00358edc();
  (*ax22)();
  sk_h_00351318();
  sk_h_00350b18();
  (*xo8)();
  sk_h_00354624(&stack0x00000008);
  sk_h_0035578c(ax30);
  return;
}



/* FUN_001c9a1c @ 0x001c9a1c   (est. sk_r4_001c9a1c)
 * Ghidra: void FUN_001c9a1c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001c9a1c(void)

{
  sk_r4_001c9a74();
  return;
}



/* FUN_001c9a74 @ 0x001c9a74   (est. sk_r4_001c9a74)
 * Ghidra: void FUN_001c9a74(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001c9f90) */
/* WARNING: Removing unreachable block (ram,0x001ca024) */
/* WARNING: Removing unreachable block (ram,0x001c9fa0) */
/* WARNING: Removing unreachable block (ram,0x001c9cc8) */
/* WARNING: Removing unreachable block (ram,0x001c9e80) */

void sk_r4_001c9a74(void)

{
  uint8_t zf;
  uint64_t v1;
  code *pc2;
  uint64_t v3;
  uint64_t ix4;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  long xo8_05;
  uint64_t xo8_06;
  long xo8_07;
  long xo8_08;
  long xo8_09;
  long xo8_10;
  long xo8_11;
  long xo8_12;
  code *xo9;
  code *xo9_00;
  long xo16;
  uint64_t ax20;
  long ax21;
  uint64_t ax22;
  uint64_t v4;
  uint64_t v5;
  code *ax24;
  code *ax26;
  code *pc6;
  sk_r4_u128_t av7;
  sk_r4_u128_t av8;
  long arg;
  uint64_t stk_28;
  code *arg;
  code *pc9;
  
  sk_rt_hook_c();
  sk_h_00353a24();
  sk_rt_dispatch(0);
  sk_h_00348ce8();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_00349494();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_00348a18();
  (*datum_00658c00)();
  sk_h_0034c2c8();
  sk_h_0034ca38();
  (*xo9)();
  if (ax21 != 0) goto LAB_001c9fd0;
  sk_h_0034d4e8(&stk_28);
  sk_h_0035a608();
  (*xo8_01)();
  sk_h_0035014c();
  (*xo8_02)();
  sk_h_003591b4();
  stk_28 = CONCAT71(stk_28._1_7_,(char)ax22);
  sk_h_00354a78();
  sk_h_0031bc70();
  sk_h_0034d914();
  (*xo9_00)();
  sk_h_0034c4bc();
  if (!(bool)zf) {
    pc2 = *(code **)(xo16 + 0x20);
    sk_h_0034d868();
    (*pc2)();
    sk_h_0034db48();
    (*pc2)();
    sk_h_003513b4(xo8);
    (*pc2)();
    goto LAB_001c9fd0;
  }
  v1 = sk_h_00351dd8();
  (*xo8_03)(v1,ax22);
  av7 = sk_h_00348730();
  pc6 = av7.lo;
  v3 = *(uint64_t *)(arg + 0x18);
  v4 = *(uint64_t *)(arg + 0x20);
  sk_h_0034995c();
  (*xo8_04)();
  pc2 = (code *)sk_h_0035aab4();
  sk_h_0034d708();
  sk_h_00354cd8();
  sk_h_0034b824((uint64_t)pc2 & 0xffffffffffff);
  if ((xo8_05 == 0) &&
     ((((uint64_t)pc2 & (ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free();
    stk_28 = v3;
    arg = ax24;
  }
  else {
    v4 = (uint64_t)ax24 >> 0x38 & 0xf;
    if ((ax20 >> 0x3d & 1) == 0) {
      sk_h_00354b8c();
      v5 = xo8_06;
      if (!(bool)zf) {
        v5 = v4;
      }
    }
    else if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      v5 = v3 & 0xffffffffffff;
    }
    else {
      sk_h_0034e56c();
      sk_rt_slot2();
      v5 = v4;
      if (!(bool)zf) {
        sk_h_0034f484();
        sk_masked_free();
        sk_masked_free();
        sk_h_003552ac();
        goto LAB_001c9c94;
      }
    }
    sk_h_0034cb4c();
    sk_h_002a4c98();
    sk_masked_free();
    v3 = stk_28;
    v4 = v5;
    ax24 = arg;
  }
LAB_001c9c94:
  sk_h_0035aaa8();
  sk_h_00356b68();
  sk_h_0034c1a8();
  if ((xo8_07 == 0) &&
     (((v3 & ((uint64_t)ax24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax24);
    arg = (code *)0x0;
    stk_28 = v4;
  }
  else {
    pc2 = (code *)0x0;
    if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      sk_h_003553e4();
    }
    else {
      pc2 = (code *)(v4 & 0xffffffffffff);
    }
    sk_h_0034e8e8();
    sk_h_002a4c98();
    sk_masked_free();
  }
  v4 = stk_28;
  sk_h_003505b0();
  sk_h_00354cd8();
  sk_h_0034e910();
  if ((xo8_08 == 0) &&
     (((v4 & ((uint64_t)arg ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(arg);
    stk_28 = v3;
    pc9 = ax24;
  }
  else {
    pc2 = (code *)((uint64_t)ax24 >> 0x38 & 0xf);
    pc9 = arg;
    if (((uint64_t)arg >> 0x3d & 1) == 0) {
      sk_h_003536fc();
    }
    else if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      pc2 = (code *)(v3 & 0xffffffffffff);
    }
    else {
      sk_h_0034ef28();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(arg);
        sk_masked_free(ax24);
        sk_h_00355374();
        goto LAB_001c9d4c;
      }
    }
    sk_h_0034cb4c();
    sk_h_002a4c98();
    sk_masked_free(ax24);
    v3 = stk_28;
    ax24 = arg;
  }
LAB_001c9d4c:
  sk_h_003572c4();
  sk_h_00356b50();
  sk_h_0034c1a8();
  if ((xo8_09 == 0) &&
     (((v3 & ((uint64_t)ax24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax24);
    stk_28 = v4;
    pc9 = ax26;
  }
  else {
    pc2 = (code *)((uint64_t)ax26 >> 0x38 & 0xf);
    if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      sk_h_003536ec();
    }
    else if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      pc2 = (code *)(v4 & 0xffffffffffff);
    }
    else {
      sk_h_0034e120();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034dec4();
        sk_masked_free();
        sk_masked_free();
        sk_h_0035368c();
        goto LAB_001c9da8;
      }
    }
    sk_h_0034e8d4();
    sk_h_002a4c98();
    sk_masked_free();
    v4 = stk_28;
    ax26 = pc9;
  }
LAB_001c9da8:
  v3 = sk_h_0035059c();
  sk_h_003560b4();
  sk_h_0034d0e0();
  if ((xo8_10 == 0) &&
     (((v4 & ((uint64_t)ax26 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax26);
    stk_28 = v3;
    pc9 = pc6;
  }
  else {
    if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      sk_h_0034f97c();
    }
    else if (((uint64_t)pc6 >> 0x3d & 1) != 0) {
      sk_h_00350b78();
      sk_h_003534ec();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a50();
        sk_masked_free(ax26);
        sk_masked_free(pc6);
        sk_h_00355384();
        goto LAB_001c9ee8;
      }
    }
    av8 = sk_h_00351354();
    sk_h_002a4c98(av8.lo,av8.hi,0);
    sk_masked_free(pc6);
    v3 = stk_28;
    pc6 = pc9;
  }
LAB_001c9ee8:
  av8 = sk_h_00356340();
  (*arg)(av8.lo,av8.hi,(int)ax22);
  sk_h_00354858();
  sk_h_0034d6c8(v3 & 0xffffffffffff);
  if ((xo8_11 == 0) && (((v3 & ((uint64_t)pc6 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
  {
    sk_masked_free(pc6);
    sk_h_003599f8();
  }
  else {
    if (((uint64_t)pc6 >> 0x3d & 1) == 0) {
      sk_h_0034d610();
    }
    else if (((uint64_t)pc2 >> 0x3d & 1) != 0) {
      sk_h_00350e54();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034ecf8();
        sk_masked_free();
        sk_masked_free(pc2);
        sk_h_0034f938();
        goto LAB_001c9f58;
      }
    }
    sk_h_0034cb38();
    sk_h_002a4c98();
    sk_masked_free(pc2);
    v4 = stk_28;
    pc2 = pc9;
  }
LAB_001c9f58:
  sk_h_003497ec();
  v3 = sk_h_001a89a8();
  sk_h_0034c960();
  if ((xo8_12 == 0) && (((v4 & ((uint64_t)pc2 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
  {
    sk_masked_free(pc2);
  }
  else {
    if (((uint64_t)pc2 >> 0x3d & 1) == 0) {
      sk_h_0034c6e4(v3 & 0xffffffffffff);
    }
    sk_h_0034f354();
    sk_h_002a4c98();
    sk_masked_free((int)ax22);
    v3 = stk_28;
  }
  *av7.hi = ix4;
  av7.hi[1] = v3;
  sk_h_0034f948();
  sk_h_0036986c();
LAB_001c9fd0:
  sk_swift_release(arg);
  sk_h_0035725c();
  sk_rt_hook_d(ix4);
  return;
}



/* FUN_001ca040 @ 0x001ca040   (est. sk_r4_001ca040)
 * Ghidra: void FUN_001ca040(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca040(uint64_t p1)

{
  sk_r4_001ca070(p1,&LAB_00319f6c,0x32e1);
  return;
}



/* FUN_001ca070 @ 0x001ca070   (est. sk_r4_001ca070)
 * Ghidra: void FUN_001ca070(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca070(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  long ax21;
  code *ax24;
  
  sk_h_003564e8();
  sk_h_00351a14();
  sk_h_00354bd4();
  sk_h_00349658();
  sk_h_0034ec68(&stack0x00000008);
  (*xo9)();
  if (ax21 == 0) {
    sk_h_0034ad20(&stack0x00000008);
    v1 = (*ax24)();
    sk_h_0034ec68(v1);
    (*xo8)();
    sk_h_00357b10();
    sk_swift_release();
  }
  else {
    sk_swift_release();
  }
  sk_h_00356454();
  return;
}



/* FUN_001ca104 @ 0x001ca104   (est. sk_r4_001ca104)
 * Ghidra: void FUN_001ca104(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca104(uint64_t p1,uint64_t p2)

{
  sk_r4_001ca134(p1,p2,&LAB_00319f9c,0xe9c0);
  return;
}



/* FUN_001ca134 @ 0x001ca134   (est. sk_r4_001ca134)
 * Ghidra: void FUN_001ca134(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca134(void)

{
  uint64_t v1;
  uint64_t xo1;
  code *xo8;
  code *xo9;
  code *ax22;
  uint64_t ax30;
  
  sk_h_003564e8();
  sk_h_00352c34();
  sk_h_00349658();
  sk_h_0034ec78();
  (*xo9)();
  sk_h_0034ec98();
  sk_h_000836a4();
  sk_h_0035159c();
  v1 = (*ax22)();
  sk_h_00351214(v1,xo1);
  (*xo8)();
  sk_h_00354624(&stack0x00000008);
  sk_h_00356454(ax30);
  return;
}



/* FUN_001ca1b0 @ 0x001ca1b0   (est. sk_r4_001ca1b0)
 * Ghidra: void FUN_001ca1b0(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca1b0(uint64_t p1)

{
  uint16_t *ax20;
  
  sk_r4_001ca104(p1,*ax20);
  return;
}



/* FUN_001ca1b4 @ 0x001ca1b4   (est. sk_r4_001ca1b4)
 * Ghidra: void FUN_001ca1b4(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca1b4(uint64_t p1)

{
  uint16_t *ax20;
  
  sk_r4_001ca104(p1,*ax20);
  return;
}



/* FUN_001ca1cc @ 0x001ca1cc   (est. sk_r4_001ca1cc)
 * Ghidra: void FUN_001ca1cc(undefined2 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca1cc(uint16_t *p1)

{
  uint16_t v1;
  long ax21;
  
  v1 = sk_r4_001ca040();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001ca1f8 @ 0x001ca1f8   (est. sk_r4_001ca1f8)
 * Ghidra: void FUN_001ca1f8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca1f8(void)

{
  sk_r4_001ca228();
  return;
}



/* FUN_001ca1fc @ 0x001ca1fc   (est. sk_r4_001ca1fc)
 * Ghidra: void FUN_001ca1fc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca1fc(void)

{
  sk_r4_001ca228();
  return;
}



/* FUN_001ca228 @ 0x001ca228   (est. sk_r4_001ca228)
 * Ghidra: void FUN_001ca228(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca228(void)

{
  code *xo8;
  code *xo9;
  code *xo9_00;
  code *ax22;
  uint64_t ax30;
  
  sk_h_003563e0();
  sk_h_0034ab30();
  sk_h_00350944(&stack0x00000008);
  (*xo9)();
  sk_h_00358e18();
  sk_h_000a6e14(&stack0x0000003e);
  (*xo9_00)();
  sk_h_0035543c();
  sk_h_000836a4();
  sk_h_00358edc();
  (*ax22)();
  sk_h_00351318();
  sk_h_00350b18();
  (*xo8)();
  sk_h_00354624(&stack0x00000008);
  sk_h_0035578c(ax30);
  return;
}



/* FUN_001ca2bc @ 0x001ca2bc   (est. sk_r4_001ca2bc)
 * Ghidra: void FUN_001ca2bc(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca2bc(void)

{
  sk_r4_001ca314();
  return;
}



/* FUN_001ca314 @ 0x001ca314   (est. sk_r4_001ca314)
 * Ghidra: void FUN_001ca314(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001ca830) */
/* WARNING: Removing unreachable block (ram,0x001ca8c4) */
/* WARNING: Removing unreachable block (ram,0x001ca840) */
/* WARNING: Removing unreachable block (ram,0x001ca568) */
/* WARNING: Removing unreachable block (ram,0x001ca720) */

void sk_r4_001ca314(void)

{
  uint8_t zf;
  uint64_t v1;
  code *pc2;
  uint64_t v3;
  uint64_t ix4;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  long xo8_05;
  uint64_t xo8_06;
  long xo8_07;
  long xo8_08;
  long xo8_09;
  long xo8_10;
  long xo8_11;
  long xo8_12;
  code *xo9;
  code *xo9_00;
  long xo16;
  uint64_t ax20;
  long ax21;
  uint64_t ax22;
  uint64_t v4;
  uint64_t v5;
  code *ax24;
  code *ax26;
  code *pc6;
  sk_r4_u128_t av7;
  sk_r4_u128_t av8;
  long arg;
  uint64_t stk_28;
  code *arg;
  code *pc9;
  
  sk_rt_hook_c();
  sk_h_00353a24();
  sk_rt_dispatch(0);
  sk_h_00348ce8();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_00349494();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_00348a18();
  (*datum_00658c00)();
  sk_h_0034c2c8();
  sk_h_0034ca38();
  (*xo9)();
  if (ax21 != 0) goto LAB_001ca870;
  sk_h_0034d4e8(&stk_28);
  sk_h_0035a608();
  (*xo8_01)();
  sk_h_0035014c();
  (*xo8_02)();
  sk_h_003591b4();
  stk_28 = CONCAT62(stk_28._2_6_,(short)ax22);
  sk_h_00354a78();
  sk_h_0031bc70();
  sk_h_0034d914();
  (*xo9_00)();
  sk_h_0034c4bc();
  if (!(bool)zf) {
    pc2 = *(code **)(xo16 + 0x20);
    sk_h_0034d868();
    (*pc2)();
    sk_h_0034db48();
    (*pc2)();
    sk_h_003513b4(xo8);
    (*pc2)();
    goto LAB_001ca870;
  }
  v1 = sk_h_00351dd8();
  (*xo8_03)(v1,ax22);
  av7 = sk_h_00348730();
  pc6 = av7.lo;
  v3 = *(uint64_t *)(arg + 0x18);
  v4 = *(uint64_t *)(arg + 0x20);
  sk_h_0034995c();
  (*xo8_04)();
  pc2 = (code *)sk_h_0035aab4();
  sk_h_0034d708();
  sk_h_00354cd8();
  sk_h_0034b824((uint64_t)pc2 & 0xffffffffffff);
  if ((xo8_05 == 0) &&
     ((((uint64_t)pc2 & (ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free();
    stk_28 = v3;
    arg = ax24;
  }
  else {
    v4 = (uint64_t)ax24 >> 0x38 & 0xf;
    if ((ax20 >> 0x3d & 1) == 0) {
      sk_h_00354b8c();
      v5 = xo8_06;
      if (!(bool)zf) {
        v5 = v4;
      }
    }
    else if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      v5 = v3 & 0xffffffffffff;
    }
    else {
      sk_h_0034e56c();
      sk_rt_slot2();
      v5 = v4;
      if (!(bool)zf) {
        sk_h_0034f484();
        sk_masked_free();
        sk_masked_free();
        sk_h_003552ac();
        goto LAB_001ca534;
      }
    }
    sk_h_0034cb4c();
    sk_h_002a4c98();
    sk_masked_free();
    v3 = stk_28;
    v4 = v5;
    ax24 = arg;
  }
LAB_001ca534:
  sk_h_0035aaa8();
  sk_h_00356b68();
  sk_h_0034c1a8();
  if ((xo8_07 == 0) &&
     (((v3 & ((uint64_t)ax24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax24);
    arg = (code *)0x0;
    stk_28 = v4;
  }
  else {
    pc2 = (code *)0x0;
    if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      sk_h_003553e4();
    }
    else {
      pc2 = (code *)(v4 & 0xffffffffffff);
    }
    sk_h_0034e8e8();
    sk_h_002a4c98();
    sk_masked_free();
  }
  v4 = stk_28;
  sk_h_003505b0();
  sk_h_00354cd8();
  sk_h_0034e910();
  if ((xo8_08 == 0) &&
     (((v4 & ((uint64_t)arg ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(arg);
    stk_28 = v3;
    pc9 = ax24;
  }
  else {
    pc2 = (code *)((uint64_t)ax24 >> 0x38 & 0xf);
    pc9 = arg;
    if (((uint64_t)arg >> 0x3d & 1) == 0) {
      sk_h_003536fc();
    }
    else if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      pc2 = (code *)(v3 & 0xffffffffffff);
    }
    else {
      sk_h_0034ef28();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(arg);
        sk_masked_free(ax24);
        sk_h_00355374();
        goto LAB_001ca5ec;
      }
    }
    sk_h_0034cb4c();
    sk_h_002a4c98();
    sk_masked_free(ax24);
    v3 = stk_28;
    ax24 = arg;
  }
LAB_001ca5ec:
  sk_h_003572c4();
  sk_h_00356b50();
  sk_h_0034c1a8();
  if ((xo8_09 == 0) &&
     (((v3 & ((uint64_t)ax24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax24);
    stk_28 = v4;
    pc9 = ax26;
  }
  else {
    pc2 = (code *)((uint64_t)ax26 >> 0x38 & 0xf);
    if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      sk_h_003536ec();
    }
    else if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      pc2 = (code *)(v4 & 0xffffffffffff);
    }
    else {
      sk_h_0034e120();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034dec4();
        sk_masked_free();
        sk_masked_free();
        sk_h_0035368c();
        goto LAB_001ca648;
      }
    }
    sk_h_0034e8d4();
    sk_h_002a4c98();
    sk_masked_free();
    v4 = stk_28;
    ax26 = pc9;
  }
LAB_001ca648:
  v3 = sk_h_0035059c();
  sk_h_003560b4();
  sk_h_0034d0e0();
  if ((xo8_10 == 0) &&
     (((v4 & ((uint64_t)ax26 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax26);
    stk_28 = v3;
    pc9 = pc6;
  }
  else {
    if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      sk_h_0034f97c();
    }
    else if (((uint64_t)pc6 >> 0x3d & 1) != 0) {
      sk_h_00350b78();
      sk_h_003534ec();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a50();
        sk_masked_free(ax26);
        sk_masked_free(pc6);
        sk_h_00355384();
        goto LAB_001ca788;
      }
    }
    av8 = sk_h_00351354();
    sk_h_002a4c98(av8.lo,av8.hi,0);
    sk_masked_free(pc6);
    v3 = stk_28;
    pc6 = pc9;
  }
LAB_001ca788:
  av8 = sk_h_00356340();
  (*arg)(av8.lo,av8.hi,(int)ax22);
  sk_h_00354858();
  sk_h_0034d6c8(v3 & 0xffffffffffff);
  if ((xo8_11 == 0) && (((v3 & ((uint64_t)pc6 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
  {
    sk_masked_free(pc6);
    sk_h_003599f8();
  }
  else {
    if (((uint64_t)pc6 >> 0x3d & 1) == 0) {
      sk_h_0034d610();
    }
    else if (((uint64_t)pc2 >> 0x3d & 1) != 0) {
      sk_h_00350e54();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034ecf8();
        sk_masked_free();
        sk_masked_free(pc2);
        sk_h_0034f938();
        goto LAB_001ca7f8;
      }
    }
    sk_h_0034cb38();
    sk_h_002a4c98();
    sk_masked_free(pc2);
    v4 = stk_28;
    pc2 = pc9;
  }
LAB_001ca7f8:
  sk_h_003497ec();
  v3 = sk_h_001a89a8();
  sk_h_0034c960();
  if ((xo8_12 == 0) && (((v4 & ((uint64_t)pc2 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
  {
    sk_masked_free(pc2);
  }
  else {
    if (((uint64_t)pc2 >> 0x3d & 1) == 0) {
      sk_h_0034c6e4(v3 & 0xffffffffffff);
    }
    sk_h_0034f354();
    sk_h_002a4c98();
    sk_masked_free((int)ax22);
    v3 = stk_28;
  }
  *av7.hi = ix4;
  av7.hi[1] = v3;
  sk_h_0034f948();
  sk_h_0036986c();
LAB_001ca870:
  sk_swift_release(arg);
  sk_h_0035725c();
  sk_rt_hook_d(ix4);
  return;
}



/* FUN_001ca8e0 @ 0x001ca8e0   (est. sk_r4_001ca8e0)
 * Ghidra: void FUN_001ca8e0(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca8e0(uint64_t p1)

{
  sk_r4_001ca910(p1,&LAB_00319fcc,0x700);
  return;
}



/* FUN_001ca910 @ 0x001ca910   (est. sk_r4_001ca910)
 * Ghidra: void FUN_001ca910(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca910(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  long ax21;
  code *ax24;
  
  sk_h_003564e8();
  sk_h_00351a14();
  sk_h_00354bd4();
  sk_h_00349658();
  sk_h_0034ec68(&stack0x00000008);
  (*xo9)();
  if (ax21 == 0) {
    sk_h_0034ad20(&stack0x00000008);
    v1 = (*ax24)();
    sk_h_0034ec68(v1);
    (*xo8)();
    sk_h_00357b10();
    sk_swift_release();
  }
  else {
    sk_swift_release();
  }
  sk_h_00356454();
  return;
}



/* FUN_001ca9a4 @ 0x001ca9a4   (est. sk_r4_001ca9a4)
 * Ghidra: void FUN_001ca9a4(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca9a4(uint64_t p1,uint64_t p2)

{
  sk_r4_001ca9d4(p1,p2,&LAB_00319ffc,0x3dc5);
  return;
}



/* FUN_001ca9d4 @ 0x001ca9d4   (est. sk_r4_001ca9d4)
 * Ghidra: void FUN_001ca9d4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ca9d4(void)

{
  uint64_t v1;
  uint64_t xo1;
  code *xo8;
  code *xo9;
  code *ax22;
  uint64_t ax30;
  
  sk_h_003564e8();
  sk_h_00352c34();
  sk_h_00349658();
  sk_h_0034ec78();
  (*xo9)();
  sk_h_0034ec98();
  sk_h_000836a4();
  sk_h_0035159c();
  v1 = (*ax22)();
  sk_h_00351214(v1,xo1);
  (*xo8)();
  sk_h_00354624(&stack0x00000008);
  sk_h_00356454(ax30);
  return;
}



/* FUN_001caa50 @ 0x001caa50   (est. sk_r4_001caa50)
 * Ghidra: void FUN_001caa50(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001caa50(uint64_t p1)

{
  uint32_t *ax20;
  
  sk_r4_001ca9a4(p1,*ax20);
  return;
}



/* FUN_001caa54 @ 0x001caa54   (est. sk_r4_001caa54)
 * Ghidra: void FUN_001caa54(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001caa54(uint64_t p1)

{
  uint32_t *ax20;
  
  sk_r4_001ca9a4(p1,*ax20);
  return;
}



/* FUN_001caa6c @ 0x001caa6c   (est. sk_r4_001caa6c)
 * Ghidra: void FUN_001caa6c(undefined4 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001caa6c(uint32_t *p1)

{
  uint32_t v1;
  long ax21;
  
  v1 = sk_r4_001ca8e0();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001caa98 @ 0x001caa98   (est. sk_r4_001caa98)
 * Ghidra: void FUN_001caa98(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001caa98(void)

{
  sk_r4_001caac8();
  return;
}



/* FUN_001caa9c @ 0x001caa9c   (est. sk_r4_001caa9c)
 * Ghidra: void FUN_001caa9c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001caa9c(void)

{
  sk_r4_001caac8();
  return;
}



/* FUN_001caac8 @ 0x001caac8   (est. sk_r4_001caac8)
 * Ghidra: void FUN_001caac8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001caac8(void)

{
  code *xo8;
  code *xo9;
  code *xo9_00;
  code *ax22;
  uint64_t ax30;
  
  sk_h_003563e0();
  sk_h_0034ab30();
  sk_h_00350944(&stack0x00000008);
  (*xo9)();
  sk_h_00358e18();
  sk_h_000a6e14(&stack0x0000003c);
  (*xo9_00)();
  sk_h_0035543c();
  sk_h_000836a4();
  sk_h_00358edc();
  (*ax22)();
  sk_h_00351318();
  sk_h_00350b18();
  (*xo8)();
  sk_h_00354624(&stack0x00000008);
  sk_h_0035578c(ax30);
  return;
}



/* FUN_001cab5c @ 0x001cab5c   (est. sk_r4_001cab5c)
 * Ghidra: void FUN_001cab5c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cab5c(void)

{
  sk_r4_001cabb4();
  return;
}



/* FUN_001cabb4 @ 0x001cabb4   (est. sk_r4_001cabb4)
 * Ghidra: void FUN_001cabb4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001cb0d0) */
/* WARNING: Removing unreachable block (ram,0x001cb164) */
/* WARNING: Removing unreachable block (ram,0x001cb0e0) */
/* WARNING: Removing unreachable block (ram,0x001cae08) */
/* WARNING: Removing unreachable block (ram,0x001cafc0) */

void sk_r4_001cabb4(void)

{
  uint8_t zf;
  uint64_t v1;
  code *pc2;
  uint64_t v3;
  uint64_t ix4;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  long xo8_05;
  uint64_t xo8_06;
  long xo8_07;
  long xo8_08;
  long xo8_09;
  long xo8_10;
  long xo8_11;
  long xo8_12;
  code *xo9;
  code *xo9_00;
  long xo16;
  uint64_t ax20;
  long ax21;
  uint32_t v4;
  uint64_t ax22;
  uint64_t v5;
  uint64_t v6;
  code *ax24;
  code *ax26;
  code *pc7;
  sk_r4_u128_t av8;
  sk_r4_u128_t av9;
  long arg;
  uint64_t stk_28;
  code *arg;
  code *pc10;
  
  sk_rt_hook_c();
  sk_h_00353a24();
  sk_rt_dispatch(0);
  sk_h_00348ce8();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_00349494();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_00348a18();
  (*datum_00658c00)();
  sk_h_0034c2c8();
  sk_h_0034ca38();
  (*xo9)();
  if (ax21 != 0) goto LAB_001cb110;
  sk_h_0034d4e8(&stk_28);
  sk_h_0035a608();
  (*xo8_01)();
  sk_h_0035014c();
  (*xo8_02)();
  sk_h_003591b4();
  v4 = (uint32_t)ax22;
  stk_28 = CONCAT44(stk_28._4_4_,v4);
  sk_h_00354a78();
  sk_h_0031bc70();
  sk_h_0034d914();
  (*xo9_00)();
  sk_h_0034c4bc();
  if (!(bool)zf) {
    pc2 = *(code **)(xo16 + 0x20);
    sk_h_0034d868();
    (*pc2)();
    sk_h_0034db48();
    (*pc2)();
    sk_h_003513b4(xo8);
    (*pc2)();
    goto LAB_001cb110;
  }
  v1 = sk_h_00351dd8();
  (*xo8_03)(v1,ax22);
  av8 = sk_h_00348730();
  pc7 = av8.lo;
  v3 = *(uint64_t *)(arg + 0x18);
  v5 = *(uint64_t *)(arg + 0x20);
  sk_h_0034995c();
  (*xo8_04)();
  pc2 = (code *)sk_h_0035aab4();
  sk_h_0034d708();
  sk_h_00354cd8();
  sk_h_0034b824((uint64_t)pc2 & 0xffffffffffff);
  if ((xo8_05 == 0) &&
     ((((uint64_t)pc2 & (ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free();
    stk_28 = v3;
    arg = ax24;
  }
  else {
    v5 = (uint64_t)ax24 >> 0x38 & 0xf;
    if ((ax20 >> 0x3d & 1) == 0) {
      sk_h_00354b8c();
      v6 = xo8_06;
      if (!(bool)zf) {
        v6 = v5;
      }
    }
    else if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      v6 = v3 & 0xffffffffffff;
    }
    else {
      sk_h_0034e56c();
      sk_rt_slot2();
      v6 = v5;
      if (!(bool)zf) {
        sk_h_0034f484();
        sk_masked_free();
        sk_masked_free();
        sk_h_003552ac();
        goto LAB_001cadd4;
      }
    }
    sk_h_0034cb4c();
    sk_h_002a4c98();
    sk_masked_free();
    v3 = stk_28;
    v5 = v6;
    ax24 = arg;
  }
LAB_001cadd4:
  sk_h_0035aaa8();
  sk_h_00356b68();
  sk_h_0034c1a8();
  if ((xo8_07 == 0) &&
     (((v3 & ((uint64_t)ax24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax24);
    arg = (code *)0x0;
    stk_28 = v5;
  }
  else {
    pc2 = (code *)0x0;
    if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      sk_h_003553e4();
    }
    else {
      pc2 = (code *)(v5 & 0xffffffffffff);
    }
    sk_h_0034e8e8();
    sk_h_002a4c98();
    sk_masked_free();
  }
  v5 = stk_28;
  sk_h_003505b0();
  sk_h_00354cd8();
  sk_h_0034e910();
  if ((xo8_08 == 0) &&
     (((v5 & ((uint64_t)arg ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(arg);
    stk_28 = v3;
    pc10 = ax24;
  }
  else {
    pc2 = (code *)((uint64_t)ax24 >> 0x38 & 0xf);
    pc10 = arg;
    if (((uint64_t)arg >> 0x3d & 1) == 0) {
      sk_h_003536fc();
    }
    else if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      pc2 = (code *)(v3 & 0xffffffffffff);
    }
    else {
      sk_h_0034ef28();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(arg);
        sk_masked_free(ax24);
        sk_h_00355374();
        goto LAB_001cae8c;
      }
    }
    sk_h_0034cb4c();
    sk_h_002a4c98();
    sk_masked_free(ax24);
    v3 = stk_28;
    ax24 = arg;
  }
LAB_001cae8c:
  sk_h_003572c4();
  sk_h_00356b50();
  sk_h_0034c1a8();
  if ((xo8_09 == 0) &&
     (((v3 & ((uint64_t)ax24 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax24);
    stk_28 = v5;
    pc10 = ax26;
  }
  else {
    pc2 = (code *)((uint64_t)ax26 >> 0x38 & 0xf);
    if (((uint64_t)ax24 >> 0x3d & 1) == 0) {
      sk_h_003536ec();
    }
    else if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      pc2 = (code *)(v5 & 0xffffffffffff);
    }
    else {
      sk_h_0034e120();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034dec4();
        sk_masked_free();
        sk_masked_free();
        sk_h_0035368c();
        goto LAB_001caee8;
      }
    }
    sk_h_0034e8d4();
    sk_h_002a4c98();
    sk_masked_free();
    v5 = stk_28;
    ax26 = pc10;
  }
LAB_001caee8:
  v3 = sk_h_0035059c();
  sk_h_003560b4();
  sk_h_0034d0e0();
  if ((xo8_10 == 0) &&
     (((v5 & ((uint64_t)ax26 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ax26);
    stk_28 = v3;
    pc10 = pc7;
  }
  else {
    if (((uint64_t)ax26 >> 0x3d & 1) == 0) {
      sk_h_0034f97c();
    }
    else if (((uint64_t)pc7 >> 0x3d & 1) != 0) {
      sk_h_00350b78();
      sk_h_003534ec();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a50();
        sk_masked_free(ax26);
        sk_masked_free(pc7);
        sk_h_00355384();
        goto LAB_001cb028;
      }
    }
    av9 = sk_h_00351354();
    sk_h_002a4c98(av9.lo,av9.hi,0);
    sk_masked_free(pc7);
    v3 = stk_28;
    pc7 = pc10;
  }
LAB_001cb028:
  av9 = sk_h_00356340();
  (*arg)(av9.lo,av9.hi,v4);
  sk_h_00354858();
  sk_h_0034d6c8(v3 & 0xffffffffffff);
  if ((xo8_11 == 0) && (((v3 & ((uint64_t)pc7 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
  {
    sk_masked_free(pc7);
    sk_h_003599f8();
  }
  else {
    if (((uint64_t)pc7 >> 0x3d & 1) == 0) {
      sk_h_0034d610();
    }
    else if (((uint64_t)pc2 >> 0x3d & 1) != 0) {
      sk_h_00350e54();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034ecf8();
        sk_masked_free();
        sk_masked_free(pc2);
        sk_h_0034f938();
        goto LAB_001cb098;
      }
    }
    sk_h_0034cb38();
    sk_h_002a4c98();
    sk_masked_free(pc2);
    v5 = stk_28;
    pc2 = pc10;
  }
LAB_001cb098:
  sk_h_003497ec();
  v3 = sk_h_001a89a8();
  sk_h_0034c960();
  if ((xo8_12 == 0) && (((v5 & ((uint64_t)pc2 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0))
  {
    sk_masked_free(pc2);
  }
  else {
    if (((uint64_t)pc2 >> 0x3d & 1) == 0) {
      sk_h_0034c6e4(v3 & 0xffffffffffff);
    }
    sk_h_0034f354();
    sk_h_002a4c98();
    sk_masked_free(v4);
    v3 = stk_28;
  }
  *av8.hi = ix4;
  av8.hi[1] = v3;
  sk_h_0034f948();
  sk_h_0036986c();
LAB_001cb110:
  sk_swift_release(arg);
  sk_h_0035725c();
  sk_rt_hook_d(ix4);
  return;
}



/* FUN_001cb180 @ 0x001cb180   (est. sk_r4_001cb180)
 * Ghidra: void FUN_001cb180(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb180(uint64_t p1)

{
  sk_r4_001c8cd8(p1,&LAB_0031a02c,0xf20);
  return;
}



/* FUN_001cb1b0 @ 0x001cb1b0   (est. sk_r4_001cb1b0)
 * Ghidra: void FUN_001cb1b0(undefined8 param_1,undefined8 param_2)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb1b0(uint64_t p1,uint64_t p2)

{
  sk_r4_001c8da0(p1,p2,&LAB_0031a05c,0x56c9);
  return;
}



/* FUN_001cb1e0 @ 0x001cb1e0   (est. sk_r4_001cb1e0)
 * Ghidra: void FUN_001cb1e0(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb1e0(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001cb1b0(p1,*ax20);
  return;
}



/* FUN_001cb1e4 @ 0x001cb1e4   (est. sk_r4_001cb1e4)
 * Ghidra: void FUN_001cb1e4(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb1e4(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001cb1b0(p1,*ax20);
  return;
}



/* FUN_001cb1fc @ 0x001cb1fc   (est. sk_r4_001cb1fc)
 * Ghidra: void FUN_001cb1fc(undefined8 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb1fc(uint64_t *p1)

{
  uint64_t v1;
  long ax21;
  
  v1 = sk_r4_001cb180();
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001cb228 @ 0x001cb228   (est. sk_r4_001cb228)
 * Ghidra: void FUN_001cb228(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb228(void)

{
  sk_r4_001c8e90();
  return;
}



/* FUN_001cb22c @ 0x001cb22c   (est. sk_r4_001cb22c)
 * Ghidra: void FUN_001cb22c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb22c(void)

{
  sk_r4_001c8e90();
  return;
}



/* FUN_001cb258 @ 0x001cb258   (est. sk_r4_001cb258)
 * Ghidra: void FUN_001cb258(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb258(void)

{
  sk_h_003545d0();
  sk_r4_001c8f7c();
  return;
}



/* FUN_001cb2a0 @ 0x001cb2a0   (est. sk_r4_001cb2a0)
 * Ghidra: void FUN_001cb2a0(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb2a0(uint64_t p1)

{
  sk_r4_001cb2d0(p1,&LAB_0031a08c,0x70c4);
  return;
}



/* FUN_001cb2d0 @ 0x001cb2d0   (est. sk_r4_001cb2d0)
 * Ghidra: void FUN_001cb2d0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb2d0(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  long ax21;
  code *ax24;
  uint64_t ax30;
  sk_r4_u128_t av2;
  
  sk_h_003564e8();
  sk_h_00351a14();
  sk_h_00354bd4();
  sk_h_00349658();
  sk_h_0034ec68(&stack0x00000008);
  (*xo9)();
  if (ax21 == 0) {
    sk_h_0034ad20(&stack0x00000008);
    v1 = (*ax24)();
    sk_h_0034ec68(v1);
    (*xo8)();
    sk_h_00354f1c();
    sk_h_00357c2c();
    sk_swift_release();
  }
  else {
    sk_swift_release();
  }
  av2 = sk_h_00351450();
  sk_h_00356454(av2.lo,av2.hi,ax30);
  return;
}



/* FUN_001cb368 @ 0x001cb368   (est. sk_r4_001cb368)
 * Ghidra: void FUN_001cb368(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb368(void)

{
  sk_r4_001cb398();
  return;
}



/* FUN_001cb398 @ 0x001cb398   (est. sk_r4_001cb398)
 * Ghidra: void FUN_001cb398(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb398(void)

{
  uint64_t v1;
  long r2;
  code *ix3;
  code *xo8;
  code *xo9;
  uint8_t auStack_78 [24];
  uint64_t stk_60;
  
  sk_h_0035acfc();
  r2 = sk_h_00352fd4();
  v1 = *(uint64_t *)(r2 + 0x20);
  sk_h_000dbcc8(r2,*(uint64_t *)(r2 + 0x18));
  sk_h_000a649c(v1);
  sk_h_00351660();
  sk_h_00350a04();
  (*xo9)();
  sk_h_000836a4(auStack_78,stk_60);
  sk_h_00353ccc();
  (*ix3)();
  sk_h_0034bddc();
  sk_h_00353c30();
  (*xo8)();
  sk_h_00354624(auStack_78);
  return;
}



/* FUN_001cb43c @ 0x001cb43c   (est. sk_r4_001cb43c)
 * Ghidra: void FUN_001cb43c(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb43c(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001cb368(p1,*ax20,ax20[1]);
  return;
}



/* FUN_001cb440 @ 0x001cb440   (est. sk_r4_001cb440)
 * Ghidra: void FUN_001cb440(undefined8 param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb440(uint64_t p1)

{
  uint64_t *ax20;
  
  sk_r4_001cb368(p1,*ax20,ax20[1]);
  return;
}



/* FUN_001cb458 @ 0x001cb458   (est. sk_r4_001cb458)
 * Ghidra: void FUN_001cb458(undefined1 (*param_1) [16])
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb458(uint8_t (*p1) [16])

{
  long ax21;
  sk_r4_u128_t av1;
  
  av1 = sk_r4_001cb2a0();
  if (ax21 == 0) {
    *p1 = av1;
  }
  return;
}



/* FUN_001cb484 @ 0x001cb484   (est. sk_r4_001cb484)
 * Ghidra: void FUN_001cb484(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb484(void)

{
  sk_r4_001cb4b4();
  return;
}



/* FUN_001cb488 @ 0x001cb488   (est. sk_r4_001cb488)
 * Ghidra: void FUN_001cb488(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb488(void)

{
  sk_r4_001cb4b4();
  return;
}



/* FUN_001cb4b4 @ 0x001cb4b4   (est. sk_r4_001cb4b4)
 * Ghidra: void FUN_001cb4b4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb4b4(void)

{
  uint64_t v1;
  code *xo8;
  code *xo9;
  code *xo9_00;
  code *ax22;
  uint64_t uStack_98;
  uint8_t auStack_88 [24];
  uint64_t stk_70;
  uint64_t uStack_68;
  
  sk_h_0034ab30();
  sk_h_00350944(auStack_88);
  (*xo9)();
  sk_h_0007b384();
  sk_h_00355d40();
  sk_h_000a6e14();
  (*xo9_00)();
  sk_h_000836a4(auStack_88,stk_70);
  (*ax22)(uStack_68);
  v1 = sk_h_0035066c();
  sk_h_00351cd0(v1,uStack_98);
  (*xo8)();
  sk_h_00354624(auStack_88);
  return;
}



/* FUN_001cb570 @ 0x001cb570   (est. sk_r4_001cb570)
 * Ghidra: void FUN_001cb570(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb570(void)

{
  sk_r4_001cb5c8();
  return;
}



/* FUN_001cb5c8 @ 0x001cb5c8   (est. sk_r4_001cb5c8)
 * Ghidra: void FUN_001cb5c8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cb5c8(void)

{
  sk_r4_u128_t av1;
  code **pppcVar2;
  code **pppcVar3;
  uint8_t zf;
  uint64_t v4;
  code **ppppcVar5;
  code **pppcVar6;
  code **ppppcVar7;
  code **xo1;
  uint64_t v8;
  uint64_t ix3;
  code *ix4;
  uint64_t ix6;
  uint64_t ix7;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  long xo8_03;
  long xo8_04;
  long xo8_05;
  long xo8_06;
  long xo8_07;
  long xo8_08;
  long xo8_09;
  code *xo9;
  code *xo9_00;
  long xo16;
  long xo16_00;
  long ax20;
  code *pc9;
  code **ppppcVar10;
  long ax21;
  code **ax23;
  code **ppppcVar11;
  code **ppppcVar12;
  code **ax25;
  code **ppppcVar13;
  sk_r4_u128_t av14;
  sk_r4_u128_t av15;
  code **arg;
  code **stk_30;
  code **ppppcVar16;
  uint64_t stk_18;
  
  sk_rt_hook_c();
  sk_h_00354ba4();
  sk_rt_dispatch(0);
  sk_h_00348e18();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_rt_hook_e();
  sk_rt_hook_i();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_003489c0();
  (*datum_00658c00)();
  sk_h_0034b4c0();
  sk_h_00353cf0();
  sk_h_0034d1e0();
  sk_h_000a649c();
  sk_h_00351360(&stk_30);
  (*xo9)();
  if (ax21 != 0) goto LAB_001cbb3c;
  sk_h_0034d1e0(&stk_30,stk_18);
  v4 = (*ix4)();
  sk_h_00351360(v4);
  av14 = (*xo8_01)();
  ppppcVar5 = av14.lo;
  sk_swift_release(&stk_30);
  stk_30 = (code ***)ppppcVar5;
  sk_h_0031bc70(ix3);
  sk_h_00352b44(&stk_30);
  (*xo9_00)();
  av15 = sk_h_0035172c();
  sk_h_00350884(av15.lo,av15.hi,ax25);
  if (!(bool)zf) {
    pc9 = *(code **)(xo16_00 + 0x20);
    sk_h_0034ed78();
    (*pc9)();
    av14 = sk_h_0035072c();
    (*pc9)(av14.lo,av14.hi,ax25);
    sk_h_00350c8c(xo8);
    (*pc9)();
    goto LAB_001cbb3c;
  }
  ppppcVar13 = (code ****)(xo16 + 8);
  (*(code *)*ppppcVar13)();
  sk_h_00348730();
  ppppcVar7 = *(code *****)(ax20 + 0x18);
  ppppcVar16 = *(code *****)(ax20 + 0x20);
  sk_h_0034995c(ax20);
  pppcVar6 = (code ***)(*xo8_02)();
  sk_enum_err(0x2d);
  av15 = sk_h_00351e08();
  ppppcVar11 = av15.hi;
  stk_30 = av15.lo;
  sk_h_0034f958();
  sk_h_003535a8();
  sk_rt_hook_v();
  ppppcVar10 = ax25;
  ppppcVar12 = ppppcVar5;
  if ((xo8_03 == 0) &&
     ((((uint64_t)ax25 & ((uint64_t)ppppcVar7 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ppppcVar7);
    stk_30 = (code ***)ppppcVar16;
    ppppcVar11 = ax23;
  }
  else {
    if (((uint64_t)ppppcVar7 >> 0x3d & 1) == 0) {
      zf = ((uint64_t)ax23 & 0x2000000000000000) == 0;
    }
    else if (((uint64_t)ax23 >> 0x3d & 1) != 0) {
      sk_h_00350288(ax25);
      sk_rt_slot2();
      ppppcVar12 = xo1;
      if (!(bool)zf) {
        sk_h_0035351c();
        sk_masked_free(ppppcVar7);
        sk_masked_free();
        ppppcVar12 = xo1;
        stk_30 = (code ***)ax25;
        ppppcVar11 = xo1;
        goto LAB_001cb884;
      }
    }
    sk_h_000e15d8();
    sk_h_00352938();
    sk_h_002a4c98();
    sk_masked_free();
    ppppcVar10 = &stk_30;
  }
LAB_001cb884:
  pppcVar2 = stk_30;
  sk_h_00208418(ax25,0);
  sk_h_00354cd8();
  sk_h_0034eb74((uint64_t)pppcVar2 & 0xffffffffffff);
  if ((xo8_04 == 0) &&
     ((((uint64_t)pppcVar2 & ((uint64_t)ppppcVar11 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ppppcVar11);
    stk_30 = (code ***)ppppcVar7;
  }
  else {
    if (((uint64_t)ppppcVar11 >> 0x3d & 1) == 0) {
      sk_h_003536fc();
    }
    else if (((uint64_t)ppppcVar12 >> 0x3d & 1) != 0) {
      sk_h_0034e69c();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ppppcVar11);
        sk_masked_free(ppppcVar12);
        stk_30 = (code ***)ppppcVar10;
        ppppcVar12 = (code ****)pppcVar2;
        goto LAB_001cb8f0;
      }
    }
    ppppcVar10 = &stk_30;
    sk_h_0035072c();
    sk_h_00352938();
    sk_h_002a4c98();
    sk_masked_free(ppppcVar12);
    ppppcVar12 = ppppcVar11;
  }
LAB_001cb8f0:
  pppcVar3 = stk_30;
  sk_h_003505b0();
  sk_h_003535a8();
  sk_h_0034c1a8();
  if ((xo8_05 == 0) &&
     ((((uint64_t)pppcVar3 & ((uint64_t)ppppcVar12 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ppppcVar12);
    stk_30 = pppcVar2;
  }
  else {
    if (((uint64_t)ppppcVar12 >> 0x3d & 1) == 0) {
      zf = ((uint64_t)ppppcVar11 & 0x2000000000000000) == 0;
    }
    else if (((uint64_t)ppppcVar11 >> 0x3d & 1) != 0) {
      sk_h_0034e120();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034dec4();
        sk_masked_free();
        sk_masked_free(ppppcVar11);
        stk_30 = pppcVar3;
        ppppcVar11 = ppppcVar10;
        goto LAB_001cb958;
      }
    }
    ppppcVar10 = &stk_30;
    sk_h_000e15d8();
    sk_h_00352938();
    sk_h_002a4c98();
    sk_masked_free(ppppcVar11);
    ppppcVar11 = ppppcVar12;
  }
LAB_001cb958:
  pppcVar2 = stk_30;
  ppppcVar7 = (code ****)sk_h_001a89a8(ix6,ix7,1);
  sk_h_003560b4();
  sk_h_0034eb74();
  if ((xo8_06 == 0) &&
     ((((uint64_t)pppcVar2 & ((uint64_t)ppppcVar11 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ppppcVar11);
    stk_30 = (code ***)ppppcVar7;
  }
  else {
    if (((uint64_t)ppppcVar11 >> 0x3d & 1) == 0) {
      sk_h_00357380();
    }
    else if (((uint64_t)ppppcVar13 >> 0x3d & 1) != 0) {
      sk_h_0034e69c();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ppppcVar11);
        sk_masked_free(ppppcVar13);
        stk_30 = (code ***)ppppcVar10;
        ppppcVar13 = (code ****)pppcVar2;
        goto LAB_001cb9cc;
      }
    }
    ppppcVar10 = &stk_30;
    sk_h_003510ac();
    sk_h_00353b40();
    sk_h_002a4c98();
    sk_masked_free(ppppcVar13);
    ppppcVar13 = ppppcVar11;
  }
LAB_001cb9cc:
  pppcVar2 = stk_30;
  av1.hi = ppppcVar10;
  av1.lo = stk_30;
  av15 = sk_h_0035059c();
  v8 = av15.hi;
  sk_h_0034d6c8((uint64_t)pppcVar2 & 0xffffffffffff);
  if ((xo8_07 == 0) &&
     ((((uint64_t)pppcVar2 & ((uint64_t)ppppcVar13 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ppppcVar13);
  }
  else {
    if (((uint64_t)ppppcVar13 >> 0x3d & 1) == 0) {
      sk_h_0034e374(av15.lo & 0xffffffffffff);
    }
    else if ((v8 >> 0x3d & 1) != 0) {
      sk_h_0035100c();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_0034ecf8();
        sk_masked_free();
        sk_masked_free(v8);
        av15 = av1;
        goto LAB_001cba38;
      }
    }
    ppppcVar10 = &stk_30;
    av15 = sk_h_00351160();
    sk_h_002a4c98(av15.lo,av15.hi,0);
    sk_masked_free(v8);
    av15.hi = ppppcVar13;
    av15.lo = stk_30;
  }
LAB_001cba38:
  ppppcVar16 = av15.hi;
  stk_30 = av15.lo;
  ppppcVar7 = (code ****)stk_30;
  av15 = sk_h_00356340();
  (*(code *)arg)(av15.lo,av15.hi,ppppcVar5,av14.hi);
  sk_h_0035a25c();
  sk_h_0034d044((uint64_t)ppppcVar7 & 0xffffffffffff);
  if ((xo8_08 == 0) &&
     ((((uint64_t)ppppcVar7 & ((uint64_t)ppppcVar16 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(ppppcVar16);
    stk_30 = pppcVar2;
  }
  else {
    if (((uint64_t)ppppcVar16 >> 0x3d & 1) == 0) {
      sk_h_00351500((uint64_t)pppcVar2 & 0xffffffffffff);
    }
    else if (((uint64_t)arg >> 0x3d & 1) != 0) {
      sk_h_003508d8(ppppcVar7);
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a5c();
        sk_masked_free(ppppcVar16);
        sk_masked_free(arg);
        stk_30 = (code ***)ppppcVar10;
        arg = ppppcVar7;
        goto LAB_001cbab4;
      }
    }
    av14 = sk_h_003509e0();
    sk_h_002a4c98(av14.lo,av14.hi,0);
    sk_masked_free(arg);
    arg = ppppcVar16;
  }
LAB_001cbab4:
  pppcVar2 = stk_30;
  sk_h_003497ec();
  sk_h_001a89a8();
  sk_h_00351f28();
  sk_h_0034de14((uint64_t)pppcVar2 & 0xffffffffffff);
  if ((xo8_09 == 0) &&
     ((((uint64_t)pppcVar2 & ((uint64_t)arg ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free(arg);
  }
  else {
    if (((uint64_t)arg >> 0x3d & 1) == 0) {
      sk_h_0034a7ac();
    }
    else if (((uint64_t)ppppcVar7 >> 0x3d & 1) != 0) {
      sk_h_0034ef98();
      sk_rt_slot2();
      if (!(bool)zf) {
        sk_h_00351a50();
        sk_masked_free(arg);
        sk_masked_free(ppppcVar7);
        sk_h_0035aafc();
        goto LAB_001cbb18;
      }
    }
    sk_h_0034c5bc();
    sk_h_002a4c98();
    sk_masked_free(ppppcVar7);
    ppppcVar7 = arg;
    ppppcVar11 = (code ****)stk_30;
  }
LAB_001cbb18:
  *xo1 = pppcVar6;
  xo1[1] = (code ***)ppppcVar11;
  xo1[2] = (code ***)ppppcVar7;
  xo1[3] = (code ***)0x0;
  *(uint8_t *)(xo1 + 9) = 3;
  sk_h_0036986c();
LAB_001cbb3c:
  sk_swift_release(ax20);
  sk_h_00354b5c();
  sk_rt_hook_d(xo16);
  return;
}



/* FUN_001cbcb4 @ 0x001cbcb4   (est. sk_r4_001cbcb4)
 * Ghidra: void FUN_001cbcb4(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cbcb4(uint64_t p1,uint64_t p2,uint64_t p3)

{
  uint8_t zf;
  long r1;
  uint64_t v2;
  long xo1;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo9;
  code *xo9_00;
  long xo16;
  long xo16_00;
  uint64_t v3;
  sk_r4_u128_t av4;
  uint64_t arg;
  uint8_t auStack_28 [40];
  
  sk_rt_hook_c();
  v3 = *(uint64_t *)(xo1 + 0x10);
  sk_h_003499f0();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  sk_h_00348f50();
  sk_h_00349b3c();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  r1 = sk_h_0034947c();
  v2 = *(uint64_t *)(r1 + 0x20);
  sk_h_0034e1ec();
  sk_h_00352a70(v2);
  sk_h_00084174();
  (*xo9)();
  av4 = sk_h_00350ab8(*(uint64_t *)(xo16_00 + 0x10));
  (*xo8_01)(av4.lo,av4.hi,xo1);
  sk_h_0034b2c8();
  if ((bool)zf) {
    sk_h_00354c38();
    sk_h_000836a4();
    sk_h_00351a44();
    v2 = sk_h_0034310c();
    sk_h_003504ac(v2);
    (*xo8_02)();
  }
  else {
    sk_h_003547ec();
    av4 = sk_h_003510dc();
    (*xo9_00)(av4.lo,av4.hi,v3);
    sk_h_00354c38();
    sk_h_000836a4();
    sk_h_003519a8();
    sk_h_0031a0ec();
    av4 = sk_h_0034d3a4();
    sk_h_00351f64(av4.lo,av4.hi,p3);
    (*xo8_03)();
    sk_h_00350630(*(uint64_t *)(xo16 + 8));
    (*xo8_04)();
  }
  sk_swift_release(auStack_28);
  sk_h_00351348();
  sk_rt_hook_d(arg);
  return;
}



/* FUN_001cbe48 @ 0x001cbe48   (est. sk_r4_001cbe48)
 * Ghidra: void FUN_001cbe48(undefined8 param_1,undefined8 param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cbe48(uint64_t p1,uint64_t p2,uint64_t p3)

{
  sk_r4_001cbcb4(p1,p2,*(uint64_t *)((p3 & 0xfffffffffffffffe) - 8));
  return;
}



/* FUN_001cbe4c @ 0x001cbe4c   (est. sk_r4_001cbe4c)
 * Ghidra: void FUN_001cbe4c(undefined8 param_1,undefined8 param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cbe4c(uint64_t p1,uint64_t p2,uint64_t p3)

{
  sk_r4_001cbcb4(p1,p2,*(uint64_t *)((p3 & 0xfffffffffffffffe) - 8));
  return;
}



/* FUN_001cbe68 @ 0x001cbe68   (est. sk_r4_001cbe68)
 * Ghidra: void FUN_001cbe68(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001cbfb0) */

void sk_r4_001cbe68(uint64_t p1,uint64_t p2,uint64_t p3)

{
  bool bVar1;
  uint64_t v2;
  uint64_t v3;
  uint64_t v4;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo9;
  code *xo9_00;
  long xo16;
  long xo16_00;
  long ax21;
  uint64_t ax23;
  sk_r4_u128_t av5;
  sk_r4_u128_t av6;
  uint8_t auStack_28 [40];
  
  av5 = sk_rt_hook_c();
  v4 = av5.hi;
  sk_h_00349b3c();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_003493ac();
  sk_rt_dispatch(0);
  sk_h_00348d4c();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_rt_hook_e();
  sk_h_003504ac();
  sk_h_0034e7a0();
  sk_h_0009e234(auStack_28);
  (*xo9)();
  if (ax21 == 0) {
    sk_h_00356858();
    sk_h_0034f1a8();
    sk_h_0031b46c();
    sk_h_0034d394();
    v2 = (*xo8_01)();
    bVar1 = (v2 & 1) == 0;
    if (bVar1) {
      sk_h_00356858();
      sk_h_0034f1a8();
      sk_h_0031a11c();
      v3 = sk_h_00353378();
      sk_h_00351c70(v3,v4,p3);
      (*xo9_00)();
      av6 = sk_h_00351160(*(uint64_t *)(xo16 + 0x20));
      (*xo8_02)(av6.lo,av6.hi,v4);
    }
    sk_h_000839d8(ax23,!bVar1,1,v4);
    sk_swift_release(auStack_28);
    sk_h_00352370(*(uint64_t *)(xo16_00 + 0x20),xo8);
    (*xo8_03)();
  }
  sk_swift_release(av5.lo);
  sk_h_0035725c();
  sk_rt_hook_d(xo8);
  return;
}



/* FUN_001cc030 @ 0x001cc030   (est. sk_r4_001cc030)
 * Ghidra: void FUN_001cc030(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc030(uint64_t p1,long p2,uint64_t p3)

{
  sk_r4_001cbe68(p1,*(uint64_t *)(p2 + 0x10),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8));
  return;
}



/* FUN_001cc034 @ 0x001cc034   (est. sk_r4_001cc034)
 * Ghidra: void FUN_001cc034(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc034(uint64_t p1,long p2,uint64_t p3)

{
  sk_r4_001cbe68(p1,*(uint64_t *)(p2 + 0x10),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8));
  return;
}



/* FUN_001cc054 @ 0x001cc054   (est. sk_r4_001cc054)
 * Ghidra: void FUN_001cc054(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc054(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4)

{
  uint64_t v1;
  code *pc2;
  long r3;
  long xo1;
  long xo8;
  code *xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long ax21;
  sk_r4_u128_t av4;
  uint64_t arg;
  uint8_t auStack_28 [24];
  uint64_t stk_10;
  
  sk_rt_hook_c();
  sk_h_00349720();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  r3 = sk_h_00348f50();
  v1 = *(uint64_t *)(r3 + 0x20);
  sk_h_000dbcc8(r3,*(uint64_t *)(r3 + 0x18));
  sk_h_00352680(v1);
  sk_h_00350ea4(auStack_28);
  (*xo9)();
  r3 = 0;
  do {
    if (r3 == *(long *)(xo1 + 0x10)) {
LAB_001cc174:
      sk_swift_release(auStack_28);
      sk_h_00351348();
      sk_rt_hook_d(arg);
      return;
    }
    av4 = sk_h_00100c38();
    sk_h_0019ea20(av4.lo,av4.hi,p3);
    if (SCARRY8(r3,1)) {
                    /* WARNING: Does not return */
      pc2 = (code *)SoftwareBreakpoint(1,0x1cc198);
      (*pc2)();
    }
    sk_h_000836a4(auStack_28,stk_10);
    sk_h_00352b74();
    sk_h_0031a14c();
    av4 = sk_h_0034d3a4();
    sk_h_00356104(av4.lo,av4.hi,p4);
    (*xo8_00)();
    if (ax21 != 0) {
      sk_h_00350630(*(uint64_t *)(xo16 + 8));
      (*xo8_02)();
      goto LAB_001cc174;
    }
    sk_h_00350630(*(uint64_t *)(xo16 + 8));
    (*xo8_01)();
    r3 = r3 + 1;
  } while( true );
}



/* FUN_001cc198 @ 0x001cc198   (est. sk_r4_001cc198)
 * Ghidra: void FUN_001cc198(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc198(uint64_t p1,long p2,uint64_t p3)

{
  uint64_t *ax20;
  
  sk_r4_001cc054(p1,*ax20,*(uint64_t *)(p2 + 0x10),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8));
  return;
}



/* FUN_001cc19c @ 0x001cc19c   (est. sk_r4_001cc19c)
 * Ghidra: void FUN_001cc19c(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc19c(uint64_t p1,long p2,uint64_t p3)

{
  uint64_t *ax20;
  
  sk_r4_001cc054(p1,*ax20,*(uint64_t *)(p2 + 0x10),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8));
  return;
}



/* FUN_001cc1c4 @ 0x001cc1c4   (est. sk_r4_001cc1c4)
 * Ghidra: void FUN_001cc1c4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc1c4(void)

{
  sk_r4_001cc3c0();
  return;
}



/* FUN_001cc1c8 @ 0x001cc1c8   (est. sk_r4_001cc1c8)
 * Ghidra: void FUN_001cc1c8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc1c8(void)

{
  sk_r4_001cc3c0();
  return;
}



/* FUN_001cc204 @ 0x001cc204   (est. sk_r4_001cc204)
 * Ghidra: void FUN_001cc204(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc204(void)

{
  sk_r4_001cc54c();
  return;
}



/* FUN_001cc208 @ 0x001cc208   (est. sk_r4_001cc208)
 * Ghidra: void FUN_001cc208(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc208(void)

{
  sk_r4_001cc54c();
  return;
}



/* FUN_001cc230 @ 0x001cc230   (est. sk_r4_001cc230)
 * Ghidra: void FUN_001cc230(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc230(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4)

{
  long r1;
  uint64_t v2;
  long xo1;
  long xo8;
  code *xo8_00;
  code *xo8_01;
  code *xo9;
  long xo16;
  long ax21;
  long r3;
  sk_r4_u128_t av4;
  uint64_t arg;
  uint8_t auStack_28 [24];
  uint64_t stk_10;
  
  sk_rt_hook_c();
  sk_h_00349720();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  r1 = sk_h_00348f50();
  v2 = *(uint64_t *)(r1 + 0x20);
  sk_h_000dbcc8(r1,*(uint64_t *)(r1 + 0x18));
  sk_h_00352680(v2);
  sk_h_00350ea4(auStack_28);
  (*xo9)();
  r1 = 0;
  r3 = *(long *)(xo1 + 0x10);
  do {
    if (r3 == r1) break;
    v2 = sk_h_00353c78();
    sk_h_001dc430(v2,xo1,p3);
    r1 = r1 + 1;
    sk_h_000836a4(auStack_28,stk_10);
    sk_h_00352b74();
    sk_h_0031a14c();
    av4 = sk_h_0034e044();
    sk_h_00356104(av4.lo,av4.hi,p4);
    (*xo8_00)();
    sk_h_00351274(*(uint64_t *)(xo16 + 8));
    (*xo8_01)();
  } while (ax21 == 0);
  sk_swift_release(auStack_28);
  sk_h_00351348();
  sk_rt_hook_d(arg);
  return;
}



/* FUN_001cc354 @ 0x001cc354   (est. sk_r4_001cc354)
 * Ghidra: void FUN_001cc354(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc354(uint64_t p1,long p2,uint64_t p3)

{
  uint64_t *ax20;
  
  sk_r4_001cc230(p1,*ax20,*(uint64_t *)(p2 + 0x10),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8));
  return;
}



/* FUN_001cc358 @ 0x001cc358   (est. sk_r4_001cc358)
 * Ghidra: void FUN_001cc358(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc358(uint64_t p1,long p2,uint64_t p3)

{
  uint64_t *ax20;
  
  sk_r4_001cc230(p1,*ax20,*(uint64_t *)(p2 + 0x10),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8));
  return;
}



/* FUN_001cc380 @ 0x001cc380   (est. sk_r4_001cc380)
 * Ghidra: void FUN_001cc380(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc380(void)

{
  sk_r4_001cc3c0();
  return;
}



/* FUN_001cc384 @ 0x001cc384   (est. sk_r4_001cc384)
 * Ghidra: void FUN_001cc384(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc384(void)

{
  sk_r4_001cc3c0();
  return;
}



/* FUN_001cc3c0 @ 0x001cc3c0   (est. sk_r4_001cc3c0)
 * Ghidra: void FUN_001cc3c0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001cc4ec) */

void sk_r4_001cc3c0(void)

{
  long r1;
  uint64_t v2;
  uint64_t v3;
  uint64_t v4;
  code *xo8;
  code *xo9;
  code *xo9_00;
  long xo16;
  uint64_t ax20;
  long ax21;
  code *ax23;
  code *ax24;
  uint64_t arg;
  uint64_t arg;
  uint8_t auStack_28 [32];
  uint64_t uStack_8;
  
  sk_rt_hook_c();
  sk_h_00356c84();
  sk_h_0034ece8();
  (*datum_00658c00)(*(uint64_t *)(xo16 + 0x40));
  sk_h_003493ac();
  r1 = sk_h_003521a4();
  v4 = *(uint64_t *)(r1 + 0x20);
  sk_h_000dbcc8(r1,*(uint64_t *)(r1 + 0x18));
  sk_h_00352680(v4);
  sk_h_003509d4(auStack_28);
  (*xo9)();
  if (ax21 == 0) {
    while( true ) {
      v4 = uStack_8;
      sk_h_0034e1ec(auStack_28);
      sk_h_0031a17c(v4);
      v2 = sk_h_00350a88();
      v3 = (*xo8)(v2,v4);
      if ((v3 & 1) != 0) break;
      sk_h_00354c38();
      sk_h_000836a4();
      sk_h_00352b74();
      sk_h_0031a1ac();
      sk_h_0034dbc8();
      sk_h_003515d8();
      (*xo9_00)();
      sk_h_003508e4();
      (*ax24)();
      sk_h_00355c1c();
      (*ax23)();
    }
    sk_swift_release(auStack_28);
    sk_swift_release(r1);
    ax20 = arg;
  }
  else {
    sk_h_0006f6b4();
    sk_free();
    sk_swift_release(r1);
  }
  v4 = sk_h_00354b5c(ax20);
  sk_rt_hook_d(v4,arg);
  return;
}



/* FUN_001cc520 @ 0x001cc520   (est. sk_r4_001cc520)
 * Ghidra: void FUN_001cc520(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc520(void)

{
  sk_r4_001cc54c();
  return;
}



/* FUN_001cc524 @ 0x001cc524   (est. sk_r4_001cc524)
 * Ghidra: void FUN_001cc524(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc524(void)

{
  sk_r4_001cc54c();
  return;
}



/* FUN_001cc54c @ 0x001cc54c   (est. sk_r4_001cc54c)
 * Ghidra: void FUN_001cc54c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc54c(void)

{
  uint64_t v1;
  code *ix3;
  long xo8;
  uint64_t *ax19;
  long ax21;
  sk_r4_u128_t av2;
  
  av2 = sk_h_0035a6f4();
  v1 = (*ix3)(av2.lo,*(uint64_t *)(av2.hi + 0x10),
                   *(uint64_t *)(xo8 + -8));
  if (ax21 == 0) {
    *ax19 = v1;
  }
  return;
}



/* FUN_001cc584 @ 0x001cc584   (est. sk_r4_001cc584)
 * Ghidra: void FUN_001cc584(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc584(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4)

{
  long r1;
  long r2;
  code *pc3;
  long r4;
  uint64_t v5;
  long xo1;
  long xo8;
  long xo8_00;
  uint64_t xo8_01;
  code *xo8_02;
  code *xo8_03;
  code *xo8_04;
  code *xo9;
  long xo16;
  long ax21;
  uint8_t auStack_80 [24];
  uint64_t stk_68;
  long stk_58;
  long lStack_50;
  long stk_48;
  long lStack_40;
  long stk_38;
  
  sk_rt_hook_c();
  sk_h_00349720();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  r4 = sk_h_003497b4();
  sk_h_0034d1e0(r4,*(uint64_t *)(r4 + 0x18));
  sk_h_00352680();
  sk_h_00350ab8(auStack_80);
  (*xo9)();
  sk_h_00354948(*(uint8_t *)(xo1 + 0x20));
  sk_h_0034fa4c();
  sk_h_00357280();
  sk_h_0035056c();
  sk_h_0028adc4();
  sk_h_00352b98(xo16 + 0x10);
  sk_h_00352554(xo16 + 8);
  sk_alloc_pages(xo1);
  r4 = stk_38;
  r2 = lStack_40;
  do {
    while (r4 == 0) {
      r1 = r2 + 1;
      if (SCARRY8(r2,1)) {
                    /* WARNING: Does not return */
        pc3 = (code *)SoftwareBreakpoint(1,0x1cc760);
        (*pc3)();
      }
      if ((long)(stk_48 + 0x40U >> 6) <= r1) goto LAB_001cc734;
      r2 = r1;
      r4 = *(long *)(lStack_50 + r1 * 8);
    }
    sk_h_0034cb24();
    sk_h_00355418(*(uint64_t *)(xo16 + 0x10),xo8_00,
                 *(long *)(stk_58 + 0x30) +
                 *(long *)(xo16 + 0x48) * (xo8_01 | r2 << 6),p3);
    (*xo8_02)();
    sk_h_000836a4(auStack_80,stk_68);
    sk_h_00352b74();
    sk_h_0031a14c();
    v5 = sk_h_000dbdf4();
    sk_h_00356104(v5,p3,p4);
    (*xo8_03)();
    sk_h_00351160(*(uint64_t *)(xo16 + 8));
    sk_h_00354b74();
    (*xo8_04)();
  } while (ax21 == 0);
LAB_001cc734:
  sk_free(stk_58);
  sk_swift_release(auStack_80);
  sk_h_003567d4();
  sk_rt_hook_d(*(uint64_t *)(xo8_00 + 0x58));
  return;
}



/* FUN_001cc764 @ 0x001cc764   (est. sk_r4_001cc764)
 * Ghidra: void FUN_001cc764(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc764(uint64_t p1,long p2,uint64_t p3)

{
  uint64_t *ax20;
  
  sk_r4_001cc584(p1,*ax20,*(uint64_t *)(p2 + 0x10),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8),*(uint64_t *)(p2 + 0x18));
  return;
}



/* FUN_001cc768 @ 0x001cc768   (est. sk_r4_001cc768)
 * Ghidra: void FUN_001cc768(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc768(uint64_t p1,long p2,uint64_t p3)

{
  uint64_t *ax20;
  
  sk_r4_001cc584(p1,*ax20,*(uint64_t *)(p2 + 0x10),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8),*(uint64_t *)(p2 + 0x18));
  return;
}



/* FUN_001cc790 @ 0x001cc790   (est. sk_r4_001cc790)
 * Ghidra: void FUN_001cc790(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001cc90c) */

void sk_r4_001cc790(void)

{
  uint64_t v1;
  uint64_t v2;
  long r3;
  uint64_t v4;
  uint64_t v5;
  uint64_t ix3;
  long xo8;
  uint64_t xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  code *xo9_00;
  long xo16;
  uint64_t ax20;
  long ax21;
  uint64_t ax30;
  sk_r4_u128_t av6;
  uint8_t auStack_28 [32];
  uint64_t uStack_8;
  
  sk_rt_hook_c();
  v2 = sk_h_00351a14();
  sk_h_00349b3c();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  sk_h_00348a18();
  (*datum_00658c00)();
  sk_h_0034ba68();
  r3 = sk_h_00359874();
  v1 = *(uint64_t *)(r3 + 0x20);
  sk_h_000dbcc8(r3,*(uint64_t *)(r3 + 0x18));
  sk_h_00352680(v1);
  sk_h_003509d4(auStack_28);
  (*xo9)();
  if (ax21 == 0) {
    while( true ) {
      v1 = uStack_8;
      sk_h_0034e1ec(auStack_28);
      sk_h_0031a17c(v1);
      v4 = sk_h_00350a88();
      v5 = (*xo8_01)(v4,v1);
      if ((v5 & 1) != 0) break;
      sk_h_00354c38();
      sk_h_000836a4();
      sk_h_00352b74();
      sk_h_0031a1ac();
      sk_h_0035102c();
      sk_h_00350b48();
      (*xo9_00)();
      av6 = sk_h_0035050c();
      av6 = sk_h_0031a1dc(av6.lo,av6.hi,ix3);
      sk_h_00350a04(av6.lo,av6.hi,av6.lo);
      sk_r4_001cc94c();
      sk_h_00100c38(*(uint64_t *)(xo16 + 8));
      (*xo8_02)();
    }
    sk_swift_release(auStack_28);
    sk_swift_release(v2);
    ax20 = xo8_00;
  }
  else {
    sk_masked_free(&datum_006577e0);
    sk_swift_release(v2);
  }
  sk_rt_hook_d(ax20,ax30);
  return;
}



/* FUN_001cc948 @ 0x001cc948   (est. sk_r4_001cc948)
 * Ghidra: undefined8 * thunk_FUN_0006e06c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


uint64_t * sk_r4_001cc948(void)

{
  return &datum_006577e0;  /* DAT_006577e0 — shared thunk data */
}



/* FUN_001cc94c @ 0x001cc94c   (est. sk_r4_001cc94c)
 * Ghidra: void FUN_001cc94c(undefined8 param_1,undefined8 param_2,long param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc94c(uint64_t p1,uint64_t p2,long p3)

{
  sk_r4_u128_t av1;
  
  sk_h_0008409c();
  av1 = sk_h_0031a1f4(0,*(uint64_t *)(p3 + 0x10),*(uint64_t *)(p3 + 0x18));
  sk_h_00084180(av1.lo,av1.hi,av1.lo);
  sk_h_0026aa7c();
  return;
}



/* FUN_001cc98c @ 0x001cc98c   (est. sk_r4_001cc98c)
 * Ghidra: void FUN_001cc98c(undefined8 *param_1,undefined8 param_2,long param_3,uint64_t param_4)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc98c(uint64_t *p1,uint64_t p2,long p3,uint64_t p4)

{
  uint64_t v1;
  long ax21;
  
  v1 = sk_r4_001cc790(p2,*(uint64_t *)(p3 + 0x10),
                       *(uint64_t *)((p4 & 0xfffffffffffffffe) - 8),
                       *(uint64_t *)(p3 + 0x18));
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001cc9c8 @ 0x001cc9c8   (est. sk_r4_001cc9c8)
 * Ghidra: void FUN_001cc9c8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cc9c8(void)

{
  sk_r4_u128_t av1;
  uint v2;
  uint8_t v3;
  uint8_t v4;
  long xo1;
  long xo1_00;
  long xo1_01;
  long xo1_02;
  long xo1_03;
  long xo1_04;
  uint64_t v5;
  long xo1_05;
  long xo1_06;
  uint64_t v6;
  uint64_t ix3;
  uint64_t v7;
  uint64_t xo8;
  uint64_t xo8_00;
  uint64_t xo8_01;
  uint64_t xo8_02;
  byte *pbVar8;
  byte extraout_w10;
  byte extraout_w10_00;
  byte extraout_w10_01;
  byte extraout_w10_02;
  long r9;
  long r10;
  uint64_t xo11;
  uint64_t xo11_00;
  uint64_t xo11_01;
  uint64_t xo11_02;
  uint64_t ax19;
  uint64_t ax20;
  sk_r4_u128_t av11;
  byte abStack_40 [16];
  
  av11 = sk_h_003504d0();
  v7 = av11.lo & 0xffffffffffff;
  v6 = av11.hi >> 0x38 & 0xf;
  v5 = v7;
  if ((av11.hi & 0x2000000000000000) != 0) {
    v5 = v6;
  }
  if (v5 == 0) {
LAB_001cccb8:
    sk_h_0007c1c4();
    return;
  }
  if ((ax19 >> 0x3c & 1) != 0) {
    sk_alloc_pages();
    av11 = sk_h_0007c1c4();
    sk_h_000b077c(av11.lo,av11.hi,10);
    sk_masked_free();
    goto LAB_001cccb8;
  }
  if ((ax19 >> 0x3d & 1) == 0) {
    if ((ax20 >> 0x3c & 1) == 0) {
      sk_h_0007c1c4();
      av11 = sk_h_002a9ba8();
    }
    else {
      av11.hi = v7;
      av11.lo = (ax19 & 0xfffffffffffffff) + 0x20;
    }
    if (0 < av11.hi) {
      if (*av11.lo == '+') {
        av11 = sk_h_0035a86c();
        v5 = av11.hi;
        if (-1 < av11.lo) {
          v3 = v5 <= ix3;
          v4 = ix3 == v5;
          if ((long)v5 <= (long)ix3) {
            sk_h_00348e48();
            av11 = sk_h_001e4cbc();
            if (((av11.hi != 0) && (av11.lo != 0)) &&
               (sk_h_0035437c(), xo1_03 != 0)) {
              while( true ) {
                av11 = sk_h_0034dda0();
                if ((bool)v3 && !(bool)v4) break;
                sk_h_0034af30(av11.lo,av11.hi,0);
                v5 = (uint64_t)extraout_w10_01;
                v3 = CARRY8(xo8_01,v5);
                v4 = xo8_01 + v5 == 0;
                if ((((xo11_01 & 1) != 0) || (SCARRY8(xo8_01,v5))) ||
                   (xo1_04 == 1)) break;
              }
            }
            goto LAB_001cccb8;
          }
        }
      }
      else {
        if (*av11.lo != '-') {
          r9 = 0;
          while( true ) {
            pbVar8 = av11.lo;
            v2 = *pbVar8 - 0x30;
            if (9 < v2) break;
            av1 = SEXT816(r9);
            r10 = r9 * 10;
            v5 = (uint64_t)(byte)v2;
            r9 = r10 + v5;
            if (((SUB168(av1 * SEXT816(10),8) != r10 >> 0x3f) || (SCARRY8(r10,v5))) ||
               (r10 = av11.hi + -1, av11.hi = r10, av11.lo = pbVar8 + 1,
               r10 == 0)) break;
          }
          goto LAB_001cccb8;
        }
        av11 = sk_h_0035a86c();
        v5 = av11.hi;
        if (-1 < av11.lo) {
          v3 = v5 <= ix3;
          v4 = ix3 == v5;
          if ((long)v5 <= (long)ix3) {
            sk_h_00348e48();
            av11 = sk_h_001e4cbc();
            if (((av11.hi != 0) && (av11.lo != 0)) && (sk_h_0035437c(), xo1 != 0)
               ) {
              while( true ) {
                av11 = sk_h_0034dda0();
                if ((bool)v3 && !(bool)v4) break;
                sk_h_0034af30(av11.lo,av11.hi,0);
                v5 = (uint64_t)extraout_w10;
                v3 = v5 <= xo8;
                v4 = xo8 == v5;
                if ((((xo11 & 1) != 0) || (SBORROW8(xo8,v5))) ||
                   (xo1_00 == 1)) break;
              }
            }
            goto LAB_001cccb8;
          }
        }
      }
LAB_001ccbb4:
      sk_h_003484b4();
      goto LAB_001ccbc4;
    }
  }
  else {
    sk_h_003584f8();
    if (v6 != 0) {
      v2 = (uint)ax20 & 0xff;
      if (v2 == 0x2b) {
        sk_h_00352058();
        av11 = sk_h_001d9840();
        v5 = av11.hi;
        if (-1 < av11.lo) {
          v3 = v5 <= ix3;
          v4 = ix3 == v5;
          if ((long)v5 <= (long)ix3) {
            sk_h_00348e48();
            av11 = sk_h_001e4cbc();
            if (((av11.hi != 0) && (av11.lo != 0)) &&
               (sk_h_0035437c(), xo1_05 != 0)) {
              while (sk_h_0034dda0(), !(bool)v3 || (bool)v4) {
                sk_h_0034af30();
                v5 = (uint64_t)extraout_w10_02;
                v3 = CARRY8(xo8_02,v5);
                v4 = xo8_02 + v5 == 0;
                if ((((xo11_02 & 1) != 0) || (SCARRY8(xo8_02,v5))) ||
                   (xo1_06 == 1)) break;
              }
            }
            goto LAB_001cccb8;
          }
        }
      }
      else {
        if (v2 != 0x2d) {
          r9 = 0;
          pbVar8 = abStack_40;
          while( true ) {
            if (9 < *pbVar8 - 0x30) break;
            av11 = SEXT816(r9);
            r10 = r9 * 10;
            v5 = (uint64_t)(byte)(*pbVar8 - 0x30);
            r9 = r10 + v5;
            if (((SUB168(av11 * SEXT816(10),8) != r10 >> 0x3f) || (SCARRY8(r10,v5))) ||
               (v6 = v6 - 1, pbVar8 = pbVar8 + 1, v6 == 0)) break;
          }
          goto LAB_001cccb8;
        }
        sk_h_00352058();
        av11 = sk_h_001d9840();
        v5 = av11.hi;
        if (-1 < av11.lo) {
          v3 = v5 <= ix3;
          v4 = ix3 == v5;
          if ((long)v5 <= (long)ix3) {
            sk_h_00348e48();
            av11 = sk_h_001e4cbc();
            if (((av11.hi != 0) && (av11.lo != 0)) &&
               (sk_h_0035437c(), xo1_01 != 0)) {
              while (sk_h_0034dda0(), !(bool)v3 || (bool)v4) {
                sk_h_0034af30();
                v5 = (uint64_t)extraout_w10_00;
                v3 = v5 <= xo8_00;
                v4 = xo8_00 == v5;
                if ((((xo11_00 & 1) != 0) || (SBORROW8(xo8_00,v5))) ||
                   (xo1_02 == 1)) break;
              }
            }
            goto LAB_001cccb8;
          }
        }
      }
      goto LAB_001ccbb4;
    }
  }
  sk_h_0034daa8();
  sk_h_00348160();
LAB_001ccbc4:
  sk_h_003524c8();
                    /* WARNING: Subroutine does not return */
  sk_h_001afe4c();
}



/* FUN_001ccd1c @ 0x001ccd1c   (est. sk_r4_001ccd1c)
 * Ghidra: void FUN_001ccd1c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ccd1c(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4)

{
  uint8_t zf;
  int iVar1;
  uint64_t v2;
  bool bVar3;
  long xo8;
  long xo8_00;
  long xo8_01;
  long xo8_02;
  long xo8_03;
  code *xo8_04;
  code *xo8_05;
  code *xo9;
  code *xo9_00;
  uint64_t xo13;
  long xo16;
  long xo16_00;
  long xo16_01;
  code *pc4;
  uint64_t ax21;
  uint64_t ax24;
  uint64_t ax30;
  sk_r4_u128_t av5;
  
  sk_cpu();
  sk_h_00357688();
  sk_h_003537d4();
  sk_rt_dispatch();
  sk_h_0034ee68();
  sk_rt_dispatch();
  sk_h_000a6f88();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  sk_h_00348a18();
  (*datum_00658c00)();
  sk_h_0034b3d8();
  sk_h_003499f0();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_003489c0();
  (*datum_00658c00)();
  sk_h_0034ba78();
  (*datum_00658c00)();
  sk_h_0034b8bc();
  sk_h_003494e8();
  (*datum_00658c00)(*(uint64_t *)(xo8_01 + 0x40));
  sk_h_0034ab10();
  sk_h_00352008();
  (*datum_00658c00)();
  sk_h_00350ec0();
  (*datum_00658c00)();
  sk_h_0034bc6c();
  sk_h_0034f21c(ax21 & 0xffffffffffff);
  if (xo8_02 == 0) {
    sk_masked_free();
    bVar3 = true;
  }
  else {
    (*datum_00658c00)();
    sk_h_003539e4();
    *(uint64_t *)(xo8_03 + -0x20) = p3;
    *(uint64_t *)(xo8_03 + -0x18) = p4;
    *(uint64_t *)(xo8_03 + -0x10) = 10;
    sk_h_00352b68(sk_h_0031a20c);
    sk_h_002b2078();
    sk_h_00356200();
    sk_h_0034f444();
    (*xo9)();
    sk_h_0034b2c8();
    if ((bool)zf) {
      sk_h_000f5e08();
      sk_h_003540ac();
      sk_h_0022d1b4(&stack0xfffffffffffffff0,10);
      sk_masked_free();
      sk_h_00100c38(*(uint64_t *)(xo16 + 8));
      (*xo8_04)();
      pc4 = *(code **)(xo16_00 + 0x20);
    }
    else {
      sk_masked_free();
      pc4 = *(code **)(xo16_00 + 0x20);
      sk_h_003511a8();
      (*pc4)();
    }
    sk_h_00350058();
    (*pc4)();
    sk_h_00349f3c();
    if (!(bool)zf) {
      pc4 = *(code **)(xo16_01 + 0x20);
      sk_h_00351554(xo13);
      (*pc4)();
      sk_h_0034cf94();
      (*pc4)();
      sk_h_00350c68(ax24);
      (*pc4)();
    }
    else {
      sk_h_0035a578();
      sk_h_003508b4();
      (*xo9_00)();
    }
    bVar3 = (bool)zf;
  }
  sk_h_00350774(ax24,bVar3);
  sk_h_000839d8();
  sk_h_00351390(ax24);
  iVar1 = sk_h_000839f8();
  if (iVar1 == 0) {
    pc4 = *(code **)(xo16_01 + 0x20);
    av5 = sk_h_00350470();
    (*pc4)(av5.lo,av5.hi,p3);
    av5 = sk_h_0008e388();
    v2 = (*pc4)(av5.lo,av5.hi,p3);
  }
  else {
    sk_h_00351384(*(uint64_t *)(xo16_00 + 8));
    v2 = (*xo8_05)();
  }
  sk_h_0034dba8(v2,iVar1 != 0);
  sk_h_000839d8();
  sk_h_0008e500(ax30);
  return;
}



/* FUN_001cd0b8 @ 0x001cd0b8   (est. sk_r4_001cd0b8)
 * Ghidra: void FUN_001cd0b8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd0b8(void)

{
  uint8_t zf;
  long xo8;
  uint64_t ax20;
  uint64_t ax21;
  sk_r4_u128_t av1;
  
  sk_masked_free(0xe000000000000000);
  sk_h_00353820();
  sk_h_002364dc();
  sk_h_00354e0c();
  sk_masked_free(0xe000000000000000);
  sk_rt_hook_u();
  if ((xo8 == 0) && (((ax21 & (ax20 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
    sk_masked_free();
  }
  else {
    if ((ax20 >> 0x3d & 1) != 0) {
      av1 = sk_rt_hook_m();
      sk_rt_slot2(av1.lo,av1.hi,0,0xe000000000000000);
      if (!(bool)zf) {
        sk_h_000b43e8();
        sk_masked_free();
        goto LAB_001cd14c;
      }
    }
    sk_h_00353ad8();
  }
LAB_001cd14c:
  sk_rt_hook_y();
  return;
}



/* FUN_001cd168 @ 0x001cd168   (est. sk_r4_001cd168)
 * Ghidra: void FUN_001cd168(long param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd168(long p1)

{
  uint8_t iw3;
  
  sk_r4_001cc9c8();
  sk_h_00359c4c();
  *(uint8_t *)(p1 + 0x18) = iw3;
  return;
}



/* FUN_001cd194 @ 0x001cd194   (est. sk_r4_001cd194)
 * Ghidra: void FUN_001cd194(long param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd194(long p1)

{
  sk_r4_001cd0b8();
  sk_h_00359c4c();
  *(uint8_t *)(p1 + 0x18) = 0;
  return;
}



/* FUN_001cd1e0 @ 0x001cd1e0   (est. sk_r4_001cd1e0)
 * Ghidra: void FUN_001cd1e0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined1 param_4)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd1e0(uint64_t p1,uint64_t p2,uint64_t p3,uint8_t p4)

{
  long r1;
  uint64_t xo1;
  uint64_t v2;
  long xo8;
  code *xo9;
  long xo16;
  uint64_t ax20;
  long *ax22;
  uint64_t arg;
  uint64_t arg;
  
  sk_h_00357cb4();
  v2 = p3;
  sk_h_003515f0();
  sk_h_0007b384(v2);
  sk_h_00355d40();
  sk_h_00084180();
  (*xo9)();
  sk_r4_001cc9c8(arg,arg);
  sk_h_00351a50();
  sk_h_00349e54();
  ax22[3] = xo8;
  ax22[4] = xo16;
  sk_h_0034f8a8();
  r1 = sk_h_0036a940();
  *ax22 = r1;
  *(uint64_t *)(r1 + 0x10) = p3;
  *(uint64_t *)(r1 + 0x18) = ax20;
  *(uint64_t *)(r1 + 0x20) = v2;
  *(uint8_t *)(r1 + 0x28) = p4;
  sk_h_00357c74(xo1);
  return;
}



/* FUN_001cd260 @ 0x001cd260   (est. sk_r4_001cd260)
 * Ghidra: void FUN_001cd260(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd260(void)

{
  int iVar1;
  uint64_t xo8;
  long xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  long xo16;
  long xo16_00;
  long xo16_01;
  code *pc2;
  uint64_t ax30;
  sk_r4_u128_t av3;
  sk_r4_u128_t stk_10;
  
  sk_cpu();
  sk_h_00355ff4();
  sk_h_003504d0();
  sk_rt_dispatch(0);
  sk_h_000a6f88();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_0034aee4();
  sk_h_003494e8();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_0034a1f8();
  sk_h_000a6bb8();
  sk_h_00350a7c();
  av3 = (*xo8_01)();
  sk_rt_hook_r();
  (**(code **)(xo16_01 + 8))();
  stk_10 = av3;
  sk_h_0031bc70();
  sk_h_00350c20(stk_10);
  (*xo9)();
  sk_h_00351390();
  iVar1 = sk_h_000839f8();
  if (iVar1 == 0) {
    pc2 = *(code **)(xo16_00 + 0x20);
    sk_h_00350c68();
    (*pc2)();
    sk_h_0034b778();
    (*pc2)();
  }
  else {
    sk_h_00358e00(*(uint64_t *)(xo16 + 8));
    (*xo8_02)();
  }
  sk_h_00350774(xo8,iVar1 != 0);
  sk_h_000839d8();
  sk_h_0008e500(ax30);
  return;
}



/* FUN_001cd3fc @ 0x001cd3fc   (est. sk_r4_001cd3fc)
 * Ghidra: void FUN_001cd3fc(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd3fc(uint64_t p1,uint64_t p2,uint64_t p3)

{
  long r1;
  uint64_t v2;
  long xo8;
  code *xo9;
  long xo16;
  uint64_t ax20;
  long *ax22;
  uint64_t stk_38;
  
  v2 = p3;
  sk_h_003515f0();
  sk_h_0007b384(v2);
  sk_h_00351660();
  sk_h_00084180();
  (*xo9)();
  sk_r4_001cd0b8(stk_38);
  sk_h_00351a50();
  sk_h_00349e54();
  ax22[3] = xo8;
  ax22[4] = xo16;
  sk_h_0034f8a8();
  r1 = sk_h_0036a940();
  *ax22 = r1;
  *(uint64_t *)(r1 + 0x10) = p3;
  *(uint64_t *)(r1 + 0x18) = ax20;
  *(uint64_t *)(r1 + 0x20) = v2;
  *(uint8_t *)(r1 + 0x28) = 0;
  return;
}



/* FUN_001cd478 @ 0x001cd478   (est. sk_r4_001cd478)
 * Ghidra: void FUN_001cd478(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd478(void)

{
  int iVar1;
  uint64_t v2;
  uint64_t v3;
  uint64_t ix4;
  uint64_t ix5;
  long xo8;
  code *xo8_00;
  code *xo8_01;
  code *xo9;
  long xo16;
  long xo16_00;
  long xo16_01;
  code *pc4;
  uint64_t ax30;
  uint8_t av5 [12];
  uint64_t stk_8;
  
  sk_cpu();
  sk_h_003504d0();
  sk_rt_dispatch(0);
  sk_h_00348ce8();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_0034aee4();
  sk_h_003494e8();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  sk_h_0034947c();
  sk_h_003198fc(ix5);
  sk_h_0034eef8();
  av5 = (*xo8_00)();
  sk_h_0034dfe4();
  v2 = (**(code **)(xo16_01 + 8))();
  if ((av5._8_4_ & 0xff) != 1) {
    stk_8 = av5.lo;
    sk_h_0031bc70(ix4);
    sk_h_00350c20(&stk_8);
    (*xo9)();
    sk_h_00351390();
    iVar1 = sk_h_000839f8();
    if (iVar1 == 0) {
      pc4 = *(code **)(xo16_00 + 0x20);
      sk_h_00350ab8();
      (*pc4)();
      sk_h_0035512c();
      sk_h_00351298();
      v2 = (*pc4)();
      v3 = 0;
      goto LAB_001cd5c0;
    }
    sk_h_0035084c(*(uint64_t *)(xo16 + 8));
    v2 = (*xo8_01)();
  }
  v3 = 1;
LAB_001cd5c0:
  sk_h_0034dba8(v2,v3);
  sk_h_000839d8();
  sk_h_0008e500(ax30);
  return;
}



/* FUN_001cd618 @ 0x001cd618   (est. sk_r4_001cd618)
 * Ghidra: void FUN_001cd618(long *param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd618(long *p1,uint64_t p2,uint64_t p3,uint64_t p4)

{
  long r1;
  long xo8;
  long xo16;
  uint64_t ax20;
  uint64_t ax21;
  
  sk_r4_001cd0b8();
  sk_h_00350b90();
  sk_h_00349e54();
  p1[3] = xo8;
  p1[4] = xo16;
  sk_h_0034f8a8();
  r1 = sk_h_0036a940();
  *p1 = r1;
  *(uint64_t *)(r1 + 0x10) = ax20;
  *(uint64_t *)(r1 + 0x18) = ax21;
  *(uint64_t *)(r1 + 0x20) = p4;
  *(uint8_t *)(r1 + 0x28) = 0;
  return;
}



/* FUN_001cd66c @ 0x001cd66c   (est. sk_r4_001cd66c)
 * Ghidra: undefined1  [16] FUN_001cd66c(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


sk_r4_u128_t sk_r4_001cd66c(uint64_t p1,uint64_t p2,uint64_t p3)

{
  code *xo8;
  long xo16;
  sk_r4_u128_t av1;
  
  sk_h_0034c034();
  sk_h_003198fc(p3);
  sk_h_0034bcf0();
  av1 = (*xo8)();
  sk_h_0034b3c8();
  (**(code **)(xo16 + 8))();
  return av1;
}



/* FUN_001cd6e0 @ 0x001cd6e0   (est. sk_r4_001cd6e0)
 * Ghidra: void FUN_001cd6e0(undefined8 *param_1)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd6e0(uint64_t *p1)

{
  uint64_t v1;
  uint8_t extraout_w1;
  
  v1 = sk_r4_001cd66c();
  *p1 = v1;
  *(uint8_t *)(p1 + 1) = extraout_w1;
  return;
}



/* FUN_001cd70c @ 0x001cd70c   (est. sk_r4_001cd70c)
 * Ghidra: void FUN_001cd70c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined1 param_4)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd70c(uint64_t p1,uint64_t p2,uint64_t p3,uint8_t p4)

{
  long r1;
  uint64_t xo1;
  long xo8;
  long xo16;
  uint64_t ax19;
  uint64_t ax20;
  long *ax21;
  
  sk_h_003503d0();
  sk_alloc_pages(xo1);
  sk_h_0007c1c4();
  sk_r4_001cc9c8();
  sk_h_00351a50();
  sk_h_00349e54();
  ax21[3] = xo8;
  ax21[4] = xo16;
  sk_h_0034f8a8();
  r1 = sk_h_0036a940();
  *ax21 = r1;
  *(uint64_t *)(r1 + 0x10) = ax19;
  *(uint64_t *)(r1 + 0x18) = ax20;
  *(uint64_t *)(r1 + 0x20) = p3;
  *(uint8_t *)(r1 + 0x28) = p4;
  return;
}



/* FUN_001cd778 @ 0x001cd778   (est. sk_r4_001cd778)
 * Ghidra: void FUN_001cd778(undefined8 param_1,undefined8 param_2,undefined8 param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd778(uint64_t p1,uint64_t p2,uint64_t p3)

{
  code *xo8;
  long xo16;
  
  sk_h_0034c034();
  sk_h_000a6bb8(p3);
  sk_h_0034bcf0();
  (*xo8)();
  sk_h_00353918();
  sk_h_0034b3c8();
  (**(code **)(xo16 + 8))();
  sk_h_003504ac();
  return;
}



/* FUN_001cd7e4 @ 0x001cd7e4   (est. sk_r4_001cd7e4)
 * Ghidra: void FUN_001cd7e4(undefined1 (*param_1) [16])
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cd7e4(uint8_t (*p1) [16])

{
  sk_r4_u128_t av1;
  
  av1 = sk_r4_001cd778();
  *p1 = av1;
  return;
}



/* FUN_001cd80c @ 0x001cd80c   (est. sk_r4_001cd80c)
 * Ghidra: void FUN_001cd80c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001ce550) */

void sk_r4_001cd80c(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,
                 uint64_t p5,uint64_t p6,uint64_t p7)

{
  long r1;
  long r2;
  uint64_t v3;
  int iVar4;
  uint8_t v5;
  code *pc6;
  uint8_t v7;
  long r8;
  uint64_t v9;
  long r10;
  uint64_t v11;
  uint64_t v12;
  uint64_t v13;
  uint64_t v14;
  uint8_t extraout_w1;
  uint64_t xo1;
  uint64_t xo1_00;
  uint64_t v15;
  uint64_t xo1_01;
  uint64_t xo1_02;
  uint64_t xo1_03;
  uint64_t xo1_04;
  uint64_t xo1_05;
  uint64_t xo1_06;
  long xo8;
  uint64_t xo8_00;
  long xo8_01;
  long xo8_02;
  long xo8_03;
  code *xo8_04;
  code *xo8_05;
  long xo8_06;
  code *xo8_07;
  code *xo8_08;
  code *xo8_09;
  code *xo8_10;
  code *xo8_11;
  code *xo8_12;
  long xo8_13;
  code *xo8_14;
  code *xo8_15;
  code *xo8_16;
  code *xo8_17;
  code *xo8_18;
  code *xo8_19;
  code *xo8_20;
  code *xo8_21;
  long xo8_22;
  code *xo8_23;
  code *xo8_24;
  code *xo8_25;
  code *xo8_26;
  code *xo8_27;
  code *xo8_28;
  code *xo8_29;
  code *xo8_30;
  code *xo8_31;
  code *xo8_32;
  code *xo8_33;
  uint64_t xo9;
  uint64_t xo9_00;
  long xo9_01;
  long xo9_02;
  long xo9_03;
  long xo9_04;
  long xo9_05;
  long xo9_06;
  long xo9_07;
  code *xo9_08;
  code *xo9_09;
  long xo9_10;
  code *xo9_11;
  code *xo9_12;
  long xo9_13;
  code *xo9_14;
  long xo10;
  long xo10_00;
  long xo13;
  long xo14;
  long xo15;
  long xo16;
  long xo16_00;
  long ax21;
  uint64_t ax23;
  long ax24;
  uint64_t v16;
  long ax25;
  uint64_t v17;
  long ax28;
  uint64_t ax30;
  sk_r4_u128_t av18;
  uint64_t stk_238;
  long stk_220;
  uint64_t stk_198 [2];
  uint64_t stk_188;
  uint8_t stk_180;
  sk_r4_u128_t stk_170;
  uint64_t stk_160;
  uint8_t stk_158;
  undefined7 uStack_157;
  uint64_t uStack_150;
  uint8_t auStack_148 [40];
  uint8_t stk_120 [8];
  long lStack_118;
  uint64_t stk_110;
  long lStack_108;
  long stk_100;
  uint8_t auStack_f8 [40];
  long stk_d0;
  long lStack_c8;
  long stk_c0;
  uint64_t uStack_b8;
  long stk_b0;
  uint8_t auStack_a8 [40];
  uint8_t stk_80 [8];
  long lStack_78;
  uint64_t stk_70;
  long lStack_68;
  long stk_60;
  uint8_t auStack_58 [48];
  long lStack_28;
  uint64_t stk_20;
  long lStack_18;
  uint64_t stk_10;
  
  sk_rt_hook_c();
  av18 = sk_h_00359b18();
  r8 = av18.lo;
  sk_h_00349720();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  sk_h_003489c0();
  (*datum_00658c00)();
  sk_h_00350464();
  sk_h_00349a68();
  (*datum_00658c00)(*(uint64_t *)(xo8_01 + 0x40));
  sk_h_003493c4();
  sk_h_003503f8();
  (*datum_00658c00)();
  sk_h_00350434();
  sk_h_003503f8();
  (*datum_00658c00)();
  sk_h_00350434();
  sk_h_003503f8();
  (*datum_00658c00)();
  sk_h_0034b758();
  v9 = sk_h_0035361c();
  sk_h_003722e4(v9,p3);
  sk_h_0034f554();
  v9 = sk_rt_dispatch();
  sk_h_000a6f88();
  (*datum_00658c00)(*(uint64_t *)(xo8_02 + 0x40));
  sk_h_003493c4();
  sk_h_003503f8();
  (*datum_00658c00)();
  sk_h_00350ec0();
  (*datum_00658c00)();
  sk_h_00352008();
  (*datum_00658c00)();
  sk_h_00350434();
  sk_h_003503f8();
  (*datum_00658c00)();
  sk_h_00350434();
  sk_h_003503f8();
  (*datum_00658c00)();
  sk_h_00350434();
  sk_h_003503f8();
  (*datum_00658c00)();
  sk_h_0034bd30();
  (*datum_00658c00)();
  sk_h_00358268();
  sk_h_00352cb0();
  v7 = ax25 == xo8_03;
  if ((bool)v7) {
    r10 = *(long *)(r8 + 0x18);
    sk_h_0034ad20(r8);
    sk_h_0006a4f0();
    sk_h_00349150();
    sk_h_00352e6c();
    stk_238 = (*xo8_11)();
    stk_198[0] = stk_238;
    sk_h_001fca54(auStack_148,av18.hi);
    sk_h_001f6b30(stk_120,auStack_148,0x6753a0);
    sk_h_00359d38(stk_110);
    sk_alloc_pages(av18.hi);
    r8 = lStack_108;
    r1 = stk_100;
joined_r0x001cde38:
    do {
      if (r1 == 0) {
        r2 = r8 + 1;
        if (SCARRY8(r8,1)) {
                    /* WARNING: Does not return */
          pc6 = (code *)SoftwareBreakpoint(1,0x1ce57c);
          (*pc6)();
        }
        v7 = r2 == r10;
        if (r2 < r10) {
          r8 = r2;
          r1 = *(long *)(lStack_118 + r2 * 8);
          goto joined_r0x001cde38;
        }
        sk_h_00359760();
        v11 = xo1_03;
      }
      else {
        sk_h_0034f884(r8);
        sk_h_00350cf4(*(uint64_t *)(xo9_10 + 0x30));
        sk_h_003540ac(ax21);
        (*xo8_12)();
        sk_h_00352038((long)*(int *)(ax24 + 0x30));
        (*xo9_11)(xo16_00 + 0x10,ax21 + xo8_13,xo1_02,ax28
                         );
        v11 = 0;
      }
      sk_h_00355be8(ax21,v11);
      sk_h_000839d8();
      sk_h_003596f8();
      av18 = sk_h_00350518();
      (*xo8_14)(av18.lo,av18.hi,v9);
      sk_h_0035163c(xo9_06);
      sk_h_00350884();
      stk_220 = xo9_10;
      if ((bool)v7) break;
      (**(code **)(xo16_00 + 0x20))
                (ax23,xo9_06 + *(int *)(ax24 + 0x30),ax28);
      sk_h_0035972c();
      sk_h_00353cf0();
      v11 = 0x6753a0;
      v15 = v11;
      (*xo8_15)();
      sk_h_00351494(stk_170);
      sk_h_00365b6c();
      v5 = (char)v11;
      av18 = sk_r4_001cc9c8(stk_170.lo,stk_170.hi);
      stk_158 = v5;
      stk_160 = v15;
      stk_170 = av18;
      v11 = sk_h_00356e84();
      sk_h_001bdb28(ax23,stk_170,v11,ax28,p7);
      sk_h_003504c4(*(uint64_t *)(xo16_00 + 8));
      (*xo8_16)();
      sk_masked_free(av18.hi);
    } while (ax21 == 0);
LAB_001ce4e8:
    sk_free(stk_238);
  }
  else {
    v7 = ax25 == 0x677880;
    if ((bool)v7) {
      sk_h_0034b440(r8);
      sk_h_0006a4f0();
      sk_h_00349150();
      sk_h_00351978();
      stk_238 = (*xo8_17)();
      stk_198[0] = stk_238;
      sk_h_00352cf8(auStack_f8);
      sk_h_001fca54();
      sk_h_0035041c();
      sk_h_001f6b30(&stk_d0,auStack_f8,xo1_04,ax28,p6);
      v16 = stk_c0 + 0x40U >> 6;
      stk_220 = stk_d0;
      sk_alloc_pages(r8);
      v17 = uStack_b8;
      r8 = stk_b0;
joined_r0x001ce080:
      while (r8 == 0) {
        v3 = v17 + 1;
        if (SCARRY8(v17,1)) {
                    /* WARNING: Does not return */
          pc6 = (code *)SoftwareBreakpoint(1,0x1ce584);
          (*pc6)();
        }
        v7 = v3 == v16;
        if ((long)v16 <= (long)v3) {
          sk_h_00359760();
          v11 = xo1_05;
          goto LAB_001ce10c;
        }
        v17 = v3;
        r8 = *(long *)(lStack_c8 + v3 * 8);
      }
      sk_h_0034f884(v17);
      sk_h_00350cf4(*(uint64_t *)(stk_d0 + 0x30));
      sk_h_003516fc(xo9_04);
      (*xo8_18)();
      (**(code **)(xo16_00 + 0x10))
                (xo16_00 + 0x10,xo9_04 + *(int *)(ax24 + 0x30),
                 *(long *)(stk_d0 + 0x38) + *(long *)(xo16_00 + 0x48) * xo9_01,
                 ax28);
      v11 = 0;
LAB_001ce10c:
      sk_h_000839d8(xo9_04,v11,1,ax24);
      av18 = sk_h_000a6e14(*(uint64_t *)(xo15 + 0x20));
      (*xo8_19)(av18.lo,av18.hi,v9);
      av18 = sk_h_00351738();
      sk_h_00350884(av18.lo,av18.hi,ax24);
      if ((bool)v7) goto LAB_001ce4e8;
      (**(code **)(xo16_00 + 0x20))
                (xo9_01,xo9_05 + *(int *)(ax24 + 0x30),ax28);
      v11 = 0x677880;
      (**(code **)(xo16 + 0x20))(xo8_00,xo9_05);
      sk_h_000dbe70(stk_170);
      sk_h_00365b6c();
      av18 = sk_r4_001cd0b8(stk_170.lo);
      stk_158 = 0;
      stk_160 = v11;
      stk_170 = av18;
      v11 = sk_h_00356e84();
      sk_h_001bdb28(xo9_01,stk_170,v11,ax28,p7);
      if (ax21 == 0) {
        sk_h_003596c4();
        sk_h_000a6e14();
        (*xo8_20)();
        sk_masked_free(av18.hi);
        goto joined_r0x001ce080;
      }
      sk_h_003596c4();
      sk_h_000a6e14();
      (*xo8_31)();
      sk_masked_free(av18.hi);
      goto LAB_001ce4e8;
    }
    r10 = sk_h_0008dae4();
    if (r10 == 0) {
      sk_h_0034b440(r8);
      sk_h_00352680();
      sk_h_00350470(stk_170);
      (*xo9_12)();
      sk_h_00352cf8(auStack_58);
      sk_h_001fca54();
      sk_h_0035780c();
      sk_h_001f6b30();
      sk_h_00358984(stk_20);
      sk_alloc_pages(r8);
      v17 = stk_10;
      r8 = lStack_18;
joined_r0x001ce2d8:
      while (v17 == 0) {
        r10 = r8 + 1;
        if (SCARRY8(r8,1)) {
                    /* WARNING: Does not return */
          pc6 = (code *)SoftwareBreakpoint(1,0x1ce588);
          (*pc6)();
        }
        v7 = r10 == xo16_00;
        if (xo16_00 <= r10) {
          v17 = 0;
          v11 = 1;
          goto LAB_001ce360;
        }
        r8 = r10;
        v17 = *(uint64_t *)(lStack_28 + r10 * 8);
      }
      v17 = v17 - 1 & v17;
      sk_h_00350cf4(*(uint64_t *)(xo10_00 + 0x30));
      sk_h_00358dd0();
      (*xo8_21)();
      sk_h_00352038((long)*(int *)(ax24 + 0x30));
      (*xo9_14)(xo16_00 + 0x10,xo9_02 + xo8_22,xo1_06,
                        ax28);
      v11 = 0;
LAB_001ce360:
      sk_h_00352480(xo9_02,v11);
      sk_h_000839d8();
      av18 = sk_h_000e72b0(*(uint64_t *)(xo15 + 0x20));
      (*xo8_23)(av18.lo,av18.hi,v9);
      sk_h_0034b2c8(xo14);
      if ((bool)v7) {
        sk_free(xo10_00);
        goto LAB_001ce56c;
      }
      iVar4 = *(int *)(ax24 + 0x30);
      av18 = sk_h_003511a8(*(uint64_t *)(xo9_13 + 0x20));
      (*xo8_24)(av18.lo,av18.hi,ax25);
      sk_h_0035972c();
      (*xo8_25)(xo9,xo14 + iVar4,ax28);
      v15 = uStack_150;
      v11 = CONCAT71(uStack_157,stk_158);
      sk_h_000836a4(stk_170,v11);
      sk_h_00351a44();
      sk_h_0031a14c();
      av18 = sk_h_0034b8cc();
      (*xo8_26)(av18.lo,av18.hi,p5,v11,v15);
      if (ax21 == 0) {
        sk_h_003596c4();
        sk_h_003507c8();
        (*xo8_27)();
        sk_h_000836a4(stk_170,CONCAT71(uStack_157,stk_158));
        sk_h_003515a8();
        v11 = sk_h_0031a14c();
        av18 = sk_h_003504c4(v11);
        sk_h_003527e0(av18.lo,av18.hi,p7);
        (*xo8_28)();
        sk_h_003596f8();
        sk_h_003504c4();
        (*xo8_29)();
        goto joined_r0x001ce2d8;
      }
      sk_free(xo10_00);
      sk_h_003596f8();
      (*xo8_32)(xo9,ax28);
      sk_h_003596c4();
      sk_h_003507c8();
      (*xo8_33)();
LAB_001ce56c:
      sk_swift_release(stk_170);
      goto LAB_001ce4f8;
    }
    sk_h_0034b440(r8);
    sk_h_0006a4f0();
    sk_h_00349150();
    sk_h_00351978();
    v11 = (*xo8_04)();
    sk_h_00352cf8(auStack_a8);
    sk_h_001fca54();
    sk_h_001f6b30(stk_80,auStack_a8);
    sk_h_00357540(stk_70);
    sk_alloc_pages(r8);
    r8 = lStack_68;
    r10 = stk_60;
joined_r0x001cdb44:
    while (r10 == 0) {
      r1 = r8 + 1;
      if (SCARRY8(r8,1)) {
                    /* WARNING: Does not return */
        pc6 = (code *)SoftwareBreakpoint(1,0x1ce580);
        (*pc6)();
      }
      v7 = r1 == ax28;
      if (ax28 <= r1) {
        sk_h_00359760();
        v15 = xo1_01;
        goto LAB_001cdbd8;
      }
      r8 = r1;
      r10 = *(long *)(lStack_78 + r1 * 8);
    }
    sk_h_0034f884(r8);
    sk_h_00350cf4(*(uint64_t *)(xo10 + 0x30));
    (*xo8_05)(xo13,xo1,ax25);
    sk_h_00352038((long)*(int *)(ax24 + 0x30));
    (*xo9_08)(xo9_07 + 0x10,xo13 + xo8_06,xo1_00,ax28);
    v15 = 0;
LAB_001cdbd8:
    sk_h_000839d8(xo13,v15,1,ax24);
    (**(code **)(xo15 + 0x20))(xo9_03,xo13,v9);
    av18 = sk_h_003517a8();
    sk_h_00350884(av18.lo,av18.hi,ax24);
    if ((bool)v7) goto LAB_001ce4bc;
    (**(code **)(xo9_07 + 0x20))
              (xo9_00,xo9_03 + *(int *)(ax24 + 0x30),ax28);
    av18 = sk_h_003524a4(*(uint64_t *)(xo16 + 0x20));
    (*xo8_07)(av18.lo,av18.hi,ax25);
    sk_rt_desc(0x656128,&datum_004e7f80);
    sk_h_00350ed0(stk_198);
    sk_h_00365b6c();
    sk_h_0034b440(stk_198);
    sk_h_0008e5d8();
    sk_h_00350470(stk_170);
    (*xo9_09)();
    sk_swift_release(stk_198);
    v14 = uStack_150;
    v15 = CONCAT71(uStack_157,stk_158);
    sk_h_0034b440(stk_170);
    sk_h_000a6bb8();
    sk_rt_hook_x();
    (*xo8_08)();
    sk_h_003562d4();
    v13 = uStack_150;
    sk_h_0034f1a8(stk_170,CONCAT71(uStack_157,stk_158));
    sk_h_003198fc();
    v12 = sk_h_00350648();
    v13 = (*xo8_09)(v12,v13);
    sk_swift_release(stk_170);
    stk_198[0] = v14;
    stk_188 = v13;
    stk_180 = extraout_w1;
    v14 = sk_h_00356e84();
    sk_h_001bdb28(xo9_00,stk_198,v14,ax28,p7);
    if (ax21 == 0) {
      sk_h_0035972c();
      sk_h_00351360();
      (*xo8_10)();
      sk_masked_free(v15);
      goto joined_r0x001cdb44;
    }
    sk_h_0035972c();
    sk_h_00351360();
    (*xo8_30)();
    sk_masked_free(v15);
LAB_001ce4bc:
    sk_free(v11);
    stk_220 = xo10;
  }
  sk_free(stk_220);
LAB_001ce4f8:
  sk_rt_hook_d(ax30);
  return;
}



/* FUN_001ce58c @ 0x001ce58c   (est. sk_r4_001ce58c)
 * Ghidra: void FUN_001ce58c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ce58c(void)

{
  long r1;
  uint64_t v2;
  code *pc3;
  long r4;
  long r5;
  long xo8;
  long xo8_00;
  uint64_t xo9;
  uint64_t xo10;
  uint64_t xo11;
  long xo16;
  long r6;
  uint64_t *ax20;
  long r7;
  uint64_t v8;
  uint64_t v9;
  uint64_t v10;
  long extraout_d0;
  uint64_t v11;
  sk_r4_u128_t av12;
  
  av12 = sk_h_00077698();
  r4 = av12.lo;
  v11 = ax20[1];
  v10 = *ax20;
  r1 = ax20[2];
  r7 = ax20[3];
  if (ax20[4] == 0) {
    r5 = r7;
    do {
      r7 = r5 + 1;
      if (SCARRY8(r5,1)) {
                    /* WARNING: Does not return */
        pc3 = (code *)SoftwareBreakpoint(1,0x1ce6d4);
        (*pc3)();
      }
      if ((long)(r1 + 0x40U >> 6) <= r7) {
        sk_h_00352048(r4,*(uint64_t *)(r4 + 0x10),*(uint64_t *)(r4 + 0x18));
        sk_h_003722e4();
        sk_h_0034b690();
        sk_h_000839d8();
        v8 = 0;
        goto LAB_001ce68c;
      }
      r5 = r5 + 1;
    } while (*(long *)(ax20[1] + r7 * 8) == 0);
  }
  r4 = sk_h_0034f264(r7);
  v8 = xo11 & xo9;
  v9 = xo10 | xo8_00 << 6;
  v2 = *(uint64_t *)(r4 + 0x10);
  r4 = *(long *)(r4 + 0x18);
  sk_h_003511e4();
  (**(code **)(xo16 + 0x10))
            (xo8,*(long *)(extraout_d0 + 0x30) + *(long *)(xo16 + 0x48) * v9,
             v2);
  sk_h_0034d1b0();
  r5 = sk_h_003722e4();
  r6 = *(long *)(r4 + -8);
  (**(code **)(r6 + 0x10))
            (xo8 + *(int *)(r5 + 0x30),
             *(long *)(extraout_d0 + 0x38) + *(long *)(r6 + 0x48) * v9,r4);
  sk_h_0034aed0();
  sk_h_000839d8();
  r5 = r7;
LAB_001ce68c:
  ax20[1] = v11;
  *ax20 = v10;
  ax20[2] = r1;
  ax20[3] = r5;
  ax20[4] = v8;
  sk_h_0007767c(av12.hi);
  return;
}



/* FUN_001ce6d4 @ 0x001ce6d4   (est. sk_r4_001ce6d4)
 * Ghidra: void FUN_001ce6d4(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ce6d4(uint64_t p1,long p2,uint64_t p3)

{
  uint64_t *ax20;
  
  sk_r4_001cd80c(p1,*ax20,*(uint64_t *)(p2 + 0x10),*(uint64_t *)(p2 + 0x18),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8),*(uint64_t *)(p2 + 0x20),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 0x10));
  return;
}



/* FUN_001ce6d8 @ 0x001ce6d8   (est. sk_r4_001ce6d8)
 * Ghidra: void FUN_001ce6d8(undefined8 param_1,long param_2,uint64_t param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001ce6d8(uint64_t p1,long p2,uint64_t p3)

{
  uint64_t *ax20;
  
  sk_r4_001cd80c(p1,*ax20,*(uint64_t *)(p2 + 0x10),*(uint64_t *)(p2 + 0x18),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 8),*(uint64_t *)(p2 + 0x20),
               *(uint64_t *)((p3 & 0xfffffffffffffffe) - 0x10));
  return;
}



/* FUN_001ce704 @ 0x001ce704   (est. sk_r4_001ce704)
 * Ghidra: void FUN_001ce704(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


/* WARNING: Removing unreachable block (ram,0x001cf4f8) */
/* WARNING: Removing unreachable block (ram,0x001cf514) */
/* WARNING: Removing unreachable block (ram,0x001cf1f4) */
/* WARNING: Removing unreachable block (ram,0x001cf3e0) */
/* WARNING: Removing unreachable block (ram,0x001cf424) */
/* WARNING: Removing unreachable block (ram,0x001cefd0) */

void sk_r4_001ce704(void)

{
  uint64_t *v1;
  uint64_t *v2;
  uint8_t v3;
  uint8_t av4 [8];
  uint8_t v5;
  uint64_t *v6;
  uint64_t *v7;
  long r8;
  uint64_t v9;
  uint64_t v10;
  char *pc11;
  uint8_t av12 [8];
  uint64_t xo1;
  uint64_t xo1_00;
  uint64_t v13;
  uint64_t xo1_01;
  long ix3;
  uint64_t ix5;
  long xo8;
  long xo8_00;
  long xo8_01;
  uint64_t *xo8_02;
  uint64_t *xo8_03;
  code *xo8_04;
  code *xo8_05;
  code *xo8_06;
  code *xo8_07;
  uint64_t *v14;
  code *xo8_08;
  long xo8_09;
  code *xo8_10;
  code *xo8_11;
  code *xo8_12;
  uint64_t xo8_13;
  code *xo8_14;
  code *xo8_15;
  code *xo8_16;
  long xo8_17;
  uint64_t *xo8_18;
  code *xo8_19;
  code *xo8_20;
  code *xo8_21;
  code *xo8_22;
  long xo8_23;
  long xo8_24;
  code *xo8_25;
  long xo8_26;
  code *xo9;
  uint64_t *v15;
  code *xo9_00;
  code *xo9_01;
  code *xo9_02;
  code *xo10;
  long xo14;
  uint64_t xo15;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  long xo16_03;
  long xo16_04;
  long xo16_05;
  long xo16_06;
  uint64_t *ax19;
  uint64_t *ax20;
  long ax21;
  code *pc16;
  uint64_t ax23;
  uint8_t av17 [8];
  uint64_t v18;
  uint64_t *v19;
  sk_r4_u128_t av20;
  sk_r4_u128_t av21;
  uint64_t *arg;
  uint64_t stk_98;
  uint64_t *v22;
  uint64_t *arg;
  uint64_t stk_70;
  uint64_t *stk_50;
  uint64_t *puStack_48;
  uint64_t *stk_40;
  uint8_t stk_38;
  uint8_t stk_30 [8];
  uint64_t *puStack_28;
  uint64_t *stk_20;
  uint64_t *stk_18;
  long stk_10;
  
  sk_rt_hook_c();
  v6 = (uint64_t *)sk_h_00350a28();
  sk_rt_dispatch(0);
  sk_h_00348d64();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_0034c330();
  sk_h_003504e8();
  sk_h_0034d464();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_0034aa9c();
  sk_h_00349b00();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  sk_h_0034ab10();
  (*datum_00658c00)();
  sk_h_00352008();
  (*datum_00658c00)();
  sk_h_00350464();
  sk_h_0034e3ac();
  (*datum_00658c00)(*(uint64_t *)(xo8_01 + 0x40));
  sk_h_00348a80();
  (*datum_00658c00)();
  sk_h_0034cd68();
  (*datum_00658c00)();
  sk_h_0034bd30();
  (*datum_00658c00)();
  sk_h_00358268();
  sk_h_0035869c();
  arg = xo8_02;
  sk_h_00352cb0();
  if (ax20 == xo8_03) {
    v22 = (uint64_t *)v6[3];
    v10 = v6[4];
    sk_h_0034e1ec(v6);
    sk_h_0006a668(v10);
    sk_h_00349150();
    (*xo8_05)();
    if (ax21 != 0) {
LAB_001cec70:
      av12 = (uint8_t  [8])v22;
      sk_masked_free(&datum_00657798);
LAB_001ceffc:
      sk_swift_release(v6);
      arg = (uint64_t *)av12;
      goto LAB_001cf004;
    }
    stk_98 = sk_h_0035866c();
    (**(code **)(xo16_00 + 0x48))();
    sk_h_0019de9c();
    sk_h_0035310c();
    sk_free();
    v9 = v22[2];
    v19 = v22 + 7;
    for (v18 = 0; v9 != v18; v18 = v18 + 1) {
      if ((uint64_t)v22[2] <= v18) {
LAB_001cf6e4:
        sk_h_00348304();
                    /* WARNING: Subroutine does not return */
        sk_h_001afe4c();
      }
      v6 = (uint64_t *)v19[-3];
      v14 = (uint64_t *)v19[-2];
      stk_20 = (uint64_t *)v19[-1];
      stk_30 = (uint8_t  [8])v6;
      puStack_28 = v14;
      sk_h_00359658(*(uint8_t *)v19);
      pc16 = *(code **)(xo16_01 + 0xe0);
      sk_alloc_pages(v14);
      sk_h_0034dd84();
      av20 = sk_h_00351888();
      sk_h_00357e34(av20.lo,av20.hi,ax19);
      (*pc16)();
      stk_30 = (uint8_t  [8])v6;
      puStack_28 = v14;
      sk_h_00365b6c(xo8_00,stk_30,0x6753a0,0x6753a0,7);
      sk_h_00355eec();
      sk_h_000bd3a4(stk_70);
      (*xo8_06)();
      sk_h_0034ba48();
      sk_h_000839d8();
      sk_h_0034e0d4();
      sk_h_00357564();
      sk_h_0035072c();
      sk_r4_001cf6f4();
      v19 = v19 + 4;
    }
LAB_001cec80:
    sk_free(stk_98);
    sk_free(v22);
    sk_h_003546a8();
  }
  else {
    v5 = ax20 == (uint64_t *)0x677880;
    if ((bool)v5) {
      sk_h_0034b440(v6);
      sk_h_0006a668();
      sk_h_00349150();
      sk_h_00351978();
      (*xo8_07)();
      v22 = ax19;
      if (ax21 != 0) goto LAB_001cec70;
      stk_98 = sk_h_0035866c();
      (**(code **)(xo16_02 + 0x48))();
      sk_h_0019de9c();
      sk_h_0035310c();
      sk_free();
      v14 = (uint64_t *)ax19[2];
      pc11 = (char *)(ax19 + 7);
      for (v19 = (uint64_t *)0x0; v6 = v19, v14 != v19;
          v19 = (uint64_t *)((long)v19 + 1)) {
        if ((uint64_t *)ax19[2] <= v19) goto LAB_001cf6e4;
        v10 = *(uint64_t *)(pc11 + -0x18);
        v6 = *(uint64_t **)(pc11 + -0x10);
        v7 = *(uint64_t **)(pc11 + -8);
        if (*pc11 == '\x01') {
          sk_alloc_pages(v6);
          sk_free(ax19);
          sk_free(stk_98);
          sk_masked_free(arg);
          sk_h_003546a8();
          sk_h_0034995c(v19);
          av12 = (uint8_t  [8])(*xo8_16)();
          v18 = sk_h_003a261c();
          if ((v18 & 1) == 0) {
            sk_h_003570a0(*(uint64_t *)((long)av12 + 0x10));
            sk_h_00350774(0,xo8_17 + 1);
            av12 = (uint8_t  [8])sk_h_001a0a70();
          }
          v18 = *(uint64_t *)((long)av12 + 0x10);
          v22 = (uint64_t *)(v18 + 1);
          if (*(uint64_t *)((long)av12 + 0x18) >> 1 <= v18) {
            sk_h_0006b42c();
            v13 = sk_h_003570a0();
            sk_h_00350774(v13,v22);
            av12 = (uint8_t  [8])sk_h_001a0a70();
          }
          sk_h_00349e54();
          stk_18 = xo8_18;
          stk_10 = xo16_06;
          sk_h_0034f8a8();
          stk_30 = (uint8_t  [8])sk_h_0036a940();
          *(uint64_t *)((long)stk_30 + 0x10) = v10;
          *(uint64_t **)((long)stk_30 + 0x18) = v6;
          *(uint64_t **)((long)stk_30 + 0x20) = v7;
          *(uint8_t *)((long)stk_30 + 0x28) = 1;
          *(uint64_t **)((long)av12 + 0x10) = v22;
          sk_h_00077070(stk_30,(uint64_t *)((long)av12 + (v18 * 5 + 4) * 8));
          sk_h_00348730();
          sk_h_00356b44();
          av20 = sk_h_001a89a8((const char *)0x005ceaf0 /* Expected_Int_key_but_found_Strin */,0x2e,1);
          *v22 = 0x677880;
          *(uint8_t (*) [8])(v18 + 9) = av12;
          *(uint8_t (*) [16])(v18 + 0x11) = av20;
          *(uint64_t *)(v18 + 0x21) = 0;
          *(uint8_t *)(v18 + 0x49) = 0;
          goto LAB_001cf640;
        }
        stk_30 = (uint8_t  [8])v10;
        puStack_28 = v6;
        stk_20 = v7;
        sk_h_00359658();
        pc16 = *(code **)(xo16_03 + 0xe0);
        sk_alloc_pages(v6);
        sk_h_0034dd84();
        sk_h_00357e34(0,ax19,xo1,ax19);
        (*pc16)();
        sk_masked_free(v6);
        stk_30 = (uint8_t  [8])v7;
        sk_h_00365b6c(xo8_00,stk_30,0x677880,0x677880,7);
        sk_h_00355eec();
        av20 = sk_h_00350bf0();
        (*xo8_08)(av20.lo,av20.hi,ax19);
        sk_h_00350750(stk_70);
        sk_h_000839d8();
        av20 = sk_h_00350798();
        sk_h_00357564(av20.lo,av20.hi,ax19);
        sk_h_000e15d8();
        sk_r4_001cf6f4();
        pc11 = pc11 + 0x20;
      }
      goto LAB_001cec80;
    }
    av20 = sk_h_0008dae4();
    v22 = av20.lo;
    if (v22 == (uint64_t *)0x0) {
      v22 = (uint64_t *)v6[3];
      v10 = v6[4];
      sk_h_0034e1ec(v6);
      sk_h_00352680(v10);
      sk_h_00084174(stk_30);
      (*xo9)();
      r8 = stk_10;
      av12 = (uint8_t  [8])stk_18;
      if (ax21 != 0) goto LAB_001cec70;
      sk_h_0034e1ec(stk_30);
      sk_h_0031a26c(r8);
      v10 = sk_h_00350a88();
      (*xo8_14)(v10,r8);
      v18 = sk_h_00351db4();
      if ((!(bool)v5) && ((v18 & 1) != 0)) {
        sk_masked_free(&datum_00657798);
        sk_h_00348730();
        sk_h_00354a00();
        sk_h_0034b440(v6);
        sk_h_0017e880();
        sk_rt_hook_x();
        v10 = (*xo8_15)();
        pc11 = (const char *)0x005cea80 /* Expected_collection_of_key_value */;
        v13 = 0x4d;
LAB_001cf090:
        av20 = sk_h_001a89a8(pc11,v13,1);
        *(uint64_t *)av12 = v10;
        *(uint8_t (*) [16])((long)av12 + 8) = av20;
        *(uint64_t *)((long)av12 + 0x18) = 0;
        *(uint8_t *)((long)av12 + 0x48) = 3;
        sk_h_0036986c();
        sk_swift_release(stk_30);
        goto LAB_001ceffc;
      }
      while( true ) {
        r8 = stk_10;
        sk_h_0034e1ec(stk_30);
        sk_h_0031a17c(r8);
        v10 = sk_h_00350a88();
        v18 = (*xo8_19)(v10,r8);
        if ((v18 & 1) != 0) break;
        sk_h_000836a4(stk_30,stk_18);
        sk_h_003519a8();
        sk_h_0031a1ac();
        sk_h_00351f64(xo15,ax20,ax20,ix3);
        (*xo9_01)();
        r8 = stk_10;
        av12 = (uint8_t  [8])stk_18;
        sk_h_0034e1ec(stk_30);
        sk_h_0031a17c(r8);
        v10 = sk_h_00350a88();
        v18 = (*xo8_20)(v10,r8);
        if ((v18 & 1) != 0) {
          sk_h_00358828();
          (**(code **)(ix3 + 8))(xo15,ax20);
          sk_masked_free(arg);
          sk_h_00348730();
          sk_h_00354a00();
          sk_h_0034b440(v6);
          sk_h_0017e880();
          sk_rt_hook_x();
          v10 = (*xo8_25)();
          pc11 = (const char *)0x005cea40 /* Unkeyed_container_reached_end_be */;
          v13 = 0x3d;
          goto LAB_001cf090;
        }
        sk_h_000836a4(stk_30,stk_18);
        sk_h_003519a8();
        sk_h_0031a1ac();
        sk_h_00350c50();
        sk_h_00351f64(ax19,ax19,ix5);
        (*xo9_02)();
        sk_h_0034e120(*(uint64_t *)(xo14 + 0x20));
        (*xo8_21)();
        sk_h_0034ba48();
        sk_h_000839d8();
        sk_h_00357564(0,ax20,ax19);
        sk_r4_001cf6f4(stk_70,xo15);
      }
      sk_swift_release(stk_30);
    }
    else {
      sk_h_00358834();
      av12 = (uint8_t  [8])v6[3];
      v14 = (uint64_t *)v6[4];
      sk_h_0034e1ec(v6);
      sk_h_0006a668(v14);
      sk_h_00349150();
      sk_h_00351f64();
      v7 = (uint64_t *)(*xo8_04)();
      if (ax21 != 0) {
        sk_masked_free(&datum_00657798);
        goto LAB_001ceffc;
      }
      r8 = sk_h_0007c198();
      (**(code **)(xo16_04 + 0x48))();
      sk_h_0019de9c();
      sk_h_00351d18();
      sk_free();
      sk_h_00353b70(*(uint64_t *)(r8 + 0x10));
      if (xo8_09 != 0) {
        sk_h_00353dac(&stack0x00000048);
        sk_h_0031bc70();
        v18 = 0;
        sk_h_00354ac8(xo16 + 0x20);
        sk_h_00354570(xo14 + 0x20);
        v19 = (uint64_t *)(r8 + 0x38);
LAB_001ced48:
        v5 = v18 == *(uint64_t *)(r8 + 0x10);
        if (v18 < *(uint64_t *)(r8 + 0x10)) {
          v1 = (uint64_t *)v19[-3];
          v2 = (uint64_t *)v19[-2];
          v15 = (uint64_t *)v19[-1];
          v3 = *(uint8_t *)v19;
          stk_50 = v1;
          puStack_48 = v2;
          stk_40 = v15;
          stk_38 = v3;
          sk_h_00350720();
          sk_rt_dispatch();
          sk_h_000a6f88();
          sk_rt_slot();
          (*datum_00658c00)();
          sk_rt_hook_e();
          sk_h_003a25e0(v2,2);
          sk_h_00352d88(v14,&stk_50,0x678560,&datum_004f1878);
          sk_h_00357068();
          (*xo9_00)();
          av21 = sk_h_0035172c();
          sk_h_00350884(av21.lo,av21.hi,v22);
          if ((bool)v5) {
            sk_h_00350524(*(uint64_t *)(xo16_05 + 8));
            (*xo8_10)();
            puStack_28 = (uint64_t *)0x0;
            stk_30 = (uint8_t  [8])0x0;
            stk_18 = (uint64_t *)0x0;
            stk_20 = (uint64_t *)0x0;
            stk_10 = 0;
          }
          else {
            stk_18 = v22;
            stk_10 = ix3;
            v10 = sk_h_00319a4c(stk_30);
            (**(code **)(v22[-1] + 0x20))(v10,v14,v22);
          }
          v10 = sk_rt_desc(0x656138,&datum_004e7f90);
          v9 = sk_h_00365b6c(arg,stk_30,v10,ax20,6);
          if ((v9 & 1) != 0) goto code_r0x001ceec4;
          sk_free(r8);
          sk_masked_free(arg);
          av20 = sk_h_00351d24();
          sk_h_000839d8(av20.lo,av20.hi,1,ax20);
          sk_h_00350bc0(&stk_20);
          (*xo8_22)(arg,ax23);
          sk_enum_err(0x20);
          _local_30 = sk_h_00356b44();
          sk_h_001a89a8((const char *)0x005cead0 /* Could_not_convert_key_to_type */,0x1e,1);
          sk_h_003562e0();
          sk_h_0034b824((uint64_t)v2 & 0xffffffffffff);
          if ((xo8_23 == 0) &&
             ((((uint64_t)v2 & ((uint64_t)arg ^ 0xffffffffffffffff)) >> 0x3d & 1
              ) == 0)) {
            sk_masked_free(arg);
            puStack_28 = arg;
            stk_30 = (uint8_t  [8])v7;
            sk_h_003546a8();
            av12 = (uint8_t  [8])arg;
            av17 = (uint8_t  [8])v7;
          }
          else {
            if (((uint64_t)arg >> 0x3d & 1) == 0) {
              sk_h_0034c6e4((uint64_t)v7 & 0xffffffffffff);
LAB_001cf434:
              sk_h_003546a8();
              v6 = v19;
            }
            else {
              if (((uint64_t)arg >> 0x3d & 1) == 0) goto LAB_001cf434;
              sk_h_003509bc();
              sk_h_00351220();
              sk_rt_slot2();
              if (!(bool)v5) {
                sk_h_0034f078();
                sk_masked_free();
                sk_masked_free(arg);
                av12 = (uint8_t  [8])ax20;
                av17 = (uint8_t  [8])v2;
                v19 = v6;
                stk_30 = (uint8_t  [8])v2;
                puStack_28 = ax20;
                goto LAB_001cf458;
              }
            }
            arg = (uint64_t *)stk_30;
            sk_h_0034f354();
            sk_h_002a4c98();
            sk_masked_free(arg);
            av12 = (uint8_t  [8])puStack_28;
            av17 = stk_30;
            v19 = v6;
          }
LAB_001cf458:
          sk_h_00354d5c();
          sk_h_00208418();
          sk_h_0034e0e4();
          sk_h_0034bf64();
          if ((xo8_24 == 0) &&
             ((((uint64_t)av17 & ((uint64_t)av12 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            sk_masked_free(av12);
            stk_30 = (uint8_t  [8])ax20;
            puStack_28 = v2;
          }
          else {
            if (((uint64_t)av12 >> 0x3d & 1) == 0) {
              sk_h_0034a7ac();
            }
            else if (((uint64_t)v2 >> 0x3d & 1) != 0) {
              sk_h_0034ca18(av17);
              arg = (uint64_t *)sk_rt_slot2();
              if (!(bool)v5) {
                sk_h_003531fc();
                sk_masked_free();
                sk_masked_free(v2);
                stk_30 = (uint8_t  [8])arg;
                puStack_28 = (uint64_t *)av17;
                goto LAB_001cf584;
              }
            }
            arg = (uint64_t *)stk_30;
            sk_h_0034c5bc();
            sk_h_002a4c98();
            sk_masked_free(v2);
          }
LAB_001cf584:
          v6 = puStack_28;
          av4 = stk_30;
          sk_h_003497ec();
          sk_h_001a89a8();
          sk_h_003562e0();
          sk_h_0034a900();
          if ((xo8_26 == 0) &&
             ((((uint64_t)av4 & ((uint64_t)v6 ^ 0xffffffffffffffff)) >> 0x3d & 1) == 0)) {
            sk_masked_free(v6);
          }
          else {
            if (((uint64_t)v6 >> 0x3d & 1) == 0) {
              sk_h_0034c6e4((uint64_t)av17 & 0xffffffffffff);
            }
            else if (((uint64_t)av12 >> 0x3d & 1) != 0) {
              sk_h_0034db48();
              sk_rt_slot2();
              if (!(bool)v5) {
                sk_h_0034f198();
                sk_masked_free();
                sk_masked_free(av12);
                av12 = av4;
                av17 = (uint8_t  [8])arg;
                goto LAB_001cf5e8;
              }
            }
            sk_h_0034f354();
            sk_h_002a4c98();
            sk_masked_free(av12);
            av12 = (uint8_t  [8])puStack_28;
            av17 = stk_30;
          }
LAB_001cf5e8:
          sk_h_00348730();
          av20 = sk_h_00350af4(xo1_01);
          sk_r4_001c1388(av20.lo,av20.hi,v15,v3,v7,av17,av12);
          sk_masked_free(v2);
          sk_free(v7);
          sk_masked_free(av12);
LAB_001cf640:
          sk_h_0036986c();
          v6 = v19;
          goto LAB_001ceffc;
        }
        goto LAB_001cf6e4;
      }
      sk_free(v7);
      sk_free(r8);
    }
  }
LAB_001cf0d0:
  sk_swift_release(v6);
LAB_001cf004:
  v10 = sk_h_00354b5c(arg);
  sk_rt_hook_d(v10,*(uint64_t *)(xo8_00 + 0x58));
  return;
code_r0x001ceec4:
  sk_h_0034ee88(arg);
  sk_h_000839d8();
  sk_h_003510d0(&stack0x00000008);
  sk_h_00355e50();
  sk_h_00350ed0();
  (*xo8_11)();
  stk_18 = (uint64_t *)CONCAT71(stk_18._1_7_,v3);
  stk_30 = (uint8_t  [8])v1;
  puStack_28 = v2;
  stk_20 = v15;
  sk_h_0034dd84((uint64_t)v7 & 0xffffffffffff | 0x6ae1000000000000);
  sk_h_00352f48(&stack0x00000038);
  sk_h_00357e34(ax19,xo1_00,ax19);
  (*xo10)();
  v18 = v18 + 1;
  sk_masked_free(v2);
  sk_h_003510d0(&stack0x00000000);
  sk_h_0034ef28();
  (*xo8_12)();
  sk_h_0034bc94(stk_70);
  sk_h_000839d8();
  sk_h_0034e6fc();
  sk_h_00357564();
  sk_h_0009e234();
  sk_r4_001cf6f4();
  v19 = v19 + 4;
  sk_h_000ec044();
  v14 = ax20;
  ix3 = av20.hi;
  if (xo8_13 == v18) goto code_r0x001cefb4;
  goto LAB_001ced48;
code_r0x001cefb4:
  sk_free(v7);
  sk_free(r8);
  sk_h_003546a8();
  v6 = v19;
  goto LAB_001cf0d0;
}



/* FUN_001cf6f4 @ 0x001cf6f4   (est. sk_r4_001cf6f4)
 * Ghidra: void FUN_001cf6f4(undefined8 param_1,undefined8 param_2,long param_3)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cf6f4(uint64_t p1,uint64_t p2,long p3)

{
  uint8_t zf;
  long xo8;
  long xo8_00;
  code *xo8_01;
  code *xo9;
  long xo16;
  long xo16_00;
  long xo16_01;
  long xo16_02;
  code *pc1;
  long ax21;
  uint64_t v2;
  uint64_t ax30;
  sk_r4_u128_t av3;
  
  sk_cpu();
  sk_h_0034da78();
  v2 = *(uint64_t *)(p3 + 0x18);
  sk_h_0035050c();
  sk_rt_dispatch();
  sk_h_00348ce8();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  sk_h_00348abc();
  (*datum_00658c00)();
  sk_h_0034b87c();
  sk_h_003499c8();
  (*datum_00658c00)(*(uint64_t *)(xo8_00 + 0x40));
  sk_h_003493ac();
  sk_h_003567e0();
  sk_h_003505e8();
  (*xo9)();
  sk_h_0034c4bc();
  if ((bool)zf) {
    pc1 = *(code **)(xo16 + 8);
    sk_h_0035084c();
    (*pc1)();
    sk_h_0006b6f4();
    v2 = sk_h_001efe44();
    sk_h_0034ece8(v2,*(uint64_t *)(ax21 + 0x10));
    (**(code **)(xo16_01 + 8))();
    sk_h_00350630();
    (*pc1)();
  }
  else {
    sk_h_00350028(*(uint64_t *)(xo16_00 + 0x20));
    (*xo8_01)();
    av3 = sk_h_003504e8();
    sk_h_0031a2b4(av3.lo,av3.hi,v2);
    sk_h_001efdc4();
    sk_h_00350bcc();
    (**(code **)(xo16_02 + 8))();
  }
  sk_h_0008e500(ax30);
  return;
}



/* FUN_001cf8b8 @ 0x001cf8b8   (est. sk_r4_001cf8b8)
 * Ghidra: void FUN_001cf8b8(undefined8 *param_1,undefined8 param_2,long param_3,uint64_t param_4)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cf8b8(uint64_t *p1,uint64_t p2,long p3,uint64_t p4)

{
  uint64_t v1;
  long ax21;
  
  v1 = sk_r4_001ce704(p2,*(uint64_t *)(p3 + 0x10),*(uint64_t *)(p3 + 0x18),
                       *(uint64_t *)((p4 & 0xfffffffffffffffe) - 8),
                       *(uint64_t *)(p3 + 0x20),
                       *(uint64_t *)((p4 & 0xfffffffffffffffe) - 0x10));
  if (ax21 == 0) {
    *p1 = v1;
  }
  return;
}



/* FUN_001cf8f8 @ 0x001cf8f8   (est. sk_r4_001cf8f8)
 * Ghidra: void FUN_001cf8f8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cf8f8(void)

{
  uint64_t ix4;
  code *xo8;
  
  sk_h_003585e8();
  sk_h_00352068();
  sk_h_0031b2bc(ix4);
  sk_h_00357b20();
  sk_h_00351118();
  (*xo8)();
  return;
}



/* FUN_001cf964 @ 0x001cf964   (est. sk_r4_001cf964)
 * Ghidra: void FUN_001cf964(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cf964(void)

{
  uint8_t zf;
  uint v1;
  uint64_t v2;
  uint64_t ix3;
  code *xo8;
  
  sk_h_00354a6c();
  if (!(bool)zf) {
    v1 = sk_h_0034d0d0();
    v2 = sk_h_0031a2cc(ix3);
    sk_h_00351e3c(v2,v1 & 1);
    (*xo8)();
  }
  return;
}



/* FUN_001cf9d0 @ 0x001cf9d0   (est. sk_r4_001cf9d0)
 * Ghidra: void FUN_001cf9d0(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cf9d0(uint64_t p1,long p2,uint64_t p3,uint64_t p4,
                 uint64_t p5)

{
  code *xo8;
  
  if (p2 != 0) {
    sk_h_0034d2b4();
    sk_h_00353e50();
    sk_h_0031a2fc(p5);
    sk_h_0034c5dc();
    sk_h_00353b58();
    (*xo8)();
  }
  return;
}



/* FUN_001cfa34 @ 0x001cfa34   (est. sk_r4_001cfa34)
 * Ghidra: void FUN_001cfa34(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfa34(void)

{
  uint8_t zf;
  uint64_t ix4;
  code *xo8;
  
  sk_h_00351db4();
  if (!(bool)zf) {
    sk_h_0034d2b4();
    sk_h_0031a32c(ix4);
    sk_h_0035a684();
    sk_h_0034bc24();
    (*xo8)();
  }
  return;
}



/* FUN_001cfa94 @ 0x001cfa94   (est. sk_r4_001cfa94)
 * Ghidra: void FUN_001cfa94(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfa94(void)

{
  uint8_t zf;
  uint64_t ix3;
  code *xo8;
  
  sk_h_0034ecc8();
  if (!(bool)zf) {
    sk_h_0034d0d0();
    sk_h_0031a35c(ix3);
    sk_h_0035a684();
    sk_h_0034bc24();
    (*xo8)();
  }
  return;
}



/* FUN_001cfaf4 @ 0x001cfaf4   (est. sk_r4_001cfaf4)
 * Ghidra: void FUN_001cfaf4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfaf4(void)

{
  uint8_t zf;
  code *xo8;
  
  sk_h_00351db4();
  if (!(bool)zf) {
    sk_h_0034d2b4();
    sk_h_00358e58();
    sk_h_0031a38c();
    sk_h_0034bddc();
    sk_h_00351e3c();
    (*xo8)();
  }
  return;
}



/* FUN_001cfb54 @ 0x001cfb54   (est. sk_r4_001cfb54)
 * Ghidra: void FUN_001cfb54(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfb54(void)

{
  sk_r4_001cfcf0();
  return;
}



/* FUN_001cfb58 @ 0x001cfb58   (est. sk_r4_001cfb58)
 * Ghidra: void FUN_001cfb58(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfb58(void)

{
  sk_r4_001cfcf0();
  return;
}



/* FUN_001cfb84 @ 0x001cfb84   (est. sk_r4_001cfb84)
 * Ghidra: void FUN_001cfb84(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfb84(void)

{
  sk_r4_001cfd94();
  return;
}



/* FUN_001cfb88 @ 0x001cfb88   (est. sk_r4_001cfb88)
 * Ghidra: void FUN_001cfb88(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfb88(void)

{
  sk_r4_001cfd94();
  return;
}



/* FUN_001cfbb4 @ 0x001cfbb4   (est. sk_r4_001cfbb4)
 * Ghidra: void FUN_001cfbb4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfbb4(void)

{
  sk_h_00354248();
  sk_r4_001cfe24();
  return;
}



/* FUN_001cfbb8 @ 0x001cfbb8   (est. sk_r4_001cfbb8)
 * Ghidra: void FUN_001cfbb8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfbb8(void)

{
  sk_h_00354248();
  sk_r4_001cfe24();
  return;
}



/* FUN_001cfbd0 @ 0x001cfbd0   (est. sk_r4_001cfbd0)
 * Ghidra: void FUN_001cfbd0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfbd0(void)

{
  uint8_t zf;
  code *xo8;
  
  sk_h_00351db4();
  if (!(bool)zf) {
    sk_h_0034d2b4();
    sk_h_00358e58();
    sk_h_0031a44c();
    sk_h_0034bddc();
    sk_h_00351e3c();
    (*xo8)();
  }
  return;
}



/* FUN_001cfc30 @ 0x001cfc30   (est. sk_r4_001cfc30)
 * Ghidra: void FUN_001cfc30(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfc30(void)

{
  sk_r4_001cff24();
  return;
}



/* FUN_001cfc34 @ 0x001cfc34   (est. sk_r4_001cfc34)
 * Ghidra: void FUN_001cfc34(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfc34(void)

{
  sk_r4_001cff24();
  return;
}



/* FUN_001cfc60 @ 0x001cfc60   (est. sk_r4_001cfc60)
 * Ghidra: void FUN_001cfc60(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfc60(void)

{
  uint8_t zf;
  code *xo8;
  
  sk_h_00351db4();
  if (!(bool)zf) {
    sk_h_0034d2b4();
    sk_h_00358e58();
    sk_h_0031a4ac();
    sk_h_0034bddc();
    sk_h_00351e3c();
    (*xo8)();
  }
  return;
}



/* FUN_001cfcc0 @ 0x001cfcc0   (est. sk_r4_001cfcc0)
 * Ghidra: void FUN_001cfcc0(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfcc0(void)

{
  sk_r4_001cfcf0();
  return;
}



/* FUN_001cfcc4 @ 0x001cfcc4   (est. sk_r4_001cfcc4)
 * Ghidra: void FUN_001cfcc4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfcc4(void)

{
  sk_r4_001cfcf0();
  return;
}



/* FUN_001cfcf0 @ 0x001cfcf0   (est. sk_r4_001cfcf0)
 * Ghidra: void FUN_001cfcf0(uint param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfcf0(uint p1,uint64_t p2,uint64_t p3,uint64_t p4,
                 code *p5)

{
  uint64_t v1;
  uint64_t v2;
  code *xo8;
  
  if ((p1 & 0xff00) != 0x100) {
    v1 = sk_h_0034d6d8();
    v2 = (*p5)(p4);
    sk_h_00352ae4(v2,v1);
    (*xo8)();
  }
  return;
}



/* FUN_001cfd64 @ 0x001cfd64   (est. sk_r4_001cfd64)
 * Ghidra: void FUN_001cfd64(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfd64(void)

{
  sk_r4_001cfd94();
  return;
}



/* FUN_001cfd68 @ 0x001cfd68   (est. sk_r4_001cfd68)
 * Ghidra: void FUN_001cfd68(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfd68(void)

{
  sk_r4_001cfd94();
  return;
}



/* FUN_001cfd94 @ 0x001cfd94   (est. sk_r4_001cfd94)
 * Ghidra: void FUN_001cfd94(uint param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfd94(uint p1,uint64_t p2,uint64_t p3,uint64_t p4,
                 code *p5)

{
  uint64_t v1;
  uint64_t v2;
  code *xo8;
  
  if ((p1 & 0xff0000) != 0x10000) {
    v1 = sk_h_0034d6d8();
    v2 = (*p5)(p4);
    sk_h_00352ae4(v2,v1);
    (*xo8)();
  }
  return;
}



/* FUN_001cfe08 @ 0x001cfe08   (est. sk_r4_001cfe08)
 * Ghidra: void FUN_001cfe08(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfe08(void)

{
  sk_h_0035422c();
  sk_r4_001cfe24();
  return;
}



/* FUN_001cfe0c @ 0x001cfe0c   (est. sk_r4_001cfe0c)
 * Ghidra: void FUN_001cfe0c(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfe0c(void)

{
  sk_h_0035422c();
  sk_r4_001cfe24();
  return;
}



/* FUN_001cfe24 @ 0x001cfe24   (est. sk_r4_001cfe24)
 * Ghidra: void FUN_001cfe24(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfe24(void)

{
  uint8_t zf;
  uint64_t v1;
  uint64_t v2;
  uint64_t ix3;
  code *ix4;
  code *xo8;
  
  sk_h_0034ecc8();
  if (!(bool)zf) {
    v1 = sk_h_0034d6d8();
    v2 = (*ix4)(ix3);
    sk_h_00352ae4(v2,v1);
    (*xo8)();
  }
  return;
}



/* FUN_001cfe94 @ 0x001cfe94   (est. sk_r4_001cfe94)
 * Ghidra: void FUN_001cfe94(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfe94(void)

{
  uint8_t zf;
  code *xo8;
  
  sk_h_00351db4();
  if (!(bool)zf) {
    sk_h_0034d2b4();
    sk_h_00358e58();
    sk_h_0031a56c();
    sk_h_0034bddc();
    sk_h_00351e3c();
    (*xo8)();
  }
  return;
}



/* FUN_001cfef4 @ 0x001cfef4   (est. sk_r4_001cfef4)
 * Ghidra: void FUN_001cfef4(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfef4(void)

{
  sk_r4_001cff24();
  return;
}



/* FUN_001cfef8 @ 0x001cfef8   (est. sk_r4_001cfef8)
 * Ghidra: void FUN_001cfef8(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cfef8(void)

{
  sk_r4_001cff24();
  return;
}



/* FUN_001cff24 @ 0x001cff24   (est. sk_r4_001cff24)
 * Ghidra: void FUN_001cff24(void)
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cff24(void)

{
  uint8_t zf;
  uint64_t ix5;
  code *ix6;
  code *xo8;
  
  sk_h_0035292c();
  if (!(bool)zf) {
    sk_h_00357198();
    sk_h_003537fc();
    (*ix6)(ix5);
    sk_h_0034ce68();
    sk_h_00354318();
    (*xo8)();
  }
  return;
}



/* FUN_001cff9c @ 0x001cff9c   (est. sk_r4_001cff9c)
 * Ghidra: void FUN_001cff9c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
 * Swift-runtime/thread-machinery function in the cL4 scheduler region. Faithful
 * transcription of the decompile: helper calls, control flow, constants preserved.
 * Confidence: medium
 * Notes: slice 0x1c0000-0x1d0000. */


void sk_r4_001cff9c(uint64_t p1,uint64_t p2,uint64_t p3,uint64_t p4,
                 uint64_t p5,uint64_t p6)

{
  uint8_t zf;
  uint64_t v1;
  uint64_t xo1;
  long xo8;
  code *xo8_00;
  code *xo8_01;
  code *xo8_02;
  code *xo9;
  code *xo9_00;
  long xo16;
  long xo16_00;
  uint64_t arg;
  
  sk_rt_hook_c();
  sk_h_00355e68();
  sk_h_003516cc();
  sk_rt_dispatch();
  sk_rt_hook_f();
  sk_rt_slot();
  (*datum_00658c00)();
  sk_h_0034b05c();
  sk_h_003499f0();
  (*datum_00658c00)(*(uint64_t *)(xo8 + 0x40));
  sk_h_00349068();
  sk_h_003534bc();
  sk_h_003512c0();
  (*xo9)();
  sk_h_0034b2c8();
  if ((bool)zf) {
    sk_h_003510dc(*(uint64_t *)(xo16 + 8));
    (*xo8_00)();
  }
  else {
    sk_h_0034db58();
    (*xo9_00)();
    sk_h_0031b2bc(p5);
    v1 = sk_h_00350648();
    (*xo8_01)(v1,xo1,p4,p6,p3,p5);
    sk_h_0035084c(*(uint64_t *)(xo16_00 + 8));
    (*xo8_02)();
  }
  sk_h_00351348();
  sk_rt_hook_d(arg);
  return;
}

