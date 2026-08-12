/* Recreated from exclavecore_bundle.t8142.RELEASE.im4p (cL4 Secure Kernel,
 * arm64e, image base 0) - the cL4 microkernel (GL1), "cL4 (679.100.61)".
 * Ground truth: Ghidra FUN_ names + addresses in the cl4_kernel.raw program.
 * Batch SK190: addresses 0x0040fd2c - 0x004158ac. This is a Swift
 * object-service / vspace / syscall-dispatch region of the cL4 kernel.
 * All function names are estimates; cross-region callees keep their FUN_
 * names as identifiers per the sibling-slice convention and are declared
 * extern below.  Decompiler register artifacts (extraout_xN, unaff_xN) are
 * modelled as locals/params; 16-byte x0:x1 Swift value returns are wpair_t.
 * Confidence: medium unless a specific function header says otherwise. */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

typedef uint64_t word_t;
typedef struct { uint64_t lo, hi; } wpair_t;   /* 16-byte (x0:x1) Swift value returns */
typedef uint64_t (*code)();                     /* unspecified-arity word-returning fn ptr */

#define SCARRY8(a, b)  (__builtin_add_overflow((a), (b), &(unsigned long){0}))
#define SBORROW8(a, b) (__builtin_sub_overflow((a), (b), &(unsigned long){0}))
#define LZCOUNT(x)     ((unsigned long)__builtin_clzll((unsigned long)(x)))
#define CL4_FATAL() __builtin_trap()

/* Ghidra SoftwareBreakpoint(code, addr) - a trap/brk that does not return. */
static inline unsigned long SoftwareBreakpoint(unsigned long kind, unsigned long addr)
{ (void)kind; (void)addr; __builtin_trap(); }

/* In-batch function forward declarations (unspecified params: the decompiled
 * call sites disagree with the callee signatures, so call arity is left
 * unchecked at call time; definitions carry the real types). */

void FUN_0040fd2c(uint64_t pad1);
bool FUN_0040fdb4(uint64_t p1);
bool FUN_0040feac(int64_t p1);
void FUN_0040fed8(uint64_t p1, uint64_t p2, uint64_t p3);
void FUN_0040ff40(int64_t p1, uint64_t pad2);
uint64_t FUN_0041001c(uint64_t p1, uint64_t p2);
void FUN_00410414(uint64_t pad1, uint64_t pad2);
uint64_t FUN_004107e4(uint64_t p1);
void FUN_004108a0(int64_t * p1, uint64_t p2);
void FUN_00410bc8(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t pad5);
void FUN_00410c2c(uint64_t pad1);
uint64_t FUN_00410cfc(uint64_t p1, uint64_t p2);
uint32_t FUN_00410e78(uint64_t pad1);
void FUN_00410f44(int64_t p1, uint64_t pad2);
uint64_t FUN_0041102c(int64_t p1);
void FUN_0041106c(uint8_t * buf, uint64_t obj);
uint64_t FUN_004110a4(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t pad4);
uint8_t FUN_004110ec(int64_t p1, int64_t p2);
uint32_t FUN_004111b0(int64_t p1, int64_t p2);
uint64_t FUN_00411290(int64_t p1, int64_t p2);
uint64_t FUN_00411308(int64_t p1, int64_t p2);
uint64_t FUN_004113d4(int64_t p1, int64_t p2);
uint32_t FUN_0041144c(int64_t p1, int64_t p2);
uint32_t FUN_004114fc(int64_t p1, int64_t p2);
uint64_t FUN_00411624(int64_t p1, int64_t p2);
uint64_t FUN_00411818(int64_t p1, int64_t p2);
uint64_t FUN_00411930(int64_t p1, int64_t p2);
void FUN_00411994(uint64_t pad1);
void FUN_004119c0(uint64_t pad1);
wpair_t FUN_00411a54(uint64_t pad1);
wpair_t FUN_00411bbc(void);
void FUN_00411bfc(uint64_t pad1);
wpair_t FUN_00411c8c(void);
wpair_t FUN_00411cc4(uint64_t reg_x20);
bool FUN_00411d40(uint64_t pad1);
void FUN_00411d94(uint8_t * buf, uint64_t v0, uint64_t v1, uint64_t v2);
void FUN_00411dd8(uint64_t pad1);
void FUN_00411e40(uint64_t * reg);
wpair_t FUN_00411f04(uint64_t a, uint64_t b, uint64_t c, uint64_t d);
void FUN_00411f48(uint64_t * reg);
void FUN_00411f4c(uint64_t * reg);
void FUN_00411f68(code cb);
void FUN_00411ff4(uint64_t pad1);
void FUN_0041202c(uint64_t pad1);
void FUN_00412074(uint64_t pad1);
wpair_t FUN_00412118(uint64_t pad1);
void FUN_004121b0(uint64_t pad1);
uint64_t FUN_00412248(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8);
void FUN_0041235c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5);
void FUN_00412494(uint64_t pad1);
void FUN_004124cc(uint64_t pad1);
void FUN_004125ac(uint64_t * obj);
void FUN_0041260c(uint64_t * obj);
wpair_t FUN_00412694(uint64_t pad1);
void FUN_00412788(uint64_t pad1);
bool FUN_004127b4(uint64_t pad1);
void FUN_0041288c(uint64_t pad1);
void FUN_004129ec(void);
uint64_t FUN_00412a58(uint64_t * p1, uint64_t * p2);
void FUN_00412bb0(uint64_t * reg);
void FUN_00412c54(void);
void FUN_00412c94(void);
uint64_t FUN_00412ce0(uint64_t pad1);
uint64_t FUN_00412ce4(uint64_t pad1);
void FUN_00412d00(uint64_t obj);
void FUN_00412d5c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t pad5);
void FUN_00412d98(uint64_t pad1);
void FUN_00412e18(uint64_t pad1);
int64_t FUN_00412e8c(uint64_t pad1);
void * FUN_00412eec(uint64_t pad1);
void FUN_00412fe4(uint64_t pad1);
uint8_t FUN_00413024(wpair_t p1, wpair_t p2);
void FUN_0041360c(uint64_t * p1, uint64_t p2);
void FUN_004139b0(uint64_t pad1);
uint64_t FUN_00413a0c(uint64_t pad1);
void FUN_00413a60(uint64_t * reg);
void FUN_00413aa0(uint64_t pad1);
void FUN_00413aec(void);
void FUN_00413b2c(uint64_t pad1);
wpair_t FUN_00413b68(uint64_t pad1);
void FUN_00414118(uint64_t pad1);
bool FUN_00414154(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, int64_t p5, uint32_t p6, uint64_t p7, uint64_t p8);
void FUN_004141ac(uint8_t * p1, uint64_t p2, uint64_t p3, uint64_t pad4, uint64_t pad5);
void FUN_00414214(uint64_t pad1);
void FUN_00414290(uint64_t pad1);
void FUN_00414334(uint8_t * p1, uint64_t p2, uint64_t p3, uint64_t p4);
void FUN_0041437c(uint64_t pad1);
void FUN_004143e8(uint64_t pad1);
void FUN_0041445c(uint64_t p1);
void FUN_0041449c(int64_t p1);
uint64_t FUN_0041454c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t pad4);
void FUN_00414594(uint64_t pad1);
void FUN_004145c0(uint64_t pad1);
wpair_t FUN_00414644(uint64_t p1);
uint32_t FUN_0041465c(int64_t p1, int64_t p2, uint64_t p3);
uint8_t FUN_00414b64(uint64_t pad1);
void FUN_00414bd8(uint64_t * p1, uint64_t * p2, uint8_t p3, uint8_t p4);
void FUN_00414bf4(uint64_t pad1);
uint8_t FUN_00414cb0(uint64_t pad1);
void FUN_00414d04(uint8_t * p1);
void FUN_00414d4c(uint64_t pad1);
void FUN_00414dac(uint64_t pad1);
uint64_t FUN_00414dec(uint16_t * p1, double * p2);
void FUN_004150e8(uint8_t * p1);
uint64_t FUN_00415430(uint64_t pad1, uint64_t pad2);
uint64_t FUN_00415470(uint64_t p1);
void FUN_00415484(uint8_t * p1, uint64_t * p2, uint64_t pad3);
void FUN_004154b8(uint64_t * p1);
void FUN_004154f0(uint64_t p1, uint64_t pad2);
void FUN_00415570(uint64_t p1, code * p2);
void FUN_004155c8(uint64_t p1, uint64_t pad2);
void FUN_00415634(uint64_t p1, uint64_t p2);
void FUN_0041567c(uint64_t p1, uint8_t p2, uint64_t pad3, uint64_t pad4);
void FUN_0041574c(uint64_t p1, uint64_t p2, uint64_t pad3, uint64_t pad4);
void FUN_0041577c(uint64_t p1, uint64_t p2, code cb);
void FUN_004157c8(uint64_t p1, char p2, uint64_t pad3, uint64_t pad4);
void FUN_00415814(uint64_t p1, uint64_t p2, uint64_t pad3, uint64_t pad4);
void FUN_00415818(uint64_t p1, uint64_t p2, uint64_t pad3, uint64_t pad4);
void FUN_00415848(uint64_t p1, char p2, uint64_t pad3, uint64_t pad4);
void FUN_004158ac(uint64_t p1, char p2);

/* Cross-region / sibling callees (extern, sibling-slice convention). */
extern uint64_t FUN_00002534();
extern uint64_t FUN_000026e8();
extern uint64_t FUN_00002850();
extern uint64_t FUN_0001a1c8();
extern uint64_t FUN_00027724();
extern uint64_t FUN_0006a374();
extern uint64_t FUN_0006a4c0();
extern uint64_t FUN_0006b674();
extern wpair_t FUN_0006b6f4();
extern wpair_t FUN_00077888();
extern uint64_t FUN_00077894();
extern wpair_t FUN_0007c1c4();
extern uint64_t FUN_000839d8();
extern uint64_t FUN_0008409c();
extern uint64_t FUN_00084174();
extern uint64_t FUN_00084180();
extern uint64_t FUN_00084220();
extern uint64_t FUN_00084234();
extern uint64_t FUN_00086840();
extern uint64_t FUN_0008e500();
extern wpair_t FUN_0008e518();
extern uint64_t FUN_0009461c();
extern uint64_t FUN_000a6f68();
extern uint64_t FUN_000a6fe0();
extern uint64_t FUN_000b4390();
extern uint64_t FUN_000dbc98();
extern wpair_t FUN_000e72b0();
extern uint64_t FUN_000e72d4();
extern uint64_t FUN_000f4ae8();
extern uint64_t FUN_00100c04();
extern uint64_t FUN_00100efc();
extern uint64_t FUN_0010a9f8();
extern uint64_t FUN_00117cc4();
extern uint64_t FUN_001a84f4();
extern uint64_t FUN_001a8564();
extern uint64_t FUN_001afa84();
extern uint64_t FUN_001b9084();
extern uint64_t FUN_001bc440();
extern uint64_t FUN_00205844();
extern uint64_t FUN_0022995c();
extern uint64_t FUN_00229a3c();
extern uint64_t FUN_00294cb4();
extern uint64_t FUN_002a0cf8();
extern uint64_t FUN_002a4ab4();
extern uint64_t FUN_002ad78c();
extern uint64_t FUN_002eaa34();
extern uint64_t FUN_00349a18();
extern uint64_t FUN_0034bd90();
extern uint64_t FUN_0034c444();
extern uint64_t FUN_0034e1ec();
extern uint64_t FUN_0034fe80();
extern uint64_t FUN_003504ac();
extern uint64_t FUN_003504d0();
extern uint64_t FUN_0035053c();
extern uint64_t FUN_003507e0();
extern uint64_t FUN_00350980();
extern uint64_t FUN_0035098c();
extern uint64_t FUN_003509bc();
extern uint64_t FUN_003509ec();
extern uint64_t FUN_00350a28();
extern uint64_t FUN_00350a88();
extern uint64_t FUN_00350b54();
extern uint64_t FUN_00350c5c();
extern wpair_t FUN_003511cc();
extern wpair_t FUN_003511d8();
extern uint64_t FUN_003513fc();
extern uint64_t FUN_00351a44();
extern uint64_t FUN_00351a50();
extern uint64_t FUN_00351d18();
extern uint64_t FUN_00351da8();
extern uint64_t FUN_00351db4();
extern uint64_t FUN_00351e3c();
extern uint64_t FUN_0035292c();
extern uint64_t FUN_00355538();
extern uint64_t FUN_00356c6c();
extern uint64_t FUN_00359018();
extern uint64_t FUN_00365b6c();
extern uint64_t FUN_0036986c();
extern uint64_t FUN_0036993c();
extern uint64_t FUN_0036a940();
extern uint64_t FUN_0036b118();
extern uint64_t FUN_0036b270();
extern uint64_t FUN_003a25d4();
extern uint64_t FUN_004080b0();
extern uint64_t FUN_0040fc50();
extern uint64_t FUN_00415b54();
extern uint64_t FUN_00415f84();
extern uint64_t FUN_004165ec();
extern uint64_t FUN_0041680c();
extern uint64_t FUN_00416ad0();
extern uint64_t FUN_00416cfc();
extern uint64_t FUN_00417454();
extern uint64_t FUN_00417b60();
extern uint64_t FUN_00418050();
extern uint64_t FUN_00418110();
extern uint64_t FUN_0041913c();
extern uint64_t FUN_00419b14();
extern uint64_t FUN_0041a3ec();
extern uint64_t FUN_0041a64c();
extern uint64_t FUN_0041ae14();
extern uint64_t FUN_0041aee4();
extern uint64_t FUN_0041b088();
extern uint64_t FUN_0041b1d4();
extern uint64_t FUN_0041b3d4();
extern uint64_t FUN_0041bdac();
extern uint64_t FUN_0041be80();
extern uint64_t FUN_0041cf18();
extern uint64_t FUN_0042d050();
extern uint64_t FUN_00447144();
extern uint64_t FUN_00449034();
extern uint64_t FUN_004491c4();
extern uint64_t FUN_0044ae70();
extern uint64_t FUN_0044b000();
extern uint64_t FUN_0044b23c();
extern uint64_t FUN_0044b35c();
extern uint64_t FUN_0044c444();
extern uint64_t FUN_00450adc();
extern uint64_t FUN_00451894();
extern uint64_t FUN_00451a64();
extern wpair_t FUN_0045399c();
extern uint64_t FUN_00456294();
extern uint64_t FUN_004580b4();
extern uint64_t FUN_0045811c();
extern uint64_t FUN_00458190();
extern uint64_t FUN_004582e8();
extern uint64_t FUN_00458720();
extern uint64_t FUN_004588cc();
extern uint64_t FUN_00458940();
extern uint64_t FUN_004589bc();
extern uint64_t FUN_004589e8();
extern uint64_t FUN_004589f8();
extern uint64_t FUN_00458a20();
extern uint64_t FUN_00458a30();
extern uint64_t FUN_00458a58();
extern uint64_t FUN_00458a68();
extern uint64_t FUN_00458a90();
extern uint64_t FUN_00458aa0();
extern uint64_t FUN_00458ac8();
extern uint64_t FUN_00458af8();
extern uint64_t FUN_00458b14();
extern uint64_t FUN_00458b24();
extern uint64_t FUN_00458b6c();
extern uint64_t FUN_00458d30();
extern uint64_t FUN_00458d40();
extern uint64_t FUN_00458e50();
extern uint64_t FUN_00458e80();
extern uint64_t FUN_00458eec();
extern uint64_t FUN_00458f88();
extern uint64_t FUN_00459024();
extern uint64_t FUN_00460d94();
extern uint64_t FUN_00460dcc();
extern uint64_t FUN_00461cb8();
extern uint64_t FUN_00462728();
extern uint64_t FUN_00462898();
extern uint64_t FUN_00462948();
extern uint64_t FUN_0046295c();
extern uint64_t FUN_00462adc();
extern uint64_t FUN_00462b6c();
extern uint64_t FUN_00462b80();
extern uint64_t FUN_00462d5c();
extern uint64_t FUN_00462e0c();
extern uint64_t FUN_00463210();
extern wpair_t FUN_004632e0();
extern uint64_t FUN_004632f4();
extern uint64_t FUN_00463558();
extern uint64_t FUN_00463718();
extern uint64_t FUN_00463878();
extern uint64_t FUN_004639fc();
extern uint64_t FUN_00463a58();
extern uint64_t FUN_00463bd4();
extern uint64_t FUN_00463de0();
extern wpair_t FUN_00463dec();
extern uint64_t FUN_00463df8();
extern uint64_t FUN_00463e10();
extern uint64_t FUN_00463e1c();
extern uint64_t FUN_00463e38();
extern uint64_t FUN_00463e54();
extern uint64_t FUN_00463e70();
extern uint64_t FUN_00463e8c();
extern uint64_t FUN_00463ea8();
extern uint64_t FUN_00463ec4();
extern uint64_t FUN_00463ee0();
extern uint64_t FUN_00463efc();
extern uint64_t FUN_00463f18();
extern wpair_t FUN_00463f94();
extern uint64_t FUN_00464000();
extern uint64_t FUN_004640c4();
extern uint64_t FUN_004642c0();
extern uint64_t FUN_004642d4();
extern uint64_t FUN_004644dc();
extern uint64_t FUN_004644e8();
extern uint64_t FUN_004644f8();
extern wpair_t FUN_00464640();
extern wpair_t FUN_00464650();
extern uint64_t FUN_004647b4();
extern wpair_t FUN_004647e4();
extern wpair_t FUN_0046482c();
extern wpair_t FUN_00464880();
extern wpair_t FUN_004648ec();
extern uint64_t FUN_00464a08();
extern uint64_t FUN_00464a38();
extern uint64_t FUN_00464a44();
extern uint64_t FUN_00464aac();
extern uint64_t FUN_00464ac4();
extern uint64_t FUN_00464d00();
extern uint64_t FUN_00464d0c();
extern uint64_t FUN_00464de4();
extern uint64_t FUN_00464e1c();
extern uint64_t FUN_00464e28();
extern uint64_t FUN_00464e40();
extern uint64_t FUN_00464eb0();
extern uint64_t FUN_00464fc4();
extern uint64_t FUN_00465054();
extern uint64_t FUN_004650f0();
extern uint64_t FUN_00465110();
extern uint64_t FUN_00465128();
extern uint64_t FUN_004651a8();
extern uint64_t FUN_00465234();
extern uint64_t FUN_00465240();
extern uint64_t FUN_00465264();
extern uint64_t FUN_00465270();
extern uint64_t FUN_00465294();
extern uint64_t FUN_004652a0();
extern uint64_t FUN_00465418();
extern uint64_t FUN_00465478();
extern uint64_t FUN_0046555c();
extern uint64_t FUN_00465584();
extern uint64_t FUN_004655fc();
extern uint64_t FUN_0046565c();
extern uint64_t FUN_00465674();
extern uint64_t FUN_004656d4();
extern uint64_t FUN_004657ac();
extern uint64_t FUN_004657b8();
extern uint64_t FUN_00465818();
extern uint64_t FUN_00465830();
extern uint64_t FUN_00465884();
extern uint64_t FUN_004658a8();
extern uint64_t FUN_004658cc();
extern uint64_t FUN_004658d8();
extern uint64_t FUN_00465938();
extern uint64_t FUN_004659bc();
extern uint64_t FUN_004659e8();
extern uint64_t FUN_00465a40();
extern uint64_t FUN_00465a88();
extern uint64_t FUN_00465aa0();
extern uint64_t FUN_00465b04();
extern uint64_t FUN_00465b58();
extern uint64_t FUN_00465c00();
extern wpair_t FUN_00465c0c();
extern uint64_t FUN_00465c44();
extern uint64_t FUN_00465c5c();
extern uint64_t FUN_00465c74();
extern uint64_t FUN_00465d08();
extern uint64_t FUN_00465d98();
extern uint64_t FUN_00465fd4();
extern uint64_t FUN_004660e0();
extern uint64_t FUN_00466104();
extern uint64_t FUN_00466124();
extern uint64_t FUN_00466130();
extern uint64_t FUN_0046613c();
extern uint64_t FUN_00466168();
extern uint64_t FUN_004661e4();
extern uint64_t FUN_0046622c();
extern uint64_t FUN_00466264();
extern uint64_t FUN_004662f4();
extern uint64_t FUN_004664f8();
extern uint64_t FUN_00466528();
extern uint64_t FUN_00466540();
extern wpair_t FUN_00466554();
extern uint64_t FUN_00466568();
extern uint64_t FUN_004665bc();
extern uint64_t FUN_0046660c();
extern uint64_t FUN_0046663c();
extern uint64_t FUN_0046666c();
extern uint64_t FUN_004666b4();
extern uint64_t FUN_004666cc();
extern uint64_t FUN_004666e4();
extern uint64_t FUN_004666f8();
extern uint64_t thunk_FUN_002298d4();
extern uint64_t thunk_FUN_002acbb8();
extern uint64_t thunk_FUN_0036b270();
extern uint64_t thunk_FUN_00413b68();
extern uint64_t thunk_FUN_00449d70();

/* Global lookup tables / strings referenced by the batch. */
extern uint64_t DAT_004baeb0;
extern uint64_t DAT_004c2450;
extern uint64_t DAT_005a1800;
extern uint8_t DAT_005a19a8[];
extern uint8_t DAT_005a3698[];
extern uint8_t DAT_005a3838[];
extern uint8_t DAT_005a3930[];
extern uint8_t DAT_005a3a50[];
extern uint8_t DAT_00657778[];
extern uint64_t DAT_00657788;
extern char s_absent_function_005dd080[];
extern char s_changeMatchingOptions__005dd0c0[];
extern uint64_t uram_00000000004baeb8;
extern uint64_t uram_00000000004c2458;
extern uint64_t uram_00000000005a1808;

/* ==================================================================== *
 * SK190 function bodies
 * ==================================================================== */

