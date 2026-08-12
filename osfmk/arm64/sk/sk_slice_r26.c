/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice: 0x004661e4-0x0046a5c8 (SKR26) — the L4 syscall/error-code dispatch
 * layer. The dense low-address run is a table of small object/name helpers,
 * nop stubs and Unicode script-name getters (returning 8 ASCII bytes in a
 * 16-byte pair, decoded in per-function notes); the high-address functions are
 * large guarded syscall/error handlers (L4_ErrorCode* strings), the vspace
 * span-search walker and the IPC error-report machinery. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "sk_internal.h"

/* ------------------------------------------------------------------ *
 * Shared 16-byte word pair (aarch64e ABI). Many functions in this slice
 * return a 16-byte object in x0:x1. lo lands in x0, hi in x1. hi usually
 * carries an object-type tag in its top byte plus a value/pointer; lo is a
 * small constant or an 8-byte ASCII name.
 * ------------------------------------------------------------------ */
typedef struct {
    uint64_t lo;   /* x0 */
    uint64_t hi;   /* x1 */
} cl4_pair_t;

/* ------------------------------------------------------------------ *
 * Out-of-range cL4 helpers called from this slice (declared extern with a
 * one-line note; their bodies are reconstructed by the range workers that own
 * them). Ground truth FUN_ address in comment. Old-style () = unspecified
 * parameter list so calls of any arity compile; return type is set where the
 * helper's value is consumed.
 * ------------------------------------------------------------------ */

/* Syscall / error-dispatch infrastructure (0x0035xxxx-0x0037xxxx region). */
extern unsigned long FUN_00365b6c();                 /* loop compare/lookup */
extern unsigned long FUN_00377824();                 /* sk_demangle_witness_slot */
extern cl4_pair_t   FUN_00377bec();                  /* sk_cached_call_dispatch */
extern unsigned long FUN_00377dcc();                 /* cached call data */
extern unsigned long FUN_00350c98();                 /* sk_syscall_ret_zero */
extern void         FUN_003515fc();                  /* sk_syscall_args_2_3 */
extern unsigned long FUN_00310e08();                 /* swift_runtime_thunk */
extern unsigned long FUN_00310d68();                 /* swift_runtime_thunk */
extern unsigned long FUN_00319308();                 /* syscall arg build */
extern unsigned long FUN_00319628();                 /* syscall arg build */
extern void         FUN_0031d678();                  /* syscall post */
extern void         FUN_0031e0d4();                  /* syscall pre */
extern unsigned long FUN_00310924();                 /* fn-pointer carrier */
extern unsigned long FUN_00310954();                 /* fn-pointer carrier */
extern unsigned long FUN_0033e448();                 /* kind decode */

/* 0x0034xxxx thunk/support helpers. */
extern void         FUN_003493c4();
extern void         FUN_00349530();
extern void         FUN_00349fe0();
extern void         FUN_0034ab10();
extern void         FUN_0034ab20();
extern unsigned long FUN_0034b0b4();
extern unsigned long FUN_0034b0c4();
extern void         FUN_0034b0d4();
extern void         FUN_0034b318();
extern void         FUN_0034b4c0();
extern void         FUN_0034b540();
extern void         FUN_0034ba68();
extern unsigned long FUN_0034cff4();
extern void         FUN_0034d090();
extern void         FUN_0034dfa4();
extern void         FUN_0034e5bc();
extern long         FUN_003722e4();
extern void         FUN_0035a9b0();
extern void         FUN_0035a8d0();
extern void         FUN_0035a8d0();

/* 0x0035xxxx dispatch/error handlers. */
extern void         FUN_003503f8();
extern void         FUN_00350428();
extern void         FUN_00350464();
extern void         FUN_00350470();
extern void         FUN_00350494();
extern void         FUN_003504a0();
extern void         FUN_003504ac();
extern cl4_pair_t   FUN_003504e8();
extern cl4_pair_t   FUN_003504f4();
extern cl4_pair_t   FUN_00350500();
extern cl4_pair_t   FUN_0035050c();
extern cl4_pair_t   FUN_00350524();
extern cl4_pair_t   FUN_0035056c();
extern void         FUN_00350518();
extern void         FUN_00350530();
extern void         FUN_0035053c();
extern void         FUN_00350548();
extern void         FUN_00350560();
extern void         FUN_003505c4();
extern void         FUN_003505e8();
extern void         FUN_00350600();
extern cl4_pair_t   FUN_0035060c();
extern void         FUN_00350618();
extern void         FUN_00350624();
extern void         FUN_0035063c();
extern cl4_pair_t   FUN_00350738();
extern void         FUN_00350774();
extern void         FUN_00350798();
extern void         FUN_0035084c();
extern void         FUN_00350878();
extern int          FUN_00350884();
extern void         FUN_003508cc();
extern cl4_pair_t   FUN_003508e4();
extern cl4_pair_t   FUN_003508fc();
extern void         FUN_003509a4();
extern cl4_pair_t   FUN_003509b0();
extern void         FUN_003509bc();
extern void         FUN_003509c8();
extern void         FUN_003509ec();
extern cl4_pair_t   FUN_00350a04();
extern void         FUN_00350a70();
extern void         FUN_00350ab8();
extern cl4_pair_t   FUN_00350af4();
extern void         FUN_00350b48();
extern void         FUN_00350b84();
extern void         FUN_00350b9c();
extern void         FUN_00350bc0();
extern void         FUN_00350c08();
extern void         FUN_00350c20();
extern void         FUN_003510ac();
extern void         FUN_003510dc();
extern void         FUN_00351118();
extern void         FUN_00351130();
extern void         FUN_00351178();
extern void         FUN_003511d8();
extern void         FUN_003511f0();
extern void         FUN_00351214();
extern void         FUN_00351274();
extern cl4_pair_t   FUN_003512c0();
extern cl4_pair_t   FUN_00351324();
extern void         FUN_0035136c();
extern int          FUN_00351390();
extern void         FUN_0035139c();
extern void         FUN_003513a8();
extern cl4_pair_t   FUN_00351450();
extern void         FUN_003514e8();
extern void         FUN_0035156c();
extern void         FUN_00351584();
extern void         FUN_003515d8();
extern void         FUN_0035166c();
extern void         FUN_00351750();
extern void         FUN_00351790();
extern cl4_pair_t   FUN_003517c0();
extern void         FUN_0035199c();
extern void         FUN_00351a50();
extern void         FUN_00351b78();
extern void         FUN_00351bd4();
extern void         FUN_00351c7c();
extern cl4_pair_t   FUN_00351cd0();
extern void         FUN_00351d30();
extern unsigned long FUN_00351db4();
extern void         FUN_00351de4();
extern void         FUN_00351dfc();
extern cl4_pair_t   FUN_00351e20();
extern void         FUN_00351e3c();
extern void         FUN_00351f1c();
extern void         FUN_00351f4c();
extern void         FUN_00352290();
extern void         FUN_003522c8();
extern void         FUN_0035256c();
extern void         FUN_00352800();
extern void         FUN_00352ae4();
extern void         FUN_00352ea8();
extern void         FUN_00352efc();
extern void         FUN_00353208();
extern void         FUN_003535a8();
extern void         FUN_003542b8();
extern void         FUN_00356bb0();
extern void         FUN_003580e4();
extern void         FUN_00359018();

/* Allocator / object helpers. */
extern long FUN_0036a940();                         /* zone/obj alloc (size,count,tag) */
extern void *FUN_0036b270();                         /* sk_alloc / refcount acquire */
extern void  FUN_0036b118();                         /* sk_free / refcount release */
extern void  FUN_0036b340();                         /* refcount link */
extern void  FUN_0036b588();                         /* sk_alloc_link */
extern void  FUN_003a25d4();                         /* object release (tightbeam) */
extern void  FUN_003a261c();                         /* object release 2 (tightbeam) */
extern cl4_pair_t FUN_0001d4f4();                         /* error-frame build */
extern unsigned long FUN_0001dd14();                 /* grow/ensure-capacity */
extern unsigned long FUN_0019dfc4();                         /* cap/name lookup */
extern unsigned long FUN_0019e578();                 /* sk_swift_helper */
extern void  FUN_001b58b0();
extern void  FUN_001b9084();
extern void  FUN_001d88fc();
extern void  FUN_001d9890();
extern unsigned long FUN_001a3e10();                 /* container head */

/* Kernel / arch primitives. */
extern unsigned long FUN_00002534();                 /* diag/boot name ref */
extern void  FUN_00117cc4();                         /* sk_memcpy */
extern cl4_pair_t   FUN_00100c38();
extern void  FUN_00100efc();
extern void  FUN_0011aa70();
extern unsigned long FUN_0014ae44();
extern unsigned long FUN_00206770();
extern void  FUN_00270c08();                         /* sk_string_insert_check */
extern void  FUN_0029fa0c();                         /* obj_slice_02 page-walk step */
extern unsigned long FUN_002a0cf8();                 /* obj_slice_02 compare */
extern void  FUN_002a4ab4();                         /* obj_slice_03 */
extern void  FUN_002a55a4();
extern void  FUN_002a74f8();
extern unsigned long FUN_002b3b50();                 /* obj_slice_04 span step */
extern cl4_pair_t FUN_002b439c();                    /* obj_slice_05 span build */
extern void  thunk_FUN_002298d4();
extern void  thunk_FUN_0024d9ac();
extern void  thunk_FUN_002acbb8();                   /* obj_slice_11 report emit */
extern cl4_pair_t thunk_FUN_002b74c0();
extern void  thunk_FUN_0036b270();                   /* refcount acquire */

/* Supervisor-call / guarded exception-return thunk. The decompiler renders the
 * cL4 exception-return / guarded-level entry as an indirect call through the
 * constant address SUB_54ffff60f100041f. Rendered here as an extern thunk. */
extern void sk_svc_call();

/* 0x004axxxx-0x004bxxxx same-binary helpers. */
extern unsigned long FUN_004a2fd8();
extern unsigned long FUN_004a3008();
extern unsigned long FUN_004a3038();
extern void         FUN_004a3050();
extern void         FUN_004a34f0();
extern void         FUN_004a4ab4();
extern void         FUN_004a4ac4();
extern cl4_pair_t   FUN_004a4b14();
extern unsigned long FUN_004aa4fc();
extern cl4_pair_t   FUN_004aa5dc();
extern unsigned long FUN_004aa67c();
extern unsigned long FUN_004aa770();
extern void         FUN_004aa938();
extern void         FUN_004aa95c();
extern void         FUN_004aa970();
extern void         FUN_004aabe4();
extern unsigned long FUN_004aac04();
extern unsigned long FUN_004aac68();
extern unsigned long FUN_004aac78();
extern unsigned long FUN_004aad84();
extern void         FUN_004aae44();
extern void         FUN_004aaf38();
extern void         FUN_004aaf6c();
extern void         FUN_004ab1c8();
extern void         FUN_004ab1dc();
extern void         FUN_004ab310();
extern void         FUN_004ab5d4();
extern void         FUN_004ab618();
extern void         FUN_004ab624();
extern void         FUN_004ab644();
extern void         FUN_004ab784();
extern void         FUN_004ab7cc();
extern void         FUN_004ab920();
extern void         FUN_004ab9b0();
extern void         FUN_004ab9e0();
extern void         FUN_004ab9ec();
extern void         FUN_004aba28();
extern void         FUN_004aba34();
extern void         FUN_004abd04();
extern void         FUN_004abd44();
extern void         FUN_004abd64();
extern void         FUN_004abd9c();
extern cl4_pair_t   FUN_004abfb8();
extern cl4_pair_t   FUN_004ac1bc();
extern void         FUN_004ac2ac();
extern void         FUN_004ac2b8();
extern void         FUN_004ac33c();
extern void         FUN_004ac36c();
extern void         FUN_004ac5c4();
extern unsigned long FUN_004ac628();
extern void         FUN_004ac7b0();
extern void         FUN_004ac85c();
extern void         FUN_004ac888();
extern void         FUN_004ac8b4();
extern void         FUN_004ac8c0();
extern void         FUN_004ac980();
extern void         FUN_004ac9c0();
extern cl4_pair_t   FUN_004ac9d8();
extern void         FUN_004aca04();
extern void         FUN_004acacc();
extern void         FUN_004acae8();
extern void         FUN_004acb04();
extern void         FUN_004acc20();
extern void         FUN_004acc48();
extern void         FUN_004b5a74();

/* 0x0041-0x0046 earlier-slice helpers. */
extern unsigned long FUN_00407ed0();
extern void FUN_00407ab8();
extern void FUN_0041d180();
extern void FUN_0042ec68();
extern void FUN_00437eec();                          /* sk_re_parse_done */
extern void FUN_004564e4();
extern void FUN_0045659c();
extern void FUN_004589e8();
extern void FUN_00458b14();
extern void FUN_004590e0();
extern void FUN_00462e9c();
extern void FUN_004633e0();
extern void FUN_0046490c();
extern unsigned long FUN_00464a44();
extern void FUN_00464f4c();
extern void FUN_00465db0();
extern cl4_pair_t FUN_0046ea44();
extern void FUN_0046ef90();
extern void FUN_0047277c();
extern void FUN_0047d358();
extern void FUN_00484910();
extern void FUN_0048736c();
extern void FUN_004877a0();
extern unsigned long FUN_004918ac();
extern void FUN_00491914();
extern void FUN_0049490c();
extern void FUN_004974ac();
extern void FUN_004974c4();
extern unsigned long FUN_004974ec();
extern unsigned long FUN_00497504();
extern unsigned long FUN_0049751c();
extern void FUN_00497994();
extern cl4_pair_t FUN_004979bc();
extern void FUN_00498c6c();
extern void FUN_0049d248();

/* Supervisor-call / GENTER-like entry opcodes. */
#define SK_SVC_CALL()   sk_svc_call()
#define SK_PANIC(msg)   __asm__ volatile("brk #1" ::: "memory")

/* Function-pointer type for Ghidra `code *` register artifacts and vtable
 * method dispatch. Old-style () so any argument list type-checks. */
typedef uint64_t (*code_fn)();
#define SK_VMETHOD(obj, off, ...) \
    (((code_fn)(*(void **)((char *)(obj) + (off))))(__VA_ARGS__))

/* ================================================================== *
 * SKR26 function bodies (address order)
 * ================================================================== */

/* Forward declarations (old-style) for the in-range functions so they can be
 * called before their definitions (mutual call graph in this slice). */
