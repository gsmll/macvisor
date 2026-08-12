/* Recreated from cl4_kernel.raw (cL4 microkernel, arm64e, image base 0).
 * Ground truth: Ghidra FUN_ names + addresses. Names use cL4/seL4 vocabulary; estimates unless matched.
 *
 * Slice R61: 0x003fdfe8-0x00404a7c (120 functions). A dense cluster of cL4
 * message/object serialization + dispatch wrappers. Many are tiny forwarders that
 * run a common per-cpu/refcount prologue (sk_rt_0034fc7c/0034d724, sk_rt_0040654c,
 * sk_rt_00377824) then dispatch through a vtable method pointer at x16+<offset> or
 * tail-call a sibling. A substantial subset is the Swift-runtime string/byte-buffer
 * encoder: width-selection by shift (FUN_004008c0 / 00400b3c choose byte/short/word
 * stores against the 0x1000/0x1001 length thresholds), which match the Swift UTF-8/
 * ASCII store helpers seen in slices R50/R54.
 *
 * The decompiler frequently recovered only register artifacts (extraout_x16/x8/x9,
 * unaff_x19/x20, unaff_w20) because these helpers read the caller's saved message
 * words off the stack (the cL4 message-passing-on-stack idiom) or the vtable slot
 * from a caller-held register. Where the body is not fully reconstructable the
 * signature is preserved and the register source is documented in a note; those
 * entries are confidence low.
 *
 * Confidence: low-medium (register-artifact wrappers; no string/header matches in
 * this slice).
 */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include "sk_internal.h"

/* 128-bit word-pair used by the 16-byte-return runtime helpers. */
typedef struct sk_u128 { word_t lo; word_t hi; } sk_u128_t;

/* ---- shared cL4 runtime helpers referenced by this slice (defined elsewhere in
 * the cL4 tree; FUN_ address preserved in the trailing comment). Declared with
 * empty parens (K&R unspecified args) so any call arity compiles. ---- */
extern uint64_t sk_rt_00019858();                                /* FUN_00019858 */
extern uint64_t sk_rt_00021480();                                /* FUN_00021480 */
extern uint64_t sk_rt_00027614();                                /* FUN_00027614 */
extern sk_u128_t sk_rt_00027670();                                /* FUN_00027670 */
extern uint64_t sk_rt_00027754();                                /* FUN_00027754 */
extern uint64_t sk_rt_0006b6f4();                                /* FUN_0006b6f4 */
extern uint64_t sk_rt_00077888();                                /* FUN_00077888 */
extern uint64_t sk_rt_0007c028();                                /* FUN_0007c028 */
extern uint64_t sk_rt_0007c1c4();                                /* FUN_0007c1c4 */
extern uint64_t sk_rt_000839d8();                                /* FUN_000839d8 */
extern sk_u128_t sk_rt_000839f8();                                /* FUN_000839f8 */
extern uint64_t sk_rt_00084220();                                /* FUN_00084220 */
extern uint64_t sk_rt_00084234();                                /* FUN_00084234 */
extern uint64_t sk_rt_0008e500();                                /* FUN_0008e500 */
extern uint64_t sk_rt_0008e518();                                /* FUN_0008e518 */
extern sk_u128_t sk_rt_0009461c();                                /* FUN_0009461c */
extern uint64_t sk_rt_000a6f88();                                /* FUN_000a6f88 */
extern sk_u128_t sk_rt_000b4390();                                /* FUN_000b4390 */
extern uint64_t sk_rt_00114330();                                /* FUN_00114330 */
extern uint64_t sk_rt_00117cc4();                                /* FUN_00117cc4 */
extern sk_u128_t sk_rt_00310d68();                                /* FUN_00310d68 */
extern uint64_t sk_rt_00349104();                                /* FUN_00349104 */
extern uint64_t sk_rt_00349530();                                /* FUN_00349530 */
extern uint64_t sk_rt_00349a9c();                                /* FUN_00349a9c */
extern uint64_t sk_rt_00349cd0();                                /* FUN_00349cd0 */
extern uint64_t sk_rt_00349d3c();                                /* FUN_00349d3c */
extern uint64_t sk_rt_0034ab20();                                /* FUN_0034ab20 */
extern uint64_t sk_rt_0034ada0();                                /* FUN_0034ada0 */
extern sk_u128_t sk_rt_0034b57c();                                /* FUN_0034b57c */
extern uint64_t sk_rt_0034b7e4();                                /* FUN_0034b7e4 */
extern uint64_t sk_rt_0034ba48();                                /* FUN_0034ba48 */
extern uint64_t sk_rt_0034bb74();                                /* FUN_0034bb74 */
extern uint64_t sk_rt_0034c144();                                /* FUN_0034c144 */
extern uint64_t sk_rt_0034cb60();                                /* FUN_0034cb60 */
extern sk_u128_t sk_rt_0034cdf8();                                /* FUN_0034cdf8 */
extern uint64_t sk_rt_0034d1c0();                                /* FUN_0034d1c0 */
extern uint64_t sk_rt_0034d724();                                /* FUN_0034d724 */
extern uint64_t sk_rt_0034dbd8();                                /* FUN_0034dbd8 */
extern uint64_t sk_rt_0034de54();                                /* FUN_0034de54 */
extern uint64_t sk_rt_0034ee88();                                /* FUN_0034ee88 */
extern uint64_t sk_rt_0034f22c();                                /* FUN_0034f22c */
extern uint64_t sk_rt_0034fa0c();                                /* FUN_0034fa0c */
extern uint64_t sk_rt_0034fc7c();                                /* FUN_0034fc7c */
extern uint64_t sk_rt_00350404();                                /* FUN_00350404 */
extern sk_u128_t sk_rt_003504ac();                                /* FUN_003504ac */
extern uint64_t sk_rt_003504d0();                                /* FUN_003504d0 */
extern uint64_t sk_rt_00350548();                                /* FUN_00350548 */
extern uint64_t sk_rt_00350750();                                /* FUN_00350750 */
extern sk_u128_t sk_rt_003507e0();                                /* FUN_003507e0 */
extern uint64_t sk_rt_003509c8();                                /* FUN_003509c8 */
extern uint64_t sk_rt_003509ec();                                /* FUN_003509ec */
extern uint64_t sk_rt_00350c5c();                                /* FUN_00350c5c */
extern sk_u128_t sk_rt_00351244();                                /* FUN_00351244 */
extern uint64_t sk_rt_003518dc();                                /* FUN_003518dc */
extern sk_u128_t sk_rt_00351d24();                                /* FUN_00351d24 */
extern uint64_t sk_rt_00352758();                                /* FUN_00352758 */
extern uint64_t sk_rt_00352dac();                                /* FUN_00352dac */
extern uint64_t sk_rt_00353498();                                /* FUN_00353498 */
extern uint64_t sk_rt_003535e4();                                /* FUN_003535e4 */
extern uint64_t sk_rt_00353d70();                                /* FUN_00353d70 */
extern sk_u128_t sk_rt_00355008();                                /* FUN_00355008 */
extern uint64_t sk_rt_0035510c();                                /* FUN_0035510c */
extern uint64_t sk_rt_003558ec();                                /* FUN_003558ec */
extern uint64_t sk_rt_00355d60();                                /* FUN_00355d60 */
extern uint64_t sk_rt_003561f4();                                /* FUN_003561f4 */
extern uint64_t sk_rt_00356638();                                /* FUN_00356638 */
extern uint64_t sk_rt_00356e64();                                /* FUN_00356e64 */
extern uint64_t sk_rt_00356e74();                                /* FUN_00356e74 */
extern uint64_t sk_rt_00357d44();                                /* FUN_00357d44 */
extern uint64_t sk_rt_00357db4();                                /* FUN_00357db4 */
extern uint64_t sk_rt_00357e04();                                /* FUN_00357e04 */
extern uint64_t sk_rt_00357ec4();                                /* FUN_00357ec4 */
extern uint64_t sk_rt_0036851c();                                /* FUN_0036851c */
extern uint64_t sk_rt_00368980();                                /* FUN_00368980 */
extern uint64_t sk_rt_0036b118();                                /* FUN_0036b118 */
extern uint64_t sk_rt_0036b270();                                /* FUN_0036b270 */
extern uint64_t sk_rt_003728b8();                                /* FUN_003728b8 */
extern sk_u128_t sk_rt_00374104();                                /* FUN_00374104 */
extern uint64_t sk_rt_00376820();                                /* FUN_00376820 */
extern sk_u128_t sk_rt_00377824();                                /* FUN_00377824 */
extern sk_u128_t sk_rt_00377dcc();                                /* FUN_00377dcc */
extern uint64_t sk_rt_00406478();                                /* FUN_00406478 */
extern uint64_t sk_rt_0040654c();                                /* FUN_0040654c */
extern uint64_t sk_rt_00406748();                                /* FUN_00406748 */
extern uint64_t sk_rt_00406814();                                /* FUN_00406814 */
extern uint64_t sk_rt_004068a4();                                /* FUN_004068a4 */
extern uint64_t sk_rt_0040692c();                                /* FUN_0040692c */
extern uint64_t sk_rt_004069d8();                                /* FUN_004069d8 */
extern uint64_t sk_rt_00406c08();                                /* FUN_00406c08 */
extern uint64_t sk_rt_00406d90();                                /* FUN_00406d90 */
extern uint64_t sk_rt_00406de8();                                /* FUN_00406de8 */
extern uint64_t sk_rt_00406e34();                                /* FUN_00406e34 */
extern uint64_t sk_rt_00406e78();                                /* FUN_00406e78 */
extern uint64_t sk_rt_00406f08();                                /* FUN_00406f08 */
extern uint64_t sk_rt_00406f60();                                /* FUN_00406f60 */
extern uint64_t sk_rt_004071a4();                                /* FUN_004071a4 */
extern uint64_t sk_rt_00407200();                                /* FUN_00407200 */
extern uint64_t sk_rt_004072e8();                                /* FUN_004072e8 */
extern uint64_t sk_rt_00407434();                                /* FUN_00407434 */
extern uint64_t sk_rt_00407460();                                /* FUN_00407460 */
extern sk_u128_t sk_rt_00407478();                                /* FUN_00407478 */
extern uint64_t sk_rt_0040749c();                                /* FUN_0040749c */
extern uint64_t sk_rt_004075ec();                                /* FUN_004075ec */
extern uint64_t sk_rt_0040761c();                                /* FUN_0040761c */
extern uint64_t sk_rt_00407638();                                /* FUN_00407638 */
extern uint64_t sk_rt_0040774c();                                /* FUN_0040774c */
extern uint64_t sk_rt_004077b0();                                /* FUN_004077b0 */
extern uint64_t sk_rt_004077dc();                                /* FUN_004077dc */
extern uint64_t sk_rt_004077ec();                                /* FUN_004077ec */
extern uint64_t sk_rt_0040799c();                                /* FUN_0040799c */
extern uint64_t sk_rt_004079e4();                                /* FUN_004079e4 */
extern uint64_t sk_rt_00407a80();                                /* FUN_00407a80 */
extern uint64_t sk_rt_00407ae8();                                /* FUN_00407ae8 */
extern uint64_t sk_rt_00407bcc();                                /* FUN_00407bcc */
extern uint64_t sk_rt_00407cb4();                                /* FUN_00407cb4 */
extern uint64_t sk_rt_00407d54();                                /* FUN_00407d54 */
extern uint64_t sk_rt_00407dc0();                                /* FUN_00407dc0 */
extern uint64_t sk_rt_00407de0();                                /* FUN_00407de0 */
extern uint64_t sk_rt_00407df0();                                /* FUN_00407df0 */
extern uint64_t sk_rt_00407f30();                                /* FUN_00407f30 */
extern uint64_t sk_rt_00407fd8();                                /* FUN_00407fd8 */
extern uint64_t sk_rt_004080bc();                                /* FUN_004080bc */
extern sk_u128_t sk_rt_004080f8();                                /* FUN_004080f8 */
extern uint64_t sk_rt_004082b4();                                /* FUN_004082b4 */
extern uint64_t sk_rt_004082c8();                                /* FUN_004082c8 */
extern uint64_t sk_rt_004082e0();                                /* FUN_004082e0 */
extern uint64_t sk_rt_00408314();                                /* FUN_00408314 */
extern uint64_t sk_rt_00408510();                                /* FUN_00408510 */

/* ---- forward declarations for the functions defined in this file ---- */
void sk_r61_003fdfe8(void);
void sk_r61_003fe04c(void);
uint64_t sk_r61_003fe0b8(void);
void sk_r61_003fe364(void);
void sk_r61_003fe37c(void);
void sk_r61_003fe3a4(void);
void sk_r61_003fe3bc(void);
void sk_r61_003fe3d4(void);
void sk_r61_003fe3ec(void);
void sk_r61_003fe404(void);
void sk_r61_003fe444(void);
void sk_r61_003fe4bc(void);
void sk_r61_003fe564(void);
void sk_r61_003fe5d0(void);
void sk_r61_003fe648(void);
void sk_r61_003fe6b0(void);
uint64_t sk_r61_003fe720(uint64_t p1, uint32_t p2);
void sk_r61_003fe838(uint64_t p1, uint64_t p2, uint32_t p3, int64_t p4);
void sk_r61_003fe9f0(void);
void sk_r61_003feb98(int32_t* p1, uint64_t p2, uint64_t p3);
void sk_r61_003fed38(int64_t p1);
void sk_r61_003fedb4(void);
void sk_r61_003fee4c(void);
void sk_r61_003feea0(void);
void sk_r61_003fef04(void);
void sk_r61_003fef68(void);
void sk_r61_003fefcc(void);
uint64_t sk_r61_003ff030(void);
void sk_r61_003ff14c(void);
void sk_r61_003ff2f0(void);
void sk_r61_003ff318(void);
void sk_r61_003ff330(void);
void sk_r61_003ff348(void);
void sk_r61_003ff360(void);
void sk_r61_003ff378(void);
void sk_r61_003ff3a0(int64_t p1);
void sk_r61_003ff424(void);
void sk_r61_003ff4c0(void);
void sk_r61_003ff524(void);
void sk_r61_003ff598(void);
void sk_r61_003ff5f8(void);
uint64_t sk_r61_003ff664(void);
void sk_r61_003ff958(int64_t p1);
void sk_r61_003ff9cc(void);
void sk_r61_003ffa74(void);
void sk_r61_003ffad8(void);
void sk_r61_003ffb40(void);
void sk_r61_003ffba8(void);
void sk_r61_003ffc04(void);
uint64_t sk_r61_003ffc64(void);
void sk_r61_003fff34(void);
void sk_r61_003fff9c(void);
void sk_r61_003fffb4(void);
void sk_r61_00400084(void);
void sk_r61_0040009c(uint64_t p1, uint64_t p2, int64_t p3, uint64_t p4, uint64_t p5);
void sk_r61_0040025c(void);
void sk_r61_00400388(void);
void sk_r61_004004ac(void);
void sk_r61_004004c4(void);
void sk_r61_00400620(void);
void sk_r61_00400638(void);
void sk_r61_00400740(void);
void sk_r61_00400758(void);
void sk_r61_004008a8(void);
void sk_r61_004008c0(uint64_t p1, uint64_t p2, int64_t p3, uint64_t p4, uint64_t p5);
void sk_r61_00400b3c(uint64_t p1, uint64_t p2, uint32_t p3, int64_t p4, uint64_t p5, uint64_t p6);
void sk_r61_00400e44(void);
void sk_r61_00400eb0(void);
void sk_r61_00400f28(void);
void sk_r61_00400fd4(void);
void sk_r61_00401044(void);
void sk_r61_004010b4(void);
void sk_r61_00401124(void);
void sk_r61_00401188(void);
uint64_t sk_r61_004011f0(uint64_t p1, uint32_t p2);
void sk_r61_00401314(uint64_t p1, uint64_t p2, uint32_t p3, int64_t p4);
void sk_r61_004014d4(void);
void sk_r61_0040153c(void);
void sk_r61_004015c8(uint64_t p1, int64_t p2);
void sk_r61_00401940(int64_t p1);
void sk_r61_004019c0(void);
int64_t* sk_r61_004019d8(void);
void sk_r61_00401aec(void);
void sk_r61_00401b64(void);
void sk_r61_00401b7c(void);
void sk_r61_00401c00(void);
void sk_r61_00401c18(void);
void sk_r61_00401ca8(void);
void sk_r61_00401cc0(void);
void sk_r61_00401d40(void);
void sk_r61_00401d58(void);
void sk_r61_00401de0(void);
uint64_t sk_r61_00401df8(void);
void sk_r61_00401f78(int32_t* p1, uint64_t p2, uint32_t p3, int64_t p4, uint64_t p5, uint64_t p6);
sk_u128_t sk_r61_00402324(int64_t p1);
void sk_r61_00402594(int64_t p1);
void sk_r61_004025f4(uint64_t p1, uint64_t p2, int64_t p3);
void sk_r61_004027a8(int64_t p1, int64_t p2);
int32_t sk_r61_00403350(void);
int32_t sk_r61_00403354(void);
int32_t sk_r61_00403728(void);
int32_t sk_r61_0040372c(void);
void sk_r61_004038d0(int64_t p1);
int64_t* sk_r61_0040394c(void);
void sk_r61_00404620(void);
void sk_r61_00404654(void);
void sk_r61_004047ac(uint64_t p1, uint64_t p2, uint64_t* p3);
void sk_r61_004047f8(void);
void sk_r61_00404850(void);
void sk_r61_00404898(void);
void sk_r61_0040489c(void);
void sk_r61_004048cc(void);
void sk_r61_004048d0(void);
void sk_r61_00404900(void);
void sk_r61_00404948(int64_t p1);
void sk_r61_00404974(void);
void sk_r61_00404978(void);
void sk_r61_004049a8(int64_t* p1);
void sk_r61_00404a24(void);
void sk_r61_00404a7c(int64_t p1);

/*--------------------------------------------------------------------*/
/* FUN_003fdfe8 @ 0x3fdfe8   (est. sk_r61_003fdfe8)
 * Ghidra: void FUN_003fdfe8(void)
 * Runs a sequence of object/runtime setup helpers, then dispatches through a
 * vtable method pointer stored at object+0x20 and reads object+0x40 as a field
 * passed to a runtime helper. Caller-provided object (register artifact x16).
 * Confidence: low
 * Notes: vtable dispatch @+0x20, field read @+0x40; callees 0034dbd8 0040654c
 *         00377824 00349530 00349104 00352dac; register artifact extraout_x16. */
void sk_r61_003fdfe8(void)
{
    uint64_t extraout_x16 = 0; /* register artifact: object pointer inherited from caller */

    sk_rt_0034dbd8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x20)))();
    sk_rt_00349104(*(uint64_t *)((uint64_t)extraout_x16 + 0x40));
    sk_rt_00352dac();
}

/* FUN_003fe04c @ 0x3fe04c   (est. sk_r61_003fe04c)
 * Ghidra: void FUN_003fe04c(void)
 * Same setup sequence as 003fdfe8 but dispatches through vtable slot +0x28,
 * then calls a runtime helper with a word loaded from the caller frame at +8
 * (register artifact x9) and a final no-op-ish helper. Caller-provided object.
 * Confidence: low
 * Notes: vtable dispatch @+0x28, field read @+0x40, frame read @(x9+8);
 *         callees 0034dbd8 0040654c 00377824 00349530 00349104 00352dac 0036b118;
 *         register artifacts extraout_x16, extraout_x9. */
void sk_r61_003fe04c(void)
{
    uint64_t extraout_x9 = 0;  /* register artifact: frame pointer inherited from caller */
    uint64_t extraout_x16 = 0; /* register artifact: object pointer inherited from caller */

    sk_rt_0034dbd8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x28)))();
    sk_rt_00349104(*(uint64_t *)((uint64_t)extraout_x16 + 0x40));
    sk_rt_00352dac(*(uint64_t *)((uint64_t)extraout_x9 + 8));
    sk_rt_0036b118();
}

/* FUN_003fe0b8 @ 0x3fe0b8   (est. sk_r61_003fe0b8)
 * Ghidra: ulong FUN_003fe0b8(void)
 * Size/alignment validation helper. After runtime setup it obtains a
 * capacity-style 16-byte value from 00355008 using a field of the caller
 * object (+0x54) as size hint. If the caller-specified count (w20) is nonzero
 * and below the expected limit, it emits a message via 00407460, then inspects
 * a word at the caller frame to decide element width (1/2/4 bytes) and returns
 * a nonzero result when a marker is present. Falls back to a 4 KiB alignment
 * check and to a u128 scalar from 000839f8 otherwise.
 * Confidence: high (verified vs decompile 2026-08-12; register artifacts explicitly
 *   declared as 0 locals per convention; switch 1/2/3/4 element-width + trap 0x3fe1b4,
 *   found_marker path, 4KiB fallback, u128 scalar tail all match)
 * Notes: many register artifacts (x1,w8,x8,w9,x11,w12,w13,x16,x19,w20);
 *         SoftwareBreakpoint(1,0x3fe1b4); callees 0034d724 0040654c 00377824
 *         0034ada0 00355008 00407460 004080bc 00407d54 00356e64 0040692c 000839f8. */
uint64_t sk_r61_003fe0b8(void)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint64_t uVar7;
    uint64_t uVar8;
    sk_u128_t auVar9;
    uint64_t extraout_x1 = 0;   /* register artifact */
    int32_t extraout_w8 = 0;    /* register artifact */
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint32_t extraout_w9 = 0;   /* register artifact */
    uint64_t extraout_x11 = 0;  /* register artifact */
    uint32_t extraout_w12 = 0;  /* register artifact */
    uint32_t extraout_w13 = 0;  /* register artifact */
    uint64_t extraout_x16 = 0;  /* register artifact: object pointer inherited from caller */
    uint64_t unaff_x19 = 0;     /* register artifact */
    uint32_t unaff_w20 = 0;     /* register artifact: caller count */

    sk_rt_0034d724();
    sk_rt_0040654c();
    sk_rt_00377824();
    uVar7 = sk_rt_0034ada0();
    auVar9 = sk_rt_00355008(uVar7, *(uint32_t *)((uint64_t)extraout_x16 + 0x54));
    uVar7 = auVar9.hi;
    if (unaff_w20 == 0) {
        return 0;
    }
    if (extraout_w9 < unaff_w20) {
        sk_rt_00407460(*(uint64_t *)((uint64_t)extraout_x8 + 0x40), auVar9.lo, uVar7, auVar9.lo);
        sk_rt_004080bc();
        uVar2 = extraout_w13;
        if (extraout_w12 < 0x100) {
            uVar2 = 1;
        }
        uVar1 = 0;
        if (1 < extraout_w12) {
            uVar1 = uVar2;
        }
        uVar7 = extraout_x1;
        switch (uVar1) {
        case 1:
            if (*(char *)(unaff_x19 + extraout_x11) != '\0') {
                goto found_marker;
            }
            break;
        case 2:
            if (*(short *)(unaff_x19 + extraout_x11) != 0) {
                goto found_marker;
            }
            break;
        case 3:
            __builtin_trap(); /* SoftwareBreakpoint(1,0x3fe1b4) */
            /* fall through */
        case 4:
            if (*(int *)(unaff_x19 + extraout_x11) != 0) {
                goto found_marker;
            }
            break;
        }
    }
    {
        bool bVar5 = 0xfff < (uint32_t)uVar7;
        bool bVar6 = (uint32_t)uVar7 == 0x1000;
        if (!bVar5) {
            sk_rt_0040692c();
            uVar3 = 0;
            if (!bVar5 || bVar6) {
                uVar3 = (uint32_t)extraout_w8 + 1;
            }
            return (uint64_t)uVar3;
        }
        uVar8 = sk_rt_000839f8().lo;
        return uVar8;
    }

found_marker:
    sk_rt_00407d54();
    uVar8 = sk_rt_00356e64();
    return uVar8;
}

/* FUN_003fe364 @ 0x3fe364   (est. sk_r61_003fe364)
 * Ghidra: void FUN_003fe364(void)
 * Calls the 00406f08 runtime helper then the sibling handler 003fffb4.
 * Confidence: medium
 * Notes: callees 00406f08 003fffb4 (sibling sk_r61_003fffb4). */
void sk_r61_003fe364(void)
{
    sk_rt_00406f08();
    sk_r61_003fffb4();
}

/* FUN_003fe37c @ 0x3fe37c   (est. sk_r61_003fe37c)
 * Ghidra: void FUN_003fe37c(void)
 * Calls the 00406f08 runtime helper then the sibling handler 0040009c.
 * Confidence: medium
 * Notes: callees 00406f08 0040009c (sibling sk_r61_0040009c). */
void sk_r61_003fe37c(void)
{
    sk_rt_00406f08();
    /* Args to sibling 0040009c live in untracked registers at the call site (decompiler
     * shows none); the forward decl requires 5, so pass the unrecovered register state as 0. */
    sk_r61_0040009c(0, 0, 0, 0, 0);
}

/* FUN_003fe3a4 @ 0x3fe3a4   (est. sk_r61_003fe3a4)
 * Ghidra: void FUN_003fe3a4(void)
 * Calls the 00406f08 runtime helper then the sibling handler 00400388.
 * Confidence: medium
 * Notes: callees 00406f08 00400388 (sibling sk_r61_00400388). */
void sk_r61_003fe3a4(void)
{
    sk_rt_00406f08();
    sk_r61_00400388();
}

/* FUN_003fe3bc @ 0x3fe3bc   (est. sk_r61_003fe3bc)
 * Ghidra: void FUN_003fe3bc(void)
 * Calls the 00406f08 runtime helper then the sibling handler 004004c4.
 * Confidence: medium
 * Notes: callees 00406f08 004004c4 (sibling sk_r61_004004c4). */
void sk_r61_003fe3bc(void)
{
    sk_rt_00406f08();
    sk_r61_004004c4();
}

/* FUN_003fe3d4 @ 0x3fe3d4   (est. sk_r61_003fe3d4)
 * Ghidra: void FUN_003fe3d4(void)
 * Calls the 00406f08 runtime helper then the sibling handler 00400638.
 * Confidence: medium
 * Notes: callees 00406f08 00400638 (sibling sk_r61_00400638). */