/* FUN_0040fd2c @ 0x0040fd2c */
void FUN_0040fd2c(uint64_t pad1)
{
    uint64_t r1;
    uint64_t r2;
    uint8_t r3;
    uint64_t * reg_x20;
    uint64_t r4;
    uint8_t s_78[72];
      r1 = *reg_x20;
      r2 = reg_x20[1];
      r4 = reg_x20[2];
      r3 = *(uint8_t *)(reg_x20 + 3);
      FUN_001a84f4(s_78);
      FUN_0040fc50(s_78,r1,r2,r4,r3);
      FUN_001a8564();
      return;
}
/* FUN_0040fdb4 @ 0x0040fdb4 */
bool FUN_0040fdb4(uint64_t p1)
{
    code * pcVar1;
    bool bVar2;
    uint64_t r3;
    int64_t extraout_x8 = 0;
    uint64_t r4;
    int64_t extraout_x9 = 0;
    bool bVar5;
    uint64_t r6;
    uint64_t r7;
    int64_t lVar8;
      if (p1 >> 0x3c == 2) {
        p1 = p1 & 0xfffffffffffffff;
        if ((*(uint8_t *)(p1 + 0x60) < 2) ||
           ((*(uint8_t *)(p1 + 0x60) == 3 &&
            (lVar8 = FUN_00463558(*(uint64_t *)(p1 + 0x10),*(uint64_t *)(p1 + 0x40),
                                  *(uint64_t *)(p1 + 0x50),*(uint64_t *)(p1 + 0x20),
                                  *(uint64_t *)(p1 + 0x30)),
            (lVar8 == 0 && extraout_x9 == 0) && extraout_x8 == 0)))) {
          return true;
        }
      }
      lVar8 = FUN_004107e4(0);
      if (lVar8 == 0) {
        bVar5 = false;
      }
      else {
        r7 = *(uint64_t *)(lVar8 + 0x10);
        r4 = 0;
        do {
          bVar2 = r7 == r4;
          bVar5 = !bVar2;
          if (bVar2) break;
          if (*(uint64_t *)(lVar8 + 0x10) <= r4) {

            pcVar1 = (code *)SoftwareBreakpoint(1,0x40fea0);
            (*pcVar1)();
          }
          r6 = *(uint64_t *)(lVar8 + r4 * 8 + 0x20);
          FUN_0036b270(r6 & 0xfffffffffffffff);
          r3 = FUN_0040fdb4(r6);
          FUN_0036b118(r6 & 0xfffffffffffffff);
          r4 = r4 + 1;
        } while ((r3 & 1) == 0);
        FUN_0036b118(lVar8);
      }
      return bVar5;
}
/* FUN_0040feac @ 0x0040feac */
bool FUN_0040feac(int64_t p1)
{
    uint8_t bVar1;
    int64_t lVar2;
    uint8_t * pbVar3;
      lVar2 = *(long *)(p1 + 0x10) + 1;
      pbVar3 = (uint8_t *)(p1 + 0x20);
      do {
        lVar2 = lVar2 + -1;
        if (lVar2 == 0) break;
        bVar1 = *pbVar3;
        pbVar3 = pbVar3 + 0x50;
      } while (1 < bVar1);
      return lVar2 != 0;
}
/* FUN_0040fed8 @ 0x0040fed8 */
void FUN_0040fed8(uint64_t p1, uint64_t p2, uint64_t p3)
{
    uint64_t r1;
    int64_t reg_x21;
      r1 = FUN_00350a28();
      FUN_0040ff40(p3,0);
      if (reg_x21 == 0) {
        FUN_0036b270(r1 & 0xfffffffffffffff);
        FUN_0036b270();
        FUN_0036b270();
      }
      FUN_003509bc();
      return;
}
/* FUN_0040ff40 @ 0x0040ff40 */
void FUN_0040ff40(int64_t p1, uint64_t pad2)
{
    int64_t lVar1;
    uint8_t s_e0[80];
    char s_90[24];
    uint64_t s_78;
    uint64_t s_70;
      lVar1 = *(long *)(p1 + 0x10);
      p1 = p1 + 0x20;
      while( true ) {
        if (lVar1 == 0) {
          return;
        }
        FUN_00117cc4(s_90,p1,0x49);
        if (s_90[0] != '\x02') break;
        p1 = p1 + 0x50;
        lVar1 = lVar1 + -1;
        s_90[0] = '\x02';
      }
      FUN_00117cc4(s_e0,p1,0x49);
      FUN_00002534(0x657bb0,&DAT_005a3698);
      FUN_00463a58();
      FUN_0036993c();
      FUN_00351a50();
      FUN_00117cc4(p1,s_e0,0x49);
      *(uint64_t *)(p1 + 0x50) = s_78;
      *(uint64_t *)(p1 + 0x58) = s_70;
      FUN_0036986c();
      FUN_00464aac();
      FUN_00459024();
      return;
}
/* FUN_00410414 @ 0x00410414 */
void FUN_00410414(uint64_t pad1, uint64_t pad2)
{
    uint64_t r1;
    uint64_t r2;
    uint8_t r3;
    uint64_t r4;
    uint64_t r5;
    uint64_t r6;
    uint64_t reg_x23;
    uint64_t reg_x24;
    uint64_t r7;
    uint64_t reg_x30;
    wpair_t pair8;
    uint8_t s_170[88];
    uint64_t s_118;
    uint64_t s_110;
    uint64_t s_108;
    uint64_t s_100;
    uint64_t s_f8;
    uint64_t s_d0;
    uint64_t s_c8;
    uint8_t s_a8[168];
      pair8 = FUN_0008e518();
      r4 = pair8.hi;
      r6 = pair8.lo;
      switch(r4 >> 0x3c) {
      default:
        r5 = *(uint64_t *)(r4 + 0x10);
        r6 = *(uint64_t *)(r4 + 0x18);
        FUN_004666b4();
        FUN_0036b270(r5);
        FUN_0036b270(r6);
        FUN_003507e0();
        FUN_004580b4();
        FUN_003504ac();
        FUN_00458720();
        FUN_0036b118(r6);
        goto LAB_00410540;
      case 1:
        r4 = r4 & 0xfffffffffffffff;
        r6 = *(uint64_t *)(r4 + 0x10);
        r1 = *(uint64_t *)(r4 + 0x18);
        r4 = *(uint64_t *)(r4 + 0x20);
        FUN_00464e1c();
        thunk_FUN_002298d4();
        FUN_0036b270(r6);
        FUN_003507e0();
        FUN_004580b4();
        FUN_0036b118(r6);
        thunk_FUN_002298d4(r1 >> 0xe);
        r4 = r4 >> 0xe;
        break;
      case 2:
        pair8 = FUN_004647e4();
        FUN_00117cc4(pair8.lo,pair8.hi,0x80);
        FUN_00465b58();
        FUN_00117cc4(s_a8,s_170,0x51);
        FUN_004661e4();
        FUN_00458a90();
        FUN_0041a3ec(r6);
        FUN_004647b4(s_118);
        thunk_FUN_002298d4();
        thunk_FUN_002298d4(s_110 >> 0xe);
        FUN_00410414(r6,s_108);
        FUN_00458aa0(s_170);
        s_100 = s_100 >> 0xe;
        s_c8 = s_f8;
        goto LAB_00410748;
      case 3:
        pair8 = FUN_004647e4();
        FUN_00117cc4(pair8.lo,pair8.hi,200);
        thunk_FUN_002298d4(3);
        FUN_004661e4();
        FUN_00458a58();
        FUN_00418110(r6);
        FUN_00458a68(s_170);
        goto LAB_00410754;
      case 4:
        pair8 = FUN_004647e4();
        FUN_00117cc4(pair8.lo,pair8.hi,0x88);
        thunk_FUN_002298d4(4);
        FUN_004661e4();
        FUN_00458a20();
        FUN_0041be80(r6);
        FUN_00458a30(s_170);
        goto LAB_00410754;
      case 5:
        FUN_00465418();
        r6 = 5;
        goto LAB_00410658;
      case 6:
        FUN_00465418();
        r6 = 6;
        goto LAB_00410658;
      case 7:
        FUN_00465418();
        r6 = 7;
    LAB_00410658:
        thunk_FUN_002298d4(r6);
        thunk_FUN_0036b270();
        FUN_00462e0c();
        FUN_001b9084();
        FUN_003a25d4();
        thunk_FUN_002298d4(reg_x23 >> 0xe);
        r4 = reg_x24 >> 0xe;
        break;
      case 8:
        pair8 = FUN_004647e4();
        FUN_00117cc4(pair8.lo,pair8.hi,0xb0);
        thunk_FUN_002298d4(8);
        FUN_00117cc4(s_a8,s_170,0x99);
        FUN_004661e4();
        FUN_004589e8();
        FUN_0041360c((uint64_t *)r6, 0);
        FUN_004589f8(s_170);
        s_100 = FUN_004647b4(s_d0);
    LAB_00410748:
        thunk_FUN_002298d4(s_100);
        r4 = s_c8 >> 0xe;
        break;
      case 9:
        r4 = r4 & 0xfffffffffffffff;
        r5 = *(uint64_t *)(r4 + 0x28);
        r1 = *(uint64_t *)(r4 + 0x30);
        r7 = *(uint64_t *)(r4 + 0x38);
        r3 = *(uint8_t *)(r4 + 0x10);
        thunk_FUN_002298d4(9);
        FUN_0036b270(r5);
        FUN_003511cc(r6,r3);
        FUN_004491c4();
        FUN_00084174();
        FUN_004582e8();
        thunk_FUN_002298d4(r1 >> 0xe);
        thunk_FUN_002298d4(r7 >> 0xe);
    LAB_00410540:
        FUN_0008e500(r5,reg_x30);
        FUN_0036b118();
        return;
      case 10:
        r4 = r4 & 0xfffffffffffffff;
        r1 = *(uint64_t *)(r4 + 0x10);
        r2 = *(uint64_t *)(r4 + 0x18);
        r7 = *(uint64_t *)(r4 + 0x40);
        r4 = *(uint64_t *)(r4 + 0x48);
        thunk_FUN_002298d4(10);
        thunk_FUN_002298d4(r1 >> 0xe);
        thunk_FUN_002298d4(r2 >> 0xe);
        FUN_00462948();
        FUN_004588cc();
        FUN_00462b6c(r6);
        FUN_0041235c(0, 0, 0, 0, 0);
        thunk_FUN_002298d4(r7 >> 0xe);
        thunk_FUN_002298d4(r4 >> 0xe);
        FUN_00462948();
        FUN_0008e500();
        FUN_00458940();
        return;
      case 0xb:
        r1 = *(uint64_t *)((r4 & 0xfffffffffffffff) + 0x10);
        r4 = *(uint64_t *)((r4 & 0xfffffffffffffff) + 0x18);
        thunk_FUN_002298d4(0xb);
        thunk_FUN_002298d4(r1 >> 0xe);
        r4 = r4 >> 0xe;
      }
      thunk_FUN_002298d4(r4);
    LAB_00410754:
      FUN_0008e500(reg_x30);
      return;
}
/* FUN_004108a0 @ 0x004108a0 */
void FUN_004108a0(int64_t * p1, uint64_t p2)
{
    uint64_t r1;
    uint8_t r2;
    int64_t lVar3;
    uint64_t r4;
    int64_t extraout_x8 = 0;
    int64_t extraout_x8_00 = 0;
    int64_t extraout_x8_01 = 0;
    int64_t extraout_x8_02 = 0;
    int64_t extraout_x8_03 = 0;
    int64_t extraout_x8_04 = 0;
    int64_t extraout_x8_05 = 0;
    int64_t extraout_x8_06 = 0;
    int64_t extraout_x8_07 = 0;
    int64_t extraout_x8_08 = 0;
    int64_t extraout_x16 = 0;
    int64_t extraout_x16_00 = 0;
    int64_t extraout_x16_01 = 0;
    int64_t extraout_x16_02 = 0;
    int64_t extraout_x16_03 = 0;
    int64_t extraout_x16_04 = 0;
    int64_t extraout_x16_05 = 0;
    int64_t extraout_x16_06 = 0;
    int64_t extraout_x16_07 = 0;
    int64_t extraout_x16_08 = 0;
    uint64_t reg_x20;
    int64_t lVar5;
    uint64_t reg_x21;
    uint64_t reg_x22;
    uint64_t reg_x23;
    uint64_t r6;
    uint64_t reg_x30;
    int64_t lVar7;
    uint64_t r8;
    uint64_t r9;
    wpair_t pair10;
      switch(p2 >> 0x3c) {
      default:
        lVar3 = FUN_00463f18();
        p1[3] = extraout_x8;
        p1[4] = extraout_x16;
        lVar5 = *(long *)(lVar3 + 0x18);
        lVar7 = *(long *)(lVar3 + 0x10);
        p1[1] = *(long *)(lVar3 + 0x18);
        *p1 = lVar7;
        FUN_0036b270(lVar7);
        goto LAB_00410a78;
      case 1:
        p2 = p2 & 0xfffffffffffffff;
        lVar5 = *(long *)(p2 + 0x10);
        p1[3] = 0x682f00;
        p1[4] = 0x681ba0;
        *p1 = lVar5;
        lVar3 = *(long *)(p2 + 0x18);
        p1[2] = *(long *)(p2 + 0x20);
        p1[1] = lVar3;
        goto LAB_00410a78;
      case 2:
        pair10 = FUN_00464650();
        FUN_00117cc4(pair10.lo,pair10.hi,0x80);
        FUN_00463ec4();
        p1[3] = extraout_x8_02;
        p1[4] = extraout_x16_02;
        FUN_00465884(0x67fc08);
        FUN_0036a940();
        pair10 = FUN_00464640();
        FUN_00117cc4(pair10.lo,pair10.hi,0x80);
        FUN_0046613c();
        FUN_00458a90();
        break;
      case 3:
        pair10 = FUN_00464650();
        FUN_00117cc4(pair10.lo,pair10.hi,200);
        FUN_00463ea8();
        p1[3] = extraout_x8_03;
        p1[4] = extraout_x16_03;
        FUN_00466124(0x67fbe0);
        FUN_0036a940();
        pair10 = FUN_00464640();
        FUN_00117cc4(pair10.lo,pair10.hi,200);
        FUN_0046613c();
        FUN_00458a58();
        break;
      case 4:
        pair10 = FUN_00464650();
        FUN_00117cc4(pair10.lo,pair10.hi,0x88);
        FUN_00463efc();
        p1[3] = extraout_x8_00;
        p1[4] = extraout_x16_00;
        FUN_00466130(0x67fbb8);
        FUN_0036a940();
        pair10 = FUN_00464640();
        FUN_00117cc4(pair10.lo,pair10.hi,0x88);
        FUN_0046613c();
        FUN_00458a20();
        break;
      case 5:
        FUN_00465478();
        FUN_00463e70();
        p1[3] = extraout_x8_05;
        p1[4] = extraout_x16_05;
        r4 = 0x67fb90;
        goto LAB_00410abc;
      case 6:
        FUN_00465478();
        FUN_00463e54();
        p1[3] = extraout_x8_06;
        p1[4] = extraout_x16_06;
        r4 = 0x67fb68;
        goto LAB_00410abc;
      case 7:
        FUN_00465478();
        FUN_00463e8c();
        p1[3] = extraout_x8_04;
        p1[4] = extraout_x16_04;
        r4 = 0x67fb40;
    LAB_00410abc:
        FUN_00355538(r4);
        lVar5 = FUN_0036a940();
        *p1 = lVar5;
        *(uint64_t *)(lVar5 + 0x10) = reg_x21;
        *(uint64_t *)(lVar5 + 0x18) = reg_x20;
        *(uint64_t *)(lVar5 + 0x20) = reg_x22;
        *(uint64_t *)(lVar5 + 0x28) = reg_x23;
        FUN_004664f8();
        thunk_FUN_0036b270();
        return;
      case 8:
        pair10 = FUN_00464650();
        FUN_00117cc4(pair10.lo,pair10.hi,0xb0);
        FUN_00463e1c();
        p1[3] = extraout_x8_08;
        p1[4] = extraout_x16_08;
        FUN_00466104(0x67fb18);
        FUN_0036a940();
        pair10 = FUN_00464640();
        FUN_00117cc4(pair10.lo,pair10.hi,0xb0);
        FUN_0046613c();
        FUN_004589e8();
        break;
      case 9:
        p2 = p2 & 0xfffffffffffffff;
        r2 = *(uint8_t *)(p2 + 0x10);
        r4 = *(uint64_t *)(p2 + 0x18);
        r9 = *(uint64_t *)(p2 + 0x20);
        lVar5 = *(long *)(p2 + 0x28);
        r1 = *(uint64_t *)(p2 + 0x30);
        r6 = *(uint64_t *)(p2 + 0x38);
        FUN_00463ee0();
        p1[3] = extraout_x8_01;
        p1[4] = extraout_x16_01;
        FUN_00002850(0x67faf0);
        lVar3 = FUN_0036a940();
        *p1 = lVar3;
        *(uint8_t *)(lVar3 + 0x10) = r2;
        *(uint64_t *)(lVar3 + 0x18) = r4;
        *(uint64_t *)(lVar3 + 0x20) = r9;
        *(long *)(lVar3 + 0x28) = lVar5;
        *(uint64_t *)(lVar3 + 0x30) = r1;
        *(uint64_t *)(lVar3 + 0x38) = r6;
    LAB_00410a78:
        FUN_004664f8(lVar5,reg_x30);
        FUN_0036b270();
        return;
      case 10:
        p2 = p2 & 0xfffffffffffffff;
        r4 = *(uint64_t *)(p2 + 0x20);
        r1 = *(uint64_t *)(p2 + 0x28);
        r9 = *(uint64_t *)(p2 + 0x30);
        r6 = *(uint64_t *)(p2 + 0x38);
        FUN_00463e38();
        p1[3] = extraout_x8_07;
        p1[4] = extraout_x16_07;
        FUN_00465128(0x67fac8);
        lVar5 = FUN_0036a940();
        *p1 = lVar5;
        r8 = *(uint64_t *)(p2 + 0x10);
        *(uint64_t *)(lVar5 + 0x18) = *(uint64_t *)(p2 + 0x18);
        *(uint64_t *)(lVar5 + 0x10) = r8;
        *(uint64_t *)(lVar5 + 0x20) = r4;
        *(uint64_t *)(lVar5 + 0x28) = r1;
        *(uint64_t *)(lVar5 + 0x30) = r9;
        *(uint64_t *)(lVar5 + 0x38) = r6;
        r9 = *(uint64_t *)(p2 + 0x40);
        *(uint64_t *)(lVar5 + 0x48) = *(uint64_t *)(p2 + 0x48);
        *(uint64_t *)(lVar5 + 0x40) = r9;
        FUN_0034c444(r4);
        FUN_004664f8();
        FUN_004588cc();
        return;
      case 0xb:
        p1[3] = 0x683100;
        p1[4] = 0x681ce0;
        lVar5 = *(long *)((p2 & 0xfffffffffffffff) + 0x10);
        p1[1] = *(long *)((p2 & 0xfffffffffffffff) + 0x18);
        *p1 = lVar5;
      }
      FUN_004664f8(reg_x30);
      return;
}
/* FUN_00410bc8 @ 0x00410bc8 */
void FUN_00410bc8(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t pad5)
{
    uint32_t r1;
    wpair_t pair2;
    uint8_t s_48[40];
      FUN_004108a0(s_48,p3);
      pair2 = FUN_00466554();
      FUN_00464e28(pair2.lo,pair2.hi,pair2.lo);
      r1 = FUN_00365b6c();
      FUN_000839d8(p1,r1 ^ 1,1,p4);
      return;
}
/* FUN_00410c2c @ 0x00410c2c */
void FUN_00410c2c(uint64_t pad1)
{
    uint64_t r1;
    code * extraout_x8 = 0;
    uint8_t s_58[32];
    uint64_t s_38;
      FUN_004108a0(s_58, 0);
      FUN_0034e1ec(s_58);
      r1 = FUN_00458e50(s_38);
      FUN_003507e0(r1);
      (*extraout_x8)();
      FUN_00351a50();
      FUN_000026e8(s_58);
      FUN_0009461c();
      return;
}
/* FUN_00410cfc @ 0x00410cfc */
uint64_t FUN_00410cfc(uint64_t p1, uint64_t p2)
{
    uint64_t r1;
    int32_t iVar2;
    char * pcVar3;
    uint8_t * pbVar4;
    uint64_t in_x16;
    uint8_t s_c0[160];
      switch(in_x16) {
      case 2:
        p1 = p1 & 0xfffffffffffffff;
        if (*(uint8_t *)(p1 + 0x60) < 3) {
          return 1;
        }
        if (*(uint8_t *)(p1 + 0x60) == 3) {
          r1 = *(uint64_t *)(p1 + 0x10);
          if ((((*(long *)(p1 + 0x50) == 0 && *(long *)(p1 + 0x58) == 0) &&
               (r1 == 0 && *(long *)(p1 + 0x48) == 0)) &&
              ((*(long *)(p1 + 0x40) == 0 && *(long *)(p1 + 0x38) == 0) &&
              *(long *)(p1 + 0x30) == 0)) &&
              ((*(long *)(p1 + 0x28) == 0 && *(long *)(p1 + 0x20) == 0) &&
              *(long *)(p1 + 0x18) == 0)) {
            return 1;
          }
          if (((r1 & 0xfffffffffffffffe) == 10 || r1 - 1 < 3) &&
             ((((*(long *)(p1 + 0x50) == 0 && *(long *)(p1 + 0x58) == 0) &&
               *(long *)(p1 + 0x48) == 0) &&
              ((*(long *)(p1 + 0x40) == 0 && *(long *)(p1 + 0x38) == 0) &&
              *(long *)(p1 + 0x30) == 0)) &&
              ((*(long *)(p1 + 0x28) == 0 && *(long *)(p1 + 0x20) == 0) &&
              *(long *)(p1 + 0x18) == 0))) {
            return 1;
          }
        }
        break;
      case 3:
      case 9:
      case 10:
        goto switchD_00410d2c_caseD_3;
      case 8:
        FUN_00117cc4(s_c0,(p1 & 0xfffffffffffffff) + 0x10,0x99);
        iVar2 = FUN_00458af8((p1 & 0xfffffffffffffff) + 0x10);
        if (1 < iVar2 - 0xfU) {
          if (iVar2 == 4) {
            pbVar4 = (uint8_t *)FUN_00458b14(s_c0);
            return (uint64_t)((uint32_t)(*pbVar4 < 0x1d) & 0x101fffffU >> (uint64_t)(*pbVar4 & 0x1f));
          }
          if (iVar2 == 0xc) {
            pcVar3 = (char *)FUN_00458b14(s_c0);
            return (uint64_t)(*pcVar3 == '\0');
          }
          return (uint64_t)(iVar2 != 0xd);
        }
      }
      p2 = 0;
    switchD_00410d2c_caseD_3:
      return p2;
}
/* FUN_00410e78 @ 0x00410e78 */
uint32_t FUN_00410e78(uint64_t pad1)
{
    int32_t iVar1;
    char * pcVar2;
    uint8_t * pbVar3;
    uint32_t r4;
    wpair_t pair5;
    uint8_t s_b0[160];
      pair5 = FUN_00463f94();
      FUN_00117cc4(pair5.lo,pair5.hi,0x99);
      iVar1 = FUN_00458af8(s_b0);
      if (1 < iVar1 - 0xfU) {
        if (iVar1 == 4) {
          pbVar3 = (uint8_t *)FUN_00458b14(s_b0);
          r4 = 0x101fffff >> (uint64_t)(*pbVar3 & 0x1f);
          if (0x1c < *pbVar3) {
            r4 = 0;
          }
          goto LAB_00410f0c;
        }
        if (iVar1 != 0xd) {
          if (iVar1 == 0xc) {
            pcVar2 = (char *)FUN_00458b14(s_b0);
            r4 = (uint32_t)(*pcVar2 == '\0');
          }
          else {
            r4 = 1;
          }
          goto LAB_00410f0c;
        }
        FUN_00458b14(s_b0);
      }
      r4 = 0;
    LAB_00410f0c:
      return r4 & 1;
}
/* FUN_00410f44 @ 0x00410f44 */
void FUN_00410f44(int64_t p1, uint64_t pad2)
{
    code * pcVar1;
    uint64_t r2;
    uint64_t r3;
    uint64_t r4;
    uint64_t extraout_x1 = 0;
    code * extraout_x8 = 0;
    code * extraout_x8_00 = 0;
    uint8_t s_58[32];
    uint64_t s_38;
      if (*(long *)(p1 + 0x10) == 0) {

        pcVar1 = (code *)SoftwareBreakpoint(1,0x411024);
        (*pcVar1)();
      }
      FUN_004108a0(s_58,*(uint64_t *)(p1 + 0x20));
      FUN_0034e1ec(s_58);
      FUN_00458e50(s_38);
      r2 = FUN_00350a88();
      r3 = (*extraout_x8)(r2,s_38);
      FUN_000026e8(s_58);
      r4 = FUN_0041102c(p1);
      if (((r4 ^ 0xffffffffffffffff) & 0xf000000000000007) != 0) {
        FUN_004108a0(s_58, 0);
        FUN_00458b24(r4);
        FUN_00464e40();
        FUN_0006a4c0();
        FUN_00351a44();
        r2 = FUN_00458e50();
        FUN_000b4390(r2);
        (*extraout_x8_00)();
        FUN_000026e8(s_58);
        if (r3 >> 0xe <= extraout_x1 >> 0xe) {
          FUN_0009461c();
          return;
        }

        pcVar1 = (code *)SoftwareBreakpoint(1,0x411028);
        (*pcVar1)();
      }

      pcVar1 = (code *)SoftwareBreakpoint(1,0x41102c);
      (*pcVar1)();
}
/* FUN_0041102c @ 0x0041102c */
uint64_t FUN_0041102c(int64_t p1)
{
    uint64_t r1;
      if (*(long *)(p1 + 0x10) == 0) {
        r1 = 0xf000000000000007;
      }
      else {
        r1 = *(uint64_t *)(p1 + *(long *)(p1 + 0x10) * 8 + 0x18);
        FUN_0036b270(r1 & 0xfffffffffffffff);
      }
      return r1;
}
/* FUN_004110a4 @ 0x004110a4 */
uint64_t FUN_004110a4(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t pad4)
{
    uint64_t r1;
    uint64_t r2;
      r1 = FUN_0041144c(p1,p3);
      if ((r1 & 1) != 0) {
        FUN_0007c1c4();
        r2 = FUN_00411930(0, 0);
        return r2;
      }
      return 0;
}
/* FUN_004110ec @ 0x004110ec */
uint8_t FUN_004110ec(int64_t p1, int64_t p2)
{
    uint8_t bVar1;
    uint64_t r2;
    uint64_t r3;
    uint64_t r4;
    uint64_t r5;
    uint8_t bVar6;
    int64_t lVar7;
    uint64_t * puVar8;
    uint64_t * puVar9;
      lVar7 = *(long *)(p1 + 0x10);
      if (lVar7 != *(long *)(p2 + 0x10)) {
        return 0;
      }
      if ((lVar7 != 0) && (p1 != p2)) {
        puVar8 = (uint64_t *)(p1 + 0x48);
        puVar9 = (uint64_t *)(p2 + 0x28);
        while( true ) {
          lVar7 = lVar7 + -1;
          r2 = puVar8[-1];
          r4 = *puVar8;
          r3 = puVar9[3];
          r5 = puVar9[4];
          bVar6 = FUN_0041b1d4(puVar8[-5],puVar8[-4],puVar8[-3],puVar8[-2],puVar9[-1],*puVar9,puVar9[1],
                               puVar9[2]);
          bVar1 = 0;
          if ((r5 ^ r4) < 0x4000) {
            bVar1 = bVar6 & (r3 ^ r2) < 0x4000;
          }
          if (bVar1 != 1) break;
          puVar8 = puVar8 + 6;
          puVar9 = puVar9 + 6;
          if (lVar7 == 0) {
            return bVar1;
          }
        }
        return bVar1;
      }
      return 1;
}
/* FUN_004111b0 @ 0x004111b0 */
uint32_t FUN_004111b0(int64_t p1, int64_t p2)
{
    uint32_t r1;
    int64_t lVar2;
    uint8_t s_4a8[376];
    uint8_t s_330[376];
    uint8_t s_1b8[376];
      lVar2 = *(long *)(p1 + 0x10);
      if (lVar2 == *(long *)(p2 + 0x10)) {
        if ((lVar2 == 0) || (p1 == p2)) {
          r1 = 1;
        }
        else {
          p1 = p1 + 0x20;
          p2 = p2 + 0x20;
          do {
            lVar2 = lVar2 + -1;
            FUN_00117cc4(s_330,p1,0x178);
            FUN_00117cc4(s_1b8,p2,0x178);
            FUN_00458d30(s_330,s_4a8);
            FUN_00458d30(s_1b8,s_4a8);
            r1 = FUN_0041913c(s_330,s_1b8);
            FUN_00458d40(s_1b8);
            FUN_00458d40(s_330);
            if ((r1 & 1) == 0) break;
            p2 = p2 + 0x178;
            p1 = p1 + 0x178;
          } while (lVar2 != 0);
        }
      }
      else {
        r1 = 0;
      }
      return r1 & 1;
}
/* FUN_00411290 @ 0x00411290 */
uint64_t FUN_00411290(int64_t p1, int64_t p2)
{
    int64_t lVar1;
    uint64_t * puVar2;
    uint64_t * puVar3;
      lVar1 = *(long *)(p1 + 0x10);
      if (lVar1 != *(long *)(p2 + 0x10)) {
        return 0;
      }
      if ((lVar1 != 0) && (p1 != p2)) {
        puVar2 = (uint64_t *)(p2 + 0x30);
        puVar3 = (uint64_t *)(p1 + 0x30);
        do {
          if ((char)puVar3[-2] != (char)puVar2[-2]) {
            return 0;
          }
          if ((puVar2[-1] ^ puVar3[-1]) >> 0xe != 0) {
            return 0;
          }
          if ((*puVar2 ^ *puVar3) >> 0xe != 0) {
            return 0;
          }
          lVar1 = lVar1 + -1;
          puVar2 = puVar2 + 3;
          puVar3 = puVar3 + 3;
        } while (lVar1 != 0);
      }
      return 1;
}
/* FUN_00411308 @ 0x00411308 */
uint64_t FUN_00411308(int64_t p1, int64_t p2)
{
    uint64_t r1;
    uint64_t r2;
    uint64_t r3;
    uint64_t r4;
    uint64_t r5;
    uint64_t r6;
    int64_t lVar7;
    uint64_t * puVar8;
    uint64_t * puVar9;
      lVar7 = *(long *)(p1 + 0x10);
      if (lVar7 == *(long *)(p2 + 0x10)) {
        if ((lVar7 != 0) && (p1 != p2)) {
          puVar8 = (uint64_t *)(p1 + 0x38);
          puVar9 = (uint64_t *)(p2 + 0x38);
          do {
            r1 = puVar8[-1];
            r3 = *puVar8;
            r2 = puVar9[-1];
            r4 = *puVar9;
            if (puVar8[-3] == puVar9[-3] && puVar8[-2] == puVar9[-2]) {
              if ((r2 ^ r1) >> 0xe != 0) goto LAB_004113b8;
            }
            else {
              r5 = FUN_002a0cf8();
              if ((r5 & 1) == 0) {
                return 0;
              }
              if (0x3fff < (r2 ^ r1)) {
                return 0;
              }
            }
            if ((r4 ^ r3) >> 0xe != 0) goto LAB_004113b8;
            puVar8 = puVar8 + 4;
            puVar9 = puVar9 + 4;
            lVar7 = lVar7 + -1;
          } while (lVar7 != 0);
        }
        r6 = 1;
      }
      else {
    LAB_004113b8:
        r6 = 0;
      }
      return r6;
}
/* FUN_004113d4 @ 0x004113d4 */
uint64_t FUN_004113d4(int64_t p1, int64_t p2)
{
    int64_t lVar1;
    uint64_t * puVar2;
    uint64_t * puVar3;
      lVar1 = *(long *)(p1 + 0x10);
      if (lVar1 != *(long *)(p2 + 0x10)) {
        return 0;
      }
      if ((lVar1 != 0) && (p1 != p2)) {
        puVar2 = (uint64_t *)(p2 + 0x30);
        puVar3 = (uint64_t *)(p1 + 0x30);
        do {
          if ((int)puVar3[-2] != (int)puVar2[-2]) {
            return 0;
          }
          if ((puVar2[-1] ^ puVar3[-1]) >> 0xe != 0) {
            return 0;
          }
          if ((*puVar2 ^ *puVar3) >> 0xe != 0) {
            return 0;
          }
          lVar1 = lVar1 + -1;
          puVar2 = puVar2 + 3;
          puVar3 = puVar3 + 3;
        } while (lVar1 != 0);
      }
      return 1;
}
/* FUN_0041144c @ 0x0041144c */
uint32_t FUN_0041144c(int64_t p1, int64_t p2)
{
    uint32_t r1;
    int64_t lVar2;
    uint64_t r3;
    uint64_t r4;
    uint64_t * puVar5;
    uint64_t * puVar6;
      lVar2 = *(long *)(p1 + 0x10);
      if (lVar2 == *(long *)(p2 + 0x10)) {
        if ((lVar2 == 0) || (p1 == p2)) {
          r1 = 1;
        }
        else {
          puVar5 = (uint64_t *)(p1 + 0x20);
          puVar6 = (uint64_t *)(p2 + 0x20);
          do {
            lVar2 = lVar2 + -1;
            r3 = *puVar5;
            r4 = *puVar6;
            FUN_0036b270(r4 & 0xfffffffffffffff);
            FUN_0036b270(r3 & 0xfffffffffffffff);
            r1 = FUN_0041001c(r3,r4);
            FUN_0036b118(r3 & 0xfffffffffffffff);
            FUN_0036b118(r4 & 0xfffffffffffffff);
            if ((r1 & 1) == 0) break;
            puVar5 = puVar5 + 1;
            puVar6 = puVar6 + 1;
          } while (lVar2 != 0);
        }
      }
      else {
        r1 = 0;
      }
      return r1 & 1;
}
/* FUN_004114fc @ 0x004114fc */
uint32_t FUN_004114fc(int64_t p1, int64_t p2)
{
    uint64_t r1;
    uint64_t r2;
    uint64_t r3;
    uint64_t r4;
    uint8_t r5;
    uint8_t r6;
    uint32_t r7;
    int64_t lVar8;
    uint8_t * puVar9;
    uint64_t r10;
    uint64_t r11;
    uint8_t * puVar12;
      lVar8 = *(long *)(p1 + 0x10);
      if (lVar8 == *(long *)(p2 + 0x10)) {
        if ((lVar8 == 0) || (p1 == p2)) {
          r7 = 1;
        }
        else {
          puVar9 = (uint8_t *)(p1 + 0x38);
          puVar12 = (uint8_t *)(p2 + 0x38);
          do {
            lVar8 = lVar8 + -1;
            r1 = *(uint64_t *)(puVar9 + -0x10);
            r3 = *(uint64_t *)(puVar9 + -8);
            r10 = *(uint64_t *)(puVar9 + -0x18);
            r2 = *(uint64_t *)(puVar12 + -0x18);
            r4 = *(uint64_t *)(puVar12 + -0x10);
            r11 = *(uint64_t *)(puVar12 + -8);
            r5 = *puVar9;
            r6 = *puVar12;
            FUN_00460d94(r10,r1,r3,r5);
            FUN_00460d94(r2,r4,r11,r6);
            r7 = FUN_0041cf18(r10,r1,r3,r5,r2,r4,r11,r6);
            FUN_00458e80(r2,r4,r11,r6);
            FUN_00458e80(r10,r1,r3,r5);
            if ((r7 & 1) == 0) break;
            puVar9 = puVar9 + 0x20;
            puVar12 = puVar12 + 0x20;
          } while (lVar8 != 0);
        }
      }
      else {
        r7 = 0;
      }
      return r7 & 1;
}
/* FUN_00411624 @ 0x00411624 */
uint64_t FUN_00411624(int64_t p1, int64_t p2)
{
    uint64_t r1;
    uint64_t r2;
    uint64_t r3;
    uint64_t r4;
    uint64_t r5;
    uint64_t r6;
    uint64_t r7;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    char cVar12;
    char cVar13;
    uint64_t r14;
    uint64_t r15;
    uint64_t r16;
    int64_t lVar17;
    uint64_t * puVar18;
    uint64_t * puVar19;
    uint64_t s_b8;
    uint64_t s_b0;
    uint64_t s_a8;
    uint64_t s_a0;
    char s_98;
    uint64_t s_90;
    uint64_t s_88;
    uint64_t s_80;
    uint64_t s_78;
    char s_70;
      lVar17 = *(long *)(p1 + 0x10);
      if (lVar17 == *(long *)(p2 + 0x10)) {
        if ((lVar17 != 0) && (p1 != p2)) {
          puVar18 = (uint64_t *)(p2 + 0x38);
          puVar19 = (uint64_t *)(p1 + 0x38);
          do {
            if ((char)puVar19[-3] != (char)puVar18[-3]) goto LAB_004117f4;
            r15 = *puVar19;
            r6 = puVar19[1];
            r1 = puVar19[2];
            r7 = puVar19[3];
            r2 = puVar19[4];
            r8 = puVar19[5];
            cVar12 = (char)puVar19[6];
            r3 = *puVar18;
            r9 = puVar18[1];
            r4 = puVar18[2];
            r10 = puVar18[3];
            r5 = puVar18[4];
            r11 = puVar18[5];
            cVar13 = (char)puVar18[6];
            if (puVar19[-2] == puVar18[-2] && puVar19[-1] == puVar18[-1]) {
              if ((r3 ^ r15) >> 0xe != 0) goto LAB_004117f4;
            }
            else {
              r14 = FUN_002a0cf8();
              if ((r14 & 1) == 0) {
                return 0;
              }
              if (0x3fff < (r3 ^ r15)) {
                return 0;
              }
            }
            if ((r9 ^ r6) >> 0xe != 0) goto LAB_004117f4;
            if (cVar12 == -1) {
              if (cVar13 != -1) goto LAB_00411780;
            }
            else {
              if (cVar13 == -1) {
    LAB_00411780:
                FUN_00458eec(r4,r10,r5,r11,cVar13);
                FUN_00458eec(r1,r7,r2,r8,cVar12);
                FUN_00458f88(r1,r7,r2,r8,cVar12);
                FUN_00458f88(r4,r10,r5,r11,cVar13);
                goto LAB_004117f4;
              }
              s_b8 = r1;
              s_b0 = r7;
              s_a8 = r2;
              s_a0 = r8;
              s_98 = cVar12;
              s_90 = r4;
              s_88 = r10;
              s_80 = r5;
              s_78 = r11;
              s_70 = cVar13;
              r15 = FUN_0042d050(&s_b8,&s_90);
              if ((r15 & 1) == 0) goto LAB_004117f4;
            }
            puVar18 = puVar18 + 10;
            puVar19 = puVar19 + 10;
            lVar17 = lVar17 + -1;
          } while (lVar17 != 0);
        }
        r16 = 1;
      }
      else {
    LAB_004117f4:
        r16 = 0;
      }
      return r16;
}
/* FUN_00411818 @ 0x00411818 */
uint64_t FUN_00411818(int64_t p1, int64_t p2)
{
    uint64_t r1;
    uint64_t r2;
    uint64_t r3;
    uint64_t r4;
    uint64_t r5;
    uint64_t r6;
    uint64_t r7;
    uint64_t r8;
    uint64_t r9;
    int64_t lVar10;
    uint64_t * puVar11;
    uint64_t * puVar12;
    uint64_t r13;
      lVar10 = *(long *)(p1 + 0x10);
      if (lVar10 == *(long *)(p2 + 0x10)) {
        if ((lVar10 != 0) && (p1 != p2)) {
          puVar11 = (uint64_t *)(p1 + 0x48);
          puVar12 = (uint64_t *)(p2 + 0x28);
          do {
            r3 = puVar11[-3];
            r1 = puVar11[-2];
            r4 = puVar11[-1];
            r13 = *puVar11;
            r7 = *puVar12;
            r5 = puVar12[1];
            r2 = puVar12[2];
            r6 = puVar12[3];
            r9 = puVar12[4];
            if (puVar11[-4] == 0) {
              if (r7 != 0) {
                FUN_003a25d4(0);
                goto LAB_0041190c;
              }
    LAB_004118c4:
              if (r1 != r2 || r3 != r5) goto LAB_0041190c;
            }
            else {
              if (r7 == 0) goto LAB_0041190c;
              if (puVar11[-5] == puVar12[-1] && puVar11[-4] == r7) goto LAB_004118c4;
              r7 = FUN_002a0cf8();
              if ((r7 & 1) == 0) {
                return 0;
              }
              if (r1 != r2 || r3 != r5) {
                return 0;
              }
            }
            if ((r6 ^ r4) >> 0xe != 0) {
              return 0;
            }
            if ((r9 ^ r13) >> 0xe != 0) {
              return 0;
            }
            puVar11 = puVar11 + 7;
            puVar12 = puVar12 + 7;
            lVar10 = lVar10 + -1;
          } while (lVar10 != 0);
        }
        r8 = 1;
      }
      else {
    LAB_0041190c:
        r8 = 0;
      }
      return r8;
}
/* FUN_00411930 @ 0x00411930 */
uint64_t FUN_00411930(int64_t p1, int64_t p2)
{
    int64_t lVar1;
    uint64_t * puVar2;
    uint64_t * puVar3;
      lVar1 = *(long *)(p1 + 0x10);
      if (lVar1 != *(long *)(p2 + 0x10)) {
        return 0;
      }
      if ((lVar1 != 0) && (p1 != p2)) {
        puVar2 = (uint64_t *)(p2 + 0x28);
        puVar3 = (uint64_t *)(p1 + 0x28);
        do {
          if ((puVar2[-1] ^ puVar3[-1]) >> 0xe != 0) {
            return 0;
          }
          if ((*puVar2 ^ *puVar3) >> 0xe != 0) {
            return 0;
          }
          lVar1 = lVar1 + -1;
          puVar2 = puVar2 + 2;
          puVar3 = puVar3 + 2;
        } while (lVar1 != 0);
      }
      return 1;
}
/* FUN_00411994 @ 0x00411994 */
void FUN_00411994(uint64_t pad1)
{
      FUN_004662f4();
      FUN_004580b4();
      FUN_0007c1c4();
      FUN_00458720();
      return;
}
/* FUN_004119c0 @ 0x004119c0 */
void FUN_004119c0(uint64_t pad1)
{
    uint8_t s_68[72];
      FUN_003504d0();
      FUN_004080b0();
      FUN_00465938();
      FUN_004580b4();
      FUN_00458720(s_68);
      FUN_001a8564();
      return;
}
/* FUN_00411a54 @ 0x00411a54 */
wpair_t FUN_00411a54(uint64_t pad1)
{
    wpair_t pair1;
    code * extraout_x8 = 0;
    uint64_t extraout_x16 = 0;
      FUN_000f4ae8();
      FUN_00027724(extraout_x16);
      FUN_0046295c();
      (*extraout_x8)();
      FUN_000e72d4();
      FUN_003a25d4();
      FUN_00463e10();
      thunk_FUN_002acbb8();
      pair1.hi = 0xec0000003c6e6f69;
      pair1.lo = 0x74616e7265746c61;
      return pair1;
}
/* FUN_00411bfc @ 0x00411bfc */
void FUN_00411bfc(uint64_t pad1)
{
    int32_t iVar1;
    wpair_t pair2;
    uint8_t s_160[320];
      pair2 = FUN_00463f94();
      FUN_00117cc4(pair2.lo,pair2.hi,0x99);
      iVar1 = FUN_00458b6c(s_160);
      if (iVar1 == 0) {
        FUN_0001a1c8(s_160);
        FUN_004650f0();
      }
      else if (iVar1 == 1) {
        FUN_0001a1c8(s_160);
        pair2 = FUN_00463dec();
        FUN_00117cc4(pair2.lo,pair2.hi,0x88);
        FUN_0044b23c();
      }
      else {
        FUN_0001a1c8(s_160);
        pair2 = FUN_00463dec();
        FUN_00117cc4(pair2.lo,pair2.hi,0x98);
        FUN_0044b35c();
      }
      return;
}
/* FUN_00411d40 @ 0x00411d40 */
bool FUN_00411d40(uint64_t pad1)
{
    uint8_t in_CY;
    uint64_t r1;
    uint64_t r2;
    uint64_t in_x3;
    uint64_t in_x5;
    uint64_t reg_x21;
      r1 = FUN_00350980();
      FUN_0041144c(r1,in_x3);
      r2 = FUN_004644dc();
      return (r2 & 1) != 0 && (!(bool)in_CY && (in_x5 ^ reg_x21) < 0x4000);
}
/* FUN_00411dd8 @ 0x00411dd8 */
void FUN_00411dd8(uint64_t pad1)
{
      FUN_0035098c();
      FUN_004080b0();
      FUN_00464e40();
      FUN_004580b4();
      FUN_0046660c();
      FUN_00464eb0();
      FUN_001a8564();
      return;
}
/* FUN_00411ff4 @ 0x00411ff4 */
void FUN_00411ff4(uint64_t pad1)
{
    uint64_t extraout_x1 = 0;
      FUN_003504d0();
      thunk_FUN_0036b270(extraout_x1);
      FUN_0007c1c4();
      return;
}
/* FUN_0041202c @ 0x0041202c */
void FUN_0041202c(uint64_t pad1)
{
    uint64_t reg_x19;
    uint64_t reg_x20;
      FUN_00351da8();
      FUN_001b9084();
      thunk_FUN_002298d4(reg_x20 >> 0xe);
      thunk_FUN_002298d4(reg_x19 >> 0xe);
      return;
}
/* FUN_00412074 @ 0x00412074 */
void FUN_00412074(uint64_t pad1)
{
    uint8_t s_78[72];
      FUN_00077888();
      FUN_003509ec();
      FUN_004080b0();
      FUN_00077894(s_78);
      FUN_001b9084();
      FUN_0046660c();
      FUN_00464eb0();
      FUN_001a8564();
      return;
}
/* FUN_00412118 @ 0x00412118 */
wpair_t FUN_00412118(uint64_t pad1)
{
    wpair_t pair1;
    uint64_t extraout_x8 = 0;
    uint64_t extraout_x9 = 0;
    uint64_t s_38;
      FUN_0008409c();
      FUN_00100c04();
      FUN_002a4ab4(0x12);
      FUN_003a25d4(s_38);
      FUN_00465054();
      FUN_00084180();
      thunk_FUN_002acbb8();
      FUN_00463e10();
      thunk_FUN_002acbb8();
      pair1.hi = extraout_x9 & 0xffffffff | 0xef3c206e00000000;
      pair1.lo = extraout_x8;
      return pair1;
}
/* FUN_004121b0 @ 0x004121b0 */
void FUN_004121b0(uint64_t pad1)
{
    uint64_t extraout_x1 = 0;
    uint64_t reg_x19;
      FUN_004662f4();
      thunk_FUN_002298d4(extraout_x1 >> 0xe);
      thunk_FUN_002298d4(reg_x19 >> 0xe);
      return;
}
/* FUN_00412494 @ 0x00412494 */
void FUN_00412494(uint64_t pad1)
{
      FUN_00462d5c();
      FUN_004588cc();
      FUN_00462d5c();
      return;
}
/* FUN_004124cc @ 0x004124cc */
void FUN_004124cc(uint64_t pad1)
{
    uint64_t reg_x19;
    int64_t reg_x20;
    uint64_t reg_x21;
    uint64_t reg_x22;
    uint64_t reg_x23;
      FUN_00349a18();
      FUN_0010a9f8();
      FUN_00458940();
      *(uint64_t *)(reg_x20 + 0x10) = reg_x23;
      *(uint64_t *)(reg_x20 + 0x18) = reg_x22;
      *(uint64_t *)(reg_x20 + 0x20) = reg_x21;
      *(uint64_t *)(reg_x20 + 0x28) = reg_x19;
      return;
}
/* FUN_00412694 @ 0x00412694 */
wpair_t FUN_00412694(uint64_t pad1)
{
    wpair_t pair1;
    uint64_t r2;
    uint64_t extraout_x8 = 0;
    uint64_t r3;
    int64_t reg_x20;
    uint64_t s_28;
      FUN_00100c04();
      FUN_002a4ab4(0x12);
      FUN_003a25d4(s_28);
      FUN_00086840(s_absent_function_005dd080);
      r3 = 0xe800000000000000;
      r2 = 0x7265746165706572;
      switch(*(uint8_t *)(reg_x20 + 0x28) >> 1 & 3) {
      default:
        goto switchD_00412710_caseD_0;
      case 1:
        r3 = 0xea00000000006e6f;
        r2 = 0x6973736572707865;
        goto switchD_00412710_caseD_0;
      case 2:
        r2 = 0x6570706f7473;
        break;
      case 3:
        r2 = 0x657261656c63;
      }
      r3 = 0xe700000000000000;
      r2 = r2 | 0x72000000000000;
    switchD_00412710_caseD_0:
      FUN_00465c74(r2);
      FUN_003a25d4(r3);
      pair1.hi = extraout_x8;
      pair1.lo = 0xd000000000000010;
      return pair1;
}
/* FUN_00412788 @ 0x00412788 */
void FUN_00412788(uint64_t pad1)
{
      FUN_004632f4();
      thunk_FUN_00449d70();
      return;
}
/* FUN_004127b4 @ 0x004127b4 */
bool FUN_004127b4(uint64_t pad1)
{
    int64_t * reg_x20;
      if ((char)reg_x20[4] != '\0') {
        return false;
      }
      return (char)reg_x20[1] != '\x01' && *reg_x20 == 0;
}
/* FUN_0041288c @ 0x0041288c */
void FUN_0041288c(uint64_t pad1)
{
    uint64_t r1;
    uint64_t r2;
    uint64_t r3;
    uint64_t r4;
    uint64_t r5;
    uint64_t * reg_x20;
    wpair_t pair6;
      r1 = *reg_x20;
      r3 = reg_x20[1];
      r2 = reg_x20[2];
      r4 = reg_x20[3];
      if (*(char *)(reg_x20 + 4) == '\0') {
        r5 = 0;
      }
      else {
        if (*(char *)(reg_x20 + 4) != '\x01') {
          thunk_FUN_002298d4(2);
          pair6 = FUN_0007c1c4();
          FUN_001b9084(pair6.lo,pair6.hi,r3);
          return;
        }
        r5 = 1;
      }
      thunk_FUN_002298d4(r5);
      if ((r3 & 0xff) == 1) {
        FUN_00229a3c(0);
      }
      else {
        FUN_00229a3c(1);
        thunk_FUN_002298d4(r1);
      }
      thunk_FUN_002298d4(r2 >> 0xe);
      thunk_FUN_002298d4(r4 >> 0xe);
      return;
}
/* FUN_00412a58 @ 0x00412a58 */
uint64_t FUN_00412a58(uint64_t * p1, uint64_t * p2)
{
    uint32_t r1;
    uint64_t r2;
    char cVar3;
    uint8_t r4;
    uint64_t * puVar5;
    uint64_t r6;
    uint64_t r7;
    uint64_t r8;
    int64_t extraout_x8 = 0;
    int64_t extraout_x8_00 = 0;
    int64_t extraout_x10 = 0;
    int64_t extraout_x10_00 = 0;
    int64_t reg_x19;
    uint64_t * reg_x20;
      puVar5 = (uint64_t *)FUN_00350c5c();
      r6 = *puVar5;
      r7 = *reg_x20;
      r2 = reg_x20[1];
      cVar3 = (char)reg_x20[4];
      if (*(char *)(reg_x19 + 0x20) == '\0') {
        if (cVar3 != '\0') {
          return 0;
        }
      }
      else {
        if (*(char *)(reg_x19 + 0x20) != '\x01') {
          if (cVar3 != '\x02') {
            return 0;
          }
          if ((r6 != r7 || *(uint64_t *)(reg_x19 + 8) != r2) &&
             (r7 = FUN_002a0cf8(*(uint64_t *)(reg_x19 + 0x18)), (r7 & 1) == 0)) {
            return 0;
          }
          goto LAB_00412b04;
        }
        if (cVar3 != '\x01') {
          return 0;
        }
      }
      r1 = (uint32_t)r2 & 0xff;
      if ((*(uint64_t *)(reg_x19 + 8) & 0xff) == 1) {
        r4 = (r2 & 0xff) != 0;
        if (r1 != 1) {
          return 0;
        }
      }
      else {
        r4 = r1 != 1 && r7 <= r6;
        if (r1 == 1 || r6 != r7) {
          return 0;
        }
      }
      r8 = FUN_00465c44(0);
      if (extraout_x10 != 0) {
        return r8;
      }
      r8 = FUN_00465264();
      if ((bool)r4) {
        return r8;
      }
    LAB_00412b04:
      cVar3 = (char)reg_x20[9];
      if (*(char *)(reg_x19 + 0x48) == '\x01') {
        r4 = cVar3 != '\0';
        if (cVar3 != '\x01') {
          return 0;
        }
      }
      else {
        if (cVar3 == '\x01') {
          return 0;
        }
        r1 = (uint32_t)reg_x20[6] & 0xff;
        if (*(char *)(reg_x19 + 0x30) == '\x01') {
          r4 = (reg_x20[6] & 0xff) != 0;
          if (r1 != 1) {
            return 0;
          }
        }
        else {
          r4 = r1 != 1 && reg_x20[5] <= *(uint64_t *)(reg_x19 + 0x28);
          if (r1 == 1 || *(uint64_t *)(reg_x19 + 0x28) != reg_x20[5]) {
            return 0;
          }
        }
        r8 = FUN_00465c44(*(uint64_t *)(reg_x19 + 0x40),0);
        if (extraout_x10_00 != 0) {
          return r8;
        }
        r8 = FUN_00464d0c();
        if (extraout_x8_00 != 0) {
          return r8;
        }
      }
      FUN_00464d0c(*(uint64_t *)(reg_x19 + 0x50));
      if ((extraout_x8 == 0) && (FUN_00465264(reg_x20[0xb]), !(bool)r4)) {
        return 1;
      }
      return 0;
}
/* FUN_00412ce0 @ 0x00412ce0 */
uint64_t FUN_00412ce0(uint64_t pad1)
{
      FUN_0036b118();
      return 0;
}
/* FUN_00412ce4 @ 0x00412ce4 */
uint64_t FUN_00412ce4(uint64_t pad1)
{
      FUN_0036b118();
      return 0;
}
/* FUN_00412d5c @ 0x00412d5c */
void FUN_00412d5c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t pad5)
{
    code * pcVar1;
    bool bVar2;
      if (p3 >> 0xe <= p1 >> 0xe) {
        p1 = p3;
      }
      bVar2 = p4 >> 0xe <= p2 >> 0xe;
      if (bVar2) {
        p4 = p2;
      }
      FUN_004659bc(p1,p4);
      if (bVar2) {
        return;
      }

      pcVar1 = (code *)SoftwareBreakpoint(1,0x412d94);
      (*pcVar1)();
}
/* FUN_00412d98 @ 0x00412d98 */
void FUN_00412d98(uint64_t pad1)
{
    uint64_t r1;
    uint64_t r2;
    int64_t reg_x19;
    int64_t reg_x21;
    int64_t lVar3;
      FUN_004665bc();
      if (reg_x19 != 0) {
        lVar3 = reg_x21 + 0x28;
        do {
          r1 = *(uint64_t *)(lVar3 + 0x18);
          r2 = *(uint64_t *)(lVar3 + 0x20);
          FUN_0041b3d4();
          thunk_FUN_002298d4(r1 >> 0xe);
          thunk_FUN_002298d4(r2 >> 0xe);
          lVar3 = lVar3 + 0x30;
          reg_x19 = reg_x19 + -1;
        } while (reg_x19 != 0);
      }
      return;
}
/* FUN_00412e18 @ 0x00412e18 */
void FUN_00412e18(uint64_t pad1)
{
    code * reg_x19;
      FUN_003504d0();
      FUN_004080b0();
      FUN_00465938();
      (*reg_x19)();
      FUN_001a8564();
      return;
}
/* FUN_00412e8c @ 0x00412e8c */
int64_t FUN_00412e8c(uint64_t pad1)
{
    uint64_t r1;
    int64_t lVar2;
    int64_t reg_x20;
    uint8_t s_30[8];
    uint64_t s_28;
      FUN_004639fc();
      FUN_00359018();
      lVar2 = FUN_0036a940();
      r1 = DAT_004baeb0;
      *(uint64_t *)(lVar2 + 0x18) = uram_00000000004baeb8;
      *(uint64_t *)(lVar2 + 0x10) = r1;
      s_28 = *(uint64_t *)(reg_x20 + 0x68);
      *(uint64_t *)(lVar2 + 0x20) = s_28;
      FUN_00460dcc(&s_28,s_30);
      return lVar2;
}
/* FUN_00412eec @ 0x00412eec */
void * FUN_00412eec(uint64_t pad1)
{
    uint64_t r1;
    void * puVar2;
    uint64_t r3;
    int64_t reg_x20;
    uint64_t r4;
      r3 = *(uint64_t *)(reg_x20 + 0x10);
      r4 = *(uint64_t *)(reg_x20 + 0x28);
      puVar2 = &DAT_00657778;
      switch((uint32_t)r4 >> 1 & 3) {
      default:
        FUN_004639fc();
        FUN_00359018();
        puVar2 = (void *)FUN_0036a940();
        r1 = DAT_004baeb0;
        *(uint64_t *)(puVar2 + 0x18) = uram_00000000004baeb8;
        *(uint64_t *)(puVar2 + 0x10) = r1;
        *(uint64_t *)(puVar2 + 0x20) = r3;
        FUN_0009461c();
        FUN_00351e3c();
        FUN_004588cc();
        break;
      case 1:
        FUN_004639fc();
        FUN_00355538();
        puVar2 = (void *)FUN_0036a940();
        r1 = DAT_004c2450;
        *(uint64_t *)(puVar2 + 0x18) = uram_00000000004c2458;
        *(uint64_t *)(puVar2 + 0x10) = r1;
        *(uint64_t *)(puVar2 + 0x20) = r3;
        *(uint64_t *)(puVar2 + 0x28) = r4 & 0xfffffffffffffff9;
        FUN_0036b270(r4 & 0xffffffffffffff9);
        FUN_0036b270(r3 & 0xfffffffffffffff);
        break;
      case 3:
        break;
      }
      return puVar2;
}
/* FUN_00412fe4 @ 0x00412fe4 */
void FUN_00412fe4(uint64_t pad1)
{
    uint64_t r1;
    int64_t extraout_x8 = 0;
    uint64_t reg_x19;
    uint64_t reg_x20;
      r1 = FUN_00350a28();
      FUN_00117cc4(extraout_x8,r1,0x99);
      *(uint64_t *)(extraout_x8 + 0xa0) = reg_x20;
      *(uint64_t *)(extraout_x8 + 0xa8) = reg_x19;
      return;
}
/* FUN_00413024 @ 0x00413024 */
uint8_t FUN_00413024(wpair_t p1, wpair_t p2)
{
    uint64_t r1;
    char cVar2;
    uint8_t bVar3;
    uint8_t bVar4;
    uint8_t bVar5;
    uint8_t bVar6;
    uint8_t bVar7;
    int32_t iVar8;
    int32_t iVar9;
    uint64_t r10;
    uint64_t r11;
    char * pcVar12;
    int32_t * piVar13;
    uint64_t * puVar14;
    int64_t lVar15;
    int64_t * plVar16;
    uint64_t extraout_x1 = 0;
    uint64_t extraout_x1_00 = 0;
    uint64_t extraout_x1_01 = 0;
    uint64_t extraout_x1_02 = 0;
    uint64_t extraout_x1_03 = 0;
    uint64_t extraout_x16 = 0;
    int64_t reg_x20;
    int64_t reg_x21;
    uint64_t extraout_d0 = 0;
    uint64_t extraout_d0_00 = 0;
    uint64_t extraout_var = 0;
    uint64_t extraout_var_00 = 0;
    uint64_t r17;
    wpair_t pair18;
    uint8_t s_5b0[320];
    uint8_t s_470[48];
    uint64_t s_440;
    uint64_t s_438;
    uint64_t s_3d0;
    uint64_t s_3c8;
    uint64_t s_3c0;
    uint64_t s_3b8;
    uint64_t s_3b0;
    uint64_t s_3a8;
    uint64_t s_3a0;
    uint8_t s_330[160];
    uint64_t s_290;
    uint64_t s_288;
    uint64_t s_280;
    uint64_t s_278;
    uint8_t s_270;
    uint64_t s_260;
    uint64_t s_258;
    uint64_t s_250;
    uint64_t s_248;
    uint64_t s_240;
    uint64_t s_238;
    uint64_t s_230;
    uint64_t s_228;
    uint8_t s_1c0[160];
    uint64_t s_120;
    uint64_t s_118;
    uint64_t s_110;
    uint64_t s_108;
    uint64_t s_100;
    uint64_t s_f8;
    uint64_t s_f0;
    uint64_t s_e0;
    uint64_t s_d8;
    uint64_t s_d0;
    uint64_t s_c0;
    uint64_t s_b8;
    uint64_t s_b0;
      r17 = p2.hi;
      r10 = p2.lo;
      FUN_00356c6c();
      FUN_00117cc4(s_330,extraout_x1,0x99);
      FUN_004660e0(s_330);
      switch(extraout_x16) {
      default:
        FUN_004666cc(s_330);
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 0) {
    LAB_004134a4:
          plVar16 = (long *)FUN_00458b14(s_1c0);
          if (reg_x20 != *plVar16 || reg_x21 != plVar16[1]) {
            FUN_0006b6f4();
            bVar7 = FUN_002a0cf8();
            goto LAB_004135a8;
          }
    LAB_0041359c:
          bVar7 = 1;
          goto LAB_004135a8;
        }
        break;
      case 1:
        piVar13 = (int *)FUN_00458b14(s_330);
        iVar8 = *piVar13;
        r11 = *(uint64_t *)(piVar13 + 2);
        r1 = *(uint64_t *)(piVar13 + 4);
        FUN_00463718();
        iVar9 = FUN_00458af8(s_1c0);
        if ((((iVar9 == 1) && (piVar13 = (int *)FUN_00458b14(s_1c0), iVar8 == *piVar13)) &&
            ((*(uint64_t *)(piVar13 + 2) ^ r11) >> 0xe == 0)) &&
           ((*(uint64_t *)(piVar13 + 4) ^ r1) < 0x4000)) goto LAB_0041359c;
        break;
      case 2:
        puVar14 = (uint64_t *)FUN_00458b14(s_330);
        r10 = *puVar14;
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 2) {
          puVar14 = (uint64_t *)FUN_00458b14(s_1c0);
          r11 = FUN_004113d4(r10,*puVar14);
          if ((r11 & 1) != 0) {
            FUN_0007c1c4();
            r11 = FUN_00411308(0, 0);
            goto joined_r0x00413540;
          }
        }
        break;
      case 3:
        puVar14 = (uint64_t *)FUN_00458b14(s_330);
        s_288 = puVar14[1];
        s_290 = *puVar14;
        s_278 = puVar14[3];
        s_280 = puVar14[2];
        s_270 = *(uint8_t *)(puVar14 + 4);
        bVar7 = *(uint8_t *)((long)puVar14 + 0x21);
        bVar3 = *(uint8_t *)((long)puVar14 + 0x22);
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 3) {
          puVar14 = (uint64_t *)FUN_00458b14(s_1c0);
          s_258 = puVar14[1];
          s_260 = *puVar14;
          s_248 = puVar14[3];
          s_250 = puVar14[2];
          s_240 = (s_240 & ~0xFFull) | (uint8_t)(*(uint8_t *)(puVar14 + 4));
          bVar4 = *(uint8_t *)((long)puVar14 + 0x21);
          bVar5 = *(uint8_t *)((long)puVar14 + 0x22);
          bVar6 = FUN_00414dec(&s_290,&s_260);
          bVar7 = (bVar6 ^ 1 | bVar7 ^ bVar4 | bVar3 ^ bVar5) ^ 1;
          goto LAB_004135a8;
        }
        break;
      case 4:
        pcVar12 = (char *)FUN_00458b14(s_330);
        cVar2 = *pcVar12;
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 4) {
          pcVar12 = (char *)FUN_00458b14(s_1c0);
          bVar7 = cVar2 == *pcVar12;
          goto LAB_004135a8;
        }
        break;
      case 5:
        FUN_004666cc(s_330);
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 5) goto LAB_004134a4;
        break;
      case 6:
        FUN_004666cc(s_330);
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 6) goto LAB_004134a4;
        break;
      case 7:
        FUN_004666cc(s_330);
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 7) goto LAB_004134a4;
        break;
      case 8:
        FUN_004666cc(s_330);
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 8) goto LAB_004134a4;
        break;
      case 9:
        FUN_00464de4(s_330);
        FUN_00117cc4(&s_260,extraout_x1_01,0x60);
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 9) {
    LAB_00413464:
          FUN_00464de4(s_1c0);
          FUN_00117cc4(s_470,extraout_x1_03,0x60);
          bVar7 = FUN_00412a58(&s_260,s_470);
          goto LAB_004135a8;
        }
        break;
      case 10:
        FUN_00464de4(s_330);
        FUN_00117cc4(&s_260,extraout_x1_02,0x60);
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 10) goto LAB_00413464;
        break;
      case 0xb:
        FUN_00464de4(s_330);
        FUN_00117cc4(&s_260,extraout_x1_00,0x99);
        FUN_00464d00(s_5b0);
        iVar8 = FUN_00458af8(s_5b0);
        if (iVar8 == 0xb) {
          FUN_00458b14(s_5b0);
          pair18 = FUN_00463dec();
          FUN_00117cc4(pair18.lo,pair18.hi,0x99);
          FUN_00117cc4(s_1c0,&s_260,0x99);
          iVar8 = FUN_00458b6c(s_1c0);
          if (iVar8 == 0) {
            lVar15 = FUN_00465aa0(s_1c0);
            s_f8 = *(uint64_t *)(lVar15 + 0x28);
            s_100 = *(uint64_t *)(lVar15 + 0x20);
            s_f0 = *(uint64_t *)(lVar15 + 0x30);
            s_120 = extraout_d0;
            s_118 = extraout_var;
            s_110 = r10;
            s_108 = r17;
            FUN_00465a40();
            iVar8 = FUN_00458b6c(s_470);
            if (iVar8 == 0) {
              lVar15 = FUN_00465aa0(s_470);
              s_b8 = *(uint64_t *)(lVar15 + 0x28);
              s_c0 = *(uint64_t *)(lVar15 + 0x20);
              s_b0 = *(uint64_t *)(lVar15 + 0x30);
              s_3c8 = s_118;
              s_3d0 = s_120;
              s_3b8 = s_108;
              s_3c0 = s_110;
              s_3a8 = s_f8;
              s_3b0 = s_100;
              s_3a0 = s_f0;
              s_e0 = extraout_d0_00;
              s_d8 = extraout_var_00;
              s_d0 = r10;
              r11 = FUN_00449034(&s_3d0,&s_e0);
              goto joined_r0x00413540;
            }
          }
          else if (iVar8 == 1) {
            r10 = FUN_0001a1c8(s_1c0);
            FUN_00117cc4(&s_e0,r10,0x88);
            FUN_00465a40();
            iVar8 = FUN_00458b6c(s_470);
            if (iVar8 == 1) {
              r10 = FUN_0001a1c8(s_470);
              FUN_00117cc4(&s_3d0,r10,0x88);
              r11 = FUN_004165ec(&s_e0,&s_3d0);
    joined_r0x00413540:
              if ((r11 & 1) != 0) goto LAB_0041359c;
            }
          }
          else {
            r10 = FUN_0001a1c8(s_1c0);
            FUN_00117cc4(&s_e0,r10,0x98);
            FUN_00465a40();
            iVar8 = FUN_00458b6c(s_470);
            if (iVar8 == 2) {
              r10 = FUN_0001a1c8(s_470);
              FUN_00117cc4(&s_3d0,r10,0x98);
              r11 = FUN_00416ad0(&s_e0,&s_3d0);
              goto joined_r0x00413540;
            }
          }
        }
        break;
      case 0xc:
        puVar14 = (uint64_t *)FUN_00458b14(s_330);
        s_258 = puVar14[1];
        s_260 = *puVar14;
        s_248 = puVar14[3];
        s_250 = puVar14[2];
        s_238 = puVar14[5];
        s_240 = puVar14[4];
        s_230 = puVar14[6];
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 0xc) {
          FUN_00458b14(s_1c0);
          lVar15 = FUN_00464fc4();
          s_440 = *(uint64_t *)(lVar15 + 0x30);
          bVar7 = FUN_00417454(&s_260,s_470);
          goto LAB_004135a8;
        }
        break;
      case 0xd:
        puVar14 = (uint64_t *)FUN_00458b14(s_330);
        s_258 = puVar14[1];
        s_260 = *puVar14;
        s_248 = puVar14[3];
        s_250 = puVar14[2];
        s_238 = puVar14[5];
        s_240 = puVar14[4];
        s_228 = puVar14[7];
        s_230 = puVar14[6];
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 0xd) {
          FUN_00458b14(s_1c0);
          lVar15 = FUN_00464fc4();
          s_438 = *(uint64_t *)(lVar15 + 0x38);
          s_440 = *(uint64_t *)(lVar15 + 0x30);
          bVar7 = FUN_0041ae14(&s_260,s_470);
          goto LAB_004135a8;
        }
        break;
      case 0xe:
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 0xe) goto LAB_0041359c;
        break;
      case 0xf:
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 0xf) goto LAB_0041359c;
        break;
      case 0x10:
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 0x10) goto LAB_0041359c;
        break;
      case 0x11:
        FUN_00463718();
        iVar8 = FUN_00458af8(s_1c0);
        if (iVar8 == 0x11) goto LAB_0041359c;
      }
      bVar7 = 0;
    LAB_004135a8:
      return bVar7 & 1;
}
/* FUN_0041360c @ 0x0041360c */
void FUN_0041360c(uint64_t * p1, uint64_t p2)
{
    uint64_t r1;
    uint64_t r2;
    uint32_t r3;
    uint8_t bVar4;
    uint8_t bVar5;
    uint8_t r6;
    int32_t iVar7;
    uint64_t r8;
    uint8_t * puVar9;
    uint64_t r10;
    uint32_t * puVar11;
    int64_t lVar12;
    uint64_t r13;
    uint64_t extraout_x1 = 0;
    uint64_t extraout_x16 = 0;
    uint64_t extraout_d0 = 0;
    uint64_t extraout_d0_00 = 0;
    uint64_t extraout_d0_01 = 0;
    uint64_t extraout_var = 0;
    uint64_t extraout_var_00 = 0;
    uint64_t extraout_var_01 = 0;
    wpair_t pair14;
    uint8_t s_1e0[160];
    uint64_t s_140;
    uint64_t s_138;
    uint64_t s_130;
    uint64_t s_128;
    uint64_t s_120;
    uint64_t s_118;
    uint64_t s_110;
    uint64_t s_108;
    uint64_t s_a0;
    uint64_t s_98;
    uint64_t s_90;
    uint64_t s_80;
      FUN_0008e518();
      pair14 = FUN_004648ec();
      FUN_00117cc4(pair14.lo,pair14.hi,0x99);
      FUN_004660e0(s_1e0);
      switch(extraout_x16) {
      default:
        FUN_00465818(s_1e0);
        r8 = 0;
        break;
      case 1:
        puVar11 = (uint32_t *)FUN_00458b14(s_1e0);
        r3 = *puVar11;
        r13 = *(uint64_t *)(puVar11 + 2);
        r10 = *(uint64_t *)(puVar11 + 4);
        FUN_00464e1c();
        thunk_FUN_002298d4();
        FUN_0022995c(r3);
        thunk_FUN_002298d4(r13 >> 0xe);
        r10 = r10 >> 0xe;
        goto LAB_00413920;
      case 2:
        FUN_00465818(s_1e0);
        FUN_00465b58();
        FUN_003507e0();
        FUN_00458190();
        FUN_003504ac();
        FUN_0045811c();
        goto LAB_00413924;
      case 3:
        lVar12 = FUN_00465b04(s_1e0);
        s_128 = *(uint64_t *)(lVar12 + 0x18);
        s_130 = *(uint64_t *)(lVar12 + 0x10);
        s_120 = (s_120 & ~0xFFull) | (uint8_t)(*(uint8_t *)(lVar12 + 0x20));
        bVar4 = *(uint8_t *)(lVar12 + 0x21);
        bVar5 = *(uint8_t *)(lVar12 + 0x22);
        s_140 = extraout_d0;
        s_138 = extraout_var;
        thunk_FUN_002298d4(3);
        FUN_00465110();
        FUN_004150e8(0);
        FUN_00229a3c(bVar4 & 1);
        r13 = (uint64_t)(bVar5 & 1);
    LAB_004138e8:
        FUN_00229a3c(r13);
        goto LAB_00413924;
      case 4:
        puVar9 = (uint8_t *)FUN_00458b14(s_1e0);
        r6 = *puVar9;
        thunk_FUN_002298d4(4);
        goto LAB_00413834;
      case 5:
        FUN_00465818(s_1e0);
        r8 = 5;
        break;
      case 6:
        FUN_00465818(s_1e0);
        r8 = 6;
        break;
      case 7:
        FUN_00465818(s_1e0);
        r8 = 7;
        break;
      case 8:
        FUN_00465818(s_1e0);
        r8 = 8;
        break;
      case 9:
        FUN_00458b14(s_1e0);
        pair14 = FUN_00463dec();
        FUN_00117cc4(pair14.lo,pair14.hi,0x60);
        r8 = 0xc;
        goto LAB_004138b0;
      case 10:
        FUN_00458b14(s_1e0);
        pair14 = FUN_00463dec();
        FUN_00117cc4(pair14.lo,pair14.hi,0x60);
        r8 = 0xd;
    LAB_004138b0:
        thunk_FUN_002298d4(r8);
        FUN_00465110();
        FUN_00412bb0(0);
        goto LAB_00413924;
      case 0xb:
        FUN_00458b14(s_1e0);
        pair14 = FUN_00463dec();
        FUN_00117cc4(pair14.lo,pair14.hi,0x99);
        thunk_FUN_002298d4(0xe);
        iVar7 = FUN_00458b6c(&s_140);
        if (iVar7 != 0) {
          if (iVar7 == 1) {
            r8 = FUN_0001a1c8(&s_140);
            FUN_00117cc4(&s_a0,r8,0x88);
            FUN_00464e1c();
            thunk_FUN_002298d4();
            FUN_0041680c();
          }
          else {
            r8 = FUN_0001a1c8(&s_140);
            FUN_00117cc4(&s_a0,r8,0x98);
            FUN_00465b58();
            FUN_00416cfc();
          }
          goto LAB_00413924;
        }
        lVar12 = FUN_00465aa0(&s_140);
        s_80 = *(uint64_t *)(lVar12 + 0x20);
        r10 = *(uint64_t *)(lVar12 + 0x30);
        s_a0 = extraout_d0_01;
        s_98 = extraout_var_01;
        s_90 = p2;
        FUN_004666b4();
        FUN_00415f84();
        FUN_0046666c();
        r10 = r10 >> 0xe;
        goto LAB_00413920;
      case 0xc:
        puVar9 = (uint8_t *)FUN_00458b14(s_1e0);
        r6 = *puVar9;
        r13 = *(uint64_t *)(puVar9 + 8);
        r2 = *(uint64_t *)(puVar9 + 0x10);
        lVar12 = *(long *)(puVar9 + 0x20);
        r1 = *(uint64_t *)(puVar9 + 0x28);
        r10 = *(uint64_t *)(puVar9 + 0x30);
        thunk_FUN_002298d4(0xf);
        thunk_FUN_002298d4(r6);
        thunk_FUN_002298d4(r13 >> 0xe);
        thunk_FUN_002298d4(r2 >> 0xe);
        if (lVar12 == 0) {
          r13 = FUN_00464ac4();
          goto LAB_004138e8;
        }
        FUN_00465584();
        FUN_00462e0c();
        FUN_001b9084();
        thunk_FUN_002298d4(r1 >> 0xe);
        r10 = r10 >> 0xe;
    LAB_00413920:
        thunk_FUN_002298d4(r10);
        goto LAB_00413924;
      case 0xd:
        lVar12 = FUN_00465b04(s_1e0);
        s_128 = *(uint64_t *)(lVar12 + 0x18);
        s_130 = *(uint64_t *)(lVar12 + 0x10);
        s_118 = *(uint64_t *)(lVar12 + 0x28);
        s_120 = *(uint64_t *)(lVar12 + 0x20);
        s_108 = *(uint64_t *)(lVar12 + 0x38);
        s_110 = *(uint64_t *)(lVar12 + 0x30);
        s_140 = extraout_d0_00;
        s_138 = extraout_var_00;
        thunk_FUN_002298d4(0x10);
        FUN_00465110();
        FUN_0041aee4();
        goto LAB_00413924;
      case 0xe:
        r6 = 9;
        goto LAB_00413834;
      case 0xf:
        r6 = 10;
        goto LAB_00413834;
      case 0x10:
        r6 = 0xb;
        goto LAB_00413834;
      case 0x11:
        r6 = 0x11;
    LAB_00413834:
        thunk_FUN_002298d4(r6);
        goto LAB_00413924;
      }
      thunk_FUN_002298d4(r8);
      FUN_00462e0c();
      FUN_001b9084();
    LAB_00413924:
      FUN_0008e500(extraout_x1);
      return;
}
/* FUN_004139b0 @ 0x004139b0 */
void FUN_004139b0(uint64_t pad1)
{
    uint8_t s_68[72];
      FUN_004080b0();
      FUN_0041360c(s_68, 0);
      FUN_001a8564();
      return;
}
/* FUN_00413a0c @ 0x00413a0c */
uint64_t FUN_00413a0c(uint64_t pad1)
{
    uint8_t in_CY;
    uint64_t r1;
    uint64_t r2;
    int64_t extraout_x8 = 0;
    int64_t reg_x19;
    int64_t reg_x20;
      FUN_00350c5c();
      r1 = FUN_00413024((wpair_t){0,0}, (wpair_t){0,0});
      if ((((r1 & 1) == 0) || ((extraout_x8 = (FUN_00464d0c(*(uint64_t *)(reg_x19 + 0xa0))) ) != 0)) ||
         (FUN_00465264(*(uint64_t *)(reg_x20 + 0xa8)), (bool)in_CY)) {
        r2 = 0;
      }
      else {
        r2 = 1;
      }
      return r2;
}
/* FUN_00413aa0 @ 0x00413aa0 */
void FUN_00413aa0(uint64_t pad1)
{
    int64_t reg_x20;
    uint8_t s_68[72];
      FUN_004080b0();
      FUN_0041360c(s_68, 0);
      FUN_00465234(*(uint64_t *)(reg_x20 + 0xa0));
      FUN_00464eb0();
      FUN_001a8564();
      return;
}
/* FUN_00413b2c @ 0x00413b2c */
void FUN_00413b2c(uint64_t pad1)
{
    uint8_t s_d0[176];
      FUN_00117cc4(s_d0);
      FUN_00413b68(0);
      return;
}
/* FUN_00413b68 @ 0x00413b68 */
wpair_t FUN_00413b68(uint64_t pad1)
{
    int64_t lVar1;
    uint64_t r2;
    int64_t lVar3;
    int64_t lVar4;
    uint32_t r5;
    int32_t iVar6;
    uint64_t r7;
    int64_t lVar8;
    int64_t * plVar9;
    int64_t extraout_x1 = 0;
    uint64_t extraout_x1_00 = 0;
    uint64_t extraout_x1_01 = 0;
    uint64_t extraout_x1_02 = 0;
    uint64_t r10;
    uint64_t r11;
    uint64_t in_x5;
    uint32_t r12;
    uint32_t extraout_w8 = 0;
    uint64_t extraout_x8 = 0;
    int64_t extraout_x8_00 = 0;
    int64_t extraout_x8_01 = 0;
    int32_t extraout_w9 = 0;
    int64_t extraout_x9 = 0;
    int32_t extraout_w11 = 0;
    int64_t reg_x20;
    int64_t lVar13;
    uint32_t * puVar14;
    int64_t extraout_d0 = 0;
    int64_t extraout_d0_00 = 0;
    int64_t extraout_d0_01 = 0;
    uint64_t extraout_var = 0;
    uint64_t extraout_var_00 = 0;
    uint64_t extraout_var_01 = 0;
    wpair_t pair15;
    int64_t s_300;
    uint64_t s_2f8;
    uint8_t s_250[96];
    int64_t s_1f0;
    int64_t lStack_1e8;
    int64_t s_1e0;
    int64_t lStack_1d8;
    int64_t s_1d0;
    int64_t lStack_1c8;
    int64_t s_1c0;
    uint8_t s_150[160];
    int64_t s_b0;
    uint64_t s_a8;
    uint64_t s_a0;
    uint64_t s_98;
    uint32_t s_91;
    uint64_t s_8d;
    uint64_t s_88;
    uint64_t s_80;
    int64_t lStack_78;
    uint64_t s_10[2];
      r7 = FUN_0008e518().lo;
      FUN_00417b60();
      if (extraout_x1 != 0) {
        s_300 = 0xa2bdef;
        s_2f8 = 0xa300000000000000;
        thunk_FUN_002acbb8();
        thunk_FUN_002acbb8(0xa3bdef,0xa300000000000000);
        lVar8 = extraout_x1;
    LAB_00413bc0:
        FUN_003a25d4(lVar8);
        goto switchD_00413c1c_caseD_e;
      }
      FUN_00464d00(s_150);
      r5 = FUN_00458af8(s_150);
      switch(r5) {
      default:
        FUN_00458b14(s_150);
        r7 = FUN_0046565c(0xae);
        r10 = 0x6168636165726e55;
        r11 = 0xeb00000000656c62;
        goto LAB_004140c0;
      case 2:
        plVar9 = (long *)FUN_00458b14(s_150);
        lVar8 = *plVar9;
        lVar3 = plVar9[1];
        lVar13 = *(long *)(lVar8 + 0x10);
        s_b0 = lVar8;
        if (lVar13 == 0) {
          FUN_00465270();
          FUN_004642d4();
          FUN_00461cb8(&s_b0);
          s_300 = lVar3;
          FUN_004642c0();
          FUN_00461cb8(&s_300);
          FUN_000a6fe0();
          s_1f0 = reg_x20;
        }
        else {
          FUN_00465270();
          FUN_000a6f68();
          s_1f0 = extraout_x8_00;
          FUN_004651a8();
          puVar14 = (uint32_t *)(lVar8 + 0x20);
          do {
            r12 = *puVar14;
            s_300 = 0xa2bdef;
            s_2f8 = 0xa300000000000000;
            if (r12 < 0x80) {
              r12 = r12 + 1;
            }
            else if (r12 < 0x800) {
              r12 = (r12 >> 6) + (r12 & 0x3f) * 0x100 + 0x81c1;
            }
            else {
              FUN_00463bd4();
              r12 = extraout_w8;
              if (extraout_w11 == 0) {
                r12 = extraout_w9 + 0x8181e1;
              }
            }
            s_10[0] = (uint64_t)r12 + 0xfefefefefefeff &
                          (-1L << (((uint64_t)(4 - ((uint32_t)LZCOUNT(r12) >> 3)) & 7) << 3) ^
                          0xffffffffffffffffU);
            FUN_00294cb4(s_10);
            thunk_FUN_002acbb8();
            FUN_003a25d4(extraout_x1_02);
            thunk_FUN_002acbb8(0xa3bdef,0xa300000000000000);
            r10 = s_2f8;
            lVar4 = s_300;
            r2 = *(uint64_t *)(s_1f0 + 0x10);
            lVar8 = r2 + 1;
            if (*(uint64_t *)(s_1f0 + 0x18) >> 1 <= r2) {
              FUN_00464000(1 < *(uint64_t *)(s_1f0 + 0x18));
              FUN_0006a374();
            }
            *(long *)(s_1f0 + 0x10) = lVar8;
            lVar1 = s_1f0 + r2 * 0x10;
            *(long *)(lVar1 + 0x20) = lVar4;
            *(uint64_t *)(lVar1 + 0x28) = r10;
            lVar13 = lVar13 + -1;
            puVar14 = puVar14 + 6;
          } while (lVar13 != 0);
          FUN_004642d4();
          FUN_00461cb8(&s_b0);
          s_300 = lVar3;
          FUN_004642c0();
          FUN_00461cb8(&s_300);
        }
        FUN_00463210();
        r10 = FUN_00462898();
        FUN_001bc440(0,0xe000000000000000,lVar8,r10);
        FUN_0034bd90();
        FUN_0036b118();
        break;
      case 3:
        lVar8 = FUN_00465b04(s_150);
        s_a0 = *(uint64_t *)(lVar8 + 0x10);
        s_98 = (uint64_t)*(uint64_t *)(lVar8 + 0x18);
        s_91 = *(uint32_t *)(lVar8 + 0x1f);
        s_b0 = extraout_d0_01;
        s_a8 = extraout_var_01;
        FUN_00465270();
        FUN_00414bf4(0);
        goto LAB_00414050;
      case 4:
        FUN_00458b14(s_150);
        FUN_00465674();
        s_2f8 = 0xe100000000000000;
        s_300 = extraout_x8_01;
        r10 = FUN_00414644(0).lo;
        thunk_FUN_002acbb8(r10,0xe100000000000000);
        lVar8 = -0x1f00000000000000;
        goto LAB_00413bc0;
      case 5:
      case 6:
      case 7:
        FUN_00458b14(s_150);
        r7 = FUN_0046565c(0x9a);
        r10 = 0x4f444f54;
        r11 = 0xe400000000000000;
    LAB_004140c0:

        FUN_001afa84(r7,0xb,2,r10,r11,in_x5,0x1a,2);
      case 8:
        FUN_00465818(s_150);
        s_b0 = 0x7b4e5c;
        s_a8 = 0xe300000000000000;
        FUN_00465270();
        FUN_000b4390();
        thunk_FUN_002acbb8();
        FUN_004589f8();
        FUN_00463878();
        thunk_FUN_002acbb8();
        break;
      case 9:
      case 10:
        FUN_00464de4(s_150);
        FUN_00117cc4(s_250,extraout_x1_00,0x60);
        FUN_00465270();
        FUN_0044ae70();
        goto LAB_00414050;
      case 0xb:
        FUN_00464de4(s_150);
        FUN_00117cc4(&s_b0,extraout_x1_01,0x99);
        iVar6 = FUN_00458b6c(&s_b0);
        if (iVar6 == 0) {
          plVar9 = (long *)FUN_0001a1c8(&s_b0);
          lStack_1e8 = plVar9[1];
          s_1f0 = *plVar9;
          lStack_1d8 = plVar9[3];
          s_1e0 = plVar9[2];
          lStack_1c8 = plVar9[5];
          s_1d0 = plVar9[4];
          s_1c0 = plVar9[6];
          FUN_00465270();
          FUN_0044b000();
        }
        else if (iVar6 == 1) {
          r10 = FUN_0001a1c8(&s_b0);
          FUN_00117cc4(&s_1f0,r10,0x88);
          FUN_00465270();
          FUN_0044b23c();
        }
        else {
          r10 = FUN_0001a1c8(&s_b0);
          FUN_00117cc4(&s_1f0,r10,0x98);
          FUN_00465270();
          FUN_0044b35c();
        }
        goto LAB_00414050;
      case 0xc:
        lVar8 = FUN_00465b04(s_150);
        s_a0 = *(uint64_t *)(lVar8 + 0x10);
        s_98 = (uint64_t)*(uint64_t *)(lVar8 + 0x18);
        *(uint8_t *)&s_91 = (uint8_t)((uint64_t)*(uint64_t *)(lVar8 + 0x18) >> 0x38);
        s_88 = *(uint64_t *)(lVar8 + 0x28);
        __builtin_memcpy((uint8_t *)&s_91+1,(uint32_t[]){ (uint32_t)(*(uint64_t *)(lVar8 + 0x20)) },3);
        s_8d = (uint64_t)((uint64_t)*(uint64_t *)(lVar8 + 0x20) >> 0x18);
        s_80 = *(uint64_t *)(lVar8 + 0x30);
        s_b0 = extraout_d0_00;
        s_a8 = extraout_var_00;
        FUN_00465270();
        FUN_0044c444();
    LAB_00414050:
        FUN_0034bd90();
        FUN_004589f8();
        break;
      case 0xd:
        lVar8 = FUN_00465b04(s_150);
        s_a0 = *(uint64_t *)(lVar8 + 0x10);
        r2 = *(uint64_t *)(lVar8 + 0x18);
        s_88 = *(uint64_t *)(lVar8 + 0x28);
        __builtin_memcpy((uint8_t *)&s_91+1,(uint32_t[]){ (uint32_t)(*(uint64_t *)(lVar8 + 0x20)) },3);
        s_8d = (uint64_t)((uint64_t)*(uint64_t *)(lVar8 + 0x20) >> 0x18);
        s_80 = *(uint64_t *)(lVar8 + 0x30);
        lVar8 = *(long *)(lVar8 + 0x38);
        s_98 = (uint64_t)r2;
        *(uint8_t *)&s_91 = (uint8_t)(r2 >> 0x38);
        s_1f0 = 0;
        lStack_1e8 = -0x2000000000000000;
        s_b0 = extraout_d0;
        s_a8 = extraout_var;
        lStack_78 = lVar8;
        FUN_00465270();
        FUN_002a4ab4(0x19);
        FUN_003a25d4(lStack_1e8);
        FUN_00462adc(s_changeMatchingOptions__005dd0c0);
        s_300 = extraout_x9;
        s_2f8 = extraout_x8;
        FUN_0041b088();
        FUN_0006b674();
        s_10[0] = r2;
        FUN_00461cb8(s_10,0x6579d0,&DAT_005a19a8);
        s_1f0 = lVar8;
        FUN_00461cb8(&s_1f0,0x6579d0,&DAT_005a19a8);
        FUN_003507e0();
        thunk_FUN_002acbb8();
        FUN_003a25d4(0xe100000000000000);
        FUN_00463e10();
        thunk_FUN_002acbb8();
        break;
      case 0xe:
        break;
      case 0xf:
        break;
      case 0x10:
        break;
      case 0x11:
      }
    switchD_00413c1c_caseD_e:
      pair15 = FUN_0006b6f4();
      FUN_0008e500(0,0,0); return pair15;
}
/* FUN_00414118 @ 0x00414118 */
void FUN_00414118(uint64_t pad1)
{
    wpair_t pair1;
      pair1 = FUN_00463f94();
      FUN_00117cc4(pair1.lo,pair1.hi,0xb0);
      thunk_FUN_00413b68();
      return;
}
/* FUN_00414154 @ 0x00414154 */
bool FUN_00414154(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, int64_t p5, uint32_t p6, uint64_t p7, uint64_t p8)
{
    uint8_t in_ZR;
    int64_t lVar1;
      lVar1 = FUN_00351db4();
      if ((bool)in_ZR) {
        if ((p6 & 0xff) != 1) {
          return false;
        }
      }
      else if ((p6 & 0xff) == 1 || lVar1 != p5) {
        return false;
      }
      return (p7 ^ p3) < 0x4000 && (p8 ^ p4) < 0x4000;
}
/* FUN_004141ac @ 0x004141ac */
void FUN_004141ac(uint8_t * p1, uint64_t p2, uint64_t p3, uint64_t pad4, uint64_t pad5)
{
    uint8_t in_ZR;
    uint64_t extraout_x1 = 0;
    uint64_t in_x3;
    uint64_t in_x4;
      FUN_0035292c();
      if ((bool)in_ZR) {
        FUN_00229a3c(0);
      }
      else {
        FUN_00229a3c(1);
        thunk_FUN_002298d4(extraout_x1);
      }
      thunk_FUN_002298d4(in_x3 >> 0xe);
      thunk_FUN_002298d4(in_x4 >> 0xe);
      return;
}
/* FUN_00414214 @ 0x00414214 */
void FUN_00414214(uint64_t pad1)
{
    wpair_t pair1;
    uint8_t s_78[72];
      pair1 = FUN_00077888();
      FUN_004080b0();
      FUN_004141ac(s_78,pair1.lo,pair1.hi, 0, 0);
      FUN_001a8564();
      return;
}
/* FUN_00414290 @ 0x00414290 */
void FUN_00414290(uint64_t pad1)
{
    uint64_t r1;
    uint64_t r2;
    uint8_t r3;
    uint64_t r4;
    uint64_t * reg_x20;
    uint8_t s_78[72];
      r4 = *reg_x20;
      r1 = reg_x20[2];
      r2 = reg_x20[3];
      r3 = *(uint8_t *)(reg_x20 + 1);
      FUN_001a84f4(s_78);
      FUN_004141ac(s_78,r4,r3,r1,r2);
      FUN_001a8564();
      return;
}
/* FUN_00414334 @ 0x00414334 */
void FUN_00414334(uint8_t * p1, uint64_t p2, uint64_t p3, uint64_t p4)
{
      FUN_0022995c(p2);
      thunk_FUN_002298d4(p3 >> 0xe);
      thunk_FUN_002298d4(p4 >> 0xe);
      return;
}
/* FUN_0041437c @ 0x0041437c */
void FUN_0041437c(uint64_t pad1)
{
    uint64_t r1;
      r1 = FUN_00350b54();
      FUN_004080b0();
      FUN_0022995c(r1);
      FUN_004652a0();
      FUN_00464eb0();
      FUN_001a8564();
      return;
}
/* FUN_004143e8 @ 0x004143e8 */
void FUN_004143e8(uint64_t pad1)
{
    uint64_t r1;
    uint64_t r2;
    uint32_t r3;
    uint32_t * reg_x20;
    uint8_t s_78[72];
      r3 = *reg_x20;
      r1 = *(uint64_t *)(reg_x20 + 2);
      r2 = *(uint64_t *)(reg_x20 + 4);
      FUN_001a84f4(s_78);
      FUN_00414334(s_78,r3,r1,r2);
      FUN_001a8564();
      return;
}
/* FUN_0041445c @ 0x0041445c */
void FUN_0041445c(uint64_t p1)
{
    uint64_t * reg_x20;
      FUN_0036b118(*reg_x20);
      *reg_x20 = p1;
      return;
}
/* FUN_0041449c @ 0x0041449c */
void FUN_0041449c(int64_t p1)
{
    uint32_t r1;
    uint8_t in_CY;
    void * puVar2;
    void * puVar3;
    uint64_t extraout_x8 = 0;
    int64_t lVar4;
    uint32_t * puVar5;
    int64_t lVar6;
      lVar4 = *(long *)(p1 + 0x10);
      if (lVar4 != 0) {
        FUN_00456294(0,lVar4,0);
        puVar2 = &DAT_00657778;
        puVar5 = (uint32_t *)(p1 + 0x20);
        lVar6 = DAT_00657788;
        do {
          r1 = *puVar5;
          puVar3 = (void *)FUN_00465d98(*(uint64_t *)(puVar2 + 0x18));
          if ((bool)in_CY) {
            FUN_000dbc98(1 < extraout_x8);
            FUN_00456294();
            puVar3 = puVar2;
          }
          *(long *)(puVar3 + 0x10) = p1;
          *(uint32_t *)(puVar3 + lVar6 * 4 + 0x20) = r1;
          in_CY = lVar4 != 0;
          lVar4 = lVar4 + -1;
          puVar2 = puVar3;
          puVar5 = puVar5 + 6;
          lVar6 = p1;
        } while (lVar4 != 0);
      }
      return;
}
/* FUN_0041454c @ 0x0041454c */
uint64_t FUN_0041454c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t pad4)
{
    uint64_t r1;
    uint64_t r2;
      r1 = FUN_004113d4(p1,p3);
      if ((r1 & 1) != 0) {
        FUN_0007c1c4();
        r2 = FUN_00411308(0, 0);
        return r2;
      }
      return 0;
}
/* FUN_00414594 @ 0x00414594 */
void FUN_00414594(uint64_t pad1)
{
      FUN_004662f4();
      FUN_00458190();
      FUN_0007c1c4();
      FUN_0045811c();
      return;
}
/* FUN_004145c0 @ 0x004145c0 */
void FUN_004145c0(uint64_t pad1)
{
    uint8_t s_68[72];
      FUN_003504d0();
      FUN_004080b0();
      FUN_00465938();
      FUN_00458190();
      FUN_0045811c(s_68);
      FUN_001a8564();
      return;
}
/* FUN_00414644 @ 0x00414644 */
wpair_t FUN_00414644(uint64_t p1)
{
    wpair_t pair1;
      pair1.lo = *(uint64_t *)((uint8_t *)DAT_005a3838 + (p1 & 0xff) * 8);
      pair1.hi = 0xe100000000000000;
      return pair1;
}
/* FUN_0041465c @ 0x0041465c */
uint32_t FUN_0041465c(int64_t p1, int64_t p2, uint64_t p3)
{
    uint64_t r1;
    int64_t reg_x19;
    int64_t reg_x20;
      if (p1 != 0x61 || p2 != -0x1f00000000000000) {
        FUN_003504d0();
        FUN_00462b80(0x61);
        r1 = FUN_002a0cf8();
        if ((r1 & 1) == 0) {
          if (reg_x20 != 0x65 || reg_x19 != -0x1f00000000000000) {
            FUN_00462b80(0x65);
            r1 = FUN_002a0cf8();
            if ((r1 & 1) == 0) {
              if (reg_x20 != 0x66 || reg_x19 != -0x1f00000000000000) {
                FUN_00462b80(0x66);
                r1 = FUN_002a0cf8();
                if ((r1 & 1) == 0) {
                  if (reg_x20 != 0x6e || reg_x19 != -0x1f00000000000000) {
                    FUN_00462b80(0x6e);
                    r1 = FUN_002a0cf8();
                    if ((r1 & 1) == 0) {
                      if (reg_x20 != 0x72 || reg_x19 != -0x1f00000000000000) {
                        FUN_00462b80(0x72);
                        r1 = FUN_002a0cf8();
                        if ((r1 & 1) == 0) {
                          if (reg_x20 != 0x74 || reg_x19 != -0x1f00000000000000) {
                            FUN_00462b80(0x74);
                            r1 = FUN_002a0cf8();
                            if ((r1 & 1) == 0) {
                              if (reg_x20 != 100 || reg_x19 != -0x1f00000000000000) {
                                FUN_00462b80(100);
                                r1 = FUN_002a0cf8();
                                if ((r1 & 1) == 0) {
                                  if (reg_x20 != 0x44 || reg_x19 != -0x1f00000000000000) {
                                    FUN_00462b80(0x44);
                                    r1 = FUN_002a0cf8();
                                    if ((r1 & 1) == 0) {
                                      if (reg_x20 != 0x68 || reg_x19 != -0x1f00000000000000) {
                                        FUN_00462b80(0x68);
                                        r1 = FUN_002a0cf8();
                                        if ((r1 & 1) == 0) {
                                          if (reg_x20 != 0x48 || reg_x19 != -0x1f00000000000000) {
                                            FUN_00462b80(0x48);
                                            r1 = FUN_002a0cf8();
                                            if ((r1 & 1) == 0) {
                                              if (reg_x20 != 0x73 || reg_x19 != -0x1f00000000000000)
                                              {
                                                FUN_00462b80(0x73);
                                                r1 = FUN_002a0cf8();
                                                if ((r1 & 1) == 0) {
                                                  if (reg_x20 != 0x53 ||
                                                      reg_x19 != -0x1f00000000000000) {
                                                    FUN_00462b80(0x53);
                                                    r1 = FUN_002a0cf8();
                                                    if ((r1 & 1) == 0) {
                                                      if (reg_x20 != 0x76 ||
                                                          reg_x19 != -0x1f00000000000000) {
                                                        FUN_00462b80(0x76);
                                                        r1 = FUN_002a0cf8();
                                                        if ((r1 & 1) == 0) {
                                                          if (reg_x20 != 0x56 ||
                                                              reg_x19 != -0x1f00000000000000) {
                                                            FUN_00462b80(0x56);
                                                            r1 = FUN_002a0cf8();
                                                            if ((r1 & 1) == 0) {
                                                              if (reg_x20 != 0x77 ||
                                                                  reg_x19 != -0x1f00000000000000) {
                                                                FUN_00462b80(0x77);
                                                                r1 = FUN_002a0cf8();
                                                                if ((r1 & 1) == 0) {
                                                                  if (reg_x20 != 0x57 ||
                                                                      reg_x19 != -0x1f00000000000000)
                                                                  {
                                                                    FUN_00462b80(0x57);
                                                                    r1 = FUN_002a0cf8();
                                                                    if ((r1 & 1) == 0) {
                                                                      if (reg_x20 != 0x62 ||
                                                                          reg_x19 !=
                                                                          -0x1f00000000000000) {
                                                                        FUN_00462b80(0x62);
                                                                        r1 = FUN_002a0cf8();
                                                                        if ((r1 & 1) == 0) {
                                                                          if ((p3 & 1) != 0) {
                                                                            return 0x1f;
                                                                          }
                                                                          if (reg_x20 != 0x43 ||
                                                                              reg_x19 !=
                                                                              -0x1f00000000000000) {
                                                                            FUN_00462b80(0x43);
                                                                            r1 = FUN_002a0cf8();
                                                                            if ((r1 & 1) == 0) {
                                                                              if (reg_x20 != 0x4e ||
                                                                                  reg_x19 !=
                                                                                  -0x1f00000000000000) {
                                                                                FUN_00462b80(0x4e);
                                                                                r1 = FUN_002a0cf8();
                                                                                if ((r1 & 1) == 0) {
                                                                                  if (reg_x20 != 0x52
                                                                                      || reg_x19 !=

                                                      -0x1f00000000000000) {
                                                        FUN_00462b80(0x52);
                                                        r1 = FUN_002a0cf8();
                                                        if ((r1 & 1) == 0) {
                                                          if (reg_x20 != 0x58 ||
                                                              reg_x19 != -0x1f00000000000000) {
                                                            FUN_00462b80(0x58);
                                                            r1 = FUN_002a0cf8();
                                                            if ((r1 & 1) == 0) {
                                                              if (reg_x20 != 0x42 ||
                                                                  reg_x19 != -0x1f00000000000000) {
                                                                FUN_00462b80(0x42);
                                                                r1 = FUN_002a0cf8();
                                                                if ((r1 & 1) == 0) {
                                                                  if (reg_x20 != 0x41 ||
                                                                      reg_x19 != -0x1f00000000000000)
                                                                  {
                                                                    FUN_00462b80(0x41);
                                                                    r1 = FUN_002a0cf8();
                                                                    if ((r1 & 1) == 0) {
                                                                      if (reg_x20 != 0x5a ||
                                                                          reg_x19 !=
                                                                          -0x1f00000000000000) {
                                                                        FUN_00462b80(0x5a);
                                                                        r1 = FUN_002a0cf8();
                                                                        if ((r1 & 1) == 0) {
                                                                          if (reg_x20 != 0x7a ||
                                                                              reg_x19 !=
                                                                              -0x1f00000000000000) {
                                                                            FUN_00462b80(0x7a);
                                                                            r1 = FUN_002a0cf8();
                                                                            if ((r1 & 1) == 0) {
                                                                              if (reg_x20 != 0x47 ||
                                                                                  reg_x19 !=
                                                                                  -0x1f00000000000000) {
                                                                                FUN_00462b80(0x47);
                                                                                r1 = FUN_002a0cf8();
                                                                                if ((r1 & 1) == 0) {
                                                                                  if (reg_x20 != 0x4b
                                                                                      || reg_x19 !=

                                                      -0x1f00000000000000) {
                                                        FUN_00462b80(0x4b);
                                                        r1 = FUN_002a0cf8();
                                                        if ((r1 & 1) == 0) {
                                                          if (reg_x20 != 0x4f ||
                                                              reg_x19 != -0x1f00000000000000) {
                                                            FUN_00462b80(0x4f);
                                                            r1 = FUN_002a0cf8();
                                                            if ((r1 & 1) == 0) {
                                                              if (reg_x20 != 0x79 ||
                                                                  reg_x19 != -0x1f00000000000000) {
                                                                FUN_00462b80(0x79);
                                                                r1 = FUN_002a0cf8();
                                                                if ((r1 & 1) == 0) {
                                                                  if (reg_x20 == 0x59 &&
                                                                      reg_x19 == -0x1f00000000000000)
                                                                  {
                                                                    return 0x1e;
                                                                  }
                                                                  FUN_00462b80(0x59);
                                                                  r1 = FUN_002a0cf8();
                                                                  if ((r1 & 1) != 0) {
                                                                    return 0x1e;
                                                                  }
                                                                  return 0x1f;
                                                                }
                                                              }
                                                              return 0x1d;
                                                            }
                                                          }
                                                          return 0x1c;
                                                        }
                                                      }
                                                      return 0x1b;
                                                      }
                                                      }
                                                      return 0x1a;
                                                      }
                                                      }
                                                      return 0x19;
                                                      }
                                                      }
                                                      return 0x18;
                                                      }
                                                      }
                                                      return 0x17;
                                                      }
                                                      }
                                                      return 0x16;
                                                      }
                                                      }
                                                      return 0x14;
                                                      }
                                                      }
                                                      return 0xc;
                                                      }
                                                      }
                                                      return 0xb;
                                                      }
                                                      }
                                                      return 6;
                                                      }
                                                      }
                                                      if ((p3 & 1) != 0) {
                                                        return 0x13;
                                                      }
                                                      return 0x15;
                                                      }
                                                      }
                                                      return 0x12;
                                                      }
                                                      }
                                                      return 0x11;
                                                      }
                                                      }
                                                      return 0x10;
                                                      }
                                                      }
                                                      return 0xf;
                                                    }
                                                  }
                                                  return 0xe;
                                                }
                                              }
                                              return 0xd;
                                            }
                                          }
                                          return 10;
                                        }
                                      }
                                      return 9;
                                    }
                                  }
                                  return 8;
                                }
                              }
                              return 7;
                            }
                          }
                          return 5;
                        }
                      }
                      return 4;
                    }
                  }
                  return 3;
                }
              }
              return 2;
            }
          }
          return 1;
        }
      }
      return 0;
}
/* FUN_00414b64 @ 0x00414b64 */
uint8_t FUN_00414b64(uint64_t pad1)
{
    uint8_t unaff_w20;
      FUN_0041465c(0, 0, 0);
      FUN_00351d18();
      FUN_003a25d4();
      return unaff_w20;
}
/* FUN_00414bd8 @ 0x00414bd8 */
void FUN_00414bd8(uint64_t * p1, uint64_t * p2, uint8_t p3, uint8_t p4)
{
    uint8_t r1;
    uint64_t r2;
    uint64_t r3;
    uint64_t r4;
      r1 = *(uint8_t *)(p2 + 4);
      r2 = *p2;
      r4 = p2[3];
      r3 = p2[2];
      p1[1] = p2[1];
      *p1 = r2;
      p1[3] = r4;
      p1[2] = r3;
      *(uint8_t *)(p1 + 4) = r1;
      *(uint8_t *)((long)p1 + 0x21) = p3;
      *(uint8_t *)((long)p1 + 0x22) = p4;
      return;
}
/* FUN_00414bf4 @ 0x00414bf4 */
void FUN_00414bf4(uint64_t pad1)
{
    uint64_t r1;
    uint64_t r2;
    bool bVar3;
    uint64_t r4;
    uint64_t extraout_x8 = 0;
    int64_t reg_x19;
    int64_t reg_x20;
    wpair_t pair5;
      r4 = FUN_00466568();
      FUN_004644f8();
      pair5 = FUN_004632e0();
      FUN_00463df8(pair5.lo,pair5.hi,0x683828);
      FUN_00462728();
      FUN_00205844();
      bVar3 = (*(uint8_t *)(reg_x20 + 0x21) & 1) == 0;
      r2 = 0x65757274;
      if (bVar3) {
        r2 = 0x65736c6166;
      }
      r1 = 0xe400000000000000;
      if (bVar3) {
        r1 = 0xe500000000000000;
      }
      thunk_FUN_002acbb8(r2,r1);
      FUN_003a25d4(r1);
      bVar3 = (*(uint8_t *)(reg_x19 + 0x22) & 1) == 0;
      r2 = 0x65757274;
      if (bVar3) {
        r2 = 0x65736c6166;
      }
      r1 = 0xe400000000000000;
      if (bVar3) {
        r1 = 0xe500000000000000;
      }
      thunk_FUN_002acbb8(r2,r1);
      FUN_003a25d4(r1);
      FUN_00466528(0,extraout_x8,r4);
      return;
}
/* FUN_00414cb0 @ 0x00414cb0 */
uint8_t FUN_00414cb0(uint64_t pad1)
{
    uint64_t r1;
    uint8_t bVar2;
    int64_t reg_x19;
    int64_t reg_x20;
      FUN_003504d0();
      r1 = FUN_00414dec(0, 0);
      if (((r1 & 1) == 0) || (((*(uint8_t *)(reg_x20 + 0x21) ^ *(uint8_t *)(reg_x19 + 0x21)) & 1) != 0)
         ) {
        bVar2 = 0;
      }
      else {
        bVar2 = *(uint8_t *)(reg_x20 + 0x22) ^ *(uint8_t *)(reg_x19 + 0x22) ^ 1;
      }
      return bVar2 & 1;
}
/* FUN_00414d04 @ 0x00414d04 */
void FUN_00414d04(uint8_t * p1)
{
    int64_t reg_x19;
    int64_t reg_x20;
      FUN_00464a38();
      FUN_004150e8(0);
      FUN_00229a3c(*(uint8_t *)(reg_x20 + 0x21) & 1);
      FUN_00229a3c(*(uint8_t *)(reg_x19 + 0x22) & 1);
      return;
}
/* FUN_00414d4c @ 0x00414d4c */
void FUN_00414d4c(uint64_t pad1)
{
    int64_t reg_x19;
    int64_t reg_x20;
    uint8_t s_68[72];
      FUN_004644e8();
      FUN_004150e8(s_68);
      FUN_00229a3c(*(uint8_t *)(reg_x20 + 0x21) & 1);
      FUN_00229a3c(*(uint8_t *)(reg_x19 + 0x22) & 1);
      FUN_001a8564();
      return;
}
/* FUN_00414dac @ 0x00414dac */
void FUN_00414dac(uint64_t pad1)
{
    uint8_t s_68[72];
      FUN_001a84f4(s_68);
      FUN_00414d04(s_68);
      FUN_001a8564();
      return;
}
/* FUN_00414dec @ 0x00414dec */
uint64_t FUN_00414dec(uint16_t * p1, double * p2)
{
    double dVar1;
    double dVar2;
    double dVar3;
    double dVar4;
    char cVar5;
    bool bVar6;
    double dVar7;
    uint32_t r8;
    int64_t extraout_x8 = 0;
    int64_t lVar9;
    int64_t extraout_x8_00 = 0;
    uint64_t r10;
    uint64_t r11;
    double dVar12;
    double dVar13;
    wpair_t pair14;
      cVar5 = (char)*p1;
      dVar1 = *(double *)(p1 + 4);
      dVar3 = *(double *)(p1 + 8);
      pair14 = *(wpair_t *)(p1 + 4);
      dVar12 = *(double *)(p1 + 0xc);
      r10 = (uint64_t)*p1;
      r11 = (uint64_t)*(uint32_t *)(p1 + 1) << 0x10 | (uint64_t)p1[3] << 0x30;
      dVar7 = (double)(r11 | r10);
      switch((char)p1[0x10]) {
      default:
        if (*(char *)(p2 + 4) == '\0') {
    LAB_0041500c:
          bVar6 = cVar5 == *(char *)p2;
    LAB_00415014:
          r8 = (uint32_t)bVar6;
          goto LAB_00415060;
        }
        break;
      case '\x01':
        if (*(char *)(p2 + 4) == '\x01') {
          r8 = 0;
          if (cVar5 == *(char *)p2) {
            r8 = (*(uint8_t *)((long)p1 + 1) ^ *(uint8_t *)((long)p2 + 1)) ^ 1;
          }
          goto LAB_00415060;
        }
        break;
      case '\x02':
        if (*(char *)(p2 + 4) == '\x02') goto LAB_0041500c;
        break;
      case '\x03':
        if (*(char *)(p2 + 4) == '\x03') goto LAB_0041500c;
        break;
      case '\x04':
        if (*(char *)(p2 + 4) == '\x04') {
          pair14.hi = dVar1;
          pair14.lo = r10 | r11;
          if ((double)(r10 | r11) != *p2 || dVar1 != p2[1]) goto LAB_00415088;
    LAB_004150a0:
          r8 = 1;
          goto LAB_00415060;
        }
        break;
      case '\x05':
        if (*(char *)(p2 + 4) == '\x05') goto LAB_0041500c;
        break;
      case '\x06':
        if (*(char *)(p2 + 4) == '\x06') {
          bVar6 = *p2 == (double)(r10 | r11);
          goto LAB_00415014;
        }
        break;
      case '\a':
        if ((*(char *)(p2 + 4) == '\a') && (cVar5 == *(char *)p2)) {
          if (dVar1 != p2[1] || dVar3 != p2[2]) goto LAB_00415088;
          goto LAB_004150a0;
        }
        break;
      case '\b':
        if (*(char *)(p2 + 4) == '\b') goto LAB_0041500c;
        break;
      case '\t':
        if (*(char *)(p2 + 4) == '\t') {
          bVar6 = dVar7 == *p2 && dVar1 == p2[1];
          goto LAB_00415014;
        }
        break;
      case '\n':
        if (*(char *)(p2 + 4) == '\n') {
          bVar6 = *p1 == *(uint16_t *)p2;
          goto LAB_00415014;
        }
        break;
      case '\v':
        if (*(char *)(p2 + 4) == '\v') goto LAB_0041500c;
        break;
      case '\f':
        if (*(char *)(p2 + 4) == '\f') goto LAB_0041500c;
        break;
      case '\r':
        if (*(char *)(p2 + 4) == '\r') goto LAB_0041500c;
        break;
      case '\x0e':
        if (*(char *)(p2 + 4) == '\x0e') {
          dVar2 = p2[1];
          dVar4 = p2[2];
          dVar13 = p2[3];
          if (dVar1 == 0.0) {
            if (dVar2 == 0.0) goto LAB_00415074;
          }
          else if ((dVar2 != 0.0) &&
                  ((dVar7 == *p2 && dVar1 == dVar2 || (r10 = FUN_00465c5c(), (r10 & 1) != 0))
                  )) {
    LAB_00415074:
            if (dVar3 != dVar4 || dVar12 != dVar13) {
              FUN_0009461c();
              pair14 = FUN_003511cc();
    LAB_00415088:
              r10 = FUN_002a0cf8(pair14.lo,pair14.hi);
              return r10;
            }
            goto LAB_004150a0;
          }
        }
        break;
      case '\x0f':
        if (((dVar3 == 0.0 && dVar1 == 0.0) && dVar12 == 0.0) && dVar7 == 0.0) {
          if (*(char *)(p2 + 4) == '\x0f') {
            FUN_004655fc();
            lVar9 = extraout_x8;
    joined_r0x0041502c:
            if (lVar9 == 0) goto LAB_004150a0;
          }
        }
        else if (dVar7 == 4.94065645841247e-324 && ((dVar3 == 0.0 && dVar1 == 0.0) && dVar12 == 0.0)) {
          if ((*(char *)(p2 + 4) == '\x0f') && (*p2 == 4.94065645841247e-324))
          goto LAB_0041504c;
        }
        else if ((*(char *)(p2 + 4) == '\x0f') && (*p2 == 9.88131291682493e-324)) {
    LAB_0041504c:
          FUN_00465d08();
          lVar9 = extraout_x8_00;
          goto joined_r0x0041502c;
        }
      }
      r8 = 0;
    LAB_00415060:
      return (uint64_t)(r8 & 1);
}
/* FUN_004150e8 @ 0x004150e8 */
void FUN_004150e8(uint8_t * p1)
{
    uint64_t r1;
    uint8_t bVar2;
    uint16_t r3;
    uint64_t r4;
    int64_t lVar5;
    uint64_t r6;
    uint16_t * reg_x20;
    uint64_t r7;
    uint64_t reg_x30;
    wpair_t pair8;
      r6 = (uint64_t)(uint8_t)*reg_x20;
      bVar2 = *(uint8_t *)((long)reg_x20 + 1);
      r3 = *reg_x20;
      r1 = *(uint64_t *)(reg_x20 + 4);
      lVar5 = *(long *)(reg_x20 + 8);
      r7 = (uint64_t)*(uint32_t *)(reg_x20 + 1) << 0x10 | (uint64_t)reg_x20[3] << 0x30 | (uint64_t)r3;
      switch((uint8_t)reg_x20[0x10]) {
      default:
        thunk_FUN_002298d4(3);
        FUN_00451a64(r6);
        break;
      case 1:
        thunk_FUN_002298d4(4);
        FUN_00447144(r6);
        FUN_00465830();
        FUN_0046663c(p1);
        FUN_003a25d4(r6);
        r6 = (uint64_t)(bVar2 & 1);
        goto LAB_00415354;
      case 2:
        r4 = 5;
        goto LAB_00415248;
      case 3:
        r4 = 6;
    LAB_00415248:
        thunk_FUN_002298d4(r4);
        FUN_00450adc(r6);
        break;
      case 4:
        thunk_FUN_002298d4(7);
        pair8 = FUN_000e72b0();
        lVar5 = pair8.hi;
        p1 = (uint8_t *)pair8.lo;
        goto LAB_00415374;
      case 5:
        thunk_FUN_002298d4(8);
        goto LAB_0041539c;
      case 6:
        thunk_FUN_002298d4(9);
        FUN_0046555c(r7,p1,reg_x30);
        FUN_002eaa34();
        return;
      case 7:
        thunk_FUN_002298d4(10);
        thunk_FUN_002298d4(r6);
        pair8 = FUN_003511d8(p1);
        lVar5 = pair8.hi;
        p1 = (uint8_t *)pair8.lo;
        goto LAB_00415374;
      case 8:
        thunk_FUN_002298d4(0xb);
    LAB_00415354:
        FUN_00229a3c(r6);
        goto LAB_004153a0;
      case 9:
        thunk_FUN_002298d4(0xc);
        thunk_FUN_002298d4(r7);
        r6 = r1;
        goto LAB_0041539c;
      case 10:
        thunk_FUN_002298d4(0xd);
        FUN_0045399c((uint64_t)r3);
        break;
      case 0xb:
        thunk_FUN_002298d4(0xe);
        FUN_00451894(r6);
        break;
      case 0xc:
        thunk_FUN_002298d4(0xf);
        r4 = FUN_00415470(r6);
        FUN_001b9084(p1,r4,0xe300000000000000);
        r6 = 0xe300000000000000;
        goto LAB_0041532c;
      case 0xd:
        thunk_FUN_002298d4(0x10);
        FUN_00415b54(r6);
        break;
      case 0xe:
        thunk_FUN_002298d4(0x11);
        if (r1 == 0) {
          FUN_00229a3c(0);
        }
        else {
          FUN_00229a3c(1);
          pair8 = FUN_000e72b0();
          FUN_001b9084(pair8.lo,pair8.hi,r1);
        }
    LAB_00415374:
        FUN_0046555c(p1,lVar5);
        FUN_001b9084();
        return;
      case 0xf:
        if (((lVar5 == 0 && r1 == 0) && *(long *)(reg_x20 + 0xc) == 0) && r7 == 0) {
          r6 = 0;
        }
        else if (r7 == 1 && ((lVar5 == 0 && r1 == 0) && *(long *)(reg_x20 + 0xc) == 0)) {
          r6 = 1;
        }
        else {
          r6 = 2;
        }
    LAB_0041539c:
        thunk_FUN_002298d4(r6);
    LAB_004153a0:
        FUN_0046555c(reg_x30);
        return;
      }
      FUN_00465830();
      FUN_0046663c(p1);
    LAB_0041532c:
      FUN_0046555c(r6,reg_x30);
      FUN_003a25d4();
      return;
}
/* FUN_00415430 @ 0x00415430 */
uint64_t FUN_00415430(uint64_t pad1, uint64_t pad2)
{
    uint64_t reg_x20;
      FUN_00356c6c();
      FUN_002ad78c(0x67f5d0);
      FUN_00465240();
      if (4 < reg_x20) {
        reg_x20 = 5;
      }
      return reg_x20;
}
/* FUN_00415484 @ 0x00415484 */
void FUN_00415484(uint8_t * p1, uint64_t * p2, uint64_t pad3)
{
    uint8_t r1;
      r1 = FUN_00415430(*p2,p2[1]);
      *p1 = r1;
      return;
}
/* FUN_004154b8 @ 0x004154b8 */
void FUN_004154b8(uint64_t * p1)
{
    uint64_t r1;
    uint8_t * reg_x20;
      r1 = FUN_00415470(*reg_x20);
      *p1 = r1;
      p1[1] = 0xe300000000000000;
      return;
}
/* FUN_004154f0 @ 0x004154f0 */
void FUN_004154f0(uint64_t p1, uint64_t pad2)
{
    uint64_t r1;
    uint8_t s_68[72];
      FUN_001a84f4(s_68,0);
      r1 = FUN_00415470(p1);
      FUN_001b9084(s_68,r1,0xe300000000000000);
      FUN_003a25d4(0xe300000000000000);
      FUN_001a8564();
      return;
}
/* FUN_00415570 @ 0x00415570 */
void FUN_00415570(uint64_t p1, code * p2)
{
    uint8_t s_68[72];
      FUN_004080b0();
      (*p2)(p1);
      FUN_00465830();
      FUN_0046663c(s_68);
      FUN_003a25d4(p2);
      FUN_001a8564();
      return;
}
/* FUN_004155c8 @ 0x004155c8 */
void FUN_004155c8(uint64_t p1, uint64_t pad2)
{
    wpair_t pair1;
    uint8_t s_68[72];
      FUN_001a84f4(s_68,0);
      pair1 = FUN_0045399c(p1);
      FUN_001b9084(s_68,pair1.lo,pair1.hi);
      FUN_003a25d4(pair1.hi);
      FUN_001a8564();
      return;
}
/* FUN_00415634 @ 0x00415634 */
void FUN_00415634(uint64_t p1, uint64_t p2)
{
    wpair_t pair1;
      pair1 = FUN_0045399c(p2);
      FUN_001b9084(p1,pair1.lo,pair1.hi);
      FUN_003a25d4(pair1.hi);
      return;
}
/* FUN_0041567c @ 0x0041567c */
void FUN_0041567c(uint64_t p1, uint8_t p2, uint64_t pad3, uint64_t pad4)
{
    uint64_t r1;
    uint64_t r2;
      r2 = 0xe500000000000000;
      r1 = 0x6d756e6c61;
      switch(p2) {
      case 1:
        r1 = 0x6b6e616c62;
        break;
      case 2:
        r1 = 0x6870617267;
        break;
      case 3:
        r1 = 0x746e697270;
        break;
      case 4:
        r2 = 0xe400000000000000;
        r1 = 0x64726f77;
        break;
      case 5:
        r2 = 0xe600000000000000;
        r1 = 0x746967696478;
      }
      FUN_001b9084(p1,r1,r2);
      FUN_003a25d4(r2);
      return;
}
/* FUN_0041574c @ 0x0041574c */
void FUN_0041574c(uint64_t p1, uint64_t p2, uint64_t pad3, uint64_t pad4)
{
      FUN_001b9084(p1,*(uint64_t *)((uint8_t *)DAT_005a3930 + (p2 & 0xff) * 8),0xe300000000000000);
      FUN_003a25d4(0xe300000000000000);
      return;
}
/* FUN_004157c8 @ 0x004157c8 */
void FUN_004157c8(uint64_t p1, char p2, uint64_t pad3, uint64_t pad4)
{
    uint64_t r1;
    uint64_t r2;
      r1 = 0x5e5b;
      if (p2 != '\x01') {
        r1 = 0x5b;
      }
      r2 = 0xe200000000000000;
      if (p2 != '\x01') {
        r2 = 0xe100000000000000;
      }
      FUN_001b9084(p1,r1,r2);
      FUN_003a25d4(r2);
      return;
}
/* FUN_00415814 @ 0x00415814 */
void FUN_00415814(uint64_t p1, uint64_t p2, uint64_t pad3, uint64_t pad4)
{
      FUN_001b9084(p1,*(uint64_t *)((uint8_t *)DAT_005a3a50 + (p2 & 0xff) * 8),0xe200000000000000);
      FUN_003a25d4(0xe200000000000000);
      return;
}
/* FUN_00415818 @ 0x00415818 */
void FUN_00415818(uint64_t p1, uint64_t p2, uint64_t pad3, uint64_t pad4)
{
      FUN_001b9084(p1,*(uint64_t *)((uint8_t *)DAT_005a3a50 + (p2 & 0xff) * 8),0xe200000000000000);
      FUN_003a25d4(0xe200000000000000);
      return;
}
/* FUN_00415848 @ 0x00415848 */
void FUN_00415848(uint64_t p1, char p2, uint64_t pad3, uint64_t pad4)
{
    uint8_t r1;
    uint64_t r2;
      if (p2 == '\0') {
        r1 = 0;
        r2 = 0xe000000000000000;
      }
      else {
        r1 = 0x3f;
        if (p2 != '\x01') {
          r1 = 0x2b;
        }
        r2 = 0xe100000000000000;
      }
      FUN_001b9084(p1,r1,r2);
      FUN_003a25d4(r2);
      return;
}
/* FUN_004158ac @ 0x004158ac */
void FUN_004158ac(uint64_t p1, char p2)
{
    uint8_t r1;
    uint64_t r2;
    uint8_t s_68[72];
      FUN_001a84f4(s_68);
      if (p2 == '\0') {
        r1 = 0;
        r2 = 0xe000000000000000;
      }
      else {
        r1 = 0x3f;
        if (p2 != '\x01') {
          r1 = 0x2b;
        }
        r2 = 0xe100000000000000;
      }
      FUN_001b9084(s_68,r1,r2);
      FUN_003a25d4(r2);
      FUN_001a8564();
      return;
}