extern cl4_pair_t   FUN_004661e4();
extern uint64_t     FUN_004661f0();
extern void         FUN_004661fc();
extern void         FUN_00466208();
extern void         FUN_00466214();
extern void         FUN_00466220();
extern void         FUN_0046622c();
extern uint64_t     FUN_00466238();
extern void         FUN_00466244();
extern uint64_t     FUN_00466250();
extern cl4_pair_t   FUN_00466264();
extern void         FUN_00466270();
extern uint64_t     FUN_0046627c();
extern void         FUN_00466290();
extern cl4_pair_t   FUN_004662a4();
extern cl4_pair_t   FUN_004662b8();
extern uint64_t     FUN_004662cc();
extern void         FUN_004662e0();
extern void         FUN_004662f4();
extern void         FUN_00466300();
extern void         FUN_00466314();
extern uint64_t     FUN_00466328();
extern uint8_t     *FUN_0046633c();
extern void         FUN_00466348();
extern void         FUN_0046635c();
extern uint64_t     FUN_00466368();
extern void         FUN_00466374();
extern void         FUN_00466388();
extern cl4_pair_t   FUN_00466394();
extern void         FUN_004663a0();
extern uint64_t     FUN_004663ac();
extern void         FUN_004663c0();
extern void         FUN_004663d4();
extern void         FUN_004663e0();
extern void         FUN_004663ec();
extern void         FUN_00466408();
extern void         FUN_00466440();
extern void         FUN_00466454();
extern void         FUN_00466468();
extern void         FUN_0046647c();
extern void         FUN_00466490();
extern void         FUN_004664a4();
extern void         FUN_004664b8();
extern void         FUN_004664d0();
extern void         FUN_004664e4();
extern void         FUN_004664f8();
extern void         FUN_00466510();
extern void         FUN_00466528();
extern void         FUN_00466540();
extern void         FUN_00466554();
extern void         FUN_00466568();
extern void         FUN_00466580();
extern void         FUN_00466594();
extern void         FUN_004665a8();
extern void         FUN_004665bc();
extern void         FUN_004665d0();
extern void         FUN_004665dc();
extern void         FUN_004665e8();
extern void         FUN_004665f4();
extern void         FUN_00466600();
extern void         FUN_0046660c();
extern void         FUN_00466618();
extern void         FUN_00466624();
extern void         FUN_00466630();
extern void         FUN_0046663c();
extern void         FUN_00466648();
extern void         FUN_00466654();
extern void         FUN_00466660();
extern void         FUN_0046666c();
extern void         FUN_00466678();
extern void         FUN_00466684();
extern void         FUN_00466690();
extern void         FUN_0046669c();
extern void         FUN_004666a8();
extern void         FUN_004666b4();
extern void         FUN_004666c0();
extern void         FUN_004666cc();
extern void         FUN_004666e4();
extern void         FUN_004666f8();
extern void         FUN_00466730();
extern void         FUN_00466744();
extern void         FUN_00466a68();
extern void         FUN_00466f18();
extern bool         FUN_00467468();
extern bool         FUN_004674e4();
extern void         FUN_00467564();
extern void         FUN_00467678();
extern void         FUN_004676a4();
extern void         FUN_0046777c();
extern void         FUN_00467848();
extern void         FUN_004678c8();
extern cl4_pair_t   FUN_00467de4();
extern cl4_pair_t   FUN_00467e44();
extern void         FUN_00468144();
extern void         FUN_004686e8();
extern void         FUN_004687e8();
extern void         FUN_00468888();
extern void         FUN_00468c6c();
extern void         FUN_00468ce4();
extern uint64_t     FUN_00468d98();
extern void         FUN_00468dd4();
extern void         FUN_00468ee4();
extern void         FUN_00469250();
extern uint64_t     FUN_004693d0();
extern void         FUN_004693ec();
extern void         FUN_0046989c();
extern void         FUN_00469918();
extern cl4_pair_t   FUN_00469b50();
extern void         FUN_00469c50();
extern void         FUN_00469d58();
extern void         FUN_00469d84();
extern void         FUN_00469dc4();
extern void         FUN_00469ee8();
extern void         FUN_00469f58();
extern void         FUN_00469f74();
extern void         FUN_0046a01c();
extern void         FUN_0046a118();
extern cl4_pair_t   FUN_0046a1b0();
extern cl4_pair_t   FUN_0046a368();
extern void         FUN_0046a5c8();

/* Additional kernel / object helpers used by the dispatchers (0x0000-0x0020
 * region). Old-style () = unspecified params; return type set where consumed. */
extern void         FUN_00019858();
extern cl4_pair_t   FUN_0001d4f4();                 /* error-frame build */
extern unsigned long FUN_0001dd14();                 /* grow/ensure-capacity */
extern unsigned long FUN_00027754();                 /* object release */
extern unsigned long FUN_000277b8();                 /* fn-pointer carrier */
extern unsigned long FUN_00027818();                 /* object release 2 */
extern cl4_pair_t   FUN_00077888();
extern void         FUN_00077894();
extern void         FUN_0007c028();
extern void         FUN_0007c1a4();
extern void         FUN_0007c1c4();
extern unsigned long FUN_000839d8();
extern long         FUN_000839f8();
extern void         FUN_00084174();
extern void         FUN_00084180();
extern void         FUN_00084220();
extern void         FUN_00084234();
extern void         FUN_0008e388();
extern void         FUN_0008e500();
extern cl4_pair_t   FUN_0008e518();                  /* launch image pair */
extern cl4_pair_t   FUN_0009461c();
extern void         FUN_0009e234();
extern void         FUN_000a68c4();
extern unsigned long FUN_000a68f4();                 /* fn-pointer carrier */
extern cl4_pair_t   FUN_000a6e14();
extern void         FUN_000a6f68();
extern unsigned long FUN_000a6f88();
extern void         FUN_000aa4ec();
extern cl4_pair_t   FUN_000b4390();
extern cl4_pair_t   FUN_000b43d0();
extern void         FUN_000bd3a4();
extern cl4_pair_t   FUN_000e15d8();
extern void         FUN_000f5d84();
extern cl4_pair_t   FUN_00100c38();
extern void         FUN_00100efc();
extern void         FUN_0011aa70();
extern unsigned long FUN_0014ae44();
extern unsigned long FUN_0019dfc4();
extern unsigned long FUN_001a3e10();                 /* container head */
extern void         FUN_001b58b0();
extern void         FUN_001b9084();
extern void         FUN_001d88fc();
extern void         FUN_001d9890();
extern unsigned long FUN_00206770();
extern void         FUN_002a55a4();
extern void         FUN_002a74f8();

/* FUN_004661e4 @ 0x004661e4   (est. sk_pair_661e4)
 * Ghidra: undefined1 [16] FUN_004661e4(void)
 * Returns a 16-byte pair of stack-frame addresses (register fragment — the
 * decompiler captured two pointers into the caller's frame, offsets 0xd0/0x8).
 * The pair is used as a name/descriptor reference handed to the caller.
 * Confidence: low
 * Notes: returns &stack0x000000d0 / &stack0x00000008 (dead stack refs). */
cl4_pair_t FUN_004661e4(void)
{
    uint8_t a[0xd0], b[8];
    return (cl4_pair_t){ .lo = (uint64_t)a, .hi = (uint64_t)b };
}

/* FUN_004661f0 @ 0x004661f0   (est. sk_tag_encode_661f0)
 * Ghidra: ulong FUN_004661f0(ulong param_1)
 * Clears the 32-bit field at bits 32..47 of the word, keeping the low 32 bits
 * and the top 16 bits, and ORs in the constant 0x6500_0000_00. A pointer/tag
 * encode helper.
 * Confidence: medium
 * Notes: pure bitfield rewrite. */
uint64_t FUN_004661f0(uint64_t v)
{
    return (v & 0xffff0000ffffffffULL) | 0x6500000000ULL;
}

/* FUN_004661fc @ 0x004661fc   (est. sk_nop_661fc)
 * Ghidra: void FUN_004661fc(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004661fc(void)
{
    return;
}

/* FUN_00466208 @ 0x00466208   (est. sk_nop_66208)
 * Ghidra: void FUN_00466208(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466208(void)
{
    return;
}

/* FUN_00466214 @ 0x00466214   (est. sk_nop_66214)
 * Ghidra: void FUN_00466214(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466214(void)
{
    return;
}

/* FUN_00466220 @ 0x00466220   (est. sk_copy_word_66220)
 * Ghidra: void FUN_00466220(void)
 * Register fragment: copies the 8-byte word at +0x38 of the source object
 * (callee-saved x19) to +0x38 of the destination object (callee-saved x20).
 * Confidence: low
 * Notes: unaff x19/x20 register fragment. */
void FUN_00466220(word_t dst, word_t src)
{
    *(word_t *)(dst + 0x38) = *(word_t *)(src + 0x38);
}

/* FUN_0046622c @ 0x0046622c   (est. sk_nop_6622c)
 * Ghidra: void FUN_0046622c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046622c(void)
{
    return;
}

/* FUN_00466238 @ 0x00466238   (est. sk_script_name_66238)
 * Ghidra: undefined8 FUN_00466238(void)
 * Returns the 8-byte ASCII name tag 0x69646962 == "bidi" (Unicode bidi script
 * tag). One of the script-name getters in this table.
 * Confidence: high
 * Notes: lo decoded "bidi". */
uint64_t FUN_00466238(void)
{
    return 0x69646962ULL;   /* "bidi" */
}

/* FUN_00466244 @ 0x00466244   (est. sk_nop_66244)
 * Ghidra: void FUN_00466244(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466244(void)
{
    return;
}

/* FUN_00466250 @ 0x00466250   (est. sk_script_name_66250)
 * Ghidra: undefined8 FUN_00466250(void)
 * Returns the 8-byte ASCII name tag 0x7465626168706c61 == "alphabets".
 * Confidence: high
 * Notes: lo decoded "alphabets". */
uint64_t FUN_00466250(void)
{
    return 0x7465626168706c61ULL;   /* "alphabets" */
}

/* FUN_00466264 @ 0x00466264   (est. sk_pair_66264)
 * Ghidra: undefined1 [16] FUN_00466264(void)
 * Returns a 16-byte pair of stack-frame addresses (offsets 0x1b0 / 0x18).
 * Register fragment; descriptor reference for the caller.
 * Confidence: low
 * Notes: returns &stack0x000001b0 / &stack0x00000018. */
cl4_pair_t FUN_00466264(void)
{
    uint8_t a[0x1b0], b[0x18];
    return (cl4_pair_t){ .lo = (uint64_t)a, .hi = (uint64_t)b };
}

/* FUN_00466270 @ 0x00466270   (est. sk_nop_66270)
 * Ghidra: void FUN_00466270(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466270(void)
{
    return;
}

/* FUN_0046627c @ 0x0046627c   (est. sk_script_name_6627c)
 * Ghidra: undefined8 FUN_0046627c(void)
 * Returns the 8-byte ASCII name tag 0x756b617365766964. Decoded little-endian
 * it reads "divesaku"; not a standard script name — treated as an opaque tag.
 * Confidence: low
 * Notes: constant 0x756b617365766964. */
uint64_t FUN_0046627c(void)
{
    return 0x756b617365766964ULL;
}

/* FUN_00466290 @ 0x00466290   (est. sk_nop_66290)
 * Ghidra: void FUN_00466290(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466290(void)
{
    return;
}

/* FUN_004662a4 @ 0x004662a4   (est. sk_pair_662a4)
 * Ghidra: undefined1 [16] FUN_004662a4(void)
 * Returns the 16-byte pair { lo = 0xd000000000000014, hi = x28 | 0x8000... }.
 * The hi word combines a callee-saved value (x28) with the top tag bit; lo is
 * a tagged type/state constant (0xd000...014).
 * Confidence: low
 * Notes: unaff_x28 register fragment. */
cl4_pair_t FUN_004662a4(word_t x28)
{
    return (cl4_pair_t){ .lo = 0xd000000000000014ULL,
                         .hi = x28 | 0x8000000000000000ULL };
}

/* FUN_004662b8 @ 0x004662b8   (est. sk_pair_662b8)
 * Ghidra: undefined1 [16] FUN_004662b8(void)
 * Returns the constant 16-byte pair { lo = 0x657a38, hi = 0x5a1a50 } — two
 * data addresses (string/table references).
 * Confidence: low
 * Notes: lo/hi are data addresses DAT_00657a38-ish / 0x5a1a50. */
cl4_pair_t FUN_004662b8(void)
{
    return (cl4_pair_t){ .lo = 0x657a38, .hi = 0x5a1a50 };
}

/* FUN_004662cc @ 0x004662cc   (est. sk_script_name_662cc)
 * Ghidra: undefined8 FUN_004662cc(void)
 * Returns the 8-byte ASCII name tag 0x616c6179616c616d == "malayalam".
 * Confidence: high
 * Notes: lo decoded "malayalam". */
uint64_t FUN_004662cc(void)
{
    return 0x616c6179616c616dULL;   /* "malayalam" */
}

/* FUN_004662e0 @ 0x004662e0   (est. sk_copy_fields_662e0)
 * Ghidra: void FUN_004662e0(undefined8 param_1, long param_2)
 * Copies four 8-byte words (+8,+0x10,+0x18,+0x20) from the source struct
 * param_2 to the destination object held in callee-saved x19.
 * Confidence: low
 * Notes: unaff_x19 register fragment. */
void FUN_004662e0(word_t dst, const word_t *src)
{
    *(word_t *)(dst + 8)  = src[1];
    *(word_t *)(dst + 0x10) = src[2];
    *(word_t *)(dst + 0x18) = src[3];
    *(word_t *)(dst + 0x20) = src[4];
}

/* FUN_004662f4 @ 0x004662f4   (est. sk_nop_662f4)
 * Ghidra: void FUN_004662f4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004662f4(void)
{
    return;
}

/* FUN_00466300 @ 0x00466300   (est. sk_nop_66300)
 * Ghidra: void FUN_00466300(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466300(void)
{
    return;
}

/* FUN_00466314 @ 0x00466314   (est. sk_nop_66314)
 * Ghidra: void FUN_00466314(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466314(void)
{
    return;
}

/* FUN_00466328 @ 0x00466328   (est. sk_script_name_66328)
 * Ghidra: undefined8 FUN_00466328(void)
 * Returns the 8-byte ASCII name tag 0x74617574636e7570 == "punctuat"
 * (punctuation script tag, 8 chars truncated).
 * Confidence: high
 * Notes: lo decoded "punctuat". */
uint64_t FUN_00466328(void)
{
    return 0x74617574636e7570ULL;   /* "punctuat" */
}

/* FUN_0046633c @ 0x0046633c   (est. sk_stack_ptr_6633c)
 * Ghidra: undefined1 * FUN_0046633c(void)
 * Returns a pointer into the caller's stack frame (address of a local slot).
 * Register fragment: returned pointer is the address of a stack local.
 * Confidence: low
 * Notes: returns &stack0x00000058. */
uint8_t *FUN_0046633c(void)
{
    uint8_t local[0x58];
    return local;
}

/* FUN_00466348 @ 0x00466348   (est. sk_store_pair_66348)
 * Ghidra: void FUN_00466348(long param_1)
 * Stores two stack-passed words into the object at +0x10 and +0x18.
 * Confidence: low
 * Notes: two stack args folded into a local buffer. */
void FUN_00466348(word_t obj, uint64_t a, uint64_t b)
{
    *(uint64_t *)(obj + 0x10) = a;
    *(uint64_t *)(obj + 0x18) = b;
}