void sk_r61_003fe3d4(void)
{
    sk_rt_00406f08();
    sk_r61_00400638();
}

/* FUN_003fe3ec @ 0x3fe3ec   (est. sk_r61_003fe3ec)
 * Ghidra: void FUN_003fe3ec(void)
 * Calls the 00406f08 runtime helper then the sibling handler 00400758.
 * Confidence: medium
 * Notes: callees 00406f08 00400758 (sibling sk_r61_00400758). */
void sk_r61_003fe3ec(void)
{
    sk_rt_00406f08();
    sk_r61_00400758();
}

/* FUN_003fe404 @ 0x3fe404   (est. sk_r61_003fe404)
 * Ghidra: void FUN_003fe404(void)
 * Calls the 00406f08 runtime helper then the sibling handler 004008c0.
 * Confidence: medium
 * Notes: callees 00406f08 004008c0 (sibling sk_r61_004008c0). */
void sk_r61_003fe404(void)
{
    sk_rt_00406f08();
    /* Args to sibling 004008c0 live in untracked registers at the call site (decompiler
     * shows none); the forward decl requires 5, so pass the unrecovered register state as 0. */
    sk_r61_004008c0(0, 0, 0, 0, 0);
}

/* FUN_003fe444 @ 0x3fe444   (est. sk_r61_003fe444)
 * Ghidra: void FUN_003fe444(void)
 * Runs 00407dc0 and 00406f08, then reads a 16-byte object from 00377824(0x13f).
 * When its high word is below 0x40 it walks the object (lo - 8) to retrieve a
 * pointer, calls 00357d44 with that pointer +0x40, and runs three more helpers.
 * Confidence: low
 * Notes: u128 halves used (.lo/.hi of 00377824); callees 00407dc0 00406f08
 *         00377824 00357d44 0034d1c0 003728b8 00019858. */
void sk_r61_003fe444(void)
{
    sk_u128_t auVar1;

    sk_rt_00407dc0();
    sk_rt_00406f08();
    auVar1 = sk_rt_00377824(0x13f);
    if (auVar1.hi < 0x40) {
        sk_rt_00357d44(*(int64_t *)((uint64_t)auVar1.lo - 8) + 0x40);
        sk_rt_0034d1c0();
        sk_rt_003728b8();
        sk_rt_00019858();
    }
}

/* FUN_003fe4bc @ 0x3fe4bc   (est. sk_r61_003fe4bc)
 * Ghidra: void FUN_003fe4bc(void)
 * Runtime setup sequence (0034fc7c 0040654c 00377824 0034b57c) then 0035510c
 * with the caller object (x16) and 0034c144. If the caller condition flag is
 * set and the caller-saved x10 count is below 0x19, it runs 00406c08, calls
 * through the caller-supplied function pointer (x9), and two more helpers;
 * otherwise it runs the 00349a9c alternate path. Ends with 0036b270.
 * Confidence: low
 * Notes: register artifacts in_ZR, extraout_x9 (code ptr), extraout_x10,
 *         extraout_x16; callees 0034fc7c 0040654c 00377824 0034b57c 0035510c
 *         0034c144 00406c08 00349cd0 003535e4 00349a9c 0036b270. */
void sk_r61_003fe4bc(void)
{
    uint8_t in_ZR = 0;        /* register artifact: caller condition flag */
    uint64_t extraout_x9 = 0; /* register artifact: caller-supplied function pointer */
    uint64_t extraout_x10 = 0; /* register artifact: caller count */
    uint64_t extraout_x16 = 0; /* register artifact: object pointer inherited from caller */

    sk_rt_0034fc7c();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_0034b57c();
    sk_rt_0035510c(extraout_x16);
    sk_rt_0034c144();
    if (in_ZR && extraout_x10 < 0x19) {
        sk_rt_00406c08();
        ((void (*)(void))extraout_x9)();
        sk_rt_00349cd0();
        sk_rt_003535e4();
    }
    else {
        sk_rt_00349a9c();
    }
    sk_rt_0036b270();
}

/* FUN_003fe564 @ 0x3fe564   (est. sk_r61_003fe564)
 * Ghidra: void FUN_003fe564(void)
 * Object method-dispatch: runs setup helpers, dispatches through vtable slot
 * +0x10, passes field +0x40 to 00349104, then runs 0034f22c and 0036b270.
 * Confidence: low
 * Notes: vtable dispatch @+0x10, field read @+0x40; register artifact
 *         extraout_x16; callees 004069d8 0040654c 00377824 00349530 00349104
 *         0034f22c 0036b270. */
void sk_r61_003fe564(void)
{
    uint64_t extraout_x16 = 0; /* register artifact: object pointer inherited from caller */

    sk_rt_004069d8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x10)))();
    sk_rt_00349104(*(uint64_t *)((uint64_t)extraout_x16 + 0x40));
    sk_rt_0034f22c();
    sk_rt_0036b270();
}

/* FUN_003fe5d0 @ 0x3fe5d0   (est. sk_r61_003fe5d0)
 * Ghidra: void FUN_003fe5d0(void)
 * Object method-dispatch: runs setup helpers, dispatches through vtable slot
 * +0x18, passes field +0x40 to 00349104, loads a word from the caller frame at
 * +8 (x9), then runs 0034f22c, 0036b270 and 0036b118(word).
 * Confidence: low
 * Notes: vtable dispatch @+0x18, field read @+0x40, frame read @(x9+8);
 *         register artifacts extraout_x16, extraout_x9; callees 004069d8
 *         0040654c 00377824 00349530 00349104 0034f22c 0036b270 0036b118. */
void sk_r61_003fe5d0(void)
{
    uint64_t extraout_x9 = 0;  /* register artifact: frame pointer inherited from caller */
    uint64_t extraout_x16 = 0; /* register artifact: object pointer inherited from caller */
    uint64_t uVar1;

    sk_rt_004069d8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x18)))();
    sk_rt_00349104(*(uint64_t *)((uint64_t)extraout_x16 + 0x40));
    uVar1 = *(uint64_t *)((uint64_t)extraout_x9 + 8);
    sk_rt_0034f22c();
    sk_rt_0036b270();
    sk_rt_0036b118(uVar1);
}

/* FUN_003fe648 @ 0x3fe648   (est. sk_r61_003fe648)
 * Ghidra: void FUN_003fe648(void)
 * Object method-dispatch: runs setup helpers, dispatches through vtable slot
 * +0x20, passes field +0x40 to 00349104, then runs 00352dac.
 * Confidence: low
 * Notes: vtable dispatch @+0x20, field read @+0x40; register artifact
 *         extraout_x16; callees 004069d8 0040654c 00377824 00349530 00349104
 *         00352dac. */
void sk_r61_003fe648(void)
{
    uint64_t extraout_x16 = 0; /* register artifact: object pointer inherited from caller */

    sk_rt_004069d8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x20)))();
    sk_rt_00349104(*(uint64_t *)((uint64_t)extraout_x16 + 0x40));
    sk_rt_00352dac();
}
/* FUN_003fe6b0 @ 0x3fe6b0   (est. sk_r61_003fe6b0)
 * Ghidra: void FUN_003fe6b0(void)
 * Acquires the current object, then dispatches through a method pointer stored
 * at this+0x28 and performs follow-up object bookkeeping. Uses register
 * artifacts as the this pointer for the vtable dispatch.
 * Confidence: low
 * Notes: register artifacts extraout_x16 (this for vtable at +0x28),
 * extraout_x9 (this for +8 read); callees FUN_004069d8 FUN_0040654c
 * FUN_00377824 FUN_00349530 FUN_00349104 FUN_00352dac FUN_0036b118. */
void sk_r61_003fe6b0(void)
{
    uint64_t extraout_x16 = 0; /* register artifact: this pointer */
    uint64_t extraout_x9 = 0;  /* register artifact */

    sk_rt_004069d8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x28)))();
    sk_rt_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_00352dac(*(uint64_t *)(extraout_x9 + 8));
    sk_rt_0036b118();
}

/* FUN_003fe720 @ 0x3fe720   (est. sk_r61_003fe720)
 * Ghidra: ulong FUN_003fe720(undefined8 param_1,uint param_2)
 * Looks up an object capability/slot by index (param_2) within the current
 * object's table (width from this+0x54) and returns the decoded slot value
 * sized to its stored width. Returns 0 when param_2 is zero, when the slot is
 * empty, or on a bounds/overflow path.
 * Confidence: low
 * Notes: register artifacts extraout_w8/w9/w12/w13, extraout_x1/x8/x11/x16,
 * unaff_x19; 16-byte return from FUN_00355008 read as .lo/.hi; SoftwareBreakpoint
 * at 0x3fe820; callees FUN_0034fc7c FUN_0040654c FUN_00377824 FUN_0034ada0
 * FUN_00355008 FUN_00407460 FUN_004080bc FUN_00407d54 FUN_00356e64
 * FUN_0040692c FUN_000839f8. */
uint64_t sk_r61_003fe720(uint64_t param_1, uint32_t param_2)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    uint32_t extraout_w8 = 0;   /* register artifact */
    uint32_t extraout_w9 = 0;   /* register artifact */
    uint32_t extraout_w12 = 0;  /* register artifact */
    uint32_t extraout_w13 = 0;  /* register artifact */
    uint64_t uVar7;
    uint64_t uVar8;
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint64_t extraout_x11 = 0;  /* register artifact */
    uint64_t extraout_x16 = 0;  /* register artifact */
    uint64_t unaff_x19 = 0;     /* register artifact */
    sk_u128_t auVar9;

    sk_rt_0034fc7c();
    sk_rt_0040654c();
    sk_rt_00377824();
    uVar7 = sk_rt_0034ada0();
    auVar9 = sk_rt_00355008(uVar7, *(uint32_t *)(extraout_x16 + 0x54));
    uVar7 = auVar9.hi;
    if (param_2 == 0) {
        return 0;
    }
    if (extraout_w9 < param_2) {
        sk_rt_00407460(*(uint64_t *)(extraout_x8 + 0x40), auVar9.lo, uVar7, auVar9.lo);
        sk_rt_004080bc();
        uVar2 = extraout_w13;
        if (extraout_w12 < 0x100) {
            uVar2 = 1;
        }
        uVar1 = 0;
        if (1 < extraout_w12) {
            uVar1 = uVar2;
        }
        uVar7 = extraout_x1;
        switch (uVar1) {
        case 1:
            if (*(char *)(unaff_x19 + extraout_x11) != '\0') {
            LAB_003fe7d0:
                sk_rt_00407d54();
                uVar8 = sk_rt_00356e64();
                return uVar8;
            }
            break;
        case 2:
            if (*(short *)(unaff_x19 + extraout_x11) != 0) goto LAB_003fe7d0;
            break;
        case 3:
            __builtin_trap(); /* SoftwareBreakpoint(1,0x3fe820) */
        case 4:
            if (*(int *)(unaff_x19 + extraout_x11) != 0) goto LAB_003fe7d0;
        }
    }
    {
        bool bVar5 = 0xfff < (uint32_t)uVar7;
        bool bVar6 = (uint32_t)uVar7 == 0x1000;
        if (!bVar5) {
            sk_rt_0040692c();
            uVar3 = 0;
            if (!bVar5 || bVar6) {
                uVar3 = extraout_w8 + 1;
            }
            return (uint64_t)uVar3;
        }
    }
    uVar8 = sk_rt_000839f8().lo;
    return uVar8;
}

/* FUN_003fe838 @ 0x3fe838   (est. sk_r61_003fe838)
 * Ghidra: void FUN_003fe838(undefined8 param_1,undefined8 param_2,uint param_3,long param_4)
 * Releases/stores a slot value: validates the slot width (param_3) against the
 * object table width (this+0x54), writes the truncated remainder into the
 * slot at (unaff_x19 + unaff_x21), and flushes/allocates the backing page when
 * the slot count is non-zero. Uses param_4 (a record) for extra args.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x8_00/x8_01, extraout_w9/w10/w11,
 * extraout_x9/x16, unaff_x19/unaff_w20/unaff_x21; SoftwareBreakpoint at
 * 0x3fe9b4; callees FUN_00350c5c FUN_0040654c FUN_00377824 FUN_0034ada0
 * FUN_00357db4 FUN_004071a4 FUN_00357e04 FUN_00407bcc FUN_003507e0
 * FUN_00114330 FUN_0009461c FUN_000839d8 FUN_0034de54 FUN_00407434. */
void sk_r61_003fe838(uint64_t param_1, uint64_t param_2, uint32_t param_3, int64_t param_4)
{
    uint32_t uVar1;
    uint32_t uVar2;
    int32_t iVar3;
    uint64_t uVar5;
    uint32_t uVar6;
    uint64_t extraout_x8 = 0;     /* register artifact */
    uint64_t *extraout_x8_00 = 0; /* register artifact */
    uint64_t *extraout_x8_01 = 0; /* register artifact */
    uint64_t *puVar7;
    uint32_t extraout_w9 = 0;     /* register artifact */
    uint64_t uVar8;
    uint64_t extraout_x9 = 0;     /* register artifact */
    uint32_t extraout_w10 = 0;    /* register artifact */
    uint32_t extraout_w11 = 0;    /* register artifact */
    uint64_t extraout_x16 = 0;    /* register artifact */
    uint32_t *unaff_x19 = 0;      /* register artifact */
    uint32_t unaff_w20 = 0;       /* register artifact */
    int64_t unaff_x21 = 0;        /* register artifact */

    uVar5 = sk_rt_00350c5c();
    sk_rt_0040654c(uVar5, *(uint64_t *)(param_4 + 0x20), *(uint64_t *)(param_4 + 0x10));
    sk_rt_00377824();
    sk_rt_0034ada0();
    uVar6 = *(uint32_t *)(extraout_x16 + 0x54);
    sk_rt_00357db4();
    sk_rt_004071a4(*(uint64_t *)(extraout_x8 + 0x40));
    sk_rt_00357e04();
    uVar2 = extraout_w11;
    if (extraout_w10 < 0x100) {
        uVar2 = 1;
    }
    uVar1 = 0;
    if (1 < extraout_w10) {
        uVar1 = uVar2;
    }
    uVar2 = 0;
    if (extraout_w9 < param_3) {
        uVar2 = uVar1;
    }
    iVar3 = (int32_t)(unaff_w20 - extraout_w9);
    if (extraout_w9 <= unaff_w20 && iVar3 != 0) {
        if ((int32_t)unaff_x21 != 0) {
            iVar3 = 1;
            sk_rt_00407bcc();
            sk_rt_003507e0();
            sk_rt_00114330();
            *unaff_x19 = unaff_w20;
        }
        switch (uVar2) {
        default:
            return;
        case 1:
            *(char *)((int64_t)unaff_x19 + unaff_x21) = (char)iVar3;
            return;
        case 2:
            *(short *)((int64_t)unaff_x19 + unaff_x21) = (short)iVar3;
            return;
        case 3:
            goto sw3_trap;
        case 4:
            *(int *)((int64_t)unaff_x19 + unaff_x21) = iVar3;
            return;
        }
    }
    switch (uVar2) {
    case 1:
        *(uint8_t *)((int64_t)unaff_x19 + unaff_x21) = 0;
        if (unaff_w20 == 0) {
            return;
        }
        goto LAB_003fe950;
    case 2:
        *(uint16_t *)((int64_t)unaff_x19 + unaff_x21) = 0;
        break;
    case 3:
    sw3_trap:
        __builtin_trap(); /* SoftwareBreakpoint(1,0x3fe9b4) */
    case 4:
        *(uint32_t *)((int64_t)unaff_x19 + unaff_x21) = 0;
    default:
    }
    if (unaff_w20 != 0) {
    LAB_003fe950:
        if (0xfff < uVar6) {
            sk_rt_0009461c();
            sk_rt_000839d8();
            return;
        }
        sk_rt_0034de54();
        if (unaff_w20 < 0x1001) {
            uVar8 = (uint64_t)(unaff_w20 - 1);
            puVar7 = extraout_x8_00;
        }
        else {
            sk_rt_00407434();
            puVar7 = extraout_x8_01;
            uVar8 = extraout_x9;
        }
        *puVar7 = uVar8;
    }
}

/* FUN_003fe9f0 @ 0x3fe9f0   (est. sk_r61_003fe9f0)
 * Ghidra: void FUN_003fe9f0(void)
 * Runs a guarded teardown/release path: performs setup, and if the condition
 * flags indicate success and a count (extraout_x10) is below 0x19, invokes the
 * release method and copies the result out; otherwise falls through to the
 * alternative cleanup path.
 * Confidence: low
 * Notes: register artifacts in_ZR (condition flags), extraout_x8/x9/x9_00/x10/x16;
 * indirect call through extraout_x9; callees FUN_00349d3c FUN_0035510c
 * FUN_0034c144 FUN_0009461c FUN_00349cd0 FUN_00349a9c FUN_0036b270. */
void sk_r61_003fe9f0(void)
{
    bool in_ZR = false;          /* register artifact: condition flags */
    uint64_t *extraout_x8 = 0;   /* register artifact */
    void (*extraout_x9)(void) = 0;   /* register artifact: method pointer */
    uint64_t *extraout_x9_00 = 0;    /* register artifact */
    uint64_t extraout_x10 = 0;       /* register artifact */
    uint64_t extraout_x16 = 0;       /* register artifact */

    sk_rt_00349d3c();
    sk_rt_0035510c(extraout_x16);
    sk_rt_0034c144();
    if (in_ZR && extraout_x10 < 0x19) {
        sk_rt_0009461c();
        extraout_x9();
        sk_rt_00349cd0();
        *extraout_x8 = *extraout_x9_00;
    }
    else {
        sk_rt_00349a9c();
        sk_rt_0036b270();
    }
}

/* FUN_003feb98 @ 0x3feb98   (est. sk_r61_003feb98)
 * Ghidra: void FUN_003feb98(int *param_1,undefined8 param_2,undefined8 param_3)
 * Stores a sized value into a slot within param_1 (a slot array) at offset
 * derived from the object header (this+0x40 aligned). The slot width selector
 * (extraout_w8 vs table width at this+0x54) picks 1/2/4-byte stores; a
 * nonzero-length tail triggers an object flush helper.
 * Confidence: low
 * Notes: register artifacts extraout_w1/w8, extraout_x9/x16; SoftwareBreakpoint
 * at 0x3fed00; callees FUN_0034b7e4 FUN_000839d8 FUN_0009461c FUN_00114330. */
void sk_r61_003feb98(int32_t *param_1, uint64_t param_2, uint64_t param_3)
{
    int64_t lVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    int32_t iVar4;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t extraout_w1 = 0; /* register artifact */
    uint32_t extraout_w8 = 0; /* register artifact */
    uint64_t extraout_x9 = 0; /* register artifact */
    uint64_t extraout_x16 = 0; /* register artifact */

    sk_rt_0034b7e4(param_3);
    uVar3 = *(uint32_t *)(extraout_x16 + 0x54);
    lVar1 = (*(int64_t *)(extraout_x9 + 0x40) + 7U & 0xfffffffffffffff8) + 8;
    if (extraout_w8 < uVar3 || extraout_w8 - uVar3 == 0) {
        uVar7 = 0;
    }
    else {
        uVar6 = 2;
        uVar2 = uVar6;
        if ((int32_t)lVar1 == 0) {
            uVar2 = (extraout_w8 - uVar3) + 1;
        }
        if (0xffff < uVar2) {
            uVar6 = 4;
        }
        if (uVar2 < 0x100) {
            uVar6 = 1;
        }
        uVar7 = 0;
        if (1 < uVar2) {
            uVar7 = uVar6;
        }
    }
    iVar4 = (int32_t)(extraout_w1 - uVar3);
    if (extraout_w1 < uVar3 || iVar4 == 0) {
        switch (uVar7) {
        case 1:
            *(uint8_t *)((int64_t)param_1 + lVar1) = 0;
            if (extraout_w1 == 0) {
                return;
            }
            goto LAB_003fecc4;
        case 2:
            *(uint16_t *)((int64_t)param_1 + lVar1) = 0;
            break;
        case 3:
            goto sw3_trap;
        case 4:
            *(uint32_t *)((int64_t)param_1 + lVar1) = 0;
        default:
        }
        if (extraout_w1 != 0) {
        LAB_003fecc4:
            sk_rt_000839d8(param_1);
            return;
        }
    }
    else {
        if ((int32_t)lVar1 != 0) {
            iVar4 = 1;
            sk_rt_0009461c();
            sk_rt_00114330();
            *param_1 = (int32_t)(extraout_w1 + ~uVar3);
        }
        switch (uVar7) {
        case 1:
            *(char *)((int64_t)param_1 + lVar1) = (char)iVar4;
            break;
        case 2:
            *(short *)((int64_t)param_1 + lVar1) = (short)iVar4;
            break;
        case 3:
        sw3_trap:
            __builtin_trap(); /* SoftwareBreakpoint(1,0x3fed00) */
        case 4:
            *(int *)((int64_t)param_1 + lVar1) = iVar4;
        }
    }
}

/* FUN_003fed38 @ 0x3fed38   (est. sk_r61_003fed38)
 * Ghidra: void FUN_003fed38(long param_1)
 * Releases a descriptor/object: forwards param_1 and its header fields at
 * +0x18/+0x10 to the release helper, then on a short count path (extraout_x1
 * below 0x40) performs further unwind/free steps.
 * Confidence: low
 * Notes: register artifact extraout_x1; callees FUN_00406f08 FUN_00377824
 * FUN_0034d1c0 FUN_003728b8 FUN_00019858. */
void sk_r61_003fed38(int64_t param_1)
{
    uint64_t extraout_x1 = 0; /* register artifact */

    sk_rt_00406f08(param_1, *(uint64_t *)(param_1 + 0x18), *(uint64_t *)(param_1 + 0x10));
    sk_rt_00377824(0x13f);
    if (extraout_x1 < 0x40) {
        sk_rt_0034d1c0();
        sk_rt_003728b8();
        sk_rt_00019858();
    }
}

/* FUN_003fedb4 @ 0x3fedb4   (est. sk_r61_003fedb4)
 * Ghidra: void FUN_003fedb4(void)
 * Alternate guarded teardown: after setup, if condition flags are set and the
 * count (extraout_x10) is below 0x19, invokes the release method and copies
 * the result; otherwise takes the fallback cleanup path.
 * Confidence: low
 * Notes: register artifacts in_ZR, extraout_x8/x9/x9_00/x10/x16; indirect call
 * through extraout_x9; callees FUN_0034d724 FUN_0040654c FUN_00377824
 * FUN_0034b57c FUN_0035510c FUN_0034c144 FUN_00406c08 FUN_00349cd0
 * FUN_00349a9c FUN_0036b270. */
void sk_r61_003fedb4(void)
{
    bool in_ZR = false;               /* register artifact: condition flags */
    uint64_t *extraout_x8 = 0;        /* register artifact */
    void (*extraout_x9)(void) = 0;    /* register artifact: method pointer */
    uint64_t *extraout_x9_00 = 0;     /* register artifact */
    uint64_t extraout_x10 = 0;        /* register artifact */
    uint64_t extraout_x16 = 0;        /* register artifact */

    sk_rt_0034d724();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_0034b57c();
    sk_rt_0035510c(extraout_x16);
    sk_rt_0034c144();
    if (in_ZR && extraout_x10 < 0x19) {
        sk_rt_00406c08();
        extraout_x9();
        sk_rt_00349cd0();
        *extraout_x8 = *extraout_x9_00;
    }
    else {
        sk_rt_00349a9c();
        sk_rt_0036b270();
    }
}

/* FUN_003fee4c @ 0x3fee4c   (est. sk_r61_003fee4c)
 * Ghidra: void FUN_003fee4c(void)
 * Perform a single virtual call through the method pointer at this+8 after
 * object setup. The decompiler could not recover the jump table at 0x3fee98
 * and treats the indirect jump as a call.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x16 (this for vtable at +8); callees
 * FUN_003561f4 FUN_0040654c FUN_00377824 FUN_00350404. */
void sk_r61_003fee4c(void)
{
    uint64_t uVar1;
    uint64_t extraout_x8 = 0;  /* register artifact */
    uint64_t extraout_x16 = 0; /* register artifact */

    sk_rt_003561f4();
    uVar1 = sk_rt_0040654c();
    sk_rt_00377824(uVar1, extraout_x8);
    sk_rt_00350404();
    /* WARNING: Could not recover jumptable at 0x003fee98 (indirect jump as call) */
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 8)))();
}

/* FUN_003feea0 @ 0x3feea0   (est. sk_r61_003feea0)
 * Ghidra: void FUN_003feea0(void)
 * Object teardown: acquire the object, dispatch through the method pointer at
 * this+0x10, then post the argument at this+0x40 and release.
 * Confidence: low
 * Notes: register artifact extraout_x16 (this for vtable at +0x10); callees
 * FUN_0034dbd8 FUN_0040654c FUN_00377824 FUN_00349530 FUN_00349104
 * FUN_0034fa0c. */
void sk_r61_003feea0(void)
{
    uint64_t extraout_x16 = 0; /* register artifact */

    sk_rt_0034dbd8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x10)))();
    sk_rt_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0034fa0c();
}

/* FUN_003fef04 @ 0x3fef04   (est. sk_r61_003fef04)
 * Ghidra: void FUN_003fef04(void)
 * Object teardown variant dispatching through the method pointer at this+0x18.
 * Confidence: low
 * Notes: register artifact extraout_x16 (vtable at +0x18); callees FUN_0034dbd8
 * FUN_0040654c FUN_00377824 FUN_00349530 FUN_00349104 FUN_0034fa0c. */
void sk_r61_003fef04(void)
{
    uint64_t extraout_x16 = 0; /* register artifact */

    sk_rt_0034dbd8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x18)))();
    sk_rt_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0034fa0c();
}

/* FUN_003fef68 @ 0x3fef68   (est. sk_r61_003fef68)
 * Ghidra: void FUN_003fef68(void)
 * Object teardown variant dispatching through the method pointer at this+0x20.
 * Confidence: low
 * Notes: register artifact extraout_x16 (vtable at +0x20); callees FUN_0034dbd8
 * FUN_0040654c FUN_00377824 FUN_00349530 FUN_00349104 FUN_0034fa0c. */
