/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel, GL1,
 * arm64e, image base 0) — the cL4 microkernel. Ground truth: Ghidra FUN_ names +
 * addresses in cl4_kernel.raw. Version "cL4 microkernel (cL4 (679.100.61))".
 * All names are estimates unless string/header-matched.
 * Slice 0x404ac0-0x41d788 (SKR62): the cL4 IPC/message-register (MR) layer.
 * This region implements the syscall message encoding/decoding path: the
 * syscall frame is a 0x50-byte struct (the seL4 message-info word plus up to
 * nine message register words at +0x20..+0x48), and the 3-bit message "tag"
 * at +0x50 (+0x28 for the nested form) selects the operation. Decoding of the
 * badge/cap right, the invocations (Send/Recv/Call/Reply/NBSendRecv/
 * NBSendWait etc.), and the TCB cap validity checks live here, alongside the
 * general "decode a cap pointer / check badge against an object" helpers used
 * by the fault and error paths.
 *
 * The top 3 bits of a syscall-word (>> 0x3d) select the cap-table type
 * ("object type" 0..5); the >> 0xe shifts are the seL4 cap-pointer
 * (index/depth in low 14 bits) reductions used to fetch the object behind a
 * capability. The 0xa000000000000000 / 0x8000000000000000 high words are the
 * cL4 "null-cap"/"matching-cap" sentinels used throughout IPC cap matching.
 * Ghidra FUN_ names are kept only in comments.
 *
 * Calling-convention notes: many functions read their arguments from a
 * preserved register (unaff_x19/unaff_x20) that the caller placed on a
 * 0x50-byte frame, so the register fragment locals are reconstructed as a
 * struct. The out-of-range callees are declared extern below (sk_x_*).
 */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "sk_internal.h"

typedef uint64_t word_t;
typedef int64_t  sword_t;
typedef unsigned char byte;
typedef unsigned int uint;

/* 16-byte value returned in x0/x1 by many cL4 helpers. */
typedef struct { unsigned long lo, hi; } cl4_pair_t;

#define CL4_SW_BP(addr)  __asm__ volatile("brk #1" ::: "memory")

/* ---- Out-of-range cL4 helpers referenced by this region (FUN_ in comment).
 * Declared with unspecified-argument prototype (matching slice conventions);
 * their bodies are reconstructed by the range worker that owns them. ---- */
extern cl4_pair_t sk_x_00002534();   /* FUN_00002534 */
extern unsigned long sk_x_00002818();   /* FUN_00002818 */
extern unsigned long sk_x_00002874();   /* FUN_00002874 */
extern cl4_pair_t sk_x_0001a1c8();   /* FUN_0001a1c8 */
extern unsigned long sk_x_00021480();   /* FUN_00021480 */
extern unsigned long sk_x_0006a374();   /* FUN_0006a374 */
extern unsigned long sk_x_0006b42c();   /* FUN_0006b42c */
extern unsigned long sk_x_0006b6a0();   /* FUN_0006b6a0 */
extern unsigned long sk_x_0006e064();   /* FUN_0006e064 */
extern unsigned long sk_x_000722b0();   /* FUN_000722b0 */
extern cl4_pair_t sk_x_00077888();   /* FUN_00077888 */
extern unsigned long sk_x_00077894();   /* FUN_00077894 */
extern unsigned long sk_x_000839d8();   /* FUN_000839d8 */
extern cl4_pair_t sk_x_00084220();   /* FUN_00084220 */
extern unsigned long sk_x_00084234();   /* FUN_00084234 */
extern unsigned long sk_x_0008e500();   /* FUN_0008e500 */
extern cl4_pair_t sk_x_0008e518();   /* FUN_0008e518 */
extern unsigned long sk_x_0009461c();   /* FUN_0009461c */
extern unsigned long sk_x_000a6e14();   /* FUN_000a6e14 */
extern unsigned long sk_x_000a6fe0();   /* FUN_000a6fe0 */
extern cl4_pair_t sk_x_000b4390();   /* FUN_000b4390 */
extern cl4_pair_t sk_x_000b43d0();   /* FUN_000b43d0 */
extern unsigned long sk_x_000b43e8();   /* FUN_000b43e8 */
extern cl4_pair_t sk_x_000b4594();   /* FUN_000b4594 */
extern unsigned long sk_x_000b45b0();   /* FUN_000b45b0 */
extern unsigned long sk_x_000bd3a4();   /* FUN_000bd3a4 */
extern cl4_pair_t sk_x_000dbd0c();   /* FUN_000dbd0c */
extern unsigned long sk_x_00100c04();   /* FUN_00100c04 */
extern unsigned long sk_x_00100e34();   /* FUN_00100e34 */
extern unsigned long sk_x_00100efc();   /* FUN_00100efc */
extern unsigned long sk_x_00117cc4();   /* FUN_00117cc4 */
extern unsigned long sk_x_001a29a0();   /* FUN_001a29a0 */
extern unsigned long sk_x_001a6a8c();   /* FUN_001a6a8c */
extern unsigned long sk_x_001a84f4();   /* FUN_001a84f4 */
extern unsigned long sk_x_001a8564();   /* FUN_001a8564 */
extern unsigned long sk_x_001afa84();   /* FUN_001afa84 */
extern unsigned long sk_x_001afe4c();   /* FUN_001afe4c */
extern unsigned long sk_x_001b9084();   /* FUN_001b9084 */
extern unsigned long sk_x_001bb7a0();   /* FUN_001bb7a0 */
extern unsigned long sk_x_001bc440();   /* FUN_001bc440 */
extern unsigned long sk_x_001ed960();   /* FUN_001ed960 */
extern cl4_pair_t sk_x_00205844();   /* FUN_00205844 */
extern unsigned long sk_x_002298d4();   /* FUN_002298d4 */
extern unsigned long sk_x_00229a3c();   /* FUN_00229a3c */
extern unsigned long sk_x_0025177c();   /* FUN_0025177c */
extern unsigned long sk_x_00268540();   /* FUN_00268540 */
extern unsigned long sk_x_00270d80();   /* FUN_00270d80 */
extern unsigned long sk_x_0028e8fc();   /* FUN_0028e8fc */
extern unsigned long sk_x_002a0cf8();   /* FUN_002a0cf8 */
extern unsigned long sk_x_002a4ab4();   /* FUN_002a4ab4 */
extern unsigned long sk_x_002acbb8();   /* FUN_002acbb8 */
extern unsigned long sk_x_002ad78c();   /* FUN_002ad78c */
extern unsigned long sk_x_002cb61c();   /* FUN_002cb61c */
extern unsigned long sk_x_0031b37c();   /* FUN_0031b37c */
extern unsigned long sk_x_0031de7c();   /* FUN_0031de7c */
extern unsigned long sk_x_0031e5c8();   /* FUN_0031e5c8 */
extern cl4_pair_t sk_x_003207d4();   /* FUN_003207d4 */
extern unsigned long sk_x_00347da8();   /* FUN_00347da8 */
extern unsigned long sk_x_00349a18();   /* FUN_00349a18 */
extern unsigned long sk_x_0034b7e4();   /* FUN_0034b7e4 */
extern unsigned long sk_x_0034ba48();   /* FUN_0034ba48 */
extern unsigned long sk_x_0034bb84();   /* FUN_0034bb84 */
extern unsigned long sk_x_0034c444();   /* FUN_0034c444 */
extern unsigned long sk_x_0034d868();   /* FUN_0034d868 */
extern unsigned long sk_x_00350470();   /* FUN_00350470 */
extern unsigned long sk_x_003504b8();   /* FUN_003504b8 */
extern unsigned long sk_x_003504c4();   /* FUN_003504c4 */
extern cl4_pair_t sk_x_003504d0();   /* FUN_003504d0 */
extern unsigned long sk_x_00350500();   /* FUN_00350500 */
extern cl4_pair_t sk_x_00350518();   /* FUN_00350518 */
extern unsigned long sk_x_0035053c();   /* FUN_0035053c */
extern unsigned long sk_x_003505c4();   /* FUN_003505c4 */
extern unsigned long sk_x_003505e8();   /* FUN_003505e8 */
extern unsigned long sk_x_00350618();   /* FUN_00350618 */
extern unsigned long sk_x_00350624();   /* FUN_00350624 */
extern unsigned long sk_x_00350738();   /* FUN_00350738 */
extern unsigned long sk_x_00350744();   /* FUN_00350744 */
extern unsigned long sk_x_003507e0();   /* FUN_003507e0 */
extern unsigned long sk_x_00350980();   /* FUN_00350980 */
extern unsigned long sk_x_0035098c();   /* FUN_0035098c */
extern unsigned long sk_x_003509c8();   /* FUN_003509c8 */
extern unsigned long sk_x_003509ec();   /* FUN_003509ec */
extern unsigned long sk_x_00350a04();   /* FUN_00350a04 */
extern unsigned long sk_x_00350b18();   /* FUN_00350b18 */
extern unsigned long sk_x_00350b54();   /* FUN_00350b54 */
extern unsigned long sk_x_00350c5c();   /* FUN_00350c5c */
extern unsigned long sk_x_003511f0();   /* FUN_003511f0 */
extern unsigned long sk_x_003514e8();   /* FUN_003514e8 */
extern unsigned long sk_x_003515b4();   /* FUN_003515b4 */
extern unsigned long sk_x_00351790();   /* FUN_00351790 */
extern unsigned long sk_x_00351aec();   /* FUN_00351aec */
extern unsigned long sk_x_00351b78();   /* FUN_00351b78 */
extern unsigned long sk_x_00351d30();   /* FUN_00351d30 */
extern cl4_pair_t sk_x_00351da8();   /* FUN_00351da8 */
extern unsigned long sk_x_00351db4();   /* FUN_00351db4 */
extern unsigned long sk_x_00351dc0();   /* FUN_00351dc0 */
extern cl4_pair_t sk_x_00351e20();   /* FUN_00351e20 */
extern unsigned long sk_x_003523fc();   /* FUN_003523fc */
extern unsigned long sk_x_00353bc4();   /* FUN_00353bc4 */
extern unsigned long sk_x_003544c8();   /* FUN_003544c8 */
extern unsigned long sk_x_00354744();   /* FUN_00354744 */
extern unsigned long sk_x_00354828();   /* FUN_00354828 */
extern unsigned long sk_x_003552a0();   /* FUN_003552a0 */
extern unsigned long sk_x_003567c8();   /* FUN_003567c8 */
extern unsigned long sk_x_00356c6c();   /* FUN_00356c6c */
extern cl4_pair_t sk_x_0035860c();   /* FUN_0035860c */
extern unsigned long sk_x_00359024();   /* FUN_00359024 */
extern unsigned long sk_x_003593c0();   /* FUN_003593c0 */
extern unsigned long sk_x_0036a940();   /* FUN_0036a940 */
extern unsigned long sk_x_0036b118();   /* FUN_0036b118 */
extern cl4_pair_t sk_x_0036b270();   /* FUN_0036b270 */
extern unsigned long sk_x_003722e4();   /* FUN_003722e4 */
extern unsigned long sk_x_00376820();   /* FUN_00376820 */
extern unsigned long sk_x_003a25d4();   /* FUN_003a25d4 */
extern unsigned long sk_x_003f406c();   /* FUN_003f406c */
extern unsigned long sk_x_003f540c();   /* FUN_003f540c */
extern unsigned long sk_x_003f55a0();   /* FUN_003f55a0 */
extern unsigned long sk_x_003f5998();   /* FUN_003f5998 */
extern unsigned long sk_x_003f5ad4();   /* FUN_003f5ad4 */
extern unsigned long sk_x_003f5c00();   /* FUN_003f5c00 */
extern unsigned long sk_x_003f5c54();   /* FUN_003f5c54 */
extern unsigned long sk_x_003f5c64();   /* FUN_003f5c64 */
extern unsigned long sk_x_003f5cc4();   /* FUN_003f5cc4 */
extern unsigned long sk_x_003f5cf0();   /* FUN_003f5cf0 */
extern unsigned long sk_x_003f5e68();   /* FUN_003f5e68 */
extern unsigned long sk_x_003f5e78();   /* FUN_003f5e78 */
extern unsigned long sk_x_003f5ee8();   /* FUN_003f5ee8 */
extern unsigned long sk_x_003f60e4();   /* FUN_003f60e4 */
extern unsigned long sk_x_003f6278();   /* FUN_003f6278 */
extern unsigned long sk_x_003f6560();   /* FUN_003f6560 */
extern unsigned long sk_x_003f6e08();   /* FUN_003f6e08 */
extern unsigned long sk_x_003f6ea8();   /* FUN_003f6ea8 */
extern unsigned long sk_x_003f6f3c();   /* FUN_003f6f3c */
extern unsigned long sk_x_003f6fec();   /* FUN_003f6fec */
extern unsigned long sk_x_003f709c();   /* FUN_003f709c */
extern unsigned long sk_x_003f70f8();   /* FUN_003f70f8 */
extern cl4_pair_t sk_x_003f7b44();   /* FUN_003f7b44 */
extern unsigned long sk_x_003f7d48();   /* FUN_003f7d48 */
extern unsigned long sk_x_003f7e8c();   /* FUN_003f7e8c */
extern unsigned long sk_x_003f8264();   /* FUN_003f8264 */
extern unsigned long sk_x_003f8f60();   /* FUN_003f8f60 */
extern unsigned long sk_x_003f9234();   /* FUN_003f9234 */
extern unsigned long sk_x_00406310();   /* FUN_00406310 */
extern unsigned long sk_x_0040633c();   /* FUN_0040633c */
extern unsigned long sk_x_004063f4();   /* FUN_004063f4 */
extern unsigned long sk_x_004064f8();   /* FUN_004064f8 */
extern unsigned long sk_x_0040668c();   /* FUN_0040668c */
extern unsigned long sk_x_004066a4();   /* FUN_004066a4 */
extern unsigned long sk_x_0040695c();   /* FUN_0040695c */
extern unsigned long sk_x_004070cc();   /* FUN_004070cc */
extern unsigned long sk_x_00407170();   /* FUN_00407170 */
extern unsigned long sk_x_00407324();   /* FUN_00407324 */
extern unsigned long sk_x_00407894();   /* FUN_00407894 */
extern unsigned long sk_x_00407d24();   /* FUN_00407d24 */
extern unsigned long sk_x_00407d44();   /* FUN_00407d44 */
extern unsigned long sk_x_00407e20();   /* FUN_00407e20 */
extern unsigned long sk_x_004080b0();   /* FUN_004080b0 */
extern unsigned long sk_x_00408238();   /* FUN_00408238 */
extern unsigned long sk_x_004082d4();   /* FUN_004082d4 */
extern unsigned long sk_x_004084e8();   /* FUN_004084e8 */
extern unsigned long sk_x_00408524();   /* FUN_00408524 */
extern unsigned long sk_x_0041001c();   /* FUN_0041001c */
extern unsigned long sk_x_00410414();   /* FUN_00410414 */
extern unsigned long sk_x_00411290();   /* FUN_00411290 */
extern unsigned long sk_x_00411308();   /* FUN_00411308 */
extern unsigned long sk_x_004114fc();   /* FUN_004114fc */
extern unsigned long sk_x_00448fd0();   /* FUN_00448fd0 */
extern unsigned long sk_x_0044929c();   /* FUN_0044929c */
extern cl4_pair_t sk_x_0044bd08();   /* FUN_0044bd08 */
extern unsigned long sk_x_0044ca60();   /* FUN_0044ca60 */
extern unsigned long sk_x_00455f60();   /* FUN_00455f60 */
extern unsigned long sk_x_0045636c();   /* FUN_0045636c */
extern unsigned long sk_x_00456858();   /* FUN_00456858 */
extern unsigned long sk_x_004578dc();   /* FUN_004578dc */
extern unsigned long sk_x_00457994();   /* FUN_00457994 */
extern unsigned long sk_x_0045811c();   /* FUN_0045811c */
extern unsigned long sk_x_00458278();   /* FUN_00458278 */
extern unsigned long sk_x_00458c98();   /* FUN_00458c98 */
extern unsigned long sk_x_00458cb8();   /* FUN_00458cb8 */
extern unsigned long sk_x_00458cd4();   /* FUN_00458cd4 */
extern unsigned long sk_x_00458d68();   /* FUN_00458d68 */
extern unsigned long sk_x_00458d78();   /* FUN_00458d78 */
extern unsigned long sk_x_00458da0();   /* FUN_00458da0 */
extern unsigned long sk_x_00458e28();   /* FUN_00458e28 */
extern unsigned long sk_x_00458e80();   /* FUN_00458e80 */
extern unsigned long sk_x_0045908c();   /* FUN_0045908c */
extern unsigned long sk_x_004590e0();   /* FUN_004590e0 */
extern unsigned long sk_x_00460d94();   /* FUN_00460d94 */
extern unsigned long sk_x_0046134c();   /* FUN_0046134c */
extern unsigned long sk_x_004613d4();   /* FUN_004613d4 */
extern unsigned long sk_x_00462728();   /* FUN_00462728 */
extern unsigned long sk_x_00462898();   /* FUN_00462898 */
extern unsigned long sk_x_0046299c();   /* FUN_0046299c */
extern unsigned long sk_x_00462b6c();   /* FUN_00462b6c */
extern unsigned long sk_x_00462d5c();   /* FUN_00462d5c */
extern unsigned long sk_x_00462e0c();   /* FUN_00462e0c */
extern unsigned long sk_x_00463210();   /* FUN_00463210 */
extern unsigned long sk_x_004632a4();   /* FUN_004632a4 */
extern unsigned long sk_x_004632f4();   /* FUN_004632f4 */
extern unsigned long sk_x_004633f4();   /* FUN_004633f4 */
extern unsigned long sk_x_00463558();   /* FUN_00463558 */
extern unsigned long sk_x_00463600();   /* FUN_00463600 */
extern unsigned long sk_x_00463708();   /* FUN_00463708 */
extern unsigned long sk_x_004637b4();   /* FUN_004637b4 */
extern unsigned long sk_x_004637dc();   /* FUN_004637dc */
extern unsigned long sk_x_00463878();   /* FUN_00463878 */
extern unsigned long sk_x_00463998();   /* FUN_00463998 */
extern unsigned long sk_x_00463ab8();   /* FUN_00463ab8 */
extern unsigned long sk_x_00463af8();   /* FUN_00463af8 */
extern unsigned long sk_x_00463dc8();   /* FUN_00463dc8 */
extern unsigned long sk_x_00463df8();   /* FUN_00463df8 */
extern cl4_pair_t sk_x_00463e04();   /* FUN_00463e04 */
extern unsigned long sk_x_00464308();   /* FUN_00464308 */
extern unsigned long sk_x_004643cc();   /* FUN_004643cc */
extern unsigned long sk_x_004644e8();   /* FUN_004644e8 */
extern unsigned long sk_x_004645ec();   /* FUN_004645ec */
extern unsigned long sk_x_004647b4();   /* FUN_004647b4 */
extern unsigned long sk_x_004648fc();   /* FUN_004648fc */
extern unsigned long sk_x_00464a08();   /* FUN_00464a08 */
extern unsigned long sk_x_00464a38();   /* FUN_00464a38 */
extern unsigned long sk_x_00464a44();   /* FUN_00464a44 */
extern unsigned long sk_x_00464ad0();   /* FUN_00464ad0 */
extern unsigned long sk_x_00464d0c();   /* FUN_00464d0c */
extern unsigned long sk_x_00464d68();   /* FUN_00464d68 */
extern unsigned long sk_x_00464e1c();   /* FUN_00464e1c */
extern unsigned long sk_x_00464eb0();   /* FUN_00464eb0 */
extern unsigned long sk_x_00464f58();   /* FUN_00464f58 */
extern unsigned long sk_x_004650e4();   /* FUN_004650e4 */
extern unsigned long sk_x_004651a8();   /* FUN_004651a8 */
extern unsigned long sk_x_00465234();   /* FUN_00465234 */
extern unsigned long sk_x_00465240();   /* FUN_00465240 */
extern unsigned long sk_x_00465264();   /* FUN_00465264 */
extern unsigned long sk_x_004652a0();   /* FUN_004652a0 */
extern unsigned long sk_x_004652f4();   /* FUN_004652f4 */
extern unsigned long sk_x_004653c0();   /* FUN_004653c0 */
extern unsigned long sk_x_00465488();   /* FUN_00465488 */
extern unsigned long sk_x_00465800();   /* FUN_00465800 */
extern unsigned long sk_x_00465884();   /* FUN_00465884 */
extern unsigned long sk_x_004658a8();   /* FUN_004658a8 */
extern unsigned long sk_x_00465944();   /* FUN_00465944 */
extern unsigned long sk_x_00465968();   /* FUN_00465968 */
extern unsigned long sk_x_00465a14();   /* FUN_00465a14 */
extern unsigned long sk_x_00465b58();   /* FUN_00465b58 */
extern unsigned long sk_x_00465c5c();   /* FUN_00465c5c */
extern unsigned long sk_x_00465c74();   /* FUN_00465c74 */
extern unsigned long sk_x_00465d1c();   /* FUN_00465d1c */
extern unsigned long sk_x_00465d3c();   /* FUN_00465d3c */
extern unsigned long sk_x_00465db0();   /* FUN_00465db0 */
extern unsigned long sk_x_00465fb4();   /* FUN_00465fb4 */
extern unsigned long sk_x_00465fe0();   /* FUN_00465fe0 */
extern unsigned long sk_x_0046622c();   /* FUN_0046622c */
extern cl4_pair_t sk_x_0046647c();   /* FUN_0046647c */
extern unsigned long sk_x_00466528();   /* FUN_00466528 */
extern cl4_pair_t sk_x_00466568();   /* FUN_00466568 */
extern unsigned long sk_x_00466580();   /* FUN_00466580 */
extern unsigned long sk_x_00466660();   /* FUN_00466660 */
extern unsigned long sk_x_004666e4();   /* FUN_004666e4 */
extern unsigned long sk_x_004666f8();   /* FUN_004666f8 */
extern unsigned long sk_x_0067f9a0();   /* FUN_0067f9a0 */