/* FUN_0046635c @ 0x0046635c   (est. sk_nop_6635c)
 * Ghidra: void FUN_0046635c(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_0046635c(void)
{
    return;
}

/* FUN_00466368 @ 0x00466368   (est. sk_tag_encode_66368)
 * Ghidra: ulong FUN_00466368(ulong param_1)
 * Keeps the low 48 bits of the word and ORs in 0x6900_0000_0000_00. Tag/pop
 * encode helper (opposite mask family to 004661f0).
 * Confidence: medium
 * Notes: pure bitfield rewrite. */
uint64_t FUN_00466368(uint64_t v)
{
    return (v & 0xffffffffffffULL) | 0x69000000000000ULL;
}

/* FUN_00466374 @ 0x00466374   (est. sk_copy_fields_66374)
 * Ghidra: void FUN_00466374(void)
 * Register fragment: copies six 8-byte words (+0x20..+0x48) from the source
 * object (x19) to the destination object (x20).
 * Confidence: low
 * Notes: unaff x19/x20 register fragment. */
void FUN_00466374(word_t dst, word_t src)
{
    uint64_t v20 = *(uint64_t *)(src + 0x20);
    uint64_t v38 = *(uint64_t *)(src + 0x38);
    uint64_t v30 = *(uint64_t *)(src + 0x30);
    *(uint64_t *)(dst + 0x28) = *(uint64_t *)(src + 0x28);
    *(uint64_t *)(dst + 0x20) = v20;
    *(uint64_t *)(dst + 0x38) = v38;
    *(uint64_t *)(dst + 0x30) = v30;
    uint64_t v40 = *(uint64_t *)(src + 0x40);
    *(uint64_t *)(dst + 0x48) = *(uint64_t *)(src + 0x48);
    *(uint64_t *)(dst + 0x40) = v40;
}

/* FUN_00466388 @ 0x00466388   (est. sk_nop_66388)
 * Ghidra: void FUN_00466388(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466388(void)
{
    return;
}

/* FUN_00466394 @ 0x00466394   (est. sk_pair_66394)
 * Ghidra: undefined1 [16] FUN_00466394(void)
 * Returns the constant 16-byte pair { lo = 0x3f28, hi = 0xe400000000000000 }.
 * hi carries the type tag 0xe4 with zero payload; lo is a small constant.
 * Confidence: medium
 * Notes: hi tag 0xe4. */
cl4_pair_t FUN_00466394(void)
{
    return (cl4_pair_t){ .lo = 0x3f28, .hi = 0xe400000000000000ULL };
}

/* FUN_004663a0 @ 0x004663a0   (est. sk_nop_663a0)
 * Ghidra: void FUN_004663a0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004663a0(void)
{
    return;
}

/* FUN_004663ac @ 0x004663ac   (est. sk_zero_663ac)
 * Ghidra: undefined8 FUN_004663ac(void)
 * Returns 0.
 * Confidence: high
 * Notes: constant zero. */
uint64_t FUN_004663ac(void)
{
    return 0;
}

/* FUN_004663c0 @ 0x004663c0   (est. sk_nop_663c0)
 * Ghidra: void FUN_004663c0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004663c0(void)
{
    return;
}

/* FUN_004663d4 @ 0x004663d4   (est. sk_nop_663d4)
 * Ghidra: void FUN_004663d4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004663d4(void)
{
    return;
}

/* FUN_004663e0 @ 0x004663e0   (est. sk_nop_663e0)
 * Ghidra: void FUN_004663e0(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004663e0(void)
{
    return;
}

/* FUN_004663ec @ 0x004663ec   (est. sk_nop_663ec)
 * Ghidra: void FUN_004663ec(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004663ec(void)
{
    return;
}

/* FUN_00466408 @ 0x00466408   (est. sk_nop_66408)
 * Ghidra: void FUN_00466408(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466408(void)
{
    return;
}

/* FUN_00466440 @ 0x00466440   (est. sk_alloc_small_66440)
 * Ghidra: void FUN_00466440(void)
 * Allocates a small object: FUN_0036a940(0x685d80, 0x18, 7) — size class 0x18,
 * tag 7, from the descriptor at 0x685d80. Result discarded.
 * Confidence: low
 * Notes: single alloc call; string desc DAT 0x685d80. */
void FUN_00466440(void)
{
    FUN_0036a940(0x685d80, 0x18, 7);
}

/* FUN_00466454 @ 0x00466454   (est. sk_frame_call_66454)
 * Ghidra: void FUN_00466454(void)
 * Builds a 16-byte local frame { lo=0, hi=0xe000000000000000 } and passes its
 * address to FUN_004590e0.
 * Confidence: low
 * Notes: local pair {0, tag 0xe0}; stack arg. */
void FUN_00466454(void)
{
    uint8_t frame[0x40];
    *(uint64_t *)(frame + 0x30) = 0;
    *(uint64_t *)(frame + 0x38) = 0xe000000000000000ULL;
    FUN_004590e0(frame + 8);
}

/* FUN_00466468 @ 0x00466468   (est. sk_call_66468)
 * Ghidra: void FUN_00466468(void)
 * Tail-calls the helper FUN_004564e4 and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00466468(void)
{
    FUN_004564e4();
}

/* FUN_0046647c @ 0x0046647c   (est. sk_name_ref_6647c)
 * Ghidra: void FUN_0046647c(void)
 * References a name/symbol: FUN_00002534(0x656248, &DAT_004e80a0) — string
 * descriptor and data address.
 * Confidence: low
 * Notes: diag/boot name ref to DAT_004e80a0. */
void FUN_0046647c(void)
{
    FUN_00002534(0x656248, (const void *)0x004e80a0);
}

/* FUN_00466490 @ 0x00466490   (est. sk_call_66490)
 * Ghidra: void FUN_00466490(void)
 * Tail-calls the page-walk helper FUN_0029fa0c and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00466490(void)
{
    FUN_0029fa0c();
}

/* FUN_004664a4 @ 0x004664a4   (est. sk_call_664a4)
 * Ghidra: void FUN_004664a4(void)
 * Tail-calls the page-walk helper FUN_0029fa0c and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_004664a4(void)
{
    FUN_0029fa0c();
}

/* FUN_004664b8 @ 0x004664b8   (est. sk_nop_664b8)
 * Ghidra: void FUN_004664b8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004664b8(void)
{
    return;
}

/* FUN_004664d0 @ 0x004664d0   (est. sk_frame_call_664d0)
 * Ghidra: void FUN_004664d0(void)
 * Calls FUN_00437eec with a stack-frame address and two zero args.
 * Confidence: low
 * Notes: stack arg &stack0x70; (0,0). */
void FUN_004664d0(void)
{
    uint8_t frame[0x70];
    FUN_00437eec(frame, 0, 0);
}

/* FUN_004664e4 @ 0x004664e4   (est. sk_frame_call_664e4)
 * Ghidra: void FUN_004664e4(void)
 * Builds a 16-byte local { lo=0, hi=0xe000000000000000 } then calls
 * FUN_002a4ab4(0x13).
 * Confidence: low
 * Notes: local pair {0, tag 0xe0}; FUN_002a4ab4(0x13). */
void FUN_004664e4(void)
{
    uint8_t frame[0x30];
    *(uint64_t *)(frame + 0x20) = 0;
    *(uint64_t *)(frame + 0x28) = 0xe000000000000000ULL;
    FUN_002a4ab4(0x13);
}

/* FUN_004664f8 @ 0x004664f8   (est. sk_nop_664f8)
 * Ghidra: void FUN_004664f8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004664f8(void)
{
    return;
}

/* FUN_00466510 @ 0x00466510   (est. sk_nop_66510)
 * Ghidra: void FUN_00466510(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466510(void)
{
    return;
}

/* FUN_00466528 @ 0x00466528   (est. sk_nop_66528)
 * Ghidra: void FUN_00466528(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466528(void)
{
    return;
}

/* FUN_00466540 @ 0x00466540   (est. sk_name_ref_66540)
 * Ghidra: void FUN_00466540(void)
 * References a name/symbol: FUN_00002534(0x6579b8, &DAT_005a1990).
 * Confidence: low
 * Notes: diag/boot name ref to DAT_005a1990. */
void FUN_00466540(void)
{
    FUN_00002534(0x6579b8, (const void *)0x005a1990);
}

/* FUN_00466554 @ 0x00466554   (est. sk_name_ref_66554)
 * Ghidra: void FUN_00466554(void)
 * References a name/symbol: FUN_00002534(0x6579b0, &DAT_005a1988).
 * Confidence: low
 * Notes: diag/boot name ref to DAT_005a1988. */
void FUN_00466554(void)
{
    FUN_00002534(0x6579b0, (const void *)0x005a1988);
}

/* FUN_00466568 @ 0x00466568   (est. sk_nop_66568)
 * Ghidra: void FUN_00466568(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466568(void)
{
    return;
}

/* FUN_00466580 @ 0x00466580   (est. sk_call_66580)
 * Ghidra: void FUN_00466580(void)
 * Tail-calls the helper FUN_0041d180 and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00466580(void)
{
    FUN_0041d180();
}

/* FUN_00466594 @ 0x00466594   (est. sk_call_66594)
 * Ghidra: void FUN_00466594(void)
 * Tail-calls the helper FUN_0045659c and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00466594(void)
{
    FUN_0045659c();
}

/* FUN_004665a8 @ 0x004665a8   (est. sk_release_slot_665a8)
 * Ghidra: void FUN_004665a8(long param_1)
 * Register fragment: reads the object slot at (x21 + param_1*8 + 0x20), masks
 * off the top tag bits (& 0xfffffffffffffff) and releases it via
 * FUN_0036b270 (refcount acquire/release).
 * Confidence: low
 * Notes: unaff_x21 register fragment; slot mask 0xfffffffffffffff. */
void FUN_004665a8(word_t x21, long idx)
{
    FUN_0036b270(*(word_t *)(x21 + idx * 8 + 0x20) & 0xfffffffffffffffULL);
}

/* FUN_004665bc @ 0x004665bc   (est. sk_call_665bc)
 * Ghidra: void FUN_004665bc(undefined8 param_1, long param_2)
 * Forwards the word at +0x10 of param_2 to thunk_FUN_002298d4.
 * Confidence: low
 * Notes: single deref + forward. */
void FUN_004665bc(word_t param_1, word_t param_2)
{
    thunk_FUN_002298d4(*(word_t *)(param_2 + 0x10));
}

/* FUN_004665d0 @ 0x004665d0   (est. sk_release_665d0)
 * Ghidra: void FUN_004665d0(void)
 * Register fragment: releases the object word at (x19 + 0x50) via FUN_003a261c.
 * Confidence: low
 * Notes: unaff_x19. */
void FUN_004665d0(word_t x19)
{
    FUN_003a261c(*(word_t *)(x19 + 0x50));
}

/* FUN_004665dc @ 0x004665dc   (est. sk_call3_665dc)
 * Ghidra: void FUN_004665dc(undefined8 param_1, undefined8 param_2)
 * Forwards three arguments (two explicit plus one stack value) to FUN_0029fa0c.
 * Confidence: low
 * Notes: one stack arg folded in. */
void FUN_004665dc(word_t a, word_t b, word_t c)
{
    FUN_0029fa0c(a, b, c);
}

/* FUN_004665e8 @ 0x004665e8   (est. sk_call_665e8)
 * Ghidra: void FUN_004665e8(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Calls FUN_00310d68(0xff, param_3) and returns.
 * Confidence: low
 * Notes: swift-runtime thunk with 0xff sentinel. */
void FUN_004665e8(word_t a, word_t b, word_t c)
{
    FUN_00310d68(0xff, c);
}

/* FUN_004665f4 @ 0x004665f4   (est. sk_release_665f4)
 * Ghidra: void FUN_004665f4(void)
 * Tail-calls the object-release helper FUN_003a25d4 and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_004665f4(void)
{
    FUN_003a25d4();
}

/* FUN_00466600 @ 0x00466600   (est. sk_report_66600)
 * Ghidra: void FUN_00466600(void)
 * Tail-calls thunk_FUN_0024d9ac with the data descriptor &DAT_005a3590.
 * Confidence: low
 * Notes: report emit to DAT_005a3590. */
void FUN_00466600(void)
{
    thunk_FUN_0024d9ac((const void *)0x005a3590);
}

/* FUN_0046660c @ 0x0046660c   (est. sk_shift_call_6660c)
 * Ghidra: void FUN_0046660c(void)
 * Register fragment: forwards (x20 >> 0xe) to thunk_FUN_002298d4 (page number
 * of the value in callee-saved x20).
 * Confidence: low
 * Notes: unaff_x20; shift 0xe = page index. */
void FUN_0046660c(word_t x20)
{
    thunk_FUN_002298d4(x20 >> 0xe);
}

/* FUN_00466618 @ 0x00466618   (est. sk_report_66618)
 * Ghidra: void FUN_00466618(void)
 * Tail-calls thunk_FUN_002acbb8 (report emit) and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00466618(void)
{
    thunk_FUN_002acbb8();
}

/* FUN_00466624 @ 0x00466624   (est. sk_frame_call_66624)
 * Ghidra: void FUN_00466624(void)
 * Register fragment: calls FUN_004589e8(x26 + 0xc0, &stack0x160) — object
 * field plus a stack-frame address.
 * Confidence: low
 * Notes: unaff_x26; stack arg. */
void FUN_00466624(word_t x26)
{
    uint8_t frame[0x160];
    FUN_004589e8(x26 + 0xc0, frame);
}

/* FUN_00466630 @ 0x00466630   (est. sk_copy_66630)
 * Ghidra: void FUN_00466630(undefined8 param_1)
 * Copies 0x80 bytes from a stack frame to param_1 via sk_memcpy.
 * Confidence: low
 * Notes: memcpy of 0x80 from stack. */
void FUN_00466630(word_t param_1)
{
    uint8_t frame[0x80];
    FUN_00117cc4(param_1, (word_t)frame, 0x80);
}

/* FUN_0046663c @ 0x0046663c   (est. sk_call_6663c)
 * Ghidra: void FUN_0046663c(undefined8 param_1, undefined8 param_2, undefined8 param_3)
 * Calls FUN_001b9084(param_1, param_3).
 * Confidence: low
 * Notes: two-arg forward. */
void FUN_0046663c(word_t a, word_t b, word_t c)
{
    FUN_001b9084(a, c);
}

/* FUN_00466648 @ 0x00466648   (est. sk_call_66648)
 * Ghidra: void FUN_00466648(void)
 * Tail-calls FUN_0042ec68 and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00466648(void)
{
    FUN_0042ec68();
}

/* FUN_00466654 @ 0x00466654   (est. sk_call_66654)
 * Ghidra: void FUN_00466654(void)
 * Tail-calls FUN_004589e8 and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00466654(void)
{
    FUN_004589e8();
}

/* FUN_00466660 @ 0x00466660   (est. sk_shift_call_66660)
 * Ghidra: void FUN_00466660(void)
 * Register fragment: forwards (x22 >> 0xe) to thunk_FUN_002298d4.
 * Confidence: low
 * Notes: unaff_x22; page index. */
void FUN_00466660(word_t x22)
{
    thunk_FUN_002298d4(x22 >> 0xe);
}