void sk_r61_003fef68(void)
{
    uint64_t extraout_x16 = 0; /* register artifact */

    sk_rt_0034dbd8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x20)))();
    sk_rt_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0034fa0c();
}

/* FUN_003fefcc @ 0x3fefcc   (est. sk_r61_003fefcc)
 * Ghidra: void FUN_003fefcc(void)
 * Object teardown variant dispatching through the method pointer at this+0x28.
 * Confidence: low
 * Notes: register artifact extraout_x16 (vtable at +0x28); callees FUN_0034dbd8
 * FUN_0040654c FUN_00377824 FUN_00349530 FUN_00349104 FUN_0034fa0c. */
void sk_r61_003fefcc(void)
{
    uint64_t extraout_x16 = 0; /* register artifact */

    sk_rt_0034dbd8();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x28)))();
    sk_rt_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0034fa0c();
}

/* FUN_003ff030 @ 0x3ff030   (est. sk_r61_003ff030)
 * Ghidra: ulong FUN_003ff030(void)
 * Reads a slot value from the object table: validates the slot index
 * (unaff_w20) against the table width (this+0x54), decodes the stored value
 * sized by the width selector, and returns it; returns 0 for an empty slot.
 * Confidence: low
 * Notes: register artifacts extraout_w1/w10/w11, extraout_x8/x8_00/x8_01/x9/x16,
 * unaff_x19/unaff_w20; SoftwareBreakpoint at 0x3ff134; callees FUN_0034d724
 * FUN_0040654c FUN_00377824 FUN_000a6f88 FUN_00355d60 FUN_00357e04 FUN_000839f8. */
uint64_t sk_r61_003ff030(void)
{
    uint32_t uVar1;
    uint32_t uVar2;
    int32_t iVar3;
    uint32_t uVar7;
    uint64_t uVar5;
    uint64_t uVar6;
    int32_t extraout_w1 = 0;     /* register artifact */
    uint64_t extraout_x8 = 0;    /* register artifact */
    uint64_t extraout_x8_00 = 0; /* register artifact */
    uint64_t extraout_x8_01 = 0; /* register artifact */
    uint64_t extraout_x9 = 0;    /* register artifact */
    uint32_t extraout_w10 = 0;   /* register artifact */
    uint32_t extraout_w11 = 0;   /* register artifact */
    uint64_t extraout_x16 = 0;   /* register artifact */
    int32_t *unaff_x19 = 0;      /* register artifact */
    uint32_t unaff_w20 = 0;      /* register artifact */

    sk_rt_0034d724();
    sk_rt_0040654c();
    sk_rt_00377824();
    uVar5 = sk_rt_000a6f88();
    if (unaff_w20 == 0) {
        return 0;
    }
    if (*(uint32_t *)(extraout_x16 + 0x54) < unaff_w20) {
        sk_rt_00355d60(*(uint64_t *)(extraout_x8 + 0x40), uVar5, *(uint32_t *)(extraout_x16 + 0x54), uVar5);
        sk_rt_00357e04((extraout_x8_00 + 8U) & 0xfffffff8);
        uVar2 = extraout_w11;
        if (extraout_w10 < 0x100) {
            uVar2 = 1;
        }
        uVar1 = 0;
        if (1 < extraout_w10) {
            uVar1 = uVar2;
        }
        switch (uVar1) {
        case 1:
            uVar7 = (uint32_t)*(uint8_t *)((int64_t)unaff_x19 + extraout_x9);
            if (*(uint8_t *)((int64_t)unaff_x19 + extraout_x9) != 0) {
            LAB_003ff0dc:
                iVar3 = (int32_t)uVar7 - 1;
                if (extraout_x8_01 != 0) {
                    iVar3 = *unaff_x19;
                }
                return (uint64_t)(extraout_w1 + iVar3 + 1);
            }
            break;
        case 2:
            uVar7 = (uint32_t)*(uint16_t *)((int64_t)unaff_x19 + extraout_x9);
            if (*(uint16_t *)((int64_t)unaff_x19 + extraout_x9) != 0) goto LAB_003ff0dc;
            break;
        case 3:
            __builtin_trap(); /* SoftwareBreakpoint(1,0x3ff134) */
        case 4:
            uVar7 = *(uint32_t *)((int64_t)unaff_x19 + extraout_x9);
            if (uVar7 != 0) goto LAB_003ff0dc;
        }
        if (extraout_w1 == 0) {
            return 0;
        }
    }
    uVar6 = sk_rt_000839f8().lo;
    return uVar6;
}

/* FUN_003ff14c @ 0x3ff14c   (est. sk_r61_003ff14c)
 * Ghidra: void FUN_003ff14c(void)
 * Slot store variant: writes a sized value at (unaff_x19 + lVar1) using the
 * width selector derived from unaff_w22 vs the table width, and on a non-empty
 * tail flushes the backing page.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x8_00/x16, unaff_x19/unaff_w20/unaff_w22;
 * SoftwareBreakpoint at 0x3ff2b0; callees FUN_00406f60 FUN_0040654c FUN_00377824
 * FUN_000a6f88 FUN_00355d60 FUN_0009461c FUN_000839d8 FUN_003507e0 FUN_00114330. */
void sk_r61_003ff14c(void)
{
    int64_t lVar1;
    uint32_t uVar2;
    int32_t iVar3;
    uint32_t uVar5;
    uint64_t extraout_x8 = 0;    /* register artifact */
    uint64_t extraout_x8_00 = 0; /* register artifact */
    uint32_t uVar6;
    uint64_t extraout_x16 = 0;   /* register artifact */
    int32_t *unaff_x19 = 0;      /* register artifact */
    uint32_t unaff_w20 = 0;      /* register artifact */
    uint32_t unaff_w22 = 0;      /* register artifact */
    uint32_t uVar7;

    sk_rt_00406f60();
    sk_rt_0040654c();
    sk_rt_00377824();
    sk_rt_000a6f88();
    uVar5 = *(uint32_t *)(extraout_x16 + 0x54);
    sk_rt_00355d60(*(uint64_t *)(extraout_x8 + 0x40));
    lVar1 = extraout_x8_00 + 8;
    if (unaff_w22 < uVar5 || unaff_w22 - uVar5 == 0) {
        uVar7 = 0;
    }
    else {
        uVar6 = 2;
        uVar2 = uVar6;
        if ((int32_t)lVar1 == 0) {
            uVar2 = (unaff_w22 - uVar5) + 1;
        }
        if (0xffff < uVar2) {
            uVar6 = 4;
        }
        if (uVar2 < 0x100) {
            uVar6 = 1;
        }
        uVar7 = 0;
        if (1 < uVar2) {
            uVar7 = uVar6;
        }
    }
    iVar3 = (int32_t)(unaff_w20 - uVar5);
    if (unaff_w20 < uVar5 || iVar3 == 0) {
        switch (uVar7) {
        case 1:
            *(uint8_t *)((int64_t)unaff_x19 + lVar1) = 0;
            if (unaff_w20 == 0) {
                return;
            }
            goto LAB_003ff274;
        case 2:
            *(uint16_t *)((int64_t)unaff_x19 + lVar1) = 0;
            break;
        case 3:
            goto sw3_trap;
        case 4:
            *(uint32_t *)((int64_t)unaff_x19 + lVar1) = 0;
        default:
        }
        if (unaff_w20 != 0) {
        LAB_003ff274:
            sk_rt_0009461c();
            sk_rt_000839d8();
            return;
        }
    }
    else {
        if ((int32_t)lVar1 != 0) {
            iVar3 = 1;
            sk_rt_003507e0();
            sk_rt_00114330();
            *unaff_x19 = (int32_t)(unaff_w20 + ~uVar5);
        }
        switch (uVar7) {
        case 1:
            *(char *)((int64_t)unaff_x19 + lVar1) = (char)iVar3;
            break;
        case 2:
            *(short *)((int64_t)unaff_x19 + lVar1) = (short)iVar3;
            break;
        case 3:
        sw3_trap:
            __builtin_trap(); /* SoftwareBreakpoint(1,0x3ff2b0) */
        case 4:
            *(int *)((int64_t)unaff_x19 + lVar1) = iVar3;
        }
    }
}

/* FUN_003ff2f0 @ 0x3ff2f0   (est. sk_r61_003ff2f0)
 * Ghidra: void FUN_003ff2f0(void)
 * Simple two-step release/decrement helper.
 * Confidence: medium
 * Notes: callees FUN_00406f08 (extern), FUN_004019d8 (sibling sk_r61_004019d8). */
void sk_r61_003ff2f0(void)
{
    sk_rt_00406f08();
    sk_r61_004019d8();
}
/* FUN_003ff318 @ 0x003ff318   (est. sk_r61_003ff318)
 * Ghidra: void FUN_003ff318(void)
 * Calls the shared runtime helper at FUN_00406f08 (dispatcher/state entry) and then
 * FUN_00401b7c. No arguments, no return value; a thin composition wrapper.
 * Confidence: medium
 * Notes: callees FUN_00406f08, FUN_00401b7c (runtime, out of slice). */
void sk_r61_003ff318(void)
{
    sk_rt_00406f08();
    sk_r61_00401b7c();
}

/* FUN_003ff330 @ 0x003ff330   (est. sk_r61_003ff330)
 * Ghidra: void FUN_003ff330(void)
 * Calls the shared runtime helper FUN_00406f08 then FUN_00401c18. No args/return.
 * Confidence: medium
 * Notes: callees FUN_00406f08, FUN_00401c18 (runtime, out of slice). */
void sk_r61_003ff330(void)
{
    sk_rt_00406f08();
    sk_r61_00401c18();
}

/* FUN_003ff348 @ 0x003ff348   (est. sk_r61_003ff348)
 * Ghidra: void FUN_003ff348(void)
 * Calls the shared runtime helper FUN_00406f08 then FUN_00401cc0. No args/return.
 * Confidence: medium
 * Notes: callees FUN_00406f08, FUN_00401cc0 (runtime, out of slice). */
void sk_r61_003ff348(void)
{
    sk_rt_00406f08();
    sk_r61_00401cc0();
}

/* FUN_003ff360 @ 0x003ff360   (est. sk_r61_003ff360)
 * Ghidra: void FUN_003ff360(void)
 * Calls the shared runtime helper FUN_00406f08 then FUN_00401d58. No args/return.
 * Confidence: medium
 * Notes: callees FUN_00406f08, FUN_00401d58 (runtime, out of slice). */
void sk_r61_003ff360(void)
{
    sk_rt_00406f08();
    sk_r61_00401d58();
}

/* FUN_003ff378 @ 0x003ff378   (est. sk_r61_003ff378)
 * Ghidra: void FUN_003ff378(void)
 * Calls the shared runtime helper FUN_00406f08 then FUN_00401df8. No args/return.
 * Confidence: medium
 * Notes: callees FUN_00406f08, FUN_00401df8 (runtime, out of slice). */
void sk_r61_003ff378(void)
{
    sk_rt_00406f08();
    sk_r61_00401df8();
}

/* FUN_003ff3a0 @ 0x003ff3a0   (est. sk_r61_003ff3a0)
 * Ghidra: void FUN_003ff3a0(long param_1)
 * Dispatches into a runtime context: forwards param_1 plus the object words at
 * offsets 0x18 and 0x10 to FUN_00406e78. Then queries a 128-bit capability/
 * region result via FUN_00377824(0x13f); if its high word is below 0x40 it
 * walks a back-pointer list node (ptr at lo-8, +0x40), re-reads a 128-bit
 * result, feeds it as a (lo, hi, kind=4) triple to FUN_003728b8 and finally
 * invokes FUN_00019858 (bump/commit). Otherwise returns without side effects.
 * Confidence: medium
 * Notes: callees FUN_00406e78, FUN_00377824, FUN_00357d44, FUN_0034cdf8,
 *         FUN_003728b8, FUN_00019858 (runtime, out of slice). */
void sk_r61_003ff3a0(int64_t param_1)
{
    sk_u128_t result;

    sk_rt_00406e78(param_1, *(uint64_t *)(param_1 + 0x18), *(uint64_t *)(param_1 + 0x10));
    result = sk_rt_00377824(0x13f);
    if (result.hi < 0x40) {
        sk_rt_00357d44(*(int64_t *)(result.lo + -8) + 0x40);
        result = sk_rt_0034cdf8();
        sk_rt_003728b8(result.lo, result.hi, 4);
        sk_rt_00019858();
    }
}

/* FUN_003ff424 @ 0x003ff424   (est. sk_r61_003ff424)
 * Ghidra: void FUN_003ff424(void)
 * Lock-style guard routine. Takes a lock, performs a capability/slot operation,
 * then conditionally runs a continuation: if the inherited flags carry and the
 * inherited count is below 0x19, it performs an update path (copying two bytes
 * into a record) else falls back to an alternate helper. Releases on exit.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x9/x9_00/x10/x16 and in_ZR (condition
 *         flags) are unrecoverable caller state; vtable-style indirect call
 *         through the x9 artifact. callees FUN_00350c5c, FUN_00406814,
 *         FUN_0034b57c, FUN_0035510c, FUN_0034c144, FUN_00406c08, FUN_00349cd0,
 *         FUN_003535e4, FUN_00349a9c, FUN_0036b270 (runtime, out of slice). */
void sk_r61_003ff424(void)
{
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint64_t extraout_x9 = 0;   /* register artifact (function pointer) */
    uint64_t extraout_x9_00 = 0; /* register artifact */
    uint64_t extraout_x10 = 0;  /* register artifact */
    uint64_t extraout_x16 = 0;  /* register artifact */
    uint64_t in_zr = 0;         /* register artifact (condition flags) */

    sk_rt_00350c5c();
    sk_rt_00406814();
    sk_rt_0034b57c();
    sk_rt_0035510c(extraout_x16);
    sk_rt_0034c144();
    if (in_zr && extraout_x10 < 0x19) {
        sk_rt_00406c08();
        ((void (*)(void))extraout_x9)();
        sk_rt_00349cd0();
        sk_rt_003535e4();
        *(uint8_t *)(extraout_x8 + 0x10) = *(uint8_t *)(extraout_x9_00 + 0x10);
        *(uint8_t *)(extraout_x8 + 0x11) = *(uint8_t *)(extraout_x9_00 + 0x11);
    } else {
        sk_rt_00349a9c();
    }
    sk_rt_0036b270();
}

/* FUN_003ff4c0 @ 0x003ff4c0   (est. sk_r61_003ff4c0)
 * Ghidra: void FUN_003ff4c0(void)
 * Method-dispatch wrapper on an inherited object: enters via FUN_00406748,
 * acquires state via FUN_00349530, calls the method pointer at object+0x10,
 * releases the slot at object+0x40 through FUN_00349104, then runs two teardown
 * helpers and the lock release.
 * Confidence: low
 * Notes: register artifact extraout_x16 is the this/object pointer (vtable call
 *         at offset 0x10). callees FUN_00406748, FUN_00349530, FUN_00349104,
 *         FUN_0034f22c, FUN_004082e0, FUN_0036b270 (runtime, out of slice). */
void sk_r61_003ff4c0(void)
{
    uint64_t thisptr = 0;       /* register artifact: this/object pointer */

    sk_rt_00406748();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)thisptr + 0x10)))();
    sk_rt_00349104(*(uint64_t *)((uint64_t)thisptr + 0x40));
    sk_rt_0034f22c();
    sk_rt_004082e0();
    sk_rt_0036b270();
}

/* FUN_003ff524 @ 0x003ff524   (est. sk_r61_003ff524)
 * Ghidra: void FUN_003ff524(void)
 * Method-dispatch wrapper on an inherited object: enters via FUN_00406748,
 * acquires state via FUN_00349530, calls the method pointer at object+0x18,
 * releases the slot at object+0x40 through FUN_00406de8, then performs a state
 * update and copies two bytes from the inherited frame (unaff_x22+0x10) into
 * the object at +0x28.
 * Confidence: low
 * Notes: register artifacts extraout_x16 (this/object, vtable call at +0x18)
 *         and unaff_x22 (caller frame). callees FUN_00406748, FUN_00349530,
 *         FUN_00406de8, FUN_0040774c, FUN_0036b118 (runtime, out of slice). */
void sk_r61_003ff524(void)
{
    uint64_t thisptr = 0;       /* register artifact: this/object pointer */
    uint64_t unaff_x22 = 0;     /* register artifact */

    sk_rt_00406748();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)thisptr + 0x18)))();
    sk_rt_00406de8(*(uint64_t *)((uint64_t)thisptr + 0x40));
    sk_rt_0040774c();
    sk_rt_0036b118();
    *(uint8_t *)((uint64_t)thisptr + 0x28) = *(uint8_t *)(unaff_x22 + 0x10);
    *(uint8_t *)((uint64_t)thisptr + 0x29) = *(uint8_t *)(unaff_x22 + 0x11);
}

/* FUN_003ff598 @ 0x003ff598   (est. sk_r61_003ff598)
 * Ghidra: void FUN_003ff598(void)
 * Method-dispatch wrapper on an inherited object: enters via FUN_00406748,
 * acquires state via FUN_00349530, calls the method pointer at object+0x20,
 * releases the slot at object+0x40 through FUN_00349104, then runs two teardown
 * helpers.
 * Confidence: low
 * Notes: register artifact extraout_x16 is the this/object pointer (vtable call
 *         at offset 0x20). callees FUN_00406748, FUN_00349530, FUN_00349104,
 *         FUN_00352dac, FUN_004082e0 (runtime, out of slice). */
void sk_r61_003ff598(void)
{
    uint64_t thisptr = 0;       /* register artifact: this/object pointer */

    sk_rt_00406748();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)thisptr + 0x20)))();
    sk_rt_00349104(*(uint64_t *)((uint64_t)thisptr + 0x40));
    sk_rt_00352dac();
    sk_rt_004082e0();
}

/* FUN_003ff5f8 @ 0x003ff5f8   (est. sk_r61_003ff5f8)
 * Ghidra: void FUN_003ff5f8(void)
 * Method-dispatch wrapper on an inherited object: enters via FUN_00406748,
 * acquires state via FUN_00349530, calls the method pointer at object+0x28,
 * releases the slot at object+0x40 through FUN_00406de8, then performs a state
 * update and copies two bytes from the inherited frame (unaff_x19+0x10) into
 * the object at +0x38.
 * Confidence: low
 * Notes: register artifacts extraout_x16 (this/object, vtable call at +0x28)
 *         and unaff_x19 (caller frame). callees FUN_00406748, FUN_00349530,
 *         FUN_00406de8, FUN_00407ae8 (runtime, out of slice). */
void sk_r61_003ff5f8(void)
{
    uint64_t thisptr = 0;       /* register artifact: this/object pointer */
    uint64_t unaff_x19 = 0;     /* register artifact */

    sk_rt_00406748();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)thisptr + 0x28)))();
    sk_rt_00406de8(*(uint64_t *)((uint64_t)thisptr + 0x40));
    sk_rt_00407ae8();
    *(uint8_t *)((uint64_t)thisptr + 0x38) = *(uint8_t *)(unaff_x19 + 0x10);
    *(uint8_t *)((uint64_t)thisptr + 0x39) = *(uint8_t *)(unaff_x19 + 0x11);
}

/* FUN_003ff664 @ 0x003ff664   (est. sk_r61_003ff664)
 * Ghidra: ulong FUN_003ff664(void)
 * Lock/slot query returning a size or offset. Takes a lock, runs an operation,
 * then looks up a 128-bit result keyed by an inherited object field at +0x54.
 * Depending on an inherited width selector (unaff_w20) and a byte-count from a
 * helper, it either tests a word at an inherited base+index (1/2/4-byte) and
 * branches to a common tail, traps (SoftwareBreakpoint) for the 3-byte case, or
 * returns a page-size-adjusted value. Returns 0 when the width selector is zero.
 * Confidence: low
 * Notes: many register artifacts (extraout_x1/x8/x10/x16, w8/w8_00/w9/w11/w12,
 *         unaff_x19, unaff_w20) are unrecoverable caller state; SoftwareBreakpoint
 *         at 0x3ff780; 128-bit result used via .hi/.lo. callees FUN_00350c5c,
 *         FUN_00406814, FUN_0034ada0, FUN_00355008, FUN_00356638, FUN_00356e74,
 *         FUN_004077ec, FUN_00356e64, FUN_0040692c, FUN_000839f8. */
uint64_t sk_r61_003ff664(void)
{
    uint32_t v1;
    uint32_t v2;
    uint32_t v3;
    bool b5;
    bool b6;
    uint64_t v7;
    uint64_t v8;
    sk_u128_t r9;
    uint64_t extraout_x1 = 0;   /* register artifact */
    uint32_t extraout_w8 = 0;   /* register artifact */
    int32_t extraout_w8_00 = 0; /* register artifact */
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint32_t extraout_w9 = 0;   /* register artifact */
    uint64_t extraout_x10 = 0;  /* register artifact */
    uint32_t extraout_w11 = 0;  /* register artifact */
    uint32_t extraout_w12 = 0;  /* register artifact */
    uint64_t extraout_x16 = 0;  /* register artifact */
    uint64_t unaff_x19 = 0;     /* register artifact */
    uint32_t unaff_w20 = 0;     /* register artifact */

    sk_rt_00350c5c();
    sk_rt_00406814();
    v7 = sk_rt_0034ada0();
    r9 = sk_rt_00355008(v7, *(uint32_t *)((uint64_t)extraout_x16 + 0x54));
    v7 = r9.hi;
    if (unaff_w20 == 0) {
        return 0;
    }
    if (extraout_w9 < unaff_w20) {
        sk_rt_00356638(*(uint64_t *)((uint64_t)extraout_x8 + 0x40), r9.lo, v7, r9.lo);
        sk_rt_00356e74();
        v2 = extraout_w12;
        if (extraout_w11 < 0x100) {
            v2 = 1;
        }
        v1 = 0;
        if (1 < extraout_w11) {
            v1 = v2;
        }
        b5 = 3 < v1;
        b6 = v1 == 4;
        v7 = extraout_x1;
        switch (v1) {
        case 1:
            if (*(char *)(unaff_x19 + extraout_x10) != '\0') {
                goto lab_3ff724;
            }
            break;
        case 2:
            if (*(short *)(unaff_x19 + extraout_x10) != 0) {
                goto lab_3ff724;
            }
            break;
        case 3:
            __builtin_trap(); /* SoftwareBreakpoint(1,0x3ff780) */
        case 4:
            if (*(int32_t *)(unaff_x19 + extraout_x10) != 0) {
                goto lab_3ff724;
            }
            break;
        }
    }
    b5 = 0xfff < (uint32_t)v7;
    b6 = (uint32_t)v7 == 0x1000;
    if (!b5) {
        sk_rt_0040692c();
        v2 = 0;
        if (!b5 || b6) {
            v2 = (uint32_t)extraout_w8_00 + 1;
        }
        return (uint64_t)v2;
    }
    v8 = sk_rt_000839f8().lo;
    return v8;

lab_3ff724:
    sk_rt_004077ec();
    v3 = extraout_w8;
    if (b5 && !b6) {
        v3 = 0;
    }
    v8 = sk_rt_00356e64(v3);
    return v8;
}

/* FUN_003ff958 @ 0x003ff958   (est. sk_r61_003ff958)
 * Ghidra: void FUN_003ff958(long param_1)
 * Dispatches into a runtime context: forwards param_1 plus the object words at
 * offsets 0x18 and 0x10 to FUN_00406e78. Then queries a 128-bit result via
 * FUN_00377824(0x13f); if its high word is below 0x40 it walks a back-pointer
 * list node (ptr at lo-8, +0x40), invokes FUN_00407fd8, re-reads a 128-bit
 * result, feeds it as a (lo, hi, kind=3) triple to FUN_003728b8 and finally
 * calls FUN_00019858 (commit). Otherwise returns without side effects.
 * Confidence: medium
 * Notes: callees FUN_00406e78, FUN_00377824, FUN_00357d44, FUN_00407fd8,
 *         FUN_0034cdf8, FUN_003728b8, FUN_00019858 (runtime, out of slice). */
void sk_r61_003ff958(int64_t param_1)
{
    sk_u128_t result;

    sk_rt_00406e78(param_1, *(uint64_t *)(param_1 + 0x18), *(uint64_t *)(param_1 + 0x10));
    result = sk_rt_00377824(0x13f);
    if (result.hi < 0x40) {
        sk_rt_00357d44(*(int64_t *)(result.lo + -8) + 0x40);
        sk_rt_00407fd8();
        result = sk_rt_0034cdf8();
        sk_rt_003728b8(result.lo, result.hi, 3);
        sk_rt_00019858();
    }
}

/* FUN_003ff9cc @ 0x003ff9cc   (est. sk_r61_003ff9cc)
 * Ghidra: void FUN_003ff9cc(void)
 * Lock-style guard routine. Takes a lock, performs a capability/slot operation,
 * then conditionally runs a continuation: if the inherited flags carry and the
 * inherited count is below 0x19, it performs an update path (copying one byte
 * into a record) else falls back to an alternate helper. Releases on exit.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x9/x9_00/x10/x16 and in_ZR (condition
 *         flags) are unrecoverable caller state; indirect call through the x9
 *         artifact. callees FUN_00350c5c, FUN_00406814, FUN_0034b57c,
 *         FUN_0035510c, FUN_0034c144, FUN_00406c08, FUN_00349cd0, FUN_003535e4,
 *         FUN_00349a9c, FUN_0036b270 (runtime, out of slice). */
void sk_r61_003ff9cc(void)
{
    uint64_t extraout_x8 = 0;    /* register artifact */
    uint64_t extraout_x9 = 0;    /* register artifact (function pointer) */
    uint64_t extraout_x9_00 = 0; /* register artifact */
    uint64_t extraout_x10 = 0;   /* register artifact */
    uint64_t extraout_x16 = 0;   /* register artifact */
    uint64_t in_zr = 0;          /* register artifact (condition flags) */

    sk_rt_00350c5c();
    sk_rt_00406814();
    sk_rt_0034b57c();
    sk_rt_0035510c(extraout_x16);
    sk_rt_0034c144();
    if (in_zr && extraout_x10 < 0x19) {
        sk_rt_00406c08();
        ((void (*)(void))extraout_x9)();
        sk_rt_00349cd0();
        sk_rt_003535e4();
        *(uint8_t *)(extraout_x8 + 0x10) = *(uint8_t *)(extraout_x9_00 + 0x10);
    } else {
        sk_rt_00349a9c();
    }
    sk_rt_0036b270();
}