/* ---- Global data slots referenced by this region ---- */
extern word_t DAT_00658c80;   /* global Swift dispatch slot */
extern word_t DAT_00657778;   /* global object pointer (opaque) */
extern word_t _DAT_004be5e0;  /* global (overlapping-underscore) word */
extern word_t _DAT_005a1820;  /* global (overlapping-underscore) word */
extern word_t DAT_004e80a0;   /* descriptor template */
extern word_t DAT_005a3520;   /* string/data template */

/* ---- Forward declarations (cross-referenced within this slice) ---- */
static void sk_r62_00404e60(word_t a, word_t b, sword_t *out);
static void sk_mr_hook_cb_0040548c(sword_t p1, word_t p2);
static uint sk_ipc_match_tag1_0041a9e4(void);
static void sk_ipc_badge_emit_tag1_0041aab4(void);
static word_t sk_ipc_match_tag2_0041ae14(void);
static void sk_ipc_badge_emit_tag2_0041aee4(void);
static uint sk_ipc_badge_match_0041a0dc(sword_t *p1, sword_t *p2);
static void sk_ipc_obj_release_0041c2e4(word_t p1, word_t p2, word_t p3, sword_t p4, byte p5);
static void sk_ipc_encode_payload_0041d180(word_t p1, word_t p2, sword_t p3, word_t p4,
                                          uint p5, word_t p6, word_t p7, sword_t *p8);
static void sk_ipc_emit_reset_0041d14c(byte val, sword_t idx, sword_t base, sword_t end);
static void sk_ipc_frame_emit_slot_0041d4a4(sword_t p1, sword_t p2, sword_t p3, sword_t p4, char p5);
/* FUN_00404ac0 @ 0x00404ac0   (est. sk_mr_syscall_dispatch)
 * Ghidra: void FUN_00404ac0(undefined8,undefined8,undefined8*,undefined8,undefined8)
 * Top-level syscall dispatcher. Fetches the caller frame via 00351da8,
 * forwards the badge/cap and register words through the dispatch slot
 * DAT_00658c80, then walks the register window with the run-reduction helper.
 * Confidence: low (heavy indirect dispatch).
 * Notes: DAT_00658c80 global dispatch slot; SoftwareBreakpoint(1) overflow. */
static void sk_mr_syscall_dispatch_00404ac0(word_t b, word_t c, word_t *frame,
                                            word_t d, word_t e)
{
    cl4_pair_t v = sk_x_00351da8();
    sk_x_0034b7e4(v.hi, v.lo, v.lo);
    (*(word_t (**)(void))DAT_00658c80)();
    sk_x_003f5c00(*frame, 0, 0, e);
    sk_x_00407d44();
    sk_x_00350624((word_t)-16 - ((word_t)&b + 0xf & ~0xf));
    (*(word_t (**)(void))sk_x_00350624)();   /* indirect dispatch (extraout_x9) */
    sk_x_003504c4(*(word_t *)((word_t)0 + 0x20));
    (*(word_t (**)(void))sk_x_003504c4)();   /* indirect dispatch (extraout_x8) */
}

/* FUN_00404b8c @ 0x00404b8c   (est. sk_r62_00404b8c)
 * Ghidra: void FUN_00404b8c(void)
 * Thin wrapper; forwards to 00021480.
 * Confidence: high (trivial). */
static void sk_r62_00404b8c(void)
{
    sk_x_00021480();
}

/* FUN_00404ba4 @ 0x00404ba4   (est. sk_mr_dispatch_a)
 * Ghidra: void FUN_00404ba4(void)
 * Register-frame dispatch helper: reads two frame words, marshals them
 * through 003f5c00/003509c8 and invokes the dispatch slot at +0x10.
 * Confidence: low. */
static void sk_mr_dispatch_a_00404ba4(void)
{
    sk_x_00407170();
    word_t u1 = *(word_t *)((word_t)0 + 0x10);
    word_t u2 = sk_x_003f5c00(*(word_t *)((word_t)0 + 0x18));
    sk_x_003509c8(u1, u2, u2);
    (*(word_t (**)(word_t, word_t, word_t))((word_t)0 + 0x10))(0, 0, u1);
}

/* FUN_00404c08 @ 0x00404c08   (est. sk_mr_update_hint)
 * Ghidra: void FUN_00404c08(void)
 * Updates a hint/version word: if the current generation (from 003f5e68)
 * differs from the stored one, records it and flags change; else clears the
 * flag byte.
 * Confidence: medium. */
static void sk_mr_update_hint_00404c08(void)
{
    sk_x_0035860c();
    word_t slot = *(word_t *)((word_t)0 + 0x18);
    sword_t gen = (sword_t)sk_x_003f5e68();
    byte flag;
    if (gen == 0 || gen == *(sword_t *)(slot + 8)) {
        flag = 0;
    } else {
        *(word_t *)(slot + 8) = 0;
        *(sword_t *)(slot + 0x10) = gen;
        flag = 1;
    }
    *(byte *)((word_t)0 + 0x10) = flag;
}

/* FUN_00404c60 @ 0x00404c60   (est. sk_r62_00404c60)
 * Ghidra: void FUN_00404c60(void)
 * Thin wrapper to 00404e60.
 * Confidence: high (trivial). */
static void sk_r62_00404c60(void)
{
    sk_r62_00404e60(0, 0, 0);
}

/* FUN_00404c78 @ 0x00404c78   (est. sk_mr_span_read)
 * Ghidra: void FUN_00404c78(undefined8*,long)
 * Computes a message-register span {base,offset,length} bounded by the
 * available register count; retains the base object.
 * Confidence: medium.
 * Notes: FUN_0040633c + noreturn 001afa84 on overflow. */
static void sk_mr_span_read_00404c78(word_t *out, sword_t off)
{
    word_t len = *(word_t *)(off + 0x10);
    word_t end = *(sword_t *)(off + 8) + len;
    if ((sword_t)end < 0) {
        sk_x_0040633c();
        sk_x_001afa84();   /* does not return */
    }
    word_t base = *(word_t *)((word_t)0 + 0x18);
    word_t cap = sk_x_003f5cf0();
    if (end <= cap) {
        cap = end;
    }
    out[0] = base;
    out[1] = len;
    out[2] = cap;
    sk_x_0036b270(base);
}

/* FUN_00404cf4 @ 0x00404cf4   (est. sk_r62_00404cf4)
 * Ghidra: void FUN_00404cf4(void)
 * Thin wrapper to 00021480.
 * Confidence: high (trivial). */
static void sk_r62_00404cf4(void)
{
    sk_x_00021480();
}

/* FUN_00404d0c @ 0x00404d0c   (est. sk_r62_00404d0c)
 * Ghidra: void FUN_00404d0c(void)
 * Thin wrapper to 00021480.
 * Confidence: high (trivial). */
static void sk_r62_00404d0c(void)
{
    sk_x_00021480();
}

/* FUN_00404d24 @ 0x00404d24   (est. sk_mr_call_args_a)
 * Ghidra: void FUN_00404d24(undefined8,undefined8,undefined8)
 * Call-args marshaller: forwards frame words to 003f5ad4 and returns to the
 * common epilogue 004082d4.
 * Confidence: low. */
static void sk_mr_call_args_a_00404d24(word_t a, word_t b, word_t c)
{
    sk_x_00407170();
    sk_x_003f5ad4(*(word_t *)((word_t)0 + 0x18), 0, c, *(word_t *)((word_t)0 + 0x10));
    sk_x_004082d4();
}

/* FUN_00404d54 @ 0x00404d54   (est. sk_mr_call_args_b)
 * Ghidra: void FUN_00404d54(undefined8,undefined8,undefined8)
 * Call-args marshaller: forwards frame words to 003f5998 and epilogue.
 * Confidence: low. */
static void sk_mr_call_args_b_00404d54(word_t a, word_t b, word_t c)
{
    sk_x_00407170();
    sk_x_003f5998(*(word_t *)((word_t)0 + 0x18), 0, c, *(word_t *)((word_t)0 + 0x10));
    sk_x_004082d4();
}

/* FUN_00404d84 @ 0x00404d84   (est. sk_mr_emit_word)
 * Ghidra: void FUN_00404d84(void)
 * Emits a message word through 003f55a0 then the common epilogue.
 * Confidence: low. */
static void sk_mr_emit_word_00404d84(void)
{
    cl4_pair_t v = sk_x_0035860c();
    sk_x_003f55a0(v.lo, v.hi, *(word_t *)((word_t)0 + 0x10));
    sk_x_004082d4();
}

/* FUN_00404dc8 @ 0x00404dc8   (est. sk_mr_emit_words)
 * Ghidra: void FUN_00404dc8(void)
 * Emits a run of message words: builds the span via 003f5ee8, writes it with
 * 004064f8, then, if the frame still has words (local_48 != 1), emits the
 * remaining batch. Faithful to the two-step emit loop.
 * Confidence: medium. */
static void sk_mr_emit_words_00404dc8(void)
{
    word_t slot = *(word_t *)((word_t)0 + 0x18);
    word_t a, b;
    sk_x_003f5ee8(&a, slot, *(word_t *)((word_t)0 + 0x20), *(word_t *)((word_t)0 + 0x10));
    sk_x_004064f8(*(word_t *)(slot + 0x10), a, b);
    sk_x_00407894();
    word_t u = sk_x_003f6278();
    if (*(byte *)((word_t)0 + 0x10) != 1) {
        word_t c, d;
        sk_x_004064f8(u, c, d);
        sk_x_00407894(0);
        sk_x_003f6278();
    }
}
/* FUN_00404e60 @ 0x00404e60   (est. sk_r62_00404e60)
 * Ghidra: void FUN_00404e60(undefined8,undefined8,long*)
 * Invokes the dispatch slot at +0x20; if a result register is set, stores it.
 * Confidence: low. */
static void sk_r62_00404e60(word_t a, word_t b, sword_t *out)
{
    (*(word_t (**)(void))((word_t)0 + 0x20))();
    if ((word_t)0 + 0x10 != 0) {
        *out = (sword_t)((word_t)0 + 0x10);
    }
}

/* FUN_00404e98 @ 0x00404e98   (est. sk_mr_span_zero)
 * Ghidra: void FUN_00404e98(void)
 * Builds an empty message span {0, frame+0x10, 0}.
 * Confidence: medium. */
static void sk_mr_span_zero_00404e98(void)
{
    sk_x_0035860c();
    word_t u2 = *(word_t *)((word_t)0 + 0x10);
    word_t u1 = sk_x_0025177c();
    ((word_t *)((word_t)0 + 0x10))[0] = u1;
    ((word_t *)((word_t)0 + 0x10))[1] = u2;
    ((word_t *)((word_t)0 + 0x10))[2] = 0;
}

/* FUN_00404ed8 @ 0x00404ed8   (est. sk_mr_emit_span)
 * Ghidra: void FUN_00404ed8(void)
 * Emits a bounded span: builds it via 003f60e4, writes with 0040695c, then
 * re-emits the tail if words remain.
 * Confidence: medium. */
static void sk_mr_emit_span_00404ed8(void)
{
    word_t u, a, b;
    u = sk_x_003f60e4(&a, *(word_t *)((word_t)0 + 0x18), *(word_t *)((word_t)0 + 0x20),
                      *(word_t *)((word_t)0 + 0x10));
    sk_x_0040695c(u, a, b);
    sk_x_00407894(0);
    u = sk_x_003f6278();
    if (*(byte *)((word_t)0 + 0x10) != 1) {
        word_t c, d;
        sk_x_0040695c(u, c, d);
        sk_x_00407894();
        sk_x_003f6278();
    }
}

/* FUN_00404f60 @ 0x00404f60   (est. sk_mr_span_copy)
 * Ghidra: void FUN_00404f60(void)
 * Copies a message span through the 0001a1c8 marshaller.
 * Confidence: low. */
static void sk_mr_span_copy_00404f60(void)
{
    word_t *p = (word_t *)sk_x_0035860c().lo;
    cl4_pair_t v = sk_x_0001a1c8(*p, p[1], *(word_t *)((word_t)0 + 0x10));
    ((cl4_pair_t *)((word_t)0 + 0x10))[0] = v;
}

/* FUN_00404f98 @ 0x00404f98   (est. sk_mr_span_from_frame)
 * Ghidra: void FUN_00404f98(void)
 * Builds a message span from the frame: {tag, frame+0x10+8, 0}.
 * Confidence: medium. */
static void sk_mr_span_from_frame_00404f98(void)
{
    sk_x_0035860c();
    word_t frame = *(word_t *)((word_t)0 + 0x10);
    word_t u1 = sk_x_0025177c();
    word_t u2 = *(word_t *)(frame + 8);
    ((word_t *)((word_t)0 + 0x10))[0] = u1;
    ((word_t *)((word_t)0 + 0x10))[1] = u2;
    ((word_t *)((word_t)0 + 0x10))[2] = 0;
}

/* FUN_00404fdc @ 0x00404fdc   (est. sk_mr_emit_check)
 * Ghidra: void FUN_00404fdc(long)
 * Emits a message span after validating the frame: if the current span still
 * matches the destination and no more words are pending, emits the primary
 * and re-checked spans; otherwise traps (fatal) via 004070cc + 00406310(0x112).
 * Confidence: medium.
 * Notes: noreturn FUN_001afa84. */
static void sk_mr_emit_check_00404fdc(sword_t p)
{
    if (*(sword_t *)(p + 8) == *(sword_t *)(*(sword_t *)((word_t)0 + 0x18) + 8) &&
        *(sword_t *)(p + 0x10) == 0) {
        word_t u, a, b;
        u = sk_x_003f5ee8(&a, *(sword_t *)((word_t)0 + 0x18), *(word_t *)((word_t)0 + 0x20),
                          *(word_t *)((word_t)0 + 0x10));
        sk_x_004064f8(u, a, b);
        u = sk_x_004084e8(0);
        if (*(byte *)((word_t)0 + 0x10) != 1) {
            word_t c, d;
            sk_x_004064f8(u, c, d);
            sk_x_004084e8();
        }
        return;
    }
    sk_x_004070cc();
    sk_x_00406310(0x112);
    sk_x_001afa84();   /* does not return */
}

/* FUN_00405088 @ 0x00405088   (est. sk_mr_call_args_c)
 * Ghidra: void FUN_00405088(undefined8,undefined8,undefined8)
 * Forwards frame words to 003f6560 (no epilogue).
 * Confidence: low. */
static void sk_mr_call_args_c_00405088(word_t a, word_t b, word_t c)
{
    sk_x_00407170();
    sk_x_003f6560(*(word_t *)((word_t)0 + 0x18), 0, c, *(word_t *)((word_t)0 + 0x10));
}

/* FUN_004050b4 @ 0x004050b4   (est. sk_mr_span_bounded)
 * Ghidra: void FUN_004050b4(undefined8,undefined8,long*)
 * Computes a bounded span and releases it: if the requested end exceeds the
 * available count, marks need-more; else releases via 000839d8.
 * Confidence: medium.
 * Notes: noreturn 001afe4c on range underflow. */
static void sk_mr_span_bounded_004050b4(word_t a, word_t b, sword_t *sp)
{
    word_t base = sk_x_00408238();
    sword_t end = sp[1] + *(sword_t *)(base + 0x10);
    if (end < 0) {
        sk_x_0040633c();
        sk_x_001afa84();   /* does not return */
    }
    word_t obj = *(word_t *)((word_t)0 + 0x18);
    word_t need = 1;
    if (*sp < end) {
        need = 1;
    } else if (end < *(sword_t *)(base + 0x10)) {
        sk_x_00347da8();
        sk_x_003504b8();
        sk_x_001afe4c();   /* does not return */
    } else {
        (*(word_t (**)(word_t))((word_t)0 + 0x20))(0);
        if ((word_t)0 + 0x10 != 0) {
            return;
        }
        need = 0;
    }
    sk_x_000839d8(0, need, 1, obj);
}

/* FUN_00405180 @ 0x00405180   (est. sk_mr_emit_region)
 * Ghidra: void FUN_00405180(undefined1 (*)[16],undefined8,undefined8)
 * Emits a multi-segment message region: builds the primary span, marshals the
 * first run, and if the frame has a second segment, marshals it too, returning
 * the 16-byte {base,length} result.
 * Confidence: low (large register-fragment path). */