/* FUN_0046666c @ 0x0046666c   (est. sk_shift_call_6666c)
 * Ghidra: void FUN_0046666c(void)
 * Register fragment: forwards (x21 >> 0xe) to thunk_FUN_002298d4.
 * Confidence: low
 * Notes: unaff_x21; page index. */
void FUN_0046666c(word_t x21)
{
    thunk_FUN_002298d4(x21 >> 0xe);
}

/* FUN_00466678 @ 0x00466678   (est. sk_release_66678)
 * Ghidra: void FUN_00466678(void)
 * Tail-calls the object-release helper FUN_003a25d4 and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00466678(void)
{
    FUN_003a25d4();
}

/* FUN_00466684 @ 0x00466684   (est. sk_copy_66684)
 * Ghidra: void FUN_00466684(undefined8 param_1)
 * Copies 0x59 bytes from a stack frame to param_1 via sk_memcpy.
 * Confidence: low
 * Notes: memcpy of 0x59 from stack. */
void FUN_00466684(word_t param_1)
{
    uint8_t frame[0x59];
    FUN_00117cc4(param_1, (word_t)frame, 0x59);
}

/* FUN_00466690 @ 0x00466690   (est. sk_release_66690)
 * Ghidra: void FUN_00466690(void)
 * Tail-calls the object-release helper FUN_003a25d4 and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00466690(void)
{
    FUN_003a25d4();
}

/* FUN_0046669c @ 0x0046669c   (est. sk_call_6669c)
 * Ghidra: void FUN_0046669c(void)
 * Tail-calls FUN_004589e8 and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_0046669c(void)
{
    FUN_004589e8();
}

/* FUN_004666a8 @ 0x004666a8   (est. sk_alloc_link_666a8)
 * Ghidra: void FUN_004666a8(void)
 * Tail-calls FUN_0036b588 (allocator link) and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_004666a8(void)
{
    FUN_0036b588();
}

/* FUN_004666b4 @ 0x004666b4   (est. sk_call0_666b4)
 * Ghidra: void FUN_004666b4(void)
 * Calls thunk_FUN_002298d4 with a zero argument.
 * Confidence: low
 * Notes: forward 0. */
void FUN_004666b4(void)
{
    thunk_FUN_002298d4(0);
}

/* FUN_004666c0 @ 0x004666c0   (est. sk_release_666c0)
 * Ghidra: void FUN_004666c0(long param_1)
 * Releases the object word at (param_1 + 8) via FUN_003a25d4.
 * Confidence: low
 * Notes: single deref + release. */
void FUN_004666c0(word_t param_1)
{
    FUN_003a25d4(*(word_t *)(param_1 + 8));
}

/* FUN_004666cc @ 0x004666cc   (est. sk_call_666cc)
 * Ghidra: void FUN_004666cc(void)
 * Tail-calls FUN_00458b14 and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_004666cc(void)
{
    FUN_00458b14();
}

/* FUN_004666e4 @ 0x004666e4   (est. sk_nop_666e4)
 * Ghidra: void FUN_004666e4(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004666e4(void)
{
    return;
}

/* FUN_004666f8 @ 0x004666f8   (est. sk_nop_666f8)
 * Ghidra: void FUN_004666f8(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_004666f8(void)
{
    return;
}

/* FUN_00466730 @ 0x00466730   (est. sk_nop_66730)
 * Ghidra: void FUN_00466730(void)
 * Empty stub; no side effects.
 * Confidence: high
 * Notes: empty body. */
void FUN_00466730(void)
{
    return;
}

/* FUN_00466744 @ 0x00466744   (est. sk_syscall_dispatch_66744)
 * Ghidra: void FUN_00466744(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Large guarded syscall/error dispatcher: captures the launch image pair,
 * marshals the syscall args, runs the error-code dispatch through a sequence
 * of runtime thunks and vtable method calls, and reports the result through
 * FUN_0008e500. Branches on a compare helper's Z flag to choose the success /
 * argument-invalid path.
 * Confidence: low
 * Notes: register-carried context pointers (extraout_x8/x9/x12/x16); the
 * SUB_54ffff60f100041f thunks are the guarded-entry supervisor calls. */
void FUN_00466744(word_t p1, word_t p2, word_t p3, word_t p4,
                  word_t p5, word_t p6)
{
    cl4_pair_t img;         /* launch image pair (auVar8) */
    cl4_pair_t t9;          /* second pair (auVar9) */
    uint64_t a;             /* uVar6 */
    uint64_t b;             /* uVar3 */
    uint64_t c;             /* uVar2 */
    uint64_t arg4;          /* uVar4 */
    uint64_t res;           /* uVar1 */
    long off;               /* lVar5 */
    word_t ctx16;           /* extraout_x16 (object ptr) */
    word_t ctx16a;          /* extraout_x16_00 */
    word_t ctx16b;          /* extraout_x16_01 */
    word_t ctxx8;           /* extraout_x8 */
    word_t ctxx9;           /* extraout_x9 */
    word_t ctxx12;          /* extraout_x12 */
    code_fn f8;             /* extraout_x8_0* */
    code_fn f9;             /* extraout_x9_00 */
    word_t x25;             /* unaff_x25 */
    word_t x30;             /* unaff_x30 */
    uint64_t local_50;

    img = FUN_0008e518();
    a = p3;
    b = p4;
    c = FUN_004aa67c();
    FUN_003515fc(c, b);                 /* marshal syscall args (2,3) */
    b = FUN_00377824();
    FUN_00464f4c();
    FUN_00077894(p4);
    FUN_00377bec();                     /* cached call dispatch */
    c = FUN_00350c98();                 /* syscall ret zero */
    c = FUN_00310e08(c, b);             /* swift runtime thunk */
    FUN_000a6f88();
    FUN_0007c1a4();
    SK_SVC_CALL();
    FUN_00350428();
    FUN_004ac36c();
    FUN_003542b8();
    arg4 = FUN_00310d68();
    t9 = FUN_00350500();
    off = FUN_004ac628(t9.lo, t9.hi, arg4);
    FUN_000a6f88();
    FUN_0007c1a4();
    SK_SVC_CALL();
    FUN_004aba28();
    FUN_0007c028();
    SK_SVC_CALL();                      /* arg from (extraout_x8 + 0x40) */
    FUN_0034ab10();
    SK_SVC_CALL();
    SK_SVC_CALL();
    FUN_00466a68(((ctxx9 - ctxx12) - ctxx12) - ctxx12, img.lo, img.hi,
                 p3, p4, p5, p6);
    FUN_00352290();
    FUN_00350774();
    FUN_000839d8();
    off = (long)*(int *)(off + 0x30);
    SK_VMETHOD(ctx16b, 0x20, (word_t)0);    /* pcVar7 capture */
    {
        cl4_pair_t t8 = FUN_003504f4();
        SK_VMETHOD(ctx16b, 0x20, t8.lo, t8.hi, arg4);
    }
    FUN_00350b48(x25 + off);
    SK_VMETHOD(ctx16b, 0x20);
    FUN_00351390();
    if (FUN_00350884() == 0) {              /* in_ZR set */
        FUN_00351390(x25 + off);
        if (FUN_00350884() == 0) {          /* in_ZR set */
            FUN_00351274(*(uint64_t *)(ctx16b + 8));
            f8();
            res = 0;
            goto done;
        }
    } else {
        cl4_pair_t e = FUN_000a6e14();
        f9(e.lo, e.hi, arg4);
        FUN_00351390(x25 + off);
        if (FUN_00350884() != 0) {          /* !in_ZR */
            SK_VMETHOD(ctx16, 0x20, local_50, x25 + off, c);
            {
                cl4_pair_t t8 = FUN_00100c38();
                res = FUN_00206770(t8.lo, t8.hi, b, a);
            }
            f8 = *(code_fn *)(ctx16 + 8);
            FUN_003514e8();
            f8();
            FUN_003505e8();
            f8();
            FUN_00351274(*(uint64_t *)(ctx16b + 8));
            f8();
            res = res ^ 1;
            goto done;
        }
        FUN_003505e8(*(uint64_t *)(ctx16 + 8));
        f8();
    }
    SK_VMETHOD(ctx16a, 8);
    res = 1;
done:
    FUN_0008e500(res & 1, x30);
    return;
}

/* FUN_00466a68 @ 0x00466a68   (est. sk_syscall_dispatch_66a68)
 * Ghidra: void FUN_00466a68(undefined8,undefined8,undefined8,undefined8)
 * Syscall/error dispatcher core (sibling of 00466744): captures the launch
 * image, runs a span-search loop (FUN_00365b6c compare against the span at
 * +0x30) over the error candidates, and on each branch invokes the matching
 * error-report helper; finishes with a vtable method call and reports via
 * FUN_0008e500.
 * Confidence: low
 * Notes: register-carried pointers (extraout_x8/x9/x16); SUB_54ffff60f100041f
 * supervisor calls; span compare helper FUN_00365b6c. */
void FUN_00466a68(void)
{
    word_t p1 = 0, p2 = 0, p3 = 0, p4 = 0;  /* register-passed args */
    cl4_pair_t img;         /* auVar10 */
    cl4_pair_t t11;         /* auVar11 */
    uint64_t a;             /* uVar3 */
    uint64_t b;             /* uVar4 */
    uint64_t v;             /* uVar5 */
    uint64_t l6;            /* lVar6 */
    uint64_t l9;            /* lVar9 */
    int cmp;                /* iVar1 */
    uint32_t tag;           /* uVar7 */
    word_t x20, x21, x30;   /* register artifacts */
    code_fn fx8, fx9;
    word_t cx16;
    uint64_t local_48, s40, s38, s30, s28, s20, s18, s10;

    img = FUN_0008e518();
    l6 = img.hi;
    v = p4;
    FUN_004ac628(0);
    FUN_000a6f88();
    FUN_0007c1a4();
    SK_SVC_CALL();
    l9 = FUN_0034cff4();
    l9 = (long)*(int *)(l9 + 0x30);
    {
        word_t l2 = *(word_t *)(l6 - 8);
        t11 = FUN_000b43d0();
        fx9(t11.lo, t11.hi, l6);
    }
    FUN_00351dfc(x21 + l9);
    fx9();
    a = FUN_004aac78();
    FUN_004ab9ec(a, x21 + l9);
    cmp = FUN_00365b6c();
    if (cmp == 0) {
spancall1:
        a = FUN_004aac04();
        FUN_004ab9ec(a, x21 + l9);
        cmp = FUN_00365b6c();
        if (cmp == 0) {
spandone:
            FUN_00351214(cx16, img.lo);
            FUN_004678c8();
            goto finish;
        }
        FUN_004aac78();
        FUN_00351178();
        a = FUN_00365b6c();
        if ((int)a == 0) {
            FUN_004aaf38();
            FUN_00351178();
            cmp = FUN_00365b6c();
            if (cmp == 0) {
                FUN_003a25d4(s10);
                goto spandone;
            }
            FUN_004676a4(s28, s20, s18, s10, local_48, s40, s38, s30);
            tag = (uint32_t)s18;
            FUN_00351a50();
            FUN_003a25d4(s30);
        } else {
            FUN_004abd44(a, local_48);
            FUN_003a25d4(s40);
            FUN_004676a4(s28, s20, s18, s10);
            tag = (uint32_t)s18;
            FUN_00351a50();
            FUN_003a25d4(s10);
            s10 = v;
        }
        FUN_003a25d4(s10);
        if ((tag & 0xff) == 1) {
            v = FUN_004aa67c();
            FUN_00351de4(v, p4);
            v = FUN_00377824();
            FUN_00464f4c();
            FUN_0009e234();
            FUN_0035053c();
            FUN_00377bec();
            a = FUN_00350c98();
            FUN_00310e08(a, v);
            FUN_004ab1c8();
        } else {
            FUN_004aaf6c();
            FUN_00407ed0();
            FUN_0035136c();
            v = FUN_00377824();
            FUN_00464f4c();
            FUN_00350c08(p4);
            FUN_00377bec();
            a = FUN_00350c98();
            FUN_00310e08(a, v);
            FUN_004aae44();
            FUN_004ab9e0();
            FUN_00351c7c();
        }
        FUN_000839d8();
        v = FUN_004ac9d8().lo;
        img.lo = v;
        img.hi = p3;
        fx8 = (code_fn)0;
    } else {
        FUN_00465db0();
        FUN_00351178(&s28);
        a = FUN_00365b6c();
        if ((int)a == 0) {
            FUN_004aac04();
            FUN_00351178();
            cmp = FUN_00365b6c();
            if (cmp == 0) {
                FUN_003a25d4(s40);
                goto spancall1;
            }
            a = s40;
            b = FUN_0001d4f4().lo;
            tag = (uint32_t)a;
            FUN_004ac33c();
            FUN_003a25d4(s40);
            FUN_00351214(b);
            FUN_004aca04();
            FUN_004676a4();
            FUN_00351a50();
            FUN_003a25d4(s10);
            x20 = s20;
        } else {
            b = v;
            FUN_004abd44(a, s28);
            v = b;
            FUN_003a25d4(s20);
            FUN_004abd64();
            a = s40;
            FUN_0001d4f4();
            tag = (uint32_t)a;
            FUN_003a25d4(s40);
            FUN_00351324();
            FUN_00352ea8();
            FUN_004676a4();
            FUN_00351a50();
            FUN_003a25d4(b);
        }
        FUN_003a25d4(v);
        if ((tag & 0xff) == 1) {
            v = FUN_004aa67c();
            FUN_00351de4(v, p4);
            v = FUN_00377824();
            FUN_00464f4c();
            FUN_0009e234();
            FUN_0035053c();
            FUN_00377bec();
            a = FUN_00350c98();
            FUN_00310e08(a, v);
            FUN_004ab1c8();
        } else {
            FUN_004aaf6c();
            v = FUN_00407ed0();
            v = FUN_00377824(v, p4, l6, x20);
            FUN_00464f4c();
            FUN_00350c08(p4);
            FUN_00377bec();
            a = FUN_00350c98();
            FUN_00310e08(a, v);
            FUN_004aae44();
            FUN_004ab9e0();
            FUN_00351c7c();
        }
        v = FUN_000839d8();
        img = FUN_004ac9d8(v, p3);
        fx8 = (code_fn)0;
    }
    fx8(img.lo, img.hi);
finish:
    FUN_00350494(*(uint64_t *)(cx16 + 8));
    fx8();
    FUN_0008e500(x30);
    return;
}

/* FUN_00466f18 @ 0x00466f18   (est. sk_syscall_dispatch_66f18)
 * Ghidra: void FUN_00466f18(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Six-argument syscall/error dispatcher (sibling of 00466a68): runs the same
 * span-search over error candidates with FUN_00365b6c, picks the matching
 * error-report handler per candidate tag (byte 0 == 1 selects the argument /
 * operation-invalid path), then reports via FUN_0008e500.
 * Confidence: low
 * Notes: register-carried pointers; SUB supervisor calls; FUN_00027754
 * release helper; L4_ErrorCode path via FUN_003508fc. */
