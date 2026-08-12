/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) — the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in program cl4_kernel.raw.
 * Slice 00: 0x28279c-0x28e374 object region. All names are estimates unless
 * string/header-matched. Uses seL4/cL4 vocabulary (TCB, cap, CNode, IPC,
 * notification, endpoint, vspace, sched, object, slot).
 *
 * This region is dominated by the cL4 kernel's embedded Swift runtime and
 * object-service machinery: Swift String/Array/Set/ContiguousArrayBuffer /
 * Range primitives (with fatal-error precondition checks and bit-reversed
 * bitmap indexing), string/UTF8/UTF16 index arithmetic, and the object /
 * collection method-dispatch service loops (heavy indirect dispatch through
 * the global DAT_00658c00 slot and per-object method tables).
 *
 * NOTE on the calling convention: the decompiler shows most of these as
 * `void FUN(void)` because every argument (including C++ `this`, `unaff_x20`)
 * is passed in registers and not modelled as a formal parameter. We model the
 * container `this` pointer as the explicit first parameter `thisp` and give
 * the out-of-range helpers unspecific-arity word-returning declarations that
 * match the actual register usage observed at the call sites. Ghidra FUN_ names
 * are kept only in comments (and, following the sibling-slice convention, as
 * the generic out-of-range helper identifiers).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t word_t;
typedef uint32_t seL4_Word;

/* Ghidra carry idiom used in the decompiled bodies (kept faithful). */
#define SCARRY8(a, b)  (__builtin_add_overflow((a), (b), &(unsigned long){0}))
#define SBORROW8(a, b) (__builtin_sub_overflow((a), (b), &(unsigned long){0}))
#define LZCOUNT(x)     ((unsigned long)__builtin_clzll((unsigned long)(x)))

/* SoftwareBreakpoint(<x>) trap path. */
#define CL4_FATAL() __builtin_trap()

/* Swift fatal-error (noreturn) precondition failure. */
#define SWIFT_FATAL(code)                      \
    do { sk_fatal_error(0xb, 2, code, 2, "Swift.Range", 0x11, 2); __builtin_trap(); } while (0)


/* 16-byte (two-word) Swift value returns. */
typedef struct { uint64_t lo, hi; } wpair_t;

/* Standard Swift precondition failures (message/type/code from decompile). */
#define SWF_INDEX_RANGE()   sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.Range",0x11,2,0x136,1)
#define SWF_RANGE_BOUND()   sk_fatal_error(0xb,2,"Range requires lowerBound < upperBound",0x27,2,"Swift.Range",0x11,2,0xb5,1)
#define SWF_CONTIG_IDX()    sk_fatal_error(0xb,2,"Index out of range",0x12,2,"Swift.ContiguousArrayBuffer",0x21,2,0x136,1)
#define SWF_FATAL(msg,mlen,type,tlen,code)     sk_fatal_error(0xb,2,(msg),(mlen),2,(type),(tlen),2,(code),1)

/* Bit-reverse a 64-bit word (Swift bitmap index helper). */
static inline uint64_t sk_bitreverse64(uint64_t v)
{
    v = ((v & 0xaaaaaaaaaaaaaaaaull) >> 1) | ((v & 0x5555555555555555ull) << 1);
    v = ((v & 0xccccccccccccccccull) >> 2) | ((v & 0x3333333333333333ull) << 2);
    v = ((v & 0xf0f0f0f0f0f0f0f0ull) >> 4) | ((v & 0x0f0f0f0f0f0f0f0full) << 4);
    v = ((v & 0xff00ff00ff00ff00ull) >> 8) | ((v & 0x00ff00ff00ff00ffull) << 8);
    v = ((v & 0xffff0000ffff0000ull) >> 16) | ((v & 0x0000ffff0000ffffull) << 16);
    return (v >> 32) | (v << 32);
}


/* Object method-dispatch slot / table bases used by constructors & loops. */
typedef uint64_t (*code)();   /* unspecified-arity word-returning fn pointer */
extern unsigned char sk_obj_methods_0[];  /* DAT_00611b24 */
extern unsigned char sk_obj_methods_1[];  /* DAT_00611b34 / LAB_00611b34 */
/* Core allocator / refcount / lock primitives (region 0x34xxxx-0x37xxxx). */
extern void *sk_alloc(unsigned long size, unsigned long tag);        /* FUN_0036a908 */
extern void *sk_alloc_pages(unsigned long size, unsigned long tag);  /* FUN_0036b270 */
extern void sk_free(void *ptr);                                      /* FUN_0036b118 */
extern unsigned long sk_object_lock(unsigned long a, unsigned long b, unsigned long c,
                                    void *d1, void *d2);             /* FUN_00377824 */
extern unsigned long sk_lock_ref(unsigned long a, ...);              /* FUN_00377bec */
extern void sk_lock_release(unsigned long a, ...);                   /* FUN_00377dcc */
extern unsigned long sk_spin_irqsave(unsigned long *flags);          /* FUN_00357cb4 */
extern void sk_irqrestore(unsigned long flags);                      /* FUN_00357c74 */
extern void sk_token_release(unsigned long a);                       /* FUN_003a25d4 */
extern unsigned long sk_obj_meta(unsigned long a);                   /* FUN_003a261c */
extern void *sk_current_tcb(void);                                   /* FUN_000867ec */
extern void *sk_cpu(void);                                           /* FUN_0008e518 */

/* Swift fatal-error (noreturn); VARIADIC. */
extern void sk_fatal_error(unsigned long, unsigned long, ...) __attribute__((noreturn)); /* FUN_001afe4c */

/* Generic out-of-range helpers referenced by this region (bodies reconstructed by
 * sibling SK range workers).  Unspecific-arity word-returning declarations so any
 * observed call pattern compiles.  Ghidra FUN_ names kept as identifiers per the
 * sibling-slice convention. */
extern uint64_t FUN_00002534();  /* out-of-range helper */
extern uint64_t FUN_000026e8();  /* out-of-range helper */
extern uint64_t FUN_0001a1c8();  /* out-of-range helper */
extern uint64_t FUN_0001da84();  /* out-of-range helper */
extern uint64_t FUN_00027754();  /* out-of-range helper */
extern uint64_t FUN_000277b8();  /* out-of-range helper */
extern uint64_t FUN_00027818();  /* out-of-range helper */
extern uint64_t FUN_0006a4c0();  /* out-of-range helper */
extern uint64_t FUN_0006b6f4();  /* out-of-range helper */
extern uint64_t FUN_0006f768();  /* out-of-range helper */
extern uint64_t FUN_0007767c();  /* out-of-range helper */
extern uint64_t FUN_00077698();  /* out-of-range helper */
extern uint64_t FUN_000776c0();  /* out-of-range helper */
extern uint64_t FUN_00077888();  /* out-of-range helper */
extern uint64_t FUN_00077894();  /* out-of-range helper */
extern uint64_t FUN_0007c028();  /* out-of-range helper */
extern uint64_t FUN_0007c1a4();  /* out-of-range helper */
extern uint64_t FUN_000839d8();  /* out-of-range helper */
extern uint64_t FUN_000839f8();  /* out-of-range helper */
extern uint64_t FUN_0008409c();  /* out-of-range helper */
extern uint64_t FUN_0008412c();  /* out-of-range helper */
extern uint64_t FUN_00084180();  /* out-of-range helper */
extern uint64_t FUN_000841a0();  /* out-of-range helper */
extern uint64_t FUN_00084220();  /* out-of-range helper */
extern uint64_t FUN_00084234();  /* out-of-range helper */
extern uint64_t FUN_000867ec();  /* out-of-range helper */
extern uint64_t FUN_0008e388();  /* out-of-range helper */
extern uint64_t FUN_0008e500();  /* out-of-range helper */
extern uint64_t FUN_0008e518();  /* out-of-range helper */
extern uint64_t FUN_0008e5d8();  /* out-of-range helper */
extern uint64_t FUN_0009461c();  /* out-of-range helper */
extern uint64_t FUN_0009e234();  /* out-of-range helper */
extern uint64_t FUN_000a6894();  /* out-of-range helper */
extern uint64_t FUN_000a68c4();  /* out-of-range helper */
extern uint64_t FUN_000a68f4();  /* out-of-range helper */
extern uint64_t FUN_000a6e14();  /* out-of-range helper */
extern uint64_t FUN_000a6f88();  /* out-of-range helper */
extern uint64_t FUN_000aa4ec();  /* out-of-range helper */
extern uint64_t FUN_000b394c();  /* out-of-range helper */
extern uint64_t FUN_000b4390();  /* out-of-range helper */
extern uint64_t FUN_000b43d0();  /* out-of-range helper */
extern uint64_t FUN_000b4594();  /* out-of-range helper */
extern uint64_t FUN_000b45b0();  /* out-of-range helper */
extern uint64_t FUN_000bd3a4();  /* out-of-range helper */
extern uint64_t FUN_000dbd0c();  /* out-of-range helper */
extern uint64_t FUN_000dbf08();  /* out-of-range helper */
extern uint64_t FUN_000e15d8();  /* out-of-range helper */
extern uint64_t FUN_000e72b0();  /* out-of-range helper */
extern uint64_t FUN_00100efc();  /* out-of-range helper */
extern uint64_t FUN_00117cc4();  /* out-of-range helper */
extern uint64_t FUN_0014ae44();  /* out-of-range helper */
extern uint64_t FUN_0014f810();  /* out-of-range helper */
extern uint64_t FUN_001676cc();  /* out-of-range helper */
extern uint64_t FUN_0019e644();  /* out-of-range helper */
extern uint64_t FUN_0019e690();  /* out-of-range helper */
extern uint64_t FUN_0019ea20();  /* out-of-range helper */
extern uint64_t FUN_0019fd10();  /* out-of-range helper */
extern uint64_t FUN_001a0414();  /* out-of-range helper */
extern uint64_t FUN_001a1854();  /* out-of-range helper */
extern uint64_t FUN_001a2128();  /* out-of-range helper */
extern uint64_t FUN_001a67bc();  /* out-of-range helper */
extern uint64_t FUN_001a6ab8();  /* out-of-range helper */
extern uint64_t FUN_001a84f4();  /* out-of-range helper */
extern uint64_t FUN_001a8564();  /* out-of-range helper */
extern uint64_t FUN_001aeab4();  /* out-of-range helper */
extern uint64_t FUN_001afe4c();  /* out-of-range helper */
extern uint64_t FUN_001b9084();  /* out-of-range helper */
extern uint64_t FUN_001bcc18();  /* out-of-range helper */
extern uint64_t FUN_001cc94c();  /* out-of-range helper */
extern uint64_t FUN_001d3fd0();  /* out-of-range helper */
extern uint64_t FUN_001d88fc();  /* out-of-range helper */
extern uint64_t FUN_001e4cbc();  /* out-of-range helper */
extern uint64_t FUN_001f26cc();  /* out-of-range helper */
extern uint64_t FUN_001f6fac();  /* out-of-range helper */
extern uint64_t FUN_001f7d28();  /* out-of-range helper */
extern uint64_t FUN_001fab14();  /* out-of-range helper */
extern uint64_t FUN_001fb194();  /* out-of-range helper */
extern uint64_t FUN_001ff258();  /* out-of-range helper */
extern uint64_t FUN_0021867c();  /* out-of-range helper */
extern uint64_t FUN_00228e78();  /* out-of-range helper */
extern uint64_t FUN_0022b584();  /* out-of-range helper */
extern uint64_t FUN_00257020();  /* out-of-range helper */
extern uint64_t FUN_0025a060();  /* out-of-range helper */
extern uint64_t FUN_0025a864();  /* out-of-range helper */
extern uint64_t FUN_0025af6c();  /* out-of-range helper */
extern uint64_t FUN_0025b7d8();  /* out-of-range helper */
extern uint64_t FUN_0025ba04();  /* out-of-range helper */
extern uint64_t FUN_0025baa4();  /* out-of-range helper */
extern uint64_t FUN_0025bae0();  /* out-of-range helper */
extern uint64_t FUN_0025c2b8();  /* out-of-range helper */
extern uint64_t FUN_0025cc54();  /* out-of-range helper */
extern uint64_t FUN_0025d0d4();  /* out-of-range helper */
extern uint64_t FUN_0025d3d0();  /* out-of-range helper */
extern uint64_t FUN_0025e000();  /* out-of-range helper */
extern uint64_t FUN_0025e240();  /* out-of-range helper */
extern uint64_t FUN_0025e370();  /* out-of-range helper */
extern uint64_t FUN_0025e4a0();  /* out-of-range helper */
extern uint64_t FUN_0025f164();  /* out-of-range helper */
extern uint64_t FUN_0025f910();  /* out-of-range helper */
extern uint64_t FUN_002603f8();  /* out-of-range helper */
extern uint64_t FUN_002608cc();  /* out-of-range helper */
extern uint64_t FUN_00261134();  /* out-of-range helper */
extern uint64_t FUN_00262e9c();  /* out-of-range helper */
extern uint64_t FUN_0026398c();  /* out-of-range helper */
extern uint64_t FUN_00263e20();  /* out-of-range helper */
extern uint64_t FUN_0026a744();  /* out-of-range helper */
extern uint64_t FUN_0026af9c();  /* out-of-range helper */
extern uint64_t FUN_0026b1dc();  /* out-of-range helper */
extern uint64_t FUN_0026bd30();  /* out-of-range helper */
extern uint64_t FUN_0028e94c();  /* out-of-range helper */
extern uint64_t FUN_002a0d50();  /* out-of-range helper */
extern uint64_t FUN_002a9ba8();  /* out-of-range helper */
extern uint64_t FUN_002ab6a0();  /* out-of-range helper */
extern uint64_t FUN_002af4d0();  /* out-of-range helper */
extern uint64_t FUN_002b3b84();  /* out-of-range helper */
extern uint64_t FUN_002b439c();  /* out-of-range helper */
extern uint64_t FUN_002b64cc();  /* out-of-range helper */
extern uint64_t FUN_0031090c();  /* out-of-range helper */
extern uint64_t FUN_00310b98();  /* out-of-range helper */
extern uint64_t FUN_00310c44();  /* out-of-range helper */
extern uint64_t FUN_00310cd4();  /* out-of-range helper */
extern uint64_t FUN_00310d34();  /* out-of-range helper */
extern uint64_t FUN_00310d68();  /* out-of-range helper */
extern uint64_t FUN_00310e08();  /* out-of-range helper */
extern uint64_t FUN_00310ed4();  /* out-of-range helper */
extern uint64_t FUN_003192d8();  /* out-of-range helper */
extern uint64_t FUN_0031948c();  /* out-of-range helper */
extern uint64_t FUN_003196e8();  /* out-of-range helper */
extern uint64_t FUN_0031993c();  /* out-of-range helper */
extern uint64_t FUN_0031996c();  /* out-of-range helper */
extern uint64_t FUN_0031997c();  /* out-of-range helper */
extern uint64_t FUN_003199ac();  /* out-of-range helper */
extern uint64_t FUN_0031a1dc();  /* out-of-range helper */
extern uint64_t FUN_0031a1f4();  /* out-of-range helper */
extern uint64_t FUN_0031afcc();  /* out-of-range helper */
extern uint64_t FUN_0031b080();  /* out-of-range helper */
extern uint64_t FUN_0031b37c();  /* out-of-range helper */
extern uint64_t FUN_0031c688();  /* out-of-range helper */
extern uint64_t FUN_0031d5d8();  /* out-of-range helper */
extern uint64_t FUN_0031dd98();  /* out-of-range helper */
extern uint64_t FUN_0031ddb0();  /* out-of-range helper */
extern uint64_t FUN_0031ddc8();  /* out-of-range helper */
extern uint64_t FUN_0031ddfc();  /* out-of-range helper */
extern uint64_t FUN_0031e134();  /* out-of-range helper */
extern uint64_t FUN_00327e08();  /* out-of-range helper */
extern uint64_t FUN_00343cac();  /* out-of-range helper */
extern uint64_t FUN_00343cf8();  /* out-of-range helper */
extern uint64_t FUN_0034435c();  /* out-of-range helper */
extern uint64_t FUN_00344d4c();  /* out-of-range helper */
extern uint64_t FUN_00344e54();  /* out-of-range helper */
extern uint64_t FUN_00346580();  /* out-of-range helper */
extern uint64_t FUN_00347ebc();  /* out-of-range helper */
extern uint64_t FUN_00348034();  /* out-of-range helper */
extern uint64_t FUN_003488bc();  /* out-of-range helper */
extern uint64_t FUN_003489c0();  /* out-of-range helper */
extern uint64_t FUN_003489dc();  /* out-of-range helper */
extern uint64_t FUN_00348abc();  /* out-of-range helper */
extern uint64_t FUN_00348b94();  /* out-of-range helper */
extern uint64_t FUN_00348bbc();  /* out-of-range helper */
extern uint64_t FUN_00348bd8();  /* out-of-range helper */
extern uint64_t FUN_00348bf8();  /* out-of-range helper */
extern uint64_t FUN_00348c48();  /* out-of-range helper */
extern uint64_t FUN_00348cd0();  /* out-of-range helper */
extern uint64_t FUN_00348ce8();  /* out-of-range helper */
extern uint64_t FUN_00348d4c();  /* out-of-range helper */
extern uint64_t FUN_00348d64();  /* out-of-range helper */
extern uint64_t FUN_00348d7c();  /* out-of-range helper */
extern uint64_t FUN_00348dd8();  /* out-of-range helper */
extern uint64_t FUN_00348e00();  /* out-of-range helper */
extern uint64_t FUN_00348e18();  /* out-of-range helper */
extern uint64_t FUN_00348e60();  /* out-of-range helper */
extern uint64_t FUN_00348f38();  /* out-of-range helper */
extern uint64_t FUN_00348f50();  /* out-of-range helper */
extern uint64_t FUN_00348f68();  /* out-of-range helper */
extern uint64_t FUN_00348fd8();  /* out-of-range helper */
extern uint64_t FUN_00349068();  /* out-of-range helper */
extern uint64_t FUN_00349080();  /* out-of-range helper */
extern uint64_t FUN_003490b8();  /* out-of-range helper */
extern uint64_t FUN_003490d0();  /* out-of-range helper */
extern uint64_t FUN_003490ec();  /* out-of-range helper */
extern uint64_t FUN_00349178();  /* out-of-range helper */
extern uint64_t FUN_0034924c();  /* out-of-range helper */
extern uint64_t FUN_0034926c();  /* out-of-range helper */
extern uint64_t FUN_003493c4();  /* out-of-range helper */
extern uint64_t FUN_0034947c();  /* out-of-range helper */
extern uint64_t FUN_003494e8();  /* out-of-range helper */
extern uint64_t FUN_00349530();  /* out-of-range helper */
extern uint64_t FUN_00349720();  /* out-of-range helper */
extern uint64_t FUN_00349734();  /* out-of-range helper */
extern uint64_t FUN_00349748();  /* out-of-range helper */
extern uint64_t FUN_003497a0();  /* out-of-range helper */
extern uint64_t FUN_003497b4();  /* out-of-range helper */
extern uint64_t FUN_00349830();  /* out-of-range helper */
extern uint64_t FUN_00349944();  /* out-of-range helper */
extern uint64_t FUN_0034998c();  /* out-of-range helper */
extern uint64_t FUN_003499b4();  /* out-of-range helper */
extern uint64_t FUN_003499c8();  /* out-of-range helper */
extern uint64_t FUN_003499f0();  /* out-of-range helper */
extern uint64_t FUN_00349a68();  /* out-of-range helper */
extern uint64_t FUN_00349b00();  /* out-of-range helper */
extern uint64_t FUN_00349b3c();  /* out-of-range helper */
extern uint64_t FUN_00349d14();  /* out-of-range helper */
extern uint64_t FUN_00349e38();  /* out-of-range helper */
extern uint64_t FUN_00349ea0();  /* out-of-range helper */
extern uint64_t FUN_00349ef4();  /* out-of-range helper */
extern uint64_t FUN_00349f3c();  /* out-of-range helper */
extern uint64_t FUN_0034a2f8();  /* out-of-range helper */
extern uint64_t FUN_0034a32c();  /* out-of-range helper */
extern uint64_t FUN_0034a340();  /* out-of-range helper */
extern uint64_t FUN_0034a3c4();  /* out-of-range helper */
extern uint64_t FUN_0034a3ec();  /* out-of-range helper */
extern uint64_t FUN_0034a464();  /* out-of-range helper */
extern uint64_t FUN_0034a4a4();  /* out-of-range helper */
extern uint64_t FUN_0034a688();  /* out-of-range helper */
extern uint64_t FUN_0034aa54();  /* out-of-range helper */
extern uint64_t FUN_0034ab10();  /* out-of-range helper */
extern uint64_t FUN_0034ac3c();  /* out-of-range helper */
extern uint64_t FUN_0034ae08();  /* out-of-range helper */
extern uint64_t FUN_0034aebc();  /* out-of-range helper */
extern uint64_t FUN_0034aee4();  /* out-of-range helper */
extern uint64_t FUN_0034af20();  /* out-of-range helper */
extern uint64_t FUN_0034b05c();  /* out-of-range helper */
extern uint64_t FUN_0034b0b4();  /* out-of-range helper */
extern uint64_t FUN_0034b0c4();  /* out-of-range helper */
extern uint64_t FUN_0034b0d4();  /* out-of-range helper */
extern uint64_t FUN_0034b278();  /* out-of-range helper */
extern uint64_t FUN_0034b2c8();  /* out-of-range helper */
extern uint64_t FUN_0034b2f8();  /* out-of-range helper */
extern uint64_t FUN_0034b348();  /* out-of-range helper */
extern uint64_t FUN_0034b358();  /* out-of-range helper */
extern uint64_t FUN_0034b3e8();  /* out-of-range helper */
extern uint64_t FUN_0034b440();  /* out-of-range helper */
extern uint64_t FUN_0034b508();  /* out-of-range helper */
extern uint64_t FUN_0034b690();  /* out-of-range helper */
extern uint64_t FUN_0034b758();  /* out-of-range helper */
extern uint64_t FUN_0034b7e4();  /* out-of-range helper */
extern uint64_t FUN_0034b85c();  /* out-of-range helper */
extern uint64_t FUN_0034b87c();  /* out-of-range helper */
extern uint64_t FUN_0034b8bc();  /* out-of-range helper */
extern uint64_t FUN_0034ba68();  /* out-of-range helper */
extern uint64_t FUN_0034bbdc();  /* out-of-range helper */
extern uint64_t FUN_0034bc94();  /* out-of-range helper */
extern uint64_t FUN_0034bcf0();  /* out-of-range helper */
extern uint64_t FUN_0034bd00();  /* out-of-range helper */
extern uint64_t FUN_0034bdbc();  /* out-of-range helper */
extern uint64_t FUN_0034bdfc();  /* out-of-range helper */
extern uint64_t FUN_0034be0c();  /* out-of-range helper */
extern uint64_t FUN_0034bec4();  /* out-of-range helper */
extern uint64_t FUN_0034c034();  /* out-of-range helper */
extern uint64_t FUN_0034c074();  /* out-of-range helper */
extern uint64_t FUN_0034c084();  /* out-of-range helper */
extern uint64_t FUN_0034c158();  /* out-of-range helper */
extern uint64_t FUN_0034c194();  /* out-of-range helper */
extern uint64_t FUN_0034c2c8();  /* out-of-range helper */
extern uint64_t FUN_0034c2d8();  /* out-of-range helper */
extern uint64_t FUN_0034c2e8();  /* out-of-range helper */
extern uint64_t FUN_0034c4fc();  /* out-of-range helper */
extern uint64_t FUN_0034c53c();  /* out-of-range helper */
extern uint64_t FUN_0034c55c();  /* out-of-range helper */
extern uint64_t FUN_0034c5ac();  /* out-of-range helper */
extern uint64_t FUN_0034c818();  /* out-of-range helper */
extern uint64_t FUN_0034c920();  /* out-of-range helper */
extern uint64_t FUN_0034c9d8();  /* out-of-range helper */
extern uint64_t FUN_0034cdd8();  /* out-of-range helper */
extern uint64_t FUN_0034ce78();  /* out-of-range helper */
extern uint64_t FUN_0034ce98();  /* out-of-range helper */
extern uint64_t FUN_0034d130();  /* out-of-range helper */
extern uint64_t FUN_0034d190();  /* out-of-range helper */
extern uint64_t FUN_0034d264();  /* out-of-range helper */
extern uint64_t FUN_0034d2a4();  /* out-of-range helper */
extern uint64_t FUN_0034d3b4();  /* out-of-range helper */
extern uint64_t FUN_0034d3c4();  /* out-of-range helper */
extern uint64_t FUN_0034d3e4();  /* out-of-range helper */
extern uint64_t FUN_0034d424();  /* out-of-range helper */
extern uint64_t FUN_0034d464();  /* out-of-range helper */
extern uint64_t FUN_0034d49c();  /* out-of-range helper */
extern uint64_t FUN_0034d574();  /* out-of-range helper */
extern uint64_t FUN_0034d5ec();  /* out-of-range helper */
extern uint64_t FUN_0034d688();  /* out-of-range helper */
extern uint64_t FUN_0034d698();  /* out-of-range helper */
extern uint64_t FUN_0034d6d8();  /* out-of-range helper */
extern uint64_t FUN_0034d8d4();  /* out-of-range helper */
extern uint64_t FUN_0034d944();  /* out-of-range helper */
extern uint64_t FUN_0034da98();  /* out-of-range helper */
extern uint64_t FUN_0034db58();  /* out-of-range helper */
extern uint64_t FUN_0034dba8();  /* out-of-range helper */
extern uint64_t FUN_0034dbb8();  /* out-of-range helper */
extern uint64_t FUN_0034dc9c();  /* out-of-range helper */
extern uint64_t FUN_0034de34();  /* out-of-range helper */
extern uint64_t FUN_0034df34();  /* out-of-range helper */
extern uint64_t FUN_0034dfa4();  /* out-of-range helper */
extern uint64_t FUN_0034dfc4();  /* out-of-range helper */
extern uint64_t FUN_0034e2b8();  /* out-of-range helper */
extern uint64_t FUN_0034e414();  /* out-of-range helper */
extern uint64_t FUN_0034e474();  /* out-of-range helper */
extern uint64_t FUN_0034e4a4();  /* out-of-range helper */
extern uint64_t FUN_0034e53c();  /* out-of-range helper */
extern uint64_t FUN_0034e55c();  /* out-of-range helper */
extern uint64_t FUN_0034e5fc();  /* out-of-range helper */
extern uint64_t FUN_0034e69c();  /* out-of-range helper */
extern uint64_t FUN_0034e6cc();  /* out-of-range helper */
extern uint64_t FUN_0034e6ec();  /* out-of-range helper */
extern uint64_t FUN_0034e70c();  /* out-of-range helper */
extern uint64_t FUN_0034ea40();  /* out-of-range helper */
extern uint64_t FUN_0034ed08();  /* out-of-range helper */
extern uint64_t FUN_0034ed28();  /* out-of-range helper */
extern uint64_t FUN_0034ed88();  /* out-of-range helper */
extern uint64_t FUN_0034edc8();  /* out-of-range helper */
extern uint64_t FUN_0034edd8();  /* out-of-range helper */
extern uint64_t FUN_0034ede8();  /* out-of-range helper */
extern uint64_t FUN_0034ee28();  /* out-of-range helper */
extern uint64_t FUN_0034ee48();  /* out-of-range helper */
extern uint64_t FUN_0034f1a8();  /* out-of-range helper */
extern uint64_t FUN_0034f2e4();  /* out-of-range helper */
extern uint64_t FUN_0034f414();  /* out-of-range helper */
extern uint64_t FUN_0034f604();  /* out-of-range helper */
extern uint64_t FUN_0034f860();  /* out-of-range helper */
extern uint64_t FUN_0034fa4c();  /* out-of-range helper */
extern uint64_t FUN_0034fce4();  /* out-of-range helper */
extern uint64_t FUN_0034ff98();  /* out-of-range helper */
extern uint64_t FUN_00350404();  /* out-of-range helper */
extern uint64_t FUN_00350410();  /* out-of-range helper */
extern uint64_t FUN_00350428();  /* out-of-range helper */
extern uint64_t FUN_00350464();  /* out-of-range helper */
extern uint64_t FUN_00350470();  /* out-of-range helper */
extern uint64_t FUN_00350488();  /* out-of-range helper */
extern uint64_t FUN_00350494();  /* out-of-range helper */
extern uint64_t FUN_003504b8();  /* out-of-range helper */
extern uint64_t FUN_003504c4();  /* out-of-range helper */
extern uint64_t FUN_0035050c();  /* out-of-range helper */
extern uint64_t FUN_00350518();  /* out-of-range helper */
extern uint64_t FUN_00350530();  /* out-of-range helper */
extern uint64_t FUN_00350548();  /* out-of-range helper */
extern uint64_t FUN_00350560();  /* out-of-range helper */
extern uint64_t FUN_0035056c();  /* out-of-range helper */
extern uint64_t FUN_003505c4();  /* out-of-range helper */
extern uint64_t FUN_003505d0();  /* out-of-range helper */
extern uint64_t FUN_00350600();  /* out-of-range helper */
extern uint64_t FUN_0035060c();  /* out-of-range helper */
extern uint64_t FUN_00350618();  /* out-of-range helper */
extern uint64_t FUN_00350624();  /* out-of-range helper */
extern uint64_t FUN_00350630();  /* out-of-range helper */
extern uint64_t FUN_0035063c();  /* out-of-range helper */
extern uint64_t FUN_00350678();  /* out-of-range helper */
extern uint64_t FUN_003506b0();  /* out-of-range helper */
extern uint64_t FUN_00350738();  /* out-of-range helper */
extern uint64_t FUN_00350768();  /* out-of-range helper */
extern uint64_t FUN_00350798();  /* out-of-range helper */
extern uint64_t FUN_003507bc();  /* out-of-range helper */
extern uint64_t FUN_003507d4();  /* out-of-range helper */
extern uint64_t FUN_003507e0();  /* out-of-range helper */
extern uint64_t FUN_0035084c();  /* out-of-range helper */
extern uint64_t FUN_00350878();  /* out-of-range helper */
extern uint64_t FUN_00350884();  /* out-of-range helper */
extern uint64_t FUN_003508a8();  /* out-of-range helper */
extern uint64_t FUN_003508b4();  /* out-of-range helper */
extern uint64_t FUN_003508c0();  /* out-of-range helper */
extern uint64_t FUN_003508cc();  /* out-of-range helper */
extern uint64_t FUN_003508e4();  /* out-of-range helper */
extern uint64_t FUN_003508f0();  /* out-of-range helper */
extern uint64_t FUN_00350914();  /* out-of-range helper */
extern uint64_t FUN_00350920();  /* out-of-range helper */
extern uint64_t FUN_00350944();  /* out-of-range helper */
extern uint64_t FUN_00350950();  /* out-of-range helper */
extern uint64_t FUN_00350974();  /* out-of-range helper */
extern uint64_t FUN_00350980();  /* out-of-range helper */
extern uint64_t FUN_0035098c();  /* out-of-range helper */
extern uint64_t FUN_003509b0();  /* out-of-range helper */
extern uint64_t FUN_003509c8();  /* out-of-range helper */
extern uint64_t FUN_00350a04();  /* out-of-range helper */
extern uint64_t FUN_00350a28();  /* out-of-range helper */
extern uint64_t FUN_00350a34();  /* out-of-range helper */
extern uint64_t FUN_00350a64();  /* out-of-range helper */
extern uint64_t FUN_00350aa0();  /* out-of-range helper */
extern uint64_t FUN_00350ac4();  /* out-of-range helper */
extern uint64_t FUN_00350ad0();  /* out-of-range helper */
extern uint64_t FUN_00350b0c();  /* out-of-range helper */
extern uint64_t FUN_00350bc0();  /* out-of-range helper */
extern uint64_t FUN_00350bd8();  /* out-of-range helper */
extern uint64_t FUN_00350bf0();  /* out-of-range helper */
extern uint64_t FUN_00350bfc();  /* out-of-range helper */
extern uint64_t FUN_00350c2c();  /* out-of-range helper */
extern uint64_t FUN_00350c38();  /* out-of-range helper */
extern uint64_t FUN_00350c68();  /* out-of-range helper */
extern uint64_t FUN_00350c80();  /* out-of-range helper */
extern uint64_t FUN_00350df4();  /* out-of-range helper */
extern uint64_t FUN_00350e24();  /* out-of-range helper */
extern uint64_t FUN_00350ed0();  /* out-of-range helper */
extern uint64_t FUN_0035102c();  /* out-of-range helper */
extern uint64_t FUN_003510a0();  /* out-of-range helper */
extern uint64_t FUN_003510ac();  /* out-of-range helper */
extern uint64_t FUN_003510d0();  /* out-of-range helper */
extern uint64_t FUN_003510dc();  /* out-of-range helper */
extern uint64_t FUN_003510e8();  /* out-of-range helper */
extern uint64_t FUN_0035110c();  /* out-of-range helper */
extern uint64_t FUN_00351130();  /* out-of-range helper */
extern uint64_t FUN_0035113c();  /* out-of-range helper */
extern uint64_t FUN_003511a8();  /* out-of-range helper */
extern uint64_t FUN_00351214();  /* out-of-range helper */
extern uint64_t FUN_0035122c();  /* out-of-range helper */
extern uint64_t FUN_0035125c();  /* out-of-range helper */
extern uint64_t FUN_00351274();  /* out-of-range helper */
extern uint64_t FUN_00351318();  /* out-of-range helper */
extern uint64_t FUN_00351348();  /* out-of-range helper */
extern uint64_t FUN_00351354();  /* out-of-range helper */
extern uint64_t FUN_00351360();  /* out-of-range helper */
extern uint64_t FUN_0035136c();  /* out-of-range helper */
extern uint64_t FUN_00351384();  /* out-of-range helper */
extern uint64_t FUN_003513a8();  /* out-of-range helper */
extern uint64_t FUN_003513d8();  /* out-of-range helper */
extern uint64_t FUN_003513f0();  /* out-of-range helper */
extern uint64_t FUN_00351450();  /* out-of-range helper */
extern uint64_t FUN_00351488();  /* out-of-range helper */
extern uint64_t FUN_00351494();  /* out-of-range helper */
extern uint64_t FUN_003514b8();  /* out-of-range helper */
extern uint64_t FUN_003514d0();  /* out-of-range helper */
extern uint64_t FUN_003515b4();  /* out-of-range helper */
extern uint64_t FUN_003515cc();  /* out-of-range helper */
extern uint64_t FUN_003515f0();  /* out-of-range helper */
extern uint64_t FUN_003515fc();  /* out-of-range helper */
extern uint64_t FUN_00351624();  /* out-of-range helper */
extern uint64_t FUN_00351648();  /* out-of-range helper */
extern uint64_t FUN_00351654();  /* out-of-range helper */
extern uint64_t FUN_003516a8();  /* out-of-range helper */
extern uint64_t FUN_003516cc();  /* out-of-range helper */
extern uint64_t FUN_003516d8();  /* out-of-range helper */
extern uint64_t FUN_0035172c();  /* out-of-range helper */
extern uint64_t FUN_00351738();  /* out-of-range helper */
extern uint64_t FUN_003517b4();  /* out-of-range helper */
extern uint64_t FUN_00351888();  /* out-of-range helper */
extern uint64_t FUN_003518a0();  /* out-of-range helper */
extern uint64_t FUN_003518b8();  /* out-of-range helper */
extern uint64_t FUN_0035196c();  /* out-of-range helper */
extern uint64_t FUN_00351990();  /* out-of-range helper */
extern uint64_t FUN_0035199c();  /* out-of-range helper */
extern uint64_t FUN_003519c0();  /* out-of-range helper */
extern uint64_t FUN_00351ab0();  /* out-of-range helper */
extern uint64_t FUN_00351ad4();  /* out-of-range helper */
extern uint64_t FUN_00351aec();  /* out-of-range helper */
extern uint64_t FUN_00351b20();  /* out-of-range helper */
extern uint64_t FUN_00351b60();  /* out-of-range helper */
extern uint64_t FUN_00351b78();  /* out-of-range helper */
extern uint64_t FUN_00351bec();  /* out-of-range helper */
extern uint64_t FUN_00351c10();  /* out-of-range helper */
extern uint64_t FUN_00351c88();  /* out-of-range helper */
extern uint64_t FUN_00351cc4();  /* out-of-range helper */
extern uint64_t FUN_00351cf4();  /* out-of-range helper */
extern uint64_t FUN_00351d00();  /* out-of-range helper */
extern uint64_t FUN_00351d18();  /* out-of-range helper */
extern uint64_t FUN_00351dfc();  /* out-of-range helper */
extern uint64_t FUN_00351e14();  /* out-of-range helper */
extern uint64_t FUN_00351e3c();  /* out-of-range helper */
extern uint64_t FUN_00351e54();  /* out-of-range helper */
extern uint64_t FUN_00351ea8();  /* out-of-range helper */
extern uint64_t FUN_00351ef8();  /* out-of-range helper */
extern uint64_t FUN_00351f34();  /* out-of-range helper */
extern uint64_t FUN_00351f40();  /* out-of-range helper */
extern uint64_t FUN_00351f4c();  /* out-of-range helper */
extern uint64_t FUN_00352018();  /* out-of-range helper */
extern uint64_t FUN_00352068();  /* out-of-range helper */
extern uint64_t FUN_00352078();  /* out-of-range helper */
extern uint64_t FUN_0035215c();  /* out-of-range helper */
extern uint64_t FUN_0035216c();  /* out-of-range helper */
extern uint64_t FUN_00352194();  /* out-of-range helper */
extern uint64_t FUN_00352290();  /* out-of-range helper */
extern uint64_t FUN_00352370();  /* out-of-range helper */
extern uint64_t FUN_00352414();  /* out-of-range helper */
extern uint64_t FUN_00352420();  /* out-of-range helper */
extern uint64_t FUN_00352474();  /* out-of-range helper */
extern uint64_t FUN_003524a4();  /* out-of-range helper */
extern uint64_t FUN_003524bc();  /* out-of-range helper */
extern uint64_t FUN_00352554();  /* out-of-range helper */
extern uint64_t FUN_0035261c();  /* out-of-range helper */
extern uint64_t FUN_00352680();  /* out-of-range helper */
extern uint64_t FUN_00352700();  /* out-of-range helper */
extern uint64_t FUN_00352800();  /* out-of-range helper */
extern uint64_t FUN_00352834();  /* out-of-range helper */
extern uint64_t FUN_00352840();  /* out-of-range helper */
extern uint64_t FUN_00352870();  /* out-of-range helper */
extern uint64_t FUN_003528b8();  /* out-of-range helper */
extern uint64_t FUN_00352914();  /* out-of-range helper */
extern uint64_t FUN_0035295c();  /* out-of-range helper */
extern uint64_t FUN_003529a4();  /* out-of-range helper */
extern uint64_t FUN_00352a28();  /* out-of-range helper */
extern uint64_t FUN_00352a34();  /* out-of-range helper */
extern uint64_t FUN_00352a64();  /* out-of-range helper */
extern uint64_t FUN_00352b14();  /* out-of-range helper */
extern uint64_t FUN_00352b98();  /* out-of-range helper */
extern uint64_t FUN_00352bec();  /* out-of-range helper */
extern uint64_t FUN_00352c10();  /* out-of-range helper */
extern uint64_t FUN_00352c1c();  /* out-of-range helper */
extern uint64_t FUN_00352c28();  /* out-of-range helper */
extern uint64_t FUN_00352c34();  /* out-of-range helper */
extern uint64_t FUN_00352ce0();  /* out-of-range helper */
extern uint64_t FUN_00352cec();  /* out-of-range helper */
extern uint64_t FUN_00352d10();  /* out-of-range helper */
extern uint64_t FUN_00352ddc();  /* out-of-range helper */
extern uint64_t FUN_00352eb4();  /* out-of-range helper */
extern uint64_t FUN_00352ecc();  /* out-of-range helper */
extern uint64_t FUN_00352ee4();  /* out-of-range helper */
extern uint64_t FUN_00352efc();  /* out-of-range helper */
extern uint64_t FUN_00353034();  /* out-of-range helper */
extern uint64_t FUN_003530e8();  /* out-of-range helper */
extern uint64_t FUN_003530f4();  /* out-of-range helper */
extern uint64_t FUN_00353100();  /* out-of-range helper */
extern uint64_t FUN_0035310c();  /* out-of-range helper */
extern uint64_t FUN_0035313c();  /* out-of-range helper */
extern uint64_t FUN_00353148();  /* out-of-range helper */
extern uint64_t FUN_00353154();  /* out-of-range helper */
extern uint64_t FUN_003531a8();  /* out-of-range helper */
extern uint64_t FUN_0035339c();  /* out-of-range helper */
extern uint64_t FUN_003535a8();  /* out-of-range helper */
extern uint64_t FUN_003537fc();  /* out-of-range helper */
extern uint64_t FUN_0035396c();  /* out-of-range helper */
extern uint64_t FUN_00353978();  /* out-of-range helper */
extern uint64_t FUN_0035399c();  /* out-of-range helper */
extern uint64_t FUN_00353a00();  /* out-of-range helper */
extern uint64_t FUN_00353a30();  /* out-of-range helper */
extern uint64_t FUN_00353aa0();  /* out-of-range helper */
extern uint64_t FUN_00353b10();  /* out-of-range helper */
extern uint64_t FUN_00353b58();  /* out-of-range helper */
extern uint64_t FUN_00353ba0();  /* out-of-range helper */
extern uint64_t FUN_00353be8();  /* out-of-range helper */
extern uint64_t FUN_00353bf4();  /* out-of-range helper */
extern uint64_t FUN_00353c18();  /* out-of-range helper */
extern uint64_t FUN_00353c24();  /* out-of-range helper */
extern uint64_t FUN_00353c48();  /* out-of-range helper */
extern uint64_t FUN_00353c6c();  /* out-of-range helper */
extern uint64_t FUN_00353cfc();  /* out-of-range helper */
extern uint64_t FUN_00353d14();  /* out-of-range helper */
extern uint64_t FUN_00353d70();  /* out-of-range helper */
extern uint64_t FUN_00353d94();  /* out-of-range helper */
extern uint64_t FUN_00353dd0();  /* out-of-range helper */
extern uint64_t FUN_00353ee4();  /* out-of-range helper */
extern uint64_t FUN_00353fa0();  /* out-of-range helper */
extern uint64_t FUN_0035401c();  /* out-of-range helper */
extern uint64_t FUN_00354128();  /* out-of-range helper */
extern uint64_t FUN_00354324();  /* out-of-range helper */
extern uint64_t FUN_003544c8();  /* out-of-range helper */
extern uint64_t FUN_00354534();  /* out-of-range helper */
extern uint64_t FUN_0035454c();  /* out-of-range helper */
extern uint64_t FUN_00354558();  /* out-of-range helper */
extern uint64_t FUN_00354618();  /* out-of-range helper */
extern uint64_t FUN_00354744();  /* out-of-range helper */
extern uint64_t FUN_00354834();  /* out-of-range helper */
extern uint64_t FUN_003548b8();  /* out-of-range helper */
extern uint64_t FUN_003548f4();  /* out-of-range helper */
extern uint64_t FUN_00354924();  /* out-of-range helper */
extern uint64_t FUN_00354930();  /* out-of-range helper */
extern uint64_t FUN_00354948();  /* out-of-range helper */
extern uint64_t FUN_00354a34();  /* out-of-range helper */
extern uint64_t FUN_00354a84();  /* out-of-range helper */
extern uint64_t FUN_00354b74();  /* out-of-range helper */
extern uint64_t FUN_00354bbc();  /* out-of-range helper */
extern uint64_t FUN_00354d14();  /* out-of-range helper */
extern uint64_t FUN_00354d44();  /* out-of-range helper */
extern uint64_t FUN_00354ef8();  /* out-of-range helper */
extern uint64_t FUN_00354ff4();  /* out-of-range helper */
extern uint64_t FUN_0035512c();  /* out-of-range helper */
extern uint64_t FUN_0035516c();  /* out-of-range helper */
extern uint64_t FUN_003551f8();  /* out-of-range helper */
extern uint64_t FUN_003552a0();  /* out-of-range helper */
extern uint64_t FUN_003552f0();  /* out-of-range helper */
extern uint64_t FUN_003553d8();  /* out-of-range helper */
extern uint64_t FUN_00355418();  /* out-of-range helper */
extern uint64_t FUN_00355458();  /* out-of-range helper */
extern uint64_t FUN_00355544();  /* out-of-range helper */
extern uint64_t FUN_00355610();  /* out-of-range helper */
extern uint64_t FUN_00355694();  /* out-of-range helper */
extern uint64_t FUN_003556f4();  /* out-of-range helper */
extern uint64_t FUN_00355adc();  /* out-of-range helper */
extern uint64_t FUN_00355b10();  /* out-of-range helper */
extern uint64_t FUN_00355c1c();  /* out-of-range helper */
extern uint64_t FUN_00355c28();  /* out-of-range helper */
extern uint64_t FUN_00355ce4();  /* out-of-range helper */
extern uint64_t FUN_00355d40();  /* out-of-range helper */
extern uint64_t FUN_00355dd8();  /* out-of-range helper */
extern uint64_t FUN_00355e68();  /* out-of-range helper */
extern uint64_t FUN_00355eec();  /* out-of-range helper */
extern uint64_t FUN_003560a8();  /* out-of-range helper */
extern uint64_t FUN_00356260();  /* out-of-range helper */
extern uint64_t FUN_00356284();  /* out-of-range helper */
extern uint64_t FUN_00356328();  /* out-of-range helper */
extern uint64_t FUN_0035647c();  /* out-of-range helper */
extern uint64_t FUN_00356688();  /* out-of-range helper */
extern uint64_t FUN_00356810();  /* out-of-range helper */
extern uint64_t FUN_0035687c();  /* out-of-range helper */
extern uint64_t FUN_00356940();  /* out-of-range helper */
extern uint64_t FUN_0035694c();  /* out-of-range helper */
extern uint64_t FUN_00356aac();  /* out-of-range helper */
extern uint64_t FUN_00356ab8();  /* out-of-range helper */
extern uint64_t FUN_00356b5c();  /* out-of-range helper */
extern uint64_t FUN_00356ba4();  /* out-of-range helper */
extern uint64_t FUN_00356bb0();  /* out-of-range helper */
extern uint64_t FUN_00356bf8();  /* out-of-range helper */
extern uint64_t FUN_00356d20();  /* out-of-range helper */
extern uint64_t FUN_00356fcc();  /* out-of-range helper */
extern uint64_t FUN_00357050();  /* out-of-range helper */
extern uint64_t FUN_00357170();  /* out-of-range helper */
extern uint64_t FUN_00357274();  /* out-of-range helper */
extern uint64_t FUN_00357280();  /* out-of-range helper */
extern uint64_t FUN_00357344();  /* out-of-range helper */
extern uint64_t FUN_00357398();  /* out-of-range helper */
extern uint64_t FUN_003573c0();  /* out-of-range helper */
extern uint64_t FUN_00357400();  /* out-of-range helper */
extern uint64_t FUN_00357540();  /* out-of-range helper */
extern uint64_t FUN_00357670();  /* out-of-range helper */
extern uint64_t FUN_00357688();  /* out-of-range helper */
extern uint64_t FUN_003578b4();  /* out-of-range helper */
extern uint64_t FUN_00357ab4();  /* out-of-range helper */
extern uint64_t FUN_00357aec();  /* out-of-range helper */
extern uint64_t FUN_00357b04();  /* out-of-range helper */
extern uint64_t FUN_00357b2c();  /* out-of-range helper */
extern uint64_t FUN_00357c74();  /* out-of-range helper */
extern uint64_t FUN_00357cb4();  /* out-of-range helper */
extern uint64_t FUN_00357e84();  /* out-of-range helper */
extern uint64_t FUN_00357f14();  /* out-of-range helper */
extern uint64_t FUN_00357f24();  /* out-of-range helper */
extern uint64_t FUN_00357f84();  /* out-of-range helper */
extern uint64_t FUN_00358054();  /* out-of-range helper */
extern uint64_t FUN_003582f8();  /* out-of-range helper */
extern uint64_t FUN_003584b4();  /* out-of-range helper */
extern uint64_t FUN_003585f4();  /* out-of-range helper */
extern uint64_t FUN_00358834();  /* out-of-range helper */
extern uint64_t FUN_00358864();  /* out-of-range helper */
extern uint64_t FUN_00358888();  /* out-of-range helper */
extern uint64_t FUN_00358930();  /* out-of-range helper */
extern uint64_t FUN_003589fc();  /* out-of-range helper */
extern uint64_t FUN_00358a50();  /* out-of-range helper */
extern uint64_t FUN_00358aa4();  /* out-of-range helper */
extern uint64_t FUN_00358b54();  /* out-of-range helper */
extern uint64_t FUN_00358bc0();  /* out-of-range helper */
extern uint64_t FUN_00358c2c();  /* out-of-range helper */
extern uint64_t FUN_00358c50();  /* out-of-range helper */
extern uint64_t FUN_00358cd4();  /* out-of-range helper */
extern uint64_t FUN_00358e0c();  /* out-of-range helper */
extern uint64_t FUN_00358ea0();  /* out-of-range helper */
extern uint64_t FUN_00358f90();  /* out-of-range helper */
extern uint64_t FUN_003590cc();  /* out-of-range helper */
extern uint64_t FUN_00359350();  /* out-of-range helper */
extern uint64_t FUN_00359398();  /* out-of-range helper */
extern uint64_t FUN_00359490();  /* out-of-range helper */
extern uint64_t FUN_0035949c();  /* out-of-range helper */
extern uint64_t FUN_00359594();  /* out-of-range helper */
extern uint64_t FUN_003595a8();  /* out-of-range helper */
extern uint64_t FUN_003595d8();  /* out-of-range helper */
extern uint64_t FUN_00359634();  /* out-of-range helper */
extern uint64_t FUN_00359678();  /* out-of-range helper */
extern uint64_t FUN_003597b4();  /* out-of-range helper */
extern uint64_t FUN_00359804();  /* out-of-range helper */
extern uint64_t FUN_00359874();  /* out-of-range helper */
extern uint64_t FUN_00359894();  /* out-of-range helper */
extern uint64_t FUN_003598cc();  /* out-of-range helper */
extern uint64_t FUN_003598ec();  /* out-of-range helper */
extern uint64_t FUN_00359920();  /* out-of-range helper */
extern uint64_t FUN_0035992c();  /* out-of-range helper */
extern uint64_t FUN_00359a04();  /* out-of-range helper */
extern uint64_t FUN_00359aec();  /* out-of-range helper */
extern uint64_t FUN_00359bec();  /* out-of-range helper */
extern uint64_t FUN_00359c58();  /* out-of-range helper */
extern uint64_t FUN_00359d38();  /* out-of-range helper */
extern uint64_t FUN_00359e60();  /* out-of-range helper */
extern uint64_t FUN_00359f08();  /* out-of-range helper */
extern uint64_t FUN_00359f14();  /* out-of-range helper */
extern uint64_t FUN_00359f8c();  /* out-of-range helper */
extern uint64_t FUN_00359fa0();  /* out-of-range helper */
extern uint64_t FUN_0035a190();  /* out-of-range helper */
extern uint64_t FUN_0035a1d4();  /* out-of-range helper */
extern uint64_t FUN_0035a274();  /* out-of-range helper */
extern uint64_t FUN_0035a4bc();  /* out-of-range helper */
extern uint64_t FUN_0035a59c();  /* out-of-range helper */
extern uint64_t FUN_0035a7c0();  /* out-of-range helper */
extern uint64_t FUN_0035a7d4();  /* out-of-range helper */
extern uint64_t FUN_0035a830();  /* out-of-range helper */
extern uint64_t FUN_0035a960();  /* out-of-range helper */
extern uint64_t FUN_00365b6c();  /* out-of-range helper */
extern uint64_t FUN_0036a908();  /* out-of-range helper */
extern uint64_t FUN_0036b118();  /* out-of-range helper */
extern uint64_t FUN_0036b270();  /* out-of-range helper */
extern uint64_t FUN_0036b6ac();  /* out-of-range helper */
extern uint64_t FUN_003722e4();  /* out-of-range helper */
extern uint64_t FUN_00376820();  /* out-of-range helper */
extern uint64_t FUN_00377824();  /* out-of-range helper */
extern uint64_t FUN_00377bec();  /* out-of-range helper */
extern uint64_t FUN_003a25d4();  /* out-of-range helper */
extern uint64_t FUN_003a25e0();  /* out-of-range helper */
extern uint64_t FUN_003a261c();  /* out-of-range helper */
extern uint64_t thunk_FUN_00012568();  /* out-of-range helper */
extern uint64_t thunk_FUN_0006e06c();  /* out-of-range helper */
extern uint64_t thunk_FUN_002298d4();  /* out-of-range helper */
extern uint64_t thunk_FUN_0025baa4();  /* out-of-range helper */
extern uint64_t thunk_FUN_0025bae0();  /* out-of-range helper */
extern uint64_t thunk_FUN_0025bca4();  /* out-of-range helper */
extern uint64_t thunk_FUN_002608cc();  /* out-of-range helper */
extern uint64_t thunk_FUN_00355354();  /* out-of-range helper */
extern uint64_t thunk_FUN_0036b270();  /* out-of-range helper */

