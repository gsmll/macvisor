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

/* 0x0035xxxx dispatch/error handlers. */
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
extern void *FUN_0036a940();                         /* zone/obj alloc (size,count,tag) */
extern void *FUN_0036b270();                         /* sk_alloc / refcount acquire */
extern void  FUN_0036b118();                         /* sk_free / refcount release */
extern void  FUN_0036b340();                         /* refcount link */
extern void  FUN_0036b588();                         /* sk_alloc_link */
extern void  FUN_003a25d4();                         /* object release (tightbeam) */
extern void  FUN_003a261c();                         /* object release 2 (tightbeam) */
extern void  FUN_0001d4f4();                         /* error-frame build */
extern unsigned long FUN_0001dd14();                 /* grow/ensure-capacity */
extern void  FUN_0019dfc4();                         /* cap/name lookup */
extern unsigned long FUN_0019e578();                 /* sk_swift_helper */
extern void  FUN_001b58b0();
extern void  FUN_001b9084();
extern void  FUN_001d88fc();
extern void  FUN_001d9890();
extern unsigned long FUN_001a3e10();                 /* container head */

/* Kernel / arch primitives. */
extern void  FUN_00002534();                         /* diag/boot name ref */
extern void  FUN_00117cc4();                         /* sk_memcpy */
extern void  FUN_00100c38();
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
extern void FUN_0046ea44();
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
typedef void (*code_fn)();
#define SK_VMETHOD(obj, off, ...) \
    (((code_fn)(*(void **)((char *)(obj) + (off))))(__VA_ARGS__))

/* ================================================================== *
 * SKR26 function bodies (address order)
 * ================================================================== */

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