void FUN_00466f18()
{
    word_t p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0, p6 = 0; /* register args */
    cl4_pair_t img;         /* auVar10 */
    cl4_pair_t t11;         /* auVar11 */
    uint64_t a, b, v;       /* uVar3, uVar4, uVar5 */
    uint32_t tag;           /* uVar7 */
    uint64_t l6, l9;        /* lVar6, lVar9 */
    int cmp;
    word_t x20, x21, x30;
    code_fn fx8, fx9;
    word_t cx16;
    uint64_t local_48, s40, s30, s28, s20, s18, s10;

    img = FUN_0008e518();
    l6 = img.hi;
    v = p4;
    FUN_004ac628(0);
    FUN_000a6f88();
    FUN_0007c1a4();
    SK_SVC_CALL();
    l9 = FUN_0034cff4();
    l9 = (long)*(int *)(l9 + 0x30);
    {
        word_t l2 = *(word_t *)(l6 - 8);
        t11 = FUN_000b43d0();
        fx9(t11.lo, t11.hi, l6);
    }
    FUN_0035256c(x21 + l9);
    fx9();
    a = FUN_004aac78();
    cmp = FUN_00365b6c(a, x21 + l9, p3);
    if (cmp == 0) {
spancall1:
        a = FUN_004aac04();
        cmp = FUN_00365b6c(a, x21 + l9, p3);
        if (cmp != 0) {
            FUN_004aac78();
            FUN_00351bd4();
            a = FUN_00365b6c();
            if ((int)a != 0) {
                FUN_004abd44(a, local_48);
                FUN_003a25d4(s40);
                FUN_00350a70();
                tag = s18;
                FUN_004676a4();
                FUN_00351a50();
                FUN_003a25d4(s10);
                FUN_003a25d4(v);
                if ((tag & 0xff) != 1) {
                    FUN_004aaf6c();
                    v = FUN_00027754(p4);
                    a = FUN_004aa770();
                    goto span_bad;
                }
                v = FUN_00027754(p4);
                a = FUN_00407ed0();
                goto span_good;
            }
            FUN_004aaf38();
            FUN_00351bd4();
            cmp = FUN_00365b6c();
            if (cmp != 0) {
                FUN_00350a70();
                tag = s18;
                FUN_004676a4();
                FUN_00351a50();
                FUN_003a25d4(s30);
                FUN_003a25d4(s10);
                if ((tag & 0xff) == 1) {
                    FUN_00027754(p4);
                    FUN_00407ed0();
                    FUN_00350b9c();
                    v = FUN_00377824();
                    FUN_00464f4c();
                    img = FUN_003508fc();
                    FUN_00377bec(img.lo, img.hi, v);
                    a = FUN_00350c98();
                    FUN_00310e08(a, v);
                    FUN_004ab1c8();
                } else {
                    FUN_004aaf6c();
                    v = FUN_00027754(p4);
                    a = FUN_004aa770();
                    a = FUN_00377824(a, v, l6, 0x0060e208);
                    FUN_00464f4c();
                    FUN_00351e3c(v, l6);
                    FUN_00377bec();
                    v = FUN_00350c98();
                    FUN_00310e08(v, a);
                    FUN_004aae44();
                    FUN_004ab9e0();
                    FUN_00351c7c();
                }
                FUN_000839d8();
                v = FUN_004ac9d8().lo;
                img.lo = v;
                img.hi = p3;
                fx8 = (code_fn)0;
                goto span_pub;
            }
            FUN_003a25d4(s10);
        }
        FUN_00027754(p4);
        FUN_00027754(p6);
        FUN_003515d8(cx16, img.lo);
        FUN_004678c8();
        goto finish;
    } else {
        FUN_00465db0();
        FUN_00351bd4(&s28);
        a = FUN_00365b6c();
        if ((int)a == 0) {
            FUN_004aac04();
            FUN_00351bd4();
            cmp = FUN_00365b6c();
            if (cmp == 0) {
                FUN_003a25d4(s40);
                goto spancall1;
            }
            a = s40;
            b = FUN_0001d4f4(0xf, local_48).lo;
            tag = (uint32_t)a;
            FUN_004ac33c();
            FUN_003a25d4(s40);
            FUN_00351214(b);
            FUN_004aca04();
            FUN_004676a4();
            FUN_00351a50();
            FUN_003a25d4(s10);
            x20 = s20;
        } else {
            b = v;
            FUN_004abd44(a, s28);
            v = b;
            FUN_003a25d4(s20);
            a = s40;
            FUN_0001d4f4(0xf, local_48);
            tag = (uint32_t)a;
            FUN_004abd9c();
            FUN_003a25d4(s40);
            FUN_00084174();
            FUN_00352ea8();
            FUN_004676a4();
            FUN_00351a50();
            FUN_003a25d4(b);
        }
        FUN_003a25d4(v);
        if ((tag & 0xff) == 1) {
            v = FUN_00027754(p4);
            a = FUN_00407ed0();
span_good:
            v = FUN_00377824(a, v, l6, x20);
            FUN_00464f4c();
            img = FUN_003508fc();
            FUN_00377bec(img.lo, img.hi, v, x20);
            a = FUN_00350c98();
            FUN_00310e08(a, v);
            FUN_004ab1c8();
        } else {
            FUN_004aaf6c();
            v = FUN_00027754(p4);
            a = FUN_004aa770();
span_bad:
            a = FUN_00377824(a, v, l6, 0x0060e208);
            FUN_00464f4c();
            FUN_00351e3c(v, l6);
            FUN_00377bec();
            v = FUN_00350c98();
            FUN_00310e08(v, a);
            FUN_004aae44();
            FUN_004ab9e0();
            FUN_00351c7c();
        }
        v = FUN_000839d8();
        img = FUN_004ac9d8(v, p3);
        fx8 = (code_fn)0;
span_pub:
        fx8(img.lo, img.hi);
    }
finish:
    FUN_00351130(*(uint64_t *)(cx16 + 8));
    fx8();
    FUN_0008e500(x30);
    return;
}

/* FUN_00467468 @ 0x00467468   (est. sk_syscall_check_67468)
 * Ghidra: bool FUN_00467468(undefined8,undefined8,undefined8,undefined8)
 * Wrapper around the 6-arg dispatcher FUN_00466f18: releases p4, prepares a
 * local argument buffer (p1,p2), dispatches with p3, and returns whether the
 * outcome byte differs from 1 (i.e. the operation did NOT take the
 * argument-invalid path).
 * Confidence: low
 * Notes: returns local_28 != 1. */
bool FUN_00467468(word_t p1, word_t p2, word_t p3, word_t p4)
{
    uint64_t a0 = p1, a1 = p2;
    uint8_t buf[16];
    char out;

    FUN_00027754(p4);
    FUN_004ab920();
    FUN_00466f18((word_t)buf, (word_t)&a0, p3);
    return out != 1;
}

/* FUN_004674e4 @ 0x004674e4   (est. sk_syscall_check_674e4)
 * Ghidra: bool FUN_004674e4(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Six-argument wrapper around FUN_00466f18: stores (p1..p4) into a local
 * buffer, releases p6, prepares p5 and dispatches; returns whether the
 * outcome byte differs from 1.
 * Confidence: low
 * Notes: returns local_28 != 1. */
bool FUN_004674e4(word_t p1, word_t p2, word_t p3, word_t p4,
                  word_t p5, word_t p6)
{
    uint64_t a0 = p1, a1 = p2, a2 = p3, a3 = p4;
    uint8_t buf[16];
    char out;

    FUN_00356bb0(p6);
    FUN_004ac980();
    FUN_00466f18((word_t)buf, (word_t)&a0, p5);
    return out != 1;
}

/* FUN_00467564 @ 0x00467564   (est. sk_syscall_report_67564)
 * Ghidra: void FUN_00467564(void)
 * Error-report helper: prepares the report object, builds a value via the
 * runtime thunks, dispatches to FUN_00467678 with the prepared pair, then
 * conditionally runs a secondary cleanup path when a stack flag is set.
 * Confidence: low
 * Notes: register fragments (extraout_x8/x16); conditional branch on stack
 * flag; unreachable block at 0x00467618 removed by the decompiler. */
void FUN_00467564(word_t in_x4, word_t stack30, word_t s18, word_t s20)
{
    cl4_pair_t p;
    uint64_t u2, u3;
    word_t ctx16, cx1, x30;
    bool b1;

    FUN_0035a9b0();
    FUN_0034d090();
    FUN_004ab5d4(in_x4);
    FUN_00350560();
    u2 = (word_t)ctx16;                 /* (*extraout_x8)() */
    FUN_00356bb0();
    p = FUN_004abfb8();
    FUN_00270c08(p.lo, p.hi, cx1);
    FUN_004aa95c();
    FUN_003513a8();
    u3 = FUN_00377824();
    p = FUN_00350af4((word_t)s18);
    FUN_00467678(p.lo, p.hi, s18, s20, u2, u3);
    FUN_0036b118(u2);
    FUN_003a25d4(s20);
    b1 = stack30 != 0;
    if (b1) {
        FUN_003542b8();
        FUN_004974ac();
        FUN_00352efc();
        u2 = FUN_00310d68();
        FUN_0034ab20(u2, u2);
        SK_VMETHOD(ctx16, 8, (word_t)s18);
    }
    FUN_0035a8d0(b1, x30);
    return;
}

/* FUN_00467678 @ 0x00467678   (est. sk_call_67678)
 * Ghidra: void FUN_00467678(void)
 * Tail-calls FUN_0049490c and returns.
 * Confidence: low
 * Notes: single call. */
void FUN_00467678(void)
{
    FUN_0049490c();
}

/* FUN_004676a4 @ 0x004676a4   (est. sk_syscall_emit_676a4)
 * Ghidra: void FUN_004676a4(void)
 * Emits a syscall/error report: releases scratch objects, marshals a 0x59-byte
 * buffer from stack, and either passes the tag byte 1 straight through or
 * reformats via FUN_0046ef90, then reports through FUN_00497994/FUN_004aba34.
 * Confidence: low
 * Notes: register/stack artifacts (in_x7, in_stack_*); memcpy 0x59. */
void FUN_004676a4(void)
{
    word_t in_x7 = 0;
    uint64_t s18 = 0, s20 = 0, s28 = 0, s90 = 0, s98 = 0;
    uint64_t sa0 = 0, sa8 = 0, se0 = 0; char se8 = 0; /* register/stack args */
    (void)sa8; (void)sa0;
    uint64_t v;             /* uVar1 */
    char tag;               /* cVar2 */
    uint8_t tagout;         /* uVar3 */
    cl4_pair_t p;
    uint8_t buf[0x59];
    uint8_t frame[0x30];

    FUN_004acb04();
    FUN_004abd04();
    thunk_FUN_0036b270(in_x7);
    thunk_FUN_0036b270();
    FUN_00100efc(&s90);
    FUN_0035053c();
    FUN_0046777c();
    tag = se8;
    v = se0;
    FUN_00117cc4((word_t)buf, (word_t)&s90, 0x59);
    if (tag == 1) {
        tagout = 1;
    } else {
        FUN_0046ef90(frame, s90, s98, sa0, sa8, v);
        s28 = s20;
        tagout = (uint8_t)s18;
    }
    FUN_00497994((word_t)buf);
    p = FUN_0009461c();
    FUN_004aba34(p.lo, p.hi, tagout, (word_t)0);
    return;
}

/* FUN_0046777c @ 0x0046777c   (est. sk_syscall_frame_6777c)
 * Ghidra: void FUN_0046777c(undefined8,undefined8,undefined8,undefined1,undefined8,undefined8,undefined8,undefined8)
 * Builds an 8-word dispatch frame: validates the address-pair range from
 * FUN_00351e20 (lo>>0xe <= hi>>0xe), packs the captured pair plus the six
 * arguments into the frame and forwards it to FUN_00351d30; panics
 * (SoftwareBreakpoint 0x467848) if the range check fails.
 * Confidence: low
 * Notes: frame of 8 words; breakpoint 0x467848 on invalid range. */
void FUN_0046777c()
{
    word_t p1 = 0, p2 = 0, p3 = 0, p5 = 0, p6 = 0, p7 = 0, p8 = 0;
    uint8_t p4 = 0;   /* register/stack args */
    cl4_pair_t r;           /* auVar2 */
    cl4_pair_t q;           /* auVar3 */
    word_t cx8, cx9, cx9b, cx10;

    r = FUN_00351e20();
    if (r.lo >> 0xe <= r.hi >> 0xe) {
        FUN_00351790();
        q = thunk_FUN_002b74c0();
        thunk_FUN_0036b270(p8);
        FUN_00462e9c(q.lo, q.hi);
        q = FUN_0046ea44();
        *(word_t *)cx8       = r.lo;
        *(word_t *)(cx8 + 8) = r.hi;
        *(word_t *)(cx8 + 0x10) = cx10;
        *(word_t *)(cx8 + 0x18) = cx9b;
        *(word_t *)(cx8 + 0x20) = p5;
        *(word_t *)(cx8 + 0x28) = p6;
        *(word_t *)(cx8 + 0x30) = p7;
        *(word_t *)(cx8 + 0x38) = p8;
        *(cl4_pair_t *)(cx8 + 0x40) = q;
        *(word_t *)(cx8 + 0x50) = p3;
        *(uint8_t *)(cx8 + 0x58) = p4;
        FUN_00351d30(cx9);
        return;
    }
    SK_PANIC("range");      /* SoftwareBreakpoint(1, 0x467848): does not return */
}

/* FUN_00467848 @ 0x00467848   (est. sk_report_done_67848)
 * Ghidra: void FUN_00467848(void)
 * Finishes a report: if the flag byte at (x20 + 0x58) is 1, resets via
 * FUN_00019858; otherwise captures the pending value at (x20+0x50), reformats
 * via FUN_0046ef90 and stores the new pair back into the object.
 * Confidence: low
 * Notes: unaff_x20 register fragment. */
void FUN_00467848(word_t x20)
{
    uint64_t v;
    uint8_t buf[0x80];
    word_t r8, r9;

    if (*(char *)(x20 + 0x58) == 1) {
        FUN_00019858();
    } else {
        v = *(uint64_t *)(x20 + 0x50);
        FUN_00117cc4((word_t)&buf[0x10]);
        FUN_0046ef90(buf, buf[0x10], buf[0x18], buf[0x20], buf[0x28], v);
        FUN_004ac8c0();
        *(word_t *)(x20 + 0x50) = r8;
        *(uint8_t *)(x20 + 0x58) = (uint8_t)r9;
    }
    return;
}

/* FUN_004678c8 @ 0x004678c8   (est. sk_syscall_validate_678c8)
 * Ghidra: void FUN_004678c8(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Six-argument syscall validator: marshals the launch image and error-code
 * descriptors (L4_ErrorCodeOperationInvalid string at 0x00688748), builds an
 * error object via FUN_0036a940, runs the candidate walk and, if the scan
 * succeeds (result bit 0), dispatches to FUN_00468144; otherwise panics at
 * SoftwareBreakpoint 0x467de4.
 * Confidence: low
 * Notes: string s_L4_ErrorCodeOperationInvalid_00688748; breakpoint
 * 0x467de4; vtable dispatch; SUB supervisor calls. */