/* ==================================================================== *
 * SK190 hand-transcribed bodies (register/arity artifacts)
 * ==================================================================== */

/* ====================================================================== *
 * SK190 hand-written bodies (arity/register-artifact adjustments).
 * Signatures are matched to the decompiled call sites; Ghidra register
 * args (unaff_x19/x20) become explicit params.
 * ====================================================================== */

/*--------------------------------------------------------------------*
 * FUN_0041001c @ 0x0041001c   (est. sk_obj_service_object_compare_dispatch)
 * Ghidra: void FUN_0041001c(void, 0)  [returns a match flag in practice]
 * Swift object-equality/dispatch switch: fetches the current object pair
 * (FUN_0008e518), switches on the tag (>> 0x3c), and either compares two
 * object payloads for equality or calls the type-specific constructor /
 * comparator helpers.  Reports the result flag via FUN_0008e500.
 * Confidence: medium.
 * Notes: many sibling helpers; extraout_x8/x9 register results approximated. */
uint64_t FUN_0041001c(uint64_t p1, uint64_t p2)
{
    uint64_t lo, hi;
    uint64_t r1, r2, r3, r4, r6, r7, r8, r10;
    uint8_t r5;
    uint32_t r9;
    bool b;
    wpair_t pair;

    (void)p1; (void)p2;
    pair = FUN_0008e518();
    hi = pair.hi;
    lo = pair.lo;
    switch (lo >> 0x3c) {
    default:
        if (hi >> 0x3c == 0) {
            r1 = *(uint64_t *)(hi + 0x10);
            r2 = *(uint64_t *)(hi + 0x18);
            FUN_0036b270(r1);
            FUN_0036b270(r2);
            FUN_003509bc();
            r6 = FUN_0041144c(0, 0);
            if ((r6 & 1) == 0) {
                FUN_0036b118(r2);
                FUN_0036b118(r1);
            } else {
                FUN_00084180();
                r6 = FUN_00411930(0, 0);
                FUN_0036b118(r2);
                FUN_0036b118(r1);
                if ((r6 & 1) != 0)
                    goto match;
            }
        }
        break;
    case 1:
        if (hi >> 0x3c == 1) {
            r1 = *(uint64_t *)((lo & 0xfffffffffffffff) + 0x20);
            FUN_0036b270(*(uint64_t *)((hi & 0xfffffffffffffff) + 0x10));
            FUN_00100efc();
            FUN_0035053c();
            FUN_00411d40(0);
            FUN_00351d18();
            FUN_0036b118();
            r9 = (uint32_t)r1;
            goto done;
        }
        break;
    case 2:
        pair = FUN_00464880();
        FUN_00117cc4(pair.lo, pair.hi, 0x80);
        if (hi >> 0x3c != 2) break;
        pair = FUN_0046482c();
        FUN_00117cc4(pair.lo, pair.hi, 0x80);
        FUN_00466264();
        FUN_00458a90();
        FUN_004658d8();
        FUN_0041a64c();
        FUN_004658cc();
        FUN_00458aa0();
        goto done2;
    case 3:
        pair = FUN_00464880();
        FUN_00117cc4(pair.lo, pair.hi, 200);
        if (hi >> 0x3c == 3) {
            pair = FUN_0046482c();
            FUN_00117cc4(pair.lo, pair.hi, 200);
            FUN_00466264();
            FUN_00458a58();
            FUN_004658d8();
            FUN_00418050();
            FUN_004658cc();
            FUN_00458a68();
            goto done2;
        }
        break;
    case 4:
        pair = FUN_00464880();
        FUN_00117cc4(pair.lo, pair.hi, 0x88);
        if (hi >> 0x3c == 4) {
            pair = FUN_0046482c();
            FUN_00117cc4(pair.lo, pair.hi, 0x88);
            FUN_00466264();
            FUN_00458a20();
            FUN_004658d8();
            FUN_0041bdac();
            FUN_004658cc();
            FUN_00458a30();
            goto done2;
        }
        break;
    case 5:
        if (hi >> 0x3c == 5) {
cmp_pair:
            r6 = lo & 0xfffffffffffffff;
            r3 = *(uint64_t *)(r6 + 0x28);
            hi = hi & 0xfffffffffffffff;
            r8 = *(uint64_t *)(hi + 0x28);
            b = *(int64_t *)(r6 + 0x10) == *(int64_t *)(hi + 0x10);
            r5 = b && *(uint64_t *)(hi + 0x18) <= *(uint64_t *)(r6 + 0x18);
            if (b && *(uint64_t *)(r6 + 0x18) == *(uint64_t *)(hi + 0x18)) {
                FUN_0046622c();
                goto nomatch;
            } else {
                r6 = FUN_002a0cf8();
                if (((r6 & 1) != 0) && (FUN_004658a8(), !r5))
                    goto nomatch;
            }
            r8 = r8 ^ r3;
            goto cmp_done;
        }
        break;
    case 6:
        if (hi >> 0x3c == 6) goto cmp_pair;
        break;
    case 7:
        if (hi >> 0x3c == 7) goto cmp_pair;
        break;
    case 8:
        pair = FUN_00464880();
        FUN_00117cc4(pair.lo, pair.hi, 0xb0);
        if ((int64_t)hi < -0x7000000000000000LL) {
            pair = FUN_0046482c();
            FUN_00117cc4(pair.lo, pair.hi, 0xb0);
            FUN_00466264();
            FUN_004589e8();
            FUN_004658d8();
            FUN_00413a0c(0);
            FUN_004658cc();
            FUN_004589f8();
            goto done2;
        }
        break;
    case 9:
        if (hi >> 0x3c == 9) {
            FUN_0036b270(*(uint64_t *)((hi & 0xfffffffffffffff) + 0x28));
            FUN_004658d8();
            FUN_00419b14();
            FUN_004658cc();
            FUN_004589bc();
            goto done2;
        }
        break;
    case 10:
        if ((hi >> 0x3c == 10) && (FUN_00465c44(), r10 == 0) &&
            (FUN_00465c44(), r10 == 0)) {
            r6 = *(uint64_t *)(r2 + 0x40);
            r3 = *(uint64_t *)(r2 + 0x48);
            hi = *(uint64_t *)(r1 + 0x40);
            r8 = *(uint64_t *)(r1 + 0x48);
            FUN_0034fe80();
            FUN_004588cc();
            FUN_0009461c();
            FUN_003511cc();
            r7 = FUN_00412248(0,0,0,0,0,0,0,0);
            FUN_0034fe80();
            FUN_00458940();
            if (((r7 & 1) != 0) && ((hi ^ r6) >> 0xe == 0)) {
                r8 = r8 ^ r3;
                goto cmp_done;
            }
        }
        break;
    case 0xb:
        if ((hi >> 0x3c == 0xb) && (FUN_00465c44(), r10 == 0)) {
            r8 = *(uint64_t *)(r2 + 0x18) ^ *(uint64_t *)(r1 + 0x18);
cmp_done:
            if (r8 < 0x4000)
                goto match;
        }
    }
    hi = 0;
done2:
    r9 = (uint32_t)hi;
done:
    FUN_0008e500(r9 & 1, 0);
    return r9 & 1;
match:
    hi = 1;
    goto done2;
nomatch:
    hi = 0;
    goto done2;
}