/* FUN_003ffa74 @ 0x003ffa74   (est. sk_r61_003ffa74)
 * Ghidra: void FUN_003ffa74(void)
 * Teardown/cleanup wrapper on an inherited object. Runs two initial helpers, then
 * looks up a 128-bit result keyed by (0, inherited x8) via FUN_00377824 and
 * forwards its low word twice to FUN_0034ab20. Calls the method pointer at
 * object+8, releases the slot at object+0x40 through FUN_0034de54, and finally
 * invokes FUN_0036b118 with the word at inherited x8_00+8.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x8_00 and extraout_x16 (this/object,
 *         vtable call at +8) are unrecoverable caller state; 128-bit result used
 *         via .lo. callees FUN_00407478, FUN_003561f4, FUN_00377824,
 *         FUN_0034ab20, FUN_0034de54, FUN_0036b118 (runtime, out of slice). */
void sk_r61_003ffa74(void)
{
    uint64_t u1;
    uint64_t extraout_x8 = 0;   /* register artifact */
    uint64_t extraout_x8_00 = 0; /* register artifact */
    uint64_t thisptr = 0;       /* register artifact: this/object pointer */

    sk_rt_00407478();
    sk_rt_003561f4();
    u1 = sk_rt_00377824(0, extraout_x8).lo;
    sk_rt_0034ab20(u1, u1);
    ((void (*)(void))(**(uint64_t **)((uint64_t)thisptr + 8)))();
    sk_rt_0034de54(*(uint64_t *)((uint64_t)thisptr + 0x40));
    sk_rt_0036b118(*(uint64_t *)(extraout_x8_00 + 8));
}
/* FUN_003ffad8 @ 0x003ffad8   (est. sk_r61_003ffad8)
 * Ghidra: void FUN_003ffad8(void)
 * Microkernel method-dispatch helper: disables preemption, prepares the object, invokes a
 * vtable method at offset 0x10, then releases a capability/tag referenced from the object.
 * Copies a byte from the source object into the destination object before re-enabling
 * preemption. No arguments or return value.
 * Confidence: low
 * Notes: vtable dispatch via register artifact this (extraout_x16 + 0x10); callees
 * FUN_00406748, FUN_00349530, FUN_00349104, FUN_0034f22c, FUN_0036b270; byte copy between
 * extraout_x8/x9 register artifacts. */
void sk_r61_003ffad8(void)
{
    uint64_t extraout_x8 = 0;   /* register artifact: source object pointer (unrecoverable) */
    uint64_t extraout_x9 = 0;   /* register artifact: destination object pointer (unrecoverable) */
    uint64_t extraout_x16 = 0;  /* register artifact: this pointer for vtable dispatch */

    sk_rt_00406748();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x10)))();
    sk_rt_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0034f22c();
    *(uint8_t *)(extraout_x9 + 0x10) = *(uint8_t *)(extraout_x8 + 0x10);
    sk_rt_0036b270();
}

/* FUN_003ffb40 @ 0x003ffb40   (est. sk_r61_003ffb40)
 * Ghidra: void FUN_003ffb40(void)
 * Method-dispatch helper analogous to sk_r61_003ffad8 but invoking the vtable method at
 * offset 0x18. After the call it releases a capability, disables/enables preemption and
 * copies a byte from the caller object into a message register area.
 * Confidence: low
 * Notes: vtable dispatch via register artifact this (extraout_x16 + 0x18); callees
 * FUN_00406748, FUN_00349530, FUN_00406de8, FUN_0040774c, FUN_0036b118, FUN_004082c8. */
void sk_r61_003ffb40(void)
{
    uint64_t extraout_x16 = 0;  /* register artifact: this pointer for vtable dispatch */
    uint64_t unaff_x22 = 0;     /* register artifact: caller object pointer (unrecoverable) */

    sk_rt_00406748();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x18)))();
    sk_rt_00406de8(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0040774c();
    sk_rt_0036b118();
    sk_rt_004082c8(*(uint8_t *)(unaff_x22 + 0x10));
}

/* FUN_003ffba8 @ 0x003ffba8   (est. sk_r61_003ffba8)
 * Ghidra: void FUN_003ffba8(void)
 * Method-dispatch helper invoking the vtable method at offset 0x20, then releasing a
 * capability/tag referenced at this+0x40 and running a finalization step.
 * Confidence: low
 * Notes: vtable dispatch via register artifact this (extraout_x16 + 0x20); callees
 * FUN_00406748, FUN_00349530, FUN_00349104, FUN_00407200. */
void sk_r61_003ffba8(void)
{
    uint64_t extraout_x16 = 0;  /* register artifact: this pointer for vtable dispatch */

    sk_rt_00406748();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x20)))();
    sk_rt_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_00407200();
}

/* FUN_003ffc04 @ 0x003ffc04   (est. sk_r61_003ffc04)
 * Ghidra: void FUN_003ffc04(void)
 * Method-dispatch helper invoking the vtable method at offset 0x28, then releasing a
 * capability and copying a byte from the caller object into a message register area.
 * Confidence: low
 * Notes: vtable dispatch via register artifact this (extraout_x16 + 0x28); callees
 * FUN_00406748, FUN_00349530, FUN_00406de8, FUN_00407ae8, FUN_004082c8. */
void sk_r61_003ffc04(void)
{
    uint64_t extraout_x16 = 0;  /* register artifact: this pointer for vtable dispatch */
    uint64_t unaff_x19 = 0;     /* register artifact: caller object pointer (unrecoverable) */

    sk_rt_00406748();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x28)))();
    sk_rt_00406de8(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_00407ae8();
    sk_rt_004082c8(*(uint8_t *)(unaff_x19 + 0x10));
}

/* FUN_003ffc64 @ 0x003ffc64   (est. sk_r61_003ffc64)
 * Ghidra: ulong FUN_003ffc64(void)
 * Checks the availability / contents of a fault/slot entry. Reads a capability index via a
 * 16-byte helper pair, and depending on the tracked size class, tests whether the location
 * is non-zero (byte/word/dword width) and returns the resulting status code from a helper.
 * Falls through to a large-page check when the size class does not match, returning an
 * error-code-derived value. Contains a SoftwareBreakpoint trap in the 3-byte size case.
 * Confidence: low
 * Notes: register artifacts extraout_w8/w9/w11/w12/x1/x8/x10/x16, unaff_x19/w20;
 * sk_u128_t from FUN_00355008 used as .lo/.hi; trap at 0x3ffd6c; callees FUN_00350c5c,
 * FUN_00406814, FUN_0034ada0, FUN_00355008, FUN_00356638, FUN_00407f30, FUN_00356e74,
 * FUN_004077ec, FUN_00356e64, FUN_0040692c, FUN_000839f8. */
uint64_t sk_r61_003ffc64(void)
{
    uint32_t uVar1;
    uint32_t uVar2;
    uint32_t uVar3;
    bool bVar5;
    bool bVar6;
    uint64_t uVar7;
    uint64_t uVar8;
    uint32_t extraout_w8 = 0;     /* register artifact (unrecoverable) */
    uint32_t extraout_w8_00 = 0;  /* register artifact (unrecoverable) */
    uint64_t extraout_x1 = 0;     /* register artifact (unrecoverable) */
    uint64_t extraout_x8 = 0;     /* register artifact (unrecoverable) */
    uint32_t extraout_w9 = 0;     /* register artifact (unrecoverable) */
    uint64_t extraout_x10 = 0;    /* register artifact (unrecoverable) */
    uint32_t extraout_w11 = 0;    /* register artifact (unrecoverable) */
    uint32_t extraout_w12 = 0;    /* register artifact (unrecoverable) */
    uint64_t extraout_x16 = 0;    /* register artifact: this pointer (unrecoverable) */
    uint64_t unaff_x19 = 0;       /* register artifact: object pointer (unrecoverable) */
    uint32_t unaff_w20 = 0;       /* register artifact: tracked size (unrecoverable) */
    sk_u128_t auVar9;

    sk_rt_00350c5c();
    sk_rt_00406814();
    uVar7 = sk_rt_0034ada0();
    auVar9 = sk_rt_00355008(uVar7, *(uint32_t *)(extraout_x16 + 0x54));
    uVar7 = auVar9.hi;
    if (unaff_w20 == 0) {
        return 0;
    }
    if (extraout_w9 < unaff_w20) {
        sk_rt_00356638(*(uint64_t *)(extraout_x8 + 0x40), auVar9.lo, uVar7, auVar9.lo);
        sk_rt_00407f30();
        sk_rt_00356e74();
        uVar2 = extraout_w12;
        if (extraout_w11 < 0x100) {
            uVar2 = 1;
        }
        uVar1 = 0;
        if (1 < extraout_w11) {
            uVar1 = uVar2;
        }
        bVar5 = 3 < uVar1;
        bVar6 = uVar1 == 4;
        uVar7 = extraout_x1;
        switch (uVar1) {
        case 1:
            if (*(char *)(unaff_x19 + extraout_x10) != '\0') {
                goto lab_send;
            }
            break;
        case 2:
            if (*(short *)(unaff_x19 + extraout_x10) != 0) {
                goto lab_send;
            }
            break;
        case 3:
            __builtin_trap(); /* SoftwareBreakpoint(1,0x3ffd6c) */
        case 4:
            if (*(int *)(unaff_x19 + extraout_x10) != 0) {
                goto lab_send;
            }
            break;
        }
    }
    bVar5 = 0xfff < (uint32_t)uVar7;
    bVar6 = (uint32_t)uVar7 == 0x1000;
    if (!bVar5) {
        sk_rt_0040692c();
        uVar2 = 0;
        if (!bVar5 || bVar6) {
            uVar2 = (uint32_t)(extraout_w8_00 + 1);
        }
        return (uint64_t)uVar2;
    }
    uVar8 = sk_rt_000839f8().lo;
    return uVar8;

lab_send:
    sk_rt_004077ec();
    uVar3 = extraout_w8;
    if (bVar5 && !bVar6) {
        uVar3 = 0;
    }
    uVar8 = sk_rt_00356e64(uVar3);
    return uVar8;
}

/* FUN_003fff34 @ 0x003fff34   (est. sk_r61_003fff34)
 * Ghidra: void FUN_003fff34(void)
 * Retrieves a descriptor/object via a 16-byte-return helper; when its size field is below
 * 0x40, dereferences the object link to obtain a pointer, adjusts it, and runs a sequence
 * of finalization/runtime helpers on it.
 * Confidence: low
 * Notes: sk_u128_t from FUN_004080f8 read as .lo/.hi; callees FUN_004080f8, FUN_00357d44,
 * FUN_0034d1c0, FUN_003728b8, FUN_00019858. */
void sk_r61_003fff34(void)
{
    sk_u128_t auVar1;

    auVar1 = sk_rt_004080f8();
    if (auVar1.hi < 0x40) {
        sk_rt_00357d44(*(int64_t *)(auVar1.lo + -8) + 0x40);
        sk_rt_0034d1c0();
        sk_rt_003728b8();
        sk_rt_00019858();
    }
}

/* FUN_003fff9c @ 0x003fff9c   (est. sk_r61_003fff9c)
 * Ghidra: void FUN_003fff9c(void)
 * Thin wrapper: disables preemption and defers to sk_r61_003fffb4 (the state-flush helper).
 * Confidence: medium
 * Notes: callees FUN_00406e78 (preemption off) and sibling FUN_003fffb4. */
void sk_r61_003fff9c(void)
{
    sk_rt_00406e78();
    sk_r61_003fffb4();
}

/* FUN_003fffb4 @ 0x003fffb4   (est. sk_r61_003fffb4)
 * Ghidra: void FUN_003fffb4(void)
 * Flushes/commits a capability state: prepares the runtime, invokes a checkpoint with tag
 * 0x13f, and if the returned size is small, posts a message (0xff) from the caller's
 * object fields and re-arms the checkpoint; finally commits the 16-byte payload and wakes
 * the consumer.
 * Confidence: low
 * Notes: register artifacts extraout_x1, extraout_x1_00, unaff_x19; sk_u128_t from
 * FUN_00377824/00351244 read as .lo/.hi; callees FUN_00353d70, FUN_00407dc0,
 * FUN_00377824, FUN_0040761c, FUN_00310d68, FUN_00351244, FUN_003728b8, FUN_00019858. */
void sk_r61_003fffb4(void)
{
    uint64_t uVar1;
    uint64_t extraout_x1 = 0;     /* register artifact (unrecoverable) */
    uint64_t extraout_x1_00 = 0;  /* register artifact (unrecoverable) */
    uint64_t unaff_x19 = 0;       /* register artifact: caller object pointer */
    sk_u128_t auVar2;

    sk_rt_00353d70();
    sk_rt_00407dc0();
    sk_rt_00377824(0x13f);
    if (extraout_x1 < 0x40) {
        sk_rt_0040761c(0xff, *(uint64_t *)(unaff_x19 + 0x28), *(uint64_t *)(unaff_x19 + 0x18));
        uVar1 = sk_rt_00377824().lo;
        sk_rt_00310d68(0x13f, uVar1);
        if (extraout_x1_00 < 0x40) {
            auVar2 = sk_rt_00351244();
            sk_rt_003728b8(auVar2.lo, auVar2.hi, 4);
            sk_rt_00019858();
        }
    }
}

/* FUN_00400084 @ 0x00400084   (est. sk_r61_00400084)
 * Ghidra: void FUN_00400084(void)
 * Thin wrapper: disables preemption and defers to sk_r61_0040009c (the 5-argument
 * message/fault handling core).
 * Confidence: medium
 * Notes: callees FUN_00406e78 (preemption off) and sibling FUN_0040009c. */
void sk_r61_00400084(void)
{
    sk_rt_00406e78();
    /* Decompiled as FUN_0040009c() with no explicit args (the 5 real arguments arrive via
       the caller's registers — register-artifact pattern). Forward decl needs 5 args. */
    sk_r61_0040009c(0, 0, 0, 0, 0);
}

/* FUN_0040009c @ 0x0040009c   (est. sk_r61_0040009c)
 * Ghidra: void FUN_0040009c(undefined8 param_1,undefined8 param_2,long param_3,
 *                           undefined8 param_4, undefined8 param_5)
 * Core message/fault send: builds an aligned output slot from the caller object's size
 * class, validates size-class constraints and the computed tail length, copies the
 * 16-byte message header/payload, and posts the result. On an unexpected size class it
 * falls back to an error-reporting helper. Re-enables the runtime at the end.
 * Confidence: low
 * Notes: many register artifacts (extraout_x1/x8/x8_00/x8_01/x8_02/x8_03/x16/x16_00,
 * unaff_x19); sk_u128_t via FUN_00377824/003507e0/000839f8; vtable-ish indirect calls
 * through extraout_x8_01/extraout_x8_03; callees FUN_0008e518, FUN_0034fc7c,
 * FUN_00377824, FUN_000a6f88, FUN_003507e0, FUN_00355d60, FUN_0036b270, FUN_000839f8,
 * FUN_00350548, FUN_00350750, FUN_000839d8, FUN_00117cc4, FUN_00408510, FUN_0008e500. */
void sk_r61_0040009c(uint64_t p1, uint64_t p2, int64_t p3, uint64_t p4, uint64_t p5)
{
    uint32_t uVar1;
    uint32_t uVar2;
    int64_t lVar6;
    int64_t lVar9;
    uint64_t *extraout_x1 = 0;      /* register artifact: data pointer */
    uint64_t extraout_x8 = 0;       /* register artifact (unrecoverable) */
    uint64_t extraout_x8_00 = 0;    /* register artifact (unrecoverable) */
    uint64_t extraout_x8_01 = 0;    /* register artifact: indirect call target */
    uint64_t *extraout_x8_02 = 0;   /* register artifact: source data pointer */
    uint64_t extraout_x8_03 = 0;    /* register artifact: indirect call target */
    uint64_t extraout_x16 = 0;      /* register artifact: this pointer */
    uint64_t extraout_x16_00 = 0;   /* register artifact: this pointer */
    uint64_t unaff_x19 = 0;         /* register artifact: base pointer */
    uint64_t uVar4;
    uint64_t uVar5;
    uint64_t uVar10;
    uint64_t *puVar7;
    uint64_t *puVar8;
    sk_u128_t auVar11;

    sk_rt_0008e518();
    sk_rt_0034fc7c();
    uVar4 = sk_rt_00377824(0).lo;
    sk_rt_000a6f88();
    lVar9 = *(int64_t *)(extraout_x8 + 0x40);
    sk_rt_00377824(0, *(uint64_t *)(p3 + 0x28), *(uint64_t *)(p3 + 0x18), p4, p5);
    uVar5 = sk_rt_000a6f88();
    uVar1 = *(uint32_t *)(extraout_x16_00 + 0x50);
    lVar6 = *(int64_t *)(extraout_x8_00 + 0x40);
    if (*(int32_t *)(extraout_x16_00 + 0x54) == 0) {
        lVar6 = lVar6 + 1;
    }
    uVar2 = ((uint32_t)uVar1 & 0xff) | (*(uint32_t *)(extraout_x16 + 0x50) & 0xf8);
    if ((uVar2 < 8 && ((*(uint32_t *)(extraout_x16 + 0x50) | uVar1) & 0x100000) == 0) &&
        (lVar6 - (-((lVar9 + 7U & 0xfffffffffffffff8ULL) + (uint64_t)(uint8_t)uVar1) - 0x11 |
                  (uint64_t)uVar1 & 0xff) < 0x19)) {
        auVar11 = sk_rt_003507e0(*(uint64_t *)(extraout_x16 + 0x10));
        ((void (*)(uint64_t, uint64_t, uint64_t))extraout_x8_01)(auVar11.lo, auVar11.hi, uVar4);
        puVar7 = (uint64_t *)((uint64_t)(unaff_x19 + lVar9 + 7U) & 0xfffffffffffffff8ULL);
        sk_rt_00355d60((int64_t)extraout_x1 + lVar9);
        uVar4 = extraout_x8_02[1];
        uVar10 = *extraout_x8_02;
        puVar8 = puVar7 + 2;
        puVar7[1] = extraout_x8_02[1];
        *puVar7 = uVar10;
        puVar7 = extraout_x8_02 + 2;
        sk_rt_0036b270(uVar4);
        auVar11 = sk_rt_000839f8(puVar7, 1, uVar5);
        if ((uint32_t)auVar11.lo == 0) {
            sk_rt_00350548(*(uint64_t *)(extraout_x16_00 + 0x10), puVar8);
            ((void (*)(void))extraout_x8_03)();
            sk_rt_00350750(puVar8);
            sk_rt_000839d8();
        } else {
            sk_rt_00117cc4(puVar8, puVar7, lVar6);
        }
        *(uint8_t *)(lVar6 + (int64_t)puVar8) = *(uint8_t *)(lVar6 + (int64_t)puVar7);
    } else {
        sk_rt_00408510(uVar2 | 7, *extraout_x1);
    }
    sk_rt_0008e500();
}

/* FUN_0040025c @ 0x0040025c   (est. sk_r61_0040025c)
 * Ghidra: void FUN_0040025c(void)
 * Performs a capability/message send from a caller frame: prepares the runtime, computes an
 * aligned destination slot from the tracked size class, and posts the message via a
 * size-class dispatch table (indirect jump through the class descriptor at +8). Returns
 * silently if the post fails.
 * Confidence: low
 * Notes: register artifacts extraout_x1, extraout_x16, unaff_x21, unaff_x22; vtable
 * dispatch at extraout_x16+8 and lVar4+8; jumptable at 0x0040036c not recoverable
 * (treated as indirect call); callees FUN_00077888, FUN_003509ec, FUN_00377824,
 * FUN_0034ab20, FUN_0036b118, FUN_000839f8. */
void sk_r61_0040025c(void)
{
    int iVar1;
    uint64_t uVar2;
    int64_t lVar3;
    uint64_t extraout_x1 = 0;   /* register artifact (unrecoverable) */
    uint64_t extraout_x16 = 0;  /* register artifact: this pointer for vtable dispatch */
    int64_t lVar4;
    uint64_t uVar5;
    uint64_t uVar6;
    uint64_t unaff_x21 = 0;     /* register artifact: caller object pointer */
    uint64_t unaff_x22 = 0;     /* register artifact: base pointer */

    sk_rt_00077888();
    sk_rt_003509ec();
    uVar2 = sk_rt_00377824(0, *(uint64_t *)(extraout_x1 + 0x20), *(uint64_t *)(unaff_x21 + 0x10)).lo;
    sk_rt_0034ab20(uVar2, uVar2);
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 8)))();
    uVar6 = (uint64_t)(unaff_x22 + *(int64_t *)(extraout_x16 + 0x40) + 7U) & 0xfffffffffffffff8ULL;
    sk_rt_0036b118(*(uint64_t *)(uVar6 + 8));
    lVar3 = sk_rt_00377824(0, *(uint64_t *)(unaff_x21 + 0x28), *(uint64_t *)(unaff_x21 + 0x18)).lo;
    lVar4 = *(int64_t *)(lVar3 + -8);
    uVar5 = (uint64_t)*(uint8_t *)(lVar4 + 0x50);
    uVar6 = uVar6 + uVar5 + 0x10;
    iVar1 = (int)sk_rt_000839f8(uVar6 & (uVar5 ^ 0xffffffffffffffffULL), 1, lVar3).lo;
    if (iVar1 != 0) {
        return;
    }
    /* WARNING: jumptable at 0x0040036c not recoverable; indirect jump treated as call */
    ((void (*)(uint64_t, uint64_t))(**(uint64_t **)((uint64_t)lVar4 + 8)))(uVar6 & (uVar5 ^ 0xffffffffffffffffULL), lVar3);
    return;
}

/* FUN_00400388 @ 0x00400388   (est. sk_r61_00400388)
 * Ghidra: void FUN_00400388(void)
 * Message/slot post core: prepares the runtime and object, invokes a vtable method at
 * offset 0x10, then copies the 16-byte message from the source frame into the destination
 * frame (both aligned by size class). Validates via a pair of 16-byte helpers and either
 * completes the post or raises an error path, copying the trailing byte between the two
 * aligned slots.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x16/x16_00, unaff_x19, unaff_x23; sk_u128_t from
 * FUN_000839f8; indirect call through extraout_x8; callees FUN_00084220, FUN_00406e34,
 * FUN_0034fc7c, FUN_00377824, FUN_00349530, FUN_004072e8, FUN_004077dc, FUN_0036b270,
 * FUN_003518dc, FUN_000839f8, FUN_0006b6f4, FUN_0034ee88, FUN_000839d8, FUN_00117cc4,
 * FUN_00084234. */
void sk_r61_00400388(void)
{
    int64_t lVar1;
    int64_t lVar4;
    uint64_t uVar2;
    uint64_t uVar3;
    uint64_t extraout_x8 = 0;      /* register artifact: indirect call target */
    uint64_t extraout_x16 = 0;     /* register artifact: this pointer for vtable dispatch */
    uint64_t extraout_x16_00 = 0;  /* register artifact: this pointer */
    uint64_t unaff_x19 = 0;        /* register artifact: destination frame pointer */
    uint64_t unaff_x23 = 0;        /* register artifact: source frame pointer */
    int iVar5;
    uint64_t uVar6;
    uint64_t uVar9;
    uint64_t *puVar7;
    uint64_t *puVar8;
    sk_u128_t auVar10;

    sk_rt_00084220();
    sk_rt_00406e34();
    sk_rt_0034fc7c();
    sk_rt_00377824(0);
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 0x10)))();
    lVar4 = *(int64_t *)(extraout_x16 + 0x40) + 7;
    puVar7 = (uint64_t *)((uint64_t)(lVar4 + unaff_x19) & 0xfffffffffffffff8ULL);
    puVar8 = (uint64_t *)((uint64_t)(lVar4 + unaff_x23) & 0xfffffffffffffff8ULL);
    uVar6 = puVar8[1];
    uVar9 = *puVar8;
    puVar7[1] = puVar8[1];
    *puVar7 = uVar9;
    sk_rt_004072e8();
    sk_rt_004077dc();
    uVar2 = (uint64_t)*(uint8_t *)(extraout_x16_00 + 0x50);
    uVar3 = uVar2 + 0x10 + (uint64_t)puVar7 & (uVar2 ^ 0xffffffffffffffffULL);
    uVar2 = uVar2 + 0x10 + (uint64_t)puVar8 & (uVar2 ^ 0xffffffffffffffffULL);
    sk_rt_0036b270(uVar6);
    sk_rt_003518dc(uVar2);
    auVar10 = sk_rt_000839f8();
    if ((uint32_t)auVar10.lo == 0) {
        sk_rt_0006b6f4(*(uint64_t *)(extraout_x16_00 + 0x10));
        ((void (*)(void))extraout_x8)();
        sk_rt_0034ee88(uVar3);
        sk_rt_000839d8();
        iVar5 = *(int32_t *)(extraout_x16_00 + 0x54);
        lVar4 = *(int64_t *)(extraout_x16_00 + 0x40);
    } else {
        iVar5 = *(int32_t *)(extraout_x16_00 + 0x54);
        lVar4 = *(int64_t *)(extraout_x16_00 + 0x40);
        lVar1 = lVar4;
        if (iVar5 == 0) {
            lVar1 = lVar4 + 1;
        }
        sk_rt_0006b6f4(auVar10.lo, auVar10.hi, lVar1);
        sk_rt_00117cc4();
    }
    if (iVar5 == 0) {
        lVar4 = lVar4 + 1;
    }
    *(uint8_t *)(lVar4 + uVar3) = *(uint8_t *)(lVar4 + uVar2);
    sk_rt_00084234();
}

/* FUN_004004ac @ 0x004004ac   (est. sk_r61_004004ac)
 * Ghidra: void FUN_004004ac(void)
 * Thin wrapper: disables preemption and defers to sk_r61_004004c4 (the message post core).
 * Confidence: medium
 * Notes: callees FUN_00406e78 (preemption off) and sibling FUN_004004c4. */