void FUN_004678c8(void)
{
    word_t p1 = 0, p2 = 0, p3 = 0, p4 = 0, p5 = 0, p6 = 0; /* register args */
    cl4_pair_t img;         /* auVar14 */
    cl4_pair_t t15;         /* auVar15 */
    uint64_t u2, u3, u6, u7, u8;
    long l4, l5, l9;
    word_t cx1, cx8, cx9, cx12, cx16;
    code_fn f8, f9;
    uint64_t local_78, local_50;
    uint64_t walk;

    FUN_0008e518();
    u7 = p4;
    FUN_004633e0();
    u2 = FUN_00377824(0xff, p4, cx1);
    u3 = FUN_0034b0b4();
    l4 = FUN_003722e4(u3, u2, u2);
    FUN_000a6f88();
    SK_SVC_CALL();                      /* arg from (extraout_x8_00+0x40) */
    FUN_003493c4();
    FUN_003503f8();
    SK_SVC_CALL();
    FUN_00350464();
    FUN_004ac36c();
    FUN_0007c028();
    SK_SVC_CALL();                      /* arg from (extraout_x8_01+0x40) */
    FUN_003493c4();
    FUN_003503f8();
    SK_SVC_CALL();
    FUN_00350464();
    FUN_00464f4c();
    FUN_0035063c(p4, cx1);
    img = FUN_00377bec();
    u3 = img.lo;
    FUN_00350530(u3, img.hi, u3);
    l5 = FUN_00310e08();
    FUN_000a6f88();
    FUN_0007c1a4();
    SK_SVC_CALL();
    FUN_00350428();
    FUN_004ac2b8();
    u6 = FUN_004aac68();
    u6 = FUN_00377824(u6, p4, cx1);
    FUN_000a6f88();
    FUN_0007c1a4();
    SK_SVC_CALL();
    FUN_004ac2ac();
    FUN_0007c028();
    SK_SVC_CALL();                      /* arg from (extraout_x8_03+0x40) */
    FUN_000aa4ec();
    FUN_004aba28();
    img = FUN_003512c0(*(uint64_t *)(cx12 + 0x10));
    f8(img.lo, img.hi, p3);
    FUN_00027754(p4);
    img = FUN_004aa5dc();
    u7 = FUN_00377824(img.lo, img.hi, cx1);
    FUN_00356bb0(p5);
    img = FUN_0035060c();
    u8 = FUN_0019e578(img.lo, img.hi, p3);
    l9 = FUN_0036a940(0x00688748 + 8, 0x40, 7);   /* L4_ErrorCodeOperationInvalid */
    *(uint64_t *)(l9 + 0x10) = cx1;
    *(uint64_t *)(l9 + 0x18) = p3;
    *(uint64_t *)(l9 + 0x20) = p4;
    *(uint64_t *)(l9 + 0x28) = p5;
    *(uint64_t *)(l9 + 0x30) = p6;
    *(uint64_t *)(l9 + 0x38) = u7;
    FUN_004ac8b4();
    FUN_0035139c(p4);
    FUN_0046490c();
    u7 = FUN_00377bec().lo;
    FUN_004ac9c0(u8, 0x004a4b78);
    img = FUN_00467de4();
    FUN_00270c08(0x004b5a74, 0, cx1, p4);
    FUN_0035156c(p4);
    f9(cx8, cx1, p4);
    FUN_00351750(p4);
    f9(cx9, cx1, p4);
    FUN_0035166c(u3);
    FUN_000e15d8();
    FUN_0035063c();
    walk = (word_t)f8;
    if ((walk & 1) != 0) {
        code_fn vm20 = *(code_fn *)(cx16 + 0x20);
        FUN_0035139c(local_50);
        vm20();
        FUN_000bd3a4(local_50 + *(int *)(l4 + 0x30));
        vm20();
        SK_VMETHOD(cx16, 0x10, (word_t)0, local_50, l4);
        FUN_003511d8(local_78);
        vm20();
        code_fn vm8 = *(code_fn *)(cx16 + 8);
        vm8((word_t)0 + *(int *)(l4 + 0x30), u2);
        SK_VMETHOD(cx16, 0x20, (word_t)0, local_50, l4);
        vm20(local_78 + *(int *)(l5 + 0x24), 0 + *(int *)(l4 + 0x30), u2);
        FUN_000b4390();
        vm8();
        t15 = FUN_00351450(cx8);
        FUN_00468144(t15.lo, t15.hi, img.lo, img.hi, l9, u7, u6, u7);
        FUN_0036b118(u7);
        FUN_0036b118(img.hi);
        FUN_0036b118(img.lo);
        FUN_00350470(*(uint64_t *)(cx16 + 8));
        f8();
        FUN_0007c1c4(*(uint64_t *)(cx16 + 8));
        f8();
        FUN_0008e500((word_t)0);
        return;
    }
    SK_PANIC("scan");       /* SoftwareBreakpoint(1, 0x467de4): does not return */
}

/* FUN_00467de4 @ 0x00467de4   (est. sk_syscall_prep_67de4)
 * Ghidra: void FUN_00467de4(void)
 * Prepares the syscall error object: runs the argument-marshalling sequence
 * (FUN_00077888, FUN_003509ec, FUN_00027754, FUN_004aa5dc, FUN_00377824,
 * FUN_00100efc, FUN_0047277c).
 * Confidence: low
 * Notes: ordered helper chain; in_x4 register artifact. */
cl4_pair_t FUN_00467de4()
{
    word_t in_x4 = 0;   /* register-passed arg (arity varies) */
    cl4_pair_t r = { 0, 0 };   /* decompiler shows void body but callers read a
                                  return pair (Ghidra inconsistency); model the
                                  register pair as zeroed. */
    FUN_00077888();
    FUN_003509ec();
    FUN_00027754(in_x4);
    FUN_004aa5dc();
    FUN_00377824();
    FUN_00100efc();
    FUN_0047277c();
    return r;
}

/* FUN_00467e44 @ 0x00467e44   (est. sk_span_search_67e44)
 * Ghidra: undefined1 [16] FUN_00467e44(undefined8,ulong,undefined8,undefined8,ulong,ulong,long,long,code*)
 * The vspace span-search walker: iterates a span array at (param_7+0x28) with
 * param_7+0x10 as the count, stepping the current address by FUN_002b3b50,
 * and for each candidate calls the supplied callback (*param_9) with a
 * (slot, span) pair built by FUN_002b439c. Returns the final (addr, span)
 * pair. Uses SoftwareBreakpoint traps for out-of-range / underflow panics.
 * Confidence: medium
 * Notes: span stride 16 bytes; callback returns bit 0 to stop; breakpoints
 * 0x4680e4/0x468104/0x46813c/0x468140/0x468144. */
cl4_pair_t FUN_00467e44(word_t base, uint64_t base_hi, word_t p3, word_t p4,
                        uint64_t cur, uint64_t cur_hi, word_t slots,
                        word_t slots_hi, code_fn cb)
{
    uint64_t count, idx, si;
    uint64_t pn;            /* current page number */
    uint64_t pn_hi;         /* limit page */
    cl4_pair_t result = { .lo = 0, .hi = 0 };

    count = 0;
    si = 0;
    pn = cur;
    do {
        uint64_t n = cur >> 0xe;
        if (n < pn >> 0xe) {
            /* advance within the span list */
            if (*(uint64_t *)(slots_hi + 0x10) <= count) {
                SK_PANIC("slots");      /* breakpoint 0x468140 */
            }
            if ((long)si <= *(long *)(slots_hi + 0x20 + count * 8)) {
                count = *(uint64_t *)(slots + 0x10);
                uint64_t *sp = (uint64_t *)(slots + 0x28) + si * 2;
                while ((count != si && 0x3fff < (pn ^ cur_hi))) {
                    if (count <= si) {
                        SK_PANIC("span");   /* breakpoint 0x46813c */
                    }
                    uint64_t slo = sp[-1];
                    uint64_t shi = *sp;
                    thunk_FUN_0036b270(shi);
                    cl4_pair_t r = FUN_002b439c(pn, base, base_hi, p3, p4);
                    uint64_t keep = cb(&slo, r.lo);
                    FUN_003a25d4(shi);
                    FUN_003a25d4(r.hi);
                    if ((keep & 1) == 0) {
                        count = 0;
                        goto next;
                    }
                    si = si + 1;
                    pn = FUN_002b3b50(pn, base, base_hi, p3, p4);
                    sp = sp + 2;
                }
                if (count == si) {
                    if (pn >> 0xe < n) {
                        SK_PANIC("span2");  /* breakpoint 0x468144 */
                    }
                    goto ret;
                }
                count = 0;
            }
        } else {
            si = 0;
            count = *(uint64_t *)(slots + 0x10);
            pn = cur;
            uint64_t *sp = (uint64_t *)(slots + 0x28);
            while ((count != si && 0x3fff < (pn ^ cur_hi))) {
                uint64_t slo = sp[-1];
                uint64_t shi = *sp;
                thunk_FUN_0036b270(shi);
                cl4_pair_t r = FUN_002b439c(pn, base, base_hi, p3, p4);
                uint64_t keep = cb(&slo, r.lo);
                FUN_003a25d4(shi);
                FUN_003a25d4(r.hi);
                if ((keep & 1) == 0) {
                    count = 0;
                    goto next;
                }
                si = si + 1;
                pn = FUN_002b3b50(pn, base, base_hi, p3, p4);
                sp = sp + 2;
            }
            if (count == si) {
                if (pn >> 0xe < n) {
                    SK_PANIC("span3");  /* breakpoint 0x468104 */
                }
                goto ret;
            }
            count = 0;
        }
next:
        if (n == base_hi >> 0xe) {
            pn = 0;
            cur = 0;
ret:
            result.hi = pn;
            result.lo = cur;
            return result;
        }
        pn = FUN_002b3b50(pn, base, base_hi, p3, p4);
        count = count + 1;
        if (si == 0) {
            SK_PANIC("underflow");      /* breakpoint 0x4680e4 */
        }
        si = si - 1;
    } while (1);
}

/* FUN_00468144 @ 0x00468144   (est. sk_syscall_walk_68144)
 * Ghidra: void FUN_00468144(void)
 * Large syscall candidate-walker: marshals the launch image, builds the error
 * descriptors, then loops a callback-driven scan (fn-pointer carrier from
 * FUN_00310954) over the candidate span at (in_x3+0x28). On a candidate match
 * it dispatches the report through the object vtable and releases scratch
 * state; the loop breaks via FUN_0008e500 when the scan succeeds (bit 0),
 * else panics (SoftwareBreakpoint 0x4686e4 etc).
 * Confidence: low
 * Notes: register-carried pointers (extraout_x8/x9/x12/x16); SUB supervisor
 * calls; breakpoints 0x4686dc/0x4686e0/0x4686e4/0x4686e8. */
void FUN_00468144(void)
{
    word_t in_x3 = 0, in_x6 = 0, in_x7 = 0, unaff_x27 = 0, unaff_x28 = 0; /* reg args */
    (void)unaff_x27;
    cl4_pair_t img;         /* auVar17 */
    uint64_t u3, u4, u5, u8, u9;
    long l4, l6, l9, l10, l11, l15, l17;
    uint64_t walk, cnt, idx;
    word_t cx8, cx9, cx12, cx16, cx16a, cx16b;
    code_fn fc7, fc12, f8, f9;
    word_t x30;
    uint64_t local_78, local_50, local_c8;
    uint64_t l1, cur;
    uint64_t local_18, local_10;

    FUN_0008e518();
    u4 = in_x6;
    u5 = in_x7;
    u3 = FUN_004aa67c();
    u4 = FUN_00377824(u3, u5, u4);
    FUN_00464f4c();
    FUN_003515fc(in_x7, in_x6);
    u5 = FUN_00377bec().lo;
    FUN_00350b84(0xff);
    l6 = FUN_00310e08();
    FUN_003504e8();
    u3 = FUN_00310d68();
    FUN_000a6f88();
    SK_SVC_CALL();                      /* arg from (extraout_x8_00+0x40) */
    FUN_003493c4();
    FUN_003503f8();
    SK_SVC_CALL();
    FUN_00350464();
    l10 = *(long *)(l6 - 8);
    SK_SVC_CALL();                      /* arg from (lVar10+0x40) */
    FUN_003493c4();
    FUN_003503f8();
    SK_SVC_CALL();
    FUN_00350464();
    FUN_003509a4();
    FUN_0007c028();
    SK_SVC_CALL();                      /* arg from (extraout_x8_02+0x40) */
    FUN_0034ab10();
    FUN_0034dfa4();
    SK_SVC_CALL();
    l15 = cx8 - cx12;
    SK_SVC_CALL();
    FUN_0034b540();
    SK_SVC_CALL();
    FUN_0034ba68();
    code_fn vm10 = *(code_fn *)(cx16 + 0x10);
    FUN_003511d8();
    vm10();
    vm10();
    local_18 = 0;
    local_10 = 0;
    FUN_003511d8(l15);
    vm10();
    fc7 = (code_fn)FUN_00310954(u5);
    cnt = 0;
    idx = 0;
    l11 = 0;
    l1 = local_18;
    do {
        local_18 = l1;
        walk = fc7(l15, unaff_x28, u4, u5);
        if ((walk & 1) == 0) {
            if ((long)cnt < 0) {
                SK_PANIC("neg");        /* breakpoint 0x4686e4 */
            }
            if (*(uint64_t *)(in_x3 + 0x10) <= cnt) {
                SK_PANIC("cap");        /* breakpoint 0x4686e8 */
            }
            if (idx <= *(long *)(in_x3 + 0x20 + cnt * 8)) {
                img = FUN_00351324();
                vm10(img.lo, img.hi, u4);
                *(uint64_t *)(l15 - 0x10) = in_x6;
                *(uint64_t *)(l15 - 8) = in_x7;
                *(uint64_t **)(l15 - 0x18) = &local_18;
                FUN_004ac888();
                FUN_00350878(cx9, l15);
                FUN_004acc48();
                fc12 = (code_fn)*(void **)cx16;
                FUN_003504ac();
                fc12();
                {
                    long r = FUN_000839f8(cx9, 1, l6);
                    idx = cx9;
                    if (r != 1) {
                        FUN_0035084c(cx9);
                        fc12();
                        fc12(unaff_x28, u4);
                        fc12(unaff_x27, u4);
                        fc7 = *(code_fn *)(l10 + 0x20);
                        local_c8 = cx9;
                        goto scan_adv;
                    }
                    goto scan_ok;
                }
            }
        } else {
            *(uint64_t *)(l15 - 8) = in_x7;
            *(uint64_t **)(l15 - 0x18) = &local_18;
            *(uint64_t *)(l15 - 0x10) = in_x6;
            FUN_004ac888();
            FUN_004acc48(cx8, l15, l15, 0);
            {
                long r = FUN_000839f8(cx8, 1, l6);
                idx = cx8;
                if (r != 1) {
                    fc7 = (code_fn)*(void **)cx16;
                    FUN_0035084c(cx8);
                    fc7();
                    fc7(unaff_x28, u4);
                    fc7(unaff_x27, u4);
                    fc7 = *(code_fn *)(l10 + 0x20);
scan_adv:
                    fc7(local_c8, idx, l6);
                    img = FUN_00351450();
                    fc7(img.lo, img.hi, l6);
                    u4 = 0;
                    goto done;
                }
            }
scan_ok:
            SK_VMETHOD(cx16, 8, (word_t)idx, u3);
        }
        FUN_00351750(in_x7);
        FUN_00350518((long *)(l6 - 8));
        f9();
        FUN_00027754(u5);
        u9 = FUN_0014ae44();
        FUN_003505e8(u9);
        FUN_00351b78();
        cnt = f8();
        fc12 = (code_fn)*(void **)cx16;
        FUN_003504ac();
        fc12();
        if ((cnt & 1) != 0) {
            FUN_0035084c();
            fc12();
            fc12(unaff_x28, u4);
            fc12(unaff_x27, u4);
            u4 = 1;
done:
            FUN_000839d8(cx8, u4, 1, l6);
            FUN_0008e500(cx9);
            return;
        }
        u9 = FUN_00027818(in_x7);
        FUN_00350b48(u9, l15);
        f8();
        local_10 = local_10 + 1;
        idx = local_18 - 1;
        l1 = idx;
        if (local_18 == 0) {
            SK_PANIC("dec");            /* breakpoint 0x4686e0 */
        }
    } while (1);
}