/*--------------------------------------------------------------------*
 * FUN_004107e4 @ 0x004107e4   (est. sk_obj_service_call_validate)
 * Ghidra: undefined8 FUN_004107e4(void)
 * Builds a service descriptor via FUN_004108a0, then runs an object
 * validation/key-derivation step (FUN_00365b6c).  Returns a status word.
 * Confidence: medium.
 * Notes: FUN_00466554 returns a 16-byte (x0:x1) pair; lo used here. */
uint64_t FUN_004107e4(uint64_t p1)
{
    uint64_t r2, r3, local60, local58, local50, local48, local40;
    uint8_t s88[40];
    int32_t i1;
    code *cb = 0;   /* extraout_x8 (unmodelled register fn-ptr) */
    (void)p1;

    FUN_004108a0(s88, 0);
    r2 = FUN_00466554().lo;
    r3 = FUN_00466540();
    i1 = FUN_00365b6c(&local60, s88, r2, r3, 6);
    if (i1 == 0) {
        local40 = 0;
        local58 = 0;
        local60 = 0;
        local48 = 0;
        local50 = 0;
        FUN_00466168();
        FUN_00461cb8(&local60);
        return 0;
    }
    FUN_0034e1ec(&local60);
    r2 = FUN_00458ac8(local40);
    FUN_003507e0(r2);
    r2 = (*cb)();
    FUN_000026e8(&local60);
    return r2;
}