/* In-range functions owned by sibling slices (not in slice_00). */
extern uint64_t FUN_00284424();  /* sibling slice */

/* Global object-method dispatch slot (DAT_00658c00) - unspecified-arity fn pointer. */
extern uint64_t (*DAT_00658c00)();

/* Forward declarations (functions reconstructed in this file, cross-referenced).
 * In-slice functions are register-passed (decompiler models many as `(void)`);
 * declared with unspecified arity so any observed call pattern compiles. */
void FUN_00286c10();
void FUN_002871cc();
long FUN_00287794(long, long, word_t);
void FUN_00287d34();
void FUN_00288a80();
void FUN_002890d8();
void FUN_0028b918();
word_t FUN_0028d1a8();
void FUN_0028adc4();
uint8_t *FUN_00287e30(long *, word_t, word_t, word_t, long, word_t);
void thunk_FUN_00287c68();
void FUN_00288910();
void FUN_002884a0();
word_t FUN_00287f6c();
void FUN_00288f34();
word_t *FUN_00288954();
word_t FUN_00289bdc();
word_t FUN_00289eac();
word_t FUN_00289ce8();
void FUN_0028a65c();
word_t FUN_0028a0d4();
word_t FUN_0028a644();
void FUN_0028a6f4();
word_t FUN_0028aad4();
void FUN_0028ac40();
void FUN_0028b31c();
void FUN_0028bdc0();
void FUN_0028beec();
void FUN_0028c808();
void FUN_0028c7d8();
void FUN_0028d6e8();
void FUN_0028cd14();
uint8_t *FUN_0028d270();

/* ====================================================================== *
 *  Swift collection / string primitives (0x28279c - 0x283344)
 * ====================================================================== */

/*--------------------------------------------------------------------*
 * FUN_0028279c @ 0x0028279c   (est. sk_swift_array_remove_reduce)
 * Ghidra: long FUN_0028279c(undefined8,undefined4*,long,undefined8,undefined8,ulong,ulong)
 * Swift Array value-reduction: iterates a count-long destination window,
 * pulling each element from a source sequence through the DAT_00658c00
 * dispatch slot, folding into out_words.  When the source is exhausted it
 * walks a backing ContiguousArrayBuffer removing the last element (a
 * removeLast-style teardown), trapping on empty/out-of-range access.
 * Confidence: low (Swift Array/Sequence reduce; indirect dispatch).
 * Notes: helpers FUN_0026bd30 (range), FUN_0026398c/00263e20/00262e9c
 *   (sequence next), FUN_0019e644 (buffer copy), FUN_00117cc4 (memcpy). */
long FUN_0028279c(word_t thisp, uint32_t *out_words, long count, word_t p4,
                  word_t p5, word_t p6, word_t p7)
{
    bool keep;
    uint32_t a, b;
    uint16_t c, d;
    char e;
    long i7, i15, i16, i17;
    word_t u8, u11, u13, u14;
    void *pu9;
    char *msg, *ty;
    word_t buf_a, buf_b, buf_c, buf_d;
    uint16_t hdr;
    uint8_t f9e;
    uint8_t f98;
    void *f90;
    uint8_t f88;
    word_t f84;
    void *f78;
    uint8_t f70;
    uint32_t f6c;
    char f68;

    u14 = p6;
    if ((p7 & 0x2000000000000000ull) != 0)
        u14 = p7;
    f9e = (uint8_t)(u14 >> 0x3e) & 1;
    hdr = 1;
    f98 = 1;
    f90 = (void *)0x657778;
    f88 = 0;
    f84 = 0x1000000000000ull;
    f78 = (void *)0x657778;
    f70 = 0;
    f6c = 0;
    f68 = 1;
    buf_a = p4;
    buf_b = p5;
    buf_c = p6;
    buf_d = p7;
    if (out_words == 0) {
        i16 = 0;
    } else {
        wpair_t r = { 0, 0 };
        /* FUN_0026bd30(0, count) -> {lo,hi} range */
        i16 = count;
        i7 = (long)(FUN_0026bd30(0, count) & 0xff);
        (void)r;
        for (; i7 != (long)((FUN_0026bd30(0, count) >> 8) & 0xff); i7++) {
            i16 = count;
            if (((long)((FUN_0026bd30(0, count) >> 8) & 0xff) <= i7)) {
                msg = "Index out of range";
                ty = "Swift.Range";
                SWF_FATAL(msg, 0x12, ty, 0x11, 0x136);
                __builtin_trap();
            }
            (*DAT_00658c00)();
            if ((hdr & 0xff00) == 0x0100) {
                /* LAB_00282914 */
                hdr = (uint16_t)(((hdr & 0xff) << 8) | 1);
                i16 = i7;
                if ((f9e & 1) != 0) break;
                u8 = FUN_0026398c(&hdr);
                e = f68;
                u14 = u8;
                if ((u8 & 0xff00000000ull) == 0x100000000ull) {
                    u14 = (word_t)f6c;
                    f6c = (uint32_t)u8;
                    f68 = 1;
                    if (e == 1) {
                        i15 = *(long *)(f78 + 0x10);
                        if (i15 == 0) { f70 = 0; break; }
                        if ((f70 & 1) == 0) {
                            u14 = i15 - 1;
                            if (u14 != 0) {
                                i17 = 0;
                                i16 = i15 * 8 + 0x1c;
                                i15 = 1;
                                do {
                                    pu9 = f78;
                                    if ((*(unsigned long *)(f78 + 0x10) <= i15 - 1u) ||
                                        (*(unsigned long *)(f78 + 0x10) <= u14)) {
                                        msg = "Index out of range";
                                        ty = "Swift.ContiguousArrayBuffer";
                                        SWF_FATAL(msg, 0x12, ty, 0x21, 0x136);
                                        __builtin_trap();
                                    }
                                    a = *(uint32_t *)(f78 + i17 + 0x20);
                                    c = *(uint16_t *)(f78 + i17 + 0x24);
                                    b = *(uint32_t *)((long)(f78 + i16) + -4);
                                    d = *(uint16_t *)(f78 + i16);
                                    u8 = FUN_003a261c(f78);
                                    if ((u8 & 1) == 0) {
                                        f78 = pu9;
                                        pu9 = (void *)FUN_0019e644(pu9);
                                    }
                                    *(uint32_t *)(pu9 + i17 + 0x20) = b;
                                    *(uint16_t *)(pu9 + i17 + 0x24) = d;
                                    *(uint32_t *)((long)(pu9 + i16) + -4) = a;
                                    *(uint16_t *)(pu9 + i16) = c;
                                    u14 = u14 - 1;
                                    i16 = i16 - 8;
                                    i17 = i17 + 8;
                                    keep = i15 < (long)u14;
                                    i15 = i15 + 1;
                                    f78 = pu9;
                                } while (keep);
                            }
                            f70 = 1;
                            if (*(long *)(f78 + 0x10) == 0) {
                                msg = "Can't removeLast element from a";
                                ty = "Swift.RangeReplaceableCollection";
                                SWF_FATAL(msg, 0x32, ty, 0x26, 0x136);
                                __builtin_trap();
                            }
                        }
                        pu9 = f78;
                        u14 = FUN_003a261c(f78);
                        if ((u14 & 1) == 0) {
                            f78 = pu9;
                            pu9 = (void *)FUN_0019e644(pu9);
                        }
                        f78 = pu9;
                        if (*(long *)(pu9 + 0x10) == 0) {
                            msg = "Can't removeLast from an empty Array";
                            ty = "Swift.Array";
                            SWF_FATAL(msg, 0x24, ty, 0x11, 0x136);
                            __builtin_trap();
                        }
                        i16 = *(long *)(pu9 + 0x10) + -1;
                        u14 = (word_t)*(uint32_t *)(pu9 + i16 * 8 + 0x20);
                        *(long *)(pu9 + 0x10) = i16;
                    }
                }
            } else {
                if ((f9e & 1) == 0)
                    u14 = FUN_00263e20(&hdr, (void *)0x346964);
                else
                    u14 = FUN_00262e9c(&buf_a);
                if ((u14 & 0xff00000000ull) == 0x100000000ull) goto label_2914;
            }
            *out_words = (uint32_t)u14;
            out_words++;
            continue;
        label_2914:
            /* hdr high byte set path; continue outer */
            hdr = (uint16_t)(((hdr & 0xff) << 8) | 1);
            i16 = i7;
            if ((f9e & 1) != 0) break;
            u8 = FUN_0026398c(&hdr);
            e = f68;
            u14 = u8;
            if ((u8 & 0xff00000000ull) == 0x100000000ull) {
                u14 = (word_t)f6c;
                f6c = (uint32_t)u8;
                f68 = 1;
                if (e == 1) {
                    i15 = *(long *)(f78 + 0x10);
                    if (i15 == 0) { f70 = 0; break; }
                    if ((f70 & 1) == 0) {
                        u14 = i15 - 1;
                        if (u14 != 0) {
                            i17 = 0;
                            i16 = i15 * 8 + 0x1c;
                            i15 = 1;
                            do {
                                pu9 = f78;
                                if ((*(unsigned long *)(f78 + 0x10) <= i15 - 1u) ||
                                    (*(unsigned long *)(f78 + 0x10) <= u14)) {
                                    msg = "Index out of range";
                                    ty = "Swift.ContiguousArrayBuffer";
                                    SWF_FATAL(msg, 0x12, ty, 0x21, 0x136);
                                    __builtin_trap();
                                }
                                a = *(uint32_t *)(f78 + i17 + 0x20);
                                c = *(uint16_t *)(f78 + i17 + 0x24);
                                b = *(uint32_t *)((long)(f78 + i16) + -4);
                                d = *(uint16_t *)(f78 + i16);
                                u8 = FUN_003a261c(f78);
                                if ((u8 & 1) == 0) {
                                    f78 = pu9;
                                    pu9 = (void *)FUN_0019e644(pu9);
                                }
                                *(uint32_t *)(pu9 + i17 + 0x20) = b;
                                *(uint16_t *)(pu9 + i17 + 0x24) = d;
                                *(uint32_t *)((long)(pu9 + i16) + -4) = a;
                                *(uint16_t *)(pu9 + i16) = c;
                                u14 = u14 - 1;
                                i16 = i16 - 8;
                                i17 = i17 + 8;
                                keep = i15 < (long)u14;
                                i15 = i15 + 1;
                                f78 = pu9;
                            } while (keep);
                        }
                        f70 = 1;
                        if (*(long *)(f78 + 0x10) == 0) {
                            msg = "Can't removeLast element from a";
                            ty = "Swift.RangeReplaceableCollection";
                            SWF_FATAL(msg, 0x32, ty, 0x26, 0x136);
                            __builtin_trap();
                        }
                    }
                    pu9 = f78;
                    u14 = FUN_003a261c(f78);
                    if ((u14 & 1) == 0) {
                        f78 = pu9;
                        pu9 = (void *)FUN_0019e644(pu9);
                    }
                    f78 = pu9;
                    if (*(long *)(pu9 + 0x10) == 0) {
                        msg = "Can't removeLast from an empty Array";
                        ty = "Swift.Array";
                        SWF_FATAL(msg, 0x24, ty, 0x11, 0x136);
                        __builtin_trap();
                    }
                    i16 = *(long *)(pu9 + 0x10) + -1;
                    u14 = (word_t)*(uint32_t *)(pu9 + i16 * 8 + 0x20);
                    *(long *)(pu9 + 0x10) = i16;
                }
            }
            *out_words = (uint32_t)u14;
            out_words++;
        }
    }
    FUN_00117cc4((void *)thisp, &buf_a, 0x61);
    return i16;
}

/*--------------------------------------------------------------------*
 * FUN_00282bc0 @ 0x00282bc0   (est. sk_swift_string_fill_bytes)
 * Ghidra: long FUN_00282bc0(undefined4*,long,long,ulong)
 * Fills dest[0..count) with successive bytes of a little-endian packed
 * word (advancing 8 bits per slot).  Returns the number of bytes written
 * (or 0 when the source word is exhausted).  Traps on negative count /
 * index out of range.
 * Confidence: medium (Swift small-string byte fill).
 * Notes: fatal helpers FUN_00347ebc/003504b8/00348034; FUN_001afe4c fatal. */
long FUN_00282bc0(uint32_t *out, long dest, long count, word_t src)
{
    uint32_t u1;
    long i2, i3;

    u1 = (uint32_t)src;
    if (dest == 0) {
        i3 = 0;
    } else {
        if (count < 0) {
            FUN_00347ebc(1);
            FUN_003504b8();
            SWF_RANGE_BOUND();
            __builtin_trap();
        }
        i3 = count;
        if (count != 0) {
            i2 = 0;
            do {
                if (count == i2) {
                    FUN_00348034();
                    FUN_003504b8();
                    SWF_INDEX_RANGE();
                    __builtin_trap();
                }
                u1 = 0;
                i3 = i2;
                if ((int)src == 0) break;
                *(char *)(dest + i2) = (char)src - 1;
                i2 = i2 + 1;
                src = src >> 8 & 0xffffff;
                u1 = (uint32_t)src;
                i3 = count;
            } while (count != i2);
        }
    }
    *out = u1;
    return i3;
}