/* FUN_004686e8 @ 0x004686e8   (est. sk_syscall_report_686e8)
 * Ghidra: void FUN_004686e8(void)
 * Error-report helper: prepares the report frame, releases scratch values,
 * dispatches to FUN_00467678 with a prepared pair, then conditionally runs a
 * secondary clear path when a stack flag is set, reporting through
 * FUN_0007c1c4 / FUN_0035a8d0.
 * Confidence: low
 * Notes: register artifacts; unreachable block at 0x00468794 removed. */
void FUN_004686e8(word_t in_x3, word_t in_x4, word_t s10, word_t s18,
                  word_t s28, word_t s38)
{
    cl4_pair_t p;
    uint64_t u2, u3, u4;
    word_t cx8, x30;
    bool b1;

    FUN_0035a9b0();
    FUN_0034b318();
    FUN_00356bb0(in_x3);
    FUN_00270c08((word_t)s10, 0x004b5a74, 0);
    u3 = s28;
    u2 = s10;
    FUN_004ab5d4(in_x4);
    FUN_00084180();
    u4 = cx8;
    FUN_004aa95c();
    FUN_00350878();
    FUN_00377824();
    FUN_0034e5bc(s10, u2);
    FUN_00467678();
    FUN_003a25d4(u3);
    FUN_0036b118(u4);
    b1 = s18 != 0;
    if (b1) {
        FUN_004acc20();
        s38 = 0;
        FUN_004aa938();
        p = FUN_004a4b14((word_t)&s38);
    }
    FUN_0007c1c4(p.lo, p.hi, !b1);
    FUN_0035a8d0();
    return;
}

/* FUN_004687e8 @ 0x004687e8   (est. sk_syscall_jump_687e8)
 * Ghidra: void FUN_004687e8(void)
 * Prepares the syscall context and performs an indirect jump through the
 * object vtable at (x20 - 8) + 0x20 (decompiler could not recover the jump
 * table; "Too many branches"). Tail-dispatch into the target handler.
 * Confidence: low
 * Notes: unrecovered jumptable at 0x00468884; unaff_x20. */
void FUN_004687e8()
{
    word_t x20 = 0, cx8 = 0, cx16 = 0;   /* register args (arity varies) */
    long r;

    FUN_00077888();
    FUN_003509ec();
    FUN_004aa4fc();
    FUN_00377824();
    FUN_00349530();
    SK_VMETHOD(cx16, 0x20, (word_t)cx8);
    FUN_00350624(0);
    r = FUN_00497504();
    /* Indirect jump: *(*(x20-8)+0x20)(cx8 + *(int *)(r+0x24)) */
    SK_VMETHOD(*(word_t *)(x20 - 8), 0x20, cx8 + *(int *)(r + 0x24));
    return;
}

/* FUN_00468888 @ 0x00468888   (est. sk_syscall_dispatch_68888)
 * Ghidra: void FUN_00468888(undefined8,undefined8,undefined8)
 * Three-argument syscall/error dispatcher: marshals the launch image and error
 * descriptors, runs the candidate walk (fn-pointer carrier FUN_000277b8), and
 * on scan success dispatches the report through the object vtable; else panics
 * at SoftwareBreakpoint 0x468c6c.
 * Confidence: low
 * Notes: L4 error strings; vtable dispatch; breakpoint 0x468c6c. */
void FUN_00468888(word_t p1, word_t p2, word_t p3)
{
    cl4_pair_t img;         /* auVar13 */
    cl4_pair_t t14;         /* auVar14 */
    uint64_t u2, u3, u4, u9, walk;
    long l5, l6, l7, l11;
    word_t cx8, cx9, cx16, cx16a, cx16b;
    code_fn fc8, fc12, f8, f9;
    word_t x30;
    uint64_t local_50;

    img = FUN_0008e518();
    u3 = p3;
    u2 = FUN_004aad84();
    FUN_00377824(u2, u3, img.hi, 0x0061628c);
    FUN_004ab310();
    FUN_003510dc();
    FUN_0035053c();
    u3 = FUN_00377bec().lo;
    FUN_004aa770();
    FUN_00350548();
    u2 = FUN_00377824();
    u4 = FUN_0034b0b4();
    FUN_004ab644(u4, u2);
    FUN_003722e4();
    l5 = FUN_000a6f88();
    SK_SVC_CALL();                      /* arg from (extraout_x8_00+0x40) */
    FUN_003493c4();
    FUN_003503f8();
    SK_SVC_CALL();
    FUN_00350464();
    FUN_004ac36c();
    FUN_0007c028();
    SK_SVC_CALL();                      /* arg from (extraout_x8_01+0x40) */
    FUN_0034ab10();
    FUN_0034dfa4();
    SK_SVC_CALL();
    FUN_0034ba68();
    FUN_00464f4c();
    FUN_000b43d0();
    FUN_00351f1c();
    u4 = FUN_00377bec().lo;
    t14 = FUN_0035050c();
    l6 = FUN_00310e08(t14.lo, t14.hi, u4);
    FUN_000a6f88();
    FUN_0007c1a4();
    SK_SVC_CALL();
    FUN_00350428();
    FUN_0035256c(0);
    l7 = FUN_00497504();
    l11 = *(long *)(l7 - 8);
    FUN_003515d8(cx8);
    f9();
    fc8 = (code_fn)FUN_000277b8(u3);
    FUN_00350798();
    u9 = FUN_00377dcc();
    fc8(u9, u3);
    FUN_00351750(u3);
    FUN_003504f4(0x0061628c);
    f9();
    FUN_0035166c(u4);
    FUN_003508cc();
    FUN_00352ae4();
    walk = f8();
    if ((walk & 1) != 0) {
        code_fn vm20 = *(code_fn *)(cx16 + 0x20);
        t14 = FUN_003509b0();
        vm20(t14.lo, t14.hi, u2);
        FUN_00350c20(local_50 + *(int *)(l5 + 0x30));
        vm20();
        FUN_0035256c(cx9);
        f9();
        FUN_00351118(cx8);
        vm20();
        code_fn vm8 = *(code_fn *)(cx16 + 8);
        vm8(cx9 + *(int *)(l5 + 0x30), u2);
        FUN_0035256c(*(uint64_t *)(cx16 + 0x20), cx9);
        f8();
        vm20(cx8 + *(int *)(l6 + 0x24), cx9 + *(int *)(l5 + 0x30), u2);
        FUN_00100c38();
        vm8();
        fc8 = (code_fn)FUN_004a3008(p3);
        FUN_00350600(0);
        l5 = FUN_004a3038();
        FUN_00351584(cx8 + *(int *)(l5 + 0x24), img.lo, cx8);
        fc8();
        SK_VMETHOD(l11, 8, (word_t)img.lo, l7);
        SK_VMETHOD(cx16, 8, (word_t)cx8, l6);
        FUN_0008e500(x30);
        return;
    }
    SK_PANIC("scan");       /* SoftwareBreakpoint(1, 0x468c6c): does not return */
}

/* FUN_00468c6c @ 0x00468c6c   (est. sk_syscall_tail_68c6c)
 * Ghidra: void FUN_00468c6c(void)
 * Short syscall tail: loads the object field at (FUN_00464a44 + 0x18), runs
 * the arg/build sequence and dispatches a vtable call.
 * Confidence: low
 * Notes: small; register artifacts. */
void FUN_00468c6c(word_t cx8, word_t cx9)
{
    uint64_t v;
    long r;

    r = FUN_00464a44();
    v = *(uint64_t *)(r + 0x18);
    FUN_003505c4(0);
    FUN_00497504();
    FUN_004a2fd8(v);
    FUN_003511f0(cx8);
    ((code_fn)cx9)();
    return;
}

/* FUN_00468ce4 @ 0x00468ce4   (est. sk_syscall_thunk_68ce4)
 * Ghidra: void FUN_00468ce4(void)
 * Thin forwarder: runs the guarded-entry sequence and dispatches to
 * FUN_00468888 with the object's +0x10/+0x18 words.
 * Confidence: low
 * Notes: unaff_x19; SUB supervisor calls. */
void FUN_00468ce4(word_t x19, word_t cx8, word_t cx9, word_t cx12)
{
    FUN_00352800();
    FUN_000a6f88();
    SK_SVC_CALL();                      /* arg from (extraout_x8+0x40) */
    FUN_000aa4ec();
    SK_VMETHOD(cx12, 0x10, (word_t)(cx9 - cx8));
    FUN_00468888(cx9 - cx8, *(uint64_t *)(x19 + 0x10), *(uint64_t *)(x19 + 0x18));
    return;
}

/* FUN_00468d98 @ 0x00468d98   (est. sk_lookup_68d98)
 * Ghidra: undefined8 FUN_00468d98(void)
 * Runs FUN_0049751c then FUN_00497994 and returns the first result.
 * Confidence: low
 * Notes: two calls; returns uVar1. */
uint64_t FUN_00468d98(void)
{
    uint64_t v;

    v = FUN_0049751c();
    FUN_00497994();
    return v;
}

/* FUN_00468dd4 @ 0x00468dd4   (est. sk_syscall_report_68dd4)
 * Ghidra: void FUN_00468dd4(void)
 * Report/report-commit helper: runs the guarded-entry sequence, dispatches
 * through the object vtable, and finishes with the report helpers
 * (FUN_004687e8) and FUN_00084234.
 * Confidence: low
 * Notes: SUB supervisor calls; register artifacts. */
void FUN_00468dd4(word_t cx8, word_t cx9, word_t cx13, word_t cx16, word_t x30)
{
    cl4_pair_t p;

    FUN_00084220();
    p = FUN_00077888();
    FUN_0007c028(p.lo, p.hi, p.hi);
    SK_SVC_CALL();                      /* arg from (extraout_x8_00+0x40) */
    FUN_000aa4ec();
    FUN_0007c028();
    SK_SVC_CALL();                      /* arg from (extraout_x8_02+0x40) */
    FUN_000aa4ec();
    FUN_004aba28();
    SK_VMETHOD(cx13, 0x10);
    FUN_00350548(*(uint64_t *)(cx16 + 0x10), cx9 - cx8);
    ((code_fn)cx8)();
    FUN_00350618(cx8);
    FUN_0035053c();
    FUN_004687e8();
    FUN_00084234(x30);
    return;
}

/* FUN_00468ee4 @ 0x00468ee4   (est. sk_span_build_68ee4)
 * Ghidra: void FUN_00468ee4(undefined8*,undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Builds a span-index object: allocates a 0x28-byte descriptor, fills its
 * object/array fields from FUN_001a3e10, then builds a parallel index array
 * (via FUN_0001dd14 capacity growth) that maps sorted span entries, copying
 * the seven output words into the caller's struct. Uses SoftwareBreakpoint
 * traps for out-of-range / overflow panics.
 * Confidence: low
 * Notes: growing index array; breakpoints 0x469230-0x469250. */
void FUN_00468ee4(uint64_t *out, word_t p2, word_t p3, word_t p4,
                  word_t p5, word_t p6, word_t p7)
{
    long src;               /* lVar5 */
    long desc;              /* lVar7 */
    uint64_t count, cap;
    uint64_t m90, m88, m80, m78, m70, m68, mb0, ma0;
    long l12, l13, l1, l2, l3, l10;

    src = FUN_001a3e10();
    {
        uint64_t n = FUN_00002534(0x0064c108 + 8, (const void *)0x004c0740);
        desc = FUN_0036a940(n, 0x28, 7);
    }
    desc = desc;    /* data at 0x4baeb0/0x4baeb8 copied into desc+0x10/0x18 */
    *(uint64_t *)(desc + 0x10) = *(uint64_t *)0x004baeb0;
    *(uint64_t *)(desc + 0x18) = *(uint64_t *)0x004baeb8;
    count = *(uint64_t *)(src + 0x10);
    *(uint64_t *)(desc + 0x20) = count;
    if (count > 1) {
        desc = FUN_0001dd14(1, count, 0, desc);
        count = *(uint64_t *)(src + 0x10);
        if (count > 1) {
            ma0 = 0;
            m90 = 0;
            m80 = -1;
            m78 = 0;
            m70 = 1;
            m68 = 0;
            do {
                long gap = (long)m68 - (long)m70;
                if (gap == 0 || (long)m68 < (long)m70) {
                    long sp = src;
                    for (m88 = 0; m68 = m70 + m88, m68 < count; m88 = m88 + 1) {
                        if (*(uint64_t *)(src + 0x10) <= m88) {
                            SK_PANIC("a");      /* 0x469230 */
                        }
                        if (*(uint64_t *)(src + 0x10) <= m68) {
                            SK_PANIC("b");      /* 0x469234 */
                        }
                        if ((*(long *)(sp + 0x20) != *(long *)(sp + m78 + 0x30) ||
                             *(long *)(sp + 0x28) != *(long *)(sp + m78 + 0x38)) &&
                            (FUN_002a0cf8() & 1) == 0) break;
                        sp = sp + 0x10;
                    }
                    mb0 = *(uint64_t *)(desc + 0x10);
                    cap = *(uint64_t *)(desc + 0x18);
                    l13 = mb0 + 1;
                    m90 = m70;
                    if (cap >> 1 <= mb0) {
grow1:
                        m90 = m70;
grow2:
                        desc = FUN_0001dd14(1 < cap, l13, 1, desc);
                    }
                } else {
                    uint64_t u9 = (uint64_t)((long)m70 - (long)m90);
                    if ((long)m70 < (long)m90) {
                        SK_PANIC("c");      /* 0x469244 */
                    }
                    if ((long)u9 < 0) {
                        SK_PANIC("d");      /* 0x469248 */
                    }
                    mb0 = *(uint64_t *)(desc + 0x10);
                    if (mb0 <= u9) {
                        SK_PANIC("e");      /* 0x46924c */
                    }
                    m88 = *(uint64_t *)(desc + u9 * 8 + 0x20);
                    if ((long)m88 < l13) {
                        cap = *(uint64_t *)(desc + 0x18);
                        l13 = mb0 + 1;
                        if (cap >> 1 <= mb0) goto grow2;
                    } else {
                        l2 = (long)m68 + (long)m80;
                        l10 = (long)m68 * 0x10;
                        l1 = (long)m68 * 0x10;
                        l12 = src;
                        for (m68 = m70 + l13; m88 = (uint64_t)((long)m80 + (long)m68),
                            (long)m68 < (long)count; m68 = m68 + 1) {
                            if (l2 < 0) {
                                SK_PANIC("f");  /* 0x469238 */
                            }
                            if (*(uint64_t *)(src + 0x10) <= m88) {
                                SK_PANIC("g");  /* 0x46923c */
                            }
                            if (*(uint64_t *)(src + 0x10) <= m68) {
                                SK_PANIC("h");  /* 0x469240 */
                            }
                            l13 = l12 + ma0 + l1;
                            l3 = l12 + l10;
                            if ((*(long *)(l13 + 0x10) != *(long *)(l3 + 0x20) ||
                                 *(long *)(l13 + 0x18) != *(long *)(l3 + 0x28)) &&
                                (FUN_002a0cf8() & 1) == 0) break;
                            l12 = l12 + 0x10;
                        }
                        cap = *(uint64_t *)(desc + 0x18);
                        l13 = mb0 + 1;
                        m90 = m70;
                        if (cap >> 1 <= mb0) goto grow1;
                    }
                }
                m70 = m70 + 1;
                *(long *)(desc + 0x10) = l13;
                *(uint64_t *)(desc + mb0 * 8 + 0x20) = m88;
                m80 = m80 - 1;
                m78 = m78 + 0x10;
                ma0 = ma0 - 0x10;
            } while (m70 != count);
        }
    }
    out[0] = p4;
    out[1] = p5;
    out[2] = p6;
    out[3] = p7;
    out[4] = src;
    out[5] = desc;
    out[6] = 0x004a4710;    /* method-table pointer (LAB_004a4710) */
    out[7] = 0;
    thunk_FUN_0036b270(p7);
    return;
}