/*--------------------------------------------------------------------*
 * FUN_0041106c @ 0x0041106c   (est. sk_obj_state_snapshot)
 * Ghidra: void FUN_0041106c(undefined8 *param_1, long param_2)
 * Copies a 48-byte object-state descriptor into the output buffer: either
 * from the object's payload array (offset obj + count*0x30) or the empty
 * 16-byte marker held in globals DAT_005a1800/DAT_005a1808.
 * Confidence: medium. */
void FUN_0041106c(uint8_t *buf, uint64_t obj)
{
    uint64_t *p;
    uint64_t v2, v3, v4, v5, v6, v7;
    uint64_t *out = (uint64_t *)buf;

    if (*(int64_t *)(obj + 0x10) == 0) {
        v4 = v5 = v6 = v7 = 0;
        v2 = DAT_005a1800;
        v3 = uram_00000000005a1808;
    } else {
        p = (uint64_t *)(obj + *(int64_t *)(obj + 0x10) * 0x30);
        v5 = p[1];
        v4 = p[0];
        v7 = p[3];
        v6 = p[2];
        v2 = p[-2];
        v3 = p[-1];
    }
    out[1] = v3;
    out[0] = v2;
    out[3] = v5;
    out[2] = v4;
    out[5] = v7;
    out[4] = v6;
}