/*--------------------------------------------------------------------*
 * FUN_00282c40 @ 0x00282c40   (est. sk_swift_bitmap_drain_index)
 * Ghidra: long FUN_00282c40(undefined8*,ulong*,long,ulong*,long)
 * Drains a Swift bitmap (bit-vector) collecting set-bit indices into
 * out[]: each set bit is reverse-indexed (bitreverse + LZCOUNT) and
 * packed with its word index (idx = lz | word<<6).  Returns count of
 * bits collected; out-pair updated with (base,size,pos,bit).  Traps on
 * negative count / index-out-of-range.
 * Confidence: medium (Swift Set/bitmap enumeration).
 * Notes: SCARRY8 overflow -> SoftwareBreakpoint trap. */
long FUN_00282c40(word_t *out, word_t *indices, long count, word_t *bits, long nbits)
{
    long i1;
    word_t u2, u6;
    char *msg, *ty;
    word_t u9;
    long i7, i8;

    if (nbits < 1)
        u6 = 0;
    else
        u6 = *bits;
    if (indices == 0) {
        i8 = 0;
        count = 0;
    } else {
        if (count < 0) {
            u9 = 0xb5;
            msg = "Range requires lowerBound < upperBound";
            ty = "Swift.Range";
            SWF_FATAL(msg, 0x27, ty, 0x11, 0xb5);
            __builtin_trap();
        }
        if (count == 0) {
            i8 = 0;
        } else {
            i7 = 0;
            i8 = 0;
            do {
                if (i7 == count) {
                    u9 = 0x136;
                    msg = "Index out of range";
                    ty = "Swift.Range";
                    SWF_FATAL(msg, 0x12, ty, 0x11, 0x136);
                    __builtin_trap();
                }
                while (u6 == 0) {
                    i1 = i8 + 1;
                    if (SCARRY8(i8, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x282d50) */
                    if (nbits <= i1) {
                        u6 = 0;
                        count = i7;
                        goto out_finish;
                    }
                    i8 = i1;
                    u6 = bits[i1];
                }
                u2 = sk_bitreverse64(u6);
                u6 = u6 - 1 & u6;
                i7 = i7 + 1;
                *indices = LZCOUNT(u2) | i8 << 6;
                indices++;
            } while (i7 != count);
        }
    }
out_finish:
    out[0] = (word_t)bits;
    out[1] = (word_t)nbits;
    out[2] = (word_t)i8;
    out[3] = u6;
    return count;
}

/*--------------------------------------------------------------------*
 * FUN_00282d90 @ 0x00282d90   (est. sk_swift_bitmap_index_single)
 * Ghidra: long FUN_00282d90(ulong*,long,long,ulong)
 * Scans a single 64-bit bitmap word and writes the reverse-index of each
 * set bit into out[] (index = LZCOUNT(bitreverse(bit))), clearing bits as
 * they are consumed.  Returns the number of bits written.  Traps on
 * negative count / index-out-of-range.
 * Confidence: medium (Swift Set enumeration).
 * Notes: same fatal pattern as neighbours. */
long FUN_00282d90(word_t *out, long dest, long count, word_t bits)
{
    word_t u1;
    char *msg, *ty;
    word_t u3;
    long i4, i5;
    word_t u6;

    u1 = bits;
    if (dest == 0) {
        i5 = 0;
    } else {
        if (count < 0) {
            u6 = 0xb5;
            msg = "Range requires lowerBound < upperBound";
            ty = "Swift.Range";
            SWF_FATAL(msg, 0x27, ty, 0x11, 0xb5);
            __builtin_trap();
        }
        i5 = count;
        if (count != 0) {
            i4 = 0;
            do {
                if (count == i4) {
                    u6 = 0x136;
                    msg = "Index out of range";
                    ty = "Swift.Range";
                    SWF_FATAL(msg, 0x12, ty, 0x11, 0x136);
                    __builtin_trap();
                }
                u1 = 0;
                i5 = i4;
                if (bits == 0) break;
                u1 = sk_bitreverse64(bits);
                *(long *)(dest + i4 * 8) = LZCOUNT(u1);
                i4 = i4 + 1;
                bits = bits - 1 & bits;
                u1 = bits;
                i5 = count;
            } while (count != i4);
        }
    }
    *out = u1;
    return i5;
}

/*--------------------------------------------------------------------*
 * FUN_00282e84 @ 0x00282e84   (est. sk_swift_string_bytes_export)
 * Ghidra: ulong FUN_00282e84(ulong*,undefined1*,ulong,ulong,ulong)
 * Exports up to `count` bytes of a Swift 16-byte (two-word) string payload
 * into out[]: low word for bytes 0-7, high word for bytes 8+.  Stops at
 * the payload's stored length (uVar6 = high-word>>0x38 & 0xf).  Returns
 * the number of bytes exported.
 * Confidence: medium (Swift string payload export).
 * Notes: fatal FUN_001afe4c on range/index errors. */
word_t FUN_00282e84(word_t *out, uint8_t *dest, word_t count, word_t lo, word_t hi)
{
    word_t u1, u3, u6, u7;
    uint8_t u2;
    char *msg, *ty;
    word_t u8;

    if (dest == 0) {
        u3 = 0;
    } else {
        if ((long)count < 0) {
            u8 = 0xb5;
            msg = "Range requires lowerBound < upperBound";
            ty = "Swift.Range";
            SWF_FATAL(msg, 0x27, ty, 0x11, 0xb5);
            __builtin_trap();
        }
        u3 = count;
        if (count != 0) {
            u6 = hi >> 0x38 & 0xf;
            u7 = 0;
            do {
                if (u7 == count) {
                    u8 = 0x136;
                    msg = "Index out of range";
                    ty = "Swift.Range";
                    SWF_FATAL(msg, 0x12, ty, 0x11, 0x136);
                    __builtin_trap();
                }
                u3 = u6;
                if (u7 == u6) break;
                u1 = u7 + 1;
                u2 = (uint8_t)(lo >> (u7 << 3 & 0x3f));
                if (7 < u7)
                    u2 = (uint8_t)(hi >> (u7 << 3 & 0x38));
                *dest = u2;
                dest++;
                u3 = count;
                u7 = u1;
            } while (u1 != count);
        }
    }
    out[0] = lo;
    out[1] = hi;
    out[2] = u3;
    return u3;
}

/*--------------------------------------------------------------------*
 * FUN_00282f94 @ 0x00282f94   (est. sk_swift_bitmap_drain_masked)
 * Ghidra: long FUN_00282f94(long*,ulong*,long,ulong*,long)
 * Masked bitmap drain: restricts the first bitmap word to the low
 * (nbits+1) bits, then collects set-bit indices into out[] (idx =
 * LZCOUNT(bitreverse(bit)) | word<<6).  Returns count collected; updates
 * out-pair (base,size,pos,bit).  Traps on negative count / OOB.
 * Confidence: medium (Swift Set drain with bit-mask).
 * Notes: bitreverse + LZCOUNT enumeration. */
long FUN_00282f94(long *out, word_t *indices, long count, word_t *bits, long nbits)
{
    long i1;
    word_t u2, u6;
    char *msg, *ty;
    word_t u9;
    long i7, i8;

    u6 = 0xffffffffffffffffull;
    if ((unsigned long)(nbits + 1u) < 0x40)
        u6 = ~(-1L << (nbits + 1u & 0x3f));
    u6 = *bits & u6;
    if (indices == 0) {
        i8 = 0;
        count = 0;
    } else {
        if (count < 0) {
            u9 = 0xb5;
            msg = "Range requires lowerBound < upperBound";
            ty = "Swift.Range";
            SWF_FATAL(msg, 0x27, ty, 0x11, 0xb5);
            __builtin_trap();
        }
        if (count == 0) {
            i8 = 0;
        } else {
            i8 = 0;
            i7 = 0;
            do {
                if (i7 == count) {
                    u9 = 0x136;
                    msg = "Index out of range";
                    ty = "Swift.Range";
                    SWF_FATAL(msg, 0x12, ty, 0x11, 0x136);
                    __builtin_trap();
                }
                while (u6 == 0) {
                    i1 = i8 + 1;
                    if (SCARRY8(i8, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x2830b4) */
                    if ((long)(nbits + 0x40u >> 6) <= i1) {
                        u6 = 0;
                        count = i7;
                        goto out_finish2;
                    }
                    i8 = i1;
                    u6 = bits[i1];
                }
                u2 = sk_bitreverse64(u6);
                u6 = u6 - 1 & u6;
                i7 = i7 + 1;
                *indices = LZCOUNT(u2) | i8 << 6;
                indices++;
            } while (i7 != count);
        }
    }
out_finish2:
    out[0] = (long)bits;
    out[1] = nbits;
    out[2] = i8;
    out[3] = (long)u6;
    return count;
}

/*--------------------------------------------------------------------*
 * FUN_002830f4 @ 0x002830f4   (est. sk_swift_utf16_drain)
 * Ghidra: long FUN_002830f4(ulong*,undefined1(*)[16],long,ulong,ulong,ulong,ulong)
 * Drains up to `count` 16-byte UTF-16 code points from a Swift string
 * payload (4-word {p4..p7}) into out[][16] via helper transforms
 * (FUN_002b439c / FUN_002ab6a0 / FUN_002b3b84), advancing while the two
 * leading words stay within a 0x4000 window.  Returns count drained.
 * Confidence: low (Swift UTF16 character drain; indirect transforms).
 * Notes: fatal on negative count / index OOB. */
long FUN_002830f4(word_t *out, uint8_t (*dest)[16], long count, word_t p4,
                  word_t p5, word_t p6, word_t p7)
{
    word_t u2, u7;
    char *msg, *ty;
    long i4, i5;
    uint8_t av[16];

    u2 = p4;
    if (dest == 0) {
        i5 = 0;
    } else {
        if (count < 0) {
            u7 = 0xb5;
            msg = "Range requires lowerBound < upperBound";
            ty = "Swift.Range";
            SWF_FATAL(msg, 0x27, ty, 0x11, 0xb5);
            __builtin_trap();
        }
        i5 = count;
        if (count != 0) {
            i4 = 0;
            do {
                if (count == i4) {
                    u7 = 0x136;
                    msg = "Index out of range";
                    ty = "Swift.Range";
                    SWF_FATAL(msg, 0x12, ty, 0x11, 0x136);
                    __builtin_trap();
                }
                i5 = i4;
                if ((u2 ^ p5) < 0x4000) break;
                i4 = i4 + 1;
                av[0] = (uint8_t)FUN_002b439c(u2, p4, p5, p6, p7);
                u7 = FUN_002ab6a0(u2, p4, p5, p6, p7);
                u2 = FUN_002b3b84(u7, p4, p5, p6, p7);
                memcpy(*dest, av, 16);
                i5 = count;
                dest++;
            } while (count != i4);
        }
    }
    out[0] = p4;
    out[1] = p5;
    out[2] = p6;
    out[3] = p7;
    out[4] = u2;
    return i5;
}

/*--------------------------------------------------------------------*
 * FUN_00283290 @ 0x00283290   (est. sk_swift_utf16_index_advance)
 * Ghidra: long FUN_00283290(ulong*,long,long,ulong,ulong,ulong,ulong)
 * Swift String (UTF-16 view) index-advance walk: for each of `count`
 * steps, reads the UTF-16 code unit at the current index (a packed
 * 4-word string {p4..p7}), advances the string index by the character
 * width (UTF-8 vs UTF-16 decode via FUN_001676cc / FUN_002a9ba8 /
 * FUN_002af4d0), and stores the unit into out[i].  Returns the number of
 * steps taken.  Traps on range / index-out-of-bounds.
 * Confidence: low (Swift StringUTF16View indexing; heavy bitfield).
 * Notes: helpers FUN_002b64cc (unit fetch), FUN_0001da84, FUN_001676cc,
 *   FUN_002a9ba8, FUN_002af4d0; fatal "String index is out of bounds". */
long FUN_00283290(word_t *out, uint16_t *units, long count, word_t p4, word_t p5,
                  word_t p6, word_t p7)
{
    uint32_t u1, u10;
    word_t u2, u6, u12;
    uint8_t b3;
    bool b4;
    uint16_t u5;
    long i7, i11;
    char *msg;
    word_t u9;
    word_t u13;
    word_t loc70, st68;

    u6 = p4;
    if (units == 0) {
        i7 = 0;
    } else {
        if (count < 0) {
            u13 = 0xb5;
            msg = "Range requires lowerBound < upperBound";
            SWF_FATAL(msg, 0x27, "Swift.Range", 0x11, 0xb5);
            __builtin_trap();
        }
        i7 = count;
        if (count != 0) {
            i11 = 0;
            u10 = (uint32_t)(p6 >> 0x3b) & 1;
            if ((p7 & 0x1000000000000000ull) == 0)
                u10 = 1;
            b4 = (p7 & 0x2000000000000000ull) != 0;
            u2 = p6 & 0xffffffffffffull;
            if (b4)
                u2 = p7 >> 0x38 & 0xf;
            u1 = (uint32_t)((long)p6 < 0);
            if (b4)
                u1 = (uint32_t)(p7 >> 0x3e) & 1;
            do {
                if (count == i11) {
                    u13 = 0x136;
                    msg = "Index out of range";
                    SWF_FATAL(msg, 0x12, "Swift.Range", 0x11, 0x136);
                    __builtin_trap();
                }
                i7 = i11;
                if ((u6 ^ p5) < 0x4000) break;
                u5 = (uint16_t)FUN_002b64cc(u6, p4, p5, p6, p7);
                if ((u6 & 0xc) == (word_t)(4 << u10)) {
                    u6 = FUN_0001da84(u6, p6, p7);
                }
                u12 = u6 >> 0x10;
                if (u2 <= u12) {
                    msg = "String index is out of bounds";
                    SWF_FATAL(msg, 0x1d, "Swift.StringUTF16View", 0x1b, 0x93);
                    __builtin_trap();
                }
                if ((p7 >> 0x3c & 1) == 0) {
                    if (u1 == 0) {
                        if ((u6 & 0xc001) == 0) {
                            u6 = FUN_001676cc(u6, p6, p7);
                            u12 = u6 >> 0x10;
                            if ((p7 >> 0x3d & 1) == 0) goto label_33d0;
label_3448:
                            loc70 = p6;
                            st68 = p7 & 0xffffffffffffffull;
                            b3 = *(uint8_t *)((long)&loc70 + u12);
                        } else {
                            if ((p7 >> 0x3d & 1) != 0) goto label_3448;
label_33d0:
                            i7 = (long)(p7 & 0xfffffffffffffffull) + 0x20;
                            if ((p6 >> 0x3c & 1) == 0)
                                i7 = (long)FUN_002a9ba8(p6, p7);
                            b3 = *(uint8_t *)(i7 + u12);
                        }
                        if ((char)b3 < 0) {
                            i7 = LZCOUNT(((uint32_t)b3 << 0x18) ^ 0xffffffff);
                            if ((int)i7 != 4) goto label_3488;
                            if ((u6 & 0xc000) != 0) {
                                i7 = 4;
                                goto label_3488;
                            }
                            u12 = 0x4004;
                        } else {
                            i7 = 1;
label_3488:
                            u6 = u6 + i7 * 0x10000;
                            u12 = 5;
                        }
                        u6 = u6 & 0xffffffffffff0000ull | u12;
                    } else {
                        u6 = (u6 & 0xffffffffffff0000ull) + 0x1000d;
                    }
                } else {
                    u6 = FUN_002af4d0(u6);
                }
                units[i11] = u5;
                i11++;
                i7 = count;
            } while (count != i11);
        }
    }
    out[0] = p4;
    out[1] = p5;
    out[2] = p6;
    out[3] = p7;
    out[4] = u6;
    return i7;
}

/* ====================================================================== *
 *  Object / collection service loops (0x286b20 - 0x28e374)
 * ====================================================================== */

/*--------------------------------------------------------------------*
 * FUN_00286b20 @ 0x00286b20   (est. sk_object_service_kernel_loop)
 * Ghidra: void FUN_00286b20(void)
 * Object-service kernel loop: takes a sequence of lock / setup helpers,
 * runs one item through the DAT_00658c00 dispatch slot, and reports the
 * result flag via FUN_000b45b0.
 * Confidence: low (object-service loop; unmodelled unaff_x19 callback).
 * Notes: helpers FUN_000b4594 / FUN_00357f84 / FUN_00352068 /
 *   FUN_003537fc / FUN_003497a0 / FUN_00351dfc / FUN_00377824 /
 *   FUN_003508a8 / FUN_0035a4bc / FUN_000b45b0. */
void FUN_00286b20(void)
{
    uint32_t u1;
    word_t e8;
    code cb = (code)0;   /* unaff_x19 */

    FUN_000b4594();
    FUN_00357f84();
    FUN_00352068();
    FUN_003537fc();
    FUN_003497a0();
    FUN_00351dfc();
    FUN_00377824();
    FUN_003508a8();
    FUN_0035a4bc();
    u1 = (uint32_t)(uintptr_t)cb;
    FUN_000b45b0(u1 & 1, e8);
}

/*--------------------------------------------------------------------*
 * FUN_00286b94 @ 0x00286b94   (est. sk_object_service_wake)
 * Ghidra: void FUN_00286b94(void)
 * Object-service wake: runs the wake/drop helpers, dispatches through the
 * stack callback, takes the object lock, and finishes through the
 * FUN_0035396c / FUN_0035a7d4 epilogue.
 * Confidence: low (object-service wake; indirect call).
 * Notes: helpers FUN_0035a7c0 / FUN_0034d6d8 / FUN_00349ea0 /
 *   FUN_00350ed0 / FUN_00377824 / FUN_000a6e14 / FUN_0035396c /
 *   FUN_0035a7d4. */
void FUN_00286b94(void)
{
    word_t e8;
    word_t x7;
    wpair_t r;
    code cb = 0;   /* in_stack_00000050 */
    word_t x30;

    FUN_0035a7c0();
    FUN_0034d6d8();
    if (cb) cb(x7);
    FUN_00349ea0();
    FUN_00350ed0();
    r.lo = FUN_00377824();
    FUN_000a6e14(r.lo, r.hi, r.lo);
    if (cb) cb(0);
    e8 = FUN_0035396c();
    FUN_0035a7d4(e8, x30);
}

/*--------------------------------------------------------------------*
 * FUN_00286c10 @ 0x00286c10   (est. sk_object_service_process)
 * Ghidra: void FUN_00286c10(void)
 * Object-service process loop: iterates over work items through the
 * DAT_00658c00 dispatch slot, breaking when the current run flag (unaff_x19)
 * is set; exits through the FUN_00351348 / FUN_00353d14 epilogue.
 * Confidence: low (object-service run loop; heavy indirect dispatch).
 * Notes: helpers FUN_00353cfc / FUN_00355e68 / FUN_0034f860 /
 *   FUN_00377824 / FUN_00348d4c / FUN_0007c1a4 / FUN_0034b05c /
 *   FUN_0035050c / FUN_0034d464 / FUN_0034aee4 / FUN_003499f0 /
 *   FUN_003490ec / FUN_0034d8d4 / FUN_00348fd8 / FUN_0034d3c4 /
 *   FUN_00358aa4 / FUN_00352680 / FUN_00359bec / FUN_00350c80 /
 *   FUN_0034b278 / FUN_003508b4 / FUN_00377bec / FUN_000a68f4. */
void FUN_00286c10(void)
{
    int i1;
    word_t u2, u3;
    long e8;
    word_t x3;
    code cb = 0;          /* unaff_x19 */
    word_t x28;
    long e16;
    word_t st28;

    FUN_00353cfc();
    FUN_00355e68();
    u3 = (word_t)FUN_0034f860();
    FUN_00377824(u3, x3);
    FUN_00348d4c();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b05c();
    FUN_0035050c();
    FUN_0034d464();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034aee4();
    FUN_003499f0();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003490ec();
    FUN_0034d8d4();
    FUN_00377824();
    FUN_00348fd8();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034d3c4();
    FUN_00358aa4();
    if (cb) cb();
    FUN_00352680(x3);
    FUN_00359bec();
    FUN_00350c80();
    if (cb) cb();
    FUN_0034b278();
    FUN_003508b4();
    u3 = FUN_00377bec();
    cb = (code)(uintptr_t)FUN_000a68f4();
    while (1) {
        if (cb) cb(x28, u3);
        FUN_00351738();
        i1 = (int)FUN_000839f8();
        if (i1 == 1) break;
        FUN_00350738(*(word_t *)(e16 + 0x20));
        if (cb) cb();
        FUN_00357050();
        if (cb) cb();
        FUN_00358ea0();
        FUN_00350618(*(word_t *)(e16 + 8));
        if (cb) cb();
        if ((cb != 0) || ((e16 & 1) != 0)) break;
    }
    FUN_0034ed28();
    if (cb) cb();
    u3 = FUN_00351348(i1 != 1);
    FUN_00353d14(u3, st28);
}

/*--------------------------------------------------------------------*
 * FUN_00286e40 @ 0x00286e40   (est. sk_object_service_wrap)
 * Ghidra: void FUN_00286e40(void)
 * Thin wrapper: runs FUN_00354d44, then the object-service process loop
 * FUN_00286c10, then FUN_00356d20.
 * Confidence: low (object-service wrapper). */
void FUN_00286e40(void)
{
    FUN_00354d44();
    FUN_00286c10();
    FUN_00356d20();
}

/*--------------------------------------------------------------------*
 * FUN_00286e80 @ 0x00286e80   (est. sk_object_service_wake2)
 * Ghidra: void FUN_00286e80(void)
 * Object-service wake variant: runs wake/setup helpers, takes the object
 * lock, and finishes through FUN_0035396c.
 * Confidence: low (object-service wake). */
void FUN_00286e80(void)
{
    word_t u1;
    word_t x3, e8;

    FUN_003585f4();
    FUN_0035694c(x3);
    u1 = FUN_00349ea0();
    FUN_00377824(u1, e8);
    FUN_0014ae44();
    FUN_003505d0();
    FUN_0034e5fc();
    FUN_0035396c();
}

/*--------------------------------------------------------------------*
 * FUN_00286ee8 @ 0x00286ee8   (est. sk_object_service_run)
 * Ghidra: void FUN_00286ee8(undefined8 x6)
 * Object-service run loop: performs the standard service prelude
 * (FUN_00353cfc / FUN_00359634 / lock / dispatch slots), then loops on
 * FUN_000a68f4 items through the DAT_00658c00 slot, breaking when the
 * unaff_x19 run flag is set; finishes via FUN_00351348 / FUN_00353d14.
 * Confidence: low (object-service run loop; heavy indirect dispatch).
 * Notes: helpers FUN_00353cfc / FUN_00359634 / FUN_003509c8 /
 *   FUN_003497b4 / FUN_00352078 / FUN_00350488 / FUN_00377824 /
 *   FUN_00348cd0 / FUN_0007c1a4 / FUN_0034af20 / FUN_00350920 /
 *   FUN_0034d464 / FUN_0034b0c4 / FUN_0034998c / FUN_00348f50 /
 *   FUN_00348ce8 / FUN_0034d3c4 / FUN_003497a0 / FUN_00352efc /
 *   FUN_001a0414 / FUN_00358cd4 / FUN_00352680 / FUN_003511a8 /
 *   FUN_0034b278 / FUN_000e72b0 / FUN_00377bec / FUN_000a68f4. */
void FUN_00286ee8(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6)
{
    int zr;
    word_t u1, u2;
    code cb = 0;
    word_t e1;
    long e8;
    code m8 = 0;
    long e16, e16b;
    long run_flag = 0;          /* unaff_x19 */
    word_t x20;
    word_t l8;

    FUN_00353cfc();
    FUN_00359634();
    FUN_003509c8(p4);
    (*DAT_00658c00)(*(word_t *)(e16 + 0x40));
    FUN_003497b4();
    FUN_00352078();
    FUN_00350488();
    FUN_00377824();
    FUN_00348cd0();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034af20();
    FUN_00350920();
    FUN_0034d464();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0c4();
    FUN_0034998c();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_00348f50();
    u1 = FUN_00350488();
    FUN_00377824(u1, u2, p3);
    FUN_00348ce8();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034d3c4();
    u1 = FUN_003497a0();
    FUN_00377824(u1, p6, p4);
    FUN_00352efc();
    u2 = FUN_001a0414();
    u1 = FUN_00358cd4(u2, l8);
    if (m8) m8(u1, u2, p3);
    FUN_00352680(p5);
    FUN_003511a8();
    if (cb) cb();
    FUN_0034b278();
    u1 = FUN_000e72b0();
    u2 = FUN_00377bec(u1, (word_t)0, p5);
    cb = (code)(uintptr_t)FUN_000a68f4();
    do {
        if (cb) cb(p5, u2);
        FUN_00352290();
        FUN_00350884();
        if (zr) {
            FUN_00354324();
            if (m8) m8(x20, p5);
            goto finish;
        }
        FUN_00350c38(*(word_t *)(e16b + 0x20));
        if (m8) m8();
        FUN_00354834();
        if (cb) cb();
        FUN_003509b0(*(word_t *)(e16b + 8));
        if (m8) m8();
        if (run_flag != 0) {
            FUN_00354324();
            if (m8) m8(x20, p5);
            u2 = FUN_0036b118(u2);
            goto finish;
        }
        FUN_00310d34(0, e1);
        FUN_00355c1c();
        FUN_001a2128(e8, e1, p4, p6);
    } while (1);
finish:
    u1 = FUN_00351348(u2);
    FUN_00353d14(u1, *(word_t *)(e8 + 0x58));
}

/*--------------------------------------------------------------------*
 * FUN_002871b4 @ 0x002871b4   (est. sk_object_service_run2)
 * Ghidra: void FUN_002871b4(void)
 * Thin wrapper around FUN_002871cc.
 * Confidence: low. */
void FUN_002871b4(void)
{
    FUN_002871cc();
}

/*--------------------------------------------------------------------*
 * FUN_002871cc @ 0x002871cc   (est. sk_object_service_run_b)
 * Ghidra: void FUN_002871cc(undefined8 x5)
 * Object-service run variant: prelude, item dispatch through the
 * DAT_00658c00 slot, and a two-phase completion handling (break on
 * in_ZR, then a second conditional branch), finishing via FUN_00351348 /
 * FUN_00353d14.  Releases the loop ref (FUN_0036b118) on early exit.
 * Confidence: low (object-service run loop; heavy indirect dispatch).
 * Notes: helpers FUN_00353cfc / FUN_003516cc / FUN_00310d68 /
 *   FUN_000a6f88 / FUN_0007c1a4 / FUN_0034aee4 / FUN_00349b00 /
 *   FUN_003497b4 / FUN_003497a0 / FUN_00377824 / FUN_00348fd8 /
 *   FUN_0034b05c / FUN_0035113c / FUN_0034d464 / FUN_0034b2f8 /
 *   FUN_003499f0 / FUN_00348f38 / FUN_00349830 / FUN_000dbf08 /
 *   FUN_0034b0d4 / FUN_001a0414 / FUN_00354d14 / FUN_000a68c4 /
 *   FUN_0035102c / FUN_0034b278 / FUN_00377bec / FUN_000a68f4. */
void FUN_002871cc(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    int zr;
    word_t u1, u2;
    code cb = 0;
    long e8, e8b, e8c;
    code m8 = 0;
    long e16;
    word_t x21 = 0;             /* unaff_x21 */
    word_t x23, x28;
    word_t l8;

    u1 = FUN_00353cfc();
    FUN_003516cc();
    FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034aee4();
    FUN_00349b00();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003497b4();
    u1 = FUN_003497a0();
    FUN_00377824(u1, p5, p3);
    FUN_00348fd8();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b05c();
    FUN_0035113c();
    FUN_0034d464();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b2f8();
    FUN_003499f0();
    (*DAT_00658c00)(*(word_t *)(e8b + 0x40));
    FUN_00348f38();
    FUN_00349830();
    FUN_000dbf08();
    FUN_00377824();
    u1 = FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0d4();
    u2 = FUN_001a0414(0, p4);
    u1 = FUN_00354d14(*(word_t *)(e16 + 0x10));
    if (m8) m8(u1, u2, p3);
    FUN_000a68c4(p5);
    FUN_0035102c();
    if (cb) cb(p3, p5);
    FUN_0034b278();
    FUN_00377bec(p5, p3, u1);
    cb = (code)(uintptr_t)FUN_000a68f4();
    do {
        FUN_00351384(x23);
        if (cb) cb();
        u1 = FUN_0035172c();
        FUN_00350884(u1, u2, x28);
        if (zr) {
            FUN_00353be8();
            FUN_00350a34();
            if (m8) m8();
            goto finish2;
        }
        FUN_003578b4();
        u1 = FUN_00351274();
        if (m8) m8(u1, u2, x28);
        FUN_003531a8();
        FUN_00357170();
        FUN_003510dc();
        if (m8) m8();
        if (x21 != 0) {
            FUN_00353be8();
            FUN_00350a34();
            if (m8) m8();
            u2 = FUN_0036b118(u2);
            goto finish2;
        }
        FUN_00351738();
        FUN_0035a274();
        FUN_00350884();
        if (zr) {
            FUN_00354bbc();
            if (m8) m8();
        } else {
            FUN_00353bf4();
            u1 = FUN_00351360();
            if (m8) m8(u1, u2, u2);
            FUN_00350798();
            FUN_00310d34();
            FUN_00355c1c();
            FUN_001a1854(e8c);
        }
    } while (1);
finish2:
    u1 = FUN_00351348(u2);
    FUN_00353d14(u1, *(word_t *)(e8 + 0x58));
}

/*--------------------------------------------------------------------*
 * FUN_00287580 @ 0x00287580   (est. sk_swift_set_build)
 * Ghidra: undefined8* FUN_00287580(long)
 * Swift Set build: allocates a hash-set buffer (FUN_0025e4a0 with tag
 * 0x100000000), then for each of the source collection's elements computes
 * its hash (FUN_001a8564) and either finds an existing bucket or inserts
 * a new (key,value) pair (FUN_000b394c).  On hash collision the element
 * ref is released (FUN_003a25d4).  Releases the source ref (FUN_0036b118)
 * and returns the set buffer.
 * Confidence: medium (Swift Set build; hash + probe).
 * Notes: helpers FUN_001fab14 / FUN_0025e4a0 / FUN_0019e690 /
 *   FUN_0036b270 / FUN_001b9084 / FUN_001a8564 / FUN_002a0d50 /
 *   FUN_003a25d4 / FUN_000b394c / FUN_0036b118; empty sentinel
 *   DAT_006577e0. */
word_t *FUN_00287580(long src)
{
    long i1, i11, i12;
    long *pl2;
    word_t u4, u9, u10;
    uint8_t b5;
    word_t u7;
    word_t *out;
    word_t local[8];

    if (*(long *)(src + 0x10) == 0) {
        out = (word_t *)0x6577e0;
    } else {
        u7 = FUN_001fab14();
        out = (word_t *)FUN_0025e4a0(u7, 0x100000000ull, 0, 1, (void *)0x657728, (void *)0x4f2238);
        i11 = *(long *)(src + 0x10);
        if (i11 != 0) {
            i12 = 0;
            do {
                FUN_0019e690(i12, 1, src);
                i1 = i12 + 1;
                if (SCARRY8(i12, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x287794) */
                pl2 = (long *)(src + 0x20 + i12 * 0x10);
                i12 = *pl2;
                u4 = (word_t)pl2[1];
                local[0] = 0x65737464;    /* "dets" XOR mask artefacts */
                FUN_0036b270(u4);
                FUN_001b9084(&local[0], i12, u4);
                u9 = FUN_001a8564();
                b5 = *(uint8_t *)(out + 4);
                while ((*(word_t *)(out + (u9 >> 6) + 7) >> (u9 & 0x3f) & 1) != 0) {
                    u9 = u9 & ~(-1L << ((word_t)b5 & 0x3f));
                    pl2 = (long *)(out[6] + u9 * 0x10);
                    i1 = *pl2;
                    u10 = (word_t)pl2[1];
                    if ((i1 == i12 && u10 == u4) ||
                        ((((u10 ^ 0xffffffffffffffffull) & 0x6000000000000000ull) != 0 ||
                          (u4 & 0x6000000000000000ull) != 0x6000000000000000ull &&
                          (u10 = FUN_002a0d50(i1, u10, i12, u4, 0), (u10 & 1) != 0)))) {
                        FUN_003a25d4(u4);
                        goto next_elem;
                    }
                    u9 = u9 + 1;
                }
                FUN_000b394c(i12, u4, u9, out);
next_elem:
                i12 = i1;
            } while (i1 != i11);
        }
    }
    FUN_0036b118((void *)src);
    return out;
}

/*--------------------------------------------------------------------*
 * FUN_00287794 @ 0x00287794   (est. sk_swift_dictionary_build)
 * Ghidra: long FUN_00287794(long,long,undefined8)
 * Swift Dictionary build: walks a source collection, computes each key's
 * hash (FUN_0031948c), and inserts (key,value) pairs into a hash table
 * with open probing (FUN_0025c2b8), copying element pairs via the
 * object-method dispatch (FUN_0019ea20 / FUN_00027754 / FUN_0014ae44).
 * Returns the hash-table descriptor.
 * Confidence: low (Swift Dictionary build; indirect method dispatch).
 * Notes: helpers FUN_0025a060 / FUN_0031948c / FUN_0019ea20 /
 *   FUN_00027754 / FUN_0014ae44 / FUN_0025c2b8 / FUN_0036b118. */
long FUN_00287794(long p1, long p2, word_t p3)
{
    uint8_t b1;
    long i2, i3, i8, i9;
    word_t u4, u7;
    word_t u5;
    long e8, e12;
    word_t *a0;
    code m98 = 0;
    long l8 = *(long *)(p2 - 8);
    uint8_t st[8];
    word_t la8;
    word_t l90, l88, l80, l78, l70, l68;

    (*DAT_00658c00)(*(word_t *)(l8 + 0x40));
    (*DAT_00658c00)();
    i3 = (long)FUN_0025a060(*(word_t *)(FUN_0025a060(0) + 0x10));
    if (*(long *)(p1 + 0x10) != 0) {
        m98 = (code)(uintptr_t)FUN_0031948c(p3);
        l70 = i3 + 0x38;
        a0 = (word_t *)(l8 + 0x20);
        l78 = l8 + 0x10;
        la8 = l8 + 8 & 0xffffffffffffull | 0x4f8000000000000ull;
        i9 = 0;
        l90 = 0;
        l88 = p1;
        do {
            i2 = l90;
            FUN_0019ea20(l90, i9, l88, p2);
            if (SCARRY8(i9, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x287a30) */
            l80 = i9 + 1;
            ((void (*)(word_t, long, long))(*a0))(l68, i2, p2);
            u4 = (word_t)m98(*(word_t *)(i3 + 0x28), p2, p3);
            b1 = *(uint8_t *)(i3 + 0x20);
            while (1) {
                u4 = u4 & ~(-1L << ((word_t)b1 & 0x3f));
                if ((*(word_t *)(l70 + (u4 >> 6) * 8) >> (u4 & 0x3f) & 1) == 0) break;
                ((code)(*(word_t *)(l8 + 0x10)))
                    (st, *(long *)(i3 + 0x30) + *(long *)(l8 + 0x48) * u4, p2);
                u5 = FUN_00027754(p3);
                {
                    code c2 = (code)(uintptr_t)FUN_0014ae44();
                    u7 = (word_t)c2(st, l68, p2, u5);
                }
                {
                    code c3 = *(code *)(l8 + 8);
                    c3(st, p2);
                }
                if ((u7 & 1) != 0) {
                    ((code)(*(word_t *)(l8 + 8)))(la8, l68, p2);
                    goto done_loop;
                }
                u4 = u4 + 1;
            }
            FUN_0025c2b8(l68, u4, i3, p2);
done_loop:
            p1 = l88;
            i9 = l80;
        } while (l80 != *(long *)(l88 + 0x10));
    }
    FUN_0036b118((void *)p1);
    return i3;
}

/*--------------------------------------------------------------------*
 * FUN_00287a30 @ 0x00287a30   (est. sk_swift_collection_init_build)
 * Ghidra: void FUN_00287a30(undefined8*,undefined8,long)
 * Swift collection initializer: resolves the element type (FUN_00310d34 /
 * FUN_00376820 / FUN_0019fd10); if the type check fails it releases the
 * container ref and returns the empty sentinel, else builds the
 * dictionary via FUN_00287794.  Stores the result into *out.
 * Confidence: low (Swift collection init; indirect).
 * Notes: helpers FUN_00310d34 / FUN_00376820 / FUN_0019fd10 /
 *   FUN_00287794 / FUN_0036b118 / thunk_FUN_0006e06c. */
void FUN_00287a30(word_t *out, word_t p2, long p3)
{
    word_t u1, u2, u3;
    word_t u4;

    u4 = *(word_t *)(p3 + 0x10);
    u1 = FUN_00310d34(0, u4);
    u2 = FUN_00376820((void *)0x4e8268, u1);
    u3 = FUN_0019fd10(u1, u2);
    if ((u3 & 1) == 0) {
        u1 = FUN_00287794(p2, u4, *(word_t *)(p3 + 0x18));
    } else {
        FUN_0036b118((void *)p2);
        u1 = thunk_FUN_0006e06c();
    }
    *out = u1;
}

/*--------------------------------------------------------------------*
 * FUN_00287adc @ 0x00287adc   (est. sk_swift_array_prepare)
 * Ghidra: void FUN_00287adc(undefined8*,long)
 * Swift Array prepare: seeds the element-count nibble from the type
 * metadata (FUN_00354948), captures a value from FUN_0034fa4c, and calls
 * the shared array-init FUN_0028adc4, storing the 5-word array header.
 * Confidence: low (Swift Array prepare; indirect).
 * Notes: helpers FUN_00354948 / FUN_0034fa4c / FUN_0028adc4. */
void FUN_00287adc(word_t *out, long p2)
{
    word_t local[5];
    word_t src[5];

    FUN_00354948(*(uint8_t *)(p2 + 0x20));
    src[0] = FUN_0034fa4c();
    src[1] = 0;
    src[2] = 0;
    src[3] = 0;
    src[4] = 0;
    FUN_0028adc4(&local[0], src);
    out[0] = local[0];
    out[1] = local[1];
    out[2] = local[2];
    out[3] = local[3];
    out[4] = local[4];
}

/*--------------------------------------------------------------------*
 * FUN_00287b4c @ 0x00287b4c   (est. sk_swift_array_has_elements)
 * Ghidra: uint FUN_00287b4c(void)
 * Returns the low bit of the collection emptiness/contains check
 * (thunk_FUN_0025bca4).  Two near-identical bodies.
 * Confidence: medium. */
uint32_t FUN_00287b4c(void)
{
    return (uint32_t)(thunk_FUN_0025bca4() & 1);
}

/*--------------------------------------------------------------------*
 * FUN_00287b50 @ 0x00287b50   (est. sk_swift_array_has_elements2)
 * Ghidra: uint FUN_00287b50(void)
 * Same contains/emptiness probe as FUN_00287b4c.
 * Confidence: medium. */
uint32_t FUN_00287b50(void)
{
    return (uint32_t)(thunk_FUN_0025bca4() & 1);
}

/*--------------------------------------------------------------------*
 * FUN_00287b68 @ 0x00287b68   (est. sk_swift_array_reserve_from_bitmap)
 * Ghidra: void FUN_00287b68(undefined8*,long)
 * Swift Array reserve: builds the capacity bitmap mask from the source
 * collection's bit width (FUN_0028adc4 with the src fields), storing the
 * 5-word array header.
 * Confidence: low (Swift Array reserve; indirect FUN_0028adc4). */
void FUN_00287b68(word_t *out, long p2)
{
    word_t u1;
    word_t *x20 = 0;            /* unaff_x20 */
    word_t local[5];
    long l48;
    word_t *pu40;
    word_t l38, l28;

    l48 = (long)(uintptr_t)x20;
    l38 = ~(-1L << ((word_t)*(uint8_t *)(l48 + 0x20) & 0x3f));
    pu40 = (word_t *)(l48 + 0x38);
    u1 = -l38;
    l28 = 0xffffffffffffffffull;
    if (u1 < 0x40)
        l28 = ~(-1L << (u1 & 0x3f));
    l28 = l28 & *pu40;
    FUN_0028adc4(&local[0], &l48, *(word_t *)(p2 + 0x10), *(word_t *)(p2 + 0x18));
    out[0] = local[0];
    out[1] = local[1];
    out[2] = local[2];
    out[3] = local[3];
    out[4] = local[4];
}

/*--------------------------------------------------------------------*
 * FUN_00287c04 @ 0x00287c04   (est. sk_swift_collection_contains)
 * Ghidra: uint FUN_00287c04(undefined8,long)
 * Collection membership probe via thunk_FUN_0025bca4 on the element.
 * Confidence: medium. */
uint32_t FUN_00287c04(word_t p1, long p2)
{
    return (uint32_t)(thunk_FUN_0025bca4(p1, 0, *(word_t *)(p2 + 0x10),
                                         *(word_t *)(p2 + 0x18)) & 1);
}

/*--------------------------------------------------------------------*
 * FUN_00287c08 @ 0x00287c08   (est. sk_swift_collection_contains2)
 * Ghidra: uint FUN_00287c08(undefined8,long)
 * Duplicate of FUN_00287c04.
 * Confidence: medium. */
uint32_t FUN_00287c08(word_t p1, long p2)
{
    return (uint32_t)(thunk_FUN_0025bca4(p1, 0, *(word_t *)(p2 + 0x10),
                                         *(word_t *)(p2 + 0x18)) & 1);
}

/*--------------------------------------------------------------------*
 * FUN_00287c44 @ 0x00287c44   (est. sk_swift_collection_remove_first_a)
 * Ghidra: void FUN_00287c44(void)
 * Wrapper to FUN_002603f8.
 * Confidence: medium. */
void FUN_00287c44(void)
{
    FUN_002603f8();
}

/*--------------------------------------------------------------------*
 * FUN_00287c48 @ 0x00287c48   (est. sk_swift_collection_remove_first_b)
 * Ghidra: void FUN_00287c48(void)
 * Wrapper to FUN_002603f8.
 * Confidence: medium. */
void FUN_00287c48(void)
{
    FUN_002603f8();
}

/*--------------------------------------------------------------------*
 * FUN_00287c68 @ 0x00287c68   (est. sk_swift_array_index_checked)
 * Ghidra: void FUN_00287c68(undefined8,ulong,int,long,long)
 * Bounds-checked array element access: validates that the index is in
 * range and the bit is set in the element bitmap and the generation tag
 * matches, then dispatches the element via the collection method table
 * (param_5-8 +0x10).  Otherwise traps (Swift fatal).
 * Confidence: low (Swift Array subscript; unchecked fatal path).
 * Notes: unrecovered jumptable at 0x287cc8; FUN_003488bc/0034a3ec. */
void FUN_00287c68(word_t p1, word_t idx, int tag, long meta, long coll)
{
    if (((-1 < (long)idx) && (idx >> ((word_t)*(uint8_t *)(meta + 0x20) & 0x3f) == 0)) &&
        ((*(word_t *)(meta + (idx >> 6) * 8 + 0x38) >> (idx & 0x3f) & 1) != 0) &&
        (tag == *(int *)(meta + 0x24))) {
        ((code)(*(word_t *)(*(long *)(coll - 8) + 0x10)))
            (p1, *(long *)(meta + 0x30) + *(long *)(*(long *)(coll - 8) + 0x48) * idx, coll);
        return;
    }
    FUN_003488bc(1);
    FUN_0034a3ec();
    __builtin_trap();           /* Swift fatal (msg dropped by decompiler) */
}

/* thunk_FUN_00287c68: register thunk to FUN_00287c68 (same body). */
void thunk_FUN_00287c68(word_t a, word_t b, int c, long d, long e)
{
    FUN_00287c68(a, b, c, d, e);
}

/*--------------------------------------------------------------------*
 * FUN_00287d08 @ 0x00287d08   (est. sk_swift_type_meta_update)
 * Ghidra: void FUN_00287d08(void)
 * Updates the element-type metadata (FUN_00352194 / FUN_0025bae0) and
 * runs the teardown helper FUN_00357670.
 * Confidence: low (Swift type-meta update). */
void FUN_00287d08(void)
{
    word_t u1;
    word_t x19 = 0;             /* unaff_x19 */

    u1 = FUN_00352194();
    FUN_0025bae0(u1, *(uint32_t *)(x19 + 8));
    FUN_00357670();
}

/*--------------------------------------------------------------------*
 * FUN_00287d34 @ 0x00287d34   (est. sk_swift_set_for_each)
 * Ghidra: void FUN_00287d34(void)
 * Swift Set forEach: gets the current CPU (FUN_0008e518), walks the set's
 * element bitmap, and dispatches each element through the collection
 * method table (FUN_00356260) with the per-item helpers, until the bitmap
 * is exhausted; ends via FUN_00359920 / FUN_0008e500.
 * Confidence: low (Swift Set forEach; indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00352c34 / FUN_00349720 /
 *   FUN_00348f50 / FUN_00350678 / FUN_0035056c / FUN_00354948 /
 *   FUN_00359fa0 / FUN_00356260 / FUN_00351ef8 / FUN_0034d49c /
 *   FUN_00351b20 / FUN_00357b04 / FUN_00350630 / FUN_00359920 /
 *   FUN_0008e500. */
void FUN_00287d34(void)
{
    word_t u2, u4;
    long e8;
    long x26 = 0;               /* unaff_x26 */
    word_t x19;
    wpair_t v5, v6;
    word_t st38;

    FUN_0008e518();
    v5.lo = FUN_00352c34();
    v5.hi = FUN_00352c34();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    v6.lo = FUN_00348f50();
    v6.hi = FUN_00348f50();
    u2 = v6.lo;
    if (*(long *)(v6.hi + 0x10) != 0) {
        FUN_00350678();
        FUN_0035056c();
        {
            long i1 = FUN_00354948(*(uint8_t *)(v5.hi + 0x20));
            while ((*(word_t *)(v5.hi + 0x10) >> (x26 & 0x3f) & 1) != 0) {
                u2 = FUN_00359fa0(i1);
                FUN_00356260(*(word_t *)(e8 + 0x10), u2,
                             *(long *)(v5.hi + 0x30) + *(long *)(e8 + 0x48) * x26);
                FUN_00351ef8(x19);
                u2 = FUN_0034d49c();
                FUN_00351b20(u2, v5.lo);
                FUN_00357b04();
                FUN_00350630();
                u2 = 0;
                if ((v5.lo & 1) != 0) {
                    u4 = (word_t)*(uint32_t *)(v5.hi + 0x24);
                    goto out_label;
                }
                x26++;
            }
        }
    }
    u4 = 0x100000000ull;
out_label:
    v5.lo = FUN_00359920(u2, u4);
    FUN_0008e500(v5.lo, v5.hi, st38);
}

/*--------------------------------------------------------------------*
 * FUN_00287d38 @ 0x00287d38   (est. sk_swift_set_for_each2)
 * Ghidra: void FUN_00287d38(void)
 * Wrapper to FUN_00287d34.
 * Confidence: medium. */
void FUN_00287d38(void)
{
    FUN_00287d34();
}

/*--------------------------------------------------------------------*
 * FUN_00287d3c @ 0x00287d3c   (est. sk_swift_set_for_each3)
 * Ghidra: void FUN_00287d3c(void)
 * Wrapper to FUN_00287d34.
 * Confidence: medium. */
void FUN_00287d3c(void)
{
    FUN_00287d34();
}

/*--------------------------------------------------------------------*
 * FUN_00287d54 @ 0x00287d54   (est. sk_swift_value_from_tcb)
 * Ghidra: void FUN_00287d54(undefined1(*)[12])
 * Copies the 12-byte value produced by thunk_FUN_0025baa4(*x20) into
 * out[].
 * Confidence: low (Swift value materialise). */
void FUN_00287d54(uint8_t (*out)[12])
{
    uint8_t av[12];
    word_t x20 = 0;             /* unaff_x20 */

    thunk_FUN_0025baa4(x20);
    memcpy(*out, av, 12);
}

/*--------------------------------------------------------------------*
 * FUN_00287d84 @ 0x00287d84   (est. sk_swift_value_from_tcb2)
 * Ghidra: void FUN_00287d84(undefined1(*)[12])
 * Copies the 12-byte value produced by thunk_FUN_00355354(*x20) into out[].
 * Confidence: low. */
void FUN_00287d84(uint8_t (*out)[12])
{
    uint8_t av[12];
    word_t x20 = 0;

    thunk_FUN_00355354(x20);
    memcpy(*out, av, 12);
}

/*--------------------------------------------------------------------*
 * FUN_00287db4 @ 0x00287db4   (est. sk_swift_box_alloc)
 * Ghidra: undefined* FUN_00287db4(long*,undefined8*,long)
 * Swift box allocation: allocates a 0x28-byte box (FUN_0036a908, tag
 * 0x96c4), initialises it via FUN_00287e30, stores the value at +0x20,
 * and returns the box's value-metadata descriptor (DAT_003471a4).
 * Confidence: low (Swift box alloc). */
word_t *FUN_00287db4(long *out_box, word_t *src, long p3)
{
    long l1;
    word_t u2;
    word_t x20 = 0;

    l1 = (long)FUN_0036a908(0x28, 0x96c4);
    *out_box = l1;
    u2 = (word_t)FUN_00287e30((long *)(uintptr_t)l1, *src, *(uint32_t *)(src + 1), x20,
                              *(word_t *)(p3 + 0x10), *(word_t *)(p3 + 0x18));
    *(word_t *)(l1 + 0x20) = u2;
    return (word_t *)0x3471a4;
}

/*--------------------------------------------------------------------*
 * FUN_00287e30 @ 0x00287e30   (est. sk_swift_box_init)
 * Ghidra: undefined1[16] FUN_00287e30(long*,undefined8,undefined8,undefined8,long)
 * Swift box initializer: fills the box header (container + type-descriptor
 * from param_5-8), allocates the element storage (FUN_0036a908, tag
 * 0x5732) at +0x10, and runs the checked array-index FUN_00287c68 to
 * initialise the element.  Returns {&DAT_003471a8, storage}.
 * Confidence: low (Swift box init). */
uint8_t *FUN_00287e30(long *box, word_t p2, word_t p3, word_t p4, long p5,
                       word_t p6)
{
    long l1;
    static uint8_t ret[16];
    (void)p6;

    l1 = *(long *)(p5 - 8);
    box[0] = p5;
    box[1] = l1;
    l1 = (long)FUN_0036a908(*(word_t *)(l1 + 0x40), 0x5732);
    box[2] = l1;
    thunk_FUN_00287c68(l1, p2, p3, p4, p5);
    *(word_t *)&ret[8] = (word_t)l1;
    *(word_t *)&ret[0] = 0x3471a8;
    return ret;
}

/*--------------------------------------------------------------------*
 * FUN_00287ee8 @ 0x00287ee8   (est. sk_swift_box_teardown)
 * Ghidra: void FUN_00287ee8(long)
 * Swift box teardown: runs the set-forEach FUN_00287d34 and the
 * teardown helper FUN_00357670, then clears the box's two flag bytes at
 * +0xc and +0xd.
 * Confidence: low. */
void FUN_00287ee8(long p1)
{
    FUN_00359350();
    FUN_00287d34();
    FUN_00357670();
    *(uint8_t *)(p1 + 0xc) = 0;
    *(uint8_t *)(p1 + 0xd) = 0;
}

/*--------------------------------------------------------------------*
 * FUN_00287f20 @ 0x00287f20   (est. sk_swift_value_from_pair)
 * Ghidra: void FUN_00287f20(undefined1(*)[12],undefined8*)
 * Copies the 12-byte value produced by thunk_FUN_0025bae0 into out[].
 * Confidence: low. */
void FUN_00287f20(uint8_t (*out)[12], word_t *src)
{
    uint8_t av[12];
    word_t x20 = 0;

    thunk_FUN_0025bae0(*src, *(uint32_t *)(src + 1), x20);
    memcpy(*out, av, 12);
}

/*--------------------------------------------------------------------*
 * FUN_00287f6c @ 0x00287f6c   (est. sk_swift_set_equality)
 * Ghidra: undefined8 FUN_00287f6c(long,long)
 * Swift Set equality: returns true if the two sets are identical or (for
 * equal element counts) every element of set1 is found in set2 by hashing
 * and open probing (FUN_0031993c / FUN_0008e5d8).  Iterates set1's
 * element bitmap; each element is hashed into set2 and probed until found
 * or the slot is empty.  Returns 1 (equal) or 0.
 * Confidence: low (Swift Set ==; hash probe + element compare).
 * Notes: helpers FUN_0031996c / FUN_0006a4c0 / FUN_0008e5d8 /
 *   FUN_0031993c / FUN_000026e8 / FUN_0031997c / FUN_003199ac;
 *   SoftwareBreakpoint(1,0x288254). */
word_t FUN_00287f6c(long set1, long set2)
{
    word_t u2, u3, u5, u6, u7, u8, u9, u10;
    long i11;
    word_t l148;
    uint8_t s138[40], s110[24], se8[24];
    word_t d0, c8, c0, b8, b0, a8, a0;
    word_t l90, s88, s80, s78, l70;
    word_t f0, f8;

    if (set1 == set2) goto equal;
    if (*(long *)(set1 + 0x10) == *(long *)(set2 + 0x10)) {
        i11 = 0;
        u9 = 1L << ((word_t)*(uint8_t *)(set1 + 0x20) & 0x3f);
        l148 = 0xffffffffffffffffull;
        if ((*(uint8_t *)(set1 + 0x20) & 0x3f) < 6)
            l148 = ~(-1L << (u9 & 0x3f));
        l148 = l148 & *(word_t *)(set1 + 0x38);
        if (l148 == 0) goto next_word;
scan:
        u7 = sk_bitreverse64(l148);
        l148 = l148 - 1 & l148;
        do {
            FUN_0031996c(*(long *)(set1 + 0x30) + (LZCOUNT(u7) | i11 << 6) * 0x28, &l90);
            u2 = l70;
            u6 = s78;
            c0 = l90;
            a8 = s78;
            a0 = l70;
            u10 = *(word_t *)(set2 + 0x28);
            FUN_0006a4c0(&c0, s78);
            {
                code m = (code)(uintptr_t)FUN_0008e5d8(u2);
                m(se8, u6, u2);
            }
            u2 = c8;
            u6 = d0;
            FUN_0006a4c0(se8, d0);
            {
                code m = (code)(uintptr_t)FUN_0031993c(u2);
                u7 = (word_t)m(u10, u6, u2);
            }
            FUN_000026e8(se8);
            u8 = -1L << ((word_t)*(uint8_t *)(set2 + 0x20) & 0x3f);
            u7 = u7 & (u8 ^ 0xffffffffffffffffull);
            if ((*(word_t *)(set2 + 0x38 + (u7 >> 6) * 8) >> (u7 & 0x3f) & 1) == 0) {
                FUN_003199ac(&c0);
                break;
            }
            while (1) {
                FUN_0031996c(*(long *)(set2 + 0x30) + u7 * 0x28, se8);
                u2 = c8;
                u6 = d0;
                FUN_0006a4c0(se8, d0);
                {
                    code m = (code)(uintptr_t)FUN_0008e5d8(u2);
                    m(s110, u6, u2);
                }
                u2 = f0;
                u6 = f8;
                FUN_0006a4c0(s110, f8);
                u3 = a0;
                u10 = a8;
                FUN_0006a4c0(&c0, a8);
                {
                    code m = (code)(uintptr_t)FUN_0008e5d8(u3);
                    m(s138, u10, u3);
                }
                {
                    code m = (code)(uintptr_t)FUN_0031997c(u2);
                    u5 = (word_t)m(s138, u6, u2);
                }
                FUN_000026e8(s138);
                FUN_000026e8(s110);
                FUN_003199ac(se8);
                if ((u5 & 1) != 0) break;
                u7 = u7 + 1 & ~u8;
                if ((*(word_t *)(set2 + 0x38 + (u7 >> 6) * 8) >> (u7 & 0x3f) & 1) == 0)
                    goto bucket_done;
            }
bucket_done:
            FUN_003199ac(&c0);
            if (l148 != 0) goto scan;
next_word:
            do {
                i11++;
                if (SCARRY8(i11, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x288254) */
                if ((long)(u9 + 0x3f >> 6) <= i11) goto equal;
                l148 = ((word_t *)(set1 + 0x38))[i11];
            } while (l148 == 0);
            u7 = sk_bitreverse64(l148);
            l148 = l148 - 1 & l148;
        } while (1);
    }
    u6 = 0;
    return u6;
equal:
    u6 = 1;
    return u6;
}

/*--------------------------------------------------------------------*
 * FUN_00288254 @ 0x00288254   (est. sk_swift_set_all_match)
 * Ghidra: void FUN_00288254(void)
 * Swift Set allSatisfy: walks the set's element bitmap, and for each
 * element runs the predicate dispatch (FUN_00358a50 / FUN_00353c6c /
 * per-item helpers); if any element fails the predicate the result is 0,
 * otherwise 1.  Ends via FUN_0008e500.
 * Confidence: low (Swift Set allSatisfy; indirect predicate).
 * Notes: helpers FUN_0008e518 / FUN_00349720 / FUN_00348abc /
 *   FUN_0034ea40 / FUN_0034c074 / FUN_00359a04 / FUN_0034c53c /
 *   FUN_0035339c / FUN_00354ff4 / FUN_00353fa0 / FUN_0034edc8 /
 *   FUN_0035512c / FUN_00350678 / FUN_00350878 / FUN_00358a50 /
 *   FUN_00355b10 / FUN_00353c6c / FUN_00352ee4 / FUN_0034d49c /
 *   FUN_00350ac4 / FUN_0035060c / FUN_00359e60 / FUN_0034bdbc /
 *   FUN_0008e500. */
void FUN_00288254(void)
{
    bool b1;
    long i2, i4, i7, i9;
    word_t u3, u5, u6;
    long x1, x10, x10b, x11, x16;
    word_t x8_0;
    code m8 = 0;
    word_t x24 = 0;             /* unaff_x24 */
    word_t x30, x3;
    wpair_t v11;
    word_t l28, l8;

    FUN_0008e518();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(x8_0 + 0x40));
    FUN_00348abc();
    (*DAT_00658c00)();
    FUN_0034ea40();
    (*DAT_00658c00)();
    v11.lo = FUN_0034c074();
    v11.hi = FUN_0034c074();
    b1 = (v11.lo == v11.hi);
    if (b1) goto out_true;
    i2 = (long)FUN_00359a04(*(word_t *)(v11.lo + 0x10));
    if (b1) {
        i9 = 0;
        FUN_0034c53c(*(word_t *)(i2 + 0x38));
        u3 = FUN_0035339c();
        i4 = x11;
        if (x10 == 0) goto next_word;
        do {
            i4 = (long)FUN_00354ff4();
            u6 = x8_0;
            while (1) {
                i7 = *(long *)(x16 + 0x48);
                {
                    code pc = *(code *)(x16 + 0x10);
                    FUN_00353fa0(i4, *(long *)(i4 + 0x30) + i7 * (u6 | i9 << 6));
                    pc();
                }
                FUN_0034edc8(*(word_t *)(x16 + 0x20));
                if (m8) m8();
                FUN_0035512c();
                FUN_00350678();
                FUN_00350878();
                i4 = (long)m8;
                do {
                    u5 = FUN_00358a50(i4);
                    if ((0 & 1) == 0) {
                        FUN_00355b10(x24);
                        if (m8) m8();
                        goto out_false;
                    }
                    FUN_00353c6c(u5, *(long *)(x1 + 0x30) + x1 * i7);
                    if (m8) m8(l28);
                    FUN_00352ee4(x3);
                    u5 = FUN_0034d49c();
                    FUN_00350ac4(u5, l8);
                    u6 = 0;
                    {
                        code pc = (code)(uintptr_t)x24;
                        FUN_0035060c();
                        pc();
                    }
                    i4 = x1 + 1;
                } while ((u6 & 1) == 0);
                FUN_00355b10((x24 & 0xffffffffffffull) | 0x4f8000000000000ull);
                {
                    code pc2 = (code)(uintptr_t)((x24 & 0xffffffffffffull) | 0x4f8000000000000ull);
                    pc2();
                }
                FUN_00359e60(u3);
                i4 = x11;
                if (x10 != 0) break;
next_word:
                do {
                    i7 = i9 + 1;
                    if (SCARRY8(i9, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x28848c) */
                    if (i4 <= i7) goto out_true;
                    i9++;
                } while (((word_t *)(i2 + 0x38))[i7] == 0);
                i4 = (long)FUN_0034bdbc();
                u6 = x8_0;
                i9 = i7;
            }
        } while (1);
    }
out_false:
    u3 = 0;
    FUN_0008e500(u3, x30);
    return;
out_true:
    u3 = 1;
    FUN_0008e500(u3, x30);
    return;
}

/*--------------------------------------------------------------------*
 * FUN_002884a0 @ 0x002884a0   (est. sk_swift_set_hash_aggregate)
 * Ghidra: void FUN_002884a0(undefined8,long)
 * Swift Set hashValue aggregate: copies the container seed (0x48 bytes),
 * then XORs the hash of every element (FUN_0031993c via FUN_0008e5d8)
 * into an accumulator over the set's bitmap.  Releases the set ref and
 * reports the aggregate via thunk_FUN_002298d4.
 * Confidence: low (Swift Set hash aggregation; indirect dispatch).
 * Notes: helpers FUN_00117cc4 / FUN_001a8564 / FUN_0036b270 /
 *   FUN_0031996c / FUN_0006a4c0 / FUN_0008e5d8 / FUN_0031993c /
 *   FUN_000026e8 / FUN_003199ac / FUN_0036b118 / thunk_FUN_002298d4. */
void FUN_002884a0(word_t p1, long set)
{
    word_t u2, u4, u6, u7, u9, u10;
    uint8_t st100[24];
    word_t e8, b8, c0;
    word_t seed;

    FUN_00117cc4(&seed, (void *)p1, 0x48);
    u4 = FUN_001a8564();
    u7 = 1L << ((word_t)*(uint8_t *)(set + 0x20) & 0x3f);
    u10 = 0xffffffffffffffffull;
    if ((*(uint8_t *)(set + 0x20) & 0x3f) < 6)
        u10 = ~(-1L << (u7 & 0x3f));
    u10 = u10 & *(word_t *)(set + 0x38);
    FUN_0036b270((void *)set);
    u9 = 0;
    {
        long i8 = 0;
        while (1) {
            for (; u10 != 0; u10 = u10 - 1 & u10) {
                u6 = sk_bitreverse64(u10);
                FUN_0031996c(*(long *)(set + 0x30) + LZCOUNT(u6) * 0x28 + i8 * 0xa00, st100);
                u2 = b8;
                {
                    code m = (code)(uintptr_t)FUN_0008e5d8(u2);
                    m(st100, c0, u2);
                }
                u2 = e8;
                {
                    code m = (code)(uintptr_t)FUN_0031993c(u2);
                    u6 = (word_t)m(u4, c0, u2);
                }
                FUN_000026e8(st100);
                FUN_003199ac(st100);
                u9 = u6 ^ u9;
            }
            i8++;
            if (SCARRY8(i8, 1)) break;
            if ((long)(u7 + 0x3f >> 6) <= i8) {
                FUN_0036b118((void *)set);
                thunk_FUN_002298d4(u9);
                return;
            }
            u10 = ((word_t *)(set + 0x38))[i8];
        }
        __builtin_trap();       /* SoftwareBreakpoint(1,0x288638) */
    }
}

/*--------------------------------------------------------------------*
 * FUN_00288638 @ 0x00288638   (est. sk_swift_collection_hash_aggregate)
 * Ghidra: void FUN_00288638(void)
 * Swift collection hashValue aggregate: seeds a 0x48-byte container
 * header, then XORs each element's hash (FUN_0031948c / FUN_00077894)
 * into an accumulator over the collection bitmap.  Releases the container
 * ref, reports via FUN_003553d8 / thunk_FUN_002298d4, and ends through
 * FUN_0008e500.
 * Confidence: low (Swift collection hash aggregation; indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_0035199c / FUN_00349720 /
 *   FUN_00348f38 / FUN_00117cc4 / FUN_001a8564 / FUN_00354948 /
 *   FUN_0034fa4c / FUN_00357280 / FUN_00077894 / FUN_0028adc4 /
 *   FUN_00359d38 / FUN_00352b98 / FUN_00352554 / FUN_0036b270 /
 *   FUN_0034c194 / FUN_00353c24 / FUN_00355418 / FUN_0031948c /
 *   FUN_00351384 / FUN_00354b74 / FUN_0036b118 / FUN_003553d8. */
void FUN_00288638(word_t a1, word_t a2, word_t a3, word_t a4)
{
    long i1, i2;
    (void)a1; (void)a2; (void)a3; (void)a4;
    word_t u4, u5, u6, u7;
    word_t x1;
    long e8;
    code m8 = 0;
    long e16;
    long x25 = 0;               /* unaff_x25 */
    word_t x30;
    wpair_t v8;
    uint8_t st_a0[72];
    long l58, st50, l48, st40, l38;

    FUN_0008e518();
    v8.lo = FUN_0035199c();
    v8.hi = FUN_0035199c();
    FUN_00349720(v8.lo, v8.lo);
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_00348f38();
    FUN_00117cc4(st_a0, (void *)x1, 0x48);
    u4 = FUN_001a8564();
    FUN_00354948(*(uint8_t *)(v8.hi + 0x20));
    FUN_0034fa4c();
    FUN_00357280();
    FUN_00077894();
    FUN_0028adc4();
    FUN_00359d38(l48);
    FUN_00352b98(e16 + 0x10);
    FUN_00352554(e16 + 8);
    FUN_0036b270((void *)v8.hi);
    u7 = 0;
    i2 = st40;
    i1 = l38;
    while (1) {
        while (i1 != 0) {
            u5 = FUN_0034c194();
            FUN_00353c24(*(word_t *)(e16 + 0x10), u5,
                         *(long *)(l58 + 0x30) + *(long *)(e16 + 0x48) * (0 | i2 << 6));
            FUN_00355418();
            if (m8) m8();
            u5 = FUN_0031948c();
            FUN_00077894(u5, u4);
            u6 = 0;
            FUN_00351384(*(word_t *)(e16 + 8));
            FUN_00354b74();
            if (m8) m8();
            u7 = u6 ^ u7;
        }
        i1 = i2 + 1;
        if (SCARRY8(i2, 1)) break;
        if (x25 <= i1) {
            FUN_0036b118((void *)l58);
            FUN_003553d8(u7);
            thunk_FUN_002298d4();
            FUN_0008e500(x30);
            return;
        }
        i2 = i1;
        i1 = *(long *)(st50 + i1 * 8);
    }
    __builtin_trap();           /* SoftwareBreakpoint(1,0x2887d8) */
}

/*--------------------------------------------------------------------*
 * FUN_002887f0 @ 0x002887f0   (est. sk_swift_set_hash_seed)
 * Ghidra: void FUN_002887f0(void)
 * Seeds the set hash from a constant nibble (s_uespemosmodnarodarenegyl
 * setybdet_004e7a30) via FUN_0034a4a4 / FUN_003552f0 / FUN_0034d264,
 * then runs the hash-seed epilogue FUN_001a8564.
 * Confidence: low (Swift Set hash seed). */
void FUN_002887f0(void)
{
    uint8_t b1;
    word_t x3;

    FUN_0034a4a4(x3);
    b1 = (uint8_t)FUN_003552f0();
    FUN_0034d264(b1, 0, b1 ^ 0);
    FUN_001a8564();
}

/*--------------------------------------------------------------------*
 * FUN_0028886c @ 0x0028886c   (est. sk_swift_collection_hash_entry)
 * Ghidra: void FUN_0028886c(undefined8,long)
 * Swift collection hash entry: builds the container (FUN_001a84f4),
 * aggregates element hashes via FUN_00288638, and runs the hash epilogue
 * FUN_001a8564.
 * Confidence: low (Swift collection hash). */
void FUN_0028886c(word_t p1, long p2)
{
    uint8_t st68[72];
    word_t x20 = 0;             /* unaff_x20 */

    FUN_001a84f4(st68);
    FUN_00288638((word_t)st68, x20, *(word_t *)(p2 + 0x10), *(word_t *)(p2 + 0x18));
    FUN_001a8564();
}

/*--------------------------------------------------------------------*
 * FUN_002888b4 @ 0x002888b4   (est. sk_object_service_slot_store)
 * Ghidra: void FUN_002888b4(void)
 * Object-service slot store: runs setup helpers (FUN_00350a28 /
 * FUN_00288910 / FUN_003535a8 / FUN_0034e70c / FUN_0031dd98) and writes
 * the 5-word value descriptor into the method-table slot.
 * Confidence: low (object-service slot store; indirect). */
void FUN_002888b4(void)
{
    word_t u1;
    word_t x22 = 0, x23 = 0;    /* unaff_x22 / x23 */
    word_t *e8 = 0;

    FUN_00350a28();
    FUN_00288910();
    FUN_003535a8();
    FUN_0034e70c();
    u1 = FUN_0031dd98();
    e8[3] = u1;
    e8[4] = 0x4f1730;
    e8[0] = x22;
    e8[1] = x23;
}

/*--------------------------------------------------------------------*
 * FUN_00288910 @ 0x00288910   (est. sk_swift_hash_mix_loop)
 * Ghidra: void FUN_00288910(void)
 * Swift hash mix helper: runs FUN_003598cc / FUN_0034e2b8 /
 * FUN_00288a80 / FUN_00353a30.
 * Confidence: low. */
void FUN_00288910(void)
{
    FUN_003598cc();
    FUN_0034e2b8();
    FUN_00288a80();
    FUN_00353a30();
}

/*--------------------------------------------------------------------*
 * FUN_00288954 @ 0x00288954   (est. sk_swift_set_copy)
 * Ghidra: undefined8* FUN_00288954(long)
 * Swift Set copy: allocates a fresh hash-set buffer (FUN_0025e370, tag
 * 0x100000000), then copies every set element (FUN_0025a864) over the
 * source bitmap.  Retains both buffers, releases them on completion, and
 * returns the copy (or the empty sentinel DAT_006577e0).
 * Confidence: medium (Swift Set copy; element copy).
 * Notes: helpers FUN_001fab14 / FUN_0025e370 / FUN_0036b270 /
 *   FUN_0031996c / FUN_0025a864 / FUN_0036b118. */
word_t *FUN_00288954(long src)
{
    word_t u1, u4, u6, u7;
    long i8;
    uint8_t st78[40];
    word_t *out;

    if (*(long *)(src + 0x10) == 0) {
        out = (word_t *)0x6577e0;
    } else {
        u4 = FUN_001fab14();
        out = (word_t *)FUN_0025e370(u4, 0x100000000ull, 0, 1);
    }
    u6 = 1L << ((word_t)*(uint8_t *)(src + 0x20) & 0x3f);
    u7 = 0xffffffffffffffffull;
    if ((*(uint8_t *)(src + 0x20) & 0x3f) < 6)
        u7 = ~(-1L << (u6 & 0x3f));
    u7 = u7 & *(word_t *)(src + 0x38);
    FUN_0036b270((void *)out);
    FUN_0036b270((void *)src);
    i8 = 0;
    while (1) {
        for (; u7 != 0; u7 = u7 - 1 & u7) {
            u1 = sk_bitreverse64(u7);
            FUN_0031996c(*(long *)(src + 0x30) + LZCOUNT(u1) * 0x28 + i8 * 0xa00, st78);
            FUN_0025a864(st78, out);
        }
        i8++;
        if (SCARRY8(i8, 1)) break;
        if ((long)(u6 + 0x3f >> 6) <= i8) {
            FUN_0036b118((void *)out);
            FUN_0036b118((void *)src);
            return out;
        }
        u7 = ((word_t *)(src + 0x38))[i8];
    }
    __builtin_trap();           /* SoftwareBreakpoint(1,0x288a80) */
}

/*--------------------------------------------------------------------*
 * FUN_00288a80 @ 0x00288a80   (est. sk_swift_collection_hash_final)
 * Ghidra: void FUN_00288a80(void)
 * Wrapper to FUN_0028b918.
 * Confidence: low. */
void FUN_00288a80(void)
{
    FUN_0028b918();
}

/*--------------------------------------------------------------------*
 * FUN_00288a88 @ 0x00288a88   (est. sk_swift_pair_materialise)
 * Ghidra: void FUN_00288a88(undefined8 x4)
 * Swift pair materialise: builds a value from FUN_0034ed08 / FUN_0031a1dc
 * and retains the box (thunk_FUN_0036b270).
 * Confidence: low. */
void FUN_00288a88(word_t p1, word_t p2, word_t p3, word_t p4)
{
    wpair_t v;

    v.lo = FUN_0034ed08(p1, p3);
    FUN_0031a1dc(v.lo, v.hi, p4);
    FUN_00357f24();
    thunk_FUN_0036b270();
}

/*--------------------------------------------------------------------*
 * FUN_00288abc @ 0x00288abc   (est. sk_swift_set_wrap)
 * Ghidra: void FUN_00288abc(undefined8*,undefined8,undefined8)
 * Swift Set wrap: retains the source collection, builds its copy
 * (FUN_00288954), and stores the 5-word value descriptor into out.
 * Confidence: low. */
void FUN_00288abc(word_t *out, word_t p2, word_t p3)
{
    word_t u1, u2;

    thunk_FUN_0036b270(p3);
    u1 = (word_t)FUN_00288954(p3);
    u2 = FUN_0035a830();
    out[3] = u2;
    out[4] = 0x4f1730;
    out[0] = p3;
    out[1] = u1;
}

/*--------------------------------------------------------------------*
 * FUN_00288b18 @ 0x00288b18   (est. sk_swift_set_equal_probe)
 * Ghidra: uint FUN_00288b18(undefined8)
 * Swift Set equality probe: builds a probe buffer (FUN_00344d4c /
 * FUN_00356fcc); if it fails returns 2, else runs the set-equality
 * FUN_00287f6c, releases both ends (FUN_003a25d4), and returns the
 * low bit.
 * Confidence: low. */
uint32_t FUN_00288b18(word_t p1)
{
    int i1;
    uint32_t u2;
    word_t l68, st60;
    uint8_t st58[40];

    FUN_00344d4c(p1, st58);
    FUN_003519c0();
    FUN_0035a830();
    i1 = (int)FUN_00356fcc(&l68, st58);
    if (i1 == 0) {
        u2 = 2;
    } else {
        FUN_0009461c();
        u2 = (uint32_t)FUN_00287f6c(0, 0);
        FUN_003a25d4(st60);
        FUN_003a25d4(l68);
        u2 = u2 & 1;
    }
    return u2;
}

/*--------------------------------------------------------------------*
 * FUN_00288b9c @ 0x00288b9c   (est. sk_swift_set_hash_seed2)
 * Ghidra: void FUN_00288b9c(void)
 * Seeds the set hash from a constant nibble (s_uespemosmodnarodarenegyl
 * setybdet_004e7a30) then aggregates via FUN_002884a0 and the hash
 * epilogue FUN_001a8564.
 * Confidence: low. */
void FUN_00288b9c(void)
{
    uint8_t b1;

    b1 = (uint8_t)FUN_00348c48();
    FUN_0034d264(b1, 0, b1 ^ 0);
    FUN_002884a0(0, 0);
    FUN_001a8564();
}

/*--------------------------------------------------------------------*
 * FUN_00288bf0 @ 0x00288bf0   (est. sk_swift_set_hash_entry)
 * Ghidra: void FUN_00288bf0(undefined8 x3)
 * Swift Set hash entry: seeds (FUN_00349d14 / FUN_00351624 /
 * FUN_00348f68), aggregates via FUN_002884a0, and runs FUN_001a8564.
 * Confidence: low. */
void FUN_00288bf0(word_t p1, word_t p2, word_t p3)
{
    uint8_t st68[72];

    FUN_00349d14(p1, p3);
    FUN_00351624();
    FUN_00348f68();
    FUN_002884a0((word_t)st68, 0);
    FUN_001a8564();
}

/*--------------------------------------------------------------------*
 * FUN_00288c34 @ 0x00288c34   (est. sk_swift_box_release)
 * Ghidra: void FUN_00288c34(undefined8 x5)
 * Swift box release: runs the teardown chain (FUN_003530e8 /
 * FUN_00352ddc / FUN_0031a1dc / FUN_00356b5c / retain), toggles the
 * release flag, and reports via FUN_000839d8.
 * Confidence: low. */
void FUN_00288c34(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    word_t u1;
    wpair_t v;

    FUN_003530e8(p1, p3);
    v.lo = FUN_00352ddc();
    FUN_0031a1dc(v.lo, v.hi, p5);
    FUN_00356b5c();
    thunk_FUN_0036b270();
    FUN_003515fc();
    u1 = FUN_00365b6c();
    FUN_0034dba8(u1, (uint32_t)u1 ^ 1);
    FUN_000839d8();
}

/*--------------------------------------------------------------------*
 * FUN_00288e50 @ 0x00288e50   (est. sk_object_service_teardown)
 * Ghidra: void FUN_00288e50(void)
 * Object-service teardown: runs the lock/release helper chain on the
 * current service context and releases the container ref (FUN_0036b118).
 * Confidence: low (object-service teardown). */
void FUN_00288e50(void)
{
    word_t x20 = 0, x30;
    word_t st8;

    FUN_00354744();
    FUN_0035098c();
    FUN_003a261c(x20);
    FUN_00358930();
    FUN_0034f2e4();
    FUN_0034c920();
    FUN_0031d5d8();
    FUN_000776c0();
    FUN_00352c1c();
    FUN_0025d0d4();
    FUN_003552a0();
    FUN_00351aec();
    FUN_001fb194();
    FUN_003544c8(st8, x30);
    FUN_0036b118();
}

/*--------------------------------------------------------------------*
 * FUN_00288ec8 @ 0x00288ec8   (est. sk_swift_element_bind)
 * Ghidra: void FUN_00288ec8(void)
 * Swift element bind: binds the collection descriptor (FUN_00351cc4 /
 * FUN_003524bc), and runs FUN_0031a1f4 / FUN_00353c18 / FUN_0026b1dc.
 * Confidence: low. */
void FUN_00288ec8(word_t a1, word_t a2)
{
    word_t u1;
    long i2;
    wpair_t v;
    (void)a1; (void)a2;

    v.lo = FUN_00351cc4();
    v.hi = FUN_00351cc4();
    i2 = (long)v.hi;
    FUN_003524bc(*(word_t *)(i2 + 0x10), v.lo, i2, *(word_t *)(i2 + 0x18));
    u1 = FUN_0031a1f4();
    FUN_00353c18(u1, u1);
    FUN_0026b1dc();
}

/*--------------------------------------------------------------------*
 * FUN_00288f34 @ 0x00288f34   (est. sk_swift_array_index_set)
 * Ghidra: void FUN_00288f34(undefined8,undefined8,long)
 * Swift Array index set: bounds-checks the index against the collection's
 * bitmap and generation tag, then writes the element via the method table
 * (FUN_00352d10) and cleans up.  Otherwise traps (Swift fatal).
 * Confidence: low (Swift Array subscript set; indirect dispatch).
 * Notes: helpers FUN_003515f0 / FUN_0031a1f4 / FUN_00352c1c /
 *   FUN_00354a34 / FUN_003a261c / FUN_00352414 / FUN_0034c920 /
 *   FUN_0031d5d8 / FUN_0025b7d8 / FUN_00352d10 / FUN_00357ab4 /
 *   FUN_0025e000 / FUN_00351aec / FUN_001fb194 / FUN_00354ef8 /
 *   FUN_0036b118; fatal FUN_003488bc/0034a3ec. */
void FUN_00288f34(word_t p1, word_t p2, long p3)
{
    long i1, i5;
    word_t u2, u3, u4;
    word_t x20 = 0;
    word_t x30;
    uint8_t av6[12];
    long st18;

    FUN_003515f0();
    i1 = (long)FUN_0031a1f4(0, *(word_t *)(p3 + 0x10), *(word_t *)(p3 + 0x18));
    u2 = FUN_00352c1c();
    u3 = FUN_00354a34(u2, p2);
    FUN_003a261c(x20);
    if (((-1 < (long)u3) &&
         (i5 = (long)(uintptr_t)x20, u3 >> ((word_t)*(uint8_t *)(i5 + 0x20) & 0x3f) == 0)) &&
        ((*(word_t *)(i5 + (u3 >> 6) * 8 + 0x38) >> (u3 & 0x3f) & 1) != 0) &&
        (0 == *(int *)(i5 + 0x24))) {
        st18 = i5;
        u4 = FUN_00352414();
        u2 = *(word_t *)(i1 + 0x10);
        if ((u4 & 1) == 0) {
            FUN_0034c920();
            FUN_0031d5d8();
            FUN_0025b7d8();
            i5 = st18;
        }
        FUN_00352d10();
        ((code)(*(word_t *)(0 + 0x20)))
            (0, *(long *)(i5 + 0x30) + *(long *)(0 + 0x48) * u3, u2);
        FUN_0034c920();
        FUN_0031d5d8();
        FUN_00357ab4();
        FUN_0025e000(u3);
        FUN_00351aec(x20, &st18);
        FUN_001fb194();
        FUN_00354ef8(i5, x30);
        FUN_0036b118();
        return;
    }
    FUN_003488bc(1);
    FUN_0034a3ec();
    __builtin_trap();           /* Swift fatal */
}

/*--------------------------------------------------------------------*
 * FUN_002890a0 @ 0x002890a0   (est. sk_swift_array_bind_set)
 * Ghidra: void FUN_002890a0(undefined8,long)
 * Swift Array bind+set: binds the collection then sets the element via
 * FUN_002890d8.
 * Confidence: low. */
void FUN_002890a0(word_t p1, long p2)
{
    word_t u1;

    FUN_003524bc(*(word_t *)(p2 + 0x10), p1, p2, *(word_t *)(p2 + 0x18));
    u1 = FUN_0031a1f4();
    FUN_002890d8(p1, u1);
}

/*--------------------------------------------------------------------*
 * FUN_002890d8 @ 0x002890d8   (est. sk_swift_array_remove_last)
 * Ghidra: void FUN_002890d8(void)
 * Swift Array removeLast: takes the IRQ-save lock (FUN_00357cb4); if the
 * fast path is taken it releases the last element (FUN_003a25d4) and
 * rebuilds; else (when the collection is non-empty) it removes the last
 * element and releases the ref.  Restores IRQ state (FUN_00357c74).
 * Confidence: low (Swift Array removeLast; indirect). */
void FUN_002890d8(word_t a1, word_t a2)
{
    word_t u1, u2;
    (void)a1; (void)a2;
    long e8;
    word_t x20 = 0;
    long i3;
    word_t x30;

    u1 = FUN_00357cb4();
    i3 = (long)(uintptr_t)x20;
    if ((u1 & 1) == 0) {
        FUN_003a25d4(i3);
        FUN_00359874();
        x20 = (word_t)e8;
    } else if (*(long *)(i3 + 0x10) != 0) {
        u2 = FUN_003a261c(i3);
        FUN_00352414();
        FUN_0034e6ec();
        FUN_0031d5d8();
        FUN_00355c28();
        FUN_0025e240(u2);
        FUN_003552a0();
        FUN_003513f0();
        FUN_001fb194();
        FUN_0036b118((void *)i3);
    }
    FUN_00357c74(x30);
}

/*--------------------------------------------------------------------*
 * FUN_00289170 @ 0x00289170   (est. sk_swift_array_remove_first)
 * Ghidra: void FUN_00289170(void)
 * Swift Array removeFirst: if the collection is non-empty runs the
 * remove-first path (FUN_0025baa4 / FUN_00288f34); otherwise traps
 * (Swift fatal).
 * Confidence: low. */
void FUN_00289170(void)
{
    word_t x20 = 0;

    FUN_00351cc4();
    if (*(long *)((uintptr_t)x20 + 0x10) != 0) {
        FUN_0025baa4();
        FUN_00288f34(0, 0, 0);
        return;
    }
    FUN_003488bc(1);
    FUN_0034ae08();
    __builtin_trap();           /* Swift fatal */
}

/*--------------------------------------------------------------------*
 * FUN_00288ca0 @ 0x00288ca0   (est. sk_object_service_process2)
 * Ghidra: void FUN_00288ca0(void)
 * Object-service process variant: CPU (FUN_0008e518), setup + dispatch
 * slots, then a conditional branch on FUN_00365b6c running either the
 * fast path (FUN_0034bd00) or the slow path with a dispatch callback
 * (FUN_0034bc94 / FUN_000839d8 / FUN_0034dfc4 / FUN_003508c0); ends via
 * FUN_00359920 / FUN_0008e500.
 * Confidence: low (object-service run; indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00359c58 / FUN_003517b4 /
 *   FUN_00310d68 / FUN_00348e00 / FUN_0007c1a4 / FUN_0034924c /
 *   FUN_00348f50 / FUN_00350920 / FUN_0031a1dc / FUN_0036b270 /
 *   FUN_0035992c / FUN_003518a0 / FUN_00365b6c / FUN_0034bd00 /
 *   FUN_0034bc94 / FUN_000839d8 / FUN_0034dfc4 / FUN_003508c0 /
 *   FUN_00359920 / FUN_0008e500. */
void FUN_00288ca0(void)
{
    int i1;
    word_t u2;
    word_t x1, x4, x5;
    long e8;
    code m8 = 0;
    long e16;
    wpair_t v4;
    word_t st48;

    FUN_0008e518();
    FUN_00359c58();
    u2 = FUN_003517b4();
    FUN_00310d68(u2, x4);
    FUN_00348e00();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034924c();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_00348f50();
    v4.lo = FUN_00350920();
    FUN_0031a1dc(v4.lo, v4.hi, x5);
    FUN_0036b270((void *)x1);
    FUN_0035992c();
    FUN_003518a0();
    i1 = (int)FUN_00365b6c();
    if (i1 == 0) {
        FUN_0034bd00();
        if (m8) m8();
    } else {
        FUN_0034bc94();
        FUN_000839d8();
        m8 = *(code *)(e16 + 0x20);
        FUN_0034dfc4();
        if (m8) m8();
        FUN_003508c0();
        if (m8) m8();
    }
    u2 = FUN_00359920();
    FUN_0008e500(u2, st48);
}

/*--------------------------------------------------------------------*
 * FUN_002891e4 @ 0x002891e4   (est. sk_object_service_run_c)
 * Ghidra: void FUN_002891e4(void)
 * Object-service run variant: prelude, then either a slow retry path
 * (looping FUN_000a68f4 items through the dispatch slot, breaking on
 * in_ZR) or the fast path; finishes via FUN_00353100 / FUN_0008e500.
 * Confidence: low (object-service run loop; heavy indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00353d70 / FUN_00353ee4 /
 *   FUN_00349b3c / FUN_003493c4 / FUN_0034d698 / FUN_0034ac3c /
 *   FUN_0034d464 / FUN_0007c1a4 / FUN_0034b2f8 / FUN_0035454c /
 *   FUN_00351494 / FUN_00377824 / FUN_000a6f88 / FUN_0034aee4 /
 *   FUN_003499c8 / FUN_0034947c / FUN_00353a00 / FUN_00351ab0 /
 *   FUN_0034ce98 / FUN_00359678 / FUN_003516a8 / FUN_00365b6c /
 *   FUN_003560a8 / FUN_000a6894 / FUN_003510e8 / FUN_00351354 /
 *   FUN_00350878 / FUN_0025a060 / FUN_00352680 / FUN_00350a34 /
 *   FUN_00377bec / FUN_000a68f4 / FUN_00349f3c / FUN_0034e69c /
 *   FUN_000b4390 / FUN_001cc94c / FUN_00084180 / FUN_0035313c /
 *   FUN_00353100 / FUN_0008e500. */
word_t FUN_002891e4(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5)
{
    int zr;
    word_t u1, u2, u3;
    long e8, e8b;
    code m8 = 0;
    long e16, e16b;
    word_t x22, x26;
    wpair_t v5;
    word_t st8;
    word_t l8;
    word_t ret;

    FUN_0008e518();
    FUN_00353d70();
    u1 = FUN_00353ee4();
    FUN_00349b3c();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003493c4();
    FUN_0034d698();
    (*DAT_00658c00)();
    FUN_0034ac3c();
    FUN_0034d464(0);
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b2f8();
    FUN_0035454c();
    FUN_00351494(0);
    u2 = FUN_00377824();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034aee4();
    FUN_003499c8();
    (*DAT_00658c00)(*(word_t *)(e8b + 0x40));
    FUN_0034947c();
    FUN_00353a00();
    FUN_00351ab0();
    if (m8) m8();
    FUN_0034ce98();
    FUN_00359678();
    FUN_003516a8(&l8);
    u3 = FUN_00365b6c();
    if ((u3 & 1) == 0) {
        FUN_003560a8();
        FUN_000a6894();
        FUN_003510e8();
        FUN_00351354();
        if (m8) m8();
        FUN_00350878();
        l8 = FUN_0025a060();
        FUN_00352680(u1);
        FUN_00351354();
        if (m8) m8();
        FUN_00350a34();
        FUN_00377bec();
        m8 = (code)(uintptr_t)FUN_000a68f4();
        while (1) {
            FUN_00350a34();
            if (m8) m8();
            FUN_00349f3c();
            if (zr) break;
            FUN_0034e69c(*(word_t *)(e16 + 0x20));
            u3 = (word_t)m8();
            FUN_000b4390(u3, u3, x22);
            FUN_001cc94c();
            FUN_00084180(*(word_t *)(e16 + 8));
            if (m8) m8();
        }
        FUN_0035313c();
        if (m8) m8(x26, u2);
    } else {
        FUN_00350618(*(word_t *)(e16b + 8));
        if (m8) m8();
    }
    u1 = FUN_00353100();
    FUN_0008e500(u1, st8);
    return ret;
}

/*--------------------------------------------------------------------*
 * FUN_00289480 @ 0x00289480   (est. sk_object_service_process3)
 * Ghidra: void FUN_00289480(void)
 * Object-service process: CPU, setup + dispatch slots, then branches on
 * the collection element count: empty -> 1; single-element -> run the
 * single path with a check (FUN_001f26cc / FUN_0034b3e8); otherwise the
 * multi-element path (FUN_0034ee28 / FUN_003513d8 / FUN_00365b6c) with
 * either retain/run or release teardown.  Result reported via
 * FUN_0008e500.
 * Confidence: low (object-service run; heavy indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00352ce0 / FUN_00350a28 /
 *   FUN_00349a68 / FUN_00349068 / FUN_00350a64 / FUN_0034d464 /
 *   FUN_0007c1a4 / FUN_0034b05c / FUN_0034f604 / FUN_0031a1dc /
 *   FUN_001aeab4 / FUN_00357400 / FUN_00349f3c / FUN_003489dc /
 *   FUN_0034a2f8 / FUN_00356bb0 / FUN_0034c9d8 / FUN_001f26cc /
 *   FUN_0034b3e8 / FUN_0034ee28 / FUN_00359678 / FUN_003513d8 /
 *   FUN_00365b6c / FUN_0036b270 / FUN_00350624 / FUN_00353b58 /
 *   FUN_0025f164 / FUN_00356328 / FUN_0036b118 / FUN_0034c818 /
 *   FUN_001bcc18 / FUN_00357344 / FUN_003a25d4 / FUN_0008e500. */
void FUN_00289480(void)
{
    uint8_t u1;
    int i2;
    word_t u3;
    uint32_t in_w5;
    long e8;
    code m8 = 0;
    long e16, e16b;
    word_t x20 = 0;             /* unaff_x20 */
    word_t x30;

    FUN_0008e518();
    FUN_00352ce0();
    u3 = FUN_00350a28();
    FUN_00349a68();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_00349068();
    FUN_00350a64();
    FUN_0034d464();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b05c();
    if (*(long *)(x20 + 0x10) == 0) {
        in_w5 = 1;
    } else {
        u1 = (uint8_t)(*(long *)(x20 + 0x10) == 1);
        if (u1) {
            FUN_0034f604();
            u3 = FUN_0031a1dc();
            FUN_001aeab4(u3, 0x66dae0);
            FUN_00357400();
            FUN_00349f3c();
            if (u1) {
                FUN_003489dc(0x2ca);
                FUN_0034a2f8();
                __builtin_trap();       /* Swift fatal */
            }
            FUN_00356bb0();
            FUN_0034c9d8();
            in_w5 = (uint32_t)FUN_001f26cc();
            FUN_0034b3e8();
            if (m8) m8();
        } else {
            FUN_0034ee28(*(word_t *)(e16 + 0x10));
            if (m8) m8();
            FUN_0034f604();
            FUN_00359678();
            FUN_003513d8();
            i2 = (int)FUN_00365b6c();
            if (i2 == 0) {
                FUN_0036b270();
                FUN_00350624(u3);
                FUN_00353b58();
                FUN_0025f164();
                FUN_00356328();
                FUN_0036b118();
            } else {
                FUN_0034c818();
                FUN_001bcc18();
                FUN_00357344();
                FUN_003a25d4();
            }
        }
    }
    FUN_0008e500(in_w5 & 1, x30);
}

/*--------------------------------------------------------------------*
 * FUN_002897f0 @ 0x002897f0   (est. sk_object_service_run_d)
 * Ghidra: void FUN_002897f0(void)
 * Object-service run variant: CPU, prelude + dispatch slots, then either
 * a dispatch loop (FUN_000a68f4 items through the slot, breaking on
 * in_ZR) or the fast path; finishes via FUN_00353034 / FUN_0008e500.
 * Confidence: low (object-service run loop; heavy indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00359c58 / FUN_00349720 /
 *   FUN_003490ec / FUN_00350a64 / FUN_0034d464 / FUN_0007c1a4 /
 *   FUN_0034b0c4 / FUN_00349830 / FUN_00352a34 / FUN_00377824 /
 *   FUN_00348d7c / FUN_0034aee4 / FUN_0034a688 / FUN_0034947c /
 *   FUN_00353a00 / FUN_00352370 / FUN_0034bec4 / FUN_00359678 /
 *   FUN_00351b60 / FUN_00365b6c / FUN_00358bc0 / FUN_00352680 /
 *   FUN_003508cc / FUN_0034b278 / FUN_003510ac / FUN_00377bec /
 *   FUN_000a68f4 / FUN_00350a04 / FUN_0034aa54 / FUN_003529a4 /
 *   FUN_00350738 / FUN_0034ede8 / FUN_0025bca4 / FUN_00350560 /
 *   FUN_0034c5ac / FUN_001bcc18 / FUN_003a25d4 / FUN_00353034 /
 *   FUN_0008e500. */
void FUN_002897f0(void)
{
    int zr;
    int i1;
    code cb = 0;
    word_t u3, u4;
    long e8, e8b;
    code m8 = 0;
    long e16, e16b;
    wpair_t v5;
    word_t st18;
    word_t l8;

    FUN_0008e518();
    v5.lo = FUN_00359c58();
    v5.hi = FUN_00359c58();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003490ec();
    FUN_00350a64();
    FUN_0034d464();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0c4();
    FUN_00349830();
    FUN_00352a34();
    FUN_00377824();
    FUN_00348d7c();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034aee4();
    FUN_0034a688();
    (*DAT_00658c00)(*(word_t *)(e8b + 0x40));
    FUN_0034947c();
    FUN_00353a00();
    FUN_00352370();
    if (cb) cb();
    FUN_0034bec4();
    FUN_00359678();
    FUN_00351b60(&l8);
    i1 = (int)FUN_00365b6c();
    if (i1 == 0) {
        FUN_00358bc0();
        FUN_00352680();
        FUN_003508cc();
        if (cb) cb();
        FUN_0034b278();
        FUN_003510ac();
        FUN_00377bec();
        cb = (code)(uintptr_t)FUN_000a68f4();
        do {
            FUN_00350a04();
            if (cb) cb();
            FUN_0034aa54();
            if (zr) {
                FUN_003529a4();
                FUN_00350738();
                if (m8) m8();
                goto finish;
            }
            FUN_0034ede8(*(word_t *)(e16 + 0x20));
            if (m8) m8();
            u3 = thunk_FUN_0025bca4();
            FUN_00350560(*(word_t *)(e16 + 8));
            if (m8) m8();
        } while ((u3 & 1) != 0);
        FUN_003529a4();
        FUN_00350738();
        if (m8) m8();
    } else {
        if (m8) m8(v5.lo);
        FUN_0034c5ac(v5.hi);
        FUN_001bcc18();
        FUN_003a25d4(l8);
    }
finish:
    u4 = FUN_00353034();
    FUN_0008e500(u4, st18);
}

/*--------------------------------------------------------------------*
 * FUN_00289a84 @ 0x00289a84   (est. sk_swift_collection_remove_op)
 * Ghidra: void FUN_00289a84(void)
 * Swift collection remove op: enters the service (FUN_00084220), and if
 * the collection is non-empty runs either the fast remove path
 * (FUN_0034e55c / FUN_00350488 / FUN_00359678 / FUN_00350ad0 / retain /
 * FUN_0034ed88 / FUN_0025f164) or the slow path (FUN_0034d190 /
 * FUN_00289bdc / release).  Exits via FUN_00084234.
 * Confidence: low (Swift collection remove; indirect dispatch).
 * Notes: helpers FUN_00084220 / FUN_00351cf4 / FUN_0034b7e4 /
 *   FUN_0034d3b4 / FUN_0034e55c / FUN_00350488 / FUN_00359678 /
 *   FUN_00350ad0 / FUN_00365b6c / FUN_0036b270 / FUN_0034435c /
 *   FUN_0034ed88 / FUN_0025f164 / FUN_00351d18 / FUN_0036b118 /
 *   FUN_0034d190 / FUN_00289bdc / FUN_003a25d4 / FUN_0035687c /
 *   FUN_00084234. */
void FUN_00289a84(void)
{
    int i1;
    word_t x1, x4, x16;
    long x9, x10;
    code cb = 0;
    wpair_t v2;
    word_t l8;

    FUN_00084220();
    FUN_00351cf4();
    FUN_0034b7e4();
    (*DAT_00658c00)(x16);
    FUN_0034d3b4();
    if (*(long *)(x1 + 0x10) != 0) {
        FUN_0034e55c();
        if (cb) cb();
        v2.lo = FUN_00350488();
        FUN_00359678(v2.lo, v2.hi, x4);
        FUN_00350ad0(&l8);
        i1 = (int)FUN_00365b6c();
        if (i1 == 0) {
            FUN_0036b270();
            *(code *)((x9 - x10) - 0x10) = (code)(uintptr_t)FUN_0034435c;
            FUN_0034ed88();
            FUN_0025f164();
            FUN_00351d18();
            FUN_0036b118();
        } else {
            FUN_0034d190();
            FUN_00289bdc();
            FUN_003a25d4(l8);
        }
    }
    v2.lo = FUN_0035687c();
    FUN_00084234(v2.lo, v2.hi, *(word_t *)((x9 - x10) + 0x48));
}

/*--------------------------------------------------------------------*
 * FUN_00289bdc @ 0x00289bdc   (est. sk_swift_collection_count_less)
 * Ghidra: undefined8 FUN_00289bdc(long,long)
 * Swift collection size comparison: returns the result of FUN_00357b2c
 * when collection1's count is less than collection2's, else 0.
 * Confidence: medium. */
word_t FUN_00289bdc(long p1, long p2)
{
    if (*(unsigned long *)(p1 + 0x10) < *(unsigned long *)(p2 + 0x10))
        return FUN_00357b2c();
    return 0;
}

/*--------------------------------------------------------------------*
 * FUN_00289bf8 @ 0x00289bf8   (est. sk_swift_collection_is_subset)
 * Ghidra: void FUN_00289bf8(void)
 * Swift collection subset test: enters the service, and depending on
 * FUN_00365b6c runs either FUN_00289eac (fast) or FUN_00289ce8 (slow)
 * subset check, releasing the probe buffer; reports the boolean via
 * FUN_00084234.
 * Confidence: low (Swift collection subset; indirect dispatch).
 * Notes: helpers FUN_00084220 / FUN_00355544 / FUN_00350980 /
 *   FUN_00349a68 / FUN_00348f50 / FUN_00350618 / FUN_0034bec4 /
 *   FUN_00359678 / FUN_00350ad0 / FUN_00365b6c / FUN_0034e474 /
 *   FUN_00289eac / FUN_0034b358 / FUN_00289ce8 / FUN_003a25d4 /
 *   FUN_00084234. */
void FUN_00289bf8(void)
{
    int i1;
    uint32_t u2;
    word_t u3;
    word_t x1, x1b, x3, x8, x12;
    code cb = 0;
    word_t x30;
    wpair_t v4;
    word_t l8;

    FUN_00084220();
    FUN_00355544();
    FUN_00350980();
    FUN_00349a68();
    (*DAT_00658c00)(*(word_t *)(x8 + 0x40));
    FUN_00348f50();
    v4.lo = FUN_00350618(*(word_t *)(x12 + 0x10));
    if (cb) cb(v4.lo, v4.hi, x3);
    FUN_0034bec4();
    FUN_00359678();
    FUN_00350ad0(&l8);
    i1 = (int)FUN_00365b6c();
    if (i1 == 0) {
        FUN_0034e474();
        u2 = (uint32_t)FUN_00289eac();
        u3 = x1b;
    } else {
        FUN_0034b358(l8);
        u2 = (uint32_t)FUN_00289ce8();
        FUN_003a25d4(l8);
        u3 = x1;
    }
    FUN_00084234(u2 & 1, u3, x30);
}

/*--------------------------------------------------------------------*
 * FUN_00289ce8 @ 0x00289ce8   (est. sk_swift_set_subset_check)
 * Ghidra: void FUN_00289ce8(void)
 * Swift Set subset check (slow path): CPU, then iterates the shorter of
 * the two sets' bitmaps, checking each element for membership in the
 * other via the dispatch predicate (FUN_00355610 / thunk_FUN_0025bca4).
 * Returns 1 if every element is present, 0 otherwise; releases both ends
 * (FUN_003a25d4 / FUN_0036b118) and exits via FUN_0008e500.
 * Confidence: low (Swift Set subset; indirect membership dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00349720 / FUN_003490ec /
 *   FUN_00359f14 / FUN_0028adc4 / FUN_00357540 / FUN_00356aac /
 *   FUN_0036b270 / FUN_00355610 / FUN_00350470 / FUN_00352c28 /
 *   FUN_0025bca4 / FUN_00350aa0 / FUN_003a25d4 / FUN_0036b118 /
 *   FUN_0008e500. */
word_t FUN_00289ce8(void)
{
    int zr;
    word_t u5, u6, u7;
    long i4;
    wpair_t v8;
    word_t x3, x8, x9, x16;
    code cb = 0;
    word_t x1;
    word_t x22 = 0;             /* unaff_x22 */
    word_t x30;
    long st48;
    word_t l40;
    long st38;
    word_t l30;

    v8.lo = FUN_0008e518();
    v8.hi = FUN_0008e518();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(x8 + 0x40));
    FUN_003490ec();
    if ((*(unsigned long *)(x1 + 0x10) == 0) || (*(unsigned long *)(v8.hi + 0x10) == 0)) {
        u7 = 1;
    } else {
        if (*(unsigned long *)(v8.hi + 0x10) <= *(unsigned long *)(x1 + 0x10))
            v8 = (wpair_t){ v8.lo, v8.hi };
        u6 = -(-1L << ((word_t)*(uint8_t *)(v8.lo + 0x20) & 0x3f));
        u5 = 0xffffffffffffffffull;
        if (u6 < 0x40)
            u5 = ~(-1L << (u6 & 0x3f));
        v8 = (wpair_t){ FUN_00359f14(u5 & *(word_t *)(v8.lo + 0x38)),
                        FUN_00359f14(u5 & *(word_t *)(v8.lo + 0x38)) };
        FUN_0028adc4(v8.lo, v8.hi, x3);
        FUN_00357540(l40);
        FUN_00356aac();
        FUN_0036b270();
        FUN_0036b270((void *)v8.hi);
        do {
            while (l30 == 0) {
                st38++;
                if (SCARRY8(st38, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x289eac) */
                if (x22 <= st38) {
                    u7 = 1;
                    goto finish;
                }
                l30 = *(word_t *)(st48 + st38 * 8);
            }
            u5 = sk_bitreverse64(l30);
            l30 = l30 - 1 & l30;
            FUN_00355610(LZCOUNT(u5) | st38 << 6);
            if (cb) cb();
            FUN_00350470();
            FUN_00352c28();
            u5 = thunk_FUN_0025bca4();
            FUN_00350aa0(*(word_t *)(x16 + 8));
            if (cb) cb();
        } while ((u5 & 1) == 0);
        u7 = 0;
finish:
        FUN_003a25d4(v8.hi);
        FUN_0036b118((void *)x9);
    }
    FUN_0008e500(u7, x30);
}

/*--------------------------------------------------------------------*
 * FUN_00289eac @ 0x00289eac   (est. sk_swift_set_subset_fast)
 * Ghidra: void FUN_00289eac(void)
 * Swift Set subset check (fast path): CPU, prelude + dispatch slots, then
 * iterates the collection bitmap dispatching each element's membership
 * through thunk_FUN_0025bca4; returns via FUN_003548b8 / FUN_0008e500.
 * Confidence: low (Swift Set subset fast; indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00352cec / FUN_00349720 /
 *   FUN_003490ec / FUN_00350a64 / FUN_0034d464 / FUN_0007c1a4 /
 *   FUN_0034b0c4 / FUN_0034a688 / FUN_00348dd8 / FUN_00352370 /
 *   FUN_00377824 / FUN_000a6f88 / FUN_003524a4 / FUN_003506b0 /
 *   FUN_003508b4 / FUN_0034b278 / FUN_00350c80 / FUN_00377bec /
 *   FUN_000a68f4 / FUN_00350738 / FUN_0034aa54 / FUN_0034ede8 /
 *   FUN_0025bca4 / FUN_00350560 / FUN_00352420 / FUN_00358e0c /
 *   FUN_003548b8 / FUN_0008e500. */
word_t FUN_00289eac(void)
{
    int zr;
    word_t u1, u3;
    code cb = 0;
    long e8, e8b;
    long e16, e16b;
    wpair_t v4;
    word_t x3, x9;
    word_t x19 = 0;             /* unaff_x19 */
    word_t st38;

    FUN_0008e518();
    FUN_00352cec();
    FUN_00349720();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003490ec();
    FUN_00350a64();
    FUN_0034d464();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0c4();
    FUN_0034a688();
    (*DAT_00658c00)(*(word_t *)(e8b + 0x40));
    FUN_00348dd8();
    FUN_00352370();
    FUN_00377824();
    FUN_000a6f88();
    FUN_0007c1a4();
    u1 = (*DAT_00658c00)();
    if (*(long *)(x19 + 0x10) != 0) {
        v4.lo = FUN_003524a4(*(word_t *)(e16b + 0x10));
        if (cb) cb(v4.lo, v4.hi, x3);
        FUN_003506b0();
        FUN_003508b4(x9);
        if (cb) cb();
        FUN_0034b278();
        v4.lo = FUN_00350c80();
        FUN_00377bec(v4.lo, v4.hi, u1);
        cb = (code)(uintptr_t)FUN_000a68f4();
        do {
            FUN_00350738();
            if (cb) cb();
            FUN_0034aa54();
            if (zr) break;
            FUN_0034ede8(*(word_t *)(e16 + 0x20));
            if (cb) cb();
            u3 = thunk_FUN_0025bca4();
            FUN_00350560(*(word_t *)(e16 + 8));
            if (cb) cb();
        } while ((u3 & 1) == 0);
        FUN_00352420();
        FUN_00358e0c();
        if (cb) cb();
    }
    u1 = FUN_003548b8();
    FUN_0008e500(u1, st38);
    return u1;
}

/*--------------------------------------------------------------------*
 * FUN_0028a0d4 @ 0x0028a0d4   (est. sk_swift_collection_remove_first)
 * Ghidra: void FUN_0028a0d4(void)
 * Wrapper to FUN_0028a65c.
 * Confidence: low. */
word_t FUN_0028a0d4(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6)
{
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    FUN_0028a65c();
    return 0;
}

/*--------------------------------------------------------------------*
 * FUN_0028a0ec @ 0x0028a0ec   (est. sk_object_service_run_e)
 * Ghidra: void FUN_0028a0ec(void)
 * Object-service run variant: CPU, prelude + dispatch slots, then loops
 * FUN_000a68f4 items through the slot, breaking on in_ZR; finishes via
 * FUN_00350e24 / FUN_0008e500.
 * Confidence: low (object-service run loop; indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00359f8c / FUN_003499f0 /
 *   FUN_00348bbc / FUN_0034b8bc / FUN_00350488 / FUN_0034d464 /
 *   FUN_0007c1a4 / FUN_0034b05c / FUN_0035113c / FUN_0035063c /
 *   FUN_00377824 / FUN_00348e60 / FUN_0034b0d4 / FUN_00352680 /
 *   FUN_003514d0 / FUN_003515cc / FUN_003518a0 / FUN_00377bec /
 *   FUN_000a68f4 / FUN_00350944 / FUN_0034b2c8 / FUN_0034edd8 /
 *   FUN_00350518 / FUN_001cc94c / FUN_00351384 / FUN_00350e24 /
 *   FUN_0008e500. */
void FUN_0028a0ec(void)
{
    int zr;
    code cb = 0;
    long e8;
    long e16;
    wpair_t v2;
    word_t x30;
    word_t l18;

    FUN_0008e518();
    FUN_00359f8c();
    FUN_003499f0();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_00348bbc();
    (*DAT_00658c00)();
    FUN_0034b8bc();
    FUN_00350488();
    FUN_0034d464();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b05c();
    FUN_0035113c();
    FUN_0035063c();
    FUN_00377824();
    FUN_00348e60();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0d4();
    FUN_00352680();
    FUN_003514d0();
    if (cb) cb();
    FUN_003515cc();
    FUN_003518a0();
    FUN_00377bec();
    cb = (code)(uintptr_t)FUN_000a68f4();
    while (1) {
        FUN_00350944();
        if (cb) cb();
        FUN_0034b2c8();
        if (zr) break;
        FUN_0034edd8(*(word_t *)(e16 + 0x20));
        if (cb) cb();
        v2.lo = FUN_00350518();
        FUN_001cc94c(v2.lo, v2.hi, l18);
        FUN_00351384(*(word_t *)(e16 + 8));
        if (cb) cb();
    }
    FUN_00350e24();
    if (cb) cb();
    FUN_0008e500(x30);
}

/*--------------------------------------------------------------------*
 * FUN_0028a2b4 @ 0x0028a2b4   (est. sk_swift_collection_merge)
 * Ghidra: void FUN_0028a2b4(void)
 * Swift collection merge: CPU, prelude, then if a guard passes it loops
 * FUN_000a68f4 items, merging each element (FUN_00288ec8 / FUN_003504c4)
 * through the slot; finishes via FUN_0008e500.
 * Confidence: low (Swift collection merge; indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_003499f0 / FUN_003490ec /
 *   FUN_00350488 / FUN_00310d68 / FUN_000a6f88 / FUN_00348bd8 /
 *   FUN_0034b87c / FUN_00349734 / FUN_000aa4ec / FUN_0035196c /
 *   FUN_00349830 / FUN_003510a0 / FUN_00377824 / FUN_00348cd0 /
 *   FUN_0007c1a4 / FUN_0034b05c / FUN_00353c48 / FUN_00352680 /
 *   FUN_00351ea8 / FUN_00350c2c / FUN_0034b278 / FUN_003507bc /
 *   FUN_00377bec / FUN_000a68f4 / FUN_0034b2c8 / FUN_003511a8 /
 *   FUN_00288ec8 / FUN_003504c4 / FUN_00353154 / FUN_0008e500. */
void FUN_0028a2b4(word_t a1, word_t a2, word_t a3)
{
    int zr;
    word_t u1, u2, u4;
    (void)a1; (void)a2; (void)a3;
    code cb = 0;
    long e8, e8b, e8c, e8d;
    code m8 = 0;
    long e16, e16b, e16c;
    wpair_t v5;
    word_t x1, x3;
    word_t x25, x27, x30;
    word_t l30;

    FUN_0008e518();
    u4 = *(word_t *)(x1 + 0x10);
    FUN_003499f0();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003490ec();
    FUN_00350488();
    u1 = FUN_00310d68();
    FUN_000a6f88();
    (*DAT_00658c00)(*(word_t *)(e8b + 0x40));
    FUN_00348bd8();
    (*DAT_00658c00)();
    FUN_0034b87c();
    FUN_00349734();
    (*DAT_00658c00)(*(word_t *)(e8c + 0x40));
    FUN_000aa4ec();
    FUN_0035196c();
    FUN_00349830();
    FUN_003510a0();
    FUN_00377824();
    FUN_00348cd0();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b05c();
    FUN_00353c48();
    if (e8d != 0) {
        if (m8) m8();
        FUN_00352680(x3);
        FUN_00351ea8();
        FUN_00350c2c();
        if (cb) cb();
        FUN_0034b278();
        FUN_003507bc();
        u2 = FUN_00377bec();
        cb = (code)(uintptr_t)FUN_000a68f4();
        while (1) {
            if (cb) cb(x27, u2);
            FUN_0034b2c8();
            if (zr) break;
            v5.lo = FUN_003511a8(*(word_t *)(e16 + 0x20));
            if (m8) m8(v5.lo, v5.hi, u4);
            FUN_00288ec8(l30, 0);
            if (m8) m8(l30, u1);
            FUN_003504c4(*(word_t *)(e16 + 8));
            if (m8) m8();
        }
        FUN_00353154();
        if (m8) m8(x25, x27);
    }
    FUN_0008e500(x30);
}

/*--------------------------------------------------------------------*
 * FUN_0028a528 @ 0x0028a528   (est. sk_swift_collection_insert_check)
 * Ghidra: void FUN_0028a528(void)
 * Swift collection insert check: enters the service, and depending on
 * FUN_00365b6c runs the fast insert (FUN_0034e474 / FUN_00261134) or the
 * slow path (FUN_0034b358 / FUN_002608cc / FUN_0035310c / release);
 * exits via FUN_00358f90 / FUN_00084234.
 * Confidence: low (Swift collection insert; indirect dispatch).
 * Notes: helpers FUN_00084220 / FUN_00355544 / FUN_00350980 /
 *   FUN_00349a68 / FUN_00348f50 / FUN_00350618 / FUN_0034bec4 /
 *   FUN_00359678 / FUN_00350ad0 / FUN_00365b6c / FUN_0034e474 /
 *   FUN_00261134 / FUN_0034b358 / FUN_002608cc / FUN_0035310c /
 *   FUN_003a25d4 / FUN_00358f90 / FUN_00084234. */
word_t FUN_0028a528(word_t p1, word_t p2, word_t p3, word_t p4, word_t p5, word_t p6)
{
    int i1;
    word_t x3, x8, x12;
    code cb = 0;
    wpair_t v2;
    word_t st38;
    word_t l8;

    FUN_00084220();
    FUN_00355544();
    FUN_00350980();
    FUN_00349a68();
    (*DAT_00658c00)(*(word_t *)(x8 + 0x40));
    FUN_00348f50();
    v2.lo = FUN_00350618(*(word_t *)(x12 + 0x10));
    if (cb) cb(v2.lo, v2.hi, x3);
    FUN_0034bec4();
    FUN_00359678();
    FUN_00350ad0(&l8);
    i1 = (int)FUN_00365b6c();
    if (i1 == 0) {
        FUN_0034e474();
        FUN_00261134();
    } else {
        FUN_0034b358(l8);
        FUN_002608cc();
        FUN_0035310c();
        FUN_003a25d4();
    }
    v2.lo = FUN_00358f90();
    FUN_00084234(v2.lo, v2.hi, st38);
    return v2.lo;
}

/*--------------------------------------------------------------------*
 * FUN_0028a614 @ 0x0028a614   (est. sk_swift_collection_insert_store)
 * Ghidra: void FUN_0028a614(undefined8 x4)
 * Swift collection insert: calls FUN_0028a528 and stores the returned
 * descriptor into the container slot.
 * Confidence: low. */
void FUN_0028a614(word_t p1, long p2, word_t p3, word_t p4)
{
    word_t u1;
    word_t x20 = 0;             /* unaff_x20 */

    u1 = FUN_0028a528(p1, x20, *(word_t *)(p2 + 0x10), p3, *(word_t *)(p2 + 0x18), p4);
    x20 = u1;
}

/*--------------------------------------------------------------------*
 * FUN_0028a618 @ 0x0028a618   (est. sk_swift_collection_insert_store2)
 * Ghidra: void FUN_0028a618(undefined8 x4)
 * Duplicate of FUN_0028a614.
 * Confidence: low. */
void FUN_0028a618(word_t p1, long p2, word_t p3, word_t p4)
{
    word_t u1;
    word_t x20 = 0;             /* unaff_x20 */

    u1 = FUN_0028a528(p1, x20, *(word_t *)(p2 + 0x10), p3, *(word_t *)(p2 + 0x18), p4);
    x20 = u1;
}

/*--------------------------------------------------------------------*
 * FUN_0028a644 @ 0x0028a644   (est. sk_swift_collection_remove_first2)
 * Ghidra: void FUN_0028a644(void)
 * Wrapper to FUN_0028a65c.
 * Confidence: low. */
word_t FUN_0028a644(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5, word_t a6)
{
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    FUN_0028a65c();
    return 0;
}

/*--------------------------------------------------------------------*
 * FUN_0028a65c @ 0x0028a65c   (est. sk_swift_collection_pop)
 * Ghidra: void FUN_0028a65c(void)
 * Swift collection pop: takes the IRQ-save lock (FUN_00357cb4), runs the
 * pop helpers (FUN_00356940 / FUN_00350a64 / FUN_0031a1dc /
 * FUN_00355c28 / FUN_00351b78) and a dispatch callback, then restores
 * IRQ state (FUN_00357c74).
 * Confidence: low (Swift collection pop; indirect). */
void FUN_0028a65c(void)
{
    word_t x4;
    code cb = 0;                /* unaff_x19 */
    word_t x30;
    wpair_t v1, v2;

    FUN_00357cb4();
    v1.lo = FUN_00356940();
    v2.lo = FUN_00350a64();
    FUN_0031a1dc(v2.lo, v2.hi, x4);
    FUN_00355c28();
    FUN_00351b78(v1.lo);
    if (cb) cb();
    FUN_00357c74(v1.hi, x30);
}

/*--------------------------------------------------------------------*
 * FUN_0028a6bc @ 0x0028a6bc   (est. sk_swift_collection_bind_remove)
 * Ghidra: void FUN_0028a6bc(undefined8 x4)
 * Swift collection bind+remove: runs FUN_002891e4 then FUN_0028a6f4 on
 * the container.
 * Confidence: low. */
void FUN_0028a6bc(word_t p1, long p2, word_t p3, word_t p4)
{
    word_t u1;

    u1 = FUN_002891e4(p1, *(word_t *)(p2 + 0x10), p3, *(word_t *)(p2 + 0x18), p4);
    FUN_0028a6f4(u1, p2);
}

/*--------------------------------------------------------------------*
 * FUN_0028a6f4 @ 0x0028a6f4   (est. sk_swift_collection_for_each_hash)
 * Ghidra: void FUN_0028a6f4(void)
 * Swift collection forEach: CPU, prelude, then iterates the collection
 * bitmap dispatching each element (FUN_00357aec / FUN_00288ec8 /
 * thunk_FUN_0025bca4) through the method table; releases the container
 * ref (FUN_0036b118) and exits via FUN_0008e500.
 * Confidence: low (Swift collection forEach; indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00352914 / FUN_00350530 /
 *   FUN_00310d68 / FUN_000a6f88 / FUN_0007c1a4 / FUN_00350428 /
 *   FUN_00349080 / FUN_003493c4 / FUN_0034e6cc / FUN_0034a464 /
 *   FUN_00350464 / FUN_0035216c / FUN_0034fa4c / FUN_0028adc4 /
 *   FUN_00359d38 / FUN_00357aec / FUN_00350a04 / FUN_00356ab8 /
 *   FUN_0025bca4 / FUN_00350914 / FUN_001cc94c / FUN_00352a64 /
 *   FUN_00288ec8 / FUN_00352b14 / FUN_0036b118 / FUN_0008e500. */
void FUN_0028a6f4(void)
{
    word_t u4, u5, u6, u7, u8;
    long i1, i2;
    code cb = 0;
    long e8;
    code m8 = 0;
    long e16;
    word_t x1, x19;
    word_t x20 = 0;             /* unaff_x20 */
    word_t x25 = 0;             /* unaff_x25 */
    word_t x30;
    wpair_t v9;
    long l58, st50, l48, st40, l38;

    FUN_0008e518();
    FUN_00352914();
    u7 = *(word_t *)(x1 + 0x10);
    FUN_00350530();
    u4 = FUN_00310d68();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_00350428();
    FUN_00349080();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003493c4();
    FUN_0034e6cc();
    (*DAT_00658c00)();
    FUN_0034a464();
    (*DAT_00658c00)();
    FUN_00350464();
    FUN_0035216c();
    FUN_0034fa4c();
    FUN_0028adc4(&l58, 0, u7);
    u5 = FUN_00359d38(l48);
    i2 = st40;
    u8 = l38;
    while (1) {
        for (; u8 != 0; u8 = u8 - 1 & u8) {
            u6 = sk_bitreverse64(u8);
            FUN_00357aec(*(word_t *)(e16 + 0x10), u5,
                         *(long *)(l58 + 0x30) + *(long *)(e16 + 0x48) *
                         (LZCOUNT(u6) | i2 << 6));
            if (cb) cb();
            v9.lo = FUN_00350a04(*(word_t *)(e16 + 0x20));
            u5 = (word_t)m8(v9.lo, v9.hi, u7);
            FUN_00356ab8(u5, x20);
            u6 = thunk_FUN_0025bca4();
            if ((u6 & 1) == 0) {
                v9.lo = FUN_00350914();
                FUN_001cc94c(v9.lo, v9.hi, x19);
            } else {
                u5 = FUN_00352a64();
                FUN_00288ec8(u5, x19);
                u5 = FUN_00352b14();
                if (m8) m8(u5, u4);
            }
            u5 = (word_t)m8();
        }
        i1 = i2 + 1;
        if (SCARRY8(i2, 1)) break;
        if (x25 <= i1) {
            FUN_0036b118((void *)l58);
            FUN_0008e500(x30);
            return;
        }
        i2 = i1;
        u8 = *(word_t *)(st50 + i1 * 8);
    }
    __builtin_trap();           /* SoftwareBreakpoint(1,0x28a950) */
}

/*--------------------------------------------------------------------*
 * FUN_0028a950 @ 0x0028a950   (est. sk_swift_collection_empty)
 * Ghidra: void FUN_0028a950(undefined8*)
 * Swift collection empty value: returns the empty sentinel from
 * thunk_FUN_0006e06c into *out.
 * Confidence: medium. */
void FUN_0028a950(word_t *out)
{
    *out = thunk_FUN_0006e06c();
}

/*--------------------------------------------------------------------*
 * FUN_0028a988 @ 0x0028a988   (est. sk_swift_array_remove_first_value)
 * Ghidra: void FUN_0028a988(undefined8*,undefined8,long)
 * Swift Array removeFirst value: calls FUN_0028a0d4 with the container
 * fields and stores the result.
 * Confidence: low. */
void FUN_0028a988(word_t *out, word_t p2, long p3)
{
    word_t u1;
    word_t x20 = 0;             /* unaff_x20 */

    u1 = FUN_0028a0d4(p2, x20, *(word_t *)(p3 + 0x10), p3, *(word_t *)(p3 + 0x18), 0x66dab8);
    *out = u1;
}

/*--------------------------------------------------------------------*
 * FUN_0028a9d0 @ 0x0028a9d0   (est. sk_swift_collection_insert_value)
 * Ghidra: void FUN_0028a9d0(undefined8*,undefined8*,long)
 * Swift collection insert value: calls thunk_FUN_002608cc and stores the
 * result.
 * Confidence: low. */
void FUN_0028a9d0(word_t *out, word_t *src, long p3)
{
    word_t u1;
    word_t x20 = 0;             /* unaff_x20 */

    u1 = thunk_FUN_002608cc(*src, x20, *(word_t *)(p3 + 0x10), *(word_t *)(p3 + 0x18));
    *out = u1;
}

/*--------------------------------------------------------------------*
 * FUN_0028aa08 @ 0x0028aa08   (est. sk_swift_array_remove_first_value2)
 * Ghidra: void FUN_0028aa08(undefined8*,undefined8,long)
 * Swift Array removeFirst value variant: calls FUN_0028a644 and stores.
 * Confidence: low. */
void FUN_0028aa08(word_t *out, word_t p2, long p3)
{
    word_t u1;
    word_t x20 = 0;             /* unaff_x20 */

    u1 = FUN_0028a644(p2, x20, *(word_t *)(p3 + 0x10), p3, *(word_t *)(p3 + 0x18), 0x66dab8);
    *out = u1;
}

/*--------------------------------------------------------------------*
 * FUN_0028aa9c @ 0x0028aa9c   (est. sk_swift_collection_merge_value)
 * Ghidra: void FUN_0028aa9c(undefined8*,undefined8*,long)
 * Swift collection merge value: calls FUN_0028aad4 and stores the result.
 * Confidence: low. */
void FUN_0028aa9c(word_t *out, word_t *src, long p3)
{
    word_t u1;
    word_t x20 = 0;             /* unaff_x20 */

    u1 = FUN_0028aad4(*src, x20, *(word_t *)(p3 + 0x10), *(word_t *)(p3 + 0x18));
    *out = u1;
}

/*--------------------------------------------------------------------*
 * FUN_0028aad4 @ 0x0028aad4   (est. sk_swift_collection_merge_check)
 * Ghidra: undefined8 FUN_0028aad4(void)
 * Swift collection merge check: compares element counts
 * (FUN_0034b85c); when the source count (>>3) is smaller it takes the
 * fast path (FUN_0025f910), else merges via FUN_0028a2b4.
 * Confidence: low. */
word_t FUN_0028aad4(word_t p1, word_t p2, word_t p3, word_t p4)
{
    word_t u1;
    word_t x21 = 0;             /* unaff_x21 */
    wpair_t v2;
    long l40;

    v2.lo = FUN_0034b85c();
    v2.hi = FUN_0034b85c();
    l40 = (long)v2.lo;
    if (*(unsigned long *)(v2.hi + 0x10) >> 3 < *(unsigned long *)(l40 + 0x10)) {
        FUN_0034e70c();
        FUN_00359678();
        FUN_00350548((void *)0xffffffffffffffc8);
        x21 = FUN_0025f910();
    } else {
        FUN_0034e70c();
        u1 = FUN_0031a1dc();
        FUN_00354558(u1, u1);
        FUN_0028a2b4((word_t)&l40, 0, 0);
    }
    return x21;
}

/*--------------------------------------------------------------------*
 * FUN_0028abac @ 0x0028abac   (est. sk_object_service_run_f)
 * Ghidra: void FUN_0028abac(undefined8*,undefined8 x4)
 * Object-service run: calls FUN_002891e4 with the container fields and
 * stores the result.
 * Confidence: low. */
void FUN_0028abac(word_t *out, word_t p2, word_t p3, word_t p4, long p5)
{
    word_t u1;

    u1 = FUN_002891e4(p2, *(word_t *)(p5 + 0x10), p3, *(word_t *)(p5 + 0x18), p4);
    *out = u1;
}

/*--------------------------------------------------------------------*
 * FUN_0028abe8 @ 0x0028abe8   (est. sk_swift_collection_merge_entry)
 * Ghidra: void FUN_0028abe8(undefined8)
 * Swift collection merge entry: runs FUN_00354558 then FUN_0028a2b4 on
 * the value.
 * Confidence: low. */
void FUN_0028abe8(word_t p1)
{
    word_t x1;
    word_t l18;

    l18 = p1;
    FUN_00354558();
    FUN_0028a2b4((word_t)&l18, x1, x1);
}

/*--------------------------------------------------------------------*
 * FUN_0028ac18 @ 0x0028ac18   (est. sk_swift_box_store)
 * Ghidra: void FUN_0028ac18(void)
 * Swift box store: runs FUN_003515b4 then FUN_0028ac40.
 * Confidence: low. */
void FUN_0028ac18(void)
{
    FUN_003515b4();
    FUN_0028ac40();
}

/*--------------------------------------------------------------------*
 * FUN_0028ac40 @ 0x0028ac40   (est. sk_swift_box_value_emit)
 * Ghidra: void FUN_0028ac40(void)
 * Swift box value emit: builds a value (FUN_00352700 / FUN_00352ddc /
 * FUN_0031a1dc) and reports it via FUN_00084180, then runs FUN_001a6ab8.
 * Confidence: low. */
void FUN_0028ac40(void)
{
    wpair_t v;

    FUN_00352700();
    FUN_00352ddc();
    v.lo = FUN_0031a1dc();
    FUN_00084180(v.lo, v.hi, v.lo, 0x66dae0);
    FUN_001a6ab8();
}

/*--------------------------------------------------------------------*
 * FUN_0028acbc @ 0x0028acbc   (est. sk_swift_element_dispatch)
 * Ghidra: void FUN_0028acbc(undefined8,long)
 * Swift element dispatch: prepares the element (FUN_0031ddb0 /
 * FUN_00350404) and dispatches it via the collection method table
 * (param2+0x10).
 * Confidence: low (Swift element dispatch; unrecovered jumptable at
 * 0x28ad0c). */
void FUN_0028acbc(word_t p1, long p2)
{
    long e16;

    FUN_0031ddb0(0, *(word_t *)(p2 + 0x10), *(word_t *)(p2 + 0x18));
    FUN_00350404();
    ((code)(*(word_t *)(e16 + 0x10)))(p1);
}

/*--------------------------------------------------------------------*
 * FUN_0028ad10 @ 0x0028ad10   (est. sk_swift_element_bind2)
 * Ghidra: void FUN_0028ad10(void)
 * Swift element bind: runs FUN_00358c50 / FUN_003524bc / FUN_0031ddb0 /
 * FUN_00349530, dispatches through the method table (0x20), and stores
 * the value into the container slot (+0x20).
 * Confidence: low (Swift element bind; indirect dispatch). */
void FUN_0028ad10(void)
{
    long e16;
    word_t x19;
    long x20 = 0;               /* unaff_x20 */
    uint8_t st50[48];

    FUN_00358c50();
    FUN_003524bc();
    FUN_0031ddb0();
    FUN_00349530();
    ((code)(*(word_t *)(e16 + 0x20)))((word_t)st50);
    FUN_0035a960();
    FUN_00359804();
    *(word_t *)(x20 + 0x20) = x19;
}

/*--------------------------------------------------------------------*
 * FUN_0028ad6c @ 0x0028ad6c   (est. sk_swift_element_bind3)
 * Ghidra: void FUN_0028ad6c(void)
 * Swift element bind variant: builds (FUN_0034ed08 / FUN_0031ddb0 /
 * FUN_00349530), dispatches via method table (0x20), and stores the
 * value into the container slot (+0x20).
 * Confidence: low (Swift element bind; indirect dispatch). */
void FUN_0028ad6c(void)
{
    word_t e8;
    long e16;
    long x20 = 0;               /* unaff_x20 */
    uint8_t st50[32];
    word_t l30;

    FUN_0034ed08();
    FUN_0031ddb0();
    FUN_00349530();
    ((code)(*(word_t *)(e16 + 0x20)))((word_t)st50);
    FUN_00359804(l30);
    *(word_t *)(x20 + 0x20) = e8;
}

/*--------------------------------------------------------------------*
 * FUN_0028adc4 @ 0x0028adc4   (est. sk_swift_array_build_header)
 * Ghidra: void FUN_0028adc4(void)
 * Swift Array header build: runs FUN_00356bf8 / FUN_0028ad6c /
 * FUN_003551f8 and stores the value into the container slot (+0x20).
 * Confidence: low (Swift Array build; indirect). */
void FUN_0028adc4(void)
{
    word_t x19 = 0;             /* unaff_x19 */
    word_t l58;

    FUN_00356bf8();
    FUN_0028ad6c();
    FUN_003551f8();
    *(word_t *)(x19 + 0x20) = l58;
}

/*--------------------------------------------------------------------*
 * FUN_0028ae00 @ 0x0028ae00   (est. sk_swift_value_store_swap)
 * Ghidra: void FUN_0028ae00(undefined8*)
 * Swift value store: releases the container ref (FUN_0036b118) and copies
 * the 5-word value descriptor from src into the container slot.
 * Confidence: low. */
void FUN_0028ae00(word_t *src)
{
    word_t x20 = 0;             /* unaff_x20 */
    word_t u1, u2, u3, u4;

    u3 = src[3];
    u2 = src[2];
    u1 = src[4];
    FUN_0036b118((void *)x20);
    u4 = src[0];
    x20 = src[1];
    x20 = u4;
    x20 = u3;
    x20 = u2;
    x20 = u1;
}

/*--------------------------------------------------------------------*
 * FUN_0028ae54 @ 0x0028ae54   (est. sk_swift_box_alloc2)
 * Ghidra: void FUN_0028ae54(void)
 * Swift box alloc variant: allocates a 0x38-byte box (FUN_0036a908, tag
 * 0x4abf), retains it (FUN_0036b270), and runs FUN_003548f4 /
 * FUN_003507e0.
 * Confidence: low. */
void FUN_0028ae54(void)
{
    FUN_0036a908(0x38, 0x4abf);
    FUN_003548f4();
    FUN_0036b270();
    FUN_003507e0();
}

/*--------------------------------------------------------------------*
 * FUN_0028aeac @ 0x0028aeac   (est. sk_swift_box_value_release)
 * Ghidra: void FUN_0028aeac(void)
 * Swift box value release: reads the box's 7-word descriptor, releases
 * the value ref (FUN_0036b118), copies the payload into the target slot,
 * and (in the branch path) retains the source first then releases it.
 * Finishes via FUN_003544c8 / thunk_FUN_00012568.
 * Confidence: low (Swift box value move; indirect). */
void FUN_0028aeac(void)
{
    word_t u1, u3, u4, u6, u7, u8;
    word_t *pu2, *pu5;
    word_t x30;
    wpair_t v9;

    v9.lo = FUN_00354744();
    v9.hi = FUN_00354744();
    pu5 = (word_t *)(uintptr_t)v9.lo;
    u7 = pu5[1];
    u8 = pu5[0];
    u1 = pu5[2];
    u3 = pu5[3];
    pu2 = (word_t *)(uintptr_t)pu5[5];
    u4 = pu5[6];
    u6 = pu5[4];
    if ((v9.hi & 1) == 0) {
        u7 = pu5[1];
        FUN_0036b118((void *)u4);
        pu2[0] = u8;
        pu2[1] = u7;
        pu2[2] = u1;
        pu2[3] = u3;
        pu2[4] = u6;
    } else {
        FUN_0036b270((void *)u8);
        FUN_0036b118((void *)u4);
        pu2[1] = u7;
        pu2[0] = u8;
        pu2[2] = u1;
        pu2[3] = u3;
        pu2[4] = u6;
        FUN_0036b118((void *)pu5[0]);
    }
    FUN_003544c8(pu5, x30);
    thunk_FUN_00012568();
}

/*--------------------------------------------------------------------*
 * FUN_0028af44 @ 0x0028af44   (est. sk_swift_collection_next_element)
 * Ghidra: void FUN_0028af44(undefined8,long)
 * Swift collection next-element: walks the container's bitmap to find the
 * next set bit, dispatches that element through the collection method
 * table (param2-8 +0x10), and advances the container position.  When the
 * bitmap is exhausted it reports completion via FUN_000839d8.
 * Confidence: low (Swift collection iterator; indirect dispatch).
 * Notes: helpers FUN_001f7d28 / FUN_0001a1c8 / FUN_000839d8;
 *   SoftwareBreakpoint(1,0x28b07c). */
void FUN_0028af44(word_t p1, long p2)
{
    long i1, i5, i7, i8;
    word_t u2, u3, u6, u9, u10;
    word_t *x20 = 0;            /* unaff_x20 */
    long l1, l8;

    u10 = x20[1];
    u9 = x20[0];
    l1 = x20[2];
    l8 = x20[3];
    u6 = x20[4];
    if (u6 == 0) {
        i7 = l8;
        do {
            l8 = i7 + 1;
            if (SCARRY8(i7, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x28b07c) */
            if ((long)(l1 + 0x40u >> 6) <= l8) {
                FUN_000839d8(p1, 1, 1, *(word_t *)(p2 + 0x10));
                u6 = 0;
                goto done;
            }
            u6 = *(word_t *)(x20[1] + l8 * 8);
            i7++;
        } while (u6 == 0);
    }
    u3 = sk_bitreverse64(u6);
    u6 = u6 - 1 & u6;
    i7 = *(long *)(p2 + 0x10);
    u2 = *(word_t *)(p2 + 0x18);
    i5 = FUN_001f7d28(u9);
    ((code)(*(word_t *)(*(long *)(i7 - 8) + 0x10)))
        (p1, i5 + *(long *)(*(long *)(i7 - 8) + 0x48) * (LZCOUNT(u3) | l8 << 6), i7);
    FUN_0001a1c8(u9, i7, u2);
    FUN_000839d8(p1, 0, 1, i7);
    i7 = l8;
done:
    x20[1] = u10;
    x20[0] = u9;
    x20[2] = l1;
    x20[3] = i7;
    x20[4] = u6;
}

/*--------------------------------------------------------------------*
 * FUN_0028b07c @ 0x0028b07c   (est. sk_swift_collection_prepare_next)
 * Ghidra: void FUN_0028b07c(void)
 * Swift collection prepare-next: snapshots the container header, runs the
 * setup helpers (FUN_00353aa0 / FUN_000e15d8 / FUN_00002534 /
 * FUN_00353dd0 / FUN_003505c4 / FUN_00327e08 / FUN_0031ddb0), and
 * dispatches through the method table (0x10) to produce the next value.
 * Confidence: low (Swift collection iterate; indirect dispatch). */
void FUN_0028b07c(word_t a1)
{
    word_t u1;
    (void)a1;
    code cb = 0;
    long e16;
    word_t *x20 = 0;            /* unaff_x20 */
    word_t l_d0, st_c8, st_c0, st_b8, l_b0;
    uint8_t st_a8[48], st_78[40];

    FUN_00353aa0();
    st_c8 = x20[1];
    l_d0 = x20[0];
    st_b8 = x20[3];
    st_c0 = x20[2];
    l_b0 = x20[4];
    FUN_000e15d8();
    FUN_00002534();
    FUN_00353dd0();
    FUN_003505c4();
    FUN_00327e08();
    u1 = FUN_0031ddb0(0, x20[2], x20[3]);
    FUN_0035295c();
    FUN_003513a8(st_78);
    if (cb) cb();
    ((code)(*(word_t *)(e16 + 0x10)))((word_t)st_a8, (word_t)st_78, u1);
    FUN_0034d5ec(st_a8, &l_d0);
    FUN_001f6fac();
    FUN_00358888();
}

/*--------------------------------------------------------------------*
 * FUN_0028b174 @ 0x0028b174   (est. sk_swift_collection_iter_value)
 * Ghidra: void FUN_0028b174(undefined8*)
 * Swift collection iterator value: snapshots the container header, runs
 * FUN_0028b07c, and copies the 0x29-byte result value into out (with the
 * packed concat fields at +0x19 and +0x21).
 * Confidence: low (Swift iterator value; byte packing). */
void FUN_0028b174(word_t *out)
{
    word_t *x20 = 0;            /* unaff_x20 */
    word_t l80, st78, st70, st68, l67, st60, st5f;
    word_t l50, st48, st40, st38, l30;

    st48 = x20[1];
    l50 = x20[0];
    st38 = x20[3];
    st40 = x20[2];
    l30 = x20[4];
    FUN_0028b07c((word_t)&l80);
    out[1] = st78;
    out[0] = l80;
    out[3] = (((l67) << 8) | (st68 & 0xff));
    out[2] = st70;
    *(word_t *)((long)out + 0x21) = st5f;
    *(word_t *)((long)out + 0x19) = ((st60) << 8) | (l67 & 0xff);
}

/*--------------------------------------------------------------------*
 * FUN_0028b1c8 @ 0x0028b1c8   (est. sk_swift_collection_build_empty)
 * Ghidra: void FUN_0028b1c8(void)
 * Swift collection build-empty: runs FUN_00352800 / FUN_0031a1dc /
 * FUN_00354924 / FUN_003a25e0 / FUN_00357f14 / FUN_003515b4 /
 * FUN_001a67bc / FUN_0035a1d4 to produce an empty collection value.
 * Confidence: low. */
void FUN_0028b1c8(word_t a1, word_t a2, word_t a3, word_t a4)
{
    word_t u1;
    (void)a1; (void)a2; (void)a3; (void)a4;
    wpair_t v2;

    FUN_00352800();
    FUN_0031a1dc(0);
    u1 = FUN_00354924();
    FUN_003a25e0(u1, 2);
    v2.lo = FUN_00357f14();
    FUN_003515b4(v2.lo, v2.hi, 7);
    FUN_001a67bc();
    FUN_0035a1d4();
}

/*--------------------------------------------------------------------*
 * FUN_0028b240 @ 0x0028b240   (est. sk_swift_collection_build_value)
 * Ghidra: void FUN_0028b240(undefined8*,long)
 * Swift collection build-value: builds an empty collection via
 * FUN_0028b1c8 and copies the 0x29-byte result into out.
 * Confidence: low. */
void FUN_0028b240(word_t *out, long p2)
{
    word_t *x20 = 0;            /* unaff_x20 */
    word_t l50, st48, st40, st38, l37, st30, st2f;

    FUN_0028b1c8((word_t)&l50, (word_t)x20, *(word_t *)(p2 + 0x10), *(word_t *)(p2 + 0x18));
    out[1] = st48;
    out[0] = l50;
    out[3] = ((l37) << 8) | (st38 & 0xff);
    out[2] = st40;
    *(word_t *)((long)out + 0x21) = st2f;
    *(word_t *)((long)out + 0x19) = ((st30) << 8) | (l37 & 0xff);
}

/*--------------------------------------------------------------------*
 * FUN_0028b28c @ 0x0028b28c   (est. sk_swift_array_remove_if_present)
 * Ghidra: void FUN_0028b28c(void)
 * Swift Array remove-if-present: if the collection is non-empty runs the
 * remove path (FUN_0025baa4 / FUN_00288f34), then reports via
 * FUN_000839d8.
 * Confidence: low. */
void FUN_0028b28c(void)
{
    word_t x20 = 0;             /* unaff_x20 */

    FUN_00353b10();
    if (*(long *)(x20 + 0x10) != 0) {
        FUN_0025baa4();
        FUN_00288f34(0, 0, 0);
    }
    FUN_000839d8();
}

/*--------------------------------------------------------------------*
 * FUN_0028b2ec @ 0x0028b2ec   (est. sk_swift_collection_prepare)
 * Ghidra: void FUN_0028b2ec(void)
 * Swift collection prepare: runs FUN_00358c50 / FUN_003524bc /
 * FUN_0031a1f4 / FUN_00353a30 then FUN_0028b31c.
 * Confidence: low. */
void FUN_0028b2ec(void)
{
    FUN_00358c50();
    FUN_003524bc();
    FUN_0031a1f4();
    FUN_00353a30();
    FUN_0028b31c();
}

/*--------------------------------------------------------------------*
 * FUN_0028b31c @ 0x0028b31c   (est. sk_swift_collection_teardown)
 * Ghidra: void FUN_0028b31c(void)
 * Swift collection teardown: takes the IRQ-save lock (FUN_00357cb4),
 * runs the teardown helpers, and releases the container ref
 * (FUN_0036b118), restoring IRQ state (FUN_00357c74).
 * Confidence: low. */
void FUN_0028b31c(void)
{
    word_t x20 = 0, x30;
    wpair_t v;
    word_t st8;

    FUN_00357cb4();
    FUN_0035098c();
    FUN_003a261c(x20);
    FUN_003589fc();
    FUN_0034f2e4();
    FUN_0034d3e4();
    v.lo = FUN_0031d5d8();
    FUN_00355458(v.lo, v.hi, v.lo);
    FUN_0025ba04();
    FUN_003552a0();
    FUN_00350bfc();
    FUN_001fb194();
    FUN_00357c74(st8, x30);
    FUN_0036b118();
}

/*--------------------------------------------------------------------*
 * FUN_0028b390 @ 0x0028b390   (est. sk_swift_cap_contains)
 * Ghidra: uint FUN_0028b390(undefined8 x3)
 * Swift capability contains: probes the capability set (FUN_0034f414 /
 * FUN_0014f810 / FUN_0034bcf0); if the probe fails returns 0, else runs
 * the success helpers and returns the inverted low bit.
 * Confidence: low (Swift cap set contains). */
uint32_t FUN_0028b390(word_t p1, word_t p2, word_t p3)
{
    uint32_t u1;
    word_t u2;
    code cb = 0, cb2 = 0;

    FUN_0034f414();
    FUN_0014f810(p3);
    FUN_0034bcf0();
    u2 = (word_t)cb();
    if ((u2 & 1) == 0) {
        u1 = 0;
    } else {
        FUN_0034c4fc();
        FUN_0006b6f4();
        FUN_0034df34();
        u1 = (uint32_t)cb2();
        u1 = u1 ^ 1;
    }
    return u1 & 1;
}

/*--------------------------------------------------------------------*
 * FUN_0028b3fc @ 0x0028b3fc   (est. sk_swift_cap_contains_wrap)
 * Ghidra: uint FUN_0028b3fc(void)
 * Wrapper: FUN_00351318 then FUN_0028b390.
 * Confidence: low. */
uint32_t FUN_0028b3fc(void)
{
    FUN_00351318();
    return FUN_0028b390(0, 0, 0) & 1;
}

/*--------------------------------------------------------------------*
 * FUN_0028b428 @ 0x0028b428   (est. sk_swift_collection_subset_cap)
 * Ghidra: uint FUN_0028b428(undefined8,undefined8)
 * Swift collection subset via cap compare: builds two buffers
 * (FUN_00351488 / FUN_00228e78 / FUN_0026a744), runs the compare helpers,
 * and returns the low bit of the comparison.
 * Confidence: low (Swift collection compare; indirect). */
uint32_t FUN_0028b428(word_t p1, word_t p2)
{
    uint32_t u1;
    code cb = 0;
    uint8_t st90[40], st68[40];

    FUN_00351488(st90, p2);
    FUN_00228e78();
    u1 = (uint32_t)FUN_0026a744(st68, st90);
    FUN_0034b440(st68);
    FUN_0031c688();
    FUN_00355d40();
    FUN_00350470();
    if (cb) cb();
    FUN_003199ac(st68);
    FUN_00351f34();
    FUN_00358b54();
    FUN_00365b6c(p1);
    return u1 & 1;
}

/*--------------------------------------------------------------------*
 * FUN_0028b4c8 @ 0x0028b4c8   (est. sk_swift_collection_cap_merge)
 * Ghidra: void FUN_0028b4c8(void)
 * Swift collection cap merge: builds the element buffer
 * (FUN_00352c10 / FUN_00228e78 / FUN_0025cc54), runs the merge helpers
 * (FUN_000e15d8 / FUN_00002534 / FUN_0035401c / FUN_001d88fc), and
 * completes via FUN_003505c4 / FUN_00344e54.
 * Confidence: low (Swift collection merge; indirect). */
void FUN_0028b4c8(void)
{
    word_t u1, e8, u2;
    word_t x20 = 0;             /* unaff_x20 */
    wpair_t v3;
    uint8_t stc0[16], st90[40], st68[40];

    FUN_00352c10();
    FUN_00228e78(st90);
    u1 = FUN_003a261c(x20);
    u2 = x20;
    FUN_00359aec(u1, u1);
    FUN_0025cc54(st68, st90);
    x20 = u2;
    FUN_000e15d8();
    v3.lo = FUN_00002534();
    FUN_0035401c(v3.lo, v3.hi, v3.lo);
    FUN_001d88fc(e8, (void *)0x346580, stc0);
    FUN_003505c4(st68);
    FUN_00344e54();
}

/*--------------------------------------------------------------------*
 * FUN_0028b5b0 @ 0x0028b5b0   (est. sk_swift_collection_cap_merge2)
 * Ghidra: void FUN_0028b5b0(void)
 * Swift collection cap merge variant: prelude, builds buffers
 * (FUN_0034e53c / FUN_00228e78 / FUN_0026af9c), runs the merge helpers,
 * and completes via FUN_003505c4 / FUN_00344e54.
 * Confidence: low (Swift collection merge; indirect). */
void FUN_0028b5b0(void)
{
    long e8, e12;
    code cb = 0;
    wpair_t v1;
    uint8_t stc0[16], st90[40], st68[40];

    FUN_00351cf4();
    FUN_00356ba4();
    FUN_003494e8();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003490ec();
    FUN_00352a28(*(word_t *)(e12 + 0x10));
    if (cb) cb();
    FUN_0034e53c(st90);
    FUN_00228e78();
    FUN_0026af9c(st68, st90);
    FUN_003199ac(st90);
    FUN_000e15d8();
    v1.lo = FUN_00002534();
    FUN_0035401c(v1.lo, v1.hi, v1.lo);
    FUN_001d88fc((void *)0x31ddc8, stc0);
    FUN_003505c4(st68);
    FUN_00344e54();
}

/*--------------------------------------------------------------------*
 * FUN_0028b6cc @ 0x0028b6cc   (est. sk_swift_collection_cap_cmp)
 * Ghidra: void FUN_0028b6cc(undefined8 x4)
 * Swift collection cap compare: runs FUN_0034f1a8 / FUN_0031c688 /
 * FUN_00355d40 / FUN_000dbd0c / FUN_00351f34 / FUN_00358b54 and finishes
 * with FUN_00365b6c.
 * Confidence: low. */
void FUN_0028b6cc(word_t p1, long p2, word_t p3, word_t p4)
{
    word_t x1;
    code cb = 0;

    FUN_0034f1a8(p2, *(word_t *)(p2 + 0x18));
    FUN_0031c688();
    FUN_00355d40();
    FUN_000dbd0c();
    if (cb) cb();
    FUN_00351f34();
    FUN_00358b54();
    FUN_00365b6c(p1, x1, p4, p3, 7);
}

/*--------------------------------------------------------------------*
 * FUN_0028b748 @ 0x0028b748   (est. sk_swift_string_meta)
 * Ghidra: void FUN_0028b748(void)
 * Wrapper to FUN_0025a060.
 * Confidence: low. */
void FUN_0028b748(void)
{
    FUN_0025a060();
}

/*--------------------------------------------------------------------*
 * FUN_0028b770 @ 0x0028b770   (est. sk_swift_array_reserve_check)
 * Ghidra: void FUN_0028b770(undefined8,long)
 * Swift Array reserve: if the collection count is below the reserved
 * capacity it takes the grow path (FUN_00352834 / FUN_0034ce78 /
 * FUN_0025af6c); otherwise it traps (Swift fatal).
 * Confidence: low (Swift Array reserve; fatal on overflow). */
void FUN_0028b770(word_t p1, long p2)
{
    word_t u1;
    code cb = 0;
    word_t x16;
    word_t *x20 = 0;            /* unaff_x20 */
    wpair_t v2;

    u1 = *(word_t *)(p2 + 0x10);
    FUN_003499b4(p1, p1);
    (*DAT_00658c00)(x16);
    FUN_0034d3b4();
    if (*(long *)(x20 + 0x10) < x20[1]) {
        v2.lo = FUN_00352834();
        if (cb) cb(v2.lo, v2.hi, u1);
        FUN_0034ce78();
        FUN_0025af6c();
        return;
    }
    FUN_00350410();
    FUN_003488bc();
    FUN_0034bbdc();
    __builtin_trap();           /* Swift fatal */
}

/*--------------------------------------------------------------------*
 * FUN_0028b85c @ 0x0028b85c   (est. sk_swift_fatal_no_recovery)
 * Ghidra: void FUN_0028b85c(void)
 * Unconditional Swift fatal (no-recovery) path.
 * Confidence: medium. */
void FUN_0028b85c(void)
{
    FUN_003488bc(1);
    FUN_0006f768();
    FUN_0035110c();
    __builtin_trap();           /* Swift fatal */
}

/*--------------------------------------------------------------------*
 * FUN_0028b918 @ 0x0028b918   (est. sk_swift_collection_rebuild)
 * Ghidra: void FUN_0028b918(void)
 * Swift collection rebuild: CPU, prelude + dispatch slots, then iterates
 * the collection bitmap and rebuilds each element through the method
 * table (FUN_00359894 / FUN_00355610 / FUN_00355418 / FUN_0028bdc0 /
 * FUN_003530f4), with a branch on the tag (unaff_x20 == 0x6753a0)
 * selecting between two element-rebuild paths.  Releases the container
 * refs and exits via FUN_00353100 / FUN_0008e500.
 * Confidence: low (Swift collection rebuild; heavy indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00077888 / FUN_00357688 /
 *   FUN_00350a64 / FUN_00310d68 / FUN_003490b8 / FUN_00348abc /
 *   FUN_0034c2d8 / FUN_00349b00 / FUN_003493c4 / FUN_0034e6cc /
 *   FUN_0034dc9c / FUN_0007c028 / FUN_0034d944 / FUN_0034b87c /
 *   FUN_0025a060 / FUN_00354a84 / FUN_0035261c / FUN_0028adc4 /
 *   FUN_00352554 / FUN_00353148 / FUN_0036b270 / FUN_00359894 /
 *   FUN_00355610 / FUN_00355418 / FUN_000dbf08 / FUN_0028bdc0 /
 *   FUN_003530f4 / FUN_00354b74 / FUN_0034b2c8 / FUN_003508f0 /
 *   FUN_003515fc / FUN_0025af6c / FUN_003553d8 / FUN_003598ec /
 *   FUN_0034db58 / FUN_000a6e14 / FUN_00355eec / FUN_0009461c /
 *   FUN_0034d424 / FUN_0031d5d8 / FUN_0025d3d0 / FUN_0036b118 /
 *   FUN_00357274 / FUN_00353100 / FUN_0008e500. */
void FUN_0028b918(void)
{
    code cb = 0;
    bool keep;
    word_t u3, u4, u5, u6, u7;
    long e8, e8b, e8c, e8d;
    word_t x1, x14;
    long e16;
    word_t x20 = 0;             /* unaff_x20 */
    word_t x21 = 0;             /* unaff_x21 */
    word_t x22, x25, x26, x28;
    wpair_t v8;
    word_t le0, la0;
    long l98, l58, st50, l48;
    word_t st40, l38;

    FUN_0008e518();
    FUN_00077888();
    FUN_00357688();
    FUN_00350a64();
    FUN_00310d68();
    FUN_003490b8((void *)0x20);
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_00348abc();
    (*DAT_00658c00)();
    FUN_0034c2d8();
    FUN_00349b00();
    (*DAT_00658c00)(*(word_t *)(e8b + 0x40));
    FUN_003493c4();
    FUN_0034e6cc();
    (*DAT_00658c00)();
    FUN_0034dc9c();
    FUN_0007c028();
    (*DAT_00658c00)(*(word_t *)(e8c + 0x40));
    FUN_003493c4();
    FUN_0034d944();
    (*DAT_00658c00)();
    FUN_0034b87c();
    u4 = FUN_0025a060(*(word_t *)(x21 + 0x10));
    u5 = FUN_00354a84();
    keep = (x20 == 0x6753a0);
    if (!keep) {
        FUN_0035261c();
        FUN_0028adc4();
        u7 = l48 + 0x40u >> 6;
        FUN_00352554(e16 + 8);
        FUN_00353148();
        FUN_0036b270((void *)u4);
        FUN_0036b270((void *)x14);
        do {
            for (; l38 != 0; l38 = l38 - 1 & l38) {
                FUN_00359894();
                FUN_00355610(0 | st40 << 6);
                FUN_00355418(l98, x1, x28);
                if (cb) cb();
                FUN_000dbf08(x25, l98);
                FUN_0028bdc0();
                FUN_003530f4(*(word_t *)(e16 + 8));
                FUN_00354b74();
                if (cb) cb();
                FUN_0034b2c8(x25);
                x22 = x25;
                if (keep) goto fatal;
                v8.lo = FUN_003508f0(*(word_t *)(e8d + 0x20));
                if (cb) cb(v8.lo, v8.hi, x20);
                FUN_003515fc(la0, u5);
                FUN_0025af6c();
                FUN_003553d8();
                st50 = l98;
            }
            st40++;
            if (SCARRY8(st40, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x28bd64) */
            if ((long)u7 <= (long)st40) break;
            l38 = *(word_t *)(st50 + st40 * 8);
        } while (1);
    }
    goto alt;
fatal:
    FUN_0036b118((void *)u5);
    FUN_0036b118((void *)l58);
    FUN_00350bc0((void *)0x18);
    if (cb) cb(x22, le0);
    FUN_0034b348();
    FUN_00354618();
    FUN_003489dc();
    FUN_0034a2f8();
    __builtin_trap();           /* Swift fatal */
alt:
    FUN_0035261c();
    FUN_0028adc4();
    u7 = l48 + 0x40u >> 6;
    FUN_0035a59c();
    FUN_00353148();
    FUN_0036b270((void *)u4);
    FUN_0036b270((void *)x14);
    FUN_00357398();
    while (1) {
        for (; l38 != 0; l38 = l38 - 1 & l38) {
            FUN_003598ec();
            ((code)(*(word_t *)(e16 + 0x10)))
                (x26, *(long *)(l58 + 0x30) + *(long *)(e16 + 0x48) * (0 | st40 << 6), x28);
            FUN_0034db58(x22);
            FUN_0028bdc0();
            FUN_000a6e14(*(word_t *)(e16 + 8));
            if (cb) cb();
            FUN_0034b2c8(x22);
            if (keep) goto fatal;
            FUN_00355eec();
            v8.lo = FUN_0009461c();
            if (cb) cb(v8.lo, v8.hi, 0x6753a0);
            FUN_0034d424();
            u6 = FUN_0031d5d8();
            FUN_0025d3d0(u4, u6);
        }
        st40++;
        if (SCARRY8(st40, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x28bd68) */
        if ((long)u7 <= (long)st40) break;
        l38 = *(word_t *)(st50 + st40 * 8);
    }
    FUN_0036b118((void *)l58);
    FUN_00357274();
    FUN_0036b118();
    u4 = FUN_00353100();
    FUN_0008e500(u4, l98);
}

/*--------------------------------------------------------------------*
 * FUN_0028bdc0 @ 0x0028bdc0   (est. sk_swift_collection_element_step)
 * Ghidra: void FUN_0028bdc0(void)
 * Swift collection element step: prelude + dispatch slots, then the
 * element-step helpers (FUN_00349178 / FUN_00353ba0 / FUN_0034aebc /
 * FUN_00365b6c / FUN_0034bc94 / FUN_000839d8).
 * Confidence: low (Swift collection element step; indirect). */
void FUN_0028bdc0(void)
{
    long e8;
    code cb = 0;

    FUN_00350a28();
    FUN_00356ba4();
    FUN_00349b00();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_00349178();
    FUN_00353ba0();
    if (cb) cb();
    FUN_0034aebc();
    FUN_00365b6c();
    FUN_0034bc94();
    FUN_000839d8();
}

/*--------------------------------------------------------------------*
 * FUN_0028be58 @ 0x0028be58   (est. sk_swift_collection_bind_pop)
 * Ghidra: void FUN_0028be58(void)
 * Swift collection bind+pop: takes the IRQ-save lock (FUN_00357cb4),
 * runs FUN_0028beec, and if a guard is set runs the pop dispatch
 * (FUN_0034d424 / FUN_0031a1dc / FUN_00349530 / method table 0x20);
 * restores IRQ state (FUN_00357c74).
 * Confidence: low (Swift collection pop; indirect). */
void FUN_0028be58(void)
{
    word_t *pu1;
    word_t x1, x1b, u2;
    long x4;
    long e16;
    word_t x30;

    FUN_00357cb4();
    pu1 = (word_t *)FUN_0035215c();
    FUN_0036b270((void *)pu1[0]);
    FUN_000bd3a4();
    FUN_0028beec();
    FUN_0035122c();
    FUN_003a25d4();
    u2 = x1;
    if (x4 != 0) {
        FUN_0034d424();
        FUN_0031a1dc();
        FUN_00349530();
        ((code)(*(word_t *)(e16 + 0x20)))();
        u2 = x1b;
    }
    FUN_00357c74(x4 != 0, u2, x30);
}

/*--------------------------------------------------------------------*
 * FUN_0028c378 @ 0x0028c378   (est. sk_swift_collection_element_cmp)
 * Ghidra: void FUN_0028c378(undefined8,undefined8,long,undefined8)
 * Swift collection element compare: dispatches the element through the
 * collection method table (param3-8 +0x40 / +0x10), runs FUN_00365b6c,
 * and reports the result via FUN_000839d8.
 * Confidence: low (Swift element compare; indirect dispatch). */
void FUN_0028c378(word_t p1, word_t p2, long p3, word_t p4, word_t p5)
{
    uint32_t u1;
    word_t x1;
    long e8, e12;
    (void)p5;

    (*DAT_00658c00)(*(word_t *)(*(long *)(p3 - 8) + 0x40), p2, p2);
    ((code)(*(word_t *)(e12 + 0x10)))
        ((word_t)0xffffffffffffffd0 + -(e8 + 0xf & 0xfffffffffffffff0ull), x1, p3);
    u1 = (uint32_t)FUN_00365b6c(p1, (word_t)0xffffffffffffffd0 + -(e8 + 0xf & 0xfffffffffffffff0ull),
                                p3, p4, 6);
    FUN_000839d8(p1, u1 ^ 1, 1, p4);
}

/*--------------------------------------------------------------------*
 * FUN_0028beec @ 0x0028beec   (est. sk_swift_collection_rebuild2)
 * Ghidra: void FUN_0028beec(void)
 * Swift collection rebuild variant: CPU, prelude + dispatch slots, then
 * iterates the collection bitmap rebuilding each element, branching on
 * the tag (unaff_x20 == 0x6753a0) between two rebuild paths (via
 * FUN_0028c378 / FUN_00350494 / FUN_003510d0 / FUN_00351654, or
 * FUN_00355610 / FUN_00351648 / FUN_00352290 / FUN_00350c38 /
 * FUN_0031d5d8).  Releases container refs and exits via FUN_0008e500.
 * Confidence: low (Swift collection rebuild2; heavy indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_00350b0c / FUN_00350a64 /
 *   FUN_00310d68 / FUN_003490b8 / FUN_0034ab10 / FUN_0034dfa4 /
 *   FUN_0034b8bc / FUN_00349b00 / FUN_0034926c / FUN_0034b87c /
 *   FUN_00349734 / FUN_003493c4 / FUN_0034e6cc / FUN_0034ba68 /
 *   FUN_0025a060 / FUN_00354a84 / FUN_0035261c / FUN_0028adc4 /
 *   FUN_00352554 / FUN_00353148 / FUN_00354128 / FUN_0036b270 /
 *   FUN_00358834 / FUN_003598ec / FUN_00355418 / FUN_00350494 /
 *   FUN_0028c378 / FUN_00354b74 / FUN_00349f3c / FUN_0036b118 /
 *   FUN_00350bc0 / FUN_003510d0 / FUN_00350c68 / FUN_00351654 /
 *   FUN_0025af6c / FUN_0035a59c / FUN_00352b98 / FUN_00358864 /
 *   FUN_00355610 / FUN_00351648 / FUN_00352290 / FUN_00350884 /
 *   FUN_0034d688 / FUN_00350c38 / FUN_00350920 / FUN_0031d5d8 /
 *   FUN_0025d3d0 / FUN_003573c0 / FUN_0008e500. */
void FUN_0028beec(void)
{
    code cb = 0;
    bool keep;
    word_t u1, u2, u6, u8, u9;
    uint8_t u4;
    long l5;
    word_t v6, x1, x3, x4;
    long e8, e8b, e8c, e8d;
    word_t e8_3;
    long e16;
    word_t x19, x21, x24, x26, x27;
    word_t *x20 = 0;            /* unaff_x20 */
    word_t x30;
    wpair_t v10;
    word_t ld8, la8, la0, l90, l78, l60, l58;
    word_t *pu50;
    long l48;
    word_t st40, l38;
    long l30;

    FUN_0008e518();
    l5 = (long)FUN_00350b0c();
    FUN_00350a64();
    FUN_00310d68();
    FUN_003490b8((void *)0x28);
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_0034ab10();
    FUN_0034dfa4();
    (*DAT_00658c00)();
    FUN_0034b8bc();
    FUN_00349b00();
    (*DAT_00658c00)(*(word_t *)(e8b + 0x40));
    FUN_0034926c();
    (*DAT_00658c00)();
    FUN_0034b87c();
    FUN_00349734();
    (*DAT_00658c00)(*(word_t *)(e8c + 0x40));
    FUN_003493c4();
    FUN_0034e6cc();
    (*DAT_00658c00)();
    FUN_0034ba68();
    l90 = FUN_0025a060(*(word_t *)(l5 + 0x10));
    l60 = l90;
    FUN_00354a84(l5);
    keep = (x20 == 0x6753a0);
    l30 = l5;
    if (!keep) {
        FUN_0035261c();
        FUN_0028adc4();
        l78 = l58;
        u9 = l48 + 0x40u >> 6;
        FUN_00352554(e16 + 8, l5);
        FUN_00353148();
        FUN_00354128(e8d + 0x20);
        FUN_0036b270();
        FUN_00358834();
        u8 = l38;
        u2 = st40;
        do {
            for (; u8 != 0; u8 = u8 - 1 & u8) {
                FUN_003598ec();
                FUN_00355418(*(word_t *)(e16 + 0x10), la0,
                             *(long *)(l58 + 0x30) + *(long *)(e16 + 0x48) * (0 | u2 << 6), x21);
                if (cb) cb();
                v10.lo = FUN_00350494(x19);
                FUN_0028c378(v10.lo, v10.hi, (long)(uintptr_t)x20, x3, x4);
                FUN_00350494(*(word_t *)(e16 + 8));
                FUN_00354b74();
                if (cb) cb();
                FUN_00349f3c(x19);
                if (keep) {
                    FUN_0036b118((void *)l90);
                    FUN_0036b118((void *)l58);
                    FUN_00350bc0((void *)0x20);
                    x24 = x19;
                    if (cb) cb(x24, ld8);
                    l90 = 0;
                    goto finish;
                }
                FUN_003510d0((void *)0x30);
                FUN_00350c68(la8);
                if (cb) cb();
                FUN_00351654(la8, l90);
                FUN_0025af6c();
                pu50 = (word_t *)ld8;
            }
            u1 = u2 + 1;
            if (SCARRY8(u2, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x28c374) */
            if ((long)u9 <= (long)u1) goto finish;
            u8 = pu50[u1];
            u2 = u1;
        } while (1);
    }
    FUN_0035261c();
    FUN_0028adc4();
    l78 = l58;
    u9 = l48 + 0x40u >> 6;
    FUN_0035a59c();
    FUN_00353148();
    FUN_00352b98(e8_3 + 0x20);
    FUN_0036b270((void *)l5);
    FUN_00358864();
    u8 = l38;
    u2 = st40;
    {
        word_t *pu7 = pu50;
        while (1) {
            for (; u8 != 0; u8 = u8 - 1 & u8) {
                u1 = sk_bitreverse64(u8);
                FUN_00355610(LZCOUNT(u1) | u2 << 6);
                if (cb) cb(x27, x1, x21);
                v10.lo = FUN_00351648(x24);
                FUN_0028c378(v10.lo, v10.hi, 0x6753a0, x3, x4);
                FUN_00351648(*(word_t *)(e16 + 8));
                if (cb) cb();
                v10.lo = FUN_00352290();
                FUN_00350884(v10.lo, v10.hi, 0x6753a0);
                if (keep) {
                    FUN_0036b118((void *)l90);
                    FUN_0036b118((void *)l58);
                    FUN_00350bc0((void *)0x20);
                    if (cb) cb(x24, ld8);
                    l90 = 0;
                    goto finish;
                }
                FUN_0034d688();
                v10.lo = FUN_00350c38();
                if (cb) cb(v10.lo, v10.hi, 0x6753a0);
                v10.lo = FUN_00350920();
                v6 = FUN_0031d5d8(v10.lo, v10.hi, x4);
                pu7 = &l60;
                FUN_0025d3d0(x26, v6);
                FUN_003573c0();
            }
            u1 = u2 + 1;
            if (SCARRY8(u2, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x28c378) */
            if ((long)u9 <= (long)u1) break;
            u8 = pu7[u1];
            u2 = u1;
        }
    }
finish:
    FUN_0036b118((void *)l78);
    FUN_0008e500(l90, x30);
}

/*--------------------------------------------------------------------*
 * FUN_0028c480 @ 0x0028c480   (est. sk_swift_collection_reserve)
 * Ghidra: void FUN_0028c480(void)
 * Swift collection reserve: runs FUN_00355ce4 / FUN_0036b6ac.
 * Confidence: low. */
void FUN_0028c480(void)
{
    FUN_00355ce4();
    FUN_0036b6ac();
}

/*--------------------------------------------------------------------*
 * FUN_0028c498 @ 0x0028c498   (est. sk_swift_collection_compact)
 * Ghidra: void FUN_0028c498(void)
 * Swift collection compact: enters the service, and while the container
 * count > 0 and its type flag allows compaction, walks the bitmap
 * compacting elements (FUN_0034a340 / FUN_0035516c / FUN_00356688 /
 * FUN_0034bdbc / FUN_0034c194 / FUN_003590cc); exits via FUN_00084234.
 * Confidence: low (Swift collection compact; indirect).
 * Notes: SoftwareBreakpoint(1,0x28c56c). */
void FUN_0028c498(void)
{
    long i2, i3;
    word_t x8, x9, x9b, x10;
    word_t *x20 = 0;            /* unaff_x20 */
    long x25 = 0;               /* unaff_x25 */
    word_t x26 = 0;             /* unaff_x26 */

    FUN_00084220();
    if ((0 < x20[2]) &&
        ((*(uint8_t *)(*(long *)(*(long *)(x20[0] + 0x88) - 8) + 0x52) & 1) != 0)) {
        FUN_0034a340(x20[7]);
        FUN_0035516c();
        i2 = 0;
        do {
            if (x26 == 0) {
                do {
                    i3 = i2 + 1;
                    if (SCARRY8(i2, 1)) __builtin_trap();   /* SoftwareBreakpoint(1,0x28c56c) */
                    if (x25 <= i3) goto out;
                    FUN_00356688();
                    i2 = x8;
                } while (x9 == 0);
                FUN_0034bdbc();
                x26 = x10 & x9b;
            } else {
                FUN_0034c194();
                i3 = i2;
            }
            FUN_003590cc();
            i2 = i3;
        } while (1);
    }
out:
    FUN_00084234();
}

/*--------------------------------------------------------------------*
 * FUN_0028c56c @ 0x0028c56c   (est. sk_swift_collection_compact2)
 * Ghidra: void FUN_0028c56c(void)
 * Swift collection compact: FUN_0028c498 then FUN_00355ce4 /
 * FUN_0036b6ac.
 * Confidence: low. */
void FUN_0028c56c(void)
{
    FUN_0028c498();
    FUN_00355ce4();
    FUN_0036b6ac();
}

/*--------------------------------------------------------------------*
 * FUN_0028c570 @ 0x0028c570   (est. sk_swift_collection_compact3)
 * Ghidra: void FUN_0028c570(void)
 * Duplicate of FUN_0028c56c.
 * Confidence: low. */
void FUN_0028c570(void)
{
    FUN_0028c498();
    FUN_00355ce4();
    FUN_0036b6ac();
}

/*--------------------------------------------------------------------*
 * FUN_0028c5c0 @ 0x0028c5c0   (est. sk_swift_value_release_cb)
 * Ghidra: void FUN_0028c5c0(undefined8*)
 * Swift value release callback: invokes FUN_001fb194 with the value's
 * fields then releases the container ref (FUN_0036b118).
 * Confidence: low. */
void FUN_0028c5c0(word_t *v)
{
    FUN_001fb194(v[2], (word_t)v, *(word_t *)(v[1] + 0x10), *(word_t *)(v[1] + 0x18));
    FUN_0036b118((void *)v[0]);
}

/*--------------------------------------------------------------------*
 * FUN_0028c60c @ 0x0028c60c   (est. sk_swift_element_dispatch2)
 * Ghidra: void FUN_0028c60c(void)
 * Swift element dispatch: binds (FUN_00355694 / FUN_003524bc /
 * FUN_00377824 / FUN_00350404) and dispatches via the method table
 * (+0x28).  Unrecovered jumptable at 0x28c65c.
 * Confidence: low (Swift element dispatch; indirect). */
void FUN_0028c60c(void)
{
    long i1;
    long e16;
    wpair_t v2;

    v2.lo = FUN_00355694();
    v2.hi = FUN_00355694();
    i1 = (long)v2.hi;
    FUN_003524bc(*(word_t *)(i1 + 0x18), v2.lo, i1, *(word_t *)(i1 + 0x10));
    FUN_00377824();
    FUN_00350404();
    ((code)(*(word_t *)(e16 + 0x28)))();
}

/*--------------------------------------------------------------------*
 * FUN_0028c660 @ 0x0028c660   (est. sk_swift_element_dispatch3)
 * Ghidra: void FUN_0028c660(void)
 * Swift element dispatch: binds (FUN_00358054 / FUN_00377824 /
 * FUN_00350404) and dispatches via the method table (+0x10).
 * Unrecovered jumptable at 0x28c6bc.
 * Confidence: low (Swift element dispatch; indirect). */
void FUN_0028c660(void)
{
    long i1;
    long e16;

    i1 = (long)FUN_00358054();
    FUN_00377824(0, *(word_t *)(i1 + 0x18), *(word_t *)(i1 + 0x10));
    FUN_00350404();
    ((code)(*(word_t *)(e16 + 0x10)))();
}

/*--------------------------------------------------------------------*
 * FUN_0028c754 @ 0x0028c754   (est. sk_swift_element_subscript)
 * Ghidra: void FUN_0028c754(undefined8,long)
 * Swift element subscript: dispatches the element at index param2+0x28
 * via the collection method table (param2+0x10 -> +0x10).
 * Confidence: low (Swift element subscript; unrecovered jumptable at
 * 0x28c780). */
void FUN_0028c754(word_t p1, long p2)
{
    long x20 = 0;               /* unaff_x20 */

    ((code)(*(word_t *)(*(long *)(*(long *)(p2 + 0x10) - 8) + 0x10)))
        (p1, x20 + *(int *)(p2 + 0x28));
}

/*--------------------------------------------------------------------*
 * FUN_0028c784 @ 0x0028c784   (est. sk_swift_element_dispatch4)
 * Ghidra: void FUN_0028c784(void)
 * Swift element dispatch: binds (FUN_00358054 / FUN_00377824 /
 * FUN_00350404) and dispatches via the method table (+0x10).
 * Unrecovered jumptable at 0x28c7d4.
 * Confidence: low. */
void FUN_0028c784(void)
{
    long i1;
    long e16;

    i1 = (long)FUN_00358054();
    FUN_00377824(0, *(word_t *)(i1 + 0x18), *(word_t *)(i1 + 0x10));
    FUN_00350404();
    ((code)(*(word_t *)(e16 + 0x10)))();
}

/*--------------------------------------------------------------------*
 * FUN_0028c7d8 @ 0x0028c7d8   (est. sk_swift_element_dispatch_cb)
 * Ghidra: void FUN_0028c7d8(void)
 * Wrapper to FUN_0028c808.
 * Confidence: low. */
void FUN_0028c7d8(word_t a1, word_t a2, word_t a3)
{
    (void)a1; (void)a2; (void)a3;
    FUN_0028c808();
}

/*--------------------------------------------------------------------*
 * FUN_0028c7f0 @ 0x0028c7f0   (est. sk_swift_element_dispatch_cb2)
 * Ghidra: void FUN_0028c7f0(void)
 * Wrapper to FUN_0028c808.
 * Confidence: low. */
void FUN_0028c7f0(word_t a1, word_t a2, word_t a3)
{
    (void)a1; (void)a2; (void)a3;
    FUN_0028c808();
}

/*--------------------------------------------------------------------*
 * FUN_0028c808 @ 0x0028c808   (est. sk_swift_element_dispatch_call)
 * Ghidra: void FUN_0028c808(undefined8,undefined8,long,code*)
 * Swift element dispatch call: gets the current TCB (FUN_000867ec), runs
 * the callback on the element type (param3+0x18), and reports the result
 * via FUN_00100efc.
 * Confidence: low (Swift element dispatch; indirect callback). */
void FUN_0028c808(word_t p1, word_t p2, long p3, code cb)
{
    code m8 = 0;
    word_t x19 = 0;             /* unaff_x19 */
    wpair_t v;

    FUN_000867ec();
    v.lo = (word_t)cb(*(word_t *)(p3 + 0x18));
    FUN_00100efc(v.lo, v.lo, v.hi, *(word_t *)(x19 + 0x10));
    if (m8) m8();
}

/*--------------------------------------------------------------------*
 * FUN_0028c868 @ 0x0028c868   (est. sk_object_service_run_g)
 * Ghidra: void FUN_0028c868(void)
 * Object-service run variant: CPU, prelude + dispatch slots, method-table
 * dispatch (FUN_00350bf0 / +0x10 / +0x20 / +8), and the epilogue
 * FUN_0008e500.
 * Confidence: low (object-service run; heavy indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_0034a3c4 / FUN_00377824 /
 *   FUN_00348bf8 / FUN_003722e4 / FUN_00348d64 / FUN_003493c4 /
 *   FUN_0034c2d8 / FUN_0034dbb8 / FUN_00377bec / FUN_0034da98 /
 *   FUN_00310e08 / FUN_000a6f88 / FUN_0007c1a4 / FUN_00350428 /
 *   FUN_003508e4 / FUN_0035063c / FUN_0034bdfc / FUN_00310b98 /
 *   FUN_00351130 / FUN_00350bf0 / FUN_00352474 / FUN_0034ee48 /
 *   FUN_0009e234 / FUN_003595d8 / FUN_00350c38 / FUN_00352eb4 /
 *   FUN_00350600 / FUN_0034de34 / FUN_00351e54 / FUN_00351450 /
 *   FUN_0008e500. */
void FUN_0028c868(void)
{
    word_t u1, u3, u4, u5;
    int i2;
    word_t e8, e8_1;
    code cb = 0;
    long x9;
    code m9 = 0;
    long e16;
    long l6;
    code pc7 = 0, pc8 = 0;
    long x20, x22, x23, x24;
    wpair_t v9;

    v9.lo = FUN_0008e518();
    v9.hi = FUN_0008e518();
    l6 = (long)v9.lo;
    u5 = *(word_t *)(l6 + 0x10);
    u1 = *(word_t *)(l6 + 0x18);
    u3 = FUN_0034a3c4();
    FUN_00377824(u3, u1);
    FUN_00348bf8();
    FUN_003722e4();
    FUN_00348d64();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003493c4();
    (*DAT_00658c00)();
    FUN_0034c2d8();
    FUN_0034dbb8(u1);
    FUN_00377bec();
    FUN_0034da98();
    u3 = FUN_00310e08();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_00350428();
    FUN_003508e4();
    FUN_0035063c();
    u4 = FUN_00377824();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034bdfc();
    FUN_00310b98(u1);
    FUN_00351130();
    if (m9) m9();
    i2 = *(int *)(l6 + 0x24);
    l6 = *(long *)(x24 - 8);
    pc7 = *(code *)(l6 + 0x10);
    FUN_00350bf0();
    if (pc7) pc7();
    if (pc7) pc7(x22 + *(int *)(x23 + 0x30), x20 + i2);
    FUN_00352474();
    FUN_0034ee48();
    if (m9) m9();
    i2 = *(int *)(x23 + 0x30);
    pc8 = *(code *)(l6 + 0x20);
    FUN_0009e234();
    if (pc8) pc8();
    pc7 = *(code *)(l6 + 8);
    if (pc7) pc7(x9 + i2);
    ((code)(*(word_t *)(e16 + 0x20)))(x9, x22);
    FUN_003595d8((long)*(int *)(x23 + 0x30));
    if (pc8) pc8();
    FUN_00350c38();
    if (pc7) pc7();
    FUN_00377bec(u1, u5, u4, (void *)0x60e208, (void *)0x60e220);
    FUN_00352eb4();
    FUN_00350600(e8, e8_1);
    if (cb) cb();
    u5 = FUN_0034de34();
    if (cb) cb(u5, u3);
    FUN_00351e54();
    FUN_00351450();
    if (cb) cb();
    FUN_0008e500(v9.hi);
}

/*--------------------------------------------------------------------*
 * FUN_0028cb54 @ 0x0028cb54   (est. sk_swift_element_bind_cb)
 * Ghidra: void FUN_0028cb54(void)
 * Swift element bind callback: binds the element (FUN_0034c084 /
 * FUN_00359490 / FUN_00353d94 / FUN_00352c1c) and dispatches.
 * Confidence: low. */
void FUN_0028cb54(void)
{
    word_t u1;
    code cb = 0;
    word_t x19 = 0;             /* unaff_x19 */

    FUN_0034c084();
    FUN_00359490();
    u1 = FUN_00353d94();
    FUN_00352c1c(u1, *(word_t *)(x19 + 0x10));
    if (cb) cb();
}

/*--------------------------------------------------------------------*
 * FUN_0028cba8 @ 0x0028cba8   (est. sk_swift_string_emit_cb)
 * Ghidra: void FUN_0028cba8(void)
 * Swift string emit callback: runs FUN_0008409c / FUN_003584b4 and
 * dispatches through FUN_00027818.
 * Confidence: low. */
void FUN_0028cba8(void)
{
    code cb = 0;

    FUN_0008409c();
    FUN_003584b4();
    cb = (code)(uintptr_t)FUN_00027818();
    if (cb) cb();
}

/*--------------------------------------------------------------------*
 * FUN_0028cc00 @ 0x0028cc00   (est. sk_swift_element_emit_cb)
 * Ghidra: void FUN_0028cc00(undefined8,undefined8,long)
 * Swift element emit callback: enters the service, binds the element
 * (FUN_00349ef4 / FUN_0031afcc / FUN_0034cdd8), dispatches, and exits
 * via FUN_00084234.
 * Confidence: low (Swift element emit; indirect). */
void FUN_0028cc00(word_t p1, word_t p2, word_t p3, word_t p4)
{
    code cb = 0;
    word_t x19 = 0;             /* unaff_x19 */
    word_t x30;
    wpair_t v;

    FUN_00084220();
    FUN_00349ef4();
    v.lo = FUN_0031afcc(*(word_t *)(p3 + 0x18));
    FUN_0034cdd8(v.lo, v.hi, *(word_t *)(x19 + 0x10));
    if (cb) cb();
    FUN_00084234(x30);
}

/*--------------------------------------------------------------------*
 * FUN_0028cc5c @ 0x0028cc5c   (est. sk_swift_string_emit)
 * Ghidra: void FUN_0028cc5c(void)
 * Swift string emit: enters the service, binds the string (FUN_00349944 /
 * FUN_003192d8 / FUN_0034b508), dispatches, and exits via FUN_00084234.
 * Confidence: low. */
void FUN_0028cc5c(void)
{
    long x3;
    code cb = 0;
    word_t x30;

    FUN_00084220();
    FUN_00349944();
    FUN_003192d8(*(word_t *)(x3 + 0x18));
    FUN_0034b508();
    if (cb) cb();
    FUN_00084234(x30);
}

/*--------------------------------------------------------------------*
 * FUN_0028ccbc @ 0x0028ccbc   (est. sk_swift_element_emit_cb2)
 * Ghidra: void FUN_0028ccbc(undefined8,undefined8,long)
 * Swift element emit callback: TCB (FUN_000867ec), binds the element
 * (FUN_0035647c), reports via FUN_00100efc, and dispatches.
 * Confidence: low. */
void FUN_0028ccbc(word_t p1, word_t p2, long p3)
{
    code cb = 0;
    word_t x19 = 0;             /* unaff_x19 */
    wpair_t v;

    FUN_000867ec();
    v.lo = FUN_0035647c(*(word_t *)(p3 + 0x18));
    FUN_00100efc(v.lo, v.hi, *(word_t *)(x19 + 0x10));
    if (cb) cb();
}

/*--------------------------------------------------------------------*
 * FUN_0028cd14 @ 0x0028cd14   (est. sk_swift_string_slice_dispatch)
 * Ghidra: void FUN_0028cd14(undefined8 x5)
 * Swift string slice dispatch: binds the element (FUN_00027754 /
 * FUN_00310c44) and dispatches with the FUN_00343cac callback.
 * Confidence: low (Swift string slice; indirect). */
void FUN_0028cd14(word_t p1, word_t p2, word_t p3, word_t p4)
{
    word_t u1, u2;
    code cb = 0;
    uint8_t st90[16];
    word_t l80, st78, l70;

    u1 = *(word_t *)(p4 + 0x10);
    l70 = *(word_t *)(p4 + 0x18);
    l80 = u1;
    st78 = p3;
    u2 = FUN_00027754(l70);
    cb = (code)(uintptr_t)FUN_00310c44();
    if (cb) cb(p1, (code)(uintptr_t)FUN_00343cac, st90, p3, u1, u2);
}

/*--------------------------------------------------------------------*
 * FUN_0028d1fc @ 0x0028d1fc   (est. sk_swift_box_alloc3)
 * Ghidra: undefined* FUN_0028d1fc(long*,undefined8,undefined8)
 * Swift box alloc: allocates a 0x28-byte box (FUN_0036a908, tag 0xdfbf),
 * initialises it via FUN_0028d270, stores the value at +0x20, returns
 * the value metadata (DAT_003471a4).
 * Confidence: low (Swift box alloc). */
word_t *FUN_0028d1fc(long *box, word_t p2, word_t p3)
{
    long l1;
    word_t u2;

    l1 = (long)FUN_0036a908(0x28, 0xdfbf);
    *box = l1;
    u2 = (word_t)FUN_0028d270(l1, p2, p3);
    *(word_t *)(l1 + 0x20) = u2;
    return (word_t *)0x3471a4;
}

/*--------------------------------------------------------------------*
 * FUN_0028d270 @ 0x0028d270   (est. sk_swift_box_init3)
 * Ghidra: undefined1[16] FUN_0028d270(long*,undefined8,long)
 * Swift box init: fills the box header, allocates element storage
 * (FUN_0036a908, tag 0x8eff), and initialises it via FUN_001ff258.
 * Returns {&DAT_003471a8, storage}.
 * Confidence: low (Swift box init). */
uint8_t *FUN_0028d270(long *box, word_t p2, long p3)
{
    word_t u1;
    long l2;
    static uint8_t ret[16];

    u1 = FUN_00027754(*(word_t *)(p3 + 0x18));
    l2 = (long)FUN_00377824(0, u1, *(word_t *)(p3 + 0x10), (void *)0x611b24, (void *)0x611b34);
    box[0] = l2;
    l2 = *(long *)(l2 - 8);
    box[1] = l2;
    l2 = (long)FUN_0036a908(*(word_t *)(l2 + 0x40), 0x8eff);
    box[2] = l2;
    FUN_001ff258(l2, p2, p3);
    *(word_t *)&ret[8] = (word_t)l2;
    *(word_t *)&ret[0] = 0x3471a8;
    return ret;
}

/*--------------------------------------------------------------------*
 * FUN_0028d344 @ 0x0028d344   (est. sk_swift_element_emit3)
 * Ghidra: void FUN_0028d344(undefined8,long)
 * Swift element emit: binds (FUN_0034a32c / FUN_00377824 /
 * FUN_00352efc / FUN_00310d68 / FUN_0034b690) and reports via
 * FUN_000839d8.
 * Confidence: low. */
void FUN_0028d344(word_t p1, long p2)
{
    word_t e8;

    FUN_0034a32c(*(word_t *)(p2 + 0x18), p1, p2, *(word_t *)(p2 + 0x10));
    FUN_00377824(0xff, e8);
    FUN_00352efc();
    FUN_00310d68();
    FUN_0034b690();
    FUN_000839d8();
}

/*--------------------------------------------------------------------*
 * FUN_0028d3f8 @ 0x0028d3f8   (est. sk_swift_string_slice_convert)
 * Ghidra: undefined8 FUN_0028d3f8(long,undefined8,undefined8,long)
 * Swift string slice convert: builds the string descriptor, runs the
 * slice dispatch (FUN_0028cd14), and depending on the conversion flag
 * either takes the direct path (FUN_00284424) or the buffer path
 * (FUN_0021867c / FUN_0031090c / FUN_0028cc00); returns the converted
 * value.
 * Confidence: low (Swift string slice conversion; indirect).
 * Notes: helpers FUN_00377824 / FUN_00027754 / FUN_0031e134 /
 *   FUN_003722e4 / FUN_0028cd14 / FUN_00284424 / FUN_0021867c /
 *   FUN_0031090c / FUN_0028cc00. */
word_t FUN_0028d3f8(long p1, word_t p2, word_t p3, long p4)
{
    long l1, l2, l3, l5;
    word_t u4, u6;
    word_t ld0, stc8;
    uint8_t stc0[16];
    word_t lb0, sta8, la0, st98;
    uint8_t st80[16];
    word_t l70;
    char l68;

    u4 = *(word_t *)(p4 + 0x18);
    stc8 = *(word_t *)(p4 + 0x18);
    u6 = *(word_t *)(p4 + 0x10);
    ld0 = u6;
    l1 = (long)FUN_00377824(0, u4, u6, (void *)0x60e208, (void *)0x60e230);
    l3 = *(long *)(l1 - 8);
    (*DAT_00658c00)(*(long *)(l3 + 0x40) + 0xf & 0xfffffffffffffff0ull);
    l5 = (long)&ld0 - 0;
    sta8 = stc8;
    lb0 = ld0;
    la0 = p2;
    st98 = p3;
    u4 = FUN_00027754(u4);
    u4 = FUN_00377824(0xff, u4, u6, (void *)0x611b24, (void *)0x611b34);
    u4 = FUN_0031e134(0xff, u4);
    u4 = FUN_003722e4(0, u4, 0x677880, 0, 0);
    FUN_0028cd14((word_t)st80, (word_t)(uintptr_t)FUN_00343cf8, (word_t)stc0, (word_t)p4);
    if (l68 == 1) {
        l70 = FUN_00284424(p1, p2, p3, p4, 0x66dcc0);
    } else {
        FUN_0021867c(l5, p4);
        l2 = (long)FUN_0031090c(0, p4, 0x66dc58);
        FUN_0028cc00(p1 + *(int *)(l2 + 0x24), l5, l70, p4);
        ((code)(*(word_t *)(l3 + 8)))(l5, l1);
        ((code)(*(word_t *)(*(long *)(p4 - 8) + 0x20)))(p1);
    }
    return l70;
}

/*--------------------------------------------------------------------*
 * FUN_0028d628 @ 0x0028d628   (est. sk_swift_string_slice_dispatch2)
 * Ghidra: void FUN_0028d628(undefined8 x4)
 * Swift string slice dispatch wrapper: FUN_0028cd14 with swapped args.
 * Confidence: low. */
void FUN_0028d628(word_t p1, word_t p2, word_t p3, word_t p4)
{
    FUN_0028cd14(p1, p2, p4, p3);
}

/*--------------------------------------------------------------------*
 * FUN_0028d62c @ 0x0028d62c   (est. sk_swift_string_slice_dispatch3)
 * Ghidra: void FUN_0028d62c(undefined8 x4)
 * Duplicate of FUN_0028d628.
 * Confidence: low. */
void FUN_0028d62c(word_t p1, word_t p2, word_t p3, word_t p4)
{
    FUN_0028cd14(p1, p2, p4, p3);
}

/*--------------------------------------------------------------------*
 * FUN_0028d64c @ 0x0028d64c   (est. sk_swift_string_value_build)
 * Ghidra: void FUN_0028d64c(undefined1(*)[16],undefined8 x7)
 * Swift string value build: resolves the element type (FUN_00027754 /
 * FUN_00377824), builds via FUN_0028d6e8, and stores the 16-byte value.
 * Confidence: low (Swift string value build). */
void FUN_0028d64c(uint8_t (*out)[16], word_t p2, word_t p3, word_t p4, word_t p5,
                  word_t p6, word_t p7)
{
    word_t u1;
    uint8_t av2[16];

    u1 = FUN_00027754(p7);
    u1 = FUN_00377824(0, u1, p6, (void *)0x611b24, (void *)0x611b34);
    FUN_0028d6e8(p4, p5, p2, p3, u1);
    memcpy(*out, av2, 16);
    *(word_t *)out[1] = p2;
}

/*--------------------------------------------------------------------*
 * FUN_0028d6e8 @ 0x0028d6e8   (est. sk_swift_string_value_alloc)
 * Ghidra: void FUN_0028d6e8(void)
 * Swift string value alloc: wrapper to FUN_0031ddfc.
 * Confidence: low. */
void FUN_0028d6e8(word_t a1, word_t a2, word_t a3, word_t a4, word_t a5)
{
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5;
    FUN_0031ddfc();
}

/*--------------------------------------------------------------------*
 * FUN_0028d700 @ 0x0028d700   (est. sk_swift_string_emit4)
 * Ghidra: void FUN_0028d700(undefined8 x3)
 * Swift string emit: binds the string (FUN_00349ef4 / FUN_00354930 /
 * FUN_00351888) and dispatches.
 * Confidence: low. */
void FUN_0028d700(word_t p1, word_t p2, word_t p3)
{
    word_t u1;
    code cb = 0;
    word_t x21 = 0;             /* unaff_x21 */

    FUN_00349ef4();
    u1 = FUN_00354930(p3);
    FUN_00351888(u1, *(word_t *)(x21 + 0x10));
    if (cb) cb();
}

/*--------------------------------------------------------------------*
 * FUN_0028d754 @ 0x0028d754   (est. sk_swift_string_emit5)
 * Ghidra: void FUN_0028d754(undefined8 x3)
 * Swift string emit: TCB (FUN_000867ec), binds the string (FUN_003196e8 /
 * FUN_00351c88), and dispatches.
 * Confidence: low. */
void FUN_0028d754(word_t p1, word_t p2, word_t p3)
{
    word_t u1;
    code cb = 0;
    word_t x21 = 0;             /* unaff_x21 */

    FUN_000867ec();
    u1 = FUN_003196e8(p3);
    FUN_00351c88(u1, u1, *(word_t *)(x21 + 0x10));
    if (cb) cb();
}

/*--------------------------------------------------------------------*
 * FUN_0028d7cc @ 0x0028d7cc   (est. sk_object_service_run_h)
 * Ghidra: void FUN_0028d7cc(undefined8 x3)
 * Object-service run variant: CPU, prelude + dispatch slots, method-table
 * dispatch (FUN_00350bf0-style +0x10/+0x20/+8), and the epilogue
 * FUN_0008e500.
 * Confidence: low (object-service run; heavy indirect dispatch).
 * Notes: helpers FUN_0008e518 / FUN_003514b8 / FUN_0034a3c4 /
 *   FUN_003515fc / FUN_00377824 / FUN_0034b0b4 / FUN_00355adc /
 *   FUN_003722e4 / FUN_00348e60 / FUN_003489c0 / FUN_0034c074 /
 *   FUN_0034d130 / FUN_00377bec / FUN_0034e414 / FUN_00310e08 /
 *   FUN_000a6f88 / FUN_0007c1a4 / FUN_0034b0c4 / FUN_003597b4 /
 *   FUN_000b43d0 / FUN_00359594 / FUN_0035399c / FUN_003508a8 /
 *   FUN_00351f4c / FUN_00351354 / FUN_0035a190 / FUN_003508f0 /
 *   FUN_00350470 / FUN_0028c7d8 / FUN_00353154 / FUN_00351360 /
 *   FUN_00356810 / FUN_00352ecc / FUN_0035949c / FUN_00351e3c /
 *   FUN_00350df4 / FUN_00348b94 / FUN_00349530 / FUN_00351d00 /
 *   FUN_0008e500. */
void FUN_0028d7cc(word_t p1, word_t p2, word_t p3)
{
    int i1;
    word_t u2, u5;
    long l3, l4;
    word_t e8, e8_1;
    code cb = 0;
    long e16, e16b, e16c;
    long x20, x24, x26, x27;
    word_t x30;
    wpair_t v8, v9;
    code pc6 = 0, pc7 = 0;

    v8.lo = FUN_0008e518();
    v8.hi = FUN_0008e518();
    l4 = (long)v8.hi;
    FUN_003514b8(p3);
    u5 = *(word_t *)(l4 + 0x10);
    FUN_0034a3c4();
    FUN_003515fc();
    u2 = FUN_00377824();
    FUN_0034b0b4();
    FUN_00355adc();
    FUN_003722e4();
    FUN_00348e60();
    (*DAT_00658c00)(*(word_t *)(e8 + 0x40));
    FUN_003489c0();
    (*DAT_00658c00)();
    FUN_0034c074();
    FUN_0034d130();
    FUN_00377bec();
    FUN_0034e414();
    l3 = (long)FUN_00310e08();
    FUN_000a6f88();
    FUN_0007c1a4();
    (*DAT_00658c00)();
    FUN_0034b0c4();
    FUN_003597b4();
    pc6 = *(code *)(e16b + 0x10);
    v9.lo = FUN_000b43d0();
    if (pc6) pc6(v9.lo, v9.hi, u2);
    FUN_00359594();
    if (pc6) pc6();
    FUN_0035399c();
    FUN_003508a8();
    FUN_00351f4c();
    if (cb) cb();
    i1 = *(int *)(x26 + 0x30);
    pc7 = *(code *)(e16b + 0x20);
    v9.lo = FUN_00351354();
    if (pc7) pc7(v9.lo, v9.hi, u2);
    pc6 = *(code *)(e16b + 8);
    if (pc6) pc6(x27 + i1, u2);
    FUN_0035a190(*(word_t *)(e16 + 0x20));
    if (cb) cb();
    if (pc7) pc7(x24 + *(int *)(l3 + 0x24), x27 + *(int *)(x20 + 0x30), u2);
    FUN_003508f0();
    if (pc6) pc6();
    v9.lo = FUN_00350470();
    FUN_0028c7d8(v9.lo, v9.hi, l4);
    FUN_00353154();
    FUN_00351360();
    if (cb) cb();
    i1 = *(int *)(l4 + 0x28);
    FUN_00356810();
    FUN_00352ecc();
    u2 = FUN_0035949c();
    FUN_00351e3c(u2, v8.lo);
    if (cb) cb();
    FUN_00350df4();
    v8.lo = FUN_00348b94();
    FUN_00377824(v8.lo, v8.hi, u5);
    FUN_00349530();
    ((code)(*(word_t *)(e16c + 0x10)))(e8, (code)(long)i1 + x20);
    FUN_00351d00();
    ((code)(long)i1)();
    FUN_0008e500(x30);
}