/* FUN_00469250 @ 0x00469250   (est. sk_syscall_report_69250)
 * Ghidra: void FUN_00469250(undefined8,undefined8,undefined8,undefined8,undefined8,undefined8)
 * Six-argument report/commit: marshals the launch image, builds the error
 * object (L4_ErrorCodeArgumentInvalid string at 0x00688728), releases scratch
 * state and commits via FUN_00468dd4/FUN_004974ec.
 * Confidence: low
 * Notes: string s_L4_ErrorCodeArgumentInvalid_00688728; SUB supervisor calls. */
void FUN_00469250(word_t p1, word_t p2, word_t p3, word_t p4,
                  word_t p5, word_t p6)
{
    cl4_pair_t img;         /* auVar5 */
    cl4_pair_t t20;         /* local_20 */
    uint64_t u1, u2, v;
    word_t cx8, cx9, cx12, x30;
    long l3;

    img = FUN_0008e518();
    v = img.hi;
    FUN_0007c028(img.lo, img.lo);
    SK_SVC_CALL();                      /* arg from (extraout_x8_00+0x40) */
    FUN_000aa4ec();
    SK_VMETHOD(cx12, 0x10, (word_t)(cx9 - cx8));
    FUN_00027754(p4);
    img = FUN_004aa5dc();
    u1 = FUN_00377824(img.lo, img.hi, v);
    FUN_00356bb0(p5);
    img = FUN_00350a04();
    u2 = FUN_0019e578(img.lo, img.hi, p3);
    l3 = FUN_0036a940(0x00688728, 0x40, 7);   /* L4_ErrorCodeArgumentInvalid */
    *(uint64_t *)(l3 + 0x10) = v;
    *(uint64_t *)(l3 + 0x18) = p3;
    *(uint64_t *)(l3 + 0x20) = p4;
    *(uint64_t *)(l3 + 0x28) = p5;
    *(uint64_t *)(l3 + 0x30) = p6;
    *(uint64_t *)(l3 + 0x38) = u1;
    FUN_00467de4(u2, 0x004aa278, l3, v, p4);
    t20 = FUN_003517c0();
    {
        word_t t = l3;
        img = FUN_003504e8();
        u2 = FUN_004974ec(img.lo, img.hi, p4);
        FUN_00468dd4(cx8, t20.lo, v, u2, 0x687b40);
    }
    FUN_0036b118(u1);
    FUN_0036b118(p5);
    FUN_0036b118(p6);
    FUN_0008e500(x30);
    return;
}

/* FUN_004693d0 @ 0x004693d0   (est. sk_pair_eq_693d0)
 * Ghidra: undefined8 FUN_004693d0(long,long,long,long)
 * Compares two 128-bit values (lo/hi pairs). Returns 1 when both halves match,
 * otherwise the result of FUN_002a0cf8.
 * Confidence: low
 * Notes: pair equality helper. */
uint64_t FUN_004693d0(long a0, long a1, long b0, long b1)
{
    if (a0 != b0 || a1 != b1) {
        return FUN_002a0cf8();
    }
    return 1;
}

/* FUN_004693ec @ 0x004693ec   (est. sk_syscall_dispatch_693ec)
 * Ghidra: void FUN_004693ec(undefined8,undefined8,long,undefined8,undefined8,undefined8)
 * Large six-argument dispatcher: marshals the launch image and error
 * descriptors, runs the span-search (FUN_00365b6c), and dispatches the
 * matching report through FUN_0046777c / FUN_00469250; releases scratch and
 * reports via FUN_0008e500.
 * Confidence: low
 * Notes: register-carried pointers; SUB supervisor calls; span compare. */
void FUN_004693ec(word_t p1, word_t p2, long p3, word_t p4, word_t p5, word_t p6)
{
    cl4_pair_t img;         /* auVar7 */
    cl4_pair_t t8;          /* auVar8 */
    uint64_t u3, u4, u5, v;
    long l2, l6;
    int cmp;
    word_t cx8, cx9, cx16, x21, x30;
    uint64_t local_c8, local_c0, local_a8, sa0, s80, s70;
    uint64_t local_88;

    img = FUN_0008e518();
    v = img.hi;
    FUN_004974ec(0xff, v, p4);
    FUN_004aa970();
    FUN_00497504();
    FUN_0034ab20();
    FUN_0007c1a4();
    SK_SVC_CALL();
    FUN_0034b0d4();
    t8 = FUN_003504e8();
    FUN_004ac628(t8.lo, t8.hi, p3);
    FUN_000a6f88();
    FUN_0007c1a4();
    SK_SVC_CALL();
    l2 = FUN_0034cff4();
    l2 = (long)*(int *)(l2 + 0x30);
    FUN_0011aa70();
    ((code_fn)cx9)();
    l6 = *(long *)(p3 - 8);
    SK_VMETHOD(l6, 0x10, (word_t)(x21 + l2), img.lo, p3);
    FUN_00465db0();
    cmp = FUN_00365b6c(&local_a8, x21 + l2, p3);
    if (cmp == 0) {
spancall1:
        FUN_004ab1dc();
        cmp = FUN_00365b6c(&local_88, x21 + l2, p3);
        if (cmp == 0) {
spandone:
            img = FUN_00350524();
            FUN_00469250(img.lo, img.hi, p3, p4, p5, p6);
            u3 = FUN_00407ed0();
            v = FUN_00377824(u3, p4, v);
            FUN_00464f4c();
            FUN_003514e8();
            FUN_003522c8();
            FUN_00377bec();
            u3 = FUN_00350c98();
            FUN_00310e08(u3, v);
            v = FUN_0019e578();
            local_c0 = cx16;
            goto finish;
        }
        FUN_004ac85c();
        FUN_004ab9b0();
        FUN_00465db0();
        FUN_003504a0(&local_a8);
        cmp = FUN_00365b6c();
        if (cmp == 0) {
            FUN_004ab1dc();
            FUN_003504a0(&local_a8);
            cmp = FUN_00365b6c();
            img.lo = sa0;
            img.hi = local_a8;
            if (cmp == 0) {
                FUN_003a25d4(s70);
                goto spandone;
            }
        } else {
            FUN_0001d4f4(0xf, local_a8, sa0);
            FUN_003535a8();
            FUN_003a25d4(sa0);
            FUN_000e15d8(s70);
            img = FUN_00351cd0();
        }
    } else {
        FUN_004ac85c();
        FUN_004ab9b0();
        u3 = sa0;
        FUN_00465db0();
        FUN_003504a0(&local_88);
        cmp = FUN_00365b6c();
        if (cmp == 0) {
            FUN_004ab1dc();
            FUN_003504a0(&local_88);
            cmp = FUN_00365b6c();
            if (cmp == 0) {
                FUN_003a25d4(u3);
                l2 = local_c8;
                goto spancall1;
            }
            FUN_00351118(0xf);
            FUN_0001d4f4();
            FUN_003a25d4(u3);
            img = FUN_004ac1bc();
        } else {
            FUN_0001d4f4(0xf, local_88, s80);
            FUN_003a25d4(s80);
            FUN_00351118(0xf);
            FUN_0001d4f4();
            FUN_003a25d4(u3);
            img = FUN_004ac1bc();
        }
    }
    FUN_0046777c(img.lo, img.hi);
    u3 = FUN_0049751c(s70);
    FUN_00497994(s70);
    FUN_004aaf6c();
    u4 = FUN_004aa770();
    FUN_00377824(u4, p4, v, 0x0060e208);
    FUN_00464f4c();
    FUN_0035060c();
    FUN_00352ae4();
    img = FUN_00377bec();
    FUN_0035050c(img.lo, img.hi, img.lo);
    img.lo = FUN_00310e08(); img.hi = 0;
    FUN_003509bc(img.lo, img.hi, img.lo);
    v = FUN_0019dfc4();
    FUN_0036b118(u3);
    SK_VMETHOD(l6, 8, (word_t)(x21 + local_c8), p3);
finish:
    FUN_00084180(*(uint64_t *)(local_c0 + 8));
    ((code_fn)cx8)();
    FUN_0008e500(v, x30);
    return;
}

/* FUN_0046989c @ 0x0046989c   (est. sk_frame_store_6989c)
 * Ghidra: void FUN_0046989c(void)
 * Builds a 0xc0-byte frame: prepares via FUN_00407ab8, fills it through
 * FUN_00469918, memcpys 0x90 bytes, then writes six trailing words from
 * register artifacts into +0x90..+0xb8.
 * Confidence: low
 * Notes: register fragments (in_x5/in_x6, unaff_x21..x25). */
void FUN_0046989c(word_t in_x5, word_t in_x6, word_t x21, word_t x22,
                  word_t x23, word_t x24, word_t x25)
{
    uint8_t frame[0xe0];
    word_t out;

    FUN_0034d090();
    FUN_00407ab8();
    FUN_00469918((uint64_t *)frame);
    FUN_0036b118(in_x6);
    FUN_00117cc4((word_t)frame, (word_t)frame, 0x90);
    *(word_t *)(frame + 0x90) = x25;
    *(word_t *)(frame + 0x98) = x24;
    *(word_t *)(frame + 0xa0) = x23;
    *(word_t *)(frame + 0xa8) = x22;
    *(word_t *)(frame + 0xb0) = x21;
    *(word_t *)(frame + 0xb8) = in_x5;
    return;
}

/* FUN_00469918 @ 0x00469918   (est. sk_kind_decode_69918)
 * Ghidra: void FUN_00469918(undefined8 *param_1)
 * Decodes a kind/descriptor object: allocates an error object (cap-invalid
 * path, s_L4_ErrorCodeCapInvalid string) or copies an existing decode result,
 * then packs the 24-word result into the caller's output buffer. Traps at
 * SoftwareBreakpoint 0x469b40 if the decode kind is unexpected.
 * Confidence: low
 * Notes: source object at callee-saved x20; string
 * s_L4_ErrorCodeCapInvalid_006886c8; big local copy of the packed block. */
static void sk_kind_pack(uint64_t *out, const uint64_t *blk)
{
    /* Pack the decode block into the output buffer, mapping the scattered
     * local fields (lo/hi words + byte flags) to their offsets. */
    out[0]  = blk[0];
    out[1]  = blk[1];
    *(uint8_t *)(out + 2)              = (uint8_t)blk[2];
    *(uint8_t *)((uint8_t *)out + 0x11) = ((uint8_t *)blk)[0x11] & 1;
    *(uint8_t *)((uint8_t *)out + 0x12) = ((uint8_t *)blk)[0x12] & 1;
    out[3]  = blk[3];
    out[4]  = blk[4];
    out[5]  = blk[5];
    *(uint8_t *)((uint8_t *)out + 0x30) = ((uint8_t *)blk)[0x30] & 1;
    out[7]  = blk[7];
    out[8]  = blk[8];
    out[9]  = blk[9];
    out[10] = blk[10];
    out[11] = blk[11];
    out[12] = blk[12];
    *(uint8_t *)((uint8_t *)out + 0x68) = ((uint8_t *)blk)[0x68] & 1;
    out[14] = blk[14];
    out[15] = blk[15];
    out[16] = blk[16];
    out[17] = blk[17];
}

void FUN_00469918(uint64_t *out)
{
    word_t base;            /* lVar7 = *unaff_x20 */
    long desc;              /* lVar5 */
    uint64_t u1, v2;
    int kind;               /* iVar4 */
    uint64_t r[24];
    uint64_t q[24];

    base = *(word_t *)0;    /* *unaff_x20 (source object head) */
    FUN_00491914((word_t)r);
    kind = FUN_0033e448((word_t)r);
    if (kind == 1) {
        u1 = *(uint64_t *)(0 + 0x18);
        v2 = *(uint64_t *)(0 + 0x20);
        FUN_00359018(0x657c78);
        desc = FUN_0036a940();
        *(uint64_t *)(desc + 0x10) = u1;
        *(char **)(desc + 0x18) = (char *)0x006886c8;   /* L4_ErrorCodeCapInvalid */
        *(long *)(desc + 0x20) = v2;
        FUN_0036b270(u1 & 0xffffffffffffffbULL);
        FUN_0047d358((word_t)&r[0]);
        FUN_0049d248(0, *(uint64_t *)(base + 0x38));
        {
            long rr = FUN_004918ac((word_t)&r[0]);
            FUN_004a4ab4((word_t)&r[0], (word_t)&q[0]);
            FUN_0036b270(rr);
            if (*(uint64_t *)0 == 0) {
                *(uint64_t *)0 = rr;
                FUN_0036b118(rr);
                sk_kind_pack(out, r);
            } else {
                FUN_004974c4((word_t)&r[0]);
                FUN_0036b340(rr, 2);
                FUN_00491914((word_t)&q[0]);
                kind = FUN_0033e448((word_t)&q[0]);
                if (kind == 1) {
                    SK_PANIC("kind");   /* breakpoint 0x469b40 */
                }
                sk_kind_pack(out, q);
            }
        }
    } else {
        sk_kind_pack(out, r);
    }
    return;
}