/*--------------------------------------------------------------------*
 * FUN_00411bbc @ 0x00411bbc   (est. sk_obj_service_reg_dispatch)
 * Ghidra: undefined1 [16] FUN_00411bbc(void)
 * Runs a Swift service registration dispatch: builds a 16-byte result
 * (FUN_00465c0c), copies type metadata (FUN_00463df8), and fills the
 * returned 16-byte buffer via FUN_00205844.
 * Confidence: medium. */
wpair_t FUN_00411bbc(void)
{
    wpair_t pair;
    uint8_t sa0[128];
    wpair_t out;

    pair = FUN_00465c0c();
    FUN_00463df8(pair.lo, pair.hi, 0x6840e0);
    FUN_00462728();
    FUN_00205844(sa0, &out);
    return out;
}

/*--------------------------------------------------------------------*
 * FUN_00411c8c @ 0x00411c8c   (est. sk_obj_service_reg_meta)
 * Ghidra: undefined1 [16] FUN_00411c8c(void)
 * Returns a 16-byte metadata value: runs three service helpers and returns
 * the local_30 buffer (Swift value build).
 * Confidence: low (Swift metadata buffer return). */
wpair_t FUN_00411c8c(void)
{
    wpair_t out;

    FUN_00465a88();
    FUN_004640c4();
    thunk_FUN_002acbb8();
    return out;
}