void sk_r61_004004ac(void)
{
    sk_rt_00406e78();
    sk_r61_004004c4();
}

/* FUN_004004c4 @ 0x004004c4   (est. sk_r61_004004c4)
 * Ghidra: void FUN_004004c4(void)
 * Message post core with preemption already disabled: invokes the vtable method at offset
 * 0x18, swaps the 16-byte capability pair between the object and a caller frame, computes
 * the aligned slot for both source and destination, and posts. On validation failure it
 * raises an error path; finally re-arms and completes with a runtime pair.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x9/x9_00/x16/x16_00, unaff_x25, unaff_x30;
 * sk_u128_t via FUN_000839f8/000b4390; indirect calls through extraout_x8/x9/x9_00;
 * callees FUN_00084220, FUN_00406e34, FUN_0034fc7c, FUN_00377824, FUN_00349530,
 * FUN_0040749c, FUN_0036b270, FUN_0036b118, FUN_004072e8, FUN_004077dc, FUN_003518dc,
 * FUN_000839f8, FUN_000b4390, FUN_00408314, FUN_0034ee88, FUN_000839d8, FUN_00117cc4,
 * FUN_00407a80, FUN_00084234. */
void sk_r61_004004c4(void)
{
    int iVar1;
    uint64_t uVar2;
    int64_t lVar3;
    uint64_t uVar4;
    uint64_t uVar6;
    uint64_t uVar7;
    uint64_t uVar8;
    uint64_t extraout_x8 = 0;      /* register artifact: indirect call target */
    uint64_t extraout_x9 = 0;      /* register artifact: indirect call target */
    uint64_t extraout_x9_00 = 0;   /* register artifact: indirect call target */
    uint64_t extraout_x16 = 0;     /* register artifact: this pointer for vtable dispatch */
    uint64_t *puVar5;
    uint64_t extraout_x16_00 = 0;  /* register artifact: this pointer */
    uint64_t *unaff_x25 = 0;       /* register artifact: caller frame pointer */
    uint64_t unaff_x30 = 0;        /* register artifact (unrecoverable) */
    sk_u128_t auVar9;

    sk_rt_00084220();
    sk_rt_00406e34();
    sk_rt_0034fc7c();
    sk_rt_00377824(0);
    sk_rt_00349530();
    puVar5 = (uint64_t *)(extraout_x16 + 0x18);
    ((void (*)(void))(*(uint64_t *)puVar5))();
    sk_rt_0040749c(*(uint64_t *)(extraout_x16 + 0x40));
    uVar7 = *(uint64_t *)(extraout_x16 + 0x20);
    uVar2 = unaff_x25[1];
    uVar8 = *unaff_x25;
    *(uint64_t *)(extraout_x16 + 0x20) = unaff_x25[1];
    *puVar5 = uVar8;
    sk_rt_0036b270(uVar2);
    sk_rt_0036b118(uVar7);
    sk_rt_004072e8();
    sk_rt_004077dc();
    uVar4 = (uint64_t)*(uint8_t *)(extraout_x16_00 + 0x50);
    uVar6 = uVar4 + 0x10 + (uint64_t)puVar5 & (uVar4 ^ 0xffffffffffffffffULL);
    sk_rt_003518dc(uVar6);
    lVar3 = sk_rt_000839f8().lo;
    sk_rt_003518dc(uVar4 + 0x10 + (uint64_t)unaff_x25 & (uVar4 ^ 0xffffffffffffffffULL));
    auVar9 = sk_rt_000839f8();
    if ((int)lVar3 == 0) {
        if ((uint32_t)auVar9.lo == 0) {
            auVar9 = sk_rt_000b4390();
            ((void (*)(uint64_t, uint64_t, uint64_t))extraout_x9_00)(auVar9.lo, auVar9.hi, uVar7);
            goto lab_00400608;
        }
        sk_rt_00408314();
        auVar9 = ((sk_u128_t (*)(void))extraout_x8)();
        iVar1 = *(int32_t *)(lVar3 + 0x4c);
        lVar3 = *(int64_t *)(lVar3 + 0x38);
    } else {
        if ((uint32_t)auVar9.lo == 0) {
            auVar9 = sk_rt_000b4390();
            ((void (*)(uint64_t, uint64_t, uint64_t))extraout_x9)(auVar9.lo, auVar9.hi, uVar7);
            sk_rt_0034ee88(uVar6);
            sk_rt_000839d8();
            goto lab_00400608;
        }
        iVar1 = *(int32_t *)(extraout_x16_00 + 0x54);
        lVar3 = *(int64_t *)(extraout_x16_00 + 0x40);
    }
    if (iVar1 == 0) {
        lVar3 = lVar3 + 1;
    }
    sk_rt_000b4390(auVar9.lo, auVar9.hi, lVar3);
    sk_rt_00117cc4();

lab_00400608:
    uVar2 = sk_rt_00407a80();
    sk_rt_00084234(uVar2, unaff_x30);
}

/* FUN_00400620 @ 0x00400620   (est. sk_r61_00400620)
 * Ghidra: void FUN_00400620(void)
 * Thin wrapper: disables preemption and defers to sk_r61_00400638 (sibling helper, defined
 * in another part file).
 * Confidence: medium
 * Notes: callees FUN_00406e78 (preemption off) and sibling sk_r61_00400638. */
void sk_r61_00400620(void)
{
    sk_rt_00406e78();
    sk_r61_00400638();
}
/* FUN_00400638 @ 0x00400638   (est. sk_r61_00400638)
 * Ghidra: void FUN_00400638(void)
 * Object-reclaim/rotation routine: drains a slot, dispatches through a vtable
 * method pointer at this+0x20, then copies one byte from a reclaimed slot to
 * a fresh slot after (re)allocating storage via the runtime. Uses several
 * caller-inherited register values (vtable this pointer, slot pointers).
 * Confidence: low
 * Notes: register artifacts extraout_x8/x16/x16_00, unaff_x25; vtable off 0x20;
 * callees FUN_00084220 FUN_00406e34 FUN_0034fc7c FUN_00377824 FUN_00349530
 * FUN_0040749c FUN_004072e8 FUN_004077dc FUN_003518dc FUN_000839f8 FUN_0006b6f4
 * FUN_0034ee88 FUN_000839d8 FUN_00117cc4 FUN_00084234. */
void sk_r61_00400638(void)
{
    uint64_t extraout_x8 = 0;     /* register artifact: code* (unrecoverable) */
    uint64_t extraout_x16 = 0;    /* register artifact: this-like ptr (unrecoverable) */
    uint64_t extraout_x16_00 = 0; /* register artifact (unrecoverable) */
    uint64_t *unaff_x25 = 0;      /* register artifact: slot ptr (unrecoverable) */
    uint64_t uVar2, uVar4, uVar7;
    int32_t iVar6;
    int64_t lVar5;
    sk_u128_t auVar8;

    sk_rt_00084220();
    sk_rt_00406e34();
    sk_rt_0034fc7c();
    sk_rt_00377824(0);
    sk_rt_00349530();
    uint64_t *puVar3 = (uint64_t *)(extraout_x16 + 0x20);
    ((void (*)(void))(**(uint64_t **)puVar3))();
    sk_rt_0040749c(*(uint64_t *)(extraout_x16 + 0x40));
    uVar7 = *unaff_x25;
    *(uint64_t *)(extraout_x16 + 0x28) = unaff_x25[1];
    *puVar3 = uVar7;
    sk_rt_004072e8();
    sk_rt_004077dc();
    uVar2 = (uint64_t)*(uint8_t *)(extraout_x16_00 + 0x50);
    uVar4 = uVar2 + 0x10 + (uint64_t)puVar3 & (uVar2 ^ 0xffffffffffffffff);
    uVar2 = uVar2 + 0x10 + (uint64_t)unaff_x25 & (uVar2 ^ 0xffffffffffffffff);
    sk_rt_003518dc(uVar2);
    auVar8 = sk_rt_000839f8();
    if ((uint32_t)auVar8.lo == 0) {
        sk_rt_0006b6f4(*(uint64_t *)(extraout_x16_00 + 0x20));
        ((void (*)(void))extraout_x8)();
        sk_rt_0034ee88(uVar4);
        sk_rt_000839d8();
        iVar6 = *(int32_t *)(extraout_x16_00 + 0x54);
        lVar5 = *(int64_t *)(extraout_x16_00 + 0x40);
    } else {
        iVar6 = *(int32_t *)(extraout_x16_00 + 0x54);
        lVar5 = *(int64_t *)(extraout_x16_00 + 0x40);
        int64_t lVar1 = lVar5;
        if (iVar6 == 0) {
            lVar1 = lVar5 + 1;
        }
        sk_rt_0006b6f4(auVar8.lo, auVar8.hi, lVar1);
        sk_rt_00117cc4();
    }
    if (iVar6 == 0) {
        lVar5 = lVar5 + 1;
    }
    *(uint8_t *)(lVar5 + uVar4) = *(uint8_t *)(lVar5 + uVar2);
    sk_rt_00084234();
}

/* FUN_00400740 @ 0x00400740   (est. sk_r61_00400740)
 * Ghidra: void FUN_00400740(void)
 * Thin wrapper: prepares the reclaim context (FUN_00406e78) then delegates to
 * the sibling reclaim body sk_r61_00400758.
 * Confidence: high
 * Notes: callees FUN_00406e78, sibling FUN_00400758. */
void sk_r61_00400740(void)
{
    sk_rt_00406e78();
    sk_r61_00400758();
}

/* FUN_00400758 @ 0x00400758   (est. sk_r61_00400758)
 * Ghidra: void FUN_00400758(void)
 * Slot-reclaim core: dispatches a vtable method at this+0x28, drains runtime
 * buffers, and either copies a reclaimed element via the runtime copy helper
 * or repopulates a fresh slot from the (re)allocated buffer. Several register
 * artifacts (vtable this pointer, slot pointers, a stack value) are inherited
 * from the caller.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x9/x9_00/x16/x16_00, unaff_x25,
 * unaff_x30; vtable off 0x28; callees FUN_00084220 FUN_00406e34 FUN_0034fc7c
 * FUN_00377824 FUN_00349530 FUN_0040749c FUN_0036b118 FUN_004072e8 FUN_004077dc
 * FUN_003518dc FUN_000839f8 FUN_000b4390 FUN_00408314 FUN_0034ee88 FUN_000839d8
 * FUN_00117cc4 FUN_00407a80 FUN_00084234. */
void sk_r61_00400758(void)
{
    uint64_t extraout_x8 = 0;     /* register artifact: code* (unrecoverable) */
    uint64_t extraout_x9 = 0;     /* register artifact: code* (unrecoverable) */
    uint64_t extraout_x9_00 = 0;  /* register artifact: code* (unrecoverable) */
    uint64_t extraout_x16 = 0;    /* register artifact: this-like ptr (unrecoverable) */
    uint64_t extraout_x16_00 = 0; /* register artifact (unrecoverable) */
    uint64_t *unaff_x25 = 0;      /* register artifact: slot ptr (unrecoverable) */
    uint64_t unaff_x30 = 0;       /* register artifact (unrecoverable) */
    uint64_t uVar2, uVar4, uVar6, uVar7;
    int32_t iVar1;
    int64_t lVar3;
    sk_u128_t auVar8;

    sk_rt_00084220();
    sk_rt_00406e34();
    sk_rt_0034fc7c();
    sk_rt_00377824(0);
    sk_rt_00349530();
    uint64_t *puVar5 = (uint64_t *)(extraout_x16 + 0x28);
    ((void (*)(void))(**(uint64_t **)puVar5))();
    sk_rt_0040749c(*(uint64_t *)(extraout_x16 + 0x40));
    uVar2 = *(uint64_t *)(extraout_x16 + 0x30);
    uVar7 = *unaff_x25;
    *(uint64_t *)(extraout_x16 + 0x30) = unaff_x25[1];
    *puVar5 = uVar7;
    sk_rt_0036b118(uVar2);
    sk_rt_004072e8();
    sk_rt_004077dc();
    uVar4 = (uint64_t)*(uint8_t *)(extraout_x16_00 + 0x50);
    uVar6 = uVar4 + 0x10 + (uint64_t)puVar5 & (uVar4 ^ 0xffffffffffffffff);
    sk_rt_003518dc(uVar6);
    lVar3 = sk_rt_000839f8().lo;
    sk_rt_003518dc(uVar4 + 0x10 + (uint64_t)unaff_x25 & (uVar4 ^ 0xffffffffffffffff));
    auVar8 = sk_rt_000839f8();
    if ((int32_t)lVar3 == 0) {
        if ((uint32_t)auVar8.lo == 0) {
            sk_rt_000b4390();
            ((void (*)(void))extraout_x9_00)();
            goto LAB_00400890;
        }
        sk_rt_00408314();
        auVar8 = ((sk_u128_t(*)(void))extraout_x8)();
        iVar1 = *(int32_t *)(lVar3 + 0x4c);
        lVar3 = *(int64_t *)(lVar3 + 0x38);
    } else {
        if ((uint32_t)auVar8.lo == 0) {
            sk_rt_000b4390();
            ((void (*)(void))extraout_x9)();
            sk_rt_0034ee88(uVar6);
            sk_rt_000839d8();
            goto LAB_00400890;
        }
        iVar1 = *(int32_t *)(extraout_x16_00 + 0x54);
        lVar3 = *(int64_t *)(extraout_x16_00 + 0x40);
    }
    if (iVar1 == 0) {
        lVar3 = lVar3 + 1;
    }
    sk_rt_000b4390(auVar8.lo, auVar8.hi, lVar3);
    sk_rt_00117cc4();
LAB_00400890:
    uVar2 = sk_rt_00407a80();
    sk_rt_00084234(uVar2, unaff_x30);
}

/* FUN_004008a8 @ 0x004008a8   (est. sk_r61_004008a8)
 * Ghidra: void FUN_004008a8(void)
 * Thin wrapper: prepares the reclaim context then delegates to the sibling
 * sk_r61_004008c0.
 * Confidence: high
 * Notes: callees FUN_00406e78, sibling FUN_004008c0. */
void sk_r61_004008a8(void)
{
    sk_rt_00406e78();
    /* decompile shows FUN_004008c0() with no explicit args; the callee's 5
     * params are passed via caller registers (unrecoverable) -> placeholders */
    sk_r61_004008c0(0, 0, 0, 0, 0);
}

/* FUN_004008c0 @ 0x004008c0   (est. sk_r61_004008c0)
 * Ghidra: void FUN_004008c0(undefined8 param_1,undefined8 param_2,long param_3,
 *         undefined8 param_4,undefined8 param_5)
 * Variable-length-slot reclaim iterator: computes a packed element size (1/2/3/4
 * bytes) from a delta, walks a caller-provided slot buffer, and copies the next
 * reclaimed element; falls back to the runtime copy/alloc helpers on overflow or
 * when the delta equals the bound. Size math and the byte-width switch use the
 * caller-inherited registers.
 * Confidence: low
 * Notes: register artifacts extraout_w1/w1_00/x8/x8_00/x9/w11/x16, unaff_x19,
 * unaff_x30; callees FUN_0008e518 FUN_0034fc7c FUN_00377824 FUN_0034cb60
 * FUN_0008e500 FUN_00355d60 FUN_000839f8. */
void sk_r61_004008c0(uint64_t param_1, uint64_t param_2, int64_t param_3,
                     uint64_t param_4, uint64_t param_5)
{
    uint32_t extraout_w1 = 0;     /* register artifact (unrecoverable) */
    uint32_t extraout_w1_00 = 0;  /* register artifact (unrecoverable) */
    uint64_t extraout_x8 = 0;     /* register artifact: long (unrecoverable) */
    uint64_t *extraout_x8_00 = 0; /* register artifact: ulong* (unrecoverable) */
    uint64_t extraout_x9 = 0;     /* register artifact: ulong (unrecoverable) */
    uint32_t extraout_w11 = 0;    /* register artifact (unrecoverable) */
    uint64_t extraout_x16 = 0;    /* register artifact (unrecoverable) */
    uint32_t *unaff_x19 = 0;      /* register artifact: uint* slot ptr (unrecoverable) */
    uint64_t unaff_x30 = 0;       /* register artifact (unrecoverable) */
    uint32_t uVar1, uVar2, uVar3, uVar8, uVar11;
    int32_t iVar4, iVar5;
    int64_t lVar6, lVar10;
    uint64_t uVar7, uVar9;

    sk_rt_0008e518();
    sk_rt_0034fc7c();
    lVar6 = sk_rt_00377824(0).lo;
    lVar6 = *(int64_t *)(lVar6 + -8);
    uVar2 = *(uint32_t *)(lVar6 + 0x54);
    sk_rt_00377824(0, *(uint64_t *)((uint64_t)param_3 + 0x28),
                   *(uint64_t *)((uint64_t)param_3 + 0x18), param_4, param_5);
    uVar7 = sk_rt_0034cb60();
    iVar5 = *(int32_t *)(extraout_x16 + 0x54);
    uVar3 = 0;
    if (iVar5 != 0) {
        uVar3 = iVar5 - 1;
    }
    uVar1 = uVar2;
    if (uVar2 <= uVar3) {
        uVar1 = uVar3;
    }
    if (uVar1 < 0x1001) {
        uVar1 = 0x1000;
    }
    lVar10 = *(int64_t *)(lVar6 + 0x40);
    lVar6 = 1;
    if (iVar5 == 0) {
        lVar6 = 2;
    }
    if (extraout_w1 != 0) {
        if (uVar1 <= extraout_w1 && extraout_w1 - uVar1 != 0) {
            uVar9 = (uint64_t)lVar6 + *(int64_t *)(extraout_x8 + 0x40) +
                    ((uint64_t)*(uint8_t *)(extraout_x16 + 0x50) +
                     (uint64_t)(lVar10 + 7U & 0xfffffffffffffff8) + 0x10 &
                    ((uint64_t)*(uint8_t *)(extraout_x16 + 0x50) ^ 0xffffffffffffffff));
            uVar8 = (uint32_t)uVar9;
            uVar3 = uVar8 << 3;
            if (uVar8 < 4) {
                uVar11 = ((extraout_w1 - uVar1) +
                          ~(uint32_t)(-1 << (uVar3 & 0x1f)) >> (uVar3 & 0x1f)) + 1;
                if (uVar11 < 0x100) {
                    if (uVar11 < 2) goto LAB_00400a48;
                    goto LAB_004009cc;
                }
                if (uVar11 >> 0x10 == 0) {
                    uVar11 = (uint32_t)*(uint16_t *)((uint64_t)unaff_x19 + uVar9);
                } else {
                    uVar11 = *(uint32_t *)((uint64_t)unaff_x19 + uVar9);
                }
            } else {
LAB_004009cc:
                uVar11 = (uint32_t)*(uint8_t *)((uint64_t)unaff_x19 + uVar9);
            }
            if (uVar11 != 0) {
                uVar2 = 0;
                if (uVar8 < 4) {
                    uVar2 = uVar11 - 1 << (uVar3 & 0x1f);
                }
                if (uVar8 != 0) {
                    uVar3 = 4;
                    if (uVar8 < 4) {
                        uVar3 = uVar8;
                    }
                    switch (uVar3) {
                    default:
                        uVar9 = (uint64_t)*(uint8_t *)unaff_x19;
                        break;
                    case 2:
                        uVar9 = (uint64_t)*(uint16_t *)unaff_x19;
                        break;
                    case 3:
                        uVar9 = (uint64_t)((uint32_t)*(uint8_t *)unaff_x19 |
                                 ((uint32_t)*(uint16_t *)((char *)unaff_x19 + 1) << 8));
                        break;
                    case 4:
                        uVar9 = (uint64_t)*unaff_x19;
                    }
                }
                iVar5 = uVar1 + ((uint32_t)uVar9 | uVar2) + 1;
                goto LAB_00400b04;
            }
        }
LAB_00400a48:
        if (uVar2 == uVar1) {
            sk_rt_0008e500();
            sk_rt_000839f8();
            return;
        }
        sk_rt_00355d60((uint64_t)unaff_x19 + lVar10, uVar7, iVar5, uVar7);
        if (extraout_w11 < 0x1001) {
            iVar5 = 0;
            if (*extraout_x8_00 < 0x1000) {
                iVar5 = (int32_t)*extraout_x8_00 + 1;
            }
            goto LAB_00400b04;
        }
        if (1 < extraout_w1_00) {
            iVar4 = (int32_t)sk_rt_000839f8(
                        ((uint64_t)extraout_x8_00 + extraout_x9 + 0x10) & ~extraout_x9).lo;
            iVar5 = 0;
            if (iVar4 != 0) {
                iVar5 = iVar4 + -1;
            }
            goto LAB_00400b04;
        }
    }
    iVar5 = 0;
LAB_00400b04:
    sk_rt_0008e500(iVar5, unaff_x30);
}

/* FUN_00400b3c @ 0x00400b3c   (est. sk_r61_00400b3c)
 * Ghidra: void FUN_00400b3c(undefined8 param_1,undefined8 param_2,uint param_3,
 *         long param_4,undefined8 param_5,undefined8 param_6)
 * Packed-slot reclaim writer: computes a variable element width (1/2/4 bytes,
 * with a 3-byte invalid case that traps), stores a run-length delta into a
 * caller slot buffer at the computed offset, then either records the delta in
 * the runtime reclaim bookkeeping or (for large sizes) emits a 128-bit pair to
 * the runtime. Size/length arithmetic and the slot pointer come from caller
 * registers.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x16, unaff_x19, unaff_w20, unaff_x30;
 * SoftwareBreakpoint(1,0x400e1c) traps in width case 3; callees FUN_0008e518
 * FUN_00350c5c FUN_00377824 FUN_0034cb60 FUN_003507e0 FUN_00114330
 * FUN_0009461c FUN_0008e500 FUN_000839d8. */
void sk_r61_00400b3c(uint64_t param_1, uint64_t param_2, uint32_t param_3,
                     int64_t param_4, uint64_t param_5, uint64_t param_6)
{
    uint64_t extraout_x8 = 0;    /* register artifact: long (unrecoverable) */
    uint64_t extraout_x16 = 0;   /* register artifact (unrecoverable) */
    uint32_t *unaff_x19 = 0;     /* register artifact: uint* slot ptr (unrecoverable) */
    uint32_t unaff_w20 = 0;      /* register artifact: uint (unrecoverable) */
    uint64_t unaff_x30 = 0;      /* register artifact (unrecoverable) */
    uint32_t uVar1, uVar2, uVar3, uVar4, uVar5, uVar9, uVar16;
    uint16_t uVar6;
    uint8_t uVar17;
    int32_t iVar12;
    uint64_t uVar10, uVar11, lVar8, lVar15, uVar13;
    sk_u128_t auVar18;

    sk_rt_0008e518();
    lVar8 = (uint64_t)param_4;
    uVar10 = param_5;
    uVar11 = param_6;
    sk_rt_00350c5c();
    lVar8 = sk_rt_00377824(0, *(uint64_t *)(lVar8 + 0x20),
                           *(uint64_t *)(lVar8 + 0x10), uVar10, uVar11).lo;
    lVar8 = *(int64_t *)(lVar8 + -8);
    uVar4 = *(uint32_t *)(lVar8 + 0x54);
    sk_rt_00377824(0, *(uint64_t *)((uint64_t)param_4 + 0x28),
                   *(uint64_t *)((uint64_t)param_4 + 0x18), param_5, param_6);
    uVar17 = 0;
    sk_rt_0034cb60();
    uVar9 = *(uint32_t *)(extraout_x16 + 0x54);
    uVar3 = 0;
    if (uVar9 != 0) {
        uVar3 = uVar9 - 1;
    }
    uVar2 = uVar4;
    if (uVar4 <= uVar3) {
        uVar2 = uVar3;
    }
    uVar3 = uVar2;
    if (uVar2 < 0x1001) {
        uVar3 = 0x1000;
    }
    lVar15 = *(int64_t *)(lVar8 + 0x40);
    uVar13 = (uint64_t)*(uint8_t *)(extraout_x16 + 0x50);
    lVar8 = *(int64_t *)(extraout_x8 + 0x40);
    if (uVar9 == 0) {
        lVar8 = lVar8 + 1;
    }
    lVar8 = lVar8 + (uVar13 + (uint64_t)(lVar15 + 7U & 0xfffffffffffffff8) + 0x10 &
                    (uVar13 ^ 0xffffffffffffffff)) + 1;
    uVar16 = (uint32_t)lVar8;
    uVar5 = uVar16 << 3;
    if (uVar3 <= param_3 && param_3 - uVar3 != 0) {
        if (uVar16 < 4) {
            uVar1 = ((param_3 - uVar3) +
                     ~(uint32_t)(-1 << (uVar5 & 0x1f)) >> (uVar5 & 0x1f)) + 1;
            uVar17 = 2;
            if (0xffff < uVar1) {
                uVar17 = 4;
            }
            if (uVar1 < 0x100) {
                uVar17 = 1 < uVar1;
            }
        } else {
            uVar17 = 1;
        }
    }
    if (uVar3 < unaff_w20) {
        uVar3 = unaff_w20 + ~uVar3;
        if (uVar16 < 4) {
            iVar12 = (int32_t)((uVar3 >> (uVar5 & 0x1f)) + 1);
            if (uVar16 != 0) {
                uVar4 = uVar3 & ((uint32_t)(-1 << (uVar5 & 0x1f)) ^ 0xffffffffU);
                sk_rt_003507e0();
                sk_rt_00114330();
                uVar6 = (uint16_t)uVar4;
                if (uVar16 == 3) {
                    *(uint16_t *)unaff_x19 = uVar6;
                    *(char *)((uint64_t)unaff_x19 + 2) = (char)(uVar4 >> 0x10);
                } else if (uVar16 == 2) {
                    *(uint16_t *)unaff_x19 = uVar6;
                } else {
                    *(char *)unaff_x19 = (char)uVar3;
                }
            }
        } else {
            sk_rt_003507e0();
            sk_rt_00114330();
            *unaff_x19 = uVar3;
            iVar12 = 1;
        }
        switch (uVar17) {
        case 1:
            *(char *)((uint64_t)unaff_x19 + lVar8) = (char)iVar12;
            break;
        case 2:
            *(short *)((uint64_t)unaff_x19 + lVar8) = (short)iVar12;
            break;
        case 3:
            goto switchD_00400dd8_caseD_3;
        case 4:
            *(int *)((uint64_t)unaff_x19 + lVar8) = iVar12;
        }
        goto switchD_00400dd8_caseD_0;
    }
    switch (uVar17) {
    case 1:
        *(uint8_t *)((uint64_t)unaff_x19 + lVar8) = 0;
        if (unaff_w20 == 0) goto switchD_00400dd8_caseD_0;
        goto LAB_00400d34;
    case 2:
        *(uint16_t *)((uint64_t)unaff_x19 + lVar8) = 0;
        break;
    case 3:
switchD_00400dd8_caseD_3:
        __builtin_trap(); /* SoftwareBreakpoint(1,0x400e1c) */
    case 4:
        *(uint32_t *)((uint64_t)unaff_x19 + lVar8) = 0;
    default:
    }
    if (unaff_w20 != 0) {
LAB_00400d34:
        if (uVar4 == uVar3) {
            auVar18 = sk_rt_0009461c();
            uVar9 = uVar4;
        } else {
            uint64_t *puVar14 =
                (uint64_t *)(((uint64_t)unaff_x19 + lVar15 + 7) & 0xfffffffffffffff8);
            if (uVar2 < 0x1001) {
                if (unaff_w20 < 0x1001) {
                    iVar12 = -1;
                } else {
                    iVar12 = -0x1001;
                    puVar14[1] = 0;
                }
                *puVar14 = (uint64_t)(unaff_w20 + (uint32_t)iVar12);
                goto switchD_00400dd8_caseD_0;
            }
            auVar18.hi = (uint64_t)(uint32_t)(unaff_w20 + 1); /* _8_4_=delta, _12_4_=0 */
            auVar18.lo = ((uint64_t)puVar14 + uVar13 + 0x10) & ~uVar13;
        }
        sk_rt_0008e500(auVar18.lo, auVar18.hi, uVar9);
        sk_rt_000839d8();
        return;
    }
switchD_00400dd8_caseD_0:
    sk_rt_0008e500(unaff_x30);
}