static void sk_mr_emit_region_00405180(cl4_pair_t *out, word_t p2, word_t p3)
{
    word_t u10 = *(word_t *)((word_t)0 + 0x10);
    word_t u9 = *(word_t *)((word_t)0 + 0x18);
    word_t l3 = *(word_t *)((word_t)0 + 0x20);
    word_t u4 = *(word_t *)((word_t)0 + 0x28);
    word_t a, b;
    sk_x_003f5ee8(&a, p2, p3, u10);
    word_t l1 = l3;
    if ((sword_t)l3 < (sword_t)b) l1 = b;
    sk_x_00350500();
    word_t u6 = sk_x_0031de7c();
    word_t u7 = sk_x_00408524();
    word_t u8 = sk_x_00407324();
    sk_x_00376820(u8, u6);
    sk_x_0040668c();
    sk_x_00270d80((byte *)&a, &l1, u6, u7);
    sk_x_00407d24();
    sk_x_003f406c();
    sk_x_00350500();
    u6 = sk_x_0031b37c();
    u7 = sk_x_004066a4();
    u7 = sk_x_00376820(u7, u6);
    sk_x_001bb7a0((byte *)&a, l1, u6, u7);
    sk_x_00407d24();
    sk_x_003f7e8c();
    sk_x_003f7d48(0, 0, 0, 0, u10);
    word_t l11 = l1;
    if ((sword_t)b < (sword_t)l3 && *(byte *)((word_t)0 + 0x10) != 1) {
        if (l3 < l1) CL4_SW_BP(0x405360);
        word_t l2 = l3 - l1;
        if (l2 > (sword_t)l3) l2 = l3;   /* local_70 clamp */
        l11 = l1 + l2;
        if (l11 < l1) CL4_SW_BP(0x405364);
        if (l11 < l1) {
            sk_x_00347da8();
            sk_x_003504b8();
            sk_x_001afe4c();   /* does not return */
        }
        sk_x_00350738();
        sk_x_0028e8fc(0, 0, u9, l3, u10);
        sk_x_003f406c();
        sk_x_001bb7a0((byte *)&a, l2, u6, u7);
        sk_x_00407d24();
        sk_x_003f7e8c();
        sk_x_003f7d48(0, 0, 0, 0, u10);
    }
    u9 = sk_x_0036b270(u4).lo;
    cl4_pair_t r = sk_x_003f7b44(u9, l11);
    *out = r;
    *(word_t *)((word_t)&out[1]) = u10;
    *(sword_t *)((word_t)&out[1] + 8) = l11;
}
/* FUN_00405374 @ 0x00405374   (est. sk_mr_span_clamp)
 * Ghidra: void FUN_00405374(undefined8*,long)
 * Clamps a message span {base,start,end} to the available register count,
 * retaining the base object.
 * Confidence: medium.
 * Notes: noreturn 001afa84 via 004070cc/004063f4(0x2f) on underflow. */
static void sk_mr_span_clamp_00405374(word_t *out, sword_t off)
{
    sword_t l4 = *(sword_t *)((word_t)0 + 0x18);
    if (l4 < 0 || l4 > *(sword_t *)(off + 8)) {
        sk_x_004070cc();
        sk_x_004063f4(0x2f);
        sk_x_001afa84();   /* does not return */
    }
    word_t obj = *(word_t *)((word_t)0 + 0x20);
    word_t start = sk_x_003f5e78(l4, off);
    word_t end = start;
    if (l4 != *(sword_t *)(off + 8)) {
        word_t lim = sk_x_003f5e68(off);
        if (lim <= start) end = sk_x_003f5cf0(off);
    }
    out[0] = obj;
    out[1] = start;
    out[2] = end;
    sk_x_0036b270(obj);
}

/* FUN_0040542c @ 0x0040542c   (est. sk_mr_install_hook)
 * Ghidra: void FUN_0040542c(undefined8,undefined8)
 * Installs a hook closure (frame words) and registers 0040548c as the
 * callback via 003f540c.
 * Confidence: low. */
static void sk_mr_install_hook_0040542c(word_t p1, word_t p2)
{
    word_t l30 = *(word_t *)((word_t)0 + 0x10);
    sk_x_00359024(p1, p2, *(word_t *)((word_t)0 + 0x18));
    sk_x_003f540c((word_t)sk_mr_hook_cb_0040548c, (byte *)&l30);
}

/* FUN_0040548c @ 0x0040548c   (est. sk_mr_hook_cb)
 * Ghidra: void FUN_0040548c(long,undefined8)
 * The hook callback: consumes message words from the span, advances the
 * destination length, and re-emits any remaining tail.
 * Confidence: low (large register-fragment path).
 * Notes: noreturn 001afe4c on range underflow. */
static void sk_mr_hook_cb_0040548c(sword_t p1, word_t p2)
{
    word_t u1 = *(word_t *)((word_t)0 + 0x10);
    word_t *pu2 = *(word_t **)((word_t)0 + 0x18);
    sword_t *pl8 = *(sword_t **)((word_t)0 + 0x20);
    word_t a, b;
    sk_x_003f5ee8((byte *)&a, p1, p2, u1);
    sk_x_00350500();
    word_t u4 = sk_x_0031de7c();
    word_t u5 = sk_x_00408524();
    word_t u6 = sk_x_00407324();
    sk_x_00376820(u6, u4);
    sk_x_0040668c();
    sk_x_00270d80((byte *)&a, (sword_t *)&a, u4, u5);
    sk_x_003f406c(0, 0, 0, 0, u1);
    sk_x_00351790();
    sk_x_00350618();
    sk_x_003f7d48();
    sword_t l7 = *pl8 + (sword_t)a;
    *pl8 = l7;
    if (*(byte *)((word_t)0 + 0x10) != 1) {
        if ((sword_t)a + (sword_t)a < (sword_t)a) {
            sk_x_00347da8();
            sk_x_003504b8();
            sk_x_001afe4c();   /* does not return */
        }
        sk_x_0028e8fc(a, a + a, *pu2, pu2[1], u1);
        sk_x_003f406c();
        sk_x_00351790();
        sk_x_000a6e14();
        sk_x_003f7d48();
        l7 = *pl8 + (sword_t)a;
        *pl8 = l7;
    }
    if (l7 != *(sword_t *)(p1 + 8)) {
        sk_x_004070cc();
        sk_x_004063f4(0x6a);
        sk_x_001afa84();   /* does not return */
    }
}

/* FUN_00405604 @ 0x00405604   (est. sk_mr_span_end)
 * Ghidra: void FUN_00405604(void)
 * Computes a span end and invokes the +0x10 dispatch slot.
 * Confidence: low. */
static void sk_mr_span_end_00405604(void)
{
    sk_x_0034bb84();
    word_t u1 = *(word_t *)((word_t)0 + 0x10);
    sk_x_003f5e78(*(word_t *)((word_t)0 + 0x18));
    sk_x_000bd3a4();
    word_t u2 = sk_x_003f5c00();
    sk_x_003509c8(u1, u2, u2);
    (*(word_t (**)(void))((word_t)0 + 0x10))();
}

/* FUN_0040567c @ 0x0040567c   (est. sk_mr_span_bounded2)
 * Ghidra: void FUN_0040567c(undefined8,undefined8,long*)
 * Computes a bounded span: if the end exceeds the count, emits the need-more
 * marker; else releases via 000839d8.
 * Confidence: medium.
 * Notes: noreturn 001afe4c on range underflow. */
static void sk_mr_span_bounded2_0040567c(word_t a, word_t b, sword_t *sp)
{
    word_t base = sk_x_00408238();
    sword_t end = sp[1] + *(sword_t *)(base + 0x10);
    if (end < 0) {
        sk_x_0040633c();
        sk_x_001afa84();   /* does not return */
    }
    if (*sp < end) {
        sk_x_00350744(0);
        sk_x_000839d8();
    } else {
        if (end < *(sword_t *)(base + 0x10)) {
            sk_x_00347da8();
            sk_x_003504b8();
            sk_x_001afe4c();   /* does not return */
        }
        (*(word_t (**)(word_t, cl4_pair_t))((word_t)0 + 0x20))(0, (cl4_pair_t){0, 0});
        if ((word_t)0 + 0x10 == 0) {
            sk_x_0034ba48();
            sk_x_000839d8();
        }
        sk_x_003f8f60((cl4_pair_t){0, 0}, 0, 0);
    }
}

/* FUN_00405778 @ 0x00405778   (est. sk_mr_span_release)
 * Ghidra: void FUN_00405778(void)
 * Releases a message span (object + run).
 * Confidence: low. */
static void sk_mr_span_release_00405778(void)
{
    word_t u1 = sk_x_00407e20();
    word_t u2 = sk_x_003f5e78();
    sk_x_003504c4();
    sk_x_003f5c54();
    sk_x_00351790();
    sk_x_0031e5c8(u1, u2);
}

/* FUN_004057e0 @ 0x004057e0   (est. sk_mr_flush_args)
 * Ghidra: void FUN_004057e0(undefined8,undefined8)
 * Forwards the full frame word set to 003f9234.
 * Confidence: low. */
static void sk_mr_flush_args_004057e0(word_t p1, word_t p2)
{
    sk_x_003f9234(p1, p2,
                  *(word_t *)((word_t)0 + 0x28), *(word_t *)((word_t)0 + 0x30),
                  *(word_t *)((word_t)0 + 0x38), *(word_t *)((word_t)0 + 0x40),
                  *(word_t *)((word_t)0 + 0x48), *(word_t *)((word_t)0 + 0x50),
                  *(word_t *)((word_t)0 + 0x58), *(word_t *)((word_t)0 + 0x60),
                  *(word_t *)((word_t)0 + 0x10), *(word_t *)((word_t)0 + 0x18),
                  *(word_t *)((word_t)0 + 0x20));
}

/* FUN_00405830 @ 0x00405830   (est. sk_r62_00405830)
 * Ghidra: void FUN_00405830(void)
 * Thin wrapper to 00021480.
 * Confidence: high (trivial). */
static void sk_r62_00405830(void)
{
    sk_x_00021480();
}

/* FUN_00405848 @ 0x00405848   (est. sk_mr_emit_cap)
 * Ghidra: void FUN_00405848(void)
 * Emits a capability word: computes the span, records it, and stores the cap
 * into the frame at the computed slot.
 * Confidence: low.
 * Notes: DAT_00658c80 dispatch slot. */
static void sk_mr_emit_cap_00405848(void)
{
    sk_x_0034bb84();
    word_t u1 = *(word_t *)((word_t)0 + 0x10);
    word_t u3 = sk_x_003f5e78(*(word_t *)((word_t)0 + 0x18));
    sk_x_003515b4(0, 0x67f358, u1);
    word_t l4 = sk_x_003722e4();
    int i2 = *(int *)(l4 + 0x30);
    ((word_t *)((word_t)0 + 0x10))[0] = u3;
    sk_x_000bd3a4(u3);
    u3 = sk_x_003f5c00();
    sk_x_001a29a0((word_t)((word_t)0 + 0x10) + i2, u3, u1);
}

/* FUN_004058d4 @ 0x004058d4   (est. sk_mr_emit_syscall)
 * Ghidra: void FUN_004058d4(undefined8,undefined8)
 * Emits a syscall: forwards frame words to 00404ac0.
 * Confidence: low. */
static void sk_mr_emit_syscall_004058d4(word_t p1, word_t p2)
{
    sk_mr_syscall_dispatch_00404ac0(p1, p2, *(word_t **)((word_t)0 + 0x18),
                                    *(word_t *)((word_t)0 + 0x20), *(word_t *)((word_t)0 + 0x10));
}

/* FUN_00405904 @ 0x00405904   (est. sk_mr_span_dispatch)
 * Ghidra: void FUN_00405904(void)
 * Dispatches a span through the +0x18 slot.
 * Confidence: low. */
static void sk_mr_span_dispatch_00405904(void)
{
    sk_x_00407e20();
    sk_x_000bd3a4();
    sk_x_003f5c00();
    sk_x_003509c8();
    (*(word_t (**)(void))((word_t)0 + 0x18))();
}

/* FUN_00405968 @ 0x00405968   (est. sk_mr_emit_word2)
 * Ghidra: void FUN_00405968(undefined8,undefined8)
 * Forwards to 003f709c.
 * Confidence: low. */
static void sk_mr_emit_word2_00405968(word_t p1, word_t p2)
{
    sk_x_003f709c(p1, p2, *(word_t *)((word_t)0 + 0x10));
}

/* FUN_00405994 @ 0x00405994   (est. sk_mr_call_args_d)
 * Ghidra: void FUN_00405994(undefined8,undefined8,undefined8)
 * Forwards frame words to 003f6f3c.
 * Confidence: low. */
static void sk_mr_call_args_d_00405994(word_t a, word_t b, word_t c)
{
    sk_x_00407170();
    sk_x_003f6f3c(*(word_t *)((word_t)0 + 0x18), 0, c, *(word_t *)((word_t)0 + 0x10));
}

/* FUN_004059c0 @ 0x004059c0   (est. sk_mr_emit_word3)
 * Ghidra: void FUN_004059c0(undefined8,undefined8)
 * Forwards to 003f6e08.
 * Confidence: low. */
static void sk_mr_emit_word3_004059c0(word_t p1, word_t p2)
{
    sk_x_003f6e08(p1, p2, *(word_t *)((word_t)0 + 0x10));
}

/* FUN_004059ec @ 0x004059ec   (est. sk_mr_call_args_e)
 * Ghidra: void FUN_004059ec(undefined8,undefined8,undefined8)
 * Forwards frame words to 003f6fec.
 * Confidence: low. */
static void sk_mr_call_args_e_004059ec(word_t a, word_t b, word_t c)
{
    sk_x_00407170();
    sk_x_003f6fec(*(word_t *)((word_t)0 + 0x18), 0, c, *(word_t *)((word_t)0 + 0x10));
}

/* FUN_00405a18 @ 0x00405a18   (est. sk_mr_emit_word4)
 * Ghidra: void FUN_00405a18(undefined8,undefined8)
 * Forwards to 003f6ea8.
 * Confidence: low. */
static void sk_mr_emit_word4_00405a18(word_t p1, word_t p2)
{
    sk_x_003f6ea8(p1, p2, *(word_t *)((word_t)0 + 0x10));
}

/* FUN_00405a44 @ 0x00405a44   (est. sk_mr_call_args_f)
 * Ghidra: void FUN_00405a44(undefined8,undefined8,undefined8,undefined8)
 * Forwards frame words to 003f70f8.
 * Confidence: low. */
static void sk_mr_call_args_f_00405a44(word_t a, word_t b, word_t c, word_t d)
{
    sk_x_00408238();
    sk_x_003f70f8(*(word_t *)((word_t)0 + 0x18), *(word_t *)((word_t)0 + 0x20), c, d,
                  *(word_t *)((word_t)0 + 0x10));
}

/* FUN_00405a78 @ 0x00405a78   (est. sk_mr_span_grow)
 * Ghidra: void FUN_00405a78(undefined8,undefined8)
 * Grows a message span by one element and forwards to 003f70f8.
 * Confidence: medium.
 * Notes: CL4_SW_BP(0x405afc) on carry; noreturn 001afe4c on overflow. */
static void sk_mr_span_grow_00405a78(word_t p1, word_t p2)
{
    word_t u1 = *(word_t *)((word_t)0 + 0x10);
    word_t l3 = *(word_t *)((word_t)0 + 0x20);
    sk_x_003f8264(l3, **(word_t **)((word_t)0 + 0x18), u1);
    if (l3 > (word_t)-1) CL4_SW_BP(0x405afc);
    if (l3 <= l3 + 1) {
        sk_x_003f70f8(l3, l3 + 1, p1, p2, u1);
        return;
    }
    sk_x_00347da8();
    sk_x_003504b8();
    sk_x_001afe4c();   /* does not return */
}
/* FUN_0041a048 @ 0x0041a048   (est. sk_ipc_frame_init)
 * Ghidra: void FUN_0041a048(void)
 * Initialises the syscall frame: calls 004637b4 then 0045908c (the register
 * snapshot / badge fetch pair used by every syscall entry).
 * Confidence: medium. */
static void sk_ipc_frame_init_0041a048(void)
{
    sk_x_004637b4();
    sk_x_0045908c();
}

/* FUN_0041a068 @ 0x0041a068   (est. sk_ipc_frame_self_cap)
 * Ghidra: ulong FUN_0041a068(void)
 * Reads the current TCB's self capability word (masked to the 57-bit object
 * pointer) and retains it.
 * Confidence: medium. */
static word_t sk_ipc_frame_self_cap_0041a068(void)
{
    word_t v = *(word_t *)((word_t)0 + 0x68);
    sk_x_0036b270(v & 0xfffffffffffffff);
    return v;
}

/* FUN_0041a094 @ 0x0041a094   (est. sk_ipc_frame_bind)
 * Ghidra: void FUN_0041a094(void)
 * Binds the syscall frame: records a 0x68-byte snapshot region and the
 * caller's registers into the per-frame slots.
 * Confidence: medium. */
static void sk_ipc_frame_bind_0041a094(void)
{
    cl4_pair_t v = sk_x_00077888();
    word_t base = sk_x_00117cc4(0, v.lo, 0x68);
    *(word_t *)(base + 0x68) = v.hi;
    *(word_t *)(base + 0x70) = (word_t)((word_t)0 + 0x20);
    *(word_t *)(base + 0x78) = (word_t)((word_t)0 + 0x19);
}

/* FUN_0041a0dc @ 0x0041a0dc   (est. sk_ipc_badge_match)
 * Ghidra: uint FUN_0041a0dc(long*,long*)
 * Core IPC badge/right matching. The message word (param_1[10] tag) selects
 * how the caller's and callee's cap pointers are compared:
 *  - tag 1/2: invoke 0041a9e4 / 0041ae14 match helper
 *  - tag 3: full-zero "null" sentinel → reply match; else the one-hot index
 *    (param_1[0]==1..10) → match the indexed badge.
 *  - default: compare low cap pointers and the >> 0xe page frames with
 *    cross-check 00465c5c.
 * Returns 1 when the badges agree.
 * Confidence: low (large register-fragment decode).
 * Notes: FUN_00463dc8/00463558 validate the cap object. */