/*--------------------------------------------------------------------*
 * FUN_00411cc4 @ 0x00411cc4   (est. sk_obj_service_dispatch_root)
 * Ghidra: undefined1 [16] FUN_00411cc4(void)
 * Root object-service dispatcher: calls the big per-type handler
 * (FUN_00413b68 -> wpair), then copies a 0xb0-byte region from
 * reg_x20+0xc0 and returns the 16-byte result.
 * Confidence: medium. */
wpair_t FUN_00411cc4(uint64_t reg_x20)
{
    wpair_t pair;
    uint8_t s190[176], se0[176];

    FUN_00465c00(se0);
    pair = FUN_00413b68(0);
    FUN_00463de0();
    thunk_FUN_002acbb8();
    FUN_00117cc4(s190, reg_x20 + 0xc0, 0xb0);
    FUN_00413b68(0);
    FUN_00465294();
    FUN_003a25d4();
    return pair;
}

/*--------------------------------------------------------------------*
 * FUN_00411d94 @ 0x00411d94   (est. sk_obj_service_call_teardown)
 * Ghidra: void FUN_00411d94(void, 0, 0, 0)
 * Teardown helper: releases the object and reports two register-derived
 * key words (v0/v1) through the sibling thunk logger.
 * Confidence: low (unaff_x19/x20 register args approximated as v0/v1). */