/* FUN_00400e44 @ 0x00400e44   (est. sk_r61_00400e44)
 * Ghidra: void FUN_00400e44(void)
 * Teardown helper: if the 128-bit runtime state has a high-half (count) below
 * 0x40, reports the slot address (state low half -8) + 0x40 and runs the
 * deallocate/finalize helpers.
 * Confidence: medium
 * Notes: callees FUN_004080f8 FUN_00357d44 FUN_0034d1c0 FUN_003728b8
 * FUN_00019858. */
void sk_r61_00400e44(void)
{
    sk_u128_t auVar1;

    auVar1 = sk_rt_004080f8();
    if (auVar1.hi < 0x40) {
        sk_rt_00357d44(*(int64_t *)(auVar1.lo + -8) + 0x40);
        sk_rt_0034d1c0();
        sk_rt_003728b8();
        sk_rt_00019858();
    }
}

/* FUN_00400eb0 @ 0x00400eb0   (est. sk_r61_00400eb0)
 * Ghidra: void FUN_00400eb0(void)
 * Teardown wrapper: prepares state, queries the runtime buffer (tag 0x13f), and
 * if the reported count is below 0x40 finalizes with the runtime helpers.
 * Confidence: medium
 * Notes: callees FUN_00407dc0 FUN_00406e78 FUN_00377824 FUN_00357d44
 * FUN_00407fd8 FUN_00351244 FUN_003728b8 FUN_00019858. */
void sk_r61_00400eb0(void)
{
    sk_u128_t auVar1;

    sk_rt_00407dc0();
    sk_rt_00406e78();
    auVar1 = sk_rt_00377824(0x13f);
    if (auVar1.hi < 0x40) {
        sk_rt_00357d44(*(int64_t *)(auVar1.lo + -8) + 0x40);
        sk_rt_00407fd8();
        auVar1 = sk_rt_00351244();
        sk_rt_003728b8(auVar1.lo, auVar1.hi, 3);
        sk_rt_00019858();
    }
}

/* FUN_00400f28 @ 0x00400f28   (est. sk_r61_00400f28)
 * Ghidra: void FUN_00400f28(void)
 * Conditional finalize: depending on the caller's zero flag and a recovered
 * count (< 0x19), either runs the teardown chain and copies a state byte, or
 * runs an alternate reclaim path. Control-flow branches on register artifacts.
 * Confidence: low
 * Notes: register artifacts in_ZR, extraout_x8/x9/x9_00/x10/x16; callees
 * FUN_0034fc7c FUN_004068a4 FUN_0034b57c FUN_0035510c FUN_0034c144 FUN_00406c08
 * FUN_00349cd0 FUN_003535e4 FUN_00349a9c FUN_0036b270. */
void sk_r61_00400f28(void)
{
    bool in_ZR = false;      /* register artifact: caller zero flag (unrecoverable) */
    uint64_t extraout_x8 = 0;   /* register artifact: long (unrecoverable) */
    uint64_t extraout_x9 = 0;   /* register artifact: code* (unrecoverable) */
    uint64_t extraout_x9_00 = 0;/* register artifact: long (unrecoverable) */
    uint64_t extraout_x10 = 0;  /* register artifact: ulong (unrecoverable) */
    uint64_t extraout_x16 = 0;  /* register artifact (unrecoverable) */

    sk_rt_0034fc7c();
    sk_rt_004068a4();
    sk_rt_0034b57c();
    sk_rt_0035510c(extraout_x16);
    sk_rt_0034c144();
    if (in_ZR && extraout_x10 < 0x19) {
        sk_rt_00406c08();
        ((void (*)(void))extraout_x9)();
        sk_rt_00349cd0();
        sk_rt_003535e4();
        *(uint8_t *)(extraout_x8 + 0x10) = *(uint8_t *)(extraout_x9_00 + 0x10);
    } else {
        sk_rt_00349a9c();
    }
    sk_rt_0036b270();
}

/* FUN_00400fd4 @ 0x00400fd4   (est. sk_r61_00400fd4)
 * Ghidra: void FUN_00400fd4(void)
 * Object re-claim: resolves the object header from the runtime state, passes the
 * descriptor through the shared allocator, dispatches a vtable method at
 * this+8 with the object pointer, then updates the reclaim bookkeeping.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x16 (this ptr); vtable off 8; callees
 * FUN_00407478 FUN_00377824 FUN_0034ab20 FUN_0034de54 FUN_0036b118. */
void sk_r61_00400fd4(void)
{
    uint64_t extraout_x8 = 0;  /* register artifact: long (unrecoverable) */
    uint64_t extraout_x16 = 0; /* register artifact: this ptr (unrecoverable) */
    sk_u128_t auVar2;
    uint64_t uVar1;

    auVar2 = sk_rt_00407478();
    uVar1 = sk_rt_00377824(0, *(uint64_t *)(auVar2.hi + 0x20),
                           *(uint64_t *)(auVar2.hi + 0x10)).lo;
    sk_rt_0034ab20(uVar1, uVar1);
    ((void (*)(uint64_t))(**(uint64_t **)(extraout_x16 + 8)))(auVar2.lo);
    sk_rt_0034de54(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0036b118(*(uint64_t *)(extraout_x8 + 8));
}

/* FUN_00401044 @ 0x00401044   (est. sk_r61_00401044)
 * Ghidra: void FUN_00401044(void)
 * Object dispatch: dispatches a vtable method at this+0x10, passes this+0x40 to
 * the shared cleanup, and copies a state byte from one recovered frame to
 * another. this pointer and frame pointers are register artifacts.
 * Confidence: low
 * Notes: register artifacts extraout_x8/x9/x16; vtable off 0x10; callees
 * FUN_004069d8 FUN_004068a4 FUN_00349530 FUN_00349104 FUN_0034f22c
 * FUN_0036b270. */
void sk_r61_00401044(void)
{
    uint64_t extraout_x8 = 0;  /* register artifact: long (unrecoverable) */
    uint64_t extraout_x9 = 0;  /* register artifact: long (unrecoverable) */
    uint64_t extraout_x16 = 0; /* register artifact: this ptr (unrecoverable) */

    sk_rt_004069d8();
    sk_rt_004068a4();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)(extraout_x16 + 0x10)))();
    sk_rt_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0034f22c();
    *(uint8_t *)(extraout_x9 + 0x10) = *(uint8_t *)(extraout_x8 + 0x10);
    sk_rt_0036b270();
}

/* FUN_004010b4 @ 0x004010b4   (est. sk_r61_004010b4)
 * Ghidra: void FUN_004010b4(void)
 * Object dispatch: dispatches a vtable method at this+0x18, passes this+0x40 to
 * the shared cleanup, then reports a recovered state byte. this pointer and the
 * state frame pointer are register artifacts.
 * Confidence: low
 * Notes: register artifacts extraout_x16, unaff_x22; vtable off 0x18; callees
 * FUN_004069d8 FUN_004068a4 FUN_00349530 FUN_00406de8 FUN_0040774c
 * FUN_0036b118 FUN_004082c8. */
void sk_r61_004010b4(void)
{
    uint64_t extraout_x16 = 0; /* register artifact: this ptr (unrecoverable) */
    uint64_t unaff_x22 = 0;    /* register artifact: long (unrecoverable) */

    sk_rt_004069d8();
    sk_rt_004068a4();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)(extraout_x16 + 0x18)))();
    sk_rt_00406de8(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0040774c();
    sk_rt_0036b118();
    sk_rt_004082c8(*(uint8_t *)(unaff_x22 + 0x10));
}

/* FUN_00401124 @ 0x00401124   (est. sk_r61_00401124)
 * Ghidra: void FUN_00401124(void)
 * Object dispatch: dispatches a vtable method at this+0x20 and passes this+0x40
 * to the shared cleanup. this pointer is a register artifact.
 * Confidence: low
 * Notes: register artifact extraout_x16; vtable off 0x20; callees FUN_004069d8
 * FUN_004068a4 FUN_00349530 FUN_00349104 FUN_00407200. */
void sk_r61_00401124(void)
{
    uint64_t extraout_x16 = 0; /* register artifact: this ptr (unrecoverable) */

    sk_rt_004069d8();
    sk_rt_004068a4();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)(extraout_x16 + 0x20)))();
    sk_rt_00349104(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_00407200();
}

/* FUN_00401188 @ 0x00401188   (est. sk_r61_00401188)
 * Ghidra: void FUN_00401188(void)
 * Object dispatch: dispatches a vtable method at this+0x28, passes this+0x40 to
 * the shared cleanup, then reports a recovered state byte. this pointer and the
 * state frame pointer are register artifacts.
 * Confidence: low
 * Notes: register artifacts extraout_x16, unaff_x19; vtable off 0x28; callees
 * FUN_004069d8 FUN_004068a4 FUN_00349530 FUN_00406de8 FUN_00407ae8
 * FUN_004082c8. */
void sk_r61_00401188(void)
{
    uint64_t extraout_x16 = 0; /* register artifact: this ptr (unrecoverable) */
    uint64_t unaff_x19 = 0;    /* register artifact: long (unrecoverable) */

    sk_rt_004069d8();
    sk_rt_004068a4();
    sk_rt_00349530();
    ((void (*)(void))(**(uint64_t **)(extraout_x16 + 0x28)))();
    sk_rt_00406de8(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_00407ae8();
    sk_rt_004082c8(*(uint8_t *)(unaff_x19 + 0x10));
}

/* FUN_004011f0 @ 0x004011f0   (est. sk_r61_004011f0)
 * Ghidra: ulong FUN_004011f0(undefined8 param_1,uint param_2)
 * Slot-probe: reads a runtime state pair, and if a caller-supplied width
 * param_2 is nonzero and a recovered count is below it, tests the packed
 * element at the computed offset (1/2/4-byte; 3-byte traps) returning a
 * non-zero scan marker; otherwise returns a size-derived result from the
 * runtime. Element width, offset and the scan buffer are register artifacts.
 * Confidence: low
 * Notes: register artifacts extraout_x1/w8/w8_00/x8/w9/x10/w11/w12/x16,
 * unaff_x19; SoftwareBreakpoint(1,0x4012fc) traps in width case 3; callees
 * FUN_0034fc7c FUN_004068a4 FUN_0034ada0 FUN_00355008 FUN_00356638
 * FUN_00407f30 FUN_00356e74 FUN_004077ec FUN_00356e64 FUN_0040692c
 * FUN_000839f8. */
uint64_t sk_r61_004011f0(uint64_t param_1, uint32_t param_2)
{
    uint64_t extraout_x1 = 0;    /* register artifact (unrecoverable) */
    uint32_t extraout_w8 = 0;    /* register artifact: undefined4 (unrecoverable) */
    int32_t extraout_w8_00 = 0;  /* register artifact: int (unrecoverable) */
    uint64_t extraout_x8 = 0;    /* register artifact: long (unrecoverable) */
    uint32_t extraout_w9 = 0;    /* register artifact: uint (unrecoverable) */
    uint64_t extraout_x10 = 0;   /* register artifact: long (unrecoverable) */
    uint32_t extraout_w11 = 0;   /* register artifact: uint (unrecoverable) */
    uint32_t extraout_w12 = 0;   /* register artifact: uint (unrecoverable) */
    uint64_t extraout_x16 = 0;   /* register artifact (unrecoverable) */
    uint64_t unaff_x19 = 0;      /* register artifact: long scan buffer (unrecoverable) */
    uint32_t uVar1, uVar2, uVar3;
    uint64_t uVar7, uVar8;
    bool bVar5, bVar6;
    sk_u128_t auVar9;

    sk_rt_0034fc7c();
    sk_rt_004068a4();
    uVar7 = sk_rt_0034ada0();
    auVar9 = sk_rt_00355008(uVar7, *(uint32_t *)(extraout_x16 + 0x54));
    uVar7 = auVar9.hi;
    if (param_2 == 0) {
        return 0;
    }
    if (extraout_w9 < param_2) {
        sk_rt_00356638(*(uint64_t *)(extraout_x8 + 0x40), auVar9.lo, uVar7, auVar9.lo);
        sk_rt_00407f30();
        sk_rt_00356e74();
        uVar2 = extraout_w12;
        if (extraout_w11 < 0x100) {
            uVar2 = 1;
        }
        uVar1 = 0;
        if (1 < extraout_w11) {
            uVar1 = uVar2;
        }
        bVar5 = 3 < uVar1;
        bVar6 = uVar1 == 4;
        uVar7 = extraout_x1;
        switch (uVar1) {
        case 1:
            if (*(char *)(unaff_x19 + extraout_x10) != '\0') {
LAB_004012a0:
                sk_rt_004077ec();
                uVar3 = extraout_w8;
                if (bVar5 && !bVar6) {
                    uVar3 = 0;
                }
                uVar8 = sk_rt_00356e64(uVar3);
                return uVar8;
            }
            break;
        case 2:
            if (*(short *)(unaff_x19 + extraout_x10) != 0) goto LAB_004012a0;
            break;
        case 3:
            __builtin_trap(); /* SoftwareBreakpoint(1,0x4012fc) */
        case 4:
            if (*(int *)(unaff_x19 + extraout_x10) != 0) goto LAB_004012a0;
        }
    }
    bVar5 = 0xfff < (uint32_t)uVar7;
    bVar6 = (uint32_t)uVar7 == 0x1000;
    if (!bVar5) {
        sk_rt_0040692c();
        uVar2 = 0;
        if (!bVar5 || bVar6) {
            uVar2 = (uint32_t)extraout_w8_00 + 1;
        }
        return (uint64_t)uVar2;
    }
    uVar8 = sk_rt_000839f8().lo;
    return uVar8;
}
/* FUN_00401314 @ 0x00401314   (est. sk_r61_00401314)
 * Ghidra: void FUN_00401314(undefined8 param_1,undefined8 param_2,uint param_3,long param_4)
 * Formats a small unsigned value (unaff_w20) into a caller-provided destination buffer
 * (unaff_x19) according to a width/size selector (uVar10), honouring an alignment/
 * length bound derived from runtime state (param_4+0x10/0x20). Calls several shared
 * cL4 helpers around the store; falls into a SoftwareBreakpoint(1,0x4014ac) for the
 * 3-byte-width case.
 * Confidence: low
 * Notes: heavy register artifacts (extraout_* / unaff_*); callees FUN_00350c5c,
 * FUN_004068a4, FUN_0034ada0, FUN_00357db4, FUN_00356638, FUN_004082b4, FUN_00357e04,
 * FUN_00407bcc, FUN_003507e0, thunk_FUN_00114330, FUN_0009461c, FUN_000839d8,
 * FUN_0034de54, FUN_00407434. */
void sk_r61_00401314(uint64_t p1, uint64_t p2, uint32_t p3, int64_t p4)
{
    uint64_t uVar4;
    uint32_t uVar2;
    uint32_t uVar5;
    int32_t iVar6;
    int64_t lVar1;
    uint32_t uVar8;
    uint64_t uVar9;
    uint32_t uVar10;
    uint64_t *puVar7;
    /* register artifacts: value inherited from caller's register (unrecoverable) */
    uint64_t extraout_x16 = 0;
    uint64_t extraout_x8 = 0;
    int64_t extraout_x10 = 0;
    uint32_t extraout_w9 = 0;
    uint32_t extraout_w10 = 0;
    uint32_t extraout_w11 = 0;
    uint32_t extraout_w9_00 = 0;
    uint64_t *extraout_x8_00 = 0;
    uint64_t *extraout_x8_01 = 0;
    uint64_t extraout_x9 = 0;
    uint32_t *unaff_x19 = 0;
    uint32_t unaff_w20 = 0;

    uVar4 = sk_rt_00350c5c();
    sk_rt_004068a4(uVar4, *(uint64_t *)(p4 + 0x20), *(uint64_t *)(p4 + 0x10));
    sk_rt_0034ada0();
    uVar5 = *(uint32_t *)(extraout_x16 + 0x54);
    sk_rt_00357db4();
    sk_rt_00356638(*(uint64_t *)(extraout_x8 + 0x40));
    lVar1 = extraout_x10 + 0x11;
    if (extraout_w9 < p3) {
        sk_rt_004082b4();
        sk_rt_00357e04();
        uVar2 = extraout_w11;
        if (extraout_w10 < 0x100) {
            uVar2 = 1;
        }
        uVar10 = 0;
        uVar8 = extraout_w9_00;
        if (1 < extraout_w10) {
            uVar10 = uVar2;
        }
    } else {
        uVar10 = 0;
        uVar8 = extraout_w9;
    }
    if (uVar8 < unaff_w20) {
        sk_rt_00407bcc();
        sk_rt_003507e0();
        sk_rt_00114330();
        iVar6 = 1;
        if ((uint32_t)lVar1 < 4) {
            iVar6 = (unaff_w20 >> 8) + 1;
            *(char *)unaff_x19 = (char)unaff_w20;
        } else {
            *unaff_x19 = unaff_w20;
        }
        switch (uVar10) {
        default:
            return;
        case 1:
            *(char *)((long)unaff_x19 + lVar1) = (char)iVar6;
            return;
        case 2:
            *(short *)((long)unaff_x19 + lVar1) = (short)iVar6;
            return;
        case 3:
            goto case3_trap;
        case 4:
            *(int *)((long)unaff_x19 + lVar1) = iVar6;
            return;
        }
    }
    switch (uVar10) {
    case 1:
        *(uint8_t *)((long)unaff_x19 + lVar1) = 0;
        if (unaff_w20 == 0) {
            return;
        }
        goto do_fill;
    case 2:
        *(uint16_t *)((long)unaff_x19 + lVar1) = 0;
        break;
    case 3:
    case3_trap:
        /* SoftwareBreakpoint(1,0x4014ac) */
        __builtin_trap();
    case 4:
        *(uint32_t *)((long)unaff_x19 + lVar1) = 0;
    default:
        break;
    }
    if (unaff_w20 != 0) {
    do_fill:
        if (0xfff < uVar5) {
            sk_rt_0009461c();
            sk_rt_000839d8();
            return;
        }
        sk_rt_0034de54();
        if (unaff_w20 < 0x1001) {
            uVar9 = (uint64_t)(unaff_w20 - 1);
            puVar7 = extraout_x8_00;
        } else {
            sk_rt_00407434();
            puVar7 = extraout_x8_01;
            uVar9 = extraout_x9;
        }
        *puVar7 = uVar9;
    }
    return;
}

/* FUN_004014d4 @ 0x004014d4   (est. sk_r61_004014d4)
 * Ghidra: void FUN_004014d4(void)
 * Acquires/runs a shared cL4 helper (FUN_004080f8) and, when the resulting
 * unrecoverable length (extraout_x1) is below 0x40, performs a small tear-down
 * sequence (FUN_0034d1c0, FUN_003728b8, FUN_00019858).
 * Confidence: low
 * Notes: register artifact extraout_x1; callees FUN_004080f8, FUN_0034d1c0,
 * FUN_003728b8, FUN_00019858. */
void sk_r61_004014d4(void)
{
    uint64_t extraout_x1 = 0; /* register artifact: value inherited from caller's register */
    sk_rt_004080f8();
    if (extraout_x1 < 0x40) {
        sk_rt_0034d1c0();
        sk_rt_003728b8();
        sk_rt_00019858();
    }
    return;
}

/* FUN_0040153c @ 0x0040153c   (est. sk_r61_0040153c)
 * Ghidra: void FUN_0040153c(void)
 * Runs a shared initializer (FUN_00349d3c, FUN_0035510c, FUN_0034c144); depending on
 * the unrecoverable zero condition flag (in_ZR) and a size (extraout_x10 < 0x19) it
 * either continues a setup path (FUN_0009461c, indirect call, FUN_00349cd0,
 * FUN_003535e4) or takes the alternate path (FUN_00349a9c), then finalizes with
 * FUN_0036b270.
 * Confidence: low
 * Notes: register artifacts in_ZR (condition flag), extraout_x9 (fn pointer),
 * extraout_x10, extraout_x16; callees FUN_00349d3c, FUN_0035510c, FUN_0034c144,
 * FUN_0009461c, FUN_00349cd0, FUN_003535e4, FUN_00349a9c, FUN_0036b270. */
void sk_r61_0040153c(void)
{
    bool in_ZR = false;        /* register artifact: Z condition flag from prior compare */
    uint64_t extraout_x9 = 0;  /* register artifact: function pointer */
    uint64_t extraout_x10 = 0; /* register artifact */
    uint64_t extraout_x16 = 0; /* register artifact */
    sk_rt_00349d3c();
    sk_rt_0035510c(extraout_x16);
    sk_rt_0034c144();
    if (in_ZR && extraout_x10 < 0x19) {
        sk_rt_0009461c();
        ((void (*)(void))extraout_x9)();
        sk_rt_00349cd0();
        sk_rt_003535e4();
    } else {
        sk_rt_00349a9c();
    }
    sk_rt_0036b270();
    return;
}

/* FUN_004015c8 @ 0x004015c8   (est. sk_r61_004015c8)
 * Ghidra: void FUN_004015c8(undefined8 param_1,long param_2)
 * Invokes a shared helper (FUN_003509c8) with the object field at param_2+0x10, then
 * performs a vtable dispatch through thisptr+8, reads thisptr+0x40 for FUN_0034de54,
 * and passes extraout_x8+8 to FUN_0036b118.
 * Confidence: low
 * Notes: register artifacts extraout_x8, extraout_x16 (thisptr, vtable offset 8);
 * callees FUN_003509c8, FUN_0034de54, FUN_0036b118. */
void sk_r61_004015c8(uint64_t p1, int64_t p2)
{
    uint64_t extraout_x8 = 0;  /* register artifact */
    uint64_t extraout_x16 = 0; /* register artifact (this-like pointer) */
    sk_rt_003509c8(*(uint64_t *)(p2 + 0x10));
    ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x16 + 8)))();
    sk_rt_0034de54(*(uint64_t *)(extraout_x16 + 0x40));
    sk_rt_0036b118(*(uint64_t *)(extraout_x8 + 8));
    return;
}

/* FUN_00401940 @ 0x00401940   (est. sk_r61_00401940)
 * Ghidra: void FUN_00401940(long param_1)
 * Looks up a metadata/object pair via FUN_00377824(0x13f, field@param_1+0x18,
 * field@param_1+0x10); if the high half of the result is below 0x40 it dereferences a
 * back-pointer (result.lo - 8), adds 0x40, and drives a finalize sequence
 * (FUN_0034cdf8, FUN_003728b8(...,3), FUN_00019858).
 * Confidence: medium
 * Notes: sk_u128 result used via .lo/.hi; callees FUN_00377824, FUN_00357d44,
 * FUN_0034cdf8, FUN_003728b8, FUN_00019858. */
void sk_r61_00401940(int64_t p1)
{
    sk_u128_t result;
    result = sk_rt_00377824(0x13f, *(uint64_t *)(p1 + 0x18), *(uint64_t *)(p1 + 0x10));
    if (result.hi < 0x40) {
        sk_rt_00357d44(*(int64_t *)(result.lo - 8) + 0x40);
        result = sk_rt_0034cdf8();
        sk_rt_003728b8(result.lo, result.hi, 3);
        sk_rt_00019858();
    }
    return;
}

/* FUN_004019c0 @ 0x004019c0   (est. sk_r61_004019c0)
 * Ghidra: void FUN_004019c0(void)
 * Thin wrapper: runs shared helper FUN_00406e78, then the sibling FUN_004019d8.
 * Confidence: medium
 * Notes: callees FUN_00406e78, FUN_004019d8 (sibling). */
void sk_r61_004019c0(void)
{
    sk_rt_00406e78();
    sk_r61_004019d8();
    return;
}