static uint sk_ipc_badge_match_0041a0dc(sword_t *p1, sword_t *p2)
{
    word_t tag = (word_t)((byte *)p1)[10] & 0xff;
    sword_t v12 = p1[0], v16 = p1[1];
    word_t v5 = (word_t)p1[2], v1 = (word_t)p1[3];
    sword_t v6 = p1[4], v2 = p1[5], v7 = p1[6], v3 = p1[7], v8 = p1[8], v15 = p1[9];

    if (tag == 1) {
        sk_x_00465fe0();
        if (*(byte *)(0 + 0x50) == 1) {
            return sk_ipc_match_tag1_0041a9e4() & 1;
        }
    } else if (tag == 2) {
        sk_x_00465fe0();
        if (*(byte *)(0 + 0x50) == 2) {
            return sk_ipc_match_tag2_0041ae14() & 1;
        }
    } else if (tag == 3) {
        if ((((v5 == 0 && v16 == 0) && (v12 == 0 && v1 == 0)) &&
             ((v6 == 0 && v2 == 0) && v7 == 0)) && ((v3 == 0 && v8 == 0) && v15 == 0)) {
            sk_x_00463dc8();
            sword_t r = sk_x_00463558(*(word_t *)(0 + 8), *(word_t *)(0 + 0x30),
                                      *(word_t *)(0 + 0x40), *(word_t *)(0 + 0x10),
                                      *(word_t *)(0 + 0x20));
            if (r == 0 && 0 == 0 && 0 == 0) {
                return 1;
            }
        } else {
            sword_t idx = v12;
            if (idx >= 1 && idx <= 10) {
                sk_x_00463dc8();
                sword_t *pl = (sword_t *)(0);
                if (*pl == idx) {
                    sword_t r = sk_x_00463558(pl[1], pl[6], pl[8], pl[2], pl[4]);
                    if (r == 0 && 0 == 0) {
                        return 1;
                    }
                }
            } else {
                sk_x_00463dc8();
            }
        }
    } else {
        word_t c2 = (word_t)p2[2], c3 = (word_t)p2[3];
        if ((byte *)p2[10] == 0) {
            if (v12 == p2[0] && v16 == p2[1]) {
                if (((c2 ^ v5) >> 0xe) == 0) {
                    if (((c3 ^ v1) >> 0xe) < 0x4000) {
                        return 1;
                    }
                }
            } else {
                word_t chk = sk_x_00465c5c();
                if (((chk & 1) != 0) && ((c2 ^ v5) < 0x4000)) {
                    if (((c3 ^ v1) >> 0xe) < 0x4000) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

/* FUN_0041a3ec @ 0x0041a3ec   (est. sk_ipc_badge_emit)
 * Ghidra: void FUN_0041a3ec(void)
 * Emits the IPC badge/right words into the message frame. The tag byte at
 * +0x50 selects the format: tags 1/2 call the helper pair; tag 3 emits the
 * one-hot encoded badge (index->type); default emits the null/address cap
 * words via thunk_FUN_002298d4 (the cap-to-slot mapper).
 * Confidence: low (register-fragment). */
static void sk_ipc_badge_emit_0041a3ec(void)
{
    sk_x_004666f8();
    sword_t *x20 = (sword_t *)((word_t)0 + 0x20);
    word_t tag = (word_t)((byte *)x20)[10] & 0xff;
    sword_t v1 = x20[0], v6 = x20[1];
    word_t v2 = (word_t)x20[2], v7 = (word_t)x20[3];
    sword_t v3 = x20[4], v8 = x20[5], v4 = x20[6], v9 = x20[7], v5 = x20[8], v10 = x20[9];

    if (tag == 1) {
        sk_x_00465fb4();
        sk_x_00465b58();
        sk_x_004650e4();
        sk_ipc_badge_emit_tag1_0041aab4();
    } else if (tag == 2) {
        sk_x_00465fb4();
        sk_x_002298d4(0xe);
        sk_x_004650e4();
        sk_ipc_badge_emit_tag2_0041aee4();
    } else if (tag == 3) {
        word_t emit = 0;
        if (((v2 == 0 && v6 == 0) && (v1 == 0 && v7 == 0)) &&
            ((v3 == 0 && v8 == 0) && v4 == 0) && (v9 == 0 && v5 == 0) && v10 == 0) {
            emit = 0;
        } else if (v1 >= 1 && v1 <= 10) {
            emit = v1 + 2;   /* index -> type (1..10 -> 3..0xc) */
        } else {
            emit = 0xd;
        }
        sk_x_002298d4(emit);
    } else {
        sk_x_00464e1c();
        sk_x_002298d4();
        sk_x_00462e0c();
        sk_x_001b9084();
        sk_x_002298d4(v2 >> 0xe);
        sk_x_002298d4(v7 >> 0xe);
    }
    sk_x_004666e4();
}

/* FUN_0041a5cc @ 0x0041a5cc   (est. sk_ipc_emit_frame_a)
 * Ghidra: void FUN_0041a5cc(void)
 * Frame emit: snapshot then 0041a3ec badge emit then 001a8564 epilogue.
 * Confidence: medium. */
static void sk_ipc_emit_frame_a_0041a5cc(void)
{
    byte frame[72];
    sk_x_004080b0();
    sk_ipc_badge_emit_0041a3ec();
    sk_x_001a8564();
}

/* FUN_0041a60c @ 0x0041a60c   (est. sk_ipc_emit_frame_b)
 * Ghidra: void FUN_0041a60c(void)
 * Frame emit: 001a84f4 snapshot then badge emit then epilogue.
 * Confidence: medium. */
static void sk_ipc_emit_frame_b_0041a60c(void)
{
    byte frame[72];
    sk_x_001a84f4(frame);
    sk_ipc_badge_emit_0041a3ec();
    sk_x_001a8564();
}

/* FUN_0041a64c @ 0x0041a64c   (est. sk_ipc_badge_match2)
 * Ghidra: undefined8 FUN_0041a64c(void)
 * Second badge-match: runs 0041a0dc plus the object/right consistency checks
 * (00464a08/00464ad0/0046622c) and compares the two TCB cap words.
 * Returns 1 when all agree.
 * Confidence: low. */
static word_t sk_ipc_badge_match2_0041a64c(void)
{
    sk_x_00350c5c();
    sk_ipc_badge_match_0041a0dc(0, 0);
    word_t u1 = sk_x_00464a08();
    if (((0 & 1) != 0) && (u1 = sk_x_00464ad0(), 0 == 0) &&
        (u1 = sk_x_0046622c(), 0 == 0)) {
        word_t m = sk_x_0041001c(*(word_t *)((word_t)0 + 0x68), *(word_t *)((word_t)0 + 0x68));
        if (((m & 1) == 0) || (sk_x_00464d0c(*(word_t *)((word_t)0 + 0x70)), 0 != 0) ||
            (sk_x_00465264(*(word_t *)((word_t)0 + 0x78)), 0)) {
            u1 = 0;
        } else {
            u1 = 1;
        }
    }
    return u1;
}

/* FUN_0041a6dc @ 0x0041a6dc   (est. sk_ipc_badge_emit_frame)
 * Ghidra: void FUN_0041a6dc(void)
 * Emits the badge frame: runs 0041a3ec then emits the two stored cap words.
 * Confidence: low. */
static void sk_ipc_badge_emit_frame_0041a6dc(void)
{
    sk_x_00464a38();
    word_t v = *(word_t *)((word_t)0 + 0x60);
    sk_ipc_badge_emit_0041a3ec();
    sk_x_00466660();
    sk_x_002298d4(v >> 0xe);
    sk_x_00410414();
    v = *(word_t *)((word_t)0 + 0x78);
    sk_x_002298d4(*(word_t *)((word_t)0 + 0x70) >> 0xe);
    sk_x_002298d4(v >> 0xe);
}

/* FUN_0041a740 @ 0x0041a740   (est. sk_ipc_emit_badge_frame)
 * Ghidra: void FUN_0041a740(void)
 * Emits the full badge frame (0041a3ec + right checks + cap words + epilogue).
 * Confidence: low. */
static void sk_ipc_emit_badge_frame_0041a740(void)
{
    byte frame[72];
    sk_x_004644e8();
    word_t v = *(word_t *)((word_t)0 + 0x60);
    sk_ipc_badge_emit_0041a3ec();
    sk_x_004652a0();
    sk_x_002298d4(v >> 0xe);
    sk_x_00410414(frame, *(word_t *)((word_t)0 + 0x68));
    sk_x_00465234(*(word_t *)((word_t)0 + 0x70));
    sk_x_00464eb0();
    sk_x_001a8564();
}

/* FUN_0041a7cc @ 0x0041a7cc   (est. sk_ipc_emit_hook_a)
 * Ghidra: void FUN_0041a7cc(void)
 * Emits via the hook closure (unaff_x19 function pointer).
 * Confidence: low. */
static void sk_ipc_emit_hook_a_0041a7cc(void)
{
    byte frame[72];
    sk_x_004653c0();
    ((void (*)(byte *))((word_t)0 + 0x19))(frame);
    sk_x_001a8564();
}

/* FUN_0041a80c @ 0x0041a80c   (est. sk_ipc_release_or_drop)
 * Ghidra: void FUN_0041a80c(void)
 * Releases the stored TCB cap when the frame is empty or tagged; else drops.
 * Confidence: medium. */
static void sk_ipc_release_or_drop_0041a80c(void)
{
    if (*(byte *)((word_t)0 + 0x50) == 0 ||
        (*(byte *)((word_t)0 + 0x50) == 1 && *(sword_t *)((word_t)0 + 8) != 0)) {
        sk_x_0036b270(*(sword_t *)((word_t)0 + 8));
    }
    sk_x_003507e0();
}

/* FUN_0041a868 @ 0x0041a868   (est. sk_ipc_reply_result)
 * Ghidra: undefined8 FUN_0041a868(void)
 * Returns the syscall reply code for a given frame: tag 3 with the right
 * lookup result (00463558) selects 0x101 / 0x100 / 0 / else 2.
 * Confidence: low.
 * Notes: FUN_0006e064 = "ok" sentinel. */
static word_t sk_ipc_reply_result_0041a868(void)
{
    if (*(byte *)((word_t)0 + 10) == 3) {
        sword_t l = sk_x_00463558(*(word_t *)((word_t)0 + 0), *(word_t *)((word_t)0 + 0x30),
                                  *(word_t *)((word_t)0 + 0x40), *(word_t *)((word_t)0 + 0x10),
                                  *(word_t *)((word_t)0 + 0x20));
        if (0 == 4 && l == 0 && 0 == 0) return 0x101;
        if (0 == 5 && l == 0 && 0 == 0) return sk_x_0006e064();
        if (0 == 7 && l == 0 && 0 == 0) return 0x100;
        if (0 == 8 && l == 0 && 0 == 0) return 0;
    }
    return 2;
}

/* FUN_0041a8f4 @ 0x0041a8f4   (est. sk_ipc_frame_release)
 * Ghidra: void FUN_0041a8f4(void)
 * Releases the frame's stored object and resets the frame.
 * Confidence: medium. */
static void sk_ipc_frame_release_0041a8f4(void)
{
    sk_x_0036b270(*(word_t *)((word_t)0 + 0x38));
    sk_x_00462d5c();
}

/* FUN_0041a92c @ 0x0041a92c   (est. sk_ipc_frame_save_regs)
 * Ghidra: void FUN_0041a92c(void)
 * Saves the caller's registers into the frame slots +0x30..+0x48.
 * Confidence: low. */
static void sk_ipc_frame_save_regs_0041a92c(void)
{
    sk_x_00349a18();
    sk_x_003a25d4(*(word_t *)((word_t)0 + 0x38));
    *(word_t *)((word_t)0 + 0x30) = (word_t)((word_t)0 + 0x23);
    *(word_t *)((word_t)0 + 0x38) = (word_t)((word_t)0 + 0x22);
    *(word_t *)((word_t)0 + 0x40) = (word_t)((word_t)0 + 0x21);
    *(word_t *)((word_t)0 + 0x48) = (word_t)((word_t)0 + 0x19);
}

/* FUN_0041a96c @ 0x0041a96c   (est. sk_ipc_build_msgwords)
 * Ghidra: void FUN_0041a96c(undefined8 x 11)
 * Builds the 0x50-byte message-info struct from the register words and copies
 * it to the destination.
 * Confidence: medium. */
static void sk_ipc_build_msgwords_0041a96c(word_t out, word_t p2, word_t p3, word_t p4,
                                           word_t p5, word_t p6, word_t p7, word_t p8,
                                           word_t p9, word_t p10, word_t p11)
{
    byte frame[80];
    word_t local[9];
    word_t w0[9];
    local[0] = p2; local[1] = p3; local[2] = p4; local[3] = p5;
    local[4] = p6; local[5] = p7; local[6] = p8; local[7] = p9;
    w0[0] = p2; w0[1] = p3; w0[2] = p4; w0[3] = p5;
    w0[4] = p6; w0[5] = p7; w0[6] = p8; w0[7] = p9;
    local[8] = p10; w0[8] = p11;
    sk_x_00458d68(&local, frame);
    sk_x_00458d78(&w0);
    sk_x_00117cc4(out, &local, 0x50);
}

/* FUN_0041a9e4 @ 0x0041a9e4   (est. sk_ipc_match_tag1)
 * Ghidra: uint FUN_0041a9e4(void)
 * Badge-match for tag 1: compares the two cap words and, if the low frame
 * words agree, validates the indexed badge objects.
 * Confidence: low. */
static uint sk_ipc_match_tag1_0041a9e4(void)
{
    word_t l4 = sk_x_003504d0().lo;
    word_t v5 = *(word_t *)(l4 + 8);
    /* unaff_x19 / unaff_x20 are caller-set base registers the decompiler
     * could not resolve; held symbolic (offsets preserved). */
    word_t *x19 = (word_t *)((word_t)0 + 0x19);
    word_t *x20 = (word_t *)((word_t)0 + 0x20);
    /* Register-aliased flag/result values (extraout_x8/x8_00/x8_01/x8_02)
     * the decompiler could not resolve; symbolic, default 0. */
    word_t e8 = 0, e8_00 = 0, e8_01 = 0, e8_02 = 0;
    word_t v6 = x19[1];
    word_t uVar3 = 0;
    word_t uVar2 = 0;
    if (v5 == 0) {
        if (v6 == 0) goto check;
    } else if (v6 != 0) {
        bool u1 = (x20[0] == x19[0]) && v6 <= v5;
        if (x20[0] == x19[0] && v5 == v6) {
            sk_x_00464ad0();
            uVar2 = u1;
            if (e8_00 != 0) { uVar3 = 0; goto ret; }
        } else {
            sk_x_002a0cf8();
            uVar3 = sk_x_00464a08();
            if ((e8 & 1) == 0) goto ret;
            uVar3 = sk_x_00465968();
            uVar2 = 0;
            if (u1) goto ret;
        }
        sk_x_004658a8();
        if (!uVar2) goto check;
        uVar3 = 0;
        goto ret;
    }
    uVar3 = 0;
    goto ret;
check:
    sk_x_00464d0c(x20[4]);
    if (e8_01 == 0 && (sk_x_00464d0c(x19[5]), e8_02 == 0)) {
        uVar3 = sk_x_00448fd0(x20[6], x20[7], x20[8], x20[9],
                              x19[6], x19[7], x19[8], x19[9]);
        goto ret;
    }
    uVar3 = 0;
ret:
    return uVar3 & 1;
}

/* FUN_0041aab4 @ 0x0041aab4   (est. sk_ipc_badge_emit_tag1)
 * Ghidra: void FUN_0041aab4(void)
 * Emits the tag-1 badge words (address caps + pending count).
 * Confidence: low. */
static void sk_ipc_badge_emit_tag1_0041aab4(void)
{
    sk_x_00464a44();
    word_t *x19 = (word_t *)((word_t)0 + 0x19);
    if (x19[1] == 0) {
        sk_x_00229a3c(0);
    } else {
        word_t u1 = x19[2], u2 = x19[3];
        sk_x_00229a3c(1);
        sk_x_00077894();
        sk_x_001b9084();
        sk_x_002298d4(u1 >> 0xe);
        sk_x_002298d4(u2 >> 0xe);
    }
    word_t u1 = x19[5];
    word_t u2;
    sk_x_002298d4(x19[4] >> 0xe);
    sk_x_002298d4(u1 >> 0xe);
    u1 = x19[8];
    u2 = x19[9];
    sk_x_001b9084();
    sk_x_002298d4(u1 >> 0xe);
    sk_x_002298d4(u2 >> 0xe);
}

/* FUN_0041ab70 @ 0x0041ab70   (est. sk_ipc_emit_hook_b)
 * Ghidra: void FUN_0041ab70(void)
 * Emits via hook closure (unaff_x19 fn ptr).
 * Confidence: low. */
static void sk_ipc_emit_hook_b_0041ab70(void)
{
    byte frame[72];
    sk_x_004648fc();
    ((void (*)(byte *))((word_t)0 + 0x19))(frame);
    sk_x_001a8564();
}

/* FUN_0041abcc @ 0x0041abcc   (est. sk_ipc_emit_hook_c)
 * Ghidra: void FUN_0041abcc(void)
 * Emits via hook closure (unaff_x19 fn ptr), with 004653c0 snapshot.
 * Confidence: low. */
static void sk_ipc_emit_hook_c_0041abcc(void)
{
    byte frame[72];
    sk_x_004653c0();
    ((void (*)(byte *))((word_t)0 + 0x19))(frame);
    sk_x_001a8564();
}

/* FUN_0041ac6c @ 0x0041ac6c   (est. sk_ipc_write_triple)
 * Ghidra: void FUN_0041ac6c(undefined8,undefined1,ulong,ulong)
 * Writes three message words: a type byte, then two cap pointers (>> 0xe).
 * Confidence: high. */
static void sk_ipc_write_triple_0041ac6c(word_t a, byte type, word_t c1, word_t c2)
{
    sk_x_002298d4(type);
    sk_x_002298d4(c1 >> 0xe);
    sk_x_002298d4(c2 >> 0xe);
}

/* FUN_0041acb4 @ 0x0041acb4   (est. sk_ipc_emit_state)
 * Ghidra: void FUN_0041acb4(void)
 * Emits a state word and the message epilogue.
 * Confidence: low. */
static void sk_ipc_emit_state_0041acb4(void)
{
    byte type = sk_x_00350b54();
    sk_x_004080b0();
    sk_x_002298d4(type);
    sk_x_004652a0();
    sk_x_00464eb0();
    sk_x_001a8564();
}

/* FUN_0041ad20 @ 0x0041ad20   (est. sk_ipc_emit_triple_frame)
 * Ghidra: void FUN_0041ad20(void)
 * Emits a triple (type + two caps) from the frame words.
 * Confidence: medium. */
static void sk_ipc_emit_triple_frame_0041ad20(void)
{
    byte frame[72];
    word_t u1 = *(word_t *)((word_t)0 + 8);
    word_t u2 = *(word_t *)((word_t)0 + 0x10);
    byte type = *(byte *)((word_t)0 + 0);
    sk_x_001a84f4(frame);
    sk_ipc_write_triple_0041ac6c(0, type, u1, u2);
    sk_x_001a8564();
}

/* FUN_0041adbc @ 0x0041adbc   (est. sk_ipc_frame_set_cap)
 * Ghidra: void FUN_0041adbc(undefined8)
 * Releases the frame's stored cap and stores a new one.
 * Confidence: medium. */
static void sk_ipc_frame_set_cap_0041adbc(word_t cap)
{
    sk_x_0036b118(*(word_t *)((word_t)0 + 0x38));
    *(word_t *)((word_t)0 + 0x38) = cap;
}

/* FUN_0041ae04 @ 0x0041ae04   (est. sk_ipc_frame_busy)
 * Ghidra: bool FUN_0041ae04(void)
 * Returns true when the frame is not tagged busy (state byte != 1).
 * Confidence: high. */
static bool sk_ipc_frame_busy_0041ae04(void)
{
    return *(byte *)((word_t)0 + 0x10) != 1;
}

/* FUN_0041ae14 @ 0x0041ae14   (est. sk_ipc_match_tag2)
 * Ghidra: undefined8 FUN_0041ae14(void)
 * Badge-match for tag 2: compares cap words via 00465264/004637dc and the
 * object pair via 00411290. Returns 1 when they agree.
 * Confidence: low. */
static word_t sk_ipc_match_tag2_0041ae14(void)
{
    cl4_pair_t v = sk_x_003504d0();
    char c1 = *(char *)(v.hi + 0x10);
    if (*(char *)(v.lo + 0x10) == 1) {
        if (c1 != 1) return 0;
    } else {
        bool b2 = c1 != 1;
        if (c1 == 1 || ((*(word_t *)((word_t)0 + 0x20) ^ *(word_t *)((word_t)0 + 0x19)) >> 0xe) != 0) {
            return 0;
        }
        sk_x_00465264(((word_t *)((word_t)0 + 0x19))[1]);
        if (b2) return 0;
    }
    word_t m = sk_x_00411290(((word_t *)((word_t)0 + 0x20))[3], ((word_t *)((word_t)0 + 0x19))[3]);
    if ((m & 1) != 0) {
        char c6 = (char)((word_t *)((word_t)0 + 0x19))[6];
        if ((char)((word_t *)((word_t)0 + 0x20))[6] == 1) {
            if (c6 == 1) {
                return sk_x_00411290(((word_t *)((word_t)0 + 0x20))[7], ((word_t *)((word_t)0 + 0x19))[7]);
            }
        } else {
            bool u3 = c6 != 0;
            if (c6 != 1 && (sk_x_004637dc(), 0 == 0) &&
                (sk_x_00465264(((word_t *)((word_t)0 + 0x19))[5]), !u3)) {
                return sk_x_00411290(((word_t *)((word_t)0 + 0x20))[7], ((word_t *)((word_t)0 + 0x19))[7]);
            }
        }
    }
    return 0;
}

/* FUN_0041aee4 @ 0x0041aee4   (est. sk_ipc_badge_emit_tag2)
 * Ghidra: void FUN_0041aee4(void)
 * Emits the tag-2 badge words.
 * Confidence: low. */
static void sk_ipc_badge_emit_tag2_0041aee4(void)
{
    sk_x_00464a44();
    word_t *x19 = (word_t *)((word_t)0 + 0x19);
    if ((char)x19[2] == 1) {
        sk_x_00229a3c(0);
    } else {
        word_t u1 = x19[0], u2 = x19[1];
        sk_x_00229a3c(1);
        sk_x_002298d4(u1 >> 0xe);
        sk_x_002298d4(u2 >> 0xe);
    }
    sk_x_00458278();
    if ((char)x19[6] == 1) {
        sk_x_00229a3c(0);
    } else {
        word_t u1 = x19[4], u2 = x19[5];
        sk_x_00229a3c(1);
        sk_x_002298d4(u1 >> 0xe);
        sk_x_002298d4(u2 >> 0xe);
    }
    sk_x_00458278();
}

/* FUN_0041afc8 @ 0x0041afc8   (est. sk_ipc_capdesc_make)
 * Ghidra: void FUN_0041afc8(undefined8*,undefined8)
 * Initialises a capability descriptor: type byte + index + object pointer
 * (the one-hot / null cap layout).
 * Confidence: high. */
static void sk_ipc_capdesc_make_0041afc8(word_t *d, word_t obj)
{
    d[0] = 0;
    d[1] = 0;
    *(byte *)(d + 2) = 1;
    d[4] = 0;
    d[5] = 0;
    d[3] = obj;
    *(byte *)(d + 6) = 1;
    d[7] = DAT_00657778;
}

/* FUN_0041aff0 @ 0x0041aff0   (est. sk_ipc_capdesc_make2)
 * Ghidra: void FUN_0041aff0(undefined8*,undefined8)
 * Alternate capability-descriptor initialiser.
 * Confidence: high. */
static void sk_ipc_capdesc_make2_0041aff0(word_t *d, word_t obj)
{
    d[0] = 0;
    d[1] = 0;
    *(byte *)(d + 2) = 1;
    d[4] = 0;
    d[5] = 0;
    d[3] = DAT_00657778;
    *(byte *)(d + 6) = 1;
    d[7] = obj;
}
/* FUN_0041b01c @ 0x0041b01c   (est. sk_ipc_parse_capdesc)
 * Ghidra: undefined1 [16] FUN_0041b01c(void)
 * Parses a capability descriptor into a 16-byte result, using the 00463e04
 * and 00205844 marshallers.
 * Confidence: low. */
static cl4_pair_t sk_ipc_parse_capdesc_0041b01c(void)
{
    cl4_pair_t v = sk_x_00463e04();
    byte t = v.lo;
    sk_x_00463df8(v.lo, v.hi, 0x6847e8);
    sk_x_00462728();
    cl4_pair_t r = sk_x_00205844(&t, (byte *)&t);
    return r;
}

/* FUN_0041b068 @ 0x0041b068   (est. sk_ipc_parse_capdesc_a)
 * Ghidra: void FUN_0041b068(void)
 * Parses the capability descriptor at the frame words.
 * Confidence: low. */
static void sk_ipc_parse_capdesc_a_0041b068(void)
{
    word_t *x20 = (word_t *)((word_t)0 + 0x20);
    sk_ipc_parse_capdesc_0041b01c();
}

/* FUN_0041b06c @ 0x0041b06c   (est. sk_ipc_parse_capdesc_b)
 * Ghidra: void FUN_0041b06c(void)
 * Parses the capability descriptor at the frame words (alt).
 * Confidence: low. */
static void sk_ipc_parse_capdesc_b_0041b06c(void)
{
    word_t *x20 = (word_t *)((word_t)0 + 0x20);
    sk_ipc_parse_capdesc_0041b01c();
}

/* FUN_0041b088 @ 0x0041b088   (est. sk_ipc_error_string)
 * Ghidra: undefined1 [16] FUN_0041b088(void)
 * Builds the error/status message for the syscall return path. Emits the
 * per-frame status words ("resetsCurrentOptions" tag / "error:" / "false" /
 * "true" hex words) and returns a 16-byte status pair.
 * Confidence: low.
 * Notes: string ref s___resetsCurrentOptions__005dd260; hex words 0x65736c6166
 *   ("false") / 0x65757274 ("true"). */
static cl4_pair_t sk_ipc_error_string_0041b088(void)
{
    sk_x_00100c04();
    sk_x_002a4ab4(0x32);
    sk_x_003a25d4((word_t)((word_t)0 + 0x38));
    sk_x_001a6a8c(*(word_t *)((word_t)0 + 0x18), 0x684750);
    sk_x_002acbb8();
    sk_x_003a25d4(0);
    sk_x_002acbb8(0x69766f6d6572202c, 0xec000000203a676e);
    sk_x_001a6a8c(*(word_t *)((word_t)0 + 0x38), 0x684750);
    sk_x_00465944();
    sk_x_002acbb8();
    sk_x_003a25d4(0x684750);
    sk_x_004643cc(0x005dd260);   /* "resetsCurrentOptions" string */
    sk_x_002acbb8(0xd000000000000018);
    bool b4 = *(byte *)((word_t)0 + 0x10) != 1;
    word_t u1 = 0x65736c6166;   /* "false" */
    word_t u2 = 0xe500000000000000;
    if (b4) {
        u1 = 0x65757274;        /* "true" */
        u2 = 0xe400000000000000;
    }
    sk_x_00465c74(u1);
    sk_x_003a25d4(u2);
    return (cl4_pair_t){ 0x203a676e69646461, 0xe800000000000000 };
}

/* FUN_0041b1a8 @ 0x0041b1a8   (est. sk_ipc_error_dispatch)
 * Ghidra: void FUN_0041b1a8(void)
 * Error-dispatch: 004632f4 then the 0041b088 error-string build.
 * Confidence: medium. */
static void sk_ipc_error_dispatch_0041b1a8(void)
{
    sk_x_004632f4();
    sk_ipc_error_string_0041b088();
}

/* FUN_0041b1d4 @ 0x0041b1d4   (est. sk_ipc_badge_validate)
 * Ghidra: ulong FUN_0041b1d4(8 args)
 * Validates an IPC badge/right pair across the two cap words. The message
 * type (param_2 >> 0x3d) and the object-type (param_6 >> 0x1d) must agree,
 * the address caps must match in their >> 0xe page frames, and the
 * null/one-hot sentinel words must be consistent. Returns 1 on success.
 * Confidence: low.
 * Notes: FUN_0006e064 = "ok". */
static word_t sk_ipc_badge_validate_0041b1d4(sword_t p1, word_t p2, word_t p3, word_t p4,
                                             sword_t p5, word_t p6, word_t p7, word_t p8)
{
    uint u3 = (uint)(p6 >> 0x20);
    switch (p2 >> 0x3d) {
    case 1:
        if (u3 >> 0x1d != 1) return 0;
        break;
    case 2:
        if (u3 >> 0x1d != 2) return 0;
        break;
    case 3:
        if (u3 >> 0x1d != 3) return 0;
        goto LAB_badge5;
    case 4:
        if (p6 > (word_t)0x9fffffffffffffff) return 0;
LAB_badge5:
        return (word_t)((((uint)p5 ^ (uint)p1) & 0xff) == 0);
    case 5:
        if (p2 == 0xa000000000000000 && p4 == 0 && p3 == 0 && p1 == 0) {
            if (u3 >> 0x1d != 5 || p6 != 0xa000000000000000) return 0;
            if (p8 != 0 || p7 != 0 || p5 != 0) return 0;
            return sk_x_0006e064();
        }
        if ((p2 == 0xa000000000000000 && p1 == 1) && p4 == 0 && p3 == 0) {
            bool b = u3 >> 0x1d == 5 && p5 == 1;
LAB_badge6:
            if (!b || p6 != 0xa000000000000000) return 0;
        } else if ((p2 == 0xa000000000000000 && p1 >= 2 && p1 <= 6) && p4 == 0 && p3 == 0) {
            bool b = u3 >> 0x1d == 5 && p5 == p1;
            goto LAB_badge6;
        } else if (u3 >> 0x1d != 5 || p5 != 7 || p6 != 0xa000000000000000) {
            return 0;
        }
        if (p8 != 0 || p7 != 0) return 0;
        return sk_x_0006e064();
    default:
        if (u3 >> 0x1d != 0) return 0;
        break;
    }
    u3 = (uint)p6 & 0xff;
    if ((p2 & 0xff) == 1) {
        if (u3 != 1) return 0;
    } else if (u3 == 1 || p1 != p5) {
        return 0;
    }
    if (((p7 ^ p3) >> 0xe) != 0 || (0x3fff < (p8 ^ p4))) return 0;
    return sk_x_0006e064();
}

/* FUN_0041b3d4 @ 0x0041b3d4   (est. sk_ipc_badge_emit)
 * Ghidra: void FUN_0041b3d4(undefined8,ulong,ulong,ulong,ulong)
 * Emits the badge/right message words from the parsed frame: maps the
 * message type to a one-hot badge type and writes the cap words.
 * Confidence: low. */
static void sk_ipc_badge_emit_0041b3d4(word_t a, word_t p2, word_t p3, word_t p4, word_t p5)
{
    word_t type = 0;
    switch (p3 >> 0x3d) {
    case 1: type = 1; break;
    case 2: type = 2; break;
    case 3:
        type = 0xb;
        goto LAB_badge_emit_map;
    case 4:
        type = 0xc;
LAB_badge_emit_map:
        sk_x_002298d4(type);
        p2 = p2 & 0xff;
LAB_badge_emit_low:
        sk_x_002298d4(p2);
        return;
    case 5:
        if (p3 == 0xa000000000000000 && p5 == 0 && p4 == 0 && p2 == 0) p2 = 3;
        else if ((p3 == 0xa000000000000000 && p2 >= 1 && p2 <= 6) && p5 == 0 && p4 == 0) p2 = p2 + 3;
        else p2 = 10;
        goto LAB_badge_emit_low;
    default:
        break;
    }
    sk_x_002298d4(type);
    if ((p3 & 0xff) == 1) {
        sk_x_00229a3c(0);
    } else {
        sk_x_00229a3c(1);
        sk_x_002298d4(p2);
    }
    sk_x_002298d4(p4 >> 0xe);
    sk_x_002298d4(p5 >> 0xe);
}

/* FUN_0041b58c @ 0x0041b58c   (est. sk_ipc_dispatch_main)
 * Ghidra: void FUN_0041b58c(void)
 * Main IPC dispatch: snapshots, runs the hook, and returns through the
 * frame epilogue.
 * Confidence: low. */
static void sk_ipc_dispatch_main_0041b58c(void)
{
    sk_x_004666f8();
    sk_x_00351da8();
    word_t u1 = sk_x_00350980();
    sk_x_004080b0();
    sk_x_00351b78(&u1, u1);
    ((void (*)(void))((word_t)0 + 0x19))();
    u1 = sk_x_001a8564();
    sk_x_004666e4(u1, 0);
}

/* FUN_0041b64c @ 0x0041b64c   (est. sk_ipc_badge_validate2)
 * Ghidra: undefined8 FUN_0041b64c(void)
 * Runs the badge validation (0041b1d4) plus object/right checks.
 * Returns 1 on success.
 * Confidence: low. */
static word_t sk_ipc_badge_validate2_0041b64c(void)
{
    word_t *p = (word_t *)sk_x_00350c5c();
    word_t m = sk_ipc_badge_validate_0041b1d4(p[0], *(word_t *)((word_t)0 + 8),
                                              *(word_t *)((word_t)0 + 0x10),
                                              *(word_t *)((word_t)0 + 0x18),
                                              *(word_t *)((word_t)0 + 0x20),
                                              *(word_t *)((word_t)0 + 0x28),
                                              *(word_t *)((word_t)0 + 0x30),
                                              *(word_t *)((word_t)0 + 0x38));
    if (((m & 1) == 0) || (sk_x_004637dc(), 0 != 0) || (sk_x_00465264(*(word_t *)((word_t)0 + 0x40)), 0)) {
        return 0;
    }
    return 1;
}

/* FUN_0041b6ac @ 0x0041b6ac   (est. sk_ipc_badge_emit2)
 * Ghidra: void FUN_0041b6ac(undefined8)
 * Emits the badge via 0041b3d4 and the trailing cap words.
 * Confidence: low. */
static void sk_ipc_badge_emit2_0041b6ac(word_t a)
{
    word_t *x20 = (word_t *)((word_t)0 + 0x20);
    sk_ipc_badge_emit_0041b3d4(a, x20[0], x20[1], x20[2], x20[3]);
    word_t u1 = x20[5];
    sk_x_004647b4(x20[4]);
    sk_x_002298d4();
    sk_x_002298d4(u1 >> 0xe);
}

/* FUN_0041b6f4 @ 0x0041b6f4   (est. sk_ipc_badge_emit_frame2)
 * Ghidra: void FUN_0041b6f4(void)
 * Emits the badge frame (0041b3d4 + right checks + epilogue).
 * Confidence: low. */
static void sk_ipc_badge_emit_frame2_0041b6f4(void)
{
    byte frame[72];
    word_t *x20 = (word_t *)((word_t)0 + 0x20);
    sk_x_004080b0();
    sk_ipc_badge_emit_0041b3d4(0, x20[0], x20[1], x20[2], x20[3]);
    sk_x_00465234(x20[4]);
    sk_x_00464eb0();
    sk_x_001a8564();
}

/* FUN_0041b760 @ 0x0041b760   (est. sk_ipc_emit_hook_d)
 * Ghidra: void FUN_0041b760(void)
 * Emits via hook closure (unaff_x19 fn ptr), 004653c0 snapshot.
 * Confidence: low. */
static void sk_ipc_emit_hook_d_0041b760(void)
{
    byte frame[72];
    sk_x_004653c0();
    ((void (*)(byte *))((word_t)0 + 0x19))(frame);
    sk_x_001a8564();
}

/* FUN_0041b7b8 @ 0x0041b7b8   (est. sk_ipc_frame_capture)
 * Ghidra: void FUN_0041b7b8(void)
 * Captures the syscall frame: snapshots 0x50 bytes, then stores the tag byte
 * and the in-register words at the fixed frame slots.
 * Confidence: low. */
static void sk_ipc_frame_capture_0041b7b8(void)
{
    sk_x_00084220();
    word_t u1 = sk_x_00351dc0();
    word_t base = sk_x_00117cc4(0, u1, 0x50);
    *(byte *)(base + 0x50) = 0;   /* extraout_w1 tag */
    *(word_t *)(base + 0x58) = 0; /* unaff_x24 */
    *(word_t *)(base + 0x60) = 0; /* unaff_x23 */
    *(word_t *)(base + 0x68) = 0; /* in_x4 */
    *(word_t *)(base + 0x70) = 0; /* in_x5 */
    *(word_t *)(base + 0x78) = 0; /* in_x6 */
    *(word_t *)(base + 0x80) = 0; /* in_x7 */
    sk_x_00084234(0);
}

/* FUN_0041b820 @ 0x0041b820   (est. sk_ipc_msgwords_match)
 * Ghidra: undefined8 FUN_0041b820(long*,long*)
 * Compares two message-word sets for IPC matching: the message types must
 * agree, the address caps must match in >> 0xe, and the null/one-hot
 * sentinels must be consistent. Returns 1 on success.
 * Confidence: low (large compare tree).
 * Notes: FUN_0006e064 = "ok". */
static word_t sk_ipc_msgwords_match_0041b820(sword_t *p1, sword_t *p2)
{
    sword_t v2 = p1[0];
    word_t v6 = (word_t)p1[1], v3 = (word_t)p1[2], v13 = (word_t)p1[3];
    sword_t v4 = p1[4];
    word_t v7 = (word_t)p1[5], v5 = (word_t)p1[6], v8 = (word_t)p1[7];

    switch (v7 >> 0x3d) {
    case 1:
        if ((word_t)p2[5] >> 0x3d != 1) return 0;
        break;
    case 2:
        if ((word_t)p2[5] >> 0x3d != 2) return 0;
        break;
    case 3:
        if ((word_t)p2[5] >> 0x3d != 3) return 0;
        if ((v6 & 0xff) == 1) { if ((char)p2[1] != 1) return 0; }
        else if ((char)p2[1] == 1 || v2 != p2[0]) return 0;
        if (((p2[2] ^ v3) >> 0xe) != 0) return 0;
        if (((p2[3] ^ v13) >> 0xe) != 0) return 0;
        {
            uint u1 = (uint)p2[5] & 0xff;
            if ((v7 & 0xff) == 1) { if (u1 != 1) return 0; }
            else if (u1 == 1 || v4 != p2[4]) return 0;
        }
        if (((p2[6] ^ v5) >> 0xe) != 0) return 0;
        v13 = (word_t)p2[7] ^ v8;
        if (v13 < 0x4000) return sk_x_0006e064(0);
        return 0;
    case 4:
        if (v7 == 0x8000000000000000 &&
            (((v3 == 0 && v6 == 0) && (v2 == 0 && v13 == 0)) &&
             ((v4 == 0 && v5 == 0) && v8 == 0))) {
            if (p2[5] > (word_t)0x9fffffffffffffff) return 0;
            if (p2[5] != 0x8000000000000000) return 0;
            if ((p2[6] != 0 || p2[7] != 0) || p2[0] != 0) return 0;
        } else if (v7 == 0x8000000000000000 &&
                   (((v3 == 0 && v6 == 0) && v13 == 0) && ((v4 == 0 && v5 == 0) && v8 == 0)) &&
                   (v2 == 1 || v2 == 2)) {
            if (p2[5] > (word_t)0x9fffffffffffffff) return 0;
            if (p2[6] != 0 || p2[7] != 0) return 0;
            if (p2[5] != 0x8000000000000000 || p2[0] != v2) return 0;
        } else {
            return 0;
        }
        /* validate the p2 object words (bytes of p2[3]/p2[4] OR-reduced) */
        {
            word_t l4 = (word_t)p2[4], l2 = (word_t)p2[3];
            byte o = 0;
            for (int i = 0; i < 8; i++) {
                o |= (byte)(l2 >> (8 * i)) | *(byte *)((word_t)p2 + 1 + i);
                o |= (byte)(l4 >> (8 * i)) | *(byte *)((word_t)p2 + 9 + i);
            }
            if (o != 0) return 0;
        }
        return sk_x_0006e064(0);
    default:
        if ((word_t)p2[5] >> 0x3d != 0) return 0;
        break;
    }
    if ((v6 & 0xff) == 1) { if ((char)p2[1] != 1) return 0; }
    else if ((char)p2[1] == 1 || v2 != p2[0]) return 0;
    if (((p2[2] ^ v3) >> 0xe) == 0) {
        v13 = (word_t)p2[3] ^ v13;
        if (v13 < 0x4000) return sk_x_0006e064(0);
    }
    return 0;
}

/* FUN_0041baa4 @ 0x0041baa4   (est. sk_ipc_msgwords_emit)
 * Ghidra: void FUN_0041baa4(void)
 * Emits a message-word set from the frame: maps the type and writes the cap
 * words with the null/one-hot encoding.
 * Confidence: low. */
static void sk_ipc_msgwords_emit_0041baa4(void)
{
    sk_x_0008e518();
    sword_t *x20 = (sword_t *)((word_t)0 + 0x20);
    sword_t v1 = x20[0];
    word_t v5 = (word_t)x20[1], v2 = (word_t)x20[2], v6 = (word_t)x20[3];
    sword_t v3 = x20[4];
    word_t v7 = (word_t)x20[5], v4 = (word_t)x20[6], v8 = (word_t)x20[7];
    word_t t;
    switch (v7 >> 0x3d) {
    case 3:
        sk_x_002298d4(6);
        if ((v5 & 0xff) == 1) sk_x_00229a3c(0);
        else { sk_x_00229a3c(1); sk_x_002298d4(v1); }
        sk_x_002298d4(v2 >> 0xe);
        sk_x_002298d4(v6 >> 0xe);
        if ((v7 & 0xff) == 1) sk_x_00229a3c(0);
        else { sk_x_00229a3c(1); sk_x_002298d4(v3); }
        sk_x_002298d4(v4 >> 0xe);
        goto LAB_msgwords_end;
    case 4:
        if (v7 == 0x8000000000000000 &&
            (((v2 == 0 && v5 == 0) && (v1 == 0 && v6 == 0)) &&
             ((v3 == 0 && v4 == 0) && v8 == 0))) t = 0;
        else if (v7 == 0x8000000000000000 && v1 == 1 &&
                 (((v2 == 0 && v5 == 0) && v6 == 0) && ((v3 == 0 && v4 == 0) && v8 == 0))) t = 1;
        else t = 2;
        sk_x_002298d4(t);
        goto LAB_msgwords_end;
    case 1: t = 4; break;
    case 2: t = 5; break;
    default: t = 3; break;
    }
    sk_x_002298d4(t);
    if ((v5 & 0xff) == 1) sk_x_00229a3c(0);
    else { sk_x_00229a3c(1); sk_x_002298d4(v1); }
    sk_x_002298d4(v2 >> 0xe);
    v8 = v6;
LAB_msgwords_end:
    sk_x_002298d4(v8 >> 0xe);
    sk_x_0008e500(0);
}

/* FUN_0041bc58 @ 0x0041bc58   (est. sk_ipc_emit_hook_e)
 * Ghidra: void FUN_0041bc58(void)
 * Emits via hook closure (unaff_x19 fn ptr), 004648fc snapshot.
 * Confidence: low. */
static void sk_ipc_emit_hook_e_0041bc58(void)
{
    byte frame[72];
    sk_x_004648fc();
    ((void (*)(byte *))((word_t)0 + 0x19))(frame);
    sk_x_001a8564();
}

/* FUN_0041bcb4 @ 0x0041bcb4   (est. sk_ipc_emit_hook_f)
 * Ghidra: void FUN_0041bcb4(void)
 * Emits via hook closure (unaff_x19 fn ptr), 004653c0 snapshot.
 * Confidence: low. */
static void sk_ipc_emit_hook_f_0041bcb4(void)
{
    byte frame[72];
    sk_x_004653c0();
    ((void (*)(byte *))((word_t)0 + 0x19))(frame);
    sk_x_001a8564();
}

/* FUN_0041bcf4 @ 0x0041bcf4   (est. sk_ipc_max_regs)
 * Ghidra: ulong FUN_0041bcf4(void)
 * Returns the message register limit (clamped to 3) from the config global.
 * Confidence: medium.
 * Notes: 0x67f928 config global. */
static word_t sk_ipc_max_regs_0041bcf4(void)
{
    sk_x_00356c6c();
    sk_x_002ad78c(0x67f928);
    sk_x_00465240();
    word_t n = (word_t)((word_t)0 + 0x20);
    if (n > 3) n = 3;
    return n;
}

/* FUN_0041bd34 @ 0x0041bd34   (est. sk_ipc_max_regs_store)
 * Ghidra: void FUN_0041bd34(undefined1*,undefined8*)
 * Stores the clamped register limit.
 * Confidence: medium. */
static void sk_ipc_max_regs_store_0041bd34(byte *out, word_t *p)
{
    byte u = sk_ipc_max_regs_0041bcf4();
    *out = u;
}

/* FUN_0041bd68 @ 0x0041bd68   (est. sk_ipc_cap_fetch)
 * Ghidra: void FUN_0041bd68(undefined1 (*)[16])
 * Fetches the capability via 0044bd08.
 * Confidence: low. */
static void sk_ipc_cap_fetch_0041bd68(cl4_pair_t *out)
{
    word_t *x20 = (word_t *)((word_t)0 + 0x20);
    cl4_pair_t v = sk_x_0044bd08(*x20);
    *out = v;
}

/* FUN_0041bdac @ 0x0041bdac   (est. sk_ipc_compare_frames)
 * Ghidra: undefined8 FUN_0041bdac(void)
 * Compares two syscall frames for IPC matching: message words (0041b820)
 * plus the right/object checks and the final object pair (00411308).
 * Returns 1 when they match.
 * Confidence: low. */
static word_t sk_ipc_compare_frames_0041bdac(void)
{
    sk_x_003504d0();
    word_t m = sk_ipc_msgwords_match_0041b820(0, 0);
    if ((((((m & 1) != 0) && (sk_x_00464ad0(), 0 == 0)) && (sk_x_0046622c(), 0 == 0)) &&
         ((*(byte *)((word_t)0 + 0x50) == *(byte *)((word_t)0 + 0x50) &&
          (sk_x_00464d0c(*(word_t *)((word_t)0 + 0x58)), 0 == 0)))) &&
        ((sk_x_00464d0c(*(word_t *)((word_t)0 + 0x60)), 0 == 0 &&
          ((m = sk_x_0041001c(*(word_t *)((word_t)0 + 0x68), *(word_t *)((word_t)0 + 0x68)),
           (m & 1) != 0 && (sk_x_00464d0c(*(word_t *)((word_t)0 + 0x70)), 0 == 0)))) &&
         (sk_x_00464d0c(*(word_t *)((word_t)0 + 0x78)), 0 == 0))) {
        return sk_x_00411308(*(word_t *)((word_t)0 + 0x80), *(word_t *)((word_t)0 + 0x80));
    }
    return 0;
}

/* FUN_0041be80 @ 0x0041be80   (est. sk_ipc_emit_compare_frame)
 * Ghidra: void FUN_0041be80(void)
 * Emits a compared frame (0041baa4 + cap words + checks).
 * Confidence: low. */
static void sk_ipc_emit_compare_frame_0041be80(void)
{
    sk_x_00464a38();
    word_t v = *(word_t *)((word_t)0 + 0x48);
    sk_ipc_msgwords_emit_0041baa4();
    sk_x_00466660();
    sk_x_002298d4(v >> 0xe);
    sk_x_0044929c();
    sk_x_00410414();
    v = *(word_t *)((word_t)0 + 0x78);
    sk_x_002298d4(*(word_t *)((word_t)0 + 0x70) >> 0xe);
    sk_x_002298d4(v >> 0xe);
    sk_x_0045811c();
}

/* FUN_0041bf18 @ 0x0041bf18   (est. sk_ipc_emit_hook_g)
 * Ghidra: void FUN_0041bf18(void)
 * Emits via hook closure (unaff_x19 fn ptr), 004648fc snapshot.
 * Confidence: low. */
static void sk_ipc_emit_hook_g_0041bf18(void)
{
    byte frame[72];
    sk_x_004648fc();
    ((void (*)(byte *))((word_t)0 + 0x19))(frame);
    sk_x_001a8564();
}

/* FUN_0041bf74 @ 0x0041bf74   (est. sk_ipc_emit_hook_h)
 * Ghidra: void FUN_0041bf74(void)
 * Emits via hook closure (unaff_x19 fn ptr), 004653c0 snapshot.
 * Confidence: low. */
static void sk_ipc_emit_hook_h_0041bf74(void)
{
    byte frame[72];
    sk_x_004653c0();
    ((void (*)(byte *))((word_t)0 + 0x19))(frame);
    sk_x_001a8564();
}

/* FUN_0041bfb4 @ 0x0041bfb4   (est. sk_ipc_badge_classify)
 * Ghidra: undefined1 [16] FUN_0041bfb4(void)
 * Classifies a badge word: returns the stored descriptor for most types, but
 * for the null/one-hot sentinel (0x8000000000000000) returns the reduced
 * 16-byte {index, 0} pair.
 * Confidence: low. */
static cl4_pair_t sk_ipc_badge_classify_0041bfb4(void)
{
    word_t *x20 = (word_t *)((word_t)0 + 0x20);
    word_t v = *(word_t *)(x20[2] + 8);
    switch (v >> 0x3d) {
    case 4:
        if (v == 0x8000000000000000 &&
            (*(sword_t *)x20[2] == 0 && *(sword_t *)(x20[0] + 8) == 0 &&
             *(sword_t *)x20[0] == 0 && *(sword_t *)(x20[3] + 8) == 0 &&
             *(sword_t *)x20[3] == 0 && *(sword_t *)(x20[1] + 8) == 0 && *(sword_t *)x20[1] == 0)) {
            v = 0;
        } else if (v == 0x8000000000000000 && *(sword_t *)x20[0] == 1 &&
                   (*(sword_t *)x20[2] == 0 && *(sword_t *)(x20[0] + 8) == 0 &&
                    *(sword_t *)(x20[3] + 8) == 0 && *(sword_t *)x20[3] == 0 &&
                    *(sword_t *)(x20[1] + 8) == 0 && *(sword_t *)x20[1] == 0)) {
            v = 1;
        } else {
            return (cl4_pair_t){ 0, 0 };
        }
        return (cl4_pair_t){ v, 0 };
    default:
        return *(cl4_pair_t *)x20;
    }
}
/* FUN_0041c0c0 @ 0x0041c0c0   (est. sk_ipc_frame_commit)
 * Ghidra: void FUN_0041c0c0(void)
 * Commits the syscall frame: builds the callback set, snapshots, and copies
 * the message words into the destination slot (stride 0x38).
 * Confidence: low.
 * Notes: callback table FUN_00455f60/000722b0/00456858/0045636c. */
static void sk_ipc_frame_commit_0041c0c0(void)
{
    cl4_pair_t v = sk_x_00466568();
    word_t *p = (word_t *)v.lo;
    sk_x_00458da0(p, 0);
    sk_x_004578dc((word_t)sk_x_00455f60, (word_t)sk_x_000722b0,
                  (word_t)sk_x_00456858, (word_t)sk_x_0045636c);
    sk_x_00463708();
    sk_x_00462b6c();
    sk_x_00457994();
    sk_x_00463ab8();
    word_t base = 0 + 0 * 0x38;
    word_t u3 = p[0], u4 = p[1], u5 = p[2], u6 = p[3], u7 = p[4], u8 = p[5];
    *(byte *)(base + 0x50) = *(byte *)(p + 6);
    *(word_t *)(base + 0x38) = u6;
    *(word_t *)(base + 0x30) = u5;
    *(word_t *)(base + 0x48) = u8;
    *(word_t *)(base + 0x40) = u7;
    *(word_t *)(base + 0x28) = u4;
    *(word_t *)(base + 0x20) = u3;
    *(word_t *)((word_t)0 + 0x20) = 0;
    sk_x_00466528(v.hi);
}

/* FUN_0041c190 @ 0x0041c190   (est. sk_ipc_frame_release2)
 * Ghidra: void FUN_0041c190(void)
 * Releases the frame's stored object and resets.
 * Confidence: medium. */
static void sk_ipc_frame_release2_0041c190(void)
{
    sk_x_0036b270(*(word_t *)((word_t)0 + 8));
    sk_x_0009461c();
}

/* FUN_0041c1c4 @ 0x0041c1c4   (est. sk_ipc_capdesc_write)
 * Ghidra: void FUN_0041c1c4(undefined8 x 8)
 * Writes a capability descriptor (8 words + tag byte).
 * Confidence: high. */
static void sk_ipc_capdesc_write_0041c1c4(word_t *d, word_t p2, word_t p3, word_t p4,
                                          word_t p5, byte p6, word_t p7, word_t p8)
{
    d[0] = p2;
    d[1] = p3;
    d[2] = p4;
    d[3] = p5;
    d[4] = p7;
    d[5] = p8;
    *(byte *)(d + 6) = p6;
}

/* FUN_0041c1d8 @ 0x0041c1d8   (est. sk_ipc_slot_scan)
 * Ghidra: undefined1 [16] FUN_0041c1d8(undefined8,undefined8,long)
 * Scans the message slot array for a matching cap; returns {index, found}.
 * Confidence: low.
 * Notes: stride 7 words; FUN_004633f4 = equality helper. */
static cl4_pair_t sk_ipc_slot_scan_0041c1d8(word_t a, word_t b, sword_t param3)
{
    sword_t n = *(sword_t *)(param3 + 0x10);
    if (n != 0) {
        sk_x_0035098c();
        sword_t i = 0;
        sword_t *slot = (sword_t *)(param3 + 0x28);
        do {
            if (*slot != 0 && (slot[-1] == 0 && *slot == 0 || (sk_x_004633f4(), 0 & 1))) {
                return (cl4_pair_t){ (word_t)i, 0 };
            }
            i++;
            slot += 7;
        } while (n != i);
    }
    return (cl4_pair_t){ 0, 1 };
}

/* FUN_0041c25c @ 0x0041c25c   (est. sk_ipc_ret_const)
 * Ghidra: undefined1 [16] FUN_0041c25c(void)
 * Returns the constant 16-byte value {0, 0x10f800}.
 * Confidence: high (trivial). */
static cl4_pair_t sk_ipc_ret_const_0041c25c(void)
{
    return (cl4_pair_t){ 0, 0x10f800 };
}

/* FUN_0041c26c @ 0x0041c26c   (est. sk_ipc_scan_nomatch)
 * Ghidra: bool FUN_0041c26c(void)
 * Runs the slot scan; returns the "not found" flag.
 * Confidence: low. */
static bool sk_ipc_scan_nomatch_0041c26c(void)
{
    sk_ipc_slot_scan_0041c1d8(0, 0, 0);
    sk_x_00351db4();
    return 0;   /* in_ZR-derived: not-found flag */
}

/* FUN_0041c270 @ 0x0041c270   (est. sk_ipc_scan_nomatch2)
 * Ghidra: bool FUN_0041c270(void)
 * Same slot-scan not-found test.
 * Confidence: low. */
static bool sk_ipc_scan_nomatch2_0041c270(void)
{
    sk_ipc_slot_scan_0041c1d8(0, 0, 0);
    sk_x_00351db4();
    return 0;
}

/* FUN_0041c28c @ 0x0041c28c   (est. sk_ipc_ret_flag)
 * Ghidra: undefined1 [16] FUN_0041c28c(uint)
 * Returns {0, param_1&1}.
 * Confidence: high (trivial). */
static cl4_pair_t sk_ipc_ret_flag_0041c28c(uint f)
{
    return (cl4_pair_t){ 0, f & 1 };
}

/* FUN_0041c29c @ 0x0041c29c   (est. sk_ipc_add_checked)
 * Ghidra: long FUN_0041c29c(long,undefined8,long)
 * Bounds-checked addition; traps on carry.
 * Confidence: high.
 * Notes: CL4_SW_BP(0x41c2ac). */
static sword_t sk_ipc_add_checked_0041c29c(sword_t p1, word_t p2, sword_t p3)
{
    if (!((sword_t)((word_t)p1 + (word_t)p3) < p1)) {
        return p1 + p3;
    }
    CL4_SW_BP(0x41c2ac);
    return 0;   /* unreachable: CL4_SW_BP traps */
}

/* FUN_0041c2ac @ 0x0041c2ac   (est. sk_ipc_add_pair)
 * Ghidra: undefined1 [16] FUN_0041c2ac(ulong,ulong,long)
 * Bounds-checked add returning the 16-byte {result, 0}; traps on carry when
 * the low bit of param_2 is set.
 * Confidence: medium. */
static cl4_pair_t sk_ipc_add_pair_0041c2ac(word_t p1, word_t p2, sword_t p3)
{
    bool carry = ((word_t)p1 + (word_t)p3) < p1;
    word_t sum = p1 + (word_t)p3;
    if ((p2 & 1) != 0 && carry) CL4_SW_BP(0x41c2c8);
    return (cl4_pair_t){ sum, 0 };
}

/* FUN_0041c2c8 @ 0x0041c2c8   (est. sk_ipc_check_increment)
 * Ghidra: void FUN_0041c2c8(undefined8,ulong,long)
 * Traps if the carry flag is set and param_3+1 overflows.
 * Confidence: medium. */
static void sk_ipc_check_increment_0041c2c8(word_t p1, word_t p2, sword_t p3)
{
    if ((p2 & 1) != 0 && p3 == (word_t)-1) CL4_SW_BP(0x41c2d8);
}

/* FUN_0041ca38 @ 0x0041ca38   (est. sk_ipc_frame_alloc_slot)
 * Ghidra: long FUN_0041ca38(void)
 * Allocates a new message slot in the frame's slot array (stride 0x38),
 * growing the array if needed, and initialises the slot's tag/cap words.
 * Returns the slot address.
 * Confidence: medium.
 * Notes: string ref 0x675c68 tag; global _DAT_005a1820; FUN_0041c2e4. */
static sword_t sk_ipc_frame_alloc_slot_0041ca38(void)
{
    sk_x_003a25d4(0);
    sk_x_00465488();
    sword_t base = sk_x_0045636c();
    word_t cnt = *(word_t *)(base + 0x10);
    if (*(word_t *)(base + 0x18) >> 1 <= cnt) {
        word_t g = sk_x_0006b42c();
        base = sk_x_0045636c(g, cnt + 1, 1);
    }
    *(word_t *)(base + 0x10) = cnt + 1;
    sword_t slot = base + cnt * 0x38;
    *(word_t *)(slot + 0x20) = 0;
    *(word_t *)(slot + 0x28) = 0;
    *(word_t *)(slot + 0x30) = 0x675c68;
    word_t g = _DAT_005a1820;
    *(word_t *)(slot + 0x40) = 0x5a1828;   /* uRam00000000005a1828 */
    *(word_t *)(slot + 0x38) = g;
    *(word_t *)(slot + 0x48) = 0xf;
    *(byte *)(slot + 0x50) = 1;
    word_t u = sk_x_003567c8();
    sk_ipc_obj_release_0041c2e4(u, 0, 0, 0, 1);
    return base;
}

/* FUN_0041cb78 @ 0x0041cb78   (est. sk_ipc_ret_f15)
 * Ghidra: undefined1 [16] FUN_0041cb78(void)
 * Returns the constant 16-byte value {0xf, 0xf}.
 * Confidence: high (trivial). */
static cl4_pair_t sk_ipc_ret_f15_0041cb78(void)
{
    return (cl4_pair_t){ 0xf, 0xf };
}

/* FUN_0041cb8c @ 0x0041cb8c   (est. sk_ipc_frame_compare)
 * Ghidra: undefined8 FUN_0041cb8c(void)
 * Compares two syscall frames for exact IPC match: the cap pointers, tag
 * bytes, and indexed cap words must all agree. Returns 1 when they match.
 * Confidence: low. */
static word_t sk_ipc_frame_compare_0041cb8c(void)
{
    sword_t l2 = (sword_t)sk_x_003504d0().lo;
    sword_t l4 = ((sword_t *)((word_t)0 + 0x19))[1];
    if (*(sword_t *)(l2 + 8) == 0) {
        if (l4 != 0) return 0;
        sk_x_003552a0();
        sk_x_00458da0();
    } else {
        if (l4 == 0) {
            sk_x_003552a0();
            sk_x_00458da0();
            return 0;
        }
        if ((*(sword_t *)((word_t)0 + 0x20) != *(sword_t *)((word_t)0 + 0x19) ||
             *(sword_t *)(l2 + 8) != l4) &&
            (sk_x_002a0cf8(), 0 & 1) == 0) {
            return 0;
        }
    }
    word_t *x20 = (word_t *)((word_t)0 + 0x20);
    word_t *x19 = (word_t *)((word_t)0 + 0x19);
    bool le = (word_t)x19[2] <= (word_t)x20[2];
    if (((x20[3] == x19[3]) && x20[2] == x19[2]) &&
        (sk_x_00464d0c(x20[4]), 0 == 0) && (sk_x_00465264(x19[5]), !le)) {
        return 1;
    }
    return 0;
}

/* FUN_0041cc48 @ 0x0041cc48   (est. sk_ipc_frame_compare2)
 * Ghidra: uint FUN_0041cc48(undefined8,undefined8*)
 * Wrapper: copies the frame words and runs 0041cb8c.
 * Confidence: low. */
static uint sk_ipc_frame_compare2_0041cc48(word_t p1, word_t *p2)
{
    word_t w[7];
    w[0] = p2[0]; w[1] = p2[1]; w[2] = p2[2]; w[3] = p2[3];
    w[4] = p2[4]; w[5] = p2[5];
    byte tag = *(byte *)(p2 + 6);
    return sk_ipc_frame_compare_0041cb8c() & 1;
}

/* FUN_0041cc98 @ 0x0041cc98   (est. sk_ipc_emit_tag_pair)
 * Ghidra: undefined1 [16] FUN_0041cc98(void)
 * Emits a tagged message pair: builds the 16-byte {msg, tag} result and
 * returns it.
 * Confidence: low. */
static cl4_pair_t sk_ipc_emit_tag_pair_0041cc98(void)
{
    word_t l58 = 0;
    word_t l50 = 0xe000000000000000;
    word_t u = *(word_t *)((word_t)0 + 0x10);
    cl4_pair_t v = sk_x_0046647c();
    sk_x_00465db0(v.lo, v.hi, v.lo);
    sk_x_0046299c();
    sk_x_00205844((byte *)&u, (byte *)&l58);
    word_t u2 = l50;
    word_t u1 = l58;
    sk_x_001ed960(0x3f, 0xe100000000000000, *(word_t *)((word_t)0 + 0x18));
    sk_x_000b43e8();
    l58 = u1;
    l50 = u2;
    sk_x_0036b270(u2);
    sk_x_000b4390();
    sk_x_002acbb8();
    sk_x_003a25d4(u2);
    sk_x_003a25d4();
    return (cl4_pair_t){ l58, l50 };
}

/* FUN_0041cd40 @ 0x0041cd40   (est. sk_ipc_emit_desc_array)
 * Ghidra: void FUN_0041cd40(void)
 * Emits an array of capability descriptors: walks the source slot array and
 * marshals each descriptor into the destination, then emits the summary.
 * Confidence: low (large multi-slot walk; unaffiliated in_x19 + opaque
 * extraout_x1 register-forwarding remain — verified against fresh decompile
 * + disassembly 2026-08-12: fixed unaff_x19 mis-modeled as 0 (now in_x19),
 * FUN_00205844 arg now &in20 (sp+0x20), extraout_x1 arg restored opaque,
 * descriptor-array base d = in_x19 + x22*0x10 corrected).
 * Notes: &DAT_004e80a0 template; string ref 0x656248. */
static void sk_ipc_emit_desc_array_0041cd40(void)
{
    cl4_pair_t v = sk_x_000b4594();
    sword_t n = *(sword_t *)(v.lo + 0x10);
    sword_t l1 = sk_x_000a6fe0();
    word_t in_x19;        /* unaffiliated x19: caller-supplied msg/ctx pointer (unaff_x19) */
    word_t extraout_x1;   /* decompiler register-forward from prior call (opaque) */
    word_t x22 = 0;
    word_t saved = 0;
    if (n != 0) {
        sk_x_004651a8();
        word_t *p = (word_t *)(l1 + 0x28);
        do {
            word_t in18 = p[0];
            word_t in20 = p[1];
            word_t in28 = p[2];
            word_t in30 = p[3];
            word_t in38 = p[4];
            word_t u2 = p[2];
            sk_x_0036b270(p[0]);
            cl4_pair_t t = sk_x_00002534(0x656248, (word_t)&DAT_004e80a0);
            sk_x_0046299c(t.lo, t.hi, t.lo);
            sk_x_00205844((byte *)&in20);
            sk_x_001ed960(0x3f, 0xe100000000000000, u2);
            sk_x_0036b270(0xe000000000000000);
            sk_x_00350a04();
            sk_x_002acbb8();
            sk_x_003a25d4(0xe000000000000000);
            sk_x_003a25d4(extraout_x1);
            sk_x_003a25d4(in18);
            x22 = *(word_t *)(in_x19 + 0x10);
            if (*(word_t *)(in_x19 + 0x18) >> 1 <= x22) {
                sk_x_0006a374(1 < *(word_t *)(in_x19 + 0x18), x22 + 1, 1);
            }
            p += 7;
            *(word_t *)(in_x19 + 0x10) = x22 + 1;
            sword_t d = in_x19 + x22 * 0x10;
            *(word_t *)(d + 0x20) = 0;
            *(word_t *)(d + 0x28) = 0xe000000000000000;
            saved = in18;
            n--;
        } while (n != 0);
    }
    sk_x_00463210();
    word_t u2 = sk_x_00462898();
    sk_x_001bc440(0x202c, 0xe200000000000000, x22, u2);
    sk_x_000b43e8();
    sk_x_0036b118(in_x19);
    sk_x_00465800(0x28);
    sk_x_000b4390();
    sk_x_002acbb8();
    sk_x_003a25d4(x22);
    sk_x_0036b270(saved);
    sk_x_00100e34();
    sk_x_002acbb8();
    sk_x_003a25d4(saved);
    sk_x_000b45b0(in_x19, saved, v.hi);
}

/* FUN_0041cf18 @ 0x0041cf18   (est. sk_ipc_match_object)
 * Ghidra: void FUN_0041cf18(8 args)
 * Recursive IPC object match: compares the caller's and callee's cap object
 * pairs (00084220), handling the tag byte (0 = compare address words, 1 =
 * compare object payloads, 2 = release-and-compare). Returns the match flag.
 * Confidence: low (recursive register-fragment path).
 * Notes: noreturn-free; FUN_004114fc = release helper. */
static void sk_ipc_match_object_0041cf18(word_t p1, word_t p2, sword_t p3, word_t p4,
                                         word_t p5, word_t p6, sword_t p7, word_t p8)
{
    cl4_pair_t v = sk_x_00084220();
    cl4_pair_t w = { p5, p6 };
    uint r = 0;
    if ((p4 & 0xff) == 0) {
        if ((p8 & 0xff) == 0) {
            if (v.hi == 0) {
                if (p6 == 0) goto LAB_match_obj_ok;
            } else if (p6 != 0) {
                if ((word_t)v.lo != p5) {
                    sk_x_00354828();
                    if ((sk_x_002a0cf8(), 0 & 1) == 0) goto LAB_match_obj_no;
                }
LAB_match_obj_ok:
                if (p3 == 0) {
                    if (p7 == 0) goto LAB_match_obj_yes;
                } else if (p7 != 0 && p3 == p7) {
LAB_match_obj_yes:
                    r = 1;
                    goto LAB_match_obj_done;
                }
            }
        }
LAB_match_obj_no:
        r = 0;
    } else {
        if ((p4 & 0xff) == 1) {
            if ((p8 & 0xff) != 1) goto LAB_match_obj_no;
            word_t u1 = *(word_t *)(v.lo + 0x20);
            word_t u7 = *(word_t *)(p5 + 0x10);
            word_t u2 = *(word_t *)(p5 + 0x18);
            word_t u8 = *(word_t *)(p5 + 0x20);
            byte u3 = *(byte *)(p5 + 0x28);
            byte u4 = *(byte *)(v.lo + 0x28);
            sk_x_0034d868();
            sk_x_00460d94();
            cl4_pair_t rv = sk_x_000b43d0();
            sk_ipc_match_object_0041cf18(rv.lo, rv.hi, u1, u4, u7, u2, u8, u3);
            sk_x_0034d868();
            sk_x_00458e80();
        } else {
            if ((p8 & 0xff) != 2) goto LAB_match_obj_no;
            word_t u7 = *(word_t *)(p5 + 0x10);
            sk_x_0036b270(u7);
            sk_x_0009461c();
            r = sk_x_004114fc();
            sk_x_0036b118(u7);
        }
        r = r & 1;
    }
LAB_match_obj_done:
    sk_x_00084234(r, 0);
}

/* FUN_0041d070 @ 0x0041d070   (est. sk_ipc_emit_payload)
 * Ghidra: void FUN_0041d070(void)
 * Emits a payload span: if the register count is not the terminal value and
 * the destination slot array is non-empty, emits via 0041d180.
 * Confidence: low.
 * Notes: unreachable block warning at 0x41d148. */
static void sk_ipc_emit_payload_0041d070(void)
{
    sk_x_00354744();
    uint u1 = (uint)0;
    sk_x_00351dc0();
    u1 = (uint)0;
    sk_x_003504d0();
    sk_x_0035053c();
    sk_x_002cb61c();
    if ((u1 & 0xff) != 2 || *(sword_t *)(*(sword_t *)((word_t)0 + 0x10) + 0x10) != 0) {
        cl4_pair_t v = sk_x_00350518();
        sk_ipc_encode_payload_0041d180(v.lo, v.hi, 0, 0, 1, 0, 0, 0);
    }
    sk_x_0035053c(0, 2);
    sk_ipc_emit_reset_0041d14c(0, 0, 0, 0);
    sk_x_003544c8(0);
}

/* FUN_0041d14c @ 0x0041d14c   (est. sk_ipc_emit_reset)
 * Ghidra: void FUN_0041d14c(undefined1,long,long,long)
 * Bounds-checked single-byte store into the destination span; traps on
 * out-of-range indices.
 * Confidence: high.
 * Notes: CL4_SW_BP at 0x41d178/0x41d17c/0x41d180. */
static void sk_ipc_emit_reset_0041d14c(byte val, sword_t idx, sword_t base, sword_t end)
{
    if (idx < 0) CL4_SW_BP(0x41d178);
    if (idx != (word_t)-1) {
        sword_t len = 0;
        if (base != 0) len = end - base;
        if (idx + 1 <= len) {
            *(byte *)(base + idx) = val;
            return;
        }
        CL4_SW_BP(0x41d180);
    }
    CL4_SW_BP(0x41d17c);
}

/* FUN_0041d180 @ 0x0041d180   (est. sk_ipc_encode_payload)
 * Ghidra: void FUN_0041d180(8 args)
 * Encodes a payload into the destination span: the tag selects the format
 * (0 = empty/single-cap, 1 = full cap, else the multi-word descriptor),
 * writing bytes via 0041d14c and growing the destination.
 * Confidence: low (large encoding tree).
 * Notes: string "Cannot encode a capture structure" at 0x005e1f50; noreturn
 *   FUN_001afa84. */
static void sk_ipc_encode_payload_0041d180(word_t p1, word_t p2, sword_t p3, word_t p4,
                                           uint p5, word_t p6, word_t p7, sword_t *p8)
{
    cl4_pair_t v = sk_x_00351e20();
    sword_t l6;
    uint tag = (uint)p4 & 0xff;
    byte u3 = 0;
    if ((p4 & 0xff) == 0) {
        if (p3 != 0) {
            sk_x_00002874(0x005e1f50);   /* "Cannot encode a capture structure" */
            sk_x_003593c0();
            sk_x_00002818();
            sk_x_001afa84();   /* does not return */
        }
        if (v.hi == 0) {
            sk_x_003523fc(1, *p8);
            sk_ipc_emit_reset_0041d14c(0, 0, 0, 0);
            sk_x_00465d3c();
            if (u3) CL4_SW_BP(0x41d350);
        } else {
            sk_x_003523fc(2, *p8);
            sk_ipc_emit_reset_0041d14c(0, 0, 0, 0);
            l6 = *p8 + 1;
            if (*p8 == (word_t)-1) CL4_SW_BP(0x41d398);
            *p8 = l6;
            sk_x_00350470();
            sword_t l9 = sk_x_00268540();
            sword_t l5 = *(sword_t *)(l9 + 0x10);
            if (l6 == (word_t)-1) CL4_SW_BP(0x41d39c);
            if (l6 + l5 < l6) CL4_SW_BP(0x41d3a0);
            sk_x_003523fc(l6);
            cl4_pair_t av = sk_x_003207d4();
            l6 = 0;
            if (p3 != 0) l6 = p3 + (sword_t)av.lo;
            sword_t l4 = av.hi - av.lo;
            if (l4 < 0) CL4_SW_BP(0x41d3a4);
            if (l4 != 0) {
                if (l6 == 0) CL4_SW_BP(0x41d3b0);
                l4 = l6 + l4;
            } else if (l6 != 0) {
                goto LAB_enc_memcpy;
            }
LAB_enc_memcpy:
            sk_x_002cb61c(l9 + 0x20, l9 + 0x20 + *(sword_t *)(l9 + 0x10), l6, l4);
            sk_x_0036b118(l9);
            l6 = *p8 + l5;
            if (*p8 == (word_t)-1) CL4_SW_BP(0x41d3a8);
        }
    } else {
        u3 = (uint)(tag - 1) != 0;   /* SBORROW4 */
        if (tag == 1) {
            word_t u8 = *(word_t *)(v.lo + 0x10);
            sk_x_00350b18(u8);
            sk_x_00460d94();
            sk_x_00350b18(u8);
            sk_x_00466580();
            sk_x_00350b18(u8);
            sk_x_00458e80();
            sk_x_003523fc(4, *p8);
            sk_ipc_emit_reset_0041d14c(0, 0, 0, 0);
            sk_x_00465d3c();
            if (u3) CL4_SW_BP(0x41d210);
        } else {
            l6 = *(sword_t *)(v.lo + 0x10);
            if ((p5 & 1) == 0) {
                sk_x_003523fc(5, *p8);
                sk_ipc_emit_reset_0041d14c(0, 0, 0, 0);
                sk_x_00465d3c();
                if (u3) CL4_SW_BP(0x41d3ac);
                *p8 = 0;
                u3 = 0;
            }
            sword_t l9 = *(sword_t *)(l6 + 0x10);
            if (l9 != 0) {
                sk_x_0036b270(l6);
                byte *p = (byte *)(l6 + 0x38);
                do {
                    word_t u8 = *(word_t *)(p - 8);
                    byte ub = *p;
                    cl4_pair_t a1 = sk_x_000dbd0c();
                    sk_x_00460d94(a1.lo, a1.hi, u8, ub);
                    a1 = sk_x_000dbd0c();
                    sk_x_00466580(a1.lo, a1.hi, u8, ub);
                    a1 = sk_x_000dbd0c();
                    sk_x_00458e80(a1.lo, a1.hi, u8, ub);
                    l9--;
                    p += 0x20;
                } while (l9 != 0);
                sk_x_0036b118(l6);
            }
            if ((p5 & 1) == 0) {
                sk_x_003523fc(6, *p8);
                sk_ipc_emit_reset_0041d14c(0, 0, 0, 0);
                sk_x_00465d3c();
                if (u3) CL4_SW_BP(0x41d338);
            } else {
                goto LAB_enc_done;
            }
        }
    }
    *p8 = l6;
LAB_enc_done:
    sk_x_00351d30(0);
}

/* FUN_0041d3e8 @ 0x0041d3e8   (est. sk_ipc_frame_release_slot)
 * Ghidra: void FUN_0041d3e8(void)
 * Releases one slot from the frame's slot array (decrements the count).
 * Confidence: medium.
 * Notes: CL4_SW_BP(0x41d430) on empty array. */
static void sk_ipc_frame_release_slot_0041d3e8(void)
{
    sword_t *x20 = *(sword_t **)((word_t)0 + 0x20);
    if (*(sword_t *)(x20 + 0x10) == 0) CL4_SW_BP(0x41d430);
    if (sk_x_004613d4() != 0) {
        return;
    }
    sk_x_0046134c(*(sword_t *)(*x20 + 0x10) + -1);
}

/* FUN_0041d430 @ 0x0041d430   (est. sk_ipc_frame_emit_final)
 * Ghidra: void FUN_0041d430(undefined8 x 4)
 * Final frame emit: sets up the tag pair and emits the descriptor array.
 * Confidence: low.
 * Notes: globals _DAT_004be5e0/uRam00000000004be5e8. */
static void sk_ipc_frame_emit_final_0041d430(word_t p1, word_t p2, word_t p3, word_t p4)
{
    byte frame[32];
    word_t l68 = _DAT_004be5e0;
    word_t u60 = 0x4be5e8;
    word_t l58 = 0xe000000000000000;
    sk_x_00463998(p1, p1, p2, p3, p4);
    u60 = 0x4be5e8;
    l68 = _DAT_004be5e0;
    l58 = 0xe000000000000000;
    sk_x_00463600();
    sk_ipc_frame_emit_slot_0041d4a4((sword_t)((word_t)&frame), 0, 0, 0, 0);
    u60 = 0;
    l58 = 0xe000000000000000;
    sk_x_004590e0((byte *)&frame);
    sk_x_0009461c();
}

/* FUN_0041d4a4 @ 0x0041d4a4   (est. sk_ipc_frame_emit_slot)
 * Ghidra: void FUN_0041d4a4(long,long,long,long,char)
 * Recursive message-slot emitter: walks the descriptor tree and emits each
 * word, with the param_5 mode selecting the formatting (0 = object, 1 =
 * slot-list, else the 0x38 frame slot). Traps on count overflows.
 * Confidence: low (large recursive emitter).
 * Notes: string refs 0x657ae0/&DAT_005a3520; hex words 0x64656d616e6e753c
 *   ("<nunamed"), 0x65736c6166 ("false"); noreturn not present. */
static void sk_ipc_frame_emit_slot_0041d4a4(sword_t p1, sword_t p2, sword_t p3, sword_t p4, char p5)
{
    word_t u5 = 0;
    if (p5 == 0) {
        sword_t l6 = 0xe90000000000003e;
        sword_t l4 = l6;
        if (p3 != 0) l4 = p3;
        if (p4 == 0) {
            sk_x_00460d94(0x64656d616e6e753c, p2, p3, 0);
        } else {
            word_t lo[3];
            lo[1] = 0;
            lo[2] = 0xe000000000000000;
            lo[0] = (word_t)p4;
            sk_x_00460d94(p2, p3, p4, 0);
            cl4_pair_t t = sk_x_00002534(0x657ae0, (word_t)&DAT_005a3520);
            sk_x_00465db0(t.lo, t.hi, t.lo);
            sk_x_0046299c();
            sk_x_00205844((byte *)lo, (byte *)(lo + 1));
            l6 = (sword_t)lo[2];
        }
        sk_x_00465800(0x286d6f7441);
        sk_x_00100efc();
        sk_x_002acbb8();
        sk_x_003a25d4(l4);
        sk_x_002acbb8(0x203a, 0xe200000000000000);
        sk_x_00350518();
        sk_x_002acbb8();
        sk_x_003a25d4(l6);
        sk_x_00100e34();
        sk_x_002acbb8();
        l4 = 0;   /* local_68[2] */
        sk_x_0044ca60();
        sk_x_0036b270(l4);
        sk_x_000b4390();
        sk_x_002acbb8();
        sk_x_003a25d4(l4);
        sk_x_00463af8();
        sk_x_003a25d4(l4);
    } else {
        if (p5 == 1) {
            word_t u8 = *(word_t *)(p2 + 0x20);
            byte u3 = *(byte *)(p2 + 0x28);
            cl4_pair_t t = sk_x_000b4390();
            sk_x_00460d94(t.lo, t.hi, u8, u3);
            sk_x_0044ca60();
            sk_x_002acbb8(0x6c616e6f6974704f, 0xea00000000007b20);
            sk_x_00463af8();
            sk_x_004645ec();
            bool over = *(sword_t *)(p1 + 0x40) == (word_t)-1;
            *(sword_t *)(p1 + 0x40) = *(sword_t *)(p1 + 0x40) + 1;
            sk_x_0034c444(p1);
            sk_ipc_frame_emit_slot_0041d4a4(0, 0, 0, 0, 0);
            t = sk_x_000b4390();
            sk_x_00458e80(t.lo, t.hi, u8, u3);
            sk_x_00465d1c();
            u5 = 0;
            if (over) CL4_SW_BP(0x41d560);
        } else {
            sword_t l4 = *(sword_t *)(p2 + 0x10);
            sk_x_0036b270(l4);
            sk_x_0044ca60();
            sk_x_002acbb8(0x7b20656c707554, 0xe700000000000000);
            sk_x_00463af8();
            sk_x_004645ec();
            if (*(sword_t *)(p1 + 0x40) == (word_t)-1) CL4_SW_BP(0x41d774);
            *(sword_t *)(p1 + 0x40) = *(sword_t *)(p1 + 0x40) + 1;
            sword_t n = *(sword_t *)(l4 + 0x10);
            byte u3 = 0;
            if (n != 0) {
                sword_t p7 = l4 + 0x38;
                do {
                    word_t u8 = *(word_t *)(p7 - 0x18);
                    p7 += 0x20;
                    sk_x_003505c4(u8);
                    sk_x_00460d94();
                    sk_x_0009461c();
                    sk_x_003511f0();
                    sk_ipc_frame_emit_slot_0041d4a4(0, 0, 0, 0, 0);
                    sk_x_003505c4(u8);
                    sk_x_00458e80();
                    n--;
                } while (n != 0);
            }
            sk_x_0036b118(l4);
            sk_x_00465d1c();
            u5 = 0;
        }
        *(word_t *)(p1 + 0x40) = u5;
        sk_x_0044ca60();
        sk_x_00463878();
        sk_x_002acbb8();
        sk_x_00463af8();
    }
    sk_x_004645ec();
}

/* FUN_0041d778 @ 0x0041d778   (est. sk_ipc_frame_swap_cap)
 * Ghidra: undefined1 [16] FUN_0041d778(void)
 * Swaps the frame's stored cap pair, returning the old value.
 * Confidence: medium. */
static cl4_pair_t sk_ipc_frame_swap_cap_0041d778(void)
{
    cl4_pair_t old = *(cl4_pair_t *)((word_t)0 + 0x28);
    *(word_t *)((word_t)0 + 0x28) = 0;
    *(word_t *)((word_t)0 + 0x30) = 0xe000000000000000;
    return old;
}

/* FUN_0041d788 @ 0x0041d788   (est. sk_ipc_frame_emit_tail)
 * Ghidra: void FUN_0041d788(void)
 * Emits the frame tail and releases.
 * Confidence: low. */
static void sk_ipc_frame_emit_tail_0041d788(void)
{
    sk_x_003509ec();
    sk_x_0044ca60();
    sk_x_0036b270();
    sk_x_00100efc();
    sk_x_002acbb8();
    sk_x_003a25d4();
    sk_x_00463af8();
    sk_x_004645ec();
}
/* FUN_0041c2e4 @ 0x0041c2e4   (est. sk_ipc_obj_release)
 * Ghidra: void FUN_0041c2e4(undefined8,undefined8,ulong,long,byte)
 * The core object-release / teardown dispatcher for the message/cap objects.
 * The frame tag (from 0008e518) selects the object kind:
 *  - kind 0/1: walk the object's slot array releasing each element
 *  - kind 2: the 0x50-byte frame teardown (release the stored object and
 *    run the callback set)
 *  - kind 3: the 0x90-byte descriptor teardown (release cap words)
 *  - kind 4: the 0x78-byte cap-object teardown
 *  - kind 10: special "in-use" bit clear
 * Confidence: low (large multi-kind teardown).
 * Notes: callback table FUN_00455f60/000722b0/00456858/0045636c; global
 *   DAT_00658c80 dispatch slot. */
static void sk_ipc_obj_release_0041c2e4(word_t p1, word_t p2, word_t p3, sword_t p4, byte p5)
{
    cl4_pair_t v = sk_x_0008e518();
    sword_t l11 = v.hi;
    word_t u9 = v.lo;
    uint u7 = (uint)p3;
    word_t u8 = 0, u10 = 0, u5 = 0, u6 = 0, u1 = 0;
    switch (u9 >> 0x3c) {
    case 0:
        u9 = *(word_t *)(u9 + 0x10);
        l11 = *(sword_t *)(u9 + 0x10);
        if (l11 != 0) {
            sk_x_0036b270(u9);
            word_t idx = 0x20;
            do {
                if ((u7 & 1) && p4 == (word_t)-1) CL4_SW_BP(0x41c9e0);
                word_t e = *(word_t *)(u9 + idx);
                cl4_pair_t r = sk_x_0036b270(e & 0xfffffffffffffff);
                sk_x_00464308(r.lo, r.hi, u7 & 1);
                sk_ipc_obj_release_0041c2e4(0, 0, 0, 0, 0);
                sk_x_0036b118(e & 0xfffffffffffffff);
                idx += 8;
                l11--;
            } while (l11 != 0);
        }
        goto LAB_objrel_c89c;
    case 1:
        u9 = *(word_t *)((u9 & 0xfffffffffffffff) + 0x10);
        l11 = *(sword_t *)(u9 + 0x10);
        if (l11 != 0) {
            sk_x_0036b270(u9);
            word_t idx = 0x20;
            do {
                word_t e = *(word_t *)(u9 + idx);
                cl4_pair_t r = sk_x_0036b270(e & 0xfffffffffffffff);
                sk_x_00464308(r.lo, r.hi, u7 & 1);
                sk_ipc_obj_release_0041c2e4(0, 0, 0, 0, 0);
                sk_x_0036b118(e & 0xfffffffffffffff);
                idx += 8;
                l11--;
            } while (l11 != 0);
        }
        goto LAB_objrel_c89c;
    case 2:
        sk_x_00117cc4(&l11, (u9 & 0xfffffffffffffff) + 0x10, 0x68);
        u8 = *(word_t *)((u9 & 0xfffffffffffffff) + 0x78);
        {
            byte state = *(byte *)((word_t)&l11 + 0x50);
            sword_t frame_slot = *(sword_t *)((word_t)&l11 + 0x10);
            if (state == 0) {
                if (p4 == (word_t)-1) CL4_SW_BP(0x41c9f0);
                sk_x_00464f58();
                sk_x_00351aec();
                sk_x_0045908c();
                sk_x_00464f58();
                sk_x_00351aec();
                sk_x_0045908c();
                sk_x_0036b270();
                sk_x_004578dc((word_t)sk_x_00455f60, (word_t)sk_x_000722b0,
                              (word_t)sk_x_00456858, (word_t)sk_x_0045636c);
                word_t u4 = sk_x_00463708();
                sk_x_00457994(u4, (word_t)sk_x_00455f60, (word_t)sk_x_000722b0,
                              (word_t)sk_x_00456858, (word_t)sk_x_0045636c);
                sk_x_00465a14();
                sk_x_00463ab8();
                *(word_t *)(0 + 0x13c05da0) = (word_t)l11;
                *(word_t *)(0 + 0x13c05da8) = 0;
                sk_x_004652f4();
                l11 = 0;
                sword_t slot = 0;
                *(byte *)(slot + 0x50) = p5 & 1;
                *(sword_t *)((word_t)0 + 0x20) = l11;
            } else if (state == 1) {
                if (p4 == (word_t)-1) CL4_SW_BP(0x41c9ec);
                word_t u4 = 0;
                if (frame_slot != 0) u4 = (word_t)l11;
                sk_x_004637b4();
                sk_x_00464f58();
                sk_x_0045908c();
                sk_x_0036b270();
                sk_x_0036b270((word_t)frame_slot);
                sk_x_004578dc((word_t)sk_x_00455f60, (word_t)sk_x_000722b0,
                              (word_t)sk_x_00456858, (word_t)sk_x_0045636c);
                sword_t cnt = *(sword_t *)(*(sword_t *)((word_t)0 + 0x20) + 0x10);
                sk_x_004632a4();
                sk_x_00457994();
                sk_x_00465a14();
                sk_x_00463ab8();
                sword_t base = 0 + cnt * 0x38;
                *(word_t *)(base + 0x20) = u4;
                *(sword_t *)(base + 0x28) = frame_slot;
                sk_x_004652f4();
                l11 = 0;
                sword_t slot = 0;
                *(byte *)(slot + 0x50) = p5 & 1;
                *(sword_t *)((word_t)0 + 0x20) = l11;
            } else if (state == 3) {
                sword_t chk = sk_x_00463558(*(word_t *)((word_t)&l11 + 0x38),
                                            *(word_t *)((word_t)&l11 + 0x30),
                                            *(word_t *)((word_t)&l11 + 0x10),
                                            *(word_t *)((word_t)&l11 + 0x20));
                if (chk == 0 && 0 == 0 && frame_slot == 0) {
                    if (p4 == (word_t)-1) CL4_SW_BP(0x41c9f4);
                    sk_x_004637b4();
                    sk_x_00464f58();
                    sk_x_0045908c();
                    sk_x_0036b270();
                    sk_x_003a25d4(0);
                    sk_x_004578dc((word_t)sk_x_00455f60, (word_t)sk_x_000722b0,
                                  (word_t)sk_x_00456858, (word_t)sk_x_0045636c);
                    sword_t cnt = *(sword_t *)(*(sword_t *)((word_t)0 + 0x20) + 0x10);
                    sk_x_00353bc4(cnt, (word_t)sk_x_00455f60, (word_t)sk_x_000722b0);
                    sk_x_00457994();
                    sword_t base = *(sword_t *)((word_t)0 + 0x20);
                    *(sword_t *)(base + 0x10) = cnt + 1;
                    base = base + cnt * 0x38;
                    *(word_t *)(base + 0x20) = 0;
                    *(word_t *)(base + 0x28) = 0;
                    sk_x_004652f4();
                    l11 = 0;
                    sword_t slot = 0;
                    *(byte *)(slot + 0x50) = p5 & 1;
                    *(sword_t *)((word_t)0 + 0x20) = l11;
                } else {
                    sk_x_0036b270(u8 & 0xfffffffffffffff);
                }
            } else {
                sk_x_0036b270(u8 & 0xfffffffffffffff);
            }
        }
        sk_x_00464d68();
        sk_x_003505e8();
        sk_ipc_obj_release_0041c2e4(0, 0, 0, 0, 0);
        goto LAB_objrel_c9c0;
    case 3:
        u9 = u9 & 0xfffffffffffffff;
        sk_x_00117cc4(&l11, u9 + 0x20, 0x90);
        u10 = *(word_t *)(u9 + 0xb0);
        u8 = *(word_t *)(u9 + 0xd0);
        sk_x_00117cc4((byte *)&l11 + 0x18, u9 + 0x20, 0x80);
        if (sk_x_00458cb8(&l11) == 3) {
            word_t u4 = sk_x_00458cd4((byte *)&l11 + 0x18);
            sk_x_00465884(0x67f9a0);
            word_t u9b = sk_x_0036a940();
            sk_x_00117cc4(u9b + 0x10, u4, 0x80);
            sk_x_00464f58();
            sk_x_00458c98();
            sk_x_00464f58();
            sk_x_00458c98();
            sk_x_0036b270(u8 & 0xfffffffffffffff);
            sk_x_0036b270(u10 & 0xfffffffffffffff);
            word_t u4b = sk_x_00464d68(u9b | 0x2000000000000000);
            sk_ipc_obj_release_0041c2e4(u4b, l11, 0, 0, 0);
            sk_x_0036b118(u9b);
            sk_x_00458e28(&l11);
            if ((p3 & 1) == 0) goto LAB_objrel_drop;
        } else {
            sk_x_0036b270(u8 & 0xfffffffffffffff);
            sk_x_0036b270(u10 & 0xfffffffffffffff);
            if ((p3 & 1) == 0) goto LAB_objrel_drop;
            if (p4 == (word_t)-1) CL4_SW_BP(0x41c9e4);
            sk_x_0006b6a0(u10);
        }
        sk_ipc_obj_release_0041c2e4(0, 0, 0, 0, 0);
        sk_x_0036b118(u10 & 0xfffffffffffffff);
        sk_x_00464d68();
        sk_x_003514e8();
        sk_ipc_obj_release_0041c2e4(0, 0, 0, 0, 0);
        goto LAB_objrel_c9c0;
    case 4:
        u9 = u9 & 0xfffffffffffffff;
        u10 = *(word_t *)(u9 + 0x10);
        u1 = *(word_t *)(u9 + 0x18);
        u8 = *(word_t *)(u9 + 0x78);
        u5 = *(word_t *)(u9 + 0x38);
        u6 = 0;
        if ((u5 >> 0x3d) == 4) {
            if (u5 == 0x8000000000000000 && u1 == 0 && u10 == 0 &&
                *(sword_t *)(u9 + 0x48) == 0 && *(sword_t *)(u9 + 0x40) == 0 &&
                *(sword_t *)(u9 + 0x30) == 0 && *(sword_t *)(u9 + 0x28) == 0 &&
                *(sword_t *)(u9 + 0x20) == 0) {
                u6 = 0;
            } else {
                u6 = (word_t)((u10 == 1 && u1 == 0 && *(sword_t *)(u9 + 0x48) == 0 &&
                              *(sword_t *)(u9 + 0x40) == 0 && *(sword_t *)(u9 + 0x30) == 0 &&
                              *(sword_t *)(u9 + 0x28) == 0 && *(sword_t *)(u9 + 0x20) == 0) &&
                             u5 == 0x8000000000000000);
            }
        } else {
            u6 = u10;
            if ((u1 & 0xff) == 1 && u6 == 0 && (p3 & 1) != 0 && p4 == (word_t)-1)
                CL4_SW_BP(0x41c9e8);
        }
        sk_x_0036b270(u8 & 0xfffffffffffffff);
        sk_x_00464d68();
        sk_x_003514e8();
        sk_ipc_obj_release_0041c2e4(0, 0, 0, 0, 0);
        u8 = u8 & 0xfffffffffffffff;
        goto LAB_objrel_c89c;
    case 10:
        u8 = *(word_t *)((u9 & 0xfffffffffffffff) + 0x38);
        if ((u8 & 6) == 2) {
            sk_x_0036b270(u8 & 0xffffffffffffff9);
            word_t u4b = sk_x_00464d68(u8 & 0xfffffffffffffff9);
            sk_ipc_obj_release_0041c2e4(u4b, l11, 0, 0, 0);
            u8 = u8 & 0xffffffffffffff9;
            goto LAB_objrel_c89c;
        }
        break;
    case 5: case 6: case 7: case 8: case 9: case 0xb:
        break;
    }
    /* default / fall-through epilogue */
    sk_x_0008e500(0);
    return;
LAB_objrel_c89c:
    sk_x_0008e500(u8, 0);
    sk_x_0036b118();
    return;
LAB_objrel_c9c0:
    sk_x_0036b118(u8 & 0xfffffffffffffff);
    sk_x_0008e500(u8, 0);
    sk_x_0036b118();
    return;
LAB_objrel_drop:
    sk_x_0008e500(0);
}