void FUN_00411d94(uint8_t *buf, uint64_t v0, uint64_t v1, uint64_t v2)
{
    (void)buf; (void)v2;
    FUN_00077888();
    FUN_004580b4();
    thunk_FUN_002298d4(v0 >> 0xe);
    thunk_FUN_002298d4(v1 >> 0xe);
}

/*--------------------------------------------------------------------*
 * FUN_00411e40 @ 0x00411e40   (est. sk_obj_service_call_wrap)
 * Ghidra: void FUN_00411e40(void)
 * Wrapper: reads three words from the register object, opens a stack
 * frame (FUN_001a84f4), runs FUN_00411d94, and closes it (FUN_001a8564).
 * Confidence: medium. */
void FUN_00411e40(uint64_t *reg)
{
    uint8_t s78[72];
    uint64_t r1, r2, r3;

    r1 = reg[0];
    r2 = reg[1];
    r3 = reg[2];
    FUN_001a84f4(s78);
    FUN_00411d94(s78, r1, r2, r3);
    FUN_001a8564();
}

/*--------------------------------------------------------------------*
 * FUN_00411f04 @ 0x00411f04   (est. sk_obj_service_pair_build)
 * Ghidra: undefined1 [16] FUN_00411f04(void, 0, 0, 0)
 * Builds a 16-byte (x0:x1) result from the two sibling service calls;
 * the four args are passed through registers.
 * Confidence: low (extraout_x8/x9 register results approximated). */
wpair_t FUN_00411f04(uint64_t a, uint64_t b, uint64_t c, uint64_t d)
{
    (void)a; (void)b; (void)c; (void)d;
    uint64_t lo, hi;
    FUN_004657b8();
    lo = thunk_FUN_002acbb8();
    FUN_004657ac();
    hi = thunk_FUN_002acbb8();
    return (wpair_t){ lo, hi };
}

/*--------------------------------------------------------------------*
 * FUN_00411f48 @ 0x00411f48   (est. sk_obj_service_pair_call_a)
 * Ghidra: void FUN_00411f48(void)
 * Calls FUN_00411f04 with four words read from the register object.
 * Confidence: medium. */
void FUN_00411f48(uint64_t *reg)
{
    FUN_00411f04(reg[0], reg[1], reg[2], reg[3]);
}

/*--------------------------------------------------------------------*
 * FUN_00411f4c @ 0x00411f4c   (est. sk_obj_service_pair_call_b)
 * Ghidra: void FUN_00411f4c(void)
 * Duplicate of FUN_00411f48.
 * Confidence: medium. */
void FUN_00411f4c(uint64_t *reg)
{
    FUN_00411f04(reg[0], reg[1], reg[2], reg[3]);
}

/*--------------------------------------------------------------------*
 * FUN_00411f68 @ 0x00411f68   (est. sk_obj_service_call_cb)
 * Ghidra: void FUN_00411f68(void)
 * Runs the service callback: opens a stack frame, sets up an object
 * (FUN_0034c444), invokes the callback (cb), and closes the frame.
 * Confidence: low (extraout_x1 approximated). */
void FUN_00411f68(code cb)
{
    uint64_t r1;
    FUN_004666f8();
    FUN_001a84f4((uint8_t *)&r1);
    FUN_0034c444((uint8_t *)&r1);
    (*cb)();
    r1 = FUN_001a8564();
    FUN_004666e4(r1, 0);
}

/*--------------------------------------------------------------------*
 * FUN_0041235c @ 0x0041235c   (est. sk_obj_service_step_dispatch)
 * Ghidra: void FUN_0041235c(undefined8, undefined8, ulong, ulong, ulong)
 * Swift object-service step dispatcher: switches on (param_5>>1)&3 to pick
 * the operation kind, logs the kind, then re-dispatches into the shared
 * per-type handler FUN_00410414 with the (maybe re-derived) key words.
 * Confidence: medium. */
void FUN_0041235c(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4, uint64_t p5)
{
    uint64_t u1;
    wpair_t pair;

    (void)p1; (void)p2;
    switch ((uint32_t)p5 >> 1 & 3) {
    default:
        u1 = 0;
        break;
    case 1:
        thunk_FUN_002298d4(1);
        FUN_0006b6f4();
        FUN_00410414(0, 0);
        thunk_FUN_002298d4(p3 >> 0xe);
        thunk_FUN_002298d4(p4 >> 0xe);
        p5 = p5 & 0xfffffffffffffff9ull;
        goto lab;
    case 2:
        u1 = 2;
        break;
    case 3:
        thunk_FUN_002298d4(3);
        return;
    }
    thunk_FUN_002298d4(u1);
    pair = FUN_0006b6f4();
    p5 = pair.hi;
    p1 = pair.lo;
lab:
    FUN_00410414(p1, p5);
}

/*--------------------------------------------------------------------*
 * FUN_004125ac @ 0x004125ac   (est. sk_obj_service_emit_pair)
 * Ghidra: void FUN_004125ac(void)
 * Emits two register-object key words through the sibling logger, then
 * dispatches the object-service step (FUN_0041235c) with the object
 * register-derived pointer as its first argument.
 * Confidence: low (unaff_x19 register arg; the 0-arg FUN_0041235c call is
 * a register-arg call site). */
void FUN_004125ac(uint64_t *obj)
{
    uint64_t u1;
    FUN_00464a44();
    u1 = obj[1];
    thunk_FUN_002298d4(obj[0] >> 0xe);
    thunk_FUN_002298d4(u1 >> 0xe);
    FUN_0041235c((uint64_t)obj, 0, 0, 0, 0);
    u1 = obj[7];
    thunk_FUN_002298d4(obj[6] >> 0xe);
    thunk_FUN_002298d4(u1 >> 0xe);
}

/*--------------------------------------------------------------------*
 * FUN_0041260c @ 0x0041260c   (est. sk_obj_service_emit_dispatch)
 * Ghidra: void FUN_0041260c(void)
 * Emits a per-object dispatch: writes the object kind (FUN_00465234),
 * runs the 5-argument service-step dispatcher with words read from the
 * object, and re-emits the next word.
 * Confidence: medium. */
void FUN_0041260c(uint64_t *obj)
{
    uint8_t s78[72];
    FUN_004644e8();
    FUN_00465234(obj[0]);
    FUN_004652a0();
    FUN_0041235c((uint64_t)s78, *(uint64_t *)(obj + 2),
                 *(uint64_t *)(obj + 3), *(uint64_t *)(obj + 4), *(uint64_t *)(obj + 5));
    FUN_00465234(*(uint64_t *)(obj + 6));
    FUN_00464eb0();
    FUN_001a8564();
}

/*--------------------------------------------------------------------*
 * FUN_004129ec @ 0x004129ec   (est. sk_obj_service_state_copy)
 * Ghidra: void FUN_004129ec(void)
 * Copies a 0x50-byte object-state pair out of a 16-byte register value
 * (FUN_00077888 returns two pointers), then stores the two register words
 * at offsets +0x50/+0x58.
 * Confidence: low (unaff_x19/x20 register args; 16-byte pair of pointers). */
void FUN_004129ec(void)
{
    wpair_t pair;
    uint64_t *p0, *p1;
    uint8_t s80[0x60];

    pair = FUN_00077888();
    p0 = (uint64_t *)pair.lo;
    p1 = (uint64_t *)pair.hi;
    FUN_00117cc4(&s80, p0, 0x50);
    *(uint64_t *)(s80 + 0x50) = 0;
    *(uint64_t *)(s80 + 0x58) = 0;
}

/*--------------------------------------------------------------------*
 * FUN_00412bb0 @ 0x00412bb0   (est. sk_obj_service_emit_slot)
 * Ghidra: void FUN_00412bb0(void)
 * Emits one object-service slot: reads state from the register object,
 * conditionally invokes the kind helpers (FUN_00464ac4 / FUN_00229a3c /
 * FUN_00465584), and logs the slot key words.
 * Confidence: low (unaff_x20/x21 register args). */
void FUN_00412bb0(uint64_t *reg)
{
    uint64_t u1, u2, u4;
    uint8_t c;

    (void)reg;
    FUN_00084220();
    FUN_004656d4();
    FUN_0041288c(0);
    if (*(uint8_t *)(reg + 9) == 1) {
        FUN_00464ac4();
        FUN_00229a3c();
    } else {
        u4 = *(uint64_t *)(reg + 5);
        u2 = *(uint64_t *)(reg + 7);
        u1 = *(uint64_t *)(reg + 8);
        c = *(uint8_t *)(reg + 6);
        FUN_00465584();
        if (c == 1) {
            FUN_00464ac4();
            FUN_00229a3c();
        } else {
            FUN_00465584();
            thunk_FUN_002298d4(u4);
        }
        thunk_FUN_002298d4(u2 >> 0xe);
        thunk_FUN_002298d4(u1 >> 0xe);
    }
    u2 = *(uint64_t *)(reg + 11);
    FUN_004647b4(*(uint64_t *)(reg + 10));
    thunk_FUN_002298d4();
    thunk_FUN_002298d4(u2 >> 0xe);
    FUN_00084234(0);
}

/*--------------------------------------------------------------------*
 * FUN_00412c54 @ 0x00412c54   (est. sk_obj_service_emit_slot_wrap_a)
 * Ghidra: void FUN_00412c54(void)
 * Wrapper: runs FUN_00412bb0 after setting up the object service.
 * Confidence: medium. */
void FUN_00412c54(void)
{
    uint8_t s68[72];
    FUN_004080b0();
    FUN_00412bb0((uint64_t *)s68);
    FUN_001a8564();
}

/*--------------------------------------------------------------------*
 * FUN_00412c94 @ 0x00412c94   (est. sk_obj_service_emit_slot_wrap_b)
 * Ghidra: void FUN_00412c94(void)
 * Wrapper: opens a frame, runs FUN_00412bb0, closes the frame.
 * Confidence: medium. */
void FUN_00412c94(void)
{
    uint8_t s68[72];
    FUN_001a84f4(s68);
    FUN_00412bb0((uint64_t *)s68);
    FUN_001a8564();
}

/*--------------------------------------------------------------------*
 * FUN_00412d00 @ 0x00412d00   (est. sk_obj_service_snapshot_check)
 * Ghidra: void FUN_00412d00(long param_1)
 * Validates an object-service snapshot: panics (SoftwareBreakpoint) if the
 * object has an empty payload, else snapshots it (FUN_0041106c) and
 * re-dispatches unless the count sentinel is -1.
 * Confidence: medium.
 * Notes: SoftwareBreakpoint(1,addr) is the does-not-return trap path. */
void FUN_00412d00(uint64_t obj)
{
    uint8_t s50[8];
    uint64_t local48;
    uint64_t local30, u28;

    if (*(int64_t *)(obj + 0x10) == 0) {
        SoftwareBreakpoint(1, 0x412d58);
    }
    FUN_0041106c(s50, obj);
    if (local48 >> 1 != 0xffffffff) {
        FUN_003513fc(local30, u28);
        FUN_00412d5c(0, 0, 0, 0, 0);
        return;
    }
    SoftwareBreakpoint(1, 0x412d5c);
}

/*--------------------------------------------------------------------*
 * FUN_00413a60 @ 0x00413a60   (est. sk_obj_service_emit_value)
 * Ghidra: void FUN_00413a60(void)
 * Emits a value from the register object: runs the per-type step
 * (FUN_0041360c) and logs the object words at +0xa0/+0xa8.
 * Confidence: low (unaff_x20 register arg). */
void FUN_00413a60(uint64_t *reg)
{
    uint64_t u1;
    FUN_0041360c(0, 0);
    u1 = *(uint64_t *)(reg + 0xa8 / 8);
    FUN_004647b4(*(uint64_t *)(reg + 0xa0 / 8));
    thunk_FUN_002298d4();
    thunk_FUN_002298d4(u1 >> 0xe);
}

/*--------------------------------------------------------------------*
 * FUN_00413aec @ 0x00413aec   (est. sk_obj_service_emit_value_wrap)
 * Ghidra: void FUN_00413aec(void)
 * Wrapper: opens a frame, emits a value (FUN_00413a60), closes the frame.
 * Confidence: medium. */
void FUN_00413aec(void)
{
    uint8_t s68[72];
    FUN_001a84f4(s68);
    FUN_00413a60((uint64_t *)s68);
    FUN_001a8564();
}

/*--------------------------------------------------------------------*
 * FUN_00412248 @ 0x00412248   (est. sk_obj_service_select_kind)
 * Ghidra: undefined8 FUN_00412248(ulong, ulong, undefined8, ulong, ulong,
 *                                 ulong, long, ulong)
 * Selects the object-service operation kind from the tag bits
 * ((param_4>>1)&3) and permission bits (param_8&6); returns a status word,
 * dispatching into FUN_0041001c for the default / allowed cases.
 * Confidence: medium. */
uint64_t FUN_00412248(uint64_t p1, uint64_t p2, uint64_t p3, uint64_t p4,
                      uint64_t p5, uint64_t p6, uint64_t p7, uint64_t p8)
{
    uint64_t r1;
    (void)p3;
    switch ((uint32_t)p4 >> 1 & 3) {
    default:
        if ((p8 & 6) == 0) {
lab:
            r1 = FUN_0041001c(p1, p5);
            return r1;
        }
        break;
    case 1:
        if ((p8 & 6) == 2) {
            FUN_0041001c(p1, p5);
            r1 = FUN_00464a08();
            if ((p1 & 1) == 0) return r1;
            if ((p6 ^ p2) >> 0xe != 0) return r1;
            r1 = FUN_00465fd4();
            if (p1 != 0) return r1;
            p1 = p4 & 0xfffffffffffffff9ull;
            p5 = p8 & 0xfffffffffffffff9ull;
            goto lab;
        }
        break;
    case 2:
        if ((p8 & 6) == 4) goto lab;
        break;
    case 3:
        if ((((~(uint32_t)p8 & 6) == 0) && p6 == 0 && p5 == 0 && p7 == 0) && p8 == 6)
            return 1;
    }
    return 0;
}

/*--------------------------------------------------------------------*
 * FUN_00415470 @ 0x00415470   (est. sk_obj_service_index_emit)
 * Ghidra: void FUN_00415470(ulong param_1)
 * Emits the object-service table entry indexed by the low byte of param_1
 * (table base DAT_005a3930, 8-byte entries).
 * Confidence: medium. */
uint64_t FUN_00415470(uint64_t p1)
{
    return FUN_004659e8(*(uint64_t *)((uint8_t *)DAT_005a3930 + (p1 & 0xff) * 8));
}

/*--------------------------------------------------------------------*
 * FUN_0041577c @ 0x0041577c   (est. sk_obj_service_cb_dispatch)
 * Ghidra: void FUN_0041577c(undefined8, undefined8, code *param_3)
 * Runs the 16-byte-returning callback (cb) with the word arg, feeds the
 * returned pair into FUN_001b9084, and releases the high word.
 * Confidence: low (callback returns 16-byte value; hi word approximated). */
void FUN_0041577c(uint64_t p1, uint64_t p2, code cb)
{
    wpair_t r;
    r.lo = (*cb)(p2);
    r.hi = 0;
    FUN_001b9084(p1, r.lo, r.hi);
    FUN_003a25d4(r.hi);
}