/* FUN_004019d8 @ 0x004019d8   (est. sk_r61_004019d8)
 * Ghidra: long * FUN_004019d8(void)
 * Advances/returns a caller-supplied cursor (unaff_x19) into a frame backed by
 * FUN_0034d724 / FUN_00377824(0) / FUN_0034b57c. Reads a small index from thisptr+0x50
 * and a base length from extraout_x9+0x40; if the index<8 and the '0x100000' flag is
 * clear and the aligned total stays under 0x19, it stores one byte and runs an aligned
 * helper; otherwise it copies a full word and offsets the cursor by an alignment-
 * derived amount. Returns the (possibly advanced) cursor.
 * Confidence: low
 * Notes: register artifacts extraout_x9, extraout_x16 (thisptr), extraout_x9_00
 * (fn pointer), unaff_x19, unaff_x20; sk_u128 used for FUN_0034b57c result; callees
 * FUN_0034d724, FUN_00377824, FUN_0034b57c, FUN_0006b6f4, FUN_003535e4, FUN_0036b270. */
int64_t* sk_r61_004019d8(void)
{
    int64_t lVar1;
    uint64_t uVar2;
    sk_u128_t auVar3;
    /* register artifacts */
    uint64_t extraout_x9 = 0;
    uint64_t extraout_x16 = 0;
    uint64_t extraout_x9_00 = 0; /* function pointer */
    int64_t *unaff_x19 = 0;
    int64_t *unaff_x20 = 0;

    sk_rt_0034d724();
    sk_rt_00377824(0);
    auVar3 = sk_rt_0034b57c();
    uVar2 = (uint64_t)(*(uint32_t *)(extraout_x16 + 0x50) & 0xff);
    lVar1 = *(int64_t *)(extraout_x9 + 0x40) + 7;
    if ((((uint32_t)uVar2 < 8) && ((*(uint32_t *)(extraout_x16 + 0x50) & 0x100000) == 0)) &&
        ((((lVar1 + ((uVar2 + 1) & (uVar2 ^ 0xffffffffffffffffULL))) & 0xfffffffffffffff8ULL) + 0x10) < 0x19)) {
        *(char *)unaff_x19 = (char)*unaff_x20;
        sk_rt_0006b6f4(auVar3.lo, auVar3.hi, auVar3.lo);
        ((void (*)(void))extraout_x9_00)();
        sk_rt_003535e4((lVar1 + ((uint64_t)((int64_t)unaff_x19 + uVar2 + 1) & ~uVar2)) & 0xfffffffffffffff8ULL);
    } else {
        lVar1 = *unaff_x20;
        *unaff_x19 = lVar1;
        unaff_x19 = (int64_t *)(lVar1 + (((uint64_t)(((uint32_t)uVar2 & 0xf8) ^ 0x1f8)) & (uVar2 + 0x10)));
    }
    sk_rt_0036b270();
    return unaff_x19;
}

/* FUN_00401aec @ 0x00401aec   (est. sk_r61_00401aec)
 * Ghidra: void FUN_00401aec(void)
 * Runs shared setup (FUN_00407478, FUN_003561f4, FUN_00377824(0,...), FUN_0034ab20),
 * then computes a byte-aligned cursor from unaff_x19 and the byte at thisptr+0x50 and
 * passes it to the vtable method at thisptr+8, followed by FUN_00355d60(thisptr+0x40
 * value + cursor) and FUN_0036b118(extraout_x8_00+8).
 * Confidence: low
 * Notes: register artifacts extraout_x8, extraout_x8_00, extraout_x16 (thisptr,
 * vtable offset 8), unaff_x19; sk_u128 result of FUN_00377824 used as scalar .lo;
 * callees FUN_00407478, FUN_003561f4, FUN_00377824, FUN_0034ab20, FUN_00355d60,
 * FUN_0036b118. */
void sk_r61_00401aec(void)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t byteVal;
    /* register artifacts */
    uint64_t extraout_x8 = 0;
    uint64_t extraout_x8_00 = 0;
    uint64_t extraout_x16 = 0; /* this-like pointer */
    int64_t unaff_x19 = 0;

    sk_rt_00407478();
    sk_rt_003561f4();
    uVar1 = sk_rt_00377824(0, extraout_x8).lo;
    sk_rt_0034ab20(uVar1, uVar1);
    byteVal = (uint64_t)*(uint8_t *)(extraout_x16 + 0x50);
    uVar2 = ((uint64_t)unaff_x19 + byteVal + 1) & (byteVal ^ 0xffffffffffffffffULL);
    ((void (*)(uint64_t))(**(uint64_t **)((uint64_t)extraout_x16 + 8)))(uVar2);
    sk_rt_00355d60(*(int64_t *)(extraout_x16 + 0x40) + uVar2);
    sk_rt_0036b118(*(uint64_t *)(extraout_x8_00 + 8));
    return;
}

/* FUN_00401b64 @ 0x00401b64   (est. sk_r61_00401b64)
 * Ghidra: void FUN_00401b64(void)
 * Thin wrapper: runs shared helper FUN_00406e78, then the sibling FUN_00401b7c.
 * Confidence: medium
 * Notes: callees FUN_00406e78, FUN_00401b7c (sibling). */
void sk_r61_00401b64(void)
{
    sk_rt_00406e78();
    sk_r61_00401b7c();
    return;
}

/* FUN_00401b7c @ 0x00401b7c   (est. sk_r61_00401b7c)
 * Ghidra: void FUN_00401b7c(void)
 * Runs shared setup (FUN_003504d0, FUN_00407638, FUN_00349530), reads a byte index
 * from thisptr+0x50, and invokes the vtable method at thisptr+0x10 with two
 * byte-aligned cursor addresses built from unaff_x20 / unaff_x19; then updates a base
 * length (FUN_0034bb74(thisptr+0x40 value + 7)) and runs FUN_0034f22c / FUN_0036b270.
 * Confidence: low
 * Notes: register artifacts extraout_x16 (thisptr, vtable offset 0x10), unaff_x19,
 * unaff_x20; callees FUN_003504d0, FUN_00407638, FUN_00349530, FUN_0034bb74,
 * FUN_0034f22c, FUN_0036b270. */
void sk_r61_00401b7c(void)
{
    uint64_t uVar1;
    uint64_t extraout_x16 = 0; /* this-like pointer */
    int64_t unaff_x19 = 0;
    int64_t unaff_x20 = 0;

    sk_rt_003504d0();
    sk_rt_00407638();
    sk_rt_00349530();
    uVar1 = (uint64_t)*(uint8_t *)(extraout_x16 + 0x50);
    ((void (*)(uint64_t, uint64_t))(**(uint64_t **)((uint64_t)extraout_x16 + 0x10)))(
        ((uint64_t)unaff_x20 + uVar1 + 1) & (uVar1 ^ 0xffffffffffffffffULL),
        ((uint64_t)unaff_x19 + uVar1 + 1) & (uVar1 ^ 0xffffffffffffffffULL));
    sk_rt_0034bb74(*(int64_t *)(extraout_x16 + 0x40) + 7);
    sk_rt_0034f22c();
    sk_rt_0036b270();
    return;
}

/* FUN_00401c00 @ 0x00401c00   (est. sk_r61_00401c00)
 * Ghidra: void FUN_00401c00(void)
 * Thin wrapper: runs shared helper FUN_00406e78, then the sibling FUN_00401c18.
 * Confidence: medium
 * Notes: callees FUN_00406e78, FUN_00401c18 (sibling). */
void sk_r61_00401c00(void)
{
    sk_rt_00406e78();
    sk_r61_00401c18();
    return;
}

/* FUN_00401c18 @ 0x00401c18   (est. sk_r61_00401c18)
 * Ghidra: void FUN_00401c18(void)
 * Runs shared setup (FUN_003504d0, FUN_00407638, FUN_00349530), reads a byte index
 * from thisptr+0x50, and invokes the vtable method at thisptr+0x18 with two
 * byte-aligned cursor addresses built from unaff_x20 / unaff_x19; updates a base
 * length (FUN_0034bb74(thisptr+0x40 value + 7)), then reads extraout_x9+8 and runs
 * FUN_0034f22c / FUN_0036b270 / FUN_0036b118.
 * Confidence: low
 * Notes: register artifacts extraout_x9, extraout_x16 (thisptr, vtable offset 0x18),
 * unaff_x19, unaff_x20; callees FUN_003504d0, FUN_00407638, FUN_00349530,
 * FUN_0034bb74, FUN_0034f22c, FUN_0036b270, FUN_0036b118. */
void sk_r61_00401c18(void)
{
    uint64_t uVar1;
    uint64_t uVar2;
    uint64_t extraout_x9 = 0;
    uint64_t extraout_x16 = 0; /* this-like pointer */
    int64_t unaff_x19 = 0;
    int64_t unaff_x20 = 0;

    sk_rt_003504d0();
    sk_rt_00407638();
    sk_rt_00349530();
    uVar1 = (uint64_t)*(uint8_t *)(extraout_x16 + 0x50);
    ((void (*)(uint64_t, uint64_t))(**(uint64_t **)((uint64_t)extraout_x16 + 0x18)))(
        ((uint64_t)unaff_x20 + uVar1 + 1) & (uVar1 ^ 0xffffffffffffffffULL),
        ((uint64_t)unaff_x19 + uVar1 + 1) & (uVar1 ^ 0xffffffffffffffffULL));
    sk_rt_0034bb74(*(int64_t *)(extraout_x16 + 0x40) + 7);
    uVar2 = *(uint64_t *)(extraout_x9 + 8);
    sk_rt_0034f22c();
    sk_rt_0036b270();
    sk_rt_0036b118(uVar2);
    return;
}

/* FUN_00401ca8 @ 0x00401ca8   (est. sk_r61_00401ca8)
 * Ghidra: void FUN_00401ca8(void)
 * Thin wrapper: runs shared helper FUN_00406e78, then the sibling FUN_00401cc0.
 * Confidence: medium
 * Notes: callees FUN_00406e78, FUN_00401cc0 (sibling). */
void sk_r61_00401ca8(void)
{
    sk_rt_00406e78();
    sk_r61_00401cc0();
    return;
}

/* FUN_00401cc0 @ 0x00401cc0   (est. sk_r61_00401cc0)
 * Ghidra: void FUN_00401cc0(void)
 * Runs shared setup (FUN_003504d0, FUN_00407638, FUN_00349530), reads a byte index
 * from thisptr+0x50, and invokes the vtable method at thisptr+0x20 with two
 * byte-aligned cursor addresses built from unaff_x20 / unaff_x19; then updates a base
 * length (FUN_0034bb74(thisptr+0x40 value + 7)) and runs FUN_00352dac.
 * Confidence: low
 * Notes: register artifacts extraout_x16 (thisptr, vtable offset 0x20), unaff_x19,
 * unaff_x20; callees FUN_003504d0, FUN_00407638, FUN_00349530, FUN_0034bb74,
 * FUN_00352dac. */
void sk_r61_00401cc0(void)
{
    uint64_t uVar1;
    uint64_t extraout_x16 = 0; /* this-like pointer */
    int64_t unaff_x19 = 0;
    int64_t unaff_x20 = 0;

    sk_rt_003504d0();
    sk_rt_00407638();
    sk_rt_00349530();
    uVar1 = (uint64_t)*(uint8_t *)(extraout_x16 + 0x50);
    ((void (*)(uint64_t, uint64_t))(**(uint64_t **)((uint64_t)extraout_x16 + 0x20)))(
        ((uint64_t)unaff_x20 + uVar1 + 1) & (uVar1 ^ 0xffffffffffffffffULL),
        ((uint64_t)unaff_x19 + uVar1 + 1) & (uVar1 ^ 0xffffffffffffffffULL));
    sk_rt_0034bb74(*(int64_t *)(extraout_x16 + 0x40) + 7);
    sk_rt_00352dac();
    return;
}

/* FUN_00401d40 @ 0x00401d40   (est. sk_r61_00401d40)
 * Ghidra: void FUN_00401d40(void)
 * Thin wrapper: runs shared helper FUN_00406e78, then the sibling FUN_00401d58.
 * Confidence: medium
 * Notes: callees FUN_00406e78, FUN_00401d58 (sibling, defined in another part file). */
void sk_r61_00401d40(void)
{
    sk_rt_00406e78();
    sk_r61_00401d58();
    return;
}
/* FUN_00401d58 @ 0x00401d58   (est. sk_r61_00401d58)
 * Ghidra: void FUN_00401d58(void)
 * Dispatcher/forwarder: calls a fixed sequence of runtime helpers, then performs a
 * method-pointer (vtable) dispatch through a this-like pointer inherited in x16.
 * Reads a byte tag at this+0x50 and computes two derived pointers from it before
 * calling the slot at this+0x28 with two arguments; finally calls three more
 * runtime helpers (one passing this+0x40 data+7, one this-relative data).
 * Confidence: low
 * Notes: register artifacts extraout_x16 (thisptr), extraout_x9, unaff_x19, unaff_x20;
 * vtable slot offset 0x28; callees FUN_003504d0/FUN_00407638/FUN_00349530/
 * FUN_0034bb74/FUN_00352dac/FUN_0036b118. */
void sk_r61_00401d58(void)
{
    uint64_t extraout_x16 = 0; /* register artifact: this-like pointer inherited from caller's x16 */
    uint64_t extraout_x9 = 0;  /* register artifact: value inherited from caller's x9 */
    uint64_t unaff_x19 = 0;    /* register artifact: value inherited from caller's x19 */
    uint64_t unaff_x20 = 0;    /* register artifact: value inherited from caller's x20 */
    uint64_t uVar1;

    sk_rt_003504d0();
    sk_rt_00407638();
    sk_rt_00349530();
    uVar1 = (uint64_t)*(uint8_t *)(extraout_x16 + 0x50);
    ((void (*)(uint64_t, uint64_t))(**(uint64_t **)((uint64_t)extraout_x16 + 0x28)))(
        uVar1 + 1 + unaff_x20 & (uVar1 ^ 0xffffffffffffffff),
        uVar1 + 1 + unaff_x19 & (uVar1 ^ 0xffffffffffffffff));
    sk_rt_0034bb74(*(uint64_t *)(extraout_x16 + 0x40) + 7);
    sk_rt_00352dac(*(uint64_t *)(extraout_x9 + 8));
    sk_rt_0036b118();
    return;
}

/* FUN_00401de0 @ 0x00401de0   (est. sk_r61_00401de0)
 * Ghidra: void FUN_00401de0(void)
 * Tiny forwarder: calls runtime helper FUN_00406e78, then the sibling
 * sk_r61_00401df8 (serialization helper) in sequence.
 * Confidence: high
 * Notes: callees FUN_00406e78 (extern), FUN_00401df8 (sibling). */
void sk_r61_00401de0(void)
{
    sk_rt_00406e78();
    sk_r61_00401df8();
    return;
}

/* FUN_00401df8 @ 0x00401df8   (est. sk_r61_00401df8)
 * Ghidra: ulong FUN_00401df8(void)
 * Message serialization/size helper. Computes an encoded-length based on a size
 * field at this+0x54 (clamped to >= 0x1000) and a type byte at this+0x50, then
 * walks an object buffer (inherited in x19) using variable-width length prefixes
 * (1/2/4-byte) to decode the leading length tag. Small-buffer path reads a
 * word-aligned length and returns count+1 if under 0x1000; otherwise delegates
 * to the big-page helper.
 * Confidence: low
 * Notes: register artifacts extraout_x16, extraout_x8, unaff_x19 (buffer ptr),
 * unaff_w20 (size input); SoftwareBreakpoint(1,0x401f50) -> trap; callees
 * FUN_0034d724/FUN_00377824/FUN_00407cb4/FUN_00356e64/FUN_000839f8. */
uint64_t sk_r61_00401df8(void)
{
    uint64_t extraout_x16 = 0; /* register artifact: this-like pointer from caller's x16 */
    uint64_t extraout_x8 = 0;  /* register artifact: value inherited from caller's x8 */
    uint64_t unaff_x19 = 0;    /* register artifact: object/buffer pointer from caller's x19 */
    uint32_t unaff_w20 = 0;    /* register artifact: size from caller's w20 */
    int64_t lVar1;
    uint64_t uVar2, uVar7, uVar8;
    uint32_t uVar3, uVar4, uVar9, uVar10;
    int32_t iVar5;

    sk_rt_0034d724();
    sk_rt_00377824(0);
    uVar7 = sk_rt_00407cb4();
    uVar4 = *(uint32_t *)(extraout_x16 + 0x54);
    uVar9 = uVar4;
    if (uVar4 < 0x1001) {
        uVar9 = 0x1000;
    }
    uVar8 = (uint64_t)*(uint8_t *)(extraout_x16 + 0x50);
    if (unaff_w20 == 0) {
        return 0;
    }
    lVar1 = *(int64_t *)(extraout_x8 + 0x40) + 7;
    if (uVar9 <= unaff_w20 && unaff_w20 - uVar9 != 0) {
        uVar2 = (uint64_t)(lVar1 + (uVar8 + 1 & (uVar8 ^ 0xffffffffffffffff)) &
                           0xfffffffffffffff8) + 0x10;
        uVar10 = 2;
        uVar3 = uVar10;
        if ((uVar2 & 0xfffffff8) == 0) {
            uVar3 = (unaff_w20 - uVar9) + 1;
        }
        if (0xffff < uVar3) {
            uVar10 = 4;
        }
        if (uVar3 < 0x100) {
            uVar10 = 1;
        }
        uVar9 = 0;
        if (1 < uVar3) {
            uVar9 = uVar10;
        }
        switch (uVar9) {
        case 1:
            uVar9 = (uint32_t)*(uint8_t *)(unaff_x19 + uVar2);
            if (*(uint8_t *)(unaff_x19 + uVar2) != 0) {
            LAB_00401ed8:
                iVar5 = (int32_t)uVar9 - 1;
                if ((uVar2 & 0xfffffff8) != 0) {
                    iVar5 = 0;
                }
                uVar8 = sk_rt_00356e64(iVar5, uVar7, uVar4, uVar7);
                return uVar8;
            }
            break;
        case 2:
            uVar9 = (uint32_t)*(uint16_t *)(unaff_x19 + uVar2);
            if (*(uint16_t *)(unaff_x19 + uVar2) != 0) goto LAB_00401ed8;
            break;
        case 3:
            __builtin_trap(); /* SoftwareBreakpoint(1,0x401f50) */
        case 4:
            uVar9 = *(uint32_t *)(unaff_x19 + uVar2);
            if (uVar9 != 0) goto LAB_00401ed8;
        }
    }
    if (uVar4 < 0x1000) {
        uVar8 = *(uint64_t *)(lVar1 + (unaff_x19 + uVar8 + 1 & ~uVar8) & 0xfffffffffffffff8);
        uVar9 = 0;
        if (uVar8 < 0x1000) {
            uVar9 = (uint32_t)uVar8 + 1;
        }
        return (uint64_t)uVar9;
    }
    uVar8 = sk_rt_000839f8().lo;
    return uVar8;
}

/* FUN_00401f78 @ 0x00401f78   (est. sk_r61_00401f78)
 * Ghidra: void FUN_00401f78(int *param_1, undefined8 param_2, uint param_3,
 *                            long param_4, undefined8 param_5, undefined8 param_6)
 * Message serialization writer. After preparing the runtime (FUN_00377824 with
 * args derived from param_4+0x18/+0x10, FUN_00407cb4), computes an element size
 * from this+0x54 (clamped to >= 0x1000) and a base offset this+0x40. When the
 * provided length (param_3) exceeds the capacity it fails through FUN_00356e74,
 * deriving a width (1/2/4/8) from the decompiler's extraout registers; otherwise
 * it writes a length delta (param_2 - capacity) into param_1 and stores the
 * serialized value at param_1+lVar1 with the matching width. Trailing small-page
 * path stores the remainder length into the aligned word.
 * Confidence: low
 * Notes: register artifacts extraout_x16, extraout_x8, extraout_x8_00,
 * extraout_x9, extraout_w10, extraout_w11, extraout_w12; SoftwareBreakpoint(1,
 * 0x402150) -> trap; callees FUN_00377824/FUN_00407cb4/FUN_00356e74/
 * FUN_0006b6f4/thunk_FUN_00114330/FUN_000839d8. */
void sk_r61_00401f78(int32_t* param_1, uint64_t param_2, uint32_t param_3,
                     int64_t param_4, uint64_t param_5, uint64_t param_6)
{
    uint64_t extraout_x16 = 0; /* register artifact: this-like pointer from caller's x16 */
    uint64_t extraout_x8 = 0;  /* register artifact: value inherited from caller's x8 */
    uint64_t extraout_x8_00 = 0; /* register artifact: value inherited from caller's x8 */
    uint64_t extraout_x9 = 0;  /* register artifact: value inherited from caller's x9 */
    uint32_t extraout_w10 = 0; /* register artifact: value inherited from caller's w10 */
    uint32_t extraout_w11 = 0; /* register artifact: value inherited from caller's w11 */
    uint32_t extraout_w12 = 0; /* register artifact: value inherited from caller's w12 */
    int64_t lVar1, lVar6;
    uint32_t uVar2, uVar5, uVar9, uVar10, uVar11;
    int32_t iVar3;
    uint64_t uVar8;
    uint64_t *puVar7;

    sk_rt_00377824(0, *(uint64_t *)(param_4 + 0x18), *(uint64_t *)(param_4 + 0x10),
                   param_5, param_6);
    sk_rt_00407cb4();
    uVar5 = *(uint32_t *)(extraout_x16 + 0x54);
    uVar9 = uVar5;
    if (uVar5 < 0x1001) {
        uVar9 = 0x1000;
    }
    uVar8 = (uint64_t)*(uint8_t *)(extraout_x16 + 0x50);
    lVar6 = *(int64_t *)(extraout_x8 + 0x40) + 7;
    lVar1 = (int64_t)((uint64_t)(lVar6 + (uVar8 + 1 & (uVar8 ^ 0xffffffffffffffff)) &
                                 0xfffffffffffffff8) + 0x10);
    if (uVar9 < param_3) {
        sk_rt_00356e74();
        uVar2 = extraout_w12;
        if (extraout_w11 < 0x100) {
            uVar2 = 1;
        }
        lVar6 = extraout_x8_00;
        uVar8 = extraout_x9;
        uVar11 = 0;
        uVar9 = extraout_w10;
        if (1 < extraout_w11) {
            uVar11 = uVar2;
        }
    } else {
        uVar11 = 0;
    }
    uVar10 = (uint32_t)param_2;
    iVar3 = (int32_t)uVar10 - (int32_t)uVar9;
    if (uVar9 <= uVar10 && iVar3 != 0) {
        if ((int32_t)lVar1 != 0) {
            iVar3 = 1;
            sk_rt_0006b6f4();
            sk_rt_00114330();
            *param_1 = uVar10 + ~uVar9;
        }
        switch (uVar11) {
        default:
            return;
        case 1:
            *(int8_t *)((int64_t)param_1 + lVar1) = (int8_t)iVar3;
            return;
        case 2:
            *(int16_t *)((int64_t)param_1 + lVar1) = (int16_t)iVar3;
            return;
        case 3:
            goto switchD_0040207c_caseD_3;
        case 4:
            *(int32_t *)((int64_t)param_1 + lVar1) = iVar3;
            return;
        }
    }
    switch (uVar11) {
    case 1:
        *(uint8_t *)((int64_t)param_1 + lVar1) = 0;
        if (uVar10 == 0) {
            return;
        }
        goto LAB_004020d4;
    case 2:
        *(uint16_t *)((int64_t)param_1 + lVar1) = 0;
        break;
    case 3:
    switchD_0040207c_caseD_3:
        __builtin_trap(); /* SoftwareBreakpoint(1,0x402150) */
    case 4:
        *(uint32_t *)((int64_t)param_1 + lVar1) = 0;
    default:
        break;
    }
    if (uVar10 != 0) {
    LAB_004020d4:
        uVar8 = (uint64_t)((int64_t)param_1 + uVar8 + 1 & ~uVar8);
        if (0xfff < uVar5) {
            sk_rt_000839d8(uVar8, param_2);
            return;
        }
        puVar7 = (uint64_t *)(lVar6 + uVar8 & 0xfffffffffffffff8);
        if (uVar10 < 0x1001) {
            uVar10 = uVar10 - 1;
        } else {
            uVar10 = uVar10 - 0x1001;
            puVar7[1] = 0;
        }
        *puVar7 = (uint64_t)uVar10;
    }
    return;
}

/* FUN_00402324 @ 0x00402324   (est. sk_r61_00402324)
 * Ghidra: undefined1  [16] FUN_00402324(long param_1)
 * Object lookup returning a 128-bit descriptor. Calls FUN_00377dcc(0x13f, tag)
 * where the tag is read at param_1+0x38. When the returned upper word is below
 * 0x40, re-resolves via FUN_00351244 then FUN_00374104(lo,hi,1); a zero lower
 * word yields the zero 128-bit value. Otherwise clamps hi to 0x3f and keeps lo.
 * Confidence: medium
 * Notes: 16-byte return; ZEXT816(0) rendered as {0,0}; callees FUN_00377dcc/
 * FUN_00351244/FUN_00374104. */
sk_u128_t sk_r61_00402324(int64_t param_1)
{
    sk_u128_t auVar1, auVar2;

    auVar1 = sk_rt_00377dcc(0x13f, *(uint64_t *)(param_1 + 0x38));
    if (auVar1.hi < 0x40) {
        auVar1 = sk_rt_00351244();
        auVar2 = sk_rt_00374104(auVar1.lo, auVar1.hi, 1);
        if (auVar2.lo == 0) {
            auVar2.lo = 0; /* ZEXT816(0) */
            auVar2.hi = 0;
        }
    } else {
        auVar2.hi = 0x3f;
        auVar2.lo = auVar1.lo;
    }
    return auVar2;
}

/* FUN_00402594 @ 0x00402594   (est. sk_r61_00402594)
 * Ghidra: void FUN_00402594(long param_1)
 * Object release/cleanup helper. Looks up an object via FUN_00310d68(0x13f, tag
 * at param_1+0x18); when the returned upper word is below 0x40, forms a header
 * pointer at descriptor.lo-8 and calls FUN_00351244(header, hi, *header+0x40),
 * then FUN_0036851c and FUN_00019858.
 * Confidence: medium
 * Notes: callees FUN_00310d68/FUN_00351244/FUN_0036851c/FUN_00019858. */
void sk_r61_00402594(int64_t param_1)
{
    sk_u128_t auVar2;

    auVar2 = sk_rt_00310d68(0x13f, *(uint64_t *)(param_1 + 0x18));
    if (auVar2.hi < 0x40) {
        int64_t *plVar1 = (int64_t *)(auVar2.lo + (uint64_t)-8);
        sk_rt_00351244(plVar1, auVar2.hi, (uint64_t)*plVar1 + 0x40);
        sk_rt_0036851c();
        sk_rt_00019858();
    }
    return;
}

/* FUN_004025f4 @ 0x004025f4   (est. sk_r61_004025f4)
 * Ghidra: void FUN_004025f4(undefined8 param_1, undefined8 param_2, long param_3)
 * Message send/serialize driver. Prepares runtime helpers and reads the message
 * tag (param_3+0x18), this+0x54 size and this+0x40 base; computes a length that
 * is +1 when size<2. Rejects when the type byte (this+0x50&0xff)>7, the
 * 0x100000 flag is set, or the computed length exceeds 0x18 (via FUN_00408510).
 * For small sizes it inspects a byte tag and dispatches through FUN_00407de0 /
 * FUN_0040799c; otherwise FUN_004077b0. On a nonzero status it emits the message
 * via FUN_003504ac/FUN_00084234/FUN_00117cc4 and returns; otherwise it falls to
 * FUN_003518dc and a FUN_000839f8 check, doing a method call, then FINALIZE
 * helpers, zeroing a byte at x19+len for small sizes.
 * Confidence: low
 * Notes: register artifacts extraout_x16, extraout_x8, unaff_x19, unaff_x22,
 * unaff_x30, extraout_w8, extraout_w8_00, extraout_x8_00 (function pointer);
 * callees FUN_00084220/FUN_00352758/FUN_0007c028/FUN_00408510/FUN_00407de0/
 * FUN_0040799c/FUN_004077b0/FUN_003504ac/FUN_00084234/FUN_00117cc4/FUN_003518dc/
 * FUN_000839f8/FUN_0034ba48/FUN_000839d8. */
void sk_r61_004025f4(uint64_t param_1, uint64_t param_2, int64_t param_3)
{
    uint64_t extraout_x16 = 0; /* register artifact: this-like pointer from caller's x16 */
    uint64_t extraout_x8 = 0;  /* register artifact: value inherited from caller's x8 */
    uint64_t unaff_x19 = 0;    /* register artifact: buffer pointer from caller's x19 */
    uint64_t *unaff_x22 = 0;   /* register artifact: pointer from caller's x22 */
    uint64_t unaff_x30 = 0;    /* register artifact: value inherited from caller's x30 */
    int32_t extraout_w8 = 0;   /* register artifact: value inherited from caller's w8 */
    int32_t extraout_w8_00 = 0; /* register artifact: value inherited from caller's w8 */
    void (*extraout_x8_00)(uint64_t, uint64_t, uint64_t) = 0; /* register artifact: fn ptr from caller's x8 */
    uint64_t uVar1, uVar5, uVar7;
    uint32_t uVar2, uVar3, uVar6;
    int32_t iVar4;
    sk_u128_t auVar8;

    sk_rt_00084220();
    sk_rt_00352758();
    uVar7 = *(uint64_t *)(param_3 + 0x18);
    sk_rt_0007c028();
    uVar3 = *(uint32_t *)(extraout_x16 + 0x54);
    uVar5 = *(uint64_t *)(extraout_x8 + 0x40);
    if (uVar3 == 0) {
        uVar5 = uVar5 + 1;
    }
    uVar1 = uVar5;
    if (uVar3 < 2) {
        uVar1 = uVar5 + 1;
    }
    if ((7 < (*(uint32_t *)(extraout_x16 + 0x50) & 0xff) ||
         (*(uint32_t *)(extraout_x16 + 0x50) & 0x100000) != 0) || 0x18 < uVar1) {
        sk_rt_00408510(*unaff_x22);
        goto LAB_00402674;
    }
    if (uVar3 < 2) {
        if (*(uint8_t *)((int64_t)unaff_x22 + uVar5) != 0) {
            uVar6 = (uint32_t)uVar5;
            iVar4 = 0;
            if (uVar6 < 4) {
                iVar4 = (int32_t)*(uint8_t *)((int64_t)unaff_x22 + uVar5) - 1 <<
                        (uint64_t)((uVar6 & 3) << 3);
            }
            if (uVar6 != 0) {
                uVar2 = 4;
                if (uVar6 < 4) {
                    uVar2 = uVar6;
                }
                switch (uVar2) {
                default:
                    break;
                case 2:
                    break;
                case 3:
                    sk_rt_00407de0(iVar4);
                    break;
                case 4:
                    break;
                }
            }
            sk_rt_0040799c();
            iVar4 = extraout_w8_00;
            goto joined_r0x004026fc;
        }
    } else {
        sk_rt_004077b0();
        iVar4 = extraout_w8;
    joined_r0x004026fc:
        if (iVar4 != 0) {
            auVar8 = sk_rt_003504ac();
            sk_rt_00084234(auVar8.lo, auVar8.hi, uVar1, unaff_x30);
            sk_rt_00117cc4();
            return;
        }
    }
    sk_rt_003518dc();
    iVar4 = (int32_t)sk_rt_000839f8().lo;
    if (iVar4 == 0) {
        auVar8 = sk_rt_003504ac(*(uint64_t *)(extraout_x16 + 0x10));
        ((void (*)(uint64_t, uint64_t, uint64_t))extraout_x8_00)(auVar8.lo, auVar8.hi, uVar7);
        sk_rt_0034ba48();
        sk_rt_000839d8();
    } else {
        auVar8 = sk_rt_003504ac();
        sk_rt_00117cc4(auVar8.lo, auVar8.hi, uVar5);
    }
    if (uVar3 < 2) {
        *(uint8_t *)(unaff_x19 + uVar5) = 0;
    }
LAB_00402674:
    sk_rt_00084234();
    return;
}

/* FUN_004027a8 @ 0x004027a8   (est. sk_r61_004027a8)
 * Ghidra: void FUN_004027a8(long param_1,long param_2)
 * Message send/consume driver (2-arg variant of sk_r61_004025f4). Reads the tag
 * at param_2+0x18, prepares FUN_0007c028, and computes a length from this+0x54
 * size and this+0x40 base (+1 when size<2). For small sizes inspects a byte tag
 * at param_1+len and dispatches FUN_003558ec / FUN_0040799c; otherwise
 * FUN_004077b0. On failure status it returns early; otherwise it resolves an
 * object via FUN_00351d24, checks FUN_000839f8, and performs an indirect jump
 * through a jumptable pointer at this+8 after FUN_0007c1c4.
 * Confidence: low
 * Notes: register artifacts extraout_x16, extraout_x8, extraout_w8, extraout_w8_00;
 * UNRECOVERED_JUMPTABLE rendered as a function pointer read at this+8; callees
 * FUN_0007c028/FUN_003558ec/FUN_0040799c/FUN_004077b0/FUN_00351d24/FUN_000839f8/
 * FUN_0007c1c4. */
void sk_r61_004027a8(int64_t param_1, int64_t param_2)
{
    uint64_t extraout_x16 = 0; /* register artifact: this-like pointer from caller's x16 */
    uint64_t extraout_x8 = 0;  /* register artifact: value inherited from caller's x8 */
    int32_t extraout_w8 = 0;   /* register artifact: value inherited from caller's w8 */
    int32_t extraout_w8_00 = 0; /* register artifact: value inherited from caller's w8 */
    uint32_t uVar1, uVar4;
    int32_t iVar2;
    uint64_t lVar3, uVar5;
    sk_u128_t auVar6;
    void (*UNRECOVERED_JUMPTABLE)(void) = 0; /* jumptable pointer read at this+8 */

    uVar5 = *(uint64_t *)(param_2 + 0x18);
    sk_rt_0007c028();
    uVar4 = *(uint32_t *)(extraout_x16 + 0x54);
    lVar3 = *(uint64_t *)(extraout_x8 + 0x40);
    if (uVar4 == 0) {
        lVar3 = lVar3 + 1;
    }
    if (uVar4 < 2) {
        if (*(uint8_t *)(param_1 + lVar3) == 0) goto LAB_0040288c;
        uVar4 = (uint32_t)lVar3;
        iVar2 = 0;
        if (uVar4 < 4) {
            iVar2 = (int32_t)*(uint8_t *)(param_1 + lVar3) - 1 << (uint64_t)((uVar4 & 3) << 3);
        }
        if (uVar4 != 0) {
            uVar1 = 4;
            if (uVar4 < 4) {
                uVar1 = uVar4;
            }
            switch (uVar1) {
            default:
                break;
            case 2:
                break;
            case 3:
                sk_rt_003558ec(iVar2);
                break;
            case 4:
                break;
            }
        }
        sk_rt_0040799c();
        iVar2 = extraout_w8_00;
    } else {
        sk_rt_004077b0(param_1, uVar4, uVar5);
        iVar2 = extraout_w8;
    }
    if (iVar2 != 0) {
        return;
    }
LAB_0040288c:
    auVar6 = sk_rt_00351d24();
    iVar2 = (int32_t)sk_rt_000839f8(auVar6.lo, auVar6.hi, uVar5).lo;
    if (iVar2 != 0) {
        return;
    }
    UNRECOVERED_JUMPTABLE = *(void (**)(void))((uint64_t)extraout_x16 + 8);
    sk_rt_0007c1c4();
    /* Could not recover jumptable at 0x004028d0: treating indirect jump as call */
    UNRECOVERED_JUMPTABLE();
    return;
}

/* FUN_00403350 @ 0x00403350   (est. sk_r61_00403350)
 * Ghidra: int FUN_00403350(void)
 * Status-thinning helper: calls FUN_004077b0 and returns its status decremented
 * by one, or 0 when the status is zero (maps 1..N to 0..N-1, 0 to 0).
 * Confidence: medium
 * Notes: register artifact extraout_w8; callee FUN_004077b0. */
int32_t sk_r61_00403350(void)
{
    int32_t iVar1;
    int32_t extraout_w8 = 0; /* register artifact: status inherited from caller's w8 */

    sk_rt_004077b0();
    iVar1 = 0;
    if (extraout_w8 != 0) {
        iVar1 = extraout_w8 + -1;
    }
    return iVar1;
}

/* FUN_00403354 @ 0x00403354   (est. sk_r61_00403354)
 * Ghidra: int FUN_00403354(void)
 * Status-thinning helper identical in shape to sk_r61_00403350: calls
 * FUN_004077b0 and returns status-1 (0 when status is 0).
 * Confidence: medium
 * Notes: register artifact extraout_w8; callee FUN_004077b0. */
int32_t sk_r61_00403354(void)
{
    int32_t iVar1;
    int32_t extraout_w8 = 0; /* register artifact: status inherited from caller's w8 */

    sk_rt_004077b0();
    iVar1 = 0;
    if (extraout_w8 != 0) {
        iVar1 = extraout_w8 + -1;
    }
    return iVar1;
}

/* FUN_00403728 @ 0x00403728   (est. sk_r61_00403728)
 * Ghidra: int FUN_00403728(void)
 * Status-thinning helper: calls FUN_000839f8 and returns its result decremented
 * by one (or 0 when the result is 0).
 * Confidence: high
 * Notes: callee FUN_000839f8 (16-byte result used as scalar via .lo). */
int32_t sk_r61_00403728(void)
{
    int32_t iVar1, iVar2;

    iVar2 = (int32_t)sk_rt_000839f8().lo;
    iVar1 = 0;
    if (iVar2 != 0) {
        iVar1 = iVar2 + -1;
    }
    return iVar1;
}

/* FUN_0040372c @ 0x0040372c   (est. sk_r61_0040372c)
 * Ghidra: int FUN_0040372c(void)
 * Status-thinning helper identical to sk_r61_00403728: calls FUN_000839f8 and
 * returns result-1 (0 when result is 0).
 * Confidence: high
 * Notes: callee FUN_000839f8 (16-byte result used as scalar via .lo). */
int32_t sk_r61_0040372c(void)
{
    int32_t iVar1, iVar2;

    iVar2 = (int32_t)sk_rt_000839f8().lo;
    iVar1 = 0;
    if (iVar2 != 0) {
        iVar1 = iVar2 + -1;
    }
    return iVar1;
}

/* FUN_004038d0 @ 0x004038d0   (est. sk_r61_004038d0)
 * Ghidra: void FUN_004038d0(long param_1)
 * Object teardown helper. Looks up an object via FUN_00377dcc(0x13f, tag at
 * param_1+0x10); when the returned (inherited) upper word is below 0x40, calls
 * FUN_0034d1c0, FUN_00368980 and FUN_00019858 in sequence.
 * Confidence: medium
 * Notes: register artifact extraout_x1 (holds the descriptor upper word);
 * callees FUN_00377dcc/FUN_0034d1c0/FUN_00368980/FUN_00019858. */
void sk_r61_004038d0(int64_t param_1)
{
    uint64_t extraout_x1 = 0; /* register artifact: lookup result upper word (hi) from caller's x1 */

    sk_rt_00377dcc(0x13f, *(uint64_t *)(param_1 + 0x10));
    if (extraout_x1 < 0x40) {
        sk_rt_0034d1c0();
        sk_rt_00368980();
        sk_rt_00019858();
    }
    return;
}

/* FUN_0040394c @ 0x0040394c   (est. sk_r61_0040394c)
 * Ghidra: long * FUN_0040394c(void)
 * Descriptor/object lookup returning a pointer. Prepares FUN_00349d3c and
 * FUN_00357ec4; when the type/state word at this+0x50 has bits 0x1000f8 set or
 * the inherited size exceeds 0x18, stores the current pointer and returns an
 * aligned offset into the object. Otherwise decodes a variable-width length
 * prefix (1/2/3/4 bytes) at x1+size and either invokes a method pointer at
 * this+0x10 and stores a 1-byte tag, returns the FUN_00117cc4 result, or falls
 * through FUN_00407df0.
 * Confidence: low
 * Notes: register artifacts extraout_x1, extraout_x8, extraout_x16, unaff_x19,
 * unaff_x20; uint3 rendered as low-24-bit read; vtable slot offset 0x10; callees
 * FUN_00349d3c/FUN_00357ec4/FUN_0036b270/FUN_00117cc4/FUN_00407df0. */
int64_t* sk_r61_0040394c(void)
{
    uint8_t bVar1;
    int64_t lVar2;
    int64_t *plVar3;
    uint32_t *extraout_x1 = 0;  /* register artifact: buffer pointer from caller's x1 */
    uint64_t extraout_x8 = 0;   /* register artifact: this-like pointer from caller's x8 */
    uint64_t extraout_x16 = 0;  /* register artifact: value inherited from caller's x16 */
    int64_t *unaff_x19 = 0;     /* register artifact: base pointer from caller's x19 */
    uint64_t unaff_x20 = 0;     /* register artifact: size from caller's x20 */
    uint32_t uVar4, uVar5, uVar6;

    sk_rt_00349d3c();
    sk_rt_00357ec4(extraout_x16);
    if ((*(uint32_t *)(extraout_x8 + 0x50) & 0x1000f8) != 0 || 0x18 < unaff_x20 + 1U) {
        uVar4 = *(uint32_t *)(extraout_x8 + 0x50) & 0xf8;
        lVar2 = *(int64_t *)extraout_x1;
        *unaff_x19 = lVar2;
        sk_rt_0036b270();
        return (int64_t *)(lVar2 + ((uint64_t)(uVar4 + 0x17 & (uVar4 ^ 0xffffffff)) & 0x1f8));
    }
    bVar1 = *(uint8_t *)((int64_t)extraout_x1 + unaff_x20);
    uVar4 = (uint32_t)bVar1;
    if (1 < bVar1) {
        uVar6 = (uint32_t)unaff_x20;
        uVar5 = 4;
        if (uVar6 < 4) {
            uVar5 = uVar6;
        }
        switch (uVar5) {
        default:
            goto switchD_004039f8_caseD_0;
        case 1:
            uVar5 = (uint32_t)(uint8_t)*extraout_x1;
            break;
        case 2:
            uVar5 = (uint32_t)(uint16_t)*extraout_x1;
            break;
        case 3:
            uVar5 = (uint32_t)(*extraout_x1 & 0x00ffffff); /* uint3: 3-byte load */
            break;
        case 4:
            uVar5 = *extraout_x1;
            break;
        }
        uVar4 = uVar5 | (uint32_t)bVar1 - 2 << (uint64_t)((uVar6 & 3) << 3);
        if (3 < uVar6) {
            uVar4 = uVar5;
        }
        uVar4 = uVar4 + 2;
    }
switchD_004039f8_caseD_0:
    if (uVar4 == 1) {
        ((void (*)(void))(**(uint64_t **)((uint64_t)extraout_x8 + 0x10)))();
        *(uint8_t *)((int64_t)unaff_x19 + unaff_x20) = 1;
    } else {
        if (uVar4 != 0) {
            plVar3 = (int64_t *)sk_rt_00117cc4();
            return plVar3;
        }
        sk_rt_00407df0();
    }
    return unaff_x19;
}

/* FUN_00404620 @ 0x00404620   (est. sk_r61_00404620)
 * Ghidra: void FUN_00404620(void)
 * Tiny forwarder: calls FUN_00353498 then FUN_00374104 in sequence.
 * Confidence: high
 * Notes: callees FUN_00353498 (extern), FUN_00374104 (extern, 16-byte result
 * unused). */
void sk_r61_00404620(void)
{
    sk_rt_00353498();
    sk_rt_00374104();
    return;
}
/* FUN_00404654 @ 0x00404654   (est. sk_r61_00404654)
 * Ghidra: void FUN_00404654(void)
 * Thin forwarder: simply calls the shared runtime helper at 0x21480 (a no-arg
 * init/register hook) and returns. No inputs or outputs of its own.
 * Confidence: medium
 * Notes: callee FUN_00021480 */
void sk_r61_00404654(void) {
    sk_rt_00021480();
}

/* FUN_004047ac @ 0x004047ac   (est. sk_r61_004047ac)
 * Ghidra: void FUN_004047ac(undefined8 param_1,undefined8 param_2,undefined8 *param_3)
 * Uses register artifact x20 as the implicit `this` pointer. Calls the runtime
 * hook 0x3504d0, releases the object reference *param_3 via 0x27754, then reads
 * the value produced by 0x4079e4 and stores it at this+8.
 * Confidence: low
 * Notes: register artifact unaff_x20 (thisptr); callees FUN_003504d0, FUN_00027754, FUN_004079e4 */
void sk_r61_004047ac(uint64_t p1, uint64_t p2, uint64_t* p3) {
    uint64_t extraout_x20 = 0; /* register artifact: value inherited from caller's x20 (thisptr) */
    sk_rt_003504d0();
    sk_rt_00027754(*p3);
    *(uint64_t *)((uint64_t)extraout_x20 + 8) = sk_rt_004079e4();
}

/* FUN_004047f8 @ 0x004047f8   (est. sk_r61_004047f8)
 * Ghidra: void FUN_004047f8(void)
 * Calls the runtime hook 0x376820 with the global data object at 0x5a14c0, then
 * reads the value from 0x4079e4 (result discarded).
 * Confidence: medium
 * Notes: global DAT_005a14c0; callees FUN_00376820, FUN_004079e4 */
void sk_r61_004047f8(void) {
    sk_rt_00376820((uint64_t)0x5a14c0);
    sk_rt_004079e4();
}

/* FUN_00404850 @ 0x00404850   (est. sk_r61_00404850)
 * Ghidra: void FUN_00404850(void)
 * Runs the runtime hook 0x4075ec, then the 0x376820 hook (no args) and finally
 * reads 0x4079e4, discarding the result.
 * Confidence: medium
 * Notes: callees FUN_004075ec, FUN_00376820, FUN_004079e4 */
void sk_r61_00404850(void) {
    sk_rt_004075ec();
    sk_rt_00376820();
    sk_rt_004079e4();
}

/* FUN_00404898 @ 0x00404898   (est. sk_r61_00404898)
 * Ghidra: void FUN_00404898(void)
 * Thin forwarder to sibling sk_r61_004049a8, passing the global slot pointer at
 * 0x64c2e0. (Ghidra also showed a second arg &DAT_004ea760, which the one-param
 * callee ignores.)
 * Confidence: high
 * Notes: callee FUN_004049a8 (sibling) */
void sk_r61_00404898(void) {
    sk_r61_004049a8((int64_t*)0x64c2e0);
}

/* FUN_0040489c @ 0x0040489c   (est. sk_r61_0040489c)
 * Ghidra: void FUN_0040489c(void)
 * Thin forwarder to sibling sk_r61_004049a8 with the global slot pointer 0x64c2e0.
 * (Ghidra also showed a second arg &DAT_004ea760, ignored by the one-param callee.)
 * Confidence: high
 * Notes: callee FUN_004049a8 (sibling) */
void sk_r61_0040489c(void) {
    sk_r61_004049a8((int64_t*)0x64c2e0);
}

/* FUN_004048cc @ 0x004048cc   (est. sk_r61_004048cc)
 * Ghidra: void FUN_004048cc(void)
 * Thin forwarder to sibling sk_r61_004049a8 with the global slot pointer 0x656380.
 * (Ghidra also showed a second arg &DAT_004ea794, ignored by the one-param callee.)
 * Confidence: high
 * Notes: callee FUN_004049a8 (sibling) */
void sk_r61_004048cc(void) {
    sk_r61_004049a8((int64_t*)0x656380);
}

/* FUN_004048d0 @ 0x004048d0   (est. sk_r61_004048d0)
 * Ghidra: void FUN_004048d0(void)
 * Thin forwarder to sibling sk_r61_004049a8 with the global slot pointer 0x656380.
 * (Ghidra also showed a second arg &DAT_004ea794, ignored by the one-param callee.)
 * Confidence: high
 * Notes: callee FUN_004049a8 (sibling) */
void sk_r61_004048d0(void) {
    sk_r61_004049a8((int64_t*)0x656380);
}

/* FUN_00404900 @ 0x00404900   (est. sk_r61_00404900)
 * Ghidra: void FUN_00404900(void)
 * Runs the runtime hook 0x406d90, then the 0x376820 hook (no args) and finally
 * reads 0x4079e4, discarding the result.
 * Confidence: medium
 * Notes: callees FUN_00406d90, FUN_00376820, FUN_004079e4 */
void sk_r61_00404900(void) {
    sk_rt_00406d90();
    sk_rt_00376820();
    sk_rt_004079e4();
}

/* FUN_00404948 @ 0x00404948   (est. sk_r61_00404948)
 * Ghidra: void FUN_00404948(long param_1)
 * Runs the runtime hook 0x406478, then reads the value produced by 0x376820 and
 * stores it at param_1+8.
 * Confidence: medium
 * Notes: callees FUN_00406478, FUN_00376820 */
void sk_r61_00404948(int64_t p1) {
    sk_rt_00406478();
    *(uint64_t *)((uint64_t)p1 + 8) = sk_rt_00376820();
}

/* FUN_00404974 @ 0x00404974   (est. sk_r61_00404974)
 * Ghidra: void FUN_00404974(void)
 * Thin forwarder to sibling sk_r61_004049a8 with the global slot pointer 0x656378.
 * (Ghidra also showed a second arg &DAT_004ea7c8, ignored by the one-param callee.)
 * Confidence: high
 * Notes: callee FUN_004049a8 (sibling) */
void sk_r61_00404974(void) {
    sk_r61_004049a8((int64_t*)0x656378);
}

/* FUN_00404978 @ 0x00404978   (est. sk_r61_00404978)
 * Ghidra: void FUN_00404978(void)
 * Thin forwarder to sibling sk_r61_004049a8 with the global slot pointer 0x656378.
 * (Ghidra also showed a second arg &DAT_004ea7c8, ignored by the one-param callee.)
 * Confidence: high
 * Notes: callee FUN_004049a8 (sibling) */
void sk_r61_00404978(void) {
    sk_r61_004049a8((int64_t*)0x656378);
}

/* FUN_004049a8 @ 0x004049a8   (est. sk_r61_004049a8)
 * Ghidra: void FUN_004049a8(long *param_1)
 * Lazy one-time slot initializer. If *param_1 (the cached slot) is still null,
 * reports the fatal message pair (&DAT_0064c2d8, &DAT_004bbe30) via 0x27614,
 * allocates a 16-byte descriptor via 0x27670 (lo/hi halves), invokes 0x6b6f4
 * (lo, hi, &local_40 where local_40 = 0x6720e8), and caches the value returned by
 * 0x376820 into *param_1.
 * Confidence: medium
 * Notes: globals DAT_0064c2d8, DAT_004bbe30; local_40=0x6720e8;
 *        callees FUN_00027614, FUN_00027670, FUN_0006b6f4, FUN_00376820 */
void sk_r61_004049a8(int64_t* p1) {
    uint64_t uStack_38;
    uint64_t local_40;

    if (*p1 == 0) {
        sk_rt_00027614((uint64_t)0x64c2d8, (uint64_t)0x4bbe30);
        sk_u128_t auVar2 = sk_rt_00027670();
        uStack_38 = auVar2.lo;
        local_40 = 0x6720e8;
        sk_rt_0006b6f4(auVar2.lo, auVar2.hi, &local_40);
        *p1 = (int64_t)sk_rt_00376820();
    }
}

/* FUN_00404a24 @ 0x00404a24   (est. sk_r61_00404a24)
 * Ghidra: void FUN_00404a24(void)
 * Calls the runtime hook 0x376820 with the global data object at 0x5a1538, then
 * reads the value from 0x4079e4 (result discarded).
 * Confidence: medium
 * Notes: global DAT_005a1538; callees FUN_00376820, FUN_004079e4 */
void sk_r61_00404a24(void) {
    sk_rt_00376820((uint64_t)0x5a1538);
    sk_rt_004079e4();
}

/* FUN_00404a7c @ 0x00404a7c   (est. sk_r61_00404a7c)
 * Ghidra: void FUN_00404a7c(long param_1)
 * Runs the runtime hook 0x406d90, then reads the value produced by 0x376820 and
 * stores it at param_1+8.
 * Confidence: medium
 * Notes: callees FUN_00406d90, FUN_00376820 */
void sk_r61_00404a7c(int64_t p1) {
    sk_rt_00406d90();
    *(uint64_t *)((uint64_t)p1 + 8) = sk_rt_00376820();
}
